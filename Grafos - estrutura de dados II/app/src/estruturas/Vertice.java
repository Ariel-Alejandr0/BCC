package estruturas;

import java.util.ArrayList;
import java.util.List;

public class Vertice {
    private List<Aresta> arestas;

    public Vertice() {
        arestas = new ArrayList<>(  );
    }

    public List<Aresta> getArestas() {
        return arestas;
    }
}
