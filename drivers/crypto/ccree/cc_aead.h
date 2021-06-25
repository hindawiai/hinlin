<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2012-2019 ARM Limited (or its affiliates). */

/* \पile cc_aead.h
 * ARM CryptoCell AEAD Crypto API
 */

#अगर_अघोषित __CC_AEAD_H__
#घोषणा __CC_AEAD_H__

#समावेश <linux/kernel.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/ctr.h>

/* mac_cmp - HW ग_लिखोs 8 B but all bytes hold the same value */
#घोषणा ICV_CMP_SIZE 8
#घोषणा CCM_CONFIG_BUF_SIZE (AES_BLOCK_SIZE * 3)
#घोषणा MAX_MAC_SIZE SHA256_DIGEST_SIZE

/* defines क्रम AES GCM configuration buffer */
#घोषणा GCM_BLOCK_LEN_SIZE 8

#घोषणा GCM_BLOCK_RFC4_IV_OFFSET	4
#घोषणा GCM_BLOCK_RFC4_IV_SIZE		8  /* IV size क्रम rfc's */
#घोषणा GCM_BLOCK_RFC4_NONCE_OFFSET	0
#घोषणा GCM_BLOCK_RFC4_NONCE_SIZE	4

/* Offsets पूर्णांकo AES CCM configuration buffer */
#घोषणा CCM_B0_OFFSET 0
#घोषणा CCM_A0_OFFSET 16
#घोषणा CCM_CTR_COUNT_0_OFFSET 32
/* CCM B0 and CTR_COUNT स्थिरants. */
#घोषणा CCM_BLOCK_NONCE_OFFSET 1  /* Nonce offset inside B0 and CTR_COUNT */
#घोषणा CCM_BLOCK_NONCE_SIZE   3  /* Nonce size inside B0 and CTR_COUNT */
#घोषणा CCM_BLOCK_IV_OFFSET    4  /* IV offset inside B0 and CTR_COUNT */
#घोषणा CCM_BLOCK_IV_SIZE      8  /* IV size inside B0 and CTR_COUNT */

क्रमागत aead_ccm_header_size अणु
	ccm_header_size_null = -1,
	ccm_header_size_zero = 0,
	ccm_header_size_2 = 2,
	ccm_header_size_6 = 6,
	ccm_header_size_max = S32_MAX
पूर्ण;

काष्ठा aead_req_ctx अणु
	/* Allocate cache line although only 4 bytes are needed to
	 *  assure next field falls @ cache line
	 *  Used क्रम both: digest HW compare and CCM/GCM MAC value
	 */
	u8 mac_buf[MAX_MAC_SIZE] ____cacheline_aligned;
	u8 ctr_iv[AES_BLOCK_SIZE] ____cacheline_aligned;

	//used in gcm
	u8 gcm_iv_inc1[AES_BLOCK_SIZE] ____cacheline_aligned;
	u8 gcm_iv_inc2[AES_BLOCK_SIZE] ____cacheline_aligned;
	u8 hkey[AES_BLOCK_SIZE] ____cacheline_aligned;
	काष्ठा अणु
		u8 len_a[GCM_BLOCK_LEN_SIZE] ____cacheline_aligned;
		u8 len_c[GCM_BLOCK_LEN_SIZE];
	पूर्ण gcm_len_block;

	u8 ccm_config[CCM_CONFIG_BUF_SIZE] ____cacheline_aligned;
	/* HW actual size input */
	अचिन्हित पूर्णांक hw_iv_size ____cacheline_aligned;
	/* used to prevent cache coherence problem */
	u8 backup_mac[MAX_MAC_SIZE];
	u8 *backup_iv; /* store orig iv */
	u32 assoclen; /* size of AAD buffer to authenticate */
	dma_addr_t mac_buf_dma_addr; /* पूर्णांकernal ICV DMA buffer */
	/* buffer क्रम पूर्णांकernal ccm configurations */
	dma_addr_t ccm_iv0_dma_addr;
	dma_addr_t icv_dma_addr; /* Phys. address of ICV */

	//used in gcm
	/* buffer क्रम पूर्णांकernal gcm configurations */
	dma_addr_t gcm_iv_inc1_dma_addr;
	/* buffer क्रम पूर्णांकernal gcm configurations */
	dma_addr_t gcm_iv_inc2_dma_addr;
	dma_addr_t hkey_dma_addr; /* Phys. address of hkey */
	dma_addr_t gcm_block_len_dma_addr; /* Phys. address of gcm block len */

	u8 *icv_virt_addr; /* Virt. address of ICV */
	काष्ठा async_gen_req_ctx gen_ctx;
	काष्ठा cc_mlli assoc;
	काष्ठा cc_mlli src;
	काष्ठा cc_mlli dst;
	काष्ठा scatterlist *src_sgl;
	काष्ठा scatterlist *dst_sgl;
	अचिन्हित पूर्णांक src_offset;
	अचिन्हित पूर्णांक dst_offset;
	क्रमागत cc_req_dma_buf_type assoc_buff_type;
	क्रमागत cc_req_dma_buf_type data_buff_type;
	काष्ठा mlli_params mlli_params;
	अचिन्हित पूर्णांक cryptlen;
	काष्ठा scatterlist ccm_adata_sg;
	क्रमागत aead_ccm_header_size ccm_hdr_size;
	अचिन्हित पूर्णांक req_authsize;
	क्रमागत drv_cipher_mode cipher_mode;
	bool is_icv_fragmented;
	bool is_single_pass;
	bool plaपूर्णांकext_authenticate_only; //क्रम gcm_rfc4543
पूर्ण;

पूर्णांक cc_aead_alloc(काष्ठा cc_drvdata *drvdata);
पूर्णांक cc_aead_मुक्त(काष्ठा cc_drvdata *drvdata);

#पूर्ण_अगर /*__CC_AEAD_H__*/
