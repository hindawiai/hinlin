<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2007-2014 Nicira, Inc.
 */

#समावेश "flow.h"
#समावेश "datapath.h"
#समावेश "flow_netlink.h"
#समावेश <linux/uaccess.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/llc_pdu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/jhash.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/llc.h>
#समावेश <linux/module.h>
#समावेश <linux/in.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/sctp.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/icmp.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/rculist.h>
#समावेश <linux/sort.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/ndisc.h>

#घोषणा TBL_MIN_BUCKETS		1024
#घोषणा MASK_ARRAY_SIZE_MIN	16
#घोषणा REHASH_INTERVAL		(10 * 60 * HZ)

#घोषणा MC_DEFAULT_HASH_ENTRIES	256
#घोषणा MC_HASH_SHIFT		8
#घोषणा MC_HASH_SEGS		((माप(uपूर्णांक32_t) * 8) / MC_HASH_SHIFT)

अटल काष्ठा kmem_cache *flow_cache;
काष्ठा kmem_cache *flow_stats_cache __पढ़ो_mostly;

अटल u16 range_n_bytes(स्थिर काष्ठा sw_flow_key_range *range)
अणु
	वापस range->end - range->start;
पूर्ण

व्योम ovs_flow_mask_key(काष्ठा sw_flow_key *dst, स्थिर काष्ठा sw_flow_key *src,
		       bool full, स्थिर काष्ठा sw_flow_mask *mask)
अणु
	पूर्णांक start = full ? 0 : mask->range.start;
	पूर्णांक len = full ? माप *dst : range_n_bytes(&mask->range);
	स्थिर दीर्घ *m = (स्थिर दीर्घ *)((स्थिर u8 *)&mask->key + start);
	स्थिर दीर्घ *s = (स्थिर दीर्घ *)((स्थिर u8 *)src + start);
	दीर्घ *d = (दीर्घ *)((u8 *)dst + start);
	पूर्णांक i;

	/* If 'full' is true then all of 'dst' is fully initialized. Otherwise,
	 * अगर 'full' is false the memory outside of the 'mask->range' is left
	 * uninitialized. This can be used as an optimization when further
	 * operations on 'dst' only use contents within 'mask->range'.
	 */
	क्रम (i = 0; i < len; i += माप(दीर्घ))
		*d++ = *s++ & *m++;
पूर्ण

काष्ठा sw_flow *ovs_flow_alloc(व्योम)
अणु
	काष्ठा sw_flow *flow;
	काष्ठा sw_flow_stats *stats;

	flow = kmem_cache_zalloc(flow_cache, GFP_KERNEL);
	अगर (!flow)
		वापस ERR_PTR(-ENOMEM);

	flow->stats_last_ग_लिखोr = -1;

	/* Initialize the शेष stat node. */
	stats = kmem_cache_alloc_node(flow_stats_cache,
				      GFP_KERNEL | __GFP_ZERO,
				      node_online(0) ? 0 : NUMA_NO_NODE);
	अगर (!stats)
		जाओ err;

	spin_lock_init(&stats->lock);

	RCU_INIT_POINTER(flow->stats[0], stats);

	cpumask_set_cpu(0, &flow->cpu_used_mask);

	वापस flow;
err:
	kmem_cache_मुक्त(flow_cache, flow);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

पूर्णांक ovs_flow_tbl_count(स्थिर काष्ठा flow_table *table)
अणु
	वापस table->count;
पूर्ण

अटल व्योम flow_मुक्त(काष्ठा sw_flow *flow)
अणु
	पूर्णांक cpu;

	अगर (ovs_identअगरier_is_key(&flow->id))
		kमुक्त(flow->id.unmasked_key);
	अगर (flow->sf_acts)
		ovs_nla_मुक्त_flow_actions((काष्ठा sw_flow_actions __क्रमce *)
					  flow->sf_acts);
	/* We खोलो code this to make sure cpu 0 is always considered */
	क्रम (cpu = 0; cpu < nr_cpu_ids;
	     cpu = cpumask_next(cpu, &flow->cpu_used_mask)) अणु
		अगर (flow->stats[cpu])
			kmem_cache_मुक्त(flow_stats_cache,
					(काष्ठा sw_flow_stats __क्रमce *)flow->stats[cpu]);
	पूर्ण

	kmem_cache_मुक्त(flow_cache, flow);
पूर्ण

अटल व्योम rcu_मुक्त_flow_callback(काष्ठा rcu_head *rcu)
अणु
	काष्ठा sw_flow *flow = container_of(rcu, काष्ठा sw_flow, rcu);

	flow_मुक्त(flow);
पूर्ण

व्योम ovs_flow_मुक्त(काष्ठा sw_flow *flow, bool deferred)
अणु
	अगर (!flow)
		वापस;

	अगर (deferred)
		call_rcu(&flow->rcu, rcu_मुक्त_flow_callback);
	अन्यथा
		flow_मुक्त(flow);
पूर्ण

अटल व्योम __table_instance_destroy(काष्ठा table_instance *ti)
अणु
	kvमुक्त(ti->buckets);
	kमुक्त(ti);
पूर्ण

अटल काष्ठा table_instance *table_instance_alloc(पूर्णांक new_size)
अणु
	काष्ठा table_instance *ti = kदो_स्मृति(माप(*ti), GFP_KERNEL);
	पूर्णांक i;

	अगर (!ti)
		वापस शून्य;

	ti->buckets = kvदो_स्मृति_array(new_size, माप(काष्ठा hlist_head),
				     GFP_KERNEL);
	अगर (!ti->buckets) अणु
		kमुक्त(ti);
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < new_size; i++)
		INIT_HLIST_HEAD(&ti->buckets[i]);

	ti->n_buckets = new_size;
	ti->node_ver = 0;
	get_अक्रमom_bytes(&ti->hash_seed, माप(u32));

	वापस ti;
