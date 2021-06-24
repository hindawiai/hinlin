<शैली गुरु>
/*
 * Copyright (C) 2014 Marvell Technology Group Ltd.
 *
 * Marvell Berlin reset driver
 *
 * Antoine Tenart <antoine.tenart@मुक्त-electrons.com>
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#घोषणा BERLIN_MAX_RESETS	32

#घोषणा to_berlin_reset_priv(p)		\
	container_of((p), काष्ठा berlin_reset_priv, rcdev)

काष्ठा berlin_reset_priv अणु
	काष्ठा regmap			*regmap;
	काष्ठा reset_controller_dev	rcdev;
पूर्ण;

अटल पूर्णांक berlin_reset_reset(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id)
अणु
	काष्ठा berlin_reset_priv *priv = to_berlin_reset_priv(rcdev);
	पूर्णांक offset = id >> 8;
	पूर्णांक mask = BIT(id & 0x1f);

	regmap_ग_लिखो(priv->regmap, offset, mask);

	/* let the reset be effective */
	udelay(10);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops berlin_reset_ops = अणु
	.reset	= berlin_reset_reset,
पूर्ण;

अटल पूर्णांक berlin_reset_xlate(काष्ठा reset_controller_dev *rcdev,
			      स्थिर काष्ठा of_phandle_args *reset_spec)
अणु
	अचिन्हित offset, bit;

	offset = reset_spec->args[0];
	bit = reset_spec->args[1];

	अगर (bit >= BERLIN_MAX_RESETS)
		वापस -EINVAL;

	वापस (offset << 8) | bit;
पूर्ण

अटल पूर्णांक berlin2_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *parent_np = of_get_parent(pdev->dev.of_node);
	काष्ठा berlin_reset_priv *priv;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->regmap = syscon_node_to_regmap(parent_np);
	of_node_put(parent_np);
	अगर (IS_ERR(priv->regmap))
		वापस PTR_ERR(priv->regmap);

	priv->rcdev.owner = THIS_MODULE;
	priv->rcdev.ops = &berlin_reset_ops;
	priv->rcdev.of_node = pdev->dev.of_node;
	priv->rcdev.of_reset_n_cells = 2;
	priv->rcdev.of_xlate = berlin_reset_xlate;

	वापस reset_controller_रेजिस्टर(&priv->rcdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id berlin_reset_dt_match[] = अणु
	अणु .compatible = "marvell,berlin2-reset" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver berlin_reset_driver = अणु
	.probe	= berlin2_reset_probe,
	.driver	= अणु
		.name = "berlin2-reset",
		.of_match_table = berlin_reset_dt_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(berlin_reset_driver);
