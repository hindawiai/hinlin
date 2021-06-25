<शैली गुरु>
/*
 * Siemens SX1 board definitions
 *
 * Copyright: Vovan888 at gmail com
 *
 * This package is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#अगर_अघोषित __ASM_ARCH_SX1_I2C_CHIPS_H
#घोषणा __ASM_ARCH_SX1_I2C_CHIPS_H

#घोषणा SOFIA_MAX_LIGHT_VAL	0x2B

#घोषणा SOFIA_I2C_ADDR		0x32
/* Sofia reg 3 bits masks */
#घोषणा SOFIA_POWER1_REG	0x03

#घोषणा	SOFIA_USB_POWER		0x01
#घोषणा	SOFIA_MMC_POWER		0x04
#घोषणा	SOFIA_BLUETOOTH_POWER	0x08
#घोषणा	SOFIA_MMILIGHT_POWER	0x20

#घोषणा SOFIA_POWER2_REG	0x04
#घोषणा SOFIA_BACKLIGHT_REG	0x06
#घोषणा SOFIA_KEYLIGHT_REG	0x07
#घोषणा SOFIA_DIMMING_REG	0x09


/* Function Prototypes क्रम SX1 devices control on I2C bus */

पूर्णांक sx1_setbacklight(u8 backlight);
पूर्णांक sx1_getbacklight(u8 *backlight);
पूर्णांक sx1_setkeylight(u8 keylight);
पूर्णांक sx1_getkeylight(u8 *keylight);

पूर्णांक sx1_seपंचांगmiघातer(u8 onoff);
पूर्णांक sx1_setusbघातer(u8 onoff);
पूर्णांक sx1_i2c_पढ़ो_byte(u8 devaddr, u8 regoffset, u8 *value);
पूर्णांक sx1_i2c_ग_लिखो_byte(u8 devaddr, u8 regoffset, u8 value);

/* MMC prototypes */

बाह्य व्योम sx1_mmc_init(व्योम);
बाह्य व्योम sx1_mmc_slot_cover_handler(व्योम *arg, पूर्णांक state);

#पूर्ण_अगर /* __ASM_ARCH_SX1_I2C_CHIPS_H */
