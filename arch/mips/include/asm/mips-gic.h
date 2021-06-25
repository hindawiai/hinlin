<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2017 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#अगर_अघोषित __MIPS_ASM_MIPS_CPS_H__
# error Please include यंत्र/mips-cps.h rather than यंत्र/mips-gic.h
#पूर्ण_अगर

#अगर_अघोषित __MIPS_ASM_MIPS_GIC_H__
#घोषणा __MIPS_ASM_MIPS_GIC_H__

#समावेश <linux/bitops.h>

/* The base address of the GIC रेजिस्टरs */
बाह्य व्योम __iomem *mips_gic_base;

/* Offsets from the GIC base address to various control blocks */
#घोषणा MIPS_GIC_SHARED_OFS	0x00000
#घोषणा MIPS_GIC_SHARED_SZ	0x08000
#घोषणा MIPS_GIC_LOCAL_OFS	0x08000
#घोषणा MIPS_GIC_LOCAL_SZ	0x04000
#घोषणा MIPS_GIC_REसूची_OFS	0x0c000
#घोषणा MIPS_GIC_REसूची_SZ	0x04000
#घोषणा MIPS_GIC_USER_OFS	0x10000
#घोषणा MIPS_GIC_USER_SZ	0x10000

/* For पढ़ो-only shared रेजिस्टरs */
#घोषणा GIC_ACCESSOR_RO(sz, off, name)					\
	CPS_ACCESSOR_RO(gic, sz, MIPS_GIC_SHARED_OFS + off, name)

/* For पढ़ो-ग_लिखो shared रेजिस्टरs */
#घोषणा GIC_ACCESSOR_RW(sz, off, name)					\
	CPS_ACCESSOR_RW(gic, sz, MIPS_GIC_SHARED_OFS + off, name)

