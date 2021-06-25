<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * DVB USB framework
 *
 * Copyright (C) 2004-6 Patrick Boettcher <patrick.boettcher@posteo.de>
 * Copyright (C) 2012 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित DVB_USB_COMMON_H
#घोषणा DVB_USB_COMMON_H

#समावेश "dvb_usb.h"

/* commonly used  methods */
बाह्य पूर्णांक usb_urb_initv2(काष्ठा usb_data_stream *stream,
		स्थिर काष्ठा usb_data_stream_properties *props);
बाह्य पूर्णांक usb_urb_निकासv2(काष्ठा usb_data_stream *stream);
बाह्य पूर्णांक usb_urb_submitv2(काष्ठा usb_data_stream *stream,
		काष्ठा usb_data_stream_properties *props);
बाह्य पूर्णांक usb_urb_समाप्तv2(काष्ठा usb_data_stream *stream);

#पूर्ण_अगर
