/*
 Navicat MySQL Data Transfer

 Source Server         : dbexperiment
 Source Server Type    : MySQL
 Source Server Version : 80023
 Source Host           : localhost:3306
 Source Schema         : filmdb

 Target Server Type    : MySQL
 Target Server Version : 80023
 File Encoding         : 65001

 Date: 05/06/2021 21:22:56
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for cinema_hallinfo
-- ----------------------------
DROP TABLE IF EXISTS `cinema_hallinfo`;
CREATE TABLE `cinema_hallinfo` (
  `cinema_hallID` int NOT NULL AUTO_INCREMENT,
  `address` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `hallName` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `capacity` int NOT NULL DEFAULT '100',
  PRIMARY KEY (`cinema_hallID`),
  KEY `cinema_hallID` (`cinema_hallID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of cinema_hallinfo
-- ----------------------------
BEGIN;
INSERT INTO `cinema_hallinfo` VALUES (1, '杨浦店', 'A', 100);
INSERT INTO `cinema_hallinfo` VALUES (2, '杨浦店', 'B', 80);
INSERT INTO `cinema_hallinfo` VALUES (3, '杨浦店', 'C', 50);
INSERT INTO `cinema_hallinfo` VALUES (4, '长宁店', 'A', 100);
INSERT INTO `cinema_hallinfo` VALUES (5, '长宁店', 'B', 80);
INSERT INTO `cinema_hallinfo` VALUES (6, '长宁店', 'C', 50);
INSERT INTO `cinema_hallinfo` VALUES (7, '闵行店', 'A', 100);
INSERT INTO `cinema_hallinfo` VALUES (8, '闵行店', 'B', 80);
COMMIT;

-- ----------------------------
-- Table structure for filminfo
-- ----------------------------
DROP TABLE IF EXISTS `filminfo`;
CREATE TABLE `filminfo` (
  `filmID` char(16) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `filmName` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `typeID` char(2) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `actor` varchar(255) DEFAULT NULL,
  `director` varchar(50) DEFAULT NULL,
  `filmGrade` decimal(3,1) DEFAULT NULL,
  PRIMARY KEY (`filmID`),
  KEY `fk_FilmInfo_FilmType` (`typeID`),
  CONSTRAINT `filminfo_ibfk_1` FOREIGN KEY (`typeID`) REFERENCES `filmtype` (`typeID`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of filminfo
-- ----------------------------
BEGIN;
INSERT INTO `filminfo` VALUES ('GH19540107900001', '百万英镑', 'XJ', '格里高利·派克，乔伊斯·格伦菲尔等', '罗纳德·尼姆', 8.0);
INSERT INTO `filminfo` VALUES ('GH19890602600002', '死亡诗社', 'QT', '罗宾·威廉姆斯，伊桑·霍克等', '彼得·威尔', 8.0);
INSERT INTO `filminfo` VALUES ('GH19940914600001', '这个杀手不太冷', 'GF', '让·雷诺，加里·奥德曼，娜塔莉·波特曼等', '吕克·贝松', 8.0);
INSERT INTO `filminfo` VALUES ('GH20070518300005', '唐伯虎点秋香', 'XJ', '周星驰，巩俐等', '李力持', 8.0);
INSERT INTO `filminfo` VALUES ('GH20080318300005', '猫和老鼠', 'DH', '', '威廉·汉纳及约瑟夫·巴', 8.0);
INSERT INTO `filminfo` VALUES ('GH20080618400001', '倚天屠龙记', 'GF', '李连杰,邱淑贞', '王晶', 8.0);
INSERT INTO `filminfo` VALUES ('GH20190510500001', '大侦探皮卡丘', 'DH', NULL, '罗伯·莱特曼', 8.0);
INSERT INTO `filminfo` VALUES ('GH20190524800001', '五月天人生无限公司', 'QT', '温商翊，石锦航，蔡升晏等', '陈奕仁', 8.0);
INSERT INTO `filminfo` VALUES ('GH20190524800002', '龙珠超：布罗利', 'DH', NULL, '长峰达也', 8.0);
COMMIT;

-- ----------------------------
-- Table structure for filmtype
-- ----------------------------
DROP TABLE IF EXISTS `filmtype`;
CREATE TABLE `filmtype` (
  `typeID` char(2) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `typeName` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`typeID`),
  KEY `typeID` (`typeID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of filmtype
-- ----------------------------
BEGIN;
INSERT INTO `filmtype` VALUES ('AQ', '爱情片');
INSERT INTO `filmtype` VALUES ('DH', '动画片');
INSERT INTO `filmtype` VALUES ('GF', '功夫片');
INSERT INTO `filmtype` VALUES ('QT', '其他');
INSERT INTO `filmtype` VALUES ('XJ', '喜剧片');
INSERT INTO `filmtype` VALUES ('ZZ', '战争片');
COMMIT;

-- ----------------------------
-- Table structure for memberinfo
-- ----------------------------
DROP TABLE IF EXISTS `memberinfo`;
CREATE TABLE `memberinfo` (
  `memberID` int NOT NULL AUTO_INCREMENT,
  `memberName` varchar(20) DEFAULT NULL,
  `memberShip` char(2) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT 'D',
  `discount` decimal(2,1) NOT NULL,
  PRIMARY KEY (`memberID`),
  KEY `memberID` (`memberID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of memberinfo
-- ----------------------------
BEGIN;
INSERT INTO `memberinfo` VALUES (1, '赵一', 'A', 0.5);
INSERT INTO `memberinfo` VALUES (2, '赵二', 'B', 0.7);
INSERT INTO `memberinfo` VALUES (3, '赵三', 'C', 0.9);
INSERT INTO `memberinfo` VALUES (4, '赵四', 'D', 1.0);
INSERT INTO `memberinfo` VALUES (5, '钱一', 'A', 0.5);
INSERT INTO `memberinfo` VALUES (6, '钱二', 'B', 0.7);
INSERT INTO `memberinfo` VALUES (7, '钱三', 'C', 0.9);
INSERT INTO `memberinfo` VALUES (8, '钱四', 'D', 1.0);
INSERT INTO `memberinfo` VALUES (9, '孙一', 'A', 0.5);
INSERT INTO `memberinfo` VALUES (10, '孙二', 'B', 0.7);
INSERT INTO `memberinfo` VALUES (11, '孙三', 'C', 0.9);
INSERT INTO `memberinfo` VALUES (12, '孙四', 'D', 1.0);
COMMIT;

-- ----------------------------
-- Table structure for playinfo
-- ----------------------------
DROP TABLE IF EXISTS `playinfo`;
CREATE TABLE `playinfo` (
  `playID` int NOT NULL AUTO_INCREMENT,
  `filmID` char(16) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `cinema_hallID` int NOT NULL,
  `startTime` datetime NOT NULL,
  `endTime` datetime NOT NULL,
  `price` decimal(6,2) NOT NULL DEFAULT '100.00',
  PRIMARY KEY (`playID`),
  KEY `filmID` (`filmID`),
  KEY `cinema_hallID` (`cinema_hallID`),
  CONSTRAINT `playinfo_ibfk_1` FOREIGN KEY (`filmID`) REFERENCES `filminfo` (`filmID`),
  CONSTRAINT `playinfo_ibfk_2` FOREIGN KEY (`cinema_hallID`) REFERENCES `cinema_hallinfo` (`cinema_hallID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of playinfo
-- ----------------------------
BEGIN;
INSERT INTO `playinfo` VALUES (1, 'GH20070518300005', 4, '2007-05-18 09:00:00', '2007-05-18 11:00:00', 80.00);
INSERT INTO `playinfo` VALUES (2, 'GH20080318300005', 5, '2008-03-18 15:00:00', '2008-03-18 17:00:00', 80.00);
INSERT INTO `playinfo` VALUES (3, 'GH20080618400001', 6, '2008-06-18 19:00:00', '2008-06-18 21:00:00', 198.00);
INSERT INTO `playinfo` VALUES (4, 'GH20190510500001', 7, '2019-05-10 00:00:00', '2019-05-10 02:00:00', 68.00);
INSERT INTO `playinfo` VALUES (5, 'GH20190524800001', 7, '2019-05-24 08:00:00', '2019-05-24 10:00:00', 70.00);
INSERT INTO `playinfo` VALUES (6, 'GH20190524800002', 7, '2019-05-24 08:00:00', '2019-05-24 10:00:00', 45.00);
INSERT INTO `playinfo` VALUES (7, 'GH19540107900001', 2, '2019-06-06 08:00:00', '2019-06-06 10:00:00', 168.00);
INSERT INTO `playinfo` VALUES (8, 'GH19540107900001', 2, '2019-06-06 11:00:00', '2019-06-06 13:00:00', 168.00);
INSERT INTO `playinfo` VALUES (9, 'GH19540107900001', 2, '2019-06-06 14:00:00', '2019-06-06 16:00:00', 168.00);
INSERT INTO `playinfo` VALUES (10, 'GH19540107900001', 2, '2019-06-06 17:00:00', '2019-06-06 19:00:00', 168.00);
INSERT INTO `playinfo` VALUES (11, 'GH19540107900001', 2, '2019-06-06 20:00:00', '2019-06-06 22:00:00', 168.00);
INSERT INTO `playinfo` VALUES (12, 'GH19940914600001', 3, '2019-03-15 08:00:00', '2019-03-15 10:00:00', 178.00);
INSERT INTO `playinfo` VALUES (13, 'GH19940914600001', 3, '2019-03-15 11:00:00', '2019-03-15 13:00:00', 178.00);
INSERT INTO `playinfo` VALUES (14, 'GH19940914600001', 3, '2019-03-15 14:00:00', '2019-03-15 16:00:00', 178.00);
INSERT INTO `playinfo` VALUES (15, 'GH19940914600001', 3, '2019-03-15 17:00:00', '2019-03-15 19:00:00', 178.00);
INSERT INTO `playinfo` VALUES (16, 'GH19940914600001', 3, '2019-03-15 20:00:00', '2019-03-15 22:00:00', 178.00);
INSERT INTO `playinfo` VALUES (17, 'GH19940914600001', 3, '2019-03-15 23:00:00', '2019-03-16 01:00:00', 178.00);
INSERT INTO `playinfo` VALUES (18, 'GH19890602600002', 1, '2019-07-09 00:00:00', '2019-07-09 02:00:00', 218.00);
INSERT INTO `playinfo` VALUES (19, 'GH19890602600002', 1, '2019-07-09 03:00:00', '2019-07-09 05:00:00', 218.00);
INSERT INTO `playinfo` VALUES (20, 'GH19890602600002', 1, '2019-07-09 06:00:00', '2019-07-09 08:00:00', 218.00);
INSERT INTO `playinfo` VALUES (21, 'GH19890602600002', 1, '2019-07-09 09:00:00', '2019-07-09 11:00:00', 218.00);
INSERT INTO `playinfo` VALUES (22, 'GH19890602600002', 1, '2019-07-09 13:00:00', '2019-07-09 15:00:00', 218.00);
INSERT INTO `playinfo` VALUES (23, 'GH19890602600002', 1, '2019-07-09 16:00:00', '2019-07-09 18:00:00', 218.00);
INSERT INTO `playinfo` VALUES (24, 'GH19890602600002', 1, '2019-07-09 19:00:00', '2019-07-09 21:00:00', 218.00);
INSERT INTO `playinfo` VALUES (25, 'GH19890602600002', 1, '2019-07-09 22:00:00', '2019-07-10 00:00:00', 218.00);
COMMIT;

-- ----------------------------
-- Table structure for ticketinfo
-- ----------------------------
DROP TABLE IF EXISTS `ticketinfo`;
CREATE TABLE `ticketinfo` (
  `seatID` varchar(8) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `playID` int NOT NULL,
  `memberID` int NOT NULL,
  `finalPrice` decimal(6,2) DEFAULT NULL,
  `grade` decimal(3,1) NOT NULL DEFAULT '8.0',
  PRIMARY KEY (`seatID`,`playID`),
  KEY `playID` (`playID`),
  KEY `memberID` (`memberID`),
  CONSTRAINT `ticketinfo_ibfk_1` FOREIGN KEY (`playID`) REFERENCES `playinfo` (`playID`),
  CONSTRAINT `ticketinfo_ibfk_2` FOREIGN KEY (`memberID`) REFERENCES `memberinfo` (`memberID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of ticketinfo
-- ----------------------------
BEGIN;
INSERT INTO `ticketinfo` VALUES ('01-02', 5, 1, 35.00, 8.0);
INSERT INTO `ticketinfo` VALUES ('03-28', 4, 1, 34.00, 8.0);
INSERT INTO `ticketinfo` VALUES ('04-13', 1, 1, 40.00, 8.0);
INSERT INTO `ticketinfo` VALUES ('05-05', 3, 1, 99.00, 8.0);
INSERT INTO `ticketinfo` VALUES ('06-14', 2, 1, 40.00, 8.0);
INSERT INTO `ticketinfo` VALUES ('06-15', 12, 1, 89.00, 8.0);
INSERT INTO `ticketinfo` VALUES ('06-16', 12, 2, 124.60, 8.0);
INSERT INTO `ticketinfo` VALUES ('06-17', 12, 3, 160.20, 8.0);
INSERT INTO `ticketinfo` VALUES ('06-18', 12, 4, 178.00, 8.0);
INSERT INTO `ticketinfo` VALUES ('06-19', 12, 7, 160.20, 8.0);
INSERT INTO `ticketinfo` VALUES ('07-15', 7, 1, 84.00, 8.0);
INSERT INTO `ticketinfo` VALUES ('07-16', 7, 6, 117.60, 8.0);
INSERT INTO `ticketinfo` VALUES ('07-17', 7, 8, 168.00, 8.0);
INSERT INTO `ticketinfo` VALUES ('07-18', 7, 12, 168.00, 8.0);
INSERT INTO `ticketinfo` VALUES ('08-10', 18, 1, 109.00, 8.0);
INSERT INTO `ticketinfo` VALUES ('08-11', 18, 11, 196.20, 8.0);
INSERT INTO `ticketinfo` VALUES ('08-12', 18, 10, 152.60, 8.0);
INSERT INTO `ticketinfo` VALUES ('08-13', 18, 9, 109.00, 8.0);
INSERT INTO `ticketinfo` VALUES ('08-14', 18, 8, 218.00, 8.0);
INSERT INTO `ticketinfo` VALUES ('08-15', 18, 7, 196.20, 8.0);
INSERT INTO `ticketinfo` VALUES ('08-18', 6, 1, 22.50, 8.0);
COMMIT;

-- ----------------------------
-- View structure for member_ticket
-- ----------------------------
DROP VIEW IF EXISTS `member_ticket`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `member_ticket` AS select `memberinfo`.`memberID` AS `memberID`,`memberinfo`.`memberName` AS `memberName`,`cinema_hallinfo`.`hallName` AS `hallName`,`cinema_hallinfo`.`address` AS `address`,`filminfo`.`filmName` AS `filmName`,`ticketinfo`.`seatID` AS `seatID`,`ticketinfo`.`finalPrice` AS `finalPrice` from ((((`memberinfo` join `cinema_hallinfo`) join `filminfo`) join `ticketinfo`) join `playinfo`) where ((`ticketinfo`.`memberID` = `memberinfo`.`memberID`) and (`ticketinfo`.`playID` = `playinfo`.`playID`) and (`playinfo`.`cinema_hallID` = `cinema_hallinfo`.`cinema_hallID`) and (`playinfo`.`filmID` = `filminfo`.`filmID`));

-- ----------------------------
-- Triggers structure for table ticketinfo
-- ----------------------------
DROP TRIGGER IF EXISTS `t_insert_ticketinfo`;
delimiter ;;
CREATE TRIGGER `t_insert_ticketinfo` BEFORE INSERT ON `ticketinfo` FOR EACH ROW BEGIN
	DECLARE member_discount DECIMAL(2,1);
	DECLARE current_price DECIMAL(6,2);

	SELECT discount INTO member_discount
	FROM memberinfo
	WHERE memberinfo.memberID=NEW.memberID;

	SELECT price INTO current_price
	FROM playinfo
	WHERE playinfo.playID=NEW.playID;

	SET NEW.finalPrice=current_price*member_discount;
END
;;
delimiter ;

-- ----------------------------
-- Triggers structure for table ticketinfo
-- ----------------------------
DROP TRIGGER IF EXISTS `t_update_ticketinfo`;
delimiter ;;
CREATE TRIGGER `t_update_ticketinfo` AFTER UPDATE ON `ticketinfo` FOR EACH ROW BEGIN
	DECLARE grade_filmID CHAR(16);
	DECLARE grade DECIMAL(3,1);

	SELECT filmID INTO grade_filmID
	FROM playinfo
	WHERE playinfo.playID=NEW.playID;
	
	SELECT CAST(AVG(ticketinfo.grade) AS DECIMAL(3,1)) INTO grade
	FROM ticketinfo, playinfo
	WHERE ticketinfo.playID=playinfo.playID AND playinfo.filmID=grade_filmID;

	UPDATE filminfo
	SET filmGrade=grade
	WHERE filminfo.filmID=grade_filmID;
END
;;
delimiter ;

SET FOREIGN_KEY_CHECKS = 1;
