<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2006-2013 Solarflare Communications Inc.
 */

#अगर_अघोषित EFX_EFX_H
#घोषणा EFX_EFX_H

#समावेश <linux/indirect_call_wrapper.h>
#समावेश "net_driver.h"
#समावेश "ef100_rx.h"
#समावेश "ef100_tx.h"
#समावेश "filter.h"

पूर्णांक efx_net_खोलो(काष्ठा net_device *net_dev);
पूर्णांक efx_net_stop(काष्ठा net_device *net_dev);

/* TX */
व्योम efx_init_tx_queue_core_txq(काष्ठा efx_tx_queue *tx_queue);
netdev_tx_t efx_hard_start_xmit(काष्ठा sk_buff *skb,
				काष्ठा net_device *net_dev);
netdev_tx_t __efx_enqueue_skb(काष्ठा efx_tx_queue *tx_queue, काष्ठा sk_buff *skb);
अटल अंतरभूत netdev_tx_t efx_enqueue_skb(काष्ठा efx_tx_queue *tx_queue, काष्ठा sk_buff *skb)
अणु
	वापस INसूचीECT_CALL_2(tx_queue->efx->type->tx_enqueue,
			       ef100_enqueue_skb, __efx_enqueue_skb,
			       tx_queue, skb);
पूर्ण
व्योम efx_xmit_करोne(काष्ठा efx_tx_queue *tx_queue, अचिन्हित पूर्णांक index);
व्योम efx_xmit_करोne_single(काष्ठा efx_tx_queue *tx_queue);
पूर्णांक efx_setup_tc(काष्ठा net_device *net_dev, क्रमागत tc_setup_type type,
		 व्योम *type_data);
बाह्य अचिन्हित पूर्णांक efx_piobuf_size;

/* RX */
व्योम __efx_rx_packet(काष्ठा efx_channel *channel);
व्योम efx_rx_packet(काष्ठा efx_rx_queue *rx_queue, अचिन्हित पूर्णांक index,
		   अचिन्हित पूर्णांक n_frags, अचिन्हित पूर्णांक len, u16 flags);
अटल अंतरभूत व्योम efx_rx_flush_packet(काष्ठा efx_channel *channel)
अणु
	अगर (channel->rx_pkt_n_frags)
		INसूचीECT_CALL_2(channel->efx->type->rx_packet,
				__ef100_rx_packet, __efx_rx_packet,
				channel);
पूर्ण
अटल अंतरभूत bool efx_rx_buf_hash_valid(काष्ठा efx_nic *efx, स्थिर u8 *prefix)
अणु
	अगर (efx->type->rx_buf_hash_valid)
		वापस INसूचीECT_CALL_1(efx->type->rx_buf_hash_valid,
				       ef100_rx_buf_hash_valid,
				       prefix);
	वापस true;
पूर्ण

/* Maximum number of TCP segments we support क्रम soft-TSO */
#घोषणा EFX_TSO_MAX_SEGS	100

/* The smallest [rt]xq_entries that the driver supports.  RX minimum
 * is a bit arbitrary.  For TX, we must have space क्रम at least 2
 * TSO skbs.
 */
#घोषणा EFX_RXQ_MIN_ENT		128U
#घोषणा EFX_TXQ_MIN_ENT(efx)	(2 * efx_tx_max_skb_descs(efx))

/* All EF10 architecture NICs steal one bit of the DMAQ size क्रम various
 * other purposes when counting TxQ entries, so we halve the queue size.
 */
#घोषणा EFX_TXQ_MAX_ENT(efx)	(EFX_WORKAROUND_EF10(efx) ? \
				 EFX_MAX_DMAQ_SIZE / 2 : EFX_MAX_DMAQ_SIZE)

अटल अंतरभूत bool efx_rss_enabled(काष्ठा efx_nic *efx)
अणु
	वापस efx->rss_spपढ़ो > 1;
पूर्ण

/* Filters */

/**
 * efx_filter_insert_filter - add or replace a filter
 * @efx: NIC in which to insert the filter
 * @spec: Specअगरication क्रम the filter
 * @replace_equal: Flag क्रम whether the specअगरied filter may replace an
 *	existing filter with equal priority
 *
 * On success, वापस the filter ID.
 * On failure, वापस a negative error code.
 *
 * If existing filters have equal match values to the new filter spec,
 * then the new filter might replace them or the function might fail,
 * as follows.
 *
 * 1. If the existing filters have lower priority, or @replace_equal
 *    is set and they have equal priority, replace them.
 *
 * 2. If the existing filters have higher priority, वापस -%EPERM.
 *
 * 3. If !efx_filter_is_mc_recipient(@spec), or the NIC करोes not
 *    support delivery to multiple recipients, वापस -%EEXIST.
 *
 * This implies that filters क्रम multiple multicast recipients must
 * all be inserted with the same priority and @replace_equal = %false.
 */
अटल अंतरभूत s32 efx_filter_insert_filter(काष्ठा efx_nic *efx,
					   काष्ठा efx_filter_spec *spec,
					   bool replace_equal)
अणु
	वापस efx->type->filter_insert(efx, spec, replace_equal);
पूर्ण

/**
 * efx_filter_हटाओ_id_safe - हटाओ a filter by ID, carefully
 * @efx: NIC from which to हटाओ the filter
 * @priority: Priority of filter, as passed to @efx_filter_insert_filter
 * @filter_id: ID of filter, as वापसed by @efx_filter_insert_filter
 *
 * This function will range-check @filter_id, so it is safe to call
 * with a value passed from userland.
 */
