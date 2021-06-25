<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mma8452.c - Support क्रम following Freescale / NXP 3-axis accelerometers:
 *
 * device name	digital output	7-bit I2C slave address (pin selectable)
 * ---------------------------------------------------------------------
 * MMA8451Q	14 bit		0x1c / 0x1d
 * MMA8452Q	12 bit		0x1c / 0x1d
 * MMA8453Q	10 bit		0x1c / 0x1d
 * MMA8652FC	12 bit		0x1d
 * MMA8653FC	10 bit		0x1d
 * FXLS8471Q	14 bit		0x1e / 0x1d / 0x1c / 0x1f
 *
 * Copyright 2015 Martin Kepplinger <martink@posteo.de>
 * Copyright 2014 Peter Meerwald <pmeerw@pmeerw.net>
 *
 *
 * TODO: orientation events
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>

#घोषणा MMA8452_STATUS				0x00
#घोषणा  MMA8452_STATUS_DRDY			(BIT(2) | BIT(1) | BIT(0))
#घोषणा MMA8452_OUT_X				0x01 /* MSB first */
#घोषणा MMA8452_OUT_Y				0x03
#घोषणा MMA8452_OUT_Z				0x05
#घोषणा MMA8452_INT_SRC				0x0c
#घोषणा MMA8452_WHO_AM_I			0x0d
#घोषणा MMA8452_DATA_CFG			0x0e
#घोषणा  MMA8452_DATA_CFG_FS_MASK		GENMASK(1, 0)
#घोषणा  MMA8452_DATA_CFG_FS_2G			0
#घोषणा  MMA8452_DATA_CFG_FS_4G			1
#घोषणा  MMA8452_DATA_CFG_FS_8G			2
#घोषणा  MMA8452_DATA_CFG_HPF_MASK		BIT(4)
#घोषणा MMA8452_HP_FILTER_CUTOFF		0x0f
#घोषणा  MMA8452_HP_FILTER_CUTOFF_SEL_MASK	GENMASK(1, 0)
#घोषणा MMA8452_FF_MT_CFG			0x15
#घोषणा  MMA8452_FF_MT_CFG_OAE			BIT(6)
#घोषणा  MMA8452_FF_MT_CFG_ELE			BIT(7)
#घोषणा MMA8452_FF_MT_SRC			0x16
#घोषणा  MMA8452_FF_MT_SRC_XHE			BIT(1)
#घोषणा  MMA8452_FF_MT_SRC_YHE			BIT(3)
#घोषणा  MMA8452_FF_MT_SRC_ZHE			BIT(5)
#घोषणा MMA8452_FF_MT_THS			0x17
#घोषणा  MMA8452_FF_MT_THS_MASK			0x7f
#घोषणा MMA8452_FF_MT_COUNT			0x18
#घोषणा MMA8452_FF_MT_CHAN_SHIFT		3
#घोषणा MMA8452_TRANSIENT_CFG			0x1d
#घोषणा  MMA8452_TRANSIENT_CFG_CHAN(chan)	BIT(chan + 1)
#घोषणा  MMA8452_TRANSIENT_CFG_HPF_BYP		BIT(0)
#घोषणा  MMA8452_TRANSIENT_CFG_ELE		BIT(4)
#घोषणा MMA8452_TRANSIENT_SRC			0x1e
#घोषणा  MMA8452_TRANSIENT_SRC_XTRANSE		BIT(1)
#घोषणा  MMA8452_TRANSIENT_SRC_YTRANSE		BIT(3)
#घोषणा  MMA8452_TRANSIENT_SRC_ZTRANSE		BIT(5)
#घोषणा MMA8452_TRANSIENT_THS			0x1f
#घोषणा  MMA8452_TRANSIENT_THS_MASK		GENMASK(6, 0)
#घोषणा MMA8452_TRANSIENT_COUNT			0x20
#घोषणा MMA8452_TRANSIENT_CHAN_SHIFT		1
#घोषणा MMA8452_CTRL_REG1			0x2a
#घोषणा  MMA8452_CTRL_ACTIVE			BIT(0)
#घोषणा  MMA8452_CTRL_DR_MASK			GENMASK(5, 3)
#घोषणा  MMA8452_CTRL_DR_SHIFT			3
#घोषणा  MMA8452_CTRL_DR_DEFAULT		0x4 /* 50 Hz sample frequency */
#घोषणा MMA8452_CTRL_REG2			0x2b
#घोषणा  MMA8452_CTRL_REG2_RST			BIT(6)
#घोषणा  MMA8452_CTRL_REG2_MODS_SHIFT		3
#घोषणा  MMA8452_CTRL_REG2_MODS_MASK		0x1b
#घोषणा MMA8452_CTRL_REG4			0x2d
#घोषणा MMA8452_CTRL_REG5			0x2e
#घोषणा MMA8452_OFF_X				0x2f
#घोषणा MMA8452_OFF_Y				0x30
#घोषणा MMA8452_OFF_Z				0x31

#घोषणा MMA8452_MAX_REG				0x31

#घोषणा  MMA8452_INT_DRDY			BIT(0)
#घोषणा  MMA8452_INT_FF_MT			BIT(2)
#घोषणा  MMA8452_INT_TRANS			BIT(5)

#घोषणा MMA8451_DEVICE_ID			0x1a
#घोषणा MMA8452_DEVICE_ID			0x2a
#घोषणा MMA8453_DEVICE_ID			0x3a
#घोषणा MMA8652_DEVICE_ID			0x4a
#घोषणा MMA8653_DEVICE_ID			0x5a
#घोषणा FXLS8471_DEVICE_ID			0x6a

#घोषणा MMA8452_AUTO_SUSPEND_DELAY_MS		2000

काष्ठा mma8452_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	u8 ctrl_reg1;
	u8 data_cfg;
	स्थिर काष्ठा mma_chip_info *chip_info;
	पूर्णांक sleep_val;
	काष्ठा regulator *vdd_reg;
	काष्ठा regulator *vddio_reg;

	/* Ensure correct alignment of समय stamp when present */
	काष्ठा अणु
		__be16 channels[3];
		s64 ts __aligned(8);
	पूर्ण buffer;
पूर्ण;

 /**
  * काष्ठा mma8452_event_regs - chip specअगरic data related to events
  * @ev_cfg:			event config रेजिस्टर address
  * @ev_cfg_ele:			latch bit in event config रेजिस्टर
  * @ev_cfg_chan_shअगरt:		number of the bit to enable events in X
  *				direction; in event config रेजिस्टर
  * @ev_src:			event source रेजिस्टर address
  * @ev_ths:			event threshold रेजिस्टर address
  * @ev_ths_mask:		mask क्रम the threshold value
  * @ev_count:			event count (period) रेजिस्टर address
  *
  * Since not all chips supported by the driver support comparing high pass
  * filtered data क्रम events (पूर्णांकerrupts), dअगरferent पूर्णांकerrupt sources are
  * used क्रम dअगरferent chips and the relevant रेजिस्टरs are included here.
  */
काष्ठा mma8452_event_regs अणु
	u8 ev_cfg;
	u8 ev_cfg_ele;
	u8 ev_cfg_chan_shअगरt;
	u8 ev_src;
	u8 ev_ths;
	u8 ev_ths_mask;
	u8 ev_count;
पूर्ण;

अटल स्थिर काष्ठा mma8452_event_regs ff_mt_ev_regs = अणु
	.ev_cfg = MMA8452_FF_MT_CFG,
	.ev_cfg_ele = MMA8452_FF_MT_CFG_ELE,
	.ev_cfg_chan_shअगरt = MMA8452_FF_MT_CHAN_SHIFT,
	.ev_src = MMA8452_FF_MT_SRC,
	.ev_ths = MMA8452_FF_MT_THS,
	.ev_ths_mask = MMA8452_FF_MT_THS_MASK,
	.ev_count = MMA8452_FF_MT_COUNT
पूर्ण;

अटल स्थिर काष्ठा mma8452_event_regs trans_ev_regs = अणु
	.ev_cfg = MMA8452_TRANSIENT_CFG,
	.ev_cfg_ele = MMA8452_TRANSIENT_CFG_ELE,
	.ev_cfg_chan_shअगरt = MMA8452_TRANSIENT_CHAN_SHIFT,
	.ev_src = MMA8452_TRANSIENT_SRC,
	.ev_ths = MMA8452_TRANSIENT_THS,
	.ev_ths_mask = MMA8452_TRANSIENT_THS_MASK,
	.ev_count = MMA8452_TRANSIENT_COUNT,
पूर्ण;

