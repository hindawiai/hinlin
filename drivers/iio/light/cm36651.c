<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 * Author: Beomho Seo <beomho.seo@samsung.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>

/* Slave address 0x19 क्रम PS of 7 bit addressing protocol क्रम I2C */
#घोषणा CM36651_I2C_ADDR_PS		0x19
/* Alert Response Address */
#घोषणा CM36651_ARA			0x0C

/* Ambient light sensor */
#घोषणा CM36651_CS_CONF1		0x00
#घोषणा CM36651_CS_CONF2		0x01
#घोषणा CM36651_ALS_WH_M		0x02
#घोषणा CM36651_ALS_WH_L		0x03
#घोषणा CM36651_ALS_WL_M		0x04
#घोषणा CM36651_ALS_WL_L		0x05
#घोषणा CM36651_CS_CONF3		0x06
#घोषणा CM36651_CS_CONF_REG_NUM		0x02

/* Proximity sensor */
#घोषणा CM36651_PS_CONF1		0x00
#घोषणा CM36651_PS_THD			0x01
#घोषणा CM36651_PS_CANC			0x02
#घोषणा CM36651_PS_CONF2		0x03
#घोषणा CM36651_PS_REG_NUM		0x04

/* CS_CONF1 command code */
#घोषणा CM36651_ALS_ENABLE		0x00
#घोषणा CM36651_ALS_DISABLE		0x01
#घोषणा CM36651_ALS_INT_EN		0x02
#घोषणा CM36651_ALS_THRES		0x04

/* CS_CONF2 command code */
#घोषणा CM36651_CS_CONF2_DEFAULT_BIT	0x08

/* CS_CONF3 channel पूर्णांकegration समय */
#घोषणा CM36651_CS_IT1			0x00 /* Integration समय 80 msec */
#घोषणा CM36651_CS_IT2			0x40 /* Integration समय 160 msec */
#घोषणा CM36651_CS_IT3			0x80 /* Integration समय 320 msec */
#घोषणा CM36651_CS_IT4			0xC0 /* Integration समय 640 msec */

/* PS_CONF1 command code */
#घोषणा CM36651_PS_ENABLE		0x00
#घोषणा CM36651_PS_DISABLE		0x01
#घोषणा CM36651_PS_INT_EN		0x02
#घोषणा CM36651_PS_PERS2		0x04
#घोषणा CM36651_PS_PERS3		0x08
#घोषणा CM36651_PS_PERS4		0x0C

/* PS_CONF1 command code: पूर्णांकegration समय */
#घोषणा CM36651_PS_IT1			0x00 /* Integration समय 0.32 msec */
#घोषणा CM36651_PS_IT2			0x10 /* Integration समय 0.42 msec */
#घोषणा CM36651_PS_IT3			0x20 /* Integration समय 0.52 msec */
#घोषणा CM36651_PS_IT4			0x30 /* Integration समय 0.64 msec */

/* PS_CONF1 command code: duty ratio */
#घोषणा CM36651_PS_DR1			0x00 /* Duty ratio 1/80 */
#घोषणा CM36651_PS_DR2			0x40 /* Duty ratio 1/160 */
#घोषणा CM36651_PS_DR3			0x80 /* Duty ratio 1/320 */
#घोषणा CM36651_PS_DR4			0xC0 /* Duty ratio 1/640 */

/* PS_THD command code */
#घोषणा CM36651_PS_INITIAL_THD		0x05

/* PS_CANC command code */
#घोषणा CM36651_PS_CANC_DEFAULT		0x00

/* PS_CONF2 command code */
#घोषणा CM36651_PS_HYS1			0x00
#घोषणा CM36651_PS_HYS2			0x01
#घोषणा CM36651_PS_SMART_PERS_EN	0x02
#घोषणा CM36651_PS_सूची_INT		0x04
#घोषणा CM36651_PS_MS			0x10

#घोषणा CM36651_CS_COLOR_NUM		4

#घोषणा CM36651_CLOSE_PROXIMITY		0x32
#घोषणा CM36651_FAR_PROXIMITY			0x33

