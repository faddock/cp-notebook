import sys

def solve():
    input_data = sys.stdin.read().split()

    n = int(input_data[0])
    a = list(map(int, input_data[1:n+1]))
    ops = input_data[n+1:]

    A = a * 2
    Ops = ops * 2
    size = 2 * n

    # dp_min[i][j]: minimum value achievable from index i to j
    # dp_max[i][j]: maximum value achievable from index i to j
    dp_min = [[0] * size for _ in range(size)]
    dp_max = [[0] * size for _ in range(size)]
    
    # Base case: segments of length 1
    for i in range(size):
        dp_min[i][i] = dp_max[i][i] = A[i]
    
    for length in range(2, n + 1):
        for i in range(0, size - length + 1):
            j = i + length - 1
            min_val = float('inf')
            max_val = float('-inf')
            
            for k in range(i, j):
                op = Ops[k]
                left_min, left_max = dp_min[i][k], dp_max[i][k]
                right_min, right_max = dp_min[k + 1][j], dp_max[k + 1][j]
                
                if op == '+':
                    c1 = left_min + right_min
                    c2 = left_min + right_max
                    c3 = left_max + right_min
                    c4 = left_max + right_max
                else:  # op == '*'
                    c1 = left_min * right_min
                    c2 = left_min * right_max
                    c3 = left_max * right_min
                    c4 = left_max * right_max

                min_val = min(min_val, c1, c2, c3, c4)
                max_val = max(max_val, c1, c2, c3, c4)
            
            dp_min[i][j] = min_val
            dp_max[i][j] = max_val

    result = float('-inf')
    for i in range(n):
        result = max(result, dp_max[i][i + n - 1])
    
    print(result)

if __name__ == "__main__":
    solve()