<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005 - 2016 Broadcom
 * All rights reserved.
 *
 * Contact Inक्रमmation:
 * linux-drivers@emulex.com
 *
 * Emulex
 * 3333 Susan Street
 * Costa Mesa, CA 92626
 */

#समावेश "be.h"
#समावेश "be_cmds.h"
#समावेश <linux/ethtool.h>

काष्ठा be_ethtool_stat अणु
	अक्षर desc[ETH_GSTRING_LEN];
	पूर्णांक type;
	पूर्णांक size;
	पूर्णांक offset;
पूर्ण;

क्रमागत अणुDRVSTAT_TX, DRVSTAT_RX, DRVSTATपूर्ण;
#घोषणा FIELDINFO(_काष्ठा, field) माप_field(_काष्ठा, field), \
					दुरत्व(_काष्ठा, field)
#घोषणा DRVSTAT_TX_INFO(field)	#field, DRVSTAT_TX,\
					FIELDINFO(काष्ठा be_tx_stats, field)
#घोषणा DRVSTAT_RX_INFO(field)	#field, DRVSTAT_RX,\
					FIELDINFO(काष्ठा be_rx_stats, field)
#घोषणा	DRVSTAT_INFO(field)	#field, DRVSTAT,\
					FIELDINFO(काष्ठा be_drv_stats, field)

अटल स्थिर काष्ठा be_ethtool_stat et_stats[] = अणु
	अणुDRVSTAT_INFO(rx_crc_errors)पूर्ण,
	अणुDRVSTAT_INFO(rx_alignment_symbol_errors)पूर्ण,
	अणुDRVSTAT_INFO(rx_छोड़ो_frames)पूर्ण,
	अणुDRVSTAT_INFO(rx_control_frames)पूर्ण,
	/* Received packets dropped when the Ethernet length field
	 * is not equal to the actual Ethernet data length.
	 */
	अणुDRVSTAT_INFO(rx_in_range_errors)पूर्ण,
	/* Received packets dropped when their length field is >= 1501 bytes
	 * and <= 1535 bytes.
	 */
	अणुDRVSTAT_INFO(rx_out_range_errors)पूर्ण,
	/* Received packets dropped when they are दीर्घer than 9216 bytes */
	अणुDRVSTAT_INFO(rx_frame_too_दीर्घ)पूर्ण,
	/* Received packets dropped when they करोn't pass the unicast or
	 * multicast address filtering.
	 */
	अणुDRVSTAT_INFO(rx_address_filtered)पूर्ण,
	/* Received packets dropped when IP packet length field is less than
	 * the IP header length field.
	 */
	अणुDRVSTAT_INFO(rx_dropped_too_small)पूर्ण,
	/* Received packets dropped when IP length field is greater than
	 * the actual packet length.
	 */
	अणुDRVSTAT_INFO(rx_dropped_too_लघु)पूर्ण,
	/* Received packets dropped when the IP header length field is less
	 * than 5.
	 */
	अणुDRVSTAT_INFO(rx_dropped_header_too_small)पूर्ण,
	/* Received packets dropped when the TCP header length field is less
	 * than 5 or the TCP header length + IP header length is more
	 * than IP packet length.
	 */
	अणुDRVSTAT_INFO(rx_dropped_tcp_length)पूर्ण,
	अणुDRVSTAT_INFO(rx_dropped_runt)पूर्ण,
	/* Number of received packets dropped when a fअगरo क्रम descriptors going
	 * पूर्णांकo the packet demux block overflows. In normal operation, this
	 * fअगरo must never overflow.
	 */
	अणुDRVSTAT_INFO(rxpp_fअगरo_overflow_drop)पूर्ण,
	/* Received packets dropped when the RX block runs out of space in
	 * one of its input FIFOs. This could happen due a दीर्घ burst of
	 * minimum-sized (64b) frames in the receive path.
	 * This counter may also be erroneously incremented rarely.
	 */
	अणुDRVSTAT_INFO(rx_input_fअगरo_overflow_drop)पूर्ण,
	अणुDRVSTAT_INFO(rx_ip_checksum_errs)पूर्ण,
	अणुDRVSTAT_INFO(rx_tcp_checksum_errs)पूर्ण,
	अणुDRVSTAT_INFO(rx_udp_checksum_errs)पूर्ण,
	अणुDRVSTAT_INFO(tx_छोड़ोframes)पूर्ण,
	अणुDRVSTAT_INFO(tx_controlframes)पूर्ण,
	अणुDRVSTAT_INFO(rx_priority_छोड़ो_frames)पूर्ण,
	अणुDRVSTAT_INFO(tx_priority_छोड़ोframes)पूर्ण,
	/* Received packets dropped when an पूर्णांकernal fअगरo going पूर्णांकo
	 * मुख्य packet buffer tank (PMEM) overflows.
	 */
	अणुDRVSTAT_INFO(pmem_fअगरo_overflow_drop)पूर्ण,
	अणुDRVSTAT_INFO(jabber_events)पूर्ण,
	/* Received packets dropped due to lack of available HW packet buffers
	 * used to temporarily hold the received packets.
	 */
	अणुDRVSTAT_INFO(rx_drops_no_pbuf)पूर्ण,
	/* Received packets dropped due to input receive buffer
	 * descriptor fअगरo overflowing.
	 */
	अणुDRVSTAT_INFO(rx_drops_no_erx_descr)पूर्ण,
	/* Packets dropped because the पूर्णांकernal FIFO to the offloaded TCP
	 * receive processing block is full. This could happen only क्रम
	 * offloaded iSCSI or FCoE trarffic.
	 */
	अणुDRVSTAT_INFO(rx_drops_no_tpre_descr)पूर्ण,
	/* Received packets dropped when they need more than 8
	 * receive buffers. This cannot happen as the driver configures
	 * 2048 byte receive buffers.
	 */
	अणुDRVSTAT_INFO(rx_drops_too_many_frags)पूर्ण,
	अणुDRVSTAT_INFO(क्रमwarded_packets)पूर्ण,
	/* Received packets dropped when the frame length
	 * is more than 9018 bytes
	 */
	अणुDRVSTAT_INFO(rx_drops_mtu)पूर्ण,
	/* Number of dma mapping errors */
	अणुDRVSTAT_INFO(dma_map_errors)पूर्ण,
	/* Number of packets dropped due to अक्रमom early drop function */
	अणुDRVSTAT_INFO(eth_red_drops)पूर्ण,
	अणुDRVSTAT_INFO(rx_roce_bytes_lsd)पूर्ण,
	अणुDRVSTAT_INFO(rx_roce_bytes_msd)पूर्ण,
	अणुDRVSTAT_INFO(rx_roce_frames)पूर्ण,
	अणुDRVSTAT_INFO(roce_drops_payload_len)पूर्ण,
	अणुDRVSTAT_INFO(roce_drops_crc)पूर्ण
पूर्ण;

#घोषणा ETHTOOL_STATS_NUM ARRAY_SIZE(et_stats)

/* Stats related to multi RX queues: get_stats routine assumes bytes, pkts
 * are first and second members respectively.
 */
