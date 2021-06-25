<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2019 Intel Corporation. */

#समावेश <linux/ethtool.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "fm10k.h"

काष्ठा fm10k_stats अणु
	/* The stat_string is expected to be a क्रमmat string क्रमmatted using
	 * vsnम_लिखो by fm10k_add_stat_strings. Every member of a stats array
	 * should use the same क्रमmat specअगरiers as they will be क्रमmatted
	 * using the same variadic arguments.
	 */
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक माप_stat;
	पूर्णांक stat_offset;
पूर्ण;

#घोषणा FM10K_STAT_FIELDS(_type, _name, _stat) अणु \
	.stat_string = _name, \
	.माप_stat = माप_field(_type, _stat), \
	.stat_offset = दुरत्व(_type, _stat) \
पूर्ण

/* netdevice statistics */
#घोषणा FM10K_NETDEV_STAT(_net_stat) \
	FM10K_STAT_FIELDS(काष्ठा net_device_stats, __stringअगरy(_net_stat), \
			  _net_stat)

अटल स्थिर काष्ठा fm10k_stats fm10k_gstrings_net_stats[] = अणु
	FM10K_NETDEV_STAT(tx_packets),
	FM10K_NETDEV_STAT(tx_bytes),
	FM10K_NETDEV_STAT(tx_errors),
	FM10K_NETDEV_STAT(rx_packets),
	FM10K_NETDEV_STAT(rx_bytes),
	FM10K_NETDEV_STAT(rx_errors),
	FM10K_NETDEV_STAT(rx_dropped),

	/* detailed Rx errors */
	FM10K_NETDEV_STAT(rx_length_errors),
	FM10K_NETDEV_STAT(rx_crc_errors),
	FM10K_NETDEV_STAT(rx_fअगरo_errors),
पूर्ण;

#घोषणा FM10K_NETDEV_STATS_LEN	ARRAY_SIZE(fm10k_gstrings_net_stats)

/* General पूर्णांकerface statistics */
#घोषणा FM10K_STAT(_name, _stat) \
	FM10K_STAT_FIELDS(काष्ठा fm10k_पूर्णांकfc, _name, _stat)

अटल स्थिर काष्ठा fm10k_stats fm10k_gstrings_global_stats[] = अणु
	FM10K_STAT("tx_restart_queue", restart_queue),
	FM10K_STAT("tx_busy", tx_busy),
	FM10K_STAT("tx_csum_errors", tx_csum_errors),
	FM10K_STAT("rx_alloc_failed", alloc_failed),
	FM10K_STAT("rx_csum_errors", rx_csum_errors),

	FM10K_STAT("tx_packets_nic", tx_packets_nic),
	FM10K_STAT("tx_bytes_nic", tx_bytes_nic),
	FM10K_STAT("rx_packets_nic", rx_packets_nic),
	FM10K_STAT("rx_bytes_nic", rx_bytes_nic),
	FM10K_STAT("rx_drops_nic", rx_drops_nic),
	FM10K_STAT("rx_overrun_pf", rx_overrun_pf),
	FM10K_STAT("rx_overrun_vf", rx_overrun_vf),

	FM10K_STAT("swapi_status", hw.swapi.status),
	FM10K_STAT("mac_rules_used", hw.swapi.mac.used),
	FM10K_STAT("mac_rules_avail", hw.swapi.mac.avail),

	FM10K_STAT("reset_while_pending", hw.mac.reset_जबतक_pending),

	FM10K_STAT("tx_hang_count", tx_समयout_count),
पूर्ण;

अटल स्थिर काष्ठा fm10k_stats fm10k_gstrings_pf_stats[] = अणु
	FM10K_STAT("timeout", stats.समयout.count),
	FM10K_STAT("ur", stats.ur.count),
	FM10K_STAT("ca", stats.ca.count),
	FM10K_STAT("um", stats.um.count),
	FM10K_STAT("xec", stats.xec.count),
	FM10K_STAT("vlan_drop", stats.vlan_drop.count),
	FM10K_STAT("loopback_drop", stats.loopback_drop.count),
	FM10K_STAT("nodesc_drop", stats.nodesc_drop.count),
पूर्ण;

/* mailbox statistics */
#घोषणा FM10K_MBX_STAT(_name, _stat) \
	FM10K_STAT_FIELDS(काष्ठा fm10k_mbx_info, _name, _stat)

अटल स्थिर काष्ठा fm10k_stats fm10k_gstrings_mbx_stats[] = अणु
	FM10K_MBX_STAT("mbx_tx_busy", tx_busy),
	FM10K_MBX_STAT("mbx_tx_dropped", tx_dropped),
	FM10K_MBX_STAT("mbx_tx_messages", tx_messages),
	FM10K_MBX_STAT("mbx_tx_dwords", tx_dwords),
	FM10K_MBX_STAT("mbx_tx_mbmem_pulled", tx_mbmem_pulled),
	FM10K_MBX_STAT("mbx_rx_messages", rx_messages),
	FM10K_MBX_STAT("mbx_rx_dwords", rx_dwords),
	FM10K_MBX_STAT("mbx_rx_parse_err", rx_parse_err),
	FM10K_MBX_STAT("mbx_rx_mbmem_pushed", rx_mbmem_pushed),
पूर्ण;

/* per-queue ring statistics */
#घोषणा FM10K_QUEUE_STAT(_name, _stat) \
	FM10K_STAT_FIELDS(काष्ठा fm10k_ring, _name, _stat)

अटल स्थिर काष्ठा fm10k_stats fm10k_gstrings_queue_stats[] = अणु
	FM10K_QUEUE_STAT("%s_queue_%u_packets", stats.packets),
	FM10K_QUEUE_STAT("%s_queue_%u_bytes", stats.bytes),
