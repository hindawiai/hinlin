<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  R-Car Gen3 THS thermal sensor driver
 *  Based on rcar_thermal.c and work from Hien Dang and Khiem Nguyen.
 *
 * Copyright (C) 2016 Renesas Electronics Corporation.
 * Copyright (C) 2016 Sang Engineering
 */
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sys_soc.h>
#समावेश <linux/thermal.h>

#समावेश "thermal_core.h"
#समावेश "thermal_hwmon.h"

/* Register offsets */
#घोषणा REG_GEN3_IRQSTR		0x04
#घोषणा REG_GEN3_IRQMSK		0x08
#घोषणा REG_GEN3_IRQCTL		0x0C
#घोषणा REG_GEN3_IRQEN		0x10
#घोषणा REG_GEN3_IRQTEMP1	0x14
#घोषणा REG_GEN3_IRQTEMP2	0x18
#घोषणा REG_GEN3_IRQTEMP3	0x1C
#घोषणा REG_GEN3_CTSR		0x20
#घोषणा REG_GEN3_THCTR		0x20
#घोषणा REG_GEN3_TEMP		0x28
#घोषणा REG_GEN3_THCODE1	0x50
#घोषणा REG_GEN3_THCODE2	0x54
#घोषणा REG_GEN3_THCODE3	0x58

/* IRQअणुSTR,MSK,ENपूर्ण bits */
#घोषणा IRQ_TEMP1		BIT(0)
#घोषणा IRQ_TEMP2		BIT(1)
#घोषणा IRQ_TEMP3		BIT(2)
#घोषणा IRQ_TEMPD1		BIT(3)
#घोषणा IRQ_TEMPD2		BIT(4)
#घोषणा IRQ_TEMPD3		BIT(5)

/* CTSR bits */
#घोषणा CTSR_PONM	BIT(8)
#घोषणा CTSR_AOUT	BIT(7)
#घोषणा CTSR_THBGR	BIT(5)
#घोषणा CTSR_VMEN	BIT(4)
#घोषणा CTSR_VMST	BIT(1)
#घोषणा CTSR_THSST	BIT(0)

/* THCTR bits */
#घोषणा THCTR_PONM	BIT(6)
#घोषणा THCTR_THSST	BIT(0)

#घोषणा CTEMP_MASK	0xFFF

#घोषणा MCELSIUS(temp)	((temp) * 1000)
#घोषणा GEN3_FUSE_MASK	0xFFF

#घोषणा TSC_MAX_NUM	5

/* शेष THCODE values अगर FUSEs are missing */
अटल स्थिर पूर्णांक thcodes[TSC_MAX_NUM][3] = अणु
	अणु 3397, 2800, 2221 पूर्ण,
	अणु 3393, 2795, 2216 पूर्ण,
	अणु 3389, 2805, 2237 पूर्ण,
	अणु 3415, 2694, 2195 पूर्ण,
	अणु 3356, 2724, 2244 पूर्ण,
पूर्ण;

/* Structure क्रम thermal temperature calculation */
काष्ठा equation_coefs अणु
	पूर्णांक a1;
	पूर्णांक b1;
	पूर्णांक a2;
	पूर्णांक b2;
पूर्ण;

काष्ठा rcar_gen3_thermal_tsc अणु
	व्योम __iomem *base;
	काष्ठा thermal_zone_device *zone;
	काष्ठा equation_coefs coef;
	पूर्णांक tj_t;
	पूर्णांक id; /* thermal channel id */
पूर्ण;

काष्ठा rcar_gen3_thermal_priv अणु
	काष्ठा rcar_gen3_thermal_tsc *tscs[TSC_MAX_NUM];
	अचिन्हित पूर्णांक num_tscs;
	व्योम (*thermal_init)(काष्ठा rcar_gen3_thermal_tsc *tsc);
पूर्ण;

अटल अंतरभूत u32 rcar_gen3_thermal_पढ़ो(काष्ठा rcar_gen3_thermal_tsc *tsc,
					 u32 reg)
अणु
	वापस ioपढ़ो32(tsc->base + reg);
पूर्ण

अटल अंतरभूत व्योम rcar_gen3_thermal_ग_लिखो(काष्ठा rcar_gen3_thermal_tsc *tsc,
					   u32 reg, u32 data)
अणु
	ioग_लिखो32(data, tsc->base + reg);
पूर्ण

