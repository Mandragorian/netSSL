char *BN_bn2hex(const BIGNUM *num);
char *BN_bn2dec(const BIGNUM *num);

/*The char buffers that hold the information is allocated using
 * a call to OPENSSL_malloc and it is the callers responsibility
 * to free them using OPENSSL_free
 */


/*This functions perform the opossite conversion */

int BN_hex2bn(BIGNUM **num, const char *str);
int BN_dec2bn(BIGNUM **num, const char *str);

