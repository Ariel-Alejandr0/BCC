package grafos;

import estruturas.*;

import java.util.List;

public class App {

    public static void main(String[] args) {
        //Atenção: bateria de testes criada com IA
        //testarGrafo();
        //testarDigrafo();
        testarBuscas();
    }

    public static void testarBuscaGrafo() {

        System.out.println("\n------------------------------------");
        System.out.println("      BUSCAS EM GRAFO");
        System.out.println("------------------------------------");

        Grafo grafo = new Grafo();

        Vertice v1 = grafo.insereV();
        Vertice v2 = grafo.insereV();
        Vertice v3 = grafo.insereV();
        Vertice v4 = grafo.insereV();

        grafo.insereA(v1, v2);
        grafo.insereA(v1, v3);
        grafo.insereA(v2, v4);
        grafo.insereA(v3, v4);

        System.out.println("\n--- Busca em Profundidade ---");

        ResultadoBusca resultadoDFS =
                BuscaEmProfundidade.busca(grafo, v1);

        resultadoDFS.imprimeTabela();

        System.out.println("\nCaminho de V1 até V4:");
        resultadoDFS.imprimeCaminho(v1, v4);


        System.out.println("\n--- Busca em Largura ---");

        ResultadoBusca resultadoBFS =
                BuscaEmLargura.busca(grafo, v1);

        resultadoBFS.imprimeTabela();

        System.out.println("\nCaminho de V1 até V4:");
        resultadoBFS.imprimeCaminho(v1, v4);
    }

    public static void testarBuscaDigrafo() {

        System.out.println("\n------------------------------------");
        System.out.println("      BUSCAS EM DIGRAFO");
        System.out.println("------------------------------------");

        Digrafo digrafo = new Digrafo();

        Vertice v1 = digrafo.insereV();
        Vertice v2 = digrafo.insereV();
        Vertice v3 = digrafo.insereV();
        Vertice v4 = digrafo.insereV();

        digrafo.insereA(v1, v2);
        digrafo.insereA(v1, v3);
        digrafo.insereA(v2, v4);
        digrafo.insereA(v3, v4);

        System.out.println("\n--- Busca em Profundidade ---");

        ResultadoBusca resultadoDFS =
                BuscaEmProfundidade.busca(digrafo, v1);

        resultadoDFS.imprimeTabela();

        System.out.println("\nCaminho de V1 até V4:");
        resultadoDFS.imprimeCaminho(v1, v4);


        System.out.println("\n--- Busca em Largura ---");

        ResultadoBusca resultadoBFS =
                BuscaEmLargura.busca(digrafo, v1);

        resultadoBFS.imprimeTabela();

        System.out.println("\nCaminho de V1 até V4:");
        resultadoBFS.imprimeCaminho(v1, v4);
    }

    public static void testarBuscaTodos() {

        System.out.println("\n------------------------------------");
        System.out.println("       BUSCA EM GRAFO DESCONEXO");
        System.out.println("------------------------------------");

        Grafo grafo = new Grafo();

        Vertice v1 = grafo.insereV();
        Vertice v2 = grafo.insereV();
        Vertice v3 = grafo.insereV();
        Vertice v4 = grafo.insereV();
        Vertice v5 = grafo.insereV();

        grafo.insereA(v1, v2);
        grafo.insereA(v2, v3);

        grafo.insereA(v4, v5);

        System.out.println("\n--- Busca em Profundidade - Todos ---");

        ResultadoBusca resultadoDFS =
                BuscaEmProfundidade.buscaTodos(grafo);

        resultadoDFS.imprimeTabela();

        System.out.println("\n--- Busca em Largura ---");

        ResultadoBusca resultadoBFS =
                BuscaEmLargura.busca(grafo, v1);

        resultadoBFS.imprimeTabela();
    }

    public static void testarBuscas() {

        System.out.println("\n====================================");
        System.out.println("          TESTE DAS BUSCAS");
        System.out.println("====================================");

        testarBuscaGrafo();
        testarBuscaDigrafo();
        testarBuscaTodos();
    }