/*
 * Linear approximation क्रम temperature
 *
 * [reg] = [temp] * a + b => [temp] = ([reg] - b) / a
 *
 * The स्थिरants a and b are calculated using two triplets of पूर्णांक values PTAT
 * and THCODE. PTAT and THCODE can either be पढ़ो from hardware or use hard
 * coded values from driver. The क्रमmula to calculate a and b are taken from
 * BSP and sparsely करोcumented and understood.
 *
 * Examining the linear क्रमmula and the क्रमmula used to calculate स्थिरants a
 * and b जबतक knowing that the span क्रम PTAT and THCODE values are between
 * 0x000 and 0xfff the largest पूर्णांकeger possible is 0xfff * 0xfff == 0xffe001.
 * Integer also needs to be चिन्हित so that leaves 7 bits क्रम binary
 * fixed poपूर्णांक scaling.
 */

#घोषणा FIXPT_SHIFT 7
#घोषणा FIXPT_INT(_x) ((_x) << FIXPT_SHIFT)
#घोषणा INT_FIXPT(_x) ((_x) >> FIXPT_SHIFT)
#घोषणा FIXPT_DIV(_a, _b) DIV_ROUND_CLOSEST(((_a) << FIXPT_SHIFT), (_b))
#घोषणा FIXPT_TO_MCELSIUS(_x) ((_x) * 1000 >> FIXPT_SHIFT)

#घोषणा RCAR3_THERMAL_GRAN 500 /* mili Celsius */

/* no idea where these स्थिरants come from */
#घोषणा TJ_3 -41

अटल व्योम rcar_gen3_thermal_calc_coefs(काष्ठा rcar_gen3_thermal_tsc *tsc,
					 पूर्णांक *ptat, स्थिर पूर्णांक *thcode,
					 पूर्णांक ths_tj_1)
अणु
	/* TODO: Find करोcumentation and करोcument स्थिरant calculation क्रमmula */

	/*
	 * Division is not scaled in BSP and अगर scaled it might overflow
	 * the भागidend (4095 * 4095 << 14 > पूर्णांक_उच्च) so keep it unscaled
	 */
	tsc->tj_t = (FIXPT_INT((ptat[1] - ptat[2]) * 157)
		     / (ptat[0] - ptat[2])) + FIXPT_INT(TJ_3);

	tsc->coef.a1 = FIXPT_DIV(FIXPT_INT(thcode[1] - thcode[2]),
				 tsc->tj_t - FIXPT_INT(TJ_3));
	tsc->coef.b1 = FIXPT_INT(thcode[2]) - tsc->coef.a1 * TJ_3;

	tsc->coef.a2 = FIXPT_DIV(FIXPT_INT(thcode[1] - thcode[0]),
				 tsc->tj_t - FIXPT_INT(ths_tj_1));
	tsc->coef.b2 = FIXPT_INT(thcode[0]) - tsc->coef.a2 * ths_tj_1;
पूर्ण

अटल पूर्णांक rcar_gen3_thermal_round(पूर्णांक temp)
अणु
	पूर्णांक result, round_offs;

	round_offs = temp >= 0 ? RCAR3_THERMAL_GRAN / 2 :
		-RCAR3_THERMAL_GRAN / 2;
	result = (temp + round_offs) / RCAR3_THERMAL_GRAN;
	वापस result * RCAR3_THERMAL_GRAN;
पूर्ण

अटल पूर्णांक rcar_gen3_thermal_get_temp(व्योम *devdata, पूर्णांक *temp)
अणु
	काष्ठा rcar_gen3_thermal_tsc *tsc = devdata;
	पूर्णांक mcelsius, val;
	पूर्णांक reg;

	/* Read रेजिस्टर and convert to mili Celsius */
	reg = rcar_gen3_thermal_पढ़ो(tsc, REG_GEN3_TEMP) & CTEMP_MASK;

	अगर (reg <= thcodes[tsc->id][1])
		val = FIXPT_DIV(FIXPT_INT(reg) - tsc->coef.b1,
				tsc->coef.a1);
	अन्यथा
		val = FIXPT_DIV(FIXPT_INT(reg) - tsc->coef.b2,
				tsc->coef.a2);
	mcelsius = FIXPT_TO_MCELSIUS(val);

	/* Guaranteed operating range is -40C to 125C. */

	/* Round value to device granularity setting */
	*temp = rcar_gen3_thermal_round(mcelsius);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops rcar_gen3_tz_of_ops = अणु
	.get_temp	= rcar_gen3_thermal_get_temp,
