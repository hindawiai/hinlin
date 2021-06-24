<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __NX_CSBCPB_H__
#घोषणा __NX_CSBCPB_H__

काष्ठा cop_symcpb_aes_ecb अणु
	u8 key[32];
	u8 __rsvd[80];
पूर्ण __packed;

काष्ठा cop_symcpb_aes_cbc अणु
	u8 iv[16];
	u8 key[32];
	u8 cv[16];
	u32 spbc;
	u8 __rsvd[44];
पूर्ण __packed;

काष्ठा cop_symcpb_aes_gca अणु
	u8 in_pat[16];
	u8 key[32];
	u8 out_pat[16];
	u32 spbc;
	u8 __rsvd[44];
पूर्ण __packed;

काष्ठा cop_symcpb_aes_gcm अणु
	u8 in_pat_or_aad[16];
	u8 iv_or_cnt[16];
	u64 bit_length_aad;
	u64 bit_length_data;
	u8 in_s0[16];
	u8 key[32];
	u8 __rsvd1[16];
	u8 out_pat_or_mac[16];
	u8 out_s0[16];
	u8 out_cnt[16];
	u32 spbc;
	u8 __rsvd2[12];
पूर्ण __packed;

काष्ठा cop_symcpb_aes_ctr अणु
	u8 iv[16];
	u8 key[32];
	u8 cv[16];
	u32 spbc;
	u8 __rsvd2[44];
पूर्ण __packed;

काष्ठा cop_symcpb_aes_cca अणु
	u8 b0[16];
	u8 b1[16];
	u8 key[16];
	u8 out_pat_or_b0[16];
	u32 spbc;
	u8 __rsvd[44];
पूर्ण __packed;

काष्ठा cop_symcpb_aes_ccm अणु
	u8 in_pat_or_b0[16];
	u8 iv_or_ctr[16];
	u8 in_s0[16];
	u8 key[16];
	u8 __rsvd1[48];
	u8 out_pat_or_mac[16];
	u8 out_s0[16];
	u8 out_ctr[16];
	u32 spbc;
	u8 __rsvd2[12];
पूर्ण __packed;

काष्ठा cop_symcpb_aes_xcbc अणु
	u8 cv[16];
	u8 key[16];
	u8 __rsvd1[16];
	u8 out_cv_mac[16];
	u32 spbc;
	u8 __rsvd2[44];
पूर्ण __packed;

काष्ठा cop_symcpb_sha256 अणु
	u64 message_bit_length;
	u64 __rsvd1;
	u8 input_partial_digest[32];
	u8 message_digest[32];
	u32 spbc;
	u8 __rsvd2[44];
पूर्ण __packed;

काष्ठा cop_symcpb_sha512 अणु
	u64 message_bit_length_hi;
	u64 message_bit_length_lo;
	u8 input_partial_digest[64];
	u8 __rsvd1[32];
	u8 message_digest[64];
	u32 spbc;
	u8 __rsvd2[76];
पूर्ण __packed;

#घोषणा NX_FDM_INTERMEDIATE		0x01
#घोषणा NX_FDM_CONTINUATION		0x02
#घोषणा NX_FDM_ENDE_ENCRYPT		0x80

#घोषणा NX_CPB_FDM(c)			((c)->cpb.hdr.fdm)
#घोषणा NX_CPB_KS_DS(c)			((c)->cpb.hdr.ks_ds)

#घोषणा NX_CPB_KEY_SIZE(c)		(NX_CPB_KS_DS(c) >> 4)
#घोषणा NX_CPB_SET_KEY_SIZE(c, x)	NX_CPB_KS_DS(c) |= ((x) << 4)
#घोषणा NX_CPB_SET_DIGEST_SIZE(c, x)	NX_CPB_KS_DS(c) |= (x)

काष्ठा cop_symcpb_header अणु
	u8 mode;
	u8 fdm;
	u8 ks_ds;
	u8 pad_byte;
	u8 __rsvd[12];
पूर्ण __packed;

