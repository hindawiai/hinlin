<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Device access क्रम Dialog DA9052 PMICs.
 *
 * Copyright(c) 2011 Dialog Semiconductor Ltd.
 *
 * Author: David Dajun Chen <dchen@diasemi.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/property.h>

#समावेश <linux/mfd/da9052/da9052.h>
#समावेश <linux/mfd/da9052/pdata.h>
#समावेश <linux/mfd/da9052/reg.h>

अटल bool da9052_reg_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल DA9052_PAGE0_CON_REG:
	हाल DA9052_STATUS_A_REG:
	हाल DA9052_STATUS_B_REG:
	हाल DA9052_STATUS_C_REG:
	हाल DA9052_STATUS_D_REG:
	हाल DA9052_EVENT_A_REG:
	हाल DA9052_EVENT_B_REG:
	हाल DA9052_EVENT_C_REG:
	हाल DA9052_EVENT_D_REG:
	हाल DA9052_FAULTLOG_REG:
	हाल DA9052_IRQ_MASK_A_REG:
	हाल DA9052_IRQ_MASK_B_REG:
	हाल DA9052_IRQ_MASK_C_REG:
	हाल DA9052_IRQ_MASK_D_REG:
	हाल DA9052_CONTROL_A_REG:
	हाल DA9052_CONTROL_B_REG:
	हाल DA9052_CONTROL_C_REG:
	हाल DA9052_CONTROL_D_REG:
	हाल DA9052_PDDIS_REG:
	हाल DA9052_INTERFACE_REG:
	हाल DA9052_RESET_REG:
	हाल DA9052_GPIO_0_1_REG:
	हाल DA9052_GPIO_2_3_REG:
	हाल DA9052_GPIO_4_5_REG:
	हाल DA9052_GPIO_6_7_REG:
	हाल DA9052_GPIO_8_9_REG:
	हाल DA9052_GPIO_10_11_REG:
	हाल DA9052_GPIO_12_13_REG:
	हाल DA9052_GPIO_14_15_REG:
	हाल DA9052_ID_0_1_REG:
	हाल DA9052_ID_2_3_REG:
	हाल DA9052_ID_4_5_REG:
	हाल DA9052_ID_6_7_REG:
	हाल DA9052_ID_8_9_REG:
	हाल DA9052_ID_10_11_REG:
	हाल DA9052_ID_12_13_REG:
	हाल DA9052_ID_14_15_REG:
	हाल DA9052_ID_16_17_REG:
	हाल DA9052_ID_18_19_REG:
	हाल DA9052_ID_20_21_REG:
	हाल DA9052_SEQ_STATUS_REG:
	हाल DA9052_SEQ_A_REG:
	हाल DA9052_SEQ_B_REG:
	हाल DA9052_SEQ_TIMER_REG:
	हाल DA9052_BUCKA_REG:
	हाल DA9052_BUCKB_REG:
	हाल DA9052_BUCKCORE_REG:
	हाल DA9052_BUCKPRO_REG:
	हाल DA9052_BUCKMEM_REG:
	हाल DA9052_BUCKPERI_REG:
	हाल DA9052_LDO1_REG:
	हाल DA9052_LDO2_REG:
	हाल DA9052_LDO3_REG:
	हाल DA9052_LDO4_REG:
	हाल DA9052_LDO5_REG:
	हाल DA9052_LDO6_REG:
	हाल DA9052_LDO7_REG:
	हाल DA9052_LDO8_REG:
	हाल DA9052_LDO9_REG:
	हाल DA9052_LDO10_REG:
	हाल DA9052_SUPPLY_REG:
	हाल DA9052_PULLDOWN_REG:
	हाल DA9052_CHGBUCK_REG:
	हाल DA9052_WAITCONT_REG:
	हाल DA9052_ISET_REG:
	हाल DA9052_BATCHG_REG:
	हाल DA9052_CHG_CONT_REG:
	हाल DA9052_INPUT_CONT_REG:
	हाल DA9052_CHG_TIME_REG:
	हाल DA9052_BBAT_CONT_REG:
	हाल DA9052_BOOST_REG:
	हाल DA9052_LED_CONT_REG:
	हाल DA9052_LEDMIN123_REG:
	हाल DA9052_LED1_CONF_REG:
	हाल DA9052_LED2_CONF_REG:
	हाल DA9052_LED3_CONF_REG:
	हाल DA9052_LED1CONT_REG:
	हाल DA9052_LED2CONT_REG:
	हाल DA9052_LED3CONT_REG:
	हाल DA9052_LED_CONT_4_REG:
	हाल DA9052_LED_CONT_5_REG:
	हाल DA9052_ADC_MAN_REG:
	हाल DA9052_ADC_CONT_REG:
	हाल DA9052_ADC_RES_L_REG:
	हाल DA9052_ADC_RES_H_REG:
	हाल DA9052_VDD_RES_REG:
	हाल DA9052_VDD_MON_REG:
	हाल DA9052_ICHG_AV_REG:
	हाल DA9052_ICHG_THD_REG:
	हाल DA9052_ICHG_END_REG:
	हाल DA9052_TBAT_RES_REG:
	हाल DA9052_TBAT_HIGHP_REG:
	हाल DA9052_TBAT_HIGHN_REG:
	हाल DA9052_TBAT_LOW_REG:
	हाल DA9052_T_OFFSET_REG:
	हाल DA9052_ADCIN4_RES_REG:
	हाल DA9052_AUTO4_HIGH_REG:
	हाल DA9052_AUTO4_LOW_REG:
	हाल DA9052_ADCIN5_RES_REG:
	हाल DA9052_AUTO5_HIGH_REG:
	हाल DA9052_AUTO5_LOW_REG:
	हाल DA9052_ADCIN6_RES_REG:
	हाल DA9052_AUTO6_HIGH_REG:
	हाल DA9052_AUTO6_LOW_REG:
	हाल DA9052_TJUNC_RES_REG:
	हाल DA9052_TSI_CONT_A_REG:
	हाल DA9052_TSI_CONT_B_REG:
	हाल DA9052_TSI_X_MSB_REG:
	हाल DA9052_TSI_Y_MSB_REG:
	हाल DA9052_TSI_LSB_REG:
	हाल DA9052_TSI_Z_MSB_REG:
	हाल DA9052_COUNT_S_REG:
	हाल DA9052_COUNT_MI_REG:
	हाल DA9052_COUNT_H_REG:
	हाल DA9052_COUNT_D_REG:
	हाल DA9052_COUNT_MO_REG:
	हाल DA9052_COUNT_Y_REG:
	हाल DA9052_ALARM_MI_REG:
	हाल DA9052_ALARM_H_REG:
	हाल DA9052_ALARM_D_REG:
	हाल DA9052_ALARM_MO_REG:
	हाल DA9052_ALARM_Y_REG:
	हाल DA9052_SECOND_A_REG:
	हाल DA9052_SECOND_B_REG:
	हाल DA9052_SECOND_C_REG:
	हाल DA9052_SECOND_D_REG:
	हाल DA9052_PAGE1_CON_REG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool da9052_reg_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल DA9052_PAGE0_CON_REG:
	हाल DA9052_EVENT_A_REG:
	हाल DA9052_EVENT_B_REG:
	हाल DA9052_EVENT_C_REG:
	हाल DA9052_EVENT_D_REG:
	हाल DA9052_FAULTLOG_REG:
	हाल DA9052_IRQ_MASK_A_REG:
	हाल DA9052_IRQ_MASK_B_REG:
	हाल DA9052_IRQ_MASK_C_REG:
	हाल DA9052_IRQ_MASK_D_REG:
	हाल DA9052_CONTROL_A_REG:
	हाल DA9052_CONTROL_B_REG:
	हाल DA9052_CONTROL_C_REG:
	हाल DA9052_CONTROL_D_REG:
	हाल DA9052_PDDIS_REG:
	हाल DA9052_RESET_REG:
	हाल DA9052_GPIO_0_1_REG:
	हाल DA9052_GPIO_2_3_REG:
	हाल DA9052_GPIO_4_5_REG:
	हाल DA9052_GPIO_6_7_REG:
	हाल DA9052_GPIO_8_9_REG:
	हाल DA9052_GPIO_10_11_REG:
	हाल DA9052_GPIO_12_13_REG:
	हाल DA9052_GPIO_14_15_REG:
	हाल DA9052_ID_0_1_REG:
	हाल DA9052_ID_2_3_REG:
	हाल DA9052_ID_4_5_REG:
	हाल DA9052_ID_6_7_REG:
	हाल DA9052_ID_8_9_REG:
	हाल DA9052_ID_10_11_REG:
	हाल DA9052_ID_12_13_REG:
	हाल DA9052_ID_14_15_REG:
	हाल DA9052_ID_16_17_REG:
	हाल DA9052_ID_18_19_REG:
	हाल DA9052_ID_20_21_REG:
	हाल DA9052_SEQ_STATUS_REG:
	हाल DA9052_SEQ_A_REG:
	हाल DA9052_SEQ_B_REG:
	हाल DA9052_SEQ_TIMER_REG:
	हाल DA9052_BUCKA_REG:
	हाल DA9052_BUCKB_REG:
	हाल DA9052_BUCKCORE_REG:
	हाल DA9052_BUCKPRO_REG:
	हाल DA9052_BUCKMEM_REG:
	हाल DA9052_BUCKPERI_REG:
	हाल DA9052_LDO1_REG:
	हाल DA9052_LDO2_REG:
	हाल DA9052_LDO3_REG:
	हाल DA9052_LDO4_REG:
	हाल DA9052_LDO5_REG:
	हाल DA9052_LDO6_REG:
	हाल DA9052_LDO7_REG:
	हाल DA9052_LDO8_REG:
	हाल DA9052_LDO9_REG:
	हाल DA9052_LDO10_REG:
	हाल DA9052_SUPPLY_REG:
	हाल DA9052_PULLDOWN_REG:
	हाल DA9052_CHGBUCK_REG:
	हाल DA9052_WAITCONT_REG:
	हाल DA9052_ISET_REG:
	हाल DA9052_BATCHG_REG:
	हाल DA9052_CHG_CONT_REG:
	हाल DA9052_INPUT_CONT_REG:
	हाल DA9052_BBAT_CONT_REG:
	हाल DA9052_BOOST_REG:
	हाल DA9052_LED_CONT_REG:
	हाल DA9052_LEDMIN123_REG:
	हाल DA9052_LED1_CONF_REG:
	हाल DA9052_LED2_CONF_REG:
	हाल DA9052_LED3_CONF_REG:
	हाल DA9052_LED1CONT_REG:
	हाल DA9052_LED2CONT_REG:
	हाल DA9052_LED3CONT_REG:
	हाल DA9052_LED_CONT_4_REG:
	हाल DA9052_LED_CONT_5_REG:
	हाल DA9052_ADC_MAN_REG:
	हाल DA9052_ADC_CONT_REG:
	हाल DA9052_ADC_RES_L_REG:
	हाल DA9052_ADC_RES_H_REG:
	हाल DA9052_VDD_RES_REG:
	हाल DA9052_VDD_MON_REG:
	हाल DA9052_ICHG_THD_REG:
	हाल DA9052_ICHG_END_REG:
	हाल DA9052_TBAT_HIGHP_REG:
	हाल DA9052_TBAT_HIGHN_REG:
	हाल DA9052_TBAT_LOW_REG:
	हाल DA9052_T_OFFSET_REG:
	हाल DA9052_AUTO4_HIGH_REG:
	हाल DA9052_AUTO4_LOW_REG:
	हाल DA9052_AUTO5_HIGH_REG:
	हाल DA9052_AUTO5_LOW_REG:
	हाल DA9052_AUTO6_HIGH_REG:
	हाल DA9052_AUTO6_LOW_REG:
	हाल DA9052_TSI_CONT_A_REG:
	हाल DA9052_TSI_CONT_B_REG:
	हाल DA9052_COUNT_S_REG:
	हाल DA9052_COUNT_MI_REG:
	हाल DA9052_COUNT_H_REG:
	हाल DA9052_COUNT_D_REG:
	हाल DA9052_COUNT_MO_REG:
	हाल DA9052_COUNT_Y_REG:
	हाल DA9052_ALARM_MI_REG:
	हाल DA9052_ALARM_H_REG:
	हाल DA9052_ALARM_D_REG:
	हाल DA9052_ALARM_MO_REG:
	हाल DA9052_ALARM_Y_REG:
	हाल DA9052_PAGE1_CON_REG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool da9052_reg_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल DA9052_STATUS_A_REG:
	हाल DA9052_STATUS_B_REG:
	हाल DA9052_STATUS_C_REG:
	हाल DA9052_STATUS_D_REG:
	हाल DA9052_EVENT_A_REG:
	हाल DA9052_EVENT_B_REG:
	हाल DA9052_EVENT_C_REG:
	हाल DA9052_EVENT_D_REG:
	हाल DA9052_CONTROL_B_REG:
	हाल DA9052_CONTROL_D_REG:
	हाल DA9052_SUPPLY_REG:
	हाल DA9052_FAULTLOG_REG:
	हाल DA9052_CHG_TIME_REG:
	हाल DA9052_ADC_RES_L_REG:
	हाल DA9052_ADC_RES_H_REG:
	हाल DA9052_VDD_RES_REG:
	हाल DA9052_ICHG_AV_REG:
	हाल DA9052_TBAT_RES_REG:
	हाल DA9052_ADCIN4_RES_REG:
	हाल DA9052_ADCIN5_RES_REG:
	हाल DA9052_ADCIN6_RES_REG:
	हाल DA9052_TJUNC_RES_REG:
	हाल DA9052_TSI_X_MSB_REG:
	हाल DA9052_TSI_Y_MSB_REG:
	हाल DA9052_TSI_LSB_REG:
	हाल DA9052_TSI_Z_MSB_REG:
	हाल DA9052_COUNT_S_REG:
	हाल DA9052_COUNT_MI_REG:
	हाल DA9052_COUNT_H_REG:
	हाल DA9052_COUNT_D_REG:
	हाल DA9052_COUNT_MO_REG:
	हाल DA9052_COUNT_Y_REG:
	हाल DA9052_ALARM_MI_REG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * TBAT look-up table is computed from the R90 reg (8 bit रेजिस्टर)
 * पढ़ोing as below. The battery temperature is in milliCentigrade
 * TBAT = (1/(t1+1/298) - 273) * 1000 mC
 * where t1 = (1/B)* ln(( ADCval * 2.5)/(R25*ITBAT*255))
 * Default values are R25 = 10e3, B = 3380, ITBAT = 50e-6
 * Example:
 * R25=10E3, B=3380, ITBAT=50e-6, ADCVAL=62d calculates
 * TBAT = 20015 mili degrees Centrigrade
 *
