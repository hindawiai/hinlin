<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित _RTW_RECV_H_
#घोषणा _RTW_RECV_H_

#घोषणा NR_RECVBUFF (8)

#घोषणा NR_PREALLOC_RECV_SKB (8)

#घोषणा NR_RECVFRAME 256

#घोषणा RXFRAME_ALIGN	8
#घोषणा RXFRAME_ALIGN_SZ	(1<<RXFRAME_ALIGN)

#घोषणा DRVINFO_SZ	4 /*  unit is 8bytes */

#घोषणा MAX_RXFRAME_CNT	512
#घोषणा MAX_RX_NUMBLKS		(32)
#घोषणा RECVFRAME_HDR_ALIGN 128


#घोषणा PHY_RSSI_SLID_WIN_MAX				100
#घोषणा PHY_LINKQUALITY_SLID_WIN_MAX		20


#घोषणा SNAP_SIZE माप(काष्ठा ieee80211_snap_hdr)

#घोषणा RX_MPDU_QUEUE				0
#घोषणा RX_CMD_QUEUE				1
#घोषणा RX_MAX_QUEUE				2

#घोषणा MAX_SUBFRAME_COUNT	64

/* क्रम Rx reordering buffer control */
काष्ठा recv_reorder_ctrl अणु
	काष्ठा adapter	*padapter;
	u8 enable;
	u16 indicate_seq;/* wstart_b, init_value = 0xffff */
	u16 wend_b;
	u8 wsize_b;
	काष्ठा __queue pending_recvframe_queue;
	काष्ठा समयr_list reordering_ctrl_समयr;
पूर्ण;

काष्ठा	stainfo_rxcache	अणु
	u16 tid_rxseq[16];
/*
	अचिन्हित लघु	tid0_rxseq;
	अचिन्हित लघु	tid1_rxseq;
	अचिन्हित लघु	tid2_rxseq;
	अचिन्हित लघु	tid3_rxseq;
	अचिन्हित लघु	tid4_rxseq;
	अचिन्हित लघु	tid5_rxseq;
	अचिन्हित लघु	tid6_rxseq;
	अचिन्हित लघु	tid7_rxseq;
	अचिन्हित लघु	tid8_rxseq;
	अचिन्हित लघु	tid9_rxseq;
	अचिन्हित लघु	tid10_rxseq;
	अचिन्हित लघु	tid11_rxseq;
	अचिन्हित लघु	tid12_rxseq;
	अचिन्हित लघु	tid13_rxseq;
	अचिन्हित लघु	tid14_rxseq;
	अचिन्हित लघु	tid15_rxseq;
*/
पूर्ण;


काष्ठा संकेत_stat अणु
	u8 update_req;		/* used to indicate */
	u8 avg_val;		/* avg of valid elements */
	u32 total_num;		/* num of valid elements */
	u32 total_val;		/* sum of valid elements */
पूर्ण;

काष्ठा phy_info अणु
	u8 rx_pwd_ba11;

	u8 SignalQuality;	 /*  in 0-100 index. */
	s8		rx_mimo_संकेत_quality[4];	/* per-path's EVM */
	u8 RxMIMOEVMdbm[4];		/* per-path's EVM dbm */

	u8 rx_mimo_संकेत_strength[4];/*  in 0~100 index */

	u16 	Cfo_लघु[4];			/*  per-path's Cfo_लघु */
	u16 	Cfo_tail[4];			/*  per-path's Cfo_tail */

	s8		RxPower; /*  in dBm Translate from PWdB */
	s8		RecvSignalPower;/*  Real घातer in dBm क्रम this packet, no beautअगरication and aggregation. Keep this raw info to be used क्रम the other procedures. */
	u8 bt_rx_rssi_percentage;
	u8 SignalStrength; /*  in 0-100 index. */

	s8		RxPwr[4];				/* per-path's pwdb */
	u8 RxSNR[4];				/* per-path's SNR */
	u8 BandWidth;
	u8 btCoexPwrAdjust;
पूर्ण;

#अगर_घोषित DBG_RX_SIGNAL_DISPLAY_RAW_DATA
काष्ठा rx_raw_rssi अणु
	u8 data_rate;
	u8 pwdball;
	s8 pwr_all;

	u8 mimo_संकेत_strength[4];/*  in 0~100 index */
	u8 mimo_संकेत_quality[4];

	s8 ofdm_pwr[4];
	u8 ofdm_snr[4];

पूर्ण;
#पूर्ण_अगर

