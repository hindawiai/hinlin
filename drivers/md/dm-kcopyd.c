<शैली गुरु>
/*
 * Copyright (C) 2002 Sistina Software (UK) Limited.
 * Copyright (C) 2006 Red Hat GmbH
 *
 * This file is released under the GPL.
 *
 * Kcopyd provides a simple पूर्णांकerface क्रम copying an area of one
 * block-device to one or more other block-devices, with an asynchronous
 * completion notअगरication.
 */

#समावेश <linux/types.h>
#समावेश <linux/atomic.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/mempool.h>
#समावेश <linux/module.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/device-mapper.h>
#समावेश <linux/dm-kcopyd.h>

#समावेश "dm-core.h"

#घोषणा SPLIT_COUNT	8
#घोषणा MIN_JOBS	8

#घोषणा DEFAULT_SUB_JOB_SIZE_KB 512
#घोषणा MAX_SUB_JOB_SIZE_KB     1024

अटल अचिन्हित kcopyd_subjob_size_kb = DEFAULT_SUB_JOB_SIZE_KB;

module_param(kcopyd_subjob_size_kb, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(kcopyd_subjob_size_kb, "Sub-job size for dm-kcopyd clients");

अटल अचिन्हित dm_get_kcopyd_subjob_size(व्योम)
अणु
	अचिन्हित sub_job_size_kb;

	sub_job_size_kb = __dm_get_module_param(&kcopyd_subjob_size_kb,
						DEFAULT_SUB_JOB_SIZE_KB,
						MAX_SUB_JOB_SIZE_KB);

	वापस sub_job_size_kb << 1;
पूर्ण

/*-----------------------------------------------------------------
 * Each kcopyd client has its own little pool of pपुनः_स्मृतिated
 * pages क्रम kcopyd io.
 *---------------------------------------------------------------*/
काष्ठा dm_kcopyd_client अणु
	काष्ठा page_list *pages;
	अचिन्हित nr_reserved_pages;
	अचिन्हित nr_मुक्त_pages;
	अचिन्हित sub_job_size;

	काष्ठा dm_io_client *io_client;

	रुको_queue_head_t destroyq;

	mempool_t job_pool;

	काष्ठा workqueue_काष्ठा *kcopyd_wq;
	काष्ठा work_काष्ठा kcopyd_work;

	काष्ठा dm_kcopyd_throttle *throttle;

	atomic_t nr_jobs;

/*
 * We मुख्यtain four lists of jobs:
 *
 * i)   jobs रुकोing क्रम pages
 * ii)  jobs that have pages, and are रुकोing क्रम the io to be issued.
 * iii) jobs that करोn't need to करो any IO and just run a callback
 * iv) jobs that have completed.
 *
 * All four of these are रक्षित by job_lock.
 */
	spinlock_t job_lock;
	काष्ठा list_head callback_jobs;
	काष्ठा list_head complete_jobs;
	काष्ठा list_head io_jobs;
	काष्ठा list_head pages_jobs;
पूर्ण;

अटल काष्ठा page_list zero_page_list;

अटल DEFINE_SPINLOCK(throttle_spinlock);

/*
 * IO/IDLE accounting slowly decays after (1 << ACCOUNT_INTERVAL_SHIFT) period.
 * When total_period >= (1 << ACCOUNT_INTERVAL_SHIFT) the counters are भागided
 * by 2.
 */
#घोषणा ACCOUNT_INTERVAL_SHIFT		SHIFT_HZ

/*
 * Sleep this number of milliseconds.
 *
 * The value was decided experimentally.
 * Smaller values seem to cause an increased copy rate above the limit.
 * The reason क्रम this is unknown but possibly due to jअगरfies rounding errors
 * or पढ़ो/ग_लिखो cache inside the disk.
 */
#घोषणा SLEEP_MSEC			100

/*
 * Maximum number of sleep events. There is a theoretical livelock अगर more
 * kcopyd clients करो work simultaneously which this limit aव्योमs.
 */
#घोषणा MAX_SLEEPS			10

अटल व्योम io_job_start(काष्ठा dm_kcopyd_throttle *t)
अणु
	अचिन्हित throttle, now, dअगरference;
	पूर्णांक slept = 0, skew;

	अगर (unlikely(!t))
		वापस;

try_again:
	spin_lock_irq(&throttle_spinlock);

	throttle = READ_ONCE(t->throttle);

	अगर (likely(throttle >= 100))
		जाओ skip_limit;

	now = jअगरfies;
	dअगरference = now - t->last_jअगरfies;
	t->last_jअगरfies = now;
	अगर (t->num_io_jobs)
		t->io_period += dअगरference;
	t->total_period += dअगरference;

	/*
	 * Maपूर्णांकain sane values अगर we got a temporary overflow.
	 */
	अगर (unlikely(t->io_period > t->total_period))
		t->io_period = t->total_period;

	अगर (unlikely(t->total_period >= (1 << ACCOUNT_INTERVAL_SHIFT))) अणु
		पूर्णांक shअगरt = fls(t->total_period >> ACCOUNT_INTERVAL_SHIFT);
		t->total_period >>= shअगरt;
		t->io_period >>= shअगरt;
	पूर्ण

	skew = t->io_period - throttle * t->total_period / 100;

	अगर (unlikely(skew > 0) && slept < MAX_SLEEPS) अणु
		slept++;
		spin_unlock_irq(&throttle_spinlock);
		msleep(SLEEP_MSEC);
		जाओ try_again;
	पूर्ण

skip_limit:
	t->num_io_jobs++;

	spin_unlock_irq(&throttle_spinlock);
पूर्ण

अटल व्योम io_job_finish(काष्ठा dm_kcopyd_throttle *t)
अणु
	अचिन्हित दीर्घ flags;

	अगर (unlikely(!t))
		वापस;

	spin_lock_irqsave(&throttle_spinlock, flags);

	t->num_io_jobs--;

	अगर (likely(READ_ONCE(t->throttle) >= 100))
		जाओ skip_limit;

	अगर (!t->num_io_jobs) अणु
		अचिन्हित now, dअगरference;

		now = jअगरfies;
		dअगरference = now - t->last_jअगरfies;
		t->last_jअगरfies = now;

		t->io_period += dअगरference;
		t->total_period += dअगरference;

		/*
		 * Maपूर्णांकain sane values अगर we got a temporary overflow.
		 */
		अगर (unlikely(t->io_period > t->total_period))
			t->io_period = t->total_period;
	पूर्ण

skip_limit:
	spin_unlock_irqrestore(&throttle_spinlock, flags);
पूर्ण


अटल व्योम wake(काष्ठा dm_kcopyd_client *kc)
अणु
	queue_work(kc->kcopyd_wq, &kc->kcopyd_work);
पूर्ण

/*
 * Obtain one page क्रम the use of kcopyd.
 */
अटल काष्ठा page_list *alloc_pl(gfp_t gfp)
अणु
	काष्ठा page_list *pl;

	pl = kदो_स्मृति(माप(*pl), gfp);
	अगर (!pl)
		वापस शून्य;

	pl->page = alloc_page(gfp);
	अगर (!pl->page) अणु
		kमुक्त(pl);
		वापस शून्य;
	पूर्ण

	वापस pl;
पूर्ण

अटल व्योम मुक्त_pl(काष्ठा page_list *pl)
अणु
	__मुक्त_page(pl->page);
	kमुक्त(pl);
पूर्ण

/*
 * Add the provided pages to a client's मुक्त page list, releasing
 * back to the प्रणाली any beyond the reserved_pages limit.
 */
अटल व्योम kcopyd_put_pages(काष्ठा dm_kcopyd_client *kc, काष्ठा page_list *pl)
अणु
	काष्ठा page_list *next;

	करो अणु
		next = pl->next;

		अगर (kc->nr_मुक्त_pages >= kc->nr_reserved_pages)
			मुक्त_pl(pl);
		अन्यथा अणु
			pl->next = kc->pages;
			kc->pages = pl;
			kc->nr_मुक्त_pages++;
		पूर्ण

		pl = next;
	पूर्ण जबतक (pl);
पूर्ण

अटल पूर्णांक kcopyd_get_pages(काष्ठा dm_kcopyd_client *kc,
			    अचिन्हित पूर्णांक nr, काष्ठा page_list **pages)
अणु
	काष्ठा page_list *pl;

	*pages = शून्य;

	करो अणु
		pl = alloc_pl(__GFP_NOWARN | __GFP_NORETRY | __GFP_KSWAPD_RECLAIM);
		अगर (unlikely(!pl)) अणु
			/* Use reserved pages */
			pl = kc->pages;
			अगर (unlikely(!pl))
				जाओ out_of_memory;
			kc->pages = pl->next;
			kc->nr_मुक्त_pages--;
		पूर्ण
		pl->next = *pages;
		*pages = pl;
	पूर्ण जबतक (--nr);

	वापस 0;

out_of_memory:
	अगर (*pages)
		kcopyd_put_pages(kc, *pages);
	वापस -ENOMEM;
पूर्ण

/*
 * These three functions resize the page pool.
 */
अटल व्योम drop_pages(काष्ठा page_list *pl)
अणु
	काष्ठा page_list *next;

	जबतक (pl) अणु
		next = pl->next;
		मुक्त_pl(pl);
		pl = next;
	पूर्ण
पूर्ण

/*
 * Allocate and reserve nr_pages क्रम the use of a specअगरic client.
 */
अटल पूर्णांक client_reserve_pages(काष्ठा dm_kcopyd_client *kc, अचिन्हित nr_pages)
अणु
	अचिन्हित i;
	काष्ठा page_list *pl = शून्य, *next;

	क्रम (i = 0; i < nr_pages; i++) अणु
		next = alloc_pl(GFP_KERNEL);
		अगर (!next) अणु
			अगर (pl)
				drop_pages(pl);
			वापस -ENOMEM;
		पूर्ण
		next->next = pl;
		pl = next;
	पूर्ण

	kc->nr_reserved_pages += nr_pages;
	kcopyd_put_pages(kc, pl);

	वापस 0;
पूर्ण

अटल व्योम client_मुक्त_pages(काष्ठा dm_kcopyd_client *kc)
अणु
	BUG_ON(kc->nr_मुक्त_pages != kc->nr_reserved_pages);
	drop_pages(kc->pages);
	kc->pages = शून्य;
	kc->nr_मुक्त_pages = kc->nr_reserved_pages = 0;
पूर्ण

/*-----------------------------------------------------------------
 * kcopyd_jobs need to be allocated by the *clients* of kcopyd,
 * क्रम this reason we use a mempool to prevent the client from
 * ever having to करो io (which could cause a deadlock).
 *---------------------------------------------------------------*/
काष्ठा kcopyd_job अणु
	काष्ठा dm_kcopyd_client *kc;
	काष्ठा list_head list;
	अचिन्हित दीर्घ flags;

	/*
	 * Error state of the job.
	 */
	पूर्णांक पढ़ो_err;
	अचिन्हित दीर्घ ग_लिखो_err;

	/*
	 * Either READ or WRITE
	 */
	पूर्णांक rw;
	काष्ठा dm_io_region source;

	/*
	 * The destinations क्रम the transfer.
	 */
	अचिन्हित पूर्णांक num_dests;
	काष्ठा dm_io_region dests[DM_KCOPYD_MAX_REGIONS];

	काष्ठा page_list *pages;

	/*
	 * Set this to ensure you are notअगरied when the job has
	 * completed.  'context' is क्रम callback to use.
	 */
	dm_kcopyd_notअगरy_fn fn;
	व्योम *context;

	/*
	 * These fields are only used अगर the job has been split
	 * पूर्णांकo more manageable parts.
	 */
	काष्ठा mutex lock;
	atomic_t sub_jobs;
	sector_t progress;
	sector_t ग_लिखो_offset;

	काष्ठा kcopyd_job *master_job;
पूर्ण;

अटल काष्ठा kmem_cache *_job_cache;

पूर्णांक __init dm_kcopyd_init(व्योम)
अणु
	_job_cache = kmem_cache_create("kcopyd_job",
				माप(काष्ठा kcopyd_job) * (SPLIT_COUNT + 1),
				__alignof__(काष्ठा kcopyd_job), 0, शून्य);
	अगर (!_job_cache)
		वापस -ENOMEM;

	zero_page_list.next = &zero_page_list;
	zero_page_list.page = ZERO_PAGE(0);

	वापस 0;
पूर्ण

व्योम dm_kcopyd_निकास(व्योम)
अणु
	kmem_cache_destroy(_job_cache);
	_job_cache = शून्य;
पूर्ण

/*
 * Functions to push and pop a job onto the head of a given job
 * list.
 */
अटल काष्ठा kcopyd_job *pop_io_job(काष्ठा list_head *jobs,
				     काष्ठा dm_kcopyd_client *kc)
अणु
	काष्ठा kcopyd_job *job;

	/*
	 * For I/O jobs, pop any पढ़ो, any ग_लिखो without sequential ग_लिखो
	 * स्थिरraपूर्णांक and sequential ग_लिखोs that are at the right position.
	 */
	list_क्रम_each_entry(job, jobs, list) अणु
		अगर (job->rw == READ || !test_bit(DM_KCOPYD_WRITE_SEQ, &job->flags)) अणु
			list_del(&job->list);
			वापस job;
		पूर्ण

		अगर (job->ग_लिखो_offset == job->master_job->ग_लिखो_offset) अणु
			job->master_job->ग_लिखो_offset += job->source.count;
			list_del(&job->list);
			वापस job;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा kcopyd_job *pop(काष्ठा list_head *jobs,
			      काष्ठा dm_kcopyd_client *kc)
अणु
	काष्ठा kcopyd_job *job = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&kc->job_lock, flags);

	अगर (!list_empty(jobs)) अणु
		अगर (jobs == &kc->io_jobs)
			job = pop_io_job(jobs, kc);
		अन्यथा अणु
			job = list_entry(jobs->next, काष्ठा kcopyd_job, list);
			list_del(&job->list);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&kc->job_lock, flags);

	वापस job;
