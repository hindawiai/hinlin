<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2013 Freescale Semiconductor, Inc.

#समावेश <linux/clk.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/cpu_cooling.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/thermal.h>
#समावेश <linux/nvmem-consumer.h>

#घोषणा REG_SET		0x4
#घोषणा REG_CLR		0x8
#घोषणा REG_TOG		0xc

/* i.MX6 specअगरic */
#घोषणा IMX6_MISC0				0x0150
#घोषणा IMX6_MISC0_REFTOP_SELBIASOFF		(1 << 3)
#घोषणा IMX6_MISC1				0x0160
#घोषणा IMX6_MISC1_IRQ_TEMPHIGH			(1 << 29)
/* Below LOW and PANIC bits are only क्रम TEMPMON_IMX6SX */
#घोषणा IMX6_MISC1_IRQ_TEMPLOW			(1 << 28)
#घोषणा IMX6_MISC1_IRQ_TEMPPANIC		(1 << 27)

#घोषणा IMX6_TEMPSENSE0				0x0180
#घोषणा IMX6_TEMPSENSE0_ALARM_VALUE_SHIFT	20
#घोषणा IMX6_TEMPSENSE0_ALARM_VALUE_MASK	(0xfff << 20)
#घोषणा IMX6_TEMPSENSE0_TEMP_CNT_SHIFT		8
#घोषणा IMX6_TEMPSENSE0_TEMP_CNT_MASK		(0xfff << 8)
#घोषणा IMX6_TEMPSENSE0_FINISHED		(1 << 2)
#घोषणा IMX6_TEMPSENSE0_MEASURE_TEMP		(1 << 1)
#घोषणा IMX6_TEMPSENSE0_POWER_DOWN		(1 << 0)

#घोषणा IMX6_TEMPSENSE1				0x0190
#घोषणा IMX6_TEMPSENSE1_MEASURE_FREQ		0xffff
#घोषणा IMX6_TEMPSENSE1_MEASURE_FREQ_SHIFT	0

#घोषणा OCOTP_MEM0			0x0480
#घोषणा OCOTP_ANA1			0x04e0

/* Below TEMPSENSE2 is only क्रम TEMPMON_IMX6SX */
#घोषणा IMX6_TEMPSENSE2				0x0290
#घोषणा IMX6_TEMPSENSE2_LOW_VALUE_SHIFT		0
#घोषणा IMX6_TEMPSENSE2_LOW_VALUE_MASK		0xfff
#घोषणा IMX6_TEMPSENSE2_PANIC_VALUE_SHIFT	16
#घोषणा IMX6_TEMPSENSE2_PANIC_VALUE_MASK	0xfff0000

/* i.MX7 specअगरic */
#घोषणा IMX7_ANADIG_DIGPROG			0x800
#घोषणा IMX7_TEMPSENSE0				0x300
#घोषणा IMX7_TEMPSENSE0_PANIC_ALARM_SHIFT	18
#घोषणा IMX7_TEMPSENSE0_PANIC_ALARM_MASK	(0x1ff << 18)
#घोषणा IMX7_TEMPSENSE0_HIGH_ALARM_SHIFT	9
#घोषणा IMX7_TEMPSENSE0_HIGH_ALARM_MASK		(0x1ff << 9)
#घोषणा IMX7_TEMPSENSE0_LOW_ALARM_SHIFT		0
#घोषणा IMX7_TEMPSENSE0_LOW_ALARM_MASK		0x1ff

#घोषणा IMX7_TEMPSENSE1				0x310
#घोषणा IMX7_TEMPSENSE1_MEASURE_FREQ_SHIFT	16
#घोषणा IMX7_TEMPSENSE1_MEASURE_FREQ_MASK	(0xffff << 16)
#घोषणा IMX7_TEMPSENSE1_FINISHED		(1 << 11)
#घोषणा IMX7_TEMPSENSE1_MEASURE_TEMP		(1 << 10)
#घोषणा IMX7_TEMPSENSE1_POWER_DOWN		(1 << 9)
#घोषणा IMX7_TEMPSENSE1_TEMP_VALUE_SHIFT	0
#घोषणा IMX7_TEMPSENSE1_TEMP_VALUE_MASK		0x1ff

/* The driver supports 1 passive trip poपूर्णांक and 1 critical trip poपूर्णांक */
क्रमागत imx_thermal_trip अणु
	IMX_TRIP_PASSIVE,
	IMX_TRIP_CRITICAL,
	IMX_TRIP_NUM,
पूर्ण;

#घोषणा IMX_POLLING_DELAY		2000 /* millisecond */
#घोषणा IMX_PASSIVE_DELAY		1000

