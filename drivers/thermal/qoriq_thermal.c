<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2016 Freescale Semiconductor, Inc.

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sizes.h>
#समावेश <linux/thermal.h>
#समावेश <linux/units.h>

#समावेश "thermal_core.h"
#समावेश "thermal_hwmon.h"

#घोषणा SITES_MAX		16
#घोषणा TMR_DISABLE		0x0
#घोषणा TMR_ME			0x80000000
#घोषणा TMR_ALPF		0x0c000000
#घोषणा TMR_ALPF_V2		0x03000000
#घोषणा TMTMIR_DEFAULT	0x0000000f
#घोषणा TIER_DISABLE	0x0
#घोषणा TEUMR0_V2		0x51009c00
#घोषणा TMSARA_V2		0xe
#घोषणा TMU_VER1		0x1
#घोषणा TMU_VER2		0x2

#घोषणा REGS_TMR	0x000	/* Mode Register */
#घोषणा TMR_DISABLE	0x0
#घोषणा TMR_ME		0x80000000
#घोषणा TMR_ALPF	0x0c000000
#घोषणा TMR_MSITE_ALL	GENMASK(15, 0)

#घोषणा REGS_TMTMIR	0x008	/* Temperature measurement पूर्णांकerval Register */
#घोषणा TMTMIR_DEFAULT	0x0000000f

#घोषणा REGS_V2_TMSR	0x008	/* monitor site रेजिस्टर */

#घोषणा REGS_V2_TMTMIR	0x00c	/* Temperature measurement पूर्णांकerval Register */

#घोषणा REGS_TIER	0x020	/* Interrupt Enable Register */
#घोषणा TIER_DISABLE	0x0


#घोषणा REGS_TTCFGR	0x080	/* Temperature Configuration Register */
#घोषणा REGS_TSCFGR	0x084	/* Sensor Configuration Register */

#घोषणा REGS_TRITSR(n)	(0x100 + 16 * (n)) /* Immediate Temperature
					    * Site Register
					    */
#घोषणा TRITSR_V	BIT(31)
#घोषणा REGS_V2_TMSAR(n)	(0x304 + 16 * (n))	/* TMU monitoring
						* site adjusपंचांगent रेजिस्टर
						*/
#घोषणा REGS_TTRnCR(n)	(0xf10 + 4 * (n)) /* Temperature Range n
					   * Control Register
					   */
#घोषणा REGS_IPBRR(n)		(0xbf8 + 4 * (n)) /* IP Block Revision
						   * Register n
						   */
#घोषणा REGS_V2_TEUMR(n)	(0xf00 + 4 * (n))

/*
 * Thermal zone data
 */
काष्ठा qoriq_sensor अणु
	पूर्णांक				id;
पूर्ण;

काष्ठा qoriq_पंचांगu_data अणु
	पूर्णांक ver;
	काष्ठा regmap *regmap;
	काष्ठा clk *clk;
	काष्ठा qoriq_sensor	sensor[SITES_MAX];
पूर्ण;

अटल काष्ठा qoriq_पंचांगu_data *qoriq_sensor_to_data(काष्ठा qoriq_sensor *s)
अणु
	वापस container_of(s, काष्ठा qoriq_पंचांगu_data, sensor[s->id]);
पूर्ण

अटल पूर्णांक पंचांगu_get_temp(व्योम *p, पूर्णांक *temp)
अणु
	काष्ठा qoriq_sensor *qsensor = p;
	काष्ठा qoriq_पंचांगu_data *qdata = qoriq_sensor_to_data(qsensor);
	u32 val;
	/*
	 * REGS_TRITSR(id) has the following layout:
	 *
	 * For TMU Rev1:
	 * 31  ... 7 6 5 4 3 2 1 0
	 *  V          TEMP
	 *
	 * Where V bit signअगरies अगर the measurement is पढ़ोy and is
	 * within sensor range. TEMP is an 8 bit value representing
	 * temperature in Celsius.

	 * For TMU Rev2:
	 * 31  ... 8 7 6 5 4 3 2 1 0
	 *  V          TEMP
	 *
	 * Where V bit signअगरies अगर the measurement is पढ़ोy and is
	 * within sensor range. TEMP is an 9 bit value representing
	 * temperature in KelVin.
	 */
	अगर (regmap_पढ़ो_poll_समयout(qdata->regmap,
				     REGS_TRITSR(qsensor->id),
				     val,
				     val & TRITSR_V,
				     USEC_PER_MSEC,
				     10 * USEC_PER_MSEC))
		वापस -ENODATA;

	अगर (qdata->ver == TMU_VER1)
		*temp = (val & GENMASK(7, 0)) * MILLIDEGREE_PER_DEGREE;
	अन्यथा
		*temp = kelvin_to_millicelsius(val & GENMASK(8, 0));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops पंचांगu_tz_ops = अणु
	.get_temp = पंचांगu_get_temp,
