<शैली गुरु>
/*
 * Copyright (c) 2013 Johannes Berg <johannes@sipsolutions.net>
 *
 *  This file is मुक्त software: you may copy, redistribute and/or modअगरy it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation, either version 2 of the License, or (at your
 *  option) any later version.
 *
 *  This file is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License क्रम more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  aदीर्घ with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *
 * Copyright (c) 2012 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <linux/pci.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "alx.h"
#समावेश "reg.h"
#समावेश "hw.h"

/* The order of these strings must match the order of the fields in
 * काष्ठा alx_hw_stats
 * See hw.h
 */
अटल स्थिर अक्षर alx_gstrings_stats[][ETH_GSTRING_LEN] = अणु
	"rx_packets",
	"rx_bcast_packets",
	"rx_mcast_packets",
	"rx_pause_packets",
	"rx_ctrl_packets",
	"rx_fcs_errors",
	"rx_length_errors",
	"rx_bytes",
	"rx_runt_packets",
	"rx_fragments",
	"rx_64B_or_less_packets",
	"rx_65B_to_127B_packets",
	"rx_128B_to_255B_packets",
	"rx_256B_to_511B_packets",
	"rx_512B_to_1023B_packets",
	"rx_1024B_to_1518B_packets",
	"rx_1519B_to_mtu_packets",
	"rx_oversize_packets",
	"rx_rxf_ov_drop_packets",
	"rx_rrd_ov_drop_packets",
	"rx_align_errors",
	"rx_bcast_bytes",
	"rx_mcast_bytes",
	"rx_address_errors",
	"tx_packets",
	"tx_bcast_packets",
	"tx_mcast_packets",
	"tx_pause_packets",
	"tx_exc_defer_packets",
	"tx_ctrl_packets",
	"tx_defer_packets",
	"tx_bytes",
	"tx_64B_or_less_packets",
	"tx_65B_to_127B_packets",
	"tx_128B_to_255B_packets",
	"tx_256B_to_511B_packets",
	"tx_512B_to_1023B_packets",
	"tx_1024B_to_1518B_packets",
	"tx_1519B_to_mtu_packets",
	"tx_single_collision",
	"tx_multiple_collisions",
	"tx_late_collision",
	"tx_abort_collision",
	"tx_underrun",
	"tx_trd_eop",
	"tx_length_errors",
	"tx_trunc_packets",
	"tx_bcast_bytes",
	"tx_mcast_bytes",
	"tx_update",
पूर्ण;

#घोषणा ALX_NUM_STATS ARRAY_SIZE(alx_gstrings_stats)


अटल u32 alx_get_supported_speeds(काष्ठा alx_hw *hw)
अणु
	u32 supported = SUPPORTED_10baseT_Half |
			SUPPORTED_10baseT_Full |
			SUPPORTED_100baseT_Half |
			SUPPORTED_100baseT_Full;

	अगर (alx_hw_giga(hw))
		supported |= SUPPORTED_1000baseT_Full;

	BUILD_BUG_ON(SUPPORTED_10baseT_Half != ADVERTISED_10baseT_Half);
	BUILD_BUG_ON(SUPPORTED_10baseT_Full != ADVERTISED_10baseT_Full);
	BUILD_BUG_ON(SUPPORTED_100baseT_Half != ADVERTISED_100baseT_Half);
	BUILD_BUG_ON(SUPPORTED_100baseT_Full != ADVERTISED_100baseT_Full);
	BUILD_BUG_ON(SUPPORTED_1000baseT_Full != ADVERTISED_1000baseT_Full);

	वापस supported;
पूर्ण

