<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2018
 */

#घोषणा KMSG_COMPONENT "qeth"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/ethtool.h>
#समावेश "qeth_core.h"


#घोषणा QETH_TXQ_STAT(_name, _stat) अणु \
	.name = _name, \
	.offset = दुरत्व(काष्ठा qeth_out_q_stats, _stat) \
पूर्ण

#घोषणा QETH_CARD_STAT(_name, _stat) अणु \
	.name = _name, \
	.offset = दुरत्व(काष्ठा qeth_card_stats, _stat) \
पूर्ण

काष्ठा qeth_stats अणु
	अक्षर name[ETH_GSTRING_LEN];
	अचिन्हित पूर्णांक offset;
पूर्ण;

अटल स्थिर काष्ठा qeth_stats txq_stats[] = अणु
	QETH_TXQ_STAT("IO buffers", bufs),
	QETH_TXQ_STAT("IO buffer elements", buf_elements),
	QETH_TXQ_STAT("packed IO buffers", bufs_pack),
	QETH_TXQ_STAT("skbs", tx_packets),
	QETH_TXQ_STAT("packed skbs", skbs_pack),
	QETH_TXQ_STAT("SG skbs", skbs_sg),
	QETH_TXQ_STAT("HW csum skbs", skbs_csum),
	QETH_TXQ_STAT("TSO skbs", skbs_tso),
	QETH_TXQ_STAT("linearized skbs", skbs_linearized),
	QETH_TXQ_STAT("linearized+error skbs", skbs_linearized_fail),
	QETH_TXQ_STAT("TSO bytes", tso_bytes),
	QETH_TXQ_STAT("Packing mode switches", packing_mode_चयन),
	QETH_TXQ_STAT("Queue stopped", stopped),
	QETH_TXQ_STAT("Doorbell", करोorbell),
	QETH_TXQ_STAT("IRQ for frames", coal_frames),
	QETH_TXQ_STAT("Completion yield", completion_yield),
	QETH_TXQ_STAT("Completion timer", completion_समयr),
पूर्ण;

अटल स्थिर काष्ठा qeth_stats card_stats[] = अणु
	QETH_CARD_STAT("rx0 IO buffers", rx_bufs),
	QETH_CARD_STAT("rx0 HW csum skbs", rx_skb_csum),
	QETH_CARD_STAT("rx0 SG skbs", rx_sg_skbs),
	QETH_CARD_STAT("rx0 SG page frags", rx_sg_frags),
	QETH_CARD_STAT("rx0 SG page allocs", rx_sg_alloc_page),
	QETH_CARD_STAT("rx0 dropped, no memory", rx_dropped_nomem),
	QETH_CARD_STAT("rx0 dropped, bad format", rx_dropped_notsupp),
	QETH_CARD_STAT("rx0 dropped, runt", rx_dropped_runt),
पूर्ण;

#घोषणा TXQ_STATS_LEN	ARRAY_SIZE(txq_stats)
#घोषणा CARD_STATS_LEN	ARRAY_SIZE(card_stats)

