<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014-2016, Fuzhou Rockchip Electronics Co., Ltd
 * Caesar Wang <wxt@rock-chips.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/thermal.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/pinctrl/consumer.h>

/*
 * If the temperature over a period of समय High,
 * the resulting TSHUT gave CRU module,let it reset the entire chip,
 * or via GPIO give PMIC.
 */
क्रमागत tshut_mode अणु
	TSHUT_MODE_CRU = 0,
	TSHUT_MODE_GPIO,
पूर्ण;

/*
 * The प्रणाली Temperature Sensors tshut(tshut) polarity
 * the bit 8 is tshut polarity.
 * 0: low active, 1: high active
 */
क्रमागत tshut_polarity अणु
	TSHUT_LOW_ACTIVE = 0,
	TSHUT_HIGH_ACTIVE,
पूर्ण;

/*
 * The प्रणाली has two Temperature Sensors.
 * sensor0 is क्रम CPU, and sensor1 is क्रम GPU.
 */
क्रमागत sensor_id अणु
	SENSOR_CPU = 0,
	SENSOR_GPU,
पूर्ण;

/*
 * The conversion table has the adc value and temperature.
 * ADC_DECREMENT: the adc value is of diminishing.(e.g. rk3288_code_table)
 * ADC_INCREMENT: the adc value is incremental.(e.g. rk3368_code_table)
 */
क्रमागत adc_sort_mode अणु
	ADC_DECREMENT = 0,
	ADC_INCREMENT,
पूर्ण;

#समावेश "thermal_hwmon.h"

/**
 * The max sensors is two in rockchip SoCs.
 * Two sensors: CPU and GPU sensor.
 */
#घोषणा SOC_MAX_SENSORS	2

/**
 * काष्ठा chip_tsadc_table - hold inक्रमmation about chip-specअगरic dअगरferences
 * @id: conversion table
 * @length: size of conversion table
 * @data_mask: mask to apply on data inमाला_दो
 * @mode: sort mode of this adc variant (incrementing or decrementing)
 */
काष्ठा chip_tsadc_table अणु
	स्थिर काष्ठा tsadc_table *id;
	अचिन्हित पूर्णांक length;
	u32 data_mask;
	क्रमागत adc_sort_mode mode;
पूर्ण;

/**
 * काष्ठा rockchip_tsadc_chip - hold the निजी data of tsadc chip
 * @chn_id: array of sensor ids of chip corresponding to the channel
 * @chn_num: the channel number of tsadc chip
 * @tshut_temp: the hardware-controlled shutकरोwn temperature value
 * @tshut_mode: the hardware-controlled shutकरोwn mode (0:CRU 1:GPIO)
 * @tshut_polarity: the hardware-controlled active polarity (0:LOW 1:HIGH)
 * @initialize: SoC special initialize tsadc controller method
 * @irq_ack: clear the पूर्णांकerrupt
 * @control: enable/disable method क्रम the tsadc controller
 * @get_temp: get the temperature
 * @set_alarm_temp: set the high temperature पूर्णांकerrupt
 * @set_tshut_temp: set the hardware-controlled shutकरोwn temperature
 * @set_tshut_mode: set the hardware-controlled shutकरोwn mode
 * @table: the chip-specअगरic conversion table
 */
काष्ठा rockchip_tsadc_chip अणु
	/* The sensor id of chip correspond to the ADC channel */
	पूर्णांक chn_id[SOC_MAX_SENSORS];
	पूर्णांक chn_num;

	/* The hardware-controlled tshut property */
	पूर्णांक tshut_temp;
	क्रमागत tshut_mode tshut_mode;
	क्रमागत tshut_polarity tshut_polarity;

	/* Chip-wide methods */
	व्योम (*initialize)(काष्ठा regmap *grf,
			   व्योम __iomem *reg, क्रमागत tshut_polarity p);
	व्योम (*irq_ack)(व्योम __iomem *reg);
	व्योम (*control)(व्योम __iomem *reg, bool on);

	/* Per-sensor methods */
	पूर्णांक (*get_temp)(स्थिर काष्ठा chip_tsadc_table *table,
			पूर्णांक chn, व्योम __iomem *reg, पूर्णांक *temp);
	पूर्णांक (*set_alarm_temp)(स्थिर काष्ठा chip_tsadc_table *table,
			      पूर्णांक chn, व्योम __iomem *reg, पूर्णांक temp);
	पूर्णांक (*set_tshut_temp)(स्थिर काष्ठा chip_tsadc_table *table,
			      पूर्णांक chn, व्योम __iomem *reg, पूर्णांक temp);
	व्योम (*set_tshut_mode)(पूर्णांक chn, व्योम __iomem *reg, क्रमागत tshut_mode m);

	/* Per-table methods */
	काष्ठा chip_tsadc_table table;
पूर्ण;

/**
 * काष्ठा rockchip_thermal_sensor - hold the inक्रमmation of thermal sensor
 * @thermal:  poपूर्णांकer to the platक्रमm/configuration data
 * @tzd: poपूर्णांकer to a thermal zone
 * @id: identअगरier of the thermal sensor
 */
काष्ठा rockchip_thermal_sensor अणु
	काष्ठा rockchip_thermal_data *thermal;
	काष्ठा thermal_zone_device *tzd;
	पूर्णांक id;
पूर्ण;

/**
 * काष्ठा rockchip_thermal_data - hold the निजी data of thermal driver
 * @chip: poपूर्णांकer to the platक्रमm/configuration data
 * @pdev: platक्रमm device of thermal
 * @reset: the reset controller of tsadc
 * @sensors: array of thermal sensors
 * @clk: the controller घड़ी is भागided by the exteral 24MHz
 * @pclk: the advanced peripherals bus घड़ी
 * @grf: the general रेजिस्टर file will be used to करो अटल set by software
 * @regs: the base address of tsadc controller
 * @tshut_temp: the hardware-controlled shutकरोwn temperature value
 * @tshut_mode: the hardware-controlled shutकरोwn mode (0:CRU 1:GPIO)
 * @tshut_polarity: the hardware-controlled active polarity (0:LOW 1:HIGH)
 */
काष्ठा rockchip_thermal_data अणु
	स्थिर काष्ठा rockchip_tsadc_chip *chip;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा reset_control *reset;

	काष्ठा rockchip_thermal_sensor sensors[SOC_MAX_SENSORS];

	काष्ठा clk *clk;
	काष्ठा clk *pclk;

	काष्ठा regmap *grf;
	व्योम __iomem *regs;

	पूर्णांक tshut_temp;
	क्रमागत tshut_mode tshut_mode;
	क्रमागत tshut_polarity tshut_polarity;
पूर्ण;

/**
 * TSADC Sensor Register description:
 *
 * TSADCV2_* are used क्रम RK3288 SoCs, the other chips can reuse it.
 * TSADCV3_* are used क्रम newer SoCs than RK3288. (e.g: RK3228, RK3399)
 *
 */
#घोषणा TSADCV2_USER_CON			0x00
#घोषणा TSADCV2_AUTO_CON			0x04
#घोषणा TSADCV2_INT_EN				0x08
#घोषणा TSADCV2_INT_PD				0x0c
#घोषणा TSADCV2_DATA(chn)			(0x20 + (chn) * 0x04)
#घोषणा TSADCV2_COMP_INT(chn)		        (0x30 + (chn) * 0x04)
#घोषणा TSADCV2_COMP_SHUT(chn)		        (0x40 + (chn) * 0x04)
#घोषणा TSADCV2_HIGHT_INT_DEBOUNCE		0x60
#घोषणा TSADCV2_HIGHT_TSHUT_DEBOUNCE		0x64
#घोषणा TSADCV2_AUTO_PERIOD			0x68
#घोषणा TSADCV2_AUTO_PERIOD_HT			0x6c

