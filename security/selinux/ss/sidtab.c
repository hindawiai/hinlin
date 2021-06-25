<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Implementation of the SID table type.
 *
 * Original author: Stephen Smalley, <sds@tycho.nsa.gov>
 * Author: Ondrej Mosnacek, <omosnacek@gmail.com>
 *
 * Copyright (C) 2018 Red Hat, Inc.
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <यंत्र/barrier.h>
#समावेश "flask.h"
#समावेश "security.h"
#समावेश "sidtab.h"

काष्ठा sidtab_str_cache अणु
	काष्ठा rcu_head rcu_member;
	काष्ठा list_head lru_member;
	काष्ठा sidtab_entry *parent;
	u32 len;
	अक्षर str[];
पूर्ण;

#घोषणा index_to_sid(index) (index + SECINITSID_NUM + 1)
#घोषणा sid_to_index(sid) (sid - (SECINITSID_NUM + 1))

पूर्णांक sidtab_init(काष्ठा sidtab *s)
अणु
	u32 i;

	स_रखो(s->roots, 0, माप(s->roots));

	क्रम (i = 0; i < SECINITSID_NUM; i++)
		s->isids[i].set = 0;

	s->frozen = false;
	s->count = 0;
	s->convert = शून्य;
	hash_init(s->context_to_sid);

	spin_lock_init(&s->lock);

#अगर CONFIG_SECURITY_SELINUX_SID2STR_CACHE_SIZE > 0
	s->cache_मुक्त_slots = CONFIG_SECURITY_SELINUX_SID2STR_CACHE_SIZE;
	INIT_LIST_HEAD(&s->cache_lru_list);
	spin_lock_init(&s->cache_lock);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल u32 context_to_sid(काष्ठा sidtab *s, काष्ठा context *context, u32 hash)
अणु
	काष्ठा sidtab_entry *entry;
	u32 sid = 0;

	rcu_पढ़ो_lock();
	hash_क्रम_each_possible_rcu(s->context_to_sid, entry, list, hash) अणु
		अगर (entry->hash != hash)
			जारी;
		अगर (context_cmp(&entry->context, context)) अणु
			sid = entry->sid;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस sid;
पूर्ण

पूर्णांक sidtab_set_initial(काष्ठा sidtab *s, u32 sid, काष्ठा context *context)
अणु
	काष्ठा sidtab_isid_entry *isid;
	u32 hash;
	पूर्णांक rc;

	अगर (sid == 0 || sid > SECINITSID_NUM)
		वापस -EINVAL;

	isid = &s->isids[sid - 1];

	rc = context_cpy(&isid->entry.context, context);
	अगर (rc)
		वापस rc;

#अगर CONFIG_SECURITY_SELINUX_SID2STR_CACHE_SIZE > 0
	isid->entry.cache = शून्य;
#पूर्ण_अगर
	isid->set = 1;

	hash = context_compute_hash(context);

	/*
	 * Multiple initial sids may map to the same context. Check that this
	 * context is not alपढ़ोy represented in the context_to_sid hashtable
	 * to aव्योम duplicate entries and दीर्घ linked lists upon hash
	 * collision.
	 */
	अगर (!context_to_sid(s, context, hash)) अणु
		isid->entry.sid = sid;
		isid->entry.hash = hash;
		hash_add(s->context_to_sid, &isid->entry.list, hash);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक sidtab_hash_stats(काष्ठा sidtab *sidtab, अक्षर *page)
अणु
	पूर्णांक i;
	पूर्णांक chain_len = 0;
	पूर्णांक slots_used = 0;
	पूर्णांक entries = 0;
	पूर्णांक max_chain_len = 0;
	पूर्णांक cur_bucket = 0;
	काष्ठा sidtab_entry *entry;

	rcu_पढ़ो_lock();
	hash_क्रम_each_rcu(sidtab->context_to_sid, i, entry, list) अणु
		entries++;
		अगर (i == cur_bucket) अणु
			chain_len++;
			अगर (chain_len == 1)
				slots_used++;
		पूर्ण अन्यथा अणु
			cur_bucket = i;
			अगर (chain_len > max_chain_len)
				max_chain_len = chain_len;
			chain_len = 0;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (chain_len > max_chain_len)
		max_chain_len = chain_len;

	वापस scnम_लिखो(page, PAGE_SIZE, "entries: %d\nbuckets used: %d/%d\n"
			 "longest chain: %d\n", entries,
			 slots_used, SIDTAB_HASH_BUCKETS, max_chain_len);