अटल स्थिर काष्ठा be_ethtool_stat et_rx_stats[] = अणु
	अणुDRVSTAT_RX_INFO(rx_bytes)पूर्ण,/* If moving this member see above note */
	अणुDRVSTAT_RX_INFO(rx_pkts)पूर्ण, /* If moving this member see above note */
	अणुDRVSTAT_RX_INFO(rx_vxlan_offload_pkts)पूर्ण,
	अणुDRVSTAT_RX_INFO(rx_compl)पूर्ण,
	अणुDRVSTAT_RX_INFO(rx_compl_err)पूर्ण,
	अणुDRVSTAT_RX_INFO(rx_mcast_pkts)पूर्ण,
	/* Number of page allocation failures जबतक posting receive buffers
	 * to HW.
	 */
	अणुDRVSTAT_RX_INFO(rx_post_fail)पूर्ण,
	/* Recevied packets dropped due to skb allocation failure */
	अणुDRVSTAT_RX_INFO(rx_drops_no_skbs)पूर्ण,
	/* Received packets dropped due to lack of available fetched buffers
	 * posted by the driver.
	 */
	अणुDRVSTAT_RX_INFO(rx_drops_no_frags)पूर्ण
पूर्ण;

#घोषणा ETHTOOL_RXSTATS_NUM (ARRAY_SIZE(et_rx_stats))

/* Stats related to multi TX queues: get_stats routine assumes compl is the
 * first member
 */
अटल स्थिर काष्ठा be_ethtool_stat et_tx_stats[] = अणु
	अणुDRVSTAT_TX_INFO(tx_compl)पूर्ण, /* If moving this member see above note */
	/* This counter is incremented when the HW encounters an error जबतक
	 * parsing the packet header of an outgoing TX request. This counter is
	 * applicable only क्रम BE2, BE3 and Skyhawk based adapters.
	 */
	अणुDRVSTAT_TX_INFO(tx_hdr_parse_err)पूर्ण,
	/* This counter is incremented when an error occurs in the DMA
	 * operation associated with the TX request from the host to the device.
	 */
	अणुDRVSTAT_TX_INFO(tx_dma_err)पूर्ण,
	/* This counter is incremented when MAC or VLAN spoof checking is
	 * enabled on the पूर्णांकerface and the TX request fails the spoof check
	 * in HW.
	 */
	अणुDRVSTAT_TX_INFO(tx_spoof_check_err)पूर्ण,
	/* This counter is incremented when the HW encounters an error जबतक
	 * perक्रमming TSO offload. This counter is applicable only क्रम Lancer
	 * adapters.
	 */
	अणुDRVSTAT_TX_INFO(tx_tso_err)पूर्ण,
	/* This counter is incremented when the HW detects Q-in-Q style VLAN
	 * tagging in a packet and such tagging is not expected on the outgoing
	 * पूर्णांकerface. This counter is applicable only क्रम Lancer adapters.
	 */
	अणुDRVSTAT_TX_INFO(tx_qinq_err)पूर्ण,
	/* This counter is incremented when the HW detects parity errors in the
	 * packet data. This counter is applicable only क्रम Lancer adapters.
	 */
	अणुDRVSTAT_TX_INFO(tx_पूर्णांकernal_parity_err)पूर्ण,
	अणुDRVSTAT_TX_INFO(tx_sge_err)पूर्ण,
	अणुDRVSTAT_TX_INFO(tx_bytes)पूर्ण,
	अणुDRVSTAT_TX_INFO(tx_pkts)पूर्ण,
	अणुDRVSTAT_TX_INFO(tx_vxlan_offload_pkts)पूर्ण,
	/* Number of skbs queued क्रम trयंत्रission by the driver */
	अणुDRVSTAT_TX_INFO(tx_reqs)पूर्ण,
	/* Number of बार the TX queue was stopped due to lack
	 * of spaces in the TXQ.
	 */
	अणुDRVSTAT_TX_INFO(tx_stops)पूर्ण,
	/* Pkts dropped in the driver's transmit path */
	अणुDRVSTAT_TX_INFO(tx_drv_drops)पूर्ण
पूर्ण;

#घोषणा ETHTOOL_TXSTATS_NUM (ARRAY_SIZE(et_tx_stats))

अटल स्थिर अक्षर et_self_tests[][ETH_GSTRING_LEN] = अणु
	"MAC Loopback test",
	"PHY Loopback test",
	"External Loopback test",
	"DDR DMA test",
	"Link test"
पूर्ण;

#घोषणा ETHTOOL_TESTS_NUM ARRAY_SIZE(et_self_tests)
#घोषणा BE_MAC_LOOPBACK 0x0
#घोषणा BE_PHY_LOOPBACK 0x1
#घोषणा BE_ONE_PORT_EXT_LOOPBACK 0x2
#घोषणा BE_NO_LOOPBACK 0xff

अटल व्योम be_get_drvinfo(काष्ठा net_device *netdev,
			   काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);

	strlcpy(drvinfo->driver, DRV_NAME, माप(drvinfo->driver));
	अगर (!स_भेद(adapter->fw_ver, adapter->fw_on_flash, FW_VER_LEN))
		strlcpy(drvinfo->fw_version, adapter->fw_ver,
			माप(drvinfo->fw_version));
	अन्यथा
		snम_लिखो(drvinfo->fw_version, माप(drvinfo->fw_version),
			 "%s [%s]", adapter->fw_ver, adapter->fw_on_flash);

	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		माप(drvinfo->bus_info));
पूर्ण

अटल u32 lancer_cmd_get_file_len(काष्ठा be_adapter *adapter, u8 *file_name)
अणु
	u32 data_पढ़ो = 0, eof;
	u8 addn_status;
	काष्ठा be_dma_mem data_len_cmd;

	स_रखो(&data_len_cmd, 0, माप(data_len_cmd));
	/* data_offset and data_size should be 0 to get reg len */
	lancer_cmd_पढ़ो_object(adapter, &data_len_cmd, 0, 0, file_name,
			       &data_पढ़ो, &eof, &addn_status);

	वापस data_पढ़ो;
पूर्ण

अटल पूर्णांक be_get_dump_len(काष्ठा be_adapter *adapter)
अणु
	u32 dump_size = 0;

	अगर (lancer_chip(adapter))
		dump_size = lancer_cmd_get_file_len(adapter,
						    LANCER_FW_DUMP_खाता);
	अन्यथा
		dump_size = adapter->fat_dump_len;

	वापस dump_size;
पूर्ण

अटल पूर्णांक lancer_cmd_पढ़ो_file(काष्ठा be_adapter *adapter, u8 *file_name,
				u32 buf_len, व्योम *buf)
अणु
	काष्ठा be_dma_mem पढ़ो_cmd;
	u32 पढ़ो_len = 0, total_पढ़ो_len = 0, chunk_size;
	u32 eof = 0;
	u8 addn_status;
	पूर्णांक status = 0;

	पढ़ो_cmd.size = LANCER_READ_खाता_CHUNK;
	पढ़ो_cmd.va = dma_alloc_coherent(&adapter->pdev->dev, पढ़ो_cmd.size,
					 &पढ़ो_cmd.dma, GFP_ATOMIC);

	अगर (!पढ़ो_cmd.va) अणु
		dev_err(&adapter->pdev->dev,
			"Memory allocation failure while reading dump\n");
		वापस -ENOMEM;
	पूर्ण

	जबतक ((total_पढ़ो_len < buf_len) && !eof) अणु
		chunk_size = min_t(u32, (buf_len - total_पढ़ो_len),
				   LANCER_READ_खाता_CHUNK);
		chunk_size = ALIGN(chunk_size, 4);
		status = lancer_cmd_पढ़ो_object(adapter, &पढ़ो_cmd, chunk_size,
						total_पढ़ो_len, file_name,
						&पढ़ो_len, &eof, &addn_status);
		अगर (!status) अणु
			स_नकल(buf + total_पढ़ो_len, पढ़ो_cmd.va, पढ़ो_len);
			total_पढ़ो_len += पढ़ो_len;
			eof &= LANCER_READ_खाता_खातापूर्ण_MASK;
		पूर्ण अन्यथा अणु
			status = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण
	dma_मुक्त_coherent(&adapter->pdev->dev, पढ़ो_cmd.size, पढ़ो_cmd.va,
			  पढ़ो_cmd.dma);

	वापस status;
