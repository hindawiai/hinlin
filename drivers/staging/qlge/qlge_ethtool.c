<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/sched.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/mempool.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <net/ipv6.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/delay.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "qlge.h"

काष्ठा qlge_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक माप_stat;
	पूर्णांक stat_offset;
पूर्ण;

#घोषणा QL_SIZखातापूर्ण(m) माप_field(काष्ठा qlge_adapter, m)
#घोषणा QL_OFF(m) दुरत्व(काष्ठा qlge_adapter, m)

अटल स्थिर काष्ठा qlge_stats qlge_gstrings_stats[] = अणु
	अणु"tx_pkts", QL_SIZखातापूर्ण(nic_stats.tx_pkts), QL_OFF(nic_stats.tx_pkts)पूर्ण,
	अणु"tx_bytes", QL_SIZखातापूर्ण(nic_stats.tx_bytes), QL_OFF(nic_stats.tx_bytes)पूर्ण,
	अणु"tx_mcast_pkts", QL_SIZखातापूर्ण(nic_stats.tx_mcast_pkts),
					QL_OFF(nic_stats.tx_mcast_pkts)पूर्ण,
	अणु"tx_bcast_pkts", QL_SIZखातापूर्ण(nic_stats.tx_bcast_pkts),
					QL_OFF(nic_stats.tx_bcast_pkts)पूर्ण,
	अणु"tx_ucast_pkts", QL_SIZखातापूर्ण(nic_stats.tx_ucast_pkts),
					QL_OFF(nic_stats.tx_ucast_pkts)पूर्ण,
	अणु"tx_ctl_pkts", QL_SIZखातापूर्ण(nic_stats.tx_ctl_pkts),
					QL_OFF(nic_stats.tx_ctl_pkts)पूर्ण,
	अणु"tx_pause_pkts", QL_SIZखातापूर्ण(nic_stats.tx_छोड़ो_pkts),
					QL_OFF(nic_stats.tx_छोड़ो_pkts)पूर्ण,
	अणु"tx_64_pkts", QL_SIZखातापूर्ण(nic_stats.tx_64_pkt),
					QL_OFF(nic_stats.tx_64_pkt)पूर्ण,
	अणु"tx_65_to_127_pkts", QL_SIZखातापूर्ण(nic_stats.tx_65_to_127_pkt),
					QL_OFF(nic_stats.tx_65_to_127_pkt)पूर्ण,
	अणु"tx_128_to_255_pkts", QL_SIZखातापूर्ण(nic_stats.tx_128_to_255_pkt),
					QL_OFF(nic_stats.tx_128_to_255_pkt)पूर्ण,
	अणु"tx_256_511_pkts", QL_SIZखातापूर्ण(nic_stats.tx_256_511_pkt),
					QL_OFF(nic_stats.tx_256_511_pkt)पूर्ण,
	अणु"tx_512_to_1023_pkts",	QL_SIZखातापूर्ण(nic_stats.tx_512_to_1023_pkt),
					QL_OFF(nic_stats.tx_512_to_1023_pkt)पूर्ण,
	अणु"tx_1024_to_1518_pkts", QL_SIZखातापूर्ण(nic_stats.tx_1024_to_1518_pkt),
					QL_OFF(nic_stats.tx_1024_to_1518_pkt)पूर्ण,
	अणु"tx_1519_to_max_pkts",	QL_SIZखातापूर्ण(nic_stats.tx_1519_to_max_pkt),
					QL_OFF(nic_stats.tx_1519_to_max_pkt)पूर्ण,
	अणु"tx_undersize_pkts", QL_SIZखातापूर्ण(nic_stats.tx_undersize_pkt),
					QL_OFF(nic_stats.tx_undersize_pkt)पूर्ण,
	अणु"tx_oversize_pkts", QL_SIZखातापूर्ण(nic_stats.tx_oversize_pkt),
					QL_OFF(nic_stats.tx_oversize_pkt)पूर्ण,
	अणु"rx_bytes", QL_SIZखातापूर्ण(nic_stats.rx_bytes), QL_OFF(nic_stats.rx_bytes)पूर्ण,
	अणु"rx_bytes_ok",	QL_SIZखातापूर्ण(nic_stats.rx_bytes_ok),
					QL_OFF(nic_stats.rx_bytes_ok)पूर्ण,
	अणु"rx_pkts", QL_SIZखातापूर्ण(nic_stats.rx_pkts), QL_OFF(nic_stats.rx_pkts)पूर्ण,
	अणु"rx_pkts_ok", QL_SIZखातापूर्ण(nic_stats.rx_pkts_ok),
					QL_OFF(nic_stats.rx_pkts_ok)पूर्ण,
	अणु"rx_bcast_pkts", QL_SIZखातापूर्ण(nic_stats.rx_bcast_pkts),
					QL_OFF(nic_stats.rx_bcast_pkts)पूर्ण,
	अणु"rx_mcast_pkts", QL_SIZखातापूर्ण(nic_stats.rx_mcast_pkts),
					QL_OFF(nic_stats.rx_mcast_pkts)पूर्ण,
	अणु"rx_ucast_pkts", QL_SIZखातापूर्ण(nic_stats.rx_ucast_pkts),
					QL_OFF(nic_stats.rx_ucast_pkts)पूर्ण,
	अणु"rx_undersize_pkts", QL_SIZखातापूर्ण(nic_stats.rx_undersize_pkts),
					QL_OFF(nic_stats.rx_undersize_pkts)पूर्ण,
	अणु"rx_oversize_pkts", QL_SIZखातापूर्ण(nic_stats.rx_oversize_pkts),
					QL_OFF(nic_stats.rx_oversize_pkts)पूर्ण,
	अणु"rx_jabber_pkts", QL_SIZखातापूर्ण(nic_stats.rx_jabber_pkts),
					QL_OFF(nic_stats.rx_jabber_pkts)पूर्ण,
	अणु"rx_undersize_fcerr_pkts",
		QL_SIZखातापूर्ण(nic_stats.rx_undersize_fcerr_pkts),
				QL_OFF(nic_stats.rx_undersize_fcerr_pkts)पूर्ण,
	अणु"rx_drop_events", QL_SIZखातापूर्ण(nic_stats.rx_drop_events),
					QL_OFF(nic_stats.rx_drop_events)पूर्ण,
	अणु"rx_fcerr_pkts", QL_SIZखातापूर्ण(nic_stats.rx_fcerr_pkts),
					QL_OFF(nic_stats.rx_fcerr_pkts)पूर्ण,
	अणु"rx_align_err", QL_SIZखातापूर्ण(nic_stats.rx_align_err),
					QL_OFF(nic_stats.rx_align_err)पूर्ण,
	अणु"rx_symbol_err", QL_SIZखातापूर्ण(nic_stats.rx_symbol_err),
					QL_OFF(nic_stats.rx_symbol_err)पूर्ण,
	अणु"rx_mac_err", QL_SIZखातापूर्ण(nic_stats.rx_mac_err),
					QL_OFF(nic_stats.rx_mac_err)पूर्ण,
	अणु"rx_ctl_pkts",	QL_SIZखातापूर्ण(nic_stats.rx_ctl_pkts),
					QL_OFF(nic_stats.rx_ctl_pkts)पूर्ण,
	अणु"rx_pause_pkts", QL_SIZखातापूर्ण(nic_stats.rx_छोड़ो_pkts),
					QL_OFF(nic_stats.rx_छोड़ो_pkts)पूर्ण,
	अणु"rx_64_pkts", QL_SIZखातापूर्ण(nic_stats.rx_64_pkts),
					QL_OFF(nic_stats.rx_64_pkts)पूर्ण,
	अणु"rx_65_to_127_pkts", QL_SIZखातापूर्ण(nic_stats.rx_65_to_127_pkts),
					QL_OFF(nic_stats.rx_65_to_127_pkts)पूर्ण,
	अणु"rx_128_255_pkts", QL_SIZखातापूर्ण(nic_stats.rx_128_255_pkts),
					QL_OFF(nic_stats.rx_128_255_pkts)पूर्ण,
	अणु"rx_256_511_pkts", QL_SIZखातापूर्ण(nic_stats.rx_256_511_pkts),
					QL_OFF(nic_stats.rx_256_511_pkts)पूर्ण,
	अणु"rx_512_to_1023_pkts",	QL_SIZखातापूर्ण(nic_stats.rx_512_to_1023_pkts),
					QL_OFF(nic_stats.rx_512_to_1023_pkts)पूर्ण,
	अणु"rx_1024_to_1518_pkts", QL_SIZखातापूर्ण(nic_stats.rx_1024_to_1518_pkts),
					QL_OFF(nic_stats.rx_1024_to_1518_pkts)पूर्ण,
	अणु"rx_1519_to_max_pkts",	QL_SIZखातापूर्ण(nic_stats.rx_1519_to_max_pkts),
					QL_OFF(nic_stats.rx_1519_to_max_pkts)पूर्ण,
	अणु"rx_len_err_pkts", QL_SIZखातापूर्ण(nic_stats.rx_len_err_pkts),
					QL_OFF(nic_stats.rx_len_err_pkts)पूर्ण,
	अणु"rx_code_err",	QL_SIZखातापूर्ण(nic_stats.rx_code_err),
					QL_OFF(nic_stats.rx_code_err)पूर्ण,
	अणु"rx_oversize_err", QL_SIZखातापूर्ण(nic_stats.rx_oversize_err),
					QL_OFF(nic_stats.rx_oversize_err)पूर्ण,
	अणु"rx_undersize_err", QL_SIZखातापूर्ण(nic_stats.rx_undersize_err),
					QL_OFF(nic_stats.rx_undersize_err)पूर्ण,
	अणु"rx_preamble_err", QL_SIZखातापूर्ण(nic_stats.rx_preamble_err),
					QL_OFF(nic_stats.rx_preamble_err)पूर्ण,
	अणु"rx_frame_len_err", QL_SIZखातापूर्ण(nic_stats.rx_frame_len_err),
					QL_OFF(nic_stats.rx_frame_len_err)पूर्ण,
	अणु"rx_crc_err", QL_SIZखातापूर्ण(nic_stats.rx_crc_err),
					QL_OFF(nic_stats.rx_crc_err)पूर्ण,
	अणु"rx_err_count", QL_SIZखातापूर्ण(nic_stats.rx_err_count),
					QL_OFF(nic_stats.rx_err_count)पूर्ण,
	अणु"tx_cbfc_pause_frames0", QL_SIZखातापूर्ण(nic_stats.tx_cbfc_छोड़ो_frames0),
				QL_OFF(nic_stats.tx_cbfc_छोड़ो_frames0)पूर्ण,
	अणु"tx_cbfc_pause_frames1", QL_SIZखातापूर्ण(nic_stats.tx_cbfc_छोड़ो_frames1),
				QL_OFF(nic_stats.tx_cbfc_छोड़ो_frames1)पूर्ण,
	अणु"tx_cbfc_pause_frames2", QL_SIZखातापूर्ण(nic_stats.tx_cbfc_छोड़ो_frames2),
				QL_OFF(nic_stats.tx_cbfc_छोड़ो_frames2)पूर्ण,
	अणु"tx_cbfc_pause_frames3", QL_SIZखातापूर्ण(nic_stats.tx_cbfc_छोड़ो_frames3),
				QL_OFF(nic_stats.tx_cbfc_छोड़ो_frames3)पूर्ण,
	अणु"tx_cbfc_pause_frames4", QL_SIZखातापूर्ण(nic_stats.tx_cbfc_छोड़ो_frames4),
				QL_OFF(nic_stats.tx_cbfc_छोड़ो_frames4)पूर्ण,
	अणु"tx_cbfc_pause_frames5", QL_SIZखातापूर्ण(nic_stats.tx_cbfc_छोड़ो_frames5),
				QL_OFF(nic_stats.tx_cbfc_छोड़ो_frames5)पूर्ण,
	अणु"tx_cbfc_pause_frames6", QL_SIZखातापूर्ण(nic_stats.tx_cbfc_छोड़ो_frames6),
				QL_OFF(nic_stats.tx_cbfc_छोड़ो_frames6)पूर्ण,
	अणु"tx_cbfc_pause_frames7", QL_SIZखातापूर्ण(nic_stats.tx_cbfc_छोड़ो_frames7),
				QL_OFF(nic_stats.tx_cbfc_छोड़ो_frames7)पूर्ण,
	अणु"rx_cbfc_pause_frames0", QL_SIZखातापूर्ण(nic_stats.rx_cbfc_छोड़ो_frames0),
				QL_OFF(nic_stats.rx_cbfc_छोड़ो_frames0)पूर्ण,
	अणु"rx_cbfc_pause_frames1", QL_SIZखातापूर्ण(nic_stats.rx_cbfc_छोड़ो_frames1),
				QL_OFF(nic_stats.rx_cbfc_छोड़ो_frames1)पूर्ण,
	अणु"rx_cbfc_pause_frames2", QL_SIZखातापूर्ण(nic_stats.rx_cbfc_छोड़ो_frames2),
				QL_OFF(nic_stats.rx_cbfc_छोड़ो_frames2)पूर्ण,
	अणु"rx_cbfc_pause_frames3", QL_SIZखातापूर्ण(nic_stats.rx_cbfc_छोड़ो_frames3),
				QL_OFF(nic_stats.rx_cbfc_छोड़ो_frames3)पूर्ण,
	अणु"rx_cbfc_pause_frames4", QL_SIZखातापूर्ण(nic_stats.rx_cbfc_छोड़ो_frames4),
				QL_OFF(nic_stats.rx_cbfc_छोड़ो_frames4)पूर्ण,
	अणु"rx_cbfc_pause_frames5", QL_SIZखातापूर्ण(nic_stats.rx_cbfc_छोड़ो_frames5),
				QL_OFF(nic_stats.rx_cbfc_छोड़ो_frames5)पूर्ण,
	अणु"rx_cbfc_pause_frames6", QL_SIZखातापूर्ण(nic_stats.rx_cbfc_छोड़ो_frames6),
				QL_OFF(nic_stats.rx_cbfc_छोड़ो_frames6)पूर्ण,
	अणु"rx_cbfc_pause_frames7", QL_SIZखातापूर्ण(nic_stats.rx_cbfc_छोड़ो_frames7),
				QL_OFF(nic_stats.rx_cbfc_छोड़ो_frames7)पूर्ण,
	अणु"rx_nic_fifo_drop", QL_SIZखातापूर्ण(nic_stats.rx_nic_fअगरo_drop),
					QL_OFF(nic_stats.rx_nic_fअगरo_drop)पूर्ण,
