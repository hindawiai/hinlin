<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 * Copyright (C) 2018 Stanislaw Gruszka <stf_xl@wp.pl>
 */

#अगर_अघोषित MT76X0U_H
#घोषणा MT76X0U_H

#समावेश <linux/bitfield.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/usb.h>
#समावेश <linux/completion.h>
#समावेश <net/mac80211.h>
#समावेश <linux/debugfs.h>

#समावेश "../mt76x02.h"
#समावेश "eeprom.h"

#घोषणा MT7610E_FIRMWARE		"mediatek/mt7610e.bin"
#घोषणा MT7650E_FIRMWARE		"mediatek/mt7650e.bin"

#घोषणा MT7610U_FIRMWARE		"mediatek/mt7610u.bin"

#घोषणा MT_USB_AGGR_SIZE_LIMIT		21 /* * 1024B */
#घोषणा MT_USB_AGGR_TIMEOUT		0x80 /* * 33ns */

अटल अंतरभूत bool is_mt7610e(काष्ठा mt76x02_dev *dev)
अणु
	अगर (!mt76_is_mmio(&dev->mt76))
		वापस false;

	वापस mt76_chip(&dev->mt76) == 0x7610;
पूर्ण

अटल अंतरभूत bool is_mt7630(काष्ठा mt76x02_dev *dev)
अणु
	वापस mt76_chip(&dev->mt76) == 0x7630;
पूर्ण

/* Init */
पूर्णांक mt76x0_init_hardware(काष्ठा mt76x02_dev *dev);
पूर्णांक mt76x0_रेजिस्टर_device(काष्ठा mt76x02_dev *dev);
व्योम mt76x0_chip_onoff(काष्ठा mt76x02_dev *dev, bool enable, bool reset);

व्योम mt76x0_mac_stop(काष्ठा mt76x02_dev *dev);

पूर्णांक mt76x0_config(काष्ठा ieee80211_hw *hw, u32 changed);

/* PHY */
व्योम mt76x0_phy_init(काष्ठा mt76x02_dev *dev);
पूर्णांक mt76x0_phy_रुको_bbp_पढ़ोy(काष्ठा mt76x02_dev *dev);
व्योम mt76x0_phy_set_channel(काष्ठा mt76x02_dev *dev,
			    काष्ठा cfg80211_chan_def *chandef);
व्योम mt76x0_phy_set_txघातer(काष्ठा mt76x02_dev *dev);
व्योम mt76x0_phy_calibrate(काष्ठा mt76x02_dev *dev, bool घातer_on);
#पूर्ण_अगर
