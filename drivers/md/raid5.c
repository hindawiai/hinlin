<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * raid5.c : Multiple Devices driver क्रम Linux
 *	   Copyright (C) 1996, 1997 Ingo Molnar, Miguel de Icaza, Gadi Oxman
 *	   Copyright (C) 1999, 2000 Ingo Molnar
 *	   Copyright (C) 2002, 2003 H. Peter Anvin
 *
 * RAID-4/5/6 management functions.
 * Thanks to Penguin Computing क्रम making the RAID-6 development possible
 * by करोnating a test server!
 */

/*
 * BITMAP UNPLUGGING:
 *
 * The sequencing क्रम updating the biपंचांगap reliably is a little
 * subtle (and I got it wrong the first समय) so it deserves some
 * explanation.
 *
 * We group biपंचांगap updates पूर्णांकo batches.  Each batch has a number.
 * We may ग_लिखो out several batches at once, but that isn't very important.
 * conf->seq_ग_लिखो is the number of the last batch successfully written.
 * conf->seq_flush is the number of the last batch that was बंदd to
 *    new additions.
 * When we discover that we will need to ग_लिखो to any block in a stripe
 * (in add_stripe_bio) we update the in-memory biपंचांगap and record in sh->bm_seq
 * the number of the batch it will be in. This is seq_flush+1.
 * When we are पढ़ोy to करो a ग_लिखो, अगर that batch hasn't been written yet,
 *   we plug the array and queue the stripe क्रम later.
 * When an unplug happens, we increment bm_flush, thus closing the current
 *   batch.
 * When we notice that bm_flush > bm_ग_लिखो, we ग_लिखो out all pending updates
 * to the biपंचांगap, and advance bm_ग_लिखो to where bm_flush was.
 * This may occasionally ग_लिखो a bit out twice, but is sure never to
 * miss any bits.
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/raid/pq.h>
#समावेश <linux/async_tx.h>
#समावेश <linux/module.h>
#समावेश <linux/async.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/cpu.h>
#समावेश <linux/slab.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/nodemask.h>

#समावेश <trace/events/block.h>
#समावेश <linux/list_sort.h>

#समावेश "md.h"
#समावेश "raid5.h"
#समावेश "raid0.h"
#समावेश "md-bitmap.h"
#समावेश "raid5-log.h"

#घोषणा UNSUPPORTED_MDDEV_FLAGS	(1L << MD_FAILFAST_SUPPORTED)

#घोषणा cpu_to_group(cpu) cpu_to_node(cpu)
#घोषणा ANY_GROUP NUMA_NO_NODE

अटल bool devices_handle_discard_safely = false;
module_param(devices_handle_discard_safely, bool, 0644);
MODULE_PARM_DESC(devices_handle_discard_safely,
		 "Set to Y if all devices in each array reliably return zeroes on reads from discarded regions");
अटल काष्ठा workqueue_काष्ठा *raid5_wq;

अटल अंतरभूत काष्ठा hlist_head *stripe_hash(काष्ठा r5conf *conf, sector_t sect)
अणु
	पूर्णांक hash = (sect >> RAID5_STRIPE_SHIFT(conf)) & HASH_MASK;
	वापस &conf->stripe_hashtbl[hash];
पूर्ण

अटल अंतरभूत पूर्णांक stripe_hash_locks_hash(काष्ठा r5conf *conf, sector_t sect)
अणु
	वापस (sect >> RAID5_STRIPE_SHIFT(conf)) & STRIPE_HASH_LOCKS_MASK;
पूर्ण

अटल अंतरभूत व्योम lock_device_hash_lock(काष्ठा r5conf *conf, पूर्णांक hash)
अणु
	spin_lock_irq(conf->hash_locks + hash);
	spin_lock(&conf->device_lock);
पूर्ण

अटल अंतरभूत व्योम unlock_device_hash_lock(काष्ठा r5conf *conf, पूर्णांक hash)
अणु
	spin_unlock(&conf->device_lock);
	spin_unlock_irq(conf->hash_locks + hash);
पूर्ण

अटल अंतरभूत व्योम lock_all_device_hash_locks_irq(काष्ठा r5conf *conf)
अणु
	पूर्णांक i;
	spin_lock_irq(conf->hash_locks);
	क्रम (i = 1; i < NR_STRIPE_HASH_LOCKS; i++)
		spin_lock_nest_lock(conf->hash_locks + i, conf->hash_locks);
	spin_lock(&conf->device_lock);
पूर्ण

अटल अंतरभूत व्योम unlock_all_device_hash_locks_irq(काष्ठा r5conf *conf)
अणु
	पूर्णांक i;
	spin_unlock(&conf->device_lock);
	क्रम (i = NR_STRIPE_HASH_LOCKS - 1; i; i--)
		spin_unlock(conf->hash_locks + i);
	spin_unlock_irq(conf->hash_locks);
पूर्ण

/* Find first data disk in a raid6 stripe */
अटल अंतरभूत पूर्णांक raid6_d0(काष्ठा stripe_head *sh)
अणु
	अगर (sh->ddf_layout)
		/* ddf always start from first device */
		वापस 0;
	/* md starts just after Q block */
	अगर (sh->qd_idx == sh->disks - 1)
		वापस 0;
	अन्यथा
		वापस sh->qd_idx + 1;
पूर्ण
अटल अंतरभूत पूर्णांक raid6_next_disk(पूर्णांक disk, पूर्णांक raid_disks)
अणु
	disk++;
	वापस (disk < raid_disks) ? disk : 0;
पूर्ण

/* When walking through the disks in a raid5, starting at raid6_d0,
 * We need to map each disk to a 'slot', where the data disks are slot
 * 0 .. raid_disks-3, the parity disk is raid_disks-2 and the Q disk
 * is raid_disks-1.  This help करोes that mapping.
 */
अटल पूर्णांक raid6_idx_to_slot(पूर्णांक idx, काष्ठा stripe_head *sh,
			     पूर्णांक *count, पूर्णांक syndrome_disks)
अणु
	पूर्णांक slot = *count;

	अगर (sh->ddf_layout)
		(*count)++;
	अगर (idx == sh->pd_idx)
		वापस syndrome_disks;
	अगर (idx == sh->qd_idx)
		वापस syndrome_disks + 1;
	अगर (!sh->ddf_layout)
		(*count)++;
	वापस slot;
पूर्ण

अटल व्योम prपूर्णांक_raid5_conf (काष्ठा r5conf *conf);

अटल पूर्णांक stripe_operations_active(काष्ठा stripe_head *sh)
अणु
	वापस sh->check_state || sh->reस्थिरruct_state ||
	       test_bit(STRIPE_BIOFILL_RUN, &sh->state) ||
	       test_bit(STRIPE_COMPUTE_RUN, &sh->state);
पूर्ण

अटल bool stripe_is_lowprio(काष्ठा stripe_head *sh)
अणु
	वापस (test_bit(STRIPE_R5C_FULL_STRIPE, &sh->state) ||
		test_bit(STRIPE_R5C_PARTIAL_STRIPE, &sh->state)) &&
	       !test_bit(STRIPE_R5C_CACHING, &sh->state);
पूर्ण

अटल व्योम raid5_wakeup_stripe_thपढ़ो(काष्ठा stripe_head *sh)
अणु
	काष्ठा r5conf *conf = sh->raid_conf;
	काष्ठा r5worker_group *group;
	पूर्णांक thपढ़ो_cnt;
	पूर्णांक i, cpu = sh->cpu;

	अगर (!cpu_online(cpu)) अणु
		cpu = cpumask_any(cpu_online_mask);
		sh->cpu = cpu;
	पूर्ण

	अगर (list_empty(&sh->lru)) अणु
		काष्ठा r5worker_group *group;
		group = conf->worker_groups + cpu_to_group(cpu);
		अगर (stripe_is_lowprio(sh))
			list_add_tail(&sh->lru, &group->loprio_list);
		अन्यथा
			list_add_tail(&sh->lru, &group->handle_list);
		group->stripes_cnt++;
		sh->group = group;
	पूर्ण

	अगर (conf->worker_cnt_per_group == 0) अणु
		md_wakeup_thपढ़ो(conf->mddev->thपढ़ो);
		वापस;
	पूर्ण

	group = conf->worker_groups + cpu_to_group(sh->cpu);

	group->workers[0].working = true;
	/* at least one worker should run to aव्योम race */
	queue_work_on(sh->cpu, raid5_wq, &group->workers[0].work);

	thपढ़ो_cnt = group->stripes_cnt / MAX_STRIPE_BATCH - 1;
	/* wakeup more workers */
	क्रम (i = 1; i < conf->worker_cnt_per_group && thपढ़ो_cnt > 0; i++) अणु
		अगर (group->workers[i].working == false) अणु
			group->workers[i].working = true;
			queue_work_on(sh->cpu, raid5_wq,
				      &group->workers[i].work);
			thपढ़ो_cnt--;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम करो_release_stripe(काष्ठा r5conf *conf, काष्ठा stripe_head *sh,
			      काष्ठा list_head *temp_inactive_list)
अणु
	पूर्णांक i;
	पूर्णांक injournal = 0;	/* number of date pages with R5_InJournal */

	BUG_ON(!list_empty(&sh->lru));
	BUG_ON(atomic_पढ़ो(&conf->active_stripes)==0);

	अगर (r5c_is_ग_लिखोback(conf->log))
		क्रम (i = sh->disks; i--; )
			अगर (test_bit(R5_InJournal, &sh->dev[i].flags))
				injournal++;
	/*
	 * In the following हालs, the stripe cannot be released to cached
	 * lists. Thereक्रमe, we make the stripe ग_लिखो out and set
	 * STRIPE_HANDLE:
	 *   1. when quiesce in r5c ग_लिखो back;
	 *   2. when resync is requested fot the stripe.
	 */
	अगर (test_bit(STRIPE_SYNC_REQUESTED, &sh->state) ||
	    (conf->quiesce && r5c_is_ग_लिखोback(conf->log) &&
	     !test_bit(STRIPE_HANDLE, &sh->state) && injournal != 0)) अणु
		अगर (test_bit(STRIPE_R5C_CACHING, &sh->state))
			r5c_make_stripe_ग_लिखो_out(sh);
		set_bit(STRIPE_HANDLE, &sh->state);
	पूर्ण

	अगर (test_bit(STRIPE_HANDLE, &sh->state)) अणु
		अगर (test_bit(STRIPE_DELAYED, &sh->state) &&
		    !test_bit(STRIPE_PREREAD_ACTIVE, &sh->state))
			list_add_tail(&sh->lru, &conf->delayed_list);
		अन्यथा अगर (test_bit(STRIPE_BIT_DELAY, &sh->state) &&
			   sh->bm_seq - conf->seq_ग_लिखो > 0)
			list_add_tail(&sh->lru, &conf->biपंचांगap_list);
		अन्यथा अणु
			clear_bit(STRIPE_DELAYED, &sh->state);
			clear_bit(STRIPE_BIT_DELAY, &sh->state);
			अगर (conf->worker_cnt_per_group == 0) अणु
				अगर (stripe_is_lowprio(sh))
					list_add_tail(&sh->lru,
							&conf->loprio_list);
				अन्यथा
					list_add_tail(&sh->lru,
							&conf->handle_list);
			पूर्ण अन्यथा अणु
				raid5_wakeup_stripe_thपढ़ो(sh);
				वापस;
			पूर्ण
		पूर्ण
		md_wakeup_thपढ़ो(conf->mddev->thपढ़ो);
	पूर्ण अन्यथा अणु
		BUG_ON(stripe_operations_active(sh));
		अगर (test_and_clear_bit(STRIPE_PREREAD_ACTIVE, &sh->state))
			अगर (atomic_dec_वापस(&conf->preपढ़ो_active_stripes)
			    < IO_THRESHOLD)
				md_wakeup_thपढ़ो(conf->mddev->thपढ़ो);
		atomic_dec(&conf->active_stripes);
		अगर (!test_bit(STRIPE_EXPANDING, &sh->state)) अणु
			अगर (!r5c_is_ग_लिखोback(conf->log))
				list_add_tail(&sh->lru, temp_inactive_list);
			अन्यथा अणु
				WARN_ON(test_bit(R5_InJournal, &sh->dev[sh->pd_idx].flags));
				अगर (injournal == 0)
					list_add_tail(&sh->lru, temp_inactive_list);
				अन्यथा अगर (injournal == conf->raid_disks - conf->max_degraded) अणु
					/* full stripe */
					अगर (!test_and_set_bit(STRIPE_R5C_FULL_STRIPE, &sh->state))
						atomic_inc(&conf->r5c_cached_full_stripes);
					अगर (test_and_clear_bit(STRIPE_R5C_PARTIAL_STRIPE, &sh->state))
						atomic_dec(&conf->r5c_cached_partial_stripes);
					list_add_tail(&sh->lru, &conf->r5c_full_stripe_list);
					r5c_check_cached_full_stripe(conf);
				पूर्ण अन्यथा
					/*
					 * STRIPE_R5C_PARTIAL_STRIPE is set in
					 * r5c_try_caching_ग_लिखो(). No need to
					 * set it again.
					 */
					list_add_tail(&sh->lru, &conf->r5c_partial_stripe_list);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __release_stripe(काष्ठा r5conf *conf, काष्ठा stripe_head *sh,
			     काष्ठा list_head *temp_inactive_list)
अणु
	अगर (atomic_dec_and_test(&sh->count))
		करो_release_stripe(conf, sh, temp_inactive_list);
पूर्ण

/*
 * @hash could be NR_STRIPE_HASH_LOCKS, then we have a list of inactive_list
 *
 * Be careful: Only one task can add/delete stripes from temp_inactive_list at
 * given समय. Adding stripes only takes device lock, जबतक deleting stripes
 * only takes hash lock.
 */
अटल व्योम release_inactive_stripe_list(काष्ठा r5conf *conf,
					 काष्ठा list_head *temp_inactive_list,
					 पूर्णांक hash)
अणु
	पूर्णांक size;
	bool करो_wakeup = false;
	अचिन्हित दीर्घ flags;

	अगर (hash == NR_STRIPE_HASH_LOCKS) अणु
		size = NR_STRIPE_HASH_LOCKS;
		hash = NR_STRIPE_HASH_LOCKS - 1;
	पूर्ण अन्यथा
		size = 1;
	जबतक (size) अणु
		काष्ठा list_head *list = &temp_inactive_list[size - 1];

		/*
		 * We करोn't hold any lock here yet, raid5_get_active_stripe() might
		 * हटाओ stripes from the list
		 */
		अगर (!list_empty_careful(list)) अणु
			spin_lock_irqsave(conf->hash_locks + hash, flags);
			अगर (list_empty(conf->inactive_list + hash) &&
			    !list_empty(list))
				atomic_dec(&conf->empty_inactive_list_nr);
			list_splice_tail_init(list, conf->inactive_list + hash);
			करो_wakeup = true;
			spin_unlock_irqrestore(conf->hash_locks + hash, flags);
		पूर्ण
		size--;
		hash--;
	पूर्ण

	अगर (करो_wakeup) अणु
		wake_up(&conf->रुको_क्रम_stripe);
		अगर (atomic_पढ़ो(&conf->active_stripes) == 0)
			wake_up(&conf->रुको_क्रम_quiescent);
		अगर (conf->retry_पढ़ो_aligned)
			md_wakeup_thपढ़ो(conf->mddev->thपढ़ो);
	पूर्ण
पूर्ण

/* should hold conf->device_lock alपढ़ोy */
अटल पूर्णांक release_stripe_list(काष्ठा r5conf *conf,
			       काष्ठा list_head *temp_inactive_list)
अणु
	काष्ठा stripe_head *sh, *t;
	पूर्णांक count = 0;
	काष्ठा llist_node *head;

	head = llist_del_all(&conf->released_stripes);
	head = llist_reverse_order(head);
	llist_क्रम_each_entry_safe(sh, t, head, release_list) अणु
		पूर्णांक hash;

		/* sh could be पढ़ोded after STRIPE_ON_RELEASE_LIST is cleard */
		smp_mb();
		clear_bit(STRIPE_ON_RELEASE_LIST, &sh->state);
		/*
		 * Don't worry the bit is set here, because अगर the bit is set
		 * again, the count is always > 1. This is true क्रम
		 * STRIPE_ON_UNPLUG_LIST bit too.
		 */
		hash = sh->hash_lock_index;
		__release_stripe(conf, sh, &temp_inactive_list[hash]);
		count++;
	पूर्ण

	वापस count;
पूर्ण

व्योम raid5_release_stripe(काष्ठा stripe_head *sh)
अणु
	काष्ठा r5conf *conf = sh->raid_conf;
	अचिन्हित दीर्घ flags;
	काष्ठा list_head list;
	पूर्णांक hash;
	bool wakeup;

	/* Aव्योम release_list until the last reference.
	 */
	अगर (atomic_add_unless(&sh->count, -1, 1))
		वापस;

	अगर (unlikely(!conf->mddev->thपढ़ो) ||
		test_and_set_bit(STRIPE_ON_RELEASE_LIST, &sh->state))
		जाओ slow_path;
	wakeup = llist_add(&sh->release_list, &conf->released_stripes);
	अगर (wakeup)
		md_wakeup_thपढ़ो(conf->mddev->thपढ़ो);
	वापस;
slow_path:
	/* we are ok here अगर STRIPE_ON_RELEASE_LIST is set or not */
	अगर (atomic_dec_and_lock_irqsave(&sh->count, &conf->device_lock, flags)) अणु
		INIT_LIST_HEAD(&list);
		hash = sh->hash_lock_index;
		करो_release_stripe(conf, sh, &list);
		spin_unlock_irqrestore(&conf->device_lock, flags);
		release_inactive_stripe_list(conf, &list, hash);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम हटाओ_hash(काष्ठा stripe_head *sh)
अणु
	pr_debug("remove_hash(), stripe %llu\n",
		(अचिन्हित दीर्घ दीर्घ)sh->sector);

	hlist_del_init(&sh->hash);
पूर्ण

अटल अंतरभूत व्योम insert_hash(काष्ठा r5conf *conf, काष्ठा stripe_head *sh)
अणु
	काष्ठा hlist_head *hp = stripe_hash(conf, sh->sector);

	pr_debug("insert_hash(), stripe %llu\n",
		(अचिन्हित दीर्घ दीर्घ)sh->sector);

	hlist_add_head(&sh->hash, hp);
पूर्ण

/* find an idle stripe, make sure it is unhashed, and वापस it. */
अटल काष्ठा stripe_head *get_मुक्त_stripe(काष्ठा r5conf *conf, पूर्णांक hash)
अणु
	काष्ठा stripe_head *sh = शून्य;
	काष्ठा list_head *first;

	अगर (list_empty(conf->inactive_list + hash))
		जाओ out;
	first = (conf->inactive_list + hash)->next;
	sh = list_entry(first, काष्ठा stripe_head, lru);
	list_del_init(first);
	हटाओ_hash(sh);
	atomic_inc(&conf->active_stripes);
	BUG_ON(hash != sh->hash_lock_index);
	अगर (list_empty(conf->inactive_list + hash))
		atomic_inc(&conf->empty_inactive_list_nr);
out:
	वापस sh;
पूर्ण

#अगर PAGE_SIZE != DEFAULT_STRIPE_SIZE
अटल व्योम मुक्त_stripe_pages(काष्ठा stripe_head *sh)
अणु
	पूर्णांक i;
	काष्ठा page *p;

	/* Have not allocate page pool */
	अगर (!sh->pages)
		वापस;

	क्रम (i = 0; i < sh->nr_pages; i++) अणु
		p = sh->pages[i];
		अगर (p)
			put_page(p);
		sh->pages[i] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक alloc_stripe_pages(काष्ठा stripe_head *sh, gfp_t gfp)
अणु
	पूर्णांक i;
	काष्ठा page *p;

	क्रम (i = 0; i < sh->nr_pages; i++) अणु
		/* The page have allocated. */
		अगर (sh->pages[i])
			जारी;

		p = alloc_page(gfp);
		अगर (!p) अणु
			मुक्त_stripe_pages(sh);
			वापस -ENOMEM;
		पूर्ण
		sh->pages[i] = p;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
init_stripe_shared_pages(काष्ठा stripe_head *sh, काष्ठा r5conf *conf, पूर्णांक disks)
अणु
	पूर्णांक nr_pages, cnt;

	अगर (sh->pages)
		वापस 0;

	/* Each of the sh->dev[i] need one conf->stripe_size */
	cnt = PAGE_SIZE / conf->stripe_size;
	nr_pages = (disks + cnt - 1) / cnt;

	sh->pages = kसुस्मृति(nr_pages, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!sh->pages)
		वापस -ENOMEM;
	sh->nr_pages = nr_pages;
	sh->stripes_per_page = cnt;
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम shrink_buffers(काष्ठा stripe_head *sh)
अणु
	पूर्णांक i;
	पूर्णांक num = sh->raid_conf->pool_size;

#अगर PAGE_SIZE == DEFAULT_STRIPE_SIZE
	क्रम (i = 0; i < num ; i++) अणु
		काष्ठा page *p;

		WARN_ON(sh->dev[i].page != sh->dev[i].orig_page);
		p = sh->dev[i].page;
		अगर (!p)
			जारी;
		sh->dev[i].page = शून्य;
		put_page(p);
	पूर्ण
#अन्यथा
	क्रम (i = 0; i < num; i++)
		sh->dev[i].page = शून्य;
	मुक्त_stripe_pages(sh); /* Free pages */
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक grow_buffers(काष्ठा stripe_head *sh, gfp_t gfp)
अणु
	पूर्णांक i;
	पूर्णांक num = sh->raid_conf->pool_size;

#अगर PAGE_SIZE == DEFAULT_STRIPE_SIZE
	क्रम (i = 0; i < num; i++) अणु
		काष्ठा page *page;

		अगर (!(page = alloc_page(gfp))) अणु
			वापस 1;
		पूर्ण
		sh->dev[i].page = page;
		sh->dev[i].orig_page = page;
		sh->dev[i].offset = 0;
	पूर्ण
#अन्यथा
	अगर (alloc_stripe_pages(sh, gfp))
		वापस -ENOMEM;

	क्रम (i = 0; i < num; i++) अणु
		sh->dev[i].page = raid5_get_dev_page(sh, i);
		sh->dev[i].orig_page = sh->dev[i].page;
		sh->dev[i].offset = raid5_get_page_offset(sh, i);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम stripe_set_idx(sector_t stripe, काष्ठा r5conf *conf, पूर्णांक previous,
			    काष्ठा stripe_head *sh);

अटल व्योम init_stripe(काष्ठा stripe_head *sh, sector_t sector, पूर्णांक previous)
अणु
	काष्ठा r5conf *conf = sh->raid_conf;
	पूर्णांक i, seq;

	BUG_ON(atomic_पढ़ो(&sh->count) != 0);
	BUG_ON(test_bit(STRIPE_HANDLE, &sh->state));
	BUG_ON(stripe_operations_active(sh));
	BUG_ON(sh->batch_head);

	pr_debug("init_stripe called, stripe %llu\n",
		(अचिन्हित दीर्घ दीर्घ)sector);
retry:
	seq = पढ़ो_seqcount_begin(&conf->gen_lock);
	sh->generation = conf->generation - previous;
	sh->disks = previous ? conf->previous_raid_disks : conf->raid_disks;
	sh->sector = sector;
	stripe_set_idx(sector, conf, previous, sh);
	sh->state = 0;

	क्रम (i = sh->disks; i--; ) अणु
		काष्ठा r5dev *dev = &sh->dev[i];

		अगर (dev->toपढ़ो || dev->पढ़ो || dev->toग_लिखो || dev->written ||
		    test_bit(R5_LOCKED, &dev->flags)) अणु
			pr_err("sector=%llx i=%d %p %p %p %p %d\n",
			       (अचिन्हित दीर्घ दीर्घ)sh->sector, i, dev->toपढ़ो,
			       dev->पढ़ो, dev->toग_लिखो, dev->written,
			       test_bit(R5_LOCKED, &dev->flags));
			WARN_ON(1);
		पूर्ण
		dev->flags = 0;
		dev->sector = raid5_compute_blocknr(sh, i, previous);
	पूर्ण
	अगर (पढ़ो_seqcount_retry(&conf->gen_lock, seq))
		जाओ retry;
	sh->overग_लिखो_disks = 0;
	insert_hash(conf, sh);
	sh->cpu = smp_processor_id();
	set_bit(STRIPE_BATCH_READY, &sh->state);
पूर्ण

अटल काष्ठा stripe_head *__find_stripe(काष्ठा r5conf *conf, sector_t sector,
					 लघु generation)
अणु
	काष्ठा stripe_head *sh;

	pr_debug("__find_stripe, sector %llu\n", (अचिन्हित दीर्घ दीर्घ)sector);
	hlist_क्रम_each_entry(sh, stripe_hash(conf, sector), hash)
		अगर (sh->sector == sector && sh->generation == generation)
			वापस sh;
	pr_debug("__stripe %llu not in cache\n", (अचिन्हित दीर्घ दीर्घ)sector);
	वापस शून्य;
पूर्ण

/*
 * Need to check अगर array has failed when deciding whether to:
 *  - start an array
 *  - हटाओ non-faulty devices
 *  - add a spare
 *  - allow a reshape
 * This determination is simple when no reshape is happening.
 * However अगर there is a reshape, we need to carefully check
 * both the beक्रमe and after sections.
 * This is because some failed devices may only affect one
 * of the two sections, and some non-in_sync devices may
 * be insync in the section most affected by failed devices.
 */
पूर्णांक raid5_calc_degraded(काष्ठा r5conf *conf)
अणु
	पूर्णांक degraded, degraded2;
	पूर्णांक i;

	rcu_पढ़ो_lock();
	degraded = 0;
	क्रम (i = 0; i < conf->previous_raid_disks; i++) अणु
		काष्ठा md_rdev *rdev = rcu_dereference(conf->disks[i].rdev);
		अगर (rdev && test_bit(Faulty, &rdev->flags))
			rdev = rcu_dereference(conf->disks[i].replacement);
		अगर (!rdev || test_bit(Faulty, &rdev->flags))
			degraded++;
		अन्यथा अगर (test_bit(In_sync, &rdev->flags))
			;
		अन्यथा
			/* not in-sync or faulty.
			 * If the reshape increases the number of devices,
			 * this is being recovered by the reshape, so
			 * this 'previous' section is not in_sync.
			 * If the number of devices is being reduced however,
			 * the device can only be part of the array अगर
			 * we are reverting a reshape, so this section will
			 * be in-sync.
			 */
			अगर (conf->raid_disks >= conf->previous_raid_disks)
				degraded++;
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (conf->raid_disks == conf->previous_raid_disks)
		वापस degraded;
	rcu_पढ़ो_lock();
	degraded2 = 0;
	क्रम (i = 0; i < conf->raid_disks; i++) अणु
		काष्ठा md_rdev *rdev = rcu_dereference(conf->disks[i].rdev);
		अगर (rdev && test_bit(Faulty, &rdev->flags))
			rdev = rcu_dereference(conf->disks[i].replacement);
		अगर (!rdev || test_bit(Faulty, &rdev->flags))
			degraded2++;
		अन्यथा अगर (test_bit(In_sync, &rdev->flags))
			;
		अन्यथा
			/* not in-sync or faulty.
			 * If reshape increases the number of devices, this
			 * section has alपढ़ोy been recovered, अन्यथा it
			 * almost certainly hasn't.
			 */
			अगर (conf->raid_disks <= conf->previous_raid_disks)
				degraded2++;
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (degraded2 > degraded)
		वापस degraded2;
	वापस degraded;
पूर्ण

अटल पूर्णांक has_failed(काष्ठा r5conf *conf)
अणु
	पूर्णांक degraded;

	अगर (conf->mddev->reshape_position == MaxSector)
		वापस conf->mddev->degraded > conf->max_degraded;

	degraded = raid5_calc_degraded(conf);
	अगर (degraded > conf->max_degraded)
		वापस 1;
	वापस 0;
पूर्ण

काष्ठा stripe_head *
raid5_get_active_stripe(काष्ठा r5conf *conf, sector_t sector,
			पूर्णांक previous, पूर्णांक noblock, पूर्णांक noquiesce)
अणु
	काष्ठा stripe_head *sh;
	पूर्णांक hash = stripe_hash_locks_hash(conf, sector);
	पूर्णांक inc_empty_inactive_list_flag;

	pr_debug("get_stripe, sector %llu\n", (अचिन्हित दीर्घ दीर्घ)sector);

	spin_lock_irq(conf->hash_locks + hash);

	करो अणु
		रुको_event_lock_irq(conf->रुको_क्रम_quiescent,
				    conf->quiesce == 0 || noquiesce,
				    *(conf->hash_locks + hash));
		sh = __find_stripe(conf, sector, conf->generation - previous);
		अगर (!sh) अणु
			अगर (!test_bit(R5_INACTIVE_BLOCKED, &conf->cache_state)) अणु
				sh = get_मुक्त_stripe(conf, hash);
				अगर (!sh && !test_bit(R5_DID_ALLOC,
						     &conf->cache_state))
					set_bit(R5_ALLOC_MORE,
						&conf->cache_state);
			पूर्ण
			अगर (noblock && sh == शून्य)
				अवरोध;

			r5c_check_stripe_cache_usage(conf);
			अगर (!sh) अणु
				set_bit(R5_INACTIVE_BLOCKED,
					&conf->cache_state);
				r5l_wake_reclaim(conf->log, 0);
				रुको_event_lock_irq(
					conf->रुको_क्रम_stripe,
					!list_empty(conf->inactive_list + hash) &&
					(atomic_पढ़ो(&conf->active_stripes)
					 < (conf->max_nr_stripes * 3 / 4)
					 || !test_bit(R5_INACTIVE_BLOCKED,
						      &conf->cache_state)),
					*(conf->hash_locks + hash));
				clear_bit(R5_INACTIVE_BLOCKED,
					  &conf->cache_state);
			पूर्ण अन्यथा अणु
				init_stripe(sh, sector, previous);
				atomic_inc(&sh->count);
			पूर्ण
		पूर्ण अन्यथा अगर (!atomic_inc_not_zero(&sh->count)) अणु
			spin_lock(&conf->device_lock);
			अगर (!atomic_पढ़ो(&sh->count)) अणु
				अगर (!test_bit(STRIPE_HANDLE, &sh->state))
					atomic_inc(&conf->active_stripes);
				BUG_ON(list_empty(&sh->lru) &&
				       !test_bit(STRIPE_EXPANDING, &sh->state));
				inc_empty_inactive_list_flag = 0;
				अगर (!list_empty(conf->inactive_list + hash))
					inc_empty_inactive_list_flag = 1;
				list_del_init(&sh->lru);
				अगर (list_empty(conf->inactive_list + hash) && inc_empty_inactive_list_flag)
					atomic_inc(&conf->empty_inactive_list_nr);
				अगर (sh->group) अणु
					sh->group->stripes_cnt--;
					sh->group = शून्य;
				पूर्ण
			पूर्ण
			atomic_inc(&sh->count);
			spin_unlock(&conf->device_lock);
		पूर्ण
	पूर्ण जबतक (sh == शून्य);

	spin_unlock_irq(conf->hash_locks + hash);
	वापस sh;
पूर्ण

अटल bool is_full_stripe_ग_लिखो(काष्ठा stripe_head *sh)
अणु
	BUG_ON(sh->overग_लिखो_disks > (sh->disks - sh->raid_conf->max_degraded));
	वापस sh->overग_लिखो_disks == (sh->disks - sh->raid_conf->max_degraded);
पूर्ण

अटल व्योम lock_two_stripes(काष्ठा stripe_head *sh1, काष्ठा stripe_head *sh2)
		__acquires(&sh1->stripe_lock)
		__acquires(&sh2->stripe_lock)
अणु
	अगर (sh1 > sh2) अणु
		spin_lock_irq(&sh2->stripe_lock);
		spin_lock_nested(&sh1->stripe_lock, 1);
	पूर्ण अन्यथा अणु
		spin_lock_irq(&sh1->stripe_lock);
		spin_lock_nested(&sh2->stripe_lock, 1);
	पूर्ण
पूर्ण

अटल व्योम unlock_two_stripes(काष्ठा stripe_head *sh1, काष्ठा stripe_head *sh2)
		__releases(&sh1->stripe_lock)
		__releases(&sh2->stripe_lock)
अणु
	spin_unlock(&sh1->stripe_lock);
	spin_unlock_irq(&sh2->stripe_lock);
पूर्ण

/* Only freshly new full stripe normal ग_लिखो stripe can be added to a batch list */
अटल bool stripe_can_batch(काष्ठा stripe_head *sh)
अणु
	काष्ठा r5conf *conf = sh->raid_conf;

	अगर (raid5_has_log(conf) || raid5_has_ppl(conf))
		वापस false;
	वापस test_bit(STRIPE_BATCH_READY, &sh->state) &&
		!test_bit(STRIPE_BITMAP_PENDING, &sh->state) &&
		is_full_stripe_ग_लिखो(sh);
पूर्ण

/* we only करो back search */
अटल व्योम stripe_add_to_batch_list(काष्ठा r5conf *conf, काष्ठा stripe_head *sh)
अणु
	काष्ठा stripe_head *head;
	sector_t head_sector, पंचांगp_sec;
	पूर्णांक hash;
	पूर्णांक dd_idx;
	पूर्णांक inc_empty_inactive_list_flag;

	/* Don't cross chunks, so stripe pd_idx/qd_idx is the same */
	पंचांगp_sec = sh->sector;
	अगर (!sector_भाग(पंचांगp_sec, conf->chunk_sectors))
		वापस;
	head_sector = sh->sector - RAID5_STRIPE_SECTORS(conf);

	hash = stripe_hash_locks_hash(conf, head_sector);
	spin_lock_irq(conf->hash_locks + hash);
	head = __find_stripe(conf, head_sector, conf->generation);
	अगर (head && !atomic_inc_not_zero(&head->count)) अणु
		spin_lock(&conf->device_lock);
		अगर (!atomic_पढ़ो(&head->count)) अणु
			अगर (!test_bit(STRIPE_HANDLE, &head->state))
				atomic_inc(&conf->active_stripes);
			BUG_ON(list_empty(&head->lru) &&
			       !test_bit(STRIPE_EXPANDING, &head->state));
			inc_empty_inactive_list_flag = 0;
			अगर (!list_empty(conf->inactive_list + hash))
				inc_empty_inactive_list_flag = 1;
			list_del_init(&head->lru);
			अगर (list_empty(conf->inactive_list + hash) && inc_empty_inactive_list_flag)
				atomic_inc(&conf->empty_inactive_list_nr);
			अगर (head->group) अणु
				head->group->stripes_cnt--;
				head->group = शून्य;
			पूर्ण
		पूर्ण
		atomic_inc(&head->count);
		spin_unlock(&conf->device_lock);
	पूर्ण
	spin_unlock_irq(conf->hash_locks + hash);

	अगर (!head)
		वापस;
	अगर (!stripe_can_batch(head))
		जाओ out;

	lock_two_stripes(head, sh);
	/* clear_batch_पढ़ोy clear the flag */
	अगर (!stripe_can_batch(head) || !stripe_can_batch(sh))
		जाओ unlock_out;

	अगर (sh->batch_head)
		जाओ unlock_out;

	dd_idx = 0;
	जबतक (dd_idx == sh->pd_idx || dd_idx == sh->qd_idx)
		dd_idx++;
	अगर (head->dev[dd_idx].toग_लिखो->bi_opf != sh->dev[dd_idx].toग_लिखो->bi_opf ||
	    bio_op(head->dev[dd_idx].toग_लिखो) != bio_op(sh->dev[dd_idx].toग_लिखो))
		जाओ unlock_out;

	अगर (head->batch_head) अणु
		spin_lock(&head->batch_head->batch_lock);
		/* This batch list is alपढ़ोy running */
		अगर (!stripe_can_batch(head)) अणु
			spin_unlock(&head->batch_head->batch_lock);
			जाओ unlock_out;
		पूर्ण
		/*
		 * We must assign batch_head of this stripe within the
		 * batch_lock, otherwise clear_batch_पढ़ोy of batch head
		 * stripe could clear BATCH_READY bit of this stripe and
		 * this stripe->batch_head करोesn't get asचिन्हित, which
		 * could confuse clear_batch_पढ़ोy क्रम this stripe
		 */
		sh->batch_head = head->batch_head;

		/*
		 * at this poपूर्णांक, head's BATCH_READY could be cleared, but we
		 * can still add the stripe to batch list
		 */
		list_add(&sh->batch_list, &head->batch_list);
		spin_unlock(&head->batch_head->batch_lock);
	पूर्ण अन्यथा अणु
		head->batch_head = head;
		sh->batch_head = head->batch_head;
		spin_lock(&head->batch_lock);
		list_add_tail(&sh->batch_list, &head->batch_list);
		spin_unlock(&head->batch_lock);
	पूर्ण

	अगर (test_and_clear_bit(STRIPE_PREREAD_ACTIVE, &sh->state))
		अगर (atomic_dec_वापस(&conf->preपढ़ो_active_stripes)
		    < IO_THRESHOLD)
			md_wakeup_thपढ़ो(conf->mddev->thपढ़ो);

	अगर (test_and_clear_bit(STRIPE_BIT_DELAY, &sh->state)) अणु
		पूर्णांक seq = sh->bm_seq;
		अगर (test_bit(STRIPE_BIT_DELAY, &sh->batch_head->state) &&
		    sh->batch_head->bm_seq > seq)
			seq = sh->batch_head->bm_seq;
		set_bit(STRIPE_BIT_DELAY, &sh->batch_head->state);
		sh->batch_head->bm_seq = seq;
	पूर्ण

	atomic_inc(&sh->count);
unlock_out:
	unlock_two_stripes(head, sh);
out:
	raid5_release_stripe(head);
पूर्ण

/* Determine अगर 'data_offset' or 'new_data_offset' should be used
 * in this stripe_head.
 */
अटल पूर्णांक use_new_offset(काष्ठा r5conf *conf, काष्ठा stripe_head *sh)
अणु
	sector_t progress = conf->reshape_progress;
	/* Need a memory barrier to make sure we see the value
	 * of conf->generation, or ->data_offset that was set beक्रमe
	 * reshape_progress was updated.
	 */
	smp_rmb();
	अगर (progress == MaxSector)
		वापस 0;
	अगर (sh->generation == conf->generation - 1)
		वापस 0;
	/* We are in a reshape, and this is a new-generation stripe,
	 * so use new_data_offset.
	 */
	वापस 1;
पूर्ण

अटल व्योम dispatch_bio_list(काष्ठा bio_list *पंचांगp)
अणु
	काष्ठा bio *bio;

	जबतक ((bio = bio_list_pop(पंचांगp)))
		submit_bio_noacct(bio);
पूर्ण

अटल पूर्णांक cmp_stripe(व्योम *priv, स्थिर काष्ठा list_head *a,
		      स्थिर काष्ठा list_head *b)
अणु
	स्थिर काष्ठा r5pending_data *da = list_entry(a,
				काष्ठा r5pending_data, sibling);
	स्थिर काष्ठा r5pending_data *db = list_entry(b,
				काष्ठा r5pending_data, sibling);
	अगर (da->sector > db->sector)
		वापस 1;
	अगर (da->sector < db->sector)
		वापस -1;
	वापस 0;
पूर्ण

अटल व्योम dispatch_defer_bios(काष्ठा r5conf *conf, पूर्णांक target,
				काष्ठा bio_list *list)
अणु
	काष्ठा r5pending_data *data;
	काष्ठा list_head *first, *next = शून्य;
	पूर्णांक cnt = 0;

	अगर (conf->pending_data_cnt == 0)
		वापस;

	list_sort(शून्य, &conf->pending_list, cmp_stripe);

	first = conf->pending_list.next;

	/* temporarily move the head */
	अगर (conf->next_pending_data)
		list_move_tail(&conf->pending_list,
				&conf->next_pending_data->sibling);

	जबतक (!list_empty(&conf->pending_list)) अणु
		data = list_first_entry(&conf->pending_list,
			काष्ठा r5pending_data, sibling);
		अगर (&data->sibling == first)
			first = data->sibling.next;
		next = data->sibling.next;

		bio_list_merge(list, &data->bios);
		list_move(&data->sibling, &conf->मुक्त_list);
		cnt++;
		अगर (cnt >= target)
			अवरोध;
	पूर्ण
	conf->pending_data_cnt -= cnt;
	BUG_ON(conf->pending_data_cnt < 0 || cnt < target);

	अगर (next != &conf->pending_list)
		conf->next_pending_data = list_entry(next,
				काष्ठा r5pending_data, sibling);
	अन्यथा
		conf->next_pending_data = शून्य;
	/* list isn't empty */
	अगर (first != &conf->pending_list)
		list_move_tail(&conf->pending_list, first);
पूर्ण

अटल व्योम flush_deferred_bios(काष्ठा r5conf *conf)
अणु
	काष्ठा bio_list पंचांगp = BIO_EMPTY_LIST;

	अगर (conf->pending_data_cnt == 0)
		वापस;

	spin_lock(&conf->pending_bios_lock);
	dispatch_defer_bios(conf, conf->pending_data_cnt, &पंचांगp);
	BUG_ON(conf->pending_data_cnt != 0);
	spin_unlock(&conf->pending_bios_lock);

	dispatch_bio_list(&पंचांगp);
पूर्ण

अटल व्योम defer_issue_bios(काष्ठा r5conf *conf, sector_t sector,
				काष्ठा bio_list *bios)
अणु
	काष्ठा bio_list पंचांगp = BIO_EMPTY_LIST;
	काष्ठा r5pending_data *ent;

	spin_lock(&conf->pending_bios_lock);
	ent = list_first_entry(&conf->मुक्त_list, काष्ठा r5pending_data,
							sibling);
	list_move_tail(&ent->sibling, &conf->pending_list);
	ent->sector = sector;
	bio_list_init(&ent->bios);
	bio_list_merge(&ent->bios, bios);
	conf->pending_data_cnt++;
	अगर (conf->pending_data_cnt >= PENDING_IO_MAX)
		dispatch_defer_bios(conf, PENDING_IO_ONE_FLUSH, &पंचांगp);

	spin_unlock(&conf->pending_bios_lock);

	dispatch_bio_list(&पंचांगp);
पूर्ण

अटल व्योम
raid5_end_पढ़ो_request(काष्ठा bio *bi);
अटल व्योम
raid5_end_ग_लिखो_request(काष्ठा bio *bi);

अटल व्योम ops_run_io(काष्ठा stripe_head *sh, काष्ठा stripe_head_state *s)
अणु
	काष्ठा r5conf *conf = sh->raid_conf;
	पूर्णांक i, disks = sh->disks;
	काष्ठा stripe_head *head_sh = sh;
	काष्ठा bio_list pending_bios = BIO_EMPTY_LIST;
	bool should_defer;

	might_sleep();

	अगर (log_stripe(sh, s) == 0)
		वापस;

	should_defer = conf->batch_bio_dispatch && conf->group_cnt;

	क्रम (i = disks; i--; ) अणु
		पूर्णांक op, op_flags = 0;
		पूर्णांक replace_only = 0;
		काष्ठा bio *bi, *rbi;
		काष्ठा md_rdev *rdev, *rrdev = शून्य;

		sh = head_sh;
		अगर (test_and_clear_bit(R5_Wantग_लिखो, &sh->dev[i].flags)) अणु
			op = REQ_OP_WRITE;
			अगर (test_and_clear_bit(R5_WantFUA, &sh->dev[i].flags))
				op_flags = REQ_FUA;
			अगर (test_bit(R5_Discard, &sh->dev[i].flags))
				op = REQ_OP_DISCARD;
		पूर्ण अन्यथा अगर (test_and_clear_bit(R5_Wantपढ़ो, &sh->dev[i].flags))
			op = REQ_OP_READ;
		अन्यथा अगर (test_and_clear_bit(R5_WantReplace,
					    &sh->dev[i].flags)) अणु
			op = REQ_OP_WRITE;
			replace_only = 1;
		पूर्ण अन्यथा
			जारी;
		अगर (test_and_clear_bit(R5_SyncIO, &sh->dev[i].flags))
			op_flags |= REQ_SYNC;

again:
		bi = &sh->dev[i].req;
		rbi = &sh->dev[i].rreq; /* For writing to replacement */

		rcu_पढ़ो_lock();
		rrdev = rcu_dereference(conf->disks[i].replacement);
		smp_mb(); /* Ensure that अगर rrdev is शून्य, rdev won't be */
		rdev = rcu_dereference(conf->disks[i].rdev);
		अगर (!rdev) अणु
			rdev = rrdev;
			rrdev = शून्य;
		पूर्ण
		अगर (op_is_ग_लिखो(op)) अणु
			अगर (replace_only)
				rdev = शून्य;
			अगर (rdev == rrdev)
				/* We raced and saw duplicates */
				rrdev = शून्य;
		पूर्ण अन्यथा अणु
			अगर (test_bit(R5_ReadRepl, &head_sh->dev[i].flags) && rrdev)
				rdev = rrdev;
			rrdev = शून्य;
		पूर्ण

		अगर (rdev && test_bit(Faulty, &rdev->flags))
			rdev = शून्य;
		अगर (rdev)
			atomic_inc(&rdev->nr_pending);
		अगर (rrdev && test_bit(Faulty, &rrdev->flags))
			rrdev = शून्य;
		अगर (rrdev)
			atomic_inc(&rrdev->nr_pending);
		rcu_पढ़ो_unlock();

		/* We have alपढ़ोy checked bad blocks क्रम पढ़ोs.  Now
		 * need to check क्रम ग_लिखोs.  We never accept ग_लिखो errors
		 * on the replacement, so we करोn't to check rrdev.
		 */
		जबतक (op_is_ग_लिखो(op) && rdev &&
		       test_bit(WriteErrorSeen, &rdev->flags)) अणु
			sector_t first_bad;
			पूर्णांक bad_sectors;
			पूर्णांक bad = is_badblock(rdev, sh->sector, RAID5_STRIPE_SECTORS(conf),
					      &first_bad, &bad_sectors);
			अगर (!bad)
				अवरोध;

			अगर (bad < 0) अणु
				set_bit(BlockedBadBlocks, &rdev->flags);
				अगर (!conf->mddev->बाह्यal &&
				    conf->mddev->sb_flags) अणु
					/* It is very unlikely, but we might
					 * still need to ग_लिखो out the
					 * bad block log - better give it
					 * a chance*/
					md_check_recovery(conf->mddev);
				पूर्ण
				/*
				 * Because md_रुको_क्रम_blocked_rdev
				 * will dec nr_pending, we must
				 * increment it first.
				 */
				atomic_inc(&rdev->nr_pending);
				md_रुको_क्रम_blocked_rdev(rdev, conf->mddev);
			पूर्ण अन्यथा अणु
				/* Acknowledged bad block - skip the ग_लिखो */
				rdev_dec_pending(rdev, conf->mddev);
				rdev = शून्य;
			पूर्ण
		पूर्ण

		अगर (rdev) अणु
			अगर (s->syncing || s->expanding || s->expanded
			    || s->replacing)
				md_sync_acct(rdev->bdev, RAID5_STRIPE_SECTORS(conf));

			set_bit(STRIPE_IO_STARTED, &sh->state);

			bio_set_dev(bi, rdev->bdev);
			bio_set_op_attrs(bi, op, op_flags);
			bi->bi_end_io = op_is_ग_लिखो(op)
				? raid5_end_ग_लिखो_request
				: raid5_end_पढ़ो_request;
			bi->bi_निजी = sh;

			pr_debug("%s: for %llu schedule op %d on disc %d\n",
				__func__, (अचिन्हित दीर्घ दीर्घ)sh->sector,
				bi->bi_opf, i);
			atomic_inc(&sh->count);
			अगर (sh != head_sh)
				atomic_inc(&head_sh->count);
			अगर (use_new_offset(conf, sh))
				bi->bi_iter.bi_sector = (sh->sector
						 + rdev->new_data_offset);
			अन्यथा
				bi->bi_iter.bi_sector = (sh->sector
						 + rdev->data_offset);
			अगर (test_bit(R5_ReadNoMerge, &head_sh->dev[i].flags))
				bi->bi_opf |= REQ_NOMERGE;

			अगर (test_bit(R5_SkipCopy, &sh->dev[i].flags))
				WARN_ON(test_bit(R5_UPTODATE, &sh->dev[i].flags));

			अगर (!op_is_ग_लिखो(op) &&
			    test_bit(R5_InJournal, &sh->dev[i].flags))
				/*
				 * issuing पढ़ो क्रम a page in journal, this
				 * must be preparing क्रम prexor in rmw; पढ़ो
				 * the data पूर्णांकo orig_page
				 */
				sh->dev[i].vec.bv_page = sh->dev[i].orig_page;
			अन्यथा
				sh->dev[i].vec.bv_page = sh->dev[i].page;
			bi->bi_vcnt = 1;
			bi->bi_io_vec[0].bv_len = RAID5_STRIPE_SIZE(conf);
			bi->bi_io_vec[0].bv_offset = sh->dev[i].offset;
			bi->bi_iter.bi_size = RAID5_STRIPE_SIZE(conf);
			bi->bi_ग_लिखो_hपूर्णांक = sh->dev[i].ग_लिखो_hपूर्णांक;
			अगर (!rrdev)
				sh->dev[i].ग_लिखो_hपूर्णांक = RWH_WRITE_LIFE_NOT_SET;
			/*
			 * If this is discard request, set bi_vcnt 0. We करोn't
			 * want to confuse SCSI because SCSI will replace payload
			 */
			अगर (op == REQ_OP_DISCARD)
				bi->bi_vcnt = 0;
			अगर (rrdev)
				set_bit(R5_DOUBLE_LOCKED, &sh->dev[i].flags);

			अगर (conf->mddev->gendisk)
				trace_block_bio_remap(bi,
						disk_devt(conf->mddev->gendisk),
						sh->dev[i].sector);
			अगर (should_defer && op_is_ग_लिखो(op))
				bio_list_add(&pending_bios, bi);
			अन्यथा
				submit_bio_noacct(bi);
		पूर्ण
		अगर (rrdev) अणु
			अगर (s->syncing || s->expanding || s->expanded
			    || s->replacing)
				md_sync_acct(rrdev->bdev, RAID5_STRIPE_SECTORS(conf));

			set_bit(STRIPE_IO_STARTED, &sh->state);

			bio_set_dev(rbi, rrdev->bdev);
			bio_set_op_attrs(rbi, op, op_flags);
			BUG_ON(!op_is_ग_लिखो(op));
			rbi->bi_end_io = raid5_end_ग_लिखो_request;
			rbi->bi_निजी = sh;

			pr_debug("%s: for %llu schedule op %d on "
				 "replacement disc %d\n",
				__func__, (अचिन्हित दीर्घ दीर्घ)sh->sector,
				rbi->bi_opf, i);
			atomic_inc(&sh->count);
			अगर (sh != head_sh)
				atomic_inc(&head_sh->count);
			अगर (use_new_offset(conf, sh))
				rbi->bi_iter.bi_sector = (sh->sector
						  + rrdev->new_data_offset);
			अन्यथा
				rbi->bi_iter.bi_sector = (sh->sector
						  + rrdev->data_offset);
			अगर (test_bit(R5_SkipCopy, &sh->dev[i].flags))
				WARN_ON(test_bit(R5_UPTODATE, &sh->dev[i].flags));
			sh->dev[i].rvec.bv_page = sh->dev[i].page;
			rbi->bi_vcnt = 1;
			rbi->bi_io_vec[0].bv_len = RAID5_STRIPE_SIZE(conf);
			rbi->bi_io_vec[0].bv_offset = sh->dev[i].offset;
			rbi->bi_iter.bi_size = RAID5_STRIPE_SIZE(conf);
			rbi->bi_ग_लिखो_hपूर्णांक = sh->dev[i].ग_लिखो_hपूर्णांक;
			sh->dev[i].ग_लिखो_hपूर्णांक = RWH_WRITE_LIFE_NOT_SET;
			/*
			 * If this is discard request, set bi_vcnt 0. We करोn't
			 * want to confuse SCSI because SCSI will replace payload
			 */
			अगर (op == REQ_OP_DISCARD)
				rbi->bi_vcnt = 0;
			अगर (conf->mddev->gendisk)
				trace_block_bio_remap(rbi,
						disk_devt(conf->mddev->gendisk),
						sh->dev[i].sector);
			अगर (should_defer && op_is_ग_लिखो(op))
				bio_list_add(&pending_bios, rbi);
			अन्यथा
				submit_bio_noacct(rbi);
		पूर्ण
		अगर (!rdev && !rrdev) अणु
			अगर (op_is_ग_लिखो(op))
				set_bit(STRIPE_DEGRADED, &sh->state);
			pr_debug("skip op %d on disc %d for sector %llu\n",
				bi->bi_opf, i, (अचिन्हित दीर्घ दीर्घ)sh->sector);
			clear_bit(R5_LOCKED, &sh->dev[i].flags);
			set_bit(STRIPE_HANDLE, &sh->state);
		पूर्ण

		अगर (!head_sh->batch_head)
			जारी;
		sh = list_first_entry(&sh->batch_list, काष्ठा stripe_head,
				      batch_list);
		अगर (sh != head_sh)
			जाओ again;
	पूर्ण

	अगर (should_defer && !bio_list_empty(&pending_bios))
		defer_issue_bios(conf, head_sh->sector, &pending_bios);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
async_copy_data(पूर्णांक frombio, काष्ठा bio *bio, काष्ठा page **page,
	अचिन्हित पूर्णांक poff, sector_t sector, काष्ठा dma_async_tx_descriptor *tx,
	काष्ठा stripe_head *sh, पूर्णांक no_skipcopy)
अणु
	काष्ठा bio_vec bvl;
	काष्ठा bvec_iter iter;
	काष्ठा page *bio_page;
	पूर्णांक page_offset;
	काष्ठा async_submit_ctl submit;
	क्रमागत async_tx_flags flags = 0;
	काष्ठा r5conf *conf = sh->raid_conf;

	अगर (bio->bi_iter.bi_sector >= sector)
		page_offset = (चिन्हित)(bio->bi_iter.bi_sector - sector) * 512;
	अन्यथा
		page_offset = (चिन्हित)(sector - bio->bi_iter.bi_sector) * -512;

	अगर (frombio)
		flags |= ASYNC_TX_FENCE;
	init_async_submit(&submit, flags, tx, शून्य, शून्य, शून्य);

	bio_क्रम_each_segment(bvl, bio, iter) अणु
		पूर्णांक len = bvl.bv_len;
		पूर्णांक clen;
		पूर्णांक b_offset = 0;

		अगर (page_offset < 0) अणु
			b_offset = -page_offset;
			page_offset += b_offset;
			len -= b_offset;
		पूर्ण

		अगर (len > 0 && page_offset + len > RAID5_STRIPE_SIZE(conf))
			clen = RAID5_STRIPE_SIZE(conf) - page_offset;
		अन्यथा
			clen = len;

		अगर (clen > 0) अणु
			b_offset += bvl.bv_offset;
			bio_page = bvl.bv_page;
			अगर (frombio) अणु
				अगर (conf->skip_copy &&
				    b_offset == 0 && page_offset == 0 &&
				    clen == RAID5_STRIPE_SIZE(conf) &&
				    !no_skipcopy)
					*page = bio_page;
				अन्यथा
					tx = async_स_नकल(*page, bio_page, page_offset + poff,
						  b_offset, clen, &submit);
			पूर्ण अन्यथा
				tx = async_स_नकल(bio_page, *page, b_offset,
						  page_offset + poff, clen, &submit);
		पूर्ण
		/* chain the operations */
		submit.depend_tx = tx;

		अगर (clen < len) /* hit end of page */
			अवरोध;
		page_offset +=  len;
	पूर्ण

	वापस tx;
पूर्ण

अटल व्योम ops_complete_biofill(व्योम *stripe_head_ref)
अणु
	काष्ठा stripe_head *sh = stripe_head_ref;
	पूर्णांक i;
	काष्ठा r5conf *conf = sh->raid_conf;

	pr_debug("%s: stripe %llu\n", __func__,
		(अचिन्हित दीर्घ दीर्घ)sh->sector);

	/* clear completed biofills */
	क्रम (i = sh->disks; i--; ) अणु
		काष्ठा r5dev *dev = &sh->dev[i];

		/* acknowledge completion of a biofill operation */
		/* and check अगर we need to reply to a पढ़ो request,
		 * new R5_Wantfill requests are held off until
		 * !STRIPE_BIOFILL_RUN
		 */
		अगर (test_and_clear_bit(R5_Wantfill, &dev->flags)) अणु
			काष्ठा bio *rbi, *rbi2;

			BUG_ON(!dev->पढ़ो);
			rbi = dev->पढ़ो;
			dev->पढ़ो = शून्य;
			जबतक (rbi && rbi->bi_iter.bi_sector <
				dev->sector + RAID5_STRIPE_SECTORS(conf)) अणु
				rbi2 = r5_next_bio(conf, rbi, dev->sector);
				bio_endio(rbi);
				rbi = rbi2;
			पूर्ण
		पूर्ण
	पूर्ण
	clear_bit(STRIPE_BIOFILL_RUN, &sh->state);

	set_bit(STRIPE_HANDLE, &sh->state);
	raid5_release_stripe(sh);
पूर्ण

अटल व्योम ops_run_biofill(काष्ठा stripe_head *sh)
अणु
	काष्ठा dma_async_tx_descriptor *tx = शून्य;
	काष्ठा async_submit_ctl submit;
	पूर्णांक i;
	काष्ठा r5conf *conf = sh->raid_conf;

	BUG_ON(sh->batch_head);
	pr_debug("%s: stripe %llu\n", __func__,
		(अचिन्हित दीर्घ दीर्घ)sh->sector);

	क्रम (i = sh->disks; i--; ) अणु
		काष्ठा r5dev *dev = &sh->dev[i];
		अगर (test_bit(R5_Wantfill, &dev->flags)) अणु
			काष्ठा bio *rbi;
			spin_lock_irq(&sh->stripe_lock);
			dev->पढ़ो = rbi = dev->toपढ़ो;
			dev->toपढ़ो = शून्य;
			spin_unlock_irq(&sh->stripe_lock);
			जबतक (rbi && rbi->bi_iter.bi_sector <
				dev->sector + RAID5_STRIPE_SECTORS(conf)) अणु
				tx = async_copy_data(0, rbi, &dev->page,
						     dev->offset,
						     dev->sector, tx, sh, 0);
				rbi = r5_next_bio(conf, rbi, dev->sector);
			पूर्ण
		पूर्ण
	पूर्ण

	atomic_inc(&sh->count);
	init_async_submit(&submit, ASYNC_TX_ACK, tx, ops_complete_biofill, sh, शून्य);
	async_trigger_callback(&submit);
पूर्ण

अटल व्योम mark_target_uptodate(काष्ठा stripe_head *sh, पूर्णांक target)
अणु
	काष्ठा r5dev *tgt;

	अगर (target < 0)
		वापस;

	tgt = &sh->dev[target];
	set_bit(R5_UPTODATE, &tgt->flags);
	BUG_ON(!test_bit(R5_Wantcompute, &tgt->flags));
	clear_bit(R5_Wantcompute, &tgt->flags);
पूर्ण

अटल व्योम ops_complete_compute(व्योम *stripe_head_ref)
अणु
	काष्ठा stripe_head *sh = stripe_head_ref;

	pr_debug("%s: stripe %llu\n", __func__,
		(अचिन्हित दीर्घ दीर्घ)sh->sector);

	/* mark the computed target(s) as uptodate */
	mark_target_uptodate(sh, sh->ops.target);
	mark_target_uptodate(sh, sh->ops.target2);

	clear_bit(STRIPE_COMPUTE_RUN, &sh->state);
	अगर (sh->check_state == check_state_compute_run)
		sh->check_state = check_state_compute_result;
	set_bit(STRIPE_HANDLE, &sh->state);
	raid5_release_stripe(sh);
पूर्ण

/* वापस a poपूर्णांकer to the address conversion region of the scribble buffer */
अटल काष्ठा page **to_addr_page(काष्ठा raid5_percpu *percpu, पूर्णांक i)
अणु
	वापस percpu->scribble + i * percpu->scribble_obj_size;
पूर्ण

/* वापस a poपूर्णांकer to the address conversion region of the scribble buffer */
अटल addr_conv_t *to_addr_conv(काष्ठा stripe_head *sh,
				 काष्ठा raid5_percpu *percpu, पूर्णांक i)
अणु
	वापस (व्योम *) (to_addr_page(percpu, i) + sh->disks + 2);
पूर्ण

/*
 * Return a poपूर्णांकer to record offset address.
 */
अटल अचिन्हित पूर्णांक *
to_addr_offs(काष्ठा stripe_head *sh, काष्ठा raid5_percpu *percpu)
अणु
	वापस (अचिन्हित पूर्णांक *) (to_addr_conv(sh, percpu, 0) + sh->disks + 2);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
ops_run_compute5(काष्ठा stripe_head *sh, काष्ठा raid5_percpu *percpu)
अणु
	पूर्णांक disks = sh->disks;
	काष्ठा page **xor_srcs = to_addr_page(percpu, 0);
	अचिन्हित पूर्णांक *off_srcs = to_addr_offs(sh, percpu);
	पूर्णांक target = sh->ops.target;
	काष्ठा r5dev *tgt = &sh->dev[target];
	काष्ठा page *xor_dest = tgt->page;
	अचिन्हित पूर्णांक off_dest = tgt->offset;
	पूर्णांक count = 0;
	काष्ठा dma_async_tx_descriptor *tx;
	काष्ठा async_submit_ctl submit;
	पूर्णांक i;

	BUG_ON(sh->batch_head);

	pr_debug("%s: stripe %llu block: %d\n",
		__func__, (अचिन्हित दीर्घ दीर्घ)sh->sector, target);
	BUG_ON(!test_bit(R5_Wantcompute, &tgt->flags));

	क्रम (i = disks; i--; ) अणु
		अगर (i != target) अणु
			off_srcs[count] = sh->dev[i].offset;
			xor_srcs[count++] = sh->dev[i].page;
		पूर्ण
	पूर्ण

	atomic_inc(&sh->count);

	init_async_submit(&submit, ASYNC_TX_FENCE|ASYNC_TX_XOR_ZERO_DST, शून्य,
			  ops_complete_compute, sh, to_addr_conv(sh, percpu, 0));
	अगर (unlikely(count == 1))
		tx = async_स_नकल(xor_dest, xor_srcs[0], off_dest, off_srcs[0],
				RAID5_STRIPE_SIZE(sh->raid_conf), &submit);
	अन्यथा
		tx = async_xor_offs(xor_dest, off_dest, xor_srcs, off_srcs, count,
				RAID5_STRIPE_SIZE(sh->raid_conf), &submit);

	वापस tx;
पूर्ण

/* set_syndrome_sources - populate source buffers क्रम gen_syndrome
 * @srcs - (काष्ठा page *) array of size sh->disks
 * @offs - (अचिन्हित पूर्णांक) array of offset क्रम each page
 * @sh - stripe_head to parse
 *
 * Populates srcs in proper layout order क्रम the stripe and वापसs the
 * 'count' of sources to be used in a call to async_gen_syndrome.  The P
 * destination buffer is recorded in srcs[count] and the Q destination
 * is recorded in srcs[count+1]].
 */
अटल पूर्णांक set_syndrome_sources(काष्ठा page **srcs,
				अचिन्हित पूर्णांक *offs,
				काष्ठा stripe_head *sh,
				पूर्णांक srctype)
अणु
	पूर्णांक disks = sh->disks;
	पूर्णांक syndrome_disks = sh->ddf_layout ? disks : (disks - 2);
	पूर्णांक d0_idx = raid6_d0(sh);
	पूर्णांक count;
	पूर्णांक i;

	क्रम (i = 0; i < disks; i++)
		srcs[i] = शून्य;

	count = 0;
	i = d0_idx;
	करो अणु
		पूर्णांक slot = raid6_idx_to_slot(i, sh, &count, syndrome_disks);
		काष्ठा r5dev *dev = &sh->dev[i];

		अगर (i == sh->qd_idx || i == sh->pd_idx ||
		    (srctype == SYNDROME_SRC_ALL) ||
		    (srctype == SYNDROME_SRC_WANT_DRAIN &&
		     (test_bit(R5_Wantdrain, &dev->flags) ||
		      test_bit(R5_InJournal, &dev->flags))) ||
		    (srctype == SYNDROME_SRC_WRITTEN &&
		     (dev->written ||
		      test_bit(R5_InJournal, &dev->flags)))) अणु
			अगर (test_bit(R5_InJournal, &dev->flags))
				srcs[slot] = sh->dev[i].orig_page;
			अन्यथा
				srcs[slot] = sh->dev[i].page;
			/*
			 * For R5_InJournal, PAGE_SIZE must be 4KB and will
			 * not shared page. In that हाल, dev[i].offset
			 * is 0.
			 */
			offs[slot] = sh->dev[i].offset;
		पूर्ण
		i = raid6_next_disk(i, disks);
	पूर्ण जबतक (i != d0_idx);

	वापस syndrome_disks;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
ops_run_compute6_1(काष्ठा stripe_head *sh, काष्ठा raid5_percpu *percpu)
अणु
	पूर्णांक disks = sh->disks;
	काष्ठा page **blocks = to_addr_page(percpu, 0);
	अचिन्हित पूर्णांक *offs = to_addr_offs(sh, percpu);
	पूर्णांक target;
	पूर्णांक qd_idx = sh->qd_idx;
	काष्ठा dma_async_tx_descriptor *tx;
	काष्ठा async_submit_ctl submit;
	काष्ठा r5dev *tgt;
	काष्ठा page *dest;
	अचिन्हित पूर्णांक dest_off;
	पूर्णांक i;
	पूर्णांक count;

	BUG_ON(sh->batch_head);
	अगर (sh->ops.target < 0)
		target = sh->ops.target2;
	अन्यथा अगर (sh->ops.target2 < 0)
		target = sh->ops.target;
	अन्यथा
		/* we should only have one valid target */
		BUG();
	BUG_ON(target < 0);
	pr_debug("%s: stripe %llu block: %d\n",
		__func__, (अचिन्हित दीर्घ दीर्घ)sh->sector, target);

	tgt = &sh->dev[target];
	BUG_ON(!test_bit(R5_Wantcompute, &tgt->flags));
	dest = tgt->page;
	dest_off = tgt->offset;

	atomic_inc(&sh->count);

	अगर (target == qd_idx) अणु
		count = set_syndrome_sources(blocks, offs, sh, SYNDROME_SRC_ALL);
		blocks[count] = शून्य; /* regenerating p is not necessary */
		BUG_ON(blocks[count+1] != dest); /* q should alपढ़ोy be set */
		init_async_submit(&submit, ASYNC_TX_FENCE, शून्य,
				  ops_complete_compute, sh,
				  to_addr_conv(sh, percpu, 0));
		tx = async_gen_syndrome(blocks, offs, count+2,
				RAID5_STRIPE_SIZE(sh->raid_conf), &submit);
	पूर्ण अन्यथा अणु
		/* Compute any data- or p-drive using XOR */
		count = 0;
		क्रम (i = disks; i-- ; ) अणु
			अगर (i == target || i == qd_idx)
				जारी;
			offs[count] = sh->dev[i].offset;
			blocks[count++] = sh->dev[i].page;
		पूर्ण

		init_async_submit(&submit, ASYNC_TX_FENCE|ASYNC_TX_XOR_ZERO_DST,
				  शून्य, ops_complete_compute, sh,
				  to_addr_conv(sh, percpu, 0));
		tx = async_xor_offs(dest, dest_off, blocks, offs, count,
				RAID5_STRIPE_SIZE(sh->raid_conf), &submit);
	पूर्ण

	वापस tx;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
ops_run_compute6_2(काष्ठा stripe_head *sh, काष्ठा raid5_percpu *percpu)
अणु
	पूर्णांक i, count, disks = sh->disks;
	पूर्णांक syndrome_disks = sh->ddf_layout ? disks : disks-2;
	पूर्णांक d0_idx = raid6_d0(sh);
	पूर्णांक faila = -1, failb = -1;
	पूर्णांक target = sh->ops.target;
	पूर्णांक target2 = sh->ops.target2;
	काष्ठा r5dev *tgt = &sh->dev[target];
	काष्ठा r5dev *tgt2 = &sh->dev[target2];
	काष्ठा dma_async_tx_descriptor *tx;
	काष्ठा page **blocks = to_addr_page(percpu, 0);
	अचिन्हित पूर्णांक *offs = to_addr_offs(sh, percpu);
	काष्ठा async_submit_ctl submit;

	BUG_ON(sh->batch_head);
	pr_debug("%s: stripe %llu block1: %d block2: %d\n",
		 __func__, (अचिन्हित दीर्घ दीर्घ)sh->sector, target, target2);
	BUG_ON(target < 0 || target2 < 0);
	BUG_ON(!test_bit(R5_Wantcompute, &tgt->flags));
	BUG_ON(!test_bit(R5_Wantcompute, &tgt2->flags));

	/* we need to खोलो-code set_syndrome_sources to handle the
	 * slot number conversion क्रम 'faila' and 'failb'
	 */
	क्रम (i = 0; i < disks ; i++) अणु
		offs[i] = 0;
		blocks[i] = शून्य;
	पूर्ण
	count = 0;
	i = d0_idx;
	करो अणु
		पूर्णांक slot = raid6_idx_to_slot(i, sh, &count, syndrome_disks);

		offs[slot] = sh->dev[i].offset;
		blocks[slot] = sh->dev[i].page;

		अगर (i == target)
			faila = slot;
		अगर (i == target2)
			failb = slot;
		i = raid6_next_disk(i, disks);
	पूर्ण जबतक (i != d0_idx);

	BUG_ON(faila == failb);
	अगर (failb < faila)
		swap(faila, failb);
	pr_debug("%s: stripe: %llu faila: %d failb: %d\n",
		 __func__, (अचिन्हित दीर्घ दीर्घ)sh->sector, faila, failb);

	atomic_inc(&sh->count);

	अगर (failb == syndrome_disks+1) अणु
		/* Q disk is one of the missing disks */
		अगर (faila == syndrome_disks) अणु
			/* Missing P+Q, just recompute */
			init_async_submit(&submit, ASYNC_TX_FENCE, शून्य,
					  ops_complete_compute, sh,
					  to_addr_conv(sh, percpu, 0));
			वापस async_gen_syndrome(blocks, offs, syndrome_disks+2,
						  RAID5_STRIPE_SIZE(sh->raid_conf),
						  &submit);
		पूर्ण अन्यथा अणु
			काष्ठा page *dest;
			अचिन्हित पूर्णांक dest_off;
			पूर्णांक data_target;
			पूर्णांक qd_idx = sh->qd_idx;

			/* Missing D+Q: recompute D from P, then recompute Q */
			अगर (target == qd_idx)
				data_target = target2;
			अन्यथा
				data_target = target;

			count = 0;
			क्रम (i = disks; i-- ; ) अणु
				अगर (i == data_target || i == qd_idx)
					जारी;
				offs[count] = sh->dev[i].offset;
				blocks[count++] = sh->dev[i].page;
			पूर्ण
			dest = sh->dev[data_target].page;
			dest_off = sh->dev[data_target].offset;
			init_async_submit(&submit,
					  ASYNC_TX_FENCE|ASYNC_TX_XOR_ZERO_DST,
					  शून्य, शून्य, शून्य,
					  to_addr_conv(sh, percpu, 0));
			tx = async_xor_offs(dest, dest_off, blocks, offs, count,
				       RAID5_STRIPE_SIZE(sh->raid_conf),
				       &submit);

			count = set_syndrome_sources(blocks, offs, sh, SYNDROME_SRC_ALL);
			init_async_submit(&submit, ASYNC_TX_FENCE, tx,
					  ops_complete_compute, sh,
					  to_addr_conv(sh, percpu, 0));
			वापस async_gen_syndrome(blocks, offs, count+2,
						  RAID5_STRIPE_SIZE(sh->raid_conf),
						  &submit);
		पूर्ण
	पूर्ण अन्यथा अणु
		init_async_submit(&submit, ASYNC_TX_FENCE, शून्य,
				  ops_complete_compute, sh,
				  to_addr_conv(sh, percpu, 0));
		अगर (failb == syndrome_disks) अणु
			/* We're missing D+P. */
			वापस async_raid6_datap_recov(syndrome_disks+2,
						RAID5_STRIPE_SIZE(sh->raid_conf),
						faila,
						blocks, offs, &submit);
		पूर्ण अन्यथा अणु
			/* We're missing D+D. */
			वापस async_raid6_2data_recov(syndrome_disks+2,
						RAID5_STRIPE_SIZE(sh->raid_conf),
						faila, failb,
						blocks, offs, &submit);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ops_complete_prexor(व्योम *stripe_head_ref)
अणु
	काष्ठा stripe_head *sh = stripe_head_ref;

	pr_debug("%s: stripe %llu\n", __func__,
		(अचिन्हित दीर्घ दीर्घ)sh->sector);

	अगर (r5c_is_ग_लिखोback(sh->raid_conf->log))
		/*
		 * raid5-cache ग_लिखो back uses orig_page during prexor.
		 * After prexor, it is समय to मुक्त orig_page
		 */
		r5c_release_extra_page(sh);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
ops_run_prexor5(काष्ठा stripe_head *sh, काष्ठा raid5_percpu *percpu,
		काष्ठा dma_async_tx_descriptor *tx)
अणु
	पूर्णांक disks = sh->disks;
	काष्ठा page **xor_srcs = to_addr_page(percpu, 0);
	अचिन्हित पूर्णांक *off_srcs = to_addr_offs(sh, percpu);
	पूर्णांक count = 0, pd_idx = sh->pd_idx, i;
	काष्ठा async_submit_ctl submit;

	/* existing parity data subtracted */
	अचिन्हित पूर्णांक off_dest = off_srcs[count] = sh->dev[pd_idx].offset;
	काष्ठा page *xor_dest = xor_srcs[count++] = sh->dev[pd_idx].page;

	BUG_ON(sh->batch_head);
	pr_debug("%s: stripe %llu\n", __func__,
		(अचिन्हित दीर्घ दीर्घ)sh->sector);

	क्रम (i = disks; i--; ) अणु
		काष्ठा r5dev *dev = &sh->dev[i];
		/* Only process blocks that are known to be uptodate */
		अगर (test_bit(R5_InJournal, &dev->flags)) अणु
			/*
			 * For this हाल, PAGE_SIZE must be equal to 4KB and
			 * page offset is zero.
			 */
			off_srcs[count] = dev->offset;
			xor_srcs[count++] = dev->orig_page;
		पूर्ण अन्यथा अगर (test_bit(R5_Wantdrain, &dev->flags)) अणु
			off_srcs[count] = dev->offset;
			xor_srcs[count++] = dev->page;
		पूर्ण
	पूर्ण

	init_async_submit(&submit, ASYNC_TX_FENCE|ASYNC_TX_XOR_DROP_DST, tx,
			  ops_complete_prexor, sh, to_addr_conv(sh, percpu, 0));
	tx = async_xor_offs(xor_dest, off_dest, xor_srcs, off_srcs, count,
			RAID5_STRIPE_SIZE(sh->raid_conf), &submit);

	वापस tx;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
ops_run_prexor6(काष्ठा stripe_head *sh, काष्ठा raid5_percpu *percpu,
		काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा page **blocks = to_addr_page(percpu, 0);
	अचिन्हित पूर्णांक *offs = to_addr_offs(sh, percpu);
	पूर्णांक count;
	काष्ठा async_submit_ctl submit;

	pr_debug("%s: stripe %llu\n", __func__,
		(अचिन्हित दीर्घ दीर्घ)sh->sector);

	count = set_syndrome_sources(blocks, offs, sh, SYNDROME_SRC_WANT_DRAIN);

	init_async_submit(&submit, ASYNC_TX_FENCE|ASYNC_TX_PQ_XOR_DST, tx,
			  ops_complete_prexor, sh, to_addr_conv(sh, percpu, 0));
	tx = async_gen_syndrome(blocks, offs, count+2,
			RAID5_STRIPE_SIZE(sh->raid_conf), &submit);

	वापस tx;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
ops_run_biodrain(काष्ठा stripe_head *sh, काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा r5conf *conf = sh->raid_conf;
	पूर्णांक disks = sh->disks;
	पूर्णांक i;
	काष्ठा stripe_head *head_sh = sh;

	pr_debug("%s: stripe %llu\n", __func__,
		(अचिन्हित दीर्घ दीर्घ)sh->sector);

	क्रम (i = disks; i--; ) अणु
		काष्ठा r5dev *dev;
		काष्ठा bio *chosen;

		sh = head_sh;
		अगर (test_and_clear_bit(R5_Wantdrain, &head_sh->dev[i].flags)) अणु
			काष्ठा bio *wbi;

again:
			dev = &sh->dev[i];
			/*
			 * clear R5_InJournal, so when rewriting a page in
			 * journal, it is not skipped by r5l_log_stripe()
			 */
			clear_bit(R5_InJournal, &dev->flags);
			spin_lock_irq(&sh->stripe_lock);
			chosen = dev->toग_लिखो;
			dev->toग_लिखो = शून्य;
			sh->overग_लिखो_disks = 0;
			BUG_ON(dev->written);
			wbi = dev->written = chosen;
			spin_unlock_irq(&sh->stripe_lock);
			WARN_ON(dev->page != dev->orig_page);

			जबतक (wbi && wbi->bi_iter.bi_sector <
				dev->sector + RAID5_STRIPE_SECTORS(conf)) अणु
				अगर (wbi->bi_opf & REQ_FUA)
					set_bit(R5_WantFUA, &dev->flags);
				अगर (wbi->bi_opf & REQ_SYNC)
					set_bit(R5_SyncIO, &dev->flags);
				अगर (bio_op(wbi) == REQ_OP_DISCARD)
					set_bit(R5_Discard, &dev->flags);
				अन्यथा अणु
					tx = async_copy_data(1, wbi, &dev->page,
							     dev->offset,
							     dev->sector, tx, sh,
							     r5c_is_ग_लिखोback(conf->log));
					अगर (dev->page != dev->orig_page &&
					    !r5c_is_ग_लिखोback(conf->log)) अणु
						set_bit(R5_SkipCopy, &dev->flags);
						clear_bit(R5_UPTODATE, &dev->flags);
						clear_bit(R5_OVERWRITE, &dev->flags);
					पूर्ण
				पूर्ण
				wbi = r5_next_bio(conf, wbi, dev->sector);
			पूर्ण

			अगर (head_sh->batch_head) अणु
				sh = list_first_entry(&sh->batch_list,
						      काष्ठा stripe_head,
						      batch_list);
				अगर (sh == head_sh)
					जारी;
				जाओ again;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस tx;
पूर्ण

अटल व्योम ops_complete_reस्थिरruct(व्योम *stripe_head_ref)
अणु
	काष्ठा stripe_head *sh = stripe_head_ref;
	पूर्णांक disks = sh->disks;
	पूर्णांक pd_idx = sh->pd_idx;
	पूर्णांक qd_idx = sh->qd_idx;
	पूर्णांक i;
	bool fua = false, sync = false, discard = false;

	pr_debug("%s: stripe %llu\n", __func__,
		(अचिन्हित दीर्घ दीर्घ)sh->sector);

	क्रम (i = disks; i--; ) अणु
		fua |= test_bit(R5_WantFUA, &sh->dev[i].flags);
		sync |= test_bit(R5_SyncIO, &sh->dev[i].flags);
		discard |= test_bit(R5_Discard, &sh->dev[i].flags);
	पूर्ण

	क्रम (i = disks; i--; ) अणु
		काष्ठा r5dev *dev = &sh->dev[i];

		अगर (dev->written || i == pd_idx || i == qd_idx) अणु
			अगर (!discard && !test_bit(R5_SkipCopy, &dev->flags)) अणु
				set_bit(R5_UPTODATE, &dev->flags);
				अगर (test_bit(STRIPE_EXPAND_READY, &sh->state))
					set_bit(R5_Expanded, &dev->flags);
			पूर्ण
			अगर (fua)
				set_bit(R5_WantFUA, &dev->flags);
			अगर (sync)
				set_bit(R5_SyncIO, &dev->flags);
		पूर्ण
	पूर्ण

	अगर (sh->reस्थिरruct_state == reस्थिरruct_state_drain_run)
		sh->reस्थिरruct_state = reस्थिरruct_state_drain_result;
	अन्यथा अगर (sh->reस्थिरruct_state == reस्थिरruct_state_prexor_drain_run)
		sh->reस्थिरruct_state = reस्थिरruct_state_prexor_drain_result;
	अन्यथा अणु
		BUG_ON(sh->reस्थिरruct_state != reस्थिरruct_state_run);
		sh->reस्थिरruct_state = reस्थिरruct_state_result;
	पूर्ण

	set_bit(STRIPE_HANDLE, &sh->state);
	raid5_release_stripe(sh);
पूर्ण

अटल व्योम
ops_run_reस्थिरruct5(काष्ठा stripe_head *sh, काष्ठा raid5_percpu *percpu,
		     काष्ठा dma_async_tx_descriptor *tx)
अणु
	पूर्णांक disks = sh->disks;
	काष्ठा page **xor_srcs;
	अचिन्हित पूर्णांक *off_srcs;
	काष्ठा async_submit_ctl submit;
	पूर्णांक count, pd_idx = sh->pd_idx, i;
	काष्ठा page *xor_dest;
	अचिन्हित पूर्णांक off_dest;
	पूर्णांक prexor = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक j = 0;
	काष्ठा stripe_head *head_sh = sh;
	पूर्णांक last_stripe;

	pr_debug("%s: stripe %llu\n", __func__,
		(अचिन्हित दीर्घ दीर्घ)sh->sector);

	क्रम (i = 0; i < sh->disks; i++) अणु
		अगर (pd_idx == i)
			जारी;
		अगर (!test_bit(R5_Discard, &sh->dev[i].flags))
			अवरोध;
	पूर्ण
	अगर (i >= sh->disks) अणु
		atomic_inc(&sh->count);
		set_bit(R5_Discard, &sh->dev[pd_idx].flags);
		ops_complete_reस्थिरruct(sh);
		वापस;
	पूर्ण
again:
	count = 0;
	xor_srcs = to_addr_page(percpu, j);
	off_srcs = to_addr_offs(sh, percpu);
	/* check अगर prexor is active which means only process blocks
	 * that are part of a पढ़ो-modअगरy-ग_लिखो (written)
	 */
	अगर (head_sh->reस्थिरruct_state == reस्थिरruct_state_prexor_drain_run) अणु
		prexor = 1;
		off_dest = off_srcs[count] = sh->dev[pd_idx].offset;
		xor_dest = xor_srcs[count++] = sh->dev[pd_idx].page;
		क्रम (i = disks; i--; ) अणु
			काष्ठा r5dev *dev = &sh->dev[i];
			अगर (head_sh->dev[i].written ||
			    test_bit(R5_InJournal, &head_sh->dev[i].flags)) अणु
				off_srcs[count] = dev->offset;
				xor_srcs[count++] = dev->page;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		xor_dest = sh->dev[pd_idx].page;
		off_dest = sh->dev[pd_idx].offset;
		क्रम (i = disks; i--; ) अणु
			काष्ठा r5dev *dev = &sh->dev[i];
			अगर (i != pd_idx) अणु
				off_srcs[count] = dev->offset;
				xor_srcs[count++] = dev->page;
			पूर्ण
		पूर्ण
	पूर्ण

	/* 1/ अगर we prexor'd then the dest is reused as a source
	 * 2/ अगर we did not prexor then we are reकरोing the parity
	 * set ASYNC_TX_XOR_DROP_DST and ASYNC_TX_XOR_ZERO_DST
	 * क्रम the synchronous xor हाल
	 */
	last_stripe = !head_sh->batch_head ||
		list_first_entry(&sh->batch_list,
				 काष्ठा stripe_head, batch_list) == head_sh;
	अगर (last_stripe) अणु
		flags = ASYNC_TX_ACK |
			(prexor ? ASYNC_TX_XOR_DROP_DST : ASYNC_TX_XOR_ZERO_DST);

		atomic_inc(&head_sh->count);
		init_async_submit(&submit, flags, tx, ops_complete_reस्थिरruct, head_sh,
				  to_addr_conv(sh, percpu, j));
	पूर्ण अन्यथा अणु
		flags = prexor ? ASYNC_TX_XOR_DROP_DST : ASYNC_TX_XOR_ZERO_DST;
		init_async_submit(&submit, flags, tx, शून्य, शून्य,
				  to_addr_conv(sh, percpu, j));
	पूर्ण

	अगर (unlikely(count == 1))
		tx = async_स_नकल(xor_dest, xor_srcs[0], off_dest, off_srcs[0],
				RAID5_STRIPE_SIZE(sh->raid_conf), &submit);
	अन्यथा
		tx = async_xor_offs(xor_dest, off_dest, xor_srcs, off_srcs, count,
				RAID5_STRIPE_SIZE(sh->raid_conf), &submit);
	अगर (!last_stripe) अणु
		j++;
		sh = list_first_entry(&sh->batch_list, काष्ठा stripe_head,
				      batch_list);
		जाओ again;
	पूर्ण
पूर्ण

अटल व्योम
ops_run_reस्थिरruct6(काष्ठा stripe_head *sh, काष्ठा raid5_percpu *percpu,
		     काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा async_submit_ctl submit;
	काष्ठा page **blocks;
	अचिन्हित पूर्णांक *offs;
	पूर्णांक count, i, j = 0;
	काष्ठा stripe_head *head_sh = sh;
	पूर्णांक last_stripe;
	पूर्णांक synflags;
	अचिन्हित दीर्घ txflags;

	pr_debug("%s: stripe %llu\n", __func__, (अचिन्हित दीर्घ दीर्घ)sh->sector);

	क्रम (i = 0; i < sh->disks; i++) अणु
		अगर (sh->pd_idx == i || sh->qd_idx == i)
			जारी;
		अगर (!test_bit(R5_Discard, &sh->dev[i].flags))
			अवरोध;
	पूर्ण
	अगर (i >= sh->disks) अणु
		atomic_inc(&sh->count);
		set_bit(R5_Discard, &sh->dev[sh->pd_idx].flags);
		set_bit(R5_Discard, &sh->dev[sh->qd_idx].flags);
		ops_complete_reस्थिरruct(sh);
		वापस;
	पूर्ण

again:
	blocks = to_addr_page(percpu, j);
	offs = to_addr_offs(sh, percpu);

	अगर (sh->reस्थिरruct_state == reस्थिरruct_state_prexor_drain_run) अणु
		synflags = SYNDROME_SRC_WRITTEN;
		txflags = ASYNC_TX_ACK | ASYNC_TX_PQ_XOR_DST;
	पूर्ण अन्यथा अणु
		synflags = SYNDROME_SRC_ALL;
		txflags = ASYNC_TX_ACK;
	पूर्ण

	count = set_syndrome_sources(blocks, offs, sh, synflags);
	last_stripe = !head_sh->batch_head ||
		list_first_entry(&sh->batch_list,
				 काष्ठा stripe_head, batch_list) == head_sh;

	अगर (last_stripe) अणु
		atomic_inc(&head_sh->count);
		init_async_submit(&submit, txflags, tx, ops_complete_reस्थिरruct,
				  head_sh, to_addr_conv(sh, percpu, j));
	पूर्ण अन्यथा
		init_async_submit(&submit, 0, tx, शून्य, शून्य,
				  to_addr_conv(sh, percpu, j));
	tx = async_gen_syndrome(blocks, offs, count+2,
			RAID5_STRIPE_SIZE(sh->raid_conf),  &submit);
	अगर (!last_stripe) अणु
		j++;
		sh = list_first_entry(&sh->batch_list, काष्ठा stripe_head,
				      batch_list);
		जाओ again;
	पूर्ण
पूर्ण

अटल व्योम ops_complete_check(व्योम *stripe_head_ref)
अणु
	काष्ठा stripe_head *sh = stripe_head_ref;

	pr_debug("%s: stripe %llu\n", __func__,
		(अचिन्हित दीर्घ दीर्घ)sh->sector);

	sh->check_state = check_state_check_result;
	set_bit(STRIPE_HANDLE, &sh->state);
	raid5_release_stripe(sh);
पूर्ण

अटल व्योम ops_run_check_p(काष्ठा stripe_head *sh, काष्ठा raid5_percpu *percpu)
अणु
	पूर्णांक disks = sh->disks;
	पूर्णांक pd_idx = sh->pd_idx;
	पूर्णांक qd_idx = sh->qd_idx;
	काष्ठा page *xor_dest;
	अचिन्हित पूर्णांक off_dest;
	काष्ठा page **xor_srcs = to_addr_page(percpu, 0);
	अचिन्हित पूर्णांक *off_srcs = to_addr_offs(sh, percpu);
	काष्ठा dma_async_tx_descriptor *tx;
	काष्ठा async_submit_ctl submit;
	पूर्णांक count;
	पूर्णांक i;

	pr_debug("%s: stripe %llu\n", __func__,
		(अचिन्हित दीर्घ दीर्घ)sh->sector);

	BUG_ON(sh->batch_head);
	count = 0;
	xor_dest = sh->dev[pd_idx].page;
	off_dest = sh->dev[pd_idx].offset;
	off_srcs[count] = off_dest;
	xor_srcs[count++] = xor_dest;
	क्रम (i = disks; i--; ) अणु
		अगर (i == pd_idx || i == qd_idx)
			जारी;
		off_srcs[count] = sh->dev[i].offset;
		xor_srcs[count++] = sh->dev[i].page;
	पूर्ण

	init_async_submit(&submit, 0, शून्य, शून्य, शून्य,
			  to_addr_conv(sh, percpu, 0));
	tx = async_xor_val_offs(xor_dest, off_dest, xor_srcs, off_srcs, count,
			   RAID5_STRIPE_SIZE(sh->raid_conf),
			   &sh->ops.zero_sum_result, &submit);

	atomic_inc(&sh->count);
	init_async_submit(&submit, ASYNC_TX_ACK, tx, ops_complete_check, sh, शून्य);
	tx = async_trigger_callback(&submit);
पूर्ण

अटल व्योम ops_run_check_pq(काष्ठा stripe_head *sh, काष्ठा raid5_percpu *percpu, पूर्णांक checkp)
अणु
	काष्ठा page **srcs = to_addr_page(percpu, 0);
	अचिन्हित पूर्णांक *offs = to_addr_offs(sh, percpu);
	काष्ठा async_submit_ctl submit;
	पूर्णांक count;

	pr_debug("%s: stripe %llu checkp: %d\n", __func__,
		(अचिन्हित दीर्घ दीर्घ)sh->sector, checkp);

	BUG_ON(sh->batch_head);
	count = set_syndrome_sources(srcs, offs, sh, SYNDROME_SRC_ALL);
	अगर (!checkp)
		srcs[count] = शून्य;

	atomic_inc(&sh->count);
	init_async_submit(&submit, ASYNC_TX_ACK, शून्य, ops_complete_check,
			  sh, to_addr_conv(sh, percpu, 0));
	async_syndrome_val(srcs, offs, count+2,
			   RAID5_STRIPE_SIZE(sh->raid_conf),
			   &sh->ops.zero_sum_result, percpu->spare_page, 0, &submit);
पूर्ण

अटल व्योम raid_run_ops(काष्ठा stripe_head *sh, अचिन्हित दीर्घ ops_request)
अणु
	पूर्णांक overlap_clear = 0, i, disks = sh->disks;
	काष्ठा dma_async_tx_descriptor *tx = शून्य;
	काष्ठा r5conf *conf = sh->raid_conf;
	पूर्णांक level = conf->level;
	काष्ठा raid5_percpu *percpu;
	अचिन्हित दीर्घ cpu;

	cpu = get_cpu();
	percpu = per_cpu_ptr(conf->percpu, cpu);
	अगर (test_bit(STRIPE_OP_BIOFILL, &ops_request)) अणु
		ops_run_biofill(sh);
		overlap_clear++;
	पूर्ण

	अगर (test_bit(STRIPE_OP_COMPUTE_BLK, &ops_request)) अणु
		अगर (level < 6)
			tx = ops_run_compute5(sh, percpu);
		अन्यथा अणु
			अगर (sh->ops.target2 < 0 || sh->ops.target < 0)
				tx = ops_run_compute6_1(sh, percpu);
			अन्यथा
				tx = ops_run_compute6_2(sh, percpu);
		पूर्ण
		/* terminate the chain अगर reस्थिरruct is not set to be run */
		अगर (tx && !test_bit(STRIPE_OP_RECONSTRUCT, &ops_request))
			async_tx_ack(tx);
	पूर्ण

	अगर (test_bit(STRIPE_OP_PREXOR, &ops_request)) अणु
		अगर (level < 6)
			tx = ops_run_prexor5(sh, percpu, tx);
		अन्यथा
			tx = ops_run_prexor6(sh, percpu, tx);
	पूर्ण

	अगर (test_bit(STRIPE_OP_PARTIAL_PARITY, &ops_request))
		tx = ops_run_partial_parity(sh, percpu, tx);

	अगर (test_bit(STRIPE_OP_BIODRAIN, &ops_request)) अणु
		tx = ops_run_biodrain(sh, tx);
		overlap_clear++;
	पूर्ण

	अगर (test_bit(STRIPE_OP_RECONSTRUCT, &ops_request)) अणु
		अगर (level < 6)
			ops_run_reस्थिरruct5(sh, percpu, tx);
		अन्यथा
			ops_run_reस्थिरruct6(sh, percpu, tx);
	पूर्ण

	अगर (test_bit(STRIPE_OP_CHECK, &ops_request)) अणु
		अगर (sh->check_state == check_state_run)
			ops_run_check_p(sh, percpu);
		अन्यथा अगर (sh->check_state == check_state_run_q)
			ops_run_check_pq(sh, percpu, 0);
		अन्यथा अगर (sh->check_state == check_state_run_pq)
			ops_run_check_pq(sh, percpu, 1);
		अन्यथा
			BUG();
	पूर्ण

	अगर (overlap_clear && !sh->batch_head)
		क्रम (i = disks; i--; ) अणु
			काष्ठा r5dev *dev = &sh->dev[i];
			अगर (test_and_clear_bit(R5_Overlap, &dev->flags))
				wake_up(&sh->raid_conf->रुको_क्रम_overlap);
		पूर्ण
	put_cpu();
पूर्ण

अटल व्योम मुक्त_stripe(काष्ठा kmem_cache *sc, काष्ठा stripe_head *sh)
अणु
#अगर PAGE_SIZE != DEFAULT_STRIPE_SIZE
	kमुक्त(sh->pages);
#पूर्ण_अगर
	अगर (sh->ppl_page)
		__मुक्त_page(sh->ppl_page);
	kmem_cache_मुक्त(sc, sh);
पूर्ण

अटल काष्ठा stripe_head *alloc_stripe(काष्ठा kmem_cache *sc, gfp_t gfp,
	पूर्णांक disks, काष्ठा r5conf *conf)
अणु
	काष्ठा stripe_head *sh;
	पूर्णांक i;

	sh = kmem_cache_zalloc(sc, gfp);
	अगर (sh) अणु
		spin_lock_init(&sh->stripe_lock);
		spin_lock_init(&sh->batch_lock);
		INIT_LIST_HEAD(&sh->batch_list);
		INIT_LIST_HEAD(&sh->lru);
		INIT_LIST_HEAD(&sh->r5c);
		INIT_LIST_HEAD(&sh->log_list);
		atomic_set(&sh->count, 1);
		sh->raid_conf = conf;
		sh->log_start = MaxSector;
		क्रम (i = 0; i < disks; i++) अणु
			काष्ठा r5dev *dev = &sh->dev[i];

			bio_init(&dev->req, &dev->vec, 1);
			bio_init(&dev->rreq, &dev->rvec, 1);
		पूर्ण

		अगर (raid5_has_ppl(conf)) अणु
			sh->ppl_page = alloc_page(gfp);
			अगर (!sh->ppl_page) अणु
				मुक्त_stripe(sc, sh);
				वापस शून्य;
			पूर्ण
		पूर्ण
#अगर PAGE_SIZE != DEFAULT_STRIPE_SIZE
		अगर (init_stripe_shared_pages(sh, conf, disks)) अणु
			मुक्त_stripe(sc, sh);
			वापस शून्य;
		पूर्ण
#पूर्ण_अगर
	पूर्ण
	वापस sh;
पूर्ण
अटल पूर्णांक grow_one_stripe(काष्ठा r5conf *conf, gfp_t gfp)
अणु
	काष्ठा stripe_head *sh;

	sh = alloc_stripe(conf->slab_cache, gfp, conf->pool_size, conf);
	अगर (!sh)
		वापस 0;

	अगर (grow_buffers(sh, gfp)) अणु
		shrink_buffers(sh);
		मुक्त_stripe(conf->slab_cache, sh);
		वापस 0;
	पूर्ण
	sh->hash_lock_index =
		conf->max_nr_stripes % NR_STRIPE_HASH_LOCKS;
	/* we just created an active stripe so... */
	atomic_inc(&conf->active_stripes);

	raid5_release_stripe(sh);
	conf->max_nr_stripes++;
	वापस 1;
पूर्ण

अटल पूर्णांक grow_stripes(काष्ठा r5conf *conf, पूर्णांक num)
अणु
	काष्ठा kmem_cache *sc;
	माप_प्रकार namelen = माप(conf->cache_name[0]);
	पूर्णांक devs = max(conf->raid_disks, conf->previous_raid_disks);

	अगर (conf->mddev->gendisk)
		snम_लिखो(conf->cache_name[0], namelen,
			"raid%d-%s", conf->level, mdname(conf->mddev));
	अन्यथा
		snम_लिखो(conf->cache_name[0], namelen,
			"raid%d-%p", conf->level, conf->mddev);
	snम_लिखो(conf->cache_name[1], namelen, "%.27s-alt", conf->cache_name[0]);

	conf->active_name = 0;
	sc = kmem_cache_create(conf->cache_name[conf->active_name],
			       माप(काष्ठा stripe_head)+(devs-1)*माप(काष्ठा r5dev),
			       0, 0, शून्य);
	अगर (!sc)
		वापस 1;
	conf->slab_cache = sc;
	conf->pool_size = devs;
	जबतक (num--)
		अगर (!grow_one_stripe(conf, GFP_KERNEL))
			वापस 1;

	वापस 0;
पूर्ण

/**
 * scribble_alloc - allocate percpu scribble buffer क्रम required size
 *		    of the scribble region
 * @percpu: from क्रम_each_present_cpu() of the caller
 * @num: total number of disks in the array
 * @cnt: scribble objs count क्रम required size of the scribble region
 *
 * The scribble buffer size must be enough to contain:
 * 1/ a काष्ठा page poपूर्णांकer क्रम each device in the array +2
 * 2/ room to convert each entry in (1) to its corresponding dma
 *    (dma_map_page()) or page (page_address()) address.
 *
 * Note: the +2 is क्रम the destination buffers of the ddf/raid6 हाल where we
 * calculate over all devices (not just the data blocks), using zeros in place
 * of the P and Q blocks.
 */
अटल पूर्णांक scribble_alloc(काष्ठा raid5_percpu *percpu,
			  पूर्णांक num, पूर्णांक cnt)
अणु
	माप_प्रकार obj_size =
		माप(काष्ठा page *) * (num + 2) +
		माप(addr_conv_t) * (num + 2) +
		माप(अचिन्हित पूर्णांक) * (num + 2);
	व्योम *scribble;

	/*
	 * If here is in raid array suspend context, it is in meदो_स्मृति noio
	 * context as well, there is no potential recursive memory reclaim
	 * I/Os with the GFP_KERNEL flag.
	 */
	scribble = kvदो_स्मृति_array(cnt, obj_size, GFP_KERNEL);
	अगर (!scribble)
		वापस -ENOMEM;

	kvमुक्त(percpu->scribble);

	percpu->scribble = scribble;
	percpu->scribble_obj_size = obj_size;
	वापस 0;
पूर्ण

अटल पूर्णांक resize_chunks(काष्ठा r5conf *conf, पूर्णांक new_disks, पूर्णांक new_sectors)
अणु
	अचिन्हित दीर्घ cpu;
	पूर्णांक err = 0;

	/*
	 * Never shrink. And mddev_suspend() could deadlock अगर this is called
	 * from raid5d. In that हाल, scribble_disks and scribble_sectors
	 * should equal to new_disks and new_sectors
	 */
	अगर (conf->scribble_disks >= new_disks &&
	    conf->scribble_sectors >= new_sectors)
		वापस 0;
	mddev_suspend(conf->mddev);
	get_online_cpus();

	क्रम_each_present_cpu(cpu) अणु
		काष्ठा raid5_percpu *percpu;

		percpu = per_cpu_ptr(conf->percpu, cpu);
		err = scribble_alloc(percpu, new_disks,
				     new_sectors / RAID5_STRIPE_SECTORS(conf));
		अगर (err)
			अवरोध;
	पूर्ण

	put_online_cpus();
	mddev_resume(conf->mddev);
	अगर (!err) अणु
		conf->scribble_disks = new_disks;
		conf->scribble_sectors = new_sectors;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक resize_stripes(काष्ठा r5conf *conf, पूर्णांक newsize)
अणु
	/* Make all the stripes able to hold 'newsize' devices.
	 * New slots in each stripe get 'page' set to a new page.
	 *
	 * This happens in stages:
	 * 1/ create a new kmem_cache and allocate the required number of
	 *    stripe_heads.
	 * 2/ gather all the old stripe_heads and transfer the pages across
	 *    to the new stripe_heads.  This will have the side effect of
	 *    मुक्तzing the array as once all stripe_heads have been collected,
	 *    no IO will be possible.  Old stripe heads are मुक्तd once their
	 *    pages have been transferred over, and the old kmem_cache is
	 *    मुक्तd when all stripes are करोne.
	 * 3/ पुनः_स्मृतिate conf->disks to be suitable bigger.  If this fails,
	 *    we simple वापस a failure status - no need to clean anything up.
	 * 4/ allocate new pages क्रम the new slots in the new stripe_heads.
	 *    If this fails, we करोn't bother trying the shrink the
	 *    stripe_heads करोwn again, we just leave them as they are.
	 *    As each stripe_head is processed the new one is released पूर्णांकo
	 *    active service.
	 *
	 * Once step2 is started, we cannot afक्रमd to रुको क्रम a ग_लिखो,
	 * so we use GFP_NOIO allocations.
	 */
	काष्ठा stripe_head *osh, *nsh;
	LIST_HEAD(newstripes);
	काष्ठा disk_info *ndisks;
	पूर्णांक err = 0;
	काष्ठा kmem_cache *sc;
	पूर्णांक i;
	पूर्णांक hash, cnt;

	md_allow_ग_लिखो(conf->mddev);

	/* Step 1 */
	sc = kmem_cache_create(conf->cache_name[1-conf->active_name],
			       माप(काष्ठा stripe_head)+(newsize-1)*माप(काष्ठा r5dev),
			       0, 0, शून्य);
	अगर (!sc)
		वापस -ENOMEM;

	/* Need to ensure स्वतः-resizing करोesn't पूर्णांकerfere */
	mutex_lock(&conf->cache_size_mutex);

	क्रम (i = conf->max_nr_stripes; i; i--) अणु
		nsh = alloc_stripe(sc, GFP_KERNEL, newsize, conf);
		अगर (!nsh)
			अवरोध;

		list_add(&nsh->lru, &newstripes);
	पूर्ण
	अगर (i) अणु
		/* didn't get enough, give up */
		जबतक (!list_empty(&newstripes)) अणु
			nsh = list_entry(newstripes.next, काष्ठा stripe_head, lru);
			list_del(&nsh->lru);
			मुक्त_stripe(sc, nsh);
		पूर्ण
		kmem_cache_destroy(sc);
		mutex_unlock(&conf->cache_size_mutex);
		वापस -ENOMEM;
	पूर्ण
	/* Step 2 - Must use GFP_NOIO now.
	 * OK, we have enough stripes, start collecting inactive
	 * stripes and copying them over
	 */
	hash = 0;
	cnt = 0;
	list_क्रम_each_entry(nsh, &newstripes, lru) अणु
		lock_device_hash_lock(conf, hash);
		रुको_event_cmd(conf->रुको_क्रम_stripe,
				    !list_empty(conf->inactive_list + hash),
				    unlock_device_hash_lock(conf, hash),
				    lock_device_hash_lock(conf, hash));
		osh = get_मुक्त_stripe(conf, hash);
		unlock_device_hash_lock(conf, hash);

#अगर PAGE_SIZE != DEFAULT_STRIPE_SIZE
	क्रम (i = 0; i < osh->nr_pages; i++) अणु
		nsh->pages[i] = osh->pages[i];
		osh->pages[i] = शून्य;
	पूर्ण
#पूर्ण_अगर
		क्रम(i=0; i<conf->pool_size; i++) अणु
			nsh->dev[i].page = osh->dev[i].page;
			nsh->dev[i].orig_page = osh->dev[i].page;
			nsh->dev[i].offset = osh->dev[i].offset;
		पूर्ण
		nsh->hash_lock_index = hash;
		मुक्त_stripe(conf->slab_cache, osh);
		cnt++;
		अगर (cnt >= conf->max_nr_stripes / NR_STRIPE_HASH_LOCKS +
		    !!((conf->max_nr_stripes % NR_STRIPE_HASH_LOCKS) > hash)) अणु
			hash++;
			cnt = 0;
		पूर्ण
	पूर्ण
	kmem_cache_destroy(conf->slab_cache);

	/* Step 3.
	 * At this poपूर्णांक, we are holding all the stripes so the array
	 * is completely stalled, so now is a good समय to resize
	 * conf->disks and the scribble region
	 */
	ndisks = kसुस्मृति(newsize, माप(काष्ठा disk_info), GFP_NOIO);
	अगर (ndisks) अणु
		क्रम (i = 0; i < conf->pool_size; i++)
			ndisks[i] = conf->disks[i];

		क्रम (i = conf->pool_size; i < newsize; i++) अणु
			ndisks[i].extra_page = alloc_page(GFP_NOIO);
			अगर (!ndisks[i].extra_page)
				err = -ENOMEM;
		पूर्ण

		अगर (err) अणु
			क्रम (i = conf->pool_size; i < newsize; i++)
				अगर (ndisks[i].extra_page)
					put_page(ndisks[i].extra_page);
			kमुक्त(ndisks);
		पूर्ण अन्यथा अणु
			kमुक्त(conf->disks);
			conf->disks = ndisks;
		पूर्ण
	पूर्ण अन्यथा
		err = -ENOMEM;

	conf->slab_cache = sc;
	conf->active_name = 1-conf->active_name;

	/* Step 4, वापस new stripes to service */
	जबतक(!list_empty(&newstripes)) अणु
		nsh = list_entry(newstripes.next, काष्ठा stripe_head, lru);
		list_del_init(&nsh->lru);

#अगर PAGE_SIZE != DEFAULT_STRIPE_SIZE
		क्रम (i = 0; i < nsh->nr_pages; i++) अणु
			अगर (nsh->pages[i])
				जारी;
			nsh->pages[i] = alloc_page(GFP_NOIO);
			अगर (!nsh->pages[i])
				err = -ENOMEM;
		पूर्ण

		क्रम (i = conf->raid_disks; i < newsize; i++) अणु
			अगर (nsh->dev[i].page)
				जारी;
			nsh->dev[i].page = raid5_get_dev_page(nsh, i);
			nsh->dev[i].orig_page = nsh->dev[i].page;
			nsh->dev[i].offset = raid5_get_page_offset(nsh, i);
		पूर्ण
#अन्यथा
		क्रम (i=conf->raid_disks; i < newsize; i++)
			अगर (nsh->dev[i].page == शून्य) अणु
				काष्ठा page *p = alloc_page(GFP_NOIO);
				nsh->dev[i].page = p;
				nsh->dev[i].orig_page = p;
				nsh->dev[i].offset = 0;
				अगर (!p)
					err = -ENOMEM;
			पूर्ण
#पूर्ण_अगर
		raid5_release_stripe(nsh);
	पूर्ण
	/* critical section pass, GFP_NOIO no दीर्घer needed */

	अगर (!err)
		conf->pool_size = newsize;
	mutex_unlock(&conf->cache_size_mutex);

	वापस err;
पूर्ण

अटल पूर्णांक drop_one_stripe(काष्ठा r5conf *conf)
अणु
	काष्ठा stripe_head *sh;
	पूर्णांक hash = (conf->max_nr_stripes - 1) & STRIPE_HASH_LOCKS_MASK;

	spin_lock_irq(conf->hash_locks + hash);
	sh = get_मुक्त_stripe(conf, hash);
	spin_unlock_irq(conf->hash_locks + hash);
	अगर (!sh)
		वापस 0;
	BUG_ON(atomic_पढ़ो(&sh->count));
	shrink_buffers(sh);
	मुक्त_stripe(conf->slab_cache, sh);
	atomic_dec(&conf->active_stripes);
	conf->max_nr_stripes--;
	वापस 1;
पूर्ण

अटल व्योम shrink_stripes(काष्ठा r5conf *conf)
अणु
	जबतक (conf->max_nr_stripes &&
	       drop_one_stripe(conf))
		;

	kmem_cache_destroy(conf->slab_cache);
	conf->slab_cache = शून्य;
पूर्ण

अटल व्योम raid5_end_पढ़ो_request(काष्ठा bio * bi)
अणु
	काष्ठा stripe_head *sh = bi->bi_निजी;
	काष्ठा r5conf *conf = sh->raid_conf;
	पूर्णांक disks = sh->disks, i;
	अक्षर b[BDEVNAME_SIZE];
	काष्ठा md_rdev *rdev = शून्य;
	sector_t s;

	क्रम (i=0 ; i<disks; i++)
		अगर (bi == &sh->dev[i].req)
			अवरोध;

	pr_debug("end_read_request %llu/%d, count: %d, error %d.\n",
		(अचिन्हित दीर्घ दीर्घ)sh->sector, i, atomic_पढ़ो(&sh->count),
		bi->bi_status);
	अगर (i == disks) अणु
		bio_reset(bi);
		BUG();
		वापस;
	पूर्ण
	अगर (test_bit(R5_ReadRepl, &sh->dev[i].flags))
		/* If replacement finished जबतक this request was outstanding,
		 * 'replacement' might be शून्य alपढ़ोy.
		 * In that हाल it moved करोwn to 'rdev'.
		 * rdev is not हटाओd until all requests are finished.
		 */
		rdev = conf->disks[i].replacement;
	अगर (!rdev)
		rdev = conf->disks[i].rdev;

	अगर (use_new_offset(conf, sh))
		s = sh->sector + rdev->new_data_offset;
	अन्यथा
		s = sh->sector + rdev->data_offset;
	अगर (!bi->bi_status) अणु
		set_bit(R5_UPTODATE, &sh->dev[i].flags);
		अगर (test_bit(R5_ReadError, &sh->dev[i].flags)) अणु
			/* Note that this cannot happen on a
			 * replacement device.  We just fail those on
			 * any error
			 */
			pr_info_ratelimited(
				"md/raid:%s: read error corrected (%lu sectors at %llu on %s)\n",
				mdname(conf->mddev), RAID5_STRIPE_SECTORS(conf),
				(अचिन्हित दीर्घ दीर्घ)s,
				bdevname(rdev->bdev, b));
			atomic_add(RAID5_STRIPE_SECTORS(conf), &rdev->corrected_errors);
			clear_bit(R5_ReadError, &sh->dev[i].flags);
			clear_bit(R5_ReWrite, &sh->dev[i].flags);
		पूर्ण अन्यथा अगर (test_bit(R5_ReadNoMerge, &sh->dev[i].flags))
			clear_bit(R5_ReadNoMerge, &sh->dev[i].flags);

		अगर (test_bit(R5_InJournal, &sh->dev[i].flags))
			/*
			 * end पढ़ो क्रम a page in journal, this
			 * must be preparing क्रम prexor in rmw
			 */
			set_bit(R5_OrigPageUPTDODATE, &sh->dev[i].flags);

		अगर (atomic_पढ़ो(&rdev->पढ़ो_errors))
			atomic_set(&rdev->पढ़ो_errors, 0);
	पूर्ण अन्यथा अणु
		स्थिर अक्षर *bdn = bdevname(rdev->bdev, b);
		पूर्णांक retry = 0;
		पूर्णांक set_bad = 0;

		clear_bit(R5_UPTODATE, &sh->dev[i].flags);
		अगर (!(bi->bi_status == BLK_STS_PROTECTION))
			atomic_inc(&rdev->पढ़ो_errors);
		अगर (test_bit(R5_ReadRepl, &sh->dev[i].flags))
			pr_warn_ratelimited(
				"md/raid:%s: read error on replacement device (sector %llu on %s).\n",
				mdname(conf->mddev),
				(अचिन्हित दीर्घ दीर्घ)s,
				bdn);
		अन्यथा अगर (conf->mddev->degraded >= conf->max_degraded) अणु
			set_bad = 1;
			pr_warn_ratelimited(
				"md/raid:%s: read error not correctable (sector %llu on %s).\n",
				mdname(conf->mddev),
				(अचिन्हित दीर्घ दीर्घ)s,
				bdn);
		पूर्ण अन्यथा अगर (test_bit(R5_ReWrite, &sh->dev[i].flags)) अणु
			/* Oh, no!!! */
			set_bad = 1;
			pr_warn_ratelimited(
				"md/raid:%s: read error NOT corrected!! (sector %llu on %s).\n",
				mdname(conf->mddev),
				(अचिन्हित दीर्घ दीर्घ)s,
				bdn);
		पूर्ण अन्यथा अगर (atomic_पढ़ो(&rdev->पढ़ो_errors)
			 > conf->max_nr_stripes) अणु
			अगर (!test_bit(Faulty, &rdev->flags)) अणु
				pr_warn("md/raid:%s: %d read_errors > %d stripes\n",
				    mdname(conf->mddev),
				    atomic_पढ़ो(&rdev->पढ़ो_errors),
				    conf->max_nr_stripes);
				pr_warn("md/raid:%s: Too many read errors, failing device %s.\n",
				    mdname(conf->mddev), bdn);
			पूर्ण
		पूर्ण अन्यथा
			retry = 1;
		अगर (set_bad && test_bit(In_sync, &rdev->flags)
		    && !test_bit(R5_ReadNoMerge, &sh->dev[i].flags))
			retry = 1;
		अगर (retry)
			अगर (sh->qd_idx >= 0 && sh->pd_idx == i)
				set_bit(R5_ReadError, &sh->dev[i].flags);
			अन्यथा अगर (test_bit(R5_ReadNoMerge, &sh->dev[i].flags)) अणु
				set_bit(R5_ReadError, &sh->dev[i].flags);
				clear_bit(R5_ReadNoMerge, &sh->dev[i].flags);
			पूर्ण अन्यथा
				set_bit(R5_ReadNoMerge, &sh->dev[i].flags);
		अन्यथा अणु
			clear_bit(R5_ReadError, &sh->dev[i].flags);
			clear_bit(R5_ReWrite, &sh->dev[i].flags);
			अगर (!(set_bad
			      && test_bit(In_sync, &rdev->flags)
			      && rdev_set_badblocks(
				      rdev, sh->sector, RAID5_STRIPE_SECTORS(conf), 0)))
				md_error(conf->mddev, rdev);
		पूर्ण
	पूर्ण
	rdev_dec_pending(rdev, conf->mddev);
	bio_reset(bi);
	clear_bit(R5_LOCKED, &sh->dev[i].flags);
	set_bit(STRIPE_HANDLE, &sh->state);
	raid5_release_stripe(sh);
पूर्ण

अटल व्योम raid5_end_ग_लिखो_request(काष्ठा bio *bi)
अणु
	काष्ठा stripe_head *sh = bi->bi_निजी;
	काष्ठा r5conf *conf = sh->raid_conf;
	पूर्णांक disks = sh->disks, i;
	काष्ठा md_rdev *rdev;
	sector_t first_bad;
	पूर्णांक bad_sectors;
	पूर्णांक replacement = 0;

	क्रम (i = 0 ; i < disks; i++) अणु
		अगर (bi == &sh->dev[i].req) अणु
			rdev = conf->disks[i].rdev;
			अवरोध;
		पूर्ण
		अगर (bi == &sh->dev[i].rreq) अणु
			rdev = conf->disks[i].replacement;
			अगर (rdev)
				replacement = 1;
			अन्यथा
				/* rdev was हटाओd and 'replacement'
				 * replaced it.  rdev is not हटाओd
				 * until all requests are finished.
				 */
				rdev = conf->disks[i].rdev;
			अवरोध;
		पूर्ण
	पूर्ण
	pr_debug("end_write_request %llu/%d, count %d, error: %d.\n",
		(अचिन्हित दीर्घ दीर्घ)sh->sector, i, atomic_पढ़ो(&sh->count),
		bi->bi_status);
	अगर (i == disks) अणु
		bio_reset(bi);
		BUG();
		वापस;
	पूर्ण

	अगर (replacement) अणु
		अगर (bi->bi_status)
			md_error(conf->mddev, rdev);
		अन्यथा अगर (is_badblock(rdev, sh->sector,
				     RAID5_STRIPE_SECTORS(conf),
				     &first_bad, &bad_sectors))
			set_bit(R5_MadeGoodRepl, &sh->dev[i].flags);
	पूर्ण अन्यथा अणु
		अगर (bi->bi_status) अणु
			set_bit(STRIPE_DEGRADED, &sh->state);
			set_bit(WriteErrorSeen, &rdev->flags);
			set_bit(R5_WriteError, &sh->dev[i].flags);
			अगर (!test_and_set_bit(WantReplacement, &rdev->flags))
				set_bit(MD_RECOVERY_NEEDED,
					&rdev->mddev->recovery);
		पूर्ण अन्यथा अगर (is_badblock(rdev, sh->sector,
				       RAID5_STRIPE_SECTORS(conf),
				       &first_bad, &bad_sectors)) अणु
			set_bit(R5_MadeGood, &sh->dev[i].flags);
			अगर (test_bit(R5_ReadError, &sh->dev[i].flags))
				/* That was a successful ग_लिखो so make
				 * sure it looks like we alपढ़ोy did
				 * a re-ग_लिखो.
				 */
				set_bit(R5_ReWrite, &sh->dev[i].flags);
		पूर्ण
	पूर्ण
	rdev_dec_pending(rdev, conf->mddev);

	अगर (sh->batch_head && bi->bi_status && !replacement)
		set_bit(STRIPE_BATCH_ERR, &sh->batch_head->state);

	bio_reset(bi);
	अगर (!test_and_clear_bit(R5_DOUBLE_LOCKED, &sh->dev[i].flags))
		clear_bit(R5_LOCKED, &sh->dev[i].flags);
	set_bit(STRIPE_HANDLE, &sh->state);
	raid5_release_stripe(sh);

	अगर (sh->batch_head && sh != sh->batch_head)
		raid5_release_stripe(sh->batch_head);
पूर्ण

अटल व्योम raid5_error(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	अक्षर b[BDEVNAME_SIZE];
	काष्ठा r5conf *conf = mddev->निजी;
	अचिन्हित दीर्घ flags;
	pr_debug("raid456: error called\n");

	spin_lock_irqsave(&conf->device_lock, flags);

	अगर (test_bit(In_sync, &rdev->flags) &&
	    mddev->degraded == conf->max_degraded) अणु
		/*
		 * Don't allow to achieve failed state
		 * Don't try to recover this device
		 */
		conf->recovery_disabled = mddev->recovery_disabled;
		spin_unlock_irqrestore(&conf->device_lock, flags);
		वापस;
	पूर्ण

	set_bit(Faulty, &rdev->flags);
	clear_bit(In_sync, &rdev->flags);
	mddev->degraded = raid5_calc_degraded(conf);
	spin_unlock_irqrestore(&conf->device_lock, flags);
	set_bit(MD_RECOVERY_INTR, &mddev->recovery);

	set_bit(Blocked, &rdev->flags);
	set_mask_bits(&mddev->sb_flags, 0,
		      BIT(MD_SB_CHANGE_DEVS) | BIT(MD_SB_CHANGE_PENDING));
	pr_crit("md/raid:%s: Disk failure on %s, disabling device.\n"
		"md/raid:%s: Operation continuing on %d devices.\n",
		mdname(mddev),
		bdevname(rdev->bdev, b),
		mdname(mddev),
		conf->raid_disks - mddev->degraded);
	r5c_update_on_rdev_error(mddev, rdev);
पूर्ण

/*
 * Input: a 'big' sector number,
 * Output: index of the data and parity disk, and the sector # in them.
 */
sector_t raid5_compute_sector(काष्ठा r5conf *conf, sector_t r_sector,
			      पूर्णांक previous, पूर्णांक *dd_idx,
			      काष्ठा stripe_head *sh)
अणु
	sector_t stripe, stripe2;
	sector_t chunk_number;
	अचिन्हित पूर्णांक chunk_offset;
	पूर्णांक pd_idx, qd_idx;
	पूर्णांक ddf_layout = 0;
	sector_t new_sector;
	पूर्णांक algorithm = previous ? conf->prev_algo
				 : conf->algorithm;
	पूर्णांक sectors_per_chunk = previous ? conf->prev_chunk_sectors
					 : conf->chunk_sectors;
	पूर्णांक raid_disks = previous ? conf->previous_raid_disks
				  : conf->raid_disks;
	पूर्णांक data_disks = raid_disks - conf->max_degraded;

	/* First compute the inक्रमmation on this sector */

	/*
	 * Compute the chunk number and the sector offset inside the chunk
	 */
	chunk_offset = sector_भाग(r_sector, sectors_per_chunk);
	chunk_number = r_sector;

	/*
	 * Compute the stripe number
	 */
	stripe = chunk_number;
	*dd_idx = sector_भाग(stripe, data_disks);
	stripe2 = stripe;
	/*
	 * Select the parity disk based on the user selected algorithm.
	 */
	pd_idx = qd_idx = -1;
	चयन(conf->level) अणु
	हाल 4:
		pd_idx = data_disks;
		अवरोध;
	हाल 5:
		चयन (algorithm) अणु
		हाल ALGORITHM_LEFT_ASYMMETRIC:
			pd_idx = data_disks - sector_भाग(stripe2, raid_disks);
			अगर (*dd_idx >= pd_idx)
				(*dd_idx)++;
			अवरोध;
		हाल ALGORITHM_RIGHT_ASYMMETRIC:
			pd_idx = sector_भाग(stripe2, raid_disks);
			अगर (*dd_idx >= pd_idx)
				(*dd_idx)++;
			अवरोध;
		हाल ALGORITHM_LEFT_SYMMETRIC:
			pd_idx = data_disks - sector_भाग(stripe2, raid_disks);
			*dd_idx = (pd_idx + 1 + *dd_idx) % raid_disks;
			अवरोध;
		हाल ALGORITHM_RIGHT_SYMMETRIC:
			pd_idx = sector_भाग(stripe2, raid_disks);
			*dd_idx = (pd_idx + 1 + *dd_idx) % raid_disks;
			अवरोध;
		हाल ALGORITHM_PARITY_0:
			pd_idx = 0;
			(*dd_idx)++;
			अवरोध;
		हाल ALGORITHM_PARITY_N:
			pd_idx = data_disks;
			अवरोध;
		शेष:
			BUG();
		पूर्ण
		अवरोध;
	हाल 6:

		चयन (algorithm) अणु
		हाल ALGORITHM_LEFT_ASYMMETRIC:
			pd_idx = raid_disks - 1 - sector_भाग(stripe2, raid_disks);
			qd_idx = pd_idx + 1;
			अगर (pd_idx == raid_disks-1) अणु
				(*dd_idx)++;	/* Q D D D P */
				qd_idx = 0;
			पूर्ण अन्यथा अगर (*dd_idx >= pd_idx)
				(*dd_idx) += 2; /* D D P Q D */
			अवरोध;
		हाल ALGORITHM_RIGHT_ASYMMETRIC:
			pd_idx = sector_भाग(stripe2, raid_disks);
			qd_idx = pd_idx + 1;
			अगर (pd_idx == raid_disks-1) अणु
				(*dd_idx)++;	/* Q D D D P */
				qd_idx = 0;
			पूर्ण अन्यथा अगर (*dd_idx >= pd_idx)
				(*dd_idx) += 2; /* D D P Q D */
			अवरोध;
		हाल ALGORITHM_LEFT_SYMMETRIC:
			pd_idx = raid_disks - 1 - sector_भाग(stripe2, raid_disks);
			qd_idx = (pd_idx + 1) % raid_disks;
			*dd_idx = (pd_idx + 2 + *dd_idx) % raid_disks;
			अवरोध;
		हाल ALGORITHM_RIGHT_SYMMETRIC:
			pd_idx = sector_भाग(stripe2, raid_disks);
			qd_idx = (pd_idx + 1) % raid_disks;
			*dd_idx = (pd_idx + 2 + *dd_idx) % raid_disks;
			अवरोध;

		हाल ALGORITHM_PARITY_0:
			pd_idx = 0;
			qd_idx = 1;
			(*dd_idx) += 2;
			अवरोध;
		हाल ALGORITHM_PARITY_N:
			pd_idx = data_disks;
			qd_idx = data_disks + 1;
			अवरोध;

		हाल ALGORITHM_ROTATING_ZERO_RESTART:
			/* Exactly the same as RIGHT_ASYMMETRIC, but or
			 * of blocks क्रम computing Q is dअगरferent.
			 */
			pd_idx = sector_भाग(stripe2, raid_disks);
			qd_idx = pd_idx + 1;
			अगर (pd_idx == raid_disks-1) अणु
				(*dd_idx)++;	/* Q D D D P */
				qd_idx = 0;
			पूर्ण अन्यथा अगर (*dd_idx >= pd_idx)
				(*dd_idx) += 2; /* D D P Q D */
			ddf_layout = 1;
			अवरोध;

		हाल ALGORITHM_ROTATING_N_RESTART:
			/* Same a left_asymmetric, by first stripe is
			 * D D D P Q  rather than
			 * Q D D D P
			 */
			stripe2 += 1;
			pd_idx = raid_disks - 1 - sector_भाग(stripe2, raid_disks);
			qd_idx = pd_idx + 1;
			अगर (pd_idx == raid_disks-1) अणु
				(*dd_idx)++;	/* Q D D D P */
				qd_idx = 0;
			पूर्ण अन्यथा अगर (*dd_idx >= pd_idx)
				(*dd_idx) += 2; /* D D P Q D */
			ddf_layout = 1;
			अवरोध;

		हाल ALGORITHM_ROTATING_N_CONTINUE:
			/* Same as left_symmetric but Q is beक्रमe P */
			pd_idx = raid_disks - 1 - sector_भाग(stripe2, raid_disks);
			qd_idx = (pd_idx + raid_disks - 1) % raid_disks;
			*dd_idx = (pd_idx + 1 + *dd_idx) % raid_disks;
			ddf_layout = 1;
			अवरोध;

		हाल ALGORITHM_LEFT_ASYMMETRIC_6:
			/* RAID5 left_asymmetric, with Q on last device */
			pd_idx = data_disks - sector_भाग(stripe2, raid_disks-1);
			अगर (*dd_idx >= pd_idx)
				(*dd_idx)++;
			qd_idx = raid_disks - 1;
			अवरोध;

		हाल ALGORITHM_RIGHT_ASYMMETRIC_6:
			pd_idx = sector_भाग(stripe2, raid_disks-1);
			अगर (*dd_idx >= pd_idx)
				(*dd_idx)++;
			qd_idx = raid_disks - 1;
			अवरोध;

		हाल ALGORITHM_LEFT_SYMMETRIC_6:
			pd_idx = data_disks - sector_भाग(stripe2, raid_disks-1);
			*dd_idx = (pd_idx + 1 + *dd_idx) % (raid_disks-1);
			qd_idx = raid_disks - 1;
			अवरोध;

		हाल ALGORITHM_RIGHT_SYMMETRIC_6:
			pd_idx = sector_भाग(stripe2, raid_disks-1);
			*dd_idx = (pd_idx + 1 + *dd_idx) % (raid_disks-1);
			qd_idx = raid_disks - 1;
			अवरोध;

		हाल ALGORITHM_PARITY_0_6:
			pd_idx = 0;
			(*dd_idx)++;
			qd_idx = raid_disks - 1;
			अवरोध;

		शेष:
			BUG();
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (sh) अणु
		sh->pd_idx = pd_idx;
		sh->qd_idx = qd_idx;
		sh->ddf_layout = ddf_layout;
	पूर्ण
	/*
	 * Finally, compute the new sector number
	 */
	new_sector = (sector_t)stripe * sectors_per_chunk + chunk_offset;
	वापस new_sector;
पूर्ण

sector_t raid5_compute_blocknr(काष्ठा stripe_head *sh, पूर्णांक i, पूर्णांक previous)
अणु
	काष्ठा r5conf *conf = sh->raid_conf;
	पूर्णांक raid_disks = sh->disks;
	पूर्णांक data_disks = raid_disks - conf->max_degraded;
	sector_t new_sector = sh->sector, check;
	पूर्णांक sectors_per_chunk = previous ? conf->prev_chunk_sectors
					 : conf->chunk_sectors;
	पूर्णांक algorithm = previous ? conf->prev_algo
				 : conf->algorithm;
	sector_t stripe;
	पूर्णांक chunk_offset;
	sector_t chunk_number;
	पूर्णांक dummy1, dd_idx = i;
	sector_t r_sector;
	काष्ठा stripe_head sh2;

	chunk_offset = sector_भाग(new_sector, sectors_per_chunk);
	stripe = new_sector;

	अगर (i == sh->pd_idx)
		वापस 0;
	चयन(conf->level) अणु
	हाल 4: अवरोध;
	हाल 5:
		चयन (algorithm) अणु
		हाल ALGORITHM_LEFT_ASYMMETRIC:
		हाल ALGORITHM_RIGHT_ASYMMETRIC:
			अगर (i > sh->pd_idx)
				i--;
			अवरोध;
		हाल ALGORITHM_LEFT_SYMMETRIC:
		हाल ALGORITHM_RIGHT_SYMMETRIC:
			अगर (i < sh->pd_idx)
				i += raid_disks;
			i -= (sh->pd_idx + 1);
			अवरोध;
		हाल ALGORITHM_PARITY_0:
			i -= 1;
			अवरोध;
		हाल ALGORITHM_PARITY_N:
			अवरोध;
		शेष:
			BUG();
		पूर्ण
		अवरोध;
	हाल 6:
		अगर (i == sh->qd_idx)
			वापस 0; /* It is the Q disk */
		चयन (algorithm) अणु
		हाल ALGORITHM_LEFT_ASYMMETRIC:
		हाल ALGORITHM_RIGHT_ASYMMETRIC:
		हाल ALGORITHM_ROTATING_ZERO_RESTART:
		हाल ALGORITHM_ROTATING_N_RESTART:
			अगर (sh->pd_idx == raid_disks-1)
				i--;	/* Q D D D P */
			अन्यथा अगर (i > sh->pd_idx)
				i -= 2; /* D D P Q D */
			अवरोध;
		हाल ALGORITHM_LEFT_SYMMETRIC:
		हाल ALGORITHM_RIGHT_SYMMETRIC:
			अगर (sh->pd_idx == raid_disks-1)
				i--; /* Q D D D P */
			अन्यथा अणु
				/* D D P Q D */
				अगर (i < sh->pd_idx)
					i += raid_disks;
				i -= (sh->pd_idx + 2);
			पूर्ण
			अवरोध;
		हाल ALGORITHM_PARITY_0:
			i -= 2;
			अवरोध;
		हाल ALGORITHM_PARITY_N:
			अवरोध;
		हाल ALGORITHM_ROTATING_N_CONTINUE:
			/* Like left_symmetric, but P is beक्रमe Q */
			अगर (sh->pd_idx == 0)
				i--;	/* P D D D Q */
			अन्यथा अणु
				/* D D Q P D */
				अगर (i < sh->pd_idx)
					i += raid_disks;
				i -= (sh->pd_idx + 1);
			पूर्ण
			अवरोध;
		हाल ALGORITHM_LEFT_ASYMMETRIC_6:
		हाल ALGORITHM_RIGHT_ASYMMETRIC_6:
			अगर (i > sh->pd_idx)
				i--;
			अवरोध;
		हाल ALGORITHM_LEFT_SYMMETRIC_6:
		हाल ALGORITHM_RIGHT_SYMMETRIC_6:
			अगर (i < sh->pd_idx)
				i += data_disks + 1;
			i -= (sh->pd_idx + 1);
			अवरोध;
		हाल ALGORITHM_PARITY_0_6:
			i -= 1;
			अवरोध;
		शेष:
			BUG();
		पूर्ण
		अवरोध;
	पूर्ण

	chunk_number = stripe * data_disks + i;
	r_sector = chunk_number * sectors_per_chunk + chunk_offset;

	check = raid5_compute_sector(conf, r_sector,
				     previous, &dummy1, &sh2);
	अगर (check != sh->sector || dummy1 != dd_idx || sh2.pd_idx != sh->pd_idx
		|| sh2.qd_idx != sh->qd_idx) अणु
		pr_warn("md/raid:%s: compute_blocknr: map not correct\n",
			mdname(conf->mddev));
		वापस 0;
	पूर्ण
	वापस r_sector;
पूर्ण

/*
 * There are हालs where we want handle_stripe_dirtying() and
 * schedule_reस्थिरruction() to delay toग_लिखो to some dev of a stripe.
 *
 * This function checks whether we want to delay the toग_लिखो. Specअगरically,
 * we delay the toग_लिखो when:
 *
 *   1. degraded stripe has a non-overग_लिखो to the missing dev, AND this
 *      stripe has data in journal (क्रम other devices).
 *
 *      In this हाल, when पढ़ोing data क्रम the non-overग_लिखो dev, it is
 *      necessary to handle complex rmw of ग_लिखो back cache (prexor with
 *      orig_page, and xor with page). To keep पढ़ो path simple, we would
 *      like to flush data in journal to RAID disks first, so complex rmw
 *      is handled in the ग_लिखो patch (handle_stripe_dirtying).
 *
 *   2. when journal space is critical (R5C_LOG_CRITICAL=1)
 *
 *      It is important to be able to flush all stripes in raid5-cache.
 *      Thereक्रमe, we need reserve some space on the journal device क्रम
 *      these flushes. If flush operation includes pending ग_लिखोs to the
 *      stripe, we need to reserve (conf->raid_disk + 1) pages per stripe
 *      क्रम the flush out. If we exclude these pending ग_लिखोs from flush
 *      operation, we only need (conf->max_degraded + 1) pages per stripe.
 *      Thereक्रमe, excluding pending ग_लिखोs in these हालs enables more
 *      efficient use of the journal device.
 *
 *      Note: To make sure the stripe makes progress, we only delay
 *      toग_लिखो क्रम stripes with data alपढ़ोy in journal (injournal > 0).
 *      When LOG_CRITICAL, stripes with injournal == 0 will be sent to
 *      no_space_stripes list.
 *
 *   3. during journal failure
 *      In journal failure, we try to flush all cached data to raid disks
 *      based on data in stripe cache. The array is पढ़ो-only to upper
 *      layers, so we would skip all pending ग_लिखोs.
 *
 */
अटल अंतरभूत bool delay_toग_लिखो(काष्ठा r5conf *conf,
				 काष्ठा r5dev *dev,
				 काष्ठा stripe_head_state *s)
अणु
	/* हाल 1 above */
	अगर (!test_bit(R5_OVERWRITE, &dev->flags) &&
	    !test_bit(R5_Insync, &dev->flags) && s->injournal)
		वापस true;
	/* हाल 2 above */
	अगर (test_bit(R5C_LOG_CRITICAL, &conf->cache_state) &&
	    s->injournal > 0)
		वापस true;
	/* हाल 3 above */
	अगर (s->log_failed && s->injournal)
		वापस true;
	वापस false;
पूर्ण

अटल व्योम
schedule_reस्थिरruction(काष्ठा stripe_head *sh, काष्ठा stripe_head_state *s,
			 पूर्णांक rcw, पूर्णांक expand)
अणु
	पूर्णांक i, pd_idx = sh->pd_idx, qd_idx = sh->qd_idx, disks = sh->disks;
	काष्ठा r5conf *conf = sh->raid_conf;
	पूर्णांक level = conf->level;

	अगर (rcw) अणु
		/*
		 * In some हालs, handle_stripe_dirtying initially decided to
		 * run rmw and allocates extra page क्रम prexor. However, rcw is
		 * cheaper later on. We need to मुक्त the extra page now,
		 * because we won't be able to करो that in ops_complete_prexor().
		 */
		r5c_release_extra_page(sh);

		क्रम (i = disks; i--; ) अणु
			काष्ठा r5dev *dev = &sh->dev[i];

			अगर (dev->toग_लिखो && !delay_toग_लिखो(conf, dev, s)) अणु
				set_bit(R5_LOCKED, &dev->flags);
				set_bit(R5_Wantdrain, &dev->flags);
				अगर (!expand)
					clear_bit(R5_UPTODATE, &dev->flags);
				s->locked++;
			पूर्ण अन्यथा अगर (test_bit(R5_InJournal, &dev->flags)) अणु
				set_bit(R5_LOCKED, &dev->flags);
				s->locked++;
			पूर्ण
		पूर्ण
		/* अगर we are not expanding this is a proper ग_लिखो request, and
		 * there will be bios with new data to be drained पूर्णांकo the
		 * stripe cache
		 */
		अगर (!expand) अणु
			अगर (!s->locked)
				/* False alarm, nothing to करो */
				वापस;
			sh->reस्थिरruct_state = reस्थिरruct_state_drain_run;
			set_bit(STRIPE_OP_BIODRAIN, &s->ops_request);
		पूर्ण अन्यथा
			sh->reस्थिरruct_state = reस्थिरruct_state_run;

		set_bit(STRIPE_OP_RECONSTRUCT, &s->ops_request);

		अगर (s->locked + conf->max_degraded == disks)
			अगर (!test_and_set_bit(STRIPE_FULL_WRITE, &sh->state))
				atomic_inc(&conf->pending_full_ग_लिखोs);
	पूर्ण अन्यथा अणु
		BUG_ON(!(test_bit(R5_UPTODATE, &sh->dev[pd_idx].flags) ||
			test_bit(R5_Wantcompute, &sh->dev[pd_idx].flags)));
		BUG_ON(level == 6 &&
			(!(test_bit(R5_UPTODATE, &sh->dev[qd_idx].flags) ||
			   test_bit(R5_Wantcompute, &sh->dev[qd_idx].flags))));

		क्रम (i = disks; i--; ) अणु
			काष्ठा r5dev *dev = &sh->dev[i];
			अगर (i == pd_idx || i == qd_idx)
				जारी;

			अगर (dev->toग_लिखो &&
			    (test_bit(R5_UPTODATE, &dev->flags) ||
			     test_bit(R5_Wantcompute, &dev->flags))) अणु
				set_bit(R5_Wantdrain, &dev->flags);
				set_bit(R5_LOCKED, &dev->flags);
				clear_bit(R5_UPTODATE, &dev->flags);
				s->locked++;
			पूर्ण अन्यथा अगर (test_bit(R5_InJournal, &dev->flags)) अणु
				set_bit(R5_LOCKED, &dev->flags);
				s->locked++;
			पूर्ण
		पूर्ण
		अगर (!s->locked)
			/* False alarm - nothing to करो */
			वापस;
		sh->reस्थिरruct_state = reस्थिरruct_state_prexor_drain_run;
		set_bit(STRIPE_OP_PREXOR, &s->ops_request);
		set_bit(STRIPE_OP_BIODRAIN, &s->ops_request);
		set_bit(STRIPE_OP_RECONSTRUCT, &s->ops_request);
	पूर्ण

	/* keep the parity disk(s) locked जबतक asynchronous operations
	 * are in flight
	 */
	set_bit(R5_LOCKED, &sh->dev[pd_idx].flags);
	clear_bit(R5_UPTODATE, &sh->dev[pd_idx].flags);
	s->locked++;

	अगर (level == 6) अणु
		पूर्णांक qd_idx = sh->qd_idx;
		काष्ठा r5dev *dev = &sh->dev[qd_idx];

		set_bit(R5_LOCKED, &dev->flags);
		clear_bit(R5_UPTODATE, &dev->flags);
		s->locked++;
	पूर्ण

	अगर (raid5_has_ppl(sh->raid_conf) && sh->ppl_page &&
	    test_bit(STRIPE_OP_BIODRAIN, &s->ops_request) &&
	    !test_bit(STRIPE_FULL_WRITE, &sh->state) &&
	    test_bit(R5_Insync, &sh->dev[pd_idx].flags))
		set_bit(STRIPE_OP_PARTIAL_PARITY, &s->ops_request);

	pr_debug("%s: stripe %llu locked: %d ops_request: %lx\n",
		__func__, (अचिन्हित दीर्घ दीर्घ)sh->sector,
		s->locked, s->ops_request);
पूर्ण

/*
 * Each stripe/dev can have one or more bion attached.
 * toपढ़ो/toग_लिखो poपूर्णांक to the first in a chain.
 * The bi_next chain must be in order.
 */
अटल पूर्णांक add_stripe_bio(काष्ठा stripe_head *sh, काष्ठा bio *bi, पूर्णांक dd_idx,
			  पूर्णांक क्रमग_लिखो, पूर्णांक previous)
अणु
	काष्ठा bio **bip;
	काष्ठा r5conf *conf = sh->raid_conf;
	पूर्णांक firstग_लिखो=0;

	pr_debug("adding bi b#%llu to stripe s#%llu\n",
		(अचिन्हित दीर्घ दीर्घ)bi->bi_iter.bi_sector,
		(अचिन्हित दीर्घ दीर्घ)sh->sector);

	spin_lock_irq(&sh->stripe_lock);
	sh->dev[dd_idx].ग_लिखो_hपूर्णांक = bi->bi_ग_लिखो_hपूर्णांक;
	/* Don't allow new IO added to stripes in batch list */
	अगर (sh->batch_head)
		जाओ overlap;
	अगर (क्रमग_लिखो) अणु
		bip = &sh->dev[dd_idx].toग_लिखो;
		अगर (*bip == शून्य)
			firstग_लिखो = 1;
	पूर्ण अन्यथा
		bip = &sh->dev[dd_idx].toपढ़ो;
	जबतक (*bip && (*bip)->bi_iter.bi_sector < bi->bi_iter.bi_sector) अणु
		अगर (bio_end_sector(*bip) > bi->bi_iter.bi_sector)
			जाओ overlap;
		bip = & (*bip)->bi_next;
	पूर्ण
	अगर (*bip && (*bip)->bi_iter.bi_sector < bio_end_sector(bi))
		जाओ overlap;

	अगर (क्रमग_लिखो && raid5_has_ppl(conf)) अणु
		/*
		 * With PPL only ग_लिखोs to consecutive data chunks within a
		 * stripe are allowed because क्रम a single stripe_head we can
		 * only have one PPL entry at a समय, which describes one data
		 * range. Not really an overlap, but रुको_क्रम_overlap can be
		 * used to handle this.
		 */
		sector_t sector;
		sector_t first = 0;
		sector_t last = 0;
		पूर्णांक count = 0;
		पूर्णांक i;

		क्रम (i = 0; i < sh->disks; i++) अणु
			अगर (i != sh->pd_idx &&
			    (i == dd_idx || sh->dev[i].toग_लिखो)) अणु
				sector = sh->dev[i].sector;
				अगर (count == 0 || sector < first)
					first = sector;
				अगर (sector > last)
					last = sector;
				count++;
			पूर्ण
		पूर्ण

		अगर (first + conf->chunk_sectors * (count - 1) != last)
			जाओ overlap;
	पूर्ण

	अगर (!क्रमग_लिखो || previous)
		clear_bit(STRIPE_BATCH_READY, &sh->state);

	BUG_ON(*bip && bi->bi_next && (*bip) != bi->bi_next);
	अगर (*bip)
		bi->bi_next = *bip;
	*bip = bi;
	bio_inc_reमुख्यing(bi);
	md_ग_लिखो_inc(conf->mddev, bi);

	अगर (क्रमग_लिखो) अणु
		/* check अगर page is covered */
		sector_t sector = sh->dev[dd_idx].sector;
		क्रम (bi=sh->dev[dd_idx].toग_लिखो;
		     sector < sh->dev[dd_idx].sector + RAID5_STRIPE_SECTORS(conf) &&
			     bi && bi->bi_iter.bi_sector <= sector;
		     bi = r5_next_bio(conf, bi, sh->dev[dd_idx].sector)) अणु
			अगर (bio_end_sector(bi) >= sector)
				sector = bio_end_sector(bi);
		पूर्ण
		अगर (sector >= sh->dev[dd_idx].sector + RAID5_STRIPE_SECTORS(conf))
			अगर (!test_and_set_bit(R5_OVERWRITE, &sh->dev[dd_idx].flags))
				sh->overग_लिखो_disks++;
	पूर्ण

	pr_debug("added bi b#%llu to stripe s#%llu, disk %d.\n",
		(अचिन्हित दीर्घ दीर्घ)(*bip)->bi_iter.bi_sector,
		(अचिन्हित दीर्घ दीर्घ)sh->sector, dd_idx);

	अगर (conf->mddev->biपंचांगap && firstग_लिखो) अणु
		/* Cannot hold spinlock over biपंचांगap_startग_लिखो,
		 * but must ensure this isn't added to a batch until
		 * we have added to the biपंचांगap and set bm_seq.
		 * So set STRIPE_BITMAP_PENDING to prevent
		 * batching.
		 * If multiple add_stripe_bio() calls race here they
		 * much all set STRIPE_BITMAP_PENDING.  So only the first one
		 * to complete "bitmap_startwrite" माला_लो to set
		 * STRIPE_BIT_DELAY.  This is important as once a stripe
		 * is added to a batch, STRIPE_BIT_DELAY cannot be changed
		 * any more.
		 */
		set_bit(STRIPE_BITMAP_PENDING, &sh->state);
		spin_unlock_irq(&sh->stripe_lock);
		md_biपंचांगap_startग_लिखो(conf->mddev->biपंचांगap, sh->sector,
				     RAID5_STRIPE_SECTORS(conf), 0);
		spin_lock_irq(&sh->stripe_lock);
		clear_bit(STRIPE_BITMAP_PENDING, &sh->state);
		अगर (!sh->batch_head) अणु
			sh->bm_seq = conf->seq_flush+1;
			set_bit(STRIPE_BIT_DELAY, &sh->state);
		पूर्ण
	पूर्ण
	spin_unlock_irq(&sh->stripe_lock);

	अगर (stripe_can_batch(sh))
		stripe_add_to_batch_list(conf, sh);
	वापस 1;

 overlap:
	set_bit(R5_Overlap, &sh->dev[dd_idx].flags);
	spin_unlock_irq(&sh->stripe_lock);
	वापस 0;
पूर्ण

अटल व्योम end_reshape(काष्ठा r5conf *conf);

अटल व्योम stripe_set_idx(sector_t stripe, काष्ठा r5conf *conf, पूर्णांक previous,
			    काष्ठा stripe_head *sh)
अणु
	पूर्णांक sectors_per_chunk =
		previous ? conf->prev_chunk_sectors : conf->chunk_sectors;
	पूर्णांक dd_idx;
	पूर्णांक chunk_offset = sector_भाग(stripe, sectors_per_chunk);
	पूर्णांक disks = previous ? conf->previous_raid_disks : conf->raid_disks;

	raid5_compute_sector(conf,
			     stripe * (disks - conf->max_degraded)
			     *sectors_per_chunk + chunk_offset,
			     previous,
			     &dd_idx, sh);
पूर्ण

अटल व्योम
handle_failed_stripe(काष्ठा r5conf *conf, काष्ठा stripe_head *sh,
		     काष्ठा stripe_head_state *s, पूर्णांक disks)
अणु
	पूर्णांक i;
	BUG_ON(sh->batch_head);
	क्रम (i = disks; i--; ) अणु
		काष्ठा bio *bi;
		पूर्णांक biपंचांगap_end = 0;

		अगर (test_bit(R5_ReadError, &sh->dev[i].flags)) अणु
			काष्ठा md_rdev *rdev;
			rcu_पढ़ो_lock();
			rdev = rcu_dereference(conf->disks[i].rdev);
			अगर (rdev && test_bit(In_sync, &rdev->flags) &&
			    !test_bit(Faulty, &rdev->flags))
				atomic_inc(&rdev->nr_pending);
			अन्यथा
				rdev = शून्य;
			rcu_पढ़ो_unlock();
			अगर (rdev) अणु
				अगर (!rdev_set_badblocks(
					    rdev,
					    sh->sector,
					    RAID5_STRIPE_SECTORS(conf), 0))
					md_error(conf->mddev, rdev);
				rdev_dec_pending(rdev, conf->mddev);
			पूर्ण
		पूर्ण
		spin_lock_irq(&sh->stripe_lock);
		/* fail all ग_लिखोs first */
		bi = sh->dev[i].toग_लिखो;
		sh->dev[i].toग_लिखो = शून्य;
		sh->overग_लिखो_disks = 0;
		spin_unlock_irq(&sh->stripe_lock);
		अगर (bi)
			biपंचांगap_end = 1;

		log_stripe_ग_लिखो_finished(sh);

		अगर (test_and_clear_bit(R5_Overlap, &sh->dev[i].flags))
			wake_up(&conf->रुको_क्रम_overlap);

		जबतक (bi && bi->bi_iter.bi_sector <
			sh->dev[i].sector + RAID5_STRIPE_SECTORS(conf)) अणु
			काष्ठा bio *nextbi = r5_next_bio(conf, bi, sh->dev[i].sector);

			md_ग_लिखो_end(conf->mddev);
			bio_io_error(bi);
			bi = nextbi;
		पूर्ण
		अगर (biपंचांगap_end)
			md_biपंचांगap_endग_लिखो(conf->mddev->biपंचांगap, sh->sector,
					   RAID5_STRIPE_SECTORS(conf), 0, 0);
		biपंचांगap_end = 0;
		/* and fail all 'written' */
		bi = sh->dev[i].written;
		sh->dev[i].written = शून्य;
		अगर (test_and_clear_bit(R5_SkipCopy, &sh->dev[i].flags)) अणु
			WARN_ON(test_bit(R5_UPTODATE, &sh->dev[i].flags));
			sh->dev[i].page = sh->dev[i].orig_page;
		पूर्ण

		अगर (bi) biपंचांगap_end = 1;
		जबतक (bi && bi->bi_iter.bi_sector <
		       sh->dev[i].sector + RAID5_STRIPE_SECTORS(conf)) अणु
			काष्ठा bio *bi2 = r5_next_bio(conf, bi, sh->dev[i].sector);

			md_ग_लिखो_end(conf->mddev);
			bio_io_error(bi);
			bi = bi2;
		पूर्ण

		/* fail any पढ़ोs अगर this device is non-operational and
		 * the data has not reached the cache yet.
		 */
		अगर (!test_bit(R5_Wantfill, &sh->dev[i].flags) &&
		    s->failed > conf->max_degraded &&
		    (!test_bit(R5_Insync, &sh->dev[i].flags) ||
		      test_bit(R5_ReadError, &sh->dev[i].flags))) अणु
			spin_lock_irq(&sh->stripe_lock);
			bi = sh->dev[i].toपढ़ो;
			sh->dev[i].toपढ़ो = शून्य;
			spin_unlock_irq(&sh->stripe_lock);
			अगर (test_and_clear_bit(R5_Overlap, &sh->dev[i].flags))
				wake_up(&conf->रुको_क्रम_overlap);
			अगर (bi)
				s->to_पढ़ो--;
			जबतक (bi && bi->bi_iter.bi_sector <
			       sh->dev[i].sector + RAID5_STRIPE_SECTORS(conf)) अणु
				काष्ठा bio *nextbi =
					r5_next_bio(conf, bi, sh->dev[i].sector);

				bio_io_error(bi);
				bi = nextbi;
			पूर्ण
		पूर्ण
		अगर (biपंचांगap_end)
			md_biपंचांगap_endग_लिखो(conf->mddev->biपंचांगap, sh->sector,
					   RAID5_STRIPE_SECTORS(conf), 0, 0);
		/* If we were in the middle of a ग_लिखो the parity block might
		 * still be locked - so just clear all R5_LOCKED flags
		 */
		clear_bit(R5_LOCKED, &sh->dev[i].flags);
	पूर्ण
	s->to_ग_लिखो = 0;
	s->written = 0;

	अगर (test_and_clear_bit(STRIPE_FULL_WRITE, &sh->state))
		अगर (atomic_dec_and_test(&conf->pending_full_ग_लिखोs))
			md_wakeup_thपढ़ो(conf->mddev->thपढ़ो);
पूर्ण

अटल व्योम
handle_failed_sync(काष्ठा r5conf *conf, काष्ठा stripe_head *sh,
		   काष्ठा stripe_head_state *s)
अणु
	पूर्णांक पात = 0;
	पूर्णांक i;

	BUG_ON(sh->batch_head);
	clear_bit(STRIPE_SYNCING, &sh->state);
	अगर (test_and_clear_bit(R5_Overlap, &sh->dev[sh->pd_idx].flags))
		wake_up(&conf->रुको_क्रम_overlap);
	s->syncing = 0;
	s->replacing = 0;
	/* There is nothing more to करो क्रम sync/check/repair.
	 * Don't even need to पात as that is handled अन्यथाwhere
	 * अगर needed, and not always wanted e.g. अगर there is a known
	 * bad block here.
	 * For recover/replace we need to record a bad block on all
	 * non-sync devices, or पात the recovery
	 */
	अगर (test_bit(MD_RECOVERY_RECOVER, &conf->mddev->recovery)) अणु
		/* During recovery devices cannot be हटाओd, so
		 * locking and refcounting of rdevs is not needed
		 */
		rcu_पढ़ो_lock();
		क्रम (i = 0; i < conf->raid_disks; i++) अणु
			काष्ठा md_rdev *rdev = rcu_dereference(conf->disks[i].rdev);
			अगर (rdev
			    && !test_bit(Faulty, &rdev->flags)
			    && !test_bit(In_sync, &rdev->flags)
			    && !rdev_set_badblocks(rdev, sh->sector,
						   RAID5_STRIPE_SECTORS(conf), 0))
				पात = 1;
			rdev = rcu_dereference(conf->disks[i].replacement);
			अगर (rdev
			    && !test_bit(Faulty, &rdev->flags)
			    && !test_bit(In_sync, &rdev->flags)
			    && !rdev_set_badblocks(rdev, sh->sector,
						   RAID5_STRIPE_SECTORS(conf), 0))
				पात = 1;
		पूर्ण
		rcu_पढ़ो_unlock();
		अगर (पात)
			conf->recovery_disabled =
				conf->mddev->recovery_disabled;
	पूर्ण
	md_करोne_sync(conf->mddev, RAID5_STRIPE_SECTORS(conf), !पात);
पूर्ण

अटल पूर्णांक want_replace(काष्ठा stripe_head *sh, पूर्णांक disk_idx)
अणु
	काष्ठा md_rdev *rdev;
	पूर्णांक rv = 0;

	rcu_पढ़ो_lock();
	rdev = rcu_dereference(sh->raid_conf->disks[disk_idx].replacement);
	अगर (rdev
	    && !test_bit(Faulty, &rdev->flags)
	    && !test_bit(In_sync, &rdev->flags)
	    && (rdev->recovery_offset <= sh->sector
		|| rdev->mddev->recovery_cp <= sh->sector))
		rv = 1;
	rcu_पढ़ो_unlock();
	वापस rv;
पूर्ण

अटल पूर्णांक need_this_block(काष्ठा stripe_head *sh, काष्ठा stripe_head_state *s,
			   पूर्णांक disk_idx, पूर्णांक disks)
अणु
	काष्ठा r5dev *dev = &sh->dev[disk_idx];
	काष्ठा r5dev *fdev[2] = अणु &sh->dev[s->failed_num[0]],
				  &sh->dev[s->failed_num[1]] पूर्ण;
	पूर्णांक i;
	bool क्रमce_rcw = (sh->raid_conf->rmw_level == PARITY_DISABLE_RMW);


	अगर (test_bit(R5_LOCKED, &dev->flags) ||
	    test_bit(R5_UPTODATE, &dev->flags))
		/* No poपूर्णांक पढ़ोing this as we alपढ़ोy have it or have
		 * decided to get it.
		 */
		वापस 0;

	अगर (dev->toपढ़ो ||
	    (dev->toग_लिखो && !test_bit(R5_OVERWRITE, &dev->flags)))
		/* We need this block to directly satisfy a request */
		वापस 1;

	अगर (s->syncing || s->expanding ||
	    (s->replacing && want_replace(sh, disk_idx)))
		/* When syncing, or expanding we पढ़ो everything.
		 * When replacing, we need the replaced block.
		 */
		वापस 1;

	अगर ((s->failed >= 1 && fdev[0]->toपढ़ो) ||
	    (s->failed >= 2 && fdev[1]->toपढ़ो))
		/* If we want to पढ़ो from a failed device, then
		 * we need to actually पढ़ो every other device.
		 */
		वापस 1;

	/* Someबार neither पढ़ो-modअगरy-ग_लिखो nor reस्थिरruct-ग_लिखो
	 * cycles can work.  In those हालs we पढ़ो every block we
	 * can.  Then the parity-update is certain to have enough to
	 * work with.
	 * This can only be a problem when we need to ग_लिखो something,
	 * and some device has failed.  If either of those tests
	 * fail we need look no further.
	 */
	अगर (!s->failed || !s->to_ग_लिखो)
		वापस 0;

	अगर (test_bit(R5_Insync, &dev->flags) &&
	    !test_bit(STRIPE_PREREAD_ACTIVE, &sh->state))
		/* Pre-पढ़ोs at not permitted until after लघु delay
		 * to gather multiple requests.  However अगर this
		 * device is no Insync, the block could only be computed
		 * and there is no need to delay that.
		 */
		वापस 0;

	क्रम (i = 0; i < s->failed && i < 2; i++) अणु
		अगर (fdev[i]->toग_लिखो &&
		    !test_bit(R5_UPTODATE, &fdev[i]->flags) &&
		    !test_bit(R5_OVERWRITE, &fdev[i]->flags))
			/* If we have a partial ग_लिखो to a failed
			 * device, then we will need to reस्थिरruct
			 * the content of that device, so all other
			 * devices must be पढ़ो.
			 */
			वापस 1;

		अगर (s->failed >= 2 &&
		    (fdev[i]->toग_लिखो ||
		     s->failed_num[i] == sh->pd_idx ||
		     s->failed_num[i] == sh->qd_idx) &&
		    !test_bit(R5_UPTODATE, &fdev[i]->flags))
			/* In max degraded raid6, If the failed disk is P, Q,
			 * or we want to पढ़ो the failed disk, we need to करो
			 * reस्थिरruct-ग_लिखो.
			 */
			क्रमce_rcw = true;
	पूर्ण

	/* If we are क्रमced to करो a reस्थिरruct-ग_लिखो, because parity
	 * cannot be trusted and we are currently recovering it, there
	 * is extra need to be careful.
	 * If one of the devices that we would need to पढ़ो, because
	 * it is not being overwritten (and maybe not written at all)
	 * is missing/faulty, then we need to पढ़ो everything we can.
	 */
	अगर (!क्रमce_rcw &&
	    sh->sector < sh->raid_conf->mddev->recovery_cp)
		/* reस्थिरruct-ग_लिखो isn't being क्रमced */
		वापस 0;
	क्रम (i = 0; i < s->failed && i < 2; i++) अणु
		अगर (s->failed_num[i] != sh->pd_idx &&
		    s->failed_num[i] != sh->qd_idx &&
		    !test_bit(R5_UPTODATE, &fdev[i]->flags) &&
		    !test_bit(R5_OVERWRITE, &fdev[i]->flags))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/* fetch_block - checks the given member device to see अगर its data needs
 * to be पढ़ो or computed to satisfy a request.
 *
 * Returns 1 when no more member devices need to be checked, otherwise वापसs
 * 0 to tell the loop in handle_stripe_fill to जारी
 */
अटल पूर्णांक fetch_block(काष्ठा stripe_head *sh, काष्ठा stripe_head_state *s,
		       पूर्णांक disk_idx, पूर्णांक disks)
अणु
	काष्ठा r5dev *dev = &sh->dev[disk_idx];

	/* is the data in this block needed, and can we get it? */
	अगर (need_this_block(sh, s, disk_idx, disks)) अणु
		/* we would like to get this block, possibly by computing it,
		 * otherwise पढ़ो it अगर the backing disk is insync
		 */
		BUG_ON(test_bit(R5_Wantcompute, &dev->flags));
		BUG_ON(test_bit(R5_Wantपढ़ो, &dev->flags));
		BUG_ON(sh->batch_head);

		/*
		 * In the raid6 हाल अगर the only non-uptodate disk is P
		 * then we alपढ़ोy trusted P to compute the other failed
		 * drives. It is safe to compute rather than re-पढ़ो P.
		 * In other हालs we only compute blocks from failed
		 * devices, otherwise check/repair might fail to detect
		 * a real inconsistency.
		 */

		अगर ((s->uptodate == disks - 1) &&
		    ((sh->qd_idx >= 0 && sh->pd_idx == disk_idx) ||
		    (s->failed && (disk_idx == s->failed_num[0] ||
				   disk_idx == s->failed_num[1])))) अणु
			/* have disk failed, and we're requested to fetch it;
			 * करो compute it
			 */
			pr_debug("Computing stripe %llu block %d\n",
			       (अचिन्हित दीर्घ दीर्घ)sh->sector, disk_idx);
			set_bit(STRIPE_COMPUTE_RUN, &sh->state);
			set_bit(STRIPE_OP_COMPUTE_BLK, &s->ops_request);
			set_bit(R5_Wantcompute, &dev->flags);
			sh->ops.target = disk_idx;
			sh->ops.target2 = -1; /* no 2nd target */
			s->req_compute = 1;
			/* Careful: from this poपूर्णांक on 'uptodate' is in the eye
			 * of raid_run_ops which services 'compute' operations
			 * beक्रमe ग_लिखोs. R5_Wantcompute flags a block that will
			 * be R5_UPTODATE by the समय it is needed क्रम a
			 * subsequent operation.
			 */
			s->uptodate++;
			वापस 1;
		पूर्ण अन्यथा अगर (s->uptodate == disks-2 && s->failed >= 2) अणु
			/* Computing 2-failure is *very* expensive; only
			 * करो it अगर failed >= 2
			 */
			पूर्णांक other;
			क्रम (other = disks; other--; ) अणु
				अगर (other == disk_idx)
					जारी;
				अगर (!test_bit(R5_UPTODATE,
				      &sh->dev[other].flags))
					अवरोध;
			पूर्ण
			BUG_ON(other < 0);
			pr_debug("Computing stripe %llu blocks %d,%d\n",
			       (अचिन्हित दीर्घ दीर्घ)sh->sector,
			       disk_idx, other);
			set_bit(STRIPE_COMPUTE_RUN, &sh->state);
			set_bit(STRIPE_OP_COMPUTE_BLK, &s->ops_request);
			set_bit(R5_Wantcompute, &sh->dev[disk_idx].flags);
			set_bit(R5_Wantcompute, &sh->dev[other].flags);
			sh->ops.target = disk_idx;
			sh->ops.target2 = other;
			s->uptodate += 2;
			s->req_compute = 1;
			वापस 1;
		पूर्ण अन्यथा अगर (test_bit(R5_Insync, &dev->flags)) अणु
			set_bit(R5_LOCKED, &dev->flags);
			set_bit(R5_Wantपढ़ो, &dev->flags);
			s->locked++;
			pr_debug("Reading block %d (sync=%d)\n",
				disk_idx, s->syncing);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * handle_stripe_fill - पढ़ो or compute data to satisfy pending requests.
 */
अटल व्योम handle_stripe_fill(काष्ठा stripe_head *sh,
			       काष्ठा stripe_head_state *s,
			       पूर्णांक disks)
अणु
	पूर्णांक i;

	/* look क्रम blocks to पढ़ो/compute, skip this अगर a compute
	 * is alपढ़ोy in flight, or अगर the stripe contents are in the
	 * midst of changing due to a ग_लिखो
	 */
	अगर (!test_bit(STRIPE_COMPUTE_RUN, &sh->state) && !sh->check_state &&
	    !sh->reस्थिरruct_state) अणु

		/*
		 * For degraded stripe with data in journal, करो not handle
		 * पढ़ो requests yet, instead, flush the stripe to raid
		 * disks first, this aव्योमs handling complex rmw of ग_लिखो
		 * back cache (prexor with orig_page, and then xor with
		 * page) in the पढ़ो path
		 */
		अगर (s->injournal && s->failed) अणु
			अगर (test_bit(STRIPE_R5C_CACHING, &sh->state))
				r5c_make_stripe_ग_लिखो_out(sh);
			जाओ out;
		पूर्ण

		क्रम (i = disks; i--; )
			अगर (fetch_block(sh, s, i, disks))
				अवरोध;
	पूर्ण
out:
	set_bit(STRIPE_HANDLE, &sh->state);
पूर्ण

अटल व्योम अवरोध_stripe_batch_list(काष्ठा stripe_head *head_sh,
				    अचिन्हित दीर्घ handle_flags);
/* handle_stripe_clean_event
 * any written block on an uptodate or failed drive can be वापसed.
 * Note that अगर we 'wrote' to a failed drive, it will be UPTODATE, but
 * never LOCKED, so we करोn't need to test 'failed' directly.
 */
अटल व्योम handle_stripe_clean_event(काष्ठा r5conf *conf,
	काष्ठा stripe_head *sh, पूर्णांक disks)
अणु
	पूर्णांक i;
	काष्ठा r5dev *dev;
	पूर्णांक discard_pending = 0;
	काष्ठा stripe_head *head_sh = sh;
	bool करो_endio = false;

	क्रम (i = disks; i--; )
		अगर (sh->dev[i].written) अणु
			dev = &sh->dev[i];
			अगर (!test_bit(R5_LOCKED, &dev->flags) &&
			    (test_bit(R5_UPTODATE, &dev->flags) ||
			     test_bit(R5_Discard, &dev->flags) ||
			     test_bit(R5_SkipCopy, &dev->flags))) अणु
				/* We can वापस any ग_लिखो requests */
				काष्ठा bio *wbi, *wbi2;
				pr_debug("Return write for disc %d\n", i);
				अगर (test_and_clear_bit(R5_Discard, &dev->flags))
					clear_bit(R5_UPTODATE, &dev->flags);
				अगर (test_and_clear_bit(R5_SkipCopy, &dev->flags)) अणु
					WARN_ON(test_bit(R5_UPTODATE, &dev->flags));
				पूर्ण
				करो_endio = true;

वापसbi:
				dev->page = dev->orig_page;
				wbi = dev->written;
				dev->written = शून्य;
				जबतक (wbi && wbi->bi_iter.bi_sector <
					dev->sector + RAID5_STRIPE_SECTORS(conf)) अणु
					wbi2 = r5_next_bio(conf, wbi, dev->sector);
					md_ग_लिखो_end(conf->mddev);
					bio_endio(wbi);
					wbi = wbi2;
				पूर्ण
				md_biपंचांगap_endग_लिखो(conf->mddev->biपंचांगap, sh->sector,
						   RAID5_STRIPE_SECTORS(conf),
						   !test_bit(STRIPE_DEGRADED, &sh->state),
						   0);
				अगर (head_sh->batch_head) अणु
					sh = list_first_entry(&sh->batch_list,
							      काष्ठा stripe_head,
							      batch_list);
					अगर (sh != head_sh) अणु
						dev = &sh->dev[i];
						जाओ वापसbi;
					पूर्ण
				पूर्ण
				sh = head_sh;
				dev = &sh->dev[i];
			पूर्ण अन्यथा अगर (test_bit(R5_Discard, &dev->flags))
				discard_pending = 1;
		पूर्ण

	log_stripe_ग_लिखो_finished(sh);

	अगर (!discard_pending &&
	    test_bit(R5_Discard, &sh->dev[sh->pd_idx].flags)) अणु
		पूर्णांक hash;
		clear_bit(R5_Discard, &sh->dev[sh->pd_idx].flags);
		clear_bit(R5_UPTODATE, &sh->dev[sh->pd_idx].flags);
		अगर (sh->qd_idx >= 0) अणु
			clear_bit(R5_Discard, &sh->dev[sh->qd_idx].flags);
			clear_bit(R5_UPTODATE, &sh->dev[sh->qd_idx].flags);
		पूर्ण
		/* now that discard is करोne we can proceed with any sync */
		clear_bit(STRIPE_DISCARD, &sh->state);
		/*
		 * SCSI discard will change some bio fields and the stripe has
		 * no updated data, so हटाओ it from hash list and the stripe
		 * will be reinitialized
		 */
unhash:
		hash = sh->hash_lock_index;
		spin_lock_irq(conf->hash_locks + hash);
		हटाओ_hash(sh);
		spin_unlock_irq(conf->hash_locks + hash);
		अगर (head_sh->batch_head) अणु
			sh = list_first_entry(&sh->batch_list,
					      काष्ठा stripe_head, batch_list);
			अगर (sh != head_sh)
					जाओ unhash;
		पूर्ण
		sh = head_sh;

		अगर (test_bit(STRIPE_SYNC_REQUESTED, &sh->state))
			set_bit(STRIPE_HANDLE, &sh->state);

	पूर्ण

	अगर (test_and_clear_bit(STRIPE_FULL_WRITE, &sh->state))
		अगर (atomic_dec_and_test(&conf->pending_full_ग_लिखोs))
			md_wakeup_thपढ़ो(conf->mddev->thपढ़ो);

	अगर (head_sh->batch_head && करो_endio)
		अवरोध_stripe_batch_list(head_sh, STRIPE_EXPAND_SYNC_FLAGS);
पूर्ण

/*
 * For RMW in ग_लिखो back cache, we need extra page in prexor to store the
 * old data. This page is stored in dev->orig_page.
 *
 * This function checks whether we have data क्रम prexor. The exact logic
 * is:
 *       R5_UPTODATE && (!R5_InJournal || R5_OrigPageUPTDODATE)
 */
अटल अंतरभूत bool uptodate_क्रम_rmw(काष्ठा r5dev *dev)
अणु
	वापस (test_bit(R5_UPTODATE, &dev->flags)) &&
		(!test_bit(R5_InJournal, &dev->flags) ||
		 test_bit(R5_OrigPageUPTDODATE, &dev->flags));
पूर्ण

अटल पूर्णांक handle_stripe_dirtying(काष्ठा r5conf *conf,
				  काष्ठा stripe_head *sh,
				  काष्ठा stripe_head_state *s,
				  पूर्णांक disks)
अणु
	पूर्णांक rmw = 0, rcw = 0, i;
	sector_t recovery_cp = conf->mddev->recovery_cp;

	/* Check whether resync is now happening or should start.
	 * If yes, then the array is dirty (after unclean shutकरोwn or
	 * initial creation), so parity in some stripes might be inconsistent.
	 * In this हाल, we need to always करो reस्थिरruct-ग_लिखो, to ensure
	 * that in हाल of drive failure or पढ़ो-error correction, we
	 * generate correct data from the parity.
	 */
	अगर (conf->rmw_level == PARITY_DISABLE_RMW ||
	    (recovery_cp < MaxSector && sh->sector >= recovery_cp &&
	     s->failed == 0)) अणु
		/* Calculate the real rcw later - क्रम now make it
		 * look like rcw is cheaper
		 */
		rcw = 1; rmw = 2;
		pr_debug("force RCW rmw_level=%u, recovery_cp=%llu sh->sector=%llu\n",
			 conf->rmw_level, (अचिन्हित दीर्घ दीर्घ)recovery_cp,
			 (अचिन्हित दीर्घ दीर्घ)sh->sector);
	पूर्ण अन्यथा क्रम (i = disks; i--; ) अणु
		/* would I have to पढ़ो this buffer क्रम पढ़ो_modअगरy_ग_लिखो */
		काष्ठा r5dev *dev = &sh->dev[i];
		अगर (((dev->toग_लिखो && !delay_toग_लिखो(conf, dev, s)) ||
		     i == sh->pd_idx || i == sh->qd_idx ||
		     test_bit(R5_InJournal, &dev->flags)) &&
		    !test_bit(R5_LOCKED, &dev->flags) &&
		    !(uptodate_क्रम_rmw(dev) ||
		      test_bit(R5_Wantcompute, &dev->flags))) अणु
			अगर (test_bit(R5_Insync, &dev->flags))
				rmw++;
			अन्यथा
				rmw += 2*disks;  /* cannot पढ़ो it */
		पूर्ण
		/* Would I have to पढ़ो this buffer क्रम reस्थिरruct_ग_लिखो */
		अगर (!test_bit(R5_OVERWRITE, &dev->flags) &&
		    i != sh->pd_idx && i != sh->qd_idx &&
		    !test_bit(R5_LOCKED, &dev->flags) &&
		    !(test_bit(R5_UPTODATE, &dev->flags) ||
		      test_bit(R5_Wantcompute, &dev->flags))) अणु
			अगर (test_bit(R5_Insync, &dev->flags))
				rcw++;
			अन्यथा
				rcw += 2*disks;
		पूर्ण
	पूर्ण

	pr_debug("for sector %llu state 0x%lx, rmw=%d rcw=%d\n",
		 (अचिन्हित दीर्घ दीर्घ)sh->sector, sh->state, rmw, rcw);
	set_bit(STRIPE_HANDLE, &sh->state);
	अगर ((rmw < rcw || (rmw == rcw && conf->rmw_level == PARITY_PREFER_RMW)) && rmw > 0) अणु
		/* prefer पढ़ो-modअगरy-ग_लिखो, but need to get some data */
		अगर (conf->mddev->queue)
			blk_add_trace_msg(conf->mddev->queue,
					  "raid5 rmw %llu %d",
					  (अचिन्हित दीर्घ दीर्घ)sh->sector, rmw);
		क्रम (i = disks; i--; ) अणु
			काष्ठा r5dev *dev = &sh->dev[i];
			अगर (test_bit(R5_InJournal, &dev->flags) &&
			    dev->page == dev->orig_page &&
			    !test_bit(R5_LOCKED, &sh->dev[sh->pd_idx].flags)) अणु
				/* alloc page क्रम prexor */
				काष्ठा page *p = alloc_page(GFP_NOIO);

				अगर (p) अणु
					dev->orig_page = p;
					जारी;
				पूर्ण

				/*
				 * alloc_page() failed, try use
				 * disk_info->extra_page
				 */
				अगर (!test_and_set_bit(R5C_EXTRA_PAGE_IN_USE,
						      &conf->cache_state)) अणु
					r5c_use_extra_page(sh);
					अवरोध;
				पूर्ण

				/* extra_page in use, add to delayed_list */
				set_bit(STRIPE_DELAYED, &sh->state);
				s->रुकोing_extra_page = 1;
				वापस -EAGAIN;
			पूर्ण
		पूर्ण

		क्रम (i = disks; i--; ) अणु
			काष्ठा r5dev *dev = &sh->dev[i];
			अगर (((dev->toग_लिखो && !delay_toग_लिखो(conf, dev, s)) ||
			     i == sh->pd_idx || i == sh->qd_idx ||
			     test_bit(R5_InJournal, &dev->flags)) &&
			    !test_bit(R5_LOCKED, &dev->flags) &&
			    !(uptodate_क्रम_rmw(dev) ||
			      test_bit(R5_Wantcompute, &dev->flags)) &&
			    test_bit(R5_Insync, &dev->flags)) अणु
				अगर (test_bit(STRIPE_PREREAD_ACTIVE,
					     &sh->state)) अणु
					pr_debug("Read_old block %d for r-m-w\n",
						 i);
					set_bit(R5_LOCKED, &dev->flags);
					set_bit(R5_Wantपढ़ो, &dev->flags);
					s->locked++;
				पूर्ण अन्यथा
					set_bit(STRIPE_DELAYED, &sh->state);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर ((rcw < rmw || (rcw == rmw && conf->rmw_level != PARITY_PREFER_RMW)) && rcw > 0) अणु
		/* want reस्थिरruct ग_लिखो, but need to get some data */
		पूर्णांक qपढ़ो =0;
		rcw = 0;
		क्रम (i = disks; i--; ) अणु
			काष्ठा r5dev *dev = &sh->dev[i];
			अगर (!test_bit(R5_OVERWRITE, &dev->flags) &&
			    i != sh->pd_idx && i != sh->qd_idx &&
			    !test_bit(R5_LOCKED, &dev->flags) &&
			    !(test_bit(R5_UPTODATE, &dev->flags) ||
			      test_bit(R5_Wantcompute, &dev->flags))) अणु
				rcw++;
				अगर (test_bit(R5_Insync, &dev->flags) &&
				    test_bit(STRIPE_PREREAD_ACTIVE,
					     &sh->state)) अणु
					pr_debug("Read_old block "
						"%d for Reconstruct\n", i);
					set_bit(R5_LOCKED, &dev->flags);
					set_bit(R5_Wantपढ़ो, &dev->flags);
					s->locked++;
					qपढ़ो++;
				पूर्ण अन्यथा
					set_bit(STRIPE_DELAYED, &sh->state);
			पूर्ण
		पूर्ण
		अगर (rcw && conf->mddev->queue)
			blk_add_trace_msg(conf->mddev->queue, "raid5 rcw %llu %d %d %d",
					  (अचिन्हित दीर्घ दीर्घ)sh->sector,
					  rcw, qपढ़ो, test_bit(STRIPE_DELAYED, &sh->state));
	पूर्ण

	अगर (rcw > disks && rmw > disks &&
	    !test_bit(STRIPE_PREREAD_ACTIVE, &sh->state))
		set_bit(STRIPE_DELAYED, &sh->state);

	/* now अगर nothing is locked, and अगर we have enough data,
	 * we can start a ग_लिखो request
	 */
	/* since handle_stripe can be called at any समय we need to handle the
	 * हाल where a compute block operation has been submitted and then a
	 * subsequent call wants to start a ग_लिखो request.  raid_run_ops only
	 * handles the हाल where compute block and reस्थिरruct are requested
	 * simultaneously.  If this is not the हाल then new ग_लिखोs need to be
	 * held off until the compute completes.
	 */
	अगर ((s->req_compute || !test_bit(STRIPE_COMPUTE_RUN, &sh->state)) &&
	    (s->locked == 0 && (rcw == 0 || rmw == 0) &&
	     !test_bit(STRIPE_BIT_DELAY, &sh->state)))
		schedule_reस्थिरruction(sh, s, rcw == 0, 0);
	वापस 0;
पूर्ण

अटल व्योम handle_parity_checks5(काष्ठा r5conf *conf, काष्ठा stripe_head *sh,
				काष्ठा stripe_head_state *s, पूर्णांक disks)
अणु
	काष्ठा r5dev *dev = शून्य;

	BUG_ON(sh->batch_head);
	set_bit(STRIPE_HANDLE, &sh->state);

	चयन (sh->check_state) अणु
	हाल check_state_idle:
		/* start a new check operation अगर there are no failures */
		अगर (s->failed == 0) अणु
			BUG_ON(s->uptodate != disks);
			sh->check_state = check_state_run;
			set_bit(STRIPE_OP_CHECK, &s->ops_request);
			clear_bit(R5_UPTODATE, &sh->dev[sh->pd_idx].flags);
			s->uptodate--;
			अवरोध;
		पूर्ण
		dev = &sh->dev[s->failed_num[0]];
		fallthrough;
	हाल check_state_compute_result:
		sh->check_state = check_state_idle;
		अगर (!dev)
			dev = &sh->dev[sh->pd_idx];

		/* check that a ग_लिखो has not made the stripe insync */
		अगर (test_bit(STRIPE_INSYNC, &sh->state))
			अवरोध;

		/* either failed parity check, or recovery is happening */
		BUG_ON(!test_bit(R5_UPTODATE, &dev->flags));
		BUG_ON(s->uptodate != disks);

		set_bit(R5_LOCKED, &dev->flags);
		s->locked++;
		set_bit(R5_Wantग_लिखो, &dev->flags);

		clear_bit(STRIPE_DEGRADED, &sh->state);
		set_bit(STRIPE_INSYNC, &sh->state);
		अवरोध;
	हाल check_state_run:
		अवरोध; /* we will be called again upon completion */
	हाल check_state_check_result:
		sh->check_state = check_state_idle;

		/* अगर a failure occurred during the check operation, leave
		 * STRIPE_INSYNC not set and let the stripe be handled again
		 */
		अगर (s->failed)
			अवरोध;

		/* handle a successful check operation, अगर parity is correct
		 * we are करोne.  Otherwise update the mismatch count and repair
		 * parity अगर !MD_RECOVERY_CHECK
		 */
		अगर ((sh->ops.zero_sum_result & SUM_CHECK_P_RESULT) == 0)
			/* parity is correct (on disc,
			 * not in buffer any more)
			 */
			set_bit(STRIPE_INSYNC, &sh->state);
		अन्यथा अणु
			atomic64_add(RAID5_STRIPE_SECTORS(conf), &conf->mddev->resync_mismatches);
			अगर (test_bit(MD_RECOVERY_CHECK, &conf->mddev->recovery)) अणु
				/* करोn't try to repair!! */
				set_bit(STRIPE_INSYNC, &sh->state);
				pr_warn_ratelimited("%s: mismatch sector in range "
						    "%llu-%llu\n", mdname(conf->mddev),
						    (अचिन्हित दीर्घ दीर्घ) sh->sector,
						    (अचिन्हित दीर्घ दीर्घ) sh->sector +
						    RAID5_STRIPE_SECTORS(conf));
			पूर्ण अन्यथा अणु
				sh->check_state = check_state_compute_run;
				set_bit(STRIPE_COMPUTE_RUN, &sh->state);
				set_bit(STRIPE_OP_COMPUTE_BLK, &s->ops_request);
				set_bit(R5_Wantcompute,
					&sh->dev[sh->pd_idx].flags);
				sh->ops.target = sh->pd_idx;
				sh->ops.target2 = -1;
				s->uptodate++;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल check_state_compute_run:
		अवरोध;
	शेष:
		pr_err("%s: unknown check_state: %d sector: %llu\n",
		       __func__, sh->check_state,
		       (अचिन्हित दीर्घ दीर्घ) sh->sector);
		BUG();
	पूर्ण
पूर्ण

अटल व्योम handle_parity_checks6(काष्ठा r5conf *conf, काष्ठा stripe_head *sh,
				  काष्ठा stripe_head_state *s,
				  पूर्णांक disks)
अणु
	पूर्णांक pd_idx = sh->pd_idx;
	पूर्णांक qd_idx = sh->qd_idx;
	काष्ठा r5dev *dev;

	BUG_ON(sh->batch_head);
	set_bit(STRIPE_HANDLE, &sh->state);

	BUG_ON(s->failed > 2);

	/* Want to check and possibly repair P and Q.
	 * However there could be one 'failed' device, in which
	 * हाल we can only check one of them, possibly using the
	 * other to generate missing data
	 */

	चयन (sh->check_state) अणु
	हाल check_state_idle:
		/* start a new check operation अगर there are < 2 failures */
		अगर (s->failed == s->q_failed) अणु
			/* The only possible failed device holds Q, so it
			 * makes sense to check P (If anything अन्यथा were failed,
			 * we would have used P to recreate it).
			 */
			sh->check_state = check_state_run;
		पूर्ण
		अगर (!s->q_failed && s->failed < 2) अणु
			/* Q is not failed, and we didn't use it to generate
			 * anything, so it makes sense to check it
			 */
			अगर (sh->check_state == check_state_run)
				sh->check_state = check_state_run_pq;
			अन्यथा
				sh->check_state = check_state_run_q;
		पूर्ण

		/* discard potentially stale zero_sum_result */
		sh->ops.zero_sum_result = 0;

		अगर (sh->check_state == check_state_run) अणु
			/* async_xor_zero_sum destroys the contents of P */
			clear_bit(R5_UPTODATE, &sh->dev[pd_idx].flags);
			s->uptodate--;
		पूर्ण
		अगर (sh->check_state >= check_state_run &&
		    sh->check_state <= check_state_run_pq) अणु
			/* async_syndrome_zero_sum preserves P and Q, so
			 * no need to mark them !uptodate here
			 */
			set_bit(STRIPE_OP_CHECK, &s->ops_request);
			अवरोध;
		पूर्ण

		/* we have 2-disk failure */
		BUG_ON(s->failed != 2);
		fallthrough;
	हाल check_state_compute_result:
		sh->check_state = check_state_idle;

		/* check that a ग_लिखो has not made the stripe insync */
		अगर (test_bit(STRIPE_INSYNC, &sh->state))
			अवरोध;

		/* now ग_लिखो out any block on a failed drive,
		 * or P or Q अगर they were recomputed
		 */
		dev = शून्य;
		अगर (s->failed == 2) अणु
			dev = &sh->dev[s->failed_num[1]];
			s->locked++;
			set_bit(R5_LOCKED, &dev->flags);
			set_bit(R5_Wantग_लिखो, &dev->flags);
		पूर्ण
		अगर (s->failed >= 1) अणु
			dev = &sh->dev[s->failed_num[0]];
			s->locked++;
			set_bit(R5_LOCKED, &dev->flags);
			set_bit(R5_Wantग_लिखो, &dev->flags);
		पूर्ण
		अगर (sh->ops.zero_sum_result & SUM_CHECK_P_RESULT) अणु
			dev = &sh->dev[pd_idx];
			s->locked++;
			set_bit(R5_LOCKED, &dev->flags);
			set_bit(R5_Wantग_लिखो, &dev->flags);
		पूर्ण
		अगर (sh->ops.zero_sum_result & SUM_CHECK_Q_RESULT) अणु
			dev = &sh->dev[qd_idx];
			s->locked++;
			set_bit(R5_LOCKED, &dev->flags);
			set_bit(R5_Wantग_लिखो, &dev->flags);
		पूर्ण
		अगर (WARN_ONCE(dev && !test_bit(R5_UPTODATE, &dev->flags),
			      "%s: disk%td not up to date\n",
			      mdname(conf->mddev),
			      dev - (काष्ठा r5dev *) &sh->dev)) अणु
			clear_bit(R5_LOCKED, &dev->flags);
			clear_bit(R5_Wantग_लिखो, &dev->flags);
			s->locked--;
		पूर्ण
		clear_bit(STRIPE_DEGRADED, &sh->state);

		set_bit(STRIPE_INSYNC, &sh->state);
		अवरोध;
	हाल check_state_run:
	हाल check_state_run_q:
	हाल check_state_run_pq:
		अवरोध; /* we will be called again upon completion */
	हाल check_state_check_result:
		sh->check_state = check_state_idle;

		/* handle a successful check operation, अगर parity is correct
		 * we are करोne.  Otherwise update the mismatch count and repair
		 * parity अगर !MD_RECOVERY_CHECK
		 */
		अगर (sh->ops.zero_sum_result == 0) अणु
			/* both parities are correct */
			अगर (!s->failed)
				set_bit(STRIPE_INSYNC, &sh->state);
			अन्यथा अणु
				/* in contrast to the raid5 हाल we can validate
				 * parity, but still have a failure to ग_लिखो
				 * back
				 */
				sh->check_state = check_state_compute_result;
				/* Returning at this poपूर्णांक means that we may go
				 * off and bring p and/or q uptodate again so
				 * we make sure to check zero_sum_result again
				 * to verअगरy अगर p or q need ग_लिखोback
				 */
			पूर्ण
		पूर्ण अन्यथा अणु
			atomic64_add(RAID5_STRIPE_SECTORS(conf), &conf->mddev->resync_mismatches);
			अगर (test_bit(MD_RECOVERY_CHECK, &conf->mddev->recovery)) अणु
				/* करोn't try to repair!! */
				set_bit(STRIPE_INSYNC, &sh->state);
				pr_warn_ratelimited("%s: mismatch sector in range "
						    "%llu-%llu\n", mdname(conf->mddev),
						    (अचिन्हित दीर्घ दीर्घ) sh->sector,
						    (अचिन्हित दीर्घ दीर्घ) sh->sector +
						    RAID5_STRIPE_SECTORS(conf));
			पूर्ण अन्यथा अणु
				पूर्णांक *target = &sh->ops.target;

				sh->ops.target = -1;
				sh->ops.target2 = -1;
				sh->check_state = check_state_compute_run;
				set_bit(STRIPE_COMPUTE_RUN, &sh->state);
				set_bit(STRIPE_OP_COMPUTE_BLK, &s->ops_request);
				अगर (sh->ops.zero_sum_result & SUM_CHECK_P_RESULT) अणु
					set_bit(R5_Wantcompute,
						&sh->dev[pd_idx].flags);
					*target = pd_idx;
					target = &sh->ops.target2;
					s->uptodate++;
				पूर्ण
				अगर (sh->ops.zero_sum_result & SUM_CHECK_Q_RESULT) अणु
					set_bit(R5_Wantcompute,
						&sh->dev[qd_idx].flags);
					*target = qd_idx;
					s->uptodate++;
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	हाल check_state_compute_run:
		अवरोध;
	शेष:
		pr_warn("%s: unknown check_state: %d sector: %llu\n",
			__func__, sh->check_state,
			(अचिन्हित दीर्घ दीर्घ) sh->sector);
		BUG();
	पूर्ण
पूर्ण

अटल व्योम handle_stripe_expansion(काष्ठा r5conf *conf, काष्ठा stripe_head *sh)
अणु
	पूर्णांक i;

	/* We have पढ़ो all the blocks in this stripe and now we need to
	 * copy some of them पूर्णांकo a target stripe क्रम expand.
	 */
	काष्ठा dma_async_tx_descriptor *tx = शून्य;
	BUG_ON(sh->batch_head);
	clear_bit(STRIPE_EXPAND_SOURCE, &sh->state);
	क्रम (i = 0; i < sh->disks; i++)
		अगर (i != sh->pd_idx && i != sh->qd_idx) अणु
			पूर्णांक dd_idx, j;
			काष्ठा stripe_head *sh2;
			काष्ठा async_submit_ctl submit;

			sector_t bn = raid5_compute_blocknr(sh, i, 1);
			sector_t s = raid5_compute_sector(conf, bn, 0,
							  &dd_idx, शून्य);
			sh2 = raid5_get_active_stripe(conf, s, 0, 1, 1);
			अगर (sh2 == शून्य)
				/* so far only the early blocks of this stripe
				 * have been requested.  When later blocks
				 * get requested, we will try again
				 */
				जारी;
			अगर (!test_bit(STRIPE_EXPANDING, &sh2->state) ||
			   test_bit(R5_Expanded, &sh2->dev[dd_idx].flags)) अणु
				/* must have alपढ़ोy करोne this block */
				raid5_release_stripe(sh2);
				जारी;
			पूर्ण

			/* place all the copies on one channel */
			init_async_submit(&submit, 0, tx, शून्य, शून्य, शून्य);
			tx = async_स_नकल(sh2->dev[dd_idx].page,
					  sh->dev[i].page, sh2->dev[dd_idx].offset,
					  sh->dev[i].offset, RAID5_STRIPE_SIZE(conf),
					  &submit);

			set_bit(R5_Expanded, &sh2->dev[dd_idx].flags);
			set_bit(R5_UPTODATE, &sh2->dev[dd_idx].flags);
			क्रम (j = 0; j < conf->raid_disks; j++)
				अगर (j != sh2->pd_idx &&
				    j != sh2->qd_idx &&
				    !test_bit(R5_Expanded, &sh2->dev[j].flags))
					अवरोध;
			अगर (j == conf->raid_disks) अणु
				set_bit(STRIPE_EXPAND_READY, &sh2->state);
				set_bit(STRIPE_HANDLE, &sh2->state);
			पूर्ण
			raid5_release_stripe(sh2);

		पूर्ण
	/* करोne submitting copies, रुको क्रम them to complete */
	async_tx_quiesce(&tx);
पूर्ण

/*
 * handle_stripe - करो things to a stripe.
 *
 * We lock the stripe by setting STRIPE_ACTIVE and then examine the
 * state of various bits to see what needs to be करोne.
 * Possible results:
 *    वापस some पढ़ो requests which now have data
 *    वापस some ग_लिखो requests which are safely on storage
 *    schedule a पढ़ो on some buffers
 *    schedule a ग_लिखो of some buffers
 *    वापस confirmation of parity correctness
 *
 */

अटल व्योम analyse_stripe(काष्ठा stripe_head *sh, काष्ठा stripe_head_state *s)
अणु
	काष्ठा r5conf *conf = sh->raid_conf;
	पूर्णांक disks = sh->disks;
	काष्ठा r5dev *dev;
	पूर्णांक i;
	पूर्णांक करो_recovery = 0;

	स_रखो(s, 0, माप(*s));

	s->expanding = test_bit(STRIPE_EXPAND_SOURCE, &sh->state) && !sh->batch_head;
	s->expanded = test_bit(STRIPE_EXPAND_READY, &sh->state) && !sh->batch_head;
	s->failed_num[0] = -1;
	s->failed_num[1] = -1;
	s->log_failed = r5l_log_disk_error(conf);

	/* Now to look around and see what can be करोne */
	rcu_पढ़ो_lock();
	क्रम (i=disks; i--; ) अणु
		काष्ठा md_rdev *rdev;
		sector_t first_bad;
		पूर्णांक bad_sectors;
		पूर्णांक is_bad = 0;

		dev = &sh->dev[i];

		pr_debug("check %d: state 0x%lx read %p write %p written %p\n",
			 i, dev->flags,
			 dev->toपढ़ो, dev->toग_लिखो, dev->written);
		/* maybe we can reply to a पढ़ो
		 *
		 * new wantfill requests are only permitted जबतक
		 * ops_complete_biofill is guaranteed to be inactive
		 */
		अगर (test_bit(R5_UPTODATE, &dev->flags) && dev->toपढ़ो &&
		    !test_bit(STRIPE_BIOFILL_RUN, &sh->state))
			set_bit(R5_Wantfill, &dev->flags);

		/* now count some things */
		अगर (test_bit(R5_LOCKED, &dev->flags))
			s->locked++;
		अगर (test_bit(R5_UPTODATE, &dev->flags))
			s->uptodate++;
		अगर (test_bit(R5_Wantcompute, &dev->flags)) अणु
			s->compute++;
			BUG_ON(s->compute > 2);
		पूर्ण

		अगर (test_bit(R5_Wantfill, &dev->flags))
			s->to_fill++;
		अन्यथा अगर (dev->toपढ़ो)
			s->to_पढ़ो++;
		अगर (dev->toग_लिखो) अणु
			s->to_ग_लिखो++;
			अगर (!test_bit(R5_OVERWRITE, &dev->flags))
				s->non_overग_लिखो++;
		पूर्ण
		अगर (dev->written)
			s->written++;
		/* Prefer to use the replacement क्रम पढ़ोs, but only
		 * अगर it is recovered enough and has no bad blocks.
		 */
		rdev = rcu_dereference(conf->disks[i].replacement);
		अगर (rdev && !test_bit(Faulty, &rdev->flags) &&
		    rdev->recovery_offset >= sh->sector + RAID5_STRIPE_SECTORS(conf) &&
		    !is_badblock(rdev, sh->sector, RAID5_STRIPE_SECTORS(conf),
				 &first_bad, &bad_sectors))
			set_bit(R5_ReadRepl, &dev->flags);
		अन्यथा अणु
			अगर (rdev && !test_bit(Faulty, &rdev->flags))
				set_bit(R5_NeedReplace, &dev->flags);
			अन्यथा
				clear_bit(R5_NeedReplace, &dev->flags);
			rdev = rcu_dereference(conf->disks[i].rdev);
			clear_bit(R5_ReadRepl, &dev->flags);
		पूर्ण
		अगर (rdev && test_bit(Faulty, &rdev->flags))
			rdev = शून्य;
		अगर (rdev) अणु
			is_bad = is_badblock(rdev, sh->sector, RAID5_STRIPE_SECTORS(conf),
					     &first_bad, &bad_sectors);
			अगर (s->blocked_rdev == शून्य
			    && (test_bit(Blocked, &rdev->flags)
				|| is_bad < 0)) अणु
				अगर (is_bad < 0)
					set_bit(BlockedBadBlocks,
						&rdev->flags);
				s->blocked_rdev = rdev;
				atomic_inc(&rdev->nr_pending);
			पूर्ण
		पूर्ण
		clear_bit(R5_Insync, &dev->flags);
		अगर (!rdev)
			/* Not in-sync */;
		अन्यथा अगर (is_bad) अणु
			/* also not in-sync */
			अगर (!test_bit(WriteErrorSeen, &rdev->flags) &&
			    test_bit(R5_UPTODATE, &dev->flags)) अणु
				/* treat as in-sync, but with a पढ़ो error
				 * which we can now try to correct
				 */
				set_bit(R5_Insync, &dev->flags);
				set_bit(R5_ReadError, &dev->flags);
			पूर्ण
		पूर्ण अन्यथा अगर (test_bit(In_sync, &rdev->flags))
			set_bit(R5_Insync, &dev->flags);
		अन्यथा अगर (sh->sector + RAID5_STRIPE_SECTORS(conf) <= rdev->recovery_offset)
			/* in sync अगर beक्रमe recovery_offset */
			set_bit(R5_Insync, &dev->flags);
		अन्यथा अगर (test_bit(R5_UPTODATE, &dev->flags) &&
			 test_bit(R5_Expanded, &dev->flags))
			/* If we've reshaped पूर्णांकo here, we assume it is Insync.
			 * We will लघुly update recovery_offset to make
			 * it official.
			 */
			set_bit(R5_Insync, &dev->flags);

		अगर (test_bit(R5_WriteError, &dev->flags)) अणु
			/* This flag करोes not apply to '.replacement'
			 * only to .rdev, so make sure to check that*/
			काष्ठा md_rdev *rdev2 = rcu_dereference(
				conf->disks[i].rdev);
			अगर (rdev2 == rdev)
				clear_bit(R5_Insync, &dev->flags);
			अगर (rdev2 && !test_bit(Faulty, &rdev2->flags)) अणु
				s->handle_bad_blocks = 1;
				atomic_inc(&rdev2->nr_pending);
			पूर्ण अन्यथा
				clear_bit(R5_WriteError, &dev->flags);
		पूर्ण
		अगर (test_bit(R5_MadeGood, &dev->flags)) अणु
			/* This flag करोes not apply to '.replacement'
			 * only to .rdev, so make sure to check that*/
			काष्ठा md_rdev *rdev2 = rcu_dereference(
				conf->disks[i].rdev);
			अगर (rdev2 && !test_bit(Faulty, &rdev2->flags)) अणु
				s->handle_bad_blocks = 1;
				atomic_inc(&rdev2->nr_pending);
			पूर्ण अन्यथा
				clear_bit(R5_MadeGood, &dev->flags);
		पूर्ण
		अगर (test_bit(R5_MadeGoodRepl, &dev->flags)) अणु
			काष्ठा md_rdev *rdev2 = rcu_dereference(
				conf->disks[i].replacement);
			अगर (rdev2 && !test_bit(Faulty, &rdev2->flags)) अणु
				s->handle_bad_blocks = 1;
				atomic_inc(&rdev2->nr_pending);
			पूर्ण अन्यथा
				clear_bit(R5_MadeGoodRepl, &dev->flags);
		पूर्ण
		अगर (!test_bit(R5_Insync, &dev->flags)) अणु
			/* The ReadError flag will just be confusing now */
			clear_bit(R5_ReadError, &dev->flags);
			clear_bit(R5_ReWrite, &dev->flags);
		पूर्ण
		अगर (test_bit(R5_ReadError, &dev->flags))
			clear_bit(R5_Insync, &dev->flags);
		अगर (!test_bit(R5_Insync, &dev->flags)) अणु
			अगर (s->failed < 2)
				s->failed_num[s->failed] = i;
			s->failed++;
			अगर (rdev && !test_bit(Faulty, &rdev->flags))
				करो_recovery = 1;
			अन्यथा अगर (!rdev) अणु
				rdev = rcu_dereference(
				    conf->disks[i].replacement);
				अगर (rdev && !test_bit(Faulty, &rdev->flags))
					करो_recovery = 1;
			पूर्ण
		पूर्ण

		अगर (test_bit(R5_InJournal, &dev->flags))
			s->injournal++;
		अगर (test_bit(R5_InJournal, &dev->flags) && dev->written)
			s->just_cached++;
	पूर्ण
	अगर (test_bit(STRIPE_SYNCING, &sh->state)) अणु
		/* If there is a failed device being replaced,
		 *     we must be recovering.
		 * अन्यथा अगर we are after recovery_cp, we must be syncing
		 * अन्यथा अगर MD_RECOVERY_REQUESTED is set, we also are syncing.
		 * अन्यथा we can only be replacing
		 * sync and recovery both need to पढ़ो all devices, and so
		 * use the same flag.
		 */
		अगर (करो_recovery ||
		    sh->sector >= conf->mddev->recovery_cp ||
		    test_bit(MD_RECOVERY_REQUESTED, &(conf->mddev->recovery)))
			s->syncing = 1;
		अन्यथा
			s->replacing = 1;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * Return '1' if this is a member of batch, or '0' अगर it is a lone stripe or
 * a head which can now be handled.
 */
अटल पूर्णांक clear_batch_पढ़ोy(काष्ठा stripe_head *sh)
अणु
	काष्ठा stripe_head *पंचांगp;
	अगर (!test_and_clear_bit(STRIPE_BATCH_READY, &sh->state))
		वापस (sh->batch_head && sh->batch_head != sh);
	spin_lock(&sh->stripe_lock);
	अगर (!sh->batch_head) अणु
		spin_unlock(&sh->stripe_lock);
		वापस 0;
	पूर्ण

	/*
	 * this stripe could be added to a batch list beक्रमe we check
	 * BATCH_READY, skips it
	 */
	अगर (sh->batch_head != sh) अणु
		spin_unlock(&sh->stripe_lock);
		वापस 1;
	पूर्ण
	spin_lock(&sh->batch_lock);
	list_क्रम_each_entry(पंचांगp, &sh->batch_list, batch_list)
		clear_bit(STRIPE_BATCH_READY, &पंचांगp->state);
	spin_unlock(&sh->batch_lock);
	spin_unlock(&sh->stripe_lock);

	/*
	 * BATCH_READY is cleared, no new stripes can be added.
	 * batch_list can be accessed without lock
	 */
	वापस 0;
पूर्ण

अटल व्योम अवरोध_stripe_batch_list(काष्ठा stripe_head *head_sh,
				    अचिन्हित दीर्घ handle_flags)
अणु
	काष्ठा stripe_head *sh, *next;
	पूर्णांक i;
	पूर्णांक करो_wakeup = 0;

	list_क्रम_each_entry_safe(sh, next, &head_sh->batch_list, batch_list) अणु

		list_del_init(&sh->batch_list);

		WARN_ONCE(sh->state & ((1 << STRIPE_ACTIVE) |
					  (1 << STRIPE_SYNCING) |
					  (1 << STRIPE_REPLACED) |
					  (1 << STRIPE_DELAYED) |
					  (1 << STRIPE_BIT_DELAY) |
					  (1 << STRIPE_FULL_WRITE) |
					  (1 << STRIPE_BIOFILL_RUN) |
					  (1 << STRIPE_COMPUTE_RUN)  |
					  (1 << STRIPE_DISCARD) |
					  (1 << STRIPE_BATCH_READY) |
					  (1 << STRIPE_BATCH_ERR) |
					  (1 << STRIPE_BITMAP_PENDING)),
			"stripe state: %lx\n", sh->state);
		WARN_ONCE(head_sh->state & ((1 << STRIPE_DISCARD) |
					      (1 << STRIPE_REPLACED)),
			"head stripe state: %lx\n", head_sh->state);

		set_mask_bits(&sh->state, ~(STRIPE_EXPAND_SYNC_FLAGS |
					    (1 << STRIPE_PREREAD_ACTIVE) |
					    (1 << STRIPE_DEGRADED) |
					    (1 << STRIPE_ON_UNPLUG_LIST)),
			      head_sh->state & (1 << STRIPE_INSYNC));

		sh->check_state = head_sh->check_state;
		sh->reस्थिरruct_state = head_sh->reस्थिरruct_state;
		spin_lock_irq(&sh->stripe_lock);
		sh->batch_head = शून्य;
		spin_unlock_irq(&sh->stripe_lock);
		क्रम (i = 0; i < sh->disks; i++) अणु
			अगर (test_and_clear_bit(R5_Overlap, &sh->dev[i].flags))
				करो_wakeup = 1;
			sh->dev[i].flags = head_sh->dev[i].flags &
				(~((1 << R5_WriteError) | (1 << R5_Overlap)));
		पूर्ण
		अगर (handle_flags == 0 ||
		    sh->state & handle_flags)
			set_bit(STRIPE_HANDLE, &sh->state);
		raid5_release_stripe(sh);
	पूर्ण
	spin_lock_irq(&head_sh->stripe_lock);
	head_sh->batch_head = शून्य;
	spin_unlock_irq(&head_sh->stripe_lock);
	क्रम (i = 0; i < head_sh->disks; i++)
		अगर (test_and_clear_bit(R5_Overlap, &head_sh->dev[i].flags))
			करो_wakeup = 1;
	अगर (head_sh->state & handle_flags)
		set_bit(STRIPE_HANDLE, &head_sh->state);

	अगर (करो_wakeup)
		wake_up(&head_sh->raid_conf->रुको_क्रम_overlap);
पूर्ण

अटल व्योम handle_stripe(काष्ठा stripe_head *sh)
अणु
	काष्ठा stripe_head_state s;
	काष्ठा r5conf *conf = sh->raid_conf;
	पूर्णांक i;
	पूर्णांक prexor;
	पूर्णांक disks = sh->disks;
	काष्ठा r5dev *pdev, *qdev;

	clear_bit(STRIPE_HANDLE, &sh->state);

	/*
	 * handle_stripe should not जारी handle the batched stripe, only
	 * the head of batch list or lone stripe can जारी. Otherwise we
	 * could see अवरोध_stripe_batch_list warns about the STRIPE_ACTIVE
	 * is set क्रम the batched stripe.
	 */
	अगर (clear_batch_पढ़ोy(sh))
		वापस;

	अगर (test_and_set_bit_lock(STRIPE_ACTIVE, &sh->state)) अणु
		/* alपढ़ोy being handled, ensure it माला_लो handled
		 * again when current action finishes */
		set_bit(STRIPE_HANDLE, &sh->state);
		वापस;
	पूर्ण

	अगर (test_and_clear_bit(STRIPE_BATCH_ERR, &sh->state))
		अवरोध_stripe_batch_list(sh, 0);

	अगर (test_bit(STRIPE_SYNC_REQUESTED, &sh->state) && !sh->batch_head) अणु
		spin_lock(&sh->stripe_lock);
		/*
		 * Cannot process 'sync' concurrently with 'discard'.
		 * Flush data in r5cache beक्रमe 'sync'.
		 */
		अगर (!test_bit(STRIPE_R5C_PARTIAL_STRIPE, &sh->state) &&
		    !test_bit(STRIPE_R5C_FULL_STRIPE, &sh->state) &&
		    !test_bit(STRIPE_DISCARD, &sh->state) &&
		    test_and_clear_bit(STRIPE_SYNC_REQUESTED, &sh->state)) अणु
			set_bit(STRIPE_SYNCING, &sh->state);
			clear_bit(STRIPE_INSYNC, &sh->state);
			clear_bit(STRIPE_REPLACED, &sh->state);
		पूर्ण
		spin_unlock(&sh->stripe_lock);
	पूर्ण
	clear_bit(STRIPE_DELAYED, &sh->state);

	pr_debug("handling stripe %llu, state=%#lx cnt=%d, "
		"pd_idx=%d, qd_idx=%d\n, check:%d, reconstruct:%d\n",
	       (अचिन्हित दीर्घ दीर्घ)sh->sector, sh->state,
	       atomic_पढ़ो(&sh->count), sh->pd_idx, sh->qd_idx,
	       sh->check_state, sh->reस्थिरruct_state);

	analyse_stripe(sh, &s);

	अगर (test_bit(STRIPE_LOG_TRAPPED, &sh->state))
		जाओ finish;

	अगर (s.handle_bad_blocks ||
	    test_bit(MD_SB_CHANGE_PENDING, &conf->mddev->sb_flags)) अणु
		set_bit(STRIPE_HANDLE, &sh->state);
		जाओ finish;
	पूर्ण

	अगर (unlikely(s.blocked_rdev)) अणु
		अगर (s.syncing || s.expanding || s.expanded ||
		    s.replacing || s.to_ग_लिखो || s.written) अणु
			set_bit(STRIPE_HANDLE, &sh->state);
			जाओ finish;
		पूर्ण
		/* There is nothing क्रम the blocked_rdev to block */
		rdev_dec_pending(s.blocked_rdev, conf->mddev);
		s.blocked_rdev = शून्य;
	पूर्ण

	अगर (s.to_fill && !test_bit(STRIPE_BIOFILL_RUN, &sh->state)) अणु
		set_bit(STRIPE_OP_BIOFILL, &s.ops_request);
		set_bit(STRIPE_BIOFILL_RUN, &sh->state);
	पूर्ण

	pr_debug("locked=%d uptodate=%d to_read=%d"
	       " to_write=%d failed=%d failed_num=%d,%d\n",
	       s.locked, s.uptodate, s.to_पढ़ो, s.to_ग_लिखो, s.failed,
	       s.failed_num[0], s.failed_num[1]);
	/*
	 * check अगर the array has lost more than max_degraded devices and,
	 * अगर so, some requests might need to be failed.
	 *
	 * When journal device failed (log_failed), we will only process
	 * the stripe अगर there is data need ग_लिखो to raid disks
	 */
	अगर (s.failed > conf->max_degraded ||
	    (s.log_failed && s.injournal == 0)) अणु
		sh->check_state = 0;
		sh->reस्थिरruct_state = 0;
		अवरोध_stripe_batch_list(sh, 0);
		अगर (s.to_पढ़ो+s.to_ग_लिखो+s.written)
			handle_failed_stripe(conf, sh, &s, disks);
		अगर (s.syncing + s.replacing)
			handle_failed_sync(conf, sh, &s);
	पूर्ण

	/* Now we check to see अगर any ग_लिखो operations have recently
	 * completed
	 */
	prexor = 0;
	अगर (sh->reस्थिरruct_state == reस्थिरruct_state_prexor_drain_result)
		prexor = 1;
	अगर (sh->reस्थिरruct_state == reस्थिरruct_state_drain_result ||
	    sh->reस्थिरruct_state == reस्थिरruct_state_prexor_drain_result) अणु
		sh->reस्थिरruct_state = reस्थिरruct_state_idle;

		/* All the 'written' buffers and the parity block are पढ़ोy to
		 * be written back to disk
		 */
		BUG_ON(!test_bit(R5_UPTODATE, &sh->dev[sh->pd_idx].flags) &&
		       !test_bit(R5_Discard, &sh->dev[sh->pd_idx].flags));
		BUG_ON(sh->qd_idx >= 0 &&
		       !test_bit(R5_UPTODATE, &sh->dev[sh->qd_idx].flags) &&
		       !test_bit(R5_Discard, &sh->dev[sh->qd_idx].flags));
		क्रम (i = disks; i--; ) अणु
			काष्ठा r5dev *dev = &sh->dev[i];
			अगर (test_bit(R5_LOCKED, &dev->flags) &&
				(i == sh->pd_idx || i == sh->qd_idx ||
				 dev->written || test_bit(R5_InJournal,
							  &dev->flags))) अणु
				pr_debug("Writing block %d\n", i);
				set_bit(R5_Wantग_लिखो, &dev->flags);
				अगर (prexor)
					जारी;
				अगर (s.failed > 1)
					जारी;
				अगर (!test_bit(R5_Insync, &dev->flags) ||
				    ((i == sh->pd_idx || i == sh->qd_idx)  &&
				     s.failed == 0))
					set_bit(STRIPE_INSYNC, &sh->state);
			पूर्ण
		पूर्ण
		अगर (test_and_clear_bit(STRIPE_PREREAD_ACTIVE, &sh->state))
			s.dec_preपढ़ो_active = 1;
	पूर्ण

	/*
	 * might be able to वापस some ग_लिखो requests अगर the parity blocks
	 * are safe, or on a failed drive
	 */
	pdev = &sh->dev[sh->pd_idx];
	s.p_failed = (s.failed >= 1 && s.failed_num[0] == sh->pd_idx)
		|| (s.failed >= 2 && s.failed_num[1] == sh->pd_idx);
	qdev = &sh->dev[sh->qd_idx];
	s.q_failed = (s.failed >= 1 && s.failed_num[0] == sh->qd_idx)
		|| (s.failed >= 2 && s.failed_num[1] == sh->qd_idx)
		|| conf->level < 6;

	अगर (s.written &&
	    (s.p_failed || ((test_bit(R5_Insync, &pdev->flags)
			     && !test_bit(R5_LOCKED, &pdev->flags)
			     && (test_bit(R5_UPTODATE, &pdev->flags) ||
				 test_bit(R5_Discard, &pdev->flags))))) &&
	    (s.q_failed || ((test_bit(R5_Insync, &qdev->flags)
			     && !test_bit(R5_LOCKED, &qdev->flags)
			     && (test_bit(R5_UPTODATE, &qdev->flags) ||
				 test_bit(R5_Discard, &qdev->flags))))))
		handle_stripe_clean_event(conf, sh, disks);

	अगर (s.just_cached)
		r5c_handle_cached_data_endio(conf, sh, disks);
	log_stripe_ग_लिखो_finished(sh);

	/* Now we might consider पढ़ोing some blocks, either to check/generate
	 * parity, or to satisfy requests
	 * or to load a block that is being partially written.
	 */
	अगर (s.to_पढ़ो || s.non_overग_लिखो
	    || (s.to_ग_लिखो && s.failed)
	    || (s.syncing && (s.uptodate + s.compute < disks))
	    || s.replacing
	    || s.expanding)
		handle_stripe_fill(sh, &s, disks);

	/*
	 * When the stripe finishes full journal ग_लिखो cycle (ग_लिखो to journal
	 * and raid disk), this is the clean up procedure so it is पढ़ोy क्रम
	 * next operation.
	 */
	r5c_finish_stripe_ग_लिखो_out(conf, sh, &s);

	/*
	 * Now to consider new ग_लिखो requests, cache ग_लिखो back and what अन्यथा,
	 * अगर anything should be पढ़ो.  We करो not handle new ग_लिखोs when:
	 * 1/ A 'write' operation (copy+xor) is alपढ़ोy in flight.
	 * 2/ A 'check' operation is in flight, as it may clobber the parity
	 *    block.
	 * 3/ A r5c cache log ग_लिखो is in flight.
	 */

	अगर (!sh->reस्थिरruct_state && !sh->check_state && !sh->log_io) अणु
		अगर (!r5c_is_ग_लिखोback(conf->log)) अणु
			अगर (s.to_ग_लिखो)
				handle_stripe_dirtying(conf, sh, &s, disks);
		पूर्ण अन्यथा अणु /* ग_लिखो back cache */
			पूर्णांक ret = 0;

			/* First, try handle ग_लिखोs in caching phase */
			अगर (s.to_ग_लिखो)
				ret = r5c_try_caching_ग_लिखो(conf, sh, &s,
							    disks);
			/*
			 * If caching phase failed: ret == -EAGAIN
			 *    OR
			 * stripe under reclaim: !caching && injournal
			 *
			 * fall back to handle_stripe_dirtying()
			 */
			अगर (ret == -EAGAIN ||
			    /* stripe under reclaim: !caching && injournal */
			    (!test_bit(STRIPE_R5C_CACHING, &sh->state) &&
			     s.injournal > 0)) अणु
				ret = handle_stripe_dirtying(conf, sh, &s,
							     disks);
				अगर (ret == -EAGAIN)
					जाओ finish;
			पूर्ण
		पूर्ण
	पूर्ण

	/* maybe we need to check and possibly fix the parity क्रम this stripe
	 * Any पढ़ोs will alपढ़ोy have been scheduled, so we just see अगर enough
	 * data is available.  The parity check is held off जबतक parity
	 * dependent operations are in flight.
	 */
	अगर (sh->check_state ||
	    (s.syncing && s.locked == 0 &&
	     !test_bit(STRIPE_COMPUTE_RUN, &sh->state) &&
	     !test_bit(STRIPE_INSYNC, &sh->state))) अणु
		अगर (conf->level == 6)
			handle_parity_checks6(conf, sh, &s, disks);
		अन्यथा
			handle_parity_checks5(conf, sh, &s, disks);
	पूर्ण

	अगर ((s.replacing || s.syncing) && s.locked == 0
	    && !test_bit(STRIPE_COMPUTE_RUN, &sh->state)
	    && !test_bit(STRIPE_REPLACED, &sh->state)) अणु
		/* Write out to replacement devices where possible */
		क्रम (i = 0; i < conf->raid_disks; i++)
			अगर (test_bit(R5_NeedReplace, &sh->dev[i].flags)) अणु
				WARN_ON(!test_bit(R5_UPTODATE, &sh->dev[i].flags));
				set_bit(R5_WantReplace, &sh->dev[i].flags);
				set_bit(R5_LOCKED, &sh->dev[i].flags);
				s.locked++;
			पूर्ण
		अगर (s.replacing)
			set_bit(STRIPE_INSYNC, &sh->state);
		set_bit(STRIPE_REPLACED, &sh->state);
	पूर्ण
	अगर ((s.syncing || s.replacing) && s.locked == 0 &&
	    !test_bit(STRIPE_COMPUTE_RUN, &sh->state) &&
	    test_bit(STRIPE_INSYNC, &sh->state)) अणु
		md_करोne_sync(conf->mddev, RAID5_STRIPE_SECTORS(conf), 1);
		clear_bit(STRIPE_SYNCING, &sh->state);
		अगर (test_and_clear_bit(R5_Overlap, &sh->dev[sh->pd_idx].flags))
			wake_up(&conf->रुको_क्रम_overlap);
	पूर्ण

	/* If the failed drives are just a ReadError, then we might need
	 * to progress the repair/check process
	 */
	अगर (s.failed <= conf->max_degraded && !conf->mddev->ro)
		क्रम (i = 0; i < s.failed; i++) अणु
			काष्ठा r5dev *dev = &sh->dev[s.failed_num[i]];
			अगर (test_bit(R5_ReadError, &dev->flags)
			    && !test_bit(R5_LOCKED, &dev->flags)
			    && test_bit(R5_UPTODATE, &dev->flags)
				) अणु
				अगर (!test_bit(R5_ReWrite, &dev->flags)) अणु
					set_bit(R5_Wantग_लिखो, &dev->flags);
					set_bit(R5_ReWrite, &dev->flags);
				पूर्ण अन्यथा
					/* let's पढ़ो it back */
					set_bit(R5_Wantपढ़ो, &dev->flags);
				set_bit(R5_LOCKED, &dev->flags);
				s.locked++;
			पूर्ण
		पूर्ण

	/* Finish reस्थिरruct operations initiated by the expansion process */
	अगर (sh->reस्थिरruct_state == reस्थिरruct_state_result) अणु
		काष्ठा stripe_head *sh_src
			= raid5_get_active_stripe(conf, sh->sector, 1, 1, 1);
		अगर (sh_src && test_bit(STRIPE_EXPAND_SOURCE, &sh_src->state)) अणु
			/* sh cannot be written until sh_src has been पढ़ो.
			 * so arrange क्रम sh to be delayed a little
			 */
			set_bit(STRIPE_DELAYED, &sh->state);
			set_bit(STRIPE_HANDLE, &sh->state);
			अगर (!test_and_set_bit(STRIPE_PREREAD_ACTIVE,
					      &sh_src->state))
				atomic_inc(&conf->preपढ़ो_active_stripes);
			raid5_release_stripe(sh_src);
			जाओ finish;
		पूर्ण
		अगर (sh_src)
			raid5_release_stripe(sh_src);

		sh->reस्थिरruct_state = reस्थिरruct_state_idle;
		clear_bit(STRIPE_EXPANDING, &sh->state);
		क्रम (i = conf->raid_disks; i--; ) अणु
			set_bit(R5_Wantग_लिखो, &sh->dev[i].flags);
			set_bit(R5_LOCKED, &sh->dev[i].flags);
			s.locked++;
		पूर्ण
	पूर्ण

	अगर (s.expanded && test_bit(STRIPE_EXPANDING, &sh->state) &&
	    !sh->reस्थिरruct_state) अणु
		/* Need to ग_लिखो out all blocks after computing parity */
		sh->disks = conf->raid_disks;
		stripe_set_idx(sh->sector, conf, 0, sh);
		schedule_reस्थिरruction(sh, &s, 1, 1);
	पूर्ण अन्यथा अगर (s.expanded && !sh->reस्थिरruct_state && s.locked == 0) अणु
		clear_bit(STRIPE_EXPAND_READY, &sh->state);
		atomic_dec(&conf->reshape_stripes);
		wake_up(&conf->रुको_क्रम_overlap);
		md_करोne_sync(conf->mddev, RAID5_STRIPE_SECTORS(conf), 1);
	पूर्ण

	अगर (s.expanding && s.locked == 0 &&
	    !test_bit(STRIPE_COMPUTE_RUN, &sh->state))
		handle_stripe_expansion(conf, sh);

finish:
	/* रुको क्रम this device to become unblocked */
	अगर (unlikely(s.blocked_rdev)) अणु
		अगर (conf->mddev->बाह्यal)
			md_रुको_क्रम_blocked_rdev(s.blocked_rdev,
						 conf->mddev);
		अन्यथा
			/* Internal metadata will immediately
			 * be written by raid5d, so we करोn't
			 * need to रुको here.
			 */
			rdev_dec_pending(s.blocked_rdev,
					 conf->mddev);
	पूर्ण

	अगर (s.handle_bad_blocks)
		क्रम (i = disks; i--; ) अणु
			काष्ठा md_rdev *rdev;
			काष्ठा r5dev *dev = &sh->dev[i];
			अगर (test_and_clear_bit(R5_WriteError, &dev->flags)) अणु
				/* We own a safe reference to the rdev */
				rdev = conf->disks[i].rdev;
				अगर (!rdev_set_badblocks(rdev, sh->sector,
							RAID5_STRIPE_SECTORS(conf), 0))
					md_error(conf->mddev, rdev);
				rdev_dec_pending(rdev, conf->mddev);
			पूर्ण
			अगर (test_and_clear_bit(R5_MadeGood, &dev->flags)) अणु
				rdev = conf->disks[i].rdev;
				rdev_clear_badblocks(rdev, sh->sector,
						     RAID5_STRIPE_SECTORS(conf), 0);
				rdev_dec_pending(rdev, conf->mddev);
			पूर्ण
			अगर (test_and_clear_bit(R5_MadeGoodRepl, &dev->flags)) अणु
				rdev = conf->disks[i].replacement;
				अगर (!rdev)
					/* rdev have been moved करोwn */
					rdev = conf->disks[i].rdev;
				rdev_clear_badblocks(rdev, sh->sector,
						     RAID5_STRIPE_SECTORS(conf), 0);
				rdev_dec_pending(rdev, conf->mddev);
			पूर्ण
		पूर्ण

	अगर (s.ops_request)
		raid_run_ops(sh, s.ops_request);

	ops_run_io(sh, &s);

	अगर (s.dec_preपढ़ो_active) अणु
		/* We delay this until after ops_run_io so that अगर make_request
		 * is रुकोing on a flush, it won't जारी until the ग_लिखोs
		 * have actually been submitted.
		 */
		atomic_dec(&conf->preपढ़ो_active_stripes);
		अगर (atomic_पढ़ो(&conf->preपढ़ो_active_stripes) <
		    IO_THRESHOLD)
			md_wakeup_thपढ़ो(conf->mddev->thपढ़ो);
	पूर्ण

	clear_bit_unlock(STRIPE_ACTIVE, &sh->state);
पूर्ण

अटल व्योम raid5_activate_delayed(काष्ठा r5conf *conf)
अणु
	अगर (atomic_पढ़ो(&conf->preपढ़ो_active_stripes) < IO_THRESHOLD) अणु
		जबतक (!list_empty(&conf->delayed_list)) अणु
			काष्ठा list_head *l = conf->delayed_list.next;
			काष्ठा stripe_head *sh;
			sh = list_entry(l, काष्ठा stripe_head, lru);
			list_del_init(l);
			clear_bit(STRIPE_DELAYED, &sh->state);
			अगर (!test_and_set_bit(STRIPE_PREREAD_ACTIVE, &sh->state))
				atomic_inc(&conf->preपढ़ो_active_stripes);
			list_add_tail(&sh->lru, &conf->hold_list);
			raid5_wakeup_stripe_thपढ़ो(sh);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम activate_bit_delay(काष्ठा r5conf *conf,
	काष्ठा list_head *temp_inactive_list)
अणु
	/* device_lock is held */
	काष्ठा list_head head;
	list_add(&head, &conf->biपंचांगap_list);
	list_del_init(&conf->biपंचांगap_list);
	जबतक (!list_empty(&head)) अणु
		काष्ठा stripe_head *sh = list_entry(head.next, काष्ठा stripe_head, lru);
		पूर्णांक hash;
		list_del_init(&sh->lru);
		atomic_inc(&sh->count);
		hash = sh->hash_lock_index;
		__release_stripe(conf, sh, &temp_inactive_list[hash]);
	पूर्ण
पूर्ण

अटल पूर्णांक in_chunk_boundary(काष्ठा mddev *mddev, काष्ठा bio *bio)
अणु
	काष्ठा r5conf *conf = mddev->निजी;
	sector_t sector = bio->bi_iter.bi_sector;
	अचिन्हित पूर्णांक chunk_sectors;
	अचिन्हित पूर्णांक bio_sectors = bio_sectors(bio);

	chunk_sectors = min(conf->chunk_sectors, conf->prev_chunk_sectors);
	वापस  chunk_sectors >=
		((sector & (chunk_sectors - 1)) + bio_sectors);
पूर्ण

/*
 *  add bio to the retry LIFO  ( in O(1) ... we are in पूर्णांकerrupt )
 *  later sampled by raid5d.
 */
अटल व्योम add_bio_to_retry(काष्ठा bio *bi,काष्ठा r5conf *conf)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&conf->device_lock, flags);

	bi->bi_next = conf->retry_पढ़ो_aligned_list;
	conf->retry_पढ़ो_aligned_list = bi;

	spin_unlock_irqrestore(&conf->device_lock, flags);
	md_wakeup_thपढ़ो(conf->mddev->thपढ़ो);
पूर्ण

अटल काष्ठा bio *हटाओ_bio_from_retry(काष्ठा r5conf *conf,
					 अचिन्हित पूर्णांक *offset)
अणु
	काष्ठा bio *bi;

	bi = conf->retry_पढ़ो_aligned;
	अगर (bi) अणु
		*offset = conf->retry_पढ़ो_offset;
		conf->retry_पढ़ो_aligned = शून्य;
		वापस bi;
	पूर्ण
	bi = conf->retry_पढ़ो_aligned_list;
	अगर(bi) अणु
		conf->retry_पढ़ो_aligned_list = bi->bi_next;
		bi->bi_next = शून्य;
		*offset = 0;
	पूर्ण

	वापस bi;
पूर्ण

/*
 *  The "raid5_align_endio" should check अगर the पढ़ो succeeded and अगर it
 *  did, call bio_endio on the original bio (having bio_put the new bio
 *  first).
 *  If the पढ़ो failed..
 */
अटल व्योम raid5_align_endio(काष्ठा bio *bi)
अणु
	काष्ठा bio* raid_bi  = bi->bi_निजी;
	काष्ठा mddev *mddev;
	काष्ठा r5conf *conf;
	काष्ठा md_rdev *rdev;
	blk_status_t error = bi->bi_status;

	bio_put(bi);

	rdev = (व्योम*)raid_bi->bi_next;
	raid_bi->bi_next = शून्य;
	mddev = rdev->mddev;
	conf = mddev->निजी;

	rdev_dec_pending(rdev, conf->mddev);

	अगर (!error) अणु
		bio_endio(raid_bi);
		अगर (atomic_dec_and_test(&conf->active_aligned_पढ़ोs))
			wake_up(&conf->रुको_क्रम_quiescent);
		वापस;
	पूर्ण

	pr_debug("raid5_align_endio : io error...handing IO for a retry\n");

	add_bio_to_retry(raid_bi, conf);
पूर्ण

अटल पूर्णांक raid5_पढ़ो_one_chunk(काष्ठा mddev *mddev, काष्ठा bio *raid_bio)
अणु
	काष्ठा r5conf *conf = mddev->निजी;
	काष्ठा bio *align_bio;
	काष्ठा md_rdev *rdev;
	sector_t sector, end_sector, first_bad;
	पूर्णांक bad_sectors, dd_idx;

	अगर (!in_chunk_boundary(mddev, raid_bio)) अणु
		pr_debug("%s: non aligned\n", __func__);
		वापस 0;
	पूर्ण

	sector = raid5_compute_sector(conf, raid_bio->bi_iter.bi_sector, 0,
				      &dd_idx, शून्य);
	end_sector = bio_end_sector(raid_bio);

	rcu_पढ़ो_lock();
	अगर (r5c_big_stripe_cached(conf, sector))
		जाओ out_rcu_unlock;

	rdev = rcu_dereference(conf->disks[dd_idx].replacement);
	अगर (!rdev || test_bit(Faulty, &rdev->flags) ||
	    rdev->recovery_offset < end_sector) अणु
		rdev = rcu_dereference(conf->disks[dd_idx].rdev);
		अगर (!rdev)
			जाओ out_rcu_unlock;
		अगर (test_bit(Faulty, &rdev->flags) ||
		    !(test_bit(In_sync, &rdev->flags) ||
		      rdev->recovery_offset >= end_sector))
			जाओ out_rcu_unlock;
	पूर्ण

	atomic_inc(&rdev->nr_pending);
	rcu_पढ़ो_unlock();

	align_bio = bio_clone_fast(raid_bio, GFP_NOIO, &mddev->bio_set);
	bio_set_dev(align_bio, rdev->bdev);
	align_bio->bi_end_io = raid5_align_endio;
	align_bio->bi_निजी = raid_bio;
	align_bio->bi_iter.bi_sector = sector;

	raid_bio->bi_next = (व्योम *)rdev;

	अगर (is_badblock(rdev, sector, bio_sectors(align_bio), &first_bad,
			&bad_sectors)) अणु
		bio_put(align_bio);
		rdev_dec_pending(rdev, mddev);
		वापस 0;
	पूर्ण

	/* No reshape active, so we can trust rdev->data_offset */
	align_bio->bi_iter.bi_sector += rdev->data_offset;

	spin_lock_irq(&conf->device_lock);
	रुको_event_lock_irq(conf->रुको_क्रम_quiescent, conf->quiesce == 0,
			    conf->device_lock);
	atomic_inc(&conf->active_aligned_पढ़ोs);
	spin_unlock_irq(&conf->device_lock);

	अगर (mddev->gendisk)
		trace_block_bio_remap(align_bio, disk_devt(mddev->gendisk),
				      raid_bio->bi_iter.bi_sector);
	submit_bio_noacct(align_bio);
	वापस 1;

out_rcu_unlock:
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

अटल काष्ठा bio *chunk_aligned_पढ़ो(काष्ठा mddev *mddev, काष्ठा bio *raid_bio)
अणु
	काष्ठा bio *split;
	sector_t sector = raid_bio->bi_iter.bi_sector;
	अचिन्हित chunk_sects = mddev->chunk_sectors;
	अचिन्हित sectors = chunk_sects - (sector & (chunk_sects-1));

	अगर (sectors < bio_sectors(raid_bio)) अणु
		काष्ठा r5conf *conf = mddev->निजी;
		split = bio_split(raid_bio, sectors, GFP_NOIO, &conf->bio_split);
		bio_chain(split, raid_bio);
		submit_bio_noacct(raid_bio);
		raid_bio = split;
	पूर्ण

	अगर (!raid5_पढ़ो_one_chunk(mddev, raid_bio))
		वापस raid_bio;

	वापस शून्य;
पूर्ण

/* __get_priority_stripe - get the next stripe to process
 *
 * Full stripe ग_लिखोs are allowed to pass preपढ़ो active stripes up until
 * the bypass_threshold is exceeded.  In general the bypass_count
 * increments when the handle_list is handled beक्रमe the hold_list; however, it
 * will not be incremented when STRIPE_IO_STARTED is sampled set signअगरying a
 * stripe with in flight i/o.  The bypass_count will be reset when the
 * head of the hold_list has changed, i.e. the head was promoted to the
 * handle_list.
 */
अटल काष्ठा stripe_head *__get_priority_stripe(काष्ठा r5conf *conf, पूर्णांक group)
अणु
	काष्ठा stripe_head *sh, *पंचांगp;
	काष्ठा list_head *handle_list = शून्य;
	काष्ठा r5worker_group *wg;
	bool second_try = !r5c_is_ग_लिखोback(conf->log) &&
		!r5l_log_disk_error(conf);
	bool try_loprio = test_bit(R5C_LOG_TIGHT, &conf->cache_state) ||
		r5l_log_disk_error(conf);

again:
	wg = शून्य;
	sh = शून्य;
	अगर (conf->worker_cnt_per_group == 0) अणु
		handle_list = try_loprio ? &conf->loprio_list :
					&conf->handle_list;
	पूर्ण अन्यथा अगर (group != ANY_GROUP) अणु
		handle_list = try_loprio ? &conf->worker_groups[group].loprio_list :
				&conf->worker_groups[group].handle_list;
		wg = &conf->worker_groups[group];
	पूर्ण अन्यथा अणु
		पूर्णांक i;
		क्रम (i = 0; i < conf->group_cnt; i++) अणु
			handle_list = try_loprio ? &conf->worker_groups[i].loprio_list :
				&conf->worker_groups[i].handle_list;
			wg = &conf->worker_groups[i];
			अगर (!list_empty(handle_list))
				अवरोध;
		पूर्ण
	पूर्ण

	pr_debug("%s: handle: %s hold: %s full_writes: %d bypass_count: %d\n",
		  __func__,
		  list_empty(handle_list) ? "empty" : "busy",
		  list_empty(&conf->hold_list) ? "empty" : "busy",
		  atomic_पढ़ो(&conf->pending_full_ग_लिखोs), conf->bypass_count);

	अगर (!list_empty(handle_list)) अणु
		sh = list_entry(handle_list->next, typeof(*sh), lru);

		अगर (list_empty(&conf->hold_list))
			conf->bypass_count = 0;
		अन्यथा अगर (!test_bit(STRIPE_IO_STARTED, &sh->state)) अणु
			अगर (conf->hold_list.next == conf->last_hold)
				conf->bypass_count++;
			अन्यथा अणु
				conf->last_hold = conf->hold_list.next;
				conf->bypass_count -= conf->bypass_threshold;
				अगर (conf->bypass_count < 0)
					conf->bypass_count = 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (!list_empty(&conf->hold_list) &&
		   ((conf->bypass_threshold &&
		     conf->bypass_count > conf->bypass_threshold) ||
		    atomic_पढ़ो(&conf->pending_full_ग_लिखोs) == 0)) अणु

		list_क्रम_each_entry(पंचांगp, &conf->hold_list,  lru) अणु
			अगर (conf->worker_cnt_per_group == 0 ||
			    group == ANY_GROUP ||
			    !cpu_online(पंचांगp->cpu) ||
			    cpu_to_group(पंचांगp->cpu) == group) अणु
				sh = पंचांगp;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (sh) अणु
			conf->bypass_count -= conf->bypass_threshold;
			अगर (conf->bypass_count < 0)
				conf->bypass_count = 0;
		पूर्ण
		wg = शून्य;
	पूर्ण

	अगर (!sh) अणु
		अगर (second_try)
			वापस शून्य;
		second_try = true;
		try_loprio = !try_loprio;
		जाओ again;
	पूर्ण

	अगर (wg) अणु
		wg->stripes_cnt--;
		sh->group = शून्य;
	पूर्ण
	list_del_init(&sh->lru);
	BUG_ON(atomic_inc_वापस(&sh->count) != 1);
	वापस sh;
पूर्ण

काष्ठा raid5_plug_cb अणु
	काष्ठा blk_plug_cb	cb;
	काष्ठा list_head	list;
	काष्ठा list_head	temp_inactive_list[NR_STRIPE_HASH_LOCKS];
पूर्ण;

अटल व्योम raid5_unplug(काष्ठा blk_plug_cb *blk_cb, bool from_schedule)
अणु
	काष्ठा raid5_plug_cb *cb = container_of(
		blk_cb, काष्ठा raid5_plug_cb, cb);
	काष्ठा stripe_head *sh;
	काष्ठा mddev *mddev = cb->cb.data;
	काष्ठा r5conf *conf = mddev->निजी;
	पूर्णांक cnt = 0;
	पूर्णांक hash;

	अगर (cb->list.next && !list_empty(&cb->list)) अणु
		spin_lock_irq(&conf->device_lock);
		जबतक (!list_empty(&cb->list)) अणु
			sh = list_first_entry(&cb->list, काष्ठा stripe_head, lru);
			list_del_init(&sh->lru);
			/*
			 * aव्योम race release_stripe_plug() sees
			 * STRIPE_ON_UNPLUG_LIST clear but the stripe
			 * is still in our list
			 */
			smp_mb__beक्रमe_atomic();
			clear_bit(STRIPE_ON_UNPLUG_LIST, &sh->state);
			/*
			 * STRIPE_ON_RELEASE_LIST could be set here. In that
			 * हाल, the count is always > 1 here
			 */
			hash = sh->hash_lock_index;
			__release_stripe(conf, sh, &cb->temp_inactive_list[hash]);
			cnt++;
		पूर्ण
		spin_unlock_irq(&conf->device_lock);
	पूर्ण
	release_inactive_stripe_list(conf, cb->temp_inactive_list,
				     NR_STRIPE_HASH_LOCKS);
	अगर (mddev->queue)
		trace_block_unplug(mddev->queue, cnt, !from_schedule);
	kमुक्त(cb);
पूर्ण

अटल व्योम release_stripe_plug(काष्ठा mddev *mddev,
				काष्ठा stripe_head *sh)
अणु
	काष्ठा blk_plug_cb *blk_cb = blk_check_plugged(
		raid5_unplug, mddev,
		माप(काष्ठा raid5_plug_cb));
	काष्ठा raid5_plug_cb *cb;

	अगर (!blk_cb) अणु
		raid5_release_stripe(sh);
		वापस;
	पूर्ण

	cb = container_of(blk_cb, काष्ठा raid5_plug_cb, cb);

	अगर (cb->list.next == शून्य) अणु
		पूर्णांक i;
		INIT_LIST_HEAD(&cb->list);
		क्रम (i = 0; i < NR_STRIPE_HASH_LOCKS; i++)
			INIT_LIST_HEAD(cb->temp_inactive_list + i);
	पूर्ण

	अगर (!test_and_set_bit(STRIPE_ON_UNPLUG_LIST, &sh->state))
		list_add_tail(&sh->lru, &cb->list);
	अन्यथा
		raid5_release_stripe(sh);
पूर्ण

अटल व्योम make_discard_request(काष्ठा mddev *mddev, काष्ठा bio *bi)
अणु
	काष्ठा r5conf *conf = mddev->निजी;
	sector_t logical_sector, last_sector;
	काष्ठा stripe_head *sh;
	पूर्णांक stripe_sectors;

	अगर (mddev->reshape_position != MaxSector)
		/* Skip discard जबतक reshape is happening */
		वापस;

	logical_sector = bi->bi_iter.bi_sector & ~((sector_t)RAID5_STRIPE_SECTORS(conf)-1);
	last_sector = bio_end_sector(bi);

	bi->bi_next = शून्य;

	stripe_sectors = conf->chunk_sectors *
		(conf->raid_disks - conf->max_degraded);
	logical_sector = DIV_ROUND_UP_SECTOR_T(logical_sector,
					       stripe_sectors);
	sector_भाग(last_sector, stripe_sectors);

	logical_sector *= conf->chunk_sectors;
	last_sector *= conf->chunk_sectors;

	क्रम (; logical_sector < last_sector;
	     logical_sector += RAID5_STRIPE_SECTORS(conf)) अणु
		DEFINE_WAIT(w);
		पूर्णांक d;
	again:
		sh = raid5_get_active_stripe(conf, logical_sector, 0, 0, 0);
		prepare_to_रुको(&conf->रुको_क्रम_overlap, &w,
				TASK_UNINTERRUPTIBLE);
		set_bit(R5_Overlap, &sh->dev[sh->pd_idx].flags);
		अगर (test_bit(STRIPE_SYNCING, &sh->state)) अणु
			raid5_release_stripe(sh);
			schedule();
			जाओ again;
		पूर्ण
		clear_bit(R5_Overlap, &sh->dev[sh->pd_idx].flags);
		spin_lock_irq(&sh->stripe_lock);
		क्रम (d = 0; d < conf->raid_disks; d++) अणु
			अगर (d == sh->pd_idx || d == sh->qd_idx)
				जारी;
			अगर (sh->dev[d].toग_लिखो || sh->dev[d].toपढ़ो) अणु
				set_bit(R5_Overlap, &sh->dev[d].flags);
				spin_unlock_irq(&sh->stripe_lock);
				raid5_release_stripe(sh);
				schedule();
				जाओ again;
			पूर्ण
		पूर्ण
		set_bit(STRIPE_DISCARD, &sh->state);
		finish_रुको(&conf->रुको_क्रम_overlap, &w);
		sh->overग_लिखो_disks = 0;
		क्रम (d = 0; d < conf->raid_disks; d++) अणु
			अगर (d == sh->pd_idx || d == sh->qd_idx)
				जारी;
			sh->dev[d].toग_लिखो = bi;
			set_bit(R5_OVERWRITE, &sh->dev[d].flags);
			bio_inc_reमुख्यing(bi);
			md_ग_लिखो_inc(mddev, bi);
			sh->overग_लिखो_disks++;
		पूर्ण
		spin_unlock_irq(&sh->stripe_lock);
		अगर (conf->mddev->biपंचांगap) अणु
			क्रम (d = 0;
			     d < conf->raid_disks - conf->max_degraded;
			     d++)
				md_biपंचांगap_startग_लिखो(mddev->biपंचांगap,
						     sh->sector,
						     RAID5_STRIPE_SECTORS(conf),
						     0);
			sh->bm_seq = conf->seq_flush + 1;
			set_bit(STRIPE_BIT_DELAY, &sh->state);
		पूर्ण

		set_bit(STRIPE_HANDLE, &sh->state);
		clear_bit(STRIPE_DELAYED, &sh->state);
		अगर (!test_and_set_bit(STRIPE_PREREAD_ACTIVE, &sh->state))
			atomic_inc(&conf->preपढ़ो_active_stripes);
		release_stripe_plug(mddev, sh);
	पूर्ण

	bio_endio(bi);
पूर्ण

अटल bool raid5_make_request(काष्ठा mddev *mddev, काष्ठा bio * bi)
अणु
	काष्ठा r5conf *conf = mddev->निजी;
	पूर्णांक dd_idx;
	sector_t new_sector;
	sector_t logical_sector, last_sector;
	काष्ठा stripe_head *sh;
	स्थिर पूर्णांक rw = bio_data_dir(bi);
	DEFINE_WAIT(w);
	bool करो_prepare;
	bool करो_flush = false;

	अगर (unlikely(bi->bi_opf & REQ_PREFLUSH)) अणु
		पूर्णांक ret = log_handle_flush_request(conf, bi);

		अगर (ret == 0)
			वापस true;
		अगर (ret == -ENODEV) अणु
			अगर (md_flush_request(mddev, bi))
				वापस true;
		पूर्ण
		/* ret == -EAGAIN, fallback */
		/*
		 * अगर r5l_handle_flush_request() didn't clear REQ_PREFLUSH,
		 * we need to flush journal device
		 */
		करो_flush = bi->bi_opf & REQ_PREFLUSH;
	पूर्ण

	अगर (!md_ग_लिखो_start(mddev, bi))
		वापस false;
	/*
	 * If array is degraded, better not करो chunk aligned पढ़ो because
	 * later we might have to पढ़ो it again in order to reस्थिरruct
	 * data on failed drives.
	 */
	अगर (rw == READ && mddev->degraded == 0 &&
	    mddev->reshape_position == MaxSector) अणु
		bi = chunk_aligned_पढ़ो(mddev, bi);
		अगर (!bi)
			वापस true;
	पूर्ण

	अगर (unlikely(bio_op(bi) == REQ_OP_DISCARD)) अणु
		make_discard_request(mddev, bi);
		md_ग_लिखो_end(mddev);
		वापस true;
	पूर्ण

	logical_sector = bi->bi_iter.bi_sector & ~((sector_t)RAID5_STRIPE_SECTORS(conf)-1);
	last_sector = bio_end_sector(bi);
	bi->bi_next = शून्य;

	prepare_to_रुको(&conf->रुको_क्रम_overlap, &w, TASK_UNINTERRUPTIBLE);
	क्रम (; logical_sector < last_sector; logical_sector += RAID5_STRIPE_SECTORS(conf)) अणु
		पूर्णांक previous;
		पूर्णांक seq;

		करो_prepare = false;
	retry:
		seq = पढ़ो_seqcount_begin(&conf->gen_lock);
		previous = 0;
		अगर (करो_prepare)
			prepare_to_रुको(&conf->रुको_क्रम_overlap, &w,
				TASK_UNINTERRUPTIBLE);
		अगर (unlikely(conf->reshape_progress != MaxSector)) अणु
			/* spinlock is needed as reshape_progress may be
			 * 64bit on a 32bit platक्रमm, and so it might be
			 * possible to see a half-updated value
			 * Of course reshape_progress could change after
			 * the lock is dropped, so once we get a reference
			 * to the stripe that we think it is, we will have
			 * to check again.
			 */
			spin_lock_irq(&conf->device_lock);
			अगर (mddev->reshape_backwards
			    ? logical_sector < conf->reshape_progress
			    : logical_sector >= conf->reshape_progress) अणु
				previous = 1;
			पूर्ण अन्यथा अणु
				अगर (mddev->reshape_backwards
				    ? logical_sector < conf->reshape_safe
				    : logical_sector >= conf->reshape_safe) अणु
					spin_unlock_irq(&conf->device_lock);
					schedule();
					करो_prepare = true;
					जाओ retry;
				पूर्ण
			पूर्ण
			spin_unlock_irq(&conf->device_lock);
		पूर्ण

		new_sector = raid5_compute_sector(conf, logical_sector,
						  previous,
						  &dd_idx, शून्य);
		pr_debug("raid456: raid5_make_request, sector %llu logical %llu\n",
			(अचिन्हित दीर्घ दीर्घ)new_sector,
			(अचिन्हित दीर्घ दीर्घ)logical_sector);

		sh = raid5_get_active_stripe(conf, new_sector, previous,
				       (bi->bi_opf & REQ_RAHEAD), 0);
		अगर (sh) अणु
			अगर (unlikely(previous)) अणु
				/* expansion might have moved on जबतक रुकोing क्रम a
				 * stripe, so we must करो the range check again.
				 * Expansion could still move past after this
				 * test, but as we are holding a reference to
				 * 'sh', we know that अगर that happens,
				 *  STRIPE_EXPANDING will get set and the expansion
				 * won't proceed until we finish with the stripe.
				 */
				पूर्णांक must_retry = 0;
				spin_lock_irq(&conf->device_lock);
				अगर (mddev->reshape_backwards
				    ? logical_sector >= conf->reshape_progress
				    : logical_sector < conf->reshape_progress)
					/* mismatch, need to try again */
					must_retry = 1;
				spin_unlock_irq(&conf->device_lock);
				अगर (must_retry) अणु
					raid5_release_stripe(sh);
					schedule();
					करो_prepare = true;
					जाओ retry;
				पूर्ण
			पूर्ण
			अगर (पढ़ो_seqcount_retry(&conf->gen_lock, seq)) अणु
				/* Might have got the wrong stripe_head
				 * by accident
				 */
				raid5_release_stripe(sh);
				जाओ retry;
			पूर्ण

			अगर (test_bit(STRIPE_EXPANDING, &sh->state) ||
			    !add_stripe_bio(sh, bi, dd_idx, rw, previous)) अणु
				/* Stripe is busy expanding or
				 * add failed due to overlap.  Flush everything
				 * and रुको a जबतक
				 */
				md_wakeup_thपढ़ो(mddev->thपढ़ो);
				raid5_release_stripe(sh);
				schedule();
				करो_prepare = true;
				जाओ retry;
			पूर्ण
			अगर (करो_flush) अणु
				set_bit(STRIPE_R5C_PREFLUSH, &sh->state);
				/* we only need flush क्रम one stripe */
				करो_flush = false;
			पूर्ण

			set_bit(STRIPE_HANDLE, &sh->state);
			clear_bit(STRIPE_DELAYED, &sh->state);
			अगर ((!sh->batch_head || sh == sh->batch_head) &&
			    (bi->bi_opf & REQ_SYNC) &&
			    !test_and_set_bit(STRIPE_PREREAD_ACTIVE, &sh->state))
				atomic_inc(&conf->preपढ़ो_active_stripes);
			release_stripe_plug(mddev, sh);
		पूर्ण अन्यथा अणु
			/* cannot get stripe क्रम पढ़ो-ahead, just give-up */
			bi->bi_status = BLK_STS_IOERR;
			अवरोध;
		पूर्ण
	पूर्ण
	finish_रुको(&conf->रुको_क्रम_overlap, &w);

	अगर (rw == WRITE)
		md_ग_लिखो_end(mddev);
	bio_endio(bi);
	वापस true;
पूर्ण

अटल sector_t raid5_size(काष्ठा mddev *mddev, sector_t sectors, पूर्णांक raid_disks);

अटल sector_t reshape_request(काष्ठा mddev *mddev, sector_t sector_nr, पूर्णांक *skipped)
अणु
	/* reshaping is quite dअगरferent to recovery/resync so it is
	 * handled quite separately ... here.
	 *
	 * On each call to sync_request, we gather one chunk worth of
	 * destination stripes and flag them as expanding.
	 * Then we find all the source stripes and request पढ़ोs.
	 * As the पढ़ोs complete, handle_stripe will copy the data
	 * पूर्णांकo the destination stripe and release that stripe.
	 */
	काष्ठा r5conf *conf = mddev->निजी;
	काष्ठा stripe_head *sh;
	काष्ठा md_rdev *rdev;
	sector_t first_sector, last_sector;
	पूर्णांक raid_disks = conf->previous_raid_disks;
	पूर्णांक data_disks = raid_disks - conf->max_degraded;
	पूर्णांक new_data_disks = conf->raid_disks - conf->max_degraded;
	पूर्णांक i;
	पूर्णांक dd_idx;
	sector_t ग_लिखोpos, पढ़ोpos, safepos;
	sector_t stripe_addr;
	पूर्णांक reshape_sectors;
	काष्ठा list_head stripes;
	sector_t retn;

	अगर (sector_nr == 0) अणु
		/* If restarting in the middle, skip the initial sectors */
		अगर (mddev->reshape_backwards &&
		    conf->reshape_progress < raid5_size(mddev, 0, 0)) अणु
			sector_nr = raid5_size(mddev, 0, 0)
				- conf->reshape_progress;
		पूर्ण अन्यथा अगर (mddev->reshape_backwards &&
			   conf->reshape_progress == MaxSector) अणु
			/* shouldn't happen, but just in हाल, finish up.*/
			sector_nr = MaxSector;
		पूर्ण अन्यथा अगर (!mddev->reshape_backwards &&
			   conf->reshape_progress > 0)
			sector_nr = conf->reshape_progress;
		sector_भाग(sector_nr, new_data_disks);
		अगर (sector_nr) अणु
			mddev->curr_resync_completed = sector_nr;
			sysfs_notअगरy_dirent_safe(mddev->sysfs_completed);
			*skipped = 1;
			retn = sector_nr;
			जाओ finish;
		पूर्ण
	पूर्ण

	/* We need to process a full chunk at a समय.
	 * If old and new chunk sizes dअगरfer, we need to process the
	 * largest of these
	 */

	reshape_sectors = max(conf->chunk_sectors, conf->prev_chunk_sectors);

	/* We update the metadata at least every 10 seconds, or when
	 * the data about to be copied would over-ग_लिखो the source of
	 * the data at the front of the range.  i.e. one new_stripe
	 * aदीर्घ from reshape_progress new_maps to after where
	 * reshape_safe old_maps to
	 */
	ग_लिखोpos = conf->reshape_progress;
	sector_भाग(ग_लिखोpos, new_data_disks);
	पढ़ोpos = conf->reshape_progress;
	sector_भाग(पढ़ोpos, data_disks);
	safepos = conf->reshape_safe;
	sector_भाग(safepos, data_disks);
	अगर (mddev->reshape_backwards) अणु
		BUG_ON(ग_लिखोpos < reshape_sectors);
		ग_लिखोpos -= reshape_sectors;
		पढ़ोpos += reshape_sectors;
		safepos += reshape_sectors;
	पूर्ण अन्यथा अणु
		ग_लिखोpos += reshape_sectors;
		/* पढ़ोpos and safepos are worst-हाल calculations.
		 * A negative number is overly pessimistic, and causes
		 * obvious problems क्रम अचिन्हित storage.  So clip to 0.
		 */
		पढ़ोpos -= min_t(sector_t, reshape_sectors, पढ़ोpos);
		safepos -= min_t(sector_t, reshape_sectors, safepos);
	पूर्ण

	/* Having calculated the 'writepos' possibly use it
	 * to set 'stripe_addr' which is where we will ग_लिखो to.
	 */
	अगर (mddev->reshape_backwards) अणु
		BUG_ON(conf->reshape_progress == 0);
		stripe_addr = ग_लिखोpos;
		BUG_ON((mddev->dev_sectors &
			~((sector_t)reshape_sectors - 1))
		       - reshape_sectors - stripe_addr
		       != sector_nr);
	पूर्ण अन्यथा अणु
		BUG_ON(ग_लिखोpos != sector_nr + reshape_sectors);
		stripe_addr = sector_nr;
	पूर्ण

	/* 'writepos' is the most advanced device address we might ग_लिखो.
	 * 'readpos' is the least advanced device address we might पढ़ो.
	 * 'safepos' is the least address recorded in the metadata as having
	 *     been reshaped.
	 * If there is a min_offset_dअगरf, these are adjusted either by
	 * increasing the safepos/पढ़ोpos अगर dअगरf is negative, or
	 * increasing ग_लिखोpos अगर dअगरf is positive.
	 * If 'readpos' is then behind 'writepos', there is no way that we can
	 * ensure safety in the face of a crash - that must be करोne by userspace
	 * making a backup of the data.  So in that हाल there is no particular
	 * rush to update metadata.
	 * Otherwise अगर 'safepos' is behind 'writepos', then we really need to
	 * update the metadata to advance 'safepos' to match 'readpos' so that
	 * we can be safe in the event of a crash.
	 * So we insist on updating metadata अगर safepos is behind ग_लिखोpos and
	 * पढ़ोpos is beyond ग_लिखोpos.
	 * In any हाल, update the metadata every 10 seconds.
	 * Maybe that number should be configurable, but I'm not sure it is
	 * worth it.... maybe it could be a multiple of safemode_delay???
	 */
	अगर (conf->min_offset_dअगरf < 0) अणु
		safepos += -conf->min_offset_dअगरf;
		पढ़ोpos += -conf->min_offset_dअगरf;
	पूर्ण अन्यथा
		ग_लिखोpos += conf->min_offset_dअगरf;

	अगर ((mddev->reshape_backwards
	     ? (safepos > ग_लिखोpos && पढ़ोpos < ग_लिखोpos)
	     : (safepos < ग_लिखोpos && पढ़ोpos > ग_लिखोpos)) ||
	    समय_after(jअगरfies, conf->reshape_checkpoपूर्णांक + 10*HZ)) अणु
		/* Cannot proceed until we've updated the superblock... */
		रुको_event(conf->रुको_क्रम_overlap,
			   atomic_पढ़ो(&conf->reshape_stripes)==0
			   || test_bit(MD_RECOVERY_INTR, &mddev->recovery));
		अगर (atomic_पढ़ो(&conf->reshape_stripes) != 0)
			वापस 0;
		mddev->reshape_position = conf->reshape_progress;
		mddev->curr_resync_completed = sector_nr;
		अगर (!mddev->reshape_backwards)
			/* Can update recovery_offset */
			rdev_क्रम_each(rdev, mddev)
				अगर (rdev->raid_disk >= 0 &&
				    !test_bit(Journal, &rdev->flags) &&
				    !test_bit(In_sync, &rdev->flags) &&
				    rdev->recovery_offset < sector_nr)
					rdev->recovery_offset = sector_nr;

		conf->reshape_checkpoपूर्णांक = jअगरfies;
		set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
		md_wakeup_thपढ़ो(mddev->thपढ़ो);
		रुको_event(mddev->sb_रुको, mddev->sb_flags == 0 ||
			   test_bit(MD_RECOVERY_INTR, &mddev->recovery));
		अगर (test_bit(MD_RECOVERY_INTR, &mddev->recovery))
			वापस 0;
		spin_lock_irq(&conf->device_lock);
		conf->reshape_safe = mddev->reshape_position;
		spin_unlock_irq(&conf->device_lock);
		wake_up(&conf->रुको_क्रम_overlap);
		sysfs_notअगरy_dirent_safe(mddev->sysfs_completed);
	पूर्ण

	INIT_LIST_HEAD(&stripes);
	क्रम (i = 0; i < reshape_sectors; i += RAID5_STRIPE_SECTORS(conf)) अणु
		पूर्णांक j;
		पूर्णांक skipped_disk = 0;
		sh = raid5_get_active_stripe(conf, stripe_addr+i, 0, 0, 1);
		set_bit(STRIPE_EXPANDING, &sh->state);
		atomic_inc(&conf->reshape_stripes);
		/* If any of this stripe is beyond the end of the old
		 * array, then we need to zero those blocks
		 */
		क्रम (j=sh->disks; j--;) अणु
			sector_t s;
			अगर (j == sh->pd_idx)
				जारी;
			अगर (conf->level == 6 &&
			    j == sh->qd_idx)
				जारी;
			s = raid5_compute_blocknr(sh, j, 0);
			अगर (s < raid5_size(mddev, 0, 0)) अणु
				skipped_disk = 1;
				जारी;
			पूर्ण
			स_रखो(page_address(sh->dev[j].page), 0, RAID5_STRIPE_SIZE(conf));
			set_bit(R5_Expanded, &sh->dev[j].flags);
			set_bit(R5_UPTODATE, &sh->dev[j].flags);
		पूर्ण
		अगर (!skipped_disk) अणु
			set_bit(STRIPE_EXPAND_READY, &sh->state);
			set_bit(STRIPE_HANDLE, &sh->state);
		पूर्ण
		list_add(&sh->lru, &stripes);
	पूर्ण
	spin_lock_irq(&conf->device_lock);
	अगर (mddev->reshape_backwards)
		conf->reshape_progress -= reshape_sectors * new_data_disks;
	अन्यथा
		conf->reshape_progress += reshape_sectors * new_data_disks;
	spin_unlock_irq(&conf->device_lock);
	/* Ok, those stripe are पढ़ोy. We can start scheduling
	 * पढ़ोs on the source stripes.
	 * The source stripes are determined by mapping the first and last
	 * block on the destination stripes.
	 */
	first_sector =
		raid5_compute_sector(conf, stripe_addr*(new_data_disks),
				     1, &dd_idx, शून्य);
	last_sector =
		raid5_compute_sector(conf, ((stripe_addr+reshape_sectors)
					    * new_data_disks - 1),
				     1, &dd_idx, शून्य);
	अगर (last_sector >= mddev->dev_sectors)
		last_sector = mddev->dev_sectors - 1;
	जबतक (first_sector <= last_sector) अणु
		sh = raid5_get_active_stripe(conf, first_sector, 1, 0, 1);
		set_bit(STRIPE_EXPAND_SOURCE, &sh->state);
		set_bit(STRIPE_HANDLE, &sh->state);
		raid5_release_stripe(sh);
		first_sector += RAID5_STRIPE_SECTORS(conf);
	पूर्ण
	/* Now that the sources are clearly marked, we can release
	 * the destination stripes
	 */
	जबतक (!list_empty(&stripes)) अणु
		sh = list_entry(stripes.next, काष्ठा stripe_head, lru);
		list_del_init(&sh->lru);
		raid5_release_stripe(sh);
	पूर्ण
	/* If this takes us to the resync_max poपूर्णांक where we have to छोड़ो,
	 * then we need to ग_लिखो out the superblock.
	 */
	sector_nr += reshape_sectors;
	retn = reshape_sectors;
finish:
	अगर (mddev->curr_resync_completed > mddev->resync_max ||
	    (sector_nr - mddev->curr_resync_completed) * 2
	    >= mddev->resync_max - mddev->curr_resync_completed) अणु
		/* Cannot proceed until we've updated the superblock... */
		रुको_event(conf->रुको_क्रम_overlap,
			   atomic_पढ़ो(&conf->reshape_stripes) == 0
			   || test_bit(MD_RECOVERY_INTR, &mddev->recovery));
		अगर (atomic_पढ़ो(&conf->reshape_stripes) != 0)
			जाओ ret;
		mddev->reshape_position = conf->reshape_progress;
		mddev->curr_resync_completed = sector_nr;
		अगर (!mddev->reshape_backwards)
			/* Can update recovery_offset */
			rdev_क्रम_each(rdev, mddev)
				अगर (rdev->raid_disk >= 0 &&
				    !test_bit(Journal, &rdev->flags) &&
				    !test_bit(In_sync, &rdev->flags) &&
				    rdev->recovery_offset < sector_nr)
					rdev->recovery_offset = sector_nr;
		conf->reshape_checkpoपूर्णांक = jअगरfies;
		set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
		md_wakeup_thपढ़ो(mddev->thपढ़ो);
		रुको_event(mddev->sb_रुको,
			   !test_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags)
			   || test_bit(MD_RECOVERY_INTR, &mddev->recovery));
		अगर (test_bit(MD_RECOVERY_INTR, &mddev->recovery))
			जाओ ret;
		spin_lock_irq(&conf->device_lock);
		conf->reshape_safe = mddev->reshape_position;
		spin_unlock_irq(&conf->device_lock);
		wake_up(&conf->रुको_क्रम_overlap);
		sysfs_notअगरy_dirent_safe(mddev->sysfs_completed);
	पूर्ण
ret:
	वापस retn;
पूर्ण

अटल अंतरभूत sector_t raid5_sync_request(काष्ठा mddev *mddev, sector_t sector_nr,
					  पूर्णांक *skipped)
अणु
	काष्ठा r5conf *conf = mddev->निजी;
	काष्ठा stripe_head *sh;
	sector_t max_sector = mddev->dev_sectors;
	sector_t sync_blocks;
	पूर्णांक still_degraded = 0;
	पूर्णांक i;

	अगर (sector_nr >= max_sector) अणु
		/* just being told to finish up .. nothing much to करो */

		अगर (test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery)) अणु
			end_reshape(conf);
			वापस 0;
		पूर्ण

		अगर (mddev->curr_resync < max_sector) /* पातed */
			md_biपंचांगap_end_sync(mddev->biपंचांगap, mddev->curr_resync,
					   &sync_blocks, 1);
		अन्यथा /* completed sync */
			conf->fullsync = 0;
		md_biपंचांगap_बंद_sync(mddev->biपंचांगap);

		वापस 0;
	पूर्ण

	/* Allow raid5_quiesce to complete */
	रुको_event(conf->रुको_क्रम_overlap, conf->quiesce != 2);

	अगर (test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery))
		वापस reshape_request(mddev, sector_nr, skipped);

	/* No need to check resync_max as we never करो more than one
	 * stripe, and as resync_max will always be on a chunk boundary,
	 * अगर the check in md_करो_sync didn't fire, there is no chance
	 * of overstepping resync_max here
	 */

	/* अगर there is too many failed drives and we are trying
	 * to resync, then निश्चित that we are finished, because there is
	 * nothing we can करो.
	 */
	अगर (mddev->degraded >= conf->max_degraded &&
	    test_bit(MD_RECOVERY_SYNC, &mddev->recovery)) अणु
		sector_t rv = mddev->dev_sectors - sector_nr;
		*skipped = 1;
		वापस rv;
	पूर्ण
	अगर (!test_bit(MD_RECOVERY_REQUESTED, &mddev->recovery) &&
	    !conf->fullsync &&
	    !md_biपंचांगap_start_sync(mddev->biपंचांगap, sector_nr, &sync_blocks, 1) &&
	    sync_blocks >= RAID5_STRIPE_SECTORS(conf)) अणु
		/* we can skip this block, and probably more */
		करो_भाग(sync_blocks, RAID5_STRIPE_SECTORS(conf));
		*skipped = 1;
		/* keep things rounded to whole stripes */
		वापस sync_blocks * RAID5_STRIPE_SECTORS(conf);
	पूर्ण

	md_biपंचांगap_cond_end_sync(mddev->biपंचांगap, sector_nr, false);

	sh = raid5_get_active_stripe(conf, sector_nr, 0, 1, 0);
	अगर (sh == शून्य) अणु
		sh = raid5_get_active_stripe(conf, sector_nr, 0, 0, 0);
		/* make sure we करोn't swamp the stripe cache अगर someone अन्यथा
		 * is trying to get access
		 */
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण
	/* Need to check अगर array will still be degraded after recovery/resync
	 * Note in हाल of > 1 drive failures it's possible we're rebuilding
	 * one drive जबतक leaving another faulty drive in array.
	 */
	rcu_पढ़ो_lock();
	क्रम (i = 0; i < conf->raid_disks; i++) अणु
		काष्ठा md_rdev *rdev = READ_ONCE(conf->disks[i].rdev);

		अगर (rdev == शून्य || test_bit(Faulty, &rdev->flags))
			still_degraded = 1;
	पूर्ण
	rcu_पढ़ो_unlock();

	md_biपंचांगap_start_sync(mddev->biपंचांगap, sector_nr, &sync_blocks, still_degraded);

	set_bit(STRIPE_SYNC_REQUESTED, &sh->state);
	set_bit(STRIPE_HANDLE, &sh->state);

	raid5_release_stripe(sh);

	वापस RAID5_STRIPE_SECTORS(conf);
पूर्ण

अटल पूर्णांक  retry_aligned_पढ़ो(काष्ठा r5conf *conf, काष्ठा bio *raid_bio,
			       अचिन्हित पूर्णांक offset)
अणु
	/* We may not be able to submit a whole bio at once as there
	 * may not be enough stripe_heads available.
	 * We cannot pre-allocate enough stripe_heads as we may need
	 * more than exist in the cache (अगर we allow ever large chunks).
	 * So we करो one stripe head at a समय and record in
	 * ->bi_hw_segments how many have been करोne.
	 *
	 * We *know* that this entire raid_bio is in one chunk, so
	 * it will be only one 'dd_idx' and only need one call to raid5_compute_sector.
	 */
	काष्ठा stripe_head *sh;
	पूर्णांक dd_idx;
	sector_t sector, logical_sector, last_sector;
	पूर्णांक scnt = 0;
	पूर्णांक handled = 0;

	logical_sector = raid_bio->bi_iter.bi_sector &
		~((sector_t)RAID5_STRIPE_SECTORS(conf)-1);
	sector = raid5_compute_sector(conf, logical_sector,
				      0, &dd_idx, शून्य);
	last_sector = bio_end_sector(raid_bio);

	क्रम (; logical_sector < last_sector;
	     logical_sector += RAID5_STRIPE_SECTORS(conf),
		     sector += RAID5_STRIPE_SECTORS(conf),
		     scnt++) अणु

		अगर (scnt < offset)
			/* alपढ़ोy करोne this stripe */
			जारी;

		sh = raid5_get_active_stripe(conf, sector, 0, 1, 1);

		अगर (!sh) अणु
			/* failed to get a stripe - must रुको */
			conf->retry_पढ़ो_aligned = raid_bio;
			conf->retry_पढ़ो_offset = scnt;
			वापस handled;
		पूर्ण

		अगर (!add_stripe_bio(sh, raid_bio, dd_idx, 0, 0)) अणु
			raid5_release_stripe(sh);
			conf->retry_पढ़ो_aligned = raid_bio;
			conf->retry_पढ़ो_offset = scnt;
			वापस handled;
		पूर्ण

		set_bit(R5_ReadNoMerge, &sh->dev[dd_idx].flags);
		handle_stripe(sh);
		raid5_release_stripe(sh);
		handled++;
	पूर्ण

	bio_endio(raid_bio);

	अगर (atomic_dec_and_test(&conf->active_aligned_पढ़ोs))
		wake_up(&conf->रुको_क्रम_quiescent);
	वापस handled;
पूर्ण

अटल पूर्णांक handle_active_stripes(काष्ठा r5conf *conf, पूर्णांक group,
				 काष्ठा r5worker *worker,
				 काष्ठा list_head *temp_inactive_list)
		__releases(&conf->device_lock)
		__acquires(&conf->device_lock)
अणु
	काष्ठा stripe_head *batch[MAX_STRIPE_BATCH], *sh;
	पूर्णांक i, batch_size = 0, hash;
	bool release_inactive = false;

	जबतक (batch_size < MAX_STRIPE_BATCH &&
			(sh = __get_priority_stripe(conf, group)) != शून्य)
		batch[batch_size++] = sh;

	अगर (batch_size == 0) अणु
		क्रम (i = 0; i < NR_STRIPE_HASH_LOCKS; i++)
			अगर (!list_empty(temp_inactive_list + i))
				अवरोध;
		अगर (i == NR_STRIPE_HASH_LOCKS) अणु
			spin_unlock_irq(&conf->device_lock);
			log_flush_stripe_to_raid(conf);
			spin_lock_irq(&conf->device_lock);
			वापस batch_size;
		पूर्ण
		release_inactive = true;
	पूर्ण
	spin_unlock_irq(&conf->device_lock);

	release_inactive_stripe_list(conf, temp_inactive_list,
				     NR_STRIPE_HASH_LOCKS);

	r5l_flush_stripe_to_raid(conf->log);
	अगर (release_inactive) अणु
		spin_lock_irq(&conf->device_lock);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < batch_size; i++)
		handle_stripe(batch[i]);
	log_ग_लिखो_stripe_run(conf);

	cond_resched();

	spin_lock_irq(&conf->device_lock);
	क्रम (i = 0; i < batch_size; i++) अणु
		hash = batch[i]->hash_lock_index;
		__release_stripe(conf, batch[i], &temp_inactive_list[hash]);
	पूर्ण
	वापस batch_size;
पूर्ण

अटल व्योम raid5_करो_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा r5worker *worker = container_of(work, काष्ठा r5worker, work);
	काष्ठा r5worker_group *group = worker->group;
	काष्ठा r5conf *conf = group->conf;
	काष्ठा mddev *mddev = conf->mddev;
	पूर्णांक group_id = group - conf->worker_groups;
	पूर्णांक handled;
	काष्ठा blk_plug plug;

	pr_debug("+++ raid5worker active\n");

	blk_start_plug(&plug);
	handled = 0;
	spin_lock_irq(&conf->device_lock);
	जबतक (1) अणु
		पूर्णांक batch_size, released;

		released = release_stripe_list(conf, worker->temp_inactive_list);

		batch_size = handle_active_stripes(conf, group_id, worker,
						   worker->temp_inactive_list);
		worker->working = false;
		अगर (!batch_size && !released)
			अवरोध;
		handled += batch_size;
		रुको_event_lock_irq(mddev->sb_रुको,
			!test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags),
			conf->device_lock);
	पूर्ण
	pr_debug("%d stripes handled\n", handled);

	spin_unlock_irq(&conf->device_lock);

	flush_deferred_bios(conf);

	r5l_flush_stripe_to_raid(conf->log);

	async_tx_issue_pending_all();
	blk_finish_plug(&plug);

	pr_debug("--- raid5worker inactive\n");
पूर्ण

/*
 * This is our raid5 kernel thपढ़ो.
 *
 * We scan the hash table क्रम stripes which can be handled now.
 * During the scan, completed stripes are saved क्रम us by the पूर्णांकerrupt
 * handler, so that they will not have to रुको क्रम our next wakeup.
 */
अटल व्योम raid5d(काष्ठा md_thपढ़ो *thपढ़ो)
अणु
	काष्ठा mddev *mddev = thपढ़ो->mddev;
	काष्ठा r5conf *conf = mddev->निजी;
	पूर्णांक handled;
	काष्ठा blk_plug plug;

	pr_debug("+++ raid5d active\n");

	md_check_recovery(mddev);

	blk_start_plug(&plug);
	handled = 0;
	spin_lock_irq(&conf->device_lock);
	जबतक (1) अणु
		काष्ठा bio *bio;
		पूर्णांक batch_size, released;
		अचिन्हित पूर्णांक offset;

		released = release_stripe_list(conf, conf->temp_inactive_list);
		अगर (released)
			clear_bit(R5_DID_ALLOC, &conf->cache_state);

		अगर (
		    !list_empty(&conf->biपंचांगap_list)) अणु
			/* Now is a good समय to flush some biपंचांगap updates */
			conf->seq_flush++;
			spin_unlock_irq(&conf->device_lock);
			md_biपंचांगap_unplug(mddev->biपंचांगap);
			spin_lock_irq(&conf->device_lock);
			conf->seq_ग_लिखो = conf->seq_flush;
			activate_bit_delay(conf, conf->temp_inactive_list);
		पूर्ण
		raid5_activate_delayed(conf);

		जबतक ((bio = हटाओ_bio_from_retry(conf, &offset))) अणु
			पूर्णांक ok;
			spin_unlock_irq(&conf->device_lock);
			ok = retry_aligned_पढ़ो(conf, bio, offset);
			spin_lock_irq(&conf->device_lock);
			अगर (!ok)
				अवरोध;
			handled++;
		पूर्ण

		batch_size = handle_active_stripes(conf, ANY_GROUP, शून्य,
						   conf->temp_inactive_list);
		अगर (!batch_size && !released)
			अवरोध;
		handled += batch_size;

		अगर (mddev->sb_flags & ~(1 << MD_SB_CHANGE_PENDING)) अणु
			spin_unlock_irq(&conf->device_lock);
			md_check_recovery(mddev);
			spin_lock_irq(&conf->device_lock);
		पूर्ण
	पूर्ण
	pr_debug("%d stripes handled\n", handled);

	spin_unlock_irq(&conf->device_lock);
	अगर (test_and_clear_bit(R5_ALLOC_MORE, &conf->cache_state) &&
	    mutex_trylock(&conf->cache_size_mutex)) अणु
		grow_one_stripe(conf, __GFP_NOWARN);
		/* Set flag even अगर allocation failed.  This helps
		 * slow करोwn allocation requests when mem is लघु
		 */
		set_bit(R5_DID_ALLOC, &conf->cache_state);
		mutex_unlock(&conf->cache_size_mutex);
	पूर्ण

	flush_deferred_bios(conf);

	r5l_flush_stripe_to_raid(conf->log);

	async_tx_issue_pending_all();
	blk_finish_plug(&plug);

	pr_debug("--- raid5d inactive\n");
पूर्ण

अटल sमाप_प्रकार
raid5_show_stripe_cache_size(काष्ठा mddev *mddev, अक्षर *page)
अणु
	काष्ठा r5conf *conf;
	पूर्णांक ret = 0;
	spin_lock(&mddev->lock);
	conf = mddev->निजी;
	अगर (conf)
		ret = प्र_लिखो(page, "%d\n", conf->min_nr_stripes);
	spin_unlock(&mddev->lock);
	वापस ret;
पूर्ण

पूर्णांक
raid5_set_cache_size(काष्ठा mddev *mddev, पूर्णांक size)
अणु
	पूर्णांक result = 0;
	काष्ठा r5conf *conf = mddev->निजी;

	अगर (size <= 16 || size > 32768)
		वापस -EINVAL;

	conf->min_nr_stripes = size;
	mutex_lock(&conf->cache_size_mutex);
	जबतक (size < conf->max_nr_stripes &&
	       drop_one_stripe(conf))
		;
	mutex_unlock(&conf->cache_size_mutex);

	md_allow_ग_लिखो(mddev);

	mutex_lock(&conf->cache_size_mutex);
	जबतक (size > conf->max_nr_stripes)
		अगर (!grow_one_stripe(conf, GFP_KERNEL)) अणु
			conf->min_nr_stripes = conf->max_nr_stripes;
			result = -ENOMEM;
			अवरोध;
		पूर्ण
	mutex_unlock(&conf->cache_size_mutex);

	वापस result;
पूर्ण
EXPORT_SYMBOL(raid5_set_cache_size);

अटल sमाप_प्रकार
raid5_store_stripe_cache_size(काष्ठा mddev *mddev, स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा r5conf *conf;
	अचिन्हित दीर्घ new;
	पूर्णांक err;

	अगर (len >= PAGE_SIZE)
		वापस -EINVAL;
	अगर (kम_से_अदीर्घ(page, 10, &new))
		वापस -EINVAL;
	err = mddev_lock(mddev);
	अगर (err)
		वापस err;
	conf = mddev->निजी;
	अगर (!conf)
		err = -ENODEV;
	अन्यथा
		err = raid5_set_cache_size(mddev, new);
	mddev_unlock(mddev);

	वापस err ?: len;
पूर्ण

अटल काष्ठा md_sysfs_entry
raid5_stripecache_size = __ATTR(stripe_cache_size, S_IRUGO | S_IWUSR,
				raid5_show_stripe_cache_size,
				raid5_store_stripe_cache_size);

अटल sमाप_प्रकार
raid5_show_rmw_level(काष्ठा mddev  *mddev, अक्षर *page)
अणु
	काष्ठा r5conf *conf = mddev->निजी;
	अगर (conf)
		वापस प्र_लिखो(page, "%d\n", conf->rmw_level);
	अन्यथा
		वापस 0;
पूर्ण

अटल sमाप_प्रकार
raid5_store_rmw_level(काष्ठा mddev  *mddev, स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा r5conf *conf = mddev->निजी;
	अचिन्हित दीर्घ new;

	अगर (!conf)
		वापस -ENODEV;

	अगर (len >= PAGE_SIZE)
		वापस -EINVAL;

	अगर (kम_से_अदीर्घ(page, 10, &new))
		वापस -EINVAL;

	अगर (new != PARITY_DISABLE_RMW && !raid6_call.xor_syndrome)
		वापस -EINVAL;

	अगर (new != PARITY_DISABLE_RMW &&
	    new != PARITY_ENABLE_RMW &&
	    new != PARITY_PREFER_RMW)
		वापस -EINVAL;

	conf->rmw_level = new;
	वापस len;
पूर्ण

अटल काष्ठा md_sysfs_entry
raid5_rmw_level = __ATTR(rmw_level, S_IRUGO | S_IWUSR,
			 raid5_show_rmw_level,
			 raid5_store_rmw_level);

अटल sमाप_प्रकार
raid5_show_stripe_size(काष्ठा mddev  *mddev, अक्षर *page)
अणु
	काष्ठा r5conf *conf;
	पूर्णांक ret = 0;

	spin_lock(&mddev->lock);
	conf = mddev->निजी;
	अगर (conf)
		ret = प्र_लिखो(page, "%lu\n", RAID5_STRIPE_SIZE(conf));
	spin_unlock(&mddev->lock);
	वापस ret;
पूर्ण

#अगर PAGE_SIZE != DEFAULT_STRIPE_SIZE
अटल sमाप_प्रकार
raid5_store_stripe_size(काष्ठा mddev  *mddev, स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा r5conf *conf;
	अचिन्हित दीर्घ new;
	पूर्णांक err;
	पूर्णांक size;

	अगर (len >= PAGE_SIZE)
		वापस -EINVAL;
	अगर (kम_से_अदीर्घ(page, 10, &new))
		वापस -EINVAL;

	/*
	 * The value should not be bigger than PAGE_SIZE. It requires to
	 * be multiple of DEFAULT_STRIPE_SIZE and the value should be घातer
	 * of two.
	 */
	अगर (new % DEFAULT_STRIPE_SIZE != 0 ||
			new > PAGE_SIZE || new == 0 ||
			new != roundup_घात_of_two(new))
		वापस -EINVAL;

	err = mddev_lock(mddev);
	अगर (err)
		वापस err;

	conf = mddev->निजी;
	अगर (!conf) अणु
		err = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	अगर (new == conf->stripe_size)
		जाओ out_unlock;

	pr_debug("md/raid: change stripe_size from %lu to %lu\n",
			conf->stripe_size, new);

	अगर (mddev->sync_thपढ़ो ||
		test_bit(MD_RECOVERY_RUNNING, &mddev->recovery) ||
		mddev->reshape_position != MaxSector ||
		mddev->sysfs_active) अणु
		err = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	mddev_suspend(mddev);
	mutex_lock(&conf->cache_size_mutex);
	size = conf->max_nr_stripes;

	shrink_stripes(conf);

	conf->stripe_size = new;
	conf->stripe_shअगरt = ilog2(new) - 9;
	conf->stripe_sectors = new >> 9;
	अगर (grow_stripes(conf, size)) अणु
		pr_warn("md/raid:%s: couldn't allocate buffers\n",
				mdname(mddev));
		err = -ENOMEM;
	पूर्ण
	mutex_unlock(&conf->cache_size_mutex);
	mddev_resume(mddev);

out_unlock:
	mddev_unlock(mddev);
	वापस err ?: len;
पूर्ण

अटल काष्ठा md_sysfs_entry
raid5_stripe_size = __ATTR(stripe_size, 0644,
			 raid5_show_stripe_size,
			 raid5_store_stripe_size);
#अन्यथा
अटल काष्ठा md_sysfs_entry
raid5_stripe_size = __ATTR(stripe_size, 0444,
			 raid5_show_stripe_size,
			 शून्य);
#पूर्ण_अगर

अटल sमाप_प्रकार
raid5_show_preपढ़ो_threshold(काष्ठा mddev *mddev, अक्षर *page)
अणु
	काष्ठा r5conf *conf;
	पूर्णांक ret = 0;
	spin_lock(&mddev->lock);
	conf = mddev->निजी;
	अगर (conf)
		ret = प्र_लिखो(page, "%d\n", conf->bypass_threshold);
	spin_unlock(&mddev->lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
raid5_store_preपढ़ो_threshold(काष्ठा mddev *mddev, स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा r5conf *conf;
	अचिन्हित दीर्घ new;
	पूर्णांक err;

	अगर (len >= PAGE_SIZE)
		वापस -EINVAL;
	अगर (kम_से_अदीर्घ(page, 10, &new))
		वापस -EINVAL;

	err = mddev_lock(mddev);
	अगर (err)
		वापस err;
	conf = mddev->निजी;
	अगर (!conf)
		err = -ENODEV;
	अन्यथा अगर (new > conf->min_nr_stripes)
		err = -EINVAL;
	अन्यथा
		conf->bypass_threshold = new;
	mddev_unlock(mddev);
	वापस err ?: len;
पूर्ण

अटल काष्ठा md_sysfs_entry
raid5_preपढ़ो_bypass_threshold = __ATTR(preपढ़ो_bypass_threshold,
					S_IRUGO | S_IWUSR,
					raid5_show_preपढ़ो_threshold,
					raid5_store_preपढ़ो_threshold);

अटल sमाप_प्रकार
raid5_show_skip_copy(काष्ठा mddev *mddev, अक्षर *page)
अणु
	काष्ठा r5conf *conf;
	पूर्णांक ret = 0;
	spin_lock(&mddev->lock);
	conf = mddev->निजी;
	अगर (conf)
		ret = प्र_लिखो(page, "%d\n", conf->skip_copy);
	spin_unlock(&mddev->lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
raid5_store_skip_copy(काष्ठा mddev *mddev, स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा r5conf *conf;
	अचिन्हित दीर्घ new;
	पूर्णांक err;

	अगर (len >= PAGE_SIZE)
		वापस -EINVAL;
	अगर (kम_से_अदीर्घ(page, 10, &new))
		वापस -EINVAL;
	new = !!new;

	err = mddev_lock(mddev);
	अगर (err)
		वापस err;
	conf = mddev->निजी;
	अगर (!conf)
		err = -ENODEV;
	अन्यथा अगर (new != conf->skip_copy) अणु
		काष्ठा request_queue *q = mddev->queue;

		mddev_suspend(mddev);
		conf->skip_copy = new;
		अगर (new)
			blk_queue_flag_set(QUEUE_FLAG_STABLE_WRITES, q);
		अन्यथा
			blk_queue_flag_clear(QUEUE_FLAG_STABLE_WRITES, q);
		mddev_resume(mddev);
	पूर्ण
	mddev_unlock(mddev);
	वापस err ?: len;
पूर्ण

अटल काष्ठा md_sysfs_entry
raid5_skip_copy = __ATTR(skip_copy, S_IRUGO | S_IWUSR,
					raid5_show_skip_copy,
					raid5_store_skip_copy);

अटल sमाप_प्रकार
stripe_cache_active_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	काष्ठा r5conf *conf = mddev->निजी;
	अगर (conf)
		वापस प्र_लिखो(page, "%d\n", atomic_पढ़ो(&conf->active_stripes));
	अन्यथा
		वापस 0;
पूर्ण

अटल काष्ठा md_sysfs_entry
raid5_stripecache_active = __ATTR_RO(stripe_cache_active);

अटल sमाप_प्रकार
raid5_show_group_thपढ़ो_cnt(काष्ठा mddev *mddev, अक्षर *page)
अणु
	काष्ठा r5conf *conf;
	पूर्णांक ret = 0;
	spin_lock(&mddev->lock);
	conf = mddev->निजी;
	अगर (conf)
		ret = प्र_लिखो(page, "%d\n", conf->worker_cnt_per_group);
	spin_unlock(&mddev->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक alloc_thपढ़ो_groups(काष्ठा r5conf *conf, पूर्णांक cnt,
			       पूर्णांक *group_cnt,
			       काष्ठा r5worker_group **worker_groups);
अटल sमाप_प्रकार
raid5_store_group_thपढ़ो_cnt(काष्ठा mddev *mddev, स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा r5conf *conf;
	अचिन्हित पूर्णांक new;
	पूर्णांक err;
	काष्ठा r5worker_group *new_groups, *old_groups;
	पूर्णांक group_cnt;

	अगर (len >= PAGE_SIZE)
		वापस -EINVAL;
	अगर (kstrtouपूर्णांक(page, 10, &new))
		वापस -EINVAL;
	/* 8192 should be big enough */
	अगर (new > 8192)
		वापस -EINVAL;

	err = mddev_lock(mddev);
	अगर (err)
		वापस err;
	conf = mddev->निजी;
	अगर (!conf)
		err = -ENODEV;
	अन्यथा अगर (new != conf->worker_cnt_per_group) अणु
		mddev_suspend(mddev);

		old_groups = conf->worker_groups;
		अगर (old_groups)
			flush_workqueue(raid5_wq);

		err = alloc_thपढ़ो_groups(conf, new, &group_cnt, &new_groups);
		अगर (!err) अणु
			spin_lock_irq(&conf->device_lock);
			conf->group_cnt = group_cnt;
			conf->worker_cnt_per_group = new;
			conf->worker_groups = new_groups;
			spin_unlock_irq(&conf->device_lock);

			अगर (old_groups)
				kमुक्त(old_groups[0].workers);
			kमुक्त(old_groups);
		पूर्ण
		mddev_resume(mddev);
	पूर्ण
	mddev_unlock(mddev);

	वापस err ?: len;
पूर्ण

अटल काष्ठा md_sysfs_entry
raid5_group_thपढ़ो_cnt = __ATTR(group_thपढ़ो_cnt, S_IRUGO | S_IWUSR,
				raid5_show_group_thपढ़ो_cnt,
				raid5_store_group_thपढ़ो_cnt);

अटल काष्ठा attribute *raid5_attrs[] =  अणु
	&raid5_stripecache_size.attr,
	&raid5_stripecache_active.attr,
	&raid5_preपढ़ो_bypass_threshold.attr,
	&raid5_group_thपढ़ो_cnt.attr,
	&raid5_skip_copy.attr,
	&raid5_rmw_level.attr,
	&raid5_stripe_size.attr,
	&r5c_journal_mode.attr,
	&ppl_ग_लिखो_hपूर्णांक.attr,
	शून्य,
पूर्ण;
अटल काष्ठा attribute_group raid5_attrs_group = अणु
	.name = शून्य,
	.attrs = raid5_attrs,
पूर्ण;

अटल पूर्णांक alloc_thपढ़ो_groups(काष्ठा r5conf *conf, पूर्णांक cnt, पूर्णांक *group_cnt,
			       काष्ठा r5worker_group **worker_groups)
अणु
	पूर्णांक i, j, k;
	sमाप_प्रकार size;
	काष्ठा r5worker *workers;

	अगर (cnt == 0) अणु
		*group_cnt = 0;
		*worker_groups = शून्य;
		वापस 0;
	पूर्ण
	*group_cnt = num_possible_nodes();
	size = माप(काष्ठा r5worker) * cnt;
	workers = kसुस्मृति(size, *group_cnt, GFP_NOIO);
	*worker_groups = kसुस्मृति(*group_cnt, माप(काष्ठा r5worker_group),
				 GFP_NOIO);
	अगर (!*worker_groups || !workers) अणु
		kमुक्त(workers);
		kमुक्त(*worker_groups);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < *group_cnt; i++) अणु
		काष्ठा r5worker_group *group;

		group = &(*worker_groups)[i];
		INIT_LIST_HEAD(&group->handle_list);
		INIT_LIST_HEAD(&group->loprio_list);
		group->conf = conf;
		group->workers = workers + i * cnt;

		क्रम (j = 0; j < cnt; j++) अणु
			काष्ठा r5worker *worker = group->workers + j;
			worker->group = group;
			INIT_WORK(&worker->work, raid5_करो_work);

			क्रम (k = 0; k < NR_STRIPE_HASH_LOCKS; k++)
				INIT_LIST_HEAD(worker->temp_inactive_list + k);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम मुक्त_thपढ़ो_groups(काष्ठा r5conf *conf)
अणु
	अगर (conf->worker_groups)
		kमुक्त(conf->worker_groups[0].workers);
	kमुक्त(conf->worker_groups);
	conf->worker_groups = शून्य;
पूर्ण

अटल sector_t
raid5_size(काष्ठा mddev *mddev, sector_t sectors, पूर्णांक raid_disks)
अणु
	काष्ठा r5conf *conf = mddev->निजी;

	अगर (!sectors)
		sectors = mddev->dev_sectors;
	अगर (!raid_disks)
		/* size is defined by the smallest of previous and new size */
		raid_disks = min(conf->raid_disks, conf->previous_raid_disks);

	sectors &= ~((sector_t)conf->chunk_sectors - 1);
	sectors &= ~((sector_t)conf->prev_chunk_sectors - 1);
	वापस sectors * (raid_disks - conf->max_degraded);
पूर्ण

अटल व्योम मुक्त_scratch_buffer(काष्ठा r5conf *conf, काष्ठा raid5_percpu *percpu)
अणु
	safe_put_page(percpu->spare_page);
	percpu->spare_page = शून्य;
	kvमुक्त(percpu->scribble);
	percpu->scribble = शून्य;
पूर्ण

अटल पूर्णांक alloc_scratch_buffer(काष्ठा r5conf *conf, काष्ठा raid5_percpu *percpu)
अणु
	अगर (conf->level == 6 && !percpu->spare_page) अणु
		percpu->spare_page = alloc_page(GFP_KERNEL);
		अगर (!percpu->spare_page)
			वापस -ENOMEM;
	पूर्ण

	अगर (scribble_alloc(percpu,
			   max(conf->raid_disks,
			       conf->previous_raid_disks),
			   max(conf->chunk_sectors,
			       conf->prev_chunk_sectors)
			   / RAID5_STRIPE_SECTORS(conf))) अणु
		मुक्त_scratch_buffer(conf, percpu);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक raid456_cpu_dead(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा r5conf *conf = hlist_entry_safe(node, काष्ठा r5conf, node);

	मुक्त_scratch_buffer(conf, per_cpu_ptr(conf->percpu, cpu));
	वापस 0;
पूर्ण

अटल व्योम raid5_मुक्त_percpu(काष्ठा r5conf *conf)
अणु
	अगर (!conf->percpu)
		वापस;

	cpuhp_state_हटाओ_instance(CPUHP_MD_RAID5_PREPARE, &conf->node);
	मुक्त_percpu(conf->percpu);
पूर्ण

अटल व्योम मुक्त_conf(काष्ठा r5conf *conf)
अणु
	पूर्णांक i;

	log_निकास(conf);

	unरेजिस्टर_shrinker(&conf->shrinker);
	मुक्त_thपढ़ो_groups(conf);
	shrink_stripes(conf);
	raid5_मुक्त_percpu(conf);
	क्रम (i = 0; i < conf->pool_size; i++)
		अगर (conf->disks[i].extra_page)
			put_page(conf->disks[i].extra_page);
	kमुक्त(conf->disks);
	bioset_निकास(&conf->bio_split);
	kमुक्त(conf->stripe_hashtbl);
	kमुक्त(conf->pending_data);
	kमुक्त(conf);
पूर्ण

अटल पूर्णांक raid456_cpu_up_prepare(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा r5conf *conf = hlist_entry_safe(node, काष्ठा r5conf, node);
	काष्ठा raid5_percpu *percpu = per_cpu_ptr(conf->percpu, cpu);

	अगर (alloc_scratch_buffer(conf, percpu)) अणु
		pr_warn("%s: failed memory allocation for cpu%u\n",
			__func__, cpu);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक raid5_alloc_percpu(काष्ठा r5conf *conf)
अणु
	पूर्णांक err = 0;

	conf->percpu = alloc_percpu(काष्ठा raid5_percpu);
	अगर (!conf->percpu)
		वापस -ENOMEM;

	err = cpuhp_state_add_instance(CPUHP_MD_RAID5_PREPARE, &conf->node);
	अगर (!err) अणु
		conf->scribble_disks = max(conf->raid_disks,
			conf->previous_raid_disks);
		conf->scribble_sectors = max(conf->chunk_sectors,
			conf->prev_chunk_sectors);
	पूर्ण
	वापस err;
पूर्ण

अटल अचिन्हित दीर्घ raid5_cache_scan(काष्ठा shrinker *shrink,
				      काष्ठा shrink_control *sc)
अणु
	काष्ठा r5conf *conf = container_of(shrink, काष्ठा r5conf, shrinker);
	अचिन्हित दीर्घ ret = SHRINK_STOP;

	अगर (mutex_trylock(&conf->cache_size_mutex)) अणु
		ret= 0;
		जबतक (ret < sc->nr_to_scan &&
		       conf->max_nr_stripes > conf->min_nr_stripes) अणु
			अगर (drop_one_stripe(conf) == 0) अणु
				ret = SHRINK_STOP;
				अवरोध;
			पूर्ण
			ret++;
		पूर्ण
		mutex_unlock(&conf->cache_size_mutex);
	पूर्ण
	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ raid5_cache_count(काष्ठा shrinker *shrink,
				       काष्ठा shrink_control *sc)
अणु
	काष्ठा r5conf *conf = container_of(shrink, काष्ठा r5conf, shrinker);

	अगर (conf->max_nr_stripes < conf->min_nr_stripes)
		/* unlikely, but not impossible */
		वापस 0;
	वापस conf->max_nr_stripes - conf->min_nr_stripes;
पूर्ण

अटल काष्ठा r5conf *setup_conf(काष्ठा mddev *mddev)
अणु
	काष्ठा r5conf *conf;
	पूर्णांक raid_disk, memory, max_disks;
	काष्ठा md_rdev *rdev;
	काष्ठा disk_info *disk;
	अक्षर pers_name[6];
	पूर्णांक i;
	पूर्णांक group_cnt;
	काष्ठा r5worker_group *new_group;
	पूर्णांक ret;

	अगर (mddev->new_level != 5
	    && mddev->new_level != 4
	    && mddev->new_level != 6) अणु
		pr_warn("md/raid:%s: raid level not set to 4/5/6 (%d)\n",
			mdname(mddev), mddev->new_level);
		वापस ERR_PTR(-EIO);
	पूर्ण
	अगर ((mddev->new_level == 5
	     && !algorithm_valid_raid5(mddev->new_layout)) ||
	    (mddev->new_level == 6
	     && !algorithm_valid_raid6(mddev->new_layout))) अणु
		pr_warn("md/raid:%s: layout %d not supported\n",
			mdname(mddev), mddev->new_layout);
		वापस ERR_PTR(-EIO);
	पूर्ण
	अगर (mddev->new_level == 6 && mddev->raid_disks < 4) अणु
		pr_warn("md/raid:%s: not enough configured devices (%d, minimum 4)\n",
			mdname(mddev), mddev->raid_disks);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!mddev->new_chunk_sectors ||
	    (mddev->new_chunk_sectors << 9) % PAGE_SIZE ||
	    !is_घातer_of_2(mddev->new_chunk_sectors)) अणु
		pr_warn("md/raid:%s: invalid chunk size %d\n",
			mdname(mddev), mddev->new_chunk_sectors << 9);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	conf = kzalloc(माप(काष्ठा r5conf), GFP_KERNEL);
	अगर (conf == शून्य)
		जाओ पात;

#अगर PAGE_SIZE != DEFAULT_STRIPE_SIZE
	conf->stripe_size = DEFAULT_STRIPE_SIZE;
	conf->stripe_shअगरt = ilog2(DEFAULT_STRIPE_SIZE) - 9;
	conf->stripe_sectors = DEFAULT_STRIPE_SIZE >> 9;
#पूर्ण_अगर
	INIT_LIST_HEAD(&conf->मुक्त_list);
	INIT_LIST_HEAD(&conf->pending_list);
	conf->pending_data = kसुस्मृति(PENDING_IO_MAX,
				     माप(काष्ठा r5pending_data),
				     GFP_KERNEL);
	अगर (!conf->pending_data)
		जाओ पात;
	क्रम (i = 0; i < PENDING_IO_MAX; i++)
		list_add(&conf->pending_data[i].sibling, &conf->मुक्त_list);
	/* Don't enable multi-thपढ़ोing by शेष*/
	अगर (!alloc_thपढ़ो_groups(conf, 0, &group_cnt, &new_group)) अणु
		conf->group_cnt = group_cnt;
		conf->worker_cnt_per_group = 0;
		conf->worker_groups = new_group;
	पूर्ण अन्यथा
		जाओ पात;
	spin_lock_init(&conf->device_lock);
	seqcount_spinlock_init(&conf->gen_lock, &conf->device_lock);
	mutex_init(&conf->cache_size_mutex);
	init_रुकोqueue_head(&conf->रुको_क्रम_quiescent);
	init_रुकोqueue_head(&conf->रुको_क्रम_stripe);
	init_रुकोqueue_head(&conf->रुको_क्रम_overlap);
	INIT_LIST_HEAD(&conf->handle_list);
	INIT_LIST_HEAD(&conf->loprio_list);
	INIT_LIST_HEAD(&conf->hold_list);
	INIT_LIST_HEAD(&conf->delayed_list);
	INIT_LIST_HEAD(&conf->biपंचांगap_list);
	init_llist_head(&conf->released_stripes);
	atomic_set(&conf->active_stripes, 0);
	atomic_set(&conf->preपढ़ो_active_stripes, 0);
	atomic_set(&conf->active_aligned_पढ़ोs, 0);
	spin_lock_init(&conf->pending_bios_lock);
	conf->batch_bio_dispatch = true;
	rdev_क्रम_each(rdev, mddev) अणु
		अगर (test_bit(Journal, &rdev->flags))
			जारी;
		अगर (blk_queue_nonrot(bdev_get_queue(rdev->bdev))) अणु
			conf->batch_bio_dispatch = false;
			अवरोध;
		पूर्ण
	पूर्ण

	conf->bypass_threshold = BYPASS_THRESHOLD;
	conf->recovery_disabled = mddev->recovery_disabled - 1;

	conf->raid_disks = mddev->raid_disks;
	अगर (mddev->reshape_position == MaxSector)
		conf->previous_raid_disks = mddev->raid_disks;
	अन्यथा
		conf->previous_raid_disks = mddev->raid_disks - mddev->delta_disks;
	max_disks = max(conf->raid_disks, conf->previous_raid_disks);

	conf->disks = kसुस्मृति(max_disks, माप(काष्ठा disk_info),
			      GFP_KERNEL);

	अगर (!conf->disks)
		जाओ पात;

	क्रम (i = 0; i < max_disks; i++) अणु
		conf->disks[i].extra_page = alloc_page(GFP_KERNEL);
		अगर (!conf->disks[i].extra_page)
			जाओ पात;
	पूर्ण

	ret = bioset_init(&conf->bio_split, BIO_POOL_SIZE, 0, 0);
	अगर (ret)
		जाओ पात;
	conf->mddev = mddev;

	अगर ((conf->stripe_hashtbl = kzalloc(PAGE_SIZE, GFP_KERNEL)) == शून्य)
		जाओ पात;

	/* We init hash_locks[0] separately to that it can be used
	 * as the reference lock in the spin_lock_nest_lock() call
	 * in lock_all_device_hash_locks_irq in order to convince
	 * lockdep that we know what we are करोing.
	 */
	spin_lock_init(conf->hash_locks);
	क्रम (i = 1; i < NR_STRIPE_HASH_LOCKS; i++)
		spin_lock_init(conf->hash_locks + i);

	क्रम (i = 0; i < NR_STRIPE_HASH_LOCKS; i++)
		INIT_LIST_HEAD(conf->inactive_list + i);

	क्रम (i = 0; i < NR_STRIPE_HASH_LOCKS; i++)
		INIT_LIST_HEAD(conf->temp_inactive_list + i);

	atomic_set(&conf->r5c_cached_full_stripes, 0);
	INIT_LIST_HEAD(&conf->r5c_full_stripe_list);
	atomic_set(&conf->r5c_cached_partial_stripes, 0);
	INIT_LIST_HEAD(&conf->r5c_partial_stripe_list);
	atomic_set(&conf->r5c_flushing_full_stripes, 0);
	atomic_set(&conf->r5c_flushing_partial_stripes, 0);

	conf->level = mddev->new_level;
	conf->chunk_sectors = mddev->new_chunk_sectors;
	अगर (raid5_alloc_percpu(conf) != 0)
		जाओ पात;

	pr_debug("raid456: run(%s) called.\n", mdname(mddev));

	rdev_क्रम_each(rdev, mddev) अणु
		raid_disk = rdev->raid_disk;
		अगर (raid_disk >= max_disks
		    || raid_disk < 0 || test_bit(Journal, &rdev->flags))
			जारी;
		disk = conf->disks + raid_disk;

		अगर (test_bit(Replacement, &rdev->flags)) अणु
			अगर (disk->replacement)
				जाओ पात;
			disk->replacement = rdev;
		पूर्ण अन्यथा अणु
			अगर (disk->rdev)
				जाओ पात;
			disk->rdev = rdev;
		पूर्ण

		अगर (test_bit(In_sync, &rdev->flags)) अणु
			अक्षर b[BDEVNAME_SIZE];
			pr_info("md/raid:%s: device %s operational as raid disk %d\n",
				mdname(mddev), bdevname(rdev->bdev, b), raid_disk);
		पूर्ण अन्यथा अगर (rdev->saved_raid_disk != raid_disk)
			/* Cannot rely on biपंचांगap to complete recovery */
			conf->fullsync = 1;
	पूर्ण

	conf->level = mddev->new_level;
	अगर (conf->level == 6) अणु
		conf->max_degraded = 2;
		अगर (raid6_call.xor_syndrome)
			conf->rmw_level = PARITY_ENABLE_RMW;
		अन्यथा
			conf->rmw_level = PARITY_DISABLE_RMW;
	पूर्ण अन्यथा अणु
		conf->max_degraded = 1;
		conf->rmw_level = PARITY_ENABLE_RMW;
	पूर्ण
	conf->algorithm = mddev->new_layout;
	conf->reshape_progress = mddev->reshape_position;
	अगर (conf->reshape_progress != MaxSector) अणु
		conf->prev_chunk_sectors = mddev->chunk_sectors;
		conf->prev_algo = mddev->layout;
	पूर्ण अन्यथा अणु
		conf->prev_chunk_sectors = conf->chunk_sectors;
		conf->prev_algo = conf->algorithm;
	पूर्ण

	conf->min_nr_stripes = NR_STRIPES;
	अगर (mddev->reshape_position != MaxSector) अणु
		पूर्णांक stripes = max_t(पूर्णांक,
			((mddev->chunk_sectors << 9) / RAID5_STRIPE_SIZE(conf)) * 4,
			((mddev->new_chunk_sectors << 9) / RAID5_STRIPE_SIZE(conf)) * 4);
		conf->min_nr_stripes = max(NR_STRIPES, stripes);
		अगर (conf->min_nr_stripes != NR_STRIPES)
			pr_info("md/raid:%s: force stripe size %d for reshape\n",
				mdname(mddev), conf->min_nr_stripes);
	पूर्ण
	memory = conf->min_nr_stripes * (माप(काष्ठा stripe_head) +
		 max_disks * ((माप(काष्ठा bio) + PAGE_SIZE))) / 1024;
	atomic_set(&conf->empty_inactive_list_nr, NR_STRIPE_HASH_LOCKS);
	अगर (grow_stripes(conf, conf->min_nr_stripes)) अणु
		pr_warn("md/raid:%s: couldn't allocate %dkB for buffers\n",
			mdname(mddev), memory);
		जाओ पात;
	पूर्ण अन्यथा
		pr_debug("md/raid:%s: allocated %dkB\n", mdname(mddev), memory);
	/*
	 * Losing a stripe head costs more than the समय to refill it,
	 * it reduces the queue depth and so can hurt throughput.
	 * So set it rather large, scaled by number of devices.
	 */
	conf->shrinker.seeks = DEFAULT_SEEKS * conf->raid_disks * 4;
	conf->shrinker.scan_objects = raid5_cache_scan;
	conf->shrinker.count_objects = raid5_cache_count;
	conf->shrinker.batch = 128;
	conf->shrinker.flags = 0;
	अगर (रेजिस्टर_shrinker(&conf->shrinker)) अणु
		pr_warn("md/raid:%s: couldn't register shrinker.\n",
			mdname(mddev));
		जाओ पात;
	पूर्ण

	प्र_लिखो(pers_name, "raid%d", mddev->new_level);
	conf->thपढ़ो = md_रेजिस्टर_thपढ़ो(raid5d, mddev, pers_name);
	अगर (!conf->thपढ़ो) अणु
		pr_warn("md/raid:%s: couldn't allocate thread.\n",
			mdname(mddev));
		जाओ पात;
	पूर्ण

	वापस conf;

 पात:
	अगर (conf) अणु
		मुक्त_conf(conf);
		वापस ERR_PTR(-EIO);
	पूर्ण अन्यथा
		वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल पूर्णांक only_parity(पूर्णांक raid_disk, पूर्णांक algo, पूर्णांक raid_disks, पूर्णांक max_degraded)
अणु
	चयन (algo) अणु
	हाल ALGORITHM_PARITY_0:
		अगर (raid_disk < max_degraded)
			वापस 1;
		अवरोध;
	हाल ALGORITHM_PARITY_N:
		अगर (raid_disk >= raid_disks - max_degraded)
			वापस 1;
		अवरोध;
	हाल ALGORITHM_PARITY_0_6:
		अगर (raid_disk == 0 ||
		    raid_disk == raid_disks - 1)
			वापस 1;
		अवरोध;
	हाल ALGORITHM_LEFT_ASYMMETRIC_6:
	हाल ALGORITHM_RIGHT_ASYMMETRIC_6:
	हाल ALGORITHM_LEFT_SYMMETRIC_6:
	हाल ALGORITHM_RIGHT_SYMMETRIC_6:
		अगर (raid_disk == raid_disks - 1)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम raid5_set_io_opt(काष्ठा r5conf *conf)
अणु
	blk_queue_io_opt(conf->mddev->queue, (conf->chunk_sectors << 9) *
			 (conf->raid_disks - conf->max_degraded));
पूर्ण

अटल पूर्णांक raid5_run(काष्ठा mddev *mddev)
अणु
	काष्ठा r5conf *conf;
	पूर्णांक working_disks = 0;
	पूर्णांक dirty_parity_disks = 0;
	काष्ठा md_rdev *rdev;
	काष्ठा md_rdev *journal_dev = शून्य;
	sector_t reshape_offset = 0;
	पूर्णांक i;
	दीर्घ दीर्घ min_offset_dअगरf = 0;
	पूर्णांक first = 1;

	अगर (mddev_init_ग_लिखोs_pending(mddev) < 0)
		वापस -ENOMEM;

	अगर (mddev->recovery_cp != MaxSector)
		pr_notice("md/raid:%s: not clean -- starting background reconstruction\n",
			  mdname(mddev));

	rdev_क्रम_each(rdev, mddev) अणु
		दीर्घ दीर्घ dअगरf;

		अगर (test_bit(Journal, &rdev->flags)) अणु
			journal_dev = rdev;
			जारी;
		पूर्ण
		अगर (rdev->raid_disk < 0)
			जारी;
		dअगरf = (rdev->new_data_offset - rdev->data_offset);
		अगर (first) अणु
			min_offset_dअगरf = dअगरf;
			first = 0;
		पूर्ण अन्यथा अगर (mddev->reshape_backwards &&
			 dअगरf < min_offset_dअगरf)
			min_offset_dअगरf = dअगरf;
		अन्यथा अगर (!mddev->reshape_backwards &&
			 dअगरf > min_offset_dअगरf)
			min_offset_dअगरf = dअगरf;
	पूर्ण

	अगर ((test_bit(MD_HAS_JOURNAL, &mddev->flags) || journal_dev) &&
	    (mddev->biपंचांगap_info.offset || mddev->biपंचांगap_info.file)) अणु
		pr_notice("md/raid:%s: array cannot have both journal and bitmap\n",
			  mdname(mddev));
		वापस -EINVAL;
	पूर्ण

	अगर (mddev->reshape_position != MaxSector) अणु
		/* Check that we can जारी the reshape.
		 * Dअगरficulties arise अगर the stripe we would ग_लिखो to
		 * next is at or after the stripe we would पढ़ो from next.
		 * For a reshape that changes the number of devices, this
		 * is only possible क्रम a very लघु समय, and mdadm makes
		 * sure that समय appears to have past beक्रमe assembling
		 * the array.  So we fail अगर that समय hasn't passed.
		 * For a reshape that keeps the number of devices the same
		 * mdadm must be monitoring the reshape can keeping the
		 * critical areas पढ़ो-only and backed up.  It will start
		 * the array in पढ़ो-only mode, so we check क्रम that.
		 */
		sector_t here_new, here_old;
		पूर्णांक old_disks;
		पूर्णांक max_degraded = (mddev->level == 6 ? 2 : 1);
		पूर्णांक chunk_sectors;
		पूर्णांक new_data_disks;

		अगर (journal_dev) अणु
			pr_warn("md/raid:%s: don't support reshape with journal - aborting.\n",
				mdname(mddev));
			वापस -EINVAL;
		पूर्ण

		अगर (mddev->new_level != mddev->level) अणु
			pr_warn("md/raid:%s: unsupported reshape required - aborting.\n",
				mdname(mddev));
			वापस -EINVAL;
		पूर्ण
		old_disks = mddev->raid_disks - mddev->delta_disks;
		/* reshape_position must be on a new-stripe boundary, and one
		 * further up in new geometry must map after here in old
		 * geometry.
		 * If the chunk sizes are dअगरferent, then as we perक्रमm reshape
		 * in units of the largest of the two, reshape_position needs
		 * be a multiple of the largest chunk size बार new data disks.
		 */
		here_new = mddev->reshape_position;
		chunk_sectors = max(mddev->chunk_sectors, mddev->new_chunk_sectors);
		new_data_disks = mddev->raid_disks - max_degraded;
		अगर (sector_भाग(here_new, chunk_sectors * new_data_disks)) अणु
			pr_warn("md/raid:%s: reshape_position not on a stripe boundary\n",
				mdname(mddev));
			वापस -EINVAL;
		पूर्ण
		reshape_offset = here_new * chunk_sectors;
		/* here_new is the stripe we will ग_लिखो to */
		here_old = mddev->reshape_position;
		sector_भाग(here_old, chunk_sectors * (old_disks-max_degraded));
		/* here_old is the first stripe that we might need to पढ़ो
		 * from */
		अगर (mddev->delta_disks == 0) अणु
			/* We cannot be sure it is safe to start an in-place
			 * reshape.  It is only safe अगर user-space is monitoring
			 * and taking स्थिरant backups.
			 * mdadm always starts a situation like this in
			 * पढ़ोonly mode so it can take control beक्रमe
			 * allowing any ग_लिखोs.  So just check क्रम that.
			 */
			अगर (असल(min_offset_dअगरf) >= mddev->chunk_sectors &&
			    असल(min_offset_dअगरf) >= mddev->new_chunk_sectors)
				/* not really in-place - so OK */;
			अन्यथा अगर (mddev->ro == 0) अणु
				pr_warn("md/raid:%s: in-place reshape must be started in read-only mode - aborting\n",
					mdname(mddev));
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अगर (mddev->reshape_backwards
		    ? (here_new * chunk_sectors + min_offset_dअगरf <=
		       here_old * chunk_sectors)
		    : (here_new * chunk_sectors >=
		       here_old * chunk_sectors + (-min_offset_dअगरf))) अणु
			/* Reading from the same stripe as writing to - bad */
			pr_warn("md/raid:%s: reshape_position too early for auto-recovery - aborting.\n",
				mdname(mddev));
			वापस -EINVAL;
		पूर्ण
		pr_debug("md/raid:%s: reshape will continue\n", mdname(mddev));
		/* OK, we should be able to जारी; */
	पूर्ण अन्यथा अणु
		BUG_ON(mddev->level != mddev->new_level);
		BUG_ON(mddev->layout != mddev->new_layout);
		BUG_ON(mddev->chunk_sectors != mddev->new_chunk_sectors);
		BUG_ON(mddev->delta_disks != 0);
	पूर्ण

	अगर (test_bit(MD_HAS_JOURNAL, &mddev->flags) &&
	    test_bit(MD_HAS_PPL, &mddev->flags)) अणु
		pr_warn("md/raid:%s: using journal device and PPL not allowed - disabling PPL\n",
			mdname(mddev));
		clear_bit(MD_HAS_PPL, &mddev->flags);
		clear_bit(MD_HAS_MULTIPLE_PPLS, &mddev->flags);
	पूर्ण

	अगर (mddev->निजी == शून्य)
		conf = setup_conf(mddev);
	अन्यथा
		conf = mddev->निजी;

	अगर (IS_ERR(conf))
		वापस PTR_ERR(conf);

	अगर (test_bit(MD_HAS_JOURNAL, &mddev->flags)) अणु
		अगर (!journal_dev) अणु
			pr_warn("md/raid:%s: journal disk is missing, force array readonly\n",
				mdname(mddev));
			mddev->ro = 1;
			set_disk_ro(mddev->gendisk, 1);
		पूर्ण अन्यथा अगर (mddev->recovery_cp == MaxSector)
			set_bit(MD_JOURNAL_CLEAN, &mddev->flags);
	पूर्ण

	conf->min_offset_dअगरf = min_offset_dअगरf;
	mddev->thपढ़ो = conf->thपढ़ो;
	conf->thपढ़ो = शून्य;
	mddev->निजी = conf;

	क्रम (i = 0; i < conf->raid_disks && conf->previous_raid_disks;
	     i++) अणु
		rdev = conf->disks[i].rdev;
		अगर (!rdev && conf->disks[i].replacement) अणु
			/* The replacement is all we have yet */
			rdev = conf->disks[i].replacement;
			conf->disks[i].replacement = शून्य;
			clear_bit(Replacement, &rdev->flags);
			conf->disks[i].rdev = rdev;
		पूर्ण
		अगर (!rdev)
			जारी;
		अगर (conf->disks[i].replacement &&
		    conf->reshape_progress != MaxSector) अणु
			/* replacements and reshape simply करो not mix. */
			pr_warn("md: cannot handle concurrent replacement and reshape.\n");
			जाओ पात;
		पूर्ण
		अगर (test_bit(In_sync, &rdev->flags)) अणु
			working_disks++;
			जारी;
		पूर्ण
		/* This disc is not fully in-sync.  However अगर it
		 * just stored parity (beyond the recovery_offset),
		 * when we करोn't need to be concerned about the
		 * array being dirty.
		 * When reshape goes 'backwards', we never have
		 * partially completed devices, so we only need
		 * to worry about reshape going क्रमwards.
		 */
		/* Hack because v0.91 करोesn't store recovery_offset properly. */
		अगर (mddev->major_version == 0 &&
		    mddev->minor_version > 90)
			rdev->recovery_offset = reshape_offset;

		अगर (rdev->recovery_offset < reshape_offset) अणु
			/* We need to check old and new layout */
			अगर (!only_parity(rdev->raid_disk,
					 conf->algorithm,
					 conf->raid_disks,
					 conf->max_degraded))
				जारी;
		पूर्ण
		अगर (!only_parity(rdev->raid_disk,
				 conf->prev_algo,
				 conf->previous_raid_disks,
				 conf->max_degraded))
			जारी;
		dirty_parity_disks++;
	पूर्ण

	/*
	 * 0 क्रम a fully functional array, 1 or 2 क्रम a degraded array.
	 */
	mddev->degraded = raid5_calc_degraded(conf);

	अगर (has_failed(conf)) अणु
		pr_crit("md/raid:%s: not enough operational devices (%d/%d failed)\n",
			mdname(mddev), mddev->degraded, conf->raid_disks);
		जाओ पात;
	पूर्ण

	/* device size must be a multiple of chunk size */
	mddev->dev_sectors &= ~((sector_t)mddev->chunk_sectors - 1);
	mddev->resync_max_sectors = mddev->dev_sectors;

	अगर (mddev->degraded > dirty_parity_disks &&
	    mddev->recovery_cp != MaxSector) अणु
		अगर (test_bit(MD_HAS_PPL, &mddev->flags))
			pr_crit("md/raid:%s: starting dirty degraded array with PPL.\n",
				mdname(mddev));
		अन्यथा अगर (mddev->ok_start_degraded)
			pr_crit("md/raid:%s: starting dirty degraded array - data corruption possible.\n",
				mdname(mddev));
		अन्यथा अणु
			pr_crit("md/raid:%s: cannot start dirty degraded array.\n",
				mdname(mddev));
			जाओ पात;
		पूर्ण
	पूर्ण

	pr_info("md/raid:%s: raid level %d active with %d out of %d devices, algorithm %d\n",
		mdname(mddev), conf->level,
		mddev->raid_disks-mddev->degraded, mddev->raid_disks,
		mddev->new_layout);

	prपूर्णांक_raid5_conf(conf);

	अगर (conf->reshape_progress != MaxSector) अणु
		conf->reshape_safe = conf->reshape_progress;
		atomic_set(&conf->reshape_stripes, 0);
		clear_bit(MD_RECOVERY_SYNC, &mddev->recovery);
		clear_bit(MD_RECOVERY_CHECK, &mddev->recovery);
		set_bit(MD_RECOVERY_RESHAPE, &mddev->recovery);
		set_bit(MD_RECOVERY_RUNNING, &mddev->recovery);
		mddev->sync_thपढ़ो = md_रेजिस्टर_thपढ़ो(md_करो_sync, mddev,
							"reshape");
		अगर (!mddev->sync_thपढ़ो)
			जाओ पात;
	पूर्ण

	/* Ok, everything is just fine now */
	अगर (mddev->to_हटाओ == &raid5_attrs_group)
		mddev->to_हटाओ = शून्य;
	अन्यथा अगर (mddev->kobj.sd &&
	    sysfs_create_group(&mddev->kobj, &raid5_attrs_group))
		pr_warn("raid5: failed to create sysfs attributes for %s\n",
			mdname(mddev));
	md_set_array_sectors(mddev, raid5_size(mddev, 0, 0));

	अगर (mddev->queue) अणु
		पूर्णांक chunk_size;
		/* पढ़ो-ahead size must cover two whole stripes, which
		 * is 2 * (datadisks) * chunksize where 'n' is the
		 * number of raid devices
		 */
		पूर्णांक data_disks = conf->previous_raid_disks - conf->max_degraded;
		पूर्णांक stripe = data_disks *
			((mddev->chunk_sectors << 9) / PAGE_SIZE);

		chunk_size = mddev->chunk_sectors << 9;
		blk_queue_io_min(mddev->queue, chunk_size);
		raid5_set_io_opt(conf);
		mddev->queue->limits.raid_partial_stripes_expensive = 1;
		/*
		 * We can only discard a whole stripe. It करोesn't make sense to
		 * discard data disk but ग_लिखो parity disk
		 */
		stripe = stripe * PAGE_SIZE;
		/* Round up to घातer of 2, as discard handling
		 * currently assumes that */
		जबतक ((stripe-1) & stripe)
			stripe = (stripe | (stripe-1)) + 1;
		mddev->queue->limits.discard_alignment = stripe;
		mddev->queue->limits.discard_granularity = stripe;

		blk_queue_max_ग_लिखो_same_sectors(mddev->queue, 0);
		blk_queue_max_ग_लिखो_zeroes_sectors(mddev->queue, 0);

		rdev_क्रम_each(rdev, mddev) अणु
			disk_stack_limits(mddev->gendisk, rdev->bdev,
					  rdev->data_offset << 9);
			disk_stack_limits(mddev->gendisk, rdev->bdev,
					  rdev->new_data_offset << 9);
		पूर्ण

		/*
		 * zeroing is required, otherwise data
		 * could be lost. Consider a scenario: discard a stripe
		 * (the stripe could be inconsistent अगर
		 * discard_zeroes_data is 0); ग_लिखो one disk of the
		 * stripe (the stripe could be inconsistent again
		 * depending on which disks are used to calculate
		 * parity); the disk is broken; The stripe data of this
		 * disk is lost.
		 *
		 * We only allow DISCARD अगर the sysadmin has confirmed that
		 * only safe devices are in use by setting a module parameter.
		 * A better idea might be to turn DISCARD पूर्णांकo WRITE_ZEROES
		 * requests, as that is required to be safe.
		 */
		अगर (devices_handle_discard_safely &&
		    mddev->queue->limits.max_discard_sectors >= (stripe >> 9) &&
		    mddev->queue->limits.discard_granularity >= stripe)
			blk_queue_flag_set(QUEUE_FLAG_DISCARD,
						mddev->queue);
		अन्यथा
			blk_queue_flag_clear(QUEUE_FLAG_DISCARD,
						mddev->queue);

		blk_queue_max_hw_sectors(mddev->queue, अच_पूर्णांक_उच्च);
	पूर्ण

	अगर (log_init(conf, journal_dev, raid5_has_ppl(conf)))
		जाओ पात;

	वापस 0;
पात:
	md_unरेजिस्टर_thपढ़ो(&mddev->thपढ़ो);
	prपूर्णांक_raid5_conf(conf);
	मुक्त_conf(conf);
	mddev->निजी = शून्य;
	pr_warn("md/raid:%s: failed to run raid set.\n", mdname(mddev));
	वापस -EIO;
पूर्ण

अटल व्योम raid5_मुक्त(काष्ठा mddev *mddev, व्योम *priv)
अणु
	काष्ठा r5conf *conf = priv;

	मुक्त_conf(conf);
	mddev->to_हटाओ = &raid5_attrs_group;
पूर्ण

अटल व्योम raid5_status(काष्ठा seq_file *seq, काष्ठा mddev *mddev)
अणु
	काष्ठा r5conf *conf = mddev->निजी;
	पूर्णांक i;

	seq_म_लिखो(seq, " level %d, %dk chunk, algorithm %d", mddev->level,
		conf->chunk_sectors / 2, mddev->layout);
	seq_म_लिखो (seq, " [%d/%d] [", conf->raid_disks, conf->raid_disks - mddev->degraded);
	rcu_पढ़ो_lock();
	क्रम (i = 0; i < conf->raid_disks; i++) अणु
		काष्ठा md_rdev *rdev = rcu_dereference(conf->disks[i].rdev);
		seq_म_लिखो (seq, "%s", rdev && test_bit(In_sync, &rdev->flags) ? "U" : "_");
	पूर्ण
	rcu_पढ़ो_unlock();
	seq_म_लिखो (seq, "]");
पूर्ण

अटल व्योम prपूर्णांक_raid5_conf (काष्ठा r5conf *conf)
अणु
	पूर्णांक i;
	काष्ठा disk_info *पंचांगp;

	pr_debug("RAID conf printout:\n");
	अगर (!conf) अणु
		pr_debug("(conf==NULL)\n");
		वापस;
	पूर्ण
	pr_debug(" --- level:%d rd:%d wd:%d\n", conf->level,
	       conf->raid_disks,
	       conf->raid_disks - conf->mddev->degraded);

	क्रम (i = 0; i < conf->raid_disks; i++) अणु
		अक्षर b[BDEVNAME_SIZE];
		पंचांगp = conf->disks + i;
		अगर (पंचांगp->rdev)
			pr_debug(" disk %d, o:%d, dev:%s\n",
			       i, !test_bit(Faulty, &पंचांगp->rdev->flags),
			       bdevname(पंचांगp->rdev->bdev, b));
	पूर्ण
पूर्ण

अटल पूर्णांक raid5_spare_active(काष्ठा mddev *mddev)
अणु
	पूर्णांक i;
	काष्ठा r5conf *conf = mddev->निजी;
	काष्ठा disk_info *पंचांगp;
	पूर्णांक count = 0;
	अचिन्हित दीर्घ flags;

	क्रम (i = 0; i < conf->raid_disks; i++) अणु
		पंचांगp = conf->disks + i;
		अगर (पंचांगp->replacement
		    && पंचांगp->replacement->recovery_offset == MaxSector
		    && !test_bit(Faulty, &पंचांगp->replacement->flags)
		    && !test_and_set_bit(In_sync, &पंचांगp->replacement->flags)) अणु
			/* Replacement has just become active. */
			अगर (!पंचांगp->rdev
			    || !test_and_clear_bit(In_sync, &पंचांगp->rdev->flags))
				count++;
			अगर (पंचांगp->rdev) अणु
				/* Replaced device not technically faulty,
				 * but we need to be sure it माला_लो हटाओd
				 * and never re-added.
				 */
				set_bit(Faulty, &पंचांगp->rdev->flags);
				sysfs_notअगरy_dirent_safe(
					पंचांगp->rdev->sysfs_state);
			पूर्ण
			sysfs_notअगरy_dirent_safe(पंचांगp->replacement->sysfs_state);
		पूर्ण अन्यथा अगर (पंचांगp->rdev
		    && पंचांगp->rdev->recovery_offset == MaxSector
		    && !test_bit(Faulty, &पंचांगp->rdev->flags)
		    && !test_and_set_bit(In_sync, &पंचांगp->rdev->flags)) अणु
			count++;
			sysfs_notअगरy_dirent_safe(पंचांगp->rdev->sysfs_state);
		पूर्ण
	पूर्ण
	spin_lock_irqsave(&conf->device_lock, flags);
	mddev->degraded = raid5_calc_degraded(conf);
	spin_unlock_irqrestore(&conf->device_lock, flags);
	prपूर्णांक_raid5_conf(conf);
	वापस count;
पूर्ण

अटल पूर्णांक raid5_हटाओ_disk(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	काष्ठा r5conf *conf = mddev->निजी;
	पूर्णांक err = 0;
	पूर्णांक number = rdev->raid_disk;
	काष्ठा md_rdev **rdevp;
	काष्ठा disk_info *p = conf->disks + number;

	prपूर्णांक_raid5_conf(conf);
	अगर (test_bit(Journal, &rdev->flags) && conf->log) अणु
		/*
		 * we can't रुको pending ग_लिखो here, as this is called in
		 * raid5d, रुको will deadlock.
		 * neilb: there is no locking about new ग_लिखोs here,
		 * so this cannot be safe.
		 */
		अगर (atomic_पढ़ो(&conf->active_stripes) ||
		    atomic_पढ़ो(&conf->r5c_cached_full_stripes) ||
		    atomic_पढ़ो(&conf->r5c_cached_partial_stripes)) अणु
			वापस -EBUSY;
		पूर्ण
		log_निकास(conf);
		वापस 0;
	पूर्ण
	अगर (rdev == p->rdev)
		rdevp = &p->rdev;
	अन्यथा अगर (rdev == p->replacement)
		rdevp = &p->replacement;
	अन्यथा
		वापस 0;

	अगर (number >= conf->raid_disks &&
	    conf->reshape_progress == MaxSector)
		clear_bit(In_sync, &rdev->flags);

	अगर (test_bit(In_sync, &rdev->flags) ||
	    atomic_पढ़ो(&rdev->nr_pending)) अणु
		err = -EBUSY;
		जाओ पात;
	पूर्ण
	/* Only हटाओ non-faulty devices अगर recovery
	 * isn't possible.
	 */
	अगर (!test_bit(Faulty, &rdev->flags) &&
	    mddev->recovery_disabled != conf->recovery_disabled &&
	    !has_failed(conf) &&
	    (!p->replacement || p->replacement == rdev) &&
	    number < conf->raid_disks) अणु
		err = -EBUSY;
		जाओ पात;
	पूर्ण
	*rdevp = शून्य;
	अगर (!test_bit(RemoveSynchronized, &rdev->flags)) अणु
		synchronize_rcu();
		अगर (atomic_पढ़ो(&rdev->nr_pending)) अणु
			/* lost the race, try later */
			err = -EBUSY;
			*rdevp = rdev;
		पूर्ण
	पूर्ण
	अगर (!err) अणु
		err = log_modअगरy(conf, rdev, false);
		अगर (err)
			जाओ पात;
	पूर्ण
	अगर (p->replacement) अणु
		/* We must have just cleared 'rdev' */
		p->rdev = p->replacement;
		clear_bit(Replacement, &p->replacement->flags);
		smp_mb(); /* Make sure other CPUs may see both as identical
			   * but will never see neither - अगर they are careful
			   */
		p->replacement = शून्य;

		अगर (!err)
			err = log_modअगरy(conf, p->rdev, true);
	पूर्ण

	clear_bit(WantReplacement, &rdev->flags);
पात:

	prपूर्णांक_raid5_conf(conf);
	वापस err;
पूर्ण

अटल पूर्णांक raid5_add_disk(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	काष्ठा r5conf *conf = mddev->निजी;
	पूर्णांक ret, err = -EEXIST;
	पूर्णांक disk;
	काष्ठा disk_info *p;
	पूर्णांक first = 0;
	पूर्णांक last = conf->raid_disks - 1;

	अगर (test_bit(Journal, &rdev->flags)) अणु
		अगर (conf->log)
			वापस -EBUSY;

		rdev->raid_disk = 0;
		/*
		 * The array is in पढ़ोonly mode अगर journal is missing, so no
		 * ग_लिखो requests running. We should be safe
		 */
		ret = log_init(conf, rdev, false);
		अगर (ret)
			वापस ret;

		ret = r5l_start(conf->log);
		अगर (ret)
			वापस ret;

		वापस 0;
	पूर्ण
	अगर (mddev->recovery_disabled == conf->recovery_disabled)
		वापस -EBUSY;

	अगर (rdev->saved_raid_disk < 0 && has_failed(conf))
		/* no poपूर्णांक adding a device */
		वापस -EINVAL;

	अगर (rdev->raid_disk >= 0)
		first = last = rdev->raid_disk;

	/*
	 * find the disk ... but prefer rdev->saved_raid_disk
	 * अगर possible.
	 */
	अगर (rdev->saved_raid_disk >= 0 &&
	    rdev->saved_raid_disk >= first &&
	    conf->disks[rdev->saved_raid_disk].rdev == शून्य)
		first = rdev->saved_raid_disk;

	क्रम (disk = first; disk <= last; disk++) अणु
		p = conf->disks + disk;
		अगर (p->rdev == शून्य) अणु
			clear_bit(In_sync, &rdev->flags);
			rdev->raid_disk = disk;
			अगर (rdev->saved_raid_disk != disk)
				conf->fullsync = 1;
			rcu_assign_poपूर्णांकer(p->rdev, rdev);

			err = log_modअगरy(conf, rdev, true);

			जाओ out;
		पूर्ण
	पूर्ण
	क्रम (disk = first; disk <= last; disk++) अणु
		p = conf->disks + disk;
		अगर (test_bit(WantReplacement, &p->rdev->flags) &&
		    p->replacement == शून्य) अणु
			clear_bit(In_sync, &rdev->flags);
			set_bit(Replacement, &rdev->flags);
			rdev->raid_disk = disk;
			err = 0;
			conf->fullsync = 1;
			rcu_assign_poपूर्णांकer(p->replacement, rdev);
			अवरोध;
		पूर्ण
	पूर्ण
out:
	prपूर्णांक_raid5_conf(conf);
	वापस err;
पूर्ण

अटल पूर्णांक raid5_resize(काष्ठा mddev *mddev, sector_t sectors)
अणु
	/* no resync is happening, and there is enough space
	 * on all devices, so we can resize.
	 * We need to make sure resync covers any new space.
	 * If the array is shrinking we should possibly रुको until
	 * any io in the हटाओd space completes, but it hardly seems
	 * worth it.
	 */
	sector_t newsize;
	काष्ठा r5conf *conf = mddev->निजी;

	अगर (raid5_has_log(conf) || raid5_has_ppl(conf))
		वापस -EINVAL;
	sectors &= ~((sector_t)conf->chunk_sectors - 1);
	newsize = raid5_size(mddev, sectors, mddev->raid_disks);
	अगर (mddev->बाह्यal_size &&
	    mddev->array_sectors > newsize)
		वापस -EINVAL;
	अगर (mddev->biपंचांगap) अणु
		पूर्णांक ret = md_biपंचांगap_resize(mddev->biपंचांगap, sectors, 0, 0);
		अगर (ret)
			वापस ret;
	पूर्ण
	md_set_array_sectors(mddev, newsize);
	अगर (sectors > mddev->dev_sectors &&
	    mddev->recovery_cp > mddev->dev_sectors) अणु
		mddev->recovery_cp = mddev->dev_sectors;
		set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
	पूर्ण
	mddev->dev_sectors = sectors;
	mddev->resync_max_sectors = sectors;
	वापस 0;
पूर्ण

अटल पूर्णांक check_stripe_cache(काष्ठा mddev *mddev)
अणु
	/* Can only proceed अगर there are plenty of stripe_heads.
	 * We need a minimum of one full stripe,, and क्रम sensible progress
	 * it is best to have about 4 बार that.
	 * If we require 4 बार, then the शेष 256 4K stripe_heads will
	 * allow क्रम chunk sizes up to 256K, which is probably OK.
	 * If the chunk size is greater, user-space should request more
	 * stripe_heads first.
	 */
	काष्ठा r5conf *conf = mddev->निजी;
	अगर (((mddev->chunk_sectors << 9) / RAID5_STRIPE_SIZE(conf)) * 4
	    > conf->min_nr_stripes ||
	    ((mddev->new_chunk_sectors << 9) / RAID5_STRIPE_SIZE(conf)) * 4
	    > conf->min_nr_stripes) अणु
		pr_warn("md/raid:%s: reshape: not enough stripes.  Needed %lu\n",
			mdname(mddev),
			((max(mddev->chunk_sectors, mddev->new_chunk_sectors) << 9)
			 / RAID5_STRIPE_SIZE(conf))*4);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक check_reshape(काष्ठा mddev *mddev)
अणु
	काष्ठा r5conf *conf = mddev->निजी;

	अगर (raid5_has_log(conf) || raid5_has_ppl(conf))
		वापस -EINVAL;
	अगर (mddev->delta_disks == 0 &&
	    mddev->new_layout == mddev->layout &&
	    mddev->new_chunk_sectors == mddev->chunk_sectors)
		वापस 0; /* nothing to करो */
	अगर (has_failed(conf))
		वापस -EINVAL;
	अगर (mddev->delta_disks < 0 && mddev->reshape_position == MaxSector) अणु
		/* We might be able to shrink, but the devices must
		 * be made bigger first.
		 * For raid6, 4 is the minimum size.
		 * Otherwise 2 is the minimum
		 */
		पूर्णांक min = 2;
		अगर (mddev->level == 6)
			min = 4;
		अगर (mddev->raid_disks + mddev->delta_disks < min)
			वापस -EINVAL;
	पूर्ण

	अगर (!check_stripe_cache(mddev))
		वापस -ENOSPC;

	अगर (mddev->new_chunk_sectors > mddev->chunk_sectors ||
	    mddev->delta_disks > 0)
		अगर (resize_chunks(conf,
				  conf->previous_raid_disks
				  + max(0, mddev->delta_disks),
				  max(mddev->new_chunk_sectors,
				      mddev->chunk_sectors)
			    ) < 0)
			वापस -ENOMEM;

	अगर (conf->previous_raid_disks + mddev->delta_disks <= conf->pool_size)
		वापस 0; /* never bother to shrink */
	वापस resize_stripes(conf, (conf->previous_raid_disks
				     + mddev->delta_disks));
पूर्ण

अटल पूर्णांक raid5_start_reshape(काष्ठा mddev *mddev)
अणु
	काष्ठा r5conf *conf = mddev->निजी;
	काष्ठा md_rdev *rdev;
	पूर्णांक spares = 0;
	अचिन्हित दीर्घ flags;

	अगर (test_bit(MD_RECOVERY_RUNNING, &mddev->recovery))
		वापस -EBUSY;

	अगर (!check_stripe_cache(mddev))
		वापस -ENOSPC;

	अगर (has_failed(conf))
		वापस -EINVAL;

	rdev_क्रम_each(rdev, mddev) अणु
		अगर (!test_bit(In_sync, &rdev->flags)
		    && !test_bit(Faulty, &rdev->flags))
			spares++;
	पूर्ण

	अगर (spares - mddev->degraded < mddev->delta_disks - conf->max_degraded)
		/* Not enough devices even to make a degraded array
		 * of that size
		 */
		वापस -EINVAL;

	/* Refuse to reduce size of the array.  Any reductions in
	 * array size must be through explicit setting of array_size
	 * attribute.
	 */
	अगर (raid5_size(mddev, 0, conf->raid_disks + mddev->delta_disks)
	    < mddev->array_sectors) अणु
		pr_warn("md/raid:%s: array size must be reduced before number of disks\n",
			mdname(mddev));
		वापस -EINVAL;
	पूर्ण

	atomic_set(&conf->reshape_stripes, 0);
	spin_lock_irq(&conf->device_lock);
	ग_लिखो_seqcount_begin(&conf->gen_lock);
	conf->previous_raid_disks = conf->raid_disks;
	conf->raid_disks += mddev->delta_disks;
	conf->prev_chunk_sectors = conf->chunk_sectors;
	conf->chunk_sectors = mddev->new_chunk_sectors;
	conf->prev_algo = conf->algorithm;
	conf->algorithm = mddev->new_layout;
	conf->generation++;
	/* Code that selects data_offset needs to see the generation update
	 * अगर reshape_progress has been set - so a memory barrier needed.
	 */
	smp_mb();
	अगर (mddev->reshape_backwards)
		conf->reshape_progress = raid5_size(mddev, 0, 0);
	अन्यथा
		conf->reshape_progress = 0;
	conf->reshape_safe = conf->reshape_progress;
	ग_लिखो_seqcount_end(&conf->gen_lock);
	spin_unlock_irq(&conf->device_lock);

	/* Now make sure any requests that proceeded on the assumption
	 * the reshape wasn't running - like Discard or Read - have
	 * completed.
	 */
	mddev_suspend(mddev);
	mddev_resume(mddev);

	/* Add some new drives, as many as will fit.
	 * We know there are enough to make the newly sized array work.
	 * Don't add devices अगर we are reducing the number of
	 * devices in the array.  This is because it is not possible
	 * to correctly record the "partially reconstructed" state of
	 * such devices during the reshape and confusion could result.
	 */
	अगर (mddev->delta_disks >= 0) अणु
		rdev_क्रम_each(rdev, mddev)
			अगर (rdev->raid_disk < 0 &&
			    !test_bit(Faulty, &rdev->flags)) अणु
				अगर (raid5_add_disk(mddev, rdev) == 0) अणु
					अगर (rdev->raid_disk
					    >= conf->previous_raid_disks)
						set_bit(In_sync, &rdev->flags);
					अन्यथा
						rdev->recovery_offset = 0;

					/* Failure here is OK */
					sysfs_link_rdev(mddev, rdev);
				पूर्ण
			पूर्ण अन्यथा अगर (rdev->raid_disk >= conf->previous_raid_disks
				   && !test_bit(Faulty, &rdev->flags)) अणु
				/* This is a spare that was manually added */
				set_bit(In_sync, &rdev->flags);
			पूर्ण

		/* When a reshape changes the number of devices,
		 * ->degraded is measured against the larger of the
		 * pre and post number of devices.
		 */
		spin_lock_irqsave(&conf->device_lock, flags);
		mddev->degraded = raid5_calc_degraded(conf);
		spin_unlock_irqrestore(&conf->device_lock, flags);
	पूर्ण
	mddev->raid_disks = conf->raid_disks;
	mddev->reshape_position = conf->reshape_progress;
	set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);

	clear_bit(MD_RECOVERY_SYNC, &mddev->recovery);
	clear_bit(MD_RECOVERY_CHECK, &mddev->recovery);
	clear_bit(MD_RECOVERY_DONE, &mddev->recovery);
	set_bit(MD_RECOVERY_RESHAPE, &mddev->recovery);
	set_bit(MD_RECOVERY_RUNNING, &mddev->recovery);
	mddev->sync_thपढ़ो = md_रेजिस्टर_thपढ़ो(md_करो_sync, mddev,
						"reshape");
	अगर (!mddev->sync_thपढ़ो) अणु
		mddev->recovery = 0;
		spin_lock_irq(&conf->device_lock);
		ग_लिखो_seqcount_begin(&conf->gen_lock);
		mddev->raid_disks = conf->raid_disks = conf->previous_raid_disks;
		mddev->new_chunk_sectors =
			conf->chunk_sectors = conf->prev_chunk_sectors;
		mddev->new_layout = conf->algorithm = conf->prev_algo;
		rdev_क्रम_each(rdev, mddev)
			rdev->new_data_offset = rdev->data_offset;
		smp_wmb();
		conf->generation --;
		conf->reshape_progress = MaxSector;
		mddev->reshape_position = MaxSector;
		ग_लिखो_seqcount_end(&conf->gen_lock);
		spin_unlock_irq(&conf->device_lock);
		वापस -EAGAIN;
	पूर्ण
	conf->reshape_checkpoपूर्णांक = jअगरfies;
	md_wakeup_thपढ़ो(mddev->sync_thपढ़ो);
	md_new_event(mddev);
	वापस 0;
पूर्ण

/* This is called from the reshape thपढ़ो and should make any
 * changes needed in 'conf'
 */
अटल व्योम end_reshape(काष्ठा r5conf *conf)
अणु

	अगर (!test_bit(MD_RECOVERY_INTR, &conf->mddev->recovery)) अणु
		काष्ठा md_rdev *rdev;

		spin_lock_irq(&conf->device_lock);
		conf->previous_raid_disks = conf->raid_disks;
		md_finish_reshape(conf->mddev);
		smp_wmb();
		conf->reshape_progress = MaxSector;
		conf->mddev->reshape_position = MaxSector;
		rdev_क्रम_each(rdev, conf->mddev)
			अगर (rdev->raid_disk >= 0 &&
			    !test_bit(Journal, &rdev->flags) &&
			    !test_bit(In_sync, &rdev->flags))
				rdev->recovery_offset = MaxSector;
		spin_unlock_irq(&conf->device_lock);
		wake_up(&conf->रुको_क्रम_overlap);

		अगर (conf->mddev->queue)
			raid5_set_io_opt(conf);
	पूर्ण
पूर्ण

/* This is called from the raid5d thपढ़ो with mddev_lock held.
 * It makes config changes to the device.
 */
अटल व्योम raid5_finish_reshape(काष्ठा mddev *mddev)
अणु
	काष्ठा r5conf *conf = mddev->निजी;

	अगर (!test_bit(MD_RECOVERY_INTR, &mddev->recovery)) अणु

		अगर (mddev->delta_disks <= 0) अणु
			पूर्णांक d;
			spin_lock_irq(&conf->device_lock);
			mddev->degraded = raid5_calc_degraded(conf);
			spin_unlock_irq(&conf->device_lock);
			क्रम (d = conf->raid_disks ;
			     d < conf->raid_disks - mddev->delta_disks;
			     d++) अणु
				काष्ठा md_rdev *rdev = conf->disks[d].rdev;
				अगर (rdev)
					clear_bit(In_sync, &rdev->flags);
				rdev = conf->disks[d].replacement;
				अगर (rdev)
					clear_bit(In_sync, &rdev->flags);
			पूर्ण
		पूर्ण
		mddev->layout = conf->algorithm;
		mddev->chunk_sectors = conf->chunk_sectors;
		mddev->reshape_position = MaxSector;
		mddev->delta_disks = 0;
		mddev->reshape_backwards = 0;
	पूर्ण
पूर्ण

अटल व्योम raid5_quiesce(काष्ठा mddev *mddev, पूर्णांक quiesce)
अणु
	काष्ठा r5conf *conf = mddev->निजी;

	अगर (quiesce) अणु
		/* stop all ग_लिखोs */
		lock_all_device_hash_locks_irq(conf);
		/* '2' tells resync/reshape to छोड़ो so that all
		 * active stripes can drain
		 */
		r5c_flush_cache(conf, पूर्णांक_उच्च);
		conf->quiesce = 2;
		रुको_event_cmd(conf->रुको_क्रम_quiescent,
				    atomic_पढ़ो(&conf->active_stripes) == 0 &&
				    atomic_पढ़ो(&conf->active_aligned_पढ़ोs) == 0,
				    unlock_all_device_hash_locks_irq(conf),
				    lock_all_device_hash_locks_irq(conf));
		conf->quiesce = 1;
		unlock_all_device_hash_locks_irq(conf);
		/* allow reshape to जारी */
		wake_up(&conf->रुको_क्रम_overlap);
	पूर्ण अन्यथा अणु
		/* re-enable ग_लिखोs */
		lock_all_device_hash_locks_irq(conf);
		conf->quiesce = 0;
		wake_up(&conf->रुको_क्रम_quiescent);
		wake_up(&conf->रुको_क्रम_overlap);
		unlock_all_device_hash_locks_irq(conf);
	पूर्ण
	log_quiesce(conf, quiesce);
पूर्ण

अटल व्योम *raid45_takeover_raid0(काष्ठा mddev *mddev, पूर्णांक level)
अणु
	काष्ठा r0conf *raid0_conf = mddev->निजी;
	sector_t sectors;

	/* क्रम raid0 takeover only one zone is supported */
	अगर (raid0_conf->nr_strip_zones > 1) अणु
		pr_warn("md/raid:%s: cannot takeover raid0 with more than one zone.\n",
			mdname(mddev));
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	sectors = raid0_conf->strip_zone[0].zone_end;
	sector_भाग(sectors, raid0_conf->strip_zone[0].nb_dev);
	mddev->dev_sectors = sectors;
	mddev->new_level = level;
	mddev->new_layout = ALGORITHM_PARITY_N;
	mddev->new_chunk_sectors = mddev->chunk_sectors;
	mddev->raid_disks += 1;
	mddev->delta_disks = 1;
	/* make sure it will be not marked as dirty */
	mddev->recovery_cp = MaxSector;

	वापस setup_conf(mddev);
पूर्ण

अटल व्योम *raid5_takeover_raid1(काष्ठा mddev *mddev)
अणु
	पूर्णांक chunksect;
	व्योम *ret;

	अगर (mddev->raid_disks != 2 ||
	    mddev->degraded > 1)
		वापस ERR_PTR(-EINVAL);

	/* Should check अगर there are ग_लिखो-behind devices? */

	chunksect = 64*2; /* 64K by शेष */

	/* The array must be an exact multiple of chunksize */
	जबतक (chunksect && (mddev->array_sectors & (chunksect-1)))
		chunksect >>= 1;

	अगर ((chunksect<<9) < RAID5_STRIPE_SIZE((काष्ठा r5conf *)mddev->निजी))
		/* array size करोes not allow a suitable chunk size */
		वापस ERR_PTR(-EINVAL);

	mddev->new_level = 5;
	mddev->new_layout = ALGORITHM_LEFT_SYMMETRIC;
	mddev->new_chunk_sectors = chunksect;

	ret = setup_conf(mddev);
	अगर (!IS_ERR(ret))
		mddev_clear_unsupported_flags(mddev,
			UNSUPPORTED_MDDEV_FLAGS);
	वापस ret;
पूर्ण

अटल व्योम *raid5_takeover_raid6(काष्ठा mddev *mddev)
अणु
	पूर्णांक new_layout;

	चयन (mddev->layout) अणु
	हाल ALGORITHM_LEFT_ASYMMETRIC_6:
		new_layout = ALGORITHM_LEFT_ASYMMETRIC;
		अवरोध;
	हाल ALGORITHM_RIGHT_ASYMMETRIC_6:
		new_layout = ALGORITHM_RIGHT_ASYMMETRIC;
		अवरोध;
	हाल ALGORITHM_LEFT_SYMMETRIC_6:
		new_layout = ALGORITHM_LEFT_SYMMETRIC;
		अवरोध;
	हाल ALGORITHM_RIGHT_SYMMETRIC_6:
		new_layout = ALGORITHM_RIGHT_SYMMETRIC;
		अवरोध;
	हाल ALGORITHM_PARITY_0_6:
		new_layout = ALGORITHM_PARITY_0;
		अवरोध;
	हाल ALGORITHM_PARITY_N:
		new_layout = ALGORITHM_PARITY_N;
		अवरोध;
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	mddev->new_level = 5;
	mddev->new_layout = new_layout;
	mddev->delta_disks = -1;
	mddev->raid_disks -= 1;
	वापस setup_conf(mddev);
पूर्ण

अटल पूर्णांक raid5_check_reshape(काष्ठा mddev *mddev)
अणु
	/* For a 2-drive array, the layout and chunk size can be changed
	 * immediately as not restriping is needed.
	 * For larger arrays we record the new value - after validation
	 * to be used by a reshape pass.
	 */
	काष्ठा r5conf *conf = mddev->निजी;
	पूर्णांक new_chunk = mddev->new_chunk_sectors;

	अगर (mddev->new_layout >= 0 && !algorithm_valid_raid5(mddev->new_layout))
		वापस -EINVAL;
	अगर (new_chunk > 0) अणु
		अगर (!is_घातer_of_2(new_chunk))
			वापस -EINVAL;
		अगर (new_chunk < (PAGE_SIZE>>9))
			वापस -EINVAL;
		अगर (mddev->array_sectors & (new_chunk-1))
			/* not factor of array size */
			वापस -EINVAL;
	पूर्ण

	/* They look valid */

	अगर (mddev->raid_disks == 2) अणु
		/* can make the change immediately */
		अगर (mddev->new_layout >= 0) अणु
			conf->algorithm = mddev->new_layout;
			mddev->layout = mddev->new_layout;
		पूर्ण
		अगर (new_chunk > 0) अणु
			conf->chunk_sectors = new_chunk ;
			mddev->chunk_sectors = new_chunk;
		पूर्ण
		set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
		md_wakeup_thपढ़ो(mddev->thपढ़ो);
	पूर्ण
	वापस check_reshape(mddev);
पूर्ण

अटल पूर्णांक raid6_check_reshape(काष्ठा mddev *mddev)
अणु
	पूर्णांक new_chunk = mddev->new_chunk_sectors;

	अगर (mddev->new_layout >= 0 && !algorithm_valid_raid6(mddev->new_layout))
		वापस -EINVAL;
	अगर (new_chunk > 0) अणु
		अगर (!is_घातer_of_2(new_chunk))
			वापस -EINVAL;
		अगर (new_chunk < (PAGE_SIZE >> 9))
			वापस -EINVAL;
		अगर (mddev->array_sectors & (new_chunk-1))
			/* not factor of array size */
			वापस -EINVAL;
	पूर्ण

	/* They look valid */
	वापस check_reshape(mddev);
पूर्ण

अटल व्योम *raid5_takeover(काष्ठा mddev *mddev)
अणु
	/* raid5 can take over:
	 *  raid0 - अगर there is only one strip zone - make it a raid4 layout
	 *  raid1 - अगर there are two drives.  We need to know the chunk size
	 *  raid4 - trivial - just use a raid4 layout.
	 *  raid6 - Providing it is a *_6 layout
	 */
	अगर (mddev->level == 0)
		वापस raid45_takeover_raid0(mddev, 5);
	अगर (mddev->level == 1)
		वापस raid5_takeover_raid1(mddev);
	अगर (mddev->level == 4) अणु
		mddev->new_layout = ALGORITHM_PARITY_N;
		mddev->new_level = 5;
		वापस setup_conf(mddev);
	पूर्ण
	अगर (mddev->level == 6)
		वापस raid5_takeover_raid6(mddev);

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल व्योम *raid4_takeover(काष्ठा mddev *mddev)
अणु
	/* raid4 can take over:
	 *  raid0 - अगर there is only one strip zone
	 *  raid5 - अगर layout is right
	 */
	अगर (mddev->level == 0)
		वापस raid45_takeover_raid0(mddev, 4);
	अगर (mddev->level == 5 &&
	    mddev->layout == ALGORITHM_PARITY_N) अणु
		mddev->new_layout = 0;
		mddev->new_level = 4;
		वापस setup_conf(mddev);
	पूर्ण
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल काष्ठा md_personality raid5_personality;

अटल व्योम *raid6_takeover(काष्ठा mddev *mddev)
अणु
	/* Currently can only take over a raid5.  We map the
	 * personality to an equivalent raid6 personality
	 * with the Q block at the end.
	 */
	पूर्णांक new_layout;

	अगर (mddev->pers != &raid5_personality)
		वापस ERR_PTR(-EINVAL);
	अगर (mddev->degraded > 1)
		वापस ERR_PTR(-EINVAL);
	अगर (mddev->raid_disks > 253)
		वापस ERR_PTR(-EINVAL);
	अगर (mddev->raid_disks < 3)
		वापस ERR_PTR(-EINVAL);

	चयन (mddev->layout) अणु
	हाल ALGORITHM_LEFT_ASYMMETRIC:
		new_layout = ALGORITHM_LEFT_ASYMMETRIC_6;
		अवरोध;
	हाल ALGORITHM_RIGHT_ASYMMETRIC:
		new_layout = ALGORITHM_RIGHT_ASYMMETRIC_6;
		अवरोध;
	हाल ALGORITHM_LEFT_SYMMETRIC:
		new_layout = ALGORITHM_LEFT_SYMMETRIC_6;
		अवरोध;
	हाल ALGORITHM_RIGHT_SYMMETRIC:
		new_layout = ALGORITHM_RIGHT_SYMMETRIC_6;
		अवरोध;
	हाल ALGORITHM_PARITY_0:
		new_layout = ALGORITHM_PARITY_0_6;
		अवरोध;
	हाल ALGORITHM_PARITY_N:
		new_layout = ALGORITHM_PARITY_N;
		अवरोध;
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	mddev->new_level = 6;
	mddev->new_layout = new_layout;
	mddev->delta_disks = 1;
	mddev->raid_disks += 1;
	वापस setup_conf(mddev);
पूर्ण

अटल पूर्णांक raid5_change_consistency_policy(काष्ठा mddev *mddev, स्थिर अक्षर *buf)
अणु
	काष्ठा r5conf *conf;
	पूर्णांक err;

	err = mddev_lock(mddev);
	अगर (err)
		वापस err;
	conf = mddev->निजी;
	अगर (!conf) अणु
		mddev_unlock(mddev);
		वापस -ENODEV;
	पूर्ण

	अगर (म_भेदन(buf, "ppl", 3) == 0) अणु
		/* ppl only works with RAID 5 */
		अगर (!raid5_has_ppl(conf) && conf->level == 5) अणु
			err = log_init(conf, शून्य, true);
			अगर (!err) अणु
				err = resize_stripes(conf, conf->pool_size);
				अगर (err)
					log_निकास(conf);
			पूर्ण
		पूर्ण अन्यथा
			err = -EINVAL;
	पूर्ण अन्यथा अगर (म_भेदन(buf, "resync", 6) == 0) अणु
		अगर (raid5_has_ppl(conf)) अणु
			mddev_suspend(mddev);
			log_निकास(conf);
			mddev_resume(mddev);
			err = resize_stripes(conf, conf->pool_size);
		पूर्ण अन्यथा अगर (test_bit(MD_HAS_JOURNAL, &conf->mddev->flags) &&
			   r5l_log_disk_error(conf)) अणु
			bool journal_dev_exists = false;
			काष्ठा md_rdev *rdev;

			rdev_क्रम_each(rdev, mddev)
				अगर (test_bit(Journal, &rdev->flags)) अणु
					journal_dev_exists = true;
					अवरोध;
				पूर्ण

			अगर (!journal_dev_exists) अणु
				mddev_suspend(mddev);
				clear_bit(MD_HAS_JOURNAL, &mddev->flags);
				mddev_resume(mddev);
			पूर्ण अन्यथा  /* need हटाओ journal device first */
				err = -EBUSY;
		पूर्ण अन्यथा
			err = -EINVAL;
	पूर्ण अन्यथा अणु
		err = -EINVAL;
	पूर्ण

	अगर (!err)
		md_update_sb(mddev, 1);

	mddev_unlock(mddev);

	वापस err;
पूर्ण

अटल पूर्णांक raid5_start(काष्ठा mddev *mddev)
अणु
	काष्ठा r5conf *conf = mddev->निजी;

	वापस r5l_start(conf->log);
पूर्ण

अटल काष्ठा md_personality raid6_personality =
अणु
	.name		= "raid6",
	.level		= 6,
	.owner		= THIS_MODULE,
	.make_request	= raid5_make_request,
	.run		= raid5_run,
	.start		= raid5_start,
	.मुक्त		= raid5_मुक्त,
	.status		= raid5_status,
	.error_handler	= raid5_error,
	.hot_add_disk	= raid5_add_disk,
	.hot_हटाओ_disk= raid5_हटाओ_disk,
	.spare_active	= raid5_spare_active,
	.sync_request	= raid5_sync_request,
	.resize		= raid5_resize,
	.size		= raid5_size,
	.check_reshape	= raid6_check_reshape,
	.start_reshape  = raid5_start_reshape,
	.finish_reshape = raid5_finish_reshape,
	.quiesce	= raid5_quiesce,
	.takeover	= raid6_takeover,
	.change_consistency_policy = raid5_change_consistency_policy,
पूर्ण;
अटल काष्ठा md_personality raid5_personality =
अणु
	.name		= "raid5",
	.level		= 5,
	.owner		= THIS_MODULE,
	.make_request	= raid5_make_request,
	.run		= raid5_run,
	.start		= raid5_start,
	.मुक्त		= raid5_मुक्त,
	.status		= raid5_status,
	.error_handler	= raid5_error,
	.hot_add_disk	= raid5_add_disk,
	.hot_हटाओ_disk= raid5_हटाओ_disk,
	.spare_active	= raid5_spare_active,
	.sync_request	= raid5_sync_request,
	.resize		= raid5_resize,
	.size		= raid5_size,
	.check_reshape	= raid5_check_reshape,
	.start_reshape  = raid5_start_reshape,
	.finish_reshape = raid5_finish_reshape,
	.quiesce	= raid5_quiesce,
	.takeover	= raid5_takeover,
	.change_consistency_policy = raid5_change_consistency_policy,
पूर्ण;

अटल काष्ठा md_personality raid4_personality =
अणु
	.name		= "raid4",
	.level		= 4,
	.owner		= THIS_MODULE,
	.make_request	= raid5_make_request,
	.run		= raid5_run,
	.start		= raid5_start,
	.मुक्त		= raid5_मुक्त,
	.status		= raid5_status,
	.error_handler	= raid5_error,
	.hot_add_disk	= raid5_add_disk,
	.hot_हटाओ_disk= raid5_हटाओ_disk,
	.spare_active	= raid5_spare_active,
	.sync_request	= raid5_sync_request,
	.resize		= raid5_resize,
	.size		= raid5_size,
	.check_reshape	= raid5_check_reshape,
	.start_reshape  = raid5_start_reshape,
	.finish_reshape = raid5_finish_reshape,
	.quiesce	= raid5_quiesce,
	.takeover	= raid4_takeover,
	.change_consistency_policy = raid5_change_consistency_policy,
पूर्ण;

अटल पूर्णांक __init raid5_init(व्योम)
अणु
	पूर्णांक ret;

	raid5_wq = alloc_workqueue("raid5wq",
		WQ_UNBOUND|WQ_MEM_RECLAIM|WQ_CPU_INTENSIVE|WQ_SYSFS, 0);
	अगर (!raid5_wq)
		वापस -ENOMEM;

	ret = cpuhp_setup_state_multi(CPUHP_MD_RAID5_PREPARE,
				      "md/raid5:prepare",
				      raid456_cpu_up_prepare,
				      raid456_cpu_dead);
	अगर (ret) अणु
		destroy_workqueue(raid5_wq);
		वापस ret;
	पूर्ण
	रेजिस्टर_md_personality(&raid6_personality);
	रेजिस्टर_md_personality(&raid5_personality);
	रेजिस्टर_md_personality(&raid4_personality);
	वापस 0;
पूर्ण

अटल व्योम raid5_निकास(व्योम)
अणु
	unरेजिस्टर_md_personality(&raid6_personality);
	unरेजिस्टर_md_personality(&raid5_personality);
	unरेजिस्टर_md_personality(&raid4_personality);
	cpuhp_हटाओ_multi_state(CPUHP_MD_RAID5_PREPARE);
	destroy_workqueue(raid5_wq);
पूर्ण

module_init(raid5_init);
module_निकास(raid5_निकास);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("RAID4/5/6 (striping with parity) personality for MD");
MODULE_ALIAS("md-personality-4"); /* RAID5 */
MODULE_ALIAS("md-raid5");
MODULE_ALIAS("md-raid4");
MODULE_ALIAS("md-level-5");
MODULE_ALIAS("md-level-4");
MODULE_ALIAS("md-personality-8"); /* RAID6 */
MODULE_ALIAS("md-raid6");
MODULE_ALIAS("md-level-6");

/* This used to be two separate modules, they were: */
MODULE_ALIAS("raid5");
MODULE_ALIAS("raid6");
