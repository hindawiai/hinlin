<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Generic TIME_WAIT sockets functions
 *
 *		From code orinally in TCP
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <net/inet_hashtables.h>
#समावेश <net/inet_समयरुको_sock.h>
#समावेश <net/ip.h>


/**
 *	inet_twsk_bind_unhash - unhash a समयरुको socket from bind hash
 *	@tw: समयरुको socket
 *	@hashinfo: hashinfo poपूर्णांकer
 *
 *	unhash a समयरुको socket from bind hash, अगर hashed.
 *	bind hash lock must be held by caller.
 *	Returns 1 अगर caller should call inet_twsk_put() after lock release.
 */
व्योम inet_twsk_bind_unhash(काष्ठा inet_समयरुको_sock *tw,
			  काष्ठा inet_hashinfo *hashinfo)
अणु
	काष्ठा inet_bind_bucket *tb = tw->tw_tb;

	अगर (!tb)
		वापस;

	__hlist_del(&tw->tw_bind_node);
	tw->tw_tb = शून्य;
	inet_bind_bucket_destroy(hashinfo->bind_bucket_cachep, tb);
	__sock_put((काष्ठा sock *)tw);
पूर्ण

/* Must be called with locally disabled BHs. */
अटल व्योम inet_twsk_समाप्त(काष्ठा inet_समयरुको_sock *tw)
अणु
	काष्ठा inet_hashinfo *hashinfo = tw->tw_dr->hashinfo;
	spinlock_t *lock = inet_ehash_lockp(hashinfo, tw->tw_hash);
	काष्ठा inet_bind_hashbucket *bhead;

	spin_lock(lock);
	sk_nulls_del_node_init_rcu((काष्ठा sock *)tw);
	spin_unlock(lock);

	/* Disassociate with bind bucket. */
	bhead = &hashinfo->bhash[inet_bhashfn(twsk_net(tw), tw->tw_num,
			hashinfo->bhash_size)];

	spin_lock(&bhead->lock);
	inet_twsk_bind_unhash(tw, hashinfo);
	spin_unlock(&bhead->lock);

	atomic_dec(&tw->tw_dr->tw_count);
	inet_twsk_put(tw);
पूर्ण

व्योम inet_twsk_मुक्त(काष्ठा inet_समयरुको_sock *tw)
अणु
	काष्ठा module *owner = tw->tw_prot->owner;
	twsk_deकाष्ठाor((काष्ठा sock *)tw);
#अगर_घोषित SOCK_REFCNT_DEBUG
	pr_debug("%s timewait_sock %p released\n", tw->tw_prot->name, tw);
#पूर्ण_अगर
	kmem_cache_मुक्त(tw->tw_prot->twsk_prot->twsk_slab, tw);
	module_put(owner);
पूर्ण

व्योम inet_twsk_put(काष्ठा inet_समयरुको_sock *tw)
अणु
	अगर (refcount_dec_and_test(&tw->tw_refcnt))
		inet_twsk_मुक्त(tw);
पूर्ण
EXPORT_SYMBOL_GPL(inet_twsk_put);

अटल व्योम inet_twsk_add_node_rcu(काष्ठा inet_समयरुको_sock *tw,
				   काष्ठा hlist_nulls_head *list)
अणु
	hlist_nulls_add_head_rcu(&tw->tw_node, list);
पूर्ण

अटल व्योम inet_twsk_add_bind_node(काष्ठा inet_समयरुको_sock *tw,
				    काष्ठा hlist_head *list)
अणु
	hlist_add_head(&tw->tw_bind_node, list);
पूर्ण

/*
 * Enter the समय रुको state. This is called with locally disabled BH.
 * Essentially we whip up a समयरुको bucket, copy the relevant info पूर्णांकo it
 * from the SK, and mess with hash chains and list linkage.
 */
व्योम inet_twsk_hashdance(काष्ठा inet_समयरुको_sock *tw, काष्ठा sock *sk,
			   काष्ठा inet_hashinfo *hashinfo)
