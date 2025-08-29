#ifndef INT128_H
#define INT128_H


/* 128-bit integer limits. */

#define UINT128_MAX ((__uint128_t)-1)
#define INT128_MAX  ((__int128_t)(UINT128_MAX >> 1))
#define INT128_MIN  (-INT128_MAX - 1)






#endif /* INT128_H */
