<शैली गुरु>
/*
 * Copyright (c) 2016, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/fs.h>
#समावेश <linux/rbtree.h>
#समावेश "mlx5_core.h"
#समावेश "fs_core.h"
#समावेश "fs_cmd.h"

#घोषणा MLX5_FC_STATS_PERIOD msecs_to_jअगरfies(1000)
/* Max number of counters to query in bulk पढ़ो is 32K */
#घोषणा MLX5_SW_MAX_COUNTERS_BULK BIT(15)
#घोषणा MLX5_FC_POOL_MAX_THRESHOLD BIT(18)
#घोषणा MLX5_FC_POOL_USED_BUFF_RATIO 10

काष्ठा mlx5_fc_cache अणु
	u64 packets;
	u64 bytes;
	u64 lastuse;
पूर्ण;

काष्ठा mlx5_fc अणु
	काष्ठा list_head list;
	काष्ठा llist_node addlist;
	काष्ठा llist_node dellist;

	/* lastअणुpackets,bytesपूर्ण members are used when calculating the delta since
	 * last पढ़ोing
	 */
	u64 lastpackets;
	u64 lastbytes;

	काष्ठा mlx5_fc_bulk *bulk;
	u32 id;
	bool aging;

	काष्ठा mlx5_fc_cache cache ____cacheline_aligned_in_smp;
पूर्ण;

अटल व्योम mlx5_fc_pool_init(काष्ठा mlx5_fc_pool *fc_pool, काष्ठा mlx5_core_dev *dev);
अटल व्योम mlx5_fc_pool_cleanup(काष्ठा mlx5_fc_pool *fc_pool);
अटल काष्ठा mlx5_fc *mlx5_fc_pool_acquire_counter(काष्ठा mlx5_fc_pool *fc_pool);
अटल व्योम mlx5_fc_pool_release_counter(काष्ठा mlx5_fc_pool *fc_pool, काष्ठा mlx5_fc *fc);

/* locking scheme:
 *
 * It is the responsibility of the user to prevent concurrent calls or bad
 * ordering to mlx5_fc_create(), mlx5_fc_destroy() and accessing a reference
 * to काष्ठा mlx5_fc.
 * e.g en_tc.c is रक्षित by RTNL lock of its caller, and will never call a
 * dump (access to काष्ठा mlx5_fc) after a counter is destroyed.
 *
 * access to counter list:
 * - create (user context)
 *   - mlx5_fc_create() only adds to an addlist to be used by
 *     mlx5_fc_stats_work(). addlist is a lockless single linked list
 *     that करोesn't require any additional synchronization when adding single
 *     node.
 *   - spawn thपढ़ो to करो the actual destroy
 *
 * - destroy (user context)
 *   - add a counter to lockless dellist
 *   - spawn thपढ़ो to करो the actual del
 *
 * - dump (user context)
 *   user should not call dump after destroy
 *
 * - query (single thपढ़ो workqueue context)
 *   destroy/dump - no conflict (see destroy)
 *   query/dump - packets and bytes might be inconsistent (since update is not
 *                atomic)
 *   query/create - no conflict (see create)
 *   since every create/destroy spawn the work, only after necessary समय has
 *   elapsed, the thपढ़ो will actually query the hardware.
 */

अटल काष्ठा list_head *mlx5_fc_counters_lookup_next(काष्ठा mlx5_core_dev *dev,
						      u32 id)
अणु
	काष्ठा mlx5_fc_stats *fc_stats = &dev->priv.fc_stats;
	अचिन्हित दीर्घ next_id = (अचिन्हित दीर्घ)id + 1;
	काष्ठा mlx5_fc *counter;
	अचिन्हित दीर्घ पंचांगp;

	rcu_पढ़ो_lock();
	/* skip counters that are in idr, but not yet in counters list */
	idr_क्रम_each_entry_जारी_ul(&fc_stats->counters_idr,
				       counter, पंचांगp, next_id) अणु
		अगर (!list_empty(&counter->list))
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस counter ? &counter->list : &fc_stats->counters;
पूर्ण

