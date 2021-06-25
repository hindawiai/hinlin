<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * max6697.h
 *     Copyright (c) 2012 Guenter Roeck <linux@roeck-us.net>
 */

#अगर_अघोषित MAX6697_H
#घोषणा MAX6697_H

#समावेश <linux/types.h>

/*
 * For all bit masks:
 * bit 0:    local temperature
 * bit 1..7: remote temperatures
 */
काष्ठा max6697_platक्रमm_data अणु
	bool smbus_समयout_disable;	/* set to disable SMBus समयouts */
	bool extended_range_enable;	/* set to enable extended temp range */
	bool beta_compensation;		/* set to enable beta compensation */
	u8 alert_mask;			/* set bit to 1 to disable alert */
	u8 over_temperature_mask;	/* set bit to 1 to disable */
	u8 resistance_cancellation;	/* set bit to 0 to disable
					 * bit mask क्रम MAX6581,
					 * boolean क्रम other chips
					 */
	u8 ideality_mask;		/* set bit to 0 to disable */
	u8 ideality_value;		/* transistor ideality as per
					 * MAX6581 datasheet
					 */
पूर्ण;

#पूर्ण_अगर /* MAX6697_H */
