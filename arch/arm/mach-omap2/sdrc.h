<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __ARCH_ARM_MACH_OMAP2_SDRC_H
#घोषणा __ARCH_ARM_MACH_OMAP2_SDRC_H

/*
 * OMAP2/3 SDRC/SMS macros and prototypes
 *
 * Copyright (C) 2007-2008, 2012 Texas Instruments, Inc.
 * Copyright (C) 2007-2008 Nokia Corporation
 *
 * Paul Walmsley
 * Tony Lindgren
 * Riअक्षरd Woodruff
 */
#अघोषित DEBUG

#अगर_अघोषित __ASSEMBLER__

#समावेश <linux/पन.स>

बाह्य व्योम __iomem *omap2_sdrc_base;
बाह्य व्योम __iomem *omap2_sms_base;

#घोषणा OMAP_SDRC_REGADDR(reg)			(omap2_sdrc_base + (reg))
#घोषणा OMAP_SMS_REGADDR(reg)			(omap2_sms_base + (reg))

/* SDRC global रेजिस्टर get/set */

अटल अंतरभूत व्योम sdrc_ग_लिखो_reg(u32 val, u16 reg)
अणु
	ग_लिखोl_relaxed(val, OMAP_SDRC_REGADDR(reg));
पूर्ण

अटल अंतरभूत u32 sdrc_पढ़ो_reg(u16 reg)
अणु
	वापस पढ़ोl_relaxed(OMAP_SDRC_REGADDR(reg));
पूर्ण

/* SMS global रेजिस्टर get/set */

अटल अंतरभूत व्योम sms_ग_लिखो_reg(u32 val, u16 reg)
अणु
	ग_लिखोl_relaxed(val, OMAP_SMS_REGADDR(reg));
पूर्ण

अटल अंतरभूत u32 sms_पढ़ो_reg(u16 reg)
अणु
	वापस पढ़ोl_relaxed(OMAP_SMS_REGADDR(reg));
पूर्ण

बाह्य व्योम omap2_set_globals_sdrc(व्योम __iomem *sdrc, व्योम __iomem *sms);


/**
 * काष्ठा omap_sdrc_params - SDRC parameters क्रम a given SDRC घड़ी rate
 * @rate: SDRC घड़ी rate (in Hz)
 * @actim_ctrla: Value to program to SDRC_ACTIM_CTRLA क्रम this rate
 * @actim_ctrlb: Value to program to SDRC_ACTIM_CTRLB क्रम this rate
 * @rfr_ctrl: Value to program to SDRC_RFR_CTRL क्रम this rate
 * @mr: Value to program to SDRC_MR क्रम this rate
 *
 * This काष्ठाure holds a pre-computed set of रेजिस्टर values क्रम the
 * SDRC क्रम a given SDRC घड़ी rate and SDRAM chip.  These are
 * पूर्णांकended to be pre-computed and specअगरied in an array in the board-*.c
 * files.  The काष्ठाure is keyed off the 'rate' field.
 */
काष्ठा omap_sdrc_params अणु
	अचिन्हित दीर्घ rate;
	u32 actim_ctrla;
	u32 actim_ctrlb;
	u32 rfr_ctrl;
	u32 mr;
पूर्ण;

#अगर_घोषित CONFIG_SOC_HAS_OMAP2_SDRC
व्योम omap2_sdrc_init(काष्ठा omap_sdrc_params *sdrc_cs0,
			    काष्ठा omap_sdrc_params *sdrc_cs1);
#अन्यथा
अटल अंतरभूत व्योम __init omap2_sdrc_init(काष्ठा omap_sdrc_params *sdrc_cs0,
					  काष्ठा omap_sdrc_params *sdrc_cs1) अणुपूर्ण;
#पूर्ण_अगर

पूर्णांक omap2_sdrc_get_params(अचिन्हित दीर्घ r,
			  काष्ठा omap_sdrc_params **sdrc_cs0,
			  काष्ठा omap_sdrc_params **sdrc_cs1);
व्योम omap2_sms_save_context(व्योम);
व्योम omap2_sms_restore_context(व्योम);

काष्ठा memory_timings अणु
	u32 m_type;		/* ddr = 1, sdr = 0 */
	u32 dll_mode;		/* use lock mode = 1, unlock mode = 0 */
	u32 slow_dll_ctrl;	/* unlock mode, dll value क्रम slow speed */
	u32 fast_dll_ctrl;	/* unlock mode, dll value क्रम fast speed */
	u32 base_cs;		/* base chip select to use क्रम calculations */
पूर्ण;

बाह्य व्योम omap2xxx_sdrc_init_params(u32 क्रमce_lock_to_unlock_mode);
काष्ठा omap_sdrc_params *rx51_get_sdram_timings(व्योम);

u32 omap2xxx_sdrc_dll_is_unlocked(व्योम);
u32 omap2xxx_sdrc_reprogram(u32 level, u32 क्रमce);


#अन्यथा
#घोषणा OMAP242X_SDRC_REGADDR(reg)					\
			OMAP2_L3_IO_ADDRESS(OMAP2420_SDRC_BASE + (reg))
#घोषणा OMAP243X_SDRC_REGADDR(reg)					\
			OMAP2_L3_IO_ADDRESS(OMAP243X_SDRC_BASE + (reg))
#घोषणा OMAP34XX_SDRC_REGADDR(reg)					\
			OMAP2_L3_IO_ADDRESS(OMAP343X_SDRC_BASE + (reg))

#पूर्ण_अगर	/* __ASSEMBLER__ */

/* Minimum frequency that the SDRC DLL can lock at */
#घोषणा MIN_SDRC_DLL_LOCK_FREQ		83000000

