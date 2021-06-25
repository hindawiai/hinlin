<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Based on the r8180 driver, which is:
 * Copyright 2004-2005 Andrea Merello <andrea.merello@gmail.com>, et al.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#समावेश "rtl_core.h"
#समावेश "rtl_eeprom.h"

अटल व्योम _rtl92e_gpio_ग_लिखो_bit(काष्ठा net_device *dev, पूर्णांक no, bool val)
अणु
	u8 reg = rtl92e_पढ़ोb(dev, EPROM_CMD);

	अगर (val)
		reg |= 1 << no;
	अन्यथा
		reg &= ~(1 << no);

	rtl92e_ग_लिखोb(dev, EPROM_CMD, reg);
	udelay(EPROM_DELAY);
पूर्ण

अटल bool _rtl92e_gpio_get_bit(काष्ठा net_device *dev, पूर्णांक no)
अणु
	u8 reg = rtl92e_पढ़ोb(dev, EPROM_CMD);

	वापस (reg >> no) & 0x1;
पूर्ण

अटल व्योम _rtl92e_eeprom_ck_cycle(काष्ठा net_device *dev)
अणु
	_rtl92e_gpio_ग_लिखो_bit(dev, EPROM_CK_BIT, 1);
	_rtl92e_gpio_ग_लिखो_bit(dev, EPROM_CK_BIT, 0);
पूर्ण

अटल u16 _rtl92e_eeprom_xfer(काष्ठा net_device *dev, u16 data, पूर्णांक tx_len)
अणु
	u16 ret = 0;
	पूर्णांक rx_len = 16;

	_rtl92e_gpio_ग_लिखो_bit(dev, EPROM_CS_BIT, 1);
	_rtl92e_eeprom_ck_cycle(dev);

	जबतक (tx_len--) अणु
		_rtl92e_gpio_ग_लिखो_bit(dev, EPROM_W_BIT,
				       (data >> tx_len) & 0x1);
		_rtl92e_eeprom_ck_cycle(dev);
	पूर्ण

	_rtl92e_gpio_ग_लिखो_bit(dev, EPROM_W_BIT, 0);

	जबतक (rx_len--) अणु
		_rtl92e_eeprom_ck_cycle(dev);
		ret |= _rtl92e_gpio_get_bit(dev, EPROM_R_BIT) << rx_len;
	पूर्ण

	_rtl92e_gpio_ग_लिखो_bit(dev, EPROM_CS_BIT, 0);
	_rtl92e_eeprom_ck_cycle(dev);

	वापस ret;
पूर्ण

u32 rtl92e_eeprom_पढ़ो(काष्ठा net_device *dev, u32 addr)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u32 ret = 0;

	rtl92e_ग_लिखोb(dev, EPROM_CMD,
		      (EPROM_CMD_PROGRAM << EPROM_CMD_OPERATING_MODE_SHIFT));
	udelay(EPROM_DELAY);

	/* EEPROM is configured as x16 */
	अगर (priv->epromtype == EEPROM_93C56)
		ret = _rtl92e_eeprom_xfer(dev, (addr & 0xFF) | (0x6 << 8), 11);
	अन्यथा
		ret = _rtl92e_eeprom_xfer(dev, (addr & 0x3F) | (0x6 << 6), 9);

	rtl92e_ग_लिखोb(dev, EPROM_CMD,
		      (EPROM_CMD_NORMAL<<EPROM_CMD_OPERATING_MODE_SHIFT));
	वापस ret;
पूर्ण