#घोषणा TSADCV2_AUTO_EN				BIT(0)
#घोषणा TSADCV2_AUTO_SRC_EN(chn)		BIT(4 + (chn))
#घोषणा TSADCV2_AUTO_TSHUT_POLARITY_HIGH	BIT(8)

#घोषणा TSADCV3_AUTO_Q_SEL_EN			BIT(1)

#घोषणा TSADCV2_INT_SRC_EN(chn)			BIT(chn)
#घोषणा TSADCV2_SHUT_2GPIO_SRC_EN(chn)		BIT(4 + (chn))
#घोषणा TSADCV2_SHUT_2CRU_SRC_EN(chn)		BIT(8 + (chn))

#घोषणा TSADCV2_INT_PD_CLEAR_MASK		~BIT(8)
#घोषणा TSADCV3_INT_PD_CLEAR_MASK		~BIT(16)

#घोषणा TSADCV2_DATA_MASK			0xfff
#घोषणा TSADCV3_DATA_MASK			0x3ff

#घोषणा TSADCV2_HIGHT_INT_DEBOUNCE_COUNT	4
#घोषणा TSADCV2_HIGHT_TSHUT_DEBOUNCE_COUNT	4
#घोषणा TSADCV2_AUTO_PERIOD_TIME		250 /* 250ms */
#घोषणा TSADCV2_AUTO_PERIOD_HT_TIME		50  /* 50ms */
#घोषणा TSADCV3_AUTO_PERIOD_TIME		1875 /* 2.5ms */
#घोषणा TSADCV3_AUTO_PERIOD_HT_TIME		1875 /* 2.5ms */

#घोषणा TSADCV2_USER_INTER_PD_SOC		0x340 /* 13 घड़ीs */

#घोषणा GRF_SARADC_TESTBIT			0x0e644
#घोषणा GRF_TSADC_TESTBIT_L			0x0e648
#घोषणा GRF_TSADC_TESTBIT_H			0x0e64c

#घोषणा PX30_GRF_SOC_CON2			0x0408

#घोषणा GRF_SARADC_TESTBIT_ON			(0x10001 << 2)
#घोषणा GRF_TSADC_TESTBIT_H_ON			(0x10001 << 2)
#घोषणा GRF_TSADC_VCM_EN_L			(0x10001 << 7)
#घोषणा GRF_TSADC_VCM_EN_H			(0x10001 << 7)

#घोषणा GRF_CON_TSADC_CH_INV			(0x10001 << 1)

/**
 * काष्ठा tsadc_table - code to temperature conversion table
 * @code: the value of adc channel
 * @temp: the temperature
 * Note:
 * code to temperature mapping of the temperature sensor is a piece wise linear
 * curve.Any temperature, code faling between to 2 give temperatures can be
 * linearly पूर्णांकerpolated.
 * Code to Temperature mapping should be updated based on manufacturer results.
 */
काष्ठा tsadc_table अणु
	u32 code;
	पूर्णांक temp;
पूर्ण;

