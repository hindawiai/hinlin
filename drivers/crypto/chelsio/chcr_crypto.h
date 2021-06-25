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

#अगर_अघोषित __CHCR_CRYPTO_H__
#घोषणा __CHCR_CRYPTO_H__

#घोषणा GHASH_BLOCK_SIZE    16
#घोषणा GHASH_DIGEST_SIZE   16

#घोषणा CCM_B0_SIZE             16
#घोषणा CCM_AAD_FIELD_SIZE      2
// 511 - 16(For IV)
#घोषणा T6_MAX_AAD_SIZE 495


/* Define following अगर h/w is not dropping the AAD and IV data beक्रमe
 * giving the processed data
 */

#घोषणा CHCR_CRA_PRIORITY 500
#घोषणा CHCR_AEAD_PRIORITY 6000
#घोषणा CHCR_AES_MAX_KEY_LEN  (2 * (AES_MAX_KEY_SIZE)) /* consider xts */
#घोषणा CHCR_MAX_CRYPTO_IV_LEN 16 /* AES IV len */

#घोषणा CHCR_MAX_AUTHENC_AES_KEY_LEN 32 /* max aes key length*/
#घोषणा CHCR_MAX_AUTHENC_SHA_KEY_LEN 128 /* max sha key length*/

#घोषणा CHCR_GIVENCRYPT_OP 2
/* CPL/SCMD parameters */

#घोषणा CHCR_ENCRYPT_OP 0
#घोषणा CHCR_DECRYPT_OP 1

#घोषणा CHCR_SCMD_SEQ_NO_CTRL_32BIT     1
#घोषणा CHCR_SCMD_SEQ_NO_CTRL_48BIT     2
#घोषणा CHCR_SCMD_SEQ_NO_CTRL_64BIT     3

#घोषणा CHCR_SCMD_PROTO_VERSION_GENERIC 4

#घोषणा CHCR_SCMD_AUTH_CTRL_AUTH_CIPHER 0
#घोषणा CHCR_SCMD_AUTH_CTRL_CIPHER_AUTH 1

#घोषणा CHCR_SCMD_CIPHER_MODE_NOP               0
#घोषणा CHCR_SCMD_CIPHER_MODE_AES_CBC           1
#घोषणा CHCR_SCMD_CIPHER_MODE_AES_GCM           2
#घोषणा CHCR_SCMD_CIPHER_MODE_AES_CTR           3
#घोषणा CHCR_SCMD_CIPHER_MODE_GENERIC_AES       4
#घोषणा CHCR_SCMD_CIPHER_MODE_AES_XTS           6
#घोषणा CHCR_SCMD_CIPHER_MODE_AES_CCM           7

#घोषणा CHCR_SCMD_AUTH_MODE_NOP             0
#घोषणा CHCR_SCMD_AUTH_MODE_SHA1            1
#घोषणा CHCR_SCMD_AUTH_MODE_SHA224          2
#घोषणा CHCR_SCMD_AUTH_MODE_SHA256          3
#घोषणा CHCR_SCMD_AUTH_MODE_GHASH           4
#घोषणा CHCR_SCMD_AUTH_MODE_SHA512_224      5
#घोषणा CHCR_SCMD_AUTH_MODE_SHA512_256      6
#घोषणा CHCR_SCMD_AUTH_MODE_SHA512_384      7
#घोषणा CHCR_SCMD_AUTH_MODE_SHA512_512      8
#घोषणा CHCR_SCMD_AUTH_MODE_CBCMAC          9
#घोषणा CHCR_SCMD_AUTH_MODE_CMAC            10

#घोषणा CHCR_SCMD_HMAC_CTRL_NOP             0
#घोषणा CHCR_SCMD_HMAC_CTRL_NO_TRUNC        1
#घोषणा CHCR_SCMD_HMAC_CTRL_TRUNC_RFC4366   2
#घोषणा CHCR_SCMD_HMAC_CTRL_IPSEC_96BIT     3
#घोषणा CHCR_SCMD_HMAC_CTRL_PL1		    4
#घोषणा CHCR_SCMD_HMAC_CTRL_PL2		    5
#घोषणा CHCR_SCMD_HMAC_CTRL_PL3		    6
#घोषणा CHCR_SCMD_HMAC_CTRL_DIV2	    7
#घोषणा VERIFY_HW 0
#घोषणा VERIFY_SW 1

