<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/include/यंत्र/hardware/cache-l2x0.h
 *
 * Copyright (C) 2007 ARM Limited
 */

#अगर_अघोषित __ASM_ARM_HARDWARE_L2X0_H
#घोषणा __ASM_ARM_HARDWARE_L2X0_H

#समावेश <linux/त्रुटिसं.स>

#घोषणा L2X0_CACHE_ID			0x000
#घोषणा L2X0_CACHE_TYPE			0x004
#घोषणा L2X0_CTRL			0x100
#घोषणा L2X0_AUX_CTRL			0x104
#घोषणा L310_TAG_LATENCY_CTRL		0x108
#घोषणा L310_DATA_LATENCY_CTRL		0x10C
#घोषणा L2X0_EVENT_CNT_CTRL		0x200
#घोषणा L2X0_EVENT_CNT1_CFG		0x204
#घोषणा L2X0_EVENT_CNT0_CFG		0x208
#घोषणा L2X0_EVENT_CNT1_VAL		0x20C
#घोषणा L2X0_EVENT_CNT0_VAL		0x210
#घोषणा L2X0_INTR_MASK			0x214
#घोषणा L2X0_MASKED_INTR_STAT		0x218
#घोषणा L2X0_RAW_INTR_STAT		0x21C
#घोषणा L2X0_INTR_CLEAR			0x220
#घोषणा L2X0_CACHE_SYNC			0x730
#घोषणा L2X0_DUMMY_REG			0x740
#घोषणा L2X0_INV_LINE_PA		0x770
#घोषणा L2X0_INV_WAY			0x77C
#घोषणा L2X0_CLEAN_LINE_PA		0x7B0
#घोषणा L2X0_CLEAN_LINE_IDX		0x7B8
#घोषणा L2X0_CLEAN_WAY			0x7BC
#घोषणा L2X0_CLEAN_INV_LINE_PA		0x7F0
#घोषणा L2X0_CLEAN_INV_LINE_IDX		0x7F8
#घोषणा L2X0_CLEAN_INV_WAY		0x7FC
/*
 * The lockकरोwn रेजिस्टरs repeat 8 बार क्रम L310, the L210 has only one
 * D and one I lockकरोwn रेजिस्टर at 0x0900 and 0x0904.
 */
#घोषणा L2X0_LOCKDOWN_WAY_D_BASE	0x900
#घोषणा L2X0_LOCKDOWN_WAY_I_BASE	0x904
#घोषणा L2X0_LOCKDOWN_STRIDE		0x08
#घोषणा L310_ADDR_FILTER_START		0xC00
#घोषणा L310_ADDR_FILTER_END		0xC04
#घोषणा L2X0_TEST_OPERATION		0xF00
#घोषणा L2X0_LINE_DATA			0xF10
#घोषणा L2X0_LINE_TAG			0xF30
#घोषणा L2X0_DEBUG_CTRL			0xF40
#घोषणा L310_PREFETCH_CTRL		0xF60
#घोषणा L310_POWER_CTRL			0xF80
#घोषणा   L310_DYNAMIC_CLK_GATING_EN	(1 << 1)
#घोषणा   L310_STNDBY_MODE_EN		(1 << 0)

/* Registers shअगरts and masks */
#घोषणा L2X0_CACHE_ID_PART_MASK		(0xf << 6)
#घोषणा L2X0_CACHE_ID_PART_L210		(1 << 6)
#घोषणा L2X0_CACHE_ID_PART_L220		(2 << 6)
#घोषणा L2X0_CACHE_ID_PART_L310		(3 << 6)
#घोषणा L2X0_CACHE_ID_RTL_MASK          0x3f
#घोषणा L210_CACHE_ID_RTL_R0P2_02	0x00
#घोषणा L210_CACHE_ID_RTL_R0P1		0x01
#घोषणा L210_CACHE_ID_RTL_R0P2_01	0x02
#घोषणा L210_CACHE_ID_RTL_R0P3		0x03
#घोषणा L210_CACHE_ID_RTL_R0P4		0x0b
#घोषणा L210_CACHE_ID_RTL_R0P5		0x0f
#घोषणा L220_CACHE_ID_RTL_R1P7_01REL0	0x06
#घोषणा L310_CACHE_ID_RTL_R0P0		0x00
#घोषणा L310_CACHE_ID_RTL_R1P0		0x02
#घोषणा L310_CACHE_ID_RTL_R2P0		0x04
#घोषणा L310_CACHE_ID_RTL_R3P0		0x05
#घोषणा L310_CACHE_ID_RTL_R3P1		0x06
#घोषणा L310_CACHE_ID_RTL_R3P1_50REL0	0x07
#घोषणा L310_CACHE_ID_RTL_R3P2		0x08
#घोषणा L310_CACHE_ID_RTL_R3P3		0x09

