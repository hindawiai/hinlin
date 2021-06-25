<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm64/include/यंत्र/arch_gicv3.h
 *
 * Copyright (C) 2015 ARM Ltd.
 */
#अगर_अघोषित __ASM_ARCH_GICV3_H
#घोषणा __ASM_ARCH_GICV3_H

#समावेश <यंत्र/sysreg.h>

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/irqchip/arm-gic-common.h>
#समावेश <linux/stringअगरy.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/cacheflush.h>

#घोषणा पढ़ो_gicreg(r)			पढ़ो_sysreg_s(SYS_ ## r)
#घोषणा ग_लिखो_gicreg(v, r)		ग_लिखो_sysreg_s(v, SYS_ ## r)

/*
 * Low-level accessors
 *
 * These प्रणाली रेजिस्टरs are 32 bits, but we make sure that the compiler
 * sets the GP रेजिस्टर's most signअगरicant bits to 0 with an explicit cast.
 */

अटल अंतरभूत व्योम gic_ग_लिखो_eoir(u32 irq)
अणु
	ग_लिखो_sysreg_s(irq, SYS_ICC_EOIR1_EL1);
	isb();
पूर्ण

अटल __always_अंतरभूत व्योम gic_ग_लिखो_dir(u32 irq)
अणु
	ग_लिखो_sysreg_s(irq, SYS_ICC_सूची_EL1);
	isb();
पूर्ण

अटल अंतरभूत u64 gic_पढ़ो_iar_common(व्योम)
अणु
	u64 irqstat;

	irqstat = पढ़ो_sysreg_s(SYS_ICC_IAR1_EL1);
	dsb(sy);
	वापस irqstat;
पूर्ण

/*
 * Cavium ThunderX erratum 23154
 *
 * The gicv3 of ThunderX requires a modअगरied version क्रम पढ़ोing the
 * IAR status to ensure data synchronization (access to icc_iar1_el1
 * is not sync'ed beक्रमe and after).
 */
अटल अंतरभूत u64 gic_पढ़ो_iar_cavium_thunderx(व्योम)
अणु
	u64 irqstat;

	nops(8);
	irqstat = पढ़ो_sysreg_s(SYS_ICC_IAR1_EL1);
	nops(4);
	mb();

	वापस irqstat;
पूर्ण

अटल अंतरभूत व्योम gic_ग_लिखो_ctlr(u32 val)
अणु
	ग_लिखो_sysreg_s(val, SYS_ICC_CTLR_EL1);
	isb();
पूर्ण

अटल अंतरभूत u32 gic_पढ़ो_ctlr(व्योम)
अणु
	वापस पढ़ो_sysreg_s(SYS_ICC_CTLR_EL1);
पूर्ण

अटल अंतरभूत व्योम gic_ग_लिखो_grpen1(u32 val)
अणु
	ग_लिखो_sysreg_s(val, SYS_ICC_IGRPEN1_EL1);
	isb();
पूर्ण

अटल अंतरभूत व्योम gic_ग_लिखो_sgi1r(u64 val)
अणु
	ग_लिखो_sysreg_s(val, SYS_ICC_SGI1R_EL1);
पूर्ण

अटल अंतरभूत u32 gic_पढ़ो_sre(व्योम)
अणु
	वापस पढ़ो_sysreg_s(SYS_ICC_SRE_EL1);
पूर्ण

अटल अंतरभूत व्योम gic_ग_लिखो_sre(u32 val)
अणु
	ग_लिखो_sysreg_s(val, SYS_ICC_SRE_EL1);
	isb();
पूर्ण

अटल अंतरभूत व्योम gic_ग_लिखो_bpr1(u32 val)
अणु
	ग_लिखो_sysreg_s(val, SYS_ICC_BPR1_EL1);
पूर्ण

अटल अंतरभूत u32 gic_पढ़ो_pmr(व्योम)
अणु
	वापस पढ़ो_sysreg_s(SYS_ICC_PMR_EL1);
