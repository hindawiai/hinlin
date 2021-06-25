<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * List pending समयrs
 *
 * Copyright(C) 2006, Red Hat, Inc., Ingo Molnar
 */

#समावेश <linux/proc_fs.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/nmi.h>

#समावेश <linux/uaccess.h>

#समावेश "tick-internal.h"

काष्ठा समयr_list_iter अणु
	पूर्णांक cpu;
	bool second_pass;
	u64 now;
पूर्ण;

/*
 * This allows prपूर्णांकing both to /proc/समयr_list and
 * to the console (on SysRq-Q):
 */
__म_लिखो(2, 3)
अटल व्योम SEQ_म_लिखो(काष्ठा seq_file *m, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	अगर (m)
		seq_भ_लिखो(m, fmt, args);
	अन्यथा
		vprपूर्णांकk(fmt, args);

	बहु_पूर्ण(args);
पूर्ण

अटल व्योम
prपूर्णांक_समयr(काष्ठा seq_file *m, काष्ठा hrसमयr *taddr, काष्ठा hrसमयr *समयr,
	    पूर्णांक idx, u64 now)
अणु
	SEQ_म_लिखो(m, " #%d: <%pK>, %ps", idx, taddr, समयr->function);
	SEQ_म_लिखो(m, ", S:%02x", समयr->state);
	SEQ_म_लिखो(m, "\n");
	SEQ_म_लिखो(m, " # expires at %Lu-%Lu nsecs [in %Ld to %Ld nsecs]\n",
		(अचिन्हित दीर्घ दीर्घ)kसमय_प्रकारo_ns(hrसमयr_get_softexpires(समयr)),
		(अचिन्हित दीर्घ दीर्घ)kसमय_प्रकारo_ns(hrसमयr_get_expires(समयr)),
		(दीर्घ दीर्घ)(kसमय_प्रकारo_ns(hrसमयr_get_softexpires(समयr)) - now),
		(दीर्घ दीर्घ)(kसमय_प्रकारo_ns(hrसमयr_get_expires(समयr)) - now));
पूर्ण

अटल व्योम
prपूर्णांक_active_समयrs(काष्ठा seq_file *m, काष्ठा hrसमयr_घड़ी_base *base,
		    u64 now)
अणु
	काष्ठा hrसमयr *समयr, पंचांगp;
	अचिन्हित दीर्घ next = 0, i;
	काष्ठा समयrqueue_node *curr;
	अचिन्हित दीर्घ flags;

next_one:
	i = 0;

	touch_nmi_watchकरोg();

	raw_spin_lock_irqsave(&base->cpu_base->lock, flags);

	curr = समयrqueue_getnext(&base->active);
	/*
	 * Crude but we have to करो this O(N*N) thing, because
	 * we have to unlock the base when prपूर्णांकing:
	 */
	जबतक (curr && i < next) अणु
		curr = समयrqueue_iterate_next(curr);
		i++;
	पूर्ण

	अगर (curr) अणु

		समयr = container_of(curr, काष्ठा hrसमयr, node);
		पंचांगp = *समयr;
		raw_spin_unlock_irqrestore(&base->cpu_base->lock, flags);

		prपूर्णांक_समयr(m, समयr, &पंचांगp, i, now);
		next++;
		जाओ next_one;
	पूर्ण
	raw_spin_unlock_irqrestore(&base->cpu_base->lock, flags);
पूर्ण

अटल व्योम
prपूर्णांक_base(काष्ठा seq_file *m, काष्ठा hrसमयr_घड़ी_base *base, u64 now)
अणु
	SEQ_म_लिखो(m, "  .base:       %pK\n", base);
	SEQ_म_लिखो(m, "  .index:      %d\n", base->index);

	SEQ_म_लिखो(m, "  .resolution: %u nsecs\n", hrसमयr_resolution);

	SEQ_म_लिखो(m,   "  .get_time:   %ps\n", base->get_समय);
#अगर_घोषित CONFIG_HIGH_RES_TIMERS
	SEQ_म_लिखो(m, "  .offset:     %Lu nsecs\n",
		   (अचिन्हित दीर्घ दीर्घ) kसमय_प्रकारo_ns(base->offset));
#पूर्ण_अगर
	SEQ_म_लिखो(m,   "active timers:\n");
	prपूर्णांक_active_समयrs(m, base, now + kसमय_प्रकारo_ns(base->offset));
पूर्ण

अटल व्योम prपूर्णांक_cpu(काष्ठा seq_file *m, पूर्णांक cpu, u64 now)
अणु
	काष्ठा hrसमयr_cpu_base *cpu_base = &per_cpu(hrसमयr_bases, cpu);
	पूर्णांक i;

	SEQ_म_लिखो(m, "cpu: %d\n", cpu);
	क्रम (i = 0; i < HRTIMER_MAX_CLOCK_BASES; i++) अणु
		SEQ_म_लिखो(m, " clock %d:\n", i);
		prपूर्णांक_base(m, cpu_base->घड़ी_base + i, now);
	पूर्ण
#घोषणा P(x) \
	SEQ_म_लिखो(m, "  .%-15s: %Lu\n", #x, \
		   (अचिन्हित दीर्घ दीर्घ)(cpu_base->x))
#घोषणा P_ns(x) \
	SEQ_म_लिखो(m, "  .%-15s: %Lu nsecs\n", #x, \
		   (अचिन्हित दीर्घ दीर्घ)(kसमय_प्रकारo_ns(cpu_base->x)))

#अगर_घोषित CONFIG_HIGH_RES_TIMERS
	P_ns(expires_next);
	P(hres_active);
	P(nr_events);
	P(nr_retries);
	P(nr_hangs);
	P(max_hang_समय);
#पूर्ण_अगर
#अघोषित P
#अघोषित P_ns

#अगर_घोषित CONFIG_TICK_ONESHOT
# define P(x) \
	SEQ_म_लिखो(m, "  .%-15s: %Lu\n", #x, \
		   (अचिन्हित दीर्घ दीर्घ)(ts->x))
# define P_ns(x) \
	SEQ_म_लिखो(m, "  .%-15s: %Lu nsecs\n", #x, \
		   (अचिन्हित दीर्घ दीर्घ)(kसमय_प्रकारo_ns(ts->x)))
	अणु
		काष्ठा tick_sched *ts = tick_get_tick_sched(cpu);
		P(nohz_mode);
		P_ns(last_tick);
		P(tick_stopped);
		P(idle_jअगरfies);
		P(idle_calls);
		P(idle_sleeps);
		P_ns(idle_entryसमय);
		P_ns(idle_wakeसमय);
		P_ns(idle_निकाससमय);
		P_ns(idle_sleepसमय);
		P_ns(ioरुको_sleepसमय);
		P(last_jअगरfies);
		P(next_समयr);
		P_ns(idle_expires);
		SEQ_म_लिखो(m, "jiffies: %Lu\n",
			   (अचिन्हित दीर्घ दीर्घ)jअगरfies);
	पूर्ण
#पूर्ण_अगर

#अघोषित P
#अघोषित P_ns
	SEQ_म_लिखो(m, "\n");
पूर्ण

#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS
अटल व्योम
prपूर्णांक_tickdevice(काष्ठा seq_file *m, काष्ठा tick_device *td, पूर्णांक cpu)
अणु
	काष्ठा घड़ी_event_device *dev = td->evtdev;

	touch_nmi_watchकरोg();

	SEQ_म_लिखो(m, "Tick Device: mode:     %d\n", td->mode);
	अगर (cpu < 0)
		SEQ_म_लिखो(m, "Broadcast device\n");
	अन्यथा
		SEQ_म_लिखो(m, "Per CPU device: %d\n", cpu);

	SEQ_म_लिखो(m, "Clock Event Device: ");
	अगर (!dev) अणु
		SEQ_म_लिखो(m, "<NULL>\n");
		वापस;
	पूर्ण
	SEQ_म_लिखो(m, "%s\n", dev->name);
	SEQ_म_लिखो(m, " max_delta_ns:   %llu\n",
		   (अचिन्हित दीर्घ दीर्घ) dev->max_delta_ns);
	SEQ_म_लिखो(m, " min_delta_ns:   %llu\n",
		   (अचिन्हित दीर्घ दीर्घ) dev->min_delta_ns);
	SEQ_म_लिखो(m, " mult:           %u\n", dev->mult);
	SEQ_म_लिखो(m, " shift:          %u\n", dev->shअगरt);
	SEQ_म_लिखो(m, " mode:           %d\n", घड़ीevent_get_state(dev));
	SEQ_म_लिखो(m, " next_event:     %Ld nsecs\n",
		   (अचिन्हित दीर्घ दीर्घ) kसमय_प्रकारo_ns(dev->next_event));

	SEQ_म_लिखो(m, " set_next_event: %ps\n", dev->set_next_event);

	अगर (dev->set_state_shutकरोwn)
		SEQ_म_लिखो(m, " shutdown:       %ps\n",
			dev->set_state_shutकरोwn);

	अगर (dev->set_state_periodic)
		SEQ_म_लिखो(m, " periodic:       %ps\n",
			dev->set_state_periodic);

	अगर (dev->set_state_oneshot)
		SEQ_म_लिखो(m, " oneshot:        %ps\n",
			dev->set_state_oneshot);

	अगर (dev->set_state_oneshot_stopped)
		SEQ_म_लिखो(m, " oneshot stopped: %ps\n",
			dev->set_state_oneshot_stopped);

	अगर (dev->tick_resume)
		SEQ_म_लिखो(m, " resume:         %ps\n",
			dev->tick_resume);

	SEQ_म_लिखो(m, " event_handler:  %ps\n", dev->event_handler);
	SEQ_म_लिखो(m, "\n");
	SEQ_म_लिखो(m, " retries:        %lu\n", dev->retries);
	SEQ_म_लिखो(m, "\n");
पूर्ण

अटल व्योम समयr_list_show_tickdevices_header(काष्ठा seq_file *m)
अणु
#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
	prपूर्णांक_tickdevice(m, tick_get_broadcast_device(), -1);
	SEQ_म_लिखो(m, "tick_broadcast_mask: %*pb\n",
		   cpumask_pr_args(tick_get_broadcast_mask()));
#अगर_घोषित CONFIG_TICK_ONESHOT
	SEQ_म_लिखो(m, "tick_broadcast_oneshot_mask: %*pb\n",
		   cpumask_pr_args(tick_get_broadcast_oneshot_mask()));
#पूर्ण_अगर
	SEQ_म_लिखो(m, "\n");
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम समयr_list_header(काष्ठा seq_file *m, u64 now)
अणु
	SEQ_म_लिखो(m, "Timer List Version: v0.8\n");
	SEQ_म_लिखो(m, "HRTIMER_MAX_CLOCK_BASES: %d\n", HRTIMER_MAX_CLOCK_BASES);
	SEQ_म_लिखो(m, "now at %Ld nsecs\n", (अचिन्हित दीर्घ दीर्घ)now);
	SEQ_म_लिखो(m, "\n");
पूर्ण

व्योम sysrq_समयr_list_show(व्योम)
अणु
	u64 now = kसमय_प्रकारo_ns(kसमय_get());
	पूर्णांक cpu;

	समयr_list_header(शून्य, now);

	क्रम_each_online_cpu(cpu)
		prपूर्णांक_cpu(शून्य, cpu, now);

#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS
	समयr_list_show_tickdevices_header(शून्य);
	क्रम_each_online_cpu(cpu)
		prपूर्णांक_tickdevice(शून्य, tick_get_device(cpu), cpu);
#पूर्ण_अगर
	वापस;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक समयr_list_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा समयr_list_iter *iter = v;

	अगर (iter->cpu == -1 && !iter->second_pass)
		समयr_list_header(m, iter->now);
	अन्यथा अगर (!iter->second_pass)
		prपूर्णांक_cpu(m, iter->cpu, iter->now);
#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS
	अन्यथा अगर (iter->cpu == -1 && iter->second_pass)
		समयr_list_show_tickdevices_header(m);
	अन्यथा
		prपूर्णांक_tickdevice(m, tick_get_device(iter->cpu), iter->cpu);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम *move_iter(काष्ठा समयr_list_iter *iter, loff_t offset)
अणु
	क्रम (; offset; offset--) अणु
		iter->cpu = cpumask_next(iter->cpu, cpu_online_mask);
		अगर (iter->cpu >= nr_cpu_ids) अणु
#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS
			अगर (!iter->second_pass) अणु
				iter->cpu = -1;
				iter->second_pass = true;
			पूर्ण अन्यथा
				वापस शून्य;
#अन्यथा
			वापस शून्य;
#पूर्ण_अगर
		पूर्ण
	पूर्ण
	वापस iter;
पूर्ण

अटल व्योम *समयr_list_start(काष्ठा seq_file *file, loff_t *offset)
अणु
	काष्ठा समयr_list_iter *iter = file->निजी;

	अगर (!*offset)
		iter->now = kसमय_प्रकारo_ns(kसमय_get());
	iter->cpu = -1;
	iter->second_pass = false;
	वापस move_iter(iter, *offset);
पूर्ण

अटल व्योम *समयr_list_next(काष्ठा seq_file *file, व्योम *v, loff_t *offset)
अणु
	काष्ठा समयr_list_iter *iter = file->निजी;
	++*offset;
	वापस move_iter(iter, 1);
पूर्ण

अटल व्योम समयr_list_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण

अटल स्थिर काष्ठा seq_operations समयr_list_sops = अणु
	.start = समयr_list_start,
	.next = समयr_list_next,
	.stop = समयr_list_stop,
	.show = समयr_list_show,
पूर्ण;

अटल पूर्णांक __init init_समयr_list_procfs(व्योम)
अणु
	काष्ठा proc_dir_entry *pe;

	pe = proc_create_seq_निजी("timer_list", 0400, शून्य, &समयr_list_sops,
			माप(काष्ठा समयr_list_iter), शून्य);
	अगर (!pe)
		वापस -ENOMEM;
	वापस 0;
पूर्ण
__initcall(init_समयr_list_procfs);
#पूर्ण_अगर