पूर्ण

अटल पूर्णांक be_पढ़ो_dump_data(काष्ठा be_adapter *adapter, u32 dump_len,
			     व्योम *buf)
अणु
	पूर्णांक status = 0;

	अगर (lancer_chip(adapter))
		status = lancer_cmd_पढ़ो_file(adapter, LANCER_FW_DUMP_खाता,
					      dump_len, buf);
	अन्यथा
		status = be_cmd_get_fat_dump(adapter, dump_len, buf);

	वापस status;
पूर्ण

अटल पूर्णांक be_get_coalesce(काष्ठा net_device *netdev,
			   काष्ठा ethtool_coalesce *et)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	काष्ठा be_aic_obj *aic = &adapter->aic_obj[0];

	et->rx_coalesce_usecs = aic->prev_eqd;
	et->rx_coalesce_usecs_high = aic->max_eqd;
	et->rx_coalesce_usecs_low = aic->min_eqd;

	et->tx_coalesce_usecs = aic->prev_eqd;
	et->tx_coalesce_usecs_high = aic->max_eqd;
	et->tx_coalesce_usecs_low = aic->min_eqd;

	et->use_adaptive_rx_coalesce = adapter->aic_enabled;
	et->use_adaptive_tx_coalesce = adapter->aic_enabled;

	वापस 0;
पूर्ण

/* TX attributes are ignored. Only RX attributes are considered
 * eqd cmd is issued in the worker thपढ़ो.
 */
अटल पूर्णांक be_set_coalesce(काष्ठा net_device *netdev,
			   काष्ठा ethtool_coalesce *et)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	काष्ठा be_aic_obj *aic = &adapter->aic_obj[0];
	काष्ठा be_eq_obj *eqo;
	पूर्णांक i;

	adapter->aic_enabled = et->use_adaptive_rx_coalesce;

	क्रम_all_evt_queues(adapter, eqo, i) अणु
		aic->max_eqd = min(et->rx_coalesce_usecs_high, BE_MAX_EQD);
		aic->min_eqd = min(et->rx_coalesce_usecs_low, aic->max_eqd);
		aic->et_eqd = min(et->rx_coalesce_usecs, aic->max_eqd);
		aic->et_eqd = max(aic->et_eqd, aic->min_eqd);
		aic++;
	पूर्ण

	/* For Skyhawk, the EQD setting happens via EQ_DB when AIC is enabled.
	 * When AIC is disabled, persistently क्रमce set EQD value via the
	 * FW cmd, so that we करोn't have to calculate the delay multiplier
	 * encode value each समय EQ_DB is rung
	 */
	अगर (!et->use_adaptive_rx_coalesce && skyhawk_chip(adapter))
		be_eqd_update(adapter, true);

	वापस 0;
पूर्ण

अटल व्योम be_get_ethtool_stats(काष्ठा net_device *netdev,
				 काष्ठा ethtool_stats *stats, uपूर्णांक64_t *data)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	काष्ठा be_rx_obj *rxo;
	काष्ठा be_tx_obj *txo;
	व्योम *p;
	अचिन्हित पूर्णांक i, j, base = 0, start;

	क्रम (i = 0; i < ETHTOOL_STATS_NUM; i++) अणु
		p = (u8 *)&adapter->drv_stats + et_stats[i].offset;
		data[i] = *(u32 *)p;
	पूर्ण
	base += ETHTOOL_STATS_NUM;

	क्रम_all_rx_queues(adapter, rxo, j) अणु
		काष्ठा be_rx_stats *stats = rx_stats(rxo);

		करो अणु
			start = u64_stats_fetch_begin_irq(&stats->sync);
			data[base] = stats->rx_bytes;
			data[base + 1] = stats->rx_pkts;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&stats->sync, start));

		क्रम (i = 2; i < ETHTOOL_RXSTATS_NUM; i++) अणु
			p = (u8 *)stats + et_rx_stats[i].offset;
			data[base + i] = *(u32 *)p;
		पूर्ण
		base += ETHTOOL_RXSTATS_NUM;
	पूर्ण

	क्रम_all_tx_queues(adapter, txo, j) अणु
		काष्ठा be_tx_stats *stats = tx_stats(txo);

		करो अणु
			start = u64_stats_fetch_begin_irq(&stats->sync_compl);
			data[base] = stats->tx_compl;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&stats->sync_compl, start));

		करो अणु
			start = u64_stats_fetch_begin_irq(&stats->sync);
			क्रम (i = 1; i < ETHTOOL_TXSTATS_NUM; i++) अणु
				p = (u8 *)stats + et_tx_stats[i].offset;
				data[base + i] =
					(et_tx_stats[i].size == माप(u64)) ?
						*(u64 *)p : *(u32 *)p;
			पूर्ण
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&stats->sync, start));
		base += ETHTOOL_TXSTATS_NUM;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर be_priv_flags[][ETH_GSTRING_LEN] = अणु
	"disable-tpe-recovery"
पूर्ण;

अटल व्योम be_get_stat_strings(काष्ठा net_device *netdev, uपूर्णांक32_t stringset,
				uपूर्णांक8_t *data)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	पूर्णांक i, j;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < ETHTOOL_STATS_NUM; i++) अणु
			स_नकल(data, et_stats[i].desc, ETH_GSTRING_LEN);
			data += ETH_GSTRING_LEN;
		पूर्ण
		क्रम (i = 0; i < adapter->num_rx_qs; i++) अणु
			क्रम (j = 0; j < ETHTOOL_RXSTATS_NUM; j++) अणु
				प्र_लिखो(data, "rxq%d: %s", i,
					et_rx_stats[j].desc);
				data += ETH_GSTRING_LEN;
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < adapter->num_tx_qs; i++) अणु
			क्रम (j = 0; j < ETHTOOL_TXSTATS_NUM; j++) अणु
				प्र_लिखो(data, "txq%d: %s", i,
					et_tx_stats[j].desc);
				data += ETH_GSTRING_LEN;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल ETH_SS_TEST:
		क्रम (i = 0; i < ETHTOOL_TESTS_NUM; i++) अणु
			स_नकल(data, et_self_tests[i], ETH_GSTRING_LEN);
			data += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	हाल ETH_SS_PRIV_FLAGS:
		क्रम (i = 0; i < ARRAY_SIZE(be_priv_flags); i++)
			म_नकल(data + i * ETH_GSTRING_LEN, be_priv_flags[i]);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक be_get_sset_count(काष्ठा net_device *netdev, पूर्णांक stringset)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);

	चयन (stringset) अणु
	हाल ETH_SS_TEST:
		वापस ETHTOOL_TESTS_NUM;
	हाल ETH_SS_STATS:
		वापस ETHTOOL_STATS_NUM +
			adapter->num_rx_qs * ETHTOOL_RXSTATS_NUM +
			adapter->num_tx_qs * ETHTOOL_TXSTATS_NUM;
	हाल ETH_SS_PRIV_FLAGS:
		वापस ARRAY_SIZE(be_priv_flags);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल u32 be_get_port_type(काष्ठा be_adapter *adapter)
