<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP2xxx Power/Reset Management (PRM) रेजिस्टर definitions
 *
 * Copyright (C) 2007-2009, 2011-2012 Texas Instruments, Inc.
 * Copyright (C) 2008-2010 Nokia Corporation
 * Paul Walmsley
 *
 * The PRM hardware modules on the OMAP2/3 are quite similar to each
 * other.  The PRM on OMAP4 has a new रेजिस्टर layout, and is handled
 * in a separate file.
 */
#अगर_अघोषित __ARCH_ARM_MACH_OMAP2_PRM2XXX_H
#घोषणा __ARCH_ARM_MACH_OMAP2_PRM2XXX_H

#समावेश "prcm-common.h"
#समावेश "prm.h"
#समावेश "prm2xxx_3xxx.h"

#घोषणा OMAP2420_PRM_REGADDR(module, reg)				\
		OMAP2_L4_IO_ADDRESS(OMAP2420_PRM_BASE + (module) + (reg))
#घोषणा OMAP2430_PRM_REGADDR(module, reg)				\
		OMAP2_L4_IO_ADDRESS(OMAP2430_PRM_BASE + (module) + (reg))

/*
 * OMAP2-specअगरic global PRM रेजिस्टरs
 * Use अणुपढ़ो,ग_लिखोपूर्णl_relaxed() with these रेजिस्टरs.
 *
 * With a few exceptions, these are the रेजिस्टर names beginning with
 * PRCM_* on 24xx.  (The exceptions are the IRQSTATUS and IRQENABLE
 * bits.)
 *
 */

#घोषणा OMAP2_PRCM_REVISION_OFFSET	0x0000
#घोषणा OMAP2420_PRCM_REVISION		OMAP2420_PRM_REGADDR(OCP_MOD, 0x0000)
#घोषणा OMAP2_PRCM_SYSCONFIG_OFFSET	0x0010
#घोषणा OMAP2420_PRCM_SYSCONFIG		OMAP2420_PRM_REGADDR(OCP_MOD, 0x0010)

#घोषणा OMAP2_PRCM_IRQSTATUS_MPU_OFFSET	0x0018
#घोषणा OMAP2420_PRCM_IRQSTATUS_MPU	OMAP2420_PRM_REGADDR(OCP_MOD, 0x0018)
#घोषणा OMAP2_PRCM_IRQENABLE_MPU_OFFSET	0x001c
#घोषणा OMAP2420_PRCM_IRQENABLE_MPU	OMAP2420_PRM_REGADDR(OCP_MOD, 0x001c)

#घोषणा OMAP2_PRCM_VOLTCTRL_OFFSET	0x0050
#घोषणा OMAP2420_PRCM_VOLTCTRL		OMAP2420_PRM_REGADDR(OCP_MOD, 0x0050)
#घोषणा OMAP2_PRCM_VOLTST_OFFSET	0x0054
#घोषणा OMAP2420_PRCM_VOLTST		OMAP2420_PRM_REGADDR(OCP_MOD, 0x0054)
#घोषणा OMAP2_PRCM_CLKSRC_CTRL_OFFSET	0x0060
#घोषणा OMAP2420_PRCM_CLKSRC_CTRL	OMAP2420_PRM_REGADDR(OCP_MOD, 0x0060)
#घोषणा OMAP2_PRCM_CLKOUT_CTRL_OFFSET	0x0070
#घोषणा OMAP2420_PRCM_CLKOUT_CTRL	OMAP2420_PRM_REGADDR(OCP_MOD, 0x0070)
#घोषणा OMAP2_PRCM_CLKEMUL_CTRL_OFFSET	0x0078
#घोषणा OMAP2420_PRCM_CLKEMUL_CTRL	OMAP2420_PRM_REGADDR(OCP_MOD, 0x0078)
#घोषणा OMAP2_PRCM_CLKCFG_CTRL_OFFSET	0x0080
#घोषणा OMAP2420_PRCM_CLKCFG_CTRL	OMAP2420_PRM_REGADDR(OCP_MOD, 0x0080)
#घोषणा OMAP2_PRCM_CLKCFG_STATUS_OFFSET	0x0084
#घोषणा OMAP2420_PRCM_CLKCFG_STATUS	OMAP2420_PRM_REGADDR(OCP_MOD, 0x0084)
#घोषणा OMAP2_PRCM_VOLTSETUP_OFFSET	0x0090
#घोषणा OMAP2420_PRCM_VOLTSETUP		OMAP2420_PRM_REGADDR(OCP_MOD, 0x0090)
#घोषणा OMAP2_PRCM_CLKSSETUP_OFFSET	0x0094
#घोषणा OMAP2420_PRCM_CLKSSETUP		OMAP2420_PRM_REGADDR(OCP_MOD, 0x0094)
#घोषणा OMAP2_PRCM_POLCTRL_OFFSET	0x0098
#घोषणा OMAP2420_PRCM_POLCTRL		OMAP2420_PRM_REGADDR(OCP_MOD, 0x0098)

