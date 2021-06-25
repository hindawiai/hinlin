<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_MMU_BOOK3E_H_
#घोषणा _ASM_POWERPC_MMU_BOOK3E_H_
/*
 * Freescale Book-E/Book-3e (ISA 2.06+) MMU support
 */

/* Book-3e defined page sizes */
#घोषणा BOOK3E_PAGESZ_1K	0
#घोषणा BOOK3E_PAGESZ_2K	1
#घोषणा BOOK3E_PAGESZ_4K	2
#घोषणा BOOK3E_PAGESZ_8K	3
#घोषणा BOOK3E_PAGESZ_16K	4
#घोषणा BOOK3E_PAGESZ_32K	5
#घोषणा BOOK3E_PAGESZ_64K	6
#घोषणा BOOK3E_PAGESZ_128K	7
#घोषणा BOOK3E_PAGESZ_256K	8
#घोषणा BOOK3E_PAGESZ_512K	9
#घोषणा BOOK3E_PAGESZ_1M	10
#घोषणा BOOK3E_PAGESZ_2M	11
#घोषणा BOOK3E_PAGESZ_4M	12
#घोषणा BOOK3E_PAGESZ_8M	13
#घोषणा BOOK3E_PAGESZ_16M	14
#घोषणा BOOK3E_PAGESZ_32M	15
#घोषणा BOOK3E_PAGESZ_64M	16
#घोषणा BOOK3E_PAGESZ_128M	17
#घोषणा BOOK3E_PAGESZ_256M	18
#घोषणा BOOK3E_PAGESZ_512M	19
#घोषणा BOOK3E_PAGESZ_1GB	20
#घोषणा BOOK3E_PAGESZ_2GB	21
#घोषणा BOOK3E_PAGESZ_4GB	22
#घोषणा BOOK3E_PAGESZ_8GB	23
#घोषणा BOOK3E_PAGESZ_16GB	24
#घोषणा BOOK3E_PAGESZ_32GB	25
#घोषणा BOOK3E_PAGESZ_64GB	26
#घोषणा BOOK3E_PAGESZ_128GB	27
#घोषणा BOOK3E_PAGESZ_256GB	28
#घोषणा BOOK3E_PAGESZ_512GB	29
#घोषणा BOOK3E_PAGESZ_1TB	30
#घोषणा BOOK3E_PAGESZ_2TB	31

/* MAS रेजिस्टरs bit definitions */

#घोषणा MAS0_TLBSEL_MASK	0x30000000
#घोषणा MAS0_TLBSEL_SHIFT	28
#घोषणा MAS0_TLBSEL(x)		(((x) << MAS0_TLBSEL_SHIFT) & MAS0_TLBSEL_MASK)
#घोषणा MAS0_GET_TLBSEL(mas0)	(((mas0) & MAS0_TLBSEL_MASK) >> \
			MAS0_TLBSEL_SHIFT)
#घोषणा MAS0_ESEL_MASK		0x0FFF0000
#घोषणा MAS0_ESEL_SHIFT		16
#घोषणा MAS0_ESEL(x)		(((x) << MAS0_ESEL_SHIFT) & MAS0_ESEL_MASK)
#घोषणा MAS0_NV(x)		((x) & 0x00000FFF)
#घोषणा MAS0_HES		0x00004000
#घोषणा MAS0_WQ_ALLWAYS		0x00000000
#घोषणा MAS0_WQ_COND		0x00001000
#घोषणा MAS0_WQ_CLR_RSRV       	0x00002000

#घोषणा MAS1_VALID		0x80000000
#घोषणा MAS1_IPROT		0x40000000
#घोषणा MAS1_TID(x)		(((x) << 16) & 0x3FFF0000)
#घोषणा MAS1_IND		0x00002000
#घोषणा MAS1_TS			0x00001000
#घोषणा MAS1_TSIZE_MASK		0x00000f80
#घोषणा MAS1_TSIZE_SHIFT	7
#घोषणा MAS1_TSIZE(x)		(((x) << MAS1_TSIZE_SHIFT) & MAS1_TSIZE_MASK)
#घोषणा MAS1_GET_TSIZE(mas1)	(((mas1) & MAS1_TSIZE_MASK) >> MAS1_TSIZE_SHIFT)

