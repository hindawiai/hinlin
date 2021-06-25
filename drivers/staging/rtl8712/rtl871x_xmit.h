<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
#अगर_अघोषित _RTL871X_XMIT_H_
#घोषणा _RTL871X_XMIT_H_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "xmit_osdep.h"

#अगर_घोषित CONFIG_R8712_TX_AGGR
#घोषणा MAX_XMITBUF_SZ  (16384)
#अन्यथा
#घोषणा MAX_XMITBUF_SZ  (2048)
#पूर्ण_अगर

#घोषणा NR_XMITBUFF     (4)

#अगर_घोषित CONFIG_R8712_TX_AGGR
#घोषणा AGGR_NR_HIGH_BOUND      (4) /*(8) */
#घोषणा AGGR_NR_LOW_BOUND       (2)
#पूर्ण_अगर

#घोषणा XMITBUF_ALIGN_SZ 512
#घोषणा TX_GUARD_BAND		5
#घोषणा MAX_NUMBLKS		(1)

/* Fixed the Big Endian bug when using the software driver encryption.*/
#घोषणा WEP_IV(pattrib_iv, txpn, keyidx)\
करो अणु \
	pattrib_iv[0] = txpn._byte_.TSC0;\
	pattrib_iv[1] = txpn._byte_.TSC1;\
	pattrib_iv[2] = txpn._byte_.TSC2;\
	pattrib_iv[3] = ((keyidx & 0x3) << 6);\
	txpn.val = (txpn.val == 0xffffff) ? 0 : (txpn.val + 1);\
पूर्ण जबतक (0)

/* Fixed the Big Endian bug when करोing the Tx.
 * The Linksys WRH54G will check this.
 */
#घोषणा TKIP_IV(pattrib_iv, txpn, keyidx)\
करो अणु \
	pattrib_iv[0] = txpn._byte_.TSC1;\
	pattrib_iv[1] = (txpn._byte_.TSC1 | 0x20) & 0x7f;\
	pattrib_iv[2] = txpn._byte_.TSC0;\
	pattrib_iv[3] = BIT(5) | ((keyidx & 0x3) << 6);\
	pattrib_iv[4] = txpn._byte_.TSC2;\
	pattrib_iv[5] = txpn._byte_.TSC3;\
	pattrib_iv[6] = txpn._byte_.TSC4;\
	pattrib_iv[7] = txpn._byte_.TSC5;\
	txpn.val = txpn.val == 0xffffffffffffULL ? 0 : \
	(txpn.val + 1);\
पूर्ण जबतक (0)

#घोषणा AES_IV(pattrib_iv, txpn, keyidx)\
करो अणु \
	pattrib_iv[0] = txpn._byte_.TSC0;\
	pattrib_iv[1] = txpn._byte_.TSC1;\
	pattrib_iv[2] = 0;\
	pattrib_iv[3] = BIT(5) | ((keyidx & 0x3) << 6);\
	pattrib_iv[4] = txpn._byte_.TSC2;\
	pattrib_iv[5] = txpn._byte_.TSC3;\
	pattrib_iv[6] = txpn._byte_.TSC4;\
	pattrib_iv[7] = txpn._byte_.TSC5;\
	txpn.val = txpn.val == 0xffffffffffffULL ? 0 : \
	(txpn.val + 1);\
पूर्ण जबतक (0)

काष्ठा hw_xmit अणु
	spinlock_t xmit_lock;
	काष्ठा list_head pending;
	काष्ठा  __queue *sta_queue;
	काष्ठा hw_txqueue *phwtxqueue;
	sपूर्णांक	txcmdcnt;
	पूर्णांक	accnt;
पूर्ण;

काष्ठा pkt_attrib अणु
	u8	type;
	u8	subtype;
	u8	bswenc;
	u8	dhcp_pkt;

	u16	seqnum;
	u16	ether_type;
	u16	pktlen;		/* the original 802.3 pkt raw_data len
				 * (not include ether_hdr data)
				 */
	u16	last_txcmdsz;

	u8	pkt_hdrlen;	/*the original 802.3 pkt header len*/
	u8	hdrlen;		/*the WLAN Header Len*/
	u8	nr_frags;
	u8	ack_policy;
	u8	mac_id;
	u8	vcs_mode;	/*भव carrier sense method*/
	u8	pctrl;/*per packet txdesc control enable*/
	u8	qsel;

	u8	priority;
	u8	encrypt;	/* when 0 indicate no encrypt. when non-zero,
				 * indicate the encrypt algorithm
				 */
	u8	iv_len;
	u8	icv_len;
	अचिन्हित अक्षर iv[8];
	अचिन्हित अक्षर icv[8];
	u8	dst[ETH_ALEN] __aligned(2);	/* क्रम ether_addr_copy */
	u8	src[ETH_ALEN];
	u8	ta[ETH_ALEN];
	u8	ra[ETH_ALEN];
	काष्ठा sta_info *psta;
