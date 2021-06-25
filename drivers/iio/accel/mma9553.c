<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Freescale MMA9553L Intelligent Peकरोmeter driver
 * Copyright (c) 2014, Intel Corporation.
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/pm_runसमय.स>
#समावेश "mma9551_core.h"

#घोषणा MMA9553_DRV_NAME			"mma9553"
#घोषणा MMA9553_IRQ_NAME			"mma9553_event"

/* Peकरोmeter configuration रेजिस्टरs (R/W) */
#घोषणा MMA9553_REG_CONF_SLEEPMIN		0x00
#घोषणा MMA9553_REG_CONF_SLEEPMAX		0x02
#घोषणा MMA9553_REG_CONF_SLEEPTHD		0x04
#घोषणा MMA9553_MASK_CONF_WORD			GENMASK(15, 0)

#घोषणा MMA9553_REG_CONF_CONF_STEPLEN		0x06
#घोषणा MMA9553_MASK_CONF_CONFIG		BIT(15)
#घोषणा MMA9553_MASK_CONF_ACT_DBCNTM		BIT(14)
#घोषणा MMA9553_MASK_CONF_SLP_DBCNTM		BIT(13)
#घोषणा MMA9553_MASK_CONF_STEPLEN		GENMASK(7, 0)

#घोषणा MMA9553_REG_CONF_HEIGHT_WEIGHT		0x08
#घोषणा MMA9553_MASK_CONF_HEIGHT		GENMASK(15, 8)
#घोषणा MMA9553_MASK_CONF_WEIGHT		GENMASK(7, 0)

#घोषणा MMA9553_REG_CONF_FILTER			0x0A
#घोषणा MMA9553_MASK_CONF_FILTSTEP		GENMASK(15, 8)
#घोषणा MMA9553_MASK_CONF_MALE			BIT(7)
#घोषणा MMA9553_MASK_CONF_FILTTIME		GENMASK(6, 0)

#घोषणा MMA9553_REG_CONF_SPEED_STEP		0x0C
#घोषणा MMA9553_MASK_CONF_SPDPRD		GENMASK(15, 8)
#घोषणा MMA9553_MASK_CONF_STEPCOALESCE		GENMASK(7, 0)

#घोषणा MMA9553_REG_CONF_ACTTHD			0x0E
#घोषणा MMA9553_MAX_ACTTHD			GENMASK(15, 0)

/* Peकरोmeter status रेजिस्टरs (R-only) */
#घोषणा MMA9553_REG_STATUS			0x00
#घोषणा MMA9553_MASK_STATUS_MRGFL		BIT(15)
#घोषणा MMA9553_MASK_STATUS_SUSPCHG		BIT(14)
#घोषणा MMA9553_MASK_STATUS_STEPCHG		BIT(13)
#घोषणा MMA9553_MASK_STATUS_ACTCHG		BIT(12)
#घोषणा MMA9553_MASK_STATUS_SUSP		BIT(11)
#घोषणा MMA9553_MASK_STATUS_ACTIVITY		GENMASK(10, 8)
#घोषणा MMA9553_MASK_STATUS_VERSION		GENMASK(7, 0)

#घोषणा MMA9553_REG_STEPCNT			0x02
#घोषणा MMA9553_REG_DISTANCE			0x04
#घोषणा MMA9553_REG_SPEED			0x06
#घोषणा MMA9553_REG_CALORIES			0x08
#घोषणा MMA9553_REG_SLEEPCNT			0x0A

/* Peकरोmeter events are always mapped to this pin. */
#घोषणा MMA9553_DEFAULT_GPIO_PIN	mma9551_gpio6
#घोषणा MMA9553_DEFAULT_GPIO_POLARITY	0

/* Bitnum used क्रम GPIO configuration = bit number in high status byte */
#घोषणा MMA9553_STATUS_TO_BITNUM(bit)	(ffs(bit) - 9)
#घोषणा MMA9553_MAX_BITNUM		MMA9553_STATUS_TO_BITNUM(BIT(16))

#घोषणा MMA9553_DEFAULT_SAMPLE_RATE	30	/* Hz */

/*
 * The पूर्णांकernal activity level must be stable क्रम ACTTHD samples beक्रमe
 * ACTIVITY is updated. The ACTIVITY variable contains the current activity
 * level and is updated every समय a step is detected or once a second
 * अगर there are no steps.
 */
#घोषणा MMA9553_ACTIVITY_THD_TO_SEC(thd) ((thd) / MMA9553_DEFAULT_SAMPLE_RATE)
#घोषणा MMA9553_ACTIVITY_SEC_TO_THD(sec) ((sec) * MMA9553_DEFAULT_SAMPLE_RATE)

/*
 * Autonomously suspend peकरोmeter अगर acceleration vector magnitude
 * is near 1g (4096 at 0.244 mg/LSB resolution) क्रम 30 seconds.
 */
#घोषणा MMA9553_DEFAULT_SLEEPMIN	3688	/* 0,9 g */
#घोषणा MMA9553_DEFAULT_SLEEPMAX	4508	/* 1,1 g */
#घोषणा MMA9553_DEFAULT_SLEEPTHD	(MMA9553_DEFAULT_SAMPLE_RATE * 30)

#घोषणा MMA9553_CONFIG_RETRIES		2

