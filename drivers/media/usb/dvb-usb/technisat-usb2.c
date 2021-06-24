<शैली गुरु>
/*
 * Linux driver क्रम Technisat DVB-S/S2 USB 2.0 device
 *
 * Copyright (C) 2010 Patrick Boettcher,
 *                    Kernel Lअसल Inc. PO Box 745, St James, NY 11780
 *
 * Development was sponsored by Technisat Digital UK Limited, whose
 * रेजिस्टरed office is Witan Gate House 500 - 600 Witan Gate West,
 * Milton Keynes, MK9 1SH
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 *
 * THIS PROGRAM IS PROVIDED "AS IS" AND BOTH THE COPYRIGHT HOLDER AND
 * TECHNISAT DIGITAL UK LTD DISCLAIM ALL WARRANTIES WITH REGARD TO
 * THIS PROGRAM INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  NEITHER THE COPYRIGHT HOLDER
 * NOR TECHNISAT DIGITAL UK LIMITED SHALL BE LIABLE FOR ANY SPECIAL,
 * सूचीECT, INसूचीECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR
 * IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS PROGRAM. See the
 * GNU General Public License क्रम more details.
 */

#घोषणा DVB_USB_LOG_PREFIX "technisat-usb2"
#समावेश "dvb-usb.h"

#समावेश "stv6110x.h"
#समावेश "stv090x.h"

/* module parameters */
DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug,
		"set debugging level (bit-mask: 1=info,2=eeprom,4=i2c,8=rc)." \
		DVB_USB_DEBUG_STATUS);

/* disables all LED control command and
 * also करोes not start the संकेत polling thपढ़ो */
अटल पूर्णांक disable_led_control;
module_param(disable_led_control, पूर्णांक, 0444);
MODULE_PARM_DESC(disable_led_control,
		"disable LED control of the device (default: 0 - LED control is active).");

/* device निजी data */
काष्ठा technisat_usb2_state अणु
	काष्ठा dvb_usb_device *dev;
	काष्ठा delayed_work green_led_work;
	u8 घातer_state;

	u16 last_scan_code;

	u8 buf[64];
पूर्ण;

/* debug prपूर्णांक helpers */
#घोषणा deb_info(args...)    dprपूर्णांकk(debug, 0x01, args)
#घोषणा deb_eeprom(args...)  dprपूर्णांकk(debug, 0x02, args)
#घोषणा deb_i2c(args...)     dprपूर्णांकk(debug, 0x04, args)
#घोषणा deb_rc(args...)      dprपूर्णांकk(debug, 0x08, args)

/* venकरोr requests */
#घोषणा SET_IFCLK_TO_EXTERNAL_TSCLK_VENDOR_REQUEST 0xB3
#घोषणा SET_FRONT_END_RESET_VENDOR_REQUEST         0xB4
#घोषणा GET_VERSION_INFO_VENDOR_REQUEST            0xB5
#घोषणा SET_GREEN_LED_VENDOR_REQUEST               0xB6
#घोषणा SET_RED_LED_VENDOR_REQUEST                 0xB7
#घोषणा GET_IR_DATA_VENDOR_REQUEST                 0xB8
#घोषणा SET_LED_TIMER_DIVIDER_VENDOR_REQUEST       0xB9
#घोषणा SET_USB_REENUMERATION                      0xBA

/* i2c-access methods */
#घोषणा I2C_SPEED_100KHZ_BIT 0x40

#घोषणा I2C_STATUS_NAK 7
#घोषणा I2C_STATUS_OK 8

अटल पूर्णांक technisat_usb2_i2c_access(काष्ठा usb_device *udev,
		u8 device_addr, u8 *tx, u8 txlen, u8 *rx, u8 rxlen)
