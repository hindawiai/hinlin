<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MARVELL_CESA_H__
#घोषणा __MARVELL_CESA_H__

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>

#समावेश <linux/dma-direction.h>
#समावेश <linux/dmapool.h>

#घोषणा CESA_ENGINE_OFF(i)			(((i) * 0x2000))

#घोषणा CESA_TDMA_BYTE_CNT			0x800
#घोषणा CESA_TDMA_SRC_ADDR			0x810
#घोषणा CESA_TDMA_DST_ADDR			0x820
#घोषणा CESA_TDMA_NEXT_ADDR			0x830

#घोषणा CESA_TDMA_CONTROL			0x840
#घोषणा CESA_TDMA_DST_BURST			GENMASK(2, 0)
#घोषणा CESA_TDMA_DST_BURST_32B			3
#घोषणा CESA_TDMA_DST_BURST_128B		4
#घोषणा CESA_TDMA_OUT_RD_EN			BIT(4)
#घोषणा CESA_TDMA_SRC_BURST			GENMASK(8, 6)
#घोषणा CESA_TDMA_SRC_BURST_32B			(3 << 6)
#घोषणा CESA_TDMA_SRC_BURST_128B		(4 << 6)
#घोषणा CESA_TDMA_CHAIN				BIT(9)
#घोषणा CESA_TDMA_BYTE_SWAP			BIT(11)
#घोषणा CESA_TDMA_NO_BYTE_SWAP			BIT(11)
#घोषणा CESA_TDMA_EN				BIT(12)
#घोषणा CESA_TDMA_FETCH_ND			BIT(13)
#घोषणा CESA_TDMA_ACT				BIT(14)

#घोषणा CESA_TDMA_CUR				0x870
#घोषणा CESA_TDMA_ERROR_CAUSE			0x8c8
#घोषणा CESA_TDMA_ERROR_MSK			0x8cc

#घोषणा CESA_TDMA_WINDOW_BASE(x)		(((x) * 0x8) + 0xa00)
#घोषणा CESA_TDMA_WINDOW_CTRL(x)		(((x) * 0x8) + 0xa04)

#घोषणा CESA_IVDIG(x)				(0xdd00 + ((x) * 4) +	\
						 (((x) < 5) ? 0 : 0x14))

#घोषणा CESA_SA_CMD				0xde00
#घोषणा CESA_SA_CMD_EN_CESA_SA_ACCL0		BIT(0)
#घोषणा CESA_SA_CMD_EN_CESA_SA_ACCL1		BIT(1)
#घोषणा CESA_SA_CMD_DISABLE_SEC			BIT(2)

#घोषणा CESA_SA_DESC_P0				0xde04

#घोषणा CESA_SA_DESC_P1				0xde14

#घोषणा CESA_SA_CFG				0xde08
#घोषणा CESA_SA_CFG_STOP_DIG_ERR		GENMASK(1, 0)
#घोषणा CESA_SA_CFG_DIG_ERR_CONT		0
#घोषणा CESA_SA_CFG_DIG_ERR_SKIP		1
#घोषणा CESA_SA_CFG_DIG_ERR_STOP		3
#घोषणा CESA_SA_CFG_CH0_W_IDMA			BIT(7)
#घोषणा CESA_SA_CFG_CH1_W_IDMA			BIT(8)
#घोषणा CESA_SA_CFG_ACT_CH0_IDMA		BIT(9)
#घोषणा CESA_SA_CFG_ACT_CH1_IDMA		BIT(10)
#घोषणा CESA_SA_CFG_MULTI_PKT			BIT(11)
#घोषणा CESA_SA_CFG_PARA_DIS			BIT(13)

#घोषणा CESA_SA_ACCEL_STATUS			0xde0c
#घोषणा CESA_SA_ST_ACT_0			BIT(0)
#घोषणा CESA_SA_ST_ACT_1			BIT(1)

/*
 * CESA_SA_FPGA_INT_STATUS looks like a FPGA leftover and is करोcumented only
 * in Errata 4.12. It looks like that it was part of an IRQ-controller in FPGA
 * and someone क्रमgot to हटाओ  it जबतक चयनing to the core and moving to
 * CESA_SA_INT_STATUS.
 */
#घोषणा CESA_SA_FPGA_INT_STATUS			0xdd68
#घोषणा CESA_SA_INT_STATUS			0xde20
#घोषणा CESA_SA_INT_AUTH_DONE			BIT(0)
#घोषणा CESA_SA_INT_DES_E_DONE			BIT(1)
#घोषणा CESA_SA_INT_AES_E_DONE			BIT(2)
#घोषणा CESA_SA_INT_AES_D_DONE			BIT(3)
#घोषणा CESA_SA_INT_ENC_DONE			BIT(4)
#घोषणा CESA_SA_INT_ACCEL0_DONE			BIT(5)
#घोषणा CESA_SA_INT_ACCEL1_DONE			BIT(6)
#घोषणा CESA_SA_INT_ACC0_IDMA_DONE		BIT(7)
#घोषणा CESA_SA_INT_ACC1_IDMA_DONE		BIT(8)
#घोषणा CESA_SA_INT_IDMA_DONE			BIT(9)
#घोषणा CESA_SA_INT_IDMA_OWN_ERR		BIT(10)

