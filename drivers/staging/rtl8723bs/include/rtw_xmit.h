<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित _RTW_XMIT_H_
#घोषणा _RTW_XMIT_H_

#समावेश <linux/completion.h>

#घोषणा MAX_XMITBUF_SZ	(20480)	/*  20k */

#घोषणा NR_XMITBUFF	(16)

#घोषणा XMITBUF_ALIGN_SZ 512

/*  xmit extension buff defination */
#घोषणा MAX_XMIT_EXTBUF_SZ	(1536)
#घोषणा NR_XMIT_EXTBUFF	(32)

#घोषणा MAX_CMDBUF_SZ	(5120)	/* 4096) */

#घोषणा MAX_NUMBLKS		(1)

#घोषणा XMIT_VO_QUEUE (0)
#घोषणा XMIT_VI_QUEUE (1)
#घोषणा XMIT_BE_QUEUE (2)
#घोषणा XMIT_BK_QUEUE (3)

#घोषणा VO_QUEUE_INX		0
#घोषणा VI_QUEUE_INX		1
#घोषणा BE_QUEUE_INX		2
#घोषणा BK_QUEUE_INX		3
#घोषणा BCN_QUEUE_INX		4
#घोषणा MGT_QUEUE_INX		5
#घोषणा HIGH_QUEUE_INX		6
#घोषणा TXCMD_QUEUE_INX	7

#घोषणा HW_QUEUE_ENTRY	8

#घोषणा WEP_IV(pattrib_iv, करोt11txpn, keyidx)\
करो अणु\
	pattrib_iv[0] = करोt11txpn._byte_.TSC0;\
	pattrib_iv[1] = करोt11txpn._byte_.TSC1;\
	pattrib_iv[2] = करोt11txpn._byte_.TSC2;\
	pattrib_iv[3] = ((keyidx & 0x3)<<6);\
	करोt11txpn.val = (करोt11txpn.val == 0xffffff) ? 0 : (करोt11txpn.val + 1);\
पूर्ण जबतक (0)


#घोषणा TKIP_IV(pattrib_iv, करोt11txpn, keyidx)\
करो अणु\
	pattrib_iv[0] = करोt11txpn._byte_.TSC1;\
	pattrib_iv[1] = (करोt11txpn._byte_.TSC1 | 0x20) & 0x7f;\
	pattrib_iv[2] = करोt11txpn._byte_.TSC0;\
	pattrib_iv[3] = BIT(5) | ((keyidx & 0x3)<<6);\
	pattrib_iv[4] = करोt11txpn._byte_.TSC2;\
	pattrib_iv[5] = करोt11txpn._byte_.TSC3;\
	pattrib_iv[6] = करोt11txpn._byte_.TSC4;\
	pattrib_iv[7] = करोt11txpn._byte_.TSC5;\
	करोt11txpn.val = करोt11txpn.val == 0xffffffffffffULL ? 0 : (करोt11txpn.val + 1);\
पूर्ण जबतक (0)

#घोषणा AES_IV(pattrib_iv, करोt11txpn, keyidx)\
करो अणु\
	pattrib_iv[0] = करोt11txpn._byte_.TSC0;\
	pattrib_iv[1] = करोt11txpn._byte_.TSC1;\
	pattrib_iv[2] = 0;\
	pattrib_iv[3] = BIT(5) | ((keyidx & 0x3)<<6);\
	pattrib_iv[4] = करोt11txpn._byte_.TSC2;\
	pattrib_iv[5] = करोt11txpn._byte_.TSC3;\
	pattrib_iv[6] = करोt11txpn._byte_.TSC4;\
	pattrib_iv[7] = करोt11txpn._byte_.TSC5;\
	करोt11txpn.val = करोt11txpn.val == 0xffffffffffffULL ? 0 : (करोt11txpn.val + 1);\
पूर्ण जबतक (0)


#घोषणा HWXMIT_ENTRY	4

/*  For Buffer Descriptor ring architecture */
#घोषणा TXDESC_SIZE 40

#घोषणा TXDESC_OFFSET TXDESC_SIZE

#घोषणा TXDESC_40_BYTES

काष्ठा tx_desc अणु
	__le32 txdw0;
	__le32 txdw1;
	__le32 txdw2;
	__le32 txdw3;
	__le32 txdw4;
	__le32 txdw5;
	__le32 txdw6;
	__le32 txdw7;

#अगर defined(TXDESC_40_BYTES) || defined(TXDESC_64_BYTES)
	__le32 txdw8;
	__le32 txdw9;
#पूर्ण_अगर /*  TXDESC_40_BYTES */

