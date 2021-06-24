<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_SCHED_GENERIC_H
#घोषणा __NET_SCHED_GENERIC_H

#समावेश <linux/netdevice.h>
#समावेश <linux/types.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/pkt_sched.h>
#समावेश <linux/pkt_cls.h>
#समावेश <linux/percpu.h>
#समावेश <linux/dynamic_queue_सीमा.स>
#समावेश <linux/list.h>
#समावेश <linux/refcount.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/atomic.h>
#समावेश <linux/hashtable.h>
#समावेश <net/gen_stats.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/flow_offload.h>

काष्ठा Qdisc_ops;
काष्ठा qdisc_walker;
काष्ठा tcf_walker;
काष्ठा module;
काष्ठा bpf_flow_keys;

काष्ठा qdisc_rate_table अणु
	काष्ठा tc_ratespec rate;
	u32		data[256];
	काष्ठा qdisc_rate_table *next;
	पूर्णांक		refcnt;
पूर्ण;

क्रमागत qdisc_state_t अणु
	__QDISC_STATE_SCHED,
	__QDISC_STATE_DEACTIVATED,
	__QDISC_STATE_MISSED,
पूर्ण;

काष्ठा qdisc_माप_प्रकारable अणु
	काष्ठा rcu_head		rcu;
	काष्ठा list_head	list;
	काष्ठा tc_sizespec	szopts;
	पूर्णांक			refcnt;
	u16			data[];
पूर्ण;

/* similar to sk_buff_head, but skb->prev poपूर्णांकer is undefined. */
काष्ठा qdisc_skb_head अणु
	काष्ठा sk_buff	*head;
	काष्ठा sk_buff	*tail;
	__u32		qlen;
	spinlock_t	lock;
पूर्ण;

काष्ठा Qdisc अणु
	पूर्णांक 			(*enqueue)(काष्ठा sk_buff *skb,
					   काष्ठा Qdisc *sch,
					   काष्ठा sk_buff **to_मुक्त);
	काष्ठा sk_buff *	(*dequeue)(काष्ठा Qdisc *sch);
	अचिन्हित पूर्णांक		flags;
#घोषणा TCQ_F_BUILTIN		1
#घोषणा TCQ_F_INGRESS		2
#घोषणा TCQ_F_CAN_BYPASS	4
#घोषणा TCQ_F_MQROOT		8
#घोषणा TCQ_F_ONETXQUEUE	0x10 /* dequeue_skb() can assume all skbs are क्रम
				      * q->dev_queue : It can test
				      * netअगर_xmit_frozen_or_stopped() beक्रमe
				      * dequeueing next packet.
				      * Its true क्रम MQ/MQPRIO slaves, or non
				      * multiqueue device.
				      */
#घोषणा TCQ_F_WARN_NONWC	(1 << 16)
#घोषणा TCQ_F_CPUSTATS		0x20 /* run using percpu statistics */
#घोषणा TCQ_F_NOPARENT		0x40 /* root of its hierarchy :
				      * qdisc_tree_decrease_qlen() should stop.
				      */
#घोषणा TCQ_F_INVISIBLE		0x80 /* invisible by शेष in dump */
#घोषणा TCQ_F_NOLOCK		0x100 /* qdisc करोes not require locking */
#घोषणा TCQ_F_OFFLOADED		0x200 /* qdisc is offloaded to HW */
	u32			limit;
	स्थिर काष्ठा Qdisc_ops	*ops;
	काष्ठा qdisc_माप_प्रकारable	__rcu *stab;
	काष्ठा hlist_node       hash;
	u32			handle;
	u32			parent;

	काष्ठा netdev_queue	*dev_queue;

	काष्ठा net_rate_estimator __rcu *rate_est;
	काष्ठा gnet_stats_basic_cpu __percpu *cpu_bstats;
	काष्ठा gnet_stats_queue	__percpu *cpu_qstats;
	पूर्णांक			pad;
	refcount_t		refcnt;

	/*
	 * For perक्रमmance sake on SMP, we put highly modअगरied fields at the end
	 */
	काष्ठा sk_buff_head	gso_skb ____cacheline_aligned_in_smp;
	काष्ठा qdisc_skb_head	q;
	काष्ठा gnet_stats_basic_packed bstats;
	seqcount_t		running;
	काष्ठा gnet_stats_queue	qstats;
	अचिन्हित दीर्घ		state;
	काष्ठा Qdisc            *next_sched;
	काष्ठा sk_buff_head	skb_bad_txq;

	spinlock_t		busylock ____cacheline_aligned_in_smp;
	spinlock_t		seqlock;

	/* क्रम NOLOCK qdisc, true अगर there are no enqueued skbs */
	bool			empty;
	काष्ठा rcu_head		rcu;

	/* निजी data */
	दीर्घ privdata[] ____cacheline_aligned;
पूर्ण;

अटल अंतरभूत व्योम qdisc_refcount_inc(काष्ठा Qdisc *qdisc)
अणु
	अगर (qdisc->flags & TCQ_F_BUILTIN)
		वापस;
	refcount_inc(&qdisc->refcnt);
पूर्ण

/* Intended to be used by unlocked users, when concurrent qdisc release is
 * possible.
 */

अटल अंतरभूत काष्ठा Qdisc *qdisc_refcount_inc_nz(काष्ठा Qdisc *qdisc)
अणु
	अगर (qdisc->flags & TCQ_F_BUILTIN)
		वापस qdisc;
	अगर (refcount_inc_not_zero(&qdisc->refcnt))
		वापस qdisc;
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool qdisc_is_running(काष्ठा Qdisc *qdisc)
अणु
	अगर (qdisc->flags & TCQ_F_NOLOCK)
		वापस spin_is_locked(&qdisc->seqlock);
	वापस (raw_पढ़ो_seqcount(&qdisc->running) & 1) ? true : false;
पूर्ण

अटल अंतरभूत bool qdisc_is_percpu_stats(स्थिर काष्ठा Qdisc *q)
अणु
	वापस q->flags & TCQ_F_CPUSTATS;
पूर्ण

अटल अंतरभूत bool qdisc_is_empty(स्थिर काष्ठा Qdisc *qdisc)
अणु
	अगर (qdisc_is_percpu_stats(qdisc))
		वापस READ_ONCE(qdisc->empty);
	वापस !READ_ONCE(qdisc->q.qlen);
पूर्ण

