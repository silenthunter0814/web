
SSL_libray_init();
OpenSSL_add_all_algorithms();
SSL_load_error_string();

SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
if (!ctx) {
    fprintf(stderr, "SSL_CTX_new() failed.\n");
    return 1;
}
