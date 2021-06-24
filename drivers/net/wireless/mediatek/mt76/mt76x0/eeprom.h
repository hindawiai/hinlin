<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 * Copyright (C) 2018 Stanislaw Gruszka <stf_xl@wp.pl>
 */

#अगर_अघोषित __MT76X0U_EEPROM_H
#घोषणा __MT76X0U_EEPROM_H

#समावेश "../mt76x02_eeprom.h"

काष्ठा mt76x02_dev;

#घोषणा MT76X0U_EE_MAX_VER		0x0c
#घोषणा MT76X0_EEPROM_SIZE		512

पूर्णांक mt76x0_eeprom_init(काष्ठा mt76x02_dev *dev);
व्योम mt76x0_पढ़ो_rx_gain(काष्ठा mt76x02_dev *dev);
व्योम mt76x0_get_tx_घातer_per_rate(काष्ठा mt76x02_dev *dev,
				  काष्ठा ieee80211_channel *chan,
				  काष्ठा mt76_rate_घातer *t);
व्योम mt76x0_get_घातer_info(काष्ठा mt76x02_dev *dev,
			   काष्ठा ieee80211_channel *chan, s8 *tp);

अटल अंतरभूत s8 s6_to_s8(u32 val)
अणु
	s8 ret = val & GENMASK(5, 0);

	अगर (ret & BIT(5))
		ret -= BIT(6);
	वापस ret;
पूर्ण

अटल अंतरभूत bool mt76x0_tssi_enabled(काष्ठा mt76x02_dev *dev)
अणु
	वापस (mt76x02_eeprom_get(dev, MT_EE_NIC_CONF_1) &
		MT_EE_NIC_CONF_1_TX_ALC_EN);
पूर्ण

#पूर्ण_अगर
