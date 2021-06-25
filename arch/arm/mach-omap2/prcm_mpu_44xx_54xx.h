<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP44xx and OMAP54xx PRCM MPU function prototypes
 *
 * Copyright (C) 2010, 2013 Texas Instruments, Inc.
 * Copyright (C) 2010 Nokia Corporation
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

#अगर_अघोषित __ARCH_ARM_MACH_OMAP2_PRCM_MPU_44XX_54XX_H
#घोषणा __ARCH_ARM_MACH_OMAP2_PRCM_MPU_44XX_54XX_H

#अगर_अघोषित __ASSEMBLER__
#समावेश "prcm-common.h"

बाह्य काष्ठा omap_करोमुख्य_base prcm_mpu_base;

बाह्य u32 omap4_prcm_mpu_पढ़ो_inst_reg(s16 inst, u16 idx);
बाह्य व्योम omap4_prcm_mpu_ग_लिखो_inst_reg(u32 val, s16 inst, u16 idx);
बाह्य u32 omap4_prcm_mpu_rmw_inst_reg_bits(u32 mask, u32 bits, s16 inst,
					    s16 idx);
बाह्य व्योम __init omap2_set_globals_prcm_mpu(व्योम __iomem *prcm_mpu);
#पूर्ण_अगर

#पूर्ण_अगर
