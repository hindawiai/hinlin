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

#समावेश <linux/kernel.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/mlx4/driver.h>
#समावेश <linux/mlx4/device.h>
#समावेश <linux/in.h>
#समावेश <net/ip.h>
#समावेश <linux/biपंचांगap.h>

#समावेश "mlx4_en.h"
#समावेश "en_port.h"

#घोषणा EN_ETHTOOL_QP_ATTACH (1ull << 63)
#घोषणा EN_ETHTOOL_SHORT_MASK cpu_to_be16(0xffff)
#घोषणा EN_ETHTOOL_WORD_MASK  cpu_to_be32(0xffffffff)

पूर्णांक mlx4_en_moderation_update(काष्ठा mlx4_en_priv *priv)
अणु
	पूर्णांक i, t;
	पूर्णांक err = 0;

	क्रम (t = 0 ; t < MLX4_EN_NUM_TX_TYPES; t++) अणु
		क्रम (i = 0; i < priv->tx_ring_num[t]; i++) अणु
			priv->tx_cq[t][i]->moder_cnt = priv->tx_frames;
			priv->tx_cq[t][i]->moder_समय = priv->tx_usecs;
			अगर (priv->port_up) अणु
				err = mlx4_en_set_cq_moder(priv,
							   priv->tx_cq[t][i]);
				अगर (err)
					वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (priv->adaptive_rx_coal)
		वापस 0;

	क्रम (i = 0; i < priv->rx_ring_num; i++) अणु
		priv->rx_cq[i]->moder_cnt = priv->rx_frames;
		priv->rx_cq[i]->moder_समय = priv->rx_usecs;
		priv->last_moder_समय[i] = MLX4_EN_AUTO_CONF;
		अगर (priv->port_up) अणु
			err = mlx4_en_set_cq_moder(priv, priv->rx_cq[i]);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम
mlx4_en_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;

	strlcpy(drvinfo->driver, DRV_NAME, माप(drvinfo->driver));
	strlcpy(drvinfo->version, DRV_VERSION,
		माप(drvinfo->version));
	snम_लिखो(drvinfo->fw_version, माप(drvinfo->fw_version),
		"%d.%d.%d",
		(u16) (mdev->dev->caps.fw_ver >> 32),
		(u16) ((mdev->dev->caps.fw_ver >> 16) & 0xffff),
		(u16) (mdev->dev->caps.fw_ver & 0xffff));
	strlcpy(drvinfo->bus_info, pci_name(mdev->dev->persist->pdev),
		माप(drvinfo->bus_info));
पूर्ण

अटल स्थिर अक्षर mlx4_en_priv_flags[][ETH_GSTRING_LEN] = अणु
	"blueflame",
	"phv-bit"
पूर्ण;

अटल स्थिर अक्षर मुख्य_strings[][ETH_GSTRING_LEN] = अणु
	/* मुख्य statistics */
	"rx_packets", "tx_packets", "rx_bytes", "tx_bytes", "rx_errors",
	"tx_errors", "rx_dropped", "tx_dropped", "multicast", "collisions",
	"rx_length_errors", "rx_over_errors", "rx_crc_errors",
	"rx_frame_errors", "rx_fifo_errors", "rx_missed_errors",
	"tx_aborted_errors", "tx_carrier_errors", "tx_fifo_errors",
	"tx_heartbeat_errors", "tx_window_errors",

	/* port statistics */
	"tso_packets",
	"xmit_more",
	"queue_stopped", "wake_queue", "tx_timeout", "rx_alloc_pages",
	"rx_csum_good", "rx_csum_none", "rx_csum_complete", "tx_chksum_offload",

	/* pf statistics */
	"pf_rx_packets",
	"pf_rx_bytes",
	"pf_tx_packets",
	"pf_tx_bytes",

	/* priority flow control statistics rx */
	"rx_pause_prio_0", "rx_pause_duration_prio_0",
	"rx_pause_transition_prio_0",
	"rx_pause_prio_1", "rx_pause_duration_prio_1",
	"rx_pause_transition_prio_1",
	"rx_pause_prio_2", "rx_pause_duration_prio_2",
	"rx_pause_transition_prio_2",
	"rx_pause_prio_3", "rx_pause_duration_prio_3",
	"rx_pause_transition_prio_3",
	"rx_pause_prio_4", "rx_pause_duration_prio_4",
	"rx_pause_transition_prio_4",
	"rx_pause_prio_5", "rx_pause_duration_prio_5",
	"rx_pause_transition_prio_5",
	"rx_pause_prio_6", "rx_pause_duration_prio_6",
	"rx_pause_transition_prio_6",
	"rx_pause_prio_7", "rx_pause_duration_prio_7",
	"rx_pause_transition_prio_7",

	/* flow control statistics rx */
	"rx_pause", "rx_pause_duration", "rx_pause_transition",

	/* priority flow control statistics tx */
	"tx_pause_prio_0", "tx_pause_duration_prio_0",
	"tx_pause_transition_prio_0",
	"tx_pause_prio_1", "tx_pause_duration_prio_1",
	"tx_pause_transition_prio_1",
	"tx_pause_prio_2", "tx_pause_duration_prio_2",
	"tx_pause_transition_prio_2",
	"tx_pause_prio_3", "tx_pause_duration_prio_3",
	"tx_pause_transition_prio_3",
	"tx_pause_prio_4", "tx_pause_duration_prio_4",
	"tx_pause_transition_prio_4",
	"tx_pause_prio_5", "tx_pause_duration_prio_5",
	"tx_pause_transition_prio_5",
	"tx_pause_prio_6", "tx_pause_duration_prio_6",
	"tx_pause_transition_prio_6",
	"tx_pause_prio_7", "tx_pause_duration_prio_7",
	"tx_pause_transition_prio_7",

	/* flow control statistics tx */
	"tx_pause", "tx_pause_duration", "tx_pause_transition",

	/* packet statistics */
	"rx_multicast_packets",
	"rx_broadcast_packets",
	"rx_jabbers",
	"rx_in_range_length_error",
	"rx_out_range_length_error",
	"tx_multicast_packets",
	"tx_broadcast_packets",
	"rx_prio_0_packets", "rx_prio_0_bytes",
	"rx_prio_1_packets", "rx_prio_1_bytes",
	"rx_prio_2_packets", "rx_prio_2_bytes",
	"rx_prio_3_packets", "rx_prio_3_bytes",
	"rx_prio_4_packets", "rx_prio_4_bytes",
	"rx_prio_5_packets", "rx_prio_5_bytes",
	"rx_prio_6_packets", "rx_prio_6_bytes",
	"rx_prio_7_packets", "rx_prio_7_bytes",
	"rx_novlan_packets", "rx_novlan_bytes",
	"tx_prio_0_packets", "tx_prio_0_bytes",
	"tx_prio_1_packets", "tx_prio_1_bytes",
	"tx_prio_2_packets", "tx_prio_2_bytes",
	"tx_prio_3_packets", "tx_prio_3_bytes",
	"tx_prio_4_packets", "tx_prio_4_bytes",
	"tx_prio_5_packets", "tx_prio_5_bytes",
	"tx_prio_6_packets", "tx_prio_6_bytes",
	"tx_prio_7_packets", "tx_prio_7_bytes",
	"tx_novlan_packets", "tx_novlan_bytes",

	/* xdp statistics */
	"rx_xdp_drop",
	"rx_xdp_tx",
	"rx_xdp_tx_full",

	/* phy statistics */
	"rx_packets_phy", "rx_bytes_phy",
	"tx_packets_phy", "tx_bytes_phy",
पूर्ण;

अटल स्थिर अक्षर mlx4_en_test_names[][ETH_GSTRING_LEN]= अणु
	"Interrupt Test",
	"Link Test",
	"Speed Test",
	"Register Test",
	"Loopback Test",
पूर्ण;

अटल u32 mlx4_en_get_msglevel(काष्ठा net_device *dev)
अणु
	वापस ((काष्ठा mlx4_en_priv *) netdev_priv(dev))->msg_enable;
पूर्ण

अटल व्योम mlx4_en_set_msglevel(काष्ठा net_device *dev, u32 val)
अणु
	((काष्ठा mlx4_en_priv *) netdev_priv(dev))->msg_enable = val;
पूर्ण

