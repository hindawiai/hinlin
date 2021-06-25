<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 *  Definitions क्रम SMC Connections, Link Groups and Links
 *
 *  Copyright IBM Corp. 2016
 *
 *  Author(s):  Ursula Braun <ubraun@linux.vnet.ibm.com>
 */

#अगर_अघोषित _SMC_CORE_H
#घोषणा _SMC_CORE_H

#समावेश <linux/atomic.h>
#समावेश <linux/smc.h>
#समावेश <linux/pci.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <net/genetlink.h>

#समावेश "smc.h"
#समावेश "smc_ib.h"

#घोषणा SMC_RMBS_PER_LGR_MAX	255	/* max. # of RMBs per link group */

काष्ठा smc_lgr_list अणु			/* list of link group definition */
	काष्ठा list_head	list;
	spinlock_t		lock;	/* protects list of link groups */
	u32			num;	/* unique link group number */
पूर्ण;

क्रमागत smc_lgr_role अणु		/* possible roles of a link group */
	SMC_CLNT,	/* client */
	SMC_SERV	/* server */
पूर्ण;

क्रमागत smc_link_state अणु			/* possible states of a link */
	SMC_LNK_UNUSED,		/* link is unused */
	SMC_LNK_INACTIVE,	/* link is inactive */
	SMC_LNK_ACTIVATING,	/* link is being activated */
	SMC_LNK_ACTIVE,		/* link is active */
पूर्ण;

#घोषणा SMC_WR_BUF_SIZE		48	/* size of work request buffer */

काष्ठा smc_wr_buf अणु
	u8	raw[SMC_WR_BUF_SIZE];
पूर्ण;

#घोषणा SMC_WR_REG_MR_WAIT_TIME	(5 * HZ)/* रुको समय क्रम ib_wr_reg_mr result */

क्रमागत smc_wr_reg_state अणु
	POSTED,		/* ib_wr_reg_mr request posted */
	CONFIRMED,	/* ib_wr_reg_mr response: successful */
	FAILED		/* ib_wr_reg_mr response: failure */
पूर्ण;

काष्ठा smc_rdma_sge अणु				/* sges क्रम RDMA ग_लिखोs */
	काष्ठा ib_sge		wr_tx_rdma_sge[SMC_IB_MAX_SEND_SGE];
पूर्ण;

#घोषणा SMC_MAX_RDMA_WRITES	2		/* max. # of RDMA ग_लिखोs per
						 * message send
						 */

काष्ठा smc_rdma_sges अणु				/* sges per message send */
	काष्ठा smc_rdma_sge	tx_rdma_sge[SMC_MAX_RDMA_WRITES];
पूर्ण;

काष्ठा smc_rdma_wr अणु				/* work requests per message
						 * send
						 */
	काष्ठा ib_rdma_wr	wr_tx_rdma[SMC_MAX_RDMA_WRITES];
पूर्ण;

#घोषणा SMC_LGR_ID_SIZE		4

