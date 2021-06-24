<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/fixp-arith.h>
#समावेश <linux/iio/adc/qcom-vadc-common.h>
#समावेश <linux/math64.h>
#समावेश <linux/log2.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/units.h>

/**
 * काष्ठा vadc_map_pt - Map the graph representation क्रम ADC channel
 * @x: Represent the ADC digitized code.
 * @y: Represent the physical data which can be temperature, voltage,
 *     resistance.
 */
काष्ठा vadc_map_pt अणु
	s32 x;
	s32 y;
पूर्ण;

/* Voltage to temperature */
अटल स्थिर काष्ठा vadc_map_pt adcmap_100k_104ef_104fb[] = अणु
	अणु1758,	-40000 पूर्ण,
	अणु1742,	-35000 पूर्ण,
	अणु1719,	-30000 पूर्ण,
	अणु1691,	-25000 पूर्ण,
	अणु1654,	-20000 पूर्ण,
	अणु1608,	-15000 पूर्ण,
	अणु1551,	-10000 पूर्ण,
	अणु1483,	-5000 पूर्ण,
	अणु1404,	0 पूर्ण,
	अणु1315,	5000 पूर्ण,
	अणु1218,	10000 पूर्ण,
	अणु1114,	15000 पूर्ण,
	अणु1007,	20000 पूर्ण,
	अणु900,	25000 पूर्ण,
	अणु795,	30000 पूर्ण,
	अणु696,	35000 पूर्ण,
	अणु605,	40000 पूर्ण,
	अणु522,	45000 पूर्ण,
	अणु448,	50000 पूर्ण,
	अणु383,	55000 पूर्ण,
	अणु327,	60000 पूर्ण,
	अणु278,	65000 पूर्ण,
	अणु237,	70000 पूर्ण,
	अणु202,	75000 पूर्ण,
	अणु172,	80000 पूर्ण,
	अणु146,	85000 पूर्ण,
	अणु125,	90000 पूर्ण,
	अणु107,	95000 पूर्ण,
	अणु92,	100000 पूर्ण,
	अणु79,	105000 पूर्ण,
	अणु68,	110000 पूर्ण,
	अणु59,	115000 पूर्ण,
	अणु51,	120000 पूर्ण,
	अणु44,	125000 पूर्ण
पूर्ण;

/*
 * Voltage to temperature table क्रम 100k pull up क्रम NTCG104EF104 with
 * 1.875V reference.
 */
अटल स्थिर काष्ठा vadc_map_pt adcmap_100k_104ef_104fb_1875_vref[] = अणु
	अणु 1831,	-40000 पूर्ण,
	अणु 1814,	-35000 पूर्ण,
	अणु 1791,	-30000 पूर्ण,
	अणु 1761,	-25000 पूर्ण,
	अणु 1723,	-20000 पूर्ण,
	अणु 1675,	-15000 पूर्ण,
	अणु 1616,	-10000 पूर्ण,
	अणु 1545,	-5000 पूर्ण,
	अणु 1463,	0 पूर्ण,
	अणु 1370,	5000 पूर्ण,
	अणु 1268,	10000 पूर्ण,
	अणु 1160,	15000 पूर्ण,
	अणु 1049,	20000 पूर्ण,
	अणु 937,	25000 पूर्ण,
	अणु 828,	30000 पूर्ण,
	अणु 726,	35000 पूर्ण,
	अणु 630,	40000 पूर्ण,
	अणु 544,	45000 पूर्ण,
	अणु 467,	50000 पूर्ण,
	अणु 399,	55000 पूर्ण,
	अणु 340,	60000 पूर्ण,
	अणु 290,	65000 पूर्ण,
	अणु 247,	70000 पूर्ण,
	अणु 209,	75000 पूर्ण,
	अणु 179,	80000 पूर्ण,
	अणु 153,	85000 पूर्ण,
	अणु 130,	90000 पूर्ण,
	अणु 112,	95000 पूर्ण,
	अणु 96,	100000 पूर्ण,
	अणु 82,	105000 पूर्ण,
	अणु 71,	110000 पूर्ण,
	अणु 62,	115000 पूर्ण,
	अणु 53,	120000 पूर्ण,
	अणु 46,	125000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vadc_map_pt adcmap7_die_temp[] = अणु
	अणु 857300, 160000 पूर्ण,
	अणु 820100, 140000 पूर्ण,
	अणु 782500, 120000 पूर्ण,
	अणु 744600, 100000 पूर्ण,
	अणु 706400, 80000 पूर्ण,
	अणु 667900, 60000 पूर्ण,
	अणु 629300, 40000 पूर्ण,
	अणु 590500, 20000 पूर्ण,
	अणु 551500, 0 पूर्ण,
	अणु 512400, -20000 पूर्ण,
	अणु 473100, -40000 पूर्ण,
	अणु 433700, -60000 पूर्ण,