अटल पूर्णांक alx_get_link_ksettings(काष्ठा net_device *netdev,
				  काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा alx_priv *alx = netdev_priv(netdev);
	काष्ठा alx_hw *hw = &alx->hw;
	u32 supported, advertising;

	supported = SUPPORTED_Autoneg |
			  SUPPORTED_TP |
			  SUPPORTED_Pause |
			  SUPPORTED_Asym_Pause;
	अगर (alx_hw_giga(hw))
		supported |= SUPPORTED_1000baseT_Full;
	supported |= alx_get_supported_speeds(hw);

	advertising = ADVERTISED_TP;
	अगर (hw->adv_cfg & ADVERTISED_Autoneg)
		advertising |= hw->adv_cfg;

	cmd->base.port = PORT_TP;
	cmd->base.phy_address = 0;

	अगर (hw->adv_cfg & ADVERTISED_Autoneg)
		cmd->base.स्वतःneg = AUTONEG_ENABLE;
	अन्यथा
		cmd->base.स्वतःneg = AUTONEG_DISABLE;

	अगर (hw->flowctrl & ALX_FC_ANEG && hw->adv_cfg & ADVERTISED_Autoneg) अणु
		अगर (hw->flowctrl & ALX_FC_RX) अणु
			advertising |= ADVERTISED_Pause;

			अगर (!(hw->flowctrl & ALX_FC_TX))
				advertising |= ADVERTISED_Asym_Pause;
		पूर्ण अन्यथा अगर (hw->flowctrl & ALX_FC_TX) अणु
			advertising |= ADVERTISED_Asym_Pause;
		पूर्ण
	पूर्ण

	cmd->base.speed = hw->link_speed;
	cmd->base.duplex = hw->duplex;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक alx_set_link_ksettings(काष्ठा net_device *netdev,
				  स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा alx_priv *alx = netdev_priv(netdev);
	काष्ठा alx_hw *hw = &alx->hw;
	u32 adv_cfg;
	u32 advertising;

	ASSERT_RTNL();

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		अगर (advertising & ~alx_get_supported_speeds(hw))
			वापस -EINVAL;
		adv_cfg = advertising | ADVERTISED_Autoneg;
	पूर्ण अन्यथा अणु
		adv_cfg = alx_speed_to_ethadv(cmd->base.speed,
					      cmd->base.duplex);

		अगर (!adv_cfg || adv_cfg == ADVERTISED_1000baseT_Full)
			वापस -EINVAL;
	पूर्ण

	hw->adv_cfg = adv_cfg;
	वापस alx_setup_speed_duplex(hw, adv_cfg, hw->flowctrl);
पूर्ण

अटल व्योम alx_get_छोड़ोparam(काष्ठा net_device *netdev,
			       काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा alx_priv *alx = netdev_priv(netdev);
	काष्ठा alx_hw *hw = &alx->hw;

	छोड़ो->स्वतःneg = !!(hw->flowctrl & ALX_FC_ANEG &&
			    hw->adv_cfg & ADVERTISED_Autoneg);
	छोड़ो->tx_छोड़ो = !!(hw->flowctrl & ALX_FC_TX);
	छोड़ो->rx_छोड़ो = !!(hw->flowctrl & ALX_FC_RX);
पूर्ण


अटल पूर्णांक alx_set_छोड़ोparam(काष्ठा net_device *netdev,
			      काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा alx_priv *alx = netdev_priv(netdev);
	काष्ठा alx_hw *hw = &alx->hw;
	पूर्णांक err = 0;
	bool reconfig_phy = false;
	u8 fc = 0;

	अगर (छोड़ो->tx_छोड़ो)
		fc |= ALX_FC_TX;
	अगर (छोड़ो->rx_छोड़ो)
		fc |= ALX_FC_RX;
	अगर (छोड़ो->स्वतःneg)
		fc |= ALX_FC_ANEG;

	ASSERT_RTNL();

	/* restart स्वतः-neg क्रम स्वतः-mode */
	अगर (hw->adv_cfg & ADVERTISED_Autoneg) अणु
		अगर (!((fc ^ hw->flowctrl) & ALX_FC_ANEG))
			reconfig_phy = true;
		अगर (fc & hw->flowctrl & ALX_FC_ANEG &&
		    (fc ^ hw->flowctrl) & (ALX_FC_RX | ALX_FC_TX))
			reconfig_phy = true;
	पूर्ण

	अगर (reconfig_phy) अणु
		err = alx_setup_speed_duplex(hw, hw->adv_cfg, fc);
		अगर (err)
			वापस err;
	पूर्ण

	/* flow control on mac */
	अगर ((fc ^ hw->flowctrl) & (ALX_FC_RX | ALX_FC_TX))
		alx_cfg_mac_flowcontrol(hw, fc);

	hw->flowctrl = fc;

	वापस 0;
पूर्ण

अटल u32 alx_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा alx_priv *alx = netdev_priv(netdev);

	वापस alx->msg_enable;
पूर्ण

अटल व्योम alx_set_msglevel(काष्ठा net_device *netdev, u32 data)
अणु
	काष्ठा alx_priv *alx = netdev_priv(netdev);

	alx->msg_enable = data;
पूर्ण

अटल व्योम alx_get_ethtool_stats(काष्ठा net_device *netdev,
				  काष्ठा ethtool_stats *estats, u64 *data)
अणु
	काष्ठा alx_priv *alx = netdev_priv(netdev);
	काष्ठा alx_hw *hw = &alx->hw;

	spin_lock(&alx->stats_lock);

	alx_update_hw_stats(hw);
	BUILD_BUG_ON(माप(hw->stats) - दुरत्व(काष्ठा alx_hw_stats, rx_ok) <
		     ALX_NUM_STATS * माप(u64));
	स_नकल(data, &hw->stats.rx_ok, ALX_NUM_STATS * माप(u64));

	spin_unlock(&alx->stats_lock);
पूर्ण

अटल व्योम alx_get_strings(काष्ठा net_device *netdev, u32 stringset, u8 *buf)
अणु
	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		स_नकल(buf, &alx_gstrings_stats, माप(alx_gstrings_stats));
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक alx_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ALX_NUM_STATS;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

स्थिर काष्ठा ethtool_ops alx_ethtool_ops = अणु
	.get_छोड़ोparam	= alx_get_छोड़ोparam,
	.set_छोड़ोparam	= alx_set_छोड़ोparam,
	.get_msglevel	= alx_get_msglevel,
	.set_msglevel	= alx_set_msglevel,
	.get_link	= ethtool_op_get_link,
	.get_strings	= alx_get_strings,
	.get_sset_count	= alx_get_sset_count,
	.get_ethtool_stats	= alx_get_ethtool_stats,
	.get_link_ksettings	= alx_get_link_ksettings,
	.set_link_ksettings	= alx_set_link_ksettings,
पूर्ण;
