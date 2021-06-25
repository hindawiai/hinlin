<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_MMU_8XX_H_
#घोषणा _ASM_POWERPC_MMU_8XX_H_
/*
 * PPC8xx support
 */

/* Control/status रेजिस्टरs क्रम the MPC8xx.
 * A ग_लिखो operation to these रेजिस्टरs causes serialized access.
 * During software tablewalk, the रेजिस्टरs used perक्रमm mask/shअगरt-add
 * operations when written/पढ़ो.  A TLB entry is created when the Mx_RPN
 * is written, and the contents of several रेजिस्टरs are used to
 * create the entry.
 */
#घोषणा SPRN_MI_CTR	784	/* Inकाष्ठाion TLB control रेजिस्टर */
#घोषणा MI_GPM		0x80000000	/* Set करोमुख्य manager mode */
#घोषणा MI_PPM		0x40000000	/* Set subpage protection */
#घोषणा MI_CIDEF	0x20000000	/* Set cache inhibit when MMU dis */
#घोषणा MI_RSV4I	0x08000000	/* Reserve 4 TLB entries */
#घोषणा MI_PPCS		0x02000000	/* Use MI_RPN prob/priv state */
#घोषणा MI_IDXMASK	0x00001f00	/* TLB index to be loaded */

/* These are the Ks and Kp from the PowerPC books.  For proper operation,
 * Ks = 0, Kp = 1.
 */
#घोषणा SPRN_MI_AP	786
#घोषणा MI_Ks		0x80000000	/* Should not be set */
#घोषणा MI_Kp		0x40000000	/* Should always be set */

/*
 * All pages' PP data bits are set to either 001 or 011 by copying _PAGE_EXEC
 * पूर्णांकo bit 21 in the ITLBmiss handler (bit 21 is the middle bit), which means
 * respectively NA क्रम All or X क्रम Supervisor and no access क्रम User.
 * Then we use the APG to say whether accesses are according to Page rules or
 * "all Supervisor" rules (Access to all)
 * _PAGE_ACCESSED is also managed via APG. When _PAGE_ACCESSED is not set, say
 * "all User" rules, that will lead to NA क्रम all.
 * Thereक्रमe, we define 4 APG groups. lsb is _PAGE_ACCESSED
 * 0 => Kernel => 11 (all accesses perक्रमmed according as user iaw page definition)
 * 1 => Kernel+Accessed => 01 (all accesses perक्रमmed according to page definition)
 * 2 => User => 11 (all accesses perक्रमmed according as user iaw page definition)
 * 3 => User+Accessed => 00 (all accesses perक्रमmed as supervisor iaw page definition) क्रम INIT
 *                    => 10 (all accesses perक्रमmed according to swaped page definition) क्रम KUEP
 * 4-15 => Not Used
 */
#घोषणा MI_APG_INIT	0xdc000000
#घोषणा MI_APG_KUEP	0xde000000

/* The effective page number रेजिस्टर.  When पढ़ो, contains the inक्रमmation
 * about the last inकाष्ठाion TLB miss.  When MI_RPN is written, bits in
 * this रेजिस्टर are used to create the TLB entry.
 */
#घोषणा SPRN_MI_EPN	787
#घोषणा MI_EPNMASK	0xfffff000	/* Effective page number क्रम entry */
#घोषणा MI_EVALID	0x00000200	/* Entry is valid */
#घोषणा MI_ASIDMASK	0x0000000f	/* ASID match value */
					/* Reset value is undefined */

/* A "level 1" or "segment" or whatever you want to call it रेजिस्टर.
 * For the inकाष्ठाion TLB, it contains bits that get loaded पूर्णांकo the
 * TLB entry when the MI_RPN is written.
 */
#घोषणा SPRN_MI_TWC	789
#घोषणा MI_APG		0x000001e0	/* Access protection group (0) */
#घोषणा MI_GUARDED	0x00000010	/* Guarded storage */
#घोषणा MI_PSMASK	0x0000000c	/* Mask of page size bits */
#घोषणा MI_PS8MEG	0x0000000c	/* 8M page size */
#घोषणा MI_PS512K	0x00000004	/* 512K page size */
#घोषणा MI_PS4K_16K	0x00000000	/* 4K or 16K page size */
#घोषणा MI_SVALID	0x00000001	/* Segment entry is valid */
					/* Reset value is undefined */

