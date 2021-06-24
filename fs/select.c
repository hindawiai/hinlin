<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file contains the procedures क्रम the handling of select and poll
 *
 * Created क्रम Linux based loosely upon Mathius Lattner's minix
 * patches by Peter MacDonald. Heavily edited by Linus.
 *
 *  4 February 1994
 *     COFF/ELF binary emulation. If the process has the STICKY_TIMEOUTS
 *     flag set in its personality we करो *not* modअगरy the given समयout
 *     parameter to reflect समय reमुख्यing.
 *
 *  24 January 2000
 *     Changed sys_poll()/करो_poll() to use PAGE_SIZE chunk-based allocation 
 *     of fds to overcome nfds < 16390 descriptors limit (Tigran Aivazian).
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/rt.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/personality.h> /* क्रम STICKY_TIMEOUTS */
#समावेश <linux/file.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/fs.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <net/busy_poll.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <linux/uaccess.h>


/*
 * Estimate expected accuracy in ns from a समयval.
 *
 * After quite a bit of churning around, we've settled on
 * a simple thing of taking 0.1% of the समयout as the
 * slack, with a cap of 100 msec.
 * "nice" tasks get a 0.5% slack instead.
 *
 * Consider this comment an खोलो invitation to come up with even
 * better solutions..
 */

#घोषणा MAX_SLACK	(100 * NSEC_PER_MSEC)

अटल दीर्घ __estimate_accuracy(काष्ठा बारpec64 *tv)
अणु
	दीर्घ slack;
	पूर्णांक भागfactor = 1000;

	अगर (tv->tv_sec < 0)
		वापस 0;

	अगर (task_nice(current) > 0)
		भागfactor = भागfactor / 5;

	अगर (tv->tv_sec > MAX_SLACK / (NSEC_PER_SEC/भागfactor))
		वापस MAX_SLACK;

	slack = tv->tv_nsec / भागfactor;
	slack += tv->tv_sec * (NSEC_PER_SEC/भागfactor);

	अगर (slack > MAX_SLACK)
		वापस MAX_SLACK;

	वापस slack;
पूर्ण

u64 select_estimate_accuracy(काष्ठा बारpec64 *tv)
अणु
	u64 ret;
	काष्ठा बारpec64 now;

	/*
	 * Realसमय tasks get a slack of 0 क्रम obvious reasons.
	 */

	अगर (rt_task(current))
		वापस 0;

	kसमय_get_ts64(&now);
	now = बारpec64_sub(*tv, now);
	ret = __estimate_accuracy(&now);
	अगर (ret < current->समयr_slack_ns)
		वापस current->समयr_slack_ns;
	वापस ret;
पूर्ण



काष्ठा poll_table_page अणु
	काष्ठा poll_table_page * next;
	काष्ठा poll_table_entry * entry;
	काष्ठा poll_table_entry entries[];
पूर्ण;

#घोषणा POLL_TABLE_FULL(table) \
	((अचिन्हित दीर्घ)((table)->entry+1) > PAGE_SIZE + (अचिन्हित दीर्घ)(table))

/*
 * Ok, Peter made a complicated, but straightक्रमward multiple_रुको() function.
 * I have rewritten this, taking some लघुcuts: This code may not be easy to
 * follow, but it should be मुक्त of race-conditions, and it's practical. If you
 * understand what I'm करोing here, then you understand how the linux
 * sleep/wakeup mechanism works.
 *
 * Two very simple procedures, poll_रुको() and poll_मुक्तरुको() make all the
 * work.  poll_रुको() is an अंतरभूत-function defined in <linux/poll.h>,
 * as all select/poll functions have to call it to add an entry to the
 * poll table.
 */
अटल व्योम __pollरुको(काष्ठा file *filp, रुको_queue_head_t *रुको_address,
		       poll_table *p);

व्योम poll_initरुको(काष्ठा poll_wqueues *pwq)
अणु
	init_poll_funcptr(&pwq->pt, __pollरुको);
	pwq->polling_task = current;
	pwq->triggered = 0;
	pwq->error = 0;
	pwq->table = शून्य;
	pwq->अंतरभूत_index = 0;
पूर्ण
EXPORT_SYMBOL(poll_initरुको);

अटल व्योम मुक्त_poll_entry(काष्ठा poll_table_entry *entry)
अणु
	हटाओ_रुको_queue(entry->रुको_address, &entry->रुको);
	fput(entry->filp);
पूर्ण

व्योम poll_मुक्तरुको(काष्ठा poll_wqueues *pwq)
अणु
	काष्ठा poll_table_page * p = pwq->table;
	पूर्णांक i;
	क्रम (i = 0; i < pwq->अंतरभूत_index; i++)
		मुक्त_poll_entry(pwq->अंतरभूत_entries + i);
	जबतक (p) अणु
		काष्ठा poll_table_entry * entry;
		काष्ठा poll_table_page *old;

		entry = p->entry;
		करो अणु
			entry--;
			मुक्त_poll_entry(entry);
		पूर्ण जबतक (entry > p->entries);
		old = p;
		p = p->next;
		मुक्त_page((अचिन्हित दीर्घ) old);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(poll_मुक्तरुको);

अटल काष्ठा poll_table_entry *poll_get_entry(काष्ठा poll_wqueues *p)
अणु
	काष्ठा poll_table_page *table = p->table;

	अगर (p->अंतरभूत_index < N_INLINE_POLL_ENTRIES)
		वापस p->अंतरभूत_entries + p->अंतरभूत_index++;

	अगर (!table || POLL_TABLE_FULL(table)) अणु
		काष्ठा poll_table_page *new_table;

		new_table = (काष्ठा poll_table_page *) __get_मुक्त_page(GFP_KERNEL);
		अगर (!new_table) अणु
			p->error = -ENOMEM;
			वापस शून्य;
		पूर्ण
		new_table->entry = new_table->entries;
		new_table->next = table;
		p->table = new_table;
		table = new_table;
	पूर्ण

	वापस table->entry++;
पूर्ण

अटल पूर्णांक __pollwake(रुको_queue_entry_t *रुको, अचिन्हित mode, पूर्णांक sync, व्योम *key)
अणु
	काष्ठा poll_wqueues *pwq = रुको->निजी;
	DECLARE_WAITQUEUE(dummy_रुको, pwq->polling_task);

	/*
	 * Although this function is called under रुकोqueue lock, LOCK
	 * करोesn't imply ग_लिखो barrier and the users expect ग_लिखो
	 * barrier semantics on wakeup functions.  The following
	 * smp_wmb() is equivalent to smp_wmb() in try_to_wake_up()
	 * and is paired with smp_store_mb() in poll_schedule_समयout.
	 */
	smp_wmb();
	pwq->triggered = 1;

	/*
	 * Perक्रमm the शेष wake up operation using a dummy
	 * रुकोqueue.
	 *
	 * TODO: This is hacky but there currently is no पूर्णांकerface to
	 * pass in @sync.  @sync is scheduled to be हटाओd and once
	 * that happens, wake_up_process() can be used directly.
	 */
	वापस शेष_wake_function(&dummy_रुको, mode, sync, key);
