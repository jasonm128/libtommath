/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tstdenis82@gmail.com, http://math.libtomcrypt.com
 */
#ifndef TOMMATH_PRIV_H_
#define TOMMATH_PRIV_H_

#include <tommath.h>

#ifdef __cplusplus
extern "C" {
#endif

/* lowlevel functions, do not call! */
int s_mp_add(mp_int *a, mp_int *b, mp_int *c);
int s_mp_sub(mp_int *a, mp_int *b, mp_int *c);
#define s_mp_mul(a, b, c) s_mp_mul_digs(a, b, c, (a)->used + (b)->used + 1)
int fast_s_mp_mul_digs(mp_int *a, mp_int *b, mp_int *c, int digs);
int s_mp_mul_digs(mp_int *a, mp_int *b, mp_int *c, int digs);
int fast_s_mp_mul_high_digs(mp_int *a, mp_int *b, mp_int *c, int digs);
int s_mp_mul_high_digs(mp_int *a, mp_int *b, mp_int *c, int digs);
int fast_s_mp_sqr(mp_int *a, mp_int *b);
int s_mp_sqr(mp_int *a, mp_int *b);
int mp_karatsuba_mul(mp_int *a, mp_int *b, mp_int *c);
int mp_toom_mul(mp_int *a, mp_int *b, mp_int *c);
int mp_karatsuba_sqr(mp_int *a, mp_int *b);
int mp_toom_sqr(mp_int *a, mp_int *b);
int fast_mp_invmod(mp_int *a, mp_int *b, mp_int *c);
int mp_invmod_slow (mp_int * a, mp_int * b, mp_int * c);
int fast_mp_montgomery_reduce(mp_int *a, mp_int *m, mp_digit mp);
int mp_exptmod_fast(mp_int *G, mp_int *X, mp_int *P, mp_int *Y, int mode);
int s_mp_exptmod (mp_int * G, mp_int * X, mp_int * P, mp_int * Y, int mode);
void bn_reverse(unsigned char *s, int len);

extern const char *mp_s_rmap;

/* Fancy macro to set an MPI from another type.
 * There are several things assumed:
 *  x is the counter and unsigned
 *  a is the pointer to the MPI
 *  b is the original value that should be set in the MPI.
 */
#define MP_SET_XLONG(func_name, type)                    \
int func_name (mp_int * a, type b)                       \
{                                                        \
  unsigned int  x;                                       \
  int           res;                                     \
                                                         \
  mp_zero (a);                                           \
                                                         \
  /* set four bits at a time */                          \
  for (x = 0; x < (sizeof(type) * 2); x++) {             \
    /* shift the number up four bits */                  \
    if ((res = mp_mul_2d (a, 4, a)) != MP_OKAY) {        \
      return res;                                        \
    }                                                    \
                                                         \
    /* OR in the top four bits of the source */          \
    a->dp[0] |= (b >> ((sizeof(type) * 8) - 4)) & 15;    \
                                                         \
    /* shift the source up to the next four bits */      \
    b <<= 4;                                             \
                                                         \
    /* ensure that digits are not clamped off */         \
    a->used += 1;                                        \
  }                                                      \
  mp_clamp (a);                                          \
  return MP_OKAY;                                        \
}

#ifdef __cplusplus
   }
#endif

#endif


/* $Source$ */
/* $Revision$ */
/* $Date$ */
