<शैली गुरु>
/*
 * Copyright (c) 2006, 2018 Oracle and/or its affiliates. All rights reserved.
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
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/rculist.h>
#समावेश <linux/llist.h>

#समावेश "rds_single_path.h"
#समावेश "ib_mr.h"
#समावेश "rds.h"

काष्ठा workqueue_काष्ठा *rds_ib_mr_wq;
काष्ठा rds_ib_dereg_odp_mr अणु
	काष्ठा work_काष्ठा work;
	काष्ठा ib_mr *mr;
पूर्ण;

अटल व्योम rds_ib_odp_mr_worker(काष्ठा work_काष्ठा *work);

अटल काष्ठा rds_ib_device *rds_ib_get_device(__be32 ipaddr)
अणु
	काष्ठा rds_ib_device *rds_ibdev;
	काष्ठा rds_ib_ipaddr *i_ipaddr;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(rds_ibdev, &rds_ib_devices, list) अणु
		list_क्रम_each_entry_rcu(i_ipaddr, &rds_ibdev->ipaddr_list, list) अणु
			अगर (i_ipaddr->ipaddr == ipaddr) अणु
				refcount_inc(&rds_ibdev->refcount);
				rcu_पढ़ो_unlock();
				वापस rds_ibdev;
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस शून्य;
पूर्ण

अटल पूर्णांक rds_ib_add_ipaddr(काष्ठा rds_ib_device *rds_ibdev, __be32 ipaddr)
अणु
	काष्ठा rds_ib_ipaddr *i_ipaddr;

	i_ipaddr = kदो_स्मृति(माप *i_ipaddr, GFP_KERNEL);
	अगर (!i_ipaddr)
		वापस -ENOMEM;

	i_ipaddr->ipaddr = ipaddr;

	spin_lock_irq(&rds_ibdev->spinlock);
	list_add_tail_rcu(&i_ipaddr->list, &rds_ibdev->ipaddr_list);
	spin_unlock_irq(&rds_ibdev->spinlock);

	वापस 0;
पूर्ण

अटल व्योम rds_ib_हटाओ_ipaddr(काष्ठा rds_ib_device *rds_ibdev, __be32 ipaddr)
अणु
	काष्ठा rds_ib_ipaddr *i_ipaddr;
	काष्ठा rds_ib_ipaddr *to_मुक्त = शून्य;


	spin_lock_irq(&rds_ibdev->spinlock);
	list_क्रम_each_entry_rcu(i_ipaddr, &rds_ibdev->ipaddr_list, list) अणु
		अगर (i_ipaddr->ipaddr == ipaddr) अणु
			list_del_rcu(&i_ipaddr->list);
			to_मुक्त = i_ipaddr;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&rds_ibdev->spinlock);

	अगर (to_मुक्त)
		kमुक्त_rcu(to_मुक्त, rcu);
पूर्ण

पूर्णांक rds_ib_update_ipaddr(काष्ठा rds_ib_device *rds_ibdev,
			 काष्ठा in6_addr *ipaddr)
अणु
	काष्ठा rds_ib_device *rds_ibdev_old;

	rds_ibdev_old = rds_ib_get_device(ipaddr->s6_addr32[3]);
	अगर (!rds_ibdev_old)
		वापस rds_ib_add_ipaddr(rds_ibdev, ipaddr->s6_addr32[3]);

	अगर (rds_ibdev_old != rds_ibdev) अणु
		rds_ib_हटाओ_ipaddr(rds_ibdev_old, ipaddr->s6_addr32[3]);
		rds_ib_dev_put(rds_ibdev_old);
		वापस rds_ib_add_ipaddr(rds_ibdev, ipaddr->s6_addr32[3]);
	पूर्ण
	rds_ib_dev_put(rds_ibdev_old);

	वापस 0;
पूर्ण

व्योम rds_ib_add_conn(काष्ठा rds_ib_device *rds_ibdev, काष्ठा rds_connection *conn)
अणु
	काष्ठा rds_ib_connection *ic = conn->c_transport_data;

	/* conn was previously on the nodev_conns_list */
	spin_lock_irq(&ib_nodev_conns_lock);
	BUG_ON(list_empty(&ib_nodev_conns));
	BUG_ON(list_empty(&ic->ib_node));
	list_del(&ic->ib_node);

	spin_lock(&rds_ibdev->spinlock);
	list_add_tail(&ic->ib_node, &rds_ibdev->conn_list);
	spin_unlock(&rds_ibdev->spinlock);
	spin_unlock_irq(&ib_nodev_conns_lock);

	ic->rds_ibdev = rds_ibdev;
	refcount_inc(&rds_ibdev->refcount);
