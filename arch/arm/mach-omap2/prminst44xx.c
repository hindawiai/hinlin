<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP4 PRM instance functions
 *
 * Copyright (C) 2009 Nokia Corporation
 * Copyright (C) 2011 Texas Instruments, Inc.
 * Paul Walmsley
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>

#समावेश "iomap.h"
#समावेश "common.h"
#समावेश "prcm-common.h"
#समावेश "prm44xx.h"
#समावेश "prm54xx.h"
#समावेश "prm7xx.h"
#समावेश "prminst44xx.h"
#समावेश "prm-regbits-44xx.h"
#समावेश "prcm44xx.h"
#समावेश "prcm43xx.h"
#समावेश "prcm_mpu44xx.h"
#समावेश "soc.h"

अटल काष्ठा omap_करोमुख्य_base _prm_bases[OMAP4_MAX_PRCM_PARTITIONS];

अटल s32 prm_dev_inst = PRM_INSTANCE_UNKNOWN;

/**
 * omap_prm_base_init - Populates the prm partitions
 *
 * Populates the base addresses of the _prm_bases
 * array used क्रम पढ़ो/ग_लिखो of prm module रेजिस्टरs.
 */
व्योम omap_prm_base_init(व्योम)
अणु
	स_नकल(&_prm_bases[OMAP4430_PRM_PARTITION], &prm_base,
	       माप(prm_base));
	स_नकल(&_prm_bases[OMAP4430_PRCM_MPU_PARTITION], &prcm_mpu_base,
	       माप(prcm_mpu_base));
पूर्ण

s32 omap4_prmst_get_prm_dev_inst(व्योम)
अणु
	वापस prm_dev_inst;
पूर्ण

व्योम omap4_prminst_set_prm_dev_inst(s32 dev_inst)
अणु
	prm_dev_inst = dev_inst;
पूर्ण

/* Read a रेजिस्टर in a PRM instance */
u32 omap4_prminst_पढ़ो_inst_reg(u8 part, s16 inst, u16 idx)
अणु
	BUG_ON(part >= OMAP4_MAX_PRCM_PARTITIONS ||
	       part == OMAP4430_INVALID_PRCM_PARTITION ||
	       !_prm_bases[part].va);
	वापस पढ़ोl_relaxed(_prm_bases[part].va + inst + idx);
पूर्ण

/* Write पूर्णांकo a रेजिस्टर in a PRM instance */
व्योम omap4_prminst_ग_लिखो_inst_reg(u32 val, u8 part, s16 inst, u16 idx)
अणु
	BUG_ON(part >= OMAP4_MAX_PRCM_PARTITIONS ||
	       part == OMAP4430_INVALID_PRCM_PARTITION ||
	       !_prm_bases[part].va);
	ग_लिखोl_relaxed(val, _prm_bases[part].va + inst + idx);
पूर्ण

/* Read-modअगरy-ग_लिखो a रेजिस्टर in PRM. Caller must lock */
u32 omap4_prminst_rmw_inst_reg_bits(u32 mask, u32 bits, u8 part, s16 inst,
				    u16 idx)
अणु
	u32 v;

	v = omap4_prminst_पढ़ो_inst_reg(part, inst, idx);
	v &= ~mask;
	v |= bits;
	omap4_prminst_ग_लिखो_inst_reg(v, part, inst, idx);

	वापस v;
पूर्ण

/**
 * omap4_prminst_is_hardreset_निश्चितed - पढ़ो the HW reset line state of
 * submodules contained in the hwmod module
 * @rstctrl_reg: RM_RSTCTRL रेजिस्टर address क्रम this module
 * @shअगरt: रेजिस्टर bit shअगरt corresponding to the reset line to check
 *
 * Returns 1 अगर the (sub)module hardreset line is currently निश्चितed,
 * 0 अगर the (sub)module hardreset line is not currently निश्चितed, or
 * -EINVAL upon parameter error.
 */
पूर्णांक omap4_prminst_is_hardreset_निश्चितed(u8 shअगरt, u8 part, s16 inst,
					u16 rstctrl_offs)
अणु
	u32 v;

	v = omap4_prminst_पढ़ो_inst_reg(part, inst, rstctrl_offs);
	v &= 1 << shअगरt;
	v >>= shअगरt;

	वापस v;
पूर्ण