काष्ठा rx_pkt_attrib	अणु
	u16 pkt_len;
	u8 physt;
	u8 drvinfo_sz;
	u8 shअगरt_sz;
	u8 hdrlen; /* the WLAN Header Len */
	u8 to_fr_ds;
	u8 amsdu;
	u8 qos;
	u8 priority;
	u8 pw_save;
	u8 mdata;
	u16 seq_num;
	u8 frag_num;
	u8 mfrag;
	u8 order;
	u8 privacy; /* in frame_ctrl field */
	u8 bdecrypted;
	u8 encrypt; /* when 0 indicates no encryption; when non-zero, indicates the encryption algorithm */
	u8 iv_len;
	u8 icv_len;
	u8 crc_err;
	u8 icv_err;

	u16 eth_type;

	u8 dst[ETH_ALEN];
	u8 src[ETH_ALEN];
	u8 ta[ETH_ALEN];
	u8 ra[ETH_ALEN];
	u8 bssid[ETH_ALEN];

	u8 ack_policy;

	u8 key_index;

	u8 data_rate;
	u8 sgi;
	u8 pkt_rpt_type;
	u32 MacIDValidEntry[2];	/*  64 bits present 64 entry. */

/*
	u8 संकेत_qual;
	s8	rx_mimo_संकेत_qual[2];
	u8 संकेत_strength;
	u32 rx_pwd_ba11;
	s32	RecvSignalPower;
*/
	काष्ठा phy_info phy_info;
पूर्ण;


/* These definition is used क्रम Rx packet reordering. */
#घोषणा SN_LESS(a, b)		(((a - b) & 0x800) != 0)
#घोषणा SN_EQUAL(a, b)	(a == b)
/* define REORDER_WIN_SIZE	128 */
/* define REORDER_ENTRY_NUM	128 */
#घोषणा REORDER_WAIT_TIME	(50) /*  (ms) */

#घोषणा RECVBUFF_ALIGN_SZ 8

#घोषणा RXDESC_SIZE	24
#घोषणा RXDESC_OFFSET RXDESC_SIZE

काष्ठा recv_stat अणु
	__le32 rxdw0;
	__le32 rxdw1;
	__le32 rxdw2;
	__le32 rxdw3;
#अगर_अघोषित BUF_DESC_ARCH
	__le32 rxdw4;
	__le32 rxdw5;
#पूर्ण_अगर /* अगर BUF_DESC_ARCH is defined, rx_buf_desc occupy 4 द्विगुन words */
पूर्ण;

#घोषणा EOR BIT(30)

/*
accesser of recv_priv: rtw_recv_entry(dispatch / passive level); recv_thपढ़ो(passive) ; वापसpkt(dispatch)
; halt(passive) ;

using enter_critical section to protect
*/
काष्ठा recv_priv अणु
	spinlock_t	lock;
	काष्ठा __queue	मुक्त_recv_queue;
	काष्ठा __queue	recv_pending_queue;
	काष्ठा __queue	uc_swdec_pending_queue;
	u8 *pallocated_frame_buf;
	u8 *precv_frame_buf;
	uपूर्णांक मुक्त_recvframe_cnt;
	काष्ठा adapter	*adapter;
	u32 bIsAnyNonBEPkts;
	u64	rx_bytes;
	u64	rx_pkts;
	u64	rx_drop;
	uपूर्णांक  rx_icv_err;
	uपूर्णांक  rx_largepacket_crcerr;
	uपूर्णांक  rx_smallpacket_crcerr;
	uपूर्णांक  rx_middlepacket_crcerr;

	काष्ठा tasklet_काष्ठा irq_prepare_beacon_tasklet;
	काष्ठा tasklet_काष्ठा recv_tasklet;
	काष्ठा sk_buff_head मुक्त_recv_skb_queue;
	काष्ठा sk_buff_head rx_skb_queue;

	u8 *pallocated_recv_buf;
	u8 *precv_buf;    /*  4 alignment */
	काष्ठा __queue	मुक्त_recv_buf_queue;
	u32 मुक्त_recv_buf_queue_cnt;

	काष्ठा __queue	recv_buf_pending_queue;

	/* For display the phy inक्रमmation */
	u8 is_संकेत_dbg;	/*  क्रम debug */
	u8 संकेत_strength_dbg;	/*  क्रम debug */

	u8 संकेत_strength;
	u8 संकेत_qual;
	s8 rssi;	/* translate_percentage_to_dbm(ptarget_wlan->network.PhyInfo.SignalStrength); */
	#अगर_घोषित DBG_RX_SIGNAL_DISPLAY_RAW_DATA
	काष्ठा rx_raw_rssi raw_rssi_info;
	#पूर्ण_अगर
	/* s8 rxpwdb; */
	s16 noise;
	/* पूर्णांक RxSNRdB[2]; */
	/* s8 RxRssi[2]; */
	/* पूर्णांक FalseAlmCnt_all; */


	काष्ठा समयr_list संकेत_stat_समयr;
	u32 संकेत_stat_sampling_पूर्णांकerval;
	/* u32 संकेत_stat_converging_स्थिरant; */
	काष्ठा संकेत_stat संकेत_qual_data;
	काष्ठा संकेत_stat संकेत_strength_data;
पूर्ण;

#घोषणा rtw_set_संकेत_stat_समयr(recvpriv) _set_समयr(&(recvpriv)->संकेत_stat_समयr, (recvpriv)->संकेत_stat_sampling_पूर्णांकerval)

काष्ठा sta_recv_priv अणु

	spinlock_t	lock;
	चिन्हित पूर्णांक	option;

	/* काष्ठा __queue	blk_strms[MAX_RX_NUMBLKS]; */
	काष्ठा __queue defrag_q;	 /* keeping the fragment frame until defrag */

	काष्ठा	stainfo_rxcache rxcache;

	/* uपूर्णांक	sta_rx_bytes; */
	/* uपूर्णांक	sta_rx_pkts; */
	/* uपूर्णांक	sta_rx_fail; */

पूर्ण;


काष्ठा recv_buf अणु
	काष्ठा list_head list;

	spinlock_t recvbuf_lock;

	u32 ref_cnt;

	काष्ठा adapter *adapter;

	u8 *pbuf;
	u8 *pallocated_buf;

	u32 len;
	u8 *phead;
	u8 *pdata;
	u8 *ptail;
	u8 *pend;

	काष्ठा sk_buff	*pskb;
	u8 reuse;
पूर्ण;


/*
	head  ----->

		data  ----->

			payload

		tail  ----->


	end   ----->

	len = (अचिन्हित पूर्णांक)(tail - data);

*/
काष्ठा recv_frame_hdr अणु
	काष्ठा list_head	list;
	काष्ठा sk_buff	 *pkt;
	काष्ठा sk_buff	 *pkt_newalloc;

	काष्ठा adapter  *adapter;

	u8 fragcnt;

	पूर्णांक frame_tag;

	काष्ठा rx_pkt_attrib attrib;

	uपूर्णांक  len;
	u8 *rx_head;
	u8 *rx_data;
	u8 *rx_tail;
	u8 *rx_end;

	व्योम *precvbuf;


	/*  */
	काष्ठा sta_info *psta;

	/* क्रम A-MPDU Rx reordering buffer control */
	काष्ठा recv_reorder_ctrl *preorder_ctrl;
पूर्ण;


जोड़ recv_frame अणु
	जोड़अणु
		काष्ठा list_head list;
		काष्ठा recv_frame_hdr hdr;
		uपूर्णांक mem[RECVFRAME_HDR_ALIGN>>2];
	पूर्ण u;

	/* uपूर्णांक mem[MAX_RXSZ>>2]; */

पूर्ण;

क्रमागत अणु
	NORMAL_RX,/* Normal rx packet */
	TX_REPORT1,/* CCX */
	TX_REPORT2,/* TX RPT */
	HIS_REPORT,/*  USB HISR RPT */
	C2H_PACKET
पूर्ण;

बाह्य जोड़ recv_frame *_rtw_alloc_recvframe(काष्ठा __queue *pमुक्त_recv_queue);  /* get a मुक्त recv_frame from pमुक्त_recv_queue */
बाह्य जोड़ recv_frame *rtw_alloc_recvframe(काष्ठा __queue *pमुक्त_recv_queue);  /* get a मुक्त recv_frame from pमुक्त_recv_queue */
बाह्य पूर्णांक	 rtw_मुक्त_recvframe(जोड़ recv_frame *precvframe, काष्ठा __queue *pमुक्त_recv_queue);

#घोषणा rtw_dequeue_recvframe(queue) rtw_alloc_recvframe(queue)
बाह्य पूर्णांक _rtw_enqueue_recvframe(जोड़ recv_frame *precvframe, काष्ठा __queue *queue);
बाह्य पूर्णांक rtw_enqueue_recvframe(जोड़ recv_frame *precvframe, काष्ठा __queue *queue);

बाह्य व्योम rtw_मुक्त_recvframe_queue(काष्ठा __queue *pframequeue,  काष्ठा __queue *pमुक्त_recv_queue);
u32 rtw_मुक्त_uc_swdec_pending_queue(काष्ठा adapter *adapter);

चिन्हित पूर्णांक rtw_enqueue_recvbuf_to_head(काष्ठा recv_buf *precvbuf, काष्ठा __queue *queue);
चिन्हित पूर्णांक rtw_enqueue_recvbuf(काष्ठा recv_buf *precvbuf, काष्ठा __queue *queue);
काष्ठा recv_buf *rtw_dequeue_recvbuf(काष्ठा __queue *queue);

