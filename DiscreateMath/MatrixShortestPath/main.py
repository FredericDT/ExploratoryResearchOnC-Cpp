MAX_N = 2147483647

def m(a, b):
    r = [[MAX_N for i in range(len(a))] for j in range(len(b[0]))]
    for i in range(len(a)):
        for j in range(len(b[0])):
            s = MAX_N
            for k in range(len(b)):
                s = min(s, a[i][k] + b[k][j])
            r[i][j] = s
    return r

