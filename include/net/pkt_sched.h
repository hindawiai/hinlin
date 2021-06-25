<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_PKT_SCHED_H
#घोषणा __NET_PKT_SCHED_H

#समावेश <linux/jअगरfies.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/netdevice.h>
#समावेश <net/sch_generic.h>
#समावेश <net/net_namespace.h>
#समावेश <uapi/linux/pkt_sched.h>

#घोषणा DEFAULT_TX_QUEUE_LEN	1000

काष्ठा qdisc_walker अणु
	पूर्णांक	stop;
	पूर्णांक	skip;
	पूर्णांक	count;
	पूर्णांक	(*fn)(काष्ठा Qdisc *, अचिन्हित दीर्घ cl, काष्ठा qdisc_walker *);
पूर्ण;

अटल अंतरभूत व्योम *qdisc_priv(काष्ठा Qdisc *q)
अणु
	वापस &q->privdata;
पूर्ण

अटल अंतरभूत काष्ठा Qdisc *qdisc_from_priv(व्योम *priv)
अणु
	वापस container_of(priv, काष्ठा Qdisc, privdata);
पूर्ण

/* 
   Timer resolution MUST BE < 10% of min_schedulable_packet_size/bandwidth
   
   Normal IP packet size ~ 512byte, hence:

   0.5Kbyte/1Mbyte/sec = 0.5msec, so that we need 50usec समयr क्रम
   10Mbit ethernet.

   10msec resolution -> <50Kbit/sec.
   
   The result: [34]86 is not good choice क्रम QoS router :-(

   The things are not so bad, because we may use artअगरicial
   घड़ी evaluated by पूर्णांकegration of network data flow
   in the most critical places.
 */

प्रकार u64	psched_समय_प्रकार;
प्रकार दीर्घ	psched_tdअगरf_t;

/* Aव्योम करोing 64 bit भागide */
#घोषणा PSCHED_SHIFT			6
#घोषणा PSCHED_TICKS2NS(x)		((s64)(x) << PSCHED_SHIFT)
#घोषणा PSCHED_NS2TICKS(x)		((x) >> PSCHED_SHIFT)

#घोषणा PSCHED_TICKS_PER_SEC		PSCHED_NS2TICKS(NSEC_PER_SEC)
#घोषणा PSCHED_PASTPERFECT		0

अटल अंतरभूत psched_समय_प्रकार psched_get_समय(व्योम)
अणु
	वापस PSCHED_NS2TICKS(kसमय_get_ns());
पूर्ण

अटल अंतरभूत psched_tdअगरf_t
psched_tdअगरf_bounded(psched_समय_प्रकार tv1, psched_समय_प्रकार tv2, psched_समय_प्रकार bound)
अणु
	वापस min(tv1 - tv2, bound);
पूर्ण

काष्ठा qdisc_watchकरोg अणु
	u64		last_expires;
	काष्ठा hrसमयr	समयr;
	काष्ठा Qdisc	*qdisc;
पूर्ण;

व्योम qdisc_watchकरोg_init_घड़ीid(काष्ठा qdisc_watchकरोg *wd, काष्ठा Qdisc *qdisc,
				 घड़ीid_t घड़ीid);
व्योम qdisc_watchकरोg_init(काष्ठा qdisc_watchकरोg *wd, काष्ठा Qdisc *qdisc);

व्योम qdisc_watchकरोg_schedule_range_ns(काष्ठा qdisc_watchकरोg *wd, u64 expires,
				      u64 delta_ns);

अटल अंतरभूत व्योम qdisc_watchकरोg_schedule_ns(काष्ठा qdisc_watchकरोg *wd,
					      u64 expires)
अणु
	वापस qdisc_watchकरोg_schedule_range_ns(wd, expires, 0ULL);
पूर्ण

अटल अंतरभूत व्योम qdisc_watchकरोg_schedule(काष्ठा qdisc_watchकरोg *wd,
					   psched_समय_प्रकार expires)
अणु
	qdisc_watchकरोg_schedule_ns(wd, PSCHED_TICKS2NS(expires));
पूर्ण

व्योम qdisc_watchकरोg_cancel(काष्ठा qdisc_watchकरोg *wd);

बाह्य काष्ठा Qdisc_ops pfअगरo_qdisc_ops;
बाह्य काष्ठा Qdisc_ops bfअगरo_qdisc_ops;
बाह्य काष्ठा Qdisc_ops pfअगरo_head_drop_qdisc_ops;

