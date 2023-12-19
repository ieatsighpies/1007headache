def partition(arr, low, high):
    mid = (low + high) // 2
    arr[low], arr[mid] = arr[mid], arr[low]  # swap mid with low
    pivot = arr[low]
    last_leftSL = low

    for i in range(low + 1, high + 1):
        if arr[i] < pivot:
            last_leftSL += 1
            arr[last_leftSL], arr[i] = arr[i], arr[last_leftSL]
        print(f"Iteration {i - low}: {arr}")

    arr[low], arr[last_leftSL] = arr[last_leftSL], arr[low]
    return last_leftSL

def qsort(arr, n, m):
    if n >= m:
        return

    pivot = partition(arr, n, m)
    qsort(arr, n, pivot - 1)
    qsort(arr, pivot + 1, m)

# Test the qsort function
arr = [24,16,26,2,24,10,18,8,19,28,30,6]
qsort(arr, 0, len(arr) - 1)
print("The final array is thus " + str(arr))
