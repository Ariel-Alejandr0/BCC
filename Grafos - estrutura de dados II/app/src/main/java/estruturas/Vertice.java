package estruturas;

import java.util.ArrayList;
import java.util.List;

public class Vertice {
    private List<Aresta> arestas;
    private List<Aresta> arestasEntrada;
    private List<Aresta> arestasSaida;

    public Vertice() {
        arestas = new ArrayList<>();
        arestasEntrada = new ArrayList<>();
        arestasSaida = new ArrayList<>();
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
