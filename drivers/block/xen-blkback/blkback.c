<शैली गुरु>
/******************************************************************************
 *
 * Back-end of the driver क्रम भव block devices. This portion of the
 * driver exports a 'unified' block-device पूर्णांकerface that can be accessed
 * by any operating प्रणाली that implements a compatible front end. A
 * reference front-end implementation can be found in:
 *  drivers/block/xen-blkfront.c
 *
 * Copyright (c) 2003-2004, Keir Fraser & Steve Hand
 * Copyright (c) 2005, Christopher Clark
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#घोषणा pr_fmt(fmt) "xen-blkback: " fmt

#समावेश <linux/spinlock.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/list.h>
#समावेश <linux/delay.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/biपंचांगap.h>

#समावेश <xen/events.h>
#समावेश <xen/page.h>
#समावेश <xen/xen.h>
#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <यंत्र/xen/hypercall.h>
#समावेश <xen/balloon.h>
#समावेश <xen/grant_table.h>
#समावेश "common.h"

/*
 * Maximum number of unused मुक्त pages to keep in the पूर्णांकernal buffer.
 * Setting this to a value too low will reduce memory used in each backend,
 * but can have a perक्रमmance penalty.
 *
 * A sane value is xen_blkअगर_reqs * BLKIF_MAX_SEGMENTS_PER_REQUEST, but can
 * be set to a lower value that might degrade perक्रमmance on some पूर्णांकensive
 * IO workloads.
 */

अटल पूर्णांक max_buffer_pages = 1024;
module_param_named(max_buffer_pages, max_buffer_pages, पूर्णांक, 0644);
MODULE_PARM_DESC(max_buffer_pages,
"Maximum number of free pages to keep in each block backend buffer");

/*
 * Maximum number of grants to map persistently in blkback. For maximum
 * perक्रमmance this should be the total numbers of grants that can be used
 * to fill the ring, but since this might become too high, specially with
 * the use of indirect descriptors, we set it to a value that provides good
 * perक्रमmance without using too much memory.
 *
 * When the list of persistent grants is full we clean it up using a LRU
 * algorithm.
 */

अटल पूर्णांक max_pgrants = 1056;
module_param_named(max_persistent_grants, max_pgrants, पूर्णांक, 0644);
MODULE_PARM_DESC(max_persistent_grants,
                 "Maximum number of grants to map persistently");

/*
 * How दीर्घ a persistent grant is allowed to reमुख्य allocated without being in
 * use. The समय is in seconds, 0 means indefinitely दीर्घ.
 */

अटल अचिन्हित पूर्णांक pgrant_समयout = 60;
module_param_named(persistent_grant_unused_seconds, pgrant_समयout,
		   uपूर्णांक, 0644);
MODULE_PARM_DESC(persistent_grant_unused_seconds,
		 "Time in seconds an unused persistent grant is allowed to "
		 "remain allocated. Default is 60, 0 means unlimited.");

/*
 * Maximum number of rings/queues blkback supports, allow as many queues as there
 * are CPUs अगर user has not specअगरied a value.
 */
अचिन्हित पूर्णांक xenblk_max_queues;
module_param_named(max_queues, xenblk_max_queues, uपूर्णांक, 0644);
MODULE_PARM_DESC(max_queues,
		 "Maximum number of hardware queues per virtual disk." \
		 "By default it is the number of online CPUs.");

/*
 * Maximum order of pages to be used क्रम the shared ring between front and
 * backend, 4KB page granularity is used.
 */
अचिन्हित पूर्णांक xen_blkअगर_max_ring_order = XENBUS_MAX_RING_GRANT_ORDER;
module_param_named(max_ring_page_order, xen_blkअगर_max_ring_order, पूर्णांक, 0444);
MODULE_PARM_DESC(max_ring_page_order, "Maximum order of pages to be used for the shared ring");
/*
 * The LRU mechanism to clean the lists of persistent grants needs to
 * be executed periodically. The समय पूर्णांकerval between consecutive executions
 * of the purge mechanism is set in ms.
 */
#घोषणा LRU_INTERVAL 100

/*
 * When the persistent grants list is full we will हटाओ unused grants
 * from the list. The percent number of grants to be हटाओd at each LRU
 * execution.
 */
#घोषणा LRU_PERCENT_CLEAN 5

/* Run-समय चयनable: /sys/module/blkback/parameters/ */
अटल अचिन्हित पूर्णांक log_stats;
module_param(log_stats, पूर्णांक, 0644);

#घोषणा BLKBACK_INVALID_HANDLE (~0)

अटल अंतरभूत bool persistent_gnt_समयout(काष्ठा persistent_gnt *persistent_gnt)
अणु
	वापस pgrant_समयout && (jअगरfies - persistent_gnt->last_used >=
			HZ * pgrant_समयout);
पूर्ण

#घोषणा vaddr(page) ((अचिन्हित दीर्घ)pfn_to_kaddr(page_to_pfn(page)))

अटल पूर्णांक करो_block_io_op(काष्ठा xen_blkअगर_ring *ring, अचिन्हित पूर्णांक *eoi_flags);
अटल पूर्णांक dispatch_rw_block_io(काष्ठा xen_blkअगर_ring *ring,
				काष्ठा blkअगर_request *req,
				काष्ठा pending_req *pending_req);
अटल व्योम make_response(काष्ठा xen_blkअगर_ring *ring, u64 id,
			  अचिन्हित लघु op, पूर्णांक st);

#घोषणा क्रमeach_grant_safe(pos, n, rbtree, node) \
	क्रम ((pos) = container_of(rb_first((rbtree)), typeof(*(pos)), node), \
	     (n) = (&(pos)->node != शून्य) ? rb_next(&(pos)->node) : शून्य; \
	     &(pos)->node != शून्य; \
	     (pos) = container_of(n, typeof(*(pos)), node), \
	     (n) = (&(pos)->node != शून्य) ? rb_next(&(pos)->node) : शून्य)


/*
 * We करोn't need locking around the persistent grant helpers
 * because blkback uses a single-thपढ़ो क्रम each backend, so we
 * can be sure that this functions will never be called recursively.
 *
 * The only exception to that is put_persistent_grant, that can be called
 * from पूर्णांकerrupt context (by xen_blkbk_unmap), so we have to use atomic
 * bit operations to modअगरy the flags of a persistent grant and to count
 * the number of used grants.
 */
अटल पूर्णांक add_persistent_gnt(काष्ठा xen_blkअगर_ring *ring,
			       काष्ठा persistent_gnt *persistent_gnt)
