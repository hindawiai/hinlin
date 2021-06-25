<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * FPGA Region Driver क्रम FPGA Management Engine (FME)
 *
 * Copyright (C) 2017-2018 Intel Corporation, Inc.
 *
 * Authors:
 *   Wu Hao <hao.wu@पूर्णांकel.com>
 *   Joseph Grecco <joe.grecco@पूर्णांकel.com>
 *   Enno Luebbers <enno.luebbers@पूर्णांकel.com>
 *   Tim Whisonant <tim.whisonant@पूर्णांकel.com>
 *   Ananda Ravuri <ananda.ravuri@पूर्णांकel.com>
 *   Henry Mitchel <henry.mitchel@पूर्णांकel.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/fpga/fpga-mgr.h>
#समावेश <linux/fpga/fpga-region.h>

#समावेश "dfl-fme-pr.h"

अटल पूर्णांक fme_region_get_bridges(काष्ठा fpga_region *region)
अणु
	काष्ठा dfl_fme_region_pdata *pdata = region->priv;
	काष्ठा device *dev = &pdata->br->dev;

	वापस fpga_bridge_get_to_list(dev, region->info, &region->bridge_list);
पूर्ण

अटल पूर्णांक fme_region_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dfl_fme_region_pdata *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा fpga_region *region;
	काष्ठा fpga_manager *mgr;
	पूर्णांक ret;

	mgr = fpga_mgr_get(&pdata->mgr->dev);
	अगर (IS_ERR(mgr))
		वापस -EPROBE_DEFER;

	region = devm_fpga_region_create(dev, mgr, fme_region_get_bridges);
	अगर (!region) अणु
		ret = -ENOMEM;
		जाओ eprobe_mgr_put;
	पूर्ण

	region->priv = pdata;
	region->compat_id = mgr->compat_id;
	platक्रमm_set_drvdata(pdev, region);

	ret = fpga_region_रेजिस्टर(region);
	अगर (ret)
		जाओ eprobe_mgr_put;

	dev_dbg(dev, "DFL FME FPGA Region probed\n");

	वापस 0;

eprobe_mgr_put:
	fpga_mgr_put(mgr);
	वापस ret;
पूर्ण

अटल पूर्णांक fme_region_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fpga_region *region = platक्रमm_get_drvdata(pdev);
	काष्ठा fpga_manager *mgr = region->mgr;

	fpga_region_unरेजिस्टर(region);
	fpga_mgr_put(mgr);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver fme_region_driver = अणु
	.driver	= अणु
		.name    = DFL_FPGA_FME_REGION,
	पूर्ण,
	.probe   = fme_region_probe,
	.हटाओ  = fme_region_हटाओ,
पूर्ण;

module_platक्रमm_driver(fme_region_driver);

MODULE_DESCRIPTION("FPGA Region for DFL FPGA Management Engine");
MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:dfl-fme-region");