पूर्ण;

/*
 * Resistance to temperature table क्रम 100k pull up क्रम NTCG104EF104.
 */
अटल स्थिर काष्ठा vadc_map_pt adcmap7_100k[] = अणु
	अणु 4250657, -40960 पूर्ण,
	अणु 3962085, -39936 पूर्ण,
	अणु 3694875, -38912 पूर्ण,
	अणु 3447322, -37888 पूर्ण,
	अणु 3217867, -36864 पूर्ण,
	अणु 3005082, -35840 पूर्ण,
	अणु 2807660, -34816 पूर्ण,
	अणु 2624405, -33792 पूर्ण,
	अणु 2454218, -32768 पूर्ण,
	अणु 2296094, -31744 पूर्ण,
	अणु 2149108, -30720 पूर्ण,
	अणु 2012414, -29696 पूर्ण,
	अणु 1885232, -28672 पूर्ण,
	अणु 1766846, -27648 पूर्ण,
	अणु 1656598, -26624 पूर्ण,
	अणु 1553884, -25600 पूर्ण,
	अणु 1458147, -24576 पूर्ण,
	अणु 1368873, -23552 पूर्ण,
	अणु 1285590, -22528 पूर्ण,
	अणु 1207863, -21504 पूर्ण,
	अणु 1135290, -20480 पूर्ण,
	अणु 1067501, -19456 पूर्ण,
	अणु 1004155, -18432 पूर्ण,
	अणु 944935, -17408 पूर्ण,
	अणु 889550, -16384 पूर्ण,
	अणु 837731, -15360 पूर्ण,
	अणु 789229, -14336 पूर्ण,
	अणु 743813, -13312 पूर्ण,
	अणु 701271, -12288 पूर्ण,
	अणु 661405, -11264 पूर्ण,
	अणु 624032, -10240 पूर्ण,
	अणु 588982, -9216 पूर्ण,
	अणु 556100, -8192 पूर्ण,
	अणु 525239, -7168 पूर्ण,
	अणु 496264, -6144 पूर्ण,
	अणु 469050, -5120 पूर्ण,
	अणु 443480, -4096 पूर्ण,
	अणु 419448, -3072 पूर्ण,
	अणु 396851, -2048 पूर्ण,
	अणु 375597, -1024 पूर्ण,
	अणु 355598, 0 पूर्ण,
	अणु 336775, 1024 पूर्ण,
	अणु 319052, 2048 पूर्ण,
	अणु 302359, 3072 पूर्ण,
	अणु 286630, 4096 पूर्ण,
	अणु 271806, 5120 पूर्ण,
	अणु 257829, 6144 पूर्ण,
	अणु 244646, 7168 पूर्ण,
	अणु 232209, 8192 पूर्ण,
	अणु 220471, 9216 पूर्ण,
	अणु 209390, 10240 पूर्ण,
	अणु 198926, 11264 पूर्ण,
	अणु 189040, 12288 पूर्ण,
	अणु 179698, 13312 पूर्ण,
	अणु 170868, 14336 पूर्ण,
	अणु 162519, 15360 पूर्ण,
	अणु 154622, 16384 पूर्ण,
	अणु 147150, 17408 पूर्ण,
	अणु 140079, 18432 पूर्ण,
	अणु 133385, 19456 पूर्ण,
	अणु 127046, 20480 पूर्ण,
	अणु 121042, 21504 पूर्ण,
	अणु 115352, 22528 पूर्ण,
	अणु 109960, 23552 पूर्ण,
	अणु 104848, 24576 पूर्ण,
	अणु 100000, 25600 पूर्ण,
	अणु 95402, 26624 पूर्ण,
	अणु 91038, 27648 पूर्ण,
	अणु 86897, 28672 पूर्ण,
	अणु 82965, 29696 पूर्ण,
	अणु 79232, 30720 पूर्ण,
	अणु 75686, 31744 पूर्ण,
	अणु 72316, 32768 पूर्ण,
	अणु 69114, 33792 पूर्ण,
	अणु 66070, 34816 पूर्ण,
	अणु 63176, 35840 पूर्ण,
	अणु 60423, 36864 पूर्ण,
	अणु 57804, 37888 पूर्ण,
	अणु 55312, 38912 पूर्ण,
	अणु 52940, 39936 पूर्ण,
	अणु 50681, 40960 पूर्ण,
	अणु 48531, 41984 पूर्ण,
	अणु 46482, 43008 पूर्ण,
	अणु 44530, 44032 पूर्ण,
	अणु 42670, 45056 पूर्ण,
	अणु 40897, 46080 पूर्ण,
	अणु 39207, 47104 पूर्ण,
	अणु 37595, 48128 पूर्ण,
	अणु 36057, 49152 पूर्ण,
	अणु 34590, 50176 पूर्ण,
	अणु 33190, 51200 पूर्ण,
	अणु 31853, 52224 पूर्ण,
	अणु 30577, 53248 पूर्ण,
	अणु 29358, 54272 पूर्ण,
	अणु 28194, 55296 पूर्ण,
	अणु 27082, 56320 पूर्ण,
	अणु 26020, 57344 पूर्ण,
	अणु 25004, 58368 पूर्ण,
	अणु 24033, 59392 पूर्ण,
	अणु 23104, 60416 पूर्ण,
	अणु 22216, 61440 पूर्ण,
	अणु 21367, 62464 पूर्ण,
	अणु 20554, 63488 पूर्ण,
	अणु 19776, 64512 पूर्ण,
	अणु 19031, 65536 पूर्ण,
	अणु 18318, 66560 पूर्ण,
	अणु 17636, 67584 पूर्ण,
	अणु 16982, 68608 पूर्ण,
	अणु 16355, 69632 पूर्ण,
	अणु 15755, 70656 पूर्ण,
	अणु 15180, 71680 पूर्ण,
	अणु 14628, 72704 पूर्ण,
	अणु 14099, 73728 पूर्ण,
	अणु 13592, 74752 पूर्ण,
	अणु 13106, 75776 पूर्ण,
	अणु 12640, 76800 पूर्ण,
	अणु 12192, 77824 पूर्ण,
	अणु 11762, 78848 पूर्ण,
	अणु 11350, 79872 पूर्ण,
	अणु 10954, 80896 पूर्ण,
	अणु 10574, 81920 पूर्ण,
	अणु 10209, 82944 पूर्ण,
	अणु 9858, 83968 पूर्ण,
	अणु 9521, 84992 पूर्ण,
	अणु 9197, 86016 पूर्ण,
	अणु 8886, 87040 पूर्ण,
	अणु 8587, 88064 पूर्ण,
	अणु 8299, 89088 पूर्ण,
	अणु 8023, 90112 पूर्ण,
	अणु 7757, 91136 पूर्ण,
	अणु 7501, 92160 पूर्ण,
	अणु 7254, 93184 पूर्ण,
	अणु 7017, 94208 पूर्ण,
	अणु 6789, 95232 पूर्ण,
	अणु 6570, 96256 पूर्ण,
	अणु 6358, 97280 पूर्ण,
	अणु 6155, 98304 पूर्ण,
	अणु 5959, 99328 पूर्ण,
	अणु 5770, 100352 पूर्ण,
	अणु 5588, 101376 पूर्ण,
	अणु 5412, 102400 पूर्ण,
	अणु 5243, 103424 पूर्ण,
	अणु 5080, 104448 पूर्ण,
	अणु 4923, 105472 पूर्ण,
	अणु 4771, 106496 पूर्ण,
	अणु 4625, 107520 पूर्ण,
	अणु 4484, 108544 पूर्ण,
	अणु 4348, 109568 पूर्ण,
	अणु 4217, 110592 पूर्ण,
	अणु 4090, 111616 पूर्ण,
	अणु 3968, 112640 पूर्ण,
	अणु 3850, 113664 पूर्ण,
	अणु 3736, 114688 पूर्ण,
	अणु 3626, 115712 पूर्ण,
	अणु 3519, 116736 पूर्ण,
	अणु 3417, 117760 पूर्ण,
	अणु 3317, 118784 पूर्ण,
	अणु 3221, 119808 पूर्ण,
	अणु 3129, 120832 पूर्ण,
	अणु 3039, 121856 पूर्ण,
	अणु 2952, 122880 पूर्ण,
	अणु 2868, 123904 पूर्ण,
	अणु 2787, 124928 पूर्ण,
	अणु 2709, 125952 पूर्ण,
	अणु 2633, 126976 पूर्ण,
	अणु 2560, 128000 पूर्ण,
	अणु 2489, 129024 पूर्ण,
	अणु 2420, 130048 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा vadc_prescale_ratio adc5_prescale_ratios[] = अणु
	अणु.num =  1, .den =  1पूर्ण,
	अणु.num =  1, .den =  3पूर्ण,
	अणु.num =  1, .den =  4पूर्ण,
	अणु.num =  1, .den =  6पूर्ण,
	अणु.num =  1, .den = 20पूर्ण,
	अणु.num =  1, .den =  8पूर्ण,
	अणु.num = 10, .den = 81पूर्ण,
	अणु.num =  1, .den = 10पूर्ण,
	अणु.num =  1, .den = 16पूर्ण
