package estruturas;

import java.util.List;
import java.util.Map;

public class ResultadoBusca {
    private List<Vertice> vertices;

    private Map<Vertice, Estado> estado;
    private Map<Vertice, Vertice> predecessor;

    private Map<Vertice, Integer> distancia;

    private Map<Vertice, Integer> ta;
    private Map<Vertice, Integer> te;

    public ResultadoBusca(
            List<Vertice> vertices,
            Map<Vertice, Estado> estado,
            Map<Vertice, Vertice> predecessor,
            Map<Vertice, Integer> distancia,
            Map<Vertice, Integer> ta,
            Map<Vertice, Integer> te
    ){
        this.vertices = vertices;
        this.estado = estado;
        this.predecessor = predecessor;
        this.distancia = distancia;
        this.ta = ta;
        this.te = te;
    }

    public void imprimeCaminho(Vertice r, Vertice v) {
        if (v == r) {
            System.out.print(r.getId());
        } else if (predecessor.get(v) == null) {
            System.out.println("não existe caminho de r para v");
        } else {
            imprimeCaminho(r, predecessor.get(v));
            System.out.print(" -> " + v.getId());
        }
    }
    public void imprimeTabela() {
        if (ta != null && te != null) {
            System.out.println("+---------+--------------+-------------+----+----+");
            System.out.println("| Vértice | Estado       | Predecessor | ta | te |");
            System.out.println("+---------+--------------+-------------+----+----+");

            for (Vertice v : vertices) {
                String idVertice = String.format("%-7s", v.getId());
                String idPredecessor = "null";
                if (predecessor.get(v) == null) {
                    idVertice = "\u001B[33m" + idVertice + "\u001B[0m";
                } else {
                    idPredecessor = Integer.toString(predecessor.get(v).getId());
                }
                System.out.printf(
                        "| %-7s | %-12s | %-11s | %-2s | %-2s |%n",
                        idVertice,
                        estado.get(v),
                        idPredecessor,
                        ta.get(v),
                        te.get(v)
                );
            }
            System.out.println("+---------+--------------+-------------+----+----+");
        } else if (distancia != null) {
            System.out.println("+---------+--------------+-------------+-----------+");
            System.out.println("| Vértice | Estado       | Predecessor | Distância |");
            System.out.println("+---------+--------------+-------------+-----------+");
            for (Vertice v : vertices) {
                String idVertice = String.format("%-7s", v.getId());
                String idPredecessor = "null";
                if (predecessor.get(v) == null) {
                    idVertice = "\u001B[33m" + idVertice + "\u001B[0m";
                } else {
                    idPredecessor = Integer.toString(predecessor.get(v).getId());
                }
                System.out.printf(
                        "| %-7s | %-12s | %-11s | %-9s |%n",
                        idVertice,
                        estado.get(v),
                        idPredecessor,
                        distancia.get(v)
                );
            }
            System.out.println("+---------+--------------+-------------+-----------+");
        }
    }
}
