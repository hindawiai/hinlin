<शैली गुरु>
/*
 * This file is part of the Chelsio T6 Crypto driver क्रम Linux.
 *
 * Copyright (c) 2003-2016 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#अगर_अघोषित __CHCR_ALGO_H__
#घोषणा __CHCR_ALGO_H__

/* Crypto key context */
#घोषणा KEY_CONTEXT_CTX_LEN_S           24
#घोषणा KEY_CONTEXT_CTX_LEN_M           0xff
#घोषणा KEY_CONTEXT_CTX_LEN_V(x)        ((x) << KEY_CONTEXT_CTX_LEN_S)
#घोषणा KEY_CONTEXT_CTX_LEN_G(x) \
	(((x) >> KEY_CONTEXT_CTX_LEN_S) & KEY_CONTEXT_CTX_LEN_M)

#घोषणा KEY_CONTEXT_DUAL_CK_S      12
#घोषणा KEY_CONTEXT_DUAL_CK_M      0x1
#घोषणा KEY_CONTEXT_DUAL_CK_V(x)   ((x) << KEY_CONTEXT_DUAL_CK_S)
#घोषणा KEY_CONTEXT_DUAL_CK_G(x)   \
(((x) >> KEY_CONTEXT_DUAL_CK_S) & KEY_CONTEXT_DUAL_CK_M)
#घोषणा KEY_CONTEXT_DUAL_CK_F      KEY_CONTEXT_DUAL_CK_V(1U)

#घोषणा KEY_CONTEXT_SALT_PRESENT_S      10
#घोषणा KEY_CONTEXT_SALT_PRESENT_M      0x1
#घोषणा KEY_CONTEXT_SALT_PRESENT_V(x)   ((x) << KEY_CONTEXT_SALT_PRESENT_S)
#घोषणा KEY_CONTEXT_SALT_PRESENT_G(x)   \
	(((x) >> KEY_CONTEXT_SALT_PRESENT_S) & \
	 KEY_CONTEXT_SALT_PRESENT_M)
#घोषणा KEY_CONTEXT_SALT_PRESENT_F      KEY_CONTEXT_SALT_PRESENT_V(1U)

#घोषणा KEY_CONTEXT_VALID_S     0
#घोषणा KEY_CONTEXT_VALID_M     0x1
#घोषणा KEY_CONTEXT_VALID_V(x)  ((x) << KEY_CONTEXT_VALID_S)
#घोषणा KEY_CONTEXT_VALID_G(x)  \
	(((x) >> KEY_CONTEXT_VALID_S) & \
	 KEY_CONTEXT_VALID_M)
#घोषणा KEY_CONTEXT_VALID_F     KEY_CONTEXT_VALID_V(1U)

#घोषणा KEY_CONTEXT_CK_SIZE_S           6
#घोषणा KEY_CONTEXT_CK_SIZE_M           0xf
#घोषणा KEY_CONTEXT_CK_SIZE_V(x)        ((x) << KEY_CONTEXT_CK_SIZE_S)
#घोषणा KEY_CONTEXT_CK_SIZE_G(x)        \
	(((x) >> KEY_CONTEXT_CK_SIZE_S) & KEY_CONTEXT_CK_SIZE_M)

#घोषणा KEY_CONTEXT_MK_SIZE_S           2
#घोषणा KEY_CONTEXT_MK_SIZE_M           0xf
#घोषणा KEY_CONTEXT_MK_SIZE_V(x)        ((x) << KEY_CONTEXT_MK_SIZE_S)
#घोषणा KEY_CONTEXT_MK_SIZE_G(x)        \
	(((x) >> KEY_CONTEXT_MK_SIZE_S) & KEY_CONTEXT_MK_SIZE_M)

#घोषणा KEY_CONTEXT_OPAD_PRESENT_S      11
#घोषणा KEY_CONTEXT_OPAD_PRESENT_M      0x1
#घोषणा KEY_CONTEXT_OPAD_PRESENT_V(x)   ((x) << KEY_CONTEXT_OPAD_PRESENT_S)
#घोषणा KEY_CONTEXT_OPAD_PRESENT_G(x)   \
	(((x) >> KEY_CONTEXT_OPAD_PRESENT_S) & \
	 KEY_CONTEXT_OPAD_PRESENT_M)
#घोषणा KEY_CONTEXT_OPAD_PRESENT_F      KEY_CONTEXT_OPAD_PRESENT_V(1U)

#घोषणा CHCR_HASH_MAX_DIGEST_SIZE 64
#घोषणा CHCR_MAX_SHA_DIGEST_SIZE 64

