<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/**
 * uniphier_thermal.c - Socionext UniPhier thermal driver
 * Copyright 2014      Panasonic Corporation
 * Copyright 2016-2017 Socionext Inc.
 * Author:
 *	Kunihiko Hayashi <hayashi.kunihiko@socionext.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/thermal.h>

#समावेश "thermal_core.h"

/*
 * block रेजिस्टरs
 * addresses are the offset from .block_base
 */
#घोषणा PVTCTLEN			0x0000
#घोषणा PVTCTLEN_EN			BIT(0)

#घोषणा PVTCTLMODE			0x0004
#घोषणा PVTCTLMODE_MASK			0xf
#घोषणा PVTCTLMODE_TEMPMON		0x5

#घोषणा EMONREPEAT			0x0040
#घोषणा EMONREPEAT_ENDLESS		BIT(24)
#घोषणा EMONREPEAT_PERIOD		GENMASK(3, 0)
#घोषणा EMONREPEAT_PERIOD_1000000	0x9

/*
 * common रेजिस्टरs
 * addresses are the offset from .map_base
 */
#घोषणा PVTCTLSEL			0x0900
#घोषणा PVTCTLSEL_MASK			GENMASK(2, 0)
#घोषणा PVTCTLSEL_MONITOR		0

#घोषणा SETALERT0			0x0910
#घोषणा SETALERT1			0x0914
#घोषणा SETALERT2			0x0918
#घोषणा SETALERT_TEMP_OVF		(GENMASK(7, 0) << 16)
#घोषणा SETALERT_TEMP_OVF_VALUE(val)	(((val) & GENMASK(7, 0)) << 16)
#घोषणा SETALERT_EN			BIT(0)

#घोषणा PMALERTINTCTL			0x0920
#घोषणा PMALERTINTCTL_CLR(ch)		BIT(4 * (ch) + 2)
#घोषणा PMALERTINTCTL_SET(ch)		BIT(4 * (ch) + 1)
#घोषणा PMALERTINTCTL_EN(ch)		BIT(4 * (ch) + 0)
#घोषणा PMALERTINTCTL_MASK		(GENMASK(10, 8) | GENMASK(6, 4) | \
					 GENMASK(2, 0))

#घोषणा TMOD				0x0928
#घोषणा TMOD_WIDTH			9

#घोषणा TMODCOEF			0x0e5c

#घोषणा TMODSETUP0_EN			BIT(30)
#घोषणा TMODSETUP0_VAL(val)		(((val) & GENMASK(13, 0)) << 16)
#घोषणा TMODSETUP1_EN			BIT(15)
#घोषणा TMODSETUP1_VAL(val)		((val) & GENMASK(14, 0))

/* SoC critical temperature */
#घोषणा CRITICAL_TEMP_LIMIT		(120 * 1000)

/* Max # of alert channels */
#घोषणा ALERT_CH_NUM			3

/* SoC specअगरic thermal sensor data */
काष्ठा uniphier_पंचांग_soc_data अणु
	u32 map_base;
	u32 block_base;
	u32 पंचांगod_setup_addr;
पूर्ण;

काष्ठा uniphier_पंचांग_dev अणु
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	bool alert_en[ALERT_CH_NUM];
	काष्ठा thermal_zone_device *tz_dev;
	स्थिर काष्ठा uniphier_पंचांग_soc_data *data;
पूर्ण;

अटल पूर्णांक uniphier_पंचांग_initialize_sensor(काष्ठा uniphier_पंचांग_dev *tdev)
अणु
	काष्ठा regmap *map = tdev->regmap;
	u32 val;
	u32 पंचांगod_calib[2];
	पूर्णांक ret;

	/* stop PVT */
	regmap_ग_लिखो_bits(map, tdev->data->block_base + PVTCTLEN,
			  PVTCTLEN_EN, 0);

	/*
	 * Since SoC has a calibrated value that was set in advance,
	 * TMODCOEF shows non-zero and PVT refers the value पूर्णांकernally.
	 *
	 * If TMODCOEF shows zero, the boards करोn't have the calibrated
	 * value, and the driver has to set शेष value from DT.
	 */
	ret = regmap_पढ़ो(map, tdev->data->map_base + TMODCOEF, &val);
	अगर (ret)
		वापस ret;
	अगर (!val) अणु
		/* look क्रम the शेष values in DT */
		ret = of_property_पढ़ो_u32_array(tdev->dev->of_node,
						 "socionext,tmod-calibration",
						 पंचांगod_calib,
						 ARRAY_SIZE(पंचांगod_calib));
		अगर (ret)
			वापस ret;

		regmap_ग_लिखो(map, tdev->data->पंचांगod_setup_addr,
			TMODSETUP0_EN | TMODSETUP0_VAL(पंचांगod_calib[0]) |
			TMODSETUP1_EN | TMODSETUP1_VAL(पंचांगod_calib[1]));
	पूर्ण

	/* select temperature mode */
	regmap_ग_लिखो_bits(map, tdev->data->block_base + PVTCTLMODE,
			  PVTCTLMODE_MASK, PVTCTLMODE_TEMPMON);

	/* set monitoring period */
	regmap_ग_लिखो_bits(map, tdev->data->block_base + EMONREPEAT,
			  EMONREPEAT_ENDLESS | EMONREPEAT_PERIOD,
			  EMONREPEAT_ENDLESS | EMONREPEAT_PERIOD_1000000);

	/* set monitor mode */
	regmap_ग_लिखो_bits(map, tdev->data->map_base + PVTCTLSEL,
			  PVTCTLSEL_MASK, PVTCTLSEL_MONITOR);

	वापस 0;
