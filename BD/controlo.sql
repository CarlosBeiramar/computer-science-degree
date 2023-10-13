
CREATE USER 'Frederico Bettencourt'@'localhost' IDENTIFIED BY '00000';
GRANT ALL ON UBERblood TO 'Frederico Bettencourt'@'localhost';

CREATE USER 'Regular'@'localhost' IDENTIFIED BY '00001';
GRANT SELECT, UPDATE, INSERT ON UBERblood.Doador TO 'Regular'@'localhost';
GRANT SELECT, INSERT ON UBERblood.Doacao TO 'Regular'@'localhost';
GRANT SELECT, INSERT ON UBERblood.Entrega TO 'Regular'@'localhost';

CREATE USER 'Enfermeiro'@'localhost' IDENTIFIED BY '00002';
GRANT SELECT, UPDATE ON UBERblood.Doacao TO 'Enfermeiro'@'localhost';
GRANT SELECT, UPDATE ON UBERblood.Doador TO 'Enfermeiro'@'localhost';
GRANT SELECT, UPDATE ON UBERblood.Sangue TO 'Enfermeiro'@'localhost';