पूर्ण

अटल व्योम __mask_array_destroy(काष्ठा mask_array *ma)
अणु
	मुक्त_percpu(ma->masks_usage_stats);
	kमुक्त(ma);
पूर्ण

अटल व्योम mask_array_rcu_cb(काष्ठा rcu_head *rcu)
अणु
	काष्ठा mask_array *ma = container_of(rcu, काष्ठा mask_array, rcu);

	__mask_array_destroy(ma);
पूर्ण

अटल व्योम tbl_mask_array_reset_counters(काष्ठा mask_array *ma)
अणु
	पूर्णांक i, cpu;

	/* As the per CPU counters are not atomic we can not go ahead and
	 * reset them from another CPU. To be able to still have an approximate
	 * zero based counter we store the value at reset, and subtract it
	 * later when processing.
	 */
	क्रम (i = 0; i < ma->max; i++) अणु
		ma->masks_usage_zero_cntr[i] = 0;

		क्रम_each_possible_cpu(cpu) अणु
			काष्ठा mask_array_stats *stats;
			अचिन्हित पूर्णांक start;
			u64 counter;

			stats = per_cpu_ptr(ma->masks_usage_stats, cpu);
			करो अणु
				start = u64_stats_fetch_begin_irq(&stats->syncp);
				counter = stats->usage_cntrs[i];
			पूर्ण जबतक (u64_stats_fetch_retry_irq(&stats->syncp, start));

			ma->masks_usage_zero_cntr[i] += counter;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा mask_array *tbl_mask_array_alloc(पूर्णांक size)
अणु
	काष्ठा mask_array *new;

	size = max(MASK_ARRAY_SIZE_MIN, size);
	new = kzalloc(माप(काष्ठा mask_array) +
		      माप(काष्ठा sw_flow_mask *) * size +
		      माप(u64) * size, GFP_KERNEL);
	अगर (!new)
		वापस शून्य;

	new->masks_usage_zero_cntr = (u64 *)((u8 *)new +
					     माप(काष्ठा mask_array) +
					     माप(काष्ठा sw_flow_mask *) *
					     size);

	new->masks_usage_stats = __alloc_percpu(माप(काष्ठा mask_array_stats) +
						माप(u64) * size,
						__alignof__(u64));
	अगर (!new->masks_usage_stats) अणु
		kमुक्त(new);
		वापस शून्य;
	पूर्ण

	new->count = 0;
	new->max = size;

	वापस new;
पूर्ण

अटल पूर्णांक tbl_mask_array_पुनः_स्मृति(काष्ठा flow_table *tbl, पूर्णांक size)
अणु
	काष्ठा mask_array *old;
	काष्ठा mask_array *new;

	new = tbl_mask_array_alloc(size);
	अगर (!new)
		वापस -ENOMEM;

	old = ovsl_dereference(tbl->mask_array);
	अगर (old) अणु
		पूर्णांक i;

		क्रम (i = 0; i < old->max; i++) अणु
			अगर (ovsl_dereference(old->masks[i]))
				new->masks[new->count++] = old->masks[i];
		पूर्ण
		call_rcu(&old->rcu, mask_array_rcu_cb);
	पूर्ण

	rcu_assign_poपूर्णांकer(tbl->mask_array, new);

	वापस 0;
पूर्ण

अटल पूर्णांक tbl_mask_array_add_mask(काष्ठा flow_table *tbl,
				   काष्ठा sw_flow_mask *new)
अणु
	काष्ठा mask_array *ma = ovsl_dereference(tbl->mask_array);
	पूर्णांक err, ma_count = READ_ONCE(ma->count);

	अगर (ma_count >= ma->max) अणु
		err = tbl_mask_array_पुनः_स्मृति(tbl, ma->max +
						  MASK_ARRAY_SIZE_MIN);
		अगर (err)
			वापस err;

		ma = ovsl_dereference(tbl->mask_array);
	पूर्ण अन्यथा अणु
		/* On every add or delete we need to reset the counters so
		 * every new mask माला_लो a fair chance of being prioritized.
		 */
		tbl_mask_array_reset_counters(ma);
	पूर्ण

	BUG_ON(ovsl_dereference(ma->masks[ma_count]));

	rcu_assign_poपूर्णांकer(ma->masks[ma_count], new);
	WRITE_ONCE(ma->count, ma_count + 1);

	वापस 0;
पूर्ण

अटल व्योम tbl_mask_array_del_mask(काष्ठा flow_table *tbl,
				    काष्ठा sw_flow_mask *mask)
अणु
	काष्ठा mask_array *ma = ovsl_dereference(tbl->mask_array);
	पूर्णांक i, ma_count = READ_ONCE(ma->count);

	/* Remove the deleted mask poपूर्णांकers from the array */
	क्रम (i = 0; i < ma_count; i++) अणु
		अगर (mask == ovsl_dereference(ma->masks[i]))
			जाओ found;
	पूर्ण

	BUG();
	वापस;

found:
	WRITE_ONCE(ma->count, ma_count - 1);

	rcu_assign_poपूर्णांकer(ma->masks[i], ma->masks[ma_count - 1]);
	RCU_INIT_POINTER(ma->masks[ma_count - 1], शून्य);

	kमुक्त_rcu(mask, rcu);

	/* Shrink the mask array अगर necessary. */
	अगर (ma->max >= (MASK_ARRAY_SIZE_MIN * 2) &&
	    ma_count <= (ma->max / 3))
		tbl_mask_array_पुनः_स्मृति(tbl, ma->max / 2);
	अन्यथा
		tbl_mask_array_reset_counters(ma);

