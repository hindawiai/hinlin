<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ADXL372 3-Axis Digital Accelerometer core driver
 *
 * Copyright 2018 Analog Devices Inc.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

#समावेश "adxl372.h"

/* ADXL372 रेजिस्टरs definition */
#घोषणा ADXL372_DEVID			0x00
#घोषणा ADXL372_DEVID_MST		0x01
#घोषणा ADXL372_PARTID			0x02
#घोषणा ADXL372_STATUS_1		0x04
#घोषणा ADXL372_STATUS_2		0x05
#घोषणा ADXL372_FIFO_ENTRIES_2		0x06
#घोषणा ADXL372_FIFO_ENTRIES_1		0x07
#घोषणा ADXL372_X_DATA_H		0x08
#घोषणा ADXL372_X_DATA_L		0x09
#घोषणा ADXL372_Y_DATA_H		0x0A
#घोषणा ADXL372_Y_DATA_L		0x0B
#घोषणा ADXL372_Z_DATA_H		0x0C
#घोषणा ADXL372_Z_DATA_L		0x0D
#घोषणा ADXL372_X_MAXPEAK_H		0x15
#घोषणा ADXL372_X_MAXPEAK_L		0x16
#घोषणा ADXL372_Y_MAXPEAK_H		0x17
#घोषणा ADXL372_Y_MAXPEAK_L		0x18
#घोषणा ADXL372_Z_MAXPEAK_H		0x19
#घोषणा ADXL372_Z_MAXPEAK_L		0x1A
#घोषणा ADXL372_OFFSET_X		0x20
#घोषणा ADXL372_OFFSET_Y		0x21
#घोषणा ADXL372_OFFSET_Z		0x22
#घोषणा ADXL372_X_THRESH_ACT_H		0x23
#घोषणा ADXL372_X_THRESH_ACT_L		0x24
#घोषणा ADXL372_Y_THRESH_ACT_H		0x25
#घोषणा ADXL372_Y_THRESH_ACT_L		0x26
#घोषणा ADXL372_Z_THRESH_ACT_H		0x27
#घोषणा ADXL372_Z_THRESH_ACT_L		0x28
#घोषणा ADXL372_TIME_ACT		0x29
#घोषणा ADXL372_X_THRESH_INACT_H	0x2A
#घोषणा ADXL372_X_THRESH_INACT_L	0x2B
#घोषणा ADXL372_Y_THRESH_INACT_H	0x2C
#घोषणा ADXL372_Y_THRESH_INACT_L	0x2D
#घोषणा ADXL372_Z_THRESH_INACT_H	0x2E
#घोषणा ADXL372_Z_THRESH_INACT_L	0x2F
#घोषणा ADXL372_TIME_INACT_H		0x30
#घोषणा ADXL372_TIME_INACT_L		0x31
#घोषणा ADXL372_X_THRESH_ACT2_H		0x32
#घोषणा ADXL372_X_THRESH_ACT2_L		0x33
#घोषणा ADXL372_Y_THRESH_ACT2_H		0x34
#घोषणा ADXL372_Y_THRESH_ACT2_L		0x35
#घोषणा ADXL372_Z_THRESH_ACT2_H		0x36
#घोषणा ADXL372_Z_THRESH_ACT2_L		0x37
#घोषणा ADXL372_HPF			0x38
#घोषणा ADXL372_FIFO_SAMPLES		0x39
#घोषणा ADXL372_FIFO_CTL		0x3A
#घोषणा ADXL372_INT1_MAP		0x3B
#घोषणा ADXL372_INT2_MAP		0x3C
#घोषणा ADXL372_TIMING			0x3D
#घोषणा ADXL372_MEASURE			0x3E
#घोषणा ADXL372_POWER_CTL		0x3F
#घोषणा ADXL372_SELF_TEST		0x40
#घोषणा ADXL372_RESET			0x41
#घोषणा ADXL372_FIFO_DATA		0x42

#घोषणा ADXL372_DEVID_VAL		0xAD
#घोषणा ADXL372_PARTID_VAL		0xFA
#घोषणा ADXL372_RESET_CODE		0x52

/* ADXL372_POWER_CTL */
#घोषणा ADXL372_POWER_CTL_MODE_MSK		GENMASK_ULL(1, 0)
#घोषणा ADXL372_POWER_CTL_MODE(x)		(((x) & 0x3) << 0)

/* ADXL372_MEASURE */
#घोषणा ADXL372_MEASURE_LINKLOOP_MSK		GENMASK_ULL(5, 4)
#घोषणा ADXL372_MEASURE_LINKLOOP_MODE(x)	(((x) & 0x3) << 4)
#घोषणा ADXL372_MEASURE_BANDWIDTH_MSK		GENMASK_ULL(2, 0)
#घोषणा ADXL372_MEASURE_BANDWIDTH_MODE(x)	(((x) & 0x7) << 0)

/* ADXL372_TIMING */
#घोषणा ADXL372_TIMING_ODR_MSK			GENMASK_ULL(7, 5)
#घोषणा ADXL372_TIMING_ODR_MODE(x)		(((x) & 0x7) << 5)

/* ADXL372_FIFO_CTL */
#घोषणा ADXL372_FIFO_CTL_FORMAT_MSK		GENMASK(5, 3)
#घोषणा ADXL372_FIFO_CTL_FORMAT_MODE(x)		(((x) & 0x7) << 3)
#घोषणा ADXL372_FIFO_CTL_MODE_MSK		GENMASK(2, 1)
#घोषणा ADXL372_FIFO_CTL_MODE_MODE(x)		(((x) & 0x3) << 1)
#घोषणा ADXL372_FIFO_CTL_SAMPLES_MSK		BIT(1)
#घोषणा ADXL372_FIFO_CTL_SAMPLES_MODE(x)	(((x) > 0xFF) ? 1 : 0)

/* ADXL372_STATUS_1 */
#घोषणा ADXL372_STATUS_1_DATA_RDY(x)		(((x) >> 0) & 0x1)
#घोषणा ADXL372_STATUS_1_FIFO_RDY(x)		(((x) >> 1) & 0x1)
#घोषणा ADXL372_STATUS_1_FIFO_FULL(x)		(((x) >> 2) & 0x1)
#घोषणा ADXL372_STATUS_1_FIFO_OVR(x)		(((x) >> 3) & 0x1)
#घोषणा ADXL372_STATUS_1_USR_NVM_BUSY(x)	(((x) >> 5) & 0x1)
#घोषणा ADXL372_STATUS_1_AWAKE(x)		(((x) >> 6) & 0x1)
#घोषणा ADXL372_STATUS_1_ERR_USR_REGS(x)	(((x) >> 7) & 0x1)