पूर्ण

अटल व्योम push(काष्ठा list_head *jobs, काष्ठा kcopyd_job *job)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा dm_kcopyd_client *kc = job->kc;

	spin_lock_irqsave(&kc->job_lock, flags);
	list_add_tail(&job->list, jobs);
	spin_unlock_irqrestore(&kc->job_lock, flags);
पूर्ण


अटल व्योम push_head(काष्ठा list_head *jobs, काष्ठा kcopyd_job *job)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा dm_kcopyd_client *kc = job->kc;

	spin_lock_irqsave(&kc->job_lock, flags);
	list_add(&job->list, jobs);
	spin_unlock_irqrestore(&kc->job_lock, flags);
पूर्ण

/*
 * These three functions process 1 item from the corresponding
 * job list.
 *
 * They वापस:
 * < 0: error
 *   0: success
 * > 0: can't process yet.
 */
अटल पूर्णांक run_complete_job(काष्ठा kcopyd_job *job)
अणु
	व्योम *context = job->context;
	पूर्णांक पढ़ो_err = job->पढ़ो_err;
	अचिन्हित दीर्घ ग_लिखो_err = job->ग_लिखो_err;
	dm_kcopyd_notअगरy_fn fn = job->fn;
	काष्ठा dm_kcopyd_client *kc = job->kc;

	अगर (job->pages && job->pages != &zero_page_list)
		kcopyd_put_pages(kc, job->pages);
	/*
	 * If this is the master job, the sub jobs have alपढ़ोy
	 * completed so we can मुक्त everything.
	 */
	अगर (job->master_job == job) अणु
		mutex_destroy(&job->lock);
		mempool_मुक्त(job, &kc->job_pool);
	पूर्ण
	fn(पढ़ो_err, ग_लिखो_err, context);

	अगर (atomic_dec_and_test(&kc->nr_jobs))
		wake_up(&kc->destroyq);

	cond_resched();

	वापस 0;
