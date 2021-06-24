<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Keem Bay OCS HCU Crypto Driver.
 *
 * Copyright (C) 2018-2020 Intel Corporation
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>

#समावेश <crypto/sha2.h>

#समावेश "ocs-hcu.h"

/* Registers. */
#घोषणा OCS_HCU_MODE			0x00
#घोषणा OCS_HCU_CHAIN			0x04
#घोषणा OCS_HCU_OPERATION		0x08
#घोषणा OCS_HCU_KEY_0			0x0C
#घोषणा OCS_HCU_ISR			0x50
#घोषणा OCS_HCU_IER			0x54
#घोषणा OCS_HCU_STATUS			0x58
#घोषणा OCS_HCU_MSG_LEN_LO		0x60
#घोषणा OCS_HCU_MSG_LEN_HI		0x64
#घोषणा OCS_HCU_KEY_BYTE_ORDER_CFG	0x80
#घोषणा OCS_HCU_DMA_SRC_ADDR		0x400
#घोषणा OCS_HCU_DMA_SRC_SIZE		0x408
#घोषणा OCS_HCU_DMA_DST_SIZE		0x40C
#घोषणा OCS_HCU_DMA_DMA_MODE		0x410
#घोषणा OCS_HCU_DMA_NEXT_SRC_DESCR	0x418
#घोषणा OCS_HCU_DMA_MSI_ISR		0x480
#घोषणा OCS_HCU_DMA_MSI_IER		0x484
#घोषणा OCS_HCU_DMA_MSI_MASK		0x488

/* Register bit definitions. */
#घोषणा HCU_MODE_ALGO_SHIFT		16
#घोषणा HCU_MODE_HMAC_SHIFT		22

#घोषणा HCU_STATUS_BUSY			BIT(0)

#घोषणा HCU_BYTE_ORDER_SWAP		BIT(0)

#घोषणा HCU_IRQ_HASH_DONE		BIT(2)
#घोषणा HCU_IRQ_HASH_ERR_MASK		(BIT(3) | BIT(1) | BIT(0))

#घोषणा HCU_DMA_IRQ_SRC_DONE		BIT(0)
#घोषणा HCU_DMA_IRQ_SAI_ERR		BIT(2)
#घोषणा HCU_DMA_IRQ_BAD_COMP_ERR	BIT(3)
#घोषणा HCU_DMA_IRQ_INBUF_RD_ERR	BIT(4)
#घोषणा HCU_DMA_IRQ_INBUF_WD_ERR	BIT(5)
#घोषणा HCU_DMA_IRQ_OUTBUF_WR_ERR	BIT(6)
#घोषणा HCU_DMA_IRQ_OUTBUF_RD_ERR	BIT(7)
#घोषणा HCU_DMA_IRQ_CRD_ERR		BIT(8)
#घोषणा HCU_DMA_IRQ_ERR_MASK		(HCU_DMA_IRQ_SAI_ERR | \
					 HCU_DMA_IRQ_BAD_COMP_ERR | \
					 HCU_DMA_IRQ_INBUF_RD_ERR | \
					 HCU_DMA_IRQ_INBUF_WD_ERR | \
					 HCU_DMA_IRQ_OUTBUF_WR_ERR | \
					 HCU_DMA_IRQ_OUTBUF_RD_ERR | \
					 HCU_DMA_IRQ_CRD_ERR)

#घोषणा HCU_DMA_SNOOP_MASK		(0x7 << 28)
#घोषणा HCU_DMA_SRC_LL_EN		BIT(25)
#घोषणा HCU_DMA_EN			BIT(31)

#घोषणा OCS_HCU_ENDIANNESS_VALUE	0x2A

#घोषणा HCU_DMA_MSI_UNMASK		BIT(0)
#घोषणा HCU_DMA_MSI_DISABLE		0
#घोषणा HCU_IRQ_DISABLE			0

#घोषणा OCS_HCU_START			BIT(0)
#घोषणा OCS_HCU_TERMINATE		BIT(1)

#घोषणा OCS_LL_DMA_FLAG_TERMINATE	BIT(31)

#घोषणा OCS_HCU_HW_KEY_LEN_U32		(OCS_HCU_HW_KEY_LEN / माप(u32))

#घोषणा HCU_DATA_WRITE_ENDIANNESS_OFFSET	26

#घोषणा OCS_HCU_NUM_CHAINS_SHA256_224_SM3	(SHA256_DIGEST_SIZE / माप(u32))
#घोषणा OCS_HCU_NUM_CHAINS_SHA384_512		(SHA512_DIGEST_SIZE / माप(u32))

/*
 * While polling on a busy HCU, रुको maximum 200us between one check and the
 * other.
 */