अणु
	u8 *b;
	पूर्णांक ret, actual_length;

	b = kदो_स्मृति(64, GFP_KERNEL);
	अगर (!b)
		वापस -ENOMEM;

	deb_i2c("i2c-access: %02x, tx: ", device_addr);
	debug_dump(tx, txlen, deb_i2c);
	deb_i2c(" ");

	अगर (txlen > 62) अणु
		err("i2c TX buffer can't exceed 62 bytes (dev 0x%02x)",
				device_addr);
		txlen = 62;
	पूर्ण
	अगर (rxlen > 62) अणु
		err("i2c RX buffer can't exceed 62 bytes (dev 0x%02x)",
				device_addr);
		rxlen = 62;
	पूर्ण

	b[0] = I2C_SPEED_100KHZ_BIT;
	b[1] = device_addr << 1;

	अगर (rx != शून्य) अणु
		b[0] |= rxlen;
		b[1] |= 1;
	पूर्ण

	स_नकल(&b[2], tx, txlen);
	ret = usb_bulk_msg(udev,
			usb_sndbulkpipe(udev, 0x01),
			b, 2 + txlen,
			शून्य, 1000);

	अगर (ret < 0) अणु
		err("i2c-error: out failed %02x = %d", device_addr, ret);
		जाओ err;
	पूर्ण

	ret = usb_bulk_msg(udev,
			usb_rcvbulkpipe(udev, 0x01),
			b, 64, &actual_length, 1000);
	अगर (ret < 0) अणु
		err("i2c-error: in failed %02x = %d", device_addr, ret);
		जाओ err;
	पूर्ण

	अगर (b[0] != I2C_STATUS_OK) अणु
		err("i2c-error: %02x = %d", device_addr, b[0]);
		/* handle tuner-i2c-nak */
		अगर (!(b[0] == I2C_STATUS_NAK &&
				device_addr == 0x60
				/* && device_is_technisat_usb2 */))
			जाओ err;
	पूर्ण

	deb_i2c("status: %d, ", b[0]);

	अगर (rx != शून्य) अणु
		स_नकल(rx, &b[2], rxlen);

		deb_i2c("rx (%d): ", rxlen);
		debug_dump(rx, rxlen, deb_i2c);
	पूर्ण

	deb_i2c("\n");

err:
	kमुक्त(b);
	वापस ret;
पूर्ण

अटल पूर्णांक technisat_usb2_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msg,
				पूर्णांक num)
अणु
	पूर्णांक ret = 0, i;
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);

	/* Ensure nobody अन्यथा hits the i2c bus जबतक we're sending our
	   sequence of messages, (such as the remote control thपढ़ो) */
	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	क्रम (i = 0; i < num; i++) अणु
		अगर (i+1 < num && msg[i+1].flags & I2C_M_RD) अणु
			ret = technisat_usb2_i2c_access(d->udev, msg[i+1].addr,
						msg[i].buf, msg[i].len,
						msg[i+1].buf, msg[i+1].len);
			अगर (ret != 0)
				अवरोध;
			i++;
		पूर्ण अन्यथा अणु
			ret = technisat_usb2_i2c_access(d->udev, msg[i].addr,
						msg[i].buf, msg[i].len,
						शून्य, 0);
			अगर (ret != 0)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret == 0)
		ret = i;

	mutex_unlock(&d->i2c_mutex);

	वापस ret;
पूर्ण

अटल u32 technisat_usb2_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल काष्ठा i2c_algorithm technisat_usb2_i2c_algo = अणु
	.master_xfer   = technisat_usb2_i2c_xfer,
	.functionality = technisat_usb2_i2c_func,
पूर्ण;

#अगर 0
अटल व्योम technisat_usb2_frontend_reset(काष्ठा usb_device *udev)
अणु
	usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			SET_FRONT_END_RESET_VENDOR_REQUEST,
			USB_TYPE_VENDOR | USB_सूची_OUT,
			10, 0,
			शून्य, 0, 500);
पूर्ण
#पूर्ण_अगर

/* LED control */
क्रमागत technisat_usb2_led_state अणु
	TECH_LED_OFF,
	TECH_LED_BLINK,
	TECH_LED_ON,
	TECH_LED_UNDEFINED
पूर्ण;

अटल पूर्णांक technisat_usb2_set_led(काष्ठा dvb_usb_device *d, पूर्णांक red,
				  क्रमागत technisat_usb2_led_state st)
