<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2009-2010, 2012 Freescale Semiconductor, Inc.
 *
 * QorIQ (P1/P2) L2 controller init क्रम Cache-SRAM instantiation
 *
 * Author: Vivek Mahajan <vivek.mahajan@मुक्तscale.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/पन.स>

#समावेश "fsl_85xx_cache_ctlr.h"

अटल अक्षर *sram_size;
अटल अक्षर *sram_offset;
काष्ठा mpc85xx_l2ctlr __iomem *l2ctlr;

अटल पूर्णांक get_cache_sram_params(काष्ठा sram_parameters *sram_params)
अणु
	अचिन्हित दीर्घ दीर्घ addr;
	अचिन्हित पूर्णांक size;

	अगर (!sram_size || (kstrtouपूर्णांक(sram_size, 0, &size) < 0))
		वापस -EINVAL;

	अगर (!sram_offset || (kम_से_अदीर्घl(sram_offset, 0, &addr) < 0))
		वापस -EINVAL;

	sram_params->sram_offset = addr;
	sram_params->sram_size = size;

	वापस 0;
पूर्ण

अटल पूर्णांक __init get_size_from_cmdline(अक्षर *str)
अणु
	अगर (!str)
		वापस 0;

	sram_size = str;
	वापस 1;
पूर्ण

अटल पूर्णांक __init get_offset_from_cmdline(अक्षर *str)
अणु
	अगर (!str)
		वापस 0;

	sram_offset = str;
	वापस 1;
पूर्ण

__setup("cache-sram-size=", get_size_from_cmdline);
__setup("cache-sram-offset=", get_offset_from_cmdline);

