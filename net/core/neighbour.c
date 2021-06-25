<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Generic address resolution entity
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>
 *	Alexey Kuznetsov	<kuznet@ms2.inr.ac.ru>
 *
 *	Fixes:
 *	Vitaly E. Lavrov	releasing शून्य neighbor in neigh_add.
 *	Harald Welte		Add neighbour cache statistics like rtstat
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/slab.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/socket.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/proc_fs.h>
#अगर_घोषित CONFIG_SYSCTL
#समावेश <linux/sysctl.h>
#पूर्ण_अगर
#समावेश <linux/बार.h>
#समावेश <net/net_namespace.h>
#समावेश <net/neighbour.h>
#समावेश <net/arp.h>
#समावेश <net/dst.h>
#समावेश <net/sock.h>
#समावेश <net/netevent.h>
#समावेश <net/netlink.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/माला.स>
#समावेश <linux/log2.h>
#समावेश <linux/inetdevice.h>
#समावेश <net/addrconf.h>

#समावेश <trace/events/neigh.h>

#घोषणा NEIGH_DEBUG 1
#घोषणा neigh_dbg(level, fmt, ...)		\
करो अणु						\
	अगर (level <= NEIGH_DEBUG)		\
		pr_debug(fmt, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

#घोषणा PNEIGH_HASHMASK		0xF

अटल व्योम neigh_समयr_handler(काष्ठा समयr_list *t);
अटल व्योम __neigh_notअगरy(काष्ठा neighbour *n, पूर्णांक type, पूर्णांक flags,
			   u32 pid);
अटल व्योम neigh_update_notअगरy(काष्ठा neighbour *neigh, u32 nlmsg_pid);
अटल पूर्णांक pneigh_अगरकरोwn_and_unlock(काष्ठा neigh_table *tbl,
				    काष्ठा net_device *dev);

#अगर_घोषित CONFIG_PROC_FS
अटल स्थिर काष्ठा seq_operations neigh_stat_seq_ops;
#पूर्ण_अगर

/*
   Neighbour hash table buckets are रक्षित with rwlock tbl->lock.

   - All the scans/updates to hash buckets MUST be made under this lock.
   - NOTHING clever should be made under this lock: no callbacks
     to protocol backends, no attempts to send something to network.
     It will result in deadlocks, अगर backend/driver wants to use neighbour
     cache.
   - If the entry requires some non-trivial actions, increase
     its reference count and release table lock.

   Neighbour entries are रक्षित:
   - with reference count.
   - with rwlock neigh->lock

   Reference count prevents deकाष्ठाion.

   neigh->lock मुख्यly serializes ll address data and its validity state.
   However, the same lock is used to protect another entry fields:
    - समयr
    - resolution queue

   Again, nothing clever shall be made under neigh->lock,
   the most complicated procedure, which we allow is dev->hard_header.
   It is supposed, that dev->hard_header is simplistic and करोes
   not make callbacks to neighbour tables.
 */

अटल पूर्णांक neigh_blackhole(काष्ठा neighbour *neigh, काष्ठा sk_buff *skb)
अणु
	kमुक्त_skb(skb);
	वापस -ENETDOWN;
पूर्ण

अटल व्योम neigh_cleanup_and_release(काष्ठा neighbour *neigh)
अणु
	trace_neigh_cleanup_and_release(neigh, 0);
	__neigh_notअगरy(neigh, RTM_DELNEIGH, 0, 0);
	call_netevent_notअगरiers(NETEVENT_NEIGH_UPDATE, neigh);
	neigh_release(neigh);
पूर्ण

/*
 * It is अक्रमom distribution in the पूर्णांकerval (1/2)*base...(3/2)*base.
 * It corresponds to शेष IPv6 settings and is not overridable,
 * because it is really reasonable choice.
 */

अचिन्हित दीर्घ neigh_अक्रम_reach_समय(अचिन्हित दीर्घ base)
अणु
	वापस base ? (pअक्रमom_u32() % base) + (base >> 1) : 0;
पूर्ण
EXPORT_SYMBOL(neigh_अक्रम_reach_समय);

अटल व्योम neigh_mark_dead(काष्ठा neighbour *n)
अणु
	n->dead = 1;
	अगर (!list_empty(&n->gc_list)) अणु
		list_del_init(&n->gc_list);
		atomic_dec(&n->tbl->gc_entries);
	पूर्ण
पूर्ण

अटल व्योम neigh_update_gc_list(काष्ठा neighbour *n)
अणु
	bool on_gc_list, exempt_from_gc;

	ग_लिखो_lock_bh(&n->tbl->lock);
	ग_लिखो_lock(&n->lock);

	अगर (n->dead)
		जाओ out;

	/* हटाओ from the gc list अगर new state is permanent or अगर neighbor
	 * is बाह्यally learned; otherwise entry should be on the gc list
	 */
	exempt_from_gc = n->nud_state & NUD_PERMANENT ||
			 n->flags & NTF_EXT_LEARNED;
	on_gc_list = !list_empty(&n->gc_list);

	अगर (exempt_from_gc && on_gc_list) अणु
		list_del_init(&n->gc_list);
		atomic_dec(&n->tbl->gc_entries);
	पूर्ण अन्यथा अगर (!exempt_from_gc && !on_gc_list) अणु
		/* add entries to the tail; cleaning हटाओs from the front */
		list_add_tail(&n->gc_list, &n->tbl->gc_list);
		atomic_inc(&n->tbl->gc_entries);
	पूर्ण

out:
	ग_लिखो_unlock(&n->lock);
	ग_लिखो_unlock_bh(&n->tbl->lock);
पूर्ण

अटल bool neigh_update_ext_learned(काष्ठा neighbour *neigh, u32 flags,
				     पूर्णांक *notअगरy)
अणु
	bool rc = false;
	u8 ndm_flags;

	अगर (!(flags & NEIGH_UPDATE_F_ADMIN))
		वापस rc;

	ndm_flags = (flags & NEIGH_UPDATE_F_EXT_LEARNED) ? NTF_EXT_LEARNED : 0;
	अगर ((neigh->flags ^ ndm_flags) & NTF_EXT_LEARNED) अणु
		अगर (ndm_flags & NTF_EXT_LEARNED)
			neigh->flags |= NTF_EXT_LEARNED;
		अन्यथा
			neigh->flags &= ~NTF_EXT_LEARNED;
		rc = true;
		*notअगरy = 1;
	पूर्ण

	वापस rc;
पूर्ण

अटल bool neigh_del(काष्ठा neighbour *n, काष्ठा neighbour __rcu **np,
		      काष्ठा neigh_table *tbl)
अणु
	bool retval = false;

	ग_लिखो_lock(&n->lock);
	अगर (refcount_पढ़ो(&n->refcnt) == 1) अणु
		काष्ठा neighbour *neigh;

		neigh = rcu_dereference_रक्षित(n->next,
						  lockdep_is_held(&tbl->lock));
		rcu_assign_poपूर्णांकer(*np, neigh);
		neigh_mark_dead(n);
		retval = true;
	पूर्ण
	ग_लिखो_unlock(&n->lock);
	अगर (retval)
		neigh_cleanup_and_release(n);
	वापस retval;
पूर्ण

bool neigh_हटाओ_one(काष्ठा neighbour *ndel, काष्ठा neigh_table *tbl)
अणु
	काष्ठा neigh_hash_table *nht;
	व्योम *pkey = ndel->primary_key;
	u32 hash_val;
	काष्ठा neighbour *n;
	काष्ठा neighbour __rcu **np;

	nht = rcu_dereference_रक्षित(tbl->nht,
					lockdep_is_held(&tbl->lock));
	hash_val = tbl->hash(pkey, ndel->dev, nht->hash_rnd);
	hash_val = hash_val >> (32 - nht->hash_shअगरt);

	np = &nht->hash_buckets[hash_val];
	जबतक ((n = rcu_dereference_रक्षित(*np,
					      lockdep_is_held(&tbl->lock)))) अणु
		अगर (n == ndel)
			वापस neigh_del(n, np, tbl);
		np = &n->next;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक neigh_क्रमced_gc(काष्ठा neigh_table *tbl)
अणु
	पूर्णांक max_clean = atomic_पढ़ो(&tbl->gc_entries) - tbl->gc_thresh2;
	अचिन्हित दीर्घ tref = jअगरfies - 5 * HZ;
	काष्ठा neighbour *n, *पंचांगp;
	पूर्णांक shrunk = 0;

	NEIGH_CACHE_STAT_INC(tbl, क्रमced_gc_runs);

	ग_लिखो_lock_bh(&tbl->lock);

	list_क्रम_each_entry_safe(n, पंचांगp, &tbl->gc_list, gc_list) अणु
		अगर (refcount_पढ़ो(&n->refcnt) == 1) अणु
			bool हटाओ = false;

			ग_लिखो_lock(&n->lock);
			अगर ((n->nud_state == NUD_FAILED) ||
			    (n->nud_state == NUD_NOARP) ||
			    (tbl->is_multicast &&
			     tbl->is_multicast(n->primary_key)) ||
			    समय_after(tref, n->updated))
				हटाओ = true;
			ग_लिखो_unlock(&n->lock);

			अगर (हटाओ && neigh_हटाओ_one(n, tbl))
				shrunk++;
			अगर (shrunk >= max_clean)
				अवरोध;
		पूर्ण
	पूर्ण

	tbl->last_flush = jअगरfies;

	ग_लिखो_unlock_bh(&tbl->lock);

	वापस shrunk;
पूर्ण

अटल व्योम neigh_add_समयr(काष्ठा neighbour *n, अचिन्हित दीर्घ when)
अणु
	neigh_hold(n);
	अगर (unlikely(mod_समयr(&n->समयr, when))) अणु
		prपूर्णांकk("NEIGH: BUG, double timer add, state is %x\n",
		       n->nud_state);
		dump_stack();
	पूर्ण
पूर्ण

अटल पूर्णांक neigh_del_समयr(काष्ठा neighbour *n)
अणु
	अगर ((n->nud_state & NUD_IN_TIMER) &&
	    del_समयr(&n->समयr)) अणु
		neigh_release(n);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम pneigh_queue_purge(काष्ठा sk_buff_head *list)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_dequeue(list)) != शून्य) अणु
		dev_put(skb->dev);
		kमुक्त_skb(skb);
	पूर्ण
पूर्ण

अटल व्योम neigh_flush_dev(काष्ठा neigh_table *tbl, काष्ठा net_device *dev,
			    bool skip_perm)
अणु
	पूर्णांक i;
	काष्ठा neigh_hash_table *nht;

	nht = rcu_dereference_रक्षित(tbl->nht,
					lockdep_is_held(&tbl->lock));

	क्रम (i = 0; i < (1 << nht->hash_shअगरt); i++) अणु
		काष्ठा neighbour *n;
		काष्ठा neighbour __rcu **np = &nht->hash_buckets[i];

		जबतक ((n = rcu_dereference_रक्षित(*np,
					lockdep_is_held(&tbl->lock))) != शून्य) अणु
			अगर (dev && n->dev != dev) अणु
				np = &n->next;
				जारी;
			पूर्ण
			अगर (skip_perm && n->nud_state & NUD_PERMANENT) अणु
				np = &n->next;
				जारी;
			पूर्ण
			rcu_assign_poपूर्णांकer(*np,
				   rcu_dereference_रक्षित(n->next,
						lockdep_is_held(&tbl->lock)));
			ग_लिखो_lock(&n->lock);
			neigh_del_समयr(n);
			neigh_mark_dead(n);
			अगर (refcount_पढ़ो(&n->refcnt) != 1) अणु
				/* The most unpleasant situation.
				   We must destroy neighbour entry,
				   but someone still uses it.

				   The destroy will be delayed until
				   the last user releases us, but
				   we must समाप्त समयrs etc. and move
				   it to safe state.
				 */
				__skb_queue_purge(&n->arp_queue);
				n->arp_queue_len_bytes = 0;
				n->output = neigh_blackhole;
				अगर (n->nud_state & NUD_VALID)
					n->nud_state = NUD_NOARP;
				अन्यथा
					n->nud_state = NUD_NONE;
				neigh_dbg(2, "neigh %p is stray\n", n);
			पूर्ण
			ग_लिखो_unlock(&n->lock);
			neigh_cleanup_and_release(n);
		पूर्ण
	पूर्ण
पूर्ण

व्योम neigh_changeaddr(काष्ठा neigh_table *tbl, काष्ठा net_device *dev)
अणु
	ग_लिखो_lock_bh(&tbl->lock);
	neigh_flush_dev(tbl, dev, false);
	ग_लिखो_unlock_bh(&tbl->lock);
पूर्ण
EXPORT_SYMBOL(neigh_changeaddr);

अटल पूर्णांक __neigh_अगरकरोwn(काष्ठा neigh_table *tbl, काष्ठा net_device *dev,
			  bool skip_perm)
अणु
	ग_लिखो_lock_bh(&tbl->lock);
	neigh_flush_dev(tbl, dev, skip_perm);
	pneigh_अगरकरोwn_and_unlock(tbl, dev);

	del_समयr_sync(&tbl->proxy_समयr);
	pneigh_queue_purge(&tbl->proxy_queue);
	वापस 0;
पूर्ण

पूर्णांक neigh_carrier_करोwn(काष्ठा neigh_table *tbl, काष्ठा net_device *dev)
अणु
	__neigh_अगरकरोwn(tbl, dev, true);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(neigh_carrier_करोwn);

पूर्णांक neigh_अगरकरोwn(काष्ठा neigh_table *tbl, काष्ठा net_device *dev)
अणु
	__neigh_अगरकरोwn(tbl, dev, false);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(neigh_अगरकरोwn);

अटल काष्ठा neighbour *neigh_alloc(काष्ठा neigh_table *tbl,
				     काष्ठा net_device *dev,
				     bool exempt_from_gc)
अणु
	काष्ठा neighbour *n = शून्य;
	अचिन्हित दीर्घ now = jअगरfies;
	पूर्णांक entries;

	अगर (exempt_from_gc)
		जाओ करो_alloc;

	entries = atomic_inc_वापस(&tbl->gc_entries) - 1;
	अगर (entries >= tbl->gc_thresh3 ||
	    (entries >= tbl->gc_thresh2 &&
	     समय_after(now, tbl->last_flush + 5 * HZ))) अणु
		अगर (!neigh_क्रमced_gc(tbl) &&
		    entries >= tbl->gc_thresh3) अणु
			net_info_ratelimited("%s: neighbor table overflow!\n",
					     tbl->id);
			NEIGH_CACHE_STAT_INC(tbl, table_fulls);
			जाओ out_entries;
		पूर्ण
	पूर्ण

करो_alloc:
	n = kzalloc(tbl->entry_size + dev->neigh_priv_len, GFP_ATOMIC);
	अगर (!n)
		जाओ out_entries;

	__skb_queue_head_init(&n->arp_queue);
	rwlock_init(&n->lock);
	seqlock_init(&n->ha_lock);
	n->updated	  = n->used = now;
	n->nud_state	  = NUD_NONE;
	n->output	  = neigh_blackhole;
	seqlock_init(&n->hh.hh_lock);
	n->parms	  = neigh_parms_clone(&tbl->parms);
	समयr_setup(&n->समयr, neigh_समयr_handler, 0);

	NEIGH_CACHE_STAT_INC(tbl, allocs);
	n->tbl		  = tbl;
	refcount_set(&n->refcnt, 1);
	n->dead		  = 1;
	INIT_LIST_HEAD(&n->gc_list);

	atomic_inc(&tbl->entries);
out:
	वापस n;

out_entries:
	अगर (!exempt_from_gc)
		atomic_dec(&tbl->gc_entries);
	जाओ out;
पूर्ण

अटल व्योम neigh_get_hash_rnd(u32 *x)
अणु
	*x = get_अक्रमom_u32() | 1;
पूर्ण

अटल काष्ठा neigh_hash_table *neigh_hash_alloc(अचिन्हित पूर्णांक shअगरt)
अणु
	माप_प्रकार size = (1 << shअगरt) * माप(काष्ठा neighbour *);
	काष्ठा neigh_hash_table *ret;
	काष्ठा neighbour __rcu **buckets;
	पूर्णांक i;

	ret = kदो_स्मृति(माप(*ret), GFP_ATOMIC);
	अगर (!ret)
		वापस शून्य;
	अगर (size <= PAGE_SIZE) अणु
		buckets = kzalloc(size, GFP_ATOMIC);
	पूर्ण अन्यथा अणु
		buckets = (काष्ठा neighbour __rcu **)
			  __get_मुक्त_pages(GFP_ATOMIC | __GFP_ZERO,
					   get_order(size));
		kmemleak_alloc(buckets, size, 1, GFP_ATOMIC);
	पूर्ण
	अगर (!buckets) अणु
		kमुक्त(ret);
		वापस शून्य;
	पूर्ण
	ret->hash_buckets = buckets;
	ret->hash_shअगरt = shअगरt;
	क्रम (i = 0; i < NEIGH_NUM_HASH_RND; i++)
		neigh_get_hash_rnd(&ret->hash_rnd[i]);
	वापस ret;
पूर्ण

अटल व्योम neigh_hash_मुक्त_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा neigh_hash_table *nht = container_of(head,
						    काष्ठा neigh_hash_table,
						    rcu);
	माप_प्रकार size = (1 << nht->hash_shअगरt) * माप(काष्ठा neighbour *);
	काष्ठा neighbour __rcu **buckets = nht->hash_buckets;

	अगर (size <= PAGE_SIZE) अणु
		kमुक्त(buckets);
	पूर्ण अन्यथा अणु
		kmemleak_मुक्त(buckets);
		मुक्त_pages((अचिन्हित दीर्घ)buckets, get_order(size));
	पूर्ण
	kमुक्त(nht);
पूर्ण

अटल काष्ठा neigh_hash_table *neigh_hash_grow(काष्ठा neigh_table *tbl,
						अचिन्हित दीर्घ new_shअगरt)
