<शैली गुरु>
/*
 * libcxgbi.h: Chelsio common library क्रम T3/T4 iSCSI driver.
 *
 * Copyright (c) 2010-2015 Chelsio Communications, Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Written by: Karen Xie (kxie@chelsio.com)
 * Written by: Rakesh Ranjan (rranjan@chelsio.com)
 */

#अगर_अघोषित	__LIBCXGBI_H__
#घोषणा	__LIBCXGBI_H__

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/list.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/version.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/libiscsi_tcp.h>

#समावेश <libcxgb_ppm.h>

क्रमागत cxgbi_dbg_flag अणु
	CXGBI_DBG_ISCSI,
	CXGBI_DBG_DDP,
	CXGBI_DBG_TOE,
	CXGBI_DBG_SOCK,

	CXGBI_DBG_PDU_TX,
	CXGBI_DBG_PDU_RX,
	CXGBI_DBG_DEV,
पूर्ण;

#घोषणा log_debug(level, fmt, ...)	\
	करो अणु	\
		अगर (dbg_level & (level)) \
			pr_info(fmt, ##__VA_ARGS__); \
	पूर्ण जबतक (0)

#घोषणा pr_info_ipaddr(fmt_trail,					\
			addr1, addr2, args_trail...)			\
करो अणु									\
	अगर (!((1 << CXGBI_DBG_SOCK) & dbg_level))			\
		अवरोध;							\
	pr_info("%pISpc - %pISpc, " fmt_trail,				\
		addr1, addr2, args_trail);				\
पूर्ण जबतक (0)

/* max. connections per adapter */
#घोषणा CXGBI_MAX_CONN		16384

/* always allocate rooms क्रम AHS */
#घोषणा SKB_TX_ISCSI_PDU_HEADER_MAX	\
	(माप(काष्ठा iscsi_hdr) + ISCSI_MAX_AHS_SIZE)

#घोषणा	ISCSI_PDU_NONPAYLOAD_LEN	312 /* bhs(48) + ahs(256) + digest(8)*/

/*
 * align pdu size to multiple of 512 क्रम better perक्रमmance
 */
#घोषणा cxgbi_align_pdu_size(n) करो अणु n = (n) & (~511); पूर्ण जबतक (0)

#घोषणा ULP2_MODE_ISCSI		2

#घोषणा ULP2_MAX_PKT_SIZE	16224
#घोषणा ULP2_MAX_PDU_PAYLOAD	\
	(ULP2_MAX_PKT_SIZE - ISCSI_PDU_NONPAYLOAD_LEN)

#घोषणा CXGBI_ULP2_MAX_ISO_PAYLOAD	65535

#घोषणा CXGBI_MAX_ISO_DATA_IN_SKB	\
	min_t(u32, MAX_SKB_FRAGS << PAGE_SHIFT, CXGBI_ULP2_MAX_ISO_PAYLOAD)

#घोषणा cxgbi_is_iso_config(csk)	((csk)->cdev->skb_iso_txhdr)
#घोषणा cxgbi_is_iso_disabled(csk)	((csk)->disable_iso)

/*
 * For iscsi connections HW may inserts digest bytes पूर्णांकo the pdu. Those digest
 * bytes are not sent by the host but are part of the TCP payload and thereक्रमe
 * consume TCP sequence space.
 */
अटल स्थिर अचिन्हित पूर्णांक ulp2_extra_len[] = अणु 0, 4, 4, 8 पूर्ण;
अटल अंतरभूत अचिन्हित पूर्णांक cxgbi_ulp_extra_len(पूर्णांक submode)
अणु
	वापस ulp2_extra_len[submode & 3];
पूर्ण

#घोषणा CPL_RX_DDP_STATUS_DDP_SHIFT	16 /* ddp'able */
#घोषणा CPL_RX_DDP_STATUS_PAD_SHIFT	19 /* pad error */
#घोषणा CPL_RX_DDP_STATUS_HCRC_SHIFT	20 /* hcrc error */
#घोषणा CPL_RX_DDP_STATUS_DCRC_SHIFT	21 /* dcrc error */