/* Real page number.  Defined by the pte.  Writing this रेजिस्टर
 * causes a TLB entry to be created क्रम the inकाष्ठाion TLB, using
 * additional inक्रमmation from the MI_EPN, and MI_TWC रेजिस्टरs.
 */
#घोषणा SPRN_MI_RPN	790
#घोषणा MI_SPS16K	0x00000008	/* Small page size (0 = 4k, 1 = 16k) */

/* Define an RPN value क्रम mapping kernel memory to large भव
 * pages क्रम boot initialization.  This has real page number of 0,
 * large page size, shared page, cache enabled, and valid.
 * Also mark all subpages valid and ग_लिखो access.
 */
#घोषणा MI_BOOTINIT	0x000001fd

#घोषणा SPRN_MD_CTR	792	/* Data TLB control रेजिस्टर */
#घोषणा MD_GPM		0x80000000	/* Set करोमुख्य manager mode */
#घोषणा MD_PPM		0x40000000	/* Set subpage protection */
#घोषणा MD_CIDEF	0x20000000	/* Set cache inhibit when MMU dis */
#घोषणा MD_WTDEF	0x10000000	/* Set ग_लिखोthrough when MMU dis */
#घोषणा MD_RSV4I	0x08000000	/* Reserve 4 TLB entries */
#घोषणा MD_TWAM		0x04000000	/* Use 4K page hardware assist */
#घोषणा MD_PPCS		0x02000000	/* Use MI_RPN prob/priv state */
#घोषणा MD_IDXMASK	0x00001f00	/* TLB index to be loaded */

#घोषणा SPRN_M_CASID	793	/* Address space ID (context) to match */
#घोषणा MC_ASIDMASK	0x0000000f	/* Bits used क्रम ASID value */


/* These are the Ks and Kp from the PowerPC books.  For proper operation,
 * Ks = 0, Kp = 1.
 */
#घोषणा SPRN_MD_AP	794
#घोषणा MD_Ks		0x80000000	/* Should not be set */
#घोषणा MD_Kp		0x40000000	/* Should always be set */

/* See explanation above at the definition of MI_APG_INIT */
#घोषणा MD_APG_INIT	0xdc000000
#घोषणा MD_APG_KUAP	0xde000000

/* The effective page number रेजिस्टर.  When पढ़ो, contains the inक्रमmation
 * about the last inकाष्ठाion TLB miss.  When MD_RPN is written, bits in
 * this रेजिस्टर are used to create the TLB entry.
 */
#घोषणा SPRN_MD_EPN	795
#घोषणा MD_EPNMASK	0xfffff000	/* Effective page number क्रम entry */
#घोषणा MD_EVALID	0x00000200	/* Entry is valid */
#घोषणा MD_ASIDMASK	0x0000000f	/* ASID match value */
					/* Reset value is undefined */

/* The poपूर्णांकer to the base address of the first level page table.
 * During a software tablewalk, पढ़ोing this रेजिस्टर provides the address
 * of the entry associated with MD_EPN.
 */
#घोषणा SPRN_M_TWB	796
#घोषणा	M_L1TB		0xfffff000	/* Level 1 table base address */
#घोषणा M_L1INDX	0x00000ffc	/* Level 1 index, when पढ़ो */
					/* Reset value is undefined */

/* A "level 1" or "segment" or whatever you want to call it रेजिस्टर.
 * For the data TLB, it contains bits that get loaded पूर्णांकo the TLB entry
 * when the MD_RPN is written.  It is also provides the hardware assist
 * क्रम finding the PTE address during software tablewalk.
 */