#घोषणा L2X0_EVENT_CNT_CTRL_ENABLE	BIT(0)

#घोषणा L2X0_EVENT_CNT_CFG_SRC_SHIFT	2
#घोषणा L2X0_EVENT_CNT_CFG_SRC_MASK	0xf
#घोषणा L2X0_EVENT_CNT_CFG_SRC_DISABLED	0
#घोषणा L2X0_EVENT_CNT_CFG_INT_DISABLED	0
#घोषणा L2X0_EVENT_CNT_CFG_INT_INCR	1
#घोषणा L2X0_EVENT_CNT_CFG_INT_OVERFLOW	2

/* L2C auxiliary control रेजिस्टर - bits common to L2C-210/220/310 */
#घोषणा L2C_AUX_CTRL_WAY_SIZE_SHIFT		17
#घोषणा L2C_AUX_CTRL_WAY_SIZE_MASK		(7 << 17)
#घोषणा L2C_AUX_CTRL_WAY_SIZE(n)		((n) << 17)
#घोषणा L2C_AUX_CTRL_EVTMON_ENABLE		BIT(20)
#घोषणा L2C_AUX_CTRL_PARITY_ENABLE		BIT(21)
#घोषणा L2C_AUX_CTRL_SHARED_OVERRIDE		BIT(22)
/* L2C-210/220 common bits */
#घोषणा L2X0_AUX_CTRL_DATA_RD_LATENCY_SHIFT	0
#घोषणा L2X0_AUX_CTRL_DATA_RD_LATENCY_MASK	(7 << 0)
#घोषणा L2X0_AUX_CTRL_DATA_WR_LATENCY_SHIFT	3
#घोषणा L2X0_AUX_CTRL_DATA_WR_LATENCY_MASK	(7 << 3)
#घोषणा L2X0_AUX_CTRL_TAG_LATENCY_SHIFT		6
#घोषणा L2X0_AUX_CTRL_TAG_LATENCY_MASK		(7 << 6)
#घोषणा L2X0_AUX_CTRL_सूचीTY_LATENCY_SHIFT	9
#घोषणा L2X0_AUX_CTRL_सूचीTY_LATENCY_MASK	(7 << 9)
#घोषणा L2X0_AUX_CTRL_ASSOC_SHIFT		13
#घोषणा L2X0_AUX_CTRL_ASSOC_MASK		(15 << 13)
/* L2C-210 specअगरic bits */
#घोषणा L210_AUX_CTRL_WRAP_DISABLE		BIT(12)
#घोषणा L210_AUX_CTRL_WA_OVERRIDE		BIT(23)
#घोषणा L210_AUX_CTRL_EXCLUSIVE_ABORT		BIT(24)
/* L2C-220 specअगरic bits */
#घोषणा L220_AUX_CTRL_EXCLUSIVE_CACHE		BIT(12)
#घोषणा L220_AUX_CTRL_FWA_SHIFT			23
#घोषणा L220_AUX_CTRL_FWA_MASK			(3 << 23)
#घोषणा L220_AUX_CTRL_NS_LOCKDOWN		BIT(26)
#घोषणा L220_AUX_CTRL_NS_INT_CTRL		BIT(27)
/* L2C-310 specअगरic bits */
#घोषणा L310_AUX_CTRL_FULL_LINE_ZERO		BIT(0)	/* R2P0+ */
#घोषणा L310_AUX_CTRL_HIGHPRIO_SO_DEV		BIT(10)	/* R2P0+ */
#घोषणा L310_AUX_CTRL_STORE_LIMITATION		BIT(11)	/* R2P0+ */
#घोषणा L310_AUX_CTRL_EXCLUSIVE_CACHE		BIT(12)
#घोषणा L310_AUX_CTRL_ASSOCIATIVITY_16		BIT(16)
#घोषणा L310_AUX_CTRL_FWA_SHIFT			23
#घोषणा L310_AUX_CTRL_FWA_MASK			(3 << 23)
#घोषणा L310_AUX_CTRL_CACHE_REPLACE_RR		BIT(25)	/* R2P0+ */
#घोषणा L310_AUX_CTRL_NS_LOCKDOWN		BIT(26)
#घोषणा L310_AUX_CTRL_NS_INT_CTRL		BIT(27)
#घोषणा L310_AUX_CTRL_DATA_PREFETCH		BIT(28)
#घोषणा L310_AUX_CTRL_INSTR_PREFETCH		BIT(29)
#घोषणा L310_AUX_CTRL_EARLY_BRESP		BIT(30)	/* R2P0+ */

