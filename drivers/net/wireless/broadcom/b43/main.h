<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*

  Broadcom B43 wireless driver

  Copyright (c) 2005 Martin Langer <martin-langer@gmx.de>,
                     Stefano Brivio <stefano.brivio@polimi.it>
                     Michael Buesch <m@bues.ch>
                     Danny van Dyk <kugelfang@gentoo.org>
                     Andreas Jaggi <andreas.jaggi@waterwave.ch>

  Some parts of the code in this file are derived from the ipw2200
  driver  Copyright(c) 2003 - 2004 Intel Corporation.


*/

#अगर_अघोषित B43_MAIN_H_
#घोषणा B43_MAIN_H_

#समावेश "b43.h"

#घोषणा P4D_BYT3S(magic, nr_bytes)	u8 __p4dding##magic[nr_bytes]
#घोषणा P4D_BYTES(line, nr_bytes)	P4D_BYT3S(line, nr_bytes)
/* Magic helper macro to pad काष्ठाures. Ignore those above. It's magic. */
#घोषणा PAD_BYTES(nr_bytes)		P4D_BYTES( __LINE__ , (nr_bytes))


बाह्य पूर्णांक b43_modparam_verbose;

/* Logmessage verbosity levels. Update the b43_modparam_verbose helptext, अगर
 * you add or हटाओ levels. */
क्रमागत b43_verbosity अणु
	B43_VERBOSITY_ERROR,
	B43_VERBOSITY_WARN,
	B43_VERBOSITY_INFO,
	B43_VERBOSITY_DEBUG,
	__B43_VERBOSITY_AFTERLAST, /* keep last */

	B43_VERBOSITY_MAX = __B43_VERBOSITY_AFTERLAST - 1,
#अगर B43_DEBUG
	B43_VERBOSITY_DEFAULT = B43_VERBOSITY_DEBUG,
#अन्यथा
	B43_VERBOSITY_DEFAULT = B43_VERBOSITY_INFO,
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत पूर्णांक b43_is_cck_rate(पूर्णांक rate)
अणु
	वापस (rate == B43_CCK_RATE_1MB ||
		rate == B43_CCK_RATE_2MB ||
		rate == B43_CCK_RATE_5MB || rate == B43_CCK_RATE_11MB);
पूर्ण

अटल अंतरभूत पूर्णांक b43_is_ofdm_rate(पूर्णांक rate)
अणु
	वापस !b43_is_cck_rate(rate);
पूर्ण

u8 b43_ieee80211_antenna_sanitize(काष्ठा b43_wldev *dev,
				  u8 antenna_nr);

व्योम b43_tsf_पढ़ो(काष्ठा b43_wldev *dev, u64 * tsf);
व्योम b43_tsf_ग_लिखो(काष्ठा b43_wldev *dev, u64 tsf);

u32 b43_shm_पढ़ो32(काष्ठा b43_wldev *dev, u16 routing, u16 offset);
u16 b43_shm_पढ़ो16(काष्ठा b43_wldev *dev, u16 routing, u16 offset);
व्योम b43_shm_ग_लिखो32(काष्ठा b43_wldev *dev, u16 routing, u16 offset, u32 value);
व्योम b43_shm_ग_लिखो16(काष्ठा b43_wldev *dev, u16 routing, u16 offset, u16 value);

u64 b43_hf_पढ़ो(काष्ठा b43_wldev *dev);
व्योम b43_hf_ग_लिखो(काष्ठा b43_wldev *dev, u64 value);

व्योम b43_dummy_transmission(काष्ठा b43_wldev *dev, bool ofdm, bool pa_on);

व्योम b43_wireless_core_reset(काष्ठा b43_wldev *dev, bool gmode);

व्योम b43_controller_restart(काष्ठा b43_wldev *dev, स्थिर अक्षर *reason);

#घोषणा B43_PS_ENABLED	(1 << 0)	/* Force enable hardware घातer saving */
#घोषणा B43_PS_DISABLED	(1 << 1)	/* Force disable hardware घातer saving */
#घोषणा B43_PS_AWAKE	(1 << 2)	/* Force device awake */
#घोषणा B43_PS_ASLEEP	(1 << 3)	/* Force device asleep */
व्योम b43_घातer_saving_ctl_bits(काष्ठा b43_wldev *dev, अचिन्हित पूर्णांक ps_flags);

व्योम b43_wireless_core_phy_pll_reset(काष्ठा b43_wldev *dev);

व्योम b43_mac_suspend(काष्ठा b43_wldev *dev);
व्योम b43_mac_enable(काष्ठा b43_wldev *dev);
व्योम b43_mac_phy_घड़ी_set(काष्ठा b43_wldev *dev, bool on);
व्योम b43_mac_चयन_freq(काष्ठा b43_wldev *dev, u8 spurmode);


काष्ठा b43_request_fw_context;
पूर्णांक b43_करो_request_fw(काष्ठा b43_request_fw_context *ctx, स्थिर अक्षर *name,
		      काष्ठा b43_firmware_file *fw, bool async);
व्योम b43_करो_release_fw(काष्ठा b43_firmware_file *fw);

#पूर्ण_अगर /* B43_MAIN_H_ */