/*
 * sge_opaque_hdr -
 * Opaque version of काष्ठाure the SGE stores at skb->head of TX_DATA packets
 * and क्रम which we must reserve space.
 */
काष्ठा sge_opaque_hdr अणु
	व्योम *dev;
	dma_addr_t addr[MAX_SKB_FRAGS + 1];
पूर्ण;

काष्ठा cxgbi_sock अणु
	काष्ठा cxgbi_device *cdev;

	पूर्णांक tid;
	पूर्णांक atid;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक mtu;
	अचिन्हित लघु rss_qid;
	अचिन्हित लघु txq_idx;
	अचिन्हित लघु advmss;
	अचिन्हित पूर्णांक tx_chan;
	अचिन्हित पूर्णांक rx_chan;
	अचिन्हित पूर्णांक mss_idx;
	अचिन्हित पूर्णांक smac_idx;
	अचिन्हित अक्षर port_id;
	पूर्णांक wr_max_cred;
	पूर्णांक wr_cred;
	पूर्णांक wr_una_cred;
#अगर_घोषित CONFIG_CHELSIO_T4_DCB
	u8 dcb_priority;
#पूर्ण_अगर
	अचिन्हित अक्षर hcrc_len;
	अचिन्हित अक्षर dcrc_len;

	व्योम *l2t;
	काष्ठा sk_buff *wr_pending_head;
	काष्ठा sk_buff *wr_pending_tail;
	काष्ठा sk_buff *cpl_बंद;
	काष्ठा sk_buff *cpl_पात_req;
	काष्ठा sk_buff *cpl_पात_rpl;
	काष्ठा sk_buff *skb_ulp_lhdr;
	spinlock_t lock;
	काष्ठा kref refcnt;
	अचिन्हित पूर्णांक state;
	अचिन्हित पूर्णांक csk_family;
	जोड़ अणु
		काष्ठा sockaddr_in saddr;
		काष्ठा sockaddr_in6 saddr6;
	पूर्ण;
	जोड़ अणु
		काष्ठा sockaddr_in daddr;
		काष्ठा sockaddr_in6 daddr6;
	पूर्ण;
	काष्ठा dst_entry *dst;
	काष्ठा sk_buff_head receive_queue;
	काष्ठा sk_buff_head ग_लिखो_queue;
	काष्ठा समयr_list retry_समयr;
	काष्ठा completion cmpl;
	पूर्णांक err;
	rwlock_t callback_lock;
	व्योम *user_data;

	u32 rcv_nxt;
	u32 copied_seq;
	u32 rcv_wup;
	u32 snd_nxt;
	u32 snd_una;
	u32 ग_लिखो_seq;
	u32 snd_win;
	u32 rcv_win;

	bool disable_iso;
	u32 no_tx_credits;
	अचिन्हित दीर्घ prev_iso_ts;
पूर्ण;

/*
 * connection states
 */
क्रमागत cxgbi_sock_statesअणु
	CTP_CLOSED,
	CTP_CONNECTING,
	CTP_ACTIVE_OPEN,
	CTP_ESTABLISHED,
	CTP_ACTIVE_CLOSE,
	CTP_PASSIVE_CLOSE,
	CTP_CLOSE_WAIT_1,
	CTP_CLOSE_WAIT_2,
	CTP_ABORTING,
पूर्ण;

/*
 * Connection flags -- many to track some बंद related events.
 */
क्रमागत cxgbi_sock_flags अणु
	CTPF_ABORT_RPL_RCVD,	/*received one ABORT_RPL_RSS message */
	CTPF_ABORT_REQ_RCVD,	/*received one ABORT_REQ_RSS message */
	CTPF_ABORT_RPL_PENDING,	/* expecting an पात reply */
	CTPF_TX_DATA_SENT,	/* alपढ़ोy sent a TX_DATA WR */
	CTPF_ACTIVE_CLOSE_NEEDED,/* need to be बंदd */
	CTPF_HAS_ATID,		/* reserved atid */
	CTPF_HAS_TID,		/* reserved hw tid */
	CTPF_OFFLOAD_DOWN,	/* offload function off */
	CTPF_LOGOUT_RSP_RCVD,   /* received logout response */
