<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the Yamaha YAS magnetic sensors, often used in Samsung
 * mobile phones. While all are not yet handled because of lacking
 * hardware, expand this driver to handle the dअगरferent variants:
 *
 * YAS530 MS-3E (2011 Samsung Galaxy S Advance)
 * YAS532 MS-3R (2011 Samsung Galaxy S4)
 * YAS533 MS-3F (Vivo 1633, 1707, V3, Y21L)
 * (YAS534 is a magnetic चयन, not handled)
 * YAS535 MS-6C
 * YAS536 MS-3W
 * YAS537 MS-3T (2015 Samsung Galaxy S6, Note 5, Xiaomi)
 * YAS539 MS-3S (2018 Samsung Galaxy A7 SM-A750FN)
 *
 * Code functions found in the MPU3050 YAS530 and YAS532 drivers
 * named "inv_compass" in the Tegra Android kernel tree.
 * Copyright (C) 2012 InvenSense Corporation
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/अक्रमom.h>

#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

#समावेश <यंत्र/unaligned.h>

/* This रेजिस्टर map covers YAS530 and YAS532 but dअगरfers in YAS 537 and YAS539 */
#घोषणा YAS5XX_DEVICE_ID		0x80
#घोषणा YAS5XX_ACTUATE_INIT_COIL	0x81
#घोषणा YAS5XX_MEASURE			0x82
#घोषणा YAS5XX_CONFIG			0x83
#घोषणा YAS5XX_MEASURE_INTERVAL		0x84
#घोषणा YAS5XX_OFFSET_X			0x85 /* [-31 .. 31] */
#घोषणा YAS5XX_OFFSET_Y1		0x86 /* [-31 .. 31] */
#घोषणा YAS5XX_OFFSET_Y2		0x87 /* [-31 .. 31] */
#घोषणा YAS5XX_TEST1			0x88
#घोषणा YAS5XX_TEST2			0x89
#घोषणा YAS5XX_CAL			0x90
#घोषणा YAS5XX_MEASURE_DATA		0xB0

/* Bits in the YAS5xx config रेजिस्टर */
#घोषणा YAS5XX_CONFIG_INTON		BIT(0) /* Interrupt on? */
#घोषणा YAS5XX_CONFIG_INTHACT		BIT(1) /* Interrupt active high? */
#घोषणा YAS5XX_CONFIG_CCK_MASK		GENMASK(4, 2)
#घोषणा YAS5XX_CONFIG_CCK_SHIFT		2

/* Bits in the measure command रेजिस्टर */
#घोषणा YAS5XX_MEASURE_START		BIT(0)
#घोषणा YAS5XX_MEASURE_LDTC		BIT(1)
#घोषणा YAS5XX_MEASURE_FORS		BIT(2)
#घोषणा YAS5XX_MEASURE_DLYMES		BIT(4)

/* Bits in the measure data रेजिस्टर */
#घोषणा YAS5XX_MEASURE_DATA_BUSY	BIT(7)

#घोषणा YAS530_DEVICE_ID		0x01 /* YAS530 (MS-3E) */
#घोषणा YAS530_VERSION_A		0 /* YAS530 (MS-3E A) */
#घोषणा YAS530_VERSION_B		1 /* YAS530B (MS-3E B) */
#घोषणा YAS530_VERSION_A_COEF		380
#घोषणा YAS530_VERSION_B_COEF		550
#घोषणा YAS530_DATA_BITS		12
#घोषणा YAS530_DATA_CENTER		BIT(YAS530_DATA_BITS - 1)
#घोषणा YAS530_DATA_OVERFLOW		(BIT(YAS530_DATA_BITS) - 1)

#घोषणा YAS532_DEVICE_ID		0x02 /* YAS532/YAS533 (MS-3R/F) */
#घोषणा YAS532_VERSION_AB		0 /* YAS532/533 AB (MS-3R/F AB) */
#घोषणा YAS532_VERSION_AC		1 /* YAS532/533 AC (MS-3R/F AC) */
#घोषणा YAS532_VERSION_AB_COEF		1800
#घोषणा YAS532_VERSION_AC_COEF_X	850
#घोषणा YAS532_VERSION_AC_COEF_Y1	750
#घोषणा YAS532_VERSION_AC_COEF_Y2	750
#घोषणा YAS532_DATA_BITS		13
#घोषणा YAS532_DATA_CENTER		BIT(YAS532_DATA_BITS - 1)
#घोषणा YAS532_DATA_OVERFLOW		(BIT(YAS532_DATA_BITS) - 1)
#घोषणा YAS532_20DEGREES		390 /* Looks like Kelvin */

/* These variant IDs are known from code dumps */
#घोषणा YAS537_DEVICE_ID		0x07 /* YAS537 (MS-3T) */
#घोषणा YAS539_DEVICE_ID		0x08 /* YAS539 (MS-3S) */

/* Turn off device regulators etc after 5 seconds of inactivity */
#घोषणा YAS5XX_AUTOSUSPEND_DELAY_MS	5000

काष्ठा yas5xx_calibration अणु
	/* Linearization calibration x, y1, y2 */
	s32 r[3];
	u32 f[3];
	/* Temperature compensation calibration */
	s32 Cx, Cy1, Cy2;
	/* Misc calibration coefficients */
	s32 a2, a3, a4, a5, a6, a7, a8, a9, k;
	/* घड़ी भागider */
	u8 dck;
