USE UBERblood;

-- Querie 1: Listar todos os doadores.
DELIMITER %%
CREATE PROCEDURE listar_doadores()
	BEGIN
		SELECT * FROM Doador;
	END
%%

CALL listar_doadores()

-- Querie 2: Listar todos os funcionários.
DELIMITER %%
CREATE PROCEDURE listar_funcionarios()
	BEGIN
		SELECT * FROM Funcionario;
	END
%%
 
CALL listar_funcionarios()

-- Querie 3: Listar todos os enfermeiros.
DELIMITER %%
CREATE PROCEDURE listar_enfermeiros()
	BEGIN
		SELECT * FROM Funcionario
        WHERE Funcionario.funcao = 'E';
	END
%%

CALL listar_enfermeiros()

-- Querie 4: Listar todos os funcionários regulares.
DELIMITER %%
CREATE PROCEDURE listar_func_regulares()
	BEGIN
		SELECT * FROM Funcionario
        WHERE Funcionario.funcao = 'R';
	END
%%

CALL listar_func_regulares()

-- Querie 5: Listar todas as entregas.
DELIMITER %%
CREATE PROCEDURE listar_entregas()
	BEGIN
		SELECT * FROM Entrega;
	END
%%

CALL listar_entregas()

-- Querie 6: listar todas as doações.
DELIMITER %%
CREATE PROCEDURE listar_doacoes()
	BEGIN
		SELECT * FROM Doacao;
	END
%%

CALL listar_doacoes()

-- Querie 7: listar tipos de sangue.
DELIMITER %%
CREATE PROCEDURE listar_tp_sangue()
	BEGIN
		SELECT * FROM Sangue;
	END
%%

CALL listar_tp_sangue()

-- Querie 8: Listar as doações de um doador.
DELIMITER %%
CREATE PROCEDURE doacoes_doador(IN n_cc VARCHAR(13))
	BEGIN
		SELECT * FROM Doacao
        WHERE Doacao.id_doador = n_cc;
	END
%%

CALL doacoes_doador('23498789')

-- Querie 9: Listar todas as entregas de um tipo de sangue.
DELIMITER %%
CREATE PROCEDURE entregas_tp_sangue(IN id INT)
	BEGIN
		SELECT S.id, S.tipo, SE.id_entrega, SE.data, E.qtd_sangue, E.id_func FROM Sangue AS S
        INNER JOIN Sangue_Entrega AS SE
        ON SE.id_sangue = id
        INNER JOIN ENTREGA AS E
        ON SE.id_entrega = E.id
        WHERE S.id = id;
	END
%%

CALL entregas_tp_sangue(7)

-- Querie 10: Listar todas as doações de um tipo de sangue.
DELIMITER %%
CREATE PROCEDURE doacoes_tp_sangue(IN id INT)
	BEGIN
		SELECT * FROM Doacao as D
        WHERE D.tipo_sangue = id AND D.estado = 'Realizado';
	END
%%

CALL doacoes_tp_sangue(5)

-- Querie 11: Listar todas as doações efetuadas por um enfermeiro.
DELIMITER %%
CREATE PROCEDURE doacoes_enf(IN id_enf VARCHAR(13))
	BEGIN
		SELECT D.id AS id_doacao, D.qtd_sangue, D.numero_consultorio, D.id_doador, D.id_enf, D.data
        FROM Doacao AS D
        WHERE D.id_enf = id_enf AND D.estado = 'Realizado';
	END
%%

CALL doacoes_enf('78354298')

-- Querie 12: Listar todas as doações efetuados por um enfermeiro numa determinada data.
DELIMITER %%
CREATE PROCEDURE doacoes_enf_data(IN id_enf VARCHAR(13), data DATE)
	BEGIN 
		SELECT D.id AS id_doacao, D.qtd_sangue, D.numero_consultorio, D.id_doador, D.id_enf, D.data
        FROM Doacao AS D
        WHERE D.id_enf = id_enf AND D.estado = 'Realizado' AND D.data = data;
	END
%%

CALL doacoes_enf_data('78354298', '2018-01-05')

-- Querie 13: Listar todas as doações numa determinada data.
DELIMITER %%
CREATE PROCEDURE doacoes_data(IN data DATE)
	BEGIN
		SELECT D.id AS id_doacao, D.qtd_sangue, D.estado, D.numero_consultorio, D.id_doador, D.id_enf, D.data
        FROM Doacao AS D
        WHERE D.data = data;
	END
%%

CALL doacoes_data('2020-12-01')

-- Querie 14: Listar todas as entregas numa determinada data.
DELIMITER %%
CREATE PROCEDURE entrega_data(IN data DATE)
	BEGIN 
		SELECT * FROM Entrega AS E
        INNER JOIN Sangue_Entrega AS SE
        ON SE.id_entrega = E.id
        WHERE SE.data = data;
	END
%%

CALL entrega_data('2020-05-12')

-- Querie 15: Listar todas as doações de um certo consultório.
DELIMITER %%
CREATE PROCEDURE doacoes_consultorio(IN consultorio INT)
	BEGIN
		SELECT * FROM Doacao AS D
        WHERE D.numero_consultorio = consultorio AND D.estado = 'Realizado';
	END
%%

CALL doacoes_consultorio(1)

-- Querie 16: Listar todas as doações agendadas para uma determinada data.
DELIMITER %%
CREATE PROCEDURE doacoes_agendadas(IN data DATE)
	BEGIN
		SELECT * FROM Doacao AS D
        WHERE D.data = data AND D.estado = 'Por Realizar';
	END
%%

CALL doacoes_agendadas('2020-12-01')

-- Querie 17: Listar todas as doações numa determinada data para um determinado consultório.
DELIMITER %%
CREATE PROCEDURE doacoes_data_cons(IN data DATE, consultorio INT)
	BEGIN
		SELECT * FROM Doacao AS D
        WHERE D.data = data AND D.numero_consultorio = consultorio;
	END
%%

CALL doacoes_data_cons('2020-12-01', 2)

-- Querie 18: Listar todas as pessoas de um concelho.
DELIMITER %%
CREATE PROCEDURE pessoas_concelho(IN concelho VARCHAR(100))
	BEGIN 
		SELECT F.nome, M.concelho
        FROM Funcionario AS F LEFT JOIN Morada AS M
        ON F.morada = M.cod_postal
        WHERE M.concelho = concelho
        UNION
        SELECT D.nome, M.concelho
        FROM Doador AS D LEFT JOIN Morada AS M
        ON D.morada = M.cod_postal
        WHERE M.concelho = concelho;
	END
%%

CALL pessoas_concelho('Braga')

-- Querie 19: Mostrar o top doador.
DELIMITER %%
CREATE PROCEDURE top_doador()
	BEGIN
		SELECT * FROM Doador AS D
        ORDER BY (D.qtd_sangue) DESC
        LIMIT 1;
	END
%%

CALL top_doador()

-- Querie 20: Mostrar o top 3 de doadores num ano.
DELIMITER %%
CREATE PROCEDURE top3_doador(IN ano YEAR)
	BEGIN
		SELECT Doador.nome, id_doador, SUM(D.qtd_sangue), ano
        FROM Doacao AS D
        INNER JOIN Doador
        ON id_doador = Doador.n_cc
        WHERE YEAR(D.data) = ano AND D.estado = 'Realizado'
        GROUP BY id_doador
        ORDER BY SUM(D.qtd_sangue) DESC
        LIMIT 3;
	END
%%

CALL top3_doador(2020)