/* Status रेजिस्टर - activity field  */
क्रमागत activity_level अणु
	ACTIVITY_UNKNOWN,
	ACTIVITY_REST,
	ACTIVITY_WALKING,
	ACTIVITY_JOGGING,
	ACTIVITY_RUNNING,
पूर्ण;

अटल काष्ठा mma9553_event_info अणु
	क्रमागत iio_chan_type type;
	क्रमागत iio_modअगरier mod;
	क्रमागत iio_event_direction dir;
पूर्ण mma9553_events_info[] = अणु
	अणु
		.type = IIO_STEPS,
		.mod = IIO_NO_MOD,
		.dir = IIO_EV_सूची_NONE,
	पूर्ण,
	अणु
		.type = IIO_ACTIVITY,
		.mod = IIO_MOD_STILL,
		.dir = IIO_EV_सूची_RISING,
	पूर्ण,
	अणु
		.type = IIO_ACTIVITY,
		.mod = IIO_MOD_STILL,
		.dir = IIO_EV_सूची_FALLING,
	पूर्ण,
	अणु
		.type = IIO_ACTIVITY,
		.mod = IIO_MOD_WALKING,
		.dir = IIO_EV_सूची_RISING,
	पूर्ण,
	अणु
		.type = IIO_ACTIVITY,
		.mod = IIO_MOD_WALKING,
		.dir = IIO_EV_सूची_FALLING,
	पूर्ण,
	अणु
		.type = IIO_ACTIVITY,
		.mod = IIO_MOD_JOGGING,
		.dir = IIO_EV_सूची_RISING,
	पूर्ण,
	अणु
		.type = IIO_ACTIVITY,
		.mod = IIO_MOD_JOGGING,
		.dir = IIO_EV_सूची_FALLING,
	पूर्ण,
	अणु
		.type = IIO_ACTIVITY,
		.mod = IIO_MOD_RUNNING,
		.dir = IIO_EV_सूची_RISING,
	पूर्ण,
	अणु
		.type = IIO_ACTIVITY,
		.mod = IIO_MOD_RUNNING,
		.dir = IIO_EV_सूची_FALLING,
	पूर्ण,
पूर्ण;

#घोषणा MMA9553_EVENTS_INFO_SIZE ARRAY_SIZE(mma9553_events_info)

काष्ठा mma9553_event अणु
	काष्ठा mma9553_event_info *info;
	bool enabled;
पूर्ण;

काष्ठा mma9553_conf_regs अणु
	u16 sleepmin;
	u16 sleepmax;
	u16 sleepthd;
	u16 config;
	u16 height_weight;
	u16 filter;
	u16 speed_step;
	u16 actthd;
पूर्ण __packed;

काष्ठा mma9553_data अणु
	काष्ठा i2c_client *client;
	/*
	 * 1. Serialize access to HW (requested by mma9551_core API).
	 * 2. Serialize sequences that घातer on/off the device and access HW.
	 */
	काष्ठा mutex mutex;
	काष्ठा mma9553_conf_regs conf;
	काष्ठा mma9553_event events[MMA9553_EVENTS_INFO_SIZE];
	पूर्णांक num_events;
	u8 gpio_bitnum;
	/*
	 * This is used क्रम all features that depend on step count:
	 * step count, distance, speed, calories.
	 */
	bool stepcnt_enabled;
	u16 stepcnt;
	u8 activity;
	s64 बारtamp;
पूर्ण;

अटल u8 mma9553_get_bits(u16 val, u16 mask)
अणु
	वापस (val & mask) >> (ffs(mask) - 1);
पूर्ण

अटल u16 mma9553_set_bits(u16 current_val, u16 val, u16 mask)
अणु
	वापस (current_val & ~mask) | (val << (ffs(mask) - 1));
पूर्ण

अटल क्रमागत iio_modअगरier mma9553_activity_to_mod(क्रमागत activity_level activity)
अणु
	चयन (activity) अणु
	हाल ACTIVITY_RUNNING:
		वापस IIO_MOD_RUNNING;
	हाल ACTIVITY_JOGGING:
		वापस IIO_MOD_JOGGING;
	हाल ACTIVITY_WALKING:
		वापस IIO_MOD_WALKING;
	हाल ACTIVITY_REST:
		वापस IIO_MOD_STILL;
	हाल ACTIVITY_UNKNOWN:
	शेष:
		वापस IIO_NO_MOD;
	पूर्ण
पूर्ण

अटल व्योम mma9553_init_events(काष्ठा mma9553_data *data)
अणु
	पूर्णांक i;

	data->num_events = MMA9553_EVENTS_INFO_SIZE;
	क्रम (i = 0; i < data->num_events; i++) अणु
		data->events[i].info = &mma9553_events_info[i];
		data->events[i].enabled = false;
	पूर्ण
पूर्ण

अटल काष्ठा mma9553_event *mma9553_get_event(काष्ठा mma9553_data *data,
					       क्रमागत iio_chan_type type,
					       क्रमागत iio_modअगरier mod,
					       क्रमागत iio_event_direction dir)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < data->num_events; i++)
		अगर (data->events[i].info->type == type &&
		    data->events[i].info->mod == mod &&
		    data->events[i].info->dir == dir)
			वापस &data->events[i];

	वापस शून्य;
पूर्ण

