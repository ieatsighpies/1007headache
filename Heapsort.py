import random

def print_heap(arr):
    print("Heap Tree:")
    for i in range(len(arr)):
        print(arr[i], end=' ')
        if (i + 2) & (i + 1) == 0:  # Check if i + 1 is a power of 2
            print()

def heapify(arr, n, i):
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2

    if left < n and arr[i] < arr[left]:
        largest = left

    if right < n and arr[largest] < arr[right]:
        largest = right

    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)
    print_heap(arr)

def heapsort(arr):
    n = len(arr)

    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)

    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        heapify(arr, i, 0)

def parse_array(arr):
    parsed_arr = []
    for num in arr:
        parsed_arr.append(int(num))
    return parsed_arr

# Test the heapsort and parse_array functions
arr = [9, 3, 9, 10, 4, 2, 6]
parsed_arr = parse_array(arr)
heapsort(parsed_arr)
print(parsed_arr)
def constructHeap(arr, H):
    for num in arr:
        H.insert(num)
    heapifying(H)

def heapifying(H):
    if not H.isLeaf():
        heapifying(H.leftChild())
        heapifying(H.rightChild())
        k = H.root()
        fixHeap(H, k)

def fixHeap(H, temp):
    if H.isLeaf():
        H.insert(temp)
    else:
        largerSubHeap = H.leftChild() if H.leftChild().root() >= H.rightChild().root() else H.rightChild()
        if temp >= largerSubHeap.root():
            H.insert(temp)
        else:
            H.insert(largerSubHeap.root())
            fixHeap(largerSubHeap, temp)

def deleteMax(H):
    temp = H.rightmostElement()
    H.deleteRightmostElement()
    fixHeap(H, temp)

def heapSort(arr):
    n = len(arr)
    H = Heap()
    constructHeap(arr, H)
    for i in range(n, 0, -1):
        curMax = H.getMax()
        deleteMax(H)
        arr[i-1] = curMax
import heapq

class Heap:
    def __init__(self):
        self.heap = []
        self.comparisons = 0

    def insert(self, item):
        self.comparisons += 1
        heapq.heappush(self.heap, -item)  # Negate item for max heap

    def deleteRightmostElement(self):
        self.comparisons += 1
        return -heapq.heappop(self.heap)  # Negate again to return original value

    def isLeaf(self):
        return len(self.heap) <= 1

    def leftChild(self):
        self.comparisons += 1
        return -self.heap[1] if len(self.heap) > 1 else None

    def rightChild(self):
        self.comparisons += 1
        return -self.heap[2] if len(self.heap) > 2 else None

    def root(self):
        self.comparisons += 1
        return -self.heap[0] if self.heap else None

    def getMax(self):
        self.comparisons += 1
        return self.root()

    def rightmostElement(self):
        self.comparisons += 1
        return -self.heap[-1] if self.heap else None
# Test the heapSort function
arr = [9, 3, 9, 10, 4, 2, 6]
heapSort(arr)
print(arr)
