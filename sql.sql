CREATE DATABASE grade_db;
DROP TABLE IF EXISTS `grade_db`.`grade`;
DROP TABLE IF EXISTS `grade_db`.`stu`;
DROP TABLE IF EXISTS `grade_db`.`subject`;
CREATE TABLE `grade` (
  `grade_id` int NOT NULL AUTO_INCREMENT,
  `stu_id` int DEFAULT NULL,
  `subject_id` int DEFAULT NULL,
  `score` decimal(4,1) DEFAULT NULL,
  PRIMARY KEY (`grade_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

CREATE TABLE `stu` (
  `stu_id` int NOT NULL AUTO_INCREMENT,
  `stu_num` varchar(30) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `stu_name` varchar(255) COLLATE utf8mb4_general_ci DEFAULT NULL,
  PRIMARY KEY (`stu_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

CREATE TABLE `subject` (
  `subject_id` int NOT NULL AUTO_INCREMENT,
  `subject_name` varchar(255) COLLATE utf8mb4_general_ci DEFAULT NULL,
  PRIMARY KEY (`subject_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

INSERT INTO `stu` (`stu_id`, `stu_num`, `stu_name`) VALUES (1, '2019205913', 'hpy');
INSERT INTO `stu` (`stu_id`, `stu_num`, `stu_name`) VALUES (2, '2019205883', 'huangfususu');

INSERT INTO `grade` (`grade_id`, `stu_id`, `subject_id`, `score`) VALUES (0, 1, 0, 100.0);
INSERT INTO `grade` (`grade_id`, `stu_id`, `subject_id`, `score`) VALUES (1, 1, 1, 80.0);
INSERT INTO `grade` (`grade_id`, `stu_id`, `subject_id`, `score`) VALUES (2, 1, 2, 60.0);
INSERT INTO `grade` (`grade_id`, `stu_id`, `subject_id`, `score`) VALUES (3, 2, 0, 63.5);
INSERT INTO `grade` (`grade_id`, `stu_id`, `subject_id`, `score`) VALUES (4, 2, 1, 80.0);
INSERT INTO `grade` (`grade_id`, `stu_id`, `subject_id`, `score`) VALUES (5, 2, 2, 50.0);

INSERT INTO `subject` (`subject_id`, `subject_name`) VALUES (0, 'ch');
INSERT INTO `subject` (`subject_id`, `subject_name`) VALUES (1, 'math');
INSERT INTO `subject` (`subject_id`, `subject_name`) VALUES (2, 'eng');