पूर्ण;

#घोषणा FM10K_GLOBAL_STATS_LEN ARRAY_SIZE(fm10k_gstrings_global_stats)
#घोषणा FM10K_PF_STATS_LEN ARRAY_SIZE(fm10k_gstrings_pf_stats)
#घोषणा FM10K_MBX_STATS_LEN ARRAY_SIZE(fm10k_gstrings_mbx_stats)
#घोषणा FM10K_QUEUE_STATS_LEN ARRAY_SIZE(fm10k_gstrings_queue_stats)

#घोषणा FM10K_STATIC_STATS_LEN (FM10K_GLOBAL_STATS_LEN + \
				FM10K_NETDEV_STATS_LEN + \
				FM10K_MBX_STATS_LEN)

अटल स्थिर अक्षर fm10k_gstrings_test[][ETH_GSTRING_LEN] = अणु
	"Mailbox test (on/offline)"
पूर्ण;

#घोषणा FM10K_TEST_LEN (माप(fm10k_gstrings_test) / ETH_GSTRING_LEN)

क्रमागत fm10k_self_test_types अणु
	FM10K_TEST_MBX,
	FM10K_TEST_MAX = FM10K_TEST_LEN
पूर्ण;

क्रमागत अणु
	FM10K_PRV_FLAG_LEN,
पूर्ण;

अटल स्थिर अक्षर fm10k_prv_flags[FM10K_PRV_FLAG_LEN][ETH_GSTRING_LEN] = अणु
पूर्ण;

अटल व्योम __fm10k_add_stat_strings(u8 **p, स्थिर काष्ठा fm10k_stats stats[],
				     स्थिर अचिन्हित पूर्णांक size, ...)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		बहु_सूची args;

		बहु_शुरू(args, size);
		vsnम_लिखो(*p, ETH_GSTRING_LEN, stats[i].stat_string, args);
		*p += ETH_GSTRING_LEN;
		बहु_पूर्ण(args);
	पूर्ण
पूर्ण

#घोषणा fm10k_add_stat_strings(p, stats, ...) \
	__fm10k_add_stat_strings(p, stats, ARRAY_SIZE(stats), ## __VA_ARGS__)

अटल व्योम fm10k_get_stat_strings(काष्ठा net_device *dev, u8 *data)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);
	अचिन्हित पूर्णांक i;

	fm10k_add_stat_strings(&data, fm10k_gstrings_net_stats);

	fm10k_add_stat_strings(&data, fm10k_gstrings_global_stats);

	fm10k_add_stat_strings(&data, fm10k_gstrings_mbx_stats);

	अगर (पूर्णांकerface->hw.mac.type != fm10k_mac_vf)
		fm10k_add_stat_strings(&data, fm10k_gstrings_pf_stats);

	क्रम (i = 0; i < पूर्णांकerface->hw.mac.max_queues; i++) अणु
		fm10k_add_stat_strings(&data, fm10k_gstrings_queue_stats,
				       "tx", i);

		fm10k_add_stat_strings(&data, fm10k_gstrings_queue_stats,
				       "rx", i);
	पूर्ण
पूर्ण

अटल व्योम fm10k_get_strings(काष्ठा net_device *dev,
			      u32 stringset, u8 *data)
अणु
	चयन (stringset) अणु
	हाल ETH_SS_TEST:
		स_नकल(data, fm10k_gstrings_test,
		       FM10K_TEST_LEN * ETH_GSTRING_LEN);
		अवरोध;
	हाल ETH_SS_STATS:
		fm10k_get_stat_strings(dev, data);
		अवरोध;
	हाल ETH_SS_PRIV_FLAGS:
		स_नकल(data, fm10k_prv_flags,
		       FM10K_PRV_FLAG_LEN * ETH_GSTRING_LEN);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक fm10k_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	पूर्णांक stats_len = FM10K_STATIC_STATS_LEN;

	चयन (sset) अणु
	हाल ETH_SS_TEST:
		वापस FM10K_TEST_LEN;
	हाल ETH_SS_STATS:
		stats_len += hw->mac.max_queues * 2 * FM10K_QUEUE_STATS_LEN;

		अगर (hw->mac.type != fm10k_mac_vf)
			stats_len += FM10K_PF_STATS_LEN;

		वापस stats_len;
	हाल ETH_SS_PRIV_FLAGS:
		वापस FM10K_PRV_FLAG_LEN;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम __fm10k_add_ethtool_stats(u64 **data, व्योम *poपूर्णांकer,
				      स्थिर काष्ठा fm10k_stats stats[],
				      स्थिर अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!poपूर्णांकer) अणु
		/* memory is not zero allocated so we have to clear it */
		क्रम (i = 0; i < size; i++)
			*((*data)++) = 0;
		वापस;
	पूर्ण

	क्रम (i = 0; i < size; i++) अणु
		अक्षर *p = (अक्षर *)poपूर्णांकer + stats[i].stat_offset;

		चयन (stats[i].माप_stat) अणु
		हाल माप(u64):
			*((*data)++) = *(u64 *)p;
			अवरोध;
		हाल माप(u32):
			*((*data)++) = *(u32 *)p;
			अवरोध;
		हाल माप(u16):
			*((*data)++) = *(u16 *)p;
			अवरोध;
		हाल माप(u8):
			*((*data)++) = *(u8 *)p;
			अवरोध;
		शेष:
			WARN_ONCE(1, "unexpected stat size for %s",
				  stats[i].stat_string);
			*((*data)++) = 0;
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा fm10k_add_ethtool_stats(data, poपूर्णांकer, stats) \
	__fm10k_add_ethtool_stats(data, poपूर्णांकer, stats, ARRAY_SIZE(stats))

