<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

/* ethtool support क्रम ixgbevf */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/uaccess.h>

#समावेश "ixgbevf.h"

#घोषणा IXGBE_ALL_RAR_ENTRIES 16

क्रमागत अणुNETDEV_STATS, IXGBEVF_STATSपूर्ण;

काष्ठा ixgbe_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक type;
	पूर्णांक माप_stat;
	पूर्णांक stat_offset;
पूर्ण;

#घोषणा IXGBEVF_STAT(_name, _stat) अणु \
	.stat_string = _name, \
	.type = IXGBEVF_STATS, \
	.माप_stat = माप_field(काष्ठा ixgbevf_adapter, _stat), \
	.stat_offset = दुरत्व(काष्ठा ixgbevf_adapter, _stat) \
पूर्ण

#घोषणा IXGBEVF_NETDEV_STAT(_net_stat) अणु \
	.stat_string = #_net_stat, \
	.type = NETDEV_STATS, \
	.माप_stat = माप_field(काष्ठा net_device_stats, _net_stat), \
	.stat_offset = दुरत्व(काष्ठा net_device_stats, _net_stat) \
पूर्ण

अटल काष्ठा ixgbe_stats ixgbevf_gstrings_stats[] = अणु
	IXGBEVF_NETDEV_STAT(rx_packets),
	IXGBEVF_NETDEV_STAT(tx_packets),
	IXGBEVF_NETDEV_STAT(rx_bytes),
	IXGBEVF_NETDEV_STAT(tx_bytes),
	IXGBEVF_STAT("tx_busy", tx_busy),
	IXGBEVF_STAT("tx_restart_queue", restart_queue),
	IXGBEVF_STAT("tx_timeout_count", tx_समयout_count),
	IXGBEVF_NETDEV_STAT(multicast),
	IXGBEVF_STAT("rx_csum_offload_errors", hw_csum_rx_error),
	IXGBEVF_STAT("alloc_rx_page", alloc_rx_page),
	IXGBEVF_STAT("alloc_rx_page_failed", alloc_rx_page_failed),
	IXGBEVF_STAT("alloc_rx_buff_failed", alloc_rx_buff_failed),
	IXGBEVF_STAT("tx_ipsec", tx_ipsec),
	IXGBEVF_STAT("rx_ipsec", rx_ipsec),
पूर्ण;

#घोषणा IXGBEVF_QUEUE_STATS_LEN ( \
	(((काष्ठा ixgbevf_adapter *)netdev_priv(netdev))->num_tx_queues + \
	 ((काष्ठा ixgbevf_adapter *)netdev_priv(netdev))->num_xdp_queues + \
	 ((काष्ठा ixgbevf_adapter *)netdev_priv(netdev))->num_rx_queues) * \
	 (माप(काष्ठा ixgbevf_stats) / माप(u64)))
#घोषणा IXGBEVF_GLOBAL_STATS_LEN ARRAY_SIZE(ixgbevf_gstrings_stats)

#घोषणा IXGBEVF_STATS_LEN (IXGBEVF_GLOBAL_STATS_LEN + IXGBEVF_QUEUE_STATS_LEN)
अटल स्थिर अक्षर ixgbe_gstrings_test[][ETH_GSTRING_LEN] = अणु
	"Register test  (offline)",
	"Link test   (on/offline)"
पूर्ण;

#घोषणा IXGBEVF_TEST_LEN (माप(ixgbe_gstrings_test) / ETH_GSTRING_LEN)

अटल स्थिर अक्षर ixgbevf_priv_flags_strings[][ETH_GSTRING_LEN] = अणु
#घोषणा IXGBEVF_PRIV_FLAGS_LEGACY_RX	BIT(0)
	"legacy-rx",
पूर्ण;

#घोषणा IXGBEVF_PRIV_FLAGS_STR_LEN ARRAY_SIZE(ixgbevf_priv_flags_strings)

अटल पूर्णांक ixgbevf_get_link_ksettings(काष्ठा net_device *netdev,
				      काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);

	ethtool_link_ksettings_zero_link_mode(cmd, supported);
	ethtool_link_ksettings_add_link_mode(cmd, supported, 10000baseT_Full);
	cmd->base.स्वतःneg = AUTONEG_DISABLE;
	cmd->base.port = -1;

	अगर (adapter->link_up) अणु
		__u32 speed = SPEED_10000;

		चयन (adapter->link_speed) अणु
		हाल IXGBE_LINK_SPEED_10GB_FULL:
			speed = SPEED_10000;
			अवरोध;
		हाल IXGBE_LINK_SPEED_1GB_FULL:
			speed = SPEED_1000;
			अवरोध;
		हाल IXGBE_LINK_SPEED_100_FULL:
			speed = SPEED_100;
			अवरोध;
		पूर्ण

		cmd->base.speed = speed;
		cmd->base.duplex = DUPLEX_FULL;
	पूर्ण अन्यथा अणु
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 ixgbevf_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);

	वापस adapter->msg_enable;
