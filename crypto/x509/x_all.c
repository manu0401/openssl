/* crypto/x509/x_all.c */
/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 * 
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 * 
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from 
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 * 
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * 
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */

#include <stdio.h>
#undef SSLEAY_MACROS
#include <openssl/stack.h>
#include "cryptlib.h"
#include <openssl/buffer.h>
#include <openssl/asn1.h>
#include <openssl/evp.h>
#include <openssl/x509.h>

int X509_verify(X509 *a, EVP_PKEY *r)
	{
	return(ASN1_item_verify(&X509_CINF_it,a->sig_alg,
		a->signature,a->cert_info,r));
	}

int X509_REQ_verify(X509_REQ *a, EVP_PKEY *r)
	{
	return( ASN1_item_verify(&X509_REQ_INFO_it,
		a->sig_alg,a->signature,a->req_info,r));
	}

int X509_CRL_verify(X509_CRL *a, EVP_PKEY *r)
	{
	return(ASN1_item_verify(&X509_CRL_INFO_it,
		a->sig_alg, a->signature,a->crl,r));
	}

int NETSCAPE_SPKI_verify(NETSCAPE_SPKI *a, EVP_PKEY *r)
	{
	return(ASN1_item_verify(&NETSCAPE_SPKAC_it,
		a->sig_algor,a->signature,a->spkac,r));
	}

int X509_sign(X509 *x, EVP_PKEY *pkey, const EVP_MD *md)
	{
	return(ASN1_item_sign(&X509_CINF_it, x->cert_info->signature,
		x->sig_alg, x->signature, x->cert_info,pkey,md));
	}

int X509_REQ_sign(X509_REQ *x, EVP_PKEY *pkey, const EVP_MD *md)
	{
	return(ASN1_item_sign(&X509_REQ_INFO_it,x->sig_alg, NULL,
		x->signature, x->req_info,pkey,md));
	}

int X509_CRL_sign(X509_CRL *x, EVP_PKEY *pkey, const EVP_MD *md)
	{
	return(ASN1_item_sign(&X509_CRL_INFO_it,x->crl->sig_alg,
		x->sig_alg, x->signature, x->crl,pkey,md));
	}

int NETSCAPE_SPKI_sign(NETSCAPE_SPKI *x, EVP_PKEY *pkey, const EVP_MD *md)
	{
	return(ASN1_item_sign(&NETSCAPE_SPKAC_it, x->sig_algor,NULL,
		x->signature, x->spkac,pkey,md));
	}

X509_ATTRIBUTE *X509_ATTRIBUTE_dup(X509_ATTRIBUTE *xa)
	{
	return ASN1_item_dup(&X509_ATTRIBUTE_it,xa);
	}

X509 *X509_dup(X509 *x509)
	{
	return ASN1_item_dup(&X509_it,x509);
	}

X509_EXTENSION *X509_EXTENSION_dup(X509_EXTENSION *ex)
	{
	return ASN1_item_dup(&X509_EXTENSION_it,ex);
	}

#ifndef OPENSSL_NO_FP_API
X509 *d2i_X509_fp(FILE *fp, X509 **x509)
	{
	return ASN1_item_d2i_fp(&X509_it, fp, x509);
	}

int i2d_X509_fp(FILE *fp, X509 *x509)
	{
	return ASN1_item_i2d_fp(&X509_it, fp, x509);
	}
#endif

X509 *d2i_X509_bio(BIO *bp, X509 **x509)
	{
	return ASN1_item_d2i_bio(&X509_it, bp, x509);
	}

int i2d_X509_bio(BIO *bp, X509 *x509)
	{
	return ASN1_item_i2d_bio(&X509_it, bp, x509);
	}

X509_CRL *X509_CRL_dup(X509_CRL *crl)
	{
	return ASN1_item_dup(&X509_CRL_it, crl);
	}

