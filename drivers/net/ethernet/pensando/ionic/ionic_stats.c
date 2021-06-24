<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2017 - 2019 Pensanकरो Systems, Inc */

#समावेश <linux/ethtool.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mutex.h>
#समावेश <linux/netdevice.h>

#समावेश "ionic.h"
#समावेश "ionic_lif.h"
#समावेश "ionic_stats.h"

अटल स्थिर काष्ठा ionic_stat_desc ionic_lअगर_stats_desc[] = अणु
	IONIC_LIF_STAT_DESC(tx_packets),
	IONIC_LIF_STAT_DESC(tx_bytes),
	IONIC_LIF_STAT_DESC(rx_packets),
	IONIC_LIF_STAT_DESC(rx_bytes),
	IONIC_LIF_STAT_DESC(tx_tso),
	IONIC_LIF_STAT_DESC(tx_tso_bytes),
	IONIC_LIF_STAT_DESC(tx_csum_none),
	IONIC_LIF_STAT_DESC(tx_csum),
	IONIC_LIF_STAT_DESC(rx_csum_none),
	IONIC_LIF_STAT_DESC(rx_csum_complete),
	IONIC_LIF_STAT_DESC(rx_csum_error),
	IONIC_LIF_STAT_DESC(hw_tx_dropped),
	IONIC_LIF_STAT_DESC(hw_rx_dropped),
	IONIC_LIF_STAT_DESC(hw_rx_over_errors),
	IONIC_LIF_STAT_DESC(hw_rx_missed_errors),
	IONIC_LIF_STAT_DESC(hw_tx_पातed_errors),
पूर्ण;

