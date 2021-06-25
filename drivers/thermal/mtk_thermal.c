<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 MediaTek Inc.
 * Author: Hanyi Wu <hanyi.wu@mediatek.com>
 *         Sascha Hauer <s.hauer@pengutronix.de>
 *         Dawei Chien <dawei.chien@mediatek.com>
 *         Louis Yu <louis.yu@mediatek.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/thermal.h>
#समावेश <linux/reset.h>
#समावेश <linux/types.h>

/* AUXADC Registers */
#घोषणा AUXADC_CON1_SET_V	0x008
#घोषणा AUXADC_CON1_CLR_V	0x00c
#घोषणा AUXADC_CON2_V		0x010
#घोषणा AUXADC_DATA(channel)	(0x14 + (channel) * 4)

#घोषणा APMIXED_SYS_TS_CON1	0x604

/* Thermal Controller Registers */
#घोषणा TEMP_MONCTL0		0x000
#घोषणा TEMP_MONCTL1		0x004
#घोषणा TEMP_MONCTL2		0x008
#घोषणा TEMP_MONIDET0		0x014
#घोषणा TEMP_MONIDET1		0x018
#घोषणा TEMP_MSRCTL0		0x038
#घोषणा TEMP_MSRCTL1		0x03c
#घोषणा TEMP_AHBPOLL		0x040
#घोषणा TEMP_AHBTO		0x044
#घोषणा TEMP_ADCPNP0		0x048
#घोषणा TEMP_ADCPNP1		0x04c
#घोषणा TEMP_ADCPNP2		0x050
#घोषणा TEMP_ADCPNP3		0x0b4

#घोषणा TEMP_ADCMUX		0x054
#घोषणा TEMP_ADCEN		0x060
#घोषणा TEMP_PNPMUXADDR		0x064
#घोषणा TEMP_ADCMUXADDR		0x068
#घोषणा TEMP_ADCENADDR		0x074
#घोषणा TEMP_ADCVALIDADDR	0x078
#घोषणा TEMP_ADCVOLTADDR	0x07c
#घोषणा TEMP_RDCTRL		0x080
#घोषणा TEMP_ADCVALIDMASK	0x084
#घोषणा TEMP_ADCVOLTAGESHIFT	0x088
#घोषणा TEMP_ADCWRITECTRL	0x08c
#घोषणा TEMP_MSR0		0x090
#घोषणा TEMP_MSR1		0x094
#घोषणा TEMP_MSR2		0x098
#घोषणा TEMP_MSR3		0x0B8

#घोषणा TEMP_SPARE0		0x0f0

#घोषणा TEMP_ADCPNP0_1          0x148
#घोषणा TEMP_ADCPNP1_1          0x14c
#घोषणा TEMP_ADCPNP2_1          0x150
#घोषणा TEMP_MSR0_1             0x190
#घोषणा TEMP_MSR1_1             0x194
#घोषणा TEMP_MSR2_1             0x198
#घोषणा TEMP_ADCPNP3_1          0x1b4
#घोषणा TEMP_MSR3_1             0x1B8

#घोषणा PTPCORESEL		0x400

#घोषणा TEMP_MONCTL1_PERIOD_UNIT(x)	((x) & 0x3ff)

#घोषणा TEMP_MONCTL2_FILTER_INTERVAL(x)	(((x) & 0x3ff) << 16)
#घोषणा TEMP_MONCTL2_SENSOR_INTERVAL(x)	((x) & 0x3ff)

#घोषणा TEMP_AHBPOLL_ADC_POLL_INTERVAL(x)	(x)

#घोषणा TEMP_ADCWRITECTRL_ADC_PNP_WRITE		BIT(0)
#घोषणा TEMP_ADCWRITECTRL_ADC_MUX_WRITE		BIT(1)

#घोषणा TEMP_ADCVALIDMASK_VALID_HIGH		BIT(5)
#घोषणा TEMP_ADCVALIDMASK_VALID_POS(bit)	(bit)

/* MT8173 thermal sensors */
#घोषणा MT8173_TS1	0
#घोषणा MT8173_TS2	1
#घोषणा MT8173_TS3	2
#घोषणा MT8173_TS4	3
#घोषणा MT8173_TSABB	4

/* AUXADC channel 11 is used क्रम the temperature sensors */
#घोषणा MT8173_TEMP_AUXADC_CHANNEL	11

/* The total number of temperature sensors in the MT8173 */
#घोषणा MT8173_NUM_SENSORS		5

/* The number of banks in the MT8173 */
#घोषणा MT8173_NUM_ZONES		4

/* The number of sensing poपूर्णांकs per bank */
#घोषणा MT8173_NUM_SENSORS_PER_ZONE	4

/* The number of controller in the MT8173 */
#घोषणा MT8173_NUM_CONTROLLER		1

/* The calibration coefficient of sensor  */
#घोषणा MT8173_CALIBRATION	165

/*
 * Layout of the fuses providing the calibration data
 * These macros could be used क्रम MT8183, MT8173, MT2701, and MT2712.
 * MT8183 has 6 sensors and needs 6 VTS calibration data.
 * MT8173 has 5 sensors and needs 5 VTS calibration data.
 * MT2701 has 3 sensors and needs 3 VTS calibration data.
 * MT2712 has 4 sensors and needs 4 VTS calibration data.
 */
#घोषणा CALIB_BUF0_VALID_V1		BIT(0)
#घोषणा CALIB_BUF1_ADC_GE_V1(x)		(((x) >> 22) & 0x3ff)
#घोषणा CALIB_BUF0_VTS_TS1_V1(x)	(((x) >> 17) & 0x1ff)
#घोषणा CALIB_BUF0_VTS_TS2_V1(x)	(((x) >> 8) & 0x1ff)
#घोषणा CALIB_BUF1_VTS_TS3_V1(x)	(((x) >> 0) & 0x1ff)
#घोषणा CALIB_BUF2_VTS_TS4_V1(x)	(((x) >> 23) & 0x1ff)
#घोषणा CALIB_BUF2_VTS_TS5_V1(x)	(((x) >> 5) & 0x1ff)
#घोषणा CALIB_BUF2_VTS_TSABB_V1(x)	(((x) >> 14) & 0x1ff)
#घोषणा CALIB_BUF0_DEGC_CALI_V1(x)	(((x) >> 1) & 0x3f)
#घोषणा CALIB_BUF0_O_SLOPE_V1(x)	(((x) >> 26) & 0x3f)
#घोषणा CALIB_BUF0_O_SLOPE_SIGN_V1(x)	(((x) >> 7) & 0x1)
#घोषणा CALIB_BUF1_ID_V1(x)		(((x) >> 9) & 0x1)

