<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/cpumask.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/स्थिति.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/समय_namespace.h>
#समावेश <linux/irqnr.h>
#समावेश <linux/sched/cpuसमय.स>
#समावेश <linux/tick.h>

#अगर_अघोषित arch_irq_stat_cpu
#घोषणा arch_irq_stat_cpu(cpu) 0
#पूर्ण_अगर
#अगर_अघोषित arch_irq_stat
#घोषणा arch_irq_stat() 0
#पूर्ण_अगर

#अगर_घोषित arch_idle_समय

अटल u64 get_idle_समय(काष्ठा kernel_cpustat *kcs, पूर्णांक cpu)
अणु
	u64 idle;

	idle = kcs->cpustat[CPUTIME_IDLE];
	अगर (cpu_online(cpu) && !nr_ioरुको_cpu(cpu))
		idle += arch_idle_समय(cpu);
	वापस idle;
पूर्ण

अटल u64 get_ioरुको_समय(काष्ठा kernel_cpustat *kcs, पूर्णांक cpu)
अणु
	u64 ioरुको;

	ioरुको = kcs->cpustat[CPUTIME_IOWAIT];
	अगर (cpu_online(cpu) && nr_ioरुको_cpu(cpu))
		ioरुको += arch_idle_समय(cpu);
	वापस ioरुको;
पूर्ण

#अन्यथा

अटल u64 get_idle_समय(काष्ठा kernel_cpustat *kcs, पूर्णांक cpu)
अणु
	u64 idle, idle_usecs = -1ULL;

	अगर (cpu_online(cpu))
		idle_usecs = get_cpu_idle_समय_us(cpu, शून्य);

	अगर (idle_usecs == -1ULL)
		/* !NO_HZ or cpu offline so we can rely on cpustat.idle */
		idle = kcs->cpustat[CPUTIME_IDLE];
	अन्यथा
		idle = idle_usecs * NSEC_PER_USEC;

	वापस idle;
पूर्ण

अटल u64 get_ioरुको_समय(काष्ठा kernel_cpustat *kcs, पूर्णांक cpu)
अणु
	u64 ioरुको, ioरुको_usecs = -1ULL;

	अगर (cpu_online(cpu))
		ioरुको_usecs = get_cpu_ioरुको_समय_us(cpu, शून्य);

	अगर (ioरुको_usecs == -1ULL)
		/* !NO_HZ or cpu offline so we can rely on cpustat.ioरुको */
		ioरुको = kcs->cpustat[CPUTIME_IOWAIT];
	अन्यथा
		ioरुको = ioरुको_usecs * NSEC_PER_USEC;

	वापस ioरुको;
पूर्ण

#पूर्ण_अगर

अटल व्योम show_irq_gap(काष्ठा seq_file *p, अचिन्हित पूर्णांक gap)
अणु
	अटल स्थिर अक्षर zeros[] = " 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0";

	जबतक (gap > 0) अणु
		अचिन्हित पूर्णांक inc;

		inc = min_t(अचिन्हित पूर्णांक, gap, ARRAY_SIZE(zeros) / 2);
		seq_ग_लिखो(p, zeros, 2 * inc);
		gap -= inc;
	पूर्ण
पूर्ण

अटल व्योम show_all_irqs(काष्ठा seq_file *p)
अणु
	अचिन्हित पूर्णांक i, next = 0;

	क्रम_each_active_irq(i) अणु
		show_irq_gap(p, i - next);
		seq_put_decimal_ull(p, " ", kstat_irqs_usr(i));
		next = i + 1;
	पूर्ण
	show_irq_gap(p, nr_irqs - next);
पूर्ण