#घोषणा IPSEC_TRUNCATED_ICV_SIZE 12
#घोषणा TLS_TRUNCATED_HMAC_SIZE 10
#घोषणा CBCMAC_DIGEST_SIZE 16
#घोषणा MAX_HASH_NAME 20

#घोषणा SHA1_INIT_STATE_5X4B    5
#घोषणा SHA256_INIT_STATE_8X4B  8
#घोषणा SHA512_INIT_STATE_8X8B  8
#घोषणा SHA1_INIT_STATE         SHA1_INIT_STATE_5X4B
#घोषणा SHA224_INIT_STATE       SHA256_INIT_STATE_8X4B
#घोषणा SHA256_INIT_STATE       SHA256_INIT_STATE_8X4B
#घोषणा SHA384_INIT_STATE       SHA512_INIT_STATE_8X8B
#घोषणा SHA512_INIT_STATE       SHA512_INIT_STATE_8X8B

#घोषणा DUMMY_BYTES 16

#घोषणा IPAD_DATA 0x36363636
#घोषणा OPAD_DATA 0x5c5c5c5c

#घोषणा TRANSHDR_SIZE(kctx_len)\
	(माप(काष्ठा chcr_wr) +\
	 kctx_len)
#घोषणा CIPHER_TRANSHDR_SIZE(kctx_len, sge_pairs) \
	(TRANSHDR_SIZE((kctx_len)) + (sge_pairs) +\
	 माप(काष्ठा cpl_rx_phys_dsgl) + AES_BLOCK_SIZE)
#घोषणा HASH_TRANSHDR_SIZE(kctx_len)\
	(TRANSHDR_SIZE(kctx_len) + DUMMY_BYTES)


#घोषणा FILL_SEC_CPL_OP_IVINSR(id, len, ofst)      \
	htonl( \
	       CPL_TX_SEC_PDU_OPCODE_V(CPL_TX_SEC_PDU) | \
	       CPL_TX_SEC_PDU_RXCHID_V((id)) | \
	       CPL_TX_SEC_PDU_ACKFOLLOWS_V(0) | \
	       CPL_TX_SEC_PDU_ULPTXLPBK_V(1) | \
	       CPL_TX_SEC_PDU_CPLLEN_V((len)) | \
	       CPL_TX_SEC_PDU_PLACEHOLDER_V(0) | \
	       CPL_TX_SEC_PDU_IVINSRTOFST_V((ofst)))

#घोषणा  FILL_SEC_CPL_CIPHERSTOP_HI(a_start, a_stop, c_start, c_stop_hi) \
	htonl( \
	       CPL_TX_SEC_PDU_AADSTART_V((a_start)) | \
	       CPL_TX_SEC_PDU_AADSTOP_V((a_stop)) | \
	       CPL_TX_SEC_PDU_CIPHERSTART_V((c_start)) | \
	       CPL_TX_SEC_PDU_CIPHERSTOP_HI_V((c_stop_hi)))

#घोषणा  FILL_SEC_CPL_AUTHINSERT(c_stop_lo, a_start, a_stop, a_inst) \
	htonl( \
	       CPL_TX_SEC_PDU_CIPHERSTOP_LO_V((c_stop_lo)) | \
		CPL_TX_SEC_PDU_AUTHSTART_V((a_start)) | \
		CPL_TX_SEC_PDU_AUTHSTOP_V((a_stop)) | \
		CPL_TX_SEC_PDU_AUTHINSERT_V((a_inst)))

#घोषणा  FILL_SEC_CPL_SCMD0_SEQNO(ctrl, seq, cmode, amode, opad, size)  \
		htonl( \
		SCMD_SEQ_NO_CTRL_V(0) | \
		SCMD_STATUS_PRESENT_V(0) | \
		SCMD_PROTO_VERSION_V(CHCR_SCMD_PROTO_VERSION_GENERIC) | \
		SCMD_ENC_DEC_CTRL_V((ctrl)) | \
		SCMD_CIPH_AUTH_SEQ_CTRL_V((seq)) | \
		SCMD_CIPH_MODE_V((cmode)) | \
		SCMD_AUTH_MODE_V((amode)) | \
		SCMD_HMAC_CTRL_V((opad)) | \
		SCMD_IV_SIZE_V((size)) | \
		SCMD_NUM_IVS_V(0))

