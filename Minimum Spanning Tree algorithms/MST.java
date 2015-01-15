import java.util.Collection;
import java.util.HashSet;
import java.util.Map;
import java.util.PriorityQueue;
/*
* @author David Barbet
*/
public class MST {

    /**
     * Using disjoint set(s), run Kruskal's algorithm on the given graph and
     * return the MST. Return null if no MST exists for the graph.
     * @param g The graph to be processed. Will never be null.
     * @return The MST of the graph; null if no valid MST exists.
     */
    public static Collection<Edge> kruskals(Graph g) {
        HashSet<Edge> answer = new HashSet<>();
        PriorityQueue<Edge> edges = new PriorityQueue<Edge>();
        Edge minimumEdge;
        DisjointSets<Vertex> aSet = new DisjointSets<Vertex>(g.getVertices());
        for (Edge e : g.getEdgeList()) {
            edges.add(e);
        }
        while (!edges.isEmpty() && (answer.size()
                != g.getVertices().size() - 1)) {
            minimumEdge = edges.poll();
            answer.add(minimumEdge);
            Vertex a = minimumEdge.getU();
            Vertex b = minimumEdge.getV();
            if (!aSet.sameSet(a, b)) {
                answer.add(minimumEdge);
                aSet.merge(a, b);
            }
        }
        if ((g.getVertices().size() - 1) != answer.size()) {
            return null;
        }
        return answer;
    }

    /**
     * Run Prim's algorithm on the given graph and return the minimum spanning
     * tree. If no MST exists, return null.
     *
     * @param g The graph to be processed. Will never be null.
     * @param start The ID of the start node. Will always exist in the graph.
     * @return the MST of the graph; null if no valid MST exists.
     */
    public static Collection<Edge> prims(Graph g, int start) {
        HashSet<Edge> answer = new HashSet<>();
        HashSet<Edge> visited = new HashSet<>();
        HashSet<Vertex> visitedNode = new HashSet<>();
        PriorityQueue<Edge> edges = new PriorityQueue<Edge>();
        Vertex current = new Vertex(start);
        Edge minimumEdge;
        for (Map.Entry<Vertex, Integer> e
                : g.getAdjacencies(current).entrySet()) {
            Edge newEdge = new Edge(current, e.getKey(), e.getValue());
            edges.add(newEdge);
            minimumEdge = newEdge;
        }
        while (!edges.isEmpty()) {
            minimumEdge = edges.poll();
            if (!visitedNode.contains(minimumEdge.getV())) {
                answer.add(minimumEdge);
                visited.add(minimumEdge);
                current = minimumEdge.getV();
                visitedNode.add(current);
                for (Map.Entry<Vertex, Integer> e
                        : g.getAdjacencies(current).entrySet()) {
                    Edge newEdge = new Edge(current, e.getKey(), e.getValue());
                    if (!(visitedNode.contains(newEdge.getV()))) {
                        edges.add(newEdge);
                    }
                }
            }
        }

        if ((g.getVertices().size() - 1) != answer.size()) {
            return null;
        }
        return answer;
    }
}
