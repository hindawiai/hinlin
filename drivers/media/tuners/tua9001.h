<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Infineon TUA9001 silicon tuner driver
 *
 * Copyright (C) 2009 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित TUA9001_H
#घोषणा TUA9001_H

#समावेश <media/dvb_frontend.h>

/*
 * I2C address
 * 0x60,
 */

/**
 * काष्ठा tua9001_platक्रमm_data - Platक्रमm data क्रम the tua9001 driver
 * @dvb_frontend: DVB frontend.
 */
काष्ठा tua9001_platक्रमm_data अणु
	काष्ठा dvb_frontend *dvb_frontend;
पूर्ण;

/*
 * TUA9001 I/O PINs:
 *
 * CEN - chip enable
 * 0 = chip disabled (chip off)
 * 1 = chip enabled (chip on)
 *
 * RESETN - chip reset
 * 0 = reset disabled (chip reset off)
 * 1 = reset enabled (chip reset on)
 *
 * RXEN - RX enable
 * 0 = RX disabled (chip idle)
 * 1 = RX enabled (chip tuned)
 */

#घोषणा TUA9001_CMD_CEN     0
#घोषणा TUA9001_CMD_RESETN  1
#घोषणा TUA9001_CMD_RXEN    2

#पूर्ण_अगर