अटल व्योम mlx4_en_get_wol(काष्ठा net_device *netdev,
			    काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(netdev);
	काष्ठा mlx4_caps *caps = &priv->mdev->dev->caps;
	पूर्णांक err = 0;
	u64 config = 0;
	u64 mask;

	अगर ((priv->port < 1) || (priv->port > 2)) अणु
		en_err(priv, "Failed to get WoL information\n");
		वापस;
	पूर्ण

	mask = (priv->port == 1) ? MLX4_DEV_CAP_FLAG_WOL_PORT1 :
		MLX4_DEV_CAP_FLAG_WOL_PORT2;

	अगर (!(caps->flags & mask)) अणु
		wol->supported = 0;
		wol->wolopts = 0;
		वापस;
	पूर्ण

	अगर (caps->wol_port[priv->port])
		wol->supported = WAKE_MAGIC;
	अन्यथा
		wol->supported = 0;

	err = mlx4_wol_पढ़ो(priv->mdev->dev, &config, priv->port);
	अगर (err) अणु
		en_err(priv, "Failed to get WoL information\n");
		वापस;
	पूर्ण

	अगर ((config & MLX4_EN_WOL_ENABLED) && (config & MLX4_EN_WOL_MAGIC))
		wol->wolopts = WAKE_MAGIC;
	अन्यथा
		wol->wolopts = 0;
पूर्ण

अटल पूर्णांक mlx4_en_set_wol(काष्ठा net_device *netdev,
			    काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(netdev);
	u64 config = 0;
	पूर्णांक err = 0;
	u64 mask;

	अगर ((priv->port < 1) || (priv->port > 2))
		वापस -EOPNOTSUPP;

	mask = (priv->port == 1) ? MLX4_DEV_CAP_FLAG_WOL_PORT1 :
		MLX4_DEV_CAP_FLAG_WOL_PORT2;

	अगर (!(priv->mdev->dev->caps.flags & mask))
		वापस -EOPNOTSUPP;

	अगर (wol->supported & ~WAKE_MAGIC)
		वापस -EINVAL;

	err = mlx4_wol_पढ़ो(priv->mdev->dev, &config, priv->port);
	अगर (err) अणु
		en_err(priv, "Failed to get WoL info, unable to modify\n");
		वापस err;
	पूर्ण

	अगर (wol->wolopts & WAKE_MAGIC) अणु
		config |= MLX4_EN_WOL_DO_MODIFY | MLX4_EN_WOL_ENABLED |
				MLX4_EN_WOL_MAGIC;
	पूर्ण अन्यथा अणु
		config &= ~(MLX4_EN_WOL_ENABLED | MLX4_EN_WOL_MAGIC);
		config |= MLX4_EN_WOL_DO_MODIFY;
	पूर्ण

	err = mlx4_wol_ग_लिखो(priv->mdev->dev, config, priv->port);
	अगर (err)
		en_err(priv, "Failed to set WoL information\n");

	वापस err;
पूर्ण

काष्ठा biपंचांगap_iterator अणु
	अचिन्हित दीर्घ *stats_biपंचांगap;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक iterator;
	bool advance_array; /* अगर set, क्रमce no increments */
पूर्ण;

अटल अंतरभूत व्योम biपंचांगap_iterator_init(काष्ठा biपंचांगap_iterator *h,
					अचिन्हित दीर्घ *stats_biपंचांगap,
					पूर्णांक count)
अणु
	h->iterator = 0;
	h->advance_array = !biपंचांगap_empty(stats_biपंचांगap, count);
	h->count = h->advance_array ? biपंचांगap_weight(stats_biपंचांगap, count)
		: count;
	h->stats_biपंचांगap = stats_biपंचांगap;
पूर्ण

अटल अंतरभूत पूर्णांक biपंचांगap_iterator_test(काष्ठा biपंचांगap_iterator *h)
अणु
	वापस !h->advance_array ? 1 : test_bit(h->iterator, h->stats_biपंचांगap);
पूर्ण

अटल अंतरभूत पूर्णांक biपंचांगap_iterator_inc(काष्ठा biपंचांगap_iterator *h)
अणु
	वापस h->iterator++;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
biपंचांगap_iterator_count(काष्ठा biपंचांगap_iterator *h)
अणु
	वापस h->count;
पूर्ण

अटल पूर्णांक mlx4_en_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा biपंचांगap_iterator it;

	biपंचांगap_iterator_init(&it, priv->stats_biपंचांगap.biपंचांगap, NUM_ALL_STATS);

	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस biपंचांगap_iterator_count(&it) +
			(priv->tx_ring_num[TX] * 2) +
			(priv->rx_ring_num * (3 + NUM_XDP_STATS));
	हाल ETH_SS_TEST:
		वापस MLX4_EN_NUM_SELF_TEST - !(priv->mdev->dev->caps.flags
					& MLX4_DEV_CAP_FLAG_UC_LOOPBACK) * 2;
	हाल ETH_SS_PRIV_FLAGS:
		वापस ARRAY_SIZE(mlx4_en_priv_flags);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम mlx4_en_get_ethtool_stats(काष्ठा net_device *dev,
		काष्ठा ethtool_stats *stats, uपूर्णांक64_t *data)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	पूर्णांक index = 0;
	पूर्णांक i;
	काष्ठा biपंचांगap_iterator it;

	biपंचांगap_iterator_init(&it, priv->stats_biपंचांगap.biपंचांगap, NUM_ALL_STATS);

	spin_lock_bh(&priv->stats_lock);

	mlx4_en_fold_software_stats(dev);

	क्रम (i = 0; i < NUM_MAIN_STATS; i++, biपंचांगap_iterator_inc(&it))
		अगर (biपंचांगap_iterator_test(&it))
			data[index++] = ((अचिन्हित दीर्घ *)&dev->stats)[i];

	क्रम (i = 0; i < NUM_PORT_STATS; i++, biपंचांगap_iterator_inc(&it))
		अगर (biपंचांगap_iterator_test(&it))
			data[index++] = ((अचिन्हित दीर्घ *)&priv->port_stats)[i];

	क्रम (i = 0; i < NUM_PF_STATS; i++, biपंचांगap_iterator_inc(&it))
		अगर (biपंचांगap_iterator_test(&it))
			data[index++] =
				((अचिन्हित दीर्घ *)&priv->pf_stats)[i];

	क्रम (i = 0; i < NUM_FLOW_PRIORITY_STATS_RX;
	     i++, biपंचांगap_iterator_inc(&it))
		अगर (biपंचांगap_iterator_test(&it))
			data[index++] =
				((u64 *)&priv->rx_priority_flowstats)[i];

	क्रम (i = 0; i < NUM_FLOW_STATS_RX; i++, biपंचांगap_iterator_inc(&it))
		अगर (biपंचांगap_iterator_test(&it))
			data[index++] = ((u64 *)&priv->rx_flowstats)[i];

	क्रम (i = 0; i < NUM_FLOW_PRIORITY_STATS_TX;
	     i++, biपंचांगap_iterator_inc(&it))
		अगर (biपंचांगap_iterator_test(&it))
			data[index++] =
				((u64 *)&priv->tx_priority_flowstats)[i];

	क्रम (i = 0; i < NUM_FLOW_STATS_TX; i++, biपंचांगap_iterator_inc(&it))
		अगर (biपंचांगap_iterator_test(&it))
			data[index++] = ((u64 *)&priv->tx_flowstats)[i];

	क्रम (i = 0; i < NUM_PKT_STATS; i++, biपंचांगap_iterator_inc(&it))
		अगर (biपंचांगap_iterator_test(&it))
			data[index++] = ((अचिन्हित दीर्घ *)&priv->pkstats)[i];

	क्रम (i = 0; i < NUM_XDP_STATS; i++, biपंचांगap_iterator_inc(&it))
		अगर (biपंचांगap_iterator_test(&it))
			data[index++] = ((अचिन्हित दीर्घ *)&priv->xdp_stats)[i];

	क्रम (i = 0; i < NUM_PHY_STATS; i++, biपंचांगap_iterator_inc(&it))
		अगर (biपंचांगap_iterator_test(&it))
			data[index++] = ((अचिन्हित दीर्घ *)&priv->phy_stats)[i];

	क्रम (i = 0; i < priv->tx_ring_num[TX]; i++) अणु
		data[index++] = priv->tx_ring[TX][i]->packets;
		data[index++] = priv->tx_ring[TX][i]->bytes;
	पूर्ण
	क्रम (i = 0; i < priv->rx_ring_num; i++) अणु
		data[index++] = priv->rx_ring[i]->packets;
		data[index++] = priv->rx_ring[i]->bytes;
		data[index++] = priv->rx_ring[i]->dropped;
		data[index++] = priv->rx_ring[i]->xdp_drop;
		data[index++] = priv->rx_ring[i]->xdp_tx;
		data[index++] = priv->rx_ring[i]->xdp_tx_full;
	पूर्ण
	spin_unlock_bh(&priv->stats_lock);

पूर्ण

अटल व्योम mlx4_en_self_test(काष्ठा net_device *dev,
			      काष्ठा ethtool_test *etest, u64 *buf)
अणु
	mlx4_en_ex_selftest(dev, &etest->flags, buf);
पूर्ण

अटल व्योम mlx4_en_get_strings(काष्ठा net_device *dev,
				uपूर्णांक32_t stringset, uपूर्णांक8_t *data)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	पूर्णांक index = 0;
	पूर्णांक i, strings = 0;
	काष्ठा biपंचांगap_iterator it;

	biपंचांगap_iterator_init(&it, priv->stats_biपंचांगap.biपंचांगap, NUM_ALL_STATS);

	चयन (stringset) अणु
	हाल ETH_SS_TEST:
		क्रम (i = 0; i < MLX4_EN_NUM_SELF_TEST - 2; i++)
			म_नकल(data + i * ETH_GSTRING_LEN, mlx4_en_test_names[i]);
		अगर (priv->mdev->dev->caps.flags & MLX4_DEV_CAP_FLAG_UC_LOOPBACK)
			क्रम (; i < MLX4_EN_NUM_SELF_TEST; i++)
				म_नकल(data + i * ETH_GSTRING_LEN, mlx4_en_test_names[i]);
		अवरोध;

	हाल ETH_SS_STATS:
		/* Add मुख्य counters */
		क्रम (i = 0; i < NUM_MAIN_STATS; i++, strings++,
		     biपंचांगap_iterator_inc(&it))
			अगर (biपंचांगap_iterator_test(&it))
				म_नकल(data + (index++) * ETH_GSTRING_LEN,
				       मुख्य_strings[strings]);

		क्रम (i = 0; i < NUM_PORT_STATS; i++, strings++,
		     biपंचांगap_iterator_inc(&it))
			अगर (biपंचांगap_iterator_test(&it))
				म_नकल(data + (index++) * ETH_GSTRING_LEN,
				       मुख्य_strings[strings]);

		क्रम (i = 0; i < NUM_PF_STATS; i++, strings++,
		     biपंचांगap_iterator_inc(&it))
			अगर (biपंचांगap_iterator_test(&it))
				म_नकल(data + (index++) * ETH_GSTRING_LEN,
				       मुख्य_strings[strings]);

		क्रम (i = 0; i < NUM_FLOW_STATS; i++, strings++,
		     biपंचांगap_iterator_inc(&it))
			अगर (biपंचांगap_iterator_test(&it))
				म_नकल(data + (index++) * ETH_GSTRING_LEN,
				       मुख्य_strings[strings]);

		क्रम (i = 0; i < NUM_PKT_STATS; i++, strings++,
		     biपंचांगap_iterator_inc(&it))
			अगर (biपंचांगap_iterator_test(&it))
				म_नकल(data + (index++) * ETH_GSTRING_LEN,
				       मुख्य_strings[strings]);

		क्रम (i = 0; i < NUM_XDP_STATS; i++, strings++,
		     biपंचांगap_iterator_inc(&it))
			अगर (biपंचांगap_iterator_test(&it))
				म_नकल(data + (index++) * ETH_GSTRING_LEN,
				       मुख्य_strings[strings]);

		क्रम (i = 0; i < NUM_PHY_STATS; i++, strings++,
		     biपंचांगap_iterator_inc(&it))
			अगर (biपंचांगap_iterator_test(&it))
				म_नकल(data + (index++) * ETH_GSTRING_LEN,
				       मुख्य_strings[strings]);

		क्रम (i = 0; i < priv->tx_ring_num[TX]; i++) अणु
			प्र_लिखो(data + (index++) * ETH_GSTRING_LEN,
				"tx%d_packets", i);
			प्र_लिखो(data + (index++) * ETH_GSTRING_LEN,
				"tx%d_bytes", i);
		पूर्ण
		क्रम (i = 0; i < priv->rx_ring_num; i++) अणु
			प्र_लिखो(data + (index++) * ETH_GSTRING_LEN,
				"rx%d_packets", i);
			प्र_लिखो(data + (index++) * ETH_GSTRING_LEN,
				"rx%d_bytes", i);
			प्र_लिखो(data + (index++) * ETH_GSTRING_LEN,
				"rx%d_dropped", i);
			प्र_लिखो(data + (index++) * ETH_GSTRING_LEN,
				"rx%d_xdp_drop", i);
			प्र_लिखो(data + (index++) * ETH_GSTRING_LEN,
				"rx%d_xdp_tx", i);
			प्र_लिखो(data + (index++) * ETH_GSTRING_LEN,
				"rx%d_xdp_tx_full", i);
		पूर्ण
		अवरोध;
	हाल ETH_SS_PRIV_FLAGS:
		क्रम (i = 0; i < ARRAY_SIZE(mlx4_en_priv_flags); i++)
			म_नकल(data + i * ETH_GSTRING_LEN,
			       mlx4_en_priv_flags[i]);
		अवरोध;

	पूर्ण
पूर्ण

अटल u32 mlx4_en_स्वतःneg_get(काष्ठा net_device *dev)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	u32 स्वतःneg = AUTONEG_DISABLE;

	अगर ((mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_ETH_BACKPL_AN_REP) &&
	    (priv->port_state.flags & MLX4_EN_PORT_ANE))
		स्वतःneg = AUTONEG_ENABLE;

	वापस स्वतःneg;
पूर्ण

अटल व्योम ptys2ethtool_update_supported_port(अचिन्हित दीर्घ *mask,
					       काष्ठा mlx4_ptys_reg *ptys_reg)
अणु
	u32 eth_proto = be32_to_cpu(ptys_reg->eth_proto_cap);

	अगर (eth_proto & (MLX4_PROT_MASK(MLX4_10GBASE_T)
			 | MLX4_PROT_MASK(MLX4_1000BASE_T)
			 | MLX4_PROT_MASK(MLX4_100BASE_TX))) अणु
		__set_bit(ETHTOOL_LINK_MODE_TP_BIT, mask);
	पूर्ण अन्यथा अगर (eth_proto & (MLX4_PROT_MASK(MLX4_10GBASE_CR)
			 | MLX4_PROT_MASK(MLX4_10GBASE_SR)
			 | MLX4_PROT_MASK(MLX4_56GBASE_SR4)
			 | MLX4_PROT_MASK(MLX4_40GBASE_CR4)
			 | MLX4_PROT_MASK(MLX4_40GBASE_SR4)
			 | MLX4_PROT_MASK(MLX4_1000BASE_CX_SGMII))) अणु
		__set_bit(ETHTOOL_LINK_MODE_FIBRE_BIT, mask);
	पूर्ण अन्यथा अगर (eth_proto & (MLX4_PROT_MASK(MLX4_56GBASE_KR4)
			 | MLX4_PROT_MASK(MLX4_40GBASE_KR4)
			 | MLX4_PROT_MASK(MLX4_20GBASE_KR2)
			 | MLX4_PROT_MASK(MLX4_10GBASE_KR)
			 | MLX4_PROT_MASK(MLX4_10GBASE_KX4)
			 | MLX4_PROT_MASK(MLX4_1000BASE_KX))) अणु
		__set_bit(ETHTOOL_LINK_MODE_Backplane_BIT, mask);
	पूर्ण
पूर्ण

अटल u32 ptys_get_active_port(काष्ठा mlx4_ptys_reg *ptys_reg)
अणु
	u32 eth_proto = be32_to_cpu(ptys_reg->eth_proto_oper);

	अगर (!eth_proto) /* link करोwn */
		eth_proto = be32_to_cpu(ptys_reg->eth_proto_cap);

	अगर (eth_proto & (MLX4_PROT_MASK(MLX4_10GBASE_T)
			 | MLX4_PROT_MASK(MLX4_1000BASE_T)
			 | MLX4_PROT_MASK(MLX4_100BASE_TX))) अणु
			वापस PORT_TP;
	पूर्ण

	अगर (eth_proto & (MLX4_PROT_MASK(MLX4_10GBASE_SR)
			 | MLX4_PROT_MASK(MLX4_56GBASE_SR4)
			 | MLX4_PROT_MASK(MLX4_40GBASE_SR4)
			 | MLX4_PROT_MASK(MLX4_1000BASE_CX_SGMII))) अणु
			वापस PORT_FIBRE;
	पूर्ण

	अगर (eth_proto & (MLX4_PROT_MASK(MLX4_10GBASE_CR)
			 | MLX4_PROT_MASK(MLX4_56GBASE_CR4)
			 | MLX4_PROT_MASK(MLX4_40GBASE_CR4))) अणु
			वापस PORT_DA;
	पूर्ण

	अगर (eth_proto & (MLX4_PROT_MASK(MLX4_56GBASE_KR4)
			 | MLX4_PROT_MASK(MLX4_40GBASE_KR4)
			 | MLX4_PROT_MASK(MLX4_20GBASE_KR2)
			 | MLX4_PROT_MASK(MLX4_10GBASE_KR)
			 | MLX4_PROT_MASK(MLX4_10GBASE_KX4)
			 | MLX4_PROT_MASK(MLX4_1000BASE_KX))) अणु
			वापस PORT_NONE;
	पूर्ण
	वापस PORT_OTHER;
पूर्ण

#घोषणा MLX4_LINK_MODES_SZ \
	(माप_field(काष्ठा mlx4_ptys_reg, eth_proto_cap) * 8)

क्रमागत ethtool_report अणु
	SUPPORTED = 0,
	ADVERTISED = 1,
पूर्ण;

काष्ठा ptys2ethtool_config अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(supported);
	__ETHTOOL_DECLARE_LINK_MODE_MASK(advertised);
	u32 speed;
पूर्ण;

अटल अचिन्हित दीर्घ *ptys2ethtool_link_mode(काष्ठा ptys2ethtool_config *cfg,
					     क्रमागत ethtool_report report)
अणु
	चयन (report) अणु
	हाल SUPPORTED:
		वापस cfg->supported;
	हाल ADVERTISED:
		वापस cfg->advertised;
	पूर्ण
	वापस शून्य;
पूर्ण

#घोषणा MLX4_BUILD_PTYS2ETHTOOL_CONFIG(reg_, speed_, ...)		\
	(अणु								\
		काष्ठा ptys2ethtool_config *cfg;			\
		अटल स्थिर अचिन्हित पूर्णांक modes[] = अणु __VA_ARGS__ पूर्ण;	\
		अचिन्हित पूर्णांक i;						\
		cfg = &ptys2ethtool_map[reg_];				\
		cfg->speed = speed_;					\
		biपंचांगap_zero(cfg->supported,				\
			    __ETHTOOL_LINK_MODE_MASK_NBITS);		\
		biपंचांगap_zero(cfg->advertised,				\
			    __ETHTOOL_LINK_MODE_MASK_NBITS);		\
		क्रम (i = 0 ; i < ARRAY_SIZE(modes) ; ++i) अणु		\
			__set_bit(modes[i], cfg->supported);		\
			__set_bit(modes[i], cfg->advertised);		\
		पूर्ण							\
	पूर्ण)

/* Translates mlx4 link mode to equivalent ethtool Link modes/speed */
अटल काष्ठा ptys2ethtool_config ptys2ethtool_map[MLX4_LINK_MODES_SZ];

व्योम __init mlx4_en_init_ptys2ethtool_map(व्योम)
अणु
	MLX4_BUILD_PTYS2ETHTOOL_CONFIG(MLX4_100BASE_TX, SPEED_100,
				       ETHTOOL_LINK_MODE_100baseT_Full_BIT);
	MLX4_BUILD_PTYS2ETHTOOL_CONFIG(MLX4_1000BASE_T, SPEED_1000,
				       ETHTOOL_LINK_MODE_1000baseT_Full_BIT);
	MLX4_BUILD_PTYS2ETHTOOL_CONFIG(MLX4_1000BASE_CX_SGMII, SPEED_1000,
				       ETHTOOL_LINK_MODE_1000baseKX_Full_BIT);
	MLX4_BUILD_PTYS2ETHTOOL_CONFIG(MLX4_1000BASE_KX, SPEED_1000,
				       ETHTOOL_LINK_MODE_1000baseKX_Full_BIT);
	MLX4_BUILD_PTYS2ETHTOOL_CONFIG(MLX4_10GBASE_T, SPEED_10000,
				       ETHTOOL_LINK_MODE_10000baseT_Full_BIT);
	MLX4_BUILD_PTYS2ETHTOOL_CONFIG(MLX4_10GBASE_CX4, SPEED_10000,
				       ETHTOOL_LINK_MODE_10000baseKX4_Full_BIT);
	MLX4_BUILD_PTYS2ETHTOOL_CONFIG(MLX4_10GBASE_KX4, SPEED_10000,
				       ETHTOOL_LINK_MODE_10000baseKX4_Full_BIT);
	MLX4_BUILD_PTYS2ETHTOOL_CONFIG(MLX4_10GBASE_KR, SPEED_10000,
				       ETHTOOL_LINK_MODE_10000baseKR_Full_BIT);
	MLX4_BUILD_PTYS2ETHTOOL_CONFIG(MLX4_10GBASE_CR, SPEED_10000,
				       ETHTOOL_LINK_MODE_10000baseKR_Full_BIT);
	MLX4_BUILD_PTYS2ETHTOOL_CONFIG(MLX4_10GBASE_SR, SPEED_10000,
				       ETHTOOL_LINK_MODE_10000baseKR_Full_BIT);
	MLX4_BUILD_PTYS2ETHTOOL_CONFIG(MLX4_20GBASE_KR2, SPEED_20000,
				       ETHTOOL_LINK_MODE_20000baseMLD2_Full_BIT,
				       ETHTOOL_LINK_MODE_20000baseKR2_Full_BIT);
	MLX4_BUILD_PTYS2ETHTOOL_CONFIG(MLX4_40GBASE_CR4, SPEED_40000,
				       ETHTOOL_LINK_MODE_40000baseCR4_Full_BIT);
	MLX4_BUILD_PTYS2ETHTOOL_CONFIG(MLX4_40GBASE_KR4, SPEED_40000,
				       ETHTOOL_LINK_MODE_40000baseKR4_Full_BIT);
	MLX4_BUILD_PTYS2ETHTOOL_CONFIG(MLX4_40GBASE_SR4, SPEED_40000,
				       ETHTOOL_LINK_MODE_40000baseSR4_Full_BIT);
	MLX4_BUILD_PTYS2ETHTOOL_CONFIG(MLX4_56GBASE_KR4, SPEED_56000,
				       ETHTOOL_LINK_MODE_56000baseKR4_Full_BIT);
	MLX4_BUILD_PTYS2ETHTOOL_CONFIG(MLX4_56GBASE_CR4, SPEED_56000,
				       ETHTOOL_LINK_MODE_56000baseCR4_Full_BIT);
	MLX4_BUILD_PTYS2ETHTOOL_CONFIG(MLX4_56GBASE_SR4, SPEED_56000,
				       ETHTOOL_LINK_MODE_56000baseSR4_Full_BIT);
पूर्ण;

अटल व्योम ptys2ethtool_update_link_modes(अचिन्हित दीर्घ *link_modes,
					   u32 eth_proto,
					   क्रमागत ethtool_report report)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < MLX4_LINK_MODES_SZ; i++) अणु
		अगर (eth_proto & MLX4_PROT_MASK(i))
			biपंचांगap_or(link_modes, link_modes,
				  ptys2ethtool_link_mode(&ptys2ethtool_map[i],
							 report),
				  __ETHTOOL_LINK_MODE_MASK_NBITS);
	पूर्ण
पूर्ण

अटल u32 ethtool2ptys_link_modes(स्थिर अचिन्हित दीर्घ *link_modes,
				   क्रमागत ethtool_report report)
अणु
	पूर्णांक i;
	u32 ptys_modes = 0;

	क्रम (i = 0; i < MLX4_LINK_MODES_SZ; i++) अणु
		अगर (biपंचांगap_पूर्णांकersects(
			    ptys2ethtool_link_mode(&ptys2ethtool_map[i],
						   report),
			    link_modes,
			    __ETHTOOL_LINK_MODE_MASK_NBITS))
			ptys_modes |= 1 << i;
	पूर्ण
	वापस ptys_modes;
पूर्ण

/* Convert actual speed (SPEED_XXX) to ptys link modes */
अटल u32 speed2ptys_link_modes(u32 speed)
अणु
	पूर्णांक i;
	u32 ptys_modes = 0;

	क्रम (i = 0; i < MLX4_LINK_MODES_SZ; i++) अणु
		अगर (ptys2ethtool_map[i].speed == speed)
			ptys_modes |= 1 << i;
	पूर्ण
	वापस ptys_modes;
पूर्ण

अटल पूर्णांक
ethtool_get_ptys_link_ksettings(काष्ठा net_device *dev,
				काष्ठा ethtool_link_ksettings *link_ksettings)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_ptys_reg ptys_reg;
	u32 eth_proto;
	पूर्णांक ret;

	स_रखो(&ptys_reg, 0, माप(ptys_reg));
	ptys_reg.local_port = priv->port;
	ptys_reg.proto_mask = MLX4_PTYS_EN;
	ret = mlx4_ACCESS_PTYS_REG(priv->mdev->dev,
				   MLX4_ACCESS_REG_QUERY, &ptys_reg);
	अगर (ret) अणु
		en_warn(priv, "Failed to run mlx4_ACCESS_PTYS_REG status(%x)",
			ret);
		वापस ret;
	पूर्ण
	en_dbg(DRV, priv, "ptys_reg.proto_mask       %x\n",
	       ptys_reg.proto_mask);
	en_dbg(DRV, priv, "ptys_reg.eth_proto_cap    %x\n",
	       be32_to_cpu(ptys_reg.eth_proto_cap));
	en_dbg(DRV, priv, "ptys_reg.eth_proto_admin  %x\n",
	       be32_to_cpu(ptys_reg.eth_proto_admin));
	en_dbg(DRV, priv, "ptys_reg.eth_proto_oper   %x\n",
	       be32_to_cpu(ptys_reg.eth_proto_oper));
	en_dbg(DRV, priv, "ptys_reg.eth_proto_lp_adv %x\n",
	       be32_to_cpu(ptys_reg.eth_proto_lp_adv));

	/* reset supported/advertising masks */
	ethtool_link_ksettings_zero_link_mode(link_ksettings, supported);
	ethtool_link_ksettings_zero_link_mode(link_ksettings, advertising);

	ptys2ethtool_update_supported_port(link_ksettings->link_modes.supported,
					   &ptys_reg);

	eth_proto = be32_to_cpu(ptys_reg.eth_proto_cap);
	ptys2ethtool_update_link_modes(link_ksettings->link_modes.supported,
				       eth_proto, SUPPORTED);

	eth_proto = be32_to_cpu(ptys_reg.eth_proto_admin);
	ptys2ethtool_update_link_modes(link_ksettings->link_modes.advertising,
				       eth_proto, ADVERTISED);

	ethtool_link_ksettings_add_link_mode(link_ksettings, supported,
					     Pause);
	ethtool_link_ksettings_add_link_mode(link_ksettings, supported,
					     Asym_Pause);

	अगर (priv->prof->tx_छोड़ो)
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     advertising, Pause);
	अगर (priv->prof->tx_छोड़ो ^ priv->prof->rx_छोड़ो)
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     advertising, Asym_Pause);

	link_ksettings->base.port = ptys_get_active_port(&ptys_reg);

	अगर (mlx4_en_स्वतःneg_get(dev)) अणु
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     supported, Autoneg);
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     advertising, Autoneg);
	पूर्ण

	link_ksettings->base.स्वतःneg
		= (priv->port_state.flags & MLX4_EN_PORT_ANC) ?
		AUTONEG_ENABLE : AUTONEG_DISABLE;

	eth_proto = be32_to_cpu(ptys_reg.eth_proto_lp_adv);

	ethtool_link_ksettings_zero_link_mode(link_ksettings, lp_advertising);
	ptys2ethtool_update_link_modes(
		link_ksettings->link_modes.lp_advertising,
		eth_proto, ADVERTISED);
	अगर (priv->port_state.flags & MLX4_EN_PORT_ANC)
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     lp_advertising, Autoneg);

	link_ksettings->base.phy_address = 0;
	link_ksettings->base.mdio_support = 0;
	link_ksettings->base.eth_tp_mdix = ETH_TP_MDI_INVALID;
	link_ksettings->base.eth_tp_mdix_ctrl = ETH_TP_MDI_AUTO;

	वापस ret;
