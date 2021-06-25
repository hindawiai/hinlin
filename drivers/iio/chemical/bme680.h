<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BME680_H_
#घोषणा BME680_H_

#घोषणा BME680_REG_CHIP_ID			0xD0
#घोषणा   BME680_CHIP_ID_VAL			0x61
#घोषणा BME680_REG_SOFT_RESET			0xE0
#घोषणा   BME680_CMD_SOFTRESET			0xB6
#घोषणा BME680_REG_STATUS			0x73
#घोषणा   BME680_SPI_MEM_PAGE_BIT		BIT(4)
#घोषणा     BME680_SPI_MEM_PAGE_1_VAL		1

#घोषणा BME680_REG_TEMP_MSB			0x22
#घोषणा BME680_REG_PRESS_MSB			0x1F
#घोषणा BM6880_REG_HUMIDITY_MSB			0x25
#घोषणा BME680_REG_GAS_MSB			0x2A
#घोषणा BME680_REG_GAS_R_LSB			0x2B
#घोषणा   BME680_GAS_STAB_BIT			BIT(4)
#घोषणा   BME680_GAS_RANGE_MASK			GENMASK(3, 0)

#घोषणा BME680_REG_CTRL_HUMIDITY		0x72
#घोषणा   BME680_OSRS_HUMIDITY_MASK		GENMASK(2, 0)

#घोषणा BME680_REG_CTRL_MEAS			0x74
#घोषणा   BME680_OSRS_TEMP_MASK			GENMASK(7, 5)
#घोषणा   BME680_OSRS_PRESS_MASK		GENMASK(4, 2)
#घोषणा   BME680_MODE_MASK			GENMASK(1, 0)
#घोषणा     BME680_MODE_FORCED			1
#घोषणा     BME680_MODE_SLEEP			0

#घोषणा BME680_REG_CONFIG			0x75
#घोषणा   BME680_FILTER_MASK			GENMASK(4, 2)
#घोषणा     BME680_FILTER_COEFF_VAL		BIT(1)

/* TEMP/PRESS/HUMID पढ़ोing skipped */
#घोषणा BME680_MEAS_SKIPPED			0x8000

#घोषणा BME680_MAX_OVERFLOW_VAL			0x40000000
#घोषणा BME680_HUM_REG_SHIFT_VAL		4
#घोषणा BME680_BIT_H1_DATA_MASK			GENMASK(3, 0)

#घोषणा BME680_REG_RES_HEAT_RANGE		0x02
#घोषणा   BME680_RHRANGE_MASK			GENMASK(5, 4)
#घोषणा BME680_REG_RES_HEAT_VAL			0x00
#घोषणा BME680_REG_RANGE_SW_ERR			0x04
#घोषणा   BME680_RSERROR_MASK			GENMASK(7, 4)
#घोषणा BME680_REG_RES_HEAT_0			0x5A
#घोषणा BME680_REG_GAS_WAIT_0			0x64
#घोषणा BME680_ADC_GAS_RES_SHIFT		6
#घोषणा BME680_AMB_TEMP				25

#घोषणा BME680_REG_CTRL_GAS_1			0x71
#घोषणा   BME680_RUN_GAS_MASK			BIT(4)
#घोषणा   BME680_NB_CONV_MASK			GENMASK(3, 0)

#घोषणा BME680_REG_MEAS_STAT_0			0x1D
#घोषणा   BME680_GAS_MEAS_BIT			BIT(6)

/* Calibration Parameters */
#घोषणा BME680_T2_LSB_REG	0x8A
#घोषणा BME680_T3_REG		0x8C
#घोषणा BME680_P1_LSB_REG	0x8E
#घोषणा BME680_P2_LSB_REG	0x90
#घोषणा BME680_P3_REG		0x92
#घोषणा BME680_P4_LSB_REG	0x94
#घोषणा BME680_P5_LSB_REG	0x96
#घोषणा BME680_P7_REG		0x98
#घोषणा BME680_P6_REG		0x99
#घोषणा BME680_P8_LSB_REG	0x9C
#घोषणा BME680_P9_LSB_REG	0x9E
#घोषणा BME680_P10_REG		0xA0
#घोषणा BME680_H2_LSB_REG	0xE2
#घोषणा BME680_H2_MSB_REG	0xE1
#घोषणा BME680_H1_MSB_REG	0xE3
#घोषणा BME680_H1_LSB_REG	0xE2
#घोषणा BME680_H3_REG		0xE4
#घोषणा BME680_H4_REG		0xE5
#घोषणा BME680_H5_REG		0xE6
#घोषणा BME680_H6_REG		0xE7
#घोषणा BME680_H7_REG		0xE8
#घोषणा BME680_T1_LSB_REG	0xE9
#घोषणा BME680_GH2_LSB_REG	0xEB
#घोषणा BME680_GH1_REG		0xED
#घोषणा BME680_GH3_REG		0xEE

बाह्य स्थिर काष्ठा regmap_config bme680_regmap_config;

पूर्णांक bme680_core_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
		      स्थिर अक्षर *name);

#पूर्ण_अगर  /* BME680_H_ */
