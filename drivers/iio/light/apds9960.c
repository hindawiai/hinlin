<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * apds9960.c - Support क्रम Avago APDS9960 gesture/RGB/ALS/proximity sensor
 *
 * Copyright (C) 2015, 2018
 * Author: Matt Ranostay <matt.ranostay@konsulko.com>
 *
 * TODO: gesture + proximity calib offsets
 */

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/err.h>
#समावेश <linux/irq.h>
#समावेश <linux/i2c.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/kfअगरo_buf.h>
#समावेश <linux/iio/sysfs.h>

#घोषणा APDS9960_REGMAP_NAME	"apds9960_regmap"
#घोषणा APDS9960_DRV_NAME	"apds9960"

#घोषणा APDS9960_REG_RAM_START	0x00
#घोषणा APDS9960_REG_RAM_END	0x7f

#घोषणा APDS9960_REG_ENABLE	0x80
#घोषणा APDS9960_REG_ATIME	0x81
#घोषणा APDS9960_REG_WTIME	0x83

#घोषणा APDS9960_REG_AILTL	0x84
#घोषणा APDS9960_REG_AILTH	0x85
#घोषणा APDS9960_REG_AIHTL	0x86
#घोषणा APDS9960_REG_AIHTH	0x87

#घोषणा APDS9960_REG_PILT	0x89
#घोषणा APDS9960_REG_PIHT	0x8b
#घोषणा APDS9960_REG_PERS	0x8c

#घोषणा APDS9960_REG_CONFIG_1	0x8d
#घोषणा APDS9960_REG_PPULSE	0x8e

#घोषणा APDS9960_REG_CONTROL	0x8f
#घोषणा APDS9960_REG_CONTROL_AGAIN_MASK		0x03
#घोषणा APDS9960_REG_CONTROL_PGAIN_MASK		0x0c
#घोषणा APDS9960_REG_CONTROL_AGAIN_MASK_SHIFT	0
#घोषणा APDS9960_REG_CONTROL_PGAIN_MASK_SHIFT	2

#घोषणा APDS9960_REG_CONFIG_2	0x90
#घोषणा APDS9960_REG_CONFIG_2_GGAIN_MASK	0x60
#घोषणा APDS9960_REG_CONFIG_2_GGAIN_MASK_SHIFT	5

#घोषणा APDS9960_REG_ID		0x92

#घोषणा APDS9960_REG_STATUS	0x93
#घोषणा APDS9960_REG_STATUS_PS_INT	BIT(5)
#घोषणा APDS9960_REG_STATUS_ALS_INT	BIT(4)
#घोषणा APDS9960_REG_STATUS_GINT	BIT(2)

#घोषणा APDS9960_REG_PDATA	0x9c
#घोषणा APDS9960_REG_POFFSET_UR	0x9d
#घोषणा APDS9960_REG_POFFSET_DL 0x9e
#घोषणा APDS9960_REG_CONFIG_3	0x9f

#घोषणा APDS9960_REG_GPENTH	0xa0
#घोषणा APDS9960_REG_GEXTH	0xa1

#घोषणा APDS9960_REG_GCONF_1	0xa2
#घोषणा APDS9960_REG_GCONF_1_GFIFO_THRES_MASK		0xc0
#घोषणा APDS9960_REG_GCONF_1_GFIFO_THRES_MASK_SHIFT	6

#घोषणा APDS9960_REG_GCONF_2	0xa3
#घोषणा APDS9960_REG_GOFFSET_U	0xa4
#घोषणा APDS9960_REG_GOFFSET_D	0xa5
#घोषणा APDS9960_REG_GPULSE	0xa6
#घोषणा APDS9960_REG_GOFFSET_L	0xa7
#घोषणा APDS9960_REG_GOFFSET_R	0xa9
#घोषणा APDS9960_REG_GCONF_3	0xaa

#घोषणा APDS9960_REG_GCONF_4	0xab
#घोषणा APDS9960_REG_GFLVL	0xae
#घोषणा APDS9960_REG_GSTATUS	0xaf

#घोषणा APDS9960_REG_IFORCE	0xe4
#घोषणा APDS9960_REG_PICLEAR	0xe5
#घोषणा APDS9960_REG_CICLEAR	0xe6
#घोषणा APDS9960_REG_AICLEAR	0xe7

#घोषणा APDS9960_DEFAULT_PERS	0x33
#घोषणा APDS9960_DEFAULT_GPENTH	0x50
#घोषणा APDS9960_DEFAULT_GEXTH	0x40

#घोषणा APDS9960_MAX_PXS_THRES_VAL	255
#घोषणा APDS9960_MAX_ALS_THRES_VAL	0xffff
#घोषणा APDS9960_MAX_INT_TIME_IN_US	1000000

