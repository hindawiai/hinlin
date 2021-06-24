<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 * Radio tuning क्रम GCT GRF5101 on RTL8180
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
#समावेश "grf5101.h"

अटल स्थिर पूर्णांक grf5101_encode[] = अणु
	0x0, 0x8, 0x4, 0xC,
	0x2, 0xA, 0x6, 0xE,
	0x1, 0x9, 0x5, 0xD,
	0x3, 0xB, 0x7, 0xF
पूर्ण;

अटल व्योम ग_लिखो_grf5101(काष्ठा ieee80211_hw *dev, u8 addr, u32 data)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	u32 phy_config;

	phy_config =  grf5101_encode[(data >> 8) & 0xF];
	phy_config |= grf5101_encode[(data >> 4) & 0xF] << 4;
	phy_config |= grf5101_encode[data & 0xF] << 8;
	phy_config |= grf5101_encode[(addr >> 1) & 0xF] << 12;
	phy_config |= (addr & 1) << 16;
	phy_config |= grf5101_encode[(data & 0xf000) >> 12] << 24;

	/* MAC will bang bits to the chip */
	phy_config |= 0x90000000;

	rtl818x_ioग_लिखो32(priv,
		(__le32 __iomem *) &priv->map->RFPinsOutput, phy_config);

	msleep(3);
पूर्ण

अटल व्योम grf5101_ग_लिखो_phy_antenna(काष्ठा ieee80211_hw *dev, लघु chan)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	u8 ant = GRF5101_ANTENNA;

	अगर (priv->rfparam & RF_PARAM_ANTBDEFAULT)
		ant |= BB_ANTENNA_B;

	अगर (chan == 14)
		ant |= BB_ANTATTEN_CHAN14;

	rtl8180_ग_लिखो_phy(dev, 0x10, ant);
पूर्ण

अटल u8 grf5101_rf_calc_rssi(u8 agc, u8 sq)
अणु
	अगर (agc > 60)
		वापस 65;

	/* TODO(?): just वापस agc (or agc + 5) to aव्योम mult / भाग */
	वापस 65 * agc / 60;
पूर्ण

अटल व्योम grf5101_rf_set_channel(काष्ठा ieee80211_hw *dev,
				   काष्ठा ieee80211_conf *conf)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	पूर्णांक channel =
		ieee80211_frequency_to_channel(conf->chandef.chan->center_freq);
	u32 txpw = priv->channels[channel - 1].hw_value & 0xFF;
	u32 chan = channel - 1;

	/* set TX घातer */
	ग_लिखो_grf5101(dev, 0x15, 0x0);
	ग_लिखो_grf5101(dev, 0x06, txpw);
	ग_लिखो_grf5101(dev, 0x15, 0x10);
	ग_लिखो_grf5101(dev, 0x15, 0x0);

	/* set frequency */
	ग_लिखो_grf5101(dev, 0x07, 0x0);
	ग_लिखो_grf5101(dev, 0x0B, chan);
	ग_लिखो_grf5101(dev, 0x07, 0x1000);

	grf5101_ग_लिखो_phy_antenna(dev, channel);
पूर्ण

