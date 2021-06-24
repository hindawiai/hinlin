<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2006-2013 Solarflare Communications Inc.
 */

#अगर_अघोषित EF4_EFX_H
#घोषणा EF4_EFX_H

#समावेश "net_driver.h"
#समावेश "filter.h"

/* All controllers use BAR 0 क्रम I/O space and BAR 2(&3) क्रम memory */
/* All VFs use BAR 0/1 क्रम memory */
#घोषणा EF4_MEM_BAR 2
#घोषणा EF4_MEM_VF_BAR 0

पूर्णांक ef4_net_खोलो(काष्ठा net_device *net_dev);
पूर्णांक ef4_net_stop(काष्ठा net_device *net_dev);

/* TX */
पूर्णांक ef4_probe_tx_queue(काष्ठा ef4_tx_queue *tx_queue);
व्योम ef4_हटाओ_tx_queue(काष्ठा ef4_tx_queue *tx_queue);
व्योम ef4_init_tx_queue(काष्ठा ef4_tx_queue *tx_queue);
व्योम ef4_init_tx_queue_core_txq(काष्ठा ef4_tx_queue *tx_queue);
व्योम ef4_fini_tx_queue(काष्ठा ef4_tx_queue *tx_queue);
netdev_tx_t ef4_hard_start_xmit(काष्ठा sk_buff *skb,
				काष्ठा net_device *net_dev);
netdev_tx_t ef4_enqueue_skb(काष्ठा ef4_tx_queue *tx_queue, काष्ठा sk_buff *skb);
व्योम ef4_xmit_करोne(काष्ठा ef4_tx_queue *tx_queue, अचिन्हित पूर्णांक index);
पूर्णांक ef4_setup_tc(काष्ठा net_device *net_dev, क्रमागत tc_setup_type type,
		 व्योम *type_data);
अचिन्हित पूर्णांक ef4_tx_max_skb_descs(काष्ठा ef4_nic *efx);
बाह्य bool ef4_separate_tx_channels;

/* RX */
व्योम ef4_set_शेष_rx_indir_table(काष्ठा ef4_nic *efx);
व्योम ef4_rx_config_page_split(काष्ठा ef4_nic *efx);
पूर्णांक ef4_probe_rx_queue(काष्ठा ef4_rx_queue *rx_queue);
व्योम ef4_हटाओ_rx_queue(काष्ठा ef4_rx_queue *rx_queue);
व्योम ef4_init_rx_queue(काष्ठा ef4_rx_queue *rx_queue);
व्योम ef4_fini_rx_queue(काष्ठा ef4_rx_queue *rx_queue);
व्योम ef4_fast_push_rx_descriptors(काष्ठा ef4_rx_queue *rx_queue, bool atomic);
व्योम ef4_rx_slow_fill(काष्ठा समयr_list *t);
व्योम __ef4_rx_packet(काष्ठा ef4_channel *channel);
व्योम ef4_rx_packet(काष्ठा ef4_rx_queue *rx_queue, अचिन्हित पूर्णांक index,
		   अचिन्हित पूर्णांक n_frags, अचिन्हित पूर्णांक len, u16 flags);
अटल अंतरभूत व्योम ef4_rx_flush_packet(काष्ठा ef4_channel *channel)
अणु
	अगर (channel->rx_pkt_n_frags)
		__ef4_rx_packet(channel);
पूर्ण
व्योम ef4_schedule_slow_fill(काष्ठा ef4_rx_queue *rx_queue);

#घोषणा EF4_MAX_DMAQ_SIZE 4096UL
#घोषणा EF4_DEFAULT_DMAQ_SIZE 1024UL
#घोषणा EF4_MIN_DMAQ_SIZE 512UL

#घोषणा EF4_MAX_EVQ_SIZE 16384UL
#घोषणा EF4_MIN_EVQ_SIZE 512UL

/* Maximum number of TCP segments we support क्रम soft-TSO */
#घोषणा EF4_TSO_MAX_SEGS	100

/* The smallest [rt]xq_entries that the driver supports.  RX minimum
 * is a bit arbitrary.  For TX, we must have space क्रम at least 2
 * TSO skbs.
 */
#घोषणा EF4_RXQ_MIN_ENT		128U
#घोषणा EF4_TXQ_MIN_ENT(efx)	(2 * ef4_tx_max_skb_descs(efx))

अटल अंतरभूत bool ef4_rss_enabled(काष्ठा ef4_nic *efx)
अणु
	वापस efx->rss_spपढ़ो > 1;
पूर्ण

/* Filters */

