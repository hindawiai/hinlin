<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_MMU_44X_H_
#घोषणा _ASM_POWERPC_MMU_44X_H_
/*
 * PPC440 support
 */

#समावेश <यंत्र/यंत्र-स्थिर.h>

#घोषणा PPC44x_MMUCR_TID	0x000000ff
#घोषणा PPC44x_MMUCR_STS	0x00010000

#घोषणा	PPC44x_TLB_PAGEID	0
#घोषणा	PPC44x_TLB_XLAT		1
#घोषणा	PPC44x_TLB_ATTRIB	2

/* Page identअगरication fields */
#घोषणा PPC44x_TLB_EPN_MASK	0xfffffc00      /* Effective Page Number */
#घोषणा	PPC44x_TLB_VALID	0x00000200      /* Valid flag */
#घोषणा PPC44x_TLB_TS		0x00000100	/* Translation address space */
#घोषणा PPC44x_TLB_1K		0x00000000	/* Page sizes */
#घोषणा PPC44x_TLB_4K		0x00000010
#घोषणा PPC44x_TLB_16K		0x00000020
#घोषणा PPC44x_TLB_64K		0x00000030
#घोषणा PPC44x_TLB_256K		0x00000040
#घोषणा PPC44x_TLB_1M		0x00000050
#घोषणा PPC44x_TLB_16M		0x00000070
#घोषणा	PPC44x_TLB_256M		0x00000090

/* Translation fields */
#घोषणा PPC44x_TLB_RPN_MASK	0xfffffc00      /* Real Page Number */
#घोषणा	PPC44x_TLB_ERPN_MASK	0x0000000f

/* Storage attribute and access control fields */
#घोषणा PPC44x_TLB_ATTR_MASK	0x0000ff80
#घोषणा PPC44x_TLB_U0		0x00008000      /* User 0 */
#घोषणा PPC44x_TLB_U1		0x00004000      /* User 1 */
#घोषणा PPC44x_TLB_U2		0x00002000      /* User 2 */
#घोषणा PPC44x_TLB_U3		0x00001000      /* User 3 */
#घोषणा PPC44x_TLB_W		0x00000800      /* Caching is ग_लिखो-through */
#घोषणा PPC44x_TLB_I		0x00000400      /* Caching is inhibited */
#घोषणा PPC44x_TLB_M		0x00000200      /* Memory is coherent */
#घोषणा PPC44x_TLB_G		0x00000100      /* Memory is guarded */
#घोषणा PPC44x_TLB_E		0x00000080      /* Memory is little endian */

#घोषणा PPC44x_TLB_PERM_MASK	0x0000003f
#घोषणा PPC44x_TLB_UX		0x00000020      /* User execution */
#घोषणा PPC44x_TLB_UW		0x00000010      /* User ग_लिखो */
#घोषणा PPC44x_TLB_UR		0x00000008      /* User पढ़ो */
#घोषणा PPC44x_TLB_SX		0x00000004      /* Super execution */
#घोषणा PPC44x_TLB_SW		0x00000002      /* Super ग_लिखो */
#घोषणा PPC44x_TLB_SR		0x00000001      /* Super पढ़ो */

/* Number of TLB entries */
#घोषणा PPC44x_TLB_SIZE		64

/* 47x bits */
#घोषणा PPC47x_MMUCR_TID	0x0000ffff
#घोषणा PPC47x_MMUCR_STS	0x00010000

/* Page identअगरication fields */
#घोषणा PPC47x_TLB0_EPN_MASK	0xfffff000      /* Effective Page Number */
#घोषणा PPC47x_TLB0_VALID	0x00000800      /* Valid flag */
#घोषणा PPC47x_TLB0_TS		0x00000400	/* Translation address space */
#घोषणा PPC47x_TLB0_4K		0x00000000
#घोषणा PPC47x_TLB0_16K		0x00000010
#घोषणा PPC47x_TLB0_64K		0x00000030
#घोषणा PPC47x_TLB0_1M		0x00000070
#घोषणा PPC47x_TLB0_16M		0x000000f0
#घोषणा PPC47x_TLB0_256M	0x000001f0
#घोषणा PPC47x_TLB0_1G		0x000003f0
#घोषणा PPC47x_TLB0_BOLTED_R	0x00000008	/* tlbre only */

/* Translation fields */
#घोषणा PPC47x_TLB1_RPN_MASK	0xfffff000      /* Real Page Number */
#घोषणा PPC47x_TLB1_ERPN_MASK	0x000003ff

