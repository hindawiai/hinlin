<शैली गुरु>
#अगर_अघोषित _ASM_POWERPC_VMALLOC_H
#घोषणा _ASM_POWERPC_VMALLOC_H

#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/page.h>

#अगर_घोषित CONFIG_HAVE_ARCH_HUGE_VMAP

#घोषणा arch_vmap_pud_supported arch_vmap_pud_supported
अटल अंतरभूत bool arch_vmap_pud_supported(pgprot_t prot)
अणु
	/* HPT करोes not cope with large pages in the vदो_स्मृति area */
	वापस radix_enabled();
पूर्ण

#घोषणा arch_vmap_pmd_supported arch_vmap_pmd_supported
अटल अंतरभूत bool arch_vmap_pmd_supported(pgprot_t prot)
अणु
	वापस radix_enabled();
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_POWERPC_VMALLOC_H */
