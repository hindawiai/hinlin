<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Thermal sensor driver क्रम Allwinner SOC
 * Copyright (C) 2019 Yangtao Li
 *
 * Based on the work of Icenowy Zheng <icenowy@aosc.io>
 * Based on the work of Ondrej Jirman <megous@megous.com>
 * Based on the work of Josef Gajdusek <atx@atx.name>
 */

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>
#समावेश <linux/thermal.h>

#समावेश "thermal_hwmon.h"

#घोषणा MAX_SENSOR_NUM	4

#घोषणा FT_TEMP_MASK				GENMASK(11, 0)
#घोषणा TEMP_CALIB_MASK				GENMASK(11, 0)
#घोषणा CALIBRATE_DEFAULT			0x800

#घोषणा SUN8I_THS_CTRL0				0x00
#घोषणा SUN8I_THS_CTRL2				0x40
#घोषणा SUN8I_THS_IC				0x44
#घोषणा SUN8I_THS_IS				0x48
#घोषणा SUN8I_THS_MFC				0x70
#घोषणा SUN8I_THS_TEMP_CALIB			0x74
#घोषणा SUN8I_THS_TEMP_DATA			0x80

#घोषणा SUN50I_THS_CTRL0			0x00
#घोषणा SUN50I_H6_THS_ENABLE			0x04
#घोषणा SUN50I_H6_THS_PC			0x08
#घोषणा SUN50I_H6_THS_DIC			0x10
#घोषणा SUN50I_H6_THS_DIS			0x20
#घोषणा SUN50I_H6_THS_MFC			0x30
#घोषणा SUN50I_H6_THS_TEMP_CALIB		0xa0
#घोषणा SUN50I_H6_THS_TEMP_DATA			0xc0

#घोषणा SUN8I_THS_CTRL0_T_ACQ0(x)		(GENMASK(15, 0) & (x))
#घोषणा SUN8I_THS_CTRL2_T_ACQ1(x)		((GENMASK(15, 0) & (x)) << 16)
#घोषणा SUN8I_THS_DATA_IRQ_STS(x)		BIT(x + 8)

#घोषणा SUN50I_THS_CTRL0_T_ACQ(x)		((GENMASK(15, 0) & (x)) << 16)
#घोषणा SUN50I_THS_FILTER_EN			BIT(2)
#घोषणा SUN50I_THS_FILTER_TYPE(x)		(GENMASK(1, 0) & (x))
#घोषणा SUN50I_H6_THS_PC_TEMP_PERIOD(x)		((GENMASK(19, 0) & (x)) << 12)
#घोषणा SUN50I_H6_THS_DATA_IRQ_STS(x)		BIT(x)

/* millidegree celsius */

काष्ठा tsensor अणु
	काष्ठा ths_device		*पंचांगdev;
	काष्ठा thermal_zone_device	*tzd;
	पूर्णांक				id;
पूर्ण;

काष्ठा ths_thermal_chip अणु
	bool            has_mod_clk;
	bool            has_bus_clk_reset;
	पूर्णांक		sensor_num;
	पूर्णांक		offset;
	पूर्णांक		scale;
	पूर्णांक		ft_deviation;
	पूर्णांक		temp_data_base;
	पूर्णांक		(*calibrate)(काष्ठा ths_device *पंचांगdev,
				     u16 *caldata, पूर्णांक callen);
	पूर्णांक		(*init)(काष्ठा ths_device *पंचांगdev);
	अचिन्हित दीर्घ	(*irq_ack)(काष्ठा ths_device *पंचांगdev);
	पूर्णांक		(*calc_temp)(काष्ठा ths_device *पंचांगdev,
				     पूर्णांक id, पूर्णांक reg);
पूर्ण;

काष्ठा ths_device अणु
	स्थिर काष्ठा ths_thermal_chip		*chip;
	काष्ठा device				*dev;
	काष्ठा regmap				*regmap;
	काष्ठा reset_control			*reset;
	काष्ठा clk				*bus_clk;
	काष्ठा clk                              *mod_clk;
	काष्ठा tsensor				sensor[MAX_SENSOR_NUM];
पूर्ण;

/* Temp Unit: millidegree Celsius */
अटल पूर्णांक sun8i_ths_calc_temp(काष्ठा ths_device *पंचांगdev,
			       पूर्णांक id, पूर्णांक reg)