#घोषणा OCS_HCU_WAIT_BUSY_RETRY_DELAY_US	200
/* Wait on a busy HCU क्रम maximum 1 second. */
#घोषणा OCS_HCU_WAIT_BUSY_TIMEOUT_US		1000000

/**
 * काष्ठा ocs_hcu_dma_entry - An entry in an OCS DMA linked list.
 * @src_addr:  Source address of the data.
 * @src_len:   Length of data to be fetched.
 * @nxt_desc:  Next descriptor to fetch.
 * @ll_flags:  Flags (Freeze @ terminate) क्रम the DMA engine.
 */
काष्ठा ocs_hcu_dma_entry अणु
	u32 src_addr;
	u32 src_len;
	u32 nxt_desc;
	u32 ll_flags;
पूर्ण;

/**
 * काष्ठा ocs_hcu_dma_list - OCS-specअगरic DMA linked list.
 * @head:	The head of the list (poपूर्णांकs to the array backing the list).
 * @tail:	The current tail of the list; शून्य अगर the list is empty.
 * @dma_addr:	The DMA address of @head (i.e., the DMA address of the backing
 *		array).
 * @max_nents:	Maximum number of entries in the list (i.e., number of elements
 *		in the backing array).
 *
 * The OCS DMA list is an array-backed list of OCS DMA descriptors. The array
 * backing the list is allocated with dma_alloc_coherent() and poपूर्णांकed by
 * @head.
 */
काष्ठा ocs_hcu_dma_list अणु
	काष्ठा ocs_hcu_dma_entry	*head;
	काष्ठा ocs_hcu_dma_entry	*tail;
	dma_addr_t			dma_addr;
	माप_प्रकार				max_nents;
पूर्ण;

अटल अंतरभूत u32 ocs_hcu_num_chains(क्रमागत ocs_hcu_algo algo)
अणु
	चयन (algo) अणु
	हाल OCS_HCU_ALGO_SHA224:
	हाल OCS_HCU_ALGO_SHA256:
	हाल OCS_HCU_ALGO_SM3:
		वापस OCS_HCU_NUM_CHAINS_SHA256_224_SM3;
	हाल OCS_HCU_ALGO_SHA384:
	हाल OCS_HCU_ALGO_SHA512:
		वापस OCS_HCU_NUM_CHAINS_SHA384_512;
	शेष:
		वापस 0;
	पूर्ण;
पूर्ण

अटल अंतरभूत u32 ocs_hcu_digest_size(क्रमागत ocs_hcu_algo algo)
अणु
	चयन (algo) अणु
	हाल OCS_HCU_ALGO_SHA224:
		वापस SHA224_DIGEST_SIZE;
	हाल OCS_HCU_ALGO_SHA256:
	हाल OCS_HCU_ALGO_SM3:
		/* SM3 shares the same block size. */
		वापस SHA256_DIGEST_SIZE;
	हाल OCS_HCU_ALGO_SHA384:
		वापस SHA384_DIGEST_SIZE;
	हाल OCS_HCU_ALGO_SHA512:
		वापस SHA512_DIGEST_SIZE;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/**
 * ocs_hcu_रुको_busy() - Wait क्रम HCU OCS hardware to became usable.
 * @hcu_dev:	OCS HCU device to रुको क्रम.
 *
 * Return: 0 अगर device मुक्त, -ETIMEOUT अगर device busy and पूर्णांकernal समयout has
 *	   expired.
 */
अटल पूर्णांक ocs_hcu_रुको_busy(काष्ठा ocs_hcu_dev *hcu_dev)
अणु
	दीर्घ val;

	वापस पढ़ोl_poll_समयout(hcu_dev->io_base + OCS_HCU_STATUS, val,
				  !(val & HCU_STATUS_BUSY),
				  OCS_HCU_WAIT_BUSY_RETRY_DELAY_US,
				  OCS_HCU_WAIT_BUSY_TIMEOUT_US);
पूर्ण

अटल व्योम ocs_hcu_करोne_irq_en(काष्ठा ocs_hcu_dev *hcu_dev)
अणु
	/* Clear any pending पूर्णांकerrupts. */
	ग_लिखोl(0xFFFFFFFF, hcu_dev->io_base + OCS_HCU_ISR);
	hcu_dev->irq_err = false;
	/* Enable error and HCU करोne पूर्णांकerrupts. */
	ग_लिखोl(HCU_IRQ_HASH_DONE | HCU_IRQ_HASH_ERR_MASK,
	       hcu_dev->io_base + OCS_HCU_IER);
पूर्ण