#घोषणा CHCR_SCMD_IVGEN_CTRL_HW             0
#घोषणा CHCR_SCMD_IVGEN_CTRL_SW             1
/* This are not really mac key size. They are पूर्णांकermediate values
 * of sha engine and its size
 */
#घोषणा CHCR_KEYCTX_MAC_KEY_SIZE_128        0
#घोषणा CHCR_KEYCTX_MAC_KEY_SIZE_160        1
#घोषणा CHCR_KEYCTX_MAC_KEY_SIZE_192        2
#घोषणा CHCR_KEYCTX_MAC_KEY_SIZE_256        3
#घोषणा CHCR_KEYCTX_MAC_KEY_SIZE_512        4
#घोषणा CHCR_KEYCTX_CIPHER_KEY_SIZE_128     0
#घोषणा CHCR_KEYCTX_CIPHER_KEY_SIZE_192     1
#घोषणा CHCR_KEYCTX_CIPHER_KEY_SIZE_256     2
#घोषणा CHCR_KEYCTX_NO_KEY                  15

#घोषणा CHCR_CPL_FW4_PLD_IV_OFFSET          (5 * 64) /* bytes. flt #5 and #6 */
#घोषणा CHCR_CPL_FW4_PLD_HASH_RESULT_OFFSET (7 * 64) /* bytes. flt #7 */
#घोषणा CHCR_CPL_FW4_PLD_DATA_SIZE          (4 * 64) /* bytes. flt #4 to #7 */

#घोषणा KEY_CONTEXT_HDR_SALT_AND_PAD	    16
#घोषणा flits_to_bytes(x)  (x * 8)

#घोषणा IV_NOP                  0
#घोषणा IV_IMMEDIATE            1
#घोषणा IV_DSGL			2

#घोषणा AEAD_H_SIZE             16

#घोषणा CRYPTO_ALG_SUB_TYPE_MASK            0x0f000000
#घोषणा CRYPTO_ALG_SUB_TYPE_HASH_HMAC       0x01000000
#घोषणा CRYPTO_ALG_SUB_TYPE_AEAD_RFC4106    0x02000000
#घोषणा CRYPTO_ALG_SUB_TYPE_AEAD_GCM	    0x03000000
#घोषणा CRYPTO_ALG_SUB_TYPE_CBC_SHA	    0x04000000
#घोषणा CRYPTO_ALG_SUB_TYPE_AEAD_CCM        0x05000000
#घोषणा CRYPTO_ALG_SUB_TYPE_AEAD_RFC4309    0x06000000
#घोषणा CRYPTO_ALG_SUB_TYPE_CBC_शून्य	    0x07000000
#घोषणा CRYPTO_ALG_SUB_TYPE_CTR             0x08000000
#घोषणा CRYPTO_ALG_SUB_TYPE_CTR_RFC3686     0x09000000
#घोषणा CRYPTO_ALG_SUB_TYPE_XTS		    0x0a000000
#घोषणा CRYPTO_ALG_SUB_TYPE_CBC		    0x0b000000
#घोषणा CRYPTO_ALG_SUB_TYPE_CTR_SHA	    0x0c000000
#घोषणा CRYPTO_ALG_SUB_TYPE_CTR_शून्य   0x0d000000
#घोषणा CRYPTO_ALG_TYPE_HMAC (CRYPTO_ALG_TYPE_AHASH |\
			      CRYPTO_ALG_SUB_TYPE_HASH_HMAC)

#घोषणा MAX_SCRATCH_PAD_SIZE    32

#घोषणा CHCR_HASH_MAX_BLOCK_SIZE_64  64
#घोषणा CHCR_HASH_MAX_BLOCK_SIZE_128 128
#घोषणा CHCR_SRC_SG_SIZE (0x10000 - माप(पूर्णांक))
#घोषणा CHCR_DST_SG_SIZE 2048

अटल अंतरभूत काष्ठा chcr_context *a_ctx(काष्ठा crypto_aead *tfm)
अणु
	वापस crypto_aead_ctx(tfm);
पूर्ण

अटल अंतरभूत काष्ठा chcr_context *c_ctx(काष्ठा crypto_skcipher *tfm)
अणु
	वापस crypto_skcipher_ctx(tfm);
पूर्ण

