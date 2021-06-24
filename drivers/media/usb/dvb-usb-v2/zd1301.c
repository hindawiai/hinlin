<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ZyDAS ZD1301 driver (USB पूर्णांकerface)
 *
 * Copyright (C) 2015 Antti Palosaari <crope@iki.fi>
 */

#समावेश "dvb_usb.h"
#समावेश "zd1301_demod.h"
#समावेश "mt2060.h"
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

काष्ठा zd1301_dev अणु
	#घोषणा BUF_LEN 8
	u8 buf[BUF_LEN]; /* bulk USB control message */
	काष्ठा zd1301_demod_platक्रमm_data demod_pdata;
	काष्ठा mt2060_platक्रमm_data mt2060_pdata;
	काष्ठा platक्रमm_device *platक्रमm_device_demod;
	काष्ठा i2c_client *i2c_client_tuner;
पूर्ण;

अटल पूर्णांक zd1301_ctrl_msg(काष्ठा dvb_usb_device *d, स्थिर u8 *wbuf,
			   अचिन्हित पूर्णांक wlen, u8 *rbuf, अचिन्हित पूर्णांक rlen)
अणु
	काष्ठा zd1301_dev *dev = d_to_priv(d);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret, actual_length;

	mutex_lock(&d->usb_mutex);

	स_नकल(&dev->buf, wbuf, wlen);

	dev_dbg(&पूर्णांकf->dev, ">>> %*ph\n", wlen, dev->buf);

	ret = usb_bulk_msg(d->udev, usb_sndbulkpipe(d->udev, 0x04), dev->buf,
			   wlen, &actual_length, 1000);
	अगर (ret) अणु
		dev_err(&पूर्णांकf->dev, "1st usb_bulk_msg() failed %d\n", ret);
		जाओ err_mutex_unlock;
	पूर्ण

	अगर (rlen) अणु
		ret = usb_bulk_msg(d->udev, usb_rcvbulkpipe(d->udev, 0x83),
				   dev->buf, rlen, &actual_length, 1000);
		अगर (ret) अणु
			dev_err(&पूर्णांकf->dev,
				"2nd usb_bulk_msg() failed %d\n", ret);
			जाओ err_mutex_unlock;
		पूर्ण

		dev_dbg(&पूर्णांकf->dev, "<<< %*ph\n", actual_length, dev->buf);

		अगर (actual_length != rlen) अणु
			/*
			 * Chip replies often with 3 byte len stub. On that हाल
			 * we have to query new reply.
			 */
			dev_dbg(&पूर्णांकf->dev, "repeating reply message\n");

			ret = usb_bulk_msg(d->udev,
					   usb_rcvbulkpipe(d->udev, 0x83),
					   dev->buf, rlen, &actual_length,
					   1000);
			अगर (ret) अणु
				dev_err(&पूर्णांकf->dev,
					"3rd usb_bulk_msg() failed %d\n", ret);
				जाओ err_mutex_unlock;
			पूर्ण

			dev_dbg(&पूर्णांकf->dev,
				"<<< %*ph\n", actual_length, dev->buf);
		पूर्ण

		स_नकल(rbuf, dev->buf, rlen);
	पूर्ण

