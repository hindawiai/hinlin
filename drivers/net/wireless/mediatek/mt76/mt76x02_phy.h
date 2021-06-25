<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#अगर_अघोषित __MT76x02_PHY_H
#घोषणा __MT76x02_PHY_H

#समावेश "mt76x02_regs.h"

अटल अंतरभूत पूर्णांक
mt76x02_get_rssi_gain_thresh(काष्ठा mt76x02_dev *dev)
अणु
	चयन (dev->mphy.chandef.width) अणु
	हाल NL80211_CHAN_WIDTH_80:
		वापस -62;
	हाल NL80211_CHAN_WIDTH_40:
		वापस -65;
	शेष:
		वापस -68;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक
mt76x02_get_low_rssi_gain_thresh(काष्ठा mt76x02_dev *dev)
अणु
	चयन (dev->mphy.chandef.width) अणु
	हाल NL80211_CHAN_WIDTH_80:
		वापस -76;
	हाल NL80211_CHAN_WIDTH_40:
		वापस -79;
	शेष:
		वापस -82;
	पूर्ण
पूर्ण

व्योम mt76x02_add_rate_घातer_offset(काष्ठा mt76_rate_घातer *r, पूर्णांक offset);
व्योम mt76x02_phy_set_txघातer(काष्ठा mt76x02_dev *dev, पूर्णांक txp_0, पूर्णांक txp_2);
व्योम mt76x02_limit_rate_घातer(काष्ठा mt76_rate_घातer *r, पूर्णांक limit);
पूर्णांक mt76x02_get_max_rate_घातer(काष्ठा mt76_rate_घातer *r);
व्योम mt76x02_phy_set_rxpath(काष्ठा mt76x02_dev *dev);
व्योम mt76x02_phy_set_txdac(काष्ठा mt76x02_dev *dev);
व्योम mt76x02_phy_set_bw(काष्ठा mt76x02_dev *dev, पूर्णांक width, u8 ctrl);
व्योम mt76x02_phy_set_band(काष्ठा mt76x02_dev *dev, पूर्णांक band,
			  bool primary_upper);
bool mt76x02_phy_adjust_vga_gain(काष्ठा mt76x02_dev *dev);
व्योम mt76x02_init_agc_gain(काष्ठा mt76x02_dev *dev);

#पूर्ण_अगर /* __MT76x02_PHY_H */
