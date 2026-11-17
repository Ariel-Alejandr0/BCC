#Inserindo variável para testar o programa (A ou B)
#Se não houver, testa o padrão que é o A

PROBLEMA="${1:-A}"

for entrada in testes/$PROBLEMA/entrada-*.txt; do
    saida="${entrada/entrada-/saida-}"

    echo "Testando ${entrada##*/}"

    if diff -q "$saida" <(python3 problema$PROBLEMA.py < "$entrada") > /dev/null; then
        echo "OK"
    else
        echo "ERRO:"
        diff -u "$saida" <(python3 problema$PROBLEMA.py < "$entrada")
    fi
done