/**
 * काष्ठा mma_chip_info - chip specअगरic data
 * @chip_id:			WHO_AM_I रेजिस्टर's value
 * @channels:			काष्ठा iio_chan_spec matching the device's
 *				capabilities
 * @num_channels:		number of channels
 * @mma_scales:			scale factors क्रम converting रेजिस्टर values
 *				to m/s^2; 3 modes: 2g, 4g, 8g; 2 पूर्णांकegers
 *				per mode: m/s^2 and micro m/s^2
 * @all_events:			all events supported by this chip
 * @enabled_events:		event flags enabled and handled by this driver
 */
काष्ठा mma_chip_info अणु
	u8 chip_id;
	स्थिर काष्ठा iio_chan_spec *channels;
	पूर्णांक num_channels;
	स्थिर पूर्णांक mma_scales[3][2];
	पूर्णांक all_events;
	पूर्णांक enabled_events;
पूर्ण;

क्रमागत अणु
	idx_x,
	idx_y,
	idx_z,
	idx_ts,
पूर्ण;

अटल पूर्णांक mma8452_drdy(काष्ठा mma8452_data *data)
अणु
	पूर्णांक tries = 150;

	जबतक (tries-- > 0) अणु
		पूर्णांक ret = i2c_smbus_पढ़ो_byte_data(data->client,
			MMA8452_STATUS);
		अगर (ret < 0)
			वापस ret;
		अगर ((ret & MMA8452_STATUS_DRDY) == MMA8452_STATUS_DRDY)
			वापस 0;

		अगर (data->sleep_val <= 20)
			usleep_range(data->sleep_val * 250,
				     data->sleep_val * 500);
		अन्यथा
			msleep(20);
	पूर्ण

	dev_err(&data->client->dev, "data not ready\n");

	वापस -EIO;
पूर्ण

अटल पूर्णांक mma8452_set_runसमय_pm_state(काष्ठा i2c_client *client, bool on)
अणु
#अगर_घोषित CONFIG_PM
	पूर्णांक ret;

	अगर (on) अणु
		ret = pm_runसमय_get_sync(&client->dev);
	पूर्ण अन्यथा अणु
		pm_runसमय_mark_last_busy(&client->dev);
		ret = pm_runसमय_put_स्वतःsuspend(&client->dev);
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(&client->dev,
			"failed to change power state to %d\n", on);
		अगर (on)
			pm_runसमय_put_noidle(&client->dev);

		वापस ret;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक mma8452_पढ़ो(काष्ठा mma8452_data *data, __be16 buf[3])
अणु
	पूर्णांक ret = mma8452_drdy(data);

	अगर (ret < 0)
		वापस ret;

	ret = mma8452_set_runसमय_pm_state(data->client, true);
	अगर (ret)
		वापस ret;

	ret = i2c_smbus_पढ़ो_i2c_block_data(data->client, MMA8452_OUT_X,
					    3 * माप(__be16), (u8 *)buf);

	ret = mma8452_set_runसमय_pm_state(data->client, false);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार mma8452_show_पूर्णांक_plus_micros(अक्षर *buf, स्थिर पूर्णांक (*vals)[2],
					    पूर्णांक n)
अणु
	माप_प्रकार len = 0;

	जबतक (n-- > 0)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%d.%06d ",
				 vals[n][0], vals[n][1]);

	/* replace trailing space by newline */
	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल पूर्णांक mma8452_get_पूर्णांक_plus_micros_index(स्थिर पूर्णांक (*vals)[2], पूर्णांक n,
					     पूर्णांक val, पूर्णांक val2)
अणु
	जबतक (n-- > 0)
		अगर (val == vals[n][0] && val2 == vals[n][1])
			वापस n;

	वापस -EINVAL;
पूर्ण

अटल अचिन्हित पूर्णांक mma8452_get_odr_index(काष्ठा mma8452_data *data)
अणु
	वापस (data->ctrl_reg1 & MMA8452_CTRL_DR_MASK) >>
			MMA8452_CTRL_DR_SHIFT;
पूर्ण

अटल स्थिर पूर्णांक mma8452_samp_freq[8][2] = अणु
	अणु800, 0पूर्ण, अणु400, 0पूर्ण, अणु200, 0पूर्ण, अणु100, 0पूर्ण, अणु50, 0पूर्ण, अणु12, 500000पूर्ण,
	अणु6, 250000पूर्ण, अणु1, 560000पूर्ण
पूर्ण;

/* Datasheet table: step समय "Relationship with the ODR" (sample frequency) */
अटल स्थिर अचिन्हित पूर्णांक mma8452_समय_step_us[4][8] = अणु
	अणु 1250, 2500, 5000, 10000, 20000, 20000, 20000, 20000 पूर्ण,  /* normal */
	अणु 1250, 2500, 5000, 10000, 20000, 80000, 80000, 80000 पूर्ण,  /* l p l n */
	अणु 1250, 2500, 2500, 2500, 2500, 2500, 2500, 2500 पूर्ण,	  /* high res*/
	अणु 1250, 2500, 5000, 10000, 20000, 80000, 160000, 160000 पूर्ण /* l p */
पूर्ण;

/* Datasheet table "High-Pass Filter Cutoff Options" */
अटल स्थिर पूर्णांक mma8452_hp_filter_cutoff[4][8][4][2] = अणु
	अणु /* normal */
	अणु अणु16, 0पूर्ण, अणु8, 0पूर्ण, अणु4, 0पूर्ण, अणु2, 0पूर्ण पूर्ण,		/* 800 Hz sample */
	अणु अणु16, 0पूर्ण, अणु8, 0पूर्ण, अणु4, 0पूर्ण, अणु2, 0पूर्ण पूर्ण,		/* 400 Hz sample */
	अणु अणु8, 0पूर्ण, अणु4, 0पूर्ण, अणु2, 0पूर्ण, अणु1, 0पूर्ण पूर्ण,		/* 200 Hz sample */
	अणु अणु4, 0पूर्ण, अणु2, 0पूर्ण, अणु1, 0पूर्ण, अणु0, 500000पूर्ण पूर्ण,	/* 100 Hz sample */
	अणु अणु2, 0पूर्ण, अणु1, 0पूर्ण, अणु0, 500000पूर्ण, अणु0, 250000पूर्ण पूर्ण,	/* 50 Hz sample */
	अणु अणु2, 0पूर्ण, अणु1, 0पूर्ण, अणु0, 500000पूर्ण, अणु0, 250000पूर्ण पूर्ण,	/* 12.5 Hz sample */
	अणु अणु2, 0पूर्ण, अणु1, 0पूर्ण, अणु0, 500000पूर्ण, अणु0, 250000पूर्ण पूर्ण,	/* 6.25 Hz sample */
	अणु अणु2, 0पूर्ण, अणु1, 0पूर्ण, अणु0, 500000पूर्ण, अणु0, 250000पूर्ण पूर्ण	/* 1.56 Hz sample */
	पूर्ण,
	अणु /* low noise low घातer */
	अणु अणु16, 0पूर्ण, अणु8, 0पूर्ण, अणु4, 0पूर्ण, अणु2, 0पूर्ण पूर्ण,
	अणु अणु16, 0पूर्ण, अणु8, 0पूर्ण, अणु4, 0पूर्ण, अणु2, 0पूर्ण पूर्ण,
	अणु अणु8, 0पूर्ण, अणु4, 0पूर्ण, अणु2, 0पूर्ण, अणु1, 0पूर्ण पूर्ण,
	अणु अणु4, 0पूर्ण, अणु2, 0पूर्ण, अणु1, 0पूर्ण, अणु0, 500000पूर्ण पूर्ण,
	अणु अणु2, 0पूर्ण, अणु1, 0पूर्ण, अणु0, 500000पूर्ण, अणु0, 250000पूर्ण पूर्ण,
	अणु अणु0, 500000पूर्ण, अणु0, 250000पूर्ण, अणु0, 125000पूर्ण, अणु0, 063000पूर्ण पूर्ण,
	अणु अणु0, 500000पूर्ण, अणु0, 250000पूर्ण, अणु0, 125000पूर्ण, अणु0, 063000पूर्ण पूर्ण,
	अणु अणु0, 500000पूर्ण, अणु0, 250000पूर्ण, अणु0, 125000पूर्ण, अणु0, 063000पूर्ण पूर्ण
	पूर्ण,
	अणु /* high resolution */
	अणु अणु16, 0पूर्ण, अणु8, 0पूर्ण, अणु4, 0पूर्ण, अणु2, 0पूर्ण पूर्ण,
	अणु अणु16, 0पूर्ण, अणु8, 0पूर्ण, अणु4, 0पूर्ण, अणु2, 0पूर्ण पूर्ण,
	अणु अणु16, 0पूर्ण, अणु8, 0पूर्ण, अणु4, 0पूर्ण, अणु2, 0पूर्ण पूर्ण,
	अणु अणु16, 0पूर्ण, अणु8, 0पूर्ण, अणु4, 0पूर्ण, अणु2, 0पूर्ण पूर्ण,
	अणु अणु16, 0पूर्ण, अणु8, 0पूर्ण, अणु4, 0पूर्ण, अणु2, 0पूर्ण पूर्ण,
	अणु अणु16, 0पूर्ण, अणु8, 0पूर्ण, अणु4, 0पूर्ण, अणु2, 0पूर्ण पूर्ण,
	अणु अणु16, 0पूर्ण, अणु8, 0पूर्ण, अणु4, 0पूर्ण, अणु2, 0पूर्ण पूर्ण,
	अणु अणु16, 0पूर्ण, अणु8, 0पूर्ण, अणु4, 0पूर्ण, अणु2, 0पूर्ण पूर्ण
	पूर्ण,
	अणु /* low घातer */
	अणु अणु16, 0पूर्ण, अणु8, 0पूर्ण, अणु4, 0पूर्ण, अणु2, 0पूर्ण पूर्ण,
	अणु अणु8, 0पूर्ण, अणु4, 0पूर्ण, अणु2, 0पूर्ण, अणु1, 0पूर्ण पूर्ण,
	अणु अणु4, 0पूर्ण, अणु2, 0पूर्ण, अणु1, 0पूर्ण, अणु0, 500000पूर्ण पूर्ण,
	अणु अणु2, 0पूर्ण, अणु1, 0पूर्ण, अणु0, 500000पूर्ण, अणु0, 250000पूर्ण पूर्ण,
	अणु अणु1, 0पूर्ण, अणु0, 500000पूर्ण, अणु0, 250000पूर्ण, अणु0, 125000पूर्ण पूर्ण,
	अणु अणु0, 250000पूर्ण, अणु0, 125000पूर्ण, अणु0, 063000पूर्ण, अणु0, 031000पूर्ण पूर्ण,
	अणु अणु0, 250000पूर्ण, अणु0, 125000पूर्ण, अणु0, 063000पूर्ण, अणु0, 031000पूर्ण पूर्ण,
	अणु अणु0, 250000पूर्ण, अणु0, 125000पूर्ण, अणु0, 063000पूर्ण, अणु0, 031000पूर्ण पूर्ण
	पूर्ण
