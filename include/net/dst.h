<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * net/dst.h	Protocol independent destination cache definitions.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 *
 */

#अगर_अघोषित _NET_DST_H
#घोषणा _NET_DST_H

#समावेश <net/dst_ops.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/bug.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/refcount.h>
#समावेश <net/neighbour.h>
#समावेश <यंत्र/processor.h>
#समावेश <linux/indirect_call_wrapper.h>

काष्ठा sk_buff;

काष्ठा dst_entry अणु
	काष्ठा net_device       *dev;
	काष्ठा  dst_ops	        *ops;
	अचिन्हित दीर्घ		_metrics;
	अचिन्हित दीर्घ           expires;
#अगर_घोषित CONFIG_XFRM
	काष्ठा xfrm_state	*xfrm;
#अन्यथा
	व्योम			*__pad1;
#पूर्ण_अगर
	पूर्णांक			(*input)(काष्ठा sk_buff *);
	पूर्णांक			(*output)(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);

	अचिन्हित लघु		flags;
#घोषणा DST_NOXFRM		0x0002
#घोषणा DST_NOPOLICY		0x0004
#घोषणा DST_NOCOUNT		0x0008
#घोषणा DST_FAKE_RTABLE		0x0010
#घोषणा DST_XFRM_TUNNEL		0x0020
#घोषणा DST_XFRM_QUEUE		0x0040
#घोषणा DST_METADATA		0x0080

	/* A non-zero value of dst->obsolete क्रमces by-hand validation
	 * of the route entry.  Positive values are set by the generic
	 * dst layer to indicate that the entry has been क्रमcefully
	 * destroyed.
	 *
	 * Negative values are used by the implementation layer code to
	 * क्रमce invocation of the dst_ops->check() method.
	 */
	लघु			obsolete;
#घोषणा DST_OBSOLETE_NONE	0
#घोषणा DST_OBSOLETE_DEAD	2
#घोषणा DST_OBSOLETE_FORCE_CHK	-1
#घोषणा DST_OBSOLETE_KILL	-2
	अचिन्हित लघु		header_len;	/* more space at head required */
	अचिन्हित लघु		trailer_len;	/* space to reserve at tail */

	/*
	 * __refcnt wants to be on a dअगरferent cache line from
	 * input/output/ops or perक्रमmance tanks badly
	 */
#अगर_घोषित CONFIG_64BIT
	atomic_t		__refcnt;	/* 64-bit offset 64 */
#पूर्ण_अगर
	पूर्णांक			__use;
	अचिन्हित दीर्घ		lastuse;
	काष्ठा lwtunnel_state   *lwtstate;
	काष्ठा rcu_head		rcu_head;
	लघु			error;
	लघु			__pad;
	__u32			tclassid;
#अगर_अघोषित CONFIG_64BIT
	atomic_t		__refcnt;	/* 32-bit offset 64 */
#पूर्ण_अगर
पूर्ण;

काष्ठा dst_metrics अणु
	u32		metrics[RTAX_MAX];
	refcount_t	refcnt;
पूर्ण __aligned(4);		/* Low poपूर्णांकer bits contain DST_METRICS_FLAGS */
बाह्य स्थिर काष्ठा dst_metrics dst_शेष_metrics;

u32 *dst_cow_metrics_generic(काष्ठा dst_entry *dst, अचिन्हित दीर्घ old);

#घोषणा DST_METRICS_READ_ONLY		0x1UL
#घोषणा DST_METRICS_REFCOUNTED		0x2UL
#घोषणा DST_METRICS_FLAGS		0x3UL
#घोषणा __DST_METRICS_PTR(Y)	\
	((u32 *)((Y) & ~DST_METRICS_FLAGS))
#घोषणा DST_METRICS_PTR(X)	__DST_METRICS_PTR((X)->_metrics)

अटल अंतरभूत bool dst_metrics_पढ़ो_only(स्थिर काष्ठा dst_entry *dst)
अणु
	वापस dst->_metrics & DST_METRICS_READ_ONLY;
