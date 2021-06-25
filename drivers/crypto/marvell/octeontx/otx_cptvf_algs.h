<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 * Marvell OcteonTX CPT driver
 *
 * Copyright (C) 2019 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#अगर_अघोषित __OTX_CPT_ALGS_H
#घोषणा __OTX_CPT_ALGS_H

#समावेश <crypto/hash.h>
#समावेश "otx_cpt_common.h"

#घोषणा OTX_CPT_MAX_ENC_KEY_SIZE    32
#घोषणा OTX_CPT_MAX_HASH_KEY_SIZE   64
#घोषणा OTX_CPT_MAX_KEY_SIZE (OTX_CPT_MAX_ENC_KEY_SIZE + \
			      OTX_CPT_MAX_HASH_KEY_SIZE)
क्रमागत otx_cpt_request_type अणु
	OTX_CPT_ENC_DEC_REQ            = 0x1,
	OTX_CPT_AEAD_ENC_DEC_REQ       = 0x2,
	OTX_CPT_AEAD_ENC_DEC_शून्य_REQ  = 0x3,
	OTX_CPT_PASSTHROUGH_REQ	       = 0x4
पूर्ण;

क्रमागत otx_cpt_major_opcodes अणु
	OTX_CPT_MAJOR_OP_MISC = 0x01,
	OTX_CPT_MAJOR_OP_FC   = 0x33,
	OTX_CPT_MAJOR_OP_HMAC = 0x35,
पूर्ण;

क्रमागत otx_cpt_req_type अणु
		OTX_CPT_AE_CORE_REQ,
		OTX_CPT_SE_CORE_REQ
पूर्ण;

क्रमागत otx_cpt_cipher_type अणु
	OTX_CPT_CIPHER_शून्य = 0x0,
	OTX_CPT_DES3_CBC = 0x1,
	OTX_CPT_DES3_ECB = 0x2,
	OTX_CPT_AES_CBC  = 0x3,
	OTX_CPT_AES_ECB  = 0x4,
	OTX_CPT_AES_CFB  = 0x5,
	OTX_CPT_AES_CTR  = 0x6,
	OTX_CPT_AES_GCM  = 0x7,
	OTX_CPT_AES_XTS  = 0x8
पूर्ण;

क्रमागत otx_cpt_mac_type अणु
	OTX_CPT_MAC_शून्य = 0x0,
	OTX_CPT_MD5      = 0x1,
	OTX_CPT_SHA1     = 0x2,
	OTX_CPT_SHA224   = 0x3,
	OTX_CPT_SHA256   = 0x4,
	OTX_CPT_SHA384   = 0x5,
	OTX_CPT_SHA512   = 0x6,
	OTX_CPT_GMAC     = 0x7
पूर्ण;

क्रमागत otx_cpt_aes_key_len अणु
	OTX_CPT_AES_128_BIT = 0x1,
	OTX_CPT_AES_192_BIT = 0x2,
	OTX_CPT_AES_256_BIT = 0x3
पूर्ण;

जोड़ otx_cpt_encr_ctrl अणु
	__be64 flags;
	u64 cflags;
	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 enc_cipher:4;
		u64 reserved1:1;
		u64 aes_key:2;
		u64 iv_source:1;
		u64 mac_type:4;
		u64 reserved2:3;
		u64 auth_input_type:1;
		u64 mac_len:8;
		u64 reserved3:8;
		u64 encr_offset:16;
		u64 iv_offset:8;
		u64 auth_offset:8;
#अन्यथा
		u64 auth_offset:8;
		u64 iv_offset:8;
		u64 encr_offset:16;
		u64 reserved3:8;
		u64 mac_len:8;
		u64 auth_input_type:1;
		u64 reserved2:3;
		u64 mac_type:4;
		u64 iv_source:1;
		u64 aes_key:2;
		u64 reserved1:1;
		u64 enc_cipher:4;
#पूर्ण_अगर
	पूर्ण e;
पूर्ण;

काष्ठा otx_cpt_cipher अणु
	स्थिर अक्षर *name;
	u8 value;
पूर्ण;

काष्ठा otx_cpt_enc_context अणु
	जोड़ otx_cpt_encr_ctrl enc_ctrl;
	u8 encr_key[32];
	u8 encr_iv[16];
पूर्ण;

जोड़ otx_cpt_fchmac_ctx अणु
	काष्ठा अणु
		u8 ipad[64];
		u8 opad[64];
	पूर्ण e;
	काष्ठा अणु
		u8 hmac_calc[64]; /* HMAC calculated */
		u8 hmac_recv[64]; /* HMAC received */
	पूर्ण s;
पूर्ण;

काष्ठा otx_cpt_fc_ctx अणु
	काष्ठा otx_cpt_enc_context enc;
	जोड़ otx_cpt_fchmac_ctx hmac;
पूर्ण;

काष्ठा otx_cpt_enc_ctx अणु
	u32 key_len;
	u8 enc_key[OTX_CPT_MAX_KEY_SIZE];
	u8 cipher_type;
	u8 key_type;
पूर्ण;

काष्ठा otx_cpt_des3_ctx अणु
	u32 key_len;
	u8 des3_key[OTX_CPT_MAX_KEY_SIZE];
पूर्ण;

जोड़ otx_cpt_offset_ctrl_word अणु
	__be64 flags;
	u64 cflags;
	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved:32;
		u64 enc_data_offset:16;
		u64 iv_offset:8;
		u64 auth_offset:8;
#अन्यथा
		u64 auth_offset:8;
		u64 iv_offset:8;
		u64 enc_data_offset:16;
		u64 reserved:32;
#पूर्ण_अगर
	पूर्ण e;
पूर्ण;

काष्ठा otx_cpt_req_ctx अणु
	काष्ठा otx_cpt_req_info cpt_req;
	जोड़ otx_cpt_offset_ctrl_word ctrl_word;
	काष्ठा otx_cpt_fc_ctx fctx;
पूर्ण;

काष्ठा otx_cpt_sdesc अणु
	काष्ठा shash_desc shash;
पूर्ण;

काष्ठा otx_cpt_aead_ctx अणु
	u8 key[OTX_CPT_MAX_KEY_SIZE];
	काष्ठा crypto_shash *hashalg;
	काष्ठा otx_cpt_sdesc *sdesc;
	u8 *ipad;
	u8 *opad;
	u32 enc_key_len;
	u32 auth_key_len;
	u8 cipher_type;
	u8 mac_type;
	u8 key_type;
	u8 is_trunc_hmac;
पूर्ण;
पूर्णांक otx_cpt_crypto_init(काष्ठा pci_dev *pdev, काष्ठा module *mod,
			क्रमागत otx_cptpf_type pf_type,
			क्रमागत otx_cptvf_type engine_type,
			पूर्णांक num_queues, पूर्णांक num_devices);
व्योम otx_cpt_crypto_निकास(काष्ठा pci_dev *pdev, काष्ठा module *mod,
			 क्रमागत otx_cptvf_type engine_type);
व्योम otx_cpt_callback(पूर्णांक status, व्योम *arg, व्योम *req);

#पूर्ण_अगर /* __OTX_CPT_ALGS_H */
