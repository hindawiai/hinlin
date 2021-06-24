<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/media/radio/si4713-i2c.c
 *
 * Silicon Lअसल Si4713 FM Radio Transmitter I2C commands.
 *
 * Copyright (c) 2009 Nokia Corporation
 * Contact: Eduarकरो Valentin <eduarकरो.valentin@nokia.com>
 */

#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-common.h>

#समावेश "si4713.h"

/* module parameters */
अटल पूर्णांक debug;
module_param(debug, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "Debug level (0 - 2)");

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Eduardo Valentin <eduardo.valentin@nokia.com>");
MODULE_DESCRIPTION("I2C driver for Si4713 FM Radio Transmitter");
MODULE_VERSION("0.0.1");

#घोषणा DEFAULT_RDS_PI			0x00
#घोषणा DEFAULT_RDS_PTY			0x00
#घोषणा DEFAULT_RDS_DEVIATION		0x00C8
#घोषणा DEFAULT_RDS_PS_REPEAT_COUNT	0x0003
#घोषणा DEFAULT_LIMITER_RTIME		0x1392
#घोषणा DEFAULT_LIMITER_DEV		0x102CA
#घोषणा DEFAULT_PILOT_FREQUENCY		0x4A38
#घोषणा DEFAULT_PILOT_DEVIATION		0x1A5E
#घोषणा DEFAULT_ACOMP_ATIME		0x0000
#घोषणा DEFAULT_ACOMP_RTIME		0xF4240L
#घोषणा DEFAULT_ACOMP_GAIN		0x0F
#घोषणा DEFAULT_ACOMP_THRESHOLD		(-0x28)
#घोषणा DEFAULT_MUTE			0x01
#घोषणा DEFAULT_POWER_LEVEL		88
#घोषणा DEFAULT_FREQUENCY		8800
#घोषणा DEFAULT_PREEMPHASIS		FMPE_EU
#घोषणा DEFAULT_TUNE_RNL		0xFF

#घोषणा to_si4713_device(sd)	container_of(sd, काष्ठा si4713_device, sd)

/* frequency करोमुख्य transक्रमmation (using बार 10 to aव्योम भग्नs) */
#घोषणा FREQDEV_UNIT	100000
#घोषणा FREQV4L2_MULTI	625
#घोषणा si4713_to_v4l2(f)	((f * FREQDEV_UNIT) / FREQV4L2_MULTI)
#घोषणा v4l2_to_si4713(f)	((f * FREQV4L2_MULTI) / FREQDEV_UNIT)
#घोषणा FREQ_RANGE_LOW			7600
#घोषणा FREQ_RANGE_HIGH			10800

#घोषणा MAX_ARGS 7

#घोषणा RDS_BLOCK			8
#घोषणा RDS_BLOCK_CLEAR			0x03
#घोषणा RDS_BLOCK_LOAD			0x04
#घोषणा RDS_RADIOTEXT_2A		0x20
#घोषणा RDS_RADIOTEXT_BLK_SIZE		4
#घोषणा RDS_RADIOTEXT_INDEX_MAX		0x0F
#घोषणा RDS_CARRIAGE_RETURN		0x0D

#घोषणा rds_ps_nblocks(len)	((len / RDS_BLOCK) + (len % RDS_BLOCK ? 1 : 0))

#घोषणा get_status_bit(p, b, m)	(((p) & (m)) >> (b))
#घोषणा set_bits(p, v, b, m)	(((p) & ~(m)) | ((v) << (b)))

#घोषणा ATTACK_TIME_UNIT	500

#घोषणा POWER_OFF			0x00
#घोषणा POWER_ON			0x01

#घोषणा msb(x)                  ((u8)((u16) x >> 8))
#घोषणा lsb(x)                  ((u8)((u16) x &  0x00FF))
#घोषणा compose_u16(msb, lsb)	(((u16)msb << 8) | lsb)
#घोषणा check_command_failed(status)	(!(status & SI4713_CTS) || \
					(status & SI4713_ERR))
/* mute definition */
#घोषणा set_mute(p)	(((p) & 1) | (((p) & 1) << 1))

#अगर_घोषित DEBUG
#घोषणा DBG_BUFFER(device, message, buffer, size)			\
	अणु								\
		पूर्णांक i;							\
		अक्षर str[(size)*5];					\
		क्रम (i = 0; i < size; i++)				\
			प्र_लिखो(str + i * 5, " 0x%02x", buffer[i]);	\
		v4l2_dbg(2, debug, device, "%s:%s\n", message, str);	\
	पूर्ण
#अन्यथा
#घोषणा DBG_BUFFER(device, message, buffer, size)
#पूर्ण_अगर

/*
 * Values क्रम limiter release समय (sorted by second column)
 *	device	release
 *	value	समय (us)
 */
अटल दीर्घ limiter_बार[] = अणु
	2000,	250,
	1000,	500,
	510,	1000,
	255,	2000,
	170,	3000,
	127,	4020,
	102,	5010,
	85,	6020,
	73,	7010,
	64,	7990,
	57,	8970,
	51,	10030,
	25,	20470,
	17,	30110,
	13,	39380,
	10,	51190,
	8,	63690,
	7,	73140,
	6,	85330,
	5,	102390,
पूर्ण;

/*
 * Values क्रम audio compression release समय (sorted by second column)
 *	device	release
 *	value	समय (us)
 */
अटल अचिन्हित दीर्घ acomp_rबार[] = अणु
	0,	100000,
	1,	200000,
	2,	350000,
	3,	525000,
	4,	1000000,
पूर्ण;

/*
 * Values क्रम preemphasis (sorted by second column)
 *	device	preemphasis
 *	value	value (v4l2)
 */
अटल अचिन्हित दीर्घ preemphasis_values[] = अणु
	FMPE_DISABLED,	V4L2_PREEMPHASIS_DISABLED,
	FMPE_EU,	V4L2_PREEMPHASIS_50_uS,
	FMPE_USA,	V4L2_PREEMPHASIS_75_uS,
पूर्ण;

अटल पूर्णांक usecs_to_dev(अचिन्हित दीर्घ usecs, अचिन्हित दीर्घ स्थिर array[],
			पूर्णांक size)
अणु
	पूर्णांक i;
	पूर्णांक rval = -EINVAL;

	क्रम (i = 0; i < size / 2; i++)
		अगर (array[(i * 2) + 1] >= usecs) अणु
			rval = array[i * 2];
			अवरोध;
		पूर्ण

	वापस rval;
पूर्ण

/* si4713_handler: IRQ handler, just complete work */
अटल irqवापस_t si4713_handler(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा si4713_device *sdev = dev;

	v4l2_dbg(2, debug, &sdev->sd,
			"%s: sending signal to completion work.\n", __func__);
	complete(&sdev->work);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * si4713_send_command - sends a command to si4713 and रुकोs its response
 * @sdev: si4713_device काष्ठाure क्रम the device we are communicating
 * @command: command id
 * @args: command arguments we are sending (up to 7)
 * @argn: actual size of @args
 * @response: buffer to place the expected response from the device (up to 15)
 * @respn: actual size of @response
 * @usecs: amount of समय to रुको beक्रमe पढ़ोing the response (in usecs)
 */
अटल पूर्णांक si4713_send_command(काष्ठा si4713_device *sdev, स्थिर u8 command,
				स्थिर u8 args[], स्थिर पूर्णांक argn,
				u8 response[], स्थिर पूर्णांक respn, स्थिर पूर्णांक usecs)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sdev->sd);
	अचिन्हित दीर्घ until_jअगरfies;
	u8 data1[MAX_ARGS + 1];
	पूर्णांक err;

	अगर (!client->adapter)
		वापस -ENODEV;

	/* First send the command and its arguments */
	data1[0] = command;
	स_नकल(data1 + 1, args, argn);
	DBG_BUFFER(&sdev->sd, "Parameters", data1, argn + 1);

	err = i2c_master_send(client, data1, argn + 1);
	अगर (err != argn + 1) अणु
		v4l2_err(&sdev->sd, "Error while sending command 0x%02x\n",
			command);
		वापस err < 0 ? err : -EIO;
	पूर्ण

	until_jअगरfies = jअगरfies + usecs_to_jअगरfies(usecs) + 1;

	/* Wait response from पूर्णांकerrupt */
	अगर (client->irq) अणु
		अगर (!रुको_क्रम_completion_समयout(&sdev->work,
				usecs_to_jअगरfies(usecs) + 1))
			v4l2_warn(&sdev->sd,
				"(%s) Device took too much time to answer.\n",
				__func__);
	पूर्ण

	करो अणु
		err = i2c_master_recv(client, response, respn);
		अगर (err != respn) अणु
			v4l2_err(&sdev->sd,
				"Error %d while reading response for command 0x%02x\n",
				err, command);
			वापस err < 0 ? err : -EIO;
		पूर्ण

		DBG_BUFFER(&sdev->sd, "Response", response, respn);
		अगर (!check_command_failed(response[0]))
			वापस 0;

		अगर (client->irq)
			वापस -EBUSY;
		अगर (usecs <= 1000)
			usleep_range(usecs, 1000);
		अन्यथा
			usleep_range(1000, 2000);
	पूर्ण जबतक (समय_is_after_jअगरfies(until_jअगरfies));

	वापस -EBUSY;