/*
 * Layout of the fuses providing the calibration data
 * These macros could be used क्रम MT7622.
 */
#घोषणा CALIB_BUF0_ADC_OE_V2(x)		(((x) >> 22) & 0x3ff)
#घोषणा CALIB_BUF0_ADC_GE_V2(x)		(((x) >> 12) & 0x3ff)
#घोषणा CALIB_BUF0_DEGC_CALI_V2(x)	(((x) >> 6) & 0x3f)
#घोषणा CALIB_BUF0_O_SLOPE_V2(x)	(((x) >> 0) & 0x3f)
#घोषणा CALIB_BUF1_VTS_TS1_V2(x)	(((x) >> 23) & 0x1ff)
#घोषणा CALIB_BUF1_VTS_TS2_V2(x)	(((x) >> 14) & 0x1ff)
#घोषणा CALIB_BUF1_VTS_TSABB_V2(x)	(((x) >> 5) & 0x1ff)
#घोषणा CALIB_BUF1_VALID_V2(x)		(((x) >> 4) & 0x1)
#घोषणा CALIB_BUF1_O_SLOPE_SIGN_V2(x)	(((x) >> 3) & 0x1)

क्रमागत अणु
	VTS1,
	VTS2,
	VTS3,
	VTS4,
	VTS5,
	VTSABB,
	MAX_NUM_VTS,
पूर्ण;

क्रमागत mtk_thermal_version अणु
	MTK_THERMAL_V1 = 1,
	MTK_THERMAL_V2,
पूर्ण;

/* MT2701 thermal sensors */
#घोषणा MT2701_TS1	0
#घोषणा MT2701_TS2	1
#घोषणा MT2701_TSABB	2

/* AUXADC channel 11 is used क्रम the temperature sensors */
#घोषणा MT2701_TEMP_AUXADC_CHANNEL	11

/* The total number of temperature sensors in the MT2701 */
#घोषणा MT2701_NUM_SENSORS	3

/* The number of sensing poपूर्णांकs per bank */
#घोषणा MT2701_NUM_SENSORS_PER_ZONE	3

/* The number of controller in the MT2701 */
#घोषणा MT2701_NUM_CONTROLLER		1

/* The calibration coefficient of sensor  */
#घोषणा MT2701_CALIBRATION	165

/* MT2712 thermal sensors */
#घोषणा MT2712_TS1	0
#घोषणा MT2712_TS2	1
#घोषणा MT2712_TS3	2
#घोषणा MT2712_TS4	3

/* AUXADC channel 11 is used क्रम the temperature sensors */
#घोषणा MT2712_TEMP_AUXADC_CHANNEL	11

/* The total number of temperature sensors in the MT2712 */
#घोषणा MT2712_NUM_SENSORS	4

/* The number of sensing poपूर्णांकs per bank */
#घोषणा MT2712_NUM_SENSORS_PER_ZONE	4

/* The number of controller in the MT2712 */
#घोषणा MT2712_NUM_CONTROLLER		1

/* The calibration coefficient of sensor  */
#घोषणा MT2712_CALIBRATION	165

#घोषणा MT7622_TEMP_AUXADC_CHANNEL	11
#घोषणा MT7622_NUM_SENSORS		1
#घोषणा MT7622_NUM_ZONES		1
#घोषणा MT7622_NUM_SENSORS_PER_ZONE	1
#घोषणा MT7622_TS1	0
#घोषणा MT7622_NUM_CONTROLLER		1

/* The maximum number of banks */
#घोषणा MAX_NUM_ZONES		8

/* The calibration coefficient of sensor  */
#घोषणा MT7622_CALIBRATION	165

/* MT8183 thermal sensors */
#घोषणा MT8183_TS1	0
#घोषणा MT8183_TS2	1
#घोषणा MT8183_TS3	2
#घोषणा MT8183_TS4	3
#घोषणा MT8183_TS5	4
#घोषणा MT8183_TSABB	5

/* AUXADC channel  is used क्रम the temperature sensors */
#घोषणा MT8183_TEMP_AUXADC_CHANNEL	11

/* The total number of temperature sensors in the MT8183 */
#घोषणा MT8183_NUM_SENSORS	6

/* The number of banks in the MT8183 */
#घोषणा MT8183_NUM_ZONES               1

/* The number of sensing poपूर्णांकs per bank */
#घोषणा MT8183_NUM_SENSORS_PER_ZONE	 6

/* The number of controller in the MT8183 */
#घोषणा MT8183_NUM_CONTROLLER		2

/* The calibration coefficient of sensor  */
#घोषणा MT8183_CALIBRATION	153

काष्ठा mtk_thermal;

काष्ठा thermal_bank_cfg अणु
	अचिन्हित पूर्णांक num_sensors;
	स्थिर पूर्णांक *sensors;
पूर्ण;

काष्ठा mtk_thermal_bank अणु
	काष्ठा mtk_thermal *mt;
	पूर्णांक id;
पूर्ण;

काष्ठा mtk_thermal_data अणु
	s32 num_banks;
	s32 num_sensors;
	s32 auxadc_channel;
	स्थिर पूर्णांक *vts_index;
	स्थिर पूर्णांक *sensor_mux_values;
	स्थिर पूर्णांक *msr;
	स्थिर पूर्णांक *adcpnp;
	स्थिर पूर्णांक cali_val;
	स्थिर पूर्णांक num_controller;
	स्थिर पूर्णांक *controller_offset;
	bool need_चयन_bank;
	काष्ठा thermal_bank_cfg bank_data[MAX_NUM_ZONES];
	क्रमागत mtk_thermal_version version;
