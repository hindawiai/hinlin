<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Radio tuning definitions क्रम RTL8225 on RTL8187
 *
 * Copyright 2007 Michael Wu <flamingice@sourmilk.net>
 * Copyright 2007 Andrea Merello <andrea.merello@gmail.com>
 *
 * Based on the r8187 driver, which is:
 * Copyright 2005 Andrea Merello <andrea.merello@gmail.com>, et al.
 */

#अगर_अघोषित RTL8187_RTL8225_H
#घोषणा RTL8187_RTL8225_H

#घोषणा RTL8187_RTL8225_ANAPARAM_ON	0xa0000a59
#घोषणा RTL8187_RTL8225_ANAPARAM2_ON	0x860c7312
#घोषणा RTL8187_RTL8225_ANAPARAM_OFF	0xa00beb59
#घोषणा RTL8187_RTL8225_ANAPARAM2_OFF	0x840dec11

#घोषणा RTL8187B_RTL8225_ANAPARAM_ON	0x45090658
#घोषणा RTL8187B_RTL8225_ANAPARAM2_ON	0x727f3f52
#घोषणा RTL8187B_RTL8225_ANAPARAM3_ON	0x00
#घोषणा RTL8187B_RTL8225_ANAPARAM_OFF	0x55480658
#घोषणा RTL8187B_RTL8225_ANAPARAM2_OFF	0x72003f50
#घोषणा RTL8187B_RTL8225_ANAPARAM3_OFF	0x00

स्थिर काष्ठा rtl818x_rf_ops * rtl8187_detect_rf(काष्ठा ieee80211_hw *);

अटल अंतरभूत व्योम rtl8225_ग_लिखो_phy_ofdm(काष्ठा ieee80211_hw *dev,
					  u8 addr, u32 data)
अणु
	rtl8187_ग_लिखो_phy(dev, addr, data);
पूर्ण

अटल अंतरभूत व्योम rtl8225_ग_लिखो_phy_cck(काष्ठा ieee80211_hw *dev,
					 u8 addr, u32 data)
अणु
	rtl8187_ग_लिखो_phy(dev, addr, data | 0x10000);
पूर्ण

#पूर्ण_अगर /* RTL8187_RTL8225_H */