अणु
	अचिन्हित पूर्णांक i, hash;
	काष्ठा neigh_hash_table *new_nht, *old_nht;

	NEIGH_CACHE_STAT_INC(tbl, hash_grows);

	old_nht = rcu_dereference_रक्षित(tbl->nht,
					    lockdep_is_held(&tbl->lock));
	new_nht = neigh_hash_alloc(new_shअगरt);
	अगर (!new_nht)
		वापस old_nht;

	क्रम (i = 0; i < (1 << old_nht->hash_shअगरt); i++) अणु
		काष्ठा neighbour *n, *next;

		क्रम (n = rcu_dereference_रक्षित(old_nht->hash_buckets[i],
						   lockdep_is_held(&tbl->lock));
		     n != शून्य;
		     n = next) अणु
			hash = tbl->hash(n->primary_key, n->dev,
					 new_nht->hash_rnd);

			hash >>= (32 - new_nht->hash_shअगरt);
			next = rcu_dereference_रक्षित(n->next,
						lockdep_is_held(&tbl->lock));

			rcu_assign_poपूर्णांकer(n->next,
					   rcu_dereference_रक्षित(
						new_nht->hash_buckets[hash],
						lockdep_is_held(&tbl->lock)));
			rcu_assign_poपूर्णांकer(new_nht->hash_buckets[hash], n);
		पूर्ण
	पूर्ण

	rcu_assign_poपूर्णांकer(tbl->nht, new_nht);
	call_rcu(&old_nht->rcu, neigh_hash_मुक्त_rcu);
	वापस new_nht;
पूर्ण

काष्ठा neighbour *neigh_lookup(काष्ठा neigh_table *tbl, स्थिर व्योम *pkey,
			       काष्ठा net_device *dev)
अणु
	काष्ठा neighbour *n;

	NEIGH_CACHE_STAT_INC(tbl, lookups);

	rcu_पढ़ो_lock_bh();
	n = __neigh_lookup_noref(tbl, pkey, dev);
	अगर (n) अणु
		अगर (!refcount_inc_not_zero(&n->refcnt))
			n = शून्य;
		NEIGH_CACHE_STAT_INC(tbl, hits);
	पूर्ण

	rcu_पढ़ो_unlock_bh();
	वापस n;
पूर्ण
EXPORT_SYMBOL(neigh_lookup);

काष्ठा neighbour *neigh_lookup_nodev(काष्ठा neigh_table *tbl, काष्ठा net *net,
				     स्थिर व्योम *pkey)
अणु
	काष्ठा neighbour *n;
	अचिन्हित पूर्णांक key_len = tbl->key_len;
	u32 hash_val;
	काष्ठा neigh_hash_table *nht;

	NEIGH_CACHE_STAT_INC(tbl, lookups);

	rcu_पढ़ो_lock_bh();
	nht = rcu_dereference_bh(tbl->nht);
	hash_val = tbl->hash(pkey, शून्य, nht->hash_rnd) >> (32 - nht->hash_shअगरt);

	क्रम (n = rcu_dereference_bh(nht->hash_buckets[hash_val]);
	     n != शून्य;
	     n = rcu_dereference_bh(n->next)) अणु
		अगर (!स_भेद(n->primary_key, pkey, key_len) &&
		    net_eq(dev_net(n->dev), net)) अणु
			अगर (!refcount_inc_not_zero(&n->refcnt))
				n = शून्य;
			NEIGH_CACHE_STAT_INC(tbl, hits);
			अवरोध;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock_bh();
	वापस n;
पूर्ण
EXPORT_SYMBOL(neigh_lookup_nodev);

अटल काष्ठा neighbour *___neigh_create(काष्ठा neigh_table *tbl,
					 स्थिर व्योम *pkey,
					 काष्ठा net_device *dev,
					 bool exempt_from_gc, bool want_ref)
अणु
	काष्ठा neighbour *n1, *rc, *n = neigh_alloc(tbl, dev, exempt_from_gc);
	u32 hash_val;
	अचिन्हित पूर्णांक key_len = tbl->key_len;
	पूर्णांक error;
	काष्ठा neigh_hash_table *nht;

	trace_neigh_create(tbl, dev, pkey, n, exempt_from_gc);

	अगर (!n) अणु
		rc = ERR_PTR(-ENOBUFS);
		जाओ out;
	पूर्ण

	स_नकल(n->primary_key, pkey, key_len);
	n->dev = dev;
	dev_hold(dev);

	/* Protocol specअगरic setup. */
	अगर (tbl->स्थिरructor &&	(error = tbl->स्थिरructor(n)) < 0) अणु
		rc = ERR_PTR(error);
		जाओ out_neigh_release;
	पूर्ण

	अगर (dev->netdev_ops->nकरो_neigh_स्थिरruct) अणु
		error = dev->netdev_ops->nकरो_neigh_स्थिरruct(dev, n);
		अगर (error < 0) अणु
			rc = ERR_PTR(error);
			जाओ out_neigh_release;
		पूर्ण
	पूर्ण

	/* Device specअगरic setup. */
	अगर (n->parms->neigh_setup &&
	    (error = n->parms->neigh_setup(n)) < 0) अणु
		rc = ERR_PTR(error);
		जाओ out_neigh_release;
	पूर्ण

	n->confirmed = jअगरfies - (NEIGH_VAR(n->parms, BASE_REACHABLE_TIME) << 1);

	ग_लिखो_lock_bh(&tbl->lock);
	nht = rcu_dereference_रक्षित(tbl->nht,
					lockdep_is_held(&tbl->lock));

	अगर (atomic_पढ़ो(&tbl->entries) > (1 << nht->hash_shअगरt))
		nht = neigh_hash_grow(tbl, nht->hash_shअगरt + 1);

	hash_val = tbl->hash(n->primary_key, dev, nht->hash_rnd) >> (32 - nht->hash_shअगरt);

	अगर (n->parms->dead) अणु
		rc = ERR_PTR(-EINVAL);
		जाओ out_tbl_unlock;
	पूर्ण

	क्रम (n1 = rcu_dereference_रक्षित(nht->hash_buckets[hash_val],
					    lockdep_is_held(&tbl->lock));
	     n1 != शून्य;
	     n1 = rcu_dereference_रक्षित(n1->next,
			lockdep_is_held(&tbl->lock))) अणु
		अगर (dev == n1->dev && !स_भेद(n1->primary_key, n->primary_key, key_len)) अणु
			अगर (want_ref)
				neigh_hold(n1);
			rc = n1;
			जाओ out_tbl_unlock;
		पूर्ण
	पूर्ण

	n->dead = 0;
	अगर (!exempt_from_gc)
		list_add_tail(&n->gc_list, &n->tbl->gc_list);

	अगर (want_ref)
		neigh_hold(n);
	rcu_assign_poपूर्णांकer(n->next,
			   rcu_dereference_रक्षित(nht->hash_buckets[hash_val],
						     lockdep_is_held(&tbl->lock)));
	rcu_assign_poपूर्णांकer(nht->hash_buckets[hash_val], n);
	ग_लिखो_unlock_bh(&tbl->lock);
	neigh_dbg(2, "neigh %p is created\n", n);
	rc = n;
out:
	वापस rc;
out_tbl_unlock:
	ग_लिखो_unlock_bh(&tbl->lock);
out_neigh_release:
	अगर (!exempt_from_gc)
		atomic_dec(&tbl->gc_entries);
	neigh_release(n);
	जाओ out;
पूर्ण

काष्ठा neighbour *__neigh_create(काष्ठा neigh_table *tbl, स्थिर व्योम *pkey,
				 काष्ठा net_device *dev, bool want_ref)
अणु
	वापस ___neigh_create(tbl, pkey, dev, false, want_ref);
पूर्ण
EXPORT_SYMBOL(__neigh_create);

अटल u32 pneigh_hash(स्थिर व्योम *pkey, अचिन्हित पूर्णांक key_len)
अणु
	u32 hash_val = *(u32 *)(pkey + key_len - 4);
	hash_val ^= (hash_val >> 16);
	hash_val ^= hash_val >> 8;
	hash_val ^= hash_val >> 4;
	hash_val &= PNEIGH_HASHMASK;
	वापस hash_val;
पूर्ण

अटल काष्ठा pneigh_entry *__pneigh_lookup_1(काष्ठा pneigh_entry *n,
					      काष्ठा net *net,
					      स्थिर व्योम *pkey,
					      अचिन्हित पूर्णांक key_len,
					      काष्ठा net_device *dev)