अटल अंतरभूत bool qdisc_run_begin(काष्ठा Qdisc *qdisc)
अणु
	अगर (qdisc->flags & TCQ_F_NOLOCK) अणु
		अगर (spin_trylock(&qdisc->seqlock))
			जाओ nolock_empty;

		/* If the MISSED flag is set, it means other thपढ़ो has
		 * set the MISSED flag beक्रमe second spin_trylock(), so
		 * we can वापस false here to aव्योम multi cpus करोing
		 * the set_bit() and second spin_trylock() concurrently.
		 */
		अगर (test_bit(__QDISC_STATE_MISSED, &qdisc->state))
			वापस false;

		/* Set the MISSED flag beक्रमe the second spin_trylock(),
		 * अगर the second spin_trylock() वापस false, it means
		 * other cpu holding the lock will करो dequeuing क्रम us
		 * or it will see the MISSED flag set after releasing
		 * lock and reschedule the net_tx_action() to करो the
		 * dequeuing.
		 */
		set_bit(__QDISC_STATE_MISSED, &qdisc->state);

		/* Retry again in हाल other CPU may not see the new flag
		 * after it releases the lock at the end of qdisc_run_end().
		 */
		अगर (!spin_trylock(&qdisc->seqlock))
			वापस false;

nolock_empty:
		WRITE_ONCE(qdisc->empty, false);
	पूर्ण अन्यथा अगर (qdisc_is_running(qdisc)) अणु
		वापस false;
	पूर्ण
	/* Variant of ग_लिखो_seqcount_begin() telling lockdep a trylock
	 * was attempted.
	 */
	raw_ग_लिखो_seqcount_begin(&qdisc->running);
	seqcount_acquire(&qdisc->running.dep_map, 0, 1, _RET_IP_);
	वापस true;
पूर्ण

अटल अंतरभूत व्योम qdisc_run_end(काष्ठा Qdisc *qdisc)
अणु
	ग_लिखो_seqcount_end(&qdisc->running);
	अगर (qdisc->flags & TCQ_F_NOLOCK) अणु
		spin_unlock(&qdisc->seqlock);

		अगर (unlikely(test_bit(__QDISC_STATE_MISSED,
				      &qdisc->state))) अणु
			clear_bit(__QDISC_STATE_MISSED, &qdisc->state);
			__netअगर_schedule(qdisc);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत bool qdisc_may_bulk(स्थिर काष्ठा Qdisc *qdisc)
अणु
	वापस qdisc->flags & TCQ_F_ONETXQUEUE;
पूर्ण

अटल अंतरभूत पूर्णांक qdisc_avail_bulklimit(स्थिर काष्ठा netdev_queue *txq)
अणु
#अगर_घोषित CONFIG_BQL
	/* Non-BQL migrated drivers will वापस 0, too. */
	वापस dql_avail(&txq->dql);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

काष्ठा Qdisc_class_ops अणु
	अचिन्हित पूर्णांक		flags;
	/* Child qdisc manipulation */
	काष्ठा netdev_queue *	(*select_queue)(काष्ठा Qdisc *, काष्ठा tcmsg *);
	पूर्णांक			(*graft)(काष्ठा Qdisc *, अचिन्हित दीर्घ cl,
					काष्ठा Qdisc *, काष्ठा Qdisc **,
					काष्ठा netlink_ext_ack *extack);
	काष्ठा Qdisc *		(*leaf)(काष्ठा Qdisc *, अचिन्हित दीर्घ cl);
	व्योम			(*qlen_notअगरy)(काष्ठा Qdisc *, अचिन्हित दीर्घ);

	/* Class manipulation routines */
	अचिन्हित दीर्घ		(*find)(काष्ठा Qdisc *, u32 classid);
	पूर्णांक			(*change)(काष्ठा Qdisc *, u32, u32,
					काष्ठा nlattr **, अचिन्हित दीर्घ *,
					काष्ठा netlink_ext_ack *);
	पूर्णांक			(*delete)(काष्ठा Qdisc *, अचिन्हित दीर्घ,
					  काष्ठा netlink_ext_ack *);
	व्योम			(*walk)(काष्ठा Qdisc *, काष्ठा qdisc_walker * arg);

	/* Filter manipulation */
	काष्ठा tcf_block *	(*tcf_block)(काष्ठा Qdisc *sch,
					     अचिन्हित दीर्घ arg,
					     काष्ठा netlink_ext_ack *extack);
	अचिन्हित दीर्घ		(*bind_tcf)(काष्ठा Qdisc *, अचिन्हित दीर्घ,
					u32 classid);
	व्योम			(*unbind_tcf)(काष्ठा Qdisc *, अचिन्हित दीर्घ);

	/* rtnetlink specअगरic */
	पूर्णांक			(*dump)(काष्ठा Qdisc *, अचिन्हित दीर्घ,
					काष्ठा sk_buff *skb, काष्ठा tcmsg*);
	पूर्णांक			(*dump_stats)(काष्ठा Qdisc *, अचिन्हित दीर्घ,
					काष्ठा gnet_dump *);
पूर्ण;

/* Qdisc_class_ops flag values */

/* Implements API that करोesn't require rtnl lock */
क्रमागत qdisc_class_ops_flags अणु
	QDISC_CLASS_OPS_DOIT_UNLOCKED = 1,
पूर्ण;

काष्ठा Qdisc_ops अणु
	काष्ठा Qdisc_ops	*next;
	स्थिर काष्ठा Qdisc_class_ops	*cl_ops;
	अक्षर			id[IFNAMSIZ];
	पूर्णांक			priv_size;
	अचिन्हित पूर्णांक		अटल_flags;

	पूर्णांक 			(*enqueue)(काष्ठा sk_buff *skb,
					   काष्ठा Qdisc *sch,
					   काष्ठा sk_buff **to_मुक्त);
	काष्ठा sk_buff *	(*dequeue)(काष्ठा Qdisc *);
	काष्ठा sk_buff *	(*peek)(काष्ठा Qdisc *);

	पूर्णांक			(*init)(काष्ठा Qdisc *sch, काष्ठा nlattr *arg,
					काष्ठा netlink_ext_ack *extack);
	व्योम			(*reset)(काष्ठा Qdisc *);
	व्योम			(*destroy)(काष्ठा Qdisc *);
	पूर्णांक			(*change)(काष्ठा Qdisc *sch,
					  काष्ठा nlattr *arg,
					  काष्ठा netlink_ext_ack *extack);
	व्योम			(*attach)(काष्ठा Qdisc *sch);
	पूर्णांक			(*change_tx_queue_len)(काष्ठा Qdisc *, अचिन्हित पूर्णांक);

	पूर्णांक			(*dump)(काष्ठा Qdisc *, काष्ठा sk_buff *);
	पूर्णांक			(*dump_stats)(काष्ठा Qdisc *, काष्ठा gnet_dump *);

	व्योम			(*ingress_block_set)(काष्ठा Qdisc *sch,
						     u32 block_index);
	व्योम			(*egress_block_set)(काष्ठा Qdisc *sch,
						    u32 block_index);
	u32			(*ingress_block_get)(काष्ठा Qdisc *sch);
	u32			(*egress_block_get)(काष्ठा Qdisc *sch);

	काष्ठा module		*owner;
पूर्ण;