अटल स्थिर काष्ठा ionic_stat_desc ionic_port_stats_desc[] = अणु
	IONIC_PORT_STAT_DESC(frames_rx_ok),
	IONIC_PORT_STAT_DESC(frames_rx_all),
	IONIC_PORT_STAT_DESC(frames_rx_bad_fcs),
	IONIC_PORT_STAT_DESC(frames_rx_bad_all),
	IONIC_PORT_STAT_DESC(octets_rx_ok),
	IONIC_PORT_STAT_DESC(octets_rx_all),
	IONIC_PORT_STAT_DESC(frames_rx_unicast),
	IONIC_PORT_STAT_DESC(frames_rx_multicast),
	IONIC_PORT_STAT_DESC(frames_rx_broadcast),
	IONIC_PORT_STAT_DESC(frames_rx_छोड़ो),
	IONIC_PORT_STAT_DESC(frames_rx_bad_length),
	IONIC_PORT_STAT_DESC(frames_rx_undersized),
	IONIC_PORT_STAT_DESC(frames_rx_oversized),
	IONIC_PORT_STAT_DESC(frames_rx_fragments),
	IONIC_PORT_STAT_DESC(frames_rx_jabber),
	IONIC_PORT_STAT_DESC(frames_rx_priछोड़ो),
	IONIC_PORT_STAT_DESC(frames_rx_stomped_crc),
	IONIC_PORT_STAT_DESC(frames_rx_too_दीर्घ),
	IONIC_PORT_STAT_DESC(frames_rx_vlan_good),
	IONIC_PORT_STAT_DESC(frames_rx_dropped),
	IONIC_PORT_STAT_DESC(frames_rx_less_than_64b),
	IONIC_PORT_STAT_DESC(frames_rx_64b),
	IONIC_PORT_STAT_DESC(frames_rx_65b_127b),
	IONIC_PORT_STAT_DESC(frames_rx_128b_255b),
	IONIC_PORT_STAT_DESC(frames_rx_256b_511b),
	IONIC_PORT_STAT_DESC(frames_rx_512b_1023b),
	IONIC_PORT_STAT_DESC(frames_rx_1024b_1518b),
	IONIC_PORT_STAT_DESC(frames_rx_1519b_2047b),
	IONIC_PORT_STAT_DESC(frames_rx_2048b_4095b),
	IONIC_PORT_STAT_DESC(frames_rx_4096b_8191b),
	IONIC_PORT_STAT_DESC(frames_rx_8192b_9215b),
	IONIC_PORT_STAT_DESC(frames_rx_other),
	IONIC_PORT_STAT_DESC(frames_tx_ok),
	IONIC_PORT_STAT_DESC(frames_tx_all),
	IONIC_PORT_STAT_DESC(frames_tx_bad),
	IONIC_PORT_STAT_DESC(octets_tx_ok),
	IONIC_PORT_STAT_DESC(octets_tx_total),
	IONIC_PORT_STAT_DESC(frames_tx_unicast),
	IONIC_PORT_STAT_DESC(frames_tx_multicast),
	IONIC_PORT_STAT_DESC(frames_tx_broadcast),
	IONIC_PORT_STAT_DESC(frames_tx_छोड़ो),
	IONIC_PORT_STAT_DESC(frames_tx_priछोड़ो),
	IONIC_PORT_STAT_DESC(frames_tx_vlan),
	IONIC_PORT_STAT_DESC(frames_tx_less_than_64b),
	IONIC_PORT_STAT_DESC(frames_tx_64b),
	IONIC_PORT_STAT_DESC(frames_tx_65b_127b),
	IONIC_PORT_STAT_DESC(frames_tx_128b_255b),
	IONIC_PORT_STAT_DESC(frames_tx_256b_511b),
	IONIC_PORT_STAT_DESC(frames_tx_512b_1023b),
	IONIC_PORT_STAT_DESC(frames_tx_1024b_1518b),
	IONIC_PORT_STAT_DESC(frames_tx_1519b_2047b),
	IONIC_PORT_STAT_DESC(frames_tx_2048b_4095b),
	IONIC_PORT_STAT_DESC(frames_tx_4096b_8191b),
	IONIC_PORT_STAT_DESC(frames_tx_8192b_9215b),
	IONIC_PORT_STAT_DESC(frames_tx_other),
	IONIC_PORT_STAT_DESC(frames_tx_pri_0),
	IONIC_PORT_STAT_DESC(frames_tx_pri_1),
	IONIC_PORT_STAT_DESC(frames_tx_pri_2),
	IONIC_PORT_STAT_DESC(frames_tx_pri_3),
	IONIC_PORT_STAT_DESC(frames_tx_pri_4),
	IONIC_PORT_STAT_DESC(frames_tx_pri_5),
	IONIC_PORT_STAT_DESC(frames_tx_pri_6),
	IONIC_PORT_STAT_DESC(frames_tx_pri_7),
	IONIC_PORT_STAT_DESC(frames_rx_pri_0),
	IONIC_PORT_STAT_DESC(frames_rx_pri_1),
	IONIC_PORT_STAT_DESC(frames_rx_pri_2),
	IONIC_PORT_STAT_DESC(frames_rx_pri_3),
	IONIC_PORT_STAT_DESC(frames_rx_pri_4),
	IONIC_PORT_STAT_DESC(frames_rx_pri_5),
	IONIC_PORT_STAT_DESC(frames_rx_pri_6),
	IONIC_PORT_STAT_DESC(frames_rx_pri_7),
	IONIC_PORT_STAT_DESC(tx_priछोड़ो_0_1us_count),
	IONIC_PORT_STAT_DESC(tx_priछोड़ो_1_1us_count),
	IONIC_PORT_STAT_DESC(tx_priछोड़ो_2_1us_count),
	IONIC_PORT_STAT_DESC(tx_priछोड़ो_3_1us_count),
	IONIC_PORT_STAT_DESC(tx_priछोड़ो_4_1us_count),
	IONIC_PORT_STAT_DESC(tx_priछोड़ो_5_1us_count),
	IONIC_PORT_STAT_DESC(tx_priछोड़ो_6_1us_count),
	IONIC_PORT_STAT_DESC(tx_priछोड़ो_7_1us_count),
	IONIC_PORT_STAT_DESC(rx_priछोड़ो_0_1us_count),
	IONIC_PORT_STAT_DESC(rx_priछोड़ो_1_1us_count),
	IONIC_PORT_STAT_DESC(rx_priछोड़ो_2_1us_count),
	IONIC_PORT_STAT_DESC(rx_priछोड़ो_3_1us_count),
	IONIC_PORT_STAT_DESC(rx_priछोड़ो_4_1us_count),
	IONIC_PORT_STAT_DESC(rx_priछोड़ो_5_1us_count),
	IONIC_PORT_STAT_DESC(rx_priछोड़ो_6_1us_count),
	IONIC_PORT_STAT_DESC(rx_priछोड़ो_7_1us_count),
	IONIC_PORT_STAT_DESC(rx_छोड़ो_1us_count),
	IONIC_PORT_STAT_DESC(frames_tx_truncated),
