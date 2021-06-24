<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Broadcom BCM2835 SoC temperature sensor
 *
 * Copyright (C) 2016 Martin Sperl
 */

#समावेश <linux/clk.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/thermal.h>

#समावेश "../thermal_hwmon.h"

#घोषणा BCM2835_TS_TSENSCTL			0x00
#घोषणा BCM2835_TS_TSENSSTAT			0x04

#घोषणा BCM2835_TS_TSENSCTL_PRWDW		BIT(0)
#घोषणा BCM2835_TS_TSENSCTL_RSTB		BIT(1)

/*
 * bandgap reference voltage in 6 mV increments
 * 000b = 1178 mV, 001b = 1184 mV, ... 111b = 1220 mV
 */
#घोषणा BCM2835_TS_TSENSCTL_CTRL_BITS		3
#घोषणा BCM2835_TS_TSENSCTL_CTRL_SHIFT		2
#घोषणा BCM2835_TS_TSENSCTL_CTRL_MASK		    \
	GENMASK(BCM2835_TS_TSENSCTL_CTRL_BITS +     \
		BCM2835_TS_TSENSCTL_CTRL_SHIFT - 1, \
		BCM2835_TS_TSENSCTL_CTRL_SHIFT)
#घोषणा BCM2835_TS_TSENSCTL_CTRL_DEFAULT	1
#घोषणा BCM2835_TS_TSENSCTL_EN_INT		BIT(5)
#घोषणा BCM2835_TS_TSENSCTL_सूचीECT		BIT(6)
#घोषणा BCM2835_TS_TSENSCTL_CLR_INT		BIT(7)
#घोषणा BCM2835_TS_TSENSCTL_THOLD_SHIFT		8
#घोषणा BCM2835_TS_TSENSCTL_THOLD_BITS		10
#घोषणा BCM2835_TS_TSENSCTL_THOLD_MASK		     \
	GENMASK(BCM2835_TS_TSENSCTL_THOLD_BITS +     \
		BCM2835_TS_TSENSCTL_THOLD_SHIFT - 1, \
		BCM2835_TS_TSENSCTL_THOLD_SHIFT)
/*
 * समय how दीर्घ the block to be निश्चितed in reset
 * which based on a घड़ी counter (TSENS घड़ी assumed)
 */
#घोषणा BCM2835_TS_TSENSCTL_RSTDELAY_SHIFT	18
#घोषणा BCM2835_TS_TSENSCTL_RSTDELAY_BITS	8
#घोषणा BCM2835_TS_TSENSCTL_REGULEN		BIT(26)

#घोषणा BCM2835_TS_TSENSSTAT_DATA_BITS		10
#घोषणा BCM2835_TS_TSENSSTAT_DATA_SHIFT		0
#घोषणा BCM2835_TS_TSENSSTAT_DATA_MASK		     \
	GENMASK(BCM2835_TS_TSENSSTAT_DATA_BITS +     \
		BCM2835_TS_TSENSSTAT_DATA_SHIFT - 1, \
		BCM2835_TS_TSENSSTAT_DATA_SHIFT)
#घोषणा BCM2835_TS_TSENSSTAT_VALID		BIT(10)
#घोषणा BCM2835_TS_TSENSSTAT_INTERRUPT		BIT(11)

काष्ठा bcm2835_thermal_data अणु
	काष्ठा thermal_zone_device *tz;
	व्योम __iomem *regs;
	काष्ठा clk *clk;
	काष्ठा dentry *debugfsdir;
पूर्ण;

अटल पूर्णांक bcm2835_thermal_adc2temp(u32 adc, पूर्णांक offset, पूर्णांक slope)
अणु
	वापस offset + slope * adc;
पूर्ण

अटल पूर्णांक bcm2835_thermal_temp2adc(पूर्णांक temp, पूर्णांक offset, पूर्णांक slope)
अणु
	temp -= offset;
	temp /= slope;

	अगर (temp < 0)
		temp = 0;
	अगर (temp >= BIT(BCM2835_TS_TSENSSTAT_DATA_BITS))
		temp = BIT(BCM2835_TS_TSENSSTAT_DATA_BITS) - 1;

	वापस temp;
पूर्ण

अटल पूर्णांक bcm2835_thermal_get_temp(व्योम *d, पूर्णांक *temp)
अणु
	काष्ठा bcm2835_thermal_data *data = d;
	u32 val = पढ़ोl(data->regs + BCM2835_TS_TSENSSTAT);

	अगर (!(val & BCM2835_TS_TSENSSTAT_VALID))
		वापस -EIO;

	val &= BCM2835_TS_TSENSSTAT_DATA_MASK;

	*temp = bcm2835_thermal_adc2temp(
		val,
		thermal_zone_get_offset(data->tz),
		thermal_zone_get_slope(data->tz));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा debugfs_reg32 bcm2835_thermal_regs[] = अणु
	अणु
		.name = "ctl",
		.offset = 0
	पूर्ण,
	अणु
		.name = "stat",
		.offset = 4
	पूर्ण
पूर्ण;

