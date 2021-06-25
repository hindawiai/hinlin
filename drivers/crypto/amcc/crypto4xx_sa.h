<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * AMCC SoC PPC4xx Crypto Driver
 *
 * Copyright (c) 2008 Applied Micro Circuits Corporation.
 * All rights reserved. James Hsiao <jhsiao@amcc.com>
 *
 * This file defines the security context
 * associate क्रमmat.
 */

#अगर_अघोषित __CRYPTO4XX_SA_H__
#घोषणा __CRYPTO4XX_SA_H__

#घोषणा AES_IV_SIZE				16

/*
 * Contents of Dynamic Security Association (SA) with all possible fields
 */
जोड़ dynamic_sa_contents अणु
	काष्ठा अणु
		u32 arc4_state_ptr:1;
		u32 arc4_ij_ptr:1;
		u32 state_ptr:1;
		u32 iv3:1;
		u32 iv2:1;
		u32 iv1:1;
		u32 iv0:1;
		u32 seq_num_mask3:1;
		u32 seq_num_mask2:1;
		u32 seq_num_mask1:1;
		u32 seq_num_mask0:1;
		u32 seq_num1:1;
		u32 seq_num0:1;
		u32 spi:1;
		u32 outer_size:5;
		u32 inner_size:5;
		u32 key_size:4;
		u32 cmd_size:4;
	पूर्ण bf;
	u32 w;
पूर्ण __attribute__((packed));

#घोषणा सूची_OUTBOUND				0
#घोषणा सूची_INBOUND				1
#घोषणा SA_OP_GROUP_BASIC			0
#घोषणा SA_OPCODE_ENCRYPT			0
#घोषणा SA_OPCODE_DECRYPT			0
#घोषणा SA_OPCODE_ENCRYPT_HASH			1
#घोषणा SA_OPCODE_HASH_DECRYPT			1
#घोषणा SA_OPCODE_HASH				3
#घोषणा SA_CIPHER_ALG_DES			0
#घोषणा SA_CIPHER_ALG_3DES			1
#घोषणा SA_CIPHER_ALG_ARC4			2
#घोषणा SA_CIPHER_ALG_AES			3
#घोषणा SA_CIPHER_ALG_KASUMI			4
#घोषणा SA_CIPHER_ALG_शून्य			15

#घोषणा SA_HASH_ALG_MD5				0
#घोषणा SA_HASH_ALG_SHA1			1
#घोषणा SA_HASH_ALG_GHASH			12
#घोषणा SA_HASH_ALG_CBC_MAC			14
#घोषणा SA_HASH_ALG_शून्य			15
#घोषणा SA_HASH_ALG_SHA1_DIGEST_SIZE		20

#घोषणा SA_LOAD_HASH_FROM_SA			0
#घोषणा SA_LOAD_HASH_FROM_STATE			2
#घोषणा SA_NOT_LOAD_HASH			3
#घोषणा SA_LOAD_IV_FROM_SA			0
#घोषणा SA_LOAD_IV_FROM_INPUT			1
#घोषणा SA_LOAD_IV_FROM_STATE			2
#घोषणा SA_LOAD_IV_GEN_IV			3

#घोषणा SA_PAD_TYPE_CONSTANT			2
#घोषणा SA_PAD_TYPE_ZERO			3
#घोषणा SA_PAD_TYPE_TLS				5
#घोषणा SA_PAD_TYPE_DTLS			5
#घोषणा SA_NOT_SAVE_HASH			0
#घोषणा SA_SAVE_HASH				1
#घोषणा SA_NOT_SAVE_IV				0
#घोषणा SA_SAVE_IV				1
#घोषणा SA_HEADER_PROC				1
#घोषणा SA_NO_HEADER_PROC			0

जोड़ sa_command_0 अणु
	काष्ठा अणु
		u32 scatter:1;
		u32 gather:1;
		u32 save_hash_state:1;
		u32 save_iv:1;
		u32 load_hash_state:2;
		u32 load_iv:2;
		u32 digest_len:4;
		u32 hdr_proc:1;
		u32 extend_pad:1;
		u32 stream_cipher_pad:1;
		u32 rsv:1;
		u32 hash_alg:4;
		u32 cipher_alg:4;
		u32 pad_type:2;
		u32 op_group:2;
		u32 dir:1;
		u32 opcode:3;
	पूर्ण bf;
	u32 w;
