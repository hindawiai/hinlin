<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2016, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/ethtool.h>
#समावेश <linux/phy.h>

#समावेश "emac.h"

अटल स्थिर अक्षर * स्थिर emac_ethtool_stat_strings[] = अणु
	"rx_ok",
	"rx_bcast",
	"rx_mcast",
	"rx_pause",
	"rx_ctrl",
	"rx_fcs_err",
	"rx_len_err",
	"rx_byte_cnt",
	"rx_runt",
	"rx_frag",
	"rx_sz_64",
	"rx_sz_65_127",
	"rx_sz_128_255",
	"rx_sz_256_511",
	"rx_sz_512_1023",
	"rx_sz_1024_1518",
	"rx_sz_1519_max",
	"rx_sz_ov",
	"rx_rxf_ov",
	"rx_align_err",
	"rx_bcast_byte_cnt",
	"rx_mcast_byte_cnt",
	"rx_err_addr",
	"rx_crc_align",
	"rx_jabbers",
	"tx_ok",
	"tx_bcast",
	"tx_mcast",
	"tx_pause",
	"tx_exc_defer",
	"tx_ctrl",
	"tx_defer",
	"tx_byte_cnt",
	"tx_sz_64",
	"tx_sz_65_127",
	"tx_sz_128_255",
	"tx_sz_256_511",
	"tx_sz_512_1023",
	"tx_sz_1024_1518",
	"tx_sz_1519_max",
	"tx_1_col",
	"tx_2_col",
	"tx_late_col",
	"tx_abort_col",
	"tx_underrun",
	"tx_rd_eop",
	"tx_len_err",
	"tx_trunc",
	"tx_bcast_byte",
	"tx_mcast_byte",
	"tx_col",
पूर्ण;

#घोषणा EMAC_STATS_LEN	ARRAY_SIZE(emac_ethtool_stat_strings)

अटल u32 emac_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा emac_adapter *adpt = netdev_priv(netdev);

	वापस adpt->msg_enable;
पूर्ण

अटल व्योम emac_set_msglevel(काष्ठा net_device *netdev, u32 data)
अणु
	काष्ठा emac_adapter *adpt = netdev_priv(netdev);

	adpt->msg_enable = data;
पूर्ण

अटल पूर्णांक emac_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_PRIV_FLAGS:
		वापस 1;
	हाल ETH_SS_STATS:
		वापस EMAC_STATS_LEN;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम emac_get_strings(काष्ठा net_device *netdev, u32 stringset, u8 *data)
अणु
	अचिन्हित पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_PRIV_FLAGS:
		म_नकल(data, "single-pause-mode");
		अवरोध;

	हाल ETH_SS_STATS:
		क्रम (i = 0; i < EMAC_STATS_LEN; i++) अणु
			strlcpy(data, emac_ethtool_stat_strings[i],
				ETH_GSTRING_LEN);
			data += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम emac_get_ethtool_stats(काष्ठा net_device *netdev,
				   काष्ठा ethtool_stats *stats,
				   u64 *data)
अणु
	काष्ठा emac_adapter *adpt = netdev_priv(netdev);

	spin_lock(&adpt->stats.lock);

	emac_update_hw_stats(adpt);
	स_नकल(data, &adpt->stats, EMAC_STATS_LEN * माप(u64));

	spin_unlock(&adpt->stats.lock);
पूर्ण

अटल पूर्णांक emac_nway_reset(काष्ठा net_device *netdev)
अणु
	काष्ठा phy_device *phydev = netdev->phydev;

	अगर (!phydev)
		वापस -ENODEV;

	वापस genphy_restart_aneg(phydev);
पूर्ण

