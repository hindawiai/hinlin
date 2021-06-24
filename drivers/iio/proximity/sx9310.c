<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2018 Google LLC.
 *
 * Driver क्रम Semtech's SX9310/SX9311 capacitive proximity/button solution.
 * Based on SX9500 driver and Semtech driver using the input framework
 * <https://my.syncplicity.com/share/teouwsim8niiaud/
 *          linux-driver-SX9310_NoSmartHSensing>.
 * Reworked in April 2019 by Evan Green <evgreen@chromium.org>
 * and in January 2020 by Daniel Campello <campello@chromium.org>.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/pm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>

/* Register definitions. */
#घोषणा SX9310_REG_IRQ_SRC				0x00
#घोषणा SX9310_REG_STAT0				0x01
#घोषणा SX9310_REG_STAT1				0x02
#घोषणा SX9310_REG_STAT1_COMPSTAT_MASK			GENMASK(3, 0)
#घोषणा SX9310_REG_IRQ_MSK				0x03
#घोषणा   SX9310_CONVDONE_IRQ				BIT(3)
#घोषणा   SX9310_FAR_IRQ				BIT(5)
#घोषणा   SX9310_CLOSE_IRQ				BIT(6)
#घोषणा SX9310_REG_IRQ_FUNC				0x04

#घोषणा SX9310_REG_PROX_CTRL0				0x10
#घोषणा   SX9310_REG_PROX_CTRL0_SENSOREN_MASK		GENMASK(3, 0)
#घोषणा   SX9310_REG_PROX_CTRL0_SCANPERIOD_MASK		GENMASK(7, 4)
#घोषणा   SX9310_REG_PROX_CTRL0_SCANPERIOD_15MS		0x01
#घोषणा SX9310_REG_PROX_CTRL1				0x11
#घोषणा SX9310_REG_PROX_CTRL2				0x12
#घोषणा   SX9310_REG_PROX_CTRL2_COMBMODE_MASK		GENMASK(7, 6)
#घोषणा   SX9310_REG_PROX_CTRL2_COMBMODE_CS0_CS1_CS2_CS3 (0x03 << 6)
#घोषणा   SX9310_REG_PROX_CTRL2_COMBMODE_CS1_CS2	(0x02 << 6)
#घोषणा   SX9310_REG_PROX_CTRL2_COMBMODE_CS0_CS1	(0x01 << 6)
#घोषणा   SX9310_REG_PROX_CTRL2_COMBMODE_CS3		(0x00 << 6)
#घोषणा   SX9310_REG_PROX_CTRL2_SHIELDEN_MASK		GENMASK(3, 2)
#घोषणा   SX9310_REG_PROX_CTRL2_SHIELDEN_DYNAMIC	(0x01 << 2)
#घोषणा   SX9310_REG_PROX_CTRL2_SHIELDEN_GROUND		(0x02 << 2)
#घोषणा SX9310_REG_PROX_CTRL3				0x13
#घोषणा   SX9310_REG_PROX_CTRL3_GAIN0_MASK		GENMASK(3, 2)
#घोषणा   SX9310_REG_PROX_CTRL3_GAIN0_X8		(0x03 << 2)
#घोषणा   SX9310_REG_PROX_CTRL3_GAIN12_MASK		GENMASK(1, 0)
#घोषणा   SX9310_REG_PROX_CTRL3_GAIN12_X4		0x02
#घोषणा SX9310_REG_PROX_CTRL4				0x14
#घोषणा   SX9310_REG_PROX_CTRL4_RESOLUTION_MASK		GENMASK(2, 0)
#घोषणा   SX9310_REG_PROX_CTRL4_RESOLUTION_FINEST	0x07
#घोषणा   SX9310_REG_PROX_CTRL4_RESOLUTION_VERY_FINE	0x06
#घोषणा   SX9310_REG_PROX_CTRL4_RESOLUTION_FINE		0x05
#घोषणा   SX9310_REG_PROX_CTRL4_RESOLUTION_MEDIUM	0x04
#घोषणा   SX9310_REG_PROX_CTRL4_RESOLUTION_MEDIUM_COARSE 0x03
#घोषणा   SX9310_REG_PROX_CTRL4_RESOLUTION_COARSE	0x02
#घोषणा   SX9310_REG_PROX_CTRL4_RESOLUTION_VERY_COARSE	0x01
#घोषणा   SX9310_REG_PROX_CTRL4_RESOLUTION_COARSEST	0x00
#घोषणा SX9310_REG_PROX_CTRL5				0x15
#घोषणा   SX9310_REG_PROX_CTRL5_RANGE_SMALL		(0x03 << 6)
#घोषणा   SX9310_REG_PROX_CTRL5_STARTUPSENS_MASK	GENMASK(3, 2)
#घोषणा   SX9310_REG_PROX_CTRL5_STARTUPSENS_CS1		(0x01 << 2)
#घोषणा   SX9310_REG_PROX_CTRL5_RAWFILT_MASK		GENMASK(1, 0)
#घोषणा   SX9310_REG_PROX_CTRL5_RAWFILT_SHIFT		0
#घोषणा   SX9310_REG_PROX_CTRL5_RAWFILT_1P25		0x02
#घोषणा SX9310_REG_PROX_CTRL6				0x16
#घोषणा   SX9310_REG_PROX_CTRL6_AVGTHRESH_DEFAULT	0x20
#घोषणा SX9310_REG_PROX_CTRL7				0x17
#घोषणा   SX9310_REG_PROX_CTRL7_AVGNEGFILT_2		(0x01 << 3)
#घोषणा   SX9310_REG_PROX_CTRL7_AVGPOSFILT_MASK		GENMASK(2, 0)
#घोषणा   SX9310_REG_PROX_CTRL7_AVGPOSFILT_SHIFT	0
#घोषणा   SX9310_REG_PROX_CTRL7_AVGPOSFILT_512		0x05
#घोषणा SX9310_REG_PROX_CTRL8				0x18
#घोषणा   SX9310_REG_PROX_CTRL8_9_PTHRESH_MASK		GENMASK(7, 3)
#घोषणा SX9310_REG_PROX_CTRL9				0x19
#घोषणा   SX9310_REG_PROX_CTRL8_9_PTHRESH_28		(0x08 << 3)
#घोषणा   SX9310_REG_PROX_CTRL8_9_PTHRESH_96		(0x11 << 3)
#घोषणा   SX9310_REG_PROX_CTRL8_9_BODYTHRESH_900	0x03
#घोषणा   SX9310_REG_PROX_CTRL8_9_BODYTHRESH_1500	0x05
#घोषणा SX9310_REG_PROX_CTRL10				0x1a
#घोषणा   SX9310_REG_PROX_CTRL10_HYST_MASK		GENMASK(5, 4)
#घोषणा   SX9310_REG_PROX_CTRL10_HYST_6PCT		(0x01 << 4)
#घोषणा   SX9310_REG_PROX_CTRL10_CLOSE_DEBOUNCE_MASK	GENMASK(3, 2)
#घोषणा   SX9310_REG_PROX_CTRL10_FAR_DEBOUNCE_MASK	GENMASK(1, 0)
#घोषणा   SX9310_REG_PROX_CTRL10_FAR_DEBOUNCE_2		0x01
#घोषणा SX9310_REG_PROX_CTRL11				0x1b
#घोषणा SX9310_REG_PROX_CTRL12				0x1c
#घोषणा SX9310_REG_PROX_CTRL13				0x1d
#घोषणा SX9310_REG_PROX_CTRL14				0x1e
#घोषणा SX9310_REG_PROX_CTRL15				0x1f
#घोषणा SX9310_REG_PROX_CTRL16				0x20
#घोषणा SX9310_REG_PROX_CTRL17				0x21
#घोषणा SX9310_REG_PROX_CTRL18				0x22
#घोषणा SX9310_REG_PROX_CTRL19				0x23
#घोषणा SX9310_REG_SAR_CTRL0				0x2a
#घोषणा   SX9310_REG_SAR_CTRL0_SARDEB_4_SAMPLES		(0x02 << 5)
#घोषणा   SX9310_REG_SAR_CTRL0_SARHYST_8		(0x02 << 3)
#घोषणा SX9310_REG_SAR_CTRL1				0x2b
/* Each increment of the slope रेजिस्टर is 0.0078125. */
#घोषणा   SX9310_REG_SAR_CTRL1_SLOPE(_hnslope)		(_hnslope / 78125)
#घोषणा SX9310_REG_SAR_CTRL2				0x2c
#घोषणा   SX9310_REG_SAR_CTRL2_SAROFFSET_DEFAULT	0x3c