पूर्ण

अटल व्योम
ethtool_get_शेष_link_ksettings(
	काष्ठा net_device *dev, काष्ठा ethtool_link_ksettings *link_ksettings)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	पूर्णांक trans_type;

	link_ksettings->base.स्वतःneg = AUTONEG_DISABLE;

	ethtool_link_ksettings_zero_link_mode(link_ksettings, supported);
	ethtool_link_ksettings_add_link_mode(link_ksettings, supported,
					     10000baseT_Full);

	ethtool_link_ksettings_zero_link_mode(link_ksettings, advertising);
	ethtool_link_ksettings_add_link_mode(link_ksettings, advertising,
					     10000baseT_Full);

	trans_type = priv->port_state.transceiver;
	अगर (trans_type > 0 && trans_type <= 0xC) अणु
		link_ksettings->base.port = PORT_FIBRE;
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     supported, FIBRE);
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     advertising, FIBRE);
	पूर्ण अन्यथा अगर (trans_type == 0x80 || trans_type == 0) अणु
		link_ksettings->base.port = PORT_TP;
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     supported, TP);
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     advertising, TP);
	पूर्ण अन्यथा  अणु
		link_ksettings->base.port = -1;
	पूर्ण
पूर्ण

अटल पूर्णांक
mlx4_en_get_link_ksettings(काष्ठा net_device *dev,
			   काष्ठा ethtool_link_ksettings *link_ksettings)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	पूर्णांक ret = -EINVAL;

	अगर (mlx4_en_QUERY_PORT(priv->mdev, priv->port))
		वापस -ENOMEM;

	en_dbg(DRV, priv, "query port state.flags ANC(%x) ANE(%x)\n",
	       priv->port_state.flags & MLX4_EN_PORT_ANC,
	       priv->port_state.flags & MLX4_EN_PORT_ANE);

	अगर (priv->mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_ETH_PROT_CTRL)
		ret = ethtool_get_ptys_link_ksettings(dev, link_ksettings);
	अगर (ret) /* ETH PROT CRTL is not supported or PTYS CMD failed */
		ethtool_get_शेष_link_ksettings(dev, link_ksettings);

	अगर (netअगर_carrier_ok(dev)) अणु
		link_ksettings->base.speed = priv->port_state.link_speed;
		link_ksettings->base.duplex = DUPLEX_FULL;
	पूर्ण अन्यथा अणु
		link_ksettings->base.speed = SPEED_UNKNOWN;
		link_ksettings->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण
	वापस 0;
