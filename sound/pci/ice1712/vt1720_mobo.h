<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_VT1720_MOBO_H
#घोषणा __SOUND_VT1720_MOBO_H

/*
 *   ALSA driver क्रम VT1720/VT1724 (Envy24PT/Envy24HT)
 *
 *   Lowlevel functions क्रम VT1720-based motherboards
 *
 *	Copyright (c) 2004 Takashi Iwai <tiwai@suse.de>
 */      

#घोषणा VT1720_MOBO_DEVICE_DESC        "{Albatron,K8X800 Pro II},"\
				       "{Chaintech,ZNF3-150},"\
				       "{Chaintech,ZNF3-250},"\
				       "{Chaintech,9CJS},"\
				       "{Shuttle,SN25P},"

#घोषणा VT1720_SUBDEVICE_K8X800		0xf217052c
#घोषणा VT1720_SUBDEVICE_ZNF3_150	0x0f2741f6
#घोषणा VT1720_SUBDEVICE_ZNF3_250	0x0f2745f6
#घोषणा VT1720_SUBDEVICE_9CJS		0x0f272327
#घोषणा VT1720_SUBDEVICE_SN25P		0x97123650

बाह्य काष्ठा snd_ice1712_card_info  snd_vt1720_mobo_cards[];

#पूर्ण_अगर /* __SOUND_VT1720_MOBO_H */