काष्ठा tcf_result अणु
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ	class;
			u32		classid;
		पूर्ण;
		स्थिर काष्ठा tcf_proto *जाओ_tp;

		/* used in the skb_tc_reinsert function */
		काष्ठा अणु
			bool		ingress;
			काष्ठा gnet_stats_queue *qstats;
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा tcf_chain;

काष्ठा tcf_proto_ops अणु
	काष्ठा list_head	head;
	अक्षर			kind[IFNAMSIZ];

	पूर्णांक			(*classअगरy)(काष्ठा sk_buff *,
					    स्थिर काष्ठा tcf_proto *,
					    काष्ठा tcf_result *);
	पूर्णांक			(*init)(काष्ठा tcf_proto*);
	व्योम			(*destroy)(काष्ठा tcf_proto *tp, bool rtnl_held,
					   काष्ठा netlink_ext_ack *extack);

	व्योम*			(*get)(काष्ठा tcf_proto*, u32 handle);
	व्योम			(*put)(काष्ठा tcf_proto *tp, व्योम *f);
	पूर्णांक			(*change)(काष्ठा net *net, काष्ठा sk_buff *,
					काष्ठा tcf_proto*, अचिन्हित दीर्घ,
					u32 handle, काष्ठा nlattr **,
					व्योम **, bool, bool,
					काष्ठा netlink_ext_ack *);
	पूर्णांक			(*delete)(काष्ठा tcf_proto *tp, व्योम *arg,
					  bool *last, bool rtnl_held,
					  काष्ठा netlink_ext_ack *);
	bool			(*delete_empty)(काष्ठा tcf_proto *tp);
	व्योम			(*walk)(काष्ठा tcf_proto *tp,
					काष्ठा tcf_walker *arg, bool rtnl_held);
	पूर्णांक			(*reoffload)(काष्ठा tcf_proto *tp, bool add,
					     flow_setup_cb_t *cb, व्योम *cb_priv,
					     काष्ठा netlink_ext_ack *extack);
	व्योम			(*hw_add)(काष्ठा tcf_proto *tp,
					  व्योम *type_data);
	व्योम			(*hw_del)(काष्ठा tcf_proto *tp,
					  व्योम *type_data);
	व्योम			(*bind_class)(व्योम *, u32, अचिन्हित दीर्घ,
					      व्योम *, अचिन्हित दीर्घ);
	व्योम *			(*पंचांगplt_create)(काष्ठा net *net,
						काष्ठा tcf_chain *chain,
						काष्ठा nlattr **tca,
						काष्ठा netlink_ext_ack *extack);
	व्योम			(*पंचांगplt_destroy)(व्योम *पंचांगplt_priv);

	/* rtnetlink specअगरic */
	पूर्णांक			(*dump)(काष्ठा net*, काष्ठा tcf_proto*, व्योम *,
					काष्ठा sk_buff *skb, काष्ठा tcmsg*,
					bool);
	पूर्णांक			(*terse_dump)(काष्ठा net *net,
					      काष्ठा tcf_proto *tp, व्योम *fh,
					      काष्ठा sk_buff *skb,
					      काष्ठा tcmsg *t, bool rtnl_held);
	पूर्णांक			(*पंचांगplt_dump)(काष्ठा sk_buff *skb,
					      काष्ठा net *net,
					      व्योम *पंचांगplt_priv);

	काष्ठा module		*owner;
	पूर्णांक			flags;
पूर्ण;

/* Classअगरiers setting TCF_PROTO_OPS_DOIT_UNLOCKED in tcf_proto_ops->flags
 * are expected to implement tcf_proto_ops->delete_empty(), otherwise race
 * conditions can occur when filters are inserted/deleted simultaneously.
 */
क्रमागत tcf_proto_ops_flags अणु
	TCF_PROTO_OPS_DOIT_UNLOCKED = 1,
पूर्ण;

काष्ठा tcf_proto अणु
	/* Fast access part */
	काष्ठा tcf_proto __rcu	*next;
	व्योम __rcu		*root;

	/* called under RCU BH lock*/
	पूर्णांक			(*classअगरy)(काष्ठा sk_buff *,
					    स्थिर काष्ठा tcf_proto *,
					    काष्ठा tcf_result *);
	__be16			protocol;

	/* All the rest */
	u32			prio;
	व्योम			*data;
	स्थिर काष्ठा tcf_proto_ops	*ops;
	काष्ठा tcf_chain	*chain;
	/* Lock protects tcf_proto shared state and can be used by unlocked
	 * classअगरiers to protect their निजी data.
	 */
	spinlock_t		lock;
	bool			deleting;
	refcount_t		refcnt;
	काष्ठा rcu_head		rcu;
	काष्ठा hlist_node	destroy_ht_node;
पूर्ण;

काष्ठा qdisc_skb_cb अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक		pkt_len;
		u16			slave_dev_queue_mapping;
		u16			tc_classid;
	पूर्ण;
#घोषणा QDISC_CB_PRIV_LEN 20
	अचिन्हित अक्षर		data[QDISC_CB_PRIV_LEN];
	u16			mru;
	bool			post_ct;
पूर्ण;

प्रकार व्योम tcf_chain_head_change_t(काष्ठा tcf_proto *tp_head, व्योम *priv);

काष्ठा tcf_chain अणु
	/* Protects filter_chain. */
	काष्ठा mutex filter_chain_lock;
	काष्ठा tcf_proto __rcu *filter_chain;
	काष्ठा list_head list;
	काष्ठा tcf_block *block;
	u32 index; /* chain index */
	अचिन्हित पूर्णांक refcnt;
	अचिन्हित पूर्णांक action_refcnt;
	bool explicitly_created;
	bool flushing;
	स्थिर काष्ठा tcf_proto_ops *पंचांगplt_ops;
	व्योम *पंचांगplt_priv;
	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा tcf_block अणु
	/* Lock protects tcf_block and lअगरeसमय-management data of chains
	 * attached to the block (refcnt, action_refcnt, explicitly_created).
	 */
	काष्ठा mutex lock;
	काष्ठा list_head chain_list;
	u32 index; /* block index क्रम shared blocks */
	u32 classid; /* which class this block beदीर्घs to */
	refcount_t refcnt;
	काष्ठा net *net;
	काष्ठा Qdisc *q;
	काष्ठा rw_semaphore cb_lock; /* protects cb_list and offload counters */
	काष्ठा flow_block flow_block;
	काष्ठा list_head owner_list;
	bool keep_dst;
	atomic_t offloadcnt; /* Number of oddloaded filters */
	अचिन्हित पूर्णांक nooffloaddevcnt; /* Number of devs unable to करो offload */
	अचिन्हित पूर्णांक lockeddevcnt; /* Number of devs that require rtnl lock. */
	काष्ठा अणु
		काष्ठा tcf_chain *chain;
		काष्ठा list_head filter_chain_list;
	पूर्ण chain0;
	काष्ठा rcu_head rcu;
	DECLARE_HASHTABLE(proto_destroy_ht, 7);
	काष्ठा mutex proto_destroy_lock; /* Lock क्रम proto_destroy hashtable. */