/* Scale factor क्रम fixed-poपूर्णांक arith in omap3_core_dpll_m2_set_rate() */
#घोषणा SDRC_MPURATE_SCALE		8

/* 2^SDRC_MPURATE_BASE_SHIFT: MPU MHz that SDRC_MPURATE_LOOPS is defined क्रम */
#घोषणा SDRC_MPURATE_BASE_SHIFT		9

/*
 * SDRC_MPURATE_LOOPS: Number of MPU loops to execute at
 * 2^MPURATE_BASE_SHIFT MHz क्रम SDRC to stabilize
 */
#घोषणा SDRC_MPURATE_LOOPS		96

/* SDRC रेजिस्टर offsets - पढ़ो/ग_लिखो with sdrc_अणुपढ़ो,ग_लिखोपूर्ण_reg() */

#घोषणा SDRC_SYSCONFIG		0x010
#घोषणा SDRC_CS_CFG		0x040
#घोषणा SDRC_SHARING		0x044
#घोषणा SDRC_ERR_TYPE		0x04C
#घोषणा SDRC_DLLA_CTRL		0x060
#घोषणा SDRC_DLLA_STATUS	0x064
#घोषणा SDRC_DLLB_CTRL		0x068
#घोषणा SDRC_DLLB_STATUS	0x06C
#घोषणा SDRC_POWER		0x070
#घोषणा SDRC_MCFG_0		0x080
#घोषणा SDRC_MR_0		0x084
#घोषणा SDRC_EMR2_0		0x08c
#घोषणा SDRC_ACTIM_CTRL_A_0	0x09c
#घोषणा SDRC_ACTIM_CTRL_B_0	0x0a0
#घोषणा SDRC_RFR_CTRL_0		0x0a4
#घोषणा SDRC_MANUAL_0		0x0a8
#घोषणा SDRC_MCFG_1		0x0B0
#घोषणा SDRC_MR_1		0x0B4
#घोषणा SDRC_EMR2_1		0x0BC
#घोषणा SDRC_ACTIM_CTRL_A_1	0x0C4
#घोषणा SDRC_ACTIM_CTRL_B_1	0x0C8
#घोषणा SDRC_RFR_CTRL_1		0x0D4
#घोषणा SDRC_MANUAL_1		0x0D8

#घोषणा SDRC_POWER_AUTOCOUNT_SHIFT	8
#घोषणा SDRC_POWER_AUTOCOUNT_MASK	(0xffff << SDRC_POWER_AUTOCOUNT_SHIFT)
#घोषणा SDRC_POWER_CLKCTRL_SHIFT	4
#घोषणा SDRC_POWER_CLKCTRL_MASK		(0x3 << SDRC_POWER_CLKCTRL_SHIFT)
#घोषणा SDRC_SELF_REFRESH_ON_AUTOCOUNT	(0x2 << SDRC_POWER_CLKCTRL_SHIFT)

/*
 * These values represent the number of memory घड़ी cycles between
 * स्वतःrefresh initiation.  They assume 1 refresh per 64 ms (JEDEC), 8192
 * rows per device, and include a subtraction of a 50 cycle winकरोw in the
 * event that the स्वतःrefresh command is delayed due to other SDRC activity.
 * The '| 1' sets the ARE field to send one स्वतःrefresh when the स्वतःrefresh
 * counter reaches 0.
 *
 * These represent optimal values क्रम common parts, it won't work क्रम all.
 * As दीर्घ as you scale करोwn, most parameters are still work, they just
 * become sub-optimal. The RFR value goes in the opposite direction. If you
 * करोn't adjust it करोwn as your घड़ी period increases the refresh पूर्णांकerval
 * will not be met. Setting all parameters क्रम complete worst हाल may work,
 * but may cut memory perक्रमmance by 2x. Due to errata the DLLs need to be
 * unlocked and their value needs run समय calibration. A dynamic call is
 * need क्रम that as no single right value exists across production samples.
 *
 * Only the FULL speed values are given. Current code is such that rate
 * changes must be made at DPLLoutx2. The actual value adjusपंचांगent क्रम low
 * frequency operation will be handled by omap_set_perक्रमmance()
 *
 * By having the boot loader boot up in the fastest L4 speed available likely
 * will result in something which you can चयन between.
 */
#घोषणा SDRC_RFR_CTRL_165MHz	(0x00044c00 | 1)
#घोषणा SDRC_RFR_CTRL_133MHz	(0x0003de00 | 1)
#घोषणा SDRC_RFR_CTRL_100MHz	(0x0002da01 | 1)
#घोषणा SDRC_RFR_CTRL_110MHz	(0x0002da01 | 1) /* Need to calc */
#घोषणा SDRC_RFR_CTRL_BYPASS	(0x00005000 | 1) /* Need to calc */


/*
 * SMS रेजिस्टर access
 */

#घोषणा OMAP242X_SMS_REGADDR(reg)					\
		(व्योम __iomem *)OMAP2_L3_IO_ADDRESS(OMAP2420_SMS_BASE + reg)
#घोषणा OMAP243X_SMS_REGADDR(reg)					\
		(व्योम __iomem *)OMAP2_L3_IO_ADDRESS(OMAP243X_SMS_BASE + reg)
#घोषणा OMAP343X_SMS_REGADDR(reg)					\
		(व्योम __iomem *)OMAP2_L3_IO_ADDRESS(OMAP343X_SMS_BASE + reg)

/* SMS रेजिस्टर offsets - पढ़ो/ग_लिखो with sms_अणुपढ़ो,ग_लिखोपूर्ण_reg() */

#घोषणा SMS_SYSCONFIG			0x010
/* REVISIT: fill in other SMS रेजिस्टरs here */



#पूर्ण_अगर
