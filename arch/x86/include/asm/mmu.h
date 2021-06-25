<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_MMU_H
#घोषणा _ASM_X86_MMU_H

#समावेश <linux/spinlock.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/mutex.h>
#समावेश <linux/atomic.h>
#समावेश <linux/bits.h>

/* Uprobes on this MM assume 32-bit code */
#घोषणा MM_CONTEXT_UPROBE_IA32	BIT(0)
/* vsyscall page is accessible on this MM */
#घोषणा MM_CONTEXT_HAS_VSYSCALL	BIT(1)

/*
 * x86 has arch-specअगरic MMU state beyond what lives in mm_काष्ठा.
 */
प्रकार काष्ठा अणु
	/*
	 * ctx_id uniquely identअगरies this mm_काष्ठा.  A ctx_id will never
	 * be reused, and zero is not a valid ctx_id.
	 */
	u64 ctx_id;

	/*
	 * Any code that needs to करो any sort of TLB flushing क्रम this
	 * mm will first make its changes to the page tables, then
	 * increment tlb_gen, then flush.  This lets the low-level
	 * flushing code keep track of what needs flushing.
	 *
	 * This is not used on Xen PV.
	 */
	atomic64_t tlb_gen;

#अगर_घोषित CONFIG_MODIFY_LDT_SYSCALL
	काष्ठा rw_semaphore	ldt_usr_sem;
	काष्ठा ldt_काष्ठा	*ldt;
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_64
	अचिन्हित लघु flags;
#पूर्ण_अगर

	काष्ठा mutex lock;
	व्योम __user *vdso;			/* vdso base address */
	स्थिर काष्ठा vdso_image *vdso_image;	/* vdso image in use */

	atomic_t perf_rdpmc_allowed;	/* nonzero अगर rdpmc is allowed */
#अगर_घोषित CONFIG_X86_INTEL_MEMORY_PROTECTION_KEYS
	/*
	 * One bit per protection key says whether userspace can
	 * use it or not.  रक्षित by mmap_lock.
	 */
	u16 pkey_allocation_map;
	s16 execute_only_pkey;
#पूर्ण_अगर
पूर्ण mm_context_t;

#घोषणा INIT_MM_CONTEXT(mm)						\
	.context = अणु							\
		.ctx_id = 1,						\
		.lock = __MUTEX_INITIALIZER(mm.context.lock),		\
	पूर्ण

व्योम leave_mm(पूर्णांक cpu);
#घोषणा leave_mm leave_mm

#पूर्ण_अगर /* _ASM_X86_MMU_H */
