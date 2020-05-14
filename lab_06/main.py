def left_side(Y, step, index):
    return (Y[index] - Y[index - 1]) / step if index > 0 else '---'

def right_side(Y, step, index):
    return (Y[index + 1] - Y[index]) / step if index < len(Y) - 1 else '---'

def center_side(Y, step, index):
    return (Y[index + 1] - Y[index - 1]) / 2 / step if index > 0 and index < len(Y) - 1 else '---'

def second_diff(Y, step, index):
    return (Y[index - 1] - 2 * Y[index] + Y[index + 1]) / step ** 2 if index > 0 and index < len(Y) - 1 else '---'

def runge_left(Y, step, index):
    if index < 2:
        return '---'
    F1 = left_side(Y, step, index)
    F2 = (Y[index] - Y[index - 2]) / 2 / step
    return F1 + F1 - F2

def align_vars_diff(Y, X, step, index):
    if index > len(Y) - 2:
        return '---'
    eta_ksi_diff = (1 / Y[index + 1] - 1 / Y[index]) / (1 / X[index + 1] - 1 / X[index])
    y = Y[index]
    x = X[index]
    return eta_ksi_diff * y * y / x / x


X = [1, 2, 3, 4, 5, 6]
Y = [0.571, 0.889, 1.091, 1.231, 1.333, 1.412]
table = [[0 for i in range(6)] for j in range(5)]
methods = [left_side, center_side, runge_left, align_vars_diff, second_diff]

print('-' * (6 + 8 * 5))
for i in range(len(X)):
    print('|', end='')
    for j in range(len(methods) - 2):
        res = methods[j](Y, X[1] - X[0], i)
        print(f'{res:.3f}'.center(8) if res != '---' else res.center(8), '|', sep='', end='')
    res = align_vars_diff(Y, X, X[1] - X[0], i)
    print(f'{res:.3f}'.center(8) if res != '---' else res.center(8), '|', sep='', end='')
    res = second_diff(Y, X[1] - X[0], i)
    print(f'{res:.3f}'.center(8) if res != '---' else res.center(8), '|', sep='')
    print('-' * (6 + 8 * 5))

