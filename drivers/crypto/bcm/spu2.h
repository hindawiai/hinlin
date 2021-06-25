<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2016 Broadcom
 */

/*
 * This file contains SPU message definitions specअगरic to SPU2.
 */

#अगर_अघोषित _SPU2_H
#घोषणा _SPU2_H

क्रमागत spu2_cipher_type अणु
	SPU2_CIPHER_TYPE_NONE = 0x0,
	SPU2_CIPHER_TYPE_AES128 = 0x1,
	SPU2_CIPHER_TYPE_AES192 = 0x2,
	SPU2_CIPHER_TYPE_AES256 = 0x3,
	SPU2_CIPHER_TYPE_DES = 0x4,
	SPU2_CIPHER_TYPE_3DES = 0x5,
	SPU2_CIPHER_TYPE_LAST
पूर्ण;

क्रमागत spu2_cipher_mode अणु
	SPU2_CIPHER_MODE_ECB = 0x0,
	SPU2_CIPHER_MODE_CBC = 0x1,
	SPU2_CIPHER_MODE_CTR = 0x2,
	SPU2_CIPHER_MODE_CFB = 0x3,
	SPU2_CIPHER_MODE_OFB = 0x4,
	SPU2_CIPHER_MODE_XTS = 0x5,
	SPU2_CIPHER_MODE_CCM = 0x6,
	SPU2_CIPHER_MODE_GCM = 0x7,
	SPU2_CIPHER_MODE_LAST
पूर्ण;

क्रमागत spu2_hash_type अणु
	SPU2_HASH_TYPE_NONE = 0x0,
	SPU2_HASH_TYPE_AES128 = 0x1,
	SPU2_HASH_TYPE_AES192 = 0x2,
	SPU2_HASH_TYPE_AES256 = 0x3,
	SPU2_HASH_TYPE_MD5 = 0x6,
	SPU2_HASH_TYPE_SHA1 = 0x7,
	SPU2_HASH_TYPE_SHA224 = 0x8,
	SPU2_HASH_TYPE_SHA256 = 0x9,
	SPU2_HASH_TYPE_SHA384 = 0xa,
	SPU2_HASH_TYPE_SHA512 = 0xb,
	SPU2_HASH_TYPE_SHA512_224 = 0xc,
	SPU2_HASH_TYPE_SHA512_256 = 0xd,
	SPU2_HASH_TYPE_SHA3_224 = 0xe,
	SPU2_HASH_TYPE_SHA3_256 = 0xf,
	SPU2_HASH_TYPE_SHA3_384 = 0x10,
	SPU2_HASH_TYPE_SHA3_512 = 0x11,
	SPU2_HASH_TYPE_LAST
पूर्ण;

क्रमागत spu2_hash_mode अणु
	SPU2_HASH_MODE_CMAC = 0x0,
	SPU2_HASH_MODE_CBC_MAC = 0x1,
	SPU2_HASH_MODE_XCBC_MAC = 0x2,
	SPU2_HASH_MODE_HMAC = 0x3,
	SPU2_HASH_MODE_RABIN = 0x4,
	SPU2_HASH_MODE_CCM = 0x5,
	SPU2_HASH_MODE_GCM = 0x6,
	SPU2_HASH_MODE_RESERVED = 0x7,
	SPU2_HASH_MODE_LAST
पूर्ण;

क्रमागत spu2_ret_md_opts अणु
	SPU2_RET_NO_MD = 0,	/* वापस no metadata */
	SPU2_RET_FMD_OMD = 1,	/* वापस both FMD and OMD */
	SPU2_RET_FMD_ONLY = 2,	/* वापस only FMD */
	SPU2_RET_FMD_OMD_IV = 3,	/* वापस FMD and OMD with just IVs */
पूर्ण;

/* Fixed Metadata क्रमmat */
काष्ठा SPU2_FMD अणु
	__le64 ctrl0;
	__le64 ctrl1;
	__le64 ctrl2;
	__le64 ctrl3;
पूर्ण;

#घोषणा FMD_SIZE  माप(काष्ठा SPU2_FMD)

/* Fixed part of request message header length in bytes. Just FMD. */
#घोषणा SPU2_REQ_FIXED_LEN FMD_SIZE
#घोषणा SPU2_HEADER_ALLOC_LEN (SPU_REQ_FIXED_LEN + \
				2 * MAX_KEY_SIZE + 2 * MAX_IV_SIZE)

