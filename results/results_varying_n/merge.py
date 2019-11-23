import json
numbers = [
    100,
    1000,
    2000,
    5000,
    10000,
    20000
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
    sResults = sFile.strip().split("\n")[1:]
    tResults = tFile.strip().split("\n")[1:]
    pResults = pFile.strip().split("\n")[1:]

    rawString = ""
    for i in range(0, len(sResults)):
        raw = []
        sRaw = sResults[i].split("\t")
        tRaw = tResults[i].split("\t")
        pRaw = [i for i in pResults[i].split(" ") if i]
        if i == 0:
            sRaw[0] = "Size"
            sRaw[1] = "Split Size"
            sRaw[2] = "Sequence Total Time"
            sRaw[3] = "Sequence Average Time"
            sRaw[4] = "Sequence Min Time"
            sRaw[5] = "Sequence Max Time"
            sRaw[6] = "Sequence Standard Deviation"
            tRaw[0] = "Size"
            tRaw[1] = "Split Size"
            tRaw[2] = "Thread Total Time"
            tRaw[3] = "Thread Average Time"
            tRaw[4] = "Thread Min Time"
            tRaw[5] = "Thread Max Time"
            tRaw[6] = "Thread Standard Deviation"
            pRaw[0] = "Size"
            pRaw[1] = "Split Size"
            pRaw[2] = "Proc Total Time"
            pRaw[3] = "Proc Average Time"
            pRaw[4] = "Proc Min Time"
            pRaw[5] = "Proc Max Time"
            pRaw[6] = "Proc Standard Deviation"
        tRaw = tRaw[2:]
        pRaw = pRaw[2:]
        raw += sRaw
        raw += tRaw
        raw += pRaw
        for i in raw:
            rawString += i + ","
        rawString = rawString[:-1]
        rawString += "\n"
    rawString = rawString[:-1]
    saver = open(f"output/{ns}.csv", "w")
    saver.write(rawString)
    saver.close()