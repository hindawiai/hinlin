<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * DVB USB Linux driver क्रम AME DTV-5100 USB2.0 DVB-T
 *
 * Copyright (C) 2008  Antoine Jacquet <royale@zerezo.com>
 * http://royale.zerezo.com/dtv5100/
 */

#अगर_अघोषित _DVB_USB_DTV5100_H_
#घोषणा _DVB_USB_DTV5100_H_

#घोषणा DVB_USB_LOG_PREFIX "dtv5100"
#समावेश "dvb-usb.h"

#घोषणा DTV5100_USB_TIMEOUT 500

#घोषणा DTV5100_DEMOD_ADDR	0x00
#घोषणा DTV5100_DEMOD_WRITE	0xc0
#घोषणा DTV5100_DEMOD_READ	0xc1

#घोषणा DTV5100_TUNER_ADDR	0xc4
#घोषणा DTV5100_TUNER_WRITE	0xc7
#घोषणा DTV5100_TUNER_READ	0xc8

#घोषणा DRIVER_AUTHOR "Antoine Jacquet, http://royale.zerezo.com/"
#घोषणा DRIVER_DESC "AME DTV-5100 USB2.0 DVB-T"

अटल काष्ठा अणु
	u8 request;
	u8 value;
	u16 index;
पूर्ण dtv5100_init[] = अणु
	अणु 0x000000c5, 0x00000000, 0x00000001 पूर्ण,
	अणु 0x000000c5, 0x00000001, 0x00000001 पूर्ण,
	अणु पूर्ण		/* Terminating entry */
पूर्ण;

#पूर्ण_अगर