पूर्ण

व्योम rds_ib_हटाओ_conn(काष्ठा rds_ib_device *rds_ibdev, काष्ठा rds_connection *conn)
अणु
	काष्ठा rds_ib_connection *ic = conn->c_transport_data;

	/* place conn on nodev_conns_list */
	spin_lock(&ib_nodev_conns_lock);

	spin_lock_irq(&rds_ibdev->spinlock);
	BUG_ON(list_empty(&ic->ib_node));
	list_del(&ic->ib_node);
	spin_unlock_irq(&rds_ibdev->spinlock);

	list_add_tail(&ic->ib_node, &ib_nodev_conns);

	spin_unlock(&ib_nodev_conns_lock);

	ic->rds_ibdev = शून्य;
	rds_ib_dev_put(rds_ibdev);
पूर्ण

व्योम rds_ib_destroy_nodev_conns(व्योम)
अणु
	काष्ठा rds_ib_connection *ic, *_ic;
	LIST_HEAD(पंचांगp_list);

	/* aव्योम calling conn_destroy with irqs off */
	spin_lock_irq(&ib_nodev_conns_lock);
	list_splice(&ib_nodev_conns, &पंचांगp_list);
	spin_unlock_irq(&ib_nodev_conns_lock);

	list_क्रम_each_entry_safe(ic, _ic, &पंचांगp_list, ib_node)
		rds_conn_destroy(ic->conn);
पूर्ण

व्योम rds_ib_get_mr_info(काष्ठा rds_ib_device *rds_ibdev, काष्ठा rds_info_rdma_connection *iinfo)
अणु
	काष्ठा rds_ib_mr_pool *pool_1m = rds_ibdev->mr_1m_pool;

	iinfo->rdma_mr_max = pool_1m->max_items;
	iinfo->rdma_mr_size = pool_1m->max_pages;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
व्योम rds6_ib_get_mr_info(काष्ठा rds_ib_device *rds_ibdev,
			 काष्ठा rds6_info_rdma_connection *iinfo6)
अणु
	काष्ठा rds_ib_mr_pool *pool_1m = rds_ibdev->mr_1m_pool;

	iinfo6->rdma_mr_max = pool_1m->max_items;
	iinfo6->rdma_mr_size = pool_1m->max_pages;
पूर्ण
#पूर्ण_अगर

काष्ठा rds_ib_mr *rds_ib_reuse_mr(काष्ठा rds_ib_mr_pool *pool)
अणु
	काष्ठा rds_ib_mr *ibmr = शून्य;
	काष्ठा llist_node *ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pool->clean_lock, flags);
	ret = llist_del_first(&pool->clean_list);
	spin_unlock_irqrestore(&pool->clean_lock, flags);
	अगर (ret) अणु
		ibmr = llist_entry(ret, काष्ठा rds_ib_mr, llnode);
		अगर (pool->pool_type == RDS_IB_MR_8K_POOL)
			rds_ib_stats_inc(s_ib_rdma_mr_8k_reused);
		अन्यथा
			rds_ib_stats_inc(s_ib_rdma_mr_1m_reused);
	पूर्ण

	वापस ibmr;
