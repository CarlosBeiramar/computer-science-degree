
'''

Neste problema pretende-se calcular a rota que um carteiro deve fazer para
entregar encomendas num bairro.

O carteiro quer tentar aliviar peso o mais depressa possível, pelo que tenta
sempre ir primeiro (pelo caminho mais rápido) ao maior prédio do bairro,
continuando depois as entregas pela ordem de tamanhos. 

O mapa do bairro é dado por uma lista de blocos rectangulares 2D, dados pelas
coordenadas do canto inferior esquerdo e superior direito, sendo que quaisquer
dois ou mais blocos que se toquem (ou intersectem) pertencem ao mesmo prédio.
Se existirem dois prédios com o mesmo tamanho, o carteiro visita primeiro o que 
começou a ser definido primeiro no mapa.

O carteiro pode deixar as encomendas de um prédio em qualquer posição que lhe
seja adjacente. Se houver duas posições de um prédio à mesma distância mais
curta, o carteiro dá  prioridade à que estiver mais à esquerda, e, em caso
de empate neste critério, então escolhe a que estiver mais para baixo.

Se um prédio não for acessível então é ignorado, passando o carteiro ao
próximo.

A função a implementar recebe o ponto onde o carteiro começa a visita e o mapa
do bairro. Deve devolver a sequência de pontos onde terá que deixar as encomendas,
intercalada pela respectiva distância.

'''
import math
import copy

def distancia(x1,y1,x2,y2):
    a = (x1 - x2)**2 + (y1 - y2)**2
    b = math.sqrt(a)
    
    return b

def calcula_area(predios):
    ret = []
    maior = 0 
    for k in predios:
        aux = len(k)
        if aux > maior:
            maior = aux
            ret = k  
    return ret

def interseta(lista1,lista2):
    interseta = False
    for a in lista1:
        for b in lista2:
            if a == b:
                interseta = True
            elif distancia(a[0],a[1],b[0],b[1]) == 1:
                interseta = True
    
    return interseta
    
def buildings(blocos):
    bairro = []
    for c in blocos:
        predio = set()
        if c[0] == c[2] and c[1] == c[3]:
            predio.add((c[0],c[1]))
        else:
            predio.add((c[0],c[1]))
            predio.add((c[2],c[3]))

            if c[0] < c[2]:
                x = c[0]
                while x < c[2]:
                    predio.add((x,c[1]))
                    predio.add((x,c[3]))
                    x += 1
                
            else:
                x = c[2]
                while x <= c[0]:
                    predio.add((x,c[1]))
                    predio.add((x,c[3]))
                    x += 1
        
            if c[1] < c[3]:
                y = c[1]
                while y <= c[3]:
                    predio.add((c[0],y))
                    predio.add((c[2],y))
                    y += 1
        
            else:
                y = c[3]
                while y <= c[1]:
                    predio.add((c[0],y))
                    predio.add((c[2],y))
                    y += 1
            
        aux = list(predio)
        aux.sort(key = lambda t : t[1])
        aux.sort(key = lambda t : t[0])
        bairro.append(aux)
        
        remover = []
        i = 0
        while i < len(bairro) - 1:
            j = i + 1
            while j < len(bairro) :
                if interseta(bairro[i],bairro[j]) == True:
                    remover.append(bairro[j])
                    for a in bairro[j]:
                        if a not in bairro[i]:
                            bairro[i].append(a)
                j += 1
            i += 1
    
        for elem in remover:
            bairro.remove(elem)
        
    return bairro

def constroi_mapa(predios,posinicial):
    final = set()
    ocupados = [item for sublist in predios for item in sublist]
    listax = []
    listay = []
    
    for x in ocupados:
        listax.append(x[0])
        listay.append(x[1])
        
    listax.sort()
    listay.sort()

    minx = min(listax[0],posinicial[0])
    maxx = max(listax[len(listax)-1],posinicial[0])
    miny = min(listay[0],posinicial[1]) 
    maxy = max(listay[len(listay)-1],posinicial[1])
    
    for x in range(minx-2,maxx+2):
        for y in range(miny-2,maxy+2):
            if (x,y) not in ocupados:
                final.add((x,y))
            if (y,x) not in ocupados:
                final.add((y,x))
                
    aux = list(final)

    return (aux,ocupados)

def build(posicoes):
    ocupados = posicoes[1]
    lista = posicoes[0]
    adj = {}
    
    for x in ocupados:
        lista.append(x)
    
    for o in lista:
        if o not in adj:
            adj[o] = set()
        
        for d in lista:
            if distancia(o[0],o[1],d[0],d[1]) == 1 and d not in ocupados:
                adj[o].add(d)
                if o not in ocupados:
                    if d not in adj:
                        adj[d] = set()
                    adj[d].add(o)
                    
    aux = []
    for k,v in adj.items():
        if len(v) == 0:
            aux.append(k)
        for d in v:
            if len(adj[d]) == 0 and d not in aux:
                aux.append(d)
    
    h = copy.deepcopy(adj)
    
    for a in aux:
        for k,v in h.items():
            for d in v:
                if a == d:
                    adj[k].remove(d)            
    return adj

def bfs(adj,o,destino,mapa,ocupados):
    pai = {}
    vis = {o}
    queue = [o]
    while destino not in vis:
        v = queue.pop(0)
        for d in adj[v]:
            if d not in vis:
                vis.add(d)
                pai[d] = v
                queue.append(d)
    return pai

def caminho(adj,o,d,mapa):
    pai = bfs(adj,o,d,mapa[0],mapa[1])
    caminho = [d]
    while d in pai:
        d = pai[d]
        caminho.insert(0,d)
    return len(caminho)-1
    
def rota(inicio,blocos):
    final = []
    if len(blocos) == 0:
        return final
    
    else:
        predios = buildings(blocos)
        mapa = constroi_mapa(predios,inicio)
        adj= build(mapa)
        entregas = len(predios)
        values = [x for k,v in adj.items() for x in v]
        
        while entregas > 0:
            
            p = calcula_area(predios)
            adjpredios = []
            custos = []
            acessivel = True
            for pos in p:
                aux = list(adj[pos])
                while aux and acessivel == True:
                    d = aux.pop()
                    if d in values:
                        adjpredios.append(d)
                    else:
                        acessivel = False
                    
                if acessivel == False:
                    break

            if acessivel == True or len(custos) > 0:
                for d in adjpredios:
                    if inicio != d:
                        c = caminho(adj,inicio,d,mapa)
                        if (inicio,d,c) not in custos:
                            custos.append((inicio,d,c))
                
                     
                custos.sort(key = lambda t : t[1][1])
                custos.sort(key = lambda t : t[1][0])
                custos.sort(key = lambda t : t[2])
                final.append(inicio)
                final.append(custos[0][2])
                inicio = custos[0][1]
                entregas -= 1
                predios.remove(p)
                
            else:
                entregas -= 1
                predios.remove(p)

        final.append(inicio)
        
    return final