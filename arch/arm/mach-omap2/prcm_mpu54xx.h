<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP54xx PRCM MPU instance offset macros
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - https://www.ti.com
 *
 * Paul Walmsley (paul@pwsan.com)
 * Rajendra Nayak (rnayak@ti.com)
 * Benoit Cousson (b-cousson@ti.com)
 *
 * This file is स्वतःmatically generated from the OMAP hardware databases.
 * We respectfully ask that any modअगरications to this file be coordinated
 * with the खुला linux-omap@vger.kernel.org mailing list and the
 * authors above to ensure that the स्वतःgeneration scripts are kept
 * up-to-date with the file contents.
 */

#अगर_अघोषित __ARCH_ARM_MACH_OMAP2_PRCM_MPU54XX_H
#घोषणा __ARCH_ARM_MACH_OMAP2_PRCM_MPU54XX_H

#समावेश "prcm_mpu_44xx_54xx.h"
#समावेश "common.h"

#घोषणा OMAP54XX_PRCM_MPU_BASE			0x48243000

#घोषणा OMAP54XX_PRCM_MPU_REGADDR(inst, reg)				\
	OMAP2_L4_IO_ADDRESS(OMAP54XX_PRCM_MPU_BASE + (inst) + (reg))

/* PRCM_MPU instances */
#घोषणा OMAP54XX_PRCM_MPU_OCP_SOCKET_INST	0x0000
#घोषणा OMAP54XX_PRCM_MPU_DEVICE_INST		0x0200
#घोषणा OMAP54XX_PRCM_MPU_PRM_C0_INST		0x0400
#घोषणा OMAP54XX_PRCM_MPU_CM_C0_INST		0x0600
#घोषणा OMAP54XX_PRCM_MPU_PRM_C1_INST		0x0800
#घोषणा OMAP54XX_PRCM_MPU_CM_C1_INST		0x0a00

/* PRCM_MPU घड़ीकरोमुख्य रेजिस्टर offsets (from instance start) */
#घोषणा OMAP54XX_PRCM_MPU_CM_C0_CPU0_CDOFFS	0x0000
#घोषणा OMAP54XX_PRCM_MPU_CM_C1_CPU1_CDOFFS	0x0000


/*
 * PRCM_MPU
 *
 * The PRCM_MPU is a local PRCM inside the MPU subप्रणाली. For the PRCM (global)
 * poपूर्णांक of view the PRCM_MPU is a single entity. It shares the same
 * programming model as the global PRCM and thus can be assimilate as two new
 * MOD inside the PRCM
 */

/* PRCM_MPU.PRCM_MPU_OCP_SOCKET रेजिस्टर offsets */
#घोषणा OMAP54XX_REVISION_PRCM_MPU_OFFSET			0x0000

/* PRCM_MPU.PRCM_MPU_DEVICE रेजिस्टर offsets */
#घोषणा OMAP54XX_PRCM_MPU_PRM_RSTST_OFFSET			0x0000
#घोषणा OMAP54XX_PRCM_MPU_PRM_PSCON_COUNT_OFFSET		0x0004
#घोषणा OMAP54XX_PRM_FRAC_INCREMENTER_NUMERATOR_OFFSET		0x0010
#घोषणा OMAP54XX_PRM_FRAC_INCREMENTER_DENUMERATOR_RELOAD_OFFSET	0x0014

/* PRCM_MPU.PRCM_MPU_PRM_C0 रेजिस्टर offsets */
#घोषणा OMAP54XX_PM_CPU0_PWRSTCTRL_OFFSET			0x0000
#घोषणा OMAP54XX_PM_CPU0_PWRSTST_OFFSET				0x0004
#घोषणा OMAP54XX_RM_CPU0_CPU0_RSTCTRL_OFFSET			0x0010
#घोषणा OMAP54XX_RM_CPU0_CPU0_RSTST_OFFSET			0x0014
#घोषणा OMAP54XX_RM_CPU0_CPU0_CONTEXT_OFFSET			0x0024

/* PRCM_MPU.PRCM_MPU_CM_C0 रेजिस्टर offsets */
#घोषणा OMAP54XX_CM_CPU0_CLKSTCTRL_OFFSET			0x0000
#घोषणा OMAP54XX_CM_CPU0_CPU0_CLKCTRL_OFFSET			0x0020
#घोषणा OMAP54XX_CM_CPU0_CPU0_CLKCTRL				OMAP54XX_PRCM_MPU_REGADDR(OMAP54XX_PRCM_MPU_CM_C0_INST, 0x0020)

/* PRCM_MPU.PRCM_MPU_PRM_C1 रेजिस्टर offsets */
#घोषणा OMAP54XX_PM_CPU1_PWRSTCTRL_OFFSET			0x0000
#घोषणा OMAP54XX_PM_CPU1_PWRSTST_OFFSET				0x0004
#घोषणा OMAP54XX_RM_CPU1_CPU1_RSTCTRL_OFFSET			0x0010
#घोषणा OMAP54XX_RM_CPU1_CPU1_RSTST_OFFSET			0x0014
#घोषणा OMAP54XX_RM_CPU1_CPU1_CONTEXT_OFFSET			0x0024

/* PRCM_MPU.PRCM_MPU_CM_C1 रेजिस्टर offsets */
#घोषणा OMAP54XX_CM_CPU1_CLKSTCTRL_OFFSET			0x0000
#घोषणा OMAP54XX_CM_CPU1_CPU1_CLKCTRL_OFFSET			0x0020
#घोषणा OMAP54XX_CM_CPU1_CPU1_CLKCTRL				OMAP54XX_PRCM_MPU_REGADDR(OMAP54XX_PRCM_MPU_CM_C1_INST, 0x0020)

#पूर्ण_अगर
