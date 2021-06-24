<शैली गुरु>
/* Synopsys DesignWare Core Enterprise Ethernet (XLGMAC) Driver
 *
 * Copyright (c) 2017 Synopsys, Inc. (www.synopsys.com)
 *
 * This program is dual-licensed; you may select either version 2 of
 * the GNU General Public License ("GPL") or BSD license ("BSD").
 *
 * This Synopsys DWC XLGMAC software driver and associated करोcumentation
 * (hereinafter the "Software") is an unsupported proprietary work of
 * Synopsys, Inc. unless otherwise expressly agreed to in writing between
 * Synopsys and you. The Software IS NOT an item of Licensed Software or a
 * Licensed Product under any End User Software License Agreement or
 * Agreement क्रम Licensed Products with Synopsys or any supplement thereto.
 * Synopsys is a रेजिस्टरed trademark of Synopsys, Inc. Other names included
 * in the SOFTWARE may be the trademarks of their respective owners.
 */

#समावेश <linux/ethtool.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>

#समावेश "dwc-xlgmac.h"
#समावेश "dwc-xlgmac-reg.h"

काष्ठा xlgmac_stats_desc अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक stat_offset;
पूर्ण;

#घोषणा XLGMAC_STAT(str, var)					\
	अणु							\
		str,						\
		दुरत्व(काष्ठा xlgmac_pdata, stats.var),	\
	पूर्ण

अटल स्थिर काष्ठा xlgmac_stats_desc xlgmac_gstring_stats[] = अणु
	/* MMC TX counters */
	XLGMAC_STAT("tx_bytes", txoctetcount_gb),
	XLGMAC_STAT("tx_bytes_good", txoctetcount_g),
	XLGMAC_STAT("tx_packets", txframecount_gb),
	XLGMAC_STAT("tx_packets_good", txframecount_g),
	XLGMAC_STAT("tx_unicast_packets", txunicastframes_gb),
	XLGMAC_STAT("tx_broadcast_packets", txbroadcastframes_gb),
	XLGMAC_STAT("tx_broadcast_packets_good", txbroadcastframes_g),
	XLGMAC_STAT("tx_multicast_packets", txmulticastframes_gb),
	XLGMAC_STAT("tx_multicast_packets_good", txmulticastframes_g),
	XLGMAC_STAT("tx_vlan_packets_good", txvlanframes_g),
	XLGMAC_STAT("tx_64_byte_packets", tx64octets_gb),
	XLGMAC_STAT("tx_65_to_127_byte_packets", tx65to127octets_gb),
	XLGMAC_STAT("tx_128_to_255_byte_packets", tx128to255octets_gb),
	XLGMAC_STAT("tx_256_to_511_byte_packets", tx256to511octets_gb),
	XLGMAC_STAT("tx_512_to_1023_byte_packets", tx512to1023octets_gb),
	XLGMAC_STAT("tx_1024_to_max_byte_packets", tx1024tomaxoctets_gb),
	XLGMAC_STAT("tx_underflow_errors", txunderflowerror),
	XLGMAC_STAT("tx_pause_frames", txछोड़ोframes),

	/* MMC RX counters */
	XLGMAC_STAT("rx_bytes", rxoctetcount_gb),
	XLGMAC_STAT("rx_bytes_good", rxoctetcount_g),
	XLGMAC_STAT("rx_packets", rxframecount_gb),
	XLGMAC_STAT("rx_unicast_packets_good", rxunicastframes_g),
	XLGMAC_STAT("rx_broadcast_packets_good", rxbroadcastframes_g),
	XLGMAC_STAT("rx_multicast_packets_good", rxmulticastframes_g),
	XLGMAC_STAT("rx_vlan_packets", rxvlanframes_gb),
	XLGMAC_STAT("rx_64_byte_packets", rx64octets_gb),
	XLGMAC_STAT("rx_65_to_127_byte_packets", rx65to127octets_gb),
	XLGMAC_STAT("rx_128_to_255_byte_packets", rx128to255octets_gb),
	XLGMAC_STAT("rx_256_to_511_byte_packets", rx256to511octets_gb),
	XLGMAC_STAT("rx_512_to_1023_byte_packets", rx512to1023octets_gb),
	XLGMAC_STAT("rx_1024_to_max_byte_packets", rx1024tomaxoctets_gb),
	XLGMAC_STAT("rx_undersize_packets_good", rxundersize_g),
	XLGMAC_STAT("rx_oversize_packets_good", rxoversize_g),
	XLGMAC_STAT("rx_crc_errors", rxcrcerror),
	XLGMAC_STAT("rx_crc_errors_small_packets", rxrunterror),
	XLGMAC_STAT("rx_crc_errors_giant_packets", rxjabbererror),
	XLGMAC_STAT("rx_length_errors", rxlengtherror),
	XLGMAC_STAT("rx_out_of_range_errors", rxoutofrangetype),
	XLGMAC_STAT("rx_fifo_overflow_errors", rxfअगरooverflow),
	XLGMAC_STAT("rx_watchdog_errors", rxwatchकरोgerror),
	XLGMAC_STAT("rx_pause_frames", rxछोड़ोframes),

	/* Extra counters */
	XLGMAC_STAT("tx_tso_packets", tx_tso_packets),
	XLGMAC_STAT("rx_split_header_packets", rx_split_header_packets),
	XLGMAC_STAT("tx_process_stopped", tx_process_stopped),
	XLGMAC_STAT("rx_process_stopped", rx_process_stopped),
	XLGMAC_STAT("tx_buffer_unavailable", tx_buffer_unavailable),
	XLGMAC_STAT("rx_buffer_unavailable", rx_buffer_unavailable),
	XLGMAC_STAT("fatal_bus_error", fatal_bus_error),
	XLGMAC_STAT("tx_vlan_packets", tx_vlan_packets),
	XLGMAC_STAT("rx_vlan_packets", rx_vlan_packets),
	XLGMAC_STAT("napi_poll_isr", napi_poll_isr),
	XLGMAC_STAT("napi_poll_txtimer", napi_poll_txसमयr),
