<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_MMU_40X_H_
#घोषणा _ASM_POWERPC_MMU_40X_H_

/*
 * PPC40x support
 */

#घोषणा PPC40X_TLB_SIZE 64

/*
 * TLB entries are defined by a "high" tag portion and a "low" data
 * portion.  On all architectures, the data portion is 32-bits.
 *
 * TLB entries are managed entirely under software control by पढ़ोing,
 * writing, and searchoing using the 4xx-specअगरic tlbre, tlbwr, and tlbsx
 * inकाष्ठाions.
 */

#घोषणा	TLB_LO          1
#घोषणा	TLB_HI          0

#घोषणा	TLB_DATA        TLB_LO
#घोषणा	TLB_TAG         TLB_HI

/* Tag portion */

#घोषणा TLB_EPN_MASK    0xFFFFFC00      /* Effective Page Number */
#घोषणा TLB_PAGESZ_MASK 0x00000380
#घोषणा TLB_PAGESZ(x)   (((x) & 0x7) << 7)
#घोषणा   PAGESZ_1K		0
#घोषणा   PAGESZ_4K             1
#घोषणा   PAGESZ_16K            2
#घोषणा   PAGESZ_64K            3
#घोषणा   PAGESZ_256K           4
#घोषणा   PAGESZ_1M             5
#घोषणा   PAGESZ_4M             6
#घोषणा   PAGESZ_16M            7
#घोषणा TLB_VALID       0x00000040      /* Entry is valid */

/* Data portion */

#घोषणा TLB_RPN_MASK    0xFFFFFC00      /* Real Page Number */
#घोषणा TLB_PERM_MASK   0x00000300
#घोषणा TLB_EX          0x00000200      /* Inकाष्ठाion execution allowed */
#घोषणा TLB_WR          0x00000100      /* Writes permitted */
#घोषणा TLB_ZSEL_MASK   0x000000F0
#घोषणा TLB_ZSEL(x)     (((x) & 0xF) << 4)
#घोषणा TLB_ATTR_MASK   0x0000000F
#घोषणा TLB_W           0x00000008      /* Caching is ग_लिखो-through */
#घोषणा TLB_I           0x00000004      /* Caching is inhibited */
#घोषणा TLB_M           0x00000002      /* Memory is coherent */
#घोषणा TLB_G           0x00000001      /* Memory is guarded from prefetch */

#अगर_अघोषित __ASSEMBLY__

प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक	id;
	अचिन्हित पूर्णांक	active;
	व्योम __user	*vdso;
पूर्ण mm_context_t;

#पूर्ण_अगर /* !__ASSEMBLY__ */

#घोषणा mmu_भव_psize	MMU_PAGE_4K
#घोषणा mmu_linear_psize	MMU_PAGE_256M

#पूर्ण_अगर /* _ASM_POWERPC_MMU_40X_H_ */
