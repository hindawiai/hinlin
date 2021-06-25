<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
 * Copyright (c) 2004 Voltaire, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित _IPOIB_H
#घोषणा _IPOIB_H

#समावेश <linux/list.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/kref.h>
#समावेश <linux/अगर_infiniband.h>
#समावेश <linux/mutex.h>

#समावेश <net/neighbour.h>
#समावेश <net/sch_generic.h>

#समावेश <linux/atomic.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_pack.h>
#समावेश <rdma/ib_sa.h>
#समावेश <linux/sched.h>
/* स्थिरants */

क्रमागत ipoib_flush_level अणु
	IPOIB_FLUSH_LIGHT,
	IPOIB_FLUSH_NORMAL,
	IPOIB_FLUSH_HEAVY
पूर्ण;

क्रमागत अणु
	IPOIB_ENCAP_LEN		  = 4,
	IPOIB_PSEUDO_LEN	  = 20,
	IPOIB_HARD_LEN		  = IPOIB_ENCAP_LEN + IPOIB_PSEUDO_LEN,

	IPOIB_UD_HEAD_SIZE	  = IB_GRH_BYTES + IPOIB_ENCAP_LEN,
	IPOIB_UD_RX_SG		  = 2, /* max buffer needed क्रम 4K mtu */

	IPOIB_CM_MTU		  = 0x10000 - 0x10, /* padding to align header to 16 */
	IPOIB_CM_BUF_SIZE	  = IPOIB_CM_MTU  + IPOIB_ENCAP_LEN,
	IPOIB_CM_HEAD_SIZE	  = IPOIB_CM_BUF_SIZE % PAGE_SIZE,
	IPOIB_CM_RX_SG		  = ALIGN(IPOIB_CM_BUF_SIZE, PAGE_SIZE) / PAGE_SIZE,
	IPOIB_RX_RING_SIZE	  = 256,
	IPOIB_TX_RING_SIZE	  = 128,
	IPOIB_MAX_QUEUE_SIZE	  = 8192,
	IPOIB_MIN_QUEUE_SIZE	  = 2,
	IPOIB_CM_MAX_CONN_QP	  = 4096,

	IPOIB_NUM_WC		  = 4,

	IPOIB_MAX_PATH_REC_QUEUE  = 3,
	IPOIB_MAX_MCAST_QUEUE	  = 64,

	IPOIB_FLAG_OPER_UP	  = 0,
	IPOIB_FLAG_INITIALIZED	  = 1,
	IPOIB_FLAG_ADMIN_UP	  = 2,
	IPOIB_PKEY_ASSIGNED	  = 3,
	IPOIB_FLAG_SUBINTERFACE	  = 5,
	IPOIB_STOP_REAPER	  = 7,
	IPOIB_FLAG_ADMIN_CM	  = 9,
	IPOIB_FLAG_UMCAST	  = 10,
	IPOIB_NEIGH_TBL_FLUSH	  = 12,
	IPOIB_FLAG_DEV_ADDR_SET	  = 13,
	IPOIB_FLAG_DEV_ADDR_CTRL  = 14,

	IPOIB_MAX_BACKOFF_SECONDS = 16,

	IPOIB_MCAST_FLAG_FOUND	  = 0,	/* used in set_multicast_list */
	IPOIB_MCAST_FLAG_SENDONLY = 1,
	/*
	 * For IPOIB_MCAST_FLAG_BUSY
	 * When set, in flight join and mcast->mc is unreliable
	 * When clear and mcast->mc IS_ERR_OR_शून्य, need to restart or
	 *   haven't started yet
	 * When clear and mcast->mc is valid poपूर्णांकer, join was successful
	 */
	IPOIB_MCAST_FLAG_BUSY	  = 2,
	IPOIB_MCAST_FLAG_ATTACHED = 3,

	MAX_SEND_CQE		  = 64,
	IPOIB_CM_COPYBREAK	  = 256,

	IPOIB_NON_CHILD		  = 0,
	IPOIB_LEGACY_CHILD	  = 1,
	IPOIB_RTNL_CHILD	  = 2,
पूर्ण;

#घोषणा	IPOIB_OP_RECV   (1ul << 31)
#अगर_घोषित CONFIG_INFINIBAND_IPOIB_CM
#घोषणा	IPOIB_OP_CM     (1ul << 30)
#अन्यथा
#घोषणा	IPOIB_OP_CM     (0)
#पूर्ण_अगर

#घोषणा IPOIB_QPN_MASK ((__क्रमce u32) cpu_to_be32(0xFFFFFF))

/* काष्ठाs */

काष्ठा ipoib_header अणु
	__be16	proto;
	u16	reserved;
