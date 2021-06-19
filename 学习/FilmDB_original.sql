/*
Navicat MySQL Data Transfer

Source Server         : MySQL
Source Server Version : 50643
Source Host           : localhost:3306
Source Database       : filmdb

Target Server Type    : MYSQL
Target Server Version : 50643
File Encoding         : 65001

Date: 2019-05-29 13:23:18
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `cinema_hallinfo`
-- ----------------------------
DROP TABLE IF EXISTS `cinema_hallinfo`;
CREATE TABLE `cinema_hallinfo` (
  `cinema_hallID` int(11) DEFAULT NULL,
  `address` varchar(20) DEFAULT NULL,
  `hallName` varchar(20) DEFAULT NULL,
  `capacity` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of cinema_hallinfo
-- ----------------------------
INSERT INTO `cinema_hallinfo` VALUES ('1', '杨浦店', 'A', '100');
INSERT INTO `cinema_hallinfo` VALUES ('2', '杨浦店', 'B', '80');
INSERT INTO `cinema_hallinfo` VALUES ('3', '杨浦店', 'C', '50');
INSERT INTO `cinema_hallinfo` VALUES ('4', '长宁店', 'A', '100');
INSERT INTO `cinema_hallinfo` VALUES ('5', '长宁店', 'B', '80');
INSERT INTO `cinema_hallinfo` VALUES ('6', '长宁店', 'C', '50');
INSERT INTO `cinema_hallinfo` VALUES ('7', '闵行店', 'A', '100');
INSERT INTO `cinema_hallinfo` VALUES ('8', '闵行店', 'B', '80');

-- ----------------------------
-- Table structure for `filminfo`
-- ----------------------------
DROP TABLE IF EXISTS `filminfo`;
CREATE TABLE `filminfo` (
  `filmID` char(16) DEFAULT NULL,
  `filmName` varchar(50) DEFAULT NULL,
  `typeID` char(2) DEFAULT NULL,
  `actor` varchar(255) DEFAULT NULL,
  `director` varchar(50) DEFAULT NULL,
  `filmGrade` decimal(3,1) DEFAULT NULL,
  KEY `fk_FilmInfo_FilmType` (`typeID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of filminfo
-- ----------------------------
INSERT INTO `filminfo` VALUES ('GH19540107900001', '百万英镑', 'XJ', '格里高利·派克，乔伊斯·格伦菲尔等', '罗纳德·尼姆', '8.0');
INSERT INTO `filminfo` VALUES ('GH19890602600002', '死亡诗社', 'QT', '罗宾·威廉姆斯，伊桑·霍克等', '彼得·威尔', '8.0');
INSERT INTO `filminfo` VALUES ('GH19940914600001', '这个杀手不太冷', 'GF', '让·雷诺，加里·奥德曼，娜塔莉·波特曼等', '吕克·贝松', '8.0');
INSERT INTO `filminfo` VALUES ('GH20070518300005', '唐伯虎点秋香', 'XJ', '周星驰，巩俐等', '李力持', '8.0');
INSERT INTO `filminfo` VALUES ('GH20080318300005', '猫和老鼠', 'DH', '', '威廉·汉纳及约瑟夫·巴', '8.0');
INSERT INTO `filminfo` VALUES ('GH20080618400001', '倚天屠龙记', 'GF', '李连杰,邱淑贞', '王晶', '8.0');
INSERT INTO `filminfo` VALUES ('GH20190510500001', '大侦探皮卡丘', 'DH', null, '罗伯·莱特曼', '8.0');
INSERT INTO `filminfo` VALUES ('GH20190524800001', '五月天人生无限公司', 'QT', '温商翊，石锦航，蔡升晏等', '陈奕仁', '8.0');
INSERT INTO `filminfo` VALUES ('GH20190524800002', '龙珠超：布罗利', 'DH', null, '长峰达也', '8.0');

-- ----------------------------
-- Table structure for `filmtype`
-- ----------------------------
DROP TABLE IF EXISTS `filmtype`;
CREATE TABLE `filmtype` (
  `typeID` char(2) DEFAULT NULL,
  `typeName` varchar(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of filmtype
-- ----------------------------
INSERT INTO `filmtype` VALUES ('AQ', '爱情片');
INSERT INTO `filmtype` VALUES ('DH', '动画片');
INSERT INTO `filmtype` VALUES ('GF', '功夫片');
INSERT INTO `filmtype` VALUES ('QT', '其他');
INSERT INTO `filmtype` VALUES ('XJ', '喜剧片');
INSERT INTO `filmtype` VALUES ('ZZ', '战争片');

-- ----------------------------
-- Table structure for `memberinfo`
-- ----------------------------
DROP TABLE IF EXISTS `memberinfo`;
CREATE TABLE `memberinfo` (
  `memberID` int(11) DEFAULT NULL,
  `memberName` varchar(20) DEFAULT NULL,
  `memberShip` char(2) DEFAULT NULL,
  `discount` decimal(2,1) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of memberinfo
-- ----------------------------
INSERT INTO `memberinfo` VALUES ('1', '赵一', 'A', '0.5');
INSERT INTO `memberinfo` VALUES ('2', '赵二', 'B', '0.7');
INSERT INTO `memberinfo` VALUES ('3', '赵三', 'C', '0.9');
INSERT INTO `memberinfo` VALUES ('4', '赵四', 'D', '1.0');
INSERT INTO `memberinfo` VALUES ('5', '钱一', 'A', '0.5');
INSERT INTO `memberinfo` VALUES ('6', '钱二', 'B', '0.7');
INSERT INTO `memberinfo` VALUES ('7', '钱三', 'C', '0.9');
INSERT INTO `memberinfo` VALUES ('8', '钱四', 'D', '1.0');
INSERT INTO `memberinfo` VALUES ('9', '孙一', 'A', '0.5');
INSERT INTO `memberinfo` VALUES ('10', '孙二', 'B', '0.7');
INSERT INTO `memberinfo` VALUES ('11', '孙三', 'C', '0.9');
INSERT INTO `memberinfo` VALUES ('12', '孙四', 'D', '1.0');

-- ----------------------------
-- Table structure for `playinfo`
-- ----------------------------
DROP TABLE IF EXISTS `playinfo`;
CREATE TABLE `playinfo` (
  `playID` int(11) DEFAULT NULL,
  `filmID` char(16) DEFAULT NULL,
  `cinema_hallID` int(11) DEFAULT NULL,
  `startTime` datetime DEFAULT NULL,
  `endTime` datetime DEFAULT NULL,
  `price` decimal(6,2) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of playinfo
-- ----------------------------
INSERT INTO `playinfo` VALUES ('1', 'GH20070518300005', '4', '2007-05-18 09:00:00', '2007-05-18 11:00:00', '80.00');
INSERT INTO `playinfo` VALUES ('2', 'GH20080318300005', '5', '2008-03-18 15:00:00', '2008-03-18 17:00:00', '80.00');
INSERT INTO `playinfo` VALUES ('3', 'GH20080618400001', '6', '2008-06-18 19:00:00', '2008-06-18 21:00:00', '198.00');
INSERT INTO `playinfo` VALUES ('4', 'GH20190510500001', '7', '2019-05-10 00:00:00', '2019-05-10 02:00:00', '68.00');
INSERT INTO `playinfo` VALUES ('5', 'GH20190524800001', '7', '2019-05-24 08:00:00', '2019-05-24 10:00:00', '70.00');
INSERT INTO `playinfo` VALUES ('6', 'GH20190524800002', '7', '2019-05-24 08:00:00', '2019-05-24 10:00:00', '45.00');
INSERT INTO `playinfo` VALUES ('7', 'GH19540107900001', '2', '2019-06-06 08:00:00', '2019-06-06 10:00:00', '168.00');
INSERT INTO `playinfo` VALUES ('8', 'GH19540107900001', '2', '2019-06-06 11:00:00', '2019-06-06 13:00:00', '168.00');
INSERT INTO `playinfo` VALUES ('9', 'GH19540107900001', '2', '2019-06-06 14:00:00', '2019-06-06 16:00:00', '168.00');
INSERT INTO `playinfo` VALUES ('10', 'GH19540107900001', '2', '2019-06-06 17:00:00', '2019-06-06 19:00:00', '168.00');
INSERT INTO `playinfo` VALUES ('11', 'GH19540107900001', '2', '2019-06-06 20:00:00', '2019-06-06 22:00:00', '168.00');
INSERT INTO `playinfo` VALUES ('12', 'GH19940914600001', '3', '2019-03-15 08:00:00', '2019-03-15 10:00:00', '178.00');
INSERT INTO `playinfo` VALUES ('13', 'GH19940914600001', '3', '2019-03-15 11:00:00', '2019-03-15 13:00:00', '178.00');
INSERT INTO `playinfo` VALUES ('14', 'GH19940914600001', '3', '2019-03-15 14:00:00', '2019-03-15 16:00:00', '178.00');
INSERT INTO `playinfo` VALUES ('15', 'GH19940914600001', '3', '2019-03-15 17:00:00', '2019-03-15 19:00:00', '178.00');
INSERT INTO `playinfo` VALUES ('16', 'GH19940914600001', '3', '2019-03-15 20:00:00', '2019-03-15 22:00:00', '178.00');
INSERT INTO `playinfo` VALUES ('17', 'GH19940914600001', '3', '2019-03-15 23:00:00', '2019-03-16 01:00:00', '178.00');
INSERT INTO `playinfo` VALUES ('18', 'GH19890602600002', '1', '2019-07-09 00:00:00', '2019-07-09 02:00:00', '218.00');
INSERT INTO `playinfo` VALUES ('19', 'GH19890602600002', '1', '2019-07-09 03:00:00', '2019-07-09 05:00:00', '218.00');
INSERT INTO `playinfo` VALUES ('20', 'GH19890602600002', '1', '2019-07-09 06:00:00', '2019-07-09 08:00:00', '218.00');
INSERT INTO `playinfo` VALUES ('21', 'GH19890602600002', '1', '2019-07-09 09:00:00', '2019-07-09 11:00:00', '218.00');
INSERT INTO `playinfo` VALUES ('22', 'GH19890602600002', '1', '2019-07-09 13:00:00', '2019-07-09 15:00:00', '218.00');
INSERT INTO `playinfo` VALUES ('23', 'GH19890602600002', '1', '2019-07-09 16:00:00', '2019-07-09 18:00:00', '218.00');
INSERT INTO `playinfo` VALUES ('24', 'GH19890602600002', '1', '2019-07-09 19:00:00', '2019-07-09 21:00:00', '218.00');
INSERT INTO `playinfo` VALUES ('25', 'GH19890602600002', '1', '2019-07-09 22:00:00', '2019-07-10 00:00:00', '218.00');

-- ----------------------------
-- Table structure for `ticketinfo`
-- ----------------------------
DROP TABLE IF EXISTS `ticketinfo`;
CREATE TABLE `ticketinfo` (
  `seatID` varchar(8) DEFAULT NULL,
  `playID` int(11) DEFAULT NULL,
  `memberID` int(11) DEFAULT NULL,
  `finalPrice` decimal(6,2) DEFAULT NULL,
  `grade` decimal(3,1) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of ticketinfo
-- ----------------------------
INSERT INTO `ticketinfo` VALUES ('01-02', '5', '1', '35.00', '8.0');
INSERT INTO `ticketinfo` VALUES ('03-28', '4', '1', '34.00', '8.0');
INSERT INTO `ticketinfo` VALUES ('04-13', '1', '1', '40.00', '8.0');
INSERT INTO `ticketinfo` VALUES ('05-05', '3', '1', '99.00', '8.0');
INSERT INTO `ticketinfo` VALUES ('06-14', '2', '1', '40.00', '8.0');
INSERT INTO `ticketinfo` VALUES ('06-15', '12', '1', '89.00', '8.0');
INSERT INTO `ticketinfo` VALUES ('06-16', '12', '2', '124.60', '8.0');
INSERT INTO `ticketinfo` VALUES ('06-17', '12', '3', '160.20', '8.0');
INSERT INTO `ticketinfo` VALUES ('06-18', '12', '4', '178.00', '8.0');
INSERT INTO `ticketinfo` VALUES ('06-19', '12', '7', '160.20', '8.0');
INSERT INTO `ticketinfo` VALUES ('07-15', '7', '1', '84.00', '8.0');
INSERT INTO `ticketinfo` VALUES ('07-16', '7', '6', '117.60', '8.0');
INSERT INTO `ticketinfo` VALUES ('07-17', '7', '8', '168.00', '8.0');
INSERT INTO `ticketinfo` VALUES ('07-18', '7', '12', '168.00', '8.0');
INSERT INTO `ticketinfo` VALUES ('08-10', '18', '1', '109.00', '8.0');
INSERT INTO `ticketinfo` VALUES ('08-11', '18', '11', '196.20', '8.0');
INSERT INTO `ticketinfo` VALUES ('08-12', '18', '10', '152.60', '8.0');
INSERT INTO `ticketinfo` VALUES ('08-13', '18', '9', '109.00', '8.0');
INSERT INTO `ticketinfo` VALUES ('08-14', '18', '8', '218.00', '8.0');
INSERT INTO `ticketinfo` VALUES ('08-15', '18', '7', '196.20', '8.0');
INSERT INTO `ticketinfo` VALUES ('08-18', '6', '1', '22.50', '8.0');