#घोषणा CM36651_CS_INT_TIME_AVAIL	"0.08 0.16 0.32 0.64"
#घोषणा CM36651_PS_INT_TIME_AVAIL	"0.000320 0.000420 0.000520 0.000640"

क्रमागत cm36651_operation_mode अणु
	CM36651_LIGHT_EN,
	CM36651_PROXIMITY_EN,
	CM36651_PROXIMITY_EV_EN,
पूर्ण;

क्रमागत cm36651_light_channel_idx अणु
	CM36651_LIGHT_CHANNEL_IDX_RED,
	CM36651_LIGHT_CHANNEL_IDX_GREEN,
	CM36651_LIGHT_CHANNEL_IDX_BLUE,
	CM36651_LIGHT_CHANNEL_IDX_CLEAR,
पूर्ण;

क्रमागत cm36651_command अणु
	CM36651_CMD_READ_RAW_LIGHT,
	CM36651_CMD_READ_RAW_PROXIMITY,
	CM36651_CMD_PROX_EV_EN,
	CM36651_CMD_PROX_EV_DIS,
पूर्ण;

अटल स्थिर u8 cm36651_cs_reg[CM36651_CS_CONF_REG_NUM] = अणु
	CM36651_CS_CONF1,
	CM36651_CS_CONF2,
पूर्ण;

अटल स्थिर u8 cm36651_ps_reg[CM36651_PS_REG_NUM] = अणु
	CM36651_PS_CONF1,
	CM36651_PS_THD,
	CM36651_PS_CANC,
	CM36651_PS_CONF2,
पूर्ण;

काष्ठा cm36651_data अणु
	स्थिर काष्ठा cm36651_platक्रमm_data *pdata;
	काष्ठा i2c_client *client;
	काष्ठा i2c_client *ps_client;
	काष्ठा i2c_client *ara_client;
	काष्ठा mutex lock;
	काष्ठा regulator *vled_reg;
	अचिन्हित दीर्घ flags;
	पूर्णांक cs_पूर्णांक_समय[CM36651_CS_COLOR_NUM];
	पूर्णांक ps_पूर्णांक_समय;
	u8 cs_ctrl_regs[CM36651_CS_CONF_REG_NUM];
	u8 ps_ctrl_regs[CM36651_PS_REG_NUM];
	u16 color[CM36651_CS_COLOR_NUM];
पूर्ण;

