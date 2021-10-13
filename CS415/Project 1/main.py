# Project 1 - Asymptotic Analysis of Algorithms
# Creators: Robert Sapien & Vince Bjazevic
# Date: 28 February 2020

import matplotlib.pyplot as plt
from random import *
import time

counter = 0


# -----------------------------------------------------------------------------
# Beginning of Fibonacci/Euclid's task
#
# Lines 18 - 48 (Fibonacci)
# Lines 52 - 76 (Euclid's)

def Fibonacci(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    return Fibonacci(n - 1) + Fibonacci(n - 2)

# Calculates the number of additions for a fibonacci sequence to n

def fibAdds(n):
    if n == 1:
        return 1
    elif n == 0:
        return 0
    return fibAdds(n - 1) + fibAdds(n - 2) + 1

# Plots the fibonacci sequences additions given a range

def PlotFib():
    fibx = []
    fiby = []
    for i in range(1, 10):
        fibx.append(i)
        fiby.append(fibAdds(i))
    print("FibValues: ", fibx)
    print("fiby: ", fiby)
    plt.scatter(fibx, fiby)
    plt.xlabel('Fibonacci Number Index')
    plt.ylabel('Number of Additions')
    plt.title('Fibonacci Analysis')
    plt.show()

# Formula for computing Euclid's, keeps track of operations through global counter

def Euclids(a, b):
    global counter
    if b == 0:
        return a
    counter += 1  # Counter computes # of operations for algorithm
    return Euclids(b, a % b)


# Produces a plot for Euclid's based on range 1 - 15

def PlotEuc():
    global counter
    EucX = []
    EucY = []
    for i in range(1, 15):
        a = Fibonacci(i)
        Euclids(Fibonacci(i + 1), a)
        EucY.append(counter)
        EucX.append(a)
        counter = 0
    plt.scatter(EucX, EucY)
    plt.xlabel('n')
    plt.ylabel('Number of mod Divisions')
    plt.title('Euclids GCD Analysis')
    plt.show()

# ------------------------------------------------------------------------------
# Exponential task
#
# Lines 86 - 113 (Decrease-by-one)
# Lines 117 - 149 (Decrease-by-constant)
# Lines 153 - 184 (Divide-and-conquer)
# Lines 186 - 197 (Plotting)

def decreaseByOne(a, n):
    if n <= 0:
        return 1
    return a * decreaseByOne(a, n - 1)

# Computes the number of multiplication done by Decrease-by-one

def dboMuls(a, n):
    if n == 0:
        return 0
    return dboMuls(a, n - 1) + 1

# Produces a plot for Decrease-by-one

def plotDBO(n):
    numMuls = []
    dbo = []

    for i in range(1, 25):
        dbo.append(i)
        numMuls.append(dboMuls(2, i))
    if n == 1:
        plot = plt.scatter(dbo, numMuls, c='red')
        return plot
    plt.xlabel("Exponent of 2")
    plt.ylabel("Decrease-By-One Multiplications")
    plt.scatter(dbo, numMuls)
    plt.show()

# Computes the number of multiplication done by Decrease-by-constant

def ComputeDBC(a, n):
    if n == 0:
        return 0
    elif n % 2 == 0:
        return (ComputeDBC(a, n / 2)) + 1
    return (ComputeDBC(a, (n - 1) / 2)) + 2

# Decrease-by-constant formula for computing exponential

def decreaseByConstant(a, n):
    if n <= 0:
        return 1
    elif n % 2 == 0:
        return decreaseByConstant(a, n / 2) ** 2
    else:
        return a * (decreaseByConstant(a, (n - 1) / 2) ** 2)

# Produces a plot for Decrease-by-Constant

def plotDBC(n):
    numMuls = []
    dbc = []

    for i in range(1, 25):
        dbc.append(i)
        numMuls.append(ComputeDBC(2, i))
    if n == 1:
        plot = plt.scatter(dbc, numMuls, c='green')
        return plot
    plt.xlabel("Exponent of 2")
    plt.ylabel("Decrease-By-Constant Multiplications")
    plt.scatter(dbc, numMuls)
    plt.show()

# Decrease-by-constant formula for computing exponential, keeps track of amount of mults by counter

def divideConquer(a, n):
    global counter
    if n == 0:
        return 1
    elif n % 2 == 0:
        counter += 1
        return divideConquer(a, n / 2) * divideConquer(a, n / 2)
    else:
        counter += 2
        return a * divideConquer(a, (n - 1) / 2) * divideConquer(a, (n - 1) / 2)

# Produces a plot for Divide-and-conquer

def plotDivC(n):
    global counter
    numMuls = []
    divC = []

    for i in range(1, 25):
        divC.append(i)
        divideConquer(2, i)
        numMuls.append(counter)
        counter = 0


    if n == 1:
        plot = plt.scatter(divC, numMuls, c='blue')
        return plot
    plt.xlabel("Exponent of 2")
    plt.ylabel("Divide-and-Conquer Multiplications")
    plt.scatter(divC, numMuls)
    plt.show()

def plotAll():
    x = []
    y = []
    DC = plotDivC(1)
    DbO = plotDBO(1)
    DbC = plotDBC(1)
    plt.legend((DbC, DbO, DC), ('Decrease By Constant Factors', 'Decrease by One', 'Decrease By Constant Factors', 'Divide and Conquer'))
    plt.scatter(x, y)
    plt.xlabel('Exponent of 2')
    plt.ylabel('Multiplications')
    plt.title('Side-by-Side-analysis')
    plt.show()

# -----------------------------------------------------------------------------
# Sorting task
#
# Lines 202 - 215  (Selection Sort)
# Lines 199 - 210 (Insertion Sort)
# Lines 231 - 288 (Plotting)

def SelectionSort(A):
    global counter
    for i in range(len(A)):
        min_idx = i
        for j in range(i + 1, len(A)):
            counter += 1
            if A[min_idx] > A[j]:
                min_idx = j
        A[i], A[min_idx] = A[min_idx], A[i]
    return A

def InsertionSort(A):
    global counter
    for i in range(len(A)):
        key = A[i]
        j = i - 1
        counter += 1
        while j >= 0 and key < A[j]:
            counter += 1
            A[j + 1] = A[j]
            j -= 1
        A[j + 1] = key
    return A


def DefaultPlotSorts():
    testCase('B')
    testCase('A')
    testCase('W')


def testCase(test):
    list = []
    if test == 'B':
        for i in range(1, 50):
            tempList = []
            for j in range(1, i):
                tempList.append(j)
            list.append(tempList)
    elif test == 'A':
        for i in range(1, 50):
            tempList = []
            for j in range(1, i):
                tempList.append(randint(1, 500))
            list.append(tempList)
    else:
        for i in range(1, 50):
            tempList = []
            for j in range(1, i):
                tempList.insert(0, j)
            list.append(tempList)
    plotSorts(list, test)


def plotSorts(list, test):
    global counter
    xInsertSort = []
    yInsertSort = []
    xSelectSort = []
    ySelectSort = []
    for i in range(len(list)):
        InsertionSort((list[i]))
        yInsertSort.append(counter)
        xInsertSort.append(len(list[i]))
    counter = 0
    for i in range(len(list)):
        SelectionSort(list[i])
        ySelectSort.append(counter)
        xSelectSort.append(len(list[i]))
    counter = 0
    if test == 'A':
        test = 'Average (random values)'
    elif test == 'B':
        test = 'Best (Sorted values)'
    else:
        test = 'Worst (Reversed Order)'
    plt.xlabel('Size of List')
    plt.ylabel('Number of Swaps')
    plt.title(str(test) + ' Case for Insertion and Selection sort')
    plt.legend((plt.scatter(xInsertSort, yInsertSort, c='red'),
                plt.scatter(xSelectSort, ySelectSort, c='purple')),
               ('Insertion Sort', 'Selection Sort'))
    plt.show()

# ------------------------------------------------------------------------------
# Main Functions
#
# Lines 297 - 323 (Instructions)
# Lines 326 - 395 (Output)
# Lines 398 - 404 (main)

def defaultInstructions():
    print("Please choose a mode. Enter 'user',"
          " for user mode or 'plot', for plot mode (case sensitive).")
    print("Type x to exit the program.\n")


def functionInstructions():
    print("Type f for Fibonnaci function.")
    print("Type g for GCD function.")
    print("Type e for Exponentiation functions."
          "   (Decrease-by-One, Decrease-by-Constant-Factor, and Divide-and-Conquer")
    print("Type s for sorting functions."
          "  (Insertion & Selection Sort)\n")
    print("Type 'plot' to change  to plot mode.")
    print("Type x to exit the program.\n")


def plotInstructions():
    print("Type fibPlot for Fibonnaci plot.")
    print("Type gcdPlot for GCD plot.")
    print("Type expPlot for Exponentiation plots together."
          "   (Decrease-by-One, Decrease-by-Constant-Factor, and Divide-and-Conquer)")
    print("Type sortPlot for sorting plot."
          "  (Insertion & Selection Sort)\n")
    print("Type DBO, DBC, or DC, to plot exponentiation separately")
    print("Type 'user' to change to function mode.")
    print("Type x to exit the program.\n")


def getOutput(i):
    if i == "user":
        functionInstructions()

    elif i == 'f':
        k = int(input("Input kth value of Fibonacci algorithm: "))
        print("kth value of Fibonacci: ", Fibonacci(k))
        print("Number of Adds: ", fibAdds(k), "\n")
        print()
        time.sleep(3)
        functionInstructions()

    elif i == 'g':
        k = int(input("Input kth value of Fibonacci algorithm to get GCD: "))
        print("GCD of k and k-1: ", Euclids(k, k - 1))
        time.sleep(3)
        functionInstructions()

    elif i == 'e':
        a = int(input("Input constant: "))
        n = int(input("Input exponent: "))
        print("Decrease-by-One: ", decreaseByOne(a, n))
        print("Decrease-by-Constant: ", decreaseByConstant(a, n))
        print("Divide-and-Conquer: ", divideConquer(a, n))
        print()
        time.sleep(3)
        functionInstructions()

    elif i == 's':
        print("Enter numbers your values with spaces between them on the same line.")
        arr = [int(j) for j in input("Input n numbers in any order: ").split()]
        arr1 = arr
        InsertionSort(arr)
        SelectionSort(arr1)
        print("Selection Sort: ", arr1)
        print("Insertion Sort: ", arr)
        print()
        time.sleep(3)
        functionInstructions()

    elif i == "plot":
        plotInstructions()

    elif i == 'fibPlot':
        PlotFib()
        plotInstructions()

    elif i == 'gcdPlot':
        PlotEuc()
        plotInstructions()

    elif i == 'expPlot':
        plotAll()
        plotInstructions()

    elif i == 'DBO':
        plotDBO(2)

    elif i == 'DBC':
        plotDBC(2)

    elif i == 'DC':
        plotDivC(2)

    elif i == 'sortPlot':
        DefaultPlotSorts()
        plotInstructions()

    else:
        print("Invalid input.")


def main():
    defaultInstructions()
    userInput = input("Input: ")
    while userInput.lower() != "x":
        getOutput(userInput)
        time.sleep(2)
        userInput = input("Input: ")


main()
