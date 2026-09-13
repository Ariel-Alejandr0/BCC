package grafos;

import estruturas.Aresta;
import estruturas.Digrafo;
import estruturas.Vertice;

import java.util.List;

public class App {

    public static void main(String[] args) {
        //ATENÇÃO: Estes testes Foram gerados via IA.
        System.out.println("=================================");
        System.out.println("       TESTES DE DIGRAFO");
        System.out.println("=================================");

        Digrafo grafo = new Digrafo();

        // =========================================================
        // 1. TESTE insereV()
        // =========================================================

        System.out.println("\n--- 1. insereV() ---");

        Vertice a = grafo.insereV();
        Vertice b = grafo.insereV();
        Vertice c = grafo.insereV();
        Vertice d = grafo.insereV();

        System.out.println("Ordem esperada: 4");
        System.out.println("Ordem obtida:   " + grafo.getOrdem());


        // =========================================================
        // 2. TESTE insereA()
        // =========================================================

        System.out.println("\n--- 2. insereA() ---");

        // A -> B
        Aresta ab = grafo.insereA(a, b);

        // A -> C
        Aresta ac = grafo.insereA(a, c);

        // B -> C
        Aresta bc = grafo.insereA(b, c);

        // C -> A
        Aresta ca = grafo.insereA(c, a);

        // D -> C
        Aresta dc = grafo.insereA(d, c);

        System.out.println("Arestas esperadas: 5");
        System.out.println("Arestas obtidas:   " + grafo.getTamanho());


        // =========================================================
        // 3. TESTE getOrdem()
        // =========================================================

        System.out.println("\n--- 3. getOrdem() ---");

        System.out.println("Esperado: 4");
        System.out.println("Obtido:   " + grafo.getOrdem());


        // =========================================================
        // 4. TESTE getTamanho()
        // =========================================================

        System.out.println("\n--- 4. getTamanho() ---");

        System.out.println("Esperado: 5");
        System.out.println("Obtido:   " + grafo.getTamanho());


        // =========================================================
        // 5. TESTE vertices()
        // =========================================================

        System.out.println("\n--- 5. vertices() ---");

        List<Vertice> vertices = grafo.vertices();

        System.out.println("Quantidade esperada: 4");
        System.out.println("Quantidade obtida:   " + vertices.size());

        for (Vertice v : vertices) {
            System.out.println(v);
        }


        // =========================================================
        // 6. TESTE arestas()
        // =========================================================

        System.out.println("\n--- 6. arestas() ---");

        List<Aresta> arestas = grafo.arestas();

        System.out.println("Quantidade esperada: 5");
        System.out.println("Quantidade obtida:   " + arestas.size());

        for (Aresta e : arestas) {
            System.out.println(
                    e.getU() + " -> " + e.getV()
            );
        }


        // =========================================================
        // 7. TESTE adj(v)
        // =========================================================

        System.out.println("\n--- 7. adj(v) ---");

        System.out.println("Adjacentes de A:");

        for (Vertice v : grafo.adj(a)) {
            System.out.println(v);
        }

        // Esperado: B e C


        // =========================================================
        // 8. TESTE getA(u, v)
        // =========================================================

        System.out.println("\n--- 8. getA(u, v) ---");

        Aresta resultado = grafo.getA(a, b);

        System.out.println("getA(A, B):");
        System.out.println(resultado);

        System.out.println("\ngetA(B, A):");
        System.out.println(grafo.getA(b, a));

        // A -> B existe
        // B -> A não existe


        // =========================================================
        // 9. TESTE grauE()
        // =========================================================

        System.out.println("\n--- 9. grauE(v) ---");

        System.out.println("grauE(A) esperado: 1");
        System.out.println("grauE(A) obtido:   " + grafo.grauE(a));

        System.out.println("grauE(C) esperado: 3");
        System.out.println("grauE(C) obtido:   " + grafo.grauE(c));


        // =========================================================
        // 10. TESTE grauS()
        // =========================================================

        System.out.println("\n--- 10. grauS(v) ---");

        System.out.println("grauS(A) esperado: 2");
        System.out.println("grauS(A) obtido:   " + grafo.grauS(a));

        System.out.println("grauS(C) esperado: 1");
        System.out.println("grauS(C) obtido:   " + grafo.grauS(c));


        // =========================================================
        // 11. TESTE verticesA()
        // =========================================================

        System.out.println("\n--- 11. verticesA(e) ---");

        List<Vertice> extremos = grafo.verticesA(ab);

        System.out.println("Origem:  " + extremos.get(0));
        System.out.println("Destino: " + extremos.get(1));


        // =========================================================
        // 12. TESTE oposto()
        // =========================================================

        System.out.println("\n--- 12. oposto(v, e) ---");

        System.out.println("oposto(A, A->B):");
        System.out.println(grafo.oposto(a, ab));

        System.out.println("\noposto(B, A->B):");
        System.out.println(grafo.oposto(b, ab));


        // =========================================================
        // 13. TESTE arestasE()
        // =========================================================

        System.out.println("\n--- 13. arestasE(v) ---");

        System.out.println("Arestas que entram em C:");

        for (Aresta e : grafo.arestasE(c)) {
            System.out.println(
                    e.getU() + " -> " + e.getV()
            );
        }

        // Esperado:
        // A -> C
        // B -> C
        // D -> C


        // =========================================================
        // 14. TESTE arestasS()
        // =========================================================

        System.out.println("\n--- 14. arestasS(v) ---");

        System.out.println("Arestas que saem de A:");

        for (Aresta e : grafo.arestasS(a)) {
            System.out.println(
                    e.getU() + " -> " + e.getV()
            );
        }

        // Esperado:
        // A -> B
        // A -> C


        // =========================================================
        // 15. TESTE removeA()
        // =========================================================

        System.out.println("\n--- 15. removeA() ---");

        System.out.println("Antes: " + grafo.getTamanho());

        grafo.removeA(ab);

        System.out.println("Depois: " + grafo.getTamanho());

        System.out.println("Esperado: 4");


        // =========================================================
        // 16. TESTE removeV()
        // =========================================================

        System.out.println("\n--- 16. removeV() ---");

        System.out.println("Antes:");

        System.out.println("Vértices: " + grafo.getOrdem());
        System.out.println("Arestas:  " + grafo.getTamanho());

        // Remover C.
        // C possui:
        //
        // A -> C
        // B -> C
        // C -> A
        // D -> C
        //
        // Todas devem ser removidas.

        grafo.removeV(c);

        System.out.println("\nDepois de remover C:");

        System.out.println("Vértices: " + grafo.getOrdem());
        System.out.println("Arestas:  " + grafo.getTamanho());

        System.out.println("\nEsperado:");
        System.out.println("Vértices: 3");
        System.out.println("Arestas:  0");


        // =========================================================
        // FIM
        // =========================================================

        System.out.println("\n=================================");
        System.out.println("       FIM DOS TESTES");
        System.out.println("=================================");
    }
}