पूर्ण

/* Remove 'mask' from the mask list, अगर it is not needed any more. */
अटल व्योम flow_mask_हटाओ(काष्ठा flow_table *tbl, काष्ठा sw_flow_mask *mask)
अणु
	अगर (mask) अणु
		/* ovs-lock is required to protect mask-refcount and
		 * mask list.
		 */
		ASSERT_OVSL();
		BUG_ON(!mask->ref_count);
		mask->ref_count--;

		अगर (!mask->ref_count)
			tbl_mask_array_del_mask(tbl, mask);
	पूर्ण
पूर्ण

अटल व्योम __mask_cache_destroy(काष्ठा mask_cache *mc)
अणु
	मुक्त_percpu(mc->mask_cache);
	kमुक्त(mc);
पूर्ण

अटल व्योम mask_cache_rcu_cb(काष्ठा rcu_head *rcu)
अणु
	काष्ठा mask_cache *mc = container_of(rcu, काष्ठा mask_cache, rcu);

	__mask_cache_destroy(mc);
पूर्ण

अटल काष्ठा mask_cache *tbl_mask_cache_alloc(u32 size)
अणु
	काष्ठा mask_cache_entry __percpu *cache = शून्य;
	काष्ठा mask_cache *new;

	/* Only allow size to be 0, or a घातer of 2, and करोes not exceed
	 * percpu allocation size.
	 */
	अगर ((!is_घातer_of_2(size) && size != 0) ||
	    (size * माप(काष्ठा mask_cache_entry)) > PCPU_MIN_UNIT_SIZE)
		वापस शून्य;

	new = kzalloc(माप(*new), GFP_KERNEL);
	अगर (!new)
		वापस शून्य;

	new->cache_size = size;
	अगर (new->cache_size > 0) अणु
		cache = __alloc_percpu(array_size(माप(काष्ठा mask_cache_entry),
						  new->cache_size),
				       __alignof__(काष्ठा mask_cache_entry));
		अगर (!cache) अणु
			kमुक्त(new);
			वापस शून्य;
		पूर्ण
	पूर्ण

	new->mask_cache = cache;
	वापस new;
पूर्ण
पूर्णांक ovs_flow_tbl_masks_cache_resize(काष्ठा flow_table *table, u32 size)
अणु
	काष्ठा mask_cache *mc = rcu_dereference_ovsl(table->mask_cache);
	काष्ठा mask_cache *new;

	अगर (size == mc->cache_size)
		वापस 0;

	अगर ((!is_घातer_of_2(size) && size != 0) ||
	    (size * माप(काष्ठा mask_cache_entry)) > PCPU_MIN_UNIT_SIZE)
		वापस -EINVAL;

	new = tbl_mask_cache_alloc(size);
	अगर (!new)
		वापस -ENOMEM;

	rcu_assign_poपूर्णांकer(table->mask_cache, new);
	call_rcu(&mc->rcu, mask_cache_rcu_cb);

	वापस 0;
पूर्ण

पूर्णांक ovs_flow_tbl_init(काष्ठा flow_table *table)
अणु
	काष्ठा table_instance *ti, *ufid_ti;
	काष्ठा mask_cache *mc;
	काष्ठा mask_array *ma;

	mc = tbl_mask_cache_alloc(MC_DEFAULT_HASH_ENTRIES);
	अगर (!mc)
		वापस -ENOMEM;

	ma = tbl_mask_array_alloc(MASK_ARRAY_SIZE_MIN);
	अगर (!ma)
		जाओ मुक्त_mask_cache;

	ti = table_instance_alloc(TBL_MIN_BUCKETS);
	अगर (!ti)
		जाओ मुक्त_mask_array;

	ufid_ti = table_instance_alloc(TBL_MIN_BUCKETS);
	अगर (!ufid_ti)
		जाओ मुक्त_ti;

	rcu_assign_poपूर्णांकer(table->ti, ti);
	rcu_assign_poपूर्णांकer(table->ufid_ti, ufid_ti);
	rcu_assign_poपूर्णांकer(table->mask_array, ma);
	rcu_assign_poपूर्णांकer(table->mask_cache, mc);
	table->last_rehash = jअगरfies;
	table->count = 0;
	table->ufid_count = 0;
	वापस 0;

मुक्त_ti:
	__table_instance_destroy(ti);
मुक्त_mask_array:
	__mask_array_destroy(ma);
मुक्त_mask_cache:
	__mask_cache_destroy(mc);
	वापस -ENOMEM;
पूर्ण

अटल व्योम flow_tbl_destroy_rcu_cb(काष्ठा rcu_head *rcu)
अणु
	काष्ठा table_instance *ti;

	ti = container_of(rcu, काष्ठा table_instance, rcu);
	__table_instance_destroy(ti);
पूर्ण

अटल व्योम table_instance_flow_मुक्त(काष्ठा flow_table *table,
				     काष्ठा table_instance *ti,
				     काष्ठा table_instance *ufid_ti,
				     काष्ठा sw_flow *flow)
अणु
	hlist_del_rcu(&flow->flow_table.node[ti->node_ver]);
	table->count--;

	अगर (ovs_identअगरier_is_ufid(&flow->id)) अणु
		hlist_del_rcu(&flow->ufid_table.node[ufid_ti->node_ver]);
		table->ufid_count--;
	पूर्ण

	flow_mask_हटाओ(table, flow->mask);
पूर्ण