#घोषणा TEMPMON_IMX6Q			1
#घोषणा TEMPMON_IMX6SX			2
#घोषणा TEMPMON_IMX7D			3

काष्ठा thermal_soc_data अणु
	u32 version;

	u32 sensor_ctrl;
	u32 घातer_करोwn_mask;
	u32 measure_temp_mask;

	u32 measure_freq_ctrl;
	u32 measure_freq_mask;
	u32 measure_freq_shअगरt;

	u32 temp_data;
	u32 temp_value_mask;
	u32 temp_value_shअगरt;
	u32 temp_valid_mask;

	u32 panic_alarm_ctrl;
	u32 panic_alarm_mask;
	u32 panic_alarm_shअगरt;

	u32 high_alarm_ctrl;
	u32 high_alarm_mask;
	u32 high_alarm_shअगरt;

	u32 low_alarm_ctrl;
	u32 low_alarm_mask;
	u32 low_alarm_shअगरt;
पूर्ण;

अटल काष्ठा thermal_soc_data thermal_imx6q_data = अणु
	.version = TEMPMON_IMX6Q,

	.sensor_ctrl = IMX6_TEMPSENSE0,
	.घातer_करोwn_mask = IMX6_TEMPSENSE0_POWER_DOWN,
	.measure_temp_mask = IMX6_TEMPSENSE0_MEASURE_TEMP,

	.measure_freq_ctrl = IMX6_TEMPSENSE1,
	.measure_freq_shअगरt = IMX6_TEMPSENSE1_MEASURE_FREQ_SHIFT,
	.measure_freq_mask = IMX6_TEMPSENSE1_MEASURE_FREQ,

	.temp_data = IMX6_TEMPSENSE0,
	.temp_value_mask = IMX6_TEMPSENSE0_TEMP_CNT_MASK,
	.temp_value_shअगरt = IMX6_TEMPSENSE0_TEMP_CNT_SHIFT,
	.temp_valid_mask = IMX6_TEMPSENSE0_FINISHED,

	.high_alarm_ctrl = IMX6_TEMPSENSE0,
	.high_alarm_mask = IMX6_TEMPSENSE0_ALARM_VALUE_MASK,
	.high_alarm_shअगरt = IMX6_TEMPSENSE0_ALARM_VALUE_SHIFT,
पूर्ण;

अटल काष्ठा thermal_soc_data thermal_imx6sx_data = अणु
	.version = TEMPMON_IMX6SX,

	.sensor_ctrl = IMX6_TEMPSENSE0,
	.घातer_करोwn_mask = IMX6_TEMPSENSE0_POWER_DOWN,
	.measure_temp_mask = IMX6_TEMPSENSE0_MEASURE_TEMP,

	.measure_freq_ctrl = IMX6_TEMPSENSE1,
	.measure_freq_shअगरt = IMX6_TEMPSENSE1_MEASURE_FREQ_SHIFT,
	.measure_freq_mask = IMX6_TEMPSENSE1_MEASURE_FREQ,

	.temp_data = IMX6_TEMPSENSE0,
	.temp_value_mask = IMX6_TEMPSENSE0_TEMP_CNT_MASK,
	.temp_value_shअगरt = IMX6_TEMPSENSE0_TEMP_CNT_SHIFT,
	.temp_valid_mask = IMX6_TEMPSENSE0_FINISHED,

	.high_alarm_ctrl = IMX6_TEMPSENSE0,
	.high_alarm_mask = IMX6_TEMPSENSE0_ALARM_VALUE_MASK,
	.high_alarm_shअगरt = IMX6_TEMPSENSE0_ALARM_VALUE_SHIFT,

	.panic_alarm_ctrl = IMX6_TEMPSENSE2,
	.panic_alarm_mask = IMX6_TEMPSENSE2_PANIC_VALUE_MASK,
	.panic_alarm_shअगरt = IMX6_TEMPSENSE2_PANIC_VALUE_SHIFT,

	.low_alarm_ctrl = IMX6_TEMPSENSE2,
	.low_alarm_mask = IMX6_TEMPSENSE2_LOW_VALUE_MASK,
	.low_alarm_shअगरt = IMX6_TEMPSENSE2_LOW_VALUE_SHIFT,
पूर्ण;

