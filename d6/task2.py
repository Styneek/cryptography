def szybkiePotegowanie(podstawa, wykladnik, modul):
    wynik = 1
    podstawa = podstawa % modul
    
    while wykladnik > 0:
        if wykladnik % 2 == 1:
            wynik = (wynik * podstawa) % modul
            
        wykladnik = wykladnik // 2
        podstawa = (podstawa * podstawa) % modul
        
    return wynik

def znajdzSwiadkow():
    daneWejsciowe = input().split()
    n = int(daneWejsciowe[0])
    k = int(daneWejsciowe[1])
    
    swiadkowie = []
    
    for a in range(2, k + 1):
        if szybkiePotegowanie(a, n - 1, n) != 1:
            swiadkowie.append(a)
            
    print(len(swiadkowie))
    
    if len(swiadkowie) > 0:
        print(" ".join(map(str, swiadkowie)))

if __name__ == "__main__":
    znajdzSwiadkow()