/* Storage attribute and access control fields */
#घोषणा PPC47x_TLB2_ATTR_MASK	0x0003ff80
#घोषणा PPC47x_TLB2_IL1I	0x00020000      /* Memory is guarded */
#घोषणा PPC47x_TLB2_IL1D	0x00010000      /* Memory is guarded */
#घोषणा PPC47x_TLB2_U0		0x00008000      /* User 0 */
#घोषणा PPC47x_TLB2_U1		0x00004000      /* User 1 */
#घोषणा PPC47x_TLB2_U2		0x00002000      /* User 2 */
#घोषणा PPC47x_TLB2_U3		0x00001000      /* User 3 */
#घोषणा PPC47x_TLB2_W		0x00000800      /* Caching is ग_लिखो-through */
#घोषणा PPC47x_TLB2_I		0x00000400      /* Caching is inhibited */
#घोषणा PPC47x_TLB2_M		0x00000200      /* Memory is coherent */
#घोषणा PPC47x_TLB2_G		0x00000100      /* Memory is guarded */
#घोषणा PPC47x_TLB2_E		0x00000080      /* Memory is little endian */
#घोषणा PPC47x_TLB2_PERM_MASK	0x0000003f
#घोषणा PPC47x_TLB2_UX		0x00000020      /* User execution */
#घोषणा PPC47x_TLB2_UW		0x00000010      /* User ग_लिखो */
#घोषणा PPC47x_TLB2_UR		0x00000008      /* User पढ़ो */
#घोषणा PPC47x_TLB2_SX		0x00000004      /* Super execution */
#घोषणा PPC47x_TLB2_SW		0x00000002      /* Super ग_लिखो */
#घोषणा PPC47x_TLB2_SR		0x00000001      /* Super पढ़ो */
#घोषणा PPC47x_TLB2_U_RWX	(PPC47x_TLB2_UX|PPC47x_TLB2_UW|PPC47x_TLB2_UR)
#घोषणा PPC47x_TLB2_S_RWX	(PPC47x_TLB2_SX|PPC47x_TLB2_SW|PPC47x_TLB2_SR)
#घोषणा PPC47x_TLB2_S_RW	(PPC47x_TLB2_SW | PPC47x_TLB2_SR)
#घोषणा PPC47x_TLB2_IMG		(PPC47x_TLB2_I | PPC47x_TLB2_M | PPC47x_TLB2_G)

#अगर_अघोषित __ASSEMBLY__

बाह्य अचिन्हित पूर्णांक tlb_44x_hwater;
बाह्य अचिन्हित पूर्णांक tlb_44x_index;

प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक	id;
	अचिन्हित पूर्णांक	active;
	व्योम __user	*vdso;
पूर्ण mm_context_t;

/* patch sites */
बाह्य s32 patch__tlb_44x_hwater_D, patch__tlb_44x_hwater_I;

#पूर्ण_अगर /* !__ASSEMBLY__ */

#अगर_अघोषित CONFIG_PPC_EARLY_DEBUG_44x
#घोषणा PPC44x_EARLY_TLBS	1
#अन्यथा
#घोषणा PPC44x_EARLY_TLBS	2
#घोषणा PPC44x_EARLY_DEBUG_VIRTADDR	(ASM_CONST(0xf0000000) \
	| (ASM_CONST(CONFIG_PPC_EARLY_DEBUG_44x_PHYSLOW) & 0xffff))
#पूर्ण_अगर

/* Size of the TLBs used क्रम pinning in lowmem */
#घोषणा PPC_PIN_SIZE	(1 << 28)	/* 256M */

#अगर defined(CONFIG_PPC_4K_PAGES)
#घोषणा PPC44x_TLBE_SIZE	PPC44x_TLB_4K
#घोषणा PPC47x_TLBE_SIZE	PPC47x_TLB0_4K
#घोषणा mmu_भव_psize	MMU_PAGE_4K
#या_अगर defined(CONFIG_PPC_16K_PAGES)
#घोषणा PPC44x_TLBE_SIZE	PPC44x_TLB_16K
#घोषणा PPC47x_TLBE_SIZE	PPC47x_TLB0_16K
#घोषणा mmu_भव_psize	MMU_PAGE_16K
#या_अगर defined(CONFIG_PPC_64K_PAGES)
#घोषणा PPC44x_TLBE_SIZE	PPC44x_TLB_64K
#घोषणा PPC47x_TLBE_SIZE	PPC47x_TLB0_64K
#घोषणा mmu_भव_psize	MMU_PAGE_64K
#या_अगर defined(CONFIG_PPC_256K_PAGES)
#घोषणा PPC44x_TLBE_SIZE	PPC44x_TLB_256K
#घोषणा mmu_भव_psize	MMU_PAGE_256K
#अन्यथा
#त्रुटि "Unsupported PAGE_SIZE"
#पूर्ण_अगर

#घोषणा mmu_linear_psize	MMU_PAGE_256M

#घोषणा PPC44x_PGD_OFF_SHIFT	(32 - PGसूची_SHIFT + PGD_T_LOG2)
#घोषणा PPC44x_PGD_OFF_MASK_BIT	(PGसूची_SHIFT - PGD_T_LOG2)
#घोषणा PPC44x_PTE_ADD_SHIFT	(32 - PGसूची_SHIFT + PTE_SHIFT + PTE_T_LOG2)
#घोषणा PPC44x_PTE_ADD_MASK_BIT	(32 - PTE_T_LOG2 - PTE_SHIFT)

#पूर्ण_अगर /* _ASM_POWERPC_MMU_44X_H_ */
