<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DVB USB framework
 *
 * Copyright (C) 2004-6 Patrick Boettcher <patrick.boettcher@posteo.de>
 * Copyright (C) 2012 Antti Palosaari <crope@iki.fi>
 */

#समावेश "dvb_usb_common.h"

अटल पूर्णांक dvb_usb_v2_generic_io(काष्ठा dvb_usb_device *d,
		u8 *wbuf, u16 wlen, u8 *rbuf, u16 rlen)
अणु
	पूर्णांक ret, actual_length;

	अगर (!wbuf || !wlen || !d->props->generic_bulk_ctrl_endpoपूर्णांक ||
			!d->props->generic_bulk_ctrl_endpoपूर्णांक_response) अणु
		dev_dbg(&d->udev->dev, "%s: failed=%d\n", __func__, -EINVAL);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(&d->udev->dev, "%s: >>> %*ph\n", __func__, wlen, wbuf);

	ret = usb_bulk_msg(d->udev, usb_sndbulkpipe(d->udev,
			d->props->generic_bulk_ctrl_endpoपूर्णांक), wbuf, wlen,
			&actual_length, 2000);
	अगर (ret) अणु
		dev_err(&d->udev->dev, "%s: usb_bulk_msg() failed=%d\n",
				KBUILD_MODNAME, ret);
		वापस ret;
	पूर्ण
	अगर (actual_length != wlen) अणु
		dev_err(&d->udev->dev, "%s: usb_bulk_msg() write length=%d, actual=%d\n",
			KBUILD_MODNAME, wlen, actual_length);
		वापस -EIO;
	पूर्ण

	/* an answer is expected */
	अगर (rbuf && rlen) अणु
		अगर (d->props->generic_bulk_ctrl_delay)
			usleep_range(d->props->generic_bulk_ctrl_delay,
					d->props->generic_bulk_ctrl_delay
					+ 20000);

		ret = usb_bulk_msg(d->udev, usb_rcvbulkpipe(d->udev,
				d->props->generic_bulk_ctrl_endpoपूर्णांक_response),
				rbuf, rlen, &actual_length, 2000);
		अगर (ret)
			dev_err(&d->udev->dev,
					"%s: 2nd usb_bulk_msg() failed=%d\n",
					KBUILD_MODNAME, ret);

		dev_dbg(&d->udev->dev, "%s: <<< %*ph\n", __func__,
				actual_length, rbuf);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक dvb_usbv2_generic_rw(काष्ठा dvb_usb_device *d,
		u8 *wbuf, u16 wlen, u8 *rbuf, u16 rlen)
अणु
	पूर्णांक ret;

	mutex_lock(&d->usb_mutex);
	ret = dvb_usb_v2_generic_io(d, wbuf, wlen, rbuf, rlen);
	mutex_unlock(&d->usb_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(dvb_usbv2_generic_rw);

पूर्णांक dvb_usbv2_generic_ग_लिखो(काष्ठा dvb_usb_device *d, u8 *buf, u16 len)
अणु
	पूर्णांक ret;

	mutex_lock(&d->usb_mutex);
	ret = dvb_usb_v2_generic_io(d, buf, len, शून्य, 0);
	mutex_unlock(&d->usb_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(dvb_usbv2_generic_ग_लिखो);

पूर्णांक dvb_usbv2_generic_rw_locked(काष्ठा dvb_usb_device *d,
		u8 *wbuf, u16 wlen, u8 *rbuf, u16 rlen)
अणु
	वापस dvb_usb_v2_generic_io(d, wbuf, wlen, rbuf, rlen);
पूर्ण
EXPORT_SYMBOL(dvb_usbv2_generic_rw_locked);

पूर्णांक dvb_usbv2_generic_ग_लिखो_locked(काष्ठा dvb_usb_device *d, u8 *buf, u16 len)
अणु
	वापस dvb_usb_v2_generic_io(d, buf, len, शून्य, 0);
पूर्ण
EXPORT_SYMBOL(dvb_usbv2_generic_ग_लिखो_locked);