अटल व्योम ocs_hcu_dma_irq_en(काष्ठा ocs_hcu_dev *hcu_dev)
अणु
	/* Clear any pending पूर्णांकerrupts. */
	ग_लिखोl(0xFFFFFFFF, hcu_dev->io_base + OCS_HCU_DMA_MSI_ISR);
	hcu_dev->irq_err = false;
	/* Only operating on DMA source completion and error पूर्णांकerrupts. */
	ग_लिखोl(HCU_DMA_IRQ_ERR_MASK | HCU_DMA_IRQ_SRC_DONE,
	       hcu_dev->io_base + OCS_HCU_DMA_MSI_IER);
	/* Unmask */
	ग_लिखोl(HCU_DMA_MSI_UNMASK, hcu_dev->io_base + OCS_HCU_DMA_MSI_MASK);
पूर्ण

अटल व्योम ocs_hcu_irq_dis(काष्ठा ocs_hcu_dev *hcu_dev)
अणु
	ग_लिखोl(HCU_IRQ_DISABLE, hcu_dev->io_base + OCS_HCU_IER);
	ग_लिखोl(HCU_DMA_MSI_DISABLE, hcu_dev->io_base + OCS_HCU_DMA_MSI_IER);
पूर्ण

अटल पूर्णांक ocs_hcu_रुको_and_disable_irq(काष्ठा ocs_hcu_dev *hcu_dev)
अणु
	पूर्णांक rc;

	rc = रुको_क्रम_completion_पूर्णांकerruptible(&hcu_dev->irq_करोne);
	अगर (rc)
		जाओ निकास;

	अगर (hcu_dev->irq_err) अणु
		/* Unset flag and वापस error. */
		hcu_dev->irq_err = false;
		rc = -EIO;
		जाओ निकास;
	पूर्ण

निकास:
	ocs_hcu_irq_dis(hcu_dev);

	वापस rc;
पूर्ण

/**
 * ocs_hcu_get_पूर्णांकermediate_data() - Get पूर्णांकermediate data.
 * @hcu_dev:	The target HCU device.
 * @data:	Where to store the पूर्णांकermediate.
 * @algo:	The algorithm being used.
 *
 * This function is used to save the current hashing process state in order to
 * जारी it in the future.
 *
 * Note: once all data has been processed, the पूर्णांकermediate data actually
 * contains the hashing result. So this function is also used to retrieve the
 * final result of a hashing process.
 *
 * Return: 0 on success, negative error code otherwise.
 */
अटल पूर्णांक ocs_hcu_get_पूर्णांकermediate_data(काष्ठा ocs_hcu_dev *hcu_dev,
					 काष्ठा ocs_hcu_idata *data,
					 क्रमागत ocs_hcu_algo algo)
अणु
	स्थिर पूर्णांक n = ocs_hcu_num_chains(algo);
	u32 *chain;
	पूर्णांक rc;
	पूर्णांक i;

	/* Data not requested. */
	अगर (!data)
		वापस -EINVAL;

	chain = (u32 *)data->digest;

	/* Ensure that the OCS is no दीर्घer busy beक्रमe पढ़ोing the chains. */
	rc = ocs_hcu_रुको_busy(hcu_dev);
	अगर (rc)
		वापस rc;

	/*
	 * This loops is safe because data->digest is an array of
	 * SHA512_DIGEST_SIZE bytes and the maximum value वापसed by
	 * ocs_hcu_num_chains() is OCS_HCU_NUM_CHAINS_SHA384_512 which is equal
	 * to SHA512_DIGEST_SIZE / माप(u32).
	 */
	क्रम (i = 0; i < n; i++)
		chain[i] = पढ़ोl(hcu_dev->io_base + OCS_HCU_CHAIN);

	data->msg_len_lo = पढ़ोl(hcu_dev->io_base + OCS_HCU_MSG_LEN_LO);
	data->msg_len_hi = पढ़ोl(hcu_dev->io_base + OCS_HCU_MSG_LEN_HI);

	वापस 0;
पूर्ण

/**
 * ocs_hcu_set_पूर्णांकermediate_data() - Set पूर्णांकermediate data.
 * @hcu_dev:	The target HCU device.
 * @data:	The पूर्णांकermediate data to be set.
 * @algo:	The algorithm being used.
 *
 * This function is used to जारी a previous hashing process.
 */
अटल व्योम ocs_hcu_set_पूर्णांकermediate_data(काष्ठा ocs_hcu_dev *hcu_dev,
					  स्थिर काष्ठा ocs_hcu_idata *data,
					  क्रमागत ocs_hcu_algo algo)
