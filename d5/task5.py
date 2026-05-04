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

def main():
    daneWejsciowe = sys.stdin.read().split()
    if not daneWejsciowe:
        return

    nazwaAlgorytmu = daneWejsciowe[0]
    liczbaBlokow = int(daneWejsciowe[1])
    liczbaZapytan = int(daneWejsciowe[2])

    bloki = []
    wskaznik = 3
    for _ in range(liczbaBlokow):
        bloki.append(daneWejsciowe[wskaznik])
        wskaznik += 1

    poziomy = []
    aktualnyPoziom = []
    for blok in bloki:
        aktualnyPoziom.append(obliczSkrot(blok.encode('utf-8'), nazwaAlgorytmu))
    poziomy.append(aktualnyPoziom)

    while len(aktualnyPoziom) > 1:
        nastepnyPoziom = []
        for i in range(0, len(aktualnyPoziom), 2):
            lewy = aktualnyPoziom[i]
            prawy = aktualnyPoziom[i + 1] if i + 1 < len(aktualnyPoziom) else aktualnyPoziom[i]
            nastepnyPoziom.append(obliczSkrot((lewy + prawy).encode('utf-8'), nazwaAlgorytmu))
        poziomy.append(nastepnyPoziom)
        aktualnyPoziom = nastepnyPoziom

    for _ in range(liczbaZapytan):
        if wskaznik >= len(daneWejsciowe):
            break
        typZapytania = daneWejsciowe[wskaznik]
        wskaznik += 1

        if typZapytania == "ROOT":
            print(poziomy[-1][0])
        elif typZapytania == "UPDATE":
            indeks = int(daneWejsciowe[wskaznik]) - 1
            nowaWartosc = daneWejsciowe[wskaznik + 1]
            wskaznik += 2

            poziomy[0][indeks] = obliczSkrot(nowaWartosc.encode('utf-8'), nazwaAlgorytmu)
            aktualnyIndeks = indeks

            for lvl in range(len(poziomy) - 1):
                lewyIndeks = aktualnyIndeks - (aktualnyIndeks % 2)
                prawyIndeks = lewyIndeks + 1

                lewySkrot = poziomy[lvl][lewyIndeks]
                prawySkrot = poziomy[lvl][prawyIndeks] if prawyIndeks < len(poziomy[lvl]) else lewySkrot

                nowySkrotRodzica = obliczSkrot((lewySkrot + prawySkrot).encode('utf-8'), nazwaAlgorytmu)

                aktualnyIndeks = aktualnyIndeks // 2
                poziomy[lvl + 1][aktualnyIndeks] = nowySkrotRodzica

            print(poziomy[-1][0])

if __name__ == "__main__":
    main()