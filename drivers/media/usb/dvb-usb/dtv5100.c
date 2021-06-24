<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DVB USB Linux driver क्रम AME DTV-5100 USB2.0 DVB-T
 *
 * Copyright (C) 2008  Antoine Jacquet <royale@zerezo.com>
 * http://royale.zerezo.com/dtv5100/
 *
 * Inspired by gl861.c and au6610.c drivers
 */

#समावेश "dtv5100.h"
#समावेश "zl10353.h"
#समावेश "qt1010.h"

/* debug */
अटल पूर्णांक dvb_usb_dtv5100_debug;
module_param_named(debug, dvb_usb_dtv5100_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debugging level" DVB_USB_DEBUG_STATUS);
DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

काष्ठा dtv5100_state अणु
	अचिन्हित अक्षर data[80];
पूर्ण;

अटल पूर्णांक dtv5100_i2c_msg(काष्ठा dvb_usb_device *d, u8 addr,
			   u8 *wbuf, u16 wlen, u8 *rbuf, u16 rlen)
अणु
	काष्ठा dtv5100_state *st = d->priv;
	u8 request;
	u8 type;
	u16 value;
	u16 index;

	चयन (wlen) अणु
	हाल 1:
		/* ग_लिखो अणु reg पूर्ण, पढ़ो अणु value पूर्ण */
		request = (addr == DTV5100_DEMOD_ADDR ? DTV5100_DEMOD_READ :
							DTV5100_TUNER_READ);
		type = USB_TYPE_VENDOR | USB_सूची_IN;
		value = 0;
		अवरोध;
	हाल 2:
		/* ग_लिखो अणु reg, value पूर्ण */
		request = (addr == DTV5100_DEMOD_ADDR ? DTV5100_DEMOD_WRITE :
							DTV5100_TUNER_WRITE);
		type = USB_TYPE_VENDOR | USB_सूची_OUT;
		value = wbuf[1];
		अवरोध;
	शेष:
		warn("wlen = %x, aborting.", wlen);
		वापस -EINVAL;
	पूर्ण
	index = (addr << 8) + wbuf[0];

	स_नकल(st->data, rbuf, rlen);
	msleep(1); /* aव्योम I2C errors */
	वापस usb_control_msg(d->udev, usb_rcvctrlpipe(d->udev, 0), request,
			       type, value, index, st->data, rlen,
			       DTV5100_USB_TIMEOUT);
पूर्ण

/* I2C */
अटल पूर्णांक dtv5100_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msg[],
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
			अगर (dtv5100_i2c_msg(d, msg[i].addr, msg[i].buf,
					    msg[i].len, msg[i+1].buf,
					    msg[i+1].len) < 0)
				अवरोध;
			i++;
		पूर्ण अन्यथा अगर (dtv5100_i2c_msg(d, msg[i].addr, msg[i].buf,
					   msg[i].len, शून्य, 0) < 0)
				अवरोध;
	पूर्ण

	mutex_unlock(&d->i2c_mutex);
	वापस i;
पूर्ण

अटल u32 dtv5100_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल काष्ठा i2c_algorithm dtv5100_i2c_algo = अणु
	.master_xfer   = dtv5100_i2c_xfer,
	.functionality = dtv5100_i2c_func,
पूर्ण;

/* Callbacks क्रम DVB USB */
अटल काष्ठा zl10353_config dtv5100_zl10353_config = अणु
	.demod_address = DTV5100_DEMOD_ADDR,
	.no_tuner = 1,
	.parallel_ts = 1,
पूर्ण;

अटल पूर्णांक dtv5100_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	adap->fe_adap[0].fe = dvb_attach(zl10353_attach, &dtv5100_zl10353_config,
			      &adap->dev->i2c_adap);
	अगर (adap->fe_adap[0].fe == शून्य)
		वापस -EIO;

	/* disable i2c gate, or it won't work... is this safe? */
	adap->fe_adap[0].fe->ops.i2c_gate_ctrl = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा qt1010_config dtv5100_qt1010_config = अणु
	.i2c_address = DTV5100_TUNER_ADDR
पूर्ण;

अटल पूर्णांक dtv5100_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	वापस dvb_attach(qt1010_attach,
			  adap->fe_adap[0].fe, &adap->dev->i2c_adap,
			  &dtv5100_qt1010_config) == शून्य ? -ENODEV : 0;
पूर्ण

/* DVB USB Driver stuff */
अटल काष्ठा dvb_usb_device_properties dtv5100_properties;

अटल पूर्णांक dtv5100_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक i, ret;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	/* initialize non qt1010/zl10353 part? */
	क्रम (i = 0; dtv5100_init[i].request; i++) अणु
		ret = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
				      dtv5100_init[i].request,
				      USB_TYPE_VENDOR | USB_सूची_OUT,
				      dtv5100_init[i].value,
				      dtv5100_init[i].index, शून्य, 0,
				      DTV5100_USB_TIMEOUT);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = dvb_usb_device_init(पूर्णांकf, &dtv5100_properties,
				  THIS_MODULE, शून्य, adapter_nr);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल काष्ठा usb_device_id dtv5100_table[] = अणु
	अणु USB_DEVICE(0x06be, 0xa232) पूर्ण,
	अणु पूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, dtv5100_table);

अटल काष्ठा dvb_usb_device_properties dtv5100_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,
	.usb_ctrl = DEVICE_SPECIFIC,

	.size_of_priv = माप(काष्ठा dtv5100_state),

	.num_adapters = 1,
	.adapter = अणुअणु
		.num_frontends = 1,
		.fe = अणुअणु
		.frontend_attach = dtv5100_frontend_attach,
		.tuner_attach    = dtv5100_tuner_attach,

		.stream = अणु
			.type = USB_BULK,
			.count = 8,
			.endpoपूर्णांक = 0x82,
			.u = अणु
				.bulk = अणु
					.buffersize = 4096,
				पूर्ण
			पूर्ण
		पूर्ण,
		पूर्णपूर्ण,
	पूर्ण पूर्ण,

	.i2c_algo = &dtv5100_i2c_algo,

	.num_device_descs = 1,
	.devices = अणु
		अणु
			.name = "AME DTV-5100 USB2.0 DVB-T",
			.cold_ids = अणु शून्य पूर्ण,
			.warm_ids = अणु &dtv5100_table[0], शून्य पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा usb_driver dtv5100_driver = अणु
	.name		= "dvb_usb_dtv5100",
	.probe		= dtv5100_probe,
	.disconnect	= dvb_usb_device_निकास,
	.id_table	= dtv5100_table,
पूर्ण;

module_usb_driver(dtv5100_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