/* Must be called with OVS mutex held. */
व्योम table_instance_flow_flush(काष्ठा flow_table *table,
			       काष्ठा table_instance *ti,
			       काष्ठा table_instance *ufid_ti)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ti->n_buckets; i++) अणु
		काष्ठा hlist_head *head = &ti->buckets[i];
		काष्ठा hlist_node *n;
		काष्ठा sw_flow *flow;

		hlist_क्रम_each_entry_safe(flow, n, head,
					  flow_table.node[ti->node_ver]) अणु

			table_instance_flow_मुक्त(table, ti, ufid_ti,
						 flow);
			ovs_flow_मुक्त(flow, true);
		पूर्ण
	पूर्ण

	अगर (WARN_ON(table->count != 0 ||
		    table->ufid_count != 0)) अणु
		table->count = 0;
		table->ufid_count = 0;
	पूर्ण
पूर्ण

अटल व्योम table_instance_destroy(काष्ठा table_instance *ti,
				   काष्ठा table_instance *ufid_ti)
अणु
	call_rcu(&ti->rcu, flow_tbl_destroy_rcu_cb);
	call_rcu(&ufid_ti->rcu, flow_tbl_destroy_rcu_cb);
पूर्ण

/* No need क्रम locking this function is called from RCU callback or
 * error path.
 */
व्योम ovs_flow_tbl_destroy(काष्ठा flow_table *table)
अणु
	काष्ठा table_instance *ti = rcu_dereference_raw(table->ti);
	काष्ठा table_instance *ufid_ti = rcu_dereference_raw(table->ufid_ti);
	काष्ठा mask_cache *mc = rcu_dereference_raw(table->mask_cache);
	काष्ठा mask_array *ma = rcu_dereference_raw(table->mask_array);

	call_rcu(&mc->rcu, mask_cache_rcu_cb);
	call_rcu(&ma->rcu, mask_array_rcu_cb);
	table_instance_destroy(ti, ufid_ti);
पूर्ण

काष्ठा sw_flow *ovs_flow_tbl_dump_next(काष्ठा table_instance *ti,
				       u32 *bucket, u32 *last)
अणु
	काष्ठा sw_flow *flow;
	काष्ठा hlist_head *head;
	पूर्णांक ver;
	पूर्णांक i;

	ver = ti->node_ver;
	जबतक (*bucket < ti->n_buckets) अणु
		i = 0;
		head = &ti->buckets[*bucket];
		hlist_क्रम_each_entry_rcu(flow, head, flow_table.node[ver]) अणु
			अगर (i < *last) अणु
				i++;
				जारी;
			पूर्ण
			*last = i + 1;
			वापस flow;
		पूर्ण
		(*bucket)++;
		*last = 0;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा hlist_head *find_bucket(काष्ठा table_instance *ti, u32 hash)
अणु
	hash = jhash_1word(hash, ti->hash_seed);
	वापस &ti->buckets[hash & (ti->n_buckets - 1)];
पूर्ण

अटल व्योम table_instance_insert(काष्ठा table_instance *ti,
				  काष्ठा sw_flow *flow)
अणु
	काष्ठा hlist_head *head;

	head = find_bucket(ti, flow->flow_table.hash);
	hlist_add_head_rcu(&flow->flow_table.node[ti->node_ver], head);
पूर्ण

अटल व्योम ufid_table_instance_insert(काष्ठा table_instance *ti,
				       काष्ठा sw_flow *flow)
अणु
	काष्ठा hlist_head *head;

	head = find_bucket(ti, flow->ufid_table.hash);
	hlist_add_head_rcu(&flow->ufid_table.node[ti->node_ver], head);
पूर्ण

अटल व्योम flow_table_copy_flows(काष्ठा table_instance *old,
				  काष्ठा table_instance *new, bool ufid)
अणु
	पूर्णांक old_ver;
	पूर्णांक i;

	old_ver = old->node_ver;
	new->node_ver = !old_ver;

	/* Insert in new table. */
	क्रम (i = 0; i < old->n_buckets; i++) अणु
		काष्ठा sw_flow *flow;
		काष्ठा hlist_head *head = &old->buckets[i];

		अगर (ufid)
			hlist_क्रम_each_entry_rcu(flow, head,
						 ufid_table.node[old_ver],
						 lockdep_ovsl_is_held())
				ufid_table_instance_insert(new, flow);
		अन्यथा
			hlist_क्रम_each_entry_rcu(flow, head,
						 flow_table.node[old_ver],
						 lockdep_ovsl_is_held())
				table_instance_insert(new, flow);
	पूर्ण
पूर्ण

अटल काष्ठा table_instance *table_instance_rehash(काष्ठा table_instance *ti,
						    पूर्णांक n_buckets, bool ufid)
अणु
	काष्ठा table_instance *new_ti;

	new_ti = table_instance_alloc(n_buckets);
	अगर (!new_ti)
		वापस शून्य;

	flow_table_copy_flows(ti, new_ti, ufid);

	वापस new_ti;
पूर्ण

पूर्णांक ovs_flow_tbl_flush(काष्ठा flow_table *flow_table)
अणु
	काष्ठा table_instance *old_ti, *new_ti;
	काष्ठा table_instance *old_ufid_ti, *new_ufid_ti;

	new_ti = table_instance_alloc(TBL_MIN_BUCKETS);
	अगर (!new_ti)
		वापस -ENOMEM;
	new_ufid_ti = table_instance_alloc(TBL_MIN_BUCKETS);
	अगर (!new_ufid_ti)
		जाओ err_मुक्त_ti;

	old_ti = ovsl_dereference(flow_table->ti);
	old_ufid_ti = ovsl_dereference(flow_table->ufid_ti);

	rcu_assign_poपूर्णांकer(flow_table->ti, new_ti);
	rcu_assign_poपूर्णांकer(flow_table->ufid_ti, new_ufid_ti);
	flow_table->last_rehash = jअगरfies;

	table_instance_flow_flush(flow_table, old_ti, old_ufid_ti);
	table_instance_destroy(old_ti, old_ufid_ti);
	वापस 0;

