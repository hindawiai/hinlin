<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2020 Western Digital Corporation or its affiliates.
 */
#अगर_अघोषित _ASM_EFI_H
#घोषणा _ASM_EFI_H

#समावेश <यंत्र/csr.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/tlbflush.h>

#अगर_घोषित CONFIG_EFI
बाह्य व्योम efi_init(व्योम);
#अन्यथा
#घोषणा efi_init()
#पूर्ण_अगर

पूर्णांक efi_create_mapping(काष्ठा mm_काष्ठा *mm, efi_memory_desc_t *md);
पूर्णांक efi_set_mapping_permissions(काष्ठा mm_काष्ठा *mm, efi_memory_desc_t *md);

#घोषणा arch_efi_call_virt_setup()      efi_virपंचांगap_load()
#घोषणा arch_efi_call_virt_tearकरोwn()   efi_virपंचांगap_unload()

#घोषणा arch_efi_call_virt(p, f, args...) p->f(args)

#घोषणा ARCH_EFI_IRQ_FLAGS_MASK (SR_IE | SR_SPIE)

/* Load initrd at enough distance from DRAM start */
अटल अंतरभूत अचिन्हित दीर्घ efi_get_max_initrd_addr(अचिन्हित दीर्घ image_addr)
अणु
	वापस image_addr + SZ_256M;
पूर्ण

#घोषणा alloc_screen_info(x...)		(&screen_info)

अटल अंतरभूत व्योम मुक्त_screen_info(काष्ठा screen_info *si)
अणु
पूर्ण

अटल अंतरभूत व्योम efअगरb_setup_from_dmi(काष्ठा screen_info *si, स्थिर अक्षर *opt)
अणु
पूर्ण

व्योम efi_virपंचांगap_load(व्योम);
व्योम efi_virपंचांगap_unload(व्योम);

#पूर्ण_अगर /* _ASM_EFI_H */
