<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2016-2017 HiSilicon Limited. */

#अगर_अघोषित _SEC_DRV_H_
#घोषणा _SEC_DRV_H_

#समावेश <crypto/algapi.h>
#समावेश <linux/kfअगरo.h>

#घोषणा SEC_MAX_SGE_NUM			64
#घोषणा SEC_HW_RING_NUM			3

#घोषणा SEC_CMD_RING			0
#घोषणा SEC_OUTORDER_RING		1
#घोषणा SEC_DBG_RING			2

/* A reasonable length to balance memory use against flexibility */
#घोषणा SEC_QUEUE_LEN			512

#घोषणा SEC_MAX_SGE_NUM   64

काष्ठा sec_bd_info अणु
#घोषणा SEC_BD_W0_T_LEN_M			GENMASK(4, 0)
#घोषणा SEC_BD_W0_T_LEN_S			0

#घोषणा SEC_BD_W0_C_WIDTH_M			GENMASK(6, 5)
#घोषणा SEC_BD_W0_C_WIDTH_S			5
#घोषणा   SEC_C_WIDTH_AES_128BIT		0
#घोषणा   SEC_C_WIDTH_AES_8BIT		1
#घोषणा   SEC_C_WIDTH_AES_1BIT		2
#घोषणा   SEC_C_WIDTH_DES_64BIT		0
#घोषणा   SEC_C_WIDTH_DES_8BIT		1
#घोषणा   SEC_C_WIDTH_DES_1BIT		2

#घोषणा SEC_BD_W0_C_MODE_M			GENMASK(9, 7)
#घोषणा SEC_BD_W0_C_MODE_S			7
#घोषणा   SEC_C_MODE_ECB			0
#घोषणा   SEC_C_MODE_CBC			1
#घोषणा   SEC_C_MODE_CTR			4
#घोषणा   SEC_C_MODE_CCM			5
#घोषणा   SEC_C_MODE_GCM			6
#घोषणा   SEC_C_MODE_XTS			7

#घोषणा SEC_BD_W0_SEQ				BIT(10)
#घोषणा SEC_BD_W0_DE				BIT(11)
#घोषणा SEC_BD_W0_DAT_SKIP_M			GENMASK(13, 12)
#घोषणा SEC_BD_W0_DAT_SKIP_S			12
#घोषणा SEC_BD_W0_C_GRAN_SIZE_19_16_M		GENMASK(17, 14)
#घोषणा SEC_BD_W0_C_GRAN_SIZE_19_16_S		14

#घोषणा SEC_BD_W0_CIPHER_M			GENMASK(19, 18)
#घोषणा SEC_BD_W0_CIPHER_S			18
#घोषणा   SEC_CIPHER_शून्य			0
#घोषणा   SEC_CIPHER_ENCRYPT			1
#घोषणा   SEC_CIPHER_DECRYPT			2

#घोषणा SEC_BD_W0_AUTH_M			GENMASK(21, 20)
#घोषणा SEC_BD_W0_AUTH_S			20
#घोषणा   SEC_AUTH_शून्य				0
#घोषणा   SEC_AUTH_MAC				1
#घोषणा   SEC_AUTH_VERIF			2

#घोषणा SEC_BD_W0_AI_GEN			BIT(22)
#घोषणा SEC_BD_W0_CI_GEN			BIT(23)
#घोषणा SEC_BD_W0_NO_HPAD			BIT(24)
#घोषणा SEC_BD_W0_HM_M				GENMASK(26, 25)
#घोषणा SEC_BD_W0_HM_S				25
#घोषणा SEC_BD_W0_ICV_OR_SKEY_EN_M		GENMASK(28, 27)
#घोषणा SEC_BD_W0_ICV_OR_SKEY_EN_S		27

/* Multi purpose field - gran size bits क्रम send, flag क्रम recv */
#घोषणा SEC_BD_W0_FLAG_M			GENMASK(30, 29)
#घोषणा SEC_BD_W0_C_GRAN_SIZE_21_20_M		GENMASK(30, 29)
#घोषणा SEC_BD_W0_FLAG_S			29
#घोषणा SEC_BD_W0_C_GRAN_SIZE_21_20_S		29