अणु
	स्थिर पूर्णांक n = ocs_hcu_num_chains(algo);
	u32 *chain = (u32 *)data->digest;
	पूर्णांक i;

	/*
	 * This loops is safe because data->digest is an array of
	 * SHA512_DIGEST_SIZE bytes and the maximum value वापसed by
	 * ocs_hcu_num_chains() is OCS_HCU_NUM_CHAINS_SHA384_512 which is equal
	 * to SHA512_DIGEST_SIZE / माप(u32).
	 */
	क्रम (i = 0; i < n; i++)
		ग_लिखोl(chain[i], hcu_dev->io_base + OCS_HCU_CHAIN);

	ग_लिखोl(data->msg_len_lo, hcu_dev->io_base + OCS_HCU_MSG_LEN_LO);
	ग_लिखोl(data->msg_len_hi, hcu_dev->io_base + OCS_HCU_MSG_LEN_HI);
पूर्ण

अटल पूर्णांक ocs_hcu_get_digest(काष्ठा ocs_hcu_dev *hcu_dev,
			      क्रमागत ocs_hcu_algo algo, u8 *dgst, माप_प्रकार dgst_len)
अणु
	u32 *chain;
	पूर्णांक rc;
	पूर्णांक i;

	अगर (!dgst)
		वापस -EINVAL;

	/* Length of the output buffer must match the algo digest size. */
	अगर (dgst_len != ocs_hcu_digest_size(algo))
		वापस -EINVAL;

	/* Ensure that the OCS is no दीर्घer busy beक्रमe पढ़ोing the chains. */
	rc = ocs_hcu_रुको_busy(hcu_dev);
	अगर (rc)
		वापस rc;

	chain = (u32 *)dgst;
	क्रम (i = 0; i < dgst_len / माप(u32); i++)
		chain[i] = पढ़ोl(hcu_dev->io_base + OCS_HCU_CHAIN);

	वापस 0;
पूर्ण

/**
 * ocs_hcu_hw_cfg() - Configure the HCU hardware.
 * @hcu_dev:	The HCU device to configure.
 * @algo:	The algorithm to be used by the HCU device.
 * @use_hmac:	Whether or not HW HMAC should be used.
 *
 * Return: 0 on success, negative error code otherwise.
 */
अटल पूर्णांक ocs_hcu_hw_cfg(काष्ठा ocs_hcu_dev *hcu_dev, क्रमागत ocs_hcu_algo algo,
			  bool use_hmac)
अणु
	u32 cfg;
	पूर्णांक rc;

	अगर (algo != OCS_HCU_ALGO_SHA256 && algo != OCS_HCU_ALGO_SHA224 &&
	    algo != OCS_HCU_ALGO_SHA384 && algo != OCS_HCU_ALGO_SHA512 &&
	    algo != OCS_HCU_ALGO_SM3)
		वापस -EINVAL;

	rc = ocs_hcu_रुको_busy(hcu_dev);
	अगर (rc)
		वापस rc;

	/* Ensure पूर्णांकerrupts are disabled. */
	ocs_hcu_irq_dis(hcu_dev);

	/* Configure endianness, hashing algorithm and HW HMAC (अगर needed) */
	cfg = OCS_HCU_ENDIANNESS_VALUE << HCU_DATA_WRITE_ENDIANNESS_OFFSET;
	cfg |= algo << HCU_MODE_ALGO_SHIFT;
	अगर (use_hmac)
		cfg |= BIT(HCU_MODE_HMAC_SHIFT);

	ग_लिखोl(cfg, hcu_dev->io_base + OCS_HCU_MODE);

	वापस 0;
पूर्ण

/**
 * ocs_hcu_clear_key() - Clear key stored in OCS HMAC KEY रेजिस्टरs.
 * @hcu_dev:	The OCS HCU device whose key रेजिस्टरs should be cleared.
 */
अटल व्योम ocs_hcu_clear_key(काष्ठा ocs_hcu_dev *hcu_dev)
अणु
	पूर्णांक reg_off;

	/* Clear OCS_HCU_KEY_[0..15] */
	क्रम (reg_off = 0; reg_off < OCS_HCU_HW_KEY_LEN; reg_off += माप(u32))
		ग_लिखोl(0, hcu_dev->io_base + OCS_HCU_KEY_0 + reg_off);
पूर्ण

/**
 * ocs_hcu_ग_लिखो_key() - Write key to OCS HMAC KEY रेजिस्टरs.
 * @hcu_dev:	The OCS HCU device the key should be written to.
 * @key:	The key to be written.
 * @len:	The size of the key to ग_लिखो. It must be OCS_HCU_HW_KEY_LEN.
 *
 * Return:	0 on success, negative error code otherwise.
 */
