[0] -> 0
[1] -> 1
[2] -> 0
[3] -> 1

------------------
    src[0][0] miss
    0: src[0]
    1:

    dst[0][0] miss
    0: dst[0]
    1:

    src[0][1] miss
    0: src[0]
    1:

    dst[1][0] miss
    0: src[0]
    1: dst[1]

    src[0][2] hit
    0: src[0]
    1: dst[1]

    dst[2][0] miss
    0: dst[2]
    1: dst[1]

    src[0][3] miss
    0: src[0]
    1: dst[1]

    dst[3][0] miss
    0: src[0]
    1: dst[3]
------------------

    src[1][0] miss
    0: src[0]
    1: src[1]

    dst[0][1] miss
    0: dst[0]
    1: src[1]

    src[1][1] hit
    0: dst[0]
    1: src[1]

    dst[1][1] miss
    0: dst[0]
    1: dst[1]

    src[1][2] miss
    0: dst[0]
    1: src[1]

    dst[2][1] miss
    0: dst[2]
    1: src[1]

    src[1][3] hit
    0: dst[2]
    1: src[1]

    dst[3][1] miss
    0: dst[2]
    1: dst[3]
------------------

    src[2][0] miss
    0: src[2]
    1: dst[3]

    dst[0][2] miss
    0: dst[0]
    1: dst[3]

    src[2][1] miss
    0: src[2]
    1: dst[3]

    dst[1][2] miss
    0: src[2]
    1: dst[1]

    src[2][2] hit
    0: src[2]
    1: dst[1]

    dst[2][2] miss
    0: dst[2]
    1: dst[1]

    src[2][3] miss
    0: src[2]
    1: dst[1]

    dst[3][2] miss
    0: src[2]
    1: dst[3]
------------------

    src[3][0] miss
    0: src[2]
    1: src[3]

    dst[0][3] miss
    0: dst[0]
    1: src[3]

    src[3][1] hit
    0: dst[0]
    1: src[3]

    dst[1][3] miss
    0: dst[0]
    1: dst[1]

    src[3][2] miss
    0: dst[0]
    1: src[3]

    dst[2][3] miss
    0: dst[2]
    1: src[3]

    src[3][3] hit
    0: dst[2]
    1: src[3]

    dst[3][3] miss
    0: dst[2]
    1: dst[3]

dst:
    m m m m
    m m m m
    m m m m
    m m m m
src:
    m m h m
    m h m h
    m m h m
    m h m h