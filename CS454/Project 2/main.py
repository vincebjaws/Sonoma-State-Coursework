from NFAtoDFA import *


def main():
    ourDFA = createDFA()
    accepting = list(ourDFA.F)
    states = list(ourDFA.Q)
    final = createFinal(ourDFA, accepting, states)
    table = createTable(ourDFA,states)

main()