अणु
	वापस पंचांगdev->chip->offset - (reg * पंचांगdev->chip->scale / 10);
पूर्ण

अटल पूर्णांक sun50i_h5_calc_temp(काष्ठा ths_device *पंचांगdev,
			       पूर्णांक id, पूर्णांक reg)
अणु
	अगर (reg >= 0x500)
		वापस -1191 * reg / 10 + 223000;
	अन्यथा अगर (!id)
		वापस -1452 * reg / 10 + 259000;
	अन्यथा
		वापस -1590 * reg / 10 + 276000;
पूर्ण

अटल पूर्णांक sun8i_ths_get_temp(व्योम *data, पूर्णांक *temp)
अणु
	काष्ठा tsensor *s = data;
	काष्ठा ths_device *पंचांगdev = s->पंचांगdev;
	पूर्णांक val = 0;

	regmap_पढ़ो(पंचांगdev->regmap, पंचांगdev->chip->temp_data_base +
		    0x4 * s->id, &val);

	/* ths have no data yet */
	अगर (!val)
		वापस -EAGAIN;

	*temp = पंचांगdev->chip->calc_temp(पंचांगdev, s->id, val);
	/*
	 * According to the original sdk, there are some platक्रमms(rarely)
	 * that add a fixed offset value after calculating the temperature
	 * value. We can't simply put it on the क्रमmula क्रम calculating the
	 * temperature above, because the क्रमmula क्रम calculating the
	 * temperature above is also used when the sensor is calibrated. If
	 * करो this, the correct calibration क्रमmula is hard to know.
	 */
	*temp += पंचांगdev->chip->ft_deviation;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops ths_ops = अणु
	.get_temp = sun8i_ths_get_temp,
पूर्ण;

अटल स्थिर काष्ठा regmap_config config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.fast_io = true,
	.max_रेजिस्टर = 0xfc,
पूर्ण;

अटल अचिन्हित दीर्घ sun8i_h3_irq_ack(काष्ठा ths_device *पंचांगdev)
अणु
	अचिन्हित दीर्घ irq_biपंचांगap = 0;
	पूर्णांक i, state;

	regmap_पढ़ो(पंचांगdev->regmap, SUN8I_THS_IS, &state);

	क्रम (i = 0; i < पंचांगdev->chip->sensor_num; i++) अणु
		अगर (state & SUN8I_THS_DATA_IRQ_STS(i)) अणु
			regmap_ग_लिखो(पंचांगdev->regmap, SUN8I_THS_IS,
				     SUN8I_THS_DATA_IRQ_STS(i));
			biपंचांगap_set(&irq_biपंचांगap, i, 1);
		पूर्ण
	पूर्ण

	वापस irq_biपंचांगap;
पूर्ण

अटल अचिन्हित दीर्घ sun50i_h6_irq_ack(काष्ठा ths_device *पंचांगdev)
अणु
	अचिन्हित दीर्घ irq_biपंचांगap = 0;
	पूर्णांक i, state;

	regmap_पढ़ो(पंचांगdev->regmap, SUN50I_H6_THS_DIS, &state);

	क्रम (i = 0; i < पंचांगdev->chip->sensor_num; i++) अणु
		अगर (state & SUN50I_H6_THS_DATA_IRQ_STS(i)) अणु
			regmap_ग_लिखो(पंचांगdev->regmap, SUN50I_H6_THS_DIS,
				     SUN50I_H6_THS_DATA_IRQ_STS(i));
			biपंचांगap_set(&irq_biपंचांगap, i, 1);
		पूर्ण
	पूर्ण

	वापस irq_biपंचांगap;
पूर्ण

अटल irqवापस_t sun8i_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ths_device *पंचांगdev = data;
	अचिन्हित दीर्घ irq_biपंचांगap = पंचांगdev->chip->irq_ack(पंचांगdev);
	पूर्णांक i;

	क्रम_each_set_bit(i, &irq_biपंचांगap, पंचांगdev->chip->sensor_num) अणु
		thermal_zone_device_update(पंचांगdev->sensor[i].tzd,
					   THERMAL_EVENT_UNSPECIFIED);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sun8i_h3_ths_calibrate(काष्ठा ths_device *पंचांगdev,
				  u16 *caldata, पूर्णांक callen)