पूर्ण

अटल व्योम ixgbevf_set_msglevel(काष्ठा net_device *netdev, u32 data)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);

	adapter->msg_enable = data;
पूर्ण

#घोषणा IXGBE_GET_STAT(_A_, _R_) (_A_->stats._R_)

अटल पूर्णांक ixgbevf_get_regs_len(काष्ठा net_device *netdev)
अणु
#घोषणा IXGBE_REGS_LEN 45
	वापस IXGBE_REGS_LEN * माप(u32);
पूर्ण

अटल व्योम ixgbevf_get_regs(काष्ठा net_device *netdev,
			     काष्ठा ethtool_regs *regs,
			     व्योम *p)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 *regs_buff = p;
	u32 regs_len = ixgbevf_get_regs_len(netdev);
	u8 i;

	स_रखो(p, 0, regs_len);

	/* generate a number suitable क्रम ethtool's रेजिस्टर version */
	regs->version = (1u << 24) | (hw->revision_id << 16) | hw->device_id;

	/* General Registers */
	regs_buff[0] = IXGBE_READ_REG(hw, IXGBE_VFCTRL);
	regs_buff[1] = IXGBE_READ_REG(hw, IXGBE_VFSTATUS);
	regs_buff[2] = IXGBE_READ_REG(hw, IXGBE_VFLINKS);
	regs_buff[3] = IXGBE_READ_REG(hw, IXGBE_VFRXMEMWRAP);
	regs_buff[4] = IXGBE_READ_REG(hw, IXGBE_VFFRTIMER);

	/* Interrupt */
	/* करोn't पढ़ो EICR because it can clear पूर्णांकerrupt causes, instead
	 * पढ़ो EICS which is a shaकरोw but करोesn't clear EICR
	 */
	regs_buff[5] = IXGBE_READ_REG(hw, IXGBE_VTEICS);
	regs_buff[6] = IXGBE_READ_REG(hw, IXGBE_VTEICS);
	regs_buff[7] = IXGBE_READ_REG(hw, IXGBE_VTEIMS);
	regs_buff[8] = IXGBE_READ_REG(hw, IXGBE_VTEIMC);
	regs_buff[9] = IXGBE_READ_REG(hw, IXGBE_VTEIAC);
	regs_buff[10] = IXGBE_READ_REG(hw, IXGBE_VTEIAM);
	regs_buff[11] = IXGBE_READ_REG(hw, IXGBE_VTEITR(0));
	regs_buff[12] = IXGBE_READ_REG(hw, IXGBE_VTIVAR(0));
	regs_buff[13] = IXGBE_READ_REG(hw, IXGBE_VTIVAR_MISC);

	/* Receive DMA */
	क्रम (i = 0; i < 2; i++)
		regs_buff[14 + i] = IXGBE_READ_REG(hw, IXGBE_VFRDBAL(i));
	क्रम (i = 0; i < 2; i++)
		regs_buff[16 + i] = IXGBE_READ_REG(hw, IXGBE_VFRDBAH(i));
	क्रम (i = 0; i < 2; i++)
		regs_buff[18 + i] = IXGBE_READ_REG(hw, IXGBE_VFRDLEN(i));
	क्रम (i = 0; i < 2; i++)
		regs_buff[20 + i] = IXGBE_READ_REG(hw, IXGBE_VFRDH(i));
	क्रम (i = 0; i < 2; i++)
		regs_buff[22 + i] = IXGBE_READ_REG(hw, IXGBE_VFRDT(i));
	क्रम (i = 0; i < 2; i++)
		regs_buff[24 + i] = IXGBE_READ_REG(hw, IXGBE_VFRXDCTL(i));
	क्रम (i = 0; i < 2; i++)
		regs_buff[26 + i] = IXGBE_READ_REG(hw, IXGBE_VFSRRCTL(i));

	/* Receive */
	regs_buff[28] = IXGBE_READ_REG(hw, IXGBE_VFPSRTYPE);

	/* Transmit */
	क्रम (i = 0; i < 2; i++)
		regs_buff[29 + i] = IXGBE_READ_REG(hw, IXGBE_VFTDBAL(i));
	क्रम (i = 0; i < 2; i++)
		regs_buff[31 + i] = IXGBE_READ_REG(hw, IXGBE_VFTDBAH(i));
	क्रम (i = 0; i < 2; i++)
		regs_buff[33 + i] = IXGBE_READ_REG(hw, IXGBE_VFTDLEN(i));
	क्रम (i = 0; i < 2; i++)
		regs_buff[35 + i] = IXGBE_READ_REG(hw, IXGBE_VFTDH(i));
	क्रम (i = 0; i < 2; i++)
		regs_buff[37 + i] = IXGBE_READ_REG(hw, IXGBE_VFTDT(i));
	क्रम (i = 0; i < 2; i++)
		regs_buff[39 + i] = IXGBE_READ_REG(hw, IXGBE_VFTXDCTL(i));
	क्रम (i = 0; i < 2; i++)
		regs_buff[41 + i] = IXGBE_READ_REG(hw, IXGBE_VFTDWBAL(i));
	क्रम (i = 0; i < 2; i++)
		regs_buff[43 + i] = IXGBE_READ_REG(hw, IXGBE_VFTDWBAH(i));
