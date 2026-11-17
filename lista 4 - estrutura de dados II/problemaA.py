
# Ariel A. Marcellino S.
# Algoritmo: union find
# Complexidade: O(V + E * a(V))

def find(pai, vertice):
    if pai[vertice] != vertice:
        pai[vertice] = find(pai, pai[vertice])

    return pai[vertice]


def union(pai, tamanho, rede1, rede2):
    raiz1 = find(pai, rede1)
    raiz2 = find(pai, rede2)

    if raiz1 == raiz2:
        return False

    # União por tamanho: árvore menor aponta para a maior
    if tamanho[raiz1] < tamanho[raiz2]:
        raiz1, raiz2 = raiz2, raiz1

    pai[raiz2] = raiz1
    tamanho[raiz1] += tamanho[raiz2]

    return True


nTestes = int(input())
alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
input()

for i in range(nTestes):
    maiorNoRede = input().upper()
    vertices = alfabeto[:alfabeto.index(maiorNoRede) + 1]

    pai = {v: v for v in vertices}
    tamanho = {v: 1 for v in vertices}

    componentes = len(vertices)

    while True:
        try:
            entrada = input()
        except EOFError: #Evitando EOFError nos teste automatizados
            break

        if entrada == "":
            break

        rede1 = entrada[0]
        rede2 = entrada[1]
        if union(pai, tamanho, rede1, rede2):
            componentes -= 1

    print(componentes)

    if i < nTestes - 1:
        print()