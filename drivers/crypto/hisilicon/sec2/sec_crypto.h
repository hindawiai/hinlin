<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019 HiSilicon Limited. */

#अगर_अघोषित __HISI_SEC_V2_CRYPTO_H
#घोषणा __HISI_SEC_V2_CRYPTO_H

#घोषणा SEC_IV_SIZE		24
#घोषणा SEC_MAX_KEY_SIZE	64
#घोषणा SEC_COMM_SCENE		0

क्रमागत sec_calg अणु
	SEC_CALG_3DES = 0x1,
	SEC_CALG_AES  = 0x2,
	SEC_CALG_SM4  = 0x3,
पूर्ण;

क्रमागत sec_hash_alg अणु
	SEC_A_HMAC_SHA1   = 0x10,
	SEC_A_HMAC_SHA256 = 0x11,
	SEC_A_HMAC_SHA512 = 0x15,
पूर्ण;

क्रमागत sec_mac_len अणु
	SEC_HMAC_SHA1_MAC   = 20,
	SEC_HMAC_SHA256_MAC = 32,
	SEC_HMAC_SHA512_MAC = 64,
पूर्ण;

क्रमागत sec_cmode अणु
	SEC_CMODE_ECB    = 0x0,
	SEC_CMODE_CBC    = 0x1,
	SEC_CMODE_CTR    = 0x4,
	SEC_CMODE_XTS    = 0x7,
पूर्ण;

क्रमागत sec_ckey_type अणु
	SEC_CKEY_128BIT = 0x0,
	SEC_CKEY_192BIT = 0x1,
	SEC_CKEY_256BIT = 0x2,
	SEC_CKEY_3DES_3KEY = 0x1,
	SEC_CKEY_3DES_2KEY = 0x3,
पूर्ण;

क्रमागत sec_bd_type अणु
	SEC_BD_TYPE1 = 0x1,
	SEC_BD_TYPE2 = 0x2,
पूर्ण;

क्रमागत sec_auth अणु
	SEC_NO_AUTH = 0x0,
	SEC_AUTH_TYPE1 = 0x1,
	SEC_AUTH_TYPE2 = 0x2,
पूर्ण;

क्रमागत sec_cipher_dir अणु
	SEC_CIPHER_ENC = 0x1,
	SEC_CIPHER_DEC = 0x2,
पूर्ण;

क्रमागत sec_addr_type अणु
	SEC_PBUF = 0x0,
	SEC_SGL  = 0x1,
	SEC_PRP  = 0x2,
पूर्ण;

काष्ठा sec_sqe_type2 अणु
	/*
	 * mac_len: 0~4 bits
	 * a_key_len: 5~10 bits
	 * a_alg: 11~16 bits
	 */
	__le32 mac_key_alg;

	/*
	 * c_icv_len: 0~5 bits
	 * c_width: 6~8 bits
	 * c_key_len: 9~11 bits
	 * c_mode: 12~15 bits
	 */
	__le16 icvw_kmode;

	/* c_alg: 0~3 bits */
	__u8 c_alg;
	__u8 rsvd4;

	/*
	 * a_len: 0~23 bits
	 * iv_offset_l: 24~31 bits
	 */
	__le32 alen_ivllen;

	/*
	 * c_len: 0~23 bits
	 * iv_offset_h: 24~31 bits
	 */
	__le32 clen_ivhlen;

	__le16 auth_src_offset;
	__le16 cipher_src_offset;
	__le16 cs_ip_header_offset;
	__le16 cs_udp_header_offset;
	__le16 pass_word_len;
	__le16 dk_len;
	__u8 salt3;
	__u8 salt2;
	__u8 salt1;
	__u8 salt0;

	__le16 tag;
	__le16 rsvd5;

	/*
	 * c_pad_type: 0~3 bits
	 * c_pad_len: 4~11 bits
	 * c_pad_data_type: 12~15 bits
	 */
	__le16 cph_pad;

	/* c_pad_len_field: 0~1 bits */
	__le16 c_pad_len_field;

	__le64 दीर्घ_a_data_len;
	__le64 a_ivin_addr;
	__le64 a_key_addr;
	__le64 mac_addr;
	__le64 c_ivin_addr;
	__le64 c_key_addr;

	__le64 data_src_addr;
	__le64 data_dst_addr;

	/*
	 * करोne: 0 bit
	 * icv: 1~3 bits
	 * csc: 4~6 bits
	 * flag: 7-10 bits
	 * dअगर_check: 11~13 bits
	 */
	__le16 करोne_flag;

	__u8 error_type;
	__u8 warning_type;
	__u8 mac_i3;
	__u8 mac_i2;
	__u8 mac_i1;
	__u8 mac_i0;
	__le16 check_sum_i;
	__u8 tls_pad_len_i;
	__u8 rsvd12;
	__le32 counter;
पूर्ण;

काष्ठा sec_sqe अणु
	/*
	 * type:	0~3 bits
	 * cipher:	4~5 bits
	 * auth:	6~7 bit s
	 */
	__u8 type_cipher_auth;

	/*
	 * seq:	0 bit
	 * de:	1~2 bits
	 * scene:	3~6 bits
	 * src_addr_type: ~7 bit, with sdm_addr_type 0-1 bits
	 */
	__u8 sds_sa_type;

	/*
	 * src_addr_type: 0~1 bits, not used now,
	 * अगर support PRP, set this field, or set zero.
	 * dst_addr_type: 2~4 bits
	 * mac_addr_type: 5~7 bits
	 */
	__u8 sdm_addr_type;
	__u8 rsvd0;

	/*
	 * nonce_len(type2): 0~3 bits
	 * huk(type2): 4 bit
	 * key_s(type2): 5 bit
	 * ci_gen: 6~7 bits
	 */
	__u8 huk_key_ci;

	/*
	 * ai_gen: 0~1 bits
	 * a_pad(type2): 2~3 bits
	 * c_s(type2): 4~5 bits
	 */
	__u8 ai_apd_cs;

	/*
	 * rhf(type2): 0 bit
	 * c_key_type: 1~2 bits
	 * a_key_type: 3~4 bits
	 * ग_लिखो_frame_len(type2): 5~7 bits
	 */
	__u8 rca_key_frm;

	/*
	 * cal_iv_addr_en(type2): 0 bit
	 * tls_up(type2): 1 bit
	 * inveld: 7 bit
	 */
	__u8 iv_tls_ld;

	/* Just using type2 BD now */
	काष्ठा sec_sqe_type2 type2;
पूर्ण;

पूर्णांक sec_रेजिस्टर_to_crypto(काष्ठा hisi_qm *qm);
व्योम sec_unरेजिस्टर_from_crypto(काष्ठा hisi_qm *qm);
#पूर्ण_अगर
