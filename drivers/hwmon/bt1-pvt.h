<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2020 BAIKAL ELECTRONICS, JSC
 *
 * Baikal-T1 Process, Voltage, Temperature sensor driver
 */
#अगर_अघोषित __HWMON_BT1_PVT_H__
#घोषणा __HWMON_BT1_PVT_H__

#समावेश <linux/completion.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/mutex.h>
#समावेश <linux/seqlock.h>

/* Baikal-T1 PVT रेजिस्टरs and their bitfields */
#घोषणा PVT_CTRL			0x00
#घोषणा PVT_CTRL_EN			BIT(0)
#घोषणा PVT_CTRL_MODE_FLD		1
#घोषणा PVT_CTRL_MODE_MASK		GENMASK(3, PVT_CTRL_MODE_FLD)
#घोषणा PVT_CTRL_MODE_TEMP		0x0
#घोषणा PVT_CTRL_MODE_VOLT		0x1
#घोषणा PVT_CTRL_MODE_LVT		0x2
#घोषणा PVT_CTRL_MODE_HVT		0x4
#घोषणा PVT_CTRL_MODE_SVT		0x6
#घोषणा PVT_CTRL_TRIM_FLD		4
#घोषणा PVT_CTRL_TRIM_MASK		GENMASK(8, PVT_CTRL_TRIM_FLD)
#घोषणा PVT_DATA			0x04
#घोषणा PVT_DATA_VALID			BIT(10)
#घोषणा PVT_DATA_DATA_FLD		0
#घोषणा PVT_DATA_DATA_MASK		GENMASK(9, PVT_DATA_DATA_FLD)
#घोषणा PVT_TTHRES			0x08
#घोषणा PVT_VTHRES			0x0C
#घोषणा PVT_LTHRES			0x10
#घोषणा PVT_HTHRES			0x14
#घोषणा PVT_STHRES			0x18
#घोषणा PVT_THRES_LO_FLD		0
#घोषणा PVT_THRES_LO_MASK		GENMASK(9, PVT_THRES_LO_FLD)
#घोषणा PVT_THRES_HI_FLD		10
#घोषणा PVT_THRES_HI_MASK		GENMASK(19, PVT_THRES_HI_FLD)
#घोषणा PVT_TTIMEOUT			0x1C
#घोषणा PVT_INTR_STAT			0x20
#घोषणा PVT_INTR_MASK			0x24
#घोषणा PVT_RAW_INTR_STAT		0x28
#घोषणा PVT_INTR_DVALID			BIT(0)
#घोषणा PVT_INTR_TTHRES_LO		BIT(1)
#घोषणा PVT_INTR_TTHRES_HI		BIT(2)
#घोषणा PVT_INTR_VTHRES_LO		BIT(3)
#घोषणा PVT_INTR_VTHRES_HI		BIT(4)
#घोषणा PVT_INTR_LTHRES_LO		BIT(5)
#घोषणा PVT_INTR_LTHRES_HI		BIT(6)
#घोषणा PVT_INTR_HTHRES_LO		BIT(7)
#घोषणा PVT_INTR_HTHRES_HI		BIT(8)
#घोषणा PVT_INTR_STHRES_LO		BIT(9)
#घोषणा PVT_INTR_STHRES_HI		BIT(10)
#घोषणा PVT_INTR_ALL			GENMASK(10, 0)
#घोषणा PVT_CLR_INTR			0x2C

