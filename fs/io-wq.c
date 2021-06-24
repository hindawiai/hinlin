<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Basic worker thपढ़ो pool क्रम io_uring
 *
 * Copyright (C) 2019 Jens Axboe
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/mm.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/percpu.h>
#समावेश <linux/slab.h>
#समावेश <linux/rculist_nulls.h>
#समावेश <linux/cpu.h>
#समावेश <linux/tracehook.h>

#समावेश "io-wq.h"

#घोषणा WORKER_IDLE_TIMEOUT	(5 * HZ)

क्रमागत अणु
	IO_WORKER_F_UP		= 1,	/* up and active */
	IO_WORKER_F_RUNNING	= 2,	/* account as running */
	IO_WORKER_F_FREE	= 4,	/* worker on मुक्त list */
	IO_WORKER_F_FIXED	= 8,	/* अटल idle worker */
	IO_WORKER_F_BOUND	= 16,	/* is करोing bounded work */
पूर्ण;

क्रमागत अणु
	IO_WQ_BIT_EXIT		= 0,	/* wq निकासing */
पूर्ण;

क्रमागत अणु
	IO_WQE_FLAG_STALLED	= 1,	/* stalled on hash */
पूर्ण;

/*
 * One क्रम each thपढ़ो in a wqe pool
 */
काष्ठा io_worker अणु
	refcount_t ref;
	अचिन्हित flags;
	काष्ठा hlist_nulls_node nulls_node;
	काष्ठा list_head all_list;
	काष्ठा task_काष्ठा *task;
	काष्ठा io_wqe *wqe;

	काष्ठा io_wq_work *cur_work;
	spinlock_t lock;

	काष्ठा completion ref_करोne;

	काष्ठा rcu_head rcu;
पूर्ण;

#अगर BITS_PER_LONG == 64
#घोषणा IO_WQ_HASH_ORDER	6
#अन्यथा
#घोषणा IO_WQ_HASH_ORDER	5
#पूर्ण_अगर

#घोषणा IO_WQ_NR_HASH_BUCKETS	(1u << IO_WQ_HASH_ORDER)

काष्ठा io_wqe_acct अणु
	अचिन्हित nr_workers;
	अचिन्हित max_workers;
	पूर्णांक index;
	atomic_t nr_running;
पूर्ण;

क्रमागत अणु
	IO_WQ_ACCT_BOUND,
	IO_WQ_ACCT_UNBOUND,
पूर्ण;

/*
 * Per-node worker thपढ़ो pool
 */
काष्ठा io_wqe अणु
	काष्ठा अणु
		raw_spinlock_t lock;
		काष्ठा io_wq_work_list work_list;
		अचिन्हित flags;
	पूर्ण ____cacheline_aligned_in_smp;

	पूर्णांक node;
	काष्ठा io_wqe_acct acct[2];

	काष्ठा hlist_nulls_head मुक्त_list;
	काष्ठा list_head all_list;

	काष्ठा रुको_queue_entry रुको;

	काष्ठा io_wq *wq;
	काष्ठा io_wq_work *hash_tail[IO_WQ_NR_HASH_BUCKETS];
पूर्ण;

/*
 * Per io_wq state
  */
काष्ठा io_wq अणु
	काष्ठा io_wqe **wqes;
	अचिन्हित दीर्घ state;

	मुक्त_work_fn *मुक्त_work;
	io_wq_work_fn *करो_work;

	काष्ठा io_wq_hash *hash;

	refcount_t refs;

	atomic_t worker_refs;
	काष्ठा completion worker_करोne;

	काष्ठा hlist_node cpuhp_node;

	काष्ठा task_काष्ठा *task;
पूर्ण;

अटल क्रमागत cpuhp_state io_wq_online;

काष्ठा io_cb_cancel_data अणु
	work_cancel_fn *fn;
	व्योम *data;
	पूर्णांक nr_running;
	पूर्णांक nr_pending;
	bool cancel_all;
पूर्ण;

अटल व्योम create_io_worker(काष्ठा io_wq *wq, काष्ठा io_wqe *wqe, पूर्णांक index);

अटल bool io_worker_get(काष्ठा io_worker *worker)
अणु
	वापस refcount_inc_not_zero(&worker->ref);
पूर्ण

अटल व्योम io_worker_release(काष्ठा io_worker *worker)
अणु
	अगर (refcount_dec_and_test(&worker->ref))
		complete(&worker->ref_करोne);
पूर्ण

अटल अंतरभूत काष्ठा io_wqe_acct *io_get_acct(काष्ठा io_wqe *wqe, bool bound)
अणु
	वापस &wqe->acct[bound ? IO_WQ_ACCT_BOUND : IO_WQ_ACCT_UNBOUND];
पूर्ण

अटल अंतरभूत काष्ठा io_wqe_acct *io_work_get_acct(काष्ठा io_wqe *wqe,
						   काष्ठा io_wq_work *work)
अणु
	वापस io_get_acct(wqe, !(work->flags & IO_WQ_WORK_UNBOUND));
पूर्ण