पूर्ण

अटल व्योम uniphier_पंचांग_set_alert(काष्ठा uniphier_पंचांग_dev *tdev, u32 ch,
				  u32 temp)
अणु
	काष्ठा regmap *map = tdev->regmap;

	/* set alert temperature */
	regmap_ग_लिखो_bits(map, tdev->data->map_base + SETALERT0 + (ch << 2),
			  SETALERT_EN | SETALERT_TEMP_OVF,
			  SETALERT_EN |
			  SETALERT_TEMP_OVF_VALUE(temp / 1000));
पूर्ण

अटल व्योम uniphier_पंचांग_enable_sensor(काष्ठा uniphier_पंचांग_dev *tdev)
अणु
	काष्ठा regmap *map = tdev->regmap;
	पूर्णांक i;
	u32 bits = 0;

	क्रम (i = 0; i < ALERT_CH_NUM; i++)
		अगर (tdev->alert_en[i])
			bits |= PMALERTINTCTL_EN(i);

	/* enable alert पूर्णांकerrupt */
	regmap_ग_लिखो_bits(map, tdev->data->map_base + PMALERTINTCTL,
			  PMALERTINTCTL_MASK, bits);

	/* start PVT */
	regmap_ग_लिखो_bits(map, tdev->data->block_base + PVTCTLEN,
			  PVTCTLEN_EN, PVTCTLEN_EN);

	usleep_range(700, 1500);	/* The spec note says at least 700us */
पूर्ण

अटल व्योम uniphier_पंचांग_disable_sensor(काष्ठा uniphier_पंचांग_dev *tdev)
अणु
	काष्ठा regmap *map = tdev->regmap;

	/* disable alert पूर्णांकerrupt */
	regmap_ग_लिखो_bits(map, tdev->data->map_base + PMALERTINTCTL,
			  PMALERTINTCTL_MASK, 0);

	/* stop PVT */
	regmap_ग_लिखो_bits(map, tdev->data->block_base + PVTCTLEN,
			  PVTCTLEN_EN, 0);

	usleep_range(1000, 2000);	/* The spec note says at least 1ms */
पूर्ण

अटल पूर्णांक uniphier_पंचांग_get_temp(व्योम *data, पूर्णांक *out_temp)
अणु
	काष्ठा uniphier_पंचांग_dev *tdev = data;
	काष्ठा regmap *map = tdev->regmap;
	पूर्णांक ret;
	u32 temp;

	ret = regmap_पढ़ो(map, tdev->data->map_base + TMOD, &temp);
	अगर (ret)
		वापस ret;

	/* MSB of the TMOD field is a sign bit */
	*out_temp = sign_extend32(temp, TMOD_WIDTH - 1) * 1000;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops uniphier_of_thermal_ops = अणु
	.get_temp = uniphier_पंचांग_get_temp,
पूर्ण;

अटल व्योम uniphier_पंचांग_irq_clear(काष्ठा uniphier_पंचांग_dev *tdev)
अणु
	u32 mask = 0, bits = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ALERT_CH_NUM; i++) अणु
		mask |= (PMALERTINTCTL_CLR(i) | PMALERTINTCTL_SET(i));
		bits |= PMALERTINTCTL_CLR(i);
	पूर्ण

	/* clear alert पूर्णांकerrupt */
	regmap_ग_लिखो_bits(tdev->regmap,
			  tdev->data->map_base + PMALERTINTCTL, mask, bits);
पूर्ण

अटल irqवापस_t uniphier_पंचांग_alarm_irq(पूर्णांक irq, व्योम *_tdev)
अणु
	काष्ठा uniphier_पंचांग_dev *tdev = _tdev;

	disable_irq_nosync(irq);
	uniphier_पंचांग_irq_clear(tdev);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t uniphier_पंचांग_alarm_irq_thपढ़ो(पूर्णांक irq, व्योम *_tdev)
