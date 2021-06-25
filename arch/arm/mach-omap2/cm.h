<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP2+ Clock Management prototypes
 *
 * Copyright (C) 2007-2009, 2012 Texas Instruments, Inc.
 * Copyright (C) 2007-2009 Nokia Corporation
 *
 * Written by Paul Walmsley
 */
#अगर_अघोषित __ARCH_ASM_MACH_OMAP2_CM_H
#घोषणा __ARCH_ASM_MACH_OMAP2_CM_H

/*
 * MAX_MODULE_READY_TIME: max duration in microseconds to रुको क्रम the
 * PRCM to request that a module निकास the inactive state in the हाल of
 * OMAP2 & 3.
 * In the हाल of OMAP4 this is the max duration in microseconds क्रम the
 * module to reach the functionnal state from an inactive state.
 */
#घोषणा MAX_MODULE_READY_TIME		2000

# अगरndef __ASSEMBLER__
#समावेश <linux/clk/ti.h>

#समावेश "prcm-common.h"

बाह्य काष्ठा omap_करोमुख्य_base cm_base;
बाह्य काष्ठा omap_करोमुख्य_base cm2_base;
बाह्य व्योम omap2_set_globals_cm(व्योम __iomem *cm, व्योम __iomem *cm2);
# endअगर

/*
 * MAX_MODULE_DISABLE_TIME: max duration in microseconds to रुको क्रम
 * the PRCM to request that a module enter the inactive state in the
 * हाल of OMAP2 & 3.  In the हाल of OMAP4 this is the max duration
 * in microseconds क्रम the module to reach the inactive state from
 * a functional state.
 * XXX FSUSB on OMAP4430 takes ~4ms to idle after reset during
 * kernel init.
 */
#घोषणा MAX_MODULE_DISABLE_TIME		5000

# अगरndef __ASSEMBLER__

/**
 * काष्ठा cm_ll_data - fn ptrs to per-SoC CM function implementations
 * @split_idlest_reg: ptr to the SoC CM-specअगरic split_idlest_reg impl
 * @रुको_module_पढ़ोy: ptr to the SoC CM-specअगरic रुको_module_पढ़ोy impl
 * @रुको_module_idle: ptr to the SoC CM-specअगरic रुको_module_idle impl
 * @module_enable: ptr to the SoC CM-specअगरic module_enable impl
 * @module_disable: ptr to the SoC CM-specअगरic module_disable impl
 * @xlate_clkctrl: ptr to the SoC CM-specअगरic clkctrl xlate addr impl
 */
काष्ठा cm_ll_data अणु
	पूर्णांक (*split_idlest_reg)(काष्ठा clk_omap_reg *idlest_reg, s16 *prcm_inst,
				u8 *idlest_reg_id);
	पूर्णांक (*रुको_module_पढ़ोy)(u8 part, s16 prcm_mod, u16 idlest_reg,
				 u8 idlest_shअगरt);
	पूर्णांक (*रुको_module_idle)(u8 part, s16 prcm_mod, u16 idlest_reg,
				u8 idlest_shअगरt);
	व्योम (*module_enable)(u8 mode, u8 part, u16 inst, u16 clkctrl_offs);
	व्योम (*module_disable)(u8 part, u16 inst, u16 clkctrl_offs);
	u32 (*xlate_clkctrl)(u8 part, u16 inst, u16 clkctrl_offs);
पूर्ण;

बाह्य पूर्णांक cm_split_idlest_reg(काष्ठा clk_omap_reg *idlest_reg, s16 *prcm_inst,
			       u8 *idlest_reg_id);
पूर्णांक omap_cm_रुको_module_पढ़ोy(u8 part, s16 prcm_mod, u16 idlest_reg,
			      u8 idlest_shअगरt);
पूर्णांक omap_cm_रुको_module_idle(u8 part, s16 prcm_mod, u16 idlest_reg,
			     u8 idlest_shअगरt);
पूर्णांक omap_cm_module_enable(u8 mode, u8 part, u16 inst, u16 clkctrl_offs);
पूर्णांक omap_cm_module_disable(u8 part, u16 inst, u16 clkctrl_offs);
u32 omap_cm_xlate_clkctrl(u8 part, u16 inst, u16 clkctrl_offs);
बाह्य पूर्णांक cm_रेजिस्टर(स्थिर काष्ठा cm_ll_data *cld);
बाह्य पूर्णांक cm_unरेजिस्टर(स्थिर काष्ठा cm_ll_data *cld);
पूर्णांक omap_cm_init(व्योम);
पूर्णांक omap2_cm_base_init(व्योम);

# endअगर

#पूर्ण_अगर
