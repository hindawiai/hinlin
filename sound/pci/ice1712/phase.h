<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_PHASE_H
#घोषणा __SOUND_PHASE_H

/*
 *   ALSA driver क्रम ICEnsemble ICE1712 (Envy24)
 *
 *   Lowlevel functions क्रम Terratec PHASE 22
 *
 *	Copyright (c) 2005 Misha Zhilin <misha@epiphan.com>
 */

#घोषणा PHASE_DEVICE_DESC	"{Terratec,Phase 22},"\
				"{Terratec,Phase 28},"\
				"{Terrasoniq,TS22},"

#घोषणा VT1724_SUBDEVICE_PHASE22	0x3b155011
#घोषणा VT1724_SUBDEVICE_PHASE28	0x3b154911
#घोषणा VT1724_SUBDEVICE_TS22		0x3b157b11

/* entry poपूर्णांक */
बाह्य काष्ठा snd_ice1712_card_info snd_vt1724_phase_cards[];

/* PHASE28 GPIO bits */
#घोषणा PHASE28_SPI_MISO	(1 << 21)
#घोषणा PHASE28_WM_RESET	(1 << 20)
#घोषणा PHASE28_SPI_CLK		(1 << 19)
#घोषणा PHASE28_SPI_MOSI	(1 << 18)
#घोषणा PHASE28_WM_RW		(1 << 17)
#घोषणा PHASE28_AC97_RESET	(1 << 16)
#घोषणा PHASE28_DIGITAL_SEL1	(1 << 15)
#घोषणा PHASE28_HP_SEL		(1 << 14)
#घोषणा PHASE28_WM_CS		(1 << 12)
#घोषणा PHASE28_AC97_COMMIT	(1 << 11)
#घोषणा PHASE28_AC97_ADDR	(1 << 10)
#घोषणा PHASE28_AC97_DATA_LOW	(1 << 9)
#घोषणा PHASE28_AC97_DATA_HIGH	(1 << 8)
#घोषणा PHASE28_AC97_DATA_MASK	0xFF
#पूर्ण_अगर /* __SOUND_PHASE */
