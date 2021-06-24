<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI da8xx DDR2/mDDR controller driver
 *
 * Copyright (C) 2016 BayLibre SAS
 *
 * Author:
 *   Bartosz Golaszewski <bgolaszewski@baylibre.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>

/*
 * REVISIT: Linux करोesn't have a good framework क्रम the kind of perक्रमmance
 * knobs this driver controls. We can't use device tree properties as it deals
 * with hardware configuration rather than description. We also करोn't want to
 * commit to मुख्यtaining some अक्रमom sysfs attributes.
 *
 * For now we just hardcode the रेजिस्टर values क्रम the boards that need
 * some changes (as is the हाल क्रम the LCD controller on da850-lcdk - the
 * first board we support here). When linux माला_लो an appropriate framework,
 * we'll easily convert the driver to it.
 */

काष्ठा da8xx_ddrctl_config_knob अणु
	स्थिर अक्षर *name;
	u32 reg;
	u32 mask;
	u32 shअगरt;
पूर्ण;

अटल स्थिर काष्ठा da8xx_ddrctl_config_knob da8xx_ddrctl_knobs[] = अणु
	अणु
		.name = "da850-pbbpr",
		.reg = 0x20,
		.mask = 0xffffff00,
		.shअगरt = 0,
	पूर्ण,
पूर्ण;

काष्ठा da8xx_ddrctl_setting अणु
	स्थिर अक्षर *name;
	u32 val;
पूर्ण;

काष्ठा da8xx_ddrctl_board_settings अणु
	स्थिर अक्षर *board;
	स्थिर काष्ठा da8xx_ddrctl_setting *settings;
पूर्ण;

अटल स्थिर काष्ठा da8xx_ddrctl_setting da850_lcdk_ddrctl_settings[] = अणु
	अणु
		.name = "da850-pbbpr",
		.val = 0x20,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा da8xx_ddrctl_board_settings da8xx_ddrctl_board_confs[] = अणु
	अणु
		.board = "ti,da850-lcdk",
		.settings = da850_lcdk_ddrctl_settings,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा da8xx_ddrctl_config_knob *
da8xx_ddrctl_match_knob(स्थिर काष्ठा da8xx_ddrctl_setting *setting)
अणु
	स्थिर काष्ठा da8xx_ddrctl_config_knob *knob;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(da8xx_ddrctl_knobs); i++) अणु
		knob = &da8xx_ddrctl_knobs[i];

		अगर (म_भेद(knob->name, setting->name) == 0)
			वापस knob;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा da8xx_ddrctl_setting *da8xx_ddrctl_get_board_settings(व्योम)
अणु
	स्थिर काष्ठा da8xx_ddrctl_board_settings *board_settings;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(da8xx_ddrctl_board_confs); i++) अणु
		board_settings = &da8xx_ddrctl_board_confs[i];

		अगर (of_machine_is_compatible(board_settings->board))
			वापस board_settings->settings;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक da8xx_ddrctl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा da8xx_ddrctl_config_knob *knob;
	स्थिर काष्ठा da8xx_ddrctl_setting *setting;
	काष्ठा resource *res;
	व्योम __iomem *ddrctl;
	काष्ठा device *dev;
	u32 reg;

	dev = &pdev->dev;

	setting = da8xx_ddrctl_get_board_settings();
	अगर (!setting) अणु
		dev_err(dev, "no settings defined for this board\n");
		वापस -EINVAL;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ddrctl = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ddrctl)) अणु
		dev_err(dev, "unable to map memory controller registers\n");
		वापस PTR_ERR(ddrctl);
	पूर्ण

	क्रम (; setting->name; setting++) अणु
		knob = da8xx_ddrctl_match_knob(setting);
		अगर (!knob) अणु
			dev_warn(dev,
				 "no such config option: %s\n", setting->name);
			जारी;
		पूर्ण

		अगर (knob->reg + माप(u32) > resource_size(res)) अणु
			dev_warn(dev,
				 "register offset of '%s' exceeds mapped memory size\n",
				 knob->name);
			जारी;
		पूर्ण

		reg = पढ़ोl(ddrctl + knob->reg);
		reg &= knob->mask;
		reg |= setting->val << knob->shअगरt;

		dev_dbg(dev, "writing 0x%08x to %s\n", reg, setting->name);

		ग_लिखोl(reg, ddrctl + knob->reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id da8xx_ddrctl_of_match[] = अणु
	अणु .compatible = "ti,da850-ddr-controller", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver da8xx_ddrctl_driver = अणु
	.probe = da8xx_ddrctl_probe,
	.driver = अणु
		.name = "da850-ddr-controller",
		.of_match_table = da8xx_ddrctl_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(da8xx_ddrctl_driver);

MODULE_AUTHOR("Bartosz Golaszewski <bgolaszewski@baylibre.com>");
MODULE_DESCRIPTION("TI da8xx DDR2/mDDR controller driver");
MODULE_LICENSE("GPL v2");