पूर्ण __attribute__((packed));

#घोषणा CRYPTO_MODE_ECB				0
#घोषणा CRYPTO_MODE_CBC				1
#घोषणा CRYPTO_MODE_OFB				2
#घोषणा CRYPTO_MODE_CFB				3
#घोषणा CRYPTO_MODE_CTR				4

#घोषणा CRYPTO_FEEDBACK_MODE_NO_FB		0
#घोषणा CRYPTO_FEEDBACK_MODE_64BIT_OFB		0
#घोषणा CRYPTO_FEEDBACK_MODE_8BIT_CFB		1
#घोषणा CRYPTO_FEEDBACK_MODE_1BIT_CFB		2
#घोषणा CRYPTO_FEEDBACK_MODE_128BIT_CFB		3

#घोषणा SA_AES_KEY_LEN_128			2
#घोषणा SA_AES_KEY_LEN_192			3
#घोषणा SA_AES_KEY_LEN_256			4

#घोषणा SA_REV2					1
/*
 * The follow defines bits sa_command_1
 * In Basic hash mode  this bit define simple hash or hmac.
 * In IPsec mode, this bit define muting control.
 */
#घोषणा SA_HASH_MODE_HASH			0
#घोषणा SA_HASH_MODE_HMAC			1
#घोषणा SA_MC_ENABLE				0
#घोषणा SA_MC_DISABLE				1
#घोषणा SA_NOT_COPY_HDR				0
#घोषणा SA_COPY_HDR				1
#घोषणा SA_NOT_COPY_PAD				0
#घोषणा SA_COPY_PAD				1
#घोषणा SA_NOT_COPY_PAYLOAD			0
#घोषणा SA_COPY_PAYLOAD				1
#घोषणा SA_EXTENDED_SN_OFF			0
#घोषणा SA_EXTENDED_SN_ON			1
#घोषणा SA_SEQ_MASK_OFF				0
#घोषणा SA_SEQ_MASK_ON				1

जोड़ sa_command_1 अणु
	काष्ठा अणु
		u32 crypto_mode31:1;
		u32 save_arc4_state:1;
		u32 arc4_stateful:1;
		u32 key_len:5;
		u32 hash_crypto_offset:8;
		u32 sa_rev:2;
		u32 byte_offset:1;
		u32 hmac_muting:1;
		u32 feedback_mode:2;
		u32 crypto_mode9_8:2;
		u32 extended_seq_num:1;
		u32 seq_num_mask:1;
		u32 mutable_bit_proc:1;
		u32 ip_version:1;
		u32 copy_pad:1;
		u32 copy_payload:1;
		u32 copy_hdr:1;
		u32 rsv1:1;
	पूर्ण bf;
	u32 w;
पूर्ण __attribute__((packed));

काष्ठा dynamic_sa_ctl अणु
	जोड़ dynamic_sa_contents sa_contents;
	जोड़ sa_command_0 sa_command_0;
	जोड़ sa_command_1 sa_command_1;
पूर्ण __attribute__((packed));

/*
 * State Record क्रम Security Association (SA)
 */
काष्ठा  sa_state_record अणु
	__le32 save_iv[4];
	__le32 save_hash_byte_cnt[2];
	जोड़ अणु
		u32 save_digest[16]; /* क्रम MD5/SHA */
		__le32 save_digest_le32[16]; /* GHASH / CBC */
	पूर्ण;
पूर्ण __attribute__((packed));

/*
 * Security Association (SA) क्रम AES128
 *
 */
काष्ठा dynamic_sa_aes128 अणु
	काष्ठा dynamic_sa_ctl	ctrl;
	__le32 key[4];
	__le32 iv[4]; /* क्रम CBC, OFC, and CFB mode */
	u32 state_ptr;
	u32 reserved;
पूर्ण __attribute__((packed));

#घोषणा SA_AES128_LEN		(माप(काष्ठा dynamic_sa_aes128)/4)
#घोषणा SA_AES128_CONTENTS	0x3e000042

/*
 * Security Association (SA) क्रम AES192
 */
काष्ठा dynamic_sa_aes192 अणु
	काष्ठा dynamic_sa_ctl ctrl;
	__le32 key[6];
	__le32 iv[4]; /* क्रम CBC, OFC, and CFB mode */
	u32 state_ptr;
	u32 reserved;
