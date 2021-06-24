<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_MMU_H
#घोषणा __ASM_MMU_H

#समावेश <यंत्र/cputype.h>

#घोषणा MMCF_AARCH32	0x1	/* mm context flag क्रम AArch32 executables */
#घोषणा USER_ASID_BIT	48
#घोषणा USER_ASID_FLAG	(UL(1) << USER_ASID_BIT)
#घोषणा TTBR_ASID_MASK	(UL(0xffff) << 48)

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/refcount.h>

प्रकार काष्ठा अणु
	atomic64_t	id;
#अगर_घोषित CONFIG_COMPAT
	व्योम		*sigpage;
#पूर्ण_अगर
	refcount_t	pinned;
	व्योम		*vdso;
	अचिन्हित दीर्घ	flags;
पूर्ण mm_context_t;

/*
 * This macro is only used by the TLBI and low-level चयन_mm() code,
 * neither of which can race with an ASID change. We thereक्रमe करोn't
 * need to reload the counter using atomic64_पढ़ो().
 */
#घोषणा ASID(mm)	((mm)->context.id.counter & 0xffff)

अटल अंतरभूत bool arm64_kernel_unmapped_at_el0(व्योम)
अणु
	वापस cpus_have_स्थिर_cap(ARM64_UNMAP_KERNEL_AT_EL0);
पूर्ण

बाह्य व्योम arm64_memblock_init(व्योम);
बाह्य व्योम paging_init(व्योम);
बाह्य व्योम booपंचांगem_init(व्योम);
बाह्य व्योम __iomem *early_io_map(phys_addr_t phys, अचिन्हित दीर्घ virt);
बाह्य व्योम init_mem_pgprot(व्योम);
बाह्य व्योम create_pgd_mapping(काष्ठा mm_काष्ठा *mm, phys_addr_t phys,
			       अचिन्हित दीर्घ virt, phys_addr_t size,
			       pgprot_t prot, bool page_mappings_only);
बाह्य व्योम *fixmap_remap_fdt(phys_addr_t dt_phys, पूर्णांक *size, pgprot_t prot);
बाह्य व्योम mark_linear_text_alias_ro(व्योम);
बाह्य bool kaslr_requires_kpti(व्योम);

#घोषणा INIT_MM_CONTEXT(name)	\
	.pgd = init_pg_dir,

#पूर्ण_अगर	/* !__ASSEMBLY__ */
#पूर्ण_अगर