अणु
	u32 port;

	चयन (adapter->phy.पूर्णांकerface_type) अणु
	हाल PHY_TYPE_BASET_1GB:
	हाल PHY_TYPE_BASEX_1GB:
	हाल PHY_TYPE_SGMII:
		port = PORT_TP;
		अवरोध;
	हाल PHY_TYPE_SFP_PLUS_10GB:
		अगर (adapter->phy.cable_type & SFP_PLUS_COPPER_CABLE)
			port = PORT_DA;
		अन्यथा
			port = PORT_FIBRE;
		अवरोध;
	हाल PHY_TYPE_QSFP:
		अगर (adapter->phy.cable_type & QSFP_PLUS_CR4_CABLE)
			port = PORT_DA;
		अन्यथा
			port = PORT_FIBRE;
		अवरोध;
	हाल PHY_TYPE_XFP_10GB:
	हाल PHY_TYPE_SFP_1GB:
		port = PORT_FIBRE;
		अवरोध;
	हाल PHY_TYPE_BASET_10GB:
		port = PORT_TP;
		अवरोध;
	शेष:
		port = PORT_OTHER;
	पूर्ण

	वापस port;
पूर्ण

अटल u32 convert_to_et_setting(काष्ठा be_adapter *adapter, u32 अगर_speeds)
अणु
	u32 val = 0;

	चयन (adapter->phy.पूर्णांकerface_type) अणु
	हाल PHY_TYPE_BASET_1GB:
	हाल PHY_TYPE_BASEX_1GB:
	हाल PHY_TYPE_SGMII:
		val |= SUPPORTED_TP;
		अगर (अगर_speeds & BE_SUPPORTED_SPEED_1GBPS)
			val |= SUPPORTED_1000baseT_Full;
		अगर (अगर_speeds & BE_SUPPORTED_SPEED_100MBPS)
			val |= SUPPORTED_100baseT_Full;
		अगर (अगर_speeds & BE_SUPPORTED_SPEED_10MBPS)
			val |= SUPPORTED_10baseT_Full;
		अवरोध;
	हाल PHY_TYPE_KX4_10GB:
		val |= SUPPORTED_Backplane;
		अगर (अगर_speeds & BE_SUPPORTED_SPEED_1GBPS)
			val |= SUPPORTED_1000baseKX_Full;
		अगर (अगर_speeds & BE_SUPPORTED_SPEED_10GBPS)
			val |= SUPPORTED_10000baseKX4_Full;
		अवरोध;
	हाल PHY_TYPE_KR2_20GB:
		val |= SUPPORTED_Backplane;
		अगर (अगर_speeds & BE_SUPPORTED_SPEED_10GBPS)
			val |= SUPPORTED_10000baseKR_Full;
		अगर (अगर_speeds & BE_SUPPORTED_SPEED_20GBPS)
			val |= SUPPORTED_20000baseKR2_Full;
		अवरोध;
	हाल PHY_TYPE_KR_10GB:
		val |= SUPPORTED_Backplane |
				SUPPORTED_10000baseKR_Full;
		अवरोध;
	हाल PHY_TYPE_KR4_40GB:
		val |= SUPPORTED_Backplane;
		अगर (अगर_speeds & BE_SUPPORTED_SPEED_10GBPS)
			val |= SUPPORTED_10000baseKR_Full;
		अगर (अगर_speeds & BE_SUPPORTED_SPEED_40GBPS)
			val |= SUPPORTED_40000baseKR4_Full;
		अवरोध;
	हाल PHY_TYPE_QSFP:
		अगर (अगर_speeds & BE_SUPPORTED_SPEED_40GBPS) अणु
			चयन (adapter->phy.cable_type) अणु
			हाल QSFP_PLUS_CR4_CABLE:
				val |= SUPPORTED_40000baseCR4_Full;
				अवरोध;
			हाल QSFP_PLUS_LR4_CABLE:
				val |= SUPPORTED_40000baseLR4_Full;
				अवरोध;
			शेष:
				val |= SUPPORTED_40000baseSR4_Full;
				अवरोध;
			पूर्ण
		पूर्ण
		fallthrough;
	हाल PHY_TYPE_SFP_PLUS_10GB:
	हाल PHY_TYPE_XFP_10GB:
	हाल PHY_TYPE_SFP_1GB:
		val |= SUPPORTED_FIBRE;
		अगर (अगर_speeds & BE_SUPPORTED_SPEED_10GBPS)
			val |= SUPPORTED_10000baseT_Full;
		अगर (अगर_speeds & BE_SUPPORTED_SPEED_1GBPS)
			val |= SUPPORTED_1000baseT_Full;
		अवरोध;
	हाल PHY_TYPE_BASET_10GB:
		val |= SUPPORTED_TP;
		अगर (अगर_speeds & BE_SUPPORTED_SPEED_10GBPS)
			val |= SUPPORTED_10000baseT_Full;
		अगर (अगर_speeds & BE_SUPPORTED_SPEED_1GBPS)
			val |= SUPPORTED_1000baseT_Full;
		अगर (अगर_speeds & BE_SUPPORTED_SPEED_100MBPS)
			val |= SUPPORTED_100baseT_Full;
		अवरोध;
	शेष:
		val |= SUPPORTED_TP;
	पूर्ण

	वापस val;
पूर्ण

bool be_छोड़ो_supported(काष्ठा be_adapter *adapter)
अणु
	वापस (adapter->phy.पूर्णांकerface_type == PHY_TYPE_SFP_PLUS_10GB ||
		adapter->phy.पूर्णांकerface_type == PHY_TYPE_XFP_10GB) ?
		false : true;
पूर्ण

