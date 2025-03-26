from collections import deque

def solve():
    import sys
    n, m = list(map(int, input().split()))
    arr = list(map(int, input().split()))

    result = []
    dq = deque()
    pl = 0
    pr = 0

    for i in range(m):
        l, r = list(map(int, input().split()))

        while pr < r:
            while dq and arr[pr] >= arr[dq[-1]]:
                dq.pop()
            dq.append(pr)
            pr += 1
        
        while pl < l-1:
            if dq[0] == pl:
                dq.popleft()
            pl += 1
        
        print(arr[dq[0]])
    

if __name__ == "__main__":
    solve()

