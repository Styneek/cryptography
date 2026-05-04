import sys

def dekompozycja():
    daneWejsciowe = sys.stdin.read().split()
    
    if not daneWejsciowe:
        return
        
    t = int(daneWejsciowe[0])
    indeks = 1
    
    for _ in range(t):
        if indeks >= len(daneWejsciowe):
            break
            
        n = int(daneWejsciowe[indeks])
        indeks += 1
        
        x = n - 1
        s = 0
        
        while x % 2 == 0:
            x = x // 2
            s += 1
            
        d = x
        print(f"{s} {d}")

if __name__ == "__main__":
    dekompozycja()