#घोषणा MAS2_EPN		(~0xFFFUL)
#घोषणा MAS2_X0			0x00000040
#घोषणा MAS2_X1			0x00000020
#घोषणा MAS2_W			0x00000010
#घोषणा MAS2_I			0x00000008
#घोषणा MAS2_M			0x00000004
#घोषणा MAS2_G			0x00000002
#घोषणा MAS2_E			0x00000001
#घोषणा MAS2_WIMGE_MASK		0x0000001f
#घोषणा MAS2_EPN_MASK(size)		(~0 << (size + 10))

#घोषणा MAS3_RPN		0xFFFFF000
#घोषणा MAS3_U0			0x00000200
#घोषणा MAS3_U1			0x00000100
#घोषणा MAS3_U2			0x00000080
#घोषणा MAS3_U3			0x00000040
#घोषणा MAS3_UX			0x00000020
#घोषणा MAS3_SX			0x00000010
#घोषणा MAS3_UW			0x00000008
#घोषणा MAS3_SW			0x00000004
#घोषणा MAS3_UR			0x00000002
#घोषणा MAS3_SR			0x00000001
#घोषणा MAS3_BAP_MASK		0x0000003f
#घोषणा MAS3_SPSIZE		0x0000003e
#घोषणा MAS3_SPSIZE_SHIFT	1

#घोषणा MAS4_TLBSEL_MASK	MAS0_TLBSEL_MASK
#घोषणा MAS4_TLBSELD(x) 	MAS0_TLBSEL(x)
#घोषणा MAS4_INDD		0x00008000	/* Default IND */
#घोषणा MAS4_TSIZED(x)		MAS1_TSIZE(x)
#घोषणा MAS4_X0D		0x00000040
#घोषणा MAS4_X1D		0x00000020
#घोषणा MAS4_WD			0x00000010
#घोषणा MAS4_ID			0x00000008
#घोषणा MAS4_MD			0x00000004
#घोषणा MAS4_GD			0x00000002
#घोषणा MAS4_ED			0x00000001
#घोषणा MAS4_WIMGED_MASK	0x0000001f	/* Default WIMGE */
#घोषणा MAS4_WIMGED_SHIFT	0
#घोषणा MAS4_VLED		MAS4_X1D	/* Default VLE */
#घोषणा MAS4_ACMD		0x000000c0	/* Default ACM */
#घोषणा MAS4_ACMD_SHIFT		6
#घोषणा MAS4_TSIZED_MASK	0x00000f80	/* Default TSIZE */
#घोषणा MAS4_TSIZED_SHIFT	7

#घोषणा MAS5_SGS		0x80000000

#घोषणा MAS6_SPID0		0x3FFF0000
#घोषणा MAS6_SPID1		0x00007FFE
#घोषणा MAS6_ISIZE(x)		MAS1_TSIZE(x)
#घोषणा MAS6_SAS		0x00000001
#घोषणा MAS6_SPID		MAS6_SPID0
#घोषणा MAS6_SIND 		0x00000002	/* Indirect page */
#घोषणा MAS6_SIND_SHIFT		1
#घोषणा MAS6_SPID_MASK		0x3fff0000
#घोषणा MAS6_SPID_SHIFT		16
#घोषणा MAS6_ISIZE_MASK		0x00000f80
#घोषणा MAS6_ISIZE_SHIFT	7

#घोषणा MAS7_RPN		0xFFFFFFFF

#घोषणा MAS8_TGS		0x80000000 /* Guest space */
#घोषणा MAS8_VF			0x40000000 /* Virtualization Fault */
#घोषणा MAS8_TLPID		0x000000ff