पूर्ण

अटल u32 sidtab_level_from_count(u32 count)
अणु
	u32 capacity = SIDTAB_LEAF_ENTRIES;
	u32 level = 0;

	जबतक (count > capacity) अणु
		capacity <<= SIDTAB_INNER_SHIFT;
		++level;
	पूर्ण
	वापस level;
पूर्ण

अटल पूर्णांक sidtab_alloc_roots(काष्ठा sidtab *s, u32 level)
अणु
	u32 l;

	अगर (!s->roots[0].ptr_leaf) अणु
		s->roots[0].ptr_leaf = kzalloc(SIDTAB_NODE_ALLOC_SIZE,
					       GFP_ATOMIC);
		अगर (!s->roots[0].ptr_leaf)
			वापस -ENOMEM;
	पूर्ण
	क्रम (l = 1; l <= level; ++l)
		अगर (!s->roots[l].ptr_inner) अणु
			s->roots[l].ptr_inner = kzalloc(SIDTAB_NODE_ALLOC_SIZE,
							GFP_ATOMIC);
			अगर (!s->roots[l].ptr_inner)
				वापस -ENOMEM;
			s->roots[l].ptr_inner->entries[0] = s->roots[l - 1];
		पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा sidtab_entry *sidtab_करो_lookup(काष्ठा sidtab *s, u32 index,
					     पूर्णांक alloc)
अणु
	जोड़ sidtab_entry_inner *entry;
	u32 level, capacity_shअगरt, leaf_index = index / SIDTAB_LEAF_ENTRIES;

	/* find the level of the subtree we need */
	level = sidtab_level_from_count(index + 1);
	capacity_shअगरt = level * SIDTAB_INNER_SHIFT;

	/* allocate roots अगर needed */
	अगर (alloc && sidtab_alloc_roots(s, level) != 0)
		वापस शून्य;

	/* lookup inside the subtree */
	entry = &s->roots[level];
	जबतक (level != 0) अणु
		capacity_shअगरt -= SIDTAB_INNER_SHIFT;
		--level;

		entry = &entry->ptr_inner->entries[leaf_index >> capacity_shअगरt];
		leaf_index &= ((u32)1 << capacity_shअगरt) - 1;

		अगर (!entry->ptr_inner) अणु
			अगर (alloc)
				entry->ptr_inner = kzalloc(SIDTAB_NODE_ALLOC_SIZE,
							   GFP_ATOMIC);
			अगर (!entry->ptr_inner)
				वापस शून्य;
		पूर्ण
	पूर्ण
	अगर (!entry->ptr_leaf) अणु
		अगर (alloc)
			entry->ptr_leaf = kzalloc(SIDTAB_NODE_ALLOC_SIZE,
						  GFP_ATOMIC);
		अगर (!entry->ptr_leaf)
			वापस शून्य;
	पूर्ण
	वापस &entry->ptr_leaf->entries[index % SIDTAB_LEAF_ENTRIES];
पूर्ण

अटल काष्ठा sidtab_entry *sidtab_lookup(काष्ठा sidtab *s, u32 index)
अणु
	/* पढ़ो entries only after पढ़ोing count */
	u32 count = smp_load_acquire(&s->count);

	अगर (index >= count)
		वापस शून्य;

	वापस sidtab_करो_lookup(s, index, 0);
पूर्ण

अटल काष्ठा sidtab_entry *sidtab_lookup_initial(काष्ठा sidtab *s, u32 sid)
अणु
	वापस s->isids[sid - 1].set ? &s->isids[sid - 1].entry : शून्य;
पूर्ण

अटल काष्ठा sidtab_entry *sidtab_search_core(काष्ठा sidtab *s, u32 sid,
					       पूर्णांक क्रमce)
अणु
	अगर (sid != 0) अणु
		काष्ठा sidtab_entry *entry;

		अगर (sid > SECINITSID_NUM)
			entry = sidtab_lookup(s, sid_to_index(sid));
		अन्यथा
			entry = sidtab_lookup_initial(s, sid);
		अगर (entry && (!entry->context.len || क्रमce))
			वापस entry;
	पूर्ण

	वापस sidtab_lookup_initial(s, SECINITSID_UNLABELED);
पूर्ण