अणु
	पूर्णांक i;

	अगर (!caldata[0] || callen < 2 * पंचांगdev->chip->sensor_num)
		वापस -EINVAL;

	क्रम (i = 0; i < पंचांगdev->chip->sensor_num; i++) अणु
		पूर्णांक offset = (i % 2) << 4;

		regmap_update_bits(पंचांगdev->regmap,
				   SUN8I_THS_TEMP_CALIB + (4 * (i >> 1)),
				   0xfff << offset,
				   caldata[i] << offset);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sun50i_h6_ths_calibrate(काष्ठा ths_device *पंचांगdev,
				   u16 *caldata, पूर्णांक callen)
अणु
	काष्ठा device *dev = पंचांगdev->dev;
	पूर्णांक i, ft_temp;

	अगर (!caldata[0] || callen < 2 + 2 * पंचांगdev->chip->sensor_num)
		वापस -EINVAL;

	/*
	 * efuse layout:
	 *
	 *	0   11  16	 32
	 *	+-------+-------+-------+
	 *	|temp|  |sensor0|sensor1|
	 *	+-------+-------+-------+
	 *
	 * The calibration data on the H6 is the ambient temperature and
	 * sensor values that are filled during the factory test stage.
	 *
	 * The unit of stored FT temperature is 0.1 degreee celusis.
	 *
	 * We need to calculate a delta between measured and caluclated
	 * रेजिस्टर values and this will become a calibration offset.
	 */
	ft_temp = (caldata[0] & FT_TEMP_MASK) * 100;

	क्रम (i = 0; i < पंचांगdev->chip->sensor_num; i++) अणु
		पूर्णांक sensor_reg = caldata[i + 1] & TEMP_CALIB_MASK;
		पूर्णांक cdata, offset;
		पूर्णांक sensor_temp = पंचांगdev->chip->calc_temp(पंचांगdev, i, sensor_reg);

		/*
		 * Calibration data is CALIBRATE_DEFAULT - (calculated
		 * temperature from sensor पढ़ोing at factory temperature
		 * minus actual factory temperature) * 14.88 (scale from
		 * temperature to रेजिस्टर values)
		 */
		cdata = CALIBRATE_DEFAULT -
			((sensor_temp - ft_temp) * 10 / पंचांगdev->chip->scale);
		अगर (cdata & ~TEMP_CALIB_MASK) अणु
			/*
			 * Calibration value more than 12-bit, but calibration
			 * रेजिस्टर is 12-bit. In this हाल, ths hardware can
			 * still work without calibration, although the data
			 * won't be so accurate.
			 */
			dev_warn(dev, "sensor%d is not calibrated.\n", i);
			जारी;
		पूर्ण

		offset = (i % 2) * 16;
		regmap_update_bits(पंचांगdev->regmap,
				   SUN50I_H6_THS_TEMP_CALIB + (i / 2 * 4),
				   0xfff << offset,
				   cdata << offset);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_ths_calibrate(काष्ठा ths_device *पंचांगdev)