व्योम ef4_mac_reconfigure(काष्ठा ef4_nic *efx);

/**
 * ef4_filter_insert_filter - add or replace a filter
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
 * 3. If !ef4_filter_is_mc_recipient(@spec), or the NIC करोes not
 *    support delivery to multiple recipients, वापस -%EEXIST.
 *
 * This implies that filters क्रम multiple multicast recipients must
 * all be inserted with the same priority and @replace_equal = %false.
 */
अटल अंतरभूत s32 ef4_filter_insert_filter(काष्ठा ef4_nic *efx,
					   काष्ठा ef4_filter_spec *spec,
					   bool replace_equal)
अणु
	वापस efx->type->filter_insert(efx, spec, replace_equal);
पूर्ण

/**
 * ef4_filter_हटाओ_id_safe - हटाओ a filter by ID, carefully
 * @efx: NIC from which to हटाओ the filter
 * @priority: Priority of filter, as passed to @ef4_filter_insert_filter
 * @filter_id: ID of filter, as वापसed by @ef4_filter_insert_filter
 *
 * This function will range-check @filter_id, so it is safe to call
 * with a value passed from userland.
 */
अटल अंतरभूत पूर्णांक ef4_filter_हटाओ_id_safe(काष्ठा ef4_nic *efx,
					    क्रमागत ef4_filter_priority priority,
					    u32 filter_id)
अणु
	वापस efx->type->filter_हटाओ_safe(efx, priority, filter_id);
पूर्ण

/**
 * ef4_filter_get_filter_safe - retrieve a filter by ID, carefully
 * @efx: NIC from which to हटाओ the filter
 * @priority: Priority of filter, as passed to @ef4_filter_insert_filter
 * @filter_id: ID of filter, as वापसed by @ef4_filter_insert_filter
 * @spec: Buffer in which to store filter specअगरication
 *
 * This function will range-check @filter_id, so it is safe to call
 * with a value passed from userland.
 */
अटल अंतरभूत पूर्णांक
ef4_filter_get_filter_safe(काष्ठा ef4_nic *efx,
			   क्रमागत ef4_filter_priority priority,
			   u32 filter_id, काष्ठा ef4_filter_spec *spec)
अणु
	वापस efx->type->filter_get_safe(efx, priority, filter_id, spec);
पूर्ण

अटल अंतरभूत u32 ef4_filter_count_rx_used(काष्ठा ef4_nic *efx,
					   क्रमागत ef4_filter_priority priority)
अणु
	वापस efx->type->filter_count_rx_used(efx, priority);
पूर्ण
अटल अंतरभूत u32 ef4_filter_get_rx_id_limit(काष्ठा ef4_nic *efx)
अणु
	वापस efx->type->filter_get_rx_id_limit(efx);
पूर्ण
अटल अंतरभूत s32 ef4_filter_get_rx_ids(काष्ठा ef4_nic *efx,
					क्रमागत ef4_filter_priority priority,
					u32 *buf, u32 size)
अणु
	वापस efx->type->filter_get_rx_ids(efx, priority, buf, size);
पूर्ण
#अगर_घोषित CONFIG_RFS_ACCEL
पूर्णांक ef4_filter_rfs(काष्ठा net_device *net_dev, स्थिर काष्ठा sk_buff *skb,
		   u16 rxq_index, u32 flow_id);
bool __ef4_filter_rfs_expire(काष्ठा ef4_nic *efx, अचिन्हित quota);
अटल अंतरभूत व्योम ef4_filter_rfs_expire(काष्ठा ef4_channel *channel)
अणु
	अगर (channel->rfs_filters_added >= 60 &&
	    __ef4_filter_rfs_expire(channel->efx, 100))
		channel->rfs_filters_added -= 60;
पूर्ण
#घोषणा ef4_filter_rfs_enabled() 1
#अन्यथा
अटल अंतरभूत व्योम ef4_filter_rfs_expire(काष्ठा ef4_channel *channel) अणुपूर्ण
#घोषणा ef4_filter_rfs_enabled() 0
#पूर्ण_अगर
bool ef4_filter_is_mc_recipient(स्थिर काष्ठा ef4_filter_spec *spec);

/* Channels */
पूर्णांक ef4_channel_dummy_op_पूर्णांक(काष्ठा ef4_channel *channel);
व्योम ef4_channel_dummy_op_व्योम(काष्ठा ef4_channel *channel);
पूर्णांक ef4_पुनः_स्मृति_channels(काष्ठा ef4_nic *efx, u32 rxq_entries, u32 txq_entries);

