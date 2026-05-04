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

def wielorundowyMillerRabin():
    daneWejsciowe = sys.stdin.read().split()
    
    if not daneWejsciowe:
        return
        
    n = int(daneWejsciowe[0])
    r = int(daneWejsciowe[1])
    
    bazy = []
    for i in range(2, 2 + r):
        bazy.append(int(daneWejsciowe[i]))
        
    d = n - 1
    s = 0
    while d % 2 == 0:
        d //= 2
        s += 1
        
    for i in range(r):
        a = bazy[i]
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
            print(f"composite round={i + 1} base={a}")
            return
            
    print("probably_prime")

if __name__ == "__main__":
    wielorundowyMillerRabin()