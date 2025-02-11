# Debug

## implicit declaration of function `EVP_MD_CTX_cleanup`

If you encounter this error :

```
./src/includes/hashes/hashes_libssl_under_1.1.0.c: In function ‘md5’:
./src/includes/hashes/hashes_libssl_under_1.1.0.c:15:16: error: storage size of ‘mdctx’ isn’t known
     EVP_MD_CTX mdctx;
                ^~~~~
./src/includes/hashes/hashes_libssl_under_1.1.0.c:20:5: warning: implicit declaration of function ‘EVP_MD_CTX_cleanup’; did you mean ‘EVP_MD_CTX_create’? [-Wimplicit-function-declaration]
     EVP_MD_CTX_cleanup(&mdctx);
     ^~~~~~~~~~~~~~~~~~
     EVP_MD_CTX_create
make: *** [Makefile:28: compile] Error 1
```

You might be using an older version of `openssl` (`< 1.1.0`). Maybe you have downloaded and installed the newer version, but your linker seems to find and use an older version of your `openssl` library.

 - `EVP_MD_CTX_new()` in `1.1.0` has replaced `EVP_MD_CTX_create()` in `1.0.x.`

 - `EVP_MD_CTX_free()` in `1.1.0` has replaced `EVP_MD_CTX_destroy()` in `1.0.x.`

You might try to use the older versions of these functions or make sure, that your linker really uses the `>= 1.1.0` version of the `openssl` library.

 - https://stackoverflow.com/questions/46768071/openssl-linking-undefined-reference-evp-md-ctx-new-and-fre