पूर्ण;

अटल पूर्णांक qcom_vadc_scale_hw_calib_volt(
				स्थिर काष्ठा vadc_prescale_ratio *prescale,
				स्थिर काष्ठा adc5_data *data,
				u16 adc_code, पूर्णांक *result_uv);
अटल पूर्णांक qcom_vadc_scale_hw_calib_therm(
				स्थिर काष्ठा vadc_prescale_ratio *prescale,
				स्थिर काष्ठा adc5_data *data,
				u16 adc_code, पूर्णांक *result_mdec);
अटल पूर्णांक qcom_vadc7_scale_hw_calib_therm(
				स्थिर काष्ठा vadc_prescale_ratio *prescale,
				स्थिर काष्ठा adc5_data *data,
				u16 adc_code, पूर्णांक *result_mdec);
अटल पूर्णांक qcom_vadc_scale_hw_smb_temp(
				स्थिर काष्ठा vadc_prescale_ratio *prescale,
				स्थिर काष्ठा adc5_data *data,
				u16 adc_code, पूर्णांक *result_mdec);
अटल पूर्णांक qcom_vadc_scale_hw_chg5_temp(
				स्थिर काष्ठा vadc_prescale_ratio *prescale,
				स्थिर काष्ठा adc5_data *data,
				u16 adc_code, पूर्णांक *result_mdec);