काष्ठा smc_link अणु
	काष्ठा smc_ib_device	*smcibdev;	/* ib-device */
	u8			ibport;		/* port - values 1 | 2 */
	काष्ठा ib_pd		*roce_pd;	/* IB protection करोमुख्य,
						 * unique क्रम every RoCE QP
						 */
	काष्ठा ib_qp		*roce_qp;	/* IB queue pair */
	काष्ठा ib_qp_attr	qp_attr;	/* IB queue pair attributes */

	काष्ठा smc_wr_buf	*wr_tx_bufs;	/* WR send payload buffers */
	काष्ठा ib_send_wr	*wr_tx_ibs;	/* WR send meta data */
	काष्ठा ib_sge		*wr_tx_sges;	/* WR send gather meta data */
	काष्ठा smc_rdma_sges	*wr_tx_rdma_sges;/*RDMA WRITE gather meta data*/
	काष्ठा smc_rdma_wr	*wr_tx_rdmas;	/* WR RDMA WRITE */
	काष्ठा smc_wr_tx_pend	*wr_tx_pends;	/* WR send रुकोing क्रम CQE */
	काष्ठा completion	*wr_tx_compl;	/* WR send CQE completion */
	/* above four vectors have wr_tx_cnt elements and use the same index */
	dma_addr_t		wr_tx_dma_addr;	/* DMA address of wr_tx_bufs */
	atomic_दीर्घ_t		wr_tx_id;	/* seq # of last sent WR */
	अचिन्हित दीर्घ		*wr_tx_mask;	/* bit mask of used indexes */
	u32			wr_tx_cnt;	/* number of WR send buffers */
	रुको_queue_head_t	wr_tx_रुको;	/* रुको क्रम मुक्त WR send buf */

	काष्ठा smc_wr_buf	*wr_rx_bufs;	/* WR recv payload buffers */
	काष्ठा ib_recv_wr	*wr_rx_ibs;	/* WR recv meta data */
	काष्ठा ib_sge		*wr_rx_sges;	/* WR recv scatter meta data */
	/* above three vectors have wr_rx_cnt elements and use the same index */
	dma_addr_t		wr_rx_dma_addr;	/* DMA address of wr_rx_bufs */
	u64			wr_rx_id;	/* seq # of last recv WR */
	u32			wr_rx_cnt;	/* number of WR recv buffers */
	अचिन्हित दीर्घ		wr_rx_tstamp;	/* jअगरfies when last buf rx */

	काष्ठा ib_reg_wr	wr_reg;		/* WR रेजिस्टर memory region */
	रुको_queue_head_t	wr_reg_रुको;	/* रुको क्रम wr_reg result */
	क्रमागत smc_wr_reg_state	wr_reg_state;	/* state of wr_reg request */

	u8			gid[SMC_GID_SIZE];/* gid matching used vlan id*/
	u8			sgid_index;	/* gid index क्रम vlan id      */
	u32			peer_qpn;	/* QP number of peer */
	क्रमागत ib_mtu		path_mtu;	/* used mtu */
	क्रमागत ib_mtu		peer_mtu;	/* mtu size of peer */
	u32			psn_initial;	/* QP tx initial packet seqno */
	u32			peer_psn;	/* QP rx initial packet seqno */
	u8			peer_mac[ETH_ALEN];	/* = gid[8:10||13:15] */
	u8			peer_gid[SMC_GID_SIZE];	/* gid of peer*/
	u8			link_id;	/* unique # within link group */
	u8			link_uid[SMC_LGR_ID_SIZE]; /* unique lnk id */
	u8			peer_link_uid[SMC_LGR_ID_SIZE]; /* peer uid */
	u8			link_idx;	/* index in lgr link array */
	u8			link_is_asym;	/* is link asymmetric? */
	काष्ठा smc_link_group	*lgr;		/* parent link group */
	काष्ठा work_काष्ठा	link_करोwn_wrk;	/* wrk to bring link करोwn */
	अक्षर			ibname[IB_DEVICE_NAME_MAX]; /* ib device name */
	पूर्णांक			ndev_अगरidx; /* network device अगरindex */

	क्रमागत smc_link_state	state;		/* state of link */
	काष्ठा delayed_work	llc_testlink_wrk; /* testlink worker */
	काष्ठा completion	llc_testlink_resp; /* रुको क्रम rx of testlink */
	पूर्णांक			llc_testlink_समय; /* testlink पूर्णांकerval */
	atomic_t		conn_cnt; /* connections on this link */
पूर्ण;

/* For now we just allow one parallel link per link group. The SMC protocol
 * allows more (up to 8).
 */
#घोषणा SMC_LINKS_PER_LGR_MAX	3
#घोषणा SMC_SINGLE_LINK		0

