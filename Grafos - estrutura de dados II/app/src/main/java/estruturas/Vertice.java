package estruturas;

import java.util.ArrayList;
import java.util.List;

public class Vertice {
    private int id;
    private List<Aresta> arestas;
    private List<Aresta> arestasEntrada;
    private List<Aresta> arestasSaida;

    public Vertice(int id) {
        this.id = id;
        arestas = new ArrayList<>();
        arestasEntrada = new ArrayList<>();
        arestasSaida = new ArrayList<>();
    }

    public int getId() {
        return id;
    }

    public List<Aresta> getArestas() {
        return arestas;
    }

    public List<Aresta> getArestasEntrada() {
        return arestasEntrada;
    }

    public List<Aresta> getArestasSaida() {
        return arestasSaida;
    }
}
