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

#अगर_अघोषित ATH9K_H
#घोषणा ATH9K_H

#समावेश <linux/etherdevice.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/leds.h>
#समावेश <linux/completion.h>
#समावेश <linux/समय.स>
#समावेश <linux/hw_अक्रमom.h>

#समावेश "common.h"
#समावेश "debug.h"
#समावेश "mci.h"
#समावेश "dfs.h"

काष्ठा ath_node;
काष्ठा ath_vअगर;

बाह्य काष्ठा ieee80211_ops ath9k_ops;
बाह्य पूर्णांक ath9k_modparam_nohwcrypt;
बाह्य पूर्णांक ath9k_led_blink;
बाह्य bool is_ath9k_unloaded;
बाह्य पूर्णांक ath9k_use_chanctx;

/*************************/
/* Descriptor Management */
/*************************/

#घोषणा ATH_TXSTATUS_RING_SIZE 512

/* Macro to expand scalars to 64-bit objects */
#घोषणा	ito64(x) (माप(x) == 1) ?			\
	(((अचिन्हित दीर्घ दीर्घ पूर्णांक)(x)) & (0xff)) :	\
	(माप(x) == 2) ?				\
	(((अचिन्हित दीर्घ दीर्घ पूर्णांक)(x)) & 0xffff) :	\
	((माप(x) == 4) ?				\
	 (((अचिन्हित दीर्घ दीर्घ पूर्णांक)(x)) & 0xffffffff) : \
	 (अचिन्हित दीर्घ दीर्घ पूर्णांक)(x))

#घोषणा ATH_TXBUF_RESET(_bf) करो अणु				\
		(_bf)->bf_lastbf = शून्य;			\
		(_bf)->bf_next = शून्य;				\
		स_रखो(&((_bf)->bf_state), 0,			\
		       माप(काष्ठा ath_buf_state));		\
	पूर्ण जबतक (0)

#घोषणा	DS2PHYS(_dd, _ds)						\
	((_dd)->dd_desc_paddr + ((caddr_t)(_ds) - (caddr_t)(_dd)->dd_desc))
#घोषणा ATH_DESC_4KB_BOUND_CHECK(_daddr) ((((_daddr) & 0xFFF) > 0xF7F) ? 1 : 0)
#घोषणा ATH_DESC_4KB_BOUND_NUM_SKIPPED(_len) ((_len) / 4096)

काष्ठा ath_descdma अणु
	व्योम *dd_desc;
	dma_addr_t dd_desc_paddr;
	u32 dd_desc_len;
पूर्ण;

पूर्णांक ath_descdma_setup(काष्ठा ath_softc *sc, काष्ठा ath_descdma *dd,
		      काष्ठा list_head *head, स्थिर अक्षर *name,
		      पूर्णांक nbuf, पूर्णांक ndesc, bool is_tx);

/***********/
/* RX / TX */
/***********/

#घोषणा	ATH_TXQ_SETUP(sc, i) ((sc)->tx.txqsetup & (1<<i))

/* increment with wrap-around */
#घोषणा INCR(_l, _sz)   करो अणु			\
		(_l)++;				\
		(_l) &= ((_sz) - 1);		\
	पूर्ण जबतक (0)

#घोषणा ATH_RXBUF               512
#घोषणा ATH_TXBUF               512
#घोषणा ATH_TXBUF_RESERVE       5
#घोषणा ATH_TXMAXTRY            13
#घोषणा ATH_MAX_SW_RETRIES      30

#घोषणा TID_TO_WME_AC(_tid)				\
	((((_tid) == 0) || ((_tid) == 3)) ? IEEE80211_AC_BE :	\
	 (((_tid) == 1) || ((_tid) == 2)) ? IEEE80211_AC_BK :	\
	 (((_tid) == 4) || ((_tid) == 5)) ? IEEE80211_AC_VI :	\
	 IEEE80211_AC_VO)

#घोषणा ATH_AGGR_DELIM_SZ          4
#घोषणा ATH_AGGR_MINPLEN           256 /* in bytes, minimum packet length */
/* number of delimiters क्रम encryption padding */
#घोषणा ATH_AGGR_ENCRYPTDELIM      10
/* minimum h/w qdepth to be sustained to maximize aggregation */
#घोषणा ATH_AGGR_MIN_QDEPTH        2
/* minimum h/w qdepth क्रम non-aggregated traffic */
#घोषणा ATH_NON_AGGR_MIN_QDEPTH    8
#घोषणा ATH_HW_CHECK_POLL_INT      1000
#घोषणा ATH_TXFIFO_DEPTH           8
#घोषणा ATH_TX_ERROR               0x01

/* Stop tx traffic 1ms beक्रमe the GO goes away */
#घोषणा ATH_P2P_PS_STOP_TIME       1000

#घोषणा IEEE80211_SEQ_SEQ_SHIFT    4
#घोषणा IEEE80211_SEQ_MAX          4096
#घोषणा IEEE80211_WEP_IVLEN        3
#घोषणा IEEE80211_WEP_KIDLEN       1
#घोषणा IEEE80211_WEP_CRCLEN       4
#घोषणा IEEE80211_MAX_MPDU_LEN     (3840 + FCS_LEN +		\
				    (IEEE80211_WEP_IVLEN +	\
				     IEEE80211_WEP_KIDLEN +	\
				     IEEE80211_WEP_CRCLEN))

/* वापस whether a bit at index _n in biपंचांगap _bm is set
 * _sz is the size of the biपंचांगap  */
#घोषणा ATH_BA_ISSET(_bm, _n)  (((_n) < (WME_BA_BMP_SIZE)) &&		\
				((_bm)[(_n) >> 5] & (1 << ((_n) & 31))))

/* वापस block-ack biपंचांगap index given sequence and starting sequence */
#घोषणा ATH_BA_INDEX(_st, _seq) (((_seq) - (_st)) & (IEEE80211_SEQ_MAX - 1))

/* वापस the seqno क्रम _start + _offset */
#घोषणा ATH_BA_INDEX2SEQ(_seq, _offset) (((_seq) + (_offset)) & (IEEE80211_SEQ_MAX - 1))

/* वापसs delimiter padding required given the packet length */
#घोषणा ATH_AGGR_GET_NDELIM(_len)					\
       (((_len) >= ATH_AGGR_MINPLEN) ? 0 :                             \
        DIV_ROUND_UP(ATH_AGGR_MINPLEN - (_len), ATH_AGGR_DELIM_SZ))