पूर्ण;

#घोषणा WLANHDR_OFFSET	64
#घोषणा DATA_FRAMETAG		0x01
#घोषणा L2_FRAMETAG		0x02
#घोषणा MGNT_FRAMETAG		0x03
#घोषणा AMSDU_FRAMETAG	0x04
#घोषणा EII_FRAMETAG		0x05
#घोषणा IEEE8023_FRAMETAG  0x06
#घोषणा MP_FRAMETAG		0x07
#घोषणा TXAGG_FRAMETAG	0x08

काष्ठा xmit_buf अणु
	काष्ठा list_head list;

	u8 *pallocated_buf;
	u8 *pbuf;
	व्योम *priv_data;
	काष्ठा urb *pxmit_urb[8];
	u32 aggr_nr;
पूर्ण;

काष्ठा xmit_frame अणु
	काष्ठा list_head list;
	काष्ठा pkt_attrib attrib;
	_pkt *pkt;
	पूर्णांक frame_tag;
	काष्ठा _adapter *padapter;
	u8 *buf_addr;
	काष्ठा xmit_buf *pxmitbuf;
	u8 *mem_addr;
	u16 sz[8];
	काष्ठा urb *pxmit_urb[8];
	u8 bpending[8];
	u8 last[8];
पूर्ण;

काष्ठा tx_servq अणु
	काष्ठा list_head tx_pending;
	काष्ठा  __queue	sta_pending;
	पूर्णांक qcnt;
पूर्ण;

काष्ठा sta_xmit_priv अणु
	spinlock_t lock;
	sपूर्णांक	option;
	sपूर्णांक	apsd_setting;	/* When bit mask is on, the associated edca
				 * queue supports APSD.
				 */
	काष्ठा tx_servq	be_q;	/* priority == 0,3 */
	काष्ठा tx_servq	bk_q;	/* priority == 1,2*/
	काष्ठा tx_servq	vi_q;	/*priority == 4,5*/
	काष्ठा tx_servq	vo_q;	/*priority == 6,7*/
	काष्ठा list_head  legacy_dz;
	काष्ठा list_head apsd;
	u16 txseq_tid[16];
	uपूर्णांक	sta_tx_bytes;
	u64	sta_tx_pkts;
	uपूर्णांक	sta_tx_fail;
पूर्ण;

काष्ठा	hw_txqueue अणु
	/*अस्थिर*/ sपूर्णांक	head;
	/*अस्थिर*/ sपूर्णांक	tail;
	/*अस्थिर*/ sपूर्णांक	मुक्त_sz;	/*in units of 64 bytes*/
	/*अस्थिर*/ sपूर्णांक      मुक्त_cmdsz;
	/*अस्थिर*/ sपूर्णांक	 txsz[8];
	uपूर्णांक	ff_hwaddr;
	uपूर्णांक	cmd_hwaddr;
	sपूर्णांक	ac_tag;
पूर्ण;

