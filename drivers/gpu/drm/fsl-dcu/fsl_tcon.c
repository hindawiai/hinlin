<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015 Toradex AG
 *
 * Stefan Agner <stefan@agner.ch>
 *
 * Freescale TCON device driver
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश "fsl_tcon.h"

व्योम fsl_tcon_bypass_disable(काष्ठा fsl_tcon *tcon)
अणु
	regmap_update_bits(tcon->regs, FSL_TCON_CTRL1,
			   FSL_TCON_CTRL1_TCON_BYPASS, 0);
पूर्ण

व्योम fsl_tcon_bypass_enable(काष्ठा fsl_tcon *tcon)
अणु
	regmap_update_bits(tcon->regs, FSL_TCON_CTRL1,
			   FSL_TCON_CTRL1_TCON_BYPASS,
			   FSL_TCON_CTRL1_TCON_BYPASS);
पूर्ण

अटल काष्ठा regmap_config fsl_tcon_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,

	.name = "tcon",
पूर्ण;

अटल पूर्णांक fsl_tcon_init_regmap(काष्ठा device *dev,
				काष्ठा fsl_tcon *tcon,
				काष्ठा device_node *np)
अणु
	काष्ठा resource res;
	व्योम __iomem *regs;

	अगर (of_address_to_resource(np, 0, &res))
		वापस -EINVAL;

	regs = devm_ioremap_resource(dev, &res);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	tcon->regs = devm_regmap_init_mmio(dev, regs,
					   &fsl_tcon_regmap_config);
	वापस PTR_ERR_OR_ZERO(tcon->regs);
पूर्ण

काष्ठा fsl_tcon *fsl_tcon_init(काष्ठा device *dev)
अणु
	काष्ठा fsl_tcon *tcon;
	काष्ठा device_node *np;
	पूर्णांक ret;

	/* TCON node is not mandatory, some devices करो not provide TCON */
	np = of_parse_phandle(dev->of_node, "fsl,tcon", 0);
	अगर (!np)
		वापस शून्य;

	tcon = devm_kzalloc(dev, माप(*tcon), GFP_KERNEL);
	अगर (!tcon)
		जाओ err_node_put;

	ret = fsl_tcon_init_regmap(dev, tcon, np);
	अगर (ret) अणु
		dev_err(dev, "Couldn't create the TCON regmap\n");
		जाओ err_node_put;
	पूर्ण

	tcon->ipg_clk = of_clk_get_by_name(np, "ipg");
	अगर (IS_ERR(tcon->ipg_clk)) अणु
		dev_err(dev, "Couldn't get the TCON bus clock\n");
		जाओ err_node_put;
	पूर्ण

	ret = clk_prepare_enable(tcon->ipg_clk);
	अगर (ret) अणु
		dev_err(dev, "Couldn't enable the TCON clock\n");
		जाओ err_node_put;
	पूर्ण

	of_node_put(np);
	dev_info(dev, "Using TCON in bypass mode\n");

	वापस tcon;

err_node_put:
	of_node_put(np);
	वापस शून्य;
पूर्ण

व्योम fsl_tcon_मुक्त(काष्ठा fsl_tcon *tcon)
अणु
	clk_disable_unprepare(tcon->ipg_clk);
	clk_put(tcon->ipg_clk);
पूर्ण

