<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2016 Broadcom
 */

/*
 * This file contains the definition of SPU messages. There are currently two
 * SPU message क्रमmats: SPU-M and SPU2. The hardware uses dअगरferent values to
 * identअगरy the same things in SPU-M vs SPU2. So this file defines values that
 * are hardware independent. Software can use these values क्रम any version of
 * SPU hardware. These values are used in APIs in spu.c. Functions पूर्णांकernal to
 * spu.c and spu2.c convert these to hardware-specअगरic values.
 */

#अगर_अघोषित _SPU_H
#घोषणा _SPU_H

#समावेश <linux/types.h>
#समावेश <linux/scatterlist.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>

क्रमागत spu_cipher_alg अणु
	CIPHER_ALG_NONE = 0x0,
	CIPHER_ALG_RC4 = 0x1,
	CIPHER_ALG_DES = 0x2,
	CIPHER_ALG_3DES = 0x3,
	CIPHER_ALG_AES = 0x4,
	CIPHER_ALG_LAST = 0x5
पूर्ण;

क्रमागत spu_cipher_mode अणु
	CIPHER_MODE_NONE = 0x0,
	CIPHER_MODE_ECB = 0x0,
	CIPHER_MODE_CBC = 0x1,
	CIPHER_MODE_OFB = 0x2,
	CIPHER_MODE_CFB = 0x3,
	CIPHER_MODE_CTR = 0x4,
	CIPHER_MODE_CCM = 0x5,
	CIPHER_MODE_GCM = 0x6,
	CIPHER_MODE_XTS = 0x7,
	CIPHER_MODE_LAST = 0x8
पूर्ण;

क्रमागत spu_cipher_type अणु
	CIPHER_TYPE_NONE = 0x0,
	CIPHER_TYPE_DES = 0x0,
	CIPHER_TYPE_3DES = 0x0,
	CIPHER_TYPE_INIT = 0x0,	/* used क्रम ARC4 */
	CIPHER_TYPE_AES128 = 0x0,
	CIPHER_TYPE_AES192 = 0x1,
	CIPHER_TYPE_UPDT = 0x1,	/* used क्रम ARC4 */
	CIPHER_TYPE_AES256 = 0x2,
पूर्ण;

क्रमागत hash_alg अणु
	HASH_ALG_NONE = 0x0,
	HASH_ALG_MD5 = 0x1,
	HASH_ALG_SHA1 = 0x2,
	HASH_ALG_SHA224 = 0x3,
	HASH_ALG_SHA256 = 0x4,
	HASH_ALG_AES = 0x5,
	HASH_ALG_SHA384 = 0x6,
	HASH_ALG_SHA512 = 0x7,
	/* Keep SHA3 algorithms at the end always */
	HASH_ALG_SHA3_224 = 0x8,
	HASH_ALG_SHA3_256 = 0x9,
	HASH_ALG_SHA3_384 = 0xa,
	HASH_ALG_SHA3_512 = 0xb,
	HASH_ALG_LAST
पूर्ण;

क्रमागत hash_mode अणु
	HASH_MODE_NONE = 0x0,
	HASH_MODE_HASH = 0x0,
	HASH_MODE_XCBC = 0x0,
	HASH_MODE_CMAC = 0x1,
	HASH_MODE_CTXT = 0x1,
	HASH_MODE_HMAC = 0x2,
	HASH_MODE_RABIN = 0x4,
	HASH_MODE_FHMAC = 0x6,
	HASH_MODE_CCM = 0x5,
	HASH_MODE_GCM = 0x6,
पूर्ण;

क्रमागत hash_type अणु
	HASH_TYPE_NONE = 0x0,
	HASH_TYPE_FULL = 0x0,
	HASH_TYPE_INIT = 0x1,
	HASH_TYPE_UPDT = 0x2,
	HASH_TYPE_FIN = 0x3,
	HASH_TYPE_AES128 = 0x0,
	HASH_TYPE_AES192 = 0x1,
	HASH_TYPE_AES256 = 0x2
पूर्ण;

