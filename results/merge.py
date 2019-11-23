import json
numbers = [
    10,
    20,
    30,
    40,
    50,
    75,
    100,
    125,
    150,
    175,
    200,
    225,
    250
]
for ns in numbers:
    # Open the individual files
    sOpen = open(f"seq{ns}.txt", "r")
    sFile = sOpen.read()
    sOpen.close()
    tOpen = open(f"thread{ns}.txt", "r")
    tFile = tOpen.read()
    tOpen.close()
    pOpen = open(f"proc{ns}.txt", "r")
    pFile = pOpen.read()
    pOpen.close()
    # Parse through the individual files
    sResults = sFile.split("*******************************************************")[3].strip().split("\n")[1:]
    tResults = tFile.split("*******************************************************")[3].strip().split("\n")[1:]
    pResults = pFile.split("*******************************************************")[3].strip().split("\n")[1:]

    for i in range(0, len(sResults)):
        raw = []
        sRaw = sResults[i].split("\t")
        tRaw = tResults[i].split("\t")
        pRaw = [i for i in pResults[i].split(" ") if i]
        raw += sRaw
        raw += tRaw
        raw += pRaw
        print(raw)
    for s in sResults:
        sRaw.append(s.split("\t"))
    for t in tResults:
        tRaw.append(t.split("\t"))
    for p in pResults:
        pRaw.append([i for i in p.split(" ") if i])

    #for i in range(1, len(sRaw)):
       # print(sRaw[i])