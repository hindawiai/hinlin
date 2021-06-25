<शैली गुरु>
/*
 * Copyright (c) 2008-2011 Atheros Communications Inc.
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

#अगर_अघोषित DEBUG_H
#घोषणा DEBUG_H

#समावेश "hw.h"
#समावेश "dfs_debug.h"

काष्ठा ath_txq;
काष्ठा ath_buf;
काष्ठा fft_sample_tlv;

#अगर_घोषित CONFIG_ATH9K_DEBUGFS
#घोषणा TX_STAT_INC(sc, q, c)	 करो अणु (sc)->debug.stats.txstats[q].c++; पूर्ण जबतक (0)
#घोषणा RX_STAT_INC(sc, c)	 करो अणु (sc)->debug.stats.rxstats.c++; पूर्ण जबतक (0)
#घोषणा RESET_STAT_INC(sc, type) करो अणु (sc)->debug.stats.reset[type]++; पूर्ण जबतक (0)
#घोषणा ANT_STAT_INC(sc, i, c)	 करो अणु (sc)->debug.stats.ant_stats[i].c++; पूर्ण जबतक (0)
#घोषणा ANT_LNA_INC(sc, i, c)	 करो अणु (sc)->debug.stats.ant_stats[i].lna_recv_cnt[c]++; पूर्ण जबतक (0)
#अन्यथा
#घोषणा TX_STAT_INC(sc, q, c)	 करो अणु (व्योम)(sc); पूर्ण जबतक (0)
#घोषणा RX_STAT_INC(sc, c)	 करो अणु (व्योम)(sc); पूर्ण जबतक (0)
#घोषणा RESET_STAT_INC(sc, type) करो अणु (व्योम)(sc); पूर्ण जबतक (0)
#घोषणा ANT_STAT_INC(sc, i, c)	 करो अणु (व्योम)(sc); पूर्ण जबतक (0)
#घोषणा ANT_LNA_INC(sc, i, c)	 करो अणु (व्योम)(sc); पूर्ण जबतक (0)
#पूर्ण_अगर

क्रमागत ath_reset_type अणु
	RESET_TYPE_BB_HANG,
	RESET_TYPE_BB_WATCHDOG,
	RESET_TYPE_FATAL_INT,
	RESET_TYPE_TX_ERROR,
	RESET_TYPE_TX_GTT,
	RESET_TYPE_TX_HANG,
	RESET_TYPE_PLL_HANG,
	RESET_TYPE_MAC_HANG,
	RESET_TYPE_BEACON_STUCK,
	RESET_TYPE_MCI,
	RESET_TYPE_CALIBRATION,
	RESET_TX_DMA_ERROR,
	RESET_RX_DMA_ERROR,
	__RESET_TYPE_MAX
पूर्ण;

#अगर_घोषित CONFIG_ATH9K_DEBUGFS

/**
 * काष्ठा ath_पूर्णांकerrupt_stats - Contains statistics about पूर्णांकerrupts
 * @total: Total no. of पूर्णांकerrupts generated so far
 * @rxok: RX with no errors
 * @rxlp: RX with low priority RX
 * @rxhp: RX with high priority, uapsd only
 * @rxeol: RX with no more RXDESC available
 * @rxorn: RX FIFO overrun
 * @txok: TX completed at the requested rate
 * @txurn: TX FIFO underrun
 * @mib: MIB regs reaching its threshold
 * @rxphyerr: RX with phy errors
 * @rx_keycache_miss: RX with key cache misses
 * @swba: Software Beacon Alert
 * @bmiss: Beacon Miss
 * @bnr: Beacon Not Ready
 * @cst: Carrier Sense TImeout
 * @gtt: Global TX Timeout
 * @tim: RX beacon TIM occurrence
 * @cabend: RX End of CAB traffic
 * @dtimsync: DTIM sync lossage
 * @dtim: RX Beacon with DTIM
 * @bb_watchकरोg: Baseband watchकरोg
 * @tsfoor: TSF out of range, indicates that the corrected TSF received
 * from a beacon dअगरfers from the PCU's पूर्णांकernal TSF by more than a
 * (programmable) threshold
 * @local_समयout: Internal bus समयout.
 * @mci: MCI पूर्णांकerrupt, specअगरic to MCI based BTCOEX chipsets
 * @gen_समयr: Generic hardware समयr पूर्णांकerrupt
 */
