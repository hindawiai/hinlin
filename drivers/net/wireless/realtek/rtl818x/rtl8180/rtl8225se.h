<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

/* Definitions क्रम RTL8187SE hardware
 *
 * Copyright 2009 Larry Finger <Larry.Finger@lwfinger.net>
 * Copyright 2014 Andrea Merello <andrea.merello@gmail.com>
 *
 * Based on the r8180 and Realtek r8187se drivers, which are:
 * Copyright 2004-2005 Andrea Merello <andrea.merello@gmail.com>, et al.
 *
 * Also based on the rtl8187 driver, which is:
 * Copyright 2007 Michael Wu <flamingice@sourmilk.net>
 * Copyright 2007 Andrea Merello <andrea.merello@gmail.com>
 */

#अगर_अघोषित RTL8187SE_RTL8225_H
#घोषणा RTL8187SE_RTL8225_H

#घोषणा RTL8225SE_ANAPARAM_ON	0xb0054d00
#घोषणा RTL8225SE_ANAPARAM2_ON	0x000004c6

/* all off except PLL */
#घोषणा RTL8225SE_ANAPARAM_OFF	0xb0054dec
/* all on including PLL */
#घोषणा RTL8225SE_ANAPARAM_OFF2	0xb0054dfc

#घोषणा RTL8225SE_ANAPARAM2_OFF	0x00ff04c6

#घोषणा RTL8225SE_ANAPARAM3	0x10

क्रमागत rtl8187se_घातer_state अणु
	RTL8187SE_POWER_ON,
	RTL8187SE_POWER_OFF,
	RTL8187SE_POWER_SLEEP
पूर्ण;

अटल अंतरभूत व्योम rtl8225se_ग_लिखो_phy_ofdm(काष्ठा ieee80211_hw *dev,
					  u8 addr, u8 data)
अणु
	rtl8180_ग_लिखो_phy(dev, addr, data);
पूर्ण

अटल अंतरभूत व्योम rtl8225se_ग_लिखो_phy_cck(काष्ठा ieee80211_hw *dev,
					 u8 addr, u8 data)
अणु
	rtl8180_ग_लिखो_phy(dev, addr, data | 0x10000);
पूर्ण


स्थिर काष्ठा rtl818x_rf_ops *rtl8187se_detect_rf(काष्ठा ieee80211_hw *);
व्योम rtl8225se_rf_stop(काष्ठा ieee80211_hw *dev);
व्योम rtl8225se_rf_set_channel(काष्ठा ieee80211_hw *dev,
				     काष्ठा ieee80211_conf *conf);
व्योम rtl8225se_rf_conf_erp(काष्ठा ieee80211_hw *dev,
				  काष्ठा ieee80211_bss_conf *info);
व्योम rtl8225se_rf_init(काष्ठा ieee80211_hw *dev);

#पूर्ण_अगर /* RTL8187SE_RTL8225_H */
