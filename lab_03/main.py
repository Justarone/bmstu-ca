from funcs import *


if __name__ == "__main__":
    filename = input("Enter filename: ")
    plist = read_from_file(filename)

    if not plist:
        print("Error with file...")
        exit(1)

    plist.sort(key=lambda x: x[0])

    a = [0] + [p[1] for p in plist]
    h = [0] + [plist[i][0] - plist[i - 1][0] for i in range(1, len(plist))]
    c = [0 for i in range(len(a))]
    b = c[:]
    d = c[:]
    ksi = c[:]
    eta = c[:]
    straight_walk(ksi, eta, len(c), plist, h)
    forward_walk(ksi, eta, c)
    find_additional(d, b, a, c, h)
    x = float(input("Введите х: "))
    i = find_section(plist, x)
    print("x = ", x, "and section is: ", plist[i - 1][0], plist[i][0])
    result = find_result(x, a[i], b[i], c[i], d[i], plist[i - 1][0])
    print("result is: ", result)