पूर्ण;

अटल अंतरभूत bool lockdep_tcf_chain_is_locked(काष्ठा tcf_chain *chain)
अणु
	वापस lockdep_is_held(&chain->filter_chain_lock);
पूर्ण

अटल अंतरभूत bool lockdep_tcf_proto_is_locked(काष्ठा tcf_proto *tp)
अणु
	वापस lockdep_is_held(&tp->lock);
पूर्ण

#घोषणा tcf_chain_dereference(p, chain)					\
	rcu_dereference_रक्षित(p, lockdep_tcf_chain_is_locked(chain))

#घोषणा tcf_proto_dereference(p, tp)					\
	rcu_dereference_रक्षित(p, lockdep_tcf_proto_is_locked(tp))

अटल अंतरभूत व्योम qdisc_cb_निजी_validate(स्थिर काष्ठा sk_buff *skb, पूर्णांक sz)
अणु
	काष्ठा qdisc_skb_cb *qcb;

	BUILD_BUG_ON(माप(skb->cb) < माप(*qcb));
	BUILD_BUG_ON(माप(qcb->data) < sz);
पूर्ण

अटल अंतरभूत पूर्णांक qdisc_qlen_cpu(स्थिर काष्ठा Qdisc *q)
अणु
	वापस this_cpu_ptr(q->cpu_qstats)->qlen;
पूर्ण

अटल अंतरभूत पूर्णांक qdisc_qlen(स्थिर काष्ठा Qdisc *q)
अणु
	वापस q->q.qlen;
पूर्ण

अटल अंतरभूत पूर्णांक qdisc_qlen_sum(स्थिर काष्ठा Qdisc *q)
अणु
	__u32 qlen = q->qstats.qlen;
	पूर्णांक i;

	अगर (qdisc_is_percpu_stats(q)) अणु
		क्रम_each_possible_cpu(i)
			qlen += per_cpu_ptr(q->cpu_qstats, i)->qlen;
	पूर्ण अन्यथा अणु
		qlen += q->q.qlen;
	पूर्ण

	वापस qlen;
पूर्ण

अटल अंतरभूत काष्ठा qdisc_skb_cb *qdisc_skb_cb(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा qdisc_skb_cb *)skb->cb;
पूर्ण

अटल अंतरभूत spinlock_t *qdisc_lock(काष्ठा Qdisc *qdisc)
अणु
	वापस &qdisc->q.lock;
पूर्ण

अटल अंतरभूत काष्ठा Qdisc *qdisc_root(स्थिर काष्ठा Qdisc *qdisc)
अणु
	काष्ठा Qdisc *q = rcu_dereference_rtnl(qdisc->dev_queue->qdisc);

	वापस q;
पूर्ण

अटल अंतरभूत काष्ठा Qdisc *qdisc_root_bh(स्थिर काष्ठा Qdisc *qdisc)
अणु
	वापस rcu_dereference_bh(qdisc->dev_queue->qdisc);
पूर्ण

अटल अंतरभूत काष्ठा Qdisc *qdisc_root_sleeping(स्थिर काष्ठा Qdisc *qdisc)
अणु
	वापस qdisc->dev_queue->qdisc_sleeping;
पूर्ण

/* The qdisc root lock is a mechanism by which to top level
 * of a qdisc tree can be locked from any qdisc node in the
 * क्रमest.  This allows changing the configuration of some
 * aspect of the qdisc tree जबतक blocking out asynchronous
 * qdisc access in the packet processing paths.
 *
 * It is only legal to करो this when the root will not change
 * on us.  Otherwise we'll potentially lock the wrong qdisc
 * root.  This is enक्रमced by holding the RTNL semaphore, which
 * all users of this lock accessor must करो.
 */
अटल अंतरभूत spinlock_t *qdisc_root_lock(स्थिर काष्ठा Qdisc *qdisc)
अणु
	काष्ठा Qdisc *root = qdisc_root(qdisc);

	ASSERT_RTNL();
	वापस qdisc_lock(root);
पूर्ण

अटल अंतरभूत spinlock_t *qdisc_root_sleeping_lock(स्थिर काष्ठा Qdisc *qdisc)
अणु
	काष्ठा Qdisc *root = qdisc_root_sleeping(qdisc);

	ASSERT_RTNL();
	वापस qdisc_lock(root);
पूर्ण

अटल अंतरभूत seqcount_t *qdisc_root_sleeping_running(स्थिर काष्ठा Qdisc *qdisc)
अणु
	काष्ठा Qdisc *root = qdisc_root_sleeping(qdisc);

	ASSERT_RTNL();
	वापस &root->running;
पूर्ण

अटल अंतरभूत काष्ठा net_device *qdisc_dev(स्थिर काष्ठा Qdisc *qdisc)
अणु
	वापस qdisc->dev_queue->dev;
पूर्ण

अटल अंतरभूत व्योम sch_tree_lock(काष्ठा Qdisc *q)
अणु
	अगर (q->flags & TCQ_F_MQROOT)
		spin_lock_bh(qdisc_lock(q));
	अन्यथा
		spin_lock_bh(qdisc_root_sleeping_lock(q));
पूर्ण

अटल अंतरभूत व्योम sch_tree_unlock(काष्ठा Qdisc *q)
अणु
	अगर (q->flags & TCQ_F_MQROOT)
		spin_unlock_bh(qdisc_lock(q));
	अन्यथा
		spin_unlock_bh(qdisc_root_sleeping_lock(q));
पूर्ण

बाह्य काष्ठा Qdisc noop_qdisc;
बाह्य काष्ठा Qdisc_ops noop_qdisc_ops;
बाह्य काष्ठा Qdisc_ops pfअगरo_fast_ops;
बाह्य काष्ठा Qdisc_ops mq_qdisc_ops;
बाह्य काष्ठा Qdisc_ops noqueue_qdisc_ops;
बाह्य स्थिर काष्ठा Qdisc_ops *शेष_qdisc_ops;
अटल अंतरभूत स्थिर काष्ठा Qdisc_ops *
get_शेष_qdisc_ops(स्थिर काष्ठा net_device *dev, पूर्णांक ntx)
अणु
	वापस ntx < dev->real_num_tx_queues ?
			शेष_qdisc_ops : &pfअगरo_fast_ops;
पूर्ण

काष्ठा Qdisc_class_common अणु
	u32			classid;
	काष्ठा hlist_node	hnode;
पूर्ण;

काष्ठा Qdisc_class_hash अणु
	काष्ठा hlist_head	*hash;
	अचिन्हित पूर्णांक		hashsize;
	अचिन्हित पूर्णांक		hashmask;
	अचिन्हित पूर्णांक		hashelems;
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक qdisc_class_hash(u32 id, u32 mask)
अणु
	id ^= id >> 8;
	id ^= id >> 4;
	वापस id & mask;