अणु
	काष्ठा technisat_usb2_state *state = d->priv;
	u8 *led = state->buf;
	पूर्णांक ret;

	led[0] = red ? SET_RED_LED_VENDOR_REQUEST : SET_GREEN_LED_VENDOR_REQUEST;

	अगर (disable_led_control && st != TECH_LED_OFF)
		वापस 0;

	चयन (st) अणु
	हाल TECH_LED_ON:
		led[1] = 0x82;
		अवरोध;
	हाल TECH_LED_BLINK:
		led[1] = 0x82;
		अगर (red) अणु
			led[2] = 0x02;
			led[3] = 10;
			led[4] = 10;
		पूर्ण अन्यथा अणु
			led[2] = 0xff;
			led[3] = 50;
			led[4] = 50;
		पूर्ण
		led[5] = 1;
		अवरोध;

	शेष:
	हाल TECH_LED_OFF:
		led[1] = 0x80;
		अवरोध;
	पूर्ण

	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	ret = usb_control_msg(d->udev, usb_sndctrlpipe(d->udev, 0),
		red ? SET_RED_LED_VENDOR_REQUEST : SET_GREEN_LED_VENDOR_REQUEST,
		USB_TYPE_VENDOR | USB_सूची_OUT,
		0, 0,
		led, 8, 500);

	mutex_unlock(&d->i2c_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक technisat_usb2_set_led_समयr(काष्ठा dvb_usb_device *d, u8 red, u8 green)
अणु
	काष्ठा technisat_usb2_state *state = d->priv;
	u8 *b = state->buf;
	पूर्णांक ret;

	b[0] = 0;

	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	ret = usb_control_msg(d->udev, usb_sndctrlpipe(d->udev, 0),
		SET_LED_TIMER_DIVIDER_VENDOR_REQUEST,
		USB_TYPE_VENDOR | USB_सूची_OUT,
		(red << 8) | green, 0,
		b, 1, 500);

	mutex_unlock(&d->i2c_mutex);

	वापस ret;
पूर्ण

अटल व्योम technisat_usb2_green_led_control(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा technisat_usb2_state *state =
		container_of(work, काष्ठा technisat_usb2_state, green_led_work.work);
	काष्ठा dvb_frontend *fe = state->dev->adapter[0].fe_adap[0].fe;

	अगर (state->घातer_state == 0)
		जाओ schedule;

	अगर (fe != शून्य) अणु
		क्रमागत fe_status status;

		अगर (fe->ops.पढ़ो_status(fe, &status) != 0)
			जाओ schedule;

		अगर (status & FE_HAS_LOCK) अणु
			u32 ber;

			अगर (fe->ops.पढ़ो_ber(fe, &ber) != 0)
				जाओ schedule;

			अगर (ber > 1000)
				technisat_usb2_set_led(state->dev, 0, TECH_LED_BLINK);
			अन्यथा
				technisat_usb2_set_led(state->dev, 0, TECH_LED_ON);
		पूर्ण अन्यथा
			technisat_usb2_set_led(state->dev, 0, TECH_LED_OFF);
	पूर्ण

schedule:
	schedule_delayed_work(&state->green_led_work,
			msecs_to_jअगरfies(500));
पूर्ण

/* method to find out whether the firmware has to be करोwnloaded or not */
अटल पूर्णांक technisat_usb2_identअगरy_state(काष्ठा usb_device *udev,
		स्थिर काष्ठा dvb_usb_device_properties *props,
		स्थिर काष्ठा dvb_usb_device_description **desc, पूर्णांक *cold)
अणु
	पूर्णांक ret;
	u8 *version;

	version = kदो_स्मृति(3, GFP_KERNEL);
	अगर (!version)
		वापस -ENOMEM;

	/* first select the पूर्णांकerface */
	अगर (usb_set_पूर्णांकerface(udev, 0, 1) != 0)
		err("could not set alternate setting to 0");
	अन्यथा
		info("set alternate setting");

	*cold = 0; /* by शेष करो not करोwnload a firmware - just in हाल something is wrong */

	ret = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
		GET_VERSION_INFO_VENDOR_REQUEST,
		USB_TYPE_VENDOR | USB_सूची_IN,
		0, 0,
		version, 3, 500);

	अगर (ret < 0)
		*cold = 1;
	अन्यथा अणु
		info("firmware version: %d.%d", version[1], version[2]);
		*cold = 0;
	पूर्ण

	kमुक्त(version);

	वापस 0;
पूर्ण

/* घातer control */
अटल पूर्णांक technisat_usb2_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक level)
अणु
	काष्ठा technisat_usb2_state *state = d->priv;

	state->घातer_state = level;

	अगर (disable_led_control)
		वापस 0;

	/* green led is turned off in any हाल - will be turned on when tuning */
	technisat_usb2_set_led(d, 0, TECH_LED_OFF);
	/* red led is turned on all the समय */
	technisat_usb2_set_led(d, 1, TECH_LED_ON);
	वापस 0;