अटल bool mma9553_is_any_event_enabled(काष्ठा mma9553_data *data,
					 bool check_type,
					 क्रमागत iio_chan_type type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < data->num_events; i++)
		अगर ((check_type && data->events[i].info->type == type &&
		     data->events[i].enabled) ||
		     (!check_type && data->events[i].enabled))
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक mma9553_set_config(काष्ठा mma9553_data *data, u16 reg,
			      u16 *p_reg_val, u16 val, u16 mask)
अणु
	पूर्णांक ret, retries;
	u16 reg_val, config;

	reg_val = *p_reg_val;
	अगर (val == mma9553_get_bits(reg_val, mask))
		वापस 0;

	reg_val = mma9553_set_bits(reg_val, val, mask);
	ret = mma9551_ग_लिखो_config_word(data->client, MMA9551_APPID_Pगलत_तर्कETER,
					reg, reg_val);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev,
			"error writing config register 0x%x\n", reg);
		वापस ret;
	पूर्ण

	*p_reg_val = reg_val;

	/* Reinitializes the peकरोmeter with current configuration values */
	config = mma9553_set_bits(data->conf.config, 1,
				  MMA9553_MASK_CONF_CONFIG);

	ret = mma9551_ग_लिखो_config_word(data->client, MMA9551_APPID_Pगलत_तर्कETER,
					MMA9553_REG_CONF_CONF_STEPLEN, config);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev,
			"error writing config register 0x%x\n",
			MMA9553_REG_CONF_CONF_STEPLEN);
		वापस ret;
	पूर्ण

	retries = MMA9553_CONFIG_RETRIES;
	करो अणु
		mma9551_sleep(MMA9553_DEFAULT_SAMPLE_RATE);
		ret = mma9551_पढ़ो_config_word(data->client,
					       MMA9551_APPID_Pगलत_तर्कETER,
					       MMA9553_REG_CONF_CONF_STEPLEN,
					       &config);
		अगर (ret < 0)
			वापस ret;
	पूर्ण जबतक (mma9553_get_bits(config, MMA9553_MASK_CONF_CONFIG) &&
		 --retries > 0);

	वापस 0;
पूर्ण

अटल पूर्णांक mma9553_पढ़ो_activity_stepcnt(काष्ठा mma9553_data *data,
					 u8 *activity, u16 *stepcnt)
अणु
	u16 buf[2];
	पूर्णांक ret;

	ret = mma9551_पढ़ो_status_words(data->client, MMA9551_APPID_Pगलत_तर्कETER,
					MMA9553_REG_STATUS, ARRAY_SIZE(buf),
					buf);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev,
			"error reading status and stepcnt\n");
		वापस ret;
	पूर्ण

	*activity = mma9553_get_bits(buf[0], MMA9553_MASK_STATUS_ACTIVITY);
	*stepcnt = buf[1];

	वापस 0;
पूर्ण

अटल पूर्णांक mma9553_conf_gpio(काष्ठा mma9553_data *data)
अणु
	u8 bitnum = 0, appid = MMA9551_APPID_Pगलत_तर्कETER;
	पूर्णांक ret;
	काष्ठा mma9553_event *ev_step_detect;
	bool activity_enabled;

	activity_enabled = mma9553_is_any_event_enabled(data, true,
							IIO_ACTIVITY);
	ev_step_detect = mma9553_get_event(data, IIO_STEPS, IIO_NO_MOD,
					   IIO_EV_सूची_NONE);

	/*
	 * If both step detector and activity are enabled, use the MRGFL bit.
	 * This bit is the logical OR of the SUSPCHG, STEPCHG, and ACTCHG flags.
	 */
	अगर (activity_enabled && ev_step_detect->enabled)
		bitnum = MMA9553_STATUS_TO_BITNUM(MMA9553_MASK_STATUS_MRGFL);
	अन्यथा अगर (ev_step_detect->enabled)
		bitnum = MMA9553_STATUS_TO_BITNUM(MMA9553_MASK_STATUS_STEPCHG);
	अन्यथा अगर (activity_enabled)
		bitnum = MMA9553_STATUS_TO_BITNUM(MMA9553_MASK_STATUS_ACTCHG);
	अन्यथा			/* Reset */
		appid = MMA9551_APPID_NONE;

	अगर (data->gpio_bitnum == bitnum)
		वापस 0;

	/* Save initial values क्रम activity and stepcnt */
	अगर (activity_enabled || ev_step_detect->enabled) अणु
		ret = mma9553_पढ़ो_activity_stepcnt(data, &data->activity,
						    &data->stepcnt);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = mma9551_gpio_config(data->client, MMA9553_DEFAULT_GPIO_PIN, appid,
				  bitnum, MMA9553_DEFAULT_GPIO_POLARITY);
	अगर (ret < 0)
		वापस ret;
	data->gpio_bitnum = bitnum;

	वापस 0;
पूर्ण

