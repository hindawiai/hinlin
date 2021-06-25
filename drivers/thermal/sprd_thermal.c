<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2020 Spपढ़ोtrum Communications Inc.

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/thermal.h>

#घोषणा SPRD_THM_CTL			0x0
#घोषणा SPRD_THM_INT_EN			0x4
#घोषणा SPRD_THM_INT_STS		0x8
#घोषणा SPRD_THM_INT_RAW_STS		0xc
#घोषणा SPRD_THM_DET_PERIOD		0x10
#घोषणा SPRD_THM_INT_CLR		0x14
#घोषणा SPRD_THM_INT_CLR_ST		0x18
#घोषणा SPRD_THM_MON_PERIOD		0x4c
#घोषणा SPRD_THM_MON_CTL		0x50
#घोषणा SPRD_THM_INTERNAL_STS1		0x54
#घोषणा SPRD_THM_RAW_READ_MSK		0x3ff

#घोषणा SPRD_THM_OFFSET(id)		((id) * 0x4)
#घोषणा SPRD_THM_TEMP(id)		(SPRD_THM_OFFSET(id) + 0x5c)
#घोषणा SPRD_THM_THRES(id)		(SPRD_THM_OFFSET(id) + 0x2c)

#घोषणा SPRD_THM_SEN(id)		BIT((id) + 2)
#घोषणा SPRD_THM_SEN_OVERHEAT_EN(id)	BIT((id) + 8)
#घोषणा SPRD_THM_SEN_OVERHEAT_ALARM_EN(id)	BIT((id) + 0)

/* bits definitions क्रम रेजिस्टर THM_CTL */
#घोषणा SPRD_THM_SET_RDY_ST		BIT(13)
#घोषणा SPRD_THM_SET_RDY		BIT(12)
#घोषणा SPRD_THM_MON_EN			BIT(1)
#घोषणा SPRD_THM_EN			BIT(0)

/* bits definitions क्रम रेजिस्टर THM_INT_CTL */
#घोषणा SPRD_THM_BIT_INT_EN		BIT(26)
#घोषणा SPRD_THM_OVERHEAT_EN		BIT(25)
#घोषणा SPRD_THM_OTP_TRIP_SHIFT		10

/* bits definitions क्रम रेजिस्टर SPRD_THM_INTERNAL_STS1 */
#घोषणा SPRD_THM_TEMPER_RDY		BIT(0)

#घोषणा SPRD_THM_DET_PERIOD_DATA	0x800
#घोषणा SPRD_THM_DET_PERIOD_MASK	GENMASK(19, 0)
#घोषणा SPRD_THM_MON_MODE		0x7
#घोषणा SPRD_THM_MON_MODE_MASK		GENMASK(3, 0)
#घोषणा SPRD_THM_MON_PERIOD_DATA	0x10
#घोषणा SPRD_THM_MON_PERIOD_MASK	GENMASK(15, 0)
#घोषणा SPRD_THM_THRES_MASK		GENMASK(19, 0)
#घोषणा SPRD_THM_INT_CLR_MASK		GENMASK(24, 0)

/* thermal sensor calibration parameters */
#घोषणा SPRD_THM_TEMP_LOW		-40000
#घोषणा SPRD_THM_TEMP_HIGH		120000
#घोषणा SPRD_THM_OTP_TEMP		120000
#घोषणा SPRD_THM_HOT_TEMP		75000
#घोषणा SPRD_THM_RAW_DATA_LOW		0
#घोषणा SPRD_THM_RAW_DATA_HIGH		1000
#घोषणा SPRD_THM_SEN_NUM		8
#घोषणा SPRD_THM_DT_OFFSET		24
#घोषणा SPRD_THM_RATION_OFFSET		17
#घोषणा SPRD_THM_RATION_SIGN		16

#घोषणा SPRD_THM_RDYST_POLLING_TIME	10
#घोषणा SPRD_THM_RDYST_TIMEOUT		700
#घोषणा SPRD_THM_TEMP_READY_POLL_TIME	10000
#घोषणा SPRD_THM_TEMP_READY_TIMEOUT	600000
#घोषणा SPRD_THM_MAX_SENSOR		8

काष्ठा sprd_thermal_sensor अणु
	काष्ठा thermal_zone_device *tzd;
	काष्ठा sprd_thermal_data *data;
	काष्ठा device *dev;
	पूर्णांक cal_slope;
	पूर्णांक cal_offset;
	पूर्णांक id;
