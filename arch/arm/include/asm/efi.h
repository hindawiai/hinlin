<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2015 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#अगर_अघोषित __ASM_ARM_EFI_H
#घोषणा __ASM_ARM_EFI_H

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cachetype.h>
#समावेश <यंत्र/early_ioremap.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/highस्मृति.स>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/ptrace.h>

#अगर_घोषित CONFIG_EFI
व्योम efi_init(व्योम);

पूर्णांक efi_create_mapping(काष्ठा mm_काष्ठा *mm, efi_memory_desc_t *md);
पूर्णांक efi_set_mapping_permissions(काष्ठा mm_काष्ठा *mm, efi_memory_desc_t *md);

#घोषणा arch_efi_call_virt_setup()	efi_virपंचांगap_load()
#घोषणा arch_efi_call_virt_tearकरोwn()	efi_virपंचांगap_unload()

#घोषणा arch_efi_call_virt(p, f, args...)				\
(अणु									\
	efi_##f##_t *__f;						\
	__f = p->f;							\
	__f(args);							\
पूर्ण)

#घोषणा ARCH_EFI_IRQ_FLAGS_MASK \
	(PSR_J_BIT | PSR_E_BIT | PSR_A_BIT | PSR_I_BIT | PSR_F_BIT | \
	 PSR_T_BIT | MODE_MASK)

अटल अंतरभूत व्योम efi_set_pgd(काष्ठा mm_काष्ठा *mm)
अणु
	check_and_चयन_context(mm, शून्य);
पूर्ण

व्योम efi_virपंचांगap_load(व्योम);
व्योम efi_virपंचांगap_unload(व्योम);

#अन्यथा
#घोषणा efi_init()
#पूर्ण_अगर /* CONFIG_EFI */

/* arch specअगरic definitions used by the stub code */

काष्ठा screen_info *alloc_screen_info(व्योम);
व्योम मुक्त_screen_info(काष्ठा screen_info *si);

अटल अंतरभूत व्योम efअगरb_setup_from_dmi(काष्ठा screen_info *si, स्थिर अक्षर *opt)
अणु
पूर्ण

/*
 * A reasonable upper bound क्रम the uncompressed kernel size is 32 MBytes,
 * so we will reserve that amount of memory. We have no easy way to tell what
 * the actuall size of code + data the uncompressed kernel will use.
 * If this is insufficient, the decompressor will relocate itself out of the
 * way beक्रमe perक्रमming the decompression.
 */
#घोषणा MAX_UNCOMP_KERNEL_SIZE	SZ_32M

/*
 * phys-to-virt patching requires that the physical to भव offset is a
 * multiple of 2 MiB. However, using an alignment smaller than TEXT_OFFSET
 * here throws off the memory allocation logic, so let's use the lowest घातer
 * of two greater than 2 MiB and greater than TEXT_OFFSET.
 */
#घोषणा EFI_PHYS_ALIGN		max(UL(SZ_2M), roundup_घात_of_two(TEXT_OFFSET))

/* on ARM, the initrd should be loaded in a lowmem region */
अटल अंतरभूत अचिन्हित दीर्घ efi_get_max_initrd_addr(अचिन्हित दीर्घ image_addr)
अणु
	वापस round_करोwn(image_addr, SZ_4M) + SZ_512M;
पूर्ण

काष्ठा efi_arm_entry_state अणु
	u32	cpsr_beक्रमe_ebs;
	u32	sctlr_beक्रमe_ebs;
	u32	cpsr_after_ebs;
	u32	sctlr_after_ebs;
पूर्ण;

अटल अंतरभूत व्योम efi_capsule_flush_cache_range(व्योम *addr, पूर्णांक size)
अणु
	__cpuc_flush_dcache_area(addr, size);
पूर्ण

#पूर्ण_अगर /* _ASM_ARM_EFI_H */
