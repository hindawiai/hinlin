<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*

  Broadcom B43legacy wireless driver

  Copyright (c) 2005 Martin Langer <martin-langer@gmx.de>,
  Copyright (c) 2005 Stefano Brivio <stefano.brivio@polimi.it>
  Copyright (c) 2005, 2006 Michael Buesch <m@bues.ch>
  Copyright (c) 2005  Danny van Dyk <kugelfang@gentoo.org>
  Copyright (c) 2005  Andreas Jaggi <andreas.jaggi@waterwave.ch>
  Copyright (c) 2007  Larry Finger <Larry.Finger@lwfinger.net>

  Some parts of the code in this file are derived from the ipw2200
  driver  Copyright(c) 2003 - 2004 Intel Corporation.


*/

#अगर_अघोषित B43legacy_MAIN_H_
#घोषणा B43legacy_MAIN_H_

#समावेश "b43legacy.h"


#घोषणा P4D_BYT3S(magic, nr_bytes)	u8 __p4dding##magic[nr_bytes]
#घोषणा P4D_BYTES(line, nr_bytes)	P4D_BYT3S(line, nr_bytes)
/* Magic helper macro to pad काष्ठाures. Ignore those above. It's magic. */
#घोषणा PAD_BYTES(nr_bytes)		P4D_BYTES(__LINE__ , (nr_bytes))


/* Lightweight function to convert a frequency (in Mhz) to a channel number. */
अटल अंतरभूत
u8 b43legacy_freq_to_channel_bg(पूर्णांक freq)
अणु
	u8 channel;

	अगर (freq == 2484)
		channel = 14;
	अन्यथा
		channel = (freq - 2407) / 5;

	वापस channel;
पूर्ण
अटल अंतरभूत
u8 b43legacy_freq_to_channel(काष्ठा b43legacy_wldev *dev,
			     पूर्णांक freq)
अणु
	वापस b43legacy_freq_to_channel_bg(freq);
पूर्ण

/* Lightweight function to convert a channel number to a frequency (in Mhz). */
अटल अंतरभूत
पूर्णांक b43legacy_channel_to_freq_bg(u8 channel)
अणु
	पूर्णांक freq;

	अगर (channel == 14)
		freq = 2484;
	अन्यथा
		freq = 2407 + (5 * channel);

	वापस freq;
पूर्ण

अटल अंतरभूत
पूर्णांक b43legacy_channel_to_freq(काष्ठा b43legacy_wldev *dev,
			      u8 channel)
अणु
	वापस b43legacy_channel_to_freq_bg(channel);
पूर्ण

अटल अंतरभूत
पूर्णांक b43legacy_is_cck_rate(पूर्णांक rate)
अणु
	वापस (rate == B43legacy_CCK_RATE_1MB ||
		rate == B43legacy_CCK_RATE_2MB ||
		rate == B43legacy_CCK_RATE_5MB ||
		rate == B43legacy_CCK_RATE_11MB);
पूर्ण

अटल अंतरभूत
पूर्णांक b43legacy_is_ofdm_rate(पूर्णांक rate)
अणु
	वापस !b43legacy_is_cck_rate(rate);
पूर्ण

व्योम b43legacy_tsf_पढ़ो(काष्ठा b43legacy_wldev *dev, u64 *tsf);
व्योम b43legacy_tsf_ग_लिखो(काष्ठा b43legacy_wldev *dev, u64 tsf);

u32 b43legacy_shm_पढ़ो32(काष्ठा b43legacy_wldev *dev,
			 u16 routing, u16 offset);
u16 b43legacy_shm_पढ़ो16(काष्ठा b43legacy_wldev *dev,
			 u16 routing, u16 offset);
व्योम b43legacy_shm_ग_लिखो32(काष्ठा b43legacy_wldev *dev,
			 u16 routing, u16 offset,
			 u32 value);
व्योम b43legacy_shm_ग_लिखो16(काष्ठा b43legacy_wldev *dev,
			 u16 routing, u16 offset,
			 u16 value);

u32 b43legacy_hf_पढ़ो(काष्ठा b43legacy_wldev *dev);
व्योम b43legacy_hf_ग_लिखो(काष्ठा b43legacy_wldev *dev, u32 value);

व्योम b43legacy_dummy_transmission(काष्ठा b43legacy_wldev *dev);

व्योम b43legacy_wireless_core_reset(काष्ठा b43legacy_wldev *dev, u32 flags);

व्योम b43legacy_mac_suspend(काष्ठा b43legacy_wldev *dev);
व्योम b43legacy_mac_enable(काष्ठा b43legacy_wldev *dev);

व्योम b43legacy_controller_restart(काष्ठा b43legacy_wldev *dev,
				  स्थिर अक्षर *reason);

#पूर्ण_अगर /* B43legacy_MAIN_H_ */
