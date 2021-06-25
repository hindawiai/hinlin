<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Radio tuning क्रम Maxim max2820 on RTL8180
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
#समावेश "max2820.h"

अटल स्थिर u32 max2820_chan[] = अणु
	12, /* CH 1 */
	17,
	22,
	27,
	32,
	37,
	42,
	47,
	52,
	57,
	62,
	67,
	72,
	84, /* CH 14 */
पूर्ण;

अटल व्योम ग_लिखो_max2820(काष्ठा ieee80211_hw *dev, u8 addr, u32 data)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	u32 phy_config;

	phy_config = 0x90 + (data & 0xf);
	phy_config <<= 16;
	phy_config += addr;
	phy_config <<= 8;
	phy_config += (data >> 4) & 0xff;

	rtl818x_ioग_लिखो32(priv,
		(__le32 __iomem *) &priv->map->RFPinsOutput, phy_config);

	msleep(1);
पूर्ण

अटल व्योम max2820_ग_लिखो_phy_antenna(काष्ठा ieee80211_hw *dev, लघु chan)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	u8 ant;

	ant = MAXIM_ANTENNA;
	अगर (priv->rfparam & RF_PARAM_ANTBDEFAULT)
		ant |= BB_ANTENNA_B;
	अगर (chan == 14)
		ant |= BB_ANTATTEN_CHAN14;

	rtl8180_ग_लिखो_phy(dev, 0x10, ant);
पूर्ण

अटल u8 max2820_rf_calc_rssi(u8 agc, u8 sq)
अणु
	bool odd;

	odd = !!(agc & 1);

	agc >>= 1;
	अगर (odd)
		agc += 76;
	अन्यथा
		agc += 66;

	/* TODO: change addends above to aव्योम mult / भाग below */
	वापस 65 * agc / 100;
पूर्ण

अटल व्योम max2820_rf_set_channel(काष्ठा ieee80211_hw *dev,
				   काष्ठा ieee80211_conf *conf)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	पूर्णांक channel = conf ?
		ieee80211_frequency_to_channel(conf->chandef.chan->center_freq) : 1;
	अचिन्हित पूर्णांक chan_idx = channel - 1;
	u32 txpw = priv->channels[chan_idx].hw_value & 0xFF;
	u32 chan = max2820_chan[chan_idx];

	/* While philips SA2400 drive the PA bias from
	 * sa2400, क्रम MAXIM we करो this directly from BB */
	rtl8180_ग_लिखो_phy(dev, 3, txpw);

	max2820_ग_लिखो_phy_antenna(dev, channel);
	ग_लिखो_max2820(dev, 3, chan);
पूर्ण

अटल व्योम max2820_rf_stop(काष्ठा ieee80211_hw *dev)
अणु
	rtl8180_ग_लिखो_phy(dev, 3, 0x8);
	ग_लिखो_max2820(dev, 1, 0);
पूर्ण


अटल व्योम max2820_rf_init(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;

	/* MAXIM from netbsd driver */
	ग_लिखो_max2820(dev, 0, 0x007); /* test mode as indicated in datasheet */
	ग_लिखो_max2820(dev, 1, 0x01e); /* enable रेजिस्टर */
	ग_लिखो_max2820(dev, 2, 0x001); /* synt रेजिस्टर */

	max2820_rf_set_channel(dev, शून्य);

	ग_लिखो_max2820(dev, 4, 0x313); /* rx रेजिस्टर */

	/* PA is driven directly by the BB, we keep the MAXIM bias
	 * at the highest value in हाल that setting it to lower
	 * values may पूर्णांकroduce some further attenuation somewhere..
	 */
	ग_लिखो_max2820(dev, 5, 0x00f);

	/* baseband configuration */
	rtl8180_ग_लिखो_phy(dev, 0, 0x88); /* sys1       */
	rtl8180_ग_लिखो_phy(dev, 3, 0x08); /* txagc      */
	rtl8180_ग_लिखो_phy(dev, 4, 0xf8); /* lnadet     */
	rtl8180_ग_लिखो_phy(dev, 5, 0x90); /* अगरagcinit  */
	rtl8180_ग_लिखो_phy(dev, 6, 0x1a); /* अगरagclimit */
	rtl8180_ग_लिखो_phy(dev, 7, 0x64); /* अगरagcdet   */

	max2820_ग_लिखो_phy_antenna(dev, 1);

	rtl8180_ग_लिखो_phy(dev, 0x11, 0x88); /* trl */

	अगर (rtl818x_ioपढ़ो8(priv, &priv->map->CONFIG2) &
	    RTL818X_CONFIG2_ANTENNA_DIV)
		rtl8180_ग_लिखो_phy(dev, 0x12, 0xc7);
	अन्यथा
		rtl8180_ग_लिखो_phy(dev, 0x12, 0x47);

	rtl8180_ग_लिखो_phy(dev, 0x13, 0x9b);

	rtl8180_ग_लिखो_phy(dev, 0x19, 0x0);  /* CHESTLIM */
	rtl8180_ग_लिखो_phy(dev, 0x1a, 0x9f); /* CHSQLIM  */

	max2820_rf_set_channel(dev, शून्य);
पूर्ण

स्थिर काष्ठा rtl818x_rf_ops max2820_rf_ops = अणु
	.name		= "Maxim",
	.init		= max2820_rf_init,
	.stop		= max2820_rf_stop,
	.set_chan	= max2820_rf_set_channel,
	.calc_rssi	= max2820_rf_calc_rssi,
पूर्ण;