अटल पूर्णांक mma9553_init(काष्ठा mma9553_data *data)
अणु
	पूर्णांक ret;

	ret = mma9551_पढ़ो_version(data->client);
	अगर (ret)
		वापस ret;

	/*
	 * Read all the peकरोmeter configuration रेजिस्टरs. This is used as
	 * a device identअगरication command to dअगरferentiate the MMA9553L
	 * from the MMA9550L.
	 */
	ret = mma9551_पढ़ो_config_words(data->client, MMA9551_APPID_Pगलत_तर्कETER,
					MMA9553_REG_CONF_SLEEPMIN,
					माप(data->conf) / माप(u16),
					(u16 *)&data->conf);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev,
			"failed to read configuration registers\n");
		वापस ret;
	पूर्ण

	/* Reset GPIO */
	data->gpio_bitnum = MMA9553_MAX_BITNUM;
	ret = mma9553_conf_gpio(data);
	अगर (ret < 0)
		वापस ret;

	ret = mma9551_app_reset(data->client, MMA9551_RSC_PED);
	अगर (ret < 0)
		वापस ret;

	/* Init config रेजिस्टरs */
	data->conf.sleepmin = MMA9553_DEFAULT_SLEEPMIN;
	data->conf.sleepmax = MMA9553_DEFAULT_SLEEPMAX;
	data->conf.sleepthd = MMA9553_DEFAULT_SLEEPTHD;
	data->conf.config = mma9553_set_bits(data->conf.config, 1,
					     MMA9553_MASK_CONF_CONFIG);
	/*
	 * Clear the activity debounce counter when the activity level changes,
	 * so that the confidence level applies क्रम any activity level.
	 */
	data->conf.config = mma9553_set_bits(data->conf.config, 1,
					     MMA9553_MASK_CONF_ACT_DBCNTM);
	ret = mma9551_ग_लिखो_config_words(data->client, MMA9551_APPID_Pगलत_तर्कETER,
					 MMA9553_REG_CONF_SLEEPMIN,
					 माप(data->conf) / माप(u16),
					 (u16 *)&data->conf);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev,
			"failed to write configuration registers\n");
		वापस ret;
	पूर्ण

	वापस mma9551_set_device_state(data->client, true);
पूर्ण

अटल पूर्णांक mma9553_पढ़ो_status_word(काष्ठा mma9553_data *data, u16 reg,
				    u16 *पंचांगp)
