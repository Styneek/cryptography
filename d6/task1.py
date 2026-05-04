def szybkiePotegowanie(podstawa, wykladnik, modul):
    wynik = 1
    podstawa = podstawa % modul
    
    while wykladnik > 0:
        if wykladnik % 2 == 1:
            wynik = (wynik * podstawa) % modul
            
        wykladnik = wykladnik // 2
        podstawa = (podstawa * podstawa) % modul
        
    return wynik

def testFermata():
    daneWejsciowe = input().split()
    n = int(daneWejsciowe[0])
    a = int(daneWejsciowe[1])
    
    wynikTestu = szybkiePotegowanie(a, n - 1, n)
    
    if wynikTestu == 1:
        print("probably_prime")
    else:
        print("definitely_composite")

if __name__ == "__main__":
    testFermata()