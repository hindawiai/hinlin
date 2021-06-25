<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * E3C EC168 DVB USB driver
 *
 * Copyright (C) 2009 Antti Palosaari <crope@iki.fi>
 */

#समावेश "ec168.h"
#समावेश "ec100.h"
#समावेश "mxl5005s.h"

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

अटल पूर्णांक ec168_ctrl_msg(काष्ठा dvb_usb_device *d, काष्ठा ec168_req *req)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक pipe;
	u8 request, requesttype;
	u8 *buf;

	चयन (req->cmd) अणु
	हाल DOWNLOAD_FIRMWARE:
	हाल GPIO:
	हाल WRITE_I2C:
	हाल STREAMING_CTRL:
		requesttype = (USB_TYPE_VENDOR | USB_सूची_OUT);
		request = req->cmd;
		अवरोध;
	हाल READ_I2C:
		requesttype = (USB_TYPE_VENDOR | USB_सूची_IN);
		request = req->cmd;
		अवरोध;
	हाल GET_CONFIG:
		requesttype = (USB_TYPE_VENDOR | USB_सूची_IN);
		request = CONFIG;
		अवरोध;
	हाल SET_CONFIG:
		requesttype = (USB_TYPE_VENDOR | USB_सूची_OUT);
		request = CONFIG;
		अवरोध;
	हाल WRITE_DEMOD:
		requesttype = (USB_TYPE_VENDOR | USB_सूची_OUT);
		request = DEMOD_RW;
		अवरोध;
	हाल READ_DEMOD:
		requesttype = (USB_TYPE_VENDOR | USB_सूची_IN);
		request = DEMOD_RW;
		अवरोध;
	शेष:
		dev_err(&d->udev->dev, "%s: unknown command=%02x\n",
				KBUILD_MODNAME, req->cmd);
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	buf = kदो_स्मृति(req->size, GFP_KERNEL);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	अगर (requesttype == (USB_TYPE_VENDOR | USB_सूची_OUT)) अणु
		/* ग_लिखो */
		स_नकल(buf, req->data, req->size);
		pipe = usb_sndctrlpipe(d->udev, 0);
	पूर्ण अन्यथा अणु
		/* पढ़ो */
		pipe = usb_rcvctrlpipe(d->udev, 0);
	पूर्ण

	msleep(1); /* aव्योम I2C errors */

	ret = usb_control_msg(d->udev, pipe, request, requesttype, req->value,
		req->index, buf, req->size, EC168_USB_TIMEOUT);

	dvb_usb_dbg_usb_control_msg(d->udev, request, requesttype, req->value,
			req->index, buf, req->size);

	अगर (ret < 0)
		जाओ err_dealloc;
	अन्यथा
		ret = 0;

	/* पढ़ो request, copy वापसed data to वापस buf */
	अगर (!ret && requesttype == (USB_TYPE_VENDOR | USB_सूची_IN))
		स_नकल(req->data, buf, req->size);

	kमुक्त(buf);
	वापस ret;

err_dealloc:
	kमुक्त(buf);
error:
	dev_dbg(&d->udev->dev, "%s: failed=%d\n", __func__, ret);
	वापस ret;
पूर्ण

/* I2C */
अटल काष्ठा ec100_config ec168_ec100_config;