पूर्ण;

अटल स्थिर काष्ठा ionic_stat_desc ionic_tx_stats_desc[] = अणु
	IONIC_TX_STAT_DESC(pkts),
	IONIC_TX_STAT_DESC(bytes),
	IONIC_TX_STAT_DESC(clean),
	IONIC_TX_STAT_DESC(dma_map_err),
	IONIC_TX_STAT_DESC(linearize),
	IONIC_TX_STAT_DESC(frags),
	IONIC_TX_STAT_DESC(tso),
	IONIC_TX_STAT_DESC(tso_bytes),
	IONIC_TX_STAT_DESC(hwstamp_valid),
	IONIC_TX_STAT_DESC(hwstamp_invalid),
	IONIC_TX_STAT_DESC(csum_none),
	IONIC_TX_STAT_DESC(csum),
	IONIC_TX_STAT_DESC(vlan_inserted),
पूर्ण;

अटल स्थिर काष्ठा ionic_stat_desc ionic_rx_stats_desc[] = अणु
	IONIC_RX_STAT_DESC(pkts),
	IONIC_RX_STAT_DESC(bytes),
	IONIC_RX_STAT_DESC(dma_map_err),
	IONIC_RX_STAT_DESC(alloc_err),
	IONIC_RX_STAT_DESC(csum_none),
	IONIC_RX_STAT_DESC(csum_complete),
	IONIC_RX_STAT_DESC(csum_error),
	IONIC_RX_STAT_DESC(hwstamp_valid),
	IONIC_RX_STAT_DESC(hwstamp_invalid),
	IONIC_RX_STAT_DESC(dropped),
	IONIC_RX_STAT_DESC(vlan_stripped),
पूर्ण;

अटल स्थिर काष्ठा ionic_stat_desc ionic_txq_stats_desc[] = अणु
	IONIC_TX_Q_STAT_DESC(stop),
	IONIC_TX_Q_STAT_DESC(wake),
	IONIC_TX_Q_STAT_DESC(drop),
	IONIC_TX_Q_STAT_DESC(dbell_count),
पूर्ण;

अटल स्थिर काष्ठा ionic_stat_desc ionic_dbg_cq_stats_desc[] = अणु
	IONIC_CQ_STAT_DESC(compl_count),
पूर्ण;

अटल स्थिर काष्ठा ionic_stat_desc ionic_dbg_पूर्णांकr_stats_desc[] = अणु
	IONIC_INTR_STAT_DESC(rearm_count),
पूर्ण;

अटल स्थिर काष्ठा ionic_stat_desc ionic_dbg_napi_stats_desc[] = अणु
	IONIC_NAPI_STAT_DESC(poll_count),
पूर्ण;

