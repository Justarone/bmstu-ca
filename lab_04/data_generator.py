import numpy
from math import *


boundaries = list(map(float, input("Enter boundaries: ").split()))
step = float(input("Enter step: "))
function = eval("lambda x: " + input("Enter function in python format (using x as arg): "))
filename = input("Enter filename: ")
with open(filename, "w") as f:
    for x in numpy.arange(boundaries[0], step + boundaries[1], step):
        f.write("{:.2f} {:.3f} 1\n".format(x, function(x)))
print("Done! Check file!")
