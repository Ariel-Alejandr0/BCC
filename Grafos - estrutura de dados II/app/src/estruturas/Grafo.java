package estruturas;

import java.util.List;

public class Grafo {
    private List<Aresta> arestas;
    private List<Vertice> vertices;

    public int getOrdem(){
        return vertices.size();
    }
    public int getTamanho(){
        return arestas.size();
    }
    public void vertices() {
        vertices.forEach((elemento) -> {
            System.out.println(elemento);
        });
    }

    public void arestas() {
        arestas.forEach((elemento) -> {
            System.out.println(elemento);
        });
    }

    public Vertice insereV(){
        Vertice novoVertice = new Vertice();
        vertices.add(novoVertice);
        return novoVertice;
    }
    public Aresta insereA(Vertice u, Vertice v){
        if(!vertices.contains(u)){
            System.out.println("Vertice u não pertence ao grafo.");
            return null;
        } else if (!vertices.contains(v)){
            System.out.println("Vertice v não pertence ao grafo.");
            return null;
        }
        Aresta novaAresta = new Aresta(u, v);
        arestas.add(novaAresta);
        return novaAresta;
    }
    public void removeA(Aresta e){
        arestas.remove(e);
    }
    public List<Vertice> adj(Vertice v){
        List<Vertice> adjacentes;
        arestas.forEach(aresta -> {
            if(aresta.getU() == v){
                Vertivce vAdj = aresta.getU();
                adjacentes.add(vAdj);
            } else if (aresta.getV() == v){
                Vertivce vAdj = aresta.getV();
                adjacentes.add(vAdj);
            }
        });
        return adjacentes;
    }
    public Aresta getA(Vertice u, Vertice v){
        for(Aresta A : arestas){
            if(A.getU() == u && A.getV() == v){
                return  A;
            } else if(A.getU() == v && A.getV() == u){
                return A;
            }
        }
        return null;
    }
    public grauE()
    
}
