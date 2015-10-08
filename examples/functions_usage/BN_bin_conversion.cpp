/* Converting from BIGNUM to binary */
len = BN_num_bytes(num);
buf = (unsigned char *)malloc(len);
len = BN_bn2bin(num, buf);

/* Converting from binary to BIGNUM */
BN_bin2bn(buf, len, num);
num = BN_bin2bn(buf, len, NULL);

