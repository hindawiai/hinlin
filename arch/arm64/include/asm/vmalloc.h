<शैली गुरु>
#अगर_अघोषित _ASM_ARM64_VMALLOC_H
#घोषणा _ASM_ARM64_VMALLOC_H

#समावेश <यंत्र/page.h>

#अगर_घोषित CONFIG_HAVE_ARCH_HUGE_VMAP

#घोषणा arch_vmap_pud_supported arch_vmap_pud_supported
अटल अंतरभूत bool arch_vmap_pud_supported(pgprot_t prot)
अणु
	/*
	 * Only 4k granule supports level 1 block mappings.
	 * SW table walks can't handle removal of पूर्णांकermediate entries.
	 */
	वापस IS_ENABLED(CONFIG_ARM64_4K_PAGES) &&
	       !IS_ENABLED(CONFIG_PTDUMP_DEBUGFS);
पूर्ण

#घोषणा arch_vmap_pmd_supported arch_vmap_pmd_supported
अटल अंतरभूत bool arch_vmap_pmd_supported(pgprot_t prot)
अणु
	/* See arch_vmap_pud_supported() */
	वापस !IS_ENABLED(CONFIG_PTDUMP_DEBUGFS);
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_ARM64_VMALLOC_H */