काष्ठा sidtab_entry *sidtab_search_entry(काष्ठा sidtab *s, u32 sid)
अणु
	वापस sidtab_search_core(s, sid, 0);
पूर्ण

काष्ठा sidtab_entry *sidtab_search_entry_क्रमce(काष्ठा sidtab *s, u32 sid)
अणु
	वापस sidtab_search_core(s, sid, 1);
पूर्ण

पूर्णांक sidtab_context_to_sid(काष्ठा sidtab *s, काष्ठा context *context,
			  u32 *sid)
अणु
	अचिन्हित दीर्घ flags;
	u32 count, hash = context_compute_hash(context);
	काष्ठा sidtab_convert_params *convert;
	काष्ठा sidtab_entry *dst, *dst_convert;
	पूर्णांक rc;

	*sid = context_to_sid(s, context, hash);
	अगर (*sid)
		वापस 0;

	/* lock-मुक्त search failed: lock, re-search, and insert अगर not found */
	spin_lock_irqsave(&s->lock, flags);

	rc = 0;
	*sid = context_to_sid(s, context, hash);
	अगर (*sid)
		जाओ out_unlock;

	अगर (unlikely(s->frozen)) अणु
		/*
		 * This sidtab is now frozen - tell the caller to पात and
		 * get the new one.
		 */
		rc = -ESTALE;
		जाओ out_unlock;
	पूर्ण

	count = s->count;
	convert = s->convert;

	/* bail out अगर we alपढ़ोy reached max entries */
	rc = -EOVERFLOW;
	अगर (count >= SIDTAB_MAX)
		जाओ out_unlock;

	/* insert context पूर्णांकo new entry */
	rc = -ENOMEM;
	dst = sidtab_करो_lookup(s, count, 1);
	अगर (!dst)
		जाओ out_unlock;

	dst->sid = index_to_sid(count);
	dst->hash = hash;

	rc = context_cpy(&dst->context, context);
	अगर (rc)
		जाओ out_unlock;

	/*
	 * अगर we are building a new sidtab, we need to convert the context
	 * and insert it there as well
	 */
	अगर (convert) अणु
		rc = -ENOMEM;
		dst_convert = sidtab_करो_lookup(convert->target, count, 1);
		अगर (!dst_convert) अणु
			context_destroy(&dst->context);
			जाओ out_unlock;
		पूर्ण

		rc = convert->func(context, &dst_convert->context,
				   convert->args);
		अगर (rc) अणु
			context_destroy(&dst->context);
			जाओ out_unlock;
		पूर्ण
		dst_convert->sid = index_to_sid(count);
		dst_convert->hash = context_compute_hash(&dst_convert->context);
		convert->target->count = count + 1;

		hash_add_rcu(convert->target->context_to_sid,
			     &dst_convert->list, dst_convert->hash);
	पूर्ण

	अगर (context->len)
		pr_info("SELinux:  Context %s is not valid (left unmapped).\n",
			context->str);

	*sid = index_to_sid(count);

	/* ग_लिखो entries beक्रमe updating count */
	smp_store_release(&s->count, count + 1);
	hash_add_rcu(s->context_to_sid, &dst->list, dst->hash);

	rc = 0;
out_unlock:
	spin_unlock_irqrestore(&s->lock, flags);
	वापस rc;
पूर्ण

अटल व्योम sidtab_convert_hashtable(काष्ठा sidtab *s, u32 count)
अणु
	काष्ठा sidtab_entry *entry;
	u32 i;

	क्रम (i = 0; i < count; i++) अणु
		entry = sidtab_करो_lookup(s, i, 0);
		entry->sid = index_to_sid(i);
		entry->hash = context_compute_hash(&entry->context);

		hash_add_rcu(s->context_to_sid, &entry->list, entry->hash);
	पूर्ण
पूर्ण

अटल पूर्णांक sidtab_convert_tree(जोड़ sidtab_entry_inner *edst,
			       जोड़ sidtab_entry_inner *esrc,
			       u32 *pos, u32 count, u32 level,
			       काष्ठा sidtab_convert_params *convert)