अणु
	काष्ठा rb_node **new = शून्य, *parent = शून्य;
	काष्ठा persistent_gnt *this;
	काष्ठा xen_blkअगर *blkअगर = ring->blkअगर;

	अगर (ring->persistent_gnt_c >= max_pgrants) अणु
		अगर (!blkअगर->vbd.overflow_max_grants)
			blkअगर->vbd.overflow_max_grants = 1;
		वापस -EBUSY;
	पूर्ण
	/* Figure out where to put new node */
	new = &ring->persistent_gnts.rb_node;
	जबतक (*new) अणु
		this = container_of(*new, काष्ठा persistent_gnt, node);

		parent = *new;
		अगर (persistent_gnt->gnt < this->gnt)
			new = &((*new)->rb_left);
		अन्यथा अगर (persistent_gnt->gnt > this->gnt)
			new = &((*new)->rb_right);
		अन्यथा अणु
			pr_alert_ratelimited("trying to add a gref that's already in the tree\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	persistent_gnt->active = true;
	/* Add new node and rebalance tree. */
	rb_link_node(&(persistent_gnt->node), parent, new);
	rb_insert_color(&(persistent_gnt->node), &ring->persistent_gnts);
	ring->persistent_gnt_c++;
	atomic_inc(&ring->persistent_gnt_in_use);
	वापस 0;
पूर्ण

अटल काष्ठा persistent_gnt *get_persistent_gnt(काष्ठा xen_blkअगर_ring *ring,
						 grant_ref_t gref)
अणु
	काष्ठा persistent_gnt *data;
	काष्ठा rb_node *node = शून्य;

	node = ring->persistent_gnts.rb_node;
	जबतक (node) अणु
		data = container_of(node, काष्ठा persistent_gnt, node);

		अगर (gref < data->gnt)
			node = node->rb_left;
		अन्यथा अगर (gref > data->gnt)
			node = node->rb_right;
		अन्यथा अणु
			अगर (data->active) अणु
				pr_alert_ratelimited("requesting a grant already in use\n");
				वापस शून्य;
			पूर्ण
			data->active = true;
			atomic_inc(&ring->persistent_gnt_in_use);
			वापस data;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम put_persistent_gnt(काष्ठा xen_blkअगर_ring *ring,
                               काष्ठा persistent_gnt *persistent_gnt)
अणु
	अगर (!persistent_gnt->active)
		pr_alert_ratelimited("freeing a grant already unused\n");
	persistent_gnt->last_used = jअगरfies;
	persistent_gnt->active = false;
	atomic_dec(&ring->persistent_gnt_in_use);
पूर्ण

अटल व्योम मुक्त_persistent_gnts(काष्ठा xen_blkअगर_ring *ring, काष्ठा rb_root *root,
                                 अचिन्हित पूर्णांक num)
अणु
	काष्ठा gnttab_unmap_grant_ref unmap[BLKIF_MAX_SEGMENTS_PER_REQUEST];
	काष्ठा page *pages[BLKIF_MAX_SEGMENTS_PER_REQUEST];
	काष्ठा persistent_gnt *persistent_gnt;
	काष्ठा rb_node *n;
	पूर्णांक segs_to_unmap = 0;
	काष्ठा gntab_unmap_queue_data unmap_data;

	unmap_data.pages = pages;
	unmap_data.unmap_ops = unmap;
	unmap_data.kunmap_ops = शून्य;

	क्रमeach_grant_safe(persistent_gnt, n, root, node) अणु
		BUG_ON(persistent_gnt->handle ==
			BLKBACK_INVALID_HANDLE);
		gnttab_set_unmap_op(&unmap[segs_to_unmap],
			(अचिन्हित दीर्घ) pfn_to_kaddr(page_to_pfn(
				persistent_gnt->page)),
			GNTMAP_host_map,
			persistent_gnt->handle);

		pages[segs_to_unmap] = persistent_gnt->page;

		अगर (++segs_to_unmap == BLKIF_MAX_SEGMENTS_PER_REQUEST ||
			!rb_next(&persistent_gnt->node)) अणु

			unmap_data.count = segs_to_unmap;
			BUG_ON(gnttab_unmap_refs_sync(&unmap_data));

			gnttab_page_cache_put(&ring->मुक्त_pages, pages,
					      segs_to_unmap);
			segs_to_unmap = 0;
		पूर्ण

		rb_erase(&persistent_gnt->node, root);
		kमुक्त(persistent_gnt);
		num--;
	पूर्ण
	BUG_ON(num != 0);
पूर्ण

व्योम xen_blkbk_unmap_purged_grants(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gnttab_unmap_grant_ref unmap[BLKIF_MAX_SEGMENTS_PER_REQUEST];
	काष्ठा page *pages[BLKIF_MAX_SEGMENTS_PER_REQUEST];
	काष्ठा persistent_gnt *persistent_gnt;
	पूर्णांक segs_to_unmap = 0;
	काष्ठा xen_blkअगर_ring *ring = container_of(work, typeof(*ring), persistent_purge_work);
	काष्ठा gntab_unmap_queue_data unmap_data;

	unmap_data.pages = pages;
	unmap_data.unmap_ops = unmap;
	unmap_data.kunmap_ops = शून्य;

	जबतक(!list_empty(&ring->persistent_purge_list)) अणु
		persistent_gnt = list_first_entry(&ring->persistent_purge_list,
		                                  काष्ठा persistent_gnt,
		                                  हटाओ_node);
		list_del(&persistent_gnt->हटाओ_node);

		gnttab_set_unmap_op(&unmap[segs_to_unmap],
			vaddr(persistent_gnt->page),
			GNTMAP_host_map,
			persistent_gnt->handle);

		pages[segs_to_unmap] = persistent_gnt->page;

		अगर (++segs_to_unmap == BLKIF_MAX_SEGMENTS_PER_REQUEST) अणु
			unmap_data.count = segs_to_unmap;
			BUG_ON(gnttab_unmap_refs_sync(&unmap_data));
			gnttab_page_cache_put(&ring->मुक्त_pages, pages,
					      segs_to_unmap);
			segs_to_unmap = 0;
		पूर्ण
		kमुक्त(persistent_gnt);
	पूर्ण
	अगर (segs_to_unmap > 0) अणु
		unmap_data.count = segs_to_unmap;
		BUG_ON(gnttab_unmap_refs_sync(&unmap_data));
		gnttab_page_cache_put(&ring->मुक्त_pages, pages, segs_to_unmap);
	पूर्ण
पूर्ण

अटल व्योम purge_persistent_gnt(काष्ठा xen_blkअगर_ring *ring)
अणु
	काष्ठा persistent_gnt *persistent_gnt;
	काष्ठा rb_node *n;
	अचिन्हित पूर्णांक num_clean, total;
	bool scan_used = false;
	काष्ठा rb_root *root;

	अगर (work_busy(&ring->persistent_purge_work)) अणु
		pr_alert_ratelimited("Scheduled work from previous purge is still busy, cannot purge list\n");
		जाओ out;
	पूर्ण

	अगर (ring->persistent_gnt_c < max_pgrants ||
	    (ring->persistent_gnt_c == max_pgrants &&
	    !ring->blkअगर->vbd.overflow_max_grants)) अणु
		num_clean = 0;
	पूर्ण अन्यथा अणु
		num_clean = (max_pgrants / 100) * LRU_PERCENT_CLEAN;
		num_clean = ring->persistent_gnt_c - max_pgrants + num_clean;
		num_clean = min(ring->persistent_gnt_c, num_clean);
		pr_debug("Going to purge at least %u persistent grants\n",
			 num_clean);
	पूर्ण

	/*
	 * At this poपूर्णांक, we can assure that there will be no calls
         * to get_persistent_grant (because we are executing this code from
         * xen_blkअगर_schedule), there can only be calls to put_persistent_gnt,
         * which means that the number of currently used grants will go करोwn,
         * but never up, so we will always be able to हटाओ the requested
         * number of grants.
	 */

	total = 0;

	BUG_ON(!list_empty(&ring->persistent_purge_list));
	root = &ring->persistent_gnts;
purge_list:
	क्रमeach_grant_safe(persistent_gnt, n, root, node) अणु
		BUG_ON(persistent_gnt->handle ==
			BLKBACK_INVALID_HANDLE);

		अगर (persistent_gnt->active)
			जारी;
		अगर (!scan_used && !persistent_gnt_समयout(persistent_gnt))
			जारी;
		अगर (scan_used && total >= num_clean)
			जारी;

		rb_erase(&persistent_gnt->node, root);
		list_add(&persistent_gnt->हटाओ_node,
			 &ring->persistent_purge_list);
		total++;
	पूर्ण
	/*
	 * Check whether we also need to start cleaning
	 * grants that were used since last purge in order to cope
	 * with the requested num
	 */
	अगर (!scan_used && total < num_clean) अणु
		pr_debug("Still missing %u purged frames\n", num_clean - total);
		scan_used = true;
		जाओ purge_list;
	पूर्ण

	अगर (total) अणु
		ring->persistent_gnt_c -= total;
		ring->blkअगर->vbd.overflow_max_grants = 0;

		/* We can defer this work */
		schedule_work(&ring->persistent_purge_work);
		pr_debug("Purged %u/%u\n", num_clean, total);
	पूर्ण

out:
	वापस;
पूर्ण

/*
 * Retrieve from the 'pending_reqs' a मुक्त pending_req काष्ठाure to be used.
 */
अटल काष्ठा pending_req *alloc_req(काष्ठा xen_blkअगर_ring *ring)
अणु
	काष्ठा pending_req *req = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ring->pending_मुक्त_lock, flags);
	अगर (!list_empty(&ring->pending_मुक्त)) अणु
		req = list_entry(ring->pending_मुक्त.next, काष्ठा pending_req,
				 मुक्त_list);
		list_del(&req->मुक्त_list);
	पूर्ण
	spin_unlock_irqrestore(&ring->pending_मुक्त_lock, flags);
	वापस req;
पूर्ण

/*
 * Return the 'pending_req' काष्ठाure back to the मुक्तpool. We also
 * wake up the thपढ़ो अगर it was रुकोing क्रम a मुक्त page.
 */
अटल व्योम मुक्त_req(काष्ठा xen_blkअगर_ring *ring, काष्ठा pending_req *req)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक was_empty;

	spin_lock_irqsave(&ring->pending_मुक्त_lock, flags);
	was_empty = list_empty(&ring->pending_मुक्त);
	list_add(&req->मुक्त_list, &ring->pending_मुक्त);
	spin_unlock_irqrestore(&ring->pending_मुक्त_lock, flags);
	अगर (was_empty)
		wake_up(&ring->pending_मुक्त_wq);
पूर्ण

/*
 * Routines क्रम managing भव block devices (vbds).
 */
अटल पूर्णांक xen_vbd_translate(काष्ठा phys_req *req, काष्ठा xen_blkअगर *blkअगर,
			     पूर्णांक operation)
अणु
	काष्ठा xen_vbd *vbd = &blkअगर->vbd;
	पूर्णांक rc = -EACCES;

	अगर ((operation != REQ_OP_READ) && vbd->पढ़ोonly)
		जाओ out;

	अगर (likely(req->nr_sects)) अणु
		blkअगर_sector_t end = req->sector_number + req->nr_sects;

		अगर (unlikely(end < req->sector_number))
			जाओ out;
		अगर (unlikely(end > vbd_sz(vbd)))
			जाओ out;
	पूर्ण

	req->dev  = vbd->pdevice;
	req->bdev = vbd->bdev;
	rc = 0;

 out:
	वापस rc;
पूर्ण

अटल व्योम xen_vbd_resize(काष्ठा xen_blkअगर *blkअगर)
अणु
	काष्ठा xen_vbd *vbd = &blkअगर->vbd;
	काष्ठा xenbus_transaction xbt;
	पूर्णांक err;
	काष्ठा xenbus_device *dev = xen_blkbk_xenbus(blkअगर->be);
	अचिन्हित दीर्घ दीर्घ new_size = vbd_sz(vbd);

	pr_info("VBD Resize: Domid: %d, Device: (%d, %d)\n",
		blkअगर->करोmid, MAJOR(vbd->pdevice), MINOR(vbd->pdevice));
	pr_info("VBD Resize: new size %llu\n", new_size);
	vbd->size = new_size;
again:
	err = xenbus_transaction_start(&xbt);
	अगर (err) अणु
		pr_warn("Error starting transaction\n");
		वापस;
	पूर्ण
	err = xenbus_म_लिखो(xbt, dev->nodename, "sectors", "%llu",
			    (अचिन्हित दीर्घ दीर्घ)vbd_sz(vbd));
	अगर (err) अणु
		pr_warn("Error writing new size\n");
		जाओ पात;
	पूर्ण
	/*
	 * Write the current state; we will use this to synchronize
	 * the front-end. If the current state is "connected" the
	 * front-end will get the new size inक्रमmation online.
	 */
	err = xenbus_म_लिखो(xbt, dev->nodename, "state", "%d", dev->state);
	अगर (err) अणु
		pr_warn("Error writing the state\n");
		जाओ पात;
	पूर्ण

	err = xenbus_transaction_end(xbt, 0);
	अगर (err == -EAGAIN)
		जाओ again;
	अगर (err)
		pr_warn("Error ending transaction\n");
	वापस;
पात:
	xenbus_transaction_end(xbt, 1);
पूर्ण

/*
 * Notअगरication from the guest OS.
 */
अटल व्योम blkअगर_notअगरy_work(काष्ठा xen_blkअगर_ring *ring)
अणु
	ring->रुकोing_reqs = 1;
	wake_up(&ring->wq);
पूर्ण

irqवापस_t xen_blkअगर_be_पूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	blkअगर_notअगरy_work(dev_id);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * SCHEDULER FUNCTIONS
 */

अटल व्योम prपूर्णांक_stats(काष्ठा xen_blkअगर_ring *ring)
अणु
	pr_info("(%s): oo %3llu  |  rd %4llu  |  wr %4llu  |  f %4llu"
		 "  |  ds %4llu | pg: %4u/%4d\n",
		 current->comm, ring->st_oo_req,
		 ring->st_rd_req, ring->st_wr_req,
		 ring->st_f_req, ring->st_ds_req,
		 ring->persistent_gnt_c, max_pgrants);
	ring->st_prपूर्णांक = jअगरfies + msecs_to_jअगरfies(10 * 1000);
	ring->st_rd_req = 0;
	ring->st_wr_req = 0;
	ring->st_oo_req = 0;
	ring->st_ds_req = 0;
पूर्ण

पूर्णांक xen_blkअगर_schedule(व्योम *arg)
अणु
	काष्ठा xen_blkअगर_ring *ring = arg;
	काष्ठा xen_blkअगर *blkअगर = ring->blkअगर;
	काष्ठा xen_vbd *vbd = &blkअगर->vbd;
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;
	bool करो_eoi;
	अचिन्हित पूर्णांक eoi_flags = XEN_EOI_FLAG_SPURIOUS;

	set_मुक्तzable();
	जबतक (!kthपढ़ो_should_stop()) अणु
		अगर (try_to_मुक्तze())
			जारी;
		अगर (unlikely(vbd->size != vbd_sz(vbd)))
			xen_vbd_resize(blkअगर);

		समयout = msecs_to_jअगरfies(LRU_INTERVAL);

		समयout = रुको_event_पूर्णांकerruptible_समयout(
			ring->wq,
			ring->रुकोing_reqs || kthपढ़ो_should_stop(),
			समयout);
		अगर (समयout == 0)
			जाओ purge_gnt_list;
		समयout = रुको_event_पूर्णांकerruptible_समयout(
			ring->pending_मुक्त_wq,
			!list_empty(&ring->pending_मुक्त) ||
			kthपढ़ो_should_stop(),
			समयout);
		अगर (समयout == 0)
			जाओ purge_gnt_list;

		करो_eoi = ring->रुकोing_reqs;

		ring->रुकोing_reqs = 0;
		smp_mb(); /* clear flag *beक्रमe* checking क्रम work */

		ret = करो_block_io_op(ring, &eoi_flags);
		अगर (ret > 0)
			ring->रुकोing_reqs = 1;
		अगर (ret == -EACCES)
			रुको_event_पूर्णांकerruptible(ring->shutकरोwn_wq,
						 kthपढ़ो_should_stop());

		अगर (करो_eoi && !ring->रुकोing_reqs) अणु
			xen_irq_lateeoi(ring->irq, eoi_flags);
			eoi_flags |= XEN_EOI_FLAG_SPURIOUS;
		पूर्ण

purge_gnt_list:
		अगर (blkअगर->vbd.feature_gnt_persistent &&
		    समय_after(jअगरfies, ring->next_lru)) अणु
			purge_persistent_gnt(ring);
			ring->next_lru = jअगरfies + msecs_to_jअगरfies(LRU_INTERVAL);
		पूर्ण

		/* Shrink the मुक्त pages pool अगर it is too large. */
		अगर (समय_beक्रमe(jअगरfies, blkअगर->buffer_squeeze_end))
			gnttab_page_cache_shrink(&ring->मुक्त_pages, 0);
		अन्यथा
			gnttab_page_cache_shrink(&ring->मुक्त_pages,
						 max_buffer_pages);

		अगर (log_stats && समय_after(jअगरfies, ring->st_prपूर्णांक))
			prपूर्णांक_stats(ring);
	पूर्ण

	/* Drain pending purge work */
	flush_work(&ring->persistent_purge_work);

	अगर (log_stats)
		prपूर्णांक_stats(ring);

	ring->xenblkd = शून्य;

	वापस 0;
पूर्ण

/*
 * Remove persistent grants and empty the pool of मुक्त pages
 */
व्योम xen_blkbk_मुक्त_caches(काष्ठा xen_blkअगर_ring *ring)
अणु
	/* Free all persistent grant pages */
	अगर (!RB_EMPTY_ROOT(&ring->persistent_gnts))
		मुक्त_persistent_gnts(ring, &ring->persistent_gnts,
			ring->persistent_gnt_c);

	BUG_ON(!RB_EMPTY_ROOT(&ring->persistent_gnts));
	ring->persistent_gnt_c = 0;

	/* Since we are shutting करोwn हटाओ all pages from the buffer */
	gnttab_page_cache_shrink(&ring->मुक्त_pages, 0 /* All */);
पूर्ण

अटल अचिन्हित पूर्णांक xen_blkbk_unmap_prepare(
	काष्ठा xen_blkअगर_ring *ring,
	काष्ठा grant_page **pages,
	अचिन्हित पूर्णांक num,
	काष्ठा gnttab_unmap_grant_ref *unmap_ops,
	काष्ठा page **unmap_pages)
अणु
	अचिन्हित पूर्णांक i, invcount = 0;

	क्रम (i = 0; i < num; i++) अणु
		अगर (pages[i]->persistent_gnt != शून्य) अणु
			put_persistent_gnt(ring, pages[i]->persistent_gnt);
			जारी;
		पूर्ण
		अगर (pages[i]->handle == BLKBACK_INVALID_HANDLE)
			जारी;
		unmap_pages[invcount] = pages[i]->page;
		gnttab_set_unmap_op(&unmap_ops[invcount], vaddr(pages[i]->page),
				    GNTMAP_host_map, pages[i]->handle);
		pages[i]->handle = BLKBACK_INVALID_HANDLE;
		invcount++;
	पूर्ण

	वापस invcount;
पूर्ण

अटल व्योम xen_blkbk_unmap_and_respond_callback(पूर्णांक result, काष्ठा gntab_unmap_queue_data *data)
अणु
	काष्ठा pending_req *pending_req = (काष्ठा pending_req *)(data->data);
	काष्ठा xen_blkअगर_ring *ring = pending_req->ring;
	काष्ठा xen_blkअगर *blkअगर = ring->blkअगर;

	/* BUG_ON used to reproduce existing behaviour,
	   but is this the best way to deal with this? */
	BUG_ON(result);

	gnttab_page_cache_put(&ring->मुक्त_pages, data->pages, data->count);
	make_response(ring, pending_req->id,
		      pending_req->operation, pending_req->status);
	मुक्त_req(ring, pending_req);
	/*
	 * Make sure the request is मुक्तd beक्रमe releasing blkअगर,
	 * or there could be a race between मुक्त_req and the
	 * cleanup करोne in xen_blkअगर_मुक्त during shutकरोwn.
	 *
	 * NB: The fact that we might try to wake up pending_मुक्त_wq
	 * beक्रमe drain_complete (in हाल there's a drain going on)
	 * it's not a problem with our current implementation
	 * because we can assure there's no thपढ़ो रुकोing on
	 * pending_मुक्त_wq अगर there's a drain going on, but it has
	 * to be taken पूर्णांकo account अगर the current model is changed.
	 */
	अगर (atomic_dec_and_test(&ring->inflight) && atomic_पढ़ो(&blkअगर->drain)) अणु
		complete(&blkअगर->drain_complete);
	पूर्ण
	xen_blkअगर_put(blkअगर);
पूर्ण

अटल व्योम xen_blkbk_unmap_and_respond(काष्ठा pending_req *req)
अणु
	काष्ठा gntab_unmap_queue_data* work = &req->gnttab_unmap_data;
	काष्ठा xen_blkअगर_ring *ring = req->ring;
	काष्ठा grant_page **pages = req->segments;
	अचिन्हित पूर्णांक invcount;

	invcount = xen_blkbk_unmap_prepare(ring, pages, req->nr_segs,
					   req->unmap, req->unmap_pages);

	work->data = req;
	work->करोne = xen_blkbk_unmap_and_respond_callback;
	work->unmap_ops = req->unmap;
	work->kunmap_ops = शून्य;
	work->pages = req->unmap_pages;
	work->count = invcount;

	gnttab_unmap_refs_async(&req->gnttab_unmap_data);
पूर्ण


/*
 * Unmap the grant references.
 *
 * This could accumulate ops up to the batch size to reduce the number
 * of hypercalls, but since this is only used in error paths there's
 * no real need.
 */
अटल व्योम xen_blkbk_unmap(काष्ठा xen_blkअगर_ring *ring,
                            काष्ठा grant_page *pages[],
                            पूर्णांक num)
अणु
	काष्ठा gnttab_unmap_grant_ref unmap[BLKIF_MAX_SEGMENTS_PER_REQUEST];
	काष्ठा page *unmap_pages[BLKIF_MAX_SEGMENTS_PER_REQUEST];
	अचिन्हित पूर्णांक invcount = 0;
	पूर्णांक ret;

	जबतक (num) अणु
		अचिन्हित पूर्णांक batch = min(num, BLKIF_MAX_SEGMENTS_PER_REQUEST);

		invcount = xen_blkbk_unmap_prepare(ring, pages, batch,
						   unmap, unmap_pages);
		अगर (invcount) अणु
			ret = gnttab_unmap_refs(unmap, शून्य, unmap_pages, invcount);
			BUG_ON(ret);
			gnttab_page_cache_put(&ring->मुक्त_pages, unmap_pages,
					      invcount);
		पूर्ण
		pages += batch;
		num -= batch;
	पूर्ण
पूर्ण

अटल पूर्णांक xen_blkbk_map(काष्ठा xen_blkअगर_ring *ring,
			 काष्ठा grant_page *pages[],
			 पूर्णांक num, bool ro)
अणु
	काष्ठा gnttab_map_grant_ref map[BLKIF_MAX_SEGMENTS_PER_REQUEST];
	काष्ठा page *pages_to_gnt[BLKIF_MAX_SEGMENTS_PER_REQUEST];
	काष्ठा persistent_gnt *persistent_gnt = शून्य;
	phys_addr_t addr = 0;
	पूर्णांक i, seg_idx, new_map_idx;
	पूर्णांक segs_to_map = 0;
	पूर्णांक ret = 0;
	पूर्णांक last_map = 0, map_until = 0;
	पूर्णांक use_persistent_gnts;
	काष्ठा xen_blkअगर *blkअगर = ring->blkअगर;

	use_persistent_gnts = (blkअगर->vbd.feature_gnt_persistent);

	/*
	 * Fill out preq.nr_sects with proper amount of sectors, and setup
	 * assign map[..] with the PFN of the page in our करोमुख्य with the
	 * corresponding grant reference क्रम each page.
	 */
again:
	क्रम (i = map_until; i < num; i++) अणु
		uपूर्णांक32_t flags;

		अगर (use_persistent_gnts) अणु
			persistent_gnt = get_persistent_gnt(
				ring,
				pages[i]->gref);
		पूर्ण

		अगर (persistent_gnt) अणु
			/*
			 * We are using persistent grants and
			 * the grant is alपढ़ोy mapped
			 */
			pages[i]->page = persistent_gnt->page;
			pages[i]->persistent_gnt = persistent_gnt;
		पूर्ण अन्यथा अणु
			अगर (gnttab_page_cache_get(&ring->मुक्त_pages,
						  &pages[i]->page)) अणु
				gnttab_page_cache_put(&ring->मुक्त_pages,
						      pages_to_gnt,
						      segs_to_map);
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			addr = vaddr(pages[i]->page);
			pages_to_gnt[segs_to_map] = pages[i]->page;
			pages[i]->persistent_gnt = शून्य;
			flags = GNTMAP_host_map;
			अगर (!use_persistent_gnts && ro)
				flags |= GNTMAP_पढ़ोonly;
			gnttab_set_map_op(&map[segs_to_map++], addr,
					  flags, pages[i]->gref,
					  blkअगर->करोmid);
		पूर्ण
		map_until = i + 1;
		अगर (segs_to_map == BLKIF_MAX_SEGMENTS_PER_REQUEST)
			अवरोध;
	पूर्ण

	अगर (segs_to_map)
		ret = gnttab_map_refs(map, शून्य, pages_to_gnt, segs_to_map);

	/*
	 * Now swizzle the MFN in our करोमुख्य with the MFN from the other करोमुख्य
	 * so that when we access vaddr(pending_req,i) it has the contents of
	 * the page from the other करोमुख्य.
	 */
	क्रम (seg_idx = last_map, new_map_idx = 0; seg_idx < map_until; seg_idx++) अणु
		अगर (!pages[seg_idx]->persistent_gnt) अणु
			/* This is a newly mapped grant */
			BUG_ON(new_map_idx >= segs_to_map);
			अगर (unlikely(map[new_map_idx].status != 0)) अणु
				pr_debug("invalid buffer -- could not remap it\n");
				gnttab_page_cache_put(&ring->मुक्त_pages,
						      &pages[seg_idx]->page, 1);
				pages[seg_idx]->handle = BLKBACK_INVALID_HANDLE;
				ret |= !ret;
				जाओ next;
			पूर्ण
			pages[seg_idx]->handle = map[new_map_idx].handle;
		पूर्ण अन्यथा अणु
			जारी;
		पूर्ण
		अगर (use_persistent_gnts &&
		    ring->persistent_gnt_c < max_pgrants) अणु
			/*
			 * We are using persistent grants, the grant is
			 * not mapped but we might have room क्रम it.
			 */
			persistent_gnt = kदो_स्मृति(माप(काष्ठा persistent_gnt),
				                 GFP_KERNEL);
			अगर (!persistent_gnt) अणु
				/*
				 * If we करोn't have enough memory to
				 * allocate the persistent_gnt काष्ठा
				 * map this grant non-persistenly
				 */
				जाओ next;
			पूर्ण
			persistent_gnt->gnt = map[new_map_idx].ref;
			persistent_gnt->handle = map[new_map_idx].handle;
			persistent_gnt->page = pages[seg_idx]->page;
			अगर (add_persistent_gnt(ring,
			                       persistent_gnt)) अणु
				kमुक्त(persistent_gnt);
				persistent_gnt = शून्य;
				जाओ next;
			पूर्ण
			pages[seg_idx]->persistent_gnt = persistent_gnt;
			pr_debug("grant %u added to the tree of persistent grants, using %u/%u\n",
				 persistent_gnt->gnt, ring->persistent_gnt_c,
				 max_pgrants);
			जाओ next;
		पूर्ण
		अगर (use_persistent_gnts && !blkअगर->vbd.overflow_max_grants) अणु
			blkअगर->vbd.overflow_max_grants = 1;
			pr_debug("domain %u, device %#x is using maximum number of persistent grants\n",
			         blkअगर->करोmid, blkअगर->vbd.handle);
		पूर्ण
		/*
		 * We could not map this grant persistently, so use it as
		 * a non-persistent grant.
		 */
next:
		new_map_idx++;
	पूर्ण
	segs_to_map = 0;
	last_map = map_until;
	अगर (!ret && map_until != num)
		जाओ again;

out:
	क्रम (i = last_map; i < num; i++) अणु
		/* Don't zap current batch's valid persistent grants. */
		अगर(i >= map_until)
			pages[i]->persistent_gnt = शून्य;
		pages[i]->handle = BLKBACK_INVALID_HANDLE;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक xen_blkbk_map_seg(काष्ठा pending_req *pending_req)
अणु
	पूर्णांक rc;

	rc = xen_blkbk_map(pending_req->ring, pending_req->segments,
			   pending_req->nr_segs,
	                   (pending_req->operation != BLKIF_OP_READ));

	वापस rc;
पूर्ण

अटल पूर्णांक xen_blkbk_parse_indirect(काष्ठा blkअगर_request *req,
				    काष्ठा pending_req *pending_req,
				    काष्ठा seg_buf seg[],
				    काष्ठा phys_req *preq)
अणु
	काष्ठा grant_page **pages = pending_req->indirect_pages;
	काष्ठा xen_blkअगर_ring *ring = pending_req->ring;
	पूर्णांक indirect_grefs, rc, n, nseg, i;
	काष्ठा blkअगर_request_segment *segments = शून्य;

	nseg = pending_req->nr_segs;
	indirect_grefs = INसूचीECT_PAGES(nseg);
	BUG_ON(indirect_grefs > BLKIF_MAX_INसूचीECT_PAGES_PER_REQUEST);

	क्रम (i = 0; i < indirect_grefs; i++)
		pages[i]->gref = req->u.indirect.indirect_grefs[i];

	rc = xen_blkbk_map(ring, pages, indirect_grefs, true);
	अगर (rc)
		जाओ unmap;

	क्रम (n = 0, i = 0; n < nseg; n++) अणु
		uपूर्णांक8_t first_sect, last_sect;

		अगर ((n % SEGS_PER_INसूचीECT_FRAME) == 0) अणु
			/* Map indirect segments */
			अगर (segments)
				kunmap_atomic(segments);
			segments = kmap_atomic(pages[n/SEGS_PER_INसूचीECT_FRAME]->page);
		पूर्ण
		i = n % SEGS_PER_INसूचीECT_FRAME;

		pending_req->segments[n]->gref = segments[i].gref;

		first_sect = READ_ONCE(segments[i].first_sect);
		last_sect = READ_ONCE(segments[i].last_sect);
		अगर (last_sect >= (XEN_PAGE_SIZE >> 9) || last_sect < first_sect) अणु
			rc = -EINVAL;
			जाओ unmap;
		पूर्ण

		seg[n].nsec = last_sect - first_sect + 1;
		seg[n].offset = first_sect << 9;
		preq->nr_sects += seg[n].nsec;
	पूर्ण

unmap:
	अगर (segments)
		kunmap_atomic(segments);
	xen_blkbk_unmap(ring, pages, indirect_grefs);
	वापस rc;
पूर्ण

अटल पूर्णांक dispatch_discard_io(काष्ठा xen_blkअगर_ring *ring,
				काष्ठा blkअगर_request *req)
अणु
	पूर्णांक err = 0;
	पूर्णांक status = BLKIF_RSP_OKAY;
	काष्ठा xen_blkअगर *blkअगर = ring->blkअगर;
	काष्ठा block_device *bdev = blkअगर->vbd.bdev;
	अचिन्हित दीर्घ secure;
	काष्ठा phys_req preq;

	xen_blkअगर_get(blkअगर);

	preq.sector_number = req->u.discard.sector_number;
	preq.nr_sects      = req->u.discard.nr_sectors;

	err = xen_vbd_translate(&preq, blkअगर, REQ_OP_WRITE);
	अगर (err) अणु
		pr_warn("access denied: DISCARD [%llu->%llu] on dev=%04x\n",
			preq.sector_number,
			preq.sector_number + preq.nr_sects, blkअगर->vbd.pdevice);
		जाओ fail_response;
	पूर्ण
	ring->st_ds_req++;

	secure = (blkअगर->vbd.discard_secure &&
		 (req->u.discard.flag & BLKIF_DISCARD_SECURE)) ?
		 BLKDEV_DISCARD_SECURE : 0;

	err = blkdev_issue_discard(bdev, req->u.discard.sector_number,
				   req->u.discard.nr_sectors,
				   GFP_KERNEL, secure);
fail_response:
	अगर (err == -EOPNOTSUPP) अणु
		pr_debug("discard op failed, not supported\n");
		status = BLKIF_RSP_EOPNOTSUPP;
	पूर्ण अन्यथा अगर (err)
		status = BLKIF_RSP_ERROR;

	make_response(ring, req->u.discard.id, req->operation, status);
	xen_blkअगर_put(blkअगर);
	वापस err;
पूर्ण

अटल पूर्णांक dispatch_other_io(काष्ठा xen_blkअगर_ring *ring,
			     काष्ठा blkअगर_request *req,
			     काष्ठा pending_req *pending_req)
अणु
	मुक्त_req(ring, pending_req);
	make_response(ring, req->u.other.id, req->operation,
		      BLKIF_RSP_EOPNOTSUPP);
	वापस -EIO;
पूर्ण

अटल व्योम xen_blk_drain_io(काष्ठा xen_blkअगर_ring *ring)
अणु
	काष्ठा xen_blkअगर *blkअगर = ring->blkअगर;

	atomic_set(&blkअगर->drain, 1);
	करो अणु
		अगर (atomic_पढ़ो(&ring->inflight) == 0)
			अवरोध;
		रुको_क्रम_completion_पूर्णांकerruptible_समयout(
				&blkअगर->drain_complete, HZ);

		अगर (!atomic_पढ़ो(&blkअगर->drain))
			अवरोध;
	पूर्ण जबतक (!kthपढ़ो_should_stop());
	atomic_set(&blkअगर->drain, 0);
पूर्ण

अटल व्योम __end_block_io_op(काष्ठा pending_req *pending_req,
		blk_status_t error)
अणु
	/* An error fails the entire request. */
	अगर (pending_req->operation == BLKIF_OP_FLUSH_DISKCACHE &&
	    error == BLK_STS_NOTSUPP) अणु
		pr_debug("flush diskcache op failed, not supported\n");
		xen_blkbk_flush_diskcache(XBT_NIL, pending_req->ring->blkअगर->be, 0);
		pending_req->status = BLKIF_RSP_EOPNOTSUPP;
	पूर्ण अन्यथा अगर (pending_req->operation == BLKIF_OP_WRITE_BARRIER &&
		   error == BLK_STS_NOTSUPP) अणु
		pr_debug("write barrier op failed, not supported\n");
		xen_blkbk_barrier(XBT_NIL, pending_req->ring->blkअगर->be, 0);
		pending_req->status = BLKIF_RSP_EOPNOTSUPP;
	पूर्ण अन्यथा अगर (error) अणु
		pr_debug("Buffer not up-to-date at end of operation,"
			 " error=%d\n", error);
		pending_req->status = BLKIF_RSP_ERROR;
	पूर्ण

	/*
	 * If all of the bio's have completed it is समय to unmap
	 * the grant references associated with 'request' and provide
	 * the proper response on the ring.
	 */
	अगर (atomic_dec_and_test(&pending_req->pendcnt))
		xen_blkbk_unmap_and_respond(pending_req);
पूर्ण

/*
 * bio callback.
 */
अटल व्योम end_block_io_op(काष्ठा bio *bio)
अणु
	__end_block_io_op(bio->bi_निजी, bio->bi_status);
	bio_put(bio);
पूर्ण



/*
 * Function to copy the from the ring buffer the 'struct blkif_request'
 * (which has the sectors we want, number of them, grant references, etc),
 * and transmute  it to the block API to hand it over to the proper block disk.
 */
अटल पूर्णांक
__करो_block_io_op(काष्ठा xen_blkअगर_ring *ring, अचिन्हित पूर्णांक *eoi_flags)
अणु
	जोड़ blkअगर_back_rings *blk_rings = &ring->blk_rings;
	काष्ठा blkअगर_request req;
	काष्ठा pending_req *pending_req;
	RING_IDX rc, rp;
	पूर्णांक more_to_करो = 0;

	rc = blk_rings->common.req_cons;
	rp = blk_rings->common.sring->req_prod;
	rmb(); /* Ensure we see queued requests up to 'rp'. */

	अगर (RING_REQUEST_PROD_OVERFLOW(&blk_rings->common, rp)) अणु
		rc = blk_rings->common.rsp_prod_pvt;
		pr_warn("Frontend provided bogus ring requests (%d - %d = %d). Halting ring processing on dev=%04x\n",
			rp, rc, rp - rc, ring->blkअगर->vbd.pdevice);
		वापस -EACCES;
	पूर्ण
	जबतक (rc != rp) अणु

		अगर (RING_REQUEST_CONS_OVERFLOW(&blk_rings->common, rc))
			अवरोध;

		/* We've seen a request, so clear spurious eoi flag. */
		*eoi_flags &= ~XEN_EOI_FLAG_SPURIOUS;

		अगर (kthपढ़ो_should_stop()) अणु
			more_to_करो = 1;
			अवरोध;
		पूर्ण

		pending_req = alloc_req(ring);
		अगर (शून्य == pending_req) अणु
			ring->st_oo_req++;
			more_to_करो = 1;
			अवरोध;
		पूर्ण

		चयन (ring->blkअगर->blk_protocol) अणु
		हाल BLKIF_PROTOCOL_NATIVE:
			स_नकल(&req, RING_GET_REQUEST(&blk_rings->native, rc), माप(req));
			अवरोध;
		हाल BLKIF_PROTOCOL_X86_32:
			blkअगर_get_x86_32_req(&req, RING_GET_REQUEST(&blk_rings->x86_32, rc));
			अवरोध;
		हाल BLKIF_PROTOCOL_X86_64:
			blkअगर_get_x86_64_req(&req, RING_GET_REQUEST(&blk_rings->x86_64, rc));
			अवरोध;
		शेष:
			BUG();
		पूर्ण
		blk_rings->common.req_cons = ++rc; /* beक्रमe make_response() */

		/* Apply all sanity checks to /निजी copy/ of request. */
		barrier();

		चयन (req.operation) अणु
		हाल BLKIF_OP_READ:
		हाल BLKIF_OP_WRITE:
		हाल BLKIF_OP_WRITE_BARRIER:
		हाल BLKIF_OP_FLUSH_DISKCACHE:
		हाल BLKIF_OP_INसूचीECT:
			अगर (dispatch_rw_block_io(ring, &req, pending_req))
				जाओ करोne;
			अवरोध;
		हाल BLKIF_OP_DISCARD:
			मुक्त_req(ring, pending_req);
			अगर (dispatch_discard_io(ring, &req))
				जाओ करोne;
			अवरोध;
		शेष:
			अगर (dispatch_other_io(ring, &req, pending_req))
				जाओ करोne;
			अवरोध;
		पूर्ण

		/* Yield poपूर्णांक क्रम this unbounded loop. */
		cond_resched();
	पूर्ण
करोne:
	वापस more_to_करो;
पूर्ण

अटल पूर्णांक
करो_block_io_op(काष्ठा xen_blkअगर_ring *ring, अचिन्हित पूर्णांक *eoi_flags)
अणु
	जोड़ blkअगर_back_rings *blk_rings = &ring->blk_rings;
	पूर्णांक more_to_करो;

	करो अणु
		more_to_करो = __करो_block_io_op(ring, eoi_flags);
		अगर (more_to_करो)
			अवरोध;

		RING_FINAL_CHECK_FOR_REQUESTS(&blk_rings->common, more_to_करो);
	पूर्ण जबतक (more_to_करो);

	वापस more_to_करो;
पूर्ण
/*
 * Transmutation of the 'struct blkif_request' to a proper 'struct bio'
 * and call the 'submit_bio' to pass it to the underlying storage.
 */
अटल पूर्णांक dispatch_rw_block_io(काष्ठा xen_blkअगर_ring *ring,
				काष्ठा blkअगर_request *req,
				काष्ठा pending_req *pending_req)
अणु
	काष्ठा phys_req preq;
	काष्ठा seg_buf *seg = pending_req->seg;
	अचिन्हित पूर्णांक nseg;
	काष्ठा bio *bio = शून्य;
	काष्ठा bio **biolist = pending_req->biolist;
	पूर्णांक i, nbio = 0;
	पूर्णांक operation;
	पूर्णांक operation_flags = 0;
	काष्ठा blk_plug plug;
	bool drain = false;
	काष्ठा grant_page **pages = pending_req->segments;
	अचिन्हित लघु req_operation;

	req_operation = req->operation == BLKIF_OP_INसूचीECT ?
			req->u.indirect.indirect_op : req->operation;

	अगर ((req->operation == BLKIF_OP_INसूचीECT) &&
	    (req_operation != BLKIF_OP_READ) &&
	    (req_operation != BLKIF_OP_WRITE)) अणु
		pr_debug("Invalid indirect operation (%u)\n", req_operation);
		जाओ fail_response;
	पूर्ण

	चयन (req_operation) अणु
	हाल BLKIF_OP_READ:
		ring->st_rd_req++;
		operation = REQ_OP_READ;
		अवरोध;
	हाल BLKIF_OP_WRITE:
		ring->st_wr_req++;
		operation = REQ_OP_WRITE;
		operation_flags = REQ_SYNC | REQ_IDLE;
		अवरोध;
	हाल BLKIF_OP_WRITE_BARRIER:
		drain = true;
		fallthrough;
	हाल BLKIF_OP_FLUSH_DISKCACHE:
		ring->st_f_req++;
		operation = REQ_OP_WRITE;
		operation_flags = REQ_PREFLUSH;
		अवरोध;
	शेष:
		operation = 0; /* make gcc happy */
		जाओ fail_response;
		अवरोध;
	पूर्ण

	/* Check that the number of segments is sane. */
	nseg = req->operation == BLKIF_OP_INसूचीECT ?
	       req->u.indirect.nr_segments : req->u.rw.nr_segments;

	अगर (unlikely(nseg == 0 && operation_flags != REQ_PREFLUSH) ||
	    unlikely((req->operation != BLKIF_OP_INसूचीECT) &&
		     (nseg > BLKIF_MAX_SEGMENTS_PER_REQUEST)) ||
	    unlikely((req->operation == BLKIF_OP_INसूचीECT) &&
		     (nseg > MAX_INसूचीECT_SEGMENTS))) अणु
		pr_debug("Bad number of segments in request (%d)\n", nseg);
		/* Haven't submitted any bio's yet. */
		जाओ fail_response;
	पूर्ण

	preq.nr_sects      = 0;

	pending_req->ring      = ring;
	pending_req->id        = req->u.rw.id;
	pending_req->operation = req_operation;
	pending_req->status    = BLKIF_RSP_OKAY;
	pending_req->nr_segs   = nseg;

	अगर (req->operation != BLKIF_OP_INसूचीECT) अणु
		preq.dev               = req->u.rw.handle;
		preq.sector_number     = req->u.rw.sector_number;
		क्रम (i = 0; i < nseg; i++) अणु
			pages[i]->gref = req->u.rw.seg[i].gref;
			seg[i].nsec = req->u.rw.seg[i].last_sect -
				req->u.rw.seg[i].first_sect + 1;
			seg[i].offset = (req->u.rw.seg[i].first_sect << 9);
			अगर ((req->u.rw.seg[i].last_sect >= (XEN_PAGE_SIZE >> 9)) ||
			    (req->u.rw.seg[i].last_sect <
			     req->u.rw.seg[i].first_sect))
				जाओ fail_response;
			preq.nr_sects += seg[i].nsec;
		पूर्ण
	पूर्ण अन्यथा अणु
		preq.dev               = req->u.indirect.handle;
		preq.sector_number     = req->u.indirect.sector_number;
		अगर (xen_blkbk_parse_indirect(req, pending_req, seg, &preq))
			जाओ fail_response;
	पूर्ण

	अगर (xen_vbd_translate(&preq, ring->blkअगर, operation) != 0) अणु
		pr_debug("access denied: %s of [%llu,%llu] on dev=%04x\n",
			 operation == REQ_OP_READ ? "read" : "write",
			 preq.sector_number,
			 preq.sector_number + preq.nr_sects,
			 ring->blkअगर->vbd.pdevice);
		जाओ fail_response;
	पूर्ण

	/*
	 * This check _MUST_ be करोne after xen_vbd_translate as the preq.bdev
	 * is set there.
	 */
	क्रम (i = 0; i < nseg; i++) अणु
		अगर (((पूर्णांक)preq.sector_number|(पूर्णांक)seg[i].nsec) &
		    ((bdev_logical_block_size(preq.bdev) >> 9) - 1)) अणु
			pr_debug("Misaligned I/O request from domain %d\n",
				 ring->blkअगर->करोmid);
			जाओ fail_response;
		पूर्ण
	पूर्ण

	/* Wait on all outstanding I/O's and once that has been completed
	 * issue the flush.
	 */
	अगर (drain)
		xen_blk_drain_io(pending_req->ring);

	/*
	 * If we have failed at this poपूर्णांक, we need to unकरो the M2P override,
	 * set gnttab_set_unmap_op on all of the grant references and perक्रमm
	 * the hypercall to unmap the grants - that is all करोne in
	 * xen_blkbk_unmap.
	 */
	अगर (xen_blkbk_map_seg(pending_req))
		जाओ fail_flush;

	/*
	 * This corresponding xen_blkअगर_put is करोne in __end_block_io_op, or
	 * below (in "!bio") अगर we are handling a BLKIF_OP_DISCARD.
	 */
	xen_blkअगर_get(ring->blkअगर);
	atomic_inc(&ring->inflight);

	क्रम (i = 0; i < nseg; i++) अणु
		जबतक ((bio == शून्य) ||
		       (bio_add_page(bio,
				     pages[i]->page,
				     seg[i].nsec << 9,
				     seg[i].offset) == 0)) अणु
			bio = bio_alloc(GFP_KERNEL, bio_max_segs(nseg - i));
			अगर (unlikely(bio == शून्य))
				जाओ fail_put_bio;

			biolist[nbio++] = bio;
			bio_set_dev(bio, preq.bdev);
			bio->bi_निजी = pending_req;
			bio->bi_end_io  = end_block_io_op;
			bio->bi_iter.bi_sector  = preq.sector_number;
			bio_set_op_attrs(bio, operation, operation_flags);
		पूर्ण

		preq.sector_number += seg[i].nsec;
	पूर्ण

	/* This will be hit अगर the operation was a flush or discard. */
	अगर (!bio) अणु
		BUG_ON(operation_flags != REQ_PREFLUSH);

		bio = bio_alloc(GFP_KERNEL, 0);
		अगर (unlikely(bio == शून्य))
			जाओ fail_put_bio;

		biolist[nbio++] = bio;
		bio_set_dev(bio, preq.bdev);
		bio->bi_निजी = pending_req;
		bio->bi_end_io  = end_block_io_op;
		bio_set_op_attrs(bio, operation, operation_flags);
	पूर्ण

	atomic_set(&pending_req->pendcnt, nbio);
	blk_start_plug(&plug);

	क्रम (i = 0; i < nbio; i++)
		submit_bio(biolist[i]);

	/* Let the I/Os go.. */
	blk_finish_plug(&plug);

	अगर (operation == REQ_OP_READ)
		ring->st_rd_sect += preq.nr_sects;
	अन्यथा अगर (operation == REQ_OP_WRITE)
		ring->st_wr_sect += preq.nr_sects;

	वापस 0;

 fail_flush:
	xen_blkbk_unmap(ring, pending_req->segments,
	                pending_req->nr_segs);
 fail_response:
	/* Haven't submitted any bio's yet. */
	make_response(ring, req->u.rw.id, req_operation, BLKIF_RSP_ERROR);
	मुक्त_req(ring, pending_req);
	msleep(1); /* back off a bit */
	वापस -EIO;

 fail_put_bio:
	क्रम (i = 0; i < nbio; i++)
		bio_put(biolist[i]);
	atomic_set(&pending_req->pendcnt, 1);
	__end_block_io_op(pending_req, BLK_STS_RESOURCE);
	msleep(1); /* back off a bit */
	वापस -EIO;
पूर्ण



/*
 * Put a response on the ring on how the operation fared.
 */
अटल व्योम make_response(काष्ठा xen_blkअगर_ring *ring, u64 id,
			  अचिन्हित लघु op, पूर्णांक st)
अणु
	काष्ठा blkअगर_response *resp;
	अचिन्हित दीर्घ     flags;
	जोड़ blkअगर_back_rings *blk_rings;
	पूर्णांक notअगरy;

	spin_lock_irqsave(&ring->blk_ring_lock, flags);
	blk_rings = &ring->blk_rings;
	/* Place on the response ring क्रम the relevant करोमुख्य. */
	चयन (ring->blkअगर->blk_protocol) अणु
	हाल BLKIF_PROTOCOL_NATIVE:
		resp = RING_GET_RESPONSE(&blk_rings->native,
					 blk_rings->native.rsp_prod_pvt);
		अवरोध;
	हाल BLKIF_PROTOCOL_X86_32:
		resp = RING_GET_RESPONSE(&blk_rings->x86_32,
					 blk_rings->x86_32.rsp_prod_pvt);
		अवरोध;
	हाल BLKIF_PROTOCOL_X86_64:
		resp = RING_GET_RESPONSE(&blk_rings->x86_64,
					 blk_rings->x86_64.rsp_prod_pvt);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	resp->id        = id;
	resp->operation = op;
	resp->status    = st;

	blk_rings->common.rsp_prod_pvt++;
	RING_PUSH_RESPONSES_AND_CHECK_NOTIFY(&blk_rings->common, notअगरy);
	spin_unlock_irqrestore(&ring->blk_ring_lock, flags);
	अगर (notअगरy)
		notअगरy_remote_via_irq(ring->irq);
पूर्ण

अटल पूर्णांक __init xen_blkअगर_init(व्योम)
अणु
	पूर्णांक rc = 0;

	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	अगर (xen_blkअगर_max_ring_order > XENBUS_MAX_RING_GRANT_ORDER) अणु
		pr_info("Invalid max_ring_order (%d), will use default max: %d.\n",
			xen_blkअगर_max_ring_order, XENBUS_MAX_RING_GRANT_ORDER);
		xen_blkअगर_max_ring_order = XENBUS_MAX_RING_GRANT_ORDER;
	पूर्ण

	अगर (xenblk_max_queues == 0)
		xenblk_max_queues = num_online_cpus();

	rc = xen_blkअगर_पूर्णांकerface_init();
	अगर (rc)
		जाओ failed_init;

	rc = xen_blkअगर_xenbus_init();
	अगर (rc)
		जाओ failed_init;

 failed_init:
	वापस rc;
पूर्ण

module_init(xen_blkअगर_init);

अटल व्योम __निकास xen_blkअगर_fini(व्योम)
अणु
	xen_blkअगर_xenbus_fini();
	xen_blkअगर_पूर्णांकerface_fini();
पूर्ण

module_निकास(xen_blkअगर_fini);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_ALIAS("xen-backend:vbd");