अटल पूर्णांक ec168_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msg[],
	पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	काष्ठा ec168_req req;
	पूर्णांक i = 0;
	पूर्णांक ret;

	अगर (num > 2)
		वापस -EINVAL;

	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	जबतक (i < num) अणु
		अगर (num > i + 1 && (msg[i+1].flags & I2C_M_RD)) अणु
			अगर (msg[i].addr == ec168_ec100_config.demod_address) अणु
				req.cmd = READ_DEMOD;
				req.value = 0;
				req.index = 0xff00 + msg[i].buf[0]; /* reg */
				req.size = msg[i+1].len; /* bytes to पढ़ो */
				req.data = &msg[i+1].buf[0];
				ret = ec168_ctrl_msg(d, &req);
				i += 2;
			पूर्ण अन्यथा अणु
				dev_err(&d->udev->dev, "%s: I2C read not " \
						"implemented\n",
						KBUILD_MODNAME);
				ret = -EOPNOTSUPP;
				i += 2;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (msg[i].addr == ec168_ec100_config.demod_address) अणु
				req.cmd = WRITE_DEMOD;
				req.value = msg[i].buf[1]; /* val */
				req.index = 0xff00 + msg[i].buf[0]; /* reg */
				req.size = 0;
				req.data = शून्य;
				ret = ec168_ctrl_msg(d, &req);
				i += 1;
			पूर्ण अन्यथा अणु
				req.cmd = WRITE_I2C;
				req.value = msg[i].buf[0]; /* val */
				req.index = 0x0100 + msg[i].addr; /* I2C addr */
				req.size = msg[i].len-1;
				req.data = &msg[i].buf[1];
				ret = ec168_ctrl_msg(d, &req);
				i += 1;
			पूर्ण
		पूर्ण
		अगर (ret)
			जाओ error;

	पूर्ण
	ret = i;

error:
	mutex_unlock(&d->i2c_mutex);
	वापस ret;
पूर्ण

अटल u32 ec168_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल काष्ठा i2c_algorithm ec168_i2c_algo = अणु
	.master_xfer   = ec168_i2c_xfer,
	.functionality = ec168_i2c_func,
पूर्ण;

/* Callbacks क्रम DVB USB */
अटल पूर्णांक ec168_identअगरy_state(काष्ठा dvb_usb_device *d, स्थिर अक्षर **name)
अणु
	पूर्णांक ret;
	u8 reply;
	काष्ठा ec168_req req = अणुGET_CONFIG, 0, 1, माप(reply), &replyपूर्ण;
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	ret = ec168_ctrl_msg(d, &req);
	अगर (ret)
		जाओ error;

	dev_dbg(&d->udev->dev, "%s: reply=%02x\n", __func__, reply);

	अगर (reply == 0x01)
		ret = WARM;
	अन्यथा
		ret = COLD;

	वापस ret;
error:
	dev_dbg(&d->udev->dev, "%s: failed=%d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक ec168_करोwnload_firmware(काष्ठा dvb_usb_device *d,
		स्थिर काष्ठा firmware *fw)
अणु
	पूर्णांक ret, len, reमुख्यing;
	काष्ठा ec168_req req = अणुDOWNLOAD_FIRMWARE, 0, 0, 0, शून्यपूर्ण;
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	#घोषणा LEN_MAX 2048 /* max packet size */
	क्रम (reमुख्यing = fw->size; reमुख्यing > 0; reमुख्यing -= LEN_MAX) अणु
		len = reमुख्यing;
		अगर (len > LEN_MAX)
			len = LEN_MAX;

		req.size = len;
		req.data = (u8 *) &fw->data[fw->size - reमुख्यing];
		req.index = fw->size - reमुख्यing;

		ret = ec168_ctrl_msg(d, &req);
		अगर (ret) अणु
			dev_err(&d->udev->dev,
					"%s: firmware download failed=%d\n",
					KBUILD_MODNAME, ret);
			जाओ error;
		पूर्ण
	पूर्ण

	req.size = 0;

	/* set "warm"? */
	req.cmd = SET_CONFIG;
	req.value = 0;
	req.index = 0x0001;
	ret = ec168_ctrl_msg(d, &req);
	अगर (ret)
		जाओ error;

	/* really needed - no idea what करोes */
	req.cmd = GPIO;
	req.value = 0;
	req.index = 0x0206;
	ret = ec168_ctrl_msg(d, &req);
	अगर (ret)
		जाओ error;

	/* activate tuner I2C? */
	req.cmd = WRITE_I2C;
	req.value = 0;
	req.index = 0x00c6;
	ret = ec168_ctrl_msg(d, &req);
	अगर (ret)
		जाओ error;

	वापस ret;
