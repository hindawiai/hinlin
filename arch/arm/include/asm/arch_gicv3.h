<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/include/यंत्र/arch_gicv3.h
 *
 * Copyright (C) 2015 ARM Ltd.
 */
#अगर_अघोषित __ASM_ARCH_GICV3_H
#घोषणा __ASM_ARCH_GICV3_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/पन.स>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cp15.h>

#घोषणा ICC_EOIR1			__ACCESS_CP15(c12, 0, c12, 1)
#घोषणा ICC_सूची				__ACCESS_CP15(c12, 0, c11, 1)
#घोषणा ICC_IAR1			__ACCESS_CP15(c12, 0, c12, 0)
#घोषणा ICC_SGI1R			__ACCESS_CP15_64(0, c12)
#घोषणा ICC_PMR				__ACCESS_CP15(c4, 0, c6, 0)
#घोषणा ICC_CTLR			__ACCESS_CP15(c12, 0, c12, 4)
#घोषणा ICC_SRE				__ACCESS_CP15(c12, 0, c12, 5)
#घोषणा ICC_IGRPEN1			__ACCESS_CP15(c12, 0, c12, 7)
#घोषणा ICC_BPR1			__ACCESS_CP15(c12, 0, c12, 3)
#घोषणा ICC_RPR				__ACCESS_CP15(c12, 0, c11, 3)

#घोषणा __ICC_AP0Rx(x)			__ACCESS_CP15(c12, 0, c8, 4 | x)
#घोषणा ICC_AP0R0			__ICC_AP0Rx(0)
#घोषणा ICC_AP0R1			__ICC_AP0Rx(1)
#घोषणा ICC_AP0R2			__ICC_AP0Rx(2)
#घोषणा ICC_AP0R3			__ICC_AP0Rx(3)

#घोषणा __ICC_AP1Rx(x)			__ACCESS_CP15(c12, 0, c9, x)
#घोषणा ICC_AP1R0			__ICC_AP1Rx(0)
#घोषणा ICC_AP1R1			__ICC_AP1Rx(1)
#घोषणा ICC_AP1R2			__ICC_AP1Rx(2)
#घोषणा ICC_AP1R3			__ICC_AP1Rx(3)

#घोषणा CPUIF_MAP(a32, a64)			\
अटल अंतरभूत व्योम ग_लिखो_ ## a64(u32 val)	\
अणु						\
	ग_लिखो_sysreg(val, a32);			\
पूर्ण						\
अटल अंतरभूत u32 पढ़ो_ ## a64(व्योम)		\
अणु						\
	वापस पढ़ो_sysreg(a32); 		\
पूर्ण						\

CPUIF_MAP(ICC_PMR, ICC_PMR_EL1)
CPUIF_MAP(ICC_AP0R0, ICC_AP0R0_EL1)
CPUIF_MAP(ICC_AP0R1, ICC_AP0R1_EL1)
CPUIF_MAP(ICC_AP0R2, ICC_AP0R2_EL1)
CPUIF_MAP(ICC_AP0R3, ICC_AP0R3_EL1)
CPUIF_MAP(ICC_AP1R0, ICC_AP1R0_EL1)
CPUIF_MAP(ICC_AP1R1, ICC_AP1R1_EL1)
CPUIF_MAP(ICC_AP1R2, ICC_AP1R2_EL1)
CPUIF_MAP(ICC_AP1R3, ICC_AP1R3_EL1)

#घोषणा पढ़ो_gicreg(r)                 पढ़ो_##r()
#घोषणा ग_लिखो_gicreg(v, r)             ग_लिखो_##r(v)

/* Low-level accessors */

अटल अंतरभूत व्योम gic_ग_लिखो_eoir(u32 irq)
अणु
	ग_लिखो_sysreg(irq, ICC_EOIR1);
	isb();
पूर्ण