/* FMD ctrl0 field masks */
#घोषणा SPU2_CIPH_ENCRYPT_EN            0x1 /* 0: decrypt, 1: encrypt */
#घोषणा SPU2_CIPH_TYPE                 0xF0 /* one of spu2_cipher_type */
#घोषणा SPU2_CIPH_TYPE_SHIFT              4
#घोषणा SPU2_CIPH_MODE                0xF00 /* one of spu2_cipher_mode */
#घोषणा SPU2_CIPH_MODE_SHIFT              8
#घोषणा SPU2_CFB_MASK                0x7000 /* cipher feedback mask */
#घोषणा SPU2_CFB_MASK_SHIFT              12
#घोषणा SPU2_PROTO_SEL             0xF00000 /* MACsec, IPsec, TLS... */
#घोषणा SPU2_PROTO_SEL_SHIFT             20
#घोषणा SPU2_HASH_FIRST           0x1000000 /* 1: hash input is input pkt
					     * data
					     */
#घोषणा SPU2_CHK_TAG              0x2000000 /* 1: check digest provided */
#घोषणा SPU2_HASH_TYPE          0x1F0000000 /* one of spu2_hash_type */
#घोषणा SPU2_HASH_TYPE_SHIFT             28
#घोषणा SPU2_HASH_MODE         0xF000000000 /* one of spu2_hash_mode */
#घोषणा SPU2_HASH_MODE_SHIFT             36
#घोषणा SPU2_CIPH_PAD_EN     0x100000000000 /* 1: Add pad to end of payload क्रम
					     *    enc
					     */
#घोषणा SPU2_CIPH_PAD      0xFF000000000000 /* cipher pad value */
#घोषणा SPU2_CIPH_PAD_SHIFT              48

/* FMD ctrl1 field masks */
#घोषणा SPU2_TAG_LOC                    0x1 /* 1: end of payload, 0: undef */
#घोषणा SPU2_HAS_FR_DATA                0x2 /* 1: msg has frame data */
#घोषणा SPU2_HAS_AAD1                   0x4 /* 1: msg has AAD1 field */
#घोषणा SPU2_HAS_NAAD                   0x8 /* 1: msg has NAAD field */
#घोषणा SPU2_HAS_AAD2                  0x10 /* 1: msg has AAD2 field */
#घोषणा SPU2_HAS_ESN                   0x20 /* 1: msg has ESN field */
#घोषणा SPU2_HASH_KEY_LEN            0xFF00 /* len of hash key in bytes.
					     * HMAC only.
					     */
#घोषणा SPU2_HASH_KEY_LEN_SHIFT           8
#घोषणा SPU2_CIPH_KEY_LEN         0xFF00000 /* len of cipher key in bytes */
#घोषणा SPU2_CIPH_KEY_LEN_SHIFT          20
#घोषणा SPU2_GENIV               0x10000000 /* 1: hw generates IV */
#घोषणा SPU2_HASH_IV             0x20000000 /* 1: IV incl in hash */
#घोषणा SPU2_RET_IV              0x40000000 /* 1: वापस IV in output msg
					     *    b4 payload
					     */
#घोषणा SPU2_RET_IV_LEN         0xF00000000 /* length in bytes of IV वापसed.
					     * 0 = 16 bytes
					     */
#घोषणा SPU2_RET_IV_LEN_SHIFT            32
#घोषणा SPU2_IV_OFFSET         0xF000000000 /* gen IV offset */
#घोषणा SPU2_IV_OFFSET_SHIFT             36
#घोषणा SPU2_IV_LEN          0x1F0000000000 /* length of input IV in bytes */
#घोषणा SPU2_IV_LEN_SHIFT                40
#घोषणा SPU2_HASH_TAG_LEN  0x7F000000000000 /* hash tag length in bytes */
#घोषणा SPU2_HASH_TAG_LEN_SHIFT          48
#घोषणा SPU2_RETURN_MD    0x300000000000000 /* वापस metadata */
#घोषणा SPU2_RETURN_MD_SHIFT             56
#घोषणा SPU2_RETURN_FD    0x400000000000000
#घोषणा SPU2_RETURN_AAD1  0x800000000000000
#घोषणा SPU2_RETURN_NAAD 0x1000000000000000
#घोषणा SPU2_RETURN_AAD2 0x2000000000000000
#घोषणा SPU2_RETURN_PAY  0x4000000000000000 /* वापस payload */