अटल व्योम bcm2835_thermal_debugfs(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm2835_thermal_data *data = platक्रमm_get_drvdata(pdev);
	काष्ठा debugfs_regset32 *regset;

	data->debugfsdir = debugfs_create_dir("bcm2835_thermal", शून्य);

	regset = devm_kzalloc(&pdev->dev, माप(*regset), GFP_KERNEL);
	अगर (!regset)
		वापस;

	regset->regs = bcm2835_thermal_regs;
	regset->nregs = ARRAY_SIZE(bcm2835_thermal_regs);
	regset->base = data->regs;

	debugfs_create_regset32("regset", 0444, data->debugfsdir, regset);
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops bcm2835_thermal_ops = अणु
	.get_temp = bcm2835_thermal_get_temp,
पूर्ण;

/*
 * Note: as per Raspberry Foundation FAQ
 * (https://www.raspberrypi.org/help/faqs/#perक्रमmanceOperatingTemperature)
 * the recommended temperature range क्रम the SoC -40C to +85C
 * so the trip limit is set to 80C.
 * this applies to all the BCM283X SoC
 */

अटल स्थिर काष्ठा of_device_id bcm2835_thermal_of_match_table[] = अणु
	अणु
		.compatible = "brcm,bcm2835-thermal",
	पूर्ण,
	अणु
		.compatible = "brcm,bcm2836-thermal",
	पूर्ण,
	अणु
		.compatible = "brcm,bcm2837-thermal",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm2835_thermal_of_match_table);

अटल पूर्णांक bcm2835_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा thermal_zone_device *tz;
	काष्ठा bcm2835_thermal_data *data;
	काष्ठा resource *res;
	पूर्णांक err = 0;
	u32 val;
	अचिन्हित दीर्घ rate;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	match = of_match_device(bcm2835_thermal_of_match_table,
				&pdev->dev);
	अगर (!match)
		वापस -EINVAL;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	data->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(data->regs)) अणु
		err = PTR_ERR(data->regs);
		वापस err;
	पूर्ण

	data->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(data->clk)) अणु
		err = PTR_ERR(data->clk);
		अगर (err != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Could not get clk: %d\n", err);
		वापस err;
	पूर्ण

	err = clk_prepare_enable(data->clk);
	अगर (err)
		वापस err;

	rate = clk_get_rate(data->clk);
	अगर ((rate < 1920000) || (rate > 5000000))
		dev_warn(&pdev->dev,
			 "Clock %pCn running at %lu Hz is outside of the recommended range: 1.92 to 5MHz\n",
			 data->clk, rate);

	/* रेजिस्टर of thermal sensor and get info from DT */
	tz = thermal_zone_of_sensor_रेजिस्टर(&pdev->dev, 0, data,
					     &bcm2835_thermal_ops);
	अगर (IS_ERR(tz)) अणु
		err = PTR_ERR(tz);
		dev_err(&pdev->dev,
			"Failed to register the thermal device: %d\n",
			err);
		जाओ err_clk;
	पूर्ण

	/*
	 * right now the FW करोes set up the HW-block, so we are not
	 * touching the configuration रेजिस्टरs.
	 * But अगर the HW is not enabled, then set it up
	 * using "sane" values used by the firmware right now.
	 */
	val = पढ़ोl(data->regs + BCM2835_TS_TSENSCTL);
	अगर (!(val & BCM2835_TS_TSENSCTL_RSTB)) अणु
		पूर्णांक trip_temp, offset, slope;

		slope = thermal_zone_get_slope(tz);
		offset = thermal_zone_get_offset(tz);
		/*
		 * For now we deal only with critical, otherwise
		 * would need to iterate
		 */
		err = tz->ops->get_trip_temp(tz, 0, &trip_temp);
		अगर (err < 0) अणु
			dev_err(&pdev->dev,
				"Not able to read trip_temp: %d\n",
				err);
			जाओ err_tz;
		पूर्ण

		/* set bandgap reference voltage and enable voltage regulator */
		val = (BCM2835_TS_TSENSCTL_CTRL_DEFAULT <<
		       BCM2835_TS_TSENSCTL_CTRL_SHIFT) |
		      BCM2835_TS_TSENSCTL_REGULEN;

		/* use the recommended reset duration */
		val |= (0xFE << BCM2835_TS_TSENSCTL_RSTDELAY_SHIFT);

		/*  trip_adc value from info */
		val |= bcm2835_thermal_temp2adc(trip_temp,
						offset,
						slope)
			<< BCM2835_TS_TSENSCTL_THOLD_SHIFT;

		/* ग_लिखो the value back to the रेजिस्टर as 2 steps */
		ग_लिखोl(val, data->regs + BCM2835_TS_TSENSCTL);
		val |= BCM2835_TS_TSENSCTL_RSTB;
		ग_लिखोl(val, data->regs + BCM2835_TS_TSENSCTL);
	पूर्ण

	data->tz = tz;

	platक्रमm_set_drvdata(pdev, data);

	/*
	 * Thermal_zone करोesn't enable hwmon as शेष,
	 * enable it here
	 */
	tz->tzp->no_hwmon = false;
	err = thermal_add_hwmon_sysfs(tz);
	अगर (err)
		जाओ err_tz;

	bcm2835_thermal_debugfs(pdev);

	वापस 0;
err_tz:
	thermal_zone_of_sensor_unरेजिस्टर(&pdev->dev, tz);
err_clk:
	clk_disable_unprepare(data->clk);

	वापस err;
पूर्ण

अटल पूर्णांक bcm2835_thermal_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm2835_thermal_data *data = platक्रमm_get_drvdata(pdev);
	काष्ठा thermal_zone_device *tz = data->tz;

	debugfs_हटाओ_recursive(data->debugfsdir);
	thermal_zone_of_sensor_unरेजिस्टर(&pdev->dev, tz);
	clk_disable_unprepare(data->clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver bcm2835_thermal_driver = अणु
	.probe = bcm2835_thermal_probe,
	.हटाओ = bcm2835_thermal_हटाओ,
	.driver = अणु
		.name = "bcm2835_thermal",
		.of_match_table = bcm2835_thermal_of_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(bcm2835_thermal_driver);

MODULE_AUTHOR("Martin Sperl");
MODULE_DESCRIPTION("Thermal driver for bcm2835 chip");
MODULE_LICENSE("GPL");