पूर्ण;

/**
 * काष्ठा yas5xx - state container क्रम the YAS5xx driver
 * @dev: parent device poपूर्णांकer
 * @devid: device ID number
 * @version: device version
 * @name: device name
 * @calibration: calibration settings from the OTP storage
 * @hard_offsets: offsets क्रम each axis measured with initcoil actuated
 * @orientation: mounting matrix, flipped axis etc
 * @map: regmap to access the YAX5xx रेजिस्टरs over I2C
 * @regs: the vdd and vddio घातer regulators
 * @reset: optional GPIO line used क्रम handling RESET
 * @lock: locks the magnetometer क्रम exclusive use during a measurement (which
 * involves several रेजिस्टर transactions so the regmap lock is not enough)
 * so that measurements get serialized in a first-come-first serve manner
 * @scan: naturally aligned measurements
 */
काष्ठा yas5xx अणु
	काष्ठा device *dev;
	अचिन्हित पूर्णांक devid;
	अचिन्हित पूर्णांक version;
	अक्षर name[16];
	काष्ठा yas5xx_calibration calibration;
	u8 hard_offsets[3];
	काष्ठा iio_mount_matrix orientation;
	काष्ठा regmap *map;
	काष्ठा regulator_bulk_data regs[2];
	काष्ठा gpio_desc *reset;
	काष्ठा mutex lock;
	/*
	 * The scanout is 4 x 32 bits in CPU endianness.
	 * Ensure बारtamp is naturally aligned
	 */
	काष्ठा अणु
		s32 channels[4];
		s64 ts __aligned(8);
	पूर्ण scan;
पूर्ण;

/* On YAS530 the x, y1 and y2 values are 12 bits */
अटल u16 yas530_extract_axis(u8 *data)
अणु
	u16 val;

	/*
	 * These are the bits used in a 16bit word:
	 * 15 14 13 12 11 10 9  8  7  6  5  4  3  2  1  0
	 *    x  x  x  x  x  x  x  x  x  x  x  x
	 */
	val = get_unaligned_be16(&data[0]);
	val = FIELD_GET(GENMASK(14, 3), val);
	वापस val;
पूर्ण

/* On YAS532 the x, y1 and y2 values are 13 bits */
अटल u16 yas532_extract_axis(u8 *data)
अणु
	u16 val;

	/*
	 * These are the bits used in a 16bit word:
	 * 15 14 13 12 11 10 9  8  7  6  5  4  3  2  1  0
	 *    x  x  x  x  x  x  x  x  x  x  x  x  x
	 */
	val = get_unaligned_be16(&data[0]);
	val = FIELD_GET(GENMASK(14, 2), val);
	वापस val;
पूर्ण

/**
 * yas5xx_measure() - Make a measure from the hardware
 * @yas5xx: The device state
 * @t: the raw temperature measurement
 * @x: the raw x axis measurement
 * @y1: the y1 axis measurement
 * @y2: the y2 axis measurement
 * @वापस: 0 on success or error code
 */
अटल पूर्णांक yas5xx_measure(काष्ठा yas5xx *yas5xx, u16 *t, u16 *x, u16 *y1, u16 *y2)
अणु
	अचिन्हित पूर्णांक busy;
	u8 data[8];
	पूर्णांक ret;
	u16 val;

	mutex_lock(&yas5xx->lock);
	ret = regmap_ग_लिखो(yas5xx->map, YAS5XX_MEASURE, YAS5XX_MEASURE_START);
	अगर (ret < 0)
		जाओ out_unlock;

	/*
	 * Typical समय to measure 1500 us, max 2000 us so रुको min 500 us
	 * and at most 20000 us (one magnitude more than the datsheet max)
	 * beक्रमe समयout.
	 */
	ret = regmap_पढ़ो_poll_समयout(yas5xx->map, YAS5XX_MEASURE_DATA, busy,
				       !(busy & YAS5XX_MEASURE_DATA_BUSY),
				       500, 20000);
	अगर (ret) अणु
		dev_err(yas5xx->dev, "timeout waiting for measurement\n");
		जाओ out_unlock;
	पूर्ण

	ret = regmap_bulk_पढ़ो(yas5xx->map, YAS5XX_MEASURE_DATA,
			       data, माप(data));
	अगर (ret)
		जाओ out_unlock;

	mutex_unlock(&yas5xx->lock);

	चयन (yas5xx->devid) अणु
	हाल YAS530_DEVICE_ID:
		/*
		 * The t value is 9 bits in big endian क्रमmat
		 * These are the bits used in a 16bit word:
		 * 15 14 13 12 11 10 9  8  7  6  5  4  3  2  1  0
		 *    x  x  x  x  x  x  x  x  x
		 */
		val = get_unaligned_be16(&data[0]);
		val = FIELD_GET(GENMASK(14, 6), val);
		*t = val;
		*x = yas530_extract_axis(&data[2]);
		*y1 = yas530_extract_axis(&data[4]);
		*y2 = yas530_extract_axis(&data[6]);
		अवरोध;
	हाल YAS532_DEVICE_ID:
		/*
		 * The t value is 10 bits in big endian क्रमmat
		 * These are the bits used in a 16bit word:
		 * 15 14 13 12 11 10 9  8  7  6  5  4  3  2  1  0
		 *    x  x  x  x  x  x  x  x  x  x
		 */
		val = get_unaligned_be16(&data[0]);
		val = FIELD_GET(GENMASK(14, 5), val);
		*t = val;
		*x = yas532_extract_axis(&data[2]);
		*y1 = yas532_extract_axis(&data[4]);
		*y2 = yas532_extract_axis(&data[6]);
		अवरोध;
	शेष:
		dev_err(yas5xx->dev, "unknown data format\n");
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;