अटल पूर्णांक ocs_hcu_ग_लिखो_key(काष्ठा ocs_hcu_dev *hcu_dev, स्थिर u8 *key, माप_प्रकार len)
अणु
	u32 key_u32[OCS_HCU_HW_KEY_LEN_U32];
	पूर्णांक i;

	अगर (len > OCS_HCU_HW_KEY_LEN)
		वापस -EINVAL;

	/* Copy key पूर्णांकo temporary u32 array. */
	स_नकल(key_u32, key, len);

	/*
	 * Hardware requires all the bytes of the HW Key vector to be
	 * written. So pad with zero until we reach OCS_HCU_HW_KEY_LEN.
	 */
	memzero_explicit((u8 *)key_u32 + len, OCS_HCU_HW_KEY_LEN - len);

	/*
	 * OCS hardware expects the MSB of the key to be written at the highest
	 * address of the HCU Key vector; in other word, the key must be
	 * written in reverse order.
	 *
	 * Thereक्रमe, we first enable byte swapping क्रम the HCU key vector;
	 * so that bytes of 32-bit word written to OCS_HCU_KEY_[0..15] will be
	 * swapped:
	 * 3 <---> 0, 2 <---> 1.
	 */
	ग_लिखोl(HCU_BYTE_ORDER_SWAP,
	       hcu_dev->io_base + OCS_HCU_KEY_BYTE_ORDER_CFG);
	/*
	 * And then we ग_लिखो the 32-bit words composing the key starting from
	 * the end of the key.
	 */
	क्रम (i = 0; i < OCS_HCU_HW_KEY_LEN_U32; i++)
		ग_लिखोl(key_u32[OCS_HCU_HW_KEY_LEN_U32 - 1 - i],
		       hcu_dev->io_base + OCS_HCU_KEY_0 + (माप(u32) * i));

	memzero_explicit(key_u32, OCS_HCU_HW_KEY_LEN);

	वापस 0;
पूर्ण

/**
 * ocs_hcu_ll_dma_start() - Start OCS HCU hashing via DMA
 * @hcu_dev:	The OCS HCU device to use.
 * @dma_list:	The OCS DMA list mapping the data to hash.
 * @finalize:	Whether or not this is the last hashing operation and thereक्रमe
 *		the final hash should be compute even अगर data is not
 *		block-aligned.
 *
 * Return: 0 on success, negative error code otherwise.
 */
अटल पूर्णांक ocs_hcu_ll_dma_start(काष्ठा ocs_hcu_dev *hcu_dev,
				स्थिर काष्ठा ocs_hcu_dma_list *dma_list,
				bool finalize)
अणु
	u32 cfg = HCU_DMA_SNOOP_MASK | HCU_DMA_SRC_LL_EN | HCU_DMA_EN;
	पूर्णांक rc;

	अगर (!dma_list)
		वापस -EINVAL;

	/*
	 * For final requests we use HCU_DONE IRQ to be notअगरied when all input
	 * data has been processed by the HCU; however, we cannot करो so क्रम
	 * non-final requests, because we करोn't get a HCU_DONE IRQ when we
	 * करोn't terminate the operation.
	 *
	 * Thereक्रमe, क्रम non-final requests, we use the DMA IRQ, which
	 * triggers when DMA has finishing feeding all the input data to the
	 * HCU, but the HCU may still be processing it. This is fine, since we
	 * will रुको क्रम the HCU processing to be completed when we try to पढ़ो
	 * पूर्णांकermediate results, in ocs_hcu_get_पूर्णांकermediate_data().
	 */
	अगर (finalize)
		ocs_hcu_करोne_irq_en(hcu_dev);
	अन्यथा
		ocs_hcu_dma_irq_en(hcu_dev);

	reinit_completion(&hcu_dev->irq_करोne);
	ग_लिखोl(dma_list->dma_addr, hcu_dev->io_base + OCS_HCU_DMA_NEXT_SRC_DESCR);
	ग_लिखोl(0, hcu_dev->io_base + OCS_HCU_DMA_SRC_SIZE);
	ग_लिखोl(0, hcu_dev->io_base + OCS_HCU_DMA_DST_SIZE);

	ग_लिखोl(OCS_HCU_START, hcu_dev->io_base + OCS_HCU_OPERATION);

	ग_लिखोl(cfg, hcu_dev->io_base + OCS_HCU_DMA_DMA_MODE);

	अगर (finalize)
		ग_लिखोl(OCS_HCU_TERMINATE, hcu_dev->io_base + OCS_HCU_OPERATION);

	rc = ocs_hcu_रुको_and_disable_irq(hcu_dev);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

काष्ठा ocs_hcu_dma_list *ocs_hcu_dma_list_alloc(काष्ठा ocs_hcu_dev *hcu_dev,
						पूर्णांक max_nents)