#घोषणा IONIC_NUM_LIF_STATS ARRAY_SIZE(ionic_lअगर_stats_desc)
#घोषणा IONIC_NUM_PORT_STATS ARRAY_SIZE(ionic_port_stats_desc)
#घोषणा IONIC_NUM_TX_STATS ARRAY_SIZE(ionic_tx_stats_desc)
#घोषणा IONIC_NUM_RX_STATS ARRAY_SIZE(ionic_rx_stats_desc)
#घोषणा IONIC_NUM_TX_Q_STATS ARRAY_SIZE(ionic_txq_stats_desc)
#घोषणा IONIC_NUM_DBG_CQ_STATS ARRAY_SIZE(ionic_dbg_cq_stats_desc)
#घोषणा IONIC_NUM_DBG_INTR_STATS ARRAY_SIZE(ionic_dbg_पूर्णांकr_stats_desc)
#घोषणा IONIC_NUM_DBG_NAPI_STATS ARRAY_SIZE(ionic_dbg_napi_stats_desc)

#घोषणा MAX_Q(lअगर)   ((lअगर)->netdev->real_num_tx_queues)

अटल व्योम ionic_add_lअगर_txq_stats(काष्ठा ionic_lअगर *lअगर, पूर्णांक q_num,
				    काष्ठा ionic_lअगर_sw_stats *stats)
अणु
	काष्ठा ionic_tx_stats *txstats = &lअगर->txqstats[q_num];

	stats->tx_packets += txstats->pkts;
	stats->tx_bytes += txstats->bytes;
	stats->tx_tso += txstats->tso;
	stats->tx_tso_bytes += txstats->tso_bytes;
	stats->tx_csum_none += txstats->csum_none;
	stats->tx_csum += txstats->csum;
	stats->tx_hwstamp_valid += txstats->hwstamp_valid;
	stats->tx_hwstamp_invalid += txstats->hwstamp_invalid;
पूर्ण

अटल व्योम ionic_add_lअगर_rxq_stats(काष्ठा ionic_lअगर *lअगर, पूर्णांक q_num,
				    काष्ठा ionic_lअगर_sw_stats *stats)
अणु
	काष्ठा ionic_rx_stats *rxstats = &lअगर->rxqstats[q_num];

	stats->rx_packets += rxstats->pkts;
	stats->rx_bytes += rxstats->bytes;
	stats->rx_csum_none += rxstats->csum_none;
	stats->rx_csum_complete += rxstats->csum_complete;
	stats->rx_csum_error += rxstats->csum_error;
	stats->rx_hwstamp_valid += rxstats->hwstamp_valid;
	stats->rx_hwstamp_invalid += rxstats->hwstamp_invalid;
पूर्ण

अटल व्योम ionic_get_lअगर_stats(काष्ठा ionic_lअगर *lअगर,
				काष्ठा ionic_lअगर_sw_stats *stats)
अणु
	काष्ठा rtnl_link_stats64 ns;
	पूर्णांक q_num;

	स_रखो(stats, 0, माप(*stats));

	क्रम (q_num = 0; q_num < MAX_Q(lअगर); q_num++) अणु
		ionic_add_lअगर_txq_stats(lअगर, q_num, stats);
		ionic_add_lअगर_rxq_stats(lअगर, q_num, stats);
	पूर्ण

	अगर (lअगर->hwstamp_txq)
		ionic_add_lअगर_txq_stats(lअगर, lअगर->hwstamp_txq->q.index, stats);

	अगर (lअगर->hwstamp_rxq)
		ionic_add_lअगर_rxq_stats(lअगर, lअगर->hwstamp_rxq->q.index, stats);

	ionic_get_stats64(lअगर->netdev, &ns);
	stats->hw_tx_dropped = ns.tx_dropped;
	stats->hw_rx_dropped = ns.rx_dropped;
	stats->hw_rx_over_errors = ns.rx_over_errors;
	stats->hw_rx_missed_errors = ns.rx_missed_errors;
	stats->hw_tx_पातed_errors = ns.tx_पातed_errors;
पूर्ण