पूर्ण;

अटल स्थिर अक्षर qlge_gstrings_test[][ETH_GSTRING_LEN] = अणु
	"Loopback test  (offline)"
पूर्ण;

#घोषणा QLGE_TEST_LEN (माप(qlge_gstrings_test) / ETH_GSTRING_LEN)
#घोषणा QLGE_STATS_LEN ARRAY_SIZE(qlge_gstrings_stats)
#घोषणा QLGE_RCV_MAC_ERR_STATS	7

अटल पूर्णांक qlge_update_ring_coalescing(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक i, status = 0;
	काष्ठा rx_ring *rx_ring;
	काष्ठा cqicb *cqicb;

	अगर (!netअगर_running(qdev->ndev))
		वापस status;

	/* Skip the शेष queue, and update the outbound handler
	 * queues अगर they changed.
	 */
	cqicb = (काष्ठा cqicb *)&qdev->rx_ring[qdev->rss_ring_count];
	अगर (le16_to_cpu(cqicb->irq_delay) != qdev->tx_coalesce_usecs ||
	    le16_to_cpu(cqicb->pkt_delay) != qdev->tx_max_coalesced_frames) अणु
		क्रम (i = qdev->rss_ring_count; i < qdev->rx_ring_count; i++) अणु
			rx_ring = &qdev->rx_ring[i];
			cqicb = (काष्ठा cqicb *)rx_ring;
			cqicb->irq_delay = cpu_to_le16(qdev->tx_coalesce_usecs);
			cqicb->pkt_delay =
				cpu_to_le16(qdev->tx_max_coalesced_frames);
			cqicb->flags = FLAGS_LI;
			status = qlge_ग_लिखो_cfg(qdev, cqicb, माप(*cqicb),
						CFG_LCQ, rx_ring->cq_id);
			अगर (status) अणु
				netअगर_err(qdev, अगरup, qdev->ndev,
					  "Failed to load CQICB.\n");
				जाओ निकास;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Update the inbound (RSS) handler queues अगर they changed. */
	cqicb = (काष्ठा cqicb *)&qdev->rx_ring[0];
	अगर (le16_to_cpu(cqicb->irq_delay) != qdev->rx_coalesce_usecs ||
	    le16_to_cpu(cqicb->pkt_delay) != qdev->rx_max_coalesced_frames) अणु
		क्रम (i = 0; i < qdev->rss_ring_count; i++, rx_ring++) अणु
			rx_ring = &qdev->rx_ring[i];
			cqicb = (काष्ठा cqicb *)rx_ring;
			cqicb->irq_delay = cpu_to_le16(qdev->rx_coalesce_usecs);
			cqicb->pkt_delay =
				cpu_to_le16(qdev->rx_max_coalesced_frames);
			cqicb->flags = FLAGS_LI;
			status = qlge_ग_लिखो_cfg(qdev, cqicb, माप(*cqicb),
						CFG_LCQ, rx_ring->cq_id);
			अगर (status) अणु
				netअगर_err(qdev, अगरup, qdev->ndev,
					  "Failed to load CQICB.\n");
				जाओ निकास;
			पूर्ण
		पूर्ण
	पूर्ण
निकास:
	वापस status;
पूर्ण

अटल व्योम qlge_update_stats(काष्ठा qlge_adapter *qdev)
अणु
	u32 i;
	u64 data;
	u64 *iter = &qdev->nic_stats.tx_pkts;

	spin_lock(&qdev->stats_lock);
	अगर (qlge_sem_spinlock(qdev, qdev->xg_sem_mask)) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Couldn't get xgmac sem.\n");
		जाओ quit;
	पूर्ण
	/*
	 * Get TX statistics.
	 */
	क्रम (i = 0x200; i < 0x280; i += 8) अणु
		अगर (qlge_पढ़ो_xgmac_reg64(qdev, i, &data)) अणु
			netअगर_err(qdev, drv, qdev->ndev,
				  "Error reading status register 0x%.04x.\n",
				  i);
			जाओ end;
		पूर्ण अन्यथा अणु
			*iter = data;
		पूर्ण
		iter++;
	पूर्ण

	/*
	 * Get RX statistics.
	 */
	क्रम (i = 0x300; i < 0x3d0; i += 8) अणु
		अगर (qlge_पढ़ो_xgmac_reg64(qdev, i, &data)) अणु
			netअगर_err(qdev, drv, qdev->ndev,
				  "Error reading status register 0x%.04x.\n",
				  i);
			जाओ end;
		पूर्ण अन्यथा अणु
			*iter = data;
		पूर्ण
		iter++;
	पूर्ण

	/* Update receive mac error statistics */
	iter += QLGE_RCV_MAC_ERR_STATS;

	/*
	 * Get Per-priority TX छोड़ो frame counter statistics.
	 */
	क्रम (i = 0x500; i < 0x540; i += 8) अणु
		अगर (qlge_पढ़ो_xgmac_reg64(qdev, i, &data)) अणु
			netअगर_err(qdev, drv, qdev->ndev,
				  "Error reading status register 0x%.04x.\n",
				  i);
			जाओ end;
		पूर्ण अन्यथा अणु
			*iter = data;
		पूर्ण
		iter++;
	पूर्ण

	/*
	 * Get Per-priority RX छोड़ो frame counter statistics.
	 */
	क्रम (i = 0x568; i < 0x5a8; i += 8) अणु
		अगर (qlge_पढ़ो_xgmac_reg64(qdev, i, &data)) अणु
			netअगर_err(qdev, drv, qdev->ndev,
				  "Error reading status register 0x%.04x.\n",
				  i);
			जाओ end;
		पूर्ण अन्यथा अणु
			*iter = data;
		पूर्ण
		iter++;
	पूर्ण

	/*
	 * Get RX NIC FIFO DROP statistics.
	 */
	अगर (qlge_पढ़ो_xgmac_reg64(qdev, 0x5b8, &data)) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Error reading status register 0x%.04x.\n", i);
		जाओ end;
	पूर्ण अन्यथा अणु
		*iter = data;
	पूर्ण
end:
	qlge_sem_unlock(qdev, qdev->xg_sem_mask);
quit:
	spin_unlock(&qdev->stats_lock);
पूर्ण

अटल व्योम qlge_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *buf)
अणु
	पूर्णांक index;

	चयन (stringset) अणु
	हाल ETH_SS_TEST:
		स_नकल(buf, *qlge_gstrings_test, QLGE_TEST_LEN * ETH_GSTRING_LEN);
		अवरोध;
	हाल ETH_SS_STATS:
		क्रम (index = 0; index < QLGE_STATS_LEN; index++) अणु
			स_नकल(buf + index * ETH_GSTRING_LEN,
			       qlge_gstrings_stats[index].stat_string,
			       ETH_GSTRING_LEN);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक qlge_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_TEST:
		वापस QLGE_TEST_LEN;
	हाल ETH_SS_STATS:
		वापस QLGE_STATS_LEN;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम
qlge_get_ethtool_stats(काष्ठा net_device *ndev,
		       काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);
	पूर्णांक index, length;

	length = QLGE_STATS_LEN;
	qlge_update_stats(qdev);

	क्रम (index = 0; index < length; index++) अणु
		अक्षर *p = (अक्षर *)qdev +
			qlge_gstrings_stats[index].stat_offset;
		*data++ = (qlge_gstrings_stats[index].माप_stat ==
			   माप(u64)) ? *(u64 *)p : (*(u32 *)p);
	पूर्ण
पूर्ण

अटल पूर्णांक qlge_get_link_ksettings(काष्ठा net_device *ndev,
				   काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);
	u32 supported, advertising;

	supported = SUPPORTED_10000baseT_Full;
	advertising = ADVERTISED_10000baseT_Full;

	अगर ((qdev->link_status & STS_LINK_TYPE_MASK) ==
	    STS_LINK_TYPE_10GBASET) अणु
		supported |= (SUPPORTED_TP | SUPPORTED_Autoneg);
		advertising |= (ADVERTISED_TP | ADVERTISED_Autoneg);
		ecmd->base.port = PORT_TP;
		ecmd->base.स्वतःneg = AUTONEG_ENABLE;
	पूर्ण अन्यथा अणु
		supported |= SUPPORTED_FIBRE;
		advertising |= ADVERTISED_FIBRE;
		ecmd->base.port = PORT_FIBRE;
	पूर्ण

	ecmd->base.speed = SPEED_10000;
	ecmd->base.duplex = DUPLEX_FULL;

	ethtool_convert_legacy_u32_to_link_mode(ecmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(ecmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल व्योम qlge_get_drvinfo(काष्ठा net_device *ndev,
			     काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);

	strscpy(drvinfo->driver, qlge_driver_name, माप(drvinfo->driver));
	strscpy(drvinfo->version, qlge_driver_version,
		माप(drvinfo->version));
	snम_लिखो(drvinfo->fw_version, माप(drvinfo->fw_version),
		 "v%d.%d.%d",
		 (qdev->fw_rev_id & 0x00ff0000) >> 16,
		 (qdev->fw_rev_id & 0x0000ff00) >> 8,
		 (qdev->fw_rev_id & 0x000000ff));
	strscpy(drvinfo->bus_info, pci_name(qdev->pdev),
		माप(drvinfo->bus_info));
पूर्ण

अटल व्योम qlge_get_wol(काष्ठा net_device *ndev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);
	अचिन्हित लघु ssys_dev = qdev->pdev->subप्रणाली_device;

	/* WOL is only supported क्रम mezz card. */
	अगर (ssys_dev == QLGE_MEZZ_SSYS_ID_068 ||
	    ssys_dev == QLGE_MEZZ_SSYS_ID_180) अणु
		wol->supported = WAKE_MAGIC;
		wol->wolopts = qdev->wol;
	पूर्ण
पूर्ण

अटल पूर्णांक qlge_set_wol(काष्ठा net_device *ndev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);
	अचिन्हित लघु ssys_dev = qdev->pdev->subप्रणाली_device;

	/* WOL is only supported क्रम mezz card. */
	अगर (ssys_dev != QLGE_MEZZ_SSYS_ID_068 &&
	    ssys_dev != QLGE_MEZZ_SSYS_ID_180) अणु
		netअगर_info(qdev, drv, qdev->ndev,
			   "WOL is only supported for mezz card\n");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (wol->wolopts & ~WAKE_MAGIC)
		वापस -EINVAL;
	qdev->wol = wol->wolopts;

	netअगर_info(qdev, drv, qdev->ndev, "Set wol option 0x%x\n", qdev->wol);
	वापस 0;
पूर्ण

अटल पूर्णांक qlge_set_phys_id(काष्ठा net_device *ndev,
			    क्रमागत ethtool_phys_id_state state)

अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		/* Save the current LED settings */
		अगर (qlge_mb_get_led_cfg(qdev))
			वापस -EIO;

		/* Start blinking */
		qlge_mb_set_led_cfg(qdev, QL_LED_BLINK);
		वापस 0;

	हाल ETHTOOL_ID_INACTIVE:
		/* Restore LED settings */
		अगर (qlge_mb_set_led_cfg(qdev, qdev->led_config))
			वापस -EIO;
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक qlge_start_loopback(काष्ठा qlge_adapter *qdev)
अणु
	अगर (netअगर_carrier_ok(qdev->ndev)) अणु
		set_bit(QL_LB_LINK_UP, &qdev->flags);
		netअगर_carrier_off(qdev->ndev);
	पूर्ण अन्यथा अणु
		clear_bit(QL_LB_LINK_UP, &qdev->flags);
	पूर्ण
	qdev->link_config |= CFG_LOOPBACK_PCS;
	वापस qlge_mb_set_port_cfg(qdev);
पूर्ण

अटल व्योम qlge_stop_loopback(काष्ठा qlge_adapter *qdev)
अणु
	qdev->link_config &= ~CFG_LOOPBACK_PCS;
	qlge_mb_set_port_cfg(qdev);
	अगर (test_bit(QL_LB_LINK_UP, &qdev->flags)) अणु
		netअगर_carrier_on(qdev->ndev);
		clear_bit(QL_LB_LINK_UP, &qdev->flags);
	पूर्ण
पूर्ण

अटल व्योम qlge_create_lb_frame(काष्ठा sk_buff *skb,
				 अचिन्हित पूर्णांक frame_size)
अणु
	स_रखो(skb->data, 0xFF, frame_size);
	frame_size &= ~1;
	स_रखो(&skb->data[frame_size / 2], 0xAA, frame_size / 2 - 1);
	skb->data[frame_size / 2 + 10] = (अचिन्हित अक्षर)0xBE;
	skb->data[frame_size / 2 + 12] = (अचिन्हित अक्षर)0xAF;
पूर्ण

व्योम qlge_check_lb_frame(काष्ठा qlge_adapter *qdev,
			 काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक frame_size = skb->len;

	अगर ((*(skb->data + 3) == 0xFF) &&
	    (*(skb->data + frame_size / 2 + 10) == 0xBE) &&
	    (*(skb->data + frame_size / 2 + 12) == 0xAF)) अणु
		atomic_dec(&qdev->lb_count);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक qlge_run_loopback_test(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक i;
	netdev_tx_t rc;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक size = SMALL_BUF_MAP_SIZE;

	क्रम (i = 0; i < 64; i++) अणु
		skb = netdev_alloc_skb(qdev->ndev, size);
		अगर (!skb)
			वापस -ENOMEM;

		skb->queue_mapping = 0;
		skb_put(skb, size);
		qlge_create_lb_frame(skb, size);
		rc = qlge_lb_send(skb, qdev->ndev);
		अगर (rc != NETDEV_TX_OK)
			वापस -EPIPE;
		atomic_inc(&qdev->lb_count);
	पूर्ण
	/* Give queue समय to settle beक्रमe testing results. */
	msleep(2);
	qlge_clean_lb_rx_ring(&qdev->rx_ring[0], 128);
	वापस atomic_पढ़ो(&qdev->lb_count) ? -EIO : 0;
पूर्ण

अटल पूर्णांक qlge_loopback_test(काष्ठा qlge_adapter *qdev, u64 *data)
अणु
	*data = qlge_start_loopback(qdev);
	अगर (*data)
		जाओ out;
	*data = qlge_run_loopback_test(qdev);
out:
	qlge_stop_loopback(qdev);
	वापस *data;
पूर्ण

अटल व्योम qlge_self_test(काष्ठा net_device *ndev,
			   काष्ठा ethtool_test *eth_test, u64 *data)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);

	स_रखो(data, 0, माप(u64) * QLGE_TEST_LEN);

	अगर (netअगर_running(ndev)) अणु
		set_bit(QL_SELFTEST, &qdev->flags);
		अगर (eth_test->flags == ETH_TEST_FL_OFFLINE) अणु
			/* Offline tests */
			अगर (qlge_loopback_test(qdev, &data[0]))
				eth_test->flags |= ETH_TEST_FL_FAILED;

		पूर्ण अन्यथा अणु
			/* Online tests */
			data[0] = 0;
		पूर्ण
		clear_bit(QL_SELFTEST, &qdev->flags);
		/* Give link समय to come up after
		 * port configuration changes.
		 */
		msleep_पूर्णांकerruptible(4 * 1000);
	पूर्ण अन्यथा अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "is down, Loopback test will fail.\n");
		eth_test->flags |= ETH_TEST_FL_FAILED;
	पूर्ण
पूर्ण

अटल पूर्णांक qlge_get_regs_len(काष्ठा net_device *ndev)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);

	अगर (!test_bit(QL_FRC_COREDUMP, &qdev->flags))
		वापस माप(काष्ठा qlge_mpi_coredump);
	अन्यथा
		वापस माप(काष्ठा qlge_reg_dump);
पूर्ण

अटल व्योम qlge_get_regs(काष्ठा net_device *ndev,
			  काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);

	qlge_get_dump(qdev, p);
	अगर (!test_bit(QL_FRC_COREDUMP, &qdev->flags))
		regs->len = माप(काष्ठा qlge_mpi_coredump);
	अन्यथा
		regs->len = माप(काष्ठा qlge_reg_dump);
पूर्ण

अटल पूर्णांक qlge_get_coalesce(काष्ठा net_device *ndev, काष्ठा ethtool_coalesce *c)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);

	c->rx_coalesce_usecs = qdev->rx_coalesce_usecs;
	c->tx_coalesce_usecs = qdev->tx_coalesce_usecs;

	/* This chip coalesces as follows:
	 * If a packet arrives, hold off पूर्णांकerrupts until
	 * cqicb->पूर्णांक_delay expires, but अगर no other packets arrive करोn't
	 * रुको दीर्घer than cqicb->pkt_पूर्णांक_delay. But ethtool करोesn't use a
	 * समयr to coalesce on a frame basis.  So, we have to take ethtool's
	 * max_coalesced_frames value and convert it to a delay in microseconds.
	 * We करो this by using a basic thoughput of 1,000,000 frames per
	 * second @ (1024 bytes).  This means one frame per usec. So it's a
	 * simple one to one ratio.
	 */
	c->rx_max_coalesced_frames = qdev->rx_max_coalesced_frames;
	c->tx_max_coalesced_frames = qdev->tx_max_coalesced_frames;

	वापस 0;