/* ADXL372_STATUS_2 */
#घोषणा ADXL372_STATUS_2_INACT(x)		(((x) >> 4) & 0x1)
#घोषणा ADXL372_STATUS_2_ACT(x)			(((x) >> 5) & 0x1)
#घोषणा ADXL372_STATUS_2_AC2(x)			(((x) >> 6) & 0x1)

/* ADXL372_INT1_MAP */
#घोषणा ADXL372_INT1_MAP_DATA_RDY_MSK		BIT(0)
#घोषणा ADXL372_INT1_MAP_DATA_RDY_MODE(x)	(((x) & 0x1) << 0)
#घोषणा ADXL372_INT1_MAP_FIFO_RDY_MSK		BIT(1)
#घोषणा ADXL372_INT1_MAP_FIFO_RDY_MODE(x)	(((x) & 0x1) << 1)
#घोषणा ADXL372_INT1_MAP_FIFO_FULL_MSK		BIT(2)
#घोषणा ADXL372_INT1_MAP_FIFO_FULL_MODE(x)	(((x) & 0x1) << 2)
#घोषणा ADXL372_INT1_MAP_FIFO_OVR_MSK		BIT(3)
#घोषणा ADXL372_INT1_MAP_FIFO_OVR_MODE(x)	(((x) & 0x1) << 3)
#घोषणा ADXL372_INT1_MAP_INACT_MSK		BIT(4)
#घोषणा ADXL372_INT1_MAP_INACT_MODE(x)		(((x) & 0x1) << 4)
#घोषणा ADXL372_INT1_MAP_ACT_MSK		BIT(5)
#घोषणा ADXL372_INT1_MAP_ACT_MODE(x)		(((x) & 0x1) << 5)
#घोषणा ADXL372_INT1_MAP_AWAKE_MSK		BIT(6)
#घोषणा ADXL372_INT1_MAP_AWAKE_MODE(x)		(((x) & 0x1) << 6)
#घोषणा ADXL372_INT1_MAP_LOW_MSK		BIT(7)
#घोषणा ADXL372_INT1_MAP_LOW_MODE(x)		(((x) & 0x1) << 7)

/* ADX372_THRESH */
#घोषणा ADXL372_THRESH_VAL_H_MSK	GENMASK(10, 3)
#घोषणा ADXL372_THRESH_VAL_H_SEL(x)	FIELD_GET(ADXL372_THRESH_VAL_H_MSK, x)
#घोषणा ADXL372_THRESH_VAL_L_MSK	GENMASK(2, 0)
#घोषणा ADXL372_THRESH_VAL_L_SEL(x)	FIELD_GET(ADXL372_THRESH_VAL_L_MSK, x)

/* The ADXL372 includes a deep, 512 sample FIFO buffer */
#घोषणा ADXL372_FIFO_SIZE			512
#घोषणा ADXL372_X_AXIS_EN(x)			((x) & BIT(0))
#घोषणा ADXL372_Y_AXIS_EN(x)			((x) & BIT(1))
#घोषणा ADXL372_Z_AXIS_EN(x)			((x) & BIT(2))

/*
 * At +/- 200g with 12-bit resolution, scale is computed as:
 * (200 + 200) * 9.81 / (2^12 - 1) = 0.958241
 */
#घोषणा ADXL372_USCALE	958241

क्रमागत adxl372_op_mode अणु
	ADXL372_STANDBY,
	ADXL372_WAKE_UP,
	ADXL372_INSTANT_ON,
	ADXL372_FULL_BW_MEASUREMENT,
पूर्ण;

क्रमागत adxl372_act_proc_mode अणु
	ADXL372_DEFAULT,
	ADXL372_LINKED,
	ADXL372_LOOPED,
पूर्ण;

क्रमागत adxl372_th_activity अणु
	ADXL372_ACTIVITY,
	ADXL372_ACTIVITY2,
	ADXL372_INACTIVITY,
पूर्ण;

क्रमागत adxl372_odr अणु
	ADXL372_ODR_400HZ,
	ADXL372_ODR_800HZ,
	ADXL372_ODR_1600HZ,
	ADXL372_ODR_3200HZ,
	ADXL372_ODR_6400HZ,
पूर्ण;

क्रमागत adxl372_bandwidth अणु
	ADXL372_BW_200HZ,
	ADXL372_BW_400HZ,
	ADXL372_BW_800HZ,
	ADXL372_BW_1600HZ,
	ADXL372_BW_3200HZ,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक adxl372_th_reg_high_addr[3] = अणु
	[ADXL372_ACTIVITY] = ADXL372_X_THRESH_ACT_H,
	[ADXL372_ACTIVITY2] = ADXL372_X_THRESH_ACT2_H,
	[ADXL372_INACTIVITY] = ADXL372_X_THRESH_INACT_H,
पूर्ण;

क्रमागत adxl372_fअगरo_क्रमmat अणु
	ADXL372_XYZ_FIFO,
	ADXL372_X_FIFO,
	ADXL372_Y_FIFO,
	ADXL372_XY_FIFO,
	ADXL372_Z_FIFO,
	ADXL372_XZ_FIFO,
	ADXL372_YZ_FIFO,
	ADXL372_XYZ_PEAK_FIFO,
पूर्ण;

क्रमागत adxl372_fअगरo_mode अणु
	ADXL372_FIFO_BYPASSED,
	ADXL372_FIFO_STREAMED,
	ADXL372_FIFO_TRIGGERED,
	ADXL372_FIFO_OLD_SAVED
पूर्ण;

अटल स्थिर पूर्णांक adxl372_samp_freq_tbl[5] = अणु
	400, 800, 1600, 3200, 6400,
पूर्ण;

अटल स्थिर पूर्णांक adxl372_bw_freq_tbl[5] = अणु
	200, 400, 800, 1600, 3200,
पूर्ण;

