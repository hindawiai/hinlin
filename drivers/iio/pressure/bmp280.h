<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/regmap.h>

/* BMP280 specअगरic रेजिस्टरs */
#घोषणा BMP280_REG_HUMIDITY_LSB		0xFE
#घोषणा BMP280_REG_HUMIDITY_MSB		0xFD
#घोषणा BMP280_REG_TEMP_XLSB		0xFC
#घोषणा BMP280_REG_TEMP_LSB		0xFB
#घोषणा BMP280_REG_TEMP_MSB		0xFA
#घोषणा BMP280_REG_PRESS_XLSB		0xF9
#घोषणा BMP280_REG_PRESS_LSB		0xF8
#घोषणा BMP280_REG_PRESS_MSB		0xF7

#घोषणा BMP280_REG_CONFIG		0xF5
#घोषणा BMP280_REG_CTRL_MEAS		0xF4
#घोषणा BMP280_REG_STATUS		0xF3
#घोषणा BMP280_REG_CTRL_HUMIDITY	0xF2

/* Due to non linear mapping, and data sizes we can't करो a bulk पढ़ो */
#घोषणा BMP280_REG_COMP_H1		0xA1
#घोषणा BMP280_REG_COMP_H2		0xE1
#घोषणा BMP280_REG_COMP_H3		0xE3
#घोषणा BMP280_REG_COMP_H4		0xE4
#घोषणा BMP280_REG_COMP_H5		0xE5
#घोषणा BMP280_REG_COMP_H6		0xE7

#घोषणा BMP280_REG_COMP_TEMP_START	0x88
#घोषणा BMP280_COMP_TEMP_REG_COUNT	6

#घोषणा BMP280_REG_COMP_PRESS_START	0x8E
#घोषणा BMP280_COMP_PRESS_REG_COUNT	18

#घोषणा BMP280_FILTER_MASK		(BIT(4) | BIT(3) | BIT(2))
#घोषणा BMP280_FILTER_OFF		0
#घोषणा BMP280_FILTER_2X		BIT(2)
#घोषणा BMP280_FILTER_4X		BIT(3)
#घोषणा BMP280_FILTER_8X		(BIT(3) | BIT(2))
#घोषणा BMP280_FILTER_16X		BIT(4)

#घोषणा BMP280_OSRS_HUMIDITY_MASK	(BIT(2) | BIT(1) | BIT(0))
#घोषणा BMP280_OSRS_HUMIDITIY_X(osrs_h)	((osrs_h) << 0)
#घोषणा BMP280_OSRS_HUMIDITY_SKIP	0
#घोषणा BMP280_OSRS_HUMIDITY_1X		BMP280_OSRS_HUMIDITIY_X(1)
#घोषणा BMP280_OSRS_HUMIDITY_2X		BMP280_OSRS_HUMIDITIY_X(2)
#घोषणा BMP280_OSRS_HUMIDITY_4X		BMP280_OSRS_HUMIDITIY_X(3)
#घोषणा BMP280_OSRS_HUMIDITY_8X		BMP280_OSRS_HUMIDITIY_X(4)
#घोषणा BMP280_OSRS_HUMIDITY_16X	BMP280_OSRS_HUMIDITIY_X(5)

#घोषणा BMP280_OSRS_TEMP_MASK		(BIT(7) | BIT(6) | BIT(5))
#घोषणा BMP280_OSRS_TEMP_SKIP		0
#घोषणा BMP280_OSRS_TEMP_X(osrs_t)	((osrs_t) << 5)
#घोषणा BMP280_OSRS_TEMP_1X		BMP280_OSRS_TEMP_X(1)
#घोषणा BMP280_OSRS_TEMP_2X		BMP280_OSRS_TEMP_X(2)
#घोषणा BMP280_OSRS_TEMP_4X		BMP280_OSRS_TEMP_X(3)
#घोषणा BMP280_OSRS_TEMP_8X		BMP280_OSRS_TEMP_X(4)
#घोषणा BMP280_OSRS_TEMP_16X		BMP280_OSRS_TEMP_X(5)

#घोषणा BMP280_OSRS_PRESS_MASK		(BIT(4) | BIT(3) | BIT(2))
#घोषणा BMP280_OSRS_PRESS_SKIP		0
#घोषणा BMP280_OSRS_PRESS_X(osrs_p)	((osrs_p) << 2)
#घोषणा BMP280_OSRS_PRESS_1X		BMP280_OSRS_PRESS_X(1)
#घोषणा BMP280_OSRS_PRESS_2X		BMP280_OSRS_PRESS_X(2)
#घोषणा BMP280_OSRS_PRESS_4X		BMP280_OSRS_PRESS_X(3)
#घोषणा BMP280_OSRS_PRESS_8X		BMP280_OSRS_PRESS_X(4)
#घोषणा BMP280_OSRS_PRESS_16X		BMP280_OSRS_PRESS_X(5)

#घोषणा BMP280_MODE_MASK		(BIT(1) | BIT(0))
#घोषणा BMP280_MODE_SLEEP		0
#घोषणा BMP280_MODE_FORCED		BIT(0)
#घोषणा BMP280_MODE_NORMAL		(BIT(1) | BIT(0))

/* BMP180 specअगरic रेजिस्टरs */
#घोषणा BMP180_REG_OUT_XLSB		0xF8
#घोषणा BMP180_REG_OUT_LSB		0xF7
#घोषणा BMP180_REG_OUT_MSB		0xF6

#घोषणा BMP180_REG_CALIB_START		0xAA
#घोषणा BMP180_REG_CALIB_COUNT		22

#घोषणा BMP180_MEAS_SCO			BIT(5)
#घोषणा BMP180_MEAS_TEMP		(0x0E | BMP180_MEAS_SCO)
#घोषणा BMP180_MEAS_PRESS_X(oss)	((oss) << 6 | 0x14 | BMP180_MEAS_SCO)
#घोषणा BMP180_MEAS_PRESS_1X		BMP180_MEAS_PRESS_X(0)
#घोषणा BMP180_MEAS_PRESS_2X		BMP180_MEAS_PRESS_X(1)
#घोषणा BMP180_MEAS_PRESS_4X		BMP180_MEAS_PRESS_X(2)
#घोषणा BMP180_MEAS_PRESS_8X		BMP180_MEAS_PRESS_X(3)

/* BMP180 and BMP280 common रेजिस्टरs */
#घोषणा BMP280_REG_CTRL_MEAS		0xF4
#घोषणा BMP280_REG_RESET		0xE0
#घोषणा BMP280_REG_ID			0xD0

#घोषणा BMP180_CHIP_ID			0x55
#घोषणा BMP280_CHIP_ID			0x58
#घोषणा BME280_CHIP_ID			0x60
#घोषणा BMP280_SOFT_RESET_VAL		0xB6

/* BMP280 रेजिस्टर skipped special values */
#घोषणा BMP280_TEMP_SKIPPED		0x80000
#घोषणा BMP280_PRESS_SKIPPED		0x80000
#घोषणा BMP280_HUMIDITY_SKIPPED		0x8000

/* Regmap configurations */
बाह्य स्थिर काष्ठा regmap_config bmp180_regmap_config;
बाह्य स्थिर काष्ठा regmap_config bmp280_regmap_config;

/* Probe called from dअगरferent transports */
पूर्णांक bmp280_common_probe(काष्ठा device *dev,
			काष्ठा regmap *regmap,
			अचिन्हित पूर्णांक chip,
			स्थिर अक्षर *name,
			पूर्णांक irq);

/* PM ops */
बाह्य स्थिर काष्ठा dev_pm_ops bmp280_dev_pm_ops;