अणु
	जबतक (n) अणु
		अगर (!स_भेद(n->key, pkey, key_len) &&
		    net_eq(pneigh_net(n), net) &&
		    (n->dev == dev || !n->dev))
			वापस n;
		n = n->next;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा pneigh_entry *__pneigh_lookup(काष्ठा neigh_table *tbl,
		काष्ठा net *net, स्थिर व्योम *pkey, काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक key_len = tbl->key_len;
	u32 hash_val = pneigh_hash(pkey, key_len);

	वापस __pneigh_lookup_1(tbl->phash_buckets[hash_val],
				 net, pkey, key_len, dev);
पूर्ण
EXPORT_SYMBOL_GPL(__pneigh_lookup);

काष्ठा pneigh_entry * pneigh_lookup(काष्ठा neigh_table *tbl,
				    काष्ठा net *net, स्थिर व्योम *pkey,
				    काष्ठा net_device *dev, पूर्णांक creat)
अणु
	काष्ठा pneigh_entry *n;
	अचिन्हित पूर्णांक key_len = tbl->key_len;
	u32 hash_val = pneigh_hash(pkey, key_len);

	पढ़ो_lock_bh(&tbl->lock);
	n = __pneigh_lookup_1(tbl->phash_buckets[hash_val],
			      net, pkey, key_len, dev);
	पढ़ो_unlock_bh(&tbl->lock);

	अगर (n || !creat)
		जाओ out;

	ASSERT_RTNL();

	n = kदो_स्मृति(माप(*n) + key_len, GFP_KERNEL);
	अगर (!n)
		जाओ out;

	n->protocol = 0;
	ग_लिखो_pnet(&n->net, net);
	स_नकल(n->key, pkey, key_len);
	n->dev = dev;
	अगर (dev)
		dev_hold(dev);

	अगर (tbl->pस्थिरructor && tbl->pस्थिरructor(n)) अणु
		अगर (dev)
			dev_put(dev);
		kमुक्त(n);
		n = शून्य;
		जाओ out;
	पूर्ण

	ग_लिखो_lock_bh(&tbl->lock);
	n->next = tbl->phash_buckets[hash_val];
	tbl->phash_buckets[hash_val] = n;
	ग_लिखो_unlock_bh(&tbl->lock);
out:
	वापस n;
पूर्ण
EXPORT_SYMBOL(pneigh_lookup);


पूर्णांक pneigh_delete(काष्ठा neigh_table *tbl, काष्ठा net *net, स्थिर व्योम *pkey,
		  काष्ठा net_device *dev)
अणु
	काष्ठा pneigh_entry *n, **np;
	अचिन्हित पूर्णांक key_len = tbl->key_len;
	u32 hash_val = pneigh_hash(pkey, key_len);

	ग_लिखो_lock_bh(&tbl->lock);
	क्रम (np = &tbl->phash_buckets[hash_val]; (n = *np) != शून्य;
	     np = &n->next) अणु
		अगर (!स_भेद(n->key, pkey, key_len) && n->dev == dev &&
		    net_eq(pneigh_net(n), net)) अणु
			*np = n->next;
			ग_लिखो_unlock_bh(&tbl->lock);
			अगर (tbl->pdeकाष्ठाor)
				tbl->pdeकाष्ठाor(n);
			अगर (n->dev)
				dev_put(n->dev);
			kमुक्त(n);
			वापस 0;
		पूर्ण
	पूर्ण
	ग_लिखो_unlock_bh(&tbl->lock);
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक pneigh_अगरकरोwn_and_unlock(काष्ठा neigh_table *tbl,
				    काष्ठा net_device *dev)
अणु
	काष्ठा pneigh_entry *n, **np, *मुक्तlist = शून्य;
	u32 h;

	क्रम (h = 0; h <= PNEIGH_HASHMASK; h++) अणु
		np = &tbl->phash_buckets[h];
		जबतक ((n = *np) != शून्य) अणु
			अगर (!dev || n->dev == dev) अणु
				*np = n->next;
				n->next = मुक्तlist;
				मुक्तlist = n;
				जारी;
			पूर्ण
			np = &n->next;
		पूर्ण
	पूर्ण
	ग_लिखो_unlock_bh(&tbl->lock);
	जबतक ((n = मुक्तlist)) अणु
		मुक्तlist = n->next;
		n->next = शून्य;
		अगर (tbl->pdeकाष्ठाor)
			tbl->pdeकाष्ठाor(n);
		अगर (n->dev)
			dev_put(n->dev);
		kमुक्त(n);
	पूर्ण
	वापस -ENOENT;
पूर्ण

अटल व्योम neigh_parms_destroy(काष्ठा neigh_parms *parms);

अटल अंतरभूत व्योम neigh_parms_put(काष्ठा neigh_parms *parms)
अणु
	अगर (refcount_dec_and_test(&parms->refcnt))
		neigh_parms_destroy(parms);
पूर्ण

/*
 *	neighbour must alपढ़ोy be out of the table;
 *
 */
व्योम neigh_destroy(काष्ठा neighbour *neigh)
अणु
	काष्ठा net_device *dev = neigh->dev;

	NEIGH_CACHE_STAT_INC(neigh->tbl, destroys);

	अगर (!neigh->dead) अणु
		pr_warn("Destroying alive neighbour %p\n", neigh);
		dump_stack();
		वापस;
	पूर्ण

	अगर (neigh_del_समयr(neigh))
		pr_warn("Impossible event\n");

	ग_लिखो_lock_bh(&neigh->lock);
	__skb_queue_purge(&neigh->arp_queue);
	ग_लिखो_unlock_bh(&neigh->lock);
	neigh->arp_queue_len_bytes = 0;

	अगर (dev->netdev_ops->nकरो_neigh_destroy)
		dev->netdev_ops->nकरो_neigh_destroy(dev, neigh);

	dev_put(dev);
	neigh_parms_put(neigh->parms);

	neigh_dbg(2, "neigh %p is destroyed\n", neigh);

	atomic_dec(&neigh->tbl->entries);
	kमुक्त_rcu(neigh, rcu);
पूर्ण
EXPORT_SYMBOL(neigh_destroy);

/* Neighbour state is suspicious;
   disable fast path.

   Called with ग_लिखो_locked neigh.
 */
अटल व्योम neigh_suspect(काष्ठा neighbour *neigh)
अणु
	neigh_dbg(2, "neigh %p is suspected\n", neigh);

	neigh->output = neigh->ops->output;
पूर्ण

/* Neighbour state is OK;
   enable fast path.

   Called with ग_लिखो_locked neigh.
 */
अटल व्योम neigh_connect(काष्ठा neighbour *neigh)
अणु
	neigh_dbg(2, "neigh %p is connected\n", neigh);

	neigh->output = neigh->ops->connected_output;
पूर्ण

अटल व्योम neigh_periodic_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा neigh_table *tbl = container_of(work, काष्ठा neigh_table, gc_work.work);
	काष्ठा neighbour *n;
	काष्ठा neighbour __rcu **np;
	अचिन्हित पूर्णांक i;
	काष्ठा neigh_hash_table *nht;

	NEIGH_CACHE_STAT_INC(tbl, periodic_gc_runs);

	ग_लिखो_lock_bh(&tbl->lock);
	nht = rcu_dereference_रक्षित(tbl->nht,
					lockdep_is_held(&tbl->lock));

	/*
	 *	periodically recompute ReachableTime from अक्रमom function
	 */

	अगर (समय_after(jअगरfies, tbl->last_अक्रम + 300 * HZ)) अणु
		काष्ठा neigh_parms *p;
		tbl->last_अक्रम = jअगरfies;
		list_क्रम_each_entry(p, &tbl->parms_list, list)
			p->reachable_समय =
				neigh_अक्रम_reach_समय(NEIGH_VAR(p, BASE_REACHABLE_TIME));
	पूर्ण

	अगर (atomic_पढ़ो(&tbl->entries) < tbl->gc_thresh1)
		जाओ out;

	क्रम (i = 0 ; i < (1 << nht->hash_shअगरt); i++) अणु
		np = &nht->hash_buckets[i];

		जबतक ((n = rcu_dereference_रक्षित(*np,
				lockdep_is_held(&tbl->lock))) != शून्य) अणु
			अचिन्हित पूर्णांक state;

			ग_लिखो_lock(&n->lock);

			state = n->nud_state;
			अगर ((state & (NUD_PERMANENT | NUD_IN_TIMER)) ||
			    (n->flags & NTF_EXT_LEARNED)) अणु
				ग_लिखो_unlock(&n->lock);
				जाओ next_elt;
			पूर्ण

			अगर (समय_beक्रमe(n->used, n->confirmed))
				n->used = n->confirmed;

			अगर (refcount_पढ़ो(&n->refcnt) == 1 &&
			    (state == NUD_FAILED ||
			     समय_after(jअगरfies, n->used + NEIGH_VAR(n->parms, GC_STALETIME)))) अणु
				*np = n->next;
				neigh_mark_dead(n);
				ग_लिखो_unlock(&n->lock);
				neigh_cleanup_and_release(n);
				जारी;
			पूर्ण
			ग_लिखो_unlock(&n->lock);

next_elt:
			np = &n->next;
		पूर्ण
		/*
		 * It's fine to release lock here, even अगर hash table
		 * grows जबतक we are preempted.
		 */
		ग_लिखो_unlock_bh(&tbl->lock);
		cond_resched();
		ग_लिखो_lock_bh(&tbl->lock);
		nht = rcu_dereference_रक्षित(tbl->nht,
						lockdep_is_held(&tbl->lock));
	पूर्ण
out:
	/* Cycle through all hash buckets every BASE_REACHABLE_TIME/2 ticks.
	 * ARP entry समयouts range from 1/2 BASE_REACHABLE_TIME to 3/2
	 * BASE_REACHABLE_TIME.
	 */
	queue_delayed_work(प्रणाली_घातer_efficient_wq, &tbl->gc_work,
			      NEIGH_VAR(&tbl->parms, BASE_REACHABLE_TIME) >> 1);
	ग_लिखो_unlock_bh(&tbl->lock);
पूर्ण

अटल __अंतरभूत__ पूर्णांक neigh_max_probes(काष्ठा neighbour *n)
अणु
	काष्ठा neigh_parms *p = n->parms;
	वापस NEIGH_VAR(p, UCAST_PROBES) + NEIGH_VAR(p, APP_PROBES) +
	       (n->nud_state & NUD_PROBE ? NEIGH_VAR(p, MCAST_REPROBES) :
	        NEIGH_VAR(p, MCAST_PROBES));
पूर्ण

अटल व्योम neigh_invalidate(काष्ठा neighbour *neigh)
	__releases(neigh->lock)
	__acquires(neigh->lock)
अणु
	काष्ठा sk_buff *skb;

	NEIGH_CACHE_STAT_INC(neigh->tbl, res_failed);
	neigh_dbg(2, "neigh %p is failed\n", neigh);
	neigh->updated = jअगरfies;

	/* It is very thin place. report_unreachable is very complicated
	   routine. Particularly, it can hit the same neighbour entry!

	   So that, we try to be accurate and aव्योम dead loop. --ANK
	 */
	जबतक (neigh->nud_state == NUD_FAILED &&
	       (skb = __skb_dequeue(&neigh->arp_queue)) != शून्य) अणु
		ग_लिखो_unlock(&neigh->lock);
		neigh->ops->error_report(neigh, skb);
		ग_लिखो_lock(&neigh->lock);
	पूर्ण
	__skb_queue_purge(&neigh->arp_queue);
	neigh->arp_queue_len_bytes = 0;
पूर्ण

अटल व्योम neigh_probe(काष्ठा neighbour *neigh)
	__releases(neigh->lock)
अणु
	काष्ठा sk_buff *skb = skb_peek_tail(&neigh->arp_queue);
	/* keep skb alive even अगर arp_queue overflows */
	अगर (skb)
		skb = skb_clone(skb, GFP_ATOMIC);
	ग_लिखो_unlock(&neigh->lock);
	अगर (neigh->ops->solicit)
		neigh->ops->solicit(neigh, skb);
	atomic_inc(&neigh->probes);
	consume_skb(skb);
पूर्ण

/* Called when a समयr expires क्रम a neighbour entry. */

अटल व्योम neigh_समयr_handler(काष्ठा समयr_list *t)
अणु
	अचिन्हित दीर्घ now, next;
	काष्ठा neighbour *neigh = from_समयr(neigh, t, समयr);
	अचिन्हित पूर्णांक state;
	पूर्णांक notअगरy = 0;

	ग_लिखो_lock(&neigh->lock);

	state = neigh->nud_state;
	now = jअगरfies;
	next = now + HZ;

	अगर (!(state & NUD_IN_TIMER))
		जाओ out;

	अगर (state & NUD_REACHABLE) अणु
		अगर (समय_beक्रमe_eq(now,
				   neigh->confirmed + neigh->parms->reachable_समय)) अणु
			neigh_dbg(2, "neigh %p is still alive\n", neigh);
			next = neigh->confirmed + neigh->parms->reachable_समय;
		पूर्ण अन्यथा अगर (समय_beक्रमe_eq(now,
					  neigh->used +
					  NEIGH_VAR(neigh->parms, DELAY_PROBE_TIME))) अणु
			neigh_dbg(2, "neigh %p is delayed\n", neigh);
			neigh->nud_state = NUD_DELAY;
			neigh->updated = jअगरfies;
			neigh_suspect(neigh);
			next = now + NEIGH_VAR(neigh->parms, DELAY_PROBE_TIME);
		पूर्ण अन्यथा अणु
			neigh_dbg(2, "neigh %p is suspected\n", neigh);
			neigh->nud_state = NUD_STALE;
			neigh->updated = jअगरfies;
			neigh_suspect(neigh);
			notअगरy = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (state & NUD_DELAY) अणु
		अगर (समय_beक्रमe_eq(now,
				   neigh->confirmed +
				   NEIGH_VAR(neigh->parms, DELAY_PROBE_TIME))) अणु
			neigh_dbg(2, "neigh %p is now reachable\n", neigh);
			neigh->nud_state = NUD_REACHABLE;
			neigh->updated = jअगरfies;
			neigh_connect(neigh);
			notअगरy = 1;
			next = neigh->confirmed + neigh->parms->reachable_समय;
		पूर्ण अन्यथा अणु
			neigh_dbg(2, "neigh %p is probed\n", neigh);
			neigh->nud_state = NUD_PROBE;
			neigh->updated = jअगरfies;
			atomic_set(&neigh->probes, 0);
			notअगरy = 1;
			next = now + max(NEIGH_VAR(neigh->parms, RETRANS_TIME),
					 HZ/100);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* NUD_PROBE|NUD_INCOMPLETE */
		next = now + max(NEIGH_VAR(neigh->parms, RETRANS_TIME), HZ/100);
	पूर्ण

	अगर ((neigh->nud_state & (NUD_INCOMPLETE | NUD_PROBE)) &&
	    atomic_पढ़ो(&neigh->probes) >= neigh_max_probes(neigh)) अणु
		neigh->nud_state = NUD_FAILED;
		notअगरy = 1;
		neigh_invalidate(neigh);
		जाओ out;
	पूर्ण

	अगर (neigh->nud_state & NUD_IN_TIMER) अणु
		अगर (समय_beक्रमe(next, jअगरfies + HZ/100))
			next = jअगरfies + HZ/100;
		अगर (!mod_समयr(&neigh->समयr, next))
			neigh_hold(neigh);
	पूर्ण
	अगर (neigh->nud_state & (NUD_INCOMPLETE | NUD_PROBE)) अणु
		neigh_probe(neigh);
	पूर्ण अन्यथा अणु
out:
		ग_लिखो_unlock(&neigh->lock);
	पूर्ण

	अगर (notअगरy)
		neigh_update_notअगरy(neigh, 0);

	trace_neigh_समयr_handler(neigh, 0);

	neigh_release(neigh);
पूर्ण

पूर्णांक __neigh_event_send(काष्ठा neighbour *neigh, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc;
	bool immediate_probe = false;

	ग_लिखो_lock_bh(&neigh->lock);

	rc = 0;
	अगर (neigh->nud_state & (NUD_CONNECTED | NUD_DELAY | NUD_PROBE))
		जाओ out_unlock_bh;
	अगर (neigh->dead)
		जाओ out_dead;

	अगर (!(neigh->nud_state & (NUD_STALE | NUD_INCOMPLETE))) अणु
		अगर (NEIGH_VAR(neigh->parms, MCAST_PROBES) +
		    NEIGH_VAR(neigh->parms, APP_PROBES)) अणु
			अचिन्हित दीर्घ next, now = jअगरfies;

			atomic_set(&neigh->probes,
				   NEIGH_VAR(neigh->parms, UCAST_PROBES));
			neigh_del_समयr(neigh);
			neigh->nud_state     = NUD_INCOMPLETE;
			neigh->updated = now;
			next = now + max(NEIGH_VAR(neigh->parms, RETRANS_TIME),
					 HZ/100);
			neigh_add_समयr(neigh, next);
			immediate_probe = true;
		पूर्ण अन्यथा अणु
			neigh->nud_state = NUD_FAILED;
			neigh->updated = jअगरfies;
			ग_लिखो_unlock_bh(&neigh->lock);

			kमुक्त_skb(skb);
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा अगर (neigh->nud_state & NUD_STALE) अणु
		neigh_dbg(2, "neigh %p is delayed\n", neigh);
		neigh_del_समयr(neigh);
		neigh->nud_state = NUD_DELAY;
		neigh->updated = jअगरfies;
		neigh_add_समयr(neigh, jअगरfies +
				NEIGH_VAR(neigh->parms, DELAY_PROBE_TIME));
	पूर्ण

	अगर (neigh->nud_state == NUD_INCOMPLETE) अणु
		अगर (skb) अणु
			जबतक (neigh->arp_queue_len_bytes + skb->truesize >
			       NEIGH_VAR(neigh->parms, QUEUE_LEN_BYTES)) अणु
				काष्ठा sk_buff *buff;

				buff = __skb_dequeue(&neigh->arp_queue);
				अगर (!buff)
					अवरोध;
				neigh->arp_queue_len_bytes -= buff->truesize;
				kमुक्त_skb(buff);
				NEIGH_CACHE_STAT_INC(neigh->tbl, unres_discards);
			पूर्ण
			skb_dst_क्रमce(skb);
			__skb_queue_tail(&neigh->arp_queue, skb);
			neigh->arp_queue_len_bytes += skb->truesize;
		पूर्ण
		rc = 1;
	पूर्ण
out_unlock_bh:
	अगर (immediate_probe)
		neigh_probe(neigh);
	अन्यथा
		ग_लिखो_unlock(&neigh->lock);
	local_bh_enable();
	trace_neigh_event_send_करोne(neigh, rc);
	वापस rc;

out_dead:
	अगर (neigh->nud_state & NUD_STALE)
		जाओ out_unlock_bh;
	ग_लिखो_unlock_bh(&neigh->lock);
	kमुक्त_skb(skb);
	trace_neigh_event_send_dead(neigh, 1);
	वापस 1;
पूर्ण
EXPORT_SYMBOL(__neigh_event_send);

अटल व्योम neigh_update_hhs(काष्ठा neighbour *neigh)
अणु
	काष्ठा hh_cache *hh;
	व्योम (*update)(काष्ठा hh_cache*, स्थिर काष्ठा net_device*, स्थिर अचिन्हित अक्षर *)
		= शून्य;

	अगर (neigh->dev->header_ops)
		update = neigh->dev->header_ops->cache_update;

	अगर (update) अणु
		hh = &neigh->hh;
		अगर (READ_ONCE(hh->hh_len)) अणु
			ग_लिखो_seqlock_bh(&hh->hh_lock);
			update(hh, neigh->dev, neigh->ha);
			ग_लिखो_sequnlock_bh(&hh->hh_lock);
		पूर्ण
	पूर्ण
पूर्ण



/* Generic update routine.
   -- lladdr is new lladdr or शून्य, अगर it is not supplied.
   -- new    is new state.
   -- flags
	NEIGH_UPDATE_F_OVERRIDE allows to override existing lladdr,
				अगर it is dअगरferent.
	NEIGH_UPDATE_F_WEAK_OVERRIDE will suspect existing "connected"
				lladdr instead of overriding it
				अगर it is dअगरferent.
	NEIGH_UPDATE_F_ADMIN	means that the change is administrative.

	NEIGH_UPDATE_F_OVERRIDE_ISROUTER allows to override existing
				NTF_ROUTER flag.
	NEIGH_UPDATE_F_ISROUTER	indicates अगर the neighbour is known as
				a router.

   Caller MUST hold reference count on the entry.
 */

अटल पूर्णांक __neigh_update(काष्ठा neighbour *neigh, स्थिर u8 *lladdr,
			  u8 new, u32 flags, u32 nlmsg_pid,
			  काष्ठा netlink_ext_ack *extack)
अणु
	bool ext_learn_change = false;
	u8 old;
	पूर्णांक err;
	पूर्णांक notअगरy = 0;
	काष्ठा net_device *dev;
	पूर्णांक update_isrouter = 0;

	trace_neigh_update(neigh, lladdr, new, flags, nlmsg_pid);

	ग_लिखो_lock_bh(&neigh->lock);

	dev    = neigh->dev;
	old    = neigh->nud_state;
	err    = -EPERM;

	अगर (neigh->dead) अणु
		NL_SET_ERR_MSG(extack, "Neighbor entry is now dead");
		new = old;
		जाओ out;
	पूर्ण
	अगर (!(flags & NEIGH_UPDATE_F_ADMIN) &&
	    (old & (NUD_NOARP | NUD_PERMANENT)))
		जाओ out;

	ext_learn_change = neigh_update_ext_learned(neigh, flags, &notअगरy);

	अगर (!(new & NUD_VALID)) अणु
		neigh_del_समयr(neigh);
		अगर (old & NUD_CONNECTED)
			neigh_suspect(neigh);
		neigh->nud_state = new;
		err = 0;
		notअगरy = old & NUD_VALID;
		अगर ((old & (NUD_INCOMPLETE | NUD_PROBE)) &&
		    (new & NUD_FAILED)) अणु
			neigh_invalidate(neigh);
			notअगरy = 1;
		पूर्ण
		जाओ out;
	पूर्ण

	/* Compare new lladdr with cached one */
	अगर (!dev->addr_len) अणु
		/* First हाल: device needs no address. */
		lladdr = neigh->ha;
	पूर्ण अन्यथा अगर (lladdr) अणु
		/* The second हाल: अगर something is alपढ़ोy cached
		   and a new address is proposed:
		   - compare new & old
		   - अगर they are dअगरferent, check override flag
		 */
		अगर ((old & NUD_VALID) &&
		    !स_भेद(lladdr, neigh->ha, dev->addr_len))
			lladdr = neigh->ha;
	पूर्ण अन्यथा अणु
		/* No address is supplied; अगर we know something,
		   use it, otherwise discard the request.
		 */
		err = -EINVAL;
		अगर (!(old & NUD_VALID)) अणु
			NL_SET_ERR_MSG(extack, "No link layer address given");
			जाओ out;
		पूर्ण
		lladdr = neigh->ha;
	पूर्ण

	/* Update confirmed बारtamp क्रम neighbour entry after we
	 * received ARP packet even अगर it करोesn't change IP to MAC binding.
	 */
	अगर (new & NUD_CONNECTED)
		neigh->confirmed = jअगरfies;

	/* If entry was valid and address is not changed,
	   करो not change entry state, अगर new one is STALE.
	 */
	err = 0;
	update_isrouter = flags & NEIGH_UPDATE_F_OVERRIDE_ISROUTER;
	अगर (old & NUD_VALID) अणु
		अगर (lladdr != neigh->ha && !(flags & NEIGH_UPDATE_F_OVERRIDE)) अणु
			update_isrouter = 0;
			अगर ((flags & NEIGH_UPDATE_F_WEAK_OVERRIDE) &&
			    (old & NUD_CONNECTED)) अणु
				lladdr = neigh->ha;
				new = NUD_STALE;
			पूर्ण अन्यथा
				जाओ out;
		पूर्ण अन्यथा अणु
			अगर (lladdr == neigh->ha && new == NUD_STALE &&
			    !(flags & NEIGH_UPDATE_F_ADMIN))
				new = old;
		पूर्ण
	पूर्ण

	/* Update बारtamp only once we know we will make a change to the
	 * neighbour entry. Otherwise we risk to move the lockसमय winकरोw with
	 * noop updates and ignore relevant ARP updates.
	 */
	अगर (new != old || lladdr != neigh->ha)
		neigh->updated = jअगरfies;

	अगर (new != old) अणु
		neigh_del_समयr(neigh);
		अगर (new & NUD_PROBE)
			atomic_set(&neigh->probes, 0);
		अगर (new & NUD_IN_TIMER)
			neigh_add_समयr(neigh, (jअगरfies +
						((new & NUD_REACHABLE) ?
						 neigh->parms->reachable_समय :
						 0)));
		neigh->nud_state = new;
		notअगरy = 1;
	पूर्ण

	अगर (lladdr != neigh->ha) अणु
		ग_लिखो_seqlock(&neigh->ha_lock);
		स_नकल(&neigh->ha, lladdr, dev->addr_len);
		ग_लिखो_sequnlock(&neigh->ha_lock);
		neigh_update_hhs(neigh);
		अगर (!(new & NUD_CONNECTED))
			neigh->confirmed = jअगरfies -
				      (NEIGH_VAR(neigh->parms, BASE_REACHABLE_TIME) << 1);
		notअगरy = 1;
	पूर्ण
	अगर (new == old)
		जाओ out;
	अगर (new & NUD_CONNECTED)
		neigh_connect(neigh);
	अन्यथा
		neigh_suspect(neigh);
	अगर (!(old & NUD_VALID)) अणु
		काष्ठा sk_buff *skb;

		/* Again: aव्योम dead loop अगर something went wrong */

		जबतक (neigh->nud_state & NUD_VALID &&
		       (skb = __skb_dequeue(&neigh->arp_queue)) != शून्य) अणु
			काष्ठा dst_entry *dst = skb_dst(skb);
			काष्ठा neighbour *n2, *n1 = neigh;
			ग_लिखो_unlock_bh(&neigh->lock);

			rcu_पढ़ो_lock();

			/* Why not just use 'neigh' as-is?  The problem is that
			 * things such as shaper, eql, and sch_teql can end up
			 * using alternative, dअगरferent, neigh objects to output
			 * the packet in the output path.  So what we need to करो
			 * here is re-lookup the top-level neigh in the path so
			 * we can reinject the packet there.
			 */
			n2 = शून्य;
			अगर (dst && dst->obsolete != DST_OBSOLETE_DEAD) अणु
				n2 = dst_neigh_lookup_skb(dst, skb);
				अगर (n2)
					n1 = n2;
			पूर्ण
			n1->output(n1, skb);
			अगर (n2)
				neigh_release(n2);
			rcu_पढ़ो_unlock();

			ग_लिखो_lock_bh(&neigh->lock);
		पूर्ण
		__skb_queue_purge(&neigh->arp_queue);
		neigh->arp_queue_len_bytes = 0;
	पूर्ण
out:
	अगर (update_isrouter)
		neigh_update_is_router(neigh, flags, &notअगरy);
	ग_लिखो_unlock_bh(&neigh->lock);

	अगर (((new ^ old) & NUD_PERMANENT) || ext_learn_change)
		neigh_update_gc_list(neigh);

	अगर (notअगरy)
		neigh_update_notअगरy(neigh, nlmsg_pid);

	trace_neigh_update_करोne(neigh, err);

	वापस err;
पूर्ण

पूर्णांक neigh_update(काष्ठा neighbour *neigh, स्थिर u8 *lladdr, u8 new,
		 u32 flags, u32 nlmsg_pid)
अणु
	वापस __neigh_update(neigh, lladdr, new, flags, nlmsg_pid, शून्य);
पूर्ण
EXPORT_SYMBOL(neigh_update);

/* Update the neigh to listen temporarily क्रम probe responses, even अगर it is
 * in a NUD_FAILED state. The caller has to hold neigh->lock क्रम writing.
 */
व्योम __neigh_set_probe_once(काष्ठा neighbour *neigh)
अणु
	अगर (neigh->dead)
		वापस;
	neigh->updated = jअगरfies;
	अगर (!(neigh->nud_state & NUD_FAILED))
		वापस;
	neigh->nud_state = NUD_INCOMPLETE;
	atomic_set(&neigh->probes, neigh_max_probes(neigh));
	neigh_add_समयr(neigh,
			jअगरfies + max(NEIGH_VAR(neigh->parms, RETRANS_TIME),
				      HZ/100));
पूर्ण
EXPORT_SYMBOL(__neigh_set_probe_once);

काष्ठा neighbour *neigh_event_ns(काष्ठा neigh_table *tbl,
				 u8 *lladdr, व्योम *saddr,
				 काष्ठा net_device *dev)
अणु
	काष्ठा neighbour *neigh = __neigh_lookup(tbl, saddr, dev,
						 lladdr || !dev->addr_len);
	अगर (neigh)
		neigh_update(neigh, lladdr, NUD_STALE,
			     NEIGH_UPDATE_F_OVERRIDE, 0);
	वापस neigh;
पूर्ण
EXPORT_SYMBOL(neigh_event_ns);

/* called with पढ़ो_lock_bh(&n->lock); */
अटल व्योम neigh_hh_init(काष्ठा neighbour *n)
अणु
	काष्ठा net_device *dev = n->dev;
	__be16 prot = n->tbl->protocol;
	काष्ठा hh_cache	*hh = &n->hh;

	ग_लिखो_lock_bh(&n->lock);

	/* Only one thपढ़ो can come in here and initialize the
	 * hh_cache entry.
	 */
	अगर (!hh->hh_len)
		dev->header_ops->cache(n, hh, prot);

	ग_लिखो_unlock_bh(&n->lock);
पूर्ण

/* Slow and careful. */

पूर्णांक neigh_resolve_output(काष्ठा neighbour *neigh, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = 0;

	अगर (!neigh_event_send(neigh, skb)) अणु
		पूर्णांक err;
		काष्ठा net_device *dev = neigh->dev;
		अचिन्हित पूर्णांक seq;

		अगर (dev->header_ops->cache && !READ_ONCE(neigh->hh.hh_len))
			neigh_hh_init(neigh);

		करो अणु
			__skb_pull(skb, skb_network_offset(skb));
			seq = पढ़ो_seqbegin(&neigh->ha_lock);
			err = dev_hard_header(skb, dev, ntohs(skb->protocol),
					      neigh->ha, शून्य, skb->len);
		पूर्ण जबतक (पढ़ो_seqretry(&neigh->ha_lock, seq));

		अगर (err >= 0)
			rc = dev_queue_xmit(skb);
		अन्यथा
			जाओ out_kमुक्त_skb;
	पूर्ण
out:
	वापस rc;
out_kमुक्त_skb:
	rc = -EINVAL;
	kमुक्त_skb(skb);
	जाओ out;
पूर्ण
EXPORT_SYMBOL(neigh_resolve_output);

/* As fast as possible without hh cache */

पूर्णांक neigh_connected_output(काष्ठा neighbour *neigh, काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = neigh->dev;
	अचिन्हित पूर्णांक seq;
	पूर्णांक err;

	करो अणु
		__skb_pull(skb, skb_network_offset(skb));
		seq = पढ़ो_seqbegin(&neigh->ha_lock);
		err = dev_hard_header(skb, dev, ntohs(skb->protocol),
				      neigh->ha, शून्य, skb->len);
	पूर्ण जबतक (पढ़ो_seqretry(&neigh->ha_lock, seq));

	अगर (err >= 0)
		err = dev_queue_xmit(skb);
	अन्यथा अणु
		err = -EINVAL;
		kमुक्त_skb(skb);
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL(neigh_connected_output);

पूर्णांक neigh_direct_output(काष्ठा neighbour *neigh, काष्ठा sk_buff *skb)
अणु
	वापस dev_queue_xmit(skb);
पूर्ण
EXPORT_SYMBOL(neigh_direct_output);

अटल व्योम neigh_proxy_process(काष्ठा समयr_list *t)
अणु
	काष्ठा neigh_table *tbl = from_समयr(tbl, t, proxy_समयr);
	दीर्घ sched_next = 0;
	अचिन्हित दीर्घ now = jअगरfies;
	काष्ठा sk_buff *skb, *n;

	spin_lock(&tbl->proxy_queue.lock);

	skb_queue_walk_safe(&tbl->proxy_queue, skb, n) अणु
		दीर्घ tdअगर = NEIGH_CB(skb)->sched_next - now;

		अगर (tdअगर <= 0) अणु
			काष्ठा net_device *dev = skb->dev;

			__skb_unlink(skb, &tbl->proxy_queue);
			अगर (tbl->proxy_reकरो && netअगर_running(dev)) अणु
				rcu_पढ़ो_lock();
				tbl->proxy_reकरो(skb);
				rcu_पढ़ो_unlock();
			पूर्ण अन्यथा अणु
				kमुक्त_skb(skb);
			पूर्ण

			dev_put(dev);
		पूर्ण अन्यथा अगर (!sched_next || tdअगर < sched_next)
			sched_next = tdअगर;
	पूर्ण
	del_समयr(&tbl->proxy_समयr);
	अगर (sched_next)
		mod_समयr(&tbl->proxy_समयr, jअगरfies + sched_next);
	spin_unlock(&tbl->proxy_queue.lock);
पूर्ण

व्योम pneigh_enqueue(काष्ठा neigh_table *tbl, काष्ठा neigh_parms *p,
		    काष्ठा sk_buff *skb)
अणु
	अचिन्हित दीर्घ sched_next = jअगरfies +
			pअक्रमom_u32_max(NEIGH_VAR(p, PROXY_DELAY));

	अगर (tbl->proxy_queue.qlen > NEIGH_VAR(p, PROXY_QLEN)) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	NEIGH_CB(skb)->sched_next = sched_next;
	NEIGH_CB(skb)->flags |= LOCALLY_ENQUEUED;

	spin_lock(&tbl->proxy_queue.lock);
	अगर (del_समयr(&tbl->proxy_समयr)) अणु
		अगर (समय_beक्रमe(tbl->proxy_समयr.expires, sched_next))
			sched_next = tbl->proxy_समयr.expires;
	पूर्ण
	skb_dst_drop(skb);
	dev_hold(skb->dev);
	__skb_queue_tail(&tbl->proxy_queue, skb);
	mod_समयr(&tbl->proxy_समयr, sched_next);
	spin_unlock(&tbl->proxy_queue.lock);
पूर्ण
EXPORT_SYMBOL(pneigh_enqueue);

अटल अंतरभूत काष्ठा neigh_parms *lookup_neigh_parms(काष्ठा neigh_table *tbl,
						      काष्ठा net *net, पूर्णांक अगरindex)
अणु
	काष्ठा neigh_parms *p;

	list_क्रम_each_entry(p, &tbl->parms_list, list) अणु
		अगर ((p->dev && p->dev->अगरindex == अगरindex && net_eq(neigh_parms_net(p), net)) ||
		    (!p->dev && !अगरindex && net_eq(net, &init_net)))
			वापस p;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा neigh_parms *neigh_parms_alloc(काष्ठा net_device *dev,
				      काष्ठा neigh_table *tbl)
अणु
	काष्ठा neigh_parms *p;
	काष्ठा net *net = dev_net(dev);
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;

	p = kmemdup(&tbl->parms, माप(*p), GFP_KERNEL);
	अगर (p) अणु
		p->tbl		  = tbl;
		refcount_set(&p->refcnt, 1);
		p->reachable_समय =
				neigh_अक्रम_reach_समय(NEIGH_VAR(p, BASE_REACHABLE_TIME));
		dev_hold(dev);
		p->dev = dev;
		ग_लिखो_pnet(&p->net, net);
		p->sysctl_table = शून्य;

		अगर (ops->nकरो_neigh_setup && ops->nकरो_neigh_setup(dev, p)) अणु
			dev_put(dev);
			kमुक्त(p);
			वापस शून्य;
		पूर्ण

		ग_लिखो_lock_bh(&tbl->lock);
		list_add(&p->list, &tbl->parms.list);
		ग_लिखो_unlock_bh(&tbl->lock);

		neigh_parms_data_state_cleanall(p);
	पूर्ण
	वापस p;
पूर्ण
EXPORT_SYMBOL(neigh_parms_alloc);

अटल व्योम neigh_rcu_मुक्त_parms(काष्ठा rcu_head *head)
अणु
	काष्ठा neigh_parms *parms =
		container_of(head, काष्ठा neigh_parms, rcu_head);

	neigh_parms_put(parms);
पूर्ण

व्योम neigh_parms_release(काष्ठा neigh_table *tbl, काष्ठा neigh_parms *parms)
अणु
	अगर (!parms || parms == &tbl->parms)
		वापस;
	ग_लिखो_lock_bh(&tbl->lock);
	list_del(&parms->list);
	parms->dead = 1;
	ग_लिखो_unlock_bh(&tbl->lock);
	अगर (parms->dev)
		dev_put(parms->dev);
	call_rcu(&parms->rcu_head, neigh_rcu_मुक्त_parms);
पूर्ण
EXPORT_SYMBOL(neigh_parms_release);

अटल व्योम neigh_parms_destroy(काष्ठा neigh_parms *parms)
अणु
	kमुक्त(parms);
पूर्ण

अटल काष्ठा lock_class_key neigh_table_proxy_queue_class;

अटल काष्ठा neigh_table *neigh_tables[NEIGH_NR_TABLES] __पढ़ो_mostly;

व्योम neigh_table_init(पूर्णांक index, काष्ठा neigh_table *tbl)
अणु
	अचिन्हित दीर्घ now = jअगरfies;
	अचिन्हित दीर्घ phsize;

	INIT_LIST_HEAD(&tbl->parms_list);
	INIT_LIST_HEAD(&tbl->gc_list);
	list_add(&tbl->parms.list, &tbl->parms_list);
	ग_लिखो_pnet(&tbl->parms.net, &init_net);
	refcount_set(&tbl->parms.refcnt, 1);
	tbl->parms.reachable_समय =
			  neigh_अक्रम_reach_समय(NEIGH_VAR(&tbl->parms, BASE_REACHABLE_TIME));

	tbl->stats = alloc_percpu(काष्ठा neigh_statistics);
	अगर (!tbl->stats)
		panic("cannot create neighbour cache statistics");

#अगर_घोषित CONFIG_PROC_FS
	अगर (!proc_create_seq_data(tbl->id, 0, init_net.proc_net_stat,
			      &neigh_stat_seq_ops, tbl))
		panic("cannot create neighbour proc dir entry");
#पूर्ण_अगर

	RCU_INIT_POINTER(tbl->nht, neigh_hash_alloc(3));

	phsize = (PNEIGH_HASHMASK + 1) * माप(काष्ठा pneigh_entry *);
	tbl->phash_buckets = kzalloc(phsize, GFP_KERNEL);

	अगर (!tbl->nht || !tbl->phash_buckets)
		panic("cannot allocate neighbour cache hashes");

	अगर (!tbl->entry_size)
		tbl->entry_size = ALIGN(दुरत्व(काष्ठा neighbour, primary_key) +
					tbl->key_len, NEIGH_PRIV_ALIGN);
	अन्यथा
		WARN_ON(tbl->entry_size % NEIGH_PRIV_ALIGN);

	rwlock_init(&tbl->lock);
	INIT_DEFERRABLE_WORK(&tbl->gc_work, neigh_periodic_work);
	queue_delayed_work(प्रणाली_घातer_efficient_wq, &tbl->gc_work,
			tbl->parms.reachable_समय);
	समयr_setup(&tbl->proxy_समयr, neigh_proxy_process, 0);
	skb_queue_head_init_class(&tbl->proxy_queue,
			&neigh_table_proxy_queue_class);

	tbl->last_flush = now;
	tbl->last_अक्रम	= now + tbl->parms.reachable_समय * 20;

	neigh_tables[index] = tbl;
पूर्ण
EXPORT_SYMBOL(neigh_table_init);

पूर्णांक neigh_table_clear(पूर्णांक index, काष्ठा neigh_table *tbl)
अणु
	neigh_tables[index] = शून्य;
	/* It is not clean... Fix it to unload IPv6 module safely */
	cancel_delayed_work_sync(&tbl->gc_work);
	del_समयr_sync(&tbl->proxy_समयr);
	pneigh_queue_purge(&tbl->proxy_queue);
	neigh_अगरकरोwn(tbl, शून्य);
	अगर (atomic_पढ़ो(&tbl->entries))
		pr_crit("neighbour leakage\n");

	call_rcu(&rcu_dereference_रक्षित(tbl->nht, 1)->rcu,
		 neigh_hash_मुक्त_rcu);
	tbl->nht = शून्य;

	kमुक्त(tbl->phash_buckets);
	tbl->phash_buckets = शून्य;

	हटाओ_proc_entry(tbl->id, init_net.proc_net_stat);

	मुक्त_percpu(tbl->stats);
	tbl->stats = शून्य;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(neigh_table_clear);

अटल काष्ठा neigh_table *neigh_find_table(पूर्णांक family)
अणु
	काष्ठा neigh_table *tbl = शून्य;

	चयन (family) अणु
	हाल AF_INET:
		tbl = neigh_tables[NEIGH_ARP_TABLE];
		अवरोध;
	हाल AF_INET6:
		tbl = neigh_tables[NEIGH_ND_TABLE];
		अवरोध;
	हाल AF_DECnet:
		tbl = neigh_tables[NEIGH_DN_TABLE];
		अवरोध;
	पूर्ण

	वापस tbl;
पूर्ण

स्थिर काष्ठा nla_policy nda_policy[NDA_MAX+1] = अणु
	[NDA_UNSPEC]		= अणु .strict_start_type = NDA_NH_ID पूर्ण,
	[NDA_DST]		= अणु .type = NLA_BINARY, .len = MAX_ADDR_LEN पूर्ण,
	[NDA_LLADDR]		= अणु .type = NLA_BINARY, .len = MAX_ADDR_LEN पूर्ण,
	[NDA_CACHEINFO]		= अणु .len = माप(काष्ठा nda_cacheinfo) पूर्ण,
	[NDA_PROBES]		= अणु .type = NLA_U32 पूर्ण,
	[NDA_VLAN]		= अणु .type = NLA_U16 पूर्ण,
	[NDA_PORT]		= अणु .type = NLA_U16 पूर्ण,
	[NDA_VNI]		= अणु .type = NLA_U32 पूर्ण,
	[NDA_IFINDEX]		= अणु .type = NLA_U32 पूर्ण,
	[NDA_MASTER]		= अणु .type = NLA_U32 पूर्ण,
	[NDA_PROTOCOL]		= अणु .type = NLA_U8 पूर्ण,
	[NDA_NH_ID]		= अणु .type = NLA_U32 पूर्ण,
	[NDA_FDB_EXT_ATTRS]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल पूर्णांक neigh_delete(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा ndmsg *ndm;
	काष्ठा nlattr *dst_attr;
	काष्ठा neigh_table *tbl;
	काष्ठा neighbour *neigh;
	काष्ठा net_device *dev = शून्य;
	पूर्णांक err = -EINVAL;

	ASSERT_RTNL();
	अगर (nlmsg_len(nlh) < माप(*ndm))
		जाओ out;

	dst_attr = nlmsg_find_attr(nlh, माप(*ndm), NDA_DST);
	अगर (!dst_attr) अणु
		NL_SET_ERR_MSG(extack, "Network address not specified");
		जाओ out;
	पूर्ण

	ndm = nlmsg_data(nlh);
	अगर (ndm->ndm_अगरindex) अणु
		dev = __dev_get_by_index(net, ndm->ndm_अगरindex);
		अगर (dev == शून्य) अणु
			err = -ENODEV;
			जाओ out;
		पूर्ण
	पूर्ण

	tbl = neigh_find_table(ndm->ndm_family);
	अगर (tbl == शून्य)
		वापस -EAFNOSUPPORT;

	अगर (nla_len(dst_attr) < (पूर्णांक)tbl->key_len) अणु
		NL_SET_ERR_MSG(extack, "Invalid network address");
		जाओ out;
	पूर्ण

	अगर (ndm->ndm_flags & NTF_PROXY) अणु
		err = pneigh_delete(tbl, net, nla_data(dst_attr), dev);
		जाओ out;
	पूर्ण

	अगर (dev == शून्य)
		जाओ out;

	neigh = neigh_lookup(tbl, nla_data(dst_attr), dev);
	अगर (neigh == शून्य) अणु
		err = -ENOENT;
		जाओ out;
	पूर्ण

	err = __neigh_update(neigh, शून्य, NUD_FAILED,
			     NEIGH_UPDATE_F_OVERRIDE | NEIGH_UPDATE_F_ADMIN,
			     NETLINK_CB(skb).portid, extack);
	ग_लिखो_lock_bh(&tbl->lock);
	neigh_release(neigh);
	neigh_हटाओ_one(neigh, tbl);
	ग_लिखो_unlock_bh(&tbl->lock);

out:
	वापस err;
पूर्ण

अटल पूर्णांक neigh_add(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		     काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक flags = NEIGH_UPDATE_F_ADMIN | NEIGH_UPDATE_F_OVERRIDE |
		NEIGH_UPDATE_F_OVERRIDE_ISROUTER;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा ndmsg *ndm;
	काष्ठा nlattr *tb[NDA_MAX+1];
	काष्ठा neigh_table *tbl;
	काष्ठा net_device *dev = शून्य;
	काष्ठा neighbour *neigh;
	व्योम *dst, *lladdr;
	u8 protocol = 0;
	पूर्णांक err;

	ASSERT_RTNL();
	err = nlmsg_parse_deprecated(nlh, माप(*ndm), tb, NDA_MAX,
				     nda_policy, extack);
	अगर (err < 0)
		जाओ out;

	err = -EINVAL;
	अगर (!tb[NDA_DST]) अणु
		NL_SET_ERR_MSG(extack, "Network address not specified");
		जाओ out;
	पूर्ण

	ndm = nlmsg_data(nlh);
	अगर (ndm->ndm_अगरindex) अणु
		dev = __dev_get_by_index(net, ndm->ndm_अगरindex);
		अगर (dev == शून्य) अणु
			err = -ENODEV;
			जाओ out;
		पूर्ण

		अगर (tb[NDA_LLADDR] && nla_len(tb[NDA_LLADDR]) < dev->addr_len) अणु
			NL_SET_ERR_MSG(extack, "Invalid link address");
			जाओ out;
		पूर्ण
	पूर्ण

	tbl = neigh_find_table(ndm->ndm_family);
	अगर (tbl == शून्य)
		वापस -EAFNOSUPPORT;

	अगर (nla_len(tb[NDA_DST]) < (पूर्णांक)tbl->key_len) अणु
		NL_SET_ERR_MSG(extack, "Invalid network address");
		जाओ out;
	पूर्ण

	dst = nla_data(tb[NDA_DST]);
	lladdr = tb[NDA_LLADDR] ? nla_data(tb[NDA_LLADDR]) : शून्य;

	अगर (tb[NDA_PROTOCOL])
		protocol = nla_get_u8(tb[NDA_PROTOCOL]);

	अगर (ndm->ndm_flags & NTF_PROXY) अणु
		काष्ठा pneigh_entry *pn;

		err = -ENOBUFS;
		pn = pneigh_lookup(tbl, net, dst, dev, 1);
		अगर (pn) अणु
			pn->flags = ndm->ndm_flags;
			अगर (protocol)
				pn->protocol = protocol;
			err = 0;
		पूर्ण
		जाओ out;
	पूर्ण

	अगर (!dev) अणु
		NL_SET_ERR_MSG(extack, "Device not specified");
		जाओ out;
	पूर्ण

	अगर (tbl->allow_add && !tbl->allow_add(dev, extack)) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	neigh = neigh_lookup(tbl, dst, dev);
	अगर (neigh == शून्य) अणु
		bool exempt_from_gc;

		अगर (!(nlh->nlmsg_flags & NLM_F_CREATE)) अणु
			err = -ENOENT;
			जाओ out;
		पूर्ण

		exempt_from_gc = ndm->ndm_state & NUD_PERMANENT ||
				 ndm->ndm_flags & NTF_EXT_LEARNED;
		neigh = ___neigh_create(tbl, dst, dev, exempt_from_gc, true);
		अगर (IS_ERR(neigh)) अणु
			err = PTR_ERR(neigh);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (nlh->nlmsg_flags & NLM_F_EXCL) अणु
			err = -EEXIST;
			neigh_release(neigh);
			जाओ out;
		पूर्ण

		अगर (!(nlh->nlmsg_flags & NLM_F_REPLACE))
			flags &= ~(NEIGH_UPDATE_F_OVERRIDE |
				   NEIGH_UPDATE_F_OVERRIDE_ISROUTER);
	पूर्ण

	अगर (protocol)
		neigh->protocol = protocol;

	अगर (ndm->ndm_flags & NTF_EXT_LEARNED)
		flags |= NEIGH_UPDATE_F_EXT_LEARNED;

	अगर (ndm->ndm_flags & NTF_ROUTER)
		flags |= NEIGH_UPDATE_F_ISROUTER;

	अगर (ndm->ndm_flags & NTF_USE) अणु
		neigh_event_send(neigh, शून्य);
		err = 0;
	पूर्ण अन्यथा
		err = __neigh_update(neigh, lladdr, ndm->ndm_state, flags,
				     NETLINK_CB(skb).portid, extack);

	neigh_release(neigh);

out:
	वापस err;
पूर्ण

अटल पूर्णांक neightbl_fill_parms(काष्ठा sk_buff *skb, काष्ठा neigh_parms *parms)
अणु
	काष्ठा nlattr *nest;

	nest = nla_nest_start_noflag(skb, NDTA_PARMS);
	अगर (nest == शून्य)
		वापस -ENOBUFS;

	अगर ((parms->dev &&
	     nla_put_u32(skb, NDTPA_IFINDEX, parms->dev->अगरindex)) ||
	    nla_put_u32(skb, NDTPA_REFCNT, refcount_पढ़ो(&parms->refcnt)) ||
	    nla_put_u32(skb, NDTPA_QUEUE_LENBYTES,
			NEIGH_VAR(parms, QUEUE_LEN_BYTES)) ||
	    /* approximative value क्रम deprecated QUEUE_LEN (in packets) */
	    nla_put_u32(skb, NDTPA_QUEUE_LEN,
			NEIGH_VAR(parms, QUEUE_LEN_BYTES) / SKB_TRUESIZE(ETH_FRAME_LEN)) ||
	    nla_put_u32(skb, NDTPA_PROXY_QLEN, NEIGH_VAR(parms, PROXY_QLEN)) ||
	    nla_put_u32(skb, NDTPA_APP_PROBES, NEIGH_VAR(parms, APP_PROBES)) ||
	    nla_put_u32(skb, NDTPA_UCAST_PROBES,
			NEIGH_VAR(parms, UCAST_PROBES)) ||
	    nla_put_u32(skb, NDTPA_MCAST_PROBES,
			NEIGH_VAR(parms, MCAST_PROBES)) ||
	    nla_put_u32(skb, NDTPA_MCAST_REPROBES,
			NEIGH_VAR(parms, MCAST_REPROBES)) ||
	    nla_put_msecs(skb, NDTPA_REACHABLE_TIME, parms->reachable_समय,
			  NDTPA_PAD) ||
	    nla_put_msecs(skb, NDTPA_BASE_REACHABLE_TIME,
			  NEIGH_VAR(parms, BASE_REACHABLE_TIME), NDTPA_PAD) ||
	    nla_put_msecs(skb, NDTPA_GC_STALETIME,
			  NEIGH_VAR(parms, GC_STALETIME), NDTPA_PAD) ||
	    nla_put_msecs(skb, NDTPA_DELAY_PROBE_TIME,
			  NEIGH_VAR(parms, DELAY_PROBE_TIME), NDTPA_PAD) ||
	    nla_put_msecs(skb, NDTPA_RETRANS_TIME,
			  NEIGH_VAR(parms, RETRANS_TIME), NDTPA_PAD) ||
	    nla_put_msecs(skb, NDTPA_ANYCAST_DELAY,
			  NEIGH_VAR(parms, ANYCAST_DELAY), NDTPA_PAD) ||
	    nla_put_msecs(skb, NDTPA_PROXY_DELAY,
			  NEIGH_VAR(parms, PROXY_DELAY), NDTPA_PAD) ||
	    nla_put_msecs(skb, NDTPA_LOCKTIME,
			  NEIGH_VAR(parms, LOCKTIME), NDTPA_PAD))
		जाओ nla_put_failure;
	वापस nla_nest_end(skb, nest);

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक neightbl_fill_info(काष्ठा sk_buff *skb, काष्ठा neigh_table *tbl,
			      u32 pid, u32 seq, पूर्णांक type, पूर्णांक flags)
अणु
	काष्ठा nlmsghdr *nlh;
	काष्ठा ndपंचांगsg *ndपंचांगsg;

	nlh = nlmsg_put(skb, pid, seq, type, माप(*ndपंचांगsg), flags);
	अगर (nlh == शून्य)
		वापस -EMSGSIZE;

	ndपंचांगsg = nlmsg_data(nlh);

	पढ़ो_lock_bh(&tbl->lock);
	ndपंचांगsg->ndपंचांग_family = tbl->family;
	ndपंचांगsg->ndपंचांग_pad1   = 0;
	ndपंचांगsg->ndपंचांग_pad2   = 0;

	अगर (nla_put_string(skb, NDTA_NAME, tbl->id) ||
	    nla_put_msecs(skb, NDTA_GC_INTERVAL, tbl->gc_पूर्णांकerval, NDTA_PAD) ||
	    nla_put_u32(skb, NDTA_THRESH1, tbl->gc_thresh1) ||
	    nla_put_u32(skb, NDTA_THRESH2, tbl->gc_thresh2) ||
	    nla_put_u32(skb, NDTA_THRESH3, tbl->gc_thresh3))
		जाओ nla_put_failure;
	अणु
		अचिन्हित दीर्घ now = jअगरfies;
		दीर्घ flush_delta = now - tbl->last_flush;
		दीर्घ अक्रम_delta = now - tbl->last_अक्रम;
		काष्ठा neigh_hash_table *nht;
		काष्ठा ndt_config ndc = अणु
			.ndtc_key_len		= tbl->key_len,
			.ndtc_entry_size	= tbl->entry_size,
			.ndtc_entries		= atomic_पढ़ो(&tbl->entries),
			.ndtc_last_flush	= jअगरfies_to_msecs(flush_delta),
			.ndtc_last_अक्रम		= jअगरfies_to_msecs(अक्रम_delta),
			.ndtc_proxy_qlen	= tbl->proxy_queue.qlen,
		पूर्ण;

		rcu_पढ़ो_lock_bh();
		nht = rcu_dereference_bh(tbl->nht);
		ndc.ndtc_hash_rnd = nht->hash_rnd[0];
		ndc.ndtc_hash_mask = ((1 << nht->hash_shअगरt) - 1);
		rcu_पढ़ो_unlock_bh();

		अगर (nla_put(skb, NDTA_CONFIG, माप(ndc), &ndc))
			जाओ nla_put_failure;
	पूर्ण

	अणु
		पूर्णांक cpu;
		काष्ठा ndt_stats ndst;

		स_रखो(&ndst, 0, माप(ndst));

		क्रम_each_possible_cpu(cpu) अणु
			काष्ठा neigh_statistics	*st;

			st = per_cpu_ptr(tbl->stats, cpu);
			ndst.ndts_allocs		+= st->allocs;
			ndst.ndts_destroys		+= st->destroys;
			ndst.ndts_hash_grows		+= st->hash_grows;
			ndst.ndts_res_failed		+= st->res_failed;
			ndst.ndts_lookups		+= st->lookups;
			ndst.ndts_hits			+= st->hits;
			ndst.ndts_rcv_probes_mcast	+= st->rcv_probes_mcast;
			ndst.ndts_rcv_probes_ucast	+= st->rcv_probes_ucast;
			ndst.ndts_periodic_gc_runs	+= st->periodic_gc_runs;
			ndst.ndts_क्रमced_gc_runs	+= st->क्रमced_gc_runs;
			ndst.ndts_table_fulls		+= st->table_fulls;
		पूर्ण

		अगर (nla_put_64bit(skb, NDTA_STATS, माप(ndst), &ndst,
				  NDTA_PAD))
			जाओ nla_put_failure;
	पूर्ण

	BUG_ON(tbl->parms.dev);
	अगर (neightbl_fill_parms(skb, &tbl->parms) < 0)
		जाओ nla_put_failure;

	पढ़ो_unlock_bh(&tbl->lock);
	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	पढ़ो_unlock_bh(&tbl->lock);
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक neightbl_fill_param_info(काष्ठा sk_buff *skb,
				    काष्ठा neigh_table *tbl,
				    काष्ठा neigh_parms *parms,
				    u32 pid, u32 seq, पूर्णांक type,
				    अचिन्हित पूर्णांक flags)
अणु
	काष्ठा ndपंचांगsg *ndपंचांगsg;
	काष्ठा nlmsghdr *nlh;

	nlh = nlmsg_put(skb, pid, seq, type, माप(*ndपंचांगsg), flags);
	अगर (nlh == शून्य)
		वापस -EMSGSIZE;

	ndपंचांगsg = nlmsg_data(nlh);

	पढ़ो_lock_bh(&tbl->lock);
	ndपंचांगsg->ndपंचांग_family = tbl->family;
	ndपंचांगsg->ndपंचांग_pad1   = 0;
	ndपंचांगsg->ndपंचांग_pad2   = 0;

	अगर (nla_put_string(skb, NDTA_NAME, tbl->id) < 0 ||
	    neightbl_fill_parms(skb, parms) < 0)
		जाओ errout;

	पढ़ो_unlock_bh(&tbl->lock);
	nlmsg_end(skb, nlh);
	वापस 0;
errout:
	पढ़ो_unlock_bh(&tbl->lock);
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल स्थिर काष्ठा nla_policy nl_neightbl_policy[NDTA_MAX+1] = अणु
	[NDTA_NAME]		= अणु .type = NLA_STRING पूर्ण,
	[NDTA_THRESH1]		= अणु .type = NLA_U32 पूर्ण,
	[NDTA_THRESH2]		= अणु .type = NLA_U32 पूर्ण,
	[NDTA_THRESH3]		= अणु .type = NLA_U32 पूर्ण,
	[NDTA_GC_INTERVAL]	= अणु .type = NLA_U64 पूर्ण,
	[NDTA_PARMS]		= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy nl_ntbl_parm_policy[NDTPA_MAX+1] = अणु
	[NDTPA_IFINDEX]			= अणु .type = NLA_U32 पूर्ण,
	[NDTPA_QUEUE_LEN]		= अणु .type = NLA_U32 पूर्ण,
	[NDTPA_PROXY_QLEN]		= अणु .type = NLA_U32 पूर्ण,
	[NDTPA_APP_PROBES]		= अणु .type = NLA_U32 पूर्ण,
	[NDTPA_UCAST_PROBES]		= अणु .type = NLA_U32 पूर्ण,
	[NDTPA_MCAST_PROBES]		= अणु .type = NLA_U32 पूर्ण,
	[NDTPA_MCAST_REPROBES]		= अणु .type = NLA_U32 पूर्ण,
	[NDTPA_BASE_REACHABLE_TIME]	= अणु .type = NLA_U64 पूर्ण,
	[NDTPA_GC_STALETIME]		= अणु .type = NLA_U64 पूर्ण,
	[NDTPA_DELAY_PROBE_TIME]	= अणु .type = NLA_U64 पूर्ण,
	[NDTPA_RETRANS_TIME]		= अणु .type = NLA_U64 पूर्ण,
	[NDTPA_ANYCAST_DELAY]		= अणु .type = NLA_U64 पूर्ण,
	[NDTPA_PROXY_DELAY]		= अणु .type = NLA_U64 पूर्ण,
	[NDTPA_LOCKTIME]		= अणु .type = NLA_U64 पूर्ण,
पूर्ण;

अटल पूर्णांक neightbl_set(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा neigh_table *tbl;
	काष्ठा ndपंचांगsg *ndपंचांगsg;
	काष्ठा nlattr *tb[NDTA_MAX+1];
	bool found = false;
	पूर्णांक err, tidx;

	err = nlmsg_parse_deprecated(nlh, माप(*ndपंचांगsg), tb, NDTA_MAX,
				     nl_neightbl_policy, extack);
	अगर (err < 0)
		जाओ errout;

	अगर (tb[NDTA_NAME] == शून्य) अणु
		err = -EINVAL;
		जाओ errout;
	पूर्ण

	ndपंचांगsg = nlmsg_data(nlh);

	क्रम (tidx = 0; tidx < NEIGH_NR_TABLES; tidx++) अणु
		tbl = neigh_tables[tidx];
		अगर (!tbl)
			जारी;
		अगर (ndपंचांगsg->ndपंचांग_family && tbl->family != ndपंचांगsg->ndपंचांग_family)
			जारी;
		अगर (nla_म_भेद(tb[NDTA_NAME], tbl->id) == 0) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस -ENOENT;

	/*
	 * We acquire tbl->lock to be nice to the periodic समयrs and
	 * make sure they always see a consistent set of values.
	 */
	ग_लिखो_lock_bh(&tbl->lock);

	अगर (tb[NDTA_PARMS]) अणु
		काष्ठा nlattr *tbp[NDTPA_MAX+1];
		काष्ठा neigh_parms *p;
		पूर्णांक i, अगरindex = 0;

		err = nla_parse_nested_deprecated(tbp, NDTPA_MAX,
						  tb[NDTA_PARMS],
						  nl_ntbl_parm_policy, extack);
		अगर (err < 0)
			जाओ errout_tbl_lock;

		अगर (tbp[NDTPA_IFINDEX])
			अगरindex = nla_get_u32(tbp[NDTPA_IFINDEX]);

		p = lookup_neigh_parms(tbl, net, अगरindex);
		अगर (p == शून्य) अणु
			err = -ENOENT;
			जाओ errout_tbl_lock;
		पूर्ण

		क्रम (i = 1; i <= NDTPA_MAX; i++) अणु
			अगर (tbp[i] == शून्य)
				जारी;

			चयन (i) अणु
			हाल NDTPA_QUEUE_LEN:
				NEIGH_VAR_SET(p, QUEUE_LEN_BYTES,
					      nla_get_u32(tbp[i]) *
					      SKB_TRUESIZE(ETH_FRAME_LEN));
				अवरोध;
			हाल NDTPA_QUEUE_LENBYTES:
				NEIGH_VAR_SET(p, QUEUE_LEN_BYTES,
					      nla_get_u32(tbp[i]));
				अवरोध;
			हाल NDTPA_PROXY_QLEN:
				NEIGH_VAR_SET(p, PROXY_QLEN,
					      nla_get_u32(tbp[i]));
				अवरोध;
			हाल NDTPA_APP_PROBES:
				NEIGH_VAR_SET(p, APP_PROBES,
					      nla_get_u32(tbp[i]));
				अवरोध;
			हाल NDTPA_UCAST_PROBES:
				NEIGH_VAR_SET(p, UCAST_PROBES,
					      nla_get_u32(tbp[i]));
				अवरोध;
			हाल NDTPA_MCAST_PROBES:
				NEIGH_VAR_SET(p, MCAST_PROBES,
					      nla_get_u32(tbp[i]));
				अवरोध;
			हाल NDTPA_MCAST_REPROBES:
				NEIGH_VAR_SET(p, MCAST_REPROBES,
					      nla_get_u32(tbp[i]));
				अवरोध;
			हाल NDTPA_BASE_REACHABLE_TIME:
				NEIGH_VAR_SET(p, BASE_REACHABLE_TIME,
					      nla_get_msecs(tbp[i]));
				/* update reachable_समय as well, otherwise, the change will
				 * only be effective after the next समय neigh_periodic_work
				 * decides to recompute it (can be multiple minutes)
				 */
				p->reachable_समय =
					neigh_अक्रम_reach_समय(NEIGH_VAR(p, BASE_REACHABLE_TIME));
				अवरोध;
			हाल NDTPA_GC_STALETIME:
				NEIGH_VAR_SET(p, GC_STALETIME,
					      nla_get_msecs(tbp[i]));
				अवरोध;
			हाल NDTPA_DELAY_PROBE_TIME:
				NEIGH_VAR_SET(p, DELAY_PROBE_TIME,
					      nla_get_msecs(tbp[i]));
				call_netevent_notअगरiers(NETEVENT_DELAY_PROBE_TIME_UPDATE, p);
				अवरोध;
			हाल NDTPA_RETRANS_TIME:
				NEIGH_VAR_SET(p, RETRANS_TIME,
					      nla_get_msecs(tbp[i]));
				अवरोध;
			हाल NDTPA_ANYCAST_DELAY:
				NEIGH_VAR_SET(p, ANYCAST_DELAY,
					      nla_get_msecs(tbp[i]));
				अवरोध;
			हाल NDTPA_PROXY_DELAY:
				NEIGH_VAR_SET(p, PROXY_DELAY,
					      nla_get_msecs(tbp[i]));
				अवरोध;
			हाल NDTPA_LOCKTIME:
				NEIGH_VAR_SET(p, LOCKTIME,
					      nla_get_msecs(tbp[i]));
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	err = -ENOENT;
	अगर ((tb[NDTA_THRESH1] || tb[NDTA_THRESH2] ||
	     tb[NDTA_THRESH3] || tb[NDTA_GC_INTERVAL]) &&
	    !net_eq(net, &init_net))
		जाओ errout_tbl_lock;

	अगर (tb[NDTA_THRESH1])
		tbl->gc_thresh1 = nla_get_u32(tb[NDTA_THRESH1]);

	अगर (tb[NDTA_THRESH2])
		tbl->gc_thresh2 = nla_get_u32(tb[NDTA_THRESH2]);

	अगर (tb[NDTA_THRESH3])
		tbl->gc_thresh3 = nla_get_u32(tb[NDTA_THRESH3]);

	अगर (tb[NDTA_GC_INTERVAL])
		tbl->gc_पूर्णांकerval = nla_get_msecs(tb[NDTA_GC_INTERVAL]);

	err = 0;

errout_tbl_lock:
	ग_लिखो_unlock_bh(&tbl->lock);
errout:
	वापस err;
पूर्ण

अटल पूर्णांक neightbl_valid_dump_info(स्थिर काष्ठा nlmsghdr *nlh,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ndपंचांगsg *ndपंचांग;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*ndपंचांग))) अणु
		NL_SET_ERR_MSG(extack, "Invalid header for neighbor table dump request");
		वापस -EINVAL;
	पूर्ण

	ndपंचांग = nlmsg_data(nlh);
	अगर (ndपंचांग->ndपंचांग_pad1  || ndपंचांग->ndपंचांग_pad2) अणु
		NL_SET_ERR_MSG(extack, "Invalid values in header for neighbor table dump request");
		वापस -EINVAL;
	पूर्ण

	अगर (nlmsg_attrlen(nlh, माप(*ndपंचांग))) अणु
		NL_SET_ERR_MSG(extack, "Invalid data after header in neighbor table dump request");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक neightbl_dump_info(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा nlmsghdr *nlh = cb->nlh;
	काष्ठा net *net = sock_net(skb->sk);
	पूर्णांक family, tidx, nidx = 0;
	पूर्णांक tbl_skip = cb->args[0];
	पूर्णांक neigh_skip = cb->args[1];
	काष्ठा neigh_table *tbl;

	अगर (cb->strict_check) अणु
		पूर्णांक err = neightbl_valid_dump_info(nlh, cb->extack);

		अगर (err < 0)
			वापस err;
	पूर्ण

	family = ((काष्ठा rtgenmsg *)nlmsg_data(nlh))->rtgen_family;

	क्रम (tidx = 0; tidx < NEIGH_NR_TABLES; tidx++) अणु
		काष्ठा neigh_parms *p;

		tbl = neigh_tables[tidx];
		अगर (!tbl)
			जारी;

		अगर (tidx < tbl_skip || (family && tbl->family != family))
			जारी;

		अगर (neightbl_fill_info(skb, tbl, NETLINK_CB(cb->skb).portid,
				       nlh->nlmsg_seq, RTM_NEWNEIGHTBL,
				       NLM_F_MULTI) < 0)
			अवरोध;

		nidx = 0;
		p = list_next_entry(&tbl->parms, list);
		list_क्रम_each_entry_from(p, &tbl->parms_list, list) अणु
			अगर (!net_eq(neigh_parms_net(p), net))
				जारी;

			अगर (nidx < neigh_skip)
				जाओ next;

			अगर (neightbl_fill_param_info(skb, tbl, p,
						     NETLINK_CB(cb->skb).portid,
						     nlh->nlmsg_seq,
						     RTM_NEWNEIGHTBL,
						     NLM_F_MULTI) < 0)
				जाओ out;
		next:
			nidx++;
		पूर्ण

		neigh_skip = 0;
	पूर्ण
out:
	cb->args[0] = tidx;
	cb->args[1] = nidx;

	वापस skb->len;
पूर्ण

अटल पूर्णांक neigh_fill_info(काष्ठा sk_buff *skb, काष्ठा neighbour *neigh,
			   u32 pid, u32 seq, पूर्णांक type, अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित दीर्घ now = jअगरfies;
	काष्ठा nda_cacheinfo ci;
	काष्ठा nlmsghdr *nlh;
	काष्ठा ndmsg *ndm;

	nlh = nlmsg_put(skb, pid, seq, type, माप(*ndm), flags);
	अगर (nlh == शून्य)
		वापस -EMSGSIZE;

	ndm = nlmsg_data(nlh);
	ndm->ndm_family	 = neigh->ops->family;
	ndm->ndm_pad1    = 0;
	ndm->ndm_pad2    = 0;
	ndm->ndm_flags	 = neigh->flags;
	ndm->ndm_type	 = neigh->type;
	ndm->ndm_अगरindex = neigh->dev->अगरindex;

	अगर (nla_put(skb, NDA_DST, neigh->tbl->key_len, neigh->primary_key))
		जाओ nla_put_failure;

	पढ़ो_lock_bh(&neigh->lock);
	ndm->ndm_state	 = neigh->nud_state;
	अगर (neigh->nud_state & NUD_VALID) अणु
		अक्षर haddr[MAX_ADDR_LEN];

		neigh_ha_snapshot(haddr, neigh, neigh->dev);
		अगर (nla_put(skb, NDA_LLADDR, neigh->dev->addr_len, haddr) < 0) अणु
			पढ़ो_unlock_bh(&neigh->lock);
			जाओ nla_put_failure;
		पूर्ण
	पूर्ण

	ci.ndm_used	 = jअगरfies_to_घड़ी_प्रकार(now - neigh->used);
	ci.ndm_confirmed = jअगरfies_to_घड़ी_प्रकार(now - neigh->confirmed);
	ci.ndm_updated	 = jअगरfies_to_घड़ी_प्रकार(now - neigh->updated);
	ci.ndm_refcnt	 = refcount_पढ़ो(&neigh->refcnt) - 1;
	पढ़ो_unlock_bh(&neigh->lock);

	अगर (nla_put_u32(skb, NDA_PROBES, atomic_पढ़ो(&neigh->probes)) ||
	    nla_put(skb, NDA_CACHEINFO, माप(ci), &ci))
		जाओ nla_put_failure;

	अगर (neigh->protocol && nla_put_u8(skb, NDA_PROTOCOL, neigh->protocol))
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक pneigh_fill_info(काष्ठा sk_buff *skb, काष्ठा pneigh_entry *pn,
			    u32 pid, u32 seq, पूर्णांक type, अचिन्हित पूर्णांक flags,
			    काष्ठा neigh_table *tbl)
अणु
	काष्ठा nlmsghdr *nlh;
	काष्ठा ndmsg *ndm;

	nlh = nlmsg_put(skb, pid, seq, type, माप(*ndm), flags);
	अगर (nlh == शून्य)
		वापस -EMSGSIZE;

	ndm = nlmsg_data(nlh);
	ndm->ndm_family	 = tbl->family;
	ndm->ndm_pad1    = 0;
	ndm->ndm_pad2    = 0;
	ndm->ndm_flags	 = pn->flags | NTF_PROXY;
	ndm->ndm_type	 = RTN_UNICAST;
	ndm->ndm_अगरindex = pn->dev ? pn->dev->अगरindex : 0;
	ndm->ndm_state	 = NUD_NONE;

	अगर (nla_put(skb, NDA_DST, tbl->key_len, pn->key))
		जाओ nla_put_failure;

	अगर (pn->protocol && nla_put_u8(skb, NDA_PROTOCOL, pn->protocol))
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल व्योम neigh_update_notअगरy(काष्ठा neighbour *neigh, u32 nlmsg_pid)
अणु
	call_netevent_notअगरiers(NETEVENT_NEIGH_UPDATE, neigh);
	__neigh_notअगरy(neigh, RTM_NEWNEIGH, 0, nlmsg_pid);
पूर्ण

अटल bool neigh_master_filtered(काष्ठा net_device *dev, पूर्णांक master_idx)
अणु
	काष्ठा net_device *master;

	अगर (!master_idx)
		वापस false;

	master = dev ? netdev_master_upper_dev_get(dev) : शून्य;
	अगर (!master || master->अगरindex != master_idx)
		वापस true;

	वापस false;
पूर्ण

अटल bool neigh_अगरindex_filtered(काष्ठा net_device *dev, पूर्णांक filter_idx)
अणु
	अगर (filter_idx && (!dev || dev->अगरindex != filter_idx))
		वापस true;

	वापस false;
पूर्ण

काष्ठा neigh_dump_filter अणु
	पूर्णांक master_idx;
	पूर्णांक dev_idx;
पूर्ण;

अटल पूर्णांक neigh_dump_table(काष्ठा neigh_table *tbl, काष्ठा sk_buff *skb,
			    काष्ठा netlink_callback *cb,
			    काष्ठा neigh_dump_filter *filter)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा neighbour *n;
	पूर्णांक rc, h, s_h = cb->args[1];
	पूर्णांक idx, s_idx = idx = cb->args[2];
	काष्ठा neigh_hash_table *nht;
	अचिन्हित पूर्णांक flags = NLM_F_MULTI;

	अगर (filter->dev_idx || filter->master_idx)
		flags |= NLM_F_DUMP_FILTERED;

	rcu_पढ़ो_lock_bh();
	nht = rcu_dereference_bh(tbl->nht);

	क्रम (h = s_h; h < (1 << nht->hash_shअगरt); h++) अणु
		अगर (h > s_h)
			s_idx = 0;
		क्रम (n = rcu_dereference_bh(nht->hash_buckets[h]), idx = 0;
		     n != शून्य;
		     n = rcu_dereference_bh(n->next)) अणु
			अगर (idx < s_idx || !net_eq(dev_net(n->dev), net))
				जाओ next;
			अगर (neigh_अगरindex_filtered(n->dev, filter->dev_idx) ||
			    neigh_master_filtered(n->dev, filter->master_idx))
				जाओ next;
			अगर (neigh_fill_info(skb, n, NETLINK_CB(cb->skb).portid,
					    cb->nlh->nlmsg_seq,
					    RTM_NEWNEIGH,
					    flags) < 0) अणु
				rc = -1;
				जाओ out;
			पूर्ण
next:
			idx++;
		पूर्ण
	पूर्ण
	rc = skb->len;
out:
	rcu_पढ़ो_unlock_bh();
	cb->args[1] = h;
	cb->args[2] = idx;
	वापस rc;
पूर्ण

अटल पूर्णांक pneigh_dump_table(काष्ठा neigh_table *tbl, काष्ठा sk_buff *skb,
			     काष्ठा netlink_callback *cb,
			     काष्ठा neigh_dump_filter *filter)
अणु
	काष्ठा pneigh_entry *n;
	काष्ठा net *net = sock_net(skb->sk);
	पूर्णांक rc, h, s_h = cb->args[3];
	पूर्णांक idx, s_idx = idx = cb->args[4];
	अचिन्हित पूर्णांक flags = NLM_F_MULTI;

	अगर (filter->dev_idx || filter->master_idx)
		flags |= NLM_F_DUMP_FILTERED;

	पढ़ो_lock_bh(&tbl->lock);

	क्रम (h = s_h; h <= PNEIGH_HASHMASK; h++) अणु
		अगर (h > s_h)
			s_idx = 0;
		क्रम (n = tbl->phash_buckets[h], idx = 0; n; n = n->next) अणु
			अगर (idx < s_idx || pneigh_net(n) != net)
				जाओ next;
			अगर (neigh_अगरindex_filtered(n->dev, filter->dev_idx) ||
			    neigh_master_filtered(n->dev, filter->master_idx))
				जाओ next;
			अगर (pneigh_fill_info(skb, n, NETLINK_CB(cb->skb).portid,
					    cb->nlh->nlmsg_seq,
					    RTM_NEWNEIGH, flags, tbl) < 0) अणु
				पढ़ो_unlock_bh(&tbl->lock);
				rc = -1;
				जाओ out;
			पूर्ण
		next:
			idx++;
		पूर्ण
	पूर्ण

	पढ़ो_unlock_bh(&tbl->lock);
	rc = skb->len;
out:
	cb->args[3] = h;
	cb->args[4] = idx;
	वापस rc;

पूर्ण

अटल पूर्णांक neigh_valid_dump_req(स्थिर काष्ठा nlmsghdr *nlh,
				bool strict_check,
				काष्ठा neigh_dump_filter *filter,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[NDA_MAX + 1];
	पूर्णांक err, i;

	अगर (strict_check) अणु
		काष्ठा ndmsg *ndm;

		अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*ndm))) अणु
			NL_SET_ERR_MSG(extack, "Invalid header for neighbor dump request");
			वापस -EINVAL;
		पूर्ण

		ndm = nlmsg_data(nlh);
		अगर (ndm->ndm_pad1  || ndm->ndm_pad2  || ndm->ndm_अगरindex ||
		    ndm->ndm_state || ndm->ndm_type) अणु
			NL_SET_ERR_MSG(extack, "Invalid values in header for neighbor dump request");
			वापस -EINVAL;
		पूर्ण

		अगर (ndm->ndm_flags & ~NTF_PROXY) अणु
			NL_SET_ERR_MSG(extack, "Invalid flags in header for neighbor dump request");
			वापस -EINVAL;
		पूर्ण

		err = nlmsg_parse_deprecated_strict(nlh, माप(काष्ठा ndmsg),
						    tb, NDA_MAX, nda_policy,
						    extack);
	पूर्ण अन्यथा अणु
		err = nlmsg_parse_deprecated(nlh, माप(काष्ठा ndmsg), tb,
					     NDA_MAX, nda_policy, extack);
	पूर्ण
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i <= NDA_MAX; ++i) अणु
		अगर (!tb[i])
			जारी;

		/* all new attributes should require strict_check */
		चयन (i) अणु
		हाल NDA_IFINDEX:
			filter->dev_idx = nla_get_u32(tb[i]);
			अवरोध;
		हाल NDA_MASTER:
			filter->master_idx = nla_get_u32(tb[i]);
			अवरोध;
		शेष:
			अगर (strict_check) अणु
				NL_SET_ERR_MSG(extack, "Unsupported attribute in neighbor dump request");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक neigh_dump_info(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा nlmsghdr *nlh = cb->nlh;
	काष्ठा neigh_dump_filter filter = अणुपूर्ण;
	काष्ठा neigh_table *tbl;
	पूर्णांक t, family, s_t;
	पूर्णांक proxy = 0;
	पूर्णांक err;

	family = ((काष्ठा rtgenmsg *)nlmsg_data(nlh))->rtgen_family;

	/* check क्रम full ndmsg काष्ठाure presence, family member is
	 * the same क्रम both काष्ठाures
	 */
	अगर (nlmsg_len(nlh) >= माप(काष्ठा ndmsg) &&
	    ((काष्ठा ndmsg *)nlmsg_data(nlh))->ndm_flags == NTF_PROXY)
		proxy = 1;

	err = neigh_valid_dump_req(nlh, cb->strict_check, &filter, cb->extack);
	अगर (err < 0 && cb->strict_check)
		वापस err;

	s_t = cb->args[0];

	क्रम (t = 0; t < NEIGH_NR_TABLES; t++) अणु
		tbl = neigh_tables[t];

		अगर (!tbl)
			जारी;
		अगर (t < s_t || (family && tbl->family != family))
			जारी;
		अगर (t > s_t)
			स_रखो(&cb->args[1], 0, माप(cb->args) -
						माप(cb->args[0]));
		अगर (proxy)
			err = pneigh_dump_table(tbl, skb, cb, &filter);
		अन्यथा
			err = neigh_dump_table(tbl, skb, cb, &filter);
		अगर (err < 0)
			अवरोध;
	पूर्ण

	cb->args[0] = t;
	वापस skb->len;
पूर्ण

अटल पूर्णांक neigh_valid_get_req(स्थिर काष्ठा nlmsghdr *nlh,
			       काष्ठा neigh_table **tbl,
			       व्योम **dst, पूर्णांक *dev_idx, u8 *ndm_flags,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[NDA_MAX + 1];
	काष्ठा ndmsg *ndm;
	पूर्णांक err, i;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*ndm))) अणु
		NL_SET_ERR_MSG(extack, "Invalid header for neighbor get request");
		वापस -EINVAL;
	पूर्ण

	ndm = nlmsg_data(nlh);
	अगर (ndm->ndm_pad1  || ndm->ndm_pad2  || ndm->ndm_state ||
	    ndm->ndm_type) अणु
		NL_SET_ERR_MSG(extack, "Invalid values in header for neighbor get request");
		वापस -EINVAL;
	पूर्ण

	अगर (ndm->ndm_flags & ~NTF_PROXY) अणु
		NL_SET_ERR_MSG(extack, "Invalid flags in header for neighbor get request");
		वापस -EINVAL;
	पूर्ण

	err = nlmsg_parse_deprecated_strict(nlh, माप(काष्ठा ndmsg), tb,
					    NDA_MAX, nda_policy, extack);
	अगर (err < 0)
		वापस err;

	*ndm_flags = ndm->ndm_flags;
	*dev_idx = ndm->ndm_अगरindex;
	*tbl = neigh_find_table(ndm->ndm_family);
	अगर (*tbl == शून्य) अणु
		NL_SET_ERR_MSG(extack, "Unsupported family in header for neighbor get request");
		वापस -EAFNOSUPPORT;
	पूर्ण

	क्रम (i = 0; i <= NDA_MAX; ++i) अणु
		अगर (!tb[i])
			जारी;

		चयन (i) अणु
		हाल NDA_DST:
			अगर (nla_len(tb[i]) != (पूर्णांक)(*tbl)->key_len) अणु
				NL_SET_ERR_MSG(extack, "Invalid network address in neighbor get request");
				वापस -EINVAL;
			पूर्ण
			*dst = nla_data(tb[i]);
			अवरोध;
		शेष:
			NL_SET_ERR_MSG(extack, "Unsupported attribute in neighbor get request");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत माप_प्रकार neigh_nlmsg_size(व्योम)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा ndmsg))
	       + nla_total_size(MAX_ADDR_LEN) /* NDA_DST */
	       + nla_total_size(MAX_ADDR_LEN) /* NDA_LLADDR */
	       + nla_total_size(माप(काष्ठा nda_cacheinfo))
	       + nla_total_size(4)  /* NDA_PROBES */
	       + nla_total_size(1); /* NDA_PROTOCOL */
पूर्ण

अटल पूर्णांक neigh_get_reply(काष्ठा net *net, काष्ठा neighbour *neigh,
			   u32 pid, u32 seq)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err = 0;

	skb = nlmsg_new(neigh_nlmsg_size(), GFP_KERNEL);
	अगर (!skb)
		वापस -ENOBUFS;

	err = neigh_fill_info(skb, neigh, pid, seq, RTM_NEWNEIGH, 0);
	अगर (err) अणु
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण

	err = rtnl_unicast(skb, net, pid);
errout:
	वापस err;
पूर्ण

अटल अंतरभूत माप_प्रकार pneigh_nlmsg_size(व्योम)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा ndmsg))
	       + nla_total_size(MAX_ADDR_LEN) /* NDA_DST */
	       + nla_total_size(1); /* NDA_PROTOCOL */