पूर्ण;

काष्ठा cxgbi_skb_rx_cb अणु
	__u32 ddigest;
	__u32 pdulen;
पूर्ण;

काष्ठा cxgbi_skb_tx_cb अणु
	व्योम *handle;
	व्योम *arp_err_handler;
	काष्ठा sk_buff *wr_next;
	u16 iscsi_hdr_len;
	u8 ulp_mode;
पूर्ण;

क्रमागत cxgbi_skcb_flags अणु
	SKCBF_TX_NEED_HDR,	/* packet needs a header */
	SKCBF_TX_MEM_WRITE,     /* memory ग_लिखो */
	SKCBF_TX_FLAG_COMPL,    /* wr completion flag */
	SKCBF_RX_COALESCED,	/* received whole pdu */
	SKCBF_RX_HDR,		/* received pdu header */
	SKCBF_RX_DATA,		/* received pdu payload */
	SKCBF_RX_STATUS,	/* received ddp status */
	SKCBF_RX_ISCSI_COMPL,   /* received iscsi completion */
	SKCBF_RX_DATA_DDPD,	/* pdu payload ddp'd */
	SKCBF_RX_HCRC_ERR,	/* header digest error */
	SKCBF_RX_DCRC_ERR,	/* data digest error */
	SKCBF_RX_PAD_ERR,	/* padding byte error */
	SKCBF_TX_ISO,		/* iso cpl in tx skb */
पूर्ण;

काष्ठा cxgbi_skb_cb अणु
	जोड़ अणु
		काष्ठा cxgbi_skb_rx_cb rx;
		काष्ठा cxgbi_skb_tx_cb tx;
	पूर्ण;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक seq;
पूर्ण;

#घोषणा CXGBI_SKB_CB(skb)	((काष्ठा cxgbi_skb_cb *)&((skb)->cb[0]))
#घोषणा cxgbi_skcb_flags(skb)		(CXGBI_SKB_CB(skb)->flags)
#घोषणा cxgbi_skcb_tcp_seq(skb)		(CXGBI_SKB_CB(skb)->seq)
#घोषणा cxgbi_skcb_rx_ddigest(skb)	(CXGBI_SKB_CB(skb)->rx.ddigest)
#घोषणा cxgbi_skcb_rx_pdulen(skb)	(CXGBI_SKB_CB(skb)->rx.pdulen)
#घोषणा cxgbi_skcb_tx_wr_next(skb)	(CXGBI_SKB_CB(skb)->tx.wr_next)
#घोषणा cxgbi_skcb_tx_iscsi_hdrlen(skb)	(CXGBI_SKB_CB(skb)->tx.iscsi_hdr_len)
#घोषणा cxgbi_skcb_tx_ulp_mode(skb)	(CXGBI_SKB_CB(skb)->tx.ulp_mode)

अटल अंतरभूत व्योम cxgbi_skcb_set_flag(काष्ठा sk_buff *skb,
					क्रमागत cxgbi_skcb_flags flag)
अणु
	__set_bit(flag, &(cxgbi_skcb_flags(skb)));
पूर्ण

अटल अंतरभूत व्योम cxgbi_skcb_clear_flag(काष्ठा sk_buff *skb,
					क्रमागत cxgbi_skcb_flags flag)
अणु
	__clear_bit(flag, &(cxgbi_skcb_flags(skb)));
पूर्ण

अटल अंतरभूत पूर्णांक cxgbi_skcb_test_flag(स्थिर काष्ठा sk_buff *skb,
				       क्रमागत cxgbi_skcb_flags flag)
अणु
	वापस test_bit(flag, &(cxgbi_skcb_flags(skb)));
पूर्ण