पूर्ण

व्योम rds_ib_sync_mr(व्योम *trans_निजी, पूर्णांक direction)
अणु
	काष्ठा rds_ib_mr *ibmr = trans_निजी;
	काष्ठा rds_ib_device *rds_ibdev = ibmr->device;

	अगर (ibmr->odp)
		वापस;

	चयन (direction) अणु
	हाल DMA_FROM_DEVICE:
		ib_dma_sync_sg_क्रम_cpu(rds_ibdev->dev, ibmr->sg,
			ibmr->sg_dma_len, DMA_BIसूचीECTIONAL);
		अवरोध;
	हाल DMA_TO_DEVICE:
		ib_dma_sync_sg_क्रम_device(rds_ibdev->dev, ibmr->sg,
			ibmr->sg_dma_len, DMA_BIसूचीECTIONAL);
		अवरोध;
	पूर्ण
पूर्ण

व्योम __rds_ib_tearकरोwn_mr(काष्ठा rds_ib_mr *ibmr)
अणु
	काष्ठा rds_ib_device *rds_ibdev = ibmr->device;

	अगर (ibmr->sg_dma_len) अणु
		ib_dma_unmap_sg(rds_ibdev->dev,
				ibmr->sg, ibmr->sg_len,
				DMA_BIसूचीECTIONAL);
		ibmr->sg_dma_len = 0;
	पूर्ण

	/* Release the s/g list */
	अगर (ibmr->sg_len) अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < ibmr->sg_len; ++i) अणु
			काष्ठा page *page = sg_page(&ibmr->sg[i]);

			/* FIXME we need a way to tell a r/w MR
			 * from a r/o MR */
			WARN_ON(!page->mapping && irqs_disabled());
			set_page_dirty(page);
			put_page(page);
		पूर्ण
		kमुक्त(ibmr->sg);

		ibmr->sg = शून्य;
		ibmr->sg_len = 0;
	पूर्ण
पूर्ण

व्योम rds_ib_tearकरोwn_mr(काष्ठा rds_ib_mr *ibmr)
अणु
	अचिन्हित पूर्णांक pinned = ibmr->sg_len;

	__rds_ib_tearकरोwn_mr(ibmr);
	अगर (pinned) अणु
		काष्ठा rds_ib_mr_pool *pool = ibmr->pool;

		atomic_sub(pinned, &pool->मुक्त_pinned);
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक rds_ib_flush_goal(काष्ठा rds_ib_mr_pool *pool, पूर्णांक मुक्त_all)
अणु
	अचिन्हित पूर्णांक item_count;

	item_count = atomic_पढ़ो(&pool->item_count);
	अगर (मुक्त_all)
		वापस item_count;

	वापस 0;
पूर्ण

/*
 * given an llist of mrs, put them all पूर्णांकo the list_head क्रम more processing
 */
अटल अचिन्हित पूर्णांक llist_append_to_list(काष्ठा llist_head *llist,
					 काष्ठा list_head *list)
अणु
	काष्ठा rds_ib_mr *ibmr;
	काष्ठा llist_node *node;
	काष्ठा llist_node *next;
	अचिन्हित पूर्णांक count = 0;

	node = llist_del_all(llist);
	जबतक (node) अणु
		next = node->next;
		ibmr = llist_entry(node, काष्ठा rds_ib_mr, llnode);
		list_add_tail(&ibmr->unmap_list, list);
		node = next;
		count++;
	पूर्ण
	वापस count;
पूर्ण

/*
 * this takes a list head of mrs and turns it पूर्णांकo linked llist nodes
 * of clusters.  Each cluster has linked llist nodes of
 * MR_CLUSTER_SIZE mrs that are पढ़ोy क्रम reuse.
 */
अटल व्योम list_to_llist_nodes(काष्ठा list_head *list,
				काष्ठा llist_node **nodes_head,
				काष्ठा llist_node **nodes_tail)
