<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* DVB USB framework compliant Linux driver क्रम the Opera1 DVB-S Card
*
* Copyright (C) 2006 Mario Hlawitschka (dh1pa@amsat.org)
* Copyright (C) 2006 Marco Gittler (g.marco@मुक्तnet.de)
*
* see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
*/

#घोषणा DVB_USB_LOG_PREFIX "opera"

#समावेश "dvb-usb.h"
#समावेश "stv0299.h"

#घोषणा OPERA_READ_MSG 0
#घोषणा OPERA_WRITE_MSG 1
#घोषणा OPERA_I2C_TUNER 0xd1

#घोषणा READ_FX2_REG_REQ  0xba
#घोषणा READ_MAC_ADDR 0x08
#घोषणा OPERA_WRITE_FX2 0xbb
#घोषणा OPERA_TUNER_REQ 0xb1
#घोषणा REG_1F_SYMBOLRATE_BYTE0 0x1f
#घोषणा REG_20_SYMBOLRATE_BYTE1 0x20
#घोषणा REG_21_SYMBOLRATE_BYTE2 0x21

#घोषणा ADDR_B600_VOLTAGE_13V (0x02)
#घोषणा ADDR_B601_VOLTAGE_18V (0x03)
#घोषणा ADDR_B1A6_STREAM_CTRL (0x04)
#घोषणा ADDR_B880_READ_REMOTE (0x05)

काष्ठा opera1_state अणु
	u32 last_key_pressed;
पूर्ण;
काष्ठा rc_map_opera_table अणु
	u32 keycode;
	u32 event;
पूर्ण;

अटल पूर्णांक dvb_usb_opera1_debug;
module_param_named(debug, dvb_usb_opera1_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug,
		 "set debugging level (1=info,xfer=2,pll=4,ts=8,err=16,rc=32,fw=64 (or-able))."
		 DVB_USB_DEBUG_STATUS);

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);


अटल पूर्णांक opera1_xilinx_rw(काष्ठा usb_device *dev, u8 request, u16 value,
			    u8 * data, u16 len, पूर्णांक flags)
अणु
	पूर्णांक ret;
	u8 पंचांगp;
	u8 *buf;
	अचिन्हित पूर्णांक pipe = (flags == OPERA_READ_MSG) ?
		usb_rcvctrlpipe(dev,0) : usb_sndctrlpipe(dev, 0);
	u8 request_type = (flags == OPERA_READ_MSG) ? USB_सूची_IN : USB_सूची_OUT;

	buf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	अगर (flags == OPERA_WRITE_MSG)
		स_नकल(buf, data, len);
	ret = usb_control_msg(dev, pipe, request,
			request_type | USB_TYPE_VENDOR, value, 0x0,
			buf, len, 2000);

	अगर (request == OPERA_TUNER_REQ) अणु
		पंचांगp = buf[0];
		अगर (usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			    OPERA_TUNER_REQ, USB_सूची_IN | USB_TYPE_VENDOR,
			    0x01, 0x0, buf, 1, 2000) < 1 || buf[0] != 0x08) अणु
			ret = 0;
			जाओ out;
		पूर्ण
		buf[0] = पंचांगp;
	पूर्ण
	अगर (flags == OPERA_READ_MSG)
		स_नकल(data, buf, len);
out:
	kमुक्त(buf);
	वापस ret;
पूर्ण

/* I2C */

अटल पूर्णांक opera1_usb_i2c_msgxfer(काष्ठा dvb_usb_device *dev, u16 addr,
				  u8 * buf, u16 len)
