<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * exynos_पंचांगu.c - Samsung Exynos TMU (Thermal Management Unit)
 *
 *  Copyright (C) 2014 Samsung Electronics
 *  Bartlomiej Zolnierkiewicz <b.zolnierkie@samsung.com>
 *  Lukasz Majewski <l.majewski@samsung.com>
 *
 *  Copyright (C) 2011 Samsung Electronics
 *  Donggeun Kim <dg77.kim@samsung.com>
 *  Amit Daniel Kachhap <amit.kachhap@linaro.org>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <dt-bindings/thermal/thermal_exynos.h>

#समावेश "../thermal_core.h"

/* Exynos generic रेजिस्टरs */
#घोषणा EXYNOS_TMU_REG_TRIMINFO		0x0
#घोषणा EXYNOS_TMU_REG_CONTROL		0x20
#घोषणा EXYNOS_TMU_REG_STATUS		0x28
#घोषणा EXYNOS_TMU_REG_CURRENT_TEMP	0x40
#घोषणा EXYNOS_TMU_REG_INTEN		0x70
#घोषणा EXYNOS_TMU_REG_INTSTAT		0x74
#घोषणा EXYNOS_TMU_REG_INTCLEAR		0x78

#घोषणा EXYNOS_TMU_TEMP_MASK		0xff
#घोषणा EXYNOS_TMU_REF_VOLTAGE_SHIFT	24
#घोषणा EXYNOS_TMU_REF_VOLTAGE_MASK	0x1f
#घोषणा EXYNOS_TMU_BUF_SLOPE_SEL_MASK	0xf
#घोषणा EXYNOS_TMU_BUF_SLOPE_SEL_SHIFT	8
#घोषणा EXYNOS_TMU_CORE_EN_SHIFT	0

/* Exynos3250 specअगरic रेजिस्टरs */
#घोषणा EXYNOS_TMU_TRIMINFO_CON1	0x10

/* Exynos4210 specअगरic रेजिस्टरs */
#घोषणा EXYNOS4210_TMU_REG_THRESHOLD_TEMP	0x44
#घोषणा EXYNOS4210_TMU_REG_TRIG_LEVEL0	0x50

/* Exynos5250, Exynos4412, Exynos3250 specअगरic रेजिस्टरs */
#घोषणा EXYNOS_TMU_TRIMINFO_CON2	0x14
#घोषणा EXYNOS_THD_TEMP_RISE		0x50
#घोषणा EXYNOS_THD_TEMP_FALL		0x54
#घोषणा EXYNOS_EMUL_CON		0x80

#घोषणा EXYNOS_TRIMINFO_RELOAD_ENABLE	1
#घोषणा EXYNOS_TRIMINFO_25_SHIFT	0
#घोषणा EXYNOS_TRIMINFO_85_SHIFT	8
#घोषणा EXYNOS_TMU_TRIP_MODE_SHIFT	13
#घोषणा EXYNOS_TMU_TRIP_MODE_MASK	0x7
#घोषणा EXYNOS_TMU_THERM_TRIP_EN_SHIFT	12

#घोषणा EXYNOS_TMU_INTEN_RISE0_SHIFT	0
#घोषणा EXYNOS_TMU_INTEN_FALL0_SHIFT	16

#घोषणा EXYNOS_EMUL_TIME	0x57F0
#घोषणा EXYNOS_EMUL_TIME_MASK	0xffff
#घोषणा EXYNOS_EMUL_TIME_SHIFT	16
#घोषणा EXYNOS_EMUL_DATA_SHIFT	8
#घोषणा EXYNOS_EMUL_DATA_MASK	0xFF
#घोषणा EXYNOS_EMUL_ENABLE	0x1

/* Exynos5260 specअगरic */
#घोषणा EXYNOS5260_TMU_REG_INTEN		0xC0
#घोषणा EXYNOS5260_TMU_REG_INTSTAT		0xC4
#घोषणा EXYNOS5260_TMU_REG_INTCLEAR		0xC8
#घोषणा EXYNOS5260_EMUL_CON			0x100

/* Exynos4412 specअगरic */
#घोषणा EXYNOS4412_MUX_ADDR_VALUE          6
#घोषणा EXYNOS4412_MUX_ADDR_SHIFT          20

/* Exynos5433 specअगरic रेजिस्टरs */
#घोषणा EXYNOS5433_THD_TEMP_RISE3_0		0x050
#घोषणा EXYNOS5433_THD_TEMP_RISE7_4		0x054
#घोषणा EXYNOS5433_THD_TEMP_FALL3_0		0x060
#घोषणा EXYNOS5433_THD_TEMP_FALL7_4		0x064
#घोषणा EXYNOS5433_TMU_REG_INTEN		0x0c0
#घोषणा EXYNOS5433_TMU_REG_INTPEND		0x0c8
#घोषणा EXYNOS5433_TMU_EMUL_CON			0x110
#घोषणा EXYNOS5433_TMU_PD_DET_EN		0x130

#घोषणा EXYNOS5433_TRIMINFO_SENSOR_ID_SHIFT	16
#घोषणा EXYNOS5433_TRIMINFO_CALIB_SEL_SHIFT	23
#घोषणा EXYNOS5433_TRIMINFO_SENSOR_ID_MASK	\
			(0xf << EXYNOS5433_TRIMINFO_SENSOR_ID_SHIFT)
#घोषणा EXYNOS5433_TRIMINFO_CALIB_SEL_MASK	BIT(23)

#घोषणा EXYNOS5433_TRIMINFO_ONE_POINT_TRIMMING	0
#घोषणा EXYNOS5433_TRIMINFO_TWO_POINT_TRIMMING	1

#घोषणा EXYNOS5433_PD_DET_EN			1

#घोषणा EXYNOS5433_G3D_BASE			0x10070000

/* Exynos7 specअगरic रेजिस्टरs */
#घोषणा EXYNOS7_THD_TEMP_RISE7_6		0x50
#घोषणा EXYNOS7_THD_TEMP_FALL7_6		0x60
#घोषणा EXYNOS7_TMU_REG_INTEN			0x110
#घोषणा EXYNOS7_TMU_REG_INTPEND			0x118
#घोषणा EXYNOS7_TMU_REG_EMUL_CON		0x160

#घोषणा EXYNOS7_TMU_TEMP_MASK			0x1ff
#घोषणा EXYNOS7_PD_DET_EN_SHIFT			23
#घोषणा EXYNOS7_TMU_INTEN_RISE0_SHIFT		0
#घोषणा EXYNOS7_EMUL_DATA_SHIFT			7
#घोषणा EXYNOS7_EMUL_DATA_MASK			0x1ff

#घोषणा EXYNOS_FIRST_POINT_TRIM			25
#घोषणा EXYNOS_SECOND_POINT_TRIM		85

#घोषणा EXYNOS_NOISE_CANCEL_MODE		4

