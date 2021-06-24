<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * PowerPC Memory Protection Keys management
 *
 * Copyright 2017, Ram Pai, IBM Corporation.
 */

#समावेश <यंत्र/mman.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/smp.h>

#समावेश <linux/pkeys.h>
#समावेश <linux/of_fdt.h>


पूर्णांक  num_pkey;		/* Max number of pkeys supported */
/*
 *  Keys marked in the reservation list cannot be allocated by  userspace
 */
u32 reserved_allocation_mask __ro_after_init;

/* Bits set क्रम the initially allocated keys */
अटल u32 initial_allocation_mask __ro_after_init;

/*
 * Even अगर we allocate keys with sys_pkey_alloc(), we need to make sure
 * other thपढ़ो still find the access denied using the same keys.
 */
u64 शेष_amr __ro_after_init  = ~0x0UL;
u64 शेष_iamr __ro_after_init = 0x5555555555555555UL;
u64 शेष_uamor __ro_after_init;
EXPORT_SYMBOL(शेष_amr);
/*
 * Key used to implement PROT_EXEC mmap. Denies READ/WRITE
 * We pick key 2 because 0 is special key and 1 is reserved as per ISA.
 */
अटल पूर्णांक execute_only_key = 2;
अटल bool pkey_execute_disable_supported;


#घोषणा AMR_BITS_PER_PKEY 2
#घोषणा AMR_RD_BIT 0x1UL
#घोषणा AMR_WR_BIT 0x2UL
#घोषणा IAMR_EX_BIT 0x1UL
#घोषणा PKEY_REG_BITS (माप(u64) * 8)
#घोषणा pkeyshअगरt(pkey) (PKEY_REG_BITS - ((pkey+1) * AMR_BITS_PER_PKEY))

अटल पूर्णांक __init dt_scan_storage_keys(अचिन्हित दीर्घ node,
				       स्थिर अक्षर *uname, पूर्णांक depth,
				       व्योम *data)
अणु
	स्थिर अक्षर *type = of_get_flat_dt_prop(node, "device_type", शून्य);
	स्थिर __be32 *prop;
	पूर्णांक *pkeys_total = (पूर्णांक *) data;

	/* We are scanning "cpu" nodes only */
	अगर (type == शून्य || म_भेद(type, "cpu") != 0)
		वापस 0;

	prop = of_get_flat_dt_prop(node, "ibm,processor-storage-keys", शून्य);
	अगर (!prop)
		वापस 0;
	*pkeys_total = be32_to_cpu(prop[0]);
	वापस 1;
पूर्ण

अटल पूर्णांक scan_pkey_feature(व्योम)
अणु
	पूर्णांक ret;
	पूर्णांक pkeys_total = 0;

	/*
	 * Pkey is not supported with Radix translation.
	 */
	अगर (early_radix_enabled())
		वापस 0;

	ret = of_scan_flat_dt(dt_scan_storage_keys, &pkeys_total);
	अगर (ret == 0) अणु
		/*
		 * Let's assume 32 pkeys on P8/P9 bare metal, अगर its not defined by device
		 * tree. We make this exception since some version of skiboot क्रमgot to
		 * expose this property on घातer8/9.
		 */
		अगर (!firmware_has_feature(FW_FEATURE_LPAR)) अणु
			अचिन्हित दीर्घ pvr = mfspr(SPRN_PVR);

			अगर (PVR_VER(pvr) == PVR_POWER8 || PVR_VER(pvr) == PVR_POWER8E ||
			    PVR_VER(pvr) == PVR_POWER8NVL || PVR_VER(pvr) == PVR_POWER9)
				pkeys_total = 32;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_PPC_MEM_KEYS
	/*
	 * Adjust the upper limit, based on the number of bits supported by
	 * arch-neutral code.
	 */
	pkeys_total = min_t(पूर्णांक, pkeys_total,
			    ((ARCH_VM_PKEY_FLAGS >> VM_PKEY_SHIFT) + 1));
#पूर्ण_अगर
	वापस pkeys_total;
पूर्ण

व्योम __init pkey_early_init_devtree(व्योम)
अणु
	पूर्णांक pkeys_total, i;