पूर्ण;

काष्ठा mtk_thermal अणु
	काष्ठा device *dev;
	व्योम __iomem *thermal_base;

	काष्ठा clk *clk_peri_therm;
	काष्ठा clk *clk_auxadc;
	/* lock: क्रम getting and putting banks */
	काष्ठा mutex lock;

	/* Calibration values */
	s32 adc_ge;
	s32 adc_oe;
	s32 degc_cali;
	s32 o_slope;
	s32 o_slope_sign;
	s32 vts[MAX_NUM_VTS];

	स्थिर काष्ठा mtk_thermal_data *conf;
	काष्ठा mtk_thermal_bank banks[MAX_NUM_ZONES];
पूर्ण;

/* MT8183 thermal sensor data */
अटल स्थिर पूर्णांक mt8183_bank_data[MT8183_NUM_SENSORS] = अणु
	MT8183_TS1, MT8183_TS2, MT8183_TS3, MT8183_TS4, MT8183_TS5, MT8183_TSABB
पूर्ण;

अटल स्थिर पूर्णांक mt8183_msr[MT8183_NUM_SENSORS_PER_ZONE] = अणु
	TEMP_MSR0_1, TEMP_MSR1_1, TEMP_MSR2_1, TEMP_MSR1, TEMP_MSR0, TEMP_MSR3_1
पूर्ण;

अटल स्थिर पूर्णांक mt8183_adcpnp[MT8183_NUM_SENSORS_PER_ZONE] = अणु
	TEMP_ADCPNP0_1, TEMP_ADCPNP1_1, TEMP_ADCPNP2_1,
	TEMP_ADCPNP1, TEMP_ADCPNP0, TEMP_ADCPNP3_1
पूर्ण;

अटल स्थिर पूर्णांक mt8183_mux_values[MT8183_NUM_SENSORS] = अणु 0, 1, 2, 3, 4, 0 पूर्ण;
अटल स्थिर पूर्णांक mt8183_tc_offset[MT8183_NUM_CONTROLLER] = अणु0x0, 0x100पूर्ण;

अटल स्थिर पूर्णांक mt8183_vts_index[MT8183_NUM_SENSORS] = अणु
	VTS1, VTS2, VTS3, VTS4, VTS5, VTSABB
पूर्ण;

/* MT8173 thermal sensor data */
अटल स्थिर पूर्णांक mt8173_bank_data[MT8173_NUM_ZONES][3] = अणु
	अणु MT8173_TS2, MT8173_TS3 पूर्ण,
	अणु MT8173_TS2, MT8173_TS4 पूर्ण,
	अणु MT8173_TS1, MT8173_TS2, MT8173_TSABB पूर्ण,
	अणु MT8173_TS2 पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक mt8173_msr[MT8173_NUM_SENSORS_PER_ZONE] = अणु
	TEMP_MSR0, TEMP_MSR1, TEMP_MSR2, TEMP_MSR3
पूर्ण;

अटल स्थिर पूर्णांक mt8173_adcpnp[MT8173_NUM_SENSORS_PER_ZONE] = अणु
	TEMP_ADCPNP0, TEMP_ADCPNP1, TEMP_ADCPNP2, TEMP_ADCPNP3
पूर्ण;

अटल स्थिर पूर्णांक mt8173_mux_values[MT8173_NUM_SENSORS] = अणु 0, 1, 2, 3, 16 पूर्ण;
अटल स्थिर पूर्णांक mt8173_tc_offset[MT8173_NUM_CONTROLLER] = अणु 0x0, पूर्ण;

अटल स्थिर पूर्णांक mt8173_vts_index[MT8173_NUM_SENSORS] = अणु
	VTS1, VTS2, VTS3, VTS4, VTSABB
पूर्ण;

/* MT2701 thermal sensor data */
अटल स्थिर पूर्णांक mt2701_bank_data[MT2701_NUM_SENSORS] = अणु
	MT2701_TS1, MT2701_TS2, MT2701_TSABB
पूर्ण;

अटल स्थिर पूर्णांक mt2701_msr[MT2701_NUM_SENSORS_PER_ZONE] = अणु
	TEMP_MSR0, TEMP_MSR1, TEMP_MSR2
पूर्ण;

अटल स्थिर पूर्णांक mt2701_adcpnp[MT2701_NUM_SENSORS_PER_ZONE] = अणु
	TEMP_ADCPNP0, TEMP_ADCPNP1, TEMP_ADCPNP2
पूर्ण;

अटल स्थिर पूर्णांक mt2701_mux_values[MT2701_NUM_SENSORS] = अणु 0, 1, 16 पूर्ण;
अटल स्थिर पूर्णांक mt2701_tc_offset[MT2701_NUM_CONTROLLER] = अणु 0x0, पूर्ण;

अटल स्थिर पूर्णांक mt2701_vts_index[MT2701_NUM_SENSORS] = अणु
	VTS1, VTS2, VTS3
पूर्ण;

/* MT2712 thermal sensor data */
अटल स्थिर पूर्णांक mt2712_bank_data[MT2712_NUM_SENSORS] = अणु
	MT2712_TS1, MT2712_TS2, MT2712_TS3, MT2712_TS4
पूर्ण;

अटल स्थिर पूर्णांक mt2712_msr[MT2712_NUM_SENSORS_PER_ZONE] = अणु
	TEMP_MSR0, TEMP_MSR1, TEMP_MSR2, TEMP_MSR3
पूर्ण;

अटल स्थिर पूर्णांक mt2712_adcpnp[MT2712_NUM_SENSORS_PER_ZONE] = अणु
	TEMP_ADCPNP0, TEMP_ADCPNP1, TEMP_ADCPNP2, TEMP_ADCPNP3
पूर्ण;

अटल स्थिर पूर्णांक mt2712_mux_values[MT2712_NUM_SENSORS] = अणु 0, 1, 2, 3 पूर्ण;
अटल स्थिर पूर्णांक mt2712_tc_offset[MT2712_NUM_CONTROLLER] = अणु 0x0, पूर्ण;

