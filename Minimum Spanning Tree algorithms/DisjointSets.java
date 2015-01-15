import java.util.HashMap;
import java.util.Map;
import java.util.Set;
/**
*@author David Barbet
*/
public class DisjointSets<T> implements DisjointSetsInterface<T> {
    //Should be a map of data to its parent; root data maps to itself.
    private Map<T, Node> set;

    /**
     * @param setItems the initial items (sameSet and merge will never be called
     * with items not in this set, this set will never contain null elements).
     */
    public DisjointSets(Set<T> setItems) {
        set = new HashMap<T, Node>();
        for (T item : setItems) {
            Node newNode = new Node();
            newNode.setParent(item);
            set.put(item, newNode);
        }
    }

    @Override
    public boolean sameSet(T u, T v) {
        if ((null == u) || (null == v)) {
            throw new IllegalArgumentException();
        }
        return find(u).equals(find(v));
    }
    private T find(T data) {
        Node aNode = set.get(data);
        if (!aNode.getParent().equals(data) && (aNode != null)) {
            aNode.setParent(find(aNode.parent));
        }
        return aNode.getParent();
    }

    @Override
    public void merge(T u, T v) {
        if ((null == u) || (null == v)) {
            throw new IllegalArgumentException();
        }
        if (!sameSet(u, v)) {
            Node uNode = set.get(u);
            Node vNode = set.get(v);
            if (uNode.getRank() < vNode.getRank()) {
                uNode.setParent(v);
            } else if (uNode.getRank() > vNode.getRank()) {
                vNode.setParent(u);
            } else {
                vNode.setParent(u);
                vNode.setRank(vNode.getRank() + 1);
            }
        }
    }

    private class Node {
        private T parent;
        private int rank;
        /**
         * Creates Node with initial rank of 0
         */
        private Node() {
            rank = 0;
        }
        /**
         * Sets the parent of  a certain node.
         * @param data the new parent
         */
        private void setParent(T data) {
            parent = data;
        }
        /**
         * Sets the rank of a node
         * @param aRank the new rank
         */
        private void setRank(int aRank) {
            rank = aRank;
        }
        /**
         * Returns the parent of a node
         * @return the parent data
         */
        private T getParent() {
            return parent;
        }
        /**
         * Returns the rank of the node
         * @return integer rank
         */
        private int getRank() {
            return rank;
        }
    }
}
