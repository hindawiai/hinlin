<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Intel CE6230 DVB USB driver
 *
 * Copyright (C) 2009 Antti Palosaari <crope@iki.fi>
 */

#समावेश "ce6230.h"

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

अटल पूर्णांक ce6230_ctrl_msg(काष्ठा dvb_usb_device *d, काष्ठा usb_req *req)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक pipe;
	u8 request;
	u8 requesttype;
	u16 value;
	u16 index;
	u8 *buf;

	request = req->cmd;
	value = req->value;
	index = req->index;

	चयन (req->cmd) अणु
	हाल I2C_READ:
	हाल DEMOD_READ:
	हाल REG_READ:
		requesttype = (USB_TYPE_VENDOR | USB_सूची_IN);
		अवरोध;
	हाल I2C_WRITE:
	हाल DEMOD_WRITE:
	हाल REG_WRITE:
		requesttype = (USB_TYPE_VENDOR | USB_सूची_OUT);
		अवरोध;
	शेष:
		dev_err(&d->udev->dev, "%s: unknown command=%02x\n",
				KBUILD_MODNAME, req->cmd);
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	buf = kदो_स्मृति(req->data_len, GFP_KERNEL);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	अगर (requesttype == (USB_TYPE_VENDOR | USB_सूची_OUT)) अणु
		/* ग_लिखो */
		स_नकल(buf, req->data, req->data_len);
		pipe = usb_sndctrlpipe(d->udev, 0);
	पूर्ण अन्यथा अणु
		/* पढ़ो */
		pipe = usb_rcvctrlpipe(d->udev, 0);
	पूर्ण

	msleep(1); /* aव्योम I2C errors */

	ret = usb_control_msg(d->udev, pipe, request, requesttype, value, index,
			buf, req->data_len, CE6230_USB_TIMEOUT);

	dvb_usb_dbg_usb_control_msg(d->udev, request, requesttype, value, index,
			buf, req->data_len);

	अगर (ret < 0)
		dev_err(&d->udev->dev, "%s: usb_control_msg() failed=%d\n",
				KBUILD_MODNAME, ret);
	अन्यथा
		ret = 0;

	/* पढ़ो request, copy वापसed data to वापस buf */
	अगर (!ret && requesttype == (USB_TYPE_VENDOR | USB_सूची_IN))
		स_नकल(req->data, buf, req->data_len);

	kमुक्त(buf);
error:
	वापस ret;
पूर्ण

/* I2C */
अटल काष्ठा zl10353_config ce6230_zl10353_config;

अटल पूर्णांक ce6230_i2c_master_xfer(काष्ठा i2c_adapter *adap,
		काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	पूर्णांक ret = 0, i = 0;
	काष्ठा usb_req req;

	अगर (num > 2)
		वापस -EOPNOTSUPP;

	स_रखो(&req, 0, माप(req));

	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	जबतक (i < num) अणु
		अगर (num > i + 1 && (msg[i+1].flags & I2C_M_RD)) अणु
			अगर (msg[i].addr ==
				ce6230_zl10353_config.demod_address) अणु
				req.cmd = DEMOD_READ;
				req.value = msg[i].addr >> 1;
				req.index = msg[i].buf[0];
				req.data_len = msg[i+1].len;
				req.data = &msg[i+1].buf[0];
				ret = ce6230_ctrl_msg(d, &req);
			पूर्ण अन्यथा अणु
				dev_err(&d->udev->dev, "%s: I2C read not " \
						"implemented\n",
						KBUILD_MODNAME);
				ret = -EOPNOTSUPP;
			पूर्ण
			i += 2;
		पूर्ण अन्यथा अणु
			अगर (msg[i].addr ==
				ce6230_zl10353_config.demod_address) अणु
				req.cmd = DEMOD_WRITE;
				req.value = msg[i].addr >> 1;
				req.index = msg[i].buf[0];
				req.data_len = msg[i].len-1;
				req.data = &msg[i].buf[1];
				ret = ce6230_ctrl_msg(d, &req);
			पूर्ण अन्यथा अणु
				req.cmd = I2C_WRITE;
				req.value = 0x2000 + (msg[i].addr >> 1);
				req.index = 0x0000;
				req.data_len = msg[i].len;
				req.data = &msg[i].buf[0];
				ret = ce6230_ctrl_msg(d, &req);
			पूर्ण
			i += 1;
		पूर्ण
		अगर (ret)
			अवरोध;
	पूर्ण

	mutex_unlock(&d->i2c_mutex);
	वापस ret ? ret : i;
पूर्ण

अटल u32 ce6230_i2c_functionality(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल काष्ठा i2c_algorithm ce6230_i2c_algorithm = अणु
	.master_xfer   = ce6230_i2c_master_xfer,
	.functionality = ce6230_i2c_functionality,
पूर्ण;

/* Callbacks क्रम DVB USB */
अटल काष्ठा zl10353_config ce6230_zl10353_config = अणु
	.demod_address = 0x1e,
	.adc_घड़ी = 450000,
	.अगर2 = 45700,
	.no_tuner = 1,
	.parallel_ts = 1,
	.घड़ी_ctl_1 = 0x34,
	.pll_0 = 0x0e,
पूर्ण;

अटल पूर्णांक ce6230_zl10353_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);

	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	adap->fe[0] = dvb_attach(zl10353_attach, &ce6230_zl10353_config,
			&d->i2c_adap);
	अगर (adap->fe[0] == शून्य)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल काष्ठा mxl5005s_config ce6230_mxl5003s_config = अणु
	.i2c_address     = 0xc6,
	.अगर_freq         = IF_FREQ_4570000HZ,
	.xtal_freq       = CRYSTAL_FREQ_16000000HZ,
	.agc_mode        = MXL_SINGLE_AGC,
	.tracking_filter = MXL_TF_DEFAULT,
	.rssi_enable     = MXL_RSSI_ENABLE,
	.cap_select      = MXL_CAP_SEL_ENABLE,
	.भाग_out         = MXL_DIV_OUT_4,
	.घड़ी_out       = MXL_CLOCK_OUT_DISABLE,
	.output_load     = MXL5005S_IF_OUTPUT_LOAD_200_OHM,
	.top		 = MXL5005S_TOP_25P2,
	.mod_mode        = MXL_DIGITAL_MODE,
	.अगर_mode         = MXL_ZERO_IF,
	.AgcMasterByte   = 0x00,
पूर्ण;

अटल पूर्णांक ce6230_mxl5003s_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	पूर्णांक ret;

	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	ret = dvb_attach(mxl5005s_attach, adap->fe[0], &d->i2c_adap,
			&ce6230_mxl5003s_config) == शून्य ? -ENODEV : 0;
	वापस ret;
पूर्ण

अटल पूर्णांक ce6230_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	पूर्णांक ret;

	dev_dbg(&d->udev->dev, "%s: onoff=%d\n", __func__, onoff);

	/* InterfaceNumber 1 / AlternateSetting 0     idle
	   InterfaceNumber 1 / AlternateSetting 1     streaming */
	ret = usb_set_पूर्णांकerface(d->udev, 1, onoff);
	अगर (ret)
		dev_err(&d->udev->dev, "%s: usb_set_interface() failed=%d\n",
				KBUILD_MODNAME, ret);

	वापस ret;
पूर्ण

/* DVB USB Driver stuff */
अटल काष्ठा dvb_usb_device_properties ce6230_props = अणु
	.driver_name = KBUILD_MODNAME,
	.owner = THIS_MODULE,
	.adapter_nr = adapter_nr,
	.bInterfaceNumber = 1,

	.i2c_algo = &ce6230_i2c_algorithm,
	.घातer_ctrl = ce6230_घातer_ctrl,
	.frontend_attach = ce6230_zl10353_frontend_attach,
	.tuner_attach = ce6230_mxl5003s_tuner_attach,

	.num_adapters = 1,
	.adapter = अणु
		अणु
			.stream = अणु
				.type = USB_BULK,
				.count = 6,
				.endpoपूर्णांक = 0x82,
				.u = अणु
					.bulk = अणु
						.buffersize = (16 * 512),
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id ce6230_id_table[] = अणु
	अणु DVB_USB_DEVICE(USB_VID_INTEL, USB_PID_INTEL_CE9500,
		&ce6230_props, "Intel CE9500 reference design", शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_A310,
		&ce6230_props, "AVerMedia A310 USB 2.0 DVB-T tuner", शून्य) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, ce6230_id_table);

अटल काष्ठा usb_driver ce6230_usb_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = ce6230_id_table,
	.probe = dvb_usbv2_probe,
	.disconnect = dvb_usbv2_disconnect,
	.suspend = dvb_usbv2_suspend,
	.resume = dvb_usbv2_resume,
	.reset_resume = dvb_usbv2_reset_resume,
	.no_dynamic_id = 1,
	.soft_unbind = 1,
पूर्ण;

module_usb_driver(ce6230_usb_driver);

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("Intel CE6230 driver");
MODULE_LICENSE("GPL");