अटल व्योम fm10k_get_ethtool_stats(काष्ठा net_device *netdev,
				    काष्ठा ethtool_stats __always_unused *stats,
				    u64 *data)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(netdev);
	काष्ठा net_device_stats *net_stats = &netdev->stats;
	पूर्णांक i;

	fm10k_update_stats(पूर्णांकerface);

	fm10k_add_ethtool_stats(&data, net_stats, fm10k_gstrings_net_stats);

	fm10k_add_ethtool_stats(&data, पूर्णांकerface, fm10k_gstrings_global_stats);

	fm10k_add_ethtool_stats(&data, &पूर्णांकerface->hw.mbx,
				fm10k_gstrings_mbx_stats);

	अगर (पूर्णांकerface->hw.mac.type != fm10k_mac_vf) अणु
		fm10k_add_ethtool_stats(&data, पूर्णांकerface,
					fm10k_gstrings_pf_stats);
	पूर्ण

	क्रम (i = 0; i < पूर्णांकerface->hw.mac.max_queues; i++) अणु
		काष्ठा fm10k_ring *ring;

		ring = पूर्णांकerface->tx_ring[i];
		fm10k_add_ethtool_stats(&data, ring,
					fm10k_gstrings_queue_stats);

		ring = पूर्णांकerface->rx_ring[i];
		fm10k_add_ethtool_stats(&data, ring,
					fm10k_gstrings_queue_stats);
	पूर्ण
पूर्ण

/* If function below adds more रेजिस्टरs this define needs to be updated */
#घोषणा FM10K_REGS_LEN_Q 29

