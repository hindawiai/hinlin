<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Low Power Subप्रणाली घड़ीs.
 *
 * Copyright (C) 2013, Intel Corporation
 * Authors: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 *	    Heikki Krogerus <heikki.krogerus@linux.पूर्णांकel.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/x86/clk-lpss.h>
#समावेश <linux/platक्रमm_device.h>

अटल पूर्णांक lpt_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpss_clk_data *drvdata;
	काष्ठा clk *clk;

	drvdata = devm_kzalloc(&pdev->dev, माप(*drvdata), GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	/* LPSS मुक्त running घड़ी */
	drvdata->name = "lpss_clk";
	clk = clk_रेजिस्टर_fixed_rate(&pdev->dev, drvdata->name, शून्य,
				      0, 100000000);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	drvdata->clk = clk;
	platक्रमm_set_drvdata(pdev, drvdata);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver lpt_clk_driver = अणु
	.driver = अणु
		.name = "clk-lpt",
	पूर्ण,
	.probe = lpt_clk_probe,
पूर्ण;

पूर्णांक __init lpt_clk_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&lpt_clk_driver);
पूर्ण