अटल u64 ionic_sw_stats_get_count(काष्ठा ionic_lअगर *lअगर)
अणु
	u64 total = 0, tx_queues = MAX_Q(lअगर), rx_queues = MAX_Q(lअगर);

	अगर (lअगर->hwstamp_txq)
		tx_queues += 1;

	अगर (lअगर->hwstamp_rxq)
		rx_queues += 1;

	total += IONIC_NUM_LIF_STATS;
	total += IONIC_NUM_PORT_STATS;

	total += tx_queues * IONIC_NUM_TX_STATS;
	total += rx_queues * IONIC_NUM_RX_STATS;

	अगर (test_bit(IONIC_LIF_F_UP, lअगर->state) &&
	    test_bit(IONIC_LIF_F_SW_DEBUG_STATS, lअगर->state)) अणु
		/* tx debug stats */
		total += tx_queues * (IONIC_NUM_DBG_CQ_STATS +
				      IONIC_NUM_TX_Q_STATS +
				      IONIC_NUM_DBG_INTR_STATS +
				      IONIC_MAX_NUM_SG_CNTR);

		/* rx debug stats */
		total += rx_queues * (IONIC_NUM_DBG_CQ_STATS +
				      IONIC_NUM_DBG_INTR_STATS +
				      IONIC_NUM_DBG_NAPI_STATS +
				      IONIC_MAX_NUM_NAPI_CNTR);
	पूर्ण

	वापस total;
पूर्ण

अटल व्योम ionic_sw_stats_get_tx_strings(काष्ठा ionic_lअगर *lअगर, u8 **buf,
					  पूर्णांक q_num)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < IONIC_NUM_TX_STATS; i++)
		ethtool_प्र_लिखो(buf, "tx_%d_%s", q_num,
				ionic_tx_stats_desc[i].name);

	अगर (!test_bit(IONIC_LIF_F_UP, lअगर->state) ||
	    !test_bit(IONIC_LIF_F_SW_DEBUG_STATS, lअगर->state))
		वापस;

	क्रम (i = 0; i < IONIC_NUM_TX_Q_STATS; i++)
		ethtool_प्र_लिखो(buf, "txq_%d_%s", q_num,
				ionic_txq_stats_desc[i].name);
	क्रम (i = 0; i < IONIC_NUM_DBG_CQ_STATS; i++)
		ethtool_प्र_लिखो(buf, "txq_%d_cq_%s", q_num,
				ionic_dbg_cq_stats_desc[i].name);
	क्रम (i = 0; i < IONIC_NUM_DBG_INTR_STATS; i++)
		ethtool_प्र_लिखो(buf, "txq_%d_intr_%s", q_num,
				ionic_dbg_पूर्णांकr_stats_desc[i].name);
	क्रम (i = 0; i < IONIC_MAX_NUM_SG_CNTR; i++)
		ethtool_प्र_लिखो(buf, "txq_%d_sg_cntr_%d", q_num, i);
पूर्ण

अटल व्योम ionic_sw_stats_get_rx_strings(काष्ठा ionic_lअगर *lअगर, u8 **buf,
					  पूर्णांक q_num)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < IONIC_NUM_RX_STATS; i++)
		ethtool_प्र_लिखो(buf, "rx_%d_%s", q_num,
				ionic_rx_stats_desc[i].name);

	अगर (!test_bit(IONIC_LIF_F_UP, lअगर->state) ||
	    !test_bit(IONIC_LIF_F_SW_DEBUG_STATS, lअगर->state))
		वापस;

	क्रम (i = 0; i < IONIC_NUM_DBG_CQ_STATS; i++)
		ethtool_प्र_लिखो(buf, "rxq_%d_cq_%s", q_num,
				ionic_dbg_cq_stats_desc[i].name);
	क्रम (i = 0; i < IONIC_NUM_DBG_INTR_STATS; i++)
		ethtool_प्र_लिखो(buf, "rxq_%d_intr_%s", q_num,
				ionic_dbg_पूर्णांकr_stats_desc[i].name);
	क्रम (i = 0; i < IONIC_NUM_DBG_NAPI_STATS; i++)
		ethtool_प्र_लिखो(buf, "rxq_%d_napi_%s", q_num,
				ionic_dbg_napi_stats_desc[i].name);
	क्रम (i = 0; i < IONIC_MAX_NUM_NAPI_CNTR; i++)
		ethtool_प्र_लिखो(buf, "rxq_%d_napi_work_done_%d", q_num, i);