काष्ठा	xmit_priv अणु
	spinlock_t lock;
	काष्ठा  __queue	be_pending;
	काष्ठा  __queue	bk_pending;
	काष्ठा  __queue	vi_pending;
	काष्ठा  __queue	vo_pending;
	काष्ठा  __queue	bm_pending;
	काष्ठा  __queue	legacy_dz_queue;
	काष्ठा  __queue	apsd_queue;
	u8 *pallocated_frame_buf;
	u8 *pxmit_frame_buf;
	uपूर्णांक मुक्त_xmitframe_cnt;
	uपूर्णांक mapping_addr;
	uपूर्णांक pkt_sz;
	काष्ठा  __queue	मुक्त_xmit_queue;
	काष्ठा	hw_txqueue	be_txqueue;
	काष्ठा	hw_txqueue	bk_txqueue;
	काष्ठा	hw_txqueue	vi_txqueue;
	काष्ठा	hw_txqueue	vo_txqueue;
	काष्ठा	hw_txqueue	bmc_txqueue;
	uपूर्णांक	frag_len;
	काष्ठा _adapter	*adapter;
	u8   vcs_setting;
	u8	vcs;
	u8	vcs_type;
	u16  rts_thresh;
	uपूर्णांक	tx_bytes;
	u64	tx_pkts;
	uपूर्णांक	tx_drop;
	काष्ठा hw_xmit *hwxmits;
	u8	hwxmit_entry;
	u8	txirp_cnt;
	काष्ठा tasklet_काष्ठा xmit_tasklet;
	काष्ठा work_काष्ठा xmit_pipe4_reset_wi;
	काष्ठा work_काष्ठा xmit_pipe6_reset_wi;
	काष्ठा work_काष्ठा xmit_piped_reset_wi;
	/*per AC pending irp*/
	पूर्णांक beq_cnt;
	पूर्णांक bkq_cnt;
	पूर्णांक viq_cnt;
	पूर्णांक voq_cnt;
	काष्ठा  __queue	मुक्त_amsdu_xmit_queue;
	u8 *pallocated_amsdu_frame_buf;
	u8 *pxmit_amsdu_frame_buf;
	uपूर्णांक मुक्त_amsdu_xmitframe_cnt;
	काष्ठा  __queue मुक्त_txagg_xmit_queue;
	u8 *pallocated_txagg_frame_buf;
	u8 *pxmit_txagg_frame_buf;
	uपूर्णांक मुक्त_txagg_xmitframe_cnt;
	पूर्णांक cmdseq;
	काष्ठा  __queue मुक्त_xmitbuf_queue;
	काष्ठा  __queue pending_xmitbuf_queue;
	u8 *pallocated_xmitbuf;
	u8 *pxmitbuf;
	uपूर्णांक मुक्त_xmitbuf_cnt;
पूर्ण;

व्योम r8712_मुक्त_xmitbuf(काष्ठा xmit_priv *pxmitpriv,
			काष्ठा xmit_buf *pxmitbuf);
काष्ठा xmit_buf *r8712_alloc_xmitbuf(काष्ठा xmit_priv *pxmitpriv);
व्योम r8712_update_protection(काष्ठा _adapter *padapter, u8 *ie, uपूर्णांक ie_len);
काष्ठा xmit_frame *r8712_alloc_xmitframe(काष्ठा xmit_priv *pxmitpriv);
व्योम r8712_मुक्त_xmitframe(काष्ठा xmit_priv *pxmitpriv,
			  काष्ठा xmit_frame *pxmitframe);
व्योम r8712_मुक्त_xmitframe_queue(काष्ठा xmit_priv *pxmitpriv,
				काष्ठा  __queue *pframequeue);
पूर्णांक r8712_xmit_classअगरier(काष्ठा _adapter *padapter,
			  काष्ठा xmit_frame *pxmitframe);
sपूर्णांक r8712_xmitframe_coalesce(काष्ठा _adapter *padapter, _pkt *pkt,
			      काष्ठा xmit_frame *pxmitframe);
sपूर्णांक _r8712_init_hw_txqueue(काष्ठा hw_txqueue *phw_txqueue, u8 ac_tag);
व्योम _r8712_init_sta_xmit_priv(काष्ठा sta_xmit_priv *psta_xmitpriv);
पूर्णांक r8712_update_attrib(काष्ठा _adapter *padapter, _pkt *pkt,
			काष्ठा pkt_attrib *pattrib);
पूर्णांक r8712_txframes_sta_ac_pending(काष्ठा _adapter *padapter,
				  काष्ठा pkt_attrib *pattrib);
पूर्णांक _r8712_init_xmit_priv(काष्ठा xmit_priv *pxmitpriv,
			  काष्ठा _adapter *padapter);
व्योम _मुक्त_xmit_priv(काष्ठा xmit_priv *pxmitpriv);
व्योम r8712_मुक्त_xmitframe_ex(काष्ठा xmit_priv *pxmitpriv,
			     काष्ठा xmit_frame *pxmitframe);
पूर्णांक r8712_pre_xmit(काष्ठा _adapter *padapter, काष्ठा xmit_frame *pxmitframe);
पूर्णांक r8712_xmit_enqueue(काष्ठा _adapter *padapter,
		       काष्ठा xmit_frame *pxmitframe);
व्योम r8712_xmit_direct(काष्ठा _adapter *padapter, काष्ठा xmit_frame *pxmitframe);
व्योम r8712_xmit_bh(काष्ठा tasklet_काष्ठा *t);

व्योम xmitframe_xmitbuf_attach(काष्ठा xmit_frame *pxmitframe,
			      काष्ठा xmit_buf *pxmitbuf);

#समावेश "rtl8712_xmit.h"

#पूर्ण_अगर	/*_RTL871X_XMIT_H_*/

