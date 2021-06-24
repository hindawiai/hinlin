<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ASM_ASID_H
#घोषणा __ASM_ASM_ASID_H

#समावेश <linux/atomic.h>
#समावेश <linux/compiler.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/percpu.h>
#समावेश <linux/spinlock.h>

काष्ठा asid_info
अणु
	atomic64_t	generation;
	अचिन्हित दीर्घ	*map;
	atomic64_t __percpu	*active;
	u64 __percpu		*reserved;
	u32			bits;
	/* Lock protecting the काष्ठाure */
	raw_spinlock_t		lock;
	/* Which CPU requires context flush on next call */
	cpumask_t		flush_pending;
	/* Number of ASID allocated by context (shअगरt value) */
	अचिन्हित पूर्णांक		ctxt_shअगरt;
	/* Callback to locally flush the context. */
	व्योम			(*flush_cpu_ctxt_cb)(व्योम);
पूर्ण;

#घोषणा NUM_ASIDS(info)			(1UL << ((info)->bits))
#घोषणा NUM_CTXT_ASIDS(info)		(NUM_ASIDS(info) >> (info)->ctxt_shअगरt)

#घोषणा active_asid(info, cpu)	*per_cpu_ptr((info)->active, cpu)

व्योम asid_new_context(काष्ठा asid_info *info, atomic64_t *pasid,
		      अचिन्हित पूर्णांक cpu, काष्ठा mm_काष्ठा *mm);

/*
 * Check the ASID is still valid क्रम the context. If not generate a new ASID.
 *
 * @pasid: Poपूर्णांकer to the current ASID batch
 * @cpu: current CPU ID. Must have been acquired through get_cpu()
 */
अटल अंतरभूत व्योम asid_check_context(काष्ठा asid_info *info,
				      atomic64_t *pasid, अचिन्हित पूर्णांक cpu,
				      काष्ठा mm_काष्ठा *mm)
अणु
	u64 asid, old_active_asid;

	asid = atomic64_पढ़ो(pasid);

	/*
	 * The memory ordering here is subtle.
	 * If our active_asid is non-zero and the ASID matches the current
	 * generation, then we update the active_asid entry with a relaxed
	 * cmpxchg. Racing with a concurrent rollover means that either:
	 *
	 * - We get a zero back from the cmpxchg and end up रुकोing on the
	 *   lock. Taking the lock synchronises with the rollover and so
	 *   we are क्रमced to see the updated generation.
	 *
	 * - We get a valid ASID back from the cmpxchg, which means the
	 *   relaxed xchg in flush_context will treat us as reserved
	 *   because atomic RmWs are totally ordered क्रम a given location.
	 */
	old_active_asid = atomic64_पढ़ो(&active_asid(info, cpu));
	अगर (old_active_asid &&
	    !((asid ^ atomic64_पढ़ो(&info->generation)) >> info->bits) &&
	    atomic64_cmpxchg_relaxed(&active_asid(info, cpu),
				     old_active_asid, asid))
		वापस;

	asid_new_context(info, pasid, cpu, mm);
पूर्ण

पूर्णांक asid_allocator_init(काष्ठा asid_info *info,
			u32 bits, अचिन्हित पूर्णांक asid_per_ctxt,
			व्योम (*flush_cpu_ctxt_cb)(व्योम));

#पूर्ण_अगर