#ifndef OPENSSL_NO_FP_API
X509_CRL *d2i_X509_CRL_fp(FILE *fp, X509_CRL **crl)
	{
	return ASN1_item_d2i_fp(&X509_CRL_it, fp, crl);
	}

int i2d_X509_CRL_fp(FILE *fp, X509_CRL *crl)
	{
	return ASN1_item_i2d_fp(&X509_CRL_it, fp, crl);
	}
#endif

X509_CRL *d2i_X509_CRL_bio(BIO *bp, X509_CRL **crl)
	{
	return ASN1_item_d2i_bio(&X509_CRL_it, bp, crl);
	}

int i2d_X509_CRL_bio(BIO *bp, X509_CRL *crl)
	{
	return ASN1_item_i2d_bio(&X509_CRL_it, bp, crl);
	}

PKCS7 *PKCS7_dup(PKCS7 *p7)
	{
	return ASN1_item_dup(&PKCS7_it, p7);
	}

#ifndef OPENSSL_NO_FP_API
PKCS7 *d2i_PKCS7_fp(FILE *fp, PKCS7 **p7)
	{
	return ASN1_item_d2i_fp(&PKCS7_it, fp, p7);
	}

int i2d_PKCS7_fp(FILE *fp, PKCS7 *p7)
	{
	return ASN1_item_i2d_fp(&PKCS7_it, fp, p7);
	}
#endif

PKCS7 *d2i_PKCS7_bio(BIO *bp, PKCS7 **p7)
	{
	return ASN1_item_d2i_bio(&PKCS7_it, bp, p7);
	}

int i2d_PKCS7_bio(BIO *bp, PKCS7 *p7)
	{
	return ASN1_item_i2d_bio(&PKCS7_it, bp, p7);
	}

X509_REQ *X509_REQ_dup(X509_REQ *req)
	{
	return ASN1_item_dup(&X509_REQ_it, req);
	}

#ifndef OPENSSL_NO_FP_API
X509_REQ *d2i_X509_REQ_fp(FILE *fp, X509_REQ **req)
	{
	return ASN1_item_d2i_fp(&X509_REQ_it, fp, req);
	}

int i2d_X509_REQ_fp(FILE *fp, X509_REQ *req)
	{
	return ASN1_item_i2d_fp(&X509_REQ_it, fp, req);
	}
#endif

X509_REQ *d2i_X509_REQ_bio(BIO *bp, X509_REQ **req)
	{
	return ASN1_item_d2i_bio(&X509_REQ_it, bp, req);
	}

int i2d_X509_REQ_bio(BIO *bp, X509_REQ *req)
	{
	return ASN1_item_i2d_bio(&X509_REQ_it, bp, req);
	}

#ifndef OPENSSL_NO_RSA
RSA *RSAPublicKey_dup(RSA *rsa)
	{
	return ASN1_item_dup(&RSAPublicKey_it, rsa);
	}

RSA *RSAPrivateKey_dup(RSA *rsa)
	{
	return ASN1_item_dup(&RSAPrivateKey_it, rsa);
	}

#ifndef OPENSSL_NO_FP_API
RSA *d2i_RSAPrivateKey_fp(FILE *fp, RSA **rsa)
	{
	return ASN1_item_d2i_fp(&RSAPrivateKey_it, fp, rsa);
	}

int i2d_RSAPrivateKey_fp(FILE *fp, RSA *rsa)
	{
	return ASN1_item_i2d_fp(&RSAPrivateKey_it, fp, rsa);
	}

RSA *d2i_RSAPublicKey_fp(FILE *fp, RSA **rsa)
	{
	return ASN1_item_d2i_fp(&RSAPublicKey_it, fp, rsa);
	}


RSA *d2i_RSA_PUBKEY_fp(FILE *fp, RSA **rsa)
	{
	return((RSA *)ASN1_d2i_fp((char *(*)())
		RSA_new,(char *(*)())d2i_RSA_PUBKEY, (fp),
		(unsigned char **)(rsa)));
	}