पूर्ण;

अटल स्थिर काष्ठा soc_device_attribute r8a7795es1[] = अणु
	अणु .soc_id = "r8a7795", .revision = "ES1.*" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल व्योम rcar_gen3_thermal_init_r8a7795es1(काष्ठा rcar_gen3_thermal_tsc *tsc)
अणु
	rcar_gen3_thermal_ग_लिखो(tsc, REG_GEN3_CTSR,  CTSR_THBGR);
	rcar_gen3_thermal_ग_लिखो(tsc, REG_GEN3_CTSR,  0x0);

	usleep_range(1000, 2000);

	rcar_gen3_thermal_ग_लिखो(tsc, REG_GEN3_CTSR, CTSR_PONM);

	rcar_gen3_thermal_ग_लिखो(tsc, REG_GEN3_IRQCTL, 0x3F);
	rcar_gen3_thermal_ग_लिखो(tsc, REG_GEN3_IRQMSK, 0);

	rcar_gen3_thermal_ग_लिखो(tsc, REG_GEN3_CTSR,
				CTSR_PONM | CTSR_AOUT | CTSR_THBGR | CTSR_VMEN);

	usleep_range(100, 200);

	rcar_gen3_thermal_ग_लिखो(tsc, REG_GEN3_CTSR,
				CTSR_PONM | CTSR_AOUT | CTSR_THBGR | CTSR_VMEN |
				CTSR_VMST | CTSR_THSST);

	usleep_range(1000, 2000);
पूर्ण

अटल व्योम rcar_gen3_thermal_init(काष्ठा rcar_gen3_thermal_tsc *tsc)
अणु
	u32 reg_val;

	reg_val = rcar_gen3_thermal_पढ़ो(tsc, REG_GEN3_THCTR);
	reg_val &= ~THCTR_PONM;
	rcar_gen3_thermal_ग_लिखो(tsc, REG_GEN3_THCTR, reg_val);

	usleep_range(1000, 2000);

	rcar_gen3_thermal_ग_लिखो(tsc, REG_GEN3_IRQCTL, 0);
	rcar_gen3_thermal_ग_लिखो(tsc, REG_GEN3_IRQMSK, 0);

	reg_val = rcar_gen3_thermal_पढ़ो(tsc, REG_GEN3_THCTR);
	reg_val |= THCTR_THSST;
	rcar_gen3_thermal_ग_लिखो(tsc, REG_GEN3_THCTR, reg_val);

	usleep_range(1000, 2000);
पूर्ण

अटल स्थिर पूर्णांक rcar_gen3_ths_tj_1 = 126;
अटल स्थिर पूर्णांक rcar_gen3_ths_tj_1_m3_w = 116;
अटल स्थिर काष्ठा of_device_id rcar_gen3_thermal_dt_ids[] = अणु
	अणु
		.compatible = "renesas,r8a774a1-thermal",
		.data = &rcar_gen3_ths_tj_1_m3_w,
	पूर्ण,
	अणु
		.compatible = "renesas,r8a774b1-thermal",
		.data = &rcar_gen3_ths_tj_1,
	पूर्ण,
	अणु
		.compatible = "renesas,r8a774e1-thermal",
		.data = &rcar_gen3_ths_tj_1,
	पूर्ण,
	अणु
		.compatible = "renesas,r8a7795-thermal",
		.data = &rcar_gen3_ths_tj_1,
	पूर्ण,
	अणु
		.compatible = "renesas,r8a7796-thermal",
		.data = &rcar_gen3_ths_tj_1_m3_w,
	पूर्ण,
	अणु
		.compatible = "renesas,r8a77961-thermal",
		.data = &rcar_gen3_ths_tj_1_m3_w,
	पूर्ण,
	अणु
		.compatible = "renesas,r8a77965-thermal",
		.data = &rcar_gen3_ths_tj_1,
	पूर्ण,
	अणु
		.compatible = "renesas,r8a77980-thermal",
		.data = &rcar_gen3_ths_tj_1,
	पूर्ण,
	अणु
		.compatible = "renesas,r8a779a0-thermal",
		.data = &rcar_gen3_ths_tj_1,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rcar_gen3_thermal_dt_ids);

अटल पूर्णांक rcar_gen3_thermal_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;

	pm_runसमय_put(dev);
	pm_runसमय_disable(dev);

	वापस 0;
