# -*- coding: utf-8 -*-

ONES = {
    1   :   "one",
    2   :   "two",
    3   :   "three",
    4   :   "four",
    5   :   "five",
    6   :   "six",
    7   :   "seven",
    8   :   "eight",
    9   :   "nine"
}

TEENS = {
    10  :   "ten",
    11  :   "eleven",
    12  :   "twelve",
    13  :   "thirteen",
    14  :   "fourteen",
    15  :   "fifteen",
    16  :   "sixteen",
    17  :   "seventeen",
    18  :   "eighteen",
    19  :   "nineteen"
}

TENS = {
    20  :   "twenty",
    30  :   "thirty",
    40  :   "forty",
    50  :   "fifty",
    60  :   "sixty",
    70  :   "seventy",
    80  :   "eighty",
    90  :   "ninety"
}

HUNDRED     =   "hundred"
THOUSAND    =   "one""thousand"

ONES_SUM    = len("".join(ONES.values()))
TEENS_SUM   = len("".join(TEENS.values()))
TENS_SUM    = 10 * sum(len(i) for i in TENS.values()) + 8 * ONES_SUM
HUNDRED_SUM = ONES_SUM + TEENS_SUM + TENS_SUM
THOUSAND_SUM = ONES_SUM * 100   \
        + HUNDRED_SUM * 9       \
        + len(HUNDRED) * 9      \
        + len(HUNDRED + "and") * 891
TOTAL_SUM   = HUNDRED_SUM + THOUSAND_SUM + len(THOUSAND)

if __name__ == "__main__":
    print(TOTAL_SUM)
