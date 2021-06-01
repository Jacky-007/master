/*
 Navicat Premium Data Transfer

 Source Server         : root
 Source Server Type    : MySQL
 Source Server Version : 80021
 Source Host           : localhost:3306
 Source Schema         : school

 Target Server Type    : MySQL
 Target Server Version : 80021
 File Encoding         : 65001

 Date: 27/05/2021 17:11:52
*/

SET NAMES utf8;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for 专业
-- ----------------------------
DROP TABLE IF EXISTS `专业`;
CREATE TABLE `专业` (
  `编号` varchar(10) NOT NULL,
  `专业名称` varchar(50) NOT NULL,
  `学院编号` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`编号`),
  KEY `学院编号` (`学院编号`),
  CONSTRAINT `专业_ibfk_1` FOREIGN KEY (`学院编号`) REFERENCES `学院` (`编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

-- ----------------------------
-- Records of 专业
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for 书籍
-- ----------------------------
DROP TABLE IF EXISTS `书籍`;
CREATE TABLE `书籍` (
  `编号` varchar(10) NOT NULL,
  `作者` varchar(30) NOT NULL,
  `出版社` varchar(30) NOT NULL,
  `库存` int DEFAULT NULL,
  `出版年份` int DEFAULT NULL,
  `可借数量` int DEFAULT NULL,
  PRIMARY KEY (`编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

-- ----------------------------
-- Records of 书籍
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for 住宿
-- ----------------------------
DROP TABLE IF EXISTS `住宿`;
CREATE TABLE `住宿` (
  `宿舍编号` varchar(10) NOT NULL,
  `学号` varchar(10) NOT NULL,
  PRIMARY KEY (`宿舍编号`,`学号`),
  KEY `学号` (`学号`),
  CONSTRAINT `住宿_ibfk_1` FOREIGN KEY (`宿舍编号`) REFERENCES `宿舍` (`编号`),
  CONSTRAINT `住宿_ibfk_2` FOREIGN KEY (`学号`) REFERENCES `学生` (`编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

-- ----------------------------
-- Records of 住宿
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for 借阅
-- ----------------------------
DROP TABLE IF EXISTS `借阅`;
CREATE TABLE `借阅` (
  `学号` varchar(10) NOT NULL,
  `图书编号` varchar(10) NOT NULL,
  `借阅日期` date NOT NULL,
  `归还日期` date DEFAULT NULL,
  `欠费情况` decimal(8,2) DEFAULT NULL,
  PRIMARY KEY (`学号`,`图书编号`,`借阅日期`),
  KEY `图书编号` (`图书编号`),
  CONSTRAINT `借阅_ibfk_1` FOREIGN KEY (`图书编号`) REFERENCES `书籍` (`编号`),
  CONSTRAINT `借阅_ibfk_2` FOREIGN KEY (`学号`) REFERENCES `学生` (`编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

-- ----------------------------
-- Records of 借阅
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for 学生
-- ----------------------------
DROP TABLE IF EXISTS `学生`;
CREATE TABLE `学生` (
  `编号` varchar(10) NOT NULL,
  `密码` varchar(30) NOT NULL,
  `性别` varchar(3) DEFAULT NULL,
  `姓名` varchar(30) NOT NULL,
  `生日` date DEFAULT NULL,
  `电话` varchar(30) DEFAULT NULL,
  `班级编号` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`编号`),
  KEY `班级编号` (`班级编号`),
  CONSTRAINT `学生_ibfk_1` FOREIGN KEY (`班级编号`) REFERENCES `班级` (`编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

-- ----------------------------
-- Records of 学生
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for 学院
-- ----------------------------
DROP TABLE IF EXISTS `学院`;
CREATE TABLE `学院` (
  `编号` varchar(10) NOT NULL,
  `名称` varchar(50) NOT NULL,
  `院长` varchar(20) NOT NULL,
  PRIMARY KEY (`编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

-- ----------------------------
-- Records of 学院
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for 宿舍
-- ----------------------------
DROP TABLE IF EXISTS `宿舍`;
CREATE TABLE `宿舍` (
  `编号` varchar(10) NOT NULL,
  `楼栋` varchar(30) NOT NULL,
  PRIMARY KEY (`编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

-- ----------------------------
-- Records of 宿舍
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for 教学
-- ----------------------------
DROP TABLE IF EXISTS `教学`;
CREATE TABLE `教学` (
  `教师编号` varchar(10) NOT NULL,
  `课程编号` varchar(10) NOT NULL,
  `授课时间` date NOT NULL,
  PRIMARY KEY (`教师编号`,`课程编号`,`授课时间`),
  KEY `课程编号` (`课程编号`),
  CONSTRAINT `教学_ibfk_1` FOREIGN KEY (`教师编号`) REFERENCES `教师` (`编号`),
  CONSTRAINT `教学_ibfk_2` FOREIGN KEY (`课程编号`) REFERENCES `课程` (`编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

-- ----------------------------
-- Records of 教学
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for 教师
-- ----------------------------
DROP TABLE IF EXISTS `教师`;
CREATE TABLE `教师` (
  `编号` varchar(10) NOT NULL,
  `姓名` varchar(30) NOT NULL,
  `邮箱` varchar(50) NOT NULL,
  `性别` varchar(3) DEFAULT NULL,
  `电话` varchar(20) DEFAULT NULL,
  `薪资` decimal(8,2) DEFAULT NULL,
  `生日` date DEFAULT NULL,
  `密码` varchar(20) DEFAULT NULL,
  `学院编号` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`编号`),
  KEY `学院编号` (`学院编号`),
  CONSTRAINT `教师_ibfk_1` FOREIGN KEY (`学院编号`) REFERENCES `学院` (`编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

-- ----------------------------
-- Records of 教师
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for 班级
-- ----------------------------
DROP TABLE IF EXISTS `班级`;
CREATE TABLE `班级` (
  `编号` varchar(10) NOT NULL,
  `班长` varchar(30) DEFAULT NULL,
  `专业编号` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`编号`),
  KEY `专业编号` (`专业编号`),
  CONSTRAINT `班级_ibfk_1` FOREIGN KEY (`专业编号`) REFERENCES `专业` (`编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

-- ----------------------------
-- Records of 班级
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for 管理员
-- ----------------------------
DROP TABLE IF EXISTS `管理员`;
CREATE TABLE `管理员` (
  `管理员编号` varchar(255) NOT NULL,
  `管理员姓名` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`管理员编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

-- ----------------------------
-- Records of 管理员
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for 课程
-- ----------------------------
DROP TABLE IF EXISTS `课程`;
CREATE TABLE `课程` (
  `编号` varchar(10) NOT NULL,
  `名称` varchar(30) NOT NULL,
  `考试类型` varchar(30) NOT NULL,
  `学分` int DEFAULT NULL,
  `类别` varchar(30) NOT NULL,
  PRIMARY KEY (`编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

-- ----------------------------
-- Records of 课程
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for 选课
-- ----------------------------
DROP TABLE IF EXISTS `选课`;
CREATE TABLE `选课` (
  `学号` varchar(10) NOT NULL,
  `课程编号` varchar(10) NOT NULL,
  `分数` decimal(5,2) DEFAULT NULL,
  `考试时间` date DEFAULT NULL,
  `考试地点` varchar(30) NOT NULL,
  `选课时间` date DEFAULT NULL,
  PRIMARY KEY (`学号`,`课程编号`),
  KEY `课程编号` (`课程编号`),
  CONSTRAINT `选课_ibfk_1` FOREIGN KEY (`学号`) REFERENCES `学生` (`编号`),
  CONSTRAINT `选课_ibfk_2` FOREIGN KEY (`课程编号`) REFERENCES `课程` (`编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

-- ----------------------------
-- Records of 选课
-- ----------------------------
BEGIN;
COMMIT;

SET FOREIGN_KEY_CHECKS = 1;
