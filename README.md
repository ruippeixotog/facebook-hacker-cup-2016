# Facebook Hacker Cup 2016

This repository contains my solutions to the problems from [Facebook Hacker Cup 2016][1]. These solutions are provided "as is" - I give no guarantees that they will work as expected.

## Instructions

You can compile all the problems by issuing the following command:

    $ make

If you want to compile only a specific problem, issue the following command, replacing `<problem_id>` with the section and identifier of the problem you want to compile (see section "Problems Solved" for the list of possible identifiers):

    $ make <problem_id>

Running a compiled problem is just a matter of executing a command similar to the next one, replacing `<problem_id>` with the identifier of the desired problem:

    $ ./<problem_id>

Unless stated otherwise, every problem in this repository reads from the standard input and writes to the standard output.

## Problems Solved

The following is the list of the problems solved. Each problem identifier is specified between round brackets. Problems marked with ✓ are done, while problems with ✗ are not complete or aren't efficient enough for the problem's limits.

### Qualification Round

* ✓ [10: Boomerang Constellations][qual1] (`boomerang-constellation`)
* ✓ [25: High Security][qual2] (`high-security`)
* ✓ [25: The Price is Correct][qual3] (`the-price-is-correct`)
* ✓ [40: Text Editor][qual4] (`text-editor`) [*]

[*] This solution requires an increased stack size. In Unix systems you can remove the stack size cap with the command `ulimit -s unlimited`. The change applies only to processes running in the shell in which the command is executed.

### Round 1

* ✓ [15: Coding Contest Creation][round11] (`coding-contest-creation`)
* ✓ [20: Laundro, Matt][round12] (`laundro-matt`)
* ✓ [25: Yachtzee][round13] (`yachtzee`)
* ✓ [40: Boomerang Tournament][round14] (`boomerang-tournament`)

[1]: https://www.facebook.com/hackercup
[qual1]: https://www.facebook.com/hackercup/problem/910374079035613/
[qual2]: https://www.facebook.com/hackercup/problem/1527664744192390/
[qual3]: https://www.facebook.com/hackercup/problem/881509321917182/
[qual4]: https://www.facebook.com/hackercup/problem/1525154397757404/
[round11]: https://www.facebook.com/hackercup/problem/798506286925018/
[round12]: https://www.facebook.com/hackercup/problem/1611251319125133/
[round13]: https://www.facebook.com/hackercup/problem/512731402225321/
[round14]: https://www.facebook.com/hackercup/problem/1424196571244550/