अणु
	पूर्णांक rc;
	u32 i;

	अगर (level != 0) अणु
		अगर (!edst->ptr_inner) अणु
			edst->ptr_inner = kzalloc(SIDTAB_NODE_ALLOC_SIZE,
						  GFP_KERNEL);
			अगर (!edst->ptr_inner)
				वापस -ENOMEM;
		पूर्ण
		i = 0;
		जबतक (i < SIDTAB_INNER_ENTRIES && *pos < count) अणु
			rc = sidtab_convert_tree(&edst->ptr_inner->entries[i],
						 &esrc->ptr_inner->entries[i],
						 pos, count, level - 1,
						 convert);
			अगर (rc)
				वापस rc;
			i++;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!edst->ptr_leaf) अणु
			edst->ptr_leaf = kzalloc(SIDTAB_NODE_ALLOC_SIZE,
						 GFP_KERNEL);
			अगर (!edst->ptr_leaf)
				वापस -ENOMEM;
		पूर्ण
		i = 0;
		जबतक (i < SIDTAB_LEAF_ENTRIES && *pos < count) अणु
			rc = convert->func(&esrc->ptr_leaf->entries[i].context,
					   &edst->ptr_leaf->entries[i].context,
					   convert->args);
			अगर (rc)
				वापस rc;
			(*pos)++;
			i++;
		पूर्ण
		cond_resched();
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक sidtab_convert(काष्ठा sidtab *s, काष्ठा sidtab_convert_params *params)
अणु
	अचिन्हित दीर्घ flags;
	u32 count, level, pos;
	पूर्णांक rc;

	spin_lock_irqsave(&s->lock, flags);

	/* concurrent policy loads are not allowed */
	अगर (s->convert) अणु
		spin_unlock_irqrestore(&s->lock, flags);
		वापस -EBUSY;
	पूर्ण

	count = s->count;
	level = sidtab_level_from_count(count);

	/* allocate last leaf in the new sidtab (to aव्योम race with
	 * live convert)
	 */
	rc = sidtab_करो_lookup(params->target, count - 1, 1) ? 0 : -ENOMEM;
	अगर (rc) अणु
		spin_unlock_irqrestore(&s->lock, flags);
		वापस rc;
	पूर्ण

	/* set count in हाल no new entries are added during conversion */
	params->target->count = count;

	/* enable live convert of new entries */
	s->convert = params;

	/* we can safely convert the tree outside the lock */
	spin_unlock_irqrestore(&s->lock, flags);

	pr_info("SELinux:  Converting %u SID table entries...\n", count);

	/* convert all entries not covered by live convert */
	pos = 0;
	rc = sidtab_convert_tree(&params->target->roots[level],
				 &s->roots[level], &pos, count, level, params);
	अगर (rc) अणु
		/* we need to keep the old table - disable live convert */
		spin_lock_irqsave(&s->lock, flags);
		s->convert = शून्य;
		spin_unlock_irqrestore(&s->lock, flags);
		वापस rc;
	पूर्ण
	/*
	 * The hashtable can also be modअगरied in sidtab_context_to_sid()
	 * so we must re-acquire the lock here.
	 */
	spin_lock_irqsave(&s->lock, flags);
	sidtab_convert_hashtable(params->target, count);
	spin_unlock_irqrestore(&s->lock, flags);

	वापस 0;
पूर्ण

व्योम sidtab_cancel_convert(काष्ठा sidtab *s)
अणु
	अचिन्हित दीर्घ flags;

	/* cancelling policy load - disable live convert of sidtab */
	spin_lock_irqsave(&s->lock, flags);
	s->convert = शून्य;
	spin_unlock_irqrestore(&s->lock, flags);
पूर्ण

व्योम sidtab_मुक्तze_begin(काष्ठा sidtab *s, अचिन्हित दीर्घ *flags) __acquires(&s->lock)
अणु
	spin_lock_irqsave(&s->lock, *flags);
	s->frozen = true;
	s->convert = शून्य;
पूर्ण
व्योम sidtab_मुक्तze_end(काष्ठा sidtab *s, अचिन्हित दीर्घ *flags) __releases(&s->lock)
अणु
	spin_unlock_irqrestore(&s->lock, *flags);
पूर्ण

अटल व्योम sidtab_destroy_entry(काष्ठा sidtab_entry *entry)
अणु
	context_destroy(&entry->context);
#अगर CONFIG_SECURITY_SELINUX_SID2STR_CACHE_SIZE > 0
	kमुक्त(rcu_dereference_raw(entry->cache));
#पूर्ण_अगर
पूर्ण