#घोषणा SX9310_REG_SENSOR_SEL				0x30
#घोषणा SX9310_REG_USE_MSB				0x31
#घोषणा SX9310_REG_USE_LSB				0x32
#घोषणा SX9310_REG_AVG_MSB				0x33
#घोषणा SX9310_REG_AVG_LSB				0x34
#घोषणा SX9310_REG_DIFF_MSB				0x35
#घोषणा SX9310_REG_DIFF_LSB				0x36
#घोषणा SX9310_REG_OFFSET_MSB				0x37
#घोषणा SX9310_REG_OFFSET_LSB				0x38
#घोषणा SX9310_REG_SAR_MSB				0x39
#घोषणा SX9310_REG_SAR_LSB				0x3a
#घोषणा SX9310_REG_I2C_ADDR				0x40
#घोषणा SX9310_REG_PAUSE				0x41
#घोषणा SX9310_REG_WHOAMI				0x42
#घोषणा   SX9310_WHOAMI_VALUE				0x01
#घोषणा   SX9311_WHOAMI_VALUE				0x02
#घोषणा SX9310_REG_RESET				0x7f
#घोषणा   SX9310_SOFT_RESET				0xde


/* 4 hardware channels, as defined in STAT0: COMB, CS2, CS1 and CS0. */
#घोषणा SX9310_NUM_CHANNELS				4
अटल_निश्चित(SX9310_NUM_CHANNELS < BITS_PER_LONG);

काष्ठा sx9310_data अणु
	/* Serialize access to रेजिस्टरs and channel configuration */
	काष्ठा mutex mutex;
	काष्ठा i2c_client *client;
	काष्ठा iio_trigger *trig;
	काष्ठा regmap *regmap;
	काष्ठा regulator_bulk_data supplies[2];
	/*
	 * Last पढ़ोing of the proximity status क्रम each channel.
	 * We only send an event to user space when this changes.
	 */
	अचिन्हित दीर्घ chan_prox_stat;
	bool trigger_enabled;
	/* Ensure correct alignment of बारtamp when present. */
	काष्ठा अणु
		__be16 channels[SX9310_NUM_CHANNELS];
		s64 ts __aligned(8);
	पूर्ण buffer;
	/* Remember enabled channels and sample rate during suspend. */
	अचिन्हित पूर्णांक suspend_ctrl0;
	काष्ठा completion completion;
	अचिन्हित दीर्घ chan_पढ़ो;
	अचिन्हित दीर्घ chan_event;
	अचिन्हित पूर्णांक whoami;
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec sx9310_events[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_shared_by_all = BIT(IIO_EV_INFO_PERIOD),
	पूर्ण,
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_shared_by_all = BIT(IIO_EV_INFO_PERIOD),
	पूर्ण,
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_EITHER,
		.mask_separate = BIT(IIO_EV_INFO_ENABLE) |
				 BIT(IIO_EV_INFO_HYSTERESIS) |
				 BIT(IIO_EV_INFO_VALUE),
	पूर्ण,
पूर्ण;

#घोषणा SX9310_NAMED_CHANNEL(idx, name)					 \
	अणु								 \
		.type = IIO_PROXIMITY,					 \
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |		 \
				      BIT(IIO_CHAN_INFO_HARDWAREGAIN),   \
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
		.info_mask_separate_available =				 \
			BIT(IIO_CHAN_INFO_HARDWAREGAIN),		 \
		.indexed = 1,						 \
		.channel = idx,						 \
		.extend_name = name,					 \
		.address = SX9310_REG_DIFF_MSB,				 \
		.event_spec = sx9310_events,				 \
		.num_event_specs = ARRAY_SIZE(sx9310_events),		 \
		.scan_index = idx,					 \
		.scan_type = अणु						 \
			.sign = 's',					 \
			.realbits = 12,					 \
			.storagebits = 16,				 \
			.endianness = IIO_BE,				 \
		पूर्ण,							 \
	पूर्ण
#घोषणा SX9310_CHANNEL(idx) SX9310_NAMED_CHANNEL(idx, शून्य)

अटल स्थिर काष्ठा iio_chan_spec sx9310_channels[] = अणु
	SX9310_CHANNEL(0),			/* CS0 */
	SX9310_CHANNEL(1),			/* CS1 */
	SX9310_CHANNEL(2),			/* CS2 */
	SX9310_NAMED_CHANNEL(3, "comb"),	/* COMB */

	IIO_CHAN_SOFT_TIMESTAMP(4),
पूर्ण;

/*
 * Each entry contains the पूर्णांकeger part (val) and the fractional part, in micro
 * seconds. It conक्रमms to the IIO output IIO_VAL_INT_PLUS_MICRO.
 */
अटल स्थिर काष्ठा अणु
	पूर्णांक val;
	पूर्णांक val2;
पूर्ण sx9310_samp_freq_table[] = अणु
	अणु 500, 0 पूर्ण, /* 0000: Min (no idle समय) */
	अणु 66, 666666 पूर्ण, /* 0001: 15 ms */
	अणु 33, 333333 पूर्ण, /* 0010: 30 ms (Typ.) */
	अणु 22, 222222 पूर्ण, /* 0011: 45 ms */
	अणु 16, 666666 पूर्ण, /* 0100: 60 ms */
	अणु 11, 111111 पूर्ण, /* 0101: 90 ms */
	अणु 8, 333333 पूर्ण, /* 0110: 120 ms */
	अणु 5, 0 पूर्ण, /* 0111: 200 ms */
	अणु 2, 500000 पूर्ण, /* 1000: 400 ms */
	अणु 1, 666666 पूर्ण, /* 1001: 600 ms */
	अणु 1, 250000 पूर्ण, /* 1010: 800 ms */
	अणु 1, 0 पूर्ण, /* 1011: 1 s */
	अणु 0, 500000 पूर्ण, /* 1100: 2 s */
	अणु 0, 333333 पूर्ण, /* 1101: 3 s */
	अणु 0, 250000 पूर्ण, /* 1110: 4 s */
	अणु 0, 200000 पूर्ण, /* 1111: 5 s */
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sx9310_scan_period_table[] = अणु
	2,   15,  30,  45,   60,   90,	 120,  200,
	400, 600, 800, 1000, 2000, 3000, 4000, 5000,
पूर्ण;

अटल sमाप_प्रकार sx9310_show_samp_freq_avail(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	माप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sx9310_samp_freq_table); i++)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%d.%d ",
				 sx9310_samp_freq_table[i].val,
				 sx9310_samp_freq_table[i].val2);
	buf[len - 1] = '\n';
	वापस len;
पूर्ण
अटल IIO_DEV_ATTR_SAMP_FREQ_AVAIL(sx9310_show_samp_freq_avail);

