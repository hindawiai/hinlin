<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009 - 2018 Intel Corporation. */

/* ethtool support क्रम igbvf */

#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delay.h>

#समावेश "igbvf.h"
#समावेश <linux/अगर_vlan.h>

काष्ठा igbvf_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक माप_stat;
	पूर्णांक stat_offset;
	पूर्णांक base_stat_offset;
पूर्ण;

#घोषणा IGBVF_STAT(current, base) \
		माप(((काष्ठा igbvf_adapter *)0)->current), \
		दुरत्व(काष्ठा igbvf_adapter, current), \
		दुरत्व(काष्ठा igbvf_adapter, base)

अटल स्थिर काष्ठा igbvf_stats igbvf_gstrings_stats[] = अणु
	अणु "rx_packets", IGBVF_STAT(stats.gprc, stats.base_gprc) पूर्ण,
	अणु "tx_packets", IGBVF_STAT(stats.gptc, stats.base_gptc) पूर्ण,
	अणु "rx_bytes", IGBVF_STAT(stats.gorc, stats.base_gorc) पूर्ण,
	अणु "tx_bytes", IGBVF_STAT(stats.gotc, stats.base_gotc) पूर्ण,
	अणु "multicast", IGBVF_STAT(stats.mprc, stats.base_mprc) पूर्ण,
	अणु "lbrx_bytes", IGBVF_STAT(stats.gorlbc, stats.base_gorlbc) पूर्ण,
	अणु "lbrx_packets", IGBVF_STAT(stats.gprlbc, stats.base_gprlbc) पूर्ण,
	अणु "tx_restart_queue", IGBVF_STAT(restart_queue, zero_base) पूर्ण,
	अणु "rx_long_byte_count", IGBVF_STAT(stats.gorc, stats.base_gorc) पूर्ण,
	अणु "rx_csum_offload_good", IGBVF_STAT(hw_csum_good, zero_base) पूर्ण,
	अणु "rx_csum_offload_errors", IGBVF_STAT(hw_csum_err, zero_base) पूर्ण,
	अणु "rx_header_split", IGBVF_STAT(rx_hdr_split, zero_base) पूर्ण,
	अणु "alloc_rx_buff_failed", IGBVF_STAT(alloc_rx_buff_failed, zero_base) पूर्ण,
पूर्ण;

#घोषणा IGBVF_GLOBAL_STATS_LEN ARRAY_SIZE(igbvf_gstrings_stats)

अटल स्थिर अक्षर igbvf_gstrings_test[][ETH_GSTRING_LEN] = अणु
	"Link test   (on/offline)"
पूर्ण;

#घोषणा IGBVF_TEST_LEN ARRAY_SIZE(igbvf_gstrings_test)

