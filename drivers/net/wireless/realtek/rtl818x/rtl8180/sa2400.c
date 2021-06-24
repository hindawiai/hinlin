<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 * Radio tuning क्रम Philips SA2400 on RTL8180
 *
 * Copyright 2007 Andrea Merello <andrea.merello@gmail.com>
 *
 * Code from the BSD driver and the rtl8181 project have been
 * very useful to understand certain things
 *
 * I want to thanks the Authors of such projects and the Ndiswrapper
 * project Authors.
 *
 * A special Big Thanks also is क्रम all people who करोnated me cards,
 * making possible the creation of the original rtl8180 driver
 * from which this code is derived!
 */

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <net/mac80211.h>

#समावेश "rtl8180.h"
#समावेश "sa2400.h"

अटल स्थिर u32 sa2400_chan[] = अणु
	0x00096c, /* ch1 */
	0x080970,
	0x100974,
	0x180978,
	0x000980,
	0x080984,
	0x100988,
	0x18098c,
	0x000994,
	0x080998,
	0x10099c,
	0x1809a0,
	0x0009a8,
	0x0009b4, /* ch 14 */
पूर्ण;

अटल व्योम ग_लिखो_sa2400(काष्ठा ieee80211_hw *dev, u8 addr, u32 data)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	u32 phy_config;

	/* MAC will bang bits to the sa2400. sw 3-wire is NOT used */
	phy_config = 0xb0000000;

	phy_config |= ((u32)(addr & 0xf)) << 24;
	phy_config |= data & 0xffffff;

	rtl818x_ioग_लिखो32(priv,
		(__le32 __iomem *) &priv->map->RFPinsOutput, phy_config);

	msleep(3);
पूर्ण

अटल व्योम sa2400_ग_लिखो_phy_antenna(काष्ठा ieee80211_hw *dev, लघु chan)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	u8 ant = SA2400_ANTENNA;

	अगर (priv->rfparam & RF_PARAM_ANTBDEFAULT)
		ant |= BB_ANTENNA_B;

	अगर (chan == 14)
		ant |= BB_ANTATTEN_CHAN14;

	rtl8180_ग_लिखो_phy(dev, 0x10, ant);

पूर्ण

अटल u8 sa2400_rf_rssi_map[] = अणु
	0x64, 0x64, 0x63, 0x62, 0x61, 0x60, 0x5f, 0x5e,
	0x5d, 0x5c, 0x5b, 0x5a, 0x57, 0x54, 0x52, 0x50,
	0x4e, 0x4c, 0x4a, 0x48, 0x46, 0x44, 0x41, 0x3f,
	0x3c, 0x3a, 0x37, 0x36, 0x36, 0x1c, 0x1c, 0x1b,
	0x1b, 0x1a, 0x1a, 0x19, 0x19, 0x18, 0x18, 0x17,
	0x17, 0x16, 0x16, 0x15, 0x15, 0x14, 0x14, 0x13,
	0x13, 0x12, 0x12, 0x11, 0x11, 0x10, 0x10, 0x0f,
	0x0f, 0x0e, 0x0e, 0x0d, 0x0d, 0x0c, 0x0c, 0x0b,
	0x0b, 0x0a, 0x0a, 0x09, 0x09, 0x08, 0x08, 0x07,
	0x07, 0x06, 0x06, 0x05, 0x04, 0x03, 0x02,
पूर्ण;

अटल u8 sa2400_rf_calc_rssi(u8 agc, u8 sq)
अणु
	अगर (sq == 0x80)
		वापस 1;

	अगर (sq > 78)
		वापस 32;

	/* TODO: recalc sa2400_rf_rssi_map to aव्योम mult / भाग */
	वापस 65 * sa2400_rf_rssi_map[sq] / 100;
पूर्ण

अटल व्योम sa2400_rf_set_channel(काष्ठा ieee80211_hw *dev,
				  काष्ठा ieee80211_conf *conf)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	पूर्णांक channel =
		ieee80211_frequency_to_channel(conf->chandef.chan->center_freq);
	u32 txpw = priv->channels[channel - 1].hw_value & 0xFF;
	u32 chan = sa2400_chan[channel - 1];

	ग_लिखो_sa2400(dev, 7, txpw);

	sa2400_ग_लिखो_phy_antenna(dev, channel);

	ग_लिखो_sa2400(dev, 0, chan);
	ग_लिखो_sa2400(dev, 1, 0xbb50);
	ग_लिखो_sa2400(dev, 2, 0x80);
	ग_लिखो_sa2400(dev, 3, 0);
पूर्ण

अटल व्योम sa2400_rf_stop(काष्ठा ieee80211_hw *dev)
अणु
	ग_लिखो_sa2400(dev, 4, 0);
पूर्ण

