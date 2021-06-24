<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * net/sunrpc/cache.c
 *
 * Generic code क्रम various authentication-related caches
 * used by sunrpc clients and servers.
 *
 * Copyright (C) 2002 Neil Brown <neilb@cse.unsw.edu.au>
 */

#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/slab.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/kmod.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/string_helpers.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/poll.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/net.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pagemap.h>
#समावेश <यंत्र/ioctls.h>
#समावेश <linux/sunrpc/types.h>
#समावेश <linux/sunrpc/cache.h>
#समावेश <linux/sunrpc/stats.h>
#समावेश <linux/sunrpc/rpc_pipe_fs.h>
#समावेश <trace/events/sunrpc.h>
#समावेश "netns.h"

#घोषणा	 RPCDBG_FACILITY RPCDBG_CACHE

अटल bool cache_defer_req(काष्ठा cache_req *req, काष्ठा cache_head *item);
अटल व्योम cache_revisit_request(काष्ठा cache_head *item);

अटल व्योम cache_init(काष्ठा cache_head *h, काष्ठा cache_detail *detail)
अणु
	समय64_t now = seconds_since_boot();
	INIT_HLIST_NODE(&h->cache_list);
	h->flags = 0;
	kref_init(&h->ref);
	h->expiry_समय = now + CACHE_NEW_EXPIRY;
	अगर (now <= detail->flush_समय)
		/* ensure it isn't alपढ़ोy expired */
		now = detail->flush_समय + 1;
	h->last_refresh = now;
पूर्ण

अटल व्योम cache_fresh_unlocked(काष्ठा cache_head *head,
				काष्ठा cache_detail *detail);

अटल काष्ठा cache_head *sunrpc_cache_find_rcu(काष्ठा cache_detail *detail,
						काष्ठा cache_head *key,
						पूर्णांक hash)
अणु
	काष्ठा hlist_head *head = &detail->hash_table[hash];
	काष्ठा cache_head *पंचांगp;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(पंचांगp, head, cache_list) अणु
		अगर (!detail->match(पंचांगp, key))
			जारी;
		अगर (test_bit(CACHE_VALID, &पंचांगp->flags) &&
		    cache_is_expired(detail, पंचांगp))
			जारी;
		पंचांगp = cache_get_rcu(पंचांगp);
		rcu_पढ़ो_unlock();
		वापस पंचांगp;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस शून्य;
पूर्ण

अटल व्योम sunrpc_begin_cache_हटाओ_entry(काष्ठा cache_head *ch,
					    काष्ठा cache_detail *cd)
अणु
	/* Must be called under cd->hash_lock */
	hlist_del_init_rcu(&ch->cache_list);
	set_bit(CACHE_CLEANED, &ch->flags);
	cd->entries --;
पूर्ण

अटल व्योम sunrpc_end_cache_हटाओ_entry(काष्ठा cache_head *ch,
					  काष्ठा cache_detail *cd)
अणु
	cache_fresh_unlocked(ch, cd);
	cache_put(ch, cd);
पूर्ण

अटल काष्ठा cache_head *sunrpc_cache_add_entry(काष्ठा cache_detail *detail,
						 काष्ठा cache_head *key,
						 पूर्णांक hash)
अणु
	काष्ठा cache_head *new, *पंचांगp, *मुक्तme = शून्य;
	काष्ठा hlist_head *head = &detail->hash_table[hash];

	new = detail->alloc();
	अगर (!new)
		वापस शून्य;
	/* must fully initialise 'new', अन्यथा
	 * we might get lose अगर we need to
	 * cache_put it soon.
	 */
	cache_init(new, detail);
	detail->init(new, key);

	spin_lock(&detail->hash_lock);

	/* check अगर entry appeared जबतक we slept */
	hlist_क्रम_each_entry_rcu(पंचांगp, head, cache_list,
				 lockdep_is_held(&detail->hash_lock)) अणु
		अगर (!detail->match(पंचांगp, key))
			जारी;
		अगर (test_bit(CACHE_VALID, &पंचांगp->flags) &&
		    cache_is_expired(detail, पंचांगp)) अणु
			sunrpc_begin_cache_हटाओ_entry(पंचांगp, detail);
			trace_cache_entry_expired(detail, पंचांगp);
			मुक्तme = पंचांगp;
			अवरोध;
		पूर्ण
		cache_get(पंचांगp);
		spin_unlock(&detail->hash_lock);
		cache_put(new, detail);
		वापस पंचांगp;
	पूर्ण

	hlist_add_head_rcu(&new->cache_list, head);
	detail->entries++;
	cache_get(new);
	spin_unlock(&detail->hash_lock);

	अगर (मुक्तme)
		sunrpc_end_cache_हटाओ_entry(मुक्तme, detail);
	वापस new;
पूर्ण

काष्ठा cache_head *sunrpc_cache_lookup_rcu(काष्ठा cache_detail *detail,
					   काष्ठा cache_head *key, पूर्णांक hash)
अणु
	काष्ठा cache_head *ret;

	ret = sunrpc_cache_find_rcu(detail, key, hash);
	अगर (ret)
		वापस ret;
	/* Didn't find anything, insert an empty entry */
	वापस sunrpc_cache_add_entry(detail, key, hash);
पूर्ण
EXPORT_SYMBOL_GPL(sunrpc_cache_lookup_rcu);

अटल व्योम cache_dequeue(काष्ठा cache_detail *detail, काष्ठा cache_head *ch);

अटल व्योम cache_fresh_locked(काष्ठा cache_head *head, समय64_t expiry,
			       काष्ठा cache_detail *detail)
अणु
	समय64_t now = seconds_since_boot();
	अगर (now <= detail->flush_समय)
		/* ensure it isn't immediately treated as expired */
		now = detail->flush_समय + 1;
	head->expiry_समय = expiry;
	head->last_refresh = now;
	smp_wmb(); /* paired with smp_rmb() in cache_is_valid() */
	set_bit(CACHE_VALID, &head->flags);
पूर्ण

अटल व्योम cache_fresh_unlocked(काष्ठा cache_head *head,
				 काष्ठा cache_detail *detail)
अणु
	अगर (test_and_clear_bit(CACHE_PENDING, &head->flags)) अणु
		cache_revisit_request(head);
		cache_dequeue(detail, head);
	पूर्ण
पूर्ण

अटल व्योम cache_make_negative(काष्ठा cache_detail *detail,
				काष्ठा cache_head *h)
अणु
	set_bit(CACHE_NEGATIVE, &h->flags);
	trace_cache_entry_make_negative(detail, h);
पूर्ण

अटल व्योम cache_entry_update(काष्ठा cache_detail *detail,
			       काष्ठा cache_head *h,
			       काष्ठा cache_head *new)
अणु
	अगर (!test_bit(CACHE_NEGATIVE, &new->flags)) अणु
		detail->update(h, new);
		trace_cache_entry_update(detail, h);
	पूर्ण अन्यथा अणु
		cache_make_negative(detail, h);
	पूर्ण
पूर्ण

काष्ठा cache_head *sunrpc_cache_update(काष्ठा cache_detail *detail,
				       काष्ठा cache_head *new, काष्ठा cache_head *old, पूर्णांक hash)
अणु
	/* The 'old' entry is to be replaced by 'new'.
	 * If 'old' is not VALID, we update it directly,
	 * otherwise we need to replace it
	 */
	काष्ठा cache_head *पंचांगp;

	अगर (!test_bit(CACHE_VALID, &old->flags)) अणु
		spin_lock(&detail->hash_lock);
		अगर (!test_bit(CACHE_VALID, &old->flags)) अणु
			cache_entry_update(detail, old, new);
			cache_fresh_locked(old, new->expiry_समय, detail);
			spin_unlock(&detail->hash_lock);
			cache_fresh_unlocked(old, detail);
			वापस old;
		पूर्ण
		spin_unlock(&detail->hash_lock);
	पूर्ण
	/* We need to insert a new entry */
	पंचांगp = detail->alloc();
	अगर (!पंचांगp) अणु
		cache_put(old, detail);
		वापस शून्य;
	पूर्ण
	cache_init(पंचांगp, detail);
	detail->init(पंचांगp, old);

	spin_lock(&detail->hash_lock);
	cache_entry_update(detail, पंचांगp, new);
	hlist_add_head(&पंचांगp->cache_list, &detail->hash_table[hash]);
	detail->entries++;
	cache_get(पंचांगp);
	cache_fresh_locked(पंचांगp, new->expiry_समय, detail);
	cache_fresh_locked(old, 0, detail);
	spin_unlock(&detail->hash_lock);
	cache_fresh_unlocked(पंचांगp, detail);
	cache_fresh_unlocked(old, detail);
	cache_put(old, detail);
	वापस पंचांगp;