अटल व्योम sidtab_destroy_tree(जोड़ sidtab_entry_inner entry, u32 level)
अणु
	u32 i;

	अगर (level != 0) अणु
		काष्ठा sidtab_node_inner *node = entry.ptr_inner;

		अगर (!node)
			वापस;

		क्रम (i = 0; i < SIDTAB_INNER_ENTRIES; i++)
			sidtab_destroy_tree(node->entries[i], level - 1);
		kमुक्त(node);
	पूर्ण अन्यथा अणु
		काष्ठा sidtab_node_leaf *node = entry.ptr_leaf;

		अगर (!node)
			वापस;

		क्रम (i = 0; i < SIDTAB_LEAF_ENTRIES; i++)
			sidtab_destroy_entry(&node->entries[i]);
		kमुक्त(node);
	पूर्ण
पूर्ण

व्योम sidtab_destroy(काष्ठा sidtab *s)
अणु
	u32 i, level;

	क्रम (i = 0; i < SECINITSID_NUM; i++)
		अगर (s->isids[i].set)
			sidtab_destroy_entry(&s->isids[i].entry);

	level = SIDTAB_MAX_LEVEL;
	जबतक (level && !s->roots[level].ptr_inner)
		--level;

	sidtab_destroy_tree(s->roots[level], level);
	/*
	 * The context_to_sid hashtable's objects are all shared
	 * with the isids array and context tree, and so करोn't need
	 * to be cleaned up here.
	 */
पूर्ण

#अगर CONFIG_SECURITY_SELINUX_SID2STR_CACHE_SIZE > 0

व्योम sidtab_sid2str_put(काष्ठा sidtab *s, काष्ठा sidtab_entry *entry,
			स्थिर अक्षर *str, u32 str_len)
अणु
	काष्ठा sidtab_str_cache *cache, *victim = शून्य;
	अचिन्हित दीर्घ flags;

	/* करो not cache invalid contexts */
	अगर (entry->context.len)
		वापस;

	spin_lock_irqsave(&s->cache_lock, flags);

	cache = rcu_dereference_रक्षित(entry->cache,
					  lockdep_is_held(&s->cache_lock));
	अगर (cache) अणु
		/* entry in cache - just bump to the head of LRU list */
		list_move(&cache->lru_member, &s->cache_lru_list);
		जाओ out_unlock;
	पूर्ण

	cache = kदो_स्मृति(माप(काष्ठा sidtab_str_cache) + str_len, GFP_ATOMIC);
	अगर (!cache)
		जाओ out_unlock;

	अगर (s->cache_मुक्त_slots == 0) अणु
		/* pop a cache entry from the tail and मुक्त it */
		victim = container_of(s->cache_lru_list.prev,
				      काष्ठा sidtab_str_cache, lru_member);
		list_del(&victim->lru_member);
		rcu_assign_poपूर्णांकer(victim->parent->cache, शून्य);
	पूर्ण अन्यथा अणु
		s->cache_मुक्त_slots--;
	पूर्ण
	cache->parent = entry;
	cache->len = str_len;
	स_नकल(cache->str, str, str_len);
	list_add(&cache->lru_member, &s->cache_lru_list);

	rcu_assign_poपूर्णांकer(entry->cache, cache);

out_unlock:
	spin_unlock_irqrestore(&s->cache_lock, flags);
	kमुक्त_rcu(victim, rcu_member);
पूर्ण

पूर्णांक sidtab_sid2str_get(काष्ठा sidtab *s, काष्ठा sidtab_entry *entry,
		       अक्षर **out, u32 *out_len)
अणु
	काष्ठा sidtab_str_cache *cache;
	पूर्णांक rc = 0;

	अगर (entry->context.len)
		वापस -ENOENT; /* करो not cache invalid contexts */

	rcu_पढ़ो_lock();

	cache = rcu_dereference(entry->cache);
	अगर (!cache) अणु
		rc = -ENOENT;
	पूर्ण अन्यथा अणु
		*out_len = cache->len;
		अगर (out) अणु
			*out = kmemdup(cache->str, cache->len, GFP_ATOMIC);
			अगर (!*out)
				rc = -ENOMEM;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	अगर (!rc && out)
		sidtab_sid2str_put(s, entry, *out, *out_len);
	वापस rc;
पूर्ण

#पूर्ण_अगर /* CONFIG_SECURITY_SELINUX_SID2STR_CACHE_SIZE > 0 */