#घोषणा L310_LATENCY_CTRL_SETUP(n)		((n) << 0)
#घोषणा L310_LATENCY_CTRL_RD(n)			((n) << 4)
#घोषणा L310_LATENCY_CTRL_WR(n)			((n) << 8)

#घोषणा L310_ADDR_FILTER_EN		1

#घोषणा L310_PREFETCH_CTRL_OFFSET_MASK		0x1f
#घोषणा L310_PREFETCH_CTRL_DBL_LINEFILL_INCR	BIT(23)
#घोषणा L310_PREFETCH_CTRL_PREFETCH_DROP	BIT(24)
#घोषणा L310_PREFETCH_CTRL_DBL_LINEFILL_WRAP	BIT(27)
#घोषणा L310_PREFETCH_CTRL_DATA_PREFETCH	BIT(28)
#घोषणा L310_PREFETCH_CTRL_INSTR_PREFETCH	BIT(29)
#घोषणा L310_PREFETCH_CTRL_DBL_LINEFILL		BIT(30)

#घोषणा L2X0_CTRL_EN			1

#घोषणा L2X0_WAY_SIZE_SHIFT		3

#अगर_अघोषित __ASSEMBLY__
बाह्य व्योम __init l2x0_init(व्योम __iomem *base, u32 aux_val, u32 aux_mask);
#अगर defined(CONFIG_CACHE_L2X0) && defined(CONFIG_OF)
बाह्य पूर्णांक l2x0_of_init(u32 aux_val, u32 aux_mask);
#अन्यथा
अटल अंतरभूत पूर्णांक l2x0_of_init(u32 aux_val, u32 aux_mask)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CACHE_L2X0_PMU
व्योम l2x0_pmu_रेजिस्टर(व्योम __iomem *base, u32 part);
व्योम l2x0_pmu_suspend(व्योम);
व्योम l2x0_pmu_resume(व्योम);
#अन्यथा
अटल अंतरभूत व्योम l2x0_pmu_रेजिस्टर(व्योम __iomem *base, u32 part) अणुपूर्ण
अटल अंतरभूत व्योम l2x0_pmu_suspend(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम l2x0_pmu_resume(व्योम) अणुपूर्ण
#पूर्ण_अगर

काष्ठा l2x0_regs अणु
	अचिन्हित दीर्घ phy_base;
	अचिन्हित दीर्घ aux_ctrl;
	/*
	 * Whether the following रेजिस्टरs need to be saved/restored
	 * depends on platक्रमm
	 */
	अचिन्हित दीर्घ tag_latency;
	अचिन्हित दीर्घ data_latency;
	अचिन्हित दीर्घ filter_start;
	अचिन्हित दीर्घ filter_end;
	अचिन्हित दीर्घ prefetch_ctrl;
	अचिन्हित दीर्घ pwr_ctrl;
	अचिन्हित दीर्घ ctrl;
	अचिन्हित दीर्घ aux2_ctrl;
पूर्ण;

बाह्य काष्ठा l2x0_regs l2x0_saved_regs;

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर
