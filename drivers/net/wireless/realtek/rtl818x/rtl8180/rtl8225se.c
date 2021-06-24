<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/* Radio tuning क्रम RTL8225 on RTL8187SE
 *
 * Copyright 2009 Larry Finger <Larry.Finger@lwfinger.net>
 * Copyright 2014 Andrea Merello <andrea.merello@gmail.com>
 *
 * Based on the r8180 and Realtek r8187se drivers, which are:
 * Copyright 2004-2005 Andrea Merello <andrea.merello@gmail.com>, et al.
 *
 * Also based on the rtl8187 driver, which is:
 * Copyright 2007 Michael Wu <flamingice@sourmilk.net>
 * Copyright 2007 Andrea Merello <andrea.merello@gmail.com>
 */

#समावेश <net/mac80211.h>

#समावेश "rtl8180.h"
#समावेश "rtl8225se.h"

#घोषणा PFX "rtl8225 (se) "

अटल स्थिर u32 RF_GAIN_TABLE[] = अणु
	0x0096, 0x0076, 0x0056, 0x0036, 0x0016, 0x01f6, 0x01d6, 0x01b6,
	0x0196, 0x0176, 0x00F7, 0x00D7, 0x00B7, 0x0097, 0x0077, 0x0057,
	0x0037, 0x00FB, 0x00DB, 0x00BB, 0x00FF, 0x00E3, 0x00C3, 0x00A3,
	0x0083, 0x0063, 0x0043, 0x0023, 0x0003, 0x01E3, 0x01C3, 0x01A3,
	0x0183, 0x0163, 0x0143, 0x0123, 0x0103
पूर्ण;

अटल स्थिर u8 cck_ofdm_gain_settings[] = अणु
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
	0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b,
	0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11,
	0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
	0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d,
	0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23,
पूर्ण;

अटल स्थिर u32 rtl8225se_chan[] = अणु
	0x0080, 0x0100, 0x0180, 0x0200, 0x0280, 0x0300, 0x0380,
	0x0400, 0x0480, 0x0500, 0x0580, 0x0600, 0x0680, 0x074A,
पूर्ण;

अटल स्थिर u8 ZEBRA_AGC[] = अणु
	0x7E, 0x7E, 0x7E, 0x7E, 0x7D, 0x7C, 0x7B, 0x7A,
	0x79, 0x78, 0x77, 0x76, 0x75, 0x74, 0x73, 0x72,
	0x71, 0x70, 0x6F, 0x6E, 0x6D, 0x6C, 0x6B, 0x6A,
	0x69, 0x68, 0x67, 0x66, 0x65, 0x64, 0x63, 0x62,
	0x48, 0x47, 0x46, 0x45, 0x44, 0x29, 0x28, 0x27,
	0x26, 0x25, 0x24, 0x23, 0x22, 0x21, 0x08, 0x07,
	0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
	0x0f, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x15, 0x16,
	0x17, 0x17, 0x18, 0x18, 0x19, 0x1a, 0x1a, 0x1b,
	0x1b, 0x1c, 0x1c, 0x1d, 0x1d, 0x1d, 0x1e, 0x1e,
	0x1f, 0x1f, 0x1f, 0x20, 0x20, 0x20, 0x20, 0x21,
	0x21, 0x21, 0x22, 0x22, 0x22, 0x23, 0x23, 0x24,
	0x24, 0x25, 0x25, 0x25, 0x26, 0x26, 0x27, 0x27,
	0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F
पूर्ण;

अटल स्थिर u8 OFDM_CONFIG[] = अणु
	0x10, 0x0F, 0x0A, 0x0C, 0x14, 0xFA, 0xFF, 0x50,
	0x00, 0x50, 0x00, 0x00, 0x00, 0x5C, 0x00, 0x00,
	0x40, 0x00, 0x40, 0x00, 0x00, 0x00, 0xA8, 0x26,
	0x32, 0x33, 0x06, 0xA5, 0x6F, 0x55, 0xC8, 0xBB,
	0x0A, 0xE1, 0x2C, 0x4A, 0x86, 0x83, 0x34, 0x00,
	0x4F, 0x24, 0x6F, 0xC2, 0x03, 0x40, 0x80, 0x00,
	0xC0, 0xC1, 0x58, 0xF1, 0x00, 0xC4, 0x90, 0x3e,
	0xD8, 0x3C, 0x7B, 0x10, 0x10