काष्ठा adxl372_axis_lookup अणु
	अचिन्हित पूर्णांक bits;
	क्रमागत adxl372_fअगरo_क्रमmat fअगरo_क्रमmat;
पूर्ण;

अटल स्थिर काष्ठा adxl372_axis_lookup adxl372_axis_lookup_table[] = अणु
	अणु BIT(0), ADXL372_X_FIFO पूर्ण,
	अणु BIT(1), ADXL372_Y_FIFO पूर्ण,
	अणु BIT(2), ADXL372_Z_FIFO पूर्ण,
	अणु BIT(0) | BIT(1), ADXL372_XY_FIFO पूर्ण,
	अणु BIT(0) | BIT(2), ADXL372_XZ_FIFO पूर्ण,
	अणु BIT(1) | BIT(2), ADXL372_YZ_FIFO पूर्ण,
	अणु BIT(0) | BIT(1) | BIT(2), ADXL372_XYZ_FIFO पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec adxl372_events[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE),
		.mask_shared_by_all = BIT(IIO_EV_INFO_PERIOD) | BIT(IIO_EV_INFO_ENABLE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE),
		.mask_shared_by_all = BIT(IIO_EV_INFO_PERIOD) | BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

#घोषणा ADXL372_ACCEL_CHANNEL(index, reg, axis) अणु			\
	.type = IIO_ACCEL,						\
	.address = reg,							\
	.modअगरied = 1,							\
	.channel2 = IIO_MOD_##axis,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),			\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |		\
				    BIT(IIO_CHAN_INFO_SAMP_FREQ) |	\
		BIT(IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY),	\
	.scan_index = index,						\
	.scan_type = अणु							\
		.sign = 's',						\
		.realbits = 12,						\
		.storagebits = 16,					\
		.shअगरt = 4,						\
		.endianness = IIO_BE,					\
	पूर्ण,								\
	.event_spec = adxl372_events,					\
	.num_event_specs = ARRAY_SIZE(adxl372_events)			\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec adxl372_channels[] = अणु
	ADXL372_ACCEL_CHANNEL(0, ADXL372_X_DATA_H, X),
	ADXL372_ACCEL_CHANNEL(1, ADXL372_Y_DATA_H, Y),
	ADXL372_ACCEL_CHANNEL(2, ADXL372_Z_DATA_H, Z),
पूर्ण;

काष्ठा adxl372_state अणु
	पूर्णांक				irq;
	काष्ठा device			*dev;
	काष्ठा regmap			*regmap;
	काष्ठा iio_trigger		*dपढ़ोy_trig;
	काष्ठा iio_trigger		*peak_datardy_trig;
	क्रमागत adxl372_fअगरo_mode		fअगरo_mode;
	क्रमागत adxl372_fअगरo_क्रमmat	fअगरo_क्रमmat;
	अचिन्हित पूर्णांक			fअगरo_axis_mask;
	क्रमागत adxl372_op_mode		op_mode;
	क्रमागत adxl372_act_proc_mode	act_proc_mode;
	क्रमागत adxl372_odr		odr;
	क्रमागत adxl372_bandwidth		bw;
	u32				act_समय_ms;
	u32				inact_समय_ms;
	u8				fअगरo_set_size;
	अचिन्हित दीर्घ			पूर्णांक1_biपंचांगask;
	अचिन्हित दीर्घ			पूर्णांक2_biपंचांगask;
	u16				watermark;
	__be16				fअगरo_buf[ADXL372_FIFO_SIZE];
	bool				peak_fअगरo_mode_en;
	काष्ठा mutex			threshold_m; /* lock क्रम threshold */
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ adxl372_channel_masks[] = अणु
	BIT(0), BIT(1), BIT(2),
	BIT(0) | BIT(1),
	BIT(0) | BIT(2),
	BIT(1) | BIT(2),
	BIT(0) | BIT(1) | BIT(2),
	0
पूर्ण;

अटल sमाप_प्रकार adxl372_पढ़ो_threshold_value(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक addr,
					    u16 *threshold)
अणु
	काष्ठा adxl372_state *st = iio_priv(indio_dev);
	__be16 raw_regval;
	u16 regval;
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(st->regmap, addr, &raw_regval, माप(raw_regval));
	अगर (ret < 0)
		वापस ret;

	regval = be16_to_cpu(raw_regval);
	regval >>= 5;

	*threshold = regval;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार adxl372_ग_लिखो_threshold_value(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक addr,
					     u16 threshold)
अणु
	काष्ठा adxl372_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->threshold_m);
	ret = regmap_ग_लिखो(st->regmap, addr, ADXL372_THRESH_VAL_H_SEL(threshold));
	अगर (ret < 0)
		जाओ unlock;

	ret = regmap_update_bits(st->regmap, addr + 1, GENMASK(7, 5),
				 ADXL372_THRESH_VAL_L_SEL(threshold) << 5);

unlock:
	mutex_unlock(&st->threshold_m);

	वापस ret;
पूर्ण

अटल पूर्णांक adxl372_पढ़ो_axis(काष्ठा adxl372_state *st, u8 addr)
अणु
	__be16 regval;
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(st->regmap, addr, &regval, माप(regval));
	अगर (ret < 0)
		वापस ret;

	वापस be16_to_cpu(regval);
पूर्ण

अटल पूर्णांक adxl372_set_op_mode(काष्ठा adxl372_state *st,
			       क्रमागत adxl372_op_mode op_mode)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(st->regmap, ADXL372_POWER_CTL,
				 ADXL372_POWER_CTL_MODE_MSK,
				 ADXL372_POWER_CTL_MODE(op_mode));
	अगर (ret < 0)
		वापस ret;

	st->op_mode = op_mode;

	वापस ret;
पूर्ण

अटल पूर्णांक adxl372_set_odr(काष्ठा adxl372_state *st,
			   क्रमागत adxl372_odr odr)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(st->regmap, ADXL372_TIMING,
				 ADXL372_TIMING_ODR_MSK,
				 ADXL372_TIMING_ODR_MODE(odr));
	अगर (ret < 0)
		वापस ret;

	st->odr = odr;

	वापस ret;
पूर्ण

अटल पूर्णांक adxl372_find_बंदst_match(स्थिर पूर्णांक *array,
				      अचिन्हित पूर्णांक size, पूर्णांक val)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		अगर (val <= array[i])
			वापस i;
	पूर्ण

	वापस size - 1;
