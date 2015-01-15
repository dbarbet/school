import java.util.Random;

/**
 * Sorting Algorithms.
 */
public interface SortingInterface {

    /**
     * Bubble sort.
     * @param arr unsorted input array.
     */
    public <T extends Comparable<? super T>> void bubblesort(T[] arr);

    /**
     * Insertion sort.
     * @param arr unsorted input array.
     */
    public <T extends Comparable<? super T>> void insertionsort(T[] arr);


    /**
     * In-place selection sort.
     * @param arr unsorted input array.
     */
    public <T extends Comparable<? super T>> void selectionsort(T[] arr);

    /**
     * In place quick sort.
     * @param arr unsorted input array.
     */
    public <T extends Comparable<? super T>> void quicksort(T[] arr, Random r);

    /**
     * Stable merge sort.
     * @param arr unsorted input array.
     */
    public <T extends Comparable<? super T>> void mergesort(T[] arr);

    /**
     * Radix sort.
     * @param arr unsorted input array.
     * @return the sorted output array.
     */
    public int[] radixsort(int[] arr);
}
