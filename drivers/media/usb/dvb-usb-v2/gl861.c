<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* DVB USB compliant linux driver क्रम GL861 USB2.0 devices.
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#समावेश <linux/माला.स>

#समावेश "dvb_usb.h"

#समावेश "zl10353.h"
#समावेश "qt1010.h"
#समावेश "tc90522.h"
#समावेश "dvb-pll.h"

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

काष्ठा gl861 अणु
	/* USB control message buffer */
	u8 buf[16];

	काष्ठा i2c_adapter *demod_sub_i2c;
	काष्ठा i2c_client  *i2c_client_demod;
	काष्ठा i2c_client  *i2c_client_tuner;
पूर्ण;

#घोषणा CMD_WRITE_SHORT     0x01
#घोषणा CMD_READ            0x02
#घोषणा CMD_WRITE           0x03

अटल पूर्णांक gl861_ctrl_msg(काष्ठा dvb_usb_device *d, u8 request, u16 value,
			  u16 index, व्योम *data, u16 size)
अणु
	काष्ठा gl861 *ctx = d_to_priv(d);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret;
	अचिन्हित पूर्णांक pipe;
	u8 requesttype;

	mutex_lock(&d->usb_mutex);

	चयन (request) अणु
	हाल CMD_WRITE:
		स_नकल(ctx->buf, data, size);
		fallthrough;
	हाल CMD_WRITE_SHORT:
		pipe = usb_sndctrlpipe(d->udev, 0);
		requesttype = USB_TYPE_VENDOR | USB_सूची_OUT;
		अवरोध;
	हाल CMD_READ:
		pipe = usb_rcvctrlpipe(d->udev, 0);
		requesttype = USB_TYPE_VENDOR | USB_सूची_IN;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err_mutex_unlock;
	पूर्ण

	ret = usb_control_msg(d->udev, pipe, request, requesttype, value,
			      index, ctx->buf, size, 200);
	dev_dbg(&पूर्णांकf->dev, "%d | %02x %02x %*ph %*ph %*ph %s %*ph\n",
		ret, requesttype, request, 2, &value, 2, &index, 2, &size,
		(requesttype & USB_सूची_IN) ? "<<<" : ">>>", size, ctx->buf);
	अगर (ret < 0)
		जाओ err_mutex_unlock;

	अगर (request == CMD_READ)
		स_नकल(data, ctx->buf, size);

	usleep_range(1000, 2000); /* Aव्योम I2C errors */

	mutex_unlock(&d->usb_mutex);

	वापस 0;