क्रमागत apds9960_als_channel_idx अणु
	IDX_ALS_CLEAR, IDX_ALS_RED, IDX_ALS_GREEN, IDX_ALS_BLUE,
पूर्ण;

#घोषणा APDS9960_REG_ALS_BASE	0x94
#घोषणा APDS9960_REG_ALS_CHANNEL(_colour) \
	(APDS9960_REG_ALS_BASE + (IDX_ALS_##_colour * 2))

क्रमागत apds9960_gesture_channel_idx अणु
	IDX_सूची_UP, IDX_सूची_DOWN, IDX_सूची_LEFT, IDX_सूची_RIGHT,
पूर्ण;

#घोषणा APDS9960_REG_GFIFO_BASE	0xfc
#घोषणा APDS9960_REG_GFIFO_सूची(_dir) \
	(APDS9960_REG_GFIFO_BASE + IDX_सूची_##_dir)

काष्ठा apds9960_data अणु
	काष्ठा i2c_client *client;
	काष्ठा iio_dev *indio_dev;
	काष्ठा mutex lock;

	/* regmap fields */
	काष्ठा regmap *regmap;
	काष्ठा regmap_field *reg_पूर्णांक_als;
	काष्ठा regmap_field *reg_पूर्णांक_ges;
	काष्ठा regmap_field *reg_पूर्णांक_pxs;

	काष्ठा regmap_field *reg_enable_als;
	काष्ठा regmap_field *reg_enable_ges;
	काष्ठा regmap_field *reg_enable_pxs;

	/* state */
	पूर्णांक als_पूर्णांक;
	पूर्णांक pxs_पूर्णांक;
	पूर्णांक gesture_mode_running;

	/* gain values */
	पूर्णांक als_gain;
	पूर्णांक pxs_gain;

	/* पूर्णांकegration समय value in us */
	पूर्णांक als_adc_पूर्णांक_us;

	/* gesture buffer */
	u8 buffer[4]; /* 4 8-bit channels */
पूर्ण;

अटल स्थिर काष्ठा reg_शेष apds9960_reg_शेषs[] = अणु
	/* Default ALS पूर्णांकegration समय = 2.48ms */
	अणु APDS9960_REG_ATIME, 0xff पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range apds9960_अस्थिर_ranges[] = अणु
	regmap_reg_range(APDS9960_REG_STATUS,
				APDS9960_REG_PDATA),
	regmap_reg_range(APDS9960_REG_GFLVL,
				APDS9960_REG_GSTATUS),
	regmap_reg_range(APDS9960_REG_GFIFO_सूची(UP),
				APDS9960_REG_GFIFO_सूची(RIGHT)),
	regmap_reg_range(APDS9960_REG_IFORCE,
				APDS9960_REG_AICLEAR),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table apds9960_अस्थिर_table = अणु
	.yes_ranges	= apds9960_अस्थिर_ranges,
	.n_yes_ranges	= ARRAY_SIZE(apds9960_अस्थिर_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range apds9960_precious_ranges[] = अणु
	regmap_reg_range(APDS9960_REG_RAM_START, APDS9960_REG_RAM_END),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table apds9960_precious_table = अणु
	.yes_ranges	= apds9960_precious_ranges,
	.n_yes_ranges	= ARRAY_SIZE(apds9960_precious_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range apds9960_पढ़ोable_ranges[] = अणु
	regmap_reg_range(APDS9960_REG_ENABLE,
				APDS9960_REG_GSTATUS),
	regmap_reg_range(APDS9960_REG_GFIFO_सूची(UP),
				APDS9960_REG_GFIFO_सूची(RIGHT)),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table apds9960_पढ़ोable_table = अणु
	.yes_ranges	= apds9960_पढ़ोable_ranges,
	.n_yes_ranges	= ARRAY_SIZE(apds9960_पढ़ोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range apds9960_ग_लिखोable_ranges[] = अणु
	regmap_reg_range(APDS9960_REG_ENABLE, APDS9960_REG_CONFIG_2),
	regmap_reg_range(APDS9960_REG_POFFSET_UR, APDS9960_REG_GCONF_4),
	regmap_reg_range(APDS9960_REG_IFORCE, APDS9960_REG_AICLEAR),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table apds9960_ग_लिखोable_table = अणु
	.yes_ranges	= apds9960_ग_लिखोable_ranges,
	.n_yes_ranges	= ARRAY_SIZE(apds9960_ग_लिखोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config apds9960_regmap_config = अणु
	.name = APDS9960_REGMAP_NAME,
	.reg_bits = 8,
	.val_bits = 8,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,

	.अस्थिर_table = &apds9960_अस्थिर_table,
	.precious_table = &apds9960_precious_table,
	.rd_table = &apds9960_पढ़ोable_table,
	.wr_table = &apds9960_ग_लिखोable_table,

	.reg_शेषs = apds9960_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(apds9960_reg_शेषs),
	.max_रेजिस्टर = APDS9960_REG_GFIFO_सूची(RIGHT),
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec apds9960_pxs_event_spec[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec apds9960_als_event_spec[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

#घोषणा APDS9960_GESTURE_CHANNEL(_dir, _si) अणु \
	.type = IIO_PROXIMITY, \
	.channel = _si + 1, \
	.scan_index = _si, \
	.indexed = 1, \
	.scan_type = अणु \
		.sign = 'u', \
		.realbits = 8, \
		.storagebits = 8, \
	पूर्ण, \
पूर्ण

#घोषणा APDS9960_INTENSITY_CHANNEL(_colour) अणु \
	.type = IIO_INTENSITY, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) | \
			BIT(IIO_CHAN_INFO_INT_TIME), \
	.channel2 = IIO_MOD_LIGHT_##_colour, \
	.address = APDS9960_REG_ALS_CHANNEL(_colour), \
	.modअगरied = 1, \
	.scan_index = -1, \
पूर्ण

अटल स्थिर अचिन्हित दीर्घ apds9960_scan_masks[] = अणु0xf, 0पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec apds9960_channels[] = अणु
	अणु
		.type = IIO_PROXIMITY,
		.address = APDS9960_REG_PDATA,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),
		.channel = 0,
		.indexed = 0,
		.scan_index = -1,

		.event_spec = apds9960_pxs_event_spec,
		.num_event_specs = ARRAY_SIZE(apds9960_pxs_event_spec),
	पूर्ण,
	/* Gesture Sensor */
	APDS9960_GESTURE_CHANNEL(UP, 0),
	APDS9960_GESTURE_CHANNEL(DOWN, 1),
	APDS9960_GESTURE_CHANNEL(LEFT, 2),
	APDS9960_GESTURE_CHANNEL(RIGHT, 3),
	/* ALS */
	अणु
		.type = IIO_INTENSITY,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_INT_TIME),
		.channel2 = IIO_MOD_LIGHT_CLEAR,
		.address = APDS9960_REG_ALS_CHANNEL(CLEAR),
		.modअगरied = 1,
		.scan_index = -1,

		.event_spec = apds9960_als_event_spec,
		.num_event_specs = ARRAY_SIZE(apds9960_als_event_spec),
	पूर्ण,
	/* RGB Sensor */
	APDS9960_INTENSITY_CHANNEL(RED),
	APDS9960_INTENSITY_CHANNEL(GREEN),
	APDS9960_INTENSITY_CHANNEL(BLUE),
पूर्ण;

/* पूर्णांकegration समय in us */
अटल स्थिर पूर्णांक apds9960_पूर्णांक_समय[][2] = अणु
	अणु 28000, 246पूर्ण,
	अणु100000, 219पूर्ण,
	अणु200000, 182पूर्ण,
	अणु700000,   0पूर्ण
पूर्ण;

/* gain mapping */
अटल स्थिर पूर्णांक apds9960_pxs_gain_map[] = अणु1, 2, 4, 8पूर्ण;
अटल स्थिर पूर्णांक apds9960_als_gain_map[] = अणु1, 4, 16, 64पूर्ण;

अटल IIO_CONST_ATTR(proximity_scale_available, "1 2 4 8");
अटल IIO_CONST_ATTR(पूर्णांकensity_scale_available, "1 4 16 64");
अटल IIO_CONST_ATTR_INT_TIME_AVAIL("0.028 0.1 0.2 0.7");

अटल काष्ठा attribute *apds9960_attributes[] = अणु
	&iio_स्थिर_attr_proximity_scale_available.dev_attr.attr,
	&iio_स्थिर_attr_पूर्णांकensity_scale_available.dev_attr.attr,
	&iio_स्थिर_attr_पूर्णांकegration_समय_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group apds9960_attribute_group = अणु
	.attrs = apds9960_attributes,
पूर्ण;

अटल स्थिर काष्ठा reg_field apds9960_reg_field_पूर्णांक_als =
				REG_FIELD(APDS9960_REG_ENABLE, 4, 4);

अटल स्थिर काष्ठा reg_field apds9960_reg_field_पूर्णांक_ges =
				REG_FIELD(APDS9960_REG_GCONF_4, 1, 1);

अटल स्थिर काष्ठा reg_field apds9960_reg_field_पूर्णांक_pxs =
				REG_FIELD(APDS9960_REG_ENABLE, 5, 5);

अटल स्थिर काष्ठा reg_field apds9960_reg_field_enable_als =
				REG_FIELD(APDS9960_REG_ENABLE, 1, 1);

अटल स्थिर काष्ठा reg_field apds9960_reg_field_enable_ges =
				REG_FIELD(APDS9960_REG_ENABLE, 6, 6);

अटल स्थिर काष्ठा reg_field apds9960_reg_field_enable_pxs =
				REG_FIELD(APDS9960_REG_ENABLE, 2, 2);

अटल पूर्णांक apds9960_set_it_समय(काष्ठा apds9960_data *data, पूर्णांक val2)
अणु
	पूर्णांक ret = -EINVAL;
	पूर्णांक idx;

	क्रम (idx = 0; idx < ARRAY_SIZE(apds9960_पूर्णांक_समय); idx++) अणु
		अगर (apds9960_पूर्णांक_समय[idx][0] == val2) अणु
			mutex_lock(&data->lock);
			ret = regmap_ग_लिखो(data->regmap, APDS9960_REG_ATIME,
						 apds9960_पूर्णांक_समय[idx][1]);
			अगर (!ret)
				data->als_adc_पूर्णांक_us = val2;
			mutex_unlock(&data->lock);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक apds9960_set_pxs_gain(काष्ठा apds9960_data *data, पूर्णांक val)
अणु
	पूर्णांक ret = -EINVAL;
	पूर्णांक idx;

	क्रम (idx = 0; idx < ARRAY_SIZE(apds9960_pxs_gain_map); idx++) अणु
		अगर (apds9960_pxs_gain_map[idx] == val) अणु
			/* pxs + gesture gains are mirrored */
			mutex_lock(&data->lock);
			ret = regmap_update_bits(data->regmap,
				APDS9960_REG_CONTROL,
				APDS9960_REG_CONTROL_PGAIN_MASK,
				idx << APDS9960_REG_CONTROL_PGAIN_MASK_SHIFT);
			अगर (ret) अणु
				mutex_unlock(&data->lock);
				अवरोध;
			पूर्ण

			ret = regmap_update_bits(data->regmap,
				APDS9960_REG_CONFIG_2,
				APDS9960_REG_CONFIG_2_GGAIN_MASK,
				idx << APDS9960_REG_CONFIG_2_GGAIN_MASK_SHIFT);
			अगर (!ret)
				data->pxs_gain = idx;
			mutex_unlock(&data->lock);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक apds9960_set_als_gain(काष्ठा apds9960_data *data, पूर्णांक val)
अणु
	पूर्णांक ret = -EINVAL;
	पूर्णांक idx;

	क्रम (idx = 0; idx < ARRAY_SIZE(apds9960_als_gain_map); idx++) अणु
		अगर (apds9960_als_gain_map[idx] == val) अणु
			mutex_lock(&data->lock);
			ret = regmap_update_bits(data->regmap,
					APDS9960_REG_CONTROL,
					APDS9960_REG_CONTROL_AGAIN_MASK, idx);
			अगर (!ret)
				data->als_gain = idx;
			mutex_unlock(&data->lock);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक apds9960_set_घातer_state(काष्ठा apds9960_data *data, bool on)
अणु
	काष्ठा device *dev = &data->client->dev;
	पूर्णांक ret = 0;

	mutex_lock(&data->lock);

	अगर (on) अणु
		पूर्णांक suspended;

		suspended = pm_runसमय_suspended(dev);
		ret = pm_runसमय_get_sync(dev);

		/* Allow one पूर्णांकegration cycle beक्रमe allowing a पढ़ोing */
		अगर (suspended)
			usleep_range(data->als_adc_पूर्णांक_us,
				     APDS9960_MAX_INT_TIME_IN_US);
	पूर्ण अन्यथा अणु
		pm_runसमय_mark_last_busy(dev);
		ret = pm_runसमय_put_स्वतःsuspend(dev);
	पूर्ण

	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण
#अन्यथा
अटल पूर्णांक apds9960_set_घातer_state(काष्ठा apds9960_data *data, bool on)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक apds9960_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा apds9960_data *data = iio_priv(indio_dev);
	__le16 buf;
	पूर्णांक ret = -EINVAL;

	अगर (data->gesture_mode_running)
		वापस -EBUSY;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		apds9960_set_घातer_state(data, true);
		चयन (chan->type) अणु
		हाल IIO_PROXIMITY:
			ret = regmap_पढ़ो(data->regmap, chan->address, val);
			अगर (!ret)
				ret = IIO_VAL_INT;
			अवरोध;
		हाल IIO_INTENSITY:
			ret = regmap_bulk_पढ़ो(data->regmap, chan->address,
					       &buf, 2);
			अगर (!ret) अणु
				ret = IIO_VAL_INT;
				*val = le16_to_cpu(buf);
			पूर्ण
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
		apds9960_set_घातer_state(data, false);
		अवरोध;
	हाल IIO_CHAN_INFO_INT_TIME:
		/* RGB + ALS sensors only have पूर्णांकegration समय */
		mutex_lock(&data->lock);
		चयन (chan->type) अणु
		हाल IIO_INTENSITY:
			*val = 0;
			*val2 = data->als_adc_पूर्णांक_us;
			ret = IIO_VAL_INT_PLUS_MICRO;
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
		mutex_unlock(&data->lock);
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		mutex_lock(&data->lock);
		चयन (chan->type) अणु
		हाल IIO_PROXIMITY:
			*val = apds9960_pxs_gain_map[data->pxs_gain];
			ret = IIO_VAL_INT;
			अवरोध;
		हाल IIO_INTENSITY:
			*val = apds9960_als_gain_map[data->als_gain];
			ret = IIO_VAL_INT;
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
		mutex_unlock(&data->lock);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण;

अटल पूर्णांक apds9960_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा apds9960_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_INT_TIME:
		/* RGB + ALS sensors only have पूर्णांक समय */
		चयन (chan->type) अणु
		हाल IIO_INTENSITY:
			अगर (val != 0)
				वापस -EINVAL;
			वापस apds9960_set_it_समय(data, val2);
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SCALE:
		अगर (val2 != 0)
			वापस -EINVAL;
		चयन (chan->type) अणु
		हाल IIO_PROXIMITY:
			वापस apds9960_set_pxs_gain(data, val);
		हाल IIO_INTENSITY:
			वापस apds9960_set_als_gain(data, val);
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक apds9960_get_thres_reg(स्थिर काष्ठा iio_chan_spec *chan,
					 क्रमागत iio_event_direction dir,
					 u8 *reg)
अणु
	चयन (dir) अणु
	हाल IIO_EV_सूची_RISING:
		चयन (chan->type) अणु
		हाल IIO_PROXIMITY:
			*reg = APDS9960_REG_PIHT;
			अवरोध;
		हाल IIO_INTENSITY:
			*reg = APDS9960_REG_AIHTL;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल IIO_EV_सूची_FALLING:
		चयन (chan->type) अणु
		हाल IIO_PROXIMITY:
			*reg = APDS9960_REG_PILT;
			अवरोध;
		हाल IIO_INTENSITY:
			*reg = APDS9960_REG_AILTL;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक apds9960_पढ़ो_event(काष्ठा iio_dev *indio_dev,
			       स्थिर काष्ठा iio_chan_spec *chan,
			       क्रमागत iio_event_type type,
			       क्रमागत iio_event_direction dir,
			       क्रमागत iio_event_info info,
			       पूर्णांक *val, पूर्णांक *val2)
अणु
	u8 reg;
	__le16 buf;
	पूर्णांक ret = 0;
	काष्ठा apds9960_data *data = iio_priv(indio_dev);

	अगर (info != IIO_EV_INFO_VALUE)
		वापस -EINVAL;

	ret = apds9960_get_thres_reg(chan, dir, &reg);
	अगर (ret < 0)
		वापस ret;

	अगर (chan->type == IIO_PROXIMITY) अणु
		ret = regmap_पढ़ो(data->regmap, reg, val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर (chan->type == IIO_INTENSITY) अणु
		ret = regmap_bulk_पढ़ो(data->regmap, reg, &buf, 2);
		अगर (ret < 0)
			वापस ret;
		*val = le16_to_cpu(buf);
	पूर्ण अन्यथा
		वापस -EINVAL;

	*val2 = 0;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक apds9960_ग_लिखो_event(काष्ठा iio_dev *indio_dev,
				स्थिर काष्ठा iio_chan_spec *chan,
				क्रमागत iio_event_type type,
				क्रमागत iio_event_direction dir,
				क्रमागत iio_event_info info,
				पूर्णांक val, पूर्णांक val2)
अणु
	u8 reg;
	__le16 buf;
	पूर्णांक ret = 0;
	काष्ठा apds9960_data *data = iio_priv(indio_dev);

	अगर (info != IIO_EV_INFO_VALUE)
		वापस -EINVAL;

	ret = apds9960_get_thres_reg(chan, dir, &reg);
	अगर (ret < 0)
		वापस ret;

	अगर (chan->type == IIO_PROXIMITY) अणु
		अगर (val < 0 || val > APDS9960_MAX_PXS_THRES_VAL)
			वापस -EINVAL;
		ret = regmap_ग_लिखो(data->regmap, reg, val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर (chan->type == IIO_INTENSITY) अणु
		अगर (val < 0 || val > APDS9960_MAX_ALS_THRES_VAL)
			वापस -EINVAL;
		buf = cpu_to_le16(val);
		ret = regmap_bulk_ग_लिखो(data->regmap, reg, &buf, 2);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक apds9960_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
				      स्थिर काष्ठा iio_chan_spec *chan,
				      क्रमागत iio_event_type type,
				      क्रमागत iio_event_direction dir)
अणु
	काष्ठा apds9960_data *data = iio_priv(indio_dev);

	चयन (chan->type) अणु
	हाल IIO_PROXIMITY:
		वापस data->pxs_पूर्णांक;
	हाल IIO_INTENSITY:
		वापस data->als_पूर्णांक;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक apds9960_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
				       स्थिर काष्ठा iio_chan_spec *chan,
				       क्रमागत iio_event_type type,
				       क्रमागत iio_event_direction dir,
				       पूर्णांक state)
अणु
	काष्ठा apds9960_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	state = !!state;

	चयन (chan->type) अणु
	हाल IIO_PROXIMITY:
		अगर (data->pxs_पूर्णांक == state)
			वापस -EINVAL;

		ret = regmap_field_ग_लिखो(data->reg_पूर्णांक_pxs, state);
		अगर (ret)
			वापस ret;
		data->pxs_पूर्णांक = state;
		apds9960_set_घातer_state(data, state);
		अवरोध;
	हाल IIO_INTENSITY:
		अगर (data->als_पूर्णांक == state)
			वापस -EINVAL;

		ret = regmap_field_ग_लिखो(data->reg_पूर्णांक_als, state);
		अगर (ret)
			वापस ret;
		data->als_पूर्णांक = state;
		apds9960_set_घातer_state(data, state);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_info apds9960_info = अणु
	.attrs = &apds9960_attribute_group,
	.पढ़ो_raw = apds9960_पढ़ो_raw,
	.ग_लिखो_raw = apds9960_ग_लिखो_raw,
	.पढ़ो_event_value = apds9960_पढ़ो_event,
	.ग_लिखो_event_value = apds9960_ग_लिखो_event,
	.पढ़ो_event_config = apds9960_पढ़ो_event_config,
	.ग_लिखो_event_config = apds9960_ग_लिखो_event_config,

पूर्ण;

अटल अंतरभूत पूर्णांक apds9660_fअगरo_is_empty(काष्ठा apds9960_data *data)
अणु
	पूर्णांक cnt;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, APDS9960_REG_GFLVL, &cnt);
	अगर (ret)
		वापस ret;

	वापस cnt;
पूर्ण

अटल व्योम apds9960_पढ़ो_gesture_fअगरo(काष्ठा apds9960_data *data)
अणु
	पूर्णांक ret, cnt = 0;

	mutex_lock(&data->lock);
	data->gesture_mode_running = 1;

	जबतक (cnt || (cnt = apds9660_fअगरo_is_empty(data) > 0)) अणु
		ret = regmap_bulk_पढ़ो(data->regmap, APDS9960_REG_GFIFO_BASE,
				      &data->buffer, 4);

		अगर (ret)
			जाओ err_पढ़ो;

		iio_push_to_buffers(data->indio_dev, data->buffer);
		cnt--;
	पूर्ण

err_पढ़ो:
	data->gesture_mode_running = 0;
	mutex_unlock(&data->lock);
पूर्ण

अटल irqवापस_t apds9960_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा apds9960_data *data = iio_priv(indio_dev);
	पूर्णांक ret, status;

	ret = regmap_पढ़ो(data->regmap, APDS9960_REG_STATUS, &status);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "irq status reg read failed\n");
		वापस IRQ_HANDLED;
	पूर्ण

	अगर ((status & APDS9960_REG_STATUS_ALS_INT) && data->als_पूर्णांक) अणु
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_INTENSITY, 0,
						    IIO_EV_TYPE_THRESH,
						    IIO_EV_सूची_EITHER),
			       iio_get_समय_ns(indio_dev));
		regmap_ग_लिखो(data->regmap, APDS9960_REG_CICLEAR, 1);
	पूर्ण

	अगर ((status & APDS9960_REG_STATUS_PS_INT) && data->pxs_पूर्णांक) अणु
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_PROXIMITY, 0,
						    IIO_EV_TYPE_THRESH,
						    IIO_EV_सूची_EITHER),
			       iio_get_समय_ns(indio_dev));
		regmap_ग_लिखो(data->regmap, APDS9960_REG_PICLEAR, 1);
	पूर्ण

	अगर (status & APDS9960_REG_STATUS_GINT)
		apds9960_पढ़ो_gesture_fअगरo(data);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक apds9960_set_घातermode(काष्ठा apds9960_data *data, bool state)
