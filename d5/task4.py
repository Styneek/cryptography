import sys
import hashlib

def obliczSkrot(sol, haslo, nazwaAlgorytmu):
    tekstDoSkrotu = sol + ":" + haslo
    bajtyTekstu = tekstDoSkrotu.encode('utf-8')
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

def main():
    daneWejsciowe = sys.stdin.read().splitlines()
    if not daneWejsciowe:
        return

    nazwaAlgorytmu = daneWejsciowe[0].strip()
    liczbaPolecen = int(daneWejsciowe[1].strip())
    
    bazaUzytkownikow = {}

    for i in range(liczbaPolecen):
        if 2 + i >= len(daneWejsciowe):
            break
            
        elementyPolecenia = daneWejsciowe[2 + i].strip().split()
        if not elementyPolecenia:
            continue
            
        operacja = elementyPolecenia[0]
        nazwaUzytkownika = elementyPolecenia[1]

        if operacja == "REGISTER":
            sol = elementyPolecenia[2]
            haslo = elementyPolecenia[3]
            if nazwaUzytkownika in bazaUzytkownikow:
                print("EXISTS")
            else:
                skrot = obliczSkrot(sol, haslo, nazwaAlgorytmu)
                bazaUzytkownikow[nazwaUzytkownika] = (sol, skrot)
                print("OK")
                
        elif operacja == "LOGIN":
            haslo = elementyPolecenia[2]
            if nazwaUzytkownika not in bazaUzytkownikow:
                print("NOUSER")
            else:
                zapisanaSol, zapisanySkrot = bazaUzytkownikow[nazwaUzytkownika]
                aktualnySkrot = obliczSkrot(zapisanaSol, haslo, nazwaAlgorytmu)
                if aktualnySkrot == zapisanySkrot:
                    print("OK")
                else:
                    print("FAIL")
                    
        elif operacja == "CHANGE":
            stareHaslo = elementyPolecenia[2]
            noweHaslo = elementyPolecenia[3]
            if nazwaUzytkownika not in bazaUzytkownikow:
                print("NOUSER")
            else:
                zapisanaSol, zapisanySkrot = bazaUzytkownikow[nazwaUzytkownika]
                testowySkrot = obliczSkrot(zapisanaSol, stareHaslo, nazwaAlgorytmu)
                if testowySkrot != zapisanySkrot:
                    print("FAIL")
                else:
                    nowySkrot = obliczSkrot(zapisanaSol, noweHaslo, nazwaAlgorytmu)
                    bazaUzytkownikow[nazwaUzytkownika] = (zapisanaSol, nowySkrot)
                    print("OK")
                    
        elif operacja == "RESET":
            stareHaslo = elementyPolecenia[2]
            nowaSol = elementyPolecenia[3]
            noweHaslo = elementyPolecenia[4]
            if nazwaUzytkownika not in bazaUzytkownikow:
                print("NOUSER")
            else:
                zapisanaSol, zapisanySkrot = bazaUzytkownikow[nazwaUzytkownika]
                testowySkrot = obliczSkrot(zapisanaSol, stareHaslo, nazwaAlgorytmu)
                if testowySkrot != zapisanySkrot:
                    print("FAIL")
                else:
                    nowySkrot = obliczSkrot(nowaSol, noweHaslo, nazwaAlgorytmu)
                    bazaUzytkownikow[nazwaUzytkownika] = (nowaSol, nowySkrot)
                    print("OK")

if __name__ == "__main__":
    main()