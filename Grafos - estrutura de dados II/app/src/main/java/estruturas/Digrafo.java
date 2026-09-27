package estruturas;

import java.util.ArrayList;
import java.util.List;

public class Digrafo extends EstruturaGrafo{
    @Override
    public Aresta insereA(Vertice u, Vertice v){
        if(!vertices.contains(u)){
            System.out.println("Vertice u não pertence ao grafo.");
            return null;
        } else if (!vertices.contains(v)){
            System.out.println("Vertice v não pertence ao grafo.");
            return null;
        }
        Aresta novaAresta = new Aresta(proximoIdAresta, u, v);
        proximoIdAresta++;
        u.getArestasSaida().add(novaAresta);
        v.getArestasEntrada().add(novaAresta);
        cacheArestas.add(novaAresta);

        return novaAresta;
    }

    public Aresta removeA(Aresta e){
        Vertice vOrigem = e.getU();
        Vertice vDestino = e.getV();

        vDestino.getArestasEntrada().remove(e);
        vOrigem.getArestasSaida().remove(e);
        cacheArestas.remove(e);
        return e;
    }
    @Override
    public Vertice removeV(Vertice v){
        if(!vertices.contains(v)){
            System.out.println("Vertice v não pertence ao grafo.");
            return null;
        }

        List<Aresta> entradas = new ArrayList<>(v.getArestasEntrada());//copia primeiro
        List<Aresta> saidas = new ArrayList<>(v.getArestasSaida());//copia primeiro

        for(Aresta a : entradas) {
            removeA(a);
        }
        for(Aresta a : saidas) {
            removeA(a);
        }
        vertices.remove(v);
        return v;
    }
    @Override
    public List<Vertice> adj(Vertice v){
        List<Vertice> adjacentes = new ArrayList<Vertice>();
        if(!vertices.contains(v)){
            System.out.println("Vertice v não pertence ao grafo.");
            return null;
        }
        for(Aresta a : v.getArestasSaida()){
            adjacentes.add(a.getV());
        }
        return adjacentes;
    }
    @Override
    public Aresta getA(Vertice u, Vertice v){
        for(Aresta a : u.getArestasSaida()){
            if(a.getU() == u && a.getV() == v){
                return  a;
            }
        }
        return null;
    }
    public int grauE(Vertice v){
        return v.getArestasEntrada().size();
    }
    public int grauS(Vertice v){
        return v.getArestasSaida().size();
    }
    public List<Vertice> verticesA(Aresta e){
        return List.of(e.getU(), e.getV());
    }
    @Override
    public Vertice oposto(Vertice v, Aresta e){
        if(v == e.getU()){
            return e.getV();
        } else if (v == e.getV()){
            return e.getU();
        }
        System.out.println("O vértice v não pertence a aresta.");
        return null;
    }
    public List<Aresta> arestasE(Vertice v){
        if(!vertices.contains(v)){
            System.out.println("Vertice v não pertence ao grafo.");
            return null;
        }
        return v.getArestasEntrada();
    }
    public List<Aresta> arestasS(Vertice v){
        if(!vertices.contains(v)){
            System.out.println("Vertice v não pertence ao grafo.");
            return null;
        }
        return v.getArestasSaida();
    }
    @Override
    public String toString() {
        StringBuilder resultado = new StringBuilder();

        for (Aresta a : cacheArestas) {
            resultado.append("A")
                    .append(a.getId())
                    .append(": V")
                    .append(a.getU().getId())
                    .append(" -----> V")
                    .append(a.getV().getId())
                    .append("\n");
        }

        return resultado.toString();
    }
}
