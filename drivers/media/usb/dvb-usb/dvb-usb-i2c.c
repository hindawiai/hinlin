<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* dvb-usb-i2c.c is part of the DVB USB library.
 *
 * Copyright (C) 2004-6 Patrick Boettcher (patrick.boettcher@posteo.de)
 * see dvb-usb-init.c क्रम copyright inक्रमmation.
 *
 * This file contains functions क्रम (de-)initializing an I2C adapter.
 */
#समावेश "dvb-usb-common.h"

पूर्णांक dvb_usb_i2c_init(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक ret = 0;

	अगर (!(d->props.caps & DVB_USB_IS_AN_I2C_ADAPTER))
		वापस 0;

	अगर (d->props.i2c_algo == शून्य) अणु
		err("no i2c algorithm specified");
		वापस -EINVAL;
	पूर्ण

	strscpy(d->i2c_adap.name, d->desc->name, माप(d->i2c_adap.name));
	d->i2c_adap.algo      = d->props.i2c_algo;
	d->i2c_adap.algo_data = शून्य;
	d->i2c_adap.dev.parent = &d->udev->dev;

	i2c_set_adapdata(&d->i2c_adap, d);

	अगर ((ret = i2c_add_adapter(&d->i2c_adap)) < 0)
		err("could not add i2c adapter");

	d->state |= DVB_USB_STATE_I2C;

	वापस ret;
पूर्ण

पूर्णांक dvb_usb_i2c_निकास(काष्ठा dvb_usb_device *d)
अणु
	अगर (d->state & DVB_USB_STATE_I2C)
		i2c_del_adapter(&d->i2c_adap);
	d->state &= ~DVB_USB_STATE_I2C;
	वापस 0;
पूर्ण