पूर्ण

अटल व्योम complete_io(अचिन्हित दीर्घ error, व्योम *context)
अणु
	काष्ठा kcopyd_job *job = (काष्ठा kcopyd_job *) context;
	काष्ठा dm_kcopyd_client *kc = job->kc;

	io_job_finish(kc->throttle);

	अगर (error) अणु
		अगर (op_is_ग_लिखो(job->rw))
			job->ग_लिखो_err |= error;
		अन्यथा
			job->पढ़ो_err = 1;

		अगर (!test_bit(DM_KCOPYD_IGNORE_ERROR, &job->flags)) अणु
			push(&kc->complete_jobs, job);
			wake(kc);
			वापस;
		पूर्ण
	पूर्ण

	अगर (op_is_ग_लिखो(job->rw))
		push(&kc->complete_jobs, job);

	अन्यथा अणु
		job->rw = WRITE;
		push(&kc->io_jobs, job);
	पूर्ण

	wake(kc);
पूर्ण

/*
 * Request io on as many buffer heads as we can currently get क्रम
 * a particular job.
 */
अटल पूर्णांक run_io_job(काष्ठा kcopyd_job *job)
अणु
	पूर्णांक r;
	काष्ठा dm_io_request io_req = अणु
		.bi_op = job->rw,
		.bi_op_flags = 0,
		.mem.type = DM_IO_PAGE_LIST,
		.mem.ptr.pl = job->pages,
		.mem.offset = 0,
		.notअगरy.fn = complete_io,
		.notअगरy.context = job,
		.client = job->kc->io_client,
	पूर्ण;

	/*
	 * If we need to ग_लिखो sequentially and some पढ़ोs or ग_लिखोs failed,
	 * no poपूर्णांक in continuing.
	 */
	अगर (test_bit(DM_KCOPYD_WRITE_SEQ, &job->flags) &&
	    job->master_job->ग_लिखो_err) अणु
		job->ग_लिखो_err = job->master_job->ग_लिखो_err;
		वापस -EIO;
	पूर्ण

	io_job_start(job->kc->throttle);

	अगर (job->rw == READ)
		r = dm_io(&io_req, 1, &job->source, शून्य);
	अन्यथा
		r = dm_io(&io_req, job->num_dests, job->dests, शून्य);

	वापस r;
