import sys, math

def cross(ax, ay, bx, by):
    return ax * by - ay * bx

def convex_hull(pts):
    pts = sorted(set(pts))
    if len(pts) <= 1:
        return pts
    def cw(o, a, b):   
        return cross(a[0]-o[0], a[1]-o[1], b[0]-o[0], b[1]-o[1]) <= 0
    lower = []
    for p in pts:
        while len(lower) >= 2 and cw(lower[-2], lower[-1], p):
            lower.pop()
        lower.append(p)
    upper = []
    for p in reversed(pts):
        while len(upper) >= 2 and cw(upper[-2], upper[-1], p):
            upper.pop()
        upper.append(p)
    return lower[:-1] + upper[:-1]          # CCW order

def minimal_time(n, A, B, points):
    x_max = max(a for a, _ in points)
    y_max = max(b for _, b in points)
    points += [(x_max, 0), (0, y_max)]      # extend with two axis points
    hull = convex_hull(points)

    d = (A, B)
    t_max = 0.0
    m = len(hull)
    for i in range(m):
        px, py = hull[i]
        qx, qy = hull[(i + 1) % m]
        ex, ey = qx - px, qy - py
        den = cross(d[0], d[1], ex, ey)
        if abs(den) < 1e-20:
            continue                        # parallel
        t = cross(px, py, ex, ey) / den
        s = cross(px, py, d[0], d[1]) / den
        if t > 0 and -1e-12 <= s <= 1 + 1e-12:
            t_max = max(t_max, t)

    return 1.0 / t_max

def main():
    it = iter(map(int, sys.stdin.read().strip().split()))
    n, A, B = next(it), next(it), next(it)
    pts = [(next(it), next(it)) for _ in range(n)]
    ans = minimal_time(n, A, B, pts)
    print(f"{ans:.15f}")

if __name__ == "__main__":
    main()