अटल पूर्णांक show_stat(काष्ठा seq_file *p, व्योम *v)
अणु
	पूर्णांक i, j;
	u64 user, nice, प्रणाली, idle, ioरुको, irq, softirq, steal;
	u64 guest, guest_nice;
	u64 sum = 0;
	u64 sum_softirq = 0;
	अचिन्हित पूर्णांक per_softirq_sums[NR_SOFTIRQS] = अणु0पूर्ण;
	काष्ठा बारpec64 bootसमय;

	user = nice = प्रणाली = idle = ioरुको =
		irq = softirq = steal = 0;
	guest = guest_nice = 0;
	getbootसमय64(&bootसमय);
	/* shअगरt boot बारtamp according to the समयns offset */
	समयns_sub_bootसमय(&bootसमय);

	क्रम_each_possible_cpu(i) अणु
		काष्ठा kernel_cpustat kcpustat;
		u64 *cpustat = kcpustat.cpustat;

		kcpustat_cpu_fetch(&kcpustat, i);

		user		+= cpustat[CPUTIME_USER];
		nice		+= cpustat[CPUTIME_NICE];
		प्रणाली		+= cpustat[CPUTIME_SYSTEM];
		idle		+= get_idle_समय(&kcpustat, i);
		ioरुको		+= get_ioरुको_समय(&kcpustat, i);
		irq		+= cpustat[CPUTIME_IRQ];
		softirq		+= cpustat[CPUTIME_SOFTIRQ];
		steal		+= cpustat[CPUTIME_STEAL];
		guest		+= cpustat[CPUTIME_GUEST];
		guest_nice	+= cpustat[CPUTIME_GUEST_NICE];
		sum		+= kstat_cpu_irqs_sum(i);
		sum		+= arch_irq_stat_cpu(i);

		क्रम (j = 0; j < NR_SOFTIRQS; j++) अणु
			अचिन्हित पूर्णांक softirq_stat = kstat_softirqs_cpu(j, i);

			per_softirq_sums[j] += softirq_stat;
			sum_softirq += softirq_stat;
		पूर्ण
	पूर्ण
	sum += arch_irq_stat();

	seq_put_decimal_ull(p, "cpu  ", nsec_to_घड़ी_प्रकार(user));
	seq_put_decimal_ull(p, " ", nsec_to_घड़ी_प्रकार(nice));
	seq_put_decimal_ull(p, " ", nsec_to_घड़ी_प्रकार(प्रणाली));
	seq_put_decimal_ull(p, " ", nsec_to_घड़ी_प्रकार(idle));
	seq_put_decimal_ull(p, " ", nsec_to_घड़ी_प्रकार(ioरुको));
	seq_put_decimal_ull(p, " ", nsec_to_घड़ी_प्रकार(irq));
	seq_put_decimal_ull(p, " ", nsec_to_घड़ी_प्रकार(softirq));
	seq_put_decimal_ull(p, " ", nsec_to_घड़ी_प्रकार(steal));
	seq_put_decimal_ull(p, " ", nsec_to_घड़ी_प्रकार(guest));
	seq_put_decimal_ull(p, " ", nsec_to_घड़ी_प्रकार(guest_nice));
	seq_अ_दो(p, '\n');

	क्रम_each_online_cpu(i) अणु
		काष्ठा kernel_cpustat kcpustat;
		u64 *cpustat = kcpustat.cpustat;

		kcpustat_cpu_fetch(&kcpustat, i);

		/* Copy values here to work around gcc-2.95.3, gcc-2.96 */
		user		= cpustat[CPUTIME_USER];
		nice		= cpustat[CPUTIME_NICE];
		प्रणाली		= cpustat[CPUTIME_SYSTEM];
		idle		= get_idle_समय(&kcpustat, i);
		ioरुको		= get_ioरुको_समय(&kcpustat, i);
		irq		= cpustat[CPUTIME_IRQ];
		softirq		= cpustat[CPUTIME_SOFTIRQ];
		steal		= cpustat[CPUTIME_STEAL];
		guest		= cpustat[CPUTIME_GUEST];
		guest_nice	= cpustat[CPUTIME_GUEST_NICE];
		seq_म_लिखो(p, "cpu%d", i);
		seq_put_decimal_ull(p, " ", nsec_to_घड़ी_प्रकार(user));
		seq_put_decimal_ull(p, " ", nsec_to_घड़ी_प्रकार(nice));
		seq_put_decimal_ull(p, " ", nsec_to_घड़ी_प्रकार(प्रणाली));
		seq_put_decimal_ull(p, " ", nsec_to_घड़ी_प्रकार(idle));
		seq_put_decimal_ull(p, " ", nsec_to_घड़ी_प्रकार(ioरुको));
		seq_put_decimal_ull(p, " ", nsec_to_घड़ी_प्रकार(irq));
		seq_put_decimal_ull(p, " ", nsec_to_घड़ी_प्रकार(softirq));
		seq_put_decimal_ull(p, " ", nsec_to_घड़ी_प्रकार(steal));
		seq_put_decimal_ull(p, " ", nsec_to_घड़ी_प्रकार(guest));
		seq_put_decimal_ull(p, " ", nsec_to_घड़ी_प्रकार(guest_nice));
		seq_अ_दो(p, '\n');
	पूर्ण
	seq_put_decimal_ull(p, "intr ", (अचिन्हित दीर्घ दीर्घ)sum);

	show_all_irqs(p);

	seq_म_लिखो(p,
		"\nctxt %llu\n"
		"btime %llu\n"
		"processes %lu\n"
		"procs_running %lu\n"
		"procs_blocked %lu\n",
		nr_context_चयनes(),
		(अचिन्हित दीर्घ दीर्घ)bootसमय.tv_sec,
		total_विभाजनs,
		nr_running(),
		nr_ioरुको());

	seq_put_decimal_ull(p, "softirq ", (अचिन्हित दीर्घ दीर्घ)sum_softirq);

	क्रम (i = 0; i < NR_SOFTIRQS; i++)
		seq_put_decimal_ull(p, " ", per_softirq_sums[i]);
	seq_अ_दो(p, '\n');

	वापस 0;
पूर्ण

अटल पूर्णांक stat_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित पूर्णांक size = 1024 + 128 * num_online_cpus();

	/* minimum size to display an पूर्णांकerrupt count : 2 bytes */
	size += 2 * nr_irqs;
	वापस single_खोलो_size(file, show_stat, शून्य, size);
पूर्ण

अटल स्थिर काष्ठा proc_ops stat_proc_ops = अणु
	.proc_flags	= PROC_ENTRY_PERMANENT,
	.proc_खोलो	= stat_खोलो,
	.proc_पढ़ो_iter	= seq_पढ़ो_iter,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
पूर्ण;

अटल पूर्णांक __init proc_stat_init(व्योम)
अणु
	proc_create("stat", 0, शून्य, &stat_proc_ops);
	वापस 0;
पूर्ण
fs_initcall(proc_stat_init);