/* tx/rx buffer list element क्रम sndbufs list and rmbs list of a lgr */
काष्ठा smc_buf_desc अणु
	काष्ठा list_head	list;
	व्योम			*cpu_addr;	/* भव address of buffer */
	काष्ठा page		*pages;
	पूर्णांक			len;		/* length of buffer */
	u32			used;		/* currently used / unused */
	जोड़ अणु
		काष्ठा अणु /* SMC-R */
			काष्ठा sg_table	sgt[SMC_LINKS_PER_LGR_MAX];
					/* भव buffer */
			काष्ठा ib_mr	*mr_rx[SMC_LINKS_PER_LGR_MAX];
					/* क्रम rmb only: memory region
					 * incl. rkey provided to peer
					 */
			u32		order;	/* allocation order */

			u8		is_conf_rkey;
					/* confirm_rkey करोne */
			u8		is_reg_mr[SMC_LINKS_PER_LGR_MAX];
					/* mem region रेजिस्टरed */
			u8		is_map_ib[SMC_LINKS_PER_LGR_MAX];
					/* mem region mapped to lnk */
			u8		is_reg_err;
					/* buffer registration err */
		पूर्ण;
		काष्ठा अणु /* SMC-D */
			अचिन्हित लघु	sba_idx;
					/* SBA index number */
			u64		token;
					/* DMB token number */
			dma_addr_t	dma_addr;
					/* DMA address */
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा smc_rtoken अणु				/* address/key of remote RMB */
	u64			dma_addr;
	u32			rkey;
पूर्ण;

#घोषणा SMC_BUF_MIN_SIZE	16384	/* minimum size of an RMB */
#घोषणा SMC_RMBE_SIZES		16	/* number of distinct RMBE sizes */
/* theoretically, the RFC states that largest size would be 512K,
 * i.e. compressed 5 and thus 6 sizes (0..5), despite
 * काष्ठा smc_clc_msg_accept_confirm.rmbe_size being a 4 bit value (0..15)
 */

काष्ठा smcd_dev;

क्रमागत smc_lgr_type अणु				/* redundancy state of lgr */
	SMC_LGR_NONE,			/* no active links, lgr to be deleted */
	SMC_LGR_SINGLE,			/* 1 active RNIC on each peer */
	SMC_LGR_SYMMETRIC,		/* 2 active RNICs on each peer */
	SMC_LGR_ASYMMETRIC_PEER,	/* local has 2, peer 1 active RNICs */
	SMC_LGR_ASYMMETRIC_LOCAL,	/* local has 1, peer 2 active RNICs */
पूर्ण;

क्रमागत smc_llc_flowtype अणु
	SMC_LLC_FLOW_NONE	= 0,
	SMC_LLC_FLOW_ADD_LINK	= 2,
	SMC_LLC_FLOW_DEL_LINK	= 4,
	SMC_LLC_FLOW_RKEY	= 6,
पूर्ण;

काष्ठा smc_llc_qentry;

काष्ठा smc_llc_flow अणु
	क्रमागत smc_llc_flowtype type;
	काष्ठा smc_llc_qentry *qentry;
पूर्ण;