#घोषणा MCELSIUS	1000

क्रमागत soc_type अणु
	SOC_ARCH_EXYNOS3250 = 1,
	SOC_ARCH_EXYNOS4210,
	SOC_ARCH_EXYNOS4412,
	SOC_ARCH_EXYNOS5250,
	SOC_ARCH_EXYNOS5260,
	SOC_ARCH_EXYNOS5420,
	SOC_ARCH_EXYNOS5420_TRIMINFO,
	SOC_ARCH_EXYNOS5433,
	SOC_ARCH_EXYNOS7,
पूर्ण;

/**
 * काष्ठा exynos_पंचांगu_data : A काष्ठाure to hold the निजी data of the TMU
 *			    driver
 * @id: identअगरier of the one instance of the TMU controller.
 * @base: base address of the single instance of the TMU controller.
 * @base_second: base address of the common रेजिस्टरs of the TMU controller.
 * @irq: irq number of the TMU controller.
 * @soc: id of the SOC type.
 * @irq_work: poपूर्णांकer to the irq work काष्ठाure.
 * @lock: lock to implement synchronization.
 * @clk: poपूर्णांकer to the घड़ी काष्ठाure.
 * @clk_sec: poपूर्णांकer to the घड़ी काष्ठाure क्रम accessing the base_second.
 * @sclk: poपूर्णांकer to the घड़ी काष्ठाure क्रम accessing the पंचांगu special clk.
 * @cal_type: calibration type क्रम temperature
 * @efuse_value: SoC defined fuse value
 * @min_efuse_value: minimum valid trimming data
 * @max_efuse_value: maximum valid trimming data
 * @temp_error1: fused value of the first poपूर्णांक trim.
 * @temp_error2: fused value of the second poपूर्णांक trim.
 * @gain: gain of amplअगरier in the positive-TC generator block
 *	0 < gain <= 15
 * @reference_voltage: reference voltage of amplअगरier
 *	in the positive-TC generator block
 *	0 < reference_voltage <= 31
 * @regulator: poपूर्णांकer to the TMU regulator काष्ठाure.
 * @reg_conf: poपूर्णांकer to काष्ठाure to रेजिस्टर with core thermal.
 * @tzd: poपूर्णांकer to thermal_zone_device काष्ठाure
 * @ntrip: number of supported trip poपूर्णांकs.
 * @enabled: current status of TMU device
 * @पंचांगu_set_trip_temp: SoC specअगरic method to set trip (rising threshold)
 * @पंचांगu_set_trip_hyst: SoC specअगरic to set hysteresis (falling threshold)
 * @पंचांगu_initialize: SoC specअगरic TMU initialization method
 * @पंचांगu_control: SoC specअगरic TMU control method
 * @पंचांगu_पढ़ो: SoC specअगरic TMU temperature पढ़ो method
 * @पंचांगu_set_emulation: SoC specअगरic TMU emulation setting method
 * @पंचांगu_clear_irqs: SoC specअगरic TMU पूर्णांकerrupts clearing method
 */
काष्ठा exynos_पंचांगu_data अणु
	पूर्णांक id;
	व्योम __iomem *base;
	व्योम __iomem *base_second;
	पूर्णांक irq;
	क्रमागत soc_type soc;
	काष्ठा work_काष्ठा irq_work;
	काष्ठा mutex lock;
	काष्ठा clk *clk, *clk_sec, *sclk;
	u32 cal_type;
	u32 efuse_value;
	u32 min_efuse_value;
	u32 max_efuse_value;
	u16 temp_error1, temp_error2;
	u8 gain;
	u8 reference_voltage;
	काष्ठा regulator *regulator;
	काष्ठा thermal_zone_device *tzd;
	अचिन्हित पूर्णांक ntrip;
	bool enabled;

	व्योम (*पंचांगu_set_trip_temp)(काष्ठा exynos_पंचांगu_data *data, पूर्णांक trip,
				 u8 temp);
	व्योम (*पंचांगu_set_trip_hyst)(काष्ठा exynos_पंचांगu_data *data, पूर्णांक trip,
				 u8 temp, u8 hyst);
	व्योम (*पंचांगu_initialize)(काष्ठा platक्रमm_device *pdev);
	व्योम (*पंचांगu_control)(काष्ठा platक्रमm_device *pdev, bool on);
	पूर्णांक (*पंचांगu_पढ़ो)(काष्ठा exynos_पंचांगu_data *data);
	व्योम (*पंचांगu_set_emulation)(काष्ठा exynos_पंचांगu_data *data, पूर्णांक temp);
	व्योम (*पंचांगu_clear_irqs)(काष्ठा exynos_पंचांगu_data *data);
पूर्ण;

/*
 * TMU treats temperature as a mapped temperature code.
 * The temperature is converted dअगरferently depending on the calibration type.
 */
अटल पूर्णांक temp_to_code(काष्ठा exynos_पंचांगu_data *data, u8 temp)
अणु
	अगर (data->cal_type == TYPE_ONE_POINT_TRIMMING)
		वापस temp + data->temp_error1 - EXYNOS_FIRST_POINT_TRIM;

	वापस (temp - EXYNOS_FIRST_POINT_TRIM) *
		(data->temp_error2 - data->temp_error1) /
		(EXYNOS_SECOND_POINT_TRIM - EXYNOS_FIRST_POINT_TRIM) +
		data->temp_error1;
पूर्ण

/*
 * Calculate a temperature value from a temperature code.
 * The unit of the temperature is degree Celsius.
 */
अटल पूर्णांक code_to_temp(काष्ठा exynos_पंचांगu_data *data, u16 temp_code)
अणु
	अगर (data->cal_type == TYPE_ONE_POINT_TRIMMING)
		वापस temp_code - data->temp_error1 + EXYNOS_FIRST_POINT_TRIM;

	वापस (temp_code - data->temp_error1) *
		(EXYNOS_SECOND_POINT_TRIM - EXYNOS_FIRST_POINT_TRIM) /
		(data->temp_error2 - data->temp_error1) +
		EXYNOS_FIRST_POINT_TRIM;
पूर्ण

अटल व्योम sanitize_temp_error(काष्ठा exynos_पंचांगu_data *data, u32 trim_info)
अणु
	u16 पंचांगu_temp_mask =
		(data->soc == SOC_ARCH_EXYNOS7) ? EXYNOS7_TMU_TEMP_MASK
						: EXYNOS_TMU_TEMP_MASK;

	data->temp_error1 = trim_info & पंचांगu_temp_mask;
	data->temp_error2 = ((trim_info >> EXYNOS_TRIMINFO_85_SHIFT) &
				EXYNOS_TMU_TEMP_MASK);

	अगर (!data->temp_error1 ||
	    (data->min_efuse_value > data->temp_error1) ||
	    (data->temp_error1 > data->max_efuse_value))
		data->temp_error1 = data->efuse_value & EXYNOS_TMU_TEMP_MASK;

	अगर (!data->temp_error2)
		data->temp_error2 =
			(data->efuse_value >> EXYNOS_TRIMINFO_85_SHIFT) &
			EXYNOS_TMU_TEMP_MASK;
