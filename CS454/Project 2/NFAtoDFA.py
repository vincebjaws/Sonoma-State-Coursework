# NFAtoDFA.py :
# This is Python code for representing finite automata, DFAs and NFAs,
# and for converting from an NFA into a DFA.
#
# Ben Reichardt, Spencer Coneley, Vince Bjazevic 1/17/2020
#

class DFA:
    """Class that encapsulates a DFA."""

    def __init__(self, transitionFunction, initialState, finalStates, stateSet):
        self.delta = transitionFunction
        self.q0 = initialState
        self.F = finalStates
        self.Q = stateSet

    def deltaHat(self, state, inputString):
        for a in inputString:
            state = self.delta[state][a]
        return state

    def inLanguage(self, inputString):
        return self.deltaHat(self.q0, inputString) in self.F


# comments:
# 	* python dictionary keys must be immutable
#	* it is a KeyError to extract an entry using a non-existent key

class NFA:
    """Class that encapsulates an NFA."""

    def __init__(self, transitionFunction, initialState, finalStates):
        self.delta = transitionFunction
        self.q0 = initialState
        self.F = set(finalStates)

    def deltaHat(self, state, inputString):
        """deltaHat is smart enough to return the empty set if no transition is defined."""
        states = set([state])
        for a in inputString:
            newStates = set([])
            for state in states:
                try:
                    newStates = newStates | self.delta[state][a]
                except KeyError:
                    pass
            states = newStates
        return states

    def inLanguage(self, inputString):
        return len(self.deltaHat(self.q0, inputString) & self.F) > 0

    def alphabet(self, N):
        """Returns the NFA's input alphabet, generated on the fly."""
        Sigma = reduce(lambda a, b: set(a) | set(b), [x.keys() for x in N.delta.values()])
        return Sigma

    def states(self):
        """Returns the NFA's set of states, generated on the fly."""
        Q = set([self.q0]) | set(self.delta.keys()) | reduce(lambda a, b: a | b, reduce(lambda a, b: a + b,
                                                                                        [x.values() for x in
                                                                                         self.delta.values()]))  # {q0, all states with outgoing arrows, all with incoming arrows}
        return Q


def convertNFAtoDFA(N):
    """Converts the input NFA into a DFA.

    The output DFA has a state for every *reachable* subset of states in the input NFA.
    In the worst case, there will be an exponential increase in the number of states.
    """
    q0 = frozenset([N.q0])  # frozensets are hashable, so can key the delta dictionary
    Q = set([q0])
    unprocessedQ = Q.copy()  # unprocessedQ tracks states for which delta is not yet defined
    delta = {}
    F = []
    Sigma = N.alphabet(N)

    while len(unprocessedQ) > 0:
        qSet = unprocessedQ.pop()
        delta[qSet] = {}
        for a in Sigma:
            nextStates = reduce(lambda x, y: x | y, [N.deltaHat(q, a) for q in qSet])
            nextStates = frozenset(nextStates)
            delta[qSet][a] = nextStates
            if not nextStates in Q:
                Q.add(nextStates)
                unprocessedQ.add(nextStates)
    for qSet in Q:
        if len(qSet & N.F) > 0:
            F.append(qSet)
    M = DFA(delta, q0, F, Q)
    return M


