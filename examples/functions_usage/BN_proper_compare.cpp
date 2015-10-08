/*In order to compare two BIGNUMs a and b we can't use the usual
 * operators < > ==. Instead we must use the BN_cmp(a,b) wich
 * returns -1 if a < b, 0 if a == b and 1 if a > b
 */