अटल स्थिर काष्ठा tsadc_table rv1108_table[] = अणु
	अणु0, -40000पूर्ण,
	अणु374, -40000पूर्ण,
	अणु382, -35000पूर्ण,
	अणु389, -30000पूर्ण,
	अणु397, -25000पूर्ण,
	अणु405, -20000पूर्ण,
	अणु413, -15000पूर्ण,
	अणु421, -10000पूर्ण,
	अणु429, -5000पूर्ण,
	अणु436, 0पूर्ण,
	अणु444, 5000पूर्ण,
	अणु452, 10000पूर्ण,
	अणु460, 15000पूर्ण,
	अणु468, 20000पूर्ण,
	अणु476, 25000पूर्ण,
	अणु483, 30000पूर्ण,
	अणु491, 35000पूर्ण,
	अणु499, 40000पूर्ण,
	अणु507, 45000पूर्ण,
	अणु515, 50000पूर्ण,
	अणु523, 55000पूर्ण,
	अणु531, 60000पूर्ण,
	अणु539, 65000पूर्ण,
	अणु547, 70000पूर्ण,
	अणु555, 75000पूर्ण,
	अणु562, 80000पूर्ण,
	अणु570, 85000पूर्ण,
	अणु578, 90000पूर्ण,
	अणु586, 95000पूर्ण,
	अणु594, 100000पूर्ण,
	अणु602, 105000पूर्ण,
	अणु610, 110000पूर्ण,
	अणु618, 115000पूर्ण,
	अणु626, 120000पूर्ण,
	अणु634, 125000पूर्ण,
	अणुTSADCV2_DATA_MASK, 125000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tsadc_table rk3228_code_table[] = अणु
	अणु0, -40000पूर्ण,
	अणु588, -40000पूर्ण,
	अणु593, -35000पूर्ण,
	अणु598, -30000पूर्ण,
	अणु603, -25000पूर्ण,
	अणु608, -20000पूर्ण,
	अणु613, -15000पूर्ण,
	अणु618, -10000पूर्ण,
	अणु623, -5000पूर्ण,
	अणु629, 0पूर्ण,
	अणु634, 5000पूर्ण,
	अणु639, 10000पूर्ण,
	अणु644, 15000पूर्ण,
	अणु649, 20000पूर्ण,
	अणु654, 25000पूर्ण,
	अणु660, 30000पूर्ण,
	अणु665, 35000पूर्ण,
	अणु670, 40000पूर्ण,
	अणु675, 45000पूर्ण,
	अणु681, 50000पूर्ण,
	अणु686, 55000पूर्ण,
	अणु691, 60000पूर्ण,
	अणु696, 65000पूर्ण,
	अणु702, 70000पूर्ण,
	अणु707, 75000पूर्ण,
	अणु712, 80000पूर्ण,
	अणु717, 85000पूर्ण,
	अणु723, 90000पूर्ण,
	अणु728, 95000पूर्ण,
	अणु733, 100000पूर्ण,
	अणु738, 105000पूर्ण,
	अणु744, 110000पूर्ण,
	अणु749, 115000पूर्ण,
	अणु754, 120000पूर्ण,
	अणु760, 125000पूर्ण,
	अणुTSADCV2_DATA_MASK, 125000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tsadc_table rk3288_code_table[] = अणु
	अणुTSADCV2_DATA_MASK, -40000पूर्ण,
	अणु3800, -40000पूर्ण,
	अणु3792, -35000पूर्ण,
	अणु3783, -30000पूर्ण,
	अणु3774, -25000पूर्ण,
	अणु3765, -20000पूर्ण,
	अणु3756, -15000पूर्ण,
	अणु3747, -10000पूर्ण,
	अणु3737, -5000पूर्ण,
	अणु3728, 0पूर्ण,
	अणु3718, 5000पूर्ण,
	अणु3708, 10000पूर्ण,
	अणु3698, 15000पूर्ण,
	अणु3688, 20000पूर्ण,
	अणु3678, 25000पूर्ण,
	अणु3667, 30000पूर्ण,
	अणु3656, 35000पूर्ण,
	अणु3645, 40000पूर्ण,
	अणु3634, 45000पूर्ण,
	अणु3623, 50000पूर्ण,
	अणु3611, 55000पूर्ण,
	अणु3600, 60000पूर्ण,
	अणु3588, 65000पूर्ण,
	अणु3575, 70000पूर्ण,
	अणु3563, 75000पूर्ण,
	अणु3550, 80000पूर्ण,
	अणु3537, 85000पूर्ण,
	अणु3524, 90000पूर्ण,
	अणु3510, 95000पूर्ण,
	अणु3496, 100000पूर्ण,
	अणु3482, 105000पूर्ण,
	अणु3467, 110000पूर्ण,
	अणु3452, 115000पूर्ण,
	अणु3437, 120000पूर्ण,
	अणु3421, 125000पूर्ण,
	अणु0, 125000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tsadc_table rk3328_code_table[] = अणु
	अणु0, -40000पूर्ण,
	अणु296, -40000पूर्ण,
	अणु304, -35000पूर्ण,
	अणु313, -30000पूर्ण,
	अणु331, -20000पूर्ण,
	अणु340, -15000पूर्ण,
	अणु349, -10000पूर्ण,
	अणु359, -5000पूर्ण,
	अणु368, 0पूर्ण,
	अणु378, 5000पूर्ण,
	अणु388, 10000पूर्ण,
	अणु398, 15000पूर्ण,
	अणु408, 20000पूर्ण,
	अणु418, 25000पूर्ण,
	अणु429, 30000पूर्ण,
	अणु440, 35000पूर्ण,
	अणु451, 40000पूर्ण,
	अणु462, 45000पूर्ण,
	अणु473, 50000पूर्ण,
	अणु485, 55000पूर्ण,
	अणु496, 60000पूर्ण,
	अणु508, 65000पूर्ण,
	अणु521, 70000पूर्ण,
	अणु533, 75000पूर्ण,
	अणु546, 80000पूर्ण,
	अणु559, 85000पूर्ण,
	अणु572, 90000पूर्ण,
	अणु586, 95000पूर्ण,
	अणु600, 100000पूर्ण,
	अणु614, 105000पूर्ण,
	अणु629, 110000पूर्ण,
	अणु644, 115000पूर्ण,
	अणु659, 120000पूर्ण,
	अणु675, 125000पूर्ण,
	अणुTSADCV2_DATA_MASK, 125000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tsadc_table rk3368_code_table[] = अणु
	अणु0, -40000पूर्ण,
	अणु106, -40000पूर्ण,
	अणु108, -35000पूर्ण,
	अणु110, -30000पूर्ण,
	अणु112, -25000पूर्ण,
	अणु114, -20000पूर्ण,
	अणु116, -15000पूर्ण,
	अणु118, -10000पूर्ण,
	अणु120, -5000पूर्ण,
	अणु122, 0पूर्ण,
	अणु124, 5000पूर्ण,
	अणु126, 10000पूर्ण,
	अणु128, 15000पूर्ण,
	अणु130, 20000पूर्ण,
	अणु132, 25000पूर्ण,
	अणु134, 30000पूर्ण,
	अणु136, 35000पूर्ण,
	अणु138, 40000पूर्ण,
	अणु140, 45000पूर्ण,
	अणु142, 50000पूर्ण,
	अणु144, 55000पूर्ण,
	अणु146, 60000पूर्ण,
	अणु148, 65000पूर्ण,
	अणु150, 70000पूर्ण,
	अणु152, 75000पूर्ण,
	अणु154, 80000पूर्ण,
	अणु156, 85000पूर्ण,
	अणु158, 90000पूर्ण,
	अणु160, 95000पूर्ण,
	अणु162, 100000पूर्ण,
	अणु163, 105000पूर्ण,
	अणु165, 110000पूर्ण,
	अणु167, 115000पूर्ण,
	अणु169, 120000पूर्ण,
	अणु171, 125000पूर्ण,
	अणुTSADCV3_DATA_MASK, 125000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tsadc_table rk3399_code_table[] = अणु
	अणु0, -40000पूर्ण,
	अणु402, -40000पूर्ण,
	अणु410, -35000पूर्ण,
	अणु419, -30000पूर्ण,
	अणु427, -25000पूर्ण,
	अणु436, -20000पूर्ण,
	अणु444, -15000पूर्ण,
	अणु453, -10000पूर्ण,
	अणु461, -5000पूर्ण,
	अणु470, 0पूर्ण,
	अणु478, 5000पूर्ण,
	अणु487, 10000पूर्ण,
	अणु496, 15000पूर्ण,
	अणु504, 20000पूर्ण,
	अणु513, 25000पूर्ण,
	अणु521, 30000पूर्ण,
	अणु530, 35000पूर्ण,
	अणु538, 40000पूर्ण,
	अणु547, 45000पूर्ण,
	अणु555, 50000पूर्ण,
	अणु564, 55000पूर्ण,
	अणु573, 60000पूर्ण,
	अणु581, 65000पूर्ण,
	अणु590, 70000पूर्ण,
	अणु599, 75000पूर्ण,
	अणु607, 80000पूर्ण,
	अणु616, 85000पूर्ण,
	अणु624, 90000पूर्ण,
	अणु633, 95000पूर्ण,
	अणु642, 100000पूर्ण,
	अणु650, 105000पूर्ण,
	अणु659, 110000पूर्ण,
	अणु668, 115000पूर्ण,
	अणु677, 120000पूर्ण,
	अणु685, 125000पूर्ण,
	अणुTSADCV3_DATA_MASK, 125000पूर्ण,
पूर्ण;

अटल u32 rk_tsadcv2_temp_to_code(स्थिर काष्ठा chip_tsadc_table *table,
				   पूर्णांक temp)
अणु
	पूर्णांक high, low, mid;
	अचिन्हित दीर्घ num;
	अचिन्हित पूर्णांक denom;
	u32 error = table->data_mask;

	low = 0;
	high = (table->length - 1) - 1; /* ignore the last check क्रम table */
	mid = (high + low) / 2;

	/* Return mask code data when the temp is over table range */
	अगर (temp < table->id[low].temp || temp > table->id[high].temp)
		जाओ निकास;

	जबतक (low <= high) अणु
		अगर (temp == table->id[mid].temp)
			वापस table->id[mid].code;
		अन्यथा अगर (temp < table->id[mid].temp)
			high = mid - 1;
		अन्यथा
			low = mid + 1;
		mid = (low + high) / 2;
	पूर्ण

	/*
	 * The conversion code granularity provided by the table. Let's
	 * assume that the relationship between temperature and
	 * analog value between 2 table entries is linear and पूर्णांकerpolate
	 * to produce less granular result.
	 */
	num = असल(table->id[mid + 1].code - table->id[mid].code);
	num *= temp - table->id[mid].temp;
	denom = table->id[mid + 1].temp - table->id[mid].temp;

	चयन (table->mode) अणु
	हाल ADC_DECREMENT:
		वापस table->id[mid].code - (num / denom);
	हाल ADC_INCREMENT:
		वापस table->id[mid].code + (num / denom);
	शेष:
		pr_err("%s: unknown table mode: %d\n", __func__, table->mode);
		वापस error;
	पूर्ण

निकास:
	pr_err("%s: invalid temperature, temp=%d error=%d\n",
	       __func__, temp, error);
	वापस error;
पूर्ण

अटल पूर्णांक rk_tsadcv2_code_to_temp(स्थिर काष्ठा chip_tsadc_table *table,
				   u32 code, पूर्णांक *temp)
