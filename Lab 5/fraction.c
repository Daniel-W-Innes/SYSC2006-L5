/* fraction.c - SYSC 2006 Winter 2018 Lab 5 */

#include <stdlib.h>  // abs(x)
#include <stdio.h>   // printf
#include <assert.h>  // assert

#include "fraction.h"

/* Print the fraction pointed to by pf in the form a/b. 
 */
void print_fraction(const fraction_t *pf) {
    printf("%d/%d", pf->num, pf->den);
}

/* Return the greatest common divisor of integers a and b; 
   i.e., return the largest positive integer that evenly divides 
   both values.
*/
int gcd(int a, int b) {
    int q = abs(a);
    int p = abs(b);
    int r = q % p;
    while (r != 0) {
        q = p;
        p = r;
        r = q % p;
    }
    return p;
}
/* Convert the fraction pointed to by pf to reduced form.

   This means that:
   (1) if the numerator is equal to 0 the denominator is always 1.
   (2) if the numerator is not equal to 0 the denominator is always
       positive, and the numerator and denominator have no common
       divisors other than 1.

   In other words,
   (1) if the numerator is 0 the denominator is always changed to 1.
   (2) if the numerator and denominator are both negative, both values
       are made positive, or if the numerator is positive and the 
       denominator is negative, the numerator is made negative and the 
       denominator is made positive.
   (3) the numerator and denominator are both divided by their greatest
       common divisor. 
*/
void reduce(fraction_t *pf) {
    if (pf->num == 0) {
        pf->den = 1;
    } else {
        if (pf->num < 0 && pf->den < 0) {
            pf->num = abs(pf->num);
            pf->den = abs(pf->den);
        } else if (pf->num < 0 || pf->den < 0) {
            pf->num = -1 * abs(pf->num);
            pf->den = abs(pf->den);
        }
        int gcd1 = gcd(pf->num, pf->den);
        pf->num /= gcd1;
        pf->den /= gcd1;
    }
}

/* InZitialize the fraction pointed to by new_fraction
   with numerator a and denominator b.
   Print an error message and terminate the calling program via exit()
   if the denominator is 0.
   The fraction returned by this function is always in reduced form
   (see documentation for reduce).
*/
void make_fraction(int a, int b, fraction_t *new_fraction) {
    if (b == 0)
        exit(EXIT_FAILURE);
    *new_fraction = (fraction_t) {a, b};
    reduce(new_fraction);
}

/* Initialize the fraction pointed to by sum with the sum of
   the fractions pointed to by pf1 and pf2.
   The fraction created by this function is always in reduced form
   (see documentation for reduce).
*/
void add_fractions(const fraction_t *pf1, const fraction_t *pf2, fraction_t *sum) {
    make_fraction(pf1->num * pf2->den + pf2->num * pf1->den, pf1->den * pf2->den, sum);
}

/* Initialize the fraction pointed to by product with the product of 
   the fractions pointed to by pf1 and pf2.
   The fraction created by this function is always in reduced form
   (see documentation for reduce).
*/
void multiply_fractions(const fraction_t *pf1, const fraction_t *pf2,
                        fraction_t *product) {
    make_fraction(pf1->num * pf2->num, pf1->den * pf2->den, product);
}