अणु
	काष्ठा uniphier_पंचांग_dev *tdev = _tdev;

	thermal_zone_device_update(tdev->tz_dev, THERMAL_EVENT_UNSPECIFIED);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक uniphier_पंचांग_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा regmap *regmap;
	काष्ठा device_node *parent;
	काष्ठा uniphier_पंचांग_dev *tdev;
	स्थिर काष्ठा thermal_trip *trips;
	पूर्णांक i, ret, irq, ntrips, crit_temp = पूर्णांक_उच्च;

	tdev = devm_kzalloc(dev, माप(*tdev), GFP_KERNEL);
	अगर (!tdev)
		वापस -ENOMEM;
	tdev->dev = dev;

	tdev->data = of_device_get_match_data(dev);
	अगर (WARN_ON(!tdev->data))
		वापस -EINVAL;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	/* get regmap from syscon node */
	parent = of_get_parent(dev->of_node); /* parent should be syscon node */
	regmap = syscon_node_to_regmap(parent);
	of_node_put(parent);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "failed to get regmap (error %ld)\n",
			PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण
	tdev->regmap = regmap;

	ret = uniphier_पंचांग_initialize_sensor(tdev);
	अगर (ret) अणु
		dev_err(dev, "failed to initialize sensor\n");
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, irq, uniphier_पंचांग_alarm_irq,
					uniphier_पंचांग_alarm_irq_thपढ़ो,
					0, "thermal", tdev);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, tdev);

	tdev->tz_dev = devm_thermal_zone_of_sensor_रेजिस्टर(dev, 0, tdev,
						&uniphier_of_thermal_ops);
	अगर (IS_ERR(tdev->tz_dev)) अणु
		dev_err(dev, "failed to register sensor device\n");
		वापस PTR_ERR(tdev->tz_dev);
	पूर्ण

	/* get trip poपूर्णांकs */
	trips = of_thermal_get_trip_poपूर्णांकs(tdev->tz_dev);
	ntrips = of_thermal_get_ntrips(tdev->tz_dev);
	अगर (ntrips > ALERT_CH_NUM) अणु
		dev_err(dev, "thermal zone has too many trips\n");
		वापस -E2BIG;
	पूर्ण

	/* set alert temperatures */
	क्रम (i = 0; i < ntrips; i++) अणु
		अगर (trips[i].type == THERMAL_TRIP_CRITICAL &&
		    trips[i].temperature < crit_temp)
			crit_temp = trips[i].temperature;
		uniphier_पंचांग_set_alert(tdev, i, trips[i].temperature);
		tdev->alert_en[i] = true;
	पूर्ण
	अगर (crit_temp > CRITICAL_TEMP_LIMIT) अणु
		dev_err(dev, "critical trip is over limit(>%d), or not set\n",
			CRITICAL_TEMP_LIMIT);
		वापस -EINVAL;
	पूर्ण

	uniphier_पंचांग_enable_sensor(tdev);

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_पंचांग_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uniphier_पंचांग_dev *tdev = platक्रमm_get_drvdata(pdev);

	/* disable sensor */
	uniphier_पंचांग_disable_sensor(tdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा uniphier_पंचांग_soc_data uniphier_pxs2_पंचांग_data = अणु
	.map_base        = 0xe000,
	.block_base      = 0xe000,
	.पंचांगod_setup_addr = 0xe904,
पूर्ण;

अटल स्थिर काष्ठा uniphier_पंचांग_soc_data uniphier_ld20_पंचांग_data = अणु
	.map_base        = 0xe000,
	.block_base      = 0xe800,
	.पंचांगod_setup_addr = 0xe938,
पूर्ण;

अटल स्थिर काष्ठा of_device_id uniphier_पंचांग_dt_ids[] = अणु
	अणु
		.compatible = "socionext,uniphier-pxs2-thermal",
		.data       = &uniphier_pxs2_पंचांग_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-ld20-thermal",
		.data       = &uniphier_ld20_पंचांग_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs3-thermal",
		.data       = &uniphier_ld20_पंचांग_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, uniphier_पंचांग_dt_ids);

अटल काष्ठा platक्रमm_driver uniphier_पंचांग_driver = अणु
	.probe = uniphier_पंचांग_probe,
	.हटाओ = uniphier_पंचांग_हटाओ,
	.driver = अणु
		.name = "uniphier-thermal",
		.of_match_table = uniphier_पंचांग_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(uniphier_पंचांग_driver);

MODULE_AUTHOR("Kunihiko Hayashi <hayashi.kunihiko@socionext.com>");
MODULE_DESCRIPTION("UniPhier thermal driver");
MODULE_LICENSE("GPL v2");