पूर्ण;

काष्ठा sprd_thermal_data अणु
	स्थिर काष्ठा sprd_thm_variant_data *var_data;
	काष्ठा sprd_thermal_sensor *sensor[SPRD_THM_MAX_SENSOR];
	काष्ठा clk *clk;
	व्योम __iomem *base;
	u32 ratio_off;
	पूर्णांक ratio_sign;
	पूर्णांक nr_sensors;
पूर्ण;

/*
 * The conversion between ADC and temperature is based on linear relationship,
 * and use idea_k to specअगरy the slope and ideal_b to specअगरy the offset.
 *
 * Since dअगरferent Spपढ़ोtrum SoCs have dअगरferent ideal_k and ideal_b,
 * we should save ideal_k and ideal_b in the device data काष्ठाure.
 */
काष्ठा sprd_thm_variant_data अणु
	u32 ideal_k;
	u32 ideal_b;
पूर्ण;

अटल स्थिर काष्ठा sprd_thm_variant_data ums512_data = अणु
	.ideal_k = 262,
	.ideal_b = 66400,
पूर्ण;

अटल अंतरभूत व्योम sprd_thm_update_bits(व्योम __iomem *reg, u32 mask, u32 val)
अणु
	u32 पंचांगp, orig;

	orig = पढ़ोl(reg);
	पंचांगp = orig & ~mask;
	पंचांगp |= val & mask;
	ग_लिखोl(पंचांगp, reg);
पूर्ण

अटल पूर्णांक sprd_thm_cal_पढ़ो(काष्ठा device_node *np, स्थिर अक्षर *cell_id,
			     u32 *val)
अणु
	काष्ठा nvmem_cell *cell;
	व्योम *buf;
	माप_प्रकार len;

	cell = of_nvmem_cell_get(np, cell_id);
	अगर (IS_ERR(cell))
		वापस PTR_ERR(cell);

	buf = nvmem_cell_पढ़ो(cell, &len);
	nvmem_cell_put(cell);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	अगर (len > माप(u32)) अणु
		kमुक्त(buf);
		वापस -EINVAL;
	पूर्ण

	स_नकल(val, buf, len);

	kमुक्त(buf);
	वापस 0;
पूर्ण

अटल पूर्णांक sprd_thm_sensor_calibration(काष्ठा device_node *np,
				       काष्ठा sprd_thermal_data *thm,
				       काष्ठा sprd_thermal_sensor *sen)
अणु
	पूर्णांक ret;
	/*
	 * According to thermal datasheet, the शेष calibration offset is 64,
	 * and the शेष ratio is 1000.
	 */
	पूर्णांक dt_offset = 64, ratio = 1000;

	ret = sprd_thm_cal_पढ़ो(np, "sen_delta_cal", &dt_offset);
	अगर (ret)
		वापस ret;

	ratio += thm->ratio_sign * thm->ratio_off;

	/*
	 * According to the ideal slope K and ideal offset B, combined with
	 * calibration value of thermal from efuse, then calibrate the real
	 * slope k and offset b:
	 * k_cal = (k * ratio) / 1000.
	 * b_cal = b + (dt_offset - 64) * 500.
	 */
	sen->cal_slope = (thm->var_data->ideal_k * ratio) / 1000;
	sen->cal_offset = thm->var_data->ideal_b + (dt_offset - 128) * 250;

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_thm_rawdata_to_temp(काष्ठा sprd_thermal_sensor *sen,
				    u32 rawdata)
अणु
	clamp(rawdata, (u32)SPRD_THM_RAW_DATA_LOW, (u32)SPRD_THM_RAW_DATA_HIGH);

	/*
	 * According to the thermal datasheet, the क्रमmula of converting
	 * adc value to the temperature value should be:
	 * T_final = k_cal * x - b_cal.
	 */
	वापस sen->cal_slope * rawdata - sen->cal_offset;
पूर्ण

अटल पूर्णांक sprd_thm_temp_to_rawdata(पूर्णांक temp, काष्ठा sprd_thermal_sensor *sen)
अणु
	u32 val;

	clamp(temp, (पूर्णांक)SPRD_THM_TEMP_LOW, (पूर्णांक)SPRD_THM_TEMP_HIGH);

	/*
	 * According to the thermal datasheet, the क्रमmula of converting
	 * adc value to the temperature value should be:
	 * T_final = k_cal * x - b_cal.
	 */
	val = (temp + sen->cal_offset) / sen->cal_slope;

	वापस clamp(val, val, (u32)(SPRD_THM_RAW_DATA_HIGH - 1));
