<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Free Electrons
 *
 * Author: Boris BREZILLON <boris.brezillon@मुक्त-electrons.com>
 *
 * Allwinner A31 AR100 घड़ी driver
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>

#समावेश "clk-factors.h"

/*
 * sun6i_get_ar100_factors - Calculates factors p, m क्रम AR100
 *
 * AR100 rate is calculated as follows
 * rate = (parent_rate >> p) / (m + 1);
 */
अटल व्योम sun6i_get_ar100_factors(काष्ठा factors_request *req)
अणु
	अचिन्हित दीर्घ भाग;
	पूर्णांक shअगरt;

	/* घड़ी only भागides */
	अगर (req->rate > req->parent_rate)
		req->rate = req->parent_rate;

	भाग = DIV_ROUND_UP(req->parent_rate, req->rate);

	अगर (भाग < 32)
		shअगरt = 0;
	अन्यथा अगर (भाग >> 1 < 32)
		shअगरt = 1;
	अन्यथा अगर (भाग >> 2 < 32)
		shअगरt = 2;
	अन्यथा
		shअगरt = 3;

	भाग >>= shअगरt;

	अगर (भाग > 32)
		भाग = 32;

	req->rate = (req->parent_rate >> shअगरt) / भाग;
	req->m = भाग - 1;
	req->p = shअगरt;
पूर्ण

अटल स्थिर काष्ठा clk_factors_config sun6i_ar100_config = अणु
	.mwidth = 5,
	.mshअगरt = 8,
	.pwidth = 2,
	.pshअगरt = 4,
पूर्ण;

अटल स्थिर काष्ठा factors_data sun6i_ar100_data = अणु
	.mux = 16,
	.muxmask = GENMASK(1, 0),
	.table = &sun6i_ar100_config,
	.getter = sun6i_get_ar100_factors,
पूर्ण;

अटल DEFINE_SPINLOCK(sun6i_ar100_lock);

अटल पूर्णांक sun6i_a31_ar100_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा resource *r;
	व्योम __iomem *reg;
	काष्ठा clk *clk;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	reg = devm_ioremap_resource(&pdev->dev, r);
	अगर (IS_ERR(reg))
		वापस PTR_ERR(reg);

	clk = sunxi_factors_रेजिस्टर(np, &sun6i_ar100_data, &sun6i_ar100_lock,
				     reg);
	अगर (!clk)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun6i_a31_ar100_clk_dt_ids[] = अणु
	अणु .compatible = "allwinner,sun6i-a31-ar100-clk" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sun6i_a31_ar100_clk_driver = अणु
	.driver = अणु
		.name = "sun6i-a31-ar100-clk",
		.of_match_table = sun6i_a31_ar100_clk_dt_ids,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = sun6i_a31_ar100_clk_probe,
पूर्ण;
builtin_platक्रमm_driver(sun6i_a31_ar100_clk_driver);