/* Ports */
पूर्णांक ef4_reconfigure_port(काष्ठा ef4_nic *efx);
पूर्णांक __ef4_reconfigure_port(काष्ठा ef4_nic *efx);

/* Ethtool support */
बाह्य स्थिर काष्ठा ethtool_ops ef4_ethtool_ops;

/* Reset handling */
पूर्णांक ef4_reset(काष्ठा ef4_nic *efx, क्रमागत reset_type method);
व्योम ef4_reset_करोwn(काष्ठा ef4_nic *efx, क्रमागत reset_type method);
पूर्णांक ef4_reset_up(काष्ठा ef4_nic *efx, क्रमागत reset_type method, bool ok);
पूर्णांक ef4_try_recovery(काष्ठा ef4_nic *efx);

/* Global */
व्योम ef4_schedule_reset(काष्ठा ef4_nic *efx, क्रमागत reset_type type);
अचिन्हित पूर्णांक ef4_usecs_to_ticks(काष्ठा ef4_nic *efx, अचिन्हित पूर्णांक usecs);
अचिन्हित पूर्णांक ef4_ticks_to_usecs(काष्ठा ef4_nic *efx, अचिन्हित पूर्णांक ticks);
पूर्णांक ef4_init_irq_moderation(काष्ठा ef4_nic *efx, अचिन्हित पूर्णांक tx_usecs,
			    अचिन्हित पूर्णांक rx_usecs, bool rx_adaptive,
			    bool rx_may_override_tx);
व्योम ef4_get_irq_moderation(काष्ठा ef4_nic *efx, अचिन्हित पूर्णांक *tx_usecs,
			    अचिन्हित पूर्णांक *rx_usecs, bool *rx_adaptive);
व्योम ef4_stop_eventq(काष्ठा ef4_channel *channel);
व्योम ef4_start_eventq(काष्ठा ef4_channel *channel);

/* Dummy PHY ops क्रम PHY drivers */
पूर्णांक ef4_port_dummy_op_पूर्णांक(काष्ठा ef4_nic *efx);
व्योम ef4_port_dummy_op_व्योम(काष्ठा ef4_nic *efx);

/* Update the generic software stats in the passed stats array */
व्योम ef4_update_sw_stats(काष्ठा ef4_nic *efx, u64 *stats);

/* MTD */
#अगर_घोषित CONFIG_SFC_FALCON_MTD
पूर्णांक ef4_mtd_add(काष्ठा ef4_nic *efx, काष्ठा ef4_mtd_partition *parts,
		माप_प्रकार n_parts, माप_प्रकार माप_part);
अटल अंतरभूत पूर्णांक ef4_mtd_probe(काष्ठा ef4_nic *efx)
अणु
	वापस efx->type->mtd_probe(efx);
पूर्ण
व्योम ef4_mtd_नाम(काष्ठा ef4_nic *efx);
व्योम ef4_mtd_हटाओ(काष्ठा ef4_nic *efx);
#अन्यथा
अटल अंतरभूत पूर्णांक ef4_mtd_probe(काष्ठा ef4_nic *efx) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ef4_mtd_नाम(काष्ठा ef4_nic *efx) अणुपूर्ण
अटल अंतरभूत व्योम ef4_mtd_हटाओ(काष्ठा ef4_nic *efx) अणुपूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम ef4_schedule_channel(काष्ठा ef4_channel *channel)
अणु
	netअगर_vdbg(channel->efx, पूर्णांकr, channel->efx->net_dev,
		   "channel %d scheduling NAPI poll on CPU%d\n",
		   channel->channel, raw_smp_processor_id());

	napi_schedule(&channel->napi_str);
पूर्ण

अटल अंतरभूत व्योम ef4_schedule_channel_irq(काष्ठा ef4_channel *channel)
अणु
	channel->event_test_cpu = raw_smp_processor_id();
	ef4_schedule_channel(channel);
पूर्ण

व्योम ef4_link_status_changed(काष्ठा ef4_nic *efx);
व्योम ef4_link_set_advertising(काष्ठा ef4_nic *efx, u32);
व्योम ef4_link_set_wanted_fc(काष्ठा ef4_nic *efx, u8);

अटल अंतरभूत व्योम ef4_device_detach_sync(काष्ठा ef4_nic *efx)
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

अटल अंतरभूत bool ef4_rwsem_निश्चित_ग_लिखो_locked(काष्ठा rw_semaphore *sem)
अणु
	अगर (WARN_ON(करोwn_पढ़ो_trylock(sem))) अणु
		up_पढ़ो(sem);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

#पूर्ण_अगर /* EF4_EFX_H */
