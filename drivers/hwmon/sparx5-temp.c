<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Sparx5 SoC temperature sensor driver
 *
 * Copyright (C) 2020 Lars Povlsen <lars.povlsen@microchip.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा TEMP_CTRL		0
#घोषणा TEMP_CFG		4
#घोषणा  TEMP_CFG_CYCLES	GENMASK(24, 15)
#घोषणा  TEMP_CFG_ENA		BIT(0)
#घोषणा TEMP_STAT		8
#घोषणा  TEMP_STAT_VALID	BIT(12)
#घोषणा  TEMP_STAT_TEMP		GENMASK(11, 0)

काष्ठा s5_hwmon अणु
	व्योम __iomem *base;
	काष्ठा clk *clk;
पूर्ण;

अटल व्योम s5_temp_clk_disable(व्योम *data)
अणु
	काष्ठा clk *clk = data;

	clk_disable_unprepare(clk);
पूर्ण

अटल व्योम s5_temp_enable(काष्ठा s5_hwmon *hwmon)
अणु
	u32 val = पढ़ोl(hwmon->base + TEMP_CFG);
	u32 clk = clk_get_rate(hwmon->clk) / USEC_PER_SEC;

	val &= ~TEMP_CFG_CYCLES;
	val |= FIELD_PREP(TEMP_CFG_CYCLES, clk);
	val |= TEMP_CFG_ENA;

	ग_लिखोl(val, hwmon->base + TEMP_CFG);
पूर्ण

अटल पूर्णांक s5_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		   u32 attr, पूर्णांक channel, दीर्घ *temp)
अणु
	काष्ठा s5_hwmon *hwmon = dev_get_drvdata(dev);
	पूर्णांक rc = 0, value;
	u32 stat;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		stat = पढ़ोl_relaxed(hwmon->base + TEMP_STAT);
		अगर (!(stat & TEMP_STAT_VALID))
			वापस -EAGAIN;
		value = stat & TEMP_STAT_TEMP;
		/*
		 * From रेजिस्टर करोcumentation:
		 * Temp(C) = TEMP_SENSOR_STAT.TEMP / 4096 * 352.2 - 109.4
		 */
		value = DIV_ROUND_CLOSEST(value * 3522, 4096) - 1094;
		/*
		 * Scale करोwn by 10 from above and multiply by 1000 to
		 * have millidegrees as specअगरied by the hwmon sysfs
		 * पूर्णांकerface.
		 */
		value *= 100;
		*temp = value;
		अवरोध;
	शेष:
		rc = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल umode_t s5_is_visible(स्थिर व्योम *_data, क्रमागत hwmon_sensor_types type,
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

अटल स्थिर काष्ठा hwmon_channel_info *s5_info[] = अणु
	HWMON_CHANNEL_INFO(chip, HWMON_C_REGISTER_TZ),
	HWMON_CHANNEL_INFO(temp, HWMON_T_INPUT),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops s5_hwmon_ops = अणु
	.is_visible = s5_is_visible,
	.पढ़ो = s5_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info s5_chip_info = अणु
	.ops = &s5_hwmon_ops,
	.info = s5_info,
पूर्ण;

अटल पूर्णांक s5_temp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *hwmon_dev;
	काष्ठा s5_hwmon *hwmon;
	पूर्णांक ret;

	hwmon = devm_kzalloc(&pdev->dev, माप(*hwmon), GFP_KERNEL);
	अगर (!hwmon)
		वापस -ENOMEM;

	hwmon->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(hwmon->base))
		वापस PTR_ERR(hwmon->base);

	hwmon->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(hwmon->clk))
		वापस PTR_ERR(hwmon->clk);

	ret = clk_prepare_enable(hwmon->clk);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(&pdev->dev, s5_temp_clk_disable,
				       hwmon->clk);
	अगर (ret)
		वापस ret;

	s5_temp_enable(hwmon);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(&pdev->dev,
							 "s5_temp",
							 hwmon,
							 &s5_chip_info,
							 शून्य);

	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id s5_temp_match[] = अणु
	अणु .compatible = "microchip,sparx5-temp" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, s5_temp_match);

अटल काष्ठा platक्रमm_driver s5_temp_driver = अणु
	.probe = s5_temp_probe,
	.driver = अणु
		.name = "sparx5-temp",
		.of_match_table = s5_temp_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(s5_temp_driver);

MODULE_AUTHOR("Lars Povlsen <lars.povlsen@microchip.com>");
MODULE_DESCRIPTION("Sparx5 SoC temperature sensor driver");
MODULE_LICENSE("GPL");