*/
अटल स्थिर पूर्णांक32_t tbat_lookup[255] = अणु
	183258, 144221, 124334, 111336, 101826, 94397, 88343, 83257,
	78889, 75071, 71688, 68656, 65914, 63414, 61120, 59001,
	570366, 55204, 53490, 51881, 50364, 48931, 47574, 46285,
	45059, 43889, 42772, 41703, 40678, 39694, 38748, 37838,
	36961, 36115, 35297, 34507, 33743, 33002, 32284, 31588,
	30911, 30254, 29615, 28994, 28389, 27799, 27225, 26664,
	26117, 25584, 25062, 24553, 24054, 23567, 23091, 22624,
	22167, 21719, 21281, 20851, 20429, 20015, 19610, 19211,
	18820, 18436, 18058, 17688, 17323, 16965, 16612, 16266,
	15925, 15589, 15259, 14933, 14613, 14298, 13987, 13681,
	13379, 13082, 12788, 12499, 12214, 11933, 11655, 11382,
	11112, 10845, 10582, 10322, 10066, 9812, 9562, 9315,
	9071, 8830, 8591, 8356, 8123, 7893, 7665, 7440,
	7218, 6998, 6780, 6565, 6352, 6141, 5933, 5726,
	5522, 5320, 5120, 4922, 4726, 4532, 4340, 4149,
	3961, 3774, 3589, 3406, 3225, 3045, 2867, 2690,
	2516, 2342, 2170, 2000, 1831, 1664, 1498, 1334,
	1171, 1009, 849, 690, 532, 376, 221, 67,
	-84, -236, -386, -535, -683, -830, -975, -1119,
	-1263, -1405, -1546, -1686, -1825, -1964, -2101, -2237,
	-2372, -2506, -2639, -2771, -2902, -3033, -3162, -3291,
	-3418, -3545, -3671, -3796, -3920, -4044, -4166, -4288,
	-4409, -4529, -4649, -4767, -4885, -5002, -5119, -5235,
	-5349, -5464, -5577, -5690, -5802, -5913, -6024, -6134,
	-6244, -6352, -6461, -6568, -6675, -6781, -6887, -6992,
	-7096, -7200, -7303, -7406, -7508, -7609, -7710, -7810,
	-7910, -8009, -8108, -8206, -8304, -8401, -8497, -8593,
	-8689, -8784, -8878, -8972, -9066, -9159, -9251, -9343,
	-9435, -9526, -9617, -9707, -9796, -9886, -9975, -10063,
	-10151, -10238, -10325, -10412, -10839, -10923, -11007, -11090,
	-11173, -11256, -11338, -11420, -11501, -11583, -11663, -11744,
	-11823, -11903, -11982