अटल अंतरभूत काष्ठा chcr_context *h_ctx(काष्ठा crypto_ahash *tfm)
अणु
	वापस crypto_tfm_ctx(crypto_ahash_tfm(tfm));
पूर्ण

काष्ठा ablk_ctx अणु
	काष्ठा crypto_skcipher *sw_cipher;
	__be32 key_ctx_hdr;
	अचिन्हित पूर्णांक enckey_len;
	अचिन्हित अक्षर ciph_mode;
	u8 key[CHCR_AES_MAX_KEY_LEN];
	u8 nonce[4];
	u8 rrkey[AES_MAX_KEY_SIZE];
पूर्ण;
काष्ठा chcr_aead_reqctx अणु
	काष्ठा	sk_buff	*skb;
	dma_addr_t iv_dma;
	dma_addr_t b0_dma;
	अचिन्हित पूर्णांक b0_len;
	अचिन्हित पूर्णांक op;
	u16 imm;
	u16 verअगरy;
	u16 txqidx;
	u16 rxqidx;
	u8 iv[CHCR_MAX_CRYPTO_IV_LEN + MAX_SCRATCH_PAD_SIZE];
	u8 *scratch_pad;
पूर्ण;

काष्ठा ulptx_walk अणु
	काष्ठा ulptx_sgl *sgl;
	अचिन्हित पूर्णांक nents;
	अचिन्हित पूर्णांक pair_idx;
	अचिन्हित पूर्णांक last_sg_len;
	काष्ठा scatterlist *last_sg;
	काष्ठा ulptx_sge_pair *pair;

पूर्ण;

काष्ठा dsgl_walk अणु
	अचिन्हित पूर्णांक nents;
	अचिन्हित पूर्णांक last_sg_len;
	काष्ठा scatterlist *last_sg;
	काष्ठा cpl_rx_phys_dsgl *dsgl;
	काष्ठा phys_sge_pairs *to;
पूर्ण;

काष्ठा chcr_gcm_ctx अणु
	u8 ghash_h[AEAD_H_SIZE];
पूर्ण;

काष्ठा chcr_authenc_ctx अणु
	u8 dec_rrkey[AES_MAX_KEY_SIZE];
	u8 h_iopad[2 * CHCR_HASH_MAX_DIGEST_SIZE];
	अचिन्हित अक्षर auth_mode;
पूर्ण;

काष्ठा __aead_ctx अणु
	काष्ठा chcr_gcm_ctx gcm[0];
	काष्ठा chcr_authenc_ctx authenc[];
पूर्ण;

काष्ठा chcr_aead_ctx अणु
	__be32 key_ctx_hdr;
	अचिन्हित पूर्णांक enckey_len;
	काष्ठा crypto_aead *sw_cipher;
	u8 salt[MAX_SALT];
	u8 key[CHCR_AES_MAX_KEY_LEN];
	u8 nonce[4];
	u16 hmac_ctrl;
	u16 mayverअगरy;
	काष्ठा	__aead_ctx ctx[];
पूर्ण;

काष्ठा hmac_ctx अणु
	काष्ठा crypto_shash *base_hash;
	u8 ipad[CHCR_HASH_MAX_BLOCK_SIZE_128];
	u8 opad[CHCR_HASH_MAX_BLOCK_SIZE_128];
पूर्ण;

काष्ठा __crypto_ctx अणु
	काष्ठा hmac_ctx hmacctx[0];
	काष्ठा ablk_ctx ablkctx[0];
	काष्ठा chcr_aead_ctx aeadctx[];
पूर्ण;

काष्ठा chcr_context अणु
	काष्ठा chcr_dev *dev;
	अचिन्हित अक्षर rxq_perchan;
	अचिन्हित अक्षर txq_perchan;
	अचिन्हित पूर्णांक  ntxq;
	अचिन्हित पूर्णांक  nrxq;
	काष्ठा completion cbc_aes_aio_करोne;
	काष्ठा __crypto_ctx crypto_ctx[];
पूर्ण;

काष्ठा chcr_hctx_per_wr अणु
	काष्ठा scatterlist *srcsg;
	काष्ठा sk_buff *skb;
	dma_addr_t dma_addr;
	u32 dma_len;
	अचिन्हित पूर्णांक src_ofst;
	अचिन्हित पूर्णांक processed;
	u32 result;
	u8 is_sg_map;
	u8 imm;
	/*Final callback called. Driver cannot rely on nbytes to decide
	 * final call
	 */
	u8 isfinal;
