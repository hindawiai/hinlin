<शैली गुरु>
/*
 * ds1307.h - platक्रमm_data क्रम the ds1307 (and variants) rtc driver
 * (C) Copyright 2012 by Wolfram Sang, Pengutronix e.K.
 * same license as the driver
 */

#अगर_अघोषित _LINUX_DS1307_H
#घोषणा _LINUX_DS1307_H

#समावेश <linux/types.h>

#घोषणा DS1307_TRICKLE_CHARGER_250_OHM	0x01
#घोषणा DS1307_TRICKLE_CHARGER_2K_OHM	0x02
#घोषणा DS1307_TRICKLE_CHARGER_4K_OHM	0x03
#घोषणा DS1307_TRICKLE_CHARGER_NO_DIODE	0x04
#घोषणा DS1307_TRICKLE_CHARGER_DIODE	0x08

काष्ठा ds1307_platक्रमm_data अणु
	u8 trickle_अक्षरger_setup;
पूर्ण;

#पूर्ण_अगर /* _LINUX_DS1307_H */
