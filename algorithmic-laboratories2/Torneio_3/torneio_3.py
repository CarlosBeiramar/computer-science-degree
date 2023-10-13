'''

Neste torneio pretende-se que implemente uma função que processa uma mensagem.

A mensagem é constituída por vários blocos de letras separados por ';'.

Cada bloco é recebido num formato comprimido: um número seguido de uma 
sequência entre parêntesis significa que essa sequência é repetida o número
de vezes indicado.

A função deve começar por descomprimir os blocos e filtrar os blocos vazios.

Depois deve filtrar os blocos que concordam com um padrão que também é parâmetro
da função processa. Um bloco concorda com um padrão se for possível obtê-lo a partir
do padrão substituindo cada caracter '?' por uma letra e cada caracter '*' por um
número arbitrário de letras. Por exemplo, 'aabxaxb' concorda com o padrão 'a*?b',
enquanto que 'ab' já não.

Depois de filtrar a função deve introduzir redundância na mensagem, repetindo 
alguns blocos. Deve escolher os blocos a repetir por forma a maximizar o 
número total de caracteres da mensagem, mas garantindo que nunca repete dois
blocos consecutivos.

Finalmente a função deve voltar a comprimir os blocos resultantes, com o cuidado
de comprimir o máximo possível.

'''
def descomprime(mensagem): 
    nums = [] 
    stringstack = [] 
    temp = "" 
    result = ""  
    i = 0
    while i < len(mensagem): 
        count = 0
  
        if mensagem[i].isdigit():
            while mensagem[i].isdigit():
                count = count * 10 + ord(mensagem[i]) - ord('0')  
                i += 1
            i -= 1
            nums.append(count) 
  
        elif mensagem[i] == ')': 
            temp = ""  
            count = 0
  
            if len(nums) != 0: 
                count = nums[-1]  
                nums.pop() 
  
            while (len(stringstack) != 0 and stringstack[-1] !='(' ): 
                temp = stringstack[-1] + temp  
                stringstack.pop() 
  
            if (len(stringstack) != 0 and stringstack[-1] == '('):  
                stringstack.pop()  
  
            for j in range(count): 
                result = result + temp  
  
            for j in range(len(result)): 
                stringstack.append(result[j])  
  
            result = "" 
  
        elif mensagem[i] == '(': 
            if mensagem[i-1].isdigit():
                stringstack.append(mensagem[i])  
  
            else: 
                stringstack.append(mensagem[i])  
                nums.append(i) 
  
        else: 
            stringstack.append(mensagem[i]) 
          
        i += 1
        
    for x in stringstack:
        if len(x) == 0:
            stringstack.remove(x)
    
    while len(stringstack) != 0:
        result = stringstack[-1] + result  
        stringstack.pop() 
  
    return result 
    
def strrmatch(palavra, padrao): 
      
    if (len(padrao) == 0): 
        return (len(palavra) == 0) 
          
    # matriz para guardar resultados de subproblemas 
    lookup = [[False for i in range(len(padrao) + 1)] for j in range(len(palavra) + 1)] 
      
    #padrao vazio,string vazia 
    lookup[0][0] = True
      
    # * pode corresponder a string vazia
    for j in range(1, len(padrao) + 1): 
        if (padrao[j - 1] == '*'): 
            lookup[0][j] = lookup[0][j - 1] 
              
    for i in range(1, len(palavra) + 1): 
        for j in range(1, len(padrao) + 1): 

            if (padrao[j - 1] == '*'): 
                lookup[i][j] = lookup[i][j - 1] or lookup[i - 1][j] 
              
            elif (padrao[j - 1] == '?' or palavra[i - 1] == padrao[j - 1]): 
                lookup[i][j] = lookup[i - 1][j - 1] 
                  
            else: 
                lookup[i][j] = False
      
    return lookup[len(palavra)][len(padrao)]

def filtra(mensagem,padrao):
    d = []
    s = descomprime(mensagem)
    palavras = []
    i = 0
    while i < len(s):
        aux = ''
        while i < len(s) and s[i] != ';':
            aux += s[i]
            i += 1
        
        if len(aux) > 0:
            palavras.append(aux)
        
        i += 1
    
    for pal in palavras:
        if strrmatch(pal, padrao):
            d.append((pal,len(pal)))
    
    return d
    
def comprime(mensagem):
    dic={}

    #passo 1 encontrar todos os padrões(sub-strings) e o seu numero de ocorrências
    for i in range(len(mensagem)):
        for j in range(i+1,len(mensagem)+1):
            dic[mensagem[i:j]]=0

    for k in dic.keys():
        i=0
        while i<len(mensagem):
            if k==mensagem[i:i+len(k)]:
                acc=1
                p=i+len(k)
                while k==mensagem[p:p+len(k)]:
                    acc+=1
                    p=p+len(k)
                if dic[k]<acc:
                    dic[k]=acc
                i=p
            else:
                i+=1

    #passo 2 eliminar os padrões que não compensam comprimir
    vf=[]
    for k,v in dic.items():
        if v==1 or v==2 or v==3 or v==4:
            vf.append(k)
    for v in vf:
        del dic[v]

    #passo 3 encontrar o padrão com o maior numero de ocorrências e comprimi-lo
    res=''
    if dic!={}:
        pdr=''
        acc=0
        for k,v in dic.items():
            if v>acc:
                acc=v
                pdr=k
        i=0
        while i<len(mensagem):
            if pdr==mensagem[i:i+len(pdr)]:
                c=1
                p=i+len(pdr)
                while pdr==mensagem[p:p+len(pdr)]:
                    c+=1
                    p=p+len(pdr)
                if c==acc:
                    res+=str(acc)+'('+pdr+')'
                else:
                    while c!=0:
                        res+=pdr
                        c-=1
                i=p
            else:
                res+=mensagem[i]
                i+=1


    else:
        res=mensagem

    return res
    
def processa(mensagem,padrao):
    s_final = []
    s =[]
    d = filtra(mensagem,padrao)
    
    lista1 = []
    lista2 = []
    lista3 = []
    
    for i in range (len(d)):
        if i % 2 == 0:
            lista1.append(d[i])
            lista1.append(d[i])
            lista2.append(d[i])
        
        elif i % 2 == 1:
            lista1.append(d[i])
            lista2.append(d[i])
            lista2.append(d[i])
    
    soma1 = 0
    soma2 = 0
    
    for pal,tam in lista1:
        soma1 += tam
    
    for pal,tam in lista2:
        soma2 += tam
            
    if soma1 > soma2:
        for i in range(len(lista1)):
            if i == len(lista1) - 1:
                s.append(lista1[i][0])
            else:
                s.append(lista1[i][0])
                
    else:
        for i in range(len(lista2)):
            if i == len(lista2) - 1:
                s.append(lista2[i][0])
            else:
                s.append(lista2[i][0])

    print(s)
    
    for pal in s:
        s_final.append(comprime(pal))
        
    s_final = ';'.join(s_final)

    
    return s_final