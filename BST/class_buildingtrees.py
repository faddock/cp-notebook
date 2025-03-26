import sys
import bisect

def main():
    n = int(input())
    a = list(map(int, input().split()))
    
    sorted_list = []
    sorted_list.append(a[0])
    
    parents = {}
    output = []
    
    for i in range(1, n):
        current = a[i]
        pos = bisect.bisect_left(sorted_list, current)
        if pos == 0:
            parent = sorted_list[0]
        elif pos == len(sorted_list):
            parent = sorted_list[-1]
        else:
            left_neighbor = sorted_list[pos - 1]
            right_neighbor = sorted_list[pos]
            if current < right_neighbor:
                parent = left_neighbor
            else:
                parent = right_neighbor
        bisect.insort(sorted_list, current)
        output.append(str(parent))
    
    print(' '.join(output))

if __name__ == "__main__":
    main()