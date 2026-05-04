import sys

def szybkiePotegowanie(podstawa, wykladnik, modul):
    wynik = 1
    podstawa = podstawa % modul
    
    while wykladnik > 0:
        if wykladnik % 2 == 1:
            wynik = (wynik * podstawa) % modul
            
        wykladnik = wykladnik // 2
        podstawa = (podstawa * podstawa) % modul
        
    return wynik

def deterministycznyMillerRabin():
    daneWejsciowe = sys.stdin.read().split()
    
    if not daneWejsciowe:
        return
        
    n = int(daneWejsciowe[0])
    
    if n % 2 == 0:
        print("composite")
        return
        
    bazy = [2, 3, 5, 7, 11, 13, 17, 19, 23]
    
    d = n - 1
    s = 0
    while d % 2 == 0:
        d //= 2
        s += 1
        
    for a in bazy:
        if a >= n:
            break
            
        x = szybkiePotegowanie(a, d, n)
        
        rundaZaliczona = False
        
        if x == 1 or x == n - 1:
            rundaZaliczona = True
        else:
            for j in range(s - 1):
                x = (x * x) % n
                if x == n - 1:
                    rundaZaliczona = True
                    break
                    
        if not rundaZaliczona:
            print("composite")
            return
            
    print("prime")

if __name__ == "__main__":
    deterministycznyMillerRabin()