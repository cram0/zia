/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCE-5-1-zia-julien.augugliaro
** File description:
** sslutils
*/

#ifndef SSLUTILS_HPP_
#define SSLUTILS_HPP_

#include <openssl/ssl.h>
#include <openssl/err.h>

namespace ssl_utils
{
    void init_ssl()
    {
        SSL_library_init();
        SSL_load_error_strings();
        OpenSSL_add_all_algorithms();
    }

    void shutdown_ssl(SSL* ssl, SSL_CTX *ctx)
    {
        SSL_shutdown(ssl);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
    }

    SSL_CTX *create_context()
    {
        const SSL_METHOD *method;
        SSL_CTX *ctx;

        method = TLS_server_method();

        ctx = SSL_CTX_new(method);
        if (!ctx) {
            perror("Unable to create SSL context");
            ERR_print_errors_fp(stderr);
            exit(EXIT_FAILURE);
        }

        return ctx;
    }

    void configure_context(SSL_CTX *ctx)
    {
        if (SSL_CTX_use_certificate_file(ctx, "../../modules/ssl/localhost.crt", SSL_FILETYPE_PEM) <= 0) {
            ERR_print_errors_fp(stderr);
            exit(EXIT_FAILURE);
        }

        if (SSL_CTX_use_PrivateKey_file(ctx, "../../modules/ssl/localhost.key", SSL_FILETYPE_PEM) <= 0 ) {
            ERR_print_errors_fp(stderr);
            exit(EXIT_FAILURE);
        }
    }

    void SSL_print_error(const SSL *s, int ret_code) {
        std::cout << "Ret code : " << ret_code << std::endl;
        switch (SSL_get_error(s, ret_code))
        {
            case SSL_ERROR_NONE:
                std::cout << "SSL_ERROR_NONE" << std::endl;
                break;
            case SSL_ERROR_ZERO_RETURN:
                std::cout << "SSL_ERROR_ZERO_RETURN" << std::endl;
                break;
            case SSL_ERROR_WANT_READ:
                std::cout << "SSL_ERROR_WANT_READ" << std::endl;
                break;
            case SSL_ERROR_WANT_WRITE:
                std::cout << "SSL_ERROR_WANT_WRITE" << std::endl;
                break;
            case SSL_ERROR_WANT_X509_LOOKUP :
                std::cout << "SSL_ERROR_WANT_X509_LOOKUP" << std::endl;
                break;
            case SSL_ERROR_SYSCALL :
                std::cout << "SSL_ERROR_SYSCALL" << std::endl;
                break;
            case SSL_ERROR_WANT_CONNECT :
                std::cout << "SSL_ERROR_WANT_CONNECT" << std::endl;
                break;
            case SSL_ERROR_WANT_ACCEPT :
                std::cout << "SSL_ERROR_WANT_ACCEPT" << std::endl;
                break;
            case SSL_ERROR_WANT_ASYNC :
                std::cout << "SSL_ERROR_WANT_ASYNC" << std::endl;
                break;
            case SSL_ERROR_WANT_ASYNC_JOB :
                std::cout << "SSL_ERROR_WANT_ASYNC_JOB" << std::endl;
                break;
            case SSL_ERROR_WANT_CLIENT_HELLO_CB :
                std::cout << "SSL_ERROR_WANT_CLIENT_HELLO_CB" << std::endl;
                break;
            default:
                std::cout << "SSL default read error" << std::endl;
                return;
        }
    }
}


#endif /* !SSLUTILS_HPP_ */