अणु
	अचिन्हित पूर्णांक low = 1;
	अचिन्हित पूर्णांक high = table->length - 1;
	अचिन्हित पूर्णांक mid = (low + high) / 2;
	अचिन्हित पूर्णांक num;
	अचिन्हित दीर्घ denom;

	WARN_ON(table->length < 2);

	चयन (table->mode) अणु
	हाल ADC_DECREMENT:
		code &= table->data_mask;
		अगर (code <= table->id[high].code)
			वापस -EAGAIN;		/* Incorrect पढ़ोing */

		जबतक (low <= high) अणु
			अगर (code >= table->id[mid].code &&
			    code < table->id[mid - 1].code)
				अवरोध;
			अन्यथा अगर (code < table->id[mid].code)
				low = mid + 1;
			अन्यथा
				high = mid - 1;

			mid = (low + high) / 2;
		पूर्ण
		अवरोध;
	हाल ADC_INCREMENT:
		code &= table->data_mask;
		अगर (code < table->id[low].code)
			वापस -EAGAIN;		/* Incorrect पढ़ोing */

		जबतक (low <= high) अणु
			अगर (code <= table->id[mid].code &&
			    code > table->id[mid - 1].code)
				अवरोध;
			अन्यथा अगर (code > table->id[mid].code)
				low = mid + 1;
			अन्यथा
				high = mid - 1;

			mid = (low + high) / 2;
		पूर्ण
		अवरोध;
	शेष:
		pr_err("%s: unknown table mode: %d\n", __func__, table->mode);
		वापस -EINVAL;
	पूर्ण

	/*
	 * The 5C granularity provided by the table is too much. Let's
	 * assume that the relationship between sensor पढ़ोings and
	 * temperature between 2 table entries is linear and पूर्णांकerpolate
	 * to produce less granular result.
	 */
	num = table->id[mid].temp - table->id[mid - 1].temp;
	num *= असल(table->id[mid - 1].code - code);
	denom = असल(table->id[mid - 1].code - table->id[mid].code);
	*temp = table->id[mid - 1].temp + (num / denom);

	वापस 0;
पूर्ण

/**
 * rk_tsadcv2_initialize - initialize TASDC Controller.
 * @grf: the general रेजिस्टर file will be used to करो अटल set by software
 * @regs: the base address of tsadc controller
 * @tshut_polarity: the hardware-controlled active polarity (0:LOW 1:HIGH)
 *
 * (1) Set TSADC_V2_AUTO_PERIOD:
 *     Configure the पूर्णांकerleave between every two accessing of
 *     TSADC in normal operation.
 *
 * (2) Set TSADCV2_AUTO_PERIOD_HT:
 *     Configure the पूर्णांकerleave between every two accessing of
 *     TSADC after the temperature is higher than COM_SHUT or COM_INT.
 *
 * (3) Set TSADCV2_HIGH_INT_DEBOUNCE and TSADC_HIGHT_TSHUT_DEBOUNCE:
 *     If the temperature is higher than COMP_INT or COMP_SHUT क्रम
 *     "debounce" बार, TSADC controller will generate पूर्णांकerrupt or TSHUT.
 */
अटल व्योम rk_tsadcv2_initialize(काष्ठा regmap *grf, व्योम __iomem *regs,
				  क्रमागत tshut_polarity tshut_polarity)
अणु
	अगर (tshut_polarity == TSHUT_HIGH_ACTIVE)
		ग_लिखोl_relaxed(0U | TSADCV2_AUTO_TSHUT_POLARITY_HIGH,
			       regs + TSADCV2_AUTO_CON);
	अन्यथा
		ग_लिखोl_relaxed(0U & ~TSADCV2_AUTO_TSHUT_POLARITY_HIGH,
			       regs + TSADCV2_AUTO_CON);

	ग_लिखोl_relaxed(TSADCV2_AUTO_PERIOD_TIME, regs + TSADCV2_AUTO_PERIOD);
	ग_लिखोl_relaxed(TSADCV2_HIGHT_INT_DEBOUNCE_COUNT,
		       regs + TSADCV2_HIGHT_INT_DEBOUNCE);
	ग_लिखोl_relaxed(TSADCV2_AUTO_PERIOD_HT_TIME,
		       regs + TSADCV2_AUTO_PERIOD_HT);
	ग_लिखोl_relaxed(TSADCV2_HIGHT_TSHUT_DEBOUNCE_COUNT,
		       regs + TSADCV2_HIGHT_TSHUT_DEBOUNCE);
पूर्ण

/**
 * rk_tsadcv3_initialize - initialize TASDC Controller.
 * @grf: the general रेजिस्टर file will be used to करो अटल set by software
 * @regs: the base address of tsadc controller
 * @tshut_polarity: the hardware-controlled active polarity (0:LOW 1:HIGH)
 *
 * (1) The tsadc control घातer sequence.
 *
 * (2) Set TSADC_V2_AUTO_PERIOD:
 *     Configure the पूर्णांकerleave between every two accessing of
 *     TSADC in normal operation.
 *
 * (2) Set TSADCV2_AUTO_PERIOD_HT:
 *     Configure the पूर्णांकerleave between every two accessing of
 *     TSADC after the temperature is higher than COM_SHUT or COM_INT.
 *
 * (3) Set TSADCV2_HIGH_INT_DEBOUNCE and TSADC_HIGHT_TSHUT_DEBOUNCE:
 *     If the temperature is higher than COMP_INT or COMP_SHUT क्रम
 *     "debounce" बार, TSADC controller will generate पूर्णांकerrupt or TSHUT.
 */
अटल व्योम rk_tsadcv3_initialize(काष्ठा regmap *grf, व्योम __iomem *regs,
				  क्रमागत tshut_polarity tshut_polarity)
अणु
	/* The tsadc control घातer sequence */
	अगर (IS_ERR(grf)) अणु
		/* Set पूर्णांकerleave value to workround ic समय sync issue */
		ग_लिखोl_relaxed(TSADCV2_USER_INTER_PD_SOC, regs +
			       TSADCV2_USER_CON);

		ग_लिखोl_relaxed(TSADCV2_AUTO_PERIOD_TIME,
			       regs + TSADCV2_AUTO_PERIOD);
		ग_लिखोl_relaxed(TSADCV2_HIGHT_INT_DEBOUNCE_COUNT,
			       regs + TSADCV2_HIGHT_INT_DEBOUNCE);
		ग_लिखोl_relaxed(TSADCV2_AUTO_PERIOD_HT_TIME,
			       regs + TSADCV2_AUTO_PERIOD_HT);
		ग_लिखोl_relaxed(TSADCV2_HIGHT_TSHUT_DEBOUNCE_COUNT,
			       regs + TSADCV2_HIGHT_TSHUT_DEBOUNCE);

	पूर्ण अन्यथा अणु
		/* Enable the voltage common mode feature */
		regmap_ग_लिखो(grf, GRF_TSADC_TESTBIT_L, GRF_TSADC_VCM_EN_L);
		regmap_ग_लिखो(grf, GRF_TSADC_TESTBIT_H, GRF_TSADC_VCM_EN_H);

		usleep_range(15, 100); /* The spec note says at least 15 us */
		regmap_ग_लिखो(grf, GRF_SARADC_TESTBIT, GRF_SARADC_TESTBIT_ON);
		regmap_ग_लिखो(grf, GRF_TSADC_TESTBIT_H, GRF_TSADC_TESTBIT_H_ON);
		usleep_range(90, 200); /* The spec note says at least 90 us */

		ग_लिखोl_relaxed(TSADCV3_AUTO_PERIOD_TIME,
			       regs + TSADCV2_AUTO_PERIOD);
		ग_लिखोl_relaxed(TSADCV2_HIGHT_INT_DEBOUNCE_COUNT,
			       regs + TSADCV2_HIGHT_INT_DEBOUNCE);
		ग_लिखोl_relaxed(TSADCV3_AUTO_PERIOD_HT_TIME,
			       regs + TSADCV2_AUTO_PERIOD_HT);
		ग_लिखोl_relaxed(TSADCV2_HIGHT_TSHUT_DEBOUNCE_COUNT,
			       regs + TSADCV2_HIGHT_TSHUT_DEBOUNCE);
	पूर्ण

	अगर (tshut_polarity == TSHUT_HIGH_ACTIVE)
		ग_लिखोl_relaxed(0U | TSADCV2_AUTO_TSHUT_POLARITY_HIGH,
			       regs + TSADCV2_AUTO_CON);
	अन्यथा
		ग_लिखोl_relaxed(0U & ~TSADCV2_AUTO_TSHUT_POLARITY_HIGH,
			       regs + TSADCV2_AUTO_CON);
