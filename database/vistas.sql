USE uberblood;

CREATE VIEW vwTelemovelDoadores AS
	SELECT n_cc AS Nr_cc, 
		nome, tipo_sangue, 
		morada AS cod_postal,
        CD.telemovel 
		FROM Doador INNER JOIN Contacto_Doador AS CD
        ON Doador.n_cc = CD.id_doador ;
        
SELECT *
	FROM vwTelemovelDoadores;
    
CREATE VIEW vwTopDoadores AS
	SELECT Doador.nome, id_doador, SUM(D.qtd_sangue) AS quantidade_doada
        FROM Doacao AS D
        INNER JOIN Doador
        ON id_doador = Doador.n_cc
        WHERE D.estado = 'Realizado'
        GROUP BY id_doador
        ORDER BY SUM(D.qtd_sangue) DESC
        LIMIT 3;
        
SELECT *
	FROM vwTopDoadores;

CREATE VIEW vwTopEnfermeiros AS
	SELECT F.nome , F.n_cc, COUNT(*) AS 'doacoes que participou'
        FROM Doacao AS D
        INNER JOIN Funcionario AS F 
        ON id_enf = F.n_cc
        WHERE D.estado = 'Realizado' AND F.funcao = 'E'  
        GROUP BY id_enf
        ORDER BY COUNT(*) DESC
        LIMIT 3;
        
SELECT *
	FROM vwTopEnfermeiros;