अटल व्योम mlx5_fc_stats_insert(काष्ठा mlx5_core_dev *dev,
				 काष्ठा mlx5_fc *counter)
अणु
	काष्ठा list_head *next = mlx5_fc_counters_lookup_next(dev, counter->id);

	list_add_tail(&counter->list, next);
पूर्ण

अटल व्योम mlx5_fc_stats_हटाओ(काष्ठा mlx5_core_dev *dev,
				 काष्ठा mlx5_fc *counter)
अणु
	काष्ठा mlx5_fc_stats *fc_stats = &dev->priv.fc_stats;

	list_del(&counter->list);

	spin_lock(&fc_stats->counters_idr_lock);
	WARN_ON(!idr_हटाओ(&fc_stats->counters_idr, counter->id));
	spin_unlock(&fc_stats->counters_idr_lock);
पूर्ण

अटल पूर्णांक get_max_bulk_query_len(काष्ठा mlx5_core_dev *dev)
अणु
	वापस min_t(पूर्णांक, MLX5_SW_MAX_COUNTERS_BULK,
			  (1 << MLX5_CAP_GEN(dev, log_max_flow_counter_bulk)));
पूर्ण

अटल व्योम update_counter_cache(पूर्णांक index, u32 *bulk_raw_data,
				 काष्ठा mlx5_fc_cache *cache)
अणु
	व्योम *stats = MLX5_ADDR_OF(query_flow_counter_out, bulk_raw_data,
			     flow_statistics[index]);
	u64 packets = MLX5_GET64(traffic_counter, stats, packets);
	u64 bytes = MLX5_GET64(traffic_counter, stats, octets);

	अगर (cache->packets == packets)
		वापस;

	cache->packets = packets;
	cache->bytes = bytes;
	cache->lastuse = jअगरfies;
पूर्ण

अटल व्योम mlx5_fc_stats_query_counter_range(काष्ठा mlx5_core_dev *dev,
					      काष्ठा mlx5_fc *first,
					      u32 last_id)
अणु
	काष्ठा mlx5_fc_stats *fc_stats = &dev->priv.fc_stats;
	bool query_more_counters = (first->id <= last_id);
	पूर्णांक max_bulk_len = get_max_bulk_query_len(dev);
	u32 *data = fc_stats->bulk_query_out;
	काष्ठा mlx5_fc *counter = first;
	u32 bulk_base_id;
	पूर्णांक bulk_len;
	पूर्णांक err;

	जबतक (query_more_counters) अणु
		/* first id must be aligned to 4 when using bulk query */
		bulk_base_id = counter->id & ~0x3;

		/* number of counters to query inc. the last counter */
		bulk_len = min_t(पूर्णांक, max_bulk_len,
				 ALIGN(last_id - bulk_base_id + 1, 4));

		err = mlx5_cmd_fc_bulk_query(dev, bulk_base_id, bulk_len,
					     data);
		अगर (err) अणु
			mlx5_core_err(dev, "Error doing bulk query: %d\n", err);
			वापस;
		पूर्ण
		query_more_counters = false;

		list_क्रम_each_entry_from(counter, &fc_stats->counters, list) अणु
			पूर्णांक counter_index = counter->id - bulk_base_id;
			काष्ठा mlx5_fc_cache *cache = &counter->cache;

			अगर (counter->id >= bulk_base_id + bulk_len) अणु
				query_more_counters = true;
				अवरोध;
			पूर्ण

			update_counter_cache(counter_index, data, cache);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mlx5_fc_मुक्त(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_fc *counter)
अणु
	mlx5_cmd_fc_मुक्त(dev, counter->id);
	kमुक्त(counter);
पूर्ण

अटल व्योम mlx5_fc_release(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_fc *counter)
अणु
	काष्ठा mlx5_fc_stats *fc_stats = &dev->priv.fc_stats;

	अगर (counter->bulk)
		mlx5_fc_pool_release_counter(&fc_stats->fc_pool, counter);
	अन्यथा
		mlx5_fc_मुक्त(dev, counter);