व्योम rtw_reordering_ctrl_समयout_handler(काष्ठा समयr_list *t);

अटल अंतरभूत u8 *get_rxmem(जोड़ recv_frame *precvframe)
अणु
	/* always वापस rx_head... */
	अगर (precvframe == शून्य)
		वापस शून्य;

	वापस precvframe->u.hdr.rx_head;
पूर्ण

अटल अंतरभूत u8 *get_recvframe_data(जोड़ recv_frame *precvframe)
अणु

	/* alwasy वापस rx_data */
	अगर (precvframe == शून्य)
		वापस शून्य;

	वापस precvframe->u.hdr.rx_data;

पूर्ण

अटल अंतरभूत u8 *recvframe_pull(जोड़ recv_frame *precvframe, चिन्हित पूर्णांक sz)
अणु
	/*  rx_data += sz; move rx_data sz bytes  hereafter */

	/* used क्रम extract sz bytes from rx_data, update rx_data and वापस the updated rx_data to the caller */


	अगर (precvframe == शून्य)
		वापस शून्य;


	precvframe->u.hdr.rx_data += sz;

	अगर (precvframe->u.hdr.rx_data > precvframe->u.hdr.rx_tail)
	अणु
		precvframe->u.hdr.rx_data -= sz;
		वापस शून्य;
	पूर्ण

	precvframe->u.hdr.len -= sz;

	वापस precvframe->u.hdr.rx_data;

पूर्ण

अटल अंतरभूत u8 *recvframe_put(जोड़ recv_frame *precvframe, चिन्हित पूर्णांक sz)
अणु
	/*  rx_tai += sz; move rx_tail sz bytes  hereafter */

	/* used क्रम append sz bytes from ptr to rx_tail, update rx_tail and वापस the updated rx_tail to the caller */
	/* after putting, rx_tail must be still larger than rx_end. */
	अचिन्हित अक्षर *prev_rx_tail;

	अगर (precvframe == शून्य)
		वापस शून्य;

	prev_rx_tail = precvframe->u.hdr.rx_tail;

	precvframe->u.hdr.rx_tail += sz;

	अगर (precvframe->u.hdr.rx_tail > precvframe->u.hdr.rx_end)
	अणु
		precvframe->u.hdr.rx_tail = prev_rx_tail;
		वापस शून्य;
	पूर्ण

	precvframe->u.hdr.len += sz;

	वापस precvframe->u.hdr.rx_tail;

पूर्ण



अटल अंतरभूत u8 *recvframe_pull_tail(जोड़ recv_frame *precvframe, चिन्हित पूर्णांक sz)
अणु
	/*  rmv data from rx_tail (by yitsen) */

	/* used क्रम extract sz bytes from rx_end, update rx_end and वापस the updated rx_end to the caller */
	/* after pulling, rx_end must be still larger than rx_data. */

	अगर (precvframe == शून्य)
		वापस शून्य;

	precvframe->u.hdr.rx_tail -= sz;

	अगर (precvframe->u.hdr.rx_tail < precvframe->u.hdr.rx_data)
	अणु
		precvframe->u.hdr.rx_tail += sz;
		वापस शून्य;
	पूर्ण

	precvframe->u.hdr.len -= sz;

	वापस precvframe->u.hdr.rx_tail;

पूर्ण

अटल अंतरभूत जोड़ recv_frame *rxmem_to_recvframe(u8 *rxmem)
अणु
	/* due to the design of 2048 bytes alignment of recv_frame, we can reference the जोड़ recv_frame */
	/* from any given member of recv_frame. */
	/*  rxmem indicates the any member/address in recv_frame */

	वापस (जोड़ recv_frame *)(((SIZE_PTR)rxmem >> RXFRAME_ALIGN) << RXFRAME_ALIGN);

पूर्ण

अटल अंतरभूत चिन्हित पूर्णांक get_recvframe_len(जोड़ recv_frame *precvframe)
अणु
	वापस precvframe->u.hdr.len;
पूर्ण


अटल अंतरभूत s32 translate_percentage_to_dbm(u32 SignalStrengthIndex)
अणु
	s32	SignalPower; /*  in dBm. */

	/*  Translate to dBm (x = 0.5y-95). */
	SignalPower = (s32)((SignalStrengthIndex + 1) >> 1);
	SignalPower -= 95;

	वापस SignalPower;
पूर्ण


काष्ठा sta_info;

बाह्य व्योम _rtw_init_sta_recv_priv(काष्ठा sta_recv_priv *psta_recvpriv);

बाह्य व्योम  mgt_dispatcher(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame);

#पूर्ण_अगर
