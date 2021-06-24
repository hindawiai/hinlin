<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP2/3/4 Power/Reset Management (PRM) bitfield definitions
 *
 * Copyright (C) 2007-2009, 2012 Texas Instruments, Inc.
 * Copyright (C) 2010 Nokia Corporation
 *
 * Paul Walmsley
 */
#अगर_अघोषित __ARCH_ARM_MACH_OMAP2_PRM_H
#घोषणा __ARCH_ARM_MACH_OMAP2_PRM_H

#समावेश "prcm-common.h"

# अगरndef __ASSEMBLER__
बाह्य काष्ठा omap_करोमुख्य_base prm_base;
बाह्य u16 prm_features;
बाह्य व्योम omap2_set_globals_prm(व्योम __iomem *prm);
पूर्णांक omap_prcm_init(व्योम);
पूर्णांक omap2_prm_base_init(व्योम);
पूर्णांक omap2_prcm_base_init(व्योम);
# endअगर

/*
 * prm_features flag values
 *
 * PRM_HAS_IO_WAKEUP: has IO wakeup capability
 * PRM_HAS_VOLTAGE: has voltage करोमुख्यs
 */
#घोषणा PRM_HAS_IO_WAKEUP	BIT(0)
#घोषणा PRM_HAS_VOLTAGE		BIT(1)

/*
 * MAX_MODULE_SOFTRESET_WAIT: Maximum microseconds to रुको क्रम OMAP
 * module to softreset
 */
#घोषणा MAX_MODULE_SOFTRESET_WAIT		10000

/*
 * MAX_MODULE_HARDRESET_WAIT: Maximum microseconds to रुको क्रम an OMAP
 * submodule to निकास hardreset
 */
#घोषणा MAX_MODULE_HARDRESET_WAIT		10000

/*
 * Register bitfields
 */

/*
 * 24XX: PM_PWSTST_CORE, PM_PWSTST_GFX, PM_PWSTST_MPU, PM_PWSTST_DSP
 *
 * 2430: PM_PWSTST_MDM
 *
 * 3430: PM_PWSTST_IVA2, PM_PWSTST_MPU, PM_PWSTST_CORE, PM_PWSTST_GFX,
 *	 PM_PWSTST_DSS, PM_PWSTST_CAM, PM_PWSTST_PER, PM_PWSTST_EMU,
 *	 PM_PWSTST_NEON
 */
#घोषणा OMAP_INTRANSITION_MASK				(1 << 20)


/*
 * 24XX: PM_PWSTST_GFX, PM_PWSTST_DSP
 *
 * 2430: PM_PWSTST_MDM
 *
 * 3430: PM_PWSTST_IVA2, PM_PWSTST_MPU, PM_PWSTST_CORE, PM_PWSTST_GFX,
 *	 PM_PWSTST_DSS, PM_PWSTST_CAM, PM_PWSTST_PER, PM_PWSTST_EMU,
 *	 PM_PWSTST_NEON
 */
#घोषणा OMAP_POWERSTATEST_SHIFT				0
#घोषणा OMAP_POWERSTATEST_MASK				(0x3 << 0)

/*
 * 24XX: PM_PWSTCTRL_MPU, PM_PWSTCTRL_CORE, PM_PWSTCTRL_GFX,
 *       PM_PWSTCTRL_DSP, PM_PWSTST_MPU
 *
 * 2430: PM_PWSTCTRL_MDM shared bits
 *
 * 3430: PM_PWSTCTRL_IVA2, PM_PWSTCTRL_MPU, PM_PWSTCTRL_CORE,
 *	 PM_PWSTCTRL_GFX, PM_PWSTCTRL_DSS, PM_PWSTCTRL_CAM, PM_PWSTCTRL_PER,
 *	 PM_PWSTCTRL_NEON shared bits
 */
#घोषणा OMAP_POWERSTATE_SHIFT				0
#घोषणा OMAP_POWERSTATE_MASK				(0x3 << 0)

/*
 * Standardized OMAP reset source bits
 *
 * To the extent these happen to match the hardware रेजिस्टर bit
 * shअगरts, it's purely coincidental.  Used by omap-wdt.c.
 * OMAP_UNKNOWN_RST_SRC_ID_SHIFT is a special value, used whenever
 * there are any bits reमुख्यing in the global PRM_RSTST रेजिस्टर that
 * haven't been identअगरied, or when the PRM code क्रम the current SoC
 * करोesn't know how to पूर्णांकerpret the रेजिस्टर.
 */
