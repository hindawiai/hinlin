<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MMU_H
#घोषणा __MMU_H

/*
 * Privileged Space Mapping Buffer (PMB) definitions
 */
#घोषणा PMB_PASCR		0xff000070
#घोषणा PMB_IRMCR		0xff000078

#घोषणा PASCR_SE		0x80000000

#घोषणा PMB_ADDR		0xf6100000
#घोषणा PMB_DATA		0xf7100000

#घोषणा NR_PMB_ENTRIES		16

#घोषणा PMB_E_MASK		0x0000000f
#घोषणा PMB_E_SHIFT		8

#घोषणा PMB_PFN_MASK		0xff000000

#घोषणा PMB_SZ_16M		0x00000000
#घोषणा PMB_SZ_64M		0x00000010
#घोषणा PMB_SZ_128M		0x00000080
#घोषणा PMB_SZ_512M		0x00000090
#घोषणा PMB_SZ_MASK		PMB_SZ_512M
#घोषणा PMB_C			0x00000008
#घोषणा PMB_WT			0x00000001
#घोषणा PMB_UB			0x00000200
#घोषणा PMB_CACHE_MASK		(PMB_C | PMB_WT | PMB_UB)
#घोषणा PMB_V			0x00000100

#घोषणा PMB_NO_ENTRY		(-1)

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/thपढ़ोs.h>
#समावेश <यंत्र/page.h>

/* Default "unsigned long" context */
प्रकार अचिन्हित दीर्घ mm_context_id_t[NR_CPUS];

प्रकार काष्ठा अणु
#अगर_घोषित CONFIG_MMU
	mm_context_id_t		id;
	व्योम			*vdso;
#अन्यथा
	अचिन्हित दीर्घ		end_brk;
#पूर्ण_अगर
#अगर_घोषित CONFIG_BINFMT_ELF_FDPIC
	अचिन्हित दीर्घ		exec_fdpic_loadmap;
	अचिन्हित दीर्घ		पूर्णांकerp_fdpic_loadmap;
#पूर्ण_अगर
पूर्ण mm_context_t;

#अगर_घोषित CONFIG_PMB
/* arch/sh/mm/pmb.c */
bool __in_29bit_mode(व्योम);

व्योम pmb_init(व्योम);
पूर्णांक pmb_bolt_mapping(अचिन्हित दीर्घ virt, phys_addr_t phys,
		     अचिन्हित दीर्घ size, pgprot_t prot);
व्योम __iomem *pmb_remap_caller(phys_addr_t phys, अचिन्हित दीर्घ size,
			       pgprot_t prot, व्योम *caller);
पूर्णांक pmb_unmap(व्योम __iomem *addr);

#अन्यथा

अटल अंतरभूत पूर्णांक
pmb_bolt_mapping(अचिन्हित दीर्घ virt, phys_addr_t phys,
		 अचिन्हित दीर्घ size, pgprot_t prot)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम __iomem *
pmb_remap_caller(phys_addr_t phys, अचिन्हित दीर्घ size,
		 pgprot_t prot, व्योम *caller)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक pmb_unmap(व्योम __iomem *addr)
अणु
	वापस -EINVAL;
पूर्ण

#घोषणा pmb_init(addr)		करो अणु पूर्ण जबतक (0)

#अगर_घोषित CONFIG_29BIT
#घोषणा __in_29bit_mode()	(1)
#अन्यथा
#घोषणा __in_29bit_mode()	(0)
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_PMB */

अटल अंतरभूत व्योम __iomem *
pmb_remap(phys_addr_t phys, अचिन्हित दीर्घ size, pgprot_t prot)
अणु
	वापस pmb_remap_caller(phys, size, prot, __builtin_वापस_address(0));
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __MMU_H */
