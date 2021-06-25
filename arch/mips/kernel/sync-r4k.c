<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Count रेजिस्टर synchronisation.
 *
 * All CPUs will have their count रेजिस्टरs synchronised to the CPU0 next समय
 * value. This can cause a small समयwarp क्रम CPU0. All other CPU's should
 * not have करोne anything signअगरicant (but they may have had पूर्णांकerrupts
 * enabled briefly - prom_smp_finish() should not be responsible क्रम enabling
 * पूर्णांकerrupts...)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/cpumask.h>

#समावेश <यंत्र/r4k-समयr.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/mipsregs.h>

अटल अचिन्हित पूर्णांक initcount = 0;
अटल atomic_t count_count_start = ATOMIC_INIT(0);
अटल atomic_t count_count_stop = ATOMIC_INIT(0);

#घोषणा COUNTON 100
#घोषणा NR_LOOPS 3

व्योम synchronise_count_master(पूर्णांक cpu)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	pr_info("Synchronize counters for CPU %u: ", cpu);

	local_irq_save(flags);

	/*
	 * We loop a few बार to get a primed inकाष्ठाion cache,
	 * then the last pass is more or less synchronised and
	 * the master and slaves each set their cycle counters to a known
	 * value all at once. This reduces the chance of having अक्रमom offsets
	 * between the processors, and guarantees that the maximum
	 * delay between the cycle counters is never bigger than
	 * the latency of inक्रमmation-passing (cachelines) between
	 * two CPUs.
	 */

	क्रम (i = 0; i < NR_LOOPS; i++) अणु
		/* slaves loop on '!= 2' */
		जबतक (atomic_पढ़ो(&count_count_start) != 1)
			mb();
		atomic_set(&count_count_stop, 0);
		smp_wmb();

		/* Let the slave ग_लिखोs its count रेजिस्टर */
		atomic_inc(&count_count_start);

		/* Count will be initialised to current समयr */
		अगर (i == 1)
			initcount = पढ़ो_c0_count();

		/*
		 * Everyone initialises count in the last loop:
		 */
		अगर (i == NR_LOOPS-1)
			ग_लिखो_c0_count(initcount);

		/*
		 * Wait क्रम slave to leave the synchronization poपूर्णांक:
		 */
		जबतक (atomic_पढ़ो(&count_count_stop) != 1)
			mb();
		atomic_set(&count_count_start, 0);
		smp_wmb();
		atomic_inc(&count_count_stop);
	पूर्ण
	/* Arrange क्रम an पूर्णांकerrupt in a लघु जबतक */
	ग_लिखो_c0_compare(पढ़ो_c0_count() + COUNTON);

	local_irq_restore(flags);

	/*
	 * i386 code reported the skew here, but the
	 * count रेजिस्टरs were almost certainly out of sync
	 * so no poपूर्णांक in alarming people
	 */
	pr_cont("done.\n");
पूर्ण

व्योम synchronise_count_slave(पूर्णांक cpu)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	/*
	 * Not every cpu is online at the समय this माला_लो called,
	 * so we first रुको क्रम the master to say everyone is पढ़ोy
	 */

	क्रम (i = 0; i < NR_LOOPS; i++) अणु
		atomic_inc(&count_count_start);
		जबतक (atomic_पढ़ो(&count_count_start) != 2)
			mb();

		/*
		 * Everyone initialises count in the last loop:
		 */
		अगर (i == NR_LOOPS-1)
			ग_लिखो_c0_count(initcount);

		atomic_inc(&count_count_stop);
		जबतक (atomic_पढ़ो(&count_count_stop) != 2)
			mb();
	पूर्ण
	/* Arrange क्रम an पूर्णांकerrupt in a लघु जबतक */
	ग_लिखो_c0_compare(पढ़ो_c0_count() + COUNTON);

	local_irq_restore(flags);
पूर्ण
#अघोषित NR_LOOPS