err_mutex_unlock:
	mutex_unlock(&d->usb_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक zd1301_demod_wreg(व्योम *reg_priv, u16 reg, u8 val)
अणु
	काष्ठा dvb_usb_device *d = reg_priv;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret;
	u8 buf[7] = अणु0x07, 0x00, 0x03, 0x01,
		     (reg >> 0) & 0xff, (reg >> 8) & 0xff, valपूर्ण;

	ret = zd1301_ctrl_msg(d, buf, 7, शून्य, 0);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक zd1301_demod_rreg(व्योम *reg_priv, u16 reg, u8 *val)
अणु
	काष्ठा dvb_usb_device *d = reg_priv;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret;
	u8 buf[7] = अणु0x07, 0x00, 0x04, 0x01,
		     (reg >> 0) & 0xff, (reg >> 8) & 0xff, 0पूर्ण;

	ret = zd1301_ctrl_msg(d, buf, 7, buf, 7);
	अगर (ret)
		जाओ err;

	*val = buf[6];

	वापस 0;
err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक zd1301_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा zd1301_dev *dev = adap_to_priv(adap);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा i2c_client *client;
	काष्ठा i2c_board_info board_info;
	काष्ठा i2c_adapter *adapter;
	काष्ठा dvb_frontend *frontend;
	पूर्णांक ret;

	dev_dbg(&पूर्णांकf->dev, "\n");

	/* Add platक्रमm demod */
	dev->demod_pdata.reg_priv = d;
	dev->demod_pdata.reg_पढ़ो = zd1301_demod_rreg;
	dev->demod_pdata.reg_ग_लिखो = zd1301_demod_wreg;
	request_module("%s", "zd1301_demod");
	pdev = platक्रमm_device_रेजिस्टर_data(&पूर्णांकf->dev,
					     "zd1301_demod",
					     PLATFORM_DEVID_AUTO,
					     &dev->demod_pdata,
					     माप(dev->demod_pdata));
	अगर (IS_ERR(pdev)) अणु
		ret = PTR_ERR(pdev);
		जाओ err;
	पूर्ण
	अगर (!pdev->dev.driver) अणु
		ret = -ENODEV;
		जाओ err_platक्रमm_device_unरेजिस्टर;
	पूर्ण
	अगर (!try_module_get(pdev->dev.driver->owner)) अणु
		ret = -ENODEV;
		जाओ err_platक्रमm_device_unरेजिस्टर;
	पूर्ण

	adapter = zd1301_demod_get_i2c_adapter(pdev);
	frontend = zd1301_demod_get_dvb_frontend(pdev);
	अगर (!adapter || !frontend) अणु
		ret = -ENODEV;
		जाओ err_module_put_demod;
	पूर्ण

	/* Add I2C tuner */
	dev->mt2060_pdata.i2c_ग_लिखो_max = 9;
	dev->mt2060_pdata.dvb_frontend = frontend;
	स_रखो(&board_info, 0, माप(board_info));
	strscpy(board_info.type, "mt2060", I2C_NAME_SIZE);
	board_info.addr = 0x60;
	board_info.platक्रमm_data = &dev->mt2060_pdata;
	request_module("%s", "mt2060");
	client = i2c_new_client_device(adapter, &board_info);
	अगर (!i2c_client_has_driver(client)) अणु
		ret = -ENODEV;
		जाओ err_module_put_demod;
	पूर्ण
	अगर (!try_module_get(client->dev.driver->owner)) अणु
		ret = -ENODEV;
		जाओ err_i2c_unरेजिस्टर_device;
	पूर्ण

	dev->platक्रमm_device_demod = pdev;
	dev->i2c_client_tuner = client;
	adap->fe[0] = frontend;

	वापस 0;
err_i2c_unरेजिस्टर_device:
	i2c_unरेजिस्टर_device(client);
err_module_put_demod:
	module_put(pdev->dev.driver->owner);
err_platक्रमm_device_unरेजिस्टर:
	platक्रमm_device_unरेजिस्टर(pdev);
err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक zd1301_frontend_detach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा zd1301_dev *dev = d_to_priv(d);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा i2c_client *client;

	dev_dbg(&पूर्णांकf->dev, "\n");

	client = dev->i2c_client_tuner;
	pdev = dev->platक्रमm_device_demod;

	/* Remove I2C tuner */
	अगर (client) अणु
		module_put(client->dev.driver->owner);
		i2c_unरेजिस्टर_device(client);
	पूर्ण

	/* Remove platक्रमm demod */
	अगर (pdev) अणु
		module_put(pdev->dev.driver->owner);
		platक्रमm_device_unरेजिस्टर(pdev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक zd1301_streaming_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा dvb_usb_device *d = fe_to_d(fe);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = d->पूर्णांकf;
	पूर्णांक ret;
	u8 buf[3] = अणु0x03, 0x00, onoff ? 0x07 : 0x08पूर्ण;

	dev_dbg(&पूर्णांकf->dev, "onoff=%d\n", onoff);

	ret = zd1301_ctrl_msg(d, buf, 3, शून्य, 0);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dvb_usb_device_properties zd1301_props = अणु
	.driver_name = KBUILD_MODNAME,
	.owner = THIS_MODULE,
	.adapter_nr = adapter_nr,
	.size_of_priv = माप(काष्ठा zd1301_dev),

	.frontend_attach = zd1301_frontend_attach,
	.frontend_detach = zd1301_frontend_detach,
	.streaming_ctrl  = zd1301_streaming_ctrl,

	.num_adapters = 1,
	.adapter = अणु
		अणु
			.stream = DVB_USB_STREAM_BULK(0x81, 6, 21 * 188),
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id zd1301_id_table[] = अणु
	अणुDVB_USB_DEVICE(USB_VID_ZYDAS, 0x13a1, &zd1301_props,
			"ZyDAS ZD1301 reference design", शून्य)पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, zd1301_id_table);

/* Usb specअगरic object needed to रेजिस्टर this driver with the usb subप्रणाली */
अटल काष्ठा usb_driver zd1301_usb_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = zd1301_id_table,
	.probe = dvb_usbv2_probe,
	.disconnect = dvb_usbv2_disconnect,
	.suspend = dvb_usbv2_suspend,
	.resume = dvb_usbv2_resume,
	.reset_resume = dvb_usbv2_reset_resume,
	.no_dynamic_id = 1,
	.soft_unbind = 1,
पूर्ण;
module_usb_driver(zd1301_usb_driver);

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("ZyDAS ZD1301 driver");
MODULE_LICENSE("GPL");