पूर्ण

अटल पूर्णांक pneigh_get_reply(काष्ठा net *net, काष्ठा pneigh_entry *neigh,
			    u32 pid, u32 seq, काष्ठा neigh_table *tbl)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err = 0;

	skb = nlmsg_new(pneigh_nlmsg_size(), GFP_KERNEL);
	अगर (!skb)
		वापस -ENOBUFS;

	err = pneigh_fill_info(skb, neigh, pid, seq, RTM_NEWNEIGH, 0, tbl);
	अगर (err) अणु
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण

	err = rtnl_unicast(skb, net, pid);
errout:
	वापस err;
पूर्ण

अटल पूर्णांक neigh_get(काष्ठा sk_buff *in_skb, काष्ठा nlmsghdr *nlh,
		     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(in_skb->sk);
	काष्ठा net_device *dev = शून्य;
	काष्ठा neigh_table *tbl = शून्य;
	काष्ठा neighbour *neigh;
	व्योम *dst = शून्य;
	u8 ndm_flags = 0;
	पूर्णांक dev_idx = 0;
	पूर्णांक err;

	err = neigh_valid_get_req(nlh, &tbl, &dst, &dev_idx, &ndm_flags,
				  extack);
	अगर (err < 0)
		वापस err;

	अगर (dev_idx) अणु
		dev = __dev_get_by_index(net, dev_idx);
		अगर (!dev) अणु
			NL_SET_ERR_MSG(extack, "Unknown device ifindex");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	अगर (!dst) अणु
		NL_SET_ERR_MSG(extack, "Network address not specified");
		वापस -EINVAL;
	पूर्ण

	अगर (ndm_flags & NTF_PROXY) अणु
		काष्ठा pneigh_entry *pn;

		pn = pneigh_lookup(tbl, net, dst, dev, 0);
		अगर (!pn) अणु
			NL_SET_ERR_MSG(extack, "Proxy neighbour entry not found");
			वापस -ENOENT;
		पूर्ण
		वापस pneigh_get_reply(net, pn, NETLINK_CB(in_skb).portid,
					nlh->nlmsg_seq, tbl);
	पूर्ण

	अगर (!dev) अणु
		NL_SET_ERR_MSG(extack, "No device specified");
		वापस -EINVAL;
	पूर्ण

	neigh = neigh_lookup(tbl, dst, dev);
	अगर (!neigh) अणु
		NL_SET_ERR_MSG(extack, "Neighbour entry not found");
		वापस -ENOENT;
	पूर्ण

	err = neigh_get_reply(net, neigh, NETLINK_CB(in_skb).portid,
			      nlh->nlmsg_seq);

	neigh_release(neigh);

	वापस err;
पूर्ण

व्योम neigh_क्रम_each(काष्ठा neigh_table *tbl, व्योम (*cb)(काष्ठा neighbour *, व्योम *), व्योम *cookie)
अणु
	पूर्णांक chain;
	काष्ठा neigh_hash_table *nht;

	rcu_पढ़ो_lock_bh();
	nht = rcu_dereference_bh(tbl->nht);

	पढ़ो_lock(&tbl->lock); /* aव्योम resizes */
	क्रम (chain = 0; chain < (1 << nht->hash_shअगरt); chain++) अणु
		काष्ठा neighbour *n;

		क्रम (n = rcu_dereference_bh(nht->hash_buckets[chain]);
		     n != शून्य;
		     n = rcu_dereference_bh(n->next))
			cb(n, cookie);
	पूर्ण
	पढ़ो_unlock(&tbl->lock);
	rcu_पढ़ो_unlock_bh();
पूर्ण
EXPORT_SYMBOL(neigh_क्रम_each);

/* The tbl->lock must be held as a ग_लिखोr and BH disabled. */
व्योम __neigh_क्रम_each_release(काष्ठा neigh_table *tbl,
			      पूर्णांक (*cb)(काष्ठा neighbour *))
अणु
	पूर्णांक chain;
	काष्ठा neigh_hash_table *nht;

	nht = rcu_dereference_रक्षित(tbl->nht,
					lockdep_is_held(&tbl->lock));
	क्रम (chain = 0; chain < (1 << nht->hash_shअगरt); chain++) अणु
		काष्ठा neighbour *n;
		काष्ठा neighbour __rcu **np;

		np = &nht->hash_buckets[chain];
		जबतक ((n = rcu_dereference_रक्षित(*np,
					lockdep_is_held(&tbl->lock))) != शून्य) अणु
			पूर्णांक release;

			ग_लिखो_lock(&n->lock);
			release = cb(n);
			अगर (release) अणु
				rcu_assign_poपूर्णांकer(*np,
					rcu_dereference_रक्षित(n->next,
						lockdep_is_held(&tbl->lock)));
				neigh_mark_dead(n);
			पूर्ण अन्यथा
				np = &n->next;
			ग_लिखो_unlock(&n->lock);
			अगर (release)
				neigh_cleanup_and_release(n);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__neigh_क्रम_each_release);

