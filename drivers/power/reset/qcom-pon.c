<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2017-18 Linaro Limited

#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/reboot-mode.h>
#समावेश <linux/regmap.h>

#घोषणा PON_SOFT_RB_SPARE		0x8f

#घोषणा GEN1_REASON_SHIFT		2
#घोषणा GEN2_REASON_SHIFT		1

काष्ठा pm8916_pon अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	u32 baseaddr;
	काष्ठा reboot_mode_driver reboot_mode;
	दीर्घ reason_shअगरt;
पूर्ण;

अटल पूर्णांक pm8916_reboot_mode_ग_लिखो(काष्ठा reboot_mode_driver *reboot,
				    अचिन्हित पूर्णांक magic)
अणु
	काष्ठा pm8916_pon *pon = container_of
			(reboot, काष्ठा pm8916_pon, reboot_mode);
	पूर्णांक ret;

	ret = regmap_update_bits(pon->regmap,
				 pon->baseaddr + PON_SOFT_RB_SPARE,
				 GENMASK(7, pon->reason_shअगरt),
				 magic << pon->reason_shअगरt);
	अगर (ret < 0)
		dev_err(pon->dev, "update reboot mode bits failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक pm8916_pon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm8916_pon *pon;
	पूर्णांक error;

	pon = devm_kzalloc(&pdev->dev, माप(*pon), GFP_KERNEL);
	अगर (!pon)
		वापस -ENOMEM;

	pon->dev = &pdev->dev;

	pon->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!pon->regmap) अणु
		dev_err(&pdev->dev, "failed to locate regmap\n");
		वापस -ENODEV;
	पूर्ण

	error = of_property_पढ़ो_u32(pdev->dev.of_node, "reg",
				     &pon->baseaddr);
	अगर (error)
		वापस error;

	pon->reboot_mode.dev = &pdev->dev;
	pon->reason_shअगरt = (दीर्घ)of_device_get_match_data(&pdev->dev);
	pon->reboot_mode.ग_लिखो = pm8916_reboot_mode_ग_लिखो;
	error = devm_reboot_mode_रेजिस्टर(&pdev->dev, &pon->reboot_mode);
	अगर (error) अणु
		dev_err(&pdev->dev, "can't register reboot mode\n");
		वापस error;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pon);

	वापस devm_of_platक्रमm_populate(&pdev->dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id pm8916_pon_id_table[] = अणु
	अणु .compatible = "qcom,pm8916-pon", .data = (व्योम *)GEN1_REASON_SHIFT पूर्ण,
	अणु .compatible = "qcom,pms405-pon", .data = (व्योम *)GEN1_REASON_SHIFT पूर्ण,
	अणु .compatible = "qcom,pm8998-pon", .data = (व्योम *)GEN2_REASON_SHIFT पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pm8916_pon_id_table);

अटल काष्ठा platक्रमm_driver pm8916_pon_driver = अणु
	.probe = pm8916_pon_probe,
	.driver = अणु
		.name = "pm8916-pon",
		.of_match_table = of_match_ptr(pm8916_pon_id_table),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(pm8916_pon_driver);

MODULE_DESCRIPTION("pm8916 Power On driver");
MODULE_LICENSE("GPL v2");