err_मुक्त_ti:
	__table_instance_destroy(new_ti);
	वापस -ENOMEM;
पूर्ण

अटल u32 flow_hash(स्थिर काष्ठा sw_flow_key *key,
		     स्थिर काष्ठा sw_flow_key_range *range)
अणु
	स्थिर u32 *hash_key = (स्थिर u32 *)((स्थिर u8 *)key + range->start);

	/* Make sure number of hash bytes are multiple of u32. */
	पूर्णांक hash_u32s = range_n_bytes(range) >> 2;

	वापस jhash2(hash_key, hash_u32s, 0);
पूर्ण

अटल पूर्णांक flow_key_start(स्थिर काष्ठा sw_flow_key *key)
अणु
	अगर (key->tun_proto)
		वापस 0;
	अन्यथा
		वापस roundकरोwn(दुरत्व(काष्ठा sw_flow_key, phy),
				 माप(दीर्घ));
पूर्ण

अटल bool cmp_key(स्थिर काष्ठा sw_flow_key *key1,
		    स्थिर काष्ठा sw_flow_key *key2,
		    पूर्णांक key_start, पूर्णांक key_end)
अणु
	स्थिर दीर्घ *cp1 = (स्थिर दीर्घ *)((स्थिर u8 *)key1 + key_start);
	स्थिर दीर्घ *cp2 = (स्थिर दीर्घ *)((स्थिर u8 *)key2 + key_start);
	दीर्घ dअगरfs = 0;
	पूर्णांक i;

	क्रम (i = key_start; i < key_end; i += माप(दीर्घ))
		dअगरfs |= *cp1++ ^ *cp2++;

	वापस dअगरfs == 0;
पूर्ण

अटल bool flow_cmp_masked_key(स्थिर काष्ठा sw_flow *flow,
				स्थिर काष्ठा sw_flow_key *key,
				स्थिर काष्ठा sw_flow_key_range *range)
अणु
	वापस cmp_key(&flow->key, key, range->start, range->end);
पूर्ण

अटल bool ovs_flow_cmp_unmasked_key(स्थिर काष्ठा sw_flow *flow,
				      स्थिर काष्ठा sw_flow_match *match)
अणु
	काष्ठा sw_flow_key *key = match->key;
	पूर्णांक key_start = flow_key_start(key);
	पूर्णांक key_end = match->range.end;

	BUG_ON(ovs_identअगरier_is_ufid(&flow->id));
	वापस cmp_key(flow->id.unmasked_key, key, key_start, key_end);
पूर्ण

अटल काष्ठा sw_flow *masked_flow_lookup(काष्ठा table_instance *ti,
					  स्थिर काष्ठा sw_flow_key *unmasked,
					  स्थिर काष्ठा sw_flow_mask *mask,
					  u32 *n_mask_hit)
अणु
	काष्ठा sw_flow *flow;
	काष्ठा hlist_head *head;
	u32 hash;
	काष्ठा sw_flow_key masked_key;

	ovs_flow_mask_key(&masked_key, unmasked, false, mask);
	hash = flow_hash(&masked_key, &mask->range);
	head = find_bucket(ti, hash);
	(*n_mask_hit)++;

	hlist_क्रम_each_entry_rcu(flow, head, flow_table.node[ti->node_ver],
				 lockdep_ovsl_is_held()) अणु
		अगर (flow->mask == mask && flow->flow_table.hash == hash &&
		    flow_cmp_masked_key(flow, &masked_key, &mask->range))
			वापस flow;
	पूर्ण
	वापस शून्य;
पूर्ण

/* Flow lookup करोes full lookup on flow table. It starts with
 * mask from index passed in *index.
 * This function MUST be called with BH disabled due to the use
 * of CPU specअगरic variables.
 */
अटल काष्ठा sw_flow *flow_lookup(काष्ठा flow_table *tbl,
				   काष्ठा table_instance *ti,
				   काष्ठा mask_array *ma,
				   स्थिर काष्ठा sw_flow_key *key,
				   u32 *n_mask_hit,
				   u32 *n_cache_hit,
				   u32 *index)
अणु
	काष्ठा mask_array_stats *stats = this_cpu_ptr(ma->masks_usage_stats);
	काष्ठा sw_flow *flow;
	काष्ठा sw_flow_mask *mask;
	पूर्णांक i;

	अगर (likely(*index < ma->max)) अणु
		mask = rcu_dereference_ovsl(ma->masks[*index]);
		अगर (mask) अणु
			flow = masked_flow_lookup(ti, key, mask, n_mask_hit);
			अगर (flow) अणु
				u64_stats_update_begin(&stats->syncp);
				stats->usage_cntrs[*index]++;
				u64_stats_update_end(&stats->syncp);
				(*n_cache_hit)++;
				वापस flow;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ma->max; i++)  अणु

		अगर (i == *index)
			जारी;

		mask = rcu_dereference_ovsl(ma->masks[i]);
		अगर (unlikely(!mask))
			अवरोध;

		flow = masked_flow_lookup(ti, key, mask, n_mask_hit);
		अगर (flow) अणु /* Found */
			*index = i;
			u64_stats_update_begin(&stats->syncp);
			stats->usage_cntrs[*index]++;
			u64_stats_update_end(&stats->syncp);
			वापस flow;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * mask_cache maps flow to probable mask. This cache is not tightly
 * coupled cache, It means updates to  mask list can result in inconsistent
 * cache entry in mask cache.
 * This is per cpu cache and is भागided in MC_HASH_SEGS segments.
 * In हाल of a hash collision the entry is hashed in next segment.
 * */
