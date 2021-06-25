<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2007-2013 Nicira, Inc.
 */

#अगर_अघोषित FLOW_TABLE_H
#घोषणा FLOW_TABLE_H 1

#समावेश <linux/kernel.h>
#समावेश <linux/netlink.h>
#समावेश <linux/खोलोvचयन.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/in6.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समय.स>

#समावेश <net/inet_ecn.h>
#समावेश <net/ip_tunnels.h>

#समावेश "flow.h"

काष्ठा mask_cache_entry अणु
	u32 skb_hash;
	u32 mask_index;
पूर्ण;

काष्ठा mask_cache अणु
	काष्ठा rcu_head rcu;
	u32 cache_size;  /* Must be ^2 value. */
	काष्ठा mask_cache_entry __percpu *mask_cache;
पूर्ण;

काष्ठा mask_count अणु
	पूर्णांक index;
	u64 counter;
पूर्ण;

काष्ठा mask_array_stats अणु
	काष्ठा u64_stats_sync syncp;
	u64 usage_cntrs[];
पूर्ण;

काष्ठा mask_array अणु
	काष्ठा rcu_head rcu;
	पूर्णांक count, max;
	काष्ठा mask_array_stats __percpu *masks_usage_stats;
	u64 *masks_usage_zero_cntr;
	काष्ठा sw_flow_mask __rcu *masks[];
पूर्ण;

काष्ठा table_instance अणु
	काष्ठा hlist_head *buckets;
	अचिन्हित पूर्णांक n_buckets;
	काष्ठा rcu_head rcu;
	पूर्णांक node_ver;
	u32 hash_seed;
पूर्ण;

काष्ठा flow_table अणु
	काष्ठा table_instance __rcu *ti;
	काष्ठा table_instance __rcu *ufid_ti;
	काष्ठा mask_cache __rcu *mask_cache;
	काष्ठा mask_array __rcu *mask_array;
	अचिन्हित दीर्घ last_rehash;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक ufid_count;
पूर्ण;

बाह्य काष्ठा kmem_cache *flow_stats_cache;

पूर्णांक ovs_flow_init(व्योम);
व्योम ovs_flow_निकास(व्योम);

काष्ठा sw_flow *ovs_flow_alloc(व्योम);
व्योम ovs_flow_मुक्त(काष्ठा sw_flow *, bool deferred);

पूर्णांक ovs_flow_tbl_init(काष्ठा flow_table *);
पूर्णांक ovs_flow_tbl_count(स्थिर काष्ठा flow_table *table);
व्योम ovs_flow_tbl_destroy(काष्ठा flow_table *table);
पूर्णांक ovs_flow_tbl_flush(काष्ठा flow_table *flow_table);

पूर्णांक ovs_flow_tbl_insert(काष्ठा flow_table *table, काष्ठा sw_flow *flow,
			स्थिर काष्ठा sw_flow_mask *mask);
व्योम ovs_flow_tbl_हटाओ(काष्ठा flow_table *table, काष्ठा sw_flow *flow);
पूर्णांक  ovs_flow_tbl_num_masks(स्थिर काष्ठा flow_table *table);
u32  ovs_flow_tbl_masks_cache_size(स्थिर काष्ठा flow_table *table);
पूर्णांक  ovs_flow_tbl_masks_cache_resize(काष्ठा flow_table *table, u32 size);
काष्ठा sw_flow *ovs_flow_tbl_dump_next(काष्ठा table_instance *table,
				       u32 *bucket, u32 *idx);
काष्ठा sw_flow *ovs_flow_tbl_lookup_stats(काष्ठा flow_table *,
					  स्थिर काष्ठा sw_flow_key *,
					  u32 skb_hash,
					  u32 *n_mask_hit,
					  u32 *n_cache_hit);
काष्ठा sw_flow *ovs_flow_tbl_lookup(काष्ठा flow_table *,
				    स्थिर काष्ठा sw_flow_key *);
काष्ठा sw_flow *ovs_flow_tbl_lookup_exact(काष्ठा flow_table *tbl,
					  स्थिर काष्ठा sw_flow_match *match);
काष्ठा sw_flow *ovs_flow_tbl_lookup_ufid(काष्ठा flow_table *,
					 स्थिर काष्ठा sw_flow_id *);

bool ovs_flow_cmp(स्थिर काष्ठा sw_flow *, स्थिर काष्ठा sw_flow_match *);

व्योम ovs_flow_mask_key(काष्ठा sw_flow_key *dst, स्थिर काष्ठा sw_flow_key *src,
		       bool full, स्थिर काष्ठा sw_flow_mask *mask);

व्योम ovs_flow_masks_rebalance(काष्ठा flow_table *table);
व्योम table_instance_flow_flush(काष्ठा flow_table *table,
			       काष्ठा table_instance *ti,
			       काष्ठा table_instance *ufid_ti);

#पूर्ण_अगर /* flow_table.h */
