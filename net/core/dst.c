<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * net/core/dst.c	Protocol independent destination cache.
 *
 * Authors:		Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 *
 */

#समावेश <linux/bitops.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <net/net_namespace.h>
#समावेश <linux/sched.h>
#समावेश <linux/prefetch.h>
#समावेश <net/lwtunnel.h>
#समावेश <net/xfrm.h>

#समावेश <net/dst.h>
#समावेश <net/dst_metadata.h>

पूर्णांक dst_discard_out(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dst_discard_out);

स्थिर काष्ठा dst_metrics dst_शेष_metrics = अणु
	/* This initializer is needed to क्रमce linker to place this variable
	 * पूर्णांकo स्थिर section. Otherwise it might end पूर्णांकo bss section.
	 * We really want to aव्योम false sharing on this variable, and catch
	 * any ग_लिखोs on it.
	 */
	.refcnt = REFCOUNT_INIT(1),
पूर्ण;
EXPORT_SYMBOL(dst_शेष_metrics);

व्योम dst_init(काष्ठा dst_entry *dst, काष्ठा dst_ops *ops,
	      काष्ठा net_device *dev, पूर्णांक initial_ref, पूर्णांक initial_obsolete,
	      अचिन्हित लघु flags)
अणु
	dst->dev = dev;
	अगर (dev)
		dev_hold(dev);
	dst->ops = ops;
	dst_init_metrics(dst, dst_शेष_metrics.metrics, true);
	dst->expires = 0UL;
#अगर_घोषित CONFIG_XFRM
	dst->xfrm = शून्य;
#पूर्ण_अगर
	dst->input = dst_discard;
	dst->output = dst_discard_out;
	dst->error = 0;
	dst->obsolete = initial_obsolete;
	dst->header_len = 0;
	dst->trailer_len = 0;
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	dst->tclassid = 0;
#पूर्ण_अगर
	dst->lwtstate = शून्य;
	atomic_set(&dst->__refcnt, initial_ref);
	dst->__use = 0;
	dst->lastuse = jअगरfies;
	dst->flags = flags;
	अगर (!(flags & DST_NOCOUNT))
		dst_entries_add(ops, 1);
पूर्ण
EXPORT_SYMBOL(dst_init);

व्योम *dst_alloc(काष्ठा dst_ops *ops, काष्ठा net_device *dev,
		पूर्णांक initial_ref, पूर्णांक initial_obsolete, अचिन्हित लघु flags)
अणु
	काष्ठा dst_entry *dst;

	अगर (ops->gc &&
	    !(flags & DST_NOCOUNT) &&
	    dst_entries_get_fast(ops) > ops->gc_thresh) अणु
		अगर (ops->gc(ops)) अणु
			pr_notice_ratelimited("Route cache is full: consider increasing sysctl net.ipv6.route.max_size.\n");
			वापस शून्य;
		पूर्ण
	पूर्ण

	dst = kmem_cache_alloc(ops->kmem_cachep, GFP_ATOMIC);
	अगर (!dst)
		वापस शून्य;

	dst_init(dst, ops, dev, initial_ref, initial_obsolete, flags);

	वापस dst;
पूर्ण
EXPORT_SYMBOL(dst_alloc);

काष्ठा dst_entry *dst_destroy(काष्ठा dst_entry * dst)
अणु
	काष्ठा dst_entry *child = शून्य;

	smp_rmb();

#अगर_घोषित CONFIG_XFRM
	अगर (dst->xfrm) अणु
		काष्ठा xfrm_dst *xdst = (काष्ठा xfrm_dst *) dst;

		child = xdst->child;
	पूर्ण
#पूर्ण_अगर
	अगर (!(dst->flags & DST_NOCOUNT))
		dst_entries_add(dst->ops, -1);

	अगर (dst->ops->destroy)
		dst->ops->destroy(dst);
	अगर (dst->dev)
		dev_put(dst->dev);

	lwtstate_put(dst->lwtstate);

	अगर (dst->flags & DST_METADATA)
		metadata_dst_मुक्त((काष्ठा metadata_dst *)dst);
	अन्यथा
		kmem_cache_मुक्त(dst->ops->kmem_cachep, dst);

	dst = child;
	अगर (dst)
		dst_release_immediate(dst);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(dst_destroy);

अटल व्योम dst_destroy_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा dst_entry *dst = container_of(head, काष्ठा dst_entry, rcu_head);

	dst = dst_destroy(dst);
पूर्ण