पूर्ण;

#घोषणा XLGMAC_STATS_COUNT	ARRAY_SIZE(xlgmac_gstring_stats)

अटल व्योम xlgmac_ethtool_get_drvinfo(काष्ठा net_device *netdev,
				       काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा xlgmac_pdata *pdata = netdev_priv(netdev);
	u32 ver = pdata->hw_feat.version;
	u32 snpsver, devid, userver;

	strlcpy(drvinfo->driver, pdata->drv_name, माप(drvinfo->driver));
	strlcpy(drvinfo->version, pdata->drv_ver, माप(drvinfo->version));
	strlcpy(drvinfo->bus_info, dev_name(pdata->dev),
		माप(drvinfo->bus_info));
	/* S|SNPSVER: Synopsys-defined Version
	 * D|DEVID: Indicates the Device family
	 * U|USERVER: User-defined Version
	 */
	snpsver = XLGMAC_GET_REG_BITS(ver, MAC_VR_SNPSVER_POS,
				      MAC_VR_SNPSVER_LEN);
	devid = XLGMAC_GET_REG_BITS(ver, MAC_VR_DEVID_POS,
				    MAC_VR_DEVID_LEN);
	userver = XLGMAC_GET_REG_BITS(ver, MAC_VR_USERVER_POS,
				      MAC_VR_USERVER_LEN);
	snम_लिखो(drvinfo->fw_version, माप(drvinfo->fw_version),
		 "S.D.U: %x.%x.%x", snpsver, devid, userver);
पूर्ण

अटल u32 xlgmac_ethtool_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा xlgmac_pdata *pdata = netdev_priv(netdev);

	वापस pdata->msg_enable;
पूर्ण

अटल व्योम xlgmac_ethtool_set_msglevel(काष्ठा net_device *netdev,
					u32 msglevel)
अणु
	काष्ठा xlgmac_pdata *pdata = netdev_priv(netdev);

	pdata->msg_enable = msglevel;
पूर्ण

अटल व्योम xlgmac_ethtool_get_channels(काष्ठा net_device *netdev,
					काष्ठा ethtool_channels *channel)
अणु
	काष्ठा xlgmac_pdata *pdata = netdev_priv(netdev);

	channel->max_rx = XLGMAC_MAX_DMA_CHANNELS;
	channel->max_tx = XLGMAC_MAX_DMA_CHANNELS;
	channel->rx_count = pdata->rx_q_count;
	channel->tx_count = pdata->tx_q_count;
पूर्ण

अटल पूर्णांक xlgmac_ethtool_get_coalesce(काष्ठा net_device *netdev,
				       काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा xlgmac_pdata *pdata = netdev_priv(netdev);

	ec->rx_coalesce_usecs = pdata->rx_usecs;
	ec->rx_max_coalesced_frames = pdata->rx_frames;
	ec->tx_max_coalesced_frames = pdata->tx_frames;

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_ethtool_set_coalesce(काष्ठा net_device *netdev,
				       काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा xlgmac_pdata *pdata = netdev_priv(netdev);
	काष्ठा xlgmac_hw_ops *hw_ops = &pdata->hw_ops;
	अचिन्हित पूर्णांक rx_frames, rx_riwt, rx_usecs;
	अचिन्हित पूर्णांक tx_frames;

	rx_usecs = ec->rx_coalesce_usecs;
	rx_riwt = hw_ops->usec_to_riwt(pdata, rx_usecs);
	rx_frames = ec->rx_max_coalesced_frames;
	tx_frames = ec->tx_max_coalesced_frames;

	अगर ((rx_riwt > XLGMAC_MAX_DMA_RIWT) ||
	    (rx_riwt < XLGMAC_MIN_DMA_RIWT) ||
	    (rx_frames > pdata->rx_desc_count))
		वापस -EINVAL;

	अगर (tx_frames > pdata->tx_desc_count)
		वापस -EINVAL;

	pdata->rx_riwt = rx_riwt;
	pdata->rx_usecs = rx_usecs;
	pdata->rx_frames = rx_frames;
	hw_ops->config_rx_coalesce(pdata);

	pdata->tx_frames = tx_frames;
	hw_ops->config_tx_coalesce(pdata);

	वापस 0;
पूर्ण

अटल व्योम xlgmac_ethtool_get_strings(काष्ठा net_device *netdev,
				       u32 stringset, u8 *data)
अणु
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < XLGMAC_STATS_COUNT; i++) अणु
			स_नकल(data, xlgmac_gstring_stats[i].stat_string,
			       ETH_GSTRING_LEN);
			data += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक xlgmac_ethtool_get_sset_count(काष्ठा net_device *netdev,
					 पूर्णांक stringset)
अणु
	पूर्णांक ret;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		ret = XLGMAC_STATS_COUNT;
		अवरोध;

	शेष:
		ret = -EOPNOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम xlgmac_ethtool_get_ethtool_stats(काष्ठा net_device *netdev,
					     काष्ठा ethtool_stats *stats,
					     u64 *data)
अणु
	काष्ठा xlgmac_pdata *pdata = netdev_priv(netdev);
	u8 *stat;
	पूर्णांक i;

	pdata->hw_ops.पढ़ो_mmc_stats(pdata);
	क्रम (i = 0; i < XLGMAC_STATS_COUNT; i++) अणु
		stat = (u8 *)pdata + xlgmac_gstring_stats[i].stat_offset;
		*data++ = *(u64 *)stat;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ethtool_ops xlgmac_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_RX_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES,
	.get_drvinfo = xlgmac_ethtool_get_drvinfo,
	.get_link = ethtool_op_get_link,
	.get_msglevel = xlgmac_ethtool_get_msglevel,
	.set_msglevel = xlgmac_ethtool_set_msglevel,
	.get_channels = xlgmac_ethtool_get_channels,
	.get_coalesce = xlgmac_ethtool_get_coalesce,
	.set_coalesce = xlgmac_ethtool_set_coalesce,
	.get_strings = xlgmac_ethtool_get_strings,
	.get_sset_count = xlgmac_ethtool_get_sset_count,
	.get_ethtool_stats = xlgmac_ethtool_get_ethtool_stats,
पूर्ण;

स्थिर काष्ठा ethtool_ops *xlgmac_get_ethtool_ops(व्योम)
अणु
	वापस &xlgmac_ethtool_ops;
पूर्ण
