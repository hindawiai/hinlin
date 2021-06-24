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
 */

#समावेश <linux/kernel.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/netdevice.h>

#समावेश "ipoib.h"

काष्ठा ipoib_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक stat_offset;
पूर्ण;

#घोषणा IPOIB_NETDEV_STAT(m) अणु \
		.stat_string = #m, \
		.stat_offset = दुरत्व(काष्ठा rtnl_link_stats64, m) पूर्ण

अटल स्थिर काष्ठा ipoib_stats ipoib_gstrings_stats[] = अणु
	IPOIB_NETDEV_STAT(rx_packets),
	IPOIB_NETDEV_STAT(tx_packets),
	IPOIB_NETDEV_STAT(rx_bytes),
	IPOIB_NETDEV_STAT(tx_bytes),
	IPOIB_NETDEV_STAT(tx_errors),
	IPOIB_NETDEV_STAT(rx_dropped),
	IPOIB_NETDEV_STAT(tx_dropped),
	IPOIB_NETDEV_STAT(multicast),
पूर्ण;

#घोषणा IPOIB_GLOBAL_STATS_LEN	ARRAY_SIZE(ipoib_gstrings_stats)

अटल व्योम ipoib_get_drvinfo(काष्ठा net_device *netdev,
			      काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(netdev);

	ib_get_device_fw_str(priv->ca, drvinfo->fw_version);

	strlcpy(drvinfo->bus_info, dev_name(priv->ca->dev.parent),
		माप(drvinfo->bus_info));

	strlcpy(drvinfo->driver, "ib_ipoib", माप(drvinfo->driver));
पूर्ण

अटल पूर्णांक ipoib_get_coalesce(काष्ठा net_device *dev,
			      काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	coal->rx_coalesce_usecs = priv->ethtool.coalesce_usecs;
	coal->rx_max_coalesced_frames = priv->ethtool.max_coalesced_frames;

	वापस 0;
पूर्ण

अटल पूर्णांक ipoib_set_coalesce(काष्ठा net_device *dev,
			      काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	पूर्णांक ret;

	/*
	 * These values are saved in the निजी data and वापसed
	 * when ipoib_get_coalesce() is called
	 */
	अगर (coal->rx_coalesce_usecs       > 0xffff ||
	    coal->rx_max_coalesced_frames > 0xffff)
		वापस -EINVAL;

	ret = rdma_set_cq_moderation(priv->recv_cq,
				     coal->rx_max_coalesced_frames,
				     coal->rx_coalesce_usecs);
	अगर (ret && ret != -EOPNOTSUPP) अणु
		ipoib_warn(priv, "failed modifying CQ (%d)\n", ret);
		वापस ret;
	पूर्ण

	priv->ethtool.coalesce_usecs       = coal->rx_coalesce_usecs;
	priv->ethtool.max_coalesced_frames = coal->rx_max_coalesced_frames;

	वापस 0;
पूर्ण
अटल व्योम ipoib_get_ethtool_stats(काष्ठा net_device *dev,
				    काष्ठा ethtool_stats __always_unused *stats,
				    u64 *data)
अणु
	पूर्णांक i;
	काष्ठा net_device_stats *net_stats = &dev->stats;
	u8 *p = (u8 *)net_stats;

	क्रम (i = 0; i < IPOIB_GLOBAL_STATS_LEN; i++)
		data[i] = *(u64 *)(p + ipoib_gstrings_stats[i].stat_offset);

पूर्ण
अटल व्योम ipoib_get_strings(काष्ठा net_device __always_unused *dev,
			      u32 stringset, u8 *data)
अणु
	u8 *p = data;
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < IPOIB_GLOBAL_STATS_LEN; i++) अणु
			स_नकल(p, ipoib_gstrings_stats[i].stat_string,
				ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
अटल पूर्णांक ipoib_get_sset_count(काष्ठा net_device __always_unused *dev,
				 पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस IPOIB_GLOBAL_STATS_LEN;
	शेष:
		अवरोध;
	पूर्ण
	वापस -EOPNOTSUPP;
पूर्ण

/* Return lane speed in unit of 1e6 bit/sec */
अटल अंतरभूत पूर्णांक ib_speed_क्रमागत_to_पूर्णांक(पूर्णांक speed)
अणु
	चयन (speed) अणु
	हाल IB_SPEED_SDR:
		वापस SPEED_2500;
	हाल IB_SPEED_DDR:
		वापस SPEED_5000;
	हाल IB_SPEED_QDR:
	हाल IB_SPEED_FDR10:
		वापस SPEED_10000;
	हाल IB_SPEED_FDR:
		वापस SPEED_14000;
	हाल IB_SPEED_EDR:
		वापस SPEED_25000;
	हाल IB_SPEED_HDR:
		वापस SPEED_50000;
	हाल IB_SPEED_NDR:
		वापस SPEED_100000;
	पूर्ण

	वापस SPEED_UNKNOWN;
पूर्ण

अटल पूर्णांक ipoib_get_link_ksettings(काष्ठा net_device *netdev,
				    काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(netdev);
	काष्ठा ib_port_attr attr;
	पूर्णांक ret, speed, width;

	अगर (!netअगर_carrier_ok(netdev)) अणु
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
		वापस 0;
	पूर्ण

	ret = ib_query_port(priv->ca, priv->port, &attr);
	अगर (ret < 0)
		वापस -EINVAL;

	speed = ib_speed_क्रमागत_to_पूर्णांक(attr.active_speed);
	width = ib_width_क्रमागत_to_पूर्णांक(attr.active_width);

	अगर (speed < 0 || width < 0)
		वापस -EINVAL;

	/* Except the following are set, the other members of
	 * the काष्ठा ethtool_link_settings are initialized to
	 * zero in the function __ethtool_get_link_ksettings.
	 */
	cmd->base.speed		 = speed * width;
	cmd->base.duplex	 = DUPLEX_FULL;

	cmd->base.phy_address	 = 0xFF;

	cmd->base.स्वतःneg	 = AUTONEG_ENABLE;
	cmd->base.port		 = PORT_OTHER;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ipoib_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_RX_USECS |
				     ETHTOOL_COALESCE_RX_MAX_FRAMES,
	.get_link_ksettings	= ipoib_get_link_ksettings,
	.get_drvinfo		= ipoib_get_drvinfo,
	.get_coalesce		= ipoib_get_coalesce,
	.set_coalesce		= ipoib_set_coalesce,
	.get_strings		= ipoib_get_strings,
	.get_ethtool_stats	= ipoib_get_ethtool_stats,
	.get_sset_count		= ipoib_get_sset_count,
	.get_link		= ethtool_op_get_link,
पूर्ण;

व्योम ipoib_set_ethtool_ops(काष्ठा net_device *dev)
अणु
	dev->ethtool_ops = &ipoib_ethtool_ops;
पूर्ण
