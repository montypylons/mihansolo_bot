def fix_text_block(text: str) -> str:
    lines = [line.strip() for line in text.splitlines()]

    words = []
    current = []

    for line in lines:
        if line == "":  # blank line = end of word
            if current:
                words.append("".join(current))
                current = []
        else:
            current.append(line)

    # add last word if not followed by blank line
    if current:
        words.append("".join(current))

    return " ".join(words)


# Example usage:
text_block = """
                     U             
                     c             
                     i             
                     P             
                     r             
                     o             
                     t             
                     o             
                     c             
                     o             
                     l             
                                   
                     (             
                     p             
                     i             
                     d             
                     =             
                     1             
                     4             
                     6             
                     6             
                     0             
                     )             
                     >             
                     :             
                                   
                     <             
                     <             
                                   
                     p             
                     o             
                     s             
                     i             
                     t             
                     i             
                     o             
                     n             
                                   
                     s             
                     t             
                     a             
                     r             
                     t             
                     p             
                     o             
                     s             
                                   
                     m             
                     o             
                     v             
                     e             
                     s             
                                   
                     e             
                     2             
                     e             
                     4             
                                   
                     g             
                     7             
                     g             
                     6             
                                   
                     d             
                     1             
                     f             
                     3             
                                   
                     b             
                     8             
                     c             
                     6             
                                   
                     f             
                     1             
                     c             
                     4             
                                   
                     g             
                     8             
                     f             
                     6             
                                   
                     d             
                     2             
                     d             
                     3             
                                   
                     c             
                     6             
                     d             
                     4             
                                   
                     f             
                     3             
                     d             
                     1             
                                   
                     d             
                     7             
                     d             
                     5             
                                   
                     e             
                     4             
                     d             
                     5             
                                   
                     f             
                     6             
                     d             
                     5             
                                   
                     c             
                     2             
                     c             
                     3             
                                   
                     d             
                     4             
                     c             
                     6             
                                   
                     d             
                     1             
                     f             
                     3             
                                   
                     e             
                     7             
                     e             
                     6             
                                   
                     g             
                     1             
                     e             
                     2             
                                   
                     c             
                     6             
                     e             
                     5             
                                   
                     f             
                     3             
                     e             
                     4             
                                   
                     e             
                     5             
                     c             
                     4             
                                   
                     e             
                     4             
                     c             
                     4             
                                   
                     e             
                     6             
                     e             
                     5             
                                   
                     e             
                     1             
                     g             
                     1             
                                   
                     f             
                     8             
                     g             
                     7             
                                   
                     d             
                     3             
                     d             
                     4             
                                   
                     e             
                     8             
                     g             
                     8             
                                   
                     d             
                     4             
                     e             
                     5             
                                   
                     g             
                     7             
                     e             
                     5             
                                   
                     c             
                     1             
                     h             
                     6             
                                   
                     f             
                     8             
                     e             
                     8             
                                   
                     b             
                     1             
                     d             
                     2             
                                   
                     d             
                     5             
                     b             
                     6             
                                   
                     c             
                     4             
                     b             
                     3             
                                   
                     d             
                     8             
                     h             
                     4             
                                   
                     g             
                     2             
                     g             
                     3             
                                   
                     h             
                     4             
                     h             
                     6             
                                   
                     d             
                     2             
                     f             
                     3             
                                   
                     c             
                     8             
                     e             
                     6             
                                   
                     b             
                     3             
                     c             
                     2             
                                   
                     e             
                     6             
                     f             
                     5             
                                   
                     c             
                     2             
                     b             
                     3             
                                   
                     f             
                     5             
                     e             
                     6             
                                   
                     b             
                     3             
                     c             
                     2             
                                   
                     e             
                     6             
                     f             
                     5             
                                   
                     c             
                     2             
                     b             
                     3             
            DEBUG    < engine.py:9à
                     U             
                     c             
                     i             
                     P             
                     r             
                     o             
                     t             
                     o             
                     c             
                     o             
                     l             
                                   
                     (             
                     p             
                     i             
                     d             
                     =             
                     1             
                     4             
                     6             
                     6             
                     0             
                     )             
                     >             
                     :             
                                   
                     <             
                     <             
                                   
                     g             
                     o             
                                   
                     w             
                     t             
                     i             
                     m             
                     e             
                                   
                     3             
                     1             
                     0             
                     7             
                     0             
                                   
                     b             
                     t             
                     i             
                     m             
                     e             
                                   
                     2             
                     4             
                     8             
                     1             
                     9             
                                   
                     w             
                     i             
                     n             
                     c             
                                   
                     1             
                     0             
                     0             
                     0             
                                   
                     b             
                     i             
                     n             
                     c             
                                   
                     1             
                     0             
                     0             
                     0             
[09/17/25   DEBUG    < engine.py:9à
16:29:49]            U             
                     c             
                     i             
                     P             
                     r             
                     o             
                     t             
                     o             
                     c             
                     o             
                     l             
                                   
                     (             
                     p             
                     i             
                     d             
                     =             
                     1             
                     4             
                     6             
                     6             
                     0             
                     )             
                     >             
                     :             
                                   
                     >             
                     >             
                                   
                     i             
                     n             
                     f             
                     o             
                                   
                     d             
                     e             
                     p             
                     t             
                     h             
                                   
                     6             
                     n             
                     o             
                     d             
                     e             
                     s             
                                   
                     1             
                     5             
                     8             
                     7             
                     6             
                     9             
                     6             
                                   
                     s             
                     c             
                     o             
                     r             
                     e             
                                   
                     c             
                     p             
                                   
                     3             
                     3             
                     0             
            DEBUG    < engine.py:9à
                     U             
                     c             
                     i             
                     P             
                     r             
                     o             
                     t             
                     o             
                     c             
                     o             
                     l             
                                   
                     (             
                     p             
                     i             
                     d             
                     =             
                     1             
                     4             
                     6             
                     6             
                     0             
                     )             
                     >             
                     :             
                                   
                     >             
                     >             
                                   
                     b             
                     e             
                     s             
                     t             
                     m             
                     o             
                     v             
                     e             
                                   
                     f             
                     5             
                     e             
                     6             
            INFO     S engine_wrapà
                     o             
                     u             
                     r             
                     c             
                     e             
                     :             
                                   
                     E             
                     n             
                     g             
                     i             
                     n             
                     e             
            INFO     E engine_wrapà
                     v             
                     a             
                     l             
                     u             
                     a             
                     t             
                     i             
                     o             
                     n             
                     :             
                                   
                     3             
                     .             
                     3             
            INFO     D engine_wrapà
                     e             
                     p             
                     t             
                     h             
                     :             
                                   
                     6             
            INFO     N engine_wrapà
                     o             
                     d             
                     e             
                     s             
                     :             
                                   
                     1             
                     .             
                     6             
                     M             
[09/17/25   DEBUG    h connectionpà
16:29:50]            t             
                     t             
                     p             
                     s             
                     :             
                     /             
                     /             
                     l             
                     i             
                     c             
                     h             
                     e             
                     s             
                     s             
                     .             
                     o             
                     r             
                     g             
                     :             
                     4             
                     4             
                     3             
                                   
                     "             
                     P             
                     O             
                     S             
                     T             
                                   
                     /             
                     a             
                     p             
                     i             
                     /             
                     b             
                     o             
                     t             
                     /             
                     g             
                     a             
                     m             
                     e             
                     /             
                     W             
                     4             
                     L             
                     S             
                     p             
                     h             
                     l             
                     Q             
                     /             
                     m             
                     o             
                     v             
                     e             
                     /             
                     f             
                     5             
                     e             
                     6             
                     ?             
                     o             
                     f             
                     f             
                     e             
                     r             
                     i             
                     n             
                     g             
                     D             
                     r             
                     a             
                     w             
                     =             
                     f             
                     a             
                     l             
                     s             
                     e             
                                   
                     H             
                     T             
                     T             
                     P             
                     /             
                     1             
                     1             
                     "             
                                   
                     2             
                     0             
                     0             
                                   
                     1             
                     1             
            DEBUG    G lichess_botà
                     a             
                     m             
                     e             
                                   
                     s             
                     t             
                     a             
                     t             
                     e             
                     :             
                                   
                     {             
                     '             
                     t             
                     y             
                     p             
                     e             
                     '             
                     :             
                                   
                     '             
                     g             
                     a             
                     m             
                     e             
                     S             
                     t             
                     a             
                     t             
                     e             
                     '             
                     ,             
                                   
                     '             
                     m             
                     o             
                     v             
                     e             
                     s             
                     '             
                     :             
                                   
                     '             
                     e             
                     2             
                     e             
                     4             
                                   
                     g             
                     7             
                     g             
                     6             
                                   
                     d             
                     1             
                     f             
                     3             
                                   
                     b             
                     8             
                     c             
                     6             
                                   
                     f             
                     1             
                     c             
                     4             
                                   
                     g             
                     8             
                     f             
                     6             
                                   
                     d             
                     2             
                     d             
                     3             
                                   
                     c             
                     6             
                     d             
                     4             
                                   
                     f             
                     3             
                     d             
                     1             
                                   
                     d             
                     7             
                     d             
                     5             
                                   
                     e             
                     4             
                     d             
                     5             
                                   
                     f             
                     6             
                     d             
                     5             
                                   
                     c             
                     2             
                     c             
                     3             
                                   
                     d             
                     4             
                     c             
                     6             
                                   
                     d             
                     1             
                     f             
                     3             
                                   
                     e             
                     7             
                     e             
                     6             
                                   
                     g             
                     1             
                     e             
                     2             
                                   
                     c             
                     6             
                     e             
                     5             
                                   
                     f             
                     3             
                     e             
                     4             
                                   
                     e             
                     5             
                     c             
                     4             
                                   
                     e             
                     4             
                     c             
                     4             
                                   
                     e             
                     6             
                     e             
                     5             
                                   
                     e             
                     1             
                     g             
                     1             
                                   
                     f             
                     8             
                     g             
                     7             
                                   
                     d             
                     3             
                     d             
                     4             
                                   
                     e             
                     8             
                     g             
                     8             
                                   
                     d             
                     4             
                     e             
                     5             
                                   
                     g             
                     7             
                     e             
                     5             
                                   
                     c             
                     1             
                     h             
                     6             
                                   
                     f             
                     8             
                     e             
                     8             
                                   
                     b             
                     1             
                     d             
                     2             
                                   
                     d             
                     5             
                     b             
                     6             
                                   
                     c             
                     4             
                     b             
                     3             
                                   
                     d             
                     8             
                     h             
                     4             
                                   
                     g             
                     2             
                     g             
                     3             
                                   
                     h             
                     4             
                     h             
                     6             
                                   
                     d             
                     2             
                     f             
                     3             
                                   
                     c             
                     8             
                     e             
                     6             
                                   
                     b             
                     3             
                     c             
                     2             
                                   
                     e             
                     6             
                     f             
                     5             
                                   
                     c             
                     2             
                     b             
                     3             
                                   
                     f             
                     5             
                     e             
                     6             
                                   
                     b             
                     3             
                     c             
                     2             
                                   
                     e             
                     6             
                     f             
                     5             
                                   
                     c             
                     2             
                     b             
                     3             
                                   
                     f             
                     5             
                     e             
                     6             
                     '             
                     ,             
                                   
                     '             
                     w             
                     t             
                     i             
                     m             
                     e             
                     '             
                     :             
                                   
                     3             
                     1             
                     0             
                     7             
                     0             
                     ,             
                                   
                     '             
                     b             
                     t             
                     i             
                     m             
                     e             
                     '             
                     :             
                                   
                     2             
                     5             
                     9             
                     7             
                     0             
                     ,             
                                   
                     '             
                     w             
                     i             
                     n             
                     c             
                     '             
                     :             
                                   
                     1             
                     0             
                     0             
                     0             
                     ,             
                                   
                     '             
                     b             
                     i             
                     n             
                     c             
                     '             
                     :             
                                   
                     1             
                     0             
                     0             
                     0             
                     ,             
                                   
                     '             
                     s             
                     t             
                     a             
                     t             
                     u             
                     s             
                     '             
                     :             
                                   
                     '             
                     s             
                     t             
                     a             
                     r             
                     t             
                     e             
                     d             
                     '             
                     }             
            DEBUG    E lichess_botà
                     v             
                     e             
                     n             
                     t             
                     :             
                                   
                     {             
                     '             
                     t             
                     y             
                     p             
                     e             
                     '             
                     :             
                                   
                     '             
                     g             
                     a             
                     m             
                     e             
                     F             
                     i             
                     n             
                     i             
                     s             
                     h             
                     '             
                     ,             
                                   
                     '             
                     g             
                     a             
                     m             
                     e             
                     '             
                     :             
                                   
                     {             
                     '             
                     f             
                     u             
                     l             
                     l             
                     I             
                     d             
                     '             
                     :             
                                   
                     '             
                     W             
                     4             
                     L             
                     S             
                     p             
                     h             
                     l             
                     Q             
                     c             
                     J             
                     4             
                     d             
                     '             
                     ,             
                                   
                     '             
                     g             
                     a             
                     m             
                     e             
                     I             
                     d             
                     '             
                     :             
                                   
                     '             
                     W             
                     4             
                     L             
                     S             
                     p             
                     h             
                     l             
                     Q             
                     '             
                     ,             
                                   
                     '             
                     f             
                     e             
                     n             
                     '             
                     :             
                                   
                     '             
                     r             
                     3             
                     r             
                     1             
                     k             
                     1             
                     /             
                     p             
                     p             
                     p             
                     2             
                     p             
                     1             
                     p             
                     /             
                     1             
                     n             
                     2             
                     b             
                     1             
                     p             
                     q             
                     /             
                     4             
                     b             
                     3             
                     /             
                     8             
                     /             
                     1             
                     Q             
                     P             
                     2             
                     N             
                     P             
                     1             
                     /             
                     P             
                     P             
                     2             
                     N             
                     P             
                     1             
                     P             
                     /             
                     R             
                     4             
                     R             
                     K             
                     1             
                                   
                     w             
                     -             
                     -             
                     1             
                     0             
                                   
                     2             
                     4             
                     '             
                     ,             
                                   
                     '             
                     c             
                     o             
                     l             
                     o             
                     r             
                     '             
                     :             
                                   
                     '             
                     b             
                     l             
                     a             
                     c             
                     k             
                     '             
                     ,             
                                   
                     '             
                     l             
                     a             
                     s             
                     t             
                     M             
                     o             
                     v             
                     e             
                     '             
                     :             
                                   
                     '             
                     f             
                     5             
                     e             
                     6             
                     '             
                     ,             
                                   
                     '             
                     s             
                     o             
                     u             
                     r             
                     c             
                     e             
                     '             
                     :             
                                   
                     '             
                     f             
                     r             
                     i             
                     e             
                     n             
                     d             
                     '             
                     ,             
                                   
                     '             
                     s             
                     t             
                     a             
                     t             
                     u             
                     s             
                     '             
                     :             
                                   
                     {             
                     '             
                     i             
                     d             
                     '             
                     :             
                                   
                     3             
                     4             
                     ,             
                                   
                     '             
                     n             
                     a             
                     m             
                     e             
                     '             
                     :             
                                   
                     '             
                     d             
                     r             
                     a             
                     w             
                     '             
                     }             
                     ,             
                                   
                     '             
                     v             
                     a             
                     r             
                     i             
                     a             
                     n             
                     t             
                     '             
                     :             
                                   
                     {             
                     '             
                     k             
                     e             
                     y             
                     '             
                     :             
                                   
                     '             
                     s             
                     t             
                     a             
                     n             
                     d             
                     a             
                     r             
                     d             
                     '             
                     ,             
                                   
                     '             
                     n             
                     a             
                     m             
                     e             
                     '             
                     :             
                                   
                     '             
                     S             
                     t             
                     a             
                     n             
                     d             
                     a             
                     r             
                     d             
                     '             
                     }             
                     ,             
                                   
                     '             
                     s             
                     p             
                     e             
                     e             
                     d             
                     '             
                     :             
                                   
                     '             
                     b             
                     u             
                     l             
                     l             
                     e             
                     t             
                     '             
                     ,             
                                   
                     '             
                     p             
                     e             
                     r             
                     f             
                     '             
                     :             
                                   
                     '             
                     b             
                     u             
                     l             
                     l             
                     e             
                     t             
                     '             
                     ,             
                                   
                     '             
                     r             
                     a             
                     t             
                     e             
                     d             
                     '             
                     :             
                                   
                     T             
                     r             
                     u             
                     e             
                     ,             
                                   
                     '             
                     h             
                     a             
                     s             
                     M             
                     o             
                     v             
                     e             
                     d             
                     '             
                     :             
                                   
                     T             
                     r             
                     u             
                     e             
                     ,             
                                   
                     '             
                     o             
                     p             
                     p             
                     o             
                     n             
                     e             
                     n             
                     t             
                     '             
                     :             
                                   
                     {             
                     '             
                     i             
                     d             
                     '             
                     :             
                                   
                     '             
                     m             
                     a             
                     i             
                     a             
                     5             
                     '             
                     ,             
                                   
                     '             
                     u             
                     s             
                     e             
                     r             
                     n             
                     a             
                     m             
                     e             
                     '             
                     :             
                                   
                     '             
                     B             
                     O             
                     T             
                                   
                     m             
                     a             
                     i             
                     a             
                     5             
                     '             
                     ,             
                                   
                     '             
                     r             
                     a             
                     t             
                     i             
                     n             
                     g             
                     '             
                     :             
                                   
                     1             
                     5             
                     8             
                     4             
                     ,             
                                   
                     '             
                     r             
                     a             
                     t             
                     i             
                     n             
                     g             
                     D             
                     i             
                     f             
                     f             
                     '             
                     :             
                                   
                     1             
                     }             
                     ,             
                                   
                     '             
                     i             
                     s             
                     M             
                     y             
                     T             
                     u             
                     r             
                     n             
                     '             
                     :             
                                   
                     F             
                     a             
                     l             
                     s             
                     e             
                     ,             
                                   
                     '             
                     s             
                     e             
                     c             
                     o             
                     n             
                     d             
                     s             
                     L             
                     e             
                     f             
                     t             
                     '             
                     :             
                                   
                     2             
                     6             
                     ,             
                                   
                     '             
                     r             
                     a             
                     t             
                     i             
                     n             
                     g             
                     D             
                     i             
                     f             
                     f             
                     '             
                     :             
                                   
                     -             
                     1             
                     ,             
                                   
                     '             
                     c             
                     o             
                     m             
                     p             
                     a             
                     t             
                     '             
                     :             
                                   
                     {             
                     '             
                     b             
                     o             
                     t             
                     '             
                     :             
                                   
                     T             
                     r             
                     u             
                     e             
                     ,             
                                   
                     '             
                     b             
                     o             
                     a             
                     r             
                     d             
                     '             
                     :             
                                   
                     F             
                     a             
                     l             
                     s             
                     e             
                     }             
                     ,             
                                   
                     '             
                     i             
                     d             
                     '             
                     :             
                                   
                     '             
                     W             
                     4             
                     L             
                     S             
                     p             
                     h             
                     l             
                     Q             
                     '             
                     }             
                     }             
            DEBUG    G lichess_botà
                     a             
                     m             
                     e             
                                   
                     s             
                     t             
                     a             
                     t             
                     e             
                     :             
                                   
                     {             
                     '             
                     t             
                     y             
                     p             
                     e             
                     '             
                     :             
                                   
                     '             
                     g             
                     a             
                     m             
                     e             
                     S             
                     t             
                     a             
                     t             
                     e             
                     '             
                     ,             
                                   
                     '             
                     m             
                     o             
                     v             
                     e             
                     s             
                     '             
                     :             
                                   
                     '             
                     e             
                     2             
                     e             
                     4             
                                   
                     g             
                     7             
                     g             
                     6             
                                   
                     d             
                     1             
                     f             
                     3             
                                   
                     b             
                     8             
                     c             
                     6             
                                   
                     f             
                     1             
                     c             
                     4             
                                   
                     g             
                     8             
                     f             
                     6             
                                   
                     d             
                     2             
                     d             
                     3             
                                   
                     c             
                     6             
                     d             
                     4             
                                   
                     f             
                     3             
                     d             
                     1             
                                   
                     d             
                     7             
                     d             
                     5             
                                   
                     e             
                     4             
                     d             
                     5             
                                   
                     f             
                     6             
                     d             
                     5             
                                   
                     c             
                     2             
                     c             
                     3             
                                   
                     d             
                     4             
                     c             
                     6             
                                   
                     d             
                     1             
                     f             
                     3             
                                   
                     e             
                     7             
                     e             
                     6             
                                   
                     g             
                     1             
                     e             
                     2             
                                   
                     c             
                     6             
                     e             
                     5             
                                   
                     f             
                     3             
                     e             
                     4             
                                   
                     e             
                     5             
                     c             
                     4             
                                   
                     e             
                     4             
                     c             
                     4             
                                   
                     e             
                     6             
                     e             
                     5             
                                   
                     e             
                     1             
                     g             
                     1             
                                   
                     f             
                     8             
                     g             
                     7             
                                   
                     d             
                     3             
                     d             
                     4             
                                   
                     e             
                     8             
                     g             
                     8             
                                   
                     d             
                     4             
                     e             
                     5             
                                   
                     g             
                     7             
                     e             
                     5             
                                   
                     c             
                     1             
                     h             
                     6             
                                   
                     f             
                     8             
                     e             
                     8             
                                   
                     b             
                     1             
                     d             
                     2             
                                   
                     d             
                     5             
                     b             
                     6             
                                   
                     c             
                     4             
                     b             
                     3             
                                   
                     d             
                     8             
                     h             
                     4             
                                   
                     g             
                     2             
                     g             
                     3             
                                   
                     h             
                     4             
                     h             
                     6             
                                   
                     d             
                     2             
                     f             
                     3             
                                   
                     c             
                     8             
                     e             
                     6             
                                   
                     b             
                     3             
                     c             
                     2             
                                   
                     e             
                     6             
                     f             
                     5             
                                   
                     c             
                     2             
                     b             
                     3             
                                   
                     f             
                     5             
                     e             
                     6             
                                   
                     b             
                     3             
                     c             
                     2             
                                   
                     e             
                     6             
                     f             
                     5             
                                   
                     c             
                     2             
                     b             
                     3             
                                   
                     f             
                     5             
                     e             
                     6             
                     '             
                     ,             
                                   
                     '             
                     w             
                     t             
                     i             
                     m             
                     e             
                     '             
                     :             
                                   
                     3             
                     1             
                     0             
                     7             
                     0             
                     ,             
                                   
                     '             
                     b             
                     t             
                     i             
                     m             
                     e             
                     '             
                     :             
                                   
                     2             
                     5             
                     9             
                     7             
                     0             
                     ,             
                                   
                     '             
                     w             
                     i             
                     n             
                     c             
                     '             
                     :             
                                   
                     1             
                     0             
                     0             
                     0             
                     ,             
                                   
                     '             
                     b             
                     i             
                     n             
                     c             
                     '             
                     :             
                                   
                     1             
                     0             
                     0             
                     0             
                     ,             
                                   
                     '             
                     s             
                     t             
                     a             
                     t             
                     u             
                     s             
                     '             
                     :             
                                   
                     '             
                     d             
                     r             
                     a             
                     w             
                     '             
                     }             
            INFO     G lichess_botà
                     a             
                     m             
                     e             
                                   
                     e             
                     n             
                     d             
                     e             
                     d             
                                   
                     i             
                     n             
                                   
                     a             
                     d             
                     r             
                     a             
                     w             
                     .             
            INFO     G lichess_botà
                     a             
                     m             
                     e             
                                   
                     d             
                     r             
                     a             
                     w             
                     n             
                                   
                     b             
                     y             
                                   
                     t             
                     h             
                     r             
                     e             
                     e             
                     f             
                     o             
                     l             
                     d             
                                   
                     r             
                     e             
                     p             
                     e             
                     t             
                     i             
                     t             
                     i             
                     o             
                     n             
                     .             
            INFO     * conversatioà
                     *             
                     *             
                                   
                     h             
                     t             
                     t             
                     p             
                     s             
                     :             
                     /             
                     /             
                     l             
                     i             
                     c             
                     h             
                     e             
                     s             
                     s             
                     .             
                     o             
                     r             
                     g             
                     /             
                     W             
                     4             
                     L             
                     S             
                     p             
                     h             
                     l             
                     Q             
                     /             
                     b             
                     l             
                     a             
                     c             
                     k             
                                   
                     [             
                     p             
                     l             
                     a             
                     y             
                     e             
                     r             
                     ]             
                                   
                     M             
                     i             
                     h             
                     a             
                     n             
                     S             
                     o             
                     l             
                     o             
                     :             
                                   
                     G             
                     o             
                     o             
                     d             
                                   
                     g             
                     a             
                     m             
                     e             
                     !             
            DEBUG    h connectionpà
                     t             
                     t             
                     p             
                     s             
                     :             
                     /             
                     /             
                     l             
                     i             
                     c             
                     h             
                     e             
                     s             
                     s             
                     .             
                     o             
                     r             
                     g             
                     :             
                     4             
                     4             
                     3             
                                   
                     "             
                     P             
                     O             
                     S             
                     T             
                                   
                     /             
                     a             
                     p             
                     i             
                     /             
                     b             
                     o             
                     t             
                     /             
                     g             
                     a             
                     m             
                     e             
                     /             
                     W             
                     4             
                     L             
                     S             
                     p             
                     h             
                     l             
                     Q             
                     /             
                     c             
                     h             
                     a             
                     t             
                                   
                     H             
                     T             
                     T             
                     P             
                     /             
                     1             
                     1             
                     "             
                                   
                     2             
                     0             
                     0             
                                   
                     1             
                     1             
            INFO     * conversatioà
                     *             
                     *             
                                   
                     h             
                     t             
                     t             
                     p             
                     s             
                     :             
                     /             
                     /             
                     l             
                     i             
                     c             
                     h             
                     e             
                     s             
                     s             
                     .             
                     o             
                     r             
                     g             
                     /             
                     W             
                     4             
                     L             
                     S             
                     p             
                     h             
                     l             
                     Q             
                     /             
                     b             
                     l             
                     a             
                     c             
                     k             
                                   
                     [             
                     s             
                     p             
                     e             
                     c             
                     t             
                     a             
                     t             
                     o             
                     r             
                     ]             
                                   
                     M             
                     i             
                     h             
                     a             
                     n             
                     S             
                     o             
                     l             
                     o             
                     :             
                                   
                     T             
                     h             
                     a             
                     n             
                     k             
                     s             
                                   
                     f             
                     o             
                     r             
                                   
                     w             
                     a             
                     t             
                     c             
                     h             
                     i             
                     n             
                     g             
                     !             
            DEBUG    h connectionpà
                     t             
                     t             
                     p             
                     s             
                     :             
                     /             
                     /             
                     l             
                     i             
                     c             
                     h             
                     e             
                     s             
                     s             
                     .             
                     o             
                     r             
                     g             
                     :             
                     4             
                     4             
                     3             
                                   
                     "             
                     P             
                     O             
                     S             
                     T             
                                   
                     /             
                     a             
                     p             
                     i             
                     /             
                     b             
                     o             
                     t             
                     /             
                     g             
                     a             
                     m             
                     e             
                     /             
                     W             
                     4             
                     L             
                     S             
                     p             
                     h             
                     l             
                     Q             
                     /             
                     c             
                     h             
                     a             
                     t             
                                   
                     H             
                     T             
                     T             
                     P             
                     /             
                     1             
                     1             
                     "             
                                   
                     2             
                     0             
                     0             
                                   
                     1             
                     1             
            DEBUG    < engine.py:9à
                     U             
                     c             
                     i             
                     P             
                     r             
                     o             
                     t             
                     o             
                     c             
                     o             
                     l             
                                   
                     (             
                     p             
                     i             
                     d             
                     =             
                     1             
                     4             
                     6             
                     6             
                     0             
                     )             
                     >             
                     :             
                                   
                     <             
                     <             
                                   
                     i             
                     s             
                     r             
                     e             
                     a             
                     d             
                     y             
            DEBUG    < engine.py:9à
                     U             
                     c             
                     i             
                     P             
                     r             
                     o             
                     t             
                     o             
                     c             
                     o             
                     l             
                                   
                     (             
                     p             
                     i             
                     d             
                     =             
                     1             
                     4             
                     6             
                     6             
                     0             
                     )             
                     >             
                     :             
                                   
                     >             
                     >             
                                   
                     r             
                     e             
                     a             
                     d             
                     y             
                     o             
                     k             
            DEBUG    < engine.py:9à
                     U             
                     c             
                     i             
                     P             
                     r             
                     o             
                     t             
                     o             
                     c             
                     o             
                     l             
                                   
                     (             
                     p             
                     i             
                     d             
                     =             
                     1             
                     4             
                     6             
                     6             
                     0             
                     )             
                     >             
                     :             
                                   
                     <             
                     <             
                                   
                     q             
                     u             
                     i             
                     t             
            DEBUG    < engine.py:9à
                     U             
                     c             
                     i             
                     P             
                     r             
                     o             
                     t             
                     o             
                     c             
                     o             
                     l             
                                   
                     (             
                     p             
                     i             
                     d             
                     =             
                     1             
                     4             
                     6             
                     6             
                     0             
                     )             
                     >             
                     :             
                                   
                     P             
                     r             
                     o             
                     c             
                     e             
                     s             
                     s             
                                   
                     e             
                     x             
                     i             
                     t             
                     e             
                     d             
            DEBUG    < engine.py:9à
                     U             
                     c             
                     i             
                     P             
                     r             
                     o             
                     t             
                     o             
                     c             
                     o             
                     l             
                                   
                     (             
                     p             
                     i             
                     d             
                     =             
                     1             
                     4             
                     6             
                     6             
                     0             
                     )             
                     >             
                     :             
                                   
                     C             
                     o             
                     n             
                     n             
                     e             
                     c             
                     t             
                     i             
                     o             
                     n             
                                   
                     l             
                     o             
                     s             
                     t             
                                   
                     (             
                     e             
                     x             
                     i             
                     t             
                                   
                     c             
                     o             
                     d             
                     e             
                     :             
                                   
                     0             
                     ,             
                                   
                     e             
                     r             
                     r             
                     o             
                     r             
                     :             
                                   
                     N             
                     o             
                     n             
                     e             
                     )             
            INFO     - lichess_botà
                     -             
                     -             
                                   
                     h             
                     t             
                     t             
                     p             
                     s             
                     :             
                     /             
                     /             
                     l             
                     i             
                     c             
                     h             
                     e             
                     s             
                     s             
                     .             
                     o             
                     r             
                     g             
                     /             
                     W             
                     4             
                     L             
                     S             
                     p             
                     h             
                     l             
                     Q             
                     /             
                     b             
                     l             
                     a             
                     c             
                     k             
                                   
                     G             
                     a             
                     m             
                     e             
                                   
                     o             
                     v             
                     e             
                     r             
            DEBUG    E lichess_botà
                     v             
                     e             
                     n             
                     t             
                     :             

"""

print(fix_text_block(text_block))
