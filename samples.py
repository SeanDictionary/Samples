# Samples
import math


def gcd(a,b):
    """
    欧几里得算法\\
    计算gcd(a,b)
    """
    if b == 0:
        return a
    return gcd(b,a%b)

def exgcd(a, b):
    """
    扩展欧几里得算法\\
    计算gcd(a,b)和满足的ax+by=gcd(a,b)的一组解
    """
    # 正常计算
    if b == 0:
        return a, 1, 0
    gcd, x, y = exgcd(b, a%b)
    return gcd, y, x-a//b*y

    # 逆元计算(实际上逆元的计算是运用了exgcd)
    """ g = gcd(a,b)
    a //= g
    b //= g
    x = pow(a,-1,b)
    y = (1-a*x)//b
    return g, x, y """

def inverse(a, n):
    """
    通过扩展欧几里得算法计算逆元
    """
    g, x, _ = exgcd(a, n)
    if g != 1:
        raise ValueError("base is not invertible for the given modulus")
    return x+n if x < 0 else x

def linear_congruence(a, b, c):
    """
    求解线性同余方程的一个特解\\
    ax + by = c
    ax ≡ c mod b
    """
    # 扩展欧几里得算法求解
    g, x, y = exgcd(a, b)
    if c%g != 0:
        raise ValueError("No solution")
    return x*c//g, y*c//g

    # 连分数求解
    """ g = gcd(a,b)
    if c%g != 0:
        raise ValueError("No solution")
    frac = rational_to_contfrac(a,b)
    p,q = convergents_from_contfrac(frac)[-2]
    return c//g*q*(-1)**len(frac), c//g*p*(-1)**(len(frac)-1) """

def rational_to_contfrac(x: int, y: int):
    """
    有理数x/y分解为连分数\\
    [a0, ..., an]
    """
    a = x // y
    pquotients = [a]
    while a * y != x:
        x, y = y, x - a * y
        a = x // y
        pquotients.append(a)
    return pquotients

def contfrac_to_rational(frac: list[int]):
    """
    [a0, ..., an]\\
    连分数还原有理数x/y
    """
    if len(frac) == 0:
        return (0, 1)
    num = frac[-1]
    denom = 1
    for _ in range(-2, -len(frac) - 1, -1):
        num, denom = frac[_] * num + denom, num
    return num, denom

def convergents_from_contfrac(frac):
    '''
    连分数计算渐进分数
    '''
    convs = []
    for i in range(len(frac)):
        convs.append(contfrac_to_rational(frac[0:i+1]))
    return convs

def irrational_sqrtn_to_contfrac(n:int, round=200):
    """
    无理数sqrt(n)分解为连分数\\
    [a0, ..., an]
    """
    m = 0
    d = 1
    a = int(math.sqrt(n))
    result = [a]
    for _ in range(round - 1):
        m = d * a - m
        d = (n - m * m) // d
        a = (int(math.sqrt(n)) + m) // d
        result.append(a)
    return result

def ascii_to_unicode(s:str):
    """
    ASCII英文字母转化为Unicode
    """
    byte = s.encode()
    ans = bytes()
    for i in byte:
        if i >= 0x41 and i <= 0x5a:
            ans += b"\xf0\x9d\x90" + bytes([0x80+i-0x41])
        elif i >= 0x61 and i <= 0x7a:
            ans += b"\xf0\x9d\x90" + bytes([0x9a+i-0x61])
        else:
            ans += bytes([i])
    return ans.decode()