अटल पूर्णांक qcom_vadc_scale_hw_calib_die_temp(
				स्थिर काष्ठा vadc_prescale_ratio *prescale,
				स्थिर काष्ठा adc5_data *data,
				u16 adc_code, पूर्णांक *result_mdec);
अटल पूर्णांक qcom_vadc7_scale_hw_calib_die_temp(
				स्थिर काष्ठा vadc_prescale_ratio *prescale,
				स्थिर काष्ठा adc5_data *data,
				u16 adc_code, पूर्णांक *result_mdec);

अटल काष्ठा qcom_adc5_scale_type scale_adc5_fn[] = अणु
	[SCALE_HW_CALIB_DEFAULT] = अणुqcom_vadc_scale_hw_calib_voltपूर्ण,
	[SCALE_HW_CALIB_THERM_100K_PULLUP] = अणुqcom_vadc_scale_hw_calib_thermपूर्ण,
	[SCALE_HW_CALIB_XOTHERM] = अणुqcom_vadc_scale_hw_calib_thermपूर्ण,
	[SCALE_HW_CALIB_THERM_100K_PU_PM7] = अणु
					qcom_vadc7_scale_hw_calib_thermपूर्ण,
	[SCALE_HW_CALIB_PMIC_THERM] = अणुqcom_vadc_scale_hw_calib_die_tempपूर्ण,
	[SCALE_HW_CALIB_PMIC_THERM_PM7] = अणु
					qcom_vadc7_scale_hw_calib_die_tempपूर्ण,
	[SCALE_HW_CALIB_PM5_CHG_TEMP] = अणुqcom_vadc_scale_hw_chg5_tempपूर्ण,
	[SCALE_HW_CALIB_PM5_SMB_TEMP] = अणुqcom_vadc_scale_hw_smb_tempपूर्ण,