पूर्ण;

अटल पूर्णांक qoriq_पंचांगu_रेजिस्टर_पंचांगu_zone(काष्ठा device *dev,
				       काष्ठा qoriq_पंचांगu_data *qdata)
अणु
	पूर्णांक id;

	अगर (qdata->ver == TMU_VER1) अणु
		regmap_ग_लिखो(qdata->regmap, REGS_TMR,
			     TMR_MSITE_ALL | TMR_ME | TMR_ALPF);
	पूर्ण अन्यथा अणु
		regmap_ग_लिखो(qdata->regmap, REGS_V2_TMSR, TMR_MSITE_ALL);
		regmap_ग_लिखो(qdata->regmap, REGS_TMR, TMR_ME | TMR_ALPF_V2);
	पूर्ण

	क्रम (id = 0; id < SITES_MAX; id++) अणु
		काष्ठा thermal_zone_device *tzd;
		काष्ठा qoriq_sensor *sensor = &qdata->sensor[id];
		पूर्णांक ret;

		sensor->id = id;

		tzd = devm_thermal_zone_of_sensor_रेजिस्टर(dev, id,
							   sensor,
							   &पंचांगu_tz_ops);
		ret = PTR_ERR_OR_ZERO(tzd);
		अगर (ret) अणु
			अगर (ret == -ENODEV)
				जारी;

			regmap_ग_लिखो(qdata->regmap, REGS_TMR, TMR_DISABLE);
			वापस ret;
		पूर्ण

		अगर (devm_thermal_add_hwmon_sysfs(tzd))
			dev_warn(dev,
				 "Failed to add hwmon sysfs attributes\n");

	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qoriq_पंचांगu_calibration(काष्ठा device *dev,
				 काष्ठा qoriq_पंचांगu_data *data)
