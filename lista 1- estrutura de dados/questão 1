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
ARR_TESTE = [1, 4, 6, 8, 7 ,19 , 51, 3, 0, 25]
print(doBubbleSort(ARR_TESTE))


def troca(lista, a, b):
    temp = lista[a]
    lista[a] = lista[b]
    lista[b] = temp
def particiona(lista, a, b):
    x = lista[a]
    while a < b:
        while lista[a] < x:
            a += 1 
        while lista[b] > x:
            b -= 1
        troca(lista, a, b)
    return a 
def quickSort(lista, a, b):
    if a < b:
        indicePivo = particiona(lista, a, b)
        quickSort(lista, a, indicePivo - 1)
        quickSort(lista, indicePivo + 1, b)
    return lista
ARR_TESTE = [1, 4, 6, 8, 7 ,19 , 51, 3, 0, 25]
print(quickSort(ARR_TESTE, 0, 9))


import math
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
ARR_TESTE = [1, 4, 6, 8, 7 ,19 , 51, 3, 0, 25]
mergesort(ARR_TESTE, 0, 10)
print(ARR_TESTE)