पूर्ण

/* mac address पढ़ोing - from the eeprom */
#अगर 0
अटल व्योम technisat_usb2_eeprom_dump(काष्ठा dvb_usb_device *d)
अणु
	u8 reg;
	u8 b[16];
	पूर्णांक i, j;

	/* full EEPROM dump */
	क्रम (j = 0; j < 256 * 4; j += 16) अणु
		reg = j;
		अगर (technisat_usb2_i2c_access(d->udev, 0x50 + j / 256, &reg, 1, b, 16) != 0)
			अवरोध;

		deb_eeprom("EEPROM: %01x%02x: ", j / 256, reg);
		क्रम (i = 0; i < 16; i++)
			deb_eeprom("%02x ", b[i]);
		deb_eeprom("\n");
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल u8 technisat_usb2_calc_lrc(स्थिर u8 *b, u16 length)
अणु
	u8 lrc = 0;
	जबतक (--length)
		lrc ^= *b++;
	वापस lrc;
पूर्ण

अटल पूर्णांक technisat_usb2_eeprom_lrc_पढ़ो(काष्ठा dvb_usb_device *d,
	u16 offset, u8 *b, u16 length, u8 tries)
अणु
	u8 bo = offset & 0xff;
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = 0x50 | ((offset >> 8) & 0x3),
			.buf = &bo,
			.len = 1
		पूर्ण, अणु
			.addr = 0x50 | ((offset >> 8) & 0x3),
			.flags	= I2C_M_RD,
			.buf = b,
			.len = length
		पूर्ण
	पूर्ण;

	जबतक (tries--) अणु
		पूर्णांक status;

		अगर (i2c_transfer(&d->i2c_adap, msg, 2) != 2)
			अवरोध;

		status =
			technisat_usb2_calc_lrc(b, length - 1) == b[length - 1];

		अगर (status)
			वापस 0;
	पूर्ण

	वापस -EREMOTEIO;
पूर्ण

#घोषणा EEPROM_MAC_START 0x3f8
#घोषणा EEPROM_MAC_TOTAL 8
अटल पूर्णांक technisat_usb2_पढ़ो_mac_address(काष्ठा dvb_usb_device *d,
		u8 mac[])
अणु
	u8 buf[EEPROM_MAC_TOTAL];

	अगर (technisat_usb2_eeprom_lrc_पढ़ो(d, EEPROM_MAC_START,
				buf, EEPROM_MAC_TOTAL, 4) != 0)
		वापस -ENODEV;

	स_नकल(mac, buf, 6);
	वापस 0;
पूर्ण

अटल काष्ठा stv090x_config technisat_usb2_stv090x_config;

/* frontend attach */
अटल पूर्णांक technisat_usb2_set_voltage(काष्ठा dvb_frontend *fe,
				      क्रमागत fe_sec_voltage voltage)
अणु
	पूर्णांक i;
	u8 gpio[3] = अणु 0 पूर्ण; /* 0 = 2, 1 = 3, 2 = 4 */

	gpio[2] = 1; /* high - voltage ? */

	चयन (voltage) अणु
	हाल SEC_VOLTAGE_13:
		gpio[0] = 1;
		अवरोध;
	हाल SEC_VOLTAGE_18:
		gpio[0] = 1;
		gpio[1] = 1;
		अवरोध;
	शेष:
	हाल SEC_VOLTAGE_OFF:
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < 3; i++)
		अगर (technisat_usb2_stv090x_config.set_gpio(fe, i+2, 0,
							   gpio[i], 0) != 0)
			वापस -EREMOTEIO;
	वापस 0;
पूर्ण