पूर्ण

/*
 * si4713_पढ़ो_property - पढ़ोs a si4713 property
 * @sdev: si4713_device काष्ठाure क्रम the device we are communicating
 * @prop: property identअगरication number
 * @pv: property value to be वापसed on success
 */
अटल पूर्णांक si4713_पढ़ो_property(काष्ठा si4713_device *sdev, u16 prop, u32 *pv)
अणु
	पूर्णांक err;
	u8 val[SI4713_GET_PROP_NRESP];
	/*
	 *	.First byte = 0
	 *	.Second byte = property's MSB
	 *	.Third byte = property's LSB
	 */
	स्थिर u8 args[SI4713_GET_PROP_NARGS] = अणु
		0x00,
		msb(prop),
		lsb(prop),
	पूर्ण;

	err = si4713_send_command(sdev, SI4713_CMD_GET_PROPERTY,
				  args, ARRAY_SIZE(args), val,
				  ARRAY_SIZE(val), DEFAULT_TIMEOUT);

	अगर (err < 0)
		वापस err;

	*pv = compose_u16(val[2], val[3]);

	v4l2_dbg(1, debug, &sdev->sd,
			"%s: property=0x%02x value=0x%02x status=0x%02x\n",
			__func__, prop, *pv, val[0]);

	वापस err;
पूर्ण

/*
 * si4713_ग_लिखो_property - modअगरies a si4713 property
 * @sdev: si4713_device काष्ठाure क्रम the device we are communicating
 * @prop: property identअगरication number
 * @val: new value क्रम that property
 */
अटल पूर्णांक si4713_ग_लिखो_property(काष्ठा si4713_device *sdev, u16 prop, u16 val)
अणु
	पूर्णांक rval;
	u8 resp[SI4713_SET_PROP_NRESP];
	/*
	 *	.First byte = 0
	 *	.Second byte = property's MSB
	 *	.Third byte = property's LSB
	 *	.Fourth byte = value's MSB
	 *	.Fअगरth byte = value's LSB
	 */
	स्थिर u8 args[SI4713_SET_PROP_NARGS] = अणु
		0x00,
		msb(prop),
		lsb(prop),
		msb(val),
		lsb(val),
	पूर्ण;

	rval = si4713_send_command(sdev, SI4713_CMD_SET_PROPERTY,
					args, ARRAY_SIZE(args),
					resp, ARRAY_SIZE(resp),
					DEFAULT_TIMEOUT);

	अगर (rval < 0)
		वापस rval;

	v4l2_dbg(1, debug, &sdev->sd,
			"%s: property=0x%02x value=0x%02x status=0x%02x\n",
			__func__, prop, val, resp[0]);

	/*
	 * As there is no command response क्रम SET_PROPERTY,
	 * रुको Tcomp समय to finish beक्रमe proceed, in order
	 * to have property properly set.
	 */
	msleep(TIMEOUT_SET_PROPERTY);

	वापस rval;
पूर्ण

/*
 * si4713_घातerup - Powers the device up
 * @sdev: si4713_device काष्ठाure क्रम the device we are communicating
 */
