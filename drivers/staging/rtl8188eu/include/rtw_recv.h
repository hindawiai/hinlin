<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित _RTW_RECV_H_
#घोषणा _RTW_RECV_H_

#समावेश <osdep_service.h>
#समावेश <drv_types.h>

#घोषणा NR_RECVFRAME 256

#घोषणा RXFRAME_ALIGN	8
#घोषणा RXFRAME_ALIGN_SZ	(1 << RXFRAME_ALIGN)

#घोषणा MAX_RXFRAME_CNT	512
#घोषणा MAX_RX_NUMBLKS		(32)
#घोषणा RECVFRAME_HDR_ALIGN 128

#घोषणा SNAP_SIZE माप(काष्ठा ieee80211_snap_hdr)

#घोषणा MAX_SUBFRAME_COUNT	64

/* क्रम Rx reordering buffer control */
काष्ठा recv_reorder_ctrl अणु
	काष्ठा adapter	*padapter;
	bool enable;
	u16 indicate_seq;/* wstart_b, init_value=0xffff */
	u16 wend_b;
	u8 wsize_b;
	काष्ठा __queue pending_recvframe_queue;
	काष्ठा समयr_list reordering_ctrl_समयr;
पूर्ण;

काष्ठा	stainfo_rxcache	अणु
	u16	tid_rxseq[16];
/*
 *	अचिन्हित लघु	tid0_rxseq;
 *	अचिन्हित लघु	tid1_rxseq;
 *	अचिन्हित लघु	tid2_rxseq;
 *	अचिन्हित लघु	tid3_rxseq;
 *	अचिन्हित लघु	tid4_rxseq;
 *	अचिन्हित लघु	tid5_rxseq;
 *	अचिन्हित लघु	tid6_rxseq;
 *	अचिन्हित लघु	tid7_rxseq;
 *	अचिन्हित लघु	tid8_rxseq;
 *	अचिन्हित लघु	tid9_rxseq;
 *	अचिन्हित लघु	tid10_rxseq;
 *	अचिन्हित लघु	tid11_rxseq;
 *	अचिन्हित लघु	tid12_rxseq;
 *	अचिन्हित लघु	tid13_rxseq;
 *	अचिन्हित लघु	tid14_rxseq;
 *	अचिन्हित लघु	tid15_rxseq;
 */
पूर्ण;

काष्ठा संकेत_stat अणु
	u8	update_req;		/* used to indicate */
	u8	avg_val;		/* avg of valid elements */
	u32	total_num;		/* num of valid elements */
	u32	total_val;		/* sum of valid elements */
पूर्ण;

#घोषणा MAX_PATH_NUM_92CS		3

काष्ठा phy_info अणु
	u8	RxPWDBAll;
	u8	SignalQuality;	 /*  in 0-100 index. */
	u8	RxMIMOSignalQuality[MAX_PATH_NUM_92CS]; /* EVM */
	u8	RxMIMOSignalStrength[MAX_PATH_NUM_92CS];/*  in 0~100 index */
	s8	RxPower; /*  in dBm Translate from PWdB */
/*  Real घातer in dBm क्रम this packet, no beautअगरication and aggregation.
 * Keep this raw info to be used क्रम the other procedures.
 */
	s8	recvघातer;
	u8	BTRxRSSIPercentage;
	u8	SignalStrength; /*  in 0-100 index. */
	u8	RxPwr[MAX_PATH_NUM_92CS];/* per-path's pwdb */
	u8	RxSNR[MAX_PATH_NUM_92CS];/* per-path's SNR */
पूर्ण;

काष्ठा rx_pkt_attrib अणु
	u16	pkt_len;
	u8	physt;
	u8	drvinfo_sz;
	u8	shअगरt_sz;
	u8	hdrlen; /* the WLAN Header Len */
	u8	to_fr_ds;
	u8	amsdu;
	u8	qos;
	u8	priority;
	u8	pw_save;
	u8	mdata;
	u16	seq_num;
	u8	frag_num;
	u8	mfrag;
	u8	order;
	u8	privacy; /* in frame_ctrl field */
	u8	bdecrypted;
	u8	encrypt; /* when 0 indicate no encrypt. when non-zero,
			  * indicate the encrypt algorithm
			  */
	u8	iv_len;
	u8	icv_len;
	u8	crc_err;
	u8	icv_err;

	u16 eth_type;

	u8	dst[ETH_ALEN];
	u8	src[ETH_ALEN];
	u8	ta[ETH_ALEN];
	u8	ra[ETH_ALEN];
	u8	bssid[ETH_ALEN];

	u8 ack_policy;

	u8	key_index;

	u8	mcs_rate;
	u8	rxht;
	u8	sgi;
	u8	pkt_rpt_type;
	u32	MacIDValidEntry[2];	/*  64 bits present 64 entry. */

	काष्ठा phy_info phy_info;
पूर्ण;

/* These definition is used क्रम Rx packet reordering. */
#घोषणा SN_LESS(a, b)		(((a - b) & 0x800) != 0)
#घोषणा SN_EQUAL(a, b)	(a == b)
#घोषणा REORDER_WAIT_TIME	(50) /*  (ms) */

#घोषणा RXDESC_SIZE	24
#घोषणा RXDESC_OFFSET RXDESC_SIZE

