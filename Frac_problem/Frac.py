import math
import gcd

def get_lcm(num1, num2):
    return ( num1*num2 ) // gcd(num1, num2)

class Frac:
    def __init__(self, numerator_, denominator_)
        gcd_ = gcd(numerator_, denominator_)
        self.numertr = numerator_ // gcd_
        self.denomntr = denominator_ // gcd_


    def __repr__(self)
        return 'Frac({}/{})'.format(self.numertr, self.denomntr)

    def __str__(self)
        return '{}/{}'.format(self.numertr, self.denomntr)

    def __сopy__(self)
        return Frac(self.numertr, self.denomntr)

    def normalize(self)
        gcd_ = gcd(self.numertr, self.denomntr)
        self.numertr // gcd_
        self.denomntr // gcd_

    def __iadd__(self, rhs)
        lcm_ = get_lcm(self.denominator, rhs.denomntr)
        self.numerator = self.numerator * (lcm // self.denomntr) + rhs.numertr * (lcm // rhs.denomntr)
        self.denomntr = lcm_

        normalize(self)
        return self

    def __add__(self, rhs)
        res = self.__copy__()
        res += rhs

        return res