पूर्ण;

अटल स्थिर u8 chan_mux[DA9052_ADC_VBBAT + 1] = अणु
	[DA9052_ADC_VDDOUT]	= DA9052_ADC_MAN_MUXSEL_VDDOUT,
	[DA9052_ADC_ICH]	= DA9052_ADC_MAN_MUXSEL_ICH,
	[DA9052_ADC_TBAT]	= DA9052_ADC_MAN_MUXSEL_TBAT,
	[DA9052_ADC_VBAT]	= DA9052_ADC_MAN_MUXSEL_VBAT,
	[DA9052_ADC_IN4]	= DA9052_ADC_MAN_MUXSEL_AD4,
	[DA9052_ADC_IN5]	= DA9052_ADC_MAN_MUXSEL_AD5,
	[DA9052_ADC_IN6]	= DA9052_ADC_MAN_MUXSEL_AD6,
	[DA9052_ADC_VBBAT]	= DA9052_ADC_MAN_MUXSEL_VBBAT
पूर्ण;

पूर्णांक da9052_adc_manual_पढ़ो(काष्ठा da9052 *da9052, अचिन्हित अक्षर channel)
अणु
	पूर्णांक ret;
	अचिन्हित लघु calc_data;
	अचिन्हित लघु data;
	अचिन्हित अक्षर mux_sel;

	अगर (channel > DA9052_ADC_VBBAT)
		वापस -EINVAL;

	mutex_lock(&da9052->auxadc_lock);

	reinit_completion(&da9052->करोne);

	/* Channel माला_लो activated on enabling the Conversion bit */
	mux_sel = chan_mux[channel] | DA9052_ADC_MAN_MAN_CONV;

	ret = da9052_reg_ग_लिखो(da9052, DA9052_ADC_MAN_REG, mux_sel);
	अगर (ret < 0)
		जाओ err;

	/* Wait क्रम an पूर्णांकerrupt */
	अगर (!रुको_क्रम_completion_समयout(&da9052->करोne,
					 msecs_to_jअगरfies(500))) अणु
		dev_err(da9052->dev,
			"timeout waiting for ADC conversion interrupt\n");
		ret = -ETIMEDOUT;
		जाओ err;
	पूर्ण

	ret = da9052_reg_पढ़ो(da9052, DA9052_ADC_RES_H_REG);
	अगर (ret < 0)
		जाओ err;

	calc_data = (अचिन्हित लघु)ret;
	data = calc_data << 2;

	ret = da9052_reg_पढ़ो(da9052, DA9052_ADC_RES_L_REG);
	अगर (ret < 0)
		जाओ err;

	calc_data = (अचिन्हित लघु)(ret & DA9052_ADC_RES_LSB);
	data |= calc_data;

	ret = data;

