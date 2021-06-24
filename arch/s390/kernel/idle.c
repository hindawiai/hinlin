<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Idle functions क्रम s390.
 *
 * Copyright IBM Corp. 2014
 *
 * Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/notअगरier.h>
#समावेश <linux/init.h>
#समावेश <linux/cpu.h>
#समावेश <linux/sched/cpuसमय.स>
#समावेश <trace/events/घातer.h>
#समावेश <यंत्र/cpu_mf.h>
#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/smp.h>
#समावेश "entry.h"

अटल DEFINE_PER_CPU(काष्ठा s390_idle_data, s390_idle);

व्योम account_idle_समय_irq(व्योम)
अणु
	काष्ठा s390_idle_data *idle = this_cpu_ptr(&s390_idle);
	u64 cycles_new[8];
	पूर्णांक i;

	clear_cpu_flag(CIF_ENABLED_WAIT);
	अगर (smp_cpu_mtid) अणु
		stccपंचांग(MT_DIAG, smp_cpu_mtid, cycles_new);
		क्रम (i = 0; i < smp_cpu_mtid; i++)
			this_cpu_add(mt_cycles[i], cycles_new[i] - idle->mt_cycles_enter[i]);
	पूर्ण

	idle->घड़ी_idle_निकास = S390_lowcore.पूर्णांक_घड़ी;
	idle->समयr_idle_निकास = S390_lowcore.sys_enter_समयr;

	S390_lowcore.steal_समयr += idle->घड़ी_idle_enter - S390_lowcore.last_update_घड़ी;
	S390_lowcore.last_update_घड़ी = idle->घड़ी_idle_निकास;

	S390_lowcore.प्रणाली_समयr += S390_lowcore.last_update_समयr - idle->समयr_idle_enter;
	S390_lowcore.last_update_समयr = idle->समयr_idle_निकास;
पूर्ण

व्योम arch_cpu_idle(व्योम)
अणु
	काष्ठा s390_idle_data *idle = this_cpu_ptr(&s390_idle);
	अचिन्हित दीर्घ idle_समय;
	अचिन्हित दीर्घ psw_mask;

	/* Wait क्रम बाह्यal, I/O or machine check पूर्णांकerrupt. */
	psw_mask = PSW_KERNEL_BITS | PSW_MASK_WAIT | PSW_MASK_DAT |
		PSW_MASK_IO | PSW_MASK_EXT | PSW_MASK_MCHECK;
	clear_cpu_flag(CIF_NOHZ_DELAY);

	/* psw_idle() वापसs with पूर्णांकerrupts disabled. */
	psw_idle(idle, psw_mask);

	/* Account समय spent with enabled रुको psw loaded as idle समय. */
	raw_ग_लिखो_seqcount_begin(&idle->seqcount);
	idle_समय = idle->घड़ी_idle_निकास - idle->घड़ी_idle_enter;
	idle->घड़ी_idle_enter = idle->घड़ी_idle_निकास = 0ULL;
	idle->idle_समय += idle_समय;
	idle->idle_count++;
	account_idle_समय(cpuसमय_प्रकारo_nsecs(idle_समय));
	raw_ग_लिखो_seqcount_end(&idle->seqcount);
	raw_local_irq_enable();
पूर्ण

अटल sमाप_प्रकार show_idle_count(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा s390_idle_data *idle = &per_cpu(s390_idle, dev->id);
	अचिन्हित दीर्घ idle_count;
	अचिन्हित पूर्णांक seq;

	करो अणु
		seq = पढ़ो_seqcount_begin(&idle->seqcount);
		idle_count = READ_ONCE(idle->idle_count);
		अगर (READ_ONCE(idle->घड़ी_idle_enter))
			idle_count++;
	पूर्ण जबतक (पढ़ो_seqcount_retry(&idle->seqcount, seq));
	वापस प्र_लिखो(buf, "%lu\n", idle_count);
पूर्ण
DEVICE_ATTR(idle_count, 0444, show_idle_count, शून्य);

अटल sमाप_प्रकार show_idle_समय(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ now, idle_समय, idle_enter, idle_निकास, in_idle;
	काष्ठा s390_idle_data *idle = &per_cpu(s390_idle, dev->id);
	अचिन्हित पूर्णांक seq;

	करो अणु
		seq = पढ़ो_seqcount_begin(&idle->seqcount);
		idle_समय = READ_ONCE(idle->idle_समय);
		idle_enter = READ_ONCE(idle->घड़ी_idle_enter);
		idle_निकास = READ_ONCE(idle->घड़ी_idle_निकास);
	पूर्ण जबतक (पढ़ो_seqcount_retry(&idle->seqcount, seq));
	in_idle = 0;
	now = get_tod_घड़ी();
	अगर (idle_enter) अणु
		अगर (idle_निकास) अणु
			in_idle = idle_निकास - idle_enter;
		पूर्ण अन्यथा अगर (now > idle_enter) अणु
			in_idle = now - idle_enter;
		पूर्ण
	पूर्ण
	idle_समय += in_idle;
	वापस प्र_लिखो(buf, "%lu\n", idle_समय >> 12);
पूर्ण
DEVICE_ATTR(idle_समय_us, 0444, show_idle_समय, शून्य);

u64 arch_cpu_idle_समय(पूर्णांक cpu)
अणु
	काष्ठा s390_idle_data *idle = &per_cpu(s390_idle, cpu);
	अचिन्हित दीर्घ now, idle_enter, idle_निकास, in_idle;
	अचिन्हित पूर्णांक seq;

	करो अणु
		seq = पढ़ो_seqcount_begin(&idle->seqcount);
		idle_enter = READ_ONCE(idle->घड़ी_idle_enter);
		idle_निकास = READ_ONCE(idle->घड़ी_idle_निकास);
	पूर्ण जबतक (पढ़ो_seqcount_retry(&idle->seqcount, seq));
	in_idle = 0;
	now = get_tod_घड़ी();
	अगर (idle_enter) अणु
		अगर (idle_निकास) अणु
			in_idle = idle_निकास - idle_enter;
		पूर्ण अन्यथा अगर (now > idle_enter) अणु
			in_idle = now - idle_enter;
		पूर्ण
	पूर्ण
	वापस cpuसमय_प्रकारo_nsecs(in_idle);
पूर्ण

व्योम arch_cpu_idle_enter(व्योम)
अणु
पूर्ण

व्योम arch_cpu_idle_निकास(व्योम)
अणु
पूर्ण

व्योम arch_cpu_idle_dead(व्योम)
अणु
	cpu_die();
पूर्ण
