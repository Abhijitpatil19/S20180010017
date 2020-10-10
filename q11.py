import random

# Abhijit Prakash Patil
# S20180010001

if __name__ == "__main__":
    n = int(input())
    m = int(input())
    chooserMain = []
    vMain = []
    par = []
    for i in range(n):
        new = [0]*n
        vMain.append(new)
        par.append(-1)
    
    for i in range(m):
        a = list(map(int, input().split()))
        vMain[a[0]][a[1]] = 1
        vMain[a[1]][a[0]] = 1
        chooserMain.append([a[0], a[1]])

    test = 10000
    minAns = 1e4
    countAns = 0
    for t in range(test):
        par = []
        chooser = []
        v = []
        for i in range(n):
            par.append(-1)
        for i in chooserMain:
            chooser.append(i)
        for i in range(n):
            new = []
            for j in range(n):
                temp = vMain[i][j]
                new.append(temp)
            v.append(new)
                
        vertices = n
        while vertices > 2:
            choice = random.choice(chooser)
            chooser.remove(choice)
            setA = choice[0]
            while par[setA] != -1:
                setA = par[setA]

            if choice[0] != setA:
                par[choice[0]] = setA

            setB = choice[1]
            while par[setB] != -1:
                setB = par[setB]

            if choice[1] != setB:
                par[choice[1]] = setB
            
            if setA != setB:
                vertices -= 1
                for i in range(n):
                    if i != setA and i != setB:
                        v[setA][i] += v[setB][i]
                        v[i][setA] += v[i][setB]
                par[setB] = setA

        ans = []
        # print(par)
        for i in range(n):
            if par[i] == -1:
                ans.append(i)
        # print(minAns, v[ans[0]][ans[1]], par,countAns, sep=" ")
        if minAns > v[ans[0]][ans[1]]:
            countAns = 1
            minAns = v[ans[0]][ans[1]]
        elif minAns == v[ans[0]][ans[1]]:
            countAns += 1

    print("total tests", test, sep=" ")
    print("Number of correct Ans:", countAns, sep=" ")
    print("percentage correct:", (float)((countAns/test)*100), sep=" ")

            

        