#घोषणा CESA_SA_INT_MSK				0xde24

#घोषणा CESA_SA_DESC_CFG_OP_MAC_ONLY		0
#घोषणा CESA_SA_DESC_CFG_OP_CRYPT_ONLY		1
#घोषणा CESA_SA_DESC_CFG_OP_MAC_CRYPT		2
#घोषणा CESA_SA_DESC_CFG_OP_CRYPT_MAC		3
#घोषणा CESA_SA_DESC_CFG_OP_MSK			GENMASK(1, 0)
#घोषणा CESA_SA_DESC_CFG_MACM_SHA256		(1 << 4)
#घोषणा CESA_SA_DESC_CFG_MACM_HMAC_SHA256	(3 << 4)
#घोषणा CESA_SA_DESC_CFG_MACM_MD5		(4 << 4)
#घोषणा CESA_SA_DESC_CFG_MACM_SHA1		(5 << 4)
#घोषणा CESA_SA_DESC_CFG_MACM_HMAC_MD5		(6 << 4)
#घोषणा CESA_SA_DESC_CFG_MACM_HMAC_SHA1		(7 << 4)
#घोषणा CESA_SA_DESC_CFG_MACM_MSK		GENMASK(6, 4)
#घोषणा CESA_SA_DESC_CFG_CRYPTM_DES		(1 << 8)
#घोषणा CESA_SA_DESC_CFG_CRYPTM_3DES		(2 << 8)
#घोषणा CESA_SA_DESC_CFG_CRYPTM_AES		(3 << 8)
#घोषणा CESA_SA_DESC_CFG_CRYPTM_MSK		GENMASK(9, 8)
#घोषणा CESA_SA_DESC_CFG_सूची_ENC		(0 << 12)
#घोषणा CESA_SA_DESC_CFG_सूची_DEC		(1 << 12)
#घोषणा CESA_SA_DESC_CFG_CRYPTCM_ECB		(0 << 16)
#घोषणा CESA_SA_DESC_CFG_CRYPTCM_CBC		(1 << 16)
#घोषणा CESA_SA_DESC_CFG_CRYPTCM_MSK		BIT(16)
#घोषणा CESA_SA_DESC_CFG_3DES_EEE		(0 << 20)
#घोषणा CESA_SA_DESC_CFG_3DES_EDE		(1 << 20)
#घोषणा CESA_SA_DESC_CFG_AES_LEN_128		(0 << 24)
#घोषणा CESA_SA_DESC_CFG_AES_LEN_192		(1 << 24)
#घोषणा CESA_SA_DESC_CFG_AES_LEN_256		(2 << 24)
#घोषणा CESA_SA_DESC_CFG_AES_LEN_MSK		GENMASK(25, 24)
#घोषणा CESA_SA_DESC_CFG_NOT_FRAG		(0 << 30)
#घोषणा CESA_SA_DESC_CFG_FIRST_FRAG		(1 << 30)
#घोषणा CESA_SA_DESC_CFG_LAST_FRAG		(2 << 30)
#घोषणा CESA_SA_DESC_CFG_MID_FRAG		(3 << 30)
#घोषणा CESA_SA_DESC_CFG_FRAG_MSK		GENMASK(31, 30)

/*
 * /-----------\ 0
 * | ACCEL CFG |	4 * 8
 * |-----------| 0x20
 * | CRYPT KEY |	8 * 4
 * |-----------| 0x40
 * |  IV   IN  |	4 * 4
 * |-----------| 0x40 (inplace)
 * |  IV BUF   |	4 * 4
 * |-----------| 0x80
 * |  DATA IN  |	16 * x (max ->max_req_size)
 * |-----------| 0x80 (inplace operation)
 * |  DATA OUT |	16 * x (max ->max_req_size)
 * \-----------/ SRAM size
 */

/*
 * Hashing memory map:
 * /-----------\ 0
 * | ACCEL CFG |        4 * 8
 * |-----------| 0x20
 * | Inner IV  |        8 * 4
 * |-----------| 0x40
 * | Outer IV  |        8 * 4
 * |-----------| 0x60
 * | Output BUF|        8 * 4
 * |-----------| 0x80
 * |  DATA IN  |        64 * x (max ->max_req_size)
 * \-----------/ SRAM size
 */

#घोषणा CESA_SA_CFG_SRAM_OFFSET			0x00
#घोषणा CESA_SA_DATA_SRAM_OFFSET		0x80

#घोषणा CESA_SA_CRYPT_KEY_SRAM_OFFSET		0x20
#घोषणा CESA_SA_CRYPT_IV_SRAM_OFFSET		0x40

#घोषणा CESA_SA_MAC_IIV_SRAM_OFFSET		0x20
#घोषणा CESA_SA_MAC_OIV_SRAM_OFFSET		0x40
#घोषणा CESA_SA_MAC_DIG_SRAM_OFFSET		0x60

#घोषणा CESA_SA_DESC_CRYPT_DATA(offset)					\
	cpu_to_le32((CESA_SA_DATA_SRAM_OFFSET + (offset)) |		\
		    ((CESA_SA_DATA_SRAM_OFFSET + (offset)) << 16))

