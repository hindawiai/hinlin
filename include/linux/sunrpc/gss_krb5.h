<शैली गुरु>
/*
 *  linux/include/linux/sunrpc/gss_krb5_types.h
 *
 *  Adapted from MIT Kerberos 5-1.2.1 lib/include/krb5.h,
 *  lib/gssapi/krb5/gssapiP_krb5.h, and others
 *
 *  Copyright (c) 2000-2008 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  Andy Adamson   <andros@umich.edu>
 *  Bruce Fields   <bfields@umich.edu>
 */

/*
 * Copyright 1995 by the Massachusetts Institute of Technology.
 * All Rights Reserved.
 *
 * Export of this software from the United States of America may
 *   require a specअगरic license from the United States Government.
 *   It is the responsibility of any person or organization contemplating
 *   export to obtain such a license beक्रमe exporting.
 *
 * WITHIN THAT CONSTRAINT, permission to use, copy, modअगरy, and
 * distribute this software and its करोcumentation क्रम any purpose and
 * without fee is hereby granted, provided that the above copyright
 * notice appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting करोcumentation, and that
 * the name of M.I.T. not be used in advertising or खुलाity pertaining
 * to distribution of the software without specअगरic, written prior
 * permission.  Furthermore अगर you modअगरy this software you must label
 * your software as modअगरied software and not distribute it in such a
 * fashion that it might be confused with the original M.I.T. software.
 * M.I.T. makes no representations about the suitability of
 * this software क्रम any purpose.  It is provided "as is" without express
 * or implied warranty.
 *
 */

#समावेश <crypto/skcipher.h>
#समावेश <linux/sunrpc/auth_gss.h>
#समावेश <linux/sunrpc/gss_err.h>
#समावेश <linux/sunrpc/gss_asn1.h>

/* Length of स्थिरant used in key derivation */
#घोषणा GSS_KRB5_K5CLENGTH (5)

/* Maximum key length (in bytes) क्रम the supported crypto algorithms*/
#घोषणा GSS_KRB5_MAX_KEYLEN (32)

/* Maximum checksum function output क्रम the supported crypto algorithms */
#घोषणा GSS_KRB5_MAX_CKSUM_LEN  (20)

/* Maximum blocksize क्रम the supported crypto algorithms */
#घोषणा GSS_KRB5_MAX_BLOCKSIZE  (16)

काष्ठा krb5_ctx;

काष्ठा gss_krb5_enctype अणु
	स्थिर u32		etype;		/* encryption (key) type */
	स्थिर u32		ctype;		/* checksum type */
	स्थिर अक्षर		*name;		/* "friendly" name */
	स्थिर अक्षर		*encrypt_name;	/* crypto encrypt name */
	स्थिर अक्षर		*cksum_name;	/* crypto checksum name */
	स्थिर u16		संकेतg;	/* signing algorithm */
	स्थिर u16		sealalg;	/* sealing algorithm */
	स्थिर u32		blocksize;	/* encryption blocksize */
	स्थिर u32		conflen;	/* confounder length
						   (normally the same as
						   the blocksize) */
	स्थिर u32		cksumlength;	/* checksum length */
	स्थिर u32		keyed_cksum;	/* is it a keyed cksum? */
	स्थिर u32		keybytes;	/* raw key len, in bytes */
	स्थिर u32		keylength;	/* final key len, in bytes */
	u32 (*encrypt) (काष्ठा crypto_sync_skcipher *tfm,
			व्योम *iv, व्योम *in, व्योम *out,
			पूर्णांक length);		/* encryption function */
	u32 (*decrypt) (काष्ठा crypto_sync_skcipher *tfm,
			व्योम *iv, व्योम *in, व्योम *out,
			पूर्णांक length);		/* decryption function */
	u32 (*mk_key) (स्थिर काष्ठा gss_krb5_enctype *gk5e,
		       काष्ठा xdr_netobj *in,
		       काष्ठा xdr_netobj *out);	/* complete key generation */
	u32 (*encrypt_v2) (काष्ठा krb5_ctx *kctx, u32 offset,
			   काष्ठा xdr_buf *buf,
			   काष्ठा page **pages); /* v2 encryption function */
	u32 (*decrypt_v2) (काष्ठा krb5_ctx *kctx, u32 offset, u32 len,
			   काष्ठा xdr_buf *buf, u32 *headskip,
			   u32 *tailskip);	/* v2 decryption function */
