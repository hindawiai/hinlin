<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PKEYS_H
#घोषणा _ASM_X86_PKEYS_H

#घोषणा ARCH_DEFAULT_PKEY	0

/*
 * If more than 16 keys are ever supported, a thorough audit
 * will be necessary to ensure that the types that store key
 * numbers and masks have sufficient capacity.
 */
#घोषणा arch_max_pkey() (boot_cpu_has(X86_FEATURE_OSPKE) ? 16 : 1)

बाह्य पूर्णांक arch_set_user_pkey_access(काष्ठा task_काष्ठा *tsk, पूर्णांक pkey,
		अचिन्हित दीर्घ init_val);

अटल अंतरभूत bool arch_pkeys_enabled(व्योम)
अणु
	वापस boot_cpu_has(X86_FEATURE_OSPKE);
पूर्ण

/*
 * Try to dedicate one of the protection keys to be used as an
 * execute-only protection key.
 */
बाह्य पूर्णांक __execute_only_pkey(काष्ठा mm_काष्ठा *mm);
अटल अंतरभूत पूर्णांक execute_only_pkey(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_OSPKE))
		वापस ARCH_DEFAULT_PKEY;

	वापस __execute_only_pkey(mm);
पूर्ण

बाह्य पूर्णांक __arch_override_mprotect_pkey(काष्ठा vm_area_काष्ठा *vma,
		पूर्णांक prot, पूर्णांक pkey);
अटल अंतरभूत पूर्णांक arch_override_mprotect_pkey(काष्ठा vm_area_काष्ठा *vma,
		पूर्णांक prot, पूर्णांक pkey)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_OSPKE))
		वापस 0;

	वापस __arch_override_mprotect_pkey(vma, prot, pkey);
पूर्ण

बाह्य पूर्णांक __arch_set_user_pkey_access(काष्ठा task_काष्ठा *tsk, पूर्णांक pkey,
		अचिन्हित दीर्घ init_val);

#घोषणा ARCH_VM_PKEY_FLAGS (VM_PKEY_BIT0 | VM_PKEY_BIT1 | VM_PKEY_BIT2 | VM_PKEY_BIT3)

#घोषणा mm_pkey_allocation_map(mm)	(mm->context.pkey_allocation_map)
#घोषणा mm_set_pkey_allocated(mm, pkey) करो अणु		\
	mm_pkey_allocation_map(mm) |= (1U << pkey);	\
पूर्ण जबतक (0)
#घोषणा mm_set_pkey_मुक्त(mm, pkey) करो अणु			\
	mm_pkey_allocation_map(mm) &= ~(1U << pkey);	\
पूर्ण जबतक (0)

अटल अंतरभूत
bool mm_pkey_is_allocated(काष्ठा mm_काष्ठा *mm, पूर्णांक pkey)
अणु
	/*
	 * "Allocated" pkeys are those that have been वापसed
	 * from pkey_alloc() or pkey 0 which is allocated
	 * implicitly when the mm is created.
	 */
	अगर (pkey < 0)
		वापस false;
	अगर (pkey >= arch_max_pkey())
		वापस false;
	/*
	 * The exec-only pkey is set in the allocation map, but
	 * is not available to any of the user पूर्णांकerfaces like
	 * mprotect_pkey().
	 */
	अगर (pkey == mm->context.execute_only_pkey)
		वापस false;

	वापस mm_pkey_allocation_map(mm) & (1U << pkey);
पूर्ण

/*
 * Returns a positive, 4-bit key on success, or -1 on failure.
 */
अटल अंतरभूत
पूर्णांक mm_pkey_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	/*
	 * Note: this is the one and only place we make sure
	 * that the pkey is valid as far as the hardware is
	 * concerned.  The rest of the kernel trusts that
	 * only good, valid pkeys come out of here.
	 */
	u16 all_pkeys_mask = ((1U << arch_max_pkey()) - 1);
	पूर्णांक ret;

	/*
	 * Are we out of pkeys?  We must handle this specially
	 * because ffz() behavior is undefined अगर there are no
	 * zeros.
	 */
	अगर (mm_pkey_allocation_map(mm) == all_pkeys_mask)
		वापस -1;

	ret = ffz(mm_pkey_allocation_map(mm));

	mm_set_pkey_allocated(mm, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत
पूर्णांक mm_pkey_मुक्त(काष्ठा mm_काष्ठा *mm, पूर्णांक pkey)
अणु
	अगर (!mm_pkey_is_allocated(mm, pkey))
		वापस -EINVAL;

	mm_set_pkey_मुक्त(mm, pkey);

	वापस 0;
पूर्ण

बाह्य पूर्णांक arch_set_user_pkey_access(काष्ठा task_काष्ठा *tsk, पूर्णांक pkey,
		अचिन्हित दीर्घ init_val);
बाह्य पूर्णांक __arch_set_user_pkey_access(काष्ठा task_काष्ठा *tsk, पूर्णांक pkey,
		अचिन्हित दीर्घ init_val);
बाह्य व्योम copy_init_pkru_to_fpregs(व्योम);

अटल अंतरभूत पूर्णांक vma_pkey(काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ vma_pkey_mask = VM_PKEY_BIT0 | VM_PKEY_BIT1 |
				      VM_PKEY_BIT2 | VM_PKEY_BIT3;

	वापस (vma->vm_flags & vma_pkey_mask) >> VM_PKEY_SHIFT;
पूर्ण

#पूर्ण_अगर /*_ASM_X86_PKEYS_H */