पूर्ण;

/* Datasheet table "MODS Oversampling modes averaging values at each ODR" */
अटल स्थिर u16 mma8452_os_ratio[4][8] = अणु
	/* 800 Hz, 400 Hz, ... , 1.56 Hz */
	अणु 2, 4, 4, 4, 4, 16, 32, 128 पूर्ण,		/* normal */
	अणु 2, 4, 4, 4, 4, 4, 8, 32 पूर्ण,		/* low घातer low noise */
	अणु 2, 4, 8, 16, 32, 128, 256, 1024 पूर्ण,	/* high resolution */
	अणु 2, 2, 2, 2, 2, 2, 4, 16 पूर्ण		/* low घातer */
पूर्ण;

अटल पूर्णांक mma8452_get_घातer_mode(काष्ठा mma8452_data *data)
अणु
	पूर्णांक reg;

	reg = i2c_smbus_पढ़ो_byte_data(data->client,
				       MMA8452_CTRL_REG2);
	अगर (reg < 0)
		वापस reg;

	वापस ((reg & MMA8452_CTRL_REG2_MODS_MASK) >>
		MMA8452_CTRL_REG2_MODS_SHIFT);
पूर्ण

अटल sमाप_प्रकार mma8452_show_samp_freq_avail(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	वापस mma8452_show_पूर्णांक_plus_micros(buf, mma8452_samp_freq,
					    ARRAY_SIZE(mma8452_samp_freq));
पूर्ण

अटल sमाप_प्रकार mma8452_show_scale_avail(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा mma8452_data *data = iio_priv(i2c_get_clientdata(
					     to_i2c_client(dev)));

	वापस mma8452_show_पूर्णांक_plus_micros(buf, data->chip_info->mma_scales,
		ARRAY_SIZE(data->chip_info->mma_scales));
पूर्ण

अटल sमाप_प्रकार mma8452_show_hp_cutoff_avail(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा mma8452_data *data = iio_priv(indio_dev);
	पूर्णांक i, j;

	i = mma8452_get_odr_index(data);
	j = mma8452_get_घातer_mode(data);
	अगर (j < 0)
		वापस j;

	वापस mma8452_show_पूर्णांक_plus_micros(buf, mma8452_hp_filter_cutoff[j][i],
		ARRAY_SIZE(mma8452_hp_filter_cutoff[0][0]));
पूर्ण

अटल sमाप_प्रकार mma8452_show_os_ratio_avail(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा mma8452_data *data = iio_priv(indio_dev);
	पूर्णांक i = mma8452_get_odr_index(data);
	पूर्णांक j;
	u16 val = 0;
	माप_प्रकार len = 0;

	क्रम (j = 0; j < ARRAY_SIZE(mma8452_os_ratio); j++) अणु
		अगर (val == mma8452_os_ratio[j][i])
			जारी;

		val = mma8452_os_ratio[j][i];

		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%d ", val);
	पूर्ण
	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल IIO_DEV_ATTR_SAMP_FREQ_AVAIL(mma8452_show_samp_freq_avail);
अटल IIO_DEVICE_ATTR(in_accel_scale_available, 0444,
		       mma8452_show_scale_avail, शून्य, 0);
अटल IIO_DEVICE_ATTR(in_accel_filter_high_pass_3db_frequency_available,
		       0444, mma8452_show_hp_cutoff_avail, शून्य, 0);
अटल IIO_DEVICE_ATTR(in_accel_oversampling_ratio_available, 0444,
		       mma8452_show_os_ratio_avail, शून्य, 0);

अटल पूर्णांक mma8452_get_samp_freq_index(काष्ठा mma8452_data *data,
				       पूर्णांक val, पूर्णांक val2)
अणु
	वापस mma8452_get_पूर्णांक_plus_micros_index(mma8452_samp_freq,
						 ARRAY_SIZE(mma8452_samp_freq),
						 val, val2);
पूर्ण

अटल पूर्णांक mma8452_get_scale_index(काष्ठा mma8452_data *data, पूर्णांक val, पूर्णांक val2)
अणु
	वापस mma8452_get_पूर्णांक_plus_micros_index(data->chip_info->mma_scales,
			ARRAY_SIZE(data->chip_info->mma_scales), val, val2);
पूर्ण

अटल पूर्णांक mma8452_get_hp_filter_index(काष्ठा mma8452_data *data,
				       पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i, j;

	i = mma8452_get_odr_index(data);
	j = mma8452_get_घातer_mode(data);
	अगर (j < 0)
		वापस j;

	वापस mma8452_get_पूर्णांक_plus_micros_index(mma8452_hp_filter_cutoff[j][i],
		ARRAY_SIZE(mma8452_hp_filter_cutoff[0][0]), val, val2);
पूर्ण

अटल पूर्णांक mma8452_पढ़ो_hp_filter(काष्ठा mma8452_data *data, पूर्णांक *hz, पूर्णांक *uHz)
अणु
	पूर्णांक j, i, ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, MMA8452_HP_FILTER_CUTOFF);
	अगर (ret < 0)
		वापस ret;

	i = mma8452_get_odr_index(data);
	j = mma8452_get_घातer_mode(data);
	अगर (j < 0)
		वापस j;

	ret &= MMA8452_HP_FILTER_CUTOFF_SEL_MASK;
	*hz = mma8452_hp_filter_cutoff[j][i][ret][0];
	*uHz = mma8452_hp_filter_cutoff[j][i][ret][1];

	वापस 0;
पूर्ण

अटल पूर्णांक mma8452_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mma8452_data *data = iio_priv(indio_dev);
	__be16 buffer[3];
	पूर्णांक i, ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		mutex_lock(&data->lock);
		ret = mma8452_पढ़ो(data, buffer);
		mutex_unlock(&data->lock);
		iio_device_release_direct_mode(indio_dev);
		अगर (ret < 0)
			वापस ret;

		*val = sign_extend32(be16_to_cpu(
			buffer[chan->scan_index]) >> chan->scan_type.shअगरt,
			chan->scan_type.realbits - 1);

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		i = data->data_cfg & MMA8452_DATA_CFG_FS_MASK;
		*val = data->chip_info->mma_scales[i][0];
		*val2 = data->chip_info->mma_scales[i][1];

		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		i = mma8452_get_odr_index(data);
		*val = mma8452_samp_freq[i][0];
		*val2 = mma8452_samp_freq[i][1];

		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		ret = i2c_smbus_पढ़ो_byte_data(data->client,
					       MMA8452_OFF_X +
					       chan->scan_index);
		अगर (ret < 0)
			वापस ret;

		*val = sign_extend32(ret, 7);

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_HIGH_PASS_FILTER_3DB_FREQUENCY:
		अगर (data->data_cfg & MMA8452_DATA_CFG_HPF_MASK) अणु
			ret = mma8452_पढ़ो_hp_filter(data, val, val2);
			अगर (ret < 0)
				वापस ret;
		पूर्ण अन्यथा अणु
			*val = 0;
			*val2 = 0;
		पूर्ण

		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		ret = mma8452_get_घातer_mode(data);
		अगर (ret < 0)
			वापस ret;

		i = mma8452_get_odr_index(data);

		*val = mma8452_os_ratio[ret][i];
		वापस IIO_VAL_INT;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mma8452_calculate_sleep(काष्ठा mma8452_data *data)
अणु
	पूर्णांक ret, i = mma8452_get_odr_index(data);

	अगर (mma8452_samp_freq[i][0] > 0)
		ret = 1000 / mma8452_samp_freq[i][0];
	अन्यथा
		ret = 1000;

	वापस ret == 0 ? 1 : ret;
पूर्ण

अटल पूर्णांक mma8452_standby(काष्ठा mma8452_data *data)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(data->client, MMA8452_CTRL_REG1,
					data->ctrl_reg1 & ~MMA8452_CTRL_ACTIVE);
पूर्ण

अटल पूर्णांक mma8452_active(काष्ठा mma8452_data *data)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(data->client, MMA8452_CTRL_REG1,
					 data->ctrl_reg1);
पूर्ण

/* वापसs >0 अगर active, 0 अगर in standby and <0 on error */
अटल पूर्णांक mma8452_is_active(काष्ठा mma8452_data *data)
अणु
	पूर्णांक reg;

	reg = i2c_smbus_पढ़ो_byte_data(data->client, MMA8452_CTRL_REG1);
	अगर (reg < 0)
		वापस reg;

	वापस reg & MMA8452_CTRL_ACTIVE;
पूर्ण

अटल पूर्णांक mma8452_change_config(काष्ठा mma8452_data *data, u8 reg, u8 val)
अणु
	पूर्णांक ret;
	पूर्णांक is_active;

	mutex_lock(&data->lock);

	is_active = mma8452_is_active(data);
	अगर (is_active < 0) अणु
		ret = is_active;
		जाओ fail;
	पूर्ण

	/* config can only be changed when in standby */
	अगर (is_active > 0) अणु
		ret = mma8452_standby(data);
		अगर (ret < 0)
			जाओ fail;
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, reg, val);
	अगर (ret < 0)
		जाओ fail;

	अगर (is_active > 0) अणु
		ret = mma8452_active(data);
		अगर (ret < 0)
			जाओ fail;
	पूर्ण

	ret = 0;
fail:
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक mma8452_set_घातer_mode(काष्ठा mma8452_data *data, u8 mode)
अणु
	पूर्णांक reg;

	reg = i2c_smbus_पढ़ो_byte_data(data->client,
				       MMA8452_CTRL_REG2);
	अगर (reg < 0)
		वापस reg;

	reg &= ~MMA8452_CTRL_REG2_MODS_MASK;
	reg |= mode << MMA8452_CTRL_REG2_MODS_SHIFT;

	वापस mma8452_change_config(data, MMA8452_CTRL_REG2, reg);
पूर्ण

/* वापसs >0 अगर in मुक्तfall mode, 0 अगर not or <0 अगर an error occurred */
अटल पूर्णांक mma8452_मुक्तfall_mode_enabled(काष्ठा mma8452_data *data)
अणु
	पूर्णांक val;

	val = i2c_smbus_पढ़ो_byte_data(data->client, MMA8452_FF_MT_CFG);
	अगर (val < 0)
		वापस val;

	वापस !(val & MMA8452_FF_MT_CFG_OAE);
पूर्ण

अटल पूर्णांक mma8452_set_मुक्तfall_mode(काष्ठा mma8452_data *data, bool state)
अणु
	पूर्णांक val;

	अगर ((state && mma8452_मुक्तfall_mode_enabled(data)) ||
	    (!state && !(mma8452_मुक्तfall_mode_enabled(data))))
		वापस 0;

	val = i2c_smbus_पढ़ो_byte_data(data->client, MMA8452_FF_MT_CFG);
	अगर (val < 0)
		वापस val;

	अगर (state) अणु
		val |= BIT(idx_x + MMA8452_FF_MT_CHAN_SHIFT);
		val |= BIT(idx_y + MMA8452_FF_MT_CHAN_SHIFT);
		val |= BIT(idx_z + MMA8452_FF_MT_CHAN_SHIFT);
		val &= ~MMA8452_FF_MT_CFG_OAE;
	पूर्ण अन्यथा अणु
		val &= ~BIT(idx_x + MMA8452_FF_MT_CHAN_SHIFT);
		val &= ~BIT(idx_y + MMA8452_FF_MT_CHAN_SHIFT);
		val &= ~BIT(idx_z + MMA8452_FF_MT_CHAN_SHIFT);
		val |= MMA8452_FF_MT_CFG_OAE;
	पूर्ण

	वापस mma8452_change_config(data, MMA8452_FF_MT_CFG, val);
पूर्ण

अटल पूर्णांक mma8452_set_hp_filter_frequency(काष्ठा mma8452_data *data,
					   पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i, reg;

	i = mma8452_get_hp_filter_index(data, val, val2);
	अगर (i < 0)
		वापस i;

	reg = i2c_smbus_पढ़ो_byte_data(data->client,
				       MMA8452_HP_FILTER_CUTOFF);
	अगर (reg < 0)
		वापस reg;

	reg &= ~MMA8452_HP_FILTER_CUTOFF_SEL_MASK;
	reg |= i;

	वापस mma8452_change_config(data, MMA8452_HP_FILTER_CUTOFF, reg);
पूर्ण

अटल पूर्णांक mma8452_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा mma8452_data *data = iio_priv(indio_dev);
	पूर्णांक i, ret;

	ret = iio_device_claim_direct_mode(indio_dev);
	अगर (ret)
		वापस ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		i = mma8452_get_samp_freq_index(data, val, val2);
		अगर (i < 0) अणु
			ret = i;
			अवरोध;
		पूर्ण
		data->ctrl_reg1 &= ~MMA8452_CTRL_DR_MASK;
		data->ctrl_reg1 |= i << MMA8452_CTRL_DR_SHIFT;

		data->sleep_val = mma8452_calculate_sleep(data);

		ret = mma8452_change_config(data, MMA8452_CTRL_REG1,
					    data->ctrl_reg1);
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		i = mma8452_get_scale_index(data, val, val2);
		अगर (i < 0) अणु
			ret = i;
			अवरोध;
		पूर्ण

		data->data_cfg &= ~MMA8452_DATA_CFG_FS_MASK;
		data->data_cfg |= i;

		ret = mma8452_change_config(data, MMA8452_DATA_CFG,
					    data->data_cfg);
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		अगर (val < -128 || val > 127) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		ret = mma8452_change_config(data,
					    MMA8452_OFF_X + chan->scan_index,
					    val);
		अवरोध;

	हाल IIO_CHAN_INFO_HIGH_PASS_FILTER_3DB_FREQUENCY:
		अगर (val == 0 && val2 == 0) अणु
			data->data_cfg &= ~MMA8452_DATA_CFG_HPF_MASK;
		पूर्ण अन्यथा अणु
			data->data_cfg |= MMA8452_DATA_CFG_HPF_MASK;
			ret = mma8452_set_hp_filter_frequency(data, val, val2);
			अगर (ret < 0)
				अवरोध;
		पूर्ण

		ret = mma8452_change_config(data, MMA8452_DATA_CFG,
					     data->data_cfg);
		अवरोध;

	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		ret = mma8452_get_odr_index(data);

		क्रम (i = 0; i < ARRAY_SIZE(mma8452_os_ratio); i++) अणु
			अगर (mma8452_os_ratio[i][ret] == val) अणु
				ret = mma8452_set_घातer_mode(data, i);
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	iio_device_release_direct_mode(indio_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक mma8452_get_event_regs(काष्ठा mma8452_data *data,
		स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_direction dir,
		स्थिर काष्ठा mma8452_event_regs **ev_reg)
अणु
	अगर (!chan)
		वापस -EINVAL;

	चयन (chan->type) अणु
	हाल IIO_ACCEL:
		चयन (dir) अणु
		हाल IIO_EV_सूची_RISING:
			अगर ((data->chip_info->all_events
					& MMA8452_INT_TRANS) &&
				(data->chip_info->enabled_events
					& MMA8452_INT_TRANS))
				*ev_reg = &trans_ev_regs;
			अन्यथा
				*ev_reg = &ff_mt_ev_regs;
			वापस 0;
		हाल IIO_EV_सूची_FALLING:
			*ev_reg = &ff_mt_ev_regs;
			वापस 0;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mma8452_पढ़ो_event_value(काष्ठा iio_dev *indio_dev,
			       स्थिर काष्ठा iio_chan_spec *chan,
			       क्रमागत iio_event_type type,
			       क्रमागत iio_event_direction dir,
			       क्रमागत iio_event_info info,
			       पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा mma8452_data *data = iio_priv(indio_dev);
	पूर्णांक ret, us, घातer_mode;
	स्थिर काष्ठा mma8452_event_regs *ev_regs;

	ret = mma8452_get_event_regs(data, chan, dir, &ev_regs);
	अगर (ret)
		वापस ret;

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		ret = i2c_smbus_पढ़ो_byte_data(data->client, ev_regs->ev_ths);
		अगर (ret < 0)
			वापस ret;

		*val = ret & ev_regs->ev_ths_mask;

		वापस IIO_VAL_INT;

	हाल IIO_EV_INFO_PERIOD:
		ret = i2c_smbus_पढ़ो_byte_data(data->client, ev_regs->ev_count);
		अगर (ret < 0)
			वापस ret;

		घातer_mode = mma8452_get_घातer_mode(data);
		अगर (घातer_mode < 0)
			वापस घातer_mode;

		us = ret * mma8452_समय_step_us[घातer_mode][
				mma8452_get_odr_index(data)];
		*val = us / USEC_PER_SEC;
		*val2 = us % USEC_PER_SEC;

		वापस IIO_VAL_INT_PLUS_MICRO;

	हाल IIO_EV_INFO_HIGH_PASS_FILTER_3DB:
		ret = i2c_smbus_पढ़ो_byte_data(data->client,
					       MMA8452_TRANSIENT_CFG);
		अगर (ret < 0)
			वापस ret;

		अगर (ret & MMA8452_TRANSIENT_CFG_HPF_BYP) अणु
			*val = 0;
			*val2 = 0;
		पूर्ण अन्यथा अणु
			ret = mma8452_पढ़ो_hp_filter(data, val, val2);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		वापस IIO_VAL_INT_PLUS_MICRO;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mma8452_ग_लिखो_event_value(काष्ठा iio_dev *indio_dev,
				स्थिर काष्ठा iio_chan_spec *chan,
				क्रमागत iio_event_type type,
				क्रमागत iio_event_direction dir,
				क्रमागत iio_event_info info,
				पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा mma8452_data *data = iio_priv(indio_dev);
	पूर्णांक ret, reg, steps;
	स्थिर काष्ठा mma8452_event_regs *ev_regs;

	ret = mma8452_get_event_regs(data, chan, dir, &ev_regs);
	अगर (ret)
		वापस ret;

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		अगर (val < 0 || val > ev_regs->ev_ths_mask)
			वापस -EINVAL;

		वापस mma8452_change_config(data, ev_regs->ev_ths, val);

	हाल IIO_EV_INFO_PERIOD:
		ret = mma8452_get_घातer_mode(data);
		अगर (ret < 0)
			वापस ret;

		steps = (val * USEC_PER_SEC + val2) /
				mma8452_समय_step_us[ret][
					mma8452_get_odr_index(data)];

		अगर (steps < 0 || steps > 0xff)
			वापस -EINVAL;

		वापस mma8452_change_config(data, ev_regs->ev_count, steps);

	हाल IIO_EV_INFO_HIGH_PASS_FILTER_3DB:
		reg = i2c_smbus_पढ़ो_byte_data(data->client,
					       MMA8452_TRANSIENT_CFG);
		अगर (reg < 0)
			वापस reg;

		अगर (val == 0 && val2 == 0) अणु
			reg |= MMA8452_TRANSIENT_CFG_HPF_BYP;
		पूर्ण अन्यथा अणु
			reg &= ~MMA8452_TRANSIENT_CFG_HPF_BYP;
			ret = mma8452_set_hp_filter_frequency(data, val, val2);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		वापस mma8452_change_config(data, MMA8452_TRANSIENT_CFG, reg);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mma8452_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     क्रमागत iio_event_type type,
				     क्रमागत iio_event_direction dir)
अणु
	काष्ठा mma8452_data *data = iio_priv(indio_dev);
	पूर्णांक ret;
	स्थिर काष्ठा mma8452_event_regs *ev_regs;

	ret = mma8452_get_event_regs(data, chan, dir, &ev_regs);
	अगर (ret)
		वापस ret;

	चयन (dir) अणु
	हाल IIO_EV_सूची_FALLING:
		वापस mma8452_मुक्तfall_mode_enabled(data);
	हाल IIO_EV_सूची_RISING:
		ret = i2c_smbus_पढ़ो_byte_data(data->client,
				ev_regs->ev_cfg);
		अगर (ret < 0)
			वापस ret;

		वापस !!(ret & BIT(chan->scan_index +
				ev_regs->ev_cfg_chan_shअगरt));
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mma8452_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
				      स्थिर काष्ठा iio_chan_spec *chan,
				      क्रमागत iio_event_type type,
				      क्रमागत iio_event_direction dir,
				      पूर्णांक state)
अणु
	काष्ठा mma8452_data *data = iio_priv(indio_dev);
	पूर्णांक val, ret;
	स्थिर काष्ठा mma8452_event_regs *ev_regs;

	ret = mma8452_get_event_regs(data, chan, dir, &ev_regs);
	अगर (ret)
		वापस ret;

	ret = mma8452_set_runसमय_pm_state(data->client, state);
	अगर (ret)
		वापस ret;

	चयन (dir) अणु
	हाल IIO_EV_सूची_FALLING:
		वापस mma8452_set_मुक्तfall_mode(data, state);
	हाल IIO_EV_सूची_RISING:
		val = i2c_smbus_पढ़ो_byte_data(data->client, ev_regs->ev_cfg);
		अगर (val < 0)
			वापस val;

		अगर (state) अणु
			अगर (mma8452_मुक्तfall_mode_enabled(data)) अणु
				val &= ~BIT(idx_x + ev_regs->ev_cfg_chan_shअगरt);
				val &= ~BIT(idx_y + ev_regs->ev_cfg_chan_shअगरt);
				val &= ~BIT(idx_z + ev_regs->ev_cfg_chan_shअगरt);
				val |= MMA8452_FF_MT_CFG_OAE;
			पूर्ण
			val |= BIT(chan->scan_index +
					ev_regs->ev_cfg_chan_shअगरt);
		पूर्ण अन्यथा अणु
			अगर (mma8452_मुक्तfall_mode_enabled(data))
				वापस 0;

			val &= ~BIT(chan->scan_index +
					ev_regs->ev_cfg_chan_shअगरt);
		पूर्ण

		val |= ev_regs->ev_cfg_ele;

		वापस mma8452_change_config(data, ev_regs->ev_cfg, val);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम mma8452_transient_पूर्णांकerrupt(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा mma8452_data *data = iio_priv(indio_dev);
	s64 ts = iio_get_समय_ns(indio_dev);
	पूर्णांक src;

	src = i2c_smbus_पढ़ो_byte_data(data->client, MMA8452_TRANSIENT_SRC);
	अगर (src < 0)
		वापस;

	अगर (src & MMA8452_TRANSIENT_SRC_XTRANSE)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEL, 0, IIO_MOD_X,
						  IIO_EV_TYPE_MAG,
						  IIO_EV_सूची_RISING),
			       ts);

	अगर (src & MMA8452_TRANSIENT_SRC_YTRANSE)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEL, 0, IIO_MOD_Y,
						  IIO_EV_TYPE_MAG,
						  IIO_EV_सूची_RISING),
			       ts);

	अगर (src & MMA8452_TRANSIENT_SRC_ZTRANSE)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEL, 0, IIO_MOD_Z,
						  IIO_EV_TYPE_MAG,
						  IIO_EV_सूची_RISING),
			       ts);
