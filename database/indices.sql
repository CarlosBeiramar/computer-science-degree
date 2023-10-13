-- Indicação da Base de Dados de Trabalho.
USE uberblood;

-- Criacao de um índice (INDEX) sobre o atributo "estado" e "data" da tabela "Doacao".
CREATE INDEX idxEstadoDataDoacao
	ON Doacao (estado,data);

SHOW INDEX FROM Doacao;
