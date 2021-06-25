<शैली गुरु>
/*
 *		INETPEER - A storage क्रम permanent inक्रमmation about peers
 *
 *  This source is covered by the GNU GPL, the same as all kernel sources.
 *
 *  Authors:	Andrey V. Savochkin <saw@msu.ru>
 */

#समावेश <linux/cache.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/समयr.h>
#समावेश <linux/समय.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/net.h>
#समावेश <linux/workqueue.h>
#समावेश <net/ip.h>
#समावेश <net/inetpeer.h>
#समावेश <net/secure_seq.h>

/*
 *  Theory of operations.
 *  We keep one entry क्रम each peer IP address.  The nodes contains दीर्घ-living
 *  inक्रमmation about the peer which करोesn't depend on routes.
 *
 *  Nodes are हटाओd only when reference counter goes to 0.
 *  When it's happened the node may be हटाओd when a sufficient amount of
 *  समय has been passed since its last use.  The less-recently-used entry can
 *  also be हटाओd अगर the pool is overloaded i.e. अगर the total amount of
 *  entries is greater-or-equal than the threshold.
 *
 *  Node pool is organised as an RB tree.
 *  Such an implementation has been chosen not just क्रम fun.  It's a way to
 *  prevent easy and efficient DoS attacks by creating hash collisions.  A huge
 *  amount of दीर्घ living nodes in a single hash slot would signअगरicantly delay
 *  lookups perक्रमmed with disabled BHs.
 *
 *  Serialisation issues.
 *  1.  Nodes may appear in the tree only with the pool lock held.
 *  2.  Nodes may disappear from the tree only with the pool lock held
 *      AND reference count being 0.
 *  3.  Global variable peer_total is modअगरied under the pool lock.
 *  4.  काष्ठा inet_peer fields modअगरication:
 *		rb_node: pool lock
 *		refcnt: atomically against modअगरications on other CPU;
 *		   usually under some other lock to prevent node disappearing
 *		daddr: unchangeable
 */

अटल काष्ठा kmem_cache *peer_cachep __ro_after_init;

व्योम inet_peer_base_init(काष्ठा inet_peer_base *bp)
अणु
	bp->rb_root = RB_ROOT;
	seqlock_init(&bp->lock);
	bp->total = 0;
पूर्ण
EXPORT_SYMBOL_GPL(inet_peer_base_init);

#घोषणा PEER_MAX_GC 32

/* Exported क्रम sysctl_net_ipv4.  */
पूर्णांक inet_peer_threshold __पढ़ो_mostly;	/* start to throw entries more
					 * aggressively at this stage */
पूर्णांक inet_peer_mपूर्णांकtl __पढ़ो_mostly = 120 * HZ;	/* TTL under high load: 120 sec */
पूर्णांक inet_peer_maxttl __पढ़ो_mostly = 10 * 60 * HZ;	/* usual समय to live: 10 min */

/* Called from ip_output.c:ip_init  */
व्योम __init inet_initpeers(व्योम)
अणु
	u64 nr_entries;

	 /* 1% of physical memory */
	nr_entries = भाग64_ul((u64)totalram_pages() << PAGE_SHIFT,
			      100 * L1_CACHE_ALIGN(माप(काष्ठा inet_peer)));

	inet_peer_threshold = clamp_val(nr_entries, 4096, 65536 + 128);

	peer_cachep = kmem_cache_create("inet_peer_cache",
			माप(काष्ठा inet_peer),
			0, SLAB_HWCACHE_ALIGN | SLAB_PANIC,
			शून्य);
पूर्ण

/* Called with rcu_पढ़ो_lock() or base->lock held */
अटल काष्ठा inet_peer *lookup(स्थिर काष्ठा inetpeer_addr *daddr,
				काष्ठा inet_peer_base *base,
				अचिन्हित पूर्णांक seq,
				काष्ठा inet_peer *gc_stack[],
				अचिन्हित पूर्णांक *gc_cnt,
				काष्ठा rb_node **parent_p,
				काष्ठा rb_node ***pp_p)