पूर्ण;

/* krb5_ctx flags definitions */
#घोषणा KRB5_CTX_FLAG_INITIATOR         0x00000001
#घोषणा KRB5_CTX_FLAG_CFX               0x00000002
#घोषणा KRB5_CTX_FLAG_ACCEPTOR_SUBKEY   0x00000004

काष्ठा krb5_ctx अणु
	पूर्णांक			initiate; /* 1 = initiating, 0 = accepting */
	u32			enctype;
	u32			flags;
	स्थिर काष्ठा gss_krb5_enctype *gk5e; /* enctype-specअगरic info */
	काष्ठा crypto_sync_skcipher *enc;
	काष्ठा crypto_sync_skcipher *seq;
	काष्ठा crypto_sync_skcipher *acceptor_enc;
	काष्ठा crypto_sync_skcipher *initiator_enc;
	काष्ठा crypto_sync_skcipher *acceptor_enc_aux;
	काष्ठा crypto_sync_skcipher *initiator_enc_aux;
	u8			Ksess[GSS_KRB5_MAX_KEYLEN]; /* session key */
	u8			cksum[GSS_KRB5_MAX_KEYLEN];
	atomic_t		seq_send;
	atomic64_t		seq_send64;
	समय64_t		endसमय;
	काष्ठा xdr_netobj	mech_used;
	u8			initiator_sign[GSS_KRB5_MAX_KEYLEN];
	u8			acceptor_sign[GSS_KRB5_MAX_KEYLEN];
	u8			initiator_seal[GSS_KRB5_MAX_KEYLEN];
	u8			acceptor_seal[GSS_KRB5_MAX_KEYLEN];
	u8			initiator_पूर्णांकeg[GSS_KRB5_MAX_KEYLEN];
	u8			acceptor_पूर्णांकeg[GSS_KRB5_MAX_KEYLEN];
पूर्ण;

/* The length of the Kerberos GSS token header */
#घोषणा GSS_KRB5_TOK_HDR_LEN	(16)

#घोषणा KG_TOK_MIC_MSG    0x0101
#घोषणा KG_TOK_WRAP_MSG   0x0201

#घोषणा KG2_TOK_INITIAL     0x0101
#घोषणा KG2_TOK_RESPONSE    0x0202
#घोषणा KG2_TOK_MIC         0x0404
#घोषणा KG2_TOK_WRAP        0x0504

#घोषणा KG2_TOKEN_FLAG_SENTBYACCEPTOR   0x01
#घोषणा KG2_TOKEN_FLAG_SEALED           0x02
#घोषणा KG2_TOKEN_FLAG_ACCEPTORSUBKEY   0x04

#घोषणा KG2_RESP_FLAG_ERROR             0x0001
#घोषणा KG2_RESP_FLAG_DELEG_OK          0x0002

क्रमागत sgn_alg अणु
	SGN_ALG_DES_MAC_MD5 = 0x0000,
	SGN_ALG_MD2_5 = 0x0001,
	SGN_ALG_DES_MAC = 0x0002,
	SGN_ALG_3 = 0x0003,		/* not published */
	SGN_ALG_HMAC_SHA1_DES3_KD = 0x0004
पूर्ण;
क्रमागत seal_alg अणु
	SEAL_ALG_NONE = 0xffff,
	SEAL_ALG_DES = 0x0000,
	SEAL_ALG_1 = 0x0001,		/* not published */
	SEAL_ALG_DES3KD = 0x0002
पूर्ण;

#घोषणा CKSUMTYPE_CRC32			0x0001
#घोषणा CKSUMTYPE_RSA_MD4		0x0002
#घोषणा CKSUMTYPE_RSA_MD4_DES		0x0003
#घोषणा CKSUMTYPE_DESCBC		0x0004
#घोषणा CKSUMTYPE_RSA_MD5		0x0007
#घोषणा CKSUMTYPE_RSA_MD5_DES		0x0008
#घोषणा CKSUMTYPE_NIST_SHA		0x0009
#घोषणा CKSUMTYPE_HMAC_SHA1_DES3	0x000c
#घोषणा CKSUMTYPE_HMAC_SHA1_96_AES128   0x000f
#घोषणा CKSUMTYPE_HMAC_SHA1_96_AES256   0x0010
#घोषणा CKSUMTYPE_HMAC_MD5_ARCFOUR      -138 /* Microsoft md5 hmac cksumtype */