अटल अंतरभूत काष्ठा io_wqe_acct *io_wqe_get_acct(काष्ठा io_worker *worker)
अणु
	वापस io_get_acct(worker->wqe, worker->flags & IO_WORKER_F_BOUND);
पूर्ण

अटल व्योम io_worker_ref_put(काष्ठा io_wq *wq)
अणु
	अगर (atomic_dec_and_test(&wq->worker_refs))
		complete(&wq->worker_करोne);
पूर्ण

अटल व्योम io_worker_निकास(काष्ठा io_worker *worker)
अणु
	काष्ठा io_wqe *wqe = worker->wqe;
	काष्ठा io_wqe_acct *acct = io_wqe_get_acct(worker);
	अचिन्हित flags;

	अगर (refcount_dec_and_test(&worker->ref))
		complete(&worker->ref_करोne);
	रुको_क्रम_completion(&worker->ref_करोne);

	preempt_disable();
	current->flags &= ~PF_IO_WORKER;
	flags = worker->flags;
	worker->flags = 0;
	अगर (flags & IO_WORKER_F_RUNNING)
		atomic_dec(&acct->nr_running);
	worker->flags = 0;
	preempt_enable();

	raw_spin_lock_irq(&wqe->lock);
	अगर (flags & IO_WORKER_F_FREE)
		hlist_nulls_del_rcu(&worker->nulls_node);
	list_del_rcu(&worker->all_list);
	acct->nr_workers--;
	raw_spin_unlock_irq(&wqe->lock);

	kमुक्त_rcu(worker, rcu);
	io_worker_ref_put(wqe->wq);
	करो_निकास(0);
पूर्ण

अटल अंतरभूत bool io_wqe_run_queue(काष्ठा io_wqe *wqe)
	__must_hold(wqe->lock)
अणु
	अगर (!wq_list_empty(&wqe->work_list) &&
	    !(wqe->flags & IO_WQE_FLAG_STALLED))
		वापस true;
	वापस false;
पूर्ण

/*
 * Check head of मुक्त list क्रम an available worker. If one isn't available,
 * caller must create one.
 */
अटल bool io_wqe_activate_मुक्त_worker(काष्ठा io_wqe *wqe)
	__must_hold(RCU)
अणु
	काष्ठा hlist_nulls_node *n;
	काष्ठा io_worker *worker;

	n = rcu_dereference(hlist_nulls_first_rcu(&wqe->मुक्त_list));
	अगर (is_a_nulls(n))
		वापस false;

	worker = hlist_nulls_entry(n, काष्ठा io_worker, nulls_node);
	अगर (io_worker_get(worker)) अणु
		wake_up_process(worker->task);
		io_worker_release(worker);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * We need a worker. If we find a मुक्त one, we're good. If not, and we're
 * below the max number of workers, create one.
 */
अटल व्योम io_wqe_wake_worker(काष्ठा io_wqe *wqe, काष्ठा io_wqe_acct *acct)
अणु
	bool ret;

	/*
	 * Most likely an attempt to queue unbounded work on an io_wq that
	 * wasn't setup with any unbounded workers.
	 */
	WARN_ON_ONCE(!acct->max_workers);

	rcu_पढ़ो_lock();
	ret = io_wqe_activate_मुक्त_worker(wqe);
	rcu_पढ़ो_unlock();

	अगर (!ret && acct->nr_workers < acct->max_workers) अणु
		atomic_inc(&acct->nr_running);
		atomic_inc(&wqe->wq->worker_refs);
		create_io_worker(wqe->wq, wqe, acct->index);
	पूर्ण
पूर्ण

अटल व्योम io_wqe_inc_running(काष्ठा io_worker *worker)
अणु
	काष्ठा io_wqe_acct *acct = io_wqe_get_acct(worker);

	atomic_inc(&acct->nr_running);
पूर्ण

काष्ठा create_worker_data अणु
	काष्ठा callback_head work;
	काष्ठा io_wqe *wqe;
	पूर्णांक index;
पूर्ण;

अटल व्योम create_worker_cb(काष्ठा callback_head *cb)
अणु
	काष्ठा create_worker_data *cwd;
	काष्ठा io_wq *wq;

	cwd = container_of(cb, काष्ठा create_worker_data, work);
	wq = cwd->wqe->wq;
	create_io_worker(wq, cwd->wqe, cwd->index);
	kमुक्त(cwd);
पूर्ण

अटल व्योम io_queue_worker_create(काष्ठा io_wqe *wqe, काष्ठा io_wqe_acct *acct)
अणु
	काष्ठा create_worker_data *cwd;
	काष्ठा io_wq *wq = wqe->wq;

	/* raced with निकास, just ignore create call */
	अगर (test_bit(IO_WQ_BIT_EXIT, &wq->state))
		जाओ fail;

	cwd = kदो_स्मृति(माप(*cwd), GFP_ATOMIC);
	अगर (cwd) अणु
		init_task_work(&cwd->work, create_worker_cb);
		cwd->wqe = wqe;
		cwd->index = acct->index;
		अगर (!task_work_add(wq->task, &cwd->work, TWA_SIGNAL))
			वापस;

		kमुक्त(cwd);
	पूर्ण
