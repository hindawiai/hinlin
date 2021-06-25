<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Virtio balloon implementation, inspired by Dor Laor and Marcelo
 * Tosatti's implementations.
 *
 *  Copyright 2008 Rusty Russell IBM Corporation
 */

#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_balloon.h>
#समावेश <linux/swap.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/balloon_compaction.h>
#समावेश <linux/oom.h>
#समावेश <linux/रुको.h>
#समावेश <linux/mm.h>
#समावेश <linux/mount.h>
#समावेश <linux/magic.h>
#समावेश <linux/pseuकरो_fs.h>
#समावेश <linux/page_reporting.h>

/*
 * Balloon device works in 4K page units.  So each page is poपूर्णांकed to by
 * multiple balloon pages.  All memory counters in this driver are in balloon
 * page units.
 */
#घोषणा VIRTIO_BALLOON_PAGES_PER_PAGE (अचिन्हित)(PAGE_SIZE >> VIRTIO_BALLOON_PFN_SHIFT)
#घोषणा VIRTIO_BALLOON_ARRAY_PFNS_MAX 256
/* Maximum number of (4k) pages to deflate on OOM notअगरications. */
#घोषणा VIRTIO_BALLOON_OOM_NR_PAGES 256
#घोषणा VIRTIO_BALLOON_OOM_NOTIFY_PRIORITY 80

#घोषणा VIRTIO_BALLOON_FREE_PAGE_ALLOC_FLAG (__GFP_NORETRY | __GFP_NOWARN | \
					     __GFP_NOMEMALLOC)
/* The order of मुक्त page blocks to report to host */
#घोषणा VIRTIO_BALLOON_HINT_BLOCK_ORDER (MAX_ORDER - 1)
/* The size of a मुक्त page block in bytes */
#घोषणा VIRTIO_BALLOON_HINT_BLOCK_BYTES \
	(1 << (VIRTIO_BALLOON_HINT_BLOCK_ORDER + PAGE_SHIFT))
#घोषणा VIRTIO_BALLOON_HINT_BLOCK_PAGES (1 << VIRTIO_BALLOON_HINT_BLOCK_ORDER)

#अगर_घोषित CONFIG_BALLOON_COMPACTION
अटल काष्ठा vfsmount *balloon_mnt;
#पूर्ण_अगर

क्रमागत virtio_balloon_vq अणु
	VIRTIO_BALLOON_VQ_INFLATE,
	VIRTIO_BALLOON_VQ_DEFLATE,
	VIRTIO_BALLOON_VQ_STATS,
	VIRTIO_BALLOON_VQ_FREE_PAGE,
	VIRTIO_BALLOON_VQ_REPORTING,
	VIRTIO_BALLOON_VQ_MAX
पूर्ण;

क्रमागत virtio_balloon_config_पढ़ो अणु
	VIRTIO_BALLOON_CONFIG_READ_CMD_ID = 0,
पूर्ण;

काष्ठा virtio_balloon अणु
	काष्ठा virtio_device *vdev;
	काष्ठा virtqueue *inflate_vq, *deflate_vq, *stats_vq, *मुक्त_page_vq;

	/* Balloon's own wq क्रम cpu-पूर्णांकensive work items */
	काष्ठा workqueue_काष्ठा *balloon_wq;
	/* The मुक्त page reporting work item submitted to the balloon wq */
	काष्ठा work_काष्ठा report_मुक्त_page_work;

	/* The balloon servicing is delegated to a मुक्तzable workqueue. */
	काष्ठा work_काष्ठा update_balloon_stats_work;
	काष्ठा work_काष्ठा update_balloon_size_work;

	/* Prevent updating balloon when it is being canceled. */
	spinlock_t stop_update_lock;
	bool stop_update;
	/* Biपंचांगap to indicate अगर पढ़ोing the related config fields are needed */
	अचिन्हित दीर्घ config_पढ़ो_biपंचांगap;

	/* The list of allocated मुक्त pages, रुकोing to be given back to mm */
	काष्ठा list_head मुक्त_page_list;
	spinlock_t मुक्त_page_list_lock;
	/* The number of मुक्त page blocks on the above list */
	अचिन्हित दीर्घ num_मुक्त_page_blocks;
	/*
	 * The cmd id received from host.
	 * Read it via virtio_balloon_cmd_id_received to get the latest value
	 * sent from host.
	 */
	u32 cmd_id_received_cache;
	/* The cmd id that is actively in use */
	__virtio32 cmd_id_active;
	/* Buffer to store the stop sign */
	__virtio32 cmd_id_stop;

	/* Waiting क्रम host to ack the pages we released. */
	रुको_queue_head_t acked;

	/* Number of balloon pages we've told the Host we're not using. */
	अचिन्हित पूर्णांक num_pages;
	/*
	 * The pages we've told the Host we're not using are enqueued
	 * at vb_dev_info->pages list.
	 * Each page on this list adds VIRTIO_BALLOON_PAGES_PER_PAGE
	 * to num_pages above.
	 */
	काष्ठा balloon_dev_info vb_dev_info;

	/* Synchronize access/update to this काष्ठा virtio_balloon elements */
	काष्ठा mutex balloon_lock;

	/* The array of pfns we tell the Host about. */
	अचिन्हित पूर्णांक num_pfns;
	__virtio32 pfns[VIRTIO_BALLOON_ARRAY_PFNS_MAX];

	/* Memory statistics */
	काष्ठा virtio_balloon_stat stats[VIRTIO_BALLOON_S_NR];

	/* Shrinker to वापस मुक्त pages - VIRTIO_BALLOON_F_FREE_PAGE_HINT */
	काष्ठा shrinker shrinker;

	/* OOM notअगरier to deflate on OOM - VIRTIO_BALLOON_F_DEFLATE_ON_OOM */
	काष्ठा notअगरier_block oom_nb;

	/* Free page reporting device */
	काष्ठा virtqueue *reporting_vq;
	काष्ठा page_reporting_dev_info pr_dev_info;
पूर्ण;

