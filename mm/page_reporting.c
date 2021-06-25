<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/mm.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/page_reporting.h>
#समावेश <linux/gfp.h>
#समावेश <linux/export.h>
#समावेश <linux/delay.h>
#समावेश <linux/scatterlist.h>

#समावेश "page_reporting.h"
#समावेश "internal.h"

#घोषणा PAGE_REPORTING_DELAY	(2 * HZ)
अटल काष्ठा page_reporting_dev_info __rcu *pr_dev_info __पढ़ो_mostly;

क्रमागत अणु
	PAGE_REPORTING_IDLE = 0,
	PAGE_REPORTING_REQUESTED,
	PAGE_REPORTING_ACTIVE
पूर्ण;

/* request page reporting */
अटल व्योम
__page_reporting_request(काष्ठा page_reporting_dev_info *prdev)
अणु
	अचिन्हित पूर्णांक state;

	/* Check to see अगर we are in desired state */
	state = atomic_पढ़ो(&prdev->state);
	अगर (state == PAGE_REPORTING_REQUESTED)
		वापस;

	/*
	 *  If reporting is alपढ़ोy active there is nothing we need to करो.
	 *  Test against 0 as that represents PAGE_REPORTING_IDLE.
	 */
	state = atomic_xchg(&prdev->state, PAGE_REPORTING_REQUESTED);
	अगर (state != PAGE_REPORTING_IDLE)
		वापस;

	/*
	 * Delay the start of work to allow a sizable queue to build. For
	 * now we are limiting this to running no more than once every
	 * couple of seconds.
	 */
	schedule_delayed_work(&prdev->work, PAGE_REPORTING_DELAY);
पूर्ण

/* notअगरy prdev of मुक्त page reporting request */
व्योम __page_reporting_notअगरy(व्योम)
अणु
	काष्ठा page_reporting_dev_info *prdev;

	/*
	 * We use RCU to protect the pr_dev_info poपूर्णांकer. In almost all
	 * हालs this should be present, however in the unlikely हाल of
	 * a shutकरोwn this will be शून्य and we should निकास.
	 */
	rcu_पढ़ो_lock();
	prdev = rcu_dereference(pr_dev_info);
	अगर (likely(prdev))
		__page_reporting_request(prdev);

	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम
page_reporting_drain(काष्ठा page_reporting_dev_info *prdev,
		     काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक nents, bool reported)
अणु
	काष्ठा scatterlist *sg = sgl;

	/*
	 * Drain the now reported pages back पूर्णांकo their respective
	 * मुक्त lists/areas. We assume at least one page is populated.
	 */
	करो अणु
		काष्ठा page *page = sg_page(sg);
		पूर्णांक mt = get_pageblock_migratetype(page);
		अचिन्हित पूर्णांक order = get_order(sg->length);

		__putback_isolated_page(page, order, mt);

		/* If the pages were not reported due to error skip flagging */
		अगर (!reported)
			जारी;

		/*
		 * If page was not comingled with another page we can
		 * consider the result to be "reported" since the page
		 * hasn't been modअगरied, otherwise we will need to
		 * report on the new larger page when we make our way
		 * up to that higher order.
		 */
		अगर (PageBuddy(page) && buddy_order(page) == order)
			__SetPageReported(page);
	पूर्ण जबतक ((sg = sg_next(sg)));

	/* reinitialize scatterlist now that it is empty */
	sg_init_table(sgl, nents);
पूर्ण

/*
 * The page reporting cycle consists of 4 stages, fill, report, drain, and
 * idle. We will cycle through the first 3 stages until we cannot obtain a
 * full scatterlist of pages, in that हाल we will चयन to idle.
 */
अटल पूर्णांक
page_reporting_cycle(काष्ठा page_reporting_dev_info *prdev, काष्ठा zone *zone,
		     अचिन्हित पूर्णांक order, अचिन्हित पूर्णांक mt,
		     काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक *offset)
