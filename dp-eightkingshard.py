def is_valid(mask, m):
    # Check that no two kings are adjacent horizontally in the mask.
    return (mask & (mask << 1)) == 0

def popcount(mask):
    return bin(mask).count("1")

# Read board dimensions and kings count.
n, m, k = map(int, input().split())

# Precompute all valid masks for a row of length m.
valid_masks = [mask for mask in range(1 << m) if is_valid(mask, m)]

# Precompute allowed transitions:
# allowed[prev_mask] holds a list of cur_masks that are compatible with prev_mask.
allowed = {}
for prev_mask in valid_masks:
    allowed[prev_mask] = []
    for cur_mask in valid_masks:
        # Check if current row's mask is safe relative to previous row's kings.
        if ((prev_mask << 1) | prev_mask | (prev_mask >> 1)) & cur_mask == 0:
            allowed[prev_mask].append(cur_mask)

# Initialize the DP.
# We'll use a list of dictionaries:
# dp[row][mask][king_count] gives the number of ways for that state.
dp = [ {mask: {} for mask in valid_masks} for _ in range(n + 1) ]
# Base case: before placing any rows, consider previous row mask as 0 (empty).
dp[0][0][0] = 1

# Iterate over each row.
for row in range(n):
    # For each possible previous row mask.
    for prev_mask in valid_masks:
        for placed in dp[row][prev_mask]:
            ways = dp[row][prev_mask][placed]
            # Try every valid current mask allowed from prev_mask.
            for cur_mask in allowed.get(prev_mask, []):
                new_count = placed + popcount(cur_mask)
                if new_count <= k:
                    dp[row + 1][cur_mask][new_count] = dp[row + 1][cur_mask].get(new_count, 0) + ways

# Sum up all ways for the last row with exactly k kings.
ans = sum(dp[n][mask].get(k, 0) for mask in valid_masks)
print(ans)