#घोषणा FILL_SEC_CPL_IVGEN_HDRLEN(last, more, ctx_in, mac, ivdrop, len) htonl( \
		SCMD_ENB_DBGID_V(0) | \
		SCMD_IV_GEN_CTRL_V(0) | \
		SCMD_LAST_FRAG_V((last)) | \
		SCMD_MORE_FRAGS_V((more)) | \
		SCMD_TLS_COMPPDU_V(0) | \
		SCMD_KEY_CTX_INLINE_V((ctx_in)) | \
		SCMD_TLS_FRAG_ENABLE_V(0) | \
		SCMD_MAC_ONLY_V((mac)) |  \
		SCMD_AADIVDROP_V((ivdrop)) | \
		SCMD_HDR_LEN_V((len)))

#घोषणा  FILL_KEY_CTX_HDR(ck_size, mk_size, d_ck, opad, ctx_len) \
		htonl(KEY_CONTEXT_VALID_V(1) | \
		      KEY_CONTEXT_CK_SIZE_V((ck_size)) | \
		      KEY_CONTEXT_MK_SIZE_V(mk_size) | \
		      KEY_CONTEXT_DUAL_CK_V((d_ck)) | \
		      KEY_CONTEXT_OPAD_PRESENT_V((opad)) | \
		      KEY_CONTEXT_SALT_PRESENT_V(1) | \
		      KEY_CONTEXT_CTX_LEN_V((ctx_len)))

#घोषणा  FILL_KEY_CRX_HDR(ck_size, mk_size, d_ck, opad, ctx_len) \
		htonl(TLS_KEYCTX_RXMK_SIZE_V(mk_size) | \
		      TLS_KEYCTX_RXCK_SIZE_V(ck_size) | \
		      TLS_KEYCTX_RX_VALID_V(1) | \
		      TLS_KEYCTX_RX_SEQCTR_V(3) | \
		      TLS_KEYCTX_RXAUTH_MODE_V(4) | \
		      TLS_KEYCTX_RXCIPH_MODE_V(2) | \
		      TLS_KEYCTX_RXFLIT_CNT_V((ctx_len)))

#घोषणा FILL_WR_OP_CCTX_SIZE \
		htonl( \
			FW_CRYPTO_LOOKASIDE_WR_OPCODE_V( \
			FW_CRYPTO_LOOKASIDE_WR) | \
			FW_CRYPTO_LOOKASIDE_WR_COMPL_V(0) | \
			FW_CRYPTO_LOOKASIDE_WR_IMM_LEN_V((0)) | \
			FW_CRYPTO_LOOKASIDE_WR_CCTX_LOC_V(0) | \
			FW_CRYPTO_LOOKASIDE_WR_CCTX_SIZE_V(0))

#घोषणा FILL_WR_RX_Q_ID(cid, qid, lcb, fid) \
		htonl( \
			FW_CRYPTO_LOOKASIDE_WR_RX_CHID_V((cid)) | \
			FW_CRYPTO_LOOKASIDE_WR_RX_Q_ID_V((qid)) | \
			FW_CRYPTO_LOOKASIDE_WR_LCB_V((lcb)) | \
			FW_CRYPTO_LOOKASIDE_WR_IV_V((IV_NOP)) | \
			FW_CRYPTO_LOOKASIDE_WR_FQIDX_V(fid))

#घोषणा FILL_ULPTX_CMD_DEST(cid, qid) \
	htonl(ULPTX_CMD_V(ULP_TX_PKT) | \
	      ULP_TXPKT_DEST_V(0) | \
	      ULP_TXPKT_DATAMODIFY_V(0) | \
	      ULP_TXPKT_CHANNELID_V((cid)) | \
	      ULP_TXPKT_RO_V(1) | \
	      ULP_TXPKT_FID_V(qid))

#घोषणा KEYCTX_ALIGN_PAD(bs) (अणुअचिन्हित पूर्णांक _bs = (bs);\
			      _bs == SHA1_DIGEST_SIZE ? 12 : 0; पूर्ण)

#घोषणा FILL_PLD_SIZE_HASH_SIZE(payload_sgl_len, sgl_lengths, total_frags) \
	htonl(FW_CRYPTO_LOOKASIDE_WR_PLD_SIZE_V(payload_sgl_len ? \
						sgl_lengths[total_frags] : 0) |\
	      FW_CRYPTO_LOOKASIDE_WR_HASH_SIZE_V(0))

#घोषणा FILL_LEN_PKD(calc_tx_flits_ofld, skb) \
	htonl(FW_CRYPTO_LOOKASIDE_WR_LEN16_V(DIV_ROUND_UP((\
					   calc_tx_flits_ofld(skb) * 8), 16)))

#घोषणा FILL_CMD_MORE(immdatalen) htonl(ULPTX_CMD_V(ULP_TX_SC_IMM) |\
					ULP_TX_SC_MORE_V((immdatalen)))