अणु
	काष्ठा मुक्त_area *area = &zone->मुक्त_area[order];
	काष्ठा list_head *list = &area->मुक्त_list[mt];
	अचिन्हित पूर्णांक page_len = PAGE_SIZE << order;
	काष्ठा page *page, *next;
	दीर्घ budget;
	पूर्णांक err = 0;

	/*
	 * Perक्रमm early check, अगर मुक्त area is empty there is
	 * nothing to process so we can skip this मुक्त_list.
	 */
	अगर (list_empty(list))
		वापस err;

	spin_lock_irq(&zone->lock);

	/*
	 * Limit how many calls we will be making to the page reporting
	 * device क्रम this list. By करोing this we aव्योम processing any
	 * given list क्रम too दीर्घ.
	 *
	 * The current value used allows us enough calls to process over a
	 * sixteenth of the current list plus one additional call to handle
	 * any pages that may have alपढ़ोy been present from the previous
	 * list processed. This should result in us reporting all pages on
	 * an idle प्रणाली in about 30 seconds.
	 *
	 * The भागision here should be cheap since PAGE_REPORTING_CAPACITY
	 * should always be a घातer of 2.
	 */
	budget = DIV_ROUND_UP(area->nr_मुक्त, PAGE_REPORTING_CAPACITY * 16);

	/* loop through मुक्त list adding unreported pages to sg list */
	list_क्रम_each_entry_safe(page, next, list, lru) अणु
		/* We are going to skip over the reported pages. */
		अगर (PageReported(page))
			जारी;

		/*
		 * If we fully consumed our budget then update our
		 * state to indicate that we are requesting additional
		 * processing and निकास this list.
		 */
		अगर (budget < 0) अणु
			atomic_set(&prdev->state, PAGE_REPORTING_REQUESTED);
			next = page;
			अवरोध;
		पूर्ण

		/* Attempt to pull page from list and place in scatterlist */
		अगर (*offset) अणु
			अगर (!__isolate_मुक्त_page(page, order)) अणु
				next = page;
				अवरोध;
			पूर्ण

			/* Add page to scatter list */
			--(*offset);
			sg_set_page(&sgl[*offset], page, page_len, 0);

			जारी;
		पूर्ण

		/*
		 * Make the first non-reported page in the मुक्त list
		 * the new head of the मुक्त list beक्रमe we release the
		 * zone lock.
		 */
		अगर (!list_is_first(&page->lru, list))
			list_rotate_to_front(&page->lru, list);

		/* release lock beक्रमe रुकोing on report processing */
		spin_unlock_irq(&zone->lock);

		/* begin processing pages in local list */
		err = prdev->report(prdev, sgl, PAGE_REPORTING_CAPACITY);

		/* reset offset since the full list was reported */
		*offset = PAGE_REPORTING_CAPACITY;

		/* update budget to reflect call to report function */
		budget--;

		/* reacquire zone lock and resume processing */
		spin_lock_irq(&zone->lock);

		/* flush reported pages from the sg list */
		page_reporting_drain(prdev, sgl, PAGE_REPORTING_CAPACITY, !err);

		/*
		 * Reset next to first entry, the old next isn't valid
		 * since we dropped the lock to report the pages
		 */
		next = list_first_entry(list, काष्ठा page, lru);

		/* निकास on error */
		अगर (err)
			अवरोध;
	पूर्ण

	/* Rotate any leftover pages to the head of the मुक्तlist */
	अगर (!list_entry_is_head(next, list, lru) && !list_is_first(&next->lru, list))
		list_rotate_to_front(&next->lru, list);

	spin_unlock_irq(&zone->lock);

	वापस err;
पूर्ण

अटल पूर्णांक
page_reporting_process_zone(काष्ठा page_reporting_dev_info *prdev,
			    काष्ठा scatterlist *sgl, काष्ठा zone *zone)
