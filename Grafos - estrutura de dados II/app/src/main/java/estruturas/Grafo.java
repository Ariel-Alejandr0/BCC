    package estruturas;

    import java.util.ArrayList;
    import java.util.List;

    public class Grafo extends EstruturaGrafo{
        @Override
        public Vertice removeV(Vertice v){
            if(!vertices.contains(v)){
                System.out.println("Vertice v não pertence ao grafo.");
                return null;
            }

            List<Aresta> arestas = new ArrayList<>(v.getArestas());//copia primeiro
            for(Aresta a : arestas) {
                removeA(a);
            }

            vertices.remove(v);
            return v;
        }
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
            u.getArestas().add(novaAresta);
            v.getArestas().add(novaAresta);
            cacheArestas.add(novaAresta);

            return novaAresta;
        }

        public boolean removeA(Aresta e){
            Vertice u = e.getU();
            Vertice v = e.getV();

            boolean removidaU = u.getArestas().remove(e);
            boolean removidaV = v.getArestas().remove(e);
            boolean removidaCache = cacheArestas.remove(e);

            return (removidaU && removidaV && removidaCache);
        }
        @Override
        public List<Vertice> adj(Vertice v){
            List<Vertice> adjacentes = new ArrayList<Vertice>();
            if(!vertices.contains(v)){
                System.out.println("Vertice v não pertence ao grafo.");
                return null;
            }
            for(Aresta a : v.getArestas()){
                if(a.getU() == v){
                    Vertice vAdj = a.getV();
                    adjacentes.add(vAdj);
                } else if (a.getV() == v){
                    Vertice vAdj = a.getU();
                    adjacentes.add(vAdj);
                }
            };
            return adjacentes;
        }
        @Override
        public Aresta getA(Vertice u, Vertice v){
            for(Aresta A : u.getArestas()){
                if(A.getU() == u && A.getV() == v){
                    return  A;
                } else if(A.getU() == v && A.getV() == u){
                    return A;
                }
            }
            return null;
        }
        public int grauV(Vertice v) {
            return v.getArestas().size();
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

        public List<Aresta> arestasV(Vertice v){
            if(!vertices.contains(v)){
                System.out.println("Vertice v não pertence ao grafo.");
                return null;
            }
            return v.getArestas();
        }
        @Override
        public String toString() {
            StringBuilder resultado = new StringBuilder();

            for (Aresta a : cacheArestas) {
                resultado.append("A")
                        .append(a.getId())
                        .append(": V")
                        .append(a.getU().getId())
                        .append(" ------ V")
                        .append(a.getV().getId())
                        .append("\n");
            }

            return resultado.toString();
        }
    }