पूर्ण

/* Calculate PTYS admin according ethtool speed (SPEED_XXX) */
अटल __be32 speed_set_ptys_admin(काष्ठा mlx4_en_priv *priv, u32 speed,
				   __be32 proto_cap)
अणु
	__be32 proto_admin = 0;

	अगर (!speed) अणु /* Speed = 0 ==> Reset Link modes */
		proto_admin = proto_cap;
		en_info(priv, "Speed was set to 0, Reset advertised Link Modes to default (%x)\n",
			be32_to_cpu(proto_cap));
	पूर्ण अन्यथा अणु
		u32 ptys_link_modes = speed2ptys_link_modes(speed);

		proto_admin = cpu_to_be32(ptys_link_modes) & proto_cap;
		en_info(priv, "Setting Speed to %d\n", speed);
	पूर्ण
	वापस proto_admin;
पूर्ण

अटल पूर्णांक
mlx4_en_set_link_ksettings(काष्ठा net_device *dev,
			   स्थिर काष्ठा ethtool_link_ksettings *link_ksettings)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_ptys_reg ptys_reg;
	__be32 proto_admin;
	u8 cur_स्वतःneg;
	पूर्णांक ret;

	u32 ptys_adv = ethtool2ptys_link_modes(
		link_ksettings->link_modes.advertising, ADVERTISED);
	स्थिर पूर्णांक speed = link_ksettings->base.speed;

	en_dbg(DRV, priv,
	       "Set Speed=%d adv={%*pbl} autoneg=%d duplex=%d\n",
	       speed, __ETHTOOL_LINK_MODE_MASK_NBITS,
	       link_ksettings->link_modes.advertising,
	       link_ksettings->base.स्वतःneg,
	       link_ksettings->base.duplex);

	अगर (!(priv->mdev->dev->caps.flags2 &
	      MLX4_DEV_CAP_FLAG2_ETH_PROT_CTRL) ||
	    (link_ksettings->base.duplex == DUPLEX_HALF))
		वापस -EINVAL;

	स_रखो(&ptys_reg, 0, माप(ptys_reg));
	ptys_reg.local_port = priv->port;
	ptys_reg.proto_mask = MLX4_PTYS_EN;
	ret = mlx4_ACCESS_PTYS_REG(priv->mdev->dev,
				   MLX4_ACCESS_REG_QUERY, &ptys_reg);
	अगर (ret) अणु
		en_warn(priv, "Failed to QUERY mlx4_ACCESS_PTYS_REG status(%x)\n",
			ret);
		वापस 0;
	पूर्ण

	cur_स्वतःneg = ptys_reg.flags & MLX4_PTYS_AN_DISABLE_ADMIN ?
				AUTONEG_DISABLE : AUTONEG_ENABLE;

	अगर (link_ksettings->base.स्वतःneg == AUTONEG_DISABLE) अणु
		proto_admin = speed_set_ptys_admin(priv, speed,
						   ptys_reg.eth_proto_cap);
		अगर ((be32_to_cpu(proto_admin) &
		     (MLX4_PROT_MASK(MLX4_1000BASE_CX_SGMII) |
		      MLX4_PROT_MASK(MLX4_1000BASE_KX))) &&
		    (ptys_reg.flags & MLX4_PTYS_AN_DISABLE_CAP))
			ptys_reg.flags |= MLX4_PTYS_AN_DISABLE_ADMIN;
	पूर्ण अन्यथा अणु
		proto_admin = cpu_to_be32(ptys_adv);
		ptys_reg.flags &= ~MLX4_PTYS_AN_DISABLE_ADMIN;
	पूर्ण

	proto_admin &= ptys_reg.eth_proto_cap;
	अगर (!proto_admin) अणु
		en_warn(priv, "Not supported link mode(s) requested, check supported link modes.\n");
		वापस -EINVAL; /* nothing to change due to bad input */
	पूर्ण

	अगर ((proto_admin == ptys_reg.eth_proto_admin) &&
	    ((ptys_reg.flags & MLX4_PTYS_AN_DISABLE_CAP) &&
	     (link_ksettings->base.स्वतःneg == cur_स्वतःneg)))
		वापस 0; /* Nothing to change */

	en_dbg(DRV, priv, "mlx4_ACCESS_PTYS_REG SET: ptys_reg.eth_proto_admin = 0x%x\n",
	       be32_to_cpu(proto_admin));

	ptys_reg.eth_proto_admin = proto_admin;
	ret = mlx4_ACCESS_PTYS_REG(priv->mdev->dev, MLX4_ACCESS_REG_WRITE,
				   &ptys_reg);
	अगर (ret) अणु
		en_warn(priv, "Failed to write mlx4_ACCESS_PTYS_REG eth_proto_admin(0x%x) status(0x%x)",
			be32_to_cpu(ptys_reg.eth_proto_admin), ret);
		वापस ret;
	पूर्ण

	mutex_lock(&priv->mdev->state_lock);
	अगर (priv->port_up) अणु
		en_warn(priv, "Port link mode changed, restarting port...\n");
		mlx4_en_stop_port(dev, 1);
		अगर (mlx4_en_start_port(dev))
			en_err(priv, "Failed restarting port %d\n", priv->port);
	पूर्ण
	mutex_unlock(&priv->mdev->state_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_en_get_coalesce(काष्ठा net_device *dev,
			      काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);

	coal->tx_coalesce_usecs = priv->tx_usecs;
	coal->tx_max_coalesced_frames = priv->tx_frames;
	coal->tx_max_coalesced_frames_irq = priv->tx_work_limit;

	coal->rx_coalesce_usecs = priv->rx_usecs;
	coal->rx_max_coalesced_frames = priv->rx_frames;

	coal->pkt_rate_low = priv->pkt_rate_low;
	coal->rx_coalesce_usecs_low = priv->rx_usecs_low;
	coal->pkt_rate_high = priv->pkt_rate_high;
	coal->rx_coalesce_usecs_high = priv->rx_usecs_high;
	coal->rate_sample_पूर्णांकerval = priv->sample_पूर्णांकerval;
	coal->use_adaptive_rx_coalesce = priv->adaptive_rx_coal;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_en_set_coalesce(काष्ठा net_device *dev,
			      काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);

	अगर (!coal->tx_max_coalesced_frames_irq)
		वापस -EINVAL;

	अगर (coal->tx_coalesce_usecs > MLX4_EN_MAX_COAL_TIME ||
	    coal->rx_coalesce_usecs > MLX4_EN_MAX_COAL_TIME ||
	    coal->rx_coalesce_usecs_low > MLX4_EN_MAX_COAL_TIME ||
	    coal->rx_coalesce_usecs_high > MLX4_EN_MAX_COAL_TIME) अणु
		netdev_info(dev, "%s: maximum coalesce time supported is %d usecs\n",
			    __func__, MLX4_EN_MAX_COAL_TIME);
		वापस -दुस्फल;
	पूर्ण

	अगर (coal->tx_max_coalesced_frames > MLX4_EN_MAX_COAL_PKTS ||
	    coal->rx_max_coalesced_frames > MLX4_EN_MAX_COAL_PKTS) अणु
		netdev_info(dev, "%s: maximum coalesced frames supported is %d\n",
			    __func__, MLX4_EN_MAX_COAL_PKTS);
		वापस -दुस्फल;
	पूर्ण

	priv->rx_frames = (coal->rx_max_coalesced_frames ==
			   MLX4_EN_AUTO_CONF) ?
				MLX4_EN_RX_COAL_TARGET :
				coal->rx_max_coalesced_frames;
	priv->rx_usecs = (coal->rx_coalesce_usecs ==
			  MLX4_EN_AUTO_CONF) ?
				MLX4_EN_RX_COAL_TIME :
				coal->rx_coalesce_usecs;

	/* Setting TX coalescing parameters */
	अगर (coal->tx_coalesce_usecs != priv->tx_usecs ||
	    coal->tx_max_coalesced_frames != priv->tx_frames) अणु
		priv->tx_usecs = coal->tx_coalesce_usecs;
		priv->tx_frames = coal->tx_max_coalesced_frames;
	पूर्ण

	/* Set adaptive coalescing params */
	priv->pkt_rate_low = coal->pkt_rate_low;
	priv->rx_usecs_low = coal->rx_coalesce_usecs_low;
	priv->pkt_rate_high = coal->pkt_rate_high;
	priv->rx_usecs_high = coal->rx_coalesce_usecs_high;
	priv->sample_पूर्णांकerval = coal->rate_sample_पूर्णांकerval;
	priv->adaptive_rx_coal = coal->use_adaptive_rx_coalesce;
	priv->tx_work_limit = coal->tx_max_coalesced_frames_irq;

	वापस mlx4_en_moderation_update(priv);
पूर्ण

अटल पूर्णांक mlx4_en_set_छोड़ोparam(काष्ठा net_device *dev,
				काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	u8 tx_छोड़ो, tx_ppp, rx_छोड़ो, rx_ppp;
	पूर्णांक err;

	अगर (छोड़ो->स्वतःneg)
		वापस -EINVAL;

	tx_छोड़ो = !!(छोड़ो->tx_छोड़ो);
	rx_छोड़ो = !!(छोड़ो->rx_छोड़ो);
	rx_ppp = (tx_छोड़ो || rx_छोड़ो) ? 0 : priv->prof->rx_ppp;
	tx_ppp = (tx_छोड़ो || rx_छोड़ो) ? 0 : priv->prof->tx_ppp;

	err = mlx4_SET_PORT_general(mdev->dev, priv->port,
				    priv->rx_skb_size + ETH_FCS_LEN,
				    tx_छोड़ो, tx_ppp, rx_छोड़ो, rx_ppp);
	अगर (err) अणु
		en_err(priv, "Failed setting pause params, err = %d\n", err);
		वापस err;
	पूर्ण

	mlx4_en_update_pfc_stats_biपंचांगap(mdev->dev, &priv->stats_biपंचांगap,
					rx_ppp, rx_छोड़ो, tx_ppp, tx_छोड़ो);

	priv->prof->tx_छोड़ो = tx_छोड़ो;
	priv->prof->rx_छोड़ो = rx_छोड़ो;
	priv->prof->tx_ppp = tx_ppp;
	priv->prof->rx_ppp = rx_ppp;

	वापस err;
पूर्ण

अटल व्योम mlx4_en_get_छोड़ो_stats(काष्ठा net_device *dev,
				    काष्ठा ethtool_छोड़ो_stats *stats)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा biपंचांगap_iterator it;

	biपंचांगap_iterator_init(&it, priv->stats_biपंचांगap.biपंचांगap, NUM_ALL_STATS);

	spin_lock_bh(&priv->stats_lock);
	अगर (test_bit(FLOW_PRIORITY_STATS_IDX_TX_FRAMES,
		     priv->stats_biपंचांगap.biपंचांगap))
		stats->tx_छोड़ो_frames = priv->tx_flowstats.tx_छोड़ो;
	अगर (test_bit(FLOW_PRIORITY_STATS_IDX_RX_FRAMES,
		     priv->stats_biपंचांगap.biपंचांगap))
		stats->rx_छोड़ो_frames = priv->rx_flowstats.rx_छोड़ो;
	spin_unlock_bh(&priv->stats_lock);
पूर्ण

अटल व्योम mlx4_en_get_छोड़ोparam(काष्ठा net_device *dev,
				 काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);

	छोड़ो->tx_छोड़ो = priv->prof->tx_छोड़ो;
	छोड़ो->rx_छोड़ो = priv->prof->rx_छोड़ो;
पूर्ण

अटल पूर्णांक mlx4_en_set_ringparam(काष्ठा net_device *dev,
				 काष्ठा ethtool_ringparam *param)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा mlx4_en_port_profile new_prof;
	काष्ठा mlx4_en_priv *पंचांगp;
	u32 rx_size, tx_size;
	पूर्णांक port_up = 0;
	पूर्णांक err = 0;

	अगर (param->rx_jumbo_pending || param->rx_mini_pending)
		वापस -EINVAL;

	अगर (param->rx_pending < MLX4_EN_MIN_RX_SIZE) अणु
		en_warn(priv, "%s: rx_pending (%d) < min (%d)\n",
			__func__, param->rx_pending,
			MLX4_EN_MIN_RX_SIZE);
		वापस -EINVAL;
	पूर्ण
	अगर (param->tx_pending < MLX4_EN_MIN_TX_SIZE) अणु
		en_warn(priv, "%s: tx_pending (%d) < min (%lu)\n",
			__func__, param->tx_pending,
			MLX4_EN_MIN_TX_SIZE);
		वापस -EINVAL;
	पूर्ण

	rx_size = roundup_घात_of_two(param->rx_pending);
	tx_size = roundup_घात_of_two(param->tx_pending);

	अगर (rx_size == (priv->port_up ? priv->rx_ring[0]->actual_size :
					priv->rx_ring[0]->size) &&
	    tx_size == priv->tx_ring[TX][0]->size)
		वापस 0;

	पंचांगp = kzalloc(माप(*पंचांगp), GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	mutex_lock(&mdev->state_lock);
	स_नकल(&new_prof, priv->prof, माप(काष्ठा mlx4_en_port_profile));
	new_prof.tx_ring_size = tx_size;
	new_prof.rx_ring_size = rx_size;
	err = mlx4_en_try_alloc_resources(priv, पंचांगp, &new_prof, true);
	अगर (err)
		जाओ out;

	अगर (priv->port_up) अणु
		port_up = 1;
		mlx4_en_stop_port(dev, 1);
	पूर्ण

	mlx4_en_safe_replace_resources(priv, पंचांगp);

	अगर (port_up) अणु
		err = mlx4_en_start_port(dev);
		अगर (err)
			en_err(priv, "Failed starting port\n");
	पूर्ण

	err = mlx4_en_moderation_update(priv);
out:
	kमुक्त(पंचांगp);
	mutex_unlock(&mdev->state_lock);
	वापस err;
पूर्ण

अटल व्योम mlx4_en_get_ringparam(काष्ठा net_device *dev,
				  काष्ठा ethtool_ringparam *param)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);

	स_रखो(param, 0, माप(*param));
	param->rx_max_pending = MLX4_EN_MAX_RX_SIZE;
	param->tx_max_pending = MLX4_EN_MAX_TX_SIZE;
	param->rx_pending = priv->port_up ?
		priv->rx_ring[0]->actual_size : priv->rx_ring[0]->size;
	param->tx_pending = priv->tx_ring[TX][0]->size;
पूर्ण

अटल u32 mlx4_en_get_rxfh_indir_size(काष्ठा net_device *dev)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);

	वापस roundकरोwn_घात_of_two(priv->rx_ring_num);
पूर्ण

अटल u32 mlx4_en_get_rxfh_key_size(काष्ठा net_device *netdev)
अणु
	वापस MLX4_EN_RSS_KEY_SIZE;
पूर्ण

अटल पूर्णांक mlx4_en_check_rxfh_func(काष्ठा net_device *dev, u8 hfunc)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);

	/* check अगर requested function is supported by the device */
	अगर (hfunc == ETH_RSS_HASH_TOP) अणु
		अगर (!(priv->mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_RSS_TOP))
			वापस -EINVAL;
		अगर (!(dev->features & NETIF_F_RXHASH))
			en_warn(priv, "Toeplitz hash function should be used in conjunction with RX hashing for optimal performance\n");
		वापस 0;
	पूर्ण अन्यथा अगर (hfunc == ETH_RSS_HASH_XOR) अणु
		अगर (!(priv->mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_RSS_XOR))
			वापस -EINVAL;
		अगर (dev->features & NETIF_F_RXHASH)
			en_warn(priv, "Enabling both XOR Hash function and RX Hashing can limit RPS functionality\n");
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mlx4_en_get_rxfh(काष्ठा net_device *dev, u32 *ring_index, u8 *key,
			    u8 *hfunc)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	u32 n = mlx4_en_get_rxfh_indir_size(dev);
	u32 i, rss_rings;

	rss_rings = priv->prof->rss_rings ?: n;
	rss_rings = roundकरोwn_घात_of_two(rss_rings);

	क्रम (i = 0; i < n; i++) अणु
		अगर (!ring_index)
			अवरोध;
		ring_index[i] = i % rss_rings;
	पूर्ण
	अगर (key)
		स_नकल(key, priv->rss_key, MLX4_EN_RSS_KEY_SIZE);
	अगर (hfunc)
		*hfunc = priv->rss_hash_fn;
	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_en_set_rxfh(काष्ठा net_device *dev, स्थिर u32 *ring_index,
			    स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	u32 n = mlx4_en_get_rxfh_indir_size(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	पूर्णांक port_up = 0;
	पूर्णांक err = 0;
	पूर्णांक i;
	पूर्णांक rss_rings = 0;

	/* Calculate RSS table size and make sure flows are spपढ़ो evenly
	 * between rings
	 */
	क्रम (i = 0; i < n; i++) अणु
		अगर (!ring_index)
			अवरोध;
		अगर (i > 0 && !ring_index[i] && !rss_rings)
			rss_rings = i;

		अगर (ring_index[i] != (i % (rss_rings ?: n)))
			वापस -EINVAL;
	पूर्ण

	अगर (!rss_rings)
		rss_rings = n;

	/* RSS table size must be an order of 2 */
	अगर (!is_घातer_of_2(rss_rings))
		वापस -EINVAL;

	अगर (hfunc != ETH_RSS_HASH_NO_CHANGE) अणु
		err = mlx4_en_check_rxfh_func(dev, hfunc);
		अगर (err)
			वापस err;
	पूर्ण

	mutex_lock(&mdev->state_lock);
	अगर (priv->port_up) अणु
		port_up = 1;
		mlx4_en_stop_port(dev, 1);
	पूर्ण

	अगर (ring_index)
		priv->prof->rss_rings = rss_rings;
	अगर (key)
		स_नकल(priv->rss_key, key, MLX4_EN_RSS_KEY_SIZE);
	अगर (hfunc !=  ETH_RSS_HASH_NO_CHANGE)
		priv->rss_hash_fn = hfunc;

	अगर (port_up) अणु
		err = mlx4_en_start_port(dev);
		अगर (err)
			en_err(priv, "Failed starting port\n");
	पूर्ण

	mutex_unlock(&mdev->state_lock);
	वापस err;
पूर्ण

#घोषणा all_zeros_or_all_ones(field)		\
	((field) == 0 || (field) == (__क्रमce typeof(field))-1)

अटल पूर्णांक mlx4_en_validate_flow(काष्ठा net_device *dev,
				 काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ethtool_usrip4_spec *l3_mask;
	काष्ठा ethtool_tcpip4_spec *l4_mask;
	काष्ठा ethhdr *eth_mask;

	अगर (cmd->fs.location >= MAX_NUM_OF_FS_RULES)
		वापस -EINVAL;

	अगर (cmd->fs.flow_type & FLOW_MAC_EXT) अणु
		/* dest mac mask must be ff:ff:ff:ff:ff:ff */
		अगर (!is_broadcast_ether_addr(cmd->fs.m_ext.h_dest))
			वापस -EINVAL;
	पूर्ण

	चयन (cmd->fs.flow_type & ~(FLOW_EXT | FLOW_MAC_EXT)) अणु
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW:
		अगर (cmd->fs.m_u.tcp_ip4_spec.tos)
			वापस -EINVAL;
		l4_mask = &cmd->fs.m_u.tcp_ip4_spec;
		/* करोn't allow mask which isn't all 0 or 1 */
		अगर (!all_zeros_or_all_ones(l4_mask->ip4src) ||
		    !all_zeros_or_all_ones(l4_mask->ip4dst) ||
		    !all_zeros_or_all_ones(l4_mask->psrc) ||
		    !all_zeros_or_all_ones(l4_mask->pdst))
			वापस -EINVAL;
		अवरोध;
	हाल IP_USER_FLOW:
		l3_mask = &cmd->fs.m_u.usr_ip4_spec;
		अगर (l3_mask->l4_4_bytes || l3_mask->tos || l3_mask->proto ||
		    cmd->fs.h_u.usr_ip4_spec.ip_ver != ETH_RX_NFC_IP4 ||
		    (!l3_mask->ip4src && !l3_mask->ip4dst) ||
		    !all_zeros_or_all_ones(l3_mask->ip4src) ||
		    !all_zeros_or_all_ones(l3_mask->ip4dst))
			वापस -EINVAL;
		अवरोध;
	हाल ETHER_FLOW:
		eth_mask = &cmd->fs.m_u.ether_spec;
		/* source mac mask must not be set */
		अगर (!is_zero_ether_addr(eth_mask->h_source))
			वापस -EINVAL;

		/* dest mac mask must be ff:ff:ff:ff:ff:ff */
		अगर (!is_broadcast_ether_addr(eth_mask->h_dest))
			वापस -EINVAL;

		अगर (!all_zeros_or_all_ones(eth_mask->h_proto))
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर ((cmd->fs.flow_type & FLOW_EXT)) अणु
		अगर (cmd->fs.m_ext.vlan_etype ||
		    !((cmd->fs.m_ext.vlan_tci & cpu_to_be16(VLAN_VID_MASK)) ==
		      0 ||
		      (cmd->fs.m_ext.vlan_tci & cpu_to_be16(VLAN_VID_MASK)) ==
		      cpu_to_be16(VLAN_VID_MASK)))
			वापस -EINVAL;

		अगर (cmd->fs.m_ext.vlan_tci) अणु
			अगर (be16_to_cpu(cmd->fs.h_ext.vlan_tci) >= VLAN_N_VID)
				वापस -EINVAL;

		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_en_ethtool_add_mac_rule(काष्ठा ethtool_rxnfc *cmd,
					काष्ठा list_head *rule_list_h,
					काष्ठा mlx4_spec_list *spec_l2,
					अचिन्हित अक्षर *mac)
अणु
	__be64 mac_msk = cpu_to_be64(MLX4_MAC_MASK << 16);

	spec_l2->id = MLX4_NET_TRANS_RULE_ID_ETH;
	स_नकल(spec_l2->eth.dst_mac_msk, &mac_msk, ETH_ALEN);
	स_नकल(spec_l2->eth.dst_mac, mac, ETH_ALEN);

	अगर ((cmd->fs.flow_type & FLOW_EXT) &&
	    (cmd->fs.m_ext.vlan_tci & cpu_to_be16(VLAN_VID_MASK))) अणु
		spec_l2->eth.vlan_id = cmd->fs.h_ext.vlan_tci;
		spec_l2->eth.vlan_id_msk = cpu_to_be16(VLAN_VID_MASK);
	पूर्ण

	list_add_tail(&spec_l2->list, rule_list_h);

	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_en_ethtool_add_mac_rule_by_ipv4(काष्ठा mlx4_en_priv *priv,
						काष्ठा ethtool_rxnfc *cmd,
						काष्ठा list_head *rule_list_h,
						काष्ठा mlx4_spec_list *spec_l2,
						__be32 ipv4_dst)
अणु
#अगर_घोषित CONFIG_INET
	अचिन्हित अक्षर mac[ETH_ALEN];

	अगर (!ipv4_is_multicast(ipv4_dst)) अणु
		अगर (cmd->fs.flow_type & FLOW_MAC_EXT)
			स_नकल(&mac, cmd->fs.h_ext.h_dest, ETH_ALEN);
		अन्यथा
			स_नकल(&mac, priv->dev->dev_addr, ETH_ALEN);
	पूर्ण अन्यथा अणु
		ip_eth_mc_map(ipv4_dst, mac);
	पूर्ण

	वापस mlx4_en_ethtool_add_mac_rule(cmd, rule_list_h, spec_l2, &mac[0]);
#अन्यथा
	वापस -EINVAL;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक add_ip_rule(काष्ठा mlx4_en_priv *priv,
		       काष्ठा ethtool_rxnfc *cmd,
		       काष्ठा list_head *list_h)
अणु
	पूर्णांक err;
	काष्ठा mlx4_spec_list *spec_l2 = शून्य;
	काष्ठा mlx4_spec_list *spec_l3 = शून्य;
	काष्ठा ethtool_usrip4_spec *l3_mask = &cmd->fs.m_u.usr_ip4_spec;

	spec_l3 = kzalloc(माप(*spec_l3), GFP_KERNEL);
	spec_l2 = kzalloc(माप(*spec_l2), GFP_KERNEL);
	अगर (!spec_l2 || !spec_l3) अणु
		err = -ENOMEM;
		जाओ मुक्त_spec;
	पूर्ण

	err = mlx4_en_ethtool_add_mac_rule_by_ipv4(priv, cmd, list_h, spec_l2,
						   cmd->fs.h_u.
						   usr_ip4_spec.ip4dst);
	अगर (err)
		जाओ मुक्त_spec;
	spec_l3->id = MLX4_NET_TRANS_RULE_ID_IPV4;
	spec_l3->ipv4.src_ip = cmd->fs.h_u.usr_ip4_spec.ip4src;
	अगर (l3_mask->ip4src)
		spec_l3->ipv4.src_ip_msk = EN_ETHTOOL_WORD_MASK;
	spec_l3->ipv4.dst_ip = cmd->fs.h_u.usr_ip4_spec.ip4dst;
	अगर (l3_mask->ip4dst)
		spec_l3->ipv4.dst_ip_msk = EN_ETHTOOL_WORD_MASK;
	list_add_tail(&spec_l3->list, list_h);

	वापस 0;

मुक्त_spec:
	kमुक्त(spec_l2);
	kमुक्त(spec_l3);
	वापस err;
पूर्ण

अटल पूर्णांक add_tcp_udp_rule(काष्ठा mlx4_en_priv *priv,
			     काष्ठा ethtool_rxnfc *cmd,
			     काष्ठा list_head *list_h, पूर्णांक proto)
अणु
	पूर्णांक err;
	काष्ठा mlx4_spec_list *spec_l2 = शून्य;
	काष्ठा mlx4_spec_list *spec_l3 = शून्य;
	काष्ठा mlx4_spec_list *spec_l4 = शून्य;
	काष्ठा ethtool_tcpip4_spec *l4_mask = &cmd->fs.m_u.tcp_ip4_spec;

	spec_l2 = kzalloc(माप(*spec_l2), GFP_KERNEL);
	spec_l3 = kzalloc(माप(*spec_l3), GFP_KERNEL);
	spec_l4 = kzalloc(माप(*spec_l4), GFP_KERNEL);
	अगर (!spec_l2 || !spec_l3 || !spec_l4) अणु
		err = -ENOMEM;
		जाओ मुक्त_spec;
	पूर्ण

	spec_l3->id = MLX4_NET_TRANS_RULE_ID_IPV4;

	अगर (proto == TCP_V4_FLOW) अणु
		err = mlx4_en_ethtool_add_mac_rule_by_ipv4(priv, cmd, list_h,
							   spec_l2,
							   cmd->fs.h_u.
							   tcp_ip4_spec.ip4dst);
		अगर (err)
			जाओ मुक्त_spec;
		spec_l4->id = MLX4_NET_TRANS_RULE_ID_TCP;
		spec_l3->ipv4.src_ip = cmd->fs.h_u.tcp_ip4_spec.ip4src;
		spec_l3->ipv4.dst_ip = cmd->fs.h_u.tcp_ip4_spec.ip4dst;
		spec_l4->tcp_udp.src_port = cmd->fs.h_u.tcp_ip4_spec.psrc;
		spec_l4->tcp_udp.dst_port = cmd->fs.h_u.tcp_ip4_spec.pdst;
	पूर्ण अन्यथा अणु
		err = mlx4_en_ethtool_add_mac_rule_by_ipv4(priv, cmd, list_h,
							   spec_l2,
							   cmd->fs.h_u.
							   udp_ip4_spec.ip4dst);
		अगर (err)
			जाओ मुक्त_spec;
		spec_l4->id = MLX4_NET_TRANS_RULE_ID_UDP;
		spec_l3->ipv4.src_ip = cmd->fs.h_u.udp_ip4_spec.ip4src;
		spec_l3->ipv4.dst_ip = cmd->fs.h_u.udp_ip4_spec.ip4dst;
		spec_l4->tcp_udp.src_port = cmd->fs.h_u.udp_ip4_spec.psrc;
		spec_l4->tcp_udp.dst_port = cmd->fs.h_u.udp_ip4_spec.pdst;
	पूर्ण

	अगर (l4_mask->ip4src)
		spec_l3->ipv4.src_ip_msk = EN_ETHTOOL_WORD_MASK;
	अगर (l4_mask->ip4dst)
		spec_l3->ipv4.dst_ip_msk = EN_ETHTOOL_WORD_MASK;

	अगर (l4_mask->psrc)
		spec_l4->tcp_udp.src_port_msk = EN_ETHTOOL_SHORT_MASK;
	अगर (l4_mask->pdst)
		spec_l4->tcp_udp.dst_port_msk = EN_ETHTOOL_SHORT_MASK;

	list_add_tail(&spec_l3->list, list_h);
	list_add_tail(&spec_l4->list, list_h);

	वापस 0;

मुक्त_spec:
	kमुक्त(spec_l2);
	kमुक्त(spec_l3);
	kमुक्त(spec_l4);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_en_ethtool_to_net_trans_rule(काष्ठा net_device *dev,
					     काष्ठा ethtool_rxnfc *cmd,
					     काष्ठा list_head *rule_list_h)
अणु
	पूर्णांक err;
	काष्ठा ethhdr *eth_spec;
	काष्ठा mlx4_spec_list *spec_l2;
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);

	err = mlx4_en_validate_flow(dev, cmd);
	अगर (err)
		वापस err;

	चयन (cmd->fs.flow_type & ~(FLOW_EXT | FLOW_MAC_EXT)) अणु
	हाल ETHER_FLOW:
		spec_l2 = kzalloc(माप(*spec_l2), GFP_KERNEL);
		अगर (!spec_l2)
			वापस -ENOMEM;

		eth_spec = &cmd->fs.h_u.ether_spec;
		mlx4_en_ethtool_add_mac_rule(cmd, rule_list_h, spec_l2,
					     &eth_spec->h_dest[0]);
		spec_l2->eth.ether_type = eth_spec->h_proto;
		अगर (eth_spec->h_proto)
			spec_l2->eth.ether_type_enable = 1;
		अवरोध;
	हाल IP_USER_FLOW:
		err = add_ip_rule(priv, cmd, rule_list_h);
		अवरोध;
	हाल TCP_V4_FLOW:
		err = add_tcp_udp_rule(priv, cmd, rule_list_h, TCP_V4_FLOW);
		अवरोध;
	हाल UDP_V4_FLOW:
		err = add_tcp_udp_rule(priv, cmd, rule_list_h, UDP_V4_FLOW);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mlx4_en_flow_replace(काष्ठा net_device *dev,
				काष्ठा ethtool_rxnfc *cmd)
अणु
	पूर्णांक err;
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा ethtool_flow_id *loc_rule;
	काष्ठा mlx4_spec_list *spec, *पंचांगp_spec;
	u32 qpn;
	u64 reg_id;

	काष्ठा mlx4_net_trans_rule rule = अणु
		.queue_mode = MLX4_NET_TRANS_Q_FIFO,
		.exclusive = 0,
		.allow_loopback = 1,
		.promisc_mode = MLX4_FS_REGULAR,
	पूर्ण;

	rule.port = priv->port;
	rule.priority = MLX4_DOMAIN_ETHTOOL | cmd->fs.location;
	INIT_LIST_HEAD(&rule.list);

	/* Allow direct QP attaches अगर the EN_ETHTOOL_QP_ATTACH flag is set */
	अगर (cmd->fs.ring_cookie == RX_CLS_FLOW_DISC)
		qpn = priv->drop_qp.qpn;
	अन्यथा अगर (cmd->fs.ring_cookie & EN_ETHTOOL_QP_ATTACH) अणु
		qpn = cmd->fs.ring_cookie & (EN_ETHTOOL_QP_ATTACH - 1);
	पूर्ण अन्यथा अणु
		अगर (cmd->fs.ring_cookie >= priv->rx_ring_num) अणु
			en_warn(priv, "rxnfc: RX ring (%llu) doesn't exist\n",
				cmd->fs.ring_cookie);
			वापस -EINVAL;
		पूर्ण
		qpn = priv->rss_map.qps[cmd->fs.ring_cookie].qpn;
		अगर (!qpn) अणु
			en_warn(priv, "rxnfc: RX ring (%llu) is inactive\n",
				cmd->fs.ring_cookie);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	rule.qpn = qpn;
	err = mlx4_en_ethtool_to_net_trans_rule(dev, cmd, &rule.list);
	अगर (err)
		जाओ out_मुक्त_list;

	loc_rule = &priv->ethtool_rules[cmd->fs.location];
	अगर (loc_rule->id) अणु
		err = mlx4_flow_detach(priv->mdev->dev, loc_rule->id);
		अगर (err) अणु
			en_err(priv, "Fail to detach network rule at location %d. registration id = %llx\n",
			       cmd->fs.location, loc_rule->id);
			जाओ out_मुक्त_list;
		पूर्ण
		loc_rule->id = 0;
		स_रखो(&loc_rule->flow_spec, 0,
		       माप(काष्ठा ethtool_rx_flow_spec));
		list_del(&loc_rule->list);
	पूर्ण
	err = mlx4_flow_attach(priv->mdev->dev, &rule, &reg_id);
	अगर (err) अणु
		en_err(priv, "Fail to attach network rule at location %d\n",
		       cmd->fs.location);
		जाओ out_मुक्त_list;
	पूर्ण
	loc_rule->id = reg_id;
	स_नकल(&loc_rule->flow_spec, &cmd->fs,
	       माप(काष्ठा ethtool_rx_flow_spec));
	list_add_tail(&loc_rule->list, &priv->ethtool_list);

out_मुक्त_list:
	list_क्रम_each_entry_safe(spec, पंचांगp_spec, &rule.list, list) अणु
		list_del(&spec->list);
		kमुक्त(spec);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_en_flow_detach(काष्ठा net_device *dev,
			       काष्ठा ethtool_rxnfc *cmd)
अणु
	पूर्णांक err = 0;
	काष्ठा ethtool_flow_id *rule;
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);

	अगर (cmd->fs.location >= MAX_NUM_OF_FS_RULES)
		वापस -EINVAL;

	rule = &priv->ethtool_rules[cmd->fs.location];
	अगर (!rule->id) अणु
		err =  -ENOENT;
		जाओ out;
	पूर्ण

	err = mlx4_flow_detach(priv->mdev->dev, rule->id);
	अगर (err) अणु
		en_err(priv, "Fail to detach network rule at location %d. registration id = 0x%llx\n",
		       cmd->fs.location, rule->id);
		जाओ out;
	पूर्ण
	rule->id = 0;
	स_रखो(&rule->flow_spec, 0, माप(काष्ठा ethtool_rx_flow_spec));
	list_del(&rule->list);
out:
	वापस err;

पूर्ण

अटल पूर्णांक mlx4_en_get_flow(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd,
			    पूर्णांक loc)
अणु
	पूर्णांक err = 0;
	काष्ठा ethtool_flow_id *rule;
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);

	अगर (loc < 0 || loc >= MAX_NUM_OF_FS_RULES)
		वापस -EINVAL;

	rule = &priv->ethtool_rules[loc];
	अगर (rule->id)
		स_नकल(&cmd->fs, &rule->flow_spec,
		       माप(काष्ठा ethtool_rx_flow_spec));
	अन्यथा
		err = -ENOENT;

	वापस err;