पूर्ण

अटल पूर्णांक adxl372_set_bandwidth(काष्ठा adxl372_state *st,
				 क्रमागत adxl372_bandwidth bw)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(st->regmap, ADXL372_MEASURE,
				 ADXL372_MEASURE_BANDWIDTH_MSK,
				 ADXL372_MEASURE_BANDWIDTH_MODE(bw));
	अगर (ret < 0)
		वापस ret;

	st->bw = bw;

	वापस ret;
पूर्ण

अटल पूर्णांक adxl372_set_act_proc_mode(काष्ठा adxl372_state *st,
				     क्रमागत adxl372_act_proc_mode mode)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(st->regmap,
				 ADXL372_MEASURE,
				 ADXL372_MEASURE_LINKLOOP_MSK,
				 ADXL372_MEASURE_LINKLOOP_MODE(mode));
	अगर (ret < 0)
		वापस ret;

	st->act_proc_mode = mode;

	वापस ret;
पूर्ण

अटल पूर्णांक adxl372_set_activity_threshold(काष्ठा adxl372_state *st,
					  क्रमागत adxl372_th_activity act,
					  bool ref_en, bool enable,
					  अचिन्हित पूर्णांक threshold)
अणु
	अचिन्हित अक्षर buf[6];
	अचिन्हित अक्षर th_reg_high_val, th_reg_low_val, th_reg_high_addr;

	/* scale factor is 100 mg/code */
	th_reg_high_val = (threshold / 100) >> 3;
	th_reg_low_val = ((threshold / 100) << 5) | (ref_en << 1) | enable;
	th_reg_high_addr = adxl372_th_reg_high_addr[act];

	buf[0] = th_reg_high_val;
	buf[1] = th_reg_low_val;
	buf[2] = th_reg_high_val;
	buf[3] = th_reg_low_val;
	buf[4] = th_reg_high_val;
	buf[5] = th_reg_low_val;

	वापस regmap_bulk_ग_लिखो(st->regmap, th_reg_high_addr,
				 buf, ARRAY_SIZE(buf));
पूर्ण

अटल पूर्णांक adxl372_set_activity_समय_ms(काष्ठा adxl372_state *st,
					अचिन्हित पूर्णांक act_समय_ms)
अणु
	अचिन्हित पूर्णांक reg_val, scale_factor;
	पूर्णांक ret;

	/*
	 * 3.3 ms per code is the scale factor of the TIME_ACT रेजिस्टर क्रम
	 * ODR = 6400 Hz. It is 6.6 ms per code क्रम ODR = 3200 Hz and below.
	 */
	अगर (st->odr == ADXL372_ODR_6400HZ)
		scale_factor = 3300;
	अन्यथा
		scale_factor = 6600;

	reg_val = DIV_ROUND_CLOSEST(act_समय_ms * 1000, scale_factor);

	/* TIME_ACT रेजिस्टर is 8 bits wide */
	अगर (reg_val > 0xFF)
		reg_val = 0xFF;

	ret = regmap_ग_लिखो(st->regmap, ADXL372_TIME_ACT, reg_val);
	अगर (ret < 0)
		वापस ret;

	st->act_समय_ms = act_समय_ms;

	वापस ret;
पूर्ण

अटल पूर्णांक adxl372_set_inactivity_समय_ms(काष्ठा adxl372_state *st,
					  अचिन्हित पूर्णांक inact_समय_ms)
अणु
	अचिन्हित पूर्णांक reg_val_h, reg_val_l, res, scale_factor;
	पूर्णांक ret;

	/*
	 * 13 ms per code is the scale factor of the TIME_INACT रेजिस्टर क्रम
	 * ODR = 6400 Hz. It is 26 ms per code क्रम ODR = 3200 Hz and below.
	 */
	अगर (st->odr == ADXL372_ODR_6400HZ)
		scale_factor = 13;
	अन्यथा
		scale_factor = 26;

	res = DIV_ROUND_CLOSEST(inact_समय_ms, scale_factor);
	reg_val_h = (res >> 8) & 0xFF;
	reg_val_l = res & 0xFF;

	ret = regmap_ग_लिखो(st->regmap, ADXL372_TIME_INACT_H, reg_val_h);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(st->regmap, ADXL372_TIME_INACT_L, reg_val_l);
	अगर (ret < 0)
		वापस ret;

	st->inact_समय_ms = inact_समय_ms;

	वापस ret;
पूर्ण

अटल पूर्णांक adxl372_set_पूर्णांकerrupts(काष्ठा adxl372_state *st,
				  अचिन्हित दीर्घ पूर्णांक1_biपंचांगask,
				  अचिन्हित दीर्घ पूर्णांक2_biपंचांगask)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(st->regmap, ADXL372_INT1_MAP, पूर्णांक1_biपंचांगask);
	अगर (ret < 0)
		वापस ret;

	वापस regmap_ग_लिखो(st->regmap, ADXL372_INT2_MAP, पूर्णांक2_biपंचांगask);
पूर्ण

अटल पूर्णांक adxl372_configure_fअगरo(काष्ठा adxl372_state *st)
अणु
	अचिन्हित पूर्णांक fअगरo_samples, fअगरo_ctl;
	पूर्णांक ret;

	/* FIFO must be configured जबतक in standby mode */
	ret = adxl372_set_op_mode(st, ADXL372_STANDBY);
	अगर (ret < 0)
		वापस ret;

	/*
	 * watermark stores the number of sets; we need to ग_लिखो the FIFO
	 * रेजिस्टरs with the number of samples
	 */
	fअगरo_samples = (st->watermark * st->fअगरo_set_size);
	fअगरo_ctl = ADXL372_FIFO_CTL_FORMAT_MODE(st->fअगरo_क्रमmat) |
		   ADXL372_FIFO_CTL_MODE_MODE(st->fअगरo_mode) |
		   ADXL372_FIFO_CTL_SAMPLES_MODE(fअगरo_samples);

	ret = regmap_ग_लिखो(st->regmap,
			   ADXL372_FIFO_SAMPLES, fअगरo_samples & 0xFF);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(st->regmap, ADXL372_FIFO_CTL, fअगरo_ctl);
	अगर (ret < 0)
		वापस ret;

	वापस adxl372_set_op_mode(st, ADXL372_FULL_BW_MEASUREMENT);
पूर्ण

अटल पूर्णांक adxl372_get_status(काष्ठा adxl372_state *st,
			      u8 *status1, u8 *status2,
			      u16 *fअगरo_entries)
अणु
	__be32 buf;
	u32 val;
	पूर्णांक ret;

	/* STATUS1, STATUS2, FIFO_ENTRIES2 and FIFO_ENTRIES are adjacent regs */
	ret = regmap_bulk_पढ़ो(st->regmap, ADXL372_STATUS_1,
			       &buf, माप(buf));
	अगर (ret < 0)
		वापस ret;

	val = be32_to_cpu(buf);

	*status1 = (val >> 24) & 0x0F;
	*status2 = (val >> 16) & 0x0F;
	/*
	 * FIFO_ENTRIES contains the least signअगरicant byte, and FIFO_ENTRIES2
	 * contains the two most signअगरicant bits
	 */
	*fअगरo_entries = val & 0x3FF;

	वापस ret;
पूर्ण

अटल व्योम adxl372_arrange_axis_data(काष्ठा adxl372_state *st, __be16 *sample)
अणु
	__be16	axis_sample[3];
	पूर्णांक i = 0;

	स_रखो(axis_sample, 0, 3 * माप(__be16));
	अगर (ADXL372_X_AXIS_EN(st->fअगरo_axis_mask))
		axis_sample[i++] = sample[0];
	अगर (ADXL372_Y_AXIS_EN(st->fअगरo_axis_mask))
		axis_sample[i++] = sample[1];
	अगर (ADXL372_Z_AXIS_EN(st->fअगरo_axis_mask))
		axis_sample[i++] = sample[2];

	स_नकल(sample, axis_sample, 3 * माप(__be16));
पूर्ण

अटल व्योम adxl372_push_event(काष्ठा iio_dev *indio_dev, s64 बारtamp, u8 status2)
अणु
	अचिन्हित पूर्णांक ev_dir = IIO_EV_सूची_NONE;

	अगर (ADXL372_STATUS_2_ACT(status2))
		ev_dir = IIO_EV_सूची_RISING;

	अगर (ADXL372_STATUS_2_INACT(status2))
		ev_dir = IIO_EV_सूची_FALLING;

	अगर (ev_dir != IIO_EV_सूची_NONE)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEL, 0, IIO_MOD_X_OR_Y_OR_Z,
						  IIO_EV_TYPE_THRESH, ev_dir),
			       बारtamp);
पूर्ण

अटल irqवापस_t adxl372_trigger_handler(पूर्णांक irq, व्योम  *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा adxl372_state *st = iio_priv(indio_dev);
	u8 status1, status2;
	u16 fअगरo_entries;
	पूर्णांक i, ret;

	ret = adxl372_get_status(st, &status1, &status2, &fअगरo_entries);
	अगर (ret < 0)
		जाओ err;

	adxl372_push_event(indio_dev, iio_get_समय_ns(indio_dev), status2);

	अगर (st->fअगरo_mode != ADXL372_FIFO_BYPASSED &&
	    ADXL372_STATUS_1_FIFO_FULL(status1)) अणु
		/*
		 * When पढ़ोing data from multiple axes from the FIFO,
		 * to ensure that data is not overwritten and stored out
		 * of order at least one sample set must be left in the
		 * FIFO after every पढ़ो.
		 */
		fअगरo_entries -= st->fअगरo_set_size;

		/* Read data from the FIFO */
		ret = regmap_noinc_पढ़ो(st->regmap, ADXL372_FIFO_DATA,
					st->fअगरo_buf,
					fअगरo_entries * माप(u16));
		अगर (ret < 0)
			जाओ err;

		/* Each sample is 2 bytes */
		क्रम (i = 0; i < fअगरo_entries; i += st->fअगरo_set_size) अणु
			/* filter peak detection data */
			अगर (st->peak_fअगरo_mode_en)
				adxl372_arrange_axis_data(st, &st->fअगरo_buf[i]);
			iio_push_to_buffers(indio_dev, &st->fअगरo_buf[i]);
		पूर्ण
	पूर्ण
err:
	iio_trigger_notअगरy_करोne(indio_dev->trig);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक adxl372_setup(काष्ठा adxl372_state *st)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(st->regmap, ADXL372_DEVID, &regval);
	अगर (ret < 0)
		वापस ret;

	अगर (regval != ADXL372_DEVID_VAL) अणु
		dev_err(st->dev, "Invalid chip id %x\n", regval);
		वापस -ENODEV;
	पूर्ण

	/*
	 * Perक्रमm a software reset to make sure the device is in a consistent
	 * state after start up.
	 */
	ret = regmap_ग_लिखो(st->regmap, ADXL372_RESET, ADXL372_RESET_CODE);
	अगर (ret < 0)
		वापस ret;

	ret = adxl372_set_op_mode(st, ADXL372_STANDBY);
	अगर (ret < 0)
		वापस ret;

	/* Set threshold क्रम activity detection to 1g */
	ret = adxl372_set_activity_threshold(st, ADXL372_ACTIVITY,
					     true, true, 1000);
	अगर (ret < 0)
		वापस ret;

	/* Set threshold क्रम inactivity detection to 100mg */
	ret = adxl372_set_activity_threshold(st, ADXL372_INACTIVITY,
					     true, true, 100);
	अगर (ret < 0)
		वापस ret;

	/* Set activity processing in Looped mode */
	ret = adxl372_set_act_proc_mode(st, ADXL372_LOOPED);
	अगर (ret < 0)
		वापस ret;

	ret = adxl372_set_odr(st, ADXL372_ODR_6400HZ);
	अगर (ret < 0)
		वापस ret;

	ret = adxl372_set_bandwidth(st, ADXL372_BW_3200HZ);
	अगर (ret < 0)
		वापस ret;

	/* Set activity समयr to 1ms */
	ret = adxl372_set_activity_समय_ms(st, 1);
	अगर (ret < 0)
		वापस ret;

	/* Set inactivity समयr to 10s */
	ret = adxl372_set_inactivity_समय_ms(st, 10000);
	अगर (ret < 0)
		वापस ret;

	/* Set the mode of operation to full bandwidth measurement mode */
	वापस adxl372_set_op_mode(st, ADXL372_FULL_BW_MEASUREMENT);
पूर्ण

अटल पूर्णांक adxl372_reg_access(काष्ठा iio_dev *indio_dev,
			      अचिन्हित पूर्णांक reg,
			      अचिन्हित पूर्णांक ग_लिखोval,
			      अचिन्हित पूर्णांक *पढ़ोval)
अणु
	काष्ठा adxl372_state *st = iio_priv(indio_dev);

	अगर (पढ़ोval)
		वापस regmap_पढ़ो(st->regmap, reg, पढ़ोval);
	अन्यथा
		वापस regmap_ग_लिखो(st->regmap, reg, ग_लिखोval);
पूर्ण

अटल पूर्णांक adxl372_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ info)
अणु
	काष्ठा adxl372_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		ret = adxl372_पढ़ो_axis(st, chan->address);
		iio_device_release_direct_mode(indio_dev);
		अगर (ret < 0)
			वापस ret;

		*val = sign_extend32(ret >> chan->scan_type.shअगरt,
				     chan->scan_type.realbits - 1);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = ADXL372_USCALE;
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = adxl372_samp_freq_tbl[st->odr];
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		*val = adxl372_bw_freq_tbl[st->bw];
		वापस IIO_VAL_INT;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक adxl372_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ info)
