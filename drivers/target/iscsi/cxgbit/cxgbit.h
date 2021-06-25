<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016 Chelsio Communications, Inc.
 */

#अगर_अघोषित __CXGBIT_H__
#घोषणा __CXGBIT_H__

#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/idr.h>
#समावेश <linux/completion.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/sched.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/inet.h>
#समावेश <linux/रुको.h>
#समावेश <linux/kref.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/byteorder.h>

#समावेश <net/net_namespace.h>

#समावेश <target/iscsi/iscsi_transport.h>
#समावेश <iscsi_target_parameters.h>
#समावेश <iscsi_target_login.h>

#समावेश "t4_regs.h"
#समावेश "t4_msg.h"
#समावेश "cxgb4.h"
#समावेश "cxgb4_uld.h"
#समावेश "l2t.h"
#समावेश "libcxgb_ppm.h"
#समावेश "cxgbit_lro.h"

बाह्य काष्ठा mutex cdev_list_lock;
बाह्य काष्ठा list_head cdev_list_head;
काष्ठा cxgbit_np;

काष्ठा cxgbit_sock;

काष्ठा cxgbit_cmd अणु
	काष्ठा scatterlist sg;
	काष्ठा cxgbi_task_tag_info ttinfo;
	bool setup_ddp;
	bool release;
पूर्ण;

#घोषणा CXGBIT_MAX_ISO_PAYLOAD	\
	min_t(u32, MAX_SKB_FRAGS * PAGE_SIZE, 65535)

काष्ठा cxgbit_iso_info अणु
	u8 flags;
	u32 mpdu;
	u32 len;
	u32 burst_len;
पूर्ण;

क्रमागत cxgbit_skcb_flags अणु
	SKCBF_TX_NEED_HDR	= (1 << 0), /* packet needs a header */
	SKCBF_TX_FLAG_COMPL	= (1 << 1), /* wr completion flag */
	SKCBF_TX_ISO		= (1 << 2), /* iso cpl in tx skb */
	SKCBF_RX_LRO		= (1 << 3), /* lro skb */
पूर्ण;

काष्ठा cxgbit_skb_rx_cb अणु
	u8 opcode;
	व्योम *pdu_cb;
	व्योम (*backlog_fn)(काष्ठा cxgbit_sock *, काष्ठा sk_buff *);
पूर्ण;

काष्ठा cxgbit_skb_tx_cb अणु
	u8 submode;
	u32 extra_len;
पूर्ण;

जोड़ cxgbit_skb_cb अणु
	काष्ठा अणु
		u8 flags;
		जोड़ अणु
			काष्ठा cxgbit_skb_tx_cb tx;
			काष्ठा cxgbit_skb_rx_cb rx;
		पूर्ण;
	पूर्ण;

	काष्ठा अणु
		/* This member must be first. */
		काष्ठा l2t_skb_cb l2t;
		काष्ठा sk_buff *wr_next;
	पूर्ण;
पूर्ण;

#घोषणा CXGBIT_SKB_CB(skb)	((जोड़ cxgbit_skb_cb *)&((skb)->cb[0]))
#घोषणा cxgbit_skcb_flags(skb)		(CXGBIT_SKB_CB(skb)->flags)
#घोषणा cxgbit_skcb_submode(skb)	(CXGBIT_SKB_CB(skb)->tx.submode)
#घोषणा cxgbit_skcb_tx_wr_next(skb)	(CXGBIT_SKB_CB(skb)->wr_next)
#घोषणा cxgbit_skcb_tx_extralen(skb)	(CXGBIT_SKB_CB(skb)->tx.extra_len)
#घोषणा cxgbit_skcb_rx_opcode(skb)	(CXGBIT_SKB_CB(skb)->rx.opcode)
#घोषणा cxgbit_skcb_rx_backlog_fn(skb)	(CXGBIT_SKB_CB(skb)->rx.backlog_fn)
#घोषणा cxgbit_rx_pdu_cb(skb)		(CXGBIT_SKB_CB(skb)->rx.pdu_cb)

अटल अंतरभूत व्योम *cplhdr(काष्ठा sk_buff *skb)
अणु
	वापस skb->data;
पूर्ण

क्रमागत cxgbit_cdev_flags अणु
	CDEV_STATE_UP = 0,
	CDEV_ISO_ENABLE,
	CDEV_DDP_ENABLE,
पूर्ण;

#घोषणा NP_INFO_HASH_SIZE 32

काष्ठा np_info अणु
	काष्ठा np_info *next;
	काष्ठा cxgbit_np *cnp;
	अचिन्हित पूर्णांक stid;
पूर्ण;

काष्ठा cxgbit_list_head अणु
	काष्ठा list_head list;
	/* device lock */
	spinlock_t lock;
पूर्ण;

