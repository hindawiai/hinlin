<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_U64_STATS_SYNC_H
#घोषणा _LINUX_U64_STATS_SYNC_H

/*
 * Protect against 64-bit values tearing on 32-bit architectures. This is
 * typically used क्रम statistics पढ़ो/update in dअगरferent subप्रणालीs.
 *
 * Key poपूर्णांकs :
 *
 * -  Use a seqcount on 32-bit SMP, only disable preemption क्रम 32-bit UP.
 * -  The whole thing is a no-op on 64-bit architectures.
 *
 * Usage स्थिरraपूर्णांकs:
 *
 * 1) Write side must ensure mutual exclusion, or one seqcount update could
 *    be lost, thus blocking पढ़ोers क्रमever.
 *
 * 2) Write side must disable preemption, or a seqcount पढ़ोer can preempt the
 *    ग_लिखोr and also spin क्रमever.
 *
 * 3) Write side must use the _irqsave() variant अगर other ग_लिखोrs, or a पढ़ोer,
 *    can be invoked from an IRQ context.
 *
 * 4) If पढ़ोer fetches several counters, there is no guarantee the whole values
 *    are consistent w.r.t. each other (remember poपूर्णांक #2: seqcounts are not
 *    used क्रम 64bit architectures).
 *
 * 5) Readers are allowed to sleep or be preempted/पूर्णांकerrupted: they perक्रमm
 *    pure पढ़ोs.
 *
 * 6) Readers must use both u64_stats_fetch_अणुbegin,retryपूर्ण_irq() अगर the stats
 *    might be updated from a hardirq or softirq context (remember poपूर्णांक #1:
 *    seqcounts are not used क्रम UP kernels). 32-bit UP stat पढ़ोers could पढ़ो
 *    corrupted 64-bit values otherwise.
 *
 * Usage :
 *
 * Stats producer (ग_लिखोr) should use following ढाँचा granted it alपढ़ोy got
 * an exclusive access to counters (a lock is alपढ़ोy taken, or per cpu
 * data is used [in a non preemptable context])
 *
 *   spin_lock_bh(...) or other synchronization to get exclusive access
 *   ...
 *   u64_stats_update_begin(&stats->syncp);
 *   u64_stats_add(&stats->bytes64, len); // non atomic operation
 *   u64_stats_inc(&stats->packets64);    // non atomic operation
 *   u64_stats_update_end(&stats->syncp);
 *
 * While a consumer (पढ़ोer) should use following ढाँचा to get consistent
 * snapshot क्रम each variable (but no guarantee on several ones)
 *
 * u64 tbytes, tpackets;
 * अचिन्हित पूर्णांक start;
 *
 * करो अणु
 *         start = u64_stats_fetch_begin(&stats->syncp);
 *         tbytes = u64_stats_पढ़ो(&stats->bytes64); // non atomic operation
 *         tpackets = u64_stats_पढ़ो(&stats->packets64); // non atomic operation
 * पूर्ण जबतक (u64_stats_fetch_retry(&stats->syncp, start));
 *
 *
 * Example of use in drivers/net/loopback.c, using per_cpu containers,
 * in BH disabled context.
 */
#समावेश <linux/seqlock.h>

काष्ठा u64_stats_sync अणु
#अगर BITS_PER_LONG==32 && defined(CONFIG_SMP)
	seqcount_t	seq;
#पूर्ण_अगर
पूर्ण;

#अगर BITS_PER_LONG == 64
#समावेश <यंत्र/local64.h>

प्रकार काष्ठा अणु
	local64_t	v;
पूर्ण u64_stats_t ;

अटल अंतरभूत u64 u64_stats_पढ़ो(स्थिर u64_stats_t *p)
अणु
	वापस local64_पढ़ो(&p->v);
पूर्ण

अटल अंतरभूत व्योम u64_stats_add(u64_stats_t *p, अचिन्हित दीर्घ val)
अणु
	local64_add(val, &p->v);
पूर्ण

अटल अंतरभूत व्योम u64_stats_inc(u64_stats_t *p)
अणु
	local64_inc(&p->v);
पूर्ण

#अन्यथा

प्रकार काष्ठा अणु
	u64		v;
पूर्ण u64_stats_t;

अटल अंतरभूत u64 u64_stats_पढ़ो(स्थिर u64_stats_t *p)
अणु
	वापस p->v;
