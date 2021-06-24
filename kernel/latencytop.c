<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * latencytop.c: Latency display infraकाष्ठाure
 *
 * (C) Copyright 2008 Intel Corporation
 * Author: Arjan van de Ven <arjan@linux.पूर्णांकel.com>
 */

/*
 * CONFIG_LATENCYTOP enables a kernel latency tracking infraकाष्ठाure that is
 * used by the "latencytop" userspace tool. The latency that is tracked is not
 * the 'traditional' पूर्णांकerrupt latency (which is primarily caused by something
 * अन्यथा consuming CPU), but instead, it is the latency an application encounters
 * because the kernel sleeps on its behalf क्रम various reasons.
 *
 * This code tracks 2 levels of statistics:
 * 1) System level latency
 * 2) Per process latency
 *
 * The latency is stored in fixed sized data काष्ठाures in an accumulated क्रमm;
 * अगर the "same" latency cause is hit twice, this will be tracked as one entry
 * in the data काष्ठाure. Both the count, total accumulated latency and maximum
 * latency are tracked in this data काष्ठाure. When the fixed size काष्ठाure is
 * full, no new causes are tracked until the buffer is flushed by writing to
 * the /proc file; the userspace tool करोes this on a regular basis.
 *
 * A latency cause is identअगरied by a stringअगरied backtrace at the poपूर्णांक that
 * the scheduler माला_लो invoked. The userland tool will use this string to
 * identअगरy the cause of the latency in human पढ़ोable क्रमm.
 *
 * The inक्रमmation is exported via /proc/latency_stats and /proc/<pid>/latency.
 * These files look like this:
 *
 * Latency Top version : v0.1
 * 70 59433 4897 i915_irq_रुको drm_ioctl vfs_ioctl करो_vfs_ioctl sys_ioctl
 * |    |    |    |
 * |    |    |    +----> the stringअगरied backtrace
 * |    |    +---------> The maximum latency क्रम this entry in microseconds
 * |    +--------------> The accumulated latency क्रम this entry (microseconds)
 * +-------------------> The number of बार this entry is hit
 *
 * (note: the average latency is the accumulated latency भागided by the number
 * of बार)
 */

#समावेश <linux/kallsyms.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/latencytop.h>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/स्थिति.स>
#समावेश <linux/list.h>
#समावेश <linux/stacktrace.h>

अटल DEFINE_RAW_SPINLOCK(latency_lock);

#घोषणा MAXLR 128
अटल काष्ठा latency_record latency_record[MAXLR];

पूर्णांक latencytop_enabled;

व्योम clear_tsk_latency_tracing(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&latency_lock, flags);
	स_रखो(&p->latency_record, 0, माप(p->latency_record));
	p->latency_record_count = 0;
	raw_spin_unlock_irqrestore(&latency_lock, flags);
पूर्ण

अटल व्योम clear_global_latency_tracing(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&latency_lock, flags);
	स_रखो(&latency_record, 0, माप(latency_record));
	raw_spin_unlock_irqrestore(&latency_lock, flags);
पूर्ण

अटल व्योम __sched
account_global_scheduler_latency(काष्ठा task_काष्ठा *tsk,
				 काष्ठा latency_record *lat)
अणु
	पूर्णांक firstnonnull = MAXLR + 1;
	पूर्णांक i;

	/* skip kernel thपढ़ोs क्रम now */
	अगर (!tsk->mm)
		वापस;

	क्रम (i = 0; i < MAXLR; i++) अणु
		पूर्णांक q, same = 1;

		/* Nothing stored: */
		अगर (!latency_record[i].backtrace[0]) अणु
			अगर (firstnonnull > i)
				firstnonnull = i;
			जारी;
		पूर्ण
		क्रम (q = 0; q < LT_BACKTRACEDEPTH; q++) अणु
			अचिन्हित दीर्घ record = lat->backtrace[q];

			अगर (latency_record[i].backtrace[q] != record) अणु
				same = 0;
				अवरोध;
			पूर्ण

			/* 0 entry marks end of backtrace: */
			अगर (!record)
				अवरोध;
		पूर्ण
		अगर (same) अणु
			latency_record[i].count++;
			latency_record[i].समय += lat->समय;
			अगर (lat->समय > latency_record[i].max)
				latency_record[i].max = lat->समय;
			वापस;
		पूर्ण
	पूर्ण

	i = firstnonnull;
	अगर (i >= MAXLR - 1)
		वापस;

	/* Allocted a new one: */
	स_नकल(&latency_record[i], lat, माप(काष्ठा latency_record));
पूर्ण