#घोषणा BAW_WITHIN(_start, _bawsz, _seqno) \
	((((_seqno) - (_start)) & 4095) < (_bawsz))

#घोषणा ATH_AN_2_TID(_an, _tidno) ath_node_to_tid(_an, _tidno)

#घोषणा IS_HT_RATE(rate)   (rate & 0x80)
#घोषणा IS_CCK_RATE(rate)  ((rate >= 0x18) && (rate <= 0x1e))
#घोषणा IS_OFDM_RATE(rate) ((rate >= 0x8) && (rate <= 0xf))

क्रमागत अणु
       WLAN_RC_PHY_OFDM,
       WLAN_RC_PHY_CCK,
पूर्ण;

काष्ठा ath_txq अणु
	पूर्णांक mac80211_qnum; /* mac80211 queue number, -1 means not mac80211 Q */
	u32 axq_qnum; /* ath9k hardware queue number */
	व्योम *axq_link;
	काष्ठा list_head axq_q;
	spinlock_t axq_lock;
	u32 axq_depth;
	u32 axq_ampdu_depth;
	bool axq_tx_inprogress;
	काष्ठा list_head txq_fअगरo[ATH_TXFIFO_DEPTH];
	u8 txq_headidx;
	u8 txq_tailidx;
	पूर्णांक pending_frames;
	काष्ठा sk_buff_head complete_q;
पूर्ण;

काष्ठा ath_frame_info अणु
	काष्ठा ath_buf *bf;
	u16 framelen;
	s8 txq;
	u8 keyix;
	u8 rtscts_rate;
	u8 retries : 6;
	u8 dyn_smps : 1;
	u8 baw_tracked : 1;
	u8 tx_घातer;
	क्रमागत ath9k_key_type keytype:2;
पूर्ण;

काष्ठा ath_rxbuf अणु
	काष्ठा list_head list;
	काष्ठा sk_buff *bf_mpdu;
	व्योम *bf_desc;
	dma_addr_t bf_daddr;
	dma_addr_t bf_buf_addr;
पूर्ण;

/**
 * क्रमागत buffer_type - Buffer type flags
 *
 * @BUF_AMPDU: This buffer is an ampdu, as part of an aggregate (during TX)
 * @BUF_AGGR: Indicates whether the buffer can be aggregated
 *	(used in aggregation scheduling)
 */
क्रमागत buffer_type अणु
	BUF_AMPDU		= BIT(0),
	BUF_AGGR		= BIT(1),
पूर्ण;

#घोषणा bf_isampdu(bf)		(bf->bf_state.bf_type & BUF_AMPDU)
#घोषणा bf_isaggr(bf)		(bf->bf_state.bf_type & BUF_AGGR)

काष्ठा ath_buf_state अणु
	u8 bf_type;
	u8 bfs_paprd;
	u8 ndelim;
	bool stale;
	u16 seqno;
	अचिन्हित दीर्घ bfs_paprd_बारtamp;
पूर्ण;

काष्ठा ath_buf अणु
	काष्ठा list_head list;
	काष्ठा ath_buf *bf_lastbf;	/* last buf of this unit (a frame or
					   an aggregate) */
	काष्ठा ath_buf *bf_next;	/* next subframe in the aggregate */
	काष्ठा sk_buff *bf_mpdu;	/* enclosing frame काष्ठाure */
	व्योम *bf_desc;			/* भव addr of desc */
	dma_addr_t bf_daddr;		/* physical addr of desc */
	dma_addr_t bf_buf_addr;	/* physical addr of data buffer, क्रम DMA */
	काष्ठा ieee80211_tx_rate rates[4];
	काष्ठा ath_buf_state bf_state;
पूर्ण;

काष्ठा ath_atx_tid अणु
	काष्ठा list_head list;
	काष्ठा sk_buff_head retry_q;
	काष्ठा ath_node *an;
	काष्ठा ath_txq *txq;
	अचिन्हित दीर्घ tx_buf[BITS_TO_LONGS(ATH_TID_MAX_BUFS)];
	u16 seq_start;
	u16 seq_next;
	u16 baw_size;
	u8 tidno;
	पूर्णांक baw_head;   /* first un-acked tx buffer */
	पूर्णांक baw_tail;   /* next unused tx buffer slot */

	s8 bar_index;
	bool active;
	bool clear_ps_filter;
पूर्ण;

व्योम ath_tx_queue_tid(काष्ठा ath_softc *sc, काष्ठा ath_atx_tid *tid);

काष्ठा ath_node अणु
	काष्ठा ath_softc *sc;
	काष्ठा ieee80211_sta *sta; /* station काष्ठा we're part of */
	काष्ठा ieee80211_vअगर *vअगर; /* पूर्णांकerface with which we're associated */

	u16 maxampdu;
	u8 mpdudensity;
	s8 ps_key;

	bool sleeping;
	bool no_ps_filter;

#अगर_घोषित CONFIG_ATH9K_STATION_STATISTICS
	काष्ठा ath_rx_rate_stats rx_rate_stats;
#पूर्ण_अगर
	u8 key_idx[4];

	पूर्णांक ackto;
	काष्ठा list_head list;
पूर्ण;

काष्ठा ath_tx_control अणु
	काष्ठा ath_txq *txq;
	काष्ठा ath_node *an;
	काष्ठा ieee80211_sta *sta;
	u8 paprd;
पूर्ण;


/**
 * @txq_map:  Index is mac80211 queue number.  This is
 *  not necessarily the same as the hardware queue number
 *  (axq_qnum).
 */
काष्ठा ath_tx अणु
	u32 txqsetup;
	spinlock_t txbuflock;
	काष्ठा list_head txbuf;
	काष्ठा ath_txq txq[ATH9K_NUM_TX_QUEUES];
	काष्ठा ath_descdma txdma;
	काष्ठा ath_txq *txq_map[IEEE80211_NUM_ACS];
	काष्ठा ath_txq *uapsdq;
	u16 max_aggr_framelen[IEEE80211_NUM_ACS][4][32];
पूर्ण;

काष्ठा ath_rx_edma अणु
	काष्ठा sk_buff_head rx_fअगरo;
	u32 rx_fअगरo_hwsize;
पूर्ण;

काष्ठा ath_rx अणु
	u8 defant;
	u8 rxotherant;
	bool discard_next;
	u32 *rxlink;
	u32 num_pkts;
	काष्ठा list_head rxbuf;
	काष्ठा ath_descdma rxdma;
	काष्ठा ath_rx_edma rx_edma[ATH9K_RX_QUEUE_MAX];

	काष्ठा ath_rxbuf *buf_hold;
	काष्ठा sk_buff *frag;

	u32 ampdu_ref;
