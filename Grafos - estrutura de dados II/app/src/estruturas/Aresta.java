package estruturas;

public class Aresta {
    private Vertice u;
    private Vertice v;

    public Aresta(Vertice u, Vertice v){
        this.u = u;
        this.v = v;
    }
    public Vertice getU(){
        return u;
    }
    public Vertice getV(){
        return v;
    }
}
