import sys
import hashlib

def obliczSkrot(bajtyTekstu, nazwaAlgorytmu):
    if nazwaAlgorytmu == "MD5":
        return hashlib.md5(bajtyTekstu).hexdigest()
    elif nazwaAlgorytmu == "SHA-1":
        return hashlib.sha1(bajtyTekstu).hexdigest()
    elif nazwaAlgorytmu == "SHA-256":
        return hashlib.sha256(bajtyTekstu).hexdigest()
    elif nazwaAlgorytmu == "SHA3-256":
        return hashlib.sha3_256(bajtyTekstu).hexdigest()
    elif nazwaAlgorytmu == "BLAKE2S":
        return hashlib.blake2s(bajtyTekstu).hexdigest()
    return ""

def obliczKorzen(liscie, nazwaAlgorytmu):
    if not liscie:
        return ""
    if len(liscie) == 1:
        return liscie[0]
        
    aktualnyPoziom = liscie[:]
    while len(aktualnyPoziom) > 1:
        nastepnyPoziom = []
        for i in range(0, len(aktualnyPoziom), 2):
            lewy = aktualnyPoziom[i]
            prawy = aktualnyPoziom[i + 1] if i + 1 < len(aktualnyPoziom) else aktualnyPoziom[i]
            nastepnyPoziom.append(obliczSkrot((lewy + prawy).encode('utf-8'), nazwaAlgorytmu))
        aktualnyPoziom = nastepnyPoziom
        
    return aktualnyPoziom[0]

def main():
    daneWejsciowe = sys.stdin.read().splitlines()
    if not daneWejsciowe:
        return

    nazwaAlgorytmu = daneWejsciowe[0].strip()
    liczbaPolecen = int(daneWejsciowe[1].strip())
    
    liczbaBitow = 0
    if nazwaAlgorytmu == "MD5":
        liczbaBitow = 128
    elif nazwaAlgorytmu == "SHA-1":
        liczbaBitow = 160
    elif nazwaAlgorytmu in ("SHA-256", "SHA3-256", "BLAKE2S"):
        liczbaBitow = 256

    zapisanaSol = None
    zapisanySkrotHasla = None
    czyZalogowany = False
    
    liscieDrzewa = []
    indeksyDokumentow = {}
    
    for i in range(liczbaPolecen):
        if 2 + i >= len(daneWejsciowe):
            break
            
        elementy = daneWejsciowe[2 + i].strip().split()
        if not elementy:
            continue
            
        operacja = elementy[0]

        if operacja == "REGISTER":
            sol = elementy[1]
            haslo = elementy[2]
            if zapisanaSol is not None:
                print("EXISTS")
            else:
                skrot = obliczSkrot((sol + ":" + haslo).encode('utf-8'), nazwaAlgorytmu)
                zapisanaSol = sol
                zapisanySkrotHasla = skrot
                print("OK")
                
        elif operacja == "LOGIN":
            haslo = elementy[1]
            if zapisanaSol is None:
                print("NOAUTH")
            else:
                skrot = obliczSkrot((zapisanaSol + ":" + haslo).encode('utf-8'), nazwaAlgorytmu)
                if skrot == zapisanySkrotHasla:
                    czyZalogowany = True
                    print("OK")
                else:
                    czyZalogowany = False
                    print("FAIL")
                    
        elif operacja == "ADD":
            if not czyZalogowany:
                print("NOAUTH")
                continue
                
            nazwaDokumentu = elementy[1]
            trescDokumentu = elementy[2]
            skrotTresci = obliczSkrot(trescDokumentu.encode('utf-8'), nazwaAlgorytmu)
            
            if nazwaDokumentu in indeksyDokumentow:
                indeks = indeksyDokumentow[nazwaDokumentu]
                liscieDrzewa[indeks] = skrotTresci
            else:
                indeksyDokumentow[nazwaDokumentu] = len(liscieDrzewa)
                liscieDrzewa.append(skrotTresci)
                
            print(skrotTresci)
            
        elif operacja == "ROOT":
            if not czyZalogowany:
                print("NOAUTH")
            elif not liscieDrzewa:
                print("EMPTY")
            else:
                korzen = obliczKorzen(liscieDrzewa, nazwaAlgorytmu)
                print(korzen)
                
        elif operacja == "VERIFY":
            if not czyZalogowany:
                print("NOAUTH")
                continue
                
            nazwaDokumentu = elementy[1]
            trescDokumentu = elementy[2]
            
            if nazwaDokumentu not in indeksyDokumentow:
                print("TAMPERED")
            else:
                indeks = indeksyDokumentow[nazwaDokumentu]
                zapisanySkrotDokumentu = liscieDrzewa[indeks]
                podanySkrotDokumentu = obliczSkrot(trescDokumentu.encode('utf-8'), nazwaAlgorytmu)
                
                if podanySkrotDokumentu == zapisanySkrotDokumentu:
                    print("OK")
                else:
                    print("TAMPERED")
                    
        elif operacja == "AVALANCHE":
            tekst1 = elementy[1]
            tekst2 = elementy[2]
            
            skrot1 = obliczSkrot(tekst1.encode('utf-8'), nazwaAlgorytmu)
            skrot2 = obliczSkrot(tekst2.encode('utf-8'), nazwaAlgorytmu)
            
            rozniaceSieBity = bin(int(skrot1, 16) ^ int(skrot2, 16)).count('1')
            procentRuznic = (rozniaceSieBity / liczbaBitow) * 100
            
            print(f"{procentRuznic:.2f}%".replace('.', '.')) 

if __name__ == "__main__":
    main()