पूर्ण

अटल पूर्णांक exynos_पंचांगu_initialize(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_पंचांगu_data *data = platक्रमm_get_drvdata(pdev);
	काष्ठा thermal_zone_device *tzd = data->tzd;
	स्थिर काष्ठा thermal_trip * स्थिर trips =
		of_thermal_get_trip_poपूर्णांकs(tzd);
	अचिन्हित पूर्णांक status;
	पूर्णांक ret = 0, temp, hyst;

	अगर (!trips) अणु
		dev_err(&pdev->dev,
			"Cannot get trip points from device tree!\n");
		वापस -ENODEV;
	पूर्ण

	अगर (data->soc != SOC_ARCH_EXYNOS5433) /* FIXME */
		ret = tzd->ops->get_crit_temp(tzd, &temp);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"No CRITICAL trip point defined in device tree!\n");
		जाओ out;
	पूर्ण

	अगर (of_thermal_get_ntrips(tzd) > data->ntrip) अणु
		dev_info(&pdev->dev,
			 "More trip points than supported by this TMU.\n");
		dev_info(&pdev->dev,
			 "%d trip points should be configured in polling mode.\n",
			 (of_thermal_get_ntrips(tzd) - data->ntrip));
	पूर्ण

	mutex_lock(&data->lock);
	clk_enable(data->clk);
	अगर (!IS_ERR(data->clk_sec))
		clk_enable(data->clk_sec);

	status = पढ़ोb(data->base + EXYNOS_TMU_REG_STATUS);
	अगर (!status) अणु
		ret = -EBUSY;
	पूर्ण अन्यथा अणु
		पूर्णांक i, ntrips =
			min_t(पूर्णांक, of_thermal_get_ntrips(tzd), data->ntrip);

		data->पंचांगu_initialize(pdev);

		/* Write temperature code क्रम rising and falling threshold */
		क्रम (i = 0; i < ntrips; i++) अणु
			/* Write temperature code क्रम rising threshold */
			ret = tzd->ops->get_trip_temp(tzd, i, &temp);
			अगर (ret)
				जाओ err;
			temp /= MCELSIUS;
			data->पंचांगu_set_trip_temp(data, i, temp);

			/* Write temperature code क्रम falling threshold */
			ret = tzd->ops->get_trip_hyst(tzd, i, &hyst);
			अगर (ret)
				जाओ err;
			hyst /= MCELSIUS;
			data->पंचांगu_set_trip_hyst(data, i, temp, hyst);
		पूर्ण

		data->पंचांगu_clear_irqs(data);
	पूर्ण
err:
	clk_disable(data->clk);
	mutex_unlock(&data->lock);
	अगर (!IS_ERR(data->clk_sec))
		clk_disable(data->clk_sec);
out:
	वापस ret;
पूर्ण

अटल u32 get_con_reg(काष्ठा exynos_पंचांगu_data *data, u32 con)
अणु
	अगर (data->soc == SOC_ARCH_EXYNOS4412 ||
	    data->soc == SOC_ARCH_EXYNOS3250)
		con |= (EXYNOS4412_MUX_ADDR_VALUE << EXYNOS4412_MUX_ADDR_SHIFT);

	con &= ~(EXYNOS_TMU_REF_VOLTAGE_MASK << EXYNOS_TMU_REF_VOLTAGE_SHIFT);
	con |= data->reference_voltage << EXYNOS_TMU_REF_VOLTAGE_SHIFT;

	con &= ~(EXYNOS_TMU_BUF_SLOPE_SEL_MASK << EXYNOS_TMU_BUF_SLOPE_SEL_SHIFT);
	con |= (data->gain << EXYNOS_TMU_BUF_SLOPE_SEL_SHIFT);

	con &= ~(EXYNOS_TMU_TRIP_MODE_MASK << EXYNOS_TMU_TRIP_MODE_SHIFT);
	con |= (EXYNOS_NOISE_CANCEL_MODE << EXYNOS_TMU_TRIP_MODE_SHIFT);

	वापस con;
पूर्ण

अटल व्योम exynos_पंचांगu_control(काष्ठा platक्रमm_device *pdev, bool on)
अणु
	काष्ठा exynos_पंचांगu_data *data = platक्रमm_get_drvdata(pdev);

	mutex_lock(&data->lock);
	clk_enable(data->clk);
	data->पंचांगu_control(pdev, on);
	data->enabled = on;
	clk_disable(data->clk);
	mutex_unlock(&data->lock);
पूर्ण

अटल व्योम exynos4210_पंचांगu_set_trip_temp(काष्ठा exynos_पंचांगu_data *data,
					 पूर्णांक trip, u8 temp)
अणु
	स्थिर काष्ठा thermal_trip * स्थिर trips =
		of_thermal_get_trip_poपूर्णांकs(data->tzd);
	u8 ref, th_code;

	ref = trips[0].temperature / MCELSIUS;

	अगर (trip == 0) अणु
		th_code = temp_to_code(data, ref);
		ग_लिखोb(th_code, data->base + EXYNOS4210_TMU_REG_THRESHOLD_TEMP);
	पूर्ण

	temp -= ref;
	ग_लिखोb(temp, data->base + EXYNOS4210_TMU_REG_TRIG_LEVEL0 + trip * 4);
पूर्ण

/* failing thresholds are not supported on Exynos4210 */
अटल व्योम exynos4210_पंचांगu_set_trip_hyst(काष्ठा exynos_पंचांगu_data *data,
					 पूर्णांक trip, u8 temp, u8 hyst)
अणु
पूर्ण

