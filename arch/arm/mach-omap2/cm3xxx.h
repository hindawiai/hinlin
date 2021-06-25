<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP2/3 Clock Management (CM) रेजिस्टर definitions
 *
 * Copyright (C) 2007-2009 Texas Instruments, Inc.
 * Copyright (C) 2007-2010 Nokia Corporation
 * Paul Walmsley
 *
 * The CM hardware modules on the OMAP2/3 are quite similar to each
 * other.  The CM modules/instances on OMAP4 are quite dअगरferent, so
 * they are handled in a separate file.
 */
#अगर_अघोषित __ARCH_ASM_MACH_OMAP2_CM3XXX_H
#घोषणा __ARCH_ASM_MACH_OMAP2_CM3XXX_H

#समावेश "prcm-common.h"
#समावेश "cm2xxx_3xxx.h"

#घोषणा OMAP34XX_CM_REGADDR(module, reg)				\
			OMAP2_L4_IO_ADDRESS(OMAP3430_CM_BASE + (module) + (reg))


/*
 * OMAP3-specअगरic global CM रेजिस्टरs
 * Use cm_अणुपढ़ो,ग_लिखोपूर्ण_reg() with these रेजिस्टरs.
 * These रेजिस्टरs appear once per CM module.
 */

#घोषणा OMAP3430_CM_SYSCONFIG		0x0010
#घोषणा OMAP3430_CM_POLCTRL		0x009c

#घोषणा OMAP3_CM_CLKOUT_CTRL_OFFSET	0x0070
#घोषणा OMAP3430_CM_CLKOUT_CTRL		OMAP_CM_REGADDR(OMAP3430_CCR_MOD, 0x0070)

/*
 * Module specअगरic CM रेजिस्टर offsets from CM_BASE + करोमुख्य offset
 * Use cm_अणुपढ़ो,ग_लिखोपूर्ण_mod_reg() with these रेजिस्टरs.
 * These रेजिस्टर offsets generally appear in more than one PRCM submodule.
 */

/* OMAP3-specअगरic रेजिस्टर offsets */

#घोषणा OMAP3430_CM_CLKEN_PLL				0x0004
#घोषणा OMAP3430ES2_CM_CLKEN2				0x0004
#घोषणा OMAP3430ES2_CM_FCLKEN3				0x0008
#घोषणा OMAP3430_CM_IDLEST_PLL				CM_IDLEST2
#घोषणा OMAP3430_CM_AUTOIDLE_PLL			CM_AUTOIDLE2
#घोषणा OMAP3430ES2_CM_AUTOIDLE2_PLL			CM_AUTOIDLE2
#घोषणा OMAP3430_CM_CLKSEL1				CM_CLKSEL
#घोषणा OMAP3430_CM_CLKSEL1_PLL				CM_CLKSEL
#घोषणा OMAP3430_CM_CLKSEL2_PLL				CM_CLKSEL2
#घोषणा OMAP3430_CM_SLEEPDEP				CM_CLKSEL2
#घोषणा OMAP3430_CM_CLKSEL3				OMAP2_CM_CLKSTCTRL
#घोषणा OMAP3430_CM_CLKSTST				0x004c
#घोषणा OMAP3430ES2_CM_CLKSEL4				0x004c
#घोषणा OMAP3430ES2_CM_CLKSEL5				0x0050
#घोषणा OMAP3430_CM_CLKSEL2_EMU				0x0050
#घोषणा OMAP3430_CM_CLKSEL3_EMU				0x0054


/* CM_IDLEST bit field values to indicate deनिश्चितed IdleReq */

#घोषणा OMAP34XX_CM_IDLEST_VAL				1


#अगर_अघोषित __ASSEMBLER__

बाह्य व्योम omap3_cm_save_context(व्योम);
बाह्य व्योम omap3_cm_restore_context(व्योम);
बाह्य व्योम omap3_cm_save_scratchpad_contents(u32 *ptr);

पूर्णांक __init omap3xxx_cm_init(स्थिर काष्ठा omap_prcm_init_data *data);

#पूर्ण_अगर

#पूर्ण_अगर