अटल पूर्णांक igbvf_get_link_ksettings(काष्ठा net_device *netdev,
				    काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 status;

	ethtool_link_ksettings_zero_link_mode(cmd, supported);
	ethtool_link_ksettings_add_link_mode(cmd, supported, 1000baseT_Full);
	ethtool_link_ksettings_zero_link_mode(cmd, advertising);
	ethtool_link_ksettings_add_link_mode(cmd, advertising, 1000baseT_Full);

	cmd->base.port = -1;

	status = er32(STATUS);
	अगर (status & E1000_STATUS_LU) अणु
		अगर (status & E1000_STATUS_SPEED_1000)
			cmd->base.speed = SPEED_1000;
		अन्यथा अगर (status & E1000_STATUS_SPEED_100)
			cmd->base.speed = SPEED_100;
		अन्यथा
			cmd->base.speed = SPEED_10;

		अगर (status & E1000_STATUS_FD)
			cmd->base.duplex = DUPLEX_FULL;
		अन्यथा
			cmd->base.duplex = DUPLEX_HALF;
	पूर्ण अन्यथा अणु
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण

	cmd->base.स्वतःneg = AUTONEG_DISABLE;

	वापस 0;
पूर्ण

अटल पूर्णांक igbvf_set_link_ksettings(काष्ठा net_device *netdev,
				    स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम igbvf_get_छोड़ोparam(काष्ठा net_device *netdev,
				 काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
पूर्ण

अटल पूर्णांक igbvf_set_छोड़ोparam(काष्ठा net_device *netdev,
				काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल u32 igbvf_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);

	वापस adapter->msg_enable;
पूर्ण

अटल व्योम igbvf_set_msglevel(काष्ठा net_device *netdev, u32 data)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);

	adapter->msg_enable = data;
पूर्ण

अटल पूर्णांक igbvf_get_regs_len(काष्ठा net_device *netdev)
अणु
#घोषणा IGBVF_REGS_LEN 8
	वापस IGBVF_REGS_LEN * माप(u32);
पूर्ण

अटल व्योम igbvf_get_regs(काष्ठा net_device *netdev,
			   काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 *regs_buff = p;

	स_रखो(p, 0, IGBVF_REGS_LEN * माप(u32));

	regs->version = (1u << 24) |
			(adapter->pdev->revision << 16) |
			adapter->pdev->device;

	regs_buff[0] = er32(CTRL);
	regs_buff[1] = er32(STATUS);

	regs_buff[2] = er32(RDLEN(0));
	regs_buff[3] = er32(RDH(0));
	regs_buff[4] = er32(RDT(0));

	regs_buff[5] = er32(TDLEN(0));
	regs_buff[6] = er32(TDH(0));
	regs_buff[7] = er32(TDT(0));
पूर्ण

अटल पूर्णांक igbvf_get_eeprom_len(काष्ठा net_device *netdev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक igbvf_get_eeprom(काष्ठा net_device *netdev,
			    काष्ठा ethtool_eeprom *eeprom, u8 *bytes)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक igbvf_set_eeprom(काष्ठा net_device *netdev,
			    काष्ठा ethtool_eeprom *eeprom, u8 *bytes)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम igbvf_get_drvinfo(काष्ठा net_device *netdev,
			      काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);

	strlcpy(drvinfo->driver,  igbvf_driver_name, माप(drvinfo->driver));
	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		माप(drvinfo->bus_info));
पूर्ण

अटल व्योम igbvf_get_ringparam(काष्ठा net_device *netdev,
				काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);
	काष्ठा igbvf_ring *tx_ring = adapter->tx_ring;
	काष्ठा igbvf_ring *rx_ring = adapter->rx_ring;

	ring->rx_max_pending = IGBVF_MAX_RXD;
	ring->tx_max_pending = IGBVF_MAX_TXD;
	ring->rx_pending = rx_ring->count;
	ring->tx_pending = tx_ring->count;
पूर्ण

अटल पूर्णांक igbvf_set_ringparam(काष्ठा net_device *netdev,
			       काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);
	काष्ठा igbvf_ring *temp_ring;
	पूर्णांक err = 0;
	u32 new_rx_count, new_tx_count;

	अगर ((ring->rx_mini_pending) || (ring->rx_jumbo_pending))
		वापस -EINVAL;

	new_rx_count = max_t(u32, ring->rx_pending, IGBVF_MIN_RXD);
	new_rx_count = min_t(u32, new_rx_count, IGBVF_MAX_RXD);
	new_rx_count = ALIGN(new_rx_count, REQ_RX_DESCRIPTOR_MULTIPLE);

	new_tx_count = max_t(u32, ring->tx_pending, IGBVF_MIN_TXD);
	new_tx_count = min_t(u32, new_tx_count, IGBVF_MAX_TXD);
	new_tx_count = ALIGN(new_tx_count, REQ_TX_DESCRIPTOR_MULTIPLE);

	अगर ((new_tx_count == adapter->tx_ring->count) &&
	    (new_rx_count == adapter->rx_ring->count)) अणु
		/* nothing to करो */
		वापस 0;
	पूर्ण

	जबतक (test_and_set_bit(__IGBVF_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	अगर (!netअगर_running(adapter->netdev)) अणु
		adapter->tx_ring->count = new_tx_count;
		adapter->rx_ring->count = new_rx_count;
		जाओ clear_reset;
	पूर्ण

	temp_ring = vदो_स्मृति(माप(काष्ठा igbvf_ring));
	अगर (!temp_ring) अणु
		err = -ENOMEM;
		जाओ clear_reset;
	पूर्ण

	igbvf_करोwn(adapter);

	/* We can't just मुक्त everything and then setup again,
	 * because the ISRs in MSI-X mode get passed poपूर्णांकers
	 * to the Tx and Rx ring काष्ठाs.
	 */
	अगर (new_tx_count != adapter->tx_ring->count) अणु
		स_नकल(temp_ring, adapter->tx_ring, माप(काष्ठा igbvf_ring));

		temp_ring->count = new_tx_count;
		err = igbvf_setup_tx_resources(adapter, temp_ring);
		अगर (err)
			जाओ err_setup;

		igbvf_मुक्त_tx_resources(adapter->tx_ring);

		स_नकल(adapter->tx_ring, temp_ring, माप(काष्ठा igbvf_ring));
	पूर्ण

	अगर (new_rx_count != adapter->rx_ring->count) अणु
		स_नकल(temp_ring, adapter->rx_ring, माप(काष्ठा igbvf_ring));

		temp_ring->count = new_rx_count;
		err = igbvf_setup_rx_resources(adapter, temp_ring);
		अगर (err)
			जाओ err_setup;

		igbvf_मुक्त_rx_resources(adapter->rx_ring);

		स_नकल(adapter->rx_ring, temp_ring, माप(काष्ठा igbvf_ring));
	पूर्ण
err_setup:
	igbvf_up(adapter);
	vमुक्त(temp_ring);
clear_reset:
	clear_bit(__IGBVF_RESETTING, &adapter->state);
	वापस err;
पूर्ण

अटल पूर्णांक igbvf_link_test(काष्ठा igbvf_adapter *adapter, u64 *data)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	*data = 0;

	spin_lock_bh(&hw->mbx_lock);

	hw->mac.ops.check_क्रम_link(hw);

	spin_unlock_bh(&hw->mbx_lock);

	अगर (!(er32(STATUS) & E1000_STATUS_LU))
		*data = 1;

	वापस *data;
पूर्ण

अटल व्योम igbvf_diag_test(काष्ठा net_device *netdev,
			    काष्ठा ethtool_test *eth_test, u64 *data)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);

	set_bit(__IGBVF_TESTING, &adapter->state);

	/* Link test perक्रमmed beक्रमe hardware reset so स्वतःneg करोesn't
	 * पूर्णांकerfere with test result
	 */
	अगर (igbvf_link_test(adapter, &data[0]))
		eth_test->flags |= ETH_TEST_FL_FAILED;

	clear_bit(__IGBVF_TESTING, &adapter->state);
	msleep_पूर्णांकerruptible(4 * 1000);
पूर्ण

अटल व्योम igbvf_get_wol(काष्ठा net_device *netdev,
			  काष्ठा ethtool_wolinfo *wol)
अणु
	wol->supported = 0;
	wol->wolopts = 0;
पूर्ण

अटल पूर्णांक igbvf_set_wol(काष्ठा net_device *netdev,
			 काष्ठा ethtool_wolinfo *wol)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक igbvf_get_coalesce(काष्ठा net_device *netdev,
			      काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);

	अगर (adapter->requested_itr <= 3)
		ec->rx_coalesce_usecs = adapter->requested_itr;
	अन्यथा
		ec->rx_coalesce_usecs = adapter->current_itr >> 2;

	वापस 0;
पूर्ण

अटल पूर्णांक igbvf_set_coalesce(काष्ठा net_device *netdev,
			      काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;

	अगर ((ec->rx_coalesce_usecs >= IGBVF_MIN_ITR_USECS) &&
	    (ec->rx_coalesce_usecs <= IGBVF_MAX_ITR_USECS)) अणु
		adapter->current_itr = ec->rx_coalesce_usecs << 2;
		adapter->requested_itr = 1000000000 /
					(adapter->current_itr * 256);
	पूर्ण अन्यथा अगर ((ec->rx_coalesce_usecs == 3) ||
		   (ec->rx_coalesce_usecs == 2)) अणु
		adapter->current_itr = IGBVF_START_ITR;
		adapter->requested_itr = ec->rx_coalesce_usecs;
	पूर्ण अन्यथा अगर (ec->rx_coalesce_usecs == 0) अणु
		/* The user's desire is to turn off पूर्णांकerrupt throttling
		 * altogether, but due to HW limitations, we can't करो that.
		 * Instead we set a very small value in EITR, which would
		 * allow ~967k पूर्णांकerrupts per second, but allow the adapter's
		 * पूर्णांकernal घड़ीing to still function properly.
		 */
		adapter->current_itr = 4;
		adapter->requested_itr = 1000000000 /
					(adapter->current_itr * 256);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(adapter->current_itr,
	       hw->hw_addr + adapter->rx_ring->itr_रेजिस्टर);

	वापस 0;
पूर्ण

अटल पूर्णांक igbvf_nway_reset(काष्ठा net_device *netdev)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);

	अगर (netअगर_running(netdev))
		igbvf_reinit_locked(adapter);
	वापस 0;
पूर्ण

अटल व्योम igbvf_get_ethtool_stats(काष्ठा net_device *netdev,
				    काष्ठा ethtool_stats *stats,
				    u64 *data)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);
	पूर्णांक i;

	igbvf_update_stats(adapter);
	क्रम (i = 0; i < IGBVF_GLOBAL_STATS_LEN; i++) अणु
		अक्षर *p = (अक्षर *)adapter +
			  igbvf_gstrings_stats[i].stat_offset;
		अक्षर *b = (अक्षर *)adapter +
			  igbvf_gstrings_stats[i].base_stat_offset;
		data[i] = ((igbvf_gstrings_stats[i].माप_stat ==
			    माप(u64)) ? (*(u64 *)p - *(u64 *)b) :
			    (*(u32 *)p - *(u32 *)b));
	पूर्ण
पूर्ण

अटल पूर्णांक igbvf_get_sset_count(काष्ठा net_device *dev, पूर्णांक stringset)
अणु
	चयन (stringset) अणु
	हाल ETH_SS_TEST:
		वापस IGBVF_TEST_LEN;
	हाल ETH_SS_STATS:
		वापस IGBVF_GLOBAL_STATS_LEN;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम igbvf_get_strings(काष्ठा net_device *netdev, u32 stringset,
			      u8 *data)
अणु
	u8 *p = data;
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_TEST:
		स_नकल(data, *igbvf_gstrings_test, माप(igbvf_gstrings_test));
		अवरोध;
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < IGBVF_GLOBAL_STATS_LEN; i++) अणु
			स_नकल(p, igbvf_gstrings_stats[i].stat_string,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ethtool_ops igbvf_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_RX_USECS,
	.get_drvinfo		= igbvf_get_drvinfo,
	.get_regs_len		= igbvf_get_regs_len,
	.get_regs		= igbvf_get_regs,
	.get_wol		= igbvf_get_wol,
	.set_wol		= igbvf_set_wol,
	.get_msglevel		= igbvf_get_msglevel,
	.set_msglevel		= igbvf_set_msglevel,
	.nway_reset		= igbvf_nway_reset,
	.get_link		= ethtool_op_get_link,
	.get_eeprom_len		= igbvf_get_eeprom_len,
	.get_eeprom		= igbvf_get_eeprom,
	.set_eeprom		= igbvf_set_eeprom,
	.get_ringparam		= igbvf_get_ringparam,
	.set_ringparam		= igbvf_set_ringparam,
	.get_छोड़ोparam		= igbvf_get_छोड़ोparam,
	.set_छोड़ोparam		= igbvf_set_छोड़ोparam,
	.self_test		= igbvf_diag_test,
	.get_sset_count		= igbvf_get_sset_count,
	.get_strings		= igbvf_get_strings,
	.get_ethtool_stats	= igbvf_get_ethtool_stats,
	.get_coalesce		= igbvf_get_coalesce,
	.set_coalesce		= igbvf_set_coalesce,
	.get_link_ksettings	= igbvf_get_link_ksettings,
	.set_link_ksettings	= igbvf_set_link_ksettings,
पूर्ण;

व्योम igbvf_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &igbvf_ethtool_ops;
पूर्ण
