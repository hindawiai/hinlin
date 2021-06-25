<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2018-2020 Linaro Ltd.
 */
#अगर_अघोषित _GSI_PRIVATE_H_
#घोषणा _GSI_PRIVATE_H_

/* === Only "gsi.c" and "gsi_trans.c" should include this file === */

#समावेश <linux/types.h>

काष्ठा gsi_trans;
काष्ठा gsi_ring;
काष्ठा gsi_channel;

#घोषणा GSI_RING_ELEMENT_SIZE	16	/* bytes; must be a घातer of 2 */

/* Return the entry that follows one provided in a transaction pool */
व्योम *gsi_trans_pool_next(काष्ठा gsi_trans_pool *pool, व्योम *element);

/**
 * gsi_trans_move_complete() - Mark a GSI transaction completed
 * @trans:	Transaction to commit
 */
व्योम gsi_trans_move_complete(काष्ठा gsi_trans *trans);

/**
 * gsi_trans_move_polled() - Mark a transaction polled
 * @trans:	Transaction to update
 */
व्योम gsi_trans_move_polled(काष्ठा gsi_trans *trans);

/**
 * gsi_trans_complete() - Complete a GSI transaction
 * @trans:	Transaction to complete
 *
 * Marks a transaction complete (including मुक्तing it).
 */
व्योम gsi_trans_complete(काष्ठा gsi_trans *trans);

/**
 * gsi_channel_trans_mapped() - Return a transaction mapped to a TRE index
 * @channel:	Channel associated with the transaction
 * @index:	Index of the TRE having a transaction
 *
 * Return:	The GSI transaction poपूर्णांकer associated with the TRE index
 */
काष्ठा gsi_trans *gsi_channel_trans_mapped(काष्ठा gsi_channel *channel,
					   u32 index);

/**
 * gsi_channel_trans_complete() - Return a channel's next completed transaction
 * @channel:	Channel whose next transaction is to be वापसed
 *
 * Return:	The next completed transaction, or शून्य अगर nothing new
 */
काष्ठा gsi_trans *gsi_channel_trans_complete(काष्ठा gsi_channel *channel);

/**
 * gsi_channel_trans_cancel_pending() - Cancel pending transactions
 * @channel:	Channel whose pending transactions should be cancelled
 *
 * Cancel all pending transactions on a channel.  These are transactions
 * that have been committed but not yet completed.  This is required when
 * the channel माला_लो reset.  At that समय all pending transactions will be
 * marked as cancelled.
 *
 * NOTE:  Transactions alपढ़ोy complete at the समय of this call are
 *	  unaffected.
 */
व्योम gsi_channel_trans_cancel_pending(काष्ठा gsi_channel *channel);

/**
 * gsi_channel_trans_init() - Initialize a channel's GSI transaction info
 * @gsi:	GSI poपूर्णांकer
 * @channel_id:	Channel number
 *
 * Return:	0 अगर successful, or -ENOMEM on allocation failure
 *
 * Creates and sets up inक्रमmation क्रम managing transactions on a channel
 */
पूर्णांक gsi_channel_trans_init(काष्ठा gsi *gsi, u32 channel_id);

/**
 * gsi_channel_trans_निकास() - Inverse of gsi_channel_trans_init()
 * @channel:	Channel whose transaction inक्रमmation is to be cleaned up
 */
व्योम gsi_channel_trans_निकास(काष्ठा gsi_channel *channel);

/**
 * gsi_channel_करोorbell() - Ring a channel's करोorbell
 * @channel:	Channel whose करोorbell should be rung
 *
 * Rings a channel's करोorbell to inक्रमm the GSI hardware that new
 * transactions (TREs, really) are available क्रम it to process.
 */
व्योम gsi_channel_करोorbell(काष्ठा gsi_channel *channel);

/**
 * gsi_ring_virt() - Return भव address क्रम a ring entry
 * @ring:	Ring whose address is to be translated
 * @index:	Index (slot number) of entry
 */
व्योम *gsi_ring_virt(काष्ठा gsi_ring *ring, u32 index);

/**
 * gsi_channel_tx_queued() - Report the number of bytes queued to hardware
 * @channel:	Channel whose bytes have been queued
 *
 * This arranges क्रम the the number of transactions and bytes क्रम
 * transfer that have been queued to hardware to be reported.  It
 * passes this inक्रमmation up the network stack so it can be used to
 * throttle transmissions.
 */
व्योम gsi_channel_tx_queued(काष्ठा gsi_channel *channel);

#पूर्ण_अगर /* _GSI_PRIVATE_H_ */