पूर्ण

अटल अंतरभूत काष्ठा Qdisc_class_common *
qdisc_class_find(स्थिर काष्ठा Qdisc_class_hash *hash, u32 id)
अणु
	काष्ठा Qdisc_class_common *cl;
	अचिन्हित पूर्णांक h;

	अगर (!id)
		वापस शून्य;

	h = qdisc_class_hash(id, hash->hashmask);
	hlist_क्रम_each_entry(cl, &hash->hash[h], hnode) अणु
		अगर (cl->classid == id)
			वापस cl;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक tc_classid_to_hwtc(काष्ठा net_device *dev, u32 classid)
अणु
	u32 hwtc = TC_H_MIN(classid) - TC_H_MIN_PRIORITY;

	वापस (hwtc < netdev_get_num_tc(dev)) ? hwtc : -EINVAL;
पूर्ण

पूर्णांक qdisc_class_hash_init(काष्ठा Qdisc_class_hash *);
व्योम qdisc_class_hash_insert(काष्ठा Qdisc_class_hash *,
			     काष्ठा Qdisc_class_common *);
व्योम qdisc_class_hash_हटाओ(काष्ठा Qdisc_class_hash *,
			     काष्ठा Qdisc_class_common *);
व्योम qdisc_class_hash_grow(काष्ठा Qdisc *, काष्ठा Qdisc_class_hash *);
व्योम qdisc_class_hash_destroy(काष्ठा Qdisc_class_hash *);

पूर्णांक dev_qdisc_change_tx_queue_len(काष्ठा net_device *dev);
व्योम dev_init_scheduler(काष्ठा net_device *dev);
व्योम dev_shutकरोwn(काष्ठा net_device *dev);
व्योम dev_activate(काष्ठा net_device *dev);
व्योम dev_deactivate(काष्ठा net_device *dev);
व्योम dev_deactivate_many(काष्ठा list_head *head);
काष्ठा Qdisc *dev_graft_qdisc(काष्ठा netdev_queue *dev_queue,
			      काष्ठा Qdisc *qdisc);
व्योम qdisc_reset(काष्ठा Qdisc *qdisc);
व्योम qdisc_put(काष्ठा Qdisc *qdisc);
व्योम qdisc_put_unlocked(काष्ठा Qdisc *qdisc);
व्योम qdisc_tree_reduce_backlog(काष्ठा Qdisc *qdisc, पूर्णांक n, पूर्णांक len);
#अगर_घोषित CONFIG_NET_SCHED
पूर्णांक qdisc_offload_dump_helper(काष्ठा Qdisc *q, क्रमागत tc_setup_type type,
			      व्योम *type_data);
व्योम qdisc_offload_graft_helper(काष्ठा net_device *dev, काष्ठा Qdisc *sch,
				काष्ठा Qdisc *new, काष्ठा Qdisc *old,
				क्रमागत tc_setup_type type, व्योम *type_data,
				काष्ठा netlink_ext_ack *extack);
#अन्यथा
अटल अंतरभूत पूर्णांक
qdisc_offload_dump_helper(काष्ठा Qdisc *q, क्रमागत tc_setup_type type,
			  व्योम *type_data)
अणु
	q->flags &= ~TCQ_F_OFFLOADED;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
qdisc_offload_graft_helper(काष्ठा net_device *dev, काष्ठा Qdisc *sch,
			   काष्ठा Qdisc *new, काष्ठा Qdisc *old,
			   क्रमागत tc_setup_type type, व्योम *type_data,
			   काष्ठा netlink_ext_ack *extack)
अणु
पूर्ण
#पूर्ण_अगर
काष्ठा Qdisc *qdisc_alloc(काष्ठा netdev_queue *dev_queue,
			  स्थिर काष्ठा Qdisc_ops *ops,
			  काष्ठा netlink_ext_ack *extack);
व्योम qdisc_मुक्त(काष्ठा Qdisc *qdisc);
काष्ठा Qdisc *qdisc_create_dflt(काष्ठा netdev_queue *dev_queue,
				स्थिर काष्ठा Qdisc_ops *ops, u32 parentid,
				काष्ठा netlink_ext_ack *extack);
व्योम __qdisc_calculate_pkt_len(काष्ठा sk_buff *skb,
			       स्थिर काष्ठा qdisc_माप_प्रकारable *stab);
पूर्णांक skb_करो_redirect(काष्ठा sk_buff *);