#घोषणा CESA_SA_DESC_CRYPT_IV(offset)					\
	cpu_to_le32((CESA_SA_CRYPT_IV_SRAM_OFFSET + (offset)) |	\
		    ((CESA_SA_CRYPT_IV_SRAM_OFFSET + (offset)) << 16))

#घोषणा CESA_SA_DESC_CRYPT_KEY(offset)					\
	cpu_to_le32(CESA_SA_CRYPT_KEY_SRAM_OFFSET + (offset))

#घोषणा CESA_SA_DESC_MAC_DATA(offset)					\
	cpu_to_le32(CESA_SA_DATA_SRAM_OFFSET + (offset))
#घोषणा CESA_SA_DESC_MAC_DATA_MSK		cpu_to_le32(GENMASK(15, 0))

#घोषणा CESA_SA_DESC_MAC_TOTAL_LEN(total_len)	cpu_to_le32((total_len) << 16)
#घोषणा CESA_SA_DESC_MAC_TOTAL_LEN_MSK		cpu_to_le32(GENMASK(31, 16))

#घोषणा CESA_SA_DESC_MAC_SRC_TOTAL_LEN_MAX	0xffff

#घोषणा CESA_SA_DESC_MAC_DIGEST(offset)					\
	cpu_to_le32(CESA_SA_MAC_DIG_SRAM_OFFSET + (offset))
#घोषणा CESA_SA_DESC_MAC_DIGEST_MSK		cpu_to_le32(GENMASK(15, 0))

#घोषणा CESA_SA_DESC_MAC_FRAG_LEN(frag_len)	cpu_to_le32((frag_len) << 16)
#घोषणा CESA_SA_DESC_MAC_FRAG_LEN_MSK		cpu_to_le32(GENMASK(31, 16))

#घोषणा CESA_SA_DESC_MAC_IV(offset)					\
	cpu_to_le32((CESA_SA_MAC_IIV_SRAM_OFFSET + (offset)) |		\
		    ((CESA_SA_MAC_OIV_SRAM_OFFSET + (offset)) << 16))

#घोषणा CESA_SA_SRAM_SIZE			2048
#घोषणा CESA_SA_SRAM_PAYLOAD_SIZE		(cesa_dev->sram_size - \
						 CESA_SA_DATA_SRAM_OFFSET)

#घोषणा CESA_SA_DEFAULT_SRAM_SIZE		2048
#घोषणा CESA_SA_MIN_SRAM_SIZE			1024

#घोषणा CESA_SA_SRAM_MSK			(2048 - 1)

#घोषणा CESA_MAX_HASH_BLOCK_SIZE		64
#घोषणा CESA_HASH_BLOCK_SIZE_MSK		(CESA_MAX_HASH_BLOCK_SIZE - 1)

/**
 * काष्ठा mv_cesa_sec_accel_desc - security accelerator descriptor
 * @config:	engine config
 * @enc_p:	input and output data poपूर्णांकers क्रम a cipher operation
 * @enc_len:	cipher operation length
 * @enc_key_p:	cipher key poपूर्णांकer
 * @enc_iv:	cipher IV poपूर्णांकers
 * @mac_src_p:	input poपूर्णांकer and total hash length
 * @mac_digest:	digest poपूर्णांकer and hash operation length
 * @mac_iv:	hmac IV poपूर्णांकers
 *
 * Structure passed to the CESA engine to describe the crypto operation
 * to be executed.
 */
काष्ठा mv_cesa_sec_accel_desc अणु
	__le32 config;
	__le32 enc_p;
	__le32 enc_len;
	__le32 enc_key_p;
	__le32 enc_iv;
	__le32 mac_src_p;
	__le32 mac_digest;
	__le32 mac_iv;
पूर्ण;

/**
 * काष्ठा mv_cesa_skcipher_op_ctx - cipher operation context
 * @key:	cipher key
 * @iv:		cipher IV
 *
 * Context associated to a cipher operation.
 */
काष्ठा mv_cesa_skcipher_op_ctx अणु
	__le32 key[8];
	u32 iv[4];
पूर्ण;

/**
 * काष्ठा mv_cesa_hash_op_ctx - hash or hmac operation context
 * @key:	cipher key
 * @iv:		cipher IV
 *
 * Context associated to an hash or hmac operation.
 */
काष्ठा mv_cesa_hash_op_ctx अणु
	u32 iv[16];
	__le32 hash[8];
पूर्ण;

/**
 * काष्ठा mv_cesa_op_ctx - crypto operation context
 * @desc:	CESA descriptor
 * @ctx:	context associated to the crypto operation
 *
 * Context associated to a crypto operation.
 */
काष्ठा mv_cesa_op_ctx अणु
	काष्ठा mv_cesa_sec_accel_desc desc;
	जोड़ अणु
		काष्ठा mv_cesa_skcipher_op_ctx skcipher;
		काष्ठा mv_cesa_hash_op_ctx hash;
	पूर्ण ctx;
पूर्ण;

