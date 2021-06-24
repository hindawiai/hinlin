<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * FPGA Bridge Driver क्रम FPGA Management Engine (FME)
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
#समावेश <linux/fpga/fpga-bridge.h>

#समावेश "dfl.h"
#समावेश "dfl-fme-pr.h"

काष्ठा fme_br_priv अणु
	काष्ठा dfl_fme_br_pdata *pdata;
	काष्ठा dfl_fpga_port_ops *port_ops;
	काष्ठा platक्रमm_device *port_pdev;
पूर्ण;

अटल पूर्णांक fme_bridge_enable_set(काष्ठा fpga_bridge *bridge, bool enable)
अणु
	काष्ठा fme_br_priv *priv = bridge->priv;
	काष्ठा platक्रमm_device *port_pdev;
	काष्ठा dfl_fpga_port_ops *ops;

	अगर (!priv->port_pdev) अणु
		port_pdev = dfl_fpga_cdev_find_port(priv->pdata->cdev,
						    &priv->pdata->port_id,
						    dfl_fpga_check_port_id);
		अगर (!port_pdev)
			वापस -ENODEV;

		priv->port_pdev = port_pdev;
	पूर्ण

	अगर (priv->port_pdev && !priv->port_ops) अणु
		ops = dfl_fpga_port_ops_get(priv->port_pdev);
		अगर (!ops || !ops->enable_set)
			वापस -ENOENT;

		priv->port_ops = ops;
	पूर्ण

	वापस priv->port_ops->enable_set(priv->port_pdev, enable);
पूर्ण

अटल स्थिर काष्ठा fpga_bridge_ops fme_bridge_ops = अणु
	.enable_set = fme_bridge_enable_set,
पूर्ण;

अटल पूर्णांक fme_br_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा fme_br_priv *priv;
	काष्ठा fpga_bridge *br;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->pdata = dev_get_platdata(dev);

	br = devm_fpga_bridge_create(dev, "DFL FPGA FME Bridge",
				     &fme_bridge_ops, priv);
	अगर (!br)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, br);

	वापस fpga_bridge_रेजिस्टर(br);
पूर्ण

अटल पूर्णांक fme_br_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fpga_bridge *br = platक्रमm_get_drvdata(pdev);
	काष्ठा fme_br_priv *priv = br->priv;

	fpga_bridge_unरेजिस्टर(br);

	अगर (priv->port_pdev)
		put_device(&priv->port_pdev->dev);
	अगर (priv->port_ops)
		dfl_fpga_port_ops_put(priv->port_ops);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver fme_br_driver = अणु
	.driver	= अणु
		.name    = DFL_FPGA_FME_BRIDGE,
	पूर्ण,
	.probe   = fme_br_probe,
	.हटाओ  = fme_br_हटाओ,
पूर्ण;

module_platक्रमm_driver(fme_br_driver);

MODULE_DESCRIPTION("FPGA Bridge for DFL FPGA Management Engine");
MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:dfl-fme-bridge");