error:
	dev_dbg(&d->udev->dev, "%s: failed=%d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल काष्ठा ec100_config ec168_ec100_config = अणु
	.demod_address = 0xff, /* not real address, demod is पूर्णांकegrated */
पूर्ण;

अटल पूर्णांक ec168_ec100_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	adap->fe[0] = dvb_attach(ec100_attach, &ec168_ec100_config,
			&d->i2c_adap);
	अगर (adap->fe[0] == शून्य)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल काष्ठा mxl5005s_config ec168_mxl5003s_config = अणु
	.i2c_address     = 0xc6,
	.अगर_freq         = IF_FREQ_4570000HZ,
	.xtal_freq       = CRYSTAL_FREQ_16000000HZ,
	.agc_mode        = MXL_SINGLE_AGC,
	.tracking_filter = MXL_TF_OFF,
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

अटल पूर्णांक ec168_mxl5003s_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	वापस dvb_attach(mxl5005s_attach, adap->fe[0], &d->i2c_adap,
			&ec168_mxl5003s_config) == शून्य ? -ENODEV : 0;
पूर्ण

अटल पूर्णांक ec168_streaming_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा dvb_usb_device *d = fe_to_d(fe);
	काष्ठा ec168_req req = अणुSTREAMING_CTRL, 0x7f01, 0x0202, 0, शून्यपूर्ण;
	dev_dbg(&d->udev->dev, "%s: onoff=%d\n", __func__, onoff);

	अगर (onoff)
		req.index = 0x0102;
	वापस ec168_ctrl_msg(d, &req);
पूर्ण

/* DVB USB Driver stuff */
/* bInterfaceNumber 0 is HID
 * bInterfaceNumber 1 is DVB-T */
अटल स्थिर काष्ठा dvb_usb_device_properties ec168_props = अणु
	.driver_name = KBUILD_MODNAME,
	.owner = THIS_MODULE,
	.adapter_nr = adapter_nr,
	.bInterfaceNumber = 1,

	.identअगरy_state = ec168_identअगरy_state,
	.firmware = EC168_FIRMWARE,
	.करोwnload_firmware = ec168_करोwnload_firmware,

	.i2c_algo = &ec168_i2c_algo,
	.frontend_attach = ec168_ec100_frontend_attach,
	.tuner_attach = ec168_mxl5003s_tuner_attach,
	.streaming_ctrl = ec168_streaming_ctrl,

	.num_adapters = 1,
	.adapter = अणु
		अणु
			.stream = DVB_USB_STREAM_BULK(0x82, 6, 32 * 512),
		पूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id ec168_id[] = अणु
	अणु DVB_USB_DEVICE(USB_VID_E3C, USB_PID_E3C_EC168,
		     &ec168_props, "E3C EC168 reference design", शून्य)पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_E3C, USB_PID_E3C_EC168_2,
		     &ec168_props, "E3C EC168 reference design", शून्य)पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_E3C, USB_PID_E3C_EC168_3,
		     &ec168_props, "E3C EC168 reference design", शून्य)पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_E3C, USB_PID_E3C_EC168_4,
		     &ec168_props, "E3C EC168 reference design", शून्य)पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_E3C, USB_PID_E3C_EC168_5,
		     &ec168_props, "E3C EC168 reference design", शून्य)पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, ec168_id);

अटल काष्ठा usb_driver ec168_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = ec168_id,
	.probe = dvb_usbv2_probe,
	.disconnect = dvb_usbv2_disconnect,
	.suspend = dvb_usbv2_suspend,
	.resume = dvb_usbv2_resume,
	.no_dynamic_id = 1,
	.soft_unbind = 1,
पूर्ण;

module_usb_driver(ec168_driver);

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("E3C EC168 driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(EC168_FIRMWARE);