/* from gssapi_err_krb5.h */
#घोषणा KG_CCACHE_NOMATCH                        (39756032L)
#घोषणा KG_KEYTAB_NOMATCH                        (39756033L)
#घोषणा KG_TGT_MISSING                           (39756034L)
#घोषणा KG_NO_SUBKEY                             (39756035L)
#घोषणा KG_CONTEXT_ESTABLISHED                   (39756036L)
#घोषणा KG_BAD_SIGN_TYPE                         (39756037L)
#घोषणा KG_BAD_LENGTH                            (39756038L)
#घोषणा KG_CTX_INCOMPLETE                        (39756039L)
#घोषणा KG_CONTEXT                               (39756040L)
#घोषणा KG_CRED                                  (39756041L)
#घोषणा KG_ENC_DESC                              (39756042L)
#घोषणा KG_BAD_SEQ                               (39756043L)
#घोषणा KG_EMPTY_CCACHE                          (39756044L)
#घोषणा KG_NO_CTYPES                             (39756045L)

/* per Kerberos v5 protocol spec crypto types from the wire. 
 * these get mapped to linux kernel crypto routines.  
 */
#घोषणा ENCTYPE_शून्य            0x0000
#घोषणा ENCTYPE_DES_CBC_CRC     0x0001	/* DES cbc mode with CRC-32 */
#घोषणा ENCTYPE_DES_CBC_MD4     0x0002	/* DES cbc mode with RSA-MD4 */
#घोषणा ENCTYPE_DES_CBC_MD5     0x0003	/* DES cbc mode with RSA-MD5 */
#घोषणा ENCTYPE_DES_CBC_RAW     0x0004	/* DES cbc mode raw */
/* XXX deprecated? */
#घोषणा ENCTYPE_DES3_CBC_SHA    0x0005	/* DES-3 cbc mode with NIST-SHA */
#घोषणा ENCTYPE_DES3_CBC_RAW    0x0006	/* DES-3 cbc mode raw */
#घोषणा ENCTYPE_DES_HMAC_SHA1   0x0008
#घोषणा ENCTYPE_DES3_CBC_SHA1   0x0010
#घोषणा ENCTYPE_AES128_CTS_HMAC_SHA1_96 0x0011
#घोषणा ENCTYPE_AES256_CTS_HMAC_SHA1_96 0x0012
#घोषणा ENCTYPE_ARCFOUR_HMAC            0x0017
#घोषणा ENCTYPE_ARCFOUR_HMAC_EXP        0x0018
#घोषणा ENCTYPE_UNKNOWN         0x01ff

/*
 * Constants used क्रम key derivation
 */
/* क्रम 3DES */
#घोषणा KG_USAGE_SEAL (22)
#घोषणा KG_USAGE_SIGN (23)
#घोषणा KG_USAGE_SEQ  (24)

/* from rfc3961 */
#घोषणा KEY_USAGE_SEED_CHECKSUM         (0x99)
#घोषणा KEY_USAGE_SEED_ENCRYPTION       (0xAA)
#घोषणा KEY_USAGE_SEED_INTEGRITY        (0x55)

/* from rfc4121 */
#घोषणा KG_USAGE_ACCEPTOR_SEAL  (22)
#घोषणा KG_USAGE_ACCEPTOR_SIGN  (23)
#घोषणा KG_USAGE_INITIATOR_SEAL (24)
#घोषणा KG_USAGE_INITIATOR_SIGN (25)

/*
 * This compile-समय check verअगरies that we will not exceed the
 * slack space allotted by the client and server auth_gss code
 * beक्रमe they call gss_wrap().
 */
#घोषणा GSS_KRB5_MAX_SLACK_NEEDED \
	(GSS_KRB5_TOK_HDR_LEN     /* gss token header */         \
	+ GSS_KRB5_MAX_CKSUM_LEN  /* gss token checksum */       \
	+ GSS_KRB5_MAX_BLOCKSIZE  /* confounder */               \
	+ GSS_KRB5_MAX_BLOCKSIZE  /* possible padding */         \
	+ GSS_KRB5_TOK_HDR_LEN    /* encrypted hdr in v2 token */\
	+ GSS_KRB5_MAX_CKSUM_LEN  /* encryption hmac */          \
	+ 4 + 4                   /* RPC verअगरier */             \
	+ GSS_KRB5_TOK_HDR_LEN                                   \
	+ GSS_KRB5_MAX_CKSUM_LEN)