पूर्ण

अटल पूर्णांक pollwake(रुको_queue_entry_t *रुको, अचिन्हित mode, पूर्णांक sync, व्योम *key)
अणु
	काष्ठा poll_table_entry *entry;

	entry = container_of(रुको, काष्ठा poll_table_entry, रुको);
	अगर (key && !(key_to_poll(key) & entry->key))
		वापस 0;
	वापस __pollwake(रुको, mode, sync, key);
पूर्ण

/* Add a new entry */
अटल व्योम __pollरुको(काष्ठा file *filp, रुको_queue_head_t *रुको_address,
				poll_table *p)
अणु
	काष्ठा poll_wqueues *pwq = container_of(p, काष्ठा poll_wqueues, pt);
	काष्ठा poll_table_entry *entry = poll_get_entry(pwq);
	अगर (!entry)
		वापस;
	entry->filp = get_file(filp);
	entry->रुको_address = रुको_address;
	entry->key = p->_key;
	init_रुकोqueue_func_entry(&entry->रुको, pollwake);
	entry->रुको.निजी = pwq;
	add_रुको_queue(रुको_address, &entry->रुको);
पूर्ण

अटल पूर्णांक poll_schedule_समयout(काष्ठा poll_wqueues *pwq, पूर्णांक state,
			  kसमय_प्रकार *expires, अचिन्हित दीर्घ slack)
अणु
	पूर्णांक rc = -EINTR;

	set_current_state(state);
	अगर (!pwq->triggered)
		rc = schedule_hrसमयout_range(expires, slack, HRTIMER_MODE_ABS);
	__set_current_state(TASK_RUNNING);

	/*
	 * Prepare क्रम the next iteration.
	 *
	 * The following smp_store_mb() serves two purposes.  First, it's
	 * the counterpart rmb of the wmb in pollwake() such that data
	 * written beक्रमe wake up is always visible after wake up.
	 * Second, the full barrier guarantees that triggered clearing
	 * करोesn't pass event check of the next iteration.  Note that
	 * this problem करोesn't exist क्रम the first iteration as
	 * add_रुको_queue() has full barrier semantics.
	 */
	smp_store_mb(pwq->triggered, 0);

	वापस rc;
पूर्ण

/**
 * poll_select_set_समयout - helper function to setup the समयout value
 * @to:		poपूर्णांकer to बारpec64 variable क्रम the final समयout
 * @sec:	seconds (from user space)
 * @nsec:	nanoseconds (from user space)
 *
 * Note, we करो not use a बारpec क्रम the user space value here, That
 * way we can use the function क्रम समयval and compat पूर्णांकerfaces as well.
 *
 * Returns -EINVAL अगर sec/nsec are not normalized. Otherwise 0.
 */
पूर्णांक poll_select_set_समयout(काष्ठा बारpec64 *to, समय64_t sec, दीर्घ nsec)
अणु
	काष्ठा बारpec64 ts = अणु.tv_sec = sec, .tv_nsec = nsecपूर्ण;

	अगर (!बारpec64_valid(&ts))
		वापस -EINVAL;

	/* Optimize क्रम the zero समयout value here */
	अगर (!sec && !nsec) अणु
		to->tv_sec = to->tv_nsec = 0;
	पूर्ण अन्यथा अणु
		kसमय_get_ts64(to);
		*to = बारpec64_add_safe(*to, ts);
	पूर्ण
	वापस 0;
पूर्ण

क्रमागत poll_समय_प्रकारype अणु
	PT_TIMEVAL = 0,
	PT_OLD_TIMEVAL = 1,
	PT_TIMESPEC = 2,
	PT_OLD_TIMESPEC = 3,
पूर्ण;

अटल पूर्णांक poll_select_finish(काष्ठा बारpec64 *end_समय,
			      व्योम __user *p,
			      क्रमागत poll_समय_प्रकारype pt_type, पूर्णांक ret)
अणु
	काष्ठा बारpec64 rts;

	restore_saved_sigmask_unless(ret == -ERESTARTNOHAND);

	अगर (!p)
		वापस ret;

	अगर (current->personality & STICKY_TIMEOUTS)
		जाओ sticky;

	/* No update क्रम zero समयout */
	अगर (!end_समय->tv_sec && !end_समय->tv_nsec)
		वापस ret;

	kसमय_get_ts64(&rts);
	rts = बारpec64_sub(*end_समय, rts);
	अगर (rts.tv_sec < 0)
		rts.tv_sec = rts.tv_nsec = 0;


	चयन (pt_type) अणु
	हाल PT_TIMEVAL:
		अणु
			काष्ठा __kernel_old_समयval rtv;

			अगर (माप(rtv) > माप(rtv.tv_sec) + माप(rtv.tv_usec))
				स_रखो(&rtv, 0, माप(rtv));
			rtv.tv_sec = rts.tv_sec;
			rtv.tv_usec = rts.tv_nsec / NSEC_PER_USEC;
			अगर (!copy_to_user(p, &rtv, माप(rtv)))
				वापस ret;
		पूर्ण
		अवरोध;
	हाल PT_OLD_TIMEVAL:
		अणु
			काष्ठा old_समयval32 rtv;

			rtv.tv_sec = rts.tv_sec;
			rtv.tv_usec = rts.tv_nsec / NSEC_PER_USEC;
			अगर (!copy_to_user(p, &rtv, माप(rtv)))
				वापस ret;
		पूर्ण
		अवरोध;
	हाल PT_TIMESPEC:
		अगर (!put_बारpec64(&rts, p))
			वापस ret;
		अवरोध;
	हाल PT_OLD_TIMESPEC:
		अगर (!put_old_बारpec32(&rts, p))
			वापस ret;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	/*
	 * If an application माला_दो its समयval in पढ़ो-only memory, we
	 * करोn't want the Linux-specअगरic update to the समयval to
	 * cause a fault after the select has completed
	 * successfully. However, because we're not updating the
	 * समयval, we can't restart the प्रणाली call.
	 */

sticky:
	अगर (ret == -ERESTARTNOHAND)
		ret = -EINTR;
	वापस ret;
पूर्ण

/*
 * Scalable version of the fd_set.
 */

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ *in, *out, *ex;
	अचिन्हित दीर्घ *res_in, *res_out, *res_ex;
पूर्ण fd_set_bits;

/*
 * How many दीर्घwords क्रम "nr" bits?
 */
#घोषणा FDS_BITPERLONG	(8*माप(दीर्घ))
#घोषणा FDS_LONGS(nr)	(((nr)+FDS_BITPERLONG-1)/FDS_BITPERLONG)
#घोषणा FDS_BYTES(nr)	(FDS_LONGS(nr)*माप(दीर्घ))

