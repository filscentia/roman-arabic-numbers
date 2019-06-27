from roman import fromRoman, toRoman
from numbers import Number

with open('input.csv') as f:
    for line in f:
        line = line.rstrip()
        data = line.split(",")

        toRomanFlag = True
        try:
            int(data[0])
        except:
            toRomanFlag = False

        if toRomanFlag:    
            answer = toRoman(data[0])
            if answer == data[1]:
                print("%s is %s :: Correct!" % (data[0],answer))
            else:
                print("%s is NOT %s should be %s :: WRONG!!" % (data[0],answer,data[1]))
        else:
            answer = fromRoman(data[0])
            if int(answer) == int(data[1]):
                print("%s is %s :: Correct!" % (data[0],answer))
            else:
                print("%s is NOT %s should be %s :: WRONG!!" % (data[0],answer,data[1]))