पूर्ण

अटल irqवापस_t mma8452_पूर्णांकerrupt(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_dev *indio_dev = p;
	काष्ठा mma8452_data *data = iio_priv(indio_dev);
	पूर्णांक ret = IRQ_NONE;
	पूर्णांक src;

	src = i2c_smbus_पढ़ो_byte_data(data->client, MMA8452_INT_SRC);
	अगर (src < 0)
		वापस IRQ_NONE;

	अगर (!(src & (data->chip_info->enabled_events | MMA8452_INT_DRDY)))
		वापस IRQ_NONE;

	अगर (src & MMA8452_INT_DRDY) अणु
		iio_trigger_poll_chained(indio_dev->trig);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (src & MMA8452_INT_FF_MT) अणु
		अगर (mma8452_मुक्तfall_mode_enabled(data)) अणु
			s64 ts = iio_get_समय_ns(indio_dev);

			iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(IIO_ACCEL, 0,
							  IIO_MOD_X_AND_Y_AND_Z,
							  IIO_EV_TYPE_MAG,
							  IIO_EV_सूची_FALLING),
					ts);
		पूर्ण
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (src & MMA8452_INT_TRANS) अणु
		mma8452_transient_पूर्णांकerrupt(indio_dev);
		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t mma8452_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा mma8452_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = mma8452_पढ़ो(data, data->buffer.channels);
	अगर (ret < 0)
		जाओ करोne;

	iio_push_to_buffers_with_बारtamp(indio_dev, &data->buffer,
					   iio_get_समय_ns(indio_dev));