काष्ठा smc_link_group अणु
	काष्ठा list_head	list;
	काष्ठा rb_root		conns_all;	/* connection tree */
	rwlock_t		conns_lock;	/* protects conns_all */
	अचिन्हित पूर्णांक		conns_num;	/* current # of connections */
	अचिन्हित लघु		vlan_id;	/* vlan id of link group */

	काष्ठा list_head	sndbufs[SMC_RMBE_SIZES];/* tx buffers */
	काष्ठा mutex		sndbufs_lock;	/* protects tx buffers */
	काष्ठा list_head	rmbs[SMC_RMBE_SIZES];	/* rx buffers */
	काष्ठा mutex		rmbs_lock;	/* protects rx buffers */

	u8			id[SMC_LGR_ID_SIZE];	/* unique lgr id */
	काष्ठा delayed_work	मुक्त_work;	/* delayed मुक्तing of an lgr */
	काष्ठा work_काष्ठा	terminate_work;	/* abnormal lgr termination */
	काष्ठा workqueue_काष्ठा	*tx_wq;		/* wq क्रम conn. tx workers */
	u8			sync_err : 1;	/* lgr no दीर्घer fits to peer */
	u8			terminating : 1;/* lgr is terminating */
	u8			मुक्तing : 1;	/* lgr is being मुक्तd */

	bool			is_smcd;	/* SMC-R or SMC-D */
	u8			smc_version;
	u8			negotiated_eid[SMC_MAX_EID_LEN];
	u8			peer_os;	/* peer operating प्रणाली */
	u8			peer_smc_release;
	u8			peer_hostname[SMC_MAX_HOSTNAME_LEN];
	जोड़ अणु
		काष्ठा अणु /* SMC-R */
			क्रमागत smc_lgr_role	role;
						/* client or server */
			काष्ठा smc_link		lnk[SMC_LINKS_PER_LGR_MAX];
						/* smc link */
			अक्षर			peer_प्रणालीid[SMC_SYSTEMID_LEN];
						/* unique प्रणाली_id of peer */
			काष्ठा smc_rtoken	rtokens[SMC_RMBS_PER_LGR_MAX]
						[SMC_LINKS_PER_LGR_MAX];
						/* remote addr/key pairs */
			DECLARE_BITMAP(rtokens_used_mask, SMC_RMBS_PER_LGR_MAX);
						/* used rtoken elements */
			u8			next_link_id;
			क्रमागत smc_lgr_type	type;
						/* redundancy state */
			u8			pnet_id[SMC_MAX_PNETID_LEN + 1];
						/* pnet id of this lgr */
			काष्ठा list_head	llc_event_q;
						/* queue क्रम llc events */
			spinlock_t		llc_event_q_lock;
						/* protects llc_event_q */
			काष्ठा mutex		llc_conf_mutex;
						/* protects lgr reconfig. */
			काष्ठा work_काष्ठा	llc_add_link_work;
			काष्ठा work_काष्ठा	llc_del_link_work;
			काष्ठा work_काष्ठा	llc_event_work;
						/* llc event worker */
			रुको_queue_head_t	llc_flow_रुकोer;
						/* w4 next llc event */
			रुको_queue_head_t	llc_msg_रुकोer;
						/* w4 next llc msg */
			काष्ठा smc_llc_flow	llc_flow_lcl;
						/* llc local control field */
			काष्ठा smc_llc_flow	llc_flow_rmt;
						/* llc remote control field */
			काष्ठा smc_llc_qentry	*delayed_event;
						/* arrived when flow active */
			spinlock_t		llc_flow_lock;
						/* protects llc flow */
			पूर्णांक			llc_testlink_समय;
						/* link keep alive समय */
			u32			llc_termination_rsn;
						/* rsn code क्रम termination */
		पूर्ण;
		काष्ठा अणु /* SMC-D */
			u64			peer_gid;
						/* Peer GID (remote) */
			काष्ठा smcd_dev		*smcd;
						/* ISM device क्रम VLAN reg. */
			u8			peer_shutकरोwn : 1;
						/* peer triggered shutकरोwnn */
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा smc_clc_msg_local;

काष्ठा smc_init_info अणु
	u8			is_smcd;
	u8			smc_type_v1;
	u8			smc_type_v2;
	u8			first_contact_peer;
	u8			first_contact_local;
	अचिन्हित लघु		vlan_id;
	u32			rc;
	/* SMC-R */
	काष्ठा smc_clc_msg_local *ib_lcl;
	काष्ठा smc_ib_device	*ib_dev;
	u8			ib_gid[SMC_GID_SIZE];
	u8			ib_port;
	u32			ib_clcqpn;
	/* SMC-D */
	u64			ism_peer_gid[SMC_MAX_ISM_DEVS + 1];
	काष्ठा smcd_dev		*ism_dev[SMC_MAX_ISM_DEVS + 1];
	u16			ism_chid[SMC_MAX_ISM_DEVS + 1];
	u8			ism_offered_cnt; /* # of ISM devices offered */
	u8			ism_selected;    /* index of selected ISM dev*/
	u8			smcd_version;