काष्ठा ath_पूर्णांकerrupt_stats अणु
	u32 total;
	u32 rxok;
	u32 rxlp;
	u32 rxhp;
	u32 rxeol;
	u32 rxorn;
	u32 txok;
	u32 txeol;
	u32 txurn;
	u32 mib;
	u32 rxphyerr;
	u32 rx_keycache_miss;
	u32 swba;
	u32 bmiss;
	u32 bnr;
	u32 cst;
	u32 gtt;
	u32 tim;
	u32 cabend;
	u32 dtimsync;
	u32 dtim;
	u32 bb_watchकरोg;
	u32 tsfoor;
	u32 mci;
	u32 gen_समयr;

	/* Sync-cause stats */
	u32 sync_cause_all;
	u32 sync_rtc_irq;
	u32 sync_mac_irq;
	u32 eeprom_illegal_access;
	u32 apb_समयout;
	u32 pci_mode_conflict;
	u32 host1_fatal;
	u32 host1_perr;
	u32 trcv_fअगरo_perr;
	u32 radm_cpl_ep;
	u32 radm_cpl_dllp_पात;
	u32 radm_cpl_tlp_पात;
	u32 radm_cpl_ecrc_err;
	u32 radm_cpl_समयout;
	u32 local_समयout;
	u32 pm_access;
	u32 mac_awake;
	u32 mac_asleep;
	u32 mac_sleep_access;
पूर्ण;


/**
 * काष्ठा ath_tx_stats - Statistics about TX
 * @tx_pkts_all:  No. of total frames transmitted, including ones that
	may have had errors.
 * @tx_bytes_all:  No. of total bytes transmitted, including ones that
	may have had errors.
 * @queued: Total MPDUs (non-aggr) queued
 * @completed: Total MPDUs (non-aggr) completed
 * @a_aggr: Total no. of aggregates queued
 * @a_queued_hw: Total AMPDUs queued to hardware
 * @a_completed: Total AMPDUs completed
 * @a_retries: No. of AMPDUs retried (SW)
 * @a_xretries: No. of AMPDUs dropped due to xretries
 * @txerr_filtered: No. of frames with TXERR_FILT flag set.
 * @fअगरo_underrun: FIFO underrun occurrences
	Valid only क्रम:
		- non-aggregate condition.
		- first packet of aggregate.
 * @xtxop: No. of frames filtered because of TXOP limit
 * @समयr_exp: Transmit समयr expiry
 * @desc_cfg_err: Descriptor configuration errors
 * @data_urn: TX data underrun errors
 * @delim_urn: TX delimiter underrun errors
 * @puttxbuf: Number of बार hardware was given txbuf to ग_लिखो.
 * @txstart:  Number of बार hardware was told to start tx.
 * @txprocdesc:  Number of बार tx descriptor was processed
 * @txfailed:  Out-of-memory or other errors in xmit path.
 */
काष्ठा ath_tx_stats अणु
	u32 tx_pkts_all;
	u32 tx_bytes_all;
	u32 queued;
	u32 completed;
	u32 xretries;
	u32 a_aggr;
	u32 a_queued_hw;
	u32 a_completed;
	u32 a_retries;
	u32 a_xretries;
	u32 txerr_filtered;
	u32 fअगरo_underrun;
	u32 xtxop;
	u32 समयr_exp;
	u32 desc_cfg_err;
	u32 data_underrun;
	u32 delim_underrun;
	u32 puttxbuf;
	u32 txstart;
	u32 txprocdesc;
	u32 txfailed;
पूर्ण;

/*
 * Various utility macros to prपूर्णांक TX/Queue counters.
 */
#घोषणा PR_QNUM(_n) sc->tx.txq_map[_n]->axq_qnum
#घोषणा TXSTATS sc->debug.stats.txstats
#घोषणा PR(str, elem)							\
	करो अणु								\
		seq_म_लिखो(file, "%s%13u%11u%10u%10u\n", str,		\
			   TXSTATS[PR_QNUM(IEEE80211_AC_BE)].elem,\
			   TXSTATS[PR_QNUM(IEEE80211_AC_BK)].elem,\
			   TXSTATS[PR_QNUM(IEEE80211_AC_VI)].elem,\
			   TXSTATS[PR_QNUM(IEEE80211_AC_VO)].elem); \
	पूर्ण जबतक(0)

काष्ठा ath_rx_rate_stats अणु
	काष्ठा अणु
		u32 ht20_cnt;
		u32 ht40_cnt;
		u32 sgi_cnt;
		u32 lgi_cnt;
	पूर्ण ht_stats[24];

	काष्ठा अणु
		u32 ofdm_cnt;
	पूर्ण ofdm_stats[8];

	काष्ठा अणु
		u32 cck_lp_cnt;
		u32 cck_sp_cnt;
	पूर्ण cck_stats[4];
पूर्ण;

काष्ठा ath_airसमय_stats अणु
	u32 rx_airसमय;
	u32 tx_airसमय;
पूर्ण;

