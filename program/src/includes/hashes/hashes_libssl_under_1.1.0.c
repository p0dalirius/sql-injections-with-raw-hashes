#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#include "hashes_libssl_under_1.1.0.h"

/*
*
*
*
*/

void md5(char * input_string, unsigned char * hash_value, unsigned int * hash_len){
    EVP_MD_CTX mdctx;
    EVP_DigestInit(&mdctx, EVP_md5());
    EVP_DigestUpdate(&mdctx, input_string, (size_t) strlen(input_string));
    EVP_DigestFinal_ex(&mdctx, hash_value, hash_len);
    EVP_MD_CTX_cleanup(&mdctx);
    free(&mdctx);
}