अणु
	काष्ठा ocs_hcu_dma_list *dma_list;

	dma_list = kदो_स्मृति(माप(*dma_list), GFP_KERNEL);
	अगर (!dma_list)
		वापस शून्य;

	/* Total size of the DMA list to allocate. */
	dma_list->head = dma_alloc_coherent(hcu_dev->dev,
					    माप(*dma_list->head) * max_nents,
					    &dma_list->dma_addr, GFP_KERNEL);
	अगर (!dma_list->head) अणु
		kमुक्त(dma_list);
		वापस शून्य;
	पूर्ण
	dma_list->max_nents = max_nents;
	dma_list->tail = शून्य;

	वापस dma_list;
पूर्ण

व्योम ocs_hcu_dma_list_मुक्त(काष्ठा ocs_hcu_dev *hcu_dev,
			   काष्ठा ocs_hcu_dma_list *dma_list)
अणु
	अगर (!dma_list)
		वापस;

	dma_मुक्त_coherent(hcu_dev->dev,
			  माप(*dma_list->head) * dma_list->max_nents,
			  dma_list->head, dma_list->dma_addr);

	kमुक्त(dma_list);
पूर्ण

/* Add a new DMA entry at the end of the OCS DMA list. */
पूर्णांक ocs_hcu_dma_list_add_tail(काष्ठा ocs_hcu_dev *hcu_dev,
			      काष्ठा ocs_hcu_dma_list *dma_list,
			      dma_addr_t addr, u32 len)
अणु
	काष्ठा device *dev = hcu_dev->dev;
	काष्ठा ocs_hcu_dma_entry *old_tail;
	काष्ठा ocs_hcu_dma_entry *new_tail;

	अगर (!len)
		वापस 0;

	अगर (!dma_list)
		वापस -EINVAL;

	अगर (addr & ~OCS_HCU_DMA_BIT_MASK) अणु
		dev_err(dev,
			"Unexpected error: Invalid DMA address for OCS HCU\n");
		वापस -EINVAL;
	पूर्ण

	old_tail = dma_list->tail;
	new_tail = old_tail ? old_tail + 1 : dma_list->head;

	/* Check अगर list is full. */
	अगर (new_tail - dma_list->head >= dma_list->max_nents)
		वापस -ENOMEM;

	/*
	 * If there was an old tail (i.e., this is not the first element we are
	 * adding), un-terminate the old tail and make it poपूर्णांक to the new one.
	 */
	अगर (old_tail) अणु
		old_tail->ll_flags &= ~OCS_LL_DMA_FLAG_TERMINATE;
		/*
		 * The old tail 'nxt_desc' must poपूर्णांक to the DMA address of the
		 * new tail.
		 */
		old_tail->nxt_desc = dma_list->dma_addr +
				     माप(*dma_list->tail) * (new_tail -
								dma_list->head);
	पूर्ण

	new_tail->src_addr = (u32)addr;
	new_tail->src_len = (u32)len;
	new_tail->ll_flags = OCS_LL_DMA_FLAG_TERMINATE;
	new_tail->nxt_desc = 0;

	/* Update list tail with new tail. */
	dma_list->tail = new_tail;

	वापस 0;
पूर्ण

/**
 * ocs_hcu_hash_init() - Initialize hash operation context.
 * @ctx:	The context to initialize.
 * @algo:	The hashing algorithm to use.
 *
 * Return:	0 on success, negative error code otherwise.
 */
पूर्णांक ocs_hcu_hash_init(काष्ठा ocs_hcu_hash_ctx *ctx, क्रमागत ocs_hcu_algo algo)
अणु
	अगर (!ctx)
		वापस -EINVAL;

	ctx->algo = algo;
	ctx->idata.msg_len_lo = 0;
	ctx->idata.msg_len_hi = 0;
	/* No need to set idata.digest to 0. */

	वापस 0;
पूर्ण

/**
 * ocs_hcu_hash_update() - Perक्रमm a hashing iteration.
 * @hcu_dev:	The OCS HCU device to use.
 * @ctx:	The OCS HCU hashing context.
 * @dma_list:	The OCS DMA list mapping the input data to process.
 *
 * Return: 0 on success; negative error code otherwise.
 */
पूर्णांक ocs_hcu_hash_update(काष्ठा ocs_hcu_dev *hcu_dev,
			काष्ठा ocs_hcu_hash_ctx *ctx,
			स्थिर काष्ठा ocs_hcu_dma_list *dma_list)
