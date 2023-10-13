-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema UBERblood
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema UBERblood
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `UBERblood` DEFAULT CHARACTER SET utf8 ;
USE `UBERblood` ;

-- -----------------------------------------------------
-- Table `UBERblood`.`Sangue`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `UBERblood`.`Sangue` (
  `id` INT NOT NULL,
  `tipo` VARCHAR(3) NOT NULL,
  `qtd_sangue` DECIMAL(5,2) NOT NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `UBERblood`.`Morada`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `UBERblood`.`Morada` (
  `cod_postal` VARCHAR(8) NOT NULL,
  `rua` VARCHAR(100) NOT NULL,
  `localidade` VARCHAR(100) NOT NULL,
  `concelho` VARCHAR(100) NOT NULL,
  PRIMARY KEY (`cod_postal`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `UBERblood`.`Doador`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `UBERblood`.`Doador` (
  `n_cc` VARCHAR(13) NOT NULL,
  `nome` VARCHAR(100) NOT NULL,
  `genero` CHAR(1) NOT NULL,
  `d_nasc` DATE NOT NULL,
  `qtd_sangue` DECIMAL(5,2) NULL,
  `tipo_sangue` INT NOT NULL,
  `morada` VARCHAR(8) NOT NULL,
  PRIMARY KEY (`n_cc`),
  INDEX `fk01_tipo_sangue_idx` (`tipo_sangue` ASC) VISIBLE,
  INDEX `fk02_morada_idx` (`morada` ASC) VISIBLE,
  CONSTRAINT `fk01_tipo_sangue`
    FOREIGN KEY (`tipo_sangue`)
    REFERENCES `UBERblood`.`Sangue` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk02_morada`
    FOREIGN KEY (`morada`)
    REFERENCES `UBERblood`.`Morada` (`cod_postal`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `UBERblood`.`Funcionario`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `UBERblood`.`Funcionario` (
  `n_cc` VARCHAR(13) NOT NULL,
  `nome` VARCHAR(100) NOT NULL,
  `funcao` VARCHAR(45) NOT NULL COMMENT '\'R\' ou \'E\' conforme for funcionario regular ou enfermeiro',
  `morada` VARCHAR(8) NOT NULL,
  PRIMARY KEY (`n_cc`),
  INDEX `fk01_morada_idx` (`morada` ASC) VISIBLE,
  CONSTRAINT `fk01_morada`
    FOREIGN KEY (`morada`)
    REFERENCES `UBERblood`.`Morada` (`cod_postal`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `UBERblood`.`Doacao`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `UBERblood`.`Doacao` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `qtd_sangue` DECIMAL(3,2) NOT NULL,
  `data` DATE NOT NULL,
  `numero_consultorio` INT NOT NULL,
  `estado` VARCHAR(50) NOT NULL COMMENT 'Para marcar se a doaçao esta por realizar ou ja foi realizada\n',
  `id_doador` VARCHAR(13) NOT NULL,
  `id_enf` VARCHAR(13) NOT NULL,
  `tipo_sangue` INT NOT NULL,
  PRIMARY KEY (`id`),
  INDEX `fk01_id_doador_idx` (`id_doador` ASC) VISIBLE,
  INDEX `fk02_id_enf_idx` (`id_enf` ASC) VISIBLE,
  INDEX `fk03_tipo_sangue_idx` (`tipo_sangue` ASC) VISIBLE,
  CONSTRAINT `fk01_id_doador`
    FOREIGN KEY (`id_doador`)
    REFERENCES `UBERblood`.`Doador` (`n_cc`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk02_id_enf`
    FOREIGN KEY (`id_enf`)
    REFERENCES `UBERblood`.`Funcionario` (`n_cc`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk03_tipo_sangue`
    FOREIGN KEY (`tipo_sangue`)
    REFERENCES `UBERblood`.`Sangue` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `UBERblood`.`UnidadeSaude`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `UBERblood`.`UnidadeSaude` (
  `id` INT NOT NULL,
  `nome` VARCHAR(100) NOT NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `UBERblood`.`Entrega`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `UBERblood`.`Entrega` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `qtd_sangue` DECIMAL(5,2) NOT NULL,
  `id_US` INT NOT NULL,
  `id_func` VARCHAR(13) NOT NULL,
  PRIMARY KEY (`id`),
  INDEX `fk01_id_US_idx` (`id_US` ASC) VISIBLE,
  INDEX `fk02_id_fun_idx` (`id_func` ASC) VISIBLE,
  CONSTRAINT `fk01_id_US`
    FOREIGN KEY (`id_US`)
    REFERENCES `UBERblood`.`UnidadeSaude` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk02_id_fun`
    FOREIGN KEY (`id_func`)
    REFERENCES `UBERblood`.`Funcionario` (`n_cc`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `UBERblood`.`Sangue_Entrega`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `UBERblood`.`Sangue_Entrega` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `id_sangue` INT NOT NULL,
  `id_entrega` INT NOT NULL,
  `data` DATE NOT NULL,
  INDEX `fk02_id_entrega_idx` (`id_entrega` ASC) VISIBLE,
  PRIMARY KEY (`id`),
  CONSTRAINT `fk01_id_sangue`
    FOREIGN KEY (`id_sangue`)
    REFERENCES `UBERblood`.`Sangue` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk02_id_entrega`
    FOREIGN KEY (`id_entrega`)
    REFERENCES `UBERblood`.`Entrega` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `UBERblood`.`Contacto_Doador`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `UBERblood`.`Contacto_Doador` (
  `telemovel` VARCHAR(15) NOT NULL,
  `email` VARCHAR(50) NULL,
  `id_doador` VARCHAR(13) NOT NULL,
  PRIMARY KEY (`telemovel`),
  INDEX `fk01_id_doador_contact_idx` (`id_doador` ASC) VISIBLE,
  CONSTRAINT `fk01_id_doador_contact`
    FOREIGN KEY (`id_doador`)
    REFERENCES `UBERblood`.`Doador` (`n_cc`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `UBERblood`.`Contacto_Funcionario`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `UBERblood`.`Contacto_Funcionario` (
  `telemovel` VARCHAR(15) NOT NULL,
  `email` VARCHAR(50) NOT NULL,
  `id_funcionario` VARCHAR(13) NOT NULL,
  PRIMARY KEY (`telemovel`),
  INDEX `fk01_id_funcionario_idx` (`id_funcionario` ASC) VISIBLE,
  CONSTRAINT `fk01_id_funcionario`
    FOREIGN KEY (`id_funcionario`)
    REFERENCES `UBERblood`.`Funcionario` (`n_cc`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