अणु
	स्थिर काष्ठा inet_sock *inet = inet_sk(sk);
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा inet_ehash_bucket *ehead = inet_ehash_bucket(hashinfo, sk->sk_hash);
	spinlock_t *lock = inet_ehash_lockp(hashinfo, sk->sk_hash);
	काष्ठा inet_bind_hashbucket *bhead;
	/* Step 1: Put TW पूर्णांकo bind hash. Original socket stays there too.
	   Note, that any socket with inet->num != 0 MUST be bound in
	   binding cache, even अगर it is बंदd.
	 */
	bhead = &hashinfo->bhash[inet_bhashfn(twsk_net(tw), inet->inet_num,
			hashinfo->bhash_size)];
	spin_lock(&bhead->lock);
	tw->tw_tb = icsk->icsk_bind_hash;
	WARN_ON(!icsk->icsk_bind_hash);
	inet_twsk_add_bind_node(tw, &tw->tw_tb->owners);
	spin_unlock(&bhead->lock);

	spin_lock(lock);

	inet_twsk_add_node_rcu(tw, &ehead->chain);

	/* Step 3: Remove SK from hash chain */
	अगर (__sk_nulls_del_node_init_rcu(sk))
		sock_prot_inuse_add(sock_net(sk), sk->sk_prot, -1);

	spin_unlock(lock);

	/* tw_refcnt is set to 3 because we have :
	 * - one reference क्रम bhash chain.
	 * - one reference क्रम ehash chain.
	 * - one reference क्रम समयr.
	 * We can use atomic_set() because prior spin_lock()/spin_unlock()
	 * committed पूर्णांकo memory all tw fields.
	 * Also note that after this poपूर्णांक, we lost our implicit reference
	 * so we are not allowed to use tw anymore.
	 */
	refcount_set(&tw->tw_refcnt, 3);
पूर्ण
EXPORT_SYMBOL_GPL(inet_twsk_hashdance);

अटल व्योम tw_समयr_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा inet_समयरुको_sock *tw = from_समयr(tw, t, tw_समयr);

	अगर (tw->tw_समाप्त)
		__NET_INC_STATS(twsk_net(tw), LINUX_MIB_TIMEWAITKILLED);
	अन्यथा
		__NET_INC_STATS(twsk_net(tw), LINUX_MIB_TIMEWAITED);
	inet_twsk_समाप्त(tw);
पूर्ण

काष्ठा inet_समयरुको_sock *inet_twsk_alloc(स्थिर काष्ठा sock *sk,
					   काष्ठा inet_समयरुको_death_row *dr,
					   स्थिर पूर्णांक state)
अणु
	काष्ठा inet_समयरुको_sock *tw;

	अगर (atomic_पढ़ो(&dr->tw_count) >= dr->sysctl_max_tw_buckets)
		वापस शून्य;

	tw = kmem_cache_alloc(sk->sk_prot_creator->twsk_prot->twsk_slab,
			      GFP_ATOMIC);
	अगर (tw) अणु
		स्थिर काष्ठा inet_sock *inet = inet_sk(sk);

		tw->tw_dr	    = dr;
		/* Give us an identity. */
		tw->tw_daddr	    = inet->inet_daddr;
		tw->tw_rcv_saddr    = inet->inet_rcv_saddr;
		tw->tw_bound_dev_अगर = sk->sk_bound_dev_अगर;
		tw->tw_tos	    = inet->tos;
		tw->tw_num	    = inet->inet_num;
		tw->tw_state	    = TCP_TIME_WAIT;
		tw->tw_substate	    = state;
		tw->tw_sport	    = inet->inet_sport;
		tw->tw_dport	    = inet->inet_dport;
		tw->tw_family	    = sk->sk_family;
		tw->tw_reuse	    = sk->sk_reuse;
		tw->tw_reuseport    = sk->sk_reuseport;
		tw->tw_hash	    = sk->sk_hash;
		tw->tw_ipv6only	    = 0;
		tw->tw_transparent  = inet->transparent;
		tw->tw_prot	    = sk->sk_prot_creator;
		atomic64_set(&tw->tw_cookie, atomic64_पढ़ो(&sk->sk_cookie));
		twsk_net_set(tw, sock_net(sk));
		समयr_setup(&tw->tw_समयr, tw_समयr_handler, TIMER_PINNED);
		/*
		 * Because we use RCU lookups, we should not set tw_refcnt
		 * to a non null value beक्रमe everything is setup क्रम this
		 * समयरुको socket.
		 */
		refcount_set(&tw->tw_refcnt, 0);

		__module_get(tw->tw_prot->owner);
	पूर्ण

	वापस tw;
