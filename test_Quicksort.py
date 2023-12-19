def partition(arr, low, high):
    # Implementation of partition function

def qsort(arr, n, m):
    # Implementation of quicksort function

def generate_tests():
    tests = [
        # Test case 1
        {
            'input': [4, 2, 7, 1, 5],
            'expected': [1, 2, 4, 5, 7],
        },
        # Test case 2
        {
            'input': [9, 3, 6, 8, 2, 1],
            'expected': [1, 2, 3, 6, 8, 9],
        },
        # Add more test cases here
    ]

    for test in tests:
        arr = test['input'].copy()
        n = 0
        m = len(arr) - 1
        comparisons = [0]  # List to store the number of comparisons

        qsort(arr, n, m, comparisons)

        # Check if the sorted array matches the expected result
        if arr == test['expected']:
            print("Test Passed")
        else:
            print("Test Failed")

        # Print the number of key comparisons
        print("Number of key comparisons:", comparisons[0])

generate_tests()