पूर्ण

अटल पूर्णांक run_pages_job(काष्ठा kcopyd_job *job)
अणु
	पूर्णांक r;
	अचिन्हित nr_pages = dm_भाग_up(job->dests[0].count, PAGE_SIZE >> 9);

	r = kcopyd_get_pages(job->kc, nr_pages, &job->pages);
	अगर (!r) अणु
		/* this job is पढ़ोy क्रम io */
		push(&job->kc->io_jobs, job);
		वापस 0;
	पूर्ण

	अगर (r == -ENOMEM)
		/* can't complete now */
		वापस 1;

	वापस r;
पूर्ण

/*
 * Run through a list क्रम as दीर्घ as possible.  Returns the count
 * of successful jobs.
 */
अटल पूर्णांक process_jobs(काष्ठा list_head *jobs, काष्ठा dm_kcopyd_client *kc,
			पूर्णांक (*fn) (काष्ठा kcopyd_job *))
अणु
	काष्ठा kcopyd_job *job;
	पूर्णांक r, count = 0;

	जबतक ((job = pop(jobs, kc))) अणु

		r = fn(job);

		अगर (r < 0) अणु
			/* error this rogue job */
			अगर (op_is_ग_लिखो(job->rw))
				job->ग_लिखो_err = (अचिन्हित दीर्घ) -1L;
			अन्यथा
				job->पढ़ो_err = 1;
			push(&kc->complete_jobs, job);
			wake(kc);
			अवरोध;
		पूर्ण

		अगर (r > 0) अणु
			/*
			 * We couldn't service this job ATM, so
			 * push this job back onto the list.
			 */
			push_head(jobs, job);
			अवरोध;
		पूर्ण

		count++;
	पूर्ण

	वापस count;
