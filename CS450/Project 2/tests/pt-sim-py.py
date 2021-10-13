# Author: Robert Sapien, Vince Bjazevic, Tim Wu
# Date: 10/27/2020
# Class: CS450
# Assignment Description: This project performs virtual
#address translation, and is expanded to simulate the 
# Clock/SEcond Chance page replacement algorithm

import sys, getopt, math

#----------------------------------------------------------------#
# Class to hold the page table elements
#----------------------------------------------------------------#
class Page_Table:
    def __init__(self, infile):
        self.vn = 0
        self.pm = 0
        self.pSize = 0
        self.pages = []
        self.ptr = 0

        file = open(infile, 'r')
        
        for x in file:
            if x != '\n':
                y = x.split()
                self.pages.append(y)

        first = False
        second = False
        for x in self.pages[0]:
            if not first:
                self.vn = int(x)
                first = True
                    
            elif first and not second:
                self.pm = int(x)
                second = True
                    
            else:
                self.pSize = int(x)

        self.pages.pop(0)

        for i in range (int(math.log(self.pSize,2))-1):
            if self.pages[i][0]:
                self.ptr = i
                break
    #----------------------------#
    def print_data(self):
        print("virtual size: ", self.vn)
        print("physical size: ", self.pm)
        print("page size size: ", self.pSize)

    def print_Pages(self):
        print(self.vn, ' ', self.pm, ' ', self.pSize)
        for num in self.pages:
            print(num)

    def get_Pages(self):
        return self.pages

    def get_virt(self):
        return self.vn

    def get_phys(self):
        return self.pm

    def get_size(self):
        return self.pSize

    def get_valid(self, row):
        return self.pages[row][0]

    def get_access_bit(self, row):
        #print("this is row: ", row)
        bin_conv = dec2bin(int(self.pages[row][1]))
        return bin_conv

    def get_frame_num(self, row):
        return self.pages[row][2]

    def get_recently_used(self, row):
        return self.pages[row][3]

    #----------------------------#


#----------------------------------------------------------------#
# Class to hold the page table elements
#----------------------------------------------------------------#
def help():
    print("Usage:\n\n")
    print("--help: Provides usage information for commands and arguments")
    print("--verbose: provides extra information about what is being output")
    print("--test: allows for tests to type conversions such as decimal to hex")
    print("-c: sets clock flag to true")


#----------------------------------------------------------------#
# Class to hold the page table elements
#----------------------------------------------------------------#    
def check_args(argv):
    try:
        opts, args = getopt.getopt(argv, 'c', ['verbose', 'test', 'help'])

    except getopt.GetoptError as err:
        print(err)
        sys.exit(2)

    flags = [False, False, False]
        
    for opt, arg in opts:
        if opt in ['--help']:
            help()
            
        elif opt in ['--verbose']:
            flags[0] = True
            
        elif opt in ['--test']:
            flags[1] = True
            
        elif opt in ['-c']:
            flags[2] = True

    return flags

#----------------------------------------------------------------#
# If 'test' flag is true this function is called to test the
# number conversion functions
#----------------------------------------------------------------#
def Test():

    def info():
        print("Type 'exit' to exit test mode and the program")
        print("For more information about testing mode\ntype 'info'")
        return

    info()

    h = False
    d = False
    
    while True:
        ins = input()
        if ins.lower() == "exit":
            print("Exiting...")
            exit()

        if ins.lower() == "info":
            info()

        if h:
            print("binary: ", hex2bin(ins))
            print("decimal: ", hex2dec(ins))
            print("binary back to hexidecimal: ", bin2hex(ins))
            
        elif d:
            print("binary: ", dec2bin(ins))
            print("hexidecimal: ", dec2hex(ins))
            print("binary back to decimal: ", bin2dec(ins))


#----------------------------------------------------------------#
# Number check & conversions: hex/dec/bin
#----------------------------------------------------------------#
def check_num(num):
    if num[:2] == "0x":
        h = "hex"
        return h
    else:
        d = "dec"
        return d

def hex2dec(n):
    return int(n, 16)
    
def dec2hex(n):
    n = int(n, base=10)
    return hex(n)
    
def hex2bin(n):
    n = int(n, base=16)
    return bin(n)

def bin2hex(n):
    n = int(n, base=2)
    return hex(n)

def bin2dec(n):
    n = int(n, base=2)
    return int(n)

def dec2bin(n):
    n = bin(int(n))
    return n[2:]

#----------------------------------------------------------------#
# Page Check
# Description: Checks to see if address is in the page table
#----------------------------------------------------------------#
def pageCheck(vn, pm):
    if type(vn) == int:
        vn = str(vn)
    #print(type(vn))
    if '0' in vn:
        if pm != 0:
            return "DISK"
        else:
            return "SEGFAULT"
    else:
        return False