u32
make_checksum(काष्ठा krb5_ctx *kctx, अक्षर *header, पूर्णांक hdrlen,
		काष्ठा xdr_buf *body, पूर्णांक body_offset, u8 *cksumkey,
		अचिन्हित पूर्णांक usage, काष्ठा xdr_netobj *cksumout);

u32
make_checksum_v2(काष्ठा krb5_ctx *, अक्षर *header, पूर्णांक hdrlen,
		 काष्ठा xdr_buf *body, पूर्णांक body_offset, u8 *key,
		 अचिन्हित पूर्णांक usage, काष्ठा xdr_netobj *cksum);

u32 gss_get_mic_kerberos(काष्ठा gss_ctx *, काष्ठा xdr_buf *,
		काष्ठा xdr_netobj *);

u32 gss_verअगरy_mic_kerberos(काष्ठा gss_ctx *, काष्ठा xdr_buf *,
		काष्ठा xdr_netobj *);

u32
gss_wrap_kerberos(काष्ठा gss_ctx *ctx_id, पूर्णांक offset,
		काष्ठा xdr_buf *outbuf, काष्ठा page **pages);

u32
gss_unwrap_kerberos(काष्ठा gss_ctx *ctx_id, पूर्णांक offset, पूर्णांक len,
		काष्ठा xdr_buf *buf);


u32
krb5_encrypt(काष्ठा crypto_sync_skcipher *key,
	     व्योम *iv, व्योम *in, व्योम *out, पूर्णांक length);

u32
krb5_decrypt(काष्ठा crypto_sync_skcipher *key,
	     व्योम *iv, व्योम *in, व्योम *out, पूर्णांक length); 

पूर्णांक
gss_encrypt_xdr_buf(काष्ठा crypto_sync_skcipher *tfm, काष्ठा xdr_buf *outbuf,
		    पूर्णांक offset, काष्ठा page **pages);

पूर्णांक
gss_decrypt_xdr_buf(काष्ठा crypto_sync_skcipher *tfm, काष्ठा xdr_buf *inbuf,
		    पूर्णांक offset);

s32
krb5_make_seq_num(काष्ठा krb5_ctx *kctx,
		काष्ठा crypto_sync_skcipher *key,
		पूर्णांक direction,
		u32 seqnum, अचिन्हित अक्षर *cksum, अचिन्हित अक्षर *buf);

s32
krb5_get_seq_num(काष्ठा krb5_ctx *kctx,
	       अचिन्हित अक्षर *cksum,
	       अचिन्हित अक्षर *buf, पूर्णांक *direction, u32 *seqnum);

पूर्णांक
xdr_extend_head(काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक shअगरtlen);

u32
krb5_derive_key(स्थिर काष्ठा gss_krb5_enctype *gk5e,
		स्थिर काष्ठा xdr_netobj *inkey,
		काष्ठा xdr_netobj *outkey,
		स्थिर काष्ठा xdr_netobj *in_स्थिरant,
		gfp_t gfp_mask);

u32
gss_krb5_des3_make_key(स्थिर काष्ठा gss_krb5_enctype *gk5e,
		       काष्ठा xdr_netobj *अक्रमombits,
		       काष्ठा xdr_netobj *key);

u32
gss_krb5_aes_make_key(स्थिर काष्ठा gss_krb5_enctype *gk5e,
		      काष्ठा xdr_netobj *अक्रमombits,
		      काष्ठा xdr_netobj *key);

u32
gss_krb5_aes_encrypt(काष्ठा krb5_ctx *kctx, u32 offset,
		     काष्ठा xdr_buf *buf,
		     काष्ठा page **pages);

u32
gss_krb5_aes_decrypt(काष्ठा krb5_ctx *kctx, u32 offset, u32 len,
		     काष्ठा xdr_buf *buf, u32 *plainoffset,
		     u32 *plainlen);

व्योम
gss_krb5_make_confounder(अक्षर *p, u32 conflen);