अटल व्योम exynos4210_पंचांगu_initialize(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_पंचांगu_data *data = platक्रमm_get_drvdata(pdev);

	sanitize_temp_error(data, पढ़ोl(data->base + EXYNOS_TMU_REG_TRIMINFO));
पूर्ण

अटल व्योम exynos4412_पंचांगu_set_trip_temp(काष्ठा exynos_पंचांगu_data *data,
					 पूर्णांक trip, u8 temp)
अणु
	u32 th, con;

	th = पढ़ोl(data->base + EXYNOS_THD_TEMP_RISE);
	th &= ~(0xff << 8 * trip);
	th |= temp_to_code(data, temp) << 8 * trip;
	ग_लिखोl(th, data->base + EXYNOS_THD_TEMP_RISE);

	अगर (trip == 3) अणु
		con = पढ़ोl(data->base + EXYNOS_TMU_REG_CONTROL);
		con |= (1 << EXYNOS_TMU_THERM_TRIP_EN_SHIFT);
		ग_लिखोl(con, data->base + EXYNOS_TMU_REG_CONTROL);
	पूर्ण
पूर्ण

अटल व्योम exynos4412_पंचांगu_set_trip_hyst(काष्ठा exynos_पंचांगu_data *data,
					 पूर्णांक trip, u8 temp, u8 hyst)
अणु
	u32 th;

	th = पढ़ोl(data->base + EXYNOS_THD_TEMP_FALL);
	th &= ~(0xff << 8 * trip);
	अगर (hyst)
		th |= temp_to_code(data, temp - hyst) << 8 * trip;
	ग_लिखोl(th, data->base + EXYNOS_THD_TEMP_FALL);
पूर्ण

अटल व्योम exynos4412_पंचांगu_initialize(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_पंचांगu_data *data = platक्रमm_get_drvdata(pdev);
	अचिन्हित पूर्णांक trim_info, ctrl;

	अगर (data->soc == SOC_ARCH_EXYNOS3250 ||
	    data->soc == SOC_ARCH_EXYNOS4412 ||
	    data->soc == SOC_ARCH_EXYNOS5250) अणु
		अगर (data->soc == SOC_ARCH_EXYNOS3250) अणु
			ctrl = पढ़ोl(data->base + EXYNOS_TMU_TRIMINFO_CON1);
			ctrl |= EXYNOS_TRIMINFO_RELOAD_ENABLE;
			ग_लिखोl(ctrl, data->base + EXYNOS_TMU_TRIMINFO_CON1);
		पूर्ण
		ctrl = पढ़ोl(data->base + EXYNOS_TMU_TRIMINFO_CON2);
		ctrl |= EXYNOS_TRIMINFO_RELOAD_ENABLE;
		ग_लिखोl(ctrl, data->base + EXYNOS_TMU_TRIMINFO_CON2);
	पूर्ण

	/* On exynos5420 the triminfo रेजिस्टर is in the shared space */
	अगर (data->soc == SOC_ARCH_EXYNOS5420_TRIMINFO)
		trim_info = पढ़ोl(data->base_second + EXYNOS_TMU_REG_TRIMINFO);
	अन्यथा
		trim_info = पढ़ोl(data->base + EXYNOS_TMU_REG_TRIMINFO);

	sanitize_temp_error(data, trim_info);
पूर्ण

अटल व्योम exynos5433_पंचांगu_set_trip_temp(काष्ठा exynos_पंचांगu_data *data,
					 पूर्णांक trip, u8 temp)
अणु
	अचिन्हित पूर्णांक reg_off, j;
	u32 th;

	अगर (trip > 3) अणु
		reg_off = EXYNOS5433_THD_TEMP_RISE7_4;
		j = trip - 4;
	पूर्ण अन्यथा अणु
		reg_off = EXYNOS5433_THD_TEMP_RISE3_0;
		j = trip;
	पूर्ण

	th = पढ़ोl(data->base + reg_off);
	th &= ~(0xff << j * 8);
	th |= (temp_to_code(data, temp) << j * 8);
	ग_लिखोl(th, data->base + reg_off);
पूर्ण

अटल व्योम exynos5433_पंचांगu_set_trip_hyst(काष्ठा exynos_पंचांगu_data *data,
					 पूर्णांक trip, u8 temp, u8 hyst)
अणु
	अचिन्हित पूर्णांक reg_off, j;
	u32 th;

	अगर (trip > 3) अणु
		reg_off = EXYNOS5433_THD_TEMP_FALL7_4;
		j = trip - 4;
	पूर्ण अन्यथा अणु
		reg_off = EXYNOS5433_THD_TEMP_FALL3_0;
		j = trip;
	पूर्ण

	th = पढ़ोl(data->base + reg_off);
	th &= ~(0xff << j * 8);
	th |= (temp_to_code(data, temp - hyst) << j * 8);
	ग_लिखोl(th, data->base + reg_off);
पूर्ण

अटल व्योम exynos5433_पंचांगu_initialize(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_पंचांगu_data *data = platक्रमm_get_drvdata(pdev);
	अचिन्हित पूर्णांक trim_info;
	पूर्णांक sensor_id, cal_type;

	trim_info = पढ़ोl(data->base + EXYNOS_TMU_REG_TRIMINFO);
	sanitize_temp_error(data, trim_info);

	/* Read the temperature sensor id */
	sensor_id = (trim_info & EXYNOS5433_TRIMINFO_SENSOR_ID_MASK)
				>> EXYNOS5433_TRIMINFO_SENSOR_ID_SHIFT;
	dev_info(&pdev->dev, "Temperature sensor ID: 0x%x\n", sensor_id);

	/* Read the calibration mode */
	ग_लिखोl(trim_info, data->base + EXYNOS_TMU_REG_TRIMINFO);
	cal_type = (trim_info & EXYNOS5433_TRIMINFO_CALIB_SEL_MASK)
				>> EXYNOS5433_TRIMINFO_CALIB_SEL_SHIFT;

	चयन (cal_type) अणु
	हाल EXYNOS5433_TRIMINFO_TWO_POINT_TRIMMING:
		data->cal_type = TYPE_TWO_POINT_TRIMMING;
		अवरोध;
	हाल EXYNOS5433_TRIMINFO_ONE_POINT_TRIMMING:
	शेष:
		data->cal_type = TYPE_ONE_POINT_TRIMMING;
		अवरोध;
	पूर्ण

	dev_info(&pdev->dev, "Calibration type is %d-point calibration\n",
			cal_type ?  2 : 1);
पूर्ण

अटल व्योम exynos7_पंचांगu_set_trip_temp(काष्ठा exynos_पंचांगu_data *data,
				      पूर्णांक trip, u8 temp)
अणु
	अचिन्हित पूर्णांक reg_off, bit_off;
	u32 th;

	reg_off = ((7 - trip) / 2) * 4;
	bit_off = ((8 - trip) % 2);

	th = पढ़ोl(data->base + EXYNOS7_THD_TEMP_RISE7_6 + reg_off);
	th &= ~(EXYNOS7_TMU_TEMP_MASK << (16 * bit_off));
	th |= temp_to_code(data, temp) << (16 * bit_off);
	ग_लिखोl(th, data->base + EXYNOS7_THD_TEMP_RISE7_6 + reg_off);
पूर्ण

अटल व्योम exynos7_पंचांगu_set_trip_hyst(काष्ठा exynos_पंचांगu_data *data,
				      पूर्णांक trip, u8 temp, u8 hyst)
अणु
	अचिन्हित पूर्णांक reg_off, bit_off;
	u32 th;

	reg_off = ((7 - trip) / 2) * 4;
	bit_off = ((8 - trip) % 2);

	th = पढ़ोl(data->base + EXYNOS7_THD_TEMP_FALL7_6 + reg_off);
	th &= ~(EXYNOS7_TMU_TEMP_MASK << (16 * bit_off));
	th |= temp_to_code(data, temp - hyst) << (16 * bit_off);
	ग_लिखोl(th, data->base + EXYNOS7_THD_TEMP_FALL7_6 + reg_off);
पूर्ण

अटल व्योम exynos7_पंचांगu_initialize(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_पंचांगu_data *data = platक्रमm_get_drvdata(pdev);
	अचिन्हित पूर्णांक trim_info;

	trim_info = पढ़ोl(data->base + EXYNOS_TMU_REG_TRIMINFO);
	sanitize_temp_error(data, trim_info);
पूर्ण

अटल व्योम exynos4210_पंचांगu_control(काष्ठा platक्रमm_device *pdev, bool on)
अणु
	काष्ठा exynos_पंचांगu_data *data = platक्रमm_get_drvdata(pdev);
	काष्ठा thermal_zone_device *tz = data->tzd;
	अचिन्हित पूर्णांक con, पूर्णांकerrupt_en = 0, i;

	con = get_con_reg(data, पढ़ोl(data->base + EXYNOS_TMU_REG_CONTROL));

	अगर (on) अणु
		क्रम (i = 0; i < data->ntrip; i++) अणु
			अगर (!of_thermal_is_trip_valid(tz, i))
				जारी;

			पूर्णांकerrupt_en |=
				(1 << (EXYNOS_TMU_INTEN_RISE0_SHIFT + i * 4));
		पूर्ण

		अगर (data->soc != SOC_ARCH_EXYNOS4210)
			पूर्णांकerrupt_en |=
				पूर्णांकerrupt_en << EXYNOS_TMU_INTEN_FALL0_SHIFT;

		con |= (1 << EXYNOS_TMU_CORE_EN_SHIFT);
	पूर्ण अन्यथा अणु
		con &= ~(1 << EXYNOS_TMU_CORE_EN_SHIFT);
	पूर्ण

	ग_लिखोl(पूर्णांकerrupt_en, data->base + EXYNOS_TMU_REG_INTEN);
	ग_लिखोl(con, data->base + EXYNOS_TMU_REG_CONTROL);
पूर्ण

अटल व्योम exynos5433_पंचांगu_control(काष्ठा platक्रमm_device *pdev, bool on)
अणु
	काष्ठा exynos_पंचांगu_data *data = platक्रमm_get_drvdata(pdev);
	काष्ठा thermal_zone_device *tz = data->tzd;
	अचिन्हित पूर्णांक con, पूर्णांकerrupt_en = 0, pd_det_en, i;

	con = get_con_reg(data, पढ़ोl(data->base + EXYNOS_TMU_REG_CONTROL));

	अगर (on) अणु
		क्रम (i = 0; i < data->ntrip; i++) अणु
			अगर (!of_thermal_is_trip_valid(tz, i))
				जारी;

			पूर्णांकerrupt_en |=
				(1 << (EXYNOS7_TMU_INTEN_RISE0_SHIFT + i));
		पूर्ण

		पूर्णांकerrupt_en |=
			पूर्णांकerrupt_en << EXYNOS_TMU_INTEN_FALL0_SHIFT;

		con |= (1 << EXYNOS_TMU_CORE_EN_SHIFT);
	पूर्ण अन्यथा
		con &= ~(1 << EXYNOS_TMU_CORE_EN_SHIFT);

	pd_det_en = on ? EXYNOS5433_PD_DET_EN : 0;

	ग_लिखोl(pd_det_en, data->base + EXYNOS5433_TMU_PD_DET_EN);
	ग_लिखोl(पूर्णांकerrupt_en, data->base + EXYNOS5433_TMU_REG_INTEN);
	ग_लिखोl(con, data->base + EXYNOS_TMU_REG_CONTROL);
पूर्ण

अटल व्योम exynos7_पंचांगu_control(काष्ठा platक्रमm_device *pdev, bool on)
अणु
	काष्ठा exynos_पंचांगu_data *data = platक्रमm_get_drvdata(pdev);
	काष्ठा thermal_zone_device *tz = data->tzd;
	अचिन्हित पूर्णांक con, पूर्णांकerrupt_en = 0, i;

	con = get_con_reg(data, पढ़ोl(data->base + EXYNOS_TMU_REG_CONTROL));

	अगर (on) अणु
		क्रम (i = 0; i < data->ntrip; i++) अणु
			अगर (!of_thermal_is_trip_valid(tz, i))
				जारी;

			पूर्णांकerrupt_en |=
				(1 << (EXYNOS7_TMU_INTEN_RISE0_SHIFT + i));
		पूर्ण

		पूर्णांकerrupt_en |=
			पूर्णांकerrupt_en << EXYNOS_TMU_INTEN_FALL0_SHIFT;

		con |= (1 << EXYNOS_TMU_CORE_EN_SHIFT);
		con |= (1 << EXYNOS7_PD_DET_EN_SHIFT);
	पूर्ण अन्यथा अणु
		con &= ~(1 << EXYNOS_TMU_CORE_EN_SHIFT);
		con &= ~(1 << EXYNOS7_PD_DET_EN_SHIFT);
	पूर्ण

	ग_लिखोl(पूर्णांकerrupt_en, data->base + EXYNOS7_TMU_REG_INTEN);
	ग_लिखोl(con, data->base + EXYNOS_TMU_REG_CONTROL);
पूर्ण

अटल पूर्णांक exynos_get_temp(व्योम *p, पूर्णांक *temp)
अणु
	काष्ठा exynos_पंचांगu_data *data = p;
	पूर्णांक value, ret = 0;

	अगर (!data || !data->पंचांगu_पढ़ो)
		वापस -EINVAL;
	अन्यथा अगर (!data->enabled)
		/*
		 * Called too early, probably
		 * from thermal_zone_of_sensor_रेजिस्टर().
		 */
		वापस -EAGAIN;

	mutex_lock(&data->lock);
	clk_enable(data->clk);

	value = data->पंचांगu_पढ़ो(data);
	अगर (value < 0)
		ret = value;
	अन्यथा
		*temp = code_to_temp(data, value) * MCELSIUS;

	clk_disable(data->clk);
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_THERMAL_EMULATION
अटल u32 get_emul_con_reg(काष्ठा exynos_पंचांगu_data *data, अचिन्हित पूर्णांक val,
			    पूर्णांक temp)
अणु
	अगर (temp) अणु
		temp /= MCELSIUS;

		val &= ~(EXYNOS_EMUL_TIME_MASK << EXYNOS_EMUL_TIME_SHIFT);
		val |= (EXYNOS_EMUL_TIME << EXYNOS_EMUL_TIME_SHIFT);
		अगर (data->soc == SOC_ARCH_EXYNOS7) अणु
			val &= ~(EXYNOS7_EMUL_DATA_MASK <<
				EXYNOS7_EMUL_DATA_SHIFT);
			val |= (temp_to_code(data, temp) <<
				EXYNOS7_EMUL_DATA_SHIFT) |
				EXYNOS_EMUL_ENABLE;
		पूर्ण अन्यथा अणु
			val &= ~(EXYNOS_EMUL_DATA_MASK <<
				EXYNOS_EMUL_DATA_SHIFT);
			val |= (temp_to_code(data, temp) <<
				EXYNOS_EMUL_DATA_SHIFT) |
				EXYNOS_EMUL_ENABLE;
		पूर्ण
	पूर्ण अन्यथा अणु
		val &= ~EXYNOS_EMUL_ENABLE;
	पूर्ण

	वापस val;
पूर्ण

अटल व्योम exynos4412_पंचांगu_set_emulation(काष्ठा exynos_पंचांगu_data *data,
					 पूर्णांक temp)
अणु
	अचिन्हित पूर्णांक val;
	u32 emul_con;

	अगर (data->soc == SOC_ARCH_EXYNOS5260)
		emul_con = EXYNOS5260_EMUL_CON;
	अन्यथा अगर (data->soc == SOC_ARCH_EXYNOS5433)
		emul_con = EXYNOS5433_TMU_EMUL_CON;
	अन्यथा अगर (data->soc == SOC_ARCH_EXYNOS7)
		emul_con = EXYNOS7_TMU_REG_EMUL_CON;
	अन्यथा
		emul_con = EXYNOS_EMUL_CON;

	val = पढ़ोl(data->base + emul_con);
	val = get_emul_con_reg(data, val, temp);
	ग_लिखोl(val, data->base + emul_con);
पूर्ण

अटल पूर्णांक exynos_पंचांगu_set_emulation(व्योम *drv_data, पूर्णांक temp)
अणु
	काष्ठा exynos_पंचांगu_data *data = drv_data;
	पूर्णांक ret = -EINVAL;

	अगर (data->soc == SOC_ARCH_EXYNOS4210)
		जाओ out;

	अगर (temp && temp < MCELSIUS)
		जाओ out;

	mutex_lock(&data->lock);
	clk_enable(data->clk);
	data->पंचांगu_set_emulation(data, temp);
	clk_disable(data->clk);
	mutex_unlock(&data->lock);
	वापस 0;
out:
	वापस ret;
पूर्ण
#अन्यथा
#घोषणा exynos4412_पंचांगu_set_emulation शून्य
अटल पूर्णांक exynos_पंचांगu_set_emulation(व्योम *drv_data, पूर्णांक temp)
	अणु वापस -EINVAL; पूर्ण
#पूर्ण_अगर /* CONFIG_THERMAL_EMULATION */

अटल पूर्णांक exynos4210_पंचांगu_पढ़ो(काष्ठा exynos_पंचांगu_data *data)
अणु
	पूर्णांक ret = पढ़ोb(data->base + EXYNOS_TMU_REG_CURRENT_TEMP);

	/* "temp_code" should range between 75 and 175 */
	वापस (ret < 75 || ret > 175) ? -ENODATA : ret;
पूर्ण

अटल पूर्णांक exynos4412_पंचांगu_पढ़ो(काष्ठा exynos_पंचांगu_data *data)
अणु
	वापस पढ़ोb(data->base + EXYNOS_TMU_REG_CURRENT_TEMP);
पूर्ण

अटल पूर्णांक exynos7_पंचांगu_पढ़ो(काष्ठा exynos_पंचांगu_data *data)
अणु
	वापस पढ़ोw(data->base + EXYNOS_TMU_REG_CURRENT_TEMP) &
		EXYNOS7_TMU_TEMP_MASK;
पूर्ण

अटल व्योम exynos_पंचांगu_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा exynos_पंचांगu_data *data = container_of(work,
			काष्ठा exynos_पंचांगu_data, irq_work);

	thermal_zone_device_update(data->tzd, THERMAL_EVENT_UNSPECIFIED);

	mutex_lock(&data->lock);
	clk_enable(data->clk);

	/* TODO: take action based on particular पूर्णांकerrupt */
	data->पंचांगu_clear_irqs(data);

	clk_disable(data->clk);
	mutex_unlock(&data->lock);
	enable_irq(data->irq);
पूर्ण

अटल व्योम exynos4210_पंचांगu_clear_irqs(काष्ठा exynos_पंचांगu_data *data)
अणु
	अचिन्हित पूर्णांक val_irq;
	u32 पंचांगu_पूर्णांकstat, पंचांगu_पूर्णांकclear;

	अगर (data->soc == SOC_ARCH_EXYNOS5260) अणु
		पंचांगu_पूर्णांकstat = EXYNOS5260_TMU_REG_INTSTAT;
		पंचांगu_पूर्णांकclear = EXYNOS5260_TMU_REG_INTCLEAR;
	पूर्ण अन्यथा अगर (data->soc == SOC_ARCH_EXYNOS7) अणु
		पंचांगu_पूर्णांकstat = EXYNOS7_TMU_REG_INTPEND;
		पंचांगu_पूर्णांकclear = EXYNOS7_TMU_REG_INTPEND;
	पूर्ण अन्यथा अगर (data->soc == SOC_ARCH_EXYNOS5433) अणु
		पंचांगu_पूर्णांकstat = EXYNOS5433_TMU_REG_INTPEND;
		पंचांगu_पूर्णांकclear = EXYNOS5433_TMU_REG_INTPEND;
	पूर्ण अन्यथा अणु
		पंचांगu_पूर्णांकstat = EXYNOS_TMU_REG_INTSTAT;
		पंचांगu_पूर्णांकclear = EXYNOS_TMU_REG_INTCLEAR;
	पूर्ण

	val_irq = पढ़ोl(data->base + पंचांगu_पूर्णांकstat);
	/*
	 * Clear the पूर्णांकerrupts.  Please note that the करोcumentation क्रम
	 * Exynos3250, Exynos4412, Exynos5250 and Exynos5260 incorrectly
	 * states that INTCLEAR रेजिस्टर has a dअगरferent placing of bits
	 * responsible क्रम FALL IRQs than INTSTAT रेजिस्टर.  Exynos5420
	 * and Exynos5440 करोcumentation is correct (Exynos4210 करोesn't
	 * support FALL IRQs at all).
	 */
	ग_लिखोl(val_irq, data->base + पंचांगu_पूर्णांकclear);
पूर्ण

अटल irqवापस_t exynos_पंचांगu_irq(पूर्णांक irq, व्योम *id)
अणु
	काष्ठा exynos_पंचांगu_data *data = id;

	disable_irq_nosync(irq);
	schedule_work(&data->irq_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा of_device_id exynos_पंचांगu_match[] = अणु
	अणु
		.compatible = "samsung,exynos3250-tmu",
		.data = (स्थिर व्योम *)SOC_ARCH_EXYNOS3250,
	पूर्ण, अणु
		.compatible = "samsung,exynos4210-tmu",
		.data = (स्थिर व्योम *)SOC_ARCH_EXYNOS4210,
	पूर्ण, अणु
		.compatible = "samsung,exynos4412-tmu",
		.data = (स्थिर व्योम *)SOC_ARCH_EXYNOS4412,
	पूर्ण, अणु
		.compatible = "samsung,exynos5250-tmu",
		.data = (स्थिर व्योम *)SOC_ARCH_EXYNOS5250,
	पूर्ण, अणु
		.compatible = "samsung,exynos5260-tmu",
		.data = (स्थिर व्योम *)SOC_ARCH_EXYNOS5260,
	पूर्ण, अणु
		.compatible = "samsung,exynos5420-tmu",
		.data = (स्थिर व्योम *)SOC_ARCH_EXYNOS5420,
	पूर्ण, अणु
		.compatible = "samsung,exynos5420-tmu-ext-triminfo",
		.data = (स्थिर व्योम *)SOC_ARCH_EXYNOS5420_TRIMINFO,
	पूर्ण, अणु
		.compatible = "samsung,exynos5433-tmu",
		.data = (स्थिर व्योम *)SOC_ARCH_EXYNOS5433,
	पूर्ण, अणु
		.compatible = "samsung,exynos7-tmu",
		.data = (स्थिर व्योम *)SOC_ARCH_EXYNOS7,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_पंचांगu_match);

अटल पूर्णांक exynos_map_dt_data(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_पंचांगu_data *data = platक्रमm_get_drvdata(pdev);
	काष्ठा resource res;

	अगर (!data || !pdev->dev.of_node)
		वापस -ENODEV;

	data->id = of_alias_get_id(pdev->dev.of_node, "tmuctrl");
	अगर (data->id < 0)
		data->id = 0;

	data->irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
	अगर (data->irq <= 0) अणु
		dev_err(&pdev->dev, "failed to get IRQ\n");
		वापस -ENODEV;
	पूर्ण

	अगर (of_address_to_resource(pdev->dev.of_node, 0, &res)) अणु
		dev_err(&pdev->dev, "failed to get Resource 0\n");
		वापस -ENODEV;
	पूर्ण

	data->base = devm_ioremap(&pdev->dev, res.start, resource_size(&res));
	अगर (!data->base) अणु
		dev_err(&pdev->dev, "Failed to ioremap memory\n");
		वापस -EADDRNOTAVAIL;
	पूर्ण

	data->soc = (क्रमागत soc_type)of_device_get_match_data(&pdev->dev);

	चयन (data->soc) अणु
	हाल SOC_ARCH_EXYNOS4210:
		data->पंचांगu_set_trip_temp = exynos4210_पंचांगu_set_trip_temp;
		data->पंचांगu_set_trip_hyst = exynos4210_पंचांगu_set_trip_hyst;
		data->पंचांगu_initialize = exynos4210_पंचांगu_initialize;
		data->पंचांगu_control = exynos4210_पंचांगu_control;
		data->पंचांगu_पढ़ो = exynos4210_पंचांगu_पढ़ो;
		data->पंचांगu_clear_irqs = exynos4210_पंचांगu_clear_irqs;
		data->ntrip = 4;
		data->gain = 15;
		data->reference_voltage = 7;
		data->efuse_value = 55;
		data->min_efuse_value = 40;
		data->max_efuse_value = 100;
		अवरोध;
	हाल SOC_ARCH_EXYNOS3250:
	हाल SOC_ARCH_EXYNOS4412:
	हाल SOC_ARCH_EXYNOS5250:
	हाल SOC_ARCH_EXYNOS5260:
	हाल SOC_ARCH_EXYNOS5420:
	हाल SOC_ARCH_EXYNOS5420_TRIMINFO:
		data->पंचांगu_set_trip_temp = exynos4412_पंचांगu_set_trip_temp;
		data->पंचांगu_set_trip_hyst = exynos4412_पंचांगu_set_trip_hyst;
		data->पंचांगu_initialize = exynos4412_पंचांगu_initialize;
		data->पंचांगu_control = exynos4210_पंचांगu_control;
		data->पंचांगu_पढ़ो = exynos4412_पंचांगu_पढ़ो;
		data->पंचांगu_set_emulation = exynos4412_पंचांगu_set_emulation;
		data->पंचांगu_clear_irqs = exynos4210_पंचांगu_clear_irqs;
		data->ntrip = 4;
		data->gain = 8;
		data->reference_voltage = 16;
		data->efuse_value = 55;
		अगर (data->soc != SOC_ARCH_EXYNOS5420 &&
		    data->soc != SOC_ARCH_EXYNOS5420_TRIMINFO)
			data->min_efuse_value = 40;
		अन्यथा
			data->min_efuse_value = 0;
		data->max_efuse_value = 100;
		अवरोध;
	हाल SOC_ARCH_EXYNOS5433:
		data->पंचांगu_set_trip_temp = exynos5433_पंचांगu_set_trip_temp;
		data->पंचांगu_set_trip_hyst = exynos5433_पंचांगu_set_trip_hyst;
		data->पंचांगu_initialize = exynos5433_पंचांगu_initialize;
		data->पंचांगu_control = exynos5433_पंचांगu_control;
		data->पंचांगu_पढ़ो = exynos4412_पंचांगu_पढ़ो;
		data->पंचांगu_set_emulation = exynos4412_पंचांगu_set_emulation;
		data->पंचांगu_clear_irqs = exynos4210_पंचांगu_clear_irqs;
		data->ntrip = 8;
		data->gain = 8;
		अगर (res.start == EXYNOS5433_G3D_BASE)
			data->reference_voltage = 23;
		अन्यथा
			data->reference_voltage = 16;
		data->efuse_value = 75;
		data->min_efuse_value = 40;
		data->max_efuse_value = 150;
		अवरोध;
	हाल SOC_ARCH_EXYNOS7:
		data->पंचांगu_set_trip_temp = exynos7_पंचांगu_set_trip_temp;
		data->पंचांगu_set_trip_hyst = exynos7_पंचांगu_set_trip_hyst;
		data->पंचांगu_initialize = exynos7_पंचांगu_initialize;
		data->पंचांगu_control = exynos7_पंचांगu_control;
		data->पंचांगu_पढ़ो = exynos7_पंचांगu_पढ़ो;
		data->पंचांगu_set_emulation = exynos4412_पंचांगu_set_emulation;
		data->पंचांगu_clear_irqs = exynos4210_पंचांगu_clear_irqs;
		data->ntrip = 8;
		data->gain = 9;
		data->reference_voltage = 17;
		data->efuse_value = 75;
		data->min_efuse_value = 15;
		data->max_efuse_value = 100;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Platform not supported\n");
		वापस -EINVAL;
	पूर्ण

	data->cal_type = TYPE_ONE_POINT_TRIMMING;

	/*
	 * Check अगर the TMU shares some रेजिस्टरs and then try to map the
	 * memory of common रेजिस्टरs.
	 */
	अगर (data->soc != SOC_ARCH_EXYNOS5420_TRIMINFO)
		वापस 0;

	अगर (of_address_to_resource(pdev->dev.of_node, 1, &res)) अणु
		dev_err(&pdev->dev, "failed to get Resource 1\n");
		वापस -ENODEV;
	पूर्ण

	data->base_second = devm_ioremap(&pdev->dev, res.start,
					resource_size(&res));
	अगर (!data->base_second) अणु
		dev_err(&pdev->dev, "Failed to ioremap memory\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops exynos_sensor_ops = अणु
	.get_temp = exynos_get_temp,
	.set_emul_temp = exynos_पंचांगu_set_emulation,
पूर्ण;

अटल पूर्णांक exynos_पंचांगu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_पंचांगu_data *data;
	पूर्णांक ret;

	data = devm_kzalloc(&pdev->dev, माप(काष्ठा exynos_पंचांगu_data),
					GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, data);
	mutex_init(&data->lock);

	/*
	 * Try enabling the regulator अगर found
	 * TODO: Add regulator as an SOC feature, so that regulator enable
	 * is a compulsory call.
	 */
	data->regulator = devm_regulator_get_optional(&pdev->dev, "vtmu");
	अगर (!IS_ERR(data->regulator)) अणु
		ret = regulator_enable(data->regulator);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to enable vtmu\n");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (PTR_ERR(data->regulator) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		dev_info(&pdev->dev, "Regulator node (vtmu) not found\n");
	पूर्ण

	ret = exynos_map_dt_data(pdev);
	अगर (ret)
		जाओ err_sensor;

	INIT_WORK(&data->irq_work, exynos_पंचांगu_work);

	data->clk = devm_clk_get(&pdev->dev, "tmu_apbif");
	अगर (IS_ERR(data->clk)) अणु
		dev_err(&pdev->dev, "Failed to get clock\n");
		ret = PTR_ERR(data->clk);
		जाओ err_sensor;
	पूर्ण

	data->clk_sec = devm_clk_get(&pdev->dev, "tmu_triminfo_apbif");
	अगर (IS_ERR(data->clk_sec)) अणु
		अगर (data->soc == SOC_ARCH_EXYNOS5420_TRIMINFO) अणु
			dev_err(&pdev->dev, "Failed to get triminfo clock\n");
			ret = PTR_ERR(data->clk_sec);
			जाओ err_sensor;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = clk_prepare(data->clk_sec);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Failed to get clock\n");
			जाओ err_sensor;
		पूर्ण
	पूर्ण

	ret = clk_prepare(data->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to get clock\n");
		जाओ err_clk_sec;
	पूर्ण

	चयन (data->soc) अणु
	हाल SOC_ARCH_EXYNOS5433:
	हाल SOC_ARCH_EXYNOS7:
		data->sclk = devm_clk_get(&pdev->dev, "tmu_sclk");
		अगर (IS_ERR(data->sclk)) अणु
			dev_err(&pdev->dev, "Failed to get sclk\n");
			जाओ err_clk;
		पूर्ण अन्यथा अणु
			ret = clk_prepare_enable(data->sclk);
			अगर (ret) अणु
				dev_err(&pdev->dev, "Failed to enable sclk\n");
				जाओ err_clk;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * data->tzd must be रेजिस्टरed beक्रमe calling exynos_पंचांगu_initialize(),
	 * requesting irq and calling exynos_पंचांगu_control().
	 */
	data->tzd = thermal_zone_of_sensor_रेजिस्टर(&pdev->dev, 0, data,
						    &exynos_sensor_ops);
	अगर (IS_ERR(data->tzd)) अणु
		ret = PTR_ERR(data->tzd);
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Failed to register sensor: %d\n",
				ret);
		जाओ err_sclk;
	पूर्ण

	ret = exynos_पंचांगu_initialize(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to initialize TMU\n");
		जाओ err_thermal;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, data->irq, exynos_पंचांगu_irq,
		IRQF_TRIGGER_RISING | IRQF_SHARED, dev_name(&pdev->dev), data);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to request irq: %d\n", data->irq);
		जाओ err_thermal;
	पूर्ण

	exynos_पंचांगu_control(pdev, true);
	वापस 0;

err_thermal:
	thermal_zone_of_sensor_unरेजिस्टर(&pdev->dev, data->tzd);
err_sclk:
	clk_disable_unprepare(data->sclk);
err_clk:
	clk_unprepare(data->clk);
err_clk_sec:
	अगर (!IS_ERR(data->clk_sec))
		clk_unprepare(data->clk_sec);
err_sensor:
	अगर (!IS_ERR(data->regulator))
		regulator_disable(data->regulator);

	वापस ret;
पूर्ण

अटल पूर्णांक exynos_पंचांगu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_पंचांगu_data *data = platक्रमm_get_drvdata(pdev);
	काष्ठा thermal_zone_device *tzd = data->tzd;

	thermal_zone_of_sensor_unरेजिस्टर(&pdev->dev, tzd);
	exynos_पंचांगu_control(pdev, false);

	clk_disable_unprepare(data->sclk);
	clk_unprepare(data->clk);
	अगर (!IS_ERR(data->clk_sec))
		clk_unprepare(data->clk_sec);

	अगर (!IS_ERR(data->regulator))
		regulator_disable(data->regulator);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक exynos_पंचांगu_suspend(काष्ठा device *dev)
अणु
	exynos_पंचांगu_control(to_platक्रमm_device(dev), false);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_पंचांगu_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	exynos_पंचांगu_initialize(pdev);
	exynos_पंचांगu_control(pdev, true);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(exynos_पंचांगu_pm,
			 exynos_पंचांगu_suspend, exynos_पंचांगu_resume);
#घोषणा EXYNOS_TMU_PM	(&exynos_पंचांगu_pm)
#अन्यथा
#घोषणा EXYNOS_TMU_PM	शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver exynos_पंचांगu_driver = अणु
	.driver = अणु
		.name   = "exynos-tmu",
		.pm     = EXYNOS_TMU_PM,
		.of_match_table = exynos_पंचांगu_match,
	पूर्ण,
	.probe = exynos_पंचांगu_probe,
	.हटाओ	= exynos_पंचांगu_हटाओ,
पूर्ण;

module_platक्रमm_driver(exynos_पंचांगu_driver);

MODULE_DESCRIPTION("Exynos TMU Driver");
MODULE_AUTHOR("Donggeun Kim <dg77.kim@samsung.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:exynos-tmu");