पूर्ण
EXPORT_SYMBOL_GPL(sunrpc_cache_update);

अटल अंतरभूत पूर्णांक cache_is_valid(काष्ठा cache_head *h)
अणु
	अगर (!test_bit(CACHE_VALID, &h->flags))
		वापस -EAGAIN;
	अन्यथा अणु
		/* entry is valid */
		अगर (test_bit(CACHE_NEGATIVE, &h->flags))
			वापस -ENOENT;
		अन्यथा अणु
			/*
			 * In combination with ग_लिखो barrier in
			 * sunrpc_cache_update, ensures that anyone
			 * using the cache entry after this sees the
			 * updated contents:
			 */
			smp_rmb();
			वापस 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक try_to_negate_entry(काष्ठा cache_detail *detail, काष्ठा cache_head *h)
अणु
	पूर्णांक rv;

	spin_lock(&detail->hash_lock);
	rv = cache_is_valid(h);
	अगर (rv == -EAGAIN) अणु
		cache_make_negative(detail, h);
		cache_fresh_locked(h, seconds_since_boot()+CACHE_NEW_EXPIRY,
				   detail);
		rv = -ENOENT;
	पूर्ण
	spin_unlock(&detail->hash_lock);
	cache_fresh_unlocked(h, detail);
	वापस rv;
पूर्ण

/*
 * This is the generic cache management routine क्रम all
 * the authentication caches.
 * It checks the currency of a cache item and will (later)
 * initiate an upcall to fill it अगर needed.
 *
 *
 * Returns 0 अगर the cache_head can be used, or cache_माला_दो it and वापसs
 * -EAGAIN अगर upcall is pending and request has been queued
 * -ETIMEDOUT अगर upcall failed or request could not be queue or
 *           upcall completed but item is still invalid (implying that
 *           the cache item has been replaced with a newer one).
 * -ENOENT अगर cache entry was negative
 */
पूर्णांक cache_check(काष्ठा cache_detail *detail,
		    काष्ठा cache_head *h, काष्ठा cache_req *rqstp)
अणु
	पूर्णांक rv;
	समय64_t refresh_age, age;

	/* First decide वापस status as best we can */
	rv = cache_is_valid(h);

	/* now see अगर we want to start an upcall */
	refresh_age = (h->expiry_समय - h->last_refresh);
	age = seconds_since_boot() - h->last_refresh;

	अगर (rqstp == शून्य) अणु
		अगर (rv == -EAGAIN)
			rv = -ENOENT;
	पूर्ण अन्यथा अगर (rv == -EAGAIN ||
		   (h->expiry_समय != 0 && age > refresh_age/2)) अणु
		dprपूर्णांकk("RPC:       Want update, refage=%lld, age=%lld\n",
				refresh_age, age);
		चयन (detail->cache_upcall(detail, h)) अणु
		हाल -EINVAL:
			rv = try_to_negate_entry(detail, h);
			अवरोध;
		हाल -EAGAIN:
			cache_fresh_unlocked(h, detail);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (rv == -EAGAIN) अणु
		अगर (!cache_defer_req(rqstp, h)) अणु
			/*
			 * Request was not deferred; handle it as best
			 * we can ourselves:
			 */
			rv = cache_is_valid(h);
			अगर (rv == -EAGAIN)
				rv = -ETIMEDOUT;
		पूर्ण
	पूर्ण
	अगर (rv)
		cache_put(h, detail);
	वापस rv;
पूर्ण
EXPORT_SYMBOL_GPL(cache_check);

/*
 * caches need to be periodically cleaned.
 * For this we मुख्यtain a list of cache_detail and
 * a current poपूर्णांकer पूर्णांकo that list and पूर्णांकo the table
 * क्रम that entry.
 *
 * Each समय cache_clean is called it finds the next non-empty entry
 * in the current table and walks the list in that entry
 * looking क्रम entries that can be हटाओd.
 *
 * An entry माला_लो हटाओd अगर:
 * - The expiry is beक्रमe current समय
 * - The last_refresh समय is beक्रमe the flush_समय क्रम that cache
 *
 * later we might drop old entries with non-NEVER expiry अगर that table
 * is getting 'full' for some definition of 'full'
 *
 * The question of "how often to scan a table" is an पूर्णांकeresting one
 * and is answered in part by the use of the "nextcheck" field in the
 * cache_detail.
 * When a scan of a table begins, the nextcheck field is set to a समय
 * that is well पूर्णांकo the future.
 * While scanning, अगर an expiry समय is found that is earlier than the
 * current nextcheck समय, nextcheck is set to that expiry समय.
 * If the flush_समय is ever set to a समय earlier than the nextcheck
 * समय, the nextcheck समय is then set to that flush_समय.
 *
 * A table is then only scanned अगर the current समय is at least
 * the nextcheck समय.
 *
 */

अटल LIST_HEAD(cache_list);
अटल DEFINE_SPINLOCK(cache_list_lock);
अटल काष्ठा cache_detail *current_detail;
अटल पूर्णांक current_index;

अटल व्योम करो_cache_clean(काष्ठा work_काष्ठा *work);
अटल काष्ठा delayed_work cache_cleaner;

व्योम sunrpc_init_cache_detail(काष्ठा cache_detail *cd)
अणु
	spin_lock_init(&cd->hash_lock);
	INIT_LIST_HEAD(&cd->queue);
	spin_lock(&cache_list_lock);
	cd->nextcheck = 0;
	cd->entries = 0;
	atomic_set(&cd->ग_लिखोrs, 0);
	cd->last_बंद = 0;
	cd->last_warn = -1;
	list_add(&cd->others, &cache_list);
	spin_unlock(&cache_list_lock);

	/* start the cleaning process */
	queue_delayed_work(प्रणाली_घातer_efficient_wq, &cache_cleaner, 0);
पूर्ण
EXPORT_SYMBOL_GPL(sunrpc_init_cache_detail);

व्योम sunrpc_destroy_cache_detail(काष्ठा cache_detail *cd)
अणु
	cache_purge(cd);
	spin_lock(&cache_list_lock);
	spin_lock(&cd->hash_lock);
	अगर (current_detail == cd)
		current_detail = शून्य;
	list_del_init(&cd->others);
	spin_unlock(&cd->hash_lock);
	spin_unlock(&cache_list_lock);
	अगर (list_empty(&cache_list)) अणु
		/* module must be being unloaded so its safe to समाप्त the worker */
		cancel_delayed_work_sync(&cache_cleaner);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(sunrpc_destroy_cache_detail);

/* clean cache tries to find something to clean
 * and cleans it.
 * It वापसs 1 अगर it cleaned something,
 *            0 अगर it didn't find anything this समय
 *           -1 अगर it fell off the end of the list.
 */
