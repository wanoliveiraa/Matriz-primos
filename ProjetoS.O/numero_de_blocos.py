
def numero_de_blocos(num):
    resultado = 0
    while num % 2 == 0:
        resultado += 1
        num /= 2
    print("valor de exploracao: ", num)
    return resultado 

lado = int(input("Lado: "))
numero_de_blocos(lado)