out_unlock:
	mutex_unlock(&yas5xx->lock);
	वापस ret;
पूर्ण

अटल s32 yas5xx_linearize(काष्ठा yas5xx *yas5xx, u16 val, पूर्णांक axis)
अणु
	काष्ठा yas5xx_calibration *c = &yas5xx->calibration;
	अटल स्थिर s32 yas532ac_coef[] = अणु
		YAS532_VERSION_AC_COEF_X,
		YAS532_VERSION_AC_COEF_Y1,
		YAS532_VERSION_AC_COEF_Y2,
	पूर्ण;
	s32 coef;

	/* Select coefficients */
	चयन (yas5xx->devid) अणु
	हाल YAS530_DEVICE_ID:
		अगर (yas5xx->version == YAS530_VERSION_A)
			coef = YAS530_VERSION_A_COEF;
		अन्यथा
			coef = YAS530_VERSION_B_COEF;
		अवरोध;
	हाल YAS532_DEVICE_ID:
		अगर (yas5xx->version == YAS532_VERSION_AB)
			coef = YAS532_VERSION_AB_COEF;
		अन्यथा
			/* Elaborate coefficients */
			coef = yas532ac_coef[axis];
		अवरोध;
	शेष:
		dev_err(yas5xx->dev, "unknown device type\n");
		वापस val;
	पूर्ण
	/*
	 * Linearization क्रमmula:
	 *
	 * x' = x - (3721 + 50 * f) + (xoffset - r) * c
	 *
	 * Where f and r are calibration values, c is a per-device
	 * and someबार per-axis coefficient.
	 */
	वापस val - (3721 + 50 * c->f[axis]) +
		(yas5xx->hard_offsets[axis] - c->r[axis]) * coef;
पूर्ण

/**
 * yas5xx_get_measure() - Measure a sample of all axis and process
 * @yas5xx: The device state
 * @to: Temperature out
 * @xo: X axis out
 * @yo: Y axis out
 * @zo: Z axis out
 * @वापस: 0 on success or error code
 *
 * Returned values are in nanotesla according to some code.
 */
अटल पूर्णांक yas5xx_get_measure(काष्ठा yas5xx *yas5xx, s32 *to, s32 *xo, s32 *yo, s32 *zo)
अणु
	काष्ठा yas5xx_calibration *c = &yas5xx->calibration;
	u16 t, x, y1, y2;
	/* These are "चिन्हित x, चिन्हित y1 etc */
	s32 sx, sy1, sy2, sy, sz;
	पूर्णांक ret;

	/* We first get raw data that needs to be translated to [x,y,z] */
	ret = yas5xx_measure(yas5xx, &t, &x, &y1, &y2);
	अगर (ret)
		वापस ret;

	/* Do some linearization अगर available */
	sx = yas5xx_linearize(yas5xx, x, 0);
	sy1 = yas5xx_linearize(yas5xx, y1, 1);
	sy2 = yas5xx_linearize(yas5xx, y2, 2);

	/*
	 * Temperature compensation क्रम x, y1, y2 respectively:
	 *
	 *          Cx * t
	 * x' = x - ------
	 *           100
	 */
	sx = sx - (c->Cx * t) / 100;
	sy1 = sy1 - (c->Cy1 * t) / 100;
	sy2 = sy2 - (c->Cy2 * t) / 100;

	/*
	 * Break y1 and y2 पूर्णांकo y and z, y1 and y2 are apparently encoding
	 * y and z.
	 */
	sy = sy1 - sy2;
	sz = -sy1 - sy2;

	/*
	 * FIXME: convert to Celsius? Just guessing this is given
	 * as 1/10:s of degrees so multiply by 100 to get millicentigrades.
	 */
	*to = t * 100;
	/*
	 * Calibrate [x,y,z] with some क्रमmulas like this:
	 *
	 *            100 * x + a_2 * y + a_3 * z
	 *  x' = k *  ---------------------------
	 *                        10
	 *
	 *           a_4 * x + a_5 * y + a_6 * z
	 *  y' = k * ---------------------------
	 *                        10
	 *
	 *           a_7 * x + a_8 * y + a_9 * z
	 *  z' = k * ---------------------------
	 *                        10
	 */
	*xo = c->k * ((100 * sx + c->a2 * sy + c->a3 * sz) / 10);
	*yo = c->k * ((c->a4 * sx + c->a5 * sy + c->a6 * sz) / 10);
	*zo = c->k * ((c->a7 * sx + c->a8 * sy + c->a9 * sz) / 10);

	वापस 0;
पूर्ण

