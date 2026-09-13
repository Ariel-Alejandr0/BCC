package estruturas;

public class Aresta {
    //para digrafo trate u e v respectivamente como origem e destino
    private int id;
    private Vertice u;
    private Vertice v;

    public Aresta(int id, Vertice u, Vertice v){
        this.id = id;
        this.u = u;
        this.v = v;
    }

    public int getId() {
        return id;
    }

    public Vertice getU(){
        return u;
    }
    public Vertice getV(){
        return v;
    }
}