पूर्ण

अटल पूर्णांक sprd_thm_पढ़ो_temp(व्योम *devdata, पूर्णांक *temp)
अणु
	काष्ठा sprd_thermal_sensor *sen = devdata;
	u32 data;

	data = पढ़ोl(sen->data->base + SPRD_THM_TEMP(sen->id)) &
		SPRD_THM_RAW_READ_MSK;

	*temp = sprd_thm_rawdata_to_temp(sen, data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops sprd_thm_ops = अणु
	.get_temp = sprd_thm_पढ़ो_temp,
पूर्ण;

अटल पूर्णांक sprd_thm_poll_पढ़ोy_status(काष्ठा sprd_thermal_data *thm)
अणु
	u32 val;
	पूर्णांक ret;

	/*
	 * Wait क्रम thermal पढ़ोy status beक्रमe configuring thermal parameters.
	 */
	ret = पढ़ोl_poll_समयout(thm->base + SPRD_THM_CTL, val,
				 !(val & SPRD_THM_SET_RDY_ST),
				 SPRD_THM_RDYST_POLLING_TIME,
				 SPRD_THM_RDYST_TIMEOUT);
	अगर (ret)
		वापस ret;

	sprd_thm_update_bits(thm->base + SPRD_THM_CTL, SPRD_THM_MON_EN,
			     SPRD_THM_MON_EN);
	sprd_thm_update_bits(thm->base + SPRD_THM_CTL, SPRD_THM_SET_RDY,
			     SPRD_THM_SET_RDY);
	वापस 0;
पूर्ण

अटल पूर्णांक sprd_thm_रुको_temp_पढ़ोy(काष्ठा sprd_thermal_data *thm)
अणु
	u32 val;

	/* Wait क्रम first temperature data पढ़ोy beक्रमe पढ़ोing temperature */
	वापस पढ़ोl_poll_समयout(thm->base + SPRD_THM_INTERNAL_STS1, val,
				  !(val & SPRD_THM_TEMPER_RDY),
				  SPRD_THM_TEMP_READY_POLL_TIME,
				  SPRD_THM_TEMP_READY_TIMEOUT);
पूर्ण

अटल पूर्णांक sprd_thm_set_पढ़ोy(काष्ठा sprd_thermal_data *thm)
अणु
	पूर्णांक ret;

	ret = sprd_thm_poll_पढ़ोy_status(thm);
	अगर (ret)
		वापस ret;

	/*
	 * Clear पूर्णांकerrupt status, enable thermal पूर्णांकerrupt and enable thermal.
	 *
	 * The SPRD thermal controller पूर्णांकegrates a hardware पूर्णांकerrupt संकेत,
	 * which means अगर the temperature is overheat, it will generate an
	 * पूर्णांकerrupt and notअगरy the event to PMIC स्वतःmatically to shutकरोwn the
	 * प्रणाली. So here we should enable the पूर्णांकerrupt bits, though we have
	 * not रेजिस्टरed an irq handler.
	 */
	ग_लिखोl(SPRD_THM_INT_CLR_MASK, thm->base + SPRD_THM_INT_CLR);
	sprd_thm_update_bits(thm->base + SPRD_THM_INT_EN,
			     SPRD_THM_BIT_INT_EN, SPRD_THM_BIT_INT_EN);
	sprd_thm_update_bits(thm->base + SPRD_THM_CTL,
			     SPRD_THM_EN, SPRD_THM_EN);
	वापस 0;
पूर्ण

अटल व्योम sprd_thm_sensor_init(काष्ठा sprd_thermal_data *thm,
				 काष्ठा sprd_thermal_sensor *sen)
अणु
	u32 otp_rawdata, hot_rawdata;

	otp_rawdata = sprd_thm_temp_to_rawdata(SPRD_THM_OTP_TEMP, sen);
	hot_rawdata = sprd_thm_temp_to_rawdata(SPRD_THM_HOT_TEMP, sen);

	/* Enable the sensor' overheat temperature protection पूर्णांकerrupt */
	sprd_thm_update_bits(thm->base + SPRD_THM_INT_EN,
			     SPRD_THM_SEN_OVERHEAT_ALARM_EN(sen->id),
			     SPRD_THM_SEN_OVERHEAT_ALARM_EN(sen->id));

	/* Set the sensor' overheat and hot threshold temperature */
	sprd_thm_update_bits(thm->base + SPRD_THM_THRES(sen->id),
			     SPRD_THM_THRES_MASK,
			     (otp_rawdata << SPRD_THM_OTP_TRIP_SHIFT) |
			     hot_rawdata);

	/* Enable the corresponding sensor */
	sprd_thm_update_bits(thm->base + SPRD_THM_CTL, SPRD_THM_SEN(sen->id),
			     SPRD_THM_SEN(sen->id));
पूर्ण

अटल व्योम sprd_thm_para_config(काष्ठा sprd_thermal_data *thm)
अणु
	/* Set the period of two valid temperature detection action */
	sprd_thm_update_bits(thm->base + SPRD_THM_DET_PERIOD,
			     SPRD_THM_DET_PERIOD_MASK, SPRD_THM_DET_PERIOD);

	/* Set the sensors' monitor mode */
	sprd_thm_update_bits(thm->base + SPRD_THM_MON_CTL,
			     SPRD_THM_MON_MODE_MASK, SPRD_THM_MON_MODE);

	/* Set the sensors' monitor period */
	sprd_thm_update_bits(thm->base + SPRD_THM_MON_PERIOD,
			     SPRD_THM_MON_PERIOD_MASK, SPRD_THM_MON_PERIOD);
पूर्ण

अटल व्योम sprd_thm_toggle_sensor(काष्ठा sprd_thermal_sensor *sen, bool on)
अणु
	काष्ठा thermal_zone_device *tzd = sen->tzd;

	अगर (on)
		thermal_zone_device_enable(tzd);
	अन्यथा
		thermal_zone_device_disable(tzd);
पूर्ण

अटल पूर्णांक sprd_thm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *sen_child;
	काष्ठा sprd_thermal_data *thm;
	काष्ठा sprd_thermal_sensor *sen;
	स्थिर काष्ठा sprd_thm_variant_data *pdata;
	पूर्णांक ret, i;
	u32 val;

	pdata = of_device_get_match_data(&pdev->dev);
	अगर (!pdata) अणु
		dev_err(&pdev->dev, "No matching driver data found\n");
		वापस -EINVAL;
	पूर्ण

	thm = devm_kzalloc(&pdev->dev, माप(*thm), GFP_KERNEL);
	अगर (!thm)
		वापस -ENOMEM;

	thm->var_data = pdata;
	thm->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(thm->base))
		वापस PTR_ERR(thm->base);

	thm->nr_sensors = of_get_child_count(np);
	अगर (thm->nr_sensors == 0 || thm->nr_sensors > SPRD_THM_MAX_SENSOR) अणु
		dev_err(&pdev->dev, "incorrect sensor count\n");
		वापस -EINVAL;
	पूर्ण

	thm->clk = devm_clk_get(&pdev->dev, "enable");
	अगर (IS_ERR(thm->clk)) अणु
		dev_err(&pdev->dev, "failed to get enable clock\n");
		वापस PTR_ERR(thm->clk);
	पूर्ण

	ret = clk_prepare_enable(thm->clk);
	अगर (ret)
		वापस ret;

	sprd_thm_para_config(thm);

	ret = sprd_thm_cal_पढ़ो(np, "thm_sign_cal", &val);
	अगर (ret)
		जाओ disable_clk;

	अगर (val > 0)
		thm->ratio_sign = -1;
	अन्यथा
		thm->ratio_sign = 1;

	ret = sprd_thm_cal_पढ़ो(np, "thm_ratio_cal", &thm->ratio_off);
	अगर (ret)
		जाओ disable_clk;

	क्रम_each_child_of_node(np, sen_child) अणु
		sen = devm_kzalloc(&pdev->dev, माप(*sen), GFP_KERNEL);
		अगर (!sen) अणु
			ret = -ENOMEM;
			जाओ disable_clk;
		पूर्ण

		sen->data = thm;
		sen->dev = &pdev->dev;

		ret = of_property_पढ़ो_u32(sen_child, "reg", &sen->id);
		अगर (ret) अणु
			dev_err(&pdev->dev, "get sensor reg failed");
			जाओ disable_clk;
		पूर्ण

		ret = sprd_thm_sensor_calibration(sen_child, thm, sen);
		अगर (ret) अणु
			dev_err(&pdev->dev, "efuse cal analysis failed");
			जाओ disable_clk;
		पूर्ण

		sprd_thm_sensor_init(thm, sen);

		sen->tzd = devm_thermal_zone_of_sensor_रेजिस्टर(sen->dev,
								sen->id,
								sen,
								&sprd_thm_ops);
		अगर (IS_ERR(sen->tzd)) अणु
			dev_err(&pdev->dev, "register thermal zone failed %d\n",
				sen->id);
			ret = PTR_ERR(sen->tzd);
			जाओ disable_clk;
		पूर्ण

		thm->sensor[sen->id] = sen;
	पूर्ण

	ret = sprd_thm_set_पढ़ोy(thm);
	अगर (ret)
		जाओ disable_clk;

	ret = sprd_thm_रुको_temp_पढ़ोy(thm);
	अगर (ret)
		जाओ disable_clk;

	क्रम (i = 0; i < thm->nr_sensors; i++)
		sprd_thm_toggle_sensor(thm->sensor[i], true);

	platक्रमm_set_drvdata(pdev, thm);
	वापस 0;