अणु
	पूर्णांक rc;

	अगर (!hcu_dev || !ctx)
		वापस -EINVAL;

	/* Configure the hardware क्रम the current request. */
	rc = ocs_hcu_hw_cfg(hcu_dev, ctx->algo, false);
	अगर (rc)
		वापस rc;

	/* If we alपढ़ोy processed some data, idata needs to be set. */
	अगर (ctx->idata.msg_len_lo || ctx->idata.msg_len_hi)
		ocs_hcu_set_पूर्णांकermediate_data(hcu_dev, &ctx->idata, ctx->algo);

	/* Start linked-list DMA hashing. */
	rc = ocs_hcu_ll_dma_start(hcu_dev, dma_list, false);
	अगर (rc)
		वापस rc;

	/* Update idata and वापस. */
	वापस ocs_hcu_get_पूर्णांकermediate_data(hcu_dev, &ctx->idata, ctx->algo);
पूर्ण

/**
 * ocs_hcu_hash_finup() - Update and finalize hash computation.
 * @hcu_dev:	The OCS HCU device to use.
 * @ctx:	The OCS HCU hashing context.
 * @dma_list:	The OCS DMA list mapping the input data to process.
 * @dgst:	The buffer where to save the computed digest.
 * @dgst_len:	The length of @dgst.
 *
 * Return: 0 on success; negative error code otherwise.
 */
पूर्णांक ocs_hcu_hash_finup(काष्ठा ocs_hcu_dev *hcu_dev,
		       स्थिर काष्ठा ocs_hcu_hash_ctx *ctx,
		       स्थिर काष्ठा ocs_hcu_dma_list *dma_list,
		       u8 *dgst, माप_प्रकार dgst_len)
अणु
	पूर्णांक rc;

	अगर (!hcu_dev || !ctx)
		वापस -EINVAL;

	/* Configure the hardware क्रम the current request. */
	rc = ocs_hcu_hw_cfg(hcu_dev, ctx->algo, false);
	अगर (rc)
		वापस rc;

	/* If we alपढ़ोy processed some data, idata needs to be set. */
	अगर (ctx->idata.msg_len_lo || ctx->idata.msg_len_hi)
		ocs_hcu_set_पूर्णांकermediate_data(hcu_dev, &ctx->idata, ctx->algo);

	/* Start linked-list DMA hashing. */
	rc = ocs_hcu_ll_dma_start(hcu_dev, dma_list, true);
	अगर (rc)
		वापस rc;

	/* Get digest and वापस. */
	वापस ocs_hcu_get_digest(hcu_dev, ctx->algo, dgst, dgst_len);
पूर्ण

/**
 * ocs_hcu_hash_final() - Finalize hash computation.
 * @hcu_dev:		The OCS HCU device to use.
 * @ctx:		The OCS HCU hashing context.
 * @dgst:		The buffer where to save the computed digest.
 * @dgst_len:		The length of @dgst.
 *
 * Return: 0 on success; negative error code otherwise.
 */
पूर्णांक ocs_hcu_hash_final(काष्ठा ocs_hcu_dev *hcu_dev,
		       स्थिर काष्ठा ocs_hcu_hash_ctx *ctx, u8 *dgst,
		       माप_प्रकार dgst_len)
अणु
	पूर्णांक rc;

	अगर (!hcu_dev || !ctx)
		वापस -EINVAL;

	/* Configure the hardware क्रम the current request. */
	rc = ocs_hcu_hw_cfg(hcu_dev, ctx->algo, false);
	अगर (rc)
		वापस rc;

	/* If we alपढ़ोy processed some data, idata needs to be set. */
	अगर (ctx->idata.msg_len_lo || ctx->idata.msg_len_hi)
		ocs_hcu_set_पूर्णांकermediate_data(hcu_dev, &ctx->idata, ctx->algo);

	/*
	 * Enable HCU पूर्णांकerrupts, so that HCU_DONE will be triggered once the
	 * final hash is computed.
	 */
	ocs_hcu_करोne_irq_en(hcu_dev);
	reinit_completion(&hcu_dev->irq_करोne);
	ग_लिखोl(OCS_HCU_TERMINATE, hcu_dev->io_base + OCS_HCU_OPERATION);

	rc = ocs_hcu_रुको_and_disable_irq(hcu_dev);
	अगर (rc)
		वापस rc;

	/* Get digest and वापस. */
	वापस ocs_hcu_get_digest(hcu_dev, ctx->algo, dgst, dgst_len);
पूर्ण

/**
 * ocs_hcu_digest() - Compute hash digest.
 * @hcu_dev:		The OCS HCU device to use.
 * @algo:		The hash algorithm to use.
 * @data:		The input data to process.
 * @data_len:		The length of @data.
 * @dgst:		The buffer where to save the computed digest.
 * @dgst_len:		The length of @dgst.
 *
 * Return: 0 on success; negative error code otherwise.
 */
पूर्णांक ocs_hcu_digest(काष्ठा ocs_hcu_dev *hcu_dev, क्रमागत ocs_hcu_algo algo,
		   व्योम *data, माप_प्रकार data_len, u8 *dgst, माप_प्रकार dgst_len)
