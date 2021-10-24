#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#include "hashes_libssl_above_1.1.0.h"

/*
*
*
*
*/

void md5(char * input_string, unsigned char * hash_value, unsigned int * hash_len){
    EVP_MD_CTX * md_ctx;
    md_ctx = EVP_MD_CTX_new();
    if (md_ctx != NULL) {
        // Calculate MD5
        EVP_DigestInit(md_ctx, EVP_md5());
        EVP_DigestUpdate(md_ctx, input_string, (size_t) strlen(input_string));
        EVP_DigestFinal_ex(md_ctx, hash_value, hash_len);
        EVP_MD_CTX_free(md_ctx);
    } else {
        // MD_CTX failed
    }
}