def createDFA():
    delta = {'q0': {'0': set(['q0', 'q7']), '1': set(['q1', 'q7']), '2': set(['q2', 'q7']), '3': set(['q3', 'q7']),
                    '4': set(['q4', 'q7']), '5': set(['q5', 'q7']), '6': set(['q6', 'q7']), '7': set(['q0', 'q7']),
                    '8': set(['q1', 'q7']), '9': set(['q2', 'q7'])},
             'q1': {'0': set(['q3', 'q8']), '1': set(['q4', 'q8']), '2': set(['q5', 'q8']), '3': set(['q6', 'q8']),
                    '4': set(['q0', 'q8']), '5': set(['q1', 'q8']), '6': set(['q2', 'q8']), '7': set(['q3', 'q8']),
                    '8': set(['q4', 'q8']), '9': set(['q5', 'q8'])},
             'q2': {'0': set(['q6', 'q9']), '1': set(['q0', 'q9']), '2': set(['q1', 'q9']), '3': set(['q2', 'q9']),
                    '4': set(['q3', 'q9']), '5': set(['q4', 'q9']), '6': set(['q5', 'q9']), '7': set(['q6', 'q9']),
                    '8': set(['q0', 'q9']), '9': set(['q1', 'q9'])},
             'q3': {'0': set(['q2', 'q10']), '1': set(['q3', 'q10']), '2': set(['q4', 'q10']), '3': set(['q5', 'q10']),
                    '4': set(['q6', 'q10']), '5': set(['q0', 'q10']), '6': set(['q1', 'q10']), '7': set(['q2', 'q10']),
                    '8': set(['q3', 'q10']), '9': set(['q4', 'q10'])},
             'q4': {'0': set(['q5', 'q11']), '1': set(['q6', 'q11']), '2': set(['q0', 'q11']), '3': set(['q1', 'q11']),
                    '4': set(['q2', 'q11']), '5': set(['q3', 'q11']), '6': set(['q4', 'q11']), '7': set(['q5', 'q11']),
                    '8': set(['q6', 'q11']), '9': set(['q0', 'q11'])},
             'q5': {'0': set(['q1', 'q12']), '1': set(['q2', 'q12']), '2': set(['q3', 'q12']), '3': set(['q4', 'q12']),
                    '4': set(['q5', 'q12']), '5': set(['q6', 'q12']), '6': set(['q0', 'q12']), '7': set(['q1', 'q12']),
                    '8': set(['q2', 'q12']), '9': set(['q3', 'q12'])},
             'q6': {'0': set(['q4', 'q13']), '1': set(['q5', 'q13']), '2': set(['q6', 'q13']), '3': set(['q0', 'q13']),
                    '4': set(['q1', 'q13']), '5': set(['q2', 'q13']), '6': set(['q3', 'q13']), '7': set(['q4', 'q13']),
                    '8': set(['q5', 'q13']), '9': set(['q6', 'q13'])},
             'q7': {'0': set(['q7']), '1': set(['q8']), '2': set(['q9']), '3': set(['q10']), '4': set(['q11']),
                    '5': set(['q12']), '6': set(['q13']), '7': set(['q7']), '8': set(['q8']), '9': set(['q9'])},
             'q8': {'0': set(['q10']), '1': set(['q11']), '2': set(['q12']), '3': set(['q13']), '4': set(['q7']),
                    '5': set(['q8']), '6': set(['q9']), '7': set(['q10']), '8': set(['q11']), '9': set(['q12'])},
             'q9': {'0': set(['q13']), '1': set(['q7']), '2': set(['q8']), '3': set(['q9']), '4': set(['q10']),
                    '5': set(['q11']), '6': set(['q12']), '7': set(['q13']), '8': set(['q7']), '9': set(['q8'])},
             'q10': {'0': set(['q9']), '1': set(['q10']), '2': set(['q11']), '3': set(['q12']), '4': set(['q13']),
                     '5': set(['q7']), '6': set(['q8']), '7': set(['q9']), '8': set(['q10']), '9': set(['q11'])},
             'q11': {'0': set(['q12']), '1': set(['q13']), '2': set(['q7']), '3': set(['q8']), '4': set(['q9']),
                     '5': set(['q10']), '6': set(['q11']), '7': set(['q12']), '8': set(['q13']), '9': set(['q7'])},
             'q12': {'0': set(['q8']), '1': set(['q9']), '2': set(['q10']), '3': set(['q11']), '4': set(['q12']),
                     '5': set(['q13']), '6': set(['q7']), '7': set(['q8']), '8': set(['q9']), '9': set(['q10'])},
             'q13': {'0': set(['q11']), '1': set(['q12']), '2': set(['q13']), '3': set(['q7']), '4': set(['q8']),
                     '5': set(['q9']), '6': set(['q10']), '7': set(['q11']), '8': set(['q12']), '9': set(['q13'])}}
    N = NFA(delta, 'q0', ['q0', 'q7'])
    N.deltaHat('q0', '0001')
    M = convertNFAtoDFA(N)
    return M


def createFinal(M, accepting, states):

    final = []
    print(final)
    print(len(final))

    for i in states:
        if accepting.__contains__(i):
            final.append(1)
        else:
            final.append(0)
    return final


def createTable(M, states):
    states = list(M.Q)
    table = []
    for i in range(len(M.Q)):
        table.append([])
        for j in range(10):
            table[i].append(0)

    print(table)
    for i in range(len(M.Q)):
        for j in range(10):
            table[i][j] = M.deltaHat(states[i], str(j))


# for q in M.Q:
#    for sym in ['0', '1']:
#        out = list(M.delta[frozenset(q)][sym])
#       print
#        'from state ' + str(list(q)) + ' on input ' + sym + ' = ' + str(out)

curState1 = set(['q0', 'q1', 'q2'])
curState = frozenset(curState1)
# for j in ['0', '1']:
#    print 'delta({q0, q1,q2} ' + j + ' = ' + M.delta[curState][j]


# both the above lines should return [('0001', True), ('00010', False), ('100101', True)]

# to run the doctests, run python or python -v directly on this script
if __name__ == "__main__":
    import doctest

    doctest.testmod()