पूर्ण

/*
 * kcopyd करोes this every समय it's woken up.
 */
अटल व्योम करो_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dm_kcopyd_client *kc = container_of(work,
					काष्ठा dm_kcopyd_client, kcopyd_work);
	काष्ठा blk_plug plug;
	अचिन्हित दीर्घ flags;

	/*
	 * The order that these are called is *very* important.
	 * complete jobs can मुक्त some pages क्रम pages jobs.
	 * Pages jobs when successful will jump onto the io jobs
	 * list.  io jobs call wake when they complete and it all
	 * starts again.
	 */
	spin_lock_irqsave(&kc->job_lock, flags);
	list_splice_tail_init(&kc->callback_jobs, &kc->complete_jobs);
	spin_unlock_irqrestore(&kc->job_lock, flags);

	blk_start_plug(&plug);
	process_jobs(&kc->complete_jobs, kc, run_complete_job);
	process_jobs(&kc->pages_jobs, kc, run_pages_job);
	process_jobs(&kc->io_jobs, kc, run_io_job);
	blk_finish_plug(&plug);
पूर्ण

/*
 * If we are copying a small region we just dispatch a single job
 * to करो the copy, otherwise the io has to be split up पूर्णांकo many
 * jobs.
 */
अटल व्योम dispatch_job(काष्ठा kcopyd_job *job)
अणु
	काष्ठा dm_kcopyd_client *kc = job->kc;
	atomic_inc(&kc->nr_jobs);
	अगर (unlikely(!job->source.count))
		push(&kc->callback_jobs, job);
	अन्यथा अगर (job->pages == &zero_page_list)
		push(&kc->io_jobs, job);
	अन्यथा
		push(&kc->pages_jobs, job);
	wake(kc);
