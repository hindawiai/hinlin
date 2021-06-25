<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Synaptics AS370 SoC Hardware Monitoring Driver
 *
 * Copyright (C) 2018 Synaptics Incorporated
 * Author: Jisheng Zhang <jszhang@kernel.org>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>

#घोषणा CTRL		0x0
#घोषणा  PD		BIT(0)
#घोषणा  EN		BIT(1)
#घोषणा  T_SEL		BIT(2)
#घोषणा  V_SEL		BIT(3)
#घोषणा  NMOS_SEL	BIT(8)
#घोषणा  PMOS_SEL	BIT(9)
#घोषणा STS		0x4
#घोषणा  BN_MASK	GENMASK(11, 0)
#घोषणा  EOC		BIT(12)

काष्ठा as370_hwmon अणु
	व्योम __iomem *base;
पूर्ण;

अटल व्योम init_pvt(काष्ठा as370_hwmon *hwmon)
अणु
	u32 val;
	व्योम __iomem *addr = hwmon->base + CTRL;

	val = PD;
	ग_लिखोl_relaxed(val, addr);
	val |= T_SEL;
	ग_लिखोl_relaxed(val, addr);
	val |= EN;
	ग_लिखोl_relaxed(val, addr);
	val &= ~PD;
	ग_लिखोl_relaxed(val, addr);
पूर्ण

अटल पूर्णांक as370_hwmon_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			    u32 attr, पूर्णांक channel, दीर्घ *temp)
अणु
	पूर्णांक val;
	काष्ठा as370_hwmon *hwmon = dev_get_drvdata(dev);

	चयन (attr) अणु
	हाल hwmon_temp_input:
		val = पढ़ोl_relaxed(hwmon->base + STS) & BN_MASK;
		*temp = DIV_ROUND_CLOSEST(val * 251802, 4096) - 85525;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल umode_t
as370_hwmon_is_visible(स्थिर व्योम *data, क्रमागत hwmon_sensor_types type,
		       u32 attr, पूर्णांक channel)
अणु
	अगर (type != hwmon_temp)
		वापस 0;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		वापस 0444;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर u32 as370_hwmon_temp_config[] = अणु
	HWMON_T_INPUT,
	0
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info as370_hwmon_temp = अणु
	.type = hwmon_temp,
	.config = as370_hwmon_temp_config,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *as370_hwmon_info[] = अणु
	&as370_hwmon_temp,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops as370_hwmon_ops = अणु
	.is_visible = as370_hwmon_is_visible,
	.पढ़ो = as370_hwmon_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info as370_chip_info = अणु
	.ops = &as370_hwmon_ops,
	.info = as370_hwmon_info,
पूर्ण;

अटल पूर्णांक as370_hwmon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *hwmon_dev;
	काष्ठा as370_hwmon *hwmon;
	काष्ठा device *dev = &pdev->dev;

	hwmon = devm_kzalloc(dev, माप(*hwmon), GFP_KERNEL);
	अगर (!hwmon)
		वापस -ENOMEM;

	hwmon->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(hwmon->base))
		वापस PTR_ERR(hwmon->base);

	init_pvt(hwmon);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev,
							 "as370",
							 hwmon,
							 &as370_chip_info,
							 शून्य);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id as370_hwmon_match[] = अणु
	अणु .compatible = "syna,as370-hwmon" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, as370_hwmon_match);

अटल काष्ठा platक्रमm_driver as370_hwmon_driver = अणु
	.probe = as370_hwmon_probe,
	.driver = अणु
		.name = "as370-hwmon",
		.of_match_table = as370_hwmon_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(as370_hwmon_driver);

MODULE_AUTHOR("Jisheng Zhang<jszhang@kernel.org>");
MODULE_DESCRIPTION("Synaptics AS370 SoC hardware monitor");
MODULE_LICENSE("GPL v2");