पूर्ण

अटल व्योम mlx5_fc_stats_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_core_dev *dev = container_of(work, काष्ठा mlx5_core_dev,
						 priv.fc_stats.work.work);
	काष्ठा mlx5_fc_stats *fc_stats = &dev->priv.fc_stats;
	/* Take dellist first to ensure that counters cannot be deleted beक्रमe
	 * they are inserted.
	 */
	काष्ठा llist_node *dellist = llist_del_all(&fc_stats->dellist);
	काष्ठा llist_node *addlist = llist_del_all(&fc_stats->addlist);
	काष्ठा mlx5_fc *counter = शून्य, *last = शून्य, *पंचांगp;
	अचिन्हित दीर्घ now = jअगरfies;

	अगर (addlist || !list_empty(&fc_stats->counters))
		queue_delayed_work(fc_stats->wq, &fc_stats->work,
				   fc_stats->sampling_पूर्णांकerval);

	llist_क्रम_each_entry(counter, addlist, addlist)
		mlx5_fc_stats_insert(dev, counter);

	llist_क्रम_each_entry_safe(counter, पंचांगp, dellist, dellist) अणु
		mlx5_fc_stats_हटाओ(dev, counter);

		mlx5_fc_release(dev, counter);
	पूर्ण

	अगर (समय_beक्रमe(now, fc_stats->next_query) ||
	    list_empty(&fc_stats->counters))
		वापस;
	last = list_last_entry(&fc_stats->counters, काष्ठा mlx5_fc, list);

	counter = list_first_entry(&fc_stats->counters, काष्ठा mlx5_fc,
				   list);
	अगर (counter)
		mlx5_fc_stats_query_counter_range(dev, counter, last->id);

	fc_stats->next_query = now + fc_stats->sampling_पूर्णांकerval;
पूर्ण

