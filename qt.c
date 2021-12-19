#include <QApplication>
#include <QDebug>
#include <QtSql>
#include <QtGui>
#if QT_VERSION_MAJOR > 4
#include <QtWidgets>
#endif

class StuGrade {
   QString m_stuid, m_stuname, m_stunum,m_ch,m_math,m_eng;
public:
   StuGrade(const QString & stuid, const QString & stuname, const QString & stunum, const QString & ch, const QString & math, const QString & eng) :
      m_stuid{stuid}, m_stuname{stuname}, m_stunum{stunum},m_ch{ch},m_math(math),m_eng{eng} {}
   QString stuid() const { return m_stuid; }
   QString stuname() const { return m_stuname; }
   QString stunum() const { return m_stunum; }
   QString ch() const { return m_ch; }
   QString math() const { return m_math; }
   QString eng() const { return m_eng; }
 };

class StuGradeModel : public QAbstractTableModel {
   QList<StuGrade> m_data;
public:
   StuGradeModel(QObject * parent = {}) : QAbstractTableModel{parent} {}
   int rowCount(const QModelIndex &) const override { return m_data.count(); }
   int columnCount(const QModelIndex &) const override { return 6; }
   QVariant data(const QModelIndex &index, int role) const override {
      if (role != Qt::DisplayRole && role != Qt::EditRole) return {};
      const auto & stu = m_data[index.row()];
      switch (index.column()) {
      case 0: return stu.stuid();
      case 1: return stu.stuname();
      case 2: return stu.stunum();
      case 3: return stu.ch();
      case 4: return stu.eng();
      case 5: return stu.math();
      default: return {};
      };
   }
   QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
      if (orientation != Qt::Horizontal || role != Qt::DisplayRole) return {};
      switch (section) {
      case 0: return "id";
      case 1: return "name";
      case 2: return "num";
      case 3: return "Ch";
      case 4: return "Math";
      case 5: return "Eng";

      default: return {};
      }
   }
   void append(const StuGrade & stu) {
      beginInsertRows({}, m_data.count(), m_data.count());
      m_data.append(stu);
      endInsertRows();
   }
};

class Widget : public QWidget {
   QGridLayout m_layout{this};
   QTableView m_view;
   StuGradeModel m_model;
   QSortFilterProxyModel m_proxy;
   QInputDialog m_dialog;
public:
   Widget() {
      m_layout.addWidget(&m_view, 0, 0, 1, 1);
      QSqlDatabase  db  = QSqlDatabase::addDatabase("QMYSQL");
      db.setHostName("127.0.0.1");
      db.setDatabaseName("grade_db");
      db.setPort(3306);
      db.setUserName("root");
      db.setPassword("HPyuko12!!");
      if(db.open()){
          qDebug()<<"connect successfully!";
          QSqlQuery query(db);
          query.exec("SELECT stu_id,stu_num, stu_name,(SELECT score FROM grade WHERE stu_id = stu.stu_id AND subject_id = 0 ) AS ch,(SELECT score FROM grade WHERE stu_id = stu.stu_id AND subject_id = 1 ) AS math,(SELECT score FROM grade WHERE stu_id = stu.stu_id AND subject_id = 2 ) AS eng FROM stu;");
          while(query.next()){
              QString id = query.value(0).toString();
              QString stu_num = query.value(1).toString();
              QString stu_name = query.value(2).toString();
              QString ch = query.value(3).toString();
              QString math = query.value(4).toString();
              QString eng = query.value(5).toString();

              m_model.append({id,stu_num,stu_name, ch, math, eng});

              qDebug()<< id << stu_num << stu_name << ch << math << eng;
          }

          m_proxy.setSourceModel(&m_model);
          m_proxy.setFilterKeyColumn(2);
          m_view.setModel(&m_proxy);
      }
      else
          qDebug()<<"failed!!!!";
   }
};

int main(int argc, char *argv[])
{
   QApplication a{argc, argv};
   Widget w;
   w.resize(800,600);
   w.show();
   return a.exec();
}