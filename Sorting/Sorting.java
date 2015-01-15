import java.util.ArrayList;
import java.util.Random;

/**
  * Sorting implementation
  * CS 1332 : Fall 2014
  * @author David Barbet
  * @version 1.0
  */
public class Sorting implements SortingInterface {


    @Override
    public <T extends Comparable<? super T>> void bubblesort(T[] arr) {
        boolean swapOccured = false;
        if (arr.length > 1) {
            int length = arr.length;
            for (int i = 0; i < arr.length; i++) {
                for (int j = 0; j < length - 1; j++) {
                    if (arr[j].compareTo(arr[j + 1]) > 0) {
                        T next = arr[j + 1];
                        arr[j + 1] = arr[j];
                        arr[j] = next;
                        swapOccured = true;
                    }
                }
                if (!swapOccured) {
                    return;
                }
                length--;
            }
        }

    }

    @Override
    public <T extends Comparable<? super T>> void insertionsort(T[] arr) {
        for (int i = 1; i < arr.length; i++) {
            int j = i;
            T swapData = arr[i];
            int theIndex = 1;
            while (j > 0) {
                if (arr[j - 1].compareTo(swapData) > 0) {
                    arr[j] = arr[j - 1];
                    j--;
                    theIndex = j;
                } else {
                    theIndex = j;
                    j = 0;
                }
            }
            arr[theIndex] = swapData;
        }

    }

    @Override
    public <T extends Comparable<? super T>> void selectionsort(T[] arr) {
        for (int i = 0; i < arr.length - 1; i++) {
            T minElement = arr[i];
            T swapElement = arr[i];
            int swapIndex = i;
            for (int j = i + 1; j < arr.length; j++) {
                if (arr[j].compareTo(minElement) < 0) {
                    minElement = arr[j];
                    swapIndex = j;
                }
            }
            arr[swapIndex] = swapElement;
            arr[i] = minElement;
        }

    }

    @Override
    public <T extends Comparable<? super T>> void quicksort(T[] arr, Random r) {
        if (arr.length != 0) {
            quicksort2(arr, r, 0, arr.length - 1);
        }

    }
    private <T> void quicksort2(T[] arr, Random r, int bot, int top) {
        if (bot < top) {
            int newIndex = halve(arr, r, bot, top);
            quicksort2(arr, r, bot, newIndex - 1);
            quicksort2(arr, r, newIndex + 1, top);
        }
    }
    private <T> int halve(T[] arr, Random r, int bot, int top) {
        int pivotIndex = r.nextInt(top - bot) + bot;
        T pivot = arr[pivotIndex];
        T topData = arr[top];
        arr[top] = pivot;
        arr[pivotIndex] = topData;
        int theIndex = bot;
        for (int i = bot; i < top; i++) {
            if (((Comparable) arr[i]).compareTo(pivot) < 0) {
                T curData = arr[i];
                arr[i] = arr[theIndex];
                arr[theIndex] = curData;
                theIndex++;
            }
        }
        T indexData = arr[theIndex];
        arr[theIndex] = arr[top];
        arr[top] = indexData;
        return theIndex;
    }