अटल पूर्णांक si4713_घातerup(काष्ठा si4713_device *sdev)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sdev->sd);
	पूर्णांक err;
	u8 resp[SI4713_PWUP_NRESP];
	/*
	 *	.First byte = Enabled पूर्णांकerrupts and boot function
	 *	.Second byte = Input operation mode
	 */
	u8 args[SI4713_PWUP_NARGS] = अणु
		SI4713_PWUP_GPO2OEN | SI4713_PWUP_FUNC_TX,
		SI4713_PWUP_OPMOD_ANALOG,
	पूर्ण;

	अगर (sdev->घातer_state)
		वापस 0;

	अगर (sdev->vdd) अणु
		err = regulator_enable(sdev->vdd);
		अगर (err) अणु
			v4l2_err(&sdev->sd, "Failed to enable vdd: %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (sdev->vio) अणु
		err = regulator_enable(sdev->vio);
		अगर (err) अणु
			v4l2_err(&sdev->sd, "Failed to enable vio: %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (sdev->gpio_reset) अणु
		udelay(50);
		gpiod_set_value(sdev->gpio_reset, 1);
	पूर्ण

	अगर (client->irq)
		args[0] |= SI4713_PWUP_CTSIEN;

	err = si4713_send_command(sdev, SI4713_CMD_POWER_UP,
					args, ARRAY_SIZE(args),
					resp, ARRAY_SIZE(resp),
					TIMEOUT_POWER_UP);

	अगर (!err) अणु
		v4l2_dbg(1, debug, &sdev->sd, "Powerup response: 0x%02x\n",
				resp[0]);
		v4l2_dbg(1, debug, &sdev->sd, "Device in power up mode\n");
		sdev->घातer_state = POWER_ON;

		अगर (client->irq)
			err = si4713_ग_लिखो_property(sdev, SI4713_GPO_IEN,
						SI4713_STC_INT | SI4713_CTS);
		वापस err;
	पूर्ण
	gpiod_set_value(sdev->gpio_reset, 0);


	अगर (sdev->vdd) अणु
		err = regulator_disable(sdev->vdd);
		अगर (err)
			v4l2_err(&sdev->sd, "Failed to disable vdd: %d\n", err);
	पूर्ण

	अगर (sdev->vio) अणु
		err = regulator_disable(sdev->vio);
		अगर (err)
			v4l2_err(&sdev->sd, "Failed to disable vio: %d\n", err);
	पूर्ण

	वापस err;
पूर्ण

/*
 * si4713_घातerकरोwn - Powers the device करोwn
 * @sdev: si4713_device काष्ठाure क्रम the device we are communicating
 */
अटल पूर्णांक si4713_घातerकरोwn(काष्ठा si4713_device *sdev)
अणु
	पूर्णांक err;
	u8 resp[SI4713_PWDN_NRESP];

	अगर (!sdev->घातer_state)
		वापस 0;

	err = si4713_send_command(sdev, SI4713_CMD_POWER_DOWN,
					शून्य, 0,
					resp, ARRAY_SIZE(resp),
					DEFAULT_TIMEOUT);

	अगर (!err) अणु
		v4l2_dbg(1, debug, &sdev->sd, "Power down response: 0x%02x\n",
				resp[0]);
		v4l2_dbg(1, debug, &sdev->sd, "Device in reset mode\n");
		अगर (sdev->gpio_reset)
			gpiod_set_value(sdev->gpio_reset, 0);

		अगर (sdev->vdd) अणु
			err = regulator_disable(sdev->vdd);
			अगर (err) अणु
				v4l2_err(&sdev->sd,
					"Failed to disable vdd: %d\n", err);
			पूर्ण
		पूर्ण

		अगर (sdev->vio) अणु
			err = regulator_disable(sdev->vio);
			अगर (err) अणु
				v4l2_err(&sdev->sd,
					"Failed to disable vio: %d\n", err);
			पूर्ण
		पूर्ण
		sdev->घातer_state = POWER_OFF;
	पूर्ण

	वापस err;
पूर्ण

/*
 * si4713_checkrev - Checks अगर we are treating a device with the correct rev.
 * @sdev: si4713_device काष्ठाure क्रम the device we are communicating
 */
अटल पूर्णांक si4713_checkrev(काष्ठा si4713_device *sdev)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sdev->sd);
	पूर्णांक rval;
	u8 resp[SI4713_GETREV_NRESP];

	rval = si4713_send_command(sdev, SI4713_CMD_GET_REV,
					शून्य, 0,
					resp, ARRAY_SIZE(resp),
					DEFAULT_TIMEOUT);

	अगर (rval < 0)
		वापस rval;

	अगर (resp[1] == SI4713_PRODUCT_NUMBER) अणु
		v4l2_info(&sdev->sd, "chip found @ 0x%02x (%s)\n",
				client->addr << 1, client->adapter->name);
	पूर्ण अन्यथा अणु
		v4l2_err(&sdev->sd, "Invalid product number 0x%X\n", resp[1]);
		rval = -EINVAL;
	पूर्ण
	वापस rval;
पूर्ण

/*
 * si4713_रुको_stc - Waits STC पूर्णांकerrupt and clears status bits. Useful
 *		     क्रम TX_TUNE_POWER, TX_TUNE_FREQ and TX_TUNE_MEAS
 * @sdev: si4713_device काष्ठाure क्रम the device we are communicating
 * @usecs: समयout to रुको क्रम STC पूर्णांकerrupt संकेत
 */
अटल पूर्णांक si4713_रुको_stc(काष्ठा si4713_device *sdev, स्थिर पूर्णांक usecs)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sdev->sd);
	u8 resp[SI4713_GET_STATUS_NRESP];
	अचिन्हित दीर्घ start_jअगरfies = jअगरfies;
	पूर्णांक err;

	अगर (client->irq &&
	    !रुको_क्रम_completion_समयout(&sdev->work, usecs_to_jअगरfies(usecs) + 1))
		v4l2_warn(&sdev->sd,
			"(%s) Device took too much time to answer.\n", __func__);

	क्रम (;;) अणु
		/* Clear status bits */
		err = si4713_send_command(sdev, SI4713_CMD_GET_INT_STATUS,
				शून्य, 0,
				resp, ARRAY_SIZE(resp),
				DEFAULT_TIMEOUT);
		/* The USB device वापसs errors when it रुकोs क्रम the
		 * STC bit to be set. Hence polling */
		अगर (err >= 0) अणु
			v4l2_dbg(1, debug, &sdev->sd,
				"%s: status bits: 0x%02x\n", __func__, resp[0]);

			अगर (resp[0] & SI4713_STC_INT)
				वापस 0;
		पूर्ण
		अगर (jअगरfies_to_usecs(jअगरfies - start_jअगरfies) > usecs)
			वापस err < 0 ? err : -EIO;
		/* We sleep here क्रम 3-4 ms in order to aव्योम flooding the device
		 * with USB requests. The si4713 USB driver was developed
		 * by reverse engineering the Winकरोws USB driver. The winकरोws
		 * driver also has a ~2.5 ms delay between responses. */
		usleep_range(3000, 4000);
	पूर्ण
पूर्ण

/*
 * si4713_tx_tune_freq - Sets the state of the RF carrier and sets the tuning
 *			frequency between 76 and 108 MHz in 10 kHz units and
 *			steps of 50 kHz.
 * @sdev: si4713_device काष्ठाure क्रम the device we are communicating
 * @frequency: desired frequency (76 - 108 MHz, unit 10 KHz, step 50 kHz)
 */
अटल पूर्णांक si4713_tx_tune_freq(काष्ठा si4713_device *sdev, u16 frequency)
अणु
	पूर्णांक err;
	u8 val[SI4713_TXFREQ_NRESP];
	/*
	 *	.First byte = 0
	 *	.Second byte = frequency's MSB
	 *	.Third byte = frequency's LSB
	 */
	स्थिर u8 args[SI4713_TXFREQ_NARGS] = अणु
		0x00,
		msb(frequency),
		lsb(frequency),
	पूर्ण;

	err = si4713_send_command(sdev, SI4713_CMD_TX_TUNE_FREQ,
				  args, ARRAY_SIZE(args), val,
				  ARRAY_SIZE(val), DEFAULT_TIMEOUT);

	अगर (err < 0)
		वापस err;

	v4l2_dbg(1, debug, &sdev->sd,
			"%s: frequency=0x%02x status=0x%02x\n", __func__,
			frequency, val[0]);

	err = si4713_रुको_stc(sdev, TIMEOUT_TX_TUNE);
	अगर (err < 0)
		वापस err;

	वापस compose_u16(args[1], args[2]);
पूर्ण

/*
 * si4713_tx_tune_घातer - Sets the RF voltage level between 88 and 120 dBuV in
 *			1 dB units. A value of 0x00 indicates off. The command
 *			also sets the antenna tuning capacitance. A value of 0
 *			indicates स्वतःtuning, and a value of 1 - 191 indicates
 *			a manual override, which results in a tuning
 *			capacitance of 0.25 pF x @antcap.
 * @sdev: si4713_device काष्ठाure क्रम the device we are communicating
 * @घातer: tuning घातer (88 - 120 dBuV, unit/step 1 dB)
 * @antcap: value of antenna tuning capacitor (0 - 191)
 */
अटल पूर्णांक si4713_tx_tune_घातer(काष्ठा si4713_device *sdev, u8 घातer,
				u8 antcap)
अणु
	पूर्णांक err;
	u8 val[SI4713_TXPWR_NRESP];
	/*
	 *	.First byte = 0
	 *	.Second byte = 0
	 *	.Third byte = घातer
	 *	.Fourth byte = antcap
	 */
	u8 args[SI4713_TXPWR_NARGS] = अणु
		0x00,
		0x00,
		घातer,
		antcap,
	पूर्ण;

	/* Map घातer values 1-87 to MIN_POWER (88) */
	अगर (घातer > 0 && घातer < SI4713_MIN_POWER)
		args[2] = घातer = SI4713_MIN_POWER;

	err = si4713_send_command(sdev, SI4713_CMD_TX_TUNE_POWER,
				  args, ARRAY_SIZE(args), val,
				  ARRAY_SIZE(val), DEFAULT_TIMEOUT);

	अगर (err < 0)
		वापस err;

	v4l2_dbg(1, debug, &sdev->sd,
			"%s: power=0x%02x antcap=0x%02x status=0x%02x\n",
			__func__, घातer, antcap, val[0]);

	वापस si4713_रुको_stc(sdev, TIMEOUT_TX_TUNE_POWER);
पूर्ण

/*
 * si4713_tx_tune_measure - Enters receive mode and measures the received noise
 *			level in units of dBuV on the selected frequency.
 *			The Frequency must be between 76 and 108 MHz in 10 kHz
 *			units and steps of 50 kHz. The command also sets the
 *			antenna	tuning capacitance. A value of 0 means
 *			स्वतःtuning, and a value of 1 to 191 indicates manual
 *			override.
 * @sdev: si4713_device काष्ठाure क्रम the device we are communicating
 * @frequency: desired frequency (76 - 108 MHz, unit 10 KHz, step 50 kHz)
 * @antcap: value of antenna tuning capacitor (0 - 191)
 */
अटल पूर्णांक si4713_tx_tune_measure(काष्ठा si4713_device *sdev, u16 frequency,
					u8 antcap)