/* TDMA descriptor flags */
#घोषणा CESA_TDMA_DST_IN_SRAM			BIT(31)
#घोषणा CESA_TDMA_SRC_IN_SRAM			BIT(30)
#घोषणा CESA_TDMA_END_OF_REQ			BIT(29)
#घोषणा CESA_TDMA_BREAK_CHAIN			BIT(28)
#घोषणा CESA_TDMA_SET_STATE			BIT(27)
#घोषणा CESA_TDMA_TYPE_MSK			GENMASK(26, 0)
#घोषणा CESA_TDMA_DUMMY				0
#घोषणा CESA_TDMA_DATA				1
#घोषणा CESA_TDMA_OP				2
#घोषणा CESA_TDMA_RESULT			3

/**
 * काष्ठा mv_cesa_tdma_desc - TDMA descriptor
 * @byte_cnt:	number of bytes to transfer
 * @src:	DMA address of the source
 * @dst:	DMA address of the destination
 * @next_dma:	DMA address of the next TDMA descriptor
 * @cur_dma:	DMA address of this TDMA descriptor
 * @next:	poपूर्णांकer to the next TDMA descriptor
 * @op:		CESA operation attached to this TDMA descriptor
 * @data:	raw data attached to this TDMA descriptor
 * @flags:	flags describing the TDMA transfer. See the
 *		"TDMA descriptor flags" section above
 *
 * TDMA descriptor used to create a transfer chain describing a crypto
 * operation.
 */
काष्ठा mv_cesa_tdma_desc अणु
	__le32 byte_cnt;
	जोड़ अणु
		__le32 src;
		u32 src_dma;
	पूर्ण;
	जोड़ अणु
		__le32 dst;
		u32 dst_dma;
	पूर्ण;
	__le32 next_dma;

	/* Software state */
	dma_addr_t cur_dma;
	काष्ठा mv_cesa_tdma_desc *next;
	जोड़ अणु
		काष्ठा mv_cesa_op_ctx *op;
		व्योम *data;
	पूर्ण;
	u32 flags;
पूर्ण;

/**
 * काष्ठा mv_cesa_sg_dma_iter - scatter-gather iterator
 * @dir:	transfer direction
 * @sg:		scatter list
 * @offset:	current position in the scatter list
 * @op_offset:	current position in the crypto operation
 *
 * Iterator used to iterate over a scatterlist जबतक creating a TDMA chain क्रम
 * a crypto operation.
 */
काष्ठा mv_cesa_sg_dma_iter अणु
	क्रमागत dma_data_direction dir;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक op_offset;
पूर्ण;

/**
 * काष्ठा mv_cesa_dma_iter - crypto operation iterator
 * @len:	the crypto operation length
 * @offset:	current position in the crypto operation
 * @op_len:	sub-operation length (the crypto engine can only act on 2kb
 *		chunks)
 *
 * Iterator used to create a TDMA chain क्रम a given crypto operation.
 */
काष्ठा mv_cesa_dma_iter अणु
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक op_len;
पूर्ण;

/**
 * काष्ठा mv_cesa_tdma_chain - TDMA chain
 * @first:	first entry in the TDMA chain
 * @last:	last entry in the TDMA chain
 *
 * Stores a TDMA chain क्रम a specअगरic crypto operation.
 */
काष्ठा mv_cesa_tdma_chain अणु
	काष्ठा mv_cesa_tdma_desc *first;
	काष्ठा mv_cesa_tdma_desc *last;
पूर्ण;

काष्ठा mv_cesa_engine;

/**
 * काष्ठा mv_cesa_caps - CESA device capabilities
 * @engines:		number of engines
 * @has_tdma:		whether this device has a TDMA block
 * @cipher_algs:	supported cipher algorithms
 * @ncipher_algs:	number of supported cipher algorithms
 * @ahash_algs:		supported hash algorithms
 * @nahash_algs:	number of supported hash algorithms
 *
 * Structure used to describe CESA device capabilities.
 */
काष्ठा mv_cesa_caps अणु
	पूर्णांक nengines;
	bool has_tdma;
	काष्ठा skcipher_alg **cipher_algs;
	पूर्णांक ncipher_algs;
	काष्ठा ahash_alg **ahash_algs;
	पूर्णांक nahash_algs;
पूर्ण;

/**
 * काष्ठा mv_cesa_dev_dma - DMA pools
 * @tdma_desc_pool:	TDMA desc pool
 * @op_pool:		crypto operation pool
 * @cache_pool:		data cache pool (used by hash implementation when the
 *			hash request is smaller than the hash block size)
 * @padding_pool:	padding pool (used by hash implementation when hardware
 *			padding cannot be used)
 *
 * Structure containing the dअगरferent DMA pools used by this driver.
 */
काष्ठा mv_cesa_dev_dma अणु
	काष्ठा dma_pool *tdma_desc_pool;
	काष्ठा dma_pool *op_pool;
	काष्ठा dma_pool *cache_pool;
	काष्ठा dma_pool *padding_pool;
पूर्ण;

/**
 * काष्ठा mv_cesa_dev - CESA device
 * @caps:	device capabilities
 * @regs:	device रेजिस्टरs
 * @sram_size:	usable SRAM size
 * @lock:	device lock
 * @engines:	array of engines
 * @dma:	dma pools
 *
 * Structure storing CESA device inक्रमmation.
 */
