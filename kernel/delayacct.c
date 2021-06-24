<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* delayacct.c - per-task delay accounting
 *
 * Copyright (C) Shailabh Nagar, IBM Corp. 2006
 */

#समावेश <linux/sched.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/cpuसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/taskstats.h>
#समावेश <linux/समय.स>
#समावेश <linux/sysctl.h>
#समावेश <linux/delayacct.h>
#समावेश <linux/module.h>

पूर्णांक delayacct_on __पढ़ो_mostly = 1;	/* Delay accounting turned on/off */
EXPORT_SYMBOL_GPL(delayacct_on);
काष्ठा kmem_cache *delayacct_cache;

अटल पूर्णांक __init delayacct_setup_disable(अक्षर *str)
अणु
	delayacct_on = 0;
	वापस 1;
पूर्ण
__setup("nodelayacct", delayacct_setup_disable);

व्योम delayacct_init(व्योम)
अणु
	delayacct_cache = KMEM_CACHE(task_delay_info, SLAB_PANIC|SLAB_ACCOUNT);
	delayacct_tsk_init(&init_task);
पूर्ण

व्योम __delayacct_tsk_init(काष्ठा task_काष्ठा *tsk)
अणु
	tsk->delays = kmem_cache_zalloc(delayacct_cache, GFP_KERNEL);
	अगर (tsk->delays)
		raw_spin_lock_init(&tsk->delays->lock);
पूर्ण

/*
 * Finish delay accounting क्रम a statistic using its बारtamps (@start),
 * accumalator (@total) and @count
 */
अटल व्योम delayacct_end(raw_spinlock_t *lock, u64 *start, u64 *total,
			  u32 *count)
अणु
	s64 ns = kसमय_get_ns() - *start;
	अचिन्हित दीर्घ flags;

	अगर (ns > 0) अणु
		raw_spin_lock_irqsave(lock, flags);
		*total += ns;
		(*count)++;
		raw_spin_unlock_irqrestore(lock, flags);
	पूर्ण
पूर्ण

व्योम __delayacct_blkio_start(व्योम)
अणु
	current->delays->blkio_start = kसमय_get_ns();
पूर्ण

/*
 * We cannot rely on the `current` macro, as we haven't yet चयनed back to
 * the process being woken.
 */
व्योम __delayacct_blkio_end(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा task_delay_info *delays = p->delays;
	u64 *total;
	u32 *count;

	अगर (p->delays->flags & DELAYACCT_PF_SWAPIN) अणु
		total = &delays->swapin_delay;
		count = &delays->swapin_count;
	पूर्ण अन्यथा अणु
		total = &delays->blkio_delay;
		count = &delays->blkio_count;
	पूर्ण

	delayacct_end(&delays->lock, &delays->blkio_start, total, count);
पूर्ण

पूर्णांक __delayacct_add_tsk(काष्ठा taskstats *d, काष्ठा task_काष्ठा *tsk)
अणु
	u64 uसमय, sसमय, sबारcaled, uबारcaled;
	अचिन्हित दीर्घ दीर्घ t2, t3;
	अचिन्हित दीर्घ flags, t1;
	s64 पंचांगp;

	task_cpuसमय(tsk, &uसमय, &sसमय);
	पंचांगp = (s64)d->cpu_run_real_total;
	पंचांगp += uसमय + sसमय;
	d->cpu_run_real_total = (पंचांगp < (s64)d->cpu_run_real_total) ? 0 : पंचांगp;

	task_cpuसमय_scaled(tsk, &uबारcaled, &sबारcaled);
	पंचांगp = (s64)d->cpu_scaled_run_real_total;
	पंचांगp += uबारcaled + sबारcaled;
	d->cpu_scaled_run_real_total =
		(पंचांगp < (s64)d->cpu_scaled_run_real_total) ? 0 : पंचांगp;

	/*
	 * No locking available क्रम sched_info (and too expensive to add one)
	 * Mitigate by taking snapshot of values
	 */
	t1 = tsk->sched_info.pcount;
	t2 = tsk->sched_info.run_delay;
	t3 = tsk->se.sum_exec_runसमय;

	d->cpu_count += t1;

	पंचांगp = (s64)d->cpu_delay_total + t2;
	d->cpu_delay_total = (पंचांगp < (s64)d->cpu_delay_total) ? 0 : पंचांगp;

	पंचांगp = (s64)d->cpu_run_भव_total + t3;
	d->cpu_run_भव_total =
		(पंचांगp < (s64)d->cpu_run_भव_total) ?	0 : पंचांगp;

	/* zero XXX_total, non-zero XXX_count implies XXX stat overflowed */

	raw_spin_lock_irqsave(&tsk->delays->lock, flags);
	पंचांगp = d->blkio_delay_total + tsk->delays->blkio_delay;
	d->blkio_delay_total = (पंचांगp < d->blkio_delay_total) ? 0 : पंचांगp;
	पंचांगp = d->swapin_delay_total + tsk->delays->swapin_delay;
	d->swapin_delay_total = (पंचांगp < d->swapin_delay_total) ? 0 : पंचांगp;
	पंचांगp = d->मुक्तpages_delay_total + tsk->delays->मुक्तpages_delay;
	d->मुक्तpages_delay_total = (पंचांगp < d->मुक्तpages_delay_total) ? 0 : पंचांगp;
	पंचांगp = d->thrashing_delay_total + tsk->delays->thrashing_delay;
	d->thrashing_delay_total = (पंचांगp < d->thrashing_delay_total) ? 0 : पंचांगp;
	d->blkio_count += tsk->delays->blkio_count;
	d->swapin_count += tsk->delays->swapin_count;
	d->मुक्तpages_count += tsk->delays->मुक्तpages_count;
	d->thrashing_count += tsk->delays->thrashing_count;
	raw_spin_unlock_irqrestore(&tsk->delays->lock, flags);

	वापस 0;
पूर्ण

__u64 __delayacct_blkio_ticks(काष्ठा task_काष्ठा *tsk)
अणु
	__u64 ret;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&tsk->delays->lock, flags);
	ret = nsec_to_घड़ी_प्रकार(tsk->delays->blkio_delay +
				tsk->delays->swapin_delay);
	raw_spin_unlock_irqrestore(&tsk->delays->lock, flags);
	वापस ret;
पूर्ण

व्योम __delayacct_मुक्तpages_start(व्योम)
अणु
	current->delays->मुक्तpages_start = kसमय_get_ns();
पूर्ण

व्योम __delayacct_मुक्तpages_end(व्योम)
अणु
	delayacct_end(
		&current->delays->lock,
		&current->delays->मुक्तpages_start,
		&current->delays->मुक्तpages_delay,
		&current->delays->मुक्तpages_count);
पूर्ण

व्योम __delayacct_thrashing_start(व्योम)
अणु
	current->delays->thrashing_start = kसमय_get_ns();
पूर्ण

व्योम __delayacct_thrashing_end(व्योम)
अणु
	delayacct_end(&current->delays->lock,
		      &current->delays->thrashing_start,
		      &current->delays->thrashing_delay,
		      &current->delays->thrashing_count);
पूर्ण
