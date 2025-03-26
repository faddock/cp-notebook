def main():
    import sys
    n = int(input()) 
    arr = list(map(int, input().split()))
    
    res = [-1] * n 
    stack = []
    
    for i in range(n-1, -1, -1):
        while stack and arr[i] >= stack[-1][0]:
            stack.pop()    
        if stack:
            res[i] = stack[-1][1]
        stack.append([arr[i], i+1])
        
    sys.stdout.write(" ".join(map(str, res)) + "\n")

if __name__ == "__main__":
    main()