अटल स्थिर पूर्णांक mt2712_vts_index[MT2712_NUM_SENSORS] = अणु
	VTS1, VTS2, VTS3, VTS4
पूर्ण;

/* MT7622 thermal sensor data */
अटल स्थिर पूर्णांक mt7622_bank_data[MT7622_NUM_SENSORS] = अणु MT7622_TS1, पूर्ण;
अटल स्थिर पूर्णांक mt7622_msr[MT7622_NUM_SENSORS_PER_ZONE] = अणु TEMP_MSR0, पूर्ण;
अटल स्थिर पूर्णांक mt7622_adcpnp[MT7622_NUM_SENSORS_PER_ZONE] = अणु TEMP_ADCPNP0, पूर्ण;
अटल स्थिर पूर्णांक mt7622_mux_values[MT7622_NUM_SENSORS] = अणु 0, पूर्ण;
अटल स्थिर पूर्णांक mt7622_vts_index[MT7622_NUM_SENSORS] = अणु VTS1 पूर्ण;
अटल स्थिर पूर्णांक mt7622_tc_offset[MT7622_NUM_CONTROLLER] = अणु 0x0, पूर्ण;

/*
 * The MT8173 thermal controller has four banks. Each bank can पढ़ो up to
 * four temperature sensors simultaneously. The MT8173 has a total of 5
 * temperature sensors. We use each bank to measure a certain area of the
 * SoC. Since TS2 is located centrally in the SoC it is influenced by multiple
 * areas, hence is used in dअगरferent banks.
 *
 * The thermal core only माला_लो the maximum temperature of all banks, so
 * the bank concept wouldn't be necessary here. However, the SVS (Smart
 * Voltage Scaling) unit makes its decisions based on the same bank
 * data, and this indeed needs the temperatures of the inभागidual banks
 * क्रम making better decisions.
 */
अटल स्थिर काष्ठा mtk_thermal_data mt8173_thermal_data = अणु
	.auxadc_channel = MT8173_TEMP_AUXADC_CHANNEL,
	.num_banks = MT8173_NUM_ZONES,
	.num_sensors = MT8173_NUM_SENSORS,
	.vts_index = mt8173_vts_index,
	.cali_val = MT8173_CALIBRATION,
	.num_controller = MT8173_NUM_CONTROLLER,
	.controller_offset = mt8173_tc_offset,
	.need_चयन_bank = true,
	.bank_data = अणु
		अणु
			.num_sensors = 2,
			.sensors = mt8173_bank_data[0],
		पूर्ण, अणु
			.num_sensors = 2,
			.sensors = mt8173_bank_data[1],
		पूर्ण, अणु
			.num_sensors = 3,
			.sensors = mt8173_bank_data[2],
		पूर्ण, अणु
			.num_sensors = 1,
			.sensors = mt8173_bank_data[3],
		पूर्ण,
	पूर्ण,
	.msr = mt8173_msr,
	.adcpnp = mt8173_adcpnp,
	.sensor_mux_values = mt8173_mux_values,
	.version = MTK_THERMAL_V1,
पूर्ण;

/*
 * The MT2701 thermal controller has one bank, which can पढ़ो up to
 * three temperature sensors simultaneously. The MT2701 has a total of 3
 * temperature sensors.
 *
 * The thermal core only माला_लो the maximum temperature of this one bank,
 * so the bank concept wouldn't be necessary here. However, the SVS (Smart
 * Voltage Scaling) unit makes its decisions based on the same bank
 * data.
 */
अटल स्थिर काष्ठा mtk_thermal_data mt2701_thermal_data = अणु
	.auxadc_channel = MT2701_TEMP_AUXADC_CHANNEL,
	.num_banks = 1,
	.num_sensors = MT2701_NUM_SENSORS,
	.vts_index = mt2701_vts_index,
	.cali_val = MT2701_CALIBRATION,
	.num_controller = MT2701_NUM_CONTROLLER,
	.controller_offset = mt2701_tc_offset,
	.need_चयन_bank = true,
	.bank_data = अणु
		अणु
			.num_sensors = 3,
			.sensors = mt2701_bank_data,
		पूर्ण,
	पूर्ण,
	.msr = mt2701_msr,
	.adcpnp = mt2701_adcpnp,
	.sensor_mux_values = mt2701_mux_values,
	.version = MTK_THERMAL_V1,
पूर्ण;

/*
 * The MT2712 thermal controller has one bank, which can पढ़ो up to
 * four temperature sensors simultaneously. The MT2712 has a total of 4
 * temperature sensors.
 *
 * The thermal core only माला_लो the maximum temperature of this one bank,
 * so the bank concept wouldn't be necessary here. However, the SVS (Smart
 * Voltage Scaling) unit makes its decisions based on the same bank
 * data.
 */
अटल स्थिर काष्ठा mtk_thermal_data mt2712_thermal_data = अणु
	.auxadc_channel = MT2712_TEMP_AUXADC_CHANNEL,
	.num_banks = 1,
	.num_sensors = MT2712_NUM_SENSORS,
	.vts_index = mt2712_vts_index,
	.cali_val = MT2712_CALIBRATION,
	.num_controller = MT2712_NUM_CONTROLLER,
	.controller_offset = mt2712_tc_offset,
	.need_चयन_bank = true,
	.bank_data = अणु
		अणु
			.num_sensors = 4,
			.sensors = mt2712_bank_data,
		पूर्ण,
	पूर्ण,
	.msr = mt2712_msr,
	.adcpnp = mt2712_adcpnp,
	.sensor_mux_values = mt2712_mux_values,
	.version = MTK_THERMAL_V1,
पूर्ण;

/*
 * MT7622 have only one sensing poपूर्णांक which uses AUXADC Channel 11 क्रम raw data
 * access.
 */