#घोषणा OMAP2430_PRCM_REVISION		OMAP2430_PRM_REGADDR(OCP_MOD, 0x0000)
#घोषणा OMAP2430_PRCM_SYSCONFIG		OMAP2430_PRM_REGADDR(OCP_MOD, 0x0010)

#घोषणा OMAP2430_PRCM_IRQSTATUS_MPU	OMAP2430_PRM_REGADDR(OCP_MOD, 0x0018)
#घोषणा OMAP2430_PRCM_IRQENABLE_MPU	OMAP2430_PRM_REGADDR(OCP_MOD, 0x001c)

#घोषणा OMAP2430_PRCM_VOLTCTRL		OMAP2430_PRM_REGADDR(OCP_MOD, 0x0050)
#घोषणा OMAP2430_PRCM_VOLTST		OMAP2430_PRM_REGADDR(OCP_MOD, 0x0054)
#घोषणा OMAP2430_PRCM_CLKSRC_CTRL	OMAP2430_PRM_REGADDR(OCP_MOD, 0x0060)
#घोषणा OMAP2430_PRCM_CLKOUT_CTRL	OMAP2430_PRM_REGADDR(OCP_MOD, 0x0070)
#घोषणा OMAP2430_PRCM_CLKEMUL_CTRL	OMAP2430_PRM_REGADDR(OCP_MOD, 0x0078)
#घोषणा OMAP2430_PRCM_CLKCFG_CTRL	OMAP2430_PRM_REGADDR(OCP_MOD, 0x0080)
#घोषणा OMAP2430_PRCM_CLKCFG_STATUS	OMAP2430_PRM_REGADDR(OCP_MOD, 0x0084)
#घोषणा OMAP2430_PRCM_VOLTSETUP		OMAP2430_PRM_REGADDR(OCP_MOD, 0x0090)
#घोषणा OMAP2430_PRCM_CLKSSETUP		OMAP2430_PRM_REGADDR(OCP_MOD, 0x0094)
#घोषणा OMAP2430_PRCM_POLCTRL		OMAP2430_PRM_REGADDR(OCP_MOD, 0x0098)

/*
 * Module specअगरic PRM रेजिस्टर offsets from PRM_BASE + करोमुख्य offset
 *
 * Use prm_अणुपढ़ो,ग_लिखोपूर्ण_mod_reg() with these रेजिस्टरs.
 *
 * With a few exceptions, these are the रेजिस्टर names beginning with
 * अणुPM,RMपूर्ण_* on both OMAP2/3 SoC families..  (The exceptions are the
 * IRQSTATUS and IRQENABLE bits.)
 */

/* Register offsets appearing on both OMAP2 and OMAP3 */

#घोषणा OMAP2_RM_RSTCTRL				0x0050
#घोषणा OMAP2_RM_RSTTIME				0x0054
#घोषणा OMAP2_RM_RSTST					0x0058
#घोषणा OMAP2_PM_PWSTCTRL				0x00e0
#घोषणा OMAP2_PM_PWSTST					0x00e4

#घोषणा PM_WKEN						0x00a0
#घोषणा PM_WKEN1					PM_WKEN
#घोषणा PM_WKST						0x00b0
#घोषणा PM_WKST1					PM_WKST
#घोषणा PM_WKDEP					0x00c8
#घोषणा PM_EVGENCTRL					0x00d4
#घोषणा PM_EVGENONTIM					0x00d8
#घोषणा PM_EVGENOFFTIM					0x00dc

/* OMAP2xxx specअगरic रेजिस्टर offsets */
#घोषणा OMAP24XX_PM_WKEN2				0x00a4
#घोषणा OMAP24XX_PM_WKST2				0x00b4

#घोषणा OMAP24XX_PRCM_IRQSTATUS_DSP			0x00f0	/* IVA mod */
#घोषणा OMAP24XX_PRCM_IRQENABLE_DSP			0x00f4	/* IVA mod */
#घोषणा OMAP24XX_PRCM_IRQSTATUS_IVA			0x00f8
#घोषणा OMAP24XX_PRCM_IRQENABLE_IVA			0x00fc

#अगर_अघोषित __ASSEMBLER__
/* Function prototypes */
बाह्य पूर्णांक omap2xxx_clkdm_sleep(काष्ठा घड़ीकरोमुख्य *clkdm);
बाह्य पूर्णांक omap2xxx_clkdm_wakeup(काष्ठा घड़ीकरोमुख्य *clkdm);

पूर्णांक __init omap2xxx_prm_init(स्थिर काष्ठा omap_prcm_init_data *data);

#पूर्ण_अगर

#पूर्ण_अगर
