<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Support क्रम the sensor part which is पूर्णांकegrated (I think) पूर्णांकo the
 * st6422 stv06xx alike bridge, as its पूर्णांकegrated there are no i2c ग_लिखोs
 * but instead direct bridge ग_लिखोs.
 *
 * Copyright (c) 2009 Hans de Goede <hdegoede@redhat.com>
 *
 * Strongly based on qc-usb-messenger, which is:
 * Copyright (c) 2001 Jean-Fredric Clere, Nikolas Zimmermann, Georg Acher
 *		      Mark Cave-Ayland, Carlo E Prelz, Dick Streefland
 * Copyright (c) 2002, 2003 Tuukka Toivonen
 */

#अगर_अघोषित STV06XX_ST6422_H_
#घोषणा STV06XX_ST6422_H_

#समावेश "stv06xx_sensor.h"

अटल पूर्णांक st6422_probe(काष्ठा sd *sd);
अटल पूर्णांक st6422_start(काष्ठा sd *sd);
अटल पूर्णांक st6422_init(काष्ठा sd *sd);
अटल पूर्णांक st6422_init_controls(काष्ठा sd *sd);
अटल पूर्णांक st6422_stop(काष्ठा sd *sd);

स्थिर काष्ठा stv06xx_sensor stv06xx_sensor_st6422 = अणु
	.name = "ST6422",
	/* No known way to lower framerate in हाल of less bandwidth */
	.min_packet_size = अणु 300, 847 पूर्ण,
	.max_packet_size = अणु 300, 847 पूर्ण,
	.init = st6422_init,
	.init_controls = st6422_init_controls,
	.probe = st6422_probe,
	.start = st6422_start,
	.stop = st6422_stop,
पूर्ण;

#पूर्ण_अगर