काष्ठा cop_parameter_block अणु
	काष्ठा cop_symcpb_header hdr;
	जोड़ अणु
		काष्ठा cop_symcpb_aes_ecb  aes_ecb;
		काष्ठा cop_symcpb_aes_cbc  aes_cbc;
		काष्ठा cop_symcpb_aes_gca  aes_gca;
		काष्ठा cop_symcpb_aes_gcm  aes_gcm;
		काष्ठा cop_symcpb_aes_cca  aes_cca;
		काष्ठा cop_symcpb_aes_ccm  aes_ccm;
		काष्ठा cop_symcpb_aes_ctr  aes_ctr;
		काष्ठा cop_symcpb_aes_xcbc aes_xcbc;
		काष्ठा cop_symcpb_sha256   sha256;
		काष्ठा cop_symcpb_sha512   sha512;
	पूर्ण;
पूर्ण __packed;

#घोषणा NX_CSB_VALID_BIT	0x80

/* co-processor status block */
काष्ठा cop_status_block अणु
	u8 valid;
	u8 crb_seq_number;
	u8 completion_code;
	u8 completion_extension;
	u32 processed_byte_count;
	u64 address;
पूर्ण __packed;

/* Nest accelerator workbook section 4.4 */
काष्ठा nx_csbcpb अणु
	अचिन्हित अक्षर __rsvd[112];
	काष्ठा cop_status_block csb;
	काष्ठा cop_parameter_block cpb;
पूर्ण __packed;

/* nx_csbcpb related definitions */
#घोषणा NX_MODE_AES_ECB			0
#घोषणा NX_MODE_AES_CBC			1
#घोषणा NX_MODE_AES_GMAC		2
#घोषणा NX_MODE_AES_GCA			3
#घोषणा NX_MODE_AES_GCM			4
#घोषणा NX_MODE_AES_CCA			5
#घोषणा NX_MODE_AES_CCM			6
#घोषणा NX_MODE_AES_CTR			7
#घोषणा NX_MODE_AES_XCBC_MAC		20
#घोषणा NX_MODE_SHA			0
#घोषणा NX_MODE_SHA_HMAC		1
#घोषणा NX_MODE_AES_CBC_HMAC_ETA	8
#घोषणा NX_MODE_AES_CBC_HMAC_ATE	9
#घोषणा NX_MODE_AES_CBC_HMAC_EAA	10
#घोषणा NX_MODE_AES_CTR_HMAC_ETA	12
#घोषणा NX_MODE_AES_CTR_HMAC_ATE	13
#घोषणा NX_MODE_AES_CTR_HMAC_EAA	14

#घोषणा NX_FDM_CI_FULL		0
#घोषणा NX_FDM_CI_FIRST		1
#घोषणा NX_FDM_CI_LAST		2
#घोषणा NX_FDM_CI_MIDDLE	3

#घोषणा NX_FDM_PR_NONE		0
#घोषणा NX_FDM_PR_PAD		1

#घोषणा NX_KS_AES_128		1
#घोषणा NX_KS_AES_192		2
#घोषणा NX_KS_AES_256		3

#घोषणा NX_DS_SHA256		2
#घोषणा NX_DS_SHA512		3

#घोषणा NX_FC_AES		0
#घोषणा NX_FC_SHA		2
#घोषणा NX_FC_AES_HMAC		6

#घोषणा NX_MAX_FC		(NX_FC_AES_HMAC + 1)
#घोषणा NX_MAX_MODE		(NX_MODE_AES_XCBC_MAC + 1)

#घोषणा HCOP_FC_AES          NX_FC_AES
#घोषणा HCOP_FC_SHA          NX_FC_SHA
#घोषणा HCOP_FC_AES_HMAC     NX_FC_AES_HMAC

/* indices पूर्णांकo the array of algorithm properties */
#घोषणा NX_PROPS_AES_128		0
#घोषणा NX_PROPS_AES_192		1
#घोषणा NX_PROPS_AES_256		2
#घोषणा NX_PROPS_SHA256			1
#घोषणा NX_PROPS_SHA512			2

#पूर्ण_अगर