/* For पढ़ो-only local रेजिस्टरs */
#घोषणा GIC_VX_ACCESSOR_RO(sz, off, name)				\
	CPS_ACCESSOR_RO(gic, sz, MIPS_GIC_LOCAL_OFS + off, vl_##name)	\
	CPS_ACCESSOR_RO(gic, sz, MIPS_GIC_REसूची_OFS + off, vo_##name)

/* For पढ़ो-ग_लिखो local रेजिस्टरs */
#घोषणा GIC_VX_ACCESSOR_RW(sz, off, name)				\
	CPS_ACCESSOR_RW(gic, sz, MIPS_GIC_LOCAL_OFS + off, vl_##name)	\
	CPS_ACCESSOR_RW(gic, sz, MIPS_GIC_REसूची_OFS + off, vo_##name)

/* For पढ़ो-only shared per-पूर्णांकerrupt रेजिस्टरs */
#घोषणा GIC_ACCESSOR_RO_INTR_REG(sz, off, stride, name)			\
अटल अंतरभूत व्योम __iomem *addr_gic_##name(अचिन्हित पूर्णांक पूर्णांकr)		\
अणु									\
	वापस mips_gic_base + (off) + (पूर्णांकr * (stride));		\
पूर्ण									\
									\
अटल अंतरभूत अचिन्हित पूर्णांक पढ़ो_gic_##name(अचिन्हित पूर्णांक पूर्णांकr)		\
अणु									\
	BUILD_BUG_ON(sz != 32);						\
	वापस __raw_पढ़ोl(addr_gic_##name(पूर्णांकr));			\
पूर्ण

/* For पढ़ो-ग_लिखो shared per-पूर्णांकerrupt रेजिस्टरs */
#घोषणा GIC_ACCESSOR_RW_INTR_REG(sz, off, stride, name)			\
	GIC_ACCESSOR_RO_INTR_REG(sz, off, stride, name)			\
									\
अटल अंतरभूत व्योम ग_लिखो_gic_##name(अचिन्हित पूर्णांक पूर्णांकr,			\
				    अचिन्हित पूर्णांक val)			\
अणु									\
	BUILD_BUG_ON(sz != 32);						\
	__raw_ग_लिखोl(val, addr_gic_##name(पूर्णांकr));			\
पूर्ण

/* For पढ़ो-only local per-पूर्णांकerrupt रेजिस्टरs */
#घोषणा GIC_VX_ACCESSOR_RO_INTR_REG(sz, off, stride, name)		\
	GIC_ACCESSOR_RO_INTR_REG(sz, MIPS_GIC_LOCAL_OFS + off,		\
				 stride, vl_##name)			\
	GIC_ACCESSOR_RO_INTR_REG(sz, MIPS_GIC_REसूची_OFS + off,		\
				 stride, vo_##name)

/* For पढ़ो-ग_लिखो local per-पूर्णांकerrupt रेजिस्टरs */
#घोषणा GIC_VX_ACCESSOR_RW_INTR_REG(sz, off, stride, name)		\
	GIC_ACCESSOR_RW_INTR_REG(sz, MIPS_GIC_LOCAL_OFS + off,		\
				 stride, vl_##name)			\
	GIC_ACCESSOR_RW_INTR_REG(sz, MIPS_GIC_REसूची_OFS + off,		\
				 stride, vo_##name)

/* For पढ़ो-only shared bit-per-पूर्णांकerrupt रेजिस्टरs */
#घोषणा GIC_ACCESSOR_RO_INTR_BIT(off, name)				\
अटल अंतरभूत व्योम __iomem *addr_gic_##name(व्योम)			\
अणु									\
	वापस mips_gic_base + (off);					\
पूर्ण									\
									\
अटल अंतरभूत अचिन्हित पूर्णांक पढ़ो_gic_##name(अचिन्हित पूर्णांक पूर्णांकr)		\
अणु									\
	व्योम __iomem *addr = addr_gic_##name();				\
	अचिन्हित पूर्णांक val;						\
									\
	अगर (mips_cm_is64) अणु						\
		addr += (पूर्णांकr / 64) * माप(uपूर्णांक64_t);			\
		val = __raw_पढ़ोq(addr) >> पूर्णांकr % 64;			\
	पूर्ण अन्यथा अणु							\
		addr += (पूर्णांकr / 32) * माप(uपूर्णांक32_t);			\
		val = __raw_पढ़ोl(addr) >> पूर्णांकr % 32;			\
	पूर्ण								\
									\
	वापस val & 0x1;						\
पूर्ण

/* For पढ़ो-ग_लिखो shared bit-per-पूर्णांकerrupt रेजिस्टरs */
#घोषणा GIC_ACCESSOR_RW_INTR_BIT(off, name)				\
	GIC_ACCESSOR_RO_INTR_BIT(off, name)				\
									\
अटल अंतरभूत व्योम ग_लिखो_gic_##name(अचिन्हित पूर्णांक पूर्णांकr)			\
अणु									\
	व्योम __iomem *addr = addr_gic_##name();				\
									\
	अगर (mips_cm_is64) अणु						\
		addr += (पूर्णांकr / 64) * माप(uपूर्णांक64_t);			\
		__raw_ग_लिखोq(BIT(पूर्णांकr % 64), addr);			\
	पूर्ण अन्यथा अणु							\
		addr += (पूर्णांकr / 32) * माप(uपूर्णांक32_t);			\
		__raw_ग_लिखोl(BIT(पूर्णांकr % 32), addr);			\
	पूर्ण								\
पूर्ण									\
									\
अटल अंतरभूत व्योम change_gic_##name(अचिन्हित पूर्णांक पूर्णांकr,			\
				     अचिन्हित पूर्णांक val)			\
अणु									\
	व्योम __iomem *addr = addr_gic_##name();				\
									\
	अगर (mips_cm_is64) अणु						\
		uपूर्णांक64_t _val;						\
									\
		addr += (पूर्णांकr / 64) * माप(uपूर्णांक64_t);			\
		_val = __raw_पढ़ोq(addr);				\
		_val &= ~BIT_ULL(पूर्णांकr % 64);				\
		_val |= (uपूर्णांक64_t)val << (पूर्णांकr % 64);			\
		__raw_ग_लिखोq(_val, addr);				\
	पूर्ण अन्यथा अणु							\
		uपूर्णांक32_t _val;						\
									\
		addr += (पूर्णांकr / 32) * माप(uपूर्णांक32_t);			\
		_val = __raw_पढ़ोl(addr);				\
		_val &= ~BIT(पूर्णांकr % 32);				\
		_val |= val << (पूर्णांकr % 32);				\
		__raw_ग_लिखोl(_val, addr);				\
	पूर्ण								\
पूर्ण

/* For पढ़ो-only local bit-per-पूर्णांकerrupt रेजिस्टरs */
#घोषणा GIC_VX_ACCESSOR_RO_INTR_BIT(sz, off, name)			\
	GIC_ACCESSOR_RO_INTR_BIT(sz, MIPS_GIC_LOCAL_OFS + off,		\
				 vl_##name)				\
	GIC_ACCESSOR_RO_INTR_BIT(sz, MIPS_GIC_REसूची_OFS + off,		\
				 vo_##name)

/* For पढ़ो-ग_लिखो local bit-per-पूर्णांकerrupt रेजिस्टरs */
#घोषणा GIC_VX_ACCESSOR_RW_INTR_BIT(sz, off, name)			\
	GIC_ACCESSOR_RW_INTR_BIT(sz, MIPS_GIC_LOCAL_OFS + off,		\
				 vl_##name)				\
	GIC_ACCESSOR_RW_INTR_BIT(sz, MIPS_GIC_REसूची_OFS + off,		\
				 vo_##name)

/* GIC_SH_CONFIG - Inक्रमmation about the GIC configuration */
GIC_ACCESSOR_RW(32, 0x000, config)
#घोषणा GIC_CONFIG_COUNTSTOP		BIT(28)
#घोषणा GIC_CONFIG_COUNTBITS		GENMASK(27, 24)
#घोषणा GIC_CONFIG_NUMINTERRUPTS	GENMASK(23, 16)
#घोषणा GIC_CONFIG_PVPS			GENMASK(6, 0)

/* GIC_SH_COUNTER - Shared global counter value */
GIC_ACCESSOR_RW(64, 0x010, counter)
GIC_ACCESSOR_RW(32, 0x010, counter_32l)
GIC_ACCESSOR_RW(32, 0x014, counter_32h)

/* GIC_SH_POL_* - Configures पूर्णांकerrupt polarity */
GIC_ACCESSOR_RW_INTR_BIT(0x100, pol)
#घोषणा GIC_POL_ACTIVE_LOW		0	/* when level triggered */
#घोषणा GIC_POL_ACTIVE_HIGH		1	/* when level triggered */
#घोषणा GIC_POL_FALLING_EDGE		0	/* when single-edge triggered */
#घोषणा GIC_POL_RISING_EDGE		1	/* when single-edge triggered */

/* GIC_SH_TRIG_* - Configures पूर्णांकerrupts to be edge or level triggered */
GIC_ACCESSOR_RW_INTR_BIT(0x180, trig)
#घोषणा GIC_TRIG_LEVEL			0
#घोषणा GIC_TRIG_EDGE			1

/* GIC_SH_DUAL_* - Configures whether पूर्णांकerrupts trigger on both edges */
GIC_ACCESSOR_RW_INTR_BIT(0x200, dual)
#घोषणा GIC_DUAL_SINGLE			0	/* when edge-triggered */
#घोषणा GIC_DUAL_DUAL			1	/* when edge-triggered */

/* GIC_SH_WEDGE - Write an 'edge', ie. trigger an पूर्णांकerrupt */
GIC_ACCESSOR_RW(32, 0x280, wedge)
#घोषणा GIC_WEDGE_RW			BIT(31)
#घोषणा GIC_WEDGE_INTR			GENMASK(7, 0)

/* GIC_SH_RMASK_* - Reset/clear shared पूर्णांकerrupt mask bits */
GIC_ACCESSOR_RW_INTR_BIT(0x300, rmask)

/* GIC_SH_SMASK_* - Set shared पूर्णांकerrupt mask bits */
GIC_ACCESSOR_RW_INTR_BIT(0x380, smask)

/* GIC_SH_MASK_* - Read the current shared पूर्णांकerrupt mask */
GIC_ACCESSOR_RO_INTR_BIT(0x400, mask)

/* GIC_SH_PEND_* - Read currently pending shared पूर्णांकerrupts */
GIC_ACCESSOR_RO_INTR_BIT(0x480, pend)

/* GIC_SH_MAPx_PIN - Map shared पूर्णांकerrupts to a particular CPU pin */
GIC_ACCESSOR_RW_INTR_REG(32, 0x500, 0x4, map_pin)
#घोषणा GIC_MAP_PIN_MAP_TO_PIN		BIT(31)
#घोषणा GIC_MAP_PIN_MAP_TO_NMI		BIT(30)
#घोषणा GIC_MAP_PIN_MAP			GENMASK(5, 0)

/* GIC_SH_MAPx_VP - Map shared पूर्णांकerrupts to a particular Virtual Processor */
GIC_ACCESSOR_RW_INTR_REG(32, 0x2000, 0x20, map_vp)

/* GIC_Vx_CTL - VP-level पूर्णांकerrupt control */
GIC_VX_ACCESSOR_RW(32, 0x000, ctl)
#घोषणा GIC_VX_CTL_FDC_ROUTABLE		BIT(4)
#घोषणा GIC_VX_CTL_SWINT_ROUTABLE	BIT(3)
#घोषणा GIC_VX_CTL_PERFCNT_ROUTABLE	BIT(2)
#घोषणा GIC_VX_CTL_TIMER_ROUTABLE	BIT(1)
#घोषणा GIC_VX_CTL_EIC			BIT(0)

/* GIC_Vx_PEND - Read currently pending local पूर्णांकerrupts */
GIC_VX_ACCESSOR_RO(32, 0x004, pend)

/* GIC_Vx_MASK - Read the current local पूर्णांकerrupt mask */
GIC_VX_ACCESSOR_RO(32, 0x008, mask)

/* GIC_Vx_RMASK - Reset/clear local पूर्णांकerrupt mask bits */
GIC_VX_ACCESSOR_RW(32, 0x00c, rmask)

/* GIC_Vx_SMASK - Set local पूर्णांकerrupt mask bits */
GIC_VX_ACCESSOR_RW(32, 0x010, smask)

/* GIC_Vx_*_MAP - Route local पूर्णांकerrupts to the desired pins */
GIC_VX_ACCESSOR_RW_INTR_REG(32, 0x040, 0x4, map)

/* GIC_Vx_WD_MAP - Route the local watchकरोg समयr पूर्णांकerrupt */
GIC_VX_ACCESSOR_RW(32, 0x040, wd_map)

/* GIC_Vx_COMPARE_MAP - Route the local count/compare पूर्णांकerrupt */
GIC_VX_ACCESSOR_RW(32, 0x044, compare_map)

/* GIC_Vx_TIMER_MAP - Route the local CPU समयr (cp0 count/compare) पूर्णांकerrupt */
GIC_VX_ACCESSOR_RW(32, 0x048, समयr_map)

/* GIC_Vx_FDC_MAP - Route the local fast debug channel पूर्णांकerrupt */
GIC_VX_ACCESSOR_RW(32, 0x04c, fdc_map)

/* GIC_Vx_PERFCTR_MAP - Route the local perक्रमmance counter पूर्णांकerrupt */
GIC_VX_ACCESSOR_RW(32, 0x050, perfctr_map)

/* GIC_Vx_SWINT0_MAP - Route the local software पूर्णांकerrupt 0 */
GIC_VX_ACCESSOR_RW(32, 0x054, swपूर्णांक0_map)

/* GIC_Vx_SWINT1_MAP - Route the local software पूर्णांकerrupt 1 */
GIC_VX_ACCESSOR_RW(32, 0x058, swपूर्णांक1_map)

/* GIC_Vx_OTHER - Configure access to other Virtual Processor रेजिस्टरs */
GIC_VX_ACCESSOR_RW(32, 0x080, other)
#घोषणा GIC_VX_OTHER_VPNUM		GENMASK(5, 0)

/* GIC_Vx_IDENT - Retrieve the local Virtual Processor's ID */
GIC_VX_ACCESSOR_RO(32, 0x088, ident)
#घोषणा GIC_VX_IDENT_VPNUM		GENMASK(5, 0)

/* GIC_Vx_COMPARE - Value to compare with GIC_SH_COUNTER */
GIC_VX_ACCESSOR_RW(64, 0x0a0, compare)

/* GIC_Vx_EIC_SHADOW_SET_BASE - Set shaकरोw रेजिस्टर set क्रम each पूर्णांकerrupt */
GIC_VX_ACCESSOR_RW_INTR_REG(32, 0x100, 0x4, eic_shaकरोw_set)

/**
 * क्रमागत mips_gic_local_पूर्णांकerrupt - GIC local पूर्णांकerrupts
 * @GIC_LOCAL_INT_WD: GIC watchकरोg समयr पूर्णांकerrupt
 * @GIC_LOCAL_INT_COMPARE: GIC count/compare पूर्णांकerrupt
 * @GIC_LOCAL_INT_TIMER: CP0 count/compare पूर्णांकerrupt
 * @GIC_LOCAL_INT_PERFCTR: Perक्रमmance counter पूर्णांकerrupt
 * @GIC_LOCAL_INT_SWINT0: Software पूर्णांकerrupt 0
 * @GIC_LOCAL_INT_SWINT1: Software पूर्णांकerrupt 1
 * @GIC_LOCAL_INT_FDC: Fast debug channel पूर्णांकerrupt
 * @GIC_NUM_LOCAL_INTRS: The number of local पूर्णांकerrupts
 *
 * Enumerates पूर्णांकerrupts provided by the GIC that are local to a VP.
 */
क्रमागत mips_gic_local_पूर्णांकerrupt अणु
	GIC_LOCAL_INT_WD,
	GIC_LOCAL_INT_COMPARE,
	GIC_LOCAL_INT_TIMER,
	GIC_LOCAL_INT_PERFCTR,
	GIC_LOCAL_INT_SWINT0,
	GIC_LOCAL_INT_SWINT1,
	GIC_LOCAL_INT_FDC,
	GIC_NUM_LOCAL_INTRS
पूर्ण;

/**
 * mips_gic_present() - Determine whether a GIC is present
 *
 * Determines whether a MIPS Global Interrupt Controller (GIC) is present in
 * the प्रणाली that the kernel is running on.
 *
 * Return true अगर a GIC is present, अन्यथा false.
 */
अटल अंतरभूत bool mips_gic_present(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_MIPS_GIC) && mips_gic_base;
पूर्ण

/**
 * mips_gic_vx_map_reg() - Return GIC_Vx_<पूर्णांकr>_MAP रेजिस्टर offset
 * @पूर्णांकr: A GIC local पूर्णांकerrupt
 *
 * Determine the index of the GIC_VL_<पूर्णांकr>_MAP or GIC_VO_<पूर्णांकr>_MAP रेजिस्टर
 * within the block of GIC map रेजिस्टरs. This is almost the same as the order
 * of पूर्णांकerrupts in the pending & mask रेजिस्टरs, as used by क्रमागत
 * mips_gic_local_पूर्णांकerrupt, but moves the FDC पूर्णांकerrupt & thus offsets the
 * पूर्णांकerrupts after it...
 *
 * Return: The map रेजिस्टर index corresponding to @पूर्णांकr.
 *
 * The वापस value is suitable क्रम use with the (पढ़ो|ग_लिखो)_gic_v[lo]_map
 * accessor functions.
 */
अटल अंतरभूत अचिन्हित पूर्णांक
mips_gic_vx_map_reg(क्रमागत mips_gic_local_पूर्णांकerrupt पूर्णांकr)
अणु
	/* WD, Compare & Timer are 1:1 */
	अगर (पूर्णांकr <= GIC_LOCAL_INT_TIMER)
		वापस पूर्णांकr;

	/* FDC moves to after Timer... */
	अगर (पूर्णांकr == GIC_LOCAL_INT_FDC)
		वापस GIC_LOCAL_INT_TIMER + 1;

	/* As a result everything अन्यथा is offset by 1 */
	वापस पूर्णांकr + 1;
पूर्ण

/**
 * gic_get_c0_compare_पूर्णांक() - Return cp0 count/compare पूर्णांकerrupt virq
 *
 * Determine the virq number to use क्रम the coprocessor 0 count/compare
 * पूर्णांकerrupt, which may be routed via the GIC.
 *
 * Returns the virq number or a negative error number.
 */
बाह्य पूर्णांक gic_get_c0_compare_पूर्णांक(व्योम);

/**
 * gic_get_c0_perfcount_पूर्णांक() - Return perक्रमmance counter पूर्णांकerrupt virq
 *
 * Determine the virq number to use क्रम CPU perक्रमmance counter पूर्णांकerrupts,
 * which may be routed via the GIC.
 *
 * Returns the virq number or a negative error number.
 */
बाह्य पूर्णांक gic_get_c0_perfcount_पूर्णांक(व्योम);

/**
 * gic_get_c0_fdc_पूर्णांक() - Return fast debug channel पूर्णांकerrupt virq
 *
 * Determine the virq number to use क्रम fast debug channel (FDC) पूर्णांकerrupts,
 * which may be routed via the GIC.
 *
 * Returns the virq number or a negative error number.
 */
बाह्य पूर्णांक gic_get_c0_fdc_पूर्णांक(व्योम);

#पूर्ण_अगर /* __MIPS_ASM_MIPS_CPS_H__ */