#अगर_घोषित TXDESC_64_BYTES
	__le32 txdw10;
	__le32 txdw11;

	/*  2008/05/15 MH Because PCIE HW memory R/W 4K limit. And now,  our descriptor */
	/*  size is 40 bytes. If you use more than 102 descriptor(103*40>4096), HW will execute */
	/*  memoryR/W CRC error. And then all DMA fetch will fail. We must decrease descriptor */
	/*  number or enlarge descriptor size as 64 bytes. */
	__le32 txdw12;
	__le32 txdw13;
	__le32 txdw14;
	__le32 txdw15;
#पूर्ण_अगर
पूर्ण;

जोड़ txdesc अणु
	काष्ठा tx_desc txdesc;
	अचिन्हित पूर्णांक value[TXDESC_SIZE>>2];
पूर्ण;

काष्ठा	hw_xmit	अणु
	/* spinlock_t xmit_lock; */
	/* काष्ठा list_head	pending; */
	काष्ठा __queue *sta_queue;
	/* काष्ठा hw_txqueue *phwtxqueue; */
	/* चिन्हित पूर्णांक	txcmdcnt; */
	पूर्णांक	accnt;
पूर्ण;

/* reduce size */
काष्ठा pkt_attrib अणु
	u8 type;
	u8 subtype;
	u8 bswenc;
	u8 dhcp_pkt;
	u16 ether_type;
	u16 seqnum;
	u16 pkt_hdrlen;	/* the original 802.3 pkt header len */
	u16 hdrlen;		/* the WLAN Header Len */
	u32 pktlen;		/* the original 802.3 pkt raw_data len (not include ether_hdr data) */
	u32 last_txcmdsz;
	u8 nr_frags;
	u8 encrypt;	/* when 0 indicates no encryption; when non-zero, indicates the encryption algorithm */
	u8 iv_len;
	u8 icv_len;
	u8 iv[18];
	u8 icv[16];
	u8 priority;
	u8 ack_policy;
	u8 mac_id;
	u8 vcs_mode;	/* भव carrier sense method */
	u8 dst[ETH_ALEN];
	u8 src[ETH_ALEN];
	u8 ta[ETH_ALEN];
	u8 ra[ETH_ALEN];
	u8 key_idx;
	u8 qos_en;
	u8 ht_en;
	u8 raid;/* rate adpative id */
	u8 bwmode;
	u8 ch_offset;/* PRIME_CHNL_OFFSET */
	u8 sgi;/* लघु GI */
	u8 ampdu_en;/* tx ampdu enable */
	u8 ampdu_spacing; /* ampdu_min_spacing क्रम peer sta's rx */
	u8 mdata;/* more data bit */
	u8 pctrl;/* per packet txdesc control enable */
	u8 triggered;/* क्रम ap mode handling Power Saving sta */
	u8 qsel;
	u8 order;/* order bit */
	u8 eosp;
	u8 rate;
	u8 पूर्णांकel_proxim;
	u8 retry_ctrl;
	u8   mbssid;
	u8 ldpc;
	u8 stbc;
	काष्ठा sta_info *psta;

	u8 rtsen;
	u8 cts2self;
	जोड़ Keytype	करोt11tkiptxmickey;
	/* जोड़ Keytype	करोt11tkiprxmickey; */
	जोड़ Keytype	करोt118021x_UncstKey;

	u8 icmp_pkt;

पूर्ण;

#घोषणा WLANHDR_OFFSET	64

#घोषणा शून्य_FRAMETAG		(0x0)
#घोषणा DATA_FRAMETAG		0x01
#घोषणा L2_FRAMETAG		0x02
#घोषणा MGNT_FRAMETAG		0x03
#घोषणा AMSDU_FRAMETAG	0x04

#घोषणा EII_FRAMETAG		0x05
#घोषणा IEEE8023_FRAMETAG  0x06

#घोषणा MP_FRAMETAG		0x07

#घोषणा TXAGG_FRAMETAG	0x08

क्रमागत अणु
	XMITBUF_DATA = 0,
	XMITBUF_MGNT = 1,
	XMITBUF_CMD = 2,
पूर्ण;

काष्ठा  submit_ctx अणु
	अचिन्हित दीर्घ submit_समय; /* */
	u32 समयout_ms; /* <0: not synchronous, 0: रुको क्रमever, >0: up to ms रुकोing */
	पूर्णांक status; /* status क्रम operation */
	काष्ठा completion करोne;
पूर्ण;

