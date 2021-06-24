<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * E3C EC168 DVB USB driver
 *
 * Copyright (C) 2009 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित EC168_H
#घोषणा EC168_H

#समावेश "dvb_usb.h"

#घोषणा EC168_USB_TIMEOUT 1000
#घोषणा EC168_FIRMWARE "dvb-usb-ec168.fw"

काष्ठा ec168_req अणु
	u8  cmd;       /* [1] */
	u16 value;     /* [2|3] */
	u16 index;     /* [4|5] */
	u16 size;      /* [6|7] */
	u8  *data;
पूर्ण;

क्रमागत ec168_cmd अणु
	DOWNLOAD_FIRMWARE    = 0x00,
	CONFIG               = 0x01,
	DEMOD_RW             = 0x03,
	GPIO                 = 0x04,
	STREAMING_CTRL       = 0x10,
	READ_I2C             = 0x20,
	WRITE_I2C            = 0x21,
	HID_DOWNLOAD         = 0x30,
	GET_CONFIG,
	SET_CONFIG,
	READ_DEMOD,
	WRITE_DEMOD,
पूर्ण;

#पूर्ण_अगर