अटल व्योम grf5101_rf_stop(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	u32 anaparam;

	anaparam = priv->anaparam;
	anaparam &= 0x000fffff;
	anaparam |= 0x3f900000;
	rtl8180_set_anaparam(priv, anaparam);

	ग_लिखो_grf5101(dev, 0x07, 0x0);
	ग_लिखो_grf5101(dev, 0x1f, 0x45);
	ग_लिखो_grf5101(dev, 0x1f, 0x5);
	ग_लिखो_grf5101(dev, 0x00, 0x8e4);
पूर्ण

अटल व्योम grf5101_rf_init(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;

	rtl8180_set_anaparam(priv, priv->anaparam);

	ग_लिखो_grf5101(dev, 0x1f, 0x0);
	ग_लिखो_grf5101(dev, 0x1f, 0x0);
	ग_लिखो_grf5101(dev, 0x1f, 0x40);
	ग_लिखो_grf5101(dev, 0x1f, 0x60);
	ग_लिखो_grf5101(dev, 0x1f, 0x61);
	ग_लिखो_grf5101(dev, 0x1f, 0x61);
	ग_लिखो_grf5101(dev, 0x00, 0xae4);
	ग_लिखो_grf5101(dev, 0x1f, 0x1);
	ग_लिखो_grf5101(dev, 0x1f, 0x41);
	ग_लिखो_grf5101(dev, 0x1f, 0x61);

	ग_लिखो_grf5101(dev, 0x01, 0x1a23);
	ग_लिखो_grf5101(dev, 0x02, 0x4971);
	ग_लिखो_grf5101(dev, 0x03, 0x41de);
	ग_लिखो_grf5101(dev, 0x04, 0x2d80);
	ग_लिखो_grf5101(dev, 0x05, 0x68ff);	/* 0x61ff original value */
	ग_लिखो_grf5101(dev, 0x06, 0x0);
	ग_लिखो_grf5101(dev, 0x07, 0x0);
	ग_लिखो_grf5101(dev, 0x08, 0x7533);
	ग_लिखो_grf5101(dev, 0x09, 0xc401);
	ग_लिखो_grf5101(dev, 0x0a, 0x0);
	ग_लिखो_grf5101(dev, 0x0c, 0x1c7);
	ग_लिखो_grf5101(dev, 0x0d, 0x29d3);
	ग_लिखो_grf5101(dev, 0x0e, 0x2e8);
	ग_लिखो_grf5101(dev, 0x10, 0x192);
	ग_लिखो_grf5101(dev, 0x11, 0x248);
	ग_लिखो_grf5101(dev, 0x12, 0x0);
	ग_लिखो_grf5101(dev, 0x13, 0x20c4);
	ग_लिखो_grf5101(dev, 0x14, 0xf4fc);
	ग_लिखो_grf5101(dev, 0x15, 0x0);
	ग_लिखो_grf5101(dev, 0x16, 0x1500);

	ग_लिखो_grf5101(dev, 0x07, 0x1000);

	/* baseband configuration */
	rtl8180_ग_लिखो_phy(dev, 0, 0xa8);
	rtl8180_ग_लिखो_phy(dev, 3, 0x0);
	rtl8180_ग_लिखो_phy(dev, 4, 0xc0);
	rtl8180_ग_लिखो_phy(dev, 5, 0x90);
	rtl8180_ग_लिखो_phy(dev, 6, 0x1e);
	rtl8180_ग_लिखो_phy(dev, 7, 0x64);

	grf5101_ग_लिखो_phy_antenna(dev, 1);

	rtl8180_ग_लिखो_phy(dev, 0x11, 0x88);

	अगर (rtl818x_ioपढ़ो8(priv, &priv->map->CONFIG2) &
	    RTL818X_CONFIG2_ANTENNA_DIV)
		rtl8180_ग_लिखो_phy(dev, 0x12, 0xc0); /* enable ant भागersity */
	अन्यथा
		rtl8180_ग_लिखो_phy(dev, 0x12, 0x40); /* disable ant भागersity */

	rtl8180_ग_लिखो_phy(dev, 0x13, 0x90 | priv->csthreshold);

	rtl8180_ग_लिखो_phy(dev, 0x19, 0x0);
	rtl8180_ग_लिखो_phy(dev, 0x1a, 0xa0);
	rtl8180_ग_लिखो_phy(dev, 0x1b, 0x44);
पूर्ण

स्थिर काष्ठा rtl818x_rf_ops grf5101_rf_ops = अणु
	.name		= "GCT",
	.init		= grf5101_rf_init,
	.stop		= grf5101_rf_stop,
	.set_chan	= grf5101_rf_set_channel,
	.calc_rssi	= grf5101_rf_calc_rssi,
पूर्ण;