काष्ठा mv_cesa_dev अणु
	स्थिर काष्ठा mv_cesa_caps *caps;
	व्योम __iomem *regs;
	काष्ठा device *dev;
	अचिन्हित पूर्णांक sram_size;
	spinlock_t lock;
	काष्ठा mv_cesa_engine *engines;
	काष्ठा mv_cesa_dev_dma *dma;
पूर्ण;

/**
 * काष्ठा mv_cesa_engine - CESA engine
 * @id:			engine id
 * @regs:		engine रेजिस्टरs
 * @sram:		SRAM memory region
 * @sram_pool:		SRAM memory region from pool
 * @sram_dma:		DMA address of the SRAM memory region
 * @lock:		engine lock
 * @req:		current crypto request
 * @clk:		engine clk
 * @zclk:		engine zclk
 * @max_req_len:	maximum chunk length (useful to create the TDMA chain)
 * @पूर्णांक_mask:		पूर्णांकerrupt mask cache
 * @pool:		memory pool poपूर्णांकing to the memory region reserved in
 *			SRAM
 * @queue:		fअगरo of the pending crypto requests
 * @load:		engine load counter, useful क्रम load balancing
 * @chain:		list of the current tdma descriptors being processed
 *			by this engine.
 * @complete_queue:	fअगरo of the processed requests by the engine
 *
 * Structure storing CESA engine inक्रमmation.
 */
काष्ठा mv_cesa_engine अणु
	पूर्णांक id;
	व्योम __iomem *regs;
	जोड़ अणु
		व्योम __iomem *sram;
		व्योम *sram_pool;
	पूर्ण;
	dma_addr_t sram_dma;
	spinlock_t lock;
	काष्ठा crypto_async_request *req;
	काष्ठा clk *clk;
	काष्ठा clk *zclk;
	माप_प्रकार max_req_len;
	u32 पूर्णांक_mask;
	काष्ठा gen_pool *pool;
	काष्ठा crypto_queue queue;
	atomic_t load;
	काष्ठा mv_cesa_tdma_chain chain;
	काष्ठा list_head complete_queue;
	पूर्णांक irq;
पूर्ण;

/**
 * काष्ठा mv_cesa_req_ops - CESA request operations
 * @process:	process a request chunk result (should वापस 0 अगर the
 *		operation, -EINPROGRESS अगर it needs more steps or an error
 *		code)
 * @step:	launch the crypto operation on the next chunk
 * @cleanup:	cleanup the crypto request (release associated data)
 * @complete:	complete the request, i.e copy result or context from sram when
 *		needed.
 */
काष्ठा mv_cesa_req_ops अणु
	पूर्णांक (*process)(काष्ठा crypto_async_request *req, u32 status);
	व्योम (*step)(काष्ठा crypto_async_request *req);
	व्योम (*cleanup)(काष्ठा crypto_async_request *req);
	व्योम (*complete)(काष्ठा crypto_async_request *req);
पूर्ण;

/**
 * काष्ठा mv_cesa_ctx - CESA operation context
 * @ops:	crypto operations
 *
 * Base context काष्ठाure inherited by operation specअगरic ones.
 */
काष्ठा mv_cesa_ctx अणु
	स्थिर काष्ठा mv_cesa_req_ops *ops;
पूर्ण;

/**
 * काष्ठा mv_cesa_hash_ctx - CESA hash operation context
 * @base:	base context काष्ठाure
 *
 * Hash context काष्ठाure.
 */
काष्ठा mv_cesa_hash_ctx अणु
	काष्ठा mv_cesa_ctx base;
पूर्ण;

/**
 * काष्ठा mv_cesa_hash_ctx - CESA hmac operation context
 * @base:	base context काष्ठाure
 * @iv:		initialization vectors
 *
 * HMAC context काष्ठाure.
 */
काष्ठा mv_cesa_hmac_ctx अणु
	काष्ठा mv_cesa_ctx base;
	__be32 iv[16];
पूर्ण;

/**
 * क्रमागत mv_cesa_req_type - request type definitions
 * @CESA_STD_REQ:	standard request
 * @CESA_DMA_REQ:	DMA request
 */
क्रमागत mv_cesa_req_type अणु
	CESA_STD_REQ,
	CESA_DMA_REQ,
पूर्ण;

/**
 * काष्ठा mv_cesa_req - CESA request
 * @engine:	engine associated with this request
 * @chain:	list of tdma descriptors associated  with this request
 */
काष्ठा mv_cesa_req अणु
	काष्ठा mv_cesa_engine *engine;
	काष्ठा mv_cesa_tdma_chain chain;
पूर्ण;

/**
 * काष्ठा mv_cesa_sg_std_iter - CESA scatter-gather iterator क्रम standard
 *				requests
 * @iter:	sg mapping iterator
 * @offset:	current offset in the SG entry mapped in memory
 */
काष्ठा mv_cesa_sg_std_iter अणु
	काष्ठा sg_mapping_iter iter;
	अचिन्हित पूर्णांक offset;
पूर्ण;

/**
 * काष्ठा mv_cesa_skcipher_std_req - cipher standard request
 * @op:		operation context
 * @offset:	current operation offset
 * @size:	size of the crypto operation
 */
काष्ठा mv_cesa_skcipher_std_req अणु
	काष्ठा mv_cesa_op_ctx op;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक size;
	bool skip_ctx;
