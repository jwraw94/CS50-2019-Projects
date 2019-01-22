def lines(a, b):
    """Return lines in both a and b"""

    # TODO
    # Split into lines by endline char \n ["L1", "L2", ... ]
    alines = a.splitlines()
    acount = len(alines)
    i = 0
    # Create array to hold the same lines
    samelines = []

    # Find all lines that appear in both a and b, but have not already been added.
    while i < acount:
        if alines[i] in b and alines[i] not in samelines:
            samelines.append(alines[i])
            i += 1
        else:
            i += 1

    # Return the number of matching lines
    return samelines


def sentences(a, b):
    """Return sentences in both a and b"""
    from nltk.tokenize import sent_tokenize

    # TODO
    # Split into lines by end of sentence as per nltk
    asentences = sent_tokenize(a)
    acounts = len(asentences)
    j = 0
    # Create array to hold the same sentences
    samesentences = []

    # Find all sentences that appear in both a and b, but have not already been added.
    while j < acounts:
        if asentences[j] in b and asentences[j] not in samesentences:
            samesentences.append(asentences[j])
            j += 1
        else:
            j += 1

    return samesentences


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    from nltk.tokenize import word_tokenize

    # TODO
    # Break the input file into a list of words.
    astrings = word_tokenize(a)
    acountstr = len(astrings)
    j = -1
    k = 0
    samestrings = []

    # Iterate through the list of words, until the last word.
    while j + 1 < acountstr:
        k = 0
        j += 1
        # Compare the current letter + n section of a string, to words in the input file. Add to list if present in both.
        while k <= len(astrings[j]) - n:
            if astrings[j][k: k + n] in b and astrings[j][k: k + n] not in samestrings:
                samestrings.append(astrings[j][k: k + n])
                k += 1
            else:
                k += 1

    return samestrings