/*
 * PVT sensors-related limits and शेष values
 * @PVT_TEMP_MIN: Minimal temperature in millidegrees of Celsius.
 * @PVT_TEMP_MAX: Maximal temperature in millidegrees of Celsius.
 * @PVT_TEMP_CHS: Number of temperature hwmon channels.
 * @PVT_VOLT_MIN: Minimal voltage in mV.
 * @PVT_VOLT_MAX: Maximal voltage in mV.
 * @PVT_VOLT_CHS: Number of voltage hwmon channels.
 * @PVT_DATA_MIN: Minimal PVT raw data value.
 * @PVT_DATA_MAX: Maximal PVT raw data value.
 * @PVT_TRIM_MIN: Minimal temperature sensor trim value.
 * @PVT_TRIM_MAX: Maximal temperature sensor trim value.
 * @PVT_TRIM_DEF: Default temperature sensor trim value (set a proper value
 *		  when one is determined क्रम Baikal-T1 SoC).
 * @PVT_TRIM_TEMP: Maximum temperature encoded by the trim factor.
 * @PVT_TRIM_STEP: Temperature stride corresponding to the trim value.
 * @PVT_TOUT_MIN: Minimal समयout between samples in nanoseconds.
 * @PVT_TOUT_DEF: Default data measurements समयout. In हाल अगर alarms are
 *		  activated the PVT IRQ is enabled to be उठाओd after each
 *		  conversion in order to have the thresholds checked and the
 *		  converted value cached. Too frequent conversions may cause
 *		  the प्रणाली CPU overload. Lets set the 50ms delay between
 *		  them by शेष to prevent this.
 */
#घोषणा PVT_TEMP_MIN		-48380L
#घोषणा PVT_TEMP_MAX		147438L
#घोषणा PVT_TEMP_CHS		1
#घोषणा PVT_VOLT_MIN		620L
#घोषणा PVT_VOLT_MAX		1168L
#घोषणा PVT_VOLT_CHS		4
#घोषणा PVT_DATA_MIN		0
#घोषणा PVT_DATA_MAX		(PVT_DATA_DATA_MASK >> PVT_DATA_DATA_FLD)
#घोषणा PVT_TRIM_MIN		0
#घोषणा PVT_TRIM_MAX		(PVT_CTRL_TRIM_MASK >> PVT_CTRL_TRIM_FLD)
#घोषणा PVT_TRIM_TEMP		7130
#घोषणा PVT_TRIM_STEP		(PVT_TRIM_TEMP / PVT_TRIM_MAX)
#घोषणा PVT_TRIM_DEF		0
#घोषणा PVT_TOUT_MIN		(NSEC_PER_SEC / 3000)
#अगर defined(CONFIG_SENSORS_BT1_PVT_ALARMS)
# define PVT_TOUT_DEF		60000
#अन्यथा
# define PVT_TOUT_DEF		0
#पूर्ण_अगर

/*
 * क्रमागत pvt_sensor_type - Baikal-T1 PVT sensor types (correspond to each PVT
 *			  sampling mode)
 * @PVT_SENSOR*: helpers to traverse the sensors in loops.
 * @PVT_TEMP: PVT Temperature sensor.
 * @PVT_VOLT: PVT Voltage sensor.
 * @PVT_LVT: PVT Low-Voltage threshold sensor.
 * @PVT_HVT: PVT High-Voltage threshold sensor.
 * @PVT_SVT: PVT Standard-Voltage threshold sensor.
 */
क्रमागत pvt_sensor_type अणु
	PVT_SENSOR_FIRST,
	PVT_TEMP = PVT_SENSOR_FIRST,
	PVT_VOLT,
	PVT_LVT,
	PVT_HVT,
	PVT_SVT,
	PVT_SENSOR_LAST = PVT_SVT,
	PVT_SENSORS_NUM
पूर्ण;

/*
 * क्रमागत pvt_घड़ी_प्रकारype - Baikal-T1 PVT घड़ीs.
 * @PVT_CLOCK_APB: APB घड़ी.
 * @PVT_CLOCK_REF: PVT reference घड़ी.
 */
क्रमागत pvt_घड़ी_प्रकारype अणु
	PVT_CLOCK_APB,
	PVT_CLOCK_REF,
	PVT_CLOCK_NUM
पूर्ण;

/*
 * काष्ठा pvt_sensor_info - Baikal-T1 PVT sensor inक्रमmational काष्ठाure
 * @channel: Sensor channel ID.
 * @label: hwmon sensor label.
 * @mode: PVT mode corresponding to the channel.
 * @thres_base: upper and lower threshold values of the sensor.
 * @thres_sts_lo: low threshold status bitfield.
 * @thres_sts_hi: high threshold status bitfield.
 * @type: Sensor type.
 * @attr_min_alarm: Min alarm attribute ID.
 * @attr_min_alarm: Max alarm attribute ID.
 */