पूर्ण;

/*******************/
/* Channel Context */
/*******************/

काष्ठा ath_acq अणु
	काष्ठा list_head acq_new;
	काष्ठा list_head acq_old;
	spinlock_t lock;
पूर्ण;

काष्ठा ath_chanctx अणु
	काष्ठा cfg80211_chan_def chandef;
	काष्ठा list_head vअगरs;
	काष्ठा ath_acq acq[IEEE80211_NUM_ACS];
	पूर्णांक hw_queue_base;

	/* करो not dereference, use क्रम comparison only */
	काष्ठा ieee80211_vअगर *primary_sta;

	काष्ठा ath_beacon_config beacon;
	काष्ठा ath9k_hw_cal_data caldata;
	काष्ठा बारpec64 tsf_ts;
	u64 tsf_val;
	u32 last_beacon;

	पूर्णांक flush_समयout;
	u16 txघातer;
	u16 cur_txघातer;
	bool offchannel;
	bool stopped;
	bool active;
	bool asचिन्हित;
	bool चयन_after_beacon;

	लघु nvअगरs;
	लघु nvअगरs_asचिन्हित;
	अचिन्हित पूर्णांक rxfilter;
पूर्ण;

क्रमागत ath_chanctx_event अणु
	ATH_CHANCTX_EVENT_BEACON_PREPARE,
	ATH_CHANCTX_EVENT_BEACON_SENT,
	ATH_CHANCTX_EVENT_TSF_TIMER,
	ATH_CHANCTX_EVENT_BEACON_RECEIVED,
	ATH_CHANCTX_EVENT_AUTHORIZED,
	ATH_CHANCTX_EVENT_SWITCH,
	ATH_CHANCTX_EVENT_ASSIGN,
	ATH_CHANCTX_EVENT_UNASSIGN,
	ATH_CHANCTX_EVENT_CHANGE,
	ATH_CHANCTX_EVENT_ENABLE_MULTICHANNEL,
पूर्ण;

क्रमागत ath_chanctx_state अणु
	ATH_CHANCTX_STATE_IDLE,
	ATH_CHANCTX_STATE_WAIT_FOR_BEACON,
	ATH_CHANCTX_STATE_WAIT_FOR_TIMER,
	ATH_CHANCTX_STATE_SWITCH,
	ATH_CHANCTX_STATE_FORCE_ACTIVE,
पूर्ण;

काष्ठा ath_chanctx_sched अणु
	bool beacon_pending;
	bool beacon_adjust;
	bool offchannel_pending;
	bool रुको_चयन;
	bool क्रमce_noa_update;
	bool extend_असलence;
	bool mgd_prepare_tx;
	क्रमागत ath_chanctx_state state;
	u8 beacon_miss;

	u32 next_tbtt;
	u32 चयन_start_समय;
	अचिन्हित पूर्णांक offchannel_duration;
	अचिन्हित पूर्णांक channel_चयन_समय;

	/* backup, in हाल the hardware समयr fails */
	काष्ठा समयr_list समयr;
पूर्ण;

क्रमागत ath_offchannel_state अणु
	ATH_OFFCHANNEL_IDLE,
	ATH_OFFCHANNEL_PROBE_SEND,
	ATH_OFFCHANNEL_PROBE_WAIT,
	ATH_OFFCHANNEL_SUSPEND,
	ATH_OFFCHANNEL_ROC_START,
	ATH_OFFCHANNEL_ROC_WAIT,
	ATH_OFFCHANNEL_ROC_DONE,
पूर्ण;

क्रमागत ath_roc_complete_reason अणु
	ATH_ROC_COMPLETE_EXPIRE,
	ATH_ROC_COMPLETE_ABORT,
	ATH_ROC_COMPLETE_CANCEL,
पूर्ण;

काष्ठा ath_offchannel अणु
	काष्ठा ath_chanctx chan;
	काष्ठा समयr_list समयr;
	काष्ठा cfg80211_scan_request *scan_req;
	काष्ठा ieee80211_vअगर *scan_vअगर;
	पूर्णांक scan_idx;
	क्रमागत ath_offchannel_state state;
	काष्ठा ieee80211_channel *roc_chan;
	काष्ठा ieee80211_vअगर *roc_vअगर;
	पूर्णांक roc_duration;
	पूर्णांक duration;
पूर्ण;

अटल अंतरभूत काष्ठा ath_atx_tid *
ath_node_to_tid(काष्ठा ath_node *an, u8 tidno)
अणु
	काष्ठा ieee80211_sta *sta = an->sta;
	काष्ठा ieee80211_vअगर *vअगर = an->vअगर;
	काष्ठा ieee80211_txq *txq;

	BUG_ON(!vअगर);
	अगर (sta)
		txq = sta->txq[tidno % ARRAY_SIZE(sta->txq)];
	अन्यथा
		txq = vअगर->txq;

	वापस (काष्ठा ath_atx_tid *) txq->drv_priv;
पूर्ण

#घोषणा हाल_rtn_string(val) हाल val: वापस #val

#घोषणा ath_क्रम_each_chanctx(_sc, _ctx)                             \
	क्रम (ctx = &sc->chanctx[0];                                 \
	     ctx <= &sc->chanctx[ARRAY_SIZE(sc->chanctx) - 1];      \
	     ctx++)

व्योम ath_chanctx_init(काष्ठा ath_softc *sc);
व्योम ath_chanctx_set_channel(काष्ठा ath_softc *sc, काष्ठा ath_chanctx *ctx,
			     काष्ठा cfg80211_chan_def *chandef);

#अगर_घोषित CONFIG_ATH9K_CHANNEL_CONTEXT