पूर्ण

अटल व्योम ixgbevf_get_drvinfo(काष्ठा net_device *netdev,
				काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);

	strlcpy(drvinfo->driver, ixgbevf_driver_name, माप(drvinfo->driver));
	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		माप(drvinfo->bus_info));

	drvinfo->n_priv_flags = IXGBEVF_PRIV_FLAGS_STR_LEN;
पूर्ण

अटल व्योम ixgbevf_get_ringparam(काष्ठा net_device *netdev,
				  काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);

	ring->rx_max_pending = IXGBEVF_MAX_RXD;
	ring->tx_max_pending = IXGBEVF_MAX_TXD;
	ring->rx_pending = adapter->rx_ring_count;
	ring->tx_pending = adapter->tx_ring_count;
पूर्ण

अटल पूर्णांक ixgbevf_set_ringparam(काष्ठा net_device *netdev,
				 काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbevf_ring *tx_ring = शून्य, *rx_ring = शून्य;
	u32 new_rx_count, new_tx_count;
	पूर्णांक i, j, err = 0;

	अगर ((ring->rx_mini_pending) || (ring->rx_jumbo_pending))
		वापस -EINVAL;

	new_tx_count = max_t(u32, ring->tx_pending, IXGBEVF_MIN_TXD);
	new_tx_count = min_t(u32, new_tx_count, IXGBEVF_MAX_TXD);
	new_tx_count = ALIGN(new_tx_count, IXGBE_REQ_TX_DESCRIPTOR_MULTIPLE);

	new_rx_count = max_t(u32, ring->rx_pending, IXGBEVF_MIN_RXD);
	new_rx_count = min_t(u32, new_rx_count, IXGBEVF_MAX_RXD);
	new_rx_count = ALIGN(new_rx_count, IXGBE_REQ_RX_DESCRIPTOR_MULTIPLE);

	/* अगर nothing to करो वापस success */
	अगर ((new_tx_count == adapter->tx_ring_count) &&
	    (new_rx_count == adapter->rx_ring_count))
		वापस 0;

	जबतक (test_and_set_bit(__IXGBEVF_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	अगर (!netअगर_running(adapter->netdev)) अणु
		क्रम (i = 0; i < adapter->num_tx_queues; i++)
			adapter->tx_ring[i]->count = new_tx_count;
		क्रम (i = 0; i < adapter->num_xdp_queues; i++)
			adapter->xdp_ring[i]->count = new_tx_count;
		क्रम (i = 0; i < adapter->num_rx_queues; i++)
			adapter->rx_ring[i]->count = new_rx_count;
		adapter->tx_ring_count = new_tx_count;
		adapter->xdp_ring_count = new_tx_count;
		adapter->rx_ring_count = new_rx_count;
		जाओ clear_reset;
	पूर्ण

	अगर (new_tx_count != adapter->tx_ring_count) अणु
		tx_ring = vदो_स्मृति(array_size(माप(*tx_ring),
					     adapter->num_tx_queues +
						adapter->num_xdp_queues));
		अगर (!tx_ring) अणु
			err = -ENOMEM;
			जाओ clear_reset;
		पूर्ण

		क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
			/* clone ring and setup updated count */
			tx_ring[i] = *adapter->tx_ring[i];
			tx_ring[i].count = new_tx_count;
			err = ixgbevf_setup_tx_resources(&tx_ring[i]);
			अगर (err) अणु
				जबतक (i) अणु
					i--;
					ixgbevf_मुक्त_tx_resources(&tx_ring[i]);
				पूर्ण

				vमुक्त(tx_ring);
				tx_ring = शून्य;

				जाओ clear_reset;
			पूर्ण
		पूर्ण

		क्रम (j = 0; j < adapter->num_xdp_queues; i++, j++) अणु
			/* clone ring and setup updated count */
			tx_ring[i] = *adapter->xdp_ring[j];
			tx_ring[i].count = new_tx_count;
			err = ixgbevf_setup_tx_resources(&tx_ring[i]);
			अगर (err) अणु
				जबतक (i) अणु
					i--;
					ixgbevf_मुक्त_tx_resources(&tx_ring[i]);
				पूर्ण

				vमुक्त(tx_ring);
				tx_ring = शून्य;

				जाओ clear_reset;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (new_rx_count != adapter->rx_ring_count) अणु
		rx_ring = vदो_स्मृति(array_size(माप(*rx_ring),
					     adapter->num_rx_queues));
		अगर (!rx_ring) अणु
			err = -ENOMEM;
			जाओ clear_reset;
		पूर्ण

		क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
			/* clone ring and setup updated count */
			rx_ring[i] = *adapter->rx_ring[i];

			/* Clear copied XDP RX-queue info */
			स_रखो(&rx_ring[i].xdp_rxq, 0,
			       माप(rx_ring[i].xdp_rxq));

			rx_ring[i].count = new_rx_count;
			err = ixgbevf_setup_rx_resources(adapter, &rx_ring[i]);
			अगर (err) अणु
				जबतक (i) अणु
					i--;
					ixgbevf_मुक्त_rx_resources(&rx_ring[i]);
				पूर्ण

				vमुक्त(rx_ring);
				rx_ring = शून्य;

				जाओ clear_reset;
			पूर्ण
		पूर्ण
	पूर्ण

	/* bring पूर्णांकerface करोwn to prepare क्रम update */
	ixgbevf_करोwn(adapter);

	/* Tx */
	अगर (tx_ring) अणु
		क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
			ixgbevf_मुक्त_tx_resources(adapter->tx_ring[i]);
			*adapter->tx_ring[i] = tx_ring[i];
		पूर्ण
		adapter->tx_ring_count = new_tx_count;

		क्रम (j = 0; j < adapter->num_xdp_queues; i++, j++) अणु
			ixgbevf_मुक्त_tx_resources(adapter->xdp_ring[j]);
			*adapter->xdp_ring[j] = tx_ring[i];
		पूर्ण
		adapter->xdp_ring_count = new_tx_count;

		vमुक्त(tx_ring);
		tx_ring = शून्य;
	पूर्ण

	/* Rx */
	अगर (rx_ring) अणु
		क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
			ixgbevf_मुक्त_rx_resources(adapter->rx_ring[i]);
			*adapter->rx_ring[i] = rx_ring[i];
		पूर्ण
		adapter->rx_ring_count = new_rx_count;

		vमुक्त(rx_ring);
		rx_ring = शून्य;
	पूर्ण

	/* restore पूर्णांकerface using new values */
	ixgbevf_up(adapter);

clear_reset:
	/* मुक्त Tx resources अगर Rx error is encountered */
	अगर (tx_ring) अणु
		क्रम (i = 0;
		     i < adapter->num_tx_queues + adapter->num_xdp_queues; i++)
			ixgbevf_मुक्त_tx_resources(&tx_ring[i]);
		vमुक्त(tx_ring);
	पूर्ण

	clear_bit(__IXGBEVF_RESETTING, &adapter->state);
	वापस err;
पूर्ण

अटल पूर्णांक ixgbevf_get_sset_count(काष्ठा net_device *netdev, पूर्णांक stringset)
अणु
	चयन (stringset) अणु
	हाल ETH_SS_TEST:
		वापस IXGBEVF_TEST_LEN;
	हाल ETH_SS_STATS:
		वापस IXGBEVF_STATS_LEN;
	हाल ETH_SS_PRIV_FLAGS:
		वापस IXGBEVF_PRIV_FLAGS_STR_LEN;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम ixgbevf_get_ethtool_stats(काष्ठा net_device *netdev,
				      काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);
	काष्ठा rtnl_link_stats64 temp;
	स्थिर काष्ठा rtnl_link_stats64 *net_stats;
	अचिन्हित पूर्णांक start;
	काष्ठा ixgbevf_ring *ring;
	पूर्णांक i, j;
	अक्षर *p;

	ixgbevf_update_stats(adapter);
	net_stats = dev_get_stats(netdev, &temp);
	क्रम (i = 0; i < IXGBEVF_GLOBAL_STATS_LEN; i++) अणु
		चयन (ixgbevf_gstrings_stats[i].type) अणु
		हाल NETDEV_STATS:
			p = (अक्षर *)net_stats +
					ixgbevf_gstrings_stats[i].stat_offset;
			अवरोध;
		हाल IXGBEVF_STATS:
			p = (अक्षर *)adapter +
					ixgbevf_gstrings_stats[i].stat_offset;
			अवरोध;
		शेष:
			data[i] = 0;
			जारी;
		पूर्ण

		data[i] = (ixgbevf_gstrings_stats[i].माप_stat ==
			   माप(u64)) ? *(u64 *)p : *(u32 *)p;
	पूर्ण

	/* populate Tx queue data */
	क्रम (j = 0; j < adapter->num_tx_queues; j++) अणु
		ring = adapter->tx_ring[j];
		अगर (!ring) अणु
			data[i++] = 0;
			data[i++] = 0;
			जारी;
		पूर्ण

		करो अणु
			start = u64_stats_fetch_begin_irq(&ring->syncp);
			data[i]   = ring->stats.packets;
			data[i + 1] = ring->stats.bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->syncp, start));
		i += 2;
	पूर्ण

	/* populate XDP queue data */
	क्रम (j = 0; j < adapter->num_xdp_queues; j++) अणु
		ring = adapter->xdp_ring[j];
		अगर (!ring) अणु
			data[i++] = 0;
			data[i++] = 0;
			जारी;
		पूर्ण

		करो अणु
			start = u64_stats_fetch_begin_irq(&ring->syncp);
			data[i] = ring->stats.packets;
			data[i + 1] = ring->stats.bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->syncp, start));
		i += 2;
	पूर्ण

	/* populate Rx queue data */
	क्रम (j = 0; j < adapter->num_rx_queues; j++) अणु
		ring = adapter->rx_ring[j];
		अगर (!ring) अणु
			data[i++] = 0;
			data[i++] = 0;
			जारी;
		पूर्ण

		करो अणु
			start = u64_stats_fetch_begin_irq(&ring->syncp);
			data[i]   = ring->stats.packets;
			data[i + 1] = ring->stats.bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->syncp, start));
		i += 2;
	पूर्ण