int i2d_RSAPublicKey_fp(FILE *fp, RSA *rsa)
	{
	return ASN1_item_i2d_fp(&RSAPublicKey_it, fp, rsa);
	}

int i2d_RSA_PUBKEY_fp(FILE *fp, RSA *rsa)
	{
	return(ASN1_i2d_fp(i2d_RSA_PUBKEY,fp,(unsigned char *)rsa));
	}
#endif

RSA *d2i_RSAPrivateKey_bio(BIO *bp, RSA **rsa)
	{
	return ASN1_item_d2i_bio(&RSAPrivateKey_it, bp, rsa);
	}

int i2d_RSAPrivateKey_bio(BIO *bp, RSA *rsa)
	{
	return ASN1_item_i2d_bio(&RSAPrivateKey_it, bp, rsa);
	}

RSA *d2i_RSAPublicKey_bio(BIO *bp, RSA **rsa)
	{
	return ASN1_item_d2i_bio(&RSAPublicKey_it, bp, rsa);
	}


RSA *d2i_RSA_PUBKEY_bio(BIO *bp, RSA **rsa)
	{
	return((RSA *)ASN1_d2i_bio((char *(*)())
		RSA_new,(char *(*)())d2i_RSA_PUBKEY, (bp),
		(unsigned char **)(rsa)));
	}

int i2d_RSAPublicKey_bio(BIO *bp, RSA *rsa)
	{
	return ASN1_item_i2d_bio(&RSAPublicKey_it, bp, rsa);
	}

int i2d_RSA_PUBKEY_bio(BIO *bp, RSA *rsa)
	{
	return(ASN1_i2d_bio(i2d_RSA_PUBKEY,bp,(unsigned char *)rsa));
	}
#endif

#ifndef OPENSSL_NO_DSA
#ifndef OPENSSL_NO_FP_API
DSA *d2i_DSAPrivateKey_fp(FILE *fp, DSA **dsa)
	{
	return((DSA *)ASN1_d2i_fp((char *(*)())
		DSA_new,(char *(*)())d2i_DSAPrivateKey, (fp),
		(unsigned char **)(dsa)));
	}

int i2d_DSAPrivateKey_fp(FILE *fp, DSA *dsa)
	{
	return(ASN1_i2d_fp(i2d_DSAPrivateKey,fp,(unsigned char *)dsa));
	}

DSA *d2i_DSA_PUBKEY_fp(FILE *fp, DSA **dsa)
	{
	return((DSA *)ASN1_d2i_fp((char *(*)())
		DSA_new,(char *(*)())d2i_DSA_PUBKEY, (fp),
		(unsigned char **)(dsa)));
	}

int i2d_DSA_PUBKEY_fp(FILE *fp, DSA *dsa)
	{
	return(ASN1_i2d_fp(i2d_DSA_PUBKEY,fp,(unsigned char *)dsa));
	}
#endif

DSA *d2i_DSAPrivateKey_bio(BIO *bp, DSA **dsa)
	{
	return((DSA *)ASN1_d2i_bio((char *(*)())
		DSA_new,(char *(*)())d2i_DSAPrivateKey, (bp),
		(unsigned char **)(dsa)));
	}

int i2d_DSAPrivateKey_bio(BIO *bp, DSA *dsa)
	{
	return(ASN1_i2d_bio(i2d_DSAPrivateKey,bp,(unsigned char *)dsa));
	}

DSA *d2i_DSA_PUBKEY_bio(BIO *bp, DSA **dsa)
	{
	return((DSA *)ASN1_d2i_bio((char *(*)())
		DSA_new,(char *(*)())d2i_DSA_PUBKEY, (bp),
		(unsigned char **)(dsa)));
	}

int i2d_DSA_PUBKEY_bio(BIO *bp, DSA *dsa)
	{
	return(ASN1_i2d_bio(i2d_DSA_PUBKEY,bp,(unsigned char *)dsa));
	}

#endif

