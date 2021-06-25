<शैली गुरु>
/*
 * NXP Wireless LAN device driver: ethtool
 *
 * Copyright 2011-2020 NXP
 *
 * This software file (the "File") is distributed by NXP
 * under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#समावेश "main.h"

अटल व्योम mwअगरiex_ethtool_get_wol(काष्ठा net_device *dev,
				    काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);
	u32 conditions = le32_to_cpu(priv->adapter->hs_cfg.conditions);

	wol->supported = WAKE_UCAST|WAKE_MCAST|WAKE_BCAST|WAKE_PHY;

	अगर (conditions == HS_CFG_COND_DEF)
		वापस;

	अगर (conditions & HS_CFG_COND_UNICAST_DATA)
		wol->wolopts |= WAKE_UCAST;
	अगर (conditions & HS_CFG_COND_MULTICAST_DATA)
		wol->wolopts |= WAKE_MCAST;
	अगर (conditions & HS_CFG_COND_BROADCAST_DATA)
		wol->wolopts |= WAKE_BCAST;
	अगर (conditions & HS_CFG_COND_MAC_EVENT)
		wol->wolopts |= WAKE_PHY;
पूर्ण

अटल पूर्णांक mwअगरiex_ethtool_set_wol(काष्ठा net_device *dev,
				   काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);
	u32 conditions = 0;

	अगर (wol->wolopts & ~(WAKE_UCAST|WAKE_MCAST|WAKE_BCAST|WAKE_PHY))
		वापस -EOPNOTSUPP;

	अगर (wol->wolopts & WAKE_UCAST)
		conditions |= HS_CFG_COND_UNICAST_DATA;
	अगर (wol->wolopts & WAKE_MCAST)
		conditions |= HS_CFG_COND_MULTICAST_DATA;
	अगर (wol->wolopts & WAKE_BCAST)
		conditions |= HS_CFG_COND_BROADCAST_DATA;
	अगर (wol->wolopts & WAKE_PHY)
		conditions |= HS_CFG_COND_MAC_EVENT;
	अगर (wol->wolopts == 0)
		conditions |= HS_CFG_COND_DEF;
	priv->adapter->hs_cfg.conditions = cpu_to_le32(conditions);

	वापस 0;
पूर्ण

स्थिर काष्ठा ethtool_ops mwअगरiex_ethtool_ops = अणु
	.get_wol = mwअगरiex_ethtool_get_wol,
	.set_wol = mwअगरiex_ethtool_set_wol,
पूर्ण;
