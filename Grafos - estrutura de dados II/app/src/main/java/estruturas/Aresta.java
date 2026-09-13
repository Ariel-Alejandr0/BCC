package estruturas;

public class Aresta {
    //para digrafo trate u e v respectivamente como origem e destino
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
