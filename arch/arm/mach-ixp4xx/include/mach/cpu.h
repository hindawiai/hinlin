<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/mach-ixp4xx/include/mach/cpu.h
 *
 * IXP4XX cpu type detection
 *
 * Copyright (C) 2007 MontaVista Software, Inc.
 */

#अगर_अघोषित __ASM_ARCH_CPU_H__
#घोषणा __ASM_ARCH_CPU_H__

#समावेश <linux/पन.स>
#समावेश <यंत्र/cputype.h>

/* Processor id value in CP15 Register 0 */
#घोषणा IXP42X_PROCESSOR_ID_VALUE	0x690541c0 /* including unused 0x690541Ex */
#घोषणा IXP42X_PROCESSOR_ID_MASK	0xffffffc0

#घोषणा IXP43X_PROCESSOR_ID_VALUE	0x69054040
#घोषणा IXP43X_PROCESSOR_ID_MASK	0xfffffff0

#घोषणा IXP46X_PROCESSOR_ID_VALUE	0x69054200 /* including IXP455 */
#घोषणा IXP46X_PROCESSOR_ID_MASK	0xfffffff0

#घोषणा cpu_is_ixp42x_rev_a0() ((पढ़ो_cpuid_id() & (IXP42X_PROCESSOR_ID_MASK | 0xF)) == \
				IXP42X_PROCESSOR_ID_VALUE)
#घोषणा cpu_is_ixp42x()	((पढ़ो_cpuid_id() & IXP42X_PROCESSOR_ID_MASK) == \
			 IXP42X_PROCESSOR_ID_VALUE)
#घोषणा cpu_is_ixp43x()	((पढ़ो_cpuid_id() & IXP43X_PROCESSOR_ID_MASK) == \
			 IXP43X_PROCESSOR_ID_VALUE)
#घोषणा cpu_is_ixp46x()	((पढ़ो_cpuid_id() & IXP46X_PROCESSOR_ID_MASK) == \
			 IXP46X_PROCESSOR_ID_VALUE)

अटल अंतरभूत u32 ixp4xx_पढ़ो_feature_bits(व्योम)
अणु
	u32 val = ~__raw_पढ़ोl(IXP4XX_EXP_CFG2);

	अगर (cpu_is_ixp42x_rev_a0())
		वापस IXP42X_FEATURE_MASK & ~(IXP4XX_FEATURE_RCOMP |
					       IXP4XX_FEATURE_AES);
	अगर (cpu_is_ixp42x())
		वापस val & IXP42X_FEATURE_MASK;
	अगर (cpu_is_ixp43x())
		वापस val & IXP43X_FEATURE_MASK;
	वापस val & IXP46X_FEATURE_MASK;
पूर्ण

अटल अंतरभूत व्योम ixp4xx_ग_लिखो_feature_bits(u32 value)
अणु
	__raw_ग_लिखोl(~value, IXP4XX_EXP_CFG2);
पूर्ण

#पूर्ण_अगर  /* _ASM_ARCH_CPU_H */
