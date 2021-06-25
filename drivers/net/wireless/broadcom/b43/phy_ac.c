<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Broadcom B43 wireless driver
 * IEEE 802.11ac AC-PHY support
 *
 * Copyright (c) 2015 Rafaध Miधecki <zajec5@gmail.com>
 */

#समावेश "b43.h"
#समावेश "phy_ac.h"

/**************************************************
 * Basic PHY ops
 **************************************************/

अटल पूर्णांक b43_phy_ac_op_allocate(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_ac *phy_ac;

	phy_ac = kzalloc(माप(*phy_ac), GFP_KERNEL);
	अगर (!phy_ac)
		वापस -ENOMEM;
	dev->phy.ac = phy_ac;

	वापस 0;
पूर्ण

अटल व्योम b43_phy_ac_op_मुक्त(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_ac *phy_ac = phy->ac;

	kमुक्त(phy_ac);
	phy->ac = शून्य;
पूर्ण

अटल व्योम b43_phy_ac_op_maskset(काष्ठा b43_wldev *dev, u16 reg, u16 mask,
				  u16 set)
अणु
	b43_ग_लिखो16f(dev, B43_MMIO_PHY_CONTROL, reg);
	b43_ग_लिखो16(dev, B43_MMIO_PHY_DATA,
		    (b43_पढ़ो16(dev, B43_MMIO_PHY_DATA) & mask) | set);
पूर्ण

अटल u16 b43_phy_ac_op_radio_पढ़ो(काष्ठा b43_wldev *dev, u16 reg)
अणु
	b43_ग_लिखो16f(dev, B43_MMIO_RADIO24_CONTROL, reg);
	वापस b43_पढ़ो16(dev, B43_MMIO_RADIO24_DATA);
पूर्ण

अटल व्योम b43_phy_ac_op_radio_ग_लिखो(काष्ठा b43_wldev *dev, u16 reg,
				      u16 value)
अणु
	b43_ग_लिखो16f(dev, B43_MMIO_RADIO24_CONTROL, reg);
	b43_ग_लिखो16(dev, B43_MMIO_RADIO24_DATA, value);
पूर्ण

अटल अचिन्हित पूर्णांक b43_phy_ac_op_get_शेष_chan(काष्ठा b43_wldev *dev)
अणु
	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
		वापस 11;
	वापस 36;
पूर्ण

अटल क्रमागत b43_txpwr_result
b43_phy_ac_op_recalc_txघातer(काष्ठा b43_wldev *dev, bool ignore_tssi)
अणु
	वापस B43_TXPWR_RES_DONE;
पूर्ण

अटल व्योम b43_phy_ac_op_adjust_txघातer(काष्ठा b43_wldev *dev)
अणु
पूर्ण

/**************************************************
 * PHY ops काष्ठा
 **************************************************/

स्थिर काष्ठा b43_phy_operations b43_phyops_ac = अणु
	.allocate		= b43_phy_ac_op_allocate,
	.मुक्त			= b43_phy_ac_op_मुक्त,
	.phy_maskset		= b43_phy_ac_op_maskset,
	.radio_पढ़ो		= b43_phy_ac_op_radio_पढ़ो,
	.radio_ग_लिखो		= b43_phy_ac_op_radio_ग_लिखो,
	.get_शेष_chan	= b43_phy_ac_op_get_शेष_chan,
	.recalc_txघातer		= b43_phy_ac_op_recalc_txघातer,
	.adjust_txघातer		= b43_phy_ac_op_adjust_txघातer,
पूर्ण;