अणु
	पूर्णांक err;
	u8 val[SI4713_TXMEA_NRESP];
	/*
	 *	.First byte = 0
	 *	.Second byte = frequency's MSB
	 *	.Third byte = frequency's LSB
	 *	.Fourth byte = antcap
	 */
	स्थिर u8 args[SI4713_TXMEA_NARGS] = अणु
		0x00,
		msb(frequency),
		lsb(frequency),
		antcap,
	पूर्ण;

	sdev->tune_rnl = DEFAULT_TUNE_RNL;

	अगर (antcap > SI4713_MAX_ANTCAP)
		वापस -गलत_तर्क;

	err = si4713_send_command(sdev, SI4713_CMD_TX_TUNE_MEASURE,
				  args, ARRAY_SIZE(args), val,
				  ARRAY_SIZE(val), DEFAULT_TIMEOUT);

	अगर (err < 0)
		वापस err;

	v4l2_dbg(1, debug, &sdev->sd,
			"%s: frequency=0x%02x antcap=0x%02x status=0x%02x\n",
			__func__, frequency, antcap, val[0]);

	वापस si4713_रुको_stc(sdev, TIMEOUT_TX_TUNE);
पूर्ण

/*
 * si4713_tx_tune_status- Returns the status of the tx_tune_freq, tx_tune_mea or
 *			tx_tune_घातer commands. This command वापस the current
 *			frequency, output voltage in dBuV, the antenna tunning
 *			capacitance value and the received noise level. The
 *			command also clears the stcपूर्णांक पूर्णांकerrupt bit when the
 *			first bit of its arguments is high.
 * @sdev: si4713_device काष्ठाure क्रम the device we are communicating
 * @पूर्णांकack: 0x01 to clear the seek/tune complete पूर्णांकerrupt status indicator.
 * @frequency: वापसed frequency
 * @घातer: वापसed घातer
 * @antcap: वापसed antenna capacitance
 * @noise: वापसed noise level
 */
अटल पूर्णांक si4713_tx_tune_status(काष्ठा si4713_device *sdev, u8 पूर्णांकack,
					u16 *frequency,	u8 *घातer,
					u8 *antcap, u8 *noise)
अणु
	पूर्णांक err;
	u8 val[SI4713_TXSTATUS_NRESP];
	/*
	 *	.First byte = पूर्णांकack bit
	 */
	स्थिर u8 args[SI4713_TXSTATUS_NARGS] = अणु
		पूर्णांकack & SI4713_INTACK_MASK,
	पूर्ण;

	err = si4713_send_command(sdev, SI4713_CMD_TX_TUNE_STATUS,
				  args, ARRAY_SIZE(args), val,
				  ARRAY_SIZE(val), DEFAULT_TIMEOUT);

	अगर (!err) अणु
		v4l2_dbg(1, debug, &sdev->sd,
			"%s: status=0x%02x\n", __func__, val[0]);
		*frequency = compose_u16(val[2], val[3]);
		sdev->frequency = *frequency;
		*घातer = val[5];
		*antcap = val[6];
		*noise = val[7];
		v4l2_dbg(1, debug, &sdev->sd,
			 "%s: response: %d x 10 kHz (power %d, antcap %d, rnl %d)\n",
			 __func__, *frequency, *घातer, *antcap, *noise);
	पूर्ण

	वापस err;
पूर्ण

/*
 * si4713_tx_rds_buff - Loads the RDS group buffer FIFO or circular buffer.
 * @sdev: si4713_device काष्ठाure क्रम the device we are communicating
 * @mode: the buffer operation mode.
 * @rdsb: RDS Block B
 * @rdsc: RDS Block C
 * @rdsd: RDS Block D
 * @cbleft: वापसs the number of available circular buffer blocks minus the
 *          number of used circular buffer blocks.
 */
अटल पूर्णांक si4713_tx_rds_buff(काष्ठा si4713_device *sdev, u8 mode, u16 rdsb,
				u16 rdsc, u16 rdsd, s8 *cbleft)
अणु
	पूर्णांक err;
	u8 val[SI4713_RDSBUFF_NRESP];

	स्थिर u8 args[SI4713_RDSBUFF_NARGS] = अणु
		mode & SI4713_RDSBUFF_MODE_MASK,
		msb(rdsb),
		lsb(rdsb),
		msb(rdsc),
		lsb(rdsc),
		msb(rdsd),
		lsb(rdsd),
	पूर्ण;

	err = si4713_send_command(sdev, SI4713_CMD_TX_RDS_BUFF,
				  args, ARRAY_SIZE(args), val,
				  ARRAY_SIZE(val), DEFAULT_TIMEOUT);

	अगर (!err) अणु
		v4l2_dbg(1, debug, &sdev->sd,
			"%s: status=0x%02x\n", __func__, val[0]);
		*cbleft = (s8)val[2] - val[3];
		v4l2_dbg(1, debug, &sdev->sd,
			 "%s: response: interrupts 0x%02x cb avail: %d cb used %d fifo avail %d fifo used %d\n",
			 __func__, val[1], val[2], val[3], val[4], val[5]);
	पूर्ण

	वापस err;
पूर्ण

/*
 * si4713_tx_rds_ps - Loads the program service buffer.
 * @sdev: si4713_device काष्ठाure क्रम the device we are communicating
 * @psid: program service id to be loaded.
 * @psअक्षर: assumed 4 size अक्षर array to be loaded पूर्णांकo the program service
 */
अटल पूर्णांक si4713_tx_rds_ps(काष्ठा si4713_device *sdev, u8 psid,
				अचिन्हित अक्षर *psअक्षर)
अणु
	पूर्णांक err;
	u8 val[SI4713_RDSPS_NRESP];

	स्थिर u8 args[SI4713_RDSPS_NARGS] = अणु
		psid & SI4713_RDSPS_PSID_MASK,
		psअक्षर[0],
		psअक्षर[1],
		psअक्षर[2],
		psअक्षर[3],
	पूर्ण;

	err = si4713_send_command(sdev, SI4713_CMD_TX_RDS_PS,
				  args, ARRAY_SIZE(args), val,
				  ARRAY_SIZE(val), DEFAULT_TIMEOUT);

	अगर (err < 0)
		वापस err;

	v4l2_dbg(1, debug, &sdev->sd, "%s: status=0x%02x\n", __func__, val[0]);

	वापस err;
पूर्ण

अटल पूर्णांक si4713_set_घातer_state(काष्ठा si4713_device *sdev, u8 value)
अणु
	अगर (value)
		वापस si4713_घातerup(sdev);
	वापस si4713_घातerकरोwn(sdev);
पूर्ण

अटल पूर्णांक si4713_set_mute(काष्ठा si4713_device *sdev, u16 mute)
अणु
	पूर्णांक rval = 0;

	mute = set_mute(mute);

	अगर (sdev->घातer_state)
		rval = si4713_ग_लिखो_property(sdev,
				SI4713_TX_LINE_INPUT_MUTE, mute);

	वापस rval;
पूर्ण

अटल पूर्णांक si4713_set_rds_ps_name(काष्ठा si4713_device *sdev, अक्षर *ps_name)
अणु
	पूर्णांक rval = 0, i;
	u8 len = 0;

	/* We want to clear the whole thing */
	अगर (!म_माप(ps_name))
		स_रखो(ps_name, 0, MAX_RDS_PS_NAME + 1);

	अगर (sdev->घातer_state) अणु
		/* Write the new ps name and clear the padding */
		क्रम (i = 0; i < MAX_RDS_PS_NAME; i += (RDS_BLOCK / 2)) अणु
			rval = si4713_tx_rds_ps(sdev, (i / (RDS_BLOCK / 2)),
						ps_name + i);
			अगर (rval < 0)
				वापस rval;
		पूर्ण

		/* Setup the size to be sent */
		अगर (म_माप(ps_name))
			len = म_माप(ps_name) - 1;
		अन्यथा
			len = 1;

		rval = si4713_ग_लिखो_property(sdev,
				SI4713_TX_RDS_PS_MESSAGE_COUNT,
				rds_ps_nblocks(len));
		अगर (rval < 0)
			वापस rval;

		rval = si4713_ग_लिखो_property(sdev,
				SI4713_TX_RDS_PS_REPEAT_COUNT,
				DEFAULT_RDS_PS_REPEAT_COUNT * 2);
		अगर (rval < 0)
			वापस rval;
	पूर्ण

	वापस rval;