disable_clk:
	clk_disable_unprepare(thm->clk);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम sprd_thm_hw_suspend(काष्ठा sprd_thermal_data *thm)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < thm->nr_sensors; i++) अणु
		sprd_thm_update_bits(thm->base + SPRD_THM_CTL,
				     SPRD_THM_SEN(thm->sensor[i]->id), 0);
	पूर्ण

	sprd_thm_update_bits(thm->base + SPRD_THM_CTL,
			     SPRD_THM_EN, 0x0);
पूर्ण

अटल पूर्णांक sprd_thm_suspend(काष्ठा device *dev)
अणु
	काष्ठा sprd_thermal_data *thm = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = 0; i < thm->nr_sensors; i++)
		sprd_thm_toggle_sensor(thm->sensor[i], false);

	sprd_thm_hw_suspend(thm);
	clk_disable_unprepare(thm->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_thm_hw_resume(काष्ठा sprd_thermal_data *thm)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < thm->nr_sensors; i++) अणु
		sprd_thm_update_bits(thm->base + SPRD_THM_CTL,
				     SPRD_THM_SEN(thm->sensor[i]->id),
				     SPRD_THM_SEN(thm->sensor[i]->id));
	पूर्ण

	ret = sprd_thm_poll_पढ़ोy_status(thm);
	अगर (ret)
		वापस ret;

	ग_लिखोl(SPRD_THM_INT_CLR_MASK, thm->base + SPRD_THM_INT_CLR);
	sprd_thm_update_bits(thm->base + SPRD_THM_CTL,
			     SPRD_THM_EN, SPRD_THM_EN);
	वापस sprd_thm_रुको_temp_पढ़ोy(thm);
