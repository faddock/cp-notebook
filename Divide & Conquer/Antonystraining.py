# similar to famous question - counting the number of inversions
# when s = 0 - its basically counting the number of inversions
# 5, -1, 3, 4, -1
# 0, 5, 4, 7, 11, 10
# above is the prefix sum array
# s = 4
# do mergesort - during the merging step count the number of inversions
# inversion is Ai > Aj when i < j

# def solve():
#     n, s = map(int, input().split())
#     arr = list(map(int, input().split()))

#     prefix_arr = []
#     count = 0

#     for i in range(n):
#         prefix_set = set(prefix_arr[:i])
#         if arr[i] < s:
#             count += 1
#         sum += arr[right]

#         while (sum >= s and left <= right):
#             sum -= arr[left]
#             left += 1
#         res += (right - left + 1)
    
#     return count

import bisect

def main():
    import sys
    input = sys.stdin.read
    data = input().split()
    
    n = int(data[0])
    s = int(data[1])
    t = list(map(int, data[2:2 + n]))
    
    # Compute prefix sums
    pre = [0] * (n + 1)
    for i in range(1, n + 1):
        pre[i] = pre[i - 1] + t[i - 1]
    
    # Simulate a multiset using a sorted list
    prefix_list = []
    bisect.insort(prefix_list, pre[0])
    
    ans = 0
    
    for r in range(1, n + 1):
        current_pre = pre[r]
        target = current_pre - s
        
        # Count the number of prefix sums less than or equal to target
        count = bisect.bisect_right(prefix_list, target)
        ans += len(prefix_list) - count
        
        # Insert the current prefix sum into the multiset
        bisect.insort(prefix_list, current_pre)
    
    print(ans)

if __name__ == "__main__":
    main()