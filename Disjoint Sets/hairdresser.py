class UnionFind():
    def __init__(self, n):
        self.parent = [i for i in range(n)]
        self.rank = [1 for _ in range(n)]

    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def union(self, x, y):
        px = self.find(x)
        py = self.find(y)
    
        if px == py:
            return False
        else:
            if self.rank[px] > self.rank[py]:
                self.parent[py] = px
                self.rank[px] += self.rank[py]
            else:
                self.parent[px] = py
                self.rank[py] += self.rank[px]
            return True


# def main():
#     n, m, l = list(map(int, input().split()))
#     res = []
#     arr = list(map(int, input().split()))
#     uf = UnionFind(int(n))
#     for i in range(m):
#         line = list(map(int, input().split()))
#         if line[0] == 0:
#             if i > 0 and arr[i-1] > l and arr[i] > l:
#                 uf.union(i-1, i)
#                 count -= 1
            
#             if i < n-1 and arr[i+1] > l and arr[i] > l:
#                 uf.union(i, i+1)
#                 count -= 1
#             print(count)
#         elif line[0] == 1:
#             arr[line[1]] += line[2]
    
#     return 0
        
def main():
    import sys
    input_data = sys.stdin.read().split()
    it = iter(input_data)
    n = int(next(it))
    m = int(next(it))
    l = int(next(it))
    arr = [int(next(it)) for _ in range(n)]
    
    above = [a > l for a in arr]
    
    segments = 0
    for i in range(n):
        if above[i] and (i == 0 or not above[i-1]):
            segments += 1
    
    output_lines = []
    for _ in range(m):
        t = int(next(it))
        if t == 0:
            output_lines.append(str(segments))
        elif t == 1: # 1 p d
            p = int(next(it)) - 1  # zero indexing
            d = int(next(it))
            
            if not above[p] and arr[p] + d > l:
                above[p] = True
                segments += 1
                if p > 0 and above[p-1]:  # left merge
                    segments -= 1
                if p < n - 1 and above[p+1]: # right merge
                    segments -= 1
            arr[p] += d

    sys.stdout.write("\n".join(output_lines) + "\n")
    
if __name__ == '__main__':
    main()         