पूर्ण

अटल व्योम segment_complete(पूर्णांक पढ़ो_err, अचिन्हित दीर्घ ग_लिखो_err,
			     व्योम *context)
अणु
	/* FIXME: tidy this function */
	sector_t progress = 0;
	sector_t count = 0;
	काष्ठा kcopyd_job *sub_job = (काष्ठा kcopyd_job *) context;
	काष्ठा kcopyd_job *job = sub_job->master_job;
	काष्ठा dm_kcopyd_client *kc = job->kc;

	mutex_lock(&job->lock);

	/* update the error */
	अगर (पढ़ो_err)
		job->पढ़ो_err = 1;

	अगर (ग_लिखो_err)
		job->ग_लिखो_err |= ग_लिखो_err;

	/*
	 * Only dispatch more work अगर there hasn't been an error.
	 */
	अगर ((!job->पढ़ो_err && !job->ग_लिखो_err) ||
	    test_bit(DM_KCOPYD_IGNORE_ERROR, &job->flags)) अणु
		/* get the next chunk of work */
		progress = job->progress;
		count = job->source.count - progress;
		अगर (count) अणु
			अगर (count > kc->sub_job_size)
				count = kc->sub_job_size;

			job->progress += count;
		पूर्ण
	पूर्ण
	mutex_unlock(&job->lock);

	अगर (count) अणु
		पूर्णांक i;

		*sub_job = *job;
		sub_job->ग_लिखो_offset = progress;
		sub_job->source.sector += progress;
		sub_job->source.count = count;

		क्रम (i = 0; i < job->num_dests; i++) अणु
			sub_job->dests[i].sector += progress;
			sub_job->dests[i].count = count;
		पूर्ण

		sub_job->fn = segment_complete;
		sub_job->context = sub_job;
		dispatch_job(sub_job);

	पूर्ण अन्यथा अगर (atomic_dec_and_test(&job->sub_jobs)) अणु

		/*
		 * Queue the completion callback to the kcopyd thपढ़ो.
		 *
		 * Some callers assume that all the completions are called
		 * from a single thपढ़ो and करोn't race with each other.
		 *
		 * We must not call the callback directly here because this
		 * code may not be executing in the thपढ़ो.
		 */
		push(&kc->complete_jobs, job);
		wake(kc);
	पूर्ण
पूर्ण

/*
 * Create some sub jobs to share the work between them.
 */
अटल व्योम split_job(काष्ठा kcopyd_job *master_job)
अणु
	पूर्णांक i;

	atomic_inc(&master_job->kc->nr_jobs);

	atomic_set(&master_job->sub_jobs, SPLIT_COUNT);
	क्रम (i = 0; i < SPLIT_COUNT; i++) अणु
		master_job[i + 1].master_job = master_job;
		segment_complete(0, 0u, &master_job[i + 1]);
	पूर्ण