पूर्ण

व्योम __dst_destroy_metrics_generic(काष्ठा dst_entry *dst, अचिन्हित दीर्घ old);

अटल अंतरभूत व्योम dst_destroy_metrics_generic(काष्ठा dst_entry *dst)
अणु
	अचिन्हित दीर्घ val = dst->_metrics;
	अगर (!(val & DST_METRICS_READ_ONLY))
		__dst_destroy_metrics_generic(dst, val);
पूर्ण

अटल अंतरभूत u32 *dst_metrics_ग_लिखो_ptr(काष्ठा dst_entry *dst)
अणु
	अचिन्हित दीर्घ p = dst->_metrics;

	BUG_ON(!p);

	अगर (p & DST_METRICS_READ_ONLY)
		वापस dst->ops->cow_metrics(dst, p);
	वापस __DST_METRICS_PTR(p);
पूर्ण

/* This may only be invoked beक्रमe the entry has reached global
 * visibility.
 */
अटल अंतरभूत व्योम dst_init_metrics(काष्ठा dst_entry *dst,
				    स्थिर u32 *src_metrics,
				    bool पढ़ो_only)
अणु
	dst->_metrics = ((अचिन्हित दीर्घ) src_metrics) |
		(पढ़ो_only ? DST_METRICS_READ_ONLY : 0);
पूर्ण

अटल अंतरभूत व्योम dst_copy_metrics(काष्ठा dst_entry *dest, स्थिर काष्ठा dst_entry *src)
अणु
	u32 *dst_metrics = dst_metrics_ग_लिखो_ptr(dest);

	अगर (dst_metrics) अणु
		u32 *src_metrics = DST_METRICS_PTR(src);

		स_नकल(dst_metrics, src_metrics, RTAX_MAX * माप(u32));
	पूर्ण
पूर्ण

अटल अंतरभूत u32 *dst_metrics_ptr(काष्ठा dst_entry *dst)
अणु
	वापस DST_METRICS_PTR(dst);
पूर्ण

अटल अंतरभूत u32
dst_metric_raw(स्थिर काष्ठा dst_entry *dst, स्थिर पूर्णांक metric)
अणु
	u32 *p = DST_METRICS_PTR(dst);

	वापस p[metric-1];
पूर्ण

अटल अंतरभूत u32
dst_metric(स्थिर काष्ठा dst_entry *dst, स्थिर पूर्णांक metric)
अणु
	WARN_ON_ONCE(metric == RTAX_HOPLIMIT ||
		     metric == RTAX_ADVMSS ||
		     metric == RTAX_MTU);
	वापस dst_metric_raw(dst, metric);
पूर्ण

अटल अंतरभूत u32
dst_metric_advmss(स्थिर काष्ठा dst_entry *dst)
अणु
	u32 advmss = dst_metric_raw(dst, RTAX_ADVMSS);

	अगर (!advmss)
		advmss = dst->ops->शेष_advmss(dst);

	वापस advmss;
पूर्ण

अटल अंतरभूत व्योम dst_metric_set(काष्ठा dst_entry *dst, पूर्णांक metric, u32 val)
अणु
	u32 *p = dst_metrics_ग_लिखो_ptr(dst);

	अगर (p)
		p[metric-1] = val;
पूर्ण

/* Kernel-पूर्णांकernal feature bits that are unallocated in user space. */
#घोषणा DST_FEATURE_ECN_CA	(1U << 31)

#घोषणा DST_FEATURE_MASK	(DST_FEATURE_ECN_CA)
#घोषणा DST_FEATURE_ECN_MASK	(DST_FEATURE_ECN_CA | RTAX_FEATURE_ECN)

अटल अंतरभूत u32
dst_feature(स्थिर काष्ठा dst_entry *dst, u32 feature)
अणु
	वापस dst_metric(dst, RTAX_FEATURES) & feature;
पूर्ण

