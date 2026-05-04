import sys
import hashlib

def main():
    daneWejsciowe = sys.stdin.read().split('\n')
    if not daneWejsciowe or daneWejsciowe[0] == "":
        return

    nazwaAlgorytmu = daneWejsciowe[0].strip()
    liczbaPar = int(daneWejsciowe[1].strip())
    
    liczbaBitow = 0
    if nazwaAlgorytmu == "MD5":
        liczbaBitow = 128
    elif nazwaAlgorytmu == "SHA-1":
        liczbaBitow = 160
    elif nazwaAlgorytmu in ("SHA-256", "SHA3-256", "BLAKE2S"):
        liczbaBitow = 256

    sumaRoznic = 0
    maksRoznic = -1
    indeksMaks = -1

    for i in range(liczbaPar):
        indeksPierwszego = 2 + 2 * i
        indeksDrugiego = 3 + 2 * i
        
        tekst1 = daneWejsciowe[indeksPierwszego] if indeksPierwszego < len(daneWejsciowe) else ""
        tekst2 = daneWejsciowe[indeksDrugiego] if indeksDrugiego < len(daneWejsciowe) else ""
        
        bajty1 = tekst1.encode('utf-8')
        bajty2 = tekst2.encode('utf-8')
        
        if nazwaAlgorytmu == "MD5":
            skrot1 = hashlib.md5(bajty1).hexdigest()
            skrot2 = hashlib.md5(bajty2).hexdigest()
        elif nazwaAlgorytmu == "SHA-1":
            skrot1 = hashlib.sha1(bajty1).hexdigest()
            skrot2 = hashlib.sha1(bajty2).hexdigest()
        elif nazwaAlgorytmu == "SHA-256":
            skrot1 = hashlib.sha256(bajty1).hexdigest()
            skrot2 = hashlib.sha256(bajty2).hexdigest()
        elif nazwaAlgorytmu == "SHA3-256":
            skrot1 = hashlib.sha3_256(bajty1).hexdigest()
            skrot2 = hashlib.sha3_256(bajty2).hexdigest()
        elif nazwaAlgorytmu == "BLAKE2S":
            skrot1 = hashlib.blake2s(bajty1).hexdigest()
            skrot2 = hashlib.blake2s(bajty2).hexdigest()
        
        rozniaceSieBity = bin(int(skrot1, 16) ^ int(skrot2, 16)).count('1')
        
        sumaRoznic += rozniaceSieBity
        if rozniaceSieBity > maksRoznic:
            maksRoznic = rozniaceSieBity
            indeksMaks = i + 1

    if liczbaPar > 0:
        sredniaProcent = (sumaRoznic / (liczbaPar * liczbaBitow)) * 100
        maksProcent = (maksRoznic / liczbaBitow) * 100
    else:
        sredniaProcent = 0.0
        maksProcent = 0.0

    print(f"{sredniaProcent:.2f}%")
    print(indeksMaks)
    print(maksRoznic)
    print(f"{maksProcent:.2f}%")

if __name__ == "__main__":
    main()