अटल स्थिर काष्ठा mtk_thermal_data mt7622_thermal_data = अणु
	.auxadc_channel = MT7622_TEMP_AUXADC_CHANNEL,
	.num_banks = MT7622_NUM_ZONES,
	.num_sensors = MT7622_NUM_SENSORS,
	.vts_index = mt7622_vts_index,
	.cali_val = MT7622_CALIBRATION,
	.num_controller = MT7622_NUM_CONTROLLER,
	.controller_offset = mt7622_tc_offset,
	.need_चयन_bank = true,
	.bank_data = अणु
		अणु
			.num_sensors = 1,
			.sensors = mt7622_bank_data,
		पूर्ण,
	पूर्ण,
	.msr = mt7622_msr,
	.adcpnp = mt7622_adcpnp,
	.sensor_mux_values = mt7622_mux_values,
	.version = MTK_THERMAL_V2,
पूर्ण;

/*
 * The MT8183 thermal controller has one bank क्रम the current SW framework.
 * The MT8183 has a total of 6 temperature sensors.
 * There are two thermal controller to control the six sensor.
 * The first one bind 2 sensor, and the other bind 4 sensors.
 * The thermal core only माला_लो the maximum temperature of all sensor, so
 * the bank concept wouldn't be necessary here. However, the SVS (Smart
 * Voltage Scaling) unit makes its decisions based on the same bank
 * data, and this indeed needs the temperatures of the inभागidual banks
 * क्रम making better decisions.
 */
अटल स्थिर काष्ठा mtk_thermal_data mt8183_thermal_data = अणु
	.auxadc_channel = MT8183_TEMP_AUXADC_CHANNEL,
	.num_banks = MT8183_NUM_ZONES,
	.num_sensors = MT8183_NUM_SENSORS,
	.vts_index = mt8183_vts_index,
	.cali_val = MT8183_CALIBRATION,
	.num_controller = MT8183_NUM_CONTROLLER,
	.controller_offset = mt8183_tc_offset,
	.need_चयन_bank = false,
	.bank_data = अणु
		अणु
			.num_sensors = 6,
			.sensors = mt8183_bank_data,
		पूर्ण,
	पूर्ण,

	.msr = mt8183_msr,
	.adcpnp = mt8183_adcpnp,
	.sensor_mux_values = mt8183_mux_values,
	.version = MTK_THERMAL_V1,
पूर्ण;

/**
 * raw_to_mcelsius - convert a raw ADC value to mcelsius
 * @mt:	The thermal controller
 * @sensno:	sensor number
 * @raw:	raw ADC value
 *
 * This converts the raw ADC value to mcelsius using the SoC specअगरic
 * calibration स्थिरants
 */
अटल पूर्णांक raw_to_mcelsius_v1(काष्ठा mtk_thermal *mt, पूर्णांक sensno, s32 raw)
अणु
	s32 पंचांगp;

	raw &= 0xfff;

	पंचांगp = 203450520 << 3;
	पंचांगp /= mt->conf->cali_val + mt->o_slope;
	पंचांगp /= 10000 + mt->adc_ge;
	पंचांगp *= raw - mt->vts[sensno] - 3350;
	पंचांगp >>= 3;

	वापस mt->degc_cali * 500 - पंचांगp;
पूर्ण

अटल पूर्णांक raw_to_mcelsius_v2(काष्ठा mtk_thermal *mt, पूर्णांक sensno, s32 raw)
अणु
	s32 क्रमmat_1;
	s32 क्रमmat_2;
	s32 g_oe;
	s32 g_gain;
	s32 g_x_roomt;
	s32 पंचांगp;

	अगर (raw == 0)
		वापस 0;

	raw &= 0xfff;
	g_gain = 10000 + (((mt->adc_ge - 512) * 10000) >> 12);
	g_oe = mt->adc_oe - 512;
	क्रमmat_1 = mt->vts[VTS2] + 3105 - g_oe;
	क्रमmat_2 = (mt->degc_cali * 10) >> 1;
	g_x_roomt = (((क्रमmat_1 * 10000) >> 12) * 10000) / g_gain;

	पंचांगp = (((((raw - g_oe) * 10000) >> 12) * 10000) / g_gain) - g_x_roomt;
	पंचांगp = पंचांगp * 10 * 100 / 11;

	अगर (mt->o_slope_sign == 0)
		पंचांगp = पंचांगp / (165 - mt->o_slope);
	अन्यथा
		पंचांगp = पंचांगp / (165 + mt->o_slope);

	वापस (क्रमmat_2 - पंचांगp) * 100;
पूर्ण

/**
 * mtk_thermal_get_bank - get bank
 * @bank:	The bank
 *
 * The bank रेजिस्टरs are banked, we have to select a bank in the
 * PTPCORESEL रेजिस्टर to access it.
 */
अटल व्योम mtk_thermal_get_bank(काष्ठा mtk_thermal_bank *bank)
अणु
	काष्ठा mtk_thermal *mt = bank->mt;
	u32 val;

	अगर (mt->conf->need_चयन_bank) अणु
		mutex_lock(&mt->lock);

		val = पढ़ोl(mt->thermal_base + PTPCORESEL);
		val &= ~0xf;
		val |= bank->id;
		ग_लिखोl(val, mt->thermal_base + PTPCORESEL);
	पूर्ण
पूर्ण

/**
 * mtk_thermal_put_bank - release bank
 * @bank:	The bank
 *
 * release a bank previously taken with mtk_thermal_get_bank,
 */
अटल व्योम mtk_thermal_put_bank(काष्ठा mtk_thermal_bank *bank)
अणु
	काष्ठा mtk_thermal *mt = bank->mt;

	अगर (mt->conf->need_चयन_bank)
		mutex_unlock(&mt->lock);
पूर्ण

/**
 * mtk_thermal_bank_temperature - get the temperature of a bank
 * @bank:	The bank
 *
 * The temperature of a bank is considered the maximum temperature of
 * the sensors associated to the bank.
 */