INसूचीECT_CALLABLE_DECLARE(अचिन्हित पूर्णांक ip6_mtu(स्थिर काष्ठा dst_entry *));
INसूचीECT_CALLABLE_DECLARE(अचिन्हित पूर्णांक ipv4_mtu(स्थिर काष्ठा dst_entry *));
अटल अंतरभूत u32 dst_mtu(स्थिर काष्ठा dst_entry *dst)
अणु
	वापस INसूचीECT_CALL_INET(dst->ops->mtu, ip6_mtu, ipv4_mtu, dst);
पूर्ण

/* RTT metrics are stored in milliseconds क्रम user ABI, but used as jअगरfies */
अटल अंतरभूत अचिन्हित दीर्घ dst_metric_rtt(स्थिर काष्ठा dst_entry *dst, पूर्णांक metric)
अणु
	वापस msecs_to_jअगरfies(dst_metric(dst, metric));
पूर्ण

अटल अंतरभूत u32
dst_allfrag(स्थिर काष्ठा dst_entry *dst)
अणु
	पूर्णांक ret = dst_feature(dst,  RTAX_FEATURE_ALLFRAG);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
dst_metric_locked(स्थिर काष्ठा dst_entry *dst, पूर्णांक metric)
अणु
	वापस dst_metric(dst, RTAX_LOCK) & (1 << metric);
पूर्ण

अटल अंतरभूत व्योम dst_hold(काष्ठा dst_entry *dst)
अणु
	/*
	 * If your kernel compilation stops here, please check
	 * the placement of __refcnt in काष्ठा dst_entry
	 */
	BUILD_BUG_ON(दुरत्व(काष्ठा dst_entry, __refcnt) & 63);
	WARN_ON(atomic_inc_not_zero(&dst->__refcnt) == 0);
पूर्ण

अटल अंतरभूत व्योम dst_use_noref(काष्ठा dst_entry *dst, अचिन्हित दीर्घ समय)
अणु
	अगर (unlikely(समय != dst->lastuse)) अणु
		dst->__use++;
		dst->lastuse = समय;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम dst_hold_and_use(काष्ठा dst_entry *dst, अचिन्हित दीर्घ समय)
अणु
	dst_hold(dst);
	dst_use_noref(dst, समय);
पूर्ण

अटल अंतरभूत काष्ठा dst_entry *dst_clone(काष्ठा dst_entry *dst)
अणु
	अगर (dst)
		dst_hold(dst);
	वापस dst;
पूर्ण

व्योम dst_release(काष्ठा dst_entry *dst);

व्योम dst_release_immediate(काष्ठा dst_entry *dst);

अटल अंतरभूत व्योम refdst_drop(अचिन्हित दीर्घ refdst)
अणु
	अगर (!(refdst & SKB_DST_NOREF))
		dst_release((काष्ठा dst_entry *)(refdst & SKB_DST_PTRMASK));
पूर्ण

/**
 * skb_dst_drop - drops skb dst
 * @skb: buffer
 *
 * Drops dst reference count अगर a reference was taken.
 */
अटल अंतरभूत व्योम skb_dst_drop(काष्ठा sk_buff *skb)
अणु
	अगर (skb->_skb_refdst) अणु
		refdst_drop(skb->_skb_refdst);
		skb->_skb_refdst = 0UL;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __skb_dst_copy(काष्ठा sk_buff *nskb, अचिन्हित दीर्घ refdst)
अणु
	nskb->_skb_refdst = refdst;
	अगर (!(nskb->_skb_refdst & SKB_DST_NOREF))
		dst_clone(skb_dst(nskb));
पूर्ण

अटल अंतरभूत व्योम skb_dst_copy(काष्ठा sk_buff *nskb, स्थिर काष्ठा sk_buff *oskb)
अणु
	__skb_dst_copy(nskb, oskb->_skb_refdst);
पूर्ण