अटल पूर्णांक cache_clean(व्योम)
अणु
	पूर्णांक rv = 0;
	काष्ठा list_head *next;

	spin_lock(&cache_list_lock);

	/* find a suitable table अगर we करोn't alपढ़ोy have one */
	जबतक (current_detail == शून्य ||
	    current_index >= current_detail->hash_size) अणु
		अगर (current_detail)
			next = current_detail->others.next;
		अन्यथा
			next = cache_list.next;
		अगर (next == &cache_list) अणु
			current_detail = शून्य;
			spin_unlock(&cache_list_lock);
			वापस -1;
		पूर्ण
		current_detail = list_entry(next, काष्ठा cache_detail, others);
		अगर (current_detail->nextcheck > seconds_since_boot())
			current_index = current_detail->hash_size;
		अन्यथा अणु
			current_index = 0;
			current_detail->nextcheck = seconds_since_boot()+30*60;
		पूर्ण
	पूर्ण

	/* find a non-empty bucket in the table */
	जबतक (current_detail &&
	       current_index < current_detail->hash_size &&
	       hlist_empty(&current_detail->hash_table[current_index]))
		current_index++;

	/* find a cleanable entry in the bucket and clean it, or set to next bucket */

	अगर (current_detail && current_index < current_detail->hash_size) अणु
		काष्ठा cache_head *ch = शून्य;
		काष्ठा cache_detail *d;
		काष्ठा hlist_head *head;
		काष्ठा hlist_node *पंचांगp;

		spin_lock(&current_detail->hash_lock);

		/* Ok, now to clean this stअक्रम */

		head = &current_detail->hash_table[current_index];
		hlist_क्रम_each_entry_safe(ch, पंचांगp, head, cache_list) अणु
			अगर (current_detail->nextcheck > ch->expiry_समय)
				current_detail->nextcheck = ch->expiry_समय+1;
			अगर (!cache_is_expired(current_detail, ch))
				जारी;

			sunrpc_begin_cache_हटाओ_entry(ch, current_detail);
			trace_cache_entry_expired(current_detail, ch);
			rv = 1;
			अवरोध;
		पूर्ण

		spin_unlock(&current_detail->hash_lock);
		d = current_detail;
		अगर (!ch)
			current_index ++;
		spin_unlock(&cache_list_lock);
		अगर (ch)
			sunrpc_end_cache_हटाओ_entry(ch, d);
	पूर्ण अन्यथा
		spin_unlock(&cache_list_lock);

	वापस rv;
पूर्ण

/*
 * We want to regularly clean the cache, so we need to schedule some work ...
 */
अटल व्योम करो_cache_clean(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक delay;

	अगर (list_empty(&cache_list))
		वापस;

	अगर (cache_clean() == -1)
		delay = round_jअगरfies_relative(30*HZ);
	अन्यथा
		delay = 5;

	queue_delayed_work(प्रणाली_घातer_efficient_wq, &cache_cleaner, delay);
पूर्ण


/*
 * Clean all caches promptly.  This just calls cache_clean
 * repeatedly until we are sure that every cache has had a chance to
 * be fully cleaned
 */
व्योम cache_flush(व्योम)
अणु
	जबतक (cache_clean() != -1)
		cond_resched();
	जबतक (cache_clean() != -1)
		cond_resched();
पूर्ण
EXPORT_SYMBOL_GPL(cache_flush);

व्योम cache_purge(काष्ठा cache_detail *detail)
अणु
	काष्ठा cache_head *ch = शून्य;
	काष्ठा hlist_head *head = शून्य;
	पूर्णांक i = 0;

	spin_lock(&detail->hash_lock);
	अगर (!detail->entries) अणु
		spin_unlock(&detail->hash_lock);
		वापस;
	पूर्ण

	dprपूर्णांकk("RPC: %d entries in %s cache\n", detail->entries, detail->name);
	क्रम (i = 0; i < detail->hash_size; i++) अणु
		head = &detail->hash_table[i];
		जबतक (!hlist_empty(head)) अणु
			ch = hlist_entry(head->first, काष्ठा cache_head,
					 cache_list);
			sunrpc_begin_cache_हटाओ_entry(ch, detail);
			spin_unlock(&detail->hash_lock);
			sunrpc_end_cache_हटाओ_entry(ch, detail);
			spin_lock(&detail->hash_lock);
		पूर्ण
	पूर्ण
	spin_unlock(&detail->hash_lock);
पूर्ण
EXPORT_SYMBOL_GPL(cache_purge);


/*
 * Deferral and Revisiting of Requests.
 *
 * If a cache lookup finds a pending entry, we
 * need to defer the request and revisit it later.
 * All deferred requests are stored in a hash table,
 * indexed by "struct cache_head *".
 * As it may be wasteful to store a whole request
 * काष्ठाure, we allow the request to provide a
 * deferred क्रमm, which must contain a
 * 'struct cache_deferred_req'
 * This cache_deferred_req contains a method to allow
 * it to be revisited when cache info is available
 */

#घोषणा	DFR_HASHSIZE	(PAGE_SIZE/माप(काष्ठा list_head))
#घोषणा	DFR_HASH(item)	((((दीर्घ)item)>>4 ^ (((दीर्घ)item)>>13)) % DFR_HASHSIZE)

#घोषणा	DFR_MAX	300	/* ??? */

अटल DEFINE_SPINLOCK(cache_defer_lock);
अटल LIST_HEAD(cache_defer_list);
अटल काष्ठा hlist_head cache_defer_hash[DFR_HASHSIZE];
अटल पूर्णांक cache_defer_cnt;

अटल व्योम __unhash_deferred_req(काष्ठा cache_deferred_req *dreq)
अणु
	hlist_del_init(&dreq->hash);
	अगर (!list_empty(&dreq->recent)) अणु
		list_del_init(&dreq->recent);
		cache_defer_cnt--;
	पूर्ण
पूर्ण

अटल व्योम __hash_deferred_req(काष्ठा cache_deferred_req *dreq, काष्ठा cache_head *item)
अणु
	पूर्णांक hash = DFR_HASH(item);

	INIT_LIST_HEAD(&dreq->recent);
	hlist_add_head(&dreq->hash, &cache_defer_hash[hash]);
पूर्ण

अटल व्योम setup_deferral(काष्ठा cache_deferred_req *dreq,
			   काष्ठा cache_head *item,
			   पूर्णांक count_me)
अणु

	dreq->item = item;

	spin_lock(&cache_defer_lock);

	__hash_deferred_req(dreq, item);

	अगर (count_me) अणु
		cache_defer_cnt++;
		list_add(&dreq->recent, &cache_defer_list);
	पूर्ण

	spin_unlock(&cache_defer_lock);

पूर्ण

काष्ठा thपढ़ो_deferred_req अणु
	काष्ठा cache_deferred_req handle;
	काष्ठा completion completion;
पूर्ण;

अटल व्योम cache_restart_thपढ़ो(काष्ठा cache_deferred_req *dreq, पूर्णांक too_many)
अणु
	काष्ठा thपढ़ो_deferred_req *dr =
		container_of(dreq, काष्ठा thपढ़ो_deferred_req, handle);
	complete(&dr->completion);
पूर्ण

अटल व्योम cache_रुको_req(काष्ठा cache_req *req, काष्ठा cache_head *item)
अणु
	काष्ठा thपढ़ो_deferred_req sleeper;
	काष्ठा cache_deferred_req *dreq = &sleeper.handle;

	sleeper.completion = COMPLETION_INITIALIZER_ONSTACK(sleeper.completion);
	dreq->revisit = cache_restart_thपढ़ो;

	setup_deferral(dreq, item, 0);

	अगर (!test_bit(CACHE_PENDING, &item->flags) ||
	    रुको_क्रम_completion_पूर्णांकerruptible_समयout(
		    &sleeper.completion, req->thपढ़ो_रुको) <= 0) अणु
		/* The completion wasn't completed, so we need
		 * to clean up
		 */
		spin_lock(&cache_defer_lock);
		अगर (!hlist_unhashed(&sleeper.handle.hash)) अणु
			__unhash_deferred_req(&sleeper.handle);
			spin_unlock(&cache_defer_lock);
		पूर्ण अन्यथा अणु
			/* cache_revisit_request alपढ़ोy हटाओd
			 * this from the hash table, but hasn't
			 * called ->revisit yet.  It will very soon
			 * and we need to रुको क्रम it.
			 */
			spin_unlock(&cache_defer_lock);
			रुको_क्रम_completion(&sleeper.completion);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cache_limit_defers(व्योम)
अणु
	/* Make sure we haven't exceed the limit of allowed deferred
	 * requests.
	 */
	काष्ठा cache_deferred_req *discard = शून्य;

	अगर (cache_defer_cnt <= DFR_MAX)
		वापस;

	spin_lock(&cache_defer_lock);

	/* Consider removing either the first or the last */
	अगर (cache_defer_cnt > DFR_MAX) अणु
		अगर (pअक्रमom_u32() & 1)
			discard = list_entry(cache_defer_list.next,
					     काष्ठा cache_deferred_req, recent);
		अन्यथा
			discard = list_entry(cache_defer_list.prev,
					     काष्ठा cache_deferred_req, recent);
		__unhash_deferred_req(discard);
	पूर्ण
	spin_unlock(&cache_defer_lock);
	अगर (discard)
		discard->revisit(discard, 1);
पूर्ण

/* Return true अगर and only अगर a deferred request is queued. */
अटल bool cache_defer_req(काष्ठा cache_req *req, काष्ठा cache_head *item)
अणु
	काष्ठा cache_deferred_req *dreq;

	अगर (req->thपढ़ो_रुको) अणु
		cache_रुको_req(req, item);
		अगर (!test_bit(CACHE_PENDING, &item->flags))
			वापस false;
	पूर्ण
	dreq = req->defer(req);
	अगर (dreq == शून्य)
		वापस false;
	setup_deferral(dreq, item, 1);
	अगर (!test_bit(CACHE_PENDING, &item->flags))
		/* Bit could have been cleared beक्रमe we managed to
		 * set up the deferral, so need to revisit just in हाल
		 */
		cache_revisit_request(item);

	cache_limit_defers();
	वापस true;
पूर्ण

अटल व्योम cache_revisit_request(काष्ठा cache_head *item)
अणु
	काष्ठा cache_deferred_req *dreq;
	काष्ठा list_head pending;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक hash = DFR_HASH(item);

	INIT_LIST_HEAD(&pending);
	spin_lock(&cache_defer_lock);

	hlist_क्रम_each_entry_safe(dreq, पंचांगp, &cache_defer_hash[hash], hash)
		अगर (dreq->item == item) अणु
			__unhash_deferred_req(dreq);
			list_add(&dreq->recent, &pending);
		पूर्ण

	spin_unlock(&cache_defer_lock);

	जबतक (!list_empty(&pending)) अणु
		dreq = list_entry(pending.next, काष्ठा cache_deferred_req, recent);
		list_del_init(&dreq->recent);
		dreq->revisit(dreq, 0);
	पूर्ण
पूर्ण

व्योम cache_clean_deferred(व्योम *owner)
अणु
	काष्ठा cache_deferred_req *dreq, *पंचांगp;
	काष्ठा list_head pending;


	INIT_LIST_HEAD(&pending);
	spin_lock(&cache_defer_lock);

	list_क्रम_each_entry_safe(dreq, पंचांगp, &cache_defer_list, recent) अणु
		अगर (dreq->owner == owner) अणु
			__unhash_deferred_req(dreq);
			list_add(&dreq->recent, &pending);
		पूर्ण
	पूर्ण
	spin_unlock(&cache_defer_lock);

	जबतक (!list_empty(&pending)) अणु
		dreq = list_entry(pending.next, काष्ठा cache_deferred_req, recent);
		list_del_init(&dreq->recent);
		dreq->revisit(dreq, 1);
	पूर्ण
पूर्ण

/*
 * communicate with user-space
 *
 * We have a magic /proc file - /proc/net/rpc/<cachename>/channel.
 * On पढ़ो, you get a full request, or block.
 * On ग_लिखो, an update request is processed.
 * Poll works अगर anything to पढ़ो, and always allows ग_लिखो.
 *
 * Implemented by linked list of requests.  Each खोलो file has
 * a ->निजी that also exists in this list.  New requests are added
 * to the end and may wakeup and preceding पढ़ोers.
 * New पढ़ोers are added to the head.  If, on पढ़ो, an item is found with
 * CACHE_UPCALLING clear, we मुक्त it from the list.
 *
 */

अटल DEFINE_SPINLOCK(queue_lock);

काष्ठा cache_queue अणु
	काष्ठा list_head	list;
	पूर्णांक			पढ़ोer;	/* अगर 0, then request */
पूर्ण;
काष्ठा cache_request अणु
	काष्ठा cache_queue	q;
	काष्ठा cache_head	*item;
	अक्षर			* buf;
	पूर्णांक			len;
	पूर्णांक			पढ़ोers;
पूर्ण;
काष्ठा cache_पढ़ोer अणु
	काष्ठा cache_queue	q;
	पूर्णांक			offset;	/* अगर non-0, we have a refcnt on next request */
पूर्ण;

अटल पूर्णांक cache_request(काष्ठा cache_detail *detail,
			       काष्ठा cache_request *crq)
अणु
	अक्षर *bp = crq->buf;
	पूर्णांक len = PAGE_SIZE;

	detail->cache_request(detail, crq->item, &bp, &len);
	अगर (len < 0)
		वापस -EAGAIN;
	वापस PAGE_SIZE - len;
पूर्ण

अटल sमाप_प्रकार cache_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count,
			  loff_t *ppos, काष्ठा cache_detail *cd)
अणु
	काष्ठा cache_पढ़ोer *rp = filp->निजी_data;
	काष्ठा cache_request *rq;
	काष्ठा inode *inode = file_inode(filp);
	पूर्णांक err;

	अगर (count == 0)
		वापस 0;

	inode_lock(inode); /* protect against multiple concurrent
			      * पढ़ोers on this file */
 again:
	spin_lock(&queue_lock);
	/* need to find next request */
	जबतक (rp->q.list.next != &cd->queue &&
	       list_entry(rp->q.list.next, काष्ठा cache_queue, list)
	       ->पढ़ोer) अणु
		काष्ठा list_head *next = rp->q.list.next;
		list_move(&rp->q.list, next);
	पूर्ण
	अगर (rp->q.list.next == &cd->queue) अणु
		spin_unlock(&queue_lock);
		inode_unlock(inode);
		WARN_ON_ONCE(rp->offset);
		वापस 0;
	पूर्ण
	rq = container_of(rp->q.list.next, काष्ठा cache_request, q.list);
	WARN_ON_ONCE(rq->q.पढ़ोer);
	अगर (rp->offset == 0)
		rq->पढ़ोers++;
	spin_unlock(&queue_lock);

	अगर (rq->len == 0) अणु
		err = cache_request(cd, rq);
		अगर (err < 0)
			जाओ out;
		rq->len = err;
	पूर्ण

	अगर (rp->offset == 0 && !test_bit(CACHE_PENDING, &rq->item->flags)) अणु
		err = -EAGAIN;
		spin_lock(&queue_lock);
		list_move(&rp->q.list, &rq->q.list);
		spin_unlock(&queue_lock);
	पूर्ण अन्यथा अणु
		अगर (rp->offset + count > rq->len)
			count = rq->len - rp->offset;
		err = -EFAULT;
		अगर (copy_to_user(buf, rq->buf + rp->offset, count))
			जाओ out;
		rp->offset += count;
		अगर (rp->offset >= rq->len) अणु
			rp->offset = 0;
			spin_lock(&queue_lock);
			list_move(&rp->q.list, &rq->q.list);
			spin_unlock(&queue_lock);
		पूर्ण
		err = 0;
	पूर्ण
 out:
	अगर (rp->offset == 0) अणु
		/* need to release rq */
		spin_lock(&queue_lock);
		rq->पढ़ोers--;
		अगर (rq->पढ़ोers == 0 &&
		    !test_bit(CACHE_PENDING, &rq->item->flags)) अणु
			list_del(&rq->q.list);
			spin_unlock(&queue_lock);
			cache_put(rq->item, cd);
			kमुक्त(rq->buf);
			kमुक्त(rq);
		पूर्ण अन्यथा
			spin_unlock(&queue_lock);
	पूर्ण
	अगर (err == -EAGAIN)
		जाओ again;
	inode_unlock(inode);
	वापस err ? err :  count;
पूर्ण

अटल sमाप_प्रकार cache_करो_करोwncall(अक्षर *kaddr, स्थिर अक्षर __user *buf,
				 माप_प्रकार count, काष्ठा cache_detail *cd)
अणु
	sमाप_प्रकार ret;

	अगर (count == 0)
		वापस -EINVAL;
	अगर (copy_from_user(kaddr, buf, count))
		वापस -EFAULT;
	kaddr[count] = '\0';
	ret = cd->cache_parse(cd, kaddr, count);
	अगर (!ret)
		ret = count;
	वापस ret;
पूर्ण

अटल sमाप_प्रकार cache_करोwncall(काष्ठा address_space *mapping,
			      स्थिर अक्षर __user *buf,
			      माप_प्रकार count, काष्ठा cache_detail *cd)
अणु
	अक्षर *ग_लिखो_buf;
	sमाप_प्रकार ret = -ENOMEM;

	अगर (count >= 32768) अणु /* 32k is max userland buffer, lets check anyway */
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ग_लिखो_buf = kvदो_स्मृति(count + 1, GFP_KERNEL);
	अगर (!ग_लिखो_buf)
		जाओ out;

	ret = cache_करो_करोwncall(ग_लिखो_buf, buf, count, cd);
	kvमुक्त(ग_लिखो_buf);
out:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार cache_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			   माप_प्रकार count, loff_t *ppos,
			   काष्ठा cache_detail *cd)
अणु
	काष्ठा address_space *mapping = filp->f_mapping;
	काष्ठा inode *inode = file_inode(filp);
	sमाप_प्रकार ret = -EINVAL;

	अगर (!cd->cache_parse)
		जाओ out;

	inode_lock(inode);
	ret = cache_करोwncall(mapping, buf, count, cd);
	inode_unlock(inode);
out:
	वापस ret;
पूर्ण

अटल DECLARE_WAIT_QUEUE_HEAD(queue_रुको);

अटल __poll_t cache_poll(काष्ठा file *filp, poll_table *रुको,
			       काष्ठा cache_detail *cd)
अणु
	__poll_t mask;
	काष्ठा cache_पढ़ोer *rp = filp->निजी_data;
	काष्ठा cache_queue *cq;

	poll_रुको(filp, &queue_रुको, रुको);

	/* alway allow ग_लिखो */
	mask = EPOLLOUT | EPOLLWRNORM;

	अगर (!rp)
		वापस mask;

	spin_lock(&queue_lock);

	क्रम (cq= &rp->q; &cq->list != &cd->queue;
	     cq = list_entry(cq->list.next, काष्ठा cache_queue, list))
		अगर (!cq->पढ़ोer) अणु
			mask |= EPOLLIN | EPOLLRDNORM;
			अवरोध;
		पूर्ण
	spin_unlock(&queue_lock);
	वापस mask;
पूर्ण

अटल पूर्णांक cache_ioctl(काष्ठा inode *ino, काष्ठा file *filp,
		       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg,
		       काष्ठा cache_detail *cd)
अणु
	पूर्णांक len = 0;
	काष्ठा cache_पढ़ोer *rp = filp->निजी_data;
	काष्ठा cache_queue *cq;

	अगर (cmd != FIONREAD || !rp)
		वापस -EINVAL;

	spin_lock(&queue_lock);

	/* only find the length reमुख्यing in current request,
	 * or the length of the next request
	 */
	क्रम (cq= &rp->q; &cq->list != &cd->queue;
	     cq = list_entry(cq->list.next, काष्ठा cache_queue, list))
		अगर (!cq->पढ़ोer) अणु
			काष्ठा cache_request *cr =
				container_of(cq, काष्ठा cache_request, q);
			len = cr->len - rp->offset;
			अवरोध;
		पूर्ण
	spin_unlock(&queue_lock);

	वापस put_user(len, (पूर्णांक __user *)arg);
पूर्ण

अटल पूर्णांक cache_खोलो(काष्ठा inode *inode, काष्ठा file *filp,
		      काष्ठा cache_detail *cd)
अणु
	काष्ठा cache_पढ़ोer *rp = शून्य;

	अगर (!cd || !try_module_get(cd->owner))
		वापस -EACCES;
	nonseekable_खोलो(inode, filp);
	अगर (filp->f_mode & FMODE_READ) अणु
		rp = kदो_स्मृति(माप(*rp), GFP_KERNEL);
		अगर (!rp) अणु
			module_put(cd->owner);
			वापस -ENOMEM;
		पूर्ण
		rp->offset = 0;
		rp->q.पढ़ोer = 1;

		spin_lock(&queue_lock);
		list_add(&rp->q.list, &cd->queue);
		spin_unlock(&queue_lock);
	पूर्ण
	अगर (filp->f_mode & FMODE_WRITE)
		atomic_inc(&cd->ग_लिखोrs);
	filp->निजी_data = rp;
	वापस 0;
पूर्ण

अटल पूर्णांक cache_release(काष्ठा inode *inode, काष्ठा file *filp,
			 काष्ठा cache_detail *cd)
अणु
	काष्ठा cache_पढ़ोer *rp = filp->निजी_data;

	अगर (rp) अणु
		spin_lock(&queue_lock);
		अगर (rp->offset) अणु
			काष्ठा cache_queue *cq;
			क्रम (cq= &rp->q; &cq->list != &cd->queue;
			     cq = list_entry(cq->list.next, काष्ठा cache_queue, list))
				अगर (!cq->पढ़ोer) अणु
					container_of(cq, काष्ठा cache_request, q)
						->पढ़ोers--;
					अवरोध;
				पूर्ण
			rp->offset = 0;
		पूर्ण
		list_del(&rp->q.list);
		spin_unlock(&queue_lock);

		filp->निजी_data = शून्य;
		kमुक्त(rp);

	पूर्ण
	अगर (filp->f_mode & FMODE_WRITE) अणु
		atomic_dec(&cd->ग_लिखोrs);
		cd->last_बंद = seconds_since_boot();
	पूर्ण
	module_put(cd->owner);
	वापस 0;
पूर्ण



अटल व्योम cache_dequeue(काष्ठा cache_detail *detail, काष्ठा cache_head *ch)
अणु
	काष्ठा cache_queue *cq, *पंचांगp;
	काष्ठा cache_request *cr;
	काष्ठा list_head dequeued;

	INIT_LIST_HEAD(&dequeued);
	spin_lock(&queue_lock);
	list_क्रम_each_entry_safe(cq, पंचांगp, &detail->queue, list)
		अगर (!cq->पढ़ोer) अणु
			cr = container_of(cq, काष्ठा cache_request, q);
			अगर (cr->item != ch)
				जारी;
			अगर (test_bit(CACHE_PENDING, &ch->flags))
				/* Lost a race and it is pending again */
				अवरोध;
			अगर (cr->पढ़ोers != 0)
				जारी;
			list_move(&cr->q.list, &dequeued);
		पूर्ण
	spin_unlock(&queue_lock);
	जबतक (!list_empty(&dequeued)) अणु
		cr = list_entry(dequeued.next, काष्ठा cache_request, q.list);
		list_del(&cr->q.list);
		cache_put(cr->item, detail);
		kमुक्त(cr->buf);
		kमुक्त(cr);
	पूर्ण
पूर्ण

/*
 * Support routines क्रम text-based upcalls.
 * Fields are separated by spaces.
 * Fields are either mangled to quote space tab newline slosh with slosh
 * or a hexअगरied with a leading \ष
 * Record is terminated with newline.
 *
 */

व्योम qword_add(अक्षर **bpp, पूर्णांक *lp, अक्षर *str)
अणु
	अक्षर *bp = *bpp;
	पूर्णांक len = *lp;
	पूर्णांक ret;

	अगर (len < 0) वापस;

	ret = string_escape_str(str, bp, len, ESCAPE_OCTAL, "\\ \n\t");
	अगर (ret >= len) अणु
		bp += len;
		len = -1;
	पूर्ण अन्यथा अणु
		bp += ret;
		len -= ret;
		*bp++ = ' ';
		len--;
	पूर्ण
	*bpp = bp;
	*lp = len;
पूर्ण
EXPORT_SYMBOL_GPL(qword_add);

व्योम qword_addhex(अक्षर **bpp, पूर्णांक *lp, अक्षर *buf, पूर्णांक blen)
अणु
	अक्षर *bp = *bpp;
	पूर्णांक len = *lp;

	अगर (len < 0) वापस;

	अगर (len > 2) अणु
		*bp++ = '\\';
		*bp++ = 'x';
		len -= 2;
		जबतक (blen && len >= 2) अणु
			bp = hex_byte_pack(bp, *buf++);
			len -= 2;
			blen--;
		पूर्ण
	पूर्ण
	अगर (blen || len<1) len = -1;
	अन्यथा अणु
		*bp++ = ' ';
		len--;
	पूर्ण
	*bpp = bp;
	*lp = len;
पूर्ण
EXPORT_SYMBOL_GPL(qword_addhex);

अटल व्योम warn_no_listener(काष्ठा cache_detail *detail)
अणु
	अगर (detail->last_warn != detail->last_बंद) अणु
		detail->last_warn = detail->last_बंद;
		अगर (detail->warn_no_listener)
			detail->warn_no_listener(detail, detail->last_बंद != 0);
	पूर्ण
पूर्ण

अटल bool cache_listeners_exist(काष्ठा cache_detail *detail)
अणु
	अगर (atomic_पढ़ो(&detail->ग_लिखोrs))
		वापस true;
	अगर (detail->last_बंद == 0)
		/* This cache was never खोलोed */
		वापस false;
	अगर (detail->last_बंद < seconds_since_boot() - 30)
		/*
		 * We allow क्रम the possibility that someone might
		 * restart a userspace daemon without restarting the
		 * server; but after 30 seconds, we give up.
		 */
		 वापस false;
	वापस true;
पूर्ण

/*
 * रेजिस्टर an upcall request to user-space and queue it up क्रम पढ़ो() by the
 * upcall daemon.
 *
 * Each request is at most one page दीर्घ.
 */
अटल पूर्णांक cache_pipe_upcall(काष्ठा cache_detail *detail, काष्ठा cache_head *h)
अणु
	अक्षर *buf;
	काष्ठा cache_request *crq;
	पूर्णांक ret = 0;

	अगर (test_bit(CACHE_CLEANED, &h->flags))
		/* Too late to make an upcall */
		वापस -EAGAIN;

	buf = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -EAGAIN;

	crq = kदो_स्मृति(माप (*crq), GFP_KERNEL);
	अगर (!crq) अणु
		kमुक्त(buf);
		वापस -EAGAIN;
	पूर्ण

	crq->q.पढ़ोer = 0;
	crq->buf = buf;
	crq->len = 0;
	crq->पढ़ोers = 0;
	spin_lock(&queue_lock);
	अगर (test_bit(CACHE_PENDING, &h->flags)) अणु
		crq->item = cache_get(h);
		list_add_tail(&crq->q.list, &detail->queue);
		trace_cache_entry_upcall(detail, h);
	पूर्ण अन्यथा
		/* Lost a race, no दीर्घer PENDING, so करोn't enqueue */
		ret = -EAGAIN;
	spin_unlock(&queue_lock);
	wake_up(&queue_रुको);
	अगर (ret == -EAGAIN) अणु
		kमुक्त(buf);
		kमुक्त(crq);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक sunrpc_cache_pipe_upcall(काष्ठा cache_detail *detail, काष्ठा cache_head *h)
अणु
	अगर (test_and_set_bit(CACHE_PENDING, &h->flags))
		वापस 0;
	वापस cache_pipe_upcall(detail, h);
पूर्ण
EXPORT_SYMBOL_GPL(sunrpc_cache_pipe_upcall);

पूर्णांक sunrpc_cache_pipe_upcall_समयout(काष्ठा cache_detail *detail,
				     काष्ठा cache_head *h)
अणु
	अगर (!cache_listeners_exist(detail)) अणु
		warn_no_listener(detail);
		trace_cache_entry_no_listener(detail, h);
		वापस -EINVAL;
	पूर्ण
	वापस sunrpc_cache_pipe_upcall(detail, h);
पूर्ण
EXPORT_SYMBOL_GPL(sunrpc_cache_pipe_upcall_समयout);

/*
 * parse a message from user-space and pass it
 * to an appropriate cache
 * Messages are, like requests, separated पूर्णांकo fields by
 * spaces and dequotes as \षHEXSTRING or embedded \नnn octal
 *
 * Message is
 *   reply cachename expiry key ... content....
 *
 * key and content are both parsed by cache
 */

पूर्णांक qword_get(अक्षर **bpp, अक्षर *dest, पूर्णांक bufsize)
अणु
	/* वापस bytes copied, or -1 on error */
	अक्षर *bp = *bpp;
	पूर्णांक len = 0;

	जबतक (*bp == ' ') bp++;

	अगर (bp[0] == '\\' && bp[1] == 'x') अणु
		/* HEX STRING */
		bp += 2;
		जबतक (len < bufsize - 1) अणु
			पूर्णांक h, l;

			h = hex_to_bin(bp[0]);
			अगर (h < 0)
				अवरोध;

			l = hex_to_bin(bp[1]);
			अगर (l < 0)
				अवरोध;

			*dest++ = (h << 4) | l;
			bp += 2;
			len++;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* text with \नnn octal quoting */
		जबतक (*bp != ' ' && *bp != '\n' && *bp && len < bufsize-1) अणु
			अगर (*bp == '\\' &&
			    है_अष्टक(bp[1]) && (bp[1] <= '3') &&
			    है_अष्टक(bp[2]) &&
			    है_अष्टक(bp[3])) अणु
				पूर्णांक byte = (*++bp -'0');
				bp++;
				byte = (byte << 3) | (*bp++ - '0');
				byte = (byte << 3) | (*bp++ - '0');
				*dest++ = byte;
				len++;
			पूर्ण अन्यथा अणु
				*dest++ = *bp++;
				len++;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (*bp != ' ' && *bp != '\n' && *bp != '\0')
		वापस -1;
	जबतक (*bp == ' ') bp++;
	*bpp = bp;
	*dest = '\0';
	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(qword_get);


/*
 * support /proc/net/rpc/$CACHENAME/content
 * as a seqfile.
 * We call ->cache_show passing शून्य क्रम the item to
 * get a header, then pass each real item in the cache
 */

अटल व्योम *__cache_seq_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	loff_t n = *pos;
	अचिन्हित पूर्णांक hash, entry;
	काष्ठा cache_head *ch;
	काष्ठा cache_detail *cd = m->निजी;

	अगर (!n--)
		वापस SEQ_START_TOKEN;
	hash = n >> 32;
	entry = n & ((1LL<<32) - 1);

	hlist_क्रम_each_entry_rcu(ch, &cd->hash_table[hash], cache_list)
		अगर (!entry--)
			वापस ch;
	n &= ~((1LL<<32) - 1);
	करो अणु
		hash++;
		n += 1LL<<32;
	पूर्ण जबतक(hash < cd->hash_size &&
		hlist_empty(&cd->hash_table[hash]));
	अगर (hash >= cd->hash_size)
		वापस शून्य;
	*pos = n+1;
	वापस hlist_entry_safe(rcu_dereference_raw(
				hlist_first_rcu(&cd->hash_table[hash])),
				काष्ठा cache_head, cache_list);
पूर्ण

अटल व्योम *cache_seq_next(काष्ठा seq_file *m, व्योम *p, loff_t *pos)
अणु
	काष्ठा cache_head *ch = p;
	पूर्णांक hash = (*pos >> 32);
	काष्ठा cache_detail *cd = m->निजी;

	अगर (p == SEQ_START_TOKEN)
		hash = 0;
	अन्यथा अगर (ch->cache_list.next == शून्य) अणु
		hash++;
		*pos += 1LL<<32;
	पूर्ण अन्यथा अणु
		++*pos;
		वापस hlist_entry_safe(rcu_dereference_raw(
					hlist_next_rcu(&ch->cache_list)),
					काष्ठा cache_head, cache_list);
	पूर्ण
	*pos &= ~((1LL<<32) - 1);
	जबतक (hash < cd->hash_size &&
	       hlist_empty(&cd->hash_table[hash])) अणु
		hash++;
		*pos += 1LL<<32;
	पूर्ण
	अगर (hash >= cd->hash_size)
		वापस शून्य;
	++*pos;
	वापस hlist_entry_safe(rcu_dereference_raw(
				hlist_first_rcu(&cd->hash_table[hash])),
				काष्ठा cache_head, cache_list);
पूर्ण

व्योम *cache_seq_start_rcu(काष्ठा seq_file *m, loff_t *pos)
	__acquires(RCU)
अणु
	rcu_पढ़ो_lock();
	वापस __cache_seq_start(m, pos);
पूर्ण
EXPORT_SYMBOL_GPL(cache_seq_start_rcu);

व्योम *cache_seq_next_rcu(काष्ठा seq_file *file, व्योम *p, loff_t *pos)
अणु
	वापस cache_seq_next(file, p, pos);
पूर्ण
EXPORT_SYMBOL_GPL(cache_seq_next_rcu);

व्योम cache_seq_stop_rcu(काष्ठा seq_file *m, व्योम *p)
	__releases(RCU)
अणु
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(cache_seq_stop_rcu);