अटल व्योम fm10k_get_reg_q(काष्ठा fm10k_hw *hw, u32 *buff, पूर्णांक i)
अणु
	पूर्णांक idx = 0;

	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_RDBAL(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_RDBAH(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_RDLEN(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_TPH_RXCTRL(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_RDH(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_RDT(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_RXQCTL(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_RXDCTL(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_RXINT(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_SRRCTL(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_QPRC(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_QPRDC(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_QBRC_L(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_QBRC_H(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_TDBAL(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_TDBAH(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_TDLEN(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_TPH_TXCTRL(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_TDH(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_TDT(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_TXDCTL(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_TXQCTL(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_TXINT(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_QPTC(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_QBTC_L(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_QBTC_H(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_TQDLOC(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_TX_SGLORT(i));
	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_PFVTCTL(i));

	BUG_ON(idx != FM10K_REGS_LEN_Q);
पूर्ण

/* If function above adds more रेजिस्टरs this define needs to be updated */
#घोषणा FM10K_REGS_LEN_VSI 43

अटल व्योम fm10k_get_reg_vsi(काष्ठा fm10k_hw *hw, u32 *buff, पूर्णांक i)
अणु
	पूर्णांक idx = 0, j;

	buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_MRQC(i));
	क्रम (j = 0; j < 10; j++)
		buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_RSSRK(i, j));
	क्रम (j = 0; j < 32; j++)
		buff[idx++] = fm10k_पढ़ो_reg(hw, FM10K_RETA(i, j));

	BUG_ON(idx != FM10K_REGS_LEN_VSI);
पूर्ण

अटल व्योम fm10k_get_regs(काष्ठा net_device *netdev,
			   काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(netdev);
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	u32 *buff = p;
	u16 i;

	regs->version = BIT(24) | (hw->revision_id << 16) | hw->device_id;

	चयन (hw->mac.type) अणु
	हाल fm10k_mac_pf:
		/* General PF Registers */
		*(buff++) = fm10k_पढ़ो_reg(hw, FM10K_CTRL);
		*(buff++) = fm10k_पढ़ो_reg(hw, FM10K_CTRL_EXT);
		*(buff++) = fm10k_पढ़ो_reg(hw, FM10K_GCR);
		*(buff++) = fm10k_पढ़ो_reg(hw, FM10K_GCR_EXT);

		क्रम (i = 0; i < 8; i++) अणु
			*(buff++) = fm10k_पढ़ो_reg(hw, FM10K_DGLORTMAP(i));
			*(buff++) = fm10k_पढ़ो_reg(hw, FM10K_DGLORTDEC(i));
		पूर्ण

		क्रम (i = 0; i < 65; i++) अणु
			fm10k_get_reg_vsi(hw, buff, i);
			buff += FM10K_REGS_LEN_VSI;
		पूर्ण

		*(buff++) = fm10k_पढ़ो_reg(hw, FM10K_DMA_CTRL);
		*(buff++) = fm10k_पढ़ो_reg(hw, FM10K_DMA_CTRL2);

		क्रम (i = 0; i < FM10K_MAX_QUEUES_PF; i++) अणु
			fm10k_get_reg_q(hw, buff, i);
			buff += FM10K_REGS_LEN_Q;
		पूर्ण

		*(buff++) = fm10k_पढ़ो_reg(hw, FM10K_TPH_CTRL);

		क्रम (i = 0; i < 8; i++)
			*(buff++) = fm10k_पढ़ो_reg(hw, FM10K_INT_MAP(i));

		/* Interrupt Throttling Registers */
		क्रम (i = 0; i < 130; i++)
			*(buff++) = fm10k_पढ़ो_reg(hw, FM10K_ITR(i));

		अवरोध;
	हाल fm10k_mac_vf:
		/* General VF रेजिस्टरs */
		*(buff++) = fm10k_पढ़ो_reg(hw, FM10K_VFCTRL);
		*(buff++) = fm10k_पढ़ो_reg(hw, FM10K_VFINT_MAP);
		*(buff++) = fm10k_पढ़ो_reg(hw, FM10K_VFSYSTIME);

		/* Interrupt Throttling Registers */
		क्रम (i = 0; i < 8; i++)
			*(buff++) = fm10k_पढ़ो_reg(hw, FM10K_VFITR(i));

		fm10k_get_reg_vsi(hw, buff, 0);
		buff += FM10K_REGS_LEN_VSI;

		क्रम (i = 0; i < FM10K_MAX_QUEUES_POOL; i++) अणु
			अगर (i < hw->mac.max_queues)
				fm10k_get_reg_q(hw, buff, i);
			अन्यथा
				स_रखो(buff, 0, माप(u32) * FM10K_REGS_LEN_Q);
			buff += FM10K_REGS_LEN_Q;
		पूर्ण

		अवरोध;
	शेष:
		वापस;
	पूर्ण
पूर्ण

/* If function above adds more रेजिस्टरs these define need to be updated */
#घोषणा FM10K_REGS_LEN_PF \
(162 + (65 * FM10K_REGS_LEN_VSI) + (FM10K_MAX_QUEUES_PF * FM10K_REGS_LEN_Q))
#घोषणा FM10K_REGS_LEN_VF \
(11 + FM10K_REGS_LEN_VSI + (FM10K_MAX_QUEUES_POOL * FM10K_REGS_LEN_Q))

अटल पूर्णांक fm10k_get_regs_len(काष्ठा net_device *netdev)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(netdev);
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;

	चयन (hw->mac.type) अणु
	हाल fm10k_mac_pf:
		वापस FM10K_REGS_LEN_PF * माप(u32);
	हाल fm10k_mac_vf:
		वापस FM10K_REGS_LEN_VF * माप(u32);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम fm10k_get_drvinfo(काष्ठा net_device *dev,
			      काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);

	म_नकलन(info->driver, fm10k_driver_name,
		माप(info->driver) - 1);
	म_नकलन(info->bus_info, pci_name(पूर्णांकerface->pdev),
		माप(info->bus_info) - 1);
पूर्ण

अटल व्योम fm10k_get_छोड़ोparam(काष्ठा net_device *dev,
				 काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);

	/* record fixed values क्रम स्वतःneg and tx छोड़ो */
	छोड़ो->स्वतःneg = 0;
	छोड़ो->tx_छोड़ो = 1;

	छोड़ो->rx_छोड़ो = पूर्णांकerface->rx_छोड़ो ? 1 : 0;
पूर्ण

अटल पूर्णांक fm10k_set_छोड़ोparam(काष्ठा net_device *dev,
				काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;

	अगर (छोड़ो->स्वतःneg || !छोड़ो->tx_छोड़ो)
		वापस -EINVAL;

	/* we can only support छोड़ो on the PF to aव्योम head-of-line blocking */
	अगर (hw->mac.type == fm10k_mac_pf)
		पूर्णांकerface->rx_छोड़ो = छोड़ो->rx_छोड़ो ? ~0 : 0;
	अन्यथा अगर (छोड़ो->rx_छोड़ो)
		वापस -EINVAL;

	अगर (netअगर_running(dev))
		fm10k_update_rx_drop_en(पूर्णांकerface);

	वापस 0;
पूर्ण

अटल u32 fm10k_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(netdev);

	वापस पूर्णांकerface->msg_enable;
पूर्ण

अटल व्योम fm10k_set_msglevel(काष्ठा net_device *netdev, u32 data)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(netdev);

	पूर्णांकerface->msg_enable = data;
पूर्ण

अटल व्योम fm10k_get_ringparam(काष्ठा net_device *netdev,
				काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(netdev);

	ring->rx_max_pending = FM10K_MAX_RXD;
	ring->tx_max_pending = FM10K_MAX_TXD;
	ring->rx_mini_max_pending = 0;
	ring->rx_jumbo_max_pending = 0;
	ring->rx_pending = पूर्णांकerface->rx_ring_count;
	ring->tx_pending = पूर्णांकerface->tx_ring_count;
	ring->rx_mini_pending = 0;
	ring->rx_jumbo_pending = 0;
पूर्ण

अटल पूर्णांक fm10k_set_ringparam(काष्ठा net_device *netdev,
			       काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(netdev);
	काष्ठा fm10k_ring *temp_ring;
	पूर्णांक i, err = 0;
	u32 new_rx_count, new_tx_count;

	अगर ((ring->rx_mini_pending) || (ring->rx_jumbo_pending))
		वापस -EINVAL;

	new_tx_count = clamp_t(u32, ring->tx_pending,
			       FM10K_MIN_TXD, FM10K_MAX_TXD);
	new_tx_count = ALIGN(new_tx_count, FM10K_REQ_TX_DESCRIPTOR_MULTIPLE);

	new_rx_count = clamp_t(u32, ring->rx_pending,
			       FM10K_MIN_RXD, FM10K_MAX_RXD);
	new_rx_count = ALIGN(new_rx_count, FM10K_REQ_RX_DESCRIPTOR_MULTIPLE);

	अगर ((new_tx_count == पूर्णांकerface->tx_ring_count) &&
	    (new_rx_count == पूर्णांकerface->rx_ring_count)) अणु
		/* nothing to करो */
		वापस 0;
	पूर्ण

	जबतक (test_and_set_bit(__FM10K_RESETTING, पूर्णांकerface->state))
		usleep_range(1000, 2000);

	अगर (!netअगर_running(पूर्णांकerface->netdev)) अणु
		क्रम (i = 0; i < पूर्णांकerface->num_tx_queues; i++)
			पूर्णांकerface->tx_ring[i]->count = new_tx_count;
		क्रम (i = 0; i < पूर्णांकerface->num_rx_queues; i++)
			पूर्णांकerface->rx_ring[i]->count = new_rx_count;
		पूर्णांकerface->tx_ring_count = new_tx_count;
		पूर्णांकerface->rx_ring_count = new_rx_count;
		जाओ clear_reset;
	पूर्ण

	/* allocate temporary buffer to store rings in */
	i = max_t(पूर्णांक, पूर्णांकerface->num_tx_queues, पूर्णांकerface->num_rx_queues);
	temp_ring = vदो_स्मृति(array_size(i, माप(काष्ठा fm10k_ring)));

	अगर (!temp_ring) अणु
		err = -ENOMEM;
		जाओ clear_reset;
	पूर्ण

	fm10k_करोwn(पूर्णांकerface);

	/* Setup new Tx resources and मुक्त the old Tx resources in that order.
	 * We can then assign the new resources to the rings via a स_नकल.
	 * The advantage to this approach is that we are guaranteed to still
	 * have resources even in the हाल of an allocation failure.
	 */
	अगर (new_tx_count != पूर्णांकerface->tx_ring_count) अणु
		क्रम (i = 0; i < पूर्णांकerface->num_tx_queues; i++) अणु
			स_नकल(&temp_ring[i], पूर्णांकerface->tx_ring[i],
			       माप(काष्ठा fm10k_ring));

			temp_ring[i].count = new_tx_count;
			err = fm10k_setup_tx_resources(&temp_ring[i]);
			अगर (err) अणु
				जबतक (i) अणु
					i--;
					fm10k_मुक्त_tx_resources(&temp_ring[i]);
				पूर्ण
				जाओ err_setup;
			पूर्ण
		पूर्ण

		क्रम (i = 0; i < पूर्णांकerface->num_tx_queues; i++) अणु
			fm10k_मुक्त_tx_resources(पूर्णांकerface->tx_ring[i]);

			स_नकल(पूर्णांकerface->tx_ring[i], &temp_ring[i],
			       माप(काष्ठा fm10k_ring));
		पूर्ण

		पूर्णांकerface->tx_ring_count = new_tx_count;
	पूर्ण

	/* Repeat the process क्रम the Rx rings अगर needed */
	अगर (new_rx_count != पूर्णांकerface->rx_ring_count) अणु
		क्रम (i = 0; i < पूर्णांकerface->num_rx_queues; i++) अणु
			स_नकल(&temp_ring[i], पूर्णांकerface->rx_ring[i],
			       माप(काष्ठा fm10k_ring));

			temp_ring[i].count = new_rx_count;
			err = fm10k_setup_rx_resources(&temp_ring[i]);
			अगर (err) अणु
				जबतक (i) अणु
					i--;
					fm10k_मुक्त_rx_resources(&temp_ring[i]);
				पूर्ण
				जाओ err_setup;
			पूर्ण
		पूर्ण

		क्रम (i = 0; i < पूर्णांकerface->num_rx_queues; i++) अणु
			fm10k_मुक्त_rx_resources(पूर्णांकerface->rx_ring[i]);

			स_नकल(पूर्णांकerface->rx_ring[i], &temp_ring[i],
			       माप(काष्ठा fm10k_ring));
		पूर्ण

		पूर्णांकerface->rx_ring_count = new_rx_count;
	पूर्ण

err_setup:
	fm10k_up(पूर्णांकerface);
	vमुक्त(temp_ring);
clear_reset:
	clear_bit(__FM10K_RESETTING, पूर्णांकerface->state);
	वापस err;
पूर्ण

अटल पूर्णांक fm10k_get_coalesce(काष्ठा net_device *dev,
			      काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);

	ec->use_adaptive_tx_coalesce = ITR_IS_ADAPTIVE(पूर्णांकerface->tx_itr);
	ec->tx_coalesce_usecs = पूर्णांकerface->tx_itr & ~FM10K_ITR_ADAPTIVE;

	ec->use_adaptive_rx_coalesce = ITR_IS_ADAPTIVE(पूर्णांकerface->rx_itr);
	ec->rx_coalesce_usecs = पूर्णांकerface->rx_itr & ~FM10K_ITR_ADAPTIVE;

	वापस 0;
पूर्ण

अटल पूर्णांक fm10k_set_coalesce(काष्ठा net_device *dev,
			      काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);
	u16 tx_itr, rx_itr;
	पूर्णांक i;

	/* verअगरy limits */
	अगर ((ec->rx_coalesce_usecs > FM10K_ITR_MAX) ||
	    (ec->tx_coalesce_usecs > FM10K_ITR_MAX))
		वापस -EINVAL;

	/* record settings */
	tx_itr = ec->tx_coalesce_usecs;
	rx_itr = ec->rx_coalesce_usecs;

	/* set initial values क्रम adaptive ITR */
	अगर (ec->use_adaptive_tx_coalesce)
		tx_itr = FM10K_ITR_ADAPTIVE | FM10K_TX_ITR_DEFAULT;

	अगर (ec->use_adaptive_rx_coalesce)
		rx_itr = FM10K_ITR_ADAPTIVE | FM10K_RX_ITR_DEFAULT;

	/* update पूर्णांकerface */
	पूर्णांकerface->tx_itr = tx_itr;
	पूर्णांकerface->rx_itr = rx_itr;

	/* update q_vectors */
	क्रम (i = 0; i < पूर्णांकerface->num_q_vectors; i++) अणु
		काष्ठा fm10k_q_vector *qv = पूर्णांकerface->q_vector[i];

		qv->tx.itr = tx_itr;
		qv->rx.itr = rx_itr;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fm10k_get_rss_hash_opts(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface,
				   काष्ठा ethtool_rxnfc *cmd)
अणु
	cmd->data = 0;

	/* Report शेष options क्रम RSS on fm10k */
	चयन (cmd->flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल TCP_V6_FLOW:
		cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		fallthrough;
	हाल UDP_V4_FLOW:
		अगर (test_bit(FM10K_FLAG_RSS_FIELD_IPV4_UDP,
			     पूर्णांकerface->flags))
			cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		fallthrough;
	हाल SCTP_V4_FLOW:
	हाल SCTP_V6_FLOW:
	हाल AH_ESP_V4_FLOW:
	हाल AH_ESP_V6_FLOW:
	हाल AH_V4_FLOW:
	हाल AH_V6_FLOW:
	हाल ESP_V4_FLOW:
	हाल ESP_V6_FLOW:
	हाल IPV4_FLOW:
	हाल IPV6_FLOW:
		cmd->data |= RXH_IP_SRC | RXH_IP_DST;
		अवरोध;
	हाल UDP_V6_FLOW:
		अगर (test_bit(FM10K_FLAG_RSS_FIELD_IPV6_UDP,
			     पूर्णांकerface->flags))
			cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		cmd->data |= RXH_IP_SRC | RXH_IP_DST;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fm10k_get_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd,
			   u32 __always_unused *rule_locs)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);
	पूर्णांक ret = -EOPNOTSUPP;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		cmd->data = पूर्णांकerface->num_rx_queues;
		ret = 0;
		अवरोध;
	हाल ETHTOOL_GRXFH:
		ret = fm10k_get_rss_hash_opts(पूर्णांकerface, cmd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fm10k_set_rss_hash_opt(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface,
				  काष्ठा ethtool_rxnfc *nfc)
अणु
	पूर्णांक rss_ipv4_udp = test_bit(FM10K_FLAG_RSS_FIELD_IPV4_UDP,
				    पूर्णांकerface->flags);
	पूर्णांक rss_ipv6_udp = test_bit(FM10K_FLAG_RSS_FIELD_IPV6_UDP,
				    पूर्णांकerface->flags);

	/* RSS करोes not support anything other than hashing
	 * to queues on src and dst IPs and ports
	 */
	अगर (nfc->data & ~(RXH_IP_SRC | RXH_IP_DST |
			  RXH_L4_B_0_1 | RXH_L4_B_2_3))
		वापस -EINVAL;

	चयन (nfc->flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल TCP_V6_FLOW:
		अगर (!(nfc->data & RXH_IP_SRC) ||
		    !(nfc->data & RXH_IP_DST) ||
		    !(nfc->data & RXH_L4_B_0_1) ||
		    !(nfc->data & RXH_L4_B_2_3))
			वापस -EINVAL;
		अवरोध;
	हाल UDP_V4_FLOW:
		अगर (!(nfc->data & RXH_IP_SRC) ||
		    !(nfc->data & RXH_IP_DST))
			वापस -EINVAL;
		चयन (nfc->data & (RXH_L4_B_0_1 | RXH_L4_B_2_3)) अणु
		हाल 0:
			clear_bit(FM10K_FLAG_RSS_FIELD_IPV4_UDP,
				  पूर्णांकerface->flags);
			अवरोध;
		हाल (RXH_L4_B_0_1 | RXH_L4_B_2_3):
			set_bit(FM10K_FLAG_RSS_FIELD_IPV4_UDP,
				पूर्णांकerface->flags);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल UDP_V6_FLOW:
		अगर (!(nfc->data & RXH_IP_SRC) ||
		    !(nfc->data & RXH_IP_DST))
			वापस -EINVAL;
		चयन (nfc->data & (RXH_L4_B_0_1 | RXH_L4_B_2_3)) अणु
		हाल 0:
			clear_bit(FM10K_FLAG_RSS_FIELD_IPV6_UDP,
				  पूर्णांकerface->flags);
			अवरोध;
		हाल (RXH_L4_B_0_1 | RXH_L4_B_2_3):
			set_bit(FM10K_FLAG_RSS_FIELD_IPV6_UDP,
				पूर्णांकerface->flags);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल AH_ESP_V4_FLOW:
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
	हाल SCTP_V4_FLOW:
	हाल AH_ESP_V6_FLOW:
	हाल AH_V6_FLOW:
	हाल ESP_V6_FLOW:
	हाल SCTP_V6_FLOW:
		अगर (!(nfc->data & RXH_IP_SRC) ||
		    !(nfc->data & RXH_IP_DST) ||
		    (nfc->data & RXH_L4_B_0_1) ||
		    (nfc->data & RXH_L4_B_2_3))
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* If something changed we need to update the MRQC रेजिस्टर. Note that
	 * test_bit() is guaranteed to वापस strictly 0 or 1, so testing क्रम
	 * equality is safe.
	 */
	अगर ((rss_ipv4_udp != test_bit(FM10K_FLAG_RSS_FIELD_IPV4_UDP,
				      पूर्णांकerface->flags)) ||
	    (rss_ipv6_udp != test_bit(FM10K_FLAG_RSS_FIELD_IPV6_UDP,
				      पूर्णांकerface->flags))) अणु
		काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
		bool warn = false;
		u32 mrqc;

		/* Perक्रमm hash on these packet types */
		mrqc = FM10K_MRQC_IPV4 |
		       FM10K_MRQC_TCP_IPV4 |
		       FM10K_MRQC_IPV6 |
		       FM10K_MRQC_TCP_IPV6;

		अगर (test_bit(FM10K_FLAG_RSS_FIELD_IPV4_UDP,
			     पूर्णांकerface->flags)) अणु
			mrqc |= FM10K_MRQC_UDP_IPV4;
			warn = true;
		पूर्ण
		अगर (test_bit(FM10K_FLAG_RSS_FIELD_IPV6_UDP,
			     पूर्णांकerface->flags)) अणु
			mrqc |= FM10K_MRQC_UDP_IPV6;
			warn = true;
		पूर्ण

		/* If we enable UDP RSS display a warning that this may cause
		 * fragmented UDP packets to arrive out of order.
		 */
		अगर (warn)
			netअगर_warn(पूर्णांकerface, drv, पूर्णांकerface->netdev,
				   "enabling UDP RSS: fragmented packets may arrive out of order to the stack above\n");

		fm10k_ग_लिखो_reg(hw, FM10K_MRQC(0), mrqc);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fm10k_set_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);
	पूर्णांक ret = -EOPNOTSUPP;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_SRXFH:
		ret = fm10k_set_rss_hash_opt(पूर्णांकerface, cmd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fm10k_mbx_test(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface, u64 *data)
अणु
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	काष्ठा fm10k_mbx_info *mbx = &hw->mbx;
	u32 attr_flag, test_msg[6];
	अचिन्हित दीर्घ समयout;
	पूर्णांक err = -EINVAL;

	/* For now this is a VF only feature */
	अगर (hw->mac.type != fm10k_mac_vf)
		वापस 0;

	/* loop through both nested and unnested attribute types */
	क्रम (attr_flag = BIT(FM10K_TEST_MSG_UNSET);
	     attr_flag < BIT(2 * FM10K_TEST_MSG_NESTED);
	     attr_flag += attr_flag) अणु
		/* generate message to be tested */
		fm10k_tlv_msg_test_create(test_msg, attr_flag);

		fm10k_mbx_lock(पूर्णांकerface);
		mbx->test_result = FM10K_NOT_IMPLEMENTED;
		err = mbx->ops.enqueue_tx(hw, mbx, test_msg);
		fm10k_mbx_unlock(पूर्णांकerface);

		/* रुको up to 1 second क्रम response */
		समयout = jअगरfies + HZ;
		करो अणु
			अगर (err < 0)
				जाओ err_out;

			usleep_range(500, 1000);

			fm10k_mbx_lock(पूर्णांकerface);
			mbx->ops.process(hw, mbx);
			fm10k_mbx_unlock(पूर्णांकerface);

			err = mbx->test_result;
			अगर (!err)
				अवरोध;
		पूर्ण जबतक (समय_is_after_jअगरfies(समयout));

		/* reporting errors */
		अगर (err)
			जाओ err_out;
	पूर्ण

err_out:
	*data = err < 0 ? (attr_flag) : (err > 0);
	वापस err;
पूर्ण

अटल व्योम fm10k_self_test(काष्ठा net_device *dev,
			    काष्ठा ethtool_test *eth_test, u64 *data)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;

	स_रखो(data, 0, माप(*data) * FM10K_TEST_LEN);

	अगर (FM10K_REMOVED(hw->hw_addr)) अणु
		netअगर_err(पूर्णांकerface, drv, dev,
			  "Interface removed - test blocked\n");
		eth_test->flags |= ETH_TEST_FL_FAILED;
		वापस;
	पूर्ण

	अगर (fm10k_mbx_test(पूर्णांकerface, &data[FM10K_TEST_MBX]))
		eth_test->flags |= ETH_TEST_FL_FAILED;
पूर्ण

अटल u32 fm10k_get_priv_flags(काष्ठा net_device *netdev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक fm10k_set_priv_flags(काष्ठा net_device *netdev, u32 priv_flags)
अणु
	अगर (priv_flags >= BIT(FM10K_PRV_FLAG_LEN))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल u32 fm10k_get_reta_size(काष्ठा net_device __always_unused *netdev)
अणु
	वापस FM10K_RETA_SIZE * FM10K_RETA_ENTRIES_PER_REG;
पूर्ण

व्योम fm10k_ग_लिखो_reta(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface, स्थिर u32 *indir)
अणु
	u16 rss_i = पूर्णांकerface->ring_feature[RING_F_RSS].indices;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	u32 table[4];
	पूर्णांक i, j;

	/* record entries to reta table */
	क्रम (i = 0; i < FM10K_RETA_SIZE; i++) अणु
		u32 reta, n;

		/* generate a new table अगर we weren't given one */
		क्रम (j = 0; j < 4; j++) अणु
			अगर (indir)
				n = indir[4 * i + j];
			अन्यथा
				n = ethtool_rxfh_indir_शेष(4 * i + j,
							       rss_i);

			table[j] = n;
		पूर्ण

		reta = table[0] |
			(table[1] << 8) |
			(table[2] << 16) |
			(table[3] << 24);

		अगर (पूर्णांकerface->reta[i] == reta)
			जारी;

		पूर्णांकerface->reta[i] = reta;
		fm10k_ग_लिखो_reg(hw, FM10K_RETA(0, i), reta);
	पूर्ण
पूर्ण

अटल पूर्णांक fm10k_get_reta(काष्ठा net_device *netdev, u32 *indir)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(netdev);
	पूर्णांक i;

	अगर (!indir)
		वापस 0;

	क्रम (i = 0; i < FM10K_RETA_SIZE; i++, indir += 4) अणु
		u32 reta = पूर्णांकerface->reta[i];

		indir[0] = (reta << 24) >> 24;
		indir[1] = (reta << 16) >> 24;
		indir[2] = (reta <<  8) >> 24;
		indir[3] = (reta) >> 24;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fm10k_set_reta(काष्ठा net_device *netdev, स्थिर u32 *indir)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(netdev);
	पूर्णांक i;
	u16 rss_i;

	अगर (!indir)
		वापस 0;

	/* Verअगरy user input. */
	rss_i = पूर्णांकerface->ring_feature[RING_F_RSS].indices;
	क्रम (i = fm10k_get_reta_size(netdev); i--;) अणु
		अगर (indir[i] < rss_i)
			जारी;
		वापस -EINVAL;
	पूर्ण

	fm10k_ग_लिखो_reta(पूर्णांकerface, indir);

	वापस 0;
पूर्ण

अटल u32 fm10k_get_rssrk_size(काष्ठा net_device __always_unused *netdev)
अणु
	वापस FM10K_RSSRK_SIZE * FM10K_RSSRK_ENTRIES_PER_REG;
पूर्ण

अटल पूर्णांक fm10k_get_rssh(काष्ठा net_device *netdev, u32 *indir, u8 *key,
			  u8 *hfunc)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(netdev);
	पूर्णांक i, err;

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	err = fm10k_get_reta(netdev, indir);
	अगर (err || !key)
		वापस err;

	क्रम (i = 0; i < FM10K_RSSRK_SIZE; i++, key += 4)
		*(__le32 *)key = cpu_to_le32(पूर्णांकerface->rssrk[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक fm10k_set_rssh(काष्ठा net_device *netdev, स्थिर u32 *indir,
			  स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(netdev);
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	पूर्णांक i, err;

	/* We करो not allow change in unsupported parameters */
	अगर (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP)
		वापस -EOPNOTSUPP;

	err = fm10k_set_reta(netdev, indir);
	अगर (err || !key)
		वापस err;

	क्रम (i = 0; i < FM10K_RSSRK_SIZE; i++, key += 4) अणु
		u32 rssrk = le32_to_cpu(*(__le32 *)key);

		अगर (पूर्णांकerface->rssrk[i] == rssrk)
			जारी;

		पूर्णांकerface->rssrk[i] = rssrk;
		fm10k_ग_लिखो_reg(hw, FM10K_RSSRK(0, i), rssrk);
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक fm10k_max_channels(काष्ठा net_device *dev)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);
	अचिन्हित पूर्णांक max_combined = पूर्णांकerface->hw.mac.max_queues;
	u8 tcs = netdev_get_num_tc(dev);

	/* For QoS report channels per traffic class */
	अगर (tcs > 1)
		max_combined = BIT((fls(max_combined / tcs) - 1));

	वापस max_combined;
पूर्ण

अटल व्योम fm10k_get_channels(काष्ठा net_device *dev,
			       काष्ठा ethtool_channels *ch)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);

	/* report maximum channels */
	ch->max_combined = fm10k_max_channels(dev);

	/* report info क्रम other vector */
	ch->max_other = NON_Q_VECTORS;
	ch->other_count = ch->max_other;

	/* record RSS queues */
	ch->combined_count = पूर्णांकerface->ring_feature[RING_F_RSS].indices;
पूर्ण

अटल पूर्णांक fm10k_set_channels(काष्ठा net_device *dev,
			      काष्ठा ethtool_channels *ch)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);
	अचिन्हित पूर्णांक count = ch->combined_count;

	/* verअगरy they are not requesting separate vectors */
	अगर (!count || ch->rx_count || ch->tx_count)
		वापस -EINVAL;

	/* verअगरy other_count has not changed */
	अगर (ch->other_count != NON_Q_VECTORS)
		वापस -EINVAL;

	/* verअगरy the number of channels करोes not exceed hardware limits */
	अगर (count > fm10k_max_channels(dev))
		वापस -EINVAL;

	पूर्णांकerface->ring_feature[RING_F_RSS].limit = count;

	/* use setup TC to update any traffic class queue mapping */
	वापस fm10k_setup_tc(dev, netdev_get_num_tc(dev));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops fm10k_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_USE_ADAPTIVE,
	.get_strings		= fm10k_get_strings,
	.get_sset_count		= fm10k_get_sset_count,
	.get_ethtool_stats      = fm10k_get_ethtool_stats,
	.get_drvinfo		= fm10k_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.get_छोड़ोparam		= fm10k_get_छोड़ोparam,
	.set_छोड़ोparam		= fm10k_set_छोड़ोparam,
	.get_msglevel		= fm10k_get_msglevel,
	.set_msglevel		= fm10k_set_msglevel,
	.get_ringparam		= fm10k_get_ringparam,
	.set_ringparam		= fm10k_set_ringparam,
	.get_coalesce		= fm10k_get_coalesce,
	.set_coalesce		= fm10k_set_coalesce,
	.get_rxnfc		= fm10k_get_rxnfc,
	.set_rxnfc		= fm10k_set_rxnfc,
	.get_regs               = fm10k_get_regs,
	.get_regs_len           = fm10k_get_regs_len,
	.self_test		= fm10k_self_test,
	.get_priv_flags		= fm10k_get_priv_flags,
	.set_priv_flags		= fm10k_set_priv_flags,
	.get_rxfh_indir_size	= fm10k_get_reta_size,
	.get_rxfh_key_size	= fm10k_get_rssrk_size,
	.get_rxfh		= fm10k_get_rssh,
	.set_rxfh		= fm10k_set_rssh,
	.get_channels		= fm10k_get_channels,
	.set_channels		= fm10k_set_channels,
	.get_ts_info		= ethtool_op_get_ts_info,
पूर्ण;

व्योम fm10k_set_ethtool_ops(काष्ठा net_device *dev)
अणु
	dev->ethtool_ops = &fm10k_ethtool_ops;
पूर्ण