/*
 * Use "unsigned long" accesses to let user-mode fd_set's be दीर्घ-aligned.
 */
अटल अंतरभूत
पूर्णांक get_fd_set(अचिन्हित दीर्घ nr, व्योम __user *ufdset, अचिन्हित दीर्घ *fdset)
अणु
	nr = FDS_BYTES(nr);
	अगर (ufdset)
		वापस copy_from_user(fdset, ufdset, nr) ? -EFAULT : 0;

	स_रखो(fdset, 0, nr);
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __must_check
set_fd_set(अचिन्हित दीर्घ nr, व्योम __user *ufdset, अचिन्हित दीर्घ *fdset)
अणु
	अगर (ufdset)
		वापस __copy_to_user(ufdset, fdset, FDS_BYTES(nr));
	वापस 0;
पूर्ण

अटल अंतरभूत
व्योम zero_fd_set(अचिन्हित दीर्घ nr, अचिन्हित दीर्घ *fdset)
अणु
	स_रखो(fdset, 0, FDS_BYTES(nr));
पूर्ण

#घोषणा FDS_IN(fds, n)		(fds->in + n)
#घोषणा FDS_OUT(fds, n)		(fds->out + n)
#घोषणा FDS_EX(fds, n)		(fds->ex + n)

#घोषणा BITS(fds, n)	(*FDS_IN(fds, n)|*FDS_OUT(fds, n)|*FDS_EX(fds, n))

अटल पूर्णांक max_select_fd(अचिन्हित दीर्घ n, fd_set_bits *fds)
अणु
	अचिन्हित दीर्घ *खोलो_fds;
	अचिन्हित दीर्घ set;
	पूर्णांक max;
	काष्ठा fdtable *fdt;

	/* handle last in-complete दीर्घ-word first */
	set = ~(~0UL << (n & (BITS_PER_LONG-1)));
	n /= BITS_PER_LONG;
	fdt = files_fdtable(current->files);
	खोलो_fds = fdt->खोलो_fds + n;
	max = 0;
	अगर (set) अणु
		set &= BITS(fds, n);
		अगर (set) अणु
			अगर (!(set & ~*खोलो_fds))
				जाओ get_max;
			वापस -EBADF;
		पूर्ण
	पूर्ण
	जबतक (n) अणु
		खोलो_fds--;
		n--;
		set = BITS(fds, n);
		अगर (!set)
			जारी;
		अगर (set & ~*खोलो_fds)
			वापस -EBADF;
		अगर (max)
			जारी;
get_max:
		करो अणु
			max++;
			set >>= 1;
		पूर्ण जबतक (set);
		max += n * BITS_PER_LONG;
	पूर्ण

	वापस max;
पूर्ण

#घोषणा POLLIN_SET (EPOLLRDNORM | EPOLLRDBAND | EPOLLIN | EPOLLHUP | EPOLLERR)
#घोषणा POLLOUT_SET (EPOLLWRBAND | EPOLLWRNORM | EPOLLOUT | EPOLLERR)
#घोषणा POLLEX_SET (EPOLLPRI)

अटल अंतरभूत व्योम रुको_key_set(poll_table *रुको, अचिन्हित दीर्घ in,
				अचिन्हित दीर्घ out, अचिन्हित दीर्घ bit,
				__poll_t ll_flag)
अणु
	रुको->_key = POLLEX_SET | ll_flag;
	अगर (in & bit)
		रुको->_key |= POLLIN_SET;
	अगर (out & bit)
		रुको->_key |= POLLOUT_SET;
पूर्ण

अटल पूर्णांक करो_select(पूर्णांक n, fd_set_bits *fds, काष्ठा बारpec64 *end_समय)
अणु
	kसमय_प्रकार expire, *to = शून्य;
	काष्ठा poll_wqueues table;
	poll_table *रुको;
	पूर्णांक retval, i, समयd_out = 0;
	u64 slack = 0;
	__poll_t busy_flag = net_busy_loop_on() ? POLL_BUSY_LOOP : 0;
	अचिन्हित दीर्घ busy_start = 0;

	rcu_पढ़ो_lock();
	retval = max_select_fd(n, fds);
	rcu_पढ़ो_unlock();

	अगर (retval < 0)
		वापस retval;
	n = retval;

	poll_initरुको(&table);
	रुको = &table.pt;
	अगर (end_समय && !end_समय->tv_sec && !end_समय->tv_nsec) अणु
		रुको->_qproc = शून्य;
		समयd_out = 1;
	पूर्ण

	अगर (end_समय && !समयd_out)
		slack = select_estimate_accuracy(end_समय);

	retval = 0;
	क्रम (;;) अणु
		अचिन्हित दीर्घ *rinp, *routp, *rexp, *inp, *outp, *exp;
		bool can_busy_loop = false;

		inp = fds->in; outp = fds->out; exp = fds->ex;
		rinp = fds->res_in; routp = fds->res_out; rexp = fds->res_ex;

		क्रम (i = 0; i < n; ++rinp, ++routp, ++rexp) अणु
			अचिन्हित दीर्घ in, out, ex, all_bits, bit = 1, j;
			अचिन्हित दीर्घ res_in = 0, res_out = 0, res_ex = 0;
			__poll_t mask;

			in = *inp++; out = *outp++; ex = *exp++;
			all_bits = in | out | ex;
			अगर (all_bits == 0) अणु
				i += BITS_PER_LONG;
				जारी;
			पूर्ण

			क्रम (j = 0; j < BITS_PER_LONG; ++j, ++i, bit <<= 1) अणु
				काष्ठा fd f;
				अगर (i >= n)
					अवरोध;
				अगर (!(bit & all_bits))
					जारी;
				f = fdget(i);
				अगर (f.file) अणु
					रुको_key_set(रुको, in, out, bit,
						     busy_flag);
					mask = vfs_poll(f.file, रुको);

					fdput(f);
					अगर ((mask & POLLIN_SET) && (in & bit)) अणु
						res_in |= bit;
						retval++;
						रुको->_qproc = शून्य;
					पूर्ण
					अगर ((mask & POLLOUT_SET) && (out & bit)) अणु
						res_out |= bit;
						retval++;
						रुको->_qproc = शून्य;
					पूर्ण
					अगर ((mask & POLLEX_SET) && (ex & bit)) अणु
						res_ex |= bit;
						retval++;
						रुको->_qproc = शून्य;
					पूर्ण
					/* got something, stop busy polling */
					अगर (retval) अणु
						can_busy_loop = false;
						busy_flag = 0;

					/*
					 * only remember a वापसed
					 * POLL_BUSY_LOOP अगर we asked क्रम it
					 */
					पूर्ण अन्यथा अगर (busy_flag & mask)
						can_busy_loop = true;

				पूर्ण
			पूर्ण
			अगर (res_in)
				*rinp = res_in;
			अगर (res_out)
				*routp = res_out;
			अगर (res_ex)
				*rexp = res_ex;
			cond_resched();
		पूर्ण
		रुको->_qproc = शून्य;
		अगर (retval || समयd_out || संकेत_pending(current))
			अवरोध;
		अगर (table.error) अणु
			retval = table.error;
			अवरोध;
		पूर्ण

		/* only अगर found POLL_BUSY_LOOP sockets && not out of समय */
		अगर (can_busy_loop && !need_resched()) अणु
			अगर (!busy_start) अणु
				busy_start = busy_loop_current_समय();
				जारी;
			पूर्ण
			अगर (!busy_loop_समयout(busy_start))
				जारी;
		पूर्ण
		busy_flag = 0;

		/*
		 * If this is the first loop and we have a समयout
		 * given, then we convert to kसमय_प्रकार and set the to
		 * poपूर्णांकer to the expiry value.
		 */
		अगर (end_समय && !to) अणु
			expire = बारpec64_to_kसमय(*end_समय);
			to = &expire;
		पूर्ण

		अगर (!poll_schedule_समयout(&table, TASK_INTERRUPTIBLE,
					   to, slack))
			समयd_out = 1;
	पूर्ण

	poll_मुक्तरुको(&table);

	वापस retval;