पूर्ण

अटल व्योम rk_tsadcv4_initialize(काष्ठा regmap *grf, व्योम __iomem *regs,
				  क्रमागत tshut_polarity tshut_polarity)
अणु
	rk_tsadcv2_initialize(grf, regs, tshut_polarity);
	regmap_ग_लिखो(grf, PX30_GRF_SOC_CON2, GRF_CON_TSADC_CH_INV);
पूर्ण

अटल व्योम rk_tsadcv2_irq_ack(व्योम __iomem *regs)
अणु
	u32 val;

	val = पढ़ोl_relaxed(regs + TSADCV2_INT_PD);
	ग_लिखोl_relaxed(val & TSADCV2_INT_PD_CLEAR_MASK, regs + TSADCV2_INT_PD);
पूर्ण

अटल व्योम rk_tsadcv3_irq_ack(व्योम __iomem *regs)
अणु
	u32 val;

	val = पढ़ोl_relaxed(regs + TSADCV2_INT_PD);
	ग_लिखोl_relaxed(val & TSADCV3_INT_PD_CLEAR_MASK, regs + TSADCV2_INT_PD);
पूर्ण

अटल व्योम rk_tsadcv2_control(व्योम __iomem *regs, bool enable)
अणु
	u32 val;

	val = पढ़ोl_relaxed(regs + TSADCV2_AUTO_CON);
	अगर (enable)
		val |= TSADCV2_AUTO_EN;
	अन्यथा
		val &= ~TSADCV2_AUTO_EN;

	ग_लिखोl_relaxed(val, regs + TSADCV2_AUTO_CON);
पूर्ण

/**
 * rk_tsadcv3_control - the tsadc controller is enabled or disabled.
 * @regs: the base address of tsadc controller
 * @enable: boolean flag to enable the controller
 *
 * NOTE: TSADC controller works at स्वतः mode, and some SoCs need set the
 * tsadc_q_sel bit on TSADCV2_AUTO_CON[1]. The (1024 - tsadc_q) as output
 * adc value अगर setting this bit to enable.
 */
अटल व्योम rk_tsadcv3_control(व्योम __iomem *regs, bool enable)
अणु
	u32 val;

	val = पढ़ोl_relaxed(regs + TSADCV2_AUTO_CON);
	अगर (enable)
		val |= TSADCV2_AUTO_EN | TSADCV3_AUTO_Q_SEL_EN;
	अन्यथा
		val &= ~TSADCV2_AUTO_EN;

	ग_लिखोl_relaxed(val, regs + TSADCV2_AUTO_CON);
पूर्ण

अटल पूर्णांक rk_tsadcv2_get_temp(स्थिर काष्ठा chip_tsadc_table *table,
			       पूर्णांक chn, व्योम __iomem *regs, पूर्णांक *temp)
अणु
	u32 val;

	val = पढ़ोl_relaxed(regs + TSADCV2_DATA(chn));

	वापस rk_tsadcv2_code_to_temp(table, val, temp);
पूर्ण

अटल पूर्णांक rk_tsadcv2_alarm_temp(स्थिर काष्ठा chip_tsadc_table *table,
				 पूर्णांक chn, व्योम __iomem *regs, पूर्णांक temp)
अणु
	u32 alarm_value;
	u32 पूर्णांक_en, पूर्णांक_clr;

	/*
	 * In some हालs, some sensors didn't need the trip poपूर्णांकs, the
	 * set_trips will pass अणु-पूर्णांक_उच्च, पूर्णांक_उच्चपूर्ण to trigger tsadc alarm
	 * in the end, ignore this हाल and disable the high temperature
	 * पूर्णांकerrupt.
	 */
	अगर (temp == पूर्णांक_उच्च) अणु
		पूर्णांक_clr = पढ़ोl_relaxed(regs + TSADCV2_INT_EN);
		पूर्णांक_clr &= ~TSADCV2_INT_SRC_EN(chn);
		ग_लिखोl_relaxed(पूर्णांक_clr, regs + TSADCV2_INT_EN);
		वापस 0;
	पूर्ण

	/* Make sure the value is valid */
	alarm_value = rk_tsadcv2_temp_to_code(table, temp);
	अगर (alarm_value == table->data_mask)
		वापस -दुस्फल;

	ग_लिखोl_relaxed(alarm_value & table->data_mask,
		       regs + TSADCV2_COMP_INT(chn));

	पूर्णांक_en = पढ़ोl_relaxed(regs + TSADCV2_INT_EN);
	पूर्णांक_en |= TSADCV2_INT_SRC_EN(chn);
	ग_लिखोl_relaxed(पूर्णांक_en, regs + TSADCV2_INT_EN);

	वापस 0;
पूर्ण

अटल पूर्णांक rk_tsadcv2_tshut_temp(स्थिर काष्ठा chip_tsadc_table *table,
				 पूर्णांक chn, व्योम __iomem *regs, पूर्णांक temp)
अणु
	u32 tshut_value, val;

	/* Make sure the value is valid */
	tshut_value = rk_tsadcv2_temp_to_code(table, temp);
	अगर (tshut_value == table->data_mask)
		वापस -दुस्फल;

	ग_लिखोl_relaxed(tshut_value, regs + TSADCV2_COMP_SHUT(chn));

	/* TSHUT will be valid */
	val = पढ़ोl_relaxed(regs + TSADCV2_AUTO_CON);
	ग_लिखोl_relaxed(val | TSADCV2_AUTO_SRC_EN(chn), regs + TSADCV2_AUTO_CON);

	वापस 0;
पूर्ण

अटल व्योम rk_tsadcv2_tshut_mode(पूर्णांक chn, व्योम __iomem *regs,
				  क्रमागत tshut_mode mode)
अणु
	u32 val;

	val = पढ़ोl_relaxed(regs + TSADCV2_INT_EN);
	अगर (mode == TSHUT_MODE_GPIO) अणु
		val &= ~TSADCV2_SHUT_2CRU_SRC_EN(chn);
		val |= TSADCV2_SHUT_2GPIO_SRC_EN(chn);
	पूर्ण अन्यथा अणु
		val &= ~TSADCV2_SHUT_2GPIO_SRC_EN(chn);
		val |= TSADCV2_SHUT_2CRU_SRC_EN(chn);
	पूर्ण

	ग_लिखोl_relaxed(val, regs + TSADCV2_INT_EN);
पूर्ण