X509_ALGOR *X509_ALGOR_dup(X509_ALGOR *xn)
	{
	return ASN1_item_dup(&X509_ALGOR_it, xn);
	}

X509_NAME *X509_NAME_dup(X509_NAME *xn)
	{
	return ASN1_item_dup(&X509_NAME_it, xn);
	}

X509_NAME_ENTRY *X509_NAME_ENTRY_dup(X509_NAME_ENTRY *ne)
	{
	return ASN1_item_dup(&X509_NAME_ENTRY_it, ne);
	}

int X509_pubkey_digest(const X509 *data, const EVP_MD *type, unsigned char *md,
	     unsigned int *len)
	{
	ASN1_BIT_STRING *key;
	key = X509_get0_pubkey_bitstr(data);
	if(!key) return 0;
	return EVP_Digest(key->data, key->length, md, len, type);
	}

int X509_digest(const X509 *data, const EVP_MD *type, unsigned char *md,
	     unsigned int *len)
	{
	return(ASN1_item_digest(&X509_it,type,(char *)data,md,len));
	}

int X509_CRL_digest(const X509_CRL *data, const EVP_MD *type, unsigned char *md,
	     unsigned int *len)
	{
	return(ASN1_item_digest(&X509_CRL_it,type,(char *)data,md,len));
	}

int X509_REQ_digest(const X509_REQ *data, const EVP_MD *type, unsigned char *md,
	     unsigned int *len)
	{
	return(ASN1_item_digest(&X509_REQ_it,type,(char *)data,md,len));
	}

int X509_NAME_digest(const X509_NAME *data, const EVP_MD *type, unsigned char *md,
	     unsigned int *len)
	{
	return(ASN1_item_digest(&X509_NAME_it,type,(char *)data,md,len));
	}

int PKCS7_ISSUER_AND_SERIAL_digest(PKCS7_ISSUER_AND_SERIAL *data, const EVP_MD *type,
	     unsigned char *md, unsigned int *len)
	{
	return(ASN1_item_digest(&PKCS7_ISSUER_AND_SERIAL_it,type,
		(char *)data,md,len));
	}


#ifndef OPENSSL_NO_FP_API
X509_SIG *d2i_PKCS8_fp(FILE *fp, X509_SIG **p8)
	{
	return((X509_SIG *)ASN1_d2i_fp((char *(*)())X509_SIG_new,
		(char *(*)())d2i_X509_SIG, (fp),(unsigned char **)(p8)));
	}

int i2d_PKCS8_fp(FILE *fp, X509_SIG *p8)
	{
	return(ASN1_i2d_fp(i2d_X509_SIG,fp,(unsigned char *)p8));
	}
#endif

X509_SIG *d2i_PKCS8_bio(BIO *bp, X509_SIG **p8)
	{
	return((X509_SIG *)ASN1_d2i_bio((char *(*)())X509_SIG_new,
		(char *(*)())d2i_X509_SIG, (bp),(unsigned char **)(p8)));
	}

int i2d_PKCS8_bio(BIO *bp, X509_SIG *p8)
	{
	return(ASN1_i2d_bio(i2d_X509_SIG,bp,(unsigned char *)p8));
	}

#ifndef OPENSSL_NO_FP_API
PKCS8_PRIV_KEY_INFO *d2i_PKCS8_PRIV_KEY_INFO_fp(FILE *fp,
						 PKCS8_PRIV_KEY_INFO **p8inf)
	{
	return((PKCS8_PRIV_KEY_INFO *)ASN1_d2i_fp(
		(char *(*)())PKCS8_PRIV_KEY_INFO_new,
		(char *(*)())d2i_PKCS8_PRIV_KEY_INFO, (fp),
				(unsigned char **)(p8inf)));
	}

int i2d_PKCS8_PRIV_KEY_INFO_fp(FILE *fp, PKCS8_PRIV_KEY_INFO *p8inf)
	{
	return(ASN1_i2d_fp(i2d_PKCS8_PRIV_KEY_INFO,fp,(unsigned char *)p8inf));
	}

