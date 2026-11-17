# Ariel A. Marcellino S.
# Algoritmo: ConexidadeBuscaProfundidade
# Complexidade: O(N + M)

def dfs(grafo, inicio):
    visitados = [False] * len(grafo)
    pilha = [inicio]
    visitados[inicio] = True

    while pilha:
        v = pilha.pop()

        for vizinho in grafo[v]:
            if not visitados[vizinho]:
                visitados[vizinho] = True
                pilha.append(vizinho)

    return all(visitados[1:])


while True:
    qtdVtc, nTestes = map(int, input().split())

    if qtdVtc == 0 and nTestes == 0:
        break

    grafo = [[] for i in range(qtdVtc + 1)]
    reverso = [[] for i in range(qtdVtc + 1)]

    for i in range(nTestes):
        V, W, P = map(int, input().split())

        grafo[V].append(W)
        reverso[W].append(V)

        if P == 2:
            grafo[W].append(V)
            reverso[V].append(W)

    if dfs(grafo, 1) and dfs(reverso, 1):
        print(1)
    else:
        print(0)