अणु
	काष्ठा rb_node **pp, *parent, *next;
	काष्ठा inet_peer *p;

	pp = &base->rb_root.rb_node;
	parent = शून्य;
	जबतक (1) अणु
		पूर्णांक cmp;

		next = rcu_dereference_raw(*pp);
		अगर (!next)
			अवरोध;
		parent = next;
		p = rb_entry(parent, काष्ठा inet_peer, rb_node);
		cmp = inetpeer_addr_cmp(daddr, &p->daddr);
		अगर (cmp == 0) अणु
			अगर (!refcount_inc_not_zero(&p->refcnt))
				अवरोध;
			वापस p;
		पूर्ण
		अगर (gc_stack) अणु
			अगर (*gc_cnt < PEER_MAX_GC)
				gc_stack[(*gc_cnt)++] = p;
		पूर्ण अन्यथा अगर (unlikely(पढ़ो_seqretry(&base->lock, seq))) अणु
			अवरोध;
		पूर्ण
		अगर (cmp == -1)
			pp = &next->rb_left;
		अन्यथा
			pp = &next->rb_right;
	पूर्ण
	*parent_p = parent;
	*pp_p = pp;
	वापस शून्य;
पूर्ण

अटल व्योम inetpeer_मुक्त_rcu(काष्ठा rcu_head *head)
अणु
	kmem_cache_मुक्त(peer_cachep, container_of(head, काष्ठा inet_peer, rcu));
पूर्ण

/* perक्रमm garbage collect on all items stacked during a lookup */
अटल व्योम inet_peer_gc(काष्ठा inet_peer_base *base,
			 काष्ठा inet_peer *gc_stack[],
			 अचिन्हित पूर्णांक gc_cnt)
अणु
	काष्ठा inet_peer *p;
	__u32 delta, ttl;
	पूर्णांक i;

	अगर (base->total >= inet_peer_threshold)
		ttl = 0; /* be aggressive */
	अन्यथा
		ttl = inet_peer_maxttl
				- (inet_peer_maxttl - inet_peer_mपूर्णांकtl) / HZ *
					base->total / inet_peer_threshold * HZ;
	क्रम (i = 0; i < gc_cnt; i++) अणु
		p = gc_stack[i];

		/* The READ_ONCE() pairs with the WRITE_ONCE()
		 * in inet_putpeer()
		 */
		delta = (__u32)jअगरfies - READ_ONCE(p->dसमय);

		अगर (delta < ttl || !refcount_dec_अगर_one(&p->refcnt))
			gc_stack[i] = शून्य;
	पूर्ण
	क्रम (i = 0; i < gc_cnt; i++) अणु
		p = gc_stack[i];
		अगर (p) अणु
			rb_erase(&p->rb_node, &base->rb_root);
			base->total--;
			call_rcu(&p->rcu, inetpeer_मुक्त_rcu);
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा inet_peer *inet_getpeer(काष्ठा inet_peer_base *base,
			       स्थिर काष्ठा inetpeer_addr *daddr,
			       पूर्णांक create)