int i2d_PKCS8PrivateKeyInfo_fp(FILE *fp, EVP_PKEY *key)
	{
	PKCS8_PRIV_KEY_INFO *p8inf;
	int ret;
	p8inf = EVP_PKEY2PKCS8(key);
	if(!p8inf) return 0;
	ret = i2d_PKCS8_PRIV_KEY_INFO_fp(fp, p8inf);
	PKCS8_PRIV_KEY_INFO_free(p8inf);
	return ret;
	}

int i2d_PrivateKey_fp(FILE *fp, EVP_PKEY *pkey)
	{
	return(ASN1_i2d_fp(i2d_PrivateKey,fp,(unsigned char *)pkey));
	}

EVP_PKEY *d2i_PrivateKey_fp(FILE *fp, EVP_PKEY **a)
{
	return((EVP_PKEY *)ASN1_d2i_fp((char *(*)())EVP_PKEY_new,
		(char *(*)())d2i_AutoPrivateKey, (fp),(unsigned char **)(a)));
}

int i2d_PUBKEY_fp(FILE *fp, EVP_PKEY *pkey)
	{
	return(ASN1_i2d_fp(i2d_PUBKEY,fp,(unsigned char *)pkey));
	}

EVP_PKEY *d2i_PUBKEY_fp(FILE *fp, EVP_PKEY **a)
{
	return((EVP_PKEY *)ASN1_d2i_fp((char *(*)())EVP_PKEY_new,
		(char *(*)())d2i_PUBKEY, (fp),(unsigned char **)(a)));
}

#endif

PKCS8_PRIV_KEY_INFO *d2i_PKCS8_PRIV_KEY_INFO_bio(BIO *bp,
						 PKCS8_PRIV_KEY_INFO **p8inf)
	{
	return((PKCS8_PRIV_KEY_INFO *)ASN1_d2i_bio(
		(char *(*)())PKCS8_PRIV_KEY_INFO_new,
		(char *(*)())d2i_PKCS8_PRIV_KEY_INFO, (bp),
				(unsigned char **)(p8inf)));
	}

int i2d_PKCS8_PRIV_KEY_INFO_bio(BIO *bp, PKCS8_PRIV_KEY_INFO *p8inf)
	{
	return(ASN1_i2d_bio(i2d_PKCS8_PRIV_KEY_INFO,bp,(unsigned char *)p8inf));
	}

int i2d_PKCS8PrivateKeyInfo_bio(BIO *bp, EVP_PKEY *key)
	{
	PKCS8_PRIV_KEY_INFO *p8inf;
	int ret;
	p8inf = EVP_PKEY2PKCS8(key);
	if(!p8inf) return 0;
	ret = i2d_PKCS8_PRIV_KEY_INFO_bio(bp, p8inf);
	PKCS8_PRIV_KEY_INFO_free(p8inf);
	return ret;
	}

int i2d_PrivateKey_bio(BIO *bp, EVP_PKEY *pkey)
	{
	return(ASN1_i2d_bio(i2d_PrivateKey,bp,(unsigned char *)pkey));
	}

EVP_PKEY *d2i_PrivateKey_bio(BIO *bp, EVP_PKEY **a)
	{
	return((EVP_PKEY *)ASN1_d2i_bio((char *(*)())EVP_PKEY_new,
		(char *(*)())d2i_AutoPrivateKey, (bp),(unsigned char **)(a)));
	}

int i2d_PUBKEY_bio(BIO *bp, EVP_PKEY *pkey)
	{
	return(ASN1_i2d_bio(i2d_PUBKEY,bp,(unsigned char *)pkey));
	}

EVP_PKEY *d2i_PUBKEY_bio(BIO *bp, EVP_PKEY **a)
	{
	return((EVP_PKEY *)ASN1_d2i_bio((char *(*)())EVP_PKEY_new,
		(char *(*)())d2i_PUBKEY, (bp),(unsigned char **)(a)));
	}