अटल अंतरभूत व्योम cxgbi_sock_set_flag(काष्ठा cxgbi_sock *csk,
					क्रमागत cxgbi_sock_flags flag)
अणु
	__set_bit(flag, &csk->flags);
	log_debug(1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx, bit %d.\n",
		csk, csk->state, csk->flags, flag);
पूर्ण

अटल अंतरभूत व्योम cxgbi_sock_clear_flag(काष्ठा cxgbi_sock *csk,
					क्रमागत cxgbi_sock_flags flag)
अणु
	__clear_bit(flag, &csk->flags);
	log_debug(1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx, bit %d.\n",
		csk, csk->state, csk->flags, flag);
पूर्ण

अटल अंतरभूत पूर्णांक cxgbi_sock_flag(काष्ठा cxgbi_sock *csk,
				क्रमागत cxgbi_sock_flags flag)
अणु
	अगर (csk == शून्य)
		वापस 0;
	वापस test_bit(flag, &csk->flags);
पूर्ण

अटल अंतरभूत व्योम cxgbi_sock_set_state(काष्ठा cxgbi_sock *csk, पूर्णांक state)
अणु
	log_debug(1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx, state -> %u.\n",
		csk, csk->state, csk->flags, state);
	csk->state = state;
पूर्ण

अटल अंतरभूत व्योम cxgbi_sock_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा cxgbi_sock *csk = container_of(kref,
						काष्ठा cxgbi_sock,
						refcnt);
	अगर (csk) अणु
		log_debug(1 << CXGBI_DBG_SOCK,
			"free csk 0x%p, state %u, flags 0x%lx\n",
			csk, csk->state, csk->flags);
		kमुक्त(csk);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __cxgbi_sock_put(स्थिर अक्षर *fn, काष्ठा cxgbi_sock *csk)
अणु
	log_debug(1 << CXGBI_DBG_SOCK,
		"%s, put csk 0x%p, ref %u-1.\n",
		fn, csk, kref_पढ़ो(&csk->refcnt));
	kref_put(&csk->refcnt, cxgbi_sock_मुक्त);
पूर्ण
#घोषणा cxgbi_sock_put(csk)	__cxgbi_sock_put(__func__, csk)

अटल अंतरभूत व्योम __cxgbi_sock_get(स्थिर अक्षर *fn, काष्ठा cxgbi_sock *csk)
अणु
	log_debug(1 << CXGBI_DBG_SOCK,
		"%s, get csk 0x%p, ref %u+1.\n",
		fn, csk, kref_पढ़ो(&csk->refcnt));
	kref_get(&csk->refcnt);
पूर्ण
#घोषणा cxgbi_sock_get(csk)	__cxgbi_sock_get(__func__, csk)

अटल अंतरभूत पूर्णांक cxgbi_sock_is_closing(काष्ठा cxgbi_sock *csk)
अणु
	वापस csk->state >= CTP_ACTIVE_CLOSE;
पूर्ण

अटल अंतरभूत पूर्णांक cxgbi_sock_is_established(काष्ठा cxgbi_sock *csk)
अणु
	वापस csk->state == CTP_ESTABLISHED;
पूर्ण

अटल अंतरभूत व्योम cxgbi_sock_purge_ग_लिखो_queue(काष्ठा cxgbi_sock *csk)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = __skb_dequeue(&csk->ग_लिखो_queue)))
		__kमुक्त_skb(skb);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cxgbi_sock_compute_wscale(अचिन्हित पूर्णांक win)
अणु
	अचिन्हित पूर्णांक wscale = 0;

	जबतक (wscale < 14 && (65535 << wscale) < win)
		wscale++;
	वापस wscale;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *alloc_wr(पूर्णांक wrlen, पूर्णांक dlen, gfp_t gfp)
अणु
	काष्ठा sk_buff *skb = alloc_skb(wrlen + dlen, gfp);

	अगर (skb) अणु
		__skb_put(skb, wrlen);
		स_रखो(skb->head, 0, wrlen + dlen);
	पूर्ण अन्यथा
		pr_info("alloc cpl wr skb %u+%u, OOM.\n", wrlen, dlen);
	वापस skb;