अणु
	काष्ठा adxl372_state *st = iio_priv(indio_dev);
	पूर्णांक odr_index, bw_index, ret;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		odr_index = adxl372_find_बंदst_match(adxl372_samp_freq_tbl,
					ARRAY_SIZE(adxl372_samp_freq_tbl),
					val);
		ret = adxl372_set_odr(st, odr_index);
		अगर (ret < 0)
			वापस ret;
		/*
		 * The समयr period depends on the ODR selected.
		 * At 3200 Hz and below, it is 6.6 ms; at 6400 Hz, it is 3.3 ms
		 */
		ret = adxl372_set_activity_समय_ms(st, st->act_समय_ms);
		अगर (ret < 0)
			वापस ret;
		/*
		 * The समयr period depends on the ODR selected.
		 * At 3200 Hz and below, it is 26 ms; at 6400 Hz, it is 13 ms
		 */
		ret = adxl372_set_inactivity_समय_ms(st, st->inact_समय_ms);
		अगर (ret < 0)
			वापस ret;
		/*
		 * The maximum bandwidth is स्थिरrained to at most half of
		 * the ODR to ensure that the Nyquist criteria is not violated
		 */
		अगर (st->bw > odr_index)
			ret = adxl372_set_bandwidth(st, odr_index);

		वापस ret;
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		bw_index = adxl372_find_बंदst_match(adxl372_bw_freq_tbl,
					ARRAY_SIZE(adxl372_bw_freq_tbl),
					val);
		वापस adxl372_set_bandwidth(st, bw_index);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक adxl372_पढ़ो_event_value(काष्ठा iio_dev *indio_dev, स्थिर काष्ठा iio_chan_spec *chan,
				    क्रमागत iio_event_type type, क्रमागत iio_event_direction dir,
				    क्रमागत iio_event_info info, पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा adxl372_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक addr;
	u16 raw_value;
	पूर्णांक ret;

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		चयन (dir) अणु
		हाल IIO_EV_सूची_RISING:
			addr = ADXL372_X_THRESH_ACT_H + 2 * chan->scan_index;
			ret = adxl372_पढ़ो_threshold_value(indio_dev, addr, &raw_value);
			अगर (ret < 0)
				वापस ret;
			*val = raw_value * ADXL372_USCALE;
			*val2 = 1000000;
			वापस IIO_VAL_FRACTIONAL;
		हाल IIO_EV_सूची_FALLING:
			addr = ADXL372_X_THRESH_INACT_H + 2 * chan->scan_index;
			ret =  adxl372_पढ़ो_threshold_value(indio_dev, addr, &raw_value);
			अगर (ret < 0)
				वापस ret;
			*val = raw_value * ADXL372_USCALE;
			*val2 = 1000000;
			वापस IIO_VAL_FRACTIONAL;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_EV_INFO_PERIOD:
		चयन (dir) अणु
		हाल IIO_EV_सूची_RISING:
			*val = st->act_समय_ms;
			*val2 = 1000;
			वापस IIO_VAL_FRACTIONAL;
		हाल IIO_EV_सूची_FALLING:
			*val = st->inact_समय_ms;
			*val2 = 1000;
			वापस IIO_VAL_FRACTIONAL;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक adxl372_ग_लिखो_event_value(काष्ठा iio_dev *indio_dev, स्थिर काष्ठा iio_chan_spec *chan,
				     क्रमागत iio_event_type type, क्रमागत iio_event_direction dir,
				     क्रमागत iio_event_info info, पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा adxl372_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक val_ms;
	अचिन्हित पूर्णांक addr;
	u16 raw_val;

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		raw_val = DIV_ROUND_UP(val * 1000000, ADXL372_USCALE);
		चयन (dir) अणु
		हाल IIO_EV_सूची_RISING:
			addr = ADXL372_X_THRESH_ACT_H + 2 * chan->scan_index;
			वापस adxl372_ग_लिखो_threshold_value(indio_dev, addr, raw_val);
		हाल IIO_EV_सूची_FALLING:
			addr = ADXL372_X_THRESH_INACT_H + 2 * chan->scan_index;
			वापस adxl372_ग_लिखो_threshold_value(indio_dev, addr, raw_val);
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_EV_INFO_PERIOD:
		val_ms = val * 1000 + DIV_ROUND_UP(val2, 1000);
		चयन (dir) अणु
		हाल IIO_EV_सूची_RISING:
			वापस adxl372_set_activity_समय_ms(st, val_ms);
		हाल IIO_EV_सूची_FALLING:
			वापस adxl372_set_inactivity_समय_ms(st, val_ms);
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक adxl372_पढ़ो_event_config(काष्ठा iio_dev *indio_dev, स्थिर काष्ठा iio_chan_spec *chan,
				     क्रमागत iio_event_type type, क्रमागत iio_event_direction dir)
अणु
	काष्ठा adxl372_state *st = iio_priv(indio_dev);

	चयन (dir) अणु
	हाल IIO_EV_सूची_RISING:
		वापस FIELD_GET(ADXL372_INT1_MAP_ACT_MSK, st->पूर्णांक1_biपंचांगask);
	हाल IIO_EV_सूची_FALLING:
		वापस FIELD_GET(ADXL372_INT1_MAP_INACT_MSK, st->पूर्णांक1_biपंचांगask);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक adxl372_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev, स्थिर काष्ठा iio_chan_spec *chan,
				      क्रमागत iio_event_type type, क्रमागत iio_event_direction dir,
				      पूर्णांक state)
अणु
	काष्ठा adxl372_state *st = iio_priv(indio_dev);

	चयन (dir) अणु
	हाल IIO_EV_सूची_RISING:
		set_mask_bits(&st->पूर्णांक1_biपंचांगask, ADXL372_INT1_MAP_ACT_MSK,
			      ADXL372_INT1_MAP_ACT_MODE(state));
		अवरोध;
	हाल IIO_EV_सूची_FALLING:
		set_mask_bits(&st->पूर्णांक1_biपंचांगask, ADXL372_INT1_MAP_INACT_MSK,
			      ADXL372_INT1_MAP_INACT_MODE(state));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस adxl372_set_पूर्णांकerrupts(st, st->पूर्णांक1_biपंचांगask, 0);
पूर्ण

अटल sमाप_प्रकार adxl372_show_filter_freq_avail(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा adxl372_state *st = iio_priv(indio_dev);
	पूर्णांक i;
	माप_प्रकार len = 0;

	क्रम (i = 0; i <= st->odr; i++)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len,
				 "%d ", adxl372_bw_freq_tbl[i]);

	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल sमाप_प्रकार adxl372_get_fअगरo_enabled(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा adxl372_state *st = iio_priv(indio_dev);

	वापस प्र_लिखो(buf, "%d\n", st->fअगरo_mode);
पूर्ण

अटल sमाप_प्रकार adxl372_get_fअगरo_watermark(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा adxl372_state *st = iio_priv(indio_dev);

	वापस प्र_लिखो(buf, "%d\n", st->watermark);
पूर्ण

अटल IIO_CONST_ATTR(hwfअगरo_watermark_min, "1");
अटल IIO_CONST_ATTR(hwfअगरo_watermark_max,
		      __stringअगरy(ADXL372_FIFO_SIZE));
अटल IIO_DEVICE_ATTR(hwfअगरo_watermark, 0444,
		       adxl372_get_fअगरo_watermark, शून्य, 0);
अटल IIO_DEVICE_ATTR(hwfअगरo_enabled, 0444,
		       adxl372_get_fअगरo_enabled, शून्य, 0);

अटल स्थिर काष्ठा attribute *adxl372_fअगरo_attributes[] = अणु
	&iio_स्थिर_attr_hwfअगरo_watermark_min.dev_attr.attr,
	&iio_स्थिर_attr_hwfअगरo_watermark_max.dev_attr.attr,
	&iio_dev_attr_hwfअगरo_watermark.dev_attr.attr,
	&iio_dev_attr_hwfअगरo_enabled.dev_attr.attr,
	शून्य,
पूर्ण;

अटल पूर्णांक adxl372_set_watermark(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक val)
अणु
	काष्ठा adxl372_state *st  = iio_priv(indio_dev);

	अगर (val > ADXL372_FIFO_SIZE)
		val = ADXL372_FIFO_SIZE;

	st->watermark = val;

	वापस 0;
पूर्ण

अटल पूर्णांक adxl372_buffer_postenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा adxl372_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक mask;
	पूर्णांक i, ret;

	st->पूर्णांक1_biपंचांगask |= ADXL372_INT1_MAP_FIFO_FULL_MSK;
	ret = adxl372_set_पूर्णांकerrupts(st, st->पूर्णांक1_biपंचांगask, 0);
	अगर (ret < 0)
		वापस ret;

	mask = *indio_dev->active_scan_mask;

	क्रम (i = 0; i < ARRAY_SIZE(adxl372_axis_lookup_table); i++) अणु
		अगर (mask == adxl372_axis_lookup_table[i].bits)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(adxl372_axis_lookup_table))
		वापस -EINVAL;

	st->fअगरo_क्रमmat = adxl372_axis_lookup_table[i].fअगरo_क्रमmat;
	st->fअगरo_axis_mask = adxl372_axis_lookup_table[i].bits;
	st->fअगरo_set_size = biपंचांगap_weight(indio_dev->active_scan_mask,
					  indio_dev->masklength);

	/* Configure the FIFO to store sets of impact event peak. */
	अगर (st->peak_fअगरo_mode_en) अणु
		st->fअगरo_set_size = 3;
		st->fअगरo_क्रमmat = ADXL372_XYZ_PEAK_FIFO;
	पूर्ण

	/*
	 * The 512 FIFO samples can be allotted in several ways, such as:
	 * 170 sample sets of concurrent 3-axis data
	 * 256 sample sets of concurrent 2-axis data (user selectable)
	 * 512 sample sets of single-axis data
	 * 170 sets of impact event peak (x, y, z)
	 */
	अगर ((st->watermark * st->fअगरo_set_size) > ADXL372_FIFO_SIZE)
		st->watermark = (ADXL372_FIFO_SIZE  / st->fअगरo_set_size);

	st->fअगरo_mode = ADXL372_FIFO_STREAMED;

	ret = adxl372_configure_fअगरo(st);
	अगर (ret < 0) अणु
		st->fअगरo_mode = ADXL372_FIFO_BYPASSED;
		st->पूर्णांक1_biपंचांगask &= ~ADXL372_INT1_MAP_FIFO_FULL_MSK;
		adxl372_set_पूर्णांकerrupts(st, st->पूर्णांक1_biपंचांगask, 0);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adxl372_buffer_predisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा adxl372_state *st = iio_priv(indio_dev);

	st->पूर्णांक1_biपंचांगask &= ~ADXL372_INT1_MAP_FIFO_FULL_MSK;
	adxl372_set_पूर्णांकerrupts(st, st->पूर्णांक1_biपंचांगask, 0);
	st->fअगरo_mode = ADXL372_FIFO_BYPASSED;
	adxl372_configure_fअगरo(st);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops adxl372_buffer_ops = अणु
	.postenable = adxl372_buffer_postenable,
	.predisable = adxl372_buffer_predisable,
पूर्ण;

अटल पूर्णांक adxl372_dपढ़ोy_trig_set_state(काष्ठा iio_trigger *trig,
					 bool state)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा adxl372_state *st = iio_priv(indio_dev);

	अगर (state)
		st->पूर्णांक1_biपंचांगask |= ADXL372_INT1_MAP_FIFO_FULL_MSK;

	वापस adxl372_set_पूर्णांकerrupts(st, st->पूर्णांक1_biपंचांगask, 0);
पूर्ण

अटल पूर्णांक adxl372_validate_trigger(काष्ठा iio_dev *indio_dev,
				    काष्ठा iio_trigger *trig)
अणु
	काष्ठा adxl372_state *st = iio_priv(indio_dev);

	अगर (st->dपढ़ोy_trig != trig && st->peak_datardy_trig != trig)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops adxl372_trigger_ops = अणु
	.validate_device = &iio_trigger_validate_own_device,
	.set_trigger_state = adxl372_dपढ़ोy_trig_set_state,
पूर्ण;

अटल पूर्णांक adxl372_peak_dपढ़ोy_trig_set_state(काष्ठा iio_trigger *trig,
					      bool state)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा adxl372_state *st = iio_priv(indio_dev);

	अगर (state)
		st->पूर्णांक1_biपंचांगask |= ADXL372_INT1_MAP_FIFO_FULL_MSK;

	st->peak_fअगरo_mode_en = state;

	वापस adxl372_set_पूर्णांकerrupts(st, st->पूर्णांक1_biपंचांगask, 0);
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops adxl372_peak_data_trigger_ops = अणु
	.validate_device = &iio_trigger_validate_own_device,
	.set_trigger_state = adxl372_peak_dपढ़ोy_trig_set_state,
पूर्ण;

अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL("400 800 1600 3200 6400");
अटल IIO_DEVICE_ATTR(in_accel_filter_low_pass_3db_frequency_available,
		       0444, adxl372_show_filter_freq_avail, शून्य, 0);

अटल काष्ठा attribute *adxl372_attributes[] = अणु
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	&iio_dev_attr_in_accel_filter_low_pass_3db_frequency_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group adxl372_attrs_group = अणु
	.attrs = adxl372_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info adxl372_info = अणु
	.validate_trigger = &adxl372_validate_trigger,
	.attrs = &adxl372_attrs_group,
	.पढ़ो_raw = adxl372_पढ़ो_raw,
	.ग_लिखो_raw = adxl372_ग_लिखो_raw,
	.पढ़ो_event_config = adxl372_पढ़ो_event_config,
	.ग_लिखो_event_config = adxl372_ग_लिखो_event_config,
	.पढ़ो_event_value = adxl372_पढ़ो_event_value,
	.ग_लिखो_event_value = adxl372_ग_लिखो_event_value,
	.debugfs_reg_access = &adxl372_reg_access,
	.hwfअगरo_set_watermark = adxl372_set_watermark,
पूर्ण;

bool adxl372_पढ़ोable_noinc_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस (reg == ADXL372_FIFO_DATA);
पूर्ण
EXPORT_SYMBOL_GPL(adxl372_पढ़ोable_noinc_reg);

पूर्णांक adxl372_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
		  पूर्णांक irq, स्थिर अक्षर *name)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा adxl372_state *st;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	dev_set_drvdata(dev, indio_dev);

	st->dev = dev;
	st->regmap = regmap;
	st->irq = irq;

	mutex_init(&st->threshold_m);

	indio_dev->channels = adxl372_channels;
	indio_dev->num_channels = ARRAY_SIZE(adxl372_channels);
	indio_dev->available_scan_masks = adxl372_channel_masks;
	indio_dev->name = name;
	indio_dev->info = &adxl372_info;
	indio_dev->modes = INDIO_सूचीECT_MODE | INDIO_BUFFER_SOFTWARE;

	ret = adxl372_setup(st);
	अगर (ret < 0) अणु
		dev_err(dev, "ADXL372 setup failed\n");
		वापस ret;
	पूर्ण

	ret = devm_iio_triggered_buffer_setup_ext(dev,
						  indio_dev, शून्य,
						  adxl372_trigger_handler,
						  &adxl372_buffer_ops,
						  adxl372_fअगरo_attributes);
	अगर (ret < 0)
		वापस ret;

	अगर (st->irq) अणु
		st->dपढ़ोy_trig = devm_iio_trigger_alloc(dev,
							 "%s-dev%d",
							 indio_dev->name,
							 indio_dev->id);
		अगर (st->dपढ़ोy_trig == शून्य)
			वापस -ENOMEM;

		st->peak_datardy_trig = devm_iio_trigger_alloc(dev,
							       "%s-dev%d-peak",
							       indio_dev->name,
							       indio_dev->id);
		अगर (!st->peak_datardy_trig)
			वापस -ENOMEM;

		st->dपढ़ोy_trig->ops = &adxl372_trigger_ops;
		st->peak_datardy_trig->ops = &adxl372_peak_data_trigger_ops;
		iio_trigger_set_drvdata(st->dपढ़ोy_trig, indio_dev);
		iio_trigger_set_drvdata(st->peak_datardy_trig, indio_dev);
		ret = devm_iio_trigger_रेजिस्टर(dev, st->dपढ़ोy_trig);
		अगर (ret < 0)
			वापस ret;

		ret = devm_iio_trigger_रेजिस्टर(dev, st->peak_datardy_trig);
		अगर (ret < 0)
			वापस ret;

		indio_dev->trig = iio_trigger_get(st->dपढ़ोy_trig);

		ret = devm_request_thपढ़ोed_irq(dev, st->irq,
					iio_trigger_generic_data_rdy_poll,
					शून्य,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					indio_dev->name, st->dपढ़ोy_trig);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण
EXPORT_SYMBOL_GPL(adxl372_probe);

MODULE_AUTHOR("Stefan Popa <stefan.popa@analog.com>");
MODULE_DESCRIPTION("Analog Devices ADXL372 3-axis accelerometer driver");
MODULE_LICENSE("GPL");