पूर्ण

अटल पूर्णांक mlx4_en_get_num_flows(काष्ठा mlx4_en_priv *priv)
अणु

	पूर्णांक i, res = 0;
	क्रम (i = 0; i < MAX_NUM_OF_FS_RULES; i++) अणु
		अगर (priv->ethtool_rules[i].id)
			res++;
	पूर्ण
	वापस res;

पूर्ण

अटल पूर्णांक mlx4_en_get_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd,
			     u32 *rule_locs)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	पूर्णांक err = 0;
	पूर्णांक i = 0, priority = 0;

	अगर ((cmd->cmd == ETHTOOL_GRXCLSRLCNT ||
	     cmd->cmd == ETHTOOL_GRXCLSRULE ||
	     cmd->cmd == ETHTOOL_GRXCLSRLALL) &&
	    (mdev->dev->caps.steering_mode !=
	     MLX4_STEERING_MODE_DEVICE_MANAGED || !priv->port_up))
		वापस -EINVAL;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		cmd->data = priv->rx_ring_num;
		अवरोध;
	हाल ETHTOOL_GRXCLSRLCNT:
		cmd->rule_cnt = mlx4_en_get_num_flows(priv);
		अवरोध;
	हाल ETHTOOL_GRXCLSRULE:
		err = mlx4_en_get_flow(dev, cmd, cmd->fs.location);
		अवरोध;
	हाल ETHTOOL_GRXCLSRLALL:
		cmd->data = MAX_NUM_OF_FS_RULES;
		जबतक ((!err || err == -ENOENT) && priority < cmd->rule_cnt) अणु
			err = mlx4_en_get_flow(dev, cmd, i);
			अगर (!err)
				rule_locs[priority++] = i;
			i++;
		पूर्ण
		err = 0;
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mlx4_en_set_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd)
अणु
	पूर्णांक err = 0;
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;

	अगर (mdev->dev->caps.steering_mode !=
	    MLX4_STEERING_MODE_DEVICE_MANAGED || !priv->port_up)
		वापस -EINVAL;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_SRXCLSRLINS:
		err = mlx4_en_flow_replace(dev, cmd);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLDEL:
		err = mlx4_en_flow_detach(dev, cmd);
		अवरोध;
	शेष:
		en_warn(priv, "Unsupported ethtool command. (%d)\n", cmd->cmd);
		वापस -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mlx4_en_get_max_num_rx_rings(काष्ठा net_device *dev)