अटल काष्ठा mlx5_fc *mlx5_fc_single_alloc(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_fc *counter;
	पूर्णांक err;

	counter = kzalloc(माप(*counter), GFP_KERNEL);
	अगर (!counter)
		वापस ERR_PTR(-ENOMEM);

	err = mlx5_cmd_fc_alloc(dev, &counter->id);
	अगर (err) अणु
		kमुक्त(counter);
		वापस ERR_PTR(err);
	पूर्ण

	वापस counter;
पूर्ण

अटल काष्ठा mlx5_fc *mlx5_fc_acquire(काष्ठा mlx5_core_dev *dev, bool aging)
अणु
	काष्ठा mlx5_fc_stats *fc_stats = &dev->priv.fc_stats;
	काष्ठा mlx5_fc *counter;

	अगर (aging && MLX5_CAP_GEN(dev, flow_counter_bulk_alloc) != 0) अणु
		counter = mlx5_fc_pool_acquire_counter(&fc_stats->fc_pool);
		अगर (!IS_ERR(counter))
			वापस counter;
	पूर्ण

	वापस mlx5_fc_single_alloc(dev);
पूर्ण

काष्ठा mlx5_fc *mlx5_fc_create(काष्ठा mlx5_core_dev *dev, bool aging)
अणु
	काष्ठा mlx5_fc *counter = mlx5_fc_acquire(dev, aging);
	काष्ठा mlx5_fc_stats *fc_stats = &dev->priv.fc_stats;
	पूर्णांक err;

	अगर (IS_ERR(counter))
		वापस counter;

	INIT_LIST_HEAD(&counter->list);
	counter->aging = aging;

	अगर (aging) अणु
		u32 id = counter->id;

		counter->cache.lastuse = jअगरfies;
		counter->lastbytes = counter->cache.bytes;
		counter->lastpackets = counter->cache.packets;

		idr_preload(GFP_KERNEL);
		spin_lock(&fc_stats->counters_idr_lock);

		err = idr_alloc_u32(&fc_stats->counters_idr, counter, &id, id,
				    GFP_NOWAIT);

		spin_unlock(&fc_stats->counters_idr_lock);
		idr_preload_end();
		अगर (err)
			जाओ err_out_alloc;

		llist_add(&counter->addlist, &fc_stats->addlist);

		mod_delayed_work(fc_stats->wq, &fc_stats->work, 0);
	पूर्ण

	वापस counter;

err_out_alloc:
	mlx5_fc_release(dev, counter);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(mlx5_fc_create);

u32 mlx5_fc_id(काष्ठा mlx5_fc *counter)
अणु
	वापस counter->id;
पूर्ण
EXPORT_SYMBOL(mlx5_fc_id);

व्योम mlx5_fc_destroy(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_fc *counter)
अणु
	काष्ठा mlx5_fc_stats *fc_stats = &dev->priv.fc_stats;

	अगर (!counter)
		वापस;

	अगर (counter->aging) अणु
		llist_add(&counter->dellist, &fc_stats->dellist);
		mod_delayed_work(fc_stats->wq, &fc_stats->work, 0);
		वापस;
	पूर्ण

	mlx5_fc_release(dev, counter);
पूर्ण
EXPORT_SYMBOL(mlx5_fc_destroy);

पूर्णांक mlx5_init_fc_stats(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_fc_stats *fc_stats = &dev->priv.fc_stats;
	पूर्णांक max_bulk_len;
	पूर्णांक max_out_len;

	spin_lock_init(&fc_stats->counters_idr_lock);
	idr_init(&fc_stats->counters_idr);
	INIT_LIST_HEAD(&fc_stats->counters);
	init_llist_head(&fc_stats->addlist);
	init_llist_head(&fc_stats->dellist);

	max_bulk_len = get_max_bulk_query_len(dev);
	max_out_len = mlx5_cmd_fc_get_bulk_query_out_len(max_bulk_len);
	fc_stats->bulk_query_out = kzalloc(max_out_len, GFP_KERNEL);
	अगर (!fc_stats->bulk_query_out)
		वापस -ENOMEM;

	fc_stats->wq = create_singlethपढ़ो_workqueue("mlx5_fc");
	अगर (!fc_stats->wq)
		जाओ err_wq_create;

	fc_stats->sampling_पूर्णांकerval = MLX5_FC_STATS_PERIOD;
	INIT_DELAYED_WORK(&fc_stats->work, mlx5_fc_stats_work);

	mlx5_fc_pool_init(&fc_stats->fc_pool, dev);
	वापस 0;

err_wq_create:
	kमुक्त(fc_stats->bulk_query_out);
	वापस -ENOMEM;
पूर्ण

व्योम mlx5_cleanup_fc_stats(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_fc_stats *fc_stats = &dev->priv.fc_stats;
	काष्ठा llist_node *पंचांगplist;
	काष्ठा mlx5_fc *counter;
	काष्ठा mlx5_fc *पंचांगp;

	cancel_delayed_work_sync(&dev->priv.fc_stats.work);
	destroy_workqueue(dev->priv.fc_stats.wq);
	dev->priv.fc_stats.wq = शून्य;

	पंचांगplist = llist_del_all(&fc_stats->addlist);
	llist_क्रम_each_entry_safe(counter, पंचांगp, पंचांगplist, addlist)
		mlx5_fc_release(dev, counter);

	list_क्रम_each_entry_safe(counter, पंचांगp, &fc_stats->counters, list)
		mlx5_fc_release(dev, counter);

	mlx5_fc_pool_cleanup(&fc_stats->fc_pool);
	idr_destroy(&fc_stats->counters_idr);
	kमुक्त(fc_stats->bulk_query_out);
पूर्ण

पूर्णांक mlx5_fc_query(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_fc *counter,
		  u64 *packets, u64 *bytes)
अणु
	वापस mlx5_cmd_fc_query(dev, counter->id, packets, bytes);
पूर्ण
EXPORT_SYMBOL(mlx5_fc_query);

u64 mlx5_fc_query_lastuse(काष्ठा mlx5_fc *counter)
अणु
	वापस counter->cache.lastuse;
पूर्ण

व्योम mlx5_fc_query_cached(काष्ठा mlx5_fc *counter,
			  u64 *bytes, u64 *packets, u64 *lastuse)
अणु
	काष्ठा mlx5_fc_cache c;

	c = counter->cache;

	*bytes = c.bytes - counter->lastbytes;
	*packets = c.packets - counter->lastpackets;
	*lastuse = c.lastuse;

	counter->lastbytes = c.bytes;
	counter->lastpackets = c.packets;
पूर्ण

व्योम mlx5_fc_queue_stats_work(काष्ठा mlx5_core_dev *dev,
			      काष्ठा delayed_work *dwork,
			      अचिन्हित दीर्घ delay)
अणु
	काष्ठा mlx5_fc_stats *fc_stats = &dev->priv.fc_stats;

	queue_delayed_work(fc_stats->wq, dwork, delay);
पूर्ण

व्योम mlx5_fc_update_sampling_पूर्णांकerval(काष्ठा mlx5_core_dev *dev,
				      अचिन्हित दीर्घ पूर्णांकerval)
अणु
	काष्ठा mlx5_fc_stats *fc_stats = &dev->priv.fc_stats;

	fc_stats->sampling_पूर्णांकerval = min_t(अचिन्हित दीर्घ, पूर्णांकerval,
					    fc_stats->sampling_पूर्णांकerval);
पूर्ण

/* Flow counter bluks */

काष्ठा mlx5_fc_bulk अणु
	काष्ठा list_head pool_list;
	u32 base_id;
	पूर्णांक bulk_len;
	अचिन्हित दीर्घ *biपंचांगask;
	काष्ठा mlx5_fc fcs[];
पूर्ण;

अटल व्योम mlx5_fc_init(काष्ठा mlx5_fc *counter, काष्ठा mlx5_fc_bulk *bulk,
			 u32 id)
अणु
	counter->bulk = bulk;
	counter->id = id;
पूर्ण

अटल पूर्णांक mlx5_fc_bulk_get_मुक्त_fcs_amount(काष्ठा mlx5_fc_bulk *bulk)
अणु
	वापस biपंचांगap_weight(bulk->biपंचांगask, bulk->bulk_len);
पूर्ण

अटल काष्ठा mlx5_fc_bulk *mlx5_fc_bulk_create(काष्ठा mlx5_core_dev *dev)
अणु
	क्रमागत mlx5_fc_bulk_alloc_biपंचांगask alloc_biपंचांगask;
	काष्ठा mlx5_fc_bulk *bulk;
	पूर्णांक err = -ENOMEM;
	पूर्णांक bulk_len;
	u32 base_id;
	पूर्णांक i;

	alloc_biपंचांगask = MLX5_CAP_GEN(dev, flow_counter_bulk_alloc);
	bulk_len = alloc_biपंचांगask > 0 ? MLX5_FC_BULK_NUM_FCS(alloc_biपंचांगask) : 1;

	bulk = kvzalloc(माप(*bulk) + bulk_len * माप(काष्ठा mlx5_fc),
			GFP_KERNEL);
	अगर (!bulk)
		जाओ err_alloc_bulk;

	bulk->biपंचांगask = kvसुस्मृति(BITS_TO_LONGS(bulk_len), माप(अचिन्हित दीर्घ),
				 GFP_KERNEL);
	अगर (!bulk->biपंचांगask)
		जाओ err_alloc_biपंचांगask;

	err = mlx5_cmd_fc_bulk_alloc(dev, alloc_biपंचांगask, &base_id);
	अगर (err)
		जाओ err_mlx5_cmd_bulk_alloc;

	bulk->base_id = base_id;
	bulk->bulk_len = bulk_len;
	क्रम (i = 0; i < bulk_len; i++) अणु
		mlx5_fc_init(&bulk->fcs[i], bulk, base_id + i);
		set_bit(i, bulk->biपंचांगask);
	पूर्ण

	वापस bulk;

err_mlx5_cmd_bulk_alloc:
	kvमुक्त(bulk->biपंचांगask);
err_alloc_biपंचांगask:
	kvमुक्त(bulk);
err_alloc_bulk:
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक
mlx5_fc_bulk_destroy(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_fc_bulk *bulk)
अणु
	अगर (mlx5_fc_bulk_get_मुक्त_fcs_amount(bulk) < bulk->bulk_len) अणु
		mlx5_core_err(dev, "Freeing bulk before all counters were released\n");
		वापस -EBUSY;
	पूर्ण

	mlx5_cmd_fc_मुक्त(dev, bulk->base_id);
	kvमुक्त(bulk->biपंचांगask);
	kvमुक्त(bulk);

	वापस 0;
पूर्ण

अटल काष्ठा mlx5_fc *mlx5_fc_bulk_acquire_fc(काष्ठा mlx5_fc_bulk *bulk)
अणु
	पूर्णांक मुक्त_fc_index = find_first_bit(bulk->biपंचांगask, bulk->bulk_len);

	अगर (मुक्त_fc_index >= bulk->bulk_len)
		वापस ERR_PTR(-ENOSPC);

	clear_bit(मुक्त_fc_index, bulk->biपंचांगask);
	वापस &bulk->fcs[मुक्त_fc_index];
पूर्ण

अटल पूर्णांक mlx5_fc_bulk_release_fc(काष्ठा mlx5_fc_bulk *bulk, काष्ठा mlx5_fc *fc)
अणु
	पूर्णांक fc_index = fc->id - bulk->base_id;

	अगर (test_bit(fc_index, bulk->biपंचांगask))
		वापस -EINVAL;

	set_bit(fc_index, bulk->biपंचांगask);
	वापस 0;
पूर्ण

/* Flow counters pool API */

अटल व्योम mlx5_fc_pool_init(काष्ठा mlx5_fc_pool *fc_pool, काष्ठा mlx5_core_dev *dev)
अणु
	fc_pool->dev = dev;
	mutex_init(&fc_pool->pool_lock);
	INIT_LIST_HEAD(&fc_pool->fully_used);
	INIT_LIST_HEAD(&fc_pool->partially_used);
	INIT_LIST_HEAD(&fc_pool->unused);
	fc_pool->available_fcs = 0;
	fc_pool->used_fcs = 0;
	fc_pool->threshold = 0;
पूर्ण

अटल व्योम mlx5_fc_pool_cleanup(काष्ठा mlx5_fc_pool *fc_pool)
अणु
	काष्ठा mlx5_core_dev *dev = fc_pool->dev;
	काष्ठा mlx5_fc_bulk *bulk;
	काष्ठा mlx5_fc_bulk *पंचांगp;

	list_क्रम_each_entry_safe(bulk, पंचांगp, &fc_pool->fully_used, pool_list)
		mlx5_fc_bulk_destroy(dev, bulk);
	list_क्रम_each_entry_safe(bulk, पंचांगp, &fc_pool->partially_used, pool_list)
		mlx5_fc_bulk_destroy(dev, bulk);
	list_क्रम_each_entry_safe(bulk, पंचांगp, &fc_pool->unused, pool_list)
		mlx5_fc_bulk_destroy(dev, bulk);
पूर्ण

अटल व्योम mlx5_fc_pool_update_threshold(काष्ठा mlx5_fc_pool *fc_pool)
अणु
	fc_pool->threshold = min_t(पूर्णांक, MLX5_FC_POOL_MAX_THRESHOLD,
				   fc_pool->used_fcs / MLX5_FC_POOL_USED_BUFF_RATIO);
पूर्ण

अटल काष्ठा mlx5_fc_bulk *
mlx5_fc_pool_alloc_new_bulk(काष्ठा mlx5_fc_pool *fc_pool)
अणु
	काष्ठा mlx5_core_dev *dev = fc_pool->dev;
	काष्ठा mlx5_fc_bulk *new_bulk;

	new_bulk = mlx5_fc_bulk_create(dev);
	अगर (!IS_ERR(new_bulk))
		fc_pool->available_fcs += new_bulk->bulk_len;
	mlx5_fc_pool_update_threshold(fc_pool);
	वापस new_bulk;
पूर्ण

अटल व्योम
mlx5_fc_pool_मुक्त_bulk(काष्ठा mlx5_fc_pool *fc_pool, काष्ठा mlx5_fc_bulk *bulk)
अणु
	काष्ठा mlx5_core_dev *dev = fc_pool->dev;

	fc_pool->available_fcs -= bulk->bulk_len;
	mlx5_fc_bulk_destroy(dev, bulk);
	mlx5_fc_pool_update_threshold(fc_pool);
पूर्ण

अटल काष्ठा mlx5_fc *
mlx5_fc_pool_acquire_from_list(काष्ठा list_head *src_list,
			       काष्ठा list_head *next_list,
			       bool move_non_full_bulk)
अणु
	काष्ठा mlx5_fc_bulk *bulk;
	काष्ठा mlx5_fc *fc;

	अगर (list_empty(src_list))
		वापस ERR_PTR(-ENODATA);

	bulk = list_first_entry(src_list, काष्ठा mlx5_fc_bulk, pool_list);
	fc = mlx5_fc_bulk_acquire_fc(bulk);
	अगर (move_non_full_bulk || mlx5_fc_bulk_get_मुक्त_fcs_amount(bulk) == 0)
		list_move(&bulk->pool_list, next_list);
	वापस fc;
पूर्ण

अटल काष्ठा mlx5_fc *
mlx5_fc_pool_acquire_counter(काष्ठा mlx5_fc_pool *fc_pool)
अणु
	काष्ठा mlx5_fc_bulk *new_bulk;
	काष्ठा mlx5_fc *fc;

	mutex_lock(&fc_pool->pool_lock);

	fc = mlx5_fc_pool_acquire_from_list(&fc_pool->partially_used,
					    &fc_pool->fully_used, false);
	अगर (IS_ERR(fc))
		fc = mlx5_fc_pool_acquire_from_list(&fc_pool->unused,
						    &fc_pool->partially_used,
						    true);
	अगर (IS_ERR(fc)) अणु
		new_bulk = mlx5_fc_pool_alloc_new_bulk(fc_pool);
		अगर (IS_ERR(new_bulk)) अणु
			fc = ERR_CAST(new_bulk);
			जाओ out;
		पूर्ण
		fc = mlx5_fc_bulk_acquire_fc(new_bulk);
		list_add(&new_bulk->pool_list, &fc_pool->partially_used);
	पूर्ण
	fc_pool->available_fcs--;
	fc_pool->used_fcs++;

out:
	mutex_unlock(&fc_pool->pool_lock);
	वापस fc;
पूर्ण

अटल व्योम
mlx5_fc_pool_release_counter(काष्ठा mlx5_fc_pool *fc_pool, काष्ठा mlx5_fc *fc)
अणु
	काष्ठा mlx5_core_dev *dev = fc_pool->dev;
	काष्ठा mlx5_fc_bulk *bulk = fc->bulk;
	पूर्णांक bulk_मुक्त_fcs_amount;

	mutex_lock(&fc_pool->pool_lock);

	अगर (mlx5_fc_bulk_release_fc(bulk, fc)) अणु
		mlx5_core_warn(dev, "Attempted to release a counter which is not acquired\n");
		जाओ unlock;
	पूर्ण

	fc_pool->available_fcs++;
	fc_pool->used_fcs--;

	bulk_मुक्त_fcs_amount = mlx5_fc_bulk_get_मुक्त_fcs_amount(bulk);
	अगर (bulk_मुक्त_fcs_amount == 1)
		list_move_tail(&bulk->pool_list, &fc_pool->partially_used);
	अगर (bulk_मुक्त_fcs_amount == bulk->bulk_len) अणु
		list_del(&bulk->pool_list);
		अगर (fc_pool->available_fcs > fc_pool->threshold)
			mlx5_fc_pool_मुक्त_bulk(fc_pool, bulk);
		अन्यथा
			list_add(&bulk->pool_list, &fc_pool->unused);
	पूर्ण

unlock:
	mutex_unlock(&fc_pool->pool_lock);
पूर्ण
