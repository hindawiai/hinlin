<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#समावेश "ratelimiter.h"
#समावेश <linux/siphash.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <net/ip.h>

अटल काष्ठा kmem_cache *entry_cache;
अटल hsiphash_key_t key;
अटल spinlock_t table_lock = __SPIN_LOCK_UNLOCKED("ratelimiter_table_lock");
अटल DEFINE_MUTEX(init_lock);
अटल u64 init_refcnt; /* Protected by init_lock, hence not atomic. */
अटल atomic_t total_entries = ATOMIC_INIT(0);
अटल अचिन्हित पूर्णांक max_entries, table_size;
अटल व्योम wg_ratelimiter_gc_entries(काष्ठा work_काष्ठा *);
अटल DECLARE_DEFERRABLE_WORK(gc_work, wg_ratelimiter_gc_entries);
अटल काष्ठा hlist_head *table_v4;
#अगर IS_ENABLED(CONFIG_IPV6)
अटल काष्ठा hlist_head *table_v6;
#पूर्ण_अगर

काष्ठा ratelimiter_entry अणु
	u64 last_समय_ns, tokens, ip;
	व्योम *net;
	spinlock_t lock;
	काष्ठा hlist_node hash;
	काष्ठा rcu_head rcu;
पूर्ण;

क्रमागत अणु
	PACKETS_PER_SECOND = 20,
	PACKETS_BURSTABLE = 5,
	PACKET_COST = NSEC_PER_SEC / PACKETS_PER_SECOND,
	TOKEN_MAX = PACKET_COST * PACKETS_BURSTABLE
पूर्ण;

अटल व्योम entry_मुक्त(काष्ठा rcu_head *rcu)
अणु
	kmem_cache_मुक्त(entry_cache,
			container_of(rcu, काष्ठा ratelimiter_entry, rcu));
	atomic_dec(&total_entries);
पूर्ण

अटल व्योम entry_uninit(काष्ठा ratelimiter_entry *entry)
अणु
	hlist_del_rcu(&entry->hash);
	call_rcu(&entry->rcu, entry_मुक्त);
पूर्ण

/* Calling this function with a शून्य work uninits all entries. */
अटल व्योम wg_ratelimiter_gc_entries(काष्ठा work_काष्ठा *work)
अणु
	स्थिर u64 now = kसमय_get_coarse_bootसमय_ns();
	काष्ठा ratelimiter_entry *entry;
	काष्ठा hlist_node *temp;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < table_size; ++i) अणु
		spin_lock(&table_lock);
		hlist_क्रम_each_entry_safe(entry, temp, &table_v4[i], hash) अणु
			अगर (unlikely(!work) ||
			    now - entry->last_समय_ns > NSEC_PER_SEC)
				entry_uninit(entry);
		पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
		hlist_क्रम_each_entry_safe(entry, temp, &table_v6[i], hash) अणु
			अगर (unlikely(!work) ||
			    now - entry->last_समय_ns > NSEC_PER_SEC)
				entry_uninit(entry);
		पूर्ण
#पूर्ण_अगर
		spin_unlock(&table_lock);
		अगर (likely(work))
			cond_resched();
	पूर्ण
	अगर (likely(work))
		queue_delayed_work(प्रणाली_घातer_efficient_wq, &gc_work, HZ);
पूर्ण

bool wg_ratelimiter_allow(काष्ठा sk_buff *skb, काष्ठा net *net)
अणु
	/* We only take the bottom half of the net poपूर्णांकer, so that we can hash
	 * 3 words in the end. This way, siphash's len param fits पूर्णांकo the final
	 * u32, and we करोn't incur an extra round.
	 */
	स्थिर u32 net_word = (अचिन्हित दीर्घ)net;
	काष्ठा ratelimiter_entry *entry;
	काष्ठा hlist_head *bucket;
	u64 ip;

	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		ip = (u64 __क्रमce)ip_hdr(skb)->saddr;
		bucket = &table_v4[hsiphash_2u32(net_word, ip, &key) &
				   (table_size - 1)];
	पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
		/* Only use 64 bits, so as to ratelimit the whole /64. */
		स_नकल(&ip, &ipv6_hdr(skb)->saddr, माप(ip));
		bucket = &table_v6[hsiphash_3u32(net_word, ip >> 32, ip, &key) &
				   (table_size - 1)];
	पूर्ण