पूर्ण

अटल पूर्णांक qlge_set_coalesce(काष्ठा net_device *ndev, काष्ठा ethtool_coalesce *c)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);

	/* Validate user parameters. */
	अगर (c->rx_coalesce_usecs > qdev->rx_ring_size / 2)
		वापस -EINVAL;
	/* Don't रुको more than 10 usec. */
	अगर (c->rx_max_coalesced_frames > MAX_INTER_FRAME_WAIT)
		वापस -EINVAL;
	अगर (c->tx_coalesce_usecs > qdev->tx_ring_size / 2)
		वापस -EINVAL;
	अगर (c->tx_max_coalesced_frames > MAX_INTER_FRAME_WAIT)
		वापस -EINVAL;

	/* Verअगरy a change took place beक्रमe updating the hardware. */
	अगर (qdev->rx_coalesce_usecs == c->rx_coalesce_usecs &&
	    qdev->tx_coalesce_usecs == c->tx_coalesce_usecs &&
	    qdev->rx_max_coalesced_frames == c->rx_max_coalesced_frames &&
	    qdev->tx_max_coalesced_frames == c->tx_max_coalesced_frames)
		वापस 0;

	qdev->rx_coalesce_usecs = c->rx_coalesce_usecs;
	qdev->tx_coalesce_usecs = c->tx_coalesce_usecs;
	qdev->rx_max_coalesced_frames = c->rx_max_coalesced_frames;
	qdev->tx_max_coalesced_frames = c->tx_max_coalesced_frames;

	वापस qlge_update_ring_coalescing(qdev);
