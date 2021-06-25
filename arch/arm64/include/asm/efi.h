<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_EFI_H
#घोषणा _ASM_EFI_H

#समावेश <यंत्र/boot.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/fpsimd.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/tlbflush.h>

#अगर_घोषित CONFIG_EFI
बाह्य व्योम efi_init(व्योम);
#अन्यथा
#घोषणा efi_init()
#पूर्ण_अगर

पूर्णांक efi_create_mapping(काष्ठा mm_काष्ठा *mm, efi_memory_desc_t *md);
पूर्णांक efi_set_mapping_permissions(काष्ठा mm_काष्ठा *mm, efi_memory_desc_t *md);

#घोषणा arch_efi_call_virt_setup()					\
(अणु									\
	efi_virपंचांगap_load();						\
	__efi_fpsimd_begin();						\
पूर्ण)

#घोषणा arch_efi_call_virt(p, f, args...)				\
(अणु									\
	efi_##f##_t *__f;						\
	__f = p->f;							\
	__efi_rt_यंत्र_wrapper(__f, #f, args);				\
पूर्ण)

#घोषणा arch_efi_call_virt_tearकरोwn()					\
(अणु									\
	__efi_fpsimd_end();						\
	efi_virपंचांगap_unload();						\
पूर्ण)

efi_status_t __efi_rt_यंत्र_wrapper(व्योम *, स्थिर अक्षर *, ...);

#घोषणा ARCH_EFI_IRQ_FLAGS_MASK (PSR_D_BIT | PSR_A_BIT | PSR_I_BIT | PSR_F_BIT)

/*
 * Even when Linux uses IRQ priorities क्रम IRQ disabling, EFI करोes not.
 * And EFI shouldn't really play around with priority masking as it is not aware
 * which priorities the OS has asचिन्हित to its पूर्णांकerrupts.
 */
#घोषणा arch_efi_save_flags(state_flags)		\
	((व्योम)((state_flags) = पढ़ो_sysreg(daअगर)))

#घोषणा arch_efi_restore_flags(state_flags)	ग_लिखो_sysreg(state_flags, daअगर)


/* arch specअगरic definitions used by the stub code */

/*
 * In some configurations (e.g. VMAP_STACK && 64K pages), stacks built पूर्णांकo the
 * kernel need greater alignment than we require the segments to be padded to.
 */
#घोषणा EFI_KIMG_ALIGN	\
	(SEGMENT_ALIGN > THREAD_ALIGN ? SEGMENT_ALIGN : THREAD_ALIGN)

/*
 * On arm64, we have to ensure that the initrd ends up in the linear region,
 * which is a 1 GB aligned region of size '1UL << (VA_BITS_MIN - 1)' that is
 * guaranteed to cover the kernel Image.
 *
 * Since the EFI stub is part of the kernel Image, we can relax the
 * usual requirements in Documentation/arm64/booting.rst, which still
 * apply to other bootloaders, and are required क्रम some kernel
 * configurations.
 */
अटल अंतरभूत अचिन्हित दीर्घ efi_get_max_initrd_addr(अचिन्हित दीर्घ image_addr)
अणु
	वापस (image_addr & ~(SZ_1G - 1UL)) + (1UL << (VA_BITS_MIN - 1));
पूर्ण

#घोषणा alloc_screen_info(x...)		&screen_info

अटल अंतरभूत व्योम मुक्त_screen_info(काष्ठा screen_info *si)
अणु
पूर्ण

अटल अंतरभूत व्योम efअगरb_setup_from_dmi(काष्ठा screen_info *si, स्थिर अक्षर *opt)
अणु
पूर्ण

#घोषणा EFI_ALLOC_ALIGN		SZ_64K

/*
 * On ARM प्रणालीs, भवly remapped UEFI runसमय services are set up in two
 * distinct stages:
 * - The stub retrieves the final version of the memory map from UEFI, populates
 *   the virt_addr fields and calls the SetVirtualAddressMap() [SVAM] runसमय
 *   service to communicate the new mapping to the firmware (Note that the new
 *   mapping is not live at this समय)
 * - During an early initcall(), the EFI प्रणाली table is permanently remapped
 *   and the भव remapping of the UEFI Runसमय Services regions is loaded
 *   पूर्णांकo a निजी set of page tables. If this all succeeds, the Runसमय
 *   Services are enabled and the EFI_RUNTIME_SERVICES bit set.
 */

अटल अंतरभूत व्योम efi_set_pgd(काष्ठा mm_काष्ठा *mm)
अणु
	__चयन_mm(mm);

	अगर (प्रणाली_uses_ttbr0_pan()) अणु
		अगर (mm != current->active_mm) अणु
			/*
			 * Update the current thपढ़ो's saved ttbr0 since it is
			 * restored as part of a वापस from exception. Enable
			 * access to the valid TTBR0_EL1 and invoke the errata
			 * workaround directly since there is no वापस from
			 * exception when invoking the EFI run-समय services.
			 */
			update_saved_ttbr0(current, mm);
			uaccess_ttbr0_enable();
			post_ttbr_update_workaround();
		पूर्ण अन्यथा अणु
			/*
			 * Defer the चयन to the current thपढ़ो's TTBR0_EL1
			 * until uaccess_enable(). Restore the current
			 * thपढ़ो's saved ttbr0 corresponding to its active_mm
			 */
			uaccess_ttbr0_disable();
			update_saved_ttbr0(current, current->active_mm);
		पूर्ण
	पूर्ण
पूर्ण

व्योम efi_virपंचांगap_load(व्योम);
व्योम efi_virपंचांगap_unload(व्योम);

अटल अंतरभूत व्योम efi_capsule_flush_cache_range(व्योम *addr, पूर्णांक size)
अणु
	__flush_dcache_area(addr, size);
पूर्ण

#पूर्ण_अगर /* _ASM_EFI_H */
