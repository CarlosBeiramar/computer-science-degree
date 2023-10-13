'''

Neste torneio pretende-se que implemente um programa que ajude um arquiteto a
planear os prédios a construir num bairro.

Um bairro de dimensão N é uma matriz quadrada com N x N lotes de iguais dimensões.
Em cada lote deve ser construído um prédio. As alturas dos prédios variam entre 
1 e N, sendo que em cada linha e coluna do bairro as alturas dos prédios devem ser
todas diferentes. Alguns lotes podem já ter um prédio previamente construído.

Para além destas retrições, o arquiteto tem que respeitar algumas regras de 
visibilidade: para cada coluna e para cada linha podem ser indicados quantos
prédios devem ser visíveis em cada uma das direcções.

Considere por exemplo o seguinte esquema para um bairro de dimensão N = 4.

    3 . . 1
    v v v v
. > . . . . < .
. > . 4 . . < 2
. > . . . . < .
1 > . . . 3 < .
    ^ ^ ^ ^
    . . 2 .

Dois dos lotes deste bairro já têm prédios constuídos (de alturas 4 e 3). Na primeira
coluna só podem estar visíveis 3 prédios quando olhando de Norte para Sul. Na terceira
coluna só podem estar visíveis 2 prédios quando olhando de Sul para Norte. Na quarta 
coluna só pode estar visível um prédio quando olhando de Norte para Sul. Na segunda
linha só podem estar visíveis 2 prédios quando olhando de Este para Oeste. Finalmente,
na quarta linha só pode estar visível um prédio quando olhando de Oeste para Este.

O programa deve calcular um possível projeto para o bairro, nomeadamente as alturas dos
prédios a construir em cada lote, que respeite todas as restrições dadas. Só serão dados
problemas onde tal é possível. Pode existir mais do que um projeto que satisfaz todas as
restrições, podendo neste caso ser devolvido qualquer um deles.

A função a implementar recebe 5 parâmetros:
- m é uma matriz quadrada (representada por uma lista de listas) que descreve quais os 
  prédios já existentes. Se um lote estiver vazio a lista irá conter um None na posição 
  respectiva.
- t é uma lista com as restrições de visibilidade para as colunas, quando olhando de Norte
  para Sul. Se não existir restrição para uma determinada coluna existirá um None na
  posição respectiva.
- b é uma lista com as restrições de visibilidade para as colunas, quando olhando de Sul
  para Norte. Se não existir restrição para uma determinada coluna existirá um None na
  posição respectiva.
- l é uma lista com as restrições de visibilidade para as linhas, quando olhando de Oeste
  para Este. Se não existir restrição para uma determinada linha existirá um None na
  posição respectiva.
- r é uma lista com as restrições de visibilidade para as linhas, quando olhando de Este
  para Oeste. Se não existir restrição para uma determinada linha existirá um None na
  posição respectiva.

A função deverá devolver uma matriz quadrada (representada por uma lista de listas) com as 
alturas projetadas para todos os lotes.

'''
def NorteSul(m,v):                          
    Norte_Sul = v[0]
    for x in Norte_Sul:
        if x == 1:
            indice = Norte_Sul.index(x)
            if m [0][indice] == None:
                m[0][indice] = len(m)
        elif x==len(m):
            for y in range(0,len(m)):
                indice = Norte_Sul.index(x)               
                if m[y][indice] == None:
                    m[y][indice] = y+1
    return m

def SulNorte(m,v):
    Sul_Norte = v[1]
    for x in Sul_Norte:
        if x == 1:
            indice = Sul_Norte.index(x)
            if m[len(m)-1][indice] == None:
                m[len(m)-1][indice] = len(m)
        elif x==len(m):
            for y in range(0,len(m)):
                indice = Sul_Norte.index(x)               
                if m[y][indice] == None:
                    m[y][indice] = len(m)-y
    return m

def OesteEste(m,v):
    Oeste_Este = v[2]
    for x in Oeste_Este:
        if x == 1:
            indice = Oeste_Este.index(x)
            if m [indice][0] == None:
                m[indice][0] = len(m)
        elif x==len(m):
            for y in range(0,len(m)):
                indice = Oeste_Este.index(x)               
                if m[indice][y] == None:
                    m[indice][y] = y+1    
    return m

def EsteOeste(m,v):
    Este_Oeste = v[3]
    for x in Este_Oeste: 
        if x == 1:
            indice = Este_Oeste.index(x)
            if m [indice][len(m)-1] == None:
                m[indice][len(m)-1] =len(m)
        elif x==len(m):
            for y in range(0,len(m)):
                indice = Este_Oeste.index(x)               
                if m[indice][y] == None:
                    m[indice][y] = len(m)-y     
    return m

def vazia_depois_max_sentido(tam,linha):
    encontrou = False
    i = len(linha)-1
    while i >= 0:
        if linha[i] == None and encontrou == True:
            return True
        if linha[i] == tam:
            encontrou = True
        i -= 1    
            
    return False

def encontra_vazia(m):
    for i in range(len(m)):
        for j in range(len(m[0])):
            if m[i][j]==None:
                return (i,j)
                
    return None