पूर्ण

अटल पूर्णांक si4713_set_rds_radio_text(काष्ठा si4713_device *sdev, स्थिर अक्षर *rt)
अणु
	अटल स्थिर अक्षर cr[RDS_RADIOTEXT_BLK_SIZE] = अणु RDS_CARRIAGE_RETURN, 0 पूर्ण;
	पूर्णांक rval = 0, i;
	u16 t_index = 0;
	u8 b_index = 0, cr_inserted = 0;
	s8 left;

	अगर (!sdev->घातer_state)
		वापस rval;

	rval = si4713_tx_rds_buff(sdev, RDS_BLOCK_CLEAR, 0, 0, 0, &left);
	अगर (rval < 0)
		वापस rval;

	अगर (!म_माप(rt))
		वापस rval;

	करो अणु
		/* RDS spec says that अगर the last block isn't used,
		 * then apply a carriage वापस
		 */
		अगर (t_index < (RDS_RADIOTEXT_INDEX_MAX * RDS_RADIOTEXT_BLK_SIZE)) अणु
			क्रम (i = 0; i < RDS_RADIOTEXT_BLK_SIZE; i++) अणु
				अगर (!rt[t_index + i] ||
				    rt[t_index + i] == RDS_CARRIAGE_RETURN) अणु
					rt = cr;
					cr_inserted = 1;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		rval = si4713_tx_rds_buff(sdev, RDS_BLOCK_LOAD,
				compose_u16(RDS_RADIOTEXT_2A, b_index++),
				compose_u16(rt[t_index], rt[t_index + 1]),
				compose_u16(rt[t_index + 2], rt[t_index + 3]),
				&left);
		अगर (rval < 0)
			वापस rval;

		t_index += RDS_RADIOTEXT_BLK_SIZE;

		अगर (cr_inserted)
			अवरोध;
	पूर्ण जबतक (left > 0);

	वापस rval;
पूर्ण

/*
 * si4713_update_tune_status - update properties from tx_tune_status
 * command. Must be called with sdev->mutex held.
 * @sdev: si4713_device काष्ठाure क्रम the device we are communicating
 */
अटल पूर्णांक si4713_update_tune_status(काष्ठा si4713_device *sdev)
अणु
	पूर्णांक rval;
	u16 f = 0;
	u8 p = 0, a = 0, n = 0;

	rval = si4713_tx_tune_status(sdev, 0x00, &f, &p, &a, &n);

	अगर (rval < 0)
		जाओ निकास;

/*	TODO: check that घातer_level and antenna_capacitor really are not
	changed by the hardware. If they are, then these controls should become
	अस्थिरs.
	sdev->घातer_level = p;
	sdev->antenna_capacitor = a;*/
	sdev->tune_rnl = n;

निकास:
	वापस rval;
पूर्ण

अटल पूर्णांक si4713_choose_econtrol_action(काष्ठा si4713_device *sdev, u32 id,
		s32 *bit, s32 *mask, u16 *property, पूर्णांक *mul,
		अचिन्हित दीर्घ **table, पूर्णांक *size)
अणु
	s32 rval = 0;

	चयन (id) अणु
	/* FM_TX class controls */
	हाल V4L2_CID_RDS_TX_PI:
		*property = SI4713_TX_RDS_PI;
		*mul = 1;
		अवरोध;
	हाल V4L2_CID_AUDIO_COMPRESSION_THRESHOLD:
		*property = SI4713_TX_ACOMP_THRESHOLD;
		*mul = 1;
		अवरोध;
	हाल V4L2_CID_AUDIO_COMPRESSION_GAIN:
		*property = SI4713_TX_ACOMP_GAIN;
		*mul = 1;
		अवरोध;
	हाल V4L2_CID_PILOT_TONE_FREQUENCY:
		*property = SI4713_TX_PILOT_FREQUENCY;
		*mul = 1;
		अवरोध;
	हाल V4L2_CID_AUDIO_COMPRESSION_ATTACK_TIME:
		*property = SI4713_TX_ACOMP_ATTACK_TIME;
		*mul = ATTACK_TIME_UNIT;
		अवरोध;
	हाल V4L2_CID_PILOT_TONE_DEVIATION:
		*property = SI4713_TX_PILOT_DEVIATION;
		*mul = 10;
		अवरोध;
	हाल V4L2_CID_AUDIO_LIMITER_DEVIATION:
		*property = SI4713_TX_AUDIO_DEVIATION;
		*mul = 10;
		अवरोध;
	हाल V4L2_CID_RDS_TX_DEVIATION:
		*property = SI4713_TX_RDS_DEVIATION;
		*mul = 1;
		अवरोध;

	हाल V4L2_CID_RDS_TX_PTY:
		*property = SI4713_TX_RDS_PS_MISC;
		*bit = 5;
		*mask = 0x1F << 5;
		अवरोध;
	हाल V4L2_CID_RDS_TX_DYNAMIC_PTY:
		*property = SI4713_TX_RDS_PS_MISC;
		*bit = 15;
		*mask = 1 << 15;
		अवरोध;
	हाल V4L2_CID_RDS_TX_COMPRESSED:
		*property = SI4713_TX_RDS_PS_MISC;
		*bit = 14;
		*mask = 1 << 14;
		अवरोध;
	हाल V4L2_CID_RDS_TX_ARTIFICIAL_HEAD:
		*property = SI4713_TX_RDS_PS_MISC;
		*bit = 13;
		*mask = 1 << 13;
		अवरोध;
	हाल V4L2_CID_RDS_TX_MONO_STEREO:
		*property = SI4713_TX_RDS_PS_MISC;
		*bit = 12;
		*mask = 1 << 12;
		अवरोध;
	हाल V4L2_CID_RDS_TX_TRAFFIC_PROGRAM:
		*property = SI4713_TX_RDS_PS_MISC;
		*bit = 10;
		*mask = 1 << 10;
		अवरोध;
	हाल V4L2_CID_RDS_TX_TRAFFIC_ANNOUNCEMENT:
		*property = SI4713_TX_RDS_PS_MISC;
		*bit = 4;
		*mask = 1 << 4;
		अवरोध;
	हाल V4L2_CID_RDS_TX_MUSIC_SPEECH:
		*property = SI4713_TX_RDS_PS_MISC;
		*bit = 3;
		*mask = 1 << 3;
		अवरोध;
	हाल V4L2_CID_AUDIO_LIMITER_ENABLED:
		*property = SI4713_TX_ACOMP_ENABLE;
		*bit = 1;
		*mask = 1 << 1;
		अवरोध;
	हाल V4L2_CID_AUDIO_COMPRESSION_ENABLED:
		*property = SI4713_TX_ACOMP_ENABLE;
		*bit = 0;
		*mask = 1 << 0;
		अवरोध;
	हाल V4L2_CID_PILOT_TONE_ENABLED:
		*property = SI4713_TX_COMPONENT_ENABLE;
		*bit = 0;
		*mask = 1 << 0;
		अवरोध;

	हाल V4L2_CID_AUDIO_LIMITER_RELEASE_TIME:
		*property = SI4713_TX_LIMITER_RELEASE_TIME;
		*table = limiter_बार;
		*size = ARRAY_SIZE(limiter_बार);
		अवरोध;
	हाल V4L2_CID_AUDIO_COMPRESSION_RELEASE_TIME:
		*property = SI4713_TX_ACOMP_RELEASE_TIME;
		*table = acomp_rबार;
		*size = ARRAY_SIZE(acomp_rबार);
		अवरोध;
	हाल V4L2_CID_TUNE_PREEMPHASIS:
		*property = SI4713_TX_PREEMPHASIS;
		*table = preemphasis_values;
		*size = ARRAY_SIZE(preemphasis_values);
		अवरोध;

	शेष:
		rval = -EINVAL;
		अवरोध;
	पूर्ण

	वापस rval;
