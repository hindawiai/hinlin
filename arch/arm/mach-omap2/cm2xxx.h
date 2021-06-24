<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP2xxx Clock Management (CM) रेजिस्टर definitions
 *
 * Copyright (C) 2007-2009, 2012 Texas Instruments, Inc.
 * Copyright (C) 2007-2010 Nokia Corporation
 * Paul Walmsley
 *
 * The CM hardware modules on the OMAP2/3 are quite similar to each
 * other.  The CM modules/instances on OMAP4 are quite dअगरferent, so
 * they are handled in a separate file.
 */
#अगर_अघोषित __ARCH_ASM_MACH_OMAP2_CM2XXX_H
#घोषणा __ARCH_ASM_MACH_OMAP2_CM2XXX_H

#समावेश "prcm-common.h"
#समावेश "cm2xxx_3xxx.h"

#घोषणा OMAP2420_CM_REGADDR(module, reg)				\
			OMAP2_L4_IO_ADDRESS(OMAP2420_CM_BASE + (module) + (reg))
#घोषणा OMAP2430_CM_REGADDR(module, reg)				\
			OMAP2_L4_IO_ADDRESS(OMAP2430_CM_BASE + (module) + (reg))

/*
 * Module specअगरic CM रेजिस्टर offsets from CM_BASE + करोमुख्य offset
 * Use cm_अणुपढ़ो,ग_लिखोपूर्ण_mod_reg() with these रेजिस्टरs.
 * These रेजिस्टर offsets generally appear in more than one PRCM submodule.
 */

/* OMAP2-specअगरic रेजिस्टर offsets */

#घोषणा OMAP24XX_CM_FCLKEN2				0x0004
#घोषणा OMAP24XX_CM_ICLKEN4				0x001c
#घोषणा OMAP24XX_CM_AUTOIDLE4				0x003c
#घोषणा OMAP24XX_CM_IDLEST4				0x002c

/* CM_IDLEST bit field values to indicate deनिश्चितed IdleReq */

#घोषणा OMAP24XX_CM_IDLEST_VAL				0


/* Clock management करोमुख्य रेजिस्टर get/set */

#अगर_अघोषित __ASSEMBLER__

बाह्य व्योम omap2xxx_cm_set_dpll_disable_स्वतःidle(व्योम);
बाह्य व्योम omap2xxx_cm_set_dpll_स्वतः_low_घातer_stop(व्योम);

बाह्य व्योम omap2xxx_cm_set_apll54_disable_स्वतःidle(व्योम);
बाह्य व्योम omap2xxx_cm_set_apll54_स्वतः_low_घातer_stop(व्योम);
बाह्य व्योम omap2xxx_cm_set_apll96_disable_स्वतःidle(व्योम);
बाह्य व्योम omap2xxx_cm_set_apll96_स्वतः_low_घातer_stop(व्योम);

पूर्णांक omap2xxx_cm_रुको_module_पढ़ोy(u8 part, s16 prcm_mod, u16 idlest_id,
				  u8 idlest_shअगरt);
बाह्य पूर्णांक omap2xxx_cm_fclks_active(व्योम);
बाह्य पूर्णांक omap2xxx_cm_mpu_retention_allowed(व्योम);
बाह्य u32 omap2xxx_cm_get_core_clk_src(व्योम);
बाह्य u32 omap2xxx_cm_get_core_pll_config(व्योम);
बाह्य व्योम omap2xxx_cm_set_mod_भागiders(u32 mpu, u32 dsp, u32 gfx, u32 core,
					 u32 mdm);

पूर्णांक __init omap2xxx_cm_init(स्थिर काष्ठा omap_prcm_init_data *data);

#पूर्ण_अगर

#पूर्ण_अगर
