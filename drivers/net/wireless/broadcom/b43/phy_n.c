<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Broadcom B43 wireless driver
  IEEE 802.11n PHY support

  Copyright (c) 2008 Michael Buesch <m@bues.ch>
  Copyright (c) 2010-2011 Rafaध Miधecki <zajec5@gmail.com>


*/

#समावेश <linux/cordic.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश "b43.h"
#समावेश "phy_n.h"
#समावेश "tables_nphy.h"
#समावेश "radio_2055.h"
#समावेश "radio_2056.h"
#समावेश "radio_2057.h"
#समावेश "main.h"
#समावेश "ppr.h"

काष्ठा nphy_txgains अणु
	u16 tx_lpf[2];
	u16 txgm[2];
	u16 pga[2];
	u16 pad[2];
	u16 ipa[2];
पूर्ण;

काष्ठा nphy_iqcal_params अणु
	u16 tx_lpf;
	u16 txgm;
	u16 pga;
	u16 pad;
	u16 ipa;
	u16 cal_gain;
	u16 ncorr[5];
पूर्ण;

काष्ठा nphy_iq_est अणु
	s32 iq0_prod;
	u32 i0_pwr;
	u32 q0_pwr;
	s32 iq1_prod;
	u32 i1_pwr;
	u32 q1_pwr;
पूर्ण;

क्रमागत b43_nphy_rf_sequence अणु
	B43_RFSEQ_RX2TX,
	B43_RFSEQ_TX2RX,
	B43_RFSEQ_RESET2RX,
	B43_RFSEQ_UPDATE_GAINH,
	B43_RFSEQ_UPDATE_GAINL,
	B43_RFSEQ_UPDATE_GAINU,
पूर्ण;

क्रमागत n_rf_ctl_over_cmd अणु
	N_RF_CTL_OVER_CMD_RXRF_PU = 0,
	N_RF_CTL_OVER_CMD_RX_PU = 1,
	N_RF_CTL_OVER_CMD_TX_PU = 2,
	N_RF_CTL_OVER_CMD_RX_GAIN = 3,
	N_RF_CTL_OVER_CMD_TX_GAIN = 4,
पूर्ण;

क्रमागत n_पूर्णांकc_override अणु
	N_INTC_OVERRIDE_OFF = 0,
	N_INTC_OVERRIDE_TRSW = 1,
	N_INTC_OVERRIDE_PA = 2,
	N_INTC_OVERRIDE_EXT_LNA_PU = 3,
	N_INTC_OVERRIDE_EXT_LNA_GAIN = 4,
पूर्ण;

क्रमागत n_rssi_type अणु
	N_RSSI_W1 = 0,
	N_RSSI_W2,
	N_RSSI_NB,
	N_RSSI_IQ,
	N_RSSI_TSSI_2G,
	N_RSSI_TSSI_5G,
	N_RSSI_TBD,
पूर्ण;

क्रमागत n_rail_type अणु
	N_RAIL_I = 0,
	N_RAIL_Q = 1,
पूर्ण;

अटल अंतरभूत bool b43_nphy_ipa(काष्ठा b43_wldev *dev)
अणु
	क्रमागत nl80211_band band = b43_current_band(dev->wl);
	वापस ((dev->phy.n->ipa2g_on && band == NL80211_BAND_2GHZ) ||
		(dev->phy.n->ipa5g_on && band == NL80211_BAND_5GHZ));
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/RxCoreGetState */
अटल u8 b43_nphy_get_rx_core_state(काष्ठा b43_wldev *dev)
अणु
	वापस (b43_phy_पढ़ो(dev, B43_NPHY_RFSEQCA) & B43_NPHY_RFSEQCA_RXEN) >>
		B43_NPHY_RFSEQCA_RXEN_SHIFT;
पूर्ण

/**************************************************
 * RF (just without b43_nphy_rf_ctl_पूर्णांकc_override)
 **************************************************/

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/ForceRFSeq */
अटल व्योम b43_nphy_क्रमce_rf_sequence(काष्ठा b43_wldev *dev,
				       क्रमागत b43_nphy_rf_sequence seq)
अणु
	अटल स्थिर u16 trigger[] = अणु
		[B43_RFSEQ_RX2TX]		= B43_NPHY_RFSEQTR_RX2TX,
		[B43_RFSEQ_TX2RX]		= B43_NPHY_RFSEQTR_TX2RX,
		[B43_RFSEQ_RESET2RX]		= B43_NPHY_RFSEQTR_RST2RX,
		[B43_RFSEQ_UPDATE_GAINH]	= B43_NPHY_RFSEQTR_UPGH,
		[B43_RFSEQ_UPDATE_GAINL]	= B43_NPHY_RFSEQTR_UPGL,
		[B43_RFSEQ_UPDATE_GAINU]	= B43_NPHY_RFSEQTR_UPGU,
	पूर्ण;
	पूर्णांक i;
	u16 seq_mode = b43_phy_पढ़ो(dev, B43_NPHY_RFSEQMODE);

	B43_WARN_ON(seq >= ARRAY_SIZE(trigger));

	b43_phy_set(dev, B43_NPHY_RFSEQMODE,
		    B43_NPHY_RFSEQMODE_CAOVER | B43_NPHY_RFSEQMODE_TROVER);
	b43_phy_set(dev, B43_NPHY_RFSEQTR, trigger[seq]);
	क्रम (i = 0; i < 200; i++) अणु
		अगर (!(b43_phy_पढ़ो(dev, B43_NPHY_RFSEQST) & trigger[seq]))
			जाओ ok;
		msleep(1);
	पूर्ण
	b43err(dev->wl, "RF sequence status timeout\n");
ok:
	b43_phy_ग_लिखो(dev, B43_NPHY_RFSEQMODE, seq_mode);
पूर्ण

अटल व्योम b43_nphy_rf_ctl_override_rev19(काष्ठा b43_wldev *dev, u16 field,
					   u16 value, u8 core, bool off,
					   u8 override_id)
अणु
	/* TODO */
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/RFCtrlOverrideRev7 */
अटल व्योम b43_nphy_rf_ctl_override_rev7(काष्ठा b43_wldev *dev, u16 field,
					  u16 value, u8 core, bool off,
					  u8 override)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	स्थिर काष्ठा nphy_rf_control_override_rev7 *e;
	u16 en_addrs[3][2] = अणु
		अणु 0x0E7, 0x0EC पूर्ण, अणु 0x342, 0x343 पूर्ण, अणु 0x346, 0x347 पूर्ण
	पूर्ण;
	u16 en_addr;
	u16 en_mask = field;
	u16 val_addr;
	u8 i;

	अगर (phy->rev >= 19 || phy->rev < 3) अणु
		B43_WARN_ON(1);
		वापस;
	पूर्ण

	/* Remember: we can get शून्य! */
	e = b43_nphy_get_rf_ctl_over_rev7(dev, field, override);

	क्रम (i = 0; i < 2; i++) अणु
		अगर (override >= ARRAY_SIZE(en_addrs)) अणु
			b43err(dev->wl, "Invalid override value %d\n", override);
			वापस;
		पूर्ण
		en_addr = en_addrs[override][i];

		अगर (e)
			val_addr = (i == 0) ? e->val_addr_core0 : e->val_addr_core1;

		अगर (off) अणु
			b43_phy_mask(dev, en_addr, ~en_mask);
			अगर (e) /* Do it safer, better than wl */
				b43_phy_mask(dev, val_addr, ~e->val_mask);
		पूर्ण अन्यथा अणु
			अगर (!core || (core & (1 << i))) अणु
				b43_phy_set(dev, en_addr, en_mask);
				अगर (e)
					b43_phy_maskset(dev, val_addr, ~e->val_mask, (value << e->val_shअगरt));
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/RFCtrlOverideOneToMany */
अटल व्योम b43_nphy_rf_ctl_override_one_to_many(काष्ठा b43_wldev *dev,
						 क्रमागत n_rf_ctl_over_cmd cmd,
						 u16 value, u8 core, bool off)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	u16 पंचांगp;

	B43_WARN_ON(phy->rev < 7);

	चयन (cmd) अणु
	हाल N_RF_CTL_OVER_CMD_RXRF_PU:
		b43_nphy_rf_ctl_override_rev7(dev, 0x20, value, core, off, 1);
		b43_nphy_rf_ctl_override_rev7(dev, 0x10, value, core, off, 1);
		b43_nphy_rf_ctl_override_rev7(dev, 0x08, value, core, off, 1);
		अवरोध;
	हाल N_RF_CTL_OVER_CMD_RX_PU:
		b43_nphy_rf_ctl_override_rev7(dev, 0x4, value, core, off, 1);
		b43_nphy_rf_ctl_override_rev7(dev, 0x2, value, core, off, 1);
		b43_nphy_rf_ctl_override_rev7(dev, 0x1, value, core, off, 1);
		b43_nphy_rf_ctl_override_rev7(dev, 0x2, value, core, off, 2);
		b43_nphy_rf_ctl_override_rev7(dev, 0x0800, 0, core, off, 1);
		अवरोध;
	हाल N_RF_CTL_OVER_CMD_TX_PU:
		b43_nphy_rf_ctl_override_rev7(dev, 0x4, value, core, off, 0);
		b43_nphy_rf_ctl_override_rev7(dev, 0x2, value, core, off, 1);
		b43_nphy_rf_ctl_override_rev7(dev, 0x1, value, core, off, 2);
		b43_nphy_rf_ctl_override_rev7(dev, 0x0800, 1, core, off, 1);
		अवरोध;
	हाल N_RF_CTL_OVER_CMD_RX_GAIN:
		पंचांगp = value & 0xFF;
		b43_nphy_rf_ctl_override_rev7(dev, 0x0800, पंचांगp, core, off, 0);
		पंचांगp = value >> 8;
		b43_nphy_rf_ctl_override_rev7(dev, 0x6000, पंचांगp, core, off, 0);
		अवरोध;
	हाल N_RF_CTL_OVER_CMD_TX_GAIN:
		पंचांगp = value & 0x7FFF;
		b43_nphy_rf_ctl_override_rev7(dev, 0x1000, पंचांगp, core, off, 0);
		पंचांगp = value >> 14;
		b43_nphy_rf_ctl_override_rev7(dev, 0x4000, पंचांगp, core, off, 0);
		अवरोध;
	पूर्ण
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/RFCtrlOverride */
अटल व्योम b43_nphy_rf_ctl_override(काष्ठा b43_wldev *dev, u16 field,
				     u16 value, u8 core, bool off)
अणु
	पूर्णांक i;
	u8 index = fls(field);
	u8 addr, en_addr, val_addr;
	/* we expect only one bit set */
	B43_WARN_ON(field & (~(1 << (index - 1))));

	अगर (dev->phy.rev >= 3) अणु
		स्थिर काष्ठा nphy_rf_control_override_rev3 *rf_ctrl;
		क्रम (i = 0; i < 2; i++) अणु
			अगर (index == 0 || index == 16) अणु
				b43err(dev->wl,
					"Unsupported RF Ctrl Override call\n");
				वापस;
			पूर्ण

			rf_ctrl = &tbl_rf_control_override_rev3[index - 1];
			en_addr = B43_PHY_N((i == 0) ?
				rf_ctrl->en_addr0 : rf_ctrl->en_addr1);
			val_addr = B43_PHY_N((i == 0) ?
				rf_ctrl->val_addr0 : rf_ctrl->val_addr1);

			अगर (off) अणु
				b43_phy_mask(dev, en_addr, ~(field));
				b43_phy_mask(dev, val_addr,
						~(rf_ctrl->val_mask));
			पूर्ण अन्यथा अणु
				अगर (core == 0 || ((1 << i) & core)) अणु
					b43_phy_set(dev, en_addr, field);
					b43_phy_maskset(dev, val_addr,
						~(rf_ctrl->val_mask),
						(value << rf_ctrl->val_shअगरt));
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा nphy_rf_control_override_rev2 *rf_ctrl;
		अगर (off) अणु
			b43_phy_mask(dev, B43_NPHY_RFCTL_OVER, ~(field));
			value = 0;
		पूर्ण अन्यथा अणु
			b43_phy_set(dev, B43_NPHY_RFCTL_OVER, field);
		पूर्ण

		क्रम (i = 0; i < 2; i++) अणु
			अगर (index <= 1 || index == 16) अणु
				b43err(dev->wl,
					"Unsupported RF Ctrl Override call\n");
				वापस;
			पूर्ण

			अगर (index == 2 || index == 10 ||
			    (index >= 13 && index <= 15)) अणु
				core = 1;
			पूर्ण

			rf_ctrl = &tbl_rf_control_override_rev2[index - 2];
			addr = B43_PHY_N((i == 0) ?
				rf_ctrl->addr0 : rf_ctrl->addr1);

			अगर ((1 << i) & core)
				b43_phy_maskset(dev, addr, ~(rf_ctrl->bmask),
						(value << rf_ctrl->shअगरt));

			b43_phy_set(dev, B43_NPHY_RFCTL_OVER, 0x1);
			b43_phy_set(dev, B43_NPHY_RFCTL_CMD,
					B43_NPHY_RFCTL_CMD_START);
			udelay(1);
			b43_phy_mask(dev, B43_NPHY_RFCTL_OVER, 0xFFFE);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम b43_nphy_rf_ctl_पूर्णांकc_override_rev7(काष्ठा b43_wldev *dev,
					       क्रमागत n_पूर्णांकc_override पूर्णांकc_override,
					       u16 value, u8 core_sel)
अणु
	u16 reg, पंचांगp, पंचांगp2, val;
	पूर्णांक core;

	/* TODO: What about rev19+? Revs 3+ and 7+ are a bit similar */

	क्रम (core = 0; core < 2; core++) अणु
		अगर ((core_sel == 1 && core != 0) ||
		    (core_sel == 2 && core != 1))
			जारी;

		reg = (core == 0) ? B43_NPHY_RFCTL_INTC1 : B43_NPHY_RFCTL_INTC2;

		चयन (पूर्णांकc_override) अणु
		हाल N_INTC_OVERRIDE_OFF:
			b43_phy_ग_लिखो(dev, reg, 0);
			b43_phy_mask(dev, 0x2ff, ~0x2000);
			b43_nphy_क्रमce_rf_sequence(dev, B43_RFSEQ_RESET2RX);
			अवरोध;
		हाल N_INTC_OVERRIDE_TRSW:
			b43_phy_maskset(dev, reg, ~0xC0, value << 6);
			b43_phy_set(dev, reg, 0x400);

			b43_phy_mask(dev, 0x2ff, ~0xC000 & 0xFFFF);
			b43_phy_set(dev, 0x2ff, 0x2000);
			b43_phy_set(dev, 0x2ff, 0x0001);
			अवरोध;
		हाल N_INTC_OVERRIDE_PA:
			पंचांगp = 0x0030;
			अगर (b43_current_band(dev->wl) == NL80211_BAND_5GHZ)
				val = value << 5;
			अन्यथा
				val = value << 4;
			b43_phy_maskset(dev, reg, ~पंचांगp, val);
			b43_phy_set(dev, reg, 0x1000);
			अवरोध;
		हाल N_INTC_OVERRIDE_EXT_LNA_PU:
			अगर (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) अणु
				पंचांगp = 0x0001;
				पंचांगp2 = 0x0004;
				val = value;
			पूर्ण अन्यथा अणु
				पंचांगp = 0x0004;
				पंचांगp2 = 0x0001;
				val = value << 2;
			पूर्ण
			b43_phy_maskset(dev, reg, ~पंचांगp, val);
			b43_phy_mask(dev, reg, ~पंचांगp2);
			अवरोध;
		हाल N_INTC_OVERRIDE_EXT_LNA_GAIN:
			अगर (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) अणु
				पंचांगp = 0x0002;
				पंचांगp2 = 0x0008;
				val = value << 1;
			पूर्ण अन्यथा अणु
				पंचांगp = 0x0008;
				पंचांगp2 = 0x0002;
				val = value << 3;
			पूर्ण
			b43_phy_maskset(dev, reg, ~पंचांगp, val);
			b43_phy_mask(dev, reg, ~पंचांगp2);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/RFCtrlIntcOverride */
अटल व्योम b43_nphy_rf_ctl_पूर्णांकc_override(काष्ठा b43_wldev *dev,
					  क्रमागत n_पूर्णांकc_override पूर्णांकc_override,
					  u16 value, u8 core)
अणु
	u8 i, j;
	u16 reg, पंचांगp, val;

	अगर (dev->phy.rev >= 7) अणु
		b43_nphy_rf_ctl_पूर्णांकc_override_rev7(dev, पूर्णांकc_override, value,
						   core);
		वापस;
	पूर्ण

	B43_WARN_ON(dev->phy.rev < 3);

	क्रम (i = 0; i < 2; i++) अणु
		अगर ((core == 1 && i == 1) || (core == 2 && !i))
			जारी;

		reg = (i == 0) ?
			B43_NPHY_RFCTL_INTC1 : B43_NPHY_RFCTL_INTC2;
		b43_phy_set(dev, reg, 0x400);

		चयन (पूर्णांकc_override) अणु
		हाल N_INTC_OVERRIDE_OFF:
			b43_phy_ग_लिखो(dev, reg, 0);
			b43_nphy_क्रमce_rf_sequence(dev, B43_RFSEQ_RESET2RX);
			अवरोध;
		हाल N_INTC_OVERRIDE_TRSW:
			अगर (!i) अणु
				b43_phy_maskset(dev, B43_NPHY_RFCTL_INTC1,
						0xFC3F, (value << 6));
				b43_phy_maskset(dev, B43_NPHY_TXF_40CO_B1S1,
						0xFFFE, 1);
				b43_phy_set(dev, B43_NPHY_RFCTL_CMD,
						B43_NPHY_RFCTL_CMD_START);
				क्रम (j = 0; j < 100; j++) अणु
					अगर (!(b43_phy_पढ़ो(dev, B43_NPHY_RFCTL_CMD) & B43_NPHY_RFCTL_CMD_START)) अणु
						j = 0;
						अवरोध;
					पूर्ण
					udelay(10);
				पूर्ण
				अगर (j)
					b43err(dev->wl,
						"intc override timeout\n");
				b43_phy_mask(dev, B43_NPHY_TXF_40CO_B1S1,
						0xFFFE);
			पूर्ण अन्यथा अणु
				b43_phy_maskset(dev, B43_NPHY_RFCTL_INTC2,
						0xFC3F, (value << 6));
				b43_phy_maskset(dev, B43_NPHY_RFCTL_OVER,
						0xFFFE, 1);
				b43_phy_set(dev, B43_NPHY_RFCTL_CMD,
						B43_NPHY_RFCTL_CMD_RXTX);
				क्रम (j = 0; j < 100; j++) अणु
					अगर (!(b43_phy_पढ़ो(dev, B43_NPHY_RFCTL_CMD) & B43_NPHY_RFCTL_CMD_RXTX)) अणु
						j = 0;
						अवरोध;
					पूर्ण
					udelay(10);
				पूर्ण
				अगर (j)
					b43err(dev->wl,
						"intc override timeout\n");
				b43_phy_mask(dev, B43_NPHY_RFCTL_OVER,
						0xFFFE);
			पूर्ण
			अवरोध;
		हाल N_INTC_OVERRIDE_PA:
			अगर (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) अणु
				पंचांगp = 0x0020;
				val = value << 5;
			पूर्ण अन्यथा अणु
				पंचांगp = 0x0010;
				val = value << 4;
			पूर्ण
			b43_phy_maskset(dev, reg, ~पंचांगp, val);
			अवरोध;
		हाल N_INTC_OVERRIDE_EXT_LNA_PU:
			अगर (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) अणु
				पंचांगp = 0x0001;
				val = value;
			पूर्ण अन्यथा अणु
				पंचांगp = 0x0004;
				val = value << 2;
			पूर्ण
			b43_phy_maskset(dev, reg, ~पंचांगp, val);
			अवरोध;
		हाल N_INTC_OVERRIDE_EXT_LNA_GAIN:
			अगर (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) अणु
				पंचांगp = 0x0002;
				val = value << 1;
			पूर्ण अन्यथा अणु
				पंचांगp = 0x0008;
				val = value << 3;
			पूर्ण
			b43_phy_maskset(dev, reg, ~पंचांगp, val);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/**************************************************
 * Various PHY ops
 **************************************************/

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/clip-detection */
अटल व्योम b43_nphy_ग_लिखो_clip_detection(काष्ठा b43_wldev *dev,
					  स्थिर u16 *clip_st)
अणु
	b43_phy_ग_लिखो(dev, B43_NPHY_C1_CLIP1THRES, clip_st[0]);
	b43_phy_ग_लिखो(dev, B43_NPHY_C2_CLIP1THRES, clip_st[1]);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/clip-detection */
अटल व्योम b43_nphy_पढ़ो_clip_detection(काष्ठा b43_wldev *dev, u16 *clip_st)
अणु
	clip_st[0] = b43_phy_पढ़ो(dev, B43_NPHY_C1_CLIP1THRES);
	clip_st[1] = b43_phy_पढ़ो(dev, B43_NPHY_C2_CLIP1THRES);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/classअगरier */
अटल u16 b43_nphy_classअगरier(काष्ठा b43_wldev *dev, u16 mask, u16 val)
अणु
	u16 पंचांगp;

	अगर (dev->dev->core_rev == 16)
		b43_mac_suspend(dev);

	पंचांगp = b43_phy_पढ़ो(dev, B43_NPHY_CLASSCTL);
	पंचांगp &= (B43_NPHY_CLASSCTL_CCKEN | B43_NPHY_CLASSCTL_OFDMEN |
		B43_NPHY_CLASSCTL_WAITEDEN);
	पंचांगp &= ~mask;
	पंचांगp |= (val & mask);
	b43_phy_maskset(dev, B43_NPHY_CLASSCTL, 0xFFF8, पंचांगp);

	अगर (dev->dev->core_rev == 16)
		b43_mac_enable(dev);

	वापस पंचांगp;
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/CCA */
अटल व्योम b43_nphy_reset_cca(काष्ठा b43_wldev *dev)
अणु
	u16 bbcfg;

	b43_phy_क्रमce_घड़ी(dev, 1);
	bbcfg = b43_phy_पढ़ो(dev, B43_NPHY_BBCFG);
	b43_phy_ग_लिखो(dev, B43_NPHY_BBCFG, bbcfg | B43_NPHY_BBCFG_RSTCCA);
	udelay(1);
	b43_phy_ग_लिखो(dev, B43_NPHY_BBCFG, bbcfg & ~B43_NPHY_BBCFG_RSTCCA);
	b43_phy_क्रमce_घड़ी(dev, 0);
	b43_nphy_क्रमce_rf_sequence(dev, B43_RFSEQ_RESET2RX);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/carriersearch */
अटल व्योम b43_nphy_stay_in_carrier_search(काष्ठा b43_wldev *dev, bool enable)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_n *nphy = phy->n;

	अगर (enable) अणु
		अटल स्थिर u16 clip[] = अणु 0xFFFF, 0xFFFF पूर्ण;
		अगर (nphy->deaf_count++ == 0) अणु
			nphy->classअगरier_state = b43_nphy_classअगरier(dev, 0, 0);
			b43_nphy_classअगरier(dev, 0x7,
					    B43_NPHY_CLASSCTL_WAITEDEN);
			b43_nphy_पढ़ो_clip_detection(dev, nphy->clip_state);
			b43_nphy_ग_लिखो_clip_detection(dev, clip);
		पूर्ण
		b43_nphy_reset_cca(dev);
	पूर्ण अन्यथा अणु
		अगर (--nphy->deaf_count == 0) अणु
			b43_nphy_classअगरier(dev, 0x7, nphy->classअगरier_state);
			b43_nphy_ग_लिखो_clip_detection(dev, nphy->clip_state);
		पूर्ण
	पूर्ण
पूर्ण

/* https://bcm-v4.sipsolutions.net/PHY/N/Read_Lpf_Bw_Ctl */
अटल u16 b43_nphy_पढ़ो_lpf_ctl(काष्ठा b43_wldev *dev, u16 offset)
अणु
	अगर (!offset)
		offset = b43_is_40mhz(dev) ? 0x159 : 0x154;
	वापस b43_ntab_पढ़ो(dev, B43_NTAB16(7, offset)) & 0x7;
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/AdjustLnaGainTbl */
अटल व्योम b43_nphy_adjust_lna_gain_table(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_n *nphy = dev->phy.n;

	u8 i;
	s16 पंचांगp;
	u16 data[4];
	s16 gain[2];
	u16 minmax[2];
	अटल स्थिर u16 lna_gain[4] = अणु -2, 10, 19, 25 पूर्ण;

	अगर (nphy->hang_aव्योम)
		b43_nphy_stay_in_carrier_search(dev, 1);

	अगर (nphy->gain_boost) अणु
		अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
			gain[0] = 6;
			gain[1] = 6;
		पूर्ण अन्यथा अणु
			पंचांगp = 40370 - 315 * dev->phy.channel;
			gain[0] = ((पंचांगp >> 13) + ((पंचांगp >> 12) & 1));
			पंचांगp = 23242 - 224 * dev->phy.channel;
			gain[1] = ((पंचांगp >> 13) + ((पंचांगp >> 12) & 1));
		पूर्ण
	पूर्ण अन्यथा अणु
		gain[0] = 0;
		gain[1] = 0;
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		अगर (nphy->elna_gain_config) अणु
			data[0] = 19 + gain[i];
			data[1] = 25 + gain[i];
			data[2] = 25 + gain[i];
			data[3] = 25 + gain[i];
		पूर्ण अन्यथा अणु
			data[0] = lna_gain[0] + gain[i];
			data[1] = lna_gain[1] + gain[i];
			data[2] = lna_gain[2] + gain[i];
			data[3] = lna_gain[3] + gain[i];
		पूर्ण
		b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(i, 8), 4, data);

		minmax[i] = 23 + gain[i];
	पूर्ण

	b43_phy_maskset(dev, B43_NPHY_C1_MINMAX_GAIN, ~B43_NPHY_C1_MINGAIN,
				minmax[0] << B43_NPHY_C1_MINGAIN_SHIFT);
	b43_phy_maskset(dev, B43_NPHY_C2_MINMAX_GAIN, ~B43_NPHY_C2_MINGAIN,
				minmax[1] << B43_NPHY_C2_MINGAIN_SHIFT);

	अगर (nphy->hang_aव्योम)
		b43_nphy_stay_in_carrier_search(dev, 0);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/SetRfSeq */
अटल व्योम b43_nphy_set_rf_sequence(काष्ठा b43_wldev *dev, u8 cmd,
					u8 *events, u8 *delays, u8 length)
अणु
	काष्ठा b43_phy_n *nphy = dev->phy.n;
	u8 i;
	u8 end = (dev->phy.rev >= 3) ? 0x1F : 0x0F;
	u16 offset1 = cmd << 4;
	u16 offset2 = offset1 + 0x80;

	अगर (nphy->hang_aव्योम)
		b43_nphy_stay_in_carrier_search(dev, true);

	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB8(7, offset1), length, events);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB8(7, offset2), length, delays);

	क्रम (i = length; i < 16; i++) अणु
		b43_ntab_ग_लिखो(dev, B43_NTAB8(7, offset1 + i), end);
		b43_ntab_ग_लिखो(dev, B43_NTAB8(7, offset2 + i), 1);
	पूर्ण

	अगर (nphy->hang_aव्योम)
		b43_nphy_stay_in_carrier_search(dev, false);
पूर्ण

/**************************************************
 * Radio 0x2057
 **************************************************/

अटल व्योम b43_radio_2057_chantab_upload(काष्ठा b43_wldev *dev,
					  स्थिर काष्ठा b43_nphy_chantabent_rev7 *e_r7,
					  स्थिर काष्ठा b43_nphy_chantabent_rev7_2g *e_r7_2g)
अणु
	अगर (e_r7_2g) अणु
		b43_radio_ग_लिखो(dev, R2057_VCOCAL_COUNTVAL0, e_r7_2g->radio_vcocal_countval0);
		b43_radio_ग_लिखो(dev, R2057_VCOCAL_COUNTVAL1, e_r7_2g->radio_vcocal_countval1);
		b43_radio_ग_लिखो(dev, R2057_RFPLL_REFMASTER_SPAREXTALSIZE, e_r7_2g->radio_rfpll_refmaster_sparextalsize);
		b43_radio_ग_लिखो(dev, R2057_RFPLL_LOOPFILTER_R1, e_r7_2g->radio_rfpll_loopfilter_r1);
		b43_radio_ग_लिखो(dev, R2057_RFPLL_LOOPFILTER_C2, e_r7_2g->radio_rfpll_loopfilter_c2);
		b43_radio_ग_लिखो(dev, R2057_RFPLL_LOOPFILTER_C1, e_r7_2g->radio_rfpll_loopfilter_c1);
		b43_radio_ग_लिखो(dev, R2057_CP_KPD_IDAC, e_r7_2g->radio_cp_kpd_idac);
		b43_radio_ग_लिखो(dev, R2057_RFPLL_MMD0, e_r7_2g->radio_rfpll_mmd0);
		b43_radio_ग_लिखो(dev, R2057_RFPLL_MMD1, e_r7_2g->radio_rfpll_mmd1);
		b43_radio_ग_लिखो(dev, R2057_VCOBUF_TUNE, e_r7_2g->radio_vcobuf_tune);
		b43_radio_ग_लिखो(dev, R2057_LOGEN_MX2G_TUNE, e_r7_2g->radio_logen_mx2g_tune);
		b43_radio_ग_लिखो(dev, R2057_LOGEN_INDBUF2G_TUNE, e_r7_2g->radio_logen_indbuf2g_tune);
		b43_radio_ग_लिखो(dev, R2057_TXMIX2G_TUNE_BOOST_PU_CORE0, e_r7_2g->radio_txmix2g_tune_boost_pu_core0);
		b43_radio_ग_लिखो(dev, R2057_PAD2G_TUNE_PUS_CORE0, e_r7_2g->radio_pad2g_tune_pus_core0);
		b43_radio_ग_लिखो(dev, R2057_LNA2G_TUNE_CORE0, e_r7_2g->radio_lna2g_tune_core0);
		b43_radio_ग_लिखो(dev, R2057_TXMIX2G_TUNE_BOOST_PU_CORE1, e_r7_2g->radio_txmix2g_tune_boost_pu_core1);
		b43_radio_ग_लिखो(dev, R2057_PAD2G_TUNE_PUS_CORE1, e_r7_2g->radio_pad2g_tune_pus_core1);
		b43_radio_ग_लिखो(dev, R2057_LNA2G_TUNE_CORE1, e_r7_2g->radio_lna2g_tune_core1);

	पूर्ण अन्यथा अणु
		b43_radio_ग_लिखो(dev, R2057_VCOCAL_COUNTVAL0, e_r7->radio_vcocal_countval0);
		b43_radio_ग_लिखो(dev, R2057_VCOCAL_COUNTVAL1, e_r7->radio_vcocal_countval1);
		b43_radio_ग_लिखो(dev, R2057_RFPLL_REFMASTER_SPAREXTALSIZE, e_r7->radio_rfpll_refmaster_sparextalsize);
		b43_radio_ग_लिखो(dev, R2057_RFPLL_LOOPFILTER_R1, e_r7->radio_rfpll_loopfilter_r1);
		b43_radio_ग_लिखो(dev, R2057_RFPLL_LOOPFILTER_C2, e_r7->radio_rfpll_loopfilter_c2);
		b43_radio_ग_लिखो(dev, R2057_RFPLL_LOOPFILTER_C1, e_r7->radio_rfpll_loopfilter_c1);
		b43_radio_ग_लिखो(dev, R2057_CP_KPD_IDAC, e_r7->radio_cp_kpd_idac);
		b43_radio_ग_लिखो(dev, R2057_RFPLL_MMD0, e_r7->radio_rfpll_mmd0);
		b43_radio_ग_लिखो(dev, R2057_RFPLL_MMD1, e_r7->radio_rfpll_mmd1);
		b43_radio_ग_लिखो(dev, R2057_VCOBUF_TUNE, e_r7->radio_vcobuf_tune);
		b43_radio_ग_लिखो(dev, R2057_LOGEN_MX2G_TUNE, e_r7->radio_logen_mx2g_tune);
		b43_radio_ग_लिखो(dev, R2057_LOGEN_MX5G_TUNE, e_r7->radio_logen_mx5g_tune);
		b43_radio_ग_लिखो(dev, R2057_LOGEN_INDBUF2G_TUNE, e_r7->radio_logen_indbuf2g_tune);
		b43_radio_ग_लिखो(dev, R2057_LOGEN_INDBUF5G_TUNE, e_r7->radio_logen_indbuf5g_tune);
		b43_radio_ग_लिखो(dev, R2057_TXMIX2G_TUNE_BOOST_PU_CORE0, e_r7->radio_txmix2g_tune_boost_pu_core0);
		b43_radio_ग_लिखो(dev, R2057_PAD2G_TUNE_PUS_CORE0, e_r7->radio_pad2g_tune_pus_core0);
		b43_radio_ग_लिखो(dev, R2057_PGA_BOOST_TUNE_CORE0, e_r7->radio_pga_boost_tune_core0);
		b43_radio_ग_लिखो(dev, R2057_TXMIX5G_BOOST_TUNE_CORE0, e_r7->radio_txmix5g_boost_tune_core0);
		b43_radio_ग_लिखो(dev, R2057_PAD5G_TUNE_MISC_PUS_CORE0, e_r7->radio_pad5g_tune_misc_pus_core0);
		b43_radio_ग_लिखो(dev, R2057_LNA2G_TUNE_CORE0, e_r7->radio_lna2g_tune_core0);
		b43_radio_ग_लिखो(dev, R2057_LNA5G_TUNE_CORE0, e_r7->radio_lna5g_tune_core0);
		b43_radio_ग_लिखो(dev, R2057_TXMIX2G_TUNE_BOOST_PU_CORE1, e_r7->radio_txmix2g_tune_boost_pu_core1);
		b43_radio_ग_लिखो(dev, R2057_PAD2G_TUNE_PUS_CORE1, e_r7->radio_pad2g_tune_pus_core1);
		b43_radio_ग_लिखो(dev, R2057_PGA_BOOST_TUNE_CORE1, e_r7->radio_pga_boost_tune_core1);
		b43_radio_ग_लिखो(dev, R2057_TXMIX5G_BOOST_TUNE_CORE1, e_r7->radio_txmix5g_boost_tune_core1);
		b43_radio_ग_लिखो(dev, R2057_PAD5G_TUNE_MISC_PUS_CORE1, e_r7->radio_pad5g_tune_misc_pus_core1);
		b43_radio_ग_लिखो(dev, R2057_LNA2G_TUNE_CORE1, e_r7->radio_lna2g_tune_core1);
		b43_radio_ग_लिखो(dev, R2057_LNA5G_TUNE_CORE1, e_r7->radio_lna5g_tune_core1);
	पूर्ण
पूर्ण

अटल व्योम b43_radio_2057_setup(काष्ठा b43_wldev *dev,
				 स्थिर काष्ठा b43_nphy_chantabent_rev7 *tabent_r7,
				 स्थिर काष्ठा b43_nphy_chantabent_rev7_2g *tabent_r7_2g)
अणु
	काष्ठा b43_phy *phy = &dev->phy;

	b43_radio_2057_chantab_upload(dev, tabent_r7, tabent_r7_2g);

	चयन (phy->radio_rev) अणु
	हाल 0 ... 4:
	हाल 6:
		अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
			b43_radio_ग_लिखो(dev, R2057_RFPLL_LOOPFILTER_R1, 0x3f);
			b43_radio_ग_लिखो(dev, R2057_CP_KPD_IDAC, 0x3f);
			b43_radio_ग_लिखो(dev, R2057_RFPLL_LOOPFILTER_C1, 0x8);
			b43_radio_ग_लिखो(dev, R2057_RFPLL_LOOPFILTER_C2, 0x8);
		पूर्ण अन्यथा अणु
			b43_radio_ग_लिखो(dev, R2057_RFPLL_LOOPFILTER_R1, 0x1f);
			b43_radio_ग_लिखो(dev, R2057_CP_KPD_IDAC, 0x3f);
			b43_radio_ग_लिखो(dev, R2057_RFPLL_LOOPFILTER_C1, 0x8);
			b43_radio_ग_लिखो(dev, R2057_RFPLL_LOOPFILTER_C2, 0x8);
		पूर्ण
		अवरोध;
	हाल 9: /* e.g. PHY rev 16 */
		b43_radio_ग_लिखो(dev, R2057_LOGEN_PTAT_RESETS, 0x20);
		b43_radio_ग_लिखो(dev, R2057_VCOBUF_IDACS, 0x18);
		अगर (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) अणु
			b43_radio_ग_लिखो(dev, R2057_LOGEN_PTAT_RESETS, 0x38);
			b43_radio_ग_लिखो(dev, R2057_VCOBUF_IDACS, 0x0f);

			अगर (b43_is_40mhz(dev)) अणु
				/* TODO */
			पूर्ण अन्यथा अणु
				b43_radio_ग_लिखो(dev,
						R2057_PAD_BIAS_FILTER_BWS_CORE0,
						0x3c);
				b43_radio_ग_लिखो(dev,
						R2057_PAD_BIAS_FILTER_BWS_CORE1,
						0x3c);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल 14: /* 2 GHz only */
		b43_radio_ग_लिखो(dev, R2057_RFPLL_LOOPFILTER_R1, 0x1b);
		b43_radio_ग_लिखो(dev, R2057_CP_KPD_IDAC, 0x3f);
		b43_radio_ग_लिखो(dev, R2057_RFPLL_LOOPFILTER_C1, 0x1f);
		b43_radio_ग_लिखो(dev, R2057_RFPLL_LOOPFILTER_C2, 0x1f);
		अवरोध;
	पूर्ण

	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
		u16 txmix2g_tune_boost_pu = 0;
		u16 pad2g_tune_pus = 0;

		अगर (b43_nphy_ipa(dev)) अणु
			चयन (phy->radio_rev) अणु
			हाल 9:
				txmix2g_tune_boost_pu = 0x0041;
				/* TODO */
				अवरोध;
			हाल 14:
				txmix2g_tune_boost_pu = 0x21;
				pad2g_tune_pus = 0x23;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (txmix2g_tune_boost_pu)
			b43_radio_ग_लिखो(dev, R2057_TXMIX2G_TUNE_BOOST_PU_CORE0,
					txmix2g_tune_boost_pu);
		अगर (pad2g_tune_pus)
			b43_radio_ग_लिखो(dev, R2057_PAD2G_TUNE_PUS_CORE0,
					pad2g_tune_pus);
		अगर (txmix2g_tune_boost_pu)
			b43_radio_ग_लिखो(dev, R2057_TXMIX2G_TUNE_BOOST_PU_CORE1,
					txmix2g_tune_boost_pu);
		अगर (pad2g_tune_pus)
			b43_radio_ग_लिखो(dev, R2057_PAD2G_TUNE_PUS_CORE1,
					pad2g_tune_pus);
	पूर्ण

	usleep_range(50, 100);

	/* VCO calibration */
	b43_radio_mask(dev, R2057_RFPLL_MISC_EN, ~0x01);
	b43_radio_mask(dev, R2057_RFPLL_MISC_CAL_RESETN, ~0x04);
	b43_radio_set(dev, R2057_RFPLL_MISC_CAL_RESETN, 0x4);
	b43_radio_set(dev, R2057_RFPLL_MISC_EN, 0x01);
	usleep_range(300, 600);
पूर्ण

/* Calibrate resistors in LPF of PLL?
 * https://bcm-v4.sipsolutions.net/PHY/radio205x_rcal
 */
अटल u8 b43_radio_2057_rcal(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	u16 saved_regs_phy[12];
	u16 saved_regs_phy_rf[6];
	u16 saved_regs_radio[2] = अणु पूर्ण;
	अटल स्थिर u16 phy_to_store[] = अणु
		B43_NPHY_RFCTL_RSSIO1, B43_NPHY_RFCTL_RSSIO2,
		B43_NPHY_RFCTL_LUT_TRSW_LO1, B43_NPHY_RFCTL_LUT_TRSW_LO2,
		B43_NPHY_RFCTL_RXG1, B43_NPHY_RFCTL_RXG2,
		B43_NPHY_RFCTL_TXG1, B43_NPHY_RFCTL_TXG2,
		B43_NPHY_REV7_RF_CTL_MISC_REG3, B43_NPHY_REV7_RF_CTL_MISC_REG4,
		B43_NPHY_REV7_RF_CTL_MISC_REG5, B43_NPHY_REV7_RF_CTL_MISC_REG6,
	पूर्ण;
	अटल स्थिर u16 phy_to_store_rf[] = अणु
		B43_NPHY_REV3_RFCTL_OVER0, B43_NPHY_REV3_RFCTL_OVER1,
		B43_NPHY_REV7_RF_CTL_OVER3, B43_NPHY_REV7_RF_CTL_OVER4,
		B43_NPHY_REV7_RF_CTL_OVER5, B43_NPHY_REV7_RF_CTL_OVER6,
	पूर्ण;
	u16 पंचांगp;
	पूर्णांक i;

	/* Save */
	क्रम (i = 0; i < ARRAY_SIZE(phy_to_store); i++)
		saved_regs_phy[i] = b43_phy_पढ़ो(dev, phy_to_store[i]);
	क्रम (i = 0; i < ARRAY_SIZE(phy_to_store_rf); i++)
		saved_regs_phy_rf[i] = b43_phy_पढ़ो(dev, phy_to_store_rf[i]);

	/* Set */
	क्रम (i = 0; i < ARRAY_SIZE(phy_to_store); i++)
		b43_phy_ग_लिखो(dev, phy_to_store[i], 0);
	b43_phy_ग_लिखो(dev, B43_NPHY_REV3_RFCTL_OVER0, 0x07ff);
	b43_phy_ग_लिखो(dev, B43_NPHY_REV3_RFCTL_OVER1, 0x07ff);
	b43_phy_ग_लिखो(dev, B43_NPHY_REV7_RF_CTL_OVER3, 0x07ff);
	b43_phy_ग_लिखो(dev, B43_NPHY_REV7_RF_CTL_OVER4, 0x07ff);
	b43_phy_ग_लिखो(dev, B43_NPHY_REV7_RF_CTL_OVER5, 0x007f);
	b43_phy_ग_लिखो(dev, B43_NPHY_REV7_RF_CTL_OVER6, 0x007f);

	चयन (phy->radio_rev) अणु
	हाल 5:
		b43_phy_mask(dev, B43_NPHY_REV7_RF_CTL_OVER3, ~0x2);
		udelay(10);
		b43_radio_set(dev, R2057_IQTEST_SEL_PU, 0x1);
		b43_radio_maskset(dev, R2057v7_IQTEST_SEL_PU2, ~0x2, 0x1);
		अवरोध;
	हाल 9:
		b43_phy_set(dev, B43_NPHY_REV7_RF_CTL_OVER3, 0x2);
		b43_phy_set(dev, B43_NPHY_REV7_RF_CTL_MISC_REG3, 0x2);
		saved_regs_radio[0] = b43_radio_पढ़ो(dev, R2057_IQTEST_SEL_PU);
		b43_radio_ग_लिखो(dev, R2057_IQTEST_SEL_PU, 0x11);
		अवरोध;
	हाल 14:
		saved_regs_radio[0] = b43_radio_पढ़ो(dev, R2057_IQTEST_SEL_PU);
		saved_regs_radio[1] = b43_radio_पढ़ो(dev, R2057v7_IQTEST_SEL_PU2);
		b43_phy_set(dev, B43_NPHY_REV7_RF_CTL_MISC_REG3, 0x2);
		b43_phy_set(dev, B43_NPHY_REV7_RF_CTL_OVER3, 0x2);
		b43_radio_ग_लिखो(dev, R2057v7_IQTEST_SEL_PU2, 0x2);
		b43_radio_ग_लिखो(dev, R2057_IQTEST_SEL_PU, 0x1);
		अवरोध;
	पूर्ण

	/* Enable */
	b43_radio_set(dev, R2057_RCAL_CONFIG, 0x1);
	udelay(10);

	/* Start */
	b43_radio_set(dev, R2057_RCAL_CONFIG, 0x2);
	usleep_range(100, 200);

	/* Stop */
	b43_radio_mask(dev, R2057_RCAL_CONFIG, ~0x2);

	/* Wait and check क्रम result */
	अगर (!b43_radio_रुको_value(dev, R2057_RCAL_STATUS, 1, 1, 100, 1000000)) अणु
		b43err(dev->wl, "Radio 0x2057 rcal timeout\n");
		वापस 0;
	पूर्ण
	पंचांगp = b43_radio_पढ़ो(dev, R2057_RCAL_STATUS) & 0x3E;

	/* Disable */
	b43_radio_mask(dev, R2057_RCAL_CONFIG, ~0x1);

	/* Restore */
	क्रम (i = 0; i < ARRAY_SIZE(phy_to_store_rf); i++)
		b43_phy_ग_लिखो(dev, phy_to_store_rf[i], saved_regs_phy_rf[i]);
	क्रम (i = 0; i < ARRAY_SIZE(phy_to_store); i++)
		b43_phy_ग_लिखो(dev, phy_to_store[i], saved_regs_phy[i]);

	चयन (phy->radio_rev) अणु
	हाल 0 ... 4:
	हाल 6:
		b43_radio_maskset(dev, R2057_TEMPSENSE_CONFIG, ~0x3C, पंचांगp);
		b43_radio_maskset(dev, R2057_BANDGAP_RCAL_TRIM, ~0xF0,
				  पंचांगp << 2);
		अवरोध;
	हाल 5:
		b43_radio_mask(dev, R2057_IPA2G_CASCONV_CORE0, ~0x1);
		b43_radio_mask(dev, R2057v7_IQTEST_SEL_PU2, ~0x2);
		अवरोध;
	हाल 9:
		b43_radio_ग_लिखो(dev, R2057_IQTEST_SEL_PU, saved_regs_radio[0]);
		अवरोध;
	हाल 14:
		b43_radio_ग_लिखो(dev, R2057_IQTEST_SEL_PU, saved_regs_radio[0]);
		b43_radio_ग_लिखो(dev, R2057v7_IQTEST_SEL_PU2, saved_regs_radio[1]);
		अवरोध;
	पूर्ण

	वापस पंचांगp & 0x3e;
पूर्ण

/* Calibrate the पूर्णांकernal RC oscillator?
 * https://bcm-v4.sipsolutions.net/PHY/radio2057_rccal
 */
अटल u16 b43_radio_2057_rccal(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	bool special = (phy->radio_rev == 3 || phy->radio_rev == 4 ||
			phy->radio_rev == 6);
	u16 पंचांगp;

	/* Setup cal */
	अगर (special) अणु
		b43_radio_ग_लिखो(dev, R2057_RCCAL_MASTER, 0x61);
		b43_radio_ग_लिखो(dev, R2057_RCCAL_TRC0, 0xC0);
	पूर्ण अन्यथा अणु
		b43_radio_ग_लिखो(dev, R2057v7_RCCAL_MASTER, 0x61);
		b43_radio_ग_लिखो(dev, R2057_RCCAL_TRC0, 0xE9);
	पूर्ण
	b43_radio_ग_लिखो(dev, R2057_RCCAL_X1, 0x6E);

	/* Start, रुको, stop */
	b43_radio_ग_लिखो(dev, R2057_RCCAL_START_R1_Q1_P1, 0x55);
	अगर (!b43_radio_रुको_value(dev, R2057_RCCAL_DONE_OSCCAP, 2, 2, 500,
				  5000000))
		b43dbg(dev->wl, "Radio 0x2057 rccal timeout\n");
	usleep_range(35, 70);
	b43_radio_ग_लिखो(dev, R2057_RCCAL_START_R1_Q1_P1, 0x15);
	usleep_range(70, 140);

	/* Setup cal */
	अगर (special) अणु
		b43_radio_ग_लिखो(dev, R2057_RCCAL_MASTER, 0x69);
		b43_radio_ग_लिखो(dev, R2057_RCCAL_TRC0, 0xB0);
	पूर्ण अन्यथा अणु
		b43_radio_ग_लिखो(dev, R2057v7_RCCAL_MASTER, 0x69);
		b43_radio_ग_लिखो(dev, R2057_RCCAL_TRC0, 0xD5);
	पूर्ण
	b43_radio_ग_लिखो(dev, R2057_RCCAL_X1, 0x6E);

	/* Start, रुको, stop */
	usleep_range(35, 70);
	b43_radio_ग_लिखो(dev, R2057_RCCAL_START_R1_Q1_P1, 0x55);
	usleep_range(70, 140);
	अगर (!b43_radio_रुको_value(dev, R2057_RCCAL_DONE_OSCCAP, 2, 2, 500,
				  5000000))
		b43dbg(dev->wl, "Radio 0x2057 rccal timeout\n");
	usleep_range(35, 70);
	b43_radio_ग_लिखो(dev, R2057_RCCAL_START_R1_Q1_P1, 0x15);
	usleep_range(70, 140);

	/* Setup cal */
	अगर (special) अणु
		b43_radio_ग_लिखो(dev, R2057_RCCAL_MASTER, 0x73);
		b43_radio_ग_लिखो(dev, R2057_RCCAL_X1, 0x28);
		b43_radio_ग_लिखो(dev, R2057_RCCAL_TRC0, 0xB0);
	पूर्ण अन्यथा अणु
		b43_radio_ग_लिखो(dev, R2057v7_RCCAL_MASTER, 0x73);
		b43_radio_ग_लिखो(dev, R2057_RCCAL_X1, 0x6E);
		b43_radio_ग_लिखो(dev, R2057_RCCAL_TRC0, 0x99);
	पूर्ण

	/* Start, रुको, stop */
	usleep_range(35, 70);
	b43_radio_ग_लिखो(dev, R2057_RCCAL_START_R1_Q1_P1, 0x55);
	usleep_range(70, 140);
	अगर (!b43_radio_रुको_value(dev, R2057_RCCAL_DONE_OSCCAP, 2, 2, 500,
				  5000000)) अणु
		b43err(dev->wl, "Radio 0x2057 rcal timeout\n");
		वापस 0;
	पूर्ण
	पंचांगp = b43_radio_पढ़ो(dev, R2057_RCCAL_DONE_OSCCAP);
	usleep_range(35, 70);
	b43_radio_ग_लिखो(dev, R2057_RCCAL_START_R1_Q1_P1, 0x15);
	usleep_range(70, 140);

	अगर (special)
		b43_radio_mask(dev, R2057_RCCAL_MASTER, ~0x1);
	अन्यथा
		b43_radio_mask(dev, R2057v7_RCCAL_MASTER, ~0x1);

	वापस पंचांगp;
पूर्ण

अटल व्योम b43_radio_2057_init_pre(काष्ठा b43_wldev *dev)
अणु
	b43_phy_mask(dev, B43_NPHY_RFCTL_CMD, ~B43_NPHY_RFCTL_CMD_CHIP0PU);
	/* Maybe wl meant to reset and set (order?) RFCTL_CMD_OEPORFORCE? */
	b43_phy_mask(dev, B43_NPHY_RFCTL_CMD, B43_NPHY_RFCTL_CMD_OEPORFORCE);
	b43_phy_set(dev, B43_NPHY_RFCTL_CMD, ~B43_NPHY_RFCTL_CMD_OEPORFORCE);
	b43_phy_set(dev, B43_NPHY_RFCTL_CMD, B43_NPHY_RFCTL_CMD_CHIP0PU);
पूर्ण

अटल व्योम b43_radio_2057_init_post(काष्ठा b43_wldev *dev)
अणु
	b43_radio_set(dev, R2057_XTALPUOVR_PINCTRL, 0x1);

	अगर (0) /* FIXME: Is this BCM43217 specअगरic? */
		b43_radio_set(dev, R2057_XTALPUOVR_PINCTRL, 0x2);

	b43_radio_set(dev, R2057_RFPLL_MISC_CAL_RESETN, 0x78);
	b43_radio_set(dev, R2057_XTAL_CONFIG2, 0x80);
	usleep_range(2000, 3000);
	b43_radio_mask(dev, R2057_RFPLL_MISC_CAL_RESETN, ~0x78);
	b43_radio_mask(dev, R2057_XTAL_CONFIG2, ~0x80);

	अगर (dev->phy.करो_full_init) अणु
		b43_radio_2057_rcal(dev);
		b43_radio_2057_rccal(dev);
	पूर्ण
	b43_radio_mask(dev, R2057_RFPLL_MASTER, ~0x8);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/Radio/2057/Init */
अटल व्योम b43_radio_2057_init(काष्ठा b43_wldev *dev)
अणु
	b43_radio_2057_init_pre(dev);
	r2057_upload_inittअसल(dev);
	b43_radio_2057_init_post(dev);
पूर्ण

/**************************************************
 * Radio 0x2056
 **************************************************/

अटल व्योम b43_chantab_radio_2056_upload(काष्ठा b43_wldev *dev,
				स्थिर काष्ठा b43_nphy_channeltab_entry_rev3 *e)
अणु
	b43_radio_ग_लिखो(dev, B2056_SYN_PLL_VCOCAL1, e->radio_syn_pll_vcocal1);
	b43_radio_ग_लिखो(dev, B2056_SYN_PLL_VCOCAL2, e->radio_syn_pll_vcocal2);
	b43_radio_ग_लिखो(dev, B2056_SYN_PLL_REFDIV, e->radio_syn_pll_refभाग);
	b43_radio_ग_लिखो(dev, B2056_SYN_PLL_MMD2, e->radio_syn_pll_mmd2);
	b43_radio_ग_लिखो(dev, B2056_SYN_PLL_MMD1, e->radio_syn_pll_mmd1);
	b43_radio_ग_लिखो(dev, B2056_SYN_PLL_LOOPFILTER1,
					e->radio_syn_pll_loopfilter1);
	b43_radio_ग_लिखो(dev, B2056_SYN_PLL_LOOPFILTER2,
					e->radio_syn_pll_loopfilter2);
	b43_radio_ग_लिखो(dev, B2056_SYN_PLL_LOOPFILTER3,
					e->radio_syn_pll_loopfilter3);
	b43_radio_ग_लिखो(dev, B2056_SYN_PLL_LOOPFILTER4,
					e->radio_syn_pll_loopfilter4);
	b43_radio_ग_लिखो(dev, B2056_SYN_PLL_LOOPFILTER5,
					e->radio_syn_pll_loopfilter5);
	b43_radio_ग_लिखो(dev, B2056_SYN_RESERVED_ADDR27,
					e->radio_syn_reserved_addr27);
	b43_radio_ग_लिखो(dev, B2056_SYN_RESERVED_ADDR28,
					e->radio_syn_reserved_addr28);
	b43_radio_ग_लिखो(dev, B2056_SYN_RESERVED_ADDR29,
					e->radio_syn_reserved_addr29);
	b43_radio_ग_लिखो(dev, B2056_SYN_LOGEN_VCOBUF1,
					e->radio_syn_logen_vcobuf1);
	b43_radio_ग_लिखो(dev, B2056_SYN_LOGEN_MIXER2, e->radio_syn_logen_mixer2);
	b43_radio_ग_लिखो(dev, B2056_SYN_LOGEN_BUF3, e->radio_syn_logen_buf3);
	b43_radio_ग_लिखो(dev, B2056_SYN_LOGEN_BUF4, e->radio_syn_logen_buf4);

	b43_radio_ग_लिखो(dev, B2056_RX0 | B2056_RX_LNAA_TUNE,
					e->radio_rx0_lnaa_tune);
	b43_radio_ग_लिखो(dev, B2056_RX0 | B2056_RX_LNAG_TUNE,
					e->radio_rx0_lnag_tune);

	b43_radio_ग_लिखो(dev, B2056_TX0 | B2056_TX_INTPAA_BOOST_TUNE,
					e->radio_tx0_पूर्णांकpaa_boost_tune);
	b43_radio_ग_लिखो(dev, B2056_TX0 | B2056_TX_INTPAG_BOOST_TUNE,
					e->radio_tx0_पूर्णांकpag_boost_tune);
	b43_radio_ग_लिखो(dev, B2056_TX0 | B2056_TX_PADA_BOOST_TUNE,
					e->radio_tx0_pada_boost_tune);
	b43_radio_ग_लिखो(dev, B2056_TX0 | B2056_TX_PADG_BOOST_TUNE,
					e->radio_tx0_padg_boost_tune);
	b43_radio_ग_लिखो(dev, B2056_TX0 | B2056_TX_PGAA_BOOST_TUNE,
					e->radio_tx0_pgaa_boost_tune);
	b43_radio_ग_लिखो(dev, B2056_TX0 | B2056_TX_PGAG_BOOST_TUNE,
					e->radio_tx0_pgag_boost_tune);
	b43_radio_ग_लिखो(dev, B2056_TX0 | B2056_TX_MIXA_BOOST_TUNE,
					e->radio_tx0_mixa_boost_tune);
	b43_radio_ग_लिखो(dev, B2056_TX0 | B2056_TX_MIXG_BOOST_TUNE,
					e->radio_tx0_mixg_boost_tune);

	b43_radio_ग_लिखो(dev, B2056_RX1 | B2056_RX_LNAA_TUNE,
					e->radio_rx1_lnaa_tune);
	b43_radio_ग_लिखो(dev, B2056_RX1 | B2056_RX_LNAG_TUNE,
					e->radio_rx1_lnag_tune);

	b43_radio_ग_लिखो(dev, B2056_TX1 | B2056_TX_INTPAA_BOOST_TUNE,
					e->radio_tx1_पूर्णांकpaa_boost_tune);
	b43_radio_ग_लिखो(dev, B2056_TX1 | B2056_TX_INTPAG_BOOST_TUNE,
					e->radio_tx1_पूर्णांकpag_boost_tune);
	b43_radio_ग_लिखो(dev, B2056_TX1 | B2056_TX_PADA_BOOST_TUNE,
					e->radio_tx1_pada_boost_tune);
	b43_radio_ग_लिखो(dev, B2056_TX1 | B2056_TX_PADG_BOOST_TUNE,
					e->radio_tx1_padg_boost_tune);
	b43_radio_ग_लिखो(dev, B2056_TX1 | B2056_TX_PGAA_BOOST_TUNE,
					e->radio_tx1_pgaa_boost_tune);
	b43_radio_ग_लिखो(dev, B2056_TX1 | B2056_TX_PGAG_BOOST_TUNE,
					e->radio_tx1_pgag_boost_tune);
	b43_radio_ग_लिखो(dev, B2056_TX1 | B2056_TX_MIXA_BOOST_TUNE,
					e->radio_tx1_mixa_boost_tune);
	b43_radio_ग_लिखो(dev, B2056_TX1 | B2056_TX_MIXG_BOOST_TUNE,
					e->radio_tx1_mixg_boost_tune);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/Radio/2056Setup */
अटल व्योम b43_radio_2056_setup(काष्ठा b43_wldev *dev,
				स्थिर काष्ठा b43_nphy_channeltab_entry_rev3 *e)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा ssb_sprom *sprom = dev->dev->bus_sprom;
	क्रमागत nl80211_band band = b43_current_band(dev->wl);
	u16 offset;
	u8 i;
	u16 bias, cbias;
	u16 pag_boost, padg_boost, pgag_boost, mixg_boost;
	u16 paa_boost, pada_boost, pgaa_boost, mixa_boost;
	bool is_pkg_fab_smic;

	B43_WARN_ON(dev->phy.rev < 3);

	is_pkg_fab_smic =
		((dev->dev->chip_id == BCMA_CHIP_ID_BCM43224 ||
		  dev->dev->chip_id == BCMA_CHIP_ID_BCM43225 ||
		  dev->dev->chip_id == BCMA_CHIP_ID_BCM43421) &&
		 dev->dev->chip_pkg == BCMA_PKG_ID_BCM43224_FAB_SMIC);

	b43_chantab_radio_2056_upload(dev, e);
	b2056_upload_syn_pll_cp2(dev, band == NL80211_BAND_5GHZ);

	अगर (sprom->boardflags2_lo & B43_BFL2_GPLL_WAR &&
	    b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
		b43_radio_ग_लिखो(dev, B2056_SYN_PLL_LOOPFILTER1, 0x1F);
		b43_radio_ग_लिखो(dev, B2056_SYN_PLL_LOOPFILTER2, 0x1F);
		अगर (dev->dev->chip_id == BCMA_CHIP_ID_BCM4716 ||
		    dev->dev->chip_id == BCMA_CHIP_ID_BCM47162) अणु
			b43_radio_ग_लिखो(dev, B2056_SYN_PLL_LOOPFILTER4, 0x14);
			b43_radio_ग_लिखो(dev, B2056_SYN_PLL_CP2, 0);
		पूर्ण अन्यथा अणु
			b43_radio_ग_लिखो(dev, B2056_SYN_PLL_LOOPFILTER4, 0x0B);
			b43_radio_ग_लिखो(dev, B2056_SYN_PLL_CP2, 0x14);
		पूर्ण
	पूर्ण
	अगर (sprom->boardflags2_hi & B43_BFH2_GPLL_WAR2 &&
	    b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
		b43_radio_ग_लिखो(dev, B2056_SYN_PLL_LOOPFILTER1, 0x1f);
		b43_radio_ग_लिखो(dev, B2056_SYN_PLL_LOOPFILTER2, 0x1f);
		b43_radio_ग_लिखो(dev, B2056_SYN_PLL_LOOPFILTER4, 0x0b);
		b43_radio_ग_लिखो(dev, B2056_SYN_PLL_CP2, 0x20);
	पूर्ण
	अगर (sprom->boardflags2_lo & B43_BFL2_APLL_WAR &&
	    b43_current_band(dev->wl) == NL80211_BAND_5GHZ) अणु
		b43_radio_ग_लिखो(dev, B2056_SYN_PLL_LOOPFILTER1, 0x1F);
		b43_radio_ग_लिखो(dev, B2056_SYN_PLL_LOOPFILTER2, 0x1F);
		b43_radio_ग_लिखो(dev, B2056_SYN_PLL_LOOPFILTER4, 0x05);
		b43_radio_ग_लिखो(dev, B2056_SYN_PLL_CP2, 0x0C);
	पूर्ण

	अगर (dev->phy.n->ipa2g_on && band == NL80211_BAND_2GHZ) अणु
		क्रम (i = 0; i < 2; i++) अणु
			offset = i ? B2056_TX1 : B2056_TX0;
			अगर (dev->phy.rev >= 5) अणु
				b43_radio_ग_लिखो(dev,
					offset | B2056_TX_PADG_IDAC, 0xcc);

				अगर (dev->dev->chip_id == BCMA_CHIP_ID_BCM4716 ||
				    dev->dev->chip_id == BCMA_CHIP_ID_BCM47162) अणु
					bias = 0x40;
					cbias = 0x45;
					pag_boost = 0x5;
					pgag_boost = 0x33;
					mixg_boost = 0x55;
				पूर्ण अन्यथा अणु
					bias = 0x25;
					cbias = 0x20;
					अगर (is_pkg_fab_smic) अणु
						bias = 0x2a;
						cbias = 0x38;
					पूर्ण
					pag_boost = 0x4;
					pgag_boost = 0x03;
					mixg_boost = 0x65;
				पूर्ण
				padg_boost = 0x77;

				b43_radio_ग_लिखो(dev,
					offset | B2056_TX_INTPAG_IMAIN_STAT,
					bias);
				b43_radio_ग_लिखो(dev,
					offset | B2056_TX_INTPAG_IAUX_STAT,
					bias);
				b43_radio_ग_लिखो(dev,
					offset | B2056_TX_INTPAG_CASCBIAS,
					cbias);
				b43_radio_ग_लिखो(dev,
					offset | B2056_TX_INTPAG_BOOST_TUNE,
					pag_boost);
				b43_radio_ग_लिखो(dev,
					offset | B2056_TX_PGAG_BOOST_TUNE,
					pgag_boost);
				b43_radio_ग_लिखो(dev,
					offset | B2056_TX_PADG_BOOST_TUNE,
					padg_boost);
				b43_radio_ग_लिखो(dev,
					offset | B2056_TX_MIXG_BOOST_TUNE,
					mixg_boost);
			पूर्ण अन्यथा अणु
				bias = b43_is_40mhz(dev) ? 0x40 : 0x20;
				b43_radio_ग_लिखो(dev,
					offset | B2056_TX_INTPAG_IMAIN_STAT,
					bias);
				b43_radio_ग_लिखो(dev,
					offset | B2056_TX_INTPAG_IAUX_STAT,
					bias);
				b43_radio_ग_लिखो(dev,
					offset | B2056_TX_INTPAG_CASCBIAS,
					0x30);
			पूर्ण
			b43_radio_ग_लिखो(dev, offset | B2056_TX_PA_SPARE1, 0xee);
		पूर्ण
	पूर्ण अन्यथा अगर (dev->phy.n->ipa5g_on && band == NL80211_BAND_5GHZ) अणु
		u16 freq = phy->chandef->chan->center_freq;
		अगर (freq < 5100) अणु
			paa_boost = 0xA;
			pada_boost = 0x77;
			pgaa_boost = 0xF;
			mixa_boost = 0xF;
		पूर्ण अन्यथा अगर (freq < 5340) अणु
			paa_boost = 0x8;
			pada_boost = 0x77;
			pgaa_boost = 0xFB;
			mixa_boost = 0xF;
		पूर्ण अन्यथा अगर (freq < 5650) अणु
			paa_boost = 0x0;
			pada_boost = 0x77;
			pgaa_boost = 0xB;
			mixa_boost = 0xF;
		पूर्ण अन्यथा अणु
			paa_boost = 0x0;
			pada_boost = 0x77;
			अगर (freq != 5825)
				pgaa_boost = -(freq - 18) / 36 + 168;
			अन्यथा
				pgaa_boost = 6;
			mixa_boost = 0xF;
		पूर्ण

		cbias = is_pkg_fab_smic ? 0x35 : 0x30;

		क्रम (i = 0; i < 2; i++) अणु
			offset = i ? B2056_TX1 : B2056_TX0;

			b43_radio_ग_लिखो(dev,
				offset | B2056_TX_INTPAA_BOOST_TUNE, paa_boost);
			b43_radio_ग_लिखो(dev,
				offset | B2056_TX_PADA_BOOST_TUNE, pada_boost);
			b43_radio_ग_लिखो(dev,
				offset | B2056_TX_PGAA_BOOST_TUNE, pgaa_boost);
			b43_radio_ग_लिखो(dev,
				offset | B2056_TX_MIXA_BOOST_TUNE, mixa_boost);
			b43_radio_ग_लिखो(dev,
				offset | B2056_TX_TXSPARE1, 0x30);
			b43_radio_ग_लिखो(dev,
				offset | B2056_TX_PA_SPARE2, 0xee);
			b43_radio_ग_लिखो(dev,
				offset | B2056_TX_PADA_CASCBIAS, 0x03);
			b43_radio_ग_लिखो(dev,
				offset | B2056_TX_INTPAA_IAUX_STAT, 0x30);
			b43_radio_ग_लिखो(dev,
				offset | B2056_TX_INTPAA_IMAIN_STAT, 0x30);
			b43_radio_ग_लिखो(dev,
				offset | B2056_TX_INTPAA_CASCBIAS, cbias);
		पूर्ण
	पूर्ण

	udelay(50);
	/* VCO calibration */
	b43_radio_ग_लिखो(dev, B2056_SYN_PLL_VCOCAL12, 0x00);
	b43_radio_ग_लिखो(dev, B2056_TX_INTPAA_PA_MISC, 0x38);
	b43_radio_ग_लिखो(dev, B2056_TX_INTPAA_PA_MISC, 0x18);
	b43_radio_ग_लिखो(dev, B2056_TX_INTPAA_PA_MISC, 0x38);
	b43_radio_ग_लिखो(dev, B2056_TX_INTPAA_PA_MISC, 0x39);
	udelay(300);
पूर्ण

अटल u8 b43_radio_2056_rcal(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	u16 mast2, पंचांगp;

	अगर (phy->rev != 3)
		वापस 0;

	mast2 = b43_radio_पढ़ो(dev, B2056_SYN_PLL_MAST2);
	b43_radio_ग_लिखो(dev, B2056_SYN_PLL_MAST2, mast2 | 0x7);

	udelay(10);
	b43_radio_ग_लिखो(dev, B2056_SYN_RCAL_MASTER, 0x01);
	udelay(10);
	b43_radio_ग_लिखो(dev, B2056_SYN_RCAL_MASTER, 0x09);

	अगर (!b43_radio_रुको_value(dev, B2056_SYN_RCAL_CODE_OUT, 0x80, 0x80, 100,
				  1000000)) अणु
		b43err(dev->wl, "Radio recalibration timeout\n");
		वापस 0;
	पूर्ण

	b43_radio_ग_लिखो(dev, B2056_SYN_RCAL_MASTER, 0x01);
	पंचांगp = b43_radio_पढ़ो(dev, B2056_SYN_RCAL_CODE_OUT);
	b43_radio_ग_लिखो(dev, B2056_SYN_RCAL_MASTER, 0x00);

	b43_radio_ग_लिखो(dev, B2056_SYN_PLL_MAST2, mast2);

	वापस पंचांगp & 0x1f;
पूर्ण

अटल व्योम b43_radio_init2056_pre(काष्ठा b43_wldev *dev)
अणु
	b43_phy_mask(dev, B43_NPHY_RFCTL_CMD,
		     ~B43_NPHY_RFCTL_CMD_CHIP0PU);
	/* Maybe wl meant to reset and set (order?) RFCTL_CMD_OEPORFORCE? */
	b43_phy_mask(dev, B43_NPHY_RFCTL_CMD,
		     B43_NPHY_RFCTL_CMD_OEPORFORCE);
	b43_phy_set(dev, B43_NPHY_RFCTL_CMD,
		    ~B43_NPHY_RFCTL_CMD_OEPORFORCE);
	b43_phy_set(dev, B43_NPHY_RFCTL_CMD,
		    B43_NPHY_RFCTL_CMD_CHIP0PU);
पूर्ण

अटल व्योम b43_radio_init2056_post(काष्ठा b43_wldev *dev)
अणु
	b43_radio_set(dev, B2056_SYN_COM_CTRL, 0xB);
	b43_radio_set(dev, B2056_SYN_COM_PU, 0x2);
	b43_radio_set(dev, B2056_SYN_COM_RESET, 0x2);
	msleep(1);
	b43_radio_mask(dev, B2056_SYN_COM_RESET, ~0x2);
	b43_radio_mask(dev, B2056_SYN_PLL_MAST2, ~0xFC);
	b43_radio_mask(dev, B2056_SYN_RCCAL_CTRL0, ~0x1);
	अगर (dev->phy.करो_full_init)
		b43_radio_2056_rcal(dev);
पूर्ण

/*
 * Initialize a Broadcom 2056 N-radio
 * https://bcm-v4.sipsolutions.net/802.11/Radio/2056/Init
 */
अटल व्योम b43_radio_init2056(काष्ठा b43_wldev *dev)
अणु
	b43_radio_init2056_pre(dev);
	b2056_upload_inittअसल(dev, 0, 0);
	b43_radio_init2056_post(dev);
पूर्ण

/**************************************************
 * Radio 0x2055
 **************************************************/

अटल व्योम b43_chantab_radio_upload(काष्ठा b43_wldev *dev,
				स्थिर काष्ठा b43_nphy_channeltab_entry_rev2 *e)
अणु
	b43_radio_ग_लिखो(dev, B2055_PLL_REF, e->radio_pll_ref);
	b43_radio_ग_लिखो(dev, B2055_RF_PLLMOD0, e->radio_rf_pllmod0);
	b43_radio_ग_लिखो(dev, B2055_RF_PLLMOD1, e->radio_rf_pllmod1);
	b43_radio_ग_लिखो(dev, B2055_VCO_CAPTAIL, e->radio_vco_captail);
	b43_पढ़ो32(dev, B43_MMIO_MACCTL); /* flush ग_लिखोs */

	b43_radio_ग_लिखो(dev, B2055_VCO_CAL1, e->radio_vco_cal1);
	b43_radio_ग_लिखो(dev, B2055_VCO_CAL2, e->radio_vco_cal2);
	b43_radio_ग_लिखो(dev, B2055_PLL_LFC1, e->radio_pll_lfc1);
	b43_radio_ग_लिखो(dev, B2055_PLL_LFR1, e->radio_pll_lfr1);
	b43_पढ़ो32(dev, B43_MMIO_MACCTL); /* flush ग_लिखोs */

	b43_radio_ग_लिखो(dev, B2055_PLL_LFC2, e->radio_pll_lfc2);
	b43_radio_ग_लिखो(dev, B2055_LGBUF_CENBUF, e->radio_lgbuf_cenbuf);
	b43_radio_ग_लिखो(dev, B2055_LGEN_TUNE1, e->radio_lgen_tune1);
	b43_radio_ग_लिखो(dev, B2055_LGEN_TUNE2, e->radio_lgen_tune2);
	b43_पढ़ो32(dev, B43_MMIO_MACCTL); /* flush ग_लिखोs */

	b43_radio_ग_लिखो(dev, B2055_C1_LGBUF_ATUNE, e->radio_c1_lgbuf_atune);
	b43_radio_ग_लिखो(dev, B2055_C1_LGBUF_GTUNE, e->radio_c1_lgbuf_gtune);
	b43_radio_ग_लिखो(dev, B2055_C1_RX_RFR1, e->radio_c1_rx_rfr1);
	b43_radio_ग_लिखो(dev, B2055_C1_TX_PGAPADTN, e->radio_c1_tx_pgapadtn);
	b43_पढ़ो32(dev, B43_MMIO_MACCTL); /* flush ग_लिखोs */

	b43_radio_ग_लिखो(dev, B2055_C1_TX_MXBGTRIM, e->radio_c1_tx_mxbgtrim);
	b43_radio_ग_लिखो(dev, B2055_C2_LGBUF_ATUNE, e->radio_c2_lgbuf_atune);
	b43_radio_ग_लिखो(dev, B2055_C2_LGBUF_GTUNE, e->radio_c2_lgbuf_gtune);
	b43_radio_ग_लिखो(dev, B2055_C2_RX_RFR1, e->radio_c2_rx_rfr1);
	b43_पढ़ो32(dev, B43_MMIO_MACCTL); /* flush ग_लिखोs */

	b43_radio_ग_लिखो(dev, B2055_C2_TX_PGAPADTN, e->radio_c2_tx_pgapadtn);
	b43_radio_ग_लिखो(dev, B2055_C2_TX_MXBGTRIM, e->radio_c2_tx_mxbgtrim);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/Radio/2055Setup */
अटल व्योम b43_radio_2055_setup(काष्ठा b43_wldev *dev,
				स्थिर काष्ठा b43_nphy_channeltab_entry_rev2 *e)
अणु
	B43_WARN_ON(dev->phy.rev >= 3);

	b43_chantab_radio_upload(dev, e);
	udelay(50);
	b43_radio_ग_लिखो(dev, B2055_VCO_CAL10, 0x05);
	b43_radio_ग_लिखो(dev, B2055_VCO_CAL10, 0x45);
	b43_पढ़ो32(dev, B43_MMIO_MACCTL); /* flush ग_लिखोs */
	b43_radio_ग_लिखो(dev, B2055_VCO_CAL10, 0x65);
	udelay(300);
पूर्ण

अटल व्योम b43_radio_init2055_pre(काष्ठा b43_wldev *dev)
अणु
	b43_phy_mask(dev, B43_NPHY_RFCTL_CMD,
		     ~B43_NPHY_RFCTL_CMD_PORFORCE);
	b43_phy_set(dev, B43_NPHY_RFCTL_CMD,
		    B43_NPHY_RFCTL_CMD_CHIP0PU |
		    B43_NPHY_RFCTL_CMD_OEPORFORCE);
	b43_phy_set(dev, B43_NPHY_RFCTL_CMD,
		    B43_NPHY_RFCTL_CMD_PORFORCE);
पूर्ण

अटल व्योम b43_radio_init2055_post(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_n *nphy = dev->phy.n;
	काष्ठा ssb_sprom *sprom = dev->dev->bus_sprom;
	bool workaround = false;

	अगर (sprom->revision < 4)
		workaround = (dev->dev->board_venकरोr != PCI_VENDOR_ID_BROADCOM
			      && dev->dev->board_type == SSB_BOARD_CB2_4321
			      && dev->dev->board_rev >= 0x41);
	अन्यथा
		workaround =
			!(sprom->boardflags2_lo & B43_BFL2_RXBB_INT_REG_DIS);

	b43_radio_mask(dev, B2055_MASTER1, 0xFFF3);
	अगर (workaround) अणु
		b43_radio_mask(dev, B2055_C1_RX_BB_REG, 0x7F);
		b43_radio_mask(dev, B2055_C2_RX_BB_REG, 0x7F);
	पूर्ण
	b43_radio_maskset(dev, B2055_RRCCAL_NOPTSEL, 0xFFC0, 0x2C);
	b43_radio_ग_लिखो(dev, B2055_CAL_MISC, 0x3C);
	b43_radio_mask(dev, B2055_CAL_MISC, 0xFFBE);
	b43_radio_set(dev, B2055_CAL_LPOCTL, 0x80);
	b43_radio_set(dev, B2055_CAL_MISC, 0x1);
	msleep(1);
	b43_radio_set(dev, B2055_CAL_MISC, 0x40);
	अगर (!b43_radio_रुको_value(dev, B2055_CAL_COUT2, 0x80, 0x80, 10, 2000))
		b43err(dev->wl, "radio post init timeout\n");
	b43_radio_mask(dev, B2055_CAL_LPOCTL, 0xFF7F);
	b43_चयन_channel(dev, dev->phy.channel);
	b43_radio_ग_लिखो(dev, B2055_C1_RX_BB_LPF, 0x9);
	b43_radio_ग_लिखो(dev, B2055_C2_RX_BB_LPF, 0x9);
	b43_radio_ग_लिखो(dev, B2055_C1_RX_BB_MIDACHP, 0x83);
	b43_radio_ग_लिखो(dev, B2055_C2_RX_BB_MIDACHP, 0x83);
	b43_radio_maskset(dev, B2055_C1_LNA_GAINBST, 0xFFF8, 0x6);
	b43_radio_maskset(dev, B2055_C2_LNA_GAINBST, 0xFFF8, 0x6);
	अगर (!nphy->gain_boost) अणु
		b43_radio_set(dev, B2055_C1_RX_RFSPC1, 0x2);
		b43_radio_set(dev, B2055_C2_RX_RFSPC1, 0x2);
	पूर्ण अन्यथा अणु
		b43_radio_mask(dev, B2055_C1_RX_RFSPC1, 0xFFFD);
		b43_radio_mask(dev, B2055_C2_RX_RFSPC1, 0xFFFD);
	पूर्ण
	udelay(2);
पूर्ण

/*
 * Initialize a Broadcom 2055 N-radio
 * https://bcm-v4.sipsolutions.net/802.11/Radio/2055/Init
 */
अटल व्योम b43_radio_init2055(काष्ठा b43_wldev *dev)
अणु
	b43_radio_init2055_pre(dev);
	अगर (b43_status(dev) < B43_STAT_INITIALIZED) अणु
		/* Follow wl, not specs. Do not क्रमce uploading all regs */
		b2055_upload_inittab(dev, 0, 0);
	पूर्ण अन्यथा अणु
		bool ghz5 = b43_current_band(dev->wl) == NL80211_BAND_5GHZ;
		b2055_upload_inittab(dev, ghz5, 0);
	पूर्ण
	b43_radio_init2055_post(dev);
पूर्ण

/**************************************************
 * Samples
 **************************************************/

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/LoadSampleTable */
अटल पूर्णांक b43_nphy_load_samples(काष्ठा b43_wldev *dev,
					काष्ठा cordic_iq *samples, u16 len) अणु
	काष्ठा b43_phy_n *nphy = dev->phy.n;
	u16 i;
	u32 *data;

	data = kसुस्मृति(len, माप(u32), GFP_KERNEL);
	अगर (!data) अणु
		b43err(dev->wl, "allocation for samples loading failed\n");
		वापस -ENOMEM;
	पूर्ण
	अगर (nphy->hang_aव्योम)
		b43_nphy_stay_in_carrier_search(dev, 1);

	क्रम (i = 0; i < len; i++) अणु
		data[i] = (samples[i].i & 0x3FF << 10);
		data[i] |= samples[i].q & 0x3FF;
	पूर्ण
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB32(17, 0), len, data);

	kमुक्त(data);
	अगर (nphy->hang_aव्योम)
		b43_nphy_stay_in_carrier_search(dev, 0);
	वापस 0;
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/GenLoadSamples */
अटल u16 b43_nphy_gen_load_samples(काष्ठा b43_wldev *dev, u32 freq, u16 max,
					bool test)
अणु
	पूर्णांक i;
	u16 bw, len, rot, angle;
	काष्ठा cordic_iq *samples;

	bw = b43_is_40mhz(dev) ? 40 : 20;
	len = bw << 3;

	अगर (test) अणु
		अगर (b43_phy_पढ़ो(dev, B43_NPHY_BBCFG) & B43_NPHY_BBCFG_RSTRX)
			bw = 82;
		अन्यथा
			bw = 80;

		अगर (b43_is_40mhz(dev))
			bw <<= 1;

		len = bw << 1;
	पूर्ण

	samples = kसुस्मृति(len, माप(काष्ठा cordic_iq), GFP_KERNEL);
	अगर (!samples) अणु
		b43err(dev->wl, "allocation for samples generation failed\n");
		वापस 0;
	पूर्ण
	rot = (((freq * 36) / bw) << 16) / 100;
	angle = 0;

	क्रम (i = 0; i < len; i++) अणु
		samples[i] = cordic_calc_iq(CORDIC_FIXED(angle));
		angle += rot;
		samples[i].q = CORDIC_FLOAT(samples[i].q * max);
		samples[i].i = CORDIC_FLOAT(samples[i].i * max);
	पूर्ण

	i = b43_nphy_load_samples(dev, samples, len);
	kमुक्त(samples);
	वापस (i < 0) ? 0 : len;
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/RunSamples */
अटल व्योम b43_nphy_run_samples(काष्ठा b43_wldev *dev, u16 samps, u16 loops,
				 u16 रुको, bool iqmode, bool dac_test,
				 bool modअगरy_bbmult)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_n *nphy = dev->phy.n;
	पूर्णांक i;
	u16 seq_mode;
	u32 पंचांगp;

	b43_nphy_stay_in_carrier_search(dev, true);

	अगर (phy->rev >= 7) अणु
		bool lpf_bw3, lpf_bw4;

		lpf_bw3 = b43_phy_पढ़ो(dev, B43_NPHY_REV7_RF_CTL_OVER3) & 0x80;
		lpf_bw4 = b43_phy_पढ़ो(dev, B43_NPHY_REV7_RF_CTL_OVER4) & 0x80;

		अगर (lpf_bw3 || lpf_bw4) अणु
			/* TODO */
		पूर्ण अन्यथा अणु
			u16 value = b43_nphy_पढ़ो_lpf_ctl(dev, 0);
			अगर (phy->rev >= 19)
				b43_nphy_rf_ctl_override_rev19(dev, 0x80, value,
							       0, false, 1);
			अन्यथा
				b43_nphy_rf_ctl_override_rev7(dev, 0x80, value,
							      0, false, 1);
			nphy->lpf_bw_overrode_क्रम_sample_play = true;
		पूर्ण
	पूर्ण

	अगर ((nphy->bb_mult_save & 0x80000000) == 0) अणु
		पंचांगp = b43_ntab_पढ़ो(dev, B43_NTAB16(15, 87));
		nphy->bb_mult_save = (पंचांगp & 0xFFFF) | 0x80000000;
	पूर्ण

	अगर (modअगरy_bbmult) अणु
		पंचांगp = !b43_is_40mhz(dev) ? 0x6464 : 0x4747;
		b43_ntab_ग_लिखो(dev, B43_NTAB16(15, 87), पंचांगp);
	पूर्ण

	b43_phy_ग_लिखो(dev, B43_NPHY_SAMP_DEPCNT, (samps - 1));

	अगर (loops != 0xFFFF)
		b43_phy_ग_लिखो(dev, B43_NPHY_SAMP_LOOPCNT, (loops - 1));
	अन्यथा
		b43_phy_ग_लिखो(dev, B43_NPHY_SAMP_LOOPCNT, loops);

	b43_phy_ग_लिखो(dev, B43_NPHY_SAMP_WAITCNT, रुको);

	seq_mode = b43_phy_पढ़ो(dev, B43_NPHY_RFSEQMODE);

	b43_phy_set(dev, B43_NPHY_RFSEQMODE, B43_NPHY_RFSEQMODE_CAOVER);
	अगर (iqmode) अणु
		b43_phy_mask(dev, B43_NPHY_IQLOCAL_CMDGCTL, 0x7FFF);
		b43_phy_set(dev, B43_NPHY_IQLOCAL_CMDGCTL, 0x8000);
	पूर्ण अन्यथा अणु
		पंचांगp = dac_test ? 5 : 1;
		b43_phy_ग_लिखो(dev, B43_NPHY_SAMP_CMD, पंचांगp);
	पूर्ण
	क्रम (i = 0; i < 100; i++) अणु
		अगर (!(b43_phy_पढ़ो(dev, B43_NPHY_RFSEQST) & 1)) अणु
			i = 0;
			अवरोध;
		पूर्ण
		udelay(10);
	पूर्ण
	अगर (i)
		b43err(dev->wl, "run samples timeout\n");

	b43_phy_ग_लिखो(dev, B43_NPHY_RFSEQMODE, seq_mode);

	b43_nphy_stay_in_carrier_search(dev, false);
पूर्ण

/**************************************************
 * RSSI
 **************************************************/

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/ScaleOffsetRssi */
अटल व्योम b43_nphy_scale_offset_rssi(काष्ठा b43_wldev *dev, u16 scale,
					s8 offset, u8 core,
					क्रमागत n_rail_type rail,
					क्रमागत n_rssi_type rssi_type)
अणु
	u16 पंचांगp;
	bool core1or5 = (core == 1) || (core == 5);
	bool core2or5 = (core == 2) || (core == 5);

	offset = clamp_val(offset, -32, 31);
	पंचांगp = ((scale & 0x3F) << 8) | (offset & 0x3F);

	चयन (rssi_type) अणु
	हाल N_RSSI_NB:
		अगर (core1or5 && rail == N_RAIL_I)
			b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_0I_RSSI_Z, पंचांगp);
		अगर (core1or5 && rail == N_RAIL_Q)
			b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_0Q_RSSI_Z, पंचांगp);
		अगर (core2or5 && rail == N_RAIL_I)
			b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_1I_RSSI_Z, पंचांगp);
		अगर (core2or5 && rail == N_RAIL_Q)
			b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_1Q_RSSI_Z, पंचांगp);
		अवरोध;
	हाल N_RSSI_W1:
		अगर (core1or5 && rail == N_RAIL_I)
			b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_0I_RSSI_X, पंचांगp);
		अगर (core1or5 && rail == N_RAIL_Q)
			b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_0Q_RSSI_X, पंचांगp);
		अगर (core2or5 && rail == N_RAIL_I)
			b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_1I_RSSI_X, पंचांगp);
		अगर (core2or5 && rail == N_RAIL_Q)
			b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_1Q_RSSI_X, पंचांगp);
		अवरोध;
	हाल N_RSSI_W2:
		अगर (core1or5 && rail == N_RAIL_I)
			b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_0I_RSSI_Y, पंचांगp);
		अगर (core1or5 && rail == N_RAIL_Q)
			b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_0Q_RSSI_Y, पंचांगp);
		अगर (core2or5 && rail == N_RAIL_I)
			b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_1I_RSSI_Y, पंचांगp);
		अगर (core2or5 && rail == N_RAIL_Q)
			b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_1Q_RSSI_Y, पंचांगp);
		अवरोध;
	हाल N_RSSI_TBD:
		अगर (core1or5 && rail == N_RAIL_I)
			b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_0I_TBD, पंचांगp);
		अगर (core1or5 && rail == N_RAIL_Q)
			b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_0Q_TBD, पंचांगp);
		अगर (core2or5 && rail == N_RAIL_I)
			b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_1I_TBD, पंचांगp);
		अगर (core2or5 && rail == N_RAIL_Q)
			b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_1Q_TBD, पंचांगp);
		अवरोध;
	हाल N_RSSI_IQ:
		अगर (core1or5 && rail == N_RAIL_I)
			b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_0I_PWRDET, पंचांगp);
		अगर (core1or5 && rail == N_RAIL_Q)
			b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_0Q_PWRDET, पंचांगp);
		अगर (core2or5 && rail == N_RAIL_I)
			b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_1I_PWRDET, पंचांगp);
		अगर (core2or5 && rail == N_RAIL_Q)
			b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_1Q_PWRDET, पंचांगp);
		अवरोध;
	हाल N_RSSI_TSSI_2G:
		अगर (core1or5)
			b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_0I_TSSI, पंचांगp);
		अगर (core2or5)
			b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_1I_TSSI, पंचांगp);
		अवरोध;
	हाल N_RSSI_TSSI_5G:
		अगर (core1or5)
			b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_0Q_TSSI, पंचांगp);
		अगर (core2or5)
			b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_1Q_TSSI, पंचांगp);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम b43_nphy_rssi_select_rev19(काष्ठा b43_wldev *dev, u8 code,
				       क्रमागत n_rssi_type rssi_type)
अणु
	/* TODO */
पूर्ण

अटल व्योम b43_nphy_rev3_rssi_select(काष्ठा b43_wldev *dev, u8 code,
				      क्रमागत n_rssi_type rssi_type)
अणु
	u8 i;
	u16 reg, val;

	अगर (code == 0) अणु
		b43_phy_mask(dev, B43_NPHY_AFECTL_OVER1, 0xFDFF);
		b43_phy_mask(dev, B43_NPHY_AFECTL_OVER, 0xFDFF);
		b43_phy_mask(dev, B43_NPHY_AFECTL_C1, 0xFCFF);
		b43_phy_mask(dev, B43_NPHY_AFECTL_C2, 0xFCFF);
		b43_phy_mask(dev, B43_NPHY_TXF_40CO_B1S0, 0xFFDF);
		b43_phy_mask(dev, B43_NPHY_TXF_40CO_B32S1, 0xFFDF);
		b43_phy_mask(dev, B43_NPHY_RFCTL_LUT_TRSW_UP1, 0xFFC3);
		b43_phy_mask(dev, B43_NPHY_RFCTL_LUT_TRSW_UP2, 0xFFC3);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 2; i++) अणु
			अगर ((code == 1 && i == 1) || (code == 2 && !i))
				जारी;

			reg = (i == 0) ?
				B43_NPHY_AFECTL_OVER1 : B43_NPHY_AFECTL_OVER;
			b43_phy_maskset(dev, reg, 0xFDFF, 0x0200);

			अगर (rssi_type == N_RSSI_W1 ||
			    rssi_type == N_RSSI_W2 ||
			    rssi_type == N_RSSI_NB) अणु
				reg = (i == 0) ?
					B43_NPHY_AFECTL_C1 :
					B43_NPHY_AFECTL_C2;
				b43_phy_maskset(dev, reg, 0xFCFF, 0);

				reg = (i == 0) ?
					B43_NPHY_RFCTL_LUT_TRSW_UP1 :
					B43_NPHY_RFCTL_LUT_TRSW_UP2;
				b43_phy_maskset(dev, reg, 0xFFC3, 0);

				अगर (rssi_type == N_RSSI_W1)
					val = (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) ? 4 : 8;
				अन्यथा अगर (rssi_type == N_RSSI_W2)
					val = 16;
				अन्यथा
					val = 32;
				b43_phy_set(dev, reg, val);

				reg = (i == 0) ?
					B43_NPHY_TXF_40CO_B1S0 :
					B43_NPHY_TXF_40CO_B32S1;
				b43_phy_set(dev, reg, 0x0020);
			पूर्ण अन्यथा अणु
				अगर (rssi_type == N_RSSI_TBD)
					val = 0x0100;
				अन्यथा अगर (rssi_type == N_RSSI_IQ)
					val = 0x0200;
				अन्यथा
					val = 0x0300;

				reg = (i == 0) ?
					B43_NPHY_AFECTL_C1 :
					B43_NPHY_AFECTL_C2;

				b43_phy_maskset(dev, reg, 0xFCFF, val);
				b43_phy_maskset(dev, reg, 0xF3FF, val << 2);

				अगर (rssi_type != N_RSSI_IQ &&
				    rssi_type != N_RSSI_TBD) अणु
					क्रमागत nl80211_band band =
						b43_current_band(dev->wl);

					अगर (dev->phy.rev < 7) अणु
						अगर (b43_nphy_ipa(dev))
							val = (band == NL80211_BAND_5GHZ) ? 0xC : 0xE;
						अन्यथा
							val = 0x11;
						reg = (i == 0) ? B2056_TX0 : B2056_TX1;
						reg |= B2056_TX_TX_SSI_MUX;
						b43_radio_ग_लिखो(dev, reg, val);
					पूर्ण

					reg = (i == 0) ?
						B43_NPHY_AFECTL_OVER1 :
						B43_NPHY_AFECTL_OVER;
					b43_phy_set(dev, reg, 0x0200);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम b43_nphy_rev2_rssi_select(काष्ठा b43_wldev *dev, u8 code,
				      क्रमागत n_rssi_type rssi_type)
अणु
	u16 val;
	bool rssi_w1_w2_nb = false;

	चयन (rssi_type) अणु
	हाल N_RSSI_W1:
	हाल N_RSSI_W2:
	हाल N_RSSI_NB:
		val = 0;
		rssi_w1_w2_nb = true;
		अवरोध;
	हाल N_RSSI_TBD:
		val = 1;
		अवरोध;
	हाल N_RSSI_IQ:
		val = 2;
		अवरोध;
	शेष:
		val = 3;
	पूर्ण

	val = (val << 12) | (val << 14);
	b43_phy_maskset(dev, B43_NPHY_AFECTL_C1, 0x0FFF, val);
	b43_phy_maskset(dev, B43_NPHY_AFECTL_C2, 0x0FFF, val);

	अगर (rssi_w1_w2_nb) अणु
		b43_phy_maskset(dev, B43_NPHY_RFCTL_RSSIO1, 0xFFCF,
				(rssi_type + 1) << 4);
		b43_phy_maskset(dev, B43_NPHY_RFCTL_RSSIO2, 0xFFCF,
				(rssi_type + 1) << 4);
	पूर्ण

	अगर (code == 0) अणु
		b43_phy_mask(dev, B43_NPHY_AFECTL_OVER, ~0x3000);
		अगर (rssi_w1_w2_nb) अणु
			b43_phy_mask(dev, B43_NPHY_RFCTL_CMD,
				~(B43_NPHY_RFCTL_CMD_RXEN |
				  B43_NPHY_RFCTL_CMD_CORESEL));
			b43_phy_mask(dev, B43_NPHY_RFCTL_OVER,
				~(0x1 << 12 |
				  0x1 << 5 |
				  0x1 << 1 |
				  0x1));
			b43_phy_mask(dev, B43_NPHY_RFCTL_CMD,
				~B43_NPHY_RFCTL_CMD_START);
			udelay(20);
			b43_phy_mask(dev, B43_NPHY_RFCTL_OVER, ~0x1);
		पूर्ण
	पूर्ण अन्यथा अणु
		b43_phy_set(dev, B43_NPHY_AFECTL_OVER, 0x3000);
		अगर (rssi_w1_w2_nb) अणु
			b43_phy_maskset(dev, B43_NPHY_RFCTL_CMD,
				~(B43_NPHY_RFCTL_CMD_RXEN |
				  B43_NPHY_RFCTL_CMD_CORESEL),
				(B43_NPHY_RFCTL_CMD_RXEN |
				 code << B43_NPHY_RFCTL_CMD_CORESEL_SHIFT));
			b43_phy_set(dev, B43_NPHY_RFCTL_OVER,
				(0x1 << 12 |
				  0x1 << 5 |
				  0x1 << 1 |
				  0x1));
			b43_phy_set(dev, B43_NPHY_RFCTL_CMD,
				B43_NPHY_RFCTL_CMD_START);
			udelay(20);
			b43_phy_mask(dev, B43_NPHY_RFCTL_OVER, ~0x1);
		पूर्ण
	पूर्ण
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/RSSISel */
अटल व्योम b43_nphy_rssi_select(काष्ठा b43_wldev *dev, u8 code,
				 क्रमागत n_rssi_type type)
अणु
	अगर (dev->phy.rev >= 19)
		b43_nphy_rssi_select_rev19(dev, code, type);
	अन्यथा अगर (dev->phy.rev >= 3)
		b43_nphy_rev3_rssi_select(dev, code, type);
	अन्यथा
		b43_nphy_rev2_rssi_select(dev, code, type);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/SetRssi2055Vcm */
अटल व्योम b43_nphy_set_rssi_2055_vcm(काष्ठा b43_wldev *dev,
				       क्रमागत n_rssi_type rssi_type, u8 *buf)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 2; i++) अणु
		अगर (rssi_type == N_RSSI_NB) अणु
			अगर (i == 0) अणु
				b43_radio_maskset(dev, B2055_C1_B0NB_RSSIVCM,
						  0xFC, buf[0]);
				b43_radio_maskset(dev, B2055_C1_RX_BB_RSSICTL5,
						  0xFC, buf[1]);
			पूर्ण अन्यथा अणु
				b43_radio_maskset(dev, B2055_C2_B0NB_RSSIVCM,
						  0xFC, buf[2 * i]);
				b43_radio_maskset(dev, B2055_C2_RX_BB_RSSICTL5,
						  0xFC, buf[2 * i + 1]);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (i == 0)
				b43_radio_maskset(dev, B2055_C1_RX_BB_RSSICTL5,
						  0xF3, buf[0] << 2);
			अन्यथा
				b43_radio_maskset(dev, B2055_C2_RX_BB_RSSICTL5,
						  0xF3, buf[2 * i + 1] << 2);
		पूर्ण
	पूर्ण
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/PollRssi */
अटल पूर्णांक b43_nphy_poll_rssi(काष्ठा b43_wldev *dev, क्रमागत n_rssi_type rssi_type,
			      s32 *buf, u8 nsamp)
अणु
	पूर्णांक i;
	पूर्णांक out;
	u16 save_regs_phy[9];
	u16 s[2];

	/* TODO: rev7+ is treated like rev3+, what about rev19+? */

	अगर (dev->phy.rev >= 3) अणु
		save_regs_phy[0] = b43_phy_पढ़ो(dev, B43_NPHY_AFECTL_C1);
		save_regs_phy[1] = b43_phy_पढ़ो(dev, B43_NPHY_AFECTL_C2);
		save_regs_phy[2] = b43_phy_पढ़ो(dev,
						B43_NPHY_RFCTL_LUT_TRSW_UP1);
		save_regs_phy[3] = b43_phy_पढ़ो(dev,
						B43_NPHY_RFCTL_LUT_TRSW_UP2);
		save_regs_phy[4] = b43_phy_पढ़ो(dev, B43_NPHY_AFECTL_OVER1);
		save_regs_phy[5] = b43_phy_पढ़ो(dev, B43_NPHY_AFECTL_OVER);
		save_regs_phy[6] = b43_phy_पढ़ो(dev, B43_NPHY_TXF_40CO_B1S0);
		save_regs_phy[7] = b43_phy_पढ़ो(dev, B43_NPHY_TXF_40CO_B32S1);
		save_regs_phy[8] = 0;
	पूर्ण अन्यथा अणु
		save_regs_phy[0] = b43_phy_पढ़ो(dev, B43_NPHY_AFECTL_C1);
		save_regs_phy[1] = b43_phy_पढ़ो(dev, B43_NPHY_AFECTL_C2);
		save_regs_phy[2] = b43_phy_पढ़ो(dev, B43_NPHY_AFECTL_OVER);
		save_regs_phy[3] = b43_phy_पढ़ो(dev, B43_NPHY_RFCTL_CMD);
		save_regs_phy[4] = b43_phy_पढ़ो(dev, B43_NPHY_RFCTL_OVER);
		save_regs_phy[5] = b43_phy_पढ़ो(dev, B43_NPHY_RFCTL_RSSIO1);
		save_regs_phy[6] = b43_phy_पढ़ो(dev, B43_NPHY_RFCTL_RSSIO2);
		save_regs_phy[7] = 0;
		save_regs_phy[8] = 0;
	पूर्ण

	b43_nphy_rssi_select(dev, 5, rssi_type);

	अगर (dev->phy.rev < 2) अणु
		save_regs_phy[8] = b43_phy_पढ़ो(dev, B43_NPHY_GPIO_SEL);
		b43_phy_ग_लिखो(dev, B43_NPHY_GPIO_SEL, 5);
	पूर्ण

	क्रम (i = 0; i < 4; i++)
		buf[i] = 0;

	क्रम (i = 0; i < nsamp; i++) अणु
		अगर (dev->phy.rev < 2) अणु
			s[0] = b43_phy_पढ़ो(dev, B43_NPHY_GPIO_LOOUT);
			s[1] = b43_phy_पढ़ो(dev, B43_NPHY_GPIO_HIOUT);
		पूर्ण अन्यथा अणु
			s[0] = b43_phy_पढ़ो(dev, B43_NPHY_RSSI1);
			s[1] = b43_phy_पढ़ो(dev, B43_NPHY_RSSI2);
		पूर्ण

		buf[0] += ((s8)((s[0] & 0x3F) << 2)) >> 2;
		buf[1] += ((s8)(((s[0] >> 8) & 0x3F) << 2)) >> 2;
		buf[2] += ((s8)((s[1] & 0x3F) << 2)) >> 2;
		buf[3] += ((s8)(((s[1] >> 8) & 0x3F) << 2)) >> 2;
	पूर्ण
	out = (buf[0] & 0xFF) << 24 | (buf[1] & 0xFF) << 16 |
		(buf[2] & 0xFF) << 8 | (buf[3] & 0xFF);

	अगर (dev->phy.rev < 2)
		b43_phy_ग_लिखो(dev, B43_NPHY_GPIO_SEL, save_regs_phy[8]);

	अगर (dev->phy.rev >= 3) अणु
		b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_C1, save_regs_phy[0]);
		b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_C2, save_regs_phy[1]);
		b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_LUT_TRSW_UP1,
				save_regs_phy[2]);
		b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_LUT_TRSW_UP2,
				save_regs_phy[3]);
		b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_OVER1, save_regs_phy[4]);
		b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_OVER, save_regs_phy[5]);
		b43_phy_ग_लिखो(dev, B43_NPHY_TXF_40CO_B1S0, save_regs_phy[6]);
		b43_phy_ग_लिखो(dev, B43_NPHY_TXF_40CO_B32S1, save_regs_phy[7]);
	पूर्ण अन्यथा अणु
		b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_C1, save_regs_phy[0]);
		b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_C2, save_regs_phy[1]);
		b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_OVER, save_regs_phy[2]);
		b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_CMD, save_regs_phy[3]);
		b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_OVER, save_regs_phy[4]);
		b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_RSSIO1, save_regs_phy[5]);
		b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_RSSIO2, save_regs_phy[6]);
	पूर्ण

	वापस out;
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/RSSICalRev3 */
अटल व्योम b43_nphy_rev3_rssi_cal(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_n *nphy = dev->phy.n;

	u16 saved_regs_phy_rfctl[2];
	u16 saved_regs_phy[22];
	u16 regs_to_store_rev3[] = अणु
		B43_NPHY_AFECTL_OVER1, B43_NPHY_AFECTL_OVER,
		B43_NPHY_AFECTL_C1, B43_NPHY_AFECTL_C2,
		B43_NPHY_TXF_40CO_B1S1, B43_NPHY_RFCTL_OVER,
		B43_NPHY_TXF_40CO_B1S0, B43_NPHY_TXF_40CO_B32S1,
		B43_NPHY_RFCTL_CMD,
		B43_NPHY_RFCTL_LUT_TRSW_UP1, B43_NPHY_RFCTL_LUT_TRSW_UP2,
		B43_NPHY_RFCTL_RSSIO1, B43_NPHY_RFCTL_RSSIO2
	पूर्ण;
	u16 regs_to_store_rev7[] = अणु
		B43_NPHY_AFECTL_OVER1, B43_NPHY_AFECTL_OVER,
		B43_NPHY_AFECTL_C1, B43_NPHY_AFECTL_C2,
		B43_NPHY_TXF_40CO_B1S1, B43_NPHY_RFCTL_OVER,
		B43_NPHY_REV7_RF_CTL_OVER3, B43_NPHY_REV7_RF_CTL_OVER4,
		B43_NPHY_REV7_RF_CTL_OVER5, B43_NPHY_REV7_RF_CTL_OVER6,
		0x2ff,
		B43_NPHY_TXF_40CO_B1S0, B43_NPHY_TXF_40CO_B32S1,
		B43_NPHY_RFCTL_CMD,
		B43_NPHY_RFCTL_LUT_TRSW_UP1, B43_NPHY_RFCTL_LUT_TRSW_UP2,
		B43_NPHY_REV7_RF_CTL_MISC_REG3, B43_NPHY_REV7_RF_CTL_MISC_REG4,
		B43_NPHY_REV7_RF_CTL_MISC_REG5, B43_NPHY_REV7_RF_CTL_MISC_REG6,
		B43_NPHY_RFCTL_RSSIO1, B43_NPHY_RFCTL_RSSIO2
	पूर्ण;
	u16 *regs_to_store;
	पूर्णांक regs_amount;

	u16 class;

	u16 clip_state[2];
	u16 clip_off[2] = अणु 0xFFFF, 0xFFFF पूर्ण;

	u8 vcm_final = 0;
	s32 offset[4];
	s32 results[8][4] = अणु पूर्ण;
	s32 results_min[4] = अणु पूर्ण;
	s32 poll_results[4] = अणु पूर्ण;

	u16 *rssical_radio_regs = शून्य;
	u16 *rssical_phy_regs = शून्य;

	u16 r; /* routing */
	u8 rx_core_state;
	पूर्णांक core, i, j, vcm;

	अगर (dev->phy.rev >= 7) अणु
		regs_to_store = regs_to_store_rev7;
		regs_amount = ARRAY_SIZE(regs_to_store_rev7);
	पूर्ण अन्यथा अणु
		regs_to_store = regs_to_store_rev3;
		regs_amount = ARRAY_SIZE(regs_to_store_rev3);
	पूर्ण
	BUG_ON(regs_amount > ARRAY_SIZE(saved_regs_phy));

	class = b43_nphy_classअगरier(dev, 0, 0);
	b43_nphy_classअगरier(dev, 7, 4);
	b43_nphy_पढ़ो_clip_detection(dev, clip_state);
	b43_nphy_ग_लिखो_clip_detection(dev, clip_off);

	saved_regs_phy_rfctl[0] = b43_phy_पढ़ो(dev, B43_NPHY_RFCTL_INTC1);
	saved_regs_phy_rfctl[1] = b43_phy_पढ़ो(dev, B43_NPHY_RFCTL_INTC2);
	क्रम (i = 0; i < regs_amount; i++)
		saved_regs_phy[i] = b43_phy_पढ़ो(dev, regs_to_store[i]);

	b43_nphy_rf_ctl_पूर्णांकc_override(dev, N_INTC_OVERRIDE_OFF, 0, 7);
	b43_nphy_rf_ctl_पूर्णांकc_override(dev, N_INTC_OVERRIDE_TRSW, 1, 7);

	अगर (dev->phy.rev >= 7) अणु
		b43_nphy_rf_ctl_override_one_to_many(dev,
						     N_RF_CTL_OVER_CMD_RXRF_PU,
						     0, 0, false);
		b43_nphy_rf_ctl_override_one_to_many(dev,
						     N_RF_CTL_OVER_CMD_RX_PU,
						     1, 0, false);
		b43_nphy_rf_ctl_override_rev7(dev, 0x80, 1, 0, false, 0);
		b43_nphy_rf_ctl_override_rev7(dev, 0x40, 1, 0, false, 0);
		अगर (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) अणु
			b43_nphy_rf_ctl_override_rev7(dev, 0x20, 0, 0, false,
						      0);
			b43_nphy_rf_ctl_override_rev7(dev, 0x10, 1, 0, false,
						      0);
		पूर्ण अन्यथा अणु
			b43_nphy_rf_ctl_override_rev7(dev, 0x10, 0, 0, false,
						      0);
			b43_nphy_rf_ctl_override_rev7(dev, 0x20, 1, 0, false,
						      0);
		पूर्ण
	पूर्ण अन्यथा अणु
		b43_nphy_rf_ctl_override(dev, 0x1, 0, 0, false);
		b43_nphy_rf_ctl_override(dev, 0x2, 1, 0, false);
		b43_nphy_rf_ctl_override(dev, 0x80, 1, 0, false);
		b43_nphy_rf_ctl_override(dev, 0x40, 1, 0, false);
		अगर (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) अणु
			b43_nphy_rf_ctl_override(dev, 0x20, 0, 0, false);
			b43_nphy_rf_ctl_override(dev, 0x10, 1, 0, false);
		पूर्ण अन्यथा अणु
			b43_nphy_rf_ctl_override(dev, 0x10, 0, 0, false);
			b43_nphy_rf_ctl_override(dev, 0x20, 1, 0, false);
		पूर्ण
	पूर्ण

	rx_core_state = b43_nphy_get_rx_core_state(dev);
	क्रम (core = 0; core < 2; core++) अणु
		अगर (!(rx_core_state & (1 << core)))
			जारी;
		r = core ? B2056_RX1 : B2056_RX0;
		b43_nphy_scale_offset_rssi(dev, 0, 0, core + 1, N_RAIL_I,
					   N_RSSI_NB);
		b43_nphy_scale_offset_rssi(dev, 0, 0, core + 1, N_RAIL_Q,
					   N_RSSI_NB);

		/* Grab RSSI results क्रम every possible VCM */
		क्रम (vcm = 0; vcm < 8; vcm++) अणु
			अगर (dev->phy.rev >= 7)
				b43_radio_maskset(dev,
						  core ? R2057_NB_MASTER_CORE1 :
							 R2057_NB_MASTER_CORE0,
						  ~R2057_VCM_MASK, vcm);
			अन्यथा
				b43_radio_maskset(dev, r | B2056_RX_RSSI_MISC,
						  0xE3, vcm << 2);
			b43_nphy_poll_rssi(dev, N_RSSI_NB, results[vcm], 8);
		पूर्ण

		/* Find out which VCM got the best results */
		क्रम (i = 0; i < 4; i += 2) अणु
			s32 currd;
			s32 mind = 0x100000;
			s32 minpoll = 249;
			u8 minvcm = 0;
			अगर (2 * core != i)
				जारी;
			क्रम (vcm = 0; vcm < 8; vcm++) अणु
				currd = results[vcm][i] * results[vcm][i] +
					results[vcm][i + 1] * results[vcm][i];
				अगर (currd < mind) अणु
					mind = currd;
					minvcm = vcm;
				पूर्ण
				अगर (results[vcm][i] < minpoll)
					minpoll = results[vcm][i];
			पूर्ण
			vcm_final = minvcm;
			results_min[i] = minpoll;
		पूर्ण

		/* Select the best VCM */
		अगर (dev->phy.rev >= 7)
			b43_radio_maskset(dev,
					  core ? R2057_NB_MASTER_CORE1 :
						 R2057_NB_MASTER_CORE0,
					  ~R2057_VCM_MASK, vcm);
		अन्यथा
			b43_radio_maskset(dev, r | B2056_RX_RSSI_MISC,
					  0xE3, vcm_final << 2);

		क्रम (i = 0; i < 4; i++) अणु
			अगर (core != i / 2)
				जारी;
			offset[i] = -results[vcm_final][i];
			अगर (offset[i] < 0)
				offset[i] = -((असल(offset[i]) + 4) / 8);
			अन्यथा
				offset[i] = (offset[i] + 4) / 8;
			अगर (results_min[i] == 248)
				offset[i] = -32;
			b43_nphy_scale_offset_rssi(dev, 0, offset[i],
						   (i / 2 == 0) ? 1 : 2,
						   (i % 2 == 0) ? N_RAIL_I : N_RAIL_Q,
						   N_RSSI_NB);
		पूर्ण
	पूर्ण

	क्रम (core = 0; core < 2; core++) अणु
		अगर (!(rx_core_state & (1 << core)))
			जारी;
		क्रम (i = 0; i < 2; i++) अणु
			b43_nphy_scale_offset_rssi(dev, 0, 0, core + 1,
						   N_RAIL_I, i);
			b43_nphy_scale_offset_rssi(dev, 0, 0, core + 1,
						   N_RAIL_Q, i);
			b43_nphy_poll_rssi(dev, i, poll_results, 8);
			क्रम (j = 0; j < 4; j++) अणु
				अगर (j / 2 == core) अणु
					offset[j] = 232 - poll_results[j];
					अगर (offset[j] < 0)
						offset[j] = -(असल(offset[j] + 4) / 8);
					अन्यथा
						offset[j] = (offset[j] + 4) / 8;
					b43_nphy_scale_offset_rssi(dev, 0,
						offset[2 * core], core + 1, j % 2, i);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_INTC1, saved_regs_phy_rfctl[0]);
	b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_INTC2, saved_regs_phy_rfctl[1]);

	b43_nphy_क्रमce_rf_sequence(dev, B43_RFSEQ_RESET2RX);

	b43_phy_set(dev, B43_NPHY_TXF_40CO_B1S1, 0x1);
	b43_phy_set(dev, B43_NPHY_RFCTL_CMD, B43_NPHY_RFCTL_CMD_START);
	b43_phy_mask(dev, B43_NPHY_TXF_40CO_B1S1, ~0x1);

	b43_phy_set(dev, B43_NPHY_RFCTL_OVER, 0x1);
	b43_phy_set(dev, B43_NPHY_RFCTL_CMD, B43_NPHY_RFCTL_CMD_RXTX);
	b43_phy_mask(dev, B43_NPHY_RFCTL_OVER, ~0x1);

	क्रम (i = 0; i < regs_amount; i++)
		b43_phy_ग_लिखो(dev, regs_to_store[i], saved_regs_phy[i]);

	/* Store क्रम future configuration */
	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
		rssical_radio_regs = nphy->rssical_cache.rssical_radio_regs_2G;
		rssical_phy_regs = nphy->rssical_cache.rssical_phy_regs_2G;
	पूर्ण अन्यथा अणु
		rssical_radio_regs = nphy->rssical_cache.rssical_radio_regs_5G;
		rssical_phy_regs = nphy->rssical_cache.rssical_phy_regs_5G;
	पूर्ण
	अगर (dev->phy.rev >= 7) अणु
		rssical_radio_regs[0] = b43_radio_पढ़ो(dev,
						       R2057_NB_MASTER_CORE0);
		rssical_radio_regs[1] = b43_radio_पढ़ो(dev,
						       R2057_NB_MASTER_CORE1);
	पूर्ण अन्यथा अणु
		rssical_radio_regs[0] = b43_radio_पढ़ो(dev, B2056_RX0 |
						       B2056_RX_RSSI_MISC);
		rssical_radio_regs[1] = b43_radio_पढ़ो(dev, B2056_RX1 |
						       B2056_RX_RSSI_MISC);
	पूर्ण
	rssical_phy_regs[0] = b43_phy_पढ़ो(dev, B43_NPHY_RSSIMC_0I_RSSI_Z);
	rssical_phy_regs[1] = b43_phy_पढ़ो(dev, B43_NPHY_RSSIMC_0Q_RSSI_Z);
	rssical_phy_regs[2] = b43_phy_पढ़ो(dev, B43_NPHY_RSSIMC_1I_RSSI_Z);
	rssical_phy_regs[3] = b43_phy_पढ़ो(dev, B43_NPHY_RSSIMC_1Q_RSSI_Z);
	rssical_phy_regs[4] = b43_phy_पढ़ो(dev, B43_NPHY_RSSIMC_0I_RSSI_X);
	rssical_phy_regs[5] = b43_phy_पढ़ो(dev, B43_NPHY_RSSIMC_0Q_RSSI_X);
	rssical_phy_regs[6] = b43_phy_पढ़ो(dev, B43_NPHY_RSSIMC_1I_RSSI_X);
	rssical_phy_regs[7] = b43_phy_पढ़ो(dev, B43_NPHY_RSSIMC_1Q_RSSI_X);
	rssical_phy_regs[8] = b43_phy_पढ़ो(dev, B43_NPHY_RSSIMC_0I_RSSI_Y);
	rssical_phy_regs[9] = b43_phy_पढ़ो(dev, B43_NPHY_RSSIMC_0Q_RSSI_Y);
	rssical_phy_regs[10] = b43_phy_पढ़ो(dev, B43_NPHY_RSSIMC_1I_RSSI_Y);
	rssical_phy_regs[11] = b43_phy_पढ़ो(dev, B43_NPHY_RSSIMC_1Q_RSSI_Y);

	/* Remember क्रम which channel we store configuration */
	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
		nphy->rssical_chanspec_2G.center_freq = phy->chandef->chan->center_freq;
	अन्यथा
		nphy->rssical_chanspec_5G.center_freq = phy->chandef->chan->center_freq;

	/* End of calibration, restore configuration */
	b43_nphy_classअगरier(dev, 7, class);
	b43_nphy_ग_लिखो_clip_detection(dev, clip_state);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/RSSICal */
अटल व्योम b43_nphy_rev2_rssi_cal(काष्ठा b43_wldev *dev, क्रमागत n_rssi_type type)
अणु
	पूर्णांक i, j, vcm;
	u8 state[4];
	u8 code, val;
	u16 class, override;
	u8 regs_save_radio[2];
	u16 regs_save_phy[2];

	s32 offset[4];
	u8 core;
	u8 rail;

	u16 clip_state[2];
	u16 clip_off[2] = अणु 0xFFFF, 0xFFFF पूर्ण;
	s32 results_min[4] = अणु पूर्ण;
	u8 vcm_final[4] = अणु पूर्ण;
	s32 results[4][4] = अणु पूर्ण;
	s32 miniq[4][2] = अणु पूर्ण;

	अगर (type == N_RSSI_NB) अणु
		code = 0;
		val = 6;
	पूर्ण अन्यथा अगर (type == N_RSSI_W1 || type == N_RSSI_W2) अणु
		code = 25;
		val = 4;
	पूर्ण अन्यथा अणु
		B43_WARN_ON(1);
		वापस;
	पूर्ण

	class = b43_nphy_classअगरier(dev, 0, 0);
	b43_nphy_classअगरier(dev, 7, 4);
	b43_nphy_पढ़ो_clip_detection(dev, clip_state);
	b43_nphy_ग_लिखो_clip_detection(dev, clip_off);

	अगर (b43_current_band(dev->wl) == NL80211_BAND_5GHZ)
		override = 0x140;
	अन्यथा
		override = 0x110;

	regs_save_phy[0] = b43_phy_पढ़ो(dev, B43_NPHY_RFCTL_INTC1);
	regs_save_radio[0] = b43_radio_पढ़ो(dev, B2055_C1_PD_RXTX);
	b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_INTC1, override);
	b43_radio_ग_लिखो(dev, B2055_C1_PD_RXTX, val);

	regs_save_phy[1] = b43_phy_पढ़ो(dev, B43_NPHY_RFCTL_INTC2);
	regs_save_radio[1] = b43_radio_पढ़ो(dev, B2055_C2_PD_RXTX);
	b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_INTC2, override);
	b43_radio_ग_लिखो(dev, B2055_C2_PD_RXTX, val);

	state[0] = b43_radio_पढ़ो(dev, B2055_C1_PD_RSSIMISC) & 0x07;
	state[1] = b43_radio_पढ़ो(dev, B2055_C2_PD_RSSIMISC) & 0x07;
	b43_radio_mask(dev, B2055_C1_PD_RSSIMISC, 0xF8);
	b43_radio_mask(dev, B2055_C2_PD_RSSIMISC, 0xF8);
	state[2] = b43_radio_पढ़ो(dev, B2055_C1_SP_RSSI) & 0x07;
	state[3] = b43_radio_पढ़ो(dev, B2055_C2_SP_RSSI) & 0x07;

	b43_nphy_rssi_select(dev, 5, type);
	b43_nphy_scale_offset_rssi(dev, 0, 0, 5, N_RAIL_I, type);
	b43_nphy_scale_offset_rssi(dev, 0, 0, 5, N_RAIL_Q, type);

	क्रम (vcm = 0; vcm < 4; vcm++) अणु
		u8 पंचांगp[4];
		क्रम (j = 0; j < 4; j++)
			पंचांगp[j] = vcm;
		अगर (type != N_RSSI_W2)
			b43_nphy_set_rssi_2055_vcm(dev, type, पंचांगp);
		b43_nphy_poll_rssi(dev, type, results[vcm], 8);
		अगर (type == N_RSSI_W1 || type == N_RSSI_W2)
			क्रम (j = 0; j < 2; j++)
				miniq[vcm][j] = min(results[vcm][2 * j],
						    results[vcm][2 * j + 1]);
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		s32 mind = 0x100000;
		u8 minvcm = 0;
		s32 minpoll = 249;
		s32 currd;
		क्रम (vcm = 0; vcm < 4; vcm++) अणु
			अगर (type == N_RSSI_NB)
				currd = असल(results[vcm][i] - code * 8);
			अन्यथा
				currd = असल(miniq[vcm][i / 2] - code * 8);

			अगर (currd < mind) अणु
				mind = currd;
				minvcm = vcm;
			पूर्ण

			अगर (results[vcm][i] < minpoll)
				minpoll = results[vcm][i];
		पूर्ण
		results_min[i] = minpoll;
		vcm_final[i] = minvcm;
	पूर्ण

	अगर (type != N_RSSI_W2)
		b43_nphy_set_rssi_2055_vcm(dev, type, vcm_final);

	क्रम (i = 0; i < 4; i++) अणु
		offset[i] = (code * 8) - results[vcm_final[i]][i];

		अगर (offset[i] < 0)
			offset[i] = -((असल(offset[i]) + 4) / 8);
		अन्यथा
			offset[i] = (offset[i] + 4) / 8;

		अगर (results_min[i] == 248)
			offset[i] = code - 32;

		core = (i / 2) ? 2 : 1;
		rail = (i % 2) ? N_RAIL_Q : N_RAIL_I;

		b43_nphy_scale_offset_rssi(dev, 0, offset[i], core, rail,
						type);
	पूर्ण

	b43_radio_maskset(dev, B2055_C1_PD_RSSIMISC, 0xF8, state[0]);
	b43_radio_maskset(dev, B2055_C2_PD_RSSIMISC, 0xF8, state[1]);

	चयन (state[2]) अणु
	हाल 1:
		b43_nphy_rssi_select(dev, 1, N_RSSI_NB);
		अवरोध;
	हाल 4:
		b43_nphy_rssi_select(dev, 1, N_RSSI_W1);
		अवरोध;
	हाल 2:
		b43_nphy_rssi_select(dev, 1, N_RSSI_W2);
		अवरोध;
	शेष:
		b43_nphy_rssi_select(dev, 1, N_RSSI_W2);
		अवरोध;
	पूर्ण

	चयन (state[3]) अणु
	हाल 1:
		b43_nphy_rssi_select(dev, 2, N_RSSI_NB);
		अवरोध;
	हाल 4:
		b43_nphy_rssi_select(dev, 2, N_RSSI_W1);
		अवरोध;
	शेष:
		b43_nphy_rssi_select(dev, 2, N_RSSI_W2);
		अवरोध;
	पूर्ण

	b43_nphy_rssi_select(dev, 0, type);

	b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_INTC1, regs_save_phy[0]);
	b43_radio_ग_लिखो(dev, B2055_C1_PD_RXTX, regs_save_radio[0]);
	b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_INTC2, regs_save_phy[1]);
	b43_radio_ग_लिखो(dev, B2055_C2_PD_RXTX, regs_save_radio[1]);

	b43_nphy_classअगरier(dev, 7, class);
	b43_nphy_ग_लिखो_clip_detection(dev, clip_state);
	/* Specs करोn't say about reset here, but it makes wl and b43 dumps
	   identical, it really seems wl perक्रमms this */
	b43_nphy_reset_cca(dev);
पूर्ण

/*
 * RSSI Calibration
 * https://bcm-v4.sipsolutions.net/802.11/PHY/N/RSSICal
 */
अटल व्योम b43_nphy_rssi_cal(काष्ठा b43_wldev *dev)
अणु
	अगर (dev->phy.rev >= 19) अणु
		/* TODO */
	पूर्ण अन्यथा अगर (dev->phy.rev >= 3) अणु
		b43_nphy_rev3_rssi_cal(dev);
	पूर्ण अन्यथा अणु
		b43_nphy_rev2_rssi_cal(dev, N_RSSI_NB);
		b43_nphy_rev2_rssi_cal(dev, N_RSSI_W1);
		b43_nphy_rev2_rssi_cal(dev, N_RSSI_W2);
	पूर्ण
पूर्ण

/**************************************************
 * Workarounds
 **************************************************/

अटल व्योम b43_nphy_gain_ctl_workarounds_rev19(काष्ठा b43_wldev *dev)
अणु
	/* TODO */
पूर्ण

अटल व्योम b43_nphy_gain_ctl_workarounds_rev7(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;

	चयन (phy->rev) अणु
	/* TODO */
	पूर्ण
पूर्ण

अटल व्योम b43_nphy_gain_ctl_workarounds_rev3(काष्ठा b43_wldev *dev)
अणु
	काष्ठा ssb_sprom *sprom = dev->dev->bus_sprom;

	bool ghz5;
	bool ext_lna;
	u16 rssi_gain;
	काष्ठा nphy_gain_ctl_workaround_entry *e;
	u8 lpf_gain[6] = अणु 0x00, 0x06, 0x0C, 0x12, 0x12, 0x12 पूर्ण;
	u8 lpf_bits[6] = अणु 0, 1, 2, 3, 3, 3 पूर्ण;

	/* Prepare values */
	ghz5 = b43_phy_पढ़ो(dev, B43_NPHY_BANDCTL)
		& B43_NPHY_BANDCTL_5GHZ;
	ext_lna = ghz5 ? sprom->boardflags_hi & B43_BFH_EXTLNA_5GHZ :
		sprom->boardflags_lo & B43_BFL_EXTLNA;
	e = b43_nphy_get_gain_ctl_workaround_ent(dev, ghz5, ext_lna);
	अगर (ghz5 && dev->phy.rev >= 5)
		rssi_gain = 0x90;
	अन्यथा
		rssi_gain = 0x50;

	b43_phy_set(dev, B43_NPHY_RXCTL, 0x0040);

	/* Set Clip 2 detect */
	b43_phy_set(dev, B43_NPHY_C1_CGAINI, B43_NPHY_C1_CGAINI_CL2DETECT);
	b43_phy_set(dev, B43_NPHY_C2_CGAINI, B43_NPHY_C2_CGAINI_CL2DETECT);

	b43_radio_ग_लिखो(dev, B2056_RX0 | B2056_RX_BIASPOLE_LNAG1_IDAC,
			0x17);
	b43_radio_ग_लिखो(dev, B2056_RX1 | B2056_RX_BIASPOLE_LNAG1_IDAC,
			0x17);
	b43_radio_ग_लिखो(dev, B2056_RX0 | B2056_RX_LNAG2_IDAC, 0xF0);
	b43_radio_ग_लिखो(dev, B2056_RX1 | B2056_RX_LNAG2_IDAC, 0xF0);
	b43_radio_ग_लिखो(dev, B2056_RX0 | B2056_RX_RSSI_POLE, 0x00);
	b43_radio_ग_लिखो(dev, B2056_RX1 | B2056_RX_RSSI_POLE, 0x00);
	b43_radio_ग_लिखो(dev, B2056_RX0 | B2056_RX_RSSI_GAIN,
			rssi_gain);
	b43_radio_ग_लिखो(dev, B2056_RX1 | B2056_RX_RSSI_GAIN,
			rssi_gain);
	b43_radio_ग_लिखो(dev, B2056_RX0 | B2056_RX_BIASPOLE_LNAA1_IDAC,
			0x17);
	b43_radio_ग_लिखो(dev, B2056_RX1 | B2056_RX_BIASPOLE_LNAA1_IDAC,
			0x17);
	b43_radio_ग_लिखो(dev, B2056_RX0 | B2056_RX_LNAA2_IDAC, 0xFF);
	b43_radio_ग_लिखो(dev, B2056_RX1 | B2056_RX_LNAA2_IDAC, 0xFF);

	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB8(0, 8), 4, e->lna1_gain);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB8(1, 8), 4, e->lna1_gain);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB8(0, 16), 4, e->lna2_gain);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB8(1, 16), 4, e->lna2_gain);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB8(0, 32), 10, e->gain_db);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB8(1, 32), 10, e->gain_db);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB8(2, 32), 10, e->gain_bits);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB8(3, 32), 10, e->gain_bits);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB8(0, 0x40), 6, lpf_gain);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB8(1, 0x40), 6, lpf_gain);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB8(2, 0x40), 6, lpf_bits);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB8(3, 0x40), 6, lpf_bits);

	b43_phy_ग_लिखो(dev, B43_NPHY_REV3_C1_INITGAIN_A, e->init_gain);
	b43_phy_ग_लिखो(dev, B43_NPHY_REV3_C2_INITGAIN_A, e->init_gain);

	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(7, 0x106), 2,
				e->rfseq_init);

	b43_phy_ग_लिखो(dev, B43_NPHY_REV3_C1_CLIP_HIGAIN_A, e->cliphi_gain);
	b43_phy_ग_लिखो(dev, B43_NPHY_REV3_C2_CLIP_HIGAIN_A, e->cliphi_gain);
	b43_phy_ग_लिखो(dev, B43_NPHY_REV3_C1_CLIP_MEDGAIN_A, e->clipmd_gain);
	b43_phy_ग_लिखो(dev, B43_NPHY_REV3_C2_CLIP_MEDGAIN_A, e->clipmd_gain);
	b43_phy_ग_लिखो(dev, B43_NPHY_REV3_C1_CLIP_LOGAIN_A, e->cliplo_gain);
	b43_phy_ग_लिखो(dev, B43_NPHY_REV3_C2_CLIP_LOGAIN_A, e->cliplo_gain);

	b43_phy_maskset(dev, B43_NPHY_CRSMINPOWER0, 0xFF00, e->crsmin);
	b43_phy_maskset(dev, B43_NPHY_CRSMINPOWERL0, 0xFF00, e->crsminl);
	b43_phy_maskset(dev, B43_NPHY_CRSMINPOWERU0, 0xFF00, e->crsminu);
	b43_phy_ग_लिखो(dev, B43_NPHY_C1_NBCLIPTHRES, e->nbclip);
	b43_phy_ग_लिखो(dev, B43_NPHY_C2_NBCLIPTHRES, e->nbclip);
	b43_phy_maskset(dev, B43_NPHY_C1_CLIPWBTHRES,
			~B43_NPHY_C1_CLIPWBTHRES_CLIP2, e->wlclip);
	b43_phy_maskset(dev, B43_NPHY_C2_CLIPWBTHRES,
			~B43_NPHY_C2_CLIPWBTHRES_CLIP2, e->wlclip);
	b43_phy_ग_लिखो(dev, B43_NPHY_CCK_SHIFTB_REF, 0x809C);
पूर्ण

अटल व्योम b43_nphy_gain_ctl_workarounds_rev1_2(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_n *nphy = dev->phy.n;

	u8 i, j;
	u8 code;
	u16 पंचांगp;
	u8 rfseq_events[3] = अणु 6, 8, 7 पूर्ण;
	u8 rfseq_delays[3] = अणु 10, 30, 1 पूर्ण;

	/* Set Clip 2 detect */
	b43_phy_set(dev, B43_NPHY_C1_CGAINI, B43_NPHY_C1_CGAINI_CL2DETECT);
	b43_phy_set(dev, B43_NPHY_C2_CGAINI, B43_NPHY_C2_CGAINI_CL2DETECT);

	/* Set narrowband clip threshold */
	b43_phy_ग_लिखो(dev, B43_NPHY_C1_NBCLIPTHRES, 0x84);
	b43_phy_ग_लिखो(dev, B43_NPHY_C2_NBCLIPTHRES, 0x84);

	अगर (!b43_is_40mhz(dev)) अणु
		/* Set dwell lengths */
		b43_phy_ग_लिखो(dev, B43_NPHY_CLIP1_NBDWELL_LEN, 0x002B);
		b43_phy_ग_लिखो(dev, B43_NPHY_CLIP2_NBDWELL_LEN, 0x002B);
		b43_phy_ग_लिखो(dev, B43_NPHY_W1CLIP1_DWELL_LEN, 0x0009);
		b43_phy_ग_लिखो(dev, B43_NPHY_W1CLIP2_DWELL_LEN, 0x0009);
	पूर्ण

	/* Set wideband clip 2 threshold */
	b43_phy_maskset(dev, B43_NPHY_C1_CLIPWBTHRES,
			~B43_NPHY_C1_CLIPWBTHRES_CLIP2, 21);
	b43_phy_maskset(dev, B43_NPHY_C2_CLIPWBTHRES,
			~B43_NPHY_C2_CLIPWBTHRES_CLIP2, 21);

	अगर (!b43_is_40mhz(dev)) अणु
		b43_phy_maskset(dev, B43_NPHY_C1_CGAINI,
			~B43_NPHY_C1_CGAINI_GAINBKOFF, 0x1);
		b43_phy_maskset(dev, B43_NPHY_C2_CGAINI,
			~B43_NPHY_C2_CGAINI_GAINBKOFF, 0x1);
		b43_phy_maskset(dev, B43_NPHY_C1_CCK_CGAINI,
			~B43_NPHY_C1_CCK_CGAINI_GAINBKOFF, 0x1);
		b43_phy_maskset(dev, B43_NPHY_C2_CCK_CGAINI,
			~B43_NPHY_C2_CCK_CGAINI_GAINBKOFF, 0x1);
	पूर्ण

	b43_phy_ग_लिखो(dev, B43_NPHY_CCK_SHIFTB_REF, 0x809C);

	अगर (nphy->gain_boost) अणु
		अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ &&
		    b43_is_40mhz(dev))
			code = 4;
		अन्यथा
			code = 5;
	पूर्ण अन्यथा अणु
		code = b43_is_40mhz(dev) ? 6 : 7;
	पूर्ण

	/* Set HPVGA2 index */
	b43_phy_maskset(dev, B43_NPHY_C1_INITGAIN, ~B43_NPHY_C1_INITGAIN_HPVGA2,
			code << B43_NPHY_C1_INITGAIN_HPVGA2_SHIFT);
	b43_phy_maskset(dev, B43_NPHY_C2_INITGAIN, ~B43_NPHY_C2_INITGAIN_HPVGA2,
			code << B43_NPHY_C2_INITGAIN_HPVGA2_SHIFT);

	b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_ADDR, 0x1D06);
	/* specs say about 2 loops, but wl करोes 4 */
	क्रम (i = 0; i < 4; i++)
		b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_DATALO, (code << 8 | 0x7C));

	b43_nphy_adjust_lna_gain_table(dev);

	अगर (nphy->elna_gain_config) अणु
		b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_ADDR, 0x0808);
		b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_DATALO, 0x0);
		b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_DATALO, 0x1);
		b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_DATALO, 0x1);
		b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_DATALO, 0x1);

		b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_ADDR, 0x0C08);
		b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_DATALO, 0x0);
		b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_DATALO, 0x1);
		b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_DATALO, 0x1);
		b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_DATALO, 0x1);

		b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_ADDR, 0x1D06);
		/* specs say about 2 loops, but wl करोes 4 */
		क्रम (i = 0; i < 4; i++)
			b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_DATALO,
						(code << 8 | 0x74));
	पूर्ण

	अगर (dev->phy.rev == 2) अणु
		क्रम (i = 0; i < 4; i++) अणु
			b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_ADDR,
					(0x0400 * i) + 0x0020);
			क्रम (j = 0; j < 21; j++) अणु
				पंचांगp = j * (i < 2 ? 3 : 1);
				b43_phy_ग_लिखो(dev,
					B43_NPHY_TABLE_DATALO, पंचांगp);
			पूर्ण
		पूर्ण
	पूर्ण

	b43_nphy_set_rf_sequence(dev, 5, rfseq_events, rfseq_delays, 3);
	b43_phy_maskset(dev, B43_NPHY_OVER_DGAIN1,
		~B43_NPHY_OVER_DGAIN_CCKDGECV & 0xFFFF,
		0x5A << B43_NPHY_OVER_DGAIN_CCKDGECV_SHIFT);

	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
		b43_phy_maskset(dev, B43_PHY_N(0xC5D), 0xFF80, 4);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/WorkaroundsGainCtrl */
अटल व्योम b43_nphy_gain_ctl_workarounds(काष्ठा b43_wldev *dev)
अणु
	अगर (dev->phy.rev >= 19)
		b43_nphy_gain_ctl_workarounds_rev19(dev);
	अन्यथा अगर (dev->phy.rev >= 7)
		b43_nphy_gain_ctl_workarounds_rev7(dev);
	अन्यथा अगर (dev->phy.rev >= 3)
		b43_nphy_gain_ctl_workarounds_rev3(dev);
	अन्यथा
		b43_nphy_gain_ctl_workarounds_rev1_2(dev);
पूर्ण

अटल व्योम b43_nphy_workarounds_rev7plus(काष्ठा b43_wldev *dev)
अणु
	काष्ठा ssb_sprom *sprom = dev->dev->bus_sprom;
	काष्ठा b43_phy *phy = &dev->phy;

	/* TX to RX */
	u8 tx2rx_events[7] = अणु 4, 3, 5, 2, 1, 8, 31, पूर्ण;
	u8 tx2rx_delays[7] = अणु 8, 4, 4, 4, 4, 6, 1, पूर्ण;
	/* RX to TX */
	u8 rx2tx_events_ipa[9] = अणु 0x0, 0x1, 0x2, 0x8, 0x5, 0x6, 0xF, 0x3,
					0x1F पूर्ण;
	u8 rx2tx_delays_ipa[9] = अणु 8, 6, 6, 4, 4, 16, 43, 1, 1 पूर्ण;

	अटल स्थिर u16 ntab7_15e_16e[] = अणु 0, 0x10f, 0x10f पूर्ण;
	u8 ntab7_138_146[] = अणु 0x11, 0x11 पूर्ण;
	u8 ntab7_133[] = अणु 0x77, 0x11, 0x11 पूर्ण;

	u16 lpf_ofdm_20mhz[2], lpf_ofdm_40mhz[2], lpf_11b[2];
	u16 bcap_val;
	s16 bcap_val_11b[2], bcap_val_11n_20[2], bcap_val_11n_40[2];
	u16 scap_val;
	s16 scap_val_11b[2], scap_val_11n_20[2], scap_val_11n_40[2];
	bool rccal_ovrd = false;

	u16 bias, conv, filt;

	u32 noise_tbl[2];

	u32 पंचांगp32;
	u8 core;

	b43_phy_ग_लिखो(dev, B43_NPHY_PHASETR_A0, 0x0125);
	b43_phy_ग_लिखो(dev, B43_NPHY_PHASETR_A1, 0x01b3);
	b43_phy_ग_लिखो(dev, B43_NPHY_PHASETR_A2, 0x0105);
	b43_phy_ग_लिखो(dev, B43_NPHY_PHASETR_B0, 0x016e);
	b43_phy_ग_लिखो(dev, B43_NPHY_PHASETR_B1, 0x00cd);
	b43_phy_ग_लिखो(dev, B43_NPHY_PHASETR_B2, 0x0020);

	अगर (phy->rev == 7) अणु
		b43_phy_set(dev, B43_NPHY_FINERX2_CGC, 0x10);
		b43_phy_maskset(dev, B43_NPHY_FREQGAIN0, 0xFF80, 0x0020);
		b43_phy_maskset(dev, B43_NPHY_FREQGAIN0, 0x80FF, 0x2700);
		b43_phy_maskset(dev, B43_NPHY_FREQGAIN1, 0xFF80, 0x002E);
		b43_phy_maskset(dev, B43_NPHY_FREQGAIN1, 0x80FF, 0x3300);
		b43_phy_maskset(dev, B43_NPHY_FREQGAIN2, 0xFF80, 0x0037);
		b43_phy_maskset(dev, B43_NPHY_FREQGAIN2, 0x80FF, 0x3A00);
		b43_phy_maskset(dev, B43_NPHY_FREQGAIN3, 0xFF80, 0x003C);
		b43_phy_maskset(dev, B43_NPHY_FREQGAIN3, 0x80FF, 0x3E00);
		b43_phy_maskset(dev, B43_NPHY_FREQGAIN4, 0xFF80, 0x003E);
		b43_phy_maskset(dev, B43_NPHY_FREQGAIN4, 0x80FF, 0x3F00);
		b43_phy_maskset(dev, B43_NPHY_FREQGAIN5, 0xFF80, 0x0040);
		b43_phy_maskset(dev, B43_NPHY_FREQGAIN5, 0x80FF, 0x4000);
		b43_phy_maskset(dev, B43_NPHY_FREQGAIN6, 0xFF80, 0x0040);
		b43_phy_maskset(dev, B43_NPHY_FREQGAIN6, 0x80FF, 0x4000);
		b43_phy_maskset(dev, B43_NPHY_FREQGAIN7, 0xFF80, 0x0040);
		b43_phy_maskset(dev, B43_NPHY_FREQGAIN7, 0x80FF, 0x4000);
	पूर्ण

	अगर (phy->rev >= 16) अणु
		b43_phy_ग_लिखो(dev, B43_NPHY_FORCEFRONT0, 0x7ff);
		b43_phy_ग_लिखो(dev, B43_NPHY_FORCEFRONT1, 0x7ff);
	पूर्ण अन्यथा अगर (phy->rev <= 8) अणु
		b43_phy_ग_लिखो(dev, B43_NPHY_FORCEFRONT0, 0x1B0);
		b43_phy_ग_लिखो(dev, B43_NPHY_FORCEFRONT1, 0x1B0);
	पूर्ण

	अगर (phy->rev >= 16)
		b43_phy_maskset(dev, B43_NPHY_TXTAILCNT, ~0xFF, 0xa0);
	अन्यथा अगर (phy->rev >= 8)
		b43_phy_maskset(dev, B43_NPHY_TXTAILCNT, ~0xFF, 0x72);

	b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 0x00), 2);
	b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 0x10), 2);
	पंचांगp32 = b43_ntab_पढ़ो(dev, B43_NTAB32(30, 0));
	पंचांगp32 &= 0xffffff;
	b43_ntab_ग_लिखो(dev, B43_NTAB32(30, 0), पंचांगp32);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(7, 0x15d), 3, ntab7_15e_16e);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(7, 0x16d), 3, ntab7_15e_16e);

	b43_nphy_set_rf_sequence(dev, 1, tx2rx_events, tx2rx_delays,
				 ARRAY_SIZE(tx2rx_events));
	अगर (b43_nphy_ipa(dev))
		b43_nphy_set_rf_sequence(dev, 0, rx2tx_events_ipa,
				rx2tx_delays_ipa, ARRAY_SIZE(rx2tx_events_ipa));

	b43_phy_maskset(dev, B43_NPHY_EPS_OVERRIDEI_0, 0x3FFF, 0x4000);
	b43_phy_maskset(dev, B43_NPHY_EPS_OVERRIDEI_1, 0x3FFF, 0x4000);

	क्रम (core = 0; core < 2; core++) अणु
		lpf_ofdm_20mhz[core] = b43_nphy_पढ़ो_lpf_ctl(dev, 0x154 + core * 0x10);
		lpf_ofdm_40mhz[core] = b43_nphy_पढ़ो_lpf_ctl(dev, 0x159 + core * 0x10);
		lpf_11b[core] = b43_nphy_पढ़ो_lpf_ctl(dev, 0x152 + core * 0x10);
	पूर्ण

	bcap_val = b43_radio_पढ़ो(dev, R2057_RCCAL_BCAP_VAL);
	scap_val = b43_radio_पढ़ो(dev, R2057_RCCAL_SCAP_VAL);

	अगर (b43_nphy_ipa(dev)) अणु
		bool ghz2 = b43_current_band(dev->wl) == NL80211_BAND_2GHZ;

		चयन (phy->radio_rev) अणु
		हाल 5:
			/* Check radio version (to be 0) by PHY rev क्रम now */
			अगर (phy->rev == 8 && b43_is_40mhz(dev)) अणु
				क्रम (core = 0; core < 2; core++) अणु
					scap_val_11b[core] = scap_val;
					bcap_val_11b[core] = bcap_val;
					scap_val_11n_20[core] = scap_val;
					bcap_val_11n_20[core] = bcap_val;
					scap_val_11n_40[core] = 0xc;
					bcap_val_11n_40[core] = 0xc;
				पूर्ण

				rccal_ovrd = true;
			पूर्ण
			अगर (phy->rev == 9) अणु
				/* TODO: Radio version 1 (e.g. BCM5357B0) */
			पूर्ण
			अवरोध;
		हाल 7:
		हाल 8:
			क्रम (core = 0; core < 2; core++) अणु
				scap_val_11b[core] = scap_val;
				bcap_val_11b[core] = bcap_val;
				lpf_ofdm_20mhz[core] = 4;
				lpf_11b[core] = 1;
				अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
					scap_val_11n_20[core] = 0xc;
					bcap_val_11n_20[core] = 0xc;
					scap_val_11n_40[core] = 0xa;
					bcap_val_11n_40[core] = 0xa;
				पूर्ण अन्यथा अणु
					scap_val_11n_20[core] = 0x14;
					bcap_val_11n_20[core] = 0x14;
					scap_val_11n_40[core] = 0xf;
					bcap_val_11n_40[core] = 0xf;
				पूर्ण
			पूर्ण

			rccal_ovrd = true;
			अवरोध;
		हाल 9:
			क्रम (core = 0; core < 2; core++) अणु
				bcap_val_11b[core] = bcap_val;
				scap_val_11b[core] = scap_val;
				lpf_11b[core] = 1;

				अगर (ghz2) अणु
					bcap_val_11n_20[core] = bcap_val + 13;
					scap_val_11n_20[core] = scap_val + 15;
				पूर्ण अन्यथा अणु
					bcap_val_11n_20[core] = bcap_val + 14;
					scap_val_11n_20[core] = scap_val + 15;
				पूर्ण
				lpf_ofdm_20mhz[core] = 4;

				अगर (ghz2) अणु
					bcap_val_11n_40[core] = bcap_val - 7;
					scap_val_11n_40[core] = scap_val - 5;
				पूर्ण अन्यथा अणु
					bcap_val_11n_40[core] = bcap_val + 2;
					scap_val_11n_40[core] = scap_val + 4;
				पूर्ण
				lpf_ofdm_40mhz[core] = 4;
			पूर्ण

			rccal_ovrd = true;
			अवरोध;
		हाल 14:
			क्रम (core = 0; core < 2; core++) अणु
				bcap_val_11b[core] = bcap_val;
				scap_val_11b[core] = scap_val;
				lpf_11b[core] = 1;
			पूर्ण

			bcap_val_11n_20[0] = bcap_val + 20;
			scap_val_11n_20[0] = scap_val + 20;
			lpf_ofdm_20mhz[0] = 3;

			bcap_val_11n_20[1] = bcap_val + 16;
			scap_val_11n_20[1] = scap_val + 16;
			lpf_ofdm_20mhz[1] = 3;

			bcap_val_11n_40[0] = bcap_val + 20;
			scap_val_11n_40[0] = scap_val + 20;
			lpf_ofdm_40mhz[0] = 4;

			bcap_val_11n_40[1] = bcap_val + 10;
			scap_val_11n_40[1] = scap_val + 10;
			lpf_ofdm_40mhz[1] = 4;

			rccal_ovrd = true;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (phy->radio_rev == 5) अणु
			क्रम (core = 0; core < 2; core++) अणु
				lpf_ofdm_20mhz[core] = 1;
				lpf_ofdm_40mhz[core] = 3;
				scap_val_11b[core] = scap_val;
				bcap_val_11b[core] = bcap_val;
				scap_val_11n_20[core] = 0x11;
				scap_val_11n_40[core] = 0x11;
				bcap_val_11n_20[core] = 0x13;
				bcap_val_11n_40[core] = 0x13;
			पूर्ण

			rccal_ovrd = true;
		पूर्ण
	पूर्ण
	अगर (rccal_ovrd) अणु
		u16 rx2tx_lut_20_11b[2], rx2tx_lut_20_11n[2], rx2tx_lut_40_11n[2];
		u8 rx2tx_lut_extra = 1;

		क्रम (core = 0; core < 2; core++) अणु
			bcap_val_11b[core] = clamp_val(bcap_val_11b[core], 0, 0x1f);
			scap_val_11b[core] = clamp_val(scap_val_11b[core], 0, 0x1f);
			bcap_val_11n_20[core] = clamp_val(bcap_val_11n_20[core], 0, 0x1f);
			scap_val_11n_20[core] = clamp_val(scap_val_11n_20[core], 0, 0x1f);
			bcap_val_11n_40[core] = clamp_val(bcap_val_11n_40[core], 0, 0x1f);
			scap_val_11n_40[core] = clamp_val(scap_val_11n_40[core], 0, 0x1f);

			rx2tx_lut_20_11b[core] = (rx2tx_lut_extra << 13) |
						 (bcap_val_11b[core] << 8) |
						 (scap_val_11b[core] << 3) |
						 lpf_11b[core];
			rx2tx_lut_20_11n[core] = (rx2tx_lut_extra << 13) |
						 (bcap_val_11n_20[core] << 8) |
						 (scap_val_11n_20[core] << 3) |
						 lpf_ofdm_20mhz[core];
			rx2tx_lut_40_11n[core] = (rx2tx_lut_extra << 13) |
						 (bcap_val_11n_40[core] << 8) |
						 (scap_val_11n_40[core] << 3) |
						 lpf_ofdm_40mhz[core];
		पूर्ण

		क्रम (core = 0; core < 2; core++) अणु
			b43_ntab_ग_लिखो(dev, B43_NTAB16(7, 0x152 + core * 16),
				       rx2tx_lut_20_11b[core]);
			b43_ntab_ग_लिखो(dev, B43_NTAB16(7, 0x153 + core * 16),
				       rx2tx_lut_20_11n[core]);
			b43_ntab_ग_लिखो(dev, B43_NTAB16(7, 0x154 + core * 16),
				       rx2tx_lut_20_11n[core]);
			b43_ntab_ग_लिखो(dev, B43_NTAB16(7, 0x155 + core * 16),
				       rx2tx_lut_40_11n[core]);
			b43_ntab_ग_लिखो(dev, B43_NTAB16(7, 0x156 + core * 16),
				       rx2tx_lut_40_11n[core]);
			b43_ntab_ग_लिखो(dev, B43_NTAB16(7, 0x157 + core * 16),
				       rx2tx_lut_40_11n[core]);
			b43_ntab_ग_लिखो(dev, B43_NTAB16(7, 0x158 + core * 16),
				       rx2tx_lut_40_11n[core]);
			b43_ntab_ग_लिखो(dev, B43_NTAB16(7, 0x159 + core * 16),
				       rx2tx_lut_40_11n[core]);
		पूर्ण
	पूर्ण

	b43_phy_ग_लिखो(dev, 0x32F, 0x3);

	अगर (phy->radio_rev == 4 || phy->radio_rev == 6)
		b43_nphy_rf_ctl_override_rev7(dev, 4, 1, 3, false, 0);

	अगर (phy->radio_rev == 3 || phy->radio_rev == 4 || phy->radio_rev == 6) अणु
		अगर (sprom->revision &&
		    sprom->boardflags2_hi & B43_BFH2_IPALVLSHIFT_3P3) अणु
			b43_radio_ग_लिखो(dev, 0x5, 0x05);
			b43_radio_ग_लिखो(dev, 0x6, 0x30);
			b43_radio_ग_लिखो(dev, 0x7, 0x00);
			b43_radio_set(dev, 0x4f, 0x1);
			b43_radio_set(dev, 0xd4, 0x1);
			bias = 0x1f;
			conv = 0x6f;
			filt = 0xaa;
		पूर्ण अन्यथा अणु
			bias = 0x2b;
			conv = 0x7f;
			filt = 0xee;
		पूर्ण
		अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
			क्रम (core = 0; core < 2; core++) अणु
				अगर (core == 0) अणु
					b43_radio_ग_लिखो(dev, 0x5F, bias);
					b43_radio_ग_लिखो(dev, 0x64, conv);
					b43_radio_ग_लिखो(dev, 0x66, filt);
				पूर्ण अन्यथा अणु
					b43_radio_ग_लिखो(dev, 0xE8, bias);
					b43_radio_ग_लिखो(dev, 0xE9, conv);
					b43_radio_ग_लिखो(dev, 0xEB, filt);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (b43_nphy_ipa(dev)) अणु
		अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
			अगर (phy->radio_rev == 3 || phy->radio_rev == 4 ||
			    phy->radio_rev == 6) अणु
				क्रम (core = 0; core < 2; core++) अणु
					अगर (core == 0)
						b43_radio_ग_लिखो(dev, 0x51,
								0x7f);
					अन्यथा
						b43_radio_ग_लिखो(dev, 0xd6,
								0x7f);
				पूर्ण
			पूर्ण
			चयन (phy->radio_rev) अणु
			हाल 3:
				क्रम (core = 0; core < 2; core++) अणु
					अगर (core == 0) अणु
						b43_radio_ग_लिखो(dev, 0x64,
								0x13);
						b43_radio_ग_लिखो(dev, 0x5F,
								0x1F);
						b43_radio_ग_लिखो(dev, 0x66,
								0xEE);
						b43_radio_ग_लिखो(dev, 0x59,
								0x8A);
						b43_radio_ग_लिखो(dev, 0x80,
								0x3E);
					पूर्ण अन्यथा अणु
						b43_radio_ग_लिखो(dev, 0x69,
								0x13);
						b43_radio_ग_लिखो(dev, 0xE8,
								0x1F);
						b43_radio_ग_लिखो(dev, 0xEB,
								0xEE);
						b43_radio_ग_लिखो(dev, 0xDE,
								0x8A);
						b43_radio_ग_लिखो(dev, 0x105,
								0x3E);
					पूर्ण
				पूर्ण
				अवरोध;
			हाल 7:
			हाल 8:
				अगर (!b43_is_40mhz(dev)) अणु
					b43_radio_ग_लिखो(dev, 0x5F, 0x14);
					b43_radio_ग_लिखो(dev, 0xE8, 0x12);
				पूर्ण अन्यथा अणु
					b43_radio_ग_लिखो(dev, 0x5F, 0x16);
					b43_radio_ग_लिखो(dev, 0xE8, 0x16);
				पूर्ण
				अवरोध;
			हाल 14:
				क्रम (core = 0; core < 2; core++) अणु
					पूर्णांक o = core ? 0x85 : 0;

					b43_radio_ग_लिखो(dev, o + R2057_IPA2G_CASCONV_CORE0, 0x13);
					b43_radio_ग_लिखो(dev, o + R2057_TXMIX2G_TUNE_BOOST_PU_CORE0, 0x21);
					b43_radio_ग_लिखो(dev, o + R2057_IPA2G_BIAS_FILTER_CORE0, 0xff);
					b43_radio_ग_लिखो(dev, o + R2057_PAD2G_IDACS_CORE0, 0x88);
					b43_radio_ग_लिखो(dev, o + R2057_PAD2G_TUNE_PUS_CORE0, 0x23);
					b43_radio_ग_लिखो(dev, o + R2057_IPA2G_IMAIN_CORE0, 0x16);
					b43_radio_ग_लिखो(dev, o + R2057_PAD_BIAS_FILTER_BWS_CORE0, 0x3e);
					b43_radio_ग_लिखो(dev, o + R2057_BACKUP1_CORE0, 0x10);
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			u16 freq = phy->chandef->chan->center_freq;
			अगर ((freq >= 5180 && freq <= 5230) ||
			    (freq >= 5745 && freq <= 5805)) अणु
				b43_radio_ग_लिखो(dev, 0x7D, 0xFF);
				b43_radio_ग_लिखो(dev, 0xFE, 0xFF);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (phy->radio_rev != 5) अणु
			क्रम (core = 0; core < 2; core++) अणु
				अगर (core == 0) अणु
					b43_radio_ग_लिखो(dev, 0x5c, 0x61);
					b43_radio_ग_लिखो(dev, 0x51, 0x70);
				पूर्ण अन्यथा अणु
					b43_radio_ग_लिखो(dev, 0xe1, 0x61);
					b43_radio_ग_लिखो(dev, 0xd6, 0x70);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (phy->radio_rev == 4) अणु
		b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 0x05), 0x20);
		b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 0x15), 0x20);
		क्रम (core = 0; core < 2; core++) अणु
			अगर (core == 0) अणु
				b43_radio_ग_लिखो(dev, 0x1a1, 0x00);
				b43_radio_ग_लिखो(dev, 0x1a2, 0x3f);
				b43_radio_ग_लिखो(dev, 0x1a6, 0x3f);
			पूर्ण अन्यथा अणु
				b43_radio_ग_लिखो(dev, 0x1a7, 0x00);
				b43_radio_ग_लिखो(dev, 0x1ab, 0x3f);
				b43_radio_ग_लिखो(dev, 0x1ac, 0x3f);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		b43_phy_set(dev, B43_NPHY_AFECTL_C1, 0x4);
		b43_phy_set(dev, B43_NPHY_AFECTL_OVER1, 0x4);
		b43_phy_set(dev, B43_NPHY_AFECTL_C2, 0x4);
		b43_phy_set(dev, B43_NPHY_AFECTL_OVER, 0x4);

		b43_phy_mask(dev, B43_NPHY_AFECTL_C1, ~0x1);
		b43_phy_set(dev, B43_NPHY_AFECTL_OVER1, 0x1);
		b43_phy_mask(dev, B43_NPHY_AFECTL_C2, ~0x1);
		b43_phy_set(dev, B43_NPHY_AFECTL_OVER, 0x1);
		b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 0x05), 0);
		b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 0x15), 0);

		b43_phy_mask(dev, B43_NPHY_AFECTL_C1, ~0x4);
		b43_phy_mask(dev, B43_NPHY_AFECTL_OVER1, ~0x4);
		b43_phy_mask(dev, B43_NPHY_AFECTL_C2, ~0x4);
		b43_phy_mask(dev, B43_NPHY_AFECTL_OVER, ~0x4);
	पूर्ण

	b43_phy_ग_लिखो(dev, B43_NPHY_ENDROP_TLEN, 0x2);

	b43_ntab_ग_लिखो(dev, B43_NTAB32(16, 0x100), 20);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB8(7, 0x138), 2, ntab7_138_146);
	b43_ntab_ग_लिखो(dev, B43_NTAB16(7, 0x141), 0x77);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB8(7, 0x133), 3, ntab7_133);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB8(7, 0x146), 2, ntab7_138_146);
	b43_ntab_ग_लिखो(dev, B43_NTAB16(7, 0x123), 0x77);
	b43_ntab_ग_लिखो(dev, B43_NTAB16(7, 0x12A), 0x77);

	b43_ntab_पढ़ो_bulk(dev, B43_NTAB32(16, 0x02), 1, noise_tbl);
	noise_tbl[1] = b43_is_40mhz(dev) ? 0x14D : 0x18D;
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB32(16, 0x02), 2, noise_tbl);

	b43_ntab_पढ़ो_bulk(dev, B43_NTAB32(16, 0x7E), 1, noise_tbl);
	noise_tbl[1] = b43_is_40mhz(dev) ? 0x14D : 0x18D;
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB32(16, 0x7E), 2, noise_tbl);

	b43_nphy_gain_ctl_workarounds(dev);

	/* TODO
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(8, 0x08), 4,
			    aux_adc_vmid_rev7_core0);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(8, 0x18), 4,
			    aux_adc_vmid_rev7_core1);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(8, 0x0C), 4,
			    aux_adc_gain_rev7);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(8, 0x1C), 4,
			    aux_adc_gain_rev7);
	*/
पूर्ण

अटल व्योम b43_nphy_workarounds_rev3plus(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_n *nphy = dev->phy.n;
	काष्ठा ssb_sprom *sprom = dev->dev->bus_sprom;

	/* TX to RX */
	u8 tx2rx_events[7] = अणु 0x4, 0x3, 0x5, 0x2, 0x1, 0x8, 0x1F पूर्ण;
	u8 tx2rx_delays[7] = अणु 8, 4, 4, 4, 4, 6, 1 पूर्ण;
	/* RX to TX */
	u8 rx2tx_events_ipa[9] = अणु 0x0, 0x1, 0x2, 0x8, 0x5, 0x6, 0xF, 0x3,
					0x1F पूर्ण;
	u8 rx2tx_delays_ipa[9] = अणु 8, 6, 6, 4, 4, 16, 43, 1, 1 पूर्ण;
	u8 rx2tx_events[9] = अणु 0x0, 0x1, 0x2, 0x8, 0x5, 0x6, 0x3, 0x4, 0x1F पूर्ण;
	u8 rx2tx_delays[9] = अणु 8, 6, 6, 4, 4, 18, 42, 1, 1 पूर्ण;

	u16 vmids[5][4] = अणु
		अणु 0xa2, 0xb4, 0xb4, 0x89, पूर्ण, /* 0 */
		अणु 0xb4, 0xb4, 0xb4, 0x24, पूर्ण, /* 1 */
		अणु 0xa2, 0xb4, 0xb4, 0x74, पूर्ण, /* 2 */
		अणु 0xa2, 0xb4, 0xb4, 0x270, पूर्ण, /* 3 */
		अणु 0xa2, 0xb4, 0xb4, 0x00, पूर्ण, /* 4 and 5 */
	पूर्ण;
	u16 gains[5][4] = अणु
		अणु 0x02, 0x02, 0x02, 0x00, पूर्ण, /* 0 */
		अणु 0x02, 0x02, 0x02, 0x02, पूर्ण, /* 1 */
		अणु 0x02, 0x02, 0x02, 0x04, पूर्ण, /* 2 */
		अणु 0x02, 0x02, 0x02, 0x00, पूर्ण, /* 3 */
		अणु 0x02, 0x02, 0x02, 0x00, पूर्ण, /* 4 and 5 */
	पूर्ण;
	u16 *vmid, *gain;

	u8 pdet_range;
	u16 पंचांगp16;
	u32 पंचांगp32;

	b43_phy_ग_लिखो(dev, B43_NPHY_FORCEFRONT0, 0x1f8);
	b43_phy_ग_लिखो(dev, B43_NPHY_FORCEFRONT1, 0x1f8);

	पंचांगp32 = b43_ntab_पढ़ो(dev, B43_NTAB32(30, 0));
	पंचांगp32 &= 0xffffff;
	b43_ntab_ग_लिखो(dev, B43_NTAB32(30, 0), पंचांगp32);

	b43_phy_ग_लिखो(dev, B43_NPHY_PHASETR_A0, 0x0125);
	b43_phy_ग_लिखो(dev, B43_NPHY_PHASETR_A1, 0x01B3);
	b43_phy_ग_लिखो(dev, B43_NPHY_PHASETR_A2, 0x0105);
	b43_phy_ग_लिखो(dev, B43_NPHY_PHASETR_B0, 0x016E);
	b43_phy_ग_लिखो(dev, B43_NPHY_PHASETR_B1, 0x00CD);
	b43_phy_ग_लिखो(dev, B43_NPHY_PHASETR_B2, 0x0020);

	b43_phy_ग_लिखो(dev, B43_NPHY_REV3_C1_CLIP_LOGAIN_B, 0x000C);
	b43_phy_ग_लिखो(dev, B43_NPHY_REV3_C2_CLIP_LOGAIN_B, 0x000C);

	/* TX to RX */
	b43_nphy_set_rf_sequence(dev, 1, tx2rx_events, tx2rx_delays,
				 ARRAY_SIZE(tx2rx_events));

	/* RX to TX */
	अगर (b43_nphy_ipa(dev))
		b43_nphy_set_rf_sequence(dev, 0, rx2tx_events_ipa,
				rx2tx_delays_ipa, ARRAY_SIZE(rx2tx_events_ipa));
	अगर (nphy->hw_phyrxchain != 3 &&
	    nphy->hw_phyrxchain != nphy->hw_phytxchain) अणु
		अगर (b43_nphy_ipa(dev)) अणु
			rx2tx_delays[5] = 59;
			rx2tx_delays[6] = 1;
			rx2tx_events[7] = 0x1F;
		पूर्ण
		b43_nphy_set_rf_sequence(dev, 0, rx2tx_events, rx2tx_delays,
					 ARRAY_SIZE(rx2tx_events));
	पूर्ण

	पंचांगp16 = (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) ?
		0x2 : 0x9C40;
	b43_phy_ग_लिखो(dev, B43_NPHY_ENDROP_TLEN, पंचांगp16);

	b43_phy_maskset(dev, B43_NPHY_SGILTRNOFFSET, 0xF0FF, 0x0700);

	अगर (!b43_is_40mhz(dev)) अणु
		b43_ntab_ग_लिखो(dev, B43_NTAB32(16, 3), 0x18D);
		b43_ntab_ग_लिखो(dev, B43_NTAB32(16, 127), 0x18D);
	पूर्ण अन्यथा अणु
		b43_ntab_ग_लिखो(dev, B43_NTAB32(16, 3), 0x14D);
		b43_ntab_ग_लिखो(dev, B43_NTAB32(16, 127), 0x14D);
	पूर्ण

	b43_nphy_gain_ctl_workarounds(dev);

	b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 0), 2);
	b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 16), 2);

	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
		pdet_range = sprom->fem.ghz2.pdet_range;
	अन्यथा
		pdet_range = sprom->fem.ghz5.pdet_range;
	vmid = vmids[min_t(u16, pdet_range, 4)];
	gain = gains[min_t(u16, pdet_range, 4)];
	चयन (pdet_range) अणु
	हाल 3:
		अगर (!(dev->phy.rev >= 4 &&
		      b43_current_band(dev->wl) == NL80211_BAND_2GHZ))
			अवरोध;
		fallthrough;
	हाल 0:
	हाल 1:
		b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(8, 0x08), 4, vmid);
		b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(8, 0x18), 4, vmid);
		b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(8, 0x0c), 4, gain);
		b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(8, 0x1c), 4, gain);
		अवरोध;
	हाल 2:
		अगर (dev->phy.rev >= 6) अणु
			अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
				vmid[3] = 0x94;
			अन्यथा
				vmid[3] = 0x8e;
			gain[3] = 3;
		पूर्ण अन्यथा अगर (dev->phy.rev == 5) अणु
			vmid[3] = 0x84;
			gain[3] = 2;
		पूर्ण
		b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(8, 0x08), 4, vmid);
		b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(8, 0x18), 4, vmid);
		b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(8, 0x0c), 4, gain);
		b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(8, 0x1c), 4, gain);
		अवरोध;
	हाल 4:
	हाल 5:
		अगर (b43_current_band(dev->wl) != NL80211_BAND_2GHZ) अणु
			अगर (pdet_range == 4) अणु
				vmid[3] = 0x8e;
				पंचांगp16 = 0x96;
				gain[3] = 0x2;
			पूर्ण अन्यथा अणु
				vmid[3] = 0x89;
				पंचांगp16 = 0x89;
				gain[3] = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (pdet_range == 4) अणु
				vmid[3] = 0x89;
				पंचांगp16 = 0x8b;
				gain[3] = 0x2;
			पूर्ण अन्यथा अणु
				vmid[3] = 0x74;
				पंचांगp16 = 0x70;
				gain[3] = 0;
			पूर्ण
		पूर्ण
		b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(8, 0x08), 4, vmid);
		b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(8, 0x0c), 4, gain);
		vmid[3] = पंचांगp16;
		b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(8, 0x18), 4, vmid);
		b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(8, 0x1c), 4, gain);
		अवरोध;
	पूर्ण

	b43_radio_ग_लिखो(dev, B2056_RX0 | B2056_RX_MIXA_MAST_BIAS, 0x00);
	b43_radio_ग_लिखो(dev, B2056_RX1 | B2056_RX_MIXA_MAST_BIAS, 0x00);
	b43_radio_ग_लिखो(dev, B2056_RX0 | B2056_RX_MIXA_BIAS_MAIN, 0x06);
	b43_radio_ग_लिखो(dev, B2056_RX1 | B2056_RX_MIXA_BIAS_MAIN, 0x06);
	b43_radio_ग_लिखो(dev, B2056_RX0 | B2056_RX_MIXA_BIAS_AUX, 0x07);
	b43_radio_ग_लिखो(dev, B2056_RX1 | B2056_RX_MIXA_BIAS_AUX, 0x07);
	b43_radio_ग_लिखो(dev, B2056_RX0 | B2056_RX_MIXA_LOB_BIAS, 0x88);
	b43_radio_ग_लिखो(dev, B2056_RX1 | B2056_RX_MIXA_LOB_BIAS, 0x88);
	b43_radio_ग_लिखो(dev, B2056_RX0 | B2056_RX_MIXA_CMFB_IDAC, 0x00);
	b43_radio_ग_लिखो(dev, B2056_RX1 | B2056_RX_MIXA_CMFB_IDAC, 0x00);
	b43_radio_ग_लिखो(dev, B2056_RX0 | B2056_RX_MIXG_CMFB_IDAC, 0x00);
	b43_radio_ग_लिखो(dev, B2056_RX1 | B2056_RX_MIXG_CMFB_IDAC, 0x00);

	/* N PHY WAR TX Chain Update with hw_phytxchain as argument */

	अगर ((sprom->boardflags2_lo & B43_BFL2_APLL_WAR &&
	     b43_current_band(dev->wl) == NL80211_BAND_5GHZ) ||
	    (sprom->boardflags2_lo & B43_BFL2_GPLL_WAR &&
	     b43_current_band(dev->wl) == NL80211_BAND_2GHZ))
		पंचांगp32 = 0x00088888;
	अन्यथा
		पंचांगp32 = 0x88888888;
	b43_ntab_ग_लिखो(dev, B43_NTAB32(30, 1), पंचांगp32);
	b43_ntab_ग_लिखो(dev, B43_NTAB32(30, 2), पंचांगp32);
	b43_ntab_ग_लिखो(dev, B43_NTAB32(30, 3), पंचांगp32);

	अगर (dev->phy.rev == 4 &&
	    b43_current_band(dev->wl) == NL80211_BAND_5GHZ) अणु
		b43_radio_ग_लिखो(dev, B2056_TX0 | B2056_TX_GMBB_IDAC,
				0x70);
		b43_radio_ग_लिखो(dev, B2056_TX1 | B2056_TX_GMBB_IDAC,
				0x70);
	पूर्ण

	/* Dropped probably-always-true condition */
	b43_phy_ग_लिखो(dev, B43_NPHY_ED_CRS40ASSERTTHRESH0, 0x03eb);
	b43_phy_ग_लिखो(dev, B43_NPHY_ED_CRS40ASSERTTHRESH1, 0x03eb);
	b43_phy_ग_लिखो(dev, B43_NPHY_ED_CRS40DEASSERTTHRESH0, 0x0341);
	b43_phy_ग_लिखो(dev, B43_NPHY_ED_CRS40DEASSERTTHRESH1, 0x0341);
	b43_phy_ग_लिखो(dev, B43_NPHY_ED_CRS20LASSERTTHRESH0, 0x042b);
	b43_phy_ग_लिखो(dev, B43_NPHY_ED_CRS20LASSERTTHRESH1, 0x042b);
	b43_phy_ग_लिखो(dev, B43_NPHY_ED_CRS20LDEASSERTTHRESH0, 0x0381);
	b43_phy_ग_लिखो(dev, B43_NPHY_ED_CRS20LDEASSERTTHRESH1, 0x0381);
	b43_phy_ग_लिखो(dev, B43_NPHY_ED_CRS20UASSERTTHRESH0, 0x042b);
	b43_phy_ग_लिखो(dev, B43_NPHY_ED_CRS20UASSERTTHRESH1, 0x042b);
	b43_phy_ग_लिखो(dev, B43_NPHY_ED_CRS20UDEASSERTTHRESH0, 0x0381);
	b43_phy_ग_लिखो(dev, B43_NPHY_ED_CRS20UDEASSERTTHRESH1, 0x0381);

	अगर (dev->phy.rev >= 6 && sprom->boardflags2_lo & B43_BFL2_SINGLEANT_CCK) अणु
		; /* TODO: 0x0080000000000000 HF */
	पूर्ण
पूर्ण

अटल व्योम b43_nphy_workarounds_rev1_2(काष्ठा b43_wldev *dev)
अणु
	काष्ठा ssb_sprom *sprom = dev->dev->bus_sprom;
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_n *nphy = phy->n;

	u8 events1[7] = अणु 0x0, 0x1, 0x2, 0x8, 0x4, 0x5, 0x3 पूर्ण;
	u8 delays1[7] = अणु 0x8, 0x6, 0x6, 0x2, 0x4, 0x3C, 0x1 पूर्ण;

	u8 events2[7] = अणु 0x0, 0x3, 0x5, 0x4, 0x2, 0x1, 0x8 पूर्ण;
	u8 delays2[7] = अणु 0x8, 0x6, 0x2, 0x4, 0x4, 0x6, 0x1 पूर्ण;

	अगर (sprom->boardflags2_lo & B43_BFL2_SKWRKFEM_BRD ||
	    dev->dev->board_type == BCMA_BOARD_TYPE_BCM943224M93) अणु
		delays1[0] = 0x1;
		delays1[5] = 0x14;
	पूर्ण

	अगर (b43_current_band(dev->wl) == NL80211_BAND_5GHZ &&
	    nphy->band5g_pwrgain) अणु
		b43_radio_mask(dev, B2055_C1_TX_RF_SPARE, ~0x8);
		b43_radio_mask(dev, B2055_C2_TX_RF_SPARE, ~0x8);
	पूर्ण अन्यथा अणु
		b43_radio_set(dev, B2055_C1_TX_RF_SPARE, 0x8);
		b43_radio_set(dev, B2055_C2_TX_RF_SPARE, 0x8);
	पूर्ण

	b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 0x00), 0x000A);
	b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 0x10), 0x000A);
	अगर (dev->phy.rev < 3) अणु
		b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 0x02), 0xCDAA);
		b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 0x12), 0xCDAA);
	पूर्ण

	अगर (dev->phy.rev < 2) अणु
		b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 0x08), 0x0000);
		b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 0x18), 0x0000);
		b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 0x07), 0x7AAB);
		b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 0x17), 0x7AAB);
		b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 0x06), 0x0800);
		b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 0x16), 0x0800);
	पूर्ण

	b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_LUT_TRSW_LO1, 0x2D8);
	b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_LUT_TRSW_UP1, 0x301);
	b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_LUT_TRSW_LO2, 0x2D8);
	b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_LUT_TRSW_UP2, 0x301);

	b43_nphy_set_rf_sequence(dev, 0, events1, delays1, 7);
	b43_nphy_set_rf_sequence(dev, 1, events2, delays2, 7);

	b43_nphy_gain_ctl_workarounds(dev);

	अगर (dev->phy.rev < 2) अणु
		अगर (b43_phy_पढ़ो(dev, B43_NPHY_RXCTL) & 0x2)
			b43_hf_ग_लिखो(dev, b43_hf_पढ़ो(dev) |
					B43_HF_MLADVW);
	पूर्ण अन्यथा अगर (dev->phy.rev == 2) अणु
		b43_phy_ग_लिखो(dev, B43_NPHY_CRSCHECK2, 0);
		b43_phy_ग_लिखो(dev, B43_NPHY_CRSCHECK3, 0);
	पूर्ण

	अगर (dev->phy.rev < 2)
		b43_phy_mask(dev, B43_NPHY_SCRAM_SIGCTL,
				~B43_NPHY_SCRAM_SIGCTL_SCM);

	/* Set phase track alpha and beta */
	b43_phy_ग_लिखो(dev, B43_NPHY_PHASETR_A0, 0x125);
	b43_phy_ग_लिखो(dev, B43_NPHY_PHASETR_A1, 0x1B3);
	b43_phy_ग_लिखो(dev, B43_NPHY_PHASETR_A2, 0x105);
	b43_phy_ग_लिखो(dev, B43_NPHY_PHASETR_B0, 0x16E);
	b43_phy_ग_लिखो(dev, B43_NPHY_PHASETR_B1, 0xCD);
	b43_phy_ग_लिखो(dev, B43_NPHY_PHASETR_B2, 0x20);

	अगर (dev->phy.rev < 3) अणु
		b43_phy_mask(dev, B43_NPHY_PIL_DW1,
			     ~B43_NPHY_PIL_DW_64QAM & 0xFFFF);
		b43_phy_ग_लिखो(dev, B43_NPHY_TXF_20CO_S2B1, 0xB5);
		b43_phy_ग_लिखो(dev, B43_NPHY_TXF_20CO_S2B2, 0xA4);
		b43_phy_ग_लिखो(dev, B43_NPHY_TXF_20CO_S2B3, 0x00);
	पूर्ण

	अगर (dev->phy.rev == 2)
		b43_phy_set(dev, B43_NPHY_FINERX2_CGC,
				B43_NPHY_FINERX2_CGC_DECGC);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/Workarounds */
अटल व्योम b43_nphy_workarounds(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_n *nphy = phy->n;

	अगर (b43_current_band(dev->wl) == NL80211_BAND_5GHZ)
		b43_nphy_classअगरier(dev, 1, 0);
	अन्यथा
		b43_nphy_classअगरier(dev, 1, 1);

	अगर (nphy->hang_aव्योम)
		b43_nphy_stay_in_carrier_search(dev, 1);

	b43_phy_set(dev, B43_NPHY_IQFLIP,
		    B43_NPHY_IQFLIP_ADC1 | B43_NPHY_IQFLIP_ADC2);

	/* TODO: rev19+ */
	अगर (dev->phy.rev >= 7)
		b43_nphy_workarounds_rev7plus(dev);
	अन्यथा अगर (dev->phy.rev >= 3)
		b43_nphy_workarounds_rev3plus(dev);
	अन्यथा
		b43_nphy_workarounds_rev1_2(dev);

	अगर (nphy->hang_aव्योम)
		b43_nphy_stay_in_carrier_search(dev, 0);
पूर्ण

/**************************************************
 * Tx/Rx common
 **************************************************/

/*
 * Transmits a known value क्रम LO calibration
 * https://bcm-v4.sipsolutions.net/802.11/PHY/N/TXTone
 */
अटल पूर्णांक b43_nphy_tx_tone(काष्ठा b43_wldev *dev, u32 freq, u16 max_val,
			    bool iqmode, bool dac_test, bool modअगरy_bbmult)
अणु
	u16 samp = b43_nphy_gen_load_samples(dev, freq, max_val, dac_test);
	अगर (samp == 0)
		वापस -1;
	b43_nphy_run_samples(dev, samp, 0xFFFF, 0, iqmode, dac_test,
			     modअगरy_bbmult);
	वापस 0;
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/Chains */
अटल व्योम b43_nphy_update_txrx_chain(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_n *nphy = dev->phy.n;

	bool override = false;
	u16 chain = 0x33;

	अगर (nphy->txrx_chain == 0) अणु
		chain = 0x11;
		override = true;
	पूर्ण अन्यथा अगर (nphy->txrx_chain == 1) अणु
		chain = 0x22;
		override = true;
	पूर्ण

	b43_phy_maskset(dev, B43_NPHY_RFSEQCA,
			~(B43_NPHY_RFSEQCA_TXEN | B43_NPHY_RFSEQCA_RXEN),
			chain);

	अगर (override)
		b43_phy_set(dev, B43_NPHY_RFSEQMODE,
				B43_NPHY_RFSEQMODE_CAOVER);
	अन्यथा
		b43_phy_mask(dev, B43_NPHY_RFSEQMODE,
				~B43_NPHY_RFSEQMODE_CAOVER);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/stop-playback */
अटल व्योम b43_nphy_stop_playback(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_n *nphy = dev->phy.n;
	u16 पंचांगp;

	अगर (nphy->hang_aव्योम)
		b43_nphy_stay_in_carrier_search(dev, 1);

	पंचांगp = b43_phy_पढ़ो(dev, B43_NPHY_SAMP_STAT);
	अगर (पंचांगp & 0x1)
		b43_phy_set(dev, B43_NPHY_SAMP_CMD, B43_NPHY_SAMP_CMD_STOP);
	अन्यथा अगर (पंचांगp & 0x2)
		b43_phy_mask(dev, B43_NPHY_IQLOCAL_CMDGCTL, 0x7FFF);

	b43_phy_mask(dev, B43_NPHY_SAMP_CMD, ~0x0004);

	अगर (nphy->bb_mult_save & 0x80000000) अणु
		पंचांगp = nphy->bb_mult_save & 0xFFFF;
		b43_ntab_ग_लिखो(dev, B43_NTAB16(15, 87), पंचांगp);
		nphy->bb_mult_save = 0;
	पूर्ण

	अगर (phy->rev >= 7 && nphy->lpf_bw_overrode_क्रम_sample_play) अणु
		अगर (phy->rev >= 19)
			b43_nphy_rf_ctl_override_rev19(dev, 0x80, 0, 0, true,
						       1);
		अन्यथा
			b43_nphy_rf_ctl_override_rev7(dev, 0x80, 0, 0, true, 1);
		nphy->lpf_bw_overrode_क्रम_sample_play = false;
	पूर्ण

	अगर (nphy->hang_aव्योम)
		b43_nphy_stay_in_carrier_search(dev, 0);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/IqCalGainParams */
अटल व्योम b43_nphy_iq_cal_gain_params(काष्ठा b43_wldev *dev, u16 core,
					काष्ठा nphy_txgains target,
					काष्ठा nphy_iqcal_params *params)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	पूर्णांक i, j, indx;
	u16 gain;

	अगर (dev->phy.rev >= 3) अणु
		params->tx_lpf = target.tx_lpf[core]; /* Rev 7+ */
		params->txgm = target.txgm[core];
		params->pga = target.pga[core];
		params->pad = target.pad[core];
		params->ipa = target.ipa[core];
		अगर (phy->rev >= 19) अणु
			/* TODO */
		पूर्ण अन्यथा अगर (phy->rev >= 7) अणु
			params->cal_gain = (params->txgm << 12) | (params->pga << 8) | (params->pad << 3) | (params->ipa) | (params->tx_lpf << 15);
		पूर्ण अन्यथा अणु
			params->cal_gain = (params->txgm << 12) | (params->pga << 8) | (params->pad << 4) | (params->ipa);
		पूर्ण
		क्रम (j = 0; j < 5; j++)
			params->ncorr[j] = 0x79;
	पूर्ण अन्यथा अणु
		gain = (target.pad[core]) | (target.pga[core] << 4) |
			(target.txgm[core] << 8);

		indx = (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) ?
			1 : 0;
		क्रम (i = 0; i < 9; i++)
			अगर (tbl_iqcal_gainparams[indx][i][0] == gain)
				अवरोध;
		i = min(i, 8);

		params->txgm = tbl_iqcal_gainparams[indx][i][1];
		params->pga = tbl_iqcal_gainparams[indx][i][2];
		params->pad = tbl_iqcal_gainparams[indx][i][3];
		params->cal_gain = (params->txgm << 7) | (params->pga << 4) |
					(params->pad << 2);
		क्रम (j = 0; j < 4; j++)
			params->ncorr[j] = tbl_iqcal_gainparams[indx][i][4 + j];
	पूर्ण
पूर्ण

/**************************************************
 * Tx and Rx
 **************************************************/

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/TxPwrCtrlEnable */
अटल व्योम b43_nphy_tx_घातer_ctrl(काष्ठा b43_wldev *dev, bool enable)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_n *nphy = dev->phy.n;
	u8 i;
	u16 bmask, val, पंचांगp;
	क्रमागत nl80211_band band = b43_current_band(dev->wl);

	अगर (nphy->hang_aव्योम)
		b43_nphy_stay_in_carrier_search(dev, 1);

	nphy->txpwrctrl = enable;
	अगर (!enable) अणु
		अगर (dev->phy.rev >= 3 &&
		    (b43_phy_पढ़ो(dev, B43_NPHY_TXPCTL_CMD) &
		     (B43_NPHY_TXPCTL_CMD_COEFF |
		      B43_NPHY_TXPCTL_CMD_HWPCTLEN |
		      B43_NPHY_TXPCTL_CMD_PCTLEN))) अणु
			/* We disable enabled TX pwr ctl, save it's state */
			nphy->tx_pwr_idx[0] = b43_phy_पढ़ो(dev,
						B43_NPHY_C1_TXPCTL_STAT) & 0x7f;
			nphy->tx_pwr_idx[1] = b43_phy_पढ़ो(dev,
						B43_NPHY_C2_TXPCTL_STAT) & 0x7f;
		पूर्ण

		b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_ADDR, 0x6840);
		क्रम (i = 0; i < 84; i++)
			b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_DATALO, 0);

		b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_ADDR, 0x6C40);
		क्रम (i = 0; i < 84; i++)
			b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_DATALO, 0);

		पंचांगp = B43_NPHY_TXPCTL_CMD_COEFF | B43_NPHY_TXPCTL_CMD_HWPCTLEN;
		अगर (dev->phy.rev >= 3)
			पंचांगp |= B43_NPHY_TXPCTL_CMD_PCTLEN;
		b43_phy_mask(dev, B43_NPHY_TXPCTL_CMD, ~पंचांगp);

		अगर (dev->phy.rev >= 3) अणु
			b43_phy_set(dev, B43_NPHY_AFECTL_OVER1, 0x0100);
			b43_phy_set(dev, B43_NPHY_AFECTL_OVER, 0x0100);
		पूर्ण अन्यथा अणु
			b43_phy_set(dev, B43_NPHY_AFECTL_OVER, 0x4000);
		पूर्ण

		अगर (dev->phy.rev == 2)
			b43_phy_maskset(dev, B43_NPHY_BPHY_CTL3,
				~B43_NPHY_BPHY_CTL3_SCALE, 0x53);
		अन्यथा अगर (dev->phy.rev < 2)
			b43_phy_maskset(dev, B43_NPHY_BPHY_CTL3,
				~B43_NPHY_BPHY_CTL3_SCALE, 0x5A);

		अगर (dev->phy.rev < 2 && b43_is_40mhz(dev))
			b43_hf_ग_लिखो(dev, b43_hf_पढ़ो(dev) | B43_HF_TSSIRPSMW);
	पूर्ण अन्यथा अणु
		b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(26, 64), 84,
				    nphy->adj_pwr_tbl);
		b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(27, 64), 84,
				    nphy->adj_pwr_tbl);

		bmask = B43_NPHY_TXPCTL_CMD_COEFF |
			B43_NPHY_TXPCTL_CMD_HWPCTLEN;
		/* wl करोes useless check क्रम "enable" param here */
		val = B43_NPHY_TXPCTL_CMD_COEFF | B43_NPHY_TXPCTL_CMD_HWPCTLEN;
		अगर (dev->phy.rev >= 3) अणु
			bmask |= B43_NPHY_TXPCTL_CMD_PCTLEN;
			अगर (val)
				val |= B43_NPHY_TXPCTL_CMD_PCTLEN;
		पूर्ण
		b43_phy_maskset(dev, B43_NPHY_TXPCTL_CMD, ~(bmask), val);

		अगर (band == NL80211_BAND_5GHZ) अणु
			अगर (phy->rev >= 19) अणु
				/* TODO */
			पूर्ण अन्यथा अगर (phy->rev >= 7) अणु
				b43_phy_maskset(dev, B43_NPHY_TXPCTL_CMD,
						~B43_NPHY_TXPCTL_CMD_INIT,
						0x32);
				b43_phy_maskset(dev, B43_NPHY_TXPCTL_INIT,
						~B43_NPHY_TXPCTL_INIT_PIDXI1,
						0x32);
			पूर्ण अन्यथा अणु
				b43_phy_maskset(dev, B43_NPHY_TXPCTL_CMD,
						~B43_NPHY_TXPCTL_CMD_INIT,
						0x64);
				अगर (phy->rev > 1)
					b43_phy_maskset(dev,
							B43_NPHY_TXPCTL_INIT,
							~B43_NPHY_TXPCTL_INIT_PIDXI1,
							0x64);
			पूर्ण
		पूर्ण

		अगर (dev->phy.rev >= 3) अणु
			अगर (nphy->tx_pwr_idx[0] != 128 &&
			    nphy->tx_pwr_idx[1] != 128) अणु
				/* Recover TX pwr ctl state */
				b43_phy_maskset(dev, B43_NPHY_TXPCTL_CMD,
						~B43_NPHY_TXPCTL_CMD_INIT,
						nphy->tx_pwr_idx[0]);
				अगर (dev->phy.rev > 1)
					b43_phy_maskset(dev,
						B43_NPHY_TXPCTL_INIT,
						~0xff, nphy->tx_pwr_idx[1]);
			पूर्ण
		पूर्ण

		अगर (phy->rev >= 7) अणु
			/* TODO */
		पूर्ण

		अगर (dev->phy.rev >= 3) अणु
			b43_phy_mask(dev, B43_NPHY_AFECTL_OVER1, ~0x100);
			b43_phy_mask(dev, B43_NPHY_AFECTL_OVER, ~0x100);
		पूर्ण अन्यथा अणु
			b43_phy_mask(dev, B43_NPHY_AFECTL_OVER, ~0x4000);
		पूर्ण

		अगर (dev->phy.rev == 2)
			b43_phy_maskset(dev, B43_NPHY_BPHY_CTL3, ~0xFF, 0x3b);
		अन्यथा अगर (dev->phy.rev < 2)
			b43_phy_maskset(dev, B43_NPHY_BPHY_CTL3, ~0xFF, 0x40);

		अगर (dev->phy.rev < 2 && b43_is_40mhz(dev))
			b43_hf_ग_लिखो(dev, b43_hf_पढ़ो(dev) & ~B43_HF_TSSIRPSMW);

		अगर (b43_nphy_ipa(dev)) अणु
			b43_phy_mask(dev, B43_NPHY_PAPD_EN0, ~0x4);
			b43_phy_mask(dev, B43_NPHY_PAPD_EN1, ~0x4);
		पूर्ण
	पूर्ण

	अगर (nphy->hang_aव्योम)
		b43_nphy_stay_in_carrier_search(dev, 0);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/TxPwrFix */
अटल व्योम b43_nphy_tx_घातer_fix(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_n *nphy = dev->phy.n;
	काष्ठा ssb_sprom *sprom = dev->dev->bus_sprom;

	u8 txpi[2], bbmult, i;
	u16 पंचांगp, radio_gain, dac_gain;
	u16 freq = phy->chandef->chan->center_freq;
	u32 txgain;
	/* u32 gaपूर्णांकbl; rev3+ */

	अगर (nphy->hang_aव्योम)
		b43_nphy_stay_in_carrier_search(dev, 1);

	/* TODO: rev19+ */
	अगर (dev->phy.rev >= 7) अणु
		txpi[0] = txpi[1] = 30;
	पूर्ण अन्यथा अगर (dev->phy.rev >= 3) अणु
		txpi[0] = 40;
		txpi[1] = 40;
	पूर्ण अन्यथा अगर (sprom->revision < 4) अणु
		txpi[0] = 72;
		txpi[1] = 72;
	पूर्ण अन्यथा अणु
		अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
			txpi[0] = sprom->txpid2g[0];
			txpi[1] = sprom->txpid2g[1];
		पूर्ण अन्यथा अगर (freq >= 4900 && freq < 5100) अणु
			txpi[0] = sprom->txpid5gl[0];
			txpi[1] = sprom->txpid5gl[1];
		पूर्ण अन्यथा अगर (freq >= 5100 && freq < 5500) अणु
			txpi[0] = sprom->txpid5g[0];
			txpi[1] = sprom->txpid5g[1];
		पूर्ण अन्यथा अगर (freq >= 5500) अणु
			txpi[0] = sprom->txpid5gh[0];
			txpi[1] = sprom->txpid5gh[1];
		पूर्ण अन्यथा अणु
			txpi[0] = 91;
			txpi[1] = 91;
		पूर्ण
	पूर्ण
	अगर (dev->phy.rev < 7 &&
	    (txpi[0] < 40 || txpi[0] > 100 || txpi[1] < 40 || txpi[1] > 100))
		txpi[0] = txpi[1] = 91;

	/*
	क्रम (i = 0; i < 2; i++) अणु
		nphy->txpwrindex[i].index_पूर्णांकernal = txpi[i];
		nphy->txpwrindex[i].index_पूर्णांकernal_save = txpi[i];
	पूर्ण
	*/

	क्रम (i = 0; i < 2; i++) अणु
		स्थिर u32 *table = b43_nphy_get_tx_gain_table(dev);

		अगर (!table)
			अवरोध;
		txgain = *(table + txpi[i]);

		अगर (dev->phy.rev >= 3)
			radio_gain = (txgain >> 16) & 0x1FFFF;
		अन्यथा
			radio_gain = (txgain >> 16) & 0x1FFF;

		अगर (dev->phy.rev >= 7)
			dac_gain = (txgain >> 8) & 0x7;
		अन्यथा
			dac_gain = (txgain >> 8) & 0x3F;
		bbmult = txgain & 0xFF;

		अगर (dev->phy.rev >= 3) अणु
			अगर (i == 0)
				b43_phy_set(dev, B43_NPHY_AFECTL_OVER1, 0x0100);
			अन्यथा
				b43_phy_set(dev, B43_NPHY_AFECTL_OVER, 0x0100);
		पूर्ण अन्यथा अणु
			b43_phy_set(dev, B43_NPHY_AFECTL_OVER, 0x4000);
		पूर्ण

		अगर (i == 0)
			b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_DACGAIN1, dac_gain);
		अन्यथा
			b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_DACGAIN2, dac_gain);

		b43_ntab_ग_लिखो(dev, B43_NTAB16(0x7, 0x110 + i), radio_gain);

		पंचांगp = b43_ntab_पढ़ो(dev, B43_NTAB16(0xF, 0x57));
		अगर (i == 0)
			पंचांगp = (पंचांगp & 0x00FF) | (bbmult << 8);
		अन्यथा
			पंचांगp = (पंचांगp & 0xFF00) | bbmult;
		b43_ntab_ग_लिखो(dev, B43_NTAB16(0xF, 0x57), पंचांगp);

		अगर (b43_nphy_ipa(dev)) अणु
			u32 पंचांगp32;
			u16 reg = (i == 0) ?
				B43_NPHY_PAPD_EN0 : B43_NPHY_PAPD_EN1;
			पंचांगp32 = b43_ntab_पढ़ो(dev, B43_NTAB32(26 + i,
							      576 + txpi[i]));
			b43_phy_maskset(dev, reg, 0xE00F, (u32) पंचांगp32 << 4);
			b43_phy_set(dev, reg, 0x4);
		पूर्ण
	पूर्ण

	b43_phy_mask(dev, B43_NPHY_BPHY_CTL2, ~B43_NPHY_BPHY_CTL2_LUT);

	अगर (nphy->hang_aव्योम)
		b43_nphy_stay_in_carrier_search(dev, 0);
पूर्ण

अटल व्योम b43_nphy_ipa_पूर्णांकernal_tssi_setup(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;

	u8 core;
	u16 r; /* routing */

	अगर (phy->rev >= 19) अणु
		/* TODO */
	पूर्ण अन्यथा अगर (phy->rev >= 7) अणु
		क्रम (core = 0; core < 2; core++) अणु
			r = core ? 0x190 : 0x170;
			अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
				b43_radio_ग_लिखो(dev, r + 0x5, 0x5);
				b43_radio_ग_लिखो(dev, r + 0x9, 0xE);
				अगर (phy->rev != 5)
					b43_radio_ग_लिखो(dev, r + 0xA, 0);
				अगर (phy->rev != 7)
					b43_radio_ग_लिखो(dev, r + 0xB, 1);
				अन्यथा
					b43_radio_ग_लिखो(dev, r + 0xB, 0x31);
			पूर्ण अन्यथा अणु
				b43_radio_ग_लिखो(dev, r + 0x5, 0x9);
				b43_radio_ग_लिखो(dev, r + 0x9, 0xC);
				b43_radio_ग_लिखो(dev, r + 0xB, 0x0);
				अगर (phy->rev != 5)
					b43_radio_ग_लिखो(dev, r + 0xA, 1);
				अन्यथा
					b43_radio_ग_लिखो(dev, r + 0xA, 0x31);
			पूर्ण
			b43_radio_ग_लिखो(dev, r + 0x6, 0);
			b43_radio_ग_लिखो(dev, r + 0x7, 0);
			b43_radio_ग_लिखो(dev, r + 0x8, 3);
			b43_radio_ग_लिखो(dev, r + 0xC, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
			b43_radio_ग_लिखो(dev, B2056_SYN_RESERVED_ADDR31, 0x128);
		अन्यथा
			b43_radio_ग_लिखो(dev, B2056_SYN_RESERVED_ADDR31, 0x80);
		b43_radio_ग_लिखो(dev, B2056_SYN_RESERVED_ADDR30, 0);
		b43_radio_ग_लिखो(dev, B2056_SYN_GPIO_MASTER1, 0x29);

		क्रम (core = 0; core < 2; core++) अणु
			r = core ? B2056_TX1 : B2056_TX0;

			b43_radio_ग_लिखो(dev, r | B2056_TX_IQCAL_VCM_HG, 0);
			b43_radio_ग_लिखो(dev, r | B2056_TX_IQCAL_IDAC, 0);
			b43_radio_ग_लिखो(dev, r | B2056_TX_TSSI_VCM, 3);
			b43_radio_ग_लिखो(dev, r | B2056_TX_TX_AMP_DET, 0);
			b43_radio_ग_लिखो(dev, r | B2056_TX_TSSI_MISC1, 8);
			b43_radio_ग_लिखो(dev, r | B2056_TX_TSSI_MISC2, 0);
			b43_radio_ग_लिखो(dev, r | B2056_TX_TSSI_MISC3, 0);
			अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
				b43_radio_ग_लिखो(dev, r | B2056_TX_TX_SSI_MASTER,
						0x5);
				अगर (phy->rev != 5)
					b43_radio_ग_लिखो(dev, r | B2056_TX_TSSIA,
							0x00);
				अगर (phy->rev >= 5)
					b43_radio_ग_लिखो(dev, r | B2056_TX_TSSIG,
							0x31);
				अन्यथा
					b43_radio_ग_लिखो(dev, r | B2056_TX_TSSIG,
							0x11);
				b43_radio_ग_लिखो(dev, r | B2056_TX_TX_SSI_MUX,
						0xE);
			पूर्ण अन्यथा अणु
				b43_radio_ग_लिखो(dev, r | B2056_TX_TX_SSI_MASTER,
						0x9);
				b43_radio_ग_लिखो(dev, r | B2056_TX_TSSIA, 0x31);
				b43_radio_ग_लिखो(dev, r | B2056_TX_TSSIG, 0x0);
				b43_radio_ग_लिखो(dev, r | B2056_TX_TX_SSI_MUX,
						0xC);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Stop radio and transmit known संकेत. Then check received संकेत strength to
 * get TSSI (Transmit Signal Strength Indicator).
 * https://bcm-v4.sipsolutions.net/802.11/PHY/N/TxPwrCtrlIdleTssi
 */
अटल व्योम b43_nphy_tx_घातer_ctl_idle_tssi(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_n *nphy = dev->phy.n;

	u32 पंचांगp;
	s32 rssi[4] = अणु पूर्ण;

	अगर (phy->chandef->chan->flags & IEEE80211_CHAN_NO_IR)
		वापस;

	अगर (b43_nphy_ipa(dev))
		b43_nphy_ipa_पूर्णांकernal_tssi_setup(dev);

	अगर (phy->rev >= 19)
		b43_nphy_rf_ctl_override_rev19(dev, 0x1000, 0, 3, false, 0);
	अन्यथा अगर (phy->rev >= 7)
		b43_nphy_rf_ctl_override_rev7(dev, 0x1000, 0, 3, false, 0);
	अन्यथा अगर (phy->rev >= 3)
		b43_nphy_rf_ctl_override(dev, 0x2000, 0, 3, false);

	b43_nphy_stop_playback(dev);
	b43_nphy_tx_tone(dev, 4000, 0, false, false, false);
	udelay(20);
	पंचांगp = b43_nphy_poll_rssi(dev, N_RSSI_TSSI_2G, rssi, 1);
	b43_nphy_stop_playback(dev);

	b43_nphy_rssi_select(dev, 0, N_RSSI_W1);

	अगर (phy->rev >= 19)
		b43_nphy_rf_ctl_override_rev19(dev, 0x1000, 0, 3, true, 0);
	अन्यथा अगर (phy->rev >= 7)
		b43_nphy_rf_ctl_override_rev7(dev, 0x1000, 0, 3, true, 0);
	अन्यथा अगर (phy->rev >= 3)
		b43_nphy_rf_ctl_override(dev, 0x2000, 0, 3, true);

	अगर (phy->rev >= 19) अणु
		/* TODO */
		वापस;
	पूर्ण अन्यथा अगर (phy->rev >= 3) अणु
		nphy->pwr_ctl_info[0].idle_tssi_5g = (पंचांगp >> 24) & 0xFF;
		nphy->pwr_ctl_info[1].idle_tssi_5g = (पंचांगp >> 8) & 0xFF;
	पूर्ण अन्यथा अणु
		nphy->pwr_ctl_info[0].idle_tssi_5g = (पंचांगp >> 16) & 0xFF;
		nphy->pwr_ctl_info[1].idle_tssi_5g = पंचांगp & 0xFF;
	पूर्ण
	nphy->pwr_ctl_info[0].idle_tssi_2g = (पंचांगp >> 24) & 0xFF;
	nphy->pwr_ctl_info[1].idle_tssi_2g = (पंचांगp >> 8) & 0xFF;
पूर्ण

/* https://bcm-v4.sipsolutions.net/PHY/N/TxPwrLimitToTbl */
अटल व्योम b43_nphy_tx_prepare_adjusted_घातer_table(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_n *nphy = dev->phy.n;

	u8 idx, delta;
	u8 i, stf_mode;

	/* Array adj_pwr_tbl corresponds to the hardware table. It consists of
	 * 21 groups, each containing 4 entries.
	 *
	 * First group has entries क्रम CCK modulation.
	 * The rest of groups has 1 entry per modulation (SISO, CDD, STBC, SDM).
	 *
	 * Group 0 is क्रम CCK
	 * Groups 1..4 use BPSK (group per coding rate)
	 * Groups 5..8 use QPSK (group per coding rate)
	 * Groups 9..12 use 16-QAM (group per coding rate)
	 * Groups 13..16 use 64-QAM (group per coding rate)
	 * Groups 17..20 are unknown
	 */

	क्रम (i = 0; i < 4; i++)
		nphy->adj_pwr_tbl[i] = nphy->tx_घातer_offset[i];

	क्रम (stf_mode = 0; stf_mode < 4; stf_mode++) अणु
		delta = 0;
		चयन (stf_mode) अणु
		हाल 0:
			अगर (b43_is_40mhz(dev) && dev->phy.rev >= 5) अणु
				idx = 68;
			पूर्ण अन्यथा अणु
				delta = 1;
				idx = b43_is_40mhz(dev) ? 52 : 4;
			पूर्ण
			अवरोध;
		हाल 1:
			idx = b43_is_40mhz(dev) ? 76 : 28;
			अवरोध;
		हाल 2:
			idx = b43_is_40mhz(dev) ? 84 : 36;
			अवरोध;
		हाल 3:
			idx = b43_is_40mhz(dev) ? 92 : 44;
			अवरोध;
		पूर्ण

		क्रम (i = 0; i < 20; i++) अणु
			nphy->adj_pwr_tbl[4 + 4 * i + stf_mode] =
				nphy->tx_घातer_offset[idx];
			अगर (i == 0)
				idx += delta;
			अगर (i == 14)
				idx += 1 - delta;
			अगर (i == 3 || i == 4 || i == 7 || i == 8 || i == 11 ||
			    i == 13)
				idx += 1;
		पूर्ण
	पूर्ण
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/TxPwrCtrlSetup */
अटल व्योम b43_nphy_tx_घातer_ctl_setup(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_n *nphy = dev->phy.n;
	काष्ठा ssb_sprom *sprom = dev->dev->bus_sprom;

	s16 a1[2], b0[2], b1[2];
	u8 idle[2];
	u8 ppr_max;
	s8 target[2];
	s32 num, den, pwr;
	u32 regval[64];

	u16 freq = phy->chandef->chan->center_freq;
	u16 पंचांगp;
	u16 r; /* routing */
	u8 i, c;

	अगर (dev->dev->core_rev == 11 || dev->dev->core_rev == 12) अणु
		b43_maskset32(dev, B43_MMIO_MACCTL, ~0, 0x200000);
		b43_पढ़ो32(dev, B43_MMIO_MACCTL);
		udelay(1);
	पूर्ण

	अगर (nphy->hang_aव्योम)
		b43_nphy_stay_in_carrier_search(dev, true);

	b43_phy_set(dev, B43_NPHY_TSSIMODE, B43_NPHY_TSSIMODE_EN);
	अगर (dev->phy.rev >= 3)
		b43_phy_mask(dev, B43_NPHY_TXPCTL_CMD,
			     ~B43_NPHY_TXPCTL_CMD_PCTLEN & 0xFFFF);
	अन्यथा
		b43_phy_set(dev, B43_NPHY_TXPCTL_CMD,
			    B43_NPHY_TXPCTL_CMD_PCTLEN);

	अगर (dev->dev->core_rev == 11 || dev->dev->core_rev == 12)
		b43_maskset32(dev, B43_MMIO_MACCTL, ~0x200000, 0);

	अगर (sprom->revision < 4) अणु
		idle[0] = nphy->pwr_ctl_info[0].idle_tssi_2g;
		idle[1] = nphy->pwr_ctl_info[1].idle_tssi_2g;
		target[0] = target[1] = 52;
		a1[0] = a1[1] = -424;
		b0[0] = b0[1] = 5612;
		b1[0] = b1[1] = -1393;
	पूर्ण अन्यथा अणु
		अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
			क्रम (c = 0; c < 2; c++) अणु
				idle[c] = nphy->pwr_ctl_info[c].idle_tssi_2g;
				target[c] = sprom->core_pwr_info[c].maxpwr_2g;
				a1[c] = sprom->core_pwr_info[c].pa_2g[0];
				b0[c] = sprom->core_pwr_info[c].pa_2g[1];
				b1[c] = sprom->core_pwr_info[c].pa_2g[2];
			पूर्ण
		पूर्ण अन्यथा अगर (freq >= 4900 && freq < 5100) अणु
			क्रम (c = 0; c < 2; c++) अणु
				idle[c] = nphy->pwr_ctl_info[c].idle_tssi_5g;
				target[c] = sprom->core_pwr_info[c].maxpwr_5gl;
				a1[c] = sprom->core_pwr_info[c].pa_5gl[0];
				b0[c] = sprom->core_pwr_info[c].pa_5gl[1];
				b1[c] = sprom->core_pwr_info[c].pa_5gl[2];
			पूर्ण
		पूर्ण अन्यथा अगर (freq >= 5100 && freq < 5500) अणु
			क्रम (c = 0; c < 2; c++) अणु
				idle[c] = nphy->pwr_ctl_info[c].idle_tssi_5g;
				target[c] = sprom->core_pwr_info[c].maxpwr_5g;
				a1[c] = sprom->core_pwr_info[c].pa_5g[0];
				b0[c] = sprom->core_pwr_info[c].pa_5g[1];
				b1[c] = sprom->core_pwr_info[c].pa_5g[2];
			पूर्ण
		पूर्ण अन्यथा अगर (freq >= 5500) अणु
			क्रम (c = 0; c < 2; c++) अणु
				idle[c] = nphy->pwr_ctl_info[c].idle_tssi_5g;
				target[c] = sprom->core_pwr_info[c].maxpwr_5gh;
				a1[c] = sprom->core_pwr_info[c].pa_5gh[0];
				b0[c] = sprom->core_pwr_info[c].pa_5gh[1];
				b1[c] = sprom->core_pwr_info[c].pa_5gh[2];
			पूर्ण
		पूर्ण अन्यथा अणु
			idle[0] = nphy->pwr_ctl_info[0].idle_tssi_5g;
			idle[1] = nphy->pwr_ctl_info[1].idle_tssi_5g;
			target[0] = target[1] = 52;
			a1[0] = a1[1] = -424;
			b0[0] = b0[1] = 5612;
			b1[0] = b1[1] = -1393;
		पूर्ण
	पूर्ण

	ppr_max = b43_ppr_get_max(dev, &nphy->tx_pwr_max_ppr);
	अगर (ppr_max) अणु
		target[0] = ppr_max;
		target[1] = ppr_max;
	पूर्ण

	अगर (dev->phy.rev >= 3) अणु
		अगर (sprom->fem.ghz2.tssipos)
			b43_phy_set(dev, B43_NPHY_TXPCTL_ITSSI, 0x4000);
		अगर (dev->phy.rev >= 7) अणु
			क्रम (c = 0; c < 2; c++) अणु
				r = c ? 0x190 : 0x170;
				अगर (b43_nphy_ipa(dev))
					b43_radio_ग_लिखो(dev, r + 0x9, (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) ? 0xE : 0xC);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (b43_nphy_ipa(dev)) अणु
				पंचांगp = (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) ? 0xC : 0xE;
				b43_radio_ग_लिखो(dev,
					B2056_TX0 | B2056_TX_TX_SSI_MUX, पंचांगp);
				b43_radio_ग_लिखो(dev,
					B2056_TX1 | B2056_TX_TX_SSI_MUX, पंचांगp);
			पूर्ण अन्यथा अणु
				b43_radio_ग_लिखो(dev,
					B2056_TX0 | B2056_TX_TX_SSI_MUX, 0x11);
				b43_radio_ग_लिखो(dev,
					B2056_TX1 | B2056_TX_TX_SSI_MUX, 0x11);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (dev->dev->core_rev == 11 || dev->dev->core_rev == 12) अणु
		b43_maskset32(dev, B43_MMIO_MACCTL, ~0, 0x200000);
		b43_पढ़ो32(dev, B43_MMIO_MACCTL);
		udelay(1);
	पूर्ण

	अगर (phy->rev >= 19) अणु
		/* TODO */
	पूर्ण अन्यथा अगर (phy->rev >= 7) अणु
		b43_phy_maskset(dev, B43_NPHY_TXPCTL_CMD,
				~B43_NPHY_TXPCTL_CMD_INIT, 0x19);
		b43_phy_maskset(dev, B43_NPHY_TXPCTL_INIT,
				~B43_NPHY_TXPCTL_INIT_PIDXI1, 0x19);
	पूर्ण अन्यथा अणु
		b43_phy_maskset(dev, B43_NPHY_TXPCTL_CMD,
				~B43_NPHY_TXPCTL_CMD_INIT, 0x40);
		अगर (dev->phy.rev > 1)
			b43_phy_maskset(dev, B43_NPHY_TXPCTL_INIT,
				~B43_NPHY_TXPCTL_INIT_PIDXI1, 0x40);
	पूर्ण

	अगर (dev->dev->core_rev == 11 || dev->dev->core_rev == 12)
		b43_maskset32(dev, B43_MMIO_MACCTL, ~0x200000, 0);

	b43_phy_ग_लिखो(dev, B43_NPHY_TXPCTL_N,
		      0xF0 << B43_NPHY_TXPCTL_N_TSSID_SHIFT |
		      3 << B43_NPHY_TXPCTL_N_NPTIL2_SHIFT);
	b43_phy_ग_लिखो(dev, B43_NPHY_TXPCTL_ITSSI,
		      idle[0] << B43_NPHY_TXPCTL_ITSSI_0_SHIFT |
		      idle[1] << B43_NPHY_TXPCTL_ITSSI_1_SHIFT |
		      B43_NPHY_TXPCTL_ITSSI_BINF);
	b43_phy_ग_लिखो(dev, B43_NPHY_TXPCTL_TPWR,
		      target[0] << B43_NPHY_TXPCTL_TPWR_0_SHIFT |
		      target[1] << B43_NPHY_TXPCTL_TPWR_1_SHIFT);

	क्रम (c = 0; c < 2; c++) अणु
		क्रम (i = 0; i < 64; i++) अणु
			num = 8 * (16 * b0[c] + b1[c] * i);
			den = 32768 + a1[c] * i;
			pwr = max((4 * num + den / 2) / den, -8);
			अगर (dev->phy.rev < 3 && (i <= (31 - idle[c] + 1)))
				pwr = max(pwr, target[c] + 1);
			regval[i] = pwr;
		पूर्ण
		b43_ntab_ग_लिखो_bulk(dev, B43_NTAB32(26 + c, 0), 64, regval);
	पूर्ण

	b43_nphy_tx_prepare_adjusted_घातer_table(dev);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(26, 64), 84, nphy->adj_pwr_tbl);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(27, 64), 84, nphy->adj_pwr_tbl);

	अगर (nphy->hang_aव्योम)
		b43_nphy_stay_in_carrier_search(dev, false);
पूर्ण

अटल व्योम b43_nphy_tx_gain_table_upload(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;

	स्थिर u32 *table = शून्य;
	u32 rfpwr_offset;
	u8 pga_gain, pad_gain;
	पूर्णांक i;
	स्थिर s16 *rf_pwr_offset_table = शून्य;

	table = b43_nphy_get_tx_gain_table(dev);
	अगर (!table)
		वापस;

	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB32(26, 192), 128, table);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB32(27, 192), 128, table);

	अगर (phy->rev < 3)
		वापस;

#अगर 0
	nphy->gmval = (table[0] >> 16) & 0x7000;
#पूर्ण_अगर

	अगर (phy->rev >= 19) अणु
		वापस;
	पूर्ण अन्यथा अगर (phy->rev >= 7) अणु
		rf_pwr_offset_table = b43_ntab_get_rf_pwr_offset_table(dev);
		अगर (!rf_pwr_offset_table)
			वापस;
		/* TODO: Enable this once we have gains configured */
		वापस;
	पूर्ण

	क्रम (i = 0; i < 128; i++) अणु
		अगर (phy->rev >= 19) अणु
			/* TODO */
			वापस;
		पूर्ण अन्यथा अगर (phy->rev >= 7) अणु
			pga_gain = (table[i] >> 24) & 0xf;
			pad_gain = (table[i] >> 19) & 0x1f;
			अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
				rfpwr_offset = rf_pwr_offset_table[pad_gain];
			अन्यथा
				rfpwr_offset = rf_pwr_offset_table[pga_gain];
		पूर्ण अन्यथा अणु
			pga_gain = (table[i] >> 24) & 0xF;
			अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
				rfpwr_offset = b43_ntab_papd_pga_gain_delta_ipa_2g[pga_gain];
			अन्यथा
				rfpwr_offset = 0; /* FIXME */
		पूर्ण

		b43_ntab_ग_लिखो(dev, B43_NTAB32(26, 576 + i), rfpwr_offset);
		b43_ntab_ग_लिखो(dev, B43_NTAB32(27, 576 + i), rfpwr_offset);
	पूर्ण
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/PA%20override */
अटल व्योम b43_nphy_pa_override(काष्ठा b43_wldev *dev, bool enable)
अणु
	काष्ठा b43_phy_n *nphy = dev->phy.n;
	क्रमागत nl80211_band band;
	u16 पंचांगp;

	अगर (!enable) अणु
		nphy->rfctrl_पूर्णांकc1_save = b43_phy_पढ़ो(dev,
						       B43_NPHY_RFCTL_INTC1);
		nphy->rfctrl_पूर्णांकc2_save = b43_phy_पढ़ो(dev,
						       B43_NPHY_RFCTL_INTC2);
		band = b43_current_band(dev->wl);
		अगर (dev->phy.rev >= 7) अणु
			पंचांगp = 0x1480;
		पूर्ण अन्यथा अगर (dev->phy.rev >= 3) अणु
			अगर (band == NL80211_BAND_5GHZ)
				पंचांगp = 0x600;
			अन्यथा
				पंचांगp = 0x480;
		पूर्ण अन्यथा अणु
			अगर (band == NL80211_BAND_5GHZ)
				पंचांगp = 0x180;
			अन्यथा
				पंचांगp = 0x120;
		पूर्ण
		b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_INTC1, पंचांगp);
		b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_INTC2, पंचांगp);
	पूर्ण अन्यथा अणु
		b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_INTC1,
				nphy->rfctrl_पूर्णांकc1_save);
		b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_INTC2,
				nphy->rfctrl_पूर्णांकc2_save);
	पूर्ण
पूर्ण

/*
 * TX low-pass filter bandwidth setup
 * https://bcm-v4.sipsolutions.net/802.11/PHY/N/TxLpFbw
 */
अटल व्योम b43_nphy_tx_lpf_bw(काष्ठा b43_wldev *dev)
अणु
	u16 पंचांगp;

	अगर (dev->phy.rev < 3 || dev->phy.rev >= 7)
		वापस;

	अगर (b43_nphy_ipa(dev))
		पंचांगp = b43_is_40mhz(dev) ? 5 : 4;
	अन्यथा
		पंचांगp = b43_is_40mhz(dev) ? 3 : 1;
	b43_phy_ग_लिखो(dev, B43_NPHY_TXF_40CO_B32S2,
		      (पंचांगp << 9) | (पंचांगp << 6) | (पंचांगp << 3) | पंचांगp);

	अगर (b43_nphy_ipa(dev)) अणु
		पंचांगp = b43_is_40mhz(dev) ? 4 : 1;
		b43_phy_ग_लिखो(dev, B43_NPHY_TXF_40CO_B1S2,
			      (पंचांगp << 9) | (पंचांगp << 6) | (पंचांगp << 3) | पंचांगp);
	पूर्ण
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/RxIqEst */
अटल व्योम b43_nphy_rx_iq_est(काष्ठा b43_wldev *dev, काष्ठा nphy_iq_est *est,
				u16 samps, u8 समय, bool रुको)
अणु
	पूर्णांक i;
	u16 पंचांगp;

	b43_phy_ग_लिखो(dev, B43_NPHY_IQEST_SAMCNT, samps);
	b43_phy_maskset(dev, B43_NPHY_IQEST_WT, ~B43_NPHY_IQEST_WT_VAL, समय);
	अगर (रुको)
		b43_phy_set(dev, B43_NPHY_IQEST_CMD, B43_NPHY_IQEST_CMD_MODE);
	अन्यथा
		b43_phy_mask(dev, B43_NPHY_IQEST_CMD, ~B43_NPHY_IQEST_CMD_MODE);

	b43_phy_set(dev, B43_NPHY_IQEST_CMD, B43_NPHY_IQEST_CMD_START);

	क्रम (i = 1000; i; i--) अणु
		पंचांगp = b43_phy_पढ़ो(dev, B43_NPHY_IQEST_CMD);
		अगर (!(पंचांगp & B43_NPHY_IQEST_CMD_START)) अणु
			est->i0_pwr = (b43_phy_पढ़ो(dev, B43_NPHY_IQEST_IPACC_HI0) << 16) |
					b43_phy_पढ़ो(dev, B43_NPHY_IQEST_IPACC_LO0);
			est->q0_pwr = (b43_phy_पढ़ो(dev, B43_NPHY_IQEST_QPACC_HI0) << 16) |
					b43_phy_पढ़ो(dev, B43_NPHY_IQEST_QPACC_LO0);
			est->iq0_prod = (b43_phy_पढ़ो(dev, B43_NPHY_IQEST_IQACC_HI0) << 16) |
					b43_phy_पढ़ो(dev, B43_NPHY_IQEST_IQACC_LO0);

			est->i1_pwr = (b43_phy_पढ़ो(dev, B43_NPHY_IQEST_IPACC_HI1) << 16) |
					b43_phy_पढ़ो(dev, B43_NPHY_IQEST_IPACC_LO1);
			est->q1_pwr = (b43_phy_पढ़ो(dev, B43_NPHY_IQEST_QPACC_HI1) << 16) |
					b43_phy_पढ़ो(dev, B43_NPHY_IQEST_QPACC_LO1);
			est->iq1_prod = (b43_phy_पढ़ो(dev, B43_NPHY_IQEST_IQACC_HI1) << 16) |
					b43_phy_पढ़ो(dev, B43_NPHY_IQEST_IQACC_LO1);
			वापस;
		पूर्ण
		udelay(10);
	पूर्ण
	स_रखो(est, 0, माप(*est));
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/RxIqCoeffs */
अटल व्योम b43_nphy_rx_iq_coeffs(काष्ठा b43_wldev *dev, bool ग_लिखो,
					काष्ठा b43_phy_n_iq_comp *pcomp)
अणु
	अगर (ग_लिखो) अणु
		b43_phy_ग_लिखो(dev, B43_NPHY_C1_RXIQ_COMPA0, pcomp->a0);
		b43_phy_ग_लिखो(dev, B43_NPHY_C1_RXIQ_COMPB0, pcomp->b0);
		b43_phy_ग_लिखो(dev, B43_NPHY_C2_RXIQ_COMPA1, pcomp->a1);
		b43_phy_ग_लिखो(dev, B43_NPHY_C2_RXIQ_COMPB1, pcomp->b1);
	पूर्ण अन्यथा अणु
		pcomp->a0 = b43_phy_पढ़ो(dev, B43_NPHY_C1_RXIQ_COMPA0);
		pcomp->b0 = b43_phy_पढ़ो(dev, B43_NPHY_C1_RXIQ_COMPB0);
		pcomp->a1 = b43_phy_पढ़ो(dev, B43_NPHY_C2_RXIQ_COMPA1);
		pcomp->b1 = b43_phy_पढ़ो(dev, B43_NPHY_C2_RXIQ_COMPB1);
	पूर्ण
पूर्ण

#अगर 0
/* Ready but not used anywhere */
/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/RxCalPhyCleanup */
अटल व्योम b43_nphy_rx_cal_phy_cleanup(काष्ठा b43_wldev *dev, u8 core)
अणु
	u16 *regs = dev->phy.n->tx_rx_cal_phy_saveregs;

	b43_phy_ग_लिखो(dev, B43_NPHY_RFSEQCA, regs[0]);
	अगर (core == 0) अणु
		b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_C1, regs[1]);
		b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_OVER1, regs[2]);
	पूर्ण अन्यथा अणु
		b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_C2, regs[1]);
		b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_OVER, regs[2]);
	पूर्ण
	b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_INTC1, regs[3]);
	b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_INTC2, regs[4]);
	b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_RSSIO1, regs[5]);
	b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_RSSIO2, regs[6]);
	b43_phy_ग_लिखो(dev, B43_NPHY_TXF_40CO_B1S1, regs[7]);
	b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_OVER, regs[8]);
	b43_phy_ग_लिखो(dev, B43_NPHY_PAPD_EN0, regs[9]);
	b43_phy_ग_लिखो(dev, B43_NPHY_PAPD_EN1, regs[10]);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/RxCalPhySetup */
अटल व्योम b43_nphy_rx_cal_phy_setup(काष्ठा b43_wldev *dev, u8 core)
अणु
	u8 rxval, txval;
	u16 *regs = dev->phy.n->tx_rx_cal_phy_saveregs;

	regs[0] = b43_phy_पढ़ो(dev, B43_NPHY_RFSEQCA);
	अगर (core == 0) अणु
		regs[1] = b43_phy_पढ़ो(dev, B43_NPHY_AFECTL_C1);
		regs[2] = b43_phy_पढ़ो(dev, B43_NPHY_AFECTL_OVER1);
	पूर्ण अन्यथा अणु
		regs[1] = b43_phy_पढ़ो(dev, B43_NPHY_AFECTL_C2);
		regs[2] = b43_phy_पढ़ो(dev, B43_NPHY_AFECTL_OVER);
	पूर्ण
	regs[3] = b43_phy_पढ़ो(dev, B43_NPHY_RFCTL_INTC1);
	regs[4] = b43_phy_पढ़ो(dev, B43_NPHY_RFCTL_INTC2);
	regs[5] = b43_phy_पढ़ो(dev, B43_NPHY_RFCTL_RSSIO1);
	regs[6] = b43_phy_पढ़ो(dev, B43_NPHY_RFCTL_RSSIO2);
	regs[7] = b43_phy_पढ़ो(dev, B43_NPHY_TXF_40CO_B1S1);
	regs[8] = b43_phy_पढ़ो(dev, B43_NPHY_RFCTL_OVER);
	regs[9] = b43_phy_पढ़ो(dev, B43_NPHY_PAPD_EN0);
	regs[10] = b43_phy_पढ़ो(dev, B43_NPHY_PAPD_EN1);

	b43_phy_mask(dev, B43_NPHY_PAPD_EN0, ~0x0001);
	b43_phy_mask(dev, B43_NPHY_PAPD_EN1, ~0x0001);

	b43_phy_maskset(dev, B43_NPHY_RFSEQCA,
			~B43_NPHY_RFSEQCA_RXDIS & 0xFFFF,
			((1 - core) << B43_NPHY_RFSEQCA_RXDIS_SHIFT));
	b43_phy_maskset(dev, B43_NPHY_RFSEQCA, ~B43_NPHY_RFSEQCA_TXEN,
			((1 - core) << B43_NPHY_RFSEQCA_TXEN_SHIFT));
	b43_phy_maskset(dev, B43_NPHY_RFSEQCA, ~B43_NPHY_RFSEQCA_RXEN,
			(core << B43_NPHY_RFSEQCA_RXEN_SHIFT));
	b43_phy_maskset(dev, B43_NPHY_RFSEQCA, ~B43_NPHY_RFSEQCA_TXDIS,
			(core << B43_NPHY_RFSEQCA_TXDIS_SHIFT));

	अगर (core == 0) अणु
		b43_phy_mask(dev, B43_NPHY_AFECTL_C1, ~0x0007);
		b43_phy_set(dev, B43_NPHY_AFECTL_OVER1, 0x0007);
	पूर्ण अन्यथा अणु
		b43_phy_mask(dev, B43_NPHY_AFECTL_C2, ~0x0007);
		b43_phy_set(dev, B43_NPHY_AFECTL_OVER, 0x0007);
	पूर्ण

	b43_nphy_rf_ctl_पूर्णांकc_override(dev, N_INTC_OVERRIDE_PA, 0, 3);
	b43_nphy_rf_ctl_override(dev, 8, 0, 3, false);
	b43_nphy_क्रमce_rf_sequence(dev, B43_RFSEQ_RX2TX);

	अगर (core == 0) अणु
		rxval = 1;
		txval = 8;
	पूर्ण अन्यथा अणु
		rxval = 4;
		txval = 2;
	पूर्ण
	b43_nphy_rf_ctl_पूर्णांकc_override(dev, N_INTC_OVERRIDE_TRSW, rxval,
				      core + 1);
	b43_nphy_rf_ctl_पूर्णांकc_override(dev, N_INTC_OVERRIDE_TRSW, txval,
				      2 - core);
पूर्ण
#पूर्ण_अगर

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/CalcRxIqComp */
अटल व्योम b43_nphy_calc_rx_iq_comp(काष्ठा b43_wldev *dev, u8 mask)
अणु
	पूर्णांक i;
	s32 iq;
	u32 ii;
	u32 qq;
	पूर्णांक iq_nbits, qq_nbits;
	पूर्णांक arsh, brsh;
	u16 पंचांगp, a, b;

	काष्ठा nphy_iq_est est;
	काष्ठा b43_phy_n_iq_comp old;
	काष्ठा b43_phy_n_iq_comp new = अणु पूर्ण;
	bool error = false;

	अगर (mask == 0)
		वापस;

	b43_nphy_rx_iq_coeffs(dev, false, &old);
	b43_nphy_rx_iq_coeffs(dev, true, &new);
	b43_nphy_rx_iq_est(dev, &est, 0x4000, 32, false);
	new = old;

	क्रम (i = 0; i < 2; i++) अणु
		अगर (i == 0 && (mask & 1)) अणु
			iq = est.iq0_prod;
			ii = est.i0_pwr;
			qq = est.q0_pwr;
		पूर्ण अन्यथा अगर (i == 1 && (mask & 2)) अणु
			iq = est.iq1_prod;
			ii = est.i1_pwr;
			qq = est.q1_pwr;
		पूर्ण अन्यथा अणु
			जारी;
		पूर्ण

		अगर (ii + qq < 2) अणु
			error = true;
			अवरोध;
		पूर्ण

		iq_nbits = fls(असल(iq));
		qq_nbits = fls(qq);

		arsh = iq_nbits - 20;
		अगर (arsh >= 0) अणु
			a = -((iq << (30 - iq_nbits)) + (ii >> (1 + arsh)));
			पंचांगp = ii >> arsh;
		पूर्ण अन्यथा अणु
			a = -((iq << (30 - iq_nbits)) + (ii << (-1 - arsh)));
			पंचांगp = ii << -arsh;
		पूर्ण
		अगर (पंचांगp == 0) अणु
			error = true;
			अवरोध;
		पूर्ण
		a /= पंचांगp;

		brsh = qq_nbits - 11;
		अगर (brsh >= 0) अणु
			b = (qq << (31 - qq_nbits));
			पंचांगp = ii >> brsh;
		पूर्ण अन्यथा अणु
			b = (qq << (31 - qq_nbits));
			पंचांगp = ii << -brsh;
		पूर्ण
		अगर (पंचांगp == 0) अणु
			error = true;
			अवरोध;
		पूर्ण
		b = पूर्णांक_वर्ग_मूल(b / पंचांगp - a * a) - (1 << 10);

		अगर (i == 0 && (mask & 0x1)) अणु
			अगर (dev->phy.rev >= 3) अणु
				new.a0 = a & 0x3FF;
				new.b0 = b & 0x3FF;
			पूर्ण अन्यथा अणु
				new.a0 = b & 0x3FF;
				new.b0 = a & 0x3FF;
			पूर्ण
		पूर्ण अन्यथा अगर (i == 1 && (mask & 0x2)) अणु
			अगर (dev->phy.rev >= 3) अणु
				new.a1 = a & 0x3FF;
				new.b1 = b & 0x3FF;
			पूर्ण अन्यथा अणु
				new.a1 = b & 0x3FF;
				new.b1 = a & 0x3FF;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (error)
		new = old;

	b43_nphy_rx_iq_coeffs(dev, true, &new);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/TxIqWar */
अटल व्योम b43_nphy_tx_iq_workaround(काष्ठा b43_wldev *dev)
अणु
	u16 array[4];
	b43_ntab_पढ़ो_bulk(dev, B43_NTAB16(0xF, 0x50), 4, array);

	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_NPHY_TXIQW0, array[0]);
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_NPHY_TXIQW1, array[1]);
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_NPHY_TXIQW2, array[2]);
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_NPHY_TXIQW3, array[3]);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/SpurWar */
अटल व्योम b43_nphy_spur_workaround(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_n *nphy = dev->phy.n;

	u8 channel = dev->phy.channel;
	पूर्णांक tone[2] = अणु 57, 58 पूर्ण;
	u32 noise[2] = अणु 0x3FF, 0x3FF पूर्ण;

	B43_WARN_ON(dev->phy.rev < 3);

	अगर (nphy->hang_aव्योम)
		b43_nphy_stay_in_carrier_search(dev, 1);

	अगर (nphy->gband_spurwar_en) अणु
		/* TODO: N PHY Adjust Analog Pfbw (7) */
		अगर (channel == 11 && b43_is_40mhz(dev)) अणु
			; /* TODO: N PHY Adjust Min Noise Var(2, tone, noise)*/
		पूर्ण अन्यथा अणु
			; /* TODO: N PHY Adjust Min Noise Var(0, शून्य, शून्य)*/
		पूर्ण
		/* TODO: N PHY Adjust CRS Min Power (0x1E) */
	पूर्ण

	अगर (nphy->aband_spurwar_en) अणु
		अगर (channel == 54) अणु
			tone[0] = 0x20;
			noise[0] = 0x25F;
		पूर्ण अन्यथा अगर (channel == 38 || channel == 102 || channel == 118) अणु
			अगर (0 /* FIXME */) अणु
				tone[0] = 0x20;
				noise[0] = 0x21F;
			पूर्ण अन्यथा अणु
				tone[0] = 0;
				noise[0] = 0;
			पूर्ण
		पूर्ण अन्यथा अगर (channel == 134) अणु
			tone[0] = 0x20;
			noise[0] = 0x21F;
		पूर्ण अन्यथा अगर (channel == 151) अणु
			tone[0] = 0x10;
			noise[0] = 0x23F;
		पूर्ण अन्यथा अगर (channel == 153 || channel == 161) अणु
			tone[0] = 0x30;
			noise[0] = 0x23F;
		पूर्ण अन्यथा अणु
			tone[0] = 0;
			noise[0] = 0;
		पूर्ण

		अगर (!tone[0] && !noise[0]) अणु
			; /* TODO: N PHY Adjust Min Noise Var(1, tone, noise)*/
		पूर्ण अन्यथा अणु
			; /* TODO: N PHY Adjust Min Noise Var(0, शून्य, शून्य)*/
		पूर्ण
	पूर्ण

	अगर (nphy->hang_aव्योम)
		b43_nphy_stay_in_carrier_search(dev, 0);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/TxPwrCtrlCoefSetup */
अटल व्योम b43_nphy_tx_pwr_ctrl_coef_setup(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_n *nphy = dev->phy.n;
	पूर्णांक i, j;
	u32 पंचांगp;
	u32 cur_real, cur_imag, real_part, imag_part;

	u16 buffer[7];

	अगर (nphy->hang_aव्योम)
		b43_nphy_stay_in_carrier_search(dev, true);

	b43_ntab_पढ़ो_bulk(dev, B43_NTAB16(15, 80), 7, buffer);

	क्रम (i = 0; i < 2; i++) अणु
		पंचांगp = ((buffer[i * 2] & 0x3FF) << 10) |
			(buffer[i * 2 + 1] & 0x3FF);
		b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_ADDR,
				(((i + 26) << 10) | 320));
		क्रम (j = 0; j < 128; j++) अणु
			b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_DATAHI,
					((पंचांगp >> 16) & 0xFFFF));
			b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_DATALO,
					(पंचांगp & 0xFFFF));
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		पंचांगp = buffer[5 + i];
		real_part = (पंचांगp >> 8) & 0xFF;
		imag_part = (पंचांगp & 0xFF);
		b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_ADDR,
				(((i + 26) << 10) | 448));

		अगर (dev->phy.rev >= 3) अणु
			cur_real = real_part;
			cur_imag = imag_part;
			पंचांगp = ((cur_real & 0xFF) << 8) | (cur_imag & 0xFF);
		पूर्ण

		क्रम (j = 0; j < 128; j++) अणु
			अगर (dev->phy.rev < 3) अणु
				cur_real = (real_part * loscale[j] + 128) >> 8;
				cur_imag = (imag_part * loscale[j] + 128) >> 8;
				पंचांगp = ((cur_real & 0xFF) << 8) |
					(cur_imag & 0xFF);
			पूर्ण
			b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_DATAHI,
					((पंचांगp >> 16) & 0xFFFF));
			b43_phy_ग_लिखो(dev, B43_NPHY_TABLE_DATALO,
					(पंचांगp & 0xFFFF));
		पूर्ण
	पूर्ण

	अगर (dev->phy.rev >= 3) अणु
		b43_shm_ग_लिखो16(dev, B43_SHM_SHARED,
				B43_SHM_SH_NPHY_TXPWR_INDX0, 0xFFFF);
		b43_shm_ग_लिखो16(dev, B43_SHM_SHARED,
				B43_SHM_SH_NPHY_TXPWR_INDX1, 0xFFFF);
	पूर्ण

	अगर (nphy->hang_aव्योम)
		b43_nphy_stay_in_carrier_search(dev, false);
पूर्ण

/*
 * Restore RSSI Calibration
 * https://bcm-v4.sipsolutions.net/802.11/PHY/N/RestoreRssiCal
 */
अटल व्योम b43_nphy_restore_rssi_cal(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_n *nphy = dev->phy.n;

	u16 *rssical_radio_regs = शून्य;
	u16 *rssical_phy_regs = शून्य;

	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
		अगर (!nphy->rssical_chanspec_2G.center_freq)
			वापस;
		rssical_radio_regs = nphy->rssical_cache.rssical_radio_regs_2G;
		rssical_phy_regs = nphy->rssical_cache.rssical_phy_regs_2G;
	पूर्ण अन्यथा अणु
		अगर (!nphy->rssical_chanspec_5G.center_freq)
			वापस;
		rssical_radio_regs = nphy->rssical_cache.rssical_radio_regs_5G;
		rssical_phy_regs = nphy->rssical_cache.rssical_phy_regs_5G;
	पूर्ण

	अगर (dev->phy.rev >= 19) अणु
		/* TODO */
	पूर्ण अन्यथा अगर (dev->phy.rev >= 7) अणु
		b43_radio_maskset(dev, R2057_NB_MASTER_CORE0, ~R2057_VCM_MASK,
				  rssical_radio_regs[0]);
		b43_radio_maskset(dev, R2057_NB_MASTER_CORE1, ~R2057_VCM_MASK,
				  rssical_radio_regs[1]);
	पूर्ण अन्यथा अणु
		b43_radio_maskset(dev, B2056_RX0 | B2056_RX_RSSI_MISC, 0xE3,
				  rssical_radio_regs[0]);
		b43_radio_maskset(dev, B2056_RX1 | B2056_RX_RSSI_MISC, 0xE3,
				  rssical_radio_regs[1]);
	पूर्ण

	b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_0I_RSSI_Z, rssical_phy_regs[0]);
	b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_0Q_RSSI_Z, rssical_phy_regs[1]);
	b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_1I_RSSI_Z, rssical_phy_regs[2]);
	b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_1Q_RSSI_Z, rssical_phy_regs[3]);

	b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_0I_RSSI_X, rssical_phy_regs[4]);
	b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_0Q_RSSI_X, rssical_phy_regs[5]);
	b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_1I_RSSI_X, rssical_phy_regs[6]);
	b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_1Q_RSSI_X, rssical_phy_regs[7]);

	b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_0I_RSSI_Y, rssical_phy_regs[8]);
	b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_0Q_RSSI_Y, rssical_phy_regs[9]);
	b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_1I_RSSI_Y, rssical_phy_regs[10]);
	b43_phy_ग_लिखो(dev, B43_NPHY_RSSIMC_1Q_RSSI_Y, rssical_phy_regs[11]);
पूर्ण

अटल व्योम b43_nphy_tx_cal_radio_setup_rev19(काष्ठा b43_wldev *dev)
अणु
	/* TODO */
पूर्ण

अटल व्योम b43_nphy_tx_cal_radio_setup_rev7(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_n *nphy = dev->phy.n;
	u16 *save = nphy->tx_rx_cal_radio_saveregs;
	पूर्णांक core, off;
	u16 r, पंचांगp;

	क्रम (core = 0; core < 2; core++) अणु
		r = core ? 0x20 : 0;
		off = core * 11;

		save[off + 0] = b43_radio_पढ़ो(dev, r + R2057_TX0_TX_SSI_MASTER);
		save[off + 1] = b43_radio_पढ़ो(dev, r + R2057_TX0_IQCAL_VCM_HG);
		save[off + 2] = b43_radio_पढ़ो(dev, r + R2057_TX0_IQCAL_IDAC);
		save[off + 3] = b43_radio_पढ़ो(dev, r + R2057_TX0_TSSI_VCM);
		save[off + 4] = 0;
		save[off + 5] = b43_radio_पढ़ो(dev, r + R2057_TX0_TX_SSI_MUX);
		अगर (phy->radio_rev != 5)
			save[off + 6] = b43_radio_पढ़ो(dev, r + R2057_TX0_TSSIA);
		save[off + 7] = b43_radio_पढ़ो(dev, r + R2057_TX0_TSSIG);
		save[off + 8] = b43_radio_पढ़ो(dev, r + R2057_TX0_TSSI_MISC1);

		अगर (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) अणु
			b43_radio_ग_लिखो(dev, r + R2057_TX0_TX_SSI_MASTER, 0xA);
			b43_radio_ग_लिखो(dev, r + R2057_TX0_IQCAL_VCM_HG, 0x43);
			b43_radio_ग_लिखो(dev, r + R2057_TX0_IQCAL_IDAC, 0x55);
			b43_radio_ग_लिखो(dev, r + R2057_TX0_TSSI_VCM, 0);
			b43_radio_ग_लिखो(dev, r + R2057_TX0_TSSIG, 0);
			अगर (nphy->use_पूर्णांक_tx_iq_lo_cal) अणु
				b43_radio_ग_लिखो(dev, r + R2057_TX0_TX_SSI_MUX, 0x4);
				पंचांगp = true ? 0x31 : 0x21; /* TODO */
				b43_radio_ग_लिखो(dev, r + R2057_TX0_TSSIA, पंचांगp);
			पूर्ण
			b43_radio_ग_लिखो(dev, r + R2057_TX0_TSSI_MISC1, 0x00);
		पूर्ण अन्यथा अणु
			b43_radio_ग_लिखो(dev, r + R2057_TX0_TX_SSI_MASTER, 0x6);
			b43_radio_ग_लिखो(dev, r + R2057_TX0_IQCAL_VCM_HG, 0x43);
			b43_radio_ग_लिखो(dev, r + R2057_TX0_IQCAL_IDAC, 0x55);
			b43_radio_ग_लिखो(dev, r + R2057_TX0_TSSI_VCM, 0);

			अगर (phy->radio_rev != 5)
				b43_radio_ग_लिखो(dev, r + R2057_TX0_TSSIA, 0);
			अगर (nphy->use_पूर्णांक_tx_iq_lo_cal) अणु
				b43_radio_ग_लिखो(dev, r + R2057_TX0_TX_SSI_MUX, 0x6);
				पंचांगp = true ? 0x31 : 0x21; /* TODO */
				b43_radio_ग_लिखो(dev, r + R2057_TX0_TSSIG, पंचांगp);
			पूर्ण
			b43_radio_ग_लिखो(dev, r + R2057_TX0_TSSI_MISC1, 0);
		पूर्ण
	पूर्ण
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/TxCalRadioSetup */
अटल व्योम b43_nphy_tx_cal_radio_setup(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_n *nphy = dev->phy.n;
	u16 *save = nphy->tx_rx_cal_radio_saveregs;
	u16 पंचांगp;
	u8 offset, i;

	अगर (phy->rev >= 19) अणु
		b43_nphy_tx_cal_radio_setup_rev19(dev);
	पूर्ण अन्यथा अगर (phy->rev >= 7) अणु
		b43_nphy_tx_cal_radio_setup_rev7(dev);
	पूर्ण अन्यथा अगर (phy->rev >= 3) अणु
	    क्रम (i = 0; i < 2; i++) अणु
		पंचांगp = (i == 0) ? 0x2000 : 0x3000;
		offset = i * 11;

		save[offset + 0] = b43_radio_पढ़ो(dev, B2055_CAL_RVARCTL);
		save[offset + 1] = b43_radio_पढ़ो(dev, B2055_CAL_LPOCTL);
		save[offset + 2] = b43_radio_पढ़ो(dev, B2055_CAL_TS);
		save[offset + 3] = b43_radio_पढ़ो(dev, B2055_CAL_RCCALRTS);
		save[offset + 4] = b43_radio_पढ़ो(dev, B2055_CAL_RCALRTS);
		save[offset + 5] = b43_radio_पढ़ो(dev, B2055_PADDRV);
		save[offset + 6] = b43_radio_पढ़ो(dev, B2055_XOCTL1);
		save[offset + 7] = b43_radio_पढ़ो(dev, B2055_XOCTL2);
		save[offset + 8] = b43_radio_पढ़ो(dev, B2055_XOREGUL);
		save[offset + 9] = b43_radio_पढ़ो(dev, B2055_XOMISC);
		save[offset + 10] = b43_radio_पढ़ो(dev, B2055_PLL_LFC1);

		अगर (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) अणु
			b43_radio_ग_लिखो(dev, पंचांगp | B2055_CAL_RVARCTL, 0x0A);
			b43_radio_ग_लिखो(dev, पंचांगp | B2055_CAL_LPOCTL, 0x40);
			b43_radio_ग_लिखो(dev, पंचांगp | B2055_CAL_TS, 0x55);
			b43_radio_ग_लिखो(dev, पंचांगp | B2055_CAL_RCCALRTS, 0);
			b43_radio_ग_लिखो(dev, पंचांगp | B2055_CAL_RCALRTS, 0);
			अगर (nphy->ipa5g_on) अणु
				b43_radio_ग_लिखो(dev, पंचांगp | B2055_PADDRV, 4);
				b43_radio_ग_लिखो(dev, पंचांगp | B2055_XOCTL1, 1);
			पूर्ण अन्यथा अणु
				b43_radio_ग_लिखो(dev, पंचांगp | B2055_PADDRV, 0);
				b43_radio_ग_लिखो(dev, पंचांगp | B2055_XOCTL1, 0x2F);
			पूर्ण
			b43_radio_ग_लिखो(dev, पंचांगp | B2055_XOCTL2, 0);
		पूर्ण अन्यथा अणु
			b43_radio_ग_लिखो(dev, पंचांगp | B2055_CAL_RVARCTL, 0x06);
			b43_radio_ग_लिखो(dev, पंचांगp | B2055_CAL_LPOCTL, 0x40);
			b43_radio_ग_लिखो(dev, पंचांगp | B2055_CAL_TS, 0x55);
			b43_radio_ग_लिखो(dev, पंचांगp | B2055_CAL_RCCALRTS, 0);
			b43_radio_ग_लिखो(dev, पंचांगp | B2055_CAL_RCALRTS, 0);
			b43_radio_ग_लिखो(dev, पंचांगp | B2055_XOCTL1, 0);
			अगर (nphy->ipa2g_on) अणु
				b43_radio_ग_लिखो(dev, पंचांगp | B2055_PADDRV, 6);
				b43_radio_ग_लिखो(dev, पंचांगp | B2055_XOCTL2,
					(dev->phy.rev < 5) ? 0x11 : 0x01);
			पूर्ण अन्यथा अणु
				b43_radio_ग_लिखो(dev, पंचांगp | B2055_PADDRV, 0);
				b43_radio_ग_लिखो(dev, पंचांगp | B2055_XOCTL2, 0);
			पूर्ण
		पूर्ण
		b43_radio_ग_लिखो(dev, पंचांगp | B2055_XOREGUL, 0);
		b43_radio_ग_लिखो(dev, पंचांगp | B2055_XOMISC, 0);
		b43_radio_ग_लिखो(dev, पंचांगp | B2055_PLL_LFC1, 0);
	    पूर्ण
	पूर्ण अन्यथा अणु
		save[0] = b43_radio_पढ़ो(dev, B2055_C1_TX_RF_IQCAL1);
		b43_radio_ग_लिखो(dev, B2055_C1_TX_RF_IQCAL1, 0x29);

		save[1] = b43_radio_पढ़ो(dev, B2055_C1_TX_RF_IQCAL2);
		b43_radio_ग_लिखो(dev, B2055_C1_TX_RF_IQCAL2, 0x54);

		save[2] = b43_radio_पढ़ो(dev, B2055_C2_TX_RF_IQCAL1);
		b43_radio_ग_लिखो(dev, B2055_C2_TX_RF_IQCAL1, 0x29);

		save[3] = b43_radio_पढ़ो(dev, B2055_C2_TX_RF_IQCAL2);
		b43_radio_ग_लिखो(dev, B2055_C2_TX_RF_IQCAL2, 0x54);

		save[3] = b43_radio_पढ़ो(dev, B2055_C1_PWRDET_RXTX);
		save[4] = b43_radio_पढ़ो(dev, B2055_C2_PWRDET_RXTX);

		अगर (!(b43_phy_पढ़ो(dev, B43_NPHY_BANDCTL) &
		    B43_NPHY_BANDCTL_5GHZ)) अणु
			b43_radio_ग_लिखो(dev, B2055_C1_PWRDET_RXTX, 0x04);
			b43_radio_ग_लिखो(dev, B2055_C2_PWRDET_RXTX, 0x04);
		पूर्ण अन्यथा अणु
			b43_radio_ग_लिखो(dev, B2055_C1_PWRDET_RXTX, 0x20);
			b43_radio_ग_लिखो(dev, B2055_C2_PWRDET_RXTX, 0x20);
		पूर्ण

		अगर (dev->phy.rev < 2) अणु
			b43_radio_set(dev, B2055_C1_TX_BB_MXGM, 0x20);
			b43_radio_set(dev, B2055_C2_TX_BB_MXGM, 0x20);
		पूर्ण अन्यथा अणु
			b43_radio_mask(dev, B2055_C1_TX_BB_MXGM, ~0x20);
			b43_radio_mask(dev, B2055_C2_TX_BB_MXGM, ~0x20);
		पूर्ण
	पूर्ण
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/UpdateTxCalLadder */
अटल व्योम b43_nphy_update_tx_cal_ladder(काष्ठा b43_wldev *dev, u16 core)
अणु
	काष्ठा b43_phy_n *nphy = dev->phy.n;
	पूर्णांक i;
	u16 scale, entry;

	u16 पंचांगp = nphy->txcal_bbmult;
	अगर (core == 0)
		पंचांगp >>= 8;
	पंचांगp &= 0xff;

	क्रम (i = 0; i < 18; i++) अणु
		scale = (ladder_lo[i].percent * पंचांगp) / 100;
		entry = ((scale & 0xFF) << 8) | ladder_lo[i].g_env;
		b43_ntab_ग_लिखो(dev, B43_NTAB16(15, i), entry);

		scale = (ladder_iq[i].percent * पंचांगp) / 100;
		entry = ((scale & 0xFF) << 8) | ladder_iq[i].g_env;
		b43_ntab_ग_लिखो(dev, B43_NTAB16(15, i + 32), entry);
	पूर्ण
पूर्ण

अटल व्योम b43_nphy_pa_set_tx_dig_filter(काष्ठा b43_wldev *dev, u16 offset,
					  स्थिर s16 *filter)
अणु
	पूर्णांक i;

	offset = B43_PHY_N(offset);

	क्रम (i = 0; i < 15; i++, offset++)
		b43_phy_ग_लिखो(dev, offset, filter[i]);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/ExtPaSetTxDigiFilts */
अटल व्योम b43_nphy_ext_pa_set_tx_dig_filters(काष्ठा b43_wldev *dev)
अणु
	b43_nphy_pa_set_tx_dig_filter(dev, 0x2C5,
				      tbl_tx_filter_coef_rev4[2]);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/IpaSetTxDigiFilts */
अटल व्योम b43_nphy_पूर्णांक_pa_set_tx_dig_filters(काष्ठा b43_wldev *dev)
अणु
	/* B43_NPHY_TXF_20CO_S0A1, B43_NPHY_TXF_40CO_S0A1, unknown */
	अटल स्थिर u16 offset[] = अणु 0x186, 0x195, 0x2C5 पूर्ण;
	अटल स्थिर s16 dig_filter_phy_rev16[] = अणु
		-375, 136, -407, 208, -1527,
		956, 93, 186, 93, 230,
		-44, 230, 201, -191, 201,
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++)
		b43_nphy_pa_set_tx_dig_filter(dev, offset[i],
					      tbl_tx_filter_coef_rev4[i]);

	/* Verअगरied with BCM43227 and BCM43228 */
	अगर (dev->phy.rev == 16)
		b43_nphy_pa_set_tx_dig_filter(dev, 0x186, dig_filter_phy_rev16);

	/* Verअगरied with BCM43131 and BCM43217 */
	अगर (dev->phy.rev == 17) अणु
		b43_nphy_pa_set_tx_dig_filter(dev, 0x186, dig_filter_phy_rev16);
		b43_nphy_pa_set_tx_dig_filter(dev, 0x195,
					      tbl_tx_filter_coef_rev4[1]);
	पूर्ण

	अगर (b43_is_40mhz(dev)) अणु
		b43_nphy_pa_set_tx_dig_filter(dev, 0x186,
					      tbl_tx_filter_coef_rev4[3]);
	पूर्ण अन्यथा अणु
		अगर (b43_current_band(dev->wl) == NL80211_BAND_5GHZ)
			b43_nphy_pa_set_tx_dig_filter(dev, 0x186,
						      tbl_tx_filter_coef_rev4[5]);
		अगर (dev->phy.channel == 14)
			b43_nphy_pa_set_tx_dig_filter(dev, 0x186,
						      tbl_tx_filter_coef_rev4[6]);
	पूर्ण
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/GetTxGain */
अटल काष्ठा nphy_txgains b43_nphy_get_tx_gains(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_n *nphy = dev->phy.n;

	u16 curr_gain[2];
	काष्ठा nphy_txgains target;
	स्थिर u32 *table = शून्य;

	अगर (!nphy->txpwrctrl) अणु
		पूर्णांक i;

		अगर (nphy->hang_aव्योम)
			b43_nphy_stay_in_carrier_search(dev, true);
		b43_ntab_पढ़ो_bulk(dev, B43_NTAB16(7, 0x110), 2, curr_gain);
		अगर (nphy->hang_aव्योम)
			b43_nphy_stay_in_carrier_search(dev, false);

		क्रम (i = 0; i < 2; ++i) अणु
			अगर (dev->phy.rev >= 7) अणु
				target.ipa[i] = curr_gain[i] & 0x0007;
				target.pad[i] = (curr_gain[i] & 0x00F8) >> 3;
				target.pga[i] = (curr_gain[i] & 0x0F00) >> 8;
				target.txgm[i] = (curr_gain[i] & 0x7000) >> 12;
				target.tx_lpf[i] = (curr_gain[i] & 0x8000) >> 15;
			पूर्ण अन्यथा अगर (dev->phy.rev >= 3) अणु
				target.ipa[i] = curr_gain[i] & 0x000F;
				target.pad[i] = (curr_gain[i] & 0x00F0) >> 4;
				target.pga[i] = (curr_gain[i] & 0x0F00) >> 8;
				target.txgm[i] = (curr_gain[i] & 0x7000) >> 12;
			पूर्ण अन्यथा अणु
				target.ipa[i] = curr_gain[i] & 0x0003;
				target.pad[i] = (curr_gain[i] & 0x000C) >> 2;
				target.pga[i] = (curr_gain[i] & 0x0070) >> 4;
				target.txgm[i] = (curr_gain[i] & 0x0380) >> 7;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक i;
		u16 index[2];
		index[0] = (b43_phy_पढ़ो(dev, B43_NPHY_C1_TXPCTL_STAT) &
			B43_NPHY_TXPCTL_STAT_BIDX) >>
			B43_NPHY_TXPCTL_STAT_BIDX_SHIFT;
		index[1] = (b43_phy_पढ़ो(dev, B43_NPHY_C2_TXPCTL_STAT) &
			B43_NPHY_TXPCTL_STAT_BIDX) >>
			B43_NPHY_TXPCTL_STAT_BIDX_SHIFT;

		क्रम (i = 0; i < 2; ++i) अणु
			table = b43_nphy_get_tx_gain_table(dev);
			अगर (!table)
				अवरोध;

			अगर (dev->phy.rev >= 7) अणु
				target.ipa[i] = (table[index[i]] >> 16) & 0x7;
				target.pad[i] = (table[index[i]] >> 19) & 0x1F;
				target.pga[i] = (table[index[i]] >> 24) & 0xF;
				target.txgm[i] = (table[index[i]] >> 28) & 0x7;
				target.tx_lpf[i] = (table[index[i]] >> 31) & 0x1;
			पूर्ण अन्यथा अगर (dev->phy.rev >= 3) अणु
				target.ipa[i] = (table[index[i]] >> 16) & 0xF;
				target.pad[i] = (table[index[i]] >> 20) & 0xF;
				target.pga[i] = (table[index[i]] >> 24) & 0xF;
				target.txgm[i] = (table[index[i]] >> 28) & 0xF;
			पूर्ण अन्यथा अणु
				target.ipa[i] = (table[index[i]] >> 16) & 0x3;
				target.pad[i] = (table[index[i]] >> 18) & 0x3;
				target.pga[i] = (table[index[i]] >> 20) & 0x7;
				target.txgm[i] = (table[index[i]] >> 23) & 0x7;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस target;
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/TxCalPhyCleanup */
अटल व्योम b43_nphy_tx_cal_phy_cleanup(काष्ठा b43_wldev *dev)
अणु
	u16 *regs = dev->phy.n->tx_rx_cal_phy_saveregs;

	अगर (dev->phy.rev >= 3) अणु
		b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_C1, regs[0]);
		b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_C2, regs[1]);
		b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_OVER1, regs[2]);
		b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_OVER, regs[3]);
		b43_phy_ग_लिखो(dev, B43_NPHY_BBCFG, regs[4]);
		b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 3), regs[5]);
		b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 19), regs[6]);
		b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_INTC1, regs[7]);
		b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_INTC2, regs[8]);
		b43_phy_ग_लिखो(dev, B43_NPHY_PAPD_EN0, regs[9]);
		b43_phy_ग_लिखो(dev, B43_NPHY_PAPD_EN1, regs[10]);
		b43_nphy_reset_cca(dev);
	पूर्ण अन्यथा अणु
		b43_phy_maskset(dev, B43_NPHY_AFECTL_C1, 0x0FFF, regs[0]);
		b43_phy_maskset(dev, B43_NPHY_AFECTL_C2, 0x0FFF, regs[1]);
		b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_OVER, regs[2]);
		b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 2), regs[3]);
		b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 18), regs[4]);
		b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_INTC1, regs[5]);
		b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_INTC2, regs[6]);
	पूर्ण
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/TxCalPhySetup */
अटल व्योम b43_nphy_tx_cal_phy_setup(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_n *nphy = dev->phy.n;
	u16 *regs = dev->phy.n->tx_rx_cal_phy_saveregs;
	u16 पंचांगp;

	regs[0] = b43_phy_पढ़ो(dev, B43_NPHY_AFECTL_C1);
	regs[1] = b43_phy_पढ़ो(dev, B43_NPHY_AFECTL_C2);
	अगर (dev->phy.rev >= 3) अणु
		b43_phy_maskset(dev, B43_NPHY_AFECTL_C1, 0xF0FF, 0x0A00);
		b43_phy_maskset(dev, B43_NPHY_AFECTL_C2, 0xF0FF, 0x0A00);

		पंचांगp = b43_phy_पढ़ो(dev, B43_NPHY_AFECTL_OVER1);
		regs[2] = पंचांगp;
		b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_OVER1, पंचांगp | 0x0600);

		पंचांगp = b43_phy_पढ़ो(dev, B43_NPHY_AFECTL_OVER);
		regs[3] = पंचांगp;
		b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_OVER, पंचांगp | 0x0600);

		regs[4] = b43_phy_पढ़ो(dev, B43_NPHY_BBCFG);
		b43_phy_mask(dev, B43_NPHY_BBCFG,
			     ~B43_NPHY_BBCFG_RSTRX & 0xFFFF);

		पंचांगp = b43_ntab_पढ़ो(dev, B43_NTAB16(8, 3));
		regs[5] = पंचांगp;
		b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 3), 0);

		पंचांगp = b43_ntab_पढ़ो(dev, B43_NTAB16(8, 19));
		regs[6] = पंचांगp;
		b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 19), 0);
		regs[7] = b43_phy_पढ़ो(dev, B43_NPHY_RFCTL_INTC1);
		regs[8] = b43_phy_पढ़ो(dev, B43_NPHY_RFCTL_INTC2);

		अगर (!nphy->use_पूर्णांक_tx_iq_lo_cal)
			b43_nphy_rf_ctl_पूर्णांकc_override(dev, N_INTC_OVERRIDE_PA,
						      1, 3);
		अन्यथा
			b43_nphy_rf_ctl_पूर्णांकc_override(dev, N_INTC_OVERRIDE_PA,
						      0, 3);
		b43_nphy_rf_ctl_पूर्णांकc_override(dev, N_INTC_OVERRIDE_TRSW, 2, 1);
		b43_nphy_rf_ctl_पूर्णांकc_override(dev, N_INTC_OVERRIDE_TRSW, 8, 2);

		regs[9] = b43_phy_पढ़ो(dev, B43_NPHY_PAPD_EN0);
		regs[10] = b43_phy_पढ़ो(dev, B43_NPHY_PAPD_EN1);
		b43_phy_mask(dev, B43_NPHY_PAPD_EN0, ~0x0001);
		b43_phy_mask(dev, B43_NPHY_PAPD_EN1, ~0x0001);

		पंचांगp = b43_nphy_पढ़ो_lpf_ctl(dev, 0);
		अगर (phy->rev >= 19)
			b43_nphy_rf_ctl_override_rev19(dev, 0x80, पंचांगp, 0, false,
						       1);
		अन्यथा अगर (phy->rev >= 7)
			b43_nphy_rf_ctl_override_rev7(dev, 0x80, पंचांगp, 0, false,
						      1);

		अगर (nphy->use_पूर्णांक_tx_iq_lo_cal && true /* FIXME */) अणु
			अगर (phy->rev >= 19) अणु
				b43_nphy_rf_ctl_override_rev19(dev, 0x8, 0, 0x3,
							       false, 0);
			पूर्ण अन्यथा अगर (phy->rev >= 8) अणु
				b43_nphy_rf_ctl_override_rev7(dev, 0x8, 0, 0x3,
							      false, 0);
			पूर्ण अन्यथा अगर (phy->rev == 7) अणु
				b43_radio_maskset(dev, R2057_OVR_REG0, 1 << 4, 1 << 4);
				अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
					b43_radio_maskset(dev, R2057_PAD2G_TUNE_PUS_CORE0, ~1, 0);
					b43_radio_maskset(dev, R2057_PAD2G_TUNE_PUS_CORE1, ~1, 0);
				पूर्ण अन्यथा अणु
					b43_radio_maskset(dev, R2057_IPA5G_CASCOFFV_PU_CORE0, ~1, 0);
					b43_radio_maskset(dev, R2057_IPA5G_CASCOFFV_PU_CORE1, ~1, 0);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		b43_phy_maskset(dev, B43_NPHY_AFECTL_C1, 0x0FFF, 0xA000);
		b43_phy_maskset(dev, B43_NPHY_AFECTL_C2, 0x0FFF, 0xA000);
		पंचांगp = b43_phy_पढ़ो(dev, B43_NPHY_AFECTL_OVER);
		regs[2] = पंचांगp;
		b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_OVER, पंचांगp | 0x3000);
		पंचांगp = b43_ntab_पढ़ो(dev, B43_NTAB16(8, 2));
		regs[3] = पंचांगp;
		पंचांगp |= 0x2000;
		b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 2), पंचांगp);
		पंचांगp = b43_ntab_पढ़ो(dev, B43_NTAB16(8, 18));
		regs[4] = पंचांगp;
		पंचांगp |= 0x2000;
		b43_ntab_ग_लिखो(dev, B43_NTAB16(8, 18), पंचांगp);
		regs[5] = b43_phy_पढ़ो(dev, B43_NPHY_RFCTL_INTC1);
		regs[6] = b43_phy_पढ़ो(dev, B43_NPHY_RFCTL_INTC2);
		अगर (b43_current_band(dev->wl) == NL80211_BAND_5GHZ)
			पंचांगp = 0x0180;
		अन्यथा
			पंचांगp = 0x0120;
		b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_INTC1, पंचांगp);
		b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_INTC2, पंचांगp);
	पूर्ण
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/SaveCal */
अटल व्योम b43_nphy_save_cal(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_n *nphy = dev->phy.n;

	काष्ठा b43_phy_n_iq_comp *rxcal_coeffs = शून्य;
	u16 *txcal_radio_regs = शून्य;
	काष्ठा b43_chanspec *iqcal_chanspec;
	u16 *table = शून्य;

	अगर (nphy->hang_aव्योम)
		b43_nphy_stay_in_carrier_search(dev, 1);

	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
		rxcal_coeffs = &nphy->cal_cache.rxcal_coeffs_2G;
		txcal_radio_regs = nphy->cal_cache.txcal_radio_regs_2G;
		iqcal_chanspec = &nphy->iqcal_chanspec_2G;
		table = nphy->cal_cache.txcal_coeffs_2G;
	पूर्ण अन्यथा अणु
		rxcal_coeffs = &nphy->cal_cache.rxcal_coeffs_5G;
		txcal_radio_regs = nphy->cal_cache.txcal_radio_regs_5G;
		iqcal_chanspec = &nphy->iqcal_chanspec_5G;
		table = nphy->cal_cache.txcal_coeffs_5G;
	पूर्ण

	b43_nphy_rx_iq_coeffs(dev, false, rxcal_coeffs);
	/* TODO use some definitions */
	अगर (phy->rev >= 19) अणु
		/* TODO */
	पूर्ण अन्यथा अगर (phy->rev >= 7) अणु
		txcal_radio_regs[0] = b43_radio_पढ़ो(dev,
						     R2057_TX0_LOFT_FINE_I);
		txcal_radio_regs[1] = b43_radio_पढ़ो(dev,
						     R2057_TX0_LOFT_FINE_Q);
		txcal_radio_regs[4] = b43_radio_पढ़ो(dev,
						     R2057_TX0_LOFT_COARSE_I);
		txcal_radio_regs[5] = b43_radio_पढ़ो(dev,
						     R2057_TX0_LOFT_COARSE_Q);
		txcal_radio_regs[2] = b43_radio_पढ़ो(dev,
						     R2057_TX1_LOFT_FINE_I);
		txcal_radio_regs[3] = b43_radio_पढ़ो(dev,
						     R2057_TX1_LOFT_FINE_Q);
		txcal_radio_regs[6] = b43_radio_पढ़ो(dev,
						     R2057_TX1_LOFT_COARSE_I);
		txcal_radio_regs[7] = b43_radio_पढ़ो(dev,
						     R2057_TX1_LOFT_COARSE_Q);
	पूर्ण अन्यथा अगर (phy->rev >= 3) अणु
		txcal_radio_regs[0] = b43_radio_पढ़ो(dev, 0x2021);
		txcal_radio_regs[1] = b43_radio_पढ़ो(dev, 0x2022);
		txcal_radio_regs[2] = b43_radio_पढ़ो(dev, 0x3021);
		txcal_radio_regs[3] = b43_radio_पढ़ो(dev, 0x3022);
		txcal_radio_regs[4] = b43_radio_पढ़ो(dev, 0x2023);
		txcal_radio_regs[5] = b43_radio_पढ़ो(dev, 0x2024);
		txcal_radio_regs[6] = b43_radio_पढ़ो(dev, 0x3023);
		txcal_radio_regs[7] = b43_radio_पढ़ो(dev, 0x3024);
	पूर्ण अन्यथा अणु
		txcal_radio_regs[0] = b43_radio_पढ़ो(dev, 0x8B);
		txcal_radio_regs[1] = b43_radio_पढ़ो(dev, 0xBA);
		txcal_radio_regs[2] = b43_radio_पढ़ो(dev, 0x8D);
		txcal_radio_regs[3] = b43_radio_पढ़ो(dev, 0xBC);
	पूर्ण
	iqcal_chanspec->center_freq = dev->phy.chandef->chan->center_freq;
	iqcal_chanspec->channel_type =
				cfg80211_get_chandef_type(dev->phy.chandef);
	b43_ntab_पढ़ो_bulk(dev, B43_NTAB16(15, 80), 8, table);

	अगर (nphy->hang_aव्योम)
		b43_nphy_stay_in_carrier_search(dev, 0);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/RestoreCal */
अटल व्योम b43_nphy_restore_cal(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_n *nphy = dev->phy.n;

	u16 coef[4];
	u16 *loft = शून्य;
	u16 *table = शून्य;

	पूर्णांक i;
	u16 *txcal_radio_regs = शून्य;
	काष्ठा b43_phy_n_iq_comp *rxcal_coeffs = शून्य;

	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
		अगर (!nphy->iqcal_chanspec_2G.center_freq)
			वापस;
		table = nphy->cal_cache.txcal_coeffs_2G;
		loft = &nphy->cal_cache.txcal_coeffs_2G[5];
	पूर्ण अन्यथा अणु
		अगर (!nphy->iqcal_chanspec_5G.center_freq)
			वापस;
		table = nphy->cal_cache.txcal_coeffs_5G;
		loft = &nphy->cal_cache.txcal_coeffs_5G[5];
	पूर्ण

	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(15, 80), 4, table);

	क्रम (i = 0; i < 4; i++) अणु
		अगर (dev->phy.rev >= 3)
			coef[i] = table[i];
		अन्यथा
			coef[i] = 0;
	पूर्ण

	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(15, 88), 4, coef);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(15, 85), 2, loft);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(15, 93), 2, loft);

	अगर (dev->phy.rev < 2)
		b43_nphy_tx_iq_workaround(dev);

	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
		txcal_radio_regs = nphy->cal_cache.txcal_radio_regs_2G;
		rxcal_coeffs = &nphy->cal_cache.rxcal_coeffs_2G;
	पूर्ण अन्यथा अणु
		txcal_radio_regs = nphy->cal_cache.txcal_radio_regs_5G;
		rxcal_coeffs = &nphy->cal_cache.rxcal_coeffs_5G;
	पूर्ण

	/* TODO use some definitions */
	अगर (phy->rev >= 19) अणु
		/* TODO */
	पूर्ण अन्यथा अगर (phy->rev >= 7) अणु
		b43_radio_ग_लिखो(dev, R2057_TX0_LOFT_FINE_I,
				txcal_radio_regs[0]);
		b43_radio_ग_लिखो(dev, R2057_TX0_LOFT_FINE_Q,
				txcal_radio_regs[1]);
		b43_radio_ग_लिखो(dev, R2057_TX0_LOFT_COARSE_I,
				txcal_radio_regs[4]);
		b43_radio_ग_लिखो(dev, R2057_TX0_LOFT_COARSE_Q,
				txcal_radio_regs[5]);
		b43_radio_ग_लिखो(dev, R2057_TX1_LOFT_FINE_I,
				txcal_radio_regs[2]);
		b43_radio_ग_लिखो(dev, R2057_TX1_LOFT_FINE_Q,
				txcal_radio_regs[3]);
		b43_radio_ग_लिखो(dev, R2057_TX1_LOFT_COARSE_I,
				txcal_radio_regs[6]);
		b43_radio_ग_लिखो(dev, R2057_TX1_LOFT_COARSE_Q,
				txcal_radio_regs[7]);
	पूर्ण अन्यथा अगर (phy->rev >= 3) अणु
		b43_radio_ग_लिखो(dev, 0x2021, txcal_radio_regs[0]);
		b43_radio_ग_लिखो(dev, 0x2022, txcal_radio_regs[1]);
		b43_radio_ग_लिखो(dev, 0x3021, txcal_radio_regs[2]);
		b43_radio_ग_लिखो(dev, 0x3022, txcal_radio_regs[3]);
		b43_radio_ग_लिखो(dev, 0x2023, txcal_radio_regs[4]);
		b43_radio_ग_लिखो(dev, 0x2024, txcal_radio_regs[5]);
		b43_radio_ग_लिखो(dev, 0x3023, txcal_radio_regs[6]);
		b43_radio_ग_लिखो(dev, 0x3024, txcal_radio_regs[7]);
	पूर्ण अन्यथा अणु
		b43_radio_ग_लिखो(dev, 0x8B, txcal_radio_regs[0]);
		b43_radio_ग_लिखो(dev, 0xBA, txcal_radio_regs[1]);
		b43_radio_ग_लिखो(dev, 0x8D, txcal_radio_regs[2]);
		b43_radio_ग_लिखो(dev, 0xBC, txcal_radio_regs[3]);
	पूर्ण
	b43_nphy_rx_iq_coeffs(dev, true, rxcal_coeffs);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/CalTxIqlo */
अटल पूर्णांक b43_nphy_cal_tx_iq_lo(काष्ठा b43_wldev *dev,
				काष्ठा nphy_txgains target,
				bool full, bool mphase)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_n *nphy = dev->phy.n;
	पूर्णांक i;
	पूर्णांक error = 0;
	पूर्णांक freq;
	bool aव्योम = false;
	u8 length;
	u16 पंचांगp, core, type, count, max, numb, last = 0, cmd;
	स्थिर u16 *table;
	bool phy6or5x;

	u16 buffer[11];
	u16 diq_start = 0;
	u16 save[2];
	u16 gain[2];
	काष्ठा nphy_iqcal_params params[2];
	bool updated[2] = अणु पूर्ण;

	b43_nphy_stay_in_carrier_search(dev, true);

	अगर (dev->phy.rev >= 4) अणु
		aव्योम = nphy->hang_aव्योम;
		nphy->hang_aव्योम = false;
	पूर्ण

	b43_ntab_पढ़ो_bulk(dev, B43_NTAB16(7, 0x110), 2, save);

	क्रम (i = 0; i < 2; i++) अणु
		b43_nphy_iq_cal_gain_params(dev, i, target, &params[i]);
		gain[i] = params[i].cal_gain;
	पूर्ण

	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(7, 0x110), 2, gain);

	b43_nphy_tx_cal_radio_setup(dev);
	b43_nphy_tx_cal_phy_setup(dev);

	phy6or5x = dev->phy.rev >= 6 ||
		(dev->phy.rev == 5 && nphy->ipa2g_on &&
		b43_current_band(dev->wl) == NL80211_BAND_2GHZ);
	अगर (phy6or5x) अणु
		अगर (b43_is_40mhz(dev)) अणु
			b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(15, 0), 18,
					tbl_tx_iqlo_cal_loft_ladder_40);
			b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(15, 32), 18,
					tbl_tx_iqlo_cal_iqimb_ladder_40);
		पूर्ण अन्यथा अणु
			b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(15, 0), 18,
					tbl_tx_iqlo_cal_loft_ladder_20);
			b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(15, 32), 18,
					tbl_tx_iqlo_cal_iqimb_ladder_20);
		पूर्ण
	पूर्ण

	अगर (phy->rev >= 19) अणु
		/* TODO */
	पूर्ण अन्यथा अगर (phy->rev >= 7) अणु
		b43_phy_ग_लिखो(dev, B43_NPHY_IQLOCAL_CMDGCTL, 0x8AD9);
	पूर्ण अन्यथा अणु
		b43_phy_ग_लिखो(dev, B43_NPHY_IQLOCAL_CMDGCTL, 0x8AA9);
	पूर्ण

	अगर (!b43_is_40mhz(dev))
		freq = 2500;
	अन्यथा
		freq = 5000;

	अगर (nphy->mphase_cal_phase_id > 2)
		b43_nphy_run_samples(dev, (b43_is_40mhz(dev) ? 40 : 20) * 8,
				     0xFFFF, 0, true, false, false);
	अन्यथा
		error = b43_nphy_tx_tone(dev, freq, 250, true, false, false);

	अगर (error == 0) अणु
		अगर (nphy->mphase_cal_phase_id > 2) अणु
			table = nphy->mphase_txcal_bestcoeffs;
			length = 11;
			अगर (dev->phy.rev < 3)
				length -= 2;
		पूर्ण अन्यथा अणु
			अगर (!full && nphy->txiqlocal_coeffsvalid) अणु
				table = nphy->txiqlocal_bestc;
				length = 11;
				अगर (dev->phy.rev < 3)
					length -= 2;
			पूर्ण अन्यथा अणु
				full = true;
				अगर (dev->phy.rev >= 3) अणु
					table = tbl_tx_iqlo_cal_startcoefs_nphyrev3;
					length = B43_NTAB_TX_IQLO_CAL_STARTCOEFS_REV3;
				पूर्ण अन्यथा अणु
					table = tbl_tx_iqlo_cal_startcoefs;
					length = B43_NTAB_TX_IQLO_CAL_STARTCOEFS;
				पूर्ण
			पूर्ण
		पूर्ण

		b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(15, 64), length, table);

		अगर (full) अणु
			अगर (dev->phy.rev >= 3)
				max = B43_NTAB_TX_IQLO_CAL_CMDS_FULLCAL_REV3;
			अन्यथा
				max = B43_NTAB_TX_IQLO_CAL_CMDS_FULLCAL;
		पूर्ण अन्यथा अणु
			अगर (dev->phy.rev >= 3)
				max = B43_NTAB_TX_IQLO_CAL_CMDS_RECAL_REV3;
			अन्यथा
				max = B43_NTAB_TX_IQLO_CAL_CMDS_RECAL;
		पूर्ण

		अगर (mphase) अणु
			count = nphy->mphase_txcal_cmdidx;
			numb = min(max,
				(u16)(count + nphy->mphase_txcal_numcmds));
		पूर्ण अन्यथा अणु
			count = 0;
			numb = max;
		पूर्ण

		क्रम (; count < numb; count++) अणु
			अगर (full) अणु
				अगर (dev->phy.rev >= 3)
					cmd = tbl_tx_iqlo_cal_cmds_fullcal_nphyrev3[count];
				अन्यथा
					cmd = tbl_tx_iqlo_cal_cmds_fullcal[count];
			पूर्ण अन्यथा अणु
				अगर (dev->phy.rev >= 3)
					cmd = tbl_tx_iqlo_cal_cmds_recal_nphyrev3[count];
				अन्यथा
					cmd = tbl_tx_iqlo_cal_cmds_recal[count];
			पूर्ण

			core = (cmd & 0x3000) >> 12;
			type = (cmd & 0x0F00) >> 8;

			अगर (phy6or5x && !updated[core]) अणु
				b43_nphy_update_tx_cal_ladder(dev, core);
				updated[core] = true;
			पूर्ण

			पंचांगp = (params[core].ncorr[type] << 8) | 0x66;
			b43_phy_ग_लिखो(dev, B43_NPHY_IQLOCAL_CMDNNUM, पंचांगp);

			अगर (type == 1 || type == 3 || type == 4) अणु
				buffer[0] = b43_ntab_पढ़ो(dev,
						B43_NTAB16(15, 69 + core));
				diq_start = buffer[0];
				buffer[0] = 0;
				b43_ntab_ग_लिखो(dev, B43_NTAB16(15, 69 + core),
						0);
			पूर्ण

			b43_phy_ग_लिखो(dev, B43_NPHY_IQLOCAL_CMD, cmd);
			क्रम (i = 0; i < 2000; i++) अणु
				पंचांगp = b43_phy_पढ़ो(dev, B43_NPHY_IQLOCAL_CMD);
				अगर (पंचांगp & 0xC000)
					अवरोध;
				udelay(10);
			पूर्ण

			b43_ntab_पढ़ो_bulk(dev, B43_NTAB16(15, 96), length,
						buffer);
			b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(15, 64), length,
						buffer);

			अगर (type == 1 || type == 3 || type == 4)
				buffer[0] = diq_start;
		पूर्ण

		अगर (mphase)
			nphy->mphase_txcal_cmdidx = (numb >= max) ? 0 : numb;

		last = (dev->phy.rev < 3) ? 6 : 7;

		अगर (!mphase || nphy->mphase_cal_phase_id == last) अणु
			b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(15, 96), 4, buffer);
			b43_ntab_पढ़ो_bulk(dev, B43_NTAB16(15, 80), 4, buffer);
			अगर (dev->phy.rev < 3) अणु
				buffer[0] = 0;
				buffer[1] = 0;
				buffer[2] = 0;
				buffer[3] = 0;
			पूर्ण
			b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(15, 88), 4,
						buffer);
			b43_ntab_पढ़ो_bulk(dev, B43_NTAB16(15, 101), 2,
						buffer);
			b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(15, 85), 2,
						buffer);
			b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(15, 93), 2,
						buffer);
			length = 11;
			अगर (dev->phy.rev < 3)
				length -= 2;
			b43_ntab_पढ़ो_bulk(dev, B43_NTAB16(15, 96), length,
						nphy->txiqlocal_bestc);
			nphy->txiqlocal_coeffsvalid = true;
			nphy->txiqlocal_chanspec.center_freq =
						phy->chandef->chan->center_freq;
			nphy->txiqlocal_chanspec.channel_type =
					cfg80211_get_chandef_type(phy->chandef);
		पूर्ण अन्यथा अणु
			length = 11;
			अगर (dev->phy.rev < 3)
				length -= 2;
			b43_ntab_पढ़ो_bulk(dev, B43_NTAB16(15, 96), length,
						nphy->mphase_txcal_bestcoeffs);
		पूर्ण

		b43_nphy_stop_playback(dev);
		b43_phy_ग_लिखो(dev, B43_NPHY_IQLOCAL_CMDGCTL, 0);
	पूर्ण

	b43_nphy_tx_cal_phy_cleanup(dev);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(7, 0x110), 2, save);

	अगर (dev->phy.rev < 2 && (!mphase || nphy->mphase_cal_phase_id == last))
		b43_nphy_tx_iq_workaround(dev);

	अगर (dev->phy.rev >= 4)
		nphy->hang_aव्योम = aव्योम;

	b43_nphy_stay_in_carrier_search(dev, false);

	वापस error;
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/ReapplyTxCalCoeffs */
अटल व्योम b43_nphy_reapply_tx_cal_coeffs(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_n *nphy = dev->phy.n;
	u8 i;
	u16 buffer[7];
	bool equal = true;

	अगर (!nphy->txiqlocal_coeffsvalid ||
	    nphy->txiqlocal_chanspec.center_freq != dev->phy.chandef->chan->center_freq ||
	    nphy->txiqlocal_chanspec.channel_type != cfg80211_get_chandef_type(dev->phy.chandef))
		वापस;

	b43_ntab_पढ़ो_bulk(dev, B43_NTAB16(15, 80), 7, buffer);
	क्रम (i = 0; i < 4; i++) अणु
		अगर (buffer[i] != nphy->txiqlocal_bestc[i]) अणु
			equal = false;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!equal) अणु
		b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(15, 80), 4,
					nphy->txiqlocal_bestc);
		क्रम (i = 0; i < 4; i++)
			buffer[i] = 0;
		b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(15, 88), 4,
					buffer);
		b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(15, 85), 2,
					&nphy->txiqlocal_bestc[5]);
		b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(15, 93), 2,
					&nphy->txiqlocal_bestc[5]);
	पूर्ण
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/CalRxIqRev2 */
अटल पूर्णांक b43_nphy_rev2_cal_rx_iq(काष्ठा b43_wldev *dev,
			काष्ठा nphy_txgains target, u8 type, bool debug)
अणु
	काष्ठा b43_phy_n *nphy = dev->phy.n;
	पूर्णांक i, j, index;
	u8 rfctl[2];
	u8 afectl_core;
	u16 पंचांगp[6];
	u16 cur_hpf1, cur_hpf2, cur_lna;
	u32 real, imag;
	क्रमागत nl80211_band band;

	u8 use;
	u16 cur_hpf;
	u16 lna[3] = अणु 3, 3, 1 पूर्ण;
	u16 hpf1[3] = अणु 7, 2, 0 पूर्ण;
	u16 hpf2[3] = अणु 2, 0, 0 पूर्ण;
	u32 घातer[3] = अणु पूर्ण;
	u16 gain_save[2];
	u16 cal_gain[2];
	काष्ठा nphy_iqcal_params cal_params[2];
	काष्ठा nphy_iq_est est;
	पूर्णांक ret = 0;
	bool playtone = true;
	पूर्णांक desired = 13;

	b43_nphy_stay_in_carrier_search(dev, 1);

	अगर (dev->phy.rev < 2)
		b43_nphy_reapply_tx_cal_coeffs(dev);
	b43_ntab_पढ़ो_bulk(dev, B43_NTAB16(7, 0x110), 2, gain_save);
	क्रम (i = 0; i < 2; i++) अणु
		b43_nphy_iq_cal_gain_params(dev, i, target, &cal_params[i]);
		cal_gain[i] = cal_params[i].cal_gain;
	पूर्ण
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(7, 0x110), 2, cal_gain);

	क्रम (i = 0; i < 2; i++) अणु
		अगर (i == 0) अणु
			rfctl[0] = B43_NPHY_RFCTL_INTC1;
			rfctl[1] = B43_NPHY_RFCTL_INTC2;
			afectl_core = B43_NPHY_AFECTL_C1;
		पूर्ण अन्यथा अणु
			rfctl[0] = B43_NPHY_RFCTL_INTC2;
			rfctl[1] = B43_NPHY_RFCTL_INTC1;
			afectl_core = B43_NPHY_AFECTL_C2;
		पूर्ण

		पंचांगp[1] = b43_phy_पढ़ो(dev, B43_NPHY_RFSEQCA);
		पंचांगp[2] = b43_phy_पढ़ो(dev, afectl_core);
		पंचांगp[3] = b43_phy_पढ़ो(dev, B43_NPHY_AFECTL_OVER);
		पंचांगp[4] = b43_phy_पढ़ो(dev, rfctl[0]);
		पंचांगp[5] = b43_phy_पढ़ो(dev, rfctl[1]);

		b43_phy_maskset(dev, B43_NPHY_RFSEQCA,
				~B43_NPHY_RFSEQCA_RXDIS & 0xFFFF,
				((1 - i) << B43_NPHY_RFSEQCA_RXDIS_SHIFT));
		b43_phy_maskset(dev, B43_NPHY_RFSEQCA, ~B43_NPHY_RFSEQCA_TXEN,
				(1 - i));
		b43_phy_set(dev, afectl_core, 0x0006);
		b43_phy_set(dev, B43_NPHY_AFECTL_OVER, 0x0006);

		band = b43_current_band(dev->wl);

		अगर (nphy->rxcalparams & 0xFF000000) अणु
			अगर (band == NL80211_BAND_5GHZ)
				b43_phy_ग_लिखो(dev, rfctl[0], 0x140);
			अन्यथा
				b43_phy_ग_लिखो(dev, rfctl[0], 0x110);
		पूर्ण अन्यथा अणु
			अगर (band == NL80211_BAND_5GHZ)
				b43_phy_ग_लिखो(dev, rfctl[0], 0x180);
			अन्यथा
				b43_phy_ग_लिखो(dev, rfctl[0], 0x120);
		पूर्ण

		अगर (band == NL80211_BAND_5GHZ)
			b43_phy_ग_लिखो(dev, rfctl[1], 0x148);
		अन्यथा
			b43_phy_ग_लिखो(dev, rfctl[1], 0x114);

		अगर (nphy->rxcalparams & 0x10000) अणु
			b43_radio_maskset(dev, B2055_C1_GENSPARE2, 0xFC,
					(i + 1));
			b43_radio_maskset(dev, B2055_C2_GENSPARE2, 0xFC,
					(2 - i));
		पूर्ण

		क्रम (j = 0; j < 4; j++) अणु
			अगर (j < 3) अणु
				cur_lna = lna[j];
				cur_hpf1 = hpf1[j];
				cur_hpf2 = hpf2[j];
			पूर्ण अन्यथा अणु
				अगर (घातer[1] > 10000) अणु
					use = 1;
					cur_hpf = cur_hpf1;
					index = 2;
				पूर्ण अन्यथा अणु
					अगर (घातer[0] > 10000) अणु
						use = 1;
						cur_hpf = cur_hpf1;
						index = 1;
					पूर्ण अन्यथा अणु
						index = 0;
						use = 2;
						cur_hpf = cur_hpf2;
					पूर्ण
				पूर्ण
				cur_lna = lna[index];
				cur_hpf1 = hpf1[index];
				cur_hpf2 = hpf2[index];
				cur_hpf += desired - hweight32(घातer[index]);
				cur_hpf = clamp_val(cur_hpf, 0, 10);
				अगर (use == 1)
					cur_hpf1 = cur_hpf;
				अन्यथा
					cur_hpf2 = cur_hpf;
			पूर्ण

			पंचांगp[0] = ((cur_hpf2 << 8) | (cur_hpf1 << 4) |
					(cur_lna << 2));
			b43_nphy_rf_ctl_override(dev, 0x400, पंचांगp[0], 3,
									false);
			b43_nphy_क्रमce_rf_sequence(dev, B43_RFSEQ_RESET2RX);
			b43_nphy_stop_playback(dev);

			अगर (playtone) अणु
				ret = b43_nphy_tx_tone(dev, 4000,
						(nphy->rxcalparams & 0xFFFF),
						false, false, true);
				playtone = false;
			पूर्ण अन्यथा अणु
				b43_nphy_run_samples(dev, 160, 0xFFFF, 0, false,
						     false, true);
			पूर्ण

			अगर (ret == 0) अणु
				अगर (j < 3) अणु
					b43_nphy_rx_iq_est(dev, &est, 1024, 32,
									false);
					अगर (i == 0) अणु
						real = est.i0_pwr;
						imag = est.q0_pwr;
					पूर्ण अन्यथा अणु
						real = est.i1_pwr;
						imag = est.q1_pwr;
					पूर्ण
					घातer[i] = ((real + imag) / 1024) + 1;
				पूर्ण अन्यथा अणु
					b43_nphy_calc_rx_iq_comp(dev, 1 << i);
				पूर्ण
				b43_nphy_stop_playback(dev);
			पूर्ण

			अगर (ret != 0)
				अवरोध;
		पूर्ण

		b43_radio_mask(dev, B2055_C1_GENSPARE2, 0xFC);
		b43_radio_mask(dev, B2055_C2_GENSPARE2, 0xFC);
		b43_phy_ग_लिखो(dev, rfctl[1], पंचांगp[5]);
		b43_phy_ग_लिखो(dev, rfctl[0], पंचांगp[4]);
		b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_OVER, पंचांगp[3]);
		b43_phy_ग_लिखो(dev, afectl_core, पंचांगp[2]);
		b43_phy_ग_लिखो(dev, B43_NPHY_RFSEQCA, पंचांगp[1]);

		अगर (ret != 0)
			अवरोध;
	पूर्ण

	b43_nphy_rf_ctl_override(dev, 0x400, 0, 3, true);
	b43_nphy_क्रमce_rf_sequence(dev, B43_RFSEQ_RESET2RX);
	b43_ntab_ग_लिखो_bulk(dev, B43_NTAB16(7, 0x110), 2, gain_save);

	b43_nphy_stay_in_carrier_search(dev, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक b43_nphy_rev3_cal_rx_iq(काष्ठा b43_wldev *dev,
			काष्ठा nphy_txgains target, u8 type, bool debug)
अणु
	वापस -1;
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/CalRxIq */
अटल पूर्णांक b43_nphy_cal_rx_iq(काष्ठा b43_wldev *dev,
			काष्ठा nphy_txgains target, u8 type, bool debug)
अणु
	अगर (dev->phy.rev >= 7)
		type = 0;

	अगर (dev->phy.rev >= 3)
		वापस b43_nphy_rev3_cal_rx_iq(dev, target, type, debug);
	अन्यथा
		वापस b43_nphy_rev2_cal_rx_iq(dev, target, type, debug);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/RxCoreSetState */
अटल व्योम b43_nphy_set_rx_core_state(काष्ठा b43_wldev *dev, u8 mask)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_n *nphy = phy->n;
	/* u16 buf[16]; it's rev3+ */

	nphy->phyrxchain = mask;

	अगर (0 /* FIXME clk */)
		वापस;

	b43_mac_suspend(dev);

	अगर (nphy->hang_aव्योम)
		b43_nphy_stay_in_carrier_search(dev, true);

	b43_phy_maskset(dev, B43_NPHY_RFSEQCA, ~B43_NPHY_RFSEQCA_RXEN,
			(mask & 0x3) << B43_NPHY_RFSEQCA_RXEN_SHIFT);

	अगर ((mask & 0x3) != 0x3) अणु
		b43_phy_ग_लिखो(dev, B43_NPHY_HPANT_SWTHRES, 1);
		अगर (dev->phy.rev >= 3) अणु
			/* TODO */
		पूर्ण
	पूर्ण अन्यथा अणु
		b43_phy_ग_लिखो(dev, B43_NPHY_HPANT_SWTHRES, 0x1E);
		अगर (dev->phy.rev >= 3) अणु
			/* TODO */
		पूर्ण
	पूर्ण

	b43_nphy_क्रमce_rf_sequence(dev, B43_RFSEQ_RESET2RX);

	अगर (nphy->hang_aव्योम)
		b43_nphy_stay_in_carrier_search(dev, false);

	b43_mac_enable(dev);
पूर्ण

अटल क्रमागत b43_txpwr_result b43_nphy_op_recalc_txघातer(काष्ठा b43_wldev *dev,
							bool ignore_tssi)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_n *nphy = dev->phy.n;
	काष्ठा ieee80211_channel *channel = dev->wl->hw->conf.chandef.chan;
	काष्ठा b43_ppr *ppr = &nphy->tx_pwr_max_ppr;
	u8 max; /* qdBm */

	अगर (nphy->tx_pwr_last_recalc_freq == channel->center_freq &&
	    nphy->tx_pwr_last_recalc_limit == phy->desired_txघातer)
		वापस B43_TXPWR_RES_DONE;

	/* Make sure we have a clean PPR */
	b43_ppr_clear(dev, ppr);

	/* HW limitations */
	b43_ppr_load_max_from_sprom(dev, ppr, B43_BAND_2G);

	/* Regulatory & user settings */
	max = INT_TO_Q52(phy->chandef->chan->max_घातer);
	अगर (phy->desired_txघातer)
		max = min_t(u8, max, INT_TO_Q52(phy->desired_txघातer));
	b43_ppr_apply_max(dev, ppr, max);
	अगर (b43_debug(dev, B43_DBG_XMITPOWER))
		b43dbg(dev->wl, "Calculated TX power: " Q52_FMT "\n",
		       Q52_ARG(b43_ppr_get_max(dev, ppr)));

	/* TODO: Enable this once we get gains working */
#अगर 0
	/* Some extra gains */
	hw_gain = 6; /* N-PHY specअगरic */
	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
		hw_gain += sprom->antenna_gain.a0;
	अन्यथा
		hw_gain += sprom->antenna_gain.a1;
	b43_ppr_add(dev, ppr, -hw_gain);
#पूर्ण_अगर

	/* Make sure we didn't go too low */
	b43_ppr_apply_min(dev, ppr, INT_TO_Q52(8));

	/* Apply */
	b43_mac_suspend(dev);
	b43_nphy_tx_घातer_ctl_setup(dev);
	अगर (dev->dev->core_rev == 11 || dev->dev->core_rev == 12) अणु
		b43_maskset32(dev, B43_MMIO_MACCTL, ~0, B43_MACCTL_PHY_LOCK);
		b43_पढ़ो32(dev, B43_MMIO_MACCTL);
		udelay(1);
	पूर्ण
	b43_nphy_tx_घातer_ctrl(dev, nphy->txpwrctrl);
	अगर (dev->dev->core_rev == 11 || dev->dev->core_rev == 12)
		b43_maskset32(dev, B43_MMIO_MACCTL, ~B43_MACCTL_PHY_LOCK, 0);
	b43_mac_enable(dev);

	nphy->tx_pwr_last_recalc_freq = channel->center_freq;
	nphy->tx_pwr_last_recalc_limit = phy->desired_txघातer;

	वापस B43_TXPWR_RES_DONE;
पूर्ण

/**************************************************
 * N-PHY init
 **************************************************/

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/MIMOConfig */
अटल व्योम b43_nphy_update_mimo_config(काष्ठा b43_wldev *dev, s32 preamble)
अणु
	u16 mimocfg = b43_phy_पढ़ो(dev, B43_NPHY_MIMOCFG);

	mimocfg |= B43_NPHY_MIMOCFG_AUTO;
	अगर (preamble == 1)
		mimocfg |= B43_NPHY_MIMOCFG_GFMIX;
	अन्यथा
		mimocfg &= ~B43_NPHY_MIMOCFG_GFMIX;

	b43_phy_ग_लिखो(dev, B43_NPHY_MIMOCFG, mimocfg);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/BPHYInit */
अटल व्योम b43_nphy_bphy_init(काष्ठा b43_wldev *dev)
अणु
	अचिन्हित पूर्णांक i;
	u16 val;

	val = 0x1E1F;
	क्रम (i = 0; i < 16; i++) अणु
		b43_phy_ग_लिखो(dev, B43_PHY_N_BMODE(0x88 + i), val);
		val -= 0x202;
	पूर्ण
	val = 0x3E3F;
	क्रम (i = 0; i < 16; i++) अणु
		b43_phy_ग_लिखो(dev, B43_PHY_N_BMODE(0x98 + i), val);
		val -= 0x202;
	पूर्ण
	b43_phy_ग_लिखो(dev, B43_PHY_N_BMODE(0x38), 0x668);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/SuperSwitchInit */
अटल व्योम b43_nphy_superचयन_init(काष्ठा b43_wldev *dev, bool init)
अणु
	अगर (dev->phy.rev >= 7)
		वापस;

	अगर (dev->phy.rev >= 3) अणु
		अगर (!init)
			वापस;
		अगर (0 /* FIXME */) अणु
			b43_ntab_ग_लिखो(dev, B43_NTAB16(9, 2), 0x211);
			b43_ntab_ग_लिखो(dev, B43_NTAB16(9, 3), 0x222);
			b43_ntab_ग_लिखो(dev, B43_NTAB16(9, 8), 0x144);
			b43_ntab_ग_लिखो(dev, B43_NTAB16(9, 12), 0x188);
		पूर्ण
	पूर्ण अन्यथा अणु
		b43_phy_ग_लिखो(dev, B43_NPHY_GPIO_LOOEN, 0);
		b43_phy_ग_लिखो(dev, B43_NPHY_GPIO_HIOEN, 0);

		चयन (dev->dev->bus_type) अणु
#अगर_घोषित CONFIG_B43_BCMA
		हाल B43_BUS_BCMA:
			bcma_chipco_gpio_control(&dev->dev->bdev->bus->drv_cc,
						 0xFC00, 0xFC00);
			अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SSB
		हाल B43_BUS_SSB:
			ssb_chipco_gpio_control(&dev->dev->sdev->bus->chipco,
						0xFC00, 0xFC00);
			अवरोध;
#पूर्ण_अगर
		पूर्ण

		b43_maskset32(dev, B43_MMIO_MACCTL, ~B43_MACCTL_GPOUTSMSK, 0);
		b43_maskset16(dev, B43_MMIO_GPIO_MASK, ~0, 0xFC00);
		b43_maskset16(dev, B43_MMIO_GPIO_CONTROL, (~0xFC00 & 0xFFFF),
			      0);

		अगर (init) अणु
			b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_LUT_TRSW_LO1, 0x2D8);
			b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_LUT_TRSW_UP1, 0x301);
			b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_LUT_TRSW_LO2, 0x2D8);
			b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_LUT_TRSW_UP2, 0x301);
		पूर्ण
	पूर्ण
पूर्ण

/* http://bcm-v4.sipsolutions.net/802.11/PHY/Init/N */
अटल पूर्णांक b43_phy_initn(काष्ठा b43_wldev *dev)
अणु
	काष्ठा ssb_sprom *sprom = dev->dev->bus_sprom;
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_n *nphy = phy->n;
	u8 tx_pwr_state;
	काष्ठा nphy_txgains target;
	u16 पंचांगp;
	bool करो_rssi_cal;

	u16 clip[2];
	bool करो_cal = false;

	अगर ((dev->phy.rev >= 3) &&
	   (sprom->boardflags_lo & B43_BFL_EXTLNA) &&
	   (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)) अणु
		चयन (dev->dev->bus_type) अणु
#अगर_घोषित CONFIG_B43_BCMA
		हाल B43_BUS_BCMA:
			bcma_cc_set32(&dev->dev->bdev->bus->drv_cc,
				      BCMA_CC_CHIPCTL, 0x40);
			अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SSB
		हाल B43_BUS_SSB:
			chipco_set32(&dev->dev->sdev->bus->chipco,
				     SSB_CHIPCO_CHIPCTL, 0x40);
			अवरोध;
#पूर्ण_अगर
		पूर्ण
	पूर्ण
	nphy->use_पूर्णांक_tx_iq_lo_cal = b43_nphy_ipa(dev) ||
		phy->rev >= 7 ||
		(phy->rev >= 5 &&
		 sprom->boardflags2_hi & B43_BFH2_INTERNDET_TXIQCAL);
	nphy->deaf_count = 0;
	b43_nphy_tables_init(dev);
	nphy->crsminpwr_adjusted = false;
	nphy->noisevars_adjusted = false;

	/* Clear all overrides */
	अगर (dev->phy.rev >= 3) अणु
		b43_phy_ग_लिखो(dev, B43_NPHY_TXF_40CO_B1S1, 0);
		b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_OVER, 0);
		अगर (phy->rev >= 7) अणु
			b43_phy_ग_लिखो(dev, B43_NPHY_REV7_RF_CTL_OVER3, 0);
			b43_phy_ग_लिखो(dev, B43_NPHY_REV7_RF_CTL_OVER4, 0);
			b43_phy_ग_लिखो(dev, B43_NPHY_REV7_RF_CTL_OVER5, 0);
			b43_phy_ग_लिखो(dev, B43_NPHY_REV7_RF_CTL_OVER6, 0);
		पूर्ण
		अगर (phy->rev >= 19) अणु
			/* TODO */
		पूर्ण

		b43_phy_ग_लिखो(dev, B43_NPHY_TXF_40CO_B1S0, 0);
		b43_phy_ग_लिखो(dev, B43_NPHY_TXF_40CO_B32S1, 0);
	पूर्ण अन्यथा अणु
		b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_OVER, 0);
	पूर्ण
	b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_INTC1, 0);
	b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_INTC2, 0);
	अगर (dev->phy.rev < 6) अणु
		b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_INTC3, 0);
		b43_phy_ग_लिखो(dev, B43_NPHY_RFCTL_INTC4, 0);
	पूर्ण
	b43_phy_mask(dev, B43_NPHY_RFSEQMODE,
		     ~(B43_NPHY_RFSEQMODE_CAOVER |
		       B43_NPHY_RFSEQMODE_TROVER));
	अगर (dev->phy.rev >= 3)
		b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_OVER1, 0);
	b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_OVER, 0);

	अगर (dev->phy.rev <= 2) अणु
		पंचांगp = (dev->phy.rev == 2) ? 0x3B : 0x40;
		b43_phy_maskset(dev, B43_NPHY_BPHY_CTL3,
				~B43_NPHY_BPHY_CTL3_SCALE,
				पंचांगp << B43_NPHY_BPHY_CTL3_SCALE_SHIFT);
	पूर्ण
	b43_phy_ग_लिखो(dev, B43_NPHY_AFESEQ_TX2RX_PUD_20M, 0x20);
	b43_phy_ग_लिखो(dev, B43_NPHY_AFESEQ_TX2RX_PUD_40M, 0x20);

	अगर (sprom->boardflags2_lo & B43_BFL2_SKWRKFEM_BRD ||
	    (dev->dev->board_venकरोr == PCI_VENDOR_ID_APPLE &&
	     dev->dev->board_type == BCMA_BOARD_TYPE_BCM943224M93))
		b43_phy_ग_लिखो(dev, B43_NPHY_TXREALFD, 0xA0);
	अन्यथा
		b43_phy_ग_लिखो(dev, B43_NPHY_TXREALFD, 0xB8);
	b43_phy_ग_लिखो(dev, B43_NPHY_MIMO_CRSTXEXT, 0xC8);
	b43_phy_ग_लिखो(dev, B43_NPHY_PLOAD_CSENSE_EXTLEN, 0x50);
	b43_phy_ग_लिखो(dev, B43_NPHY_TXRIFS_FRDEL, 0x30);

	अगर (phy->rev < 8)
		b43_nphy_update_mimo_config(dev, nphy->preamble_override);

	b43_nphy_update_txrx_chain(dev);

	अगर (phy->rev < 2) अणु
		b43_phy_ग_लिखो(dev, B43_NPHY_DUP40_GFBL, 0xAA8);
		b43_phy_ग_लिखो(dev, B43_NPHY_DUP40_BL, 0x9A4);
	पूर्ण

	अगर (b43_nphy_ipa(dev)) अणु
		b43_phy_set(dev, B43_NPHY_PAPD_EN0, 0x1);
		b43_phy_maskset(dev, B43_NPHY_EPS_TABLE_ADJ0, 0x007F,
				nphy->papd_epsilon_offset[0] << 7);
		b43_phy_set(dev, B43_NPHY_PAPD_EN1, 0x1);
		b43_phy_maskset(dev, B43_NPHY_EPS_TABLE_ADJ1, 0x007F,
				nphy->papd_epsilon_offset[1] << 7);
		b43_nphy_पूर्णांक_pa_set_tx_dig_filters(dev);
	पूर्ण अन्यथा अगर (phy->rev >= 5) अणु
		b43_nphy_ext_pa_set_tx_dig_filters(dev);
	पूर्ण

	b43_nphy_workarounds(dev);

	/* Reset CCA, in init code it dअगरfers a little from standard way */
	b43_phy_क्रमce_घड़ी(dev, 1);
	पंचांगp = b43_phy_पढ़ो(dev, B43_NPHY_BBCFG);
	b43_phy_ग_लिखो(dev, B43_NPHY_BBCFG, पंचांगp | B43_NPHY_BBCFG_RSTCCA);
	b43_phy_ग_लिखो(dev, B43_NPHY_BBCFG, पंचांगp & ~B43_NPHY_BBCFG_RSTCCA);
	b43_phy_क्रमce_घड़ी(dev, 0);

	b43_mac_phy_घड़ी_set(dev, true);

	अगर (phy->rev < 7) अणु
		b43_nphy_pa_override(dev, false);
		b43_nphy_क्रमce_rf_sequence(dev, B43_RFSEQ_RX2TX);
		b43_nphy_क्रमce_rf_sequence(dev, B43_RFSEQ_RESET2RX);
		b43_nphy_pa_override(dev, true);
	पूर्ण

	b43_nphy_classअगरier(dev, 0, 0);
	b43_nphy_पढ़ो_clip_detection(dev, clip);
	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
		b43_nphy_bphy_init(dev);

	tx_pwr_state = nphy->txpwrctrl;
	b43_nphy_tx_घातer_ctrl(dev, false);
	b43_nphy_tx_घातer_fix(dev);
	b43_nphy_tx_घातer_ctl_idle_tssi(dev);
	b43_nphy_tx_घातer_ctl_setup(dev);
	b43_nphy_tx_gain_table_upload(dev);

	अगर (nphy->phyrxchain != 3)
		b43_nphy_set_rx_core_state(dev, nphy->phyrxchain);
	अगर (nphy->mphase_cal_phase_id > 0) अणु
		;/* TODO PHY Periodic Calibration Multi-Phase Restart */
	पूर्ण

	करो_rssi_cal = false;
	अगर (phy->rev >= 3) अणु
		अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
			करो_rssi_cal = !nphy->rssical_chanspec_2G.center_freq;
		अन्यथा
			करो_rssi_cal = !nphy->rssical_chanspec_5G.center_freq;

		अगर (करो_rssi_cal)
			b43_nphy_rssi_cal(dev);
		अन्यथा
			b43_nphy_restore_rssi_cal(dev);
	पूर्ण अन्यथा अणु
		b43_nphy_rssi_cal(dev);
	पूर्ण

	अगर (!((nphy->measure_hold & 0x6) != 0)) अणु
		अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
			करो_cal = !nphy->iqcal_chanspec_2G.center_freq;
		अन्यथा
			करो_cal = !nphy->iqcal_chanspec_5G.center_freq;

		अगर (nphy->mute)
			करो_cal = false;

		अगर (करो_cal) अणु
			target = b43_nphy_get_tx_gains(dev);

			अगर (nphy->antsel_type == 2)
				b43_nphy_superचयन_init(dev, true);
			अगर (nphy->perical != 2) अणु
				b43_nphy_rssi_cal(dev);
				अगर (phy->rev >= 3) अणु
					nphy->cal_orig_pwr_idx[0] =
					    nphy->txpwrindex[0].index_पूर्णांकernal;
					nphy->cal_orig_pwr_idx[1] =
					    nphy->txpwrindex[1].index_पूर्णांकernal;
					/* TODO N PHY Pre Calibrate TX Gain */
					target = b43_nphy_get_tx_gains(dev);
				पूर्ण
				अगर (!b43_nphy_cal_tx_iq_lo(dev, target, true, false))
					अगर (b43_nphy_cal_rx_iq(dev, target, 2, 0) == 0)
						b43_nphy_save_cal(dev);
			पूर्ण अन्यथा अगर (nphy->mphase_cal_phase_id == 0) अणु
				;/* N PHY Periodic Calibration with arg 3 */
			पूर्ण
		पूर्ण अन्यथा अणु
			b43_nphy_restore_cal(dev);
		पूर्ण
	पूर्ण

	b43_nphy_tx_pwr_ctrl_coef_setup(dev);
	b43_nphy_tx_घातer_ctrl(dev, tx_pwr_state);
	b43_phy_ग_लिखो(dev, B43_NPHY_TXMACIF_HOLDOFF, 0x0015);
	b43_phy_ग_लिखो(dev, B43_NPHY_TXMACDELAY, 0x0320);
	अगर (phy->rev >= 3 && phy->rev <= 6)
		b43_phy_ग_लिखो(dev, B43_NPHY_PLOAD_CSENSE_EXTLEN, 0x0032);
	b43_nphy_tx_lpf_bw(dev);
	अगर (phy->rev >= 3)
		b43_nphy_spur_workaround(dev);

	वापस 0;
पूर्ण

/**************************************************
 * Channel चयनing ops.
 **************************************************/

अटल व्योम b43_chantab_phy_upload(काष्ठा b43_wldev *dev,
				   स्थिर काष्ठा b43_phy_n_sfo_cfg *e)
अणु
	b43_phy_ग_लिखो(dev, B43_NPHY_BW1A, e->phy_bw1a);
	b43_phy_ग_लिखो(dev, B43_NPHY_BW2, e->phy_bw2);
	b43_phy_ग_लिखो(dev, B43_NPHY_BW3, e->phy_bw3);
	b43_phy_ग_लिखो(dev, B43_NPHY_BW4, e->phy_bw4);
	b43_phy_ग_लिखो(dev, B43_NPHY_BW5, e->phy_bw5);
	b43_phy_ग_लिखो(dev, B43_NPHY_BW6, e->phy_bw6);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PmuSpurAव्योम */
अटल व्योम b43_nphy_pmu_spur_aव्योम(काष्ठा b43_wldev *dev, bool aव्योम)
अणु
	चयन (dev->dev->bus_type) अणु
#अगर_घोषित CONFIG_B43_BCMA
	हाल B43_BUS_BCMA:
		bcma_pmu_spuraव्योम_pllupdate(&dev->dev->bdev->bus->drv_cc,
					     aव्योम);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SSB
	हाल B43_BUS_SSB:
		ssb_pmu_spuraव्योम_pllupdate(&dev->dev->sdev->bus->chipco,
					    aव्योम);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/ChanspecSetup */
अटल व्योम b43_nphy_channel_setup(काष्ठा b43_wldev *dev,
				स्थिर काष्ठा b43_phy_n_sfo_cfg *e,
				काष्ठा ieee80211_channel *new_channel)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_n *nphy = dev->phy.n;
	पूर्णांक ch = new_channel->hw_value;
	u16 पंचांगp16;

	अगर (new_channel->band == NL80211_BAND_5GHZ) अणु
		/* Switch to 2 GHz क्रम a moment to access B43_PHY_B_BBCFG */
		b43_phy_mask(dev, B43_NPHY_BANDCTL, ~B43_NPHY_BANDCTL_5GHZ);

		पंचांगp16 = b43_पढ़ो16(dev, B43_MMIO_PSM_PHY_HDR);
		b43_ग_लिखो16(dev, B43_MMIO_PSM_PHY_HDR, पंचांगp16 | 4);
		/* Put BPHY in the reset */
		b43_phy_set(dev, B43_PHY_B_BBCFG,
			    B43_PHY_B_BBCFG_RSTCCA | B43_PHY_B_BBCFG_RSTRX);
		b43_ग_लिखो16(dev, B43_MMIO_PSM_PHY_HDR, पंचांगp16);
		b43_phy_set(dev, B43_NPHY_BANDCTL, B43_NPHY_BANDCTL_5GHZ);
	पूर्ण अन्यथा अगर (new_channel->band == NL80211_BAND_2GHZ) अणु
		b43_phy_mask(dev, B43_NPHY_BANDCTL, ~B43_NPHY_BANDCTL_5GHZ);
		पंचांगp16 = b43_पढ़ो16(dev, B43_MMIO_PSM_PHY_HDR);
		b43_ग_लिखो16(dev, B43_MMIO_PSM_PHY_HDR, पंचांगp16 | 4);
		/* Take BPHY out of the reset */
		b43_phy_mask(dev, B43_PHY_B_BBCFG,
			     (u16)~(B43_PHY_B_BBCFG_RSTCCA | B43_PHY_B_BBCFG_RSTRX));
		b43_ग_लिखो16(dev, B43_MMIO_PSM_PHY_HDR, पंचांगp16);
	पूर्ण

	b43_chantab_phy_upload(dev, e);

	अगर (new_channel->hw_value == 14) अणु
		b43_nphy_classअगरier(dev, 2, 0);
		b43_phy_set(dev, B43_PHY_B_TEST, 0x0800);
	पूर्ण अन्यथा अणु
		b43_nphy_classअगरier(dev, 2, 2);
		अगर (new_channel->band == NL80211_BAND_2GHZ)
			b43_phy_mask(dev, B43_PHY_B_TEST, ~0x840);
	पूर्ण

	अगर (!nphy->txpwrctrl)
		b43_nphy_tx_घातer_fix(dev);

	अगर (dev->phy.rev < 3)
		b43_nphy_adjust_lna_gain_table(dev);

	b43_nphy_tx_lpf_bw(dev);

	अगर (dev->phy.rev >= 3 &&
	    dev->phy.n->spur_aव्योम != B43_SPUR_AVOID_DISABLE) अणु
		u8 spuraव्योम = 0;

		अगर (dev->phy.n->spur_aव्योम == B43_SPUR_AVOID_FORCE) अणु
			spuraव्योम = 1;
		पूर्ण अन्यथा अगर (phy->rev >= 19) अणु
			/* TODO */
		पूर्ण अन्यथा अगर (phy->rev >= 18) अणु
			/* TODO */
		पूर्ण अन्यथा अगर (phy->rev >= 17) अणु
			/* TODO: Off क्रम channels 1-11, but check 12-14! */
		पूर्ण अन्यथा अगर (phy->rev >= 16) अणु
			/* TODO: Off क्रम 2 GHz, but check 5 GHz! */
		पूर्ण अन्यथा अगर (phy->rev >= 7) अणु
			अगर (!b43_is_40mhz(dev)) अणु /* 20MHz */
				अगर (ch == 13 || ch == 14 || ch == 153)
					spuraव्योम = 1;
			पूर्ण अन्यथा अणु /* 40 MHz */
				अगर (ch == 54)
					spuraव्योम = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!b43_is_40mhz(dev)) अणु /* 20MHz */
				अगर ((ch >= 5 && ch <= 8) || ch == 13 || ch == 14)
					spuraव्योम = 1;
			पूर्ण अन्यथा अणु /* 40MHz */
				अगर (nphy->aband_spurwar_en &&
				    (ch == 38 || ch == 102 || ch == 118))
					spuraव्योम = dev->dev->chip_id == 0x4716;
			पूर्ण
		पूर्ण

		b43_nphy_pmu_spur_aव्योम(dev, spuraव्योम);

		b43_mac_चयन_freq(dev, spuraव्योम);

		अगर (dev->phy.rev == 3 || dev->phy.rev == 4)
			b43_wireless_core_phy_pll_reset(dev);

		अगर (spuraव्योम)
			b43_phy_set(dev, B43_NPHY_BBCFG, B43_NPHY_BBCFG_RSTRX);
		अन्यथा
			b43_phy_mask(dev, B43_NPHY_BBCFG,
				     ~B43_NPHY_BBCFG_RSTRX & 0xFFFF);

		b43_nphy_reset_cca(dev);

		/* wl sets useless phy_isspuraव्योम here */
	पूर्ण

	b43_phy_ग_लिखो(dev, B43_NPHY_NDATAT_DUP40, 0x3830);

	अगर (phy->rev >= 3)
		b43_nphy_spur_workaround(dev);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/SetChanspec */
अटल पूर्णांक b43_nphy_set_channel(काष्ठा b43_wldev *dev,
				काष्ठा ieee80211_channel *channel,
				क्रमागत nl80211_channel_type channel_type)
अणु
	काष्ठा b43_phy *phy = &dev->phy;

	स्थिर काष्ठा b43_nphy_channeltab_entry_rev2 *tabent_r2 = शून्य;
	स्थिर काष्ठा b43_nphy_channeltab_entry_rev3 *tabent_r3 = शून्य;
	स्थिर काष्ठा b43_nphy_chantabent_rev7 *tabent_r7 = शून्य;
	स्थिर काष्ठा b43_nphy_chantabent_rev7_2g *tabent_r7_2g = शून्य;

	u8 पंचांगp;

	अगर (phy->rev >= 19) अणु
		वापस -ESRCH;
		/* TODO */
	पूर्ण अन्यथा अगर (phy->rev >= 7) अणु
		r2057_get_chantabent_rev7(dev, channel->center_freq,
					  &tabent_r7, &tabent_r7_2g);
		अगर (!tabent_r7 && !tabent_r7_2g)
			वापस -ESRCH;
	पूर्ण अन्यथा अगर (phy->rev >= 3) अणु
		tabent_r3 = b43_nphy_get_chantabent_rev3(dev,
							channel->center_freq);
		अगर (!tabent_r3)
			वापस -ESRCH;
	पूर्ण अन्यथा अणु
		tabent_r2 = b43_nphy_get_chantabent_rev2(dev,
							channel->hw_value);
		अगर (!tabent_r2)
			वापस -ESRCH;
	पूर्ण

	/* Channel is set later in common code, but we need to set it on our
	   own to let this function's subcalls work properly. */
	phy->channel = channel->hw_value;

#अगर 0
	अगर (b43_channel_type_is_40mhz(phy->channel_type) !=
		b43_channel_type_is_40mhz(channel_type))
		; /* TODO: BMAC BW Set (channel_type) */
#पूर्ण_अगर

	अगर (channel_type == NL80211_CHAN_HT40PLUS) अणु
		b43_phy_set(dev, B43_NPHY_RXCTL, B43_NPHY_RXCTL_BSELU20);
		अगर (phy->rev >= 7)
			b43_phy_set(dev, 0x310, 0x8000);
	पूर्ण अन्यथा अगर (channel_type == NL80211_CHAN_HT40MINUS) अणु
		b43_phy_mask(dev, B43_NPHY_RXCTL, ~B43_NPHY_RXCTL_BSELU20);
		अगर (phy->rev >= 7)
			b43_phy_mask(dev, 0x310, (u16)~0x8000);
	पूर्ण

	अगर (phy->rev >= 19) अणु
		/* TODO */
	पूर्ण अन्यथा अगर (phy->rev >= 7) अणु
		स्थिर काष्ठा b43_phy_n_sfo_cfg *phy_regs = tabent_r7 ?
			&(tabent_r7->phy_regs) : &(tabent_r7_2g->phy_regs);

		अगर (phy->radio_rev <= 4 || phy->radio_rev == 6) अणु
			पंचांगp = (channel->band == NL80211_BAND_5GHZ) ? 2 : 0;
			b43_radio_maskset(dev, R2057_TIA_CONFIG_CORE0, ~2, पंचांगp);
			b43_radio_maskset(dev, R2057_TIA_CONFIG_CORE1, ~2, पंचांगp);
		पूर्ण

		b43_radio_2057_setup(dev, tabent_r7, tabent_r7_2g);
		b43_nphy_channel_setup(dev, phy_regs, channel);
	पूर्ण अन्यथा अगर (phy->rev >= 3) अणु
		पंचांगp = (channel->band == NL80211_BAND_5GHZ) ? 4 : 0;
		b43_radio_maskset(dev, 0x08, 0xFFFB, पंचांगp);
		b43_radio_2056_setup(dev, tabent_r3);
		b43_nphy_channel_setup(dev, &(tabent_r3->phy_regs), channel);
	पूर्ण अन्यथा अणु
		पंचांगp = (channel->band == NL80211_BAND_5GHZ) ? 0x0020 : 0x0050;
		b43_radio_maskset(dev, B2055_MASTER1, 0xFF8F, पंचांगp);
		b43_radio_2055_setup(dev, tabent_r2);
		b43_nphy_channel_setup(dev, &(tabent_r2->phy_regs), channel);
	पूर्ण

	वापस 0;
पूर्ण

/**************************************************
 * Basic PHY ops.
 **************************************************/

अटल पूर्णांक b43_nphy_op_allocate(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_n *nphy;

	nphy = kzalloc(माप(*nphy), GFP_KERNEL);
	अगर (!nphy)
		वापस -ENOMEM;

	dev->phy.n = nphy;

	वापस 0;
पूर्ण

अटल व्योम b43_nphy_op_prepare_काष्ठाs(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_n *nphy = phy->n;
	काष्ठा ssb_sprom *sprom = dev->dev->bus_sprom;

	स_रखो(nphy, 0, माप(*nphy));

	nphy->hang_aव्योम = (phy->rev == 3 || phy->rev == 4);
	nphy->spur_aव्योम = (phy->rev >= 3) ?
				B43_SPUR_AVOID_AUTO : B43_SPUR_AVOID_DISABLE;
	nphy->gain_boost = true; /* this way we follow wl, assume it is true */
	nphy->txrx_chain = 2; /* sth dअगरferent than 0 and 1 क्रम now */
	nphy->phyrxchain = 3; /* to aव्योम b43_nphy_set_rx_core_state like wl */
	nphy->perical = 2; /* aव्योम additional rssi cal on init (like wl) */
	/* 128 can mean disabled-by-शेष state of TX pwr ctl. Max value is
	 * 0x7f == 127 and we check क्रम 128 when restoring TX pwr ctl. */
	nphy->tx_pwr_idx[0] = 128;
	nphy->tx_pwr_idx[1] = 128;

	/* Hardware TX घातer control and 5GHz घातer gain */
	nphy->txpwrctrl = false;
	nphy->pwg_gain_5ghz = false;
	अगर (dev->phy.rev >= 3 ||
	    (dev->dev->board_venकरोr == PCI_VENDOR_ID_APPLE &&
	     (dev->dev->core_rev == 11 || dev->dev->core_rev == 12))) अणु
		nphy->txpwrctrl = true;
		nphy->pwg_gain_5ghz = true;
	पूर्ण अन्यथा अगर (sprom->revision >= 4) अणु
		अगर (dev->phy.rev >= 2 &&
		    (sprom->boardflags2_lo & B43_BFL2_TXPWRCTRL_EN)) अणु
			nphy->txpwrctrl = true;
#अगर_घोषित CONFIG_B43_SSB
			अगर (dev->dev->bus_type == B43_BUS_SSB &&
			    dev->dev->sdev->bus->bustype == SSB_BUSTYPE_PCI) अणु
				काष्ठा pci_dev *pdev =
					dev->dev->sdev->bus->host_pci;
				अगर (pdev->device == 0x4328 ||
				    pdev->device == 0x432a)
					nphy->pwg_gain_5ghz = true;
			पूर्ण
#पूर्ण_अगर
		पूर्ण अन्यथा अगर (sprom->boardflags2_lo & B43_BFL2_5G_PWRGAIN) अणु
			nphy->pwg_gain_5ghz = true;
		पूर्ण
	पूर्ण

	अगर (dev->phy.rev >= 3) अणु
		nphy->ipa2g_on = sprom->fem.ghz2.extpa_gain == 2;
		nphy->ipa5g_on = sprom->fem.ghz5.extpa_gain == 2;
	पूर्ण
पूर्ण

अटल व्योम b43_nphy_op_मुक्त(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_n *nphy = phy->n;

	kमुक्त(nphy);
	phy->n = शून्य;
पूर्ण

अटल पूर्णांक b43_nphy_op_init(काष्ठा b43_wldev *dev)
अणु
	वापस b43_phy_initn(dev);
पूर्ण

अटल अंतरभूत व्योम check_phyreg(काष्ठा b43_wldev *dev, u16 offset)
अणु
#अगर B43_DEBUG
	अगर ((offset & B43_PHYROUTE) == B43_PHYROUTE_OFDM_GPHY) अणु
		/* OFDM रेजिस्टरs are onnly available on A/G-PHYs */
		b43err(dev->wl, "Invalid OFDM PHY access at "
		       "0x%04X on N-PHY\n", offset);
		dump_stack();
	पूर्ण
	अगर ((offset & B43_PHYROUTE) == B43_PHYROUTE_EXT_GPHY) अणु
		/* Ext-G रेजिस्टरs are only available on G-PHYs */
		b43err(dev->wl, "Invalid EXT-G PHY access at "
		       "0x%04X on N-PHY\n", offset);
		dump_stack();
	पूर्ण
#पूर्ण_अगर /* B43_DEBUG */
पूर्ण

अटल व्योम b43_nphy_op_maskset(काष्ठा b43_wldev *dev, u16 reg, u16 mask,
				 u16 set)
अणु
	check_phyreg(dev, reg);
	b43_ग_लिखो16f(dev, B43_MMIO_PHY_CONTROL, reg);
	b43_maskset16(dev, B43_MMIO_PHY_DATA, mask, set);
	dev->phy.ग_लिखोs_counter = 1;
पूर्ण

अटल u16 b43_nphy_op_radio_पढ़ो(काष्ठा b43_wldev *dev, u16 reg)
अणु
	/* Register 1 is a 32-bit रेजिस्टर. */
	B43_WARN_ON(dev->phy.rev < 7 && reg == 1);

	अगर (dev->phy.rev >= 7)
		reg |= 0x200; /* Radio 0x2057 */
	अन्यथा
		reg |= 0x100;

	b43_ग_लिखो16f(dev, B43_MMIO_RADIO_CONTROL, reg);
	वापस b43_पढ़ो16(dev, B43_MMIO_RADIO_DATA_LOW);
पूर्ण

अटल व्योम b43_nphy_op_radio_ग_लिखो(काष्ठा b43_wldev *dev, u16 reg, u16 value)
अणु
	/* Register 1 is a 32-bit रेजिस्टर. */
	B43_WARN_ON(dev->phy.rev < 7 && reg == 1);

	b43_ग_लिखो16f(dev, B43_MMIO_RADIO_CONTROL, reg);
	b43_ग_लिखो16(dev, B43_MMIO_RADIO_DATA_LOW, value);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/Radio/Switch%20Radio */
अटल व्योम b43_nphy_op_software_rfसमाप्त(काष्ठा b43_wldev *dev,
					bool blocked)
अणु
	काष्ठा b43_phy *phy = &dev->phy;

	अगर (b43_पढ़ो32(dev, B43_MMIO_MACCTL) & B43_MACCTL_ENABLED)
		b43err(dev->wl, "MAC not suspended\n");

	अगर (blocked) अणु
		अगर (phy->rev >= 19) अणु
			/* TODO */
		पूर्ण अन्यथा अगर (phy->rev >= 8) अणु
			b43_phy_mask(dev, B43_NPHY_RFCTL_CMD,
				     ~B43_NPHY_RFCTL_CMD_CHIP0PU);
		पूर्ण अन्यथा अगर (phy->rev >= 7) अणु
			/* Nothing needed */
		पूर्ण अन्यथा अगर (phy->rev >= 3) अणु
			b43_phy_mask(dev, B43_NPHY_RFCTL_CMD,
				     ~B43_NPHY_RFCTL_CMD_CHIP0PU);

			b43_radio_mask(dev, 0x09, ~0x2);

			b43_radio_ग_लिखो(dev, 0x204D, 0);
			b43_radio_ग_लिखो(dev, 0x2053, 0);
			b43_radio_ग_लिखो(dev, 0x2058, 0);
			b43_radio_ग_लिखो(dev, 0x205E, 0);
			b43_radio_mask(dev, 0x2062, ~0xF0);
			b43_radio_ग_लिखो(dev, 0x2064, 0);

			b43_radio_ग_लिखो(dev, 0x304D, 0);
			b43_radio_ग_लिखो(dev, 0x3053, 0);
			b43_radio_ग_लिखो(dev, 0x3058, 0);
			b43_radio_ग_लिखो(dev, 0x305E, 0);
			b43_radio_mask(dev, 0x3062, ~0xF0);
			b43_radio_ग_लिखो(dev, 0x3064, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (phy->rev >= 19) अणु
			/* TODO */
		पूर्ण अन्यथा अगर (phy->rev >= 7) अणु
			अगर (!dev->phy.radio_on)
				b43_radio_2057_init(dev);
			b43_चयन_channel(dev, dev->phy.channel);
		पूर्ण अन्यथा अगर (phy->rev >= 3) अणु
			अगर (!dev->phy.radio_on)
				b43_radio_init2056(dev);
			b43_चयन_channel(dev, dev->phy.channel);
		पूर्ण अन्यथा अणु
			b43_radio_init2055(dev);
		पूर्ण
	पूर्ण
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/Anacore */
अटल व्योम b43_nphy_op_चयन_analog(काष्ठा b43_wldev *dev, bool on)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	u16 override = on ? 0x0 : 0x7FFF;
	u16 core = on ? 0xD : 0x00FD;

	अगर (phy->rev >= 19) अणु
		/* TODO */
	पूर्ण अन्यथा अगर (phy->rev >= 3) अणु
		अगर (on) अणु
			b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_C1, core);
			b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_OVER1, override);
			b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_C2, core);
			b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_OVER, override);
		पूर्ण अन्यथा अणु
			b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_OVER1, override);
			b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_C1, core);
			b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_OVER, override);
			b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_C2, core);
		पूर्ण
	पूर्ण अन्यथा अणु
		b43_phy_ग_लिखो(dev, B43_NPHY_AFECTL_OVER, override);
	पूर्ण
पूर्ण

अटल पूर्णांक b43_nphy_op_चयन_channel(काष्ठा b43_wldev *dev,
				      अचिन्हित पूर्णांक new_channel)
अणु
	काष्ठा ieee80211_channel *channel = dev->wl->hw->conf.chandef.chan;
	क्रमागत nl80211_channel_type channel_type =
		cfg80211_get_chandef_type(&dev->wl->hw->conf.chandef);

	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
		अगर ((new_channel < 1) || (new_channel > 14))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (new_channel > 200)
			वापस -EINVAL;
	पूर्ण

	वापस b43_nphy_set_channel(dev, channel, channel_type);
पूर्ण

अटल अचिन्हित पूर्णांक b43_nphy_op_get_शेष_chan(काष्ठा b43_wldev *dev)
अणु
	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
		वापस 1;
	वापस 36;
पूर्ण

स्थिर काष्ठा b43_phy_operations b43_phyops_n = अणु
	.allocate		= b43_nphy_op_allocate,
	.मुक्त			= b43_nphy_op_मुक्त,
	.prepare_काष्ठाs	= b43_nphy_op_prepare_काष्ठाs,
	.init			= b43_nphy_op_init,
	.phy_maskset		= b43_nphy_op_maskset,
	.radio_पढ़ो		= b43_nphy_op_radio_पढ़ो,
	.radio_ग_लिखो		= b43_nphy_op_radio_ग_लिखो,
	.software_rfसमाप्त	= b43_nphy_op_software_rfसमाप्त,
	.चयन_analog		= b43_nphy_op_चयन_analog,
	.चयन_channel		= b43_nphy_op_चयन_channel,
	.get_शेष_chan	= b43_nphy_op_get_शेष_chan,
	.recalc_txघातer		= b43_nphy_op_recalc_txघातer,
पूर्ण;
