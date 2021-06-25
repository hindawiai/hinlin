<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2019-2020 Linaro Ltd.
 */
#अगर_अघोषित _GSI_TRANS_H_
#घोषणा _GSI_TRANS_H_

#समावेश <linux/types.h>
#समावेश <linux/refcount.h>
#समावेश <linux/completion.h>
#समावेश <linux/dma-direction.h>

#समावेश "ipa_cmd.h"

काष्ठा page;
काष्ठा scatterlist;
काष्ठा device;
काष्ठा sk_buff;

काष्ठा gsi;
काष्ठा gsi_trans;
काष्ठा gsi_trans_pool;

/**
 * काष्ठा gsi_trans - a GSI transaction
 *
 * Most fields in this काष्ठाure क्रम पूर्णांकernal use by the transaction core code:
 * @links:	Links क्रम channel transaction lists by state
 * @gsi:	GSI poपूर्णांकer
 * @channel_id: Channel number transaction is associated with
 * @cancelled:	If set by the core code, transaction was cancelled
 * @tre_count:	Number of TREs reserved क्रम this transaction
 * @used:	Number of TREs *used* (could be less than tre_count)
 * @len:	Total # of transfer bytes represented in sgl[] (set by core)
 * @data:	Preserved but not touched by the core transaction code
 * @sgl:	An array of scatter/gather entries managed by core code
 * @info:	Array of command inक्रमmation काष्ठाures (command channel)
 * @direction:	DMA transfer direction (DMA_NONE क्रम commands)
 * @refcount:	Reference count used क्रम deकाष्ठाion
 * @completion:	Completed when the transaction completes
 * @byte_count:	TX channel byte count recorded when transaction committed
 * @trans_count: Channel transaction count when committed (क्रम BQL accounting)
 *
 * The size used क्रम some fields in this काष्ठाure were chosen to ensure
 * the full काष्ठाure size is no larger than 128 bytes.
 */
काष्ठा gsi_trans अणु
	काष्ठा list_head links;		/* gsi_channel lists */

	काष्ठा gsi *gsi;
	u8 channel_id;

	bool cancelled;			/* true अगर transaction was cancelled */

	u8 tre_count;			/* # TREs requested */
	u8 used;			/* # entries used in sgl[] */
	u32 len;			/* total # bytes across sgl[] */

	व्योम *data;
	काष्ठा scatterlist *sgl;
	काष्ठा ipa_cmd_info *info;	/* array of entries, or null */
	क्रमागत dma_data_direction direction;

	refcount_t refcount;
	काष्ठा completion completion;

	u64 byte_count;			/* channel byte_count when committed */
	u64 trans_count;		/* channel trans_count when committed */
पूर्ण;

/**
 * gsi_trans_pool_init() - Initialize a pool of काष्ठाures क्रम transactions
 * @pool:	GSI transaction poll poपूर्णांकer
 * @size:	Size of elements in the pool
 * @count:	Minimum number of elements in the pool
 * @max_alloc:	Maximum number of elements allocated at a समय from pool
 *
 * Return:	0 अगर successful, or a negative error code
 */
पूर्णांक gsi_trans_pool_init(काष्ठा gsi_trans_pool *pool, माप_प्रकार size, u32 count,
			u32 max_alloc);

/**
 * gsi_trans_pool_alloc() - Allocate one or more elements from a pool
 * @pool:	Pool poपूर्णांकer
 * @count:	Number of elements to allocate from the pool
 *
 * Return:	Virtual address of element(s) allocated from the pool
 */
व्योम *gsi_trans_pool_alloc(काष्ठा gsi_trans_pool *pool, u32 count);

/**
 * gsi_trans_pool_निकास() - Inverse of gsi_trans_pool_init()
 * @pool:	Pool poपूर्णांकer
 */
व्योम gsi_trans_pool_निकास(काष्ठा gsi_trans_pool *pool);

/**
 * gsi_trans_pool_init_dma() - Initialize a pool of DMA-able काष्ठाures
 * @dev:	Device used क्रम DMA
 * @pool:	Pool poपूर्णांकer
 * @size:	Size of elements in the pool
 * @count:	Minimum number of elements in the pool
 * @max_alloc:	Maximum number of elements allocated at a समय from pool
 *
 * Return:	0 अगर successful, or a negative error code
 *
 * Structures in this pool reside in DMA-coherent memory.
 */
पूर्णांक gsi_trans_pool_init_dma(काष्ठा device *dev, काष्ठा gsi_trans_pool *pool,
			    माप_प्रकार size, u32 count, u32 max_alloc);

/**
 * gsi_trans_pool_alloc_dma() - Allocate an element from a DMA pool
 * @pool:	DMA pool poपूर्णांकer
 * @addr:	DMA address "handle" associated with the allocation
 *
 * Return:	Virtual address of element allocated from the pool
 *
 * Only one element at a समय may be allocated from a DMA pool.
 */