पूर्ण;

काष्ठा chcr_ahash_req_ctx अणु
	काष्ठा chcr_hctx_per_wr hctx_wr;
	u8 *reqbfr;
	u8 *skbfr;
	/* SKB which is being sent to the hardware क्रम processing */
	u64 data_len;  /* Data len till समय */
	u16 txqidx;
	u16 rxqidx;
	u8 reqlen;
	u8 partial_hash[CHCR_HASH_MAX_DIGEST_SIZE];
	u8 bfr1[CHCR_HASH_MAX_BLOCK_SIZE_128];
	u8 bfr2[CHCR_HASH_MAX_BLOCK_SIZE_128];
पूर्ण;

काष्ठा chcr_skcipher_req_ctx अणु
	काष्ठा sk_buff *skb;
	काष्ठा scatterlist *dstsg;
	अचिन्हित पूर्णांक processed;
	अचिन्हित पूर्णांक last_req_len;
	अचिन्हित पूर्णांक partial_req;
	काष्ठा scatterlist *srcsg;
	अचिन्हित पूर्णांक src_ofst;
	अचिन्हित पूर्णांक dst_ofst;
	अचिन्हित पूर्णांक op;
	u16 imm;
	u8 iv[CHCR_MAX_CRYPTO_IV_LEN];
	u8 init_iv[CHCR_MAX_CRYPTO_IV_LEN];
	u16 txqidx;
	u16 rxqidx;
	काष्ठा skcipher_request fallback_req;	// keep at the end
पूर्ण;

काष्ठा chcr_alg_ढाँचा अणु
	u32 type;
	u32 is_रेजिस्टरed;
	जोड़ अणु
		काष्ठा skcipher_alg skcipher;
		काष्ठा ahash_alg hash;
		काष्ठा aead_alg aead;
	पूर्ण alg;
पूर्ण;

प्रकार काष्ठा sk_buff *(*create_wr_t)(काष्ठा aead_request *req,
				       अचिन्हित लघु qid,
				       पूर्णांक size);

व्योम chcr_verअगरy_tag(काष्ठा aead_request *req, u8 *input, पूर्णांक *err);
पूर्णांक chcr_aead_dma_map(काष्ठा device *dev, काष्ठा aead_request *req,
		      अचिन्हित लघु op_type);
व्योम chcr_aead_dma_unmap(काष्ठा device *dev, काष्ठा aead_request *req,
			 अचिन्हित लघु op_type);
व्योम chcr_add_aead_dst_ent(काष्ठा aead_request *req,
			   काष्ठा cpl_rx_phys_dsgl *phys_cpl,
			   अचिन्हित लघु qid);
व्योम chcr_add_aead_src_ent(काष्ठा aead_request *req, काष्ठा ulptx_sgl *ulptx);
व्योम chcr_add_cipher_src_ent(काष्ठा skcipher_request *req,
			     व्योम *ulptx,
			     काष्ठा  cipher_wr_param *wrparam);
पूर्णांक chcr_cipher_dma_map(काष्ठा device *dev, काष्ठा skcipher_request *req);
व्योम chcr_cipher_dma_unmap(काष्ठा device *dev, काष्ठा skcipher_request *req);
व्योम chcr_add_cipher_dst_ent(काष्ठा skcipher_request *req,
			     काष्ठा cpl_rx_phys_dsgl *phys_cpl,
			     काष्ठा  cipher_wr_param *wrparam,
			     अचिन्हित लघु qid);
पूर्णांक sg_nents_len_skip(काष्ठा scatterlist *sg, u64 len, u64 skip);
व्योम chcr_add_hash_src_ent(काष्ठा ahash_request *req, काष्ठा ulptx_sgl *ulptx,
			   काष्ठा hash_wr_param *param);
पूर्णांक chcr_hash_dma_map(काष्ठा device *dev, काष्ठा ahash_request *req);
व्योम chcr_hash_dma_unmap(काष्ठा device *dev, काष्ठा ahash_request *req);
व्योम chcr_aead_common_निकास(काष्ठा aead_request *req);
#पूर्ण_अगर /* __CHCR_CRYPTO_H__ */
