def main():
    import sys
    l, r = list(map(int, input().split()))
    
    res = 0
    for i in range(l, r+1):
        if "495" in str(i):
            res += 1
    print (res)

if __name__ == "__main__":
    main()
            
