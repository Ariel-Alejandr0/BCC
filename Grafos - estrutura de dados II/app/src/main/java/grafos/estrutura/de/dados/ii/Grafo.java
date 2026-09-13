package grafos.estrutura.de.dados.ii;

import java.util.ArrayList;
import java.util.List;

public class Grafo {
    private final List<Aresta> arestas = new ArrayList<>();
    private final List<Vertice> vertices = new ArrayList<>();

    public int getOrdem() {
        return vertices.size();
    }

    public int getTamanho() {
        return arestas.size();
    }

    public void vertices() {
        vertices.forEach(System.out::println);
    }

    public void arestas() {
        arestas.forEach(System.out::println);
    }

    public Vertice insereV() {
        Vertice novoVertice = new Vertice();
        vertices.add(novoVertice);
        return novoVertice;
    }

    public Vertice insereV(String nome) {
        Vertice novoVertice = new Vertice(nome);
        vertices.add(novoVertice);
        return novoVertice;
    }

    public Aresta insereA(Vertice u, Vertice v) {
        if (u == null || v == null) {
            throw new IllegalArgumentException("Os vértices não podem ser nulos.");
        }
        if (!vertices.contains(u)) {
            System.out.println("Vértice u não pertence ao grafo.");
            return null;
        }
        if (!vertices.contains(v)) {
            System.out.println("Vértice v não pertence ao grafo.");
            return null;
        }

        Aresta novaAresta = new Aresta(u, v);
        arestas.add(novaAresta);
        u.adicionarAresta(novaAresta);
        v.adicionarAresta(novaAresta);
        return novaAresta;
    }

    public void removeA(Aresta e) {
        arestas.remove(e);
    }

    public List<Vertice> adj(Vertice v) {
        List<Vertice> adjacentes = new ArrayList<>();
        for (Aresta aresta : arestas) {
            if (aresta.getU().equals(v)) {
                adjacentes.add(aresta.getV());
            } else if (aresta.getV().equals(v)) {
                adjacentes.add(aresta.getU());
            }
        }
        return adjacentes;
    }

    public Aresta getA(Vertice u, Vertice v) {
        for (Aresta aresta : arestas) {
            if ((aresta.getU().equals(u) && aresta.getV().equals(v)) ||
                    (aresta.getU().equals(v) && aresta.getV().equals(u))) {
                return aresta;
            }
        }
        return null;
    }

    public int grauE(Vertice v) {
        int grau = 0;
        for (Aresta aresta : arestas) {
            if (aresta.getU().equals(v) || aresta.getV().equals(v)) {
                grau++;
            }
        }
        return grau;
    }

    public int grauE() {
        return arestas.size();
    }
}