अटल काष्ठा stv090x_config technisat_usb2_stv090x_config = अणु
	.device         = STV0903,
	.demod_mode     = STV090x_SINGLE,
	.clk_mode       = STV090x_CLK_EXT,

	.xtal           = 8000000,
	.address        = 0x68,

	.ts1_mode       = STV090x_TSMODE_DVBCI,
	.ts1_clk        = 13400000,
	.ts1_tei        = 1,

	.repeater_level = STV090x_RPTLEVEL_64,

	.tuner_bbgain   = 6,
पूर्ण;

अटल काष्ठा stv6110x_config technisat_usb2_stv6110x_config = अणु
	.addr           = 0x60,
	.refclk         = 16000000,
	.clk_भाग        = 2,
पूर्ण;

अटल पूर्णांक technisat_usb2_frontend_attach(काष्ठा dvb_usb_adapter *a)
अणु
	काष्ठा usb_device *udev = a->dev->udev;
	पूर्णांक ret;

	a->fe_adap[0].fe = dvb_attach(stv090x_attach, &technisat_usb2_stv090x_config,
			&a->dev->i2c_adap, STV090x_DEMODULATOR_0);

	अगर (a->fe_adap[0].fe) अणु
		स्थिर काष्ठा stv6110x_devctl *ctl;

		ctl = dvb_attach(stv6110x_attach,
				a->fe_adap[0].fe,
				&technisat_usb2_stv6110x_config,
				&a->dev->i2c_adap);

		अगर (ctl) अणु
			technisat_usb2_stv090x_config.tuner_init          = ctl->tuner_init;
			technisat_usb2_stv090x_config.tuner_sleep         = ctl->tuner_sleep;
			technisat_usb2_stv090x_config.tuner_set_mode      = ctl->tuner_set_mode;
			technisat_usb2_stv090x_config.tuner_set_frequency = ctl->tuner_set_frequency;
			technisat_usb2_stv090x_config.tuner_get_frequency = ctl->tuner_get_frequency;
			technisat_usb2_stv090x_config.tuner_set_bandwidth = ctl->tuner_set_bandwidth;
			technisat_usb2_stv090x_config.tuner_get_bandwidth = ctl->tuner_get_bandwidth;
			technisat_usb2_stv090x_config.tuner_set_bbgain    = ctl->tuner_set_bbgain;
			technisat_usb2_stv090x_config.tuner_get_bbgain    = ctl->tuner_get_bbgain;
			technisat_usb2_stv090x_config.tuner_set_refclk    = ctl->tuner_set_refclk;
			technisat_usb2_stv090x_config.tuner_get_status    = ctl->tuner_get_status;

			/* call the init function once to initialize
			   tuner's clock output divider and demod's
			   master घड़ी */
			अगर (a->fe_adap[0].fe->ops.init)
				a->fe_adap[0].fe->ops.init(a->fe_adap[0].fe);

			अगर (mutex_lock_पूर्णांकerruptible(&a->dev->i2c_mutex) < 0)
				वापस -EAGAIN;

			ret = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
					SET_IFCLK_TO_EXTERNAL_TSCLK_VENDOR_REQUEST,
					USB_TYPE_VENDOR | USB_सूची_OUT,
					0, 0,
					शून्य, 0, 500);
			mutex_unlock(&a->dev->i2c_mutex);

			अगर (ret != 0)
				err("could not set IF_CLK to external");

			a->fe_adap[0].fe->ops.set_voltage = technisat_usb2_set_voltage;

			/* अगर everything was successful assign a nice name to the frontend */
			strscpy(a->fe_adap[0].fe->ops.info.name,
				a->dev->desc->name,
				माप(a->fe_adap[0].fe->ops.info.name));
		पूर्ण अन्यथा अणु
			dvb_frontend_detach(a->fe_adap[0].fe);
			a->fe_adap[0].fe = शून्य;
		पूर्ण
	पूर्ण

	technisat_usb2_set_led_समयr(a->dev, 1, 1);

	वापस a->fe_adap[0].fe == शून्य ? -ENODEV : 0;
पूर्ण

/* Remote control */

/* the device is giving providing raw IR-संकेतs to the host mapping
 * it only to one remote control is just the शेष implementation
 */
#घोषणा NOMINAL_IR_BIT_TRANSITION_TIME_US 889
#घोषणा NOMINAL_IR_BIT_TIME_US (2 * NOMINAL_IR_BIT_TRANSITION_TIME_US)