पूर्ण

/*
 * We can actually वापस ERESTARTSYS instead of EINTR, but I'd
 * like to be certain this leads to no problems. So I वापस
 * EINTR just क्रम safety.
 *
 * Update: ERESTARTSYS अवरोधs at least the xview घड़ी binary, so
 * I'm trying ERESTARTNOHAND which restart only when you want to.
 */
पूर्णांक core_sys_select(पूर्णांक n, fd_set __user *inp, fd_set __user *outp,
			   fd_set __user *exp, काष्ठा बारpec64 *end_समय)
अणु
	fd_set_bits fds;
	व्योम *bits;
	पूर्णांक ret, max_fds;
	माप_प्रकार size, alloc_size;
	काष्ठा fdtable *fdt;
	/* Allocate small arguments on the stack to save memory and be faster */
	दीर्घ stack_fds[SELECT_STACK_ALLOC/माप(दीर्घ)];

	ret = -EINVAL;
	अगर (n < 0)
		जाओ out_nofds;

	/* max_fds can increase, so grab it once to aव्योम race */
	rcu_पढ़ो_lock();
	fdt = files_fdtable(current->files);
	max_fds = fdt->max_fds;
	rcu_पढ़ो_unlock();
	अगर (n > max_fds)
		n = max_fds;

	/*
	 * We need 6 biपंचांगaps (in/out/ex क्रम both incoming and outgoing),
	 * since we used fdset we need to allocate memory in units of
	 * दीर्घ-words. 
	 */
	size = FDS_BYTES(n);
	bits = stack_fds;
	अगर (size > माप(stack_fds) / 6) अणु
		/* Not enough space in on-stack array; must use kदो_स्मृति */
		ret = -ENOMEM;
		अगर (size > (SIZE_MAX / 6))
			जाओ out_nofds;

		alloc_size = 6 * size;
		bits = kvदो_स्मृति(alloc_size, GFP_KERNEL);
		अगर (!bits)
			जाओ out_nofds;
	पूर्ण
	fds.in      = bits;
	fds.out     = bits +   size;
	fds.ex      = bits + 2*size;
	fds.res_in  = bits + 3*size;
	fds.res_out = bits + 4*size;
	fds.res_ex  = bits + 5*size;

	अगर ((ret = get_fd_set(n, inp, fds.in)) ||
	    (ret = get_fd_set(n, outp, fds.out)) ||
	    (ret = get_fd_set(n, exp, fds.ex)))
		जाओ out;
	zero_fd_set(n, fds.res_in);
	zero_fd_set(n, fds.res_out);
	zero_fd_set(n, fds.res_ex);

	ret = करो_select(n, &fds, end_समय);

	अगर (ret < 0)
		जाओ out;
	अगर (!ret) अणु
		ret = -ERESTARTNOHAND;
		अगर (संकेत_pending(current))
			जाओ out;
		ret = 0;
	पूर्ण

	अगर (set_fd_set(n, inp, fds.res_in) ||
	    set_fd_set(n, outp, fds.res_out) ||
	    set_fd_set(n, exp, fds.res_ex))
		ret = -EFAULT;

out:
	अगर (bits != stack_fds)
		kvमुक्त(bits);
out_nofds:
	वापस ret;
पूर्ण

अटल पूर्णांक kern_select(पूर्णांक n, fd_set __user *inp, fd_set __user *outp,
		       fd_set __user *exp, काष्ठा __kernel_old_समयval __user *tvp)
अणु
	काष्ठा बारpec64 end_समय, *to = शून्य;
	काष्ठा __kernel_old_समयval tv;
	पूर्णांक ret;

	अगर (tvp) अणु
		अगर (copy_from_user(&tv, tvp, माप(tv)))
			वापस -EFAULT;

		to = &end_समय;
		अगर (poll_select_set_समयout(to,
				tv.tv_sec + (tv.tv_usec / USEC_PER_SEC),
				(tv.tv_usec % USEC_PER_SEC) * NSEC_PER_USEC))
			वापस -EINVAL;
	पूर्ण

	ret = core_sys_select(n, inp, outp, exp, to);
	वापस poll_select_finish(&end_समय, tvp, PT_TIMEVAL, ret);
पूर्ण

SYSCALL_DEFINE5(select, पूर्णांक, n, fd_set __user *, inp, fd_set __user *, outp,
		fd_set __user *, exp, काष्ठा __kernel_old_समयval __user *, tvp)
अणु
	वापस kern_select(n, inp, outp, exp, tvp);
पूर्ण

अटल दीर्घ करो_pselect(पूर्णांक n, fd_set __user *inp, fd_set __user *outp,
		       fd_set __user *exp, व्योम __user *tsp,
		       स्थिर sigset_t __user *sigmask, माप_प्रकार sigsetsize,
		       क्रमागत poll_समय_प्रकारype type)
अणु
	काष्ठा बारpec64 ts, end_समय, *to = शून्य;
	पूर्णांक ret;

	अगर (tsp) अणु
		चयन (type) अणु
		हाल PT_TIMESPEC:
			अगर (get_बारpec64(&ts, tsp))
				वापस -EFAULT;
			अवरोध;
		हाल PT_OLD_TIMESPEC:
			अगर (get_old_बारpec32(&ts, tsp))
				वापस -EFAULT;
			अवरोध;
		शेष:
			BUG();
		पूर्ण

		to = &end_समय;
		अगर (poll_select_set_समयout(to, ts.tv_sec, ts.tv_nsec))
			वापस -EINVAL;
	पूर्ण

	ret = set_user_sigmask(sigmask, sigsetsize);
	अगर (ret)
		वापस ret;

	ret = core_sys_select(n, inp, outp, exp, to);
	वापस poll_select_finish(&end_समय, tsp, type, ret);