अणु
	काष्ठा rds_ib_mr *ibmr;
	काष्ठा llist_node *cur = शून्य;
	काष्ठा llist_node **next = nodes_head;

	list_क्रम_each_entry(ibmr, list, unmap_list) अणु
		cur = &ibmr->llnode;
		*next = cur;
		next = &cur->next;
	पूर्ण
	*next = शून्य;
	*nodes_tail = cur;
पूर्ण

/*
 * Flush our pool of MRs.
 * At a minimum, all currently unused MRs are unmapped.
 * If the number of MRs allocated exceeds the limit, we also try
 * to मुक्त as many MRs as needed to get back to this limit.
 */
पूर्णांक rds_ib_flush_mr_pool(काष्ठा rds_ib_mr_pool *pool,
			 पूर्णांक मुक्त_all, काष्ठा rds_ib_mr **ibmr_ret)
अणु
	काष्ठा rds_ib_mr *ibmr;
	काष्ठा llist_node *clean_nodes;
	काष्ठा llist_node *clean_tail;
	LIST_HEAD(unmap_list);
	अचिन्हित दीर्घ unpinned = 0;
	अचिन्हित पूर्णांक nमुक्तd = 0, dirty_to_clean = 0, मुक्त_goal;

	अगर (pool->pool_type == RDS_IB_MR_8K_POOL)
		rds_ib_stats_inc(s_ib_rdma_mr_8k_pool_flush);
	अन्यथा
		rds_ib_stats_inc(s_ib_rdma_mr_1m_pool_flush);

	अगर (ibmr_ret) अणु
		DEFINE_WAIT(रुको);
		जबतक (!mutex_trylock(&pool->flush_lock)) अणु
			ibmr = rds_ib_reuse_mr(pool);
			अगर (ibmr) अणु
				*ibmr_ret = ibmr;
				finish_रुको(&pool->flush_रुको, &रुको);
				जाओ out_nolock;
			पूर्ण

			prepare_to_रुको(&pool->flush_रुको, &रुको,
					TASK_UNINTERRUPTIBLE);
			अगर (llist_empty(&pool->clean_list))
				schedule();

			ibmr = rds_ib_reuse_mr(pool);
			अगर (ibmr) अणु
				*ibmr_ret = ibmr;
				finish_रुको(&pool->flush_रुको, &रुको);
				जाओ out_nolock;
			पूर्ण
		पूर्ण
		finish_रुको(&pool->flush_रुको, &रुको);
	पूर्ण अन्यथा
		mutex_lock(&pool->flush_lock);

	अगर (ibmr_ret) अणु
		ibmr = rds_ib_reuse_mr(pool);
		अगर (ibmr) अणु
			*ibmr_ret = ibmr;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Get the list of all MRs to be dropped. Ordering matters -
	 * we want to put drop_list ahead of मुक्त_list.
	 */
	dirty_to_clean = llist_append_to_list(&pool->drop_list, &unmap_list);
	dirty_to_clean += llist_append_to_list(&pool->मुक्त_list, &unmap_list);
	अगर (मुक्त_all) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&pool->clean_lock, flags);
		llist_append_to_list(&pool->clean_list, &unmap_list);
		spin_unlock_irqrestore(&pool->clean_lock, flags);
	पूर्ण

	मुक्त_goal = rds_ib_flush_goal(pool, मुक्त_all);

	अगर (list_empty(&unmap_list))
		जाओ out;

	rds_ib_unreg_frmr(&unmap_list, &nमुक्तd, &unpinned, मुक्त_goal);

	अगर (!list_empty(&unmap_list)) अणु
		अचिन्हित दीर्घ flags;

		list_to_llist_nodes(&unmap_list, &clean_nodes, &clean_tail);
		अगर (ibmr_ret) अणु
			*ibmr_ret = llist_entry(clean_nodes, काष्ठा rds_ib_mr, llnode);
			clean_nodes = clean_nodes->next;
		पूर्ण
		/* more than one entry in llist nodes */
		अगर (clean_nodes) अणु
			spin_lock_irqsave(&pool->clean_lock, flags);
			llist_add_batch(clean_nodes, clean_tail,
					&pool->clean_list);
			spin_unlock_irqrestore(&pool->clean_lock, flags);
		पूर्ण
	पूर्ण

	atomic_sub(unpinned, &pool->मुक्त_pinned);
	atomic_sub(dirty_to_clean, &pool->dirty_count);
	atomic_sub(nमुक्तd, &pool->item_count);