अटल काष्ठा thermal_soc_data thermal_imx7d_data = अणु
	.version = TEMPMON_IMX7D,

	.sensor_ctrl = IMX7_TEMPSENSE1,
	.घातer_करोwn_mask = IMX7_TEMPSENSE1_POWER_DOWN,
	.measure_temp_mask = IMX7_TEMPSENSE1_MEASURE_TEMP,

	.measure_freq_ctrl = IMX7_TEMPSENSE1,
	.measure_freq_shअगरt = IMX7_TEMPSENSE1_MEASURE_FREQ_SHIFT,
	.measure_freq_mask = IMX7_TEMPSENSE1_MEASURE_FREQ_MASK,

	.temp_data = IMX7_TEMPSENSE1,
	.temp_value_mask = IMX7_TEMPSENSE1_TEMP_VALUE_MASK,
	.temp_value_shअगरt = IMX7_TEMPSENSE1_TEMP_VALUE_SHIFT,
	.temp_valid_mask = IMX7_TEMPSENSE1_FINISHED,

	.panic_alarm_ctrl = IMX7_TEMPSENSE1,
	.panic_alarm_mask = IMX7_TEMPSENSE0_PANIC_ALARM_MASK,
	.panic_alarm_shअगरt = IMX7_TEMPSENSE0_PANIC_ALARM_SHIFT,

	.high_alarm_ctrl = IMX7_TEMPSENSE0,
	.high_alarm_mask = IMX7_TEMPSENSE0_HIGH_ALARM_MASK,
	.high_alarm_shअगरt = IMX7_TEMPSENSE0_HIGH_ALARM_SHIFT,

	.low_alarm_ctrl = IMX7_TEMPSENSE0,
	.low_alarm_mask = IMX7_TEMPSENSE0_LOW_ALARM_MASK,
	.low_alarm_shअगरt = IMX7_TEMPSENSE0_LOW_ALARM_SHIFT,
पूर्ण;

काष्ठा imx_thermal_data अणु
	काष्ठा cpufreq_policy *policy;
	काष्ठा thermal_zone_device *tz;
	काष्ठा thermal_cooling_device *cdev;
	काष्ठा regmap *tempmon;
	u32 c1, c2; /* See क्रमmula in imx_init_calib() */
	पूर्णांक temp_passive;
	पूर्णांक temp_critical;
	पूर्णांक temp_max;
	पूर्णांक alarm_temp;
	पूर्णांक last_temp;
	bool irq_enabled;
	पूर्णांक irq;
	काष्ठा clk *thermal_clk;
	स्थिर काष्ठा thermal_soc_data *socdata;
	स्थिर अक्षर *temp_grade;
पूर्ण;

अटल व्योम imx_set_panic_temp(काष्ठा imx_thermal_data *data,
			       पूर्णांक panic_temp)
अणु
	स्थिर काष्ठा thermal_soc_data *soc_data = data->socdata;
	काष्ठा regmap *map = data->tempmon;
	पूर्णांक critical_value;

	critical_value = (data->c2 - panic_temp) / data->c1;

	regmap_ग_लिखो(map, soc_data->panic_alarm_ctrl + REG_CLR,
		     soc_data->panic_alarm_mask);
	regmap_ग_लिखो(map, soc_data->panic_alarm_ctrl + REG_SET,
		     critical_value << soc_data->panic_alarm_shअगरt);
पूर्ण

अटल व्योम imx_set_alarm_temp(काष्ठा imx_thermal_data *data,
			       पूर्णांक alarm_temp)
अणु
	काष्ठा regmap *map = data->tempmon;
	स्थिर काष्ठा thermal_soc_data *soc_data = data->socdata;
	पूर्णांक alarm_value;

	data->alarm_temp = alarm_temp;

	अगर (data->socdata->version == TEMPMON_IMX7D)
		alarm_value = alarm_temp / 1000 + data->c1 - 25;
	अन्यथा
		alarm_value = (data->c2 - alarm_temp) / data->c1;

	regmap_ग_लिखो(map, soc_data->high_alarm_ctrl + REG_CLR,
		     soc_data->high_alarm_mask);
	regmap_ग_लिखो(map, soc_data->high_alarm_ctrl + REG_SET,
		     alarm_value << soc_data->high_alarm_shअगरt);
पूर्ण