पूर्ण;

/* Find the connection associated with the given alert token in the link group.
 * To use rbtrees we have to implement our own search core.
 * Requires @conns_lock
 * @token	alert token to search क्रम
 * @lgr		 link group to search in
 * Returns connection associated with token अगर found, शून्य otherwise.
 */
अटल अंतरभूत काष्ठा smc_connection *smc_lgr_find_conn(
	u32 token, काष्ठा smc_link_group *lgr)
अणु
	काष्ठा smc_connection *res = शून्य;
	काष्ठा rb_node *node;

	node = lgr->conns_all.rb_node;
	जबतक (node) अणु
		काष्ठा smc_connection *cur = rb_entry(node,
					काष्ठा smc_connection, alert_node);

		अगर (cur->alert_token_local > token) अणु
			node = node->rb_left;
		पूर्ण अन्यथा अणु
			अगर (cur->alert_token_local < token) अणु
				node = node->rb_right;
			पूर्ण अन्यथा अणु
				res = cur;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस res;
पूर्ण

/* वापसs true अगर the specअगरied link is usable */
अटल अंतरभूत bool smc_link_usable(काष्ठा smc_link *lnk)
अणु
	अगर (lnk->state == SMC_LNK_UNUSED || lnk->state == SMC_LNK_INACTIVE)
		वापस false;
	वापस true;
पूर्ण

अटल अंतरभूत bool smc_link_active(काष्ठा smc_link *lnk)
अणु
	वापस lnk->state == SMC_LNK_ACTIVE;
पूर्ण

अटल अंतरभूत व्योम smc_gid_be16_convert(__u8 *buf, u8 *gid_raw)
अणु
	प्र_लिखो(buf, "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x",
		be16_to_cpu(((__be16 *)gid_raw)[0]),
		be16_to_cpu(((__be16 *)gid_raw)[1]),
		be16_to_cpu(((__be16 *)gid_raw)[2]),
		be16_to_cpu(((__be16 *)gid_raw)[3]),
		be16_to_cpu(((__be16 *)gid_raw)[4]),
		be16_to_cpu(((__be16 *)gid_raw)[5]),
		be16_to_cpu(((__be16 *)gid_raw)[6]),
		be16_to_cpu(((__be16 *)gid_raw)[7]));
पूर्ण

काष्ठा smc_pci_dev अणु
	__u32		pci_fid;
	__u16		pci_pchid;
	__u16		pci_venकरोr;
	__u16		pci_device;
	__u8		pci_id[SMC_PCI_ID_STR_LEN];
पूर्ण;

अटल अंतरभूत व्योम smc_set_pci_values(काष्ठा pci_dev *pci_dev,
				      काष्ठा smc_pci_dev *smc_dev)
अणु
	smc_dev->pci_venकरोr = pci_dev->venकरोr;
	smc_dev->pci_device = pci_dev->device;
	snम_लिखो(smc_dev->pci_id, माप(smc_dev->pci_id), "%s",
		 pci_name(pci_dev));
#अगर IS_ENABLED(CONFIG_S390)
	अणु /* Set s390 specअगरic PCI inक्रमmation */
	काष्ठा zpci_dev *zdev;

	zdev = to_zpci(pci_dev);
	smc_dev->pci_fid = zdev->fid;
	smc_dev->pci_pchid = zdev->pchid;
	पूर्ण
#पूर्ण_अगर
पूर्ण

काष्ठा smc_sock;
काष्ठा smc_clc_msg_accept_confirm;

व्योम smc_lgr_cleanup_early(काष्ठा smc_connection *conn);
व्योम smc_lgr_terminate_sched(काष्ठा smc_link_group *lgr);
व्योम smcr_port_add(काष्ठा smc_ib_device *smcibdev, u8 ibport);
व्योम smcr_port_err(काष्ठा smc_ib_device *smcibdev, u8 ibport);
व्योम smc_smcd_terminate(काष्ठा smcd_dev *dev, u64 peer_gid,
			अचिन्हित लघु vlan);