#अगर_घोषित CONFIG_PPC_MEM_KEYS
	/*
	 * We define PKEY_DISABLE_EXECUTE in addition to the arch-neutral
	 * generic defines क्रम PKEY_DISABLE_ACCESS and PKEY_DISABLE_WRITE.
	 * Ensure that the bits a distinct.
	 */
	BUILD_BUG_ON(PKEY_DISABLE_EXECUTE &
		     (PKEY_DISABLE_ACCESS | PKEY_DISABLE_WRITE));

	/*
	 * pkey_to_vmflag_bits() assumes that the pkey bits are contiguous
	 * in the vmaflag. Make sure that is really the हाल.
	 */
	BUILD_BUG_ON(__builtin_clzl(ARCH_VM_PKEY_FLAGS >> VM_PKEY_SHIFT) +
		     __builtin_popcountl(ARCH_VM_PKEY_FLAGS >> VM_PKEY_SHIFT)
				!= (माप(u64) * BITS_PER_BYTE));
#पूर्ण_अगर
	/*
	 * Only P7 and above supports SPRN_AMR update with MSR[PR] = 1
	 */
	अगर (!early_cpu_has_feature(CPU_FTR_ARCH_206))
		वापस;

	/* scan the device tree क्रम pkey feature */
	pkeys_total = scan_pkey_feature();
	अगर (!pkeys_total)
		जाओ out;

	/* Allow all keys to be modअगरied by शेष */
	शेष_uamor = ~0x0UL;

	cur_cpu_spec->mmu_features |= MMU_FTR_PKEY;

	/*
	 * The device tree cannot be relied to indicate support क्रम
	 * execute_disable support. Instead we use a PVR check.
	 */
	अगर (pvr_version_is(PVR_POWER7) || pvr_version_is(PVR_POWER7p))
		pkey_execute_disable_supported = false;
	अन्यथा
		pkey_execute_disable_supported = true;

#अगर_घोषित CONFIG_PPC_4K_PAGES
	/*
	 * The OS can manage only 8 pkeys due to its inability to represent them
	 * in the Linux 4K PTE. Mark all other keys reserved.
	 */
	num_pkey = min(8, pkeys_total);
#अन्यथा
	num_pkey = pkeys_total;
#पूर्ण_अगर

	अगर (unlikely(num_pkey <= execute_only_key) || !pkey_execute_disable_supported) अणु
		/*
		 * Insufficient number of keys to support
		 * execute only key. Mark it unavailable.
		 */
		execute_only_key = -1;
	पूर्ण अन्यथा अणु
		/*
		 * Mark the execute_only_pkey as not available क्रम
		 * user allocation via pkey_alloc.
		 */
		reserved_allocation_mask |= (0x1 << execute_only_key);

		/*
		 * Deny READ/WRITE क्रम execute_only_key.
		 * Allow execute in IAMR.
		 */
		शेष_amr  |= (0x3ul << pkeyshअगरt(execute_only_key));
		शेष_iamr &= ~(0x1ul << pkeyshअगरt(execute_only_key));

		/*
		 * Clear the uamor bits क्रम this key.
		 */
		शेष_uamor &= ~(0x3ul << pkeyshअगरt(execute_only_key));
	पूर्ण

	अगर (unlikely(num_pkey <= 3)) अणु
		/*
		 * Insufficient number of keys to support
		 * KUAP/KUEP feature.
		 */
		disable_kuep = true;
		disable_kuap = true;
		WARN(1, "Disabling kernel user protection due to low (%d) max supported keys\n", num_pkey);
	पूर्ण अन्यथा अणु
		/*  handle key which is used by kernel क्रम KAUP */
		reserved_allocation_mask |= (0x1 << 3);
		/*
		 * Mark access क्रम kup_key in शेष amr so that
		 * we जारी to operate with that AMR in
		 * copy_to/from_user().
		 */
		शेष_amr   &= ~(0x3ul << pkeyshअगरt(3));
		शेष_iamr  &= ~(0x1ul << pkeyshअगरt(3));
		शेष_uamor &= ~(0x3ul << pkeyshअगरt(3));
	पूर्ण

	/*
	 * Allow access क्रम only key 0. And prevent any other modअगरication.
	 */
	शेष_amr   &= ~(0x3ul << pkeyshअगरt(0));
	शेष_iamr  &= ~(0x1ul << pkeyshअगरt(0));
	शेष_uamor &= ~(0x3ul << pkeyshअगरt(0));
	/*
	 * key 0 is special in that we want to consider it an allocated
	 * key which is pपुनः_स्मृतिated. We करोn't allow changing AMR bits
	 * w.r.t key 0. But one can pkey_मुक्त(key0)
	 */
	initial_allocation_mask |= (0x1 << 0);

	/*
	 * key 1 is recommended not to be used. PowerISA(3.0) page 1015,
	 * programming note.
	 */
	reserved_allocation_mask |= (0x1 << 1);
	शेष_uamor &= ~(0x3ul << pkeyshअगरt(1));

	/*
	 * Prevent the usage of OS reserved keys. Update UAMOR
	 * क्रम those keys. Also mark the rest of the bits in the
	 * 32 bit mask as reserved.
	 */
	क्रम (i = num_pkey; i < 32 ; i++) अणु
		reserved_allocation_mask |= (0x1 << i);
		शेष_uamor &= ~(0x3ul << pkeyshअगरt(i));
	पूर्ण
	/*
	 * Prevent the allocation of reserved keys too.
	 */
	initial_allocation_mask |= reserved_allocation_mask;

	pr_info("Enabling pkeys with max key count %d\n", num_pkey);