काष्ठा sw_flow *ovs_flow_tbl_lookup_stats(काष्ठा flow_table *tbl,
					  स्थिर काष्ठा sw_flow_key *key,
					  u32 skb_hash,
					  u32 *n_mask_hit,
					  u32 *n_cache_hit)
अणु
	काष्ठा mask_cache *mc = rcu_dereference(tbl->mask_cache);
	काष्ठा mask_array *ma = rcu_dereference(tbl->mask_array);
	काष्ठा table_instance *ti = rcu_dereference(tbl->ti);
	काष्ठा mask_cache_entry *entries, *ce;
	काष्ठा sw_flow *flow;
	u32 hash;
	पूर्णांक seg;

	*n_mask_hit = 0;
	*n_cache_hit = 0;
	अगर (unlikely(!skb_hash || mc->cache_size == 0)) अणु
		u32 mask_index = 0;
		u32 cache = 0;

		वापस flow_lookup(tbl, ti, ma, key, n_mask_hit, &cache,
				   &mask_index);
	पूर्ण

	/* Pre and post recirulation flows usually have the same skb_hash
	 * value. To aव्योम hash collisions, rehash the 'skb_hash' with
	 * 'recirc_id'.  */
	अगर (key->recirc_id)
		skb_hash = jhash_1word(skb_hash, key->recirc_id);

	ce = शून्य;
	hash = skb_hash;
	entries = this_cpu_ptr(mc->mask_cache);

	/* Find the cache entry 'ce' to operate on. */
	क्रम (seg = 0; seg < MC_HASH_SEGS; seg++) अणु
		पूर्णांक index = hash & (mc->cache_size - 1);
		काष्ठा mask_cache_entry *e;

		e = &entries[index];
		अगर (e->skb_hash == skb_hash) अणु
			flow = flow_lookup(tbl, ti, ma, key, n_mask_hit,
					   n_cache_hit, &e->mask_index);
			अगर (!flow)
				e->skb_hash = 0;
			वापस flow;
		पूर्ण

		अगर (!ce || e->skb_hash < ce->skb_hash)
			ce = e;  /* A better replacement cache candidate. */

		hash >>= MC_HASH_SHIFT;
	पूर्ण

	/* Cache miss, करो full lookup. */
	flow = flow_lookup(tbl, ti, ma, key, n_mask_hit, n_cache_hit,
			   &ce->mask_index);
	अगर (flow)
		ce->skb_hash = skb_hash;

	*n_cache_hit = 0;
	वापस flow;
पूर्ण

काष्ठा sw_flow *ovs_flow_tbl_lookup(काष्ठा flow_table *tbl,
				    स्थिर काष्ठा sw_flow_key *key)
अणु
	काष्ठा table_instance *ti = rcu_dereference_ovsl(tbl->ti);
	काष्ठा mask_array *ma = rcu_dereference_ovsl(tbl->mask_array);
	u32 __always_unused n_mask_hit;
	u32 __always_unused n_cache_hit;
	काष्ठा sw_flow *flow;
	u32 index = 0;

	/* This function माला_लो called trough the netlink पूर्णांकerface and thereक्रमe
	 * is preemptible. However, flow_lookup() function needs to be called
	 * with BH disabled due to CPU specअगरic variables.
	 */
	local_bh_disable();
	flow = flow_lookup(tbl, ti, ma, key, &n_mask_hit, &n_cache_hit, &index);
	local_bh_enable();
	वापस flow;
पूर्ण

काष्ठा sw_flow *ovs_flow_tbl_lookup_exact(काष्ठा flow_table *tbl,
					  स्थिर काष्ठा sw_flow_match *match)
अणु
	काष्ठा mask_array *ma = ovsl_dereference(tbl->mask_array);
	पूर्णांक i;

	/* Always called under ovs-mutex. */
	क्रम (i = 0; i < ma->max; i++) अणु
		काष्ठा table_instance *ti = rcu_dereference_ovsl(tbl->ti);
		u32 __always_unused n_mask_hit;
		काष्ठा sw_flow_mask *mask;
		काष्ठा sw_flow *flow;

		mask = ovsl_dereference(ma->masks[i]);
		अगर (!mask)
			जारी;

		flow = masked_flow_lookup(ti, match->key, mask, &n_mask_hit);
		अगर (flow && ovs_identअगरier_is_key(&flow->id) &&
		    ovs_flow_cmp_unmasked_key(flow, match)) अणु
			वापस flow;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल u32 ufid_hash(स्थिर काष्ठा sw_flow_id *sfid)
अणु
	वापस jhash(sfid->ufid, sfid->ufid_len, 0);
पूर्ण

अटल bool ovs_flow_cmp_ufid(स्थिर काष्ठा sw_flow *flow,
			      स्थिर काष्ठा sw_flow_id *sfid)
अणु
	अगर (flow->id.ufid_len != sfid->ufid_len)
		वापस false;

	वापस !स_भेद(flow->id.ufid, sfid->ufid, sfid->ufid_len);
पूर्ण

bool ovs_flow_cmp(स्थिर काष्ठा sw_flow *flow,
		  स्थिर काष्ठा sw_flow_match *match)
अणु
	अगर (ovs_identअगरier_is_ufid(&flow->id))
		वापस flow_cmp_masked_key(flow, match->key, &match->range);

	वापस ovs_flow_cmp_unmasked_key(flow, match);
पूर्ण

