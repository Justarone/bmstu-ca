from numpy.polynomial.legendre import leggauss
from math import pi, cos, sin, exp

def main_function(param):
    subfunc = lambda x, y: 2 * cos(x) / (1 - (sin(x) ** 2) * (cos(y) ** 2))
    func = lambda x, y: (4 / pi) * (1 - exp(-param * subfunc(x, y))) * cos(x) * sin(x)
    return func


# a = start, b = end
def simpson(func, a, b, num_of_nodes):
    if (num_of_nodes < 3 or num_of_nodes & 1 == 0):
        raise ValueError

    h = (b - a) / (num_of_nodes - 1)
    x = a
    res = 0

    for _ in range((num_of_nodes - 1) // 2):
        res += func(x) + 4 * func(x + h) + func(x + 2 * h)
        x += 2 * h

    return res * (h / 3)


#converts to args func to one arg func
def func_2_to_1(func2, value):
    return lambda y: func2(value, y)


def t_to_x(t, a, b):
    return (b + a) / 2 + (b - a) * t / 2


def gauss(func, a, b, num_of_nodes):
    args, coeffs = leggauss(num_of_nodes)
    res = 0

    for i in range(num_of_nodes):
        res += (b - a) / 2 * coeffs[i] * func(t_to_x(args[i], a, b))

    return res


# func = f(x, y) - function which we integrate
# limits = [[a, b], [c, d]] - limits for x and y
# num_of_nodes = [N, M] - number of nodes for x and y
# integrators = [func1, func2] - functions, which we use to integrate: f(func, a, b, num_of_nodes)
def integrate2(func, limits, num_of_nodes, integrators):
    inner = lambda x: integrators[1](func_2_to_1(func, x), limits[1][0], limits[1][1], num_of_nodes[1])
    return integrators[0](inner, limits[0][0], limits[0][1], num_of_nodes[0])


N = int(input("Enter N: ")) + 1
M = int(input("Enter M: ")) + 1
param = float(input("Enter param: "))
# mode = bool(int(input("Enter mode:\n0: Gauss-Simpson;\n1: Simpson-Gauss;\nEnter: ")))

# func1 = simpson if mode else gauss
# func2 = gauss if mode else simpson

func1 = gauss
func2 = gauss

print(integrate2(main_function(param), [[0, pi / 2], [0, pi / 2]], [N, M], [func1, func2]))