पूर्ण

अटल __always_अंतरभूत व्योम gic_ग_लिखो_pmr(u32 val)
अणु
	ग_लिखो_sysreg_s(val, SYS_ICC_PMR_EL1);
पूर्ण

अटल अंतरभूत u32 gic_पढ़ो_rpr(व्योम)
अणु
	वापस पढ़ो_sysreg_s(SYS_ICC_RPR_EL1);
पूर्ण

#घोषणा gic_पढ़ो_typer(c)		पढ़ोq_relaxed(c)
#घोषणा gic_ग_लिखो_irouter(v, c)		ग_लिखोq_relaxed(v, c)
#घोषणा gic_पढ़ो_lpir(c)		पढ़ोq_relaxed(c)
#घोषणा gic_ग_लिखो_lpir(v, c)		ग_लिखोq_relaxed(v, c)

#घोषणा gic_flush_dcache_to_poc(a,l)	__flush_dcache_area((a), (l))

#घोषणा gits_पढ़ो_baser(c)		पढ़ोq_relaxed(c)
#घोषणा gits_ग_लिखो_baser(v, c)		ग_लिखोq_relaxed(v, c)

#घोषणा gits_पढ़ो_cbaser(c)		पढ़ोq_relaxed(c)
#घोषणा gits_ग_लिखो_cbaser(v, c)		ग_लिखोq_relaxed(v, c)

#घोषणा gits_ग_लिखो_cग_लिखोr(v, c)	ग_लिखोq_relaxed(v, c)

#घोषणा gicr_पढ़ो_propbaser(c)		पढ़ोq_relaxed(c)
#घोषणा gicr_ग_लिखो_propbaser(v, c)	ग_लिखोq_relaxed(v, c)

#घोषणा gicr_ग_लिखो_pendbaser(v, c)	ग_लिखोq_relaxed(v, c)
#घोषणा gicr_पढ़ो_pendbaser(c)		पढ़ोq_relaxed(c)

#घोषणा gicr_ग_लिखो_vpropbaser(v, c)	ग_लिखोq_relaxed(v, c)
#घोषणा gicr_पढ़ो_vpropbaser(c)		पढ़ोq_relaxed(c)

#घोषणा gicr_ग_लिखो_vpendbaser(v, c)	ग_लिखोq_relaxed(v, c)
#घोषणा gicr_पढ़ो_vpendbaser(c)		पढ़ोq_relaxed(c)

अटल अंतरभूत bool gic_prio_masking_enabled(व्योम)
अणु
	वापस प्रणाली_uses_irq_prio_masking();
पूर्ण

अटल अंतरभूत व्योम gic_pmr_mask_irqs(व्योम)
अणु
	BUILD_BUG_ON(GICD_INT_DEF_PRI < (__GIC_PRIO_IRQOFF |
					 GIC_PRIO_PSR_I_SET));
	BUILD_BUG_ON(GICD_INT_DEF_PRI >= GIC_PRIO_IRQON);
	/*
	 * Need to make sure IRQON allows IRQs when SCR_EL3.FIQ is cleared
	 * and non-secure PMR accesses are not subject to the shअगरts that
	 * are applied to IRQ priorities
	 */
	BUILD_BUG_ON((0x80 | (GICD_INT_DEF_PRI >> 1)) >= GIC_PRIO_IRQON);
	/*
	 * Same situation as above, but now we make sure that we can mask
	 * regular पूर्णांकerrupts.
	 */
	BUILD_BUG_ON((0x80 | (GICD_INT_DEF_PRI >> 1)) < (__GIC_PRIO_IRQOFF_NS |
							 GIC_PRIO_PSR_I_SET));
	gic_ग_लिखो_pmr(GIC_PRIO_IRQOFF);
पूर्ण

अटल अंतरभूत व्योम gic_arch_enable_irqs(व्योम)
अणु
	यंत्र अस्थिर ("msr daifclr, #3" : : : "memory");
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __ASM_ARCH_GICV3_H */