पूर्ण;

अटल पूर्णांक qcom_vadc_map_voltage_temp(स्थिर काष्ठा vadc_map_pt *pts,
				      u32 tablesize, s32 input, पूर्णांक *output)
अणु
	u32 i = 0;

	अगर (!pts)
		वापस -EINVAL;

	जबतक (i < tablesize && pts[i].x > input)
		i++;

	अगर (i == 0) अणु
		*output = pts[0].y;
	पूर्ण अन्यथा अगर (i == tablesize) अणु
		*output = pts[tablesize - 1].y;
	पूर्ण अन्यथा अणु
		/* पूर्णांकerpolate linearly */
		*output = fixp_linear_पूर्णांकerpolate(pts[i - 1].x, pts[i - 1].y,
						  pts[i].x, pts[i].y,
						  input);
	पूर्ण

	वापस 0;
पूर्ण

अटल s32 qcom_vadc_map_temp_voltage(स्थिर काष्ठा vadc_map_pt *pts,
				      u32 tablesize, पूर्णांक input)
अणु
	u32 i = 0;

	/*
	 * Table must be sorted, find the पूर्णांकerval of 'y' which contains value
	 * 'input' and map it to proper 'x' value
	 */
	जबतक (i < tablesize && pts[i].y < input)
		i++;

	अगर (i == 0)
		वापस pts[0].x;
	अगर (i == tablesize)
		वापस pts[tablesize - 1].x;

	/* पूर्णांकerpolate linearly */
	वापस fixp_linear_पूर्णांकerpolate(pts[i - 1].y, pts[i - 1].x,
			pts[i].y, pts[i].x, input);
पूर्ण

अटल व्योम qcom_vadc_scale_calib(स्थिर काष्ठा vadc_linear_graph *calib_graph,
				  u16 adc_code,
				  bool असलolute,
				  s64 *scale_voltage)
अणु
	*scale_voltage = (adc_code - calib_graph->gnd);
	*scale_voltage *= calib_graph->dx;
	*scale_voltage = भाग64_s64(*scale_voltage, calib_graph->dy);
	अगर (असलolute)
		*scale_voltage += calib_graph->dx;

	अगर (*scale_voltage < 0)
		*scale_voltage = 0;
पूर्ण

अटल पूर्णांक qcom_vadc_scale_volt(स्थिर काष्ठा vadc_linear_graph *calib_graph,
				स्थिर काष्ठा vadc_prescale_ratio *prescale,
				bool असलolute, u16 adc_code,
				पूर्णांक *result_uv)
अणु
	s64 voltage = 0, result = 0;

	qcom_vadc_scale_calib(calib_graph, adc_code, असलolute, &voltage);

	voltage = voltage * prescale->den;
	result = भाग64_s64(voltage, prescale->num);
	*result_uv = result;

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_vadc_scale_therm(स्थिर काष्ठा vadc_linear_graph *calib_graph,
				 स्थिर काष्ठा vadc_prescale_ratio *prescale,
				 bool असलolute, u16 adc_code,
				 पूर्णांक *result_mdec)
अणु
	s64 voltage = 0;
	पूर्णांक ret;

	qcom_vadc_scale_calib(calib_graph, adc_code, असलolute, &voltage);

	अगर (असलolute)
		voltage = भाग64_s64(voltage, 1000);

	ret = qcom_vadc_map_voltage_temp(adcmap_100k_104ef_104fb,
					 ARRAY_SIZE(adcmap_100k_104ef_104fb),
					 voltage, result_mdec);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_vadc_scale_die_temp(स्थिर काष्ठा vadc_linear_graph *calib_graph,
				    स्थिर काष्ठा vadc_prescale_ratio *prescale,
				    bool असलolute,
				    u16 adc_code, पूर्णांक *result_mdec)
