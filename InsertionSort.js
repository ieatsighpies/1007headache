function insertionSort(arr) {
    let count = 0;
    let n = arr.length;

    for (let i = 1; i < n; i++) {
        for (let j = i; j > 0; j--) {
            if (arr[j] < arr[j - 1]) {
                // Swap arr[j] and arr[j - 1]
                let temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
                count++;
            } else {
                break;
            }
        }
    }

    return { sortedArray: arr, iterations: count };
}

const inputArray = [3, 9, 9, 10, 4, 2, 6];
const result = insertionSort(inputArray);

console.log("Sorted Array:", result.sortedArray);
console.log("Number of iterations:", result.iterations);