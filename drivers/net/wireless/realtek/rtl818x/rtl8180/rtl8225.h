<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित RTL8180_RTL8225_H
#घोषणा RTL8180_RTL8225_H

#घोषणा RTL8225_ANAPARAM_ON	0xa0000b59
#घोषणा RTL8225_ANAPARAM2_ON	0x860dec11
#घोषणा RTL8225_ANAPARAM_OFF	0xa00beb59
#घोषणा RTL8225_ANAPARAM2_OFF	0x840dec11

स्थिर काष्ठा rtl818x_rf_ops * rtl8180_detect_rf(काष्ठा ieee80211_hw *);

अटल अंतरभूत व्योम rtl8225_ग_लिखो_phy_ofdm(काष्ठा ieee80211_hw *dev,
					  u8 addr, u8 data)
अणु
	rtl8180_ग_लिखो_phy(dev, addr, data);
पूर्ण

अटल अंतरभूत व्योम rtl8225_ग_लिखो_phy_cck(काष्ठा ieee80211_hw *dev,
					 u8 addr, u8 data)
अणु
	rtl8180_ग_लिखो_phy(dev, addr, data | 0x10000);
पूर्ण

#पूर्ण_अगर /* RTL8180_RTL8225_H */
