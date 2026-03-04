from random import randint 
import math
import time

def doBubbleSort(lista):
    n = len(lista)
    for i in range(n, 0, -1):
        troca = False
        for j in range(0, i - 1):
            if lista[j] > lista[j + 1]:
                temp = lista[j]
                lista[j] = lista[j + 1]
                lista[j + 1] = temp 
                troca = True 
        if troca == False:
            return lista 
    return lista

def troca(lista, a, b):
    temp = lista[a]
    lista[a] = lista[b]
    lista[b] = temp
def particiona(lista, a, b):
    pivo = lista[a]
    i = a - 1
    j = b + 1

    while True:
        i += 1
        while lista[i] < pivo:
            i += 1

        j -= 1
        while lista[j] > pivo:
            j -= 1

        if i >= j:
            return j

        troca(lista, i, j)


def quickSort(lista, a, b):
    if a < b:
        p = particiona(lista, a, b)
        quickSort(lista, a, p)
        quickSort(lista, p + 1, b)


def merge(lista, p, q, r): #p = valor min; q = valor mediano; r = valor max 
    n1 = q - p
    n2 = r - q
    left = [None] * (n1 + 1)
    right = [None] * (n2 + 1)
    for i in range(0, n1): 
        left[i] = lista[p + i]
    for j in range(0, n2):
        right[j] = lista[q + j]
    left[n1] = math.inf
    right[n2] = math.inf
    i = 0 
    j = 0 
    for k in range(p, r):
        if left[i] <= right[j]:
            lista[k] = left[i]
            i = i + 1 
        else:
            lista[k] = right[j]
            j = j + 1
    return lista 
def mergesort(lista, p, r):
    if p < r - 1:
        q = math.floor((p + r) / 2)
        mergesort(lista, p, q)
        mergesort(lista, q, r)
        merge(lista, p, q, r)
from random import randint 
def gerarNumRand(n):
    lista = []
    for i in range(n):
        num = randint(1, 1000)
        while num in lista:
            num = randint(1, 1000)
        lista.append(num)
    return lista

def medir_tempo(funcao, lista, *args):
    copia = lista.copy()
    inicio = time.perf_counter()
    
    funcao(copia, *args)
    
    fim = time.perf_counter()
    return fim - inicio

# n = int(input("Digite a quantidade de números aleatórios: "))
# numeros_aleatorios = gerarNumRand(n)

# print("\nArray original:")
# print(numeros_aleatorios)

for i in [10, 10**2, 10**3, 10**4]:
    print(f"\nGerando {i} números aleatórios...")
    numeros_aleatorios = gerarNumRand(i)
    # Medindo tempos
    tempo_bubble = medir_tempo(doBubbleSort, numeros_aleatorios)
    tempo_quick = medir_tempo(quickSort, numeros_aleatorios, 0, len(numeros_aleatorios) - 1)
    tempo_merge = medir_tempo(mergesort, numeros_aleatorios, 0, len(numeros_aleatorios))

    print("\nTempos de execução:")
    print(f"Bubble Sort: {tempo_bubble:.6f} segundos")
    print(f"Quick Sort:  {tempo_quick:.6f} segundos")
    print(f"Merge Sort:  {tempo_merge:.6f} segundos")
print("\nFim dos testes.")