/* Operations to mark dst as DEAD and clean up the net device referenced
 * by dst:
 * 1. put the dst under blackhole पूर्णांकerface and discard all tx/rx packets
 *    on this route.
 * 2. release the net_device
 * This function should be called when removing routes from the fib tree
 * in preparation क्रम a NETDEV_DOWN/NETDEV_UNREGISTER event and also to
 * make the next dst_ops->check() fail.
 */
व्योम dst_dev_put(काष्ठा dst_entry *dst)
अणु
	काष्ठा net_device *dev = dst->dev;

	dst->obsolete = DST_OBSOLETE_DEAD;
	अगर (dst->ops->अगरकरोwn)
		dst->ops->अगरकरोwn(dst, dev, true);
	dst->input = dst_discard;
	dst->output = dst_discard_out;
	dst->dev = blackhole_netdev;
	dev_hold(dst->dev);
	dev_put(dev);
पूर्ण
EXPORT_SYMBOL(dst_dev_put);

व्योम dst_release(काष्ठा dst_entry *dst)
अणु
	अगर (dst) अणु
		पूर्णांक newrefcnt;

		newrefcnt = atomic_dec_वापस(&dst->__refcnt);
		अगर (WARN_ONCE(newrefcnt < 0, "dst_release underflow"))
			net_warn_ratelimited("%s: dst:%p refcnt:%d\n",
					     __func__, dst, newrefcnt);
		अगर (!newrefcnt)
			call_rcu(&dst->rcu_head, dst_destroy_rcu);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(dst_release);

व्योम dst_release_immediate(काष्ठा dst_entry *dst)
अणु
	अगर (dst) अणु
		पूर्णांक newrefcnt;

		newrefcnt = atomic_dec_वापस(&dst->__refcnt);
		अगर (WARN_ONCE(newrefcnt < 0, "dst_release_immediate underflow"))
			net_warn_ratelimited("%s: dst:%p refcnt:%d\n",
					     __func__, dst, newrefcnt);
		अगर (!newrefcnt)
			dst_destroy(dst);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(dst_release_immediate);

u32 *dst_cow_metrics_generic(काष्ठा dst_entry *dst, अचिन्हित दीर्घ old)
अणु
	काष्ठा dst_metrics *p = kदो_स्मृति(माप(*p), GFP_ATOMIC);

	अगर (p) अणु
		काष्ठा dst_metrics *old_p = (काष्ठा dst_metrics *)__DST_METRICS_PTR(old);
		अचिन्हित दीर्घ prev, new;

		refcount_set(&p->refcnt, 1);
		स_नकल(p->metrics, old_p->metrics, माप(p->metrics));

		new = (अचिन्हित दीर्घ) p;
		prev = cmpxchg(&dst->_metrics, old, new);

		अगर (prev != old) अणु
			kमुक्त(p);
			p = (काष्ठा dst_metrics *)__DST_METRICS_PTR(prev);
			अगर (prev & DST_METRICS_READ_ONLY)
				p = शून्य;
		पूर्ण अन्यथा अगर (prev & DST_METRICS_REFCOUNTED) अणु
			अगर (refcount_dec_and_test(&old_p->refcnt))
				kमुक्त(old_p);
		पूर्ण
	पूर्ण
	BUILD_BUG_ON(दुरत्व(काष्ठा dst_metrics, metrics) != 0);
	वापस (u32 *)p;
पूर्ण
EXPORT_SYMBOL(dst_cow_metrics_generic);

/* Caller निश्चितs that dst_metrics_पढ़ो_only(dst) is false.  */
व्योम __dst_destroy_metrics_generic(काष्ठा dst_entry *dst, अचिन्हित दीर्घ old)
अणु
	अचिन्हित दीर्घ prev, new;

	new = ((अचिन्हित दीर्घ) &dst_शेष_metrics) | DST_METRICS_READ_ONLY;
	prev = cmpxchg(&dst->_metrics, old, new);
	अगर (prev == old)
		kमुक्त(__DST_METRICS_PTR(old));
पूर्ण
EXPORT_SYMBOL(__dst_destroy_metrics_generic);

काष्ठा dst_entry *dst_blackhole_check(काष्ठा dst_entry *dst, u32 cookie)
अणु
	वापस शून्य;
पूर्ण

u32 *dst_blackhole_cow_metrics(काष्ठा dst_entry *dst, अचिन्हित दीर्घ old)
अणु
	वापस शून्य;
पूर्ण