#----------------------------------------------------------------#
#Translate virtual address to physical address (clock)
#----------------------------------------------------------------#
def virt2phys_clock(pt, virt):
    #print(virt)
    numType = check_num(virt)
    pgSize = pt.get_size()
    virtSize = pt.get_virt()
    indexSize = int(virtSize - math.log(pt.pSize, 2)) #fram size
    numPages = math.log(pt.pSize, 2)
    pgfault = "PAGEFAULT"
    if numType == "hex": #hex to bin
        virtBin = hex2bin(virt)[2:]
        if len(virtBin) < virtSize:
            while len(virtBin) < virtSize: #append 0s to front of string
                virtBin = "0" + virtBin
        append = virtBin[indexSize:] #virtual offset
        ptindex = virtBin[:indexSize] #page
        
    else: #decimal to bin
        virtBin = hex2bin(dec2hex(virt))[2:]
        if len(virtBin) < virtSize:
            while len(virtBin) < virtSize:
                virtBin = "0" + virtBin
        append = virtBin[indexSize:]
        ptindex = virtBin[:indexSize]
    
    idx = bin2dec(ptindex)

    #check if idx is already valid
    
    if pt.pages[pt.ptr][0] == 1:
        return virtual2physical(pt,virt);
    #check & updating table
    #if pt.pages[pt.ptr][3]:

    for i in range (pt.ptr+1, int(numPages)-1):
            #print("ptr", pt.ptr+1)

            if int(pt.pages[i][3]) == 0: #and pt.pages[i][0] == 0: #if valid && not recently used
                pt.pages[i][0] = 0 #update i valid
                pt.pages[pt.ptr][0] = 1 #update ptr valid
                pt.pages[pt.ptr][2] = pt.pages[i][2] #update ptr frame
                pt.pages[pt.ptr][3] = 1 #update 
                
                pt.ptr += 1
                if (pt.ptr > numPages):
                    for i in range(pt.ptr-1):
                        if pt.pages[i][0]:
                            pt.ptr = i
                return "PAGEFAULT"
            else:
                pt.ptr += 1
                if (pt.ptr > numPages):
                    for i in range(pt.ptr-1):
                        if pt.pages[i][0]:
                            pt.ptr = i
                return virtual2physical(pt, virt)


    
#----------------------------------------------------------------#
#Translate virtual address to physical address
#----------------------------------------------------------------#
def virtual2physical(pt, virt):
    numType = check_num(virt)
    pgSize = pt.get_size()
    virtSize = pt.get_virt()
    indexSize = int(virtSize - math.log(pgSize, 2)) #frame size

    if numType == "hex": #hex to bin
        virtBin = hex2bin(virt)[2:]
        if len(virtBin) < virtSize:
            while len(virtBin) < virtSize: #append 0s to front of string
                virtBin = "0" + virtBin
        append = virtBin[indexSize:] #virtual offset
        ptindex = virtBin[:indexSize] #page
        
    else: #decimal to bin
        virtBin = hex2bin(dec2hex(virt))[2:]
        if len(virtBin) < virtSize:
            while len(virtBin) < virtSize:
                virtBin = "0" + virtBin
        append = virtBin[indexSize:]
        ptindex = virtBin[:indexSize]
    
    index = bin2dec(ptindex) #page in dec
    pm = bin2dec(pt.get_access_bit(index)) #permission bit
    fnBin = hex2bin(dec2hex(pt.get_frame_num(index))) #frame in bin
    vn = pt.get_valid(index)


    check = pageCheck(vn, pm)
    if check:
        return check

    virt2phy = fnBin + append #frame + offset
    
    #converting virtual address to physical depending in the type of number
    if numType == "hex":
        physical = bin2hex(virt2phy)
    else:
        physical = bin2dec(virt2phy)
    return physical

def read_in(flags, pt):
    print("Type or 'quit' to leave the program")
    
    if(flags[2]):
        for line in sys.stdin:
            if line.lower() == 'quit':
                return
            clock  = virt2phys_clock(pt, line)
            print(clock)
    else:
        for line in sys.stdin:
            if line.lower() == 'quit':
                return
            phys = virtual2physical(pt, line)
            print(phys)
    return
#----------------------------------------------------------------#
# Main function
#----------------------------------------------------------------#
def main(argv):

    #### sets flags [0] = "verbose", [1] = "test", [2] = "c"
    flags = check_args(argv)
    
    infile = argv[-1]
    if flags[0]: print("infile: ", infile)

    if flags[0]: print("reading in file...")

    pTable = Page_Table(infile)

    pTable.print_Pages()
    pTable.print_data()

    read_in(flags, pTable)
    print("Leaving program...")

    return

if __name__ == "__main__":
    main(sys.argv[1:])
