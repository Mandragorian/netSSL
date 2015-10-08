BIGNUM a, b *c;

/* First, the wrong way to copy a BIGNUM */
a = b;
*c = b;

/* Now the right way to copy a BIGNUM */
BN_copy(&a,&b);    /* Copies b to a */

c = BN_dup(&b);    /* Creates c and initializes it to the same value
		      as b */