#घोषणा SEC_BD_W0_DONE				BIT(31)
	u32 w0;

#घोषणा SEC_BD_W1_AUTH_GRAN_SIZE_M		GENMASK(21, 0)
#घोषणा SEC_BD_W1_AUTH_GRAN_SIZE_S		0
#घोषणा SEC_BD_W1_M_KEY_EN			BIT(22)
#घोषणा SEC_BD_W1_BD_INVALID			BIT(23)
#घोषणा SEC_BD_W1_ADDR_TYPE			BIT(24)

#घोषणा SEC_BD_W1_A_ALG_M			GENMASK(28, 25)
#घोषणा SEC_BD_W1_A_ALG_S			25
#घोषणा   SEC_A_ALG_SHA1			0
#घोषणा   SEC_A_ALG_SHA256			1
#घोषणा   SEC_A_ALG_MD5				2
#घोषणा   SEC_A_ALG_SHA224			3
#घोषणा   SEC_A_ALG_HMAC_SHA1			8
#घोषणा   SEC_A_ALG_HMAC_SHA224			10
#घोषणा   SEC_A_ALG_HMAC_SHA256			11
#घोषणा   SEC_A_ALG_HMAC_MD5			12
#घोषणा   SEC_A_ALG_AES_XCBC			13
#घोषणा   SEC_A_ALG_AES_CMAC			14

#घोषणा SEC_BD_W1_C_ALG_M			GENMASK(31, 29)
#घोषणा SEC_BD_W1_C_ALG_S			29
#घोषणा   SEC_C_ALG_DES				0
#घोषणा   SEC_C_ALG_3DES			1
#घोषणा   SEC_C_ALG_AES				2

	u32 w1;

#घोषणा SEC_BD_W2_C_GRAN_SIZE_15_0_M		GENMASK(15, 0)
#घोषणा SEC_BD_W2_C_GRAN_SIZE_15_0_S		0
#घोषणा SEC_BD_W2_GRAN_NUM_M			GENMASK(31, 16)
#घोषणा SEC_BD_W2_GRAN_NUM_S			16
	u32 w2;

#घोषणा SEC_BD_W3_AUTH_LEN_OFFSET_M		GENMASK(9, 0)
#घोषणा SEC_BD_W3_AUTH_LEN_OFFSET_S		0
#घोषणा SEC_BD_W3_CIPHER_LEN_OFFSET_M		GENMASK(19, 10)
#घोषणा SEC_BD_W3_CIPHER_LEN_OFFSET_S		10
#घोषणा SEC_BD_W3_MAC_LEN_M			GENMASK(24, 20)
#घोषणा SEC_BD_W3_MAC_LEN_S			20
#घोषणा SEC_BD_W3_A_KEY_LEN_M			GENMASK(29, 25)
#घोषणा SEC_BD_W3_A_KEY_LEN_S			25
#घोषणा SEC_BD_W3_C_KEY_LEN_M			GENMASK(31, 30)
#घोषणा SEC_BD_W3_C_KEY_LEN_S			30
#घोषणा   SEC_KEY_LEN_AES_128			0
#घोषणा   SEC_KEY_LEN_AES_192			1
#घोषणा   SEC_KEY_LEN_AES_256			2
#घोषणा   SEC_KEY_LEN_DES			1
#घोषणा   SEC_KEY_LEN_3DES_3_KEY		1
#घोषणा   SEC_KEY_LEN_3DES_2_KEY		3
	u32 w3;

	/* W4,5 */
	जोड़ अणु
		u32 authkey_addr_lo;
		u32 authiv_addr_lo;
	पूर्ण;
	जोड़ अणु
		u32 authkey_addr_hi;
		u32 authiv_addr_hi;
	पूर्ण;

	/* W6,7 */
	u32 cipher_key_addr_lo;
	u32 cipher_key_addr_hi;

	/* W8,9 */
	u32 cipher_iv_addr_lo;
	u32 cipher_iv_addr_hi;

	/* W10,11 */
	u32 data_addr_lo;
	u32 data_addr_hi;

	/* W12,13 */
	u32 mac_addr_lo;
	u32 mac_addr_hi;

	/* W14,15 */
	u32 cipher_destin_addr_lo;
	u32 cipher_destin_addr_hi;