पूर्ण

अटल पूर्णांक si4713_s_frequency(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_frequency *f);
अटल पूर्णांक si4713_s_modulator(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_modulator *);
/*
 * si4713_setup - Sets the device up with current configuration.
 * @sdev: si4713_device काष्ठाure क्रम the device we are communicating
 */
अटल पूर्णांक si4713_setup(काष्ठा si4713_device *sdev)
अणु
	काष्ठा v4l2_frequency f;
	काष्ठा v4l2_modulator vm;
	पूर्णांक rval;

	/* Device procedure needs to set frequency first */
	f.tuner = 0;
	f.frequency = sdev->frequency ? sdev->frequency : DEFAULT_FREQUENCY;
	f.frequency = si4713_to_v4l2(f.frequency);
	rval = si4713_s_frequency(&sdev->sd, &f);

	vm.index = 0;
	अगर (sdev->stereo)
		vm.txsubchans = V4L2_TUNER_SUB_STEREO;
	अन्यथा
		vm.txsubchans = V4L2_TUNER_SUB_MONO;
	अगर (sdev->rds_enabled)
		vm.txsubchans |= V4L2_TUNER_SUB_RDS;
	si4713_s_modulator(&sdev->sd, &vm);

	वापस rval;
पूर्ण

/*
 * si4713_initialize - Sets the device up with शेष configuration.
 * @sdev: si4713_device काष्ठाure क्रम the device we are communicating
 */
अटल पूर्णांक si4713_initialize(काष्ठा si4713_device *sdev)
अणु
	पूर्णांक rval;

	rval = si4713_set_घातer_state(sdev, POWER_ON);
	अगर (rval < 0)
		वापस rval;

	rval = si4713_checkrev(sdev);
	अगर (rval < 0)
		वापस rval;

	rval = si4713_set_घातer_state(sdev, POWER_OFF);
	अगर (rval < 0)
		वापस rval;

	sdev->frequency = DEFAULT_FREQUENCY;
	sdev->stereo = 1;
	sdev->tune_rnl = DEFAULT_TUNE_RNL;
	वापस 0;
पूर्ण

/* si4713_s_ctrl - set the value of a control */
अटल पूर्णांक si4713_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा si4713_device *sdev =
		container_of(ctrl->handler, काष्ठा si4713_device, ctrl_handler);
	u32 val = 0;
	s32 bit = 0, mask = 0;
	u16 property = 0;
	पूर्णांक mul = 0;
	अचिन्हित दीर्घ *table = शून्य;
	पूर्णांक size = 0;
	bool क्रमce = false;
	पूर्णांक c;
	पूर्णांक ret = 0;

	अगर (ctrl->id != V4L2_CID_AUDIO_MUTE)
		वापस -EINVAL;
	अगर (ctrl->is_new) अणु
		अगर (ctrl->val) अणु
			ret = si4713_set_mute(sdev, ctrl->val);
			अगर (!ret)
				ret = si4713_set_घातer_state(sdev, POWER_DOWN);
			वापस ret;
		पूर्ण
		ret = si4713_set_घातer_state(sdev, POWER_UP);
		अगर (!ret)
			ret = si4713_set_mute(sdev, ctrl->val);
		अगर (!ret)
			ret = si4713_setup(sdev);
		अगर (ret)
			वापस ret;
		क्रमce = true;
	पूर्ण

	अगर (!sdev->घातer_state)
		वापस 0;

	क्रम (c = 1; !ret && c < ctrl->ncontrols; c++) अणु
		ctrl = ctrl->cluster[c];

		अगर (!क्रमce && !ctrl->is_new)
			जारी;

		चयन (ctrl->id) अणु
		हाल V4L2_CID_RDS_TX_PS_NAME:
			ret = si4713_set_rds_ps_name(sdev, ctrl->p_new.p_अक्षर);
			अवरोध;

		हाल V4L2_CID_RDS_TX_RADIO_TEXT:
			ret = si4713_set_rds_radio_text(sdev, ctrl->p_new.p_अक्षर);
			अवरोध;

		हाल V4L2_CID_TUNE_ANTENNA_CAPACITOR:
			/* करोn't handle this control अगर we क्रमce setting all
			 * controls since in that हाल it will be handled by
			 * V4L2_CID_TUNE_POWER_LEVEL. */
			अगर (क्रमce)
				अवरोध;
			fallthrough;
		हाल V4L2_CID_TUNE_POWER_LEVEL:
			ret = si4713_tx_tune_घातer(sdev,
				sdev->tune_pwr_level->val, sdev->tune_ant_cap->val);
			अगर (!ret) अणु
				/* Make sure we करोn't set this twice */
				sdev->tune_ant_cap->is_new = false;
				sdev->tune_pwr_level->is_new = false;
			पूर्ण
			अवरोध;

		हाल V4L2_CID_RDS_TX_ALT_FREQS_ENABLE:
		हाल V4L2_CID_RDS_TX_ALT_FREQS:
			अगर (sdev->rds_alt_freqs_enable->val) अणु
				val = sdev->rds_alt_freqs->p_new.p_u32[0];
				val = val / 100 - 876 + 0xe101;
			पूर्ण अन्यथा अणु
				val = 0xe0e0;
			पूर्ण
			ret = si4713_ग_लिखो_property(sdev, SI4713_TX_RDS_PS_AF, val);
			अवरोध;

		शेष:
			ret = si4713_choose_econtrol_action(sdev, ctrl->id, &bit,
					&mask, &property, &mul, &table, &size);
			अगर (ret < 0)
				अवरोध;

			val = ctrl->val;
			अगर (mul) अणु
				val = val / mul;
			पूर्ण अन्यथा अगर (table) अणु
				ret = usecs_to_dev(val, table, size);
				अगर (ret < 0)
					अवरोध;
				val = ret;
				ret = 0;
			पूर्ण

			अगर (mask) अणु
				ret = si4713_पढ़ो_property(sdev, property, &val);
				अगर (ret < 0)
					अवरोध;
				val = set_bits(val, ctrl->val, bit, mask);
			पूर्ण

			ret = si4713_ग_लिखो_property(sdev, property, val);
			अगर (ret < 0)
				अवरोध;
			अगर (mask)
				val = ctrl->val;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/* si4713_ioctl - deal with निजी ioctls (only rnl क्रम now) */