अटल पूर्णांक cm36651_setup_reg(काष्ठा cm36651_data *cm36651)
अणु
	काष्ठा i2c_client *client = cm36651->client;
	काष्ठा i2c_client *ps_client = cm36651->ps_client;
	पूर्णांक i, ret;

	/* CS initialization */
	cm36651->cs_ctrl_regs[CM36651_CS_CONF1] = CM36651_ALS_ENABLE |
							     CM36651_ALS_THRES;
	cm36651->cs_ctrl_regs[CM36651_CS_CONF2] = CM36651_CS_CONF2_DEFAULT_BIT;

	क्रम (i = 0; i < CM36651_CS_CONF_REG_NUM; i++) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(client, cm36651_cs_reg[i],
						     cm36651->cs_ctrl_regs[i]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* PS initialization */
	cm36651->ps_ctrl_regs[CM36651_PS_CONF1] = CM36651_PS_ENABLE |
								CM36651_PS_IT2;
	cm36651->ps_ctrl_regs[CM36651_PS_THD] = CM36651_PS_INITIAL_THD;
	cm36651->ps_ctrl_regs[CM36651_PS_CANC] = CM36651_PS_CANC_DEFAULT;
	cm36651->ps_ctrl_regs[CM36651_PS_CONF2] = CM36651_PS_HYS2 |
				CM36651_PS_सूची_INT | CM36651_PS_SMART_PERS_EN;

	क्रम (i = 0; i < CM36651_PS_REG_NUM; i++) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(ps_client, cm36651_ps_reg[i],
						     cm36651->ps_ctrl_regs[i]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Set shutकरोwn mode */
	ret = i2c_smbus_ग_लिखो_byte_data(client, CM36651_CS_CONF1,
							  CM36651_ALS_DISABLE);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(cm36651->ps_client,
					 CM36651_PS_CONF1, CM36651_PS_DISABLE);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक cm36651_पढ़ो_output(काष्ठा cm36651_data *cm36651,
				काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val)
अणु
	काष्ठा i2c_client *client = cm36651->client;
	पूर्णांक ret = -EINVAL;

	चयन (chan->type) अणु
	हाल IIO_LIGHT:
		*val = i2c_smbus_पढ़ो_word_data(client, chan->address);
		अगर (*val < 0)
			वापस ret;

		ret = i2c_smbus_ग_लिखो_byte_data(client, CM36651_CS_CONF1,
							CM36651_ALS_DISABLE);
		अगर (ret < 0)
			वापस ret;

		ret = IIO_VAL_INT;
		अवरोध;
	हाल IIO_PROXIMITY:
		*val = i2c_smbus_पढ़ो_byte(cm36651->ps_client);
		अगर (*val < 0)
			वापस ret;

		अगर (!test_bit(CM36651_PROXIMITY_EV_EN, &cm36651->flags)) अणु
			ret = i2c_smbus_ग_लिखो_byte_data(cm36651->ps_client,
					CM36651_PS_CONF1, CM36651_PS_DISABLE);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		ret = IIO_VAL_INT;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t cm36651_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा iio_dev *indio_dev = data;
	काष्ठा cm36651_data *cm36651 = iio_priv(indio_dev);
	काष्ठा i2c_client *client = cm36651->client;
	पूर्णांक ev_dir, ret;
	u64 ev_code;

	/*
	 * The PS INT pin is an active low संकेत that PS INT move logic low
	 * when the object is detect. Once the MCU host received the PS INT
	 * "LOW" संकेत, the Host needs to पढ़ो the data at Alert Response
	 * Address(ARA) to clear the PS INT संकेत. After clearing the PS
	 * INT pin, the PS INT संकेत toggles from low to high.
	 */
	ret = i2c_smbus_पढ़ो_byte(cm36651->ara_client);
	अगर (ret < 0) अणु
		dev_err(&client->dev,
				"%s: Data read failed: %d\n", __func__, ret);
		वापस IRQ_HANDLED;
	पूर्ण
	चयन (ret) अणु
	हाल CM36651_CLOSE_PROXIMITY:
		ev_dir = IIO_EV_सूची_RISING;
		अवरोध;
	हाल CM36651_FAR_PROXIMITY:
		ev_dir = IIO_EV_सूची_FALLING;
		अवरोध;
	शेष:
		dev_err(&client->dev,
			"%s: Data read wrong: %d\n", __func__, ret);
		वापस IRQ_HANDLED;
	पूर्ण

	ev_code = IIO_UNMOD_EVENT_CODE(IIO_PROXIMITY,
				CM36651_CMD_READ_RAW_PROXIMITY,
				IIO_EV_TYPE_THRESH, ev_dir);

	iio_push_event(indio_dev, ev_code, iio_get_समय_ns(indio_dev));

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक cm36651_set_operation_mode(काष्ठा cm36651_data *cm36651, पूर्णांक cmd)
अणु
	काष्ठा i2c_client *client = cm36651->client;
	काष्ठा i2c_client *ps_client = cm36651->ps_client;
	पूर्णांक ret = -EINVAL;

	चयन (cmd) अणु
	हाल CM36651_CMD_READ_RAW_LIGHT:
		ret = i2c_smbus_ग_लिखो_byte_data(client, CM36651_CS_CONF1,
				cm36651->cs_ctrl_regs[CM36651_CS_CONF1]);
		अवरोध;
	हाल CM36651_CMD_READ_RAW_PROXIMITY:
		अगर (test_bit(CM36651_PROXIMITY_EV_EN, &cm36651->flags))
			वापस CM36651_PROXIMITY_EV_EN;

		ret = i2c_smbus_ग_लिखो_byte_data(ps_client, CM36651_PS_CONF1,
				cm36651->ps_ctrl_regs[CM36651_PS_CONF1]);
		अवरोध;
	हाल CM36651_CMD_PROX_EV_EN:
		अगर (test_bit(CM36651_PROXIMITY_EV_EN, &cm36651->flags)) अणु
			dev_err(&client->dev,
				"Already proximity event enable state\n");
			वापस ret;
		पूर्ण
		set_bit(CM36651_PROXIMITY_EV_EN, &cm36651->flags);

		ret = i2c_smbus_ग_लिखो_byte_data(ps_client,
			cm36651_ps_reg[CM36651_PS_CONF1],
			CM36651_PS_INT_EN | CM36651_PS_PERS2 | CM36651_PS_IT2);

		अगर (ret < 0) अणु
			dev_err(&client->dev, "Proximity enable event failed\n");
			वापस ret;
		पूर्ण
		अवरोध;
	हाल CM36651_CMD_PROX_EV_DIS:
		अगर (!test_bit(CM36651_PROXIMITY_EV_EN, &cm36651->flags)) अणु
			dev_err(&client->dev,
				"Already proximity event disable state\n");
			वापस ret;
		पूर्ण
		clear_bit(CM36651_PROXIMITY_EV_EN, &cm36651->flags);
		ret = i2c_smbus_ग_लिखो_byte_data(ps_client,
					CM36651_PS_CONF1, CM36651_PS_DISABLE);
		अवरोध;
	पूर्ण

	अगर (ret < 0)
		dev_err(&client->dev, "Write register failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक cm36651_पढ़ो_channel(काष्ठा cm36651_data *cm36651,
				काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val)
अणु
	काष्ठा i2c_client *client = cm36651->client;
	पूर्णांक cmd, ret;

	अगर (chan->type == IIO_LIGHT)
		cmd = CM36651_CMD_READ_RAW_LIGHT;
	अन्यथा अगर (chan->type == IIO_PROXIMITY)
		cmd = CM36651_CMD_READ_RAW_PROXIMITY;
	अन्यथा
		वापस -EINVAL;

	ret = cm36651_set_operation_mode(cm36651, cmd);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "CM36651 set operation mode failed\n");
		वापस ret;
	पूर्ण
	/* Delay क्रम work after enable operation */
	msleep(50);
	ret = cm36651_पढ़ो_output(cm36651, chan, val);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "CM36651 read output failed\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cm36651_पढ़ो_पूर्णांक_समय(काष्ठा cm36651_data *cm36651,
				काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val2)
