<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Code shared between the dअगरferent Qualcomm PMIC voltage ADCs
 */

#अगर_अघोषित QCOM_VADC_COMMON_H
#घोषणा QCOM_VADC_COMMON_H

#समावेश <linux/types.h>

#घोषणा VADC_CONV_TIME_MIN_US			2000
#घोषणा VADC_CONV_TIME_MAX_US			2100

/* Min ADC code represents 0V */
#घोषणा VADC_MIN_ADC_CODE			0x6000
/* Max ADC code represents full-scale range of 1.8V */
#घोषणा VADC_MAX_ADC_CODE			0xa800

#घोषणा VADC_ABSOLUTE_RANGE_UV			625000
#घोषणा VADC_RATIOMETRIC_RANGE			1800

#घोषणा VADC_DEF_PRESCALING			0 /* 1:1 */
#घोषणा VADC_DEF_DECIMATION			0 /* 512 */
#घोषणा VADC_DEF_HW_SETTLE_TIME			0 /* 0 us */
#घोषणा VADC_DEF_AVG_SAMPLES			0 /* 1 sample */
#घोषणा VADC_DEF_CALIB_TYPE			VADC_CALIB_ABSOLUTE

#घोषणा VADC_DECIMATION_MIN			512
#घोषणा VADC_DECIMATION_MAX			4096
#घोषणा ADC5_DEF_VBAT_PRESCALING		1 /* 1:3 */
#घोषणा ADC5_DECIMATION_SHORT			250
#घोषणा ADC5_DECIMATION_MEDIUM			420
#घोषणा ADC5_DECIMATION_LONG			840
/* Default decimation - 1024 क्रम rev2, 840 क्रम pmic5 */
#घोषणा ADC5_DECIMATION_DEFAULT			2
#घोषणा ADC5_DECIMATION_SAMPLES_MAX		3

#घोषणा VADC_HW_SETTLE_DELAY_MAX		10000
#घोषणा VADC_HW_SETTLE_SAMPLES_MAX		16
#घोषणा VADC_AVG_SAMPLES_MAX			512
#घोषणा ADC5_AVG_SAMPLES_MAX			16

#घोषणा PMIC5_CHG_TEMP_SCALE_FACTOR		377500
#घोषणा PMIC5_SMB_TEMP_CONSTANT			419400
#घोषणा PMIC5_SMB_TEMP_SCALE_FACTOR		356

#घोषणा PMI_CHG_SCALE_1				-138890
#घोषणा PMI_CHG_SCALE_2				391750000000LL

#घोषणा VADC5_MAX_CODE				0x7fff
#घोषणा ADC5_FULL_SCALE_CODE			0x70e4
#घोषणा ADC5_USR_DATA_CHECK			0x8000

#घोषणा R_PU_100K				100000
#घोषणा RATIO_MAX_ADC7				BIT(14)

/*
 * VADC_CALIB_ABSOLUTE: uses the 625mV and 1.25V as reference channels.
 * VADC_CALIB_RATIOMETRIC: uses the reference voltage (1.8V) and GND क्रम
 * calibration.
 */
क्रमागत vadc_calibration अणु
	VADC_CALIB_ABSOLUTE = 0,
	VADC_CALIB_RATIOMETRIC
पूर्ण;

/**
 * काष्ठा vadc_linear_graph - Represent ADC अक्षरacteristics.
 * @dy: numerator slope to calculate the gain.
 * @dx: denominator slope to calculate the gain.
 * @gnd: A/D word of the ground reference used क्रम the channel.
 *
 * Each ADC device has dअगरferent offset and gain parameters which are
 * computed to calibrate the device.
 */
काष्ठा vadc_linear_graph अणु
	s32 dy;
	s32 dx;
	s32 gnd;
पूर्ण;

/**
 * काष्ठा vadc_prescale_ratio - Represent scaling ratio क्रम ADC input.
 * @num: the inverse numerator of the gain applied to the input channel.
 * @den: the inverse denominator of the gain applied to the input channel.
 */
काष्ठा vadc_prescale_ratio अणु
	u32 num;
	u32 den;
पूर्ण;

/**
 * क्रमागत vadc_scale_fn_type - Scaling function to convert ADC code to
 *				physical scaled units क्रम the channel.
 * SCALE_DEFAULT: Default scaling to convert raw adc code to voltage (uV).
 * SCALE_THERM_100K_PULLUP: Returns temperature in millidegC.
 *				 Uses a mapping table with 100K pullup.
 * SCALE_PMIC_THERM: Returns result in milli degree's Centigrade.
 * SCALE_XOTHERM: Returns XO thermistor voltage in millidegC.
 * SCALE_PMI_CHG_TEMP: Conversion क्रम PMI CHG temp
 * SCALE_HW_CALIB_DEFAULT: Default scaling to convert raw adc code to
 *	voltage (uV) with hardware applied offset/slope values to adc code.
 * SCALE_HW_CALIB_THERM_100K_PULLUP: Returns temperature in millidegC using
 *	lookup table. The hardware applies offset/slope to adc code.
 * SCALE_HW_CALIB_XOTHERM: Returns XO thermistor voltage in millidegC using
 *	100k pullup. The hardware applies offset/slope to adc code.
 * SCALE_HW_CALIB_THERM_100K_PU_PM7: Returns temperature in millidegC using
 *	lookup table क्रम PMIC7. The hardware applies offset/slope to adc code.
 * SCALE_HW_CALIB_PMIC_THERM: Returns result in milli degree's Centigrade.
 *	The hardware applies offset/slope to adc code.
 * SCALE_HW_CALIB_PMIC_THERM: Returns result in milli degree's Centigrade.
 *	The hardware applies offset/slope to adc code. This is क्रम PMIC7.
 * SCALE_HW_CALIB_PM5_CHG_TEMP: Returns result in millidegrees क्रम PMIC5
 *	अक्षरger temperature.
 * SCALE_HW_CALIB_PM5_SMB_TEMP: Returns result in millidegrees क्रम PMIC5
 *	SMB1390 temperature.
 */
क्रमागत vadc_scale_fn_type अणु
	SCALE_DEFAULT = 0,
	SCALE_THERM_100K_PULLUP,
	SCALE_PMIC_THERM,
	SCALE_XOTHERM,
	SCALE_PMI_CHG_TEMP,
	SCALE_HW_CALIB_DEFAULT,
	SCALE_HW_CALIB_THERM_100K_PULLUP,
	SCALE_HW_CALIB_XOTHERM,
	SCALE_HW_CALIB_THERM_100K_PU_PM7,
	SCALE_HW_CALIB_PMIC_THERM,
	SCALE_HW_CALIB_PMIC_THERM_PM7,
	SCALE_HW_CALIB_PM5_CHG_TEMP,
	SCALE_HW_CALIB_PM5_SMB_TEMP,
	SCALE_HW_CALIB_INVALID,
पूर्ण;

काष्ठा adc5_data अणु
	स्थिर u32	full_scale_code_volt;
	स्थिर u32	full_scale_code_cur;
	स्थिर काष्ठा adc5_channels *adc_chans;
	स्थिर काष्ठा iio_info *info;
	अचिन्हित पूर्णांक	*decimation;
	अचिन्हित पूर्णांक	*hw_settle_1;
	अचिन्हित पूर्णांक	*hw_settle_2;
पूर्ण;

पूर्णांक qcom_vadc_scale(क्रमागत vadc_scale_fn_type scaletype,
		    स्थिर काष्ठा vadc_linear_graph *calib_graph,
		    स्थिर काष्ठा vadc_prescale_ratio *prescale,
		    bool असलolute,
		    u16 adc_code, पूर्णांक *result_mdec);

काष्ठा qcom_adc5_scale_type अणु
	पूर्णांक (*scale_fn)(स्थिर काष्ठा vadc_prescale_ratio *prescale,
		स्थिर काष्ठा adc5_data *data, u16 adc_code, पूर्णांक *result);
पूर्ण;

पूर्णांक qcom_adc5_hw_scale(क्रमागत vadc_scale_fn_type scaletype,
		    अचिन्हित पूर्णांक prescale_ratio,
		    स्थिर काष्ठा adc5_data *data,
		    u16 adc_code, पूर्णांक *result_mdec);

u16 qcom_adc_पंचांग5_temp_volt_scale(अचिन्हित पूर्णांक prescale_ratio,
				 u32 full_scale_code_volt, पूर्णांक temp);

पूर्णांक qcom_adc5_prescaling_from_dt(u32 num, u32 den);

पूर्णांक qcom_adc5_hw_settle_समय_from_dt(u32 value, स्थिर अचिन्हित पूर्णांक *hw_settle);

पूर्णांक qcom_adc5_avg_samples_from_dt(u32 value);

पूर्णांक qcom_adc5_decimation_from_dt(u32 value, स्थिर अचिन्हित पूर्णांक *decimation);

पूर्णांक qcom_vadc_decimation_from_dt(u32 value);

#पूर्ण_अगर /* QCOM_VADC_COMMON_H */