पूर्ण

अटल व्योम ionic_sw_stats_get_strings(काष्ठा ionic_lअगर *lअगर, u8 **buf)
अणु
	पूर्णांक i, q_num;

	क्रम (i = 0; i < IONIC_NUM_LIF_STATS; i++)
		ethtool_प्र_लिखो(buf, ionic_lअगर_stats_desc[i].name);

	क्रम (i = 0; i < IONIC_NUM_PORT_STATS; i++)
		ethtool_प्र_लिखो(buf, ionic_port_stats_desc[i].name);

	क्रम (q_num = 0; q_num < MAX_Q(lअगर); q_num++)
		ionic_sw_stats_get_tx_strings(lअगर, buf, q_num);

	अगर (lअगर->hwstamp_txq)
		ionic_sw_stats_get_tx_strings(lअगर, buf, lअगर->hwstamp_txq->q.index);

	क्रम (q_num = 0; q_num < MAX_Q(lअगर); q_num++)
		ionic_sw_stats_get_rx_strings(lअगर, buf, q_num);

	अगर (lअगर->hwstamp_rxq)
		ionic_sw_stats_get_rx_strings(lअगर, buf, lअगर->hwstamp_rxq->q.index);
पूर्ण

अटल व्योम ionic_sw_stats_get_txq_values(काष्ठा ionic_lअगर *lअगर, u64 **buf,
					  पूर्णांक q_num)
अणु
	काष्ठा ionic_tx_stats *txstats;
	काष्ठा ionic_qcq *txqcq;
	पूर्णांक i;

	txstats = &lअगर->txqstats[q_num];

	क्रम (i = 0; i < IONIC_NUM_TX_STATS; i++) अणु
		**buf = IONIC_READ_STAT64(txstats, &ionic_tx_stats_desc[i]);
		(*buf)++;
	पूर्ण

	अगर (!test_bit(IONIC_LIF_F_UP, lअगर->state) ||
	    !test_bit(IONIC_LIF_F_SW_DEBUG_STATS, lअगर->state))
		वापस;

	txqcq = lअगर->txqcqs[q_num];
	क्रम (i = 0; i < IONIC_NUM_TX_Q_STATS; i++) अणु
		**buf = IONIC_READ_STAT64(&txqcq->q,
					  &ionic_txq_stats_desc[i]);
		(*buf)++;
	पूर्ण
	क्रम (i = 0; i < IONIC_NUM_DBG_CQ_STATS; i++) अणु
		**buf = IONIC_READ_STAT64(&txqcq->cq,
					  &ionic_dbg_cq_stats_desc[i]);
		(*buf)++;
	पूर्ण
	क्रम (i = 0; i < IONIC_NUM_DBG_INTR_STATS; i++) अणु
		**buf = IONIC_READ_STAT64(&txqcq->पूर्णांकr,
					  &ionic_dbg_पूर्णांकr_stats_desc[i]);
		(*buf)++;
	पूर्ण
	क्रम (i = 0; i < IONIC_NUM_DBG_NAPI_STATS; i++) अणु
		**buf = IONIC_READ_STAT64(&txqcq->napi_stats,
					  &ionic_dbg_napi_stats_desc[i]);
		(*buf)++;
	पूर्ण
	क्रम (i = 0; i < IONIC_MAX_NUM_NAPI_CNTR; i++) अणु
		**buf = txqcq->napi_stats.work_करोne_cntr[i];
		(*buf)++;
	पूर्ण
	क्रम (i = 0; i < IONIC_MAX_NUM_SG_CNTR; i++) अणु
		**buf = txstats->sg_cntr[i];
		(*buf)++;
	पूर्ण
पूर्ण

अटल व्योम ionic_sw_stats_get_rxq_values(काष्ठा ionic_lअगर *lअगर, u64 **buf,
					  पूर्णांक q_num)