/**
 * omap4_prminst_निश्चित_hardreset - निश्चित the HW reset line of a submodule
 * @rstctrl_reg: RM_RSTCTRL रेजिस्टर address क्रम this module
 * @shअगरt: रेजिस्टर bit shअगरt corresponding to the reset line to निश्चित
 *
 * Some IPs like dsp, ipu or iva contain processors that require an HW
 * reset line to be निश्चितed / deनिश्चितed in order to fully enable the
 * IP.  These modules may have multiple hard-reset lines that reset
 * dअगरferent 'submodules' inside the IP block.  This function will
 * place the submodule पूर्णांकo reset.  Returns 0 upon success or -EINVAL
 * upon an argument error.
 */
पूर्णांक omap4_prminst_निश्चित_hardreset(u8 shअगरt, u8 part, s16 inst,
				   u16 rstctrl_offs)
अणु
	u32 mask = 1 << shअगरt;

	omap4_prminst_rmw_inst_reg_bits(mask, mask, part, inst, rstctrl_offs);

	वापस 0;
पूर्ण

/**
 * omap4_prminst_deनिश्चित_hardreset - deनिश्चित a submodule hardreset line and
 * रुको
 * @shअगरt: रेजिस्टर bit shअगरt corresponding to the reset line to deनिश्चित
 * @st_shअगरt: status bit offset corresponding to the reset line
 * @part: PRM partition
 * @inst: PRM instance offset
 * @rstctrl_offs: reset रेजिस्टर offset
 * @rstst_offs: reset status रेजिस्टर offset
 *
 * Some IPs like dsp, ipu or iva contain processors that require an HW
 * reset line to be निश्चितed / deनिश्चितed in order to fully enable the
 * IP.  These modules may have multiple hard-reset lines that reset
 * dअगरferent 'submodules' inside the IP block.  This function will
 * take the submodule out of reset and रुको until the PRCM indicates
 * that the reset has completed beक्रमe वापसing.  Returns 0 upon success or
 * -EINVAL upon an argument error, -EEXIST अगर the submodule was alपढ़ोy out
 * of reset, or -EBUSY अगर the submodule did not निकास reset promptly.
 */
पूर्णांक omap4_prminst_deनिश्चित_hardreset(u8 shअगरt, u8 st_shअगरt, u8 part, s16 inst,
				     u16 rstctrl_offs, u16 rstst_offs)
अणु
	पूर्णांक c;
	u32 mask = 1 << shअगरt;
	u32 st_mask = 1 << st_shअगरt;

	/* Check the current status to aव्योम de-निश्चितing the line twice */
	अगर (omap4_prminst_is_hardreset_निश्चितed(shअगरt, part, inst,
						rstctrl_offs) == 0)
		वापस -EEXIST;

	/* Clear the reset status by writing 1 to the status bit */
	omap4_prminst_rmw_inst_reg_bits(0xffffffff, st_mask, part, inst,
					rstst_offs);
	/* de-निश्चित the reset control line */
	omap4_prminst_rmw_inst_reg_bits(mask, 0, part, inst, rstctrl_offs);
	/* रुको the status to be set */
	omap_test_समयout(omap4_prminst_is_hardreset_निश्चितed(st_shअगरt, part,
							      inst, rstst_offs),
			  MAX_MODULE_HARDRESET_WAIT, c);

	वापस (c == MAX_MODULE_HARDRESET_WAIT) ? -EBUSY : 0;
पूर्ण


व्योम omap4_prminst_global_warm_sw_reset(व्योम)
अणु
	u32 v;
	s32 inst = omap4_prmst_get_prm_dev_inst();

	अगर (inst == PRM_INSTANCE_UNKNOWN)
		वापस;

	v = omap4_prminst_पढ़ो_inst_reg(OMAP4430_PRM_PARTITION, inst,
					OMAP4_PRM_RSTCTRL_OFFSET);
	v |= OMAP4430_RST_GLOBAL_WARM_SW_MASK;
	omap4_prminst_ग_लिखो_inst_reg(v, OMAP4430_PRM_PARTITION,
				 inst, OMAP4_PRM_RSTCTRL_OFFSET);

	/* OCP barrier */
	v = omap4_prminst_पढ़ो_inst_reg(OMAP4430_PRM_PARTITION,
				    inst, OMAP4_PRM_RSTCTRL_OFFSET);
पूर्ण