fail:
	atomic_dec(&acct->nr_running);
	io_worker_ref_put(wq);
पूर्ण

अटल व्योम io_wqe_dec_running(काष्ठा io_worker *worker)
	__must_hold(wqe->lock)
अणु
	काष्ठा io_wqe_acct *acct = io_wqe_get_acct(worker);
	काष्ठा io_wqe *wqe = worker->wqe;

	अगर (!(worker->flags & IO_WORKER_F_UP))
		वापस;

	अगर (atomic_dec_and_test(&acct->nr_running) && io_wqe_run_queue(wqe)) अणु
		atomic_inc(&acct->nr_running);
		atomic_inc(&wqe->wq->worker_refs);
		io_queue_worker_create(wqe, acct);
	पूर्ण
पूर्ण

/*
 * Worker will start processing some work. Move it to the busy list, अगर
 * it's currently on the मुक्तlist
 */
अटल व्योम __io_worker_busy(काष्ठा io_wqe *wqe, काष्ठा io_worker *worker,
			     काष्ठा io_wq_work *work)
	__must_hold(wqe->lock)
अणु
	bool worker_bound, work_bound;

	BUILD_BUG_ON((IO_WQ_ACCT_UNBOUND ^ IO_WQ_ACCT_BOUND) != 1);

	अगर (worker->flags & IO_WORKER_F_FREE) अणु
		worker->flags &= ~IO_WORKER_F_FREE;
		hlist_nulls_del_init_rcu(&worker->nulls_node);
	पूर्ण

	/*
	 * If worker is moving from bound to unbound (or vice versa), then
	 * ensure we update the running accounting.
	 */
	worker_bound = (worker->flags & IO_WORKER_F_BOUND) != 0;
	work_bound = (work->flags & IO_WQ_WORK_UNBOUND) == 0;
	अगर (worker_bound != work_bound) अणु
		पूर्णांक index = work_bound ? IO_WQ_ACCT_UNBOUND : IO_WQ_ACCT_BOUND;
		io_wqe_dec_running(worker);
		worker->flags ^= IO_WORKER_F_BOUND;
		wqe->acct[index].nr_workers--;
		wqe->acct[index ^ 1].nr_workers++;
		io_wqe_inc_running(worker);
	 पूर्ण
पूर्ण

/*
 * No work, worker going to sleep. Move to मुक्तlist, and unuse mm अगर we
 * have one attached. Dropping the mm may potentially sleep, so we drop
 * the lock in that हाल and वापस success. Since the caller has to
 * retry the loop in that हाल (we changed task state), we करोn't regrab
 * the lock अगर we वापस success.
 */
अटल व्योम __io_worker_idle(काष्ठा io_wqe *wqe, काष्ठा io_worker *worker)
	__must_hold(wqe->lock)
अणु
	अगर (!(worker->flags & IO_WORKER_F_FREE)) अणु
		worker->flags |= IO_WORKER_F_FREE;
		hlist_nulls_add_head_rcu(&worker->nulls_node, &wqe->मुक्त_list);
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक io_get_work_hash(काष्ठा io_wq_work *work)
अणु
	वापस work->flags >> IO_WQ_HASH_SHIFT;
पूर्ण

अटल व्योम io_रुको_on_hash(काष्ठा io_wqe *wqe, अचिन्हित पूर्णांक hash)
अणु
	काष्ठा io_wq *wq = wqe->wq;

	spin_lock(&wq->hash->रुको.lock);
	अगर (list_empty(&wqe->रुको.entry)) अणु
		__add_रुको_queue(&wq->hash->रुको, &wqe->रुको);
		अगर (!test_bit(hash, &wq->hash->map)) अणु
			__set_current_state(TASK_RUNNING);
			list_del_init(&wqe->रुको.entry);
		पूर्ण
	पूर्ण
	spin_unlock(&wq->hash->रुको.lock);
पूर्ण

अटल काष्ठा io_wq_work *io_get_next_work(काष्ठा io_wqe *wqe)
	__must_hold(wqe->lock)
अणु
	काष्ठा io_wq_work_node *node, *prev;
	काष्ठा io_wq_work *work, *tail;
	अचिन्हित पूर्णांक stall_hash = -1U;

	wq_list_क्रम_each(node, prev, &wqe->work_list) अणु
		अचिन्हित पूर्णांक hash;

		work = container_of(node, काष्ठा io_wq_work, list);

		/* not hashed, can run anyसमय */
		अगर (!io_wq_is_hashed(work)) अणु
			wq_list_del(&wqe->work_list, node, prev);
			वापस work;
		पूर्ण

		hash = io_get_work_hash(work);
		/* all items with this hash lie in [work, tail] */
		tail = wqe->hash_tail[hash];

		/* hashed, can run अगर not alपढ़ोy running */
		अगर (!test_and_set_bit(hash, &wqe->wq->hash->map)) अणु
			wqe->hash_tail[hash] = शून्य;
			wq_list_cut(&wqe->work_list, &tail->list, prev);
			वापस work;
		पूर्ण
		अगर (stall_hash == -1U)
			stall_hash = hash;
		/* fast क्रमward to a next hash, क्रम-each will fix up @prev */
		node = &tail->list;
	पूर्ण

	अगर (stall_hash != -1U) अणु
		raw_spin_unlock(&wqe->lock);
		io_रुको_on_hash(wqe, stall_hash);
		raw_spin_lock(&wqe->lock);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool io_flush_संकेतs(व्योम)