अणु
	s64 voltage = 0;
	u64 temp; /* Temporary variable क्रम करो_भाग */

	qcom_vadc_scale_calib(calib_graph, adc_code, असलolute, &voltage);

	अगर (voltage > 0) अणु
		temp = voltage * prescale->den;
		करो_भाग(temp, prescale->num * 2);
		voltage = temp;
	पूर्ण अन्यथा अणु
		voltage = 0;
	पूर्ण

	*result_mdec = milli_kelvin_to_millicelsius(voltage);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_vadc_scale_chg_temp(स्थिर काष्ठा vadc_linear_graph *calib_graph,
				    स्थिर काष्ठा vadc_prescale_ratio *prescale,
				    bool असलolute,
				    u16 adc_code, पूर्णांक *result_mdec)
अणु
	s64 voltage = 0, result = 0;

	qcom_vadc_scale_calib(calib_graph, adc_code, असलolute, &voltage);

	voltage = voltage * prescale->den;
	voltage = भाग64_s64(voltage, prescale->num);
	voltage = ((PMI_CHG_SCALE_1) * (voltage * 2));
	voltage = (voltage + PMI_CHG_SCALE_2);
	result =  भाग64_s64(voltage, 1000000);
	*result_mdec = result;

	वापस 0;
पूर्ण

/* convert voltage to ADC code, using 1.875V reference */
अटल u16 qcom_vadc_scale_voltage_code(s32 voltage,
					स्थिर काष्ठा vadc_prescale_ratio *prescale,
					स्थिर u32 full_scale_code_volt,
					अचिन्हित पूर्णांक factor)
अणु
	s64 volt = voltage;
	s64 adc_vdd_ref_mv = 1875; /* reference voltage */

	volt *= prescale->num * factor * full_scale_code_volt;
	volt = भाग64_s64(volt, (s64)prescale->den * adc_vdd_ref_mv * 1000);

	वापस volt;
पूर्ण

अटल पूर्णांक qcom_vadc_scale_code_voltage_factor(u16 adc_code,
				स्थिर काष्ठा vadc_prescale_ratio *prescale,
				स्थिर काष्ठा adc5_data *data,
				अचिन्हित पूर्णांक factor)
अणु
	s64 voltage, temp, adc_vdd_ref_mv = 1875;

	/*
	 * The normal data range is between 0V to 1.875V. On हालs where
	 * we पढ़ो low voltage values, the ADC code can go beyond the
	 * range and the scale result is incorrect so we clamp the values
	 * क्रम the हालs where the code represents a value below 0V
	 */
	अगर (adc_code > VADC5_MAX_CODE)
		adc_code = 0;

	/* (ADC code * vref_vadc (1.875V)) / full_scale_code */
	voltage = (s64) adc_code * adc_vdd_ref_mv * 1000;
	voltage = भाग64_s64(voltage, data->full_scale_code_volt);
	अगर (voltage > 0) अणु
		voltage *= prescale->den;
		temp = prescale->num * factor;
		voltage = भाग64_s64(voltage, temp);
	पूर्ण अन्यथा अणु
		voltage = 0;
	पूर्ण

	वापस (पूर्णांक) voltage;
पूर्ण

अटल पूर्णांक qcom_vadc7_scale_hw_calib_therm(
				स्थिर काष्ठा vadc_prescale_ratio *prescale,
				स्थिर काष्ठा adc5_data *data,
				u16 adc_code, पूर्णांक *result_mdec)