अटल पूर्णांक be_get_link_ksettings(काष्ठा net_device *netdev,
				 काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	u8 link_status;
	u16 link_speed = 0;
	पूर्णांक status;
	u32 स्वतः_speeds;
	u32 fixed_speeds;
	u32 supported = 0, advertising = 0;

	अगर (adapter->phy.link_speed < 0) अणु
		status = be_cmd_link_status_query(adapter, &link_speed,
						  &link_status, 0);
		अगर (!status)
			be_link_status_update(adapter, link_status);
		cmd->base.speed = link_speed;

		status = be_cmd_get_phy_info(adapter);
		अगर (!status) अणु
			स्वतः_speeds = adapter->phy.स्वतः_speeds_supported;
			fixed_speeds = adapter->phy.fixed_speeds_supported;

			be_cmd_query_cable_type(adapter);

			supported =
				convert_to_et_setting(adapter,
						      स्वतः_speeds |
						      fixed_speeds);
			advertising =
				convert_to_et_setting(adapter, स्वतः_speeds);

			cmd->base.port = be_get_port_type(adapter);

			अगर (adapter->phy.स्वतः_speeds_supported) अणु
				supported |= SUPPORTED_Autoneg;
				cmd->base.स्वतःneg = AUTONEG_ENABLE;
				advertising |= ADVERTISED_Autoneg;
			पूर्ण

			supported |= SUPPORTED_Pause;
			अगर (be_छोड़ो_supported(adapter))
				advertising |= ADVERTISED_Pause;
		पूर्ण अन्यथा अणु
			cmd->base.port = PORT_OTHER;
			cmd->base.स्वतःneg = AUTONEG_DISABLE;
		पूर्ण

		/* Save क्रम future use */
		adapter->phy.link_speed = cmd->base.speed;
		adapter->phy.port_type = cmd->base.port;
		adapter->phy.स्वतःneg = cmd->base.स्वतःneg;
		adapter->phy.advertising = advertising;
		adapter->phy.supported = supported;
	पूर्ण अन्यथा अणु
		cmd->base.speed = adapter->phy.link_speed;
		cmd->base.port = adapter->phy.port_type;
		cmd->base.स्वतःneg = adapter->phy.स्वतःneg;
		advertising = adapter->phy.advertising;
		supported = adapter->phy.supported;
	पूर्ण

	cmd->base.duplex = netअगर_carrier_ok(netdev) ?
		DUPLEX_FULL : DUPLEX_UNKNOWN;
	cmd->base.phy_address = adapter->port_num;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल व्योम be_get_ringparam(काष्ठा net_device *netdev,
			     काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);

	ring->rx_max_pending = adapter->rx_obj[0].q.len;
	ring->rx_pending = adapter->rx_obj[0].q.len;
	ring->tx_max_pending = adapter->tx_obj[0].q.len;
	ring->tx_pending = adapter->tx_obj[0].q.len;
पूर्ण

अटल व्योम
be_get_छोड़ोparam(काष्ठा net_device *netdev, काष्ठा ethtool_छोड़ोparam *ecmd)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);

	be_cmd_get_flow_control(adapter, &ecmd->tx_छोड़ो, &ecmd->rx_छोड़ो);
	ecmd->स्वतःneg = adapter->phy.fc_स्वतःneg;
पूर्ण

अटल पूर्णांक
be_set_छोड़ोparam(काष्ठा net_device *netdev, काष्ठा ethtool_छोड़ोparam *ecmd)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	पूर्णांक status;

	अगर (ecmd->स्वतःneg != adapter->phy.fc_स्वतःneg)
		वापस -EINVAL;

	status = be_cmd_set_flow_control(adapter, ecmd->tx_छोड़ो,
					 ecmd->rx_छोड़ो);
	अगर (status) अणु
		dev_warn(&adapter->pdev->dev, "Pause param set failed\n");
		वापस be_cmd_status(status);
	पूर्ण

	adapter->tx_fc = ecmd->tx_छोड़ो;
	adapter->rx_fc = ecmd->rx_छोड़ो;
	वापस 0;
पूर्ण