व्योम *gsi_trans_pool_alloc_dma(काष्ठा gsi_trans_pool *pool, dma_addr_t *addr);

/**
 * gsi_trans_pool_निकास_dma() - Inverse of gsi_trans_pool_init_dma()
 * @dev:	Device used क्रम DMA
 * @pool:	Pool poपूर्णांकer
 */
व्योम gsi_trans_pool_निकास_dma(काष्ठा device *dev, काष्ठा gsi_trans_pool *pool);

/**
 * gsi_channel_trans_alloc() - Allocate a GSI transaction on a channel
 * @gsi:	GSI poपूर्णांकer
 * @channel_id:	Channel the transaction is associated with
 * @tre_count:	Number of elements in the transaction
 * @direction:	DMA direction क्रम entire SGL (or DMA_NONE)
 *
 * Return:	A GSI transaction काष्ठाure, or a null poपूर्णांकer अगर all
 *		available transactions are in use
 */
काष्ठा gsi_trans *gsi_channel_trans_alloc(काष्ठा gsi *gsi, u32 channel_id,
					  u32 tre_count,
					  क्रमागत dma_data_direction direction);

/**
 * gsi_trans_मुक्त() - Free a previously-allocated GSI transaction
 * @trans:	Transaction to be मुक्तd
 */
व्योम gsi_trans_मुक्त(काष्ठा gsi_trans *trans);

/**
 * gsi_trans_cmd_add() - Add an immediate command to a transaction
 * @trans:	Transaction
 * @buf:	Buffer poपूर्णांकer क्रम command payload
 * @size:	Number of bytes in buffer
 * @addr:	DMA address क्रम payload
 * @direction:	Direction of DMA transfer (or DMA_NONE अगर none required)
 * @opcode:	IPA immediate command opcode
 */
व्योम gsi_trans_cmd_add(काष्ठा gsi_trans *trans, व्योम *buf, u32 size,
		       dma_addr_t addr, क्रमागत dma_data_direction direction,
		       क्रमागत ipa_cmd_opcode opcode);

/**
 * gsi_trans_page_add() - Add a page transfer to a transaction
 * @trans:	Transaction
 * @page:	Page poपूर्णांकer
 * @size:	Number of bytes (starting at offset) to transfer
 * @offset:	Offset within page क्रम start of transfer
 */
पूर्णांक gsi_trans_page_add(काष्ठा gsi_trans *trans, काष्ठा page *page, u32 size,
		       u32 offset);

/**
 * gsi_trans_skb_add() - Add a socket transfer to a transaction
 * @trans:	Transaction
 * @skb:	Socket buffer क्रम transfer (outbound)
 *
 * Return:	0, or -EMSGSIZE अगर socket data won't fit in transaction.
 */
पूर्णांक gsi_trans_skb_add(काष्ठा gsi_trans *trans, काष्ठा sk_buff *skb);

/**
 * gsi_trans_commit() - Commit a GSI transaction
 * @trans:	Transaction to commit
 * @ring_db:	Whether to tell the hardware about these queued transfers
 */
व्योम gsi_trans_commit(काष्ठा gsi_trans *trans, bool ring_db);

/**
 * gsi_trans_commit_रुको() - Commit a GSI transaction and रुको क्रम it
 *			     to complete
 * @trans:	Transaction to commit
 */
व्योम gsi_trans_commit_रुको(काष्ठा gsi_trans *trans);

/**
 * gsi_trans_commit_रुको_समयout() - Commit a GSI transaction and रुको क्रम
 *				     it to complete, with समयout
 * @trans:	Transaction to commit
 * @समयout:	Timeout period (in milliseconds)
 */
पूर्णांक gsi_trans_commit_रुको_समयout(काष्ठा gsi_trans *trans,
				  अचिन्हित दीर्घ समयout);

/**
 * gsi_trans_पढ़ो_byte() - Issue a single byte पढ़ो TRE on a channel
 * @gsi:	GSI poपूर्णांकer
 * @channel_id:	Channel on which to पढ़ो a byte
 * @addr:	DMA address पूर्णांकo which to transfer the one byte
 *
 * This is not a transaction operation at all.  It's defined here because
 * it needs to be करोne in coordination with other transaction activity.
 */
पूर्णांक gsi_trans_पढ़ो_byte(काष्ठा gsi *gsi, u32 channel_id, dma_addr_t addr);

/**
 * gsi_trans_पढ़ो_byte_करोne() - Clean up after a single byte पढ़ो TRE
 * @gsi:	GSI poपूर्णांकer
 * @channel_id:	Channel on which byte was पढ़ो
 *
 * This function needs to be called to संकेत that the work related
 * to पढ़ोing a byte initiated by gsi_trans_पढ़ो_byte() is complete.
 */
व्योम gsi_trans_पढ़ो_byte_करोne(काष्ठा gsi *gsi, u32 channel_id);

#पूर्ण_अगर /* _GSI_TRANS_H_ */
