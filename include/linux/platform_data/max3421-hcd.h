<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2014 eGauge Systems LLC
 *	Contributed by David Mosberger-Tang <davidm@egauge.net>
 *
 * Platक्रमm-data काष्ठाure क्रम MAX3421 USB HCD driver.
 *
 */
#अगर_अघोषित MAX3421_HCD_PLAT_H_INCLUDED
#घोषणा MAX3421_HCD_PLAT_H_INCLUDED

/*
 * This काष्ठाure defines the mapping of certain auxiliary functions to the
 * MAX3421E GPIO pins.  The chip has eight GP inमाला_दो and eight GP outमाला_दो.
 * A value of 0 indicates that the pin is not used/wired to anything.
 *
 * At this poपूर्णांक, the only control the max3421-hcd driver cares about is
 * to control Vbus (5V to the peripheral).
 */
काष्ठा max3421_hcd_platक्रमm_data अणु
	u8 vbus_gpout;			/* pin controlling Vbus */
	u8 vbus_active_level;		/* level that turns on घातer */
पूर्ण;

#पूर्ण_अगर /* MAX3421_HCD_PLAT_H_INCLUDED */