पूर्णांक fअगरo_set_limit(काष्ठा Qdisc *q, अचिन्हित पूर्णांक limit);
काष्ठा Qdisc *fअगरo_create_dflt(काष्ठा Qdisc *sch, काष्ठा Qdisc_ops *ops,
			       अचिन्हित पूर्णांक limit,
			       काष्ठा netlink_ext_ack *extack);

पूर्णांक रेजिस्टर_qdisc(काष्ठा Qdisc_ops *qops);
पूर्णांक unरेजिस्टर_qdisc(काष्ठा Qdisc_ops *qops);
व्योम qdisc_get_शेष(अक्षर *id, माप_प्रकार len);
पूर्णांक qdisc_set_शेष(स्थिर अक्षर *id);

व्योम qdisc_hash_add(काष्ठा Qdisc *q, bool invisible);
व्योम qdisc_hash_del(काष्ठा Qdisc *q);
काष्ठा Qdisc *qdisc_lookup(काष्ठा net_device *dev, u32 handle);
काष्ठा Qdisc *qdisc_lookup_rcu(काष्ठा net_device *dev, u32 handle);
काष्ठा qdisc_rate_table *qdisc_get_rtab(काष्ठा tc_ratespec *r,
					काष्ठा nlattr *tab,
					काष्ठा netlink_ext_ack *extack);
व्योम qdisc_put_rtab(काष्ठा qdisc_rate_table *tab);
व्योम qdisc_put_stab(काष्ठा qdisc_माप_प्रकारable *tab);
व्योम qdisc_warn_nonwc(स्थिर अक्षर *txt, काष्ठा Qdisc *qdisc);
bool sch_direct_xmit(काष्ठा sk_buff *skb, काष्ठा Qdisc *q,
		     काष्ठा net_device *dev, काष्ठा netdev_queue *txq,
		     spinlock_t *root_lock, bool validate);

व्योम __qdisc_run(काष्ठा Qdisc *q);

अटल अंतरभूत व्योम qdisc_run(काष्ठा Qdisc *q)
अणु
	अगर (qdisc_run_begin(q)) अणु
		__qdisc_run(q);
		qdisc_run_end(q);
	पूर्ण
पूर्ण

/* Calculate maximal size of packet seen by hard_start_xmit
   routine of this device.
 */
अटल अंतरभूत अचिन्हित पूर्णांक psched_mtu(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->mtu + dev->hard_header_len;
पूर्ण

अटल अंतरभूत काष्ठा net *qdisc_net(काष्ठा Qdisc *q)
अणु
	वापस dev_net(q->dev_queue->dev);
पूर्ण

काष्ठा tc_cbs_qopt_offload अणु
	u8 enable;
	s32 queue;
	s32 hicredit;
	s32 locredit;
	s32 idleslope;
	s32 sendslope;
पूर्ण;

काष्ठा tc_etf_qopt_offload अणु
	u8 enable;
	s32 queue;
पूर्ण;

काष्ठा tc_taprio_sched_entry अणु
	u8 command; /* TC_TAPRIO_CMD_* */

	/* The gate_mask in the offloading side refers to traffic classes */
	u32 gate_mask;
	u32 पूर्णांकerval;
पूर्ण;

काष्ठा tc_taprio_qopt_offload अणु
	u8 enable;
	kसमय_प्रकार base_समय;
	u64 cycle_समय;
	u64 cycle_समय_extension;

	माप_प्रकार num_entries;
	काष्ठा tc_taprio_sched_entry entries[];
पूर्ण;

/* Reference counting */
काष्ठा tc_taprio_qopt_offload *taprio_offload_get(काष्ठा tc_taprio_qopt_offload
						  *offload);
व्योम taprio_offload_मुक्त(काष्ठा tc_taprio_qopt_offload *offload);

/* Ensure skb_mstamp_ns, which might have been populated with the txसमय, is
 * not mistaken क्रम a software बारtamp, because this will otherwise prevent
 * the dispatch of hardware बारtamps to the socket.
 */
अटल अंतरभूत व्योम skb_txसमय_consumed(काष्ठा sk_buff *skb)
अणु
	skb->tstamp = kसमय_set(0, 0);
पूर्ण

#पूर्ण_अगर