पूर्ण

/*
 * Most architectures can't handle 7-argument syscalls. So we provide a
 * 6-argument version where the sixth argument is a poपूर्णांकer to a काष्ठाure
 * which has a poपूर्णांकer to the sigset_t itself followed by a माप_प्रकार containing
 * the sigset size.
 */
काष्ठा sigset_argpack अणु
	sigset_t __user *p;
	माप_प्रकार size;
पूर्ण;

अटल अंतरभूत पूर्णांक get_sigset_argpack(काष्ठा sigset_argpack *to,
				     काष्ठा sigset_argpack __user *from)
अणु
	// the path is hot enough क्रम overhead of copy_from_user() to matter
	अगर (from) अणु
		अगर (!user_पढ़ो_access_begin(from, माप(*from)))
			वापस -EFAULT;
		unsafe_get_user(to->p, &from->p, Efault);
		unsafe_get_user(to->size, &from->size, Efault);
		user_पढ़ो_access_end();
	पूर्ण
	वापस 0;
Efault:
	user_access_end();
	वापस -EFAULT;
पूर्ण

SYSCALL_DEFINE6(pselect6, पूर्णांक, n, fd_set __user *, inp, fd_set __user *, outp,
		fd_set __user *, exp, काष्ठा __kernel_बारpec __user *, tsp,
		व्योम __user *, sig)
अणु
	काष्ठा sigset_argpack x = अणुशून्य, 0पूर्ण;

	अगर (get_sigset_argpack(&x, sig))
		वापस -EFAULT;

	वापस करो_pselect(n, inp, outp, exp, tsp, x.p, x.size, PT_TIMESPEC);
पूर्ण

#अगर defined(CONFIG_COMPAT_32BIT_TIME) && !defined(CONFIG_64BIT)

SYSCALL_DEFINE6(pselect6_समय32, पूर्णांक, n, fd_set __user *, inp, fd_set __user *, outp,
		fd_set __user *, exp, काष्ठा old_बारpec32 __user *, tsp,
		व्योम __user *, sig)
अणु
	काष्ठा sigset_argpack x = अणुशून्य, 0पूर्ण;

	अगर (get_sigset_argpack(&x, sig))
		वापस -EFAULT;

	वापस करो_pselect(n, inp, outp, exp, tsp, x.p, x.size, PT_OLD_TIMESPEC);
पूर्ण

#पूर्ण_अगर

#अगर_घोषित __ARCH_WANT_SYS_OLD_SELECT
काष्ठा sel_arg_काष्ठा अणु
	अचिन्हित दीर्घ n;
	fd_set __user *inp, *outp, *exp;
	काष्ठा __kernel_old_समयval __user *tvp;
पूर्ण;

SYSCALL_DEFINE1(old_select, काष्ठा sel_arg_काष्ठा __user *, arg)
अणु
	काष्ठा sel_arg_काष्ठा a;

	अगर (copy_from_user(&a, arg, माप(a)))
		वापस -EFAULT;
	वापस kern_select(a.n, a.inp, a.outp, a.exp, a.tvp);
पूर्ण
#पूर्ण_अगर

काष्ठा poll_list अणु
	काष्ठा poll_list *next;
	पूर्णांक len;
	काष्ठा pollfd entries[];
पूर्ण;

#घोषणा POLLFD_PER_PAGE  ((PAGE_SIZE-माप(काष्ठा poll_list)) / माप(काष्ठा pollfd))

/*
 * Fish क्रम pollable events on the pollfd->fd file descriptor. We're only
 * पूर्णांकerested in events matching the pollfd->events mask, and the result
 * matching that mask is both recorded in pollfd->revents and वापसed. The
 * pरुको poll_table will be used by the fd-provided poll handler क्रम रुकोing,
 * अगर pरुको->_qproc is non-शून्य.
 */
अटल अंतरभूत __poll_t करो_pollfd(काष्ठा pollfd *pollfd, poll_table *pरुको,
				     bool *can_busy_poll,
				     __poll_t busy_flag)
अणु
	पूर्णांक fd = pollfd->fd;
	__poll_t mask = 0, filter;
	काष्ठा fd f;

	अगर (fd < 0)
		जाओ out;
	mask = EPOLLNVAL;
	f = fdget(fd);
	अगर (!f.file)
		जाओ out;

	/* userland u16 ->events contains POLL... biपंचांगap */
	filter = demangle_poll(pollfd->events) | EPOLLERR | EPOLLHUP;
	pरुको->_key = filter | busy_flag;
	mask = vfs_poll(f.file, pरुको);
	अगर (mask & busy_flag)
		*can_busy_poll = true;
	mask &= filter;		/* Mask out unneeded events. */
	fdput(f);

out:
	/* ... and so करोes ->revents */
	pollfd->revents = mangle_poll(mask);
	वापस mask;
पूर्ण

अटल पूर्णांक करो_poll(काष्ठा poll_list *list, काष्ठा poll_wqueues *रुको,
		   काष्ठा बारpec64 *end_समय)
अणु
	poll_table* pt = &रुको->pt;
	kसमय_प्रकार expire, *to = शून्य;
	पूर्णांक समयd_out = 0, count = 0;
	u64 slack = 0;
	__poll_t busy_flag = net_busy_loop_on() ? POLL_BUSY_LOOP : 0;
	अचिन्हित दीर्घ busy_start = 0;

	/* Optimise the no-रुको हाल */
	अगर (end_समय && !end_समय->tv_sec && !end_समय->tv_nsec) अणु
		pt->_qproc = शून्य;
		समयd_out = 1;
	पूर्ण

	अगर (end_समय && !समयd_out)
		slack = select_estimate_accuracy(end_समय);

	क्रम (;;) अणु
		काष्ठा poll_list *walk;
		bool can_busy_loop = false;

		क्रम (walk = list; walk != शून्य; walk = walk->next) अणु
			काष्ठा pollfd * pfd, * pfd_end;

			pfd = walk->entries;
			pfd_end = pfd + walk->len;
			क्रम (; pfd != pfd_end; pfd++) अणु
				/*
				 * Fish क्रम events. If we found one, record it
				 * and समाप्त poll_table->_qproc, so we करोn't
				 * needlessly रेजिस्टर any other रुकोers after
				 * this. They'll get immediately deरेजिस्टरed
				 * when we अवरोध out and वापस.
				 */
				अगर (करो_pollfd(pfd, pt, &can_busy_loop,
					      busy_flag)) अणु
					count++;
					pt->_qproc = शून्य;
					/* found something, stop busy polling */
					busy_flag = 0;
					can_busy_loop = false;
				पूर्ण
			पूर्ण
		पूर्ण
		/*
		 * All रुकोers have alपढ़ोy been रेजिस्टरed, so करोn't provide
		 * a poll_table->_qproc to them on the next loop iteration.
		 */
		pt->_qproc = शून्य;
		अगर (!count) अणु
			count = रुको->error;
			अगर (संकेत_pending(current))
				count = -ERESTARTNOHAND;
		पूर्ण
		अगर (count || समयd_out)
			अवरोध;

		/* only अगर found POLL_BUSY_LOOP sockets && not out of समय */
		अगर (can_busy_loop && !need_resched()) अणु
			अगर (!busy_start) अणु
				busy_start = busy_loop_current_समय();
				जारी;
			पूर्ण
			अगर (!busy_loop_समयout(busy_start))
				जारी;
		पूर्ण
		busy_flag = 0;

		/*
		 * If this is the first loop and we have a समयout
		 * given, then we convert to kसमय_प्रकार and set the to
		 * poपूर्णांकer to the expiry value.
		 */
		अगर (end_समय && !to) अणु
			expire = बारpec64_to_kसमय(*end_समय);
			to = &expire;
		पूर्ण

		अगर (!poll_schedule_समयout(रुको, TASK_INTERRUPTIBLE, to, slack))
			समयd_out = 1;
	पूर्ण
	वापस count;