अणु
	वापस regmap_update_bits(data->regmap, APDS9960_REG_ENABLE, 1, state);
पूर्ण

अटल पूर्णांक apds9960_buffer_postenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा apds9960_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = regmap_field_ग_लिखो(data->reg_पूर्णांक_ges, 1);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(data->reg_enable_ges, 1);
	अगर (ret)
		वापस ret;

	pm_runसमय_get_sync(&data->client->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक apds9960_buffer_predisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा apds9960_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = regmap_field_ग_लिखो(data->reg_enable_ges, 0);
	अगर (ret)
		वापस ret;

	ret = regmap_field_ग_लिखो(data->reg_पूर्णांक_ges, 0);
	अगर (ret)
		वापस ret;

	pm_runसमय_put_स्वतःsuspend(&data->client->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops apds9960_buffer_setup_ops = अणु
	.postenable = apds9960_buffer_postenable,
	.predisable = apds9960_buffer_predisable,
पूर्ण;

अटल पूर्णांक apds9960_regfield_init(काष्ठा apds9960_data *data)
अणु
	काष्ठा device *dev = &data->client->dev;
	काष्ठा regmap *regmap = data->regmap;

	data->reg_पूर्णांक_als = devm_regmap_field_alloc(dev, regmap,
						apds9960_reg_field_पूर्णांक_als);
	अगर (IS_ERR(data->reg_पूर्णांक_als)) अणु
		dev_err(dev, "INT ALS reg field init failed\n");
		वापस PTR_ERR(data->reg_पूर्णांक_als);
	पूर्ण

	data->reg_पूर्णांक_ges = devm_regmap_field_alloc(dev, regmap,
						apds9960_reg_field_पूर्णांक_ges);
	अगर (IS_ERR(data->reg_पूर्णांक_ges)) अणु
		dev_err(dev, "INT gesture reg field init failed\n");
		वापस PTR_ERR(data->reg_पूर्णांक_ges);
	पूर्ण

	data->reg_पूर्णांक_pxs = devm_regmap_field_alloc(dev, regmap,
						apds9960_reg_field_पूर्णांक_pxs);
	अगर (IS_ERR(data->reg_पूर्णांक_pxs)) अणु
		dev_err(dev, "INT pxs reg field init failed\n");
		वापस PTR_ERR(data->reg_पूर्णांक_pxs);
	पूर्ण

	data->reg_enable_als = devm_regmap_field_alloc(dev, regmap,
						apds9960_reg_field_enable_als);
	अगर (IS_ERR(data->reg_enable_als)) अणु
		dev_err(dev, "Enable ALS reg field init failed\n");
		वापस PTR_ERR(data->reg_enable_als);
	पूर्ण

	data->reg_enable_ges = devm_regmap_field_alloc(dev, regmap,
						apds9960_reg_field_enable_ges);
	अगर (IS_ERR(data->reg_enable_ges)) अणु
		dev_err(dev, "Enable gesture reg field init failed\n");
		वापस PTR_ERR(data->reg_enable_ges);
	पूर्ण

	data->reg_enable_pxs = devm_regmap_field_alloc(dev, regmap,
						apds9960_reg_field_enable_pxs);
	अगर (IS_ERR(data->reg_enable_pxs)) अणु
		dev_err(dev, "Enable PXS reg field init failed\n");
		वापस PTR_ERR(data->reg_enable_pxs);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक apds9960_chip_init(काष्ठा apds9960_data *data)
अणु
	पूर्णांक ret;

	/* Default IT क्रम ALS of 28 ms */
	ret = apds9960_set_it_समय(data, 28000);
	अगर (ret)
		वापस ret;

	/* Ensure gesture पूर्णांकerrupt is OFF */
	ret = regmap_field_ग_लिखो(data->reg_पूर्णांक_ges, 0);
	अगर (ret)
		वापस ret;

	/* Disable gesture sensor, since polling is useless from user-space */
	ret = regmap_field_ग_लिखो(data->reg_enable_ges, 0);
	अगर (ret)
		वापस ret;

	/* Ensure proximity पूर्णांकerrupt is OFF */
	ret = regmap_field_ग_लिखो(data->reg_पूर्णांक_pxs, 0);
	अगर (ret)
		वापस ret;

	/* Enable proximity sensor क्रम polling */
	ret = regmap_field_ग_लिखो(data->reg_enable_pxs, 1);
	अगर (ret)
		वापस ret;

	/* Ensure ALS पूर्णांकerrupt is OFF */
	ret = regmap_field_ग_लिखो(data->reg_पूर्णांक_als, 0);
	अगर (ret)
		वापस ret;

	/* Enable ALS sensor क्रम polling */
	ret = regmap_field_ग_लिखो(data->reg_enable_als, 1);
	अगर (ret)
		वापस ret;
	/*
	 * When enabled trigger an पूर्णांकerrupt after 3 पढ़ोings
	 * outside threshold क्रम ALS + PXS
	 */
	ret = regmap_ग_लिखो(data->regmap, APDS9960_REG_PERS,
			   APDS9960_DEFAULT_PERS);
	अगर (ret)
		वापस ret;

	/*
	 * Wait क्रम 4 event outside gesture threshold to prevent पूर्णांकerrupt
	 * flooding.
	 */
	ret = regmap_update_bits(data->regmap, APDS9960_REG_GCONF_1,
			APDS9960_REG_GCONF_1_GFIFO_THRES_MASK,
			BIT(0) << APDS9960_REG_GCONF_1_GFIFO_THRES_MASK_SHIFT);
	अगर (ret)
		वापस ret;

	/* Default ENTER and EXIT thresholds क्रम the GESTURE engine. */
	ret = regmap_ग_लिखो(data->regmap, APDS9960_REG_GPENTH,
			   APDS9960_DEFAULT_GPENTH);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(data->regmap, APDS9960_REG_GEXTH,
			   APDS9960_DEFAULT_GEXTH);
	अगर (ret)
		वापस ret;

	वापस apds9960_set_घातermode(data, 1);
पूर्ण

अटल पूर्णांक apds9960_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा apds9960_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	indio_dev->info = &apds9960_info;
	indio_dev->name = APDS9960_DRV_NAME;
	indio_dev->channels = apds9960_channels;
	indio_dev->num_channels = ARRAY_SIZE(apds9960_channels);
	indio_dev->available_scan_masks = apds9960_scan_masks;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = devm_iio_kfअगरo_buffer_setup(&client->dev, indio_dev,
					  INDIO_BUFFER_SOFTWARE,
					  &apds9960_buffer_setup_ops);
	अगर (ret)
		वापस ret;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);

	data->regmap = devm_regmap_init_i2c(client, &apds9960_regmap_config);
	अगर (IS_ERR(data->regmap)) अणु
		dev_err(&client->dev, "regmap initialization failed.\n");
		वापस PTR_ERR(data->regmap);
	पूर्ण

	data->client = client;
	data->indio_dev = indio_dev;
	mutex_init(&data->lock);

	ret = pm_runसमय_set_active(&client->dev);
	अगर (ret)
		जाओ error_घातer_करोwn;

	pm_runसमय_enable(&client->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&client->dev, 5000);
	pm_runसमय_use_स्वतःsuspend(&client->dev);

	apds9960_set_घातer_state(data, true);

	ret = apds9960_regfield_init(data);
	अगर (ret)
		जाओ error_घातer_करोwn;

	ret = apds9960_chip_init(data);
	अगर (ret)
		जाओ error_घातer_करोwn;

	अगर (client->irq <= 0) अणु
		dev_err(&client->dev, "no valid irq defined\n");
		ret = -EINVAL;
		जाओ error_घातer_करोwn;
	पूर्ण
	ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					शून्य, apds9960_पूर्णांकerrupt_handler,
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					"apds9960_event",
					indio_dev);
	अगर (ret) अणु
		dev_err(&client->dev, "request irq (%d) failed\n", client->irq);
		जाओ error_घातer_करोwn;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ error_घातer_करोwn;

	apds9960_set_घातer_state(data, false);

	वापस 0;

