<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * gpपन.स -- GPIO driver क्रम NXP PCF50633
 *
 * (C) 2006-2008 by Openmoko, Inc.
 * All rights reserved.
 */

#अगर_अघोषित __LINUX_MFD_PCF50633_GPIO_H
#घोषणा __LINUX_MFD_PCF50633_GPIO_H

#समावेश <linux/mfd/pcf50633/core.h>

#घोषणा PCF50633_GPIO1		1
#घोषणा PCF50633_GPIO2		2
#घोषणा PCF50633_GPIO3		3
#घोषणा PCF50633_GPO		4

#घोषणा PCF50633_REG_GPIO1CFG	0x14
#घोषणा PCF50633_REG_GPIO2CFG	0x15
#घोषणा PCF50633_REG_GPIO3CFG	0x16
#घोषणा PCF50633_REG_GPOCFG 	0x17

#घोषणा PCF50633_GPOCFG_GPOSEL_MASK	0x07

क्रमागत pcf50633_reg_gpocfg अणु
	PCF50633_GPOCFG_GPOSEL_0	= 0x00,
	PCF50633_GPOCFG_GPOSEL_LED_NFET	= 0x01,
	PCF50633_GPOCFG_GPOSEL_SYSxOK	= 0x02,
	PCF50633_GPOCFG_GPOSEL_CLK32K	= 0x03,
	PCF50633_GPOCFG_GPOSEL_ADAPUSB	= 0x04,
	PCF50633_GPOCFG_GPOSEL_USBxOK	= 0x05,
	PCF50633_GPOCFG_GPOSEL_ACTPH4	= 0x06,
	PCF50633_GPOCFG_GPOSEL_1	= 0x07,
	PCF50633_GPOCFG_GPOSEL_INVERSE	= 0x08,
पूर्ण;

पूर्णांक pcf50633_gpio_set(काष्ठा pcf50633 *pcf, पूर्णांक gpio, u8 val);
u8 pcf50633_gpio_get(काष्ठा pcf50633 *pcf, पूर्णांक gpio);

पूर्णांक pcf50633_gpio_invert_set(काष्ठा pcf50633 *, पूर्णांक gpio, पूर्णांक invert);
पूर्णांक pcf50633_gpio_invert_get(काष्ठा pcf50633 *pcf, पूर्णांक gpio);

पूर्णांक pcf50633_gpio_घातer_supply_set(काष्ठा pcf50633 *,
					पूर्णांक gpio, पूर्णांक regulator, पूर्णांक on);
#पूर्ण_अगर /* __LINUX_MFD_PCF50633_GPIO_H */