अटल पूर्णांक c_show(काष्ठा seq_file *m, व्योम *p)
अणु
	काष्ठा cache_head *cp = p;
	काष्ठा cache_detail *cd = m->निजी;

	अगर (p == SEQ_START_TOKEN)
		वापस cd->cache_show(m, cd, शून्य);

	अगरdebug(CACHE)
		seq_म_लिखो(m, "# expiry=%lld refcnt=%d flags=%lx\n",
			   convert_to_wallघड़ी(cp->expiry_समय),
			   kref_पढ़ो(&cp->ref), cp->flags);
	cache_get(cp);
	अगर (cache_check(cd, cp, शून्य))
		/* cache_check करोes a cache_put on failure */
		seq_माला_दो(m, "# ");
	अन्यथा अणु
		अगर (cache_is_expired(cd, cp))
			seq_माला_दो(m, "# ");
		cache_put(cp, cd);
	पूर्ण

	वापस cd->cache_show(m, cd, cp);
पूर्ण

अटल स्थिर काष्ठा seq_operations cache_content_op = अणु
	.start	= cache_seq_start_rcu,
	.next	= cache_seq_next_rcu,
	.stop	= cache_seq_stop_rcu,
	.show	= c_show,
पूर्ण;

अटल पूर्णांक content_खोलो(काष्ठा inode *inode, काष्ठा file *file,
			काष्ठा cache_detail *cd)
अणु
	काष्ठा seq_file *seq;
	पूर्णांक err;

	अगर (!cd || !try_module_get(cd->owner))
		वापस -EACCES;

	err = seq_खोलो(file, &cache_content_op);
	अगर (err) अणु
		module_put(cd->owner);
		वापस err;
	पूर्ण

	seq = file->निजी_data;
	seq->निजी = cd;
	वापस 0;
पूर्ण

अटल पूर्णांक content_release(काष्ठा inode *inode, काष्ठा file *file,
		काष्ठा cache_detail *cd)
अणु
	पूर्णांक ret = seq_release(inode, file);
	module_put(cd->owner);
	वापस ret;
पूर्ण

अटल पूर्णांक खोलो_flush(काष्ठा inode *inode, काष्ठा file *file,
			काष्ठा cache_detail *cd)
अणु
	अगर (!cd || !try_module_get(cd->owner))
		वापस -EACCES;
	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल पूर्णांक release_flush(काष्ठा inode *inode, काष्ठा file *file,
			काष्ठा cache_detail *cd)
अणु
	module_put(cd->owner);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार पढ़ो_flush(काष्ठा file *file, अक्षर __user *buf,
			  माप_प्रकार count, loff_t *ppos,
			  काष्ठा cache_detail *cd)
अणु
	अक्षर tbuf[22];
	माप_प्रकार len;

	len = snम_लिखो(tbuf, माप(tbuf), "%llu\n",
			convert_to_wallघड़ी(cd->flush_समय));
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, tbuf, len);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_flush(काष्ठा file *file, स्थिर अक्षर __user *buf,
			   माप_प्रकार count, loff_t *ppos,
			   काष्ठा cache_detail *cd)
अणु
	अक्षर tbuf[20];
	अक्षर *ep;
	समय64_t now;

	अगर (*ppos || count > माप(tbuf)-1)
		वापस -EINVAL;
	अगर (copy_from_user(tbuf, buf, count))
		वापस -EFAULT;
	tbuf[count] = 0;
	simple_म_से_अदीर्घ(tbuf, &ep, 0);
	अगर (*ep && *ep != '\n')
		वापस -EINVAL;
	/* Note that जबतक we check that 'buf' holds a valid number,
	 * we always ignore the value and just flush everything.
	 * Making use of the number leads to races.
	 */

	now = seconds_since_boot();
	/* Always flush everything, so behave like cache_purge()
	 * Do this by advancing flush_समय to the current समय,
	 * or by one second अगर it has alपढ़ोy reached the current समय.
	 * Newly added cache entries will always have ->last_refresh greater
	 * that ->flush_समय, so they करोn't get flushed prematurely.
	 */

	अगर (cd->flush_समय >= now)
		now = cd->flush_समय + 1;

	cd->flush_समय = now;
	cd->nextcheck = now;
	cache_flush();

	अगर (cd->flush)
		cd->flush();

	*ppos += count;
	वापस count;
पूर्ण