अटल स्थिर काष्ठा regmap_range sx9310_writable_reg_ranges[] = अणु
	regmap_reg_range(SX9310_REG_IRQ_MSK, SX9310_REG_IRQ_FUNC),
	regmap_reg_range(SX9310_REG_PROX_CTRL0, SX9310_REG_PROX_CTRL19),
	regmap_reg_range(SX9310_REG_SAR_CTRL0, SX9310_REG_SAR_CTRL2),
	regmap_reg_range(SX9310_REG_SENSOR_SEL, SX9310_REG_SENSOR_SEL),
	regmap_reg_range(SX9310_REG_OFFSET_MSB, SX9310_REG_OFFSET_LSB),
	regmap_reg_range(SX9310_REG_PAUSE, SX9310_REG_PAUSE),
	regmap_reg_range(SX9310_REG_RESET, SX9310_REG_RESET),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table sx9310_ग_लिखोable_regs = अणु
	.yes_ranges = sx9310_writable_reg_ranges,
	.n_yes_ranges = ARRAY_SIZE(sx9310_writable_reg_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range sx9310_पढ़ोable_reg_ranges[] = अणु
	regmap_reg_range(SX9310_REG_IRQ_SRC, SX9310_REG_IRQ_FUNC),
	regmap_reg_range(SX9310_REG_PROX_CTRL0, SX9310_REG_PROX_CTRL19),
	regmap_reg_range(SX9310_REG_SAR_CTRL0, SX9310_REG_SAR_CTRL2),
	regmap_reg_range(SX9310_REG_SENSOR_SEL, SX9310_REG_SAR_LSB),
	regmap_reg_range(SX9310_REG_I2C_ADDR, SX9310_REG_WHOAMI),
	regmap_reg_range(SX9310_REG_RESET, SX9310_REG_RESET),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table sx9310_पढ़ोable_regs = अणु
	.yes_ranges = sx9310_पढ़ोable_reg_ranges,
	.n_yes_ranges = ARRAY_SIZE(sx9310_पढ़ोable_reg_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range sx9310_अस्थिर_reg_ranges[] = अणु
	regmap_reg_range(SX9310_REG_IRQ_SRC, SX9310_REG_STAT1),
	regmap_reg_range(SX9310_REG_USE_MSB, SX9310_REG_DIFF_LSB),
	regmap_reg_range(SX9310_REG_SAR_MSB, SX9310_REG_SAR_LSB),
	regmap_reg_range(SX9310_REG_RESET, SX9310_REG_RESET),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table sx9310_अस्थिर_regs = अणु
	.yes_ranges = sx9310_अस्थिर_reg_ranges,
	.n_yes_ranges = ARRAY_SIZE(sx9310_अस्थिर_reg_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config sx9310_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = SX9310_REG_RESET,
	.cache_type = REGCACHE_RBTREE,

	.wr_table = &sx9310_ग_लिखोable_regs,
	.rd_table = &sx9310_पढ़ोable_regs,
	.अस्थिर_table = &sx9310_अस्थिर_regs,
पूर्ण;

अटल पूर्णांक sx9310_update_chan_en(काष्ठा sx9310_data *data,
				 अचिन्हित दीर्घ chan_पढ़ो,
				 अचिन्हित दीर्घ chan_event)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ channels = chan_पढ़ो | chan_event;

	अगर ((data->chan_पढ़ो | data->chan_event) != channels) अणु
		ret = regmap_update_bits(data->regmap, SX9310_REG_PROX_CTRL0,
					 SX9310_REG_PROX_CTRL0_SENSOREN_MASK,
					 channels);
		अगर (ret)
			वापस ret;
	पूर्ण
	data->chan_पढ़ो = chan_पढ़ो;
	data->chan_event = chan_event;
	वापस 0;
पूर्ण

अटल पूर्णांक sx9310_get_पढ़ो_channel(काष्ठा sx9310_data *data, पूर्णांक channel)
अणु
	वापस sx9310_update_chan_en(data, data->chan_पढ़ो | BIT(channel),
				     data->chan_event);
पूर्ण

अटल पूर्णांक sx9310_put_पढ़ो_channel(काष्ठा sx9310_data *data, पूर्णांक channel)
अणु
	वापस sx9310_update_chan_en(data, data->chan_पढ़ो & ~BIT(channel),
				     data->chan_event);
पूर्ण

अटल पूर्णांक sx9310_get_event_channel(काष्ठा sx9310_data *data, पूर्णांक channel)
अणु
	वापस sx9310_update_chan_en(data, data->chan_पढ़ो,
				     data->chan_event | BIT(channel));
पूर्ण

अटल पूर्णांक sx9310_put_event_channel(काष्ठा sx9310_data *data, पूर्णांक channel)
अणु
	वापस sx9310_update_chan_en(data, data->chan_पढ़ो,
				     data->chan_event & ~BIT(channel));
पूर्ण

अटल पूर्णांक sx9310_enable_irq(काष्ठा sx9310_data *data, अचिन्हित पूर्णांक irq)
अणु
	अगर (!data->client->irq)
		वापस 0;
	वापस regmap_update_bits(data->regmap, SX9310_REG_IRQ_MSK, irq, irq);
पूर्ण

अटल पूर्णांक sx9310_disable_irq(काष्ठा sx9310_data *data, अचिन्हित पूर्णांक irq)
अणु
	अगर (!data->client->irq)
		वापस 0;
	वापस regmap_update_bits(data->regmap, SX9310_REG_IRQ_MSK, irq, 0);
पूर्ण

अटल पूर्णांक sx9310_पढ़ो_prox_data(काष्ठा sx9310_data *data,
				 स्थिर काष्ठा iio_chan_spec *chan, __be16 *val)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(data->regmap, SX9310_REG_SENSOR_SEL, chan->channel);
	अगर (ret)
		वापस ret;

	वापस regmap_bulk_पढ़ो(data->regmap, chan->address, val, माप(*val));
पूर्ण

/*
 * If we have no पूर्णांकerrupt support, we have to रुको क्रम a scan period
 * after enabling a channel to get a result.
 */
अटल पूर्णांक sx9310_रुको_क्रम_sample(काष्ठा sx9310_data *data)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(data->regmap, SX9310_REG_PROX_CTRL0, &val);
	अगर (ret)
		वापस ret;

	val = FIELD_GET(SX9310_REG_PROX_CTRL0_SCANPERIOD_MASK, val);

	msleep(sx9310_scan_period_table[val]);

	वापस 0;
पूर्ण

अटल पूर्णांक sx9310_पढ़ो_proximity(काष्ठा sx9310_data *data,
				 स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक *val)
अणु
	पूर्णांक ret;
	__be16 rawval;

	mutex_lock(&data->mutex);

	ret = sx9310_get_पढ़ो_channel(data, chan->channel);
	अगर (ret)
		जाओ out;

	ret = sx9310_enable_irq(data, SX9310_CONVDONE_IRQ);
	अगर (ret)
		जाओ out_put_channel;

	mutex_unlock(&data->mutex);

	अगर (data->client->irq) अणु
		ret = रुको_क्रम_completion_पूर्णांकerruptible(&data->completion);
		reinit_completion(&data->completion);
	पूर्ण अन्यथा अणु
		ret = sx9310_रुको_क्रम_sample(data);
	पूर्ण

	mutex_lock(&data->mutex);

	अगर (ret)
		जाओ out_disable_irq;

	ret = sx9310_पढ़ो_prox_data(data, chan, &rawval);
	अगर (ret)
		जाओ out_disable_irq;

	*val = sign_extend32(be16_to_cpu(rawval),
			     chan->address == SX9310_REG_DIFF_MSB ? 11 : 15);

	ret = sx9310_disable_irq(data, SX9310_CONVDONE_IRQ);
	अगर (ret)
		जाओ out_put_channel;

	ret = sx9310_put_पढ़ो_channel(data, chan->channel);
	अगर (ret)
		जाओ out;

	mutex_unlock(&data->mutex);

	वापस IIO_VAL_INT;

out_disable_irq:
	sx9310_disable_irq(data, SX9310_CONVDONE_IRQ);
out_put_channel:
	sx9310_put_पढ़ो_channel(data, chan->channel);
out:
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक sx9310_पढ़ो_gain(काष्ठा sx9310_data *data,
			    स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक *val)
अणु
	अचिन्हित पूर्णांक regval, gain;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, SX9310_REG_PROX_CTRL3, &regval);
	अगर (ret)
		वापस ret;

	चयन (chan->channel) अणु
	हाल 0:
	हाल 3:
		gain = FIELD_GET(SX9310_REG_PROX_CTRL3_GAIN0_MASK, regval);
		अवरोध;
	हाल 1:
	हाल 2:
		gain = FIELD_GET(SX9310_REG_PROX_CTRL3_GAIN12_MASK, regval);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	*val = 1 << gain;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक sx9310_पढ़ो_samp_freq(काष्ठा sx9310_data *data, पूर्णांक *val, पूर्णांक *val2)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, SX9310_REG_PROX_CTRL0, &regval);
	अगर (ret)
		वापस ret;

	regval = FIELD_GET(SX9310_REG_PROX_CTRL0_SCANPERIOD_MASK, regval);
	*val = sx9310_samp_freq_table[regval].val;
	*val2 = sx9310_samp_freq_table[regval].val2;

	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण

अटल पूर्णांक sx9310_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक *val,
			   पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा sx9310_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (chan->type != IIO_PROXIMITY)
		वापस -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		ret = sx9310_पढ़ो_proximity(data, chan, val);
		iio_device_release_direct_mode(indio_dev);
		वापस ret;
	हाल IIO_CHAN_INFO_HARDWAREGAIN:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		ret = sx9310_पढ़ो_gain(data, chan, val);
		iio_device_release_direct_mode(indio_dev);
		वापस ret;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस sx9310_पढ़ो_samp_freq(data, val, val2);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर पूर्णांक sx9310_gain_vals[] = अणु 1, 2, 4, 8 पूर्ण;

अटल पूर्णांक sx9310_पढ़ो_avail(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length,
			     दीर्घ mask)
अणु
	अगर (chan->type != IIO_PROXIMITY)
		वापस -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_HARDWAREGAIN:
		*type = IIO_VAL_INT;
		*length = ARRAY_SIZE(sx9310_gain_vals);
		*vals = sx9310_gain_vals;
		वापस IIO_AVAIL_LIST;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक sx9310_pthresh_codes[] = अणु
	2, 4, 6, 8, 12, 16, 20, 24, 28, 32, 40, 48, 56, 64, 72, 80, 88, 96, 112,
	128, 144, 160, 192, 224, 256, 320, 384, 512, 640, 768, 1024, 1536
पूर्ण;

अटल पूर्णांक sx9310_get_thresh_reg(अचिन्हित पूर्णांक channel)
अणु
	चयन (channel) अणु
	हाल 0:
	हाल 3:
		वापस SX9310_REG_PROX_CTRL8;
	हाल 1:
	हाल 2:
		वापस SX9310_REG_PROX_CTRL9;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sx9310_पढ़ो_thresh(काष्ठा sx9310_data *data,
			      स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक *val)
अणु
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	reg = ret = sx9310_get_thresh_reg(chan->channel);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(data->regmap, reg, &regval);
	अगर (ret)
		वापस ret;

	regval = FIELD_GET(SX9310_REG_PROX_CTRL8_9_PTHRESH_MASK, regval);
	अगर (regval >= ARRAY_SIZE(sx9310_pthresh_codes))
		वापस -EINVAL;

	*val = sx9310_pthresh_codes[regval];
	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक sx9310_पढ़ो_hysteresis(काष्ठा sx9310_data *data,
				  स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक *val)
अणु
	अचिन्हित पूर्णांक regval, pthresh;
	पूर्णांक ret;

	ret = sx9310_पढ़ो_thresh(data, chan, &pthresh);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(data->regmap, SX9310_REG_PROX_CTRL10, &regval);
	अगर (ret)
		वापस ret;

	regval = FIELD_GET(SX9310_REG_PROX_CTRL10_HYST_MASK, regval);
	अगर (!regval)
		regval = 5;

	/* regval is at most 5 */
	*val = pthresh >> (5 - regval);

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक sx9310_पढ़ो_far_debounce(काष्ठा sx9310_data *data, पूर्णांक *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, SX9310_REG_PROX_CTRL10, &regval);
	अगर (ret)
		वापस ret;

	regval = FIELD_GET(SX9310_REG_PROX_CTRL10_FAR_DEBOUNCE_MASK, regval);
	अगर (regval)
		*val = 1 << regval;
	अन्यथा
		*val = 0;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक sx9310_पढ़ो_बंद_debounce(काष्ठा sx9310_data *data, पूर्णांक *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, SX9310_REG_PROX_CTRL10, &regval);
	अगर (ret)
		वापस ret;

	regval = FIELD_GET(SX9310_REG_PROX_CTRL10_CLOSE_DEBOUNCE_MASK, regval);
	अगर (regval)
		*val = 1 << regval;
	अन्यथा
		*val = 0;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक sx9310_पढ़ो_event_val(काष्ठा iio_dev *indio_dev,
				 स्थिर काष्ठा iio_chan_spec *chan,
				 क्रमागत iio_event_type type,
				 क्रमागत iio_event_direction dir,
				 क्रमागत iio_event_info info, पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा sx9310_data *data = iio_priv(indio_dev);

	अगर (chan->type != IIO_PROXIMITY)
		वापस -EINVAL;

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		वापस sx9310_पढ़ो_thresh(data, chan, val);
	हाल IIO_EV_INFO_PERIOD:
		चयन (dir) अणु
		हाल IIO_EV_सूची_RISING:
			वापस sx9310_पढ़ो_far_debounce(data, val);
		हाल IIO_EV_सूची_FALLING:
			वापस sx9310_पढ़ो_बंद_debounce(data, val);
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_EV_INFO_HYSTERESIS:
		वापस sx9310_पढ़ो_hysteresis(data, chan, val);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक sx9310_ग_लिखो_thresh(काष्ठा sx9310_data *data,
			       स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक val)
अणु
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret, i;

	reg = ret = sx9310_get_thresh_reg(chan->channel);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(sx9310_pthresh_codes); i++) अणु
		अगर (sx9310_pthresh_codes[i] == val) अणु
			regval = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == ARRAY_SIZE(sx9310_pthresh_codes))
		वापस -EINVAL;

	regval = FIELD_PREP(SX9310_REG_PROX_CTRL8_9_PTHRESH_MASK, regval);
	mutex_lock(&data->mutex);
	ret = regmap_update_bits(data->regmap, reg,
				 SX9310_REG_PROX_CTRL8_9_PTHRESH_MASK, regval);
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक sx9310_ग_लिखो_hysteresis(काष्ठा sx9310_data *data,
				   स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक _val)