व्योम smc_smcd_terminate_all(काष्ठा smcd_dev *dev);
व्योम smc_smcr_terminate_all(काष्ठा smc_ib_device *smcibdev);
पूर्णांक smc_buf_create(काष्ठा smc_sock *smc, bool is_smcd);
पूर्णांक smc_uncompress_bufsize(u8 compressed);
पूर्णांक smc_rmb_rtoken_handling(काष्ठा smc_connection *conn, काष्ठा smc_link *link,
			    काष्ठा smc_clc_msg_accept_confirm *clc);
पूर्णांक smc_rtoken_add(काष्ठा smc_link *lnk, __be64 nw_vaddr, __be32 nw_rkey);
पूर्णांक smc_rtoken_delete(काष्ठा smc_link *lnk, __be32 nw_rkey);
व्योम smc_rtoken_set(काष्ठा smc_link_group *lgr, पूर्णांक link_idx, पूर्णांक link_idx_new,
		    __be32 nw_rkey_known, __be64 nw_vaddr, __be32 nw_rkey);
व्योम smc_rtoken_set2(काष्ठा smc_link_group *lgr, पूर्णांक rtok_idx, पूर्णांक link_id,
		     __be64 nw_vaddr, __be32 nw_rkey);
व्योम smc_sndbuf_sync_sg_क्रम_cpu(काष्ठा smc_connection *conn);
व्योम smc_sndbuf_sync_sg_क्रम_device(काष्ठा smc_connection *conn);
व्योम smc_rmb_sync_sg_क्रम_cpu(काष्ठा smc_connection *conn);
व्योम smc_rmb_sync_sg_क्रम_device(काष्ठा smc_connection *conn);
पूर्णांक smc_vlan_by_tcpsk(काष्ठा socket *clcsock, काष्ठा smc_init_info *ini);

व्योम smc_conn_मुक्त(काष्ठा smc_connection *conn);
पूर्णांक smc_conn_create(काष्ठा smc_sock *smc, काष्ठा smc_init_info *ini);
व्योम smc_lgr_schedule_मुक्त_work_fast(काष्ठा smc_link_group *lgr);
पूर्णांक smc_core_init(व्योम);
व्योम smc_core_निकास(व्योम);

पूर्णांक smcr_link_init(काष्ठा smc_link_group *lgr, काष्ठा smc_link *lnk,
		   u8 link_idx, काष्ठा smc_init_info *ini);
व्योम smcr_link_clear(काष्ठा smc_link *lnk, bool log);
पूर्णांक smcr_buf_map_lgr(काष्ठा smc_link *lnk);
पूर्णांक smcr_buf_reg_lgr(काष्ठा smc_link *lnk);
व्योम smcr_lgr_set_type(काष्ठा smc_link_group *lgr, क्रमागत smc_lgr_type new_type);
व्योम smcr_lgr_set_type_asym(काष्ठा smc_link_group *lgr,
			    क्रमागत smc_lgr_type new_type, पूर्णांक asym_lnk_idx);
पूर्णांक smcr_link_reg_rmb(काष्ठा smc_link *link, काष्ठा smc_buf_desc *rmb_desc);
काष्ठा smc_link *smc_चयन_conns(काष्ठा smc_link_group *lgr,
				  काष्ठा smc_link *from_lnk, bool is_dev_err);
व्योम smcr_link_करोwn_cond(काष्ठा smc_link *lnk);
व्योम smcr_link_करोwn_cond_sched(काष्ठा smc_link *lnk);
पूर्णांक smc_nl_get_sys_info(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);
पूर्णांक smcr_nl_get_lgr(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);
पूर्णांक smcr_nl_get_link(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);
पूर्णांक smcd_nl_get_lgr(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);

अटल अंतरभूत काष्ठा smc_link_group *smc_get_lgr(काष्ठा smc_link *link)
अणु
	वापस link->lgr;
पूर्ण
#पूर्ण_अगर