अटल स्थिर काष्ठा rockchip_tsadc_chip px30_tsadc_data = अणु
	.chn_id[SENSOR_CPU] = 0, /* cpu sensor is channel 0 */
	.chn_id[SENSOR_GPU] = 1, /* gpu sensor is channel 1 */
	.chn_num = 2, /* 2 channels क्रम tsadc */

	.tshut_mode = TSHUT_MODE_CRU, /* शेष TSHUT via CRU */
	.tshut_temp = 95000,

	.initialize = rk_tsadcv4_initialize,
	.irq_ack = rk_tsadcv3_irq_ack,
	.control = rk_tsadcv3_control,
	.get_temp = rk_tsadcv2_get_temp,
	.set_alarm_temp = rk_tsadcv2_alarm_temp,
	.set_tshut_temp = rk_tsadcv2_tshut_temp,
	.set_tshut_mode = rk_tsadcv2_tshut_mode,

	.table = अणु
		.id = rk3328_code_table,
		.length = ARRAY_SIZE(rk3328_code_table),
		.data_mask = TSADCV2_DATA_MASK,
		.mode = ADC_INCREMENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rockchip_tsadc_chip rv1108_tsadc_data = अणु
	.chn_id[SENSOR_CPU] = 0, /* cpu sensor is channel 0 */
	.chn_num = 1, /* one channel क्रम tsadc */

	.tshut_mode = TSHUT_MODE_GPIO, /* शेष TSHUT via GPIO give PMIC */
	.tshut_polarity = TSHUT_LOW_ACTIVE, /* शेष TSHUT LOW ACTIVE */
	.tshut_temp = 95000,

	.initialize = rk_tsadcv2_initialize,
	.irq_ack = rk_tsadcv3_irq_ack,
	.control = rk_tsadcv3_control,
	.get_temp = rk_tsadcv2_get_temp,
	.set_alarm_temp = rk_tsadcv2_alarm_temp,
	.set_tshut_temp = rk_tsadcv2_tshut_temp,
	.set_tshut_mode = rk_tsadcv2_tshut_mode,

	.table = अणु
		.id = rv1108_table,
		.length = ARRAY_SIZE(rv1108_table),
		.data_mask = TSADCV2_DATA_MASK,
		.mode = ADC_INCREMENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rockchip_tsadc_chip rk3228_tsadc_data = अणु
	.chn_id[SENSOR_CPU] = 0, /* cpu sensor is channel 0 */
	.chn_num = 1, /* one channel क्रम tsadc */

	.tshut_mode = TSHUT_MODE_GPIO, /* शेष TSHUT via GPIO give PMIC */
	.tshut_polarity = TSHUT_LOW_ACTIVE, /* शेष TSHUT LOW ACTIVE */
	.tshut_temp = 95000,

	.initialize = rk_tsadcv2_initialize,
	.irq_ack = rk_tsadcv3_irq_ack,
	.control = rk_tsadcv3_control,
	.get_temp = rk_tsadcv2_get_temp,
	.set_alarm_temp = rk_tsadcv2_alarm_temp,
	.set_tshut_temp = rk_tsadcv2_tshut_temp,
	.set_tshut_mode = rk_tsadcv2_tshut_mode,

	.table = अणु
		.id = rk3228_code_table,
		.length = ARRAY_SIZE(rk3228_code_table),
		.data_mask = TSADCV3_DATA_MASK,
		.mode = ADC_INCREMENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rockchip_tsadc_chip rk3288_tsadc_data = अणु
	.chn_id[SENSOR_CPU] = 1, /* cpu sensor is channel 1 */
	.chn_id[SENSOR_GPU] = 2, /* gpu sensor is channel 2 */
	.chn_num = 2, /* two channels क्रम tsadc */

	.tshut_mode = TSHUT_MODE_GPIO, /* शेष TSHUT via GPIO give PMIC */
	.tshut_polarity = TSHUT_LOW_ACTIVE, /* शेष TSHUT LOW ACTIVE */
	.tshut_temp = 95000,

	.initialize = rk_tsadcv2_initialize,
	.irq_ack = rk_tsadcv2_irq_ack,
	.control = rk_tsadcv2_control,
	.get_temp = rk_tsadcv2_get_temp,
	.set_alarm_temp = rk_tsadcv2_alarm_temp,
	.set_tshut_temp = rk_tsadcv2_tshut_temp,
	.set_tshut_mode = rk_tsadcv2_tshut_mode,

	.table = अणु
		.id = rk3288_code_table,
		.length = ARRAY_SIZE(rk3288_code_table),
		.data_mask = TSADCV2_DATA_MASK,
		.mode = ADC_DECREMENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rockchip_tsadc_chip rk3328_tsadc_data = अणु
	.chn_id[SENSOR_CPU] = 0, /* cpu sensor is channel 0 */
	.chn_num = 1, /* one channels क्रम tsadc */

	.tshut_mode = TSHUT_MODE_CRU, /* शेष TSHUT via CRU */
	.tshut_temp = 95000,

	.initialize = rk_tsadcv2_initialize,
	.irq_ack = rk_tsadcv3_irq_ack,
	.control = rk_tsadcv3_control,
	.get_temp = rk_tsadcv2_get_temp,
	.set_alarm_temp = rk_tsadcv2_alarm_temp,
	.set_tshut_temp = rk_tsadcv2_tshut_temp,
	.set_tshut_mode = rk_tsadcv2_tshut_mode,

	.table = अणु
		.id = rk3328_code_table,
		.length = ARRAY_SIZE(rk3328_code_table),
		.data_mask = TSADCV2_DATA_MASK,
		.mode = ADC_INCREMENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rockchip_tsadc_chip rk3366_tsadc_data = अणु
	.chn_id[SENSOR_CPU] = 0, /* cpu sensor is channel 0 */
	.chn_id[SENSOR_GPU] = 1, /* gpu sensor is channel 1 */
	.chn_num = 2, /* two channels क्रम tsadc */

	.tshut_mode = TSHUT_MODE_GPIO, /* शेष TSHUT via GPIO give PMIC */
	.tshut_polarity = TSHUT_LOW_ACTIVE, /* शेष TSHUT LOW ACTIVE */
	.tshut_temp = 95000,

	.initialize = rk_tsadcv3_initialize,
	.irq_ack = rk_tsadcv3_irq_ack,
	.control = rk_tsadcv3_control,
	.get_temp = rk_tsadcv2_get_temp,
	.set_alarm_temp = rk_tsadcv2_alarm_temp,
	.set_tshut_temp = rk_tsadcv2_tshut_temp,
	.set_tshut_mode = rk_tsadcv2_tshut_mode,

	.table = अणु
		.id = rk3228_code_table,
		.length = ARRAY_SIZE(rk3228_code_table),
		.data_mask = TSADCV3_DATA_MASK,
		.mode = ADC_INCREMENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rockchip_tsadc_chip rk3368_tsadc_data = अणु
	.chn_id[SENSOR_CPU] = 0, /* cpu sensor is channel 0 */
	.chn_id[SENSOR_GPU] = 1, /* gpu sensor is channel 1 */
	.chn_num = 2, /* two channels क्रम tsadc */

	.tshut_mode = TSHUT_MODE_GPIO, /* शेष TSHUT via GPIO give PMIC */
	.tshut_polarity = TSHUT_LOW_ACTIVE, /* शेष TSHUT LOW ACTIVE */
	.tshut_temp = 95000,

	.initialize = rk_tsadcv2_initialize,
	.irq_ack = rk_tsadcv2_irq_ack,
	.control = rk_tsadcv2_control,
	.get_temp = rk_tsadcv2_get_temp,
	.set_alarm_temp = rk_tsadcv2_alarm_temp,
	.set_tshut_temp = rk_tsadcv2_tshut_temp,
	.set_tshut_mode = rk_tsadcv2_tshut_mode,

	.table = अणु
		.id = rk3368_code_table,
		.length = ARRAY_SIZE(rk3368_code_table),
		.data_mask = TSADCV3_DATA_MASK,
		.mode = ADC_INCREMENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rockchip_tsadc_chip rk3399_tsadc_data = अणु
	.chn_id[SENSOR_CPU] = 0, /* cpu sensor is channel 0 */
	.chn_id[SENSOR_GPU] = 1, /* gpu sensor is channel 1 */
	.chn_num = 2, /* two channels क्रम tsadc */

	.tshut_mode = TSHUT_MODE_GPIO, /* शेष TSHUT via GPIO give PMIC */
	.tshut_polarity = TSHUT_LOW_ACTIVE, /* शेष TSHUT LOW ACTIVE */
	.tshut_temp = 95000,

	.initialize = rk_tsadcv3_initialize,
	.irq_ack = rk_tsadcv3_irq_ack,
	.control = rk_tsadcv3_control,
	.get_temp = rk_tsadcv2_get_temp,
	.set_alarm_temp = rk_tsadcv2_alarm_temp,
	.set_tshut_temp = rk_tsadcv2_tshut_temp,
	.set_tshut_mode = rk_tsadcv2_tshut_mode,

	.table = अणु
		.id = rk3399_code_table,
		.length = ARRAY_SIZE(rk3399_code_table),
		.data_mask = TSADCV3_DATA_MASK,
		.mode = ADC_INCREMENT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_rockchip_thermal_match[] = अणु
	अणु	.compatible = "rockchip,px30-tsadc",
		.data = (व्योम *)&px30_tsadc_data,
	पूर्ण,
	अणु
		.compatible = "rockchip,rv1108-tsadc",
		.data = (व्योम *)&rv1108_tsadc_data,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3228-tsadc",
		.data = (व्योम *)&rk3228_tsadc_data,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3288-tsadc",
		.data = (व्योम *)&rk3288_tsadc_data,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3328-tsadc",
		.data = (व्योम *)&rk3328_tsadc_data,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3366-tsadc",
		.data = (व्योम *)&rk3366_tsadc_data,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3368-tsadc",
		.data = (व्योम *)&rk3368_tsadc_data,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3399-tsadc",
		.data = (व्योम *)&rk3399_tsadc_data,
	पूर्ण,
	अणु /* end */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_rockchip_thermal_match);