अणु
	s64 resistance = adc_code;
	पूर्णांक ret, result;

	अगर (adc_code >= RATIO_MAX_ADC7)
		वापस -EINVAL;

	/* (ADC code * R_PULLUP (100Kohm)) / (full_scale_code - ADC code)*/
	resistance *= R_PU_100K;
	resistance = भाग64_s64(resistance, RATIO_MAX_ADC7 - adc_code);

	ret = qcom_vadc_map_voltage_temp(adcmap7_100k,
				 ARRAY_SIZE(adcmap7_100k),
				 resistance, &result);
	अगर (ret)
		वापस ret;

	*result_mdec = result;

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_vadc_scale_hw_calib_volt(
				स्थिर काष्ठा vadc_prescale_ratio *prescale,
				स्थिर काष्ठा adc5_data *data,
				u16 adc_code, पूर्णांक *result_uv)
अणु
	*result_uv = qcom_vadc_scale_code_voltage_factor(adc_code,
				prescale, data, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_vadc_scale_hw_calib_therm(
				स्थिर काष्ठा vadc_prescale_ratio *prescale,
				स्थिर काष्ठा adc5_data *data,
				u16 adc_code, पूर्णांक *result_mdec)
अणु
	पूर्णांक voltage;

	voltage = qcom_vadc_scale_code_voltage_factor(adc_code,
				prescale, data, 1000);

	/* Map voltage to temperature from look-up table */
	वापस qcom_vadc_map_voltage_temp(adcmap_100k_104ef_104fb_1875_vref,
				 ARRAY_SIZE(adcmap_100k_104ef_104fb_1875_vref),
				 voltage, result_mdec);
पूर्ण

अटल पूर्णांक qcom_vadc_scale_hw_calib_die_temp(
				स्थिर काष्ठा vadc_prescale_ratio *prescale,
				स्थिर काष्ठा adc5_data *data,
				u16 adc_code, पूर्णांक *result_mdec)
अणु
	*result_mdec = qcom_vadc_scale_code_voltage_factor(adc_code,
				prescale, data, 2);
	*result_mdec = milli_kelvin_to_millicelsius(*result_mdec);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_vadc7_scale_hw_calib_die_temp(
				स्थिर काष्ठा vadc_prescale_ratio *prescale,
				स्थिर काष्ठा adc5_data *data,
				u16 adc_code, पूर्णांक *result_mdec)
अणु

	पूर्णांक voltage;

	voltage = qcom_vadc_scale_code_voltage_factor(adc_code,
				prescale, data, 1);

	वापस qcom_vadc_map_voltage_temp(adcmap7_die_temp, ARRAY_SIZE(adcmap7_die_temp),
			voltage, result_mdec);
पूर्ण

अटल पूर्णांक qcom_vadc_scale_hw_smb_temp(
				स्थिर काष्ठा vadc_prescale_ratio *prescale,
				स्थिर काष्ठा adc5_data *data,
				u16 adc_code, पूर्णांक *result_mdec)
अणु
	*result_mdec = qcom_vadc_scale_code_voltage_factor(adc_code * 100,
				prescale, data, PMIC5_SMB_TEMP_SCALE_FACTOR);
	*result_mdec = PMIC5_SMB_TEMP_CONSTANT - *result_mdec;

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_vadc_scale_hw_chg5_temp(
				स्थिर काष्ठा vadc_prescale_ratio *prescale,
				स्थिर काष्ठा adc5_data *data,
				u16 adc_code, पूर्णांक *result_mdec)
अणु
	*result_mdec = qcom_vadc_scale_code_voltage_factor(adc_code,
				prescale, data, 4);
	*result_mdec = PMIC5_CHG_TEMP_SCALE_FACTOR - *result_mdec;

	वापस 0;
पूर्ण

पूर्णांक qcom_vadc_scale(क्रमागत vadc_scale_fn_type scaletype,
		    स्थिर काष्ठा vadc_linear_graph *calib_graph,
		    स्थिर काष्ठा vadc_prescale_ratio *prescale,
		    bool असलolute,
		    u16 adc_code, पूर्णांक *result)
अणु
	चयन (scaletype) अणु
	हाल SCALE_DEFAULT:
		वापस qcom_vadc_scale_volt(calib_graph, prescale,
					    असलolute, adc_code,
					    result);
	हाल SCALE_THERM_100K_PULLUP:
	हाल SCALE_XOTHERM:
		वापस qcom_vadc_scale_therm(calib_graph, prescale,
					     असलolute, adc_code,
					     result);
	हाल SCALE_PMIC_THERM:
		वापस qcom_vadc_scale_die_temp(calib_graph, prescale,
						असलolute, adc_code,
						result);
	हाल SCALE_PMI_CHG_TEMP:
		वापस qcom_vadc_scale_chg_temp(calib_graph, prescale,
						असलolute, adc_code,
						result);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(qcom_vadc_scale);

u16 qcom_adc_पंचांग5_temp_volt_scale(अचिन्हित पूर्णांक prescale_ratio,
				 u32 full_scale_code_volt, पूर्णांक temp)
अणु
	स्थिर काष्ठा vadc_prescale_ratio *prescale = &adc5_prescale_ratios[prescale_ratio];
	s32 voltage;

	voltage = qcom_vadc_map_temp_voltage(adcmap_100k_104ef_104fb_1875_vref,
					     ARRAY_SIZE(adcmap_100k_104ef_104fb_1875_vref),
					     temp);
	वापस qcom_vadc_scale_voltage_code(voltage, prescale, full_scale_code_volt, 1000);
पूर्ण
EXPORT_SYMBOL(qcom_adc_पंचांग5_temp_volt_scale);

पूर्णांक qcom_adc5_hw_scale(क्रमागत vadc_scale_fn_type scaletype,
		    अचिन्हित पूर्णांक prescale_ratio,
		    स्थिर काष्ठा adc5_data *data,
		    u16 adc_code, पूर्णांक *result)
अणु
	स्थिर काष्ठा vadc_prescale_ratio *prescale = &adc5_prescale_ratios[prescale_ratio];

	अगर (!(scaletype >= SCALE_HW_CALIB_DEFAULT &&
		scaletype < SCALE_HW_CALIB_INVALID)) अणु
		pr_err("Invalid scale type %d\n", scaletype);
		वापस -EINVAL;
	पूर्ण

	वापस scale_adc5_fn[scaletype].scale_fn(prescale, data,
					adc_code, result);
पूर्ण
EXPORT_SYMBOL(qcom_adc5_hw_scale);

पूर्णांक qcom_adc5_prescaling_from_dt(u32 num, u32 den)
अणु
	अचिन्हित पूर्णांक pre;

	क्रम (pre = 0; pre < ARRAY_SIZE(adc5_prescale_ratios); pre++)
		अगर (adc5_prescale_ratios[pre].num == num &&
		    adc5_prescale_ratios[pre].den == den)
			अवरोध;

	अगर (pre == ARRAY_SIZE(adc5_prescale_ratios))
		वापस -EINVAL;

	वापस pre;
पूर्ण
EXPORT_SYMBOL(qcom_adc5_prescaling_from_dt);

पूर्णांक qcom_adc5_hw_settle_समय_from_dt(u32 value,
				     स्थिर अचिन्हित पूर्णांक *hw_settle)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < VADC_HW_SETTLE_SAMPLES_MAX; i++) अणु
		अगर (value == hw_settle[i])
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(qcom_adc5_hw_settle_समय_from_dt);

पूर्णांक qcom_adc5_avg_samples_from_dt(u32 value)
अणु
	अगर (!is_घातer_of_2(value) || value > ADC5_AVG_SAMPLES_MAX)
		वापस -EINVAL;

	वापस __ffs(value);
पूर्ण
EXPORT_SYMBOL(qcom_adc5_avg_samples_from_dt);

पूर्णांक qcom_adc5_decimation_from_dt(u32 value, स्थिर अचिन्हित पूर्णांक *decimation)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ADC5_DECIMATION_SAMPLES_MAX; i++) अणु
		अगर (value == decimation[i])
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(qcom_adc5_decimation_from_dt);

पूर्णांक qcom_vadc_decimation_from_dt(u32 value)
अणु
	अगर (!is_घातer_of_2(value) || value < VADC_DECIMATION_MIN ||
	    value > VADC_DECIMATION_MAX)
		वापस -EINVAL;

	वापस __ffs64(value / VADC_DECIMATION_MIN);
पूर्ण
EXPORT_SYMBOL(qcom_vadc_decimation_from_dt);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Qualcomm ADC common functionality");