अणु
	अगर (unlikely(test_thपढ़ो_flag(TIF_NOTIFY_SIGNAL))) अणु
		__set_current_state(TASK_RUNNING);
		tracehook_notअगरy_संकेत();
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम io_assign_current_work(काष्ठा io_worker *worker,
				   काष्ठा io_wq_work *work)
अणु
	अगर (work) अणु
		io_flush_संकेतs();
		cond_resched();
	पूर्ण

	spin_lock_irq(&worker->lock);
	worker->cur_work = work;
	spin_unlock_irq(&worker->lock);
पूर्ण

अटल व्योम io_wqe_enqueue(काष्ठा io_wqe *wqe, काष्ठा io_wq_work *work);

अटल व्योम io_worker_handle_work(काष्ठा io_worker *worker)
	__releases(wqe->lock)
अणु
	काष्ठा io_wqe *wqe = worker->wqe;
	काष्ठा io_wq *wq = wqe->wq;
	bool करो_समाप्त = test_bit(IO_WQ_BIT_EXIT, &wq->state);

	करो अणु
		काष्ठा io_wq_work *work;
get_next:
		/*
		 * If we got some work, mark us as busy. If we didn't, but
		 * the list isn't empty, it means we stalled on hashed work.
		 * Mark us stalled so we करोn't keep looking क्रम work when we
		 * can't make progress, any work completion or insertion will
		 * clear the stalled flag.
		 */
		work = io_get_next_work(wqe);
		अगर (work)
			__io_worker_busy(wqe, worker, work);
		अन्यथा अगर (!wq_list_empty(&wqe->work_list))
			wqe->flags |= IO_WQE_FLAG_STALLED;

		raw_spin_unlock_irq(&wqe->lock);
		अगर (!work)
			अवरोध;
		io_assign_current_work(worker, work);
		__set_current_state(TASK_RUNNING);

		/* handle a whole dependent link */
		करो अणु
			काष्ठा io_wq_work *next_hashed, *linked;
			अचिन्हित पूर्णांक hash = io_get_work_hash(work);

			next_hashed = wq_next_work(work);

			अगर (unlikely(करो_समाप्त) && (work->flags & IO_WQ_WORK_UNBOUND))
				work->flags |= IO_WQ_WORK_CANCEL;
			wq->करो_work(work);
			io_assign_current_work(worker, शून्य);

			linked = wq->मुक्त_work(work);
			work = next_hashed;
			अगर (!work && linked && !io_wq_is_hashed(linked)) अणु
				work = linked;
				linked = शून्य;
			पूर्ण
			io_assign_current_work(worker, work);
			अगर (linked)
				io_wqe_enqueue(wqe, linked);

			अगर (hash != -1U && !next_hashed) अणु
				clear_bit(hash, &wq->hash->map);
				अगर (wq_has_sleeper(&wq->hash->रुको))
					wake_up(&wq->hash->रुको);
				raw_spin_lock_irq(&wqe->lock);
				wqe->flags &= ~IO_WQE_FLAG_STALLED;
				/* skip unnecessary unlock-lock wqe->lock */
				अगर (!work)
					जाओ get_next;
				raw_spin_unlock_irq(&wqe->lock);
			पूर्ण
		पूर्ण जबतक (work);

		raw_spin_lock_irq(&wqe->lock);
	पूर्ण जबतक (1);
पूर्ण

अटल पूर्णांक io_wqe_worker(व्योम *data)
अणु
	काष्ठा io_worker *worker = data;
	काष्ठा io_wqe *wqe = worker->wqe;
	काष्ठा io_wq *wq = wqe->wq;
	अक्षर buf[TASK_COMM_LEN];

	worker->flags |= (IO_WORKER_F_UP | IO_WORKER_F_RUNNING);

	snम_लिखो(buf, माप(buf), "iou-wrk-%d", wq->task->pid);
	set_task_comm(current, buf);

	जबतक (!test_bit(IO_WQ_BIT_EXIT, &wq->state)) अणु
		दीर्घ ret;

		set_current_state(TASK_INTERRUPTIBLE);