पूर्णांक neigh_xmit(पूर्णांक index, काष्ठा net_device *dev,
	       स्थिर व्योम *addr, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err = -EAFNOSUPPORT;
	अगर (likely(index < NEIGH_NR_TABLES)) अणु
		काष्ठा neigh_table *tbl;
		काष्ठा neighbour *neigh;

		tbl = neigh_tables[index];
		अगर (!tbl)
			जाओ out;
		rcu_पढ़ो_lock_bh();
		अगर (index == NEIGH_ARP_TABLE) अणु
			u32 key = *((u32 *)addr);

			neigh = __ipv4_neigh_lookup_noref(dev, key);
		पूर्ण अन्यथा अणु
			neigh = __neigh_lookup_noref(tbl, addr, dev);
		पूर्ण
		अगर (!neigh)
			neigh = __neigh_create(tbl, addr, dev, false);
		err = PTR_ERR(neigh);
		अगर (IS_ERR(neigh)) अणु
			rcu_पढ़ो_unlock_bh();
			जाओ out_kमुक्त_skb;
		पूर्ण
		err = neigh->output(neigh, skb);
		rcu_पढ़ो_unlock_bh();
	पूर्ण
	अन्यथा अगर (index == NEIGH_LINK_TABLE) अणु
		err = dev_hard_header(skb, dev, ntohs(skb->protocol),
				      addr, शून्य, skb->len);
		अगर (err < 0)
			जाओ out_kमुक्त_skb;
		err = dev_queue_xmit(skb);
	पूर्ण
out:
	वापस err;
out_kमुक्त_skb:
	kमुक्त_skb(skb);
	जाओ out;
पूर्ण
EXPORT_SYMBOL(neigh_xmit);

#अगर_घोषित CONFIG_PROC_FS

अटल काष्ठा neighbour *neigh_get_first(काष्ठा seq_file *seq)
अणु
	काष्ठा neigh_seq_state *state = seq->निजी;
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा neigh_hash_table *nht = state->nht;
	काष्ठा neighbour *n = शून्य;
	पूर्णांक bucket;

	state->flags &= ~NEIGH_SEQ_IS_PNEIGH;
	क्रम (bucket = 0; bucket < (1 << nht->hash_shअगरt); bucket++) अणु
		n = rcu_dereference_bh(nht->hash_buckets[bucket]);

		जबतक (n) अणु
			अगर (!net_eq(dev_net(n->dev), net))
				जाओ next;
			अगर (state->neigh_sub_iter) अणु
				loff_t fakep = 0;
				व्योम *v;

				v = state->neigh_sub_iter(state, n, &fakep);
				अगर (!v)
					जाओ next;
			पूर्ण
			अगर (!(state->flags & NEIGH_SEQ_SKIP_NOARP))
				अवरोध;
			अगर (n->nud_state & ~NUD_NOARP)
				अवरोध;
next:
			n = rcu_dereference_bh(n->next);
		पूर्ण

		अगर (n)
			अवरोध;
	पूर्ण
	state->bucket = bucket;

	वापस n;
पूर्ण

अटल काष्ठा neighbour *neigh_get_next(काष्ठा seq_file *seq,
					काष्ठा neighbour *n,
					loff_t *pos)
अणु
	काष्ठा neigh_seq_state *state = seq->निजी;
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा neigh_hash_table *nht = state->nht;

	अगर (state->neigh_sub_iter) अणु
		व्योम *v = state->neigh_sub_iter(state, n, pos);
		अगर (v)
			वापस n;
	पूर्ण
	n = rcu_dereference_bh(n->next);

	जबतक (1) अणु
		जबतक (n) अणु
			अगर (!net_eq(dev_net(n->dev), net))
				जाओ next;
			अगर (state->neigh_sub_iter) अणु
				व्योम *v = state->neigh_sub_iter(state, n, pos);
				अगर (v)
					वापस n;
				जाओ next;
			पूर्ण
			अगर (!(state->flags & NEIGH_SEQ_SKIP_NOARP))
				अवरोध;

			अगर (n->nud_state & ~NUD_NOARP)
				अवरोध;
next:
			n = rcu_dereference_bh(n->next);
		पूर्ण

		अगर (n)
			अवरोध;

		अगर (++state->bucket >= (1 << nht->hash_shअगरt))
			अवरोध;

		n = rcu_dereference_bh(nht->hash_buckets[state->bucket]);
	पूर्ण

	अगर (n && pos)
		--(*pos);
	वापस n;
पूर्ण

अटल काष्ठा neighbour *neigh_get_idx(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा neighbour *n = neigh_get_first(seq);

	अगर (n) अणु
		--(*pos);
		जबतक (*pos) अणु
			n = neigh_get_next(seq, n, pos);
			अगर (!n)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस *pos ? शून्य : n;
पूर्ण

अटल काष्ठा pneigh_entry *pneigh_get_first(काष्ठा seq_file *seq)
अणु
	काष्ठा neigh_seq_state *state = seq->निजी;
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा neigh_table *tbl = state->tbl;
	काष्ठा pneigh_entry *pn = शून्य;
	पूर्णांक bucket = state->bucket;

	state->flags |= NEIGH_SEQ_IS_PNEIGH;
	क्रम (bucket = 0; bucket <= PNEIGH_HASHMASK; bucket++) अणु
		pn = tbl->phash_buckets[bucket];
		जबतक (pn && !net_eq(pneigh_net(pn), net))
			pn = pn->next;
		अगर (pn)
			अवरोध;
	पूर्ण
	state->bucket = bucket;

	वापस pn;
पूर्ण

अटल काष्ठा pneigh_entry *pneigh_get_next(काष्ठा seq_file *seq,
					    काष्ठा pneigh_entry *pn,
					    loff_t *pos)
अणु
	काष्ठा neigh_seq_state *state = seq->निजी;
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा neigh_table *tbl = state->tbl;

	करो अणु
		pn = pn->next;
	पूर्ण जबतक (pn && !net_eq(pneigh_net(pn), net));

	जबतक (!pn) अणु
		अगर (++state->bucket > PNEIGH_HASHMASK)
			अवरोध;
		pn = tbl->phash_buckets[state->bucket];
		जबतक (pn && !net_eq(pneigh_net(pn), net))
			pn = pn->next;
		अगर (pn)
			अवरोध;
	पूर्ण

	अगर (pn && pos)
		--(*pos);

	वापस pn;
पूर्ण

अटल काष्ठा pneigh_entry *pneigh_get_idx(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा pneigh_entry *pn = pneigh_get_first(seq);

	अगर (pn) अणु
		--(*pos);
		जबतक (*pos) अणु
			pn = pneigh_get_next(seq, pn, pos);
			अगर (!pn)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस *pos ? शून्य : pn;
पूर्ण

अटल व्योम *neigh_get_idx_any(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा neigh_seq_state *state = seq->निजी;
	व्योम *rc;
	loff_t idxpos = *pos;

	rc = neigh_get_idx(seq, &idxpos);
	अगर (!rc && !(state->flags & NEIGH_SEQ_NEIGH_ONLY))
		rc = pneigh_get_idx(seq, &idxpos);

	वापस rc;
पूर्ण

व्योम *neigh_seq_start(काष्ठा seq_file *seq, loff_t *pos, काष्ठा neigh_table *tbl, अचिन्हित पूर्णांक neigh_seq_flags)
	__acquires(tbl->lock)
	__acquires(rcu_bh)
अणु
	काष्ठा neigh_seq_state *state = seq->निजी;

	state->tbl = tbl;
	state->bucket = 0;
	state->flags = (neigh_seq_flags & ~NEIGH_SEQ_IS_PNEIGH);

	rcu_पढ़ो_lock_bh();
	state->nht = rcu_dereference_bh(tbl->nht);
	पढ़ो_lock(&tbl->lock);

	वापस *pos ? neigh_get_idx_any(seq, pos) : SEQ_START_TOKEN;
पूर्ण
EXPORT_SYMBOL(neigh_seq_start);

व्योम *neigh_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा neigh_seq_state *state;
	व्योम *rc;

	अगर (v == SEQ_START_TOKEN) अणु
		rc = neigh_get_first(seq);
		जाओ out;
	पूर्ण

	state = seq->निजी;
	अगर (!(state->flags & NEIGH_SEQ_IS_PNEIGH)) अणु
		rc = neigh_get_next(seq, v, शून्य);
		अगर (rc)
			जाओ out;
		अगर (!(state->flags & NEIGH_SEQ_NEIGH_ONLY))
			rc = pneigh_get_first(seq);
	पूर्ण अन्यथा अणु
		BUG_ON(state->flags & NEIGH_SEQ_NEIGH_ONLY);
		rc = pneigh_get_next(seq, v, शून्य);
	पूर्ण
out:
	++(*pos);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(neigh_seq_next);

व्योम neigh_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(tbl->lock)
	__releases(rcu_bh)
अणु
	काष्ठा neigh_seq_state *state = seq->निजी;
	काष्ठा neigh_table *tbl = state->tbl;

	पढ़ो_unlock(&tbl->lock);
	rcu_पढ़ो_unlock_bh();
पूर्ण
EXPORT_SYMBOL(neigh_seq_stop);

/* statistics via seq_file */

अटल व्योम *neigh_stat_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा neigh_table *tbl = PDE_DATA(file_inode(seq->file));
	पूर्णांक cpu;

	अगर (*pos == 0)
		वापस SEQ_START_TOKEN;

	क्रम (cpu = *pos-1; cpu < nr_cpu_ids; ++cpu) अणु
		अगर (!cpu_possible(cpu))
			जारी;
		*pos = cpu+1;
		वापस per_cpu_ptr(tbl->stats, cpu);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम *neigh_stat_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा neigh_table *tbl = PDE_DATA(file_inode(seq->file));
	पूर्णांक cpu;

	क्रम (cpu = *pos; cpu < nr_cpu_ids; ++cpu) अणु
		अगर (!cpu_possible(cpu))
			जारी;
		*pos = cpu+1;
		वापस per_cpu_ptr(tbl->stats, cpu);
	पूर्ण
	(*pos)++;
	वापस शून्य;
पूर्ण

अटल व्योम neigh_stat_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु

पूर्ण

अटल पूर्णांक neigh_stat_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा neigh_table *tbl = PDE_DATA(file_inode(seq->file));
	काष्ठा neigh_statistics *st = v;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_म_लिखो(seq, "entries  allocs destroys hash_grows  lookups hits  res_failed  rcv_probes_mcast rcv_probes_ucast  periodic_gc_runs forced_gc_runs unresolved_discards table_fulls\n");
		वापस 0;
	पूर्ण

	seq_म_लिखो(seq, "%08x  %08lx %08lx %08lx  %08lx %08lx  %08lx  "
			"%08lx %08lx  %08lx %08lx %08lx %08lx\n",
		   atomic_पढ़ो(&tbl->entries),

		   st->allocs,
		   st->destroys,
		   st->hash_grows,

		   st->lookups,
		   st->hits,

		   st->res_failed,

		   st->rcv_probes_mcast,
		   st->rcv_probes_ucast,

		   st->periodic_gc_runs,
		   st->क्रमced_gc_runs,
		   st->unres_discards,
		   st->table_fulls
		   );

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations neigh_stat_seq_ops = अणु
	.start	= neigh_stat_seq_start,
	.next	= neigh_stat_seq_next,
	.stop	= neigh_stat_seq_stop,
	.show	= neigh_stat_seq_show,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PROC_FS */

अटल व्योम __neigh_notअगरy(काष्ठा neighbour *n, पूर्णांक type, पूर्णांक flags,
			   u32 pid)
अणु
	काष्ठा net *net = dev_net(n->dev);
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOBUFS;

	skb = nlmsg_new(neigh_nlmsg_size(), GFP_ATOMIC);
	अगर (skb == शून्य)
		जाओ errout;

	err = neigh_fill_info(skb, n, pid, 0, type, flags);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in neigh_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण
	rtnl_notअगरy(skb, net, 0, RTNLGRP_NEIGH, शून्य, GFP_ATOMIC);
	वापस;
errout:
	अगर (err < 0)
		rtnl_set_sk_err(net, RTNLGRP_NEIGH, err);
पूर्ण

व्योम neigh_app_ns(काष्ठा neighbour *n)
अणु
	__neigh_notअगरy(n, RTM_GETNEIGH, NLM_F_REQUEST, 0);
पूर्ण
EXPORT_SYMBOL(neigh_app_ns);

#अगर_घोषित CONFIG_SYSCTL
अटल पूर्णांक unres_qlen_max = पूर्णांक_उच्च / SKB_TRUESIZE(ETH_FRAME_LEN);

अटल पूर्णांक proc_unres_qlen(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
			   व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक size, ret;
	काष्ठा ctl_table पंचांगp = *ctl;

	पंचांगp.extra1 = SYSCTL_ZERO;
	पंचांगp.extra2 = &unres_qlen_max;
	पंचांगp.data = &size;

	size = *(पूर्णांक *)ctl->data / SKB_TRUESIZE(ETH_FRAME_LEN);
	ret = proc_करोपूर्णांकvec_minmax(&पंचांगp, ग_लिखो, buffer, lenp, ppos);

	अगर (ग_लिखो && !ret)
		*(पूर्णांक *)ctl->data = size * SKB_TRUESIZE(ETH_FRAME_LEN);
	वापस ret;
पूर्ण

अटल काष्ठा neigh_parms *neigh_get_dev_parms_rcu(काष्ठा net_device *dev,
						   पूर्णांक family)
अणु
	चयन (family) अणु
	हाल AF_INET:
		वापस __in_dev_arp_parms_get_rcu(dev);
	हाल AF_INET6:
		वापस __in6_dev_nd_parms_get_rcu(dev);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम neigh_copy_dflt_parms(काष्ठा net *net, काष्ठा neigh_parms *p,
				  पूर्णांक index)
अणु
	काष्ठा net_device *dev;
	पूर्णांक family = neigh_parms_family(p);

	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(net, dev) अणु
		काष्ठा neigh_parms *dst_p =
				neigh_get_dev_parms_rcu(dev, family);

		अगर (dst_p && !test_bit(index, dst_p->data_state))
			dst_p->data[index] = p->data[index];
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम neigh_proc_update(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो)
अणु
	काष्ठा net_device *dev = ctl->extra1;
	काष्ठा neigh_parms *p = ctl->extra2;
	काष्ठा net *net = neigh_parms_net(p);
	पूर्णांक index = (पूर्णांक *) ctl->data - p->data;

	अगर (!ग_लिखो)
		वापस;

	set_bit(index, p->data_state);
	अगर (index == NEIGH_VAR_DELAY_PROBE_TIME)
		call_netevent_notअगरiers(NETEVENT_DELAY_PROBE_TIME_UPDATE, p);
	अगर (!dev) /* शून्य dev means this is शेष value */
		neigh_copy_dflt_parms(net, p, index);
पूर्ण

अटल पूर्णांक neigh_proc_करोपूर्णांकvec_zero_पूर्णांकmax(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
					   व्योम *buffer, माप_प्रकार *lenp,
					   loff_t *ppos)
अणु
	काष्ठा ctl_table पंचांगp = *ctl;
	पूर्णांक ret;

	पंचांगp.extra1 = SYSCTL_ZERO;
	पंचांगp.extra2 = SYSCTL_पूर्णांक_उच्च;

	ret = proc_करोपूर्णांकvec_minmax(&पंचांगp, ग_लिखो, buffer, lenp, ppos);
	neigh_proc_update(ctl, ग_लिखो);
	वापस ret;
पूर्ण

पूर्णांक neigh_proc_करोपूर्णांकvec(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो, व्योम *buffer,
			माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret = proc_करोपूर्णांकvec(ctl, ग_लिखो, buffer, lenp, ppos);

	neigh_proc_update(ctl, ग_लिखो);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(neigh_proc_करोपूर्णांकvec);

पूर्णांक neigh_proc_करोपूर्णांकvec_jअगरfies(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो, व्योम *buffer,
				माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret = proc_करोपूर्णांकvec_jअगरfies(ctl, ग_लिखो, buffer, lenp, ppos);

	neigh_proc_update(ctl, ग_लिखो);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(neigh_proc_करोपूर्णांकvec_jअगरfies);

अटल पूर्णांक neigh_proc_करोपूर्णांकvec_userhz_jअगरfies(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
					      व्योम *buffer, माप_प्रकार *lenp,
					      loff_t *ppos)
अणु
	पूर्णांक ret = proc_करोपूर्णांकvec_userhz_jअगरfies(ctl, ग_लिखो, buffer, lenp, ppos);

	neigh_proc_update(ctl, ग_लिखो);
	वापस ret;
पूर्ण

पूर्णांक neigh_proc_करोपूर्णांकvec_ms_jअगरfies(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
				   व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret = proc_करोपूर्णांकvec_ms_jअगरfies(ctl, ग_लिखो, buffer, lenp, ppos);

	neigh_proc_update(ctl, ग_लिखो);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(neigh_proc_करोपूर्णांकvec_ms_jअगरfies);

अटल पूर्णांक neigh_proc_करोपूर्णांकvec_unres_qlen(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
					  व्योम *buffer, माप_प्रकार *lenp,
					  loff_t *ppos)
अणु
	पूर्णांक ret = proc_unres_qlen(ctl, ग_लिखो, buffer, lenp, ppos);

	neigh_proc_update(ctl, ग_लिखो);
	वापस ret;
पूर्ण

अटल पूर्णांक neigh_proc_base_reachable_समय(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
					  व्योम *buffer, माप_प्रकार *lenp,
					  loff_t *ppos)
अणु
	काष्ठा neigh_parms *p = ctl->extra2;
	पूर्णांक ret;

	अगर (म_भेद(ctl->procname, "base_reachable_time") == 0)
		ret = neigh_proc_करोपूर्णांकvec_jअगरfies(ctl, ग_लिखो, buffer, lenp, ppos);
	अन्यथा अगर (म_भेद(ctl->procname, "base_reachable_time_ms") == 0)
		ret = neigh_proc_करोपूर्णांकvec_ms_jअगरfies(ctl, ग_लिखो, buffer, lenp, ppos);
	अन्यथा
		ret = -1;

	अगर (ग_लिखो && ret == 0) अणु
		/* update reachable_समय as well, otherwise, the change will
		 * only be effective after the next समय neigh_periodic_work
		 * decides to recompute it
		 */
		p->reachable_समय =
			neigh_अक्रम_reach_समय(NEIGH_VAR(p, BASE_REACHABLE_TIME));
	पूर्ण
	वापस ret;
पूर्ण

#घोषणा NEIGH_PARMS_DATA_OFFSET(index)	\
	(&((काष्ठा neigh_parms *) 0)->data[index])

#घोषणा NEIGH_SYSCTL_ENTRY(attr, data_attr, name, mval, proc) \
	[NEIGH_VAR_ ## attr] = अणु \
		.procname	= name, \
		.data		= NEIGH_PARMS_DATA_OFFSET(NEIGH_VAR_ ## data_attr), \
		.maxlen		= माप(पूर्णांक), \
		.mode		= mval, \
		.proc_handler	= proc, \
	पूर्ण

#घोषणा NEIGH_SYSCTL_ZERO_INTMAX_ENTRY(attr, name) \
	NEIGH_SYSCTL_ENTRY(attr, attr, name, 0644, neigh_proc_करोपूर्णांकvec_zero_पूर्णांकmax)

#घोषणा NEIGH_SYSCTL_JIFFIES_ENTRY(attr, name) \
	NEIGH_SYSCTL_ENTRY(attr, attr, name, 0644, neigh_proc_करोपूर्णांकvec_jअगरfies)

#घोषणा NEIGH_SYSCTL_USERHZ_JIFFIES_ENTRY(attr, name) \
	NEIGH_SYSCTL_ENTRY(attr, attr, name, 0644, neigh_proc_करोपूर्णांकvec_userhz_jअगरfies)

#घोषणा NEIGH_SYSCTL_MS_JIFFIES_REUSED_ENTRY(attr, data_attr, name) \
	NEIGH_SYSCTL_ENTRY(attr, data_attr, name, 0644, neigh_proc_करोपूर्णांकvec_ms_jअगरfies)

#घोषणा NEIGH_SYSCTL_UNRES_QLEN_REUSED_ENTRY(attr, data_attr, name) \
	NEIGH_SYSCTL_ENTRY(attr, data_attr, name, 0644, neigh_proc_करोपूर्णांकvec_unres_qlen)

अटल काष्ठा neigh_sysctl_table अणु
	काष्ठा ctl_table_header *sysctl_header;
	काष्ठा ctl_table neigh_vars[NEIGH_VAR_MAX + 1];
पूर्ण neigh_sysctl_ढाँचा __पढ़ो_mostly = अणु
	.neigh_vars = अणु
		NEIGH_SYSCTL_ZERO_INTMAX_ENTRY(MCAST_PROBES, "mcast_solicit"),
		NEIGH_SYSCTL_ZERO_INTMAX_ENTRY(UCAST_PROBES, "ucast_solicit"),
		NEIGH_SYSCTL_ZERO_INTMAX_ENTRY(APP_PROBES, "app_solicit"),
		NEIGH_SYSCTL_ZERO_INTMAX_ENTRY(MCAST_REPROBES, "mcast_resolicit"),
		NEIGH_SYSCTL_USERHZ_JIFFIES_ENTRY(RETRANS_TIME, "retrans_time"),
		NEIGH_SYSCTL_JIFFIES_ENTRY(BASE_REACHABLE_TIME, "base_reachable_time"),
		NEIGH_SYSCTL_JIFFIES_ENTRY(DELAY_PROBE_TIME, "delay_first_probe_time"),
		NEIGH_SYSCTL_JIFFIES_ENTRY(GC_STALETIME, "gc_stale_time"),
		NEIGH_SYSCTL_ZERO_INTMAX_ENTRY(QUEUE_LEN_BYTES, "unres_qlen_bytes"),
		NEIGH_SYSCTL_ZERO_INTMAX_ENTRY(PROXY_QLEN, "proxy_qlen"),
		NEIGH_SYSCTL_USERHZ_JIFFIES_ENTRY(ANYCAST_DELAY, "anycast_delay"),
		NEIGH_SYSCTL_USERHZ_JIFFIES_ENTRY(PROXY_DELAY, "proxy_delay"),
		NEIGH_SYSCTL_USERHZ_JIFFIES_ENTRY(LOCKTIME, "locktime"),
		NEIGH_SYSCTL_UNRES_QLEN_REUSED_ENTRY(QUEUE_LEN, QUEUE_LEN_BYTES, "unres_qlen"),
		NEIGH_SYSCTL_MS_JIFFIES_REUSED_ENTRY(RETRANS_TIME_MS, RETRANS_TIME, "retrans_time_ms"),
		NEIGH_SYSCTL_MS_JIFFIES_REUSED_ENTRY(BASE_REACHABLE_TIME_MS, BASE_REACHABLE_TIME, "base_reachable_time_ms"),
		[NEIGH_VAR_GC_INTERVAL] = अणु
			.procname	= "gc_interval",
			.maxlen		= माप(पूर्णांक),
			.mode		= 0644,
			.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
		पूर्ण,
		[NEIGH_VAR_GC_THRESH1] = अणु
			.procname	= "gc_thresh1",
			.maxlen		= माप(पूर्णांक),
			.mode		= 0644,
			.extra1		= SYSCTL_ZERO,
			.extra2		= SYSCTL_पूर्णांक_उच्च,
			.proc_handler	= proc_करोपूर्णांकvec_minmax,
		पूर्ण,
		[NEIGH_VAR_GC_THRESH2] = अणु
			.procname	= "gc_thresh2",
			.maxlen		= माप(पूर्णांक),
			.mode		= 0644,
			.extra1		= SYSCTL_ZERO,
			.extra2		= SYSCTL_पूर्णांक_उच्च,
			.proc_handler	= proc_करोपूर्णांकvec_minmax,
		पूर्ण,
		[NEIGH_VAR_GC_THRESH3] = अणु
			.procname	= "gc_thresh3",
			.maxlen		= माप(पूर्णांक),
			.mode		= 0644,
			.extra1		= SYSCTL_ZERO,
			.extra2		= SYSCTL_पूर्णांक_उच्च,
			.proc_handler	= proc_करोपूर्णांकvec_minmax,
		पूर्ण,
		अणुपूर्ण,
	पूर्ण,
पूर्ण;

पूर्णांक neigh_sysctl_रेजिस्टर(काष्ठा net_device *dev, काष्ठा neigh_parms *p,
			  proc_handler *handler)
अणु
	पूर्णांक i;
	काष्ठा neigh_sysctl_table *t;
	स्थिर अक्षर *dev_name_source;
	अक्षर neigh_path[ माप("net//neigh/") + IFNAMSIZ + IFNAMSIZ ];
	अक्षर *p_name;

	t = kmemdup(&neigh_sysctl_ढाँचा, माप(*t), GFP_KERNEL);
	अगर (!t)
		जाओ err;

	क्रम (i = 0; i < NEIGH_VAR_GC_INTERVAL; i++) अणु
		t->neigh_vars[i].data += (दीर्घ) p;
		t->neigh_vars[i].extra1 = dev;
		t->neigh_vars[i].extra2 = p;
	पूर्ण

	अगर (dev) अणु
		dev_name_source = dev->name;
		/* Terminate the table early */
		स_रखो(&t->neigh_vars[NEIGH_VAR_GC_INTERVAL], 0,
		       माप(t->neigh_vars[NEIGH_VAR_GC_INTERVAL]));
	पूर्ण अन्यथा अणु
		काष्ठा neigh_table *tbl = p->tbl;
		dev_name_source = "default";
		t->neigh_vars[NEIGH_VAR_GC_INTERVAL].data = &tbl->gc_पूर्णांकerval;
		t->neigh_vars[NEIGH_VAR_GC_THRESH1].data = &tbl->gc_thresh1;
		t->neigh_vars[NEIGH_VAR_GC_THRESH2].data = &tbl->gc_thresh2;
		t->neigh_vars[NEIGH_VAR_GC_THRESH3].data = &tbl->gc_thresh3;
	पूर्ण

	अगर (handler) अणु
		/* RetransTime */
		t->neigh_vars[NEIGH_VAR_RETRANS_TIME].proc_handler = handler;
		/* ReachableTime */
		t->neigh_vars[NEIGH_VAR_BASE_REACHABLE_TIME].proc_handler = handler;
		/* RetransTime (in milliseconds)*/
		t->neigh_vars[NEIGH_VAR_RETRANS_TIME_MS].proc_handler = handler;
		/* ReachableTime (in milliseconds) */
		t->neigh_vars[NEIGH_VAR_BASE_REACHABLE_TIME_MS].proc_handler = handler;
	पूर्ण अन्यथा अणु
		/* Those handlers will update p->reachable_समय after
		 * base_reachable_समय(_ms) is set to ensure the new समयr starts being
		 * applied after the next neighbour update instead of रुकोing क्रम
		 * neigh_periodic_work to update its value (can be multiple minutes)
		 * So any handler that replaces them should करो this as well
		 */
		/* ReachableTime */
		t->neigh_vars[NEIGH_VAR_BASE_REACHABLE_TIME].proc_handler =
			neigh_proc_base_reachable_समय;
		/* ReachableTime (in milliseconds) */
		t->neigh_vars[NEIGH_VAR_BASE_REACHABLE_TIME_MS].proc_handler =
			neigh_proc_base_reachable_समय;
	पूर्ण

	/* Don't export sysctls to unprivileged users */
	अगर (neigh_parms_net(p)->user_ns != &init_user_ns)
		t->neigh_vars[0].procname = शून्य;

	चयन (neigh_parms_family(p)) अणु
	हाल AF_INET:
	      p_name = "ipv4";
	      अवरोध;
	हाल AF_INET6:
	      p_name = "ipv6";
	      अवरोध;
	शेष:
	      BUG();
	पूर्ण

	snम_लिखो(neigh_path, माप(neigh_path), "net/%s/neigh/%s",
		p_name, dev_name_source);
	t->sysctl_header =
		रेजिस्टर_net_sysctl(neigh_parms_net(p), neigh_path, t->neigh_vars);
	अगर (!t->sysctl_header)
		जाओ मुक्त;

	p->sysctl_table = t;
	वापस 0;

मुक्त:
	kमुक्त(t);
err:
	वापस -ENOBUFS;
पूर्ण
EXPORT_SYMBOL(neigh_sysctl_रेजिस्टर);

व्योम neigh_sysctl_unरेजिस्टर(काष्ठा neigh_parms *p)
अणु
	अगर (p->sysctl_table) अणु
		काष्ठा neigh_sysctl_table *t = p->sysctl_table;
		p->sysctl_table = शून्य;
		unरेजिस्टर_net_sysctl_table(t->sysctl_header);
		kमुक्त(t);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(neigh_sysctl_unरेजिस्टर);

#पूर्ण_अगर	/* CONFIG_SYSCTL */

अटल पूर्णांक __init neigh_init(व्योम)
अणु
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_NEWNEIGH, neigh_add, शून्य, 0);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_DELNEIGH, neigh_delete, शून्य, 0);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_GETNEIGH, neigh_get, neigh_dump_info, 0);

	rtnl_रेजिस्टर(PF_UNSPEC, RTM_GETNEIGHTBL, शून्य, neightbl_dump_info,
		      0);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_SETNEIGHTBL, neightbl_set, शून्य, 0);

	वापस 0;
पूर्ण

subsys_initcall(neigh_init);
