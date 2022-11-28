CREATE DATABASE  IF NOT EXISTS `banksimu` /*!40100 DEFAULT CHARACTER SET utf8mb3 */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `banksimu`;
-- MySQL dump 10.13  Distrib 8.0.30, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: banksimu
-- ------------------------------------------------------
-- Server version	8.0.29

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `bank_account`
--

DROP TABLE IF EXISTS `bank_account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `bank_account` (
  `idbank_account` int NOT NULL AUTO_INCREMENT,
  `balance` double DEFAULT NULL,
  `user_iduser` int NOT NULL,
  `credit_limit` double DEFAULT NULL,
  PRIMARY KEY (`idbank_account`),
  KEY `fk_bank_account_user1_idx` (`user_iduser`),
  CONSTRAINT `fk_bank_account_user1` FOREIGN KEY (`user_iduser`) REFERENCES `user` (`iduser`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bank_account`
--

LOCK TABLES `bank_account` WRITE;
/*!40000 ALTER TABLE `bank_account` DISABLE KEYS */;
/*!40000 ALTER TABLE `bank_account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `bank_account_bank_card`
--

DROP TABLE IF EXISTS `bank_account_bank_card`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `bank_account_bank_card` (
  `idbank_account_bank_card` int NOT NULL,
  `bank_account_idbank_account` int NOT NULL,
  `bank_card_idbank_card` int NOT NULL,
  PRIMARY KEY (`idbank_account_bank_card`),
  KEY `fk_bank_account_bank_card_bank_account1_idx` (`bank_account_idbank_account`),
  KEY `fk_bank_account_bank_card_bank_card1_idx` (`bank_card_idbank_card`),
  CONSTRAINT `fk_bank_account_bank_card_bank_account1` FOREIGN KEY (`bank_account_idbank_account`) REFERENCES `bank_account` (`idbank_account`),
  CONSTRAINT `fk_bank_account_bank_card_bank_card1` FOREIGN KEY (`bank_card_idbank_card`) REFERENCES `bank_card` (`idbank_card`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bank_account_bank_card`
--

LOCK TABLES `bank_account_bank_card` WRITE;
/*!40000 ALTER TABLE `bank_account_bank_card` DISABLE KEYS */;
/*!40000 ALTER TABLE `bank_account_bank_card` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `bank_card`
--

DROP TABLE IF EXISTS `bank_card`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `bank_card` (
  `idbank_card` int NOT NULL AUTO_INCREMENT,
  `card_number` varchar(45) DEFAULT NULL,
  `pin_code` varchar(255) DEFAULT NULL,
  `user_iduser` int NOT NULL,
  `type` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idbank_card`),
  UNIQUE KEY `card_number_UNIQUE` (`card_number`),
  KEY `fk_bank_card_user1_idx` (`user_iduser`),
  CONSTRAINT `fk_bank_card_user1` FOREIGN KEY (`user_iduser`) REFERENCES `user` (`iduser`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bank_card`
--

LOCK TABLES `bank_card` WRITE;
/*!40000 ALTER TABLE `bank_card` DISABLE KEYS */;
INSERT INTO `bank_card` VALUES (1,'4209 5489 1327 4944','$2a$10$tJ/0sTPDmk7pGgbdGtC.auZz4efSHVQqIr0n0fzEffyiudmSkIpBW',1,'Debit'),(3,'4209 5489 1327 4945','$2a$10$O4E8JYq.4Al/bduwtFNFMOtnPxHKpyoP/qDFVkcWD9t1QCcf4HXPG',11,'Debit');
/*!40000 ALTER TABLE `bank_card` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transactions`
--

DROP TABLE IF EXISTS `transactions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `transactions` (
  `idtransactions` int NOT NULL AUTO_INCREMENT,
  `amount` varchar(45) DEFAULT NULL,
  `bank_account_idbank_account` int NOT NULL,
  `type` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idtransactions`),
  KEY `fk_transactions_bank_account1_idx` (`bank_account_idbank_account`),
  CONSTRAINT `fk_transactions_bank_account1` FOREIGN KEY (`bank_account_idbank_account`) REFERENCES `bank_account` (`idbank_account`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transactions`
--

LOCK TABLES `transactions` WRITE;
/*!40000 ALTER TABLE `transactions` DISABLE KEYS */;
/*!40000 ALTER TABLE `transactions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `user` (
  `iduser` int NOT NULL AUTO_INCREMENT,
  `first_name` varchar(45) DEFAULT NULL,
  `last_name` varchar(45) DEFAULT NULL,
  `address` varchar(45) DEFAULT NULL,
  `email` varchar(45) DEFAULT NULL,
  `phone_number` char(15) DEFAULT NULL,
  PRIMARY KEY (`iduser`),
  UNIQUE KEY `email_UNIQUE` (`email`),
  UNIQUE KEY `phone_number_UNIQUE` (`phone_number`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` VALUES (1,'Pertti','Erareika','Kuukkelikuja 5','p.erareika@ss.fi','00440068'),(3,'Silja','Sihisi','Siilikuja 5','siili@ss.f','06001231'),(4,'Pertti','Erareika','Kuukkelikuja 5','p.erareika@ss.com','00440069'),(8,'Pertti','Erareika','Kuukkelikuja 5','p.erareika@sss.fi','004400600'),(9,'Silja','Sihisi','Siilikuja 5','siili@sss.fi','0600123123'),(11,'Seppo','Taalasmaa','Pihlajanoja 0','suppo@gmail.com','0100100');
/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-11-27 14:48:37
