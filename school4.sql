/*
 Navicat Premium Data Transfer

 Source Server         : root
 Source Server Type    : MySQL
 Source Server Version : 80021
 Source Host           : localhost:3306
 Source Schema         : school2

 Target Server Type    : MySQL
 Target Server Version : 80021
 File Encoding         : 65001

 Date: 31/05/2021 21:55:08
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for 专业
-- ----------------------------
DROP TABLE IF EXISTS `专业`;
CREATE TABLE `专业` (
  `专业编号` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `专业名称` varchar(50) NOT NULL,
  `学院编号` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  PRIMARY KEY (`专业编号`),
  KEY `学院编号` (`学院编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

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
  `书籍编号` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `作者` varchar(30) NOT NULL,
  `出版社` varchar(30) NOT NULL,
  `库存` int DEFAULT NULL,
  `出版年份` date DEFAULT NULL,
  `价格` decimal(10,3) NOT NULL DEFAULT '0.000',
  `类别` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL DEFAULT '',
  `可借副本数量` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`书籍编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

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
  `床号` int NOT NULL DEFAULT '1',
  PRIMARY KEY (`宿舍编号`,`学号`),
  KEY `学号` (`学号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of 住宿
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for 可借图书
-- ----------------------------
DROP TABLE IF EXISTS `可借图书`;
CREATE TABLE `可借图书` (
  `可借书籍编号` varchar(15) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `可借副本编号` int NOT NULL,
  `学号` varchar(15) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `借书日期` date NOT NULL,
  `应还日期` date NOT NULL,
  `罚款` decimal(10,3) NOT NULL DEFAULT '0.000',
  PRIMARY KEY (`可借书籍编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of 可借图书
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for 学生
-- ----------------------------
DROP TABLE IF EXISTS `学生`;
CREATE TABLE `学生` (
  `学号` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `密码` varchar(30) NOT NULL,
  `性别` varchar(3) DEFAULT NULL,
  `姓名` varchar(30) NOT NULL,
  `生日` date DEFAULT NULL,
  `电话` varchar(30) DEFAULT NULL,
  `班级编号` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `意愿值` int DEFAULT '100',
  PRIMARY KEY (`学号`),
  KEY `班级编号` (`班级编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of 学生
-- ----------------------------
BEGIN;
INSERT INTO `学生` VALUES ('10185102101', 'lxh', '女', '李小浩', '2000-11-14', '13845678912', '01', NULL);
INSERT INTO `学生` VALUES ('10185102102', 'dxy', '女', '董小尧', '2020-01-31', '13348678912', '01', NULL);
COMMIT;

-- ----------------------------
-- Table structure for 学院
-- ----------------------------
DROP TABLE IF EXISTS `学院`;
CREATE TABLE `学院` (
  `学院编号` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `学院名称` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `院长` varchar(20) NOT NULL,
  PRIMARY KEY (`学院编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

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
  `宿舍编号` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `楼栋编号` varchar(30) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  PRIMARY KEY (`宿舍编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of 宿舍
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for 开设课程
-- ----------------------------
DROP TABLE IF EXISTS `开设课程`;
CREATE TABLE `开设课程` (
  `课程编号` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `开课学期` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `课程名称` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `课程类别` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `考试时间` date DEFAULT NULL,
  `考试地点` varchar(30) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `选课开始时间` datetime DEFAULT NULL,
  `选课截止时间` datetime DEFAULT NULL,
  `人数上限` decimal(5,2) DEFAULT NULL,
  PRIMARY KEY (`开课学期`,`课程编号`) USING BTREE,
  KEY `课程编号` (`课程编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of 开设课程
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for 教务
-- ----------------------------
DROP TABLE IF EXISTS `教务`;
CREATE TABLE `教务` (
  `教务编号` varchar(15) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `教务姓名` varchar(255) DEFAULT NULL,
  `密码` varchar(15) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '12345',
  PRIMARY KEY (`教务编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of 教务
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
  KEY `课程编号` (`课程编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

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
  `教师编号` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `教师姓名` varchar(30) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `邮箱` varchar(50) NOT NULL,
  `性别` varchar(3) DEFAULT NULL,
  `电话` varchar(20) DEFAULT NULL,
  `薪资` decimal(8,2) DEFAULT NULL,
  `生日` date DEFAULT NULL,
  `密码` varchar(20) DEFAULT NULL,
  `学院编号` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`教师编号`),
  KEY `学院编号` (`学院编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

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
  `班级编号` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `班长学号` varchar(30) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `专业编号` varchar(10) DEFAULT NULL,
  `人数` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`班级编号`),
  KEY `专业编号` (`专业编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

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
  `密码` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL DEFAULT '123456789',
  PRIMARY KEY (`管理员编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

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
  `课程编号` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `课程名称` varchar(30) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `考试类型` varchar(30) NOT NULL,
  `学分` decimal(5,2) DEFAULT NULL,
  `类别` varchar(30) NOT NULL,
  `授课老师` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`课程编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

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
  `学号` varchar(15) NOT NULL,
  `开课编号` varchar(255) NOT NULL,
  `所投意愿值` decimal(4,0) DEFAULT NULL,
  PRIMARY KEY (`学号`,`开课编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of 选课
-- ----------------------------
BEGIN;
COMMIT;

SET FOREIGN_KEY_CHECKS = 1;
