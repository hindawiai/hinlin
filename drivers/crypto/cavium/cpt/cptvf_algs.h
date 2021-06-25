<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016 Cavium, Inc.
 */

#अगर_अघोषित _CPTVF_ALGS_H_
#घोषणा _CPTVF_ALGS_H_

#समावेश "request_manager.h"

#घोषणा MAX_DEVICES 16
#घोषणा MAJOR_OP_FC 0x33
#घोषणा MAX_ENC_KEY_SIZE 32
#घोषणा MAX_HASH_KEY_SIZE 64
#घोषणा MAX_KEY_SIZE (MAX_ENC_KEY_SIZE + MAX_HASH_KEY_SIZE)
#घोषणा CONTROL_WORD_LEN 8
#घोषणा KEY2_OFFSET 48

#घोषणा DMA_MODE_FLAG(dma_mode) \
	(((dma_mode) == DMA_GATHER_SCATTER) ? (1 << 7) : 0)

क्रमागत req_type अणु
	AE_CORE_REQ,
	SE_CORE_REQ,
पूर्ण;

क्रमागत cipher_type अणु
	DES3_CBC = 0x1,
	DES3_ECB = 0x2,
	AES_CBC = 0x3,
	AES_ECB = 0x4,
	AES_CFB = 0x5,
	AES_CTR = 0x6,
	AES_GCM = 0x7,
	AES_XTS = 0x8
पूर्ण;

क्रमागत aes_type अणु
	AES_128_BIT = 0x1,
	AES_192_BIT = 0x2,
	AES_256_BIT = 0x3
पूर्ण;

जोड़ encr_ctrl अणु
	u64 flags;
	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 enc_cipher:4;
		u64 reserved1:1;
		u64 aes_key:2;
		u64 iv_source:1;
		u64 hash_type:4;
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
		u64 hash_type:4;
		u64 iv_source:1;
		u64 aes_key:2;
		u64 reserved1:1;
		u64 enc_cipher:4;
#पूर्ण_अगर
	पूर्ण e;
पूर्ण;

काष्ठा cvm_cipher अणु
	स्थिर अक्षर *name;
	u8 value;
पूर्ण;

काष्ठा enc_context अणु
	जोड़ encr_ctrl enc_ctrl;
	u8 encr_key[32];
	u8 encr_iv[16];
पूर्ण;

काष्ठा fchmac_context अणु
	u8 ipad[64];
	u8 opad[64]; /* or OPAD */
पूर्ण;

काष्ठा fc_context अणु
	काष्ठा enc_context enc;
	काष्ठा fchmac_context hmac;
पूर्ण;

काष्ठा cvm_enc_ctx अणु
	u32 key_len;
	u8 enc_key[MAX_KEY_SIZE];
	u8 cipher_type:4;
	u8 key_type:2;
पूर्ण;

काष्ठा cvm_des3_ctx अणु
	u32 key_len;
	u8 des3_key[MAX_KEY_SIZE];
पूर्ण;

काष्ठा cvm_req_ctx अणु
	काष्ठा cpt_request_info cpt_req;
	u64 control_word;
	काष्ठा fc_context fctx;
पूर्ण;

पूर्णांक cptvf_करो_request(व्योम *cptvf, काष्ठा cpt_request_info *req);
#पूर्ण_अगर /*_CPTVF_ALGS_H_*/