काष्ठा recv_stat अणु
	__le32 rxdw0;
	__le32 rxdw1;
	__le32 rxdw2;
	__le32 rxdw3;
	__le32 rxdw4;
	__le32 rxdw5;
पूर्ण;

/*
 * accesser of recv_priv: rtw_recv_entry(dispatch / passive level);
 * recv_thपढ़ो(passive) ; वापसpkt(dispatch)
 * ; halt(passive) ;
 *
 * using enter_critical section to protect
 */
काष्ठा recv_priv अणु
	काष्ठा __queue मुक्त_recv_queue;
	काष्ठा __queue recv_pending_queue;
	काष्ठा __queue uc_swdec_pending_queue;
	व्योम *pallocated_frame_buf;
	काष्ठा adapter	*adapter;
	u32	bIsAnyNonBEPkts;
	u64	rx_bytes;
	u64	rx_pkts;
	u64	rx_drop;
	u64	last_rx_bytes;

	काष्ठा tasklet_काष्ठा irq_prepare_beacon_tasklet;
	काष्ठा tasklet_काष्ठा recv_tasklet;
	काष्ठा sk_buff_head मुक्त_recv_skb_queue;
	काष्ठा sk_buff_head rx_skb_queue;
	काष्ठा recv_buf *precv_buf;    /*  4 alignment */
	काष्ठा __queue मुक्त_recv_buf_queue;
	/* For display the phy inक्रमmation */
	s8 rssi;
	s8 rxpwdb;
	u8 संकेत_strength;
	u8 संकेत_qual;
	u8 noise;
	s8 RxRssi[2];

	काष्ठा समयr_list संकेत_stat_समयr;
	u32 संकेत_stat_sampling_पूर्णांकerval;
	काष्ठा संकेत_stat संकेत_qual_data;
	काष्ठा संकेत_stat संकेत_strength_data;
पूर्ण;

#घोषणा rtw_set_संकेत_stat_समयr(recvpriv)			\
	mod_समयr(&(recvpriv)->संकेत_stat_समयr, jअगरfies +	\
		  msecs_to_jअगरfies((recvpriv)->संकेत_stat_sampling_पूर्णांकerval))

काष्ठा sta_recv_priv अणु
	spinlock_t lock;
	पूर्णांक	option;
	काष्ठा __queue defrag_q; /* keeping the fragment frame until defrag */
	काष्ठा	stainfo_rxcache rxcache;
पूर्ण;

काष्ठा recv_buf अणु
	काष्ठा adapter *adapter;
	काष्ठा urb *purb;
	काष्ठा sk_buff *pskb;
	u8	reuse;
पूर्ण;

/*
 *	head  ----->
 *
 *		data  ----->
 *
 *			payload
 *
 *		tail  ----->
 *
 *
 *	end   ----->
 *
 *	len = (अचिन्हित पूर्णांक )(tail - data);
 *
 */
काष्ठा recv_frame अणु
	काष्ठा list_head list;
	काष्ठा sk_buff	 *pkt;
	काष्ठा adapter  *adapter;
	काष्ठा rx_pkt_attrib attrib;
	काष्ठा sta_info *psta;
	/* क्रम A-MPDU Rx reordering buffer control */
	काष्ठा recv_reorder_ctrl *preorder_ctrl;
पूर्ण;

काष्ठा recv_frame *_rtw_alloc_recvframe(काष्ठा __queue *pमुक्त_recv_queue);
काष्ठा recv_frame *rtw_alloc_recvframe(काष्ठा __queue *pमुक्त_recv_queue);
व्योम rtw_init_recvframe(काष्ठा recv_frame *precvframe,
			काष्ठा recv_priv *precvpriv);
पूर्णांक  rtw_मुक्त_recvframe(काष्ठा recv_frame *precvframe,
			काष्ठा __queue *pमुक्त_recv_queue);
#घोषणा rtw_dequeue_recvframe(queue) rtw_alloc_recvframe(queue)
पूर्णांक _rtw_enqueue_recvframe(काष्ठा recv_frame *precvframe,
			   काष्ठा __queue *queue);
पूर्णांक rtw_enqueue_recvframe(काष्ठा recv_frame *precvframe, काष्ठा __queue *queue);
व्योम rtw_मुक्त_recvframe_queue(काष्ठा __queue *pframequeue,
			      काष्ठा __queue *pमुक्त_recv_queue);
u32 rtw_मुक्त_uc_swdec_pending_queue(काष्ठा adapter *adapter);

व्योम rtw_reordering_ctrl_समयout_handler(काष्ठा समयr_list *t);

अटल अंतरभूत s32 translate_percentage_to_dbm(u32 sig_stren_index)
अणु
	s32	घातer; /*  in dBm. */

	/*  Translate to dBm (x=0.5y-95). */
	घातer = (s32)((sig_stren_index + 1) >> 1);
	घातer -= 95;

	वापस घातer;
पूर्ण

काष्ठा sta_info;

व्योम _rtw_init_sta_recv_priv(काष्ठा sta_recv_priv *psta_recvpriv);

व्योम  mgt_dispatcher(काष्ठा adapter *padapter, काष्ठा recv_frame *precv_frame);

#पूर्ण_अगर