अटल अंतरभूत व्योम gic_ग_लिखो_dir(u32 val)
अणु
	ग_लिखो_sysreg(val, ICC_सूची);
	isb();
पूर्ण

अटल अंतरभूत u32 gic_पढ़ो_iar(व्योम)
अणु
	u32 irqstat = पढ़ो_sysreg(ICC_IAR1);

	dsb(sy);

	वापस irqstat;
पूर्ण

अटल अंतरभूत व्योम gic_ग_लिखो_ctlr(u32 val)
अणु
	ग_लिखो_sysreg(val, ICC_CTLR);
	isb();
पूर्ण

अटल अंतरभूत u32 gic_पढ़ो_ctlr(व्योम)
अणु
	वापस पढ़ो_sysreg(ICC_CTLR);
पूर्ण

अटल अंतरभूत व्योम gic_ग_लिखो_grpen1(u32 val)
अणु
	ग_लिखो_sysreg(val, ICC_IGRPEN1);
	isb();
पूर्ण

अटल अंतरभूत व्योम gic_ग_लिखो_sgi1r(u64 val)
अणु
	ग_लिखो_sysreg(val, ICC_SGI1R);
पूर्ण

अटल अंतरभूत u32 gic_पढ़ो_sre(व्योम)
अणु
	वापस पढ़ो_sysreg(ICC_SRE);
पूर्ण

अटल अंतरभूत व्योम gic_ग_लिखो_sre(u32 val)
अणु
	ग_लिखो_sysreg(val, ICC_SRE);
	isb();
पूर्ण

अटल अंतरभूत व्योम gic_ग_लिखो_bpr1(u32 val)
अणु
	ग_लिखो_sysreg(val, ICC_BPR1);
पूर्ण

अटल अंतरभूत u32 gic_पढ़ो_pmr(व्योम)
अणु
	वापस पढ़ो_sysreg(ICC_PMR);
पूर्ण

अटल अंतरभूत व्योम gic_ग_लिखो_pmr(u32 val)
अणु
	ग_लिखो_sysreg(val, ICC_PMR);
पूर्ण

अटल अंतरभूत u32 gic_पढ़ो_rpr(व्योम)
अणु
	वापस पढ़ो_sysreg(ICC_RPR);
पूर्ण

/*
 * Even in 32bit प्रणालीs that use LPAE, there is no guarantee that the I/O
 * पूर्णांकerface provides true 64bit atomic accesses, so using strd/ldrd करोesn't
 * make much sense.
 * Moreover, 64bit I/O emulation is extremely dअगरficult to implement on
 * AArch32, since the syndrome रेजिस्टर करोesn't provide any inक्रमmation क्रम
 * them.
 * Consequently, the following IO helpers use 32bit accesses.
 */
अटल अंतरभूत व्योम __gic_ग_लिखोq_nonatomic(u64 val, अस्थिर व्योम __iomem *addr)
अणु
	ग_लिखोl_relaxed((u32)val, addr);
	ग_लिखोl_relaxed((u32)(val >> 32), addr + 4);
पूर्ण