अटल अंतरभूत पूर्णांक efx_filter_हटाओ_id_safe(काष्ठा efx_nic *efx,
					    क्रमागत efx_filter_priority priority,
					    u32 filter_id)
अणु
	वापस efx->type->filter_हटाओ_safe(efx, priority, filter_id);
पूर्ण

/**
 * efx_filter_get_filter_safe - retrieve a filter by ID, carefully
 * @efx: NIC from which to हटाओ the filter
 * @priority: Priority of filter, as passed to @efx_filter_insert_filter
 * @filter_id: ID of filter, as वापसed by @efx_filter_insert_filter
 * @spec: Buffer in which to store filter specअगरication
 *
 * This function will range-check @filter_id, so it is safe to call
 * with a value passed from userland.
 */
अटल अंतरभूत पूर्णांक
efx_filter_get_filter_safe(काष्ठा efx_nic *efx,
			   क्रमागत efx_filter_priority priority,
			   u32 filter_id, काष्ठा efx_filter_spec *spec)
अणु
	वापस efx->type->filter_get_safe(efx, priority, filter_id, spec);
पूर्ण

अटल अंतरभूत u32 efx_filter_count_rx_used(काष्ठा efx_nic *efx,
					   क्रमागत efx_filter_priority priority)
अणु
	वापस efx->type->filter_count_rx_used(efx, priority);
पूर्ण
अटल अंतरभूत u32 efx_filter_get_rx_id_limit(काष्ठा efx_nic *efx)
अणु
	वापस efx->type->filter_get_rx_id_limit(efx);
पूर्ण
अटल अंतरभूत s32 efx_filter_get_rx_ids(काष्ठा efx_nic *efx,
					क्रमागत efx_filter_priority priority,
					u32 *buf, u32 size)
अणु
	वापस efx->type->filter_get_rx_ids(efx, priority, buf, size);
पूर्ण

/* RSS contexts */
अटल अंतरभूत bool efx_rss_active(काष्ठा efx_rss_context *ctx)
अणु
	वापस ctx->context_id != EFX_MCDI_RSS_CONTEXT_INVALID;
पूर्ण

/* Ethtool support */
बाह्य स्थिर काष्ठा ethtool_ops efx_ethtool_ops;

/* Global */
अचिन्हित पूर्णांक efx_usecs_to_ticks(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक usecs);
अचिन्हित पूर्णांक efx_ticks_to_usecs(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक ticks);
पूर्णांक efx_init_irq_moderation(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक tx_usecs,
			    अचिन्हित पूर्णांक rx_usecs, bool rx_adaptive,
			    bool rx_may_override_tx);
व्योम efx_get_irq_moderation(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक *tx_usecs,
			    अचिन्हित पूर्णांक *rx_usecs, bool *rx_adaptive);

/* Update the generic software stats in the passed stats array */
व्योम efx_update_sw_stats(काष्ठा efx_nic *efx, u64 *stats);

/* MTD */
#अगर_घोषित CONFIG_SFC_MTD
पूर्णांक efx_mtd_add(काष्ठा efx_nic *efx, काष्ठा efx_mtd_partition *parts,
		माप_प्रकार n_parts, माप_प्रकार माप_part);
अटल अंतरभूत पूर्णांक efx_mtd_probe(काष्ठा efx_nic *efx)
अणु
	वापस efx->type->mtd_probe(efx);
पूर्ण
व्योम efx_mtd_नाम(काष्ठा efx_nic *efx);
व्योम efx_mtd_हटाओ(काष्ठा efx_nic *efx);
#अन्यथा
अटल अंतरभूत पूर्णांक efx_mtd_probe(काष्ठा efx_nic *efx) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम efx_mtd_नाम(काष्ठा efx_nic *efx) अणुपूर्ण
अटल अंतरभूत व्योम efx_mtd_हटाओ(काष्ठा efx_nic *efx) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SFC_SRIOV
अटल अंतरभूत अचिन्हित पूर्णांक efx_vf_size(काष्ठा efx_nic *efx)
अणु
	वापस 1 << efx->vi_scale;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम efx_device_detach_sync(काष्ठा efx_nic *efx)
अणु
	काष्ठा net_device *dev = efx->net_dev;

	/* Lock/मुक्तze all TX queues so that we can be sure the
	 * TX scheduler is stopped when we're करोne and beक्रमe
	 * netअगर_device_present() becomes false.
	 */
	netअगर_tx_lock_bh(dev);
	netअगर_device_detach(dev);
	netअगर_tx_unlock_bh(dev);
पूर्ण

अटल अंतरभूत व्योम efx_device_attach_अगर_not_resetting(काष्ठा efx_nic *efx)
अणु
	अगर ((efx->state != STATE_DISABLED) && !efx->reset_pending)
		netअगर_device_attach(efx->net_dev);
पूर्ण

अटल अंतरभूत bool efx_rwsem_निश्चित_ग_लिखो_locked(काष्ठा rw_semaphore *sem)
अणु
	अगर (WARN_ON(करोwn_पढ़ो_trylock(sem))) अणु
		up_पढ़ो(sem);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

पूर्णांक efx_xdp_tx_buffers(काष्ठा efx_nic *efx, पूर्णांक n, काष्ठा xdp_frame **xdpfs,
		       bool flush);

#पूर्ण_अगर /* EFX_EFX_H */