अटल पूर्णांक imx_get_temp(काष्ठा thermal_zone_device *tz, पूर्णांक *temp)
अणु
	काष्ठा imx_thermal_data *data = tz->devdata;
	स्थिर काष्ठा thermal_soc_data *soc_data = data->socdata;
	काष्ठा regmap *map = data->tempmon;
	अचिन्हित पूर्णांक n_meas;
	bool रुको, run_measurement;
	u32 val;

	run_measurement = !data->irq_enabled;
	अगर (!run_measurement) अणु
		/* Check अगर a measurement is currently in progress */
		regmap_पढ़ो(map, soc_data->temp_data, &val);
		रुको = !(val & soc_data->temp_valid_mask);
	पूर्ण अन्यथा अणु
		/*
		 * Every समय we measure the temperature, we will घातer on the
		 * temperature sensor, enable measurements, take a पढ़ोing,
		 * disable measurements, घातer off the temperature sensor.
		 */
		regmap_ग_लिखो(map, soc_data->sensor_ctrl + REG_CLR,
			    soc_data->घातer_करोwn_mask);
		regmap_ग_लिखो(map, soc_data->sensor_ctrl + REG_SET,
			    soc_data->measure_temp_mask);

		रुको = true;
	पूर्ण

	/*
	 * According to the temp sensor designers, it may require up to ~17us
	 * to complete a measurement.
	 */
	अगर (रुको)
		usleep_range(20, 50);

	regmap_पढ़ो(map, soc_data->temp_data, &val);

	अगर (run_measurement) अणु
		regmap_ग_लिखो(map, soc_data->sensor_ctrl + REG_CLR,
			     soc_data->measure_temp_mask);
		regmap_ग_लिखो(map, soc_data->sensor_ctrl + REG_SET,
			     soc_data->घातer_करोwn_mask);
	पूर्ण

	अगर ((val & soc_data->temp_valid_mask) == 0) अणु
		dev_dbg(&tz->device, "temp measurement never finished\n");
		वापस -EAGAIN;
	पूर्ण

	n_meas = (val & soc_data->temp_value_mask)
		>> soc_data->temp_value_shअगरt;

	/* See imx_init_calib() क्रम क्रमmula derivation */
	अगर (data->socdata->version == TEMPMON_IMX7D)
		*temp = (n_meas - data->c1 + 25) * 1000;
	अन्यथा
		*temp = data->c2 - n_meas * data->c1;

	/* Update alarm value to next higher trip poपूर्णांक क्रम TEMPMON_IMX6Q */
	अगर (data->socdata->version == TEMPMON_IMX6Q) अणु
		अगर (data->alarm_temp == data->temp_passive &&
			*temp >= data->temp_passive)
			imx_set_alarm_temp(data, data->temp_critical);
		अगर (data->alarm_temp == data->temp_critical &&
			*temp < data->temp_passive) अणु
			imx_set_alarm_temp(data, data->temp_passive);
			dev_dbg(&tz->device, "thermal alarm off: T < %d\n",
				data->alarm_temp / 1000);
		पूर्ण
	पूर्ण

	अगर (*temp != data->last_temp) अणु
		dev_dbg(&tz->device, "millicelsius: %d\n", *temp);
		data->last_temp = *temp;
	पूर्ण

	/* Reenable alarm IRQ अगर temperature below alarm temperature */
	अगर (!data->irq_enabled && *temp < data->alarm_temp) अणु
		data->irq_enabled = true;
		enable_irq(data->irq);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx_change_mode(काष्ठा thermal_zone_device *tz,
			   क्रमागत thermal_device_mode mode)
अणु
	काष्ठा imx_thermal_data *data = tz->devdata;
	काष्ठा regmap *map = data->tempmon;
	स्थिर काष्ठा thermal_soc_data *soc_data = data->socdata;

	अगर (mode == THERMAL_DEVICE_ENABLED) अणु
		regmap_ग_लिखो(map, soc_data->sensor_ctrl + REG_CLR,
			     soc_data->घातer_करोwn_mask);
		regmap_ग_लिखो(map, soc_data->sensor_ctrl + REG_SET,
			     soc_data->measure_temp_mask);

		अगर (!data->irq_enabled) अणु
			data->irq_enabled = true;
			enable_irq(data->irq);
		पूर्ण
	पूर्ण अन्यथा अणु
		regmap_ग_लिखो(map, soc_data->sensor_ctrl + REG_CLR,
			     soc_data->measure_temp_mask);
		regmap_ग_लिखो(map, soc_data->sensor_ctrl + REG_SET,
			     soc_data->घातer_करोwn_mask);

		अगर (data->irq_enabled) अणु
			disable_irq(data->irq);
			data->irq_enabled = false;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx_get_trip_type(काष्ठा thermal_zone_device *tz, पूर्णांक trip,
			     क्रमागत thermal_trip_type *type)
अणु
	*type = (trip == IMX_TRIP_PASSIVE) ? THERMAL_TRIP_PASSIVE :
					     THERMAL_TRIP_CRITICAL;
	वापस 0;
पूर्ण

अटल पूर्णांक imx_get_crit_temp(काष्ठा thermal_zone_device *tz, पूर्णांक *temp)
अणु
	काष्ठा imx_thermal_data *data = tz->devdata;

	*temp = data->temp_critical;
	वापस 0;
पूर्ण

अटल पूर्णांक imx_get_trip_temp(काष्ठा thermal_zone_device *tz, पूर्णांक trip,
			     पूर्णांक *temp)
अणु
	काष्ठा imx_thermal_data *data = tz->devdata;

	*temp = (trip == IMX_TRIP_PASSIVE) ? data->temp_passive :
					     data->temp_critical;
	वापस 0;
पूर्ण

अटल पूर्णांक imx_set_trip_temp(काष्ठा thermal_zone_device *tz, पूर्णांक trip,
			     पूर्णांक temp)
अणु
	काष्ठा imx_thermal_data *data = tz->devdata;

	/* करो not allow changing critical threshold */
	अगर (trip == IMX_TRIP_CRITICAL)
		वापस -EPERM;

	/* करो not allow passive to be set higher than critical */
	अगर (temp < 0 || temp > data->temp_critical)
		वापस -EINVAL;

	data->temp_passive = temp;

	imx_set_alarm_temp(data, temp);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_bind(काष्ठा thermal_zone_device *tz,
		    काष्ठा thermal_cooling_device *cdev)
अणु
	पूर्णांक ret;

	ret = thermal_zone_bind_cooling_device(tz, IMX_TRIP_PASSIVE, cdev,
					       THERMAL_NO_LIMIT,
					       THERMAL_NO_LIMIT,
					       THERMAL_WEIGHT_DEFAULT);
	अगर (ret) अणु
		dev_err(&tz->device,
			"binding zone %s with cdev %s failed:%d\n",
			tz->type, cdev->type, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx_unbind(काष्ठा thermal_zone_device *tz,
		      काष्ठा thermal_cooling_device *cdev)
अणु
	पूर्णांक ret;

	ret = thermal_zone_unbind_cooling_device(tz, IMX_TRIP_PASSIVE, cdev);
	अगर (ret) अणु
		dev_err(&tz->device,
			"unbinding zone %s with cdev %s failed:%d\n",
			tz->type, cdev->type, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा thermal_zone_device_ops imx_tz_ops = अणु
	.bind = imx_bind,
	.unbind = imx_unbind,
	.get_temp = imx_get_temp,
	.change_mode = imx_change_mode,
	.get_trip_type = imx_get_trip_type,
	.get_trip_temp = imx_get_trip_temp,
	.get_crit_temp = imx_get_crit_temp,
	.set_trip_temp = imx_set_trip_temp,
पूर्ण;

अटल पूर्णांक imx_init_calib(काष्ठा platक्रमm_device *pdev, u32 ocotp_ana1)
अणु
	काष्ठा imx_thermal_data *data = platक्रमm_get_drvdata(pdev);
	पूर्णांक n1;
	u64 temp64;

	अगर (ocotp_ana1 == 0 || ocotp_ana1 == ~0) अणु
		dev_err(&pdev->dev, "invalid sensor calibration data\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * On i.MX7D, we only use the calibration data at 25C to get the temp,
	 * Tmeas = ( Nmeas - n1) + 25; n1 is the fuse value क्रम 25C.
	 */
	अगर (data->socdata->version == TEMPMON_IMX7D) अणु
		data->c1 = (ocotp_ana1 >> 9) & 0x1ff;
		वापस 0;
	पूर्ण

	/*
	 * The sensor is calibrated at 25 तओC (aka T1) and the value measured
	 * (aka N1) at this temperature is provided in bits [31:20] in the
	 * i.MX's OCOTP value ANA1.
	 * To find the actual temperature T, the following क्रमmula has to be used
	 * when पढ़ोing value n from the sensor:
	 *
	 * T = T1 + (N - N1) / (0.4148468 - 0.0015423 * N1) तओC + 3.580661 तओC
	 *   = [T1' - N1 / (0.4148468 - 0.0015423 * N1) तओC] + N / (0.4148468 - 0.0015423 * N1) तओC
	 *   = [T1' + N1 / (0.0015423 * N1 - 0.4148468) तओC] - N / (0.0015423 * N1 - 0.4148468) तओC
	 *   = c2 - c1 * N
	 *
	 * with
	 *
	 *  T1' = 28.580661 तओC
	 *   c1 = 1 / (0.0015423 * N1 - 0.4297157) तओC
	 *   c2 = T1' + N1 / (0.0015423 * N1 - 0.4148468) तओC
	 *      = T1' + N1 * c1
	 */
	n1 = ocotp_ana1 >> 20;

	temp64 = 10000000; /* use 10^7 as fixed poपूर्णांक स्थिरant क्रम values in क्रमmula */
	temp64 *= 1000; /* to get result in तओmC */
	करो_भाग(temp64, 15423 * n1 - 4148468);
	data->c1 = temp64;
	data->c2 = n1 * data->c1 + 28581;

	वापस 0;
पूर्ण

अटल व्योम imx_init_temp_grade(काष्ठा platक्रमm_device *pdev, u32 ocotp_mem0)
अणु
	काष्ठा imx_thermal_data *data = platक्रमm_get_drvdata(pdev);

	/* The maximum die temp is specअगरied by the Temperature Grade */
	चयन ((ocotp_mem0 >> 6) & 0x3) अणु
	हाल 0: /* Commercial (0 to 95 तओC) */
		data->temp_grade = "Commercial";
		data->temp_max = 95000;
		अवरोध;
	हाल 1: /* Extended Commercial (-20 तओC to 105 तओC) */
		data->temp_grade = "Extended Commercial";
		data->temp_max = 105000;
		अवरोध;
	हाल 2: /* Industrial (-40 तओC to 105 तओC) */
		data->temp_grade = "Industrial";
		data->temp_max = 105000;
		अवरोध;
	हाल 3: /* Automotive (-40 तओC to 125 तओC) */
		data->temp_grade = "Automotive";
		data->temp_max = 125000;
		अवरोध;
	पूर्ण

	/*
	 * Set the critical trip poपूर्णांक at 5 तओC under max
	 * Set the passive trip poपूर्णांक at 10 तओC under max (changeable via sysfs)
	 */
	data->temp_critical = data->temp_max - (1000 * 5);
	data->temp_passive = data->temp_max - (1000 * 10);
पूर्ण

अटल पूर्णांक imx_init_from_tempmon_data(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *map;
	पूर्णांक ret;
	u32 val;

	map = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
					      "fsl,tempmon-data");
	अगर (IS_ERR(map)) अणु
		ret = PTR_ERR(map);
		dev_err(&pdev->dev, "failed to get sensor regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(map, OCOTP_ANA1, &val);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to read sensor data: %d\n", ret);
		वापस ret;
	पूर्ण
	ret = imx_init_calib(pdev, val);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(map, OCOTP_MEM0, &val);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to read sensor data: %d\n", ret);
		वापस ret;
	पूर्ण
	imx_init_temp_grade(pdev, val);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_init_from_nvmem_cells(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	u32 val;

	ret = nvmem_cell_पढ़ो_u32(&pdev->dev, "calib", &val);
	अगर (ret)
		वापस ret;

	ret = imx_init_calib(pdev, val);
	अगर (ret)
		वापस ret;

	ret = nvmem_cell_पढ़ो_u32(&pdev->dev, "temp_grade", &val);
	अगर (ret)
		वापस ret;
	imx_init_temp_grade(pdev, val);

	वापस 0;
पूर्ण

अटल irqवापस_t imx_thermal_alarm_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा imx_thermal_data *data = dev;

	disable_irq_nosync(irq);
	data->irq_enabled = false;

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t imx_thermal_alarm_irq_thपढ़ो(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा imx_thermal_data *data = dev;

	dev_dbg(&data->tz->device, "THERMAL ALARM: T > %d\n",
		data->alarm_temp / 1000);

	thermal_zone_device_update(data->tz, THERMAL_EVENT_UNSPECIFIED);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_imx_thermal_match[] = अणु
	अणु .compatible = "fsl,imx6q-tempmon", .data = &thermal_imx6q_data, पूर्ण,
	अणु .compatible = "fsl,imx6sx-tempmon", .data = &thermal_imx6sx_data, पूर्ण,
	अणु .compatible = "fsl,imx7d-tempmon", .data = &thermal_imx7d_data, पूर्ण,
	अणु /* end */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_imx_thermal_match);

#अगर_घोषित CONFIG_CPU_FREQ
/*
 * Create cooling device in हाल no #cooling-cells property is available in
 * CPU node
 */
अटल पूर्णांक imx_thermal_रेजिस्टर_legacy_cooling(काष्ठा imx_thermal_data *data)
अणु
	काष्ठा device_node *np;
	पूर्णांक ret = 0;

	data->policy = cpufreq_cpu_get(0);
	अगर (!data->policy) अणु
		pr_debug("%s: CPUFreq policy not found\n", __func__);
		वापस -EPROBE_DEFER;
	पूर्ण

	np = of_get_cpu_node(data->policy->cpu, शून्य);

	अगर (!np || !of_find_property(np, "#cooling-cells", शून्य)) अणु
		data->cdev = cpufreq_cooling_रेजिस्टर(data->policy);
		अगर (IS_ERR(data->cdev)) अणु
			ret = PTR_ERR(data->cdev);
			cpufreq_cpu_put(data->policy);
		पूर्ण
	पूर्ण

	of_node_put(np);

	वापस ret;
पूर्ण

अटल व्योम imx_thermal_unरेजिस्टर_legacy_cooling(काष्ठा imx_thermal_data *data)
अणु
	cpufreq_cooling_unरेजिस्टर(data->cdev);
	cpufreq_cpu_put(data->policy);
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक imx_thermal_रेजिस्टर_legacy_cooling(काष्ठा imx_thermal_data *data)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम imx_thermal_unरेजिस्टर_legacy_cooling(काष्ठा imx_thermal_data *data)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक imx_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_thermal_data *data;
	काष्ठा regmap *map;
	पूर्णांक measure_freq;
	पूर्णांक ret;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	map = syscon_regmap_lookup_by_phandle(pdev->dev.of_node, "fsl,tempmon");
	अगर (IS_ERR(map)) अणु
		ret = PTR_ERR(map);
		dev_err(&pdev->dev, "failed to get tempmon regmap: %d\n", ret);
		वापस ret;
	पूर्ण
	data->tempmon = map;

	data->socdata = of_device_get_match_data(&pdev->dev);
	अगर (!data->socdata) अणु
		dev_err(&pdev->dev, "no device match found\n");
		वापस -ENODEV;
	पूर्ण

	/* make sure the IRQ flag is clear beक्रमe enabling irq on i.MX6SX */
	अगर (data->socdata->version == TEMPMON_IMX6SX) अणु
		regmap_ग_लिखो(map, IMX6_MISC1 + REG_CLR,
			IMX6_MISC1_IRQ_TEMPHIGH | IMX6_MISC1_IRQ_TEMPLOW
			| IMX6_MISC1_IRQ_TEMPPANIC);
		/*
		 * reset value of LOW ALARM is incorrect, set it to lowest
		 * value to aव्योम false trigger of low alarm.
		 */
		regmap_ग_लिखो(map, data->socdata->low_alarm_ctrl + REG_SET,
			     data->socdata->low_alarm_mask);
	पूर्ण

	data->irq = platक्रमm_get_irq(pdev, 0);
	अगर (data->irq < 0)
		वापस data->irq;

	platक्रमm_set_drvdata(pdev, data);

	अगर (of_find_property(pdev->dev.of_node, "nvmem-cells", शून्य)) अणु
		ret = imx_init_from_nvmem_cells(pdev);
		अगर (ret)
			वापस dev_err_probe(&pdev->dev, ret,
					     "failed to init from nvmem\n");
	पूर्ण अन्यथा अणु
		ret = imx_init_from_tempmon_data(pdev);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to init from fsl,tempmon-data\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* Make sure sensor is in known good state क्रम measurements */
	regmap_ग_लिखो(map, data->socdata->sensor_ctrl + REG_CLR,
		     data->socdata->घातer_करोwn_mask);
	regmap_ग_लिखो(map, data->socdata->sensor_ctrl + REG_CLR,
		     data->socdata->measure_temp_mask);
	regmap_ग_लिखो(map, data->socdata->measure_freq_ctrl + REG_CLR,
		     data->socdata->measure_freq_mask);
	अगर (data->socdata->version != TEMPMON_IMX7D)
		regmap_ग_लिखो(map, IMX6_MISC0 + REG_SET,
			IMX6_MISC0_REFTOP_SELBIASOFF);
	regmap_ग_लिखो(map, data->socdata->sensor_ctrl + REG_SET,
		     data->socdata->घातer_करोwn_mask);

	ret = imx_thermal_रेजिस्टर_legacy_cooling(data);
	अगर (ret)
		वापस dev_err_probe(&pdev->dev, ret,
				     "failed to register cpufreq cooling device\n");

	data->thermal_clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(data->thermal_clk)) अणु
		ret = PTR_ERR(data->thermal_clk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev,
				"failed to get thermal clk: %d\n", ret);
		जाओ legacy_cleanup;
	पूर्ण

	/*
	 * Thermal sensor needs clk on to get correct value, normally
	 * we should enable its clk beक्रमe taking measurement and disable
	 * clk after measurement is करोne, but अगर alarm function is enabled,
	 * hardware will स्वतः measure the temperature periodically, so we
	 * need to keep the clk always on क्रम alarm function.
	 */
	ret = clk_prepare_enable(data->thermal_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to enable thermal clk: %d\n", ret);
		जाओ legacy_cleanup;
	पूर्ण

	data->tz = thermal_zone_device_रेजिस्टर("imx_thermal_zone",
						IMX_TRIP_NUM,
						BIT(IMX_TRIP_PASSIVE), data,
						&imx_tz_ops, शून्य,
						IMX_PASSIVE_DELAY,
						IMX_POLLING_DELAY);
	अगर (IS_ERR(data->tz)) अणु
		ret = PTR_ERR(data->tz);
		dev_err(&pdev->dev,
			"failed to register thermal zone device %d\n", ret);
		जाओ clk_disable;
	पूर्ण

	dev_info(&pdev->dev, "%s CPU temperature grade - max:%dC"
		 " critical:%dC passive:%dC\n", data->temp_grade,
		 data->temp_max / 1000, data->temp_critical / 1000,
		 data->temp_passive / 1000);

	/* Enable measurements at ~ 10 Hz */
	regmap_ग_लिखो(map, data->socdata->measure_freq_ctrl + REG_CLR,
		     data->socdata->measure_freq_mask);
	measure_freq = DIV_ROUND_UP(32768, 10); /* 10 Hz */
	regmap_ग_लिखो(map, data->socdata->measure_freq_ctrl + REG_SET,
		     measure_freq << data->socdata->measure_freq_shअगरt);
	imx_set_alarm_temp(data, data->temp_passive);

	अगर (data->socdata->version == TEMPMON_IMX6SX)
		imx_set_panic_temp(data, data->temp_critical);

	regmap_ग_लिखो(map, data->socdata->sensor_ctrl + REG_CLR,
		     data->socdata->घातer_करोwn_mask);
	regmap_ग_लिखो(map, data->socdata->sensor_ctrl + REG_SET,
		     data->socdata->measure_temp_mask);

	data->irq_enabled = true;
	ret = thermal_zone_device_enable(data->tz);
	अगर (ret)
		जाओ thermal_zone_unरेजिस्टर;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, data->irq,
			imx_thermal_alarm_irq, imx_thermal_alarm_irq_thपढ़ो,
			0, "imx_thermal", data);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to request alarm irq: %d\n", ret);
		जाओ thermal_zone_unरेजिस्टर;
	पूर्ण

	वापस 0;

thermal_zone_unरेजिस्टर:
	thermal_zone_device_unरेजिस्टर(data->tz);
clk_disable:
	clk_disable_unprepare(data->thermal_clk);
legacy_cleanup:
	imx_thermal_unरेजिस्टर_legacy_cooling(data);

	वापस ret;
पूर्ण

अटल पूर्णांक imx_thermal_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_thermal_data *data = platक्रमm_get_drvdata(pdev);
	काष्ठा regmap *map = data->tempmon;

	/* Disable measurements */
	regmap_ग_लिखो(map, data->socdata->sensor_ctrl + REG_SET,
		     data->socdata->घातer_करोwn_mask);
	अगर (!IS_ERR(data->thermal_clk))
		clk_disable_unprepare(data->thermal_clk);

	thermal_zone_device_unरेजिस्टर(data->tz);
	imx_thermal_unरेजिस्टर_legacy_cooling(data);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imx_thermal_suspend(काष्ठा device *dev)
अणु
	काष्ठा imx_thermal_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;

	/*
	 * Need to disable thermal sensor, otherwise, when thermal core
	 * try to get temperature beक्रमe thermal sensor resume, a wrong
	 * temperature will be पढ़ो as the thermal sensor is घातered
	 * करोwn. This is करोne in change_mode() operation called from
	 * thermal_zone_device_disable()
	 */
	ret = thermal_zone_device_disable(data->tz);
	अगर (ret)
		वापस ret;
	clk_disable_unprepare(data->thermal_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imx_thermal_resume(काष्ठा device *dev)
अणु
	काष्ठा imx_thermal_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(data->thermal_clk);
	अगर (ret)
		वापस ret;
	/* Enabled thermal sensor after resume */
	ret = thermal_zone_device_enable(data->tz);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(imx_thermal_pm_ops,
			 imx_thermal_suspend, imx_thermal_resume);

अटल काष्ठा platक्रमm_driver imx_thermal = अणु
	.driver = अणु
		.name	= "imx_thermal",
		.pm	= &imx_thermal_pm_ops,
		.of_match_table = of_imx_thermal_match,
	पूर्ण,
	.probe		= imx_thermal_probe,
	.हटाओ		= imx_thermal_हटाओ,
पूर्ण;
module_platक्रमm_driver(imx_thermal);

MODULE_AUTHOR("Freescale Semiconductor, Inc.");
MODULE_DESCRIPTION("Thermal driver for Freescale i.MX SoCs");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:imx-thermal");
