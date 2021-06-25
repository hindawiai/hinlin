<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DVB USB Linux driver क्रम Alcor Micro AU6610 DVB-T USB2.0.
 *
 * Copyright (C) 2006 Antti Palosaari <crope@iki.fi>
 */

#समावेश "au6610.h"
#समावेश "zl10353.h"
#समावेश "qt1010.h"

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

अटल पूर्णांक au6610_usb_msg(काष्ठा dvb_usb_device *d, u8 operation, u8 addr,
			  u8 *wbuf, u16 wlen, u8 *rbuf, u16 rlen)
अणु
	पूर्णांक ret;
	u16 index;
	u8 *usb_buf;

	/*
	 * allocate enough क्रम all known requests,
	 * पढ़ो वापसs 5 and ग_लिखो 6 bytes
	 */
	usb_buf = kदो_स्मृति(6, GFP_KERNEL);
	अगर (!usb_buf)
		वापस -ENOMEM;

	चयन (wlen) अणु
	हाल 1:
		index = wbuf[0] << 8;
		अवरोध;
	हाल 2:
		index = wbuf[0] << 8;
		index += wbuf[1];
		अवरोध;
	शेष:
		dev_err(&d->udev->dev, "%s: wlen=%d, aborting\n",
				KBUILD_MODNAME, wlen);
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	ret = usb_control_msg(d->udev, usb_rcvctrlpipe(d->udev, 0), operation,
			      USB_TYPE_VENDOR|USB_सूची_IN, addr << 1, index,
			      usb_buf, 6, AU6610_USB_TIMEOUT);

	dvb_usb_dbg_usb_control_msg(d->udev, operation,
			(USB_TYPE_VENDOR|USB_सूची_IN), addr << 1, index,
			usb_buf, 6);

	अगर (ret < 0)
		जाओ error;

	चयन (operation) अणु
	हाल AU6610_REQ_I2C_READ:
	हाल AU6610_REQ_USB_READ:
		/* requested value is always 5th byte in buffer */
		rbuf[0] = usb_buf[4];
	पूर्ण
error:
	kमुक्त(usb_buf);
	वापस ret;
पूर्ण

अटल पूर्णांक au6610_i2c_msg(काष्ठा dvb_usb_device *d, u8 addr,
			  u8 *wbuf, u16 wlen, u8 *rbuf, u16 rlen)
अणु
	u8 request;
	u8 wo = (rbuf == शून्य || rlen == 0); /* ग_लिखो-only */

	अगर (wo) अणु
		request = AU6610_REQ_I2C_WRITE;
	पूर्ण अन्यथा अणु /* rw */
		request = AU6610_REQ_I2C_READ;
	पूर्ण

	वापस au6610_usb_msg(d, request, addr, wbuf, wlen, rbuf, rlen);
पूर्ण


/* I2C */
अटल पूर्णांक au6610_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msg[],
			   पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	पूर्णांक i;

	अगर (num > 2)
		वापस -EINVAL;

	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	क्रम (i = 0; i < num; i++) अणु
		/* ग_लिखो/पढ़ो request */
		अगर (i+1 < num && (msg[i+1].flags & I2C_M_RD)) अणु
			अगर (au6610_i2c_msg(d, msg[i].addr, msg[i].buf,
					   msg[i].len, msg[i+1].buf,
					   msg[i+1].len) < 0)
				अवरोध;
			i++;
		पूर्ण अन्यथा अगर (au6610_i2c_msg(d, msg[i].addr, msg[i].buf,
					       msg[i].len, शून्य, 0) < 0)
				अवरोध;
	पूर्ण

	mutex_unlock(&d->i2c_mutex);
	वापस i;
पूर्ण


अटल u32 au6610_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल काष्ठा i2c_algorithm au6610_i2c_algo = अणु
	.master_xfer   = au6610_i2c_xfer,
	.functionality = au6610_i2c_func,
पूर्ण;

/* Callbacks क्रम DVB USB */
अटल काष्ठा zl10353_config au6610_zl10353_config = अणु
	.demod_address = 0x0f,
	.no_tuner = 1,
	.parallel_ts = 1,
पूर्ण;

अटल पूर्णांक au6610_zl10353_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	adap->fe[0] = dvb_attach(zl10353_attach, &au6610_zl10353_config,
			&adap_to_d(adap)->i2c_adap);
	अगर (adap->fe[0] == शून्य)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल काष्ठा qt1010_config au6610_qt1010_config = अणु
	.i2c_address = 0x62
पूर्ण;

अटल पूर्णांक au6610_qt1010_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	वापस dvb_attach(qt1010_attach, adap->fe[0],
			&adap_to_d(adap)->i2c_adap,
			&au6610_qt1010_config) == शून्य ? -ENODEV : 0;
पूर्ण

अटल पूर्णांक au6610_init(काष्ठा dvb_usb_device *d)
अणु
	/* TODO: this functionality beदीर्घs likely to the streaming control */
	/* bInterfaceNumber 0, bAlternateSetting 5 */
	वापस usb_set_पूर्णांकerface(d->udev, 0, 5);
पूर्ण

अटल काष्ठा dvb_usb_device_properties au6610_props = अणु
	.driver_name = KBUILD_MODNAME,
	.owner = THIS_MODULE,
	.adapter_nr = adapter_nr,

	.i2c_algo = &au6610_i2c_algo,
	.frontend_attach = au6610_zl10353_frontend_attach,
	.tuner_attach = au6610_qt1010_tuner_attach,
	.init = au6610_init,

	.num_adapters = 1,
	.adapter = अणु
		अणु
			.stream = DVB_USB_STREAM_ISOC(0x82, 5, 40, 942, 1),
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id au6610_id_table[] = अणु
	अणु DVB_USB_DEVICE(USB_VID_ALCOR_MICRO, USB_PID_SIGMATEK_DVB_110,
		&au6610_props, "Sigmatek DVB-110", शून्य) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, au6610_id_table);

अटल काष्ठा usb_driver au6610_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = au6610_id_table,
	.probe = dvb_usbv2_probe,
	.disconnect = dvb_usbv2_disconnect,
	.suspend = dvb_usbv2_suspend,
	.resume = dvb_usbv2_resume,
	.reset_resume = dvb_usbv2_reset_resume,
	.no_dynamic_id = 1,
	.soft_unbind = 1,
पूर्ण;

module_usb_driver(au6610_driver);

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("Driver for Alcor Micro AU6610 DVB-T USB2.0");
MODULE_VERSION("0.1");
MODULE_LICENSE("GPL");
