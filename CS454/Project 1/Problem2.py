import queue
import numpy

#constructs a DFA based on the passed in k and digits, and performs BFS on it. 
def smallestMultiple(k,digits):
    digits.sort(reverse=True)

    matrix = []
    for i in range(k):
        matrix.insert(i, [0]*len(digits))
    matrix[0] = digits


    for i in range(1, k):
        for r in range(len(digits)):
            matrix[i][r] = (10 * i + digits[r]) % k

    last = []
    for element in digits:
        if element != 0:
            last.append(element)
        else:
            last.append(-1)
    print(digits)
    print(last)

    matrix.insert(k+1, last)



    return MinString(matrix,len(matrix) - 1,digits)

# takes in a DFA in the form of a matrix and returns the shortest path to the 0 state, ignoring transitions labeled -1.
def MinString(DFA,startstate,labels):
    queue = []


    # array of indexes, 0 = not discovered, 1 = discovered.
    discovered = [0] * len(DFA)
    discovered[startstate] = 1

    #index of parent node
    parent = [0] * len(DFA)

    #number of node
    label = [""] * len(DFA)


    queue.append(startstate)

    next = 0
    found = 0
    while(len(queue) != 0 and found == 0):
        curr = queue.pop(0)
        count = 0
        for transition in DFA[curr]:

            next = transition
            if next == -1:

                continue

            if next == 0:
                parent[next] = curr
                label[next] = str(labels[count])
                found = 1
                break
            elif discovered[next] == 0:
                discovered[next] = 1
                parent[next] = curr


                queue.append(next)
                label[next] = str(labels[count])
                #What does this do? its in the pseudocode

            count += 1


    if(next != 0):
        print("no valid solution")
        return parent
    else:
        output = ""
        while(next != len(DFA) - 1):
            output += label[next]
            next = parent[next]
        print(''.join(reversed(output)))