out:
	/*
	 * Setup uamor on boot cpu
	 */
	mtspr(SPRN_UAMOR, शेष_uamor);

	वापस;
पूर्ण

#अगर_घोषित CONFIG_PPC_KUEP
व्योम setup_kuep(bool disabled)
अणु
	अगर (disabled)
		वापस;
	/*
	 * On hash अगर PKEY feature is not enabled, disable KUAP too.
	 */
	अगर (!early_radix_enabled() && !early_mmu_has_feature(MMU_FTR_PKEY))
		वापस;

	अगर (smp_processor_id() == boot_cpuid) अणु
		pr_info("Activating Kernel Userspace Execution Prevention\n");
		cur_cpu_spec->mmu_features |= MMU_FTR_BOOK3S_KUEP;
	पूर्ण

	/*
	 * Radix always uses key0 of the IAMR to determine अगर an access is
	 * allowed. We set bit 0 (IBM bit 1) of key0, to prevent inकाष्ठाion
	 * fetch.
	 */
	mtspr(SPRN_IAMR, AMR_KUEP_BLOCKED);
	isync();
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_KUAP
व्योम setup_kuap(bool disabled)
अणु
	अगर (disabled)
		वापस;
	/*
	 * On hash अगर PKEY feature is not enabled, disable KUAP too.
	 */
	अगर (!early_radix_enabled() && !early_mmu_has_feature(MMU_FTR_PKEY))
		वापस;

	अगर (smp_processor_id() == boot_cpuid) अणु
		pr_info("Activating Kernel Userspace Access Prevention\n");
		cur_cpu_spec->mmu_features |= MMU_FTR_BOOK3S_KUAP;
	पूर्ण

	/*
	 * Set the शेष kernel AMR values on all cpus.
	 */
	mtspr(SPRN_AMR, AMR_KUAP_BLOCKED);
	isync();
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_MEM_KEYS
व्योम pkey_mm_init(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (!mmu_has_feature(MMU_FTR_PKEY))
		वापस;
	mm_pkey_allocation_map(mm) = initial_allocation_mask;
	mm->context.execute_only_pkey = execute_only_key;
पूर्ण

अटल अंतरभूत व्योम init_amr(पूर्णांक pkey, u8 init_bits)
अणु
	u64 new_amr_bits = (((u64)init_bits & 0x3UL) << pkeyshअगरt(pkey));
	u64 old_amr = current_thपढ़ो_amr() & ~((u64)(0x3ul) << pkeyshअगरt(pkey));

	current->thपढ़ो.regs->amr = old_amr | new_amr_bits;
पूर्ण

अटल अंतरभूत व्योम init_iamr(पूर्णांक pkey, u8 init_bits)
अणु
	u64 new_iamr_bits = (((u64)init_bits & 0x1UL) << pkeyshअगरt(pkey));
	u64 old_iamr = current_thपढ़ो_iamr() & ~((u64)(0x1ul) << pkeyshअगरt(pkey));

	अगर (!likely(pkey_execute_disable_supported))
		वापस;

	current->thपढ़ो.regs->iamr = old_iamr | new_iamr_bits;
पूर्ण

/*
 * Set the access rights in AMR IAMR and UAMOR रेजिस्टरs क्रम @pkey to that
 * specअगरied in @init_val.
 */
पूर्णांक __arch_set_user_pkey_access(काष्ठा task_काष्ठा *tsk, पूर्णांक pkey,
				अचिन्हित दीर्घ init_val)
अणु
	u64 new_amr_bits = 0x0ul;
	u64 new_iamr_bits = 0x0ul;
	u64 pkey_bits, uamor_pkey_bits;

	/*
	 * Check whether the key is disabled by UAMOR.
	 */
	pkey_bits = 0x3ul << pkeyshअगरt(pkey);
	uamor_pkey_bits = (शेष_uamor & pkey_bits);

	/*
	 * Both the bits in UAMOR corresponding to the key should be set
	 */
	अगर (uamor_pkey_bits != pkey_bits)
		वापस -EINVAL;

	अगर (init_val & PKEY_DISABLE_EXECUTE) अणु
		अगर (!pkey_execute_disable_supported)
			वापस -EINVAL;
		new_iamr_bits |= IAMR_EX_BIT;
	पूर्ण
	init_iamr(pkey, new_iamr_bits);

	/* Set the bits we need in AMR: */
	अगर (init_val & PKEY_DISABLE_ACCESS)
		new_amr_bits |= AMR_RD_BIT | AMR_WR_BIT;
	अन्यथा अगर (init_val & PKEY_DISABLE_WRITE)
		new_amr_bits |= AMR_WR_BIT;

	init_amr(pkey, new_amr_bits);
	वापस 0;
पूर्ण

पूर्णांक execute_only_pkey(काष्ठा mm_काष्ठा *mm)
अणु
	वापस mm->context.execute_only_pkey;
पूर्ण

अटल अंतरभूत bool vma_is_pkey_exec_only(काष्ठा vm_area_काष्ठा *vma)
अणु
	/* Do this check first since the vm_flags should be hot */
	अगर ((vma->vm_flags & VM_ACCESS_FLAGS) != VM_EXEC)
		वापस false;

	वापस (vma_pkey(vma) == vma->vm_mm->context.execute_only_pkey);
पूर्ण

/*
 * This should only be called क्रम *plain* mprotect calls.
 */
पूर्णांक __arch_override_mprotect_pkey(काष्ठा vm_area_काष्ठा *vma, पूर्णांक prot,
				  पूर्णांक pkey)
अणु
	/*
	 * If the currently associated pkey is execute-only, but the requested
	 * protection is not execute-only, move it back to the शेष pkey.
	 */
	अगर (vma_is_pkey_exec_only(vma) && (prot != PROT_EXEC))
		वापस 0;

	/*
	 * The requested protection is execute-only. Hence let's use an
	 * execute-only pkey.
	 */
	अगर (prot == PROT_EXEC) अणु
		pkey = execute_only_pkey(vma->vm_mm);
		अगर (pkey > 0)
			वापस pkey;
	पूर्ण

	/* Nothing to override. */
	वापस vma_pkey(vma);
पूर्ण

अटल bool pkey_access_permitted(पूर्णांक pkey, bool ग_लिखो, bool execute)
अणु
	पूर्णांक pkey_shअगरt;
	u64 amr;

	pkey_shअगरt = pkeyshअगरt(pkey);
	अगर (execute)
		वापस !(current_thपढ़ो_iamr() & (IAMR_EX_BIT << pkey_shअगरt));

	amr = current_thपढ़ो_amr();
	अगर (ग_लिखो)
		वापस !(amr & (AMR_WR_BIT << pkey_shअगरt));

	वापस !(amr & (AMR_RD_BIT << pkey_shअगरt));
पूर्ण

bool arch_pte_access_permitted(u64 pte, bool ग_लिखो, bool execute)
अणु
	अगर (!mmu_has_feature(MMU_FTR_PKEY))
		वापस true;

	वापस pkey_access_permitted(pte_to_pkey_bits(pte), ग_लिखो, execute);
पूर्ण

/*
 * We only want to enक्रमce protection keys on the current thपढ़ो because we
 * effectively have no access to AMR/IAMR क्रम other thपढ़ोs or any way to tell
 * which AMR/IAMR in a thपढ़ोed process we could use.
 *
 * So करो not enक्रमce things अगर the VMA is not from the current mm, or अगर we are
 * in a kernel thपढ़ो.
 */
bool arch_vma_access_permitted(काष्ठा vm_area_काष्ठा *vma, bool ग_लिखो,
			       bool execute, bool क्रमeign)
अणु
	अगर (!mmu_has_feature(MMU_FTR_PKEY))
		वापस true;
	/*
	 * Do not enक्रमce our key-permissions on a क्रमeign vma.
	 */
	अगर (क्रमeign || vma_is_क्रमeign(vma))
		वापस true;

	वापस pkey_access_permitted(vma_pkey(vma), ग_लिखो, execute);
पूर्ण

व्योम arch_dup_pkeys(काष्ठा mm_काष्ठा *oldmm, काष्ठा mm_काष्ठा *mm)
अणु
	अगर (!mmu_has_feature(MMU_FTR_PKEY))
		वापस;

	/* Duplicate the oldmm pkey state in mm: */
	mm_pkey_allocation_map(mm) = mm_pkey_allocation_map(oldmm);
	mm->context.execute_only_pkey = oldmm->context.execute_only_pkey;
पूर्ण

#पूर्ण_अगर /* CONFIG_PPC_MEM_KEYS */
