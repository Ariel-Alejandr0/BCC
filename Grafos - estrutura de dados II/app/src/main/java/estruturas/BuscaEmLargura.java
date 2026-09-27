package estruturas;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;

public class BuscaEmLargura {
    private static Map<Vertice, Estado> estado = new HashMap<>();
    private static Map<Vertice, Vertice> predecessor = new HashMap<>();
    private static Map<Vertice, Integer> distancia = new HashMap<>();

    public static ResultadoBusca busca(EstruturaGrafo grafo, Vertice r) {

        for (Vertice v : grafo.vertices()) {
            estado.put(v, Estado.NAO_VISITADO);
            predecessor.put(v, null);
        }
        estado.put(r, Estado.VISITADO);
        Queue<Vertice> fila = new LinkedList<>();
        fila.add(r);

        while (!fila.isEmpty()) {
            Vertice vi = fila.remove();
            for (Vertice vj : grafo.adj(vi)) {
                if (estado.get(vj) == Estado.NAO_VISITADO) {
                    estado.put(vj, Estado.VISITADO);
                    predecessor.put(vj, vi);
                    fila.add(vj);
                }
            }
            estado.put(vi, Estado.ENCERRADO);
        }
        return new ResultadoBusca(
                grafo.vertices(),
                estado,
                predecessor,
                distancia,
                null,
                null
        );
    }
    public static ResultadoBusca buscaTodos(EstruturaGrafo grafo) {
        for (Vertice v : grafo.vertices()) {
            estado.put(v, Estado.NAO_VISITADO);
            predecessor.put(v, null);
            distancia.put(v, null);
        }
        for (Vertice v : grafo.vertices()) {
            if (estado.get(v) == Estado.NAO_VISITADO) {
                estado.put(v, Estado.VISITADO);
                distancia.put(v, 0);
                Queue<Vertice> fila = new LinkedList<>();
                fila.add(v);
                while (!fila.isEmpty()) {
                    Vertice vi = fila.remove();
                    for (Vertice vj : grafo.adj(vi)) {
                        if (estado.get(vj) == Estado.NAO_VISITADO) {
                            estado.put(vj, Estado.VISITADO);
                            predecessor.put(vj, vi);
                            distancia.put(vj, distancia.get(vi) + 1);

                            fila.add(vj);
                        }
                    }
                    estado.put(vi, Estado.ENCERRADO);
                }
            }
        }

        return new ResultadoBusca(
                grafo.vertices(),
                estado,
                predecessor,
                distancia,
                null,
                null
        );
    }
}