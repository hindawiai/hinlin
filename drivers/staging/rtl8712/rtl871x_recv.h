<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _RTL871X_RECV_H_
#घोषणा _RTL871X_RECV_H_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"

#घोषणा NR_RECVFRAME 256

#घोषणा RXFRAME_ALIGN	8
#घोषणा RXFRAME_ALIGN_SZ	(1 << RXFRAME_ALIGN)

#घोषणा MAX_SUBFRAME_COUNT	64

/* क्रम Rx reordering buffer control */
काष्ठा recv_reorder_ctrl अणु
	काष्ठा _adapter	*padapter;
	u16 indicate_seq; /* =wstart_b, init_value=0xffff */
	u16 wend_b;
	u8 wsize_b;
	काष्ठा  __queue pending_recvframe_queue;
	काष्ठा समयr_list reordering_ctrl_समयr;
पूर्ण;

काष्ठा	stainfo_rxcache	अणु
	u16	tid_rxseq[16];
पूर्ण;

#घोषणा		PHY_RSSI_SLID_WIN_MAX			100
#घोषणा		PHY_LINKQUALITY_SLID_WIN_MAX		20

काष्ठा smooth_rssi_data अणु
	u32	elements[100];	/* array to store values */
	u32	index;		/* index to current array to store */
	u32	total_num;	/* num of valid elements */
	u32	total_val;	/* sum of valid elements */
पूर्ण;

काष्ठा rx_pkt_attrib अणु
	u8	amsdu;
	u8	order;
	u8	qos;
	u8	to_fr_ds;
	u8	frag_num;
	u16	seq_num;
	u8   pw_save;
	u8    mfrag;
	u8    mdata;
	u8	privacy; /* in frame_ctrl field */
	u8	bdecrypted;
	पूर्णांक	hdrlen;	 /* the WLAN Header Len */
	पूर्णांक	encrypt; /* 0 no encrypt. != 0 encrypt algorithm */
	पूर्णांक	iv_len;
	पूर्णांक	icv_len;
	पूर्णांक	priority;
	पूर्णांक	ack_policy;
	u8	crc_err;
	u8	dst[ETH_ALEN];
	u8	src[ETH_ALEN];
	u8	ta[ETH_ALEN];
	u8	ra[ETH_ALEN];
	u8	bssid[ETH_ALEN];
	u8	tcpchk_valid; /* 0: invalid, 1: valid */
	u8	ip_chkrpt; /* 0: incorrect, 1: correct */
	u8	tcp_chkrpt; /* 0: incorrect, 1: correct */
	u8	संकेत_qual;
	s8	rx_mimo_संकेत_qual[2];
	u8	mcs_rate;
	u8	htc;
	u8	संकेत_strength;
पूर्ण;

/*
 * accesser of recv_priv: recv_entry(dispatch / passive level);
 * recv_thपढ़ो(passive) ; वापसpkt(dispatch)
 * ; halt(passive) ;
 *
 * using enter_critical section to protect
 */
काष्ठा recv_priv अणु
	spinlock_t lock;
	काष्ठा  __queue	मुक्त_recv_queue;
	काष्ठा  __queue	recv_pending_queue;
	u8 *pallocated_frame_buf;
	u8 *precv_frame_buf;
	uपूर्णांक मुक्त_recvframe_cnt;
	काष्ठा _adapter	*adapter;
	uपूर्णांक	rx_bytes;
	uपूर्णांक	rx_pkts;
	uपूर्णांक	rx_drop;
	uपूर्णांक  rx_icv_err;
	uपूर्णांक  rx_largepacket_crcerr;
	uपूर्णांक  rx_smallpacket_crcerr;
	uपूर्णांक  rx_middlepacket_crcerr;
	u8  rx_pending_cnt;
	uपूर्णांक	ff_hwaddr;
	काष्ठा tasklet_काष्ठा recv_tasklet;
	काष्ठा sk_buff_head मुक्त_recv_skb_queue;
	काष्ठा sk_buff_head rx_skb_queue;
	u8 *pallocated_recv_buf;
	u8 *precv_buf;    /* 4 alignment */
	काष्ठा  __queue	मुक्त_recv_buf_queue;
	u32	मुक्त_recv_buf_queue_cnt;
	/* For the phy inक्रमmation */
	s8 rssi;
	u8 संकेत;
	u8 noise;
	u8 fw_rssi;
	काष्ठा smooth_rssi_data संकेत_qual_data;
	काष्ठा smooth_rssi_data संकेत_strength_data;
पूर्ण;