/**
 * __account_scheduler_latency - record an occurred latency
 * @tsk - the task काष्ठा of the task hitting the latency
 * @usecs - the duration of the latency in microseconds
 * @पूर्णांकer - 1 अगर the sleep was पूर्णांकerruptible, 0 अगर unपूर्णांकerruptible
 *
 * This function is the मुख्य entry poपूर्णांक क्रम recording latency entries
 * as called by the scheduler.
 *
 * This function has a few special हालs to deal with normal 'non-latency'
 * sleeps: specअगरically, पूर्णांकerruptible sleep दीर्घer than 5 msec is skipped
 * since this usually is caused by रुकोing क्रम events via select() and co.
 *
 * Negative latencies (caused by समय going backwards) are also explicitly
 * skipped.
 */
व्योम __sched
__account_scheduler_latency(काष्ठा task_काष्ठा *tsk, पूर्णांक usecs, पूर्णांक पूर्णांकer)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i, q;
	काष्ठा latency_record lat;

	/* Long पूर्णांकerruptible रुकोs are generally user requested... */
	अगर (पूर्णांकer && usecs > 5000)
		वापस;

	/* Negative sleeps are समय going backwards */
	/* Zero-समय sleeps are non-पूर्णांकeresting */
	अगर (usecs <= 0)
		वापस;

	स_रखो(&lat, 0, माप(lat));
	lat.count = 1;
	lat.समय = usecs;
	lat.max = usecs;

	stack_trace_save_tsk(tsk, lat.backtrace, LT_BACKTRACEDEPTH, 0);

	raw_spin_lock_irqsave(&latency_lock, flags);

	account_global_scheduler_latency(tsk, &lat);

	क्रम (i = 0; i < tsk->latency_record_count; i++) अणु
		काष्ठा latency_record *mylat;
		पूर्णांक same = 1;

		mylat = &tsk->latency_record[i];
		क्रम (q = 0; q < LT_BACKTRACEDEPTH; q++) अणु
			अचिन्हित दीर्घ record = lat.backtrace[q];

			अगर (mylat->backtrace[q] != record) अणु
				same = 0;
				अवरोध;
			पूर्ण

			/* 0 entry is end of backtrace */
			अगर (!record)
				अवरोध;
		पूर्ण
		अगर (same) अणु
			mylat->count++;
			mylat->समय += lat.समय;
			अगर (lat.समय > mylat->max)
				mylat->max = lat.समय;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	/*
	 * लघु term hack; अगर we're > 32 we stop; future we recycle:
	 */
	अगर (tsk->latency_record_count >= LT_SAVECOUNT)
		जाओ out_unlock;

	/* Allocated a new one: */
	i = tsk->latency_record_count++;
	स_नकल(&tsk->latency_record[i], &lat, माप(काष्ठा latency_record));

out_unlock:
	raw_spin_unlock_irqrestore(&latency_lock, flags);
पूर्ण

अटल पूर्णांक lstats_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक i;

	seq_माला_दो(m, "Latency Top version : v0.1\n");

	क्रम (i = 0; i < MAXLR; i++) अणु
		काष्ठा latency_record *lr = &latency_record[i];

		अगर (lr->backtrace[0]) अणु
			पूर्णांक q;
			seq_म_लिखो(m, "%i %lu %lu",
				   lr->count, lr->समय, lr->max);
			क्रम (q = 0; q < LT_BACKTRACEDEPTH; q++) अणु
				अचिन्हित दीर्घ bt = lr->backtrace[q];

				अगर (!bt)
					अवरोध;

				seq_म_लिखो(m, " %ps", (व्योम *)bt);
			पूर्ण
			seq_माला_दो(m, "\n");
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार
lstats_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार count,
	     loff_t *offs)
अणु
	clear_global_latency_tracing();

	वापस count;
पूर्ण

अटल पूर्णांक lstats_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस single_खोलो(filp, lstats_show, शून्य);
पूर्ण

अटल स्थिर काष्ठा proc_ops lstats_proc_ops = अणु
	.proc_खोलो	= lstats_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_ग_लिखो	= lstats_ग_लिखो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
पूर्ण;

अटल पूर्णांक __init init_lstats_procfs(व्योम)
अणु
	proc_create("latency_stats", 0644, शून्य, &lstats_proc_ops);
	वापस 0;
पूर्ण

पूर्णांक sysctl_latencytop(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer,
		माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक err;

	err = proc_करोपूर्णांकvec(table, ग_लिखो, buffer, lenp, ppos);
	अगर (latencytop_enabled)
		क्रमce_schedstat_enabled();

	वापस err;
पूर्ण
device_initcall(init_lstats_procfs);
