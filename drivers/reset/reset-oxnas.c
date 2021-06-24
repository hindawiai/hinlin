<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/reset/reset-oxnas.c
 *
 * Copyright (C) 2016 Neil Armstrong <narmstrong@baylibre.com>
 * Copyright (C) 2014 Ma Haijun <mahaijuns@gmail.com>
 * Copyright (C) 2009 Oxक्रमd Semiconductor Ltd
 */
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/types.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>

/* Regmap offsets */
#घोषणा RST_SET_REGOFFSET	0x34
#घोषणा RST_CLR_REGOFFSET	0x38

काष्ठा oxnas_reset अणु
	काष्ठा regmap *regmap;
	काष्ठा reset_controller_dev rcdev;
पूर्ण;

अटल पूर्णांक oxnas_reset_reset(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id)
अणु
	काष्ठा oxnas_reset *data =
		container_of(rcdev, काष्ठा oxnas_reset, rcdev);

	regmap_ग_लिखो(data->regmap, RST_SET_REGOFFSET, BIT(id));
	msleep(50);
	regmap_ग_लिखो(data->regmap, RST_CLR_REGOFFSET, BIT(id));

	वापस 0;
पूर्ण

अटल पूर्णांक oxnas_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id)
अणु
	काष्ठा oxnas_reset *data =
		container_of(rcdev, काष्ठा oxnas_reset, rcdev);

	regmap_ग_लिखो(data->regmap, RST_SET_REGOFFSET, BIT(id));

	वापस 0;
पूर्ण

अटल पूर्णांक oxnas_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id)
अणु
	काष्ठा oxnas_reset *data =
		container_of(rcdev, काष्ठा oxnas_reset, rcdev);

	regmap_ग_लिखो(data->regmap, RST_CLR_REGOFFSET, BIT(id));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops oxnas_reset_ops = अणु
	.reset		= oxnas_reset_reset,
	.निश्चित		= oxnas_reset_निश्चित,
	.deनिश्चित	= oxnas_reset_deनिश्चित,
पूर्ण;

अटल स्थिर काष्ठा of_device_id oxnas_reset_dt_ids[] = अणु
	 अणु .compatible = "oxsemi,ox810se-reset", पूर्ण,
	 अणु .compatible = "oxsemi,ox820-reset", पूर्ण,
	 अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल पूर्णांक oxnas_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा oxnas_reset *data;
	काष्ठा device *parent;

	parent = pdev->dev.parent;
	अगर (!parent) अणु
		dev_err(&pdev->dev, "no parent\n");
		वापस -ENODEV;
	पूर्ण

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->regmap = syscon_node_to_regmap(parent->of_node);
	अगर (IS_ERR(data->regmap)) अणु
		dev_err(&pdev->dev, "failed to get parent regmap\n");
		वापस PTR_ERR(data->regmap);
	पूर्ण

	platक्रमm_set_drvdata(pdev, data);

	data->rcdev.owner = THIS_MODULE;
	data->rcdev.nr_resets = 32;
	data->rcdev.ops = &oxnas_reset_ops;
	data->rcdev.of_node = pdev->dev.of_node;

	वापस devm_reset_controller_रेजिस्टर(&pdev->dev, &data->rcdev);
पूर्ण

अटल काष्ठा platक्रमm_driver oxnas_reset_driver = अणु
	.probe	= oxnas_reset_probe,
	.driver = अणु
		.name		= "oxnas-reset",
		.of_match_table	= oxnas_reset_dt_ids,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(oxnas_reset_driver);