पूर्ण

अटल अंतरभूत व्योम u64_stats_add(u64_stats_t *p, अचिन्हित दीर्घ val)
अणु
	p->v += val;
पूर्ण

अटल अंतरभूत व्योम u64_stats_inc(u64_stats_t *p)
अणु
	p->v++;
पूर्ण
#पूर्ण_अगर

#अगर BITS_PER_LONG == 32 && defined(CONFIG_SMP)
#घोषणा u64_stats_init(syncp)	seqcount_init(&(syncp)->seq)
#अन्यथा
अटल अंतरभूत व्योम u64_stats_init(काष्ठा u64_stats_sync *syncp)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम u64_stats_update_begin(काष्ठा u64_stats_sync *syncp)
अणु
#अगर BITS_PER_LONG==32 && defined(CONFIG_SMP)
	ग_लिखो_seqcount_begin(&syncp->seq);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम u64_stats_update_end(काष्ठा u64_stats_sync *syncp)
अणु
#अगर BITS_PER_LONG==32 && defined(CONFIG_SMP)
	ग_लिखो_seqcount_end(&syncp->seq);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
u64_stats_update_begin_irqsave(काष्ठा u64_stats_sync *syncp)
अणु
	अचिन्हित दीर्घ flags = 0;

#अगर BITS_PER_LONG==32 && defined(CONFIG_SMP)
	local_irq_save(flags);
	ग_लिखो_seqcount_begin(&syncp->seq);
#पूर्ण_अगर
	वापस flags;
पूर्ण

अटल अंतरभूत व्योम
u64_stats_update_end_irqrestore(काष्ठा u64_stats_sync *syncp,
				अचिन्हित दीर्घ flags)
अणु
#अगर BITS_PER_LONG==32 && defined(CONFIG_SMP)
	ग_लिखो_seqcount_end(&syncp->seq);
	local_irq_restore(flags);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __u64_stats_fetch_begin(स्थिर काष्ठा u64_stats_sync *syncp)
अणु
#अगर BITS_PER_LONG==32 && defined(CONFIG_SMP)
	वापस पढ़ो_seqcount_begin(&syncp->seq);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक u64_stats_fetch_begin(स्थिर काष्ठा u64_stats_sync *syncp)
अणु
#अगर BITS_PER_LONG==32 && !defined(CONFIG_SMP)
	preempt_disable();
#पूर्ण_अगर
	वापस __u64_stats_fetch_begin(syncp);
पूर्ण

अटल अंतरभूत bool __u64_stats_fetch_retry(स्थिर काष्ठा u64_stats_sync *syncp,
					 अचिन्हित पूर्णांक start)
अणु
#अगर BITS_PER_LONG==32 && defined(CONFIG_SMP)
	वापस पढ़ो_seqcount_retry(&syncp->seq, start);
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool u64_stats_fetch_retry(स्थिर काष्ठा u64_stats_sync *syncp,
					 अचिन्हित पूर्णांक start)
अणु
#अगर BITS_PER_LONG==32 && !defined(CONFIG_SMP)
	preempt_enable();
#पूर्ण_अगर
	वापस __u64_stats_fetch_retry(syncp, start);
पूर्ण

/*
 * In हाल irq handlers can update u64 counters, पढ़ोers can use following helpers
 * - SMP 32bit arches use seqcount protection, irq safe.
 * - UP 32bit must disable irqs.
 * - 64bit have no problem atomically पढ़ोing u64 values, irq safe.
 */
अटल अंतरभूत अचिन्हित पूर्णांक u64_stats_fetch_begin_irq(स्थिर काष्ठा u64_stats_sync *syncp)
अणु
#अगर BITS_PER_LONG==32 && !defined(CONFIG_SMP)
	local_irq_disable();
#पूर्ण_अगर
	वापस __u64_stats_fetch_begin(syncp);
पूर्ण

अटल अंतरभूत bool u64_stats_fetch_retry_irq(स्थिर काष्ठा u64_stats_sync *syncp,
					     अचिन्हित पूर्णांक start)
अणु
#अगर BITS_PER_LONG==32 && !defined(CONFIG_SMP)
	local_irq_enable();
#पूर्ण_अगर
	वापस __u64_stats_fetch_retry(syncp, start);
पूर्ण

#पूर्ण_अगर /* _LINUX_U64_STATS_SYNC_H */
