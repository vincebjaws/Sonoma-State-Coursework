import os
import sys
import time as tm
import math

class BinHash:
    def __init__(self, c, w, v, n):
        self.capacity = c
        self.weights = w
        self.values = v
        self.size = n
        self.k = int(math.pow(2, n-4))
        self.bn = int(math.ceil(math.log2(n+1)))
        self.bw = int(math.ceil(math.log2(c+1)))

        self.hashTable = [[] for i in range(self.k)]
        self.htSize = 0
        self.opt_values = []
        self.v_w = []
        for i in range(len(w)):
            self.v_w.append((self.values[i], self.weights[i]))

    def print(self):
        start = tm.time()
        self.hash(self.size, self.capacity)
        self.getOPT_values(self.size, self.capacity)
        self.opt_values.reverse()
        t = tm.time() - start

        print('Space-efficient Dynamic Programming Optimal Value:', )
        print('Traditional Dynamic Programming Optimal subset: ',
              '{', ', '.join(str(x) for x in self.opt_values), '}', sep="")
        print('Space-efficient Dynamic Programming Time Taken:', t)
        print('Space-efficient Dynamic Programming Space Taken:', self.k, end='\n\n')

    def h(self, i, j):
        ri = format(i, "b")
        rj = format(j, "b")

        while len(ri) < self.bn:
            ri = "0" + ri
        while len(rj) < self.bw:
            rj = "0" + rj

        rij = "0b" + "1" + ri + rj
        b2dec = int(rij, 2)

        return b2dec

    def insert(self, i, j, num):
        n = self.h(i, j)
        idx = n % self.k
        item = (num, n)
        self.hashTable[idx].append(item)
        self.htSize += 1

    def find(self, i, j):
        num = self.h(i, j)
        idx = num % self.k

        n = -1
        for i in self.hashTable[idx]:
            if i[1] == num:
                return i[0]
        return n

    def hash(self, i, j):
        if i == 0 or j == 0:
            return 0
        if self.find(i, j) == -1:
            v = self.v_w[i - 1][0]
            w = self.v_w[i - 1][1]
            if j < w:
                n = self.hash(i - 1, j)
            else:
                n = max(self.hash(i - 1, j), v + self.hash(i - 1, j - w))
            self.insert(i, j, n)

        return self.find(i, j)

    # Space-Efficient Dynamic Approach
    def getOPT_values(self, i, j):
        if i == 0 or j == 0: return 0
        v = self.v_w[i-1][0]
        w = self.v_w[i - 1][1]
        if j - w >= 0:
            n = v + self.find(i - 1, j - w)
            f = self.find(i - 1, j)
            if n > f and j - w >= 0:
                self.opt_values.append(i)
                return self.getOPT_values(i - 1, j - w)

        return self.getOPT_values(i - 1, j)

    def getOPT_Val(self):
        num = self.h(self.size, self.capacity)
        idx = num % self.k
        for i in self.hashTable[idx]:
            if i[1] == num:
                return i[0]

# Traditional(Bottom Up) Approach
def TDP(capacity, weights, values, n):
    # start time
    start = tm.time()
    # creates (capacity + 1)x(# of weights or values) table
    table = [[0 for w in range(capacity + 1)] for i in range(n + 1)]

    # adds values to Knapsack table
    for i in range(n + 1):
        for w in range(capacity + 1):
            if i == 0 or w == 0:
                table[i][w] = 0
            elif weights[i - 1] <= w:
                table[i][w] = max(values[i - 1] + table[i - 1][w - weights[i - 1]],
                                  table[i - 1][w])
            else:
                table[i][w] = table[i - 1][w]

    # end time
    end = tm.time() - start

    # stores the result of Knapsack table
    res = table[n][capacity]
    print('Traditional Dynamic Programming Optimal value:', res)

    w = capacity
    opt_values = []
    for i in range(n, 0, -1):
        if res <= 0:
            break
        if res == table[i - 1][w]:
            continue
        else:
            # optimal item indexes
            opt_values.append(i)

            # Since this weight is included
            # its value is deducted
            res = res - values[i - 1]
            w = w - weights[i - 1]

    opt_values.reverse()

    # prints optimal values and algorithm time
    print('Traditional Dynamic Programming Optimal subset: ',
          '{', ', '.join(str(x) for x in opt_values), '}', sep="")
    print('Traditional Dynamic Programming Time Taken:', end, end='\n\n')

operations = 0
heap = []
n = 0