अणु
	चयन (chan->type) अणु
	हाल IIO_LIGHT:
		अगर (cm36651->cs_पूर्णांक_समय[chan->address] == CM36651_CS_IT1)
			*val2 = 80000;
		अन्यथा अगर (cm36651->cs_पूर्णांक_समय[chan->address] == CM36651_CS_IT2)
			*val2 = 160000;
		अन्यथा अगर (cm36651->cs_पूर्णांक_समय[chan->address] == CM36651_CS_IT3)
			*val2 = 320000;
		अन्यथा अगर (cm36651->cs_पूर्णांक_समय[chan->address] == CM36651_CS_IT4)
			*val2 = 640000;
		अन्यथा
			वापस -EINVAL;
		अवरोध;
	हाल IIO_PROXIMITY:
		अगर (cm36651->ps_पूर्णांक_समय == CM36651_PS_IT1)
			*val2 = 320;
		अन्यथा अगर (cm36651->ps_पूर्णांक_समय == CM36651_PS_IT2)
			*val2 = 420;
		अन्यथा अगर (cm36651->ps_पूर्णांक_समय == CM36651_PS_IT3)
			*val2 = 520;
		अन्यथा अगर (cm36651->ps_पूर्णांक_समय == CM36651_PS_IT4)
			*val2 = 640;
		अन्यथा
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण

अटल पूर्णांक cm36651_ग_लिखो_पूर्णांक_समय(काष्ठा cm36651_data *cm36651,
				काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val)