अटल पूर्णांक mtk_thermal_bank_temperature(काष्ठा mtk_thermal_bank *bank)
अणु
	काष्ठा mtk_thermal *mt = bank->mt;
	स्थिर काष्ठा mtk_thermal_data *conf = mt->conf;
	पूर्णांक i, temp = पूर्णांक_न्यून, max = पूर्णांक_न्यून;
	u32 raw;

	क्रम (i = 0; i < conf->bank_data[bank->id].num_sensors; i++) अणु
		raw = पढ़ोl(mt->thermal_base + conf->msr[i]);

		अगर (mt->conf->version == MTK_THERMAL_V1) अणु
			temp = raw_to_mcelsius_v1(
				mt, conf->bank_data[bank->id].sensors[i], raw);
		पूर्ण अन्यथा अणु
			temp = raw_to_mcelsius_v2(
				mt, conf->bank_data[bank->id].sensors[i], raw);
		पूर्ण

		/*
		 * The first पढ़ो of a sensor often contains very high bogus
		 * temperature value. Filter these out so that the प्रणाली करोes
		 * not immediately shut करोwn.
		 */
		अगर (temp > 200000)
			temp = 0;

		अगर (temp > max)
			max = temp;
	पूर्ण

	वापस max;
पूर्ण

अटल पूर्णांक mtk_पढ़ो_temp(व्योम *data, पूर्णांक *temperature)
अणु
	काष्ठा mtk_thermal *mt = data;
	पूर्णांक i;
	पूर्णांक tempmax = पूर्णांक_न्यून;

	क्रम (i = 0; i < mt->conf->num_banks; i++) अणु
		काष्ठा mtk_thermal_bank *bank = &mt->banks[i];

		mtk_thermal_get_bank(bank);

		tempmax = max(tempmax, mtk_thermal_bank_temperature(bank));

		mtk_thermal_put_bank(bank);
	पूर्ण

	*temperature = tempmax;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops mtk_thermal_ops = अणु
	.get_temp = mtk_पढ़ो_temp,
पूर्ण;

अटल व्योम mtk_thermal_init_bank(काष्ठा mtk_thermal *mt, पूर्णांक num,
				  u32 apmixed_phys_base, u32 auxadc_phys_base,
				  पूर्णांक ctrl_id)
अणु
	काष्ठा mtk_thermal_bank *bank = &mt->banks[num];
	स्थिर काष्ठा mtk_thermal_data *conf = mt->conf;
	पूर्णांक i;

	पूर्णांक offset = mt->conf->controller_offset[ctrl_id];
	व्योम __iomem *controller_base = mt->thermal_base + offset;

	bank->id = num;
	bank->mt = mt;

	mtk_thermal_get_bank(bank);

	/* bus घड़ी 66M counting unit is 12 * 15.15ns * 256 = 46.540us */
	ग_लिखोl(TEMP_MONCTL1_PERIOD_UNIT(12), controller_base + TEMP_MONCTL1);

	/*
	 * filt पूर्णांकerval is 1 * 46.540us = 46.54us,
	 * sen पूर्णांकerval is 429 * 46.540us = 19.96ms
	 */
	ग_लिखोl(TEMP_MONCTL2_FILTER_INTERVAL(1) |
			TEMP_MONCTL2_SENSOR_INTERVAL(429),
			controller_base + TEMP_MONCTL2);

	/* poll is set to 10u */
	ग_लिखोl(TEMP_AHBPOLL_ADC_POLL_INTERVAL(768),
	       controller_base + TEMP_AHBPOLL);

	/* temperature sampling control, 1 sample */
	ग_लिखोl(0x0, controller_base + TEMP_MSRCTL0);

	/* exceed this polling समय, IRQ would be inserted */
	ग_लिखोl(0xffffffff, controller_base + TEMP_AHBTO);

	/* number of पूर्णांकerrupts per event, 1 is enough */
	ग_लिखोl(0x0, controller_base + TEMP_MONIDET0);
	ग_लिखोl(0x0, controller_base + TEMP_MONIDET1);

	/*
	 * The MT8173 thermal controller करोes not have its own ADC. Instead it
	 * uses AHB bus accesses to control the AUXADC. To करो this the thermal
	 * controller has to be programmed with the physical addresses of the
	 * AUXADC रेजिस्टरs and with the various bit positions in the AUXADC.
	 * Also the thermal controller controls a mux in the APMIXEDSYS रेजिस्टर
	 * space.
	 */

	/*
	 * this value will be stored to TEMP_PNPMUXADDR (TEMP_SPARE0)
	 * स्वतःmatically by hw
	 */
	ग_लिखोl(BIT(conf->auxadc_channel), controller_base + TEMP_ADCMUX);

	/* AHB address क्रम auxadc mux selection */
	ग_लिखोl(auxadc_phys_base + AUXADC_CON1_CLR_V,
	       controller_base + TEMP_ADCMUXADDR);

	अगर (mt->conf->version == MTK_THERMAL_V1) अणु
		/* AHB address क्रम pnp sensor mux selection */
		ग_लिखोl(apmixed_phys_base + APMIXED_SYS_TS_CON1,
		       controller_base + TEMP_PNPMUXADDR);
	पूर्ण

	/* AHB value क्रम auxadc enable */
	ग_लिखोl(BIT(conf->auxadc_channel), controller_base + TEMP_ADCEN);

	/* AHB address क्रम auxadc enable (channel 0 immediate mode selected) */
	ग_लिखोl(auxadc_phys_base + AUXADC_CON1_SET_V,
	       controller_base + TEMP_ADCENADDR);

	/* AHB address क्रम auxadc valid bit */
	ग_लिखोl(auxadc_phys_base + AUXADC_DATA(conf->auxadc_channel),
	       controller_base + TEMP_ADCVALIDADDR);

	/* AHB address क्रम auxadc voltage output */
	ग_लिखोl(auxadc_phys_base + AUXADC_DATA(conf->auxadc_channel),
	       controller_base + TEMP_ADCVOLTADDR);

	/* पढ़ो valid & voltage are at the same रेजिस्टर */
	ग_लिखोl(0x0, controller_base + TEMP_RDCTRL);

	/* indicate where the valid bit is */
	ग_लिखोl(TEMP_ADCVALIDMASK_VALID_HIGH | TEMP_ADCVALIDMASK_VALID_POS(12),
	       controller_base + TEMP_ADCVALIDMASK);

	/* no shअगरt */
	ग_लिखोl(0x0, controller_base + TEMP_ADCVOLTAGESHIFT);

	/* enable auxadc mux ग_लिखो transaction */
	ग_लिखोl(TEMP_ADCWRITECTRL_ADC_MUX_WRITE,
		controller_base + TEMP_ADCWRITECTRL);

	क्रम (i = 0; i < conf->bank_data[num].num_sensors; i++)
		ग_लिखोl(conf->sensor_mux_values[conf->bank_data[num].sensors[i]],
		       mt->thermal_base + conf->adcpnp[i]);

	ग_लिखोl((1 << conf->bank_data[num].num_sensors) - 1,
	       controller_base + TEMP_MONCTL0);

	ग_लिखोl(TEMP_ADCWRITECTRL_ADC_PNP_WRITE |
	       TEMP_ADCWRITECTRL_ADC_MUX_WRITE,
	       controller_base + TEMP_ADCWRITECTRL);

	mtk_thermal_put_bank(bank);