अणु
	पूर्णांक ret = 0;
	u8 request;
	u16 value;

	अगर (!dev) अणु
		info("no usb_device");
		वापस -EINVAL;
	पूर्ण
	अगर (mutex_lock_पूर्णांकerruptible(&dev->usb_mutex) < 0)
		वापस -EAGAIN;

	चयन (addr>>1)अणु
		हाल ADDR_B600_VOLTAGE_13V:
			request=0xb6;
			value=0x00;
			अवरोध;
		हाल ADDR_B601_VOLTAGE_18V:
			request=0xb6;
			value=0x01;
			अवरोध;
		हाल ADDR_B1A6_STREAM_CTRL:
			request=0xb1;
			value=0xa6;
			अवरोध;
		हाल ADDR_B880_READ_REMOTE:
			request=0xb8;
			value=0x80;
			अवरोध;
		शेष:
			request=0xb1;
			value=addr;
	पूर्ण
	ret = opera1_xilinx_rw(dev->udev, request,
		value, buf, len,
		addr&0x01?OPERA_READ_MSG:OPERA_WRITE_MSG);

	mutex_unlock(&dev->usb_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक opera1_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msg[],
			   पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	पूर्णांक i = 0, पंचांगp = 0;

	अगर (!d)
		वापस -ENODEV;
	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	क्रम (i = 0; i < num; i++) अणु
		अगर ((पंचांगp = opera1_usb_i2c_msgxfer(d,
					(msg[i].addr<<1)|(msg[i].flags&I2C_M_RD?0x01:0),
					msg[i].buf,
					msg[i].len
					)) != msg[i].len) अणु
			अवरोध;
		पूर्ण
		अगर (dvb_usb_opera1_debug & 0x10)
			info("sending i2c message %d %d", पंचांगp, msg[i].len);
	पूर्ण
	mutex_unlock(&d->i2c_mutex);
	वापस num;
पूर्ण

अटल u32 opera1_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल काष्ठा i2c_algorithm opera1_i2c_algo = अणु
	.master_xfer = opera1_i2c_xfer,
	.functionality = opera1_i2c_func,
पूर्ण;

अटल पूर्णांक opera1_set_voltage(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_sec_voltage voltage)
अणु
	अटल u8 command_13v[1]=अणु0x00पूर्ण;
	अटल u8 command_18v[1]=अणु0x01पूर्ण;
	काष्ठा i2c_msg msg[] = अणु
		अणु.addr = ADDR_B600_VOLTAGE_13V,.flags = 0,.buf = command_13v,.len = 1पूर्ण,
	पूर्ण;
	काष्ठा dvb_usb_adapter *udev_adap =
	    (काष्ठा dvb_usb_adapter *)(fe->dvb->priv);
	अगर (voltage == SEC_VOLTAGE_18) अणु
		msg[0].addr = ADDR_B601_VOLTAGE_18V;
		msg[0].buf = command_18v;
	पूर्ण
	i2c_transfer(&udev_adap->dev->i2c_adap, msg, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक opera1_stv0299_set_symbol_rate(काष्ठा dvb_frontend *fe, u32 srate,
					  u32 ratio)
अणु
	stv0299_ग_लिखोreg(fe, 0x13, 0x98);
	stv0299_ग_लिखोreg(fe, 0x14, 0x95);
	stv0299_ग_लिखोreg(fe, REG_1F_SYMBOLRATE_BYTE0, (ratio >> 16) & 0xff);
	stv0299_ग_लिखोreg(fe, REG_20_SYMBOLRATE_BYTE1, (ratio >> 8) & 0xff);
	stv0299_ग_लिखोreg(fe, REG_21_SYMBOLRATE_BYTE2, (ratio) & 0xf0);
	वापस 0;

पूर्ण
अटल u8 opera1_inittab[] = अणु
	0x00, 0xa1,
	0x01, 0x15,
	0x02, 0x30,
	0x03, 0x00,
	0x04, 0x7d,
	0x05, 0x05,
	0x06, 0x02,
	0x07, 0x00,
	0x0b, 0x00,
	0x0c, 0x01,
	0x0d, 0x81,
	0x0e, 0x44,
	0x0f, 0x19,
	0x10, 0x3f,
	0x11, 0x84,
	0x12, 0xda,
	0x13, 0x98,
	0x14, 0x95,
	0x15, 0xc9,
	0x16, 0xeb,
	0x17, 0x00,
	0x18, 0x19,
	0x19, 0x8b,
	0x1a, 0x00,
	0x1b, 0x82,
	0x1c, 0x7f,
	0x1d, 0x00,
	0x1e, 0x00,
	REG_1F_SYMBOLRATE_BYTE0, 0x06,
	REG_20_SYMBOLRATE_BYTE1, 0x50,
	REG_21_SYMBOLRATE_BYTE2, 0x10,
	0x22, 0x00,
	0x23, 0x00,
	0x24, 0x37,
	0x25, 0xbc,
	0x26, 0x00,
	0x27, 0x00,
	0x28, 0x00,
	0x29, 0x1e,
	0x2a, 0x14,
	0x2b, 0x1f,
	0x2c, 0x09,
	0x2d, 0x0a,
	0x2e, 0x00,
	0x2f, 0x00,
	0x30, 0x00,
	0x31, 0x1f,
	0x32, 0x19,
	0x33, 0xfc,
	0x34, 0x13,
	0xff, 0xff,
पूर्ण;

अटल काष्ठा stv0299_config opera1_stv0299_config = अणु
	.demod_address = 0xd0>>1,
	.min_delay_ms = 100,
	.mclk = 88000000UL,
	.invert = 1,
	.skip_reinit = 0,
	.lock_output = STV0299_LOCKOUTPUT_0,
	.volt13_op0_op1 = STV0299_VOLT13_OP0,
	.inittab = opera1_inittab,
	.set_symbol_rate = opera1_stv0299_set_symbol_rate,
पूर्ण;

अटल पूर्णांक opera1_frontend_attach(काष्ठा dvb_usb_adapter *d)
अणु
	d->fe_adap[0].fe = dvb_attach(stv0299_attach, &opera1_stv0299_config,
				      &d->dev->i2c_adap);
	अगर ((d->fe_adap[0].fe) != शून्य) अणु
		d->fe_adap[0].fe->ops.set_voltage = opera1_set_voltage;
		वापस 0;
	पूर्ण
	info("not attached stv0299");
	वापस -EIO;
पूर्ण

अटल पूर्णांक opera1_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	dvb_attach(
		dvb_pll_attach, adap->fe_adap[0].fe, 0xc0>>1,
		&adap->dev->i2c_adap, DVB_PLL_OPERA1
	);
	वापस 0;
पूर्ण

अटल पूर्णांक opera1_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	u8 val = onoff ? 0x01 : 0x00;

	अगर (dvb_usb_opera1_debug)
		info("power %s", onoff ? "on" : "off");
	वापस opera1_xilinx_rw(d->udev, 0xb7, val,
				&val, 1, OPERA_WRITE_MSG);
पूर्ण

अटल पूर्णांक opera1_streaming_ctrl(काष्ठा dvb_usb_adapter *adap, पूर्णांक onoff)
अणु
	अटल u8 buf_start[2] = अणु 0xff, 0x03 पूर्ण;
	अटल u8 buf_stop[2] = अणु 0xff, 0x00 पूर्ण;
	काष्ठा i2c_msg start_tuner[] = अणु
		अणु.addr = ADDR_B1A6_STREAM_CTRL,.buf = onoff ? buf_start : buf_stop,.len = 2पूर्ण,
	पूर्ण;
	अगर (dvb_usb_opera1_debug)
		info("streaming %s", onoff ? "on" : "off");
	i2c_transfer(&adap->dev->i2c_adap, start_tuner, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक opera1_pid_filter(काष्ठा dvb_usb_adapter *adap, पूर्णांक index, u16 pid,
			     पूर्णांक onoff)
अणु
	u8 b_pid[3];
	काष्ठा i2c_msg msg[] = अणु
		अणु.addr = ADDR_B1A6_STREAM_CTRL,.buf = b_pid,.len = 3पूर्ण,
	पूर्ण;
	अगर (dvb_usb_opera1_debug)
		info("pidfilter index: %d pid: %d %s", index, pid,
			onoff ? "on" : "off");
	b_pid[0] = (2 * index) + 4;
	b_pid[1] = onoff ? (pid & 0xff) : (0x00);
	b_pid[2] = onoff ? ((pid >> 8) & 0xff) : (0x00);
	i2c_transfer(&adap->dev->i2c_adap, msg, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक opera1_pid_filter_control(काष्ठा dvb_usb_adapter *adap, पूर्णांक onoff)
अणु
	पूर्णांक u = 0x04;
	u8 b_pid[3];
	काष्ठा i2c_msg msg[] = अणु
		अणु.addr = ADDR_B1A6_STREAM_CTRL,.buf = b_pid,.len = 3पूर्ण,
	पूर्ण;
	अगर (dvb_usb_opera1_debug)
		info("%s hw-pidfilter", onoff ? "enable" : "disable");
	क्रम (; u < 0x7e; u += 2) अणु
		b_pid[0] = u;
		b_pid[1] = 0;
		b_pid[2] = 0x80;
		i2c_transfer(&adap->dev->i2c_adap, msg, 1);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा rc_map_table rc_map_opera1_table[] = अणु
	अणु0x5fa0, KEY_1पूर्ण,
	अणु0x51af, KEY_2पूर्ण,
	अणु0x5da2, KEY_3पूर्ण,
	अणु0x41be, KEY_4पूर्ण,
	अणु0x0bf5, KEY_5पूर्ण,
	अणु0x43bd, KEY_6पूर्ण,
	अणु0x47b8, KEY_7पूर्ण,
	अणु0x49b6, KEY_8पूर्ण,
	अणु0x05fa, KEY_9पूर्ण,
	अणु0x45ba, KEY_0पूर्ण,
	अणु0x09f6, KEY_CHANNELUPपूर्ण,	/*chanup */
	अणु0x1be5, KEY_CHANNELDOWNपूर्ण,	/*chanकरोwn */
	अणु0x5da3, KEY_VOLUMEDOWNपूर्ण,	/*volकरोwn */
	अणु0x5fa1, KEY_VOLUMEUPपूर्ण,		/*volup */
	अणु0x07f8, KEY_SPACEपूर्ण,		/*tab */
	अणु0x1fe1, KEY_OKपूर्ण,		/*play ok */
	अणु0x1be4, KEY_ZOOMपूर्ण,		/*zoom */
	अणु0x59a6, KEY_MUTEपूर्ण,		/*mute */
	अणु0x5ba5, KEY_RADIOपूर्ण,		/*tv/f */
	अणु0x19e7, KEY_RECORDपूर्ण,		/*rec */
	अणु0x01fe, KEY_STOPपूर्ण,		/*Stop */
	अणु0x03fd, KEY_PAUSEपूर्ण,		/*छोड़ो */
	अणु0x03fc, KEY_SCREENपूर्ण,		/*<- -> */
	अणु0x07f9, KEY_CAMERAपूर्ण,		/*capture */
	अणु0x47b9, KEY_ESCपूर्ण,		/*निकास */
	अणु0x43bc, KEY_POWER2पूर्ण,		/*घातer */
पूर्ण;

अटल पूर्णांक opera1_rc_query(काष्ठा dvb_usb_device *dev, u32 * event, पूर्णांक *state)
अणु
	काष्ठा opera1_state *opst = dev->priv;
	u8 rcbuffer[32];
	स्थिर u16 starपंचांगarker1 = 0x10ed;
	स्थिर u16 starपंचांगarker2 = 0x11ec;
	काष्ठा i2c_msg पढ़ो_remote[] = अणु
		अणु.addr = ADDR_B880_READ_REMOTE,.buf = rcbuffer,.flags = I2C_M_RD,.len = 32पूर्ण,
	पूर्ण;
	पूर्णांक i = 0;
	u32 send_key = 0;

	अगर (i2c_transfer(&dev->i2c_adap, पढ़ो_remote, 1) == 1) अणु
		क्रम (i = 0; i < 32; i++) अणु
			अगर (rcbuffer[i])
				send_key |= 1;
			अगर (i < 31)
				send_key = send_key << 1;
		पूर्ण
		अगर (send_key & 0x8000)
			send_key = (send_key << 1) | (send_key >> 15 & 0x01);

		अगर (send_key == 0xffff && opst->last_key_pressed != 0) अणु
			*state = REMOTE_KEY_REPEAT;
			*event = opst->last_key_pressed;
			वापस 0;
		पूर्ण
		क्रम (; send_key != 0;) अणु
			अगर (send_key >> 16 == starपंचांगarker2) अणु
				अवरोध;
			पूर्ण अन्यथा अगर (send_key >> 16 == starपंचांगarker1) अणु
				send_key =
					(send_key & 0xfffeffff) | (starपंचांगarker1 << 16);
				अवरोध;
			पूर्ण अन्यथा
				send_key >>= 1;
		पूर्ण

		अगर (send_key == 0)
			वापस 0;

		send_key = (send_key & 0xffff) | 0x0100;

		क्रम (i = 0; i < ARRAY_SIZE(rc_map_opera1_table); i++) अणु
			अगर (rc5_scan(&rc_map_opera1_table[i]) == (send_key & 0xffff)) अणु
				*state = REMOTE_KEY_PRESSED;
				*event = rc_map_opera1_table[i].keycode;
				opst->last_key_pressed =
					rc_map_opera1_table[i].keycode;
				अवरोध;
			पूर्ण
			opst->last_key_pressed = 0;
		पूर्ण
	पूर्ण अन्यथा
		*state = REMOTE_NO_KEY_PRESSED;
	वापस 0;
पूर्ण

अटल काष्ठा usb_device_id opera1_table[] = अणु
	अणुUSB_DEVICE(USB_VID_CYPRESS, USB_PID_OPERA1_COLD)पूर्ण,
	अणुUSB_DEVICE(USB_VID_OPERA1, USB_PID_OPERA1_WARM)पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, opera1_table);

अटल पूर्णांक opera1_पढ़ो_mac_address(काष्ठा dvb_usb_device *d, u8 mac[6])
अणु
	u8 command[] = अणु READ_MAC_ADDR पूर्ण;
	opera1_xilinx_rw(d->udev, 0xb1, 0xa0, command, 1, OPERA_WRITE_MSG);
	opera1_xilinx_rw(d->udev, 0xb1, 0xa1, mac, 6, OPERA_READ_MSG);
	वापस 0;
पूर्ण
अटल पूर्णांक opera1_xilinx_load_firmware(काष्ठा usb_device *dev,
				       स्थिर अक्षर *filename)
अणु
	स्थिर काष्ठा firmware *fw = शून्य;
	u8 *b, *p;
	पूर्णांक ret = 0, i,fpgasize=40;
	u8 testval;
	info("start downloading fpga firmware %s",filename);

	अगर ((ret = request_firmware(&fw, filename, &dev->dev)) != 0) अणु
		err("did not find the firmware file '%s'. You can use <kernel_dir>/scripts/get_dvb_firmware to get the firmware",
			filename);
		वापस ret;
	पूर्ण अन्यथा अणु
		p = kदो_स्मृति(fw->size, GFP_KERNEL);
		opera1_xilinx_rw(dev, 0xbc, 0x00, &testval, 1, OPERA_READ_MSG);
		अगर (p != शून्य && testval != 0x67) अणु

			u8 reset = 0, fpga_command = 0;
			स_नकल(p, fw->data, fw->size);
			/* clear fpga ? */
			opera1_xilinx_rw(dev, 0xbc, 0xaa, &fpga_command, 1,
					 OPERA_WRITE_MSG);
			क्रम (i = 0; i < fw->size;) अणु
				अगर ( (fw->size - i) <fpgasize)अणु
				    fpgasize=fw->size-i;
				पूर्ण
				b = (u8 *) p + i;
				अगर (opera1_xilinx_rw
					(dev, OPERA_WRITE_FX2, 0x0, b , fpgasize,
						OPERA_WRITE_MSG) != fpgasize
					) अणु
					err("error while transferring firmware");
					ret = -EINVAL;
					अवरोध;
				पूर्ण
				i = i + fpgasize;
			पूर्ण
			/* restart the CPU */
			अगर (ret || opera1_xilinx_rw
					(dev, 0xa0, 0xe600, &reset, 1,
					OPERA_WRITE_MSG) != 1) अणु
				err("could not restart the USB controller CPU.");
				ret = -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण
	kमुक्त(p);
	release_firmware(fw);
	वापस ret;
पूर्ण

अटल काष्ठा dvb_usb_device_properties opera1_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,
	.usb_ctrl = CYPRESS_FX2,
	.firmware = "dvb-usb-opera-01.fw",
	.size_of_priv = माप(काष्ठा opera1_state),

	.घातer_ctrl = opera1_घातer_ctrl,
	.i2c_algo = &opera1_i2c_algo,

	.rc.legacy = अणु
		.rc_map_table = rc_map_opera1_table,
		.rc_map_size = ARRAY_SIZE(rc_map_opera1_table),
		.rc_पूर्णांकerval = 200,
		.rc_query = opera1_rc_query,
	पूर्ण,
	.पढ़ो_mac_address = opera1_पढ़ो_mac_address,
	.generic_bulk_ctrl_endpoपूर्णांक = 0x00,
	/* parameter क्रम the MPEG2-data transfer */
	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.frontend_attach = opera1_frontend_attach,
			.streaming_ctrl = opera1_streaming_ctrl,
			.tuner_attach = opera1_tuner_attach,
			.caps =
				DVB_USB_ADAP_HAS_PID_FILTER |
				DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
			.pid_filter = opera1_pid_filter,
			.pid_filter_ctrl = opera1_pid_filter_control,
			.pid_filter_count = 252,
			.stream = अणु
				.type = USB_BULK,
				.count = 10,
				.endpoपूर्णांक = 0x82,
				.u = अणु
					.bulk = अणु
						.buffersize = 4096,
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्णपूर्ण,
		पूर्ण
	पूर्ण,
	.num_device_descs = 1,
	.devices = अणु
		अणु"Opera1 DVB-S USB2.0",
			अणु&opera1_table[0], शून्यपूर्ण,
			अणु&opera1_table[1], शून्यपूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल पूर्णांक opera1_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	अगर (le16_to_cpu(udev->descriptor.idProduct) == USB_PID_OPERA1_WARM &&
	    le16_to_cpu(udev->descriptor.idVenकरोr) == USB_VID_OPERA1 &&
		opera1_xilinx_load_firmware(udev, "dvb-usb-opera1-fpga-01.fw") != 0
	    ) अणु
		वापस -EINVAL;
	पूर्ण

	अगर (0 != dvb_usb_device_init(पूर्णांकf, &opera1_properties,
				     THIS_MODULE, शून्य, adapter_nr))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल काष्ठा usb_driver opera1_driver = अणु
	.name = "opera1",
	.probe = opera1_probe,
	.disconnect = dvb_usb_device_निकास,
	.id_table = opera1_table,
पूर्ण;

module_usb_driver(opera1_driver);

MODULE_AUTHOR("Mario Hlawitschka (c) dh1pa@amsat.org");
MODULE_AUTHOR("Marco Gittler (c) g.marco@freenet.de");
MODULE_DESCRIPTION("Driver for Opera1 DVB-S device");
MODULE_VERSION("0.1");
MODULE_LICENSE("GPL");