पूर्ण __attribute__((packed));

#घोषणा SA_AES192_LEN		(माप(काष्ठा dynamic_sa_aes192)/4)
#घोषणा SA_AES192_CONTENTS	0x3e000062

/*
 * Security Association (SA) क्रम AES256
 */
काष्ठा dynamic_sa_aes256 अणु
	काष्ठा dynamic_sa_ctl ctrl;
	__le32 key[8];
	__le32 iv[4]; /* क्रम CBC, OFC, and CFB mode */
	u32 state_ptr;
	u32 reserved;
पूर्ण __attribute__((packed));

#घोषणा SA_AES256_LEN		(माप(काष्ठा dynamic_sa_aes256)/4)
#घोषणा SA_AES256_CONTENTS	0x3e000082
#घोषणा SA_AES_CONTENTS		0x3e000002

/*
 * Security Association (SA) क्रम AES128 CCM
 */
काष्ठा dynamic_sa_aes128_ccm अणु
	काष्ठा dynamic_sa_ctl ctrl;
	__le32 key[4];
	__le32 iv[4];
	u32 state_ptr;
	u32 reserved;
पूर्ण __packed;
#घोषणा SA_AES128_CCM_LEN	(माप(काष्ठा dynamic_sa_aes128_ccm)/4)
#घोषणा SA_AES128_CCM_CONTENTS	0x3e000042
#घोषणा SA_AES_CCM_CONTENTS	0x3e000002

/*
 * Security Association (SA) क्रम AES128_GCM
 */
काष्ठा dynamic_sa_aes128_gcm अणु
	काष्ठा dynamic_sa_ctl ctrl;
	__le32 key[4];
	__le32 inner_digest[4];
	__le32 iv[4];
	u32 state_ptr;
	u32 reserved;
पूर्ण __packed;

#घोषणा SA_AES128_GCM_LEN	(माप(काष्ठा dynamic_sa_aes128_gcm)/4)
#घोषणा SA_AES128_GCM_CONTENTS	0x3e000442
#घोषणा SA_AES_GCM_CONTENTS	0x3e000402

/*
 * Security Association (SA) क्रम HASH160: HMAC-SHA1
 */
काष्ठा dynamic_sa_hash160 अणु
	काष्ठा dynamic_sa_ctl ctrl;
	__le32 inner_digest[5];
	__le32 outer_digest[5];
	u32 state_ptr;
	u32 reserved;
पूर्ण __attribute__((packed));
#घोषणा SA_HASH160_LEN		(माप(काष्ठा dynamic_sa_hash160)/4)
#घोषणा SA_HASH160_CONTENTS     0x2000a502

अटल अंतरभूत u32
get_dynamic_sa_offset_state_ptr_field(काष्ठा dynamic_sa_ctl *cts)
अणु
	u32 offset;

	offset = cts->sa_contents.bf.key_size
		+ cts->sa_contents.bf.inner_size
		+ cts->sa_contents.bf.outer_size
		+ cts->sa_contents.bf.spi
		+ cts->sa_contents.bf.seq_num0
		+ cts->sa_contents.bf.seq_num1
		+ cts->sa_contents.bf.seq_num_mask0
		+ cts->sa_contents.bf.seq_num_mask1
		+ cts->sa_contents.bf.seq_num_mask2
		+ cts->sa_contents.bf.seq_num_mask3
		+ cts->sa_contents.bf.iv0
		+ cts->sa_contents.bf.iv1
		+ cts->sa_contents.bf.iv2
		+ cts->sa_contents.bf.iv3;

	वापस माप(काष्ठा dynamic_sa_ctl) + offset * 4;
पूर्ण

अटल अंतरभूत __le32 *get_dynamic_sa_key_field(काष्ठा dynamic_sa_ctl *cts)
अणु
	वापस (__le32 *) ((अचिन्हित दीर्घ)cts + माप(काष्ठा dynamic_sa_ctl));
पूर्ण

अटल अंतरभूत __le32 *get_dynamic_sa_inner_digest(काष्ठा dynamic_sa_ctl *cts)
अणु
	वापस (__le32 *) ((अचिन्हित दीर्घ)cts +
		माप(काष्ठा dynamic_sa_ctl) +
		cts->sa_contents.bf.key_size * 4);
पूर्ण

#पूर्ण_अगर