अटल दीर्घ si4713_ioctl(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा si4713_device *sdev = to_si4713_device(sd);
	काष्ठा si4713_rnl *rnl = arg;
	u16 frequency;
	पूर्णांक rval = 0;

	अगर (!arg)
		वापस -EINVAL;

	चयन (cmd) अणु
	हाल SI4713_IOC_MEASURE_RNL:
		frequency = v4l2_to_si4713(rnl->frequency);

		अगर (sdev->घातer_state) अणु
			/* Set desired measurement frequency */
			rval = si4713_tx_tune_measure(sdev, frequency, 0);
			अगर (rval < 0)
				वापस rval;
			/* get results from tune status */
			rval = si4713_update_tune_status(sdev);
			अगर (rval < 0)
				वापस rval;
		पूर्ण
		rnl->rnl = sdev->tune_rnl;
		अवरोध;

	शेष:
		/* nothing */
		rval = -ENOIOCTLCMD;
	पूर्ण

	वापस rval;
पूर्ण

/* si4713_g_modulator - get modulator attributes */
अटल पूर्णांक si4713_g_modulator(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_modulator *vm)
अणु
	काष्ठा si4713_device *sdev = to_si4713_device(sd);
	पूर्णांक rval = 0;

	अगर (!sdev)
		वापस -ENODEV;

	अगर (vm->index > 0)
		वापस -EINVAL;

	strscpy(vm->name, "FM Modulator", माप(vm->name));
	vm->capability = V4L2_TUNER_CAP_STEREO | V4L2_TUNER_CAP_LOW |
		V4L2_TUNER_CAP_RDS | V4L2_TUNER_CAP_RDS_CONTROLS;

	/* Report current frequency range limits */
	vm->rangelow = si4713_to_v4l2(FREQ_RANGE_LOW);
	vm->rangehigh = si4713_to_v4l2(FREQ_RANGE_HIGH);

	अगर (sdev->घातer_state) अणु
		u32 comp_en = 0;

		rval = si4713_पढ़ो_property(sdev, SI4713_TX_COMPONENT_ENABLE,
						&comp_en);
		अगर (rval < 0)
			वापस rval;

		sdev->stereo = get_status_bit(comp_en, 1, 1 << 1);
	पूर्ण

	/* Report current audio mode: mono or stereo */
	अगर (sdev->stereo)
		vm->txsubchans = V4L2_TUNER_SUB_STEREO;
	अन्यथा
		vm->txsubchans = V4L2_TUNER_SUB_MONO;

	/* Report rds feature status */
	अगर (sdev->rds_enabled)
		vm->txsubchans |= V4L2_TUNER_SUB_RDS;
	अन्यथा
		vm->txsubchans &= ~V4L2_TUNER_SUB_RDS;

	वापस rval;
पूर्ण

/* si4713_s_modulator - set modulator attributes */
अटल पूर्णांक si4713_s_modulator(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_modulator *vm)
अणु
	काष्ठा si4713_device *sdev = to_si4713_device(sd);
	पूर्णांक rval = 0;
	u16 stereo, rds;
	u32 p;

	अगर (!sdev)
		वापस -ENODEV;

	अगर (vm->index > 0)
		वापस -EINVAL;

	/* Set audio mode: mono or stereo */
	अगर (vm->txsubchans & V4L2_TUNER_SUB_STEREO)
		stereo = 1;
	अन्यथा अगर (vm->txsubchans & V4L2_TUNER_SUB_MONO)
		stereo = 0;
	अन्यथा
		वापस -EINVAL;

	rds = !!(vm->txsubchans & V4L2_TUNER_SUB_RDS);

	अगर (sdev->घातer_state) अणु
		rval = si4713_पढ़ो_property(sdev,
						SI4713_TX_COMPONENT_ENABLE, &p);
		अगर (rval < 0)
			वापस rval;

		p = set_bits(p, stereo, 1, 1 << 1);
		p = set_bits(p, rds, 2, 1 << 2);

		rval = si4713_ग_लिखो_property(sdev,
						SI4713_TX_COMPONENT_ENABLE, p);
		अगर (rval < 0)
			वापस rval;
	पूर्ण

	sdev->stereo = stereo;
	sdev->rds_enabled = rds;

	वापस rval;
पूर्ण

/* si4713_g_frequency - get tuner or modulator radio frequency */
अटल पूर्णांक si4713_g_frequency(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_frequency *f)
अणु
	काष्ठा si4713_device *sdev = to_si4713_device(sd);
	पूर्णांक rval = 0;

	अगर (f->tuner)
		वापस -EINVAL;

	अगर (sdev->घातer_state) अणु
		u16 freq;
		u8 p, a, n;

		rval = si4713_tx_tune_status(sdev, 0x00, &freq, &p, &a, &n);
		अगर (rval < 0)
			वापस rval;

		sdev->frequency = freq;
	पूर्ण

	f->frequency = si4713_to_v4l2(sdev->frequency);

	वापस rval;
पूर्ण

/* si4713_s_frequency - set tuner or modulator radio frequency */
अटल पूर्णांक si4713_s_frequency(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा si4713_device *sdev = to_si4713_device(sd);
	पूर्णांक rval = 0;
	u16 frequency = v4l2_to_si4713(f->frequency);

	अगर (f->tuner)
		वापस -EINVAL;

	/* Check frequency range */
	frequency = clamp_t(u16, frequency, FREQ_RANGE_LOW, FREQ_RANGE_HIGH);

	अगर (sdev->घातer_state) अणु
		rval = si4713_tx_tune_freq(sdev, frequency);
		अगर (rval < 0)
			वापस rval;
		frequency = rval;
		rval = 0;
	पूर्ण
	sdev->frequency = frequency;

	वापस rval;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops si4713_ctrl_ops = अणु
	.s_ctrl = si4713_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops si4713_subdev_core_ops = अणु
	.ioctl		= si4713_ioctl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_tuner_ops si4713_subdev_tuner_ops = अणु
	.g_frequency	= si4713_g_frequency,
	.s_frequency	= si4713_s_frequency,
	.g_modulator	= si4713_g_modulator,
	.s_modulator	= si4713_s_modulator,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops si4713_subdev_ops = अणु
	.core		= &si4713_subdev_core_ops,
	.tuner		= &si4713_subdev_tuner_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config si4713_alt_freqs_ctrl = अणु
	.id = V4L2_CID_RDS_TX_ALT_FREQS,
	.type = V4L2_CTRL_TYPE_U32,
	.min = 87600,
	.max = 107900,
	.step = 100,
	.def = 87600,
	.dims = अणु 1 पूर्ण,
	.elem_size = माप(u32),
पूर्ण;

/*
 * I2C driver पूर्णांकerface
 */
/* si4713_probe - probe क्रम the device */
अटल पूर्णांक si4713_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा si4713_device *sdev;
	काष्ठा v4l2_ctrl_handler *hdl;
	काष्ठा si4713_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा device_node *np = client->dev.of_node;
	काष्ठा radio_si4713_platक्रमm_data si4713_pdev_pdata;
	काष्ठा platक्रमm_device *si4713_pdev;
	पूर्णांक rval;

	sdev = devm_kzalloc(&client->dev, माप(*sdev), GFP_KERNEL);
	अगर (!sdev) अणु
		dev_err(&client->dev, "Failed to alloc video device.\n");
		rval = -ENOMEM;
		जाओ निकास;
	पूर्ण

	sdev->gpio_reset = devm_gpiod_get_optional(&client->dev, "reset",
						   GPIOD_OUT_LOW);
	अगर (IS_ERR(sdev->gpio_reset)) अणु
		rval = PTR_ERR(sdev->gpio_reset);
		dev_err(&client->dev, "Failed to request gpio: %d\n", rval);
		जाओ निकास;
	पूर्ण

	sdev->vdd = devm_regulator_get_optional(&client->dev, "vdd");
	अगर (IS_ERR(sdev->vdd)) अणु
		rval = PTR_ERR(sdev->vdd);
		अगर (rval == -EPROBE_DEFER)
			जाओ निकास;

		dev_dbg(&client->dev, "no vdd regulator found: %d\n", rval);
		sdev->vdd = शून्य;
	पूर्ण

	sdev->vio = devm_regulator_get_optional(&client->dev, "vio");
	अगर (IS_ERR(sdev->vio)) अणु
		rval = PTR_ERR(sdev->vio);
		अगर (rval == -EPROBE_DEFER)
			जाओ निकास;

		dev_dbg(&client->dev, "no vio regulator found: %d\n", rval);
		sdev->vio = शून्य;
	पूर्ण

	v4l2_i2c_subdev_init(&sdev->sd, client, &si4713_subdev_ops);

	init_completion(&sdev->work);

	hdl = &sdev->ctrl_handler;
	v4l2_ctrl_handler_init(hdl, 20);
	sdev->mute = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, DEFAULT_MUTE);

	sdev->rds_pi = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_RDS_TX_PI, 0, 0xffff, 1, DEFAULT_RDS_PI);
	sdev->rds_pty = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_RDS_TX_PTY, 0, 31, 1, DEFAULT_RDS_PTY);
	sdev->rds_compressed = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_RDS_TX_COMPRESSED, 0, 1, 1, 0);
	sdev->rds_art_head = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_RDS_TX_ARTIFICIAL_HEAD, 0, 1, 1, 0);
	sdev->rds_stereo = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_RDS_TX_MONO_STEREO, 0, 1, 1, 1);
	sdev->rds_tp = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_RDS_TX_TRAFFIC_PROGRAM, 0, 1, 1, 0);
	sdev->rds_ta = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_RDS_TX_TRAFFIC_ANNOUNCEMENT, 0, 1, 1, 0);
	sdev->rds_ms = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_RDS_TX_MUSIC_SPEECH, 0, 1, 1, 1);
	sdev->rds_dyn_pty = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_RDS_TX_DYNAMIC_PTY, 0, 1, 1, 0);
	sdev->rds_alt_freqs_enable = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_RDS_TX_ALT_FREQS_ENABLE, 0, 1, 1, 0);
	sdev->rds_alt_freqs = v4l2_ctrl_new_custom(hdl, &si4713_alt_freqs_ctrl, शून्य);
	sdev->rds_deviation = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_RDS_TX_DEVIATION, 0, MAX_RDS_DEVIATION,
			10, DEFAULT_RDS_DEVIATION);
	/*
	 * Report step as 8. From RDS spec, psname
	 * should be 8. But there are receivers which scroll strings
	 * sized as 8xN.
	 */
	sdev->rds_ps_name = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_RDS_TX_PS_NAME, 0, MAX_RDS_PS_NAME, 8, 0);
	/*
	 * Report step as 32 (2A block). From RDS spec,
	 * radio text should be 32 क्रम 2A block. But there are receivers
	 * which scroll strings sized as 32xN. Setting शेष to 32.
	 */
	sdev->rds_radio_text = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_RDS_TX_RADIO_TEXT, 0, MAX_RDS_RADIO_TEXT, 32, 0);

	sdev->limiter_enabled = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_AUDIO_LIMITER_ENABLED, 0, 1, 1, 1);
	sdev->limiter_release_समय = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_AUDIO_LIMITER_RELEASE_TIME, 250,
			MAX_LIMITER_RELEASE_TIME, 10, DEFAULT_LIMITER_RTIME);
	sdev->limiter_deviation = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_AUDIO_LIMITER_DEVIATION, 0,
			MAX_LIMITER_DEVIATION, 10, DEFAULT_LIMITER_DEV);

	sdev->compression_enabled = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_AUDIO_COMPRESSION_ENABLED, 0, 1, 1, 1);
	sdev->compression_gain = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_AUDIO_COMPRESSION_GAIN, 0, MAX_ACOMP_GAIN, 1,
			DEFAULT_ACOMP_GAIN);
	sdev->compression_threshold = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_AUDIO_COMPRESSION_THRESHOLD,
			MIN_ACOMP_THRESHOLD, MAX_ACOMP_THRESHOLD, 1,
			DEFAULT_ACOMP_THRESHOLD);
	sdev->compression_attack_समय = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_AUDIO_COMPRESSION_ATTACK_TIME, 0,
			MAX_ACOMP_ATTACK_TIME, 500, DEFAULT_ACOMP_ATIME);
	sdev->compression_release_समय = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_AUDIO_COMPRESSION_RELEASE_TIME, 100000,
			MAX_ACOMP_RELEASE_TIME, 100000, DEFAULT_ACOMP_RTIME);

	sdev->pilot_tone_enabled = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_PILOT_TONE_ENABLED, 0, 1, 1, 1);
	sdev->pilot_tone_deviation = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_PILOT_TONE_DEVIATION, 0, MAX_PILOT_DEVIATION,
			10, DEFAULT_PILOT_DEVIATION);
	sdev->pilot_tone_freq = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_PILOT_TONE_FREQUENCY, 0, MAX_PILOT_FREQUENCY,
			1, DEFAULT_PILOT_FREQUENCY);

	sdev->tune_preemphasis = v4l2_ctrl_new_std_menu(hdl, &si4713_ctrl_ops,
			V4L2_CID_TUNE_PREEMPHASIS,
			V4L2_PREEMPHASIS_75_uS, 0, V4L2_PREEMPHASIS_50_uS);
	sdev->tune_pwr_level = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_TUNE_POWER_LEVEL, 0, SI4713_MAX_POWER,
			1, DEFAULT_POWER_LEVEL);
	sdev->tune_ant_cap = v4l2_ctrl_new_std(hdl, &si4713_ctrl_ops,
			V4L2_CID_TUNE_ANTENNA_CAPACITOR, 0, SI4713_MAX_ANTCAP,
			1, 0);

	अगर (hdl->error) अणु
		rval = hdl->error;
		जाओ मुक्त_ctrls;
	पूर्ण
	v4l2_ctrl_cluster(29, &sdev->mute);
	sdev->sd.ctrl_handler = hdl;

	अगर (client->irq) अणु
		rval = devm_request_irq(&client->dev, client->irq,
			si4713_handler, IRQF_TRIGGER_FALLING,
			client->name, sdev);
		अगर (rval < 0) अणु
			v4l2_err(&sdev->sd, "Could not request IRQ\n");
			जाओ मुक्त_ctrls;
		पूर्ण
		v4l2_dbg(1, debug, &sdev->sd, "IRQ requested.\n");
	पूर्ण अन्यथा अणु
		v4l2_warn(&sdev->sd, "IRQ not configured. Using timeouts.\n");
	पूर्ण

	rval = si4713_initialize(sdev);
	अगर (rval < 0) अणु
		v4l2_err(&sdev->sd, "Failed to probe device information.\n");
		जाओ मुक्त_ctrls;
	पूर्ण

	अगर (!np && (!pdata || !pdata->is_platक्रमm_device))
		वापस 0;

	si4713_pdev = platक्रमm_device_alloc("radio-si4713", -1);
	अगर (!si4713_pdev) अणु
		rval = -ENOMEM;
		जाओ put_मुख्य_pdev;
	पूर्ण

	si4713_pdev_pdata.subdev = client;
	rval = platक्रमm_device_add_data(si4713_pdev, &si4713_pdev_pdata,
					माप(si4713_pdev_pdata));
	अगर (rval)
		जाओ put_मुख्य_pdev;

	rval = platक्रमm_device_add(si4713_pdev);
	अगर (rval)
		जाओ put_मुख्य_pdev;

	sdev->pd = si4713_pdev;

	वापस 0;

