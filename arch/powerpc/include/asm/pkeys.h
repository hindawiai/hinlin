<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * PowerPC Memory Protection Keys management
 *
 * Copyright 2017, Ram Pai, IBM Corporation.
 */

#अगर_अघोषित _ASM_POWERPC_KEYS_H
#घोषणा _ASM_POWERPC_KEYS_H

#समावेश <linux/jump_label.h>
#समावेश <यंत्र/firmware.h>

बाह्य पूर्णांक num_pkey;
बाह्य u32 reserved_allocation_mask; /* bits set क्रम reserved keys */

#घोषणा ARCH_VM_PKEY_FLAGS (VM_PKEY_BIT0 | VM_PKEY_BIT1 | VM_PKEY_BIT2 | \
			    VM_PKEY_BIT3 | VM_PKEY_BIT4)

/* Override any generic PKEY permission defines */
#घोषणा PKEY_DISABLE_EXECUTE   0x4
#घोषणा PKEY_ACCESS_MASK       (PKEY_DISABLE_ACCESS | \
				PKEY_DISABLE_WRITE  | \
				PKEY_DISABLE_EXECUTE)

#अगर_घोषित CONFIG_PPC_BOOK3S_64
#समावेश <यंत्र/book3s/64/pkeys.h>
#अन्यथा
#त्रुटि "Not supported"
#पूर्ण_अगर


अटल अंतरभूत u64 pkey_to_vmflag_bits(u16 pkey)
अणु
	वापस (((u64)pkey << VM_PKEY_SHIFT) & ARCH_VM_PKEY_FLAGS);
पूर्ण

अटल अंतरभूत पूर्णांक vma_pkey(काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (!mmu_has_feature(MMU_FTR_PKEY))
		वापस 0;
	वापस (vma->vm_flags & ARCH_VM_PKEY_FLAGS) >> VM_PKEY_SHIFT;
पूर्ण

अटल अंतरभूत पूर्णांक arch_max_pkey(व्योम)
अणु
	वापस num_pkey;
पूर्ण

#घोषणा pkey_alloc_mask(pkey) (0x1 << pkey)

#घोषणा mm_pkey_allocation_map(mm) (mm->context.pkey_allocation_map)

#घोषणा __mm_pkey_allocated(mm, pkey) अणु	\
	mm_pkey_allocation_map(mm) |= pkey_alloc_mask(pkey); \
पूर्ण

#घोषणा __mm_pkey_मुक्त(mm, pkey) अणु	\
	mm_pkey_allocation_map(mm) &= ~pkey_alloc_mask(pkey);	\
पूर्ण

#घोषणा __mm_pkey_is_allocated(mm, pkey)	\
	(mm_pkey_allocation_map(mm) & pkey_alloc_mask(pkey))

#घोषणा __mm_pkey_is_reserved(pkey) (reserved_allocation_mask & \
				       pkey_alloc_mask(pkey))

अटल अंतरभूत bool mm_pkey_is_allocated(काष्ठा mm_काष्ठा *mm, पूर्णांक pkey)
अणु
	अगर (pkey < 0 || pkey >= arch_max_pkey())
		वापस false;

	/* Reserved keys are never allocated. */
	अगर (__mm_pkey_is_reserved(pkey))
		वापस false;

	वापस __mm_pkey_is_allocated(mm, pkey);
पूर्ण

/*
 * Returns a positive, 5-bit key on success, or -1 on failure.
 * Relies on the mmap_lock to protect against concurrency in mm_pkey_alloc() and
 * mm_pkey_मुक्त().
 */
अटल अंतरभूत पूर्णांक mm_pkey_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	/*
	 * Note: this is the one and only place we make sure that the pkey is
	 * valid as far as the hardware is concerned. The rest of the kernel
	 * trusts that only good, valid pkeys come out of here.
	 */
	u32 all_pkeys_mask = (u32)(~(0x0));
	पूर्णांक ret;

	अगर (!mmu_has_feature(MMU_FTR_PKEY))
		वापस -1;
	/*
	 * Are we out of pkeys? We must handle this specially because ffz()
	 * behavior is undefined अगर there are no zeros.
	 */
	अगर (mm_pkey_allocation_map(mm) == all_pkeys_mask)
		वापस -1;

	ret = ffz((u32)mm_pkey_allocation_map(mm));
	__mm_pkey_allocated(mm, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक mm_pkey_मुक्त(काष्ठा mm_काष्ठा *mm, पूर्णांक pkey)
अणु
	अगर (!mmu_has_feature(MMU_FTR_PKEY))
		वापस -1;

	अगर (!mm_pkey_is_allocated(mm, pkey))
		वापस -EINVAL;

	__mm_pkey_मुक्त(mm, pkey);

	वापस 0;
पूर्ण

/*
 * Try to dedicate one of the protection keys to be used as an
 * execute-only protection key.
 */
बाह्य पूर्णांक execute_only_pkey(काष्ठा mm_काष्ठा *mm);
बाह्य पूर्णांक __arch_override_mprotect_pkey(काष्ठा vm_area_काष्ठा *vma,
					 पूर्णांक prot, पूर्णांक pkey);
अटल अंतरभूत पूर्णांक arch_override_mprotect_pkey(काष्ठा vm_area_काष्ठा *vma,
					      पूर्णांक prot, पूर्णांक pkey)
अणु
	अगर (!mmu_has_feature(MMU_FTR_PKEY))
		वापस 0;

	/*
	 * Is this an mprotect_pkey() call? If so, never override the value that
	 * came from the user.
	 */
	अगर (pkey != -1)
		वापस pkey;

	वापस __arch_override_mprotect_pkey(vma, prot, pkey);
पूर्ण

बाह्य पूर्णांक __arch_set_user_pkey_access(काष्ठा task_काष्ठा *tsk, पूर्णांक pkey,
				       अचिन्हित दीर्घ init_val);
अटल अंतरभूत पूर्णांक arch_set_user_pkey_access(काष्ठा task_काष्ठा *tsk, पूर्णांक pkey,
					    अचिन्हित दीर्घ init_val)
अणु
	अगर (!mmu_has_feature(MMU_FTR_PKEY))
		वापस -EINVAL;

	/*
	 * userspace should not change pkey-0 permissions.
	 * pkey-0 is associated with every page in the kernel.
	 * If userspace denies any permission on pkey-0, the
	 * kernel cannot operate.
	 */
	अगर (pkey == 0)
		वापस init_val ? -EINVAL : 0;

	वापस __arch_set_user_pkey_access(tsk, pkey, init_val);
पूर्ण

अटल अंतरभूत bool arch_pkeys_enabled(व्योम)
अणु
	वापस mmu_has_feature(MMU_FTR_PKEY);
पूर्ण

बाह्य व्योम pkey_mm_init(काष्ठा mm_काष्ठा *mm);
#पूर्ण_अगर /*_ASM_POWERPC_KEYS_H */