error_घातer_करोwn:
	apds9960_set_घातer_state(data, false);

	वापस ret;
पूर्ण

अटल पूर्णांक apds9960_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा apds9960_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);
	apds9960_set_घातermode(data, 0);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक apds9960_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा apds9960_data *data =
			iio_priv(i2c_get_clientdata(to_i2c_client(dev)));

	वापस apds9960_set_घातermode(data, 0);
पूर्ण

अटल पूर्णांक apds9960_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा apds9960_data *data =
			iio_priv(i2c_get_clientdata(to_i2c_client(dev)));

	वापस apds9960_set_घातermode(data, 1);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops apds9960_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(apds9960_runसमय_suspend,
			   apds9960_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id apds9960_id[] = अणु
	अणु "apds9960", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, apds9960_id);

अटल स्थिर काष्ठा acpi_device_id apds9960_acpi_match[] = अणु
	अणु "MSHW0184" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, apds9960_acpi_match);

अटल स्थिर काष्ठा of_device_id apds9960_of_match[] = अणु
	अणु .compatible = "avago,apds9960" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, apds9960_of_match);

अटल काष्ठा i2c_driver apds9960_driver = अणु
	.driver = अणु
		.name	= APDS9960_DRV_NAME,
		.of_match_table = apds9960_of_match,
		.pm	= &apds9960_pm_ops,
		.acpi_match_table = apds9960_acpi_match,
	पूर्ण,
	.probe		= apds9960_probe,
	.हटाओ		= apds9960_हटाओ,
	.id_table	= apds9960_id,
पूर्ण;
module_i2c_driver(apds9960_driver);

MODULE_AUTHOR("Matt Ranostay <matt.ranostay@konsulko.com>");
MODULE_DESCRIPTION("APDS9960 Gesture/RGB/ALS/Proximity sensor");
MODULE_LICENSE("GPL");
