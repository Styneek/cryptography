import sys
import hashlib

def main():
    daneWejsciowe = sys.stdin.read().splitlines()
    if not daneWejsciowe:
        return

    nazwaAlgorytmu = daneWejsciowe[0].strip()
    liczbaTekstow = int(daneWejsciowe[1].strip())

    for i in range(liczbaTekstow):
        tekst = daneWejsciowe[2 + i] if (2 + i) < len(daneWejsciowe) else ""
        bajtyTekstu = tekst.encode('utf-8')
        
        if nazwaAlgorytmu == "MD5":
            skrot = hashlib.md5(bajtyTekstu)
        elif nazwaAlgorytmu == "SHA-1":
            skrot = hashlib.sha1(bajtyTekstu)
        elif nazwaAlgorytmu == "SHA-256":
            skrot = hashlib.sha256(bajtyTekstu)
        elif nazwaAlgorytmu == "SHA3-256":
            skrot = hashlib.sha3_256(bajtyTekstu)
        elif nazwaAlgorytmu == "BLAKE2S":
            skrot = hashlib.blake2s(bajtyTekstu)
        
        print(skrot.hexdigest())

if __name__ == "__main__":
    main()