#funçao para contar o numero de predios visiveis numa linha ou coluna
def visibilidade(lista):
    ant = 0
    count = 0
    for x in lista:
        if x != None:
            if x > ant:
                count += 1
                ant = x
                
    return count

def visibilidadecontra(lista):
    count = 1
    x = len(lista) - 1
    ant = lista[x]
    x -= 1
    while x >= 0:
        if ant == None:
            ant = lista[x]
            
        else:
            if lista[x] != None:
                if lista[x] > ant:
                    count += 1
                    ant = lista[x]
        x -= 1
    return count

def pos_valida(m, numero, posicao):
    # Ver as linhas
    for i in range(len(m[0])):
        if m[posicao[0]][i] == numero and posicao[1]!=i:
            return False
     #Ver as colunas
    for i in range(len(m)):
        if m[i][posicao[1]] == numero and posicao[0]!=i:
            return False
            
    return True

def completa(lista):
    for x in lista:
        if x == None:
            return False
            
    return True

def restricoes(m,v,pred,posicao):
    Norte = v[0]
    Sul = v[1]
    Oeste = v[2]
    Este = v[3]
    c = posicao[1]
    l = posicao[0]
    tam = len(m)

    linha = []
    coluna = []
    for i in range(0,len(m)):
        linha.append(m[l][i])
        coluna.append(m[i][c])
        
    linha[c] = pred
    coluna[l] = pred
    
    if completa(linha):
        if Oeste[l] != None:
            if Oeste[l] != visibilidade(linha):
                return False
        
        if Este[l] != None:
            if Este[l] != visibilidadecontra(linha):
                return False
        
        for col in range(0,len(m)):
            aux = []
            a = 0
            while a < len(m):
                aux.append(m[a][col])
                a += 1
            
            if completa(aux):
                if Norte[col] != None:
                    if Norte[col] != visibilidade(aux):
                        return False
                    
                if Sul[col] != None:
                    if Sul[col] != visibilidadecontra(aux):
                        return False
                        
            else:
                if Norte[col] != None and Norte[col] < visibilidade(aux) and vazia_depois_max_sentido(tam,aux):
                    return False
        
                if Sul[col] != None and Sul[col] < visibilidadecontra(aux) and vazia_depois_max_sentido(tam,aux):
                    return False
        
    if completa(coluna): #caso a coluna esteja completa
        if Norte[c] != None:
            if Norte[c] != visibilidade(coluna):
                return False
        
        if Sul[c] != None:
            if Sul[c] != visibilidadecontra(coluna):
                return False
        
        for lin in range(0,len(m)):
            aux = []
            a = 0
            while a < len(m):
                aux.append(m[lin][a])
                a += 1
            
            if completa(aux):
                if Oeste[lin] != None:
                    if Oeste[lin] != visibilidade(aux):
                        return False
                    
                if Este[lin] != None:
                    if Este[lin] != visibilidadecontra(aux):
                        return False
                        
            else:
                if Oeste[lin] != None and Oeste[lin] < visibilidade(aux) and vazia_depois_max_sentido(tam,aux):
                    return False
        
                if Este[lin] != None and Este[lin] < visibilidadecontra(aux) and vazia_depois_max_sentido(tam,aux):
                    return False

    #if not completa(coluna):
    if Norte[c] != None and Norte[c] < visibilidade(coluna) and vazia_depois_max_sentido(tam,coluna):
        return False
        
    if Sul[c] != None and Sul[c] < visibilidadecontra(coluna) and vazia_depois_max_sentido(tam,coluna):
        return False
    
    #if not completa(linha):
    if Este[l] != None and Este[l] < visibilidadecontra(linha) and vazia_depois_max_sentido(tam,linha):
        return False
        
    if Oeste[l] != None and Oeste[l] < visibilidadecontra(linha) and vazia_depois_max_sentido(tam,linha):
        return False
        
 
    return True

def resolve(m,v):
    pos = encontra_vazia(m)
    if not pos:
        return True
    else:
        a = pos[0]
        b = pos[1]
        for i in range(1,len(m)+1):
            if pos_valida(m,i,pos) and restricoes(m,v,i,pos):
                m[a][b] = i
                
                if resolve(m,v):
                    return True
                    
                m[a][b] = None
    return False

def projeto(m,t,b,l,r):
    v = [t,b,l,r]
    m = NorteSul(m,v) #caso uma restrição seja 1 ou len(m) são casos triviais
    m = SulNorte(m,v) #caso uma restrição seja 1 ou len(m) são casos triviais
    m = OesteEste(m,v) #caso uma restrição seja 1 ou len(m) são casos triviais
    m = EsteOeste(m,v) #caso uma restrição seja 1 ou len(m) são casos triviais
    resolve(m,v)
    return m


m = [[None,None,None,None],
     [None,4   ,None,None],
     [None,None,None,None],
     [None,None,None,3   ]]
v = ([3,2,2,1],[1,3,2,2],[4,2,3,1],[1,2,2,2])


m1 = [[None,None,2   ],
      [None,3   ,None],
      [None,None,None]]
v1 = ([None,None,None],[None,None,None],[None,None,None],[None,None,None])         