अणु
	अचिन्हित पूर्णांक hyst, val = _val;
	पूर्णांक ret, pthresh;

	ret = sx9310_पढ़ो_thresh(data, chan, &pthresh);
	अगर (ret < 0)
		वापस ret;

	अगर (val == 0)
		hyst = 0;
	अन्यथा अगर (val == pthresh >> 2)
		hyst = 3;
	अन्यथा अगर (val == pthresh >> 3)
		hyst = 2;
	अन्यथा अगर (val == pthresh >> 4)
		hyst = 1;
	अन्यथा
		वापस -EINVAL;

	hyst = FIELD_PREP(SX9310_REG_PROX_CTRL10_HYST_MASK, hyst);
	mutex_lock(&data->mutex);
	ret = regmap_update_bits(data->regmap, SX9310_REG_PROX_CTRL10,
				 SX9310_REG_PROX_CTRL10_HYST_MASK, hyst);
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक sx9310_ग_लिखो_far_debounce(काष्ठा sx9310_data *data, पूर्णांक val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक regval;

	अगर (val > 0)
		val = ilog2(val);
	अगर (!FIELD_FIT(SX9310_REG_PROX_CTRL10_FAR_DEBOUNCE_MASK, val))
		वापस -EINVAL;

	regval = FIELD_PREP(SX9310_REG_PROX_CTRL10_FAR_DEBOUNCE_MASK, val);

	mutex_lock(&data->mutex);
	ret = regmap_update_bits(data->regmap, SX9310_REG_PROX_CTRL10,
				 SX9310_REG_PROX_CTRL10_FAR_DEBOUNCE_MASK,
				 regval);
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक sx9310_ग_लिखो_बंद_debounce(काष्ठा sx9310_data *data, पूर्णांक val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक regval;

	अगर (val > 0)
		val = ilog2(val);
	अगर (!FIELD_FIT(SX9310_REG_PROX_CTRL10_CLOSE_DEBOUNCE_MASK, val))
		वापस -EINVAL;

	regval = FIELD_PREP(SX9310_REG_PROX_CTRL10_CLOSE_DEBOUNCE_MASK, val);

	mutex_lock(&data->mutex);
	ret = regmap_update_bits(data->regmap, SX9310_REG_PROX_CTRL10,
				 SX9310_REG_PROX_CTRL10_CLOSE_DEBOUNCE_MASK,
				 regval);
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक sx9310_ग_लिखो_event_val(काष्ठा iio_dev *indio_dev,
				  स्थिर काष्ठा iio_chan_spec *chan,
				  क्रमागत iio_event_type type,
				  क्रमागत iio_event_direction dir,
				  क्रमागत iio_event_info info, पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा sx9310_data *data = iio_priv(indio_dev);

	अगर (chan->type != IIO_PROXIMITY)
		वापस -EINVAL;

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		वापस sx9310_ग_लिखो_thresh(data, chan, val);
	हाल IIO_EV_INFO_PERIOD:
		चयन (dir) अणु
		हाल IIO_EV_सूची_RISING:
			वापस sx9310_ग_लिखो_far_debounce(data, val);
		हाल IIO_EV_सूची_FALLING:
			वापस sx9310_ग_लिखो_बंद_debounce(data, val);
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_EV_INFO_HYSTERESIS:
		वापस sx9310_ग_लिखो_hysteresis(data, chan, val);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक sx9310_set_samp_freq(काष्ठा sx9310_data *data, पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(sx9310_samp_freq_table); i++)
		अगर (val == sx9310_samp_freq_table[i].val &&
		    val2 == sx9310_samp_freq_table[i].val2)
			अवरोध;

	अगर (i == ARRAY_SIZE(sx9310_samp_freq_table))
		वापस -EINVAL;

	mutex_lock(&data->mutex);

	ret = regmap_update_bits(
		data->regmap, SX9310_REG_PROX_CTRL0,
		SX9310_REG_PROX_CTRL0_SCANPERIOD_MASK,
		FIELD_PREP(SX9310_REG_PROX_CTRL0_SCANPERIOD_MASK, i));

	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक sx9310_ग_लिखो_gain(काष्ठा sx9310_data *data,
			    स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक val)
अणु
	अचिन्हित पूर्णांक gain, mask;
	पूर्णांक ret;

	gain = ilog2(val);

	चयन (chan->channel) अणु
	हाल 0:
	हाल 3:
		mask = SX9310_REG_PROX_CTRL3_GAIN0_MASK;
		gain = FIELD_PREP(SX9310_REG_PROX_CTRL3_GAIN0_MASK, gain);
		अवरोध;
	हाल 1:
	हाल 2:
		mask = SX9310_REG_PROX_CTRL3_GAIN12_MASK;
		gain = FIELD_PREP(SX9310_REG_PROX_CTRL3_GAIN12_MASK, gain);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&data->mutex);
	ret = regmap_update_bits(data->regmap, SX9310_REG_PROX_CTRL3, mask,
				 gain);
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक sx9310_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक val, पूर्णांक val2,
			    दीर्घ mask)
अणु
	काष्ठा sx9310_data *data = iio_priv(indio_dev);

	अगर (chan->type != IIO_PROXIMITY)
		वापस -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस sx9310_set_samp_freq(data, val, val2);
	हाल IIO_CHAN_INFO_HARDWAREGAIN:
		वापस sx9310_ग_लिखो_gain(data, chan, val);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल irqवापस_t sx9310_irq_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा sx9310_data *data = iio_priv(indio_dev);

	अगर (data->trigger_enabled)
		iio_trigger_poll(data->trig);

	/*
	 * Even अगर no event is enabled, we need to wake the thपढ़ो to clear the
	 * पूर्णांकerrupt state by पढ़ोing SX9310_REG_IRQ_SRC.
	 * It is not possible to करो that here because regmap_पढ़ो takes a mutex.
	 */
	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल व्योम sx9310_push_events(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val, chan;
	काष्ठा sx9310_data *data = iio_priv(indio_dev);
	s64 बारtamp = iio_get_समय_ns(indio_dev);
	अचिन्हित दीर्घ prox_changed;

	/* Read proximity state on all channels */
	ret = regmap_पढ़ो(data->regmap, SX9310_REG_STAT0, &val);
	अगर (ret) अणु
		dev_err(&data->client->dev, "i2c transfer error in irq\n");
		वापस;
	पूर्ण

	/*
	 * Only iterate over channels with changes on proximity status that have
	 * events enabled.
	 */
	prox_changed = (data->chan_prox_stat ^ val) & data->chan_event;

	क्रम_each_set_bit(chan, &prox_changed, SX9310_NUM_CHANNELS) अणु
		पूर्णांक dir;
		u64 ev;

		dir = (val & BIT(chan)) ? IIO_EV_सूची_FALLING : IIO_EV_सूची_RISING;
		ev = IIO_UNMOD_EVENT_CODE(IIO_PROXIMITY, chan,
					  IIO_EV_TYPE_THRESH, dir);

		iio_push_event(indio_dev, ev, बारtamp);
	पूर्ण
	data->chan_prox_stat = val;
पूर्ण

अटल irqवापस_t sx9310_irq_thपढ़ो_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा sx9310_data *data = iio_priv(indio_dev);
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	mutex_lock(&data->mutex);

	ret = regmap_पढ़ो(data->regmap, SX9310_REG_IRQ_SRC, &val);
	अगर (ret) अणु
		dev_err(&data->client->dev, "i2c transfer error in irq\n");
		जाओ out;
	पूर्ण

	अगर (val & (SX9310_FAR_IRQ | SX9310_CLOSE_IRQ))
		sx9310_push_events(indio_dev);

	अगर (val & SX9310_CONVDONE_IRQ)
		complete(&data->completion);

out:
	mutex_unlock(&data->mutex);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sx9310_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा iio_chan_spec *chan,
				    क्रमागत iio_event_type type,
				    क्रमागत iio_event_direction dir)
अणु
	काष्ठा sx9310_data *data = iio_priv(indio_dev);

	वापस !!(data->chan_event & BIT(chan->channel));
पूर्ण

अटल पूर्णांक sx9310_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     क्रमागत iio_event_type type,
				     क्रमागत iio_event_direction dir, पूर्णांक state)