काष्ठा cxgbit_device अणु
	काष्ठा list_head list;
	काष्ठा cxgb4_lld_info lldi;
	काष्ठा np_info *np_hash_tab[NP_INFO_HASH_SIZE];
	/* np lock */
	spinlock_t np_lock;
	u8 selectq[MAX_NPORTS][2];
	काष्ठा cxgbit_list_head cskq;
	u32 mdsl;
	काष्ठा kref kref;
	अचिन्हित दीर्घ flags;
पूर्ण;

काष्ठा cxgbit_wr_रुको अणु
	काष्ठा completion completion;
	पूर्णांक ret;
पूर्ण;

क्रमागत cxgbit_csk_state अणु
	CSK_STATE_IDLE = 0,
	CSK_STATE_LISTEN,
	CSK_STATE_CONNECTING,
	CSK_STATE_ESTABLISHED,
	CSK_STATE_ABORTING,
	CSK_STATE_CLOSING,
	CSK_STATE_MORIBUND,
	CSK_STATE_DEAD,
पूर्ण;

क्रमागत cxgbit_csk_flags अणु
	CSK_TX_DATA_SENT = 0,
	CSK_LOGIN_PDU_DONE,
	CSK_LOGIN_DONE,
	CSK_DDP_ENABLE,
	CSK_ABORT_RPL_WAIT,
पूर्ण;

काष्ठा cxgbit_sock_common अणु
	काष्ठा cxgbit_device *cdev;
	काष्ठा sockaddr_storage local_addr;
	काष्ठा sockaddr_storage remote_addr;
	काष्ठा cxgbit_wr_रुको wr_रुको;
	क्रमागत cxgbit_csk_state state;
	अचिन्हित दीर्घ flags;
पूर्ण;

काष्ठा cxgbit_np अणु
	काष्ठा cxgbit_sock_common com;
	रुको_queue_head_t accept_रुको;
	काष्ठा iscsi_np *np;
	काष्ठा completion accept_comp;
	काष्ठा list_head np_accept_list;
	/* np accept lock */
	spinlock_t np_accept_lock;
	काष्ठा kref kref;
	अचिन्हित पूर्णांक stid;
पूर्ण;

काष्ठा cxgbit_sock अणु
	काष्ठा cxgbit_sock_common com;
	काष्ठा cxgbit_np *cnp;
	काष्ठा iscsi_conn *conn;
	काष्ठा l2t_entry *l2t;
	काष्ठा dst_entry *dst;
	काष्ठा list_head list;
	काष्ठा sk_buff_head rxq;
	काष्ठा sk_buff_head txq;
	काष्ठा sk_buff_head ppodq;
	काष्ठा sk_buff_head backlogq;
	काष्ठा sk_buff_head skbq;
	काष्ठा sk_buff *wr_pending_head;
	काष्ठा sk_buff *wr_pending_tail;
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff *lro_skb;
	काष्ठा sk_buff *lro_hskb;
	काष्ठा list_head accept_node;
	/* socket lock */
	spinlock_t lock;
	रुको_queue_head_t रुकोq;
	bool lock_owner;
	काष्ठा kref kref;
	u32 max_iso_npdu;
	u32 wr_cred;
	u32 wr_una_cred;
	u32 wr_max_cred;
	u32 snd_una;
	u32 tid;
	u32 snd_nxt;
	u32 rcv_nxt;
	u32 smac_idx;
	u32 tx_chan;
	u32 mtu;
	u32 ग_लिखो_seq;
	u32 rx_credits;
	u32 snd_win;
	u32 rcv_win;
	u16 mss;
	u16 emss;
	u16 plen;
	u16 rss_qid;
	u16 txq_idx;
	u16 ctrlq_idx;
	u8 tos;
	u8 port_id;
#घोषणा CXGBIT_SUBMODE_HCRC 0x1
#घोषणा CXGBIT_SUBMODE_DCRC 0x2
	u8 submode;
#अगर_घोषित CONFIG_CHELSIO_T4_DCB
	u8 dcb_priority;
#पूर्ण_अगर
	u8 snd_wscale;
पूर्ण;

व्योम _cxgbit_मुक्त_cdev(काष्ठा kref *kref);
व्योम _cxgbit_मुक्त_csk(काष्ठा kref *kref);
व्योम _cxgbit_मुक्त_cnp(काष्ठा kref *kref);

अटल अंतरभूत व्योम cxgbit_get_cdev(काष्ठा cxgbit_device *cdev)
अणु
	kref_get(&cdev->kref);
पूर्ण

अटल अंतरभूत व्योम cxgbit_put_cdev(काष्ठा cxgbit_device *cdev)
अणु
	kref_put(&cdev->kref, _cxgbit_मुक्त_cdev);
पूर्ण

अटल अंतरभूत व्योम cxgbit_get_csk(काष्ठा cxgbit_sock *csk)
अणु
	kref_get(&csk->kref);
पूर्ण