काष्ठा neighbour *dst_blackhole_neigh_lookup(स्थिर काष्ठा dst_entry *dst,
					     काष्ठा sk_buff *skb,
					     स्थिर व्योम *daddr)
अणु
	वापस शून्य;
पूर्ण

व्योम dst_blackhole_update_pmtu(काष्ठा dst_entry *dst, काष्ठा sock *sk,
			       काष्ठा sk_buff *skb, u32 mtu,
			       bool confirm_neigh)
अणु
पूर्ण
EXPORT_SYMBOL_GPL(dst_blackhole_update_pmtu);

व्योम dst_blackhole_redirect(काष्ठा dst_entry *dst, काष्ठा sock *sk,
			    काष्ठा sk_buff *skb)
अणु
पूर्ण
EXPORT_SYMBOL_GPL(dst_blackhole_redirect);

अचिन्हित पूर्णांक dst_blackhole_mtu(स्थिर काष्ठा dst_entry *dst)
अणु
	अचिन्हित पूर्णांक mtu = dst_metric_raw(dst, RTAX_MTU);

	वापस mtu ? : dst->dev->mtu;
पूर्ण
EXPORT_SYMBOL_GPL(dst_blackhole_mtu);

अटल काष्ठा dst_ops dst_blackhole_ops = अणु
	.family		= AF_UNSPEC,
	.neigh_lookup	= dst_blackhole_neigh_lookup,
	.check		= dst_blackhole_check,
	.cow_metrics	= dst_blackhole_cow_metrics,
	.update_pmtu	= dst_blackhole_update_pmtu,
	.redirect	= dst_blackhole_redirect,
	.mtu		= dst_blackhole_mtu,
पूर्ण;

अटल व्योम __metadata_dst_init(काष्ठा metadata_dst *md_dst,
				क्रमागत metadata_type type, u8 optslen)
अणु
	काष्ठा dst_entry *dst;

	dst = &md_dst->dst;
	dst_init(dst, &dst_blackhole_ops, शून्य, 1, DST_OBSOLETE_NONE,
		 DST_METADATA | DST_NOCOUNT);
	स_रखो(dst + 1, 0, माप(*md_dst) + optslen - माप(*dst));
	md_dst->type = type;
पूर्ण

काष्ठा metadata_dst *metadata_dst_alloc(u8 optslen, क्रमागत metadata_type type,
					gfp_t flags)
अणु
	काष्ठा metadata_dst *md_dst;

	md_dst = kदो_स्मृति(माप(*md_dst) + optslen, flags);
	अगर (!md_dst)
		वापस शून्य;

	__metadata_dst_init(md_dst, type, optslen);

	वापस md_dst;
पूर्ण
EXPORT_SYMBOL_GPL(metadata_dst_alloc);

व्योम metadata_dst_मुक्त(काष्ठा metadata_dst *md_dst)
अणु
#अगर_घोषित CONFIG_DST_CACHE
	अगर (md_dst->type == METADATA_IP_TUNNEL)
		dst_cache_destroy(&md_dst->u.tun_info.dst_cache);
#पूर्ण_अगर
	kमुक्त(md_dst);
पूर्ण
EXPORT_SYMBOL_GPL(metadata_dst_मुक्त);

काष्ठा metadata_dst __percpu *
metadata_dst_alloc_percpu(u8 optslen, क्रमागत metadata_type type, gfp_t flags)
अणु
	पूर्णांक cpu;
	काष्ठा metadata_dst __percpu *md_dst;

	md_dst = __alloc_percpu_gfp(माप(काष्ठा metadata_dst) + optslen,
				    __alignof__(काष्ठा metadata_dst), flags);
	अगर (!md_dst)
		वापस शून्य;

	क्रम_each_possible_cpu(cpu)
		__metadata_dst_init(per_cpu_ptr(md_dst, cpu), type, optslen);

	वापस md_dst;
पूर्ण
EXPORT_SYMBOL_GPL(metadata_dst_alloc_percpu);

व्योम metadata_dst_मुक्त_percpu(काष्ठा metadata_dst __percpu *md_dst)
अणु
#अगर_घोषित CONFIG_DST_CACHE
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा metadata_dst *one_md_dst = per_cpu_ptr(md_dst, cpu);

		अगर (one_md_dst->type == METADATA_IP_TUNNEL)
			dst_cache_destroy(&one_md_dst->u.tun_info.dst_cache);
	पूर्ण
#पूर्ण_अगर
	मुक्त_percpu(md_dst);
पूर्ण
EXPORT_SYMBOL_GPL(metadata_dst_मुक्त_percpu);
