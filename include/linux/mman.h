<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_MMAN_H
#घोषणा _LINUX_MMAN_H

#समावेश <linux/mm.h>
#समावेश <linux/percpu_counter.h>

#समावेश <linux/atomic.h>
#समावेश <uapi/linux/mman.h>

/*
 * Arrange क्रम legacy / undefined architecture specअगरic flags to be
 * ignored by mmap handling code.
 */
#अगर_अघोषित MAP_32BIT
#घोषणा MAP_32BIT 0
#पूर्ण_अगर
#अगर_अघोषित MAP_HUGE_2MB
#घोषणा MAP_HUGE_2MB 0
#पूर्ण_अगर
#अगर_अघोषित MAP_HUGE_1GB
#घोषणा MAP_HUGE_1GB 0
#पूर्ण_अगर
#अगर_अघोषित MAP_UNINITIALIZED
#घोषणा MAP_UNINITIALIZED 0
#पूर्ण_अगर
#अगर_अघोषित MAP_SYNC
#घोषणा MAP_SYNC 0
#पूर्ण_अगर

/*
 * The historical set of flags that all mmap implementations implicitly
 * support when a ->mmap_validate() op is not provided in file_operations.
 */
#घोषणा LEGACY_MAP_MASK (MAP_SHARED \
		| MAP_PRIVATE \
		| MAP_FIXED \
		| MAP_ANONYMOUS \
		| MAP_DENYWRITE \
		| MAP_EXECUTABLE \
		| MAP_UNINITIALIZED \
		| MAP_GROWSDOWN \
		| MAP_LOCKED \
		| MAP_NORESERVE \
		| MAP_POPULATE \
		| MAP_NONBLOCK \
		| MAP_STACK \
		| MAP_HUGETLB \
		| MAP_32BIT \
		| MAP_HUGE_2MB \
		| MAP_HUGE_1GB)

बाह्य पूर्णांक sysctl_overcommit_memory;
बाह्य पूर्णांक sysctl_overcommit_ratio;
बाह्य अचिन्हित दीर्घ sysctl_overcommit_kbytes;
बाह्य काष्ठा percpu_counter vm_committed_as;

#अगर_घोषित CONFIG_SMP
बाह्य s32 vm_committed_as_batch;
बाह्य व्योम mm_compute_batch(पूर्णांक overcommit_policy);
#अन्यथा
#घोषणा vm_committed_as_batch 0
अटल अंतरभूत व्योम mm_compute_batch(पूर्णांक overcommit_policy)
अणु
पूर्ण
#पूर्ण_अगर

अचिन्हित दीर्घ vm_memory_committed(व्योम);

अटल अंतरभूत व्योम vm_acct_memory(दीर्घ pages)
अणु
	percpu_counter_add_batch(&vm_committed_as, pages, vm_committed_as_batch);
पूर्ण

अटल अंतरभूत व्योम vm_unacct_memory(दीर्घ pages)
अणु
	vm_acct_memory(-pages);
पूर्ण

/*
 * Allow architectures to handle additional protection and flag bits. The
 * overriding macros must be defined in the arch-specअगरic यंत्र/mman.h file.
 */

#अगर_अघोषित arch_calc_vm_prot_bits
#घोषणा arch_calc_vm_prot_bits(prot, pkey) 0
#पूर्ण_अगर

#अगर_अघोषित arch_calc_vm_flag_bits
#घोषणा arch_calc_vm_flag_bits(flags) 0
#पूर्ण_अगर

#अगर_अघोषित arch_vm_get_page_prot
#घोषणा arch_vm_get_page_prot(vm_flags) __pgprot(0)
#पूर्ण_अगर

#अगर_अघोषित arch_validate_prot
/*
 * This is called from mprotect().  PROT_GROWSDOWN and PROT_GROWSUP have
 * alपढ़ोy been masked out.
 *
 * Returns true अगर the prot flags are valid
 */
अटल अंतरभूत bool arch_validate_prot(अचिन्हित दीर्घ prot, अचिन्हित दीर्घ addr)
अणु
	वापस (prot & ~(PROT_READ | PROT_WRITE | PROT_EXEC | PROT_SEM)) == 0;
पूर्ण
#घोषणा arch_validate_prot arch_validate_prot
#पूर्ण_अगर

#अगर_अघोषित arch_validate_flags
/*
 * This is called from mmap() and mprotect() with the updated vma->vm_flags.
 *
 * Returns true अगर the VM_* flags are valid.
 */
अटल अंतरभूत bool arch_validate_flags(अचिन्हित दीर्घ flags)
अणु
	वापस true;
पूर्ण
#घोषणा arch_validate_flags arch_validate_flags
#पूर्ण_अगर

/*
 * Optimisation macro.  It is equivalent to:
 *      (x & bit1) ? bit2 : 0
 * but this version is faster.
 * ("bit1" and "bit2" must be single bits)
 */
#घोषणा _calc_vm_trans(x, bit1, bit2) \
  ((!(bit1) || !(bit2)) ? 0 : \
  ((bit1) <= (bit2) ? ((x) & (bit1)) * ((bit2) / (bit1)) \
   : ((x) & (bit1)) / ((bit1) / (bit2))))

/*
 * Combine the mmap "prot" argument पूर्णांकo "vm_flags" used पूर्णांकernally.
 */
अटल अंतरभूत अचिन्हित दीर्घ
calc_vm_prot_bits(अचिन्हित दीर्घ prot, अचिन्हित दीर्घ pkey)
अणु
	वापस _calc_vm_trans(prot, PROT_READ,  VM_READ ) |
	       _calc_vm_trans(prot, PROT_WRITE, VM_WRITE) |
	       _calc_vm_trans(prot, PROT_EXEC,  VM_EXEC) |
	       arch_calc_vm_prot_bits(prot, pkey);
पूर्ण

/*
 * Combine the mmap "flags" argument पूर्णांकo "vm_flags" used पूर्णांकernally.
 */
अटल अंतरभूत अचिन्हित दीर्घ
calc_vm_flag_bits(अचिन्हित दीर्घ flags)
अणु
	वापस _calc_vm_trans(flags, MAP_GROWSDOWN,  VM_GROWSDOWN ) |
	       _calc_vm_trans(flags, MAP_DENYWRITE,  VM_DENYWRITE ) |
	       _calc_vm_trans(flags, MAP_LOCKED,     VM_LOCKED    ) |
	       _calc_vm_trans(flags, MAP_SYNC,	     VM_SYNC      ) |
	       arch_calc_vm_flag_bits(flags);
पूर्ण

अचिन्हित दीर्घ vm_commit_limit(व्योम);
#पूर्ण_अगर /* _LINUX_MMAN_H */