पूर्ण;

क्रमागत sec_mem_region अणु
	SEC_COMMON = 0,
	SEC_SAA,
	SEC_NUM_ADDR_REGIONS
पूर्ण;

#घोषणा SEC_NAME_SIZE				64
#घोषणा SEC_Q_NUM				16


/**
 * काष्ठा sec_queue_ring_cmd - store inक्रमmation about a SEC HW cmd ring
 * @used: Local counter used to cheaply establish अगर the ring is empty.
 * @lock: Protect against simultaneous adjusting of the पढ़ो and ग_लिखो poपूर्णांकers.
 * @vaddr: Virtual address क्रम the ram pages used क्रम the ring.
 * @paddr: Physical address of the dma mapped region of ram used क्रम the ring.
 * @callback: Callback function called on a ring element completing.
 */
काष्ठा sec_queue_ring_cmd अणु
	atomic_t used;
	काष्ठा mutex lock;
	काष्ठा sec_bd_info *vaddr;
	dma_addr_t paddr;
	व्योम (*callback)(काष्ठा sec_bd_info *resp, व्योम *ctx);
पूर्ण;

काष्ठा sec_debug_bd_info;
काष्ठा sec_queue_ring_db अणु
	काष्ठा sec_debug_bd_info *vaddr;
	dma_addr_t paddr;
पूर्ण;

काष्ठा sec_out_bd_info;
काष्ठा sec_queue_ring_cq अणु
	काष्ठा sec_out_bd_info *vaddr;
	dma_addr_t paddr;
पूर्ण;

काष्ठा sec_dev_info;

क्रमागत sec_cipher_alg अणु
	SEC_C_DES_ECB_64,
	SEC_C_DES_CBC_64,

	SEC_C_3DES_ECB_192_3KEY,
	SEC_C_3DES_ECB_192_2KEY,

	SEC_C_3DES_CBC_192_3KEY,
	SEC_C_3DES_CBC_192_2KEY,

	SEC_C_AES_ECB_128,
	SEC_C_AES_ECB_192,
	SEC_C_AES_ECB_256,

	SEC_C_AES_CBC_128,
	SEC_C_AES_CBC_192,
	SEC_C_AES_CBC_256,

	SEC_C_AES_CTR_128,
	SEC_C_AES_CTR_192,
	SEC_C_AES_CTR_256,

	SEC_C_AES_XTS_128,
	SEC_C_AES_XTS_256,

	SEC_C_शून्य,
पूर्ण;

/**
 * काष्ठा sec_alg_tfm_ctx - hardware specअगरic tranक्रमmation context
 * @cipher_alg: Cipher algorithm enabled include encryption mode.
 * @key: Key storage अगर required.
 * @pkey: DMA address क्रम the key storage.
 * @req_ढाँचा: Request ढाँचा to save समय on setup.
 * @queue: The hardware queue associated with this tfm context.
 * @lock: Protect key and pkey to ensure they are consistent
 * @auth_buf: Current context buffer क्रम auth operations.
 * @backlog: The backlog queue used क्रम हालs where our buffers aren't
 * large enough.
 */
काष्ठा sec_alg_tfm_ctx अणु
	क्रमागत sec_cipher_alg cipher_alg;
	u8 *key;
	dma_addr_t pkey;
	काष्ठा sec_bd_info req_ढाँचा;
	काष्ठा sec_queue *queue;
	काष्ठा mutex lock;
	u8 *auth_buf;
	काष्ठा list_head backlog;
पूर्ण;

