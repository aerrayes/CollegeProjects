
CREATE DATABASE IF NOT EXISTS `keywordurl`;


CREATE TABLE IF NOT EXISTS `link` (
	`urlid` int(11) NOT NULL AUTO_INCREMENT,
	`url` varchar(100) COLLATE utf8_unicode_ci NOT NULL,
	`hashcode` int(11) NOT NULL,
	PRIMARY KEY(`urlid`),
  CONSTRAINT url_const UNIQUE (`url`)
);

CREATE TABLE IF NOT EXISTS `keyword` (
	`keywordid` int(11) NOT NULL AUTO_INCREMENT,
	`keyword` varchar(100) COLLATE utf8_unicode_ci DEFAULT NULL,
	PRIMARY KEY(`keywordid`),
  CONSTRAINT keyword_const UNIQUE (`keyword`)
);

CREATE TABLE IF NOT EXISTS `keyword_url` (
  `serial` int(11) NOT NULL AUTO_INCREMENT,
  `keywordid` int(11) NOT NULL,
  `urlid` int(11) NOT NULL,
  `prioirty` int(1) NOT NULL,
  `index` int(11) NOT NULL,
  PRIMARY KEY (`serial`),
  KEY `link` (`urlid`),
  KEY `keyword` (`keywordid`),
  CONSTRAINT key_url UNIQUE (keywordid,urlid,`index`)
);



