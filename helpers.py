from nltk.tokenize import sent_tokenize
from nltk.tokenize import WhitespaceTokenizer
import string


def lines(a, b):
    """Return lines in both a and b"""

    a = a.splitlines()  # splitting file on lines
    b = b.splitlines()
    dubl = set(a) & set(b)  # intersection of boths sets
    return dubl


def sentences(a, b):
    """Return sentences in both a and b"""

    alist = []
    blist = []
    alist = sent_tokenize(a, language='english')  # splitting file on words
    blist = sent_tokenize(b, language='english')  # splitting file on words
    dubl = set(alist) & set(blist)  # intersection of boths sets
    return dubl


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    alist = []
    blist = []
    for i in range(0, len(a) - n + 1):
        x = a[i:i + n]  # splitting tex on substring length of n
        alist.append(x)
    for i in range(0, len(b) - n + 1):
        x = b[i:i + n]  # splitting tex on substring length of n
        blist.append(x)
    dubl = set(alist) & set(blist)  # intersection of boths sets
    return dubl