काष्ठा sw_flow *ovs_flow_tbl_lookup_ufid(काष्ठा flow_table *tbl,
					 स्थिर काष्ठा sw_flow_id *ufid)
अणु
	काष्ठा table_instance *ti = rcu_dereference_ovsl(tbl->ufid_ti);
	काष्ठा sw_flow *flow;
	काष्ठा hlist_head *head;
	u32 hash;

	hash = ufid_hash(ufid);
	head = find_bucket(ti, hash);
	hlist_क्रम_each_entry_rcu(flow, head, ufid_table.node[ti->node_ver],
				 lockdep_ovsl_is_held()) अणु
		अगर (flow->ufid_table.hash == hash &&
		    ovs_flow_cmp_ufid(flow, ufid))
			वापस flow;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक ovs_flow_tbl_num_masks(स्थिर काष्ठा flow_table *table)
अणु
	काष्ठा mask_array *ma = rcu_dereference_ovsl(table->mask_array);
	वापस READ_ONCE(ma->count);
पूर्ण

u32 ovs_flow_tbl_masks_cache_size(स्थिर काष्ठा flow_table *table)
अणु
	काष्ठा mask_cache *mc = rcu_dereference_ovsl(table->mask_cache);

	वापस READ_ONCE(mc->cache_size);
पूर्ण

अटल काष्ठा table_instance *table_instance_expand(काष्ठा table_instance *ti,
						    bool ufid)
अणु
	वापस table_instance_rehash(ti, ti->n_buckets * 2, ufid);
पूर्ण

/* Must be called with OVS mutex held. */
व्योम ovs_flow_tbl_हटाओ(काष्ठा flow_table *table, काष्ठा sw_flow *flow)
अणु
	काष्ठा table_instance *ti = ovsl_dereference(table->ti);
	काष्ठा table_instance *ufid_ti = ovsl_dereference(table->ufid_ti);

	BUG_ON(table->count == 0);
	table_instance_flow_मुक्त(table, ti, ufid_ti, flow);
पूर्ण

अटल काष्ठा sw_flow_mask *mask_alloc(व्योम)
अणु
	काष्ठा sw_flow_mask *mask;

	mask = kदो_स्मृति(माप(*mask), GFP_KERNEL);
	अगर (mask)
		mask->ref_count = 1;

	वापस mask;
पूर्ण

अटल bool mask_equal(स्थिर काष्ठा sw_flow_mask *a,
		       स्थिर काष्ठा sw_flow_mask *b)
अणु
	स्थिर u8 *a_ = (स्थिर u8 *)&a->key + a->range.start;
	स्थिर u8 *b_ = (स्थिर u8 *)&b->key + b->range.start;

	वापस  (a->range.end == b->range.end)
		&& (a->range.start == b->range.start)
		&& (स_भेद(a_, b_, range_n_bytes(&a->range)) == 0);
पूर्ण

अटल काष्ठा sw_flow_mask *flow_mask_find(स्थिर काष्ठा flow_table *tbl,
					   स्थिर काष्ठा sw_flow_mask *mask)
अणु
	काष्ठा mask_array *ma;
	पूर्णांक i;

	ma = ovsl_dereference(tbl->mask_array);
	क्रम (i = 0; i < ma->max; i++) अणु
		काष्ठा sw_flow_mask *t;
		t = ovsl_dereference(ma->masks[i]);

		अगर (t && mask_equal(mask, t))
			वापस t;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Add 'mask' पूर्णांकo the mask list, अगर it is not alपढ़ोy there. */
अटल पूर्णांक flow_mask_insert(काष्ठा flow_table *tbl, काष्ठा sw_flow *flow,
			    स्थिर काष्ठा sw_flow_mask *new)
अणु
	काष्ठा sw_flow_mask *mask;

	mask = flow_mask_find(tbl, new);
	अगर (!mask) अणु
		/* Allocate a new mask अगर none exsits. */
		mask = mask_alloc();
		अगर (!mask)
			वापस -ENOMEM;
		mask->key = new->key;
		mask->range = new->range;

		/* Add mask to mask-list. */
		अगर (tbl_mask_array_add_mask(tbl, mask)) अणु
			kमुक्त(mask);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		BUG_ON(!mask->ref_count);
		mask->ref_count++;
	पूर्ण

	flow->mask = mask;
	वापस 0;
पूर्ण

/* Must be called with OVS mutex held. */
अटल व्योम flow_key_insert(काष्ठा flow_table *table, काष्ठा sw_flow *flow)
अणु
	काष्ठा table_instance *new_ti = शून्य;
	काष्ठा table_instance *ti;

	flow->flow_table.hash = flow_hash(&flow->key, &flow->mask->range);
	ti = ovsl_dereference(table->ti);
	table_instance_insert(ti, flow);
	table->count++;

	/* Expand table, अगर necessary, to make room. */
	अगर (table->count > ti->n_buckets)
		new_ti = table_instance_expand(ti, false);
	अन्यथा अगर (समय_after(jअगरfies, table->last_rehash + REHASH_INTERVAL))
		new_ti = table_instance_rehash(ti, ti->n_buckets, false);

	अगर (new_ti) अणु
		rcu_assign_poपूर्णांकer(table->ti, new_ti);
		call_rcu(&ti->rcu, flow_tbl_destroy_rcu_cb);
		table->last_rehash = jअगरfies;
	पूर्ण
पूर्ण