क्रमागत aead_type अणु
	AES_CCM,
	AES_GCM,
	AUTHENC,
	AEAD_TYPE_LAST
पूर्ण;

बाह्य अक्षर *hash_alg_name[HASH_ALG_LAST];
बाह्य अक्षर *aead_alg_name[AEAD_TYPE_LAST];

काष्ठा spu_request_opts अणु
	bool is_inbound;
	bool auth_first;
	bool is_aead;
	bool is_esp;
	bool bd_suppress;
	bool is_rfc4543;
पूर्ण;

काष्ठा spu_cipher_parms अणु
	क्रमागत spu_cipher_alg  alg;
	क्रमागत spu_cipher_mode mode;
	क्रमागत spu_cipher_type type;
	u8                  *key_buf;
	u16                  key_len;
	/* iv_buf and iv_len include salt, अगर applicable */
	u8                  *iv_buf;
	u16                  iv_len;
पूर्ण;

काष्ठा spu_hash_parms अणु
	क्रमागत hash_alg  alg;
	क्रमागत hash_mode mode;
	क्रमागत hash_type type;
	u8             digestsize;
	u8            *key_buf;
	u16            key_len;
	u16            prebuf_len;
	/* length of hash pad. चिन्हित, needs to handle roll-overs */
	पूर्णांक            pad_len;
पूर्ण;

काष्ठा spu_aead_parms अणु
	u32 assoc_size;
	u16 iv_len;      /* length of IV field between assoc data and data */
	u8  aad_pad_len; /* For AES GCM/CCM, length of padding after AAD */
	u8  data_pad_len;/* For AES GCM/CCM, length of padding after data */
	bool वापस_iv;  /* True अगर SPU should वापस an IV */
	u32 ret_iv_len;  /* Length in bytes of वापसed IV */
	u32 ret_iv_off;  /* Offset पूर्णांकo full IV अगर partial IV वापसed */
पूर्ण;

/************** SPU sizes ***************/

#घोषणा SPU_RX_STATUS_LEN  4

/* Max length of padding क्रम 4-byte alignment of STATUS field */
#घोषणा SPU_STAT_PAD_MAX  4

/* Max length of pad fragment. 4 is क्रम 4-byte alignment of STATUS field */
#घोषणा SPU_PAD_LEN_MAX (SPU_GCM_CCM_ALIGN + MAX_HASH_BLOCK_SIZE + \
			 SPU_STAT_PAD_MAX)

/* GCM and CCM require 16-byte alignment */
#घोषणा SPU_GCM_CCM_ALIGN 16

/* Length up SUPDT field in SPU response message क्रम RC4 */
#घोषणा SPU_SUPDT_LEN 260

/* SPU status error codes. These used as common error codes across all
 * SPU variants.
 */
#घोषणा SPU_INVALID_ICV  1

/* Indicates no limit to the length of the payload in a SPU message */
#घोषणा SPU_MAX_PAYLOAD_INF  0xFFFFFFFF

/* Size of XTS tweak ("i" parameter), in bytes */
#घोषणा SPU_XTS_TWEAK_SIZE 16

/* CCM B_0 field definitions, common क्रम SPU-M and SPU2 */
#घोषणा CCM_B0_ADATA		0x40
#घोषणा CCM_B0_ADATA_SHIFT	   6
#घोषणा CCM_B0_M_PRIME		0x38
#घोषणा CCM_B0_M_PRIME_SHIFT	   3
#घोषणा CCM_B0_L_PRIME		0x07
#घोषणा CCM_B0_L_PRIME_SHIFT	   0
#घोषणा CCM_ESP_L_VALUE		   4

/**
 * spu_req_incl_icv() - Return true अगर SPU request message should include the
 * ICV as a separate buffer.
 * @cipher_mode:  the cipher mode being requested
 * @is_encrypt:   true अगर encrypting. false अगर decrypting.
 *
 * Return:  true अगर ICV to be included as separate buffer
 */
अटल __always_अंतरभूत  bool spu_req_incl_icv(क्रमागत spu_cipher_mode cipher_mode,
					      bool is_encrypt)