पूर्ण


/*
 * The number of WRs needed क्रम an skb depends on the number of fragments
 * in the skb and whether it has any payload in its मुख्य body.  This maps the
 * length of the gather list represented by an skb पूर्णांकo the # of necessary WRs.
 * The extra two fragments are क्रम iscsi bhs and payload padding.
 */
#घोषणा SKB_WR_LIST_SIZE	 (MAX_SKB_FRAGS + 2)

अटल अंतरभूत व्योम cxgbi_sock_reset_wr_list(काष्ठा cxgbi_sock *csk)
अणु
	csk->wr_pending_head = csk->wr_pending_tail = शून्य;
पूर्ण

अटल अंतरभूत व्योम cxgbi_sock_enqueue_wr(काष्ठा cxgbi_sock *csk,
					  काष्ठा sk_buff *skb)
अणु
	cxgbi_skcb_tx_wr_next(skb) = शून्य;
	/*
	 * We want to take an extra reference since both us and the driver
	 * need to मुक्त the packet beक्रमe it's really मुक्तd.
	 */
	skb_get(skb);

	अगर (!csk->wr_pending_head)
		csk->wr_pending_head = skb;
	अन्यथा
		cxgbi_skcb_tx_wr_next(csk->wr_pending_tail) = skb;
	csk->wr_pending_tail = skb;
पूर्ण

अटल अंतरभूत पूर्णांक cxgbi_sock_count_pending_wrs(स्थिर काष्ठा cxgbi_sock *csk)
अणु
	पूर्णांक n = 0;
	स्थिर काष्ठा sk_buff *skb = csk->wr_pending_head;

	जबतक (skb) अणु
		n += skb->csum;
		skb = cxgbi_skcb_tx_wr_next(skb);
	पूर्ण
	वापस n;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *cxgbi_sock_peek_wr(स्थिर काष्ठा cxgbi_sock *csk)
अणु
	वापस csk->wr_pending_head;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *cxgbi_sock_dequeue_wr(काष्ठा cxgbi_sock *csk)
अणु
	काष्ठा sk_buff *skb = csk->wr_pending_head;

	अगर (likely(skb)) अणु
		csk->wr_pending_head = cxgbi_skcb_tx_wr_next(skb);
		cxgbi_skcb_tx_wr_next(skb) = शून्य;
	पूर्ण
	वापस skb;
पूर्ण