loop:
		raw_spin_lock_irq(&wqe->lock);
		अगर (io_wqe_run_queue(wqe)) अणु
			io_worker_handle_work(worker);
			जाओ loop;
		पूर्ण
		__io_worker_idle(wqe, worker);
		raw_spin_unlock_irq(&wqe->lock);
		अगर (io_flush_संकेतs())
			जारी;
		ret = schedule_समयout(WORKER_IDLE_TIMEOUT);
		अगर (संकेत_pending(current)) अणु
			काष्ठा kसंकेत ksig;

			अगर (!get_संकेत(&ksig))
				जारी;
			अवरोध;
		पूर्ण
		अगर (ret)
			जारी;
		/* समयd out, निकास unless we're the fixed worker */
		अगर (test_bit(IO_WQ_BIT_EXIT, &wq->state) ||
		    !(worker->flags & IO_WORKER_F_FIXED))
			अवरोध;
	पूर्ण

	अगर (test_bit(IO_WQ_BIT_EXIT, &wq->state)) अणु
		raw_spin_lock_irq(&wqe->lock);
		अगर (!wq_list_empty(&wqe->work_list))
			io_worker_handle_work(worker);
		अन्यथा
			raw_spin_unlock_irq(&wqe->lock);
	पूर्ण

	io_worker_निकास(worker);
	वापस 0;
पूर्ण

/*
 * Called when a worker is scheduled in. Mark us as currently running.
 */