पूर्ण;

/**
 * काष्ठा mv_cesa_skcipher_req - cipher request
 * @req:	type specअगरic request inक्रमmation
 * @src_nents:	number of entries in the src sg list
 * @dst_nents:	number of entries in the dest sg list
 */
काष्ठा mv_cesa_skcipher_req अणु
	काष्ठा mv_cesa_req base;
	काष्ठा mv_cesa_skcipher_std_req std;
	पूर्णांक src_nents;
	पूर्णांक dst_nents;
पूर्ण;

/**
 * काष्ठा mv_cesa_ahash_std_req - standard hash request
 * @offset:	current operation offset
 */
काष्ठा mv_cesa_ahash_std_req अणु
	अचिन्हित पूर्णांक offset;
पूर्ण;

/**
 * काष्ठा mv_cesa_ahash_dma_req - DMA hash request
 * @padding:		padding buffer
 * @padding_dma:	DMA address of the padding buffer
 * @cache_dma:		DMA address of the cache buffer
 */
काष्ठा mv_cesa_ahash_dma_req अणु
	u8 *padding;
	dma_addr_t padding_dma;
	u8 *cache;
	dma_addr_t cache_dma;
पूर्ण;

/**
 * काष्ठा mv_cesa_ahash_req - hash request
 * @req:		type specअगरic request inक्रमmation
 * @cache:		cache buffer
 * @cache_ptr:		ग_लिखो poपूर्णांकer in the cache buffer
 * @len:		hash total length
 * @src_nents:		number of entries in the scatterlist
 * @last_req:		define whether the current operation is the last one
 *			or not
 * @state:		hash state
 */
काष्ठा mv_cesa_ahash_req अणु
	काष्ठा mv_cesa_req base;
	जोड़ अणु
		काष्ठा mv_cesa_ahash_dma_req dma;
		काष्ठा mv_cesa_ahash_std_req std;
	पूर्ण req;
	काष्ठा mv_cesa_op_ctx op_पंचांगpl;
	u8 cache[CESA_MAX_HASH_BLOCK_SIZE];
	अचिन्हित पूर्णांक cache_ptr;
	u64 len;
	पूर्णांक src_nents;
	bool last_req;
	bool algo_le;
	u32 state[8];
पूर्ण;

/* CESA functions */

बाह्य काष्ठा mv_cesa_dev *cesa_dev;


अटल अंतरभूत व्योम
mv_cesa_engine_enqueue_complete_request(काष्ठा mv_cesa_engine *engine,
					काष्ठा crypto_async_request *req)
अणु
	list_add_tail(&req->list, &engine->complete_queue);
पूर्ण

अटल अंतरभूत काष्ठा crypto_async_request *
mv_cesa_engine_dequeue_complete_request(काष्ठा mv_cesa_engine *engine)
अणु
	काष्ठा crypto_async_request *req;

	req = list_first_entry_or_null(&engine->complete_queue,
				       काष्ठा crypto_async_request,
				       list);
	अगर (req)
		list_del(&req->list);

	वापस req;
पूर्ण


अटल अंतरभूत क्रमागत mv_cesa_req_type
mv_cesa_req_get_type(काष्ठा mv_cesa_req *req)
अणु
	वापस req->chain.first ? CESA_DMA_REQ : CESA_STD_REQ;
पूर्ण

अटल अंतरभूत व्योम mv_cesa_update_op_cfg(काष्ठा mv_cesa_op_ctx *op,
					 u32 cfg, u32 mask)
अणु
	op->desc.config &= cpu_to_le32(~mask);
	op->desc.config |= cpu_to_le32(cfg);
पूर्ण

अटल अंतरभूत u32 mv_cesa_get_op_cfg(स्थिर काष्ठा mv_cesa_op_ctx *op)
अणु
	वापस le32_to_cpu(op->desc.config);
पूर्ण

अटल अंतरभूत व्योम mv_cesa_set_op_cfg(काष्ठा mv_cesa_op_ctx *op, u32 cfg)
अणु
	op->desc.config = cpu_to_le32(cfg);
पूर्ण

अटल अंतरभूत व्योम mv_cesa_adjust_op(काष्ठा mv_cesa_engine *engine,
				     काष्ठा mv_cesa_op_ctx *op)
अणु
	u32 offset = engine->sram_dma & CESA_SA_SRAM_MSK;

	op->desc.enc_p = CESA_SA_DESC_CRYPT_DATA(offset);
	op->desc.enc_key_p = CESA_SA_DESC_CRYPT_KEY(offset);
	op->desc.enc_iv = CESA_SA_DESC_CRYPT_IV(offset);
	op->desc.mac_src_p &= ~CESA_SA_DESC_MAC_DATA_MSK;
	op->desc.mac_src_p |= CESA_SA_DESC_MAC_DATA(offset);
	op->desc.mac_digest &= ~CESA_SA_DESC_MAC_DIGEST_MSK;
	op->desc.mac_digest |= CESA_SA_DESC_MAC_DIGEST(offset);
	op->desc.mac_iv = CESA_SA_DESC_MAC_IV(offset);
पूर्ण

अटल अंतरभूत व्योम mv_cesa_set_crypt_op_len(काष्ठा mv_cesa_op_ctx *op, पूर्णांक len)
अणु
	op->desc.enc_len = cpu_to_le32(len);