अटल पूर्णांक be_set_phys_id(काष्ठा net_device *netdev,
			  क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	पूर्णांक status = 0;

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		status = be_cmd_get_beacon_state(adapter, adapter->hba_port_num,
						 &adapter->beacon_state);
		अगर (status)
			वापस be_cmd_status(status);
		वापस 1;       /* cycle on/off once per second */

	हाल ETHTOOL_ID_ON:
		status = be_cmd_set_beacon_state(adapter, adapter->hba_port_num,
						 0, 0, BEACON_STATE_ENABLED);
		अवरोध;

	हाल ETHTOOL_ID_OFF:
		status = be_cmd_set_beacon_state(adapter, adapter->hba_port_num,
						 0, 0, BEACON_STATE_DISABLED);
		अवरोध;

	हाल ETHTOOL_ID_INACTIVE:
		status = be_cmd_set_beacon_state(adapter, adapter->hba_port_num,
						 0, 0, adapter->beacon_state);
	पूर्ण

	वापस be_cmd_status(status);
पूर्ण

अटल पूर्णांक be_set_dump(काष्ठा net_device *netdev, काष्ठा ethtool_dump *dump)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	काष्ठा device *dev = &adapter->pdev->dev;
	पूर्णांक status;

	अगर (!lancer_chip(adapter) ||
	    !check_privilege(adapter, MAX_PRIVILEGES))
		वापस -EOPNOTSUPP;

	चयन (dump->flag) अणु
	हाल LANCER_INITIATE_FW_DUMP:
		status = lancer_initiate_dump(adapter);
		अगर (!status)
			dev_info(dev, "FW dump initiated successfully\n");
		अवरोध;
	हाल LANCER_DELETE_FW_DUMP:
		status = lancer_delete_dump(adapter);
		अगर (!status)
			dev_info(dev, "FW dump deleted successfully\n");
	अवरोध;
	शेष:
		dev_err(dev, "Invalid dump level: 0x%x\n", dump->flag);
		वापस -EINVAL;
	पूर्ण
	वापस status;
पूर्ण

अटल व्योम be_get_wol(काष्ठा net_device *netdev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);

	अगर (adapter->wol_cap & BE_WOL_CAP) अणु
		wol->supported |= WAKE_MAGIC;
		अगर (adapter->wol_en)
			wol->wolopts |= WAKE_MAGIC;
	पूर्ण अन्यथा अणु
		wol->wolopts = 0;
	पूर्ण
	स_रखो(&wol->sopass, 0, माप(wol->sopass));
पूर्ण

अटल पूर्णांक be_set_wol(काष्ठा net_device *netdev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	काष्ठा device *dev = &adapter->pdev->dev;
	काष्ठा be_dma_mem cmd;
	u8 mac[ETH_ALEN];
	bool enable;
	पूर्णांक status;

	अगर (wol->wolopts & ~WAKE_MAGIC)
		वापस -EOPNOTSUPP;

	अगर (!(adapter->wol_cap & BE_WOL_CAP)) अणु
		dev_warn(&adapter->pdev->dev, "WOL not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	cmd.size = माप(काष्ठा be_cmd_req_acpi_wol_magic_config);
	cmd.va = dma_alloc_coherent(dev, cmd.size, &cmd.dma, GFP_KERNEL);
	अगर (!cmd.va)
		वापस -ENOMEM;

	eth_zero_addr(mac);

	enable = wol->wolopts & WAKE_MAGIC;
	अगर (enable)
		ether_addr_copy(mac, adapter->netdev->dev_addr);

	status = be_cmd_enable_magic_wol(adapter, mac, &cmd);
	अगर (status) अणु
		dev_err(dev, "Could not set Wake-on-lan mac address\n");
		status = be_cmd_status(status);
		जाओ err;
	पूर्ण

	pci_enable_wake(adapter->pdev, PCI_D3hot, enable);
	pci_enable_wake(adapter->pdev, PCI_D3cold, enable);

	adapter->wol_en = enable ? true : false;

err:
	dma_मुक्त_coherent(dev, cmd.size, cmd.va, cmd.dma);
	वापस status;
पूर्ण

अटल पूर्णांक be_test_ddr_dma(काष्ठा be_adapter *adapter)
अणु
	पूर्णांक ret, i;
	काष्ठा be_dma_mem ddrdma_cmd;
	अटल स्थिर u64 pattern[2] = अणु
		0x5a5a5a5a5a5a5a5aULL, 0xa5a5a5a5a5a5a5a5ULL
	पूर्ण;

	ddrdma_cmd.size = माप(काष्ठा be_cmd_req_ddrdma_test);
	ddrdma_cmd.va = dma_alloc_coherent(&adapter->pdev->dev,
					   ddrdma_cmd.size, &ddrdma_cmd.dma,
					   GFP_KERNEL);
	अगर (!ddrdma_cmd.va)
		वापस -ENOMEM;

	क्रम (i = 0; i < 2; i++) अणु
		ret = be_cmd_ddr_dma_test(adapter, pattern[i],
					  4096, &ddrdma_cmd);
		अगर (ret != 0)
			जाओ err;
	पूर्ण

err:
	dma_मुक्त_coherent(&adapter->pdev->dev, ddrdma_cmd.size, ddrdma_cmd.va,
			  ddrdma_cmd.dma);
	वापस be_cmd_status(ret);
पूर्ण

अटल u64 be_loopback_test(काष्ठा be_adapter *adapter, u8 loopback_type,
			    u64 *status)
अणु
	पूर्णांक ret;

	ret = be_cmd_set_loopback(adapter, adapter->hba_port_num,
				  loopback_type, 1);
	अगर (ret)
		वापस ret;

	*status = be_cmd_loopback_test(adapter, adapter->hba_port_num,
				       loopback_type, 1500, 2, 0xabc);

	ret = be_cmd_set_loopback(adapter, adapter->hba_port_num,
				  BE_NO_LOOPBACK, 1);
	अगर (ret)
		वापस ret;

	वापस *status;
पूर्ण

अटल व्योम be_self_test(काष्ठा net_device *netdev, काष्ठा ethtool_test *test,
			 u64 *data)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	पूर्णांक status, cnt;
	u8 link_status = 0;

	अगर (adapter->function_caps & BE_FUNCTION_CAPS_SUPER_NIC) अणु
		dev_err(&adapter->pdev->dev, "Self test not supported\n");
		test->flags |= ETH_TEST_FL_FAILED;
		वापस;
	पूर्ण

	स_रखो(data, 0, माप(u64) * ETHTOOL_TESTS_NUM);

	/* check link status beक्रमe offline tests */
	link_status = netअगर_carrier_ok(netdev);

	अगर (test->flags & ETH_TEST_FL_OFFLINE) अणु
		अगर (be_loopback_test(adapter, BE_MAC_LOOPBACK, &data[0]) != 0)
			test->flags |= ETH_TEST_FL_FAILED;

		अगर (be_loopback_test(adapter, BE_PHY_LOOPBACK, &data[1]) != 0)
			test->flags |= ETH_TEST_FL_FAILED;

		अगर (test->flags & ETH_TEST_FL_EXTERNAL_LB) अणु
			अगर (be_loopback_test(adapter, BE_ONE_PORT_EXT_LOOPBACK,
					     &data[2]) != 0)
				test->flags |= ETH_TEST_FL_FAILED;
			test->flags |= ETH_TEST_FL_EXTERNAL_LB_DONE;
		पूर्ण
	पूर्ण

	अगर (!lancer_chip(adapter) && be_test_ddr_dma(adapter) != 0) अणु
		data[3] = 1;
		test->flags |= ETH_TEST_FL_FAILED;
	पूर्ण

	/* link status was करोwn prior to test */
	अगर (!link_status) अणु
		test->flags |= ETH_TEST_FL_FAILED;
		data[4] = 1;
		वापस;
	पूर्ण

	क्रम (cnt = 10; cnt; cnt--) अणु
		status = be_cmd_link_status_query(adapter, शून्य, &link_status,
						  0);
		अगर (status) अणु
			test->flags |= ETH_TEST_FL_FAILED;
			data[4] = -1;
			अवरोध;
		पूर्ण

		अगर (link_status)
			अवरोध;

		msleep_पूर्णांकerruptible(500);
	पूर्ण
पूर्ण

अटल पूर्णांक be_करो_flash(काष्ठा net_device *netdev, काष्ठा ethtool_flash *efl)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);

	वापस be_load_fw(adapter, efl->data);
पूर्ण

अटल पूर्णांक
be_get_dump_flag(काष्ठा net_device *netdev, काष्ठा ethtool_dump *dump)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);

	अगर (!check_privilege(adapter, MAX_PRIVILEGES))
		वापस -EOPNOTSUPP;

	dump->len = be_get_dump_len(adapter);
	dump->version = 1;
	dump->flag = 0x1;	/* FW dump is enabled */
	वापस 0;
पूर्ण

अटल पूर्णांक
be_get_dump_data(काष्ठा net_device *netdev, काष्ठा ethtool_dump *dump,
		 व्योम *buf)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	पूर्णांक status;

	अगर (!check_privilege(adapter, MAX_PRIVILEGES))
		वापस -EOPNOTSUPP;

	status = be_पढ़ो_dump_data(adapter, dump->len, buf);
	वापस be_cmd_status(status);
पूर्ण

अटल पूर्णांक be_get_eeprom_len(काष्ठा net_device *netdev)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);

	अगर (!check_privilege(adapter, MAX_PRIVILEGES))
		वापस 0;

	अगर (lancer_chip(adapter)) अणु
		अगर (be_physfn(adapter))
			वापस lancer_cmd_get_file_len(adapter,
						       LANCER_VPD_PF_खाता);
		अन्यथा
			वापस lancer_cmd_get_file_len(adapter,
						       LANCER_VPD_VF_खाता);
	पूर्ण अन्यथा अणु
		वापस BE_READ_SEEPROM_LEN;
	पूर्ण
पूर्ण

अटल पूर्णांक be_पढ़ो_eeprom(काष्ठा net_device *netdev,
			  काष्ठा ethtool_eeprom *eeprom, uपूर्णांक8_t *data)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	काष्ठा be_dma_mem eeprom_cmd;
	काष्ठा be_cmd_resp_seeprom_पढ़ो *resp;
	पूर्णांक status;

	अगर (!eeprom->len)
		वापस -EINVAL;

	अगर (lancer_chip(adapter)) अणु
		अगर (be_physfn(adapter))
			वापस lancer_cmd_पढ़ो_file(adapter, LANCER_VPD_PF_खाता,
						    eeprom->len, data);
		अन्यथा
			वापस lancer_cmd_पढ़ो_file(adapter, LANCER_VPD_VF_खाता,
						    eeprom->len, data);
	पूर्ण

	eeprom->magic = BE_VENDOR_ID | (adapter->pdev->device<<16);

	स_रखो(&eeprom_cmd, 0, माप(काष्ठा be_dma_mem));
	eeprom_cmd.size = माप(काष्ठा be_cmd_req_seeprom_पढ़ो);
	eeprom_cmd.va = dma_alloc_coherent(&adapter->pdev->dev,
					   eeprom_cmd.size, &eeprom_cmd.dma,
					   GFP_KERNEL);

	अगर (!eeprom_cmd.va)
		वापस -ENOMEM;

	status = be_cmd_get_seeprom_data(adapter, &eeprom_cmd);

	अगर (!status) अणु
		resp = eeprom_cmd.va;
		स_नकल(data, resp->seeprom_data + eeprom->offset, eeprom->len);
	पूर्ण
	dma_मुक्त_coherent(&adapter->pdev->dev, eeprom_cmd.size, eeprom_cmd.va,
			  eeprom_cmd.dma);

	वापस be_cmd_status(status);
पूर्ण

अटल u32 be_get_msg_level(काष्ठा net_device *netdev)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);

	वापस adapter->msg_enable;
पूर्ण

अटल व्योम be_set_msg_level(काष्ठा net_device *netdev, u32 level)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);

	अगर (adapter->msg_enable == level)
		वापस;

	अगर ((level & NETIF_MSG_HW) != (adapter->msg_enable & NETIF_MSG_HW))
		अगर (BEx_chip(adapter))
			be_cmd_set_fw_log_level(adapter, level & NETIF_MSG_HW ?
						FW_LOG_LEVEL_DEFAULT :
						FW_LOG_LEVEL_FATAL);
	adapter->msg_enable = level;