अणु
	काष्ठा nvmem_cell *calcell;
	काष्ठा device *dev = पंचांगdev->dev;
	u16 *caldata;
	माप_प्रकार callen;
	पूर्णांक ret = 0;

	calcell = devm_nvmem_cell_get(dev, "calibration");
	अगर (IS_ERR(calcell)) अणु
		अगर (PTR_ERR(calcell) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		/*
		 * Even अगर the बाह्यal calibration data stored in sid is
		 * not accessible, the THS hardware can still work, although
		 * the data won't be so accurate.
		 *
		 * The शेष value of calibration रेजिस्टर is 0x800 क्रम
		 * every sensor, and the calibration value is usually 0x7xx
		 * or 0x8xx, so they won't be away from the शेष value
		 * क्रम a lot.
		 *
		 * So here we करो not वापस error अगर the calibration data is
		 * not available, except the probe needs deferring.
		 */
		जाओ out;
	पूर्ण

	caldata = nvmem_cell_पढ़ो(calcell, &callen);
	अगर (IS_ERR(caldata)) अणु
		ret = PTR_ERR(caldata);
		जाओ out;
	पूर्ण

	पंचांगdev->chip->calibrate(पंचांगdev, caldata, callen);

	kमुक्त(caldata);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक sun8i_ths_resource_init(काष्ठा ths_device *पंचांगdev)
अणु
	काष्ठा device *dev = पंचांगdev->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	व्योम __iomem *base;
	पूर्णांक ret;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	पंचांगdev->regmap = devm_regmap_init_mmio(dev, base, &config);
	अगर (IS_ERR(पंचांगdev->regmap))
		वापस PTR_ERR(पंचांगdev->regmap);

	अगर (पंचांगdev->chip->has_bus_clk_reset) अणु
		पंचांगdev->reset = devm_reset_control_get(dev, शून्य);
		अगर (IS_ERR(पंचांगdev->reset))
			वापस PTR_ERR(पंचांगdev->reset);

		पंचांगdev->bus_clk = devm_clk_get(&pdev->dev, "bus");
		अगर (IS_ERR(पंचांगdev->bus_clk))
			वापस PTR_ERR(पंचांगdev->bus_clk);
	पूर्ण

	अगर (पंचांगdev->chip->has_mod_clk) अणु
		पंचांगdev->mod_clk = devm_clk_get(&pdev->dev, "mod");
		अगर (IS_ERR(पंचांगdev->mod_clk))
			वापस PTR_ERR(पंचांगdev->mod_clk);
	पूर्ण

	ret = reset_control_deनिश्चित(पंचांगdev->reset);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(पंचांगdev->bus_clk);
	अगर (ret)
		जाओ निश्चित_reset;

	ret = clk_set_rate(पंचांगdev->mod_clk, 24000000);
	अगर (ret)
		जाओ bus_disable;

	ret = clk_prepare_enable(पंचांगdev->mod_clk);
	अगर (ret)
		जाओ bus_disable;

	ret = sun8i_ths_calibrate(पंचांगdev);
	अगर (ret)
		जाओ mod_disable;

	वापस 0;

mod_disable:
	clk_disable_unprepare(पंचांगdev->mod_clk);
bus_disable:
	clk_disable_unprepare(पंचांगdev->bus_clk);
निश्चित_reset:
	reset_control_निश्चित(पंचांगdev->reset);

	वापस ret;
पूर्ण

अटल पूर्णांक sun8i_h3_thermal_init(काष्ठा ths_device *पंचांगdev)
अणु
	पूर्णांक val;

	/* average over 4 samples */
	regmap_ग_लिखो(पंचांगdev->regmap, SUN8I_THS_MFC,
		     SUN50I_THS_FILTER_EN |
		     SUN50I_THS_FILTER_TYPE(1));
	/*
	 * clkin = 24MHz
	 * filter_samples = 4
	 * period = 0.25s
	 *
	 * x = period * clkin / 4096 / filter_samples - 1
	 *   = 365
	 */
	val = GENMASK(7 + पंचांगdev->chip->sensor_num, 8);
	regmap_ग_लिखो(पंचांगdev->regmap, SUN8I_THS_IC,
		     SUN50I_H6_THS_PC_TEMP_PERIOD(365) | val);
	/*
	 * T_acq = 20us
	 * clkin = 24MHz
	 *
	 * x = T_acq * clkin - 1
	 *   = 479
	 */
	regmap_ग_लिखो(पंचांगdev->regmap, SUN8I_THS_CTRL0,
		     SUN8I_THS_CTRL0_T_ACQ0(479));
	val = GENMASK(पंचांगdev->chip->sensor_num - 1, 0);
	regmap_ग_लिखो(पंचांगdev->regmap, SUN8I_THS_CTRL2,
		     SUN8I_THS_CTRL2_T_ACQ1(479) | val);

	वापस 0;
पूर्ण

/*
 * Without this unकरोcumented value, the वापसed temperatures would
 * be higher than real ones by about 20C.
 */
#घोषणा SUN50I_H6_CTRL0_UNK 0x0000002f

अटल पूर्णांक sun50i_h6_thermal_init(काष्ठा ths_device *पंचांगdev)
अणु
	पूर्णांक val;

	/*
	 * T_acq = 20us
	 * clkin = 24MHz
	 *
	 * x = T_acq * clkin - 1
	 *   = 479
	 */
	regmap_ग_लिखो(पंचांगdev->regmap, SUN50I_THS_CTRL0,
		     SUN50I_H6_CTRL0_UNK | SUN50I_THS_CTRL0_T_ACQ(479));
	/* average over 4 samples */
	regmap_ग_लिखो(पंचांगdev->regmap, SUN50I_H6_THS_MFC,
		     SUN50I_THS_FILTER_EN |
		     SUN50I_THS_FILTER_TYPE(1));
	/*
	 * clkin = 24MHz
	 * filter_samples = 4
	 * period = 0.25s
	 *
	 * x = period * clkin / 4096 / filter_samples - 1
	 *   = 365
	 */
	regmap_ग_लिखो(पंचांगdev->regmap, SUN50I_H6_THS_PC,
		     SUN50I_H6_THS_PC_TEMP_PERIOD(365));
	/* enable sensor */
	val = GENMASK(पंचांगdev->chip->sensor_num - 1, 0);
	regmap_ग_लिखो(पंचांगdev->regmap, SUN50I_H6_THS_ENABLE, val);
	/* thermal data पूर्णांकerrupt enable */
	val = GENMASK(पंचांगdev->chip->sensor_num - 1, 0);
	regmap_ग_लिखो(पंचांगdev->regmap, SUN50I_H6_THS_DIC, val);

	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_ths_रेजिस्टर(काष्ठा ths_device *पंचांगdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < पंचांगdev->chip->sensor_num; i++) अणु
		पंचांगdev->sensor[i].पंचांगdev = पंचांगdev;
		पंचांगdev->sensor[i].id = i;
		पंचांगdev->sensor[i].tzd =
			devm_thermal_zone_of_sensor_रेजिस्टर(पंचांगdev->dev,
							     i,
							     &पंचांगdev->sensor[i],
							     &ths_ops);
		अगर (IS_ERR(पंचांगdev->sensor[i].tzd))
			वापस PTR_ERR(पंचांगdev->sensor[i].tzd);

		अगर (devm_thermal_add_hwmon_sysfs(पंचांगdev->sensor[i].tzd))
			dev_warn(पंचांगdev->dev,
				 "Failed to add hwmon sysfs attributes\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_ths_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ths_device *पंचांगdev;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret, irq;

	पंचांगdev = devm_kzalloc(dev, माप(*पंचांगdev), GFP_KERNEL);
	अगर (!पंचांगdev)
		वापस -ENOMEM;

	पंचांगdev->dev = dev;
	पंचांगdev->chip = of_device_get_match_data(&pdev->dev);
	अगर (!पंचांगdev->chip)
		वापस -EINVAL;

	platक्रमm_set_drvdata(pdev, पंचांगdev);

	ret = sun8i_ths_resource_init(पंचांगdev);
	अगर (ret)
		वापस ret;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = पंचांगdev->chip->init(पंचांगdev);
	अगर (ret)
		वापस ret;

	ret = sun8i_ths_रेजिस्टर(पंचांगdev);
	अगर (ret)
		वापस ret;

	/*
	 * Aव्योम entering the पूर्णांकerrupt handler, the thermal device is not
	 * रेजिस्टरed yet, we deffer the registration of the पूर्णांकerrupt to
	 * the end.
	 */
	ret = devm_request_thपढ़ोed_irq(dev, irq, शून्य,
					sun8i_irq_thपढ़ो,
					IRQF_ONESHOT, "ths", पंचांगdev);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_ths_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ths_device *पंचांगdev = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(पंचांगdev->mod_clk);
	clk_disable_unprepare(पंचांगdev->bus_clk);
	reset_control_निश्चित(पंचांगdev->reset);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ths_thermal_chip sun8i_a83t_ths = अणु
	.sensor_num = 3,
	.scale = 705,
	.offset = 191668,
	.temp_data_base = SUN8I_THS_TEMP_DATA,
	.calibrate = sun8i_h3_ths_calibrate,
	.init = sun8i_h3_thermal_init,
	.irq_ack = sun8i_h3_irq_ack,
	.calc_temp = sun8i_ths_calc_temp,
पूर्ण;

अटल स्थिर काष्ठा ths_thermal_chip sun8i_h3_ths = अणु
	.sensor_num = 1,
	.scale = 1211,
	.offset = 217000,
	.has_mod_clk = true,
	.has_bus_clk_reset = true,
	.temp_data_base = SUN8I_THS_TEMP_DATA,
	.calibrate = sun8i_h3_ths_calibrate,
	.init = sun8i_h3_thermal_init,
	.irq_ack = sun8i_h3_irq_ack,
	.calc_temp = sun8i_ths_calc_temp,
पूर्ण;

अटल स्थिर काष्ठा ths_thermal_chip sun8i_r40_ths = अणु
	.sensor_num = 2,
	.offset = 251086,
	.scale = 1130,
	.has_mod_clk = true,
	.has_bus_clk_reset = true,
	.temp_data_base = SUN8I_THS_TEMP_DATA,
	.calibrate = sun8i_h3_ths_calibrate,
	.init = sun8i_h3_thermal_init,
	.irq_ack = sun8i_h3_irq_ack,
	.calc_temp = sun8i_ths_calc_temp,
पूर्ण;

अटल स्थिर काष्ठा ths_thermal_chip sun50i_a64_ths = अणु
	.sensor_num = 3,
	.offset = 260890,
	.scale = 1170,
	.has_mod_clk = true,
	.has_bus_clk_reset = true,
	.temp_data_base = SUN8I_THS_TEMP_DATA,
	.calibrate = sun8i_h3_ths_calibrate,
	.init = sun8i_h3_thermal_init,
	.irq_ack = sun8i_h3_irq_ack,
	.calc_temp = sun8i_ths_calc_temp,
पूर्ण;

अटल स्थिर काष्ठा ths_thermal_chip sun50i_a100_ths = अणु
	.sensor_num = 3,
	.has_bus_clk_reset = true,
	.ft_deviation = 8000,
	.offset = 187744,
	.scale = 672,
	.temp_data_base = SUN50I_H6_THS_TEMP_DATA,
	.calibrate = sun50i_h6_ths_calibrate,
	.init = sun50i_h6_thermal_init,
	.irq_ack = sun50i_h6_irq_ack,
	.calc_temp = sun8i_ths_calc_temp,
पूर्ण;

अटल स्थिर काष्ठा ths_thermal_chip sun50i_h5_ths = अणु
	.sensor_num = 2,
	.has_mod_clk = true,
	.has_bus_clk_reset = true,
	.temp_data_base = SUN8I_THS_TEMP_DATA,
	.calibrate = sun8i_h3_ths_calibrate,
	.init = sun8i_h3_thermal_init,
	.irq_ack = sun8i_h3_irq_ack,
	.calc_temp = sun50i_h5_calc_temp,
पूर्ण;

अटल स्थिर काष्ठा ths_thermal_chip sun50i_h6_ths = अणु
	.sensor_num = 2,
	.has_bus_clk_reset = true,
	.ft_deviation = 7000,
	.offset = 187744,
	.scale = 672,
	.temp_data_base = SUN50I_H6_THS_TEMP_DATA,
	.calibrate = sun50i_h6_ths_calibrate,
	.init = sun50i_h6_thermal_init,
	.irq_ack = sun50i_h6_irq_ack,
	.calc_temp = sun8i_ths_calc_temp,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_ths_match[] = अणु
	अणु .compatible = "allwinner,sun8i-a83t-ths", .data = &sun8i_a83t_ths पूर्ण,
	अणु .compatible = "allwinner,sun8i-h3-ths", .data = &sun8i_h3_ths पूर्ण,
	अणु .compatible = "allwinner,sun8i-r40-ths", .data = &sun8i_r40_ths पूर्ण,
	अणु .compatible = "allwinner,sun50i-a64-ths", .data = &sun50i_a64_ths पूर्ण,
	अणु .compatible = "allwinner,sun50i-a100-ths", .data = &sun50i_a100_ths पूर्ण,
	अणु .compatible = "allwinner,sun50i-h5-ths", .data = &sun50i_h5_ths पूर्ण,
	अणु .compatible = "allwinner,sun50i-h6-ths", .data = &sun50i_h6_ths पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_ths_match);

अटल काष्ठा platक्रमm_driver ths_driver = अणु
	.probe = sun8i_ths_probe,
	.हटाओ = sun8i_ths_हटाओ,
	.driver = अणु
		.name = "sun8i-thermal",
		.of_match_table = of_ths_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ths_driver);

MODULE_DESCRIPTION("Thermal sensor driver for Allwinner SOC");
MODULE_LICENSE("GPL v2");