#घोषणा FIRMWARE_CLOCK_TICK 83333
#घोषणा FIRMWARE_CLOCK_DIVISOR 256

#घोषणा IR_PERCENT_TOLERANCE 15

#घोषणा NOMINAL_IR_BIT_TRANSITION_TICKS ((NOMINAL_IR_BIT_TRANSITION_TIME_US * 1000 * 1000) / FIRMWARE_CLOCK_TICK)
#घोषणा NOMINAL_IR_BIT_TRANSITION_TICK_COUNT (NOMINAL_IR_BIT_TRANSITION_TICKS / FIRMWARE_CLOCK_DIVISOR)

#घोषणा NOMINAL_IR_BIT_TIME_TICKS ((NOMINAL_IR_BIT_TIME_US * 1000 * 1000) / FIRMWARE_CLOCK_TICK)
#घोषणा NOMINAL_IR_BIT_TIME_TICK_COUNT (NOMINAL_IR_BIT_TIME_TICKS / FIRMWARE_CLOCK_DIVISOR)

#घोषणा MINIMUM_IR_BIT_TRANSITION_TICK_COUNT (NOMINAL_IR_BIT_TRANSITION_TICK_COUNT - ((NOMINAL_IR_BIT_TRANSITION_TICK_COUNT * IR_PERCENT_TOLERANCE) / 100))
#घोषणा MAXIMUM_IR_BIT_TRANSITION_TICK_COUNT (NOMINAL_IR_BIT_TRANSITION_TICK_COUNT + ((NOMINAL_IR_BIT_TRANSITION_TICK_COUNT * IR_PERCENT_TOLERANCE) / 100))

#घोषणा MINIMUM_IR_BIT_TIME_TICK_COUNT (NOMINAL_IR_BIT_TIME_TICK_COUNT - ((NOMINAL_IR_BIT_TIME_TICK_COUNT * IR_PERCENT_TOLERANCE) / 100))
#घोषणा MAXIMUM_IR_BIT_TIME_TICK_COUNT (NOMINAL_IR_BIT_TIME_TICK_COUNT + ((NOMINAL_IR_BIT_TIME_TICK_COUNT * IR_PERCENT_TOLERANCE) / 100))