पूर्ण
EXPORT_SYMBOL_GPL(inet_twsk_alloc);

/* These are always called from BH context.  See callers in
 * tcp_input.c to verअगरy this.
 */

/* This is क्रम handling early-समाप्तs of TIME_WAIT sockets.
 * Warning : consume reference.
 * Caller should not access tw anymore.
 */
व्योम inet_twsk_deschedule_put(काष्ठा inet_समयरुको_sock *tw)
अणु
	अगर (del_समयr_sync(&tw->tw_समयr))
		inet_twsk_समाप्त(tw);
	inet_twsk_put(tw);
पूर्ण
EXPORT_SYMBOL(inet_twsk_deschedule_put);

व्योम __inet_twsk_schedule(काष्ठा inet_समयरुको_sock *tw, पूर्णांक समयo, bool rearm)
अणु
	/* समयout := RTO * 3.5
	 *
	 * 3.5 = 1+2+0.5 to रुको क्रम two retransmits.
	 *
	 * RATIONALE: अगर FIN arrived and we entered TIME-WAIT state,
	 * our ACK acking that FIN can be lost. If N subsequent retransmitted
	 * FINs (or previous seqments) are lost (probability of such event
	 * is p^(N+1), where p is probability to lose single packet and
	 * समय to detect the loss is about RTO*(2^N - 1) with exponential
	 * backoff). Normal समयरुको length is calculated so, that we
	 * रुकोed at least क्रम one retransmitted FIN (maximal RTO is 120sec).
	 * [ BTW Linux. following BSD, violates this requirement रुकोing
	 *   only क्रम 60sec, we should रुको at least क्रम 240 secs.
	 *   Well, 240 consumes too much of resources 8)
	 * ]
	 * This पूर्णांकerval is not reduced to catch old duplicate and
	 * responces to our wandering segments living क्रम two MSLs.
	 * However, अगर we use PAWS to detect
	 * old duplicates, we can reduce the पूर्णांकerval to bounds required
	 * by RTO, rather than MSL. So, अगर peer understands PAWS, we
	 * समाप्त tw bucket after 3.5*RTO (it is important that this number
	 * is greater than TS tick!) and detect old duplicates with help
	 * of PAWS.
	 */

	tw->tw_समाप्त = समयo <= 4*HZ;
	अगर (!rearm) अणु
		BUG_ON(mod_समयr(&tw->tw_समयr, jअगरfies + समयo));
		atomic_inc(&tw->tw_dr->tw_count);
	पूर्ण अन्यथा अणु
		mod_समयr_pending(&tw->tw_समयr, jअगरfies + समयo);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(__inet_twsk_schedule);

व्योम inet_twsk_purge(काष्ठा inet_hashinfo *hashinfo, पूर्णांक family)
अणु
	काष्ठा inet_समयरुको_sock *tw;
	काष्ठा sock *sk;
	काष्ठा hlist_nulls_node *node;
	अचिन्हित पूर्णांक slot;

	क्रम (slot = 0; slot <= hashinfo->ehash_mask; slot++) अणु
		काष्ठा inet_ehash_bucket *head = &hashinfo->ehash[slot];
restart_rcu:
		cond_resched();
		rcu_पढ़ो_lock();
restart:
		sk_nulls_क्रम_each_rcu(sk, node, &head->chain) अणु
			अगर (sk->sk_state != TCP_TIME_WAIT)
				जारी;
			tw = inet_twsk(sk);
			अगर ((tw->tw_family != family) ||
				refcount_पढ़ो(&twsk_net(tw)->ns.count))
				जारी;

			अगर (unlikely(!refcount_inc_not_zero(&tw->tw_refcnt)))
				जारी;

			अगर (unlikely((tw->tw_family != family) ||
				     refcount_पढ़ो(&twsk_net(tw)->ns.count))) अणु
				inet_twsk_put(tw);
				जाओ restart;
			पूर्ण

			rcu_पढ़ो_unlock();
			local_bh_disable();
			inet_twsk_deschedule_put(tw);
			local_bh_enable();
			जाओ restart_rcu;
		पूर्ण
		/* If the nulls value we got at the end of this lookup is
		 * not the expected one, we must restart lookup.
		 * We probably met an item that was moved to another chain.
		 */
		अगर (get_nulls_value(node) != slot)
			जाओ restart;
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(inet_twsk_purge);