/* Bit definitions क्रम MMUCFG */
#घोषणा MMUCFG_MAVN	0x00000003	/* MMU Architecture Version Number */
#घोषणा MMUCFG_MAVN_V1	0x00000000	/* v1.0 */
#घोषणा MMUCFG_MAVN_V2	0x00000001	/* v2.0 */
#घोषणा MMUCFG_NTLBS	0x0000000c	/* Number of TLBs */
#घोषणा MMUCFG_PIDSIZE	0x000007c0	/* PID Reg Size */
#घोषणा MMUCFG_TWC	0x00008000	/* TLB Write Conditional (v2.0) */
#घोषणा MMUCFG_LRAT	0x00010000	/* LRAT Supported (v2.0) */
#घोषणा MMUCFG_RASIZE	0x00fe0000	/* Real Addr Size */
#घोषणा MMUCFG_LPIDSIZE	0x0f000000	/* LPID Reg Size */

/* Bit definitions क्रम MMUCSR0 */
#घोषणा MMUCSR0_TLB1FI	0x00000002	/* TLB1 Flash invalidate */
#घोषणा MMUCSR0_TLB0FI	0x00000004	/* TLB0 Flash invalidate */
#घोषणा MMUCSR0_TLB2FI	0x00000040	/* TLB2 Flash invalidate */
#घोषणा MMUCSR0_TLB3FI	0x00000020	/* TLB3 Flash invalidate */
#घोषणा MMUCSR0_TLBFI	(MMUCSR0_TLB0FI | MMUCSR0_TLB1FI | \
			 MMUCSR0_TLB2FI | MMUCSR0_TLB3FI)
#घोषणा MMUCSR0_TLB0PS	0x00000780	/* TLB0 Page Size */
#घोषणा MMUCSR0_TLB1PS	0x00007800	/* TLB1 Page Size */
#घोषणा MMUCSR0_TLB2PS	0x00078000	/* TLB2 Page Size */
#घोषणा MMUCSR0_TLB3PS	0x00780000	/* TLB3 Page Size */

/* MMUCFG bits */
#घोषणा MMUCFG_MAVN_NASK	0x00000003
#घोषणा MMUCFG_MAVN_V1_0	0x00000000
#घोषणा MMUCFG_MAVN_V2_0	0x00000001
#घोषणा MMUCFG_NTLB_MASK	0x0000000c
#घोषणा MMUCFG_NTLB_SHIFT	2
#घोषणा MMUCFG_PIDSIZE_MASK	0x000007c0
#घोषणा MMUCFG_PIDSIZE_SHIFT	6
#घोषणा MMUCFG_TWC		0x00008000
#घोषणा MMUCFG_LRAT		0x00010000
#घोषणा MMUCFG_RASIZE_MASK	0x00fe0000
#घोषणा MMUCFG_RASIZE_SHIFT	17
#घोषणा MMUCFG_LPIDSIZE_MASK	0x0f000000
#घोषणा MMUCFG_LPIDSIZE_SHIFT	24

/* TLBnCFG encoding */
#घोषणा TLBnCFG_N_ENTRY		0x00000fff	/* number of entries */
#घोषणा TLBnCFG_HES		0x00002000	/* HW select supported */
#घोषणा TLBnCFG_IPROT		0x00008000	/* IPROT supported */
#घोषणा TLBnCFG_GTWE		0x00010000	/* Guest can ग_लिखो */
#घोषणा TLBnCFG_IND		0x00020000	/* IND entries supported */
#घोषणा TLBnCFG_PT		0x00040000	/* Can load from page table */
#घोषणा TLBnCFG_MINSIZE		0x00f00000	/* Minimum Page Size (v1.0) */
#घोषणा TLBnCFG_MINSIZE_SHIFT	20
#घोषणा TLBnCFG_MAXSIZE		0x000f0000	/* Maximum Page Size (v1.0) */
#घोषणा TLBnCFG_MAXSIZE_SHIFT	16
#घोषणा TLBnCFG_ASSOC		0xff000000	/* Associativity */
#घोषणा TLBnCFG_ASSOC_SHIFT	24

