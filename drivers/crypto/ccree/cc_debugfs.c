<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2012-2019 ARM Limited or its affiliates. */

#समावेश <linux/kernel.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/stringअगरy.h>
#समावेश "cc_driver.h"
#समावेश "cc_crypto_ctx.h"
#समावेश "cc_debugfs.h"

#घोषणा CC_DEBUG_REG(_X) अणु	\
	.name = __stringअगरy(_X),\
	.offset = CC_REG(_X)	\
	पूर्ण

/*
 * This is a global var क्रम the dentry of the
 * debugfs ccree/ dir. It is not tied करोwn to
 * a specअगरic instance of ccree, hence it is
 * global.
 */
अटल काष्ठा dentry *cc_debugfs_dir;

अटल काष्ठा debugfs_reg32 ver_sig_regs[] = अणु
	अणु .name = "SIGNATURE" पूर्ण, /* Must be 0th */
	अणु .name = "VERSION" पूर्ण, /* Must be 1st */
पूर्ण;

अटल स्थिर काष्ठा debugfs_reg32 pid_cid_regs[] = अणु
	CC_DEBUG_REG(PERIPHERAL_ID_0),
	CC_DEBUG_REG(PERIPHERAL_ID_1),
	CC_DEBUG_REG(PERIPHERAL_ID_2),
	CC_DEBUG_REG(PERIPHERAL_ID_3),
	CC_DEBUG_REG(PERIPHERAL_ID_4),
	CC_DEBUG_REG(COMPONENT_ID_0),
	CC_DEBUG_REG(COMPONENT_ID_1),
	CC_DEBUG_REG(COMPONENT_ID_2),
	CC_DEBUG_REG(COMPONENT_ID_3),
पूर्ण;

अटल स्थिर काष्ठा debugfs_reg32 debug_regs[] = अणु
	CC_DEBUG_REG(HOST_IRR),
	CC_DEBUG_REG(HOST_POWER_DOWN_EN),
	CC_DEBUG_REG(AXIM_MON_ERR),
	CC_DEBUG_REG(DSCRPTR_QUEUE_CONTENT),
	CC_DEBUG_REG(HOST_IMR),
	CC_DEBUG_REG(AXIM_CFG),
	CC_DEBUG_REG(AXIM_CACHE_PARAMS),
	CC_DEBUG_REG(GPR_HOST),
	CC_DEBUG_REG(AXIM_MON_COMP),
पूर्ण;

व्योम __init cc_debugfs_global_init(व्योम)
अणु
	cc_debugfs_dir = debugfs_create_dir("ccree", शून्य);
पूर्ण

व्योम __निकास cc_debugfs_global_fini(व्योम)
अणु
	debugfs_हटाओ(cc_debugfs_dir);
पूर्ण

पूर्णांक cc_debugfs_init(काष्ठा cc_drvdata *drvdata)
अणु
	काष्ठा device *dev = drvdata_to_dev(drvdata);
	काष्ठा debugfs_regset32 *regset, *verset;

	regset = devm_kzalloc(dev, माप(*regset), GFP_KERNEL);
	अगर (!regset)
		वापस -ENOMEM;

	regset->regs = debug_regs;
	regset->nregs = ARRAY_SIZE(debug_regs);
	regset->base = drvdata->cc_base;
	regset->dev = dev;

	drvdata->dir = debugfs_create_dir(drvdata->plat_dev->name,
					  cc_debugfs_dir);

	debugfs_create_regset32("regs", 0400, drvdata->dir, regset);
	debugfs_create_bool("coherent", 0400, drvdata->dir, &drvdata->coherent);

	verset = devm_kzalloc(dev, माप(*verset), GFP_KERNEL);
	/* Failing here is not important enough to fail the module load */
	अगर (!verset)
		वापस 0;

	अगर (drvdata->hw_rev <= CC_HW_REV_712) अणु
		ver_sig_regs[0].offset = drvdata->sig_offset;
		ver_sig_regs[1].offset = drvdata->ver_offset;
		verset->regs = ver_sig_regs;
		verset->nregs = ARRAY_SIZE(ver_sig_regs);
	पूर्ण अन्यथा अणु
		verset->regs = pid_cid_regs;
		verset->nregs = ARRAY_SIZE(pid_cid_regs);
	पूर्ण
	verset->base = drvdata->cc_base;
	verset->dev = dev;

	debugfs_create_regset32("version", 0400, drvdata->dir, verset);
	वापस 0;
पूर्ण

व्योम cc_debugfs_fini(काष्ठा cc_drvdata *drvdata)
अणु
	debugfs_हटाओ_recursive(drvdata->dir);
पूर्ण