अटल अंतरभूत u64 __gic_पढ़ोq_nonatomic(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u64 val;

	val = पढ़ोl_relaxed(addr);
	val |= (u64)पढ़ोl_relaxed(addr + 4) << 32;
	वापस val;
पूर्ण

#घोषणा gic_flush_dcache_to_poc(a,l)    __cpuc_flush_dcache_area((a), (l))

/*
 *  GICD_IROUTERn, contain the affinity values associated to each पूर्णांकerrupt.
 *  The upper-word (aff3) will always be 0, so there is no need क्रम a lock.
 */
#घोषणा gic_ग_लिखो_irouter(v, c)		__gic_ग_लिखोq_nonatomic(v, c)

/*
 * GICR_TYPER is an ID रेजिस्टर and करोesn't need atomicity.
 */
#घोषणा gic_पढ़ो_typer(c)		__gic_पढ़ोq_nonatomic(c)

/*
 * GITS_BASER - hi and lo bits may be accessed independently.
 */
#घोषणा gits_पढ़ो_baser(c)		__gic_पढ़ोq_nonatomic(c)
#घोषणा gits_ग_लिखो_baser(v, c)		__gic_ग_लिखोq_nonatomic(v, c)

/*
 * GICR_PENDBASER and GICR_PROPBASE are changed with LPIs disabled, so they
 * won't be being used during any updates and can be changed non-atomically
 */
#घोषणा gicr_पढ़ो_propbaser(c)		__gic_पढ़ोq_nonatomic(c)
#घोषणा gicr_ग_लिखो_propbaser(v, c)	__gic_ग_लिखोq_nonatomic(v, c)
#घोषणा gicr_पढ़ो_pendbaser(c)		__gic_पढ़ोq_nonatomic(c)
#घोषणा gicr_ग_लिखो_pendbaser(v, c)	__gic_ग_लिखोq_nonatomic(v, c)

/*
 * GICR_xLPIR - only the lower bits are signअगरicant
 */
#घोषणा gic_पढ़ो_lpir(c)		पढ़ोl_relaxed(c)
#घोषणा gic_ग_लिखो_lpir(v, c)		ग_लिखोl_relaxed(lower_32_bits(v), c)

/*
 * GITS_TYPER is an ID रेजिस्टर and करोesn't need atomicity.
 */
#घोषणा gits_पढ़ो_typer(c)		__gic_पढ़ोq_nonatomic(c)

/*
 * GITS_CBASER - hi and lo bits may be accessed independently.
 */
#घोषणा gits_पढ़ो_cbaser(c)		__gic_पढ़ोq_nonatomic(c)
#घोषणा gits_ग_लिखो_cbaser(v, c)		__gic_ग_लिखोq_nonatomic(v, c)

/*
 * GITS_CWRITER - hi and lo bits may be accessed independently.
 */
#घोषणा gits_ग_लिखो_cग_लिखोr(v, c)	__gic_ग_लिखोq_nonatomic(v, c)

/*
 * GICR_VPROPBASER - hi and lo bits may be accessed independently.
 */
#घोषणा gicr_पढ़ो_vpropbaser(c)		__gic_पढ़ोq_nonatomic(c)
#घोषणा gicr_ग_लिखो_vpropbaser(v, c)	__gic_ग_लिखोq_nonatomic(v, c)

/*
 * GICR_VPENDBASER - the Valid bit must be cleared beक्रमe changing
 * anything अन्यथा.
 */
अटल अंतरभूत व्योम gicr_ग_लिखो_vpendbaser(u64 val, व्योम __iomem *addr)
अणु
	u32 पंचांगp;

	पंचांगp = पढ़ोl_relaxed(addr + 4);
	अगर (पंचांगp & (GICR_VPENDBASER_Valid >> 32)) अणु
		पंचांगp &= ~(GICR_VPENDBASER_Valid >> 32);
		ग_लिखोl_relaxed(पंचांगp, addr + 4);
	पूर्ण

	/*
	 * Use the fact that __gic_ग_लिखोq_nonatomic ग_लिखोs the second
	 * half of the 64bit quantity after the first.
	 */
	__gic_ग_लिखोq_nonatomic(val, addr);
पूर्ण

#घोषणा gicr_पढ़ो_vpendbaser(c)		__gic_पढ़ोq_nonatomic(c)

अटल अंतरभूत bool gic_prio_masking_enabled(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम gic_pmr_mask_irqs(व्योम)
अणु
	/* Should not get called. */
	WARN_ON_ONCE(true);
पूर्ण

अटल अंतरभूत व्योम gic_arch_enable_irqs(व्योम)
अणु
	/* Should not get called. */
	WARN_ON_ONCE(true);
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* !__ASM_ARCH_GICV3_H */