पूर्ण

अटल व्योम ixgbevf_get_strings(काष्ठा net_device *netdev, u32 stringset,
				u8 *data)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);
	अक्षर *p = (अक्षर *)data;
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_TEST:
		स_नकल(data, *ixgbe_gstrings_test,
		       IXGBEVF_TEST_LEN * ETH_GSTRING_LEN);
		अवरोध;
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < IXGBEVF_GLOBAL_STATS_LEN; i++) अणु
			स_नकल(p, ixgbevf_gstrings_stats[i].stat_string,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण

		क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
			प्र_लिखो(p, "tx_queue_%u_packets", i);
			p += ETH_GSTRING_LEN;
			प्र_लिखो(p, "tx_queue_%u_bytes", i);
			p += ETH_GSTRING_LEN;
		पूर्ण
		क्रम (i = 0; i < adapter->num_xdp_queues; i++) अणु
			प्र_लिखो(p, "xdp_queue_%u_packets", i);
			p += ETH_GSTRING_LEN;
			प्र_लिखो(p, "xdp_queue_%u_bytes", i);
			p += ETH_GSTRING_LEN;
		पूर्ण
		क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
			प्र_लिखो(p, "rx_queue_%u_packets", i);
			p += ETH_GSTRING_LEN;
			प्र_लिखो(p, "rx_queue_%u_bytes", i);
			p += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	हाल ETH_SS_PRIV_FLAGS:
		स_नकल(data, ixgbevf_priv_flags_strings,
		       IXGBEVF_PRIV_FLAGS_STR_LEN * ETH_GSTRING_LEN);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक ixgbevf_link_test(काष्ठा ixgbevf_adapter *adapter, u64 *data)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	bool link_up;
	u32 link_speed = 0;
	*data = 0;

	hw->mac.ops.check_link(hw, &link_speed, &link_up, true);
	अगर (!link_up)
		*data = 1;

	वापस *data;
पूर्ण

/* ethtool रेजिस्टर test data */
काष्ठा ixgbevf_reg_test अणु
	u16 reg;
	u8  array_len;
	u8  test_type;
	u32 mask;
	u32 ग_लिखो;
पूर्ण;

/* In the hardware, रेजिस्टरs are laid out either singly, in arrays
 * spaced 0x40 bytes apart, or in contiguous tables.  We assume
 * most tests take place on arrays or single रेजिस्टरs (handled
 * as a single-element array) and special-हाल the tables.
 * Table tests are always pattern tests.
 *
 * We also make provision क्रम some required setup steps by specअगरying
 * रेजिस्टरs to be written without any पढ़ो-back testing.
 */

#घोषणा PATTERN_TEST	1
#घोषणा SET_READ_TEST	2
#घोषणा WRITE_NO_TEST	3
#घोषणा TABLE32_TEST	4
#घोषणा TABLE64_TEST_LO	5
#घोषणा TABLE64_TEST_HI	6

/* शेष VF रेजिस्टर test */
अटल स्थिर काष्ठा ixgbevf_reg_test reg_test_vf[] = अणु
	अणु IXGBE_VFRDBAL(0), 2, PATTERN_TEST, 0xFFFFFF80, 0xFFFFFF80 पूर्ण,
	अणु IXGBE_VFRDBAH(0), 2, PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु IXGBE_VFRDLEN(0), 2, PATTERN_TEST, 0x000FFF80, 0x000FFFFF पूर्ण,
	अणु IXGBE_VFRXDCTL(0), 2, WRITE_NO_TEST, 0, IXGBE_RXDCTL_ENABLE पूर्ण,
	अणु IXGBE_VFRDT(0), 2, PATTERN_TEST, 0x0000FFFF, 0x0000FFFF पूर्ण,
	अणु IXGBE_VFRXDCTL(0), 2, WRITE_NO_TEST, 0, 0 पूर्ण,
	अणु IXGBE_VFTDBAL(0), 2, PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF पूर्ण,
	अणु IXGBE_VFTDBAH(0), 2, PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु IXGBE_VFTDLEN(0), 2, PATTERN_TEST, 0x000FFF80, 0x000FFF80 पूर्ण,
	अणु .reg = 0 पूर्ण
पूर्ण;

अटल स्थिर u32 रेजिस्टर_test_patterns[] = अणु
	0x5A5A5A5A, 0xA5A5A5A5, 0x00000000, 0xFFFFFFFF
पूर्ण;

अटल bool reg_pattern_test(काष्ठा ixgbevf_adapter *adapter, u64 *data,
			     पूर्णांक reg, u32 mask, u32 ग_लिखो)
अणु
	u32 pat, val, beक्रमe;

	अगर (IXGBE_REMOVED(adapter->hw.hw_addr)) अणु
		*data = 1;
		वापस true;
	पूर्ण
	क्रम (pat = 0; pat < ARRAY_SIZE(रेजिस्टर_test_patterns); pat++) अणु
		beक्रमe = ixgbevf_पढ़ो_reg(&adapter->hw, reg);
		ixgbe_ग_लिखो_reg(&adapter->hw, reg,
				रेजिस्टर_test_patterns[pat] & ग_लिखो);
		val = ixgbevf_पढ़ो_reg(&adapter->hw, reg);
		अगर (val != (रेजिस्टर_test_patterns[pat] & ग_लिखो & mask)) अणु
			hw_dbg(&adapter->hw,
			       "pattern test reg %04X failed: got 0x%08X expected 0x%08X\n",
			       reg, val,
			       रेजिस्टर_test_patterns[pat] & ग_लिखो & mask);
			*data = reg;
			ixgbe_ग_लिखो_reg(&adapter->hw, reg, beक्रमe);
			वापस true;
		पूर्ण
		ixgbe_ग_लिखो_reg(&adapter->hw, reg, beक्रमe);
	पूर्ण
	वापस false;
पूर्ण

अटल bool reg_set_and_check(काष्ठा ixgbevf_adapter *adapter, u64 *data,
			      पूर्णांक reg, u32 mask, u32 ग_लिखो)
अणु
	u32 val, beक्रमe;

	अगर (IXGBE_REMOVED(adapter->hw.hw_addr)) अणु
		*data = 1;
		वापस true;
	पूर्ण
	beक्रमe = ixgbevf_पढ़ो_reg(&adapter->hw, reg);
	ixgbe_ग_लिखो_reg(&adapter->hw, reg, ग_लिखो & mask);
	val = ixgbevf_पढ़ो_reg(&adapter->hw, reg);
	अगर ((ग_लिखो & mask) != (val & mask)) अणु
		pr_err("set/check reg %04X test failed: got 0x%08X expected 0x%08X\n",
		       reg, (val & mask), ग_लिखो & mask);
		*data = reg;
		ixgbe_ग_लिखो_reg(&adapter->hw, reg, beक्रमe);
		वापस true;
	पूर्ण
	ixgbe_ग_लिखो_reg(&adapter->hw, reg, beक्रमe);
	वापस false;
पूर्ण

अटल पूर्णांक ixgbevf_reg_test(काष्ठा ixgbevf_adapter *adapter, u64 *data)
अणु
	स्थिर काष्ठा ixgbevf_reg_test *test;
	u32 i;

	अगर (IXGBE_REMOVED(adapter->hw.hw_addr)) अणु
		dev_err(&adapter->pdev->dev,
			"Adapter removed - register test blocked\n");
		*data = 1;
		वापस 1;
	पूर्ण
	test = reg_test_vf;

	/* Perक्रमm the रेजिस्टर test, looping through the test table
	 * until we either fail or reach the null entry.
	 */
	जबतक (test->reg) अणु
		क्रम (i = 0; i < test->array_len; i++) अणु
			bool b = false;

			चयन (test->test_type) अणु
			हाल PATTERN_TEST:
				b = reg_pattern_test(adapter, data,
						     test->reg + (i * 0x40),
						     test->mask,
						     test->ग_लिखो);
				अवरोध;
			हाल SET_READ_TEST:
				b = reg_set_and_check(adapter, data,
						      test->reg + (i * 0x40),
						      test->mask,
						      test->ग_लिखो);
				अवरोध;
			हाल WRITE_NO_TEST:
				ixgbe_ग_लिखो_reg(&adapter->hw,
						test->reg + (i * 0x40),
						test->ग_लिखो);
				अवरोध;
			हाल TABLE32_TEST:
				b = reg_pattern_test(adapter, data,
						     test->reg + (i * 4),
						     test->mask,
						     test->ग_लिखो);
				अवरोध;
			हाल TABLE64_TEST_LO:
				b = reg_pattern_test(adapter, data,
						     test->reg + (i * 8),
						     test->mask,
						     test->ग_लिखो);
				अवरोध;
			हाल TABLE64_TEST_HI:
				b = reg_pattern_test(adapter, data,
						     test->reg + 4 + (i * 8),
						     test->mask,
						     test->ग_लिखो);
				अवरोध;
			पूर्ण
			अगर (b)
				वापस 1;
		पूर्ण
		test++;
	पूर्ण

	*data = 0;
	वापस *data;
पूर्ण

अटल व्योम ixgbevf_diag_test(काष्ठा net_device *netdev,
			      काष्ठा ethtool_test *eth_test, u64 *data)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);
	bool अगर_running = netअगर_running(netdev);

	अगर (IXGBE_REMOVED(adapter->hw.hw_addr)) अणु
		dev_err(&adapter->pdev->dev,
			"Adapter removed - test blocked\n");
		data[0] = 1;
		data[1] = 1;
		eth_test->flags |= ETH_TEST_FL_FAILED;
		वापस;
	पूर्ण
	set_bit(__IXGBEVF_TESTING, &adapter->state);
	अगर (eth_test->flags == ETH_TEST_FL_OFFLINE) अणु
		/* Offline tests */

		hw_dbg(&adapter->hw, "offline testing starting\n");

		/* Link test perक्रमmed beक्रमe hardware reset so स्वतःneg करोesn't
		 * पूर्णांकerfere with test result
		 */
		अगर (ixgbevf_link_test(adapter, &data[1]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		अगर (अगर_running)
			/* indicate we're in test mode */
			ixgbevf_बंद(netdev);
		अन्यथा
			ixgbevf_reset(adapter);

		hw_dbg(&adapter->hw, "register testing starting\n");
		अगर (ixgbevf_reg_test(adapter, &data[0]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		ixgbevf_reset(adapter);

		clear_bit(__IXGBEVF_TESTING, &adapter->state);
		अगर (अगर_running)
			ixgbevf_खोलो(netdev);
	पूर्ण अन्यथा अणु
		hw_dbg(&adapter->hw, "online testing starting\n");
		/* Online tests */
		अगर (ixgbevf_link_test(adapter, &data[1]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		/* Online tests aren't run; pass by शेष */
		data[0] = 0;

		clear_bit(__IXGBEVF_TESTING, &adapter->state);
	पूर्ण
	msleep_पूर्णांकerruptible(4 * 1000);
पूर्ण

अटल पूर्णांक ixgbevf_nway_reset(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);

	अगर (netअगर_running(netdev))
		ixgbevf_reinit_locked(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbevf_get_coalesce(काष्ठा net_device *netdev,
				काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);

	/* only valid अगर in स्थिरant ITR mode */
	अगर (adapter->rx_itr_setting <= 1)
		ec->rx_coalesce_usecs = adapter->rx_itr_setting;
	अन्यथा
		ec->rx_coalesce_usecs = adapter->rx_itr_setting >> 2;

	/* अगर in mixed Tx/Rx queues per vector mode, report only Rx settings */
	अगर (adapter->q_vector[0]->tx.count && adapter->q_vector[0]->rx.count)
		वापस 0;

	/* only valid अगर in स्थिरant ITR mode */
	अगर (adapter->tx_itr_setting <= 1)
		ec->tx_coalesce_usecs = adapter->tx_itr_setting;
	अन्यथा
		ec->tx_coalesce_usecs = adapter->tx_itr_setting >> 2;

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbevf_set_coalesce(काष्ठा net_device *netdev,
				काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbevf_q_vector *q_vector;
	पूर्णांक num_vectors, i;
	u16 tx_itr_param, rx_itr_param;

	/* करोn't accept Tx specific changes if we've got mixed RxTx vectors */
	अगर (adapter->q_vector[0]->tx.count &&
	    adapter->q_vector[0]->rx.count && ec->tx_coalesce_usecs)
		वापस -EINVAL;

	अगर ((ec->rx_coalesce_usecs > (IXGBE_MAX_EITR >> 2)) ||
	    (ec->tx_coalesce_usecs > (IXGBE_MAX_EITR >> 2)))
		वापस -EINVAL;

	अगर (ec->rx_coalesce_usecs > 1)
		adapter->rx_itr_setting = ec->rx_coalesce_usecs << 2;
	अन्यथा
		adapter->rx_itr_setting = ec->rx_coalesce_usecs;

	अगर (adapter->rx_itr_setting == 1)
		rx_itr_param = IXGBE_20K_ITR;
	अन्यथा
		rx_itr_param = adapter->rx_itr_setting;

	अगर (ec->tx_coalesce_usecs > 1)
		adapter->tx_itr_setting = ec->tx_coalesce_usecs << 2;
	अन्यथा
		adapter->tx_itr_setting = ec->tx_coalesce_usecs;

	अगर (adapter->tx_itr_setting == 1)
		tx_itr_param = IXGBE_12K_ITR;
	अन्यथा
		tx_itr_param = adapter->tx_itr_setting;

	num_vectors = adapter->num_msix_vectors - NON_Q_VECTORS;

	क्रम (i = 0; i < num_vectors; i++) अणु
		q_vector = adapter->q_vector[i];
		अगर (q_vector->tx.count && !q_vector->rx.count)
			/* Tx only */
			q_vector->itr = tx_itr_param;
		अन्यथा
			/* Rx only or mixed */
			q_vector->itr = rx_itr_param;
		ixgbevf_ग_लिखो_eitr(q_vector);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbevf_get_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *info,
			     u32 *rules __always_unused)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(dev);

	चयन (info->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		info->data = adapter->num_rx_queues;
		वापस 0;
	शेष:
		hw_dbg(&adapter->hw, "Command parameters not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल u32 ixgbevf_get_rxfh_indir_size(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);

	अगर (adapter->hw.mac.type >= ixgbe_mac_X550_vf)
		वापस IXGBEVF_X550_VFRETA_SIZE;

	वापस IXGBEVF_82599_RETA_SIZE;
पूर्ण

अटल u32 ixgbevf_get_rxfh_key_size(काष्ठा net_device *netdev)
अणु
	वापस IXGBEVF_RSS_HASH_KEY_SIZE;
पूर्ण

अटल पूर्णांक ixgbevf_get_rxfh(काष्ठा net_device *netdev, u32 *indir, u8 *key,
			    u8 *hfunc)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);
	पूर्णांक err = 0;

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	अगर (adapter->hw.mac.type >= ixgbe_mac_X550_vf) अणु
		अगर (key)
			स_नकल(key, adapter->rss_key,
			       ixgbevf_get_rxfh_key_size(netdev));

		अगर (indir) अणु
			पूर्णांक i;

			क्रम (i = 0; i < IXGBEVF_X550_VFRETA_SIZE; i++)
				indir[i] = adapter->rss_indir_tbl[i];
		पूर्ण
	पूर्ण अन्यथा अणु
		/* If neither indirection table nor hash key was requested
		 *  - just वापस a success aव्योमing taking any locks.
		 */
		अगर (!indir && !key)
			वापस 0;

		spin_lock_bh(&adapter->mbx_lock);
		अगर (indir)
			err = ixgbevf_get_reta_locked(&adapter->hw, indir,
						      adapter->num_rx_queues);

		अगर (!err && key)
			err = ixgbevf_get_rss_key_locked(&adapter->hw, key);

		spin_unlock_bh(&adapter->mbx_lock);
	पूर्ण

	वापस err;
पूर्ण

अटल u32 ixgbevf_get_priv_flags(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);
	u32 priv_flags = 0;

	अगर (adapter->flags & IXGBEVF_FLAGS_LEGACY_RX)
		priv_flags |= IXGBEVF_PRIV_FLAGS_LEGACY_RX;

	वापस priv_flags;
पूर्ण

अटल पूर्णांक ixgbevf_set_priv_flags(काष्ठा net_device *netdev, u32 priv_flags)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);
	अचिन्हित पूर्णांक flags = adapter->flags;

	flags &= ~IXGBEVF_FLAGS_LEGACY_RX;
	अगर (priv_flags & IXGBEVF_PRIV_FLAGS_LEGACY_RX)
		flags |= IXGBEVF_FLAGS_LEGACY_RX;

	अगर (flags != adapter->flags) अणु
		adapter->flags = flags;

		/* reset पूर्णांकerface to repopulate queues */
		अगर (netअगर_running(netdev))
			ixgbevf_reinit_locked(adapter);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ixgbevf_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS,
	.get_drvinfo		= ixgbevf_get_drvinfo,
	.get_regs_len		= ixgbevf_get_regs_len,
	.get_regs		= ixgbevf_get_regs,
	.nway_reset		= ixgbevf_nway_reset,
	.get_link		= ethtool_op_get_link,
	.get_ringparam		= ixgbevf_get_ringparam,
	.set_ringparam		= ixgbevf_set_ringparam,
	.get_msglevel		= ixgbevf_get_msglevel,
	.set_msglevel		= ixgbevf_set_msglevel,
	.self_test		= ixgbevf_diag_test,
	.get_sset_count		= ixgbevf_get_sset_count,
	.get_strings		= ixgbevf_get_strings,
	.get_ethtool_stats	= ixgbevf_get_ethtool_stats,
	.get_coalesce		= ixgbevf_get_coalesce,
	.set_coalesce		= ixgbevf_set_coalesce,
	.get_rxnfc		= ixgbevf_get_rxnfc,
	.get_rxfh_indir_size	= ixgbevf_get_rxfh_indir_size,
	.get_rxfh_key_size	= ixgbevf_get_rxfh_key_size,
	.get_rxfh		= ixgbevf_get_rxfh,
	.get_link_ksettings	= ixgbevf_get_link_ksettings,
	.get_priv_flags		= ixgbevf_get_priv_flags,
	.set_priv_flags		= ixgbevf_set_priv_flags,
पूर्ण;

व्योम ixgbevf_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &ixgbevf_ethtool_ops;
पूर्ण