/* TLBnPS encoding */
#घोषणा TLBnPS_4K		0x00000004
#घोषणा TLBnPS_8K		0x00000008
#घोषणा TLBnPS_16K		0x00000010
#घोषणा TLBnPS_32K		0x00000020
#घोषणा TLBnPS_64K		0x00000040
#घोषणा TLBnPS_128K		0x00000080
#घोषणा TLBnPS_256K		0x00000100
#घोषणा TLBnPS_512K		0x00000200
#घोषणा TLBnPS_1M 		0x00000400
#घोषणा TLBnPS_2M 		0x00000800
#घोषणा TLBnPS_4M 		0x00001000
#घोषणा TLBnPS_8M 		0x00002000
#घोषणा TLBnPS_16M		0x00004000
#घोषणा TLBnPS_32M		0x00008000
#घोषणा TLBnPS_64M		0x00010000
#घोषणा TLBnPS_128M		0x00020000
#घोषणा TLBnPS_256M		0x00040000
#घोषणा TLBnPS_512M		0x00080000
#घोषणा TLBnPS_1G		0x00100000
#घोषणा TLBnPS_2G		0x00200000
#घोषणा TLBnPS_4G		0x00400000
#घोषणा TLBnPS_8G		0x00800000
#घोषणा TLBnPS_16G		0x01000000
#घोषणा TLBnPS_32G		0x02000000
#घोषणा TLBnPS_64G		0x04000000
#घोषणा TLBnPS_128G		0x08000000
#घोषणा TLBnPS_256G		0x10000000

/* tlbilx action encoding */
#घोषणा TLBILX_T_ALL			0
#घोषणा TLBILX_T_TID			1
#घोषणा TLBILX_T_FULLMATCH		3
#घोषणा TLBILX_T_CLASS0			4
#घोषणा TLBILX_T_CLASS1			5
#घोषणा TLBILX_T_CLASS2			6
#घोषणा TLBILX_T_CLASS3			7

/*
 * The mapping only needs to be cache-coherent on SMP, except on
 * Freescale e500mc derivatives where it's also needed क्रम coherent DMA.
 */
#अगर defined(CONFIG_SMP) || defined(CONFIG_PPC_E500MC)
#घोषणा MAS2_M_IF_NEEDED	MAS2_M
#अन्यथा
#घोषणा MAS2_M_IF_NEEDED	0
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/bug.h>

बाह्य अचिन्हित पूर्णांक tlbcam_index;

प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक	id;
	अचिन्हित पूर्णांक	active;
	व्योम __user	*vdso;
पूर्ण mm_context_t;

/* Page size definitions, common between 32 and 64-bit
 *
 *    shअगरt : is the "PAGE_SHIFT" value क्रम that page size
 *    penc  : is the pte encoding mask
 *
 */
काष्ठा mmu_psize_def
अणु
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

/* The page sizes use the same names as 64-bit hash but are
 * स्थिरants
 */
#अगर defined(CONFIG_PPC_4K_PAGES)
#घोषणा mmu_भव_psize	MMU_PAGE_4K
#अन्यथा
#त्रुटि Unsupported page size
#पूर्ण_अगर

बाह्य पूर्णांक mmu_linear_psize;
बाह्य पूर्णांक mmu_vmemmap_psize;

काष्ठा tlb_core_data अणु
	/*
	 * Per-core spinlock क्रम e6500 TLB handlers (no tlbsrx.)
	 * Must be the first काष्ठा element.
	 */
	u8 lock;

	/* For software way selection, as on Freescale TLB1 */
	u8 esel_next, esel_max, esel_first;
पूर्ण;

#अगर_घोषित CONFIG_PPC64
बाह्य अचिन्हित दीर्घ linear_map_top;
बाह्य पूर्णांक book3e_htw_mode;

#घोषणा PPC_HTW_NONE	0
#घोषणा PPC_HTW_IBM	1
#घोषणा PPC_HTW_E6500	2

/*
 * 64-bit booke platक्रमms करोn't load the tlb in the tlb miss handler code.
 * HUGETLB_NEED_PRELOAD handles this - it causes huge_ptep_set_access_flags to
 * वापस 1, indicating that the tlb requires preloading.
 */
#घोषणा HUGETLB_NEED_PRELOAD

#घोषणा mmu_cleanup_all शून्य

#घोषणा MAX_PHYSMEM_BITS        44

#पूर्ण_अगर

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_POWERPC_MMU_BOOK3E_H_ */