अटल पूर्णांक yas5xx_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2,
			   दीर्घ mask)
अणु
	काष्ठा yas5xx *yas5xx = iio_priv(indio_dev);
	s32 t, x, y, z;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		pm_runसमय_get_sync(yas5xx->dev);
		ret = yas5xx_get_measure(yas5xx, &t, &x, &y, &z);
		pm_runसमय_mark_last_busy(yas5xx->dev);
		pm_runसमय_put_स्वतःsuspend(yas5xx->dev);
		अगर (ret)
			वापस ret;
		चयन (chan->address) अणु
		हाल 0:
			*val = t;
			अवरोध;
		हाल 1:
			*val = x;
			अवरोध;
		हाल 2:
			*val = y;
			अवरोध;
		हाल 3:
			*val = z;
			अवरोध;
		शेष:
			dev_err(yas5xx->dev, "unknown channel\n");
			वापस -EINVAL;
		पूर्ण
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (chan->address == 0) अणु
			/* Temperature is unscaled */
			*val = 1;
			वापस IIO_VAL_INT;
		पूर्ण
		/*
		 * The axis values are in nanotesla according to the venकरोr
		 * drivers, but is clearly in microtesla according to
		 * experiments. Since 1 uT = 0.01 Gauss, we need to भागide
		 * by 100000000 (10^8) to get to Gauss from the raw value.
		 */
		*val = 1;
		*val2 = 100000000;
		वापस IIO_VAL_FRACTIONAL;
	शेष:
		/* Unknown request */
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम yas5xx_fill_buffer(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा yas5xx *yas5xx = iio_priv(indio_dev);
	s32 t, x, y, z;
	पूर्णांक ret;

	pm_runसमय_get_sync(yas5xx->dev);
	ret = yas5xx_get_measure(yas5xx, &t, &x, &y, &z);
	pm_runसमय_mark_last_busy(yas5xx->dev);
	pm_runसमय_put_स्वतःsuspend(yas5xx->dev);
	अगर (ret) अणु
		dev_err(yas5xx->dev, "error refilling buffer\n");
		वापस;
	पूर्ण
	yas5xx->scan.channels[0] = t;
	yas5xx->scan.channels[1] = x;
	yas5xx->scan.channels[2] = y;
	yas5xx->scan.channels[3] = z;
	iio_push_to_buffers_with_बारtamp(indio_dev, &yas5xx->scan,
					   iio_get_समय_ns(indio_dev));
पूर्ण

अटल irqवापस_t yas5xx_handle_trigger(पूर्णांक irq, व्योम *p)
अणु
	स्थिर काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;

	yas5xx_fill_buffer(indio_dev);
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण


अटल स्थिर काष्ठा iio_mount_matrix *
yas5xx_get_mount_matrix(स्थिर काष्ठा iio_dev *indio_dev,
			स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा yas5xx *yas5xx = iio_priv(indio_dev);

	वापस &yas5xx->orientation;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info yas5xx_ext_info[] = अणु
	IIO_MOUNT_MATRIX(IIO_SHARED_BY_सूची, yas5xx_get_mount_matrix),
	अणु पूर्ण
पूर्ण;

#घोषणा YAS5XX_AXIS_CHANNEL(axis, index)				\
	अणु								\
		.type = IIO_MAGN,					\
		.modअगरied = 1,						\
		.channel2 = IIO_MOD_##axis,				\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |		\
			BIT(IIO_CHAN_INFO_SCALE),			\
		.ext_info = yas5xx_ext_info,				\
		.address = index,					\
		.scan_index = index,					\
		.scan_type = अणु						\
			.sign = 's',					\
			.realbits = 32,					\
			.storagebits = 32,				\
			.endianness = IIO_CPU,				\
		पूर्ण,							\
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec yas5xx_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
		.address = 0,
		.scan_index = 0,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 32,
			.storagebits = 32,
			.endianness = IIO_CPU,
		पूर्ण,
	पूर्ण,
	YAS5XX_AXIS_CHANNEL(X, 1),
	YAS5XX_AXIS_CHANNEL(Y, 2),
	YAS5XX_AXIS_CHANNEL(Z, 3),
	IIO_CHAN_SOFT_TIMESTAMP(4),
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ yas5xx_scan_masks[] = अणु GENMASK(3, 0), 0 पूर्ण;

अटल स्थिर काष्ठा iio_info yas5xx_info = अणु
	.पढ़ो_raw = &yas5xx_पढ़ो_raw,
पूर्ण;

अटल bool yas5xx_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg == YAS5XX_ACTUATE_INIT_COIL ||
		reg == YAS5XX_MEASURE ||
		(reg >= YAS5XX_MEASURE_DATA && reg <= YAS5XX_MEASURE_DATA + 8);
पूर्ण

/* TODO: enable regmap cache, using mark dirty and sync at runसमय resume */
अटल स्थिर काष्ठा regmap_config yas5xx_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0xff,
	.अस्थिर_reg = yas5xx_अस्थिर_reg,
पूर्ण;

/**
 * yas53x_extract_calibration() - extracts the a2-a9 and k calibration
 * @data: the bitfield to use
 * @c: the calibration to populate
 */
अटल व्योम yas53x_extract_calibration(u8 *data, काष्ठा yas5xx_calibration *c)
अणु
	u64 val = get_unaligned_be64(data);

	/*
	 * Bitfield layout क्रम the axis calibration data, क्रम factor
	 * a2 = 2 etc, k = k, c = घड़ी भागider
	 *
	 * n   7 6 5 4 3 2 1 0
	 * 0 [ 2 2 2 2 2 2 3 3 ] bits 63 .. 56
	 * 1 [ 3 3 4 4 4 4 4 4 ] bits 55 .. 48
	 * 2 [ 5 5 5 5 5 5 6 6 ] bits 47 .. 40
	 * 3 [ 6 6 6 6 7 7 7 7 ] bits 39 .. 32
	 * 4 [ 7 7 7 8 8 8 8 8 ] bits 31 .. 24
	 * 5 [ 8 9 9 9 9 9 9 9 ] bits 23 .. 16
	 * 6 [ 9 k k k k k c c ] bits 15 .. 8
	 * 7 [ c x x x x x x x ] bits  7 .. 0
	 */
	c->a2 = FIELD_GET(GENMASK_ULL(63, 58), val) - 32;
	c->a3 = FIELD_GET(GENMASK_ULL(57, 54), val) - 8;
	c->a4 = FIELD_GET(GENMASK_ULL(53, 48), val) - 32;
	c->a5 = FIELD_GET(GENMASK_ULL(47, 42), val) + 38;
	c->a6 = FIELD_GET(GENMASK_ULL(41, 36), val) - 32;
	c->a7 = FIELD_GET(GENMASK_ULL(35, 29), val) - 64;
	c->a8 = FIELD_GET(GENMASK_ULL(28, 23), val) - 32;
	c->a9 = FIELD_GET(GENMASK_ULL(22, 15), val);
	c->k = FIELD_GET(GENMASK_ULL(14, 10), val) + 10;
	c->dck = FIELD_GET(GENMASK_ULL(9, 7), val);
पूर्ण

अटल पूर्णांक yas530_get_calibration_data(काष्ठा yas5xx *yas5xx)
अणु
	काष्ठा yas5xx_calibration *c = &yas5xx->calibration;
	u8 data[16];
	u32 val;
	पूर्णांक ret;

	/* Dummy पढ़ो, first पढ़ो is ALWAYS wrong */
	ret = regmap_bulk_पढ़ो(yas5xx->map, YAS5XX_CAL, data, माप(data));
	अगर (ret)
		वापस ret;

	/* Actual calibration पढ़ोout */
	ret = regmap_bulk_पढ़ो(yas5xx->map, YAS5XX_CAL, data, माप(data));
	अगर (ret)
		वापस ret;
	dev_dbg(yas5xx->dev, "calibration data: %*ph\n", 14, data);

	add_device_अक्रमomness(data, माप(data));
	yas5xx->version = data[15] & GENMASK(1, 0);

	/* Extract the calibration from the bitfield */
	c->Cx = data[0] * 6 - 768;
	c->Cy1 = data[1] * 6 - 768;
	c->Cy2 = data[2] * 6 - 768;
	yas53x_extract_calibration(&data[3], c);

	/*
	 * Extract linearization:
	 * Linearization layout in the 32 bits at byte 11:
	 * The r factors are 6 bit values where bit 5 is the sign
	 *
	 * n    7  6  5  4  3  2  1  0
	 * 0 [ xx xx xx r0 r0 r0 r0 r0 ] bits 31 .. 24
	 * 1 [ r0 f0 f0 r1 r1 r1 r1 r1 ] bits 23 .. 16
	 * 2 [ r1 f1 f1 r2 r2 r2 r2 r2 ] bits 15 .. 8
	 * 3 [ r2 f2 f2 xx xx xx xx xx ] bits  7 .. 0
	 */
	val = get_unaligned_be32(&data[11]);
	c->f[0] = FIELD_GET(GENMASK(22, 21), val);
	c->f[1] = FIELD_GET(GENMASK(14, 13), val);
	c->f[2] = FIELD_GET(GENMASK(6, 5), val);
	c->r[0] = sign_extend32(FIELD_GET(GENMASK(28, 23), val), 5);
	c->r[1] = sign_extend32(FIELD_GET(GENMASK(20, 15), val), 5);
	c->r[2] = sign_extend32(FIELD_GET(GENMASK(12, 7), val), 5);
	वापस 0;
पूर्ण

अटल पूर्णांक yas532_get_calibration_data(काष्ठा yas5xx *yas5xx)
अणु
	काष्ठा yas5xx_calibration *c = &yas5xx->calibration;
	u8 data[14];
	u32 val;
	पूर्णांक ret;

	/* Dummy पढ़ो, first पढ़ो is ALWAYS wrong */
	ret = regmap_bulk_पढ़ो(yas5xx->map, YAS5XX_CAL, data, माप(data));
	अगर (ret)
		वापस ret;
	/* Actual calibration पढ़ोout */
	ret = regmap_bulk_पढ़ो(yas5xx->map, YAS5XX_CAL, data, माप(data));
	अगर (ret)
		वापस ret;
	dev_dbg(yas5xx->dev, "calibration data: %*ph\n", 14, data);

	/* Sanity check, is this all zeroes? */
	अगर (स_प्रथम_inv(data, 0x00, 13)) अणु
		अगर (!(data[13] & BIT(7)))
			dev_warn(yas5xx->dev, "calibration is blank!\n");
	पूर्ण

	add_device_अक्रमomness(data, माप(data));
	/* Only one bit of version info reserved here as far as we know */
	yas5xx->version = data[13] & BIT(0);

	/* Extract calibration from the bitfield */
	c->Cx = data[0] * 10 - 1280;
	c->Cy1 = data[1] * 10 - 1280;
	c->Cy2 = data[2] * 10 - 1280;
	yas53x_extract_calibration(&data[3], c);
	/*
	 * Extract linearization:
	 * Linearization layout in the 32 bits at byte 10:
	 * The r factors are 6 bit values where bit 5 is the sign
	 *
	 * n    7  6  5  4  3  2  1  0
	 * 0 [ xx r0 r0 r0 r0 r0 r0 f0 ] bits 31 .. 24
	 * 1 [ f0 r1 r1 r1 r1 r1 r1 f1 ] bits 23 .. 16
	 * 2 [ f1 r2 r2 r2 r2 r2 r2 f2 ] bits 15 .. 8
	 * 3 [ f2 xx xx xx xx xx xx xx ] bits  7 .. 0
	 */
	val = get_unaligned_be32(&data[10]);
	c->f[0] = FIELD_GET(GENMASK(24, 23), val);
	c->f[1] = FIELD_GET(GENMASK(16, 15), val);
	c->f[2] = FIELD_GET(GENMASK(8, 7), val);
	c->r[0] = sign_extend32(FIELD_GET(GENMASK(30, 25), val), 5);
	c->r[1] = sign_extend32(FIELD_GET(GENMASK(22, 17), val), 5);
	c->r[2] = sign_extend32(FIELD_GET(GENMASK(14, 7), val), 5);

	वापस 0;
पूर्ण

अटल व्योम yas5xx_dump_calibration(काष्ठा yas5xx *yas5xx)
अणु
	काष्ठा yas5xx_calibration *c = &yas5xx->calibration;

	dev_dbg(yas5xx->dev, "f[] = [%d, %d, %d]\n",
		c->f[0], c->f[1], c->f[2]);
	dev_dbg(yas5xx->dev, "r[] = [%d, %d, %d]\n",
		c->r[0], c->r[1], c->r[2]);
	dev_dbg(yas5xx->dev, "Cx = %d\n", c->Cx);
	dev_dbg(yas5xx->dev, "Cy1 = %d\n", c->Cy1);
	dev_dbg(yas5xx->dev, "Cy2 = %d\n", c->Cy2);
	dev_dbg(yas5xx->dev, "a2 = %d\n", c->a2);
	dev_dbg(yas5xx->dev, "a3 = %d\n", c->a3);
	dev_dbg(yas5xx->dev, "a4 = %d\n", c->a4);
	dev_dbg(yas5xx->dev, "a5 = %d\n", c->a5);
	dev_dbg(yas5xx->dev, "a6 = %d\n", c->a6);
	dev_dbg(yas5xx->dev, "a7 = %d\n", c->a7);
	dev_dbg(yas5xx->dev, "a8 = %d\n", c->a8);
	dev_dbg(yas5xx->dev, "a9 = %d\n", c->a9);
	dev_dbg(yas5xx->dev, "k = %d\n", c->k);
	dev_dbg(yas5xx->dev, "dck = %d\n", c->dck);
पूर्ण

अटल पूर्णांक yas5xx_set_offsets(काष्ठा yas5xx *yas5xx, s8 ox, s8 oy1, s8 oy2)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(yas5xx->map, YAS5XX_OFFSET_X, ox);
	अगर (ret)
		वापस ret;
	ret = regmap_ग_लिखो(yas5xx->map, YAS5XX_OFFSET_Y1, oy1);
	अगर (ret)
		वापस ret;
	वापस regmap_ग_लिखो(yas5xx->map, YAS5XX_OFFSET_Y2, oy2);
पूर्ण

अटल s8 yas5xx_adjust_offset(s8 old, पूर्णांक bit, u16 center, u16 measure)
अणु
	अगर (measure > center)
		वापस old + BIT(bit);
	अगर (measure < center)
		वापस old - BIT(bit);
	वापस old;
पूर्ण

अटल पूर्णांक yas5xx_meaure_offsets(काष्ठा yas5xx *yas5xx)
अणु
	पूर्णांक ret;
	u16 center;
	u16 t, x, y1, y2;
	s8 ox, oy1, oy2;
	पूर्णांक i;

	/* Actuate the init coil and measure offsets */
	ret = regmap_ग_लिखो(yas5xx->map, YAS5XX_ACTUATE_INIT_COIL, 0);
	अगर (ret)
		वापस ret;

	/* When the initcoil is active this should be around the center */
	चयन (yas5xx->devid) अणु
	हाल YAS530_DEVICE_ID:
		center = YAS530_DATA_CENTER;
		अवरोध;
	हाल YAS532_DEVICE_ID:
		center = YAS532_DATA_CENTER;
		अवरोध;
	शेष:
		dev_err(yas5xx->dev, "unknown device type\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * We set offsets in the पूर्णांकerval +-31 by iterating
	 * +-16, +-8, +-4, +-2, +-1 adjusting the offsets each
	 * समय, then writing the final offsets पूर्णांकo the
	 * रेजिस्टरs.
	 *
	 * NOTE: these offsets are NOT in the same unit or magnitude
	 * as the values क्रम [x, y1, y2]. The value is +/-31
	 * but the effect on the raw values is much larger.
	 * The effect of the offset is to bring the measure
	 * rougly to the center.
	 */
	ox = 0;
	oy1 = 0;
	oy2 = 0;

	क्रम (i = 4; i >= 0; i--) अणु
		ret = yas5xx_set_offsets(yas5xx, ox, oy1, oy2);
		अगर (ret)
			वापस ret;

		ret = yas5xx_measure(yas5xx, &t, &x, &y1, &y2);
		अगर (ret)
			वापस ret;
		dev_dbg(yas5xx->dev, "measurement %d: x=%d, y1=%d, y2=%d\n",
			5-i, x, y1, y2);

		ox = yas5xx_adjust_offset(ox, i, center, x);
		oy1 = yas5xx_adjust_offset(oy1, i, center, y1);
		oy2 = yas5xx_adjust_offset(oy2, i, center, y2);
	पूर्ण

	/* Needed क्रम calibration algorithm */
	yas5xx->hard_offsets[0] = ox;
	yas5xx->hard_offsets[1] = oy1;
	yas5xx->hard_offsets[2] = oy2;
	ret = yas5xx_set_offsets(yas5xx, ox, oy1, oy2);
	अगर (ret)
		वापस ret;

	dev_info(yas5xx->dev, "discovered hard offsets: x=%d, y1=%d, y2=%d\n",
		 ox, oy1, oy2);
	वापस 0;
पूर्ण

अटल पूर्णांक yas5xx_घातer_on(काष्ठा yas5xx *yas5xx)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/* Zero the test रेजिस्टरs */
	ret = regmap_ग_लिखो(yas5xx->map, YAS5XX_TEST1, 0);
	अगर (ret)
		वापस ret;
	ret = regmap_ग_लिखो(yas5xx->map, YAS5XX_TEST2, 0);
	अगर (ret)
		वापस ret;

	/* Set up क्रम no पूर्णांकerrupts, calibrated घड़ी भागider */
	val = FIELD_PREP(YAS5XX_CONFIG_CCK_MASK, yas5xx->calibration.dck);
	ret = regmap_ग_लिखो(yas5xx->map, YAS5XX_CONFIG, val);
	अगर (ret)
		वापस ret;

	/* Measure पूर्णांकerval 0 (back-to-back?)  */
	वापस regmap_ग_लिखो(yas5xx->map, YAS5XX_MEASURE_INTERVAL, 0);
पूर्ण

अटल पूर्णांक yas5xx_probe(काष्ठा i2c_client *i2c,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा device *dev = &i2c->dev;
	काष्ठा yas5xx *yas5xx;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*yas5xx));
	अगर (!indio_dev)
		वापस -ENOMEM;

	yas5xx = iio_priv(indio_dev);
	i2c_set_clientdata(i2c, indio_dev);
	yas5xx->dev = dev;
	mutex_init(&yas5xx->lock);

	ret = iio_पढ़ो_mount_matrix(dev, "mount-matrix", &yas5xx->orientation);
	अगर (ret)
		वापस ret;

	yas5xx->regs[0].supply = "vdd";
	yas5xx->regs[1].supply = "iovdd";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(yas5xx->regs),
				      yas5xx->regs);
	अगर (ret)
		वापस dev_err_probe(dev, ret, "cannot get regulators\n");

	ret = regulator_bulk_enable(ARRAY_SIZE(yas5xx->regs), yas5xx->regs);
	अगर (ret) अणु
		dev_err(dev, "cannot enable regulators\n");
		वापस ret;
	पूर्ण

	/* See comment in runसमय resume callback */
	usleep_range(31000, 40000);

	/* This will take the device out of reset अगर need be */
	yas5xx->reset = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(yas5xx->reset)) अणु
		ret = dev_err_probe(dev, PTR_ERR(yas5xx->reset),
				    "failed to get reset line\n");
		जाओ reg_off;
	पूर्ण

	yas5xx->map = devm_regmap_init_i2c(i2c, &yas5xx_regmap_config);
	अगर (IS_ERR(yas5xx->map)) अणु
		dev_err(dev, "failed to allocate register map\n");
		ret = PTR_ERR(yas5xx->map);
		जाओ निश्चित_reset;
	पूर्ण

	ret = regmap_पढ़ो(yas5xx->map, YAS5XX_DEVICE_ID, &yas5xx->devid);
	अगर (ret)
		जाओ निश्चित_reset;

	चयन (yas5xx->devid) अणु
	हाल YAS530_DEVICE_ID:
		ret = yas530_get_calibration_data(yas5xx);
		अगर (ret)
			जाओ निश्चित_reset;
		dev_info(dev, "detected YAS530 MS-3E %s",
			 yas5xx->version ? "B" : "A");
		म_नकलन(yas5xx->name, "yas530", माप(yas5xx->name));
		अवरोध;
	हाल YAS532_DEVICE_ID:
		ret = yas532_get_calibration_data(yas5xx);
		अगर (ret)
			जाओ निश्चित_reset;
		dev_info(dev, "detected YAS532/YAS533 MS-3R/F %s",
			 yas5xx->version ? "AC" : "AB");
		म_नकलन(yas5xx->name, "yas532", माप(yas5xx->name));
		अवरोध;
	शेष:
		ret = -ENODEV;
		dev_err(dev, "unhandled device ID %02x\n", yas5xx->devid);
		जाओ निश्चित_reset;
	पूर्ण

	yas5xx_dump_calibration(yas5xx);
	ret = yas5xx_घातer_on(yas5xx);
	अगर (ret)
		जाओ निश्चित_reset;
	ret = yas5xx_meaure_offsets(yas5xx);
	अगर (ret)
		जाओ निश्चित_reset;

	indio_dev->info = &yas5xx_info;
	indio_dev->available_scan_masks = yas5xx_scan_masks;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->name = yas5xx->name;
	indio_dev->channels = yas5xx_channels;
	indio_dev->num_channels = ARRAY_SIZE(yas5xx_channels);

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
					 yas5xx_handle_trigger,
					 शून्य);
	अगर (ret) अणु
		dev_err(dev, "triggered buffer setup failed\n");
		जाओ निश्चित_reset;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(dev, "device register failed\n");
		जाओ cleanup_buffer;
	पूर्ण

	/* Take runसमय PM online */
	pm_runसमय_get_noresume(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	pm_runसमय_set_स्वतःsuspend_delay(dev, YAS5XX_AUTOSUSPEND_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_put(dev);

	वापस 0;

cleanup_buffer:
	iio_triggered_buffer_cleanup(indio_dev);
निश्चित_reset:
	gpiod_set_value_cansleep(yas5xx->reset, 1);
reg_off:
	regulator_bulk_disable(ARRAY_SIZE(yas5xx->regs), yas5xx->regs);

	वापस ret;
पूर्ण

अटल पूर्णांक yas5xx_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(i2c);
	काष्ठा yas5xx *yas5xx = iio_priv(indio_dev);
	काष्ठा device *dev = &i2c->dev;

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	/*
	 * Now we can't get any more पढ़ोs from the device, which would
	 * also call pm_runसमय* functions and race with our disable
	 * code. Disable PM runसमय in orderly fashion and घातer करोwn.
	 */
	pm_runसमय_get_sync(dev);
	pm_runसमय_put_noidle(dev);
	pm_runसमय_disable(dev);
	gpiod_set_value_cansleep(yas5xx->reset, 1);
	regulator_bulk_disable(ARRAY_SIZE(yas5xx->regs), yas5xx->regs);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused yas5xx_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा yas5xx *yas5xx = iio_priv(indio_dev);

	gpiod_set_value_cansleep(yas5xx->reset, 1);
	regulator_bulk_disable(ARRAY_SIZE(yas5xx->regs), yas5xx->regs);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused yas5xx_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा yas5xx *yas5xx = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(yas5xx->regs), yas5xx->regs);
	अगर (ret) अणु
		dev_err(dev, "cannot enable regulators\n");
		वापस ret;
	पूर्ण

	/*
	 * The YAS530 datasheet says TVSKW is up to 30 ms, after that 1 ms
	 * क्रम all voltages to settle. The YAS532 is 10ms then 4ms क्रम the
	 * I2C to come online. Let's keep it safe and put this at 31ms.
	 */
	usleep_range(31000, 40000);
	gpiod_set_value_cansleep(yas5xx->reset, 0);

	ret = yas5xx_घातer_on(yas5xx);
	अगर (ret) अणु
		dev_err(dev, "cannot power on\n");
		जाओ out_reset;
	पूर्ण

	वापस 0;

out_reset:
	gpiod_set_value_cansleep(yas5xx->reset, 1);
	regulator_bulk_disable(ARRAY_SIZE(yas5xx->regs), yas5xx->regs);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops yas5xx_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(yas5xx_runसमय_suspend,
			   yas5xx_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id yas5xx_id[] = अणु
	अणु"yas530", पूर्ण,
	अणु"yas532", पूर्ण,
	अणु"yas533", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, yas5xx_id);

अटल स्थिर काष्ठा of_device_id yas5xx_of_match[] = अणु
	अणु .compatible = "yamaha,yas530", पूर्ण,
	अणु .compatible = "yamaha,yas532", पूर्ण,
	अणु .compatible = "yamaha,yas533", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, yas5xx_of_match);

अटल काष्ठा i2c_driver yas5xx_driver = अणु
	.driver	 = अणु
		.name	= "yas5xx",
		.of_match_table = yas5xx_of_match,
		.pm = &yas5xx_dev_pm_ops,
	पूर्ण,
	.probe	  = yas5xx_probe,
	.हटाओ	  = yas5xx_हटाओ,
	.id_table = yas5xx_id,
पूर्ण;
module_i2c_driver(yas5xx_driver);

MODULE_DESCRIPTION("Yamaha YAS53x 3-axis magnetometer driver");
MODULE_AUTHOR("Linus Walleij");
MODULE_LICENSE("GPL v2");