अणु
	काष्ठा sx9310_data *data = iio_priv(indio_dev);
	अचिन्हित पूर्णांक eventirq = SX9310_FAR_IRQ | SX9310_CLOSE_IRQ;
	पूर्णांक ret;

	/* If the state hasn't changed, there's nothing to करो. */
	अगर (!!(data->chan_event & BIT(chan->channel)) == state)
		वापस 0;

	mutex_lock(&data->mutex);
	अगर (state) अणु
		ret = sx9310_get_event_channel(data, chan->channel);
		अगर (ret)
			जाओ out_unlock;
		अगर (!(data->chan_event & ~BIT(chan->channel))) अणु
			ret = sx9310_enable_irq(data, eventirq);
			अगर (ret)
				sx9310_put_event_channel(data, chan->channel);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = sx9310_put_event_channel(data, chan->channel);
		अगर (ret)
			जाओ out_unlock;
		अगर (!data->chan_event) अणु
			ret = sx9310_disable_irq(data, eventirq);
			अगर (ret)
				sx9310_get_event_channel(data, chan->channel);
		पूर्ण
	पूर्ण

out_unlock:
	mutex_unlock(&data->mutex);
	वापस ret;
पूर्ण

अटल काष्ठा attribute *sx9310_attributes[] = अणु
	&iio_dev_attr_sampling_frequency_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group sx9310_attribute_group = अणु
	.attrs = sx9310_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info sx9310_info = अणु
	.attrs = &sx9310_attribute_group,
	.पढ़ो_raw = sx9310_पढ़ो_raw,
	.पढ़ो_avail = sx9310_पढ़ो_avail,
	.पढ़ो_event_value = sx9310_पढ़ो_event_val,
	.ग_लिखो_event_value = sx9310_ग_लिखो_event_val,
	.ग_लिखो_raw = sx9310_ग_लिखो_raw,
	.पढ़ो_event_config = sx9310_पढ़ो_event_config,
	.ग_लिखो_event_config = sx9310_ग_लिखो_event_config,