अणु
	bool घातered_on;
	पूर्णांक ret;

	/*
	 * The HW only counts steps and other dependent
	 * parameters (speed, distance, calories, activity)
	 * अगर घातer is on (from enabling an event or the
	 * step counter).
	 */
	घातered_on = mma9553_is_any_event_enabled(data, false, 0) ||
		     data->stepcnt_enabled;
	अगर (!घातered_on) अणु
		dev_err(&data->client->dev, "No channels enabled\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&data->mutex);
	ret = mma9551_पढ़ो_status_word(data->client, MMA9551_APPID_Pगलत_तर्कETER,
				       reg, पंचांगp);
	mutex_unlock(&data->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक mma9553_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mma9553_data *data = iio_priv(indio_dev);
	पूर्णांक ret;
	u16 पंचांगp;
	u8 activity;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		चयन (chan->type) अणु
		हाल IIO_STEPS:
			ret = mma9553_पढ़ो_status_word(data,
						       MMA9553_REG_STEPCNT,
						       &पंचांगp);
			अगर (ret < 0)
				वापस ret;
			*val = पंचांगp;
			वापस IIO_VAL_INT;
		हाल IIO_DISTANCE:
			ret = mma9553_पढ़ो_status_word(data,
						       MMA9553_REG_DISTANCE,
						       &पंचांगp);
			अगर (ret < 0)
				वापस ret;
			*val = पंचांगp;
			वापस IIO_VAL_INT;
		हाल IIO_ACTIVITY:
			ret = mma9553_पढ़ो_status_word(data,
						       MMA9553_REG_STATUS,
						       &पंचांगp);
			अगर (ret < 0)
				वापस ret;

			activity =
			    mma9553_get_bits(पंचांगp, MMA9553_MASK_STATUS_ACTIVITY);

			/*
			 * The device करोes not support confidence value levels,
			 * so we will always have 100% क्रम current activity and
			 * 0% क्रम the others.
			 */
			अगर (chan->channel2 == mma9553_activity_to_mod(activity))
				*val = 100;
			अन्यथा
				*val = 0;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_VELOCITY:	/* m/h */
			अगर (chan->channel2 != IIO_MOD_ROOT_SUM_SQUARED_X_Y_Z)
				वापस -EINVAL;
			ret = mma9553_पढ़ो_status_word(data,
						       MMA9553_REG_SPEED,
						       &पंचांगp);
			अगर (ret < 0)
				वापस ret;
			*val = पंचांगp;
			वापस IIO_VAL_INT;
		हाल IIO_ENERGY:	/* Cal or kcal */
			ret = mma9553_पढ़ो_status_word(data,
						       MMA9553_REG_CALORIES,
						       &पंचांगp);
			अगर (ret < 0)
				वापस ret;
			*val = पंचांगp;
			वापस IIO_VAL_INT;
		हाल IIO_ACCEL:
			mutex_lock(&data->mutex);
			ret = mma9551_पढ़ो_accel_chan(data->client,
						      chan, val, val2);
			mutex_unlock(&data->mutex);
			वापस ret;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_VELOCITY:	/* m/h to m/s */
			अगर (chan->channel2 != IIO_MOD_ROOT_SUM_SQUARED_X_Y_Z)
				वापस -EINVAL;
			*val = 0;
			*val2 = 277;	/* 0.000277 */
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_ENERGY:	/* Cal or kcal to J */
			*val = 4184;
			वापस IIO_VAL_INT;
		हाल IIO_ACCEL:
			वापस mma9551_पढ़ो_accel_scale(val, val2);
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_ENABLE:
		*val = data->stepcnt_enabled;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_CALIBHEIGHT:
		पंचांगp = mma9553_get_bits(data->conf.height_weight,
				       MMA9553_MASK_CONF_HEIGHT);
		*val = पंचांगp / 100;	/* cm to m */
		*val2 = (पंचांगp % 100) * 10000;
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_CALIBWEIGHT:
		*val = mma9553_get_bits(data->conf.height_weight,
					MMA9553_MASK_CONF_WEIGHT);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_DEBOUNCE_COUNT:
		चयन (chan->type) अणु
		हाल IIO_STEPS:
			*val = mma9553_get_bits(data->conf.filter,
						MMA9553_MASK_CONF_FILTSTEP);
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_DEBOUNCE_TIME:
		चयन (chan->type) अणु
		हाल IIO_STEPS:
			*val = mma9553_get_bits(data->conf.filter,
						MMA9553_MASK_CONF_FILTTIME);
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_INT_TIME:
		चयन (chan->type) अणु
		हाल IIO_VELOCITY:
			अगर (chan->channel2 != IIO_MOD_ROOT_SUM_SQUARED_X_Y_Z)
				वापस -EINVAL;
			*val = mma9553_get_bits(data->conf.speed_step,
						MMA9553_MASK_CONF_SPDPRD);
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mma9553_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा mma9553_data *data = iio_priv(indio_dev);
	पूर्णांक ret, पंचांगp;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_ENABLE:
		अगर (data->stepcnt_enabled == !!val)
			वापस 0;
		mutex_lock(&data->mutex);
		ret = mma9551_set_घातer_state(data->client, val);
		अगर (ret < 0) अणु
			mutex_unlock(&data->mutex);
			वापस ret;
		पूर्ण
		data->stepcnt_enabled = val;
		mutex_unlock(&data->mutex);
		वापस 0;
	हाल IIO_CHAN_INFO_CALIBHEIGHT:
		/* m to cm */
		पंचांगp = val * 100 + val2 / 10000;
		अगर (पंचांगp < 0 || पंचांगp > 255)
			वापस -EINVAL;
		mutex_lock(&data->mutex);
		ret = mma9553_set_config(data,
					 MMA9553_REG_CONF_HEIGHT_WEIGHT,
					 &data->conf.height_weight,
					 पंचांगp, MMA9553_MASK_CONF_HEIGHT);
		mutex_unlock(&data->mutex);
		वापस ret;
	हाल IIO_CHAN_INFO_CALIBWEIGHT:
		अगर (val < 0 || val > 255)
			वापस -EINVAL;
		mutex_lock(&data->mutex);
		ret = mma9553_set_config(data,
					 MMA9553_REG_CONF_HEIGHT_WEIGHT,
					 &data->conf.height_weight,
					 val, MMA9553_MASK_CONF_WEIGHT);
		mutex_unlock(&data->mutex);
		वापस ret;
	हाल IIO_CHAN_INFO_DEBOUNCE_COUNT:
		चयन (chan->type) अणु
		हाल IIO_STEPS:
			/*
			 * Set to 0 to disable step filtering. If the value
			 * specअगरied is greater than 6, then 6 will be used.
			 */
			अगर (val < 0)
				वापस -EINVAL;
			अगर (val > 6)
				val = 6;
			mutex_lock(&data->mutex);
			ret = mma9553_set_config(data, MMA9553_REG_CONF_FILTER,
						 &data->conf.filter, val,
						 MMA9553_MASK_CONF_FILTSTEP);
			mutex_unlock(&data->mutex);
			वापस ret;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_DEBOUNCE_TIME:
		चयन (chan->type) अणु
		हाल IIO_STEPS:
			अगर (val < 0 || val > 127)
				वापस -EINVAL;
			mutex_lock(&data->mutex);
			ret = mma9553_set_config(data, MMA9553_REG_CONF_FILTER,
						 &data->conf.filter, val,
						 MMA9553_MASK_CONF_FILTTIME);
			mutex_unlock(&data->mutex);
			वापस ret;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_INT_TIME:
		चयन (chan->type) अणु
		हाल IIO_VELOCITY:
			अगर (chan->channel2 != IIO_MOD_ROOT_SUM_SQUARED_X_Y_Z)
				वापस -EINVAL;
			/*
			 * If set to a value greater than 5, then 5 will be
			 * used. Warning: Do not set SPDPRD to 0 or 1 as
			 * this may cause undesirable behavior.
			 */
			अगर (val < 2)
				वापस -EINVAL;
			अगर (val > 5)
				val = 5;
			mutex_lock(&data->mutex);
			ret = mma9553_set_config(data,
						 MMA9553_REG_CONF_SPEED_STEP,
						 &data->conf.speed_step, val,
						 MMA9553_MASK_CONF_SPDPRD);
			mutex_unlock(&data->mutex);
			वापस ret;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mma9553_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     क्रमागत iio_event_type type,
				     क्रमागत iio_event_direction dir)
अणु
	काष्ठा mma9553_data *data = iio_priv(indio_dev);
	काष्ठा mma9553_event *event;

	event = mma9553_get_event(data, chan->type, chan->channel2, dir);
	अगर (!event)
		वापस -EINVAL;

	वापस event->enabled;
पूर्ण

अटल पूर्णांक mma9553_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
				      स्थिर काष्ठा iio_chan_spec *chan,
				      क्रमागत iio_event_type type,
				      क्रमागत iio_event_direction dir, पूर्णांक state)