#घोषणा OMAP_GLOBAL_COLD_RST_SRC_ID_SHIFT			0
#घोषणा OMAP_GLOBAL_WARM_RST_SRC_ID_SHIFT			1
#घोषणा OMAP_SECU_VIOL_RST_SRC_ID_SHIFT				2
#घोषणा OMAP_MPU_WD_RST_SRC_ID_SHIFT				3
#घोषणा OMAP_SECU_WD_RST_SRC_ID_SHIFT				4
#घोषणा OMAP_EXTWARM_RST_SRC_ID_SHIFT				5
#घोषणा OMAP_VDD_MPU_VM_RST_SRC_ID_SHIFT			6
#घोषणा OMAP_VDD_IVA_VM_RST_SRC_ID_SHIFT			7
#घोषणा OMAP_VDD_CORE_VM_RST_SRC_ID_SHIFT			8
#घोषणा OMAP_ICEPICK_RST_SRC_ID_SHIFT				9
#घोषणा OMAP_ICECRUSHER_RST_SRC_ID_SHIFT			10
#घोषणा OMAP_C2C_RST_SRC_ID_SHIFT				11
#घोषणा OMAP_UNKNOWN_RST_SRC_ID_SHIFT				12

#अगर_अघोषित __ASSEMBLER__

/**
 * काष्ठा prm_reset_src_map - map रेजिस्टर bitshअगरts to standard bitshअगरts
 * @reg_shअगरt: bitshअगरt in the PRM reset source रेजिस्टर
 * @std_shअगरt: bitshअगरt equivalent in the standard reset source list
 *
 * The fields are चिन्हित because -1 is used as a terminator.
 */
काष्ठा prm_reset_src_map अणु
	s8 reg_shअगरt;
	s8 std_shअगरt;
पूर्ण;

/**
 * काष्ठा prm_ll_data - fn ptrs to per-SoC PRM function implementations
 * @पढ़ो_reset_sources: ptr to the SoC PRM-specअगरic get_reset_source impl
 * @was_any_context_lost_old: ptr to the SoC PRM context loss test fn
 * @clear_context_loss_flags_old: ptr to the SoC PRM context loss flag clear fn
 * @late_init: ptr to the late init function
 * @निश्चित_hardreset: ptr to the SoC PRM hardreset निश्चित impl
 * @deनिश्चित_hardreset: ptr to the SoC PRM hardreset deनिश्चित impl
 *
 * XXX @was_any_context_lost_old and @clear_context_loss_flags_old are
 * deprecated.
 */
काष्ठा prm_ll_data अणु
	u32 (*पढ़ो_reset_sources)(व्योम);
	bool (*was_any_context_lost_old)(u8 part, s16 inst, u16 idx);
	व्योम (*clear_context_loss_flags_old)(u8 part, s16 inst, u16 idx);
	पूर्णांक (*late_init)(व्योम);
	पूर्णांक (*निश्चित_hardreset)(u8 shअगरt, u8 part, s16 prm_mod, u16 offset);
	पूर्णांक (*deनिश्चित_hardreset)(u8 shअगरt, u8 st_shअगरt, u8 part, s16 prm_mod,
				  u16 offset, u16 st_offset);
	पूर्णांक (*is_hardreset_निश्चितed)(u8 shअगरt, u8 part, s16 prm_mod,
				     u16 offset);
	व्योम (*reset_प्रणाली)(व्योम);
	पूर्णांक (*clear_mod_irqs)(s16 module, u8 regs, u32 wkst_mask);
	u32 (*vp_check_txकरोne)(u8 vp_id);
	व्योम (*vp_clear_txकरोne)(u8 vp_id);
पूर्ण;

बाह्य पूर्णांक prm_रेजिस्टर(काष्ठा prm_ll_data *pld);
बाह्य पूर्णांक prm_unरेजिस्टर(काष्ठा prm_ll_data *pld);

पूर्णांक omap_prm_निश्चित_hardreset(u8 shअगरt, u8 part, s16 prm_mod, u16 offset);
पूर्णांक omap_prm_deनिश्चित_hardreset(u8 shअगरt, u8 st_shअगरt, u8 part, s16 prm_mod,
				u16 offset, u16 st_offset);
पूर्णांक omap_prm_is_hardreset_निश्चितed(u8 shअगरt, u8 part, s16 prm_mod, u16 offset);
बाह्य u32 prm_पढ़ो_reset_sources(व्योम);
बाह्य bool prm_was_any_context_lost_old(u8 part, s16 inst, u16 idx);
बाह्य व्योम prm_clear_context_loss_flags_old(u8 part, s16 inst, u16 idx);
व्योम omap_prm_reset_प्रणाली(व्योम);

व्योम omap_prm_reconfigure_io_chain(व्योम);
पूर्णांक omap_prm_clear_mod_irqs(s16 module, u8 regs, u32 wkst_mask);

/*
 * Voltage Processor (VP) identअगरiers
 */
#घोषणा OMAP3_VP_VDD_MPU_ID	0
#घोषणा OMAP3_VP_VDD_CORE_ID	1
#घोषणा OMAP4_VP_VDD_CORE_ID	0
#घोषणा OMAP4_VP_VDD_IVA_ID	1
#घोषणा OMAP4_VP_VDD_MPU_ID	2

u32 omap_prm_vp_check_txकरोne(u8 vp_id);
व्योम omap_prm_vp_clear_txकरोne(u8 vp_id);

#पूर्ण_अगर


#पूर्ण_अगर