अणु
	काष्ठा ionic_rx_stats *rxstats;
	काष्ठा ionic_qcq *rxqcq;
	पूर्णांक i;

	rxstats = &lअगर->rxqstats[q_num];

	क्रम (i = 0; i < IONIC_NUM_RX_STATS; i++) अणु
		**buf = IONIC_READ_STAT64(rxstats, &ionic_rx_stats_desc[i]);
		(*buf)++;
	पूर्ण

	अगर (!test_bit(IONIC_LIF_F_UP, lअगर->state) ||
	    !test_bit(IONIC_LIF_F_SW_DEBUG_STATS, lअगर->state))
		वापस;

	rxqcq = lअगर->rxqcqs[q_num];
	क्रम (i = 0; i < IONIC_NUM_DBG_CQ_STATS; i++) अणु
		**buf = IONIC_READ_STAT64(&rxqcq->cq,
					  &ionic_dbg_cq_stats_desc[i]);
		(*buf)++;
	पूर्ण
	क्रम (i = 0; i < IONIC_NUM_DBG_INTR_STATS; i++) अणु
		**buf = IONIC_READ_STAT64(&rxqcq->पूर्णांकr,
					  &ionic_dbg_पूर्णांकr_stats_desc[i]);
		(*buf)++;
	पूर्ण
	क्रम (i = 0; i < IONIC_NUM_DBG_NAPI_STATS; i++) अणु
		**buf = IONIC_READ_STAT64(&rxqcq->napi_stats,
					  &ionic_dbg_napi_stats_desc[i]);
		(*buf)++;
	पूर्ण
	क्रम (i = 0; i < IONIC_MAX_NUM_NAPI_CNTR; i++) अणु
		**buf = rxqcq->napi_stats.work_करोne_cntr[i];
		(*buf)++;
	पूर्ण
पूर्ण

अटल व्योम ionic_sw_stats_get_values(काष्ठा ionic_lअगर *lअगर, u64 **buf)
अणु
	काष्ठा ionic_port_stats *port_stats;
	काष्ठा ionic_lअगर_sw_stats lअगर_stats;
	पूर्णांक i, q_num;

	ionic_get_lअगर_stats(lअगर, &lअगर_stats);

	क्रम (i = 0; i < IONIC_NUM_LIF_STATS; i++) अणु
		**buf = IONIC_READ_STAT64(&lअगर_stats, &ionic_lअगर_stats_desc[i]);
		(*buf)++;
	पूर्ण

	port_stats = &lअगर->ionic->idev.port_info->stats;
	क्रम (i = 0; i < IONIC_NUM_PORT_STATS; i++) अणु
		**buf = IONIC_READ_STAT_LE64(port_stats,
					     &ionic_port_stats_desc[i]);
		(*buf)++;
	पूर्ण

	क्रम (q_num = 0; q_num < MAX_Q(lअगर); q_num++)
		ionic_sw_stats_get_txq_values(lअगर, buf, q_num);

	अगर (lअगर->hwstamp_txq)
		ionic_sw_stats_get_txq_values(lअगर, buf, lअगर->hwstamp_txq->q.index);

	क्रम (q_num = 0; q_num < MAX_Q(lअगर); q_num++)
		ionic_sw_stats_get_rxq_values(lअगर, buf, q_num);

	अगर (lअगर->hwstamp_rxq)
		ionic_sw_stats_get_rxq_values(lअगर, buf, lअगर->hwstamp_rxq->q.index);
पूर्ण

स्थिर काष्ठा ionic_stats_group_पूर्णांकf ionic_stats_groups[] = अणु
	/* SW Stats group */
	अणु
		.get_strings = ionic_sw_stats_get_strings,
		.get_values = ionic_sw_stats_get_values,
		.get_count = ionic_sw_stats_get_count,
	पूर्ण,
	/* Add more stat groups here */
पूर्ण;

स्थिर पूर्णांक ionic_num_stats_grps = ARRAY_SIZE(ionic_stats_groups);