    @Override
    public <T extends Comparable<? super T>> void mergesort(T[] arr) {
        mergeSort2(arr, arr.length, 0, arr.length - 1);
    }
    private <T> void mergeSort2(T[] arr, int length, int bot, int top) {
        if (bot < top) {
            int middleIndex = (top + bot) / 2;
            int lowerMiddle = middleIndex;
            int upperMiddle = middleIndex + 1;
            mergeSort2(arr, length, bot, lowerMiddle);
            mergeSort2(arr, length, upperMiddle, top);
            mergeArr(arr, length, bot, lowerMiddle, upperMiddle, top);
        }
    }
    private <T> void mergeArr(T[] arr, int length, int bot1,
            int bot2, int top1, int top2) {
        T[] retArr = (T[]) new Comparable[length];
        int lowerIndexBot = bot1;
        int upperIndexBot = bot2;
        int lowerIndexTop = top1;
        int upperIndexTop = top2;
        int count = lowerIndexBot;
        while ((lowerIndexBot <= upperIndexBot)
                && (lowerIndexTop <= upperIndexTop)) {
            if (((Comparable)
                    arr[lowerIndexBot]).compareTo(arr[lowerIndexTop]) <= 0) {
                retArr[count] = arr[lowerIndexBot];
                lowerIndexBot++;
                count++;
            } else {
                retArr[count] = arr[lowerIndexTop];
                lowerIndexTop++;
                count++;
            }
        }
        while (lowerIndexBot <= upperIndexBot) {
            retArr[count] = arr[lowerIndexBot];
            count++;
            lowerIndexBot++;
        }
        while (lowerIndexTop <= upperIndexTop) {
            retArr[count] = arr[lowerIndexTop];
            count++;
            lowerIndexTop++;
        }
        int copyArrLength = upperIndexTop - bot1 + 1;
        for (int i = 0; i < copyArrLength; i++) {
            arr[top2] = retArr[top2];
            top2--;
        }
    }
    @Override
    public int[] radixsort(int[] arr) {
        if (arr.length == 0) {
            return arr;
        }
        int largest = arr[0];
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] > largest) {
                largest = arr[i];
            }
        }
        int largestEx = 0;
        int curTest = 1;
        while (curTest < largest) {
            largestEx++;
            curTest = curTest * 10;
        }
        ArrayList<Integer> data = new ArrayList<Integer>();
        for (int i = 0; i < arr.length; i++) {
            data.add(arr[i]);
        }
        int curBase = 1;
        for (int i = 0; i <= largestEx; i++) {
            /**
            *There is definitely a better way to do this.
            *Good thing this assignment didn't care about space efficiency.
            */
            ArrayList<Integer> zero = new ArrayList<Integer>();
            ArrayList<Integer> one = new ArrayList<Integer>();
            ArrayList<Integer> two = new ArrayList<Integer>();
            ArrayList<Integer> three = new ArrayList<Integer>();
            ArrayList<Integer> four = new ArrayList<Integer>();
            ArrayList<Integer> five = new ArrayList<Integer>();
            ArrayList<Integer> six = new ArrayList<Integer>();
            ArrayList<Integer> seven = new ArrayList<Integer>();
            ArrayList<Integer> eight = new ArrayList<Integer>();
            ArrayList<Integer> nine = new ArrayList<Integer>();
            ArrayList<Integer> negzero = new ArrayList<Integer>();
            ArrayList<Integer> negone = new ArrayList<Integer>();
            ArrayList<Integer> negtwo = new ArrayList<Integer>();
            ArrayList<Integer> negthree = new ArrayList<Integer>();
            ArrayList<Integer> negfour = new ArrayList<Integer>();
            ArrayList<Integer> negfive = new ArrayList<Integer>();
            ArrayList<Integer> negsix = new ArrayList<Integer>();
            ArrayList<Integer> negseven = new ArrayList<Integer>();
            ArrayList<Integer> negeight = new ArrayList<Integer>();
            ArrayList<Integer> negnine = new ArrayList<Integer>();
            for (int j = 0; j < data.size(); j++) {
                int currBuckNum = Math.abs((data.get(j) / curBase) % 10);
                if (data.get(j) < 0) {
                    /**
                    *This is definitely messy and not a good way to do this, but it works.
                    */
                    if (currBuckNum == 0) {
                        negzero.add(data.get(j));
                    }
                    if (currBuckNum == 1) {
                        negone.add(data.get(j));
                    }
                    if (currBuckNum == 2) {
                        negtwo.add(data.get(j));
                    }
                    if (currBuckNum == 3) {
                        negthree.add(data.get(j));
                    }
                    if (currBuckNum == 4) {
                        negfour.add(data.get(j));
                    }
                    if (currBuckNum == 5) {
                        negfive.add(data.get(j));
                    }
                    if (currBuckNum == 6) {
                        negsix.add(data.get(j));
                    }
                    if (currBuckNum == 7) {
                        negseven.add(data.get(j));
                    }
                    if (currBuckNum == 8) {
                        negeight.add(data.get(j));
                    }
                    if (currBuckNum == 9) {
                        negnine.add(data.get(j));
                    }
                } else {
                    if (currBuckNum == 0) {
                        zero.add(data.get(j));
                    }
                    if (currBuckNum == 1) {
                        one.add(data.get(j));
                    }
                    if (currBuckNum == 2) {
                        two.add(data.get(j));
                    }
                    if (currBuckNum == 3) {
                        three.add(data.get(j));
                    }
                    if (currBuckNum == 4) {
                        four.add(data.get(j));
                    }
                    if (currBuckNum == 5) {
                        five.add(data.get(j));
                    }
                    if (currBuckNum == 6) {
                        six.add(data.get(j));
                    }
                    if (currBuckNum == 7) {
                        seven.add(data.get(j));
                    }
                    if (currBuckNum == 8) {
                        eight.add(data.get(j));
                    }
                    if (currBuckNum == 9) {
                        nine.add(data.get(j));
                    }
                }
            }
            data = new ArrayList<Integer>();
            data.addAll(negnine);
            data.addAll(negeight);
            data.addAll(negseven);
            data.addAll(negsix);
            data.addAll(negfive);
            data.addAll(negfour);
            data.addAll(negthree);
            data.addAll(negtwo);
            data.addAll(negone);
            data.addAll(negzero);
            data.addAll(zero);
            data.addAll(one);
            data.addAll(two);
            data.addAll(three);
            data.addAll(four);
            data.addAll(five);
            data.addAll(six);
            data.addAll(seven);
            data.addAll(eight);
            data.addAll(nine);
            curBase = curBase * 10;
        }
        int[] retArr = new int[data.size()];
        for (int i = 0; i < retArr.length; i++) {
            retArr[i] = data.get(i);
        }
        return retArr;
    }

}
