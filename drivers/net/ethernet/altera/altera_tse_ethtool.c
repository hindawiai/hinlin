<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Ethtool support क्रम Altera Triple-Speed Ethernet MAC driver
 * Copyright (C) 2008-2014 Altera Corporation. All rights reserved
 *
 * Contributors:
 *   Dalon Westergreen
 *   Thomas Chou
 *   Ian Abbott
 *   Yuriy Kozlov
 *   Tobias Klauser
 *   Andriy Smolskyy
 *   Roman Bulgakov
 *   Dmytro Mytarchuk
 *
 * Original driver contributed by SLS.
 * Major updates contributed by GlobalLogic
 */

#समावेश <linux/ethtool.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/phy.h>

#समावेश "altera_tse.h"

#घोषणा TSE_STATS_LEN	31
#घोषणा TSE_NUM_REGS	128

अटल अक्षर स्थिर stat_gstrings[][ETH_GSTRING_LEN] = अणु
	"tx_packets",
	"rx_packets",
	"rx_crc_errors",
	"rx_align_errors",
	"tx_bytes",
	"rx_bytes",
	"tx_pause",
	"rx_pause",
	"rx_errors",
	"tx_errors",
	"rx_unicast",
	"rx_multicast",
	"rx_broadcast",
	"tx_discards",
	"tx_unicast",
	"tx_multicast",
	"tx_broadcast",
	"ether_drops",
	"rx_total_bytes",
	"rx_total_packets",
	"rx_undersize",
	"rx_oversize",
	"rx_64_bytes",
	"rx_65_127_bytes",
	"rx_128_255_bytes",
	"rx_256_511_bytes",
	"rx_512_1023_bytes",
	"rx_1024_1518_bytes",
	"rx_gte_1519_bytes",
	"rx_jabbers",
	"rx_runts",
पूर्ण;

अटल व्योम tse_get_drvinfo(काष्ठा net_device *dev,
			    काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा altera_tse_निजी *priv = netdev_priv(dev);
	u32 rev = ioपढ़ो32(&priv->mac_dev->megacore_revision);

	म_नकल(info->driver, "altera_tse");
	snम_लिखो(info->fw_version, ETHTOOL_FWVERS_LEN, "v%d.%d",
		 rev & 0xFFFF, (rev & 0xFFFF0000) >> 16);
	प्र_लिखो(info->bus_info, "platform");
पूर्ण

/* Fill in a buffer with the strings which correspond to the
 * stats
 */
अटल व्योम tse_gstrings(काष्ठा net_device *dev, u32 stringset, u8 *buf)
अणु
	स_नकल(buf, stat_gstrings, TSE_STATS_LEN * ETH_GSTRING_LEN);
पूर्ण

अटल व्योम tse_fill_stats(काष्ठा net_device *dev, काष्ठा ethtool_stats *dummy,
			   u64 *buf)
अणु
	काष्ठा altera_tse_निजी *priv = netdev_priv(dev);
	u64 ext;

	buf[0] = csrrd32(priv->mac_dev,
			 tse_csroffs(frames_transmitted_ok));
	buf[1] = csrrd32(priv->mac_dev,
			 tse_csroffs(frames_received_ok));
	buf[2] = csrrd32(priv->mac_dev,
			 tse_csroffs(frames_check_sequence_errors));
	buf[3] = csrrd32(priv->mac_dev,
			 tse_csroffs(alignment_errors));

	/* Extended aOctetsTransmittedOK counter */
	ext = (u64) csrrd32(priv->mac_dev,
			    tse_csroffs(msb_octets_transmitted_ok)) << 32;

	ext |= csrrd32(priv->mac_dev,
		       tse_csroffs(octets_transmitted_ok));
	buf[4] = ext;

	/* Extended aOctetsReceivedOK counter */
	ext = (u64) csrrd32(priv->mac_dev,
			    tse_csroffs(msb_octets_received_ok)) << 32;

	ext |= csrrd32(priv->mac_dev,
		       tse_csroffs(octets_received_ok));
	buf[5] = ext;

	buf[6] = csrrd32(priv->mac_dev,
			 tse_csroffs(tx_छोड़ो_mac_ctrl_frames));
	buf[7] = csrrd32(priv->mac_dev,
			 tse_csroffs(rx_छोड़ो_mac_ctrl_frames));
	buf[8] = csrrd32(priv->mac_dev,
			 tse_csroffs(अगर_in_errors));
	buf[9] = csrrd32(priv->mac_dev,
			 tse_csroffs(अगर_out_errors));
	buf[10] = csrrd32(priv->mac_dev,
			  tse_csroffs(अगर_in_ucast_pkts));
	buf[11] = csrrd32(priv->mac_dev,
			  tse_csroffs(अगर_in_multicast_pkts));
	buf[12] = csrrd32(priv->mac_dev,
			  tse_csroffs(अगर_in_broadcast_pkts));
	buf[13] = csrrd32(priv->mac_dev,
			  tse_csroffs(अगर_out_discards));
	buf[14] = csrrd32(priv->mac_dev,
			  tse_csroffs(अगर_out_ucast_pkts));
	buf[15] = csrrd32(priv->mac_dev,
			  tse_csroffs(अगर_out_multicast_pkts));
	buf[16] = csrrd32(priv->mac_dev,
			  tse_csroffs(अगर_out_broadcast_pkts));
	buf[17] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_drop_events));

	/* Extended etherStatsOctets counter */
	ext = (u64) csrrd32(priv->mac_dev,
			    tse_csroffs(msb_ether_stats_octets)) << 32;
	ext |= csrrd32(priv->mac_dev,
		       tse_csroffs(ether_stats_octets));
	buf[18] = ext;

	buf[19] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_pkts));
	buf[20] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_undersize_pkts));
	buf[21] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_oversize_pkts));
	buf[22] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_pkts_64_octets));
	buf[23] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_pkts_65to127_octets));
	buf[24] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_pkts_128to255_octets));
	buf[25] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_pkts_256to511_octets));
	buf[26] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_pkts_512to1023_octets));
	buf[27] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_pkts_1024to1518_octets));
	buf[28] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_pkts_1519tox_octets));
	buf[29] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_jabbers));
	buf[30] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_fragments));