/**
 * dst_hold_safe - Take a reference on a dst अगर possible
 * @dst: poपूर्णांकer to dst entry
 *
 * This helper वापसs false अगर it could not safely
 * take a reference on a dst.
 */
अटल अंतरभूत bool dst_hold_safe(काष्ठा dst_entry *dst)
अणु
	वापस atomic_inc_not_zero(&dst->__refcnt);
पूर्ण

/**
 * skb_dst_क्रमce - makes sure skb dst is refcounted
 * @skb: buffer
 *
 * If dst is not yet refcounted and not destroyed, grab a ref on it.
 * Returns true अगर dst is refcounted.
 */
अटल अंतरभूत bool skb_dst_क्रमce(काष्ठा sk_buff *skb)
अणु
	अगर (skb_dst_is_noref(skb)) अणु
		काष्ठा dst_entry *dst = skb_dst(skb);

		WARN_ON(!rcu_पढ़ो_lock_held());
		अगर (!dst_hold_safe(dst))
			dst = शून्य;

		skb->_skb_refdst = (अचिन्हित दीर्घ)dst;
	पूर्ण

	वापस skb->_skb_refdst != 0UL;
पूर्ण


/**
 *	__skb_tunnel_rx - prepare skb क्रम rx reinsert
 *	@skb: buffer
 *	@dev: tunnel device
 *	@net: netns क्रम packet i/o
 *
 *	After decapsulation, packet is going to re-enter (netअगर_rx()) our stack,
 *	so make some cleanups. (no accounting करोne)
 */
अटल अंतरभूत व्योम __skb_tunnel_rx(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				   काष्ठा net *net)
अणु
	skb->dev = dev;

	/*
	 * Clear hash so that we can recalulate the hash क्रम the
	 * encapsulated packet, unless we have alपढ़ोy determine the hash
	 * over the L4 4-tuple.
	 */
	skb_clear_hash_अगर_not_l4(skb);
	skb_set_queue_mapping(skb, 0);
	skb_scrub_packet(skb, !net_eq(net, dev_net(dev)));
पूर्ण

/**
 *	skb_tunnel_rx - prepare skb क्रम rx reinsert
 *	@skb: buffer
 *	@dev: tunnel device
 *	@net: netns क्रम packet i/o
 *
 *	After decapsulation, packet is going to re-enter (netअगर_rx()) our stack,
 *	so make some cleanups, and perक्रमm accounting.
 *	Note: this accounting is not SMP safe.
 */
अटल अंतरभूत व्योम skb_tunnel_rx(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				 काष्ठा net *net)
अणु
	/* TODO : stats should be SMP safe */
	dev->stats.rx_packets++;
	dev->stats.rx_bytes += skb->len;
	__skb_tunnel_rx(skb, dev, net);
पूर्ण