अणु
	काष्ठा inet_peer *p, *gc_stack[PEER_MAX_GC];
	काष्ठा rb_node **pp, *parent;
	अचिन्हित पूर्णांक gc_cnt, seq;
	पूर्णांक invalidated;

	/* Attempt a lockless lookup first.
	 * Because of a concurrent ग_लिखोr, we might not find an existing entry.
	 */
	rcu_पढ़ो_lock();
	seq = पढ़ो_seqbegin(&base->lock);
	p = lookup(daddr, base, seq, शून्य, &gc_cnt, &parent, &pp);
	invalidated = पढ़ो_seqretry(&base->lock, seq);
	rcu_पढ़ो_unlock();

	अगर (p)
		वापस p;

	/* If no ग_लिखोr did a change during our lookup, we can वापस early. */
	अगर (!create && !invalidated)
		वापस शून्य;

	/* retry an exact lookup, taking the lock beक्रमe.
	 * At least, nodes should be hot in our cache.
	 */
	parent = शून्य;
	ग_लिखो_seqlock_bh(&base->lock);

	gc_cnt = 0;
	p = lookup(daddr, base, seq, gc_stack, &gc_cnt, &parent, &pp);
	अगर (!p && create) अणु
		p = kmem_cache_alloc(peer_cachep, GFP_ATOMIC);
		अगर (p) अणु
			p->daddr = *daddr;
			p->dसमय = (__u32)jअगरfies;
			refcount_set(&p->refcnt, 2);
			atomic_set(&p->rid, 0);
			p->metrics[RTAX_LOCK-1] = INETPEER_METRICS_NEW;
			p->rate_tokens = 0;
			p->n_redirects = 0;
			/* 60*HZ is arbitrary, but chosen enough high so that the first
			 * calculation of tokens is at its maximum.
			 */
			p->rate_last = jअगरfies - 60*HZ;

			rb_link_node(&p->rb_node, parent, pp);
			rb_insert_color(&p->rb_node, &base->rb_root);
			base->total++;
		पूर्ण
	पूर्ण
	अगर (gc_cnt)
		inet_peer_gc(base, gc_stack, gc_cnt);
	ग_लिखो_sequnlock_bh(&base->lock);

	वापस p;
पूर्ण
EXPORT_SYMBOL_GPL(inet_getpeer);

व्योम inet_putpeer(काष्ठा inet_peer *p)
अणु
	/* The WRITE_ONCE() pairs with itself (we run lockless)
	 * and the READ_ONCE() in inet_peer_gc()
	 */
	WRITE_ONCE(p->dसमय, (__u32)jअगरfies);

	अगर (refcount_dec_and_test(&p->refcnt))
		call_rcu(&p->rcu, inetpeer_मुक्त_rcu);
पूर्ण
EXPORT_SYMBOL_GPL(inet_putpeer);

/*
 *	Check transmit rate limitation क्रम given message.
 *	The rate inक्रमmation is held in the inet_peer entries now.
 *	This function is generic and could be used क्रम other purposes
 *	too. It uses a Token bucket filter as suggested by Alexey Kuznetsov.
 *
 *	Note that the same inet_peer fields are modअगरied by functions in
 *	route.c too, but these work क्रम packet destinations जबतक xrlim_allow
 *	works क्रम icmp destinations. This means the rate limiting inक्रमmation
 *	क्रम one "ip object" is shared - and these ICMPs are twice limited:
 *	by source and by destination.
 *
 *	RFC 1812: 4.3.2.8 SHOULD be able to limit error message rate
 *			  SHOULD allow setting of rate limits
 *
 * 	Shared between ICMPv4 and ICMPv6.
 */
#घोषणा XRLIM_BURST_FACTOR 6
bool inet_peer_xrlim_allow(काष्ठा inet_peer *peer, पूर्णांक समयout)
अणु
	अचिन्हित दीर्घ now, token;
	bool rc = false;

	अगर (!peer)
		वापस true;

	token = peer->rate_tokens;
	now = jअगरfies;
	token += now - peer->rate_last;
	peer->rate_last = now;
	अगर (token > XRLIM_BURST_FACTOR * समयout)
		token = XRLIM_BURST_FACTOR * समयout;
	अगर (token >= समयout) अणु
		token -= समयout;
		rc = true;
	पूर्ण
	peer->rate_tokens = token;
	वापस rc;
पूर्ण
EXPORT_SYMBOL(inet_peer_xrlim_allow);

व्योम inetpeer_invalidate_tree(काष्ठा inet_peer_base *base)
अणु
	काष्ठा rb_node *p = rb_first(&base->rb_root);

	जबतक (p) अणु
		काष्ठा inet_peer *peer = rb_entry(p, काष्ठा inet_peer, rb_node);

		p = rb_next(p);
		rb_erase(&peer->rb_node, &base->rb_root);
		inet_putpeer(peer);
		cond_resched();
	पूर्ण

	base->total = 0;
पूर्ण
EXPORT_SYMBOL(inetpeer_invalidate_tree);