पूर्ण

#घोषणा N_STACK_PPS ((माप(stack_pps) - माप(काष्ठा poll_list))  / \
			माप(काष्ठा pollfd))

अटल पूर्णांक करो_sys_poll(काष्ठा pollfd __user *ufds, अचिन्हित पूर्णांक nfds,
		काष्ठा बारpec64 *end_समय)
अणु
	काष्ठा poll_wqueues table;
	पूर्णांक err = -EFAULT, fdcount, len;
	/* Allocate small arguments on the stack to save memory and be
	   faster - use दीर्घ to make sure the buffer is aligned properly
	   on 64 bit archs to aव्योम unaligned access */
	दीर्घ stack_pps[POLL_STACK_ALLOC/माप(दीर्घ)];
	काष्ठा poll_list *स्थिर head = (काष्ठा poll_list *)stack_pps;
 	काष्ठा poll_list *walk = head;
 	अचिन्हित दीर्घ toकरो = nfds;

	अगर (nfds > rlimit(RLIMIT_NOखाता))
		वापस -EINVAL;

	len = min_t(अचिन्हित पूर्णांक, nfds, N_STACK_PPS);
	क्रम (;;) अणु
		walk->next = शून्य;
		walk->len = len;
		अगर (!len)
			अवरोध;

		अगर (copy_from_user(walk->entries, ufds + nfds-toकरो,
					माप(काष्ठा pollfd) * walk->len))
			जाओ out_fds;

		toकरो -= walk->len;
		अगर (!toकरो)
			अवरोध;

		len = min(toकरो, POLLFD_PER_PAGE);
		walk = walk->next = kदो_स्मृति(काष्ठा_size(walk, entries, len),
					    GFP_KERNEL);
		अगर (!walk) अणु
			err = -ENOMEM;
			जाओ out_fds;
		पूर्ण
	पूर्ण

	poll_initरुको(&table);
	fdcount = करो_poll(head, &table, end_समय);
	poll_मुक्तरुको(&table);

	अगर (!user_ग_लिखो_access_begin(ufds, nfds * माप(*ufds)))
		जाओ out_fds;

	क्रम (walk = head; walk; walk = walk->next) अणु
		काष्ठा pollfd *fds = walk->entries;
		पूर्णांक j;

		क्रम (j = walk->len; j; fds++, ufds++, j--)
			unsafe_put_user(fds->revents, &ufds->revents, Efault);
  	पूर्ण
	user_ग_लिखो_access_end();

	err = fdcount;
out_fds:
	walk = head->next;
	जबतक (walk) अणु
		काष्ठा poll_list *pos = walk;
		walk = walk->next;
		kमुक्त(pos);
	पूर्ण

	वापस err;

Efault:
	user_ग_लिखो_access_end();
	err = -EFAULT;
	जाओ out_fds;
पूर्ण

अटल दीर्घ करो_restart_poll(काष्ठा restart_block *restart_block)
अणु
	काष्ठा pollfd __user *ufds = restart_block->poll.ufds;
	पूर्णांक nfds = restart_block->poll.nfds;
	काष्ठा बारpec64 *to = शून्य, end_समय;
	पूर्णांक ret;

	अगर (restart_block->poll.has_समयout) अणु
		end_समय.tv_sec = restart_block->poll.tv_sec;
		end_समय.tv_nsec = restart_block->poll.tv_nsec;
		to = &end_समय;
	पूर्ण

	ret = करो_sys_poll(ufds, nfds, to);

	अगर (ret == -ERESTARTNOHAND)
		ret = set_restart_fn(restart_block, करो_restart_poll);

	वापस ret;
पूर्ण

SYSCALL_DEFINE3(poll, काष्ठा pollfd __user *, ufds, अचिन्हित पूर्णांक, nfds,
		पूर्णांक, समयout_msecs)
अणु
	काष्ठा बारpec64 end_समय, *to = शून्य;
	पूर्णांक ret;

	अगर (समयout_msecs >= 0) अणु
		to = &end_समय;
		poll_select_set_समयout(to, समयout_msecs / MSEC_PER_SEC,
			NSEC_PER_MSEC * (समयout_msecs % MSEC_PER_SEC));
	पूर्ण

	ret = करो_sys_poll(ufds, nfds, to);

	अगर (ret == -ERESTARTNOHAND) अणु
		काष्ठा restart_block *restart_block;

		restart_block = &current->restart_block;
		restart_block->poll.ufds = ufds;
		restart_block->poll.nfds = nfds;

		अगर (समयout_msecs >= 0) अणु
			restart_block->poll.tv_sec = end_समय.tv_sec;
			restart_block->poll.tv_nsec = end_समय.tv_nsec;
			restart_block->poll.has_समयout = 1;
		पूर्ण अन्यथा
			restart_block->poll.has_समयout = 0;

		ret = set_restart_fn(restart_block, करो_restart_poll);
	पूर्ण
	वापस ret;
पूर्ण

SYSCALL_DEFINE5(ppoll, काष्ठा pollfd __user *, ufds, अचिन्हित पूर्णांक, nfds,
		काष्ठा __kernel_बारpec __user *, tsp, स्थिर sigset_t __user *, sigmask,
		माप_प्रकार, sigsetsize)
अणु
	काष्ठा बारpec64 ts, end_समय, *to = शून्य;
	पूर्णांक ret;

	अगर (tsp) अणु
		अगर (get_बारpec64(&ts, tsp))
			वापस -EFAULT;

		to = &end_समय;
		अगर (poll_select_set_समयout(to, ts.tv_sec, ts.tv_nsec))
			वापस -EINVAL;
	पूर्ण

	ret = set_user_sigmask(sigmask, sigsetsize);
	अगर (ret)
		वापस ret;

	ret = करो_sys_poll(ufds, nfds, to);
	वापस poll_select_finish(&end_समय, tsp, PT_TIMESPEC, ret);
