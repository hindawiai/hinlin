<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Khadas MCU Controlled FAN driver
 *
 * Copyright (C) 2020 BayLibre SAS
 * Author(s): Neil Armstrong <narmstrong@baylibre.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/khadas-mcu.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/thermal.h>

#घोषणा MAX_LEVEL 3

काष्ठा khadas_mcu_fan_ctx अणु
	काष्ठा khadas_mcu *mcu;
	अचिन्हित पूर्णांक level;
	काष्ठा thermal_cooling_device *cdev;
पूर्ण;

अटल पूर्णांक khadas_mcu_fan_set_level(काष्ठा khadas_mcu_fan_ctx *ctx,
				    अचिन्हित पूर्णांक level)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(ctx->mcu->regmap, KHADAS_MCU_CMD_FAN_STATUS_CTRL_REG,
			   level);
	अगर (ret)
		वापस ret;

	ctx->level = level;

	वापस 0;
पूर्ण

अटल पूर्णांक khadas_mcu_fan_get_max_state(काष्ठा thermal_cooling_device *cdev,
					अचिन्हित दीर्घ *state)
अणु
	*state = MAX_LEVEL;

	वापस 0;
पूर्ण

अटल पूर्णांक khadas_mcu_fan_get_cur_state(काष्ठा thermal_cooling_device *cdev,
					अचिन्हित दीर्घ *state)
अणु
	काष्ठा khadas_mcu_fan_ctx *ctx = cdev->devdata;

	*state = ctx->level;

	वापस 0;
पूर्ण

अटल पूर्णांक
khadas_mcu_fan_set_cur_state(काष्ठा thermal_cooling_device *cdev,
			     अचिन्हित दीर्घ state)
अणु
	काष्ठा khadas_mcu_fan_ctx *ctx = cdev->devdata;

	अगर (state > MAX_LEVEL)
		वापस -EINVAL;

	अगर (state == ctx->level)
		वापस 0;

	वापस khadas_mcu_fan_set_level(ctx, state);
पूर्ण

अटल स्थिर काष्ठा thermal_cooling_device_ops khadas_mcu_fan_cooling_ops = अणु
	.get_max_state = khadas_mcu_fan_get_max_state,
	.get_cur_state = khadas_mcu_fan_get_cur_state,
	.set_cur_state = khadas_mcu_fan_set_cur_state,
पूर्ण;

अटल पूर्णांक khadas_mcu_fan_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा khadas_mcu *mcu = dev_get_drvdata(pdev->dev.parent);
	काष्ठा thermal_cooling_device *cdev;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा khadas_mcu_fan_ctx *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;
	ctx->mcu = mcu;
	platक्रमm_set_drvdata(pdev, ctx);

	cdev = devm_thermal_of_cooling_device_रेजिस्टर(dev->parent,
			dev->parent->of_node, "khadas-mcu-fan", ctx,
			&khadas_mcu_fan_cooling_ops);
	अगर (IS_ERR(cdev)) अणु
		ret = PTR_ERR(cdev);
		dev_err(dev, "Failed to register khadas-mcu-fan as cooling device: %d\n",
			ret);
		वापस ret;
	पूर्ण
	ctx->cdev = cdev;

	वापस 0;
पूर्ण

अटल व्योम khadas_mcu_fan_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा khadas_mcu_fan_ctx *ctx = platक्रमm_get_drvdata(pdev);

	khadas_mcu_fan_set_level(ctx, 0);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक khadas_mcu_fan_suspend(काष्ठा device *dev)
अणु
	काष्ठा khadas_mcu_fan_ctx *ctx = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक level_save = ctx->level;
	पूर्णांक ret;

	ret = khadas_mcu_fan_set_level(ctx, 0);
	अगर (ret)
		वापस ret;

	ctx->level = level_save;

	वापस 0;
पूर्ण

अटल पूर्णांक khadas_mcu_fan_resume(काष्ठा device *dev)
अणु
	काष्ठा khadas_mcu_fan_ctx *ctx = dev_get_drvdata(dev);

	वापस khadas_mcu_fan_set_level(ctx, ctx->level);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(khadas_mcu_fan_pm, khadas_mcu_fan_suspend,
			 khadas_mcu_fan_resume);

अटल स्थिर काष्ठा platक्रमm_device_id khadas_mcu_fan_id_table[] = अणु
	अणु .name = "khadas-mcu-fan-ctrl", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, khadas_mcu_fan_id_table);

अटल काष्ठा platक्रमm_driver khadas_mcu_fan_driver = अणु
	.probe		= khadas_mcu_fan_probe,
	.shutकरोwn	= khadas_mcu_fan_shutकरोwn,
	.driver	= अणु
		.name		= "khadas-mcu-fan-ctrl",
		.pm		= &khadas_mcu_fan_pm,
	पूर्ण,
	.id_table	= khadas_mcu_fan_id_table,
पूर्ण;

module_platक्रमm_driver(khadas_mcu_fan_driver);

MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_DESCRIPTION("Khadas MCU FAN driver");
MODULE_LICENSE("GPL");
