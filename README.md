This is a simple MT19937 random number generator. The code is straightforward conversion of the Mersenne Twister pseudocode published on the [Wikipedia page](http://en.wikipedia.org/wiki/Mersenne_twister) into C (1989 standard).

The generator is initialized by the `ms_init` function. After this, 32-bit pseudorandom numbers can be generated by calling `ms_rand()`. If the user doesn't call `ms_init` prior to the first call to `ms_rand()`, the generator is seeded to the system time (unless lines 6 and 7 are commented out, in which case, you'd better seed the generator with something or you'll get all zeroes). The `main` function included in this code is a very simple demo that counts instances of generated pseudorandom numbers between 0 and 19 and prints the counts.