अणु
	काष्ठा device *dev = hcu_dev->dev;
	dma_addr_t dma_handle;
	u32 reg;
	पूर्णांक rc;

	/* Configure the hardware क्रम the current request. */
	rc = ocs_hcu_hw_cfg(hcu_dev, algo, false);
	अगर (rc)
		वापस rc;

	dma_handle = dma_map_single(dev, data, data_len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, dma_handle))
		वापस -EIO;

	reg = HCU_DMA_SNOOP_MASK | HCU_DMA_EN;

	ocs_hcu_करोne_irq_en(hcu_dev);

	reinit_completion(&hcu_dev->irq_करोne);

	ग_लिखोl(dma_handle, hcu_dev->io_base + OCS_HCU_DMA_SRC_ADDR);
	ग_लिखोl(data_len, hcu_dev->io_base + OCS_HCU_DMA_SRC_SIZE);
	ग_लिखोl(OCS_HCU_START, hcu_dev->io_base + OCS_HCU_OPERATION);
	ग_लिखोl(reg, hcu_dev->io_base + OCS_HCU_DMA_DMA_MODE);

	ग_लिखोl(OCS_HCU_TERMINATE, hcu_dev->io_base + OCS_HCU_OPERATION);

	rc = ocs_hcu_रुको_and_disable_irq(hcu_dev);
	अगर (rc)
		वापस rc;

	dma_unmap_single(dev, dma_handle, data_len, DMA_TO_DEVICE);

	वापस ocs_hcu_get_digest(hcu_dev, algo, dgst, dgst_len);
पूर्ण

/**
 * ocs_hcu_hmac() - Compute HMAC.
 * @hcu_dev:		The OCS HCU device to use.
 * @algo:		The hash algorithm to use with HMAC.
 * @key:		The key to use.
 * @dma_list:	The OCS DMA list mapping the input data to process.
 * @key_len:		The length of @key.
 * @dgst:		The buffer where to save the computed HMAC.
 * @dgst_len:		The length of @dgst.
 *
 * Return: 0 on success; negative error code otherwise.
 */
पूर्णांक ocs_hcu_hmac(काष्ठा ocs_hcu_dev *hcu_dev, क्रमागत ocs_hcu_algo algo,
		 स्थिर u8 *key, माप_प्रकार key_len,
		 स्थिर काष्ठा ocs_hcu_dma_list *dma_list,
		 u8 *dgst, माप_प्रकार dgst_len)
अणु
	पूर्णांक rc;

	/* Ensure 'key' is not शून्य. */
	अगर (!key || key_len == 0)
		वापस -EINVAL;

	/* Configure the hardware क्रम the current request. */
	rc = ocs_hcu_hw_cfg(hcu_dev, algo, true);
	अगर (rc)
		वापस rc;

	rc = ocs_hcu_ग_लिखो_key(hcu_dev, key, key_len);
	अगर (rc)
		वापस rc;

	rc = ocs_hcu_ll_dma_start(hcu_dev, dma_list, true);

	/* Clear HW key beक्रमe processing वापस code. */
	ocs_hcu_clear_key(hcu_dev);

	अगर (rc)
		वापस rc;

	वापस ocs_hcu_get_digest(hcu_dev, algo, dgst, dgst_len);
पूर्ण

irqवापस_t ocs_hcu_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ocs_hcu_dev *hcu_dev = dev_id;
	u32 hcu_irq;
	u32 dma_irq;

	/* Read and clear the HCU पूर्णांकerrupt. */
	hcu_irq = पढ़ोl(hcu_dev->io_base + OCS_HCU_ISR);
	ग_लिखोl(hcu_irq, hcu_dev->io_base + OCS_HCU_ISR);

	/* Read and clear the HCU DMA पूर्णांकerrupt. */
	dma_irq = पढ़ोl(hcu_dev->io_base + OCS_HCU_DMA_MSI_ISR);
	ग_लिखोl(dma_irq, hcu_dev->io_base + OCS_HCU_DMA_MSI_ISR);

	/* Check क्रम errors. */
	अगर (hcu_irq & HCU_IRQ_HASH_ERR_MASK || dma_irq & HCU_DMA_IRQ_ERR_MASK) अणु
		hcu_dev->irq_err = true;
		जाओ complete;
	पूर्ण

	/* Check क्रम DONE IRQs. */
	अगर (hcu_irq & HCU_IRQ_HASH_DONE || dma_irq & HCU_DMA_IRQ_SRC_DONE)
		जाओ complete;

	वापस IRQ_NONE;

complete:
	complete(&hcu_dev->irq_करोne);

	वापस IRQ_HANDLED;
पूर्ण

MODULE_LICENSE("GPL");