पूर्ण;

अटल व्योम rtl8187se_three_wire_io(काष्ठा ieee80211_hw *dev, u8 *data,
				    u8 len, bool ग_लिखो)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	पूर्णांक i;
	u8 पंचांगp;

	करो अणु
		क्रम (i = 0; i < 5; i++) अणु
			पंचांगp = rtl818x_ioपढ़ो8(priv, SW_3W_CMD1);
			अगर (!(पंचांगp & 0x3))
				अवरोध;
			udelay(10);
		पूर्ण
		अगर (i == 5)
			wiphy_err(dev->wiphy, PFX
				"CmdReg: 0x%x RE/WE bits aren't clear\n", पंचांगp);

		पंचांगp = rtl818x_ioपढ़ो8(priv, &priv->map->rf_sw_config) | 0x02;
		rtl818x_ioग_लिखो8(priv, &priv->map->rf_sw_config, पंचांगp);

		पंचांगp = rtl818x_ioपढ़ो8(priv, REG_ADDR1(0x84)) & 0xF7;
		rtl818x_ioग_लिखो8(priv, REG_ADDR1(0x84), पंचांगp);
		अगर (ग_लिखो) अणु
			अगर (len == 16) अणु
				rtl818x_ioग_लिखो16(priv, SW_3W_DB0,
				  *(u16 *)data);
			पूर्ण अन्यथा अगर (len == 64) अणु
				rtl818x_ioग_लिखो32(priv, SW_3W_DB0_4,
				  *((u32 *)data));
				rtl818x_ioग_लिखो32(priv, SW_3W_DB1_4,
				  *((u32 *)(data + 4)));
			पूर्ण अन्यथा
				wiphy_err(dev->wiphy, PFX
					"Unimplemented length\n");
		पूर्ण अन्यथा अणु
			rtl818x_ioग_लिखो16(priv, SW_3W_DB0, *(u16 *)data);
		पूर्ण
		अगर (ग_लिखो)
			पंचांगp = 2;
		अन्यथा
			पंचांगp = 1;
		rtl818x_ioग_लिखो8(priv, SW_3W_CMD1, पंचांगp);
		क्रम (i = 0; i < 5; i++) अणु
			पंचांगp = rtl818x_ioपढ़ो8(priv, SW_3W_CMD1);
			अगर (!(पंचांगp & 0x3))
				अवरोध;
			udelay(10);
		पूर्ण
		rtl818x_ioग_लिखो8(priv, SW_3W_CMD1, 0);
		अगर (!ग_लिखो) अणु
			*((u16 *)data) = rtl818x_ioपढ़ो16(priv, SI_DATA_REG);
			*((u16 *)data) &= 0x0FFF;
		पूर्ण
	पूर्ण जबतक (0);
पूर्ण

अटल u32 rtl8187se_rf_पढ़ोreg(काष्ठा ieee80211_hw *dev, u8 addr)
अणु
	u32 dataपढ़ो = addr & 0x0F;
	rtl8187se_three_wire_io(dev, (u8 *)&dataपढ़ो, 16, 0);
	वापस dataपढ़ो;
पूर्ण

अटल व्योम rtl8187se_rf_ग_लिखोreg(काष्ठा ieee80211_hw *dev, u8 addr, u32 data)
अणु
	u32 outdata = (data << 4) | (u32)(addr & 0x0F);
	rtl8187se_three_wire_io(dev, (u8 *)&outdata, 16, 1);
पूर्ण


अटल व्योम rtl8225se_ग_लिखो_zebra_agc(काष्ठा ieee80211_hw *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 128; i++) अणु
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0xF, ZEBRA_AGC[i]);
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0xE, i+0x80);
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0xE, 0);
	पूर्ण
पूर्ण

अटल व्योम rtl8187se_ग_लिखो_ofdm_config(काष्ठा ieee80211_hw *dev)
अणु
	/* ग_लिखो OFDM_CONFIG table */
	पूर्णांक i;

	क्रम (i = 0; i < 60; i++)
		rtl8225se_ग_लिखो_phy_ofdm(dev, i, OFDM_CONFIG[i]);

पूर्ण

अटल व्योम rtl8225sez2_rf_set_tx_घातer(काष्ठा ieee80211_hw *dev, पूर्णांक channel)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	u8 cck_घातer, ofdm_घातer;

	cck_घातer = priv->channels[channel - 1].hw_value & 0xFF;
	अगर (cck_घातer > 35)
		cck_घातer = 35;
	rtl818x_ioग_लिखो8(priv, &priv->map->TX_GAIN_CCK,
			 cck_ofdm_gain_settings[cck_घातer]);

	usleep_range(1000, 5000);
	ofdm_घातer = priv->channels[channel - 1].hw_value >> 8;
	अगर (ofdm_घातer > 35)
		ofdm_घातer = 35;

	rtl818x_ioग_लिखो8(priv, &priv->map->TX_GAIN_OFDM,
			 cck_ofdm_gain_settings[ofdm_घातer]);
	अगर (ofdm_घातer < 12) अणु
		rtl8225se_ग_लिखो_phy_ofdm(dev, 7, 0x5C);
		rtl8225se_ग_लिखो_phy_ofdm(dev, 9, 0x5C);
	पूर्ण
	अगर (ofdm_घातer < 18) अणु
		rtl8225se_ग_लिखो_phy_ofdm(dev, 7, 0x54);
		rtl8225se_ग_लिखो_phy_ofdm(dev, 9, 0x54);
	पूर्ण अन्यथा अणु
		rtl8225se_ग_लिखो_phy_ofdm(dev, 7, 0x50);
		rtl8225se_ग_लिखो_phy_ofdm(dev, 9, 0x50);
	पूर्ण

	usleep_range(1000, 5000);
पूर्ण

अटल व्योम rtl8187se_ग_लिखो_rf_gain(काष्ठा ieee80211_hw *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <= 36; i++) अणु
		rtl8187se_rf_ग_लिखोreg(dev, 0x01, i); mdelay(1);
		rtl8187se_rf_ग_लिखोreg(dev, 0x02, RF_GAIN_TABLE[i]); mdelay(1);
	पूर्ण
पूर्ण

अटल व्योम rtl8187se_ग_लिखो_initial_gain(काष्ठा ieee80211_hw *dev,
					पूर्णांक init_gain)
अणु
	चयन (init_gain) अणु
	शेष:
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0x17, 0x26); mdelay(1);
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0x24, 0x86); mdelay(1);
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0x05, 0xFA); mdelay(1);
		अवरोध;
	हाल 2:
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0x17, 0x36); mdelay(1);
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0x24, 0x86); mdelay(1);
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0x05, 0xFA); mdelay(1);
		अवरोध;
	हाल 3:
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0x17, 0x36); mdelay(1);
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0x24, 0x86); mdelay(1);
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0x05, 0xFB); mdelay(1);
		अवरोध;
	हाल 4:
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0x17, 0x46); mdelay(1);
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0x24, 0x86); mdelay(1);
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0x05, 0xFB); mdelay(1);
		अवरोध;
	हाल 5:
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0x17, 0x46); mdelay(1);
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0x24, 0x96); mdelay(1);
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0x05, 0xFB); mdelay(1);
		अवरोध;
	हाल 6:
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0x17, 0x56); mdelay(1);
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0x24, 0x96); mdelay(1);
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0x05, 0xFC); mdelay(1);
		अवरोध;
	हाल 7:
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0x17, 0x56); mdelay(1);
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0x24, 0xA6); mdelay(1);
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0x05, 0xFC); mdelay(1);
		अवरोध;
	हाल 8:
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0x17, 0x66); mdelay(1);
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0x24, 0xB6); mdelay(1);
		rtl8225se_ग_लिखो_phy_ofdm(dev, 0x05, 0xFC); mdelay(1);
		अवरोध;
	पूर्ण
पूर्ण