पूर्ण

अटल पूर्णांक tse_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस TSE_STATS_LEN;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल u32 tse_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा altera_tse_निजी *priv = netdev_priv(dev);
	वापस priv->msg_enable;
पूर्ण

अटल व्योम tse_set_msglevel(काष्ठा net_device *dev, uपूर्णांक32_t data)
अणु
	काष्ठा altera_tse_निजी *priv = netdev_priv(dev);
	priv->msg_enable = data;
पूर्ण

अटल पूर्णांक tse_reglen(काष्ठा net_device *dev)
अणु
	वापस TSE_NUM_REGS * माप(u32);
पूर्ण

अटल व्योम tse_get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs,
			 व्योम *regbuf)
अणु
	पूर्णांक i;
	काष्ठा altera_tse_निजी *priv = netdev_priv(dev);
	u32 *buf = regbuf;

	/* Set version to a known value, so ethtool knows
	 * how to करो any special क्रमmatting of this data.
	 * This version number will need to change अगर and
	 * when this रेजिस्टर table is changed.
	 *
	 * version[31:0] = 1: Dump the first 128 TSE Registers
	 *      Upper bits are all 0 by शेष
	 *
	 * Upper 16-bits will indicate feature presence क्रम
	 * Ethtool रेजिस्टर decoding in future version.
	 */

	regs->version = 1;

	क्रम (i = 0; i < TSE_NUM_REGS; i++)
		buf[i] = csrrd32(priv->mac_dev, i * 4);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops tse_ethtool_ops = अणु
	.get_drvinfo = tse_get_drvinfo,
	.get_regs_len = tse_reglen,
	.get_regs = tse_get_regs,
	.get_link = ethtool_op_get_link,
	.get_strings = tse_gstrings,
	.get_sset_count = tse_sset_count,
	.get_ethtool_stats = tse_fill_stats,
	.get_msglevel = tse_get_msglevel,
	.set_msglevel = tse_set_msglevel,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
पूर्ण;

व्योम altera_tse_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &tse_ethtool_ops;
पूर्ण