#घोषणा MAX_NK 8
#घोषणा MAX_DSGL_ENT			32
#घोषणा MIN_AUTH_SG			1 /* IV */
#घोषणा MIN_GCM_SG			1 /* IV */
#घोषणा MIN_DIGEST_SG			1 /*Partial Buffer*/
#घोषणा MIN_CCM_SG			1 /*IV+B0*/
#घोषणा CIP_SPACE_LEFT(len) \
	((SGE_MAX_WR_LEN - CIP_WR_MIN_LEN - (len)))
#घोषणा HASH_SPACE_LEFT(len) \
	((SGE_MAX_WR_LEN - HASH_WR_MIN_LEN - (len)))

काष्ठा algo_param अणु
	अचिन्हित पूर्णांक auth_mode;
	अचिन्हित पूर्णांक mk_size;
	अचिन्हित पूर्णांक result_size;
पूर्ण;

काष्ठा hash_wr_param अणु
	काष्ठा algo_param alg_prm;
	अचिन्हित पूर्णांक opad_needed;
	अचिन्हित पूर्णांक more;
	अचिन्हित पूर्णांक last;
	अचिन्हित पूर्णांक kctx_len;
	अचिन्हित पूर्णांक sg_len;
	अचिन्हित पूर्णांक bfr_len;
	अचिन्हित पूर्णांक hash_size;
	u64 scmd1;
पूर्ण;

काष्ठा cipher_wr_param अणु
	काष्ठा skcipher_request *req;
	अक्षर *iv;
	पूर्णांक bytes;
	अचिन्हित लघु qid;
पूर्ण;
क्रमागत अणु
	AES_KEYLENGTH_128BIT = 128,
	AES_KEYLENGTH_192BIT = 192,
	AES_KEYLENGTH_256BIT = 256
पूर्ण;

क्रमागत अणु
	KEYLENGTH_3BYTES = 3,
	KEYLENGTH_4BYTES = 4,
	KEYLENGTH_6BYTES = 6,
	KEYLENGTH_8BYTES = 8
पूर्ण;

क्रमागत अणु
	NUMBER_OF_ROUNDS_10 = 10,
	NUMBER_OF_ROUNDS_12 = 12,
	NUMBER_OF_ROUNDS_14 = 14,
पूर्ण;

/*
 * CCM defines values of 4, 6, 8, 10, 12, 14, and 16 octets,
 * where they indicate the size of the पूर्णांकegrity check value (ICV)
 */
क्रमागत अणु
	ICV_4  = 4,
	ICV_6  = 6,
	ICV_8  = 8,
	ICV_10 = 10,
	ICV_12 = 12,
	ICV_13 = 13,
	ICV_14 = 14,
	ICV_15 = 15,
	ICV_16 = 16
पूर्ण;

काष्ठा phys_sge_pairs अणु
	__be16 len[8];
	__be64 addr[8];
पूर्ण;


अटल स्थिर u32 chcr_sha1_init[SHA1_DIGEST_SIZE / 4] = अणु
		SHA1_H0, SHA1_H1, SHA1_H2, SHA1_H3, SHA1_H4,
पूर्ण;

अटल स्थिर u32 chcr_sha224_init[SHA256_DIGEST_SIZE / 4] = अणु
		SHA224_H0, SHA224_H1, SHA224_H2, SHA224_H3,
		SHA224_H4, SHA224_H5, SHA224_H6, SHA224_H7,
पूर्ण;

अटल स्थिर u32 chcr_sha256_init[SHA256_DIGEST_SIZE / 4] = अणु
		SHA256_H0, SHA256_H1, SHA256_H2, SHA256_H3,
		SHA256_H4, SHA256_H5, SHA256_H6, SHA256_H7,
पूर्ण;

अटल स्थिर u64 chcr_sha384_init[SHA512_DIGEST_SIZE / 8] = अणु
		SHA384_H0, SHA384_H1, SHA384_H2, SHA384_H3,
		SHA384_H4, SHA384_H5, SHA384_H6, SHA384_H7,
पूर्ण;

अटल स्थिर u64 chcr_sha512_init[SHA512_DIGEST_SIZE / 8] = अणु
		SHA512_H0, SHA512_H1, SHA512_H2, SHA512_H3,
		SHA512_H4, SHA512_H5, SHA512_H6, SHA512_H7,
पूर्ण;