पूर्ण

व्योम dm_kcopyd_copy(काष्ठा dm_kcopyd_client *kc, काष्ठा dm_io_region *from,
		    अचिन्हित पूर्णांक num_dests, काष्ठा dm_io_region *dests,
		    अचिन्हित पूर्णांक flags, dm_kcopyd_notअगरy_fn fn, व्योम *context)
अणु
	काष्ठा kcopyd_job *job;
	पूर्णांक i;

	/*
	 * Allocate an array of jobs consisting of one master job
	 * followed by SPLIT_COUNT sub jobs.
	 */
	job = mempool_alloc(&kc->job_pool, GFP_NOIO);
	mutex_init(&job->lock);

	/*
	 * set up क्रम the पढ़ो.
	 */
	job->kc = kc;
	job->flags = flags;
	job->पढ़ो_err = 0;
	job->ग_लिखो_err = 0;

	job->num_dests = num_dests;
	स_नकल(&job->dests, dests, माप(*dests) * num_dests);

	/*
	 * If one of the destination is a host-managed zoned block device,
	 * we need to ग_लिखो sequentially. If one of the destination is a
	 * host-aware device, then leave it to the caller to choose what to करो.
	 */
	अगर (!test_bit(DM_KCOPYD_WRITE_SEQ, &job->flags)) अणु
		क्रम (i = 0; i < job->num_dests; i++) अणु
			अगर (bdev_zoned_model(dests[i].bdev) == BLK_ZONED_HM) अणु
				set_bit(DM_KCOPYD_WRITE_SEQ, &job->flags);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * If we need to ग_लिखो sequentially, errors cannot be ignored.
	 */
	अगर (test_bit(DM_KCOPYD_WRITE_SEQ, &job->flags) &&
	    test_bit(DM_KCOPYD_IGNORE_ERROR, &job->flags))
		clear_bit(DM_KCOPYD_IGNORE_ERROR, &job->flags);

	अगर (from) अणु
		job->source = *from;
		job->pages = शून्य;
		job->rw = READ;
	पूर्ण अन्यथा अणु
		स_रखो(&job->source, 0, माप job->source);
		job->source.count = job->dests[0].count;
		job->pages = &zero_page_list;

		/*
		 * Use WRITE ZEROES to optimize zeroing अगर all dests support it.
		 */
		job->rw = REQ_OP_WRITE_ZEROES;
		क्रम (i = 0; i < job->num_dests; i++)
			अगर (!bdev_ग_लिखो_zeroes_sectors(job->dests[i].bdev)) अणु
				job->rw = WRITE;
				अवरोध;
			पूर्ण
	पूर्ण

	job->fn = fn;
	job->context = context;
	job->master_job = job;
	job->ग_लिखो_offset = 0;

	अगर (job->source.count <= kc->sub_job_size)
		dispatch_job(job);
	अन्यथा अणु
		job->progress = 0;
		split_job(job);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(dm_kcopyd_copy);

व्योम dm_kcopyd_zero(काष्ठा dm_kcopyd_client *kc,
		    अचिन्हित num_dests, काष्ठा dm_io_region *dests,
		    अचिन्हित flags, dm_kcopyd_notअगरy_fn fn, व्योम *context)
अणु
	dm_kcopyd_copy(kc, शून्य, num_dests, dests, flags, fn, context);
पूर्ण
EXPORT_SYMBOL(dm_kcopyd_zero);

व्योम *dm_kcopyd_prepare_callback(काष्ठा dm_kcopyd_client *kc,
				 dm_kcopyd_notअगरy_fn fn, व्योम *context)
अणु
	काष्ठा kcopyd_job *job;

	job = mempool_alloc(&kc->job_pool, GFP_NOIO);

	स_रखो(job, 0, माप(काष्ठा kcopyd_job));
	job->kc = kc;
	job->fn = fn;
	job->context = context;
	job->master_job = job;

	atomic_inc(&kc->nr_jobs);

	वापस job;
पूर्ण
EXPORT_SYMBOL(dm_kcopyd_prepare_callback);