पूर्ण

अटल पूर्णांक sprd_thm_resume(काष्ठा device *dev)
अणु
	काष्ठा sprd_thermal_data *thm = dev_get_drvdata(dev);
	पूर्णांक ret, i;

	ret = clk_prepare_enable(thm->clk);
	अगर (ret)
		वापस ret;

	ret = sprd_thm_hw_resume(thm);
	अगर (ret)
		जाओ disable_clk;

	क्रम (i = 0; i < thm->nr_sensors; i++)
		sprd_thm_toggle_sensor(thm->sensor[i], true);

	वापस 0;

disable_clk:
	clk_disable_unprepare(thm->clk);
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sprd_thm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sprd_thermal_data *thm = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < thm->nr_sensors; i++) अणु
		sprd_thm_toggle_sensor(thm->sensor[i], false);
		devm_thermal_zone_of_sensor_unरेजिस्टर(&pdev->dev,
						       thm->sensor[i]->tzd);
	पूर्ण

	clk_disable_unprepare(thm->clk);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sprd_thermal_of_match[] = अणु
	अणु .compatible = "sprd,ums512-thermal", .data = &ums512_data पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dev_pm_ops sprd_thermal_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sprd_thm_suspend, sprd_thm_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver sprd_thermal_driver = अणु
	.probe = sprd_thm_probe,
	.हटाओ = sprd_thm_हटाओ,
	.driver = अणु
		.name = "sprd-thermal",
		.pm = &sprd_thermal_pm_ops,
		.of_match_table = sprd_thermal_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sprd_thermal_driver);

MODULE_AUTHOR("Freeman Liu <freeman.liu@unisoc.com>");
MODULE_DESCRIPTION("Spreadtrum thermal driver");
MODULE_LICENSE("GPL v2");