अटल व्योम emac_get_ringparam(काष्ठा net_device *netdev,
			       काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा emac_adapter *adpt = netdev_priv(netdev);

	ring->rx_max_pending = EMAC_MAX_RX_DESCS;
	ring->tx_max_pending = EMAC_MAX_TX_DESCS;
	ring->rx_pending = adpt->rx_desc_cnt;
	ring->tx_pending = adpt->tx_desc_cnt;
पूर्ण

अटल पूर्णांक emac_set_ringparam(काष्ठा net_device *netdev,
			      काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा emac_adapter *adpt = netdev_priv(netdev);

	/* We करोn't have separate queues/rings क्रम small/large frames, so
	 * reject any attempt to specअगरy those values separately.
	 */
	अगर (ring->rx_mini_pending || ring->rx_jumbo_pending)
		वापस -EINVAL;

	adpt->tx_desc_cnt =
		clamp_val(ring->tx_pending, EMAC_MIN_TX_DESCS, EMAC_MAX_TX_DESCS);

	adpt->rx_desc_cnt =
		clamp_val(ring->rx_pending, EMAC_MIN_RX_DESCS, EMAC_MAX_RX_DESCS);

	अगर (netअगर_running(netdev))
		वापस emac_reinit_locked(adpt);

	वापस 0;
पूर्ण

अटल व्योम emac_get_छोड़ोparam(काष्ठा net_device *netdev,
				काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा emac_adapter *adpt = netdev_priv(netdev);

	छोड़ो->स्वतःneg = adpt->स्वतःmatic ? AUTONEG_ENABLE : AUTONEG_DISABLE;
	छोड़ो->rx_छोड़ो = adpt->rx_flow_control ? 1 : 0;
	छोड़ो->tx_छोड़ो = adpt->tx_flow_control ? 1 : 0;
पूर्ण

अटल पूर्णांक emac_set_छोड़ोparam(काष्ठा net_device *netdev,
			       काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा emac_adapter *adpt = netdev_priv(netdev);

	adpt->स्वतःmatic = छोड़ो->स्वतःneg == AUTONEG_ENABLE;
	adpt->rx_flow_control = छोड़ो->rx_छोड़ो != 0;
	adpt->tx_flow_control = छोड़ो->tx_छोड़ो != 0;

	अगर (netअगर_running(netdev))
		वापस emac_reinit_locked(adpt);

	वापस 0;
पूर्ण

/* Selected रेजिस्टरs that might want to track during runसमय. */
अटल स्थिर u16 emac_regs[] = अणु
	EMAC_DMA_MAS_CTRL,
	EMAC_MAC_CTRL,
	EMAC_TXQ_CTRL_0,
	EMAC_RXQ_CTRL_0,
	EMAC_DMA_CTRL,
	EMAC_INT_MASK,
	EMAC_AXI_MAST_CTRL,
	EMAC_CORE_HW_VERSION,
	EMAC_MISC_CTRL,
पूर्ण;

/* Every समय emac_regs[] above is changed, increase this version number. */
#घोषणा EMAC_REGS_VERSION	0

#घोषणा EMAC_MAX_REG_SIZE	ARRAY_SIZE(emac_regs)

अटल व्योम emac_get_regs(काष्ठा net_device *netdev,
			  काष्ठा ethtool_regs *regs, व्योम *buff)
अणु
	काष्ठा emac_adapter *adpt = netdev_priv(netdev);
	u32 *val = buff;
	अचिन्हित पूर्णांक i;

	regs->version = EMAC_REGS_VERSION;
	regs->len = EMAC_MAX_REG_SIZE * माप(u32);

	क्रम (i = 0; i < EMAC_MAX_REG_SIZE; i++)
		val[i] = पढ़ोl(adpt->base + emac_regs[i]);
पूर्ण

अटल पूर्णांक emac_get_regs_len(काष्ठा net_device *netdev)
अणु
	वापस EMAC_MAX_REG_SIZE * माप(u32);
पूर्ण

#घोषणा EMAC_PRIV_ENABLE_SINGLE_PAUSE	BIT(0)

अटल पूर्णांक emac_set_priv_flags(काष्ठा net_device *netdev, u32 flags)
अणु
	काष्ठा emac_adapter *adpt = netdev_priv(netdev);

	adpt->single_छोड़ो_mode = !!(flags & EMAC_PRIV_ENABLE_SINGLE_PAUSE);

	अगर (netअगर_running(netdev))
		वापस emac_reinit_locked(adpt);

	वापस 0;
पूर्ण

अटल u32 emac_get_priv_flags(काष्ठा net_device *netdev)
अणु
	काष्ठा emac_adapter *adpt = netdev_priv(netdev);

	वापस adpt->single_छोड़ो_mode ? EMAC_PRIV_ENABLE_SINGLE_PAUSE : 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops emac_ethtool_ops = अणु
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,

	.get_msglevel    = emac_get_msglevel,
	.set_msglevel    = emac_set_msglevel,

	.get_sset_count  = emac_get_sset_count,
	.get_strings = emac_get_strings,
	.get_ethtool_stats = emac_get_ethtool_stats,

	.get_ringparam = emac_get_ringparam,
	.set_ringparam = emac_set_ringparam,

	.get_छोड़ोparam = emac_get_छोड़ोparam,
	.set_छोड़ोparam = emac_set_छोड़ोparam,

	.nway_reset = emac_nway_reset,

	.get_link = ethtool_op_get_link,

	.get_regs_len    = emac_get_regs_len,
	.get_regs        = emac_get_regs,

	.set_priv_flags = emac_set_priv_flags,
	.get_priv_flags = emac_get_priv_flags,
पूर्ण;

व्योम emac_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &emac_ethtool_ops;
पूर्ण