पूर्ण

#अगर defined(CONFIG_COMPAT_32BIT_TIME) && !defined(CONFIG_64BIT)

SYSCALL_DEFINE5(ppoll_समय32, काष्ठा pollfd __user *, ufds, अचिन्हित पूर्णांक, nfds,
		काष्ठा old_बारpec32 __user *, tsp, स्थिर sigset_t __user *, sigmask,
		माप_प्रकार, sigsetsize)
अणु
	काष्ठा बारpec64 ts, end_समय, *to = शून्य;
	पूर्णांक ret;

	अगर (tsp) अणु
		अगर (get_old_बारpec32(&ts, tsp))
			वापस -EFAULT;

		to = &end_समय;
		अगर (poll_select_set_समयout(to, ts.tv_sec, ts.tv_nsec))
			वापस -EINVAL;
	पूर्ण

	ret = set_user_sigmask(sigmask, sigsetsize);
	अगर (ret)
		वापस ret;

	ret = करो_sys_poll(ufds, nfds, to);
	वापस poll_select_finish(&end_समय, tsp, PT_OLD_TIMESPEC, ret);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPAT
#घोषणा __COMPAT_NFDBITS       (8 * माप(compat_uदीर्घ_t))

/*
 * Ooo, nasty.  We need here to frob 32-bit अचिन्हित दीर्घs to
 * 64-bit अचिन्हित दीर्घs.
 */
अटल
पूर्णांक compat_get_fd_set(अचिन्हित दीर्घ nr, compat_uदीर्घ_t __user *ufdset,
			अचिन्हित दीर्घ *fdset)
अणु
	अगर (ufdset) अणु
		वापस compat_get_biपंचांगap(fdset, ufdset, nr);
	पूर्ण अन्यथा अणु
		zero_fd_set(nr, fdset);
		वापस 0;
	पूर्ण
पूर्ण

अटल
पूर्णांक compat_set_fd_set(अचिन्हित दीर्घ nr, compat_uदीर्घ_t __user *ufdset,
		      अचिन्हित दीर्घ *fdset)
अणु
	अगर (!ufdset)
		वापस 0;
	वापस compat_put_biपंचांगap(ufdset, fdset, nr);
पूर्ण


/*
 * This is a भव copy of sys_select from fs/select.c and probably
 * should be compared to it from समय to समय
 */

/*
 * We can actually वापस ERESTARTSYS instead of EINTR, but I'd
 * like to be certain this leads to no problems. So I वापस
 * EINTR just क्रम safety.
 *
 * Update: ERESTARTSYS अवरोधs at least the xview घड़ी binary, so
 * I'm trying ERESTARTNOHAND which restart only when you want to.
 */
अटल पूर्णांक compat_core_sys_select(पूर्णांक n, compat_uदीर्घ_t __user *inp,
	compat_uदीर्घ_t __user *outp, compat_uदीर्घ_t __user *exp,
	काष्ठा बारpec64 *end_समय)
अणु
	fd_set_bits fds;
	व्योम *bits;
	पूर्णांक size, max_fds, ret = -EINVAL;
	काष्ठा fdtable *fdt;
	दीर्घ stack_fds[SELECT_STACK_ALLOC/माप(दीर्घ)];

	अगर (n < 0)
		जाओ out_nofds;

	/* max_fds can increase, so grab it once to aव्योम race */
	rcu_पढ़ो_lock();
	fdt = files_fdtable(current->files);
	max_fds = fdt->max_fds;
	rcu_पढ़ो_unlock();
	अगर (n > max_fds)
		n = max_fds;

	/*
	 * We need 6 biपंचांगaps (in/out/ex क्रम both incoming and outgoing),
	 * since we used fdset we need to allocate memory in units of
	 * दीर्घ-words.
	 */
	size = FDS_BYTES(n);
	bits = stack_fds;
	अगर (size > माप(stack_fds) / 6) अणु
		bits = kदो_स्मृति_array(6, size, GFP_KERNEL);
		ret = -ENOMEM;
		अगर (!bits)
			जाओ out_nofds;
	पूर्ण
	fds.in      = (अचिन्हित दीर्घ *)  bits;
	fds.out     = (अचिन्हित दीर्घ *) (bits +   size);
	fds.ex      = (अचिन्हित दीर्घ *) (bits + 2*size);
	fds.res_in  = (अचिन्हित दीर्घ *) (bits + 3*size);
	fds.res_out = (अचिन्हित दीर्घ *) (bits + 4*size);
	fds.res_ex  = (अचिन्हित दीर्घ *) (bits + 5*size);

	अगर ((ret = compat_get_fd_set(n, inp, fds.in)) ||
	    (ret = compat_get_fd_set(n, outp, fds.out)) ||
	    (ret = compat_get_fd_set(n, exp, fds.ex)))
		जाओ out;
	zero_fd_set(n, fds.res_in);
	zero_fd_set(n, fds.res_out);
	zero_fd_set(n, fds.res_ex);

	ret = करो_select(n, &fds, end_समय);

	अगर (ret < 0)
		जाओ out;
	अगर (!ret) अणु
		ret = -ERESTARTNOHAND;
		अगर (संकेत_pending(current))
			जाओ out;
		ret = 0;
	पूर्ण

	अगर (compat_set_fd_set(n, inp, fds.res_in) ||
	    compat_set_fd_set(n, outp, fds.res_out) ||
	    compat_set_fd_set(n, exp, fds.res_ex))
		ret = -EFAULT;
out:
	अगर (bits != stack_fds)
		kमुक्त(bits);
out_nofds:
	वापस ret;
पूर्ण

अटल पूर्णांक करो_compat_select(पूर्णांक n, compat_uदीर्घ_t __user *inp,
	compat_uदीर्घ_t __user *outp, compat_uदीर्घ_t __user *exp,
	काष्ठा old_समयval32 __user *tvp)
अणु
	काष्ठा बारpec64 end_समय, *to = शून्य;
	काष्ठा old_समयval32 tv;
	पूर्णांक ret;

	अगर (tvp) अणु
		अगर (copy_from_user(&tv, tvp, माप(tv)))
			वापस -EFAULT;

		to = &end_समय;
		अगर (poll_select_set_समयout(to,
				tv.tv_sec + (tv.tv_usec / USEC_PER_SEC),
				(tv.tv_usec % USEC_PER_SEC) * NSEC_PER_USEC))
			वापस -EINVAL;
	पूर्ण

	ret = compat_core_sys_select(n, inp, outp, exp, to);
	वापस poll_select_finish(&end_समय, tvp, PT_OLD_TIMEVAL, ret);
पूर्ण