व्योम rtl8225se_rf_init(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा rtl8180_priv *priv = dev->priv;
	u32 rf23, rf24;
	u8 d_cut = 0;
	u8 पंचांगp;

	/* Page 1 */
	rtl8187se_rf_ग_लिखोreg(dev, 0x00, 0x013F); mdelay(1);
	rf23 = rtl8187se_rf_पढ़ोreg(dev, 0x08); mdelay(1);
	rf24 = rtl8187se_rf_पढ़ोreg(dev, 0x09); mdelay(1);
	अगर (rf23 == 0x0818 && rf24 == 0x070C)
		d_cut = 1;

	wiphy_info(dev->wiphy, "RTL8225-SE version %s\n",
		d_cut ? "D" : "not-D");

	/* Page 0: reg 0 - 15 */
	rtl8187se_rf_ग_लिखोreg(dev, 0x00, 0x009F); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x01, 0x06E0); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x02, 0x004D); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x03, 0x07F1); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x04, 0x0975); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x05, 0x0C72); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x06, 0x0AE6); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x07, 0x00CA); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x08, 0x0E1C); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x09, 0x02F0); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x0A, 0x09D0); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x0B, 0x01BA); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x0C, 0x0640); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x0D, 0x08DF); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x0E, 0x0020); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x0F, 0x0990); mdelay(1);
	/* page 1: reg 16-30 */
	rtl8187se_rf_ग_लिखोreg(dev, 0x00, 0x013F); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x03, 0x0806); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x04, 0x03A7); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x05, 0x059B); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x06, 0x0081); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x07, 0x01A0); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x0A, 0x0001); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x0B, 0x0418); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x0C, 0x0FBE); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x0D, 0x0008); mdelay(1);
	अगर (d_cut)
		rtl8187se_rf_ग_लिखोreg(dev, 0x0E, 0x0807);
	अन्यथा
		rtl8187se_rf_ग_लिखोreg(dev, 0x0E, 0x0806);
	mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x0F, 0x0ACC); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x00, 0x01D7); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x03, 0x0E00); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x04, 0x0E50); mdelay(1);

	rtl8187se_ग_लिखो_rf_gain(dev);

	rtl8187se_rf_ग_लिखोreg(dev, 0x05, 0x0203); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x06, 0x0200); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x00, 0x0137); mdelay(11);
	rtl8187se_rf_ग_लिखोreg(dev, 0x0D, 0x0008); mdelay(11);
	rtl8187se_rf_ग_लिखोreg(dev, 0x00, 0x0037); mdelay(11);
	rtl8187se_rf_ग_लिखोreg(dev, 0x04, 0x0160); mdelay(11);
	rtl8187se_rf_ग_लिखोreg(dev, 0x07, 0x0080); mdelay(11);
	rtl8187se_rf_ग_लिखोreg(dev, 0x02, 0x088D); msleep(221);
	rtl8187se_rf_ग_लिखोreg(dev, 0x00, 0x0137); mdelay(11);
	rtl8187se_rf_ग_लिखोreg(dev, 0x07, 0x0000); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x07, 0x0180); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x07, 0x0220); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x07, 0x03E0); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x06, 0x00C1); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x0A, 0x0001); mdelay(1);
	अगर (priv->xtal_cal) अणु
		पंचांगp = (priv->xtal_in << 4) | (priv->xtal_out << 1) |
		      (1 << 11) | (1 << 9);
		rtl8187se_rf_ग_लिखोreg(dev, 0x0F, पंचांगp);
		wiphy_info(dev->wiphy, "Xtal cal\n");
		mdelay(1);
	पूर्ण अन्यथा अणु
		wiphy_info(dev->wiphy, "NO Xtal cal\n");
		rtl8187se_rf_ग_लिखोreg(dev, 0x0F, 0x0ACC);
		mdelay(1);
	पूर्ण
	/* page 0 */
	rtl8187se_rf_ग_लिखोreg(dev, 0x00, 0x00BF); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x0D, 0x08DF); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x02, 0x004D); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x04, 0x0975); msleep(31);
	rtl8187se_rf_ग_लिखोreg(dev, 0x00, 0x0197); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x05, 0x05AB); mdelay(1);

	rtl8187se_rf_ग_लिखोreg(dev, 0x00, 0x009F); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x01, 0x0000); mdelay(1);
	rtl8187se_rf_ग_लिखोreg(dev, 0x02, 0x0000); mdelay(1);
	/* घातer save parameters */
	/* TODO: move to dev.c */
	rtl818x_ioग_लिखो8(priv, REG_ADDR1(0x024E),
		 rtl818x_ioपढ़ो8(priv, REG_ADDR1(0x24E)) & 0x9F);
	rtl8225se_ग_लिखो_phy_cck(dev, 0x00, 0xC8);
	rtl8225se_ग_लिखो_phy_cck(dev, 0x06, 0x1C);
	rtl8225se_ग_लिखो_phy_cck(dev, 0x10, 0x78);
	rtl8225se_ग_लिखो_phy_cck(dev, 0x2E, 0xD0);
	rtl8225se_ग_लिखो_phy_cck(dev, 0x2F, 0x06);
	rtl8225se_ग_लिखो_phy_cck(dev, 0x01, 0x46);

	/* घातer control */
	rtl818x_ioग_लिखो8(priv, &priv->map->TX_GAIN_CCK, 0x10);
	rtl818x_ioग_लिखो8(priv, &priv->map->TX_GAIN_OFDM, 0x1B);

	rtl818x_ioग_लिखो8(priv, &priv->map->TX_ANTENNA, 0x03);
	rtl8225se_ग_लिखो_phy_ofdm(dev, 0x00, 0x12);

	rtl8225se_ग_लिखो_zebra_agc(dev);

	rtl8225se_ग_लिखो_phy_ofdm(dev, 0x10, 0x00);

	rtl8187se_ग_लिखो_ofdm_config(dev);

	/* turn on RF */
	rtl8187se_rf_ग_लिखोreg(dev, 0x00, 0x009F); udelay(500);
	rtl8187se_rf_ग_लिखोreg(dev, 0x04, 0x0972); udelay(500);
	/* turn on RF again */
	rtl8187se_rf_ग_लिखोreg(dev, 0x00, 0x009F); udelay(500);
	rtl8187se_rf_ग_लिखोreg(dev, 0x04, 0x0972); udelay(500);
	/* turn on BB */
	rtl8225se_ग_लिखो_phy_ofdm(dev, 0x10, 0x40);
	rtl8225se_ग_लिखो_phy_ofdm(dev, 0x12, 0x40);

	rtl8187se_ग_लिखो_initial_gain(dev, 4);
