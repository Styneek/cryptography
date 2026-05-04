import sys

def sprawdzKryteriumKorseleta():
    daneWejsciowe = sys.stdin.read().split()
    
    if not daneWejsciowe:
        return
        
    oryginalneN = int(daneWejsciowe[0])
    n = oryginalneN
    
    czynniki = []
    dzielnik = 2
    
    while dzielnik * dzielnik <= n:
        if n % dzielnik == 0:
            czynniki.append(dzielnik)
            while n % dzielnik == 0:
                n //= dzielnik
        dzielnik += 1
        
    if n > 1:
        czynniki.append(n)
        
    if len(czynniki) < 2:
        print("not_carmichael")
        return
        
    iloczyn = 1
    for czynnik in czynniki:
        iloczyn *= czynnik
        
    if iloczyn != oryginalneN:
        print("not_carmichael")
        return
        
    for czynnik in czynniki:
        if (oryginalneN - 1) % (czynnik - 1) != 0:
            print("not_carmichael")
            return
            
    print("carmichael")

if __name__ == "__main__":
    sprawdzKryteriumKorseleta()