पूर्ण

अटल व्योम rcar_gen3_hwmon_action(व्योम *data)
अणु
	काष्ठा thermal_zone_device *zone = data;

	thermal_हटाओ_hwmon_sysfs(zone);
पूर्ण

अटल पूर्णांक rcar_gen3_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_gen3_thermal_priv *priv;
	काष्ठा device *dev = &pdev->dev;
	स्थिर पूर्णांक *rcar_gen3_ths_tj_1 = of_device_get_match_data(dev);
	काष्ठा resource *res;
	काष्ठा thermal_zone_device *zone;
	पूर्णांक ret, i;

	/* शेष values अगर FUSEs are missing */
	/* TODO: Read values from hardware on supported platक्रमms */
	पूर्णांक ptat[3] = अणु 2631, 1509, 435 पूर्ण;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->thermal_init = rcar_gen3_thermal_init;
	अगर (soc_device_match(r8a7795es1))
		priv->thermal_init = rcar_gen3_thermal_init_r8a7795es1;

	platक्रमm_set_drvdata(pdev, priv);

	pm_runसमय_enable(dev);
	pm_runसमय_get_sync(dev);

	क्रम (i = 0; i < TSC_MAX_NUM; i++) अणु
		काष्ठा rcar_gen3_thermal_tsc *tsc;

		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, i);
		अगर (!res)
			अवरोध;

		tsc = devm_kzalloc(dev, माप(*tsc), GFP_KERNEL);
		अगर (!tsc) अणु
			ret = -ENOMEM;
			जाओ error_unरेजिस्टर;
		पूर्ण

		tsc->base = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(tsc->base)) अणु
			ret = PTR_ERR(tsc->base);
			जाओ error_unरेजिस्टर;
		पूर्ण
		tsc->id = i;

		priv->tscs[i] = tsc;

		priv->thermal_init(tsc);
		rcar_gen3_thermal_calc_coefs(tsc, ptat, thcodes[i],
					     *rcar_gen3_ths_tj_1);

		zone = devm_thermal_zone_of_sensor_रेजिस्टर(dev, i, tsc,
							    &rcar_gen3_tz_of_ops);
		अगर (IS_ERR(zone)) अणु
			dev_err(dev, "Can't register thermal zone\n");
			ret = PTR_ERR(zone);
			जाओ error_unरेजिस्टर;
		पूर्ण
		tsc->zone = zone;

		tsc->zone->tzp->no_hwmon = false;
		ret = thermal_add_hwmon_sysfs(tsc->zone);
		अगर (ret)
			जाओ error_unरेजिस्टर;

		ret = devm_add_action_or_reset(dev, rcar_gen3_hwmon_action, zone);
		अगर (ret)
			जाओ error_unरेजिस्टर;

		ret = of_thermal_get_ntrips(tsc->zone);
		अगर (ret < 0)
			जाओ error_unरेजिस्टर;

		dev_info(dev, "TSC%d: Loaded %d trip points\n", i, ret);
	पूर्ण

	priv->num_tscs = i;

	अगर (!priv->num_tscs) अणु
		ret = -ENODEV;
		जाओ error_unरेजिस्टर;
	पूर्ण

	वापस 0;

error_unरेजिस्टर:
	rcar_gen3_thermal_हटाओ(pdev);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused rcar_gen3_thermal_resume(काष्ठा device *dev)
अणु
	काष्ठा rcar_gen3_thermal_priv *priv = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < priv->num_tscs; i++) अणु
		काष्ठा rcar_gen3_thermal_tsc *tsc = priv->tscs[i];

		priv->thermal_init(tsc);
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(rcar_gen3_thermal_pm_ops, शून्य,
			 rcar_gen3_thermal_resume);

अटल काष्ठा platक्रमm_driver rcar_gen3_thermal_driver = अणु
	.driver	= अणु
		.name	= "rcar_gen3_thermal",
		.pm = &rcar_gen3_thermal_pm_ops,
		.of_match_table = rcar_gen3_thermal_dt_ids,
	पूर्ण,
	.probe		= rcar_gen3_thermal_probe,
	.हटाओ		= rcar_gen3_thermal_हटाओ,
पूर्ण;
module_platक्रमm_driver(rcar_gen3_thermal_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("R-Car Gen3 THS thermal sensor driver");
MODULE_AUTHOR("Wolfram Sang <wsa+renesas@sang-engineering.com>");