पूर्ण;

अटल पूर्णांक sx9310_set_trigger_state(काष्ठा iio_trigger *trig, bool state)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा sx9310_data *data = iio_priv(indio_dev);
	पूर्णांक ret = 0;

	mutex_lock(&data->mutex);

	अगर (state)
		ret = sx9310_enable_irq(data, SX9310_CONVDONE_IRQ);
	अन्यथा अगर (!data->chan_पढ़ो)
		ret = sx9310_disable_irq(data, SX9310_CONVDONE_IRQ);
	अगर (ret)
		जाओ out;

	data->trigger_enabled = state;

out:
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops sx9310_trigger_ops = अणु
	.set_trigger_state = sx9310_set_trigger_state,
पूर्ण;

अटल irqवापस_t sx9310_trigger_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_poll_func *pf = निजी;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा sx9310_data *data = iio_priv(indio_dev);
	__be16 val;
	पूर्णांक bit, ret, i = 0;

	mutex_lock(&data->mutex);

	क्रम_each_set_bit(bit, indio_dev->active_scan_mask,
			 indio_dev->masklength) अणु
		ret = sx9310_पढ़ो_prox_data(data, &indio_dev->channels[bit],
					    &val);
		अगर (ret)
			जाओ out;

		data->buffer.channels[i++] = val;
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, &data->buffer,
					   pf->बारtamp);