अटल पूर्णांक mpc85xx_l2ctlr_of_probe(काष्ठा platक्रमm_device *dev)
अणु
	दीर्घ rval;
	अचिन्हित पूर्णांक rem;
	अचिन्हित अक्षर ways;
	स्थिर अचिन्हित पूर्णांक *prop;
	अचिन्हित पूर्णांक l2cache_size;
	काष्ठा sram_parameters sram_params;

	अगर (!dev->dev.of_node) अणु
		dev_err(&dev->dev, "Device's OF-node is NULL\n");
		वापस -EINVAL;
	पूर्ण

	prop = of_get_property(dev->dev.of_node, "cache-size", शून्य);
	अगर (!prop) अणु
		dev_err(&dev->dev, "Missing L2 cache-size\n");
		वापस -EINVAL;
	पूर्ण
	l2cache_size = *prop;

	अगर (get_cache_sram_params(&sram_params))
		वापस 0; /* fall back to L2 cache only */

	rem = l2cache_size % sram_params.sram_size;
	ways = LOCK_WAYS_FULL * sram_params.sram_size / l2cache_size;
	अगर (rem || (ways & (ways - 1))) अणु
		dev_err(&dev->dev, "Illegal cache-sram-size in command line\n");
		वापस -EINVAL;
	पूर्ण

	l2ctlr = of_iomap(dev->dev.of_node, 0);
	अगर (!l2ctlr) अणु
		dev_err(&dev->dev, "Can't map L2 controller\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Write bits[0-17] to srbar0
	 */
	out_be32(&l2ctlr->srbar0,
		lower_32_bits(sram_params.sram_offset) & L2SRAM_BAR_MSK_LO18);

	/*
	 * Write bits[18-21] to srbare0
	 */
#अगर_घोषित CONFIG_PHYS_64BIT
	out_be32(&l2ctlr->srbarea0,
		upper_32_bits(sram_params.sram_offset) & L2SRAM_BARE_MSK_HI4);
#पूर्ण_अगर

	clrsetbits_be32(&l2ctlr->ctl, L2CR_L2E, L2CR_L2FI);

	चयन (ways) अणु
	हाल LOCK_WAYS_EIGHTH:
		setbits32(&l2ctlr->ctl,
			L2CR_L2E | L2CR_L2FI | L2CR_SRAM_EIGHTH);
		अवरोध;

	हाल LOCK_WAYS_TWO_EIGHTH:
		setbits32(&l2ctlr->ctl,
			L2CR_L2E | L2CR_L2FI | L2CR_SRAM_QUART);
		अवरोध;

	हाल LOCK_WAYS_HALF:
		setbits32(&l2ctlr->ctl,
			L2CR_L2E | L2CR_L2FI | L2CR_SRAM_HALF);
		अवरोध;

	हाल LOCK_WAYS_FULL:
	शेष:
		setbits32(&l2ctlr->ctl,
			L2CR_L2E | L2CR_L2FI | L2CR_SRAM_FULL);
		अवरोध;
	पूर्ण
	eieio();

	rval = instantiate_cache_sram(dev, sram_params);
	अगर (rval < 0) अणु
		dev_err(&dev->dev, "Can't instantiate Cache-SRAM\n");
		iounmap(l2ctlr);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mpc85xx_l2ctlr_of_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	BUG_ON(!l2ctlr);

	iounmap(l2ctlr);
	हटाओ_cache_sram(dev);
	dev_info(&dev->dev, "MPC85xx L2 controller unloaded\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mpc85xx_l2ctlr_of_match[] = अणु
	अणु
		.compatible = "fsl,p2020-l2-cache-controller",
	पूर्ण,
	अणु
		.compatible = "fsl,p2010-l2-cache-controller",
	पूर्ण,
	अणु
		.compatible = "fsl,p1020-l2-cache-controller",
	पूर्ण,
	अणु
		.compatible = "fsl,p1011-l2-cache-controller",
	पूर्ण,
	अणु
		.compatible = "fsl,p1013-l2-cache-controller",
	पूर्ण,
	अणु
		.compatible = "fsl,p1022-l2-cache-controller",
	पूर्ण,
	अणु
		.compatible = "fsl,mpc8548-l2-cache-controller",
	पूर्ण,
	अणु	.compatible = "fsl,mpc8544-l2-cache-controller",पूर्ण,
	अणु	.compatible = "fsl,mpc8572-l2-cache-controller",पूर्ण,
	अणु	.compatible = "fsl,mpc8536-l2-cache-controller",पूर्ण,
	अणु	.compatible = "fsl,p1021-l2-cache-controller",पूर्ण,
	अणु	.compatible = "fsl,p1012-l2-cache-controller",पूर्ण,
	अणु	.compatible = "fsl,p1025-l2-cache-controller",पूर्ण,
	अणु	.compatible = "fsl,p1016-l2-cache-controller",पूर्ण,
	अणु	.compatible = "fsl,p1024-l2-cache-controller",पूर्ण,
	अणु	.compatible = "fsl,p1015-l2-cache-controller",पूर्ण,
	अणु	.compatible = "fsl,p1010-l2-cache-controller",पूर्ण,
	अणु	.compatible = "fsl,bsc9131-l2-cache-controller",पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver mpc85xx_l2ctlr_of_platक्रमm_driver = अणु
	.driver	= अणु
		.name		= "fsl-l2ctlr",
		.of_match_table	= mpc85xx_l2ctlr_of_match,
	पूर्ण,
	.probe		= mpc85xx_l2ctlr_of_probe,
	.हटाओ		= mpc85xx_l2ctlr_of_हटाओ,
पूर्ण;

अटल __init पूर्णांक mpc85xx_l2ctlr_of_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&mpc85xx_l2ctlr_of_platक्रमm_driver);
पूर्ण

अटल व्योम __निकास mpc85xx_l2ctlr_of_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&mpc85xx_l2ctlr_of_platक्रमm_driver);
पूर्ण

subsys_initcall(mpc85xx_l2ctlr_of_init);
module_निकास(mpc85xx_l2ctlr_of_निकास);

MODULE_DESCRIPTION("Freescale MPC85xx L2 controller init");
MODULE_LICENSE("GPL v2");