अणु
	पूर्णांक i, val, len;
	u32 range[4];
	स्थिर u32 *calibration;
	काष्ठा device_node *np = dev->of_node;

	len = of_property_count_u32_elems(np, "fsl,tmu-range");
	अगर (len < 0 || len > 4) अणु
		dev_err(dev, "invalid range data.\n");
		वापस len;
	पूर्ण

	val = of_property_पढ़ो_u32_array(np, "fsl,tmu-range", range, len);
	अगर (val != 0) अणु
		dev_err(dev, "failed to read range data.\n");
		वापस val;
	पूर्ण

	/* Init temperature range रेजिस्टरs */
	क्रम (i = 0; i < len; i++)
		regmap_ग_लिखो(data->regmap, REGS_TTRnCR(i), range[i]);

	calibration = of_get_property(np, "fsl,tmu-calibration", &len);
	अगर (calibration == शून्य || len % 8) अणु
		dev_err(dev, "invalid calibration data.\n");
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < len; i += 8, calibration += 2) अणु
		val = of_पढ़ो_number(calibration, 1);
		regmap_ग_लिखो(data->regmap, REGS_TTCFGR, val);
		val = of_पढ़ो_number(calibration + 1, 1);
		regmap_ग_लिखो(data->regmap, REGS_TSCFGR, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qoriq_पंचांगu_init_device(काष्ठा qoriq_पंचांगu_data *data)
अणु
	पूर्णांक i;

	/* Disable पूर्णांकerrupt, using polling instead */
	regmap_ग_लिखो(data->regmap, REGS_TIER, TIER_DISABLE);

	/* Set update_पूर्णांकerval */

	अगर (data->ver == TMU_VER1) अणु
		regmap_ग_लिखो(data->regmap, REGS_TMTMIR, TMTMIR_DEFAULT);
	पूर्ण अन्यथा अणु
		regmap_ग_लिखो(data->regmap, REGS_V2_TMTMIR, TMTMIR_DEFAULT);
		regmap_ग_लिखो(data->regmap, REGS_V2_TEUMR(0), TEUMR0_V2);
		क्रम (i = 0; i < SITES_MAX; i++)
			regmap_ग_लिखो(data->regmap, REGS_V2_TMSAR(i), TMSARA_V2);
	पूर्ण

	/* Disable monitoring */
	regmap_ग_लिखो(data->regmap, REGS_TMR, TMR_DISABLE);
पूर्ण

अटल स्थिर काष्ठा regmap_range qoriq_yes_ranges[] = अणु
	regmap_reg_range(REGS_TMR, REGS_TSCFGR),
	regmap_reg_range(REGS_TTRnCR(0), REGS_TTRnCR(3)),
	regmap_reg_range(REGS_V2_TEUMR(0), REGS_V2_TEUMR(2)),
	regmap_reg_range(REGS_V2_TMSAR(0), REGS_V2_TMSAR(15)),
	regmap_reg_range(REGS_IPBRR(0), REGS_IPBRR(1)),
	/* Read only रेजिस्टरs below */
	regmap_reg_range(REGS_TRITSR(0), REGS_TRITSR(15)),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table qoriq_wr_table = अणु
	.yes_ranges	= qoriq_yes_ranges,
	.n_yes_ranges	= ARRAY_SIZE(qoriq_yes_ranges) - 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table qoriq_rd_table = अणु
	.yes_ranges	= qoriq_yes_ranges,
	.n_yes_ranges	= ARRAY_SIZE(qoriq_yes_ranges),
पूर्ण;

अटल व्योम qoriq_पंचांगu_action(व्योम *p)
अणु
	काष्ठा qoriq_पंचांगu_data *data = p;

	regmap_ग_लिखो(data->regmap, REGS_TMR, TMR_DISABLE);
	clk_disable_unprepare(data->clk);
पूर्ण

अटल पूर्णांक qoriq_पंचांगu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	u32 ver;
	काष्ठा qoriq_पंचांगu_data *data;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	स्थिर bool little_endian = of_property_पढ़ो_bool(np, "little-endian");
	स्थिर क्रमागत regmap_endian क्रमmat_endian =
		little_endian ? REGMAP_ENDIAN_LITTLE : REGMAP_ENDIAN_BIG;
	स्थिर काष्ठा regmap_config regmap_config = अणु
		.reg_bits		= 32,
		.val_bits		= 32,
		.reg_stride		= 4,
		.rd_table		= &qoriq_rd_table,
		.wr_table		= &qoriq_wr_table,
		.val_क्रमmat_endian	= क्रमmat_endian,
		.max_रेजिस्टर		= SZ_4K,
	पूर्ण;
	व्योम __iomem *base;

	data = devm_kzalloc(dev, माप(काष्ठा qoriq_पंचांगu_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	ret = PTR_ERR_OR_ZERO(base);
	अगर (ret) अणु
		dev_err(dev, "Failed to get memory region\n");
		वापस ret;
	पूर्ण

	data->regmap = devm_regmap_init_mmio(dev, base, &regmap_config);
	ret = PTR_ERR_OR_ZERO(data->regmap);
	अगर (ret) अणु
		dev_err(dev, "Failed to init regmap (%d)\n", ret);
		वापस ret;
	पूर्ण

	data->clk = devm_clk_get_optional(dev, शून्य);
	अगर (IS_ERR(data->clk))
		वापस PTR_ERR(data->clk);

	ret = clk_prepare_enable(data->clk);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable clock\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(dev, qoriq_पंचांगu_action, data);
	अगर (ret)
		वापस ret;

	/* version रेजिस्टर offset at: 0xbf8 on both v1 and v2 */
	ret = regmap_पढ़ो(data->regmap, REGS_IPBRR(0), &ver);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to read IP block version\n");
		वापस ret;
	पूर्ण
	data->ver = (ver >> 8) & 0xff;

	qoriq_पंचांगu_init_device(data);	/* TMU initialization */

	ret = qoriq_पंचांगu_calibration(dev, data);	/* TMU calibration */
	अगर (ret < 0)
		वापस ret;

	ret = qoriq_पंचांगu_रेजिस्टर_पंचांगu_zone(dev, data);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to register sensors\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, data);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused qoriq_पंचांगu_suspend(काष्ठा device *dev)
अणु
	काष्ठा qoriq_पंचांगu_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regmap_update_bits(data->regmap, REGS_TMR, TMR_ME, 0);
	अगर (ret)
		वापस ret;

	clk_disable_unprepare(data->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused qoriq_पंचांगu_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा qoriq_पंचांगu_data *data = dev_get_drvdata(dev);

	ret = clk_prepare_enable(data->clk);
	अगर (ret)
		वापस ret;

	/* Enable monitoring */
	वापस regmap_update_bits(data->regmap, REGS_TMR, TMR_ME, TMR_ME);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(qoriq_पंचांगu_pm_ops,
			 qoriq_पंचांगu_suspend, qoriq_पंचांगu_resume);

अटल स्थिर काष्ठा of_device_id qoriq_पंचांगu_match[] = अणु
	अणु .compatible = "fsl,qoriq-tmu", पूर्ण,
	अणु .compatible = "fsl,imx8mq-tmu", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, qoriq_पंचांगu_match);

अटल काष्ठा platक्रमm_driver qoriq_पंचांगu = अणु
	.driver	= अणु
		.name		= "qoriq_thermal",
		.pm		= &qoriq_पंचांगu_pm_ops,
		.of_match_table	= qoriq_पंचांगu_match,
	पूर्ण,
	.probe	= qoriq_पंचांगu_probe,
पूर्ण;
module_platक्रमm_driver(qoriq_पंचांगu);

MODULE_AUTHOR("Jia Hongtao <hongtao.jia@nxp.com>");
MODULE_DESCRIPTION("QorIQ Thermal Monitoring Unit driver");
MODULE_LICENSE("GPL v2");