पूर्ण

अटल u64 be_get_rss_hash_opts(काष्ठा be_adapter *adapter, u64 flow_type)
अणु
	u64 data = 0;

	चयन (flow_type) अणु
	हाल TCP_V4_FLOW:
		अगर (adapter->rss_info.rss_flags & RSS_ENABLE_IPV4)
			data |= RXH_IP_DST | RXH_IP_SRC;
		अगर (adapter->rss_info.rss_flags & RSS_ENABLE_TCP_IPV4)
			data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		अवरोध;
	हाल UDP_V4_FLOW:
		अगर (adapter->rss_info.rss_flags & RSS_ENABLE_IPV4)
			data |= RXH_IP_DST | RXH_IP_SRC;
		अगर (adapter->rss_info.rss_flags & RSS_ENABLE_UDP_IPV4)
			data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		अवरोध;
	हाल TCP_V6_FLOW:
		अगर (adapter->rss_info.rss_flags & RSS_ENABLE_IPV6)
			data |= RXH_IP_DST | RXH_IP_SRC;
		अगर (adapter->rss_info.rss_flags & RSS_ENABLE_TCP_IPV6)
			data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		अवरोध;
	हाल UDP_V6_FLOW:
		अगर (adapter->rss_info.rss_flags & RSS_ENABLE_IPV6)
			data |= RXH_IP_DST | RXH_IP_SRC;
		अगर (adapter->rss_info.rss_flags & RSS_ENABLE_UDP_IPV6)
			data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		अवरोध;
	पूर्ण

	वापस data;
पूर्ण

अटल पूर्णांक be_get_rxnfc(काष्ठा net_device *netdev, काष्ठा ethtool_rxnfc *cmd,
			u32 *rule_locs)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);

	अगर (!be_multi_rxq(adapter)) अणु
		dev_info(&adapter->pdev->dev,
			 "ethtool::get_rxnfc: RX flow hashing is disabled\n");
		वापस -EINVAL;
	पूर्ण

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_GRXFH:
		cmd->data = be_get_rss_hash_opts(adapter, cmd->flow_type);
		अवरोध;
	हाल ETHTOOL_GRXRINGS:
		cmd->data = adapter->num_rx_qs;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक be_set_rss_hash_opts(काष्ठा be_adapter *adapter,
				काष्ठा ethtool_rxnfc *cmd)
अणु
	पूर्णांक status;
	u32 rss_flags = adapter->rss_info.rss_flags;

	अगर (cmd->data != L3_RSS_FLAGS &&
	    cmd->data != (L3_RSS_FLAGS | L4_RSS_FLAGS))
		वापस -EINVAL;

	चयन (cmd->flow_type) अणु
	हाल TCP_V4_FLOW:
		अगर (cmd->data == L3_RSS_FLAGS)
			rss_flags &= ~RSS_ENABLE_TCP_IPV4;
		अन्यथा अगर (cmd->data == (L3_RSS_FLAGS | L4_RSS_FLAGS))
			rss_flags |= RSS_ENABLE_IPV4 |
					RSS_ENABLE_TCP_IPV4;
		अवरोध;
	हाल TCP_V6_FLOW:
		अगर (cmd->data == L3_RSS_FLAGS)
			rss_flags &= ~RSS_ENABLE_TCP_IPV6;
		अन्यथा अगर (cmd->data == (L3_RSS_FLAGS | L4_RSS_FLAGS))
			rss_flags |= RSS_ENABLE_IPV6 |
					RSS_ENABLE_TCP_IPV6;
		अवरोध;
	हाल UDP_V4_FLOW:
		अगर ((cmd->data == (L3_RSS_FLAGS | L4_RSS_FLAGS)) &&
		    BEx_chip(adapter))
			वापस -EINVAL;

		अगर (cmd->data == L3_RSS_FLAGS)
			rss_flags &= ~RSS_ENABLE_UDP_IPV4;
		अन्यथा अगर (cmd->data == (L3_RSS_FLAGS | L4_RSS_FLAGS))
			rss_flags |= RSS_ENABLE_IPV4 |
					RSS_ENABLE_UDP_IPV4;
		अवरोध;
	हाल UDP_V6_FLOW:
		अगर ((cmd->data == (L3_RSS_FLAGS | L4_RSS_FLAGS)) &&
		    BEx_chip(adapter))
			वापस -EINVAL;

		अगर (cmd->data == L3_RSS_FLAGS)
			rss_flags &= ~RSS_ENABLE_UDP_IPV6;
		अन्यथा अगर (cmd->data == (L3_RSS_FLAGS | L4_RSS_FLAGS))
			rss_flags |= RSS_ENABLE_IPV6 |
					RSS_ENABLE_UDP_IPV6;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (rss_flags == adapter->rss_info.rss_flags)
		वापस 0;

	status = be_cmd_rss_config(adapter, adapter->rss_info.rsstable,
				   rss_flags, RSS_INसूची_TABLE_LEN,
				   adapter->rss_info.rss_hkey);
	अगर (!status)
		adapter->rss_info.rss_flags = rss_flags;

	वापस be_cmd_status(status);
पूर्ण

