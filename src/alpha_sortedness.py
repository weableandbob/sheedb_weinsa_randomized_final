import random
import sys

array = []

def genAlphaSortedArray(alpha, n):
    global array
    array = range(0, n)
    num_replace = int((1 - alpha) * n)
    for i in xrange(0, num_replace):
        index = random.randint(0, n-1)
        if index == 0:
            array[index] = array[index + 1] + 1
        else:
            array[index] = array[index - 1] - 1

def getRandomSubArray(gamma):
    global array
    index = random.randint(0, len(array) - gamma - 1)
    return array[index:index + gamma]

def calcAlphaSortedness(sub_array):
    num_unsorted = 0
    for i in xrange(0, len(sub_array) - 1):
        if sub_array[i] > sub_array[i + 1]:
            num_unsorted += 1
    return float(len(sub_array) - num_unsorted) / len(sub_array)

def main():
    random.seed()

    if(len(sys.argv) != 5):
        print "Usage is %s array_size alpha beta gamma" % sys.argv[0]
        return
    n = int(sys.argv[1])
    alpha = float(sys.argv[2])
    beta = int(sys.argv[3])
    gamma = int(sys.argv[4])

    genAlphaSortedArray(alpha, n)

    total_alpha_sortedness = 0
    for i in xrange(0, beta):
        total_alpha_sortedness += calcAlphaSortedness(getRandomSubArray(gamma))
        print total_alpha_sortedness
    approximate_alpha_sortedness = float(total_alpha_sortedness) / beta
    if approximate_alpha_sortedness >= alpha:
        print "True"
    else:
        print "False"

if __name__ == "__main__":
    main()