#घोषणा ANT_MAIN 0
#घोषणा ANT_ALT  1

काष्ठा ath_antenna_stats अणु
	u32 recv_cnt;
	u32 rssi_avg;
	u32 lna_recv_cnt[4];
	u32 lna_attempt_cnt[4];
पूर्ण;

काष्ठा ath_stats अणु
	काष्ठा ath_पूर्णांकerrupt_stats istats;
	काष्ठा ath_tx_stats txstats[ATH9K_NUM_TX_QUEUES];
	काष्ठा ath_rx_stats rxstats;
	काष्ठा ath_dfs_stats dfs_stats;
	काष्ठा ath_antenna_stats ant_stats[2];
	u32 reset[__RESET_TYPE_MAX];
पूर्ण;

काष्ठा ath9k_debug अणु
	काष्ठा dentry *debugfs_phy;
	u32 regidx;
	काष्ठा ath_stats stats;
पूर्ण;

पूर्णांक ath9k_init_debug(काष्ठा ath_hw *ah);
व्योम ath9k_deinit_debug(काष्ठा ath_softc *sc);

व्योम ath_debug_stat_पूर्णांकerrupt(काष्ठा ath_softc *sc, क्रमागत ath9k_पूर्णांक status);
व्योम ath_debug_stat_tx(काष्ठा ath_softc *sc, काष्ठा ath_buf *bf,
		       काष्ठा ath_tx_status *ts, काष्ठा ath_txq *txq,
		       अचिन्हित पूर्णांक flags);
व्योम ath_debug_stat_rx(काष्ठा ath_softc *sc, काष्ठा ath_rx_status *rs);
पूर्णांक ath9k_get_et_sset_count(काष्ठा ieee80211_hw *hw,
			    काष्ठा ieee80211_vअगर *vअगर, पूर्णांक sset);
व्योम ath9k_get_et_stats(काष्ठा ieee80211_hw *hw,
			काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ethtool_stats *stats, u64 *data);
व्योम ath9k_get_et_strings(काष्ठा ieee80211_hw *hw,
			  काष्ठा ieee80211_vअगर *vअगर,
			  u32 sset, u8 *data);
व्योम ath9k_sta_add_debugfs(काष्ठा ieee80211_hw *hw,
			   काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta,
			   काष्ठा dentry *dir);
व्योम ath9k_debug_stat_ant(काष्ठा ath_softc *sc,
			  काष्ठा ath_hw_antcomb_conf *भाग_ant_conf,
			  पूर्णांक मुख्य_rssi_avg, पूर्णांक alt_rssi_avg);
व्योम ath9k_debug_sync_cause(काष्ठा ath_softc *sc, u32 sync_cause);

#अन्यथा

अटल अंतरभूत पूर्णांक ath9k_init_debug(काष्ठा ath_hw *ah)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ath9k_deinit_debug(काष्ठा ath_softc *sc)
अणु
पूर्ण
अटल अंतरभूत व्योम ath_debug_stat_पूर्णांकerrupt(काष्ठा ath_softc *sc,
					    क्रमागत ath9k_पूर्णांक status)
अणु
पूर्ण
अटल अंतरभूत व्योम ath_debug_stat_tx(काष्ठा ath_softc *sc,
				     काष्ठा ath_buf *bf,
				     काष्ठा ath_tx_status *ts,
				     काष्ठा ath_txq *txq,
				     अचिन्हित पूर्णांक flags)
अणु
पूर्ण
अटल अंतरभूत व्योम ath_debug_stat_rx(काष्ठा ath_softc *sc,
				     काष्ठा ath_rx_status *rs)
अणु
पूर्ण
अटल अंतरभूत व्योम ath9k_debug_stat_ant(काष्ठा ath_softc *sc,
					काष्ठा ath_hw_antcomb_conf *भाग_ant_conf,
					पूर्णांक मुख्य_rssi_avg, पूर्णांक alt_rssi_avg)
अणु

पूर्ण

अटल अंतरभूत व्योम
ath9k_debug_sync_cause(काष्ठा ath_softc *sc, u32 sync_cause)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_ATH9K_DEBUGFS */

#अगर_घोषित CONFIG_ATH9K_STATION_STATISTICS
व्योम ath_debug_rate_stats(काष्ठा ath_softc *sc,
			  काष्ठा ath_rx_status *rs,
			  काष्ठा sk_buff *skb);
#अन्यथा
अटल अंतरभूत व्योम ath_debug_rate_stats(काष्ठा ath_softc *sc,
					काष्ठा ath_rx_status *rs,
					काष्ठा sk_buff *skb)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_ATH9K_STATION_STATISTICS */

#पूर्ण_अगर /* DEBUG_H */
