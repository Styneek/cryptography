import sys
import hashlib

def main():
    daneWejsciowe = sys.stdin.read().splitlines()
    if not daneWejsciowe:
        return

    nazwaAlgorytmu = daneWejsciowe[0].strip()
    liczbaZnakow = int(daneWejsciowe[1].strip())
    liczbaTekstow = int(daneWejsciowe[2].strip())

    wystapieniaSkrotow = {}

    for i in range(liczbaTekstow):
        tekst = daneWejsciowe[3 + i] if (3 + i) < len(daneWejsciowe) else ""
        bajtyTekstu = tekst.encode('utf-8')
        
        if nazwaAlgorytmu == "MD5":
            pelnySkrot = hashlib.md5(bajtyTekstu).hexdigest()
        elif nazwaAlgorytmu == "SHA-1":
            pelnySkrot = hashlib.sha1(bajtyTekstu).hexdigest()
        elif nazwaAlgorytmu == "SHA-256":
            pelnySkrot = hashlib.sha256(bajtyTekstu).hexdigest()
        elif nazwaAlgorytmu == "SHA3-256":
            pelnySkrot = hashlib.sha3_256(bajtyTekstu).hexdigest()
        elif nazwaAlgorytmu == "BLAKE2S":
            pelnySkrot = hashlib.blake2s(bajtyTekstu).hexdigest()
        
        skroconySkrot = pelnySkrot[:liczbaZnakow]
        
        if skroconySkrot in wystapieniaSkrotow:
            wystapieniaSkrotow[skroconySkrot] += 1
        else:
            wystapieniaSkrotow[skroconySkrot] = 1

    liczbaKolizji = 0
    kolidujaceSkroty = []

    for skrot, wystapienia in wystapieniaSkrotow.items():
        if wystapienia >= 2:
            liczbaKolizji += (wystapienia * (wystapienia - 1)) // 2
            kolidujaceSkroty.append(skrot)

    print(liczbaKolizji)
    
    if kolidujaceSkroty:
        kolidujaceSkroty.sort()
        print(kolidujaceSkroty[0])
    else:
        print("BRAK")

if __name__ == "__main__":
    main()