करोne:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mma8452_reg_access_dbg(काष्ठा iio_dev *indio_dev,
				  अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक ग_लिखोval,
				  अचिन्हित पूर्णांक *पढ़ोval)
अणु
	पूर्णांक ret;
	काष्ठा mma8452_data *data = iio_priv(indio_dev);

	अगर (reg > MMA8452_MAX_REG)
		वापस -EINVAL;

	अगर (!पढ़ोval)
		वापस mma8452_change_config(data, reg, ग_लिखोval);

	ret = i2c_smbus_पढ़ो_byte_data(data->client, reg);
	अगर (ret < 0)
		वापस ret;

	*पढ़ोval = ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_event_spec mma8452_मुक्तfall_event[] = अणु
	अणु
		.type = IIO_EV_TYPE_MAG,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_ENABLE),
		.mask_shared_by_type = BIT(IIO_EV_INFO_VALUE) |
					BIT(IIO_EV_INFO_PERIOD) |
					BIT(IIO_EV_INFO_HIGH_PASS_FILTER_3DB)
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec mma8652_मुक्तfall_event[] = अणु
	अणु
		.type = IIO_EV_TYPE_MAG,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_ENABLE),
		.mask_shared_by_type = BIT(IIO_EV_INFO_VALUE) |
					BIT(IIO_EV_INFO_PERIOD)
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec mma8452_transient_event[] = अणु
	अणु
		.type = IIO_EV_TYPE_MAG,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_ENABLE),
		.mask_shared_by_type = BIT(IIO_EV_INFO_VALUE) |
					BIT(IIO_EV_INFO_PERIOD) |
					BIT(IIO_EV_INFO_HIGH_PASS_FILTER_3DB)
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec mma8452_motion_event[] = अणु
	अणु
		.type = IIO_EV_TYPE_MAG,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_ENABLE),
		.mask_shared_by_type = BIT(IIO_EV_INFO_VALUE) |
					BIT(IIO_EV_INFO_PERIOD)
	पूर्ण,