अणु
	काष्ठा mma9553_data *data = iio_priv(indio_dev);
	काष्ठा mma9553_event *event;
	पूर्णांक ret;

	event = mma9553_get_event(data, chan->type, chan->channel2, dir);
	अगर (!event)
		वापस -EINVAL;

	अगर (event->enabled == state)
		वापस 0;

	mutex_lock(&data->mutex);

	ret = mma9551_set_घातer_state(data->client, state);
	अगर (ret < 0)
		जाओ err_out;
	event->enabled = state;

	ret = mma9553_conf_gpio(data);
	अगर (ret < 0)
		जाओ err_conf_gpio;

	mutex_unlock(&data->mutex);

	वापस 0;

err_conf_gpio:
	अगर (state) अणु
		event->enabled = false;
		mma9551_set_घातer_state(data->client, false);
	पूर्ण
err_out:
	mutex_unlock(&data->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक mma9553_पढ़ो_event_value(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा iio_chan_spec *chan,
				    क्रमागत iio_event_type type,
				    क्रमागत iio_event_direction dir,
				    क्रमागत iio_event_info info,
				    पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा mma9553_data *data = iio_priv(indio_dev);

	*val2 = 0;
	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		चयन (chan->type) अणु
		हाल IIO_STEPS:
			*val = mma9553_get_bits(data->conf.speed_step,
						MMA9553_MASK_CONF_STEPCOALESCE);
			वापस IIO_VAL_INT;
		हाल IIO_ACTIVITY:
			/*
			 * The device करोes not support confidence value levels.
			 * We set an average of 50%.
			 */
			*val = 50;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_EV_INFO_PERIOD:
		चयन (chan->type) अणु
		हाल IIO_ACTIVITY:
			*val = MMA9553_ACTIVITY_THD_TO_SEC(data->conf.actthd);
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mma9553_ग_लिखो_event_value(काष्ठा iio_dev *indio_dev,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     क्रमागत iio_event_type type,
				     क्रमागत iio_event_direction dir,
				     क्रमागत iio_event_info info,
				     पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा mma9553_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		चयन (chan->type) अणु
		हाल IIO_STEPS:
			अगर (val < 0 || val > 255)
				वापस -EINVAL;
			mutex_lock(&data->mutex);
			ret = mma9553_set_config(data,
						MMA9553_REG_CONF_SPEED_STEP,
						&data->conf.speed_step, val,
						MMA9553_MASK_CONF_STEPCOALESCE);
			mutex_unlock(&data->mutex);
			वापस ret;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_EV_INFO_PERIOD:
		चयन (chan->type) अणु
		हाल IIO_ACTIVITY:
			अगर (val < 0 || val > MMA9553_ACTIVITY_THD_TO_SEC(
			    MMA9553_MAX_ACTTHD))
				वापस -EINVAL;
			mutex_lock(&data->mutex);
			ret = mma9553_set_config(data, MMA9553_REG_CONF_ACTTHD,
						 &data->conf.actthd,
						 MMA9553_ACTIVITY_SEC_TO_THD
						 (val), MMA9553_MASK_CONF_WORD);
			mutex_unlock(&data->mutex);
			वापस ret;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mma9553_get_calibgender_mode(काष्ठा iio_dev *indio_dev,
					स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा mma9553_data *data = iio_priv(indio_dev);
	u8 gender;

	gender = mma9553_get_bits(data->conf.filter, MMA9553_MASK_CONF_MALE);
	/*
	 * HW expects 0 क्रम female and 1 क्रम male,
	 * जबतक iio index is 0 क्रम male and 1 क्रम female.
	 */
	वापस !gender;
पूर्ण

अटल पूर्णांक mma9553_set_calibgender_mode(काष्ठा iio_dev *indio_dev,
					स्थिर काष्ठा iio_chan_spec *chan,
					अचिन्हित पूर्णांक mode)
अणु
	काष्ठा mma9553_data *data = iio_priv(indio_dev);
	u8 gender = !mode;
	पूर्णांक ret;

	अगर ((mode != 0) && (mode != 1))
		वापस -EINVAL;
	mutex_lock(&data->mutex);
	ret = mma9553_set_config(data, MMA9553_REG_CONF_FILTER,
				 &data->conf.filter, gender,
				 MMA9553_MASK_CONF_MALE);
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_event_spec mma9553_step_event = अणु
	.type = IIO_EV_TYPE_CHANGE,
	.dir = IIO_EV_सूची_NONE,
	.mask_separate = BIT(IIO_EV_INFO_ENABLE) | BIT(IIO_EV_INFO_VALUE),
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec mma9553_activity_events[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_ENABLE) |
				 BIT(IIO_EV_INFO_VALUE) |
				 BIT(IIO_EV_INFO_PERIOD),
	 पूर्ण,
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_ENABLE) |
				 BIT(IIO_EV_INFO_VALUE) |
				 BIT(IIO_EV_INFO_PERIOD),
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर mma9553_calibgender_modes[] = अणु "male", "female" पूर्ण;

अटल स्थिर काष्ठा iio_क्रमागत mma9553_calibgender_क्रमागत = अणु
	.items = mma9553_calibgender_modes,
	.num_items = ARRAY_SIZE(mma9553_calibgender_modes),
	.get = mma9553_get_calibgender_mode,
	.set = mma9553_set_calibgender_mode,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec_ext_info mma9553_ext_info[] = अणु
	IIO_ENUM("calibgender", IIO_SHARED_BY_TYPE, &mma9553_calibgender_क्रमागत),
	IIO_ENUM_AVAILABLE("calibgender", &mma9553_calibgender_क्रमागत),
	अणुपूर्ण,
पूर्ण;

#घोषणा MMA9553_Pगलत_तर्कETER_CHANNEL(_type, _mask) अणु		\
	.type = _type,						\
	.info_mask_separate = BIT(IIO_CHAN_INFO_ENABLE)      |	\
			      BIT(IIO_CHAN_INFO_CALIBHEIGHT) |	\
			      _mask,				\
	.ext_info = mma9553_ext_info,				\
पूर्ण

#घोषणा MMA9553_ACTIVITY_CHANNEL(_chan2) अणु				\
	.type = IIO_ACTIVITY,						\
	.modअगरied = 1,							\
	.channel2 = _chan2,						\
	.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_CALIBHEIGHT) |	\
				    BIT(IIO_CHAN_INFO_ENABLE),		\
	.event_spec = mma9553_activity_events,				\
	.num_event_specs = ARRAY_SIZE(mma9553_activity_events),		\
	.ext_info = mma9553_ext_info,					\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mma9553_channels[] = अणु
	MMA9551_ACCEL_CHANNEL(IIO_MOD_X),
	MMA9551_ACCEL_CHANNEL(IIO_MOD_Y),
	MMA9551_ACCEL_CHANNEL(IIO_MOD_Z),

	अणु
		.type = IIO_STEPS,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED) |
				     BIT(IIO_CHAN_INFO_ENABLE) |
				     BIT(IIO_CHAN_INFO_DEBOUNCE_COUNT) |
				     BIT(IIO_CHAN_INFO_DEBOUNCE_TIME),
		.event_spec = &mma9553_step_event,
		.num_event_specs = 1,
	पूर्ण,

	MMA9553_Pगलत_तर्कETER_CHANNEL(IIO_DISTANCE, BIT(IIO_CHAN_INFO_PROCESSED)),
	अणु
		.type = IIO_VELOCITY,
		.modअगरied = 1,
		.channel2 = IIO_MOD_ROOT_SUM_SQUARED_X_Y_Z,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE) |
				      BIT(IIO_CHAN_INFO_INT_TIME) |
				      BIT(IIO_CHAN_INFO_ENABLE),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_CALIBHEIGHT),
		.ext_info = mma9553_ext_info,
	पूर्ण,
	MMA9553_Pगलत_तर्कETER_CHANNEL(IIO_ENERGY, BIT(IIO_CHAN_INFO_RAW) |
				  BIT(IIO_CHAN_INFO_SCALE) |
				  BIT(IIO_CHAN_INFO_CALIBWEIGHT)),

	MMA9553_ACTIVITY_CHANNEL(IIO_MOD_RUNNING),
	MMA9553_ACTIVITY_CHANNEL(IIO_MOD_JOGGING),
	MMA9553_ACTIVITY_CHANNEL(IIO_MOD_WALKING),
	MMA9553_ACTIVITY_CHANNEL(IIO_MOD_STILL),