पूर्ण

अटल अंतरभूत व्योम mv_cesa_set_mac_op_total_len(काष्ठा mv_cesa_op_ctx *op,
						पूर्णांक len)
अणु
	op->desc.mac_src_p &= ~CESA_SA_DESC_MAC_TOTAL_LEN_MSK;
	op->desc.mac_src_p |= CESA_SA_DESC_MAC_TOTAL_LEN(len);
पूर्ण

अटल अंतरभूत व्योम mv_cesa_set_mac_op_frag_len(काष्ठा mv_cesa_op_ctx *op,
					       पूर्णांक len)
अणु
	op->desc.mac_digest &= ~CESA_SA_DESC_MAC_FRAG_LEN_MSK;
	op->desc.mac_digest |= CESA_SA_DESC_MAC_FRAG_LEN(len);
पूर्ण

अटल अंतरभूत व्योम mv_cesa_set_पूर्णांक_mask(काष्ठा mv_cesa_engine *engine,
					u32 पूर्णांक_mask)
अणु
	अगर (पूर्णांक_mask == engine->पूर्णांक_mask)
		वापस;

	ग_लिखोl_relaxed(पूर्णांक_mask, engine->regs + CESA_SA_INT_MSK);
	engine->पूर्णांक_mask = पूर्णांक_mask;
पूर्ण

अटल अंतरभूत u32 mv_cesa_get_पूर्णांक_mask(काष्ठा mv_cesa_engine *engine)
अणु
	वापस engine->पूर्णांक_mask;
पूर्ण

अटल अंतरभूत bool mv_cesa_mac_op_is_first_frag(स्थिर काष्ठा mv_cesa_op_ctx *op)
अणु
	वापस (mv_cesa_get_op_cfg(op) & CESA_SA_DESC_CFG_FRAG_MSK) ==
		CESA_SA_DESC_CFG_FIRST_FRAG;
पूर्ण

पूर्णांक mv_cesa_queue_req(काष्ठा crypto_async_request *req,
		      काष्ठा mv_cesa_req *creq);

काष्ठा crypto_async_request *
mv_cesa_dequeue_req_locked(काष्ठा mv_cesa_engine *engine,
			   काष्ठा crypto_async_request **backlog);

अटल अंतरभूत काष्ठा mv_cesa_engine *mv_cesa_select_engine(पूर्णांक weight)
अणु
	पूर्णांक i;
	u32 min_load = U32_MAX;
	काष्ठा mv_cesa_engine *selected = शून्य;

	क्रम (i = 0; i < cesa_dev->caps->nengines; i++) अणु
		काष्ठा mv_cesa_engine *engine = cesa_dev->engines + i;
		u32 load = atomic_पढ़ो(&engine->load);

		अगर (load < min_load) अणु
			min_load = load;
			selected = engine;
		पूर्ण
	पूर्ण

	atomic_add(weight, &selected->load);

	वापस selected;
पूर्ण

/*
 * Helper function that indicates whether a crypto request needs to be
 * cleaned up or not after being enqueued using mv_cesa_queue_req().
 */
अटल अंतरभूत पूर्णांक mv_cesa_req_needs_cleanup(काष्ठा crypto_async_request *req,
					    पूर्णांक ret)
अणु
	/*
	 * The queue still had some space, the request was queued
	 * normally, so there's no need to clean it up.
	 */
	अगर (ret == -EINPROGRESS)
		वापस false;

	/*
	 * The queue had not space left, but since the request is
	 * flagged with CRYPTO_TFM_REQ_MAY_BACKLOG, it was added to
	 * the backlog and will be processed later. There's no need to
	 * clean it up.
	 */
	अगर (ret == -EBUSY)
		वापस false;

	/* Request wasn't queued, we need to clean it up */
	वापस true;
पूर्ण

/* TDMA functions */

अटल अंतरभूत व्योम mv_cesa_req_dma_iter_init(काष्ठा mv_cesa_dma_iter *iter,
					     अचिन्हित पूर्णांक len)
अणु
	iter->len = len;
	iter->op_len = min(len, CESA_SA_SRAM_PAYLOAD_SIZE);
	iter->offset = 0;
पूर्ण

अटल अंतरभूत व्योम mv_cesa_sg_dma_iter_init(काष्ठा mv_cesa_sg_dma_iter *iter,
					    काष्ठा scatterlist *sg,
					    क्रमागत dma_data_direction dir)
अणु
	iter->op_offset = 0;
	iter->offset = 0;
	iter->sg = sg;
	iter->dir = dir;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
mv_cesa_req_dma_iter_transfer_len(काष्ठा mv_cesa_dma_iter *iter,
				  काष्ठा mv_cesa_sg_dma_iter *sgiter)
अणु
	वापस min(iter->op_len - sgiter->op_offset,
		   sg_dma_len(sgiter->sg) - sgiter->offset);
पूर्ण

bool mv_cesa_req_dma_iter_next_transfer(काष्ठा mv_cesa_dma_iter *chain,
					काष्ठा mv_cesa_sg_dma_iter *sgiter,
					अचिन्हित पूर्णांक len);