अटल पूर्णांक be_set_rxnfc(काष्ठा net_device *netdev, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	पूर्णांक status = 0;

	अगर (!be_multi_rxq(adapter)) अणु
		dev_err(&adapter->pdev->dev,
			"ethtool::set_rxnfc: RX flow hashing is disabled\n");
		वापस -EINVAL;
	पूर्ण

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_SRXFH:
		status = be_set_rss_hash_opts(adapter, cmd);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम be_get_channels(काष्ठा net_device *netdev,
			    काष्ठा ethtool_channels *ch)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	u16 num_rx_irqs = max_t(u16, adapter->num_rss_qs, 1);

	/* num_tx_qs is always same as the number of irqs used क्रम TX */
	ch->combined_count = min(adapter->num_tx_qs, num_rx_irqs);
	ch->rx_count = num_rx_irqs - ch->combined_count;
	ch->tx_count = adapter->num_tx_qs - ch->combined_count;

	ch->max_combined = be_max_qp_irqs(adapter);
	/* The user must create atleast one combined channel */
	ch->max_rx = be_max_rx_irqs(adapter) - 1;
	ch->max_tx = be_max_tx_irqs(adapter) - 1;
पूर्ण

अटल पूर्णांक be_set_channels(काष्ठा net_device  *netdev,
			   काष्ठा ethtool_channels *ch)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	पूर्णांक status;

	/* we support either only combined channels or a combination of
	 * combined and either RX-only or TX-only channels.
	 */
	अगर (ch->other_count || !ch->combined_count ||
	    (ch->rx_count && ch->tx_count))
		वापस -EINVAL;

	अगर (ch->combined_count > be_max_qp_irqs(adapter) ||
	    (ch->rx_count &&
	     (ch->rx_count + ch->combined_count) > be_max_rx_irqs(adapter)) ||
	    (ch->tx_count &&
	     (ch->tx_count + ch->combined_count) > be_max_tx_irqs(adapter)))
		वापस -EINVAL;

	adapter->cfg_num_rx_irqs = ch->combined_count + ch->rx_count;
	adapter->cfg_num_tx_irqs = ch->combined_count + ch->tx_count;

	status = be_update_queues(adapter);
	वापस be_cmd_status(status);
पूर्ण

अटल u32 be_get_rxfh_indir_size(काष्ठा net_device *netdev)
अणु
	वापस RSS_INसूची_TABLE_LEN;
पूर्ण

अटल u32 be_get_rxfh_key_size(काष्ठा net_device *netdev)
अणु
	वापस RSS_HASH_KEY_LEN;
पूर्ण

अटल पूर्णांक be_get_rxfh(काष्ठा net_device *netdev, u32 *indir, u8 *hkey,
		       u8 *hfunc)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	पूर्णांक i;
	काष्ठा rss_info *rss = &adapter->rss_info;

	अगर (indir) अणु
		क्रम (i = 0; i < RSS_INसूची_TABLE_LEN; i++)
			indir[i] = rss->rss_queue[i];
	पूर्ण

	अगर (hkey)
		स_नकल(hkey, rss->rss_hkey, RSS_HASH_KEY_LEN);

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	वापस 0;
पूर्ण

अटल पूर्णांक be_set_rxfh(काष्ठा net_device *netdev, स्थिर u32 *indir,
		       स्थिर u8 *hkey, स्थिर u8 hfunc)
अणु
	पूर्णांक rc = 0, i, j;
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	u8 rsstable[RSS_INसूची_TABLE_LEN];

	/* We करो not allow change in unsupported parameters */
	अगर (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP)
		वापस -EOPNOTSUPP;

	अगर (indir) अणु
		काष्ठा be_rx_obj *rxo;

		क्रम (i = 0; i < RSS_INसूची_TABLE_LEN; i++) अणु
			j = indir[i];
			rxo = &adapter->rx_obj[j];
			rsstable[i] = rxo->rss_id;
			adapter->rss_info.rss_queue[i] = j;
		पूर्ण
	पूर्ण अन्यथा अणु
		स_नकल(rsstable, adapter->rss_info.rsstable,
		       RSS_INसूची_TABLE_LEN);
	पूर्ण

	अगर (!hkey)
		hkey =  adapter->rss_info.rss_hkey;

	rc = be_cmd_rss_config(adapter, rsstable,
			       adapter->rss_info.rss_flags,
			       RSS_INसूची_TABLE_LEN, hkey);
	अगर (rc) अणु
		adapter->rss_info.rss_flags = RSS_ENABLE_NONE;
		वापस -EIO;
	पूर्ण
	स_नकल(adapter->rss_info.rss_hkey, hkey, RSS_HASH_KEY_LEN);
	स_नकल(adapter->rss_info.rsstable, rsstable,
	       RSS_INसूची_TABLE_LEN);
	वापस 0;
पूर्ण

अटल पूर्णांक be_get_module_info(काष्ठा net_device *netdev,
			      काष्ठा ethtool_modinfo *modinfo)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	u8 page_data[PAGE_DATA_LEN];
	पूर्णांक status;

	अगर (!check_privilege(adapter, MAX_PRIVILEGES))
		वापस -EOPNOTSUPP;

	status = be_cmd_पढ़ो_port_transceiver_data(adapter, TR_PAGE_A0,
						   page_data);
	अगर (!status) अणु
		अगर (!page_data[SFP_PLUS_SFF_8472_COMP]) अणु
			modinfo->type = ETH_MODULE_SFF_8079;
			modinfo->eeprom_len = PAGE_DATA_LEN;
		पूर्ण अन्यथा अणु
			modinfo->type = ETH_MODULE_SFF_8472;
			modinfo->eeprom_len = 2 * PAGE_DATA_LEN;
		पूर्ण
	पूर्ण
	वापस be_cmd_status(status);
पूर्ण

अटल पूर्णांक be_get_module_eeprom(काष्ठा net_device *netdev,
				काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	पूर्णांक status;

	अगर (!check_privilege(adapter, MAX_PRIVILEGES))
		वापस -EOPNOTSUPP;

	status = be_cmd_पढ़ो_port_transceiver_data(adapter, TR_PAGE_A0,
						   data);
	अगर (status)
		जाओ err;

	अगर (eeprom->offset + eeprom->len > PAGE_DATA_LEN) अणु
		status = be_cmd_पढ़ो_port_transceiver_data(adapter,
							   TR_PAGE_A2,
							   data +
							   PAGE_DATA_LEN);
		अगर (status)
			जाओ err;
	पूर्ण
	अगर (eeprom->offset)
		स_नकल(data, data + eeprom->offset, eeprom->len);
err:
	वापस be_cmd_status(status);
पूर्ण

अटल u32 be_get_priv_flags(काष्ठा net_device *netdev)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);

	वापस adapter->priv_flags;
पूर्ण

अटल पूर्णांक be_set_priv_flags(काष्ठा net_device *netdev, u32 flags)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	bool tpe_old = !!(adapter->priv_flags & BE_DISABLE_TPE_RECOVERY);
	bool tpe_new = !!(flags & BE_DISABLE_TPE_RECOVERY);

	अगर (tpe_old != tpe_new) अणु
		अगर (tpe_new) अणु
			adapter->priv_flags |= BE_DISABLE_TPE_RECOVERY;
			dev_info(&adapter->pdev->dev,
				 "HW error recovery is disabled\n");
		पूर्ण अन्यथा अणु
			adapter->priv_flags &= ~BE_DISABLE_TPE_RECOVERY;
			dev_info(&adapter->pdev->dev,
				 "HW error recovery is enabled\n");
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा ethtool_ops be_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_USE_ADAPTIVE |
				     ETHTOOL_COALESCE_USECS_LOW_HIGH,
	.get_drvinfo = be_get_drvinfo,
	.get_wol = be_get_wol,
	.set_wol = be_set_wol,
	.get_link = ethtool_op_get_link,
	.get_eeprom_len = be_get_eeprom_len,
	.get_eeprom = be_पढ़ो_eeprom,
	.get_coalesce = be_get_coalesce,
	.set_coalesce = be_set_coalesce,
	.get_ringparam = be_get_ringparam,
	.get_छोड़ोparam = be_get_छोड़ोparam,
	.set_छोड़ोparam = be_set_छोड़ोparam,
	.set_priv_flags = be_set_priv_flags,
	.get_priv_flags = be_get_priv_flags,
	.get_strings = be_get_stat_strings,
	.set_phys_id = be_set_phys_id,
	.set_dump = be_set_dump,
	.get_msglevel = be_get_msg_level,
	.set_msglevel = be_set_msg_level,
	.get_sset_count = be_get_sset_count,
	.get_ethtool_stats = be_get_ethtool_stats,
	.flash_device = be_करो_flash,
	.self_test = be_self_test,
	.get_rxnfc = be_get_rxnfc,
	.set_rxnfc = be_set_rxnfc,
	.get_rxfh_indir_size = be_get_rxfh_indir_size,
	.get_rxfh_key_size = be_get_rxfh_key_size,
	.get_rxfh = be_get_rxfh,
	.set_rxfh = be_set_rxfh,
	.get_dump_flag = be_get_dump_flag,
	.get_dump_data = be_get_dump_data,
	.get_channels = be_get_channels,
	.set_channels = be_set_channels,
	.get_module_info = be_get_module_info,
	.get_module_eeprom = be_get_module_eeprom,
	.get_link_ksettings = be_get_link_ksettings,
पूर्ण;