पूर्ण;

/*
 * Threshold is configured in fixed 8G/127 steps regardless of
 * currently selected scale क्रम measurement.
 */
अटल IIO_CONST_ATTR_NAMED(accel_transient_scale, in_accel_scale, "0.617742");

अटल काष्ठा attribute *mma8452_event_attributes[] = अणु
	&iio_स्थिर_attr_accel_transient_scale.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mma8452_event_attribute_group = अणु
	.attrs = mma8452_event_attributes,
पूर्ण;

#घोषणा MMA8452_FREEFALL_CHANNEL(modअगरier) अणु \
	.type = IIO_ACCEL, \
	.modअगरied = 1, \
	.channel2 = modअगरier, \
	.scan_index = -1, \
	.event_spec = mma8452_मुक्तfall_event, \
	.num_event_specs = ARRAY_SIZE(mma8452_मुक्तfall_event), \
पूर्ण

#घोषणा MMA8652_FREEFALL_CHANNEL(modअगरier) अणु \
	.type = IIO_ACCEL, \
	.modअगरied = 1, \
	.channel2 = modअगरier, \
	.scan_index = -1, \
	.event_spec = mma8652_मुक्तfall_event, \
	.num_event_specs = ARRAY_SIZE(mma8652_मुक्तfall_event), \
पूर्ण

#घोषणा MMA8452_CHANNEL(axis, idx, bits) अणु \
	.type = IIO_ACCEL, \
	.modअगरied = 1, \
	.channel2 = IIO_MOD_##axis, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
			      BIT(IIO_CHAN_INFO_CALIBBIAS), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SAMP_FREQ) | \
			BIT(IIO_CHAN_INFO_SCALE) | \
			BIT(IIO_CHAN_INFO_HIGH_PASS_FILTER_3DB_FREQUENCY) | \
			BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO), \
	.scan_index = idx, \
	.scan_type = अणु \
		.sign = 's', \
		.realbits = (bits), \
		.storagebits = 16, \
		.shअगरt = 16 - (bits), \
		.endianness = IIO_BE, \
	पूर्ण, \
	.event_spec = mma8452_transient_event, \
	.num_event_specs = ARRAY_SIZE(mma8452_transient_event), \
पूर्ण

#घोषणा MMA8652_CHANNEL(axis, idx, bits) अणु \
	.type = IIO_ACCEL, \
	.modअगरied = 1, \
	.channel2 = IIO_MOD_##axis, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
		BIT(IIO_CHAN_INFO_CALIBBIAS), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SAMP_FREQ) | \
		BIT(IIO_CHAN_INFO_SCALE) | \
		BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO), \
	.scan_index = idx, \
	.scan_type = अणु \
		.sign = 's', \
		.realbits = (bits), \
		.storagebits = 16, \
		.shअगरt = 16 - (bits), \
		.endianness = IIO_BE, \
	पूर्ण, \
	.event_spec = mma8452_motion_event, \
	.num_event_specs = ARRAY_SIZE(mma8452_motion_event), \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mma8451_channels[] = अणु
	MMA8452_CHANNEL(X, idx_x, 14),
	MMA8452_CHANNEL(Y, idx_y, 14),
	MMA8452_CHANNEL(Z, idx_z, 14),
	IIO_CHAN_SOFT_TIMESTAMP(idx_ts),
	MMA8452_FREEFALL_CHANNEL(IIO_MOD_X_AND_Y_AND_Z),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec mma8452_channels[] = अणु
	MMA8452_CHANNEL(X, idx_x, 12),
	MMA8452_CHANNEL(Y, idx_y, 12),
	MMA8452_CHANNEL(Z, idx_z, 12),
	IIO_CHAN_SOFT_TIMESTAMP(idx_ts),
	MMA8452_FREEFALL_CHANNEL(IIO_MOD_X_AND_Y_AND_Z),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec mma8453_channels[] = अणु
	MMA8452_CHANNEL(X, idx_x, 10),
	MMA8452_CHANNEL(Y, idx_y, 10),
	MMA8452_CHANNEL(Z, idx_z, 10),
	IIO_CHAN_SOFT_TIMESTAMP(idx_ts),
	MMA8452_FREEFALL_CHANNEL(IIO_MOD_X_AND_Y_AND_Z),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec mma8652_channels[] = अणु
	MMA8652_CHANNEL(X, idx_x, 12),
	MMA8652_CHANNEL(Y, idx_y, 12),
	MMA8652_CHANNEL(Z, idx_z, 12),
	IIO_CHAN_SOFT_TIMESTAMP(idx_ts),
	MMA8652_FREEFALL_CHANNEL(IIO_MOD_X_AND_Y_AND_Z),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec mma8653_channels[] = अणु
	MMA8652_CHANNEL(X, idx_x, 10),
	MMA8652_CHANNEL(Y, idx_y, 10),
	MMA8652_CHANNEL(Z, idx_z, 10),
	IIO_CHAN_SOFT_TIMESTAMP(idx_ts),
	MMA8652_FREEFALL_CHANNEL(IIO_MOD_X_AND_Y_AND_Z),
पूर्ण;

क्रमागत अणु
	mma8451,
	mma8452,
	mma8453,
	mma8652,
	mma8653,
	fxls8471,
पूर्ण;