/**
 * काष्ठा sec_request - data associate with a single crypto request
 * @elements: List of subparts of this request (hardware size restriction)
 * @num_elements: The number of subparts (used as an optimization)
 * @lock: Protect elements of this काष्ठाure against concurrent change.
 * @tfm_ctx: hardware specअगरic context.
 * @len_in: length of in sgl from upper layers
 * @len_out: length of out sgl from upper layers
 * @dma_iv: initialization vector - phsyical address
 * @err: store used to track errors across subelements of this request.
 * @req_base: poपूर्णांकer to base element of associate crypto context.
 * This is needed to allow shared handling skcipher, ahash etc.
 * @cb: completion callback.
 * @backlog_head: list head to allow backlog मुख्यtenance.
 *
 * The hardware is limited in the maximum size of data that it can
 * process from a single BD.  Typically this is fairly large (32MB)
 * but still requires the complनिकासy of splitting the incoming
 * skreq up पूर्णांकo a number of elements complete with appropriate
 * iv chaining.
 */
काष्ठा sec_request अणु
	काष्ठा list_head elements;
	पूर्णांक num_elements;
	काष्ठा mutex lock;
	काष्ठा sec_alg_tfm_ctx *tfm_ctx;
	पूर्णांक len_in;
	पूर्णांक len_out;
	dma_addr_t dma_iv;
	पूर्णांक err;
	काष्ठा crypto_async_request *req_base;
	व्योम (*cb)(काष्ठा sec_bd_info *resp, काष्ठा crypto_async_request *req);
	काष्ठा list_head backlog_head;
पूर्ण;

/**
 * काष्ठा sec_request_el - A subpart of a request.
 * @head: allow us to attach this to the list in the sec_request
 * @req: hardware block descriptor corresponding to this request subpart
 * @in: hardware sgl क्रम input - भव address
 * @dma_in: hardware sgl क्रम input - physical address
 * @sgl_in: scatterlist क्रम this request subpart
 * @out: hardware sgl क्रम output - भव address
 * @dma_out: hardware sgl क्रम output - physical address
 * @sgl_out: scatterlist क्रम this request subpart
 * @sec_req: The request which this subpart क्रमms a part of
 * @el_length: Number of bytes in this subpart. Needed to locate
 * last ivsize chunk क्रम iv chaining.
 */
काष्ठा sec_request_el अणु
	काष्ठा list_head head;
	काष्ठा sec_bd_info req;
	काष्ठा sec_hw_sgl *in;
	dma_addr_t dma_in;
	काष्ठा scatterlist *sgl_in;
	काष्ठा sec_hw_sgl *out;
	dma_addr_t dma_out;
	काष्ठा scatterlist *sgl_out;
	काष्ठा sec_request *sec_req;
	माप_प्रकार el_length;
पूर्ण;

/**
 * काष्ठा sec_queue - All the inक्रमmation about a HW queue
 * @dev_info: The parent SEC device to which this queue beदीर्घs.
 * @task_irq: Completion पूर्णांकerrupt क्रम the queue.
 * @name: Human पढ़ोable queue description also used as irq name.
 * @ring: The several HW rings associated with one queue.
 * @regs: The iomapped device रेजिस्टरs
 * @queue_id: Index of the queue used क्रम naming and resource selection.
 * @in_use: Flag to say अगर the queue is in use.
 * @expected: The next expected element to finish assuming we were in order.
 * @uprocessed: A biपंचांगap to track which OoO elements are करोne but not handled.
 * @softqueue: A software queue used when chaining requirements prevent direct
 *   use of the hardware queues.
 * @havesoftqueue: A flag to say we have a queues - as we may need one क्रम the
 *   current mode.
 * @queuelock: Protect the soft queue from concurrent changes to aव्योम some
 *   potential loss of data races.
 * @shaकरोw: Poपूर्णांकers back to the shaकरोw copy of the hardware ring element
 *   need because we can't store any context reference in the bd element.
 */