पूर्ण

अटल u64 of_get_phys_base(काष्ठा device_node *np)
अणु
	u64 size64;
	स्थिर __be32 *regaddr_p;

	regaddr_p = of_get_address(np, 0, &size64, शून्य);
	अगर (!regaddr_p)
		वापस OF_BAD_ADDR;

	वापस of_translate_address(np, regaddr_p);
पूर्ण

अटल पूर्णांक mtk_thermal_extract_efuse_v1(काष्ठा mtk_thermal *mt, u32 *buf)
अणु
	पूर्णांक i;

	अगर (!(buf[0] & CALIB_BUF0_VALID_V1))
		वापस -EINVAL;

	mt->adc_ge = CALIB_BUF1_ADC_GE_V1(buf[1]);

	क्रम (i = 0; i < mt->conf->num_sensors; i++) अणु
		चयन (mt->conf->vts_index[i]) अणु
		हाल VTS1:
			mt->vts[VTS1] = CALIB_BUF0_VTS_TS1_V1(buf[0]);
			अवरोध;
		हाल VTS2:
			mt->vts[VTS2] = CALIB_BUF0_VTS_TS2_V1(buf[0]);
			अवरोध;
		हाल VTS3:
			mt->vts[VTS3] = CALIB_BUF1_VTS_TS3_V1(buf[1]);
			अवरोध;
		हाल VTS4:
			mt->vts[VTS4] = CALIB_BUF2_VTS_TS4_V1(buf[2]);
			अवरोध;
		हाल VTS5:
			mt->vts[VTS5] = CALIB_BUF2_VTS_TS5_V1(buf[2]);
			अवरोध;
		हाल VTSABB:
			mt->vts[VTSABB] =
				CALIB_BUF2_VTS_TSABB_V1(buf[2]);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	mt->degc_cali = CALIB_BUF0_DEGC_CALI_V1(buf[0]);
	अगर (CALIB_BUF1_ID_V1(buf[1]) &
	    CALIB_BUF0_O_SLOPE_SIGN_V1(buf[0]))
		mt->o_slope = -CALIB_BUF0_O_SLOPE_V1(buf[0]);
	अन्यथा
		mt->o_slope = CALIB_BUF0_O_SLOPE_V1(buf[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_thermal_extract_efuse_v2(काष्ठा mtk_thermal *mt, u32 *buf)
अणु
	अगर (!CALIB_BUF1_VALID_V2(buf[1]))
		वापस -EINVAL;

	mt->adc_oe = CALIB_BUF0_ADC_OE_V2(buf[0]);
	mt->adc_ge = CALIB_BUF0_ADC_GE_V2(buf[0]);
	mt->degc_cali = CALIB_BUF0_DEGC_CALI_V2(buf[0]);
	mt->o_slope = CALIB_BUF0_O_SLOPE_V2(buf[0]);
	mt->vts[VTS1] = CALIB_BUF1_VTS_TS1_V2(buf[1]);
	mt->vts[VTS2] = CALIB_BUF1_VTS_TS2_V2(buf[1]);
	mt->vts[VTSABB] = CALIB_BUF1_VTS_TSABB_V2(buf[1]);
	mt->o_slope_sign = CALIB_BUF1_O_SLOPE_SIGN_V2(buf[1]);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_thermal_get_calibration_data(काष्ठा device *dev,
					    काष्ठा mtk_thermal *mt)
अणु
	काष्ठा nvmem_cell *cell;
	u32 *buf;
	माप_प्रकार len;
	पूर्णांक i, ret = 0;

	/* Start with शेष values */
	mt->adc_ge = 512;
	क्रम (i = 0; i < mt->conf->num_sensors; i++)
		mt->vts[i] = 260;
	mt->degc_cali = 40;
	mt->o_slope = 0;

	cell = nvmem_cell_get(dev, "calibration-data");
	अगर (IS_ERR(cell)) अणु
		अगर (PTR_ERR(cell) == -EPROBE_DEFER)
			वापस PTR_ERR(cell);
		वापस 0;
	पूर्ण

	buf = (u32 *)nvmem_cell_पढ़ो(cell, &len);

	nvmem_cell_put(cell);

	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	अगर (len < 3 * माप(u32)) अणु
		dev_warn(dev, "invalid calibration data\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (mt->conf->version == MTK_THERMAL_V1)
		ret = mtk_thermal_extract_efuse_v1(mt, buf);
	अन्यथा
		ret = mtk_thermal_extract_efuse_v2(mt, buf);

	अगर (ret) अणु
		dev_info(dev, "Device not calibrated, using default calibration values\n");
		ret = 0;
	पूर्ण

out:
	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id mtk_thermal_of_match[] = अणु
	अणु
		.compatible = "mediatek,mt8173-thermal",
		.data = (व्योम *)&mt8173_thermal_data,
	पूर्ण,
	अणु
		.compatible = "mediatek,mt2701-thermal",
		.data = (व्योम *)&mt2701_thermal_data,
	पूर्ण,
	अणु
		.compatible = "mediatek,mt2712-thermal",
		.data = (व्योम *)&mt2712_thermal_data,
	पूर्ण,
	अणु
		.compatible = "mediatek,mt7622-thermal",
		.data = (व्योम *)&mt7622_thermal_data,
	पूर्ण,
	अणु
		.compatible = "mediatek,mt8183-thermal",
		.data = (व्योम *)&mt8183_thermal_data,
	पूर्ण, अणु
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_thermal_of_match);

अटल व्योम mtk_thermal_turn_on_buffer(व्योम __iomem *apmixed_base)
अणु
	पूर्णांक पंचांगp;

	पंचांगp = पढ़ोl(apmixed_base + APMIXED_SYS_TS_CON1);
	पंचांगp &= ~(0x37);
	पंचांगp |= 0x1;
	ग_लिखोl(पंचांगp, apmixed_base + APMIXED_SYS_TS_CON1);
	udelay(200);
पूर्ण

अटल व्योम mtk_thermal_release_periodic_ts(काष्ठा mtk_thermal *mt,
					    व्योम __iomem *auxadc_base)
अणु
	पूर्णांक पंचांगp;

	ग_लिखोl(0x800, auxadc_base + AUXADC_CON1_SET_V);
	ग_लिखोl(0x1, mt->thermal_base + TEMP_MONCTL0);
	पंचांगp = पढ़ोl(mt->thermal_base + TEMP_MSRCTL1);
	ग_लिखोl((पंचांगp & (~0x10e)), mt->thermal_base + TEMP_MSRCTL1);
पूर्ण

अटल पूर्णांक mtk_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret, i, ctrl_id;
	काष्ठा device_node *auxadc, *apmixedsys, *np = pdev->dev.of_node;
	काष्ठा mtk_thermal *mt;
	काष्ठा resource *res;
	u64 auxadc_phys_base, apmixed_phys_base;
	काष्ठा thermal_zone_device *tzdev;
	व्योम __iomem *apmixed_base, *auxadc_base;

	mt = devm_kzalloc(&pdev->dev, माप(*mt), GFP_KERNEL);
	अगर (!mt)
		वापस -ENOMEM;

	mt->conf = of_device_get_match_data(&pdev->dev);

	mt->clk_peri_therm = devm_clk_get(&pdev->dev, "therm");
	अगर (IS_ERR(mt->clk_peri_therm))
		वापस PTR_ERR(mt->clk_peri_therm);

	mt->clk_auxadc = devm_clk_get(&pdev->dev, "auxadc");
	अगर (IS_ERR(mt->clk_auxadc))
		वापस PTR_ERR(mt->clk_auxadc);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mt->thermal_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(mt->thermal_base))
		वापस PTR_ERR(mt->thermal_base);

	ret = mtk_thermal_get_calibration_data(&pdev->dev, mt);
	अगर (ret)
		वापस ret;

	mutex_init(&mt->lock);

	mt->dev = &pdev->dev;

	auxadc = of_parse_phandle(np, "mediatek,auxadc", 0);
	अगर (!auxadc) अणु
		dev_err(&pdev->dev, "missing auxadc node\n");
		वापस -ENODEV;
	पूर्ण

	auxadc_base = of_iomap(auxadc, 0);
	auxadc_phys_base = of_get_phys_base(auxadc);

	of_node_put(auxadc);

	अगर (auxadc_phys_base == OF_BAD_ADDR) अणु
		dev_err(&pdev->dev, "Can't get auxadc phys address\n");
		वापस -EINVAL;
	पूर्ण

	apmixedsys = of_parse_phandle(np, "mediatek,apmixedsys", 0);
	अगर (!apmixedsys) अणु
		dev_err(&pdev->dev, "missing apmixedsys node\n");
		वापस -ENODEV;
	पूर्ण

	apmixed_base = of_iomap(apmixedsys, 0);
	apmixed_phys_base = of_get_phys_base(apmixedsys);

	of_node_put(apmixedsys);

	अगर (apmixed_phys_base == OF_BAD_ADDR) अणु
		dev_err(&pdev->dev, "Can't get auxadc phys address\n");
		वापस -EINVAL;
	पूर्ण

	ret = device_reset_optional(&pdev->dev);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(mt->clk_auxadc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't enable auxadc clk: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(mt->clk_peri_therm);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't enable peri clk: %d\n", ret);
		जाओ err_disable_clk_auxadc;
	पूर्ण

	अगर (mt->conf->version == MTK_THERMAL_V2) अणु
		mtk_thermal_turn_on_buffer(apmixed_base);
		mtk_thermal_release_periodic_ts(mt, auxadc_base);
	पूर्ण

	क्रम (ctrl_id = 0; ctrl_id < mt->conf->num_controller ; ctrl_id++)
		क्रम (i = 0; i < mt->conf->num_banks; i++)
			mtk_thermal_init_bank(mt, i, apmixed_phys_base,
					      auxadc_phys_base, ctrl_id);

	platक्रमm_set_drvdata(pdev, mt);

	tzdev = devm_thermal_zone_of_sensor_रेजिस्टर(&pdev->dev, 0, mt,
						     &mtk_thermal_ops);
	अगर (IS_ERR(tzdev)) अणु
		ret = PTR_ERR(tzdev);
		जाओ err_disable_clk_peri_therm;
	पूर्ण

	वापस 0;

err_disable_clk_peri_therm:
	clk_disable_unprepare(mt->clk_peri_therm);
err_disable_clk_auxadc:
	clk_disable_unprepare(mt->clk_auxadc);

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_thermal_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_thermal *mt = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(mt->clk_peri_therm);
	clk_disable_unprepare(mt->clk_auxadc);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mtk_thermal_driver = अणु
	.probe = mtk_thermal_probe,
	.हटाओ = mtk_thermal_हटाओ,
	.driver = अणु
		.name = "mtk-thermal",
		.of_match_table = mtk_thermal_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mtk_thermal_driver);

MODULE_AUTHOR("Michael Kao <michael.kao@mediatek.com>");
MODULE_AUTHOR("Louis Yu <louis.yu@mediatek.com>");
MODULE_AUTHOR("Dawei Chien <dawei.chien@mediatek.com>");
MODULE_AUTHOR("Sascha Hauer <s.hauer@pengutronix.de>");
MODULE_AUTHOR("Hanyi Wu <hanyi.wu@mediatek.com>");
MODULE_DESCRIPTION("Mediatek thermal driver");
MODULE_LICENSE("GPL v2");