out:
	mutex_unlock(&data->mutex);

	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sx9310_buffer_preenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sx9310_data *data = iio_priv(indio_dev);
	अचिन्हित दीर्घ channels = 0;
	पूर्णांक bit, ret;

	mutex_lock(&data->mutex);
	क्रम_each_set_bit(bit, indio_dev->active_scan_mask,
			 indio_dev->masklength)
		__set_bit(indio_dev->channels[bit].channel, &channels);

	ret = sx9310_update_chan_en(data, channels, data->chan_event);
	mutex_unlock(&data->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक sx9310_buffer_postdisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sx9310_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = sx9310_update_chan_en(data, 0, data->chan_event);
	mutex_unlock(&data->mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops sx9310_buffer_setup_ops = अणु
	.preenable = sx9310_buffer_preenable,
	.postdisable = sx9310_buffer_postdisable,
पूर्ण;

काष्ठा sx9310_reg_शेष अणु
	u8 reg;
	u8 def;
पूर्ण;

अटल स्थिर काष्ठा sx9310_reg_शेष sx9310_शेष_regs[] = अणु
	अणु SX9310_REG_IRQ_MSK, 0x00 पूर्ण,
	अणु SX9310_REG_IRQ_FUNC, 0x00 पूर्ण,
	/*
	 * The lower 4 bits should not be set as it enable sensors measurements.
	 * Turning the detection on beक्रमe the configuration values are set to
	 * good values can cause the device to वापस erroneous पढ़ोings.
	 */
	अणु SX9310_REG_PROX_CTRL0, SX9310_REG_PROX_CTRL0_SCANPERIOD_15MS पूर्ण,
	अणु SX9310_REG_PROX_CTRL1, 0x00 पूर्ण,
	अणु SX9310_REG_PROX_CTRL2, SX9310_REG_PROX_CTRL2_COMBMODE_CS1_CS2 |
				 SX9310_REG_PROX_CTRL2_SHIELDEN_DYNAMIC पूर्ण,
	अणु SX9310_REG_PROX_CTRL3, SX9310_REG_PROX_CTRL3_GAIN0_X8 |
				 SX9310_REG_PROX_CTRL3_GAIN12_X4 पूर्ण,
	अणु SX9310_REG_PROX_CTRL4, SX9310_REG_PROX_CTRL4_RESOLUTION_FINEST पूर्ण,
	अणु SX9310_REG_PROX_CTRL5, SX9310_REG_PROX_CTRL5_RANGE_SMALL |
				 SX9310_REG_PROX_CTRL5_STARTUPSENS_CS1 |
				 SX9310_REG_PROX_CTRL5_RAWFILT_1P25 पूर्ण,
	अणु SX9310_REG_PROX_CTRL6, SX9310_REG_PROX_CTRL6_AVGTHRESH_DEFAULT पूर्ण,
	अणु SX9310_REG_PROX_CTRL7, SX9310_REG_PROX_CTRL7_AVGNEGFILT_2 |
				 SX9310_REG_PROX_CTRL7_AVGPOSFILT_512 पूर्ण,
	अणु SX9310_REG_PROX_CTRL8, SX9310_REG_PROX_CTRL8_9_PTHRESH_96 |
				 SX9310_REG_PROX_CTRL8_9_BODYTHRESH_1500 पूर्ण,
	अणु SX9310_REG_PROX_CTRL9, SX9310_REG_PROX_CTRL8_9_PTHRESH_28 |
				 SX9310_REG_PROX_CTRL8_9_BODYTHRESH_900 पूर्ण,
	अणु SX9310_REG_PROX_CTRL10, SX9310_REG_PROX_CTRL10_HYST_6PCT |
				  SX9310_REG_PROX_CTRL10_FAR_DEBOUNCE_2 पूर्ण,
	अणु SX9310_REG_PROX_CTRL11, 0x00 पूर्ण,
	अणु SX9310_REG_PROX_CTRL12, 0x00 पूर्ण,
	अणु SX9310_REG_PROX_CTRL13, 0x00 पूर्ण,
	अणु SX9310_REG_PROX_CTRL14, 0x00 पूर्ण,
	अणु SX9310_REG_PROX_CTRL15, 0x00 पूर्ण,
	अणु SX9310_REG_PROX_CTRL16, 0x00 पूर्ण,
	अणु SX9310_REG_PROX_CTRL17, 0x00 पूर्ण,
	अणु SX9310_REG_PROX_CTRL18, 0x00 पूर्ण,
	अणु SX9310_REG_PROX_CTRL19, 0x00 पूर्ण,
	अणु SX9310_REG_SAR_CTRL0, SX9310_REG_SAR_CTRL0_SARDEB_4_SAMPLES |
				SX9310_REG_SAR_CTRL0_SARHYST_8 पूर्ण,
	अणु SX9310_REG_SAR_CTRL1, SX9310_REG_SAR_CTRL1_SLOPE(10781250) पूर्ण,
	अणु SX9310_REG_SAR_CTRL2, SX9310_REG_SAR_CTRL2_SAROFFSET_DEFAULT पूर्ण,
पूर्ण;

/* Activate all channels and perक्रमm an initial compensation. */
अटल पूर्णांक sx9310_init_compensation(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sx9310_data *data = iio_priv(indio_dev);
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक ctrl0;

	ret = regmap_पढ़ो(data->regmap, SX9310_REG_PROX_CTRL0, &ctrl0);
	अगर (ret)
		वापस ret;

	/* run the compensation phase on all channels */
	ret = regmap_ग_लिखो(data->regmap, SX9310_REG_PROX_CTRL0,
			   ctrl0 | SX9310_REG_PROX_CTRL0_SENSOREN_MASK);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो_poll_समयout(data->regmap, SX9310_REG_STAT1, val,
				       !(val & SX9310_REG_STAT1_COMPSTAT_MASK),
				       20000, 2000000);
	अगर (ret) अणु
		अगर (ret == -ETIMEDOUT)
			dev_err(&data->client->dev,
				"initial compensation timed out: 0x%02x\n",
				val);
		वापस ret;
	पूर्ण

	regmap_ग_लिखो(data->regmap, SX9310_REG_PROX_CTRL0, ctrl0);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sx9310_reg_शेष *
sx9310_get_शेष_reg(काष्ठा sx9310_data *data, पूर्णांक idx,
		       काष्ठा sx9310_reg_शेष *reg_def)
अणु
	स्थिर काष्ठा device_node *np = data->client->dev.of_node;
	u32 combined[SX9310_NUM_CHANNELS];
	u32 start = 0, raw = 0, pos = 0;
	अचिन्हित दीर्घ comb_mask = 0;
	पूर्णांक ret, i, count;
	स्थिर अक्षर *res;

	स_नकल(reg_def, &sx9310_शेष_regs[idx], माप(*reg_def));
	अगर (!np)
		वापस reg_def;

	चयन (reg_def->reg) अणु
	हाल SX9310_REG_PROX_CTRL2:
		अगर (of_property_पढ़ो_bool(np, "semtech,cs0-ground")) अणु
			reg_def->def &= ~SX9310_REG_PROX_CTRL2_SHIELDEN_MASK;
			reg_def->def |= SX9310_REG_PROX_CTRL2_SHIELDEN_GROUND;
		पूर्ण

		count = of_property_count_elems_of_size(np, "semtech,combined-sensors",
							माप(u32));
		अगर (count > 0 && count <= ARRAY_SIZE(combined)) अणु
			ret = of_property_पढ़ो_u32_array(np, "semtech,combined-sensors",
							 combined, count);
			अगर (ret)
				अवरोध;
		पूर्ण अन्यथा अणु
			/*
			 * Either the property करोes not exist in the DT or the
			 * number of entries is incorrect.
			 */
			अवरोध;
		पूर्ण
		क्रम (i = 0; i < count; i++) अणु
			अगर (combined[i] >= SX9310_NUM_CHANNELS) अणु
				/* Invalid sensor (invalid DT). */
				अवरोध;
			पूर्ण
			comb_mask |= BIT(combined[i]);
		पूर्ण
		अगर (i < count)
			अवरोध;

		reg_def->def &= ~SX9310_REG_PROX_CTRL2_COMBMODE_MASK;
		अगर (comb_mask == (BIT(3) | BIT(2) | BIT(1) | BIT(0)))
			reg_def->def |= SX9310_REG_PROX_CTRL2_COMBMODE_CS0_CS1_CS2_CS3;
		अन्यथा अगर (comb_mask == (BIT(1) | BIT(2)))
			reg_def->def |= SX9310_REG_PROX_CTRL2_COMBMODE_CS1_CS2;
		अन्यथा अगर (comb_mask == (BIT(0) | BIT(1)))
			reg_def->def |= SX9310_REG_PROX_CTRL2_COMBMODE_CS0_CS1;
		अन्यथा अगर (comb_mask == BIT(3))
			reg_def->def |= SX9310_REG_PROX_CTRL2_COMBMODE_CS3;

		अवरोध;
	हाल SX9310_REG_PROX_CTRL4:
		ret = of_property_पढ़ो_string(np, "semtech,resolution", &res);
		अगर (ret)
			अवरोध;

		reg_def->def &= ~SX9310_REG_PROX_CTRL4_RESOLUTION_MASK;
		अगर (!म_भेद(res, "coarsest"))
			reg_def->def |= SX9310_REG_PROX_CTRL4_RESOLUTION_COARSEST;
		अन्यथा अगर (!म_भेद(res, "very-coarse"))
			reg_def->def |= SX9310_REG_PROX_CTRL4_RESOLUTION_VERY_COARSE;
		अन्यथा अगर (!म_भेद(res, "coarse"))
			reg_def->def |= SX9310_REG_PROX_CTRL4_RESOLUTION_COARSE;
		अन्यथा अगर (!म_भेद(res, "medium-coarse"))
			reg_def->def |= SX9310_REG_PROX_CTRL4_RESOLUTION_MEDIUM_COARSE;
		अन्यथा अगर (!म_भेद(res, "medium"))
			reg_def->def |= SX9310_REG_PROX_CTRL4_RESOLUTION_MEDIUM;
		अन्यथा अगर (!म_भेद(res, "fine"))
			reg_def->def |= SX9310_REG_PROX_CTRL4_RESOLUTION_FINE;
		अन्यथा अगर (!म_भेद(res, "very-fine"))
			reg_def->def |= SX9310_REG_PROX_CTRL4_RESOLUTION_VERY_FINE;
		अन्यथा अगर (!म_भेद(res, "finest"))
			reg_def->def |= SX9310_REG_PROX_CTRL4_RESOLUTION_FINEST;

		अवरोध;
	हाल SX9310_REG_PROX_CTRL5:
		ret = of_property_पढ़ो_u32(np, "semtech,startup-sensor", &start);
		अगर (ret) अणु
			start = FIELD_GET(SX9310_REG_PROX_CTRL5_STARTUPSENS_MASK,
					  reg_def->def);
		पूर्ण

		reg_def->def &= ~SX9310_REG_PROX_CTRL5_STARTUPSENS_MASK;
		reg_def->def |= FIELD_PREP(SX9310_REG_PROX_CTRL5_STARTUPSENS_MASK,
					   start);

		ret = of_property_पढ़ो_u32(np, "semtech,proxraw-strength", &raw);
		अगर (ret) अणु
			raw = FIELD_GET(SX9310_REG_PROX_CTRL5_RAWFILT_MASK,
					reg_def->def);
		पूर्ण अन्यथा अणु
			raw = ilog2(raw);
		पूर्ण

		reg_def->def &= ~SX9310_REG_PROX_CTRL5_RAWFILT_MASK;
		reg_def->def |= FIELD_PREP(SX9310_REG_PROX_CTRL5_RAWFILT_MASK,
					   raw);
		अवरोध;
	हाल SX9310_REG_PROX_CTRL7:
		ret = of_property_पढ़ो_u32(np, "semtech,avg-pos-strength", &pos);
		अगर (ret)
			अवरोध;

		/* Powers of 2, except क्रम a gap between 16 and 64 */
		pos = clamp(ilog2(pos), 3, 11) - (pos >= 32 ? 4 : 3);
		reg_def->def &= ~SX9310_REG_PROX_CTRL7_AVGPOSFILT_MASK;
		reg_def->def |= FIELD_PREP(SX9310_REG_PROX_CTRL7_AVGPOSFILT_MASK,
					   pos);
		अवरोध;
	पूर्ण

	वापस reg_def;
पूर्ण

अटल पूर्णांक sx9310_init_device(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sx9310_data *data = iio_priv(indio_dev);
	काष्ठा sx9310_reg_शेष पंचांगp;
	स्थिर काष्ठा sx9310_reg_शेष *initval;
	पूर्णांक ret;
	अचिन्हित पूर्णांक i, val;

	ret = regmap_ग_लिखो(data->regmap, SX9310_REG_RESET, SX9310_SOFT_RESET);
	अगर (ret)
		वापस ret;

	usleep_range(1000, 2000); /* घातer-up समय is ~1ms. */

	/* Clear reset पूर्णांकerrupt state by पढ़ोing SX9310_REG_IRQ_SRC. */
	ret = regmap_पढ़ो(data->regmap, SX9310_REG_IRQ_SRC, &val);
	अगर (ret)
		वापस ret;

	/* Program some sane शेषs. */
	क्रम (i = 0; i < ARRAY_SIZE(sx9310_शेष_regs); i++) अणु
		initval = sx9310_get_शेष_reg(data, i, &पंचांगp);
		ret = regmap_ग_लिखो(data->regmap, initval->reg, initval->def);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस sx9310_init_compensation(indio_dev);
पूर्ण

अटल पूर्णांक sx9310_set_indio_dev_name(काष्ठा device *dev,
				     काष्ठा iio_dev *indio_dev,
				     अचिन्हित पूर्णांक whoami)
अणु
	अचिन्हित पूर्णांक दीर्घ ddata;

	ddata = (uपूर्णांकptr_t)device_get_match_data(dev);
	अगर (ddata != whoami) अणु
		dev_err(dev, "WHOAMI does not match device data: %u\n", whoami);
		वापस -ENODEV;
	पूर्ण

	चयन (whoami) अणु
	हाल SX9310_WHOAMI_VALUE:
		indio_dev->name = "sx9310";
		अवरोध;
	हाल SX9311_WHOAMI_VALUE:
		indio_dev->name = "sx9311";
		अवरोध;
	शेष:
		dev_err(dev, "unexpected WHOAMI response: %u\n", whoami);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sx9310_regulator_disable(व्योम *_data)
अणु
	काष्ठा sx9310_data *data = _data;

	regulator_bulk_disable(ARRAY_SIZE(data->supplies), data->supplies);
पूर्ण

अटल पूर्णांक sx9310_probe(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = &client->dev;
	काष्ठा iio_dev *indio_dev;
	काष्ठा sx9310_data *data;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	data->client = client;
	data->supplies[0].supply = "vdd";
	data->supplies[1].supply = "svdd";
	mutex_init(&data->mutex);
	init_completion(&data->completion);

	data->regmap = devm_regmap_init_i2c(client, &sx9310_regmap_config);
	अगर (IS_ERR(data->regmap))
		वापस PTR_ERR(data->regmap);

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(data->supplies),
				      data->supplies);
	अगर (ret)
		वापस ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(data->supplies), data->supplies);
	अगर (ret)
		वापस ret;
	/* Must रुको क्रम Tpor समय after initial घातer up */
	usleep_range(1000, 1100);

	ret = devm_add_action_or_reset(dev, sx9310_regulator_disable, data);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(data->regmap, SX9310_REG_WHOAMI, &data->whoami);
	अगर (ret) अणु
		dev_err(dev, "error in reading WHOAMI register: %d", ret);
		वापस ret;
	पूर्ण

	ret = sx9310_set_indio_dev_name(dev, indio_dev, data->whoami);
	अगर (ret)
		वापस ret;

	ACPI_COMPANION_SET(&indio_dev->dev, ACPI_COMPANION(dev));
	indio_dev->channels = sx9310_channels;
	indio_dev->num_channels = ARRAY_SIZE(sx9310_channels);
	indio_dev->info = &sx9310_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	i2c_set_clientdata(client, indio_dev);

	ret = sx9310_init_device(indio_dev);
	अगर (ret)
		वापस ret;

	अगर (client->irq) अणु
		ret = devm_request_thपढ़ोed_irq(dev, client->irq,
						sx9310_irq_handler,
						sx9310_irq_thपढ़ो_handler,
						IRQF_ONESHOT,
						"sx9310_event", indio_dev);
		अगर (ret)
			वापस ret;

		data->trig = devm_iio_trigger_alloc(dev, "%s-dev%d",
						    indio_dev->name,
						    indio_dev->id);
		अगर (!data->trig)
			वापस -ENOMEM;

		data->trig->ops = &sx9310_trigger_ops;
		iio_trigger_set_drvdata(data->trig, indio_dev);

		ret = devm_iio_trigger_रेजिस्टर(dev, data->trig);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = devm_iio_triggered_buffer_setup(dev, indio_dev,
					      iio_pollfunc_store_समय,
					      sx9310_trigger_handler,
					      &sx9310_buffer_setup_ops);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल पूर्णांक __maybe_unused sx9310_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा sx9310_data *data = iio_priv(indio_dev);
	u8 ctrl0;
	पूर्णांक ret;

	disable_irq_nosync(data->client->irq);

	mutex_lock(&data->mutex);
	ret = regmap_पढ़ो(data->regmap, SX9310_REG_PROX_CTRL0,
			  &data->suspend_ctrl0);
	अगर (ret)
		जाओ out;

	ctrl0 = data->suspend_ctrl0 & ~SX9310_REG_PROX_CTRL0_SENSOREN_MASK;
	ret = regmap_ग_लिखो(data->regmap, SX9310_REG_PROX_CTRL0, ctrl0);
	अगर (ret)
		जाओ out;

	ret = regmap_ग_लिखो(data->regmap, SX9310_REG_PAUSE, 0);

out:
	mutex_unlock(&data->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused sx9310_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा sx9310_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = regmap_ग_लिखो(data->regmap, SX9310_REG_PAUSE, 1);
	अगर (ret)
		जाओ out;

	ret = regmap_ग_लिखो(data->regmap, SX9310_REG_PROX_CTRL0,
			   data->suspend_ctrl0);

out:
	mutex_unlock(&data->mutex);
	अगर (ret)
		वापस ret;

	enable_irq(data->client->irq);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sx9310_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sx9310_suspend, sx9310_resume)
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id sx9310_acpi_match[] = अणु
	अणु "STH9310", SX9310_WHOAMI_VALUE पूर्ण,
	अणु "STH9311", SX9311_WHOAMI_VALUE पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, sx9310_acpi_match);

अटल स्थिर काष्ठा of_device_id sx9310_of_match[] = अणु
	अणु .compatible = "semtech,sx9310", (व्योम *)SX9310_WHOAMI_VALUE पूर्ण,
	अणु .compatible = "semtech,sx9311", (व्योम *)SX9311_WHOAMI_VALUE पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sx9310_of_match);

अटल स्थिर काष्ठा i2c_device_id sx9310_id[] = अणु
	अणु "sx9310", SX9310_WHOAMI_VALUE पूर्ण,
	अणु "sx9311", SX9311_WHOAMI_VALUE पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sx9310_id);

अटल काष्ठा i2c_driver sx9310_driver = अणु
	.driver = अणु
		.name	= "sx9310",
		.acpi_match_table = sx9310_acpi_match,
		.of_match_table = sx9310_of_match,
		.pm = &sx9310_pm_ops,

		/*
		 * Lots of i2c transfers in probe + over 200 ms रुकोing in
		 * sx9310_init_compensation() mean a slow probe; prefer async
		 * so we करोn't delay boot if we're builtin to the kernel.
		 */
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
	.probe_new	= sx9310_probe,
	.id_table	= sx9310_id,
पूर्ण;
module_i2c_driver(sx9310_driver);

MODULE_AUTHOR("Gwendal Grignou <gwendal@chromium.org>");
MODULE_AUTHOR("Daniel Campello <campello@chromium.org>");
MODULE_DESCRIPTION("Driver for Semtech SX9310/SX9311 proximity sensor");
MODULE_LICENSE("GPL v2");