अणु
	वापस min_t(पूर्णांक, num_online_cpus(), MAX_RX_RINGS);
पूर्ण

अटल व्योम mlx4_en_get_channels(काष्ठा net_device *dev,
				 काष्ठा ethtool_channels *channel)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);

	channel->max_rx = mlx4_en_get_max_num_rx_rings(dev);
	channel->max_tx = priv->mdev->profile.max_num_tx_rings_p_up;

	channel->rx_count = priv->rx_ring_num;
	channel->tx_count = priv->tx_ring_num[TX] /
			    priv->prof->num_up;
पूर्ण

अटल पूर्णांक mlx4_en_set_channels(काष्ठा net_device *dev,
				काष्ठा ethtool_channels *channel)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा mlx4_en_port_profile new_prof;
	काष्ठा mlx4_en_priv *पंचांगp;
	पूर्णांक total_tx_count;
	पूर्णांक port_up = 0;
	पूर्णांक xdp_count;
	पूर्णांक err = 0;
	u8 up;

	अगर (!channel->tx_count || !channel->rx_count)
		वापस -EINVAL;

	पंचांगp = kzalloc(माप(*पंचांगp), GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	mutex_lock(&mdev->state_lock);
	xdp_count = priv->tx_ring_num[TX_XDP] ? channel->rx_count : 0;
	total_tx_count = channel->tx_count * priv->prof->num_up + xdp_count;
	अगर (total_tx_count > MAX_TX_RINGS) अणु
		err = -EINVAL;
		en_err(priv,
		       "Total number of TX and XDP rings (%d) exceeds the maximum supported (%d)\n",
		       total_tx_count, MAX_TX_RINGS);
		जाओ out;
	पूर्ण

	स_नकल(&new_prof, priv->prof, माप(काष्ठा mlx4_en_port_profile));
	new_prof.num_tx_rings_p_up = channel->tx_count;
	new_prof.tx_ring_num[TX] = channel->tx_count * priv->prof->num_up;
	new_prof.tx_ring_num[TX_XDP] = xdp_count;
	new_prof.rx_ring_num = channel->rx_count;

	err = mlx4_en_try_alloc_resources(priv, पंचांगp, &new_prof, true);
	अगर (err)
		जाओ out;

	अगर (priv->port_up) अणु
		port_up = 1;
		mlx4_en_stop_port(dev, 1);
	पूर्ण

	mlx4_en_safe_replace_resources(priv, पंचांगp);

	netअगर_set_real_num_rx_queues(dev, priv->rx_ring_num);

	up = (priv->prof->num_up == MLX4_EN_NUM_UP_LOW) ?
				    0 : priv->prof->num_up;
	mlx4_en_setup_tc(dev, up);

	en_warn(priv, "Using %d TX rings\n", priv->tx_ring_num[TX]);
	en_warn(priv, "Using %d RX rings\n", priv->rx_ring_num);

	अगर (port_up) अणु
		err = mlx4_en_start_port(dev);
		अगर (err)
			en_err(priv, "Failed starting port\n");
	पूर्ण

	err = mlx4_en_moderation_update(priv);
out:
	mutex_unlock(&mdev->state_lock);
	kमुक्त(पंचांगp);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_en_get_ts_info(काष्ठा net_device *dev,
			       काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	पूर्णांक ret;

	ret = ethtool_op_get_ts_info(dev, info);
	अगर (ret)
		वापस ret;

	अगर (mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_TS) अणु
		info->so_बारtamping |=
			SOF_TIMESTAMPING_TX_HARDWARE |
			SOF_TIMESTAMPING_RX_HARDWARE |
			SOF_TIMESTAMPING_RAW_HARDWARE;

		info->tx_types =
			(1 << HWTSTAMP_TX_OFF) |
			(1 << HWTSTAMP_TX_ON);

		info->rx_filters =
			(1 << HWTSTAMP_FILTER_NONE) |
			(1 << HWTSTAMP_FILTER_ALL);

		अगर (mdev->ptp_घड़ी)
			info->phc_index = ptp_घड़ी_index(mdev->ptp_घड़ी);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mlx4_en_set_priv_flags(काष्ठा net_device *dev, u32 flags)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	bool bf_enabled_new = !!(flags & MLX4_EN_PRIV_FLAGS_BLUEFLAME);
	bool bf_enabled_old = !!(priv->pflags & MLX4_EN_PRIV_FLAGS_BLUEFLAME);
	bool phv_enabled_new = !!(flags & MLX4_EN_PRIV_FLAGS_PHV);
	bool phv_enabled_old = !!(priv->pflags & MLX4_EN_PRIV_FLAGS_PHV);
	पूर्णांक i;
	पूर्णांक ret = 0;

	अगर (bf_enabled_new != bf_enabled_old) अणु
		पूर्णांक t;

		अगर (bf_enabled_new) अणु
			bool bf_supported = true;

			क्रम (t = 0; t < MLX4_EN_NUM_TX_TYPES; t++)
				क्रम (i = 0; i < priv->tx_ring_num[t]; i++)
					bf_supported &=
						priv->tx_ring[t][i]->bf_alloced;

			अगर (!bf_supported) अणु
				en_err(priv, "BlueFlame is not supported\n");
				वापस -EINVAL;
			पूर्ण

			priv->pflags |= MLX4_EN_PRIV_FLAGS_BLUEFLAME;
		पूर्ण अन्यथा अणु
			priv->pflags &= ~MLX4_EN_PRIV_FLAGS_BLUEFLAME;
		पूर्ण

		क्रम (t = 0; t < MLX4_EN_NUM_TX_TYPES; t++)
			क्रम (i = 0; i < priv->tx_ring_num[t]; i++)
				priv->tx_ring[t][i]->bf_enabled =
					bf_enabled_new;

		en_info(priv, "BlueFlame %s\n",
			bf_enabled_new ?  "Enabled" : "Disabled");
	पूर्ण

	अगर (phv_enabled_new != phv_enabled_old) अणु
		ret = set_phv_bit(mdev->dev, priv->port, (पूर्णांक)phv_enabled_new);
		अगर (ret)
			वापस ret;
		अन्यथा अगर (phv_enabled_new)
			priv->pflags |= MLX4_EN_PRIV_FLAGS_PHV;
		अन्यथा
			priv->pflags &= ~MLX4_EN_PRIV_FLAGS_PHV;
		en_info(priv, "PHV bit %s\n",
			phv_enabled_new ?  "Enabled" : "Disabled");
	पूर्ण
	वापस 0;
पूर्ण

अटल u32 mlx4_en_get_priv_flags(काष्ठा net_device *dev)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);

	वापस priv->pflags;
पूर्ण

अटल पूर्णांक mlx4_en_get_tunable(काष्ठा net_device *dev,
			       स्थिर काष्ठा ethtool_tunable *tuna,
			       व्योम *data)
अणु
	स्थिर काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	पूर्णांक ret = 0;

	चयन (tuna->id) अणु
	हाल ETHTOOL_TX_COPYBREAK:
		*(u32 *)data = priv->prof->अंतरभूत_thold;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mlx4_en_set_tunable(काष्ठा net_device *dev,
			       स्थिर काष्ठा ethtool_tunable *tuna,
			       स्थिर व्योम *data)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	पूर्णांक val, ret = 0;

	चयन (tuna->id) अणु
	हाल ETHTOOL_TX_COPYBREAK:
		val = *(u32 *)data;
		अगर (val < MIN_PKT_LEN || val > MAX_INLINE)
			ret = -EINVAL;
		अन्यथा
			priv->prof->अंतरभूत_thold = val;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mlx4_en_get_module_info(काष्ठा net_device *dev,
				   काष्ठा ethtool_modinfo *modinfo)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	पूर्णांक ret;
	u8 data[4];

	/* Read first 2 bytes to get Module & REV ID */
	ret = mlx4_get_module_info(mdev->dev, priv->port,
				   0/*offset*/, 2/*size*/, data);
	अगर (ret < 2)
		वापस -EIO;

	चयन (data[0] /* identअगरier */) अणु
	हाल MLX4_MODULE_ID_QSFP:
		modinfo->type = ETH_MODULE_SFF_8436;
		modinfo->eeprom_len = ETH_MODULE_SFF_8436_LEN;
		अवरोध;
	हाल MLX4_MODULE_ID_QSFP_PLUS:
		अगर (data[1] >= 0x3) अणु /* revision id */
			modinfo->type = ETH_MODULE_SFF_8636;
			modinfo->eeprom_len = ETH_MODULE_SFF_8636_LEN;
		पूर्ण अन्यथा अणु
			modinfo->type = ETH_MODULE_SFF_8436;
			modinfo->eeprom_len = ETH_MODULE_SFF_8436_LEN;
		पूर्ण
		अवरोध;
	हाल MLX4_MODULE_ID_QSFP28:
		modinfo->type = ETH_MODULE_SFF_8636;
		modinfo->eeprom_len = ETH_MODULE_SFF_8636_LEN;
		अवरोध;
	हाल MLX4_MODULE_ID_SFP:
		modinfo->type = ETH_MODULE_SFF_8472;
		modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_en_get_module_eeprom(काष्ठा net_device *dev,
				     काष्ठा ethtool_eeprom *ee,
				     u8 *data)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	पूर्णांक offset = ee->offset;
	पूर्णांक i = 0, ret;

	अगर (ee->len == 0)
		वापस -EINVAL;

	स_रखो(data, 0, ee->len);

	जबतक (i < ee->len) अणु
		en_dbg(DRV, priv,
		       "mlx4_get_module_info i(%d) offset(%d) len(%d)\n",
		       i, offset, ee->len - i);

		ret = mlx4_get_module_info(mdev->dev, priv->port,
					   offset, ee->len - i, data + i);

		अगर (!ret) /* Done पढ़ोing */
			वापस 0;

		अगर (ret < 0) अणु
			en_err(priv,
			       "mlx4_get_module_info i(%d) offset(%d) bytes_to_read(%d) - FAILED (0x%x)\n",
			       i, offset, ee->len - i, ret);
			वापस 0;
		पूर्ण

		i += ret;
		offset += ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_en_set_phys_id(काष्ठा net_device *dev,
			       क्रमागत ethtool_phys_id_state state)
अणु
	पूर्णांक err;
	u16 beacon_duration;
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;

	अगर (!(mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_PORT_BEACON))
		वापस -EOPNOTSUPP;

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		beacon_duration = PORT_BEACON_MAX_LIMIT;
		अवरोध;
	हाल ETHTOOL_ID_INACTIVE:
		beacon_duration = 0;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	err = mlx4_SET_PORT_BEACON(mdev->dev, priv->port, beacon_duration);
	वापस err;
पूर्ण

स्थिर काष्ठा ethtool_ops mlx4_en_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES |
				     ETHTOOL_COALESCE_TX_MAX_FRAMES_IRQ |
				     ETHTOOL_COALESCE_PKT_RATE_RX_USECS,
	.get_drvinfo = mlx4_en_get_drvinfo,
	.get_link_ksettings = mlx4_en_get_link_ksettings,
	.set_link_ksettings = mlx4_en_set_link_ksettings,
	.get_link = ethtool_op_get_link,
	.get_strings = mlx4_en_get_strings,
	.get_sset_count = mlx4_en_get_sset_count,
	.get_ethtool_stats = mlx4_en_get_ethtool_stats,
	.self_test = mlx4_en_self_test,
	.set_phys_id = mlx4_en_set_phys_id,
	.get_wol = mlx4_en_get_wol,
	.set_wol = mlx4_en_set_wol,
	.get_msglevel = mlx4_en_get_msglevel,
	.set_msglevel = mlx4_en_set_msglevel,
	.get_coalesce = mlx4_en_get_coalesce,
	.set_coalesce = mlx4_en_set_coalesce,
	.get_छोड़ो_stats = mlx4_en_get_छोड़ो_stats,
	.get_छोड़ोparam = mlx4_en_get_छोड़ोparam,
	.set_छोड़ोparam = mlx4_en_set_छोड़ोparam,
	.get_ringparam = mlx4_en_get_ringparam,
	.set_ringparam = mlx4_en_set_ringparam,
	.get_rxnfc = mlx4_en_get_rxnfc,
	.set_rxnfc = mlx4_en_set_rxnfc,
	.get_rxfh_indir_size = mlx4_en_get_rxfh_indir_size,
	.get_rxfh_key_size = mlx4_en_get_rxfh_key_size,
	.get_rxfh = mlx4_en_get_rxfh,
	.set_rxfh = mlx4_en_set_rxfh,
	.get_channels = mlx4_en_get_channels,
	.set_channels = mlx4_en_set_channels,
	.get_ts_info = mlx4_en_get_ts_info,
	.set_priv_flags = mlx4_en_set_priv_flags,
	.get_priv_flags = mlx4_en_get_priv_flags,
	.get_tunable		= mlx4_en_get_tunable,
	.set_tunable		= mlx4_en_set_tunable,
	.get_module_info = mlx4_en_get_module_info,
	.get_module_eeprom = mlx4_en_get_module_eeprom
पूर्ण;