व्योम io_wq_worker_running(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा io_worker *worker = tsk->pf_io_worker;

	अगर (!worker)
		वापस;
	अगर (!(worker->flags & IO_WORKER_F_UP))
		वापस;
	अगर (worker->flags & IO_WORKER_F_RUNNING)
		वापस;
	worker->flags |= IO_WORKER_F_RUNNING;
	io_wqe_inc_running(worker);
पूर्ण

/*
 * Called when worker is going to sleep. If there are no workers currently
 * running and we have work pending, wake up a मुक्त one or create a new one.
 */
व्योम io_wq_worker_sleeping(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा io_worker *worker = tsk->pf_io_worker;

	अगर (!worker)
		वापस;
	अगर (!(worker->flags & IO_WORKER_F_UP))
		वापस;
	अगर (!(worker->flags & IO_WORKER_F_RUNNING))
		वापस;

	worker->flags &= ~IO_WORKER_F_RUNNING;

	raw_spin_lock_irq(&worker->wqe->lock);
	io_wqe_dec_running(worker);
	raw_spin_unlock_irq(&worker->wqe->lock);
पूर्ण

अटल व्योम create_io_worker(काष्ठा io_wq *wq, काष्ठा io_wqe *wqe, पूर्णांक index)
अणु
	काष्ठा io_wqe_acct *acct = &wqe->acct[index];
	काष्ठा io_worker *worker;
	काष्ठा task_काष्ठा *tsk;

	__set_current_state(TASK_RUNNING);

	worker = kzalloc_node(माप(*worker), GFP_KERNEL, wqe->node);
	अगर (!worker)
		जाओ fail;

	refcount_set(&worker->ref, 1);
	worker->nulls_node.pprev = शून्य;
	worker->wqe = wqe;
	spin_lock_init(&worker->lock);
	init_completion(&worker->ref_करोne);

	tsk = create_io_thपढ़ो(io_wqe_worker, worker, wqe->node);
	अगर (IS_ERR(tsk)) अणु
		kमुक्त(worker);
fail:
		atomic_dec(&acct->nr_running);
		io_worker_ref_put(wq);
		वापस;
	पूर्ण

	tsk->pf_io_worker = worker;
	worker->task = tsk;
	set_cpus_allowed_ptr(tsk, cpumask_of_node(wqe->node));
	tsk->flags |= PF_NO_SETAFFINITY;

	raw_spin_lock_irq(&wqe->lock);
	hlist_nulls_add_head_rcu(&worker->nulls_node, &wqe->मुक्त_list);
	list_add_tail_rcu(&worker->all_list, &wqe->all_list);
	worker->flags |= IO_WORKER_F_FREE;
	अगर (index == IO_WQ_ACCT_BOUND)
		worker->flags |= IO_WORKER_F_BOUND;
	अगर (!acct->nr_workers && (worker->flags & IO_WORKER_F_BOUND))
		worker->flags |= IO_WORKER_F_FIXED;
	acct->nr_workers++;
	raw_spin_unlock_irq(&wqe->lock);
	wake_up_new_task(tsk);
पूर्ण

/*
 * Iterate the passed in list and call the specअगरic function क्रम each
 * worker that isn't निकासing
 */
अटल bool io_wq_क्रम_each_worker(काष्ठा io_wqe *wqe,
				  bool (*func)(काष्ठा io_worker *, व्योम *),
				  व्योम *data)
अणु
	काष्ठा io_worker *worker;
	bool ret = false;

	list_क्रम_each_entry_rcu(worker, &wqe->all_list, all_list) अणु
		अगर (io_worker_get(worker)) अणु
			/* no task अगर node is/was offline */
			अगर (worker->task)
				ret = func(worker, data);
			io_worker_release(worker);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल bool io_wq_worker_wake(काष्ठा io_worker *worker, व्योम *data)
अणु
	set_notअगरy_संकेत(worker->task);
	wake_up_process(worker->task);
	वापस false;
पूर्ण

अटल bool io_wq_work_match_all(काष्ठा io_wq_work *work, व्योम *data)
अणु
	वापस true;
पूर्ण

अटल व्योम io_run_cancel(काष्ठा io_wq_work *work, काष्ठा io_wqe *wqe)
अणु
	काष्ठा io_wq *wq = wqe->wq;

	करो अणु
		work->flags |= IO_WQ_WORK_CANCEL;
		wq->करो_work(work);
		work = wq->मुक्त_work(work);
	पूर्ण जबतक (work);
पूर्ण

अटल व्योम io_wqe_insert_work(काष्ठा io_wqe *wqe, काष्ठा io_wq_work *work)
अणु
	अचिन्हित पूर्णांक hash;
	काष्ठा io_wq_work *tail;

	अगर (!io_wq_is_hashed(work)) अणु
append:
		wq_list_add_tail(&work->list, &wqe->work_list);
		वापस;
	पूर्ण

	hash = io_get_work_hash(work);
	tail = wqe->hash_tail[hash];
	wqe->hash_tail[hash] = work;
	अगर (!tail)
		जाओ append;

	wq_list_add_after(&work->list, &tail->list, &wqe->work_list);
पूर्ण

अटल व्योम io_wqe_enqueue(काष्ठा io_wqe *wqe, काष्ठा io_wq_work *work)
अणु
	काष्ठा io_wqe_acct *acct = io_work_get_acct(wqe, work);
	पूर्णांक work_flags;
	अचिन्हित दीर्घ flags;

	अगर (test_bit(IO_WQ_BIT_EXIT, &wqe->wq->state)) अणु
		io_run_cancel(work, wqe);
		वापस;
	पूर्ण

	work_flags = work->flags;
	raw_spin_lock_irqsave(&wqe->lock, flags);
	io_wqe_insert_work(wqe, work);
	wqe->flags &= ~IO_WQE_FLAG_STALLED;
	raw_spin_unlock_irqrestore(&wqe->lock, flags);

	अगर ((work_flags & IO_WQ_WORK_CONCURRENT) ||
	    !atomic_पढ़ो(&acct->nr_running))
		io_wqe_wake_worker(wqe, acct);
पूर्ण

व्योम io_wq_enqueue(काष्ठा io_wq *wq, काष्ठा io_wq_work *work)
अणु
	काष्ठा io_wqe *wqe = wq->wqes[numa_node_id()];

	io_wqe_enqueue(wqe, work);
पूर्ण

/*
 * Work items that hash to the same value will not be करोne in parallel.
 * Used to limit concurrent ग_लिखोs, generally hashed by inode.
 */
व्योम io_wq_hash_work(काष्ठा io_wq_work *work, व्योम *val)
अणु
	अचिन्हित पूर्णांक bit;

	bit = hash_ptr(val, IO_WQ_HASH_ORDER);
	work->flags |= (IO_WQ_WORK_HASHED | (bit << IO_WQ_HASH_SHIFT));
पूर्ण

अटल bool io_wq_worker_cancel(काष्ठा io_worker *worker, व्योम *data)
अणु
	काष्ठा io_cb_cancel_data *match = data;
	अचिन्हित दीर्घ flags;

	/*
	 * Hold the lock to aव्योम ->cur_work going out of scope, caller
	 * may dereference the passed in work.
	 */
	spin_lock_irqsave(&worker->lock, flags);
	अगर (worker->cur_work &&
	    match->fn(worker->cur_work, match->data)) अणु
		set_notअगरy_संकेत(worker->task);
		match->nr_running++;
	पूर्ण
	spin_unlock_irqrestore(&worker->lock, flags);

	वापस match->nr_running && !match->cancel_all;
पूर्ण

अटल अंतरभूत व्योम io_wqe_हटाओ_pending(काष्ठा io_wqe *wqe,
					 काष्ठा io_wq_work *work,
					 काष्ठा io_wq_work_node *prev)
अणु
	अचिन्हित पूर्णांक hash = io_get_work_hash(work);
	काष्ठा io_wq_work *prev_work = शून्य;

	अगर (io_wq_is_hashed(work) && work == wqe->hash_tail[hash]) अणु
		अगर (prev)
			prev_work = container_of(prev, काष्ठा io_wq_work, list);
		अगर (prev_work && io_get_work_hash(prev_work) == hash)
			wqe->hash_tail[hash] = prev_work;
		अन्यथा
			wqe->hash_tail[hash] = शून्य;
	पूर्ण
	wq_list_del(&wqe->work_list, &work->list, prev);
पूर्ण

अटल व्योम io_wqe_cancel_pending_work(काष्ठा io_wqe *wqe,
				       काष्ठा io_cb_cancel_data *match)
अणु
	काष्ठा io_wq_work_node *node, *prev;
	काष्ठा io_wq_work *work;
	अचिन्हित दीर्घ flags;

retry:
	raw_spin_lock_irqsave(&wqe->lock, flags);
	wq_list_क्रम_each(node, prev, &wqe->work_list) अणु
		work = container_of(node, काष्ठा io_wq_work, list);
		अगर (!match->fn(work, match->data))
			जारी;
		io_wqe_हटाओ_pending(wqe, work, prev);
		raw_spin_unlock_irqrestore(&wqe->lock, flags);
		io_run_cancel(work, wqe);
		match->nr_pending++;
		अगर (!match->cancel_all)
			वापस;

		/* not safe to जारी after unlock */
		जाओ retry;
	पूर्ण
	raw_spin_unlock_irqrestore(&wqe->lock, flags);
पूर्ण

अटल व्योम io_wqe_cancel_running_work(काष्ठा io_wqe *wqe,
				       काष्ठा io_cb_cancel_data *match)
अणु
	rcu_पढ़ो_lock();
	io_wq_क्रम_each_worker(wqe, io_wq_worker_cancel, match);
	rcu_पढ़ो_unlock();
पूर्ण

क्रमागत io_wq_cancel io_wq_cancel_cb(काष्ठा io_wq *wq, work_cancel_fn *cancel,
				  व्योम *data, bool cancel_all)
अणु
	काष्ठा io_cb_cancel_data match = अणु
		.fn		= cancel,
		.data		= data,
		.cancel_all	= cancel_all,
	पूर्ण;
	पूर्णांक node;

	/*
	 * First check pending list, अगर we're lucky we can just हटाओ it
	 * from there. CANCEL_OK means that the work is वापसed as-new,
	 * no completion will be posted क्रम it.
	 */
	क्रम_each_node(node) अणु
		काष्ठा io_wqe *wqe = wq->wqes[node];

		io_wqe_cancel_pending_work(wqe, &match);
		अगर (match.nr_pending && !match.cancel_all)
			वापस IO_WQ_CANCEL_OK;
	पूर्ण

	/*
	 * Now check अगर a मुक्त (going busy) or busy worker has the work
	 * currently running. If we find it there, we'll वापस CANCEL_RUNNING
	 * as an indication that we attempt to संकेत cancellation. The
	 * completion will run normally in this हाल.
	 */
	क्रम_each_node(node) अणु
		काष्ठा io_wqe *wqe = wq->wqes[node];

		io_wqe_cancel_running_work(wqe, &match);
		अगर (match.nr_running && !match.cancel_all)
			वापस IO_WQ_CANCEL_RUNNING;
	पूर्ण

	अगर (match.nr_running)
		वापस IO_WQ_CANCEL_RUNNING;
	अगर (match.nr_pending)
		वापस IO_WQ_CANCEL_OK;
	वापस IO_WQ_CANCEL_NOTFOUND;
पूर्ण

अटल पूर्णांक io_wqe_hash_wake(काष्ठा रुको_queue_entry *रुको, अचिन्हित mode,
			    पूर्णांक sync, व्योम *key)
अणु
	काष्ठा io_wqe *wqe = container_of(रुको, काष्ठा io_wqe, रुको);

	list_del_init(&रुको->entry);

	rcu_पढ़ो_lock();
	io_wqe_activate_मुक्त_worker(wqe);
	rcu_पढ़ो_unlock();
	वापस 1;
पूर्ण

काष्ठा io_wq *io_wq_create(अचिन्हित bounded, काष्ठा io_wq_data *data)
अणु
	पूर्णांक ret = -ENOMEM, node;
	काष्ठा io_wq *wq;

	अगर (WARN_ON_ONCE(!data->मुक्त_work || !data->करो_work))
		वापस ERR_PTR(-EINVAL);

	wq = kzalloc(माप(*wq), GFP_KERNEL);
	अगर (!wq)
		वापस ERR_PTR(-ENOMEM);

	wq->wqes = kसुस्मृति(nr_node_ids, माप(काष्ठा io_wqe *), GFP_KERNEL);
	अगर (!wq->wqes)
		जाओ err_wq;

	ret = cpuhp_state_add_instance_nocalls(io_wq_online, &wq->cpuhp_node);
	अगर (ret)
		जाओ err_wqes;

	refcount_inc(&data->hash->refs);
	wq->hash = data->hash;
	wq->मुक्त_work = data->मुक्त_work;
	wq->करो_work = data->करो_work;

	ret = -ENOMEM;
	क्रम_each_node(node) अणु
		काष्ठा io_wqe *wqe;
		पूर्णांक alloc_node = node;

		अगर (!node_online(alloc_node))
			alloc_node = NUMA_NO_NODE;
		wqe = kzalloc_node(माप(काष्ठा io_wqe), GFP_KERNEL, alloc_node);
		अगर (!wqe)
			जाओ err;
		wq->wqes[node] = wqe;
		wqe->node = alloc_node;
		wqe->acct[IO_WQ_ACCT_BOUND].index = IO_WQ_ACCT_BOUND;
		wqe->acct[IO_WQ_ACCT_UNBOUND].index = IO_WQ_ACCT_UNBOUND;
		wqe->acct[IO_WQ_ACCT_BOUND].max_workers = bounded;
		atomic_set(&wqe->acct[IO_WQ_ACCT_BOUND].nr_running, 0);
		wqe->acct[IO_WQ_ACCT_UNBOUND].max_workers =
					task_rlimit(current, RLIMIT_NPROC);
		atomic_set(&wqe->acct[IO_WQ_ACCT_UNBOUND].nr_running, 0);
		wqe->रुको.func = io_wqe_hash_wake;
		INIT_LIST_HEAD(&wqe->रुको.entry);
		wqe->wq = wq;
		raw_spin_lock_init(&wqe->lock);
		INIT_WQ_LIST(&wqe->work_list);
		INIT_HLIST_शून्यS_HEAD(&wqe->मुक्त_list, 0);
		INIT_LIST_HEAD(&wqe->all_list);
	पूर्ण

	wq->task = get_task_काष्ठा(data->task);
	refcount_set(&wq->refs, 1);
	atomic_set(&wq->worker_refs, 1);
	init_completion(&wq->worker_करोne);
	वापस wq;
err:
	io_wq_put_hash(data->hash);
	cpuhp_state_हटाओ_instance_nocalls(io_wq_online, &wq->cpuhp_node);
	क्रम_each_node(node)
		kमुक्त(wq->wqes[node]);
err_wqes:
	kमुक्त(wq->wqes);
err_wq:
	kमुक्त(wq);
	वापस ERR_PTR(ret);
पूर्ण

अटल bool io_task_work_match(काष्ठा callback_head *cb, व्योम *data)
अणु
	काष्ठा create_worker_data *cwd;

	अगर (cb->func != create_worker_cb)
		वापस false;
	cwd = container_of(cb, काष्ठा create_worker_data, work);
	वापस cwd->wqe->wq == data;
पूर्ण

व्योम io_wq_निकास_start(काष्ठा io_wq *wq)
अणु
	set_bit(IO_WQ_BIT_EXIT, &wq->state);
पूर्ण

अटल व्योम io_wq_निकास_workers(काष्ठा io_wq *wq)
अणु
	काष्ठा callback_head *cb;
	पूर्णांक node;

	अगर (!wq->task)
		वापस;

	जबतक ((cb = task_work_cancel_match(wq->task, io_task_work_match, wq)) != शून्य) अणु
		काष्ठा create_worker_data *cwd;

		cwd = container_of(cb, काष्ठा create_worker_data, work);
		atomic_dec(&cwd->wqe->acct[cwd->index].nr_running);
		io_worker_ref_put(wq);
		kमुक्त(cwd);
	पूर्ण

	rcu_पढ़ो_lock();
	क्रम_each_node(node) अणु
		काष्ठा io_wqe *wqe = wq->wqes[node];

		io_wq_क्रम_each_worker(wqe, io_wq_worker_wake, शून्य);
	पूर्ण
	rcu_पढ़ो_unlock();
	io_worker_ref_put(wq);
	रुको_क्रम_completion(&wq->worker_करोne);

	क्रम_each_node(node) अणु
		spin_lock_irq(&wq->hash->रुको.lock);
		list_del_init(&wq->wqes[node]->रुको.entry);
		spin_unlock_irq(&wq->hash->रुको.lock);
	पूर्ण
	put_task_काष्ठा(wq->task);
	wq->task = शून्य;
पूर्ण

अटल व्योम io_wq_destroy(काष्ठा io_wq *wq)
अणु
	पूर्णांक node;

	cpuhp_state_हटाओ_instance_nocalls(io_wq_online, &wq->cpuhp_node);

	क्रम_each_node(node) अणु
		काष्ठा io_wqe *wqe = wq->wqes[node];
		काष्ठा io_cb_cancel_data match = अणु
			.fn		= io_wq_work_match_all,
			.cancel_all	= true,
		पूर्ण;
		io_wqe_cancel_pending_work(wqe, &match);
		kमुक्त(wqe);
	पूर्ण
	io_wq_put_hash(wq->hash);
	kमुक्त(wq->wqes);
	kमुक्त(wq);
पूर्ण

व्योम io_wq_put_and_निकास(काष्ठा io_wq *wq)
अणु
	WARN_ON_ONCE(!test_bit(IO_WQ_BIT_EXIT, &wq->state));

	io_wq_निकास_workers(wq);
	अगर (refcount_dec_and_test(&wq->refs))
		io_wq_destroy(wq);
पूर्ण

अटल bool io_wq_worker_affinity(काष्ठा io_worker *worker, व्योम *data)
अणु
	set_cpus_allowed_ptr(worker->task, cpumask_of_node(worker->wqe->node));

	वापस false;
पूर्ण

अटल पूर्णांक io_wq_cpu_online(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा io_wq *wq = hlist_entry_safe(node, काष्ठा io_wq, cpuhp_node);
	पूर्णांक i;

	rcu_पढ़ो_lock();
	क्रम_each_node(i)
		io_wq_क्रम_each_worker(wq->wqes[i], io_wq_worker_affinity, शून्य);
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

अटल __init पूर्णांक io_wq_init(व्योम)
अणु
	पूर्णांक ret;

	ret = cpuhp_setup_state_multi(CPUHP_AP_ONLINE_DYN, "io-wq/online",
					io_wq_cpu_online, शून्य);
	अगर (ret < 0)
		वापस ret;
	io_wq_online = ret;
	वापस 0;
पूर्ण
subsys_initcall(io_wq_init);