क्रमागत अणु
	RTW_SCTX_SUBMITTED = -1,
	RTW_SCTX_DONE_SUCCESS = 0,
	RTW_SCTX_DONE_UNKNOWN,
	RTW_SCTX_DONE_TIMEOUT,
	RTW_SCTX_DONE_BUF_ALLOC,
	RTW_SCTX_DONE_BUF_FREE,
	RTW_SCTX_DONE_WRITE_PORT_ERR,
	RTW_SCTX_DONE_TX_DESC_NA,
	RTW_SCTX_DONE_TX_DENY,
	RTW_SCTX_DONE_CCX_PKT_FAIL,
	RTW_SCTX_DONE_DRV_STOP,
	RTW_SCTX_DONE_DEV_REMOVE,
	RTW_SCTX_DONE_CMD_ERROR,
पूर्ण;


व्योम rtw_sctx_init(काष्ठा submit_ctx *sctx, पूर्णांक समयout_ms);
पूर्णांक rtw_sctx_रुको(काष्ठा submit_ctx *sctx, स्थिर अक्षर *msg);
व्योम rtw_sctx_करोne_err(काष्ठा submit_ctx **sctx, पूर्णांक status);
व्योम rtw_sctx_करोne(काष्ठा submit_ctx **sctx);

काष्ठा xmit_buf अणु
	काष्ठा list_head	list;

	काष्ठा adapter *padapter;

	u8 *pallocated_buf;

	u8 *pbuf;

	व्योम *priv_data;

	u16 buf_tag; /*  0: Normal xmitbuf, 1: extension xmitbuf, 2:cmd xmitbuf */
	u16 flags;
	u32 alloc_sz;

	u32  len;

	काष्ठा submit_ctx *sctx;

	u8 *phead;
	u8 *pdata;
	u8 *ptail;
	u8 *pend;
	u32 ff_hwaddr;
	u8 pg_num;
	u8 agg_num;

#अगर defined(DBG_XMIT_BUF) || defined(DBG_XMIT_BUF_EXT)
	u8 no;
#पूर्ण_अगर

पूर्ण;


काष्ठा xmit_frame अणु
	काष्ठा list_head	list;

	काष्ठा pkt_attrib attrib;

	काष्ठा sk_buff *pkt;

	पूर्णांक	frame_tag;

	काष्ठा adapter *padapter;

	u8 *buf_addr;

	काष्ठा xmit_buf *pxmitbuf;

	u8 pg_num;
	u8 agg_num;

	u8 ack_report;

	u8 *alloc_addr; /* the actual address this xmitframe allocated */
	u8 ext_tag; /* 0:data, 1:mgmt */

पूर्ण;

काष्ठा tx_servq अणु
	काष्ठा list_head	tx_pending;
	काष्ठा __queue	sta_pending;
	पूर्णांक qcnt;
पूर्ण;


काष्ठा sta_xmit_priv अणु
	spinlock_t	lock;
	चिन्हित पूर्णांक	option;
	चिन्हित पूर्णांक	apsd_setting;	/* When bit mask is on, the associated edca queue supports APSD. */


	/* काष्ठा tx_servq blk_q[MAX_NUMBLKS]; */
	काष्ठा tx_servq	be_q;			/* priority == 0, 3 */
	काष्ठा tx_servq	bk_q;			/* priority == 1, 2 */
	काष्ठा tx_servq	vi_q;			/* priority == 4, 5 */
	काष्ठा tx_servq	vo_q;			/* priority == 6, 7 */
	काष्ठा list_head	legacy_dz;
	काष्ठा list_head  apsd;

	u16 txseq_tid[16];

	/* uपूर्णांक	sta_tx_bytes; */
	/* u64	sta_tx_pkts; */
	/* uपूर्णांक	sta_tx_fail; */


पूर्ण;


काष्ठा	hw_txqueue	अणु
	अस्थिर चिन्हित पूर्णांक	head;
	अस्थिर चिन्हित पूर्णांक	tail;
	अस्थिर चिन्हित पूर्णांक	मुक्त_sz;	/* in units of 64 bytes */
	अस्थिर चिन्हित पूर्णांक      मुक्त_cmdsz;
	अस्थिर चिन्हित पूर्णांक	 txsz[8];
	uपूर्णांक	ff_hwaddr;
	uपूर्णांक	cmd_hwaddr;
	चिन्हित पूर्णांक	ac_tag;
पूर्ण;

क्रमागत cmdbuf_type अणु
	CMDBUF_BEACON = 0x00,
	CMDBUF_RSVD,
	CMDBUF_MAX
पूर्ण;