अटल अंतरभूत bool mv_cesa_req_dma_iter_next_op(काष्ठा mv_cesa_dma_iter *iter)
अणु
	iter->offset += iter->op_len;
	iter->op_len = min(iter->len - iter->offset,
			   CESA_SA_SRAM_PAYLOAD_SIZE);

	वापस iter->op_len;
पूर्ण

व्योम mv_cesa_dma_step(काष्ठा mv_cesa_req *dreq);

अटल अंतरभूत पूर्णांक mv_cesa_dma_process(काष्ठा mv_cesa_req *dreq,
				      u32 status)
अणु
	अगर (!(status & CESA_SA_INT_ACC0_IDMA_DONE))
		वापस -EINPROGRESS;

	अगर (status & CESA_SA_INT_IDMA_OWN_ERR)
		वापस -EINVAL;

	वापस 0;
पूर्ण

व्योम mv_cesa_dma_prepare(काष्ठा mv_cesa_req *dreq,
			 काष्ठा mv_cesa_engine *engine);
व्योम mv_cesa_dma_cleanup(काष्ठा mv_cesa_req *dreq);
व्योम mv_cesa_tdma_chain(काष्ठा mv_cesa_engine *engine,
			काष्ठा mv_cesa_req *dreq);
पूर्णांक mv_cesa_tdma_process(काष्ठा mv_cesa_engine *engine, u32 status);


अटल अंतरभूत व्योम
mv_cesa_tdma_desc_iter_init(काष्ठा mv_cesa_tdma_chain *chain)
अणु
	स_रखो(chain, 0, माप(*chain));
पूर्ण

पूर्णांक mv_cesa_dma_add_result_op(काष्ठा mv_cesa_tdma_chain *chain, dma_addr_t src,
			  u32 size, u32 flags, gfp_t gfp_flags);

काष्ठा mv_cesa_op_ctx *mv_cesa_dma_add_op(काष्ठा mv_cesa_tdma_chain *chain,
					स्थिर काष्ठा mv_cesa_op_ctx *op_templ,
					bool skip_ctx,
					gfp_t flags);

पूर्णांक mv_cesa_dma_add_data_transfer(काष्ठा mv_cesa_tdma_chain *chain,
				  dma_addr_t dst, dma_addr_t src, u32 size,
				  u32 flags, gfp_t gfp_flags);

पूर्णांक mv_cesa_dma_add_dummy_launch(काष्ठा mv_cesa_tdma_chain *chain, gfp_t flags);
पूर्णांक mv_cesa_dma_add_dummy_end(काष्ठा mv_cesa_tdma_chain *chain, gfp_t flags);

पूर्णांक mv_cesa_dma_add_op_transfers(काष्ठा mv_cesa_tdma_chain *chain,
				 काष्ठा mv_cesa_dma_iter *dma_iter,
				 काष्ठा mv_cesa_sg_dma_iter *sgiter,
				 gfp_t gfp_flags);

माप_प्रकार mv_cesa_sg_copy(काष्ठा mv_cesa_engine *engine,
		       काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक nents,
		       अचिन्हित पूर्णांक sram_off, माप_प्रकार buflen, off_t skip,
		       bool to_sram);

अटल अंतरभूत माप_प्रकार mv_cesa_sg_copy_to_sram(काष्ठा mv_cesa_engine *engine,
					     काष्ठा scatterlist *sgl,
					     अचिन्हित पूर्णांक nents,
					     अचिन्हित पूर्णांक sram_off,
					     माप_प्रकार buflen, off_t skip)
अणु
	वापस mv_cesa_sg_copy(engine, sgl, nents, sram_off, buflen, skip,
			       true);
पूर्ण

अटल अंतरभूत माप_प्रकार mv_cesa_sg_copy_from_sram(काष्ठा mv_cesa_engine *engine,
					       काष्ठा scatterlist *sgl,
					       अचिन्हित पूर्णांक nents,
					       अचिन्हित पूर्णांक sram_off,
					       माप_प्रकार buflen, off_t skip)
अणु
	वापस mv_cesa_sg_copy(engine, sgl, nents, sram_off, buflen, skip,
			       false);
पूर्ण

/* Algorithm definitions */

बाह्य काष्ठा ahash_alg mv_md5_alg;
बाह्य काष्ठा ahash_alg mv_sha1_alg;
बाह्य काष्ठा ahash_alg mv_sha256_alg;
बाह्य काष्ठा ahash_alg mv_ahmac_md5_alg;
बाह्य काष्ठा ahash_alg mv_ahmac_sha1_alg;
बाह्य काष्ठा ahash_alg mv_ahmac_sha256_alg;

बाह्य काष्ठा skcipher_alg mv_cesa_ecb_des_alg;
बाह्य काष्ठा skcipher_alg mv_cesa_cbc_des_alg;
बाह्य काष्ठा skcipher_alg mv_cesa_ecb_des3_ede_alg;
बाह्य काष्ठा skcipher_alg mv_cesa_cbc_des3_ede_alg;
बाह्य काष्ठा skcipher_alg mv_cesa_ecb_aes_alg;
बाह्य काष्ठा skcipher_alg mv_cesa_cbc_aes_alg;

#पूर्ण_अगर /* __MARVELL_CESA_H__ */