अटल अंतरभूत u32 dst_tclassid(स्थिर काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	स्थिर काष्ठा dst_entry *dst;

	dst = skb_dst(skb);
	अगर (dst)
		वापस dst->tclassid;
#पूर्ण_अगर
	वापस 0;
पूर्ण

पूर्णांक dst_discard_out(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);
अटल अंतरभूत पूर्णांक dst_discard(काष्ठा sk_buff *skb)
अणु
	वापस dst_discard_out(&init_net, skb->sk, skb);
पूर्ण
व्योम *dst_alloc(काष्ठा dst_ops *ops, काष्ठा net_device *dev, पूर्णांक initial_ref,
		पूर्णांक initial_obsolete, अचिन्हित लघु flags);
व्योम dst_init(काष्ठा dst_entry *dst, काष्ठा dst_ops *ops,
	      काष्ठा net_device *dev, पूर्णांक initial_ref, पूर्णांक initial_obsolete,
	      अचिन्हित लघु flags);
काष्ठा dst_entry *dst_destroy(काष्ठा dst_entry *dst);
व्योम dst_dev_put(काष्ठा dst_entry *dst);

अटल अंतरभूत व्योम dst_confirm(काष्ठा dst_entry *dst)
अणु
पूर्ण

अटल अंतरभूत काष्ठा neighbour *dst_neigh_lookup(स्थिर काष्ठा dst_entry *dst, स्थिर व्योम *daddr)
अणु
	काष्ठा neighbour *n = dst->ops->neigh_lookup(dst, शून्य, daddr);
	वापस IS_ERR(n) ? शून्य : n;
पूर्ण

अटल अंतरभूत काष्ठा neighbour *dst_neigh_lookup_skb(स्थिर काष्ठा dst_entry *dst,
						     काष्ठा sk_buff *skb)
अणु
	काष्ठा neighbour *n;

	अगर (WARN_ON_ONCE(!dst->ops->neigh_lookup))
		वापस शून्य;

	n = dst->ops->neigh_lookup(dst, skb, शून्य);

	वापस IS_ERR(n) ? शून्य : n;
पूर्ण

अटल अंतरभूत व्योम dst_confirm_neigh(स्थिर काष्ठा dst_entry *dst,
				     स्थिर व्योम *daddr)
अणु
	अगर (dst->ops->confirm_neigh)
		dst->ops->confirm_neigh(dst, daddr);
पूर्ण

अटल अंतरभूत व्योम dst_link_failure(काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	अगर (dst && dst->ops && dst->ops->link_failure)
		dst->ops->link_failure(skb);
पूर्ण

अटल अंतरभूत व्योम dst_set_expires(काष्ठा dst_entry *dst, पूर्णांक समयout)
अणु
	अचिन्हित दीर्घ expires = jअगरfies + समयout;

	अगर (expires == 0)
		expires = 1;

	अगर (dst->expires == 0 || समय_beक्रमe(expires, dst->expires))
		dst->expires = expires;
पूर्ण

INसूचीECT_CALLABLE_DECLARE(पूर्णांक ip6_output(काष्ठा net *, काष्ठा sock *,
					 काष्ठा sk_buff *));
INसूचीECT_CALLABLE_DECLARE(पूर्णांक ip_output(काष्ठा net *, काष्ठा sock *,
					 काष्ठा sk_buff *));
/* Output packet to network from transport.  */
अटल अंतरभूत पूर्णांक dst_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस INसूचीECT_CALL_INET(skb_dst(skb)->output,
				  ip6_output, ip_output,
				  net, sk, skb);
पूर्ण

INसूचीECT_CALLABLE_DECLARE(पूर्णांक ip6_input(काष्ठा sk_buff *));
INसूचीECT_CALLABLE_DECLARE(पूर्णांक ip_local_deliver(काष्ठा sk_buff *));
/* Input packet from network to transport.  */
अटल अंतरभूत पूर्णांक dst_input(काष्ठा sk_buff *skb)
अणु
	वापस INसूचीECT_CALL_INET(skb_dst(skb)->input,
				  ip6_input, ip_local_deliver, skb);
पूर्ण

INसूचीECT_CALLABLE_DECLARE(काष्ठा dst_entry *ip6_dst_check(काष्ठा dst_entry *,
							  u32));
INसूचीECT_CALLABLE_DECLARE(काष्ठा dst_entry *ipv4_dst_check(काष्ठा dst_entry *,
							   u32));
अटल अंतरभूत काष्ठा dst_entry *dst_check(काष्ठा dst_entry *dst, u32 cookie)
अणु
	अगर (dst->obsolete)
		dst = INसूचीECT_CALL_INET(dst->ops->check, ip6_dst_check,
					 ipv4_dst_check, dst, cookie);
	वापस dst;
पूर्ण

/* Flags क्रम xfrm_lookup flags argument. */
क्रमागत अणु
	XFRM_LOOKUP_ICMP = 1 << 0,
	XFRM_LOOKUP_QUEUE = 1 << 1,
	XFRM_LOOKUP_KEEP_DST_REF = 1 << 2,
पूर्ण;

काष्ठा flowi;
#अगर_अघोषित CONFIG_XFRM
अटल अंतरभूत काष्ठा dst_entry *xfrm_lookup(काष्ठा net *net,
					    काष्ठा dst_entry *dst_orig,
					    स्थिर काष्ठा flowi *fl,
					    स्थिर काष्ठा sock *sk,
					    पूर्णांक flags)
अणु
	वापस dst_orig;
पूर्ण

अटल अंतरभूत काष्ठा dst_entry *
xfrm_lookup_with_अगरid(काष्ठा net *net, काष्ठा dst_entry *dst_orig,
		      स्थिर काष्ठा flowi *fl, स्थिर काष्ठा sock *sk,
		      पूर्णांक flags, u32 अगर_id)
अणु
	वापस dst_orig;
पूर्ण

अटल अंतरभूत काष्ठा dst_entry *xfrm_lookup_route(काष्ठा net *net,
						  काष्ठा dst_entry *dst_orig,
						  स्थिर काष्ठा flowi *fl,
						  स्थिर काष्ठा sock *sk,
						  पूर्णांक flags)
अणु
	वापस dst_orig;
पूर्ण

अटल अंतरभूत काष्ठा xfrm_state *dst_xfrm(स्थिर काष्ठा dst_entry *dst)
अणु
	वापस शून्य;
पूर्ण

#अन्यथा
काष्ठा dst_entry *xfrm_lookup(काष्ठा net *net, काष्ठा dst_entry *dst_orig,
			      स्थिर काष्ठा flowi *fl, स्थिर काष्ठा sock *sk,
			      पूर्णांक flags);

काष्ठा dst_entry *xfrm_lookup_with_अगरid(काष्ठा net *net,
					काष्ठा dst_entry *dst_orig,
					स्थिर काष्ठा flowi *fl,
					स्थिर काष्ठा sock *sk, पूर्णांक flags,
					u32 अगर_id);

काष्ठा dst_entry *xfrm_lookup_route(काष्ठा net *net, काष्ठा dst_entry *dst_orig,
				    स्थिर काष्ठा flowi *fl, स्थिर काष्ठा sock *sk,
				    पूर्णांक flags);

/* skb attached with this dst needs transक्रमmation अगर dst->xfrm is valid */
अटल अंतरभूत काष्ठा xfrm_state *dst_xfrm(स्थिर काष्ठा dst_entry *dst)
अणु
	वापस dst->xfrm;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम skb_dst_update_pmtu(काष्ठा sk_buff *skb, u32 mtu)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);

	अगर (dst && dst->ops->update_pmtu)
		dst->ops->update_pmtu(dst, शून्य, skb, mtu, true);
पूर्ण

/* update dst pmtu but not करो neighbor confirm */
अटल अंतरभूत व्योम skb_dst_update_pmtu_no_confirm(काष्ठा sk_buff *skb, u32 mtu)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);

	अगर (dst && dst->ops->update_pmtu)
		dst->ops->update_pmtu(dst, शून्य, skb, mtu, false);
पूर्ण

काष्ठा dst_entry *dst_blackhole_check(काष्ठा dst_entry *dst, u32 cookie);
व्योम dst_blackhole_update_pmtu(काष्ठा dst_entry *dst, काष्ठा sock *sk,
			       काष्ठा sk_buff *skb, u32 mtu, bool confirm_neigh);
व्योम dst_blackhole_redirect(काष्ठा dst_entry *dst, काष्ठा sock *sk,
			    काष्ठा sk_buff *skb);
u32 *dst_blackhole_cow_metrics(काष्ठा dst_entry *dst, अचिन्हित दीर्घ old);
काष्ठा neighbour *dst_blackhole_neigh_lookup(स्थिर काष्ठा dst_entry *dst,
					     काष्ठा sk_buff *skb,
					     स्थिर व्योम *daddr);
अचिन्हित पूर्णांक dst_blackhole_mtu(स्थिर काष्ठा dst_entry *dst);

#पूर्ण_अगर /* _NET_DST_H */