अटल व्योम qeth_add_stat_data(u64 **dst, व्योम *src,
			       स्थिर काष्ठा qeth_stats stats[],
			       अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक i;
	अक्षर *stat;

	क्रम (i = 0; i < size; i++) अणु
		stat = (अक्षर *)src + stats[i].offset;
		**dst = *(u64 *)stat;
		(*dst)++;
	पूर्ण
पूर्ण

अटल व्योम qeth_add_stat_strings(u8 **data, स्थिर अक्षर *prefix,
				  स्थिर काष्ठा qeth_stats stats[],
				  अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		snम_लिखो(*data, ETH_GSTRING_LEN, "%s%s", prefix, stats[i].name);
		*data += ETH_GSTRING_LEN;
	पूर्ण
पूर्ण

अटल पूर्णांक qeth_get_sset_count(काष्ठा net_device *dev, पूर्णांक stringset)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		वापस CARD_STATS_LEN +
		       card->qdio.no_out_queues * TXQ_STATS_LEN;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम qeth_get_ethtool_stats(काष्ठा net_device *dev,
				   काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;
	अचिन्हित पूर्णांक i;

	qeth_add_stat_data(&data, &card->stats, card_stats, CARD_STATS_LEN);
	क्रम (i = 0; i < card->qdio.no_out_queues; i++)
		qeth_add_stat_data(&data, &card->qdio.out_qs[i]->stats,
				   txq_stats, TXQ_STATS_LEN);
पूर्ण

अटल व्योम __qeth_set_coalesce(काष्ठा net_device *dev,
				काष्ठा qeth_qdio_out_q *queue,
				काष्ठा ethtool_coalesce *coal)
अणु
	WRITE_ONCE(queue->coalesce_usecs, coal->tx_coalesce_usecs);
	WRITE_ONCE(queue->max_coalesced_frames, coal->tx_max_coalesced_frames);

	अगर (coal->tx_coalesce_usecs &&
	    netअगर_running(dev) &&
	    !qeth_out_queue_is_empty(queue))
		qeth_tx_arm_समयr(queue, coal->tx_coalesce_usecs);
पूर्ण

अटल पूर्णांक qeth_set_coalesce(काष्ठा net_device *dev,
			     काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;
	काष्ठा qeth_qdio_out_q *queue;
	अचिन्हित पूर्णांक i;

	अगर (!IS_IQD(card))
		वापस -EOPNOTSUPP;

	अगर (!coal->tx_coalesce_usecs && !coal->tx_max_coalesced_frames)
		वापस -EINVAL;

	qeth_क्रम_each_output_queue(card, queue, i)
		__qeth_set_coalesce(dev, queue, coal);

	वापस 0;
पूर्ण

अटल व्योम qeth_get_ringparam(काष्ठा net_device *dev,
			       काष्ठा ethtool_ringparam *param)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;

	param->rx_max_pending = QDIO_MAX_BUFFERS_PER_Q;
	param->rx_mini_max_pending = 0;
	param->rx_jumbo_max_pending = 0;
	param->tx_max_pending = QDIO_MAX_BUFFERS_PER_Q;

	param->rx_pending = card->qdio.in_buf_pool.buf_count;
	param->rx_mini_pending = 0;
	param->rx_jumbo_pending = 0;
	param->tx_pending = QDIO_MAX_BUFFERS_PER_Q;
पूर्ण

अटल व्योम qeth_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;
	अक्षर prefix[ETH_GSTRING_LEN] = "";
	अचिन्हित पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		qeth_add_stat_strings(&data, prefix, card_stats,
				      CARD_STATS_LEN);
		क्रम (i = 0; i < card->qdio.no_out_queues; i++) अणु
			snम_लिखो(prefix, ETH_GSTRING_LEN, "tx%u ", i);
			qeth_add_stat_strings(&data, prefix, txq_stats,
					      TXQ_STATS_LEN);
		पूर्ण
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम qeth_get_drvinfo(काष्ठा net_device *dev,
			     काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;

	strlcpy(info->driver, IS_LAYER2(card) ? "qeth_l2" : "qeth_l3",
		माप(info->driver));
	strlcpy(info->fw_version, card->info.mcl_level,
		माप(info->fw_version));
	snम_लिखो(info->bus_info, माप(info->bus_info), "%s/%s/%s",
		 CARD_RDEV_ID(card), CARD_WDEV_ID(card), CARD_DDEV_ID(card));
पूर्ण

अटल व्योम qeth_get_channels(काष्ठा net_device *dev,
			      काष्ठा ethtool_channels *channels)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;

	channels->max_rx = dev->num_rx_queues;
	channels->max_tx = card->qdio.no_out_queues;
	channels->max_other = 0;
	channels->max_combined = 0;
	channels->rx_count = dev->real_num_rx_queues;
	channels->tx_count = dev->real_num_tx_queues;
	channels->other_count = 0;
	channels->combined_count = 0;
पूर्ण

अटल पूर्णांक qeth_set_channels(काष्ठा net_device *dev,
			     काष्ठा ethtool_channels *channels)
अणु
	काष्ठा qeth_priv *priv = netdev_priv(dev);
	काष्ठा qeth_card *card = dev->ml_priv;
	पूर्णांक rc;

	अगर (channels->rx_count == 0 || channels->tx_count == 0)
		वापस -EINVAL;
	अगर (channels->tx_count > card->qdio.no_out_queues)
		वापस -EINVAL;

	/* Prio-queueing needs all TX queues: */
	अगर (qeth_uses_tx_prio_queueing(card))
		वापस -EPERM;

	अगर (IS_IQD(card)) अणु
		अगर (channels->tx_count < QETH_IQD_MIN_TXQ)
			वापस -EINVAL;

		/* Reject करोwngrade जबतक running. It could push displaced
		 * ucast flows onto txq0, which is reserved क्रम mcast.
		 */
		अगर (netअगर_running(dev) &&
		    channels->tx_count < dev->real_num_tx_queues)
			वापस -EPERM;
	पूर्ण

	rc = qeth_set_real_num_tx_queues(card, channels->tx_count);
	अगर (!rc)
		priv->tx_wanted_queues = channels->tx_count;

	वापस rc;
पूर्ण

अटल पूर्णांक qeth_get_ts_info(काष्ठा net_device *dev,
			    काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;

	अगर (!IS_IQD(card))
		वापस -EOPNOTSUPP;

	वापस ethtool_op_get_ts_info(dev, info);
पूर्ण

अटल पूर्णांक qeth_get_tunable(काष्ठा net_device *dev,
			    स्थिर काष्ठा ethtool_tunable *tuna, व्योम *data)
अणु
	काष्ठा qeth_priv *priv = netdev_priv(dev);

	चयन (tuna->id) अणु
	हाल ETHTOOL_RX_COPYBREAK:
		*(u32 *)data = priv->rx_copyअवरोध;
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक qeth_set_tunable(काष्ठा net_device *dev,
			    स्थिर काष्ठा ethtool_tunable *tuna,
			    स्थिर व्योम *data)
अणु
	काष्ठा qeth_priv *priv = netdev_priv(dev);

	चयन (tuna->id) अणु
	हाल ETHTOOL_RX_COPYBREAK:
		WRITE_ONCE(priv->rx_copyअवरोध, *(u32 *)data);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक qeth_get_per_queue_coalesce(काष्ठा net_device *dev, u32 __queue,
				       काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;
	काष्ठा qeth_qdio_out_q *queue;

	अगर (!IS_IQD(card))
		वापस -EOPNOTSUPP;

	अगर (__queue >= card->qdio.no_out_queues)
		वापस -EINVAL;

	queue = card->qdio.out_qs[__queue];

	coal->tx_coalesce_usecs = queue->coalesce_usecs;
	coal->tx_max_coalesced_frames = queue->max_coalesced_frames;
	वापस 0;
पूर्ण

अटल पूर्णांक qeth_set_per_queue_coalesce(काष्ठा net_device *dev, u32 queue,
				       काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;

	अगर (!IS_IQD(card))
		वापस -EOPNOTSUPP;

	अगर (queue >= card->qdio.no_out_queues)
		वापस -EINVAL;

	अगर (!coal->tx_coalesce_usecs && !coal->tx_max_coalesced_frames)
		वापस -EINVAL;

	__qeth_set_coalesce(dev, card->qdio.out_qs[queue], coal);
	वापस 0;
पूर्ण

/* Helper function to fill 'advertising' and 'supported' which are the same. */
/* Autoneg and full-duplex are supported and advertised unconditionally.     */
/* Always advertise and support all speeds up to specअगरied, and only one     */
/* specअगरied port type.							     */
अटल व्योम qeth_set_ethtool_link_modes(काष्ठा ethtool_link_ksettings *cmd,
					क्रमागत qeth_link_mode link_mode)
अणु
	ethtool_link_ksettings_zero_link_mode(cmd, supported);
	ethtool_link_ksettings_zero_link_mode(cmd, advertising);
	ethtool_link_ksettings_zero_link_mode(cmd, lp_advertising);

	ethtool_link_ksettings_add_link_mode(cmd, supported, Autoneg);
	ethtool_link_ksettings_add_link_mode(cmd, advertising, Autoneg);

	चयन (cmd->base.port) अणु
	हाल PORT_TP:
		ethtool_link_ksettings_add_link_mode(cmd, supported, TP);
		ethtool_link_ksettings_add_link_mode(cmd, advertising, TP);

		चयन (cmd->base.speed) अणु
		हाल SPEED_10000:
			ethtool_link_ksettings_add_link_mode(cmd, supported,
							     10000baseT_Full);
			ethtool_link_ksettings_add_link_mode(cmd, advertising,
							     10000baseT_Full);
			fallthrough;
		हाल SPEED_1000:
			ethtool_link_ksettings_add_link_mode(cmd, supported,
							     1000baseT_Full);
			ethtool_link_ksettings_add_link_mode(cmd, advertising,
							     1000baseT_Full);
			ethtool_link_ksettings_add_link_mode(cmd, supported,
							     1000baseT_Half);
			ethtool_link_ksettings_add_link_mode(cmd, advertising,
							     1000baseT_Half);
			fallthrough;
		हाल SPEED_100:
			ethtool_link_ksettings_add_link_mode(cmd, supported,
							     100baseT_Full);
			ethtool_link_ksettings_add_link_mode(cmd, advertising,
							     100baseT_Full);
			ethtool_link_ksettings_add_link_mode(cmd, supported,
							     100baseT_Half);
			ethtool_link_ksettings_add_link_mode(cmd, advertising,
							     100baseT_Half);
			fallthrough;
		हाल SPEED_10:
			ethtool_link_ksettings_add_link_mode(cmd, supported,
							     10baseT_Full);
			ethtool_link_ksettings_add_link_mode(cmd, advertising,
							     10baseT_Full);
			ethtool_link_ksettings_add_link_mode(cmd, supported,
							     10baseT_Half);
			ethtool_link_ksettings_add_link_mode(cmd, advertising,
							     10baseT_Half);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अवरोध;
	हाल PORT_FIBRE:
		ethtool_link_ksettings_add_link_mode(cmd, supported, FIBRE);
		ethtool_link_ksettings_add_link_mode(cmd, advertising, FIBRE);

		चयन (cmd->base.speed) अणु
		हाल SPEED_25000:
			ethtool_link_ksettings_add_link_mode(cmd, supported,
							     25000baseSR_Full);
			ethtool_link_ksettings_add_link_mode(cmd, advertising,
							     25000baseSR_Full);
			अवरोध;
		हाल SPEED_10000:
			अगर (link_mode == QETH_LINK_MODE_FIBRE_LONG) अणु
				ethtool_link_ksettings_add_link_mode(cmd, supported,
								     10000baseLR_Full);
				ethtool_link_ksettings_add_link_mode(cmd, advertising,
								     10000baseLR_Full);
			पूर्ण अन्यथा अगर (link_mode == QETH_LINK_MODE_FIBRE_SHORT) अणु
				ethtool_link_ksettings_add_link_mode(cmd, supported,
								     10000baseSR_Full);
				ethtool_link_ksettings_add_link_mode(cmd, advertising,
								     10000baseSR_Full);
			पूर्ण
			अवरोध;
		हाल SPEED_1000:
			ethtool_link_ksettings_add_link_mode(cmd, supported,
							     1000baseX_Full);
			ethtool_link_ksettings_add_link_mode(cmd, advertising,
							     1000baseX_Full);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक qeth_get_link_ksettings(काष्ठा net_device *netdev,
				   काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा qeth_card *card = netdev->ml_priv;
	काष्ठा qeth_link_info link_info;

	cmd->base.speed = card->info.link_info.speed;
	cmd->base.duplex = card->info.link_info.duplex;
	cmd->base.port = card->info.link_info.port;
	cmd->base.स्वतःneg = AUTONEG_ENABLE;
	cmd->base.phy_address = 0;
	cmd->base.mdio_support = 0;
	cmd->base.eth_tp_mdix = ETH_TP_MDI_INVALID;
	cmd->base.eth_tp_mdix_ctrl = ETH_TP_MDI_INVALID;

	/* Check अगर we can obtain more accurate inक्रमmation.	 */
	अगर (!qeth_query_card_info(card, &link_info)) अणु
		अगर (link_info.speed != SPEED_UNKNOWN)
			cmd->base.speed = link_info.speed;
		अगर (link_info.duplex != DUPLEX_UNKNOWN)
			cmd->base.duplex = link_info.duplex;
		अगर (link_info.port != PORT_OTHER)
			cmd->base.port = link_info.port;
	पूर्ण

	qeth_set_ethtool_link_modes(cmd, card->info.link_info.link_mode);

	वापस 0;
पूर्ण

स्थिर काष्ठा ethtool_ops qeth_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_TX_USECS |
				     ETHTOOL_COALESCE_TX_MAX_FRAMES,
	.get_link = ethtool_op_get_link,
	.set_coalesce = qeth_set_coalesce,
	.get_ringparam = qeth_get_ringparam,
	.get_strings = qeth_get_strings,
	.get_ethtool_stats = qeth_get_ethtool_stats,
	.get_sset_count = qeth_get_sset_count,
	.get_drvinfo = qeth_get_drvinfo,
	.get_channels = qeth_get_channels,
	.set_channels = qeth_set_channels,
	.get_ts_info = qeth_get_ts_info,
	.get_tunable = qeth_get_tunable,
	.set_tunable = qeth_set_tunable,
	.get_per_queue_coalesce = qeth_get_per_queue_coalesce,
	.set_per_queue_coalesce = qeth_set_per_queue_coalesce,
	.get_link_ksettings = qeth_get_link_ksettings,
पूर्ण;

स्थिर काष्ठा ethtool_ops qeth_osn_ethtool_ops = अणु
	.get_strings = qeth_get_strings,
	.get_ethtool_stats = qeth_get_ethtool_stats,
	.get_sset_count = qeth_get_sset_count,
	.get_drvinfo = qeth_get_drvinfo,
पूर्ण;
