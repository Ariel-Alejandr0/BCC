package grafos.estrutura.de.dados.ii;

public class Aresta {
    private final Vertice u;
    private final Vertice v;

    public Aresta(Vertice u, Vertice v) {
        this.u = u;
        this.v = v;
    }

    public Vertice getU() {
        return u;
    }

    public Vertice getV() {
        return v;
    }

    @Override
    public String toString() {
        return u + " - " + v;
    }
}