अटल अंतरभूत bool skb_at_tc_ingress(स्थिर काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	वापस skb->tc_at_ingress;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool skb_skip_tc_classअगरy(काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	अगर (skb->tc_skip_classअगरy) अणु
		skb->tc_skip_classअगरy = 0;
		वापस true;
	पूर्ण
#पूर्ण_अगर
	वापस false;
पूर्ण

/* Reset all TX qdiscs greater than index of a device.  */
अटल अंतरभूत व्योम qdisc_reset_all_tx_gt(काष्ठा net_device *dev, अचिन्हित पूर्णांक i)
अणु
	काष्ठा Qdisc *qdisc;

	क्रम (; i < dev->num_tx_queues; i++) अणु
		qdisc = rtnl_dereference(netdev_get_tx_queue(dev, i)->qdisc);
		अगर (qdisc) अणु
			spin_lock_bh(qdisc_lock(qdisc));
			qdisc_reset(qdisc);
			spin_unlock_bh(qdisc_lock(qdisc));
		पूर्ण
	पूर्ण
पूर्ण

/* Are all TX queues of the device empty?  */
अटल अंतरभूत bool qdisc_all_tx_empty(स्थिर काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक i;

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
		काष्ठा netdev_queue *txq = netdev_get_tx_queue(dev, i);
		स्थिर काष्ठा Qdisc *q = rcu_dereference(txq->qdisc);

		अगर (!qdisc_is_empty(q)) अणु
			rcu_पढ़ो_unlock();
			वापस false;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस true;
पूर्ण

/* Are any of the TX qdiscs changing?  */
अटल अंतरभूत bool qdisc_tx_changing(स्थिर काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
		काष्ठा netdev_queue *txq = netdev_get_tx_queue(dev, i);
		अगर (rcu_access_poपूर्णांकer(txq->qdisc) != txq->qdisc_sleeping)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* Is the device using the noop qdisc on all queues?  */
अटल अंतरभूत bool qdisc_tx_is_noop(स्थिर काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
		काष्ठा netdev_queue *txq = netdev_get_tx_queue(dev, i);
		अगर (rcu_access_poपूर्णांकer(txq->qdisc) != &noop_qdisc)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक qdisc_pkt_len(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस qdisc_skb_cb(skb)->pkt_len;
पूर्ण

/* additional qdisc xmit flags (NET_XMIT_MASK in linux/netdevice.h) */
क्रमागत net_xmit_qdisc_t अणु
	__NET_XMIT_STOLEN = 0x00010000,
	__NET_XMIT_BYPASS = 0x00020000,
पूर्ण;

#अगर_घोषित CONFIG_NET_CLS_ACT
#घोषणा net_xmit_drop_count(e)	((e) & __NET_XMIT_STOLEN ? 0 : 1)
#अन्यथा
#घोषणा net_xmit_drop_count(e)	(1)
#पूर्ण_अगर

अटल अंतरभूत व्योम qdisc_calculate_pkt_len(काष्ठा sk_buff *skb,
					   स्थिर काष्ठा Qdisc *sch)
अणु
#अगर_घोषित CONFIG_NET_SCHED
	काष्ठा qdisc_माप_प्रकारable *stab = rcu_dereference_bh(sch->stab);

	अगर (stab)
		__qdisc_calculate_pkt_len(skb, stab);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक qdisc_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
				काष्ठा sk_buff **to_मुक्त)
अणु
	qdisc_calculate_pkt_len(skb, sch);
	वापस sch->enqueue(skb, sch, to_मुक्त);
पूर्ण

अटल अंतरभूत व्योम _bstats_update(काष्ठा gnet_stats_basic_packed *bstats,
				  __u64 bytes, __u32 packets)
अणु
	bstats->bytes += bytes;
	bstats->packets += packets;
पूर्ण

अटल अंतरभूत व्योम bstats_update(काष्ठा gnet_stats_basic_packed *bstats,
				 स्थिर काष्ठा sk_buff *skb)
अणु
	_bstats_update(bstats,
		       qdisc_pkt_len(skb),
		       skb_is_gso(skb) ? skb_shinfo(skb)->gso_segs : 1);
पूर्ण

अटल अंतरभूत व्योम _bstats_cpu_update(काष्ठा gnet_stats_basic_cpu *bstats,
				      __u64 bytes, __u32 packets)
अणु
	u64_stats_update_begin(&bstats->syncp);
	_bstats_update(&bstats->bstats, bytes, packets);
	u64_stats_update_end(&bstats->syncp);
पूर्ण

अटल अंतरभूत व्योम bstats_cpu_update(काष्ठा gnet_stats_basic_cpu *bstats,
				     स्थिर काष्ठा sk_buff *skb)
अणु
	u64_stats_update_begin(&bstats->syncp);
	bstats_update(&bstats->bstats, skb);
	u64_stats_update_end(&bstats->syncp);
पूर्ण

अटल अंतरभूत व्योम qdisc_bstats_cpu_update(काष्ठा Qdisc *sch,
					   स्थिर काष्ठा sk_buff *skb)
अणु
	bstats_cpu_update(this_cpu_ptr(sch->cpu_bstats), skb);
पूर्ण

अटल अंतरभूत व्योम qdisc_bstats_update(काष्ठा Qdisc *sch,
				       स्थिर काष्ठा sk_buff *skb)
अणु
	bstats_update(&sch->bstats, skb);
पूर्ण

अटल अंतरभूत व्योम qdisc_qstats_backlog_dec(काष्ठा Qdisc *sch,
					    स्थिर काष्ठा sk_buff *skb)
अणु
	sch->qstats.backlog -= qdisc_pkt_len(skb);
पूर्ण

अटल अंतरभूत व्योम qdisc_qstats_cpu_backlog_dec(काष्ठा Qdisc *sch,
						स्थिर काष्ठा sk_buff *skb)
अणु
	this_cpu_sub(sch->cpu_qstats->backlog, qdisc_pkt_len(skb));
पूर्ण

अटल अंतरभूत व्योम qdisc_qstats_backlog_inc(काष्ठा Qdisc *sch,
					    स्थिर काष्ठा sk_buff *skb)
अणु
	sch->qstats.backlog += qdisc_pkt_len(skb);
पूर्ण

अटल अंतरभूत व्योम qdisc_qstats_cpu_backlog_inc(काष्ठा Qdisc *sch,
						स्थिर काष्ठा sk_buff *skb)
अणु
	this_cpu_add(sch->cpu_qstats->backlog, qdisc_pkt_len(skb));
पूर्ण

अटल अंतरभूत व्योम qdisc_qstats_cpu_qlen_inc(काष्ठा Qdisc *sch)
अणु
	this_cpu_inc(sch->cpu_qstats->qlen);
पूर्ण

अटल अंतरभूत व्योम qdisc_qstats_cpu_qlen_dec(काष्ठा Qdisc *sch)
अणु
	this_cpu_dec(sch->cpu_qstats->qlen);
पूर्ण

अटल अंतरभूत व्योम qdisc_qstats_cpu_requeues_inc(काष्ठा Qdisc *sch)
अणु
	this_cpu_inc(sch->cpu_qstats->requeues);
पूर्ण

अटल अंतरभूत व्योम __qdisc_qstats_drop(काष्ठा Qdisc *sch, पूर्णांक count)
अणु
	sch->qstats.drops += count;
पूर्ण

अटल अंतरभूत व्योम qstats_drop_inc(काष्ठा gnet_stats_queue *qstats)
अणु
	qstats->drops++;
पूर्ण

अटल अंतरभूत व्योम qstats_overlimit_inc(काष्ठा gnet_stats_queue *qstats)
अणु
	qstats->overlimits++;
पूर्ण

अटल अंतरभूत व्योम qdisc_qstats_drop(काष्ठा Qdisc *sch)
अणु
	qstats_drop_inc(&sch->qstats);
पूर्ण

अटल अंतरभूत व्योम qdisc_qstats_cpu_drop(काष्ठा Qdisc *sch)
अणु
	this_cpu_inc(sch->cpu_qstats->drops);
पूर्ण

अटल अंतरभूत व्योम qdisc_qstats_overlimit(काष्ठा Qdisc *sch)
अणु
	sch->qstats.overlimits++;
पूर्ण

अटल अंतरभूत पूर्णांक qdisc_qstats_copy(काष्ठा gnet_dump *d, काष्ठा Qdisc *sch)
अणु
	__u32 qlen = qdisc_qlen_sum(sch);

	वापस gnet_stats_copy_queue(d, sch->cpu_qstats, &sch->qstats, qlen);
पूर्ण

अटल अंतरभूत व्योम qdisc_qstats_qlen_backlog(काष्ठा Qdisc *sch,  __u32 *qlen,
					     __u32 *backlog)
अणु
	काष्ठा gnet_stats_queue qstats = अणु 0 पूर्ण;
	__u32 len = qdisc_qlen_sum(sch);

	__gnet_stats_copy_queue(&qstats, sch->cpu_qstats, &sch->qstats, len);
	*qlen = qstats.qlen;
	*backlog = qstats.backlog;
पूर्ण

अटल अंतरभूत व्योम qdisc_tree_flush_backlog(काष्ठा Qdisc *sch)
अणु
	__u32 qlen, backlog;

	qdisc_qstats_qlen_backlog(sch, &qlen, &backlog);
	qdisc_tree_reduce_backlog(sch, qlen, backlog);
पूर्ण

अटल अंतरभूत व्योम qdisc_purge_queue(काष्ठा Qdisc *sch)
अणु
	__u32 qlen, backlog;

	qdisc_qstats_qlen_backlog(sch, &qlen, &backlog);
	qdisc_reset(sch);
	qdisc_tree_reduce_backlog(sch, qlen, backlog);
पूर्ण

अटल अंतरभूत व्योम qdisc_skb_head_init(काष्ठा qdisc_skb_head *qh)
अणु
	qh->head = शून्य;
	qh->tail = शून्य;
	qh->qlen = 0;
पूर्ण

अटल अंतरभूत व्योम __qdisc_enqueue_tail(काष्ठा sk_buff *skb,
					काष्ठा qdisc_skb_head *qh)
अणु
	काष्ठा sk_buff *last = qh->tail;

	अगर (last) अणु
		skb->next = शून्य;
		last->next = skb;
		qh->tail = skb;
	पूर्ण अन्यथा अणु
		qh->tail = skb;
		qh->head = skb;
	पूर्ण
	qh->qlen++;
पूर्ण

अटल अंतरभूत पूर्णांक qdisc_enqueue_tail(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch)
अणु
	__qdisc_enqueue_tail(skb, &sch->q);
	qdisc_qstats_backlog_inc(sch, skb);
	वापस NET_XMIT_SUCCESS;
पूर्ण

अटल अंतरभूत व्योम __qdisc_enqueue_head(काष्ठा sk_buff *skb,
					काष्ठा qdisc_skb_head *qh)
अणु
	skb->next = qh->head;

	अगर (!qh->head)
		qh->tail = skb;
	qh->head = skb;
	qh->qlen++;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *__qdisc_dequeue_head(काष्ठा qdisc_skb_head *qh)
अणु
	काष्ठा sk_buff *skb = qh->head;

	अगर (likely(skb != शून्य)) अणु
		qh->head = skb->next;
		qh->qlen--;
		अगर (qh->head == शून्य)
			qh->tail = शून्य;
		skb->next = शून्य;
	पूर्ण

	वापस skb;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *qdisc_dequeue_head(काष्ठा Qdisc *sch)
अणु
	काष्ठा sk_buff *skb = __qdisc_dequeue_head(&sch->q);

	अगर (likely(skb != शून्य)) अणु
		qdisc_qstats_backlog_dec(sch, skb);
		qdisc_bstats_update(sch, skb);
	पूर्ण

	वापस skb;
पूर्ण

/* Instead of calling kमुक्त_skb() जबतक root qdisc lock is held,
 * queue the skb क्रम future मुक्तing at end of __dev_xmit_skb()
 */
अटल अंतरभूत व्योम __qdisc_drop(काष्ठा sk_buff *skb, काष्ठा sk_buff **to_मुक्त)
अणु
	skb->next = *to_मुक्त;
	*to_मुक्त = skb;
पूर्ण

अटल अंतरभूत व्योम __qdisc_drop_all(काष्ठा sk_buff *skb,
				    काष्ठा sk_buff **to_मुक्त)
अणु
	अगर (skb->prev)
		skb->prev->next = *to_मुक्त;
	अन्यथा
		skb->next = *to_मुक्त;
	*to_मुक्त = skb;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __qdisc_queue_drop_head(काष्ठा Qdisc *sch,
						   काष्ठा qdisc_skb_head *qh,
						   काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा sk_buff *skb = __qdisc_dequeue_head(qh);

	अगर (likely(skb != शून्य)) अणु
		अचिन्हित पूर्णांक len = qdisc_pkt_len(skb);

		qdisc_qstats_backlog_dec(sch, skb);
		__qdisc_drop(skb, to_मुक्त);
		वापस len;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *qdisc_peek_head(काष्ठा Qdisc *sch)
अणु
	स्थिर काष्ठा qdisc_skb_head *qh = &sch->q;

	वापस qh->head;
पूर्ण

/* generic pseuकरो peek method क्रम non-work-conserving qdisc */
अटल अंतरभूत काष्ठा sk_buff *qdisc_peek_dequeued(काष्ठा Qdisc *sch)
अणु
	काष्ठा sk_buff *skb = skb_peek(&sch->gso_skb);

	/* we can reuse ->gso_skb because peek isn't called क्रम root qdiscs */
	अगर (!skb) अणु
		skb = sch->dequeue(sch);

		अगर (skb) अणु
			__skb_queue_head(&sch->gso_skb, skb);
			/* it's still part of the queue */
			qdisc_qstats_backlog_inc(sch, skb);
			sch->q.qlen++;
		पूर्ण
	पूर्ण

	वापस skb;
पूर्ण

अटल अंतरभूत व्योम qdisc_update_stats_at_dequeue(काष्ठा Qdisc *sch,
						 काष्ठा sk_buff *skb)
अणु
	अगर (qdisc_is_percpu_stats(sch)) अणु
		qdisc_qstats_cpu_backlog_dec(sch, skb);
		qdisc_bstats_cpu_update(sch, skb);
		qdisc_qstats_cpu_qlen_dec(sch);
	पूर्ण अन्यथा अणु
		qdisc_qstats_backlog_dec(sch, skb);
		qdisc_bstats_update(sch, skb);
		sch->q.qlen--;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम qdisc_update_stats_at_enqueue(काष्ठा Qdisc *sch,
						 अचिन्हित पूर्णांक pkt_len)
अणु
	अगर (qdisc_is_percpu_stats(sch)) अणु
		qdisc_qstats_cpu_qlen_inc(sch);
		this_cpu_add(sch->cpu_qstats->backlog, pkt_len);
	पूर्ण अन्यथा अणु
		sch->qstats.backlog += pkt_len;
		sch->q.qlen++;
	पूर्ण
पूर्ण

/* use instead of qdisc->dequeue() क्रम all qdiscs queried with ->peek() */
अटल अंतरभूत काष्ठा sk_buff *qdisc_dequeue_peeked(काष्ठा Qdisc *sch)
अणु
	काष्ठा sk_buff *skb = skb_peek(&sch->gso_skb);

	अगर (skb) अणु
		skb = __skb_dequeue(&sch->gso_skb);
		अगर (qdisc_is_percpu_stats(sch)) अणु
			qdisc_qstats_cpu_backlog_dec(sch, skb);
			qdisc_qstats_cpu_qlen_dec(sch);
		पूर्ण अन्यथा अणु
			qdisc_qstats_backlog_dec(sch, skb);
			sch->q.qlen--;
		पूर्ण
	पूर्ण अन्यथा अणु
		skb = sch->dequeue(sch);
	पूर्ण

	वापस skb;
पूर्ण

अटल अंतरभूत व्योम __qdisc_reset_queue(काष्ठा qdisc_skb_head *qh)
अणु
	/*
	 * We करो not know the backlog in bytes of this list, it
	 * is up to the caller to correct it
	 */
	ASSERT_RTNL();
	अगर (qh->qlen) अणु
		rtnl_kमुक्त_skbs(qh->head, qh->tail);

		qh->head = शून्य;
		qh->tail = शून्य;
		qh->qlen = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम qdisc_reset_queue(काष्ठा Qdisc *sch)
अणु
	__qdisc_reset_queue(&sch->q);
	sch->qstats.backlog = 0;
पूर्ण

अटल अंतरभूत काष्ठा Qdisc *qdisc_replace(काष्ठा Qdisc *sch, काष्ठा Qdisc *new,
					  काष्ठा Qdisc **pold)
अणु
	काष्ठा Qdisc *old;

	sch_tree_lock(sch);
	old = *pold;
	*pold = new;
	अगर (old != शून्य)
		qdisc_purge_queue(old);
	sch_tree_unlock(sch);

	वापस old;
पूर्ण

अटल अंतरभूत व्योम rtnl_qdisc_drop(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch)
अणु
	rtnl_kमुक्त_skbs(skb, skb);
	qdisc_qstats_drop(sch);
पूर्ण

अटल अंतरभूत पूर्णांक qdisc_drop_cpu(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
				 काष्ठा sk_buff **to_मुक्त)
अणु
	__qdisc_drop(skb, to_मुक्त);
	qdisc_qstats_cpu_drop(sch);

	वापस NET_XMIT_DROP;
पूर्ण

अटल अंतरभूत पूर्णांक qdisc_drop(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
			     काष्ठा sk_buff **to_मुक्त)
अणु
	__qdisc_drop(skb, to_मुक्त);
	qdisc_qstats_drop(sch);

	वापस NET_XMIT_DROP;
पूर्ण

अटल अंतरभूत पूर्णांक qdisc_drop_all(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
				 काष्ठा sk_buff **to_मुक्त)
अणु
	__qdisc_drop_all(skb, to_मुक्त);
	qdisc_qstats_drop(sch);

	वापस NET_XMIT_DROP;
पूर्ण

/* Length to Time (L2T) lookup in a qdisc_rate_table, to determine how
   दीर्घ it will take to send a packet given its size.
 */
अटल अंतरभूत u32 qdisc_l2t(काष्ठा qdisc_rate_table* rtab, अचिन्हित पूर्णांक pktlen)
अणु
	पूर्णांक slot = pktlen + rtab->rate.cell_align + rtab->rate.overhead;
	अगर (slot < 0)
		slot = 0;
	slot >>= rtab->rate.cell_log;
	अगर (slot > 255)
		वापस rtab->data[255]*(slot >> 8) + rtab->data[slot & 0xFF];
	वापस rtab->data[slot];
पूर्ण

काष्ठा psched_ratecfg अणु
	u64	rate_bytes_ps; /* bytes per second */
	u32	mult;
	u16	overhead;
	u8	linklayer;
	u8	shअगरt;
पूर्ण;

अटल अंतरभूत u64 psched_l2t_ns(स्थिर काष्ठा psched_ratecfg *r,
				अचिन्हित पूर्णांक len)
अणु
	len += r->overhead;

	अगर (unlikely(r->linklayer == TC_LINKLAYER_ATM))
		वापस ((u64)(DIV_ROUND_UP(len,48)*53) * r->mult) >> r->shअगरt;

	वापस ((u64)len * r->mult) >> r->shअगरt;
पूर्ण

व्योम psched_ratecfg_precompute(काष्ठा psched_ratecfg *r,
			       स्थिर काष्ठा tc_ratespec *conf,
			       u64 rate64);

अटल अंतरभूत व्योम psched_ratecfg_getrate(काष्ठा tc_ratespec *res,
					  स्थिर काष्ठा psched_ratecfg *r)
अणु
	स_रखो(res, 0, माप(*res));

	/* legacy काष्ठा tc_ratespec has a 32bit @rate field
	 * Qdisc using 64bit rate should add new attributes
	 * in order to मुख्यtain compatibility.
	 */
	res->rate = min_t(u64, r->rate_bytes_ps, ~0U);

	res->overhead = r->overhead;
	res->linklayer = (r->linklayer & TC_LINKLAYER_MASK);
पूर्ण

काष्ठा psched_pktrate अणु
	u64	rate_pkts_ps; /* packets per second */
	u32	mult;
	u8	shअगरt;
पूर्ण;

अटल अंतरभूत u64 psched_pkt2t_ns(स्थिर काष्ठा psched_pktrate *r,
				  अचिन्हित पूर्णांक pkt_num)
अणु
	वापस ((u64)pkt_num * r->mult) >> r->shअगरt;
पूर्ण

व्योम psched_ppscfg_precompute(काष्ठा psched_pktrate *r, u64 pktrate64);

/* Mini Qdisc serves क्रम specअगरic needs of ingress/clsact Qdisc.
 * The fast path only needs to access filter list and to update stats
 */
काष्ठा mini_Qdisc अणु
	काष्ठा tcf_proto *filter_list;
	काष्ठा tcf_block *block;
	काष्ठा gnet_stats_basic_cpu __percpu *cpu_bstats;
	काष्ठा gnet_stats_queue	__percpu *cpu_qstats;
	काष्ठा rcu_head rcu;
पूर्ण;

अटल अंतरभूत व्योम mini_qdisc_bstats_cpu_update(काष्ठा mini_Qdisc *miniq,
						स्थिर काष्ठा sk_buff *skb)
अणु
	bstats_cpu_update(this_cpu_ptr(miniq->cpu_bstats), skb);
पूर्ण

अटल अंतरभूत व्योम mini_qdisc_qstats_cpu_drop(काष्ठा mini_Qdisc *miniq)
अणु
	this_cpu_inc(miniq->cpu_qstats->drops);
पूर्ण

काष्ठा mini_Qdisc_pair अणु
	काष्ठा mini_Qdisc miniq1;
	काष्ठा mini_Qdisc miniq2;
	काष्ठा mini_Qdisc __rcu **p_miniq;
पूर्ण;

व्योम mini_qdisc_pair_swap(काष्ठा mini_Qdisc_pair *miniqp,
			  काष्ठा tcf_proto *tp_head);
व्योम mini_qdisc_pair_init(काष्ठा mini_Qdisc_pair *miniqp, काष्ठा Qdisc *qdisc,
			  काष्ठा mini_Qdisc __rcu **p_miniq);
व्योम mini_qdisc_pair_block_init(काष्ठा mini_Qdisc_pair *miniqp,
				काष्ठा tcf_block *block);

पूर्णांक sch_frag_xmit_hook(काष्ठा sk_buff *skb, पूर्णांक (*xmit)(काष्ठा sk_buff *skb));

#पूर्ण_अगर
