import numpy
from math import *


boundaries_x = list(map(float, input("Enter boundaries x (using space): ").split()))
step_x = float(input("Enter step x: "))
boundaries_y = list(map(float, input("Enter boundaries y (using space): ").split()))
step_y = float(input("Enter step y: "))
function = eval("lambda x, y: " + input("Enter function in python format (using x, y as args): "))
filename = input("Enter filename: ")
with open("../data/" + filename, "w") as f:
    print((boundaries_x[1] - boundaries_x[0]) % step_x == 0)
    f.write(f"{int((boundaries_x[1] - boundaries_x[0]) % step_x != 0) + int((boundaries_x[1] - boundaries_x[0] + step_x) / step_x)}  ")
    f.write(f"{int((boundaries_y[1] - boundaries_y[0]) % step_y != 0) + int((boundaries_y[1] - boundaries_y[0] + step_y) / step_y)}\n")
    for x in numpy.arange(boundaries_x[0], step_x + boundaries_x[1], step_x):
        for y in numpy.arange(boundaries_y[0], step_y + boundaries_y[1], step_y):
            f.write("{:.2f} {:.2f} {:.3f}    ".format(x, y, function(x, y)))
        f.write("\n")
print("Done! Check file in \"data\" folder!")
