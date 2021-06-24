<शैली गुरु>
/*
 * Copyright (c) 2007 Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */


#समावेश <linux/अगर_vlan.h>

#समावेश <linux/mlx4/device.h>
#समावेश <linux/mlx4/cmd.h>

#समावेश "en_port.h"
#समावेश "mlx4_en.h"


पूर्णांक mlx4_SET_VLAN_FLTR(काष्ठा mlx4_dev *dev, काष्ठा mlx4_en_priv *priv)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_set_vlan_fltr_mbox *filter;
	पूर्णांक i;
	पूर्णांक j;
	पूर्णांक index = 0;
	u32 entry;
	पूर्णांक err = 0;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	filter = mailbox->buf;
	क्रम (i = VLAN_FLTR_SIZE - 1; i >= 0; i--) अणु
		entry = 0;
		क्रम (j = 0; j < 32; j++)
			अगर (test_bit(index++, priv->active_vlans))
				entry |= 1 << j;
		filter->entry[i] = cpu_to_be32(entry);
	पूर्ण
	err = mlx4_cmd(dev, mailbox->dma, priv->port, 0, MLX4_CMD_SET_VLAN_FLTR,
		       MLX4_CMD_TIME_CLASS_B, MLX4_CMD_WRAPPED);
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण

पूर्णांक mlx4_en_QUERY_PORT(काष्ठा mlx4_en_dev *mdev, u8 port)
अणु
	काष्ठा mlx4_en_query_port_context *qport_context;
	काष्ठा mlx4_en_priv *priv = netdev_priv(mdev->pndev[port]);
	काष्ठा mlx4_en_port_state *state = &priv->port_state;
	काष्ठा mlx4_cmd_mailbox *mailbox;
	पूर्णांक err;

	mailbox = mlx4_alloc_cmd_mailbox(mdev->dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	err = mlx4_cmd_box(mdev->dev, 0, mailbox->dma, port, 0,
			   MLX4_CMD_QUERY_PORT, MLX4_CMD_TIME_CLASS_B,
			   MLX4_CMD_WRAPPED);
	अगर (err)
		जाओ out;
	qport_context = mailbox->buf;

	/* This command is always accessed from Ethtool context
	 * alपढ़ोy synchronized, no need in locking */
	state->link_state = !!(qport_context->link_up & MLX4_EN_LINK_UP_MASK);
	चयन (qport_context->link_speed & MLX4_EN_SPEED_MASK) अणु
	हाल MLX4_EN_100M_SPEED:
		state->link_speed = SPEED_100;
		अवरोध;
	हाल MLX4_EN_1G_SPEED:
		state->link_speed = SPEED_1000;
		अवरोध;
	हाल MLX4_EN_10G_SPEED_XAUI:
	हाल MLX4_EN_10G_SPEED_XFI:
		state->link_speed = SPEED_10000;
		अवरोध;
	हाल MLX4_EN_20G_SPEED:
		state->link_speed = SPEED_20000;
		अवरोध;
	हाल MLX4_EN_40G_SPEED:
		state->link_speed = SPEED_40000;
		अवरोध;
	हाल MLX4_EN_56G_SPEED:
		state->link_speed = SPEED_56000;
		अवरोध;
	शेष:
		state->link_speed = -1;
		अवरोध;
	पूर्ण

	state->transceiver = qport_context->transceiver;

	state->flags = 0; /* Reset and recalculate the port flags */
	state->flags |= (qport_context->link_up & MLX4_EN_ANC_MASK) ?
		MLX4_EN_PORT_ANC : 0;
	state->flags |= (qport_context->स्वतःneg & MLX4_EN_AUTONEG_MASK) ?
		MLX4_EN_PORT_ANE : 0;

out:
	mlx4_मुक्त_cmd_mailbox(mdev->dev, mailbox);
	वापस err;
पूर्ण

/* Each counter set is located in काष्ठा mlx4_en_stat_out_mbox
 * with a स्थिर offset between its prio components.
 * This function runs over a counter set and sum all of it's prio components.
 */
अटल अचिन्हित दीर्घ en_stats_adder(__be64 *start, __be64 *next, पूर्णांक num)
अणु
	__be64 *curr = start;
	अचिन्हित दीर्घ ret = 0;
	पूर्णांक i;
	पूर्णांक offset = next - start;

	क्रम (i = 0; i < num; i++) अणु
		ret += be64_to_cpu(*curr);
		curr += offset;
	पूर्ण

	वापस ret;
पूर्ण

व्योम mlx4_en_fold_software_stats(काष्ठा net_device *dev)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	अचिन्हित दीर्घ packets, bytes;
	पूर्णांक i;

	अगर (!priv->port_up || mlx4_is_master(mdev->dev))
		वापस;

	packets = 0;
	bytes = 0;
	क्रम (i = 0; i < priv->rx_ring_num; i++) अणु
		स्थिर काष्ठा mlx4_en_rx_ring *ring = priv->rx_ring[i];

		packets += READ_ONCE(ring->packets);
		bytes   += READ_ONCE(ring->bytes);
	पूर्ण
	dev->stats.rx_packets = packets;
	dev->stats.rx_bytes = bytes;

	packets = 0;
	bytes = 0;
	क्रम (i = 0; i < priv->tx_ring_num[TX]; i++) अणु
		स्थिर काष्ठा mlx4_en_tx_ring *ring = priv->tx_ring[TX][i];

		packets += READ_ONCE(ring->packets);
		bytes   += READ_ONCE(ring->bytes);
	पूर्ण
	dev->stats.tx_packets = packets;
	dev->stats.tx_bytes = bytes;
पूर्ण

पूर्णांक mlx4_en_DUMP_ETH_STATS(काष्ठा mlx4_en_dev *mdev, u8 port, u8 reset)
अणु
	काष्ठा mlx4_counter पंचांगp_counter_stats;
	काष्ठा mlx4_en_stat_out_mbox *mlx4_en_stats;
	काष्ठा mlx4_en_stat_out_flow_control_mbox *flowstats;
	काष्ठा net_device *dev = mdev->pndev[port];
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा mlx4_cmd_mailbox *mailbox, *mailbox_priority;
	u64 in_mod = reset << 8 | port;
	पूर्णांक err;
	पूर्णांक i, counter_index;
	अचिन्हित दीर्घ sw_tx_dropped = 0;
	अचिन्हित दीर्घ sw_rx_dropped = 0;

	mailbox = mlx4_alloc_cmd_mailbox(mdev->dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	mailbox_priority = mlx4_alloc_cmd_mailbox(mdev->dev);
	अगर (IS_ERR(mailbox_priority)) अणु
		mlx4_मुक्त_cmd_mailbox(mdev->dev, mailbox);
		वापस PTR_ERR(mailbox_priority);
	पूर्ण

	err = mlx4_cmd_box(mdev->dev, 0, mailbox->dma, in_mod, 0,
			   MLX4_CMD_DUMP_ETH_STATS, MLX4_CMD_TIME_CLASS_B,
			   MLX4_CMD_NATIVE);
	अगर (err)
		जाओ out;

	mlx4_en_stats = mailbox->buf;

	स_रखो(&पंचांगp_counter_stats, 0, माप(पंचांगp_counter_stats));
	counter_index = mlx4_get_शेष_counter_index(mdev->dev, port);
	err = mlx4_get_counter_stats(mdev->dev, counter_index,
				     &पंचांगp_counter_stats, reset);

	/* 0xffs indicates invalid value */
	स_रखो(mailbox_priority->buf, 0xff,
	       माप(*flowstats) * MLX4_NUM_PRIORITIES);

	अगर (mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_FLOWSTATS_EN) अणु
		स_रखो(mailbox_priority->buf, 0,
		       माप(*flowstats) * MLX4_NUM_PRIORITIES);
		err = mlx4_cmd_box(mdev->dev, 0, mailbox_priority->dma,
				   in_mod | MLX4_DUMP_ETH_STATS_FLOW_CONTROL,
				   0, MLX4_CMD_DUMP_ETH_STATS,
				   MLX4_CMD_TIME_CLASS_B, MLX4_CMD_NATIVE);
		अगर (err)
			जाओ out;
	पूर्ण

	flowstats = mailbox_priority->buf;

	spin_lock_bh(&priv->stats_lock);

	mlx4_en_fold_software_stats(dev);

	priv->port_stats.rx_chksum_good = 0;
	priv->port_stats.rx_chksum_none = 0;
	priv->port_stats.rx_chksum_complete = 0;
	priv->port_stats.rx_alloc_pages = 0;
	priv->xdp_stats.rx_xdp_drop    = 0;
	priv->xdp_stats.rx_xdp_tx      = 0;
	priv->xdp_stats.rx_xdp_tx_full = 0;
	क्रम (i = 0; i < priv->rx_ring_num; i++) अणु
		स्थिर काष्ठा mlx4_en_rx_ring *ring = priv->rx_ring[i];

		sw_rx_dropped			+= READ_ONCE(ring->dropped);
		priv->port_stats.rx_chksum_good += READ_ONCE(ring->csum_ok);
		priv->port_stats.rx_chksum_none += READ_ONCE(ring->csum_none);
		priv->port_stats.rx_chksum_complete += READ_ONCE(ring->csum_complete);
		priv->port_stats.rx_alloc_pages += READ_ONCE(ring->rx_alloc_pages);
		priv->xdp_stats.rx_xdp_drop	+= READ_ONCE(ring->xdp_drop);
		priv->xdp_stats.rx_xdp_tx	+= READ_ONCE(ring->xdp_tx);
		priv->xdp_stats.rx_xdp_tx_full	+= READ_ONCE(ring->xdp_tx_full);
	पूर्ण
	priv->port_stats.tx_chksum_offload = 0;
	priv->port_stats.queue_stopped = 0;
	priv->port_stats.wake_queue = 0;
	priv->port_stats.tso_packets = 0;
	priv->port_stats.xmit_more = 0;

	क्रम (i = 0; i < priv->tx_ring_num[TX]; i++) अणु
		स्थिर काष्ठा mlx4_en_tx_ring *ring = priv->tx_ring[TX][i];

		sw_tx_dropped			   += READ_ONCE(ring->tx_dropped);
		priv->port_stats.tx_chksum_offload += READ_ONCE(ring->tx_csum);
		priv->port_stats.queue_stopped     += READ_ONCE(ring->queue_stopped);
		priv->port_stats.wake_queue        += READ_ONCE(ring->wake_queue);
		priv->port_stats.tso_packets       += READ_ONCE(ring->tso_packets);
		priv->port_stats.xmit_more         += READ_ONCE(ring->xmit_more);
	पूर्ण

	अगर (!mlx4_is_slave(mdev->dev)) अणु
		काष्ठा mlx4_en_phy_stats *p_stats = &priv->phy_stats;

		p_stats->rx_packets_phy =
			en_stats_adder(&mlx4_en_stats->RTOT_prio_0,
				       &mlx4_en_stats->RTOT_prio_1,
				       NUM_PRIORITIES);
		p_stats->tx_packets_phy =
			en_stats_adder(&mlx4_en_stats->TTOT_prio_0,
				       &mlx4_en_stats->TTOT_prio_1,
				       NUM_PRIORITIES);
		p_stats->rx_bytes_phy =
			en_stats_adder(&mlx4_en_stats->ROCT_prio_0,
				       &mlx4_en_stats->ROCT_prio_1,
				       NUM_PRIORITIES);
		p_stats->tx_bytes_phy =
			en_stats_adder(&mlx4_en_stats->TOCT_prio_0,
				       &mlx4_en_stats->TOCT_prio_1,
				       NUM_PRIORITIES);
		अगर (mlx4_is_master(mdev->dev)) अणु
			stats->rx_packets = p_stats->rx_packets_phy;
			stats->tx_packets = p_stats->tx_packets_phy;
			stats->rx_bytes = p_stats->rx_bytes_phy;
			stats->tx_bytes = p_stats->tx_bytes_phy;
		पूर्ण
	पूर्ण

	/* net device stats */
	stats->rx_errors = be64_to_cpu(mlx4_en_stats->PCS) +
			   be32_to_cpu(mlx4_en_stats->RJBBR) +
			   be32_to_cpu(mlx4_en_stats->RCRC) +
			   be32_to_cpu(mlx4_en_stats->RRUNT) +
			   be64_to_cpu(mlx4_en_stats->RInRangeLengthErr) +
			   be64_to_cpu(mlx4_en_stats->ROutRangeLengthErr) +
			   be32_to_cpu(mlx4_en_stats->RSHORT) +
			   en_stats_adder(&mlx4_en_stats->RGIANT_prio_0,
					  &mlx4_en_stats->RGIANT_prio_1,
					  NUM_PRIORITIES);
	stats->tx_errors = en_stats_adder(&mlx4_en_stats->TGIANT_prio_0,
					  &mlx4_en_stats->TGIANT_prio_1,
					  NUM_PRIORITIES);
	stats->multicast = en_stats_adder(&mlx4_en_stats->MCAST_prio_0,
					  &mlx4_en_stats->MCAST_prio_1,
					  NUM_PRIORITIES);
	stats->rx_dropped = be32_to_cpu(mlx4_en_stats->RDROP) +
			    sw_rx_dropped;
	stats->rx_length_errors = be32_to_cpu(mlx4_en_stats->RdropLength);
	stats->rx_crc_errors = be32_to_cpu(mlx4_en_stats->RCRC);
	stats->rx_fअगरo_errors = be32_to_cpu(mlx4_en_stats->RdropOvflw);
	stats->tx_dropped = be32_to_cpu(mlx4_en_stats->TDROP) +
			    sw_tx_dropped;

	/* RX stats */
	priv->pkstats.rx_multicast_packets = stats->multicast;
	priv->pkstats.rx_broadcast_packets =
			en_stats_adder(&mlx4_en_stats->RBCAST_prio_0,
				       &mlx4_en_stats->RBCAST_prio_1,
				       NUM_PRIORITIES);
	priv->pkstats.rx_jabbers = be32_to_cpu(mlx4_en_stats->RJBBR);
	priv->pkstats.rx_in_range_length_error =
		be64_to_cpu(mlx4_en_stats->RInRangeLengthErr);
	priv->pkstats.rx_out_range_length_error =
		be64_to_cpu(mlx4_en_stats->ROutRangeLengthErr);

	/* Tx stats */
	priv->pkstats.tx_multicast_packets =
		en_stats_adder(&mlx4_en_stats->TMCAST_prio_0,
			       &mlx4_en_stats->TMCAST_prio_1,
			       NUM_PRIORITIES);
	priv->pkstats.tx_broadcast_packets =
		en_stats_adder(&mlx4_en_stats->TBCAST_prio_0,
			       &mlx4_en_stats->TBCAST_prio_1,
			       NUM_PRIORITIES);

	priv->pkstats.rx_prio[0][0] = be64_to_cpu(mlx4_en_stats->RTOT_prio_0);
	priv->pkstats.rx_prio[0][1] = be64_to_cpu(mlx4_en_stats->ROCT_prio_0);
	priv->pkstats.rx_prio[1][0] = be64_to_cpu(mlx4_en_stats->RTOT_prio_1);
	priv->pkstats.rx_prio[1][1] = be64_to_cpu(mlx4_en_stats->ROCT_prio_1);
	priv->pkstats.rx_prio[2][0] = be64_to_cpu(mlx4_en_stats->RTOT_prio_2);
	priv->pkstats.rx_prio[2][1] = be64_to_cpu(mlx4_en_stats->ROCT_prio_2);
	priv->pkstats.rx_prio[3][0] = be64_to_cpu(mlx4_en_stats->RTOT_prio_3);
	priv->pkstats.rx_prio[3][1] = be64_to_cpu(mlx4_en_stats->ROCT_prio_3);
	priv->pkstats.rx_prio[4][0] = be64_to_cpu(mlx4_en_stats->RTOT_prio_4);
	priv->pkstats.rx_prio[4][1] = be64_to_cpu(mlx4_en_stats->ROCT_prio_4);
	priv->pkstats.rx_prio[5][0] = be64_to_cpu(mlx4_en_stats->RTOT_prio_5);
	priv->pkstats.rx_prio[5][1] = be64_to_cpu(mlx4_en_stats->ROCT_prio_5);
	priv->pkstats.rx_prio[6][0] = be64_to_cpu(mlx4_en_stats->RTOT_prio_6);
	priv->pkstats.rx_prio[6][1] = be64_to_cpu(mlx4_en_stats->ROCT_prio_6);
	priv->pkstats.rx_prio[7][0] = be64_to_cpu(mlx4_en_stats->RTOT_prio_7);
	priv->pkstats.rx_prio[7][1] = be64_to_cpu(mlx4_en_stats->ROCT_prio_7);
	priv->pkstats.rx_prio[8][0] = be64_to_cpu(mlx4_en_stats->RTOT_novlan);
	priv->pkstats.rx_prio[8][1] = be64_to_cpu(mlx4_en_stats->ROCT_novlan);
	priv->pkstats.tx_prio[0][0] = be64_to_cpu(mlx4_en_stats->TTOT_prio_0);
	priv->pkstats.tx_prio[0][1] = be64_to_cpu(mlx4_en_stats->TOCT_prio_0);
	priv->pkstats.tx_prio[1][0] = be64_to_cpu(mlx4_en_stats->TTOT_prio_1);
	priv->pkstats.tx_prio[1][1] = be64_to_cpu(mlx4_en_stats->TOCT_prio_1);
	priv->pkstats.tx_prio[2][0] = be64_to_cpu(mlx4_en_stats->TTOT_prio_2);
	priv->pkstats.tx_prio[2][1] = be64_to_cpu(mlx4_en_stats->TOCT_prio_2);
	priv->pkstats.tx_prio[3][0] = be64_to_cpu(mlx4_en_stats->TTOT_prio_3);
	priv->pkstats.tx_prio[3][1] = be64_to_cpu(mlx4_en_stats->TOCT_prio_3);
	priv->pkstats.tx_prio[4][0] = be64_to_cpu(mlx4_en_stats->TTOT_prio_4);
	priv->pkstats.tx_prio[4][1] = be64_to_cpu(mlx4_en_stats->TOCT_prio_4);
	priv->pkstats.tx_prio[5][0] = be64_to_cpu(mlx4_en_stats->TTOT_prio_5);
	priv->pkstats.tx_prio[5][1] = be64_to_cpu(mlx4_en_stats->TOCT_prio_5);
	priv->pkstats.tx_prio[6][0] = be64_to_cpu(mlx4_en_stats->TTOT_prio_6);
	priv->pkstats.tx_prio[6][1] = be64_to_cpu(mlx4_en_stats->TOCT_prio_6);
	priv->pkstats.tx_prio[7][0] = be64_to_cpu(mlx4_en_stats->TTOT_prio_7);
	priv->pkstats.tx_prio[7][1] = be64_to_cpu(mlx4_en_stats->TOCT_prio_7);
	priv->pkstats.tx_prio[8][0] = be64_to_cpu(mlx4_en_stats->TTOT_novlan);
	priv->pkstats.tx_prio[8][1] = be64_to_cpu(mlx4_en_stats->TOCT_novlan);

	अगर (पंचांगp_counter_stats.counter_mode == 0) अणु
		priv->pf_stats.rx_bytes   = be64_to_cpu(पंचांगp_counter_stats.rx_bytes);
		priv->pf_stats.tx_bytes   = be64_to_cpu(पंचांगp_counter_stats.tx_bytes);
		priv->pf_stats.rx_packets = be64_to_cpu(पंचांगp_counter_stats.rx_frames);
		priv->pf_stats.tx_packets = be64_to_cpu(पंचांगp_counter_stats.tx_frames);
	पूर्ण

	क्रम (i = 0; i < MLX4_NUM_PRIORITIES; i++)	अणु
		priv->rx_priority_flowstats[i].rx_छोड़ो =
			be64_to_cpu(flowstats[i].rx_छोड़ो);
		priv->rx_priority_flowstats[i].rx_छोड़ो_duration =
			be64_to_cpu(flowstats[i].rx_छोड़ो_duration);
		priv->rx_priority_flowstats[i].rx_छोड़ो_transition =
			be64_to_cpu(flowstats[i].rx_छोड़ो_transition);
		priv->tx_priority_flowstats[i].tx_छोड़ो =
			be64_to_cpu(flowstats[i].tx_छोड़ो);
		priv->tx_priority_flowstats[i].tx_छोड़ो_duration =
			be64_to_cpu(flowstats[i].tx_छोड़ो_duration);
		priv->tx_priority_flowstats[i].tx_छोड़ो_transition =
			be64_to_cpu(flowstats[i].tx_छोड़ो_transition);
	पूर्ण

	/* अगर pfc is not in use, all priorities counters have the same value */
	priv->rx_flowstats.rx_छोड़ो =
		be64_to_cpu(flowstats[0].rx_छोड़ो);
	priv->rx_flowstats.rx_छोड़ो_duration =
		be64_to_cpu(flowstats[0].rx_छोड़ो_duration);
	priv->rx_flowstats.rx_छोड़ो_transition =
		be64_to_cpu(flowstats[0].rx_छोड़ो_transition);
	priv->tx_flowstats.tx_छोड़ो =
		be64_to_cpu(flowstats[0].tx_छोड़ो);
	priv->tx_flowstats.tx_छोड़ो_duration =
		be64_to_cpu(flowstats[0].tx_छोड़ो_duration);
	priv->tx_flowstats.tx_छोड़ो_transition =
		be64_to_cpu(flowstats[0].tx_छोड़ो_transition);

	spin_unlock_bh(&priv->stats_lock);

out:
	mlx4_मुक्त_cmd_mailbox(mdev->dev, mailbox);
	mlx4_मुक्त_cmd_mailbox(mdev->dev, mailbox_priority);
	वापस err;
पूर्ण

