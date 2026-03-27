from random import randint  
import math
def gerarNumRand(n):
    lista = []
    for i in range(n):
        num = randint(0, n)
        while num in lista:
            num = randint(0, n)
        lista.append(num)
    return lista
n = int(input("Digite a quantidade de números aleatórios que deseja gerar: "))
numeros_aleatorios = gerarNumRand(n)            
print(numeros_aleatorios)