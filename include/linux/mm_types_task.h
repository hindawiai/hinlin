<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_MM_TYPES_TASK_H
#घोषणा _LINUX_MM_TYPES_TASK_H

/*
 * Here are the definitions of the MM data types that are embedded in 'struct task_struct'.
 *
 * (These are defined separately to decouple sched.h from mm_types.h as much as possible.)
 */

#समावेश <linux/types.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/atomic.h>
#समावेश <linux/cpumask.h>

#समावेश <यंत्र/page.h>

#अगर_घोषित CONFIG_ARCH_WANT_BATCHED_UNMAP_TLB_FLUSH
#समावेश <यंत्र/tlbbatch.h>
#पूर्ण_अगर

#घोषणा USE_SPLIT_PTE_PTLOCKS	(NR_CPUS >= CONFIG_SPLIT_PTLOCK_CPUS)
#घोषणा USE_SPLIT_PMD_PTLOCKS	(USE_SPLIT_PTE_PTLOCKS && \
		IS_ENABLED(CONFIG_ARCH_ENABLE_SPLIT_PMD_PTLOCK))
#घोषणा ALLOC_SPLIT_PTLOCKS	(SPINLOCK_SIZE > BITS_PER_LONG/8)

/*
 * The per task VMA cache array:
 */
#घोषणा VMACACHE_BITS 2
#घोषणा VMACACHE_SIZE (1U << VMACACHE_BITS)
#घोषणा VMACACHE_MASK (VMACACHE_SIZE - 1)

काष्ठा vmacache अणु
	u64 seqnum;
	काष्ठा vm_area_काष्ठा *vmas[VMACACHE_SIZE];
पूर्ण;

/*
 * When updating this, please also update काष्ठा resident_page_types[] in
 * kernel/विभाजन.c
 */
क्रमागत अणु
	MM_खाताPAGES,	/* Resident file mapping pages */
	MM_ANONPAGES,	/* Resident anonymous pages */
	MM_SWAPENTS,	/* Anonymous swap entries */
	MM_SHMEMPAGES,	/* Resident shared memory pages */
	NR_MM_COUNTERS
पूर्ण;

#अगर USE_SPLIT_PTE_PTLOCKS && defined(CONFIG_MMU)
#घोषणा SPLIT_RSS_COUNTING
/* per-thपढ़ो cached inक्रमmation, */
काष्ठा task_rss_stat अणु
	पूर्णांक events;	/* क्रम synchronization threshold */
	पूर्णांक count[NR_MM_COUNTERS];
पूर्ण;
#पूर्ण_अगर /* USE_SPLIT_PTE_PTLOCKS */

काष्ठा mm_rss_stat अणु
	atomic_दीर्घ_t count[NR_MM_COUNTERS];
पूर्ण;

काष्ठा page_frag अणु
	काष्ठा page *page;
#अगर (BITS_PER_LONG > 32) || (PAGE_SIZE >= 65536)
	__u32 offset;
	__u32 size;
#अन्यथा
	__u16 offset;
	__u16 size;
#पूर्ण_अगर
पूर्ण;

/* Track pages that require TLB flushes */
काष्ठा tlbflush_unmap_batch अणु
#अगर_घोषित CONFIG_ARCH_WANT_BATCHED_UNMAP_TLB_FLUSH
	/*
	 * The arch code makes the following promise: generic code can modअगरy a
	 * PTE, then call arch_tlbbatch_add_mm() (which पूर्णांकernally provides all
	 * needed barriers), then call arch_tlbbatch_flush(), and the entries
	 * will be flushed on all CPUs by the समय that arch_tlbbatch_flush()
	 * वापसs.
	 */
	काष्ठा arch_tlbflush_unmap_batch arch;

	/* True अगर a flush is needed. */
	bool flush_required;

	/*
	 * If true then the PTE was dirty when unmapped. The entry must be
	 * flushed beक्रमe IO is initiated or a stale TLB entry potentially
	 * allows an update without redirtying the page.
	 */
	bool writable;
#पूर्ण_अगर
पूर्ण;

#पूर्ण_अगर /* _LINUX_MM_TYPES_TASK_H */