पूर्ण;

अटल स्थिर काष्ठा iio_info mma9553_info = अणु
	.पढ़ो_raw = mma9553_पढ़ो_raw,
	.ग_लिखो_raw = mma9553_ग_लिखो_raw,
	.पढ़ो_event_config = mma9553_पढ़ो_event_config,
	.ग_लिखो_event_config = mma9553_ग_लिखो_event_config,
	.पढ़ो_event_value = mma9553_पढ़ो_event_value,
	.ग_लिखो_event_value = mma9553_ग_लिखो_event_value,
पूर्ण;

अटल irqवापस_t mma9553_irq_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा mma9553_data *data = iio_priv(indio_dev);

	data->बारtamp = iio_get_समय_ns(indio_dev);
	/*
	 * Since we only configure the पूर्णांकerrupt pin when an
	 * event is enabled, we are sure we have at least
	 * one event enabled at this poपूर्णांक.
	 */
	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t mma9553_event_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा mma9553_data *data = iio_priv(indio_dev);
	u16 stepcnt;
	u8 activity;
	काष्ठा mma9553_event *ev_activity, *ev_prev_activity, *ev_step_detect;
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = mma9553_पढ़ो_activity_stepcnt(data, &activity, &stepcnt);
	अगर (ret < 0) अणु
		mutex_unlock(&data->mutex);
		वापस IRQ_HANDLED;
	पूर्ण

	ev_prev_activity = mma9553_get_event(data, IIO_ACTIVITY,
					     mma9553_activity_to_mod(
					     data->activity),
					     IIO_EV_सूची_FALLING);
	ev_activity = mma9553_get_event(data, IIO_ACTIVITY,
					mma9553_activity_to_mod(activity),
					IIO_EV_सूची_RISING);
	ev_step_detect = mma9553_get_event(data, IIO_STEPS, IIO_NO_MOD,
					   IIO_EV_सूची_NONE);

	अगर (ev_step_detect->enabled && (stepcnt != data->stepcnt)) अणु
		data->stepcnt = stepcnt;
		iio_push_event(indio_dev,
			       IIO_EVENT_CODE(IIO_STEPS, 0, IIO_NO_MOD,
					      IIO_EV_सूची_NONE,
					      IIO_EV_TYPE_CHANGE, 0, 0, 0),
			       data->बारtamp);
	पूर्ण

	अगर (activity != data->activity) अणु
		data->activity = activity;
		/* ev_activity can be शून्य अगर activity == ACTIVITY_UNKNOWN */
		अगर (ev_prev_activity && ev_prev_activity->enabled)
			iio_push_event(indio_dev,
				       IIO_EVENT_CODE(IIO_ACTIVITY, 0,
						    ev_prev_activity->info->mod,
						    IIO_EV_सूची_FALLING,
						    IIO_EV_TYPE_THRESH, 0, 0,
						    0),
				       data->बारtamp);

		अगर (ev_activity && ev_activity->enabled)
			iio_push_event(indio_dev,
				       IIO_EVENT_CODE(IIO_ACTIVITY, 0,
						      ev_activity->info->mod,
						      IIO_EV_सूची_RISING,
						      IIO_EV_TYPE_THRESH, 0, 0,
						      0),
				       data->बारtamp);
	पूर्ण
	mutex_unlock(&data->mutex);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर अक्षर *mma9553_match_acpi_device(काष्ठा device *dev)