व्योम cxgbi_sock_check_wr_invariants(स्थिर काष्ठा cxgbi_sock *);
व्योम cxgbi_sock_purge_wr_queue(काष्ठा cxgbi_sock *);
व्योम cxgbi_sock_skb_entail(काष्ठा cxgbi_sock *, काष्ठा sk_buff *);
व्योम cxgbi_sock_fail_act_खोलो(काष्ठा cxgbi_sock *, पूर्णांक);
व्योम cxgbi_sock_act_खोलो_req_arp_failure(व्योम *, काष्ठा sk_buff *);
व्योम cxgbi_sock_बंदd(काष्ठा cxgbi_sock *);
व्योम cxgbi_sock_established(काष्ठा cxgbi_sock *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
व्योम cxgbi_sock_rcv_पात_rpl(काष्ठा cxgbi_sock *);
व्योम cxgbi_sock_rcv_peer_बंद(काष्ठा cxgbi_sock *);
व्योम cxgbi_sock_rcv_बंद_conn_rpl(काष्ठा cxgbi_sock *, u32);
व्योम cxgbi_sock_rcv_wr_ack(काष्ठा cxgbi_sock *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक,
				पूर्णांक);
अचिन्हित पूर्णांक cxgbi_sock_select_mss(काष्ठा cxgbi_sock *, अचिन्हित पूर्णांक);
व्योम cxgbi_sock_मुक्त_cpl_skbs(काष्ठा cxgbi_sock *);

काष्ठा cxgbi_hba अणु
	काष्ठा net_device *ndev;
	काष्ठा net_device *vdev;	/* vlan dev */
	काष्ठा Scsi_Host *shost;
	काष्ठा cxgbi_device *cdev;
	__be32 ipv4addr;
	अचिन्हित अक्षर port_id;
पूर्ण;

काष्ठा cxgbi_ports_map अणु
	अचिन्हित पूर्णांक max_connect;
	अचिन्हित पूर्णांक used;
	अचिन्हित लघु sport_base;
	spinlock_t lock;
	अचिन्हित पूर्णांक next;
	काष्ठा cxgbi_sock **port_csk;
पूर्ण;

#घोषणा CXGBI_FLAG_DEV_T3		0x1
#घोषणा CXGBI_FLAG_DEV_T4		0x2
#घोषणा CXGBI_FLAG_ADAPTER_RESET	0x4
#घोषणा CXGBI_FLAG_IPV4_SET		0x10
#घोषणा CXGBI_FLAG_USE_PPOD_OFLDQ       0x40
#घोषणा CXGBI_FLAG_DDP_OFF		0x100
#घोषणा CXGBI_FLAG_DEV_ISO_OFF		0x400

काष्ठा cxgbi_device अणु
	काष्ठा list_head list_head;
	काष्ठा list_head rcu_node;
	अचिन्हित पूर्णांक flags;
	काष्ठा net_device **ports;
	व्योम *lldev;
	काष्ठा cxgbi_hba **hbas;
	स्थिर अचिन्हित लघु *mtus;
	अचिन्हित अक्षर nmtus;
	अचिन्हित अक्षर nports;
	काष्ठा pci_dev *pdev;
	काष्ठा dentry *debugfs_root;
	काष्ठा iscsi_transport *itp;
	काष्ठा module *owner;

	अचिन्हित पूर्णांक pfvf;
	अचिन्हित पूर्णांक rx_credit_thres;
	अचिन्हित पूर्णांक skb_tx_rsvd;
	u32 skb_iso_txhdr;
	अचिन्हित पूर्णांक skb_rx_extra;	/* क्रम msg coalesced mode */
	अचिन्हित पूर्णांक tx_max_size;
	अचिन्हित पूर्णांक rx_max_size;
	अचिन्हित पूर्णांक rxq_idx_cntr;
	काष्ठा cxgbi_ports_map pmap;

	व्योम (*dev_ddp_cleanup)(काष्ठा cxgbi_device *);
	काष्ठा cxgbi_ppm* (*cdev2ppm)(काष्ठा cxgbi_device *);
	पूर्णांक (*csk_ddp_set_map)(काष्ठा cxgbi_ppm *, काष्ठा cxgbi_sock *,
			       काष्ठा cxgbi_task_tag_info *);
	व्योम (*csk_ddp_clear_map)(काष्ठा cxgbi_device *cdev,
				  काष्ठा cxgbi_ppm *,
				  काष्ठा cxgbi_task_tag_info *);
	पूर्णांक (*csk_ddp_setup_digest)(काष्ठा cxgbi_sock *,
				    अचिन्हित पूर्णांक, पूर्णांक, पूर्णांक);
	पूर्णांक (*csk_ddp_setup_pgidx)(काष्ठा cxgbi_sock *,
				   अचिन्हित पूर्णांक, पूर्णांक);

	व्योम (*csk_release_offload_resources)(काष्ठा cxgbi_sock *);
	पूर्णांक (*csk_rx_pdu_पढ़ोy)(काष्ठा cxgbi_sock *, काष्ठा sk_buff *);
	u32 (*csk_send_rx_credits)(काष्ठा cxgbi_sock *, u32);
	पूर्णांक (*csk_push_tx_frames)(काष्ठा cxgbi_sock *, पूर्णांक);
	व्योम (*csk_send_पात_req)(काष्ठा cxgbi_sock *);
	व्योम (*csk_send_बंद_req)(काष्ठा cxgbi_sock *);
	पूर्णांक (*csk_alloc_cpls)(काष्ठा cxgbi_sock *);
	पूर्णांक (*csk_init_act_खोलो)(काष्ठा cxgbi_sock *);

	व्योम *dd_data;
पूर्ण;
#घोषणा cxgbi_cdev_priv(cdev)	((cdev)->dd_data)

काष्ठा cxgbi_conn अणु
	काष्ठा cxgbi_endpoपूर्णांक *cep;
	काष्ठा iscsi_conn *iconn;
	काष्ठा cxgbi_hba *chba;
	u32 task_idx_bits;
	अचिन्हित पूर्णांक ddp_full;
	अचिन्हित पूर्णांक ddp_tag_full;
पूर्ण;

काष्ठा cxgbi_endpoपूर्णांक अणु
	काष्ठा cxgbi_conn *cconn;
	काष्ठा cxgbi_hba *chba;
	काष्ठा cxgbi_sock *csk;
पूर्ण;

काष्ठा cxgbi_task_data अणु
#घोषणा CXGBI_TASK_SGL_CHECKED	0x1
#घोषणा CXGBI_TASK_SGL_COPY	0x2
	u8 flags;
	अचिन्हित लघु nr_frags;
	काष्ठा page_frag frags[MAX_SKB_FRAGS];
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक dlen;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक sgoffset;
	u32 total_count;
	u32 total_offset;
	u32 max_xmit_dlength;
	काष्ठा cxgbi_task_tag_info ttinfo;
पूर्ण;
#घोषणा iscsi_task_cxgbi_data(task) \
	((task)->dd_data + माप(काष्ठा iscsi_tcp_task))

काष्ठा cxgbi_iso_info अणु
#घोषणा CXGBI_ISO_INFO_FSLICE		0x1
#घोषणा CXGBI_ISO_INFO_LSLICE		0x2
#घोषणा CXGBI_ISO_INFO_IMM_ENABLE	0x4
	u8 flags;
	u8 op;
	u8 ahs;
	u8 num_pdu;
	u32 mpdu;
	u32 burst_size;
	u32 len;
	u32 segment_offset;
	u32 datasn_offset;
	u32 buffer_offset;
पूर्ण;

अटल अंतरभूत व्योम cxgbi_set_iscsi_ipv4(काष्ठा cxgbi_hba *chba, __be32 ipaddr)
अणु
	अगर (chba->cdev->flags & CXGBI_FLAG_IPV4_SET)
		chba->ipv4addr = ipaddr;
	अन्यथा
		pr_info("set iscsi ipv4 NOT supported, using %s ipv4.\n",
			chba->ndev->name);
पूर्ण

काष्ठा cxgbi_device *cxgbi_device_रेजिस्टर(अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
व्योम cxgbi_device_unरेजिस्टर(काष्ठा cxgbi_device *);
व्योम cxgbi_device_unरेजिस्टर_all(अचिन्हित पूर्णांक flag);
काष्ठा cxgbi_device *cxgbi_device_find_by_lldev(व्योम *);
काष्ठा cxgbi_device *cxgbi_device_find_by_netdev(काष्ठा net_device *, पूर्णांक *);
काष्ठा cxgbi_device *cxgbi_device_find_by_netdev_rcu(काष्ठा net_device *,
						     पूर्णांक *);
पूर्णांक cxgbi_hbas_add(काष्ठा cxgbi_device *, u64, अचिन्हित पूर्णांक,
			काष्ठा scsi_host_ढाँचा *,
			काष्ठा scsi_transport_ढाँचा *);
व्योम cxgbi_hbas_हटाओ(काष्ठा cxgbi_device *);

पूर्णांक cxgbi_device_porपंचांगap_create(काष्ठा cxgbi_device *cdev, अचिन्हित पूर्णांक base,
			अचिन्हित पूर्णांक max_conn);
व्योम cxgbi_device_porपंचांगap_cleanup(काष्ठा cxgbi_device *cdev);

व्योम cxgbi_conn_tx_खोलो(काष्ठा cxgbi_sock *);
व्योम cxgbi_conn_pdu_पढ़ोy(काष्ठा cxgbi_sock *);
पूर्णांक cxgbi_conn_alloc_pdu(काष्ठा iscsi_task *, u8);
पूर्णांक cxgbi_conn_init_pdu(काष्ठा iscsi_task *, अचिन्हित पूर्णांक , अचिन्हित पूर्णांक);
पूर्णांक cxgbi_conn_xmit_pdu(काष्ठा iscsi_task *);

व्योम cxgbi_cleanup_task(काष्ठा iscsi_task *task);

umode_t cxgbi_attr_is_visible(पूर्णांक param_type, पूर्णांक param);
व्योम cxgbi_get_conn_stats(काष्ठा iscsi_cls_conn *, काष्ठा iscsi_stats *);
पूर्णांक cxgbi_set_conn_param(काष्ठा iscsi_cls_conn *,
			क्रमागत iscsi_param, अक्षर *, पूर्णांक);
पूर्णांक cxgbi_get_ep_param(काष्ठा iscsi_endpoपूर्णांक *ep, क्रमागत iscsi_param, अक्षर *);
काष्ठा iscsi_cls_conn *cxgbi_create_conn(काष्ठा iscsi_cls_session *, u32);
पूर्णांक cxgbi_bind_conn(काष्ठा iscsi_cls_session *,
			काष्ठा iscsi_cls_conn *, u64, पूर्णांक);
व्योम cxgbi_destroy_session(काष्ठा iscsi_cls_session *);
काष्ठा iscsi_cls_session *cxgbi_create_session(काष्ठा iscsi_endpoपूर्णांक *,
			u16, u16, u32);
पूर्णांक cxgbi_set_host_param(काष्ठा Scsi_Host *,
			क्रमागत iscsi_host_param, अक्षर *, पूर्णांक);
पूर्णांक cxgbi_get_host_param(काष्ठा Scsi_Host *, क्रमागत iscsi_host_param, अक्षर *);
काष्ठा iscsi_endpoपूर्णांक *cxgbi_ep_connect(काष्ठा Scsi_Host *,
			काष्ठा sockaddr *, पूर्णांक);
पूर्णांक cxgbi_ep_poll(काष्ठा iscsi_endpoपूर्णांक *, पूर्णांक);
व्योम cxgbi_ep_disconnect(काष्ठा iscsi_endpoपूर्णांक *);

पूर्णांक cxgbi_iscsi_init(काष्ठा iscsi_transport *,
			काष्ठा scsi_transport_ढाँचा **);
व्योम cxgbi_iscsi_cleanup(काष्ठा iscsi_transport *,
			काष्ठा scsi_transport_ढाँचा **);
व्योम cxgbi_parse_pdu_itt(काष्ठा iscsi_conn *, itt_t, पूर्णांक *, पूर्णांक *);
पूर्णांक cxgbi_ddp_init(काष्ठा cxgbi_device *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक,
			अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
पूर्णांक cxgbi_ddp_cleanup(काष्ठा cxgbi_device *);
व्योम cxgbi_ddp_page_size_factor(पूर्णांक *);
व्योम cxgbi_ddp_set_one_ppod(काष्ठा cxgbi_pagepod *,
			    काष्ठा cxgbi_task_tag_info *,
			    काष्ठा scatterlist **sg_pp, अचिन्हित पूर्णांक *sg_off);
पूर्णांक cxgbi_ddp_ppm_setup(व्योम **ppm_pp, काष्ठा cxgbi_device *cdev,
			काष्ठा cxgbi_tag_क्रमmat *tक्रमmat,
			अचिन्हित पूर्णांक iscsi_size, अचिन्हित पूर्णांक llimit,
			अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक rsvd_factor,
			अचिन्हित पूर्णांक edram_start, अचिन्हित पूर्णांक edram_size);
#पूर्ण_अगर	/*__LIBCXGBI_H__*/