काष्ठा pvt_sensor_info अणु
	पूर्णांक channel;
	स्थिर अक्षर *label;
	u32 mode;
	अचिन्हित दीर्घ thres_base;
	u32 thres_sts_lo;
	u32 thres_sts_hi;
	क्रमागत hwmon_sensor_types type;
	u32 attr_min_alarm;
	u32 attr_max_alarm;
पूर्ण;

#घोषणा PVT_SENSOR_INFO(_ch, _label, _type, _mode, _thres)	\
	अणु							\
		.channel = _ch,					\
		.label = _label,				\
		.mode = PVT_CTRL_MODE_ ##_mode,			\
		.thres_base = PVT_ ##_thres,			\
		.thres_sts_lo = PVT_INTR_ ##_thres## _LO,	\
		.thres_sts_hi = PVT_INTR_ ##_thres## _HI,	\
		.type = _type,					\
		.attr_min_alarm = _type## _min,			\
		.attr_max_alarm = _type## _max,			\
	पूर्ण

/*
 * काष्ठा pvt_cache - PVT sensors data cache
 * @data: data cache in raw क्रमmat.
 * @thres_sts_lo: low threshold status saved on the previous data conversion.
 * @thres_sts_hi: high threshold status saved on the previous data conversion.
 * @data_seqlock: cached data seq-lock.
 * @conversion: data conversion completion.
 */
काष्ठा pvt_cache अणु
	u32 data;
#अगर defined(CONFIG_SENSORS_BT1_PVT_ALARMS)
	seqlock_t data_seqlock;
	u32 thres_sts_lo;
	u32 thres_sts_hi;
#अन्यथा
	काष्ठा completion conversion;
#पूर्ण_अगर
पूर्ण;

/*
 * काष्ठा pvt_hwmon - Baikal-T1 PVT निजी data
 * @dev: device काष्ठाure of the PVT platक्रमm device.
 * @hwmon: hwmon device काष्ठाure.
 * @regs: poपूर्णांकer to the Baikal-T1 PVT रेजिस्टरs region.
 * @irq: PVT events IRQ number.
 * @clks: Array of the PVT घड़ीs descriptor (APB/ref घड़ीs).
 * @ref_clk: Poपूर्णांकer to the reference घड़ीs descriptor.
 * @अगरace_mtx: Generic पूर्णांकerface mutex (used to lock the alarm रेजिस्टरs
 *	       when the alarms enabled, or the data conversion पूर्णांकerface
 *	       अगर alarms are disabled).
 * @sensor: current PVT sensor the data conversion is being perक्रमmed क्रम.
 * @cache: data cache descriptor.
 * @समयout: conversion समयout cache.
 */
काष्ठा pvt_hwmon अणु
	काष्ठा device *dev;
	काष्ठा device *hwmon;

	व्योम __iomem *regs;
	पूर्णांक irq;

	काष्ठा clk_bulk_data clks[PVT_CLOCK_NUM];

	काष्ठा mutex अगरace_mtx;
	क्रमागत pvt_sensor_type sensor;
	काष्ठा pvt_cache cache[PVT_SENSORS_NUM];
	kसमय_प्रकार समयout;
पूर्ण;

/*
 * काष्ठा pvt_poly_term - a term descriptor of the PVT data translation
 *			  polynomial
 * @deg: degree of the term.
 * @coef: multiplication factor of the term.
 * @भागider: distributed भागider per each degree.
 * @भागider_leftover: भागider leftover, which couldn't be redistributed.
 */
काष्ठा pvt_poly_term अणु
	अचिन्हित पूर्णांक deg;
	दीर्घ coef;
	दीर्घ भागider;
	दीर्घ भागider_leftover;
पूर्ण;

/*
 * काष्ठा pvt_poly - PVT data translation polynomial descriptor
 * @total_भागider: total data भागider.
 * @terms: polynomial terms up to a मुक्त one.
 */
काष्ठा pvt_poly अणु
	दीर्घ total_भागider;
	काष्ठा pvt_poly_term terms[];
पूर्ण;

#पूर्ण_अगर /* __HWMON_BT1_PVT_H__ */
