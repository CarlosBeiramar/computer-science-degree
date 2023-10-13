USE UBERblood;

-- Inserção de Moradas
INSERT INTO `UBERblood`.`Morada` 
	(cod_postal, rua, localidade, concelho) 
	VALUES 
		('4710-321','Rua Santa Margarida','Braga','Braga'),
		('4810-122','Rua António Marcelino','Barcelos','Barcelos'),
		('4755-213','Rua David Barbosa','Macieira de Rates','Barcelos'),
		('4990-685','Rua S. João Baptista da Queijada','Ponte de Lima','Viana do Castelo'),
		('4710-412','Rua Padre António Vieira','Braga','Braga'),
		('4710-562','Rua da Agrela','Adaúfe','Braga'),
		('4700-207', 'Rua do Caires', 'Braga', 'Braga'),
		('8000-355','Rua Dr. Cândido Guerreiro','Faro','Faro'),
		('8125-507', 'Avenida Cerro da Vila', 'Quarteira', 'Quarteira'),
		('5000-554', 'Rua Santo António', 'Vila Real', 'Vila Real');
    
-- SELECT * FROM Morada;

-- Inserção de funcionários
INSERT INTO `UBERblood`.`Funcionario` 
	(n_cc,nome,funcao,morada) 
	VALUES 
		('43240000', 'Frederico Bettencourt', 'A', '8000-355'),
		('12343245','Bruna Araújo', 'R','4990-685'),
		('12354243','Daniel Ferreira', 'R','4755-213'),
		('78354298','Ricardo Cruz', 'E','4710-562'),
		('90854563','Carlos Beiramar', 'E','4710-412'),
		('12362173','Manuel António', 'E','4710-321');
        
-- SELECT * FROM Funcionario;

-- Querie para testar a junção de tabelas Funcionario e Morada
-- SELECT nome, funcao, cod_postal AS CodigoPostal, rua, localidade, concelho  
-- FROM Funcionario AS F INNER JOIN Morada AS M
-- ON F.morada = M.cod_postal;

-- Inserção de Contactos de Funcionario
INSERT INTO `UBERblood`.`Contacto_Funcionario`
	(telemovel,email,id_funcionario)
    	VALUES
		('914563249', 'frediBett@gmail.com', '43240000'),
		('961233244', 'baraujo@hotmail.com', '12343245'),
		('935435439', 'danielferreira28@gmail.com', '12354243'),
		('969754837', 'ricardocruz06@gmail.com', '78354298'),
		('911273683', 'carlitosBeiramar@hotmail.com', '90854563'),
		('911155443', 'manelAntonio@gmail.com', '12362173');

-- Inserção de tipos de sangue
INSERT INTO `UBERblood`.`Sangue`
	(id, tipo, qtd_sangue)
    	VALUES
		(1, 'A+',0),
		(2, 'A-',0),
		(3, 'B+',0),
		(4, 'B-',0),
		(5, 'AB+',1.35),
		(6, 'AB-',0),
		(7, 'O+',1.35),
		(8, 'O-',0.45);
        
-- Inserção de doadores
INSERT INTO `UBERblood`.`Doador` 
	(n_cc, nome, genero, d_nasc, qtd_sangue, tipo_sangue, morada)
    	VALUES
		('12321312', 'Justino Manuel', 'M', '1997-01-06', NULL, 1, '5000-554'),
		('73642237', 'Maria Antónia', 'F', '1980-08-17', 0.9, 8, '4710-321'),
		('83423473', 'Heródoto', 'M', '1960-11-23', '1.8', 5, '4810-122'),
		('73467328', 'Diego Maradona', 'M', '1980-11-15', NULL, 4, '4700-207'),
		('23498789', 'Elisabete Faria', 'F', '1975-01-12', 4.05, 7, '8125-507');
        
-- Inserção de contacto doadores
INSERT INTO `UBERblood`.`Contacto_Doador`
	(telemovel, email, id_doador)
    	VALUES
		('961231231', 'justinomanuel@gmail.com', '12321312'),
		('913243234', 'mantonia@hotmail.com', '73642237'),
		('969837828', NULL, '83423473'),
		('932382424', NULL, '73467328'),
		('934789324', 'elifaria@gmail.com', '23498789');

        
-- Inserção de Unidades de Saúde
INSERT INTO `UBERblood`.`UnidadeSaude`
	(id, nome)
   	VALUES
		(1, "Hospital de Braga"),
		(2, "Hospital da Luz"),
		(3, "Hospital Santa Maria da Roménia");

-- Inserção de doações
INSERT INTO `UBERblood`.`Doacao` 
	(qtd_sangue, data, numero_consultorio, estado, id_doador, id_enf, tipo_sangue)
	VALUES
	    (0.45, '2018-01-05', 2, 'Realizado', '23498789', '78354298', 7),
            (0.45, '2018-04-19', 2, 'Realizado', '23498789', '90854563', 7),
            (0.45, '2018-07-20', 2, 'Realizado', '23498789', '78354298', 7),
            (0.45, '2018-10-24', 2, 'Realizado', '23498789', '12362173', 7),
            (0.45, '2019-01-05', 2, 'Realizado', '23498789', '90854563', 7),
            (0.45, '2019-04-19', 2, 'Realizado', '23498789', '12362173', 7),
            (0.45, '2019-07-20', 2, 'Realizado', '23498789', '78354298', 7),
            (0.45, '2019-10-24', 2, 'Realizado', '23498789', '90854563', 7),
            (0.45, '2019-11-18', 2, 'Realizado', '83423473', '78354298', 5),
            (0.45, '2020-01-05', 2, 'Realizado', '23498789', '78354298', 7),
            (0.45, '2020-01-26', 1, 'Realizado', '83423473', '90854563', 5),
            (0.45, '2020-04-20', 2, 'Realizado', '83423473', '12362173', 5),
            (0.45, '2020-05-01', 1, 'Realizado', '73642237', '90854563', 8),
            (0.45, '2020-08-07', 2, 'Realizado', '83423473', '78354298', 5),
            (0.45, '2020-11-5', 2, 'Realizado', '73642237', '12362173', 8),
	    (0, '2020-12-01', 2, 'Por Realizar', '12321312', '78354298', 1),
            (0, '2021-01-21', 1, 'Por Realizar', '73467328', '90854563', 4),
            (0, '2021-04-19', 2, 'Por Realizar', '23498789', '90854563', 7);
            

INSERT INTO `UBERblood`.`Entrega` 
	(qtd_sangue, id_US, id_func)
    	VALUES 
		(0.9, 1, '12354243'),
		(1.8, 2, '12343245'),
		(0.45, 1, '12354243'),
		(0.45, 3, '12343245');
        

INSERT INTO `UBERblood`.`Sangue_Entrega`
    	(id_sangue, id_entrega, data)
    	VALUES
		(7,1,'2020-05-12'),
		(7,2,'2020-10-01'),
		(5,3,'2020-11-02'),
		(8,4,'2020-12-01');