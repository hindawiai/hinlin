<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2012-2019 ARM Limited (or its affiliates). */

/* \पile cc_hash.h
 * ARM CryptoCell Hash Crypto API
 */

#अगर_अघोषित __CC_HASH_H__
#घोषणा __CC_HASH_H__

#समावेश "cc_buffer_mgr.h"

#घोषणा HMAC_IPAD_CONST	0x36363636
#घोषणा HMAC_OPAD_CONST	0x5C5C5C5C
#घोषणा HASH_LEN_SIZE_712 16
#घोषणा HASH_LEN_SIZE_630 8
#घोषणा HASH_MAX_LEN_SIZE HASH_LEN_SIZE_712
#घोषणा CC_MAX_HASH_DIGEST_SIZE	SHA512_DIGEST_SIZE
#घोषणा CC_MAX_HASH_BLCK_SIZE SHA512_BLOCK_SIZE

#घोषणा XCBC_MAC_K1_OFFSET 0
#घोषणा XCBC_MAC_K2_OFFSET 16
#घोषणा XCBC_MAC_K3_OFFSET 32

#घोषणा CC_EXPORT_MAGIC 0xC2EE1070U

/* this काष्ठा was taken from drivers/crypto/nx/nx-aes-xcbc.c and it is used
 * क्रम xcbc/cmac statesize
 */
काष्ठा aeshash_state अणु
	u8 state[AES_BLOCK_SIZE];
	अचिन्हित पूर्णांक count;
	u8 buffer[AES_BLOCK_SIZE];
पूर्ण;

/* ahash state */
काष्ठा ahash_req_ctx अणु
	u8 buffers[2][CC_MAX_HASH_BLCK_SIZE] ____cacheline_aligned;
	u8 digest_result_buff[CC_MAX_HASH_DIGEST_SIZE] ____cacheline_aligned;
	u8 digest_buff[CC_MAX_HASH_DIGEST_SIZE] ____cacheline_aligned;
	u8 opad_digest_buff[CC_MAX_HASH_DIGEST_SIZE] ____cacheline_aligned;
	u8 digest_bytes_len[HASH_MAX_LEN_SIZE] ____cacheline_aligned;
	काष्ठा async_gen_req_ctx gen_ctx ____cacheline_aligned;
	क्रमागत cc_req_dma_buf_type data_dma_buf_type;
	dma_addr_t opad_digest_dma_addr;
	dma_addr_t digest_buff_dma_addr;
	dma_addr_t digest_bytes_len_dma_addr;
	dma_addr_t digest_result_dma_addr;
	u32 buf_cnt[2];
	u32 buff_index;
	u32 xcbc_count; /* count xcbc update operatations */
	काष्ठा scatterlist buff_sg[2];
	काष्ठा scatterlist *curr_sg;
	u32 in_nents;
	u32 mlli_nents;
	काष्ठा mlli_params mlli_params;
पूर्ण;

अटल अंतरभूत u32 *cc_hash_buf_cnt(काष्ठा ahash_req_ctx *state)
अणु
	वापस &state->buf_cnt[state->buff_index];
पूर्ण

अटल अंतरभूत u8 *cc_hash_buf(काष्ठा ahash_req_ctx *state)
अणु
	वापस state->buffers[state->buff_index];
पूर्ण

अटल अंतरभूत u32 *cc_next_buf_cnt(काष्ठा ahash_req_ctx *state)
अणु
	वापस &state->buf_cnt[state->buff_index ^ 1];
पूर्ण

अटल अंतरभूत u8 *cc_next_buf(काष्ठा ahash_req_ctx *state)
अणु
	वापस state->buffers[state->buff_index ^ 1];
पूर्ण

पूर्णांक cc_hash_alloc(काष्ठा cc_drvdata *drvdata);
पूर्णांक cc_init_hash_sram(काष्ठा cc_drvdata *drvdata);
पूर्णांक cc_hash_मुक्त(काष्ठा cc_drvdata *drvdata);

/**
 * cc_digest_len_addr() - Gets the initial digest length
 *
 * @drvdata: Associated device driver context
 * @mode: The Hash mode. Supported modes: MD5/SHA1/SHA224/SHA256/SHA384/SHA512
 *
 * Return:
 * Returns the address of the initial digest length in SRAM
 */
u32 cc_digest_len_addr(व्योम *drvdata, u32 mode);

/**
 * cc_larval_digest_addr() - Gets the address of the initial digest in SRAM
 * according to the given hash mode
 *
 * @drvdata: Associated device driver context
 * @mode: The Hash mode. Supported modes: MD5/SHA1/SHA224/SHA256/SHA384/SHA512
 *
 * Return:
 * The address of the initial digest in SRAM
 */
u32 cc_larval_digest_addr(व्योम *drvdata, u32 mode);

#पूर्ण_अगर /*__CC_HASH_H__*/