काष्ठा sta_recv_priv अणु
	spinlock_t lock;
	sपूर्णांक	option;
	काष्ठा  __queue defrag_q; /* keeping the fragment frame until defrag */
	काष्ठा	stainfo_rxcache rxcache;
	uपूर्णांक	sta_rx_bytes;
	uपूर्णांक	sta_rx_pkts;
	uपूर्णांक	sta_rx_fail;
पूर्ण;

#समावेश "rtl8712_recv.h"

/* get a मुक्त recv_frame from pमुक्त_recv_queue */
जोड़ recv_frame *r8712_alloc_recvframe(काष्ठा  __queue *pमुक्त_recv_queue);
व्योम r8712_मुक्त_recvframe(जोड़ recv_frame *precvframe,
			  काष्ठा  __queue *pमुक्त_recv_queue);
व्योम r8712_मुक्त_recvframe_queue(काष्ठा  __queue *pframequeue,
				 काष्ठा  __queue *pमुक्त_recv_queue);
पूर्णांक r8712_wlanhdr_to_ethhdr(जोड़ recv_frame *precvframe);
पूर्णांक recv_func(काष्ठा _adapter *padapter, व्योम *pcontext);

अटल अंतरभूत u8 *get_rxmem(जोड़ recv_frame *precvframe)
अणु
	/* always वापस rx_head... */
	अगर (!precvframe)
		वापस शून्य;
	वापस precvframe->u.hdr.rx_head;
पूर्ण

अटल अंतरभूत u8 *get_recvframe_data(जोड़ recv_frame *precvframe)
अणु
	/* always वापस rx_data */
	अगर (!precvframe)
		वापस शून्य;
	वापस precvframe->u.hdr.rx_data;
पूर्ण

अटल अंतरभूत u8 *recvframe_pull(जोड़ recv_frame *precvframe, sपूर्णांक sz)
अणु
	/* used क्रम extract sz bytes from rx_data, update rx_data and वापस
	 * the updated rx_data to the caller
	 */
	अगर (!precvframe)
		वापस शून्य;
	precvframe->u.hdr.rx_data += sz;
	अगर (precvframe->u.hdr.rx_data > precvframe->u.hdr.rx_tail) अणु
		precvframe->u.hdr.rx_data -= sz;
		वापस शून्य;
	पूर्ण
	precvframe->u.hdr.len -= sz;
	वापस precvframe->u.hdr.rx_data;
पूर्ण

अटल अंतरभूत u8 *recvframe_put(जोड़ recv_frame *precvframe, sपूर्णांक sz)
अणु
	/* used क्रम append sz bytes from ptr to rx_tail, update rx_tail and
	 * वापस the updated rx_tail to the caller
	 * after putting, rx_tail must be still larger than rx_end.
	 */
	अगर (!precvframe)
		वापस शून्य;
	precvframe->u.hdr.rx_tail += sz;
	अगर (precvframe->u.hdr.rx_tail > precvframe->u.hdr.rx_end) अणु
		precvframe->u.hdr.rx_tail -= sz;
		वापस शून्य;
	पूर्ण
	precvframe->u.hdr.len += sz;
	वापस precvframe->u.hdr.rx_tail;
पूर्ण

अटल अंतरभूत u8 *recvframe_pull_tail(जोड़ recv_frame *precvframe, sपूर्णांक sz)
अणु
	/* rmv data from rx_tail (by yitsen)
	 * used क्रम extract sz bytes from rx_end, update rx_end and वापस the
	 * updated rx_end to the caller
	 * after pulling, rx_end must be still larger than rx_data.
	 */
	अगर (!precvframe)
		वापस शून्य;
	precvframe->u.hdr.rx_tail -= sz;
	अगर (precvframe->u.hdr.rx_tail < precvframe->u.hdr.rx_data) अणु
		precvframe->u.hdr.rx_tail += sz;
		वापस शून्य;
	पूर्ण
	precvframe->u.hdr.len -= sz;
	वापस precvframe->u.hdr.rx_tail;
पूर्ण

काष्ठा sta_info;

व्योम	_r8712_init_sta_recv_priv(काष्ठा sta_recv_priv *psta_recvpriv);
sपूर्णांक r8712_recvframe_chkmic(काष्ठा _adapter *adapter,
			    जोड़ recv_frame *precvframe);
जोड़ recv_frame *r8712_decryptor(काष्ठा _adapter *adapter,
				  जोड़ recv_frame *precv_frame);
जोड़ recv_frame *r8712_recvframe_chk_defrag(काष्ठा _adapter *adapter,
					     जोड़ recv_frame *precv_frame);
पूर्णांक r8712_validate_recv_frame(काष्ठा _adapter *adapter,
			      जोड़ recv_frame *precv_frame);
जोड़ recv_frame *r8712_portctrl(काष्ठा _adapter *adapter,
				 जोड़ recv_frame *precv_frame);

#पूर्ण_अगर