अणु
	अचिन्हित पूर्णांक order, mt, leftover, offset = PAGE_REPORTING_CAPACITY;
	अचिन्हित दीर्घ watermark;
	पूर्णांक err = 0;

	/* Generate minimum watermark to be able to guarantee progress */
	watermark = low_wmark_pages(zone) +
		    (PAGE_REPORTING_CAPACITY << PAGE_REPORTING_MIN_ORDER);

	/*
	 * Cancel request अगर insufficient मुक्त memory or अगर we failed
	 * to allocate page reporting statistics क्रम the zone.
	 */
	अगर (!zone_watermark_ok(zone, 0, watermark, 0, ALLOC_CMA))
		वापस err;

	/* Process each मुक्त list starting from lowest order/mt */
	क्रम (order = PAGE_REPORTING_MIN_ORDER; order < MAX_ORDER; order++) अणु
		क्रम (mt = 0; mt < MIGRATE_TYPES; mt++) अणु
			/* We करो not pull pages from the isolate मुक्त list */
			अगर (is_migrate_isolate(mt))
				जारी;

			err = page_reporting_cycle(prdev, zone, order, mt,
						   sgl, &offset);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	/* report the leftover pages beक्रमe going idle */
	leftover = PAGE_REPORTING_CAPACITY - offset;
	अगर (leftover) अणु
		sgl = &sgl[offset];
		err = prdev->report(prdev, sgl, leftover);

		/* flush any reमुख्यing pages out from the last report */
		spin_lock_irq(&zone->lock);
		page_reporting_drain(prdev, sgl, leftover, !err);
		spin_unlock_irq(&zone->lock);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम page_reporting_process(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *d_work = to_delayed_work(work);
	काष्ठा page_reporting_dev_info *prdev =
		container_of(d_work, काष्ठा page_reporting_dev_info, work);
	पूर्णांक err = 0, state = PAGE_REPORTING_ACTIVE;
	काष्ठा scatterlist *sgl;
	काष्ठा zone *zone;

	/*
	 * Change the state to "Active" so that we can track अगर there is
	 * anyone requests page reporting after we complete our pass. If
	 * the state is not altered by the end of the pass we will चयन
	 * to idle and quit scheduling reporting runs.
	 */
	atomic_set(&prdev->state, state);

	/* allocate scatterlist to store pages being reported on */
	sgl = kदो_स्मृति_array(PAGE_REPORTING_CAPACITY, माप(*sgl), GFP_KERNEL);
	अगर (!sgl)
		जाओ err_out;

	sg_init_table(sgl, PAGE_REPORTING_CAPACITY);

	क्रम_each_zone(zone) अणु
		err = page_reporting_process_zone(prdev, sgl, zone);
		अगर (err)
			अवरोध;
	पूर्ण

	kमुक्त(sgl);
err_out:
	/*
	 * If the state has reverted back to requested then there may be
	 * additional pages to be processed. We will defer क्रम 2s to allow
	 * more pages to accumulate.
	 */
	state = atomic_cmpxchg(&prdev->state, state, PAGE_REPORTING_IDLE);
	अगर (state == PAGE_REPORTING_REQUESTED)
		schedule_delayed_work(&prdev->work, PAGE_REPORTING_DELAY);
पूर्ण

अटल DEFINE_MUTEX(page_reporting_mutex);
DEFINE_STATIC_KEY_FALSE(page_reporting_enabled);

पूर्णांक page_reporting_रेजिस्टर(काष्ठा page_reporting_dev_info *prdev)
अणु
	पूर्णांक err = 0;

	mutex_lock(&page_reporting_mutex);

	/* nothing to करो अगर alपढ़ोy in use */
	अगर (rcu_access_poपूर्णांकer(pr_dev_info)) अणु
		err = -EBUSY;
		जाओ err_out;
	पूर्ण

	/* initialize state and work काष्ठाures */
	atomic_set(&prdev->state, PAGE_REPORTING_IDLE);
	INIT_DELAYED_WORK(&prdev->work, &page_reporting_process);

	/* Begin initial flush of zones */
	__page_reporting_request(prdev);

	/* Assign device to allow notअगरications */
	rcu_assign_poपूर्णांकer(pr_dev_info, prdev);

	/* enable page reporting notअगरication */
	अगर (!अटल_key_enabled(&page_reporting_enabled)) अणु
		अटल_branch_enable(&page_reporting_enabled);
		pr_info("Free page reporting enabled\n");
	पूर्ण
err_out:
	mutex_unlock(&page_reporting_mutex);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(page_reporting_रेजिस्टर);

व्योम page_reporting_unरेजिस्टर(काष्ठा page_reporting_dev_info *prdev)
अणु
	mutex_lock(&page_reporting_mutex);

	अगर (rcu_access_poपूर्णांकer(pr_dev_info) == prdev) अणु
		/* Disable page reporting notअगरication */
		RCU_INIT_POINTER(pr_dev_info, शून्य);
		synchronize_rcu();

		/* Flush any existing work, and lock it out */
		cancel_delayed_work_sync(&prdev->work);
	पूर्ण

	mutex_unlock(&page_reporting_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(page_reporting_unरेजिस्टर);