काष्ठा sec_queue अणु
	काष्ठा sec_dev_info *dev_info;
	पूर्णांक task_irq;
	अक्षर name[SEC_NAME_SIZE];
	काष्ठा sec_queue_ring_cmd ring_cmd;
	काष्ठा sec_queue_ring_cq ring_cq;
	काष्ठा sec_queue_ring_db ring_db;
	व्योम __iomem *regs;
	u32 queue_id;
	bool in_use;
	पूर्णांक expected;

	DECLARE_BITMAP(unprocessed, SEC_QUEUE_LEN);
	DECLARE_KFIFO_PTR(softqueue, typeof(काष्ठा sec_request_el *));
	bool havesoftqueue;
	काष्ठा mutex queuelock;
	व्योम *shaकरोw[SEC_QUEUE_LEN];
पूर्ण;

/**
 * काष्ठा sec_hw_sge: Track each of the 64 element SEC HW SGL entries
 * @buf: The IOV dma address क्रम this entry.
 * @len: Length of this IOV.
 * @pad: Reserved space.
 */
काष्ठा sec_hw_sge अणु
	dma_addr_t buf;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक pad;
पूर्ण;

/**
 * काष्ठा sec_hw_sgl: One hardware SGL entry.
 * @next_sgl: The next entry अगर we need to chain dma address. Null अगर last.
 * @entry_sum_in_chain: The full count of SGEs - only matters क्रम first SGL.
 * @entry_sum_in_sgl: The number of SGEs in this SGL element.
 * @flag: Unused in skciphers.
 * @serial_num: Unsued in skciphers.
 * @cpuid: Currently unused.
 * @data_bytes_in_sgl: Count of bytes from all SGEs in this SGL.
 * @next: Virtual address used to stash the next sgl - useful in completion.
 * @reserved: A reserved field not currently used.
 * @sge_entries: The (up to) 64 Scatter Gather Entries, representing IOVs.
 * @node: Currently unused.
 */
काष्ठा sec_hw_sgl अणु
	dma_addr_t next_sgl;
	u16 entry_sum_in_chain;
	u16 entry_sum_in_sgl;
	u32 flag;
	u64 serial_num;
	u32 cpuid;
	u32 data_bytes_in_sgl;
	काष्ठा sec_hw_sgl *next;
	u64 reserved;
	काष्ठा sec_hw_sge  sge_entries[SEC_MAX_SGE_NUM];
	u8 node[16];
पूर्ण;

काष्ठा dma_pool;

/**
 * काष्ठा sec_dev_info: The full SEC unit comprising queues and processors.
 * @sec_id: Index used to track which SEC this is when more than one is present.
 * @num_saas: The number of backed processors enabled.
 * @regs: iomapped रेजिस्टर regions shared by whole SEC unit.
 * @dev_lock: Protects concurrent queue allocation / मुक्तing क्रम the SEC.
 * @queues: The 16 queues that this SEC instance provides.
 * @dev: Device poपूर्णांकer.
 * @hw_sgl_pool: DMA pool used to mimise mapping क्रम the scatter gather lists.
 */
काष्ठा sec_dev_info अणु
	पूर्णांक sec_id;
	पूर्णांक num_saas;
	व्योम __iomem *regs[SEC_NUM_ADDR_REGIONS];
	काष्ठा mutex dev_lock;
	पूर्णांक queues_in_use;
	काष्ठा sec_queue queues[SEC_Q_NUM];
	काष्ठा device *dev;
	काष्ठा dma_pool *hw_sgl_pool;
पूर्ण;

पूर्णांक sec_queue_send(काष्ठा sec_queue *queue, काष्ठा sec_bd_info *msg, व्योम *ctx);
bool sec_queue_can_enqueue(काष्ठा sec_queue *queue, पूर्णांक num);
पूर्णांक sec_queue_stop_release(काष्ठा sec_queue *queue);
काष्ठा sec_queue *sec_queue_alloc_start_safe(व्योम);
bool sec_queue_empty(काष्ठा sec_queue *queue);

/* Algorithm specअगरic elements from sec_algs.c */
व्योम sec_alg_callback(काष्ठा sec_bd_info *resp, व्योम *ctx);
पूर्णांक sec_algs_रेजिस्टर(व्योम);
व्योम sec_algs_unरेजिस्टर(व्योम);

#पूर्ण_अगर /* _SEC_DRV_H_ */