अटल व्योम
rockchip_thermal_toggle_sensor(काष्ठा rockchip_thermal_sensor *sensor, bool on)
अणु
	काष्ठा thermal_zone_device *tzd = sensor->tzd;

	अगर (on)
		thermal_zone_device_enable(tzd);
	अन्यथा
		thermal_zone_device_disable(tzd);
पूर्ण

अटल irqवापस_t rockchip_thermal_alarm_irq_thपढ़ो(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा rockchip_thermal_data *thermal = dev;
	पूर्णांक i;

	dev_dbg(&thermal->pdev->dev, "thermal alarm\n");

	thermal->chip->irq_ack(thermal->regs);

	क्रम (i = 0; i < thermal->chip->chn_num; i++)
		thermal_zone_device_update(thermal->sensors[i].tzd,
					   THERMAL_EVENT_UNSPECIFIED);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rockchip_thermal_set_trips(व्योम *_sensor, पूर्णांक low, पूर्णांक high)
अणु
	काष्ठा rockchip_thermal_sensor *sensor = _sensor;
	काष्ठा rockchip_thermal_data *thermal = sensor->thermal;
	स्थिर काष्ठा rockchip_tsadc_chip *tsadc = thermal->chip;

	dev_dbg(&thermal->pdev->dev, "%s: sensor %d: low: %d, high %d\n",
		__func__, sensor->id, low, high);

	वापस tsadc->set_alarm_temp(&tsadc->table,
				     sensor->id, thermal->regs, high);
पूर्ण

अटल पूर्णांक rockchip_thermal_get_temp(व्योम *_sensor, पूर्णांक *out_temp)
अणु
	काष्ठा rockchip_thermal_sensor *sensor = _sensor;
	काष्ठा rockchip_thermal_data *thermal = sensor->thermal;
	स्थिर काष्ठा rockchip_tsadc_chip *tsadc = sensor->thermal->chip;
	पूर्णांक retval;

	retval = tsadc->get_temp(&tsadc->table,
				 sensor->id, thermal->regs, out_temp);
	dev_dbg(&thermal->pdev->dev, "sensor %d - temp: %d, retval: %d\n",
		sensor->id, *out_temp, retval);

	वापस retval;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops rockchip_of_thermal_ops = अणु
	.get_temp = rockchip_thermal_get_temp,
	.set_trips = rockchip_thermal_set_trips,
पूर्ण;

अटल पूर्णांक rockchip_configure_from_dt(काष्ठा device *dev,
				      काष्ठा device_node *np,
				      काष्ठा rockchip_thermal_data *thermal)
अणु
	u32 shut_temp, tshut_mode, tshut_polarity;

	अगर (of_property_पढ़ो_u32(np, "rockchip,hw-tshut-temp", &shut_temp)) अणु
		dev_warn(dev,
			 "Missing tshut temp property, using default %d\n",
			 thermal->chip->tshut_temp);
		thermal->tshut_temp = thermal->chip->tshut_temp;
	पूर्ण अन्यथा अणु
		अगर (shut_temp > पूर्णांक_उच्च) अणु
			dev_err(dev, "Invalid tshut temperature specified: %d\n",
				shut_temp);
			वापस -दुस्फल;
		पूर्ण
		thermal->tshut_temp = shut_temp;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "rockchip,hw-tshut-mode", &tshut_mode)) अणु
		dev_warn(dev,
			 "Missing tshut mode property, using default (%s)\n",
			 thermal->chip->tshut_mode == TSHUT_MODE_GPIO ?
				"gpio" : "cru");
		thermal->tshut_mode = thermal->chip->tshut_mode;
	पूर्ण अन्यथा अणु
		thermal->tshut_mode = tshut_mode;
	पूर्ण

	अगर (thermal->tshut_mode > 1) अणु
		dev_err(dev, "Invalid tshut mode specified: %d\n",
			thermal->tshut_mode);
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "rockchip,hw-tshut-polarity",
				 &tshut_polarity)) अणु
		dev_warn(dev,
			 "Missing tshut-polarity property, using default (%s)\n",
			 thermal->chip->tshut_polarity == TSHUT_LOW_ACTIVE ?
				"low" : "high");
		thermal->tshut_polarity = thermal->chip->tshut_polarity;
	पूर्ण अन्यथा अणु
		thermal->tshut_polarity = tshut_polarity;
	पूर्ण

	अगर (thermal->tshut_polarity > 1) अणु
		dev_err(dev, "Invalid tshut-polarity specified: %d\n",
			thermal->tshut_polarity);
		वापस -EINVAL;
	पूर्ण

	/* The tsadc wont to handle the error in here since some SoCs didn't
	 * need this property.
	 */
	thermal->grf = syscon_regmap_lookup_by_phandle(np, "rockchip,grf");
	अगर (IS_ERR(thermal->grf))
		dev_warn(dev, "Missing rockchip,grf property\n");

	वापस 0;
पूर्ण

अटल पूर्णांक
rockchip_thermal_रेजिस्टर_sensor(काष्ठा platक्रमm_device *pdev,
				 काष्ठा rockchip_thermal_data *thermal,
				 काष्ठा rockchip_thermal_sensor *sensor,
				 पूर्णांक id)