अटल स्थिर काष्ठा mma_chip_info mma_chip_info_table[] = अणु
	[mma8451] = अणु
		.chip_id = MMA8451_DEVICE_ID,
		.channels = mma8451_channels,
		.num_channels = ARRAY_SIZE(mma8451_channels),
		/*
		 * Hardware has fullscale of -2G, -4G, -8G corresponding to
		 * raw value -8192 क्रम 14 bit, -2048 क्रम 12 bit or -512 क्रम 10
		 * bit.
		 * The userspace पूर्णांकerface uses m/s^2 and we declare micro units
		 * So scale factor क्रम 12 bit here is given by:
		 *	g * N * 1000000 / 2048 क्रम N = 2, 4, 8 and g=9.80665
		 */
		.mma_scales = अणु अणु0, 2394पूर्ण, अणु0, 4788पूर्ण, अणु0, 9577पूर्ण पूर्ण,
		/*
		 * Although we enable the पूर्णांकerrupt sources once and क्रम
		 * all here the event detection itself is not enabled until
		 * userspace asks क्रम it by mma8452_ग_लिखो_event_config()
		 */
		.all_events = MMA8452_INT_DRDY |
					MMA8452_INT_TRANS |
					MMA8452_INT_FF_MT,
		.enabled_events = MMA8452_INT_TRANS |
					MMA8452_INT_FF_MT,
	पूर्ण,
	[mma8452] = अणु
		.chip_id = MMA8452_DEVICE_ID,
		.channels = mma8452_channels,
		.num_channels = ARRAY_SIZE(mma8452_channels),
		.mma_scales = अणु अणु0, 9577पूर्ण, अणु0, 19154पूर्ण, अणु0, 38307पूर्ण पूर्ण,
		/*
		 * Although we enable the पूर्णांकerrupt sources once and क्रम
		 * all here the event detection itself is not enabled until
		 * userspace asks क्रम it by mma8452_ग_लिखो_event_config()
		 */
		.all_events = MMA8452_INT_DRDY |
					MMA8452_INT_TRANS |
					MMA8452_INT_FF_MT,
		.enabled_events = MMA8452_INT_TRANS |
					MMA8452_INT_FF_MT,
	पूर्ण,
	[mma8453] = अणु
		.chip_id = MMA8453_DEVICE_ID,
		.channels = mma8453_channels,
		.num_channels = ARRAY_SIZE(mma8453_channels),
		.mma_scales = अणु अणु0, 38307पूर्ण, अणु0, 76614पूर्ण, अणु0, 153228पूर्ण पूर्ण,
		/*
		 * Although we enable the पूर्णांकerrupt sources once and क्रम
		 * all here the event detection itself is not enabled until
		 * userspace asks क्रम it by mma8452_ग_लिखो_event_config()
		 */
		.all_events = MMA8452_INT_DRDY |
					MMA8452_INT_TRANS |
					MMA8452_INT_FF_MT,
		.enabled_events = MMA8452_INT_TRANS |
					MMA8452_INT_FF_MT,
	पूर्ण,
	[mma8652] = अणु
		.chip_id = MMA8652_DEVICE_ID,
		.channels = mma8652_channels,
		.num_channels = ARRAY_SIZE(mma8652_channels),
		.mma_scales = अणु अणु0, 9577पूर्ण, अणु0, 19154पूर्ण, अणु0, 38307पूर्ण पूर्ण,
		.all_events = MMA8452_INT_DRDY |
					MMA8452_INT_FF_MT,
		.enabled_events = MMA8452_INT_FF_MT,
	पूर्ण,
	[mma8653] = अणु
		.chip_id = MMA8653_DEVICE_ID,
		.channels = mma8653_channels,
		.num_channels = ARRAY_SIZE(mma8653_channels),
		.mma_scales = अणु अणु0, 38307पूर्ण, अणु0, 76614पूर्ण, अणु0, 153228पूर्ण पूर्ण,
		/*
		 * Although we enable the पूर्णांकerrupt sources once and क्रम
		 * all here the event detection itself is not enabled until
		 * userspace asks क्रम it by mma8452_ग_लिखो_event_config()
		 */
		.all_events = MMA8452_INT_DRDY |
					MMA8452_INT_FF_MT,
		.enabled_events = MMA8452_INT_FF_MT,
	पूर्ण,
	[fxls8471] = अणु
		.chip_id = FXLS8471_DEVICE_ID,
		.channels = mma8451_channels,
		.num_channels = ARRAY_SIZE(mma8451_channels),
		.mma_scales = अणु अणु0, 2394पूर्ण, अणु0, 4788पूर्ण, अणु0, 9577पूर्ण पूर्ण,
		/*
		 * Although we enable the पूर्णांकerrupt sources once and क्रम
		 * all here the event detection itself is not enabled until
		 * userspace asks क्रम it by mma8452_ग_लिखो_event_config()
		 */
		.all_events = MMA8452_INT_DRDY |
					MMA8452_INT_TRANS |
					MMA8452_INT_FF_MT,
		.enabled_events = MMA8452_INT_TRANS |
					MMA8452_INT_FF_MT,
	पूर्ण,
पूर्ण;

अटल काष्ठा attribute *mma8452_attributes[] = अणु
	&iio_dev_attr_sampling_frequency_available.dev_attr.attr,
	&iio_dev_attr_in_accel_scale_available.dev_attr.attr,
	&iio_dev_attr_in_accel_filter_high_pass_3db_frequency_available.dev_attr.attr,
	&iio_dev_attr_in_accel_oversampling_ratio_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group mma8452_group = अणु
	.attrs = mma8452_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info mma8452_info = अणु
	.attrs = &mma8452_group,
	.पढ़ो_raw = &mma8452_पढ़ो_raw,
	.ग_लिखो_raw = &mma8452_ग_लिखो_raw,
	.event_attrs = &mma8452_event_attribute_group,
	.पढ़ो_event_value = &mma8452_पढ़ो_event_value,
	.ग_लिखो_event_value = &mma8452_ग_लिखो_event_value,
	.पढ़ो_event_config = &mma8452_पढ़ो_event_config,
	.ग_लिखो_event_config = &mma8452_ग_लिखो_event_config,
	.debugfs_reg_access = &mma8452_reg_access_dbg,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ mma8452_scan_masks[] = अणु0x7, 0पूर्ण;

अटल पूर्णांक mma8452_data_rdy_trigger_set_state(काष्ठा iio_trigger *trig,
					      bool state)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा mma8452_data *data = iio_priv(indio_dev);
	पूर्णांक reg, ret;

	ret = mma8452_set_runसमय_pm_state(data->client, state);
	अगर (ret)
		वापस ret;

	reg = i2c_smbus_पढ़ो_byte_data(data->client, MMA8452_CTRL_REG4);
	अगर (reg < 0)
		वापस reg;

	अगर (state)
		reg |= MMA8452_INT_DRDY;
	अन्यथा
		reg &= ~MMA8452_INT_DRDY;

	वापस mma8452_change_config(data, MMA8452_CTRL_REG4, reg);
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops mma8452_trigger_ops = अणु
	.set_trigger_state = mma8452_data_rdy_trigger_set_state,
	.validate_device = iio_trigger_validate_own_device,
पूर्ण;

अटल पूर्णांक mma8452_trigger_setup(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा mma8452_data *data = iio_priv(indio_dev);
	काष्ठा iio_trigger *trig;
	पूर्णांक ret;

	trig = devm_iio_trigger_alloc(&data->client->dev, "%s-dev%d",
				      indio_dev->name,
				      indio_dev->id);
	अगर (!trig)
		वापस -ENOMEM;

	trig->ops = &mma8452_trigger_ops;
	iio_trigger_set_drvdata(trig, indio_dev);

	ret = iio_trigger_रेजिस्टर(trig);
	अगर (ret)
		वापस ret;

	indio_dev->trig = trig;

	वापस 0;
पूर्ण

अटल व्योम mma8452_trigger_cleanup(काष्ठा iio_dev *indio_dev)
अणु
	अगर (indio_dev->trig)
		iio_trigger_unरेजिस्टर(indio_dev->trig);
पूर्ण

अटल पूर्णांक mma8452_reset(काष्ठा i2c_client *client)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client,	MMA8452_CTRL_REG2,
					MMA8452_CTRL_REG2_RST);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < 10; i++) अणु
		usleep_range(100, 200);
		ret = i2c_smbus_पढ़ो_byte_data(client, MMA8452_CTRL_REG2);
		अगर (ret == -EIO)
			जारी; /* I2C comm reset */
		अगर (ret < 0)
			वापस ret;
		अगर (!(ret & MMA8452_CTRL_REG2_RST))
			वापस 0;
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल स्थिर काष्ठा of_device_id mma8452_dt_ids[] = अणु
	अणु .compatible = "fsl,mma8451", .data = &mma_chip_info_table[mma8451] पूर्ण,
	अणु .compatible = "fsl,mma8452", .data = &mma_chip_info_table[mma8452] पूर्ण,
	अणु .compatible = "fsl,mma8453", .data = &mma_chip_info_table[mma8453] पूर्ण,
	अणु .compatible = "fsl,mma8652", .data = &mma_chip_info_table[mma8652] पूर्ण,
	अणु .compatible = "fsl,mma8653", .data = &mma_chip_info_table[mma8653] पूर्ण,
	अणु .compatible = "fsl,fxls8471", .data = &mma_chip_info_table[fxls8471] पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mma8452_dt_ids);