अटल व्योम sa2400_rf_init(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	u32 anaparam, txconf;
	u8 firdac;
	पूर्णांक analogphy = priv->rfparam & RF_PARAM_ANALOGPHY;

	anaparam = priv->anaparam;
	anaparam &= ~(1 << ANAPARAM_TXDACOFF_SHIFT);
	anaparam &= ~ANAPARAM_PWR1_MASK;
	anaparam &= ~ANAPARAM_PWR0_MASK;

	अगर (analogphy) अणु
		anaparam |= SA2400_ANA_ANAPARAM_PWR1_ON << ANAPARAM_PWR1_SHIFT;
		firdac = 0;
	पूर्ण अन्यथा अणु
		anaparam |= (SA2400_DIG_ANAPARAM_PWR1_ON << ANAPARAM_PWR1_SHIFT);
		anaparam |= (SA2400_ANAPARAM_PWR0_ON << ANAPARAM_PWR0_SHIFT);
		firdac = 1 << SA2400_REG4_FIRDAC_SHIFT;
	पूर्ण

	rtl8180_set_anaparam(priv, anaparam);

	ग_लिखो_sa2400(dev, 0, sa2400_chan[0]);
	ग_लिखो_sa2400(dev, 1, 0xbb50);
	ग_लिखो_sa2400(dev, 2, 0x80);
	ग_लिखो_sa2400(dev, 3, 0);
	ग_लिखो_sa2400(dev, 4, 0x19340 | firdac);
	ग_लिखो_sa2400(dev, 5, 0x1dfb | (SA2400_MAX_SENS - 54) << 15);
	ग_लिखो_sa2400(dev, 4, 0x19348 | firdac); /* calibrate VCO */

	अगर (!analogphy)
		ग_लिखो_sa2400(dev, 4, 0x1938c); /*???*/

	ग_लिखो_sa2400(dev, 4, 0x19340 | firdac);

	ग_लिखो_sa2400(dev, 0, sa2400_chan[0]);
	ग_लिखो_sa2400(dev, 1, 0xbb50);
	ग_लिखो_sa2400(dev, 2, 0x80);
	ग_लिखो_sa2400(dev, 3, 0);
	ग_लिखो_sa2400(dev, 4, 0x19344 | firdac); /* calibrate filter */

	/* new from rtl8180 embedded driver (rtl8181 project) */
	ग_लिखो_sa2400(dev, 6, 0x13ff | (1 << 23)); /* MANRX */
	ग_लिखो_sa2400(dev, 8, 0); /* VCO */

	अगर (analogphy) अणु
		rtl8180_set_anaparam(priv, anaparam |
				     (1 << ANAPARAM_TXDACOFF_SHIFT));

		txconf = rtl818x_ioपढ़ो32(priv, &priv->map->TX_CONF);
		rtl818x_ioग_लिखो32(priv, &priv->map->TX_CONF,
			txconf | RTL818X_TX_CONF_LOOPBACK_CONT);

		ग_लिखो_sa2400(dev, 4, 0x19341); /* calibrates DC */

		/* a 5us sleep is required here,
		 * we rely on the 3ms delay पूर्णांकroduced in ग_लिखो_sa2400 */
		ग_लिखो_sa2400(dev, 4, 0x19345);

		/* a 20us sleep is required here,
		 * we rely on the 3ms delay पूर्णांकroduced in ग_लिखो_sa2400 */

		rtl818x_ioग_लिखो32(priv, &priv->map->TX_CONF, txconf);

		rtl8180_set_anaparam(priv, anaparam);
	पूर्ण
	/* end new code */

	ग_लिखो_sa2400(dev, 4, 0x19341 | firdac); /* RTX MODE */

	/* baseband configuration */
	rtl8180_ग_लिखो_phy(dev, 0, 0x98);
	rtl8180_ग_लिखो_phy(dev, 3, 0x38);
	rtl8180_ग_लिखो_phy(dev, 4, 0xe0);
	rtl8180_ग_लिखो_phy(dev, 5, 0x90);
	rtl8180_ग_लिखो_phy(dev, 6, 0x1a);
	rtl8180_ग_लिखो_phy(dev, 7, 0x64);

	sa2400_ग_लिखो_phy_antenna(dev, 1);

	rtl8180_ग_लिखो_phy(dev, 0x11, 0x80);

	अगर (rtl818x_ioपढ़ो8(priv, &priv->map->CONFIG2) &
	    RTL818X_CONFIG2_ANTENNA_DIV)
		rtl8180_ग_लिखो_phy(dev, 0x12, 0xc7); /* enable ant भागersity */
	अन्यथा
		rtl8180_ग_लिखो_phy(dev, 0x12, 0x47); /* disable ant भागersity */

	rtl8180_ग_लिखो_phy(dev, 0x13, 0x90 | priv->csthreshold);

	rtl8180_ग_लिखो_phy(dev, 0x19, 0x0);
	rtl8180_ग_लिखो_phy(dev, 0x1a, 0xa0);
पूर्ण

स्थिर काष्ठा rtl818x_rf_ops sa2400_rf_ops = अणु
	.name		= "Philips",
	.init		= sa2400_rf_init,
	.stop		= sa2400_rf_stop,
	.set_chan	= sa2400_rf_set_channel,
	.calc_rssi	= sa2400_rf_calc_rssi,
पूर्ण;