अटल अंतरभूत काष्ठा ath_chanctx *
ath_chanctx_get(काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	काष्ठा ath_chanctx **ptr = (व्योम *) ctx->drv_priv;
	वापस *ptr;
पूर्ण

bool ath9k_is_chanctx_enabled(व्योम);
व्योम ath9k_fill_chanctx_ops(व्योम);
व्योम ath9k_init_channel_context(काष्ठा ath_softc *sc);
व्योम ath9k_offchannel_init(काष्ठा ath_softc *sc);
व्योम ath9k_deinit_channel_context(काष्ठा ath_softc *sc);
पूर्णांक ath9k_init_p2p(काष्ठा ath_softc *sc);
व्योम ath9k_deinit_p2p(काष्ठा ath_softc *sc);
व्योम ath9k_p2p_हटाओ_vअगर(काष्ठा ath_softc *sc,
			  काष्ठा ieee80211_vअगर *vअगर);
व्योम ath9k_p2p_beacon_sync(काष्ठा ath_softc *sc);
व्योम ath9k_p2p_bss_info_changed(काष्ठा ath_softc *sc,
				काष्ठा ieee80211_vअगर *vअगर);
व्योम ath9k_beacon_add_noa(काष्ठा ath_softc *sc, काष्ठा ath_vअगर *avp,
			  काष्ठा sk_buff *skb);
व्योम ath9k_p2p_ps_समयr(व्योम *priv);
व्योम ath9k_chanctx_wake_queues(काष्ठा ath_softc *sc, काष्ठा ath_chanctx *ctx);
व्योम ath9k_chanctx_stop_queues(काष्ठा ath_softc *sc, काष्ठा ath_chanctx *ctx);
व्योम ath_chanctx_check_active(काष्ठा ath_softc *sc, काष्ठा ath_chanctx *ctx);

व्योम ath_chanctx_beacon_recv_ev(काष्ठा ath_softc *sc,
				क्रमागत ath_chanctx_event ev);
व्योम ath_chanctx_beacon_sent_ev(काष्ठा ath_softc *sc,
				क्रमागत ath_chanctx_event ev);
व्योम ath_chanctx_event(काष्ठा ath_softc *sc, काष्ठा ieee80211_vअगर *vअगर,
		       क्रमागत ath_chanctx_event ev);
व्योम ath_chanctx_set_next(काष्ठा ath_softc *sc, bool क्रमce);
व्योम ath_offchannel_next(काष्ठा ath_softc *sc);
व्योम ath_scan_complete(काष्ठा ath_softc *sc, bool पात);
व्योम ath_roc_complete(काष्ठा ath_softc *sc,
		      क्रमागत ath_roc_complete_reason reason);
काष्ठा ath_chanctx* ath_is_go_chanctx_present(काष्ठा ath_softc *sc);

#अन्यथा

अटल अंतरभूत bool ath9k_is_chanctx_enabled(व्योम)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत व्योम ath9k_fill_chanctx_ops(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम ath9k_init_channel_context(काष्ठा ath_softc *sc)
अणु
पूर्ण
अटल अंतरभूत व्योम ath9k_offchannel_init(काष्ठा ath_softc *sc)
अणु
पूर्ण
अटल अंतरभूत व्योम ath9k_deinit_channel_context(काष्ठा ath_softc *sc)
अणु
पूर्ण
अटल अंतरभूत व्योम ath_chanctx_beacon_recv_ev(काष्ठा ath_softc *sc,
					      क्रमागत ath_chanctx_event ev)
अणु
पूर्ण
अटल अंतरभूत व्योम ath_chanctx_beacon_sent_ev(काष्ठा ath_softc *sc,
					      क्रमागत ath_chanctx_event ev)
अणु
पूर्ण
अटल अंतरभूत व्योम ath_chanctx_event(काष्ठा ath_softc *sc,
				     काष्ठा ieee80211_vअगर *vअगर,
				     क्रमागत ath_chanctx_event ev)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक ath9k_init_p2p(काष्ठा ath_softc *sc)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम ath9k_deinit_p2p(काष्ठा ath_softc *sc)
अणु
पूर्ण
अटल अंतरभूत व्योम ath9k_p2p_हटाओ_vअगर(काष्ठा ath_softc *sc,
					काष्ठा ieee80211_vअगर *vअगर)
अणु
पूर्ण
अटल अंतरभूत व्योम ath9k_p2p_beacon_sync(काष्ठा ath_softc *sc)
अणु
पूर्ण
अटल अंतरभूत व्योम ath9k_p2p_bss_info_changed(काष्ठा ath_softc *sc,
					      काष्ठा ieee80211_vअगर *vअगर)
अणु
पूर्ण
अटल अंतरभूत व्योम ath9k_beacon_add_noa(काष्ठा ath_softc *sc, काष्ठा ath_vअगर *avp,
					काष्ठा sk_buff *skb)
अणु
पूर्ण
अटल अंतरभूत व्योम ath9k_p2p_ps_समयr(काष्ठा ath_softc *sc)
अणु
पूर्ण
अटल अंतरभूत व्योम ath9k_chanctx_wake_queues(काष्ठा ath_softc *sc,
					     काष्ठा ath_chanctx *ctx)
अणु
पूर्ण
अटल अंतरभूत व्योम ath9k_chanctx_stop_queues(काष्ठा ath_softc *sc,
					     काष्ठा ath_chanctx *ctx)
अणु
पूर्ण
अटल अंतरभूत व्योम ath_chanctx_check_active(काष्ठा ath_softc *sc,
					    काष्ठा ath_chanctx *ctx)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_ATH9K_CHANNEL_CONTEXT */

अटल अंतरभूत व्योम ath_txq_lock(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq)
अणु
	spin_lock_bh(&txq->axq_lock);
पूर्ण
अटल अंतरभूत व्योम ath_txq_unlock(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq)
अणु
	spin_unlock_bh(&txq->axq_lock);
पूर्ण

व्योम ath_startrecv(काष्ठा ath_softc *sc);
bool ath_stoprecv(काष्ठा ath_softc *sc);
u32 ath_calcrxfilter(काष्ठा ath_softc *sc);
पूर्णांक ath_rx_init(काष्ठा ath_softc *sc, पूर्णांक nbufs);
व्योम ath_rx_cleanup(काष्ठा ath_softc *sc);
पूर्णांक ath_rx_tasklet(काष्ठा ath_softc *sc, पूर्णांक flush, bool hp);
काष्ठा ath_txq *ath_txq_setup(काष्ठा ath_softc *sc, पूर्णांक qtype, पूर्णांक subtype);
व्योम ath_txq_unlock_complete(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq);
व्योम ath_tx_cleanupq(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq);
bool ath_drain_all_txq(काष्ठा ath_softc *sc);
व्योम ath_draपूर्णांकxq(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq);
व्योम ath_tx_node_init(काष्ठा ath_softc *sc, काष्ठा ath_node *an);
व्योम ath_tx_node_cleanup(काष्ठा ath_softc *sc, काष्ठा ath_node *an);
व्योम ath_txq_schedule(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq);
व्योम ath_txq_schedule_all(काष्ठा ath_softc *sc);
पूर्णांक ath_tx_init(काष्ठा ath_softc *sc, पूर्णांक nbufs);
पूर्णांक ath_txq_update(काष्ठा ath_softc *sc, पूर्णांक qnum,
		   काष्ठा ath9k_tx_queue_info *q);
u32 ath_pkt_duration(काष्ठा ath_softc *sc, u8 rix, पूर्णांक pktlen,
		     पूर्णांक width, पूर्णांक half_gi, bool लघुPreamble);
व्योम ath_update_max_aggr_framelen(काष्ठा ath_softc *sc, पूर्णांक queue, पूर्णांक txop);
व्योम ath_assign_seq(काष्ठा ath_common *common, काष्ठा sk_buff *skb);
पूर्णांक ath_tx_start(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb,
		 काष्ठा ath_tx_control *txctl);
व्योम ath_tx_cabq(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		 काष्ठा sk_buff *skb);
व्योम ath_tx_tasklet(काष्ठा ath_softc *sc);
व्योम ath_tx_edma_tasklet(काष्ठा ath_softc *sc);
पूर्णांक ath_tx_aggr_start(काष्ठा ath_softc *sc, काष्ठा ieee80211_sta *sta,
		      u16 tid, u16 *ssn);
व्योम ath_tx_aggr_stop(काष्ठा ath_softc *sc, काष्ठा ieee80211_sta *sta, u16 tid);

व्योम ath_tx_aggr_wakeup(काष्ठा ath_softc *sc, काष्ठा ath_node *an);
व्योम ath_tx_aggr_sleep(काष्ठा ieee80211_sta *sta, काष्ठा ath_softc *sc,
		       काष्ठा ath_node *an);
व्योम ath9k_release_buffered_frames(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_sta *sta,
				   u16 tids, पूर्णांक nframes,
				   क्रमागत ieee80211_frame_release_type reason,
				   bool more_data);
व्योम ath9k_wake_tx_queue(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_txq *queue);

/********/
/* VIFs */
/********/

#घोषणा P2P_DEFAULT_CTWIN 10

काष्ठा ath_vअगर अणु
	काष्ठा list_head list;

	u16 seq_no;

	/* BSS info */
	u8 bssid[ETH_ALEN] __aligned(2);
	u16 aid;
	bool assoc;

	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा ath_node mcast_node;
	पूर्णांक av_bslot;
	__le64 tsf_adjust; /* TSF adjusपंचांगent क्रम staggered beacons */
	काष्ठा ath_buf *av_bcbuf;
	काष्ठा ath_chanctx *chanctx;

	/* P2P Client */
	काष्ठा ieee80211_noa_data noa;

	/* P2P GO */
	u8 noa_index;
	u32 offchannel_start;
	u32 offchannel_duration;

	/* These are used क्रम both periodic and one-shot */
	u32 noa_start;
	u32 noa_duration;
	bool periodic_noa;
	bool oneshot_noa;
पूर्ण;

काष्ठा ath9k_vअगर_iter_data अणु
	u8 hw_macaddr[ETH_ALEN]; /* address of the first vअगर */
	u8 mask[ETH_ALEN]; /* bssid mask */
	bool has_hw_macaddr;
	u8 slotसमय;
	bool beacons;

	पूर्णांक naps;      /* number of AP vअगरs */
	पूर्णांक nmeshes;   /* number of mesh vअगरs */
	पूर्णांक nstations; /* number of station vअगरs */
	पूर्णांक nadhocs;   /* number of adhoc vअगरs */
	पूर्णांक nocbs;     /* number of OCB vअगरs */
	पूर्णांक nbcnvअगरs;  /* number of beaconing vअगरs */
	काष्ठा ieee80211_vअगर *primary_beacon_vअगर;
	काष्ठा ieee80211_vअगर *primary_sta;
पूर्ण;

व्योम ath9k_calculate_iter_data(काष्ठा ath_softc *sc,
			       काष्ठा ath_chanctx *ctx,
			       काष्ठा ath9k_vअगर_iter_data *iter_data);
व्योम ath9k_calculate_summary_state(काष्ठा ath_softc *sc,
				   काष्ठा ath_chanctx *ctx);
व्योम ath9k_set_txघातer(काष्ठा ath_softc *sc, काष्ठा ieee80211_vअगर *vअगर);

/*******************/
/* Beacon Handling */
/*******************/

/*
 * Regardless of the number of beacons we stagger, (i.e. regardless of the
 * number of BSSIDs) अगर a given beacon करोes not go out even after रुकोing this
 * number of beacon पूर्णांकervals, the game's up.
 */
#घोषणा BSTUCK_THRESH           	9
#घोषणा	ATH_BCBUF               	8
#घोषणा ATH_DEFAULT_BINTVAL     	100 /* TU */
#घोषणा ATH_DEFAULT_BMISS_LIMIT 	10

#घोषणा TSF_TO_TU(_h,_l) \
	((((u32)(_h)) << 22) | (((u32)(_l)) >> 10))

काष्ठा ath_beacon अणु
	क्रमागत अणु
		OK,		/* no change needed */
		UPDATE,		/* update pending */
		COMMIT		/* beacon sent, commit change */
	पूर्ण updateslot;		/* slot समय update fsm */

	u32 beaconq;
	u32 bmisscnt;
	काष्ठा ieee80211_vअगर *bslot[ATH_BCBUF];
	पूर्णांक slotसमय;
	पूर्णांक slotupdate;
	काष्ठा ath_descdma bdma;
	काष्ठा ath_txq *cabq;
	काष्ठा list_head bbuf;

	bool tx_processed;
	bool tx_last;
पूर्ण;

व्योम ath9k_beacon_tasklet(काष्ठा tasklet_काष्ठा *t);
व्योम ath9k_beacon_config(काष्ठा ath_softc *sc, काष्ठा ieee80211_vअगर *मुख्य_vअगर,
			 bool beacons);
व्योम ath9k_beacon_assign_slot(काष्ठा ath_softc *sc, काष्ठा ieee80211_vअगर *vअगर);
व्योम ath9k_beacon_हटाओ_slot(काष्ठा ath_softc *sc, काष्ठा ieee80211_vअगर *vअगर);
व्योम ath9k_beacon_ensure_primary_slot(काष्ठा ath_softc *sc);
व्योम ath9k_set_beacon(काष्ठा ath_softc *sc);
bool ath9k_csa_is_finished(काष्ठा ath_softc *sc, काष्ठा ieee80211_vअगर *vअगर);
व्योम ath9k_csa_update(काष्ठा ath_softc *sc);

/*******************/
/* Link Monitoring */
/*******************/

#घोषणा ATH_STA_SHORT_CALINTERVAL 1000    /* 1 second */
#घोषणा ATH_AP_SHORT_CALINTERVAL  100     /* 100 ms */
#घोषणा ATH_ANI_POLLINTERVAL_OLD  100     /* 100 ms */
#घोषणा ATH_ANI_POLLINTERVAL_NEW  1000    /* 1000 ms */
#घोषणा ATH_LONG_CALINTERVAL_INT  1000    /* 1000 ms */
#घोषणा ATH_LONG_CALINTERVAL      30000   /* 30 seconds */
#घोषणा ATH_RESTART_CALINTERVAL   1200000 /* 20 minutes */
#घोषणा ATH_ANI_MAX_SKIP_COUNT    10
#घोषणा ATH_PAPRD_TIMEOUT         100 /* msecs */
#घोषणा ATH_PLL_WORK_INTERVAL     100

व्योम ath_hw_check_work(काष्ठा work_काष्ठा *work);
व्योम ath_reset_work(काष्ठा work_काष्ठा *work);
bool ath_hw_check(काष्ठा ath_softc *sc);
व्योम ath_hw_pll_work(काष्ठा work_काष्ठा *work);
व्योम ath_paprd_calibrate(काष्ठा work_काष्ठा *work);
व्योम ath_ani_calibrate(काष्ठा समयr_list *t);
व्योम ath_start_ani(काष्ठा ath_softc *sc);
व्योम ath_stop_ani(काष्ठा ath_softc *sc);
व्योम ath_check_ani(काष्ठा ath_softc *sc);
पूर्णांक ath_update_survey_stats(काष्ठा ath_softc *sc);
व्योम ath_update_survey_nf(काष्ठा ath_softc *sc, पूर्णांक channel);
व्योम ath9k_queue_reset(काष्ठा ath_softc *sc, क्रमागत ath_reset_type type);
व्योम ath_ps_full_sleep(काष्ठा समयr_list *t);
व्योम __ath9k_flush(काष्ठा ieee80211_hw *hw, u32 queues, bool drop,
		   bool sw_pending, bool समयout_override);

/**********/
/* BTCOEX */
/**********/

#घोषणा ATH_DUMP_BTCOEX(_s, _val)				\
	करो अणु							\
		len += scnम_लिखो(buf + len, size - len,		\
				 "%20s : %10d\n", _s, (_val));	\
	पूर्ण जबतक (0)

क्रमागत bt_op_flags अणु
	BT_OP_PRIORITY_DETECTED,
	BT_OP_SCAN,
पूर्ण;

काष्ठा ath_btcoex अणु
	spinlock_t btcoex_lock;
	काष्ठा समयr_list period_समयr; /* Timer क्रम BT period */
	काष्ठा समयr_list no_stomp_समयr;
	u32 bt_priority_cnt;
	अचिन्हित दीर्घ bt_priority_समय;
	अचिन्हित दीर्घ op_flags;
	पूर्णांक bt_stomp_type; /* Types of BT stomping */
	u32 btcoex_no_stomp; /* in msec */
	u32 btcoex_period; /* in msec */
	u32 btscan_no_stomp; /* in msec */
	u32 duty_cycle;
	u32 bt_रुको_समय;
	पूर्णांक rssi_count;
	काष्ठा ath_mci_profile mci;
	u8 stomp_audio;
पूर्ण;

#अगर_घोषित CONFIG_ATH9K_BTCOEX_SUPPORT
पूर्णांक ath9k_init_btcoex(काष्ठा ath_softc *sc);
व्योम ath9k_deinit_btcoex(काष्ठा ath_softc *sc);
व्योम ath9k_start_btcoex(काष्ठा ath_softc *sc);
व्योम ath9k_stop_btcoex(काष्ठा ath_softc *sc);
व्योम ath9k_btcoex_समयr_resume(काष्ठा ath_softc *sc);
व्योम ath9k_btcoex_समयr_छोड़ो(काष्ठा ath_softc *sc);
व्योम ath9k_btcoex_handle_पूर्णांकerrupt(काष्ठा ath_softc *sc, u32 status);
u16 ath9k_btcoex_aggr_limit(काष्ठा ath_softc *sc, u32 max_4ms_framelen);
व्योम ath9k_btcoex_stop_gen_समयr(काष्ठा ath_softc *sc);
पूर्णांक ath9k_dump_btcoex(काष्ठा ath_softc *sc, u8 *buf, u32 size);
#अन्यथा
अटल अंतरभूत पूर्णांक ath9k_init_btcoex(काष्ठा ath_softc *sc)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम ath9k_deinit_btcoex(काष्ठा ath_softc *sc)
अणु
पूर्ण
अटल अंतरभूत व्योम ath9k_start_btcoex(काष्ठा ath_softc *sc)
अणु
पूर्ण
अटल अंतरभूत व्योम ath9k_stop_btcoex(काष्ठा ath_softc *sc)
अणु
पूर्ण
अटल अंतरभूत व्योम ath9k_btcoex_handle_पूर्णांकerrupt(काष्ठा ath_softc *sc,
						 u32 status)
अणु
पूर्ण
अटल अंतरभूत u16 ath9k_btcoex_aggr_limit(काष्ठा ath_softc *sc,
					  u32 max_4ms_framelen)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम ath9k_btcoex_stop_gen_समयr(काष्ठा ath_softc *sc)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक ath9k_dump_btcoex(काष्ठा ath_softc *sc, u8 *buf, u32 size)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_ATH9K_BTCOEX_SUPPORT */

/********************/
/*   LED Control    */
/********************/

#घोषणा ATH_LED_PIN_DEF 		1
#घोषणा ATH_LED_PIN_9287		8
#घोषणा ATH_LED_PIN_9300		10
#घोषणा ATH_LED_PIN_9485		6
#घोषणा ATH_LED_PIN_9462		4

#अगर_घोषित CONFIG_MAC80211_LEDS
व्योम ath_init_leds(काष्ठा ath_softc *sc);
व्योम ath_deinit_leds(काष्ठा ath_softc *sc);
#अन्यथा
अटल अंतरभूत व्योम ath_init_leds(काष्ठा ath_softc *sc)
अणु
पूर्ण

अटल अंतरभूत व्योम ath_deinit_leds(काष्ठा ath_softc *sc)
अणु
पूर्ण
#पूर्ण_अगर

/************************/
/* Wake on Wireless LAN */
/************************/

#अगर_घोषित CONFIG_ATH9K_WOW
व्योम ath9k_init_wow(काष्ठा ieee80211_hw *hw);
व्योम ath9k_deinit_wow(काष्ठा ieee80211_hw *hw);
पूर्णांक ath9k_suspend(काष्ठा ieee80211_hw *hw,
		  काष्ठा cfg80211_wowlan *wowlan);
पूर्णांक ath9k_resume(काष्ठा ieee80211_hw *hw);
व्योम ath9k_set_wakeup(काष्ठा ieee80211_hw *hw, bool enabled);
#अन्यथा
अटल अंतरभूत व्योम ath9k_init_wow(काष्ठा ieee80211_hw *hw)
अणु
पूर्ण
अटल अंतरभूत व्योम ath9k_deinit_wow(काष्ठा ieee80211_hw *hw)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक ath9k_suspend(काष्ठा ieee80211_hw *hw,
				काष्ठा cfg80211_wowlan *wowlan)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक ath9k_resume(काष्ठा ieee80211_hw *hw)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम ath9k_set_wakeup(काष्ठा ieee80211_hw *hw, bool enabled)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_ATH9K_WOW */

/*******************************/
/* Antenna भागersity/combining */
/*******************************/

#घोषणा ATH_ANT_RX_CURRENT_SHIFT 4
#घोषणा ATH_ANT_RX_MAIN_SHIFT 2
#घोषणा ATH_ANT_RX_MASK 0x3

#घोषणा ATH_ANT_DIV_COMB_SHORT_SCAN_INTR 50
#घोषणा ATH_ANT_DIV_COMB_SHORT_SCAN_PKTCOUNT 0x100
#घोषणा ATH_ANT_DIV_COMB_MAX_PKTCOUNT 0x200
#घोषणा ATH_ANT_DIV_COMB_INIT_COUNT 95
#घोषणा ATH_ANT_DIV_COMB_MAX_COUNT 100
#घोषणा ATH_ANT_DIV_COMB_ALT_ANT_RATIO 30
#घोषणा ATH_ANT_DIV_COMB_ALT_ANT_RATIO2 20
#घोषणा ATH_ANT_DIV_COMB_ALT_ANT_RATIO_LOW_RSSI 50
#घोषणा ATH_ANT_DIV_COMB_ALT_ANT_RATIO2_LOW_RSSI 50

#घोषणा ATH_ANT_DIV_COMB_LNA1_DELTA_HI -4
#घोषणा ATH_ANT_DIV_COMB_LNA1_DELTA_MID -2
#घोषणा ATH_ANT_DIV_COMB_LNA1_DELTA_LOW 2

काष्ठा ath_ant_comb अणु
	u16 count;
	u16 total_pkt_count;
	bool scan;
	bool scan_not_start;
	पूर्णांक मुख्य_total_rssi;
	पूर्णांक alt_total_rssi;
	पूर्णांक alt_recv_cnt;
	पूर्णांक मुख्य_recv_cnt;
	पूर्णांक rssi_lna1;
	पूर्णांक rssi_lna2;
	पूर्णांक rssi_add;
	पूर्णांक rssi_sub;
	पूर्णांक rssi_first;
	पूर्णांक rssi_second;
	पूर्णांक rssi_third;
	पूर्णांक ant_ratio;
	पूर्णांक ant_ratio2;
	bool alt_good;
	पूर्णांक quick_scan_cnt;
	क्रमागत ath9k_ant_भाग_comb_lna_conf मुख्य_conf;
	क्रमागत ath9k_ant_भाग_comb_lna_conf first_quick_scan_conf;
	क्रमागत ath9k_ant_भाग_comb_lna_conf second_quick_scan_conf;
	bool first_ratio;
	bool second_ratio;
	अचिन्हित दीर्घ scan_start_समय;

	/*
	 * Card-specअगरic config values.
	 */
	पूर्णांक low_rssi_thresh;
	पूर्णांक fast_भाग_bias;
पूर्ण;

व्योम ath_ant_comb_scan(काष्ठा ath_softc *sc, काष्ठा ath_rx_status *rs);

/********************/
/* Main driver core */
/********************/

#घोषणा ATH9K_PCI_CUS198          0x0001
#घोषणा ATH9K_PCI_CUS230          0x0002
#घोषणा ATH9K_PCI_CUS217          0x0004
#घोषणा ATH9K_PCI_CUS252          0x0008
#घोषणा ATH9K_PCI_WOW             0x0010
#घोषणा ATH9K_PCI_BT_ANT_DIV      0x0020
#घोषणा ATH9K_PCI_D3_L1_WAR       0x0040
#घोषणा ATH9K_PCI_AR9565_1ANT     0x0080
#घोषणा ATH9K_PCI_AR9565_2ANT     0x0100
#घोषणा ATH9K_PCI_NO_PLL_PWRSAVE  0x0200
#घोषणा ATH9K_PCI_KILLER          0x0400
#घोषणा ATH9K_PCI_LED_ACT_HI      0x0800

/*
 * Default cache line size, in bytes.
 * Used when PCI device not fully initialized by bootrom/BIOS
*/
#घोषणा DEFAULT_CACHELINE       32
#घोषणा ATH_CABQ_READY_TIME     80      /* % of beacon पूर्णांकerval */
#घोषणा ATH_TXPOWER_MAX         100     /* .5 dBm units */
#घोषणा MAX_GTT_CNT             5

/* Powersave flags */
#घोषणा PS_WAIT_FOR_BEACON        BIT(0)
#घोषणा PS_WAIT_FOR_CAB           BIT(1)
#घोषणा PS_WAIT_FOR_PSPOLL_DATA   BIT(2)
#घोषणा PS_WAIT_FOR_TX_ACK        BIT(3)
#घोषणा PS_BEACON_SYNC            BIT(4)
#घोषणा PS_WAIT_FOR_ANI           BIT(5)

#घोषणा ATH9K_NUM_CHANCTX  2 /* supports 2 operating channels */

काष्ठा ath_softc अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा device *dev;

	काष्ठा survey_info *cur_survey;
	काष्ठा survey_info survey[ATH9K_NUM_CHANNELS];

	spinlock_t पूर्णांकr_lock;
	काष्ठा tasklet_काष्ठा पूर्णांकr_tq;
	काष्ठा tasklet_काष्ठा bcon_tasklet;
	काष्ठा ath_hw *sc_ah;
	व्योम __iomem *mem;
	पूर्णांक irq;
	spinlock_t sc_serial_rw;
	spinlock_t sc_pm_lock;
	spinlock_t sc_pcu_lock;
	काष्ठा mutex mutex;
	काष्ठा work_काष्ठा paprd_work;
	काष्ठा work_काष्ठा hw_reset_work;
	काष्ठा completion paprd_complete;
	रुको_queue_head_t tx_रुको;

#अगर_घोषित CONFIG_ATH9K_CHANNEL_CONTEXT
	काष्ठा work_काष्ठा chanctx_work;
	काष्ठा ath_gen_समयr *p2p_ps_समयr;
	काष्ठा ath_vअगर *p2p_ps_vअगर;
	काष्ठा ath_chanctx_sched sched;
	काष्ठा ath_offchannel offchannel;
	काष्ठा ath_chanctx *next_chan;
	काष्ठा completion go_beacon;
	काष्ठा बारpec64 last_event_समय;
#पूर्ण_अगर

	अचिन्हित दीर्घ driver_data;

	u8 gtt_cnt;
	u32 पूर्णांकrstatus;
	u16 ps_flags; /* PS_* */
	bool ps_enabled;
	bool ps_idle;
	लघु nbcnvअगरs;
	अचिन्हित दीर्घ ps_usecount;

	काष्ठा ath_rx rx;
	काष्ठा ath_tx tx;
	काष्ठा ath_beacon beacon;

	काष्ठा cfg80211_chan_def cur_chandef;
	काष्ठा ath_chanctx chanctx[ATH9K_NUM_CHANCTX];
	काष्ठा ath_chanctx *cur_chan;
	spinlock_t chan_lock;

#अगर_घोषित CONFIG_MAC80211_LEDS
	bool led_रेजिस्टरed;
	अक्षर led_name[32];
	काष्ठा led_classdev led_cdev;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ATH9K_DEBUGFS
	काष्ठा ath9k_debug debug;
#पूर्ण_अगर
	काष्ठा delayed_work hw_check_work;
	काष्ठा delayed_work hw_pll_work;
	काष्ठा समयr_list sleep_समयr;

#अगर_घोषित CONFIG_ATH9K_BTCOEX_SUPPORT
	काष्ठा ath_btcoex btcoex;
	काष्ठा ath_mci_coex mci_coex;
	काष्ठा work_काष्ठा mci_work;
#पूर्ण_अगर

	काष्ठा ath_descdma txsdma;

	काष्ठा ath_ant_comb ant_comb;
	u8 ant_tx, ant_rx;
	काष्ठा dfs_pattern_detector *dfs_detector;
	u64 dfs_prev_pulse_ts;
	u32 wow_enabled;

	काष्ठा ath_spec_scan_priv spec_priv;

	काष्ठा ieee80211_vअगर *tx99_vअगर;
	काष्ठा sk_buff *tx99_skb;
	bool tx99_state;
	s16 tx99_घातer;

#अगर_घोषित CONFIG_ATH9K_WOW
	u32 wow_पूर्णांकr_beक्रमe_sleep;
	bool क्रमce_wow;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ATH9K_HWRNG
	u32 rng_last;
	काष्ठा task_काष्ठा *rng_task;
#पूर्ण_अगर
पूर्ण;

/********/
/* TX99 */
/********/

#अगर_घोषित CONFIG_ATH9K_TX99
व्योम ath9k_tx99_init_debug(काष्ठा ath_softc *sc);
पूर्णांक ath9k_tx99_send(काष्ठा ath_softc *sc, काष्ठा sk_buff *skb,
		    काष्ठा ath_tx_control *txctl);
#अन्यथा
अटल अंतरभूत व्योम ath9k_tx99_init_debug(काष्ठा ath_softc *sc)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक ath9k_tx99_send(काष्ठा ath_softc *sc,
				  काष्ठा sk_buff *skb,
				  काष्ठा ath_tx_control *txctl)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_ATH9K_TX99 */

/***************************/
/* Ranकरोm Number Generator */
/***************************/
#अगर_घोषित CONFIG_ATH9K_HWRNG
व्योम ath9k_rng_start(काष्ठा ath_softc *sc);
व्योम ath9k_rng_stop(काष्ठा ath_softc *sc);
#अन्यथा
अटल अंतरभूत व्योम ath9k_rng_start(काष्ठा ath_softc *sc)
अणु
पूर्ण

अटल अंतरभूत व्योम ath9k_rng_stop(काष्ठा ath_softc *sc)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम ath_पढ़ो_cachesize(काष्ठा ath_common *common, पूर्णांक *csz)
अणु
	common->bus_ops->पढ़ो_cachesize(common, csz);
पूर्ण

व्योम ath9k_tasklet(काष्ठा tasklet_काष्ठा *t);
पूर्णांक ath_cabq_update(काष्ठा ath_softc *);
u8 ath9k_parse_mpdudensity(u8 mpdudensity);
irqवापस_t ath_isr(पूर्णांक irq, व्योम *dev);
पूर्णांक ath_reset(काष्ठा ath_softc *sc, काष्ठा ath9k_channel *hchan);
व्योम ath_cancel_work(काष्ठा ath_softc *sc);
व्योम ath_restart_work(काष्ठा ath_softc *sc);
पूर्णांक ath9k_init_device(u16 devid, काष्ठा ath_softc *sc,
		    स्थिर काष्ठा ath_bus_ops *bus_ops);
व्योम ath9k_deinit_device(काष्ठा ath_softc *sc);
व्योम ath9k_reload_chainmask_settings(काष्ठा ath_softc *sc);
u8 ath_txchainmask_reduction(काष्ठा ath_softc *sc, u8 chainmask, u32 rate);
व्योम ath_start_rfसमाप्त_poll(काष्ठा ath_softc *sc);
व्योम ath9k_rfसमाप्त_poll_state(काष्ठा ieee80211_hw *hw);
व्योम ath9k_ps_wakeup(काष्ठा ath_softc *sc);
व्योम ath9k_ps_restore(काष्ठा ath_softc *sc);

#अगर_घोषित CONFIG_ATH9K_PCI
पूर्णांक ath_pci_init(व्योम);
व्योम ath_pci_निकास(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक ath_pci_init(व्योम) अणु वापस 0; पूर्ण;
अटल अंतरभूत व्योम ath_pci_निकास(व्योम) अणुपूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ATH9K_AHB
पूर्णांक ath_ahb_init(व्योम);
व्योम ath_ahb_निकास(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक ath_ahb_init(व्योम) अणु वापस 0; पूर्ण;
अटल अंतरभूत व्योम ath_ahb_निकास(व्योम) अणुपूर्ण;
#पूर्ण_अगर

#पूर्ण_अगर /* ATH9K_H */
