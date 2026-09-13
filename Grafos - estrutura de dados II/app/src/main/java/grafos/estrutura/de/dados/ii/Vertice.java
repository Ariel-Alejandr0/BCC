package grafos.estrutura.de.dados.ii;

import java.util.ArrayList;
import java.util.List;

public class Vertice {
    private final List<Aresta> arestas = new ArrayList<>();
    private final String nome;

    public Vertice() {
        this("V");
    }

    public Vertice(String nome) {
        this.nome = nome;
    }

    public List<Aresta> getArestas() {
        return arestas;
    }

    public void adicionarAresta(Aresta aresta) {
        arestas.add(aresta);
    }

    public String getNome() {
        return nome;
    }

    @Override
    public String toString() {
        return nome;
    }
}
