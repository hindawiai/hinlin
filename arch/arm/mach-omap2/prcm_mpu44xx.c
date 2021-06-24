<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP4 PRCM_MPU module functions
 *
 * Copyright (C) 2009 Nokia Corporation
 * Paul Walmsley
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>

#समावेश "iomap.h"
#समावेश "common.h"
#समावेश "prcm_mpu44xx.h"
#समावेश "cm-regbits-44xx.h"

/*
 * prcm_mpu_base: the भव address of the start of the PRCM_MPU IP
 *   block रेजिस्टरs
 */
काष्ठा omap_करोमुख्य_base prcm_mpu_base;

/* PRCM_MPU low-level functions */

u32 omap4_prcm_mpu_पढ़ो_inst_reg(s16 inst, u16 reg)
अणु
	वापस पढ़ोl_relaxed(OMAP44XX_PRCM_MPU_REGADDR(inst, reg));
पूर्ण

व्योम omap4_prcm_mpu_ग_लिखो_inst_reg(u32 val, s16 inst, u16 reg)
अणु
	ग_लिखोl_relaxed(val, OMAP44XX_PRCM_MPU_REGADDR(inst, reg));
पूर्ण

u32 omap4_prcm_mpu_rmw_inst_reg_bits(u32 mask, u32 bits, s16 inst, s16 reg)
अणु
	u32 v;

	v = omap4_prcm_mpu_पढ़ो_inst_reg(inst, reg);
	v &= ~mask;
	v |= bits;
	omap4_prcm_mpu_ग_लिखो_inst_reg(v, inst, reg);

	वापस v;
पूर्ण

/**
 * omap2_set_globals_prcm_mpu - set the MPU PRCM base address (क्रम early use)
 * @prcm_mpu: PRCM_MPU base भव address
 *
 * XXX Will be replaced when the PRM/CM drivers are completed.
 */
व्योम __init omap2_set_globals_prcm_mpu(व्योम __iomem *prcm_mpu)
अणु
	prcm_mpu_base.va = prcm_mpu;
पूर्ण