def greedy_sort(list):
    if len(list) == 1:
        return list
    return helper_sort(greedy_sort(list[len(list) // 2:]),
                       greedy_sort(list[:len(list) // 2]))

def helper_sort(right, left):
    global operations
    temp = []
    left_count = 0
    right_count = 0
    while right_count < len(right) and left_count < len(left):
        if right[right_count] < left[left_count]:
            temp.append(left[left_count])
            left_count += 1
        else:
            temp.append(right[right_count])
            right_count += 1
        operations += 1
    if right_count == len(right):
        temp += left[left_count:]
    if left_count == len(left):
        temp += right[right_count:]
    return temp

def greedy_optimal(ratios, weights, capacity, values):
    global operations
    subset = []
    sorted_array = greedy_sort(ratios)
    counter = 0
    current = 0
    optimal_value = 0

    while current + weights[ratios.index(sorted_array[counter])] < capacity:
        index = ratios.index(sorted_array[counter])
        current += weights[index]
        optimal_value += values[index]
        subset.append(index+ 1)
        counter += 1
    subset.sort()
    print()
    print("Greedy Approach Optimal Value:", optimal_value)
    print('Greedy Approach Optimal subset: ',
          '{', ', '.join(str(x) for x in subset), '}', sep="")
    print("Greedy Approach Number of Operations: ", operations)
    operations = 0

def heap_create():
    global heap
    global n
    if n <= 1:
        return
    rmp = n//2
    while rmp >0:
        sift(rmp)
        rmp -= 1

def heap_swap(a, b):
    global operations
    global heap
    operations += 1
    if heap[a] < heap[b]:
        heap[a], heap[b] = heap[b], heap[a]

def remove_top():
    global n
    global heap
    if n == 0:
        return -1
    m = heap[1]
    heap[1], heap[n] = heap[n], heap[1]
    n -= 1
    sift(1)
    return m

def sift(num):
    global n
    global heap
    global operations
    while num <= n // 2:
        if num * 2 + 1 > n:
            heap_swap(num, num * 2)
            return
        elif heap[num * 2] >= heap[num * 2 + 1]:
            heap_swap(num, num * 2)
            num = num * 2
        else:
            heap_swap(num, num * 2 + 1)
            num = num * 2 + 1
        operations += 1

def heap_optimal(ratios, weight, capacity, values):
    global operations
    global heap
    global n
    heap = [*[-1], *ratios]
    n = len(heap) - 1
    subset = []
    optimal_value = 0
    heap_create()
    current = 0
    reference = ratios.index(remove_top())

    while reference != -1 and current + weight[reference] < capacity:
        current += weight[reference]
        optimal_value += values[reference]
        subset.append(reference + 1)
        reference = ratios.index(remove_top())
    subset.sort()
    print()
    print("Heap-Based Greedy Approach Optimal Value:", optimal_value)
    print('Heap-Based Greedy Approach Optimal subset: ',
          '{', ', '.join(str(x) for x in subset), '}', sep="")
    print("Heap-Based Greedy Approach Number of Operations: ", operations)
    operations = 0

def main():
    args = sys.argv
    if len(args) != 3:
        print("Invalid number of arguments. Exiting...")
        return

    dir = args[1]
    num = args[2]
    if len(num) == 1:
        num = '0' + num
    files = os.listdir(dir)
    cFileName = "p" + num + "_c.txt"
    wFileName = "p" + num + "_w.txt"
    vFileName = "p" + num + "_v.txt"
    fileList = []
    for file in files:
        if cFileName == file:
            fileList.append(file)
        elif wFileName == file:
            fileList.append(file)
        elif vFileName == file:
            fileList.append(file)

    c = 0
    w = []
    v = []

    for file in fileList:
        FDir = dir + '/' + file
        F = open(FDir, 'r')

        if file[4] == 'c':
            f = F.read().splitlines()
            c = int(f[0])
            F.close()

        elif file[4] == 'w':
            w = F.read().splitlines()
            F.close()
            for i in range(len(w)):
                w[i] = int(w[i].strip(" "))

        elif file[4] == 'v':
            v = F.read().splitlines()
            for i in range(len(v)):
                v[i] = int(v[i].strip(" "))
            F.close()

    ratios = list(map(lambda x, y: x / y, v, w))

    print("File containing the capacity, weights, and values are: ", end=" ")
    print(cFileName, wFileName, "", sep=", ", end=vFileName + '\n\n')
    print("Knapsack capacity = {0}. Total number of items = {1}".format(c, len(w)), end='\n\n')

    TDP(c, w, v, len(w))
    BH = BinHash(c, w, v, len(w))
    BH.print()

    greedy_optimal(ratios, w, c, v)
    heap_optimal(ratios, w, c, v)


main()