अणु
	अगर ((cipher_mode == CIPHER_MODE_GCM) && !is_encrypt)
		वापस true;
	अगर ((cipher_mode == CIPHER_MODE_CCM) && !is_encrypt)
		वापस true;

	वापस false;
पूर्ण

अटल __always_अंतरभूत u32 spu_real_db_size(u32 assoc_size,
					    u32 aead_iv_buf_len,
					    u32 prebuf_len,
					    u32 data_size,
					    u32 aad_pad_len,
					    u32 gcm_pad_len,
					    u32 hash_pad_len)
अणु
	वापस assoc_size + aead_iv_buf_len + prebuf_len + data_size +
	    aad_pad_len + gcm_pad_len + hash_pad_len;
पूर्ण

/************** SPU Functions Prototypes **************/

व्योम spum_dump_msg_hdr(u8 *buf, अचिन्हित पूर्णांक buf_len);

u32 spum_ns2_ctx_max_payload(क्रमागत spu_cipher_alg cipher_alg,
			     क्रमागत spu_cipher_mode cipher_mode,
			     अचिन्हित पूर्णांक blocksize);
u32 spum_nsp_ctx_max_payload(क्रमागत spu_cipher_alg cipher_alg,
			     क्रमागत spu_cipher_mode cipher_mode,
			     अचिन्हित पूर्णांक blocksize);
u32 spum_payload_length(u8 *spu_hdr);
u16 spum_response_hdr_len(u16 auth_key_len, u16 enc_key_len, bool is_hash);
u16 spum_hash_pad_len(क्रमागत hash_alg hash_alg, क्रमागत hash_mode hash_mode,
		      u32 chunksize, u16 hash_block_size);
u32 spum_gcm_ccm_pad_len(क्रमागत spu_cipher_mode cipher_mode,
			 अचिन्हित पूर्णांक data_size);
u32 spum_assoc_resp_len(क्रमागत spu_cipher_mode cipher_mode,
			अचिन्हित पूर्णांक assoc_len, अचिन्हित पूर्णांक iv_len,
			bool is_encrypt);
u8 spum_aead_ivlen(क्रमागत spu_cipher_mode cipher_mode, u16 iv_len);
bool spu_req_incl_icv(क्रमागत spu_cipher_mode cipher_mode, bool is_encrypt);
क्रमागत hash_type spum_hash_type(u32 src_sent);
u32 spum_digest_size(u32 alg_digest_size, क्रमागत hash_alg alg,
		     क्रमागत hash_type htype);

u32 spum_create_request(u8 *spu_hdr,
			काष्ठा spu_request_opts *req_opts,
			काष्ठा spu_cipher_parms *cipher_parms,
			काष्ठा spu_hash_parms *hash_parms,
			काष्ठा spu_aead_parms *aead_parms,
			अचिन्हित पूर्णांक data_size);

u16 spum_cipher_req_init(u8 *spu_hdr, काष्ठा spu_cipher_parms *cipher_parms);

व्योम spum_cipher_req_finish(u8 *spu_hdr,
			    u16 spu_req_hdr_len,
			    अचिन्हित पूर्णांक is_inbound,
			    काष्ठा spu_cipher_parms *cipher_parms,
			    अचिन्हित पूर्णांक data_size);

व्योम spum_request_pad(u8 *pad_start,
		      u32 gcm_padding,
		      u32 hash_pad_len,
		      क्रमागत hash_alg auth_alg,
		      क्रमागत hash_mode auth_mode,
		      अचिन्हित पूर्णांक total_sent, u32 status_padding);

u8 spum_xts_tweak_in_payload(व्योम);
u8 spum_tx_status_len(व्योम);
u8 spum_rx_status_len(व्योम);
पूर्णांक spum_status_process(u8 *statp);

व्योम spum_ccm_update_iv(अचिन्हित पूर्णांक digestsize,
			काष्ठा spu_cipher_parms *cipher_parms,
			अचिन्हित पूर्णांक assoclen,
			अचिन्हित पूर्णांक chunksize,
			bool is_encrypt,
			bool is_esp);
u32 spum_wordalign_padlen(u32 data_size);
#पूर्ण_अगर