    public static void testarGrafo() {

        System.out.println("\n====================================");
        System.out.println("      TESTE GRAFO NÃO DIRECIONADO");
        System.out.println("====================================");

        Grafo grafo = new Grafo();

        Vertice v1 = grafo.insereV();
        Vertice v2 = grafo.insereV();
        Vertice v3 = grafo.insereV();
        Vertice v4 = grafo.insereV();

        Aresta a1 = grafo.insereA(v1, v2);
        Aresta a2 = grafo.insereA(v1, v3);
        Aresta a3 = grafo.insereA(v2, v3);
        Aresta a4 = grafo.insereA(v3, v4);

        System.out.println("\n--- getOrdem() ---");
        System.out.println("Esperado: 4");
        System.out.println("Obtido: " + grafo.getOrdem());

        System.out.println("\n--- getTamanho() ---");
        System.out.println("Esperado: 4");
        System.out.println("Obtido: " + grafo.getTamanho());

        System.out.println("\n--- vertices() ---");
        for (Vertice v : grafo.vertices()) {
            System.out.println(v);
        }

        System.out.println("\n--- arestas() ---");
        for (Aresta a : grafo.arestas()) {
            System.out.println(a);
        }

        System.out.println("\n--- adj(V1) ---");
        for (Vertice v : grafo.adj(v1)) {
            System.out.println(v);
        }

        System.out.println("\n--- getA(V1,V2) ---");
        System.out.println(grafo.getA(v1, v2));

        System.out.println("\n--- getA(V2,V1) ---");
        System.out.println(grafo.getA(v2, v1));

        System.out.println("\n--- grau(V1) ---");
        System.out.println("Esperado: 2");
        System.out.println("Obtido: " + grafo.grauV(v1));

        System.out.println("\n--- grau(V3) ---");
        System.out.println("Esperado: 3");
        System.out.println("Obtido: " + grafo.grauV(v3));

        System.out.println("\n--- verticesA(A1) ---");
        List<Vertice> verticesA = grafo.verticesA(a1);
        System.out.println(verticesA.get(0));
        System.out.println(verticesA.get(1));

        System.out.println("\n--- oposto(V1,A1) ---");
        System.out.println(grafo.oposto(v1, a1));

        System.out.println("\n--- oposto(V2,A1) ---");
        System.out.println(grafo.oposto(v2, a1));

        System.out.println("\n--- arestasV(V3) ---");
        for (Aresta a : grafo.arestasV(v3)) {
            System.out.println(a);
        }

        System.out.println("\n--- toString() ---");
        System.out.println(grafo);

        System.out.println("\n--- removeA(A1) ---");
        grafo.removeA(a1);
        System.out.println("Arestas esperadas: 3");
        System.out.println("Arestas obtidas: " + grafo.getTamanho());

        System.out.println("\n--- removeV(V3) ---");
        grafo.removeV(v3);

        System.out.println("Vértices esperados: 3");
        System.out.println("Vértices obtidos: " + grafo.getOrdem());

        System.out.println("Arestas esperadas: 0");
        System.out.println("Arestas obtidas: " + grafo.getTamanho());

        System.out.println("\n--- toString() final ---");
        System.out.println(grafo);
    }

    public static void testarDigrafo() {

        System.out.println("\n====================================");
        System.out.println("             TESTE DIGRAFO");
        System.out.println("====================================");

        Digrafo digrafo = new Digrafo();

        Vertice v1 = digrafo.insereV();
        Vertice v2 = digrafo.insereV();
        Vertice v3 = digrafo.insereV();
        Vertice v4 = digrafo.insereV();

        Aresta a1 = digrafo.insereA(v1, v2);
        Aresta a2 = digrafo.insereA(v1, v3);
        Aresta a3 = digrafo.insereA(v2, v3);
        Aresta a4 = digrafo.insereA(v3, v1);
        Aresta a5 = digrafo.insereA(v4, v3);

        System.out.println("\n--- getOrdem() ---");
        System.out.println("Esperado: 4");
        System.out.println("Obtido: " + digrafo.getOrdem());

        System.out.println("\n--- getTamanho() ---");
        System.out.println("Esperado: 5");
        System.out.println("Obtido: " + digrafo.getTamanho());

        System.out.println("\n--- vertices() ---");
        for (Vertice v : digrafo.vertices()) {
            System.out.println(v);
        }

        System.out.println("\n--- arestas() ---");
        for (Aresta a : digrafo.arestas()) {
            System.out.println(a);
        }

        System.out.println("\n--- adj(V1) ---");
        for (Vertice v : digrafo.adj(v1)) {
            System.out.println(v);
        }

        System.out.println("\n--- getA(V1,V2) ---");
        System.out.println(digrafo.getA(v1, v2));

        System.out.println("\n--- getA(V2,V1) ---");
        System.out.println(digrafo.getA(v2, v1));

        System.out.println("\n--- grauE(V1) ---");
        System.out.println("Esperado: 1");
        System.out.println("Obtido: " + digrafo.grauE(v1));

        System.out.println("\n--- grauS(V1) ---");
        System.out.println("Esperado: 2");
        System.out.println("Obtido: " + digrafo.grauS(v1));

        System.out.println("\n--- grauE(V3) ---");
        System.out.println("Esperado: 3");
        System.out.println("Obtido: " + digrafo.grauE(v3));

        System.out.println("\n--- grauS(V3) ---");
        System.out.println("Esperado: 1");
        System.out.println("Obtido: " + digrafo.grauS(v3));

        System.out.println("\n--- verticesA(A1) ---");
        List<Vertice> verticesA = digrafo.verticesA(a1);
        System.out.println("Origem: " + verticesA.get(0));
        System.out.println("Destino: " + verticesA.get(1));

        System.out.println("\n--- oposto(V1,A1) ---");
        System.out.println(digrafo.oposto(v1, a1));

        System.out.println("\n--- oposto(V2,A1) ---");
        System.out.println(digrafo.oposto(v2, a1));

        System.out.println("\n--- arestasE(V3) ---");
        for (Aresta a : digrafo.arestasE(v3)) {
            System.out.println(a);
        }

        System.out.println("\n--- arestasS(V1) ---");
        for (Aresta a : digrafo.arestasS(v1)) {
            System.out.println(a);
        }

        System.out.println("\n--- toString() ---");
        System.out.println(digrafo);

        System.out.println("\n--- removeA(A1) ---");
        digrafo.removeA(a1);

        System.out.println("Arestas esperadas: 4");
        System.out.println("Arestas obtidas: " + digrafo.getTamanho());

        System.out.println("\n--- removeV(V3) ---");
        digrafo.removeV(v3);

        System.out.println("Vértices esperados: 3");
        System.out.println("Vértices obtidos: " + digrafo.getOrdem());

        System.out.println("Arestas esperadas: 0");
        System.out.println("Arestas obtidas: " + digrafo.getTamanho());

        System.out.println("\n--- toString() final ---");
        System.out.println(digrafo);
    }
}