err:
	mutex_unlock(&da9052->auxadc_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(da9052_adc_manual_पढ़ो);

पूर्णांक da9052_adc_पढ़ो_temp(काष्ठा da9052 *da9052)
अणु
	पूर्णांक tbat;

	tbat = da9052_reg_पढ़ो(da9052, DA9052_TBAT_RES_REG);
	अगर (tbat <= 0)
		वापस tbat;

	/* ARRAY_SIZE check is not needed since TBAT is a 8-bit रेजिस्टर */
	वापस tbat_lookup[tbat - 1];
पूर्ण
EXPORT_SYMBOL_GPL(da9052_adc_पढ़ो_temp);

अटल स्थिर काष्ठा mfd_cell da9052_subdev_info[] = अणु
	अणु
		.name = "da9052-regulator",
		.id = 0,
	पूर्ण,
	अणु
		.name = "da9052-regulator",
		.id = 1,
	पूर्ण,
	अणु
		.name = "da9052-regulator",
		.id = 2,
	पूर्ण,
	अणु
		.name = "da9052-regulator",
		.id = 3,
	पूर्ण,
	अणु
		.name = "da9052-regulator",
		.id = 4,
	पूर्ण,
	अणु
		.name = "da9052-regulator",
		.id = 5,
	पूर्ण,
	अणु
		.name = "da9052-regulator",
		.id = 6,
	पूर्ण,
	अणु
		.name = "da9052-regulator",
		.id = 7,
	पूर्ण,
	अणु
		.name = "da9052-regulator",
		.id = 8,
	पूर्ण,
	अणु
		.name = "da9052-regulator",
		.id = 9,
	पूर्ण,
	अणु
		.name = "da9052-regulator",
		.id = 10,
	पूर्ण,
	अणु
		.name = "da9052-regulator",
		.id = 11,
	पूर्ण,
	अणु
		.name = "da9052-regulator",
		.id = 12,
	पूर्ण,
	अणु
		.name = "da9052-regulator",
		.id = 13,
	पूर्ण,
	अणु
		.name = "da9052-onkey",
	पूर्ण,
	अणु
		.name = "da9052-rtc",
	पूर्ण,
	अणु
		.name = "da9052-gpio",
	पूर्ण,
	अणु
		.name = "da9052-hwmon",
	पूर्ण,
	अणु
		.name = "da9052-leds",
	पूर्ण,
	अणु
		.name = "da9052-wled1",
	पूर्ण,
	अणु
		.name = "da9052-wled2",
	पूर्ण,
	अणु
		.name = "da9052-wled3",
	पूर्ण,
	अणु
		.name = "da9052-bat",
	पूर्ण,
	अणु
		.name = "da9052-watchdog",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell da9052_tsi_subdev_info[] = अणु
	अणु .name = "da9052-tsi" पूर्ण,
पूर्ण;

स्थिर काष्ठा regmap_config da9052_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.cache_type = REGCACHE_RBTREE,

	.max_रेजिस्टर = DA9052_PAGE1_CON_REG,
	.पढ़ोable_reg = da9052_reg_पढ़ोable,
	.ग_लिखोable_reg = da9052_reg_ग_लिखोable,
	.अस्थिर_reg = da9052_reg_अस्थिर,
पूर्ण;
EXPORT_SYMBOL_GPL(da9052_regmap_config);

अटल पूर्णांक da9052_clear_fault_log(काष्ठा da9052 *da9052)
अणु
	पूर्णांक ret = 0;
	पूर्णांक fault_log = 0;

	fault_log = da9052_reg_पढ़ो(da9052, DA9052_FAULTLOG_REG);
	अगर (fault_log < 0) अणु
		dev_err(da9052->dev,
			"Cannot read FAULT_LOG %d\n", fault_log);
		वापस fault_log;
	पूर्ण

	अगर (fault_log) अणु
		अगर (fault_log & DA9052_FAULTLOG_TWDERROR)
			dev_dbg(da9052->dev,
				"Fault log entry detected: TWD_ERROR\n");
		अगर (fault_log & DA9052_FAULTLOG_VDDFAULT)
			dev_dbg(da9052->dev,
				"Fault log entry detected: VDD_FAULT\n");
		अगर (fault_log & DA9052_FAULTLOG_VDDSTART)
			dev_dbg(da9052->dev,
				"Fault log entry detected: VDD_START\n");
		अगर (fault_log & DA9052_FAULTLOG_TEMPOVER)
			dev_dbg(da9052->dev,
				"Fault log entry detected: TEMP_OVER\n");
		अगर (fault_log & DA9052_FAULTLOG_KEYSHUT)
			dev_dbg(da9052->dev,
				"Fault log entry detected: KEY_SHUT\n");
		अगर (fault_log & DA9052_FAULTLOG_NSDSET)
			dev_dbg(da9052->dev,
				"Fault log entry detected: nSD_SHUT\n");
		अगर (fault_log & DA9052_FAULTLOG_WAITSET)
			dev_dbg(da9052->dev,
				"Fault log entry detected: WAIT_SHUT\n");

		ret = da9052_reg_ग_लिखो(da9052,
					DA9052_FAULTLOG_REG,
					0xFF);
		अगर (ret < 0)
			dev_err(da9052->dev,
				"Cannot reset FAULT_LOG values %d\n", ret);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक da9052_device_init(काष्ठा da9052 *da9052, u8 chip_id)
अणु
	काष्ठा da9052_pdata *pdata = dev_get_platdata(da9052->dev);
	पूर्णांक ret;

	mutex_init(&da9052->auxadc_lock);
	init_completion(&da9052->करोne);

	ret = da9052_clear_fault_log(da9052);
	अगर (ret < 0)
		dev_warn(da9052->dev, "Cannot clear FAULT_LOG\n");

	अगर (pdata && pdata->init != शून्य)
		pdata->init(da9052);

	da9052->chip_id = chip_id;

	ret = da9052_irq_init(da9052);
	अगर (ret != 0) अणु
		dev_err(da9052->dev, "da9052_irq_init failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = mfd_add_devices(da9052->dev, PLATFORM_DEVID_AUTO,
			      da9052_subdev_info,
			      ARRAY_SIZE(da9052_subdev_info), शून्य, 0, शून्य);
	अगर (ret) अणु
		dev_err(da9052->dev, "mfd_add_devices failed: %d\n", ret);
		जाओ err;
	पूर्ण

	/*
	 * Check अगर touchscreen pins are used are analogue input instead
	 * of having a touchscreen connected to them. The analogue input
	 * functionality will be provided by hwmon driver (अगर enabled).
	 */
	अगर (!device_property_पढ़ो_bool(da9052->dev, "dlg,tsi-as-adc")) अणु
		ret = mfd_add_devices(da9052->dev, PLATFORM_DEVID_AUTO,
				      da9052_tsi_subdev_info,
				      ARRAY_SIZE(da9052_tsi_subdev_info),
				      शून्य, 0, शून्य);
		अगर (ret) अणु
			dev_err(da9052->dev, "failed to add TSI subdev: %d\n",
				ret);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	mfd_हटाओ_devices(da9052->dev);
	da9052_irq_निकास(da9052);

	वापस ret;
पूर्ण

व्योम da9052_device_निकास(काष्ठा da9052 *da9052)
अणु
	mfd_हटाओ_devices(da9052->dev);
	da9052_irq_निकास(da9052);
पूर्ण

MODULE_AUTHOR("David Dajun Chen <dchen@diasemi.com>");
MODULE_DESCRIPTION("DA9052 MFD Core");
MODULE_LICENSE("GPL");