#घोषणा SPRN_MD_TWC	797
#घोषणा MD_L2TB		0xfffff000	/* Level 2 table base address */
#घोषणा MD_L2INDX	0xfffffe00	/* Level 2 index (*pte), when पढ़ो */
#घोषणा MD_APG		0x000001e0	/* Access protection group (0) */
#घोषणा MD_GUARDED	0x00000010	/* Guarded storage */
#घोषणा MD_PSMASK	0x0000000c	/* Mask of page size bits */
#घोषणा MD_PS8MEG	0x0000000c	/* 8M page size */
#घोषणा MD_PS512K	0x00000004	/* 512K page size */
#घोषणा MD_PS4K_16K	0x00000000	/* 4K or 16K page size */
#घोषणा MD_WT		0x00000002	/* Use ग_लिखोthrough page attribute */
#घोषणा MD_SVALID	0x00000001	/* Segment entry is valid */
					/* Reset value is undefined */


/* Real page number.  Defined by the pte.  Writing this रेजिस्टर
 * causes a TLB entry to be created क्रम the data TLB, using
 * additional inक्रमmation from the MD_EPN, and MD_TWC रेजिस्टरs.
 */
#घोषणा SPRN_MD_RPN	798
#घोषणा MD_SPS16K	0x00000008	/* Small page size (0 = 4k, 1 = 16k) */

/* This is a temporary storage रेजिस्टर that could be used to save
 * a processor working रेजिस्टर during a tablewalk.
 */
#घोषणा SPRN_M_TW	799

#अगर defined(CONFIG_PPC_4K_PAGES)
#घोषणा mmu_भव_psize	MMU_PAGE_4K
#या_अगर defined(CONFIG_PPC_16K_PAGES)
#घोषणा mmu_भव_psize	MMU_PAGE_16K
#घोषणा PTE_FRAG_NR		4
#घोषणा PTE_FRAG_SIZE_SHIFT	12
#घोषणा PTE_FRAG_SIZE		(1UL << 12)
#अन्यथा
#त्रुटि "Unsupported PAGE_SIZE"
#पूर्ण_अगर

#घोषणा mmu_linear_psize	MMU_PAGE_8M

#घोषणा MODULES_VADDR	(PAGE_OFFSET - SZ_256M)
#घोषणा MODULES_END	PAGE_OFFSET

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/mmdebug.h>

व्योम mmu_pin_tlb(अचिन्हित दीर्घ top, bool पढ़ोonly);

प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक active;
	व्योम __user *vdso;
	व्योम *pte_frag;
पूर्ण mm_context_t;

#घोषणा PHYS_IMMR_BASE (mfspr(SPRN_IMMR) & 0xfff80000)
#घोषणा VIRT_IMMR_BASE (__fix_to_virt(FIX_IMMR_BASE))

/* Page size definitions, common between 32 and 64-bit
 *
 *    shअगरt : is the "PAGE_SHIFT" value क्रम that page size
 *    penc  : is the pte encoding mask
 *
 */
काष्ठा mmu_psize_def अणु
	अचिन्हित पूर्णांक	shअगरt;	/* number of bits */
	अचिन्हित पूर्णांक	enc;	/* PTE encoding */
	अचिन्हित पूर्णांक    ind;    /* Corresponding indirect page size shअगरt */
	अचिन्हित पूर्णांक	flags;
#घोषणा MMU_PAGE_SIZE_सूचीECT	0x1	/* Supported as a direct size */
#घोषणा MMU_PAGE_SIZE_INसूचीECT	0x2	/* Supported as an indirect size */
पूर्ण;

बाह्य काष्ठा mmu_psize_def mmu_psize_defs[MMU_PAGE_COUNT];

अटल अंतरभूत पूर्णांक shअगरt_to_mmu_psize(अचिन्हित पूर्णांक shअगरt)
अणु
	पूर्णांक psize;

	क्रम (psize = 0; psize < MMU_PAGE_COUNT; ++psize)
		अगर (mmu_psize_defs[psize].shअगरt == shअगरt)
			वापस psize;
	वापस -1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक mmu_pमाप_प्रकारo_shअगरt(अचिन्हित पूर्णांक mmu_psize)
अणु
	अगर (mmu_psize_defs[mmu_psize].shअगरt)
		वापस mmu_psize_defs[mmu_psize].shअगरt;
	BUG();
पूर्ण

/* patch sites */
बाह्य s32 patch__itlbmiss_निकास_1, patch__dtlbmiss_निकास_1;
बाह्य s32 patch__itlbmiss_perf, patch__dtlbmiss_perf;

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_POWERPC_MMU_8XX_H_ */