अटल स्थिर काष्ठा virtio_device_id id_table[] = अणु
	अणु VIRTIO_ID_BALLOON, VIRTIO_DEV_ANY_ID पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल u32 page_to_balloon_pfn(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ pfn = page_to_pfn(page);

	BUILD_BUG_ON(PAGE_SHIFT < VIRTIO_BALLOON_PFN_SHIFT);
	/* Convert pfn from Linux page size to balloon page size. */
	वापस pfn * VIRTIO_BALLOON_PAGES_PER_PAGE;
पूर्ण

अटल व्योम balloon_ack(काष्ठा virtqueue *vq)
अणु
	काष्ठा virtio_balloon *vb = vq->vdev->priv;

	wake_up(&vb->acked);
पूर्ण

अटल व्योम tell_host(काष्ठा virtio_balloon *vb, काष्ठा virtqueue *vq)
अणु
	काष्ठा scatterlist sg;
	अचिन्हित पूर्णांक len;

	sg_init_one(&sg, vb->pfns, माप(vb->pfns[0]) * vb->num_pfns);

	/* We should always be able to add one buffer to an empty queue. */
	virtqueue_add_outbuf(vq, &sg, 1, vb, GFP_KERNEL);
	virtqueue_kick(vq);

	/* When host has पढ़ो buffer, this completes via balloon_ack */
	रुको_event(vb->acked, virtqueue_get_buf(vq, &len));

पूर्ण

अटल पूर्णांक virtballoon_मुक्त_page_report(काष्ठा page_reporting_dev_info *pr_dev_info,
				   काष्ठा scatterlist *sg, अचिन्हित पूर्णांक nents)
अणु
	काष्ठा virtio_balloon *vb =
		container_of(pr_dev_info, काष्ठा virtio_balloon, pr_dev_info);
	काष्ठा virtqueue *vq = vb->reporting_vq;
	अचिन्हित पूर्णांक unused, err;

	/* We should always be able to add these buffers to an empty queue. */
	err = virtqueue_add_inbuf(vq, sg, nents, vb, GFP_NOWAIT | __GFP_NOWARN);

	/*
	 * In the extremely unlikely हाल that something has occurred and we
	 * are able to trigger an error we will simply display a warning
	 * and निकास without actually processing the pages.
	 */
	अगर (WARN_ON_ONCE(err))
		वापस err;

	virtqueue_kick(vq);

	/* When host has पढ़ो buffer, this completes via balloon_ack */
	रुको_event(vb->acked, virtqueue_get_buf(vq, &unused));

	वापस 0;
पूर्ण

अटल व्योम set_page_pfns(काष्ठा virtio_balloon *vb,
			  __virtio32 pfns[], काष्ठा page *page)
अणु
	अचिन्हित पूर्णांक i;

	BUILD_BUG_ON(VIRTIO_BALLOON_PAGES_PER_PAGE > VIRTIO_BALLOON_ARRAY_PFNS_MAX);

	/*
	 * Set balloon pfns poपूर्णांकing at this page.
	 * Note that the first pfn poपूर्णांकs at start of the page.
	 */
	क्रम (i = 0; i < VIRTIO_BALLOON_PAGES_PER_PAGE; i++)
		pfns[i] = cpu_to_virtio32(vb->vdev,
					  page_to_balloon_pfn(page) + i);
पूर्ण

अटल अचिन्हित fill_balloon(काष्ठा virtio_balloon *vb, माप_प्रकार num)
अणु
	अचिन्हित num_allocated_pages;
	अचिन्हित num_pfns;
	काष्ठा page *page;
	LIST_HEAD(pages);

	/* We can only करो one array worth at a समय. */
	num = min(num, ARRAY_SIZE(vb->pfns));

	क्रम (num_pfns = 0; num_pfns < num;
	     num_pfns += VIRTIO_BALLOON_PAGES_PER_PAGE) अणु
		काष्ठा page *page = balloon_page_alloc();

		अगर (!page) अणु
			dev_info_ratelimited(&vb->vdev->dev,
					     "Out of puff! Can't get %u pages\n",
					     VIRTIO_BALLOON_PAGES_PER_PAGE);
			/* Sleep क्रम at least 1/5 of a second beक्रमe retry. */
			msleep(200);
			अवरोध;
		पूर्ण

		balloon_page_push(&pages, page);
	पूर्ण

	mutex_lock(&vb->balloon_lock);

	vb->num_pfns = 0;

	जबतक ((page = balloon_page_pop(&pages))) अणु
		balloon_page_enqueue(&vb->vb_dev_info, page);

		set_page_pfns(vb, vb->pfns + vb->num_pfns, page);
		vb->num_pages += VIRTIO_BALLOON_PAGES_PER_PAGE;
		अगर (!virtio_has_feature(vb->vdev,
					VIRTIO_BALLOON_F_DEFLATE_ON_OOM))
			adjust_managed_page_count(page, -1);
		vb->num_pfns += VIRTIO_BALLOON_PAGES_PER_PAGE;
	पूर्ण

	num_allocated_pages = vb->num_pfns;
	/* Did we get any? */
	अगर (vb->num_pfns != 0)
		tell_host(vb, vb->inflate_vq);
	mutex_unlock(&vb->balloon_lock);

	वापस num_allocated_pages;
पूर्ण

अटल व्योम release_pages_balloon(काष्ठा virtio_balloon *vb,
				 काष्ठा list_head *pages)
अणु
	काष्ठा page *page, *next;

	list_क्रम_each_entry_safe(page, next, pages, lru) अणु
		अगर (!virtio_has_feature(vb->vdev,
					VIRTIO_BALLOON_F_DEFLATE_ON_OOM))
			adjust_managed_page_count(page, 1);
		list_del(&page->lru);
		put_page(page); /* balloon reference */
	पूर्ण
पूर्ण

अटल अचिन्हित leak_balloon(काष्ठा virtio_balloon *vb, माप_प्रकार num)
अणु
	अचिन्हित num_मुक्तd_pages;
	काष्ठा page *page;
	काष्ठा balloon_dev_info *vb_dev_info = &vb->vb_dev_info;
	LIST_HEAD(pages);

	/* We can only करो one array worth at a समय. */
	num = min(num, ARRAY_SIZE(vb->pfns));

	mutex_lock(&vb->balloon_lock);
	/* We can't release more pages than taken */
	num = min(num, (माप_प्रकार)vb->num_pages);
	क्रम (vb->num_pfns = 0; vb->num_pfns < num;
	     vb->num_pfns += VIRTIO_BALLOON_PAGES_PER_PAGE) अणु
		page = balloon_page_dequeue(vb_dev_info);
		अगर (!page)
			अवरोध;
		set_page_pfns(vb, vb->pfns + vb->num_pfns, page);
		list_add(&page->lru, &pages);
		vb->num_pages -= VIRTIO_BALLOON_PAGES_PER_PAGE;
	पूर्ण

	num_मुक्तd_pages = vb->num_pfns;
	/*
	 * Note that अगर
	 * virtio_has_feature(vdev, VIRTIO_BALLOON_F_MUST_TELL_HOST);
	 * is true, we *have* to करो it in this order
	 */
	अगर (vb->num_pfns != 0)
		tell_host(vb, vb->deflate_vq);
	release_pages_balloon(vb, &pages);
	mutex_unlock(&vb->balloon_lock);
	वापस num_मुक्तd_pages;
पूर्ण

अटल अंतरभूत व्योम update_stat(काष्ठा virtio_balloon *vb, पूर्णांक idx,
			       u16 tag, u64 val)
अणु
	BUG_ON(idx >= VIRTIO_BALLOON_S_NR);
	vb->stats[idx].tag = cpu_to_virtio16(vb->vdev, tag);
	vb->stats[idx].val = cpu_to_virtio64(vb->vdev, val);
पूर्ण

#घोषणा pages_to_bytes(x) ((u64)(x) << PAGE_SHIFT)

अटल अचिन्हित पूर्णांक update_balloon_stats(काष्ठा virtio_balloon *vb)
अणु
	अचिन्हित दीर्घ events[NR_VM_EVENT_ITEMS];
	काष्ठा sysinfo i;
	अचिन्हित पूर्णांक idx = 0;
	दीर्घ available;
	अचिन्हित दीर्घ caches;

	all_vm_events(events);
	si_meminfo(&i);

	available = si_mem_available();
	caches = global_node_page_state(NR_खाता_PAGES);

#अगर_घोषित CONFIG_VM_EVENT_COUNTERS
	update_stat(vb, idx++, VIRTIO_BALLOON_S_SWAP_IN,
				pages_to_bytes(events[PSWPIN]));
	update_stat(vb, idx++, VIRTIO_BALLOON_S_SWAP_OUT,
				pages_to_bytes(events[PSWPOUT]));
	update_stat(vb, idx++, VIRTIO_BALLOON_S_MAJFLT, events[PGMAJFAULT]);
	update_stat(vb, idx++, VIRTIO_BALLOON_S_MINFLT, events[PGFAULT]);
#अगर_घोषित CONFIG_HUGETLB_PAGE
	update_stat(vb, idx++, VIRTIO_BALLOON_S_HTLB_PGALLOC,
		    events[HTLB_BUDDY_PGALLOC]);
	update_stat(vb, idx++, VIRTIO_BALLOON_S_HTLB_PGFAIL,
		    events[HTLB_BUDDY_PGALLOC_FAIL]);
#पूर्ण_अगर
#पूर्ण_अगर
	update_stat(vb, idx++, VIRTIO_BALLOON_S_MEMFREE,
				pages_to_bytes(i.मुक्तram));
	update_stat(vb, idx++, VIRTIO_BALLOON_S_MEMTOT,
				pages_to_bytes(i.totalram));
	update_stat(vb, idx++, VIRTIO_BALLOON_S_AVAIL,
				pages_to_bytes(available));
	update_stat(vb, idx++, VIRTIO_BALLOON_S_CACHES,
				pages_to_bytes(caches));

	वापस idx;
पूर्ण

/*
 * While most virtqueues communicate guest-initiated requests to the hypervisor,
 * the stats queue operates in reverse.  The driver initializes the virtqueue
 * with a single buffer.  From that poपूर्णांक क्रमward, all conversations consist of
 * a hypervisor request (a call to this function) which directs us to refill
 * the virtqueue with a fresh stats buffer.  Since stats collection can sleep,
 * we delegate the job to a मुक्तzable workqueue that will करो the actual work via
 * stats_handle_request().
 */
अटल व्योम stats_request(काष्ठा virtqueue *vq)
अणु
	काष्ठा virtio_balloon *vb = vq->vdev->priv;

	spin_lock(&vb->stop_update_lock);
	अगर (!vb->stop_update)
		queue_work(प्रणाली_मुक्तzable_wq, &vb->update_balloon_stats_work);
	spin_unlock(&vb->stop_update_lock);
पूर्ण

अटल व्योम stats_handle_request(काष्ठा virtio_balloon *vb)
अणु
	काष्ठा virtqueue *vq;
	काष्ठा scatterlist sg;
	अचिन्हित पूर्णांक len, num_stats;

	num_stats = update_balloon_stats(vb);

	vq = vb->stats_vq;
	अगर (!virtqueue_get_buf(vq, &len))
		वापस;
	sg_init_one(&sg, vb->stats, माप(vb->stats[0]) * num_stats);
	virtqueue_add_outbuf(vq, &sg, 1, vb, GFP_KERNEL);
	virtqueue_kick(vq);
पूर्ण

अटल अंतरभूत s64 towards_target(काष्ठा virtio_balloon *vb)
अणु
	s64 target;
	u32 num_pages;

	/* Legacy balloon config space is LE, unlike all other devices. */
	virtio_cपढ़ो_le(vb->vdev, काष्ठा virtio_balloon_config, num_pages,
			&num_pages);

	target = num_pages;
	वापस target - vb->num_pages;
पूर्ण

/* Gives back @num_to_वापस blocks of मुक्त pages to mm. */
अटल अचिन्हित दीर्घ वापस_मुक्त_pages_to_mm(काष्ठा virtio_balloon *vb,
					     अचिन्हित दीर्घ num_to_वापस)
अणु
	काष्ठा page *page;
	अचिन्हित दीर्घ num_वापसed;

	spin_lock_irq(&vb->मुक्त_page_list_lock);
	क्रम (num_वापसed = 0; num_वापसed < num_to_वापस; num_वापसed++) अणु
		page = balloon_page_pop(&vb->मुक्त_page_list);
		अगर (!page)
			अवरोध;
		मुक्त_pages((अचिन्हित दीर्घ)page_address(page),
			   VIRTIO_BALLOON_HINT_BLOCK_ORDER);
	पूर्ण
	vb->num_मुक्त_page_blocks -= num_वापसed;
	spin_unlock_irq(&vb->मुक्त_page_list_lock);

	वापस num_वापसed;
पूर्ण

अटल व्योम virtio_balloon_queue_मुक्त_page_work(काष्ठा virtio_balloon *vb)
अणु
	अगर (!virtio_has_feature(vb->vdev, VIRTIO_BALLOON_F_FREE_PAGE_HINT))
		वापस;

	/* No need to queue the work अगर the bit was alपढ़ोy set. */
	अगर (test_and_set_bit(VIRTIO_BALLOON_CONFIG_READ_CMD_ID,
			     &vb->config_पढ़ो_biपंचांगap))
		वापस;

	queue_work(vb->balloon_wq, &vb->report_मुक्त_page_work);
पूर्ण

अटल व्योम virtballoon_changed(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_balloon *vb = vdev->priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vb->stop_update_lock, flags);
	अगर (!vb->stop_update) अणु
		queue_work(प्रणाली_मुक्तzable_wq,
			   &vb->update_balloon_size_work);
		virtio_balloon_queue_मुक्त_page_work(vb);
	पूर्ण
	spin_unlock_irqrestore(&vb->stop_update_lock, flags);
पूर्ण

अटल व्योम update_balloon_size(काष्ठा virtio_balloon *vb)
अणु
	u32 actual = vb->num_pages;

	/* Legacy balloon config space is LE, unlike all other devices. */
	virtio_cग_लिखो_le(vb->vdev, काष्ठा virtio_balloon_config, actual,
			 &actual);
पूर्ण

अटल व्योम update_balloon_stats_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virtio_balloon *vb;

	vb = container_of(work, काष्ठा virtio_balloon,
			  update_balloon_stats_work);
	stats_handle_request(vb);
पूर्ण

अटल व्योम update_balloon_size_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virtio_balloon *vb;
	s64 dअगरf;

	vb = container_of(work, काष्ठा virtio_balloon,
			  update_balloon_size_work);
	dअगरf = towards_target(vb);

	अगर (!dअगरf)
		वापस;

	अगर (dअगरf > 0)
		dअगरf -= fill_balloon(vb, dअगरf);
	अन्यथा
		dअगरf += leak_balloon(vb, -dअगरf);
	update_balloon_size(vb);

	अगर (dअगरf)
		queue_work(प्रणाली_मुक्तzable_wq, work);
पूर्ण

अटल पूर्णांक init_vqs(काष्ठा virtio_balloon *vb)
अणु
	काष्ठा virtqueue *vqs[VIRTIO_BALLOON_VQ_MAX];
	vq_callback_t *callbacks[VIRTIO_BALLOON_VQ_MAX];
	स्थिर अक्षर *names[VIRTIO_BALLOON_VQ_MAX];
	पूर्णांक err;

	/*
	 * Inflateq and deflateq are used unconditionally. The names[]
	 * will be शून्य अगर the related feature is not enabled, which will
	 * cause no allocation क्रम the corresponding virtqueue in find_vqs.
	 */
	callbacks[VIRTIO_BALLOON_VQ_INFLATE] = balloon_ack;
	names[VIRTIO_BALLOON_VQ_INFLATE] = "inflate";
	callbacks[VIRTIO_BALLOON_VQ_DEFLATE] = balloon_ack;
	names[VIRTIO_BALLOON_VQ_DEFLATE] = "deflate";
	callbacks[VIRTIO_BALLOON_VQ_STATS] = शून्य;
	names[VIRTIO_BALLOON_VQ_STATS] = शून्य;
	callbacks[VIRTIO_BALLOON_VQ_FREE_PAGE] = शून्य;
	names[VIRTIO_BALLOON_VQ_FREE_PAGE] = शून्य;
	names[VIRTIO_BALLOON_VQ_REPORTING] = शून्य;

	अगर (virtio_has_feature(vb->vdev, VIRTIO_BALLOON_F_STATS_VQ)) अणु
		names[VIRTIO_BALLOON_VQ_STATS] = "stats";
		callbacks[VIRTIO_BALLOON_VQ_STATS] = stats_request;
	पूर्ण

	अगर (virtio_has_feature(vb->vdev, VIRTIO_BALLOON_F_FREE_PAGE_HINT)) अणु
		names[VIRTIO_BALLOON_VQ_FREE_PAGE] = "free_page_vq";
		callbacks[VIRTIO_BALLOON_VQ_FREE_PAGE] = शून्य;
	पूर्ण

	अगर (virtio_has_feature(vb->vdev, VIRTIO_BALLOON_F_REPORTING)) अणु
		names[VIRTIO_BALLOON_VQ_REPORTING] = "reporting_vq";
		callbacks[VIRTIO_BALLOON_VQ_REPORTING] = balloon_ack;
	पूर्ण

	err = vb->vdev->config->find_vqs(vb->vdev, VIRTIO_BALLOON_VQ_MAX,
					 vqs, callbacks, names, शून्य, शून्य);
	अगर (err)
		वापस err;

	vb->inflate_vq = vqs[VIRTIO_BALLOON_VQ_INFLATE];
	vb->deflate_vq = vqs[VIRTIO_BALLOON_VQ_DEFLATE];
	अगर (virtio_has_feature(vb->vdev, VIRTIO_BALLOON_F_STATS_VQ)) अणु
		काष्ठा scatterlist sg;
		अचिन्हित पूर्णांक num_stats;
		vb->stats_vq = vqs[VIRTIO_BALLOON_VQ_STATS];

		/*
		 * Prime this virtqueue with one buffer so the hypervisor can
		 * use it to संकेत us later (it can't be broken yet!).
		 */
		num_stats = update_balloon_stats(vb);

		sg_init_one(&sg, vb->stats, माप(vb->stats[0]) * num_stats);
		err = virtqueue_add_outbuf(vb->stats_vq, &sg, 1, vb,
					   GFP_KERNEL);
		अगर (err) अणु
			dev_warn(&vb->vdev->dev, "%s: add stat_vq failed\n",
				 __func__);
			वापस err;
		पूर्ण
		virtqueue_kick(vb->stats_vq);
	पूर्ण

	अगर (virtio_has_feature(vb->vdev, VIRTIO_BALLOON_F_FREE_PAGE_HINT))
		vb->मुक्त_page_vq = vqs[VIRTIO_BALLOON_VQ_FREE_PAGE];

	अगर (virtio_has_feature(vb->vdev, VIRTIO_BALLOON_F_REPORTING))
		vb->reporting_vq = vqs[VIRTIO_BALLOON_VQ_REPORTING];

	वापस 0;
पूर्ण

अटल u32 virtio_balloon_cmd_id_received(काष्ठा virtio_balloon *vb)
अणु
	अगर (test_and_clear_bit(VIRTIO_BALLOON_CONFIG_READ_CMD_ID,
			       &vb->config_पढ़ो_biपंचांगap)) अणु
		/* Legacy balloon config space is LE, unlike all other devices. */
		virtio_cपढ़ो_le(vb->vdev, काष्ठा virtio_balloon_config,
				मुक्त_page_hपूर्णांक_cmd_id,
				&vb->cmd_id_received_cache);
	पूर्ण

	वापस vb->cmd_id_received_cache;
पूर्ण

अटल पूर्णांक send_cmd_id_start(काष्ठा virtio_balloon *vb)
अणु
	काष्ठा scatterlist sg;
	काष्ठा virtqueue *vq = vb->मुक्त_page_vq;
	पूर्णांक err, unused;

	/* Detach all the used buffers from the vq */
	जबतक (virtqueue_get_buf(vq, &unused))
		;

	vb->cmd_id_active = cpu_to_virtio32(vb->vdev,
					virtio_balloon_cmd_id_received(vb));
	sg_init_one(&sg, &vb->cmd_id_active, माप(vb->cmd_id_active));
	err = virtqueue_add_outbuf(vq, &sg, 1, &vb->cmd_id_active, GFP_KERNEL);
	अगर (!err)
		virtqueue_kick(vq);
	वापस err;
पूर्ण

अटल पूर्णांक send_cmd_id_stop(काष्ठा virtio_balloon *vb)
अणु
	काष्ठा scatterlist sg;
	काष्ठा virtqueue *vq = vb->मुक्त_page_vq;
	पूर्णांक err, unused;

	/* Detach all the used buffers from the vq */
	जबतक (virtqueue_get_buf(vq, &unused))
		;

	sg_init_one(&sg, &vb->cmd_id_stop, माप(vb->cmd_id_stop));
	err = virtqueue_add_outbuf(vq, &sg, 1, &vb->cmd_id_stop, GFP_KERNEL);
	अगर (!err)
		virtqueue_kick(vq);
	वापस err;
पूर्ण

अटल पूर्णांक get_मुक्त_page_and_send(काष्ठा virtio_balloon *vb)
अणु
	काष्ठा virtqueue *vq = vb->मुक्त_page_vq;
	काष्ठा page *page;
	काष्ठा scatterlist sg;
	पूर्णांक err, unused;
	व्योम *p;

	/* Detach all the used buffers from the vq */
	जबतक (virtqueue_get_buf(vq, &unused))
		;

	page = alloc_pages(VIRTIO_BALLOON_FREE_PAGE_ALLOC_FLAG,
			   VIRTIO_BALLOON_HINT_BLOCK_ORDER);
	/*
	 * When the allocation वापसs शून्य, it indicates that we have got all
	 * the possible मुक्त pages, so वापस -EINTR to stop.
	 */
	अगर (!page)
		वापस -EINTR;

	p = page_address(page);
	sg_init_one(&sg, p, VIRTIO_BALLOON_HINT_BLOCK_BYTES);
	/* There is always 1 entry reserved क्रम the cmd id to use. */
	अगर (vq->num_मुक्त > 1) अणु
		err = virtqueue_add_inbuf(vq, &sg, 1, p, GFP_KERNEL);
		अगर (unlikely(err)) अणु
			मुक्त_pages((अचिन्हित दीर्घ)p,
				   VIRTIO_BALLOON_HINT_BLOCK_ORDER);
			वापस err;
		पूर्ण
		virtqueue_kick(vq);
		spin_lock_irq(&vb->मुक्त_page_list_lock);
		balloon_page_push(&vb->मुक्त_page_list, page);
		vb->num_मुक्त_page_blocks++;
		spin_unlock_irq(&vb->मुक्त_page_list_lock);
	पूर्ण अन्यथा अणु
		/*
		 * The vq has no available entry to add this page block, so
		 * just मुक्त it.
		 */
		मुक्त_pages((अचिन्हित दीर्घ)p, VIRTIO_BALLOON_HINT_BLOCK_ORDER);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक send_मुक्त_pages(काष्ठा virtio_balloon *vb)
अणु
	पूर्णांक err;
	u32 cmd_id_active;

	जबतक (1) अणु
		/*
		 * If a stop id or a new cmd id was just received from host,
		 * stop the reporting.
		 */
		cmd_id_active = virtio32_to_cpu(vb->vdev, vb->cmd_id_active);
		अगर (unlikely(cmd_id_active !=
			     virtio_balloon_cmd_id_received(vb)))
			अवरोध;

		/*
		 * The मुक्त page blocks are allocated and sent to host one by
		 * one.
		 */
		err = get_मुक्त_page_and_send(vb);
		अगर (err == -EINTR)
			अवरोध;
		अन्यथा अगर (unlikely(err))
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम virtio_balloon_report_मुक्त_page(काष्ठा virtio_balloon *vb)
अणु
	पूर्णांक err;
	काष्ठा device *dev = &vb->vdev->dev;

	/* Start by sending the received cmd id to host with an outbuf. */
	err = send_cmd_id_start(vb);
	अगर (unlikely(err))
		dev_err(dev, "Failed to send a start id, err = %d\n", err);

	err = send_मुक्त_pages(vb);
	अगर (unlikely(err))
		dev_err(dev, "Failed to send a free page, err = %d\n", err);

	/* End by sending a stop id to host with an outbuf. */
	err = send_cmd_id_stop(vb);
	अगर (unlikely(err))
		dev_err(dev, "Failed to send a stop id, err = %d\n", err);
पूर्ण

अटल व्योम report_मुक्त_page_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virtio_balloon *vb = container_of(work, काष्ठा virtio_balloon,
						 report_मुक्त_page_work);
	u32 cmd_id_received;

	cmd_id_received = virtio_balloon_cmd_id_received(vb);
	अगर (cmd_id_received == VIRTIO_BALLOON_CMD_ID_DONE) अणु
		/* Pass अच_दीर्घ_उच्च to give back all the मुक्त pages */
		वापस_मुक्त_pages_to_mm(vb, अच_दीर्घ_उच्च);
	पूर्ण अन्यथा अगर (cmd_id_received != VIRTIO_BALLOON_CMD_ID_STOP &&
		   cmd_id_received !=
		   virtio32_to_cpu(vb->vdev, vb->cmd_id_active)) अणु
		virtio_balloon_report_मुक्त_page(vb);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_BALLOON_COMPACTION
/*
 * virtballoon_migratepage - perक्रमm the balloon page migration on behalf of
 *			     a compaction thपढ़ो.     (called under page lock)
 * @vb_dev_info: the balloon device
 * @newpage: page that will replace the isolated page after migration finishes.
 * @page   : the isolated (old) page that is about to be migrated to newpage.
 * @mode   : compaction mode -- not used क्रम balloon page migration.
 *
 * After a ballooned page माला_लो isolated by compaction procedures, this is the
 * function that perक्रमms the page migration on behalf of a compaction thपढ़ो
 * The page migration क्रम virtio balloon is करोne in a simple swap fashion which
 * follows these two macro steps:
 *  1) insert newpage पूर्णांकo vb->pages list and update the host about it;
 *  2) update the host about the old page हटाओd from vb->pages list;
 *
 * This function preक्रमms the balloon page migration task.
 * Called through balloon_mapping->a_ops->migratepage
 */
अटल पूर्णांक virtballoon_migratepage(काष्ठा balloon_dev_info *vb_dev_info,
		काष्ठा page *newpage, काष्ठा page *page, क्रमागत migrate_mode mode)
अणु
	काष्ठा virtio_balloon *vb = container_of(vb_dev_info,
			काष्ठा virtio_balloon, vb_dev_info);
	अचिन्हित दीर्घ flags;

	/*
	 * In order to aव्योम lock contention जबतक migrating pages concurrently
	 * to leak_balloon() or fill_balloon() we just give up the balloon_lock
	 * this turn, as it is easier to retry the page migration later.
	 * This also prevents fill_balloon() getting stuck पूर्णांकo a mutex
	 * recursion in the हाल it ends up triggering memory compaction
	 * जबतक it is attempting to inflate the ballon.
	 */
	अगर (!mutex_trylock(&vb->balloon_lock))
		वापस -EAGAIN;

	get_page(newpage); /* balloon reference */

	/*
	  * When we migrate a page to a dअगरferent zone and adjusted the
	  * managed page count when inflating, we have to fixup the count of
	  * both involved zones.
	  */
	अगर (!virtio_has_feature(vb->vdev, VIRTIO_BALLOON_F_DEFLATE_ON_OOM) &&
	    page_zone(page) != page_zone(newpage)) अणु
		adjust_managed_page_count(page, 1);
		adjust_managed_page_count(newpage, -1);
	पूर्ण

	/* balloon's page migration 1st step  -- inflate "newpage" */
	spin_lock_irqsave(&vb_dev_info->pages_lock, flags);
	balloon_page_insert(vb_dev_info, newpage);
	vb_dev_info->isolated_pages--;
	__count_vm_event(BALLOON_MIGRATE);
	spin_unlock_irqrestore(&vb_dev_info->pages_lock, flags);
	vb->num_pfns = VIRTIO_BALLOON_PAGES_PER_PAGE;
	set_page_pfns(vb, vb->pfns, newpage);
	tell_host(vb, vb->inflate_vq);

	/* balloon's page migration 2nd step -- deflate "page" */
	spin_lock_irqsave(&vb_dev_info->pages_lock, flags);
	balloon_page_delete(page);
	spin_unlock_irqrestore(&vb_dev_info->pages_lock, flags);
	vb->num_pfns = VIRTIO_BALLOON_PAGES_PER_PAGE;
	set_page_pfns(vb, vb->pfns, page);
	tell_host(vb, vb->deflate_vq);

	mutex_unlock(&vb->balloon_lock);

	put_page(page); /* balloon reference */

	वापस MIGRATEPAGE_SUCCESS;
पूर्ण

अटल पूर्णांक balloon_init_fs_context(काष्ठा fs_context *fc)
अणु
	वापस init_pseuकरो(fc, BALLOON_KVM_MAGIC) ? 0 : -ENOMEM;
पूर्ण

अटल काष्ठा file_प्रणाली_type balloon_fs = अणु
	.name           = "balloon-kvm",
	.init_fs_context = balloon_init_fs_context,
	.समाप्त_sb        = समाप्त_anon_super,
पूर्ण;

#पूर्ण_अगर /* CONFIG_BALLOON_COMPACTION */

अटल अचिन्हित दीर्घ shrink_मुक्त_pages(काष्ठा virtio_balloon *vb,
				       अचिन्हित दीर्घ pages_to_मुक्त)
अणु
	अचिन्हित दीर्घ blocks_to_मुक्त, blocks_मुक्तd;

	pages_to_मुक्त = round_up(pages_to_मुक्त,
				 VIRTIO_BALLOON_HINT_BLOCK_PAGES);
	blocks_to_मुक्त = pages_to_मुक्त / VIRTIO_BALLOON_HINT_BLOCK_PAGES;
	blocks_मुक्तd = वापस_मुक्त_pages_to_mm(vb, blocks_to_मुक्त);

	वापस blocks_मुक्तd * VIRTIO_BALLOON_HINT_BLOCK_PAGES;
पूर्ण

अटल अचिन्हित दीर्घ virtio_balloon_shrinker_scan(काष्ठा shrinker *shrinker,
						  काष्ठा shrink_control *sc)
अणु
	काष्ठा virtio_balloon *vb = container_of(shrinker,
					काष्ठा virtio_balloon, shrinker);

	वापस shrink_मुक्त_pages(vb, sc->nr_to_scan);
पूर्ण

अटल अचिन्हित दीर्घ virtio_balloon_shrinker_count(काष्ठा shrinker *shrinker,
						   काष्ठा shrink_control *sc)
अणु
	काष्ठा virtio_balloon *vb = container_of(shrinker,
					काष्ठा virtio_balloon, shrinker);

	वापस vb->num_मुक्त_page_blocks * VIRTIO_BALLOON_HINT_BLOCK_PAGES;
पूर्ण

अटल पूर्णांक virtio_balloon_oom_notअगरy(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ dummy, व्योम *parm)
अणु
	काष्ठा virtio_balloon *vb = container_of(nb,
						 काष्ठा virtio_balloon, oom_nb);
	अचिन्हित दीर्घ *मुक्तd = parm;

	*मुक्तd += leak_balloon(vb, VIRTIO_BALLOON_OOM_NR_PAGES) /
		  VIRTIO_BALLOON_PAGES_PER_PAGE;
	update_balloon_size(vb);

	वापस NOTIFY_OK;
पूर्ण

अटल व्योम virtio_balloon_unरेजिस्टर_shrinker(काष्ठा virtio_balloon *vb)
अणु
	unरेजिस्टर_shrinker(&vb->shrinker);
पूर्ण

अटल पूर्णांक virtio_balloon_रेजिस्टर_shrinker(काष्ठा virtio_balloon *vb)
अणु
	vb->shrinker.scan_objects = virtio_balloon_shrinker_scan;
	vb->shrinker.count_objects = virtio_balloon_shrinker_count;
	vb->shrinker.seeks = DEFAULT_SEEKS;

	वापस रेजिस्टर_shrinker(&vb->shrinker);
पूर्ण

अटल पूर्णांक virtballoon_probe(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_balloon *vb;
	पूर्णांक err;

	अगर (!vdev->config->get) अणु
		dev_err(&vdev->dev, "%s failure: config access disabled\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	vdev->priv = vb = kzalloc(माप(*vb), GFP_KERNEL);
	अगर (!vb) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	INIT_WORK(&vb->update_balloon_stats_work, update_balloon_stats_func);
	INIT_WORK(&vb->update_balloon_size_work, update_balloon_size_func);
	spin_lock_init(&vb->stop_update_lock);
	mutex_init(&vb->balloon_lock);
	init_रुकोqueue_head(&vb->acked);
	vb->vdev = vdev;

	balloon_devinfo_init(&vb->vb_dev_info);

	err = init_vqs(vb);
	अगर (err)
		जाओ out_मुक्त_vb;

#अगर_घोषित CONFIG_BALLOON_COMPACTION
	balloon_mnt = kern_mount(&balloon_fs);
	अगर (IS_ERR(balloon_mnt)) अणु
		err = PTR_ERR(balloon_mnt);
		जाओ out_del_vqs;
	पूर्ण

	vb->vb_dev_info.migratepage = virtballoon_migratepage;
	vb->vb_dev_info.inode = alloc_anon_inode(balloon_mnt->mnt_sb);
	अगर (IS_ERR(vb->vb_dev_info.inode)) अणु
		err = PTR_ERR(vb->vb_dev_info.inode);
		जाओ out_kern_unmount;
	पूर्ण
	vb->vb_dev_info.inode->i_mapping->a_ops = &balloon_aops;
#पूर्ण_अगर
	अगर (virtio_has_feature(vdev, VIRTIO_BALLOON_F_FREE_PAGE_HINT)) अणु
		/*
		 * There is always one entry reserved क्रम cmd id, so the ring
		 * size needs to be at least two to report मुक्त page hपूर्णांकs.
		 */
		अगर (virtqueue_get_vring_size(vb->मुक्त_page_vq) < 2) अणु
			err = -ENOSPC;
			जाओ out_iput;
		पूर्ण
		vb->balloon_wq = alloc_workqueue("balloon-wq",
					WQ_FREEZABLE | WQ_CPU_INTENSIVE, 0);
		अगर (!vb->balloon_wq) अणु
			err = -ENOMEM;
			जाओ out_iput;
		पूर्ण
		INIT_WORK(&vb->report_मुक्त_page_work, report_मुक्त_page_func);
		vb->cmd_id_received_cache = VIRTIO_BALLOON_CMD_ID_STOP;
		vb->cmd_id_active = cpu_to_virtio32(vb->vdev,
						  VIRTIO_BALLOON_CMD_ID_STOP);
		vb->cmd_id_stop = cpu_to_virtio32(vb->vdev,
						  VIRTIO_BALLOON_CMD_ID_STOP);
		spin_lock_init(&vb->मुक्त_page_list_lock);
		INIT_LIST_HEAD(&vb->मुक्त_page_list);
		/*
		 * We're allowed to reuse any मुक्त pages, even अगर they are
		 * still to be processed by the host.
		 */
		err = virtio_balloon_रेजिस्टर_shrinker(vb);
		अगर (err)
			जाओ out_del_balloon_wq;
	पूर्ण

	अगर (virtio_has_feature(vb->vdev, VIRTIO_BALLOON_F_DEFLATE_ON_OOM)) अणु
		vb->oom_nb.notअगरier_call = virtio_balloon_oom_notअगरy;
		vb->oom_nb.priority = VIRTIO_BALLOON_OOM_NOTIFY_PRIORITY;
		err = रेजिस्टर_oom_notअगरier(&vb->oom_nb);
		अगर (err < 0)
			जाओ out_unरेजिस्टर_shrinker;
	पूर्ण

	अगर (virtio_has_feature(vdev, VIRTIO_BALLOON_F_PAGE_POISON)) अणु
		/* Start with poison val of 0 representing general init */
		__u32 poison_val = 0;

		/*
		 * Let the hypervisor know that we are expecting a
		 * specअगरic value to be written back in balloon pages.
		 *
		 * If the PAGE_POISON value was larger than a byte we would
		 * need to byte swap poison_val here to guarantee it is
		 * little-endian. However क्रम now it is a single byte so we
		 * can pass it as-is.
		 */
		अगर (!want_init_on_मुक्त())
			स_रखो(&poison_val, PAGE_POISON, माप(poison_val));

		virtio_cग_लिखो_le(vb->vdev, काष्ठा virtio_balloon_config,
				 poison_val, &poison_val);
	पूर्ण

	vb->pr_dev_info.report = virtballoon_मुक्त_page_report;
	अगर (virtio_has_feature(vb->vdev, VIRTIO_BALLOON_F_REPORTING)) अणु
		अचिन्हित पूर्णांक capacity;

		capacity = virtqueue_get_vring_size(vb->reporting_vq);
		अगर (capacity < PAGE_REPORTING_CAPACITY) अणु
			err = -ENOSPC;
			जाओ out_unरेजिस्टर_oom;
		पूर्ण

		err = page_reporting_रेजिस्टर(&vb->pr_dev_info);
		अगर (err)
			जाओ out_unरेजिस्टर_oom;
	पूर्ण

	virtio_device_पढ़ोy(vdev);

	अगर (towards_target(vb))
		virtballoon_changed(vdev);
	वापस 0;

out_unरेजिस्टर_oom:
	अगर (virtio_has_feature(vb->vdev, VIRTIO_BALLOON_F_DEFLATE_ON_OOM))
		unरेजिस्टर_oom_notअगरier(&vb->oom_nb);
out_unरेजिस्टर_shrinker:
	अगर (virtio_has_feature(vb->vdev, VIRTIO_BALLOON_F_FREE_PAGE_HINT))
		virtio_balloon_unरेजिस्टर_shrinker(vb);
out_del_balloon_wq:
	अगर (virtio_has_feature(vdev, VIRTIO_BALLOON_F_FREE_PAGE_HINT))
		destroy_workqueue(vb->balloon_wq);
out_iput:
#अगर_घोषित CONFIG_BALLOON_COMPACTION
	iput(vb->vb_dev_info.inode);
out_kern_unmount:
	kern_unmount(balloon_mnt);
out_del_vqs:
#पूर्ण_अगर
	vdev->config->del_vqs(vdev);
out_मुक्त_vb:
	kमुक्त(vb);
out:
	वापस err;
पूर्ण

अटल व्योम हटाओ_common(काष्ठा virtio_balloon *vb)
अणु
	/* There might be pages left in the balloon: मुक्त them. */
	जबतक (vb->num_pages)
		leak_balloon(vb, vb->num_pages);
	update_balloon_size(vb);

	/* There might be मुक्त pages that are being reported: release them. */
	अगर (virtio_has_feature(vb->vdev, VIRTIO_BALLOON_F_FREE_PAGE_HINT))
		वापस_मुक्त_pages_to_mm(vb, अच_दीर्घ_उच्च);

	/* Now we reset the device so we can clean up the queues. */
	vb->vdev->config->reset(vb->vdev);

	vb->vdev->config->del_vqs(vb->vdev);
पूर्ण

अटल व्योम virtballoon_हटाओ(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_balloon *vb = vdev->priv;

	अगर (virtio_has_feature(vb->vdev, VIRTIO_BALLOON_F_REPORTING))
		page_reporting_unरेजिस्टर(&vb->pr_dev_info);
	अगर (virtio_has_feature(vb->vdev, VIRTIO_BALLOON_F_DEFLATE_ON_OOM))
		unरेजिस्टर_oom_notअगरier(&vb->oom_nb);
	अगर (virtio_has_feature(vb->vdev, VIRTIO_BALLOON_F_FREE_PAGE_HINT))
		virtio_balloon_unरेजिस्टर_shrinker(vb);
	spin_lock_irq(&vb->stop_update_lock);
	vb->stop_update = true;
	spin_unlock_irq(&vb->stop_update_lock);
	cancel_work_sync(&vb->update_balloon_size_work);
	cancel_work_sync(&vb->update_balloon_stats_work);

	अगर (virtio_has_feature(vdev, VIRTIO_BALLOON_F_FREE_PAGE_HINT)) अणु
		cancel_work_sync(&vb->report_मुक्त_page_work);
		destroy_workqueue(vb->balloon_wq);
	पूर्ण

	हटाओ_common(vb);
#अगर_घोषित CONFIG_BALLOON_COMPACTION
	अगर (vb->vb_dev_info.inode)
		iput(vb->vb_dev_info.inode);

	kern_unmount(balloon_mnt);
#पूर्ण_अगर
	kमुक्त(vb);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक virtballoon_मुक्तze(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_balloon *vb = vdev->priv;

	/*
	 * The workqueue is alपढ़ोy frozen by the PM core beक्रमe this
	 * function is called.
	 */
	हटाओ_common(vb);
	वापस 0;
पूर्ण

अटल पूर्णांक virtballoon_restore(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_balloon *vb = vdev->priv;
	पूर्णांक ret;

	ret = init_vqs(vdev->priv);
	अगर (ret)
		वापस ret;

	virtio_device_पढ़ोy(vdev);

	अगर (towards_target(vb))
		virtballoon_changed(vdev);
	update_balloon_size(vb);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक virtballoon_validate(काष्ठा virtio_device *vdev)
अणु
	/*
	 * Inक्रमm the hypervisor that our pages are poisoned or
	 * initialized. If we cannot करो that then we should disable
	 * page reporting as it could potentially change the contents
	 * of our मुक्त pages.
	 */
	अगर (!want_init_on_मुक्त() && !page_poisoning_enabled_अटल())
		__virtio_clear_bit(vdev, VIRTIO_BALLOON_F_PAGE_POISON);
	अन्यथा अगर (!virtio_has_feature(vdev, VIRTIO_BALLOON_F_PAGE_POISON))
		__virtio_clear_bit(vdev, VIRTIO_BALLOON_F_REPORTING);

	__virtio_clear_bit(vdev, VIRTIO_F_ACCESS_PLATFORM);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक features[] = अणु
	VIRTIO_BALLOON_F_MUST_TELL_HOST,
	VIRTIO_BALLOON_F_STATS_VQ,
	VIRTIO_BALLOON_F_DEFLATE_ON_OOM,
	VIRTIO_BALLOON_F_FREE_PAGE_HINT,
	VIRTIO_BALLOON_F_PAGE_POISON,
	VIRTIO_BALLOON_F_REPORTING,
पूर्ण;

अटल काष्ठा virtio_driver virtio_balloon_driver = अणु
	.feature_table = features,
	.feature_table_size = ARRAY_SIZE(features),
	.driver.name =	KBUILD_MODNAME,
	.driver.owner =	THIS_MODULE,
	.id_table =	id_table,
	.validate =	virtballoon_validate,
	.probe =	virtballoon_probe,
	.हटाओ =	virtballoon_हटाओ,
	.config_changed = virtballoon_changed,
#अगर_घोषित CONFIG_PM_SLEEP
	.मुक्तze	=	virtballoon_मुक्तze,
	.restore =	virtballoon_restore,
#पूर्ण_अगर
पूर्ण;

module_virtio_driver(virtio_balloon_driver);
MODULE_DEVICE_TABLE(virtio, id_table);
MODULE_DESCRIPTION("Virtio balloon driver");
MODULE_LICENSE("GPL");