अटल पूर्णांक mma8452_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा mma8452_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;
	स्थिर काष्ठा of_device_id *match;

	match = of_match_device(mma8452_dt_ids, &client->dev);
	अगर (!match) अणु
		dev_err(&client->dev, "unknown device model\n");
		वापस -ENODEV;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	data->client = client;
	mutex_init(&data->lock);
	data->chip_info = match->data;

	data->vdd_reg = devm_regulator_get(&client->dev, "vdd");
	अगर (IS_ERR(data->vdd_reg))
		वापस dev_err_probe(&client->dev, PTR_ERR(data->vdd_reg),
				     "failed to get VDD regulator!\n");

	data->vddio_reg = devm_regulator_get(&client->dev, "vddio");
	अगर (IS_ERR(data->vddio_reg))
		वापस dev_err_probe(&client->dev, PTR_ERR(data->vddio_reg),
				     "failed to get VDDIO regulator!\n");

	ret = regulator_enable(data->vdd_reg);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to enable VDD regulator!\n");
		वापस ret;
	पूर्ण

	ret = regulator_enable(data->vddio_reg);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to enable VDDIO regulator!\n");
		जाओ disable_regulator_vdd;
	पूर्ण

	ret = i2c_smbus_पढ़ो_byte_data(client, MMA8452_WHO_AM_I);
	अगर (ret < 0)
		जाओ disable_regulators;

	चयन (ret) अणु
	हाल MMA8451_DEVICE_ID:
	हाल MMA8452_DEVICE_ID:
	हाल MMA8453_DEVICE_ID:
	हाल MMA8652_DEVICE_ID:
	हाल MMA8653_DEVICE_ID:
	हाल FXLS8471_DEVICE_ID:
		अगर (ret == data->chip_info->chip_id)
			अवरोध;
		fallthrough;
	शेष:
		ret = -ENODEV;
		जाओ disable_regulators;
	पूर्ण

	dev_info(&client->dev, "registering %s accelerometer; ID 0x%x\n",
		 match->compatible, data->chip_info->chip_id);

	i2c_set_clientdata(client, indio_dev);
	indio_dev->info = &mma8452_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = data->chip_info->channels;
	indio_dev->num_channels = data->chip_info->num_channels;
	indio_dev->available_scan_masks = mma8452_scan_masks;

	ret = mma8452_reset(client);
	अगर (ret < 0)
		जाओ disable_regulators;

	data->data_cfg = MMA8452_DATA_CFG_FS_2G;
	ret = i2c_smbus_ग_लिखो_byte_data(client, MMA8452_DATA_CFG,
					data->data_cfg);
	अगर (ret < 0)
		जाओ disable_regulators;

	/*
	 * By शेष set transient threshold to max to aव्योम events अगर
	 * enabling without configuring threshold.
	 */
	ret = i2c_smbus_ग_लिखो_byte_data(client, MMA8452_TRANSIENT_THS,
					MMA8452_TRANSIENT_THS_MASK);
	अगर (ret < 0)
		जाओ disable_regulators;

	अगर (client->irq) अणु
		पूर्णांक irq2;

		irq2 = of_irq_get_byname(client->dev.of_node, "INT2");

		अगर (irq2 == client->irq) अणु
			dev_dbg(&client->dev, "using interrupt line INT2\n");
		पूर्ण अन्यथा अणु
			ret = i2c_smbus_ग_लिखो_byte_data(client,
						MMA8452_CTRL_REG5,
						data->chip_info->all_events);
			अगर (ret < 0)
				जाओ disable_regulators;

			dev_dbg(&client->dev, "using interrupt line INT1\n");
		पूर्ण

		ret = i2c_smbus_ग_लिखो_byte_data(client,
					MMA8452_CTRL_REG4,
					data->chip_info->enabled_events);
		अगर (ret < 0)
			जाओ disable_regulators;

		ret = mma8452_trigger_setup(indio_dev);
		अगर (ret < 0)
			जाओ disable_regulators;
	पूर्ण

	data->ctrl_reg1 = MMA8452_CTRL_ACTIVE |
			  (MMA8452_CTRL_DR_DEFAULT << MMA8452_CTRL_DR_SHIFT);

	data->sleep_val = mma8452_calculate_sleep(data);

	ret = i2c_smbus_ग_लिखो_byte_data(client, MMA8452_CTRL_REG1,
					data->ctrl_reg1);
	अगर (ret < 0)
		जाओ trigger_cleanup;

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
					 mma8452_trigger_handler, शून्य);
	अगर (ret < 0)
		जाओ trigger_cleanup;

	अगर (client->irq) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev,
						client->irq,
						शून्य, mma8452_पूर्णांकerrupt,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						client->name, indio_dev);
		अगर (ret)
			जाओ buffer_cleanup;
	पूर्ण

	ret = pm_runसमय_set_active(&client->dev);
	अगर (ret < 0)
		जाओ buffer_cleanup;

	pm_runसमय_enable(&client->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&client->dev,
					 MMA8452_AUTO_SUSPEND_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(&client->dev);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0)
		जाओ buffer_cleanup;

	ret = mma8452_set_मुक्तfall_mode(data, false);
	अगर (ret < 0)
		जाओ unरेजिस्टर_device;

	वापस 0;

unरेजिस्टर_device:
	iio_device_unरेजिस्टर(indio_dev);

buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);

trigger_cleanup:
	mma8452_trigger_cleanup(indio_dev);

disable_regulators:
	regulator_disable(data->vddio_reg);

disable_regulator_vdd:
	regulator_disable(data->vdd_reg);

	वापस ret;
पूर्ण

अटल पूर्णांक mma8452_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा mma8452_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);
	pm_runसमय_put_noidle(&client->dev);

	iio_triggered_buffer_cleanup(indio_dev);
	mma8452_trigger_cleanup(indio_dev);
	mma8452_standby(iio_priv(indio_dev));

	regulator_disable(data->vddio_reg);
	regulator_disable(data->vdd_reg);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mma8452_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा mma8452_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = mma8452_standby(data);
	mutex_unlock(&data->lock);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "powering off device failed\n");
		वापस -EAGAIN;
	पूर्ण

	ret = regulator_disable(data->vddio_reg);
	अगर (ret) अणु
		dev_err(dev, "failed to disable VDDIO regulator\n");
		वापस ret;
	पूर्ण

	ret = regulator_disable(data->vdd_reg);
	अगर (ret) अणु
		dev_err(dev, "failed to disable VDD regulator\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mma8452_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा mma8452_data *data = iio_priv(indio_dev);
	पूर्णांक ret, sleep_val;

	ret = regulator_enable(data->vdd_reg);
	अगर (ret) अणु
		dev_err(dev, "failed to enable VDD regulator\n");
		वापस ret;
	पूर्ण

	ret = regulator_enable(data->vddio_reg);
	अगर (ret) अणु
		dev_err(dev, "failed to enable VDDIO regulator\n");
		regulator_disable(data->vdd_reg);
		वापस ret;
	पूर्ण

	ret = mma8452_active(data);
	अगर (ret < 0)
		जाओ runसमय_resume_failed;

	ret = mma8452_get_odr_index(data);
	sleep_val = 1000 / mma8452_samp_freq[ret][0];
	अगर (sleep_val < 20)
		usleep_range(sleep_val * 1000, 20000);
	अन्यथा
		msleep_पूर्णांकerruptible(sleep_val);

	वापस 0;

runसमय_resume_failed:
	regulator_disable(data->vddio_reg);
	regulator_disable(data->vdd_reg);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops mma8452_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend, pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(mma8452_runसमय_suspend,
			   mma8452_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id mma8452_id[] = अणु
	अणु "mma8451", mma8451 पूर्ण,
	अणु "mma8452", mma8452 पूर्ण,
	अणु "mma8453", mma8453 पूर्ण,
	अणु "mma8652", mma8652 पूर्ण,
	अणु "mma8653", mma8653 पूर्ण,
	अणु "fxls8471", fxls8471 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mma8452_id);

अटल काष्ठा i2c_driver mma8452_driver = अणु
	.driver = अणु
		.name	= "mma8452",
		.of_match_table = of_match_ptr(mma8452_dt_ids),
		.pm	= &mma8452_pm_ops,
	पूर्ण,
	.probe = mma8452_probe,
	.हटाओ = mma8452_हटाओ,
	.id_table = mma8452_id,
पूर्ण;
module_i2c_driver(mma8452_driver);

MODULE_AUTHOR("Peter Meerwald <pmeerw@pmeerw.net>");
MODULE_DESCRIPTION("Freescale / NXP MMA8452 accelerometer driver");
MODULE_LICENSE("GPL");