#पूर्ण_अगर
	अन्यथा
		वापस false;
	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(entry, bucket, hash) अणु
		अगर (entry->net == net && entry->ip == ip) अणु
			u64 now, tokens;
			bool ret;
			/* Quasi-inspired by nft_limit.c, but this is actually a
			 * slightly dअगरferent algorithm. Namely, we incorporate
			 * the burst as part of the maximum tokens, rather than
			 * as part of the rate.
			 */
			spin_lock(&entry->lock);
			now = kसमय_get_coarse_bootसमय_ns();
			tokens = min_t(u64, TOKEN_MAX,
				       entry->tokens + now -
					       entry->last_समय_ns);
			entry->last_समय_ns = now;
			ret = tokens >= PACKET_COST;
			entry->tokens = ret ? tokens - PACKET_COST : tokens;
			spin_unlock(&entry->lock);
			rcu_पढ़ो_unlock();
			वापस ret;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (atomic_inc_वापस(&total_entries) > max_entries)
		जाओ err_oom;

	entry = kmem_cache_alloc(entry_cache, GFP_KERNEL);
	अगर (unlikely(!entry))
		जाओ err_oom;

	entry->net = net;
	entry->ip = ip;
	INIT_HLIST_NODE(&entry->hash);
	spin_lock_init(&entry->lock);
	entry->last_समय_ns = kसमय_get_coarse_bootसमय_ns();
	entry->tokens = TOKEN_MAX - PACKET_COST;
	spin_lock(&table_lock);
	hlist_add_head_rcu(&entry->hash, bucket);
	spin_unlock(&table_lock);
	वापस true;

err_oom:
	atomic_dec(&total_entries);
	वापस false;
पूर्ण

पूर्णांक wg_ratelimiter_init(व्योम)
अणु
	mutex_lock(&init_lock);
	अगर (++init_refcnt != 1)
		जाओ out;

	entry_cache = KMEM_CACHE(ratelimiter_entry, 0);
	अगर (!entry_cache)
		जाओ err;

	/* xt_hashlimit.c uses a slightly dअगरferent algorithm क्रम ratelimiting,
	 * but what it shares in common is that it uses a massive hashtable. So,
	 * we borrow their wisकरोm about good table sizes on dअगरferent प्रणालीs
	 * dependent on RAM. This calculation here comes from there.
	 */
	table_size = (totalram_pages() > (1U << 30) / PAGE_SIZE) ? 8192 :
		max_t(अचिन्हित दीर्घ, 16, roundup_घात_of_two(
			(totalram_pages() << PAGE_SHIFT) /
			(1U << 14) / माप(काष्ठा hlist_head)));
	max_entries = table_size * 8;

	table_v4 = kvzalloc(table_size * माप(*table_v4), GFP_KERNEL);
	अगर (unlikely(!table_v4))
		जाओ err_kmemcache;

#अगर IS_ENABLED(CONFIG_IPV6)
	table_v6 = kvzalloc(table_size * माप(*table_v6), GFP_KERNEL);
	अगर (unlikely(!table_v6)) अणु
		kvमुक्त(table_v4);
		जाओ err_kmemcache;
	पूर्ण
#पूर्ण_अगर

	queue_delayed_work(प्रणाली_घातer_efficient_wq, &gc_work, HZ);
	get_अक्रमom_bytes(&key, माप(key));
out:
	mutex_unlock(&init_lock);
	वापस 0;

err_kmemcache:
	kmem_cache_destroy(entry_cache);
err:
	--init_refcnt;
	mutex_unlock(&init_lock);
	वापस -ENOMEM;
पूर्ण

व्योम wg_ratelimiter_uninit(व्योम)
अणु
	mutex_lock(&init_lock);
	अगर (!init_refcnt || --init_refcnt)
		जाओ out;

	cancel_delayed_work_sync(&gc_work);
	wg_ratelimiter_gc_entries(शून्य);
	rcu_barrier();
	kvमुक्त(table_v4);
#अगर IS_ENABLED(CONFIG_IPV6)
	kvमुक्त(table_v6);
#पूर्ण_अगर
	kmem_cache_destroy(entry_cache);
out:
	mutex_unlock(&init_lock);
पूर्ण

#समावेश "selftest/ratelimiter.c"