काष्ठा	xmit_priv अणु

	spinlock_t	lock;

	काष्ठा completion xmit_comp;
	काष्ठा completion terminate_xmitthपढ़ो_comp;

	/* काष्ठा __queue	blk_strms[MAX_NUMBLKS]; */
	काष्ठा __queue	be_pending;
	काष्ठा __queue	bk_pending;
	काष्ठा __queue	vi_pending;
	काष्ठा __queue	vo_pending;
	काष्ठा __queue	bm_pending;

	/* काष्ठा __queue	legacy_dz_queue; */
	/* काष्ठा __queue	apsd_queue; */

	u8 *pallocated_frame_buf;
	u8 *pxmit_frame_buf;
	uपूर्णांक मुक्त_xmitframe_cnt;
	काष्ठा __queue	मुक्त_xmit_queue;

	/* uपूर्णांक mapping_addr; */
	/* uपूर्णांक pkt_sz; */

	u8 *xframe_ext_alloc_addr;
	u8 *xframe_ext;
	uपूर्णांक मुक्त_xframe_ext_cnt;
	काष्ठा __queue मुक्त_xframe_ext_queue;

	/* काष्ठा	hw_txqueue	be_txqueue; */
	/* काष्ठा	hw_txqueue	bk_txqueue; */
	/* काष्ठा	hw_txqueue	vi_txqueue; */
	/* काष्ठा	hw_txqueue	vo_txqueue; */
	/* काष्ठा	hw_txqueue	bmc_txqueue; */

	uपूर्णांक	frag_len;

	काष्ठा adapter	*adapter;

	u8   vcs_setting;
	u8 vcs;
	u8 vcs_type;
	/* u16  rts_thresh; */

	u64	tx_bytes;
	u64	tx_pkts;
	u64	tx_drop;
	u64	last_tx_pkts;

	काष्ठा hw_xmit *hwxmits;
	u8 hwxmit_entry;

	u8 wmm_para_seq[4];/* sequence क्रम wmm ac parameter strength from large to small. it's value is 0->vo, 1->vi, 2->be, 3->bk. */

	व्योम *SdioXmitThपढ़ो;
	काष्ठा completion SdioXmitStart;
	काष्ठा completion SdioXmitTerminate;

	काष्ठा __queue मुक्त_xmitbuf_queue;
	काष्ठा __queue pending_xmitbuf_queue;
	u8 *pallocated_xmitbuf;
	u8 *pxmitbuf;
	uपूर्णांक मुक्त_xmitbuf_cnt;

	काष्ठा __queue मुक्त_xmit_extbuf_queue;
	u8 *pallocated_xmit_extbuf;
	u8 *pxmit_extbuf;
	uपूर्णांक मुक्त_xmit_extbuf_cnt;

	काष्ठा xmit_buf	pcmd_xmitbuf[CMDBUF_MAX];

	u16 nqos_ssn;

	पूर्णांक	ack_tx;
	काष्ठा mutex ack_tx_mutex;
	काष्ठा submit_ctx ack_tx_ops;
	u8 seq_no;
	spinlock_t lock_sctx;
पूर्ण;

बाह्य काष्ठा xmit_frame *__rtw_alloc_cmdxmitframe(काष्ठा xmit_priv *pxmitpriv,
		क्रमागत cmdbuf_type buf_type);
#घोषणा rtw_alloc_cmdxmitframe(p) __rtw_alloc_cmdxmitframe(p, CMDBUF_RSVD)
#घोषणा rtw_alloc_bcnxmitframe(p) __rtw_alloc_cmdxmitframe(p, CMDBUF_BEACON)

बाह्य काष्ठा xmit_buf *rtw_alloc_xmitbuf_ext(काष्ठा xmit_priv *pxmitpriv);
बाह्य s32 rtw_मुक्त_xmitbuf_ext(काष्ठा xmit_priv *pxmitpriv, काष्ठा xmit_buf *pxmitbuf);

बाह्य काष्ठा xmit_buf *rtw_alloc_xmitbuf(काष्ठा xmit_priv *pxmitpriv);
बाह्य s32 rtw_मुक्त_xmitbuf(काष्ठा xmit_priv *pxmitpriv, काष्ठा xmit_buf *pxmitbuf);

व्योम rtw_count_tx_stats(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe, पूर्णांक sz);
बाह्य व्योम rtw_update_protection(काष्ठा adapter *padapter, u8 *ie, uपूर्णांक ie_len);
बाह्य s32 rtw_make_wlanhdr(काष्ठा adapter *padapter, u8 *hdr, काष्ठा pkt_attrib *pattrib);
बाह्य s32 rtw_put_snap(u8 *data, u16 h_proto);