अणु
	काष्ठा i2c_client *client = cm36651->client;
	काष्ठा i2c_client *ps_client = cm36651->ps_client;
	पूर्णांक पूर्णांक_समय, ret;

	चयन (chan->type) अणु
	हाल IIO_LIGHT:
		अगर (val == 80000)
			पूर्णांक_समय = CM36651_CS_IT1;
		अन्यथा अगर (val == 160000)
			पूर्णांक_समय = CM36651_CS_IT2;
		अन्यथा अगर (val == 320000)
			पूर्णांक_समय = CM36651_CS_IT3;
		अन्यथा अगर (val == 640000)
			पूर्णांक_समय = CM36651_CS_IT4;
		अन्यथा
			वापस -EINVAL;

		ret = i2c_smbus_ग_लिखो_byte_data(client, CM36651_CS_CONF3,
					   पूर्णांक_समय >> 2 * (chan->address));
		अगर (ret < 0) अणु
			dev_err(&client->dev, "CS integration time write failed\n");
			वापस ret;
		पूर्ण
		cm36651->cs_पूर्णांक_समय[chan->address] = पूर्णांक_समय;
		अवरोध;
	हाल IIO_PROXIMITY:
		अगर (val == 320)
			पूर्णांक_समय = CM36651_PS_IT1;
		अन्यथा अगर (val == 420)
			पूर्णांक_समय = CM36651_PS_IT2;
		अन्यथा अगर (val == 520)
			पूर्णांक_समय = CM36651_PS_IT3;
		अन्यथा अगर (val == 640)
			पूर्णांक_समय = CM36651_PS_IT4;
		अन्यथा
			वापस -EINVAL;

		ret = i2c_smbus_ग_लिखो_byte_data(ps_client,
						CM36651_PS_CONF1, पूर्णांक_समय);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "PS integration time write failed\n");
			वापस ret;
		पूर्ण
		cm36651->ps_पूर्णांक_समय = पूर्णांक_समय;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cm36651_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा cm36651_data *cm36651 = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&cm36651->lock);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = cm36651_पढ़ो_channel(cm36651, chan, val);
		अवरोध;
	हाल IIO_CHAN_INFO_INT_TIME:
		*val = 0;
		ret = cm36651_पढ़ो_पूर्णांक_समय(cm36651, chan, val2);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	mutex_unlock(&cm36651->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक cm36651_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा cm36651_data *cm36651 = iio_priv(indio_dev);
	काष्ठा i2c_client *client = cm36651->client;
	पूर्णांक ret = -EINVAL;

	अगर (mask == IIO_CHAN_INFO_INT_TIME) अणु
		ret = cm36651_ग_लिखो_पूर्णांक_समय(cm36651, chan, val2);
		अगर (ret < 0)
			dev_err(&client->dev, "Integration time write failed\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cm36651_पढ़ो_prox_thresh(काष्ठा iio_dev *indio_dev,
					स्थिर काष्ठा iio_chan_spec *chan,
					क्रमागत iio_event_type type,
					क्रमागत iio_event_direction dir,
					क्रमागत iio_event_info info,
					पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा cm36651_data *cm36651 = iio_priv(indio_dev);

	*val = cm36651->ps_ctrl_regs[CM36651_PS_THD];

	वापस 0;
पूर्ण

अटल पूर्णांक cm36651_ग_लिखो_prox_thresh(काष्ठा iio_dev *indio_dev,
					स्थिर काष्ठा iio_chan_spec *chan,
					क्रमागत iio_event_type type,
					क्रमागत iio_event_direction dir,
					क्रमागत iio_event_info info,
					पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा cm36651_data *cm36651 = iio_priv(indio_dev);
	काष्ठा i2c_client *client = cm36651->client;
	पूर्णांक ret;

	अगर (val < 3 || val > 255)
		वापस -EINVAL;

	cm36651->ps_ctrl_regs[CM36651_PS_THD] = val;
	ret = i2c_smbus_ग_लिखो_byte_data(cm36651->ps_client, CM36651_PS_THD,
					cm36651->ps_ctrl_regs[CM36651_PS_THD]);

	अगर (ret < 0) अणु
		dev_err(&client->dev, "PS threshold write failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cm36651_ग_लिखो_prox_event_config(काष्ठा iio_dev *indio_dev,
					स्थिर काष्ठा iio_chan_spec *chan,
					क्रमागत iio_event_type type,
					क्रमागत iio_event_direction dir,
					पूर्णांक state)
अणु
	काष्ठा cm36651_data *cm36651 = iio_priv(indio_dev);
	पूर्णांक cmd, ret;

	mutex_lock(&cm36651->lock);

	cmd = state ? CM36651_CMD_PROX_EV_EN : CM36651_CMD_PROX_EV_DIS;
	ret = cm36651_set_operation_mode(cm36651, cmd);

	mutex_unlock(&cm36651->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक cm36651_पढ़ो_prox_event_config(काष्ठा iio_dev *indio_dev,
					स्थिर काष्ठा iio_chan_spec *chan,
					क्रमागत iio_event_type type,
					क्रमागत iio_event_direction dir)
अणु
	काष्ठा cm36651_data *cm36651 = iio_priv(indio_dev);
	पूर्णांक event_en;

	mutex_lock(&cm36651->lock);

	event_en = test_bit(CM36651_PROXIMITY_EV_EN, &cm36651->flags);

	mutex_unlock(&cm36651->lock);

	वापस event_en;
पूर्ण

#घोषणा CM36651_LIGHT_CHANNEL(_color, _idx) अणु		\
	.type = IIO_LIGHT,				\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |	\
			BIT(IIO_CHAN_INFO_INT_TIME),	\
	.address = _idx,				\
	.modअगरied = 1,					\
	.channel2 = IIO_MOD_LIGHT_##_color,		\
पूर्ण							\

अटल स्थिर काष्ठा iio_event_spec cm36651_event_spec[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_EITHER,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
				BIT(IIO_EV_INFO_ENABLE),
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec cm36651_channels[] = अणु
	अणु
		.type = IIO_PROXIMITY,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_INT_TIME),
		.event_spec = cm36651_event_spec,
		.num_event_specs = ARRAY_SIZE(cm36651_event_spec),
	पूर्ण,
	CM36651_LIGHT_CHANNEL(RED, CM36651_LIGHT_CHANNEL_IDX_RED),
	CM36651_LIGHT_CHANNEL(GREEN, CM36651_LIGHT_CHANNEL_IDX_GREEN),
	CM36651_LIGHT_CHANNEL(BLUE, CM36651_LIGHT_CHANNEL_IDX_BLUE),
	CM36651_LIGHT_CHANNEL(CLEAR, CM36651_LIGHT_CHANNEL_IDX_CLEAR),
पूर्ण;

अटल IIO_CONST_ATTR(in_illuminance_पूर्णांकegration_समय_available,
					CM36651_CS_INT_TIME_AVAIL);
अटल IIO_CONST_ATTR(in_proximity_पूर्णांकegration_समय_available,
					CM36651_PS_INT_TIME_AVAIL);

अटल काष्ठा attribute *cm36651_attributes[] = अणु
	&iio_स्थिर_attr_in_illuminance_पूर्णांकegration_समय_available.dev_attr.attr,
	&iio_स्थिर_attr_in_proximity_पूर्णांकegration_समय_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group cm36651_attribute_group = अणु
	.attrs = cm36651_attributes
पूर्ण;

अटल स्थिर काष्ठा iio_info cm36651_info = अणु
	.पढ़ो_raw		= &cm36651_पढ़ो_raw,
	.ग_लिखो_raw		= &cm36651_ग_लिखो_raw,
	.पढ़ो_event_value	= &cm36651_पढ़ो_prox_thresh,
	.ग_लिखो_event_value	= &cm36651_ग_लिखो_prox_thresh,
	.पढ़ो_event_config	= &cm36651_पढ़ो_prox_event_config,
	.ग_लिखो_event_config	= &cm36651_ग_लिखो_prox_event_config,
	.attrs			= &cm36651_attribute_group,
पूर्ण;

अटल पूर्णांक cm36651_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cm36651_data *cm36651;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*cm36651));
	अगर (!indio_dev)
		वापस -ENOMEM;

	cm36651 = iio_priv(indio_dev);

	cm36651->vled_reg = devm_regulator_get(&client->dev, "vled");
	अगर (IS_ERR(cm36651->vled_reg)) अणु
		dev_err(&client->dev, "get regulator vled failed\n");
		वापस PTR_ERR(cm36651->vled_reg);
	पूर्ण

	ret = regulator_enable(cm36651->vled_reg);
	अगर (ret) अणु
		dev_err(&client->dev, "enable regulator vled failed\n");
		वापस ret;
	पूर्ण

	i2c_set_clientdata(client, indio_dev);

	cm36651->client = client;
	cm36651->ps_client = i2c_new_dummy_device(client->adapter,
						     CM36651_I2C_ADDR_PS);
	अगर (IS_ERR(cm36651->ps_client)) अणु
		dev_err(&client->dev, "%s: new i2c device failed\n", __func__);
		ret = PTR_ERR(cm36651->ps_client);
		जाओ error_disable_reg;
	पूर्ण

	cm36651->ara_client = i2c_new_dummy_device(client->adapter, CM36651_ARA);
	अगर (IS_ERR(cm36651->ara_client)) अणु
		dev_err(&client->dev, "%s: new i2c device failed\n", __func__);
		ret = PTR_ERR(cm36651->ara_client);
		जाओ error_i2c_unरेजिस्टर_ps;
	पूर्ण

	mutex_init(&cm36651->lock);
	indio_dev->channels = cm36651_channels;
	indio_dev->num_channels = ARRAY_SIZE(cm36651_channels);
	indio_dev->info = &cm36651_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = cm36651_setup_reg(cm36651);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: register setup failed\n", __func__);
		जाओ error_i2c_unरेजिस्टर_ara;
	पूर्ण

	ret = request_thपढ़ोed_irq(client->irq, शून्य, cm36651_irq_handler,
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
							"cm36651", indio_dev);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: request irq failed\n", __func__);
		जाओ error_i2c_unरेजिस्टर_ara;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: regist device failed\n", __func__);
		जाओ error_मुक्त_irq;
	पूर्ण

	वापस 0;

error_मुक्त_irq:
	मुक्त_irq(client->irq, indio_dev);
error_i2c_unरेजिस्टर_ara:
	i2c_unरेजिस्टर_device(cm36651->ara_client);
error_i2c_unरेजिस्टर_ps:
	i2c_unरेजिस्टर_device(cm36651->ps_client);
error_disable_reg:
	regulator_disable(cm36651->vled_reg);
	वापस ret;
पूर्ण

अटल पूर्णांक cm36651_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा cm36651_data *cm36651 = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	regulator_disable(cm36651->vled_reg);
	मुक्त_irq(client->irq, indio_dev);
	i2c_unरेजिस्टर_device(cm36651->ps_client);
	i2c_unरेजिस्टर_device(cm36651->ara_client);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id cm36651_id[] = अणु
	अणु "cm36651", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, cm36651_id);

अटल स्थिर काष्ठा of_device_id cm36651_of_match[] = अणु
	अणु .compatible = "capella,cm36651" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cm36651_of_match);

अटल काष्ठा i2c_driver cm36651_driver = अणु
	.driver = अणु
		.name	= "cm36651",
		.of_match_table = cm36651_of_match,
	पूर्ण,
	.probe		= cm36651_probe,
	.हटाओ		= cm36651_हटाओ,
	.id_table	= cm36651_id,
पूर्ण;

module_i2c_driver(cm36651_driver);

MODULE_AUTHOR("Beomho Seo <beomho.seo@samsung.com>");
MODULE_DESCRIPTION("CM36651 proximity/ambient light sensor driver");
MODULE_LICENSE("GPL v2");
