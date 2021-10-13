from array import *
import numpy
import sys

def Count(n):
    numpy.set_printoptions(threshold=sys.maxsize)
    dt = numpy.dtype(('U', 10))

    DFAtable = GenerateDFATable()

    RecTable = []
    for i in range(1024):
        RecTable.append([0] * 2)

    recRows = len(RecTable)


    for x in range(recRows):
        RecTable[x][0] = 1

    for y in range(n-5):
        RecTable = RecurrenceStep(RecTable,DFAtable)

    total = int(0);
    for x in range(1024):
        total += RecTable[x][0]

    return total



def GenerateDFATable():
    numpy.set_printoptions(threshold=sys.maxsize)
    dt=numpy.dtype(('U',10))
    matrix = numpy.empty([1024,5],dtype=dt)



    count = 0
    inputs = ["a","b","c","d"]

    for i in range(0,4):
        for j in range(0, 4):
            for k in range(0, 4):
                for l in range(0, 4):
                    for m in range(0, 4):
                        matrix[count][0] = (inputs[i] + inputs[j] + inputs[k] + inputs[l] + inputs[m]).encode('UTF-8')
                        count += 1

    rows = matrix.shape[0]
    cols = matrix.shape[1]

    for x in range(0, rows):
        for y in range(1, cols):
            tempstring = matrix[x][0] + inputs[y-1]

            if "a" in tempstring and "b" in tempstring and "c" in tempstring and "d" in tempstring:
                newstring = tempstring[1:]

                for m in range(0,rows):
                    if newstring == matrix[m][0]:

                        matrix[x][y] = str(m)
                        break
            else:
                matrix[x][y] = str(-1)


    return matrix


def RecurrenceStep(RecTable, DFA):

    for x in range(1024):
        sum = int(0)
        for y in range(1,5):

            if DFA[x][y] != "-1":
                sum += RecTable[int(DFA[x][y])][0]

        RecTable[x][1] = sum

    for sublist in RecTable:
        sublist[0], sublist[1] = sublist[1], sublist[0]

    return RecTable
