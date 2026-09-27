package estruturas;

import java.util.ArrayList;
import java.util.List;

public abstract class EstruturaGrafo {
    protected int proximoId = 1;
    protected int proximoIdAresta = 1;
    protected List<Vertice> vertices = new ArrayList<>();
    protected List<Aresta> cacheArestas = new ArrayList<>();

    public int getOrdem() {
        return vertices.size();
    }

    public int getTamanho() {
        return cacheArestas.size();
    }

    public List<Vertice> vertices() {
        return vertices;
    }

    public List<Aresta> arestas() {
        return cacheArestas;
    }

    public Vertice insereV() {
        Vertice novo = new Vertice(proximoId++);
        vertices.add(novo);
        return novo;
    }

    public abstract Aresta insereA(Vertice u, Vertice v);

    public abstract Vertice removeV(Vertice v);

    public abstract List<Vertice> adj(Vertice v);

    public abstract Aresta getA(Vertice u, Vertice v);

    public abstract Vertice oposto(Vertice v, Aresta e);
}