out:
	mutex_unlock(&pool->flush_lock);
	अगर (रुकोqueue_active(&pool->flush_रुको))
		wake_up(&pool->flush_रुको);
out_nolock:
	वापस 0;
पूर्ण

काष्ठा rds_ib_mr *rds_ib_try_reuse_ibmr(काष्ठा rds_ib_mr_pool *pool)
अणु
	काष्ठा rds_ib_mr *ibmr = शून्य;
	पूर्णांक iter = 0;

	जबतक (1) अणु
		ibmr = rds_ib_reuse_mr(pool);
		अगर (ibmr)
			वापस ibmr;

		अगर (atomic_inc_वापस(&pool->item_count) <= pool->max_items)
			अवरोध;

		atomic_dec(&pool->item_count);

		अगर (++iter > 2) अणु
			अगर (pool->pool_type == RDS_IB_MR_8K_POOL)
				rds_ib_stats_inc(s_ib_rdma_mr_8k_pool_depleted);
			अन्यथा
				rds_ib_stats_inc(s_ib_rdma_mr_1m_pool_depleted);
			अवरोध;
		पूर्ण

		/* We करो have some empty MRs. Flush them out. */
		अगर (pool->pool_type == RDS_IB_MR_8K_POOL)
			rds_ib_stats_inc(s_ib_rdma_mr_8k_pool_रुको);
		अन्यथा
			rds_ib_stats_inc(s_ib_rdma_mr_1m_pool_रुको);

		rds_ib_flush_mr_pool(pool, 0, &ibmr);
		अगर (ibmr)
			वापस ibmr;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम rds_ib_mr_pool_flush_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rds_ib_mr_pool *pool = container_of(work, काष्ठा rds_ib_mr_pool, flush_worker.work);

	rds_ib_flush_mr_pool(pool, 0, शून्य);
पूर्ण

व्योम rds_ib_मुक्त_mr(व्योम *trans_निजी, पूर्णांक invalidate)
अणु
	काष्ठा rds_ib_mr *ibmr = trans_निजी;
	काष्ठा rds_ib_mr_pool *pool = ibmr->pool;
	काष्ठा rds_ib_device *rds_ibdev = ibmr->device;

	rdsdebug("RDS/IB: free_mr nents %u\n", ibmr->sg_len);

	अगर (ibmr->odp) अणु
		/* A MR created and marked as use_once. We use delayed work,
		 * because there is a change that we are in पूर्णांकerrupt and can't
		 * call to ib_dereg_mr() directly.
		 */
		INIT_DELAYED_WORK(&ibmr->work, rds_ib_odp_mr_worker);
		queue_delayed_work(rds_ib_mr_wq, &ibmr->work, 0);
		वापस;
	पूर्ण

	/* Return it to the pool's मुक्त list */
	rds_ib_मुक्त_frmr_list(ibmr);

	atomic_add(ibmr->sg_len, &pool->मुक्त_pinned);
	atomic_inc(&pool->dirty_count);

	/* If we've pinned too many pages, request a flush */
	अगर (atomic_पढ़ो(&pool->मुक्त_pinned) >= pool->max_मुक्त_pinned ||
	    atomic_पढ़ो(&pool->dirty_count) >= pool->max_items / 5)
		queue_delayed_work(rds_ib_mr_wq, &pool->flush_worker, 10);

	अगर (invalidate) अणु
		अगर (likely(!in_पूर्णांकerrupt())) अणु
			rds_ib_flush_mr_pool(pool, 0, शून्य);
		पूर्ण अन्यथा अणु
			/* We get here अगर the user created a MR marked
			 * as use_once and invalidate at the same समय.
			 */
			queue_delayed_work(rds_ib_mr_wq,
					   &pool->flush_worker, 10);
		पूर्ण
	पूर्ण

	rds_ib_dev_put(rds_ibdev);