अटल sमाप_प्रकार cache_पढ़ो_procfs(काष्ठा file *filp, अक्षर __user *buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा cache_detail *cd = PDE_DATA(file_inode(filp));

	वापस cache_पढ़ो(filp, buf, count, ppos, cd);
पूर्ण

अटल sमाप_प्रकार cache_ग_लिखो_procfs(काष्ठा file *filp, स्थिर अक्षर __user *buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा cache_detail *cd = PDE_DATA(file_inode(filp));

	वापस cache_ग_लिखो(filp, buf, count, ppos, cd);
पूर्ण

अटल __poll_t cache_poll_procfs(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा cache_detail *cd = PDE_DATA(file_inode(filp));

	वापस cache_poll(filp, रुको, cd);
पूर्ण

अटल दीर्घ cache_ioctl_procfs(काष्ठा file *filp,
			       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा cache_detail *cd = PDE_DATA(inode);

	वापस cache_ioctl(inode, filp, cmd, arg, cd);
पूर्ण

अटल पूर्णांक cache_खोलो_procfs(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा cache_detail *cd = PDE_DATA(inode);

	वापस cache_खोलो(inode, filp, cd);
पूर्ण

अटल पूर्णांक cache_release_procfs(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा cache_detail *cd = PDE_DATA(inode);

	वापस cache_release(inode, filp, cd);
पूर्ण

अटल स्थिर काष्ठा proc_ops cache_channel_proc_ops = अणु
	.proc_lseek	= no_llseek,
	.proc_पढ़ो	= cache_पढ़ो_procfs,
	.proc_ग_लिखो	= cache_ग_लिखो_procfs,
	.proc_poll	= cache_poll_procfs,
	.proc_ioctl	= cache_ioctl_procfs, /* क्रम FIONREAD */
	.proc_खोलो	= cache_खोलो_procfs,
	.proc_release	= cache_release_procfs,
पूर्ण;

अटल पूर्णांक content_खोलो_procfs(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा cache_detail *cd = PDE_DATA(inode);

	वापस content_खोलो(inode, filp, cd);
पूर्ण

अटल पूर्णांक content_release_procfs(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा cache_detail *cd = PDE_DATA(inode);

	वापस content_release(inode, filp, cd);
पूर्ण

अटल स्थिर काष्ठा proc_ops content_proc_ops = अणु
	.proc_खोलो	= content_खोलो_procfs,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= content_release_procfs,
पूर्ण;

अटल पूर्णांक खोलो_flush_procfs(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा cache_detail *cd = PDE_DATA(inode);

	वापस खोलो_flush(inode, filp, cd);
पूर्ण

अटल पूर्णांक release_flush_procfs(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा cache_detail *cd = PDE_DATA(inode);

	वापस release_flush(inode, filp, cd);
पूर्ण

अटल sमाप_प्रकार पढ़ो_flush_procfs(काष्ठा file *filp, अक्षर __user *buf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा cache_detail *cd = PDE_DATA(file_inode(filp));

	वापस पढ़ो_flush(filp, buf, count, ppos, cd);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_flush_procfs(काष्ठा file *filp,
				  स्थिर अक्षर __user *buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा cache_detail *cd = PDE_DATA(file_inode(filp));

	वापस ग_लिखो_flush(filp, buf, count, ppos, cd);
पूर्ण

अटल स्थिर काष्ठा proc_ops cache_flush_proc_ops = अणु
	.proc_खोलो	= खोलो_flush_procfs,
	.proc_पढ़ो	= पढ़ो_flush_procfs,
	.proc_ग_लिखो	= ग_लिखो_flush_procfs,
	.proc_release	= release_flush_procfs,
	.proc_lseek	= no_llseek,
पूर्ण;

अटल व्योम हटाओ_cache_proc_entries(काष्ठा cache_detail *cd)
अणु
	अगर (cd->procfs) अणु
		proc_हटाओ(cd->procfs);
		cd->procfs = शून्य;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक create_cache_proc_entries(काष्ठा cache_detail *cd, काष्ठा net *net)
अणु
	काष्ठा proc_dir_entry *p;
	काष्ठा sunrpc_net *sn;

	sn = net_generic(net, sunrpc_net_id);
	cd->procfs = proc_सूची_गढ़ो(cd->name, sn->proc_net_rpc);
	अगर (cd->procfs == शून्य)
		जाओ out_nomem;

	p = proc_create_data("flush", S_IFREG | 0600,
			     cd->procfs, &cache_flush_proc_ops, cd);
	अगर (p == शून्य)
		जाओ out_nomem;

	अगर (cd->cache_request || cd->cache_parse) अणु
		p = proc_create_data("channel", S_IFREG | 0600, cd->procfs,
				     &cache_channel_proc_ops, cd);
		अगर (p == शून्य)
			जाओ out_nomem;
	पूर्ण
	अगर (cd->cache_show) अणु
		p = proc_create_data("content", S_IFREG | 0400, cd->procfs,
				     &content_proc_ops, cd);
		अगर (p == शून्य)
			जाओ out_nomem;
	पूर्ण
	वापस 0;
out_nomem:
	हटाओ_cache_proc_entries(cd);
	वापस -ENOMEM;
पूर्ण
#अन्यथा /* CONFIG_PROC_FS */
अटल पूर्णांक create_cache_proc_entries(काष्ठा cache_detail *cd, काष्ठा net *net)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

व्योम __init cache_initialize(व्योम)
अणु
	INIT_DEFERRABLE_WORK(&cache_cleaner, करो_cache_clean);
पूर्ण

पूर्णांक cache_रेजिस्टर_net(काष्ठा cache_detail *cd, काष्ठा net *net)
अणु
	पूर्णांक ret;

	sunrpc_init_cache_detail(cd);
	ret = create_cache_proc_entries(cd, net);
	अगर (ret)
		sunrpc_destroy_cache_detail(cd);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cache_रेजिस्टर_net);

व्योम cache_unरेजिस्टर_net(काष्ठा cache_detail *cd, काष्ठा net *net)
अणु
	हटाओ_cache_proc_entries(cd);
	sunrpc_destroy_cache_detail(cd);
पूर्ण
EXPORT_SYMBOL_GPL(cache_unरेजिस्टर_net);

काष्ठा cache_detail *cache_create_net(स्थिर काष्ठा cache_detail *पंचांगpl, काष्ठा net *net)
अणु
	काष्ठा cache_detail *cd;
	पूर्णांक i;

	cd = kmemdup(पंचांगpl, माप(काष्ठा cache_detail), GFP_KERNEL);
	अगर (cd == शून्य)
		वापस ERR_PTR(-ENOMEM);

	cd->hash_table = kसुस्मृति(cd->hash_size, माप(काष्ठा hlist_head),
				 GFP_KERNEL);
	अगर (cd->hash_table == शून्य) अणु
		kमुक्त(cd);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	क्रम (i = 0; i < cd->hash_size; i++)
		INIT_HLIST_HEAD(&cd->hash_table[i]);
	cd->net = net;
	वापस cd;
पूर्ण
EXPORT_SYMBOL_GPL(cache_create_net);

व्योम cache_destroy_net(काष्ठा cache_detail *cd, काष्ठा net *net)
अणु
	kमुक्त(cd->hash_table);
	kमुक्त(cd);
पूर्ण
EXPORT_SYMBOL_GPL(cache_destroy_net);

अटल sमाप_प्रकार cache_पढ़ो_pipefs(काष्ठा file *filp, अक्षर __user *buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा cache_detail *cd = RPC_I(file_inode(filp))->निजी;

	वापस cache_पढ़ो(filp, buf, count, ppos, cd);
पूर्ण

अटल sमाप_प्रकार cache_ग_लिखो_pipefs(काष्ठा file *filp, स्थिर अक्षर __user *buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा cache_detail *cd = RPC_I(file_inode(filp))->निजी;

	वापस cache_ग_लिखो(filp, buf, count, ppos, cd);
पूर्ण

अटल __poll_t cache_poll_pipefs(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा cache_detail *cd = RPC_I(file_inode(filp))->निजी;

	वापस cache_poll(filp, रुको, cd);
पूर्ण

अटल दीर्घ cache_ioctl_pipefs(काष्ठा file *filp,
			      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा cache_detail *cd = RPC_I(inode)->निजी;

	वापस cache_ioctl(inode, filp, cmd, arg, cd);
पूर्ण

अटल पूर्णांक cache_खोलो_pipefs(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा cache_detail *cd = RPC_I(inode)->निजी;

	वापस cache_खोलो(inode, filp, cd);
पूर्ण

अटल पूर्णांक cache_release_pipefs(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा cache_detail *cd = RPC_I(inode)->निजी;

	वापस cache_release(inode, filp, cd);
पूर्ण

स्थिर काष्ठा file_operations cache_file_operations_pipefs = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.पढ़ो		= cache_पढ़ो_pipefs,
	.ग_लिखो		= cache_ग_लिखो_pipefs,
	.poll		= cache_poll_pipefs,
	.unlocked_ioctl	= cache_ioctl_pipefs, /* क्रम FIONREAD */
	.खोलो		= cache_खोलो_pipefs,
	.release	= cache_release_pipefs,
पूर्ण;

अटल पूर्णांक content_खोलो_pipefs(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा cache_detail *cd = RPC_I(inode)->निजी;

	वापस content_खोलो(inode, filp, cd);
पूर्ण

अटल पूर्णांक content_release_pipefs(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा cache_detail *cd = RPC_I(inode)->निजी;

	वापस content_release(inode, filp, cd);
पूर्ण

स्थिर काष्ठा file_operations content_file_operations_pipefs = अणु
	.खोलो		= content_खोलो_pipefs,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= content_release_pipefs,
पूर्ण;

अटल पूर्णांक खोलो_flush_pipefs(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा cache_detail *cd = RPC_I(inode)->निजी;

	वापस खोलो_flush(inode, filp, cd);
पूर्ण

अटल पूर्णांक release_flush_pipefs(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा cache_detail *cd = RPC_I(inode)->निजी;

	वापस release_flush(inode, filp, cd);
पूर्ण

अटल sमाप_प्रकार पढ़ो_flush_pipefs(काष्ठा file *filp, अक्षर __user *buf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा cache_detail *cd = RPC_I(file_inode(filp))->निजी;

	वापस पढ़ो_flush(filp, buf, count, ppos, cd);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_flush_pipefs(काष्ठा file *filp,
				  स्थिर अक्षर __user *buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा cache_detail *cd = RPC_I(file_inode(filp))->निजी;

	वापस ग_लिखो_flush(filp, buf, count, ppos, cd);
पूर्ण

स्थिर काष्ठा file_operations cache_flush_operations_pipefs = अणु
	.खोलो		= खोलो_flush_pipefs,
	.पढ़ो		= पढ़ो_flush_pipefs,
	.ग_लिखो		= ग_लिखो_flush_pipefs,
	.release	= release_flush_pipefs,
	.llseek		= no_llseek,
पूर्ण;

पूर्णांक sunrpc_cache_रेजिस्टर_pipefs(काष्ठा dentry *parent,
				 स्थिर अक्षर *name, umode_t umode,
				 काष्ठा cache_detail *cd)
अणु
	काष्ठा dentry *dir = rpc_create_cache_dir(parent, name, umode, cd);
	अगर (IS_ERR(dir))
		वापस PTR_ERR(dir);
	cd->pipefs = dir;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sunrpc_cache_रेजिस्टर_pipefs);

व्योम sunrpc_cache_unरेजिस्टर_pipefs(काष्ठा cache_detail *cd)
अणु
	अगर (cd->pipefs) अणु
		rpc_हटाओ_cache_dir(cd->pipefs);
		cd->pipefs = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(sunrpc_cache_unरेजिस्टर_pipefs);

व्योम sunrpc_cache_unhash(काष्ठा cache_detail *cd, काष्ठा cache_head *h)
अणु
	spin_lock(&cd->hash_lock);
	अगर (!hlist_unhashed(&h->cache_list))अणु
		sunrpc_begin_cache_हटाओ_entry(h, cd);
		spin_unlock(&cd->hash_lock);
		sunrpc_end_cache_हटाओ_entry(h, cd);
	पूर्ण अन्यथा
		spin_unlock(&cd->hash_lock);
पूर्ण
EXPORT_SYMBOL_GPL(sunrpc_cache_unhash);