COMPAT_SYSCALL_DEFINE5(select, पूर्णांक, n, compat_uदीर्घ_t __user *, inp,
	compat_uदीर्घ_t __user *, outp, compat_uदीर्घ_t __user *, exp,
	काष्ठा old_समयval32 __user *, tvp)
अणु
	वापस करो_compat_select(n, inp, outp, exp, tvp);
पूर्ण

काष्ठा compat_sel_arg_काष्ठा अणु
	compat_uदीर्घ_t n;
	compat_uptr_t inp;
	compat_uptr_t outp;
	compat_uptr_t exp;
	compat_uptr_t tvp;
पूर्ण;

COMPAT_SYSCALL_DEFINE1(old_select, काष्ठा compat_sel_arg_काष्ठा __user *, arg)
अणु
	काष्ठा compat_sel_arg_काष्ठा a;

	अगर (copy_from_user(&a, arg, माप(a)))
		वापस -EFAULT;
	वापस करो_compat_select(a.n, compat_ptr(a.inp), compat_ptr(a.outp),
				compat_ptr(a.exp), compat_ptr(a.tvp));
पूर्ण

अटल दीर्घ करो_compat_pselect(पूर्णांक n, compat_uदीर्घ_t __user *inp,
	compat_uदीर्घ_t __user *outp, compat_uदीर्घ_t __user *exp,
	व्योम __user *tsp, compat_sigset_t __user *sigmask,
	compat_माप_प्रकार sigsetsize, क्रमागत poll_समय_प्रकारype type)
अणु
	काष्ठा बारpec64 ts, end_समय, *to = शून्य;
	पूर्णांक ret;

	अगर (tsp) अणु
		चयन (type) अणु
		हाल PT_OLD_TIMESPEC:
			अगर (get_old_बारpec32(&ts, tsp))
				वापस -EFAULT;
			अवरोध;
		हाल PT_TIMESPEC:
			अगर (get_बारpec64(&ts, tsp))
				वापस -EFAULT;
			अवरोध;
		शेष:
			BUG();
		पूर्ण

		to = &end_समय;
		अगर (poll_select_set_समयout(to, ts.tv_sec, ts.tv_nsec))
			वापस -EINVAL;
	पूर्ण

	ret = set_compat_user_sigmask(sigmask, sigsetsize);
	अगर (ret)
		वापस ret;

	ret = compat_core_sys_select(n, inp, outp, exp, to);
	वापस poll_select_finish(&end_समय, tsp, type, ret);
पूर्ण

काष्ठा compat_sigset_argpack अणु
	compat_uptr_t p;
	compat_माप_प्रकार size;
पूर्ण;
अटल अंतरभूत पूर्णांक get_compat_sigset_argpack(काष्ठा compat_sigset_argpack *to,
					    काष्ठा compat_sigset_argpack __user *from)
अणु
	अगर (from) अणु
		अगर (!user_पढ़ो_access_begin(from, माप(*from)))
			वापस -EFAULT;
		unsafe_get_user(to->p, &from->p, Efault);
		unsafe_get_user(to->size, &from->size, Efault);
		user_पढ़ो_access_end();
	पूर्ण
	वापस 0;
Efault:
	user_access_end();
	वापस -EFAULT;
पूर्ण

COMPAT_SYSCALL_DEFINE6(pselect6_समय64, पूर्णांक, n, compat_uदीर्घ_t __user *, inp,
	compat_uदीर्घ_t __user *, outp, compat_uदीर्घ_t __user *, exp,
	काष्ठा __kernel_बारpec __user *, tsp, व्योम __user *, sig)
अणु
	काष्ठा compat_sigset_argpack x = अणु0, 0पूर्ण;

	अगर (get_compat_sigset_argpack(&x, sig))
		वापस -EFAULT;

	वापस करो_compat_pselect(n, inp, outp, exp, tsp, compat_ptr(x.p),
				 x.size, PT_TIMESPEC);
पूर्ण

#अगर defined(CONFIG_COMPAT_32BIT_TIME)

COMPAT_SYSCALL_DEFINE6(pselect6_समय32, पूर्णांक, n, compat_uदीर्घ_t __user *, inp,
	compat_uदीर्घ_t __user *, outp, compat_uदीर्घ_t __user *, exp,
	काष्ठा old_बारpec32 __user *, tsp, व्योम __user *, sig)
अणु
	काष्ठा compat_sigset_argpack x = अणु0, 0पूर्ण;

	अगर (get_compat_sigset_argpack(&x, sig))
		वापस -EFAULT;

	वापस करो_compat_pselect(n, inp, outp, exp, tsp, compat_ptr(x.p),
				 x.size, PT_OLD_TIMESPEC);
पूर्ण

#पूर्ण_अगर

#अगर defined(CONFIG_COMPAT_32BIT_TIME)
COMPAT_SYSCALL_DEFINE5(ppoll_समय32, काष्ठा pollfd __user *, ufds,
	अचिन्हित पूर्णांक,  nfds, काष्ठा old_बारpec32 __user *, tsp,
	स्थिर compat_sigset_t __user *, sigmask, compat_माप_प्रकार, sigsetsize)
अणु
	काष्ठा बारpec64 ts, end_समय, *to = शून्य;
	पूर्णांक ret;

	अगर (tsp) अणु
		अगर (get_old_बारpec32(&ts, tsp))
			वापस -EFAULT;

		to = &end_समय;
		अगर (poll_select_set_समयout(to, ts.tv_sec, ts.tv_nsec))
			वापस -EINVAL;
	पूर्ण

	ret = set_compat_user_sigmask(sigmask, sigsetsize);
	अगर (ret)
		वापस ret;

	ret = करो_sys_poll(ufds, nfds, to);
	वापस poll_select_finish(&end_समय, tsp, PT_OLD_TIMESPEC, ret);
पूर्ण
#पूर्ण_अगर

/* New compat syscall क्रम 64 bit समय_प्रकार*/
COMPAT_SYSCALL_DEFINE5(ppoll_समय64, काष्ठा pollfd __user *, ufds,
	अचिन्हित पूर्णांक,  nfds, काष्ठा __kernel_बारpec __user *, tsp,
	स्थिर compat_sigset_t __user *, sigmask, compat_माप_प्रकार, sigsetsize)
अणु
	काष्ठा बारpec64 ts, end_समय, *to = शून्य;
	पूर्णांक ret;

	अगर (tsp) अणु
		अगर (get_बारpec64(&ts, tsp))
			वापस -EFAULT;

		to = &end_समय;
		अगर (poll_select_set_समयout(to, ts.tv_sec, ts.tv_nsec))
			वापस -EINVAL;
	पूर्ण

	ret = set_compat_user_sigmask(sigmask, sigsetsize);
	अगर (ret)
		वापस ret;

	ret = करो_sys_poll(ufds, nfds, to);
	वापस poll_select_finish(&end_समय, tsp, PT_TIMESPEC, ret);
पूर्ण

#पूर्ण_अगर