पूर्ण

व्योम rds_ib_flush_mrs(व्योम)
अणु
	काष्ठा rds_ib_device *rds_ibdev;

	करोwn_पढ़ो(&rds_ib_devices_lock);
	list_क्रम_each_entry(rds_ibdev, &rds_ib_devices, list) अणु
		अगर (rds_ibdev->mr_8k_pool)
			rds_ib_flush_mr_pool(rds_ibdev->mr_8k_pool, 0, शून्य);

		अगर (rds_ibdev->mr_1m_pool)
			rds_ib_flush_mr_pool(rds_ibdev->mr_1m_pool, 0, शून्य);
	पूर्ण
	up_पढ़ो(&rds_ib_devices_lock);
पूर्ण

u32 rds_ib_get_lkey(व्योम *trans_निजी)
अणु
	काष्ठा rds_ib_mr *ibmr = trans_निजी;

	वापस ibmr->u.mr->lkey;
पूर्ण

व्योम *rds_ib_get_mr(काष्ठा scatterlist *sg, अचिन्हित दीर्घ nents,
		    काष्ठा rds_sock *rs, u32 *key_ret,
		    काष्ठा rds_connection *conn,
		    u64 start, u64 length, पूर्णांक need_odp)
अणु
	काष्ठा rds_ib_device *rds_ibdev;
	काष्ठा rds_ib_mr *ibmr = शून्य;
	काष्ठा rds_ib_connection *ic = शून्य;
	पूर्णांक ret;

	rds_ibdev = rds_ib_get_device(rs->rs_bound_addr.s6_addr32[3]);
	अगर (!rds_ibdev) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (need_odp == ODP_ZEROBASED || need_odp == ODP_VIRTUAL) अणु
		u64 virt_addr = need_odp == ODP_ZEROBASED ? 0 : start;
		पूर्णांक access_flags =
			(IB_ACCESS_LOCAL_WRITE | IB_ACCESS_REMOTE_READ |
			 IB_ACCESS_REMOTE_WRITE | IB_ACCESS_REMOTE_ATOMIC |
			 IB_ACCESS_ON_DEMAND);
		काष्ठा ib_sge sge = अणुपूर्ण;
		काष्ठा ib_mr *ib_mr;

		अगर (!rds_ibdev->odp_capable) अणु
			ret = -EOPNOTSUPP;
			जाओ out;
		पूर्ण

		ib_mr = ib_reg_user_mr(rds_ibdev->pd, start, length, virt_addr,
				       access_flags);

		अगर (IS_ERR(ib_mr)) अणु
			rdsdebug("rds_ib_get_user_mr returned %d\n",
				 IS_ERR(ib_mr));
			ret = PTR_ERR(ib_mr);
			जाओ out;
		पूर्ण
		अगर (key_ret)
			*key_ret = ib_mr->rkey;

		ibmr = kzalloc(माप(*ibmr), GFP_KERNEL);
		अगर (!ibmr) अणु
			ib_dereg_mr(ib_mr);
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		ibmr->u.mr = ib_mr;
		ibmr->odp = 1;

		sge.addr = virt_addr;
		sge.length = length;
		sge.lkey = ib_mr->lkey;

		ib_advise_mr(rds_ibdev->pd,
			     IB_UVERBS_ADVISE_MR_ADVICE_PREFETCH_WRITE,
			     IB_UVERBS_ADVISE_MR_FLAG_FLUSH, &sge, 1);
		वापस ibmr;
	पूर्ण

	अगर (conn)
		ic = conn->c_transport_data;

	अगर (!rds_ibdev->mr_8k_pool || !rds_ibdev->mr_1m_pool) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	ibmr = rds_ib_reg_frmr(rds_ibdev, ic, sg, nents, key_ret);
	अगर (IS_ERR(ibmr)) अणु
		ret = PTR_ERR(ibmr);
		pr_warn("RDS/IB: rds_ib_get_mr failed (errno=%d)\n", ret);
	पूर्ण अन्यथा अणु
		वापस ibmr;
	पूर्ण

 out:
	अगर (rds_ibdev)
		rds_ib_dev_put(rds_ibdev);

	वापस ERR_PTR(ret);