पूर्ण

अटल व्योम qlge_get_छोड़ोparam(काष्ठा net_device *ndev,
				काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);

	qlge_mb_get_port_cfg(qdev);
	अगर (qdev->link_config & CFG_PAUSE_STD) अणु
		छोड़ो->rx_छोड़ो = 1;
		छोड़ो->tx_छोड़ो = 1;
	पूर्ण
पूर्ण

अटल पूर्णांक qlge_set_छोड़ोparam(काष्ठा net_device *ndev,
			       काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);

	अगर ((छोड़ो->rx_छोड़ो) && (छोड़ो->tx_छोड़ो))
		qdev->link_config |= CFG_PAUSE_STD;
	अन्यथा अगर (!छोड़ो->rx_छोड़ो && !छोड़ो->tx_छोड़ो)
		qdev->link_config &= ~CFG_PAUSE_STD;
	अन्यथा
		वापस -EINVAL;

	वापस qlge_mb_set_port_cfg(qdev);
पूर्ण

अटल u32 qlge_get_msglevel(काष्ठा net_device *ndev)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);

	वापस qdev->msg_enable;
पूर्ण

अटल व्योम qlge_set_msglevel(काष्ठा net_device *ndev, u32 value)
अणु
	काष्ठा qlge_adapter *qdev = netdev_to_qdev(ndev);

	qdev->msg_enable = value;
पूर्ण

स्थिर काष्ठा ethtool_ops qlge_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES,
	.get_drvinfo = qlge_get_drvinfo,
	.get_wol = qlge_get_wol,
	.set_wol = qlge_set_wol,
	.get_regs_len	= qlge_get_regs_len,
	.get_regs = qlge_get_regs,
	.get_msglevel = qlge_get_msglevel,
	.set_msglevel = qlge_set_msglevel,
	.get_link = ethtool_op_get_link,
	.set_phys_id		 = qlge_set_phys_id,
	.self_test		 = qlge_self_test,
	.get_छोड़ोparam		 = qlge_get_छोड़ोparam,
	.set_छोड़ोparam		 = qlge_set_छोड़ोparam,
	.get_coalesce = qlge_get_coalesce,
	.set_coalesce = qlge_set_coalesce,
	.get_sset_count = qlge_get_sset_count,
	.get_strings = qlge_get_strings,
	.get_ethtool_stats = qlge_get_ethtool_stats,
	.get_link_ksettings = qlge_get_link_ksettings,
पूर्ण;