अणु
	स्थिर काष्ठा rockchip_tsadc_chip *tsadc = thermal->chip;
	पूर्णांक error;

	tsadc->set_tshut_mode(id, thermal->regs, thermal->tshut_mode);

	error = tsadc->set_tshut_temp(&tsadc->table, id, thermal->regs,
			      thermal->tshut_temp);
	अगर (error)
		dev_err(&pdev->dev, "%s: invalid tshut=%d, error=%d\n",
			__func__, thermal->tshut_temp, error);

	sensor->thermal = thermal;
	sensor->id = id;
	sensor->tzd = devm_thermal_zone_of_sensor_रेजिस्टर(&pdev->dev, id,
					sensor, &rockchip_of_thermal_ops);
	अगर (IS_ERR(sensor->tzd)) अणु
		error = PTR_ERR(sensor->tzd);
		dev_err(&pdev->dev, "failed to register sensor %d: %d\n",
			id, error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * Reset TSADC Controller, reset all tsadc रेजिस्टरs.
 * @reset: the reset controller of tsadc
 */
अटल व्योम rockchip_thermal_reset_controller(काष्ठा reset_control *reset)
अणु
	reset_control_निश्चित(reset);
	usleep_range(10, 20);
	reset_control_deनिश्चित(reset);
पूर्ण

अटल पूर्णांक rockchip_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा rockchip_thermal_data *thermal;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा resource *res;
	पूर्णांक irq;
	पूर्णांक i;
	पूर्णांक error;

	match = of_match_node(of_rockchip_thermal_match, np);
	अगर (!match)
		वापस -ENXIO;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -EINVAL;

	thermal = devm_kzalloc(&pdev->dev, माप(काष्ठा rockchip_thermal_data),
			       GFP_KERNEL);
	अगर (!thermal)
		वापस -ENOMEM;

	thermal->pdev = pdev;

	thermal->chip = (स्थिर काष्ठा rockchip_tsadc_chip *)match->data;
	अगर (!thermal->chip)
		वापस -EINVAL;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	thermal->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(thermal->regs))
		वापस PTR_ERR(thermal->regs);

	thermal->reset = devm_reset_control_get(&pdev->dev, "tsadc-apb");
	अगर (IS_ERR(thermal->reset)) अणु
		error = PTR_ERR(thermal->reset);
		dev_err(&pdev->dev, "failed to get tsadc reset: %d\n", error);
		वापस error;
	पूर्ण

	thermal->clk = devm_clk_get(&pdev->dev, "tsadc");
	अगर (IS_ERR(thermal->clk)) अणु
		error = PTR_ERR(thermal->clk);
		dev_err(&pdev->dev, "failed to get tsadc clock: %d\n", error);
		वापस error;
	पूर्ण

	thermal->pclk = devm_clk_get(&pdev->dev, "apb_pclk");
	अगर (IS_ERR(thermal->pclk)) अणु
		error = PTR_ERR(thermal->pclk);
		dev_err(&pdev->dev, "failed to get apb_pclk clock: %d\n",
			error);
		वापस error;
	पूर्ण

	error = clk_prepare_enable(thermal->clk);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to enable converter clock: %d\n",
			error);
		वापस error;
	पूर्ण

	error = clk_prepare_enable(thermal->pclk);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to enable pclk: %d\n", error);
		जाओ err_disable_clk;
	पूर्ण

	rockchip_thermal_reset_controller(thermal->reset);

	error = rockchip_configure_from_dt(&pdev->dev, np, thermal);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to parse device tree data: %d\n",
			error);
		जाओ err_disable_pclk;
	पूर्ण

	thermal->chip->initialize(thermal->grf, thermal->regs,
				  thermal->tshut_polarity);

	क्रम (i = 0; i < thermal->chip->chn_num; i++) अणु
		error = rockchip_thermal_रेजिस्टर_sensor(pdev, thermal,
						&thermal->sensors[i],
						thermal->chip->chn_id[i]);
		अगर (error) अणु
			dev_err(&pdev->dev,
				"failed to register sensor[%d] : error = %d\n",
				i, error);
			जाओ err_disable_pclk;
		पूर्ण
	पूर्ण

	error = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
					  &rockchip_thermal_alarm_irq_thपढ़ो,
					  IRQF_ONESHOT,
					  "rockchip_thermal", thermal);
	अगर (error) अणु
		dev_err(&pdev->dev,
			"failed to request tsadc irq: %d\n", error);
		जाओ err_disable_pclk;
	पूर्ण

	thermal->chip->control(thermal->regs, true);

	क्रम (i = 0; i < thermal->chip->chn_num; i++) अणु
		rockchip_thermal_toggle_sensor(&thermal->sensors[i], true);
		thermal->sensors[i].tzd->tzp->no_hwmon = false;
		error = thermal_add_hwmon_sysfs(thermal->sensors[i].tzd);
		अगर (error)
			dev_warn(&pdev->dev,
				 "failed to register sensor %d with hwmon: %d\n",
				 i, error);
	पूर्ण

	platक्रमm_set_drvdata(pdev, thermal);

	वापस 0;

err_disable_pclk:
	clk_disable_unprepare(thermal->pclk);
err_disable_clk:
	clk_disable_unprepare(thermal->clk);

	वापस error;
पूर्ण

अटल पूर्णांक rockchip_thermal_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rockchip_thermal_data *thermal = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < thermal->chip->chn_num; i++) अणु
		काष्ठा rockchip_thermal_sensor *sensor = &thermal->sensors[i];

		thermal_हटाओ_hwmon_sysfs(sensor->tzd);
		rockchip_thermal_toggle_sensor(sensor, false);
	पूर्ण

	thermal->chip->control(thermal->regs, false);

	clk_disable_unprepare(thermal->pclk);
	clk_disable_unprepare(thermal->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rockchip_thermal_suspend(काष्ठा device *dev)
अणु
	काष्ठा rockchip_thermal_data *thermal = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = 0; i < thermal->chip->chn_num; i++)
		rockchip_thermal_toggle_sensor(&thermal->sensors[i], false);

	thermal->chip->control(thermal->regs, false);

	clk_disable(thermal->pclk);
	clk_disable(thermal->clk);

	pinctrl_pm_select_sleep_state(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rockchip_thermal_resume(काष्ठा device *dev)
अणु
	काष्ठा rockchip_thermal_data *thermal = dev_get_drvdata(dev);
	पूर्णांक i;
	पूर्णांक error;

	error = clk_enable(thermal->clk);
	अगर (error)
		वापस error;

	error = clk_enable(thermal->pclk);
	अगर (error) अणु
		clk_disable(thermal->clk);
		वापस error;
	पूर्ण

	rockchip_thermal_reset_controller(thermal->reset);

	thermal->chip->initialize(thermal->grf, thermal->regs,
				  thermal->tshut_polarity);

	क्रम (i = 0; i < thermal->chip->chn_num; i++) अणु
		पूर्णांक id = thermal->sensors[i].id;

		thermal->chip->set_tshut_mode(id, thermal->regs,
					      thermal->tshut_mode);

		error = thermal->chip->set_tshut_temp(&thermal->chip->table,
					      id, thermal->regs,
					      thermal->tshut_temp);
		अगर (error)
			dev_err(dev, "%s: invalid tshut=%d, error=%d\n",
				__func__, thermal->tshut_temp, error);
	पूर्ण

	thermal->chip->control(thermal->regs, true);

	क्रम (i = 0; i < thermal->chip->chn_num; i++)
		rockchip_thermal_toggle_sensor(&thermal->sensors[i], true);

	pinctrl_pm_select_शेष_state(dev);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(rockchip_thermal_pm_ops,
			 rockchip_thermal_suspend, rockchip_thermal_resume);

अटल काष्ठा platक्रमm_driver rockchip_thermal_driver = अणु
	.driver = अणु
		.name = "rockchip-thermal",
		.pm = &rockchip_thermal_pm_ops,
		.of_match_table = of_rockchip_thermal_match,
	पूर्ण,
	.probe = rockchip_thermal_probe,
	.हटाओ = rockchip_thermal_हटाओ,
पूर्ण;

module_platक्रमm_driver(rockchip_thermal_driver);

MODULE_DESCRIPTION("ROCKCHIP THERMAL Driver");
MODULE_AUTHOR("Rockchip, Inc.");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:rockchip-thermal");