अटल अंतरभूत व्योम copy_hash_init_values(अक्षर *key, पूर्णांक digestsize)
अणु
	u8 i;
	__be32 *dkey = (__be32 *)key;
	u64 *ldkey = (u64 *)key;
	__be64 *sha384 = (__be64 *)chcr_sha384_init;
	__be64 *sha512 = (__be64 *)chcr_sha512_init;

	चयन (digestsize) अणु
	हाल SHA1_DIGEST_SIZE:
		क्रम (i = 0; i < SHA1_INIT_STATE; i++)
			dkey[i] = cpu_to_be32(chcr_sha1_init[i]);
		अवरोध;
	हाल SHA224_DIGEST_SIZE:
		क्रम (i = 0; i < SHA224_INIT_STATE; i++)
			dkey[i] = cpu_to_be32(chcr_sha224_init[i]);
		अवरोध;
	हाल SHA256_DIGEST_SIZE:
		क्रम (i = 0; i < SHA256_INIT_STATE; i++)
			dkey[i] = cpu_to_be32(chcr_sha256_init[i]);
		अवरोध;
	हाल SHA384_DIGEST_SIZE:
		क्रम (i = 0; i < SHA384_INIT_STATE; i++)
			ldkey[i] = be64_to_cpu(sha384[i]);
		अवरोध;
	हाल SHA512_DIGEST_SIZE:
		क्रम (i = 0; i < SHA512_INIT_STATE; i++)
			ldkey[i] = be64_to_cpu(sha512[i]);
		अवरोध;
	पूर्ण
पूर्ण

/* Number of len fields(8) * size of one addr field */
#घोषणा PHYSDSGL_MAX_LEN_SIZE 16

अटल अंतरभूत u16 get_space_क्रम_phys_dsgl(अचिन्हित पूर्णांक sgl_entr)
अणु
	/* len field size + addr field size */
	वापस ((sgl_entr >> 3) + ((sgl_entr % 8) ?
				   1 : 0)) * PHYSDSGL_MAX_LEN_SIZE +
		(sgl_entr << 3) + ((sgl_entr % 2 ? 1 : 0) << 3);
पूर्ण

/* The AES s-transक्रमm matrix (s-box). */
अटल स्थिर u8 aes_sbox[256] = अणु
	99,  124, 119, 123, 242, 107, 111, 197, 48,  1,   103, 43,  254, 215,
	171, 118, 202, 130, 201, 125, 250, 89,  71,  240, 173, 212, 162, 175,
	156, 164, 114, 192, 183, 253, 147, 38,  54,  63,  247, 204, 52,  165,
	229, 241, 113, 216, 49,  21, 4,   199, 35,  195, 24,  150, 5, 154, 7,
	18,  128, 226, 235, 39,  178, 117, 9,   131, 44,  26,  27,  110, 90,
	160, 82,  59,  214, 179, 41,  227, 47,  132, 83,  209, 0,   237, 32,
	252, 177, 91,  106, 203, 190, 57,  74,  76,  88,  207, 208, 239, 170,
	251, 67,  77,  51,  133, 69,  249, 2,   127, 80,  60,  159, 168, 81,
	163, 64,  143, 146, 157, 56,  245, 188, 182, 218, 33,  16,  255, 243,
	210, 205, 12,  19,  236, 95,  151, 68,  23,  196, 167, 126, 61,  100,
	93,  25,  115, 96,  129, 79,  220, 34,  42,  144, 136, 70,  238, 184,
	20,  222, 94,  11,  219, 224, 50,  58,  10,  73,  6,   36,  92,  194,
	211, 172, 98,  145, 149, 228, 121, 231, 200, 55,  109, 141, 213, 78,
	169, 108, 86,  244, 234, 101, 122, 174, 8, 186, 120, 37,  46,  28, 166,
	180, 198, 232, 221, 116, 31,  75,  189, 139, 138, 112, 62,  181, 102,
	72,  3,   246, 14,  97,  53,  87,  185, 134, 193, 29,  158, 225, 248,
	152, 17,  105, 217, 142, 148, 155, 30,  135, 233, 206, 85,  40,  223,
	140, 161, 137, 13,  191, 230, 66,  104, 65,  153, 45,  15,  176, 84,
	187, 22
पूर्ण;

अटल अंतरभूत u32 aes_ks_subword(स्थिर u32 w)
अणु
	u8 bytes[4];

	*(u32 *)(&bytes[0]) = w;
	bytes[0] = aes_sbox[bytes[0]];
	bytes[1] = aes_sbox[bytes[1]];
	bytes[2] = aes_sbox[bytes[2]];
	bytes[3] = aes_sbox[bytes[3]];
	वापस *(u32 *)(&bytes[0]);
पूर्ण

#पूर्ण_अगर /* __CHCR_ALGO_H__ */