/* FMD ctrl2 field masks */
#घोषणा SPU2_AAD1_OFFSET              0xFFF /* byte offset of AAD1 field */
#घोषणा SPU2_AAD1_LEN               0xFF000 /* length of AAD1 in bytes */
#घोषणा SPU2_AAD1_LEN_SHIFT              12
#घोषणा SPU2_AAD2_OFFSET         0xFFF00000 /* byte offset of AAD2 field */
#घोषणा SPU2_AAD2_OFFSET_SHIFT           20
#घोषणा SPU2_PL_OFFSET   0xFFFFFFFF00000000 /* payload offset from AAD2 */
#घोषणा SPU2_PL_OFFSET_SHIFT             32

/* FMD ctrl3 field masks */
#घोषणा SPU2_PL_LEN              0xFFFFFFFF /* payload length in bytes */
#घोषणा SPU2_TLS_LEN         0xFFFF00000000 /* TLS encrypt: cipher len
					     * TLS decrypt: compressed len
					     */
#घोषणा SPU2_TLS_LEN_SHIFT               32

/*
 * Max value that can be represented in the Payload Length field of the
 * ctrl3 word of FMD.
 */
#घोषणा SPU2_MAX_PAYLOAD  SPU2_PL_LEN

/* Error values वापसed in STATUS field of response messages */
#घोषणा SPU2_INVALID_ICV  1

व्योम spu2_dump_msg_hdr(u8 *buf, अचिन्हित पूर्णांक buf_len);
u32 spu2_ctx_max_payload(क्रमागत spu_cipher_alg cipher_alg,
			 क्रमागत spu_cipher_mode cipher_mode,
			 अचिन्हित पूर्णांक blocksize);
u32 spu2_payload_length(u8 *spu_hdr);
u16 spu2_response_hdr_len(u16 auth_key_len, u16 enc_key_len, bool is_hash);
u16 spu2_hash_pad_len(क्रमागत hash_alg hash_alg, क्रमागत hash_mode hash_mode,
		      u32 chunksize, u16 hash_block_size);
u32 spu2_gcm_ccm_pad_len(क्रमागत spu_cipher_mode cipher_mode,
			 अचिन्हित पूर्णांक data_size);
u32 spu2_assoc_resp_len(क्रमागत spu_cipher_mode cipher_mode,
			अचिन्हित पूर्णांक assoc_len, अचिन्हित पूर्णांक iv_len,
			bool is_encrypt);
u8 spu2_aead_ivlen(क्रमागत spu_cipher_mode cipher_mode,
		   u16 iv_len);
क्रमागत hash_type spu2_hash_type(u32 src_sent);
u32 spu2_digest_size(u32 alg_digest_size, क्रमागत hash_alg alg,
		     क्रमागत hash_type htype);
u32 spu2_create_request(u8 *spu_hdr,
			काष्ठा spu_request_opts *req_opts,
			काष्ठा spu_cipher_parms *cipher_parms,
			काष्ठा spu_hash_parms *hash_parms,
			काष्ठा spu_aead_parms *aead_parms,
			अचिन्हित पूर्णांक data_size);
u16 spu2_cipher_req_init(u8 *spu_hdr, काष्ठा spu_cipher_parms *cipher_parms);
व्योम spu2_cipher_req_finish(u8 *spu_hdr,
			    u16 spu_req_hdr_len,
			    अचिन्हित पूर्णांक is_inbound,
			    काष्ठा spu_cipher_parms *cipher_parms,
			    अचिन्हित पूर्णांक data_size);
व्योम spu2_request_pad(u8 *pad_start, u32 gcm_padding, u32 hash_pad_len,
		      क्रमागत hash_alg auth_alg, क्रमागत hash_mode auth_mode,
		      अचिन्हित पूर्णांक total_sent, u32 status_padding);
u8 spu2_xts_tweak_in_payload(व्योम);
u8 spu2_tx_status_len(व्योम);
u8 spu2_rx_status_len(व्योम);
पूर्णांक spu2_status_process(u8 *statp);
व्योम spu2_ccm_update_iv(अचिन्हित पूर्णांक digestsize,
			काष्ठा spu_cipher_parms *cipher_parms,
			अचिन्हित पूर्णांक assoclen, अचिन्हित पूर्णांक chunksize,
			bool is_encrypt, bool is_esp);
u32 spu2_wordalign_padlen(u32 data_size);
#पूर्ण_अगर
