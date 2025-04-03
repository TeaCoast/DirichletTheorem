from math import *
import decimal as dcml

"""
def simplify_fraction(c: list, n=1):
    if len(c) == 1:
        return (c[0],1)
    if len(c) == 2:
        return (c[0] * c[1] + n, c[1])
    new_c = c[:-2]
    new_c.append(c[-2]*c[-1] + n)
    return simplify_fraction(new_c, c[-1])
"""

def simplify_fraction(cs: list[int]):
    if len(cs) == 1:
        return (cs[0], 1)
    n = 1
    d = cs[-1]
    i = len(cs) - 2
    while i > 0:
        new_d = cs[i] * d + n
        n = d
        d = new_d
        i -= 1
    return (cs[0] * d + n, d)


def evaluate_fraction(c: list):
    n, d = simplify_fraction(c)
    return n/d

    
def simple_cfa_v1(a: float, n: int) -> list[int]:
    c = floor(a)
    r = 1 / (a - c)

    cs = [c]

    for i in range(n):
        c = floor(r)
        cs.append(c)
        r = 1 / (r - c)
    
    return cs


def cfa_limit_v1(a0: float, a1: float, a: float) -> list[int]:
    c = floor(a)
    r = 1 / (a - c)

    cs = [c]

    while True:
        c = floor(r)
        if a0 < evaluate_fraction(cs + [c + 1]) < a1 or a0 < evaluate_fraction(cs + [c - 1]) < a1:
            break
        cs.append(c)
        r = 1 / (r - c)
    
    return cs

def cfa_limit_v2(a0: float, a1: float, n=50) -> list[int]:
    c0 = floor(a0)
    c1 = floor(a1)
    if c0 != c1:
        return None
    c = c0
    r0 = 1 / (a0 - c)
    r1 = 1 / (a1 - c)

    cs = [c]

    for i in range(n):
        c0 = floor(r0)
        c1 = floor(r1)
        if c0 != c1:
            break
        c = c0
        cs.append(c)
        r0 = 1 / (r0 - c)
        r1 = 1 / (r1 - c)
    
    return cs


def simple_cfa_v2(an: int, ad: int, n: int) -> list[int]:
    c = an // ad

    rn = ad
    rd = an - c * ad

    cs = [c]

    for i in range(n):
        if rd == 0:
            break
        c = rn // rd
        cs.append(c)
        new_rd = rn - c * rd
        rn = rd
        rd = new_rd
    
    return cs

def cfa_limit_v3(a0n: int, a0d: int, a1n: int, a1d: int) -> list[int]:
    c0 = a0n // a0d
    c1 = a1n // a1d
    if c0 != c1:
        return None
    c = c0

    r0n = a0d
    r0d = a0n - c * a0d

    r1n = a1d
    r1d = a1n - c * a1d

    cs = [c]

    while True:
        if r0d == 0 or r1d == 0:
            break
        c0 = r0n // r0d
        c1 = r1n // r1d
        if c0 != c1:
            break
        c = c0
        cs.append(c)

        new_r0d = r0n - c * r0d
        r0n = r0d
        r0d = new_r0d

        new_r1d = r1n - c * r1d
        r1n = r1d
        r1d = new_r1d
    
    return cs
    
PI = "3.14159265358979323846264"

left_digits = PI.find(".")
right_digits = 23

pi_approx = PI[:left_digits + 1 + right_digits]

print(pi_approx)

a0 = float(pi_approx)
a1 = a0 + 10 ** -right_digits

print(cfa_limit_v2(a0, a1))

an = int(pi_approx.replace('.', ''))
ad = 10 ** right_digits
print(simple_cfa_v2(an, ad, 11))

print(cfa_limit_v3(an, ad, an + 1, ad))