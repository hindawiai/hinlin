<शैली गुरु>
#अगर_अघोषित _ASM_X86_VMALLOC_H
#घोषणा _ASM_X86_VMALLOC_H

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pgtable_areas.h>

#अगर_घोषित CONFIG_HAVE_ARCH_HUGE_VMAP

#अगर_घोषित CONFIG_X86_64
#घोषणा arch_vmap_pud_supported arch_vmap_pud_supported
अटल अंतरभूत bool arch_vmap_pud_supported(pgprot_t prot)
अणु
	वापस boot_cpu_has(X86_FEATURE_GBPAGES);
पूर्ण
#पूर्ण_अगर

#घोषणा arch_vmap_pmd_supported arch_vmap_pmd_supported
अटल अंतरभूत bool arch_vmap_pmd_supported(pgprot_t prot)
अणु
	वापस boot_cpu_has(X86_FEATURE_PSE);
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_VMALLOC_H */