अटल पूर्णांक technisat_usb2_get_ir(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा technisat_usb2_state *state = d->priv;
	काष्ठा ir_raw_event ev;
	u8 *buf = state->buf;
	पूर्णांक i, ret;

	buf[0] = GET_IR_DATA_VENDOR_REQUEST;
	buf[1] = 0x08;
	buf[2] = 0x8f;
	buf[3] = MINIMUM_IR_BIT_TRANSITION_TICK_COUNT;
	buf[4] = MAXIMUM_IR_BIT_TIME_TICK_COUNT;

	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;
	ret = usb_control_msg(d->udev, usb_sndctrlpipe(d->udev, 0),
			GET_IR_DATA_VENDOR_REQUEST,
			USB_TYPE_VENDOR | USB_सूची_OUT,
			0, 0,
			buf, 5, 500);
	अगर (ret < 0)
		जाओ unlock;

	buf[1] = 0;
	buf[2] = 0;
	ret = usb_control_msg(d->udev, usb_rcvctrlpipe(d->udev, 0),
			GET_IR_DATA_VENDOR_REQUEST,
			USB_TYPE_VENDOR | USB_सूची_IN,
			0x8080, 0,
			buf, 62, 500);

unlock:
	mutex_unlock(&d->i2c_mutex);

	अगर (ret < 0)
		वापस ret;

	अगर (ret == 1)
		वापस 0; /* no key pressed */

	/* decoding */

#अगर 0
	deb_rc("RC: %d ", ret);
	debug_dump(buf + 1, ret, deb_rc);
#पूर्ण_अगर

	ev.pulse = 0;
	क्रम (i = 1; i < ARRAY_SIZE(state->buf); i++) अणु
		अगर (buf[i] == 0xff) अणु
			ev.pulse = 0;
			ev.duration = 889 * 2;
			ir_raw_event_store(d->rc_dev, &ev);
			अवरोध;
		पूर्ण

		ev.pulse = !ev.pulse;
		ev.duration = (buf[i] * FIRMWARE_CLOCK_DIVISOR *
			       FIRMWARE_CLOCK_TICK) / (1000 * 1000);
		ir_raw_event_store(d->rc_dev, &ev);
	पूर्ण

	ir_raw_event_handle(d->rc_dev);

	वापस 1;
पूर्ण

अटल पूर्णांक technisat_usb2_rc_query(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक ret = technisat_usb2_get_ir(d);

	अगर (ret < 0)
		वापस ret;

	अगर (ret == 0)
		वापस 0;

	अगर (!disable_led_control)
		technisat_usb2_set_led(d, 1, TECH_LED_BLINK);

	वापस 0;
पूर्ण

/* DVB-USB and USB stuff follows */
अटल काष्ठा usb_device_id technisat_usb2_id_table[] = अणु
	अणु USB_DEVICE(USB_VID_TECHNISAT, USB_PID_TECHNISAT_USB2_DVB_S2) पूर्ण,
	अणु 0 पूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, technisat_usb2_id_table);

/* device description */
अटल काष्ठा dvb_usb_device_properties technisat_usb2_devices = अणु
	.caps              = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl          = CYPRESS_FX2,

	.identअगरy_state    = technisat_usb2_identअगरy_state,
	.firmware          = "dvb-usb-SkyStar_USB_HD_FW_v17_63.HEX.fw",

	.size_of_priv      = माप(काष्ठा technisat_usb2_state),

	.i2c_algo          = &technisat_usb2_i2c_algo,

	.घातer_ctrl        = technisat_usb2_घातer_ctrl,
	.पढ़ो_mac_address  = technisat_usb2_पढ़ो_mac_address,

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.frontend_attach  = technisat_usb2_frontend_attach,

			.stream = अणु
				.type = USB_ISOC,
				.count = 4,
				.endpoपूर्णांक = 0x2,
				.u = अणु
					.isoc = अणु
						.framesperurb = 32,
						.framesize = 2048,
						.पूर्णांकerval = 1,
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्णपूर्ण,
			.size_of_priv = 0,
		पूर्ण,
	पूर्ण,

	.num_device_descs = 1,
	.devices = अणु
		अणु   "Technisat SkyStar USB HD (DVB-S/S2)",
			अणु &technisat_usb2_id_table[0], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण,
	पूर्ण,

	.rc.core = अणु
		.rc_पूर्णांकerval = 100,
		.rc_codes    = RC_MAP_TECHNISAT_USB2,
		.module_name = "technisat-usb2",
		.rc_query    = technisat_usb2_rc_query,
		.allowed_protos = RC_PROTO_BIT_ALL_IR_DECODER,
		.driver_type    = RC_DRIVER_IR_RAW,
	पूर्ण
पूर्ण;

अटल पूर्णांक technisat_usb2_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा dvb_usb_device *dev;

	अगर (dvb_usb_device_init(पूर्णांकf, &technisat_usb2_devices, THIS_MODULE,
				&dev, adapter_nr) != 0)
		वापस -ENODEV;

	अगर (dev) अणु
		काष्ठा technisat_usb2_state *state = dev->priv;
		state->dev = dev;

		अगर (!disable_led_control) अणु
			INIT_DELAYED_WORK(&state->green_led_work,
					technisat_usb2_green_led_control);
			schedule_delayed_work(&state->green_led_work,
					msecs_to_jअगरfies(500));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम technisat_usb2_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा dvb_usb_device *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	/* work and stuff was only created when the device is is hot-state */
	अगर (dev != शून्य) अणु
		काष्ठा technisat_usb2_state *state = dev->priv;
		अगर (state != शून्य)
			cancel_delayed_work_sync(&state->green_led_work);
	पूर्ण

	dvb_usb_device_निकास(पूर्णांकf);
पूर्ण

अटल काष्ठा usb_driver technisat_usb2_driver = अणु
	.name       = "dvb_usb_technisat_usb2",
	.probe      = technisat_usb2_probe,
	.disconnect = technisat_usb2_disconnect,
	.id_table   = technisat_usb2_id_table,
पूर्ण;

module_usb_driver(technisat_usb2_driver);

MODULE_AUTHOR("Patrick Boettcher <pboettcher@kernellabs.com>");
MODULE_DESCRIPTION("Driver for Technisat DVB-S/S2 USB 2.0 device");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