put_मुख्य_pdev:
	platक्रमm_device_put(si4713_pdev);
	v4l2_device_unरेजिस्टर_subdev(&sdev->sd);
मुक्त_ctrls:
	v4l2_ctrl_handler_मुक्त(hdl);
निकास:
	वापस rval;
पूर्ण

/* si4713_हटाओ - हटाओ the device */
अटल पूर्णांक si4713_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा si4713_device *sdev = to_si4713_device(sd);

	platक्रमm_device_unरेजिस्टर(sdev->pd);

	अगर (sdev->घातer_state)
		si4713_set_घातer_state(sdev, POWER_DOWN);

	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);

	वापस 0;
पूर्ण

/* si4713_i2c_driver - i2c driver पूर्णांकerface */
अटल स्थिर काष्ठा i2c_device_id si4713_id[] = अणु
	अणु "si4713" , 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, si4713_id);

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id si4713_of_match[] = अणु
	अणु .compatible = "silabs,si4713" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, si4713_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver si4713_i2c_driver = अणु
	.driver		= अणु
		.name	= "si4713",
		.of_match_table = of_match_ptr(si4713_of_match),
	पूर्ण,
	.probe_new	= si4713_probe,
	.हटाओ         = si4713_हटाओ,
	.id_table       = si4713_id,
पूर्ण;

module_i2c_driver(si4713_i2c_driver);