अणु
	स्थिर काष्ठा acpi_device_id *id;

	id = acpi_match_device(dev->driver->acpi_match_table, dev);
	अगर (!id)
		वापस शून्य;

	वापस dev_name(dev);
पूर्ण

अटल पूर्णांक mma9553_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा mma9553_data *data;
	काष्ठा iio_dev *indio_dev;
	स्थिर अक्षर *name = शून्य;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	अगर (id)
		name = id->name;
	अन्यथा अगर (ACPI_HANDLE(&client->dev))
		name = mma9553_match_acpi_device(&client->dev);
	अन्यथा
		वापस -ENOSYS;

	mutex_init(&data->mutex);
	mma9553_init_events(data);

	ret = mma9553_init(data);
	अगर (ret < 0)
		वापस ret;

	indio_dev->channels = mma9553_channels;
	indio_dev->num_channels = ARRAY_SIZE(mma9553_channels);
	indio_dev->name = name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &mma9553_info;

	अगर (client->irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
						mma9553_irq_handler,
						mma9553_event_handler,
						IRQF_TRIGGER_RISING,
						MMA9553_IRQ_NAME, indio_dev);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "request irq %d failed\n",
				client->irq);
			जाओ out_घातeroff;
		पूर्ण
	पूर्ण

	ret = pm_runसमय_set_active(&client->dev);
	अगर (ret < 0)
		जाओ out_घातeroff;

	pm_runसमय_enable(&client->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&client->dev,
					 MMA9551_AUTO_SUSPEND_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(&client->dev);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "unable to register iio device\n");
		जाओ out_घातeroff;
	पूर्ण

	dev_dbg(&indio_dev->dev, "Registered device %s\n", name);
	वापस 0;

out_घातeroff:
	mma9551_set_device_state(client, false);
	वापस ret;
पूर्ण

अटल पूर्णांक mma9553_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा mma9553_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);
	pm_runसमय_put_noidle(&client->dev);

	mutex_lock(&data->mutex);
	mma9551_set_device_state(data->client, false);
	mutex_unlock(&data->mutex);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mma9553_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा mma9553_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = mma9551_set_device_state(data->client, false);
	mutex_unlock(&data->mutex);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "powering off device failed\n");
		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mma9553_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा mma9553_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = mma9551_set_device_state(data->client, true);
	अगर (ret < 0)
		वापस ret;

	mma9551_sleep(MMA9553_DEFAULT_SAMPLE_RATE);

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mma9553_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा mma9553_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = mma9551_set_device_state(data->client, false);
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक mma9553_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा mma9553_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = mma9551_set_device_state(data->client, true);
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops mma9553_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(mma9553_suspend, mma9553_resume)
	SET_RUNTIME_PM_OPS(mma9553_runसमय_suspend,
			   mma9553_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id mma9553_acpi_match[] = अणु
	अणु"MMA9553", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(acpi, mma9553_acpi_match);

अटल स्थिर काष्ठा i2c_device_id mma9553_id[] = अणु
	अणु"mma9553", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, mma9553_id);

अटल काष्ठा i2c_driver mma9553_driver = अणु
	.driver = अणु
		   .name = MMA9553_DRV_NAME,
		   .acpi_match_table = ACPI_PTR(mma9553_acpi_match),
		   .pm = &mma9553_pm_ops,
		   पूर्ण,
	.probe = mma9553_probe,
	.हटाओ = mma9553_हटाओ,
	.id_table = mma9553_id,
पूर्ण;

module_i2c_driver(mma9553_driver);

MODULE_AUTHOR("Irina Tirdea <irina.tirdea@intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MMA9553L pedometer platform driver");