अटल अंतरभूत व्योम cxgbit_put_csk(काष्ठा cxgbit_sock *csk)
अणु
	kref_put(&csk->kref, _cxgbit_मुक्त_csk);
पूर्ण

अटल अंतरभूत व्योम cxgbit_get_cnp(काष्ठा cxgbit_np *cnp)
अणु
	kref_get(&cnp->kref);
पूर्ण

अटल अंतरभूत व्योम cxgbit_put_cnp(काष्ठा cxgbit_np *cnp)
अणु
	kref_put(&cnp->kref, _cxgbit_मुक्त_cnp);
पूर्ण

अटल अंतरभूत व्योम cxgbit_sock_reset_wr_list(काष्ठा cxgbit_sock *csk)
अणु
	csk->wr_pending_tail = शून्य;
	csk->wr_pending_head = शून्य;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *cxgbit_sock_peek_wr(स्थिर काष्ठा cxgbit_sock *csk)
अणु
	वापस csk->wr_pending_head;
पूर्ण

अटल अंतरभूत व्योम
cxgbit_sock_enqueue_wr(काष्ठा cxgbit_sock *csk, काष्ठा sk_buff *skb)
अणु
	cxgbit_skcb_tx_wr_next(skb) = शून्य;

	skb_get(skb);

	अगर (!csk->wr_pending_head)
		csk->wr_pending_head = skb;
	अन्यथा
		cxgbit_skcb_tx_wr_next(csk->wr_pending_tail) = skb;
	csk->wr_pending_tail = skb;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *cxgbit_sock_dequeue_wr(काष्ठा cxgbit_sock *csk)
अणु
	काष्ठा sk_buff *skb = csk->wr_pending_head;

	अगर (likely(skb)) अणु
		csk->wr_pending_head = cxgbit_skcb_tx_wr_next(skb);
		cxgbit_skcb_tx_wr_next(skb) = शून्य;
	पूर्ण
	वापस skb;
पूर्ण

प्रकार व्योम (*cxgbit_cplhandler_func)(काष्ठा cxgbit_device *,
				       काष्ठा sk_buff *);

पूर्णांक cxgbit_setup_np(काष्ठा iscsi_np *, काष्ठा sockaddr_storage *);
पूर्णांक cxgbit_setup_conn_digest(काष्ठा cxgbit_sock *);
पूर्णांक cxgbit_accept_np(काष्ठा iscsi_np *, काष्ठा iscsi_conn *);
व्योम cxgbit_मुक्त_np(काष्ठा iscsi_np *);
व्योम cxgbit_पात_conn(काष्ठा cxgbit_sock *csk);
व्योम cxgbit_मुक्त_conn(काष्ठा iscsi_conn *);
बाह्य cxgbit_cplhandler_func cxgbit_cplhandlers[NUM_CPL_CMDS];
पूर्णांक cxgbit_get_login_rx(काष्ठा iscsi_conn *, काष्ठा iscsi_login *);
पूर्णांक cxgbit_rx_data_ack(काष्ठा cxgbit_sock *);
पूर्णांक cxgbit_l2t_send(काष्ठा cxgbit_device *, काष्ठा sk_buff *,
		    काष्ठा l2t_entry *);
व्योम cxgbit_push_tx_frames(काष्ठा cxgbit_sock *);
पूर्णांक cxgbit_put_login_tx(काष्ठा iscsi_conn *, काष्ठा iscsi_login *, u32);
पूर्णांक cxgbit_xmit_pdu(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *,
		    काष्ठा iscsi_datain_req *, स्थिर व्योम *, u32);
व्योम cxgbit_get_r2t_ttt(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *,
			काष्ठा iscsi_r2t *);
u32 cxgbit_send_tx_flowc_wr(काष्ठा cxgbit_sock *);
पूर्णांक cxgbit_ofld_send(काष्ठा cxgbit_device *, काष्ठा sk_buff *);
व्योम cxgbit_get_rx_pdu(काष्ठा iscsi_conn *);
पूर्णांक cxgbit_validate_params(काष्ठा iscsi_conn *);
काष्ठा cxgbit_device *cxgbit_find_device(काष्ठा net_device *, u8 *);

/* DDP */
पूर्णांक cxgbit_ddp_init(काष्ठा cxgbit_device *);
पूर्णांक cxgbit_setup_conn_pgidx(काष्ठा cxgbit_sock *, u32);
पूर्णांक cxgbit_reserve_ttt(काष्ठा cxgbit_sock *, काष्ठा iscsi_cmd *);
व्योम cxgbit_unmap_cmd(काष्ठा iscsi_conn *, काष्ठा iscsi_cmd *);

अटल अंतरभूत
काष्ठा cxgbi_ppm *cdev2ppm(काष्ठा cxgbit_device *cdev)
अणु
	वापस (काष्ठा cxgbi_ppm *)(*cdev->lldi.iscsi_ppm);
पूर्ण
#पूर्ण_अगर /* __CXGBIT_H__ */