err_mutex_unlock:
	mutex_unlock(&d->usb_mutex);
	dev_dbg(&पूर्णांकf->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक gl861_लघु_ग_लिखो(काष्ठा dvb_usb_device *d, u8 addr, u8 reg, u8 val)
अणु
	वापस gl861_ctrl_msg(d, CMD_WRITE_SHORT,
			      (addr << 9) | val, reg, शून्य, 0);
पूर्ण

अटल पूर्णांक gl861_i2c_master_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msg[],
				 पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	काष्ठा gl861 *ctx = d_to_priv(d);
	पूर्णांक ret;
	u8 request, *data;
	u16 value, index, size;

	/* XXX: I2C adapter maximum data lengths are not tested */
	अगर (num == 1 && !(msg[0].flags & I2C_M_RD)) अणु
		/* I2C ग_लिखो */
		अगर (msg[0].len < 2 || msg[0].len > माप(ctx->buf)) अणु
			ret = -EOPNOTSUPP;
			जाओ err;
		पूर्ण

		value = (msg[0].addr << 1) << 8;
		index = msg[0].buf[0];

		अगर (msg[0].len == 2) अणु
			request = CMD_WRITE_SHORT;
			value |= msg[0].buf[1];
			size = 0;
			data = शून्य;
		पूर्ण अन्यथा अणु
			request = CMD_WRITE;
			size = msg[0].len - 1;
			data = &msg[0].buf[1];
		पूर्ण

		ret = gl861_ctrl_msg(d, request, value, index, data, size);
	पूर्ण अन्यथा अगर (num == 2 && !(msg[0].flags & I2C_M_RD) &&
		   (msg[1].flags & I2C_M_RD)) अणु
		/* I2C ग_लिखो + पढ़ो */
		अगर (msg[0].len > 1 || msg[1].len > माप(ctx->buf)) अणु
			ret = -EOPNOTSUPP;
			जाओ err;
		पूर्ण

		value = (msg[0].addr << 1) << 8;
		index = msg[0].buf[0];
		request = CMD_READ;

		ret = gl861_ctrl_msg(d, request, value, index,
				     msg[1].buf, msg[1].len);
	पूर्ण अन्यथा अगर (num == 1 && (msg[0].flags & I2C_M_RD)) अणु
		/* I2C पढ़ो */
		अगर (msg[0].len > माप(ctx->buf)) अणु
			ret = -EOPNOTSUPP;
			जाओ err;
		पूर्ण
		value = (msg[0].addr << 1) << 8;
		index = 0x0100;
		request = CMD_READ;

		ret = gl861_ctrl_msg(d, request, value, index,
				     msg[0].buf, msg[0].len);
	पूर्ण अन्यथा अणु
		/* Unsupported I2C message */
		dev_dbg(&पूर्णांकf->dev, "unknown i2c msg, num %u\n", num);
		ret = -EOPNOTSUPP;
	पूर्ण
	अगर (ret)
		जाओ err;

	वापस num;
err:
	dev_dbg(&पूर्णांकf->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल u32 gl861_i2c_functionality(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल काष्ठा i2c_algorithm gl861_i2c_algo = अणु
	.master_xfer   = gl861_i2c_master_xfer,
	.functionality = gl861_i2c_functionality,
पूर्ण;

/* Callbacks क्रम DVB USB */
अटल काष्ठा zl10353_config gl861_zl10353_config = अणु
	.demod_address = 0x0f,
	.no_tuner = 1,
	.parallel_ts = 1,
पूर्ण;

अटल पूर्णांक gl861_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु

	adap->fe[0] = dvb_attach(zl10353_attach, &gl861_zl10353_config,
		&adap_to_d(adap)->i2c_adap);
	अगर (adap->fe[0] == शून्य)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल काष्ठा qt1010_config gl861_qt1010_config = अणु
	.i2c_address = 0x62
पूर्ण;

अटल पूर्णांक gl861_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	वापस dvb_attach(qt1010_attach,
			  adap->fe[0], &adap_to_d(adap)->i2c_adap,
			  &gl861_qt1010_config) == शून्य ? -ENODEV : 0;
पूर्ण

अटल पूर्णांक gl861_init(काष्ठा dvb_usb_device *d)
अणु
	/*
	 * There is 2 पूर्णांकerfaces. Interface 0 is क्रम TV and पूर्णांकerface 1 is
	 * क्रम HID remote controller. Interface 0 has 2 alternate settings.
	 * For some reason we need to set पूर्णांकerface explicitly, शेषed
	 * as alternate setting 1?
	 */
	वापस usb_set_पूर्णांकerface(d->udev, 0, 0);
पूर्ण

/* DVB USB Driver stuff */
अटल काष्ठा dvb_usb_device_properties gl861_props = अणु
	.driver_name = KBUILD_MODNAME,
	.owner = THIS_MODULE,
	.adapter_nr = adapter_nr,

	.size_of_priv = माप(काष्ठा gl861),

	.i2c_algo = &gl861_i2c_algo,
	.frontend_attach = gl861_frontend_attach,
	.tuner_attach = gl861_tuner_attach,
	.init = gl861_init,

	.num_adapters = 1,
	.adapter = अणु
		अणु
			.stream = DVB_USB_STREAM_BULK(0x81, 7, 512),
		पूर्ण
	पूर्ण
पूर्ण;


/*
 * For Friio
 */
काष्ठा friio_config अणु
	काष्ठा i2c_board_info demod_info;
	काष्ठा tc90522_config demod_cfg;

	काष्ठा i2c_board_info tuner_info;
	काष्ठा dvb_pll_config tuner_cfg;
पूर्ण;

अटल स्थिर काष्ठा friio_config friio_config = अणु
	.demod_info = अणु I2C_BOARD_INFO(TC90522_I2C_DEV_TER, 0x18), पूर्ण,
	.demod_cfg = अणु .split_tuner_पढ़ो_i2c = true, पूर्ण,
	.tuner_info = अणु I2C_BOARD_INFO("tua6034_friio", 0x60), पूर्ण,
पूर्ण;


/* GPIO control in Friio */

#घोषणा FRIIO_CTL_LNB (1 << 0)
#घोषणा FRIIO_CTL_STROBE (1 << 1)
#घोषणा FRIIO_CTL_CLK (1 << 2)
#घोषणा FRIIO_CTL_LED (1 << 3)

#घोषणा FRIIO_LED_RUNNING 0x6400ff64
#घोषणा FRIIO_LED_STOPPED 0x96ff00ff

/* control PIC16F676 attached to Friio */
अटल पूर्णांक friio_ext_ctl(काष्ठा dvb_usb_device *d,
			    u32 sat_color, पूर्णांक घातer_on)
अणु
	पूर्णांक i, ret;
	काष्ठा i2c_msg msg;
	u8 *buf;
	u32 mask;
	u8 घातer = (घातer_on) ? FRIIO_CTL_LNB : 0;

	buf = kदो_स्मृति(2, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	msg.addr = 0x00;
	msg.flags = 0;
	msg.len = 2;
	msg.buf = buf;
	buf[0] = 0x00;

	/* send 2bit header (&B10) */
	buf[1] = घातer | FRIIO_CTL_LED | FRIIO_CTL_STROBE;
	ret = i2c_transfer(&d->i2c_adap, &msg, 1);
	buf[1] |= FRIIO_CTL_CLK;
	ret += i2c_transfer(&d->i2c_adap, &msg, 1);

	buf[1] = घातer | FRIIO_CTL_STROBE;
	ret += i2c_transfer(&d->i2c_adap, &msg, 1);
	buf[1] |= FRIIO_CTL_CLK;
	ret += i2c_transfer(&d->i2c_adap, &msg, 1);

	/* send 32bit(satur, R, G, B) data in serial */
	mask = 1UL << 31;
	क्रम (i = 0; i < 32; i++) अणु
		buf[1] = घातer | FRIIO_CTL_STROBE;
		अगर (sat_color & mask)
			buf[1] |= FRIIO_CTL_LED;
		ret += i2c_transfer(&d->i2c_adap, &msg, 1);
		buf[1] |= FRIIO_CTL_CLK;
		ret += i2c_transfer(&d->i2c_adap, &msg, 1);
		mask >>= 1;
	पूर्ण

	/* set the strobe off */
	buf[1] = घातer;
	ret += i2c_transfer(&d->i2c_adap, &msg, 1);
	buf[1] |= FRIIO_CTL_CLK;
	ret += i2c_transfer(&d->i2c_adap, &msg, 1);

	kमुक्त(buf);
	वापस (ret == 70) ? 0 : -EREMOTEIO;
पूर्ण

/* init/config of gl861 क्रम Friio */
/* NOTE:
 * This function cannot be moved to friio_init()/dvb_usbv2_init(),
 * because the init defined here includes a whole device reset,
 * it must be run early beक्रमe any activities like I2C,
 * but friio_init() is called by dvb-usbv2 after अणु_frontend, _tunerपूर्ण_attach(),
 * where I2C communication is used.
 * In addition, this reset is required in reset_resume() as well.
 * Thus this function is set to be called from _घातer_ctl().
 *
 * Since it will be called on the early init stage
 * where the i2c adapter is not initialized yet,
 * we cannot use i2c_transfer() here.
 */
अटल पूर्णांक friio_reset(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक i, ret;
	u8 wbuf[1], rbuf[2];

	अटल स्थिर u8 friio_init_cmds[][2] = अणु
		अणु0x33, 0x08पूर्ण, अणु0x37, 0x40पूर्ण, अणु0x3a, 0x1fपूर्ण, अणु0x3b, 0xffपूर्ण,
		अणु0x3c, 0x1fपूर्ण, अणु0x3d, 0xffपूर्ण, अणु0x38, 0x00पूर्ण, अणु0x35, 0x00पूर्ण,
		अणु0x39, 0x00पूर्ण, अणु0x36, 0x00पूर्ण,
	पूर्ण;

	ret = usb_set_पूर्णांकerface(d->udev, 0, 0);
	अगर (ret < 0)
		वापस ret;

	ret = gl861_लघु_ग_लिखो(d, 0x00, 0x11, 0x02);
	अगर (ret < 0)
		वापस ret;
	usleep_range(2000, 3000);

	ret = gl861_लघु_ग_लिखो(d, 0x00, 0x11, 0x00);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Check अगर the dev is really a Friio White, since it might be
	 * another device, Friio Black, with the same VID/PID.
	 */

	usleep_range(1000, 2000);
	wbuf[0] = 0x80;
	ret = gl861_ctrl_msg(d, CMD_WRITE, 0x09 << 9, 0x03, wbuf, 1);
	अगर (ret < 0)
		वापस ret;

	usleep_range(2000, 3000);
	ret = gl861_ctrl_msg(d, CMD_READ, 0x09 << 9, 0x0100, rbuf, 2);
	अगर (ret < 0)
		वापस ret;
	अगर (rbuf[0] != 0xff || rbuf[1] != 0xff)
		वापस -ENODEV;


	usleep_range(1000, 2000);
	wbuf[0] = 0x80;
	ret = gl861_ctrl_msg(d, CMD_WRITE, 0x48 << 9, 0x03, wbuf, 1);
	अगर (ret < 0)
		वापस ret;

	usleep_range(2000, 3000);
	ret = gl861_ctrl_msg(d, CMD_READ, 0x48 << 9, 0x0100, rbuf, 2);
	अगर (ret < 0)
		वापस ret;
	अगर (rbuf[0] != 0xff || rbuf[1] != 0xff)
		वापस -ENODEV;

	ret = gl861_लघु_ग_लिखो(d, 0x00, 0x30, 0x04);
	अगर (ret < 0)
		वापस ret;

	ret = gl861_लघु_ग_लिखो(d, 0x00, 0x00, 0x01);
	अगर (ret < 0)
		वापस ret;

	ret = gl861_लघु_ग_लिखो(d, 0x00, 0x06, 0x0f);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(friio_init_cmds); i++) अणु
		ret = gl861_लघु_ग_लिखो(d, 0x00, friio_init_cmds[i][0],
					friio_init_cmds[i][1]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * DVB callbacks क्रम Friio
 */

अटल पूर्णांक friio_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	वापस onoff ? friio_reset(d) : 0;
पूर्ण

अटल पूर्णांक friio_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	स्थिर काष्ठा i2c_board_info *info;
	काष्ठा dvb_usb_device *d;
	काष्ठा tc90522_config cfg;
	काष्ठा i2c_client *cl;
	काष्ठा gl861 *priv;

	info = &friio_config.demod_info;
	cfg = friio_config.demod_cfg;
	d = adap_to_d(adap);
	cl = dvb_module_probe("tc90522", info->type,
			      &d->i2c_adap, info->addr, &cfg);
	अगर (!cl)
		वापस -ENODEV;
	adap->fe[0] = cfg.fe;

	priv = adap_to_priv(adap);
	priv->i2c_client_demod = cl;
	priv->demod_sub_i2c = cfg.tuner_i2c;
	वापस 0;
पूर्ण

अटल पूर्णांक friio_frontend_detach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा gl861 *priv;

	priv = adap_to_priv(adap);
	dvb_module_release(priv->i2c_client_demod);
	वापस 0;
पूर्ण

अटल पूर्णांक friio_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	स्थिर काष्ठा i2c_board_info *info;
	काष्ठा dvb_pll_config cfg;
	काष्ठा i2c_client *cl;
	काष्ठा gl861 *priv;

	priv = adap_to_priv(adap);
	info = &friio_config.tuner_info;
	cfg = friio_config.tuner_cfg;
	cfg.fe = adap->fe[0];

	cl = dvb_module_probe("dvb_pll", info->type,
			      priv->demod_sub_i2c, info->addr, &cfg);
	अगर (!cl)
		वापस -ENODEV;
	priv->i2c_client_tuner = cl;
	वापस 0;
पूर्ण

अटल पूर्णांक friio_tuner_detach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा gl861 *priv;

	priv = adap_to_priv(adap);
	dvb_module_release(priv->i2c_client_tuner);
	वापस 0;
पूर्ण

अटल पूर्णांक friio_init(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	काष्ठा gl861 *priv;

	अटल स्थिर u8 demod_init[][2] = अणु
		अणु0x01, 0x40पूर्ण, अणु0x04, 0x38पूर्ण, अणु0x05, 0x40पूर्ण, अणु0x07, 0x40पूर्ण,
		अणु0x0f, 0x4fपूर्ण, अणु0x11, 0x21पूर्ण, अणु0x12, 0x0bपूर्ण, अणु0x13, 0x2fपूर्ण,
		अणु0x14, 0x31पूर्ण, अणु0x16, 0x02पूर्ण, अणु0x21, 0xc4पूर्ण, अणु0x22, 0x20पूर्ण,
		अणु0x2c, 0x79पूर्ण, अणु0x2d, 0x34पूर्ण, अणु0x2f, 0x00पूर्ण, अणु0x30, 0x28पूर्ण,
		अणु0x31, 0x31पूर्ण, अणु0x32, 0xdfपूर्ण, अणु0x38, 0x01पूर्ण, अणु0x39, 0x78पूर्ण,
		अणु0x3b, 0x33पूर्ण, अणु0x3c, 0x33पूर्ण, अणु0x48, 0x90पूर्ण, अणु0x51, 0x68पूर्ण,
		अणु0x5e, 0x38पूर्ण, अणु0x71, 0x00पूर्ण, अणु0x72, 0x08पूर्ण, अणु0x77, 0x00पूर्ण,
		अणु0xc0, 0x21पूर्ण, अणु0xc1, 0x10पूर्ण, अणु0xe4, 0x1aपूर्ण, अणु0xea, 0x1fपूर्ण,
		अणु0x77, 0x00पूर्ण, अणु0x71, 0x00पूर्ण, अणु0x71, 0x00पूर्ण, अणु0x76, 0x0cपूर्ण,
	पूर्ण;

	/* घातer on LNA? */
	ret = friio_ext_ctl(d, FRIIO_LED_STOPPED, true);
	अगर (ret < 0)
		वापस ret;
	msleep(20);

	/* init/config demod */
	priv = d_to_priv(d);
	क्रम (i = 0; i < ARRAY_SIZE(demod_init); i++) अणु
		पूर्णांक ret;

		ret = i2c_master_send(priv->i2c_client_demod, demod_init[i], 2);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	msleep(100);
	वापस 0;
पूर्ण

अटल व्योम friio_निकास(काष्ठा dvb_usb_device *d)
अणु
	friio_ext_ctl(d, FRIIO_LED_STOPPED, false);
पूर्ण

अटल पूर्णांक friio_streaming_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	u32 led_color;

	led_color = onoff ? FRIIO_LED_RUNNING : FRIIO_LED_STOPPED;
	वापस friio_ext_ctl(fe_to_d(fe), led_color, true);
पूर्ण


अटल काष्ठा dvb_usb_device_properties friio_props = अणु
	.driver_name = KBUILD_MODNAME,
	.owner = THIS_MODULE,
	.adapter_nr = adapter_nr,

	.size_of_priv = माप(काष्ठा gl861),

	.i2c_algo = &gl861_i2c_algo,
	.घातer_ctrl = friio_घातer_ctrl,
	.frontend_attach = friio_frontend_attach,
	.frontend_detach = friio_frontend_detach,
	.tuner_attach = friio_tuner_attach,
	.tuner_detach = friio_tuner_detach,
	.init = friio_init,
	.निकास = friio_निकास,
	.streaming_ctrl = friio_streaming_ctrl,

	.num_adapters = 1,
	.adapter = अणु
		अणु
			.stream = DVB_USB_STREAM_BULK(0x01, 8, 16384),
		पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_device_id gl861_id_table[] = अणु
	अणु DVB_USB_DEVICE(USB_VID_MSI, USB_PID_MSI_MEGASKY580_55801,
		&gl861_props, "MSI Mega Sky 55801 DVB-T USB2.0", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_ALINK, USB_PID_ALINK_DTU,
		&gl861_props, "A-LINK DTU DVB-T USB2.0", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_774, USB_PID_FRIIO_WHITE,
		&friio_props, "774 Friio White ISDB-T USB2.0", शून्य) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, gl861_id_table);

अटल काष्ठा usb_driver gl861_usb_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = gl861_id_table,
	.probe = dvb_usbv2_probe,
	.disconnect = dvb_usbv2_disconnect,
	.suspend = dvb_usbv2_suspend,
	.resume = dvb_usbv2_resume,
	.reset_resume = dvb_usbv2_reset_resume,
	.no_dynamic_id = 1,
	.soft_unbind = 1,
पूर्ण;

module_usb_driver(gl861_usb_driver);

MODULE_AUTHOR("Carl Lundqvist <comabug@gmail.com>");
MODULE_DESCRIPTION("Driver MSI Mega Sky 580 DVB-T USB2.0 / GL861");
MODULE_VERSION("0.1");
MODULE_LICENSE("GPL");