पूर्ण

व्योम rds_ib_destroy_mr_pool(काष्ठा rds_ib_mr_pool *pool)
अणु
	cancel_delayed_work_sync(&pool->flush_worker);
	rds_ib_flush_mr_pool(pool, 1, शून्य);
	WARN_ON(atomic_पढ़ो(&pool->item_count));
	WARN_ON(atomic_पढ़ो(&pool->मुक्त_pinned));
	kमुक्त(pool);
पूर्ण

काष्ठा rds_ib_mr_pool *rds_ib_create_mr_pool(काष्ठा rds_ib_device *rds_ibdev,
					     पूर्णांक pool_type)
अणु
	काष्ठा rds_ib_mr_pool *pool;

	pool = kzalloc(माप(*pool), GFP_KERNEL);
	अगर (!pool)
		वापस ERR_PTR(-ENOMEM);

	pool->pool_type = pool_type;
	init_llist_head(&pool->मुक्त_list);
	init_llist_head(&pool->drop_list);
	init_llist_head(&pool->clean_list);
	spin_lock_init(&pool->clean_lock);
	mutex_init(&pool->flush_lock);
	init_रुकोqueue_head(&pool->flush_रुको);
	INIT_DELAYED_WORK(&pool->flush_worker, rds_ib_mr_pool_flush_worker);

	अगर (pool_type == RDS_IB_MR_1M_POOL) अणु
		/* +1 allows क्रम unaligned MRs */
		pool->max_pages = RDS_MR_1M_MSG_SIZE + 1;
		pool->max_items = rds_ibdev->max_1m_mrs;
	पूर्ण अन्यथा अणु
		/* pool_type == RDS_IB_MR_8K_POOL */
		pool->max_pages = RDS_MR_8K_MSG_SIZE + 1;
		pool->max_items = rds_ibdev->max_8k_mrs;
	पूर्ण

	pool->max_मुक्त_pinned = pool->max_items * pool->max_pages / 4;
	pool->max_items_soft = rds_ibdev->max_mrs * 3 / 4;

	वापस pool;
पूर्ण

पूर्णांक rds_ib_mr_init(व्योम)
अणु
	rds_ib_mr_wq = alloc_workqueue("rds_mr_flushd", WQ_MEM_RECLAIM, 0);
	अगर (!rds_ib_mr_wq)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/* By the समय this is called all the IB devices should have been torn करोwn and
 * had their pools मुक्तd.  As each pool is मुक्तd its work काष्ठा is रुकोed on,
 * so the pool flushing work queue should be idle by the समय we get here.
 */
व्योम rds_ib_mr_निकास(व्योम)
अणु
	destroy_workqueue(rds_ib_mr_wq);
पूर्ण

अटल व्योम rds_ib_odp_mr_worker(काष्ठा work_काष्ठा  *work)
अणु
	काष्ठा rds_ib_mr *ibmr;

	ibmr = container_of(work, काष्ठा rds_ib_mr, work.work);
	ib_dereg_mr(ibmr->u.mr);
	kमुक्त(ibmr);
पूर्ण
