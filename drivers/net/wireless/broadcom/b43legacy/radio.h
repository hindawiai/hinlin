<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*

  Broadcom B43legacy wireless driver

  Copyright (c) 2005 Martin Langer <martin-langer@gmx.de>,
		     Stefano Brivio <stefano.brivio@polimi.it>
		     Michael Buesch <m@bues.ch>
		     Danny van Dyk <kugelfang@gentoo.org>
		     Andreas Jaggi <andreas.jaggi@waterwave.ch>

  Some parts of the code in this file are derived from the ipw2200
  driver  Copyright(c) 2003 - 2004 Intel Corporation.


*/

#अगर_अघोषित B43legacy_RADIO_H_
#घोषणा B43legacy_RADIO_H_

#समावेश "b43legacy.h"


#घोषणा B43legacy_RADIO_DEFAULT_CHANNEL_BG	6

/* Force antenna 0. */
#घोषणा B43legacy_RADIO_TXANTENNA_0		0
/* Force antenna 1. */
#घोषणा B43legacy_RADIO_TXANTENNA_1		1
/* Use the RX antenna, that was selected क्रम the most recently
 * received good PLCP header.
 */
#घोषणा B43legacy_RADIO_TXANTENNA_LASTPLCP	3
#घोषणा B43legacy_RADIO_TXANTENNA_DEFAULT	B43legacy_RADIO_TXANTENNA_LASTPLCP

#घोषणा B43legacy_RADIO_INTERFMODE_NONE		0
#घोषणा B43legacy_RADIO_INTERFMODE_NONWLAN	1
#घोषणा B43legacy_RADIO_INTERFMODE_MANUALWLAN	2
#घोषणा B43legacy_RADIO_INTERFMODE_AUTOWLAN	3


व्योम b43legacy_radio_lock(काष्ठा b43legacy_wldev *dev);
व्योम b43legacy_radio_unlock(काष्ठा b43legacy_wldev *dev);

u16 b43legacy_radio_पढ़ो16(काष्ठा b43legacy_wldev *dev, u16 offset);
व्योम b43legacy_radio_ग_लिखो16(काष्ठा b43legacy_wldev *dev, u16 offset, u16 val);

u16 b43legacy_radio_init2050(काष्ठा b43legacy_wldev *dev);

व्योम b43legacy_radio_turn_on(काष्ठा b43legacy_wldev *dev);
व्योम b43legacy_radio_turn_off(काष्ठा b43legacy_wldev *dev, bool क्रमce);

पूर्णांक b43legacy_radio_selectchannel(काष्ठा b43legacy_wldev *dev, u8 channel,
				  पूर्णांक synthetic_pu_workaround);

व्योम b43legacy_radio_set_txघातer_a(काष्ठा b43legacy_wldev *dev, u16 txघातer);
व्योम b43legacy_radio_set_txघातer_bg(काष्ठा b43legacy_wldev *dev,
				    u16 baseband_attenuation, u16 attenuation,
				    u16 txघातer);

u16 b43legacy_शेष_baseband_attenuation(काष्ठा b43legacy_wldev *dev);
u16 b43legacy_शेष_radio_attenuation(काष्ठा b43legacy_wldev *dev);
u16 b43legacy_शेष_txctl1(काष्ठा b43legacy_wldev *dev);

व्योम b43legacy_radio_set_txantenna(काष्ठा b43legacy_wldev *dev, u32 val);

व्योम b43legacy_radio_clear_tssi(काष्ठा b43legacy_wldev *dev);

u8 b43legacy_radio_aci_detect(काष्ठा b43legacy_wldev *dev, u8 channel);
u8 b43legacy_radio_aci_scan(काष्ठा b43legacy_wldev *dev);

पूर्णांक b43legacy_radio_set_पूर्णांकerference_mitigation(काष्ठा b43legacy_wldev *dev,
						पूर्णांक mode);

व्योम b43legacy_calc_nrssi_slope(काष्ठा b43legacy_wldev *dev);
व्योम b43legacy_calc_nrssi_threshold(काष्ठा b43legacy_wldev *dev);
s16 b43legacy_nrssi_hw_पढ़ो(काष्ठा b43legacy_wldev *dev, u16 offset);
व्योम b43legacy_nrssi_hw_ग_लिखो(काष्ठा b43legacy_wldev *dev, u16 offset, s16 val);
व्योम b43legacy_nrssi_hw_update(काष्ठा b43legacy_wldev *dev, u16 val);
व्योम b43legacy_nrssi_mem_update(काष्ठा b43legacy_wldev *dev);

u16 b43legacy_radio_calibrationvalue(काष्ठा b43legacy_wldev *dev);

#पूर्ण_अगर /* B43legacy_RADIO_H_ */