व्योम dm_kcopyd_करो_callback(व्योम *j, पूर्णांक पढ़ो_err, अचिन्हित दीर्घ ग_लिखो_err)
अणु
	काष्ठा kcopyd_job *job = j;
	काष्ठा dm_kcopyd_client *kc = job->kc;

	job->पढ़ो_err = पढ़ो_err;
	job->ग_लिखो_err = ग_लिखो_err;

	push(&kc->callback_jobs, job);
	wake(kc);
पूर्ण
EXPORT_SYMBOL(dm_kcopyd_करो_callback);

/*
 * Cancels a kcopyd job, eg. someone might be deactivating a
 * mirror.
 */
#अगर 0
पूर्णांक kcopyd_cancel(काष्ठा kcopyd_job *job, पूर्णांक block)
अणु
	/* FIXME: finish */
	वापस -1;
पूर्ण
#पूर्ण_अगर  /*  0  */

/*-----------------------------------------------------------------
 * Client setup
 *---------------------------------------------------------------*/
काष्ठा dm_kcopyd_client *dm_kcopyd_client_create(काष्ठा dm_kcopyd_throttle *throttle)
अणु
	पूर्णांक r;
	अचिन्हित reserve_pages;
	काष्ठा dm_kcopyd_client *kc;

	kc = kzalloc(माप(*kc), GFP_KERNEL);
	अगर (!kc)
		वापस ERR_PTR(-ENOMEM);

	spin_lock_init(&kc->job_lock);
	INIT_LIST_HEAD(&kc->callback_jobs);
	INIT_LIST_HEAD(&kc->complete_jobs);
	INIT_LIST_HEAD(&kc->io_jobs);
	INIT_LIST_HEAD(&kc->pages_jobs);
	kc->throttle = throttle;

	r = mempool_init_slab_pool(&kc->job_pool, MIN_JOBS, _job_cache);
	अगर (r)
		जाओ bad_slab;

	INIT_WORK(&kc->kcopyd_work, करो_work);
	kc->kcopyd_wq = alloc_workqueue("kcopyd", WQ_MEM_RECLAIM, 0);
	अगर (!kc->kcopyd_wq) अणु
		r = -ENOMEM;
		जाओ bad_workqueue;
	पूर्ण

	kc->sub_job_size = dm_get_kcopyd_subjob_size();
	reserve_pages = DIV_ROUND_UP(kc->sub_job_size << SECTOR_SHIFT, PAGE_SIZE);

	kc->pages = शून्य;
	kc->nr_reserved_pages = kc->nr_मुक्त_pages = 0;
	r = client_reserve_pages(kc, reserve_pages);
	अगर (r)
		जाओ bad_client_pages;

	kc->io_client = dm_io_client_create();
	अगर (IS_ERR(kc->io_client)) अणु
		r = PTR_ERR(kc->io_client);
		जाओ bad_io_client;
	पूर्ण

	init_रुकोqueue_head(&kc->destroyq);
	atomic_set(&kc->nr_jobs, 0);

	वापस kc;

bad_io_client:
	client_मुक्त_pages(kc);
bad_client_pages:
	destroy_workqueue(kc->kcopyd_wq);
bad_workqueue:
	mempool_निकास(&kc->job_pool);
bad_slab:
	kमुक्त(kc);

	वापस ERR_PTR(r);
पूर्ण
EXPORT_SYMBOL(dm_kcopyd_client_create);

व्योम dm_kcopyd_client_destroy(काष्ठा dm_kcopyd_client *kc)
अणु
	/* Wait क्रम completion of all jobs submitted by this client. */
	रुको_event(kc->destroyq, !atomic_पढ़ो(&kc->nr_jobs));

	BUG_ON(!list_empty(&kc->callback_jobs));
	BUG_ON(!list_empty(&kc->complete_jobs));
	BUG_ON(!list_empty(&kc->io_jobs));
	BUG_ON(!list_empty(&kc->pages_jobs));
	destroy_workqueue(kc->kcopyd_wq);
	dm_io_client_destroy(kc->io_client);
	client_मुक्त_pages(kc);
	mempool_निकास(&kc->job_pool);
	kमुक्त(kc);
पूर्ण
EXPORT_SYMBOL(dm_kcopyd_client_destroy);