बाह्य काष्ठा xmit_frame *rtw_alloc_xmitframe(काष्ठा xmit_priv *pxmitpriv);
काष्ठा xmit_frame *rtw_alloc_xmitframe_ext(काष्ठा xmit_priv *pxmitpriv);
काष्ठा xmit_frame *rtw_alloc_xmitframe_once(काष्ठा xmit_priv *pxmitpriv);
बाह्य s32 rtw_मुक्त_xmitframe(काष्ठा xmit_priv *pxmitpriv, काष्ठा xmit_frame *pxmitframe);
बाह्य व्योम rtw_मुक्त_xmitframe_queue(काष्ठा xmit_priv *pxmitpriv, काष्ठा __queue *pframequeue);
काष्ठा tx_servq *rtw_get_sta_pending(काष्ठा adapter *padapter, काष्ठा sta_info *psta, चिन्हित पूर्णांक up, u8 *ac);
बाह्य s32 rtw_xmitframe_enqueue(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe);

बाह्य s32 rtw_xmit_classअगरier(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe);
बाह्य u32 rtw_calculate_wlan_pkt_size_by_attribue(काष्ठा pkt_attrib *pattrib);
#घोषणा rtw_wlan_pkt_size(f) rtw_calculate_wlan_pkt_size_by_attribue(&f->attrib)
बाह्य s32 rtw_xmitframe_coalesce(काष्ठा adapter *padapter, काष्ठा sk_buff *pkt, काष्ठा xmit_frame *pxmitframe);
बाह्य s32 rtw_mgmt_xmitframe_coalesce(काष्ठा adapter *padapter, काष्ठा sk_buff *pkt, काष्ठा xmit_frame *pxmitframe);
s32 _rtw_init_hw_txqueue(काष्ठा hw_txqueue *phw_txqueue, u8 ac_tag);
व्योम _rtw_init_sta_xmit_priv(काष्ठा sta_xmit_priv *psta_xmitpriv);


s32 rtw_txframes_pending(काष्ठा adapter *padapter);
व्योम rtw_init_hwxmits(काष्ठा hw_xmit *phwxmit, चिन्हित पूर्णांक entry);


s32 _rtw_init_xmit_priv(काष्ठा xmit_priv *pxmitpriv, काष्ठा adapter *padapter);
व्योम _rtw_मुक्त_xmit_priv(काष्ठा xmit_priv *pxmitpriv);


s32 rtw_alloc_hwxmits(काष्ठा adapter *padapter);
व्योम rtw_मुक्त_hwxmits(काष्ठा adapter *padapter);


s32 rtw_xmit(काष्ठा adapter *padapter, काष्ठा sk_buff **pkt);
bool xmitframe_hiq_filter(काष्ठा xmit_frame *xmitframe);

चिन्हित पूर्णांक xmitframe_enqueue_क्रम_sleeping_sta(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe);
व्योम stop_sta_xmit(काष्ठा adapter *padapter, काष्ठा sta_info *psta);
व्योम wakeup_sta_to_xmit(काष्ठा adapter *padapter, काष्ठा sta_info *psta);
व्योम xmit_delivery_enabled_frames(काष्ठा adapter *padapter, काष्ठा sta_info *psta);

u8 query_ra_लघु_GI(काष्ठा sta_info *psta);

u8 qos_acm(u8 acm_mask, u8 priority);

व्योम enqueue_pending_xmitbuf(काष्ठा xmit_priv *pxmitpriv, काष्ठा xmit_buf *pxmitbuf);
व्योम enqueue_pending_xmitbuf_to_head(काष्ठा xmit_priv *pxmitpriv, काष्ठा xmit_buf *pxmitbuf);
काष्ठा xmit_buf *dequeue_pending_xmitbuf(काष्ठा xmit_priv *pxmitpriv);
काष्ठा xmit_buf *dequeue_pending_xmitbuf_under_survey(काष्ठा xmit_priv *pxmitpriv);
चिन्हित पूर्णांक	check_pending_xmitbuf(काष्ठा xmit_priv *pxmitpriv);
पूर्णांक	rtw_xmit_thपढ़ो(व्योम *context);

u32 rtw_get_ff_hwaddr(काष्ठा xmit_frame	*pxmitframe);

पूर्णांक rtw_ack_tx_रुको(काष्ठा xmit_priv *pxmitpriv, u32 समयout_ms);
व्योम rtw_ack_tx_करोne(काष्ठा xmit_priv *pxmitpriv, पूर्णांक status);

/* include after declaring काष्ठा xmit_buf, in order to aव्योम warning */
#समावेश <xmit_osdep.h>

#पूर्ण_अगर	/* _RTL871X_XMIT_H_ */