/* Must be called with OVS mutex held. */
अटल व्योम flow_ufid_insert(काष्ठा flow_table *table, काष्ठा sw_flow *flow)
अणु
	काष्ठा table_instance *ti;

	flow->ufid_table.hash = ufid_hash(&flow->id);
	ti = ovsl_dereference(table->ufid_ti);
	ufid_table_instance_insert(ti, flow);
	table->ufid_count++;

	/* Expand table, अगर necessary, to make room. */
	अगर (table->ufid_count > ti->n_buckets) अणु
		काष्ठा table_instance *new_ti;

		new_ti = table_instance_expand(ti, true);
		अगर (new_ti) अणु
			rcu_assign_poपूर्णांकer(table->ufid_ti, new_ti);
			call_rcu(&ti->rcu, flow_tbl_destroy_rcu_cb);
		पूर्ण
	पूर्ण
पूर्ण

/* Must be called with OVS mutex held. */
पूर्णांक ovs_flow_tbl_insert(काष्ठा flow_table *table, काष्ठा sw_flow *flow,
			स्थिर काष्ठा sw_flow_mask *mask)
अणु
	पूर्णांक err;

	err = flow_mask_insert(table, flow, mask);
	अगर (err)
		वापस err;
	flow_key_insert(table, flow);
	अगर (ovs_identअगरier_is_ufid(&flow->id))
		flow_ufid_insert(table, flow);

	वापस 0;
पूर्ण

अटल पूर्णांक compare_mask_and_count(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा mask_count *mc_a = a;
	स्थिर काष्ठा mask_count *mc_b = b;

	वापस (s64)mc_b->counter - (s64)mc_a->counter;
पूर्ण

/* Must be called with OVS mutex held. */
व्योम ovs_flow_masks_rebalance(काष्ठा flow_table *table)
अणु
	काष्ठा mask_array *ma = rcu_dereference_ovsl(table->mask_array);
	काष्ठा mask_count *masks_and_count;
	काष्ठा mask_array *new;
	पूर्णांक masks_entries = 0;
	पूर्णांक i;

	/* Build array of all current entries with use counters. */
	masks_and_count = kदो_स्मृति_array(ma->max, माप(*masks_and_count),
					GFP_KERNEL);
	अगर (!masks_and_count)
		वापस;

	क्रम (i = 0; i < ma->max; i++) अणु
		काष्ठा sw_flow_mask *mask;
		पूर्णांक cpu;

		mask = rcu_dereference_ovsl(ma->masks[i]);
		अगर (unlikely(!mask))
			अवरोध;

		masks_and_count[i].index = i;
		masks_and_count[i].counter = 0;

		क्रम_each_possible_cpu(cpu) अणु
			काष्ठा mask_array_stats *stats;
			अचिन्हित पूर्णांक start;
			u64 counter;

			stats = per_cpu_ptr(ma->masks_usage_stats, cpu);
			करो अणु
				start = u64_stats_fetch_begin_irq(&stats->syncp);
				counter = stats->usage_cntrs[i];
			पूर्ण जबतक (u64_stats_fetch_retry_irq(&stats->syncp,
							   start));

			masks_and_count[i].counter += counter;
		पूर्ण

		/* Subtract the zero count value. */
		masks_and_count[i].counter -= ma->masks_usage_zero_cntr[i];

		/* Rather than calling tbl_mask_array_reset_counters()
		 * below when no change is needed, करो it अंतरभूत here.
		 */
		ma->masks_usage_zero_cntr[i] += masks_and_count[i].counter;
	पूर्ण

	अगर (i == 0)
		जाओ मुक्त_mask_entries;

	/* Sort the entries */
	masks_entries = i;
	sort(masks_and_count, masks_entries, माप(*masks_and_count),
	     compare_mask_and_count, शून्य);

	/* If the order is the same, nothing to करो... */
	क्रम (i = 0; i < masks_entries; i++) अणु
		अगर (i != masks_and_count[i].index)
			अवरोध;
	पूर्ण
	अगर (i == masks_entries)
		जाओ मुक्त_mask_entries;

	/* Rebuilt the new list in order of usage. */
	new = tbl_mask_array_alloc(ma->max);
	अगर (!new)
		जाओ मुक्त_mask_entries;

	क्रम (i = 0; i < masks_entries; i++) अणु
		पूर्णांक index = masks_and_count[i].index;

		अगर (ovsl_dereference(ma->masks[index]))
			new->masks[new->count++] = ma->masks[index];
	पूर्ण

	rcu_assign_poपूर्णांकer(table->mask_array, new);
	call_rcu(&ma->rcu, mask_array_rcu_cb);

मुक्त_mask_entries:
	kमुक्त(masks_and_count);
पूर्ण

/* Initializes the flow module.
 * Returns zero अगर successful or a negative error code. */
पूर्णांक ovs_flow_init(व्योम)
अणु
	BUILD_BUG_ON(__alignof__(काष्ठा sw_flow_key) % __alignof__(दीर्घ));
	BUILD_BUG_ON(माप(काष्ठा sw_flow_key) % माप(दीर्घ));

	flow_cache = kmem_cache_create("sw_flow", माप(काष्ठा sw_flow)
				       + (nr_cpu_ids
					  * माप(काष्ठा sw_flow_stats *)),
				       0, 0, शून्य);
	अगर (flow_cache == शून्य)
		वापस -ENOMEM;

	flow_stats_cache
		= kmem_cache_create("sw_flow_stats", माप(काष्ठा sw_flow_stats),
				    0, SLAB_HWCACHE_ALIGN, शून्य);
	अगर (flow_stats_cache == शून्य) अणु
		kmem_cache_destroy(flow_cache);
		flow_cache = शून्य;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/* Uninitializes the flow module. */
व्योम ovs_flow_निकास(व्योम)
अणु
	kmem_cache_destroy(flow_stats_cache);
	kmem_cache_destroy(flow_cache);
पूर्ण