पूर्ण;

काष्ठा ipoib_pseuकरो_header अणु
	u8	hwaddr[INFINIBAND_ALEN];
पूर्ण;

अटल अंतरभूत व्योम skb_add_pseuकरो_hdr(काष्ठा sk_buff *skb)
अणु
	अक्षर *data = skb_push(skb, IPOIB_PSEUDO_LEN);

	/*
	 * only the ipoib header is present now, make room क्रम a dummy
	 * pseuकरो header and set skb field accordingly
	 */
	स_रखो(data, 0, IPOIB_PSEUDO_LEN);
	skb_reset_mac_header(skb);
	skb_pull(skb, IPOIB_HARD_LEN);
पूर्ण

अटल अंतरभूत काष्ठा ipoib_dev_priv *ipoib_priv(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा rdma_netdev *rn = netdev_priv(dev);

	वापस rn->clnt_priv;
पूर्ण

/* Used क्रम all multicast joins (broadcast, IPv4 mcast and IPv6 mcast) */
काष्ठा ipoib_mcast अणु
	काष्ठा ib_sa_mcmember_rec mcmember;
	काष्ठा ib_sa_multicast	 *mc;
	काष्ठा ipoib_ah		 *ah;

	काष्ठा rb_node    rb_node;
	काष्ठा list_head  list;

	अचिन्हित दीर्घ created;
	अचिन्हित दीर्घ backoff;
	अचिन्हित दीर्घ delay_until;

	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर logcount;

	काष्ठा list_head  neigh_list;

	काष्ठा sk_buff_head pkt_queue;

	काष्ठा net_device *dev;
	काष्ठा completion करोne;
पूर्ण;

काष्ठा ipoib_rx_buf अणु
	काष्ठा sk_buff *skb;
	u64		mapping[IPOIB_UD_RX_SG];
पूर्ण;

काष्ठा ipoib_tx_buf अणु
	काष्ठा sk_buff *skb;
	u64		mapping[MAX_SKB_FRAGS + 1];
पूर्ण;

काष्ठा ib_cm_id;

काष्ठा ipoib_cm_data अणु
	__be32 qpn; /* High byte MUST be ignored on receive */
	__be32 mtu;
पूर्ण;

/*
 * Quoting 10.3.1 Queue Pair and EE Context States:
 *
 * Note, क्रम QPs that are associated with an SRQ, the Consumer should take the
 * QP through the Error State beक्रमe invoking a Destroy QP or a Modअगरy QP to the
 * Reset State.  The Consumer may invoke the Destroy QP without first perक्रमming
 * a Modअगरy QP to the Error State and रुकोing क्रम the Affiliated Asynchronous
 * Last WQE Reached Event. However, अगर the Consumer करोes not रुको क्रम the
 * Affiliated Asynchronous Last WQE Reached Event, then WQE and Data Segment
 * leakage may occur. Thereक्रमe, it is good programming practice to tear करोwn a
 * QP that is associated with an SRQ by using the following process:
 *
 * - Put the QP in the Error State
 * - Wait क्रम the Affiliated Asynchronous Last WQE Reached Event;
 * - either:
 *       drain the CQ by invoking the Poll CQ verb and either रुको क्रम CQ
 *       to be empty or the number of Poll CQ operations has exceeded
 *       CQ capacity size;
 * - or
 *       post another WR that completes on the same CQ and रुको क्रम this
 *       WR to वापस as a WC;
 * - and then invoke a Destroy QP or Reset QP.
 *
 * We use the second option and रुको क्रम a completion on the
 * same CQ beक्रमe destroying QPs attached to our SRQ.
 */

क्रमागत ipoib_cm_state अणु
	IPOIB_CM_RX_LIVE,
	IPOIB_CM_RX_ERROR, /* Ignored by stale task */
	IPOIB_CM_RX_FLUSH  /* Last WQE Reached event observed */
पूर्ण;

काष्ठा ipoib_cm_rx अणु
	काष्ठा ib_cm_id	       *id;
	काष्ठा ib_qp	       *qp;
	काष्ठा ipoib_cm_rx_buf *rx_ring;
	काष्ठा list_head	list;
	काष्ठा net_device      *dev;
	अचिन्हित दीर्घ		jअगरfies;
	क्रमागत ipoib_cm_state	state;
	पूर्णांक			recv_count;
पूर्ण;

काष्ठा ipoib_cm_tx अणु
	काष्ठा ib_cm_id	    *id;
	काष्ठा ib_qp	    *qp;
	काष्ठा list_head     list;
	काष्ठा net_device   *dev;
	काष्ठा ipoib_neigh  *neigh;
	काष्ठा ipoib_tx_buf *tx_ring;
	अचिन्हित पूर्णांक	     tx_head;
	अचिन्हित पूर्णांक	     tx_tail;
	अचिन्हित दीर्घ	     flags;
	u32		     mtu;
	अचिन्हित पूर्णांक         max_send_sge;
पूर्ण;

काष्ठा ipoib_cm_rx_buf अणु
	काष्ठा sk_buff *skb;
	u64 mapping[IPOIB_CM_RX_SG];
पूर्ण;

काष्ठा ipoib_cm_dev_priv अणु
	काष्ठा ib_srq	       *srq;
	काष्ठा ipoib_cm_rx_buf *srq_ring;
	काष्ठा ib_cm_id	       *id;
	काष्ठा list_head	passive_ids;   /* state: LIVE */
	काष्ठा list_head	rx_error_list; /* state: ERROR */
	काष्ठा list_head	rx_flush_list; /* state: FLUSH, drain not started */
	काष्ठा list_head	rx_drain_list; /* state: FLUSH, drain started */
	काष्ठा list_head	rx_reap_list;  /* state: FLUSH, drain करोne */
	काष्ठा work_काष्ठा      start_task;
	काष्ठा work_काष्ठा      reap_task;
	काष्ठा work_काष्ठा      skb_task;
	काष्ठा work_काष्ठा      rx_reap_task;
	काष्ठा delayed_work     stale_task;
	काष्ठा sk_buff_head     skb_queue;
	काष्ठा list_head	start_list;
	काष्ठा list_head	reap_list;
	काष्ठा ib_wc		ibwc[IPOIB_NUM_WC];
	काष्ठा ib_sge		rx_sge[IPOIB_CM_RX_SG];
	काष्ठा ib_recv_wr       rx_wr;
	पूर्णांक			nonsrq_conn_qp;
	पूर्णांक			max_cm_mtu;
	पूर्णांक			num_frags;
पूर्ण;

काष्ठा ipoib_ethtool_st अणु
	u16     coalesce_usecs;
	u16     max_coalesced_frames;
पूर्ण;

काष्ठा ipoib_neigh_table;

काष्ठा ipoib_neigh_hash अणु
	काष्ठा ipoib_neigh_table       *ntbl;
	काष्ठा ipoib_neigh __rcu      **buckets;
	काष्ठा rcu_head			rcu;
	u32				mask;
	u32				size;
पूर्ण;

काष्ठा ipoib_neigh_table अणु
	काष्ठा ipoib_neigh_hash __rcu  *htbl;
	atomic_t			entries;
	काष्ठा completion		flushed;
	काष्ठा completion		deleted;
पूर्ण;

काष्ठा ipoib_qp_state_validate अणु
	काष्ठा work_काष्ठा work;
	काष्ठा ipoib_dev_priv   *priv;
पूर्ण;

/*
 * Device निजी locking: network stack tx_lock protects members used
 * in TX fast path, lock protects everything अन्यथा.  lock nests inside
 * of tx_lock (ie tx_lock must be acquired first अगर needed).
 */
काष्ठा ipoib_dev_priv अणु
	spinlock_t lock;

	काष्ठा net_device *dev;
	व्योम (*next_priv_deकाष्ठाor)(काष्ठा net_device *dev);

	काष्ठा napi_काष्ठा send_napi;
	काष्ठा napi_काष्ठा recv_napi;

	अचिन्हित दीर्घ flags;

	/*
	 * This protects access to the child_पूर्णांकfs list.
	 * To READ from child_पूर्णांकfs the RTNL or vlan_rwsem पढ़ो side must be
	 * held.  To WRITE RTNL and the vlan_rwsem ग_लिखो side must be held (in
	 * that order) This lock exists because we have a few contexts where
	 * we need the child_पूर्णांकfs, but करो not want to grab the RTNL.
	 */
	काष्ठा rw_semaphore vlan_rwsem;
	काष्ठा mutex mcast_mutex;

	काष्ठा rb_root  path_tree;
	काष्ठा list_head path_list;

	काष्ठा ipoib_neigh_table ntbl;

	काष्ठा ipoib_mcast *broadcast;
	काष्ठा list_head multicast_list;
	काष्ठा rb_root multicast_tree;

	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा delayed_work mcast_task;
	काष्ठा work_काष्ठा carrier_on_task;
	काष्ठा work_काष्ठा flush_light;
	काष्ठा work_काष्ठा flush_normal;
	काष्ठा work_काष्ठा flush_heavy;
	काष्ठा work_काष्ठा restart_task;
	काष्ठा delayed_work ah_reap_task;
	काष्ठा delayed_work neigh_reap_task;
	काष्ठा ib_device *ca;
	u8		  port;
	u16		  pkey;
	u16		  pkey_index;
	काष्ठा ib_pd	 *pd;
	काष्ठा ib_cq	 *recv_cq;
	काष्ठा ib_cq	 *send_cq;
	काष्ठा ib_qp	 *qp;
	u32		  qkey;

	जोड़ ib_gid local_gid;
	u32	     local_lid;

	अचिन्हित पूर्णांक admin_mtu;
	अचिन्हित पूर्णांक mcast_mtu;
	अचिन्हित पूर्णांक max_ib_mtu;

	काष्ठा ipoib_rx_buf *rx_ring;

	काष्ठा ipoib_tx_buf *tx_ring;
	/* cyclic ring variables क्रम managing tx_ring, क्रम UD only */
	अचिन्हित पूर्णांक	     tx_head;
	अचिन्हित पूर्णांक	     tx_tail;
	/* cyclic ring variables क्रम counting overall outstanding send WRs */
	अचिन्हित पूर्णांक	     global_tx_head;
	अचिन्हित पूर्णांक	     global_tx_tail;
	काष्ठा ib_sge	     tx_sge[MAX_SKB_FRAGS + 1];
	काष्ठा ib_ud_wr      tx_wr;
	काष्ठा ib_wc	     send_wc[MAX_SEND_CQE];

	काष्ठा ib_recv_wr    rx_wr;
	काष्ठा ib_sge	     rx_sge[IPOIB_UD_RX_SG];

	काष्ठा ib_wc ibwc[IPOIB_NUM_WC];

	काष्ठा list_head dead_ahs;

	काष्ठा ib_event_handler event_handler;

	काष्ठा net_device *parent;
	काष्ठा list_head child_पूर्णांकfs;
	काष्ठा list_head list;
	पूर्णांक    child_type;

#अगर_घोषित CONFIG_INFINIBAND_IPOIB_CM
	काष्ठा ipoib_cm_dev_priv cm;
#पूर्ण_अगर

#अगर_घोषित CONFIG_INFINIBAND_IPOIB_DEBUG
	काष्ठा list_head fs_list;
	काष्ठा dentry *mcg_dentry;
	काष्ठा dentry *path_dentry;
#पूर्ण_अगर
	u64	hca_caps;
	काष्ठा ipoib_ethtool_st ethtool;
	अचिन्हित पूर्णांक max_send_sge;
	स्थिर काष्ठा net_device_ops	*rn_ops;
पूर्ण;

काष्ठा ipoib_ah अणु
	काष्ठा net_device *dev;
	काष्ठा ib_ah	  *ah;
	काष्ठा list_head   list;
	काष्ठा kref	   ref;
	अचिन्हित पूर्णांक	   last_send;
	पूर्णांक  		   valid;
पूर्ण;

काष्ठा ipoib_path अणु
	काष्ठा net_device    *dev;
	काष्ठा sa_path_rec pathrec;
	काष्ठा ipoib_ah      *ah;
	काष्ठा sk_buff_head   queue;

	काष्ठा list_head      neigh_list;

	पूर्णांक		      query_id;
	काष्ठा ib_sa_query   *query;
	काष्ठा completion     करोne;

	काष्ठा rb_node	      rb_node;
	काष्ठा list_head      list;
पूर्ण;

काष्ठा ipoib_neigh अणु
	काष्ठा ipoib_ah    *ah;
#अगर_घोषित CONFIG_INFINIBAND_IPOIB_CM
	काष्ठा ipoib_cm_tx *cm;
#पूर्ण_अगर
	u8     daddr[INFINIBAND_ALEN];
	काष्ठा sk_buff_head queue;

	काष्ठा net_device *dev;

	काष्ठा list_head    list;
	काष्ठा ipoib_neigh __rcu *hnext;
	काष्ठा rcu_head     rcu;
	atomic_t	    refcnt;
	अचिन्हित दीर्घ       alive;
पूर्ण;

#घोषणा IPOIB_UD_MTU(ib_mtu)		(ib_mtu - IPOIB_ENCAP_LEN)
#घोषणा IPOIB_UD_BUF_SIZE(ib_mtu)	(ib_mtu + IB_GRH_BYTES)

व्योम ipoib_neigh_dtor(काष्ठा ipoib_neigh *neigh);
अटल अंतरभूत व्योम ipoib_neigh_put(काष्ठा ipoib_neigh *neigh)
अणु
	अगर (atomic_dec_and_test(&neigh->refcnt))
		ipoib_neigh_dtor(neigh);
पूर्ण
काष्ठा ipoib_neigh *ipoib_neigh_get(काष्ठा net_device *dev, u8 *daddr);
काष्ठा ipoib_neigh *ipoib_neigh_alloc(u8 *daddr,
				      काष्ठा net_device *dev);
व्योम ipoib_neigh_मुक्त(काष्ठा ipoib_neigh *neigh);
व्योम ipoib_del_neighs_by_gid(काष्ठा net_device *dev, u8 *gid);

बाह्य काष्ठा workqueue_काष्ठा *ipoib_workqueue;

/* functions */

पूर्णांक ipoib_rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
पूर्णांक ipoib_tx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
व्योम ipoib_ib_rx_completion(काष्ठा ib_cq *cq, व्योम *ctx_ptr);
व्योम ipoib_ib_tx_completion(काष्ठा ib_cq *cq, व्योम *ctx_ptr);

काष्ठा ipoib_ah *ipoib_create_ah(काष्ठा net_device *dev,
				 काष्ठा ib_pd *pd, काष्ठा rdma_ah_attr *attr);
व्योम ipoib_मुक्त_ah(काष्ठा kref *kref);
अटल अंतरभूत व्योम ipoib_put_ah(काष्ठा ipoib_ah *ah)
अणु
	kref_put(&ah->ref, ipoib_मुक्त_ah);
पूर्ण
पूर्णांक ipoib_खोलो(काष्ठा net_device *dev);
व्योम ipoib_पूर्णांकf_मुक्त(काष्ठा net_device *dev);
पूर्णांक ipoib_add_pkey_attr(काष्ठा net_device *dev);
पूर्णांक ipoib_add_umcast_attr(काष्ठा net_device *dev);

पूर्णांक ipoib_send(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
	       काष्ठा ib_ah *address, u32 dqpn);
व्योम ipoib_reap_ah(काष्ठा work_काष्ठा *work);

काष्ठा ipoib_path *__path_find(काष्ठा net_device *dev, व्योम *gid);
व्योम ipoib_mark_paths_invalid(काष्ठा net_device *dev);
व्योम ipoib_flush_paths(काष्ठा net_device *dev);
काष्ठा net_device *ipoib_पूर्णांकf_alloc(काष्ठा ib_device *hca, u32 port,
				    स्थिर अक्षर *क्रमmat);
पूर्णांक ipoib_पूर्णांकf_init(काष्ठा ib_device *hca, u32 port, स्थिर अक्षर *क्रमmat,
		    काष्ठा net_device *dev);
व्योम ipoib_ib_tx_समयr_func(काष्ठा समयr_list *t);
व्योम ipoib_ib_dev_flush_light(काष्ठा work_काष्ठा *work);
व्योम ipoib_ib_dev_flush_normal(काष्ठा work_काष्ठा *work);
व्योम ipoib_ib_dev_flush_heavy(काष्ठा work_काष्ठा *work);
व्योम ipoib_pkey_event(काष्ठा work_काष्ठा *work);
व्योम ipoib_ib_dev_cleanup(काष्ठा net_device *dev);

पूर्णांक ipoib_ib_dev_खोलो_शेष(काष्ठा net_device *dev);
पूर्णांक ipoib_ib_dev_खोलो(काष्ठा net_device *dev);
व्योम ipoib_ib_dev_stop(काष्ठा net_device *dev);
व्योम ipoib_ib_dev_up(काष्ठा net_device *dev);
व्योम ipoib_ib_dev_करोwn(काष्ठा net_device *dev);
पूर्णांक ipoib_ib_dev_stop_शेष(काष्ठा net_device *dev);
व्योम ipoib_pkey_dev_check_presence(काष्ठा net_device *dev);

व्योम ipoib_mcast_join_task(काष्ठा work_काष्ठा *work);
व्योम ipoib_mcast_carrier_on_task(काष्ठा work_काष्ठा *work);
व्योम ipoib_mcast_send(काष्ठा net_device *dev, u8 *daddr, काष्ठा sk_buff *skb);

व्योम ipoib_mcast_restart_task(काष्ठा work_काष्ठा *work);
व्योम ipoib_mcast_start_thपढ़ो(काष्ठा net_device *dev);
व्योम ipoib_mcast_stop_thपढ़ो(काष्ठा net_device *dev);

व्योम ipoib_mcast_dev_करोwn(काष्ठा net_device *dev);
व्योम ipoib_mcast_dev_flush(काष्ठा net_device *dev);

पूर्णांक ipoib_dma_map_tx(काष्ठा ib_device *ca, काष्ठा ipoib_tx_buf *tx_req);
व्योम ipoib_dma_unmap_tx(काष्ठा ipoib_dev_priv *priv,
			काष्ठा ipoib_tx_buf *tx_req);

काष्ठा rtnl_link_ops *ipoib_get_link_ops(व्योम);

अटल अंतरभूत व्योम ipoib_build_sge(काष्ठा ipoib_dev_priv *priv,
				   काष्ठा ipoib_tx_buf *tx_req)
अणु
	पूर्णांक i, off;
	काष्ठा sk_buff *skb = tx_req->skb;
	skb_frag_t *frags = skb_shinfo(skb)->frags;
	पूर्णांक nr_frags = skb_shinfo(skb)->nr_frags;
	u64 *mapping = tx_req->mapping;

	अगर (skb_headlen(skb)) अणु
		priv->tx_sge[0].addr         = mapping[0];
		priv->tx_sge[0].length       = skb_headlen(skb);
		off = 1;
	पूर्ण अन्यथा
		off = 0;

	क्रम (i = 0; i < nr_frags; ++i) अणु
		priv->tx_sge[i + off].addr = mapping[i + off];
		priv->tx_sge[i + off].length = skb_frag_size(&frags[i]);
	पूर्ण
	priv->tx_wr.wr.num_sge	     = nr_frags + off;
पूर्ण

#अगर_घोषित CONFIG_INFINIBAND_IPOIB_DEBUG
काष्ठा ipoib_mcast_iter *ipoib_mcast_iter_init(काष्ठा net_device *dev);
पूर्णांक ipoib_mcast_iter_next(काष्ठा ipoib_mcast_iter *iter);
व्योम ipoib_mcast_iter_पढ़ो(काष्ठा ipoib_mcast_iter *iter,
				  जोड़ ib_gid *gid,
				  अचिन्हित दीर्घ *created,
				  अचिन्हित पूर्णांक *queuelen,
				  अचिन्हित पूर्णांक *complete,
				  अचिन्हित पूर्णांक *send_only);

काष्ठा ipoib_path_iter *ipoib_path_iter_init(काष्ठा net_device *dev);
पूर्णांक ipoib_path_iter_next(काष्ठा ipoib_path_iter *iter);
व्योम ipoib_path_iter_पढ़ो(काष्ठा ipoib_path_iter *iter,
			  काष्ठा ipoib_path *path);
#पूर्ण_अगर

पूर्णांक ipoib_mcast_attach(काष्ठा net_device *dev, काष्ठा ib_device *hca,
		       जोड़ ib_gid *mgid, u16 mlid, पूर्णांक set_qkey, u32 qkey);
पूर्णांक ipoib_mcast_detach(काष्ठा net_device *dev, काष्ठा ib_device *hca,
		       जोड़ ib_gid *mgid, u16 mlid);
व्योम ipoib_mcast_हटाओ_list(काष्ठा list_head *हटाओ_list);
व्योम ipoib_check_and_add_mcast_senकरोnly(काष्ठा ipoib_dev_priv *priv, u8 *mgid,
				काष्ठा list_head *हटाओ_list);

पूर्णांक ipoib_init_qp(काष्ठा net_device *dev);
पूर्णांक ipoib_transport_dev_init(काष्ठा net_device *dev, काष्ठा ib_device *ca);
व्योम ipoib_transport_dev_cleanup(काष्ठा net_device *dev);

व्योम ipoib_event(काष्ठा ib_event_handler *handler,
		 काष्ठा ib_event *record);

पूर्णांक ipoib_vlan_add(काष्ठा net_device *pdev, अचिन्हित लघु pkey);
पूर्णांक ipoib_vlan_delete(काष्ठा net_device *pdev, अचिन्हित लघु pkey);

पूर्णांक __ipoib_vlan_add(काष्ठा ipoib_dev_priv *ppriv, काष्ठा ipoib_dev_priv *priv,
		     u16 pkey, पूर्णांक child_type);

पूर्णांक  __init ipoib_netlink_init(व्योम);
व्योम __निकास ipoib_netlink_fini(व्योम);

व्योम ipoib_set_umcast(काष्ठा net_device *ndev, पूर्णांक umcast_val);
पूर्णांक  ipoib_set_mode(काष्ठा net_device *dev, स्थिर अक्षर *buf);

व्योम ipoib_setup_common(काष्ठा net_device *dev);

व्योम ipoib_pkey_खोलो(काष्ठा ipoib_dev_priv *priv);
व्योम ipoib_drain_cq(काष्ठा net_device *dev);

व्योम ipoib_set_ethtool_ops(काष्ठा net_device *dev);

#घोषणा IPOIB_FLAGS_RC		0x80
#घोषणा IPOIB_FLAGS_UC		0x40

/* We करोn't support UC connections at the moment */
#घोषणा IPOIB_CM_SUPPORTED(ha)   (ha[0] & (IPOIB_FLAGS_RC))

#अगर_घोषित CONFIG_INFINIBAND_IPOIB_CM

बाह्य पूर्णांक ipoib_max_conn_qp;

अटल अंतरभूत पूर्णांक ipoib_cm_admin_enabled(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	वापस IPOIB_CM_SUPPORTED(dev->dev_addr) &&
		test_bit(IPOIB_FLAG_ADMIN_CM, &priv->flags);
पूर्ण

अटल अंतरभूत पूर्णांक ipoib_cm_enabled(काष्ठा net_device *dev, u8 *hwaddr)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	वापस IPOIB_CM_SUPPORTED(hwaddr) &&
		test_bit(IPOIB_FLAG_ADMIN_CM, &priv->flags);
पूर्ण

अटल अंतरभूत पूर्णांक ipoib_cm_up(काष्ठा ipoib_neigh *neigh)

अणु
	वापस test_bit(IPOIB_FLAG_OPER_UP, &neigh->cm->flags);
पूर्ण

अटल अंतरभूत काष्ठा ipoib_cm_tx *ipoib_cm_get(काष्ठा ipoib_neigh *neigh)
अणु
	वापस neigh->cm;
पूर्ण

अटल अंतरभूत व्योम ipoib_cm_set(काष्ठा ipoib_neigh *neigh, काष्ठा ipoib_cm_tx *tx)
अणु
	neigh->cm = tx;
पूर्ण

अटल अंतरभूत पूर्णांक ipoib_cm_has_srq(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	वापस !!priv->cm.srq;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ipoib_cm_max_mtu(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	वापस priv->cm.max_cm_mtu;
पूर्ण

व्योम ipoib_cm_send(काष्ठा net_device *dev, काष्ठा sk_buff *skb, काष्ठा ipoib_cm_tx *tx);
पूर्णांक ipoib_cm_dev_खोलो(काष्ठा net_device *dev);
व्योम ipoib_cm_dev_stop(काष्ठा net_device *dev);
पूर्णांक ipoib_cm_dev_init(काष्ठा net_device *dev);
पूर्णांक ipoib_cm_add_mode_attr(काष्ठा net_device *dev);
व्योम ipoib_cm_dev_cleanup(काष्ठा net_device *dev);
काष्ठा ipoib_cm_tx *ipoib_cm_create_tx(काष्ठा net_device *dev, काष्ठा ipoib_path *path,
				    काष्ठा ipoib_neigh *neigh);
व्योम ipoib_cm_destroy_tx(काष्ठा ipoib_cm_tx *tx);
व्योम ipoib_cm_skb_too_दीर्घ(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			   अचिन्हित पूर्णांक mtu);
व्योम ipoib_cm_handle_rx_wc(काष्ठा net_device *dev, काष्ठा ib_wc *wc);
व्योम ipoib_cm_handle_tx_wc(काष्ठा net_device *dev, काष्ठा ib_wc *wc);
#अन्यथा

#घोषणा ipoib_max_conn_qp 0

अटल अंतरभूत पूर्णांक ipoib_cm_admin_enabled(काष्ठा net_device *dev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक ipoib_cm_enabled(काष्ठा net_device *dev, u8 *hwaddr)

अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ipoib_cm_up(काष्ठा ipoib_neigh *neigh)

अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा ipoib_cm_tx *ipoib_cm_get(काष्ठा ipoib_neigh *neigh)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम ipoib_cm_set(काष्ठा ipoib_neigh *neigh, काष्ठा ipoib_cm_tx *tx)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ipoib_cm_has_srq(काष्ठा net_device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ipoib_cm_max_mtu(काष्ठा net_device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
व्योम ipoib_cm_send(काष्ठा net_device *dev, काष्ठा sk_buff *skb, काष्ठा ipoib_cm_tx *tx)
अणु
	वापस;
पूर्ण

अटल अंतरभूत
पूर्णांक ipoib_cm_dev_खोलो(काष्ठा net_device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
व्योम ipoib_cm_dev_stop(काष्ठा net_device *dev)
अणु
	वापस;
पूर्ण

अटल अंतरभूत
पूर्णांक ipoib_cm_dev_init(काष्ठा net_device *dev)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत
व्योम ipoib_cm_dev_cleanup(काष्ठा net_device *dev)
अणु
	वापस;
पूर्ण

अटल अंतरभूत
काष्ठा ipoib_cm_tx *ipoib_cm_create_tx(काष्ठा net_device *dev, काष्ठा ipoib_path *path,
				    काष्ठा ipoib_neigh *neigh)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत
व्योम ipoib_cm_destroy_tx(काष्ठा ipoib_cm_tx *tx)
अणु
	वापस;
पूर्ण

अटल अंतरभूत
पूर्णांक ipoib_cm_add_mode_attr(काष्ठा net_device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ipoib_cm_skb_too_दीर्घ(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
					 अचिन्हित पूर्णांक mtu)
अणु
	dev_kमुक्त_skb_any(skb);
पूर्ण

अटल अंतरभूत व्योम ipoib_cm_handle_rx_wc(काष्ठा net_device *dev, काष्ठा ib_wc *wc)
अणु
पूर्ण

अटल अंतरभूत व्योम ipoib_cm_handle_tx_wc(काष्ठा net_device *dev, काष्ठा ib_wc *wc)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_INFINIBAND_IPOIB_DEBUG
व्योम ipoib_create_debug_files(काष्ठा net_device *dev);
व्योम ipoib_delete_debug_files(काष्ठा net_device *dev);
व्योम ipoib_रेजिस्टर_debugfs(व्योम);
व्योम ipoib_unरेजिस्टर_debugfs(व्योम);
#अन्यथा
अटल अंतरभूत व्योम ipoib_create_debug_files(काष्ठा net_device *dev) अणु पूर्ण
अटल अंतरभूत व्योम ipoib_delete_debug_files(काष्ठा net_device *dev) अणु पूर्ण
अटल अंतरभूत व्योम ipoib_रेजिस्टर_debugfs(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम ipoib_unरेजिस्टर_debugfs(व्योम) अणु पूर्ण
#पूर्ण_अगर

#घोषणा ipoib_prपूर्णांकk(level, priv, क्रमmat, arg...)	\
	prपूर्णांकk(level "%s: " क्रमmat, ((काष्ठा ipoib_dev_priv *) priv)->dev->name , ## arg)
#घोषणा ipoib_warn(priv, क्रमmat, arg...)		\
करो अणु							\
	अटल DEFINE_RATELIMIT_STATE(_rs,		\
		10 * HZ /*10 seconds */,		\
		100);		\
	अगर (__ratelimit(&_rs))				\
		ipoib_prपूर्णांकk(KERN_WARNING, priv, क्रमmat , ## arg);\
पूर्ण जबतक (0)

बाह्य पूर्णांक ipoib_sendq_size;
बाह्य पूर्णांक ipoib_recvq_size;

बाह्य काष्ठा ib_sa_client ipoib_sa_client;

#अगर_घोषित CONFIG_INFINIBAND_IPOIB_DEBUG
बाह्य पूर्णांक ipoib_debug_level;

#घोषणा ipoib_dbg(priv, क्रमmat, arg...)			\
	करो अणु						\
		अगर (ipoib_debug_level > 0)			\
			ipoib_prपूर्णांकk(KERN_DEBUG, priv, क्रमmat , ## arg); \
	पूर्ण जबतक (0)
#घोषणा ipoib_dbg_mcast(priv, क्रमmat, arg...)		\
	करो अणु						\
		अगर (mcast_debug_level > 0)		\
			ipoib_prपूर्णांकk(KERN_DEBUG, priv, क्रमmat , ## arg); \
	पूर्ण जबतक (0)
#अन्यथा /* CONFIG_INFINIBAND_IPOIB_DEBUG */
#घोषणा ipoib_dbg(priv, क्रमmat, arg...)			\
	करो अणु (व्योम) (priv); पूर्ण जबतक (0)
#घोषणा ipoib_dbg_mcast(priv, क्रमmat, arg...)		\
	करो अणु (व्योम) (priv); पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_INFINIBAND_IPOIB_DEBUG */

#अगर_घोषित CONFIG_INFINIBAND_IPOIB_DEBUG_DATA
#घोषणा ipoib_dbg_data(priv, क्रमmat, arg...)		\
	करो अणु						\
		अगर (data_debug_level > 0)		\
			ipoib_prपूर्णांकk(KERN_DEBUG, priv, क्रमmat , ## arg); \
	पूर्ण जबतक (0)
#अन्यथा /* CONFIG_INFINIBAND_IPOIB_DEBUG_DATA */
#घोषणा ipoib_dbg_data(priv, क्रमmat, arg...)		\
	करो अणु (व्योम) (priv); पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_INFINIBAND_IPOIB_DEBUG_DATA */

#घोषणा IPOIB_QPN(ha) (be32_to_cpup((__be32 *) ha) & 0xffffff)

#पूर्ण_अगर /* _IPOIB_H */
