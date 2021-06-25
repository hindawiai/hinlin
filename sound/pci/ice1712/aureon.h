<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_AUREON_H
#घोषणा __SOUND_AUREON_H

/*
 *   ALSA driver क्रम VIA VT1724 (Envy24HT)
 *
 *   Lowlevel functions क्रम Terratec Aureon cards
 *
 *	Copyright (c) 2003 Takashi Iwai <tiwai@suse.de>
 */      

#घोषणा  AUREON_DEVICE_DESC 	       "{Terratec,Aureon 5.1 Sky},"\
				       "{Terratec,Aureon 7.1 Space},"\
				       "{Terratec,Aureon 7.1 Universe}," \
					"{AudioTrak,Prodigy 7.1}," \
					"{AudioTrak,Prodigy 7.1 LT},"\
					"{AudioTrak,Prodigy 7.1 XT},"

#घोषणा VT1724_SUBDEVICE_AUREON51_SKY	0x3b154711	/* Aureon 5.1 Sky */
#घोषणा VT1724_SUBDEVICE_AUREON71_SPACE	0x3b154511	/* Aureon 7.1 Space */
#घोषणा VT1724_SUBDEVICE_AUREON71_UNIVERSE	0x3b155311	/* Aureon 7.1 Universe */
#घोषणा VT1724_SUBDEVICE_PRODIGY71	0x33495345	/* PRODIGY 7.1 */
#घोषणा VT1724_SUBDEVICE_PRODIGY71LT	0x32315441	/* PRODIGY 7.1 LT */
#घोषणा VT1724_SUBDEVICE_PRODIGY71XT	0x36315441	/* PRODIGY 7.1 XT*/

बाह्य काष्ठा snd_ice1712_card_info  snd_vt1724_aureon_cards[];

/* GPIO bits */
#घोषणा AUREON_CS8415_CS	(1 << 22)
#घोषणा AUREON_SPI_MISO		(1 << 21)
#घोषणा AUREON_WM_RESET		(1 << 20)
#घोषणा AUREON_SPI_CLK		(1 << 19)
#घोषणा AUREON_SPI_MOSI		(1 << 18)
#घोषणा AUREON_WM_RW		(1 << 17)
#घोषणा AUREON_AC97_RESET	(1 << 16)
#घोषणा AUREON_DIGITAL_SEL1	(1 << 15)
#घोषणा AUREON_HP_SEL		(1 << 14)
#घोषणा AUREON_WM_CS		(1 << 12)
#घोषणा AUREON_AC97_COMMIT	(1 << 11)
#घोषणा AUREON_AC97_ADDR	(1 << 10)
#घोषणा AUREON_AC97_DATA_LOW	(1 << 9)
#घोषणा AUREON_AC97_DATA_HIGH	(1 << 8)
#घोषणा AUREON_AC97_DATA_MASK	0xFF

#घोषणा PRODIGY_WM_CS		(1 << 8)
#घोषणा PRODIGY_SPI_MOSI	(1 << 10)
#घोषणा PRODIGY_SPI_CLK		(1 << 9)
#घोषणा PRODIGY_HP_SEL		(1 << 5)

#पूर्ण_अगर /* __SOUND_AUREON_H */
