package estruturas;

import java.util.HashMap;
import java.util.Map;

public class BuscaEmProfundidade {
    private static Map<Vertice, Estado> estado = new HashMap<>();
    private static Map<Vertice, Vertice> predecessor = new HashMap<>();
    private static Map<Vertice, Integer> ta = new HashMap<>();
    private static Map<Vertice, Integer> te = new HashMap<>();
    private static int tempo;

    private static void visitaVertice(EstruturaGrafo grafo, Vertice vi) {
        estado.put(vi, Estado.VISITADO);
        tempo++;
        ta.put(vi, tempo);
        for (Vertice vj : grafo.adj(vi)) {
            if (estado.get(vj) == Estado.NAO_VISITADO) {
                predecessor.put(vj, vi);
                visitaVertice(grafo, vj);
            }
        }
        estado.put(vi, Estado.ENCERRADO);
        tempo++;
        te.put(vi, tempo);
    }

    public static ResultadoBusca busca(EstruturaGrafo grafo, Vertice r) {
        for (Vertice v : grafo.vertices()) {
            estado.put(v, Estado.NAO_VISITADO);
            predecessor.put(v, null);
        }
        tempo = 0;
        visitaVertice(grafo, r);
        return new ResultadoBusca(
                grafo.vertices,
                estado,
                predecessor,
                null,
                ta,
                te
        );
    }

    public static ResultadoBusca buscaTodos(EstruturaGrafo grafo) {
        for (Vertice v : grafo.vertices()) {
            estado.put(v, Estado.NAO_VISITADO);
            predecessor.put(v, null);
        }
        tempo = 0;

        for (Vertice v : grafo.vertices()) {
            if (estado.get(v) == Estado.NAO_VISITADO) {
                visitaVertice(grafo, v);
            }
        }
        return new ResultadoBusca(
                grafo.vertices,
                estado,
                predecessor,
                null,
                ta,
                te
        );
    }
}