पूर्ण

व्योम rtl8225se_rf_stop(काष्ठा ieee80211_hw *dev)
अणु
	/* checked क्रम 8187se */
	काष्ठा rtl8180_priv *priv = dev->priv;

	/* turn off BB RXIQ matrix to cut off rx संकेत */
	rtl8225se_ग_लिखो_phy_ofdm(dev, 0x10, 0x00);
	rtl8225se_ग_लिखो_phy_ofdm(dev, 0x12, 0x00);
	/* turn off RF */
	rtl8187se_rf_ग_लिखोreg(dev, 0x04, 0x0000);
	rtl8187se_rf_ग_लिखोreg(dev, 0x00, 0x0000);

	usleep_range(1000, 5000);
	/* turn off A/D and D/A */
	rtl8180_set_anaparam(priv, RTL8225SE_ANAPARAM_OFF);
	rtl8180_set_anaparam2(priv, RTL8225SE_ANAPARAM2_OFF);
पूर्ण

व्योम rtl8225se_rf_set_channel(काष्ठा ieee80211_hw *dev,
				   काष्ठा ieee80211_conf *conf)
अणु
	पूर्णांक chan =
		ieee80211_frequency_to_channel(conf->chandef.chan->center_freq);

	rtl8225sez2_rf_set_tx_घातer(dev, chan);
	rtl8187se_rf_ग_लिखोreg(dev, 0x7, rtl8225se_chan[chan - 1]);
	अगर ((rtl8187se_rf_पढ़ोreg(dev, 0x7) & 0x0F80) !=
		rtl8225se_chan[chan - 1])
		rtl8187se_rf_ग_लिखोreg(dev, 0x7, rtl8225se_chan[chan - 1]);
	usleep_range(10000, 20000);
पूर्ण

अटल स्थिर काष्ठा rtl818x_rf_ops rtl8225se_ops = अणु
	.name		= "rtl8225-se",
	.init		= rtl8225se_rf_init,
	.stop		= rtl8225se_rf_stop,
	.set_chan	= rtl8225se_rf_set_channel,
पूर्ण;

स्थिर काष्ठा rtl818x_rf_ops *rtl8187se_detect_rf(काष्ठा ieee80211_hw *dev)
अणु
	वापस &rtl8225se_ops;
पूर्ण
