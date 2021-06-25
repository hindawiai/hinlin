<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/* Copyright (C) 2020 MediaTek Inc. */

#अगर_अघोषित __MT7921_EEPROM_H
#घोषणा __MT7921_EEPROM_H

#समावेश "mt7921.h"

क्रमागत mt7921_eeprom_field अणु
	MT_EE_CHIP_ID =		0x000,
	MT_EE_VERSION =		0x002,
	MT_EE_MAC_ADDR =	0x004,
	MT_EE_WIFI_CONF =	0x07c,
	__MT_EE_MAX =		0x3bf
पूर्ण;

#घोषणा MT_EE_WIFI_CONF_TX_MASK			BIT(0)
#घोषणा MT_EE_WIFI_CONF_BAND_SEL		GENMASK(3, 2)

क्रमागत mt7921_eeprom_band अणु
	MT_EE_NA,
	MT_EE_5GHZ,
	MT_EE_2GHZ,
	MT_EE_DUAL_BAND,
पूर्ण;

#पूर्ण_अगर
