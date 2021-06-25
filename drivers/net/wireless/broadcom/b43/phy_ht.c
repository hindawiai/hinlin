<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Broadcom B43 wireless driver
  IEEE 802.11n HT-PHY support

  Copyright (c) 2011 Rafaध Miधecki <zajec5@gmail.com>


*/

#समावेश <linux/slab.h>

#समावेश "b43.h"
#समावेश "phy_ht.h"
#समावेश "tables_phy_ht.h"
#समावेश "radio_2059.h"
#समावेश "main.h"

/* Force values to keep compatibility with wl */
क्रमागत ht_rssi_type अणु
	HT_RSSI_W1 = 0,
	HT_RSSI_W2 = 1,
	HT_RSSI_NB = 2,
	HT_RSSI_IQ = 3,
	HT_RSSI_TSSI_2G = 4,
	HT_RSSI_TSSI_5G = 5,
	HT_RSSI_TBD = 6,
पूर्ण;

/**************************************************
 * Radio 2059.
 **************************************************/

अटल व्योम b43_radio_2059_channel_setup(काष्ठा b43_wldev *dev,
			स्थिर काष्ठा b43_phy_ht_channeltab_e_radio2059 *e)
अणु
	अटल स्थिर u16 routing[] = अणु R2059_C1, R2059_C2, R2059_C3, पूर्ण;
	u16 r;
	पूर्णांक core;

	b43_radio_ग_लिखो(dev, 0x16, e->radio_syn16);
	b43_radio_ग_लिखो(dev, 0x17, e->radio_syn17);
	b43_radio_ग_लिखो(dev, 0x22, e->radio_syn22);
	b43_radio_ग_लिखो(dev, 0x25, e->radio_syn25);
	b43_radio_ग_लिखो(dev, 0x27, e->radio_syn27);
	b43_radio_ग_लिखो(dev, 0x28, e->radio_syn28);
	b43_radio_ग_लिखो(dev, 0x29, e->radio_syn29);
	b43_radio_ग_लिखो(dev, 0x2c, e->radio_syn2c);
	b43_radio_ग_लिखो(dev, 0x2d, e->radio_syn2d);
	b43_radio_ग_लिखो(dev, 0x37, e->radio_syn37);
	b43_radio_ग_लिखो(dev, 0x41, e->radio_syn41);
	b43_radio_ग_लिखो(dev, 0x43, e->radio_syn43);
	b43_radio_ग_लिखो(dev, 0x47, e->radio_syn47);

	क्रम (core = 0; core < 3; core++) अणु
		r = routing[core];
		b43_radio_ग_लिखो(dev, r | 0x4a, e->radio_rxtx4a);
		b43_radio_ग_लिखो(dev, r | 0x58, e->radio_rxtx58);
		b43_radio_ग_लिखो(dev, r | 0x5a, e->radio_rxtx5a);
		b43_radio_ग_लिखो(dev, r | 0x6a, e->radio_rxtx6a);
		b43_radio_ग_लिखो(dev, r | 0x6d, e->radio_rxtx6d);
		b43_radio_ग_लिखो(dev, r | 0x6e, e->radio_rxtx6e);
		b43_radio_ग_लिखो(dev, r | 0x92, e->radio_rxtx92);
		b43_radio_ग_लिखो(dev, r | 0x98, e->radio_rxtx98);
	पूर्ण

	udelay(50);

	/* Calibration */
	b43_radio_mask(dev, R2059_RFPLL_MISC_EN, ~0x1);
	b43_radio_mask(dev, R2059_RFPLL_MISC_CAL_RESETN, ~0x4);
	b43_radio_set(dev, R2059_RFPLL_MISC_CAL_RESETN, 0x4);
	b43_radio_set(dev, R2059_RFPLL_MISC_EN, 0x1);

	udelay(300);
पूर्ण

/* Calibrate resistors in LPF of PLL? */
अटल व्योम b43_radio_2059_rcal(काष्ठा b43_wldev *dev)
अणु
	/* Enable */
	b43_radio_set(dev, R2059_C3 | R2059_RCAL_CONFIG, 0x1);
	usleep_range(10, 20);

	b43_radio_set(dev, R2059_C3 | 0x0BF, 0x1);
	b43_radio_maskset(dev, R2059_C3 | 0x19B, 0x3, 0x2);

	/* Start */
	b43_radio_set(dev, R2059_C3 | R2059_RCAL_CONFIG, 0x2);
	usleep_range(100, 200);

	/* Stop */
	b43_radio_mask(dev, R2059_C3 | R2059_RCAL_CONFIG, ~0x2);

	अगर (!b43_radio_रुको_value(dev, R2059_C3 | R2059_RCAL_STATUS, 1, 1, 100,
				  1000000))
		b43err(dev->wl, "Radio 0x2059 rcal timeout\n");

	/* Disable */
	b43_radio_mask(dev, R2059_C3 | R2059_RCAL_CONFIG, ~0x1);

	b43_radio_set(dev, 0xa, 0x60);
पूर्ण

/* Calibrate the पूर्णांकernal RC oscillator? */
अटल व्योम b43_radio_2057_rccal(काष्ठा b43_wldev *dev)
अणु
	अटल स्थिर u16 radio_values[3][2] = अणु
		अणु 0x61, 0xE9 पूर्ण, अणु 0x69, 0xD5 पूर्ण, अणु 0x73, 0x99 पूर्ण,
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++) अणु
		b43_radio_ग_लिखो(dev, R2059_RCCAL_MASTER, radio_values[i][0]);
		b43_radio_ग_लिखो(dev, R2059_RCCAL_X1, 0x6E);
		b43_radio_ग_लिखो(dev, R2059_RCCAL_TRC0, radio_values[i][1]);

		/* Start */
		b43_radio_ग_लिखो(dev, R2059_RCCAL_START_R1_Q1_P1, 0x55);

		/* Wait */
		अगर (!b43_radio_रुको_value(dev, R2059_RCCAL_DONE_OSCCAP, 2, 2,
					  500, 5000000))
			b43err(dev->wl, "Radio 0x2059 rccal timeout\n");

		/* Stop */
		b43_radio_ग_लिखो(dev, R2059_RCCAL_START_R1_Q1_P1, 0x15);
	पूर्ण

	b43_radio_mask(dev, R2059_RCCAL_MASTER, ~0x1);
पूर्ण

अटल व्योम b43_radio_2059_init_pre(काष्ठा b43_wldev *dev)
अणु
	b43_phy_mask(dev, B43_PHY_HT_RF_CTL_CMD, ~B43_PHY_HT_RF_CTL_CMD_CHIP0_PU);
	b43_phy_set(dev, B43_PHY_HT_RF_CTL_CMD, B43_PHY_HT_RF_CTL_CMD_FORCE);
	b43_phy_mask(dev, B43_PHY_HT_RF_CTL_CMD, ~B43_PHY_HT_RF_CTL_CMD_FORCE);
	b43_phy_set(dev, B43_PHY_HT_RF_CTL_CMD, B43_PHY_HT_RF_CTL_CMD_CHIP0_PU);
पूर्ण

अटल व्योम b43_radio_2059_init(काष्ठा b43_wldev *dev)
अणु
	अटल स्थिर u16 routing[] = अणु R2059_C1, R2059_C2, R2059_C3 पूर्ण;
	पूर्णांक i;

	/* Prepare (reset?) radio */
	b43_radio_2059_init_pre(dev);

	r2059_upload_inittअसल(dev);

	क्रम (i = 0; i < ARRAY_SIZE(routing); i++)
		b43_radio_set(dev, routing[i] | 0x146, 0x3);

	/* Post init starts below */

	b43_radio_set(dev, R2059_RFPLL_MISC_CAL_RESETN, 0x0078);
	b43_radio_set(dev, R2059_XTAL_CONFIG2, 0x0080);
	msleep(2);
	b43_radio_mask(dev, R2059_RFPLL_MISC_CAL_RESETN, ~0x0078);
	b43_radio_mask(dev, R2059_XTAL_CONFIG2, ~0x0080);

	अगर (1) अणु /* FIXME */
		b43_radio_2059_rcal(dev);
		b43_radio_2057_rccal(dev);
	पूर्ण

	b43_radio_mask(dev, R2059_RFPLL_MASTER, ~0x0008);
पूर्ण

/**************************************************
 * RF
 **************************************************/

अटल व्योम b43_phy_ht_क्रमce_rf_sequence(काष्ठा b43_wldev *dev, u16 rf_seq)
अणु
	u8 i;

	u16 save_seq_mode = b43_phy_पढ़ो(dev, B43_PHY_HT_RF_SEQ_MODE);
	b43_phy_set(dev, B43_PHY_HT_RF_SEQ_MODE, 0x3);

	b43_phy_set(dev, B43_PHY_HT_RF_SEQ_TRIG, rf_seq);
	क्रम (i = 0; i < 200; i++) अणु
		अगर (!(b43_phy_पढ़ो(dev, B43_PHY_HT_RF_SEQ_STATUS) & rf_seq)) अणु
			i = 0;
			अवरोध;
		पूर्ण
		msleep(1);
	पूर्ण
	अगर (i)
		b43err(dev->wl, "Forcing RF sequence timeout\n");

	b43_phy_ग_लिखो(dev, B43_PHY_HT_RF_SEQ_MODE, save_seq_mode);
पूर्ण

अटल व्योम b43_phy_ht_pa_override(काष्ठा b43_wldev *dev, bool enable)
अणु
	काष्ठा b43_phy_ht *htphy = dev->phy.ht;
	अटल स्थिर u16 regs[3] = अणु B43_PHY_HT_RF_CTL_INT_C1,
				     B43_PHY_HT_RF_CTL_INT_C2,
				     B43_PHY_HT_RF_CTL_INT_C3 पूर्ण;
	पूर्णांक i;

	अगर (enable) अणु
		क्रम (i = 0; i < 3; i++)
			b43_phy_ग_लिखो(dev, regs[i], htphy->rf_ctl_पूर्णांक_save[i]);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 3; i++)
			htphy->rf_ctl_पूर्णांक_save[i] = b43_phy_पढ़ो(dev, regs[i]);
		/* TODO: Does 5GHz band use dअगरferent value (not 0x0400)? */
		क्रम (i = 0; i < 3; i++)
			b43_phy_ग_लिखो(dev, regs[i], 0x0400);
	पूर्ण
पूर्ण

/**************************************************
 * Various PHY ops
 **************************************************/

अटल u16 b43_phy_ht_classअगरier(काष्ठा b43_wldev *dev, u16 mask, u16 val)
अणु
	u16 पंचांगp;
	u16 allowed = B43_PHY_HT_CLASS_CTL_CCK_EN |
		      B43_PHY_HT_CLASS_CTL_OFDM_EN |
		      B43_PHY_HT_CLASS_CTL_WAITED_EN;

	पंचांगp = b43_phy_पढ़ो(dev, B43_PHY_HT_CLASS_CTL);
	पंचांगp &= allowed;
	पंचांगp &= ~mask;
	पंचांगp |= (val & mask);
	b43_phy_maskset(dev, B43_PHY_HT_CLASS_CTL, ~allowed, पंचांगp);

	वापस पंचांगp;
पूर्ण

अटल व्योम b43_phy_ht_reset_cca(काष्ठा b43_wldev *dev)
अणु
	u16 bbcfg;

	b43_phy_क्रमce_घड़ी(dev, true);
	bbcfg = b43_phy_पढ़ो(dev, B43_PHY_HT_BBCFG);
	b43_phy_ग_लिखो(dev, B43_PHY_HT_BBCFG, bbcfg | B43_PHY_HT_BBCFG_RSTCCA);
	udelay(1);
	b43_phy_ग_लिखो(dev, B43_PHY_HT_BBCFG, bbcfg & ~B43_PHY_HT_BBCFG_RSTCCA);
	b43_phy_क्रमce_घड़ी(dev, false);

	b43_phy_ht_क्रमce_rf_sequence(dev, B43_PHY_HT_RF_SEQ_TRIG_RST2RX);
पूर्ण

अटल व्योम b43_phy_ht_zero_extg(काष्ठा b43_wldev *dev)
अणु
	u8 i, j;
	अटल स्थिर u16 base[] = अणु 0x40, 0x60, 0x80 पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(base); i++) अणु
		क्रम (j = 0; j < 4; j++)
			b43_phy_ग_लिखो(dev, B43_PHY_EXTG(base[i] + j), 0);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(base); i++)
		b43_phy_ग_लिखो(dev, B43_PHY_EXTG(base[i] + 0xc), 0);
पूर्ण

/* Some unknown AFE (Analog Frondned) op */
अटल व्योम b43_phy_ht_afe_unk1(काष्ठा b43_wldev *dev)
अणु
	u8 i;

	अटल स्थिर u16 ctl_regs[3][2] = अणु
		अणु B43_PHY_HT_AFE_C1_OVER, B43_PHY_HT_AFE_C1 पूर्ण,
		अणु B43_PHY_HT_AFE_C2_OVER, B43_PHY_HT_AFE_C2 पूर्ण,
		अणु B43_PHY_HT_AFE_C3_OVER, B43_PHY_HT_AFE_C3पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < 3; i++) अणु
		/* TODO: verअगरy masks&sets */
		b43_phy_set(dev, ctl_regs[i][1], 0x4);
		b43_phy_set(dev, ctl_regs[i][0], 0x4);
		b43_phy_mask(dev, ctl_regs[i][1], ~0x1);
		b43_phy_set(dev, ctl_regs[i][0], 0x1);
		b43_httab_ग_लिखो(dev, B43_HTTAB16(8, 5 + (i * 0x10)), 0);
		b43_phy_mask(dev, ctl_regs[i][0], ~0x4);
	पूर्ण
पूर्ण

अटल व्योम b43_phy_ht_पढ़ो_clip_detection(काष्ठा b43_wldev *dev, u16 *clip_st)
अणु
	clip_st[0] = b43_phy_पढ़ो(dev, B43_PHY_HT_C1_CLIP1THRES);
	clip_st[1] = b43_phy_पढ़ो(dev, B43_PHY_HT_C2_CLIP1THRES);
	clip_st[2] = b43_phy_पढ़ो(dev, B43_PHY_HT_C3_CLIP1THRES);
पूर्ण

अटल व्योम b43_phy_ht_bphy_init(काष्ठा b43_wldev *dev)
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

अटल व्योम b43_phy_ht_bphy_reset(काष्ठा b43_wldev *dev, bool reset)
अणु
	u16 पंचांगp;

	पंचांगp = b43_पढ़ो16(dev, B43_MMIO_PSM_PHY_HDR);
	b43_ग_लिखो16(dev, B43_MMIO_PSM_PHY_HDR,
		    पंचांगp | B43_PSM_HDR_MAC_PHY_FORCE_CLK);

	/* Put BPHY in or take it out of the reset */
	अगर (reset)
		b43_phy_set(dev, B43_PHY_B_BBCFG,
			    B43_PHY_B_BBCFG_RSTCCA | B43_PHY_B_BBCFG_RSTRX);
	अन्यथा
		b43_phy_mask(dev, B43_PHY_B_BBCFG,
			     (u16)~(B43_PHY_B_BBCFG_RSTCCA |
				    B43_PHY_B_BBCFG_RSTRX));

	b43_ग_लिखो16(dev, B43_MMIO_PSM_PHY_HDR, पंचांगp);
पूर्ण

/**************************************************
 * Samples
 **************************************************/

अटल व्योम b43_phy_ht_stop_playback(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_ht *phy_ht = dev->phy.ht;
	u16 पंचांगp;
	पूर्णांक i;

	पंचांगp = b43_phy_पढ़ो(dev, B43_PHY_HT_SAMP_STAT);
	अगर (पंचांगp & 0x1)
		b43_phy_set(dev, B43_PHY_HT_SAMP_CMD, B43_PHY_HT_SAMP_CMD_STOP);
	अन्यथा अगर (पंचांगp & 0x2)
		b43_phy_mask(dev, B43_PHY_HT_IQLOCAL_CMDGCTL, 0x7FFF);

	b43_phy_mask(dev, B43_PHY_HT_SAMP_CMD, ~0x0004);

	क्रम (i = 0; i < 3; i++) अणु
		अगर (phy_ht->bb_mult_save[i] >= 0) अणु
			b43_httab_ग_लिखो(dev, B43_HTTAB16(13, 0x63 + i * 4),
					phy_ht->bb_mult_save[i]);
			b43_httab_ग_लिखो(dev, B43_HTTAB16(13, 0x67 + i * 4),
					phy_ht->bb_mult_save[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल u16 b43_phy_ht_load_samples(काष्ठा b43_wldev *dev)
अणु
	पूर्णांक i;
	u16 len = 20 << 3;

	b43_phy_ग_लिखो(dev, B43_PHY_HT_TABLE_ADDR, 0x4400);

	क्रम (i = 0; i < len; i++) अणु
		b43_phy_ग_लिखो(dev, B43_PHY_HT_TABLE_DATAHI, 0);
		b43_phy_ग_लिखो(dev, B43_PHY_HT_TABLE_DATALO, 0);
	पूर्ण

	वापस len;
पूर्ण

अटल व्योम b43_phy_ht_run_samples(काष्ठा b43_wldev *dev, u16 samps, u16 loops,
				   u16 रुको)
अणु
	काष्ठा b43_phy_ht *phy_ht = dev->phy.ht;
	u16 save_seq_mode;
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++) अणु
		अगर (phy_ht->bb_mult_save[i] < 0)
			phy_ht->bb_mult_save[i] = b43_httab_पढ़ो(dev, B43_HTTAB16(13, 0x63 + i * 4));
	पूर्ण

	b43_phy_ग_लिखो(dev, B43_PHY_HT_SAMP_DEP_CNT, samps - 1);
	अगर (loops != 0xFFFF)
		loops--;
	b43_phy_ग_लिखो(dev, B43_PHY_HT_SAMP_LOOP_CNT, loops);
	b43_phy_ग_लिखो(dev, B43_PHY_HT_SAMP_WAIT_CNT, रुको);

	save_seq_mode = b43_phy_पढ़ो(dev, B43_PHY_HT_RF_SEQ_MODE);
	b43_phy_set(dev, B43_PHY_HT_RF_SEQ_MODE,
		    B43_PHY_HT_RF_SEQ_MODE_CA_OVER);

	/* TODO: find out mask bits! Do we need more function arguments? */
	b43_phy_mask(dev, B43_PHY_HT_SAMP_CMD, ~0);
	b43_phy_mask(dev, B43_PHY_HT_SAMP_CMD, ~0);
	b43_phy_mask(dev, B43_PHY_HT_IQLOCAL_CMDGCTL, ~0);
	b43_phy_set(dev, B43_PHY_HT_SAMP_CMD, 0x1);

	क्रम (i = 0; i < 100; i++) अणु
		अगर (!(b43_phy_पढ़ो(dev, B43_PHY_HT_RF_SEQ_STATUS) & 1)) अणु
			i = 0;
			अवरोध;
		पूर्ण
		udelay(10);
	पूर्ण
	अगर (i)
		b43err(dev->wl, "run samples timeout\n");

	b43_phy_ग_लिखो(dev, B43_PHY_HT_RF_SEQ_MODE, save_seq_mode);
पूर्ण

अटल व्योम b43_phy_ht_tx_tone(काष्ठा b43_wldev *dev)
अणु
	u16 samp;

	samp = b43_phy_ht_load_samples(dev);
	b43_phy_ht_run_samples(dev, samp, 0xFFFF, 0);
पूर्ण

/**************************************************
 * RSSI
 **************************************************/

अटल व्योम b43_phy_ht_rssi_select(काष्ठा b43_wldev *dev, u8 core_sel,
				   क्रमागत ht_rssi_type rssi_type)
अणु
	अटल स्थिर u16 ctl_regs[3][2] = अणु
		अणु B43_PHY_HT_AFE_C1, B43_PHY_HT_AFE_C1_OVER, पूर्ण,
		अणु B43_PHY_HT_AFE_C2, B43_PHY_HT_AFE_C2_OVER, पूर्ण,
		अणु B43_PHY_HT_AFE_C3, B43_PHY_HT_AFE_C3_OVER, पूर्ण,
	पूर्ण;
	अटल स्थिर u16 radio_r[] = अणु R2059_C1, R2059_C2, R2059_C3, पूर्ण;
	पूर्णांक core;

	अगर (core_sel == 0) अणु
		b43err(dev->wl, "RSSI selection for core off not implemented yet\n");
	पूर्ण अन्यथा अणु
		क्रम (core = 0; core < 3; core++) अणु
			/* Check अगर caller requested a one specअगरic core */
			अगर ((core_sel == 1 && core != 0) ||
			    (core_sel == 2 && core != 1) ||
			    (core_sel == 3 && core != 2))
				जारी;

			चयन (rssi_type) अणु
			हाल HT_RSSI_TSSI_2G:
				b43_phy_set(dev, ctl_regs[core][0], 0x3 << 8);
				b43_phy_set(dev, ctl_regs[core][0], 0x3 << 10);
				b43_phy_set(dev, ctl_regs[core][1], 0x1 << 9);
				b43_phy_set(dev, ctl_regs[core][1], 0x1 << 10);

				b43_radio_set(dev, R2059_C3 | 0xbf, 0x1);
				b43_radio_ग_लिखो(dev, radio_r[core] | 0x159,
						0x11);
				अवरोध;
			शेष:
				b43err(dev->wl, "RSSI selection for type %d not implemented yet\n",
				       rssi_type);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम b43_phy_ht_poll_rssi(काष्ठा b43_wldev *dev, क्रमागत ht_rssi_type type,
				 s32 *buf, u8 nsamp)
अणु
	u16 phy_regs_values[12];
	अटल स्थिर u16 phy_regs_to_save[] = अणु
		B43_PHY_HT_AFE_C1, B43_PHY_HT_AFE_C1_OVER,
		0x848, 0x841,
		B43_PHY_HT_AFE_C2, B43_PHY_HT_AFE_C2_OVER,
		0x868, 0x861,
		B43_PHY_HT_AFE_C3, B43_PHY_HT_AFE_C3_OVER,
		0x888, 0x881,
	पूर्ण;
	u16 पंचांगp[3];
	पूर्णांक i;

	क्रम (i = 0; i < 12; i++)
		phy_regs_values[i] = b43_phy_पढ़ो(dev, phy_regs_to_save[i]);

	b43_phy_ht_rssi_select(dev, 5, type);

	क्रम (i = 0; i < 6; i++)
		buf[i] = 0;

	क्रम (i = 0; i < nsamp; i++) अणु
		पंचांगp[0] = b43_phy_पढ़ो(dev, B43_PHY_HT_RSSI_C1);
		पंचांगp[1] = b43_phy_पढ़ो(dev, B43_PHY_HT_RSSI_C2);
		पंचांगp[2] = b43_phy_पढ़ो(dev, B43_PHY_HT_RSSI_C3);

		buf[0] += ((s8)((पंचांगp[0] & 0x3F) << 2)) >> 2;
		buf[1] += ((s8)(((पंचांगp[0] >> 8) & 0x3F) << 2)) >> 2;
		buf[2] += ((s8)((पंचांगp[1] & 0x3F) << 2)) >> 2;
		buf[3] += ((s8)(((पंचांगp[1] >> 8) & 0x3F) << 2)) >> 2;
		buf[4] += ((s8)((पंचांगp[2] & 0x3F) << 2)) >> 2;
		buf[5] += ((s8)(((पंचांगp[2] >> 8) & 0x3F) << 2)) >> 2;
	पूर्ण

	क्रम (i = 0; i < 12; i++)
		b43_phy_ग_लिखो(dev, phy_regs_to_save[i], phy_regs_values[i]);
पूर्ण

/**************************************************
 * Tx/Rx
 **************************************************/

अटल व्योम b43_phy_ht_tx_घातer_fix(काष्ठा b43_wldev *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++) अणु
		u16 mask;
		u32 पंचांगp = b43_httab_पढ़ो(dev, B43_HTTAB32(26, 0xE8));

		अगर (0) /* FIXME */
			mask = 0x2 << (i * 4);
		अन्यथा
			mask = 0;
		b43_phy_mask(dev, B43_PHY_EXTG(0x108), mask);

		b43_httab_ग_लिखो(dev, B43_HTTAB16(7, 0x110 + i), पंचांगp >> 16);
		b43_httab_ग_लिखो(dev, B43_HTTAB8(13, 0x63 + (i * 4)),
				पंचांगp & 0xFF);
		b43_httab_ग_लिखो(dev, B43_HTTAB8(13, 0x73 + (i * 4)),
				पंचांगp & 0xFF);
	पूर्ण
पूर्ण

अटल व्योम b43_phy_ht_tx_घातer_ctl(काष्ठा b43_wldev *dev, bool enable)
अणु
	काष्ठा b43_phy_ht *phy_ht = dev->phy.ht;
	u16 en_bits = B43_PHY_HT_TXPCTL_CMD_C1_COEFF |
		      B43_PHY_HT_TXPCTL_CMD_C1_HWPCTLEN |
		      B43_PHY_HT_TXPCTL_CMD_C1_PCTLEN;
	अटल स्थिर u16 cmd_regs[3] = अणु B43_PHY_HT_TXPCTL_CMD_C1,
					 B43_PHY_HT_TXPCTL_CMD_C2,
					 B43_PHY_HT_TXPCTL_CMD_C3 पूर्ण;
	अटल स्थिर u16 status_regs[3] = अणु B43_PHY_HT_TX_PCTL_STATUS_C1,
					    B43_PHY_HT_TX_PCTL_STATUS_C2,
					    B43_PHY_HT_TX_PCTL_STATUS_C3 पूर्ण;
	पूर्णांक i;

	अगर (!enable) अणु
		अगर (b43_phy_पढ़ो(dev, B43_PHY_HT_TXPCTL_CMD_C1) & en_bits) अणु
			/* We disable enabled TX pwr ctl, save it's state */
			क्रम (i = 0; i < 3; i++)
				phy_ht->tx_pwr_idx[i] =
					b43_phy_पढ़ो(dev, status_regs[i]);
		पूर्ण
		b43_phy_mask(dev, B43_PHY_HT_TXPCTL_CMD_C1, ~en_bits);
	पूर्ण अन्यथा अणु
		b43_phy_set(dev, B43_PHY_HT_TXPCTL_CMD_C1, en_bits);

		अगर (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) अणु
			क्रम (i = 0; i < 3; i++)
				b43_phy_ग_लिखो(dev, cmd_regs[i], 0x32);
		पूर्ण

		क्रम (i = 0; i < 3; i++)
			अगर (phy_ht->tx_pwr_idx[i] <=
			    B43_PHY_HT_TXPCTL_CMD_C1_INIT)
				b43_phy_ग_लिखो(dev, cmd_regs[i],
					      phy_ht->tx_pwr_idx[i]);
	पूर्ण

	phy_ht->tx_pwr_ctl = enable;
पूर्ण

अटल व्योम b43_phy_ht_tx_घातer_ctl_idle_tssi(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_ht *phy_ht = dev->phy.ht;
	अटल स्थिर u16 base[] = अणु 0x840, 0x860, 0x880 पूर्ण;
	u16 save_regs[3][3];
	s32 rssi_buf[6];
	पूर्णांक core;

	क्रम (core = 0; core < 3; core++) अणु
		save_regs[core][1] = b43_phy_पढ़ो(dev, base[core] + 6);
		save_regs[core][2] = b43_phy_पढ़ो(dev, base[core] + 7);
		save_regs[core][0] = b43_phy_पढ़ो(dev, base[core] + 0);

		b43_phy_ग_लिखो(dev, base[core] + 6, 0);
		b43_phy_mask(dev, base[core] + 7, ~0xF); /* 0xF? Or just 0x6? */
		b43_phy_set(dev, base[core] + 0, 0x0400);
		b43_phy_set(dev, base[core] + 0, 0x1000);
	पूर्ण

	b43_phy_ht_tx_tone(dev);
	udelay(20);
	b43_phy_ht_poll_rssi(dev, HT_RSSI_TSSI_2G, rssi_buf, 1);
	b43_phy_ht_stop_playback(dev);
	b43_phy_ht_reset_cca(dev);

	phy_ht->idle_tssi[0] = rssi_buf[0] & 0xff;
	phy_ht->idle_tssi[1] = rssi_buf[2] & 0xff;
	phy_ht->idle_tssi[2] = rssi_buf[4] & 0xff;

	क्रम (core = 0; core < 3; core++) अणु
		b43_phy_ग_लिखो(dev, base[core] + 0, save_regs[core][0]);
		b43_phy_ग_लिखो(dev, base[core] + 6, save_regs[core][1]);
		b43_phy_ग_लिखो(dev, base[core] + 7, save_regs[core][2]);
	पूर्ण
पूर्ण

अटल व्योम b43_phy_ht_tssi_setup(काष्ठा b43_wldev *dev)
अणु
	अटल स्थिर u16 routing[] = अणु R2059_C1, R2059_C2, R2059_C3, पूर्ण;
	पूर्णांक core;

	/* 0x159 is probably TX_SSI_MUX or TSSIG (by comparing to N-PHY) */
	क्रम (core = 0; core < 3; core++) अणु
		b43_radio_set(dev, 0x8bf, 0x1);
		b43_radio_ग_लिखो(dev, routing[core] | 0x0159, 0x0011);
	पूर्ण
पूर्ण

अटल व्योम b43_phy_ht_tx_घातer_ctl_setup(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_ht *phy_ht = dev->phy.ht;
	काष्ठा ssb_sprom *sprom = dev->dev->bus_sprom;

	u8 *idle = phy_ht->idle_tssi;
	u8 target[3];
	s16 a1[3], b0[3], b1[3];

	u16 freq = dev->phy.chandef->chan->center_freq;
	पूर्णांक i, c;

	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
		क्रम (c = 0; c < 3; c++) अणु
			target[c] = sprom->core_pwr_info[c].maxpwr_2g;
			a1[c] = sprom->core_pwr_info[c].pa_2g[0];
			b0[c] = sprom->core_pwr_info[c].pa_2g[1];
			b1[c] = sprom->core_pwr_info[c].pa_2g[2];
		पूर्ण
	पूर्ण अन्यथा अगर (freq >= 4900 && freq < 5100) अणु
		क्रम (c = 0; c < 3; c++) अणु
			target[c] = sprom->core_pwr_info[c].maxpwr_5gl;
			a1[c] = sprom->core_pwr_info[c].pa_5gl[0];
			b0[c] = sprom->core_pwr_info[c].pa_5gl[1];
			b1[c] = sprom->core_pwr_info[c].pa_5gl[2];
		पूर्ण
	पूर्ण अन्यथा अगर (freq >= 5100 && freq < 5500) अणु
		क्रम (c = 0; c < 3; c++) अणु
			target[c] = sprom->core_pwr_info[c].maxpwr_5g;
			a1[c] = sprom->core_pwr_info[c].pa_5g[0];
			b0[c] = sprom->core_pwr_info[c].pa_5g[1];
			b1[c] = sprom->core_pwr_info[c].pa_5g[2];
		पूर्ण
	पूर्ण अन्यथा अगर (freq >= 5500) अणु
		क्रम (c = 0; c < 3; c++) अणु
			target[c] = sprom->core_pwr_info[c].maxpwr_5gh;
			a1[c] = sprom->core_pwr_info[c].pa_5gh[0];
			b0[c] = sprom->core_pwr_info[c].pa_5gh[1];
			b1[c] = sprom->core_pwr_info[c].pa_5gh[2];
		पूर्ण
	पूर्ण अन्यथा अणु
		target[0] = target[1] = target[2] = 52;
		a1[0] = a1[1] = a1[2] = -424;
		b0[0] = b0[1] = b0[2] = 5612;
		b1[0] = b1[1] = b1[2] = -1393;
	पूर्ण

	b43_phy_set(dev, B43_PHY_HT_TSSIMODE, B43_PHY_HT_TSSIMODE_EN);
	b43_phy_mask(dev, B43_PHY_HT_TXPCTL_CMD_C1,
		     ~B43_PHY_HT_TXPCTL_CMD_C1_PCTLEN & 0xFFFF);

	/* TODO: Does it depend on sprom->fem.ghz2.tssipos? */
	b43_phy_set(dev, B43_PHY_HT_TXPCTL_IDLE_TSSI, 0x4000);

	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_CMD_C1,
			~B43_PHY_HT_TXPCTL_CMD_C1_INIT, 0x19);
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_CMD_C2,
			~B43_PHY_HT_TXPCTL_CMD_C2_INIT, 0x19);
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_CMD_C3,
			~B43_PHY_HT_TXPCTL_CMD_C3_INIT, 0x19);

	b43_phy_set(dev, B43_PHY_HT_TXPCTL_IDLE_TSSI,
		    B43_PHY_HT_TXPCTL_IDLE_TSSI_BINF);

	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_IDLE_TSSI,
			~B43_PHY_HT_TXPCTL_IDLE_TSSI_C1,
			idle[0] << B43_PHY_HT_TXPCTL_IDLE_TSSI_C1_SHIFT);
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_IDLE_TSSI,
			~B43_PHY_HT_TXPCTL_IDLE_TSSI_C2,
			idle[1] << B43_PHY_HT_TXPCTL_IDLE_TSSI_C2_SHIFT);
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_IDLE_TSSI2,
			~B43_PHY_HT_TXPCTL_IDLE_TSSI2_C3,
			idle[2] << B43_PHY_HT_TXPCTL_IDLE_TSSI2_C3_SHIFT);

	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_N, ~B43_PHY_HT_TXPCTL_N_TSSID,
			0xf0);
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_N, ~B43_PHY_HT_TXPCTL_N_NPTIL2,
			0x3 << B43_PHY_HT_TXPCTL_N_NPTIL2_SHIFT);
#अगर 0
	/* TODO: what to mask/set? */
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_CMD_C1, 0x800, 0)
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_CMD_C1, 0x400, 0)
#पूर्ण_अगर

	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_TARG_PWR,
			~B43_PHY_HT_TXPCTL_TARG_PWR_C1,
			target[0] << B43_PHY_HT_TXPCTL_TARG_PWR_C1_SHIFT);
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_TARG_PWR,
			~B43_PHY_HT_TXPCTL_TARG_PWR_C2 & 0xFFFF,
			target[1] << B43_PHY_HT_TXPCTL_TARG_PWR_C2_SHIFT);
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_TARG_PWR2,
			~B43_PHY_HT_TXPCTL_TARG_PWR2_C3,
			target[2] << B43_PHY_HT_TXPCTL_TARG_PWR2_C3_SHIFT);

	क्रम (c = 0; c < 3; c++) अणु
		s32 num, den, pwr;
		u32 regval[64];

		क्रम (i = 0; i < 64; i++) अणु
			num = 8 * (16 * b0[c] + b1[c] * i);
			den = 32768 + a1[c] * i;
			pwr = max((4 * num + den / 2) / den, -8);
			regval[i] = pwr;
		पूर्ण
		b43_httab_ग_लिखो_bulk(dev, B43_HTTAB16(26 + c, 0), 64, regval);
	पूर्ण
पूर्ण

/**************************************************
 * Channel चयनing ops.
 **************************************************/

अटल व्योम b43_phy_ht_spur_aव्योम(काष्ठा b43_wldev *dev,
				  काष्ठा ieee80211_channel *new_channel)
अणु
	काष्ठा bcma_device *core = dev->dev->bdev;
	पूर्णांक spuraव्योम = 0;

	/* Check क्रम 13 and 14 is just a guess, we करोn't have enough logs. */
	अगर (new_channel->hw_value == 13 || new_channel->hw_value == 14)
		spuraव्योम = 1;
	bcma_core_pll_ctl(core, B43_BCMA_CLKCTLST_PHY_PLL_REQ, 0, false);
	bcma_pmu_spuraव्योम_pllupdate(&core->bus->drv_cc, spuraव्योम);
	bcma_core_pll_ctl(core,
			  B43_BCMA_CLKCTLST_80211_PLL_REQ |
			  B43_BCMA_CLKCTLST_PHY_PLL_REQ,
			  B43_BCMA_CLKCTLST_80211_PLL_ST |
			  B43_BCMA_CLKCTLST_PHY_PLL_ST, false);

	b43_mac_चयन_freq(dev, spuraव्योम);

	b43_wireless_core_phy_pll_reset(dev);

	अगर (spuraव्योम)
		b43_phy_set(dev, B43_PHY_HT_BBCFG, B43_PHY_HT_BBCFG_RSTRX);
	अन्यथा
		b43_phy_mask(dev, B43_PHY_HT_BBCFG,
				~B43_PHY_HT_BBCFG_RSTRX & 0xFFFF);

	b43_phy_ht_reset_cca(dev);
पूर्ण

अटल व्योम b43_phy_ht_channel_setup(काष्ठा b43_wldev *dev,
				स्थिर काष्ठा b43_phy_ht_channeltab_e_phy *e,
				काष्ठा ieee80211_channel *new_channel)
अणु
	अगर (new_channel->band == NL80211_BAND_5GHZ) अणु
		/* Switch to 2 GHz क्रम a moment to access B-PHY regs */
		b43_phy_mask(dev, B43_PHY_HT_BANDCTL, ~B43_PHY_HT_BANDCTL_5GHZ);

		b43_phy_ht_bphy_reset(dev, true);

		/* Switch to 5 GHz */
		b43_phy_set(dev, B43_PHY_HT_BANDCTL, B43_PHY_HT_BANDCTL_5GHZ);
	पूर्ण अन्यथा अणु
		/* Switch to 2 GHz */
		b43_phy_mask(dev, B43_PHY_HT_BANDCTL, ~B43_PHY_HT_BANDCTL_5GHZ);

		b43_phy_ht_bphy_reset(dev, false);
	पूर्ण

	b43_phy_ग_लिखो(dev, B43_PHY_HT_BW1, e->bw1);
	b43_phy_ग_लिखो(dev, B43_PHY_HT_BW2, e->bw2);
	b43_phy_ग_लिखो(dev, B43_PHY_HT_BW3, e->bw3);
	b43_phy_ग_लिखो(dev, B43_PHY_HT_BW4, e->bw4);
	b43_phy_ग_लिखो(dev, B43_PHY_HT_BW5, e->bw5);
	b43_phy_ग_लिखो(dev, B43_PHY_HT_BW6, e->bw6);

	अगर (new_channel->hw_value == 14) अणु
		b43_phy_ht_classअगरier(dev, B43_PHY_HT_CLASS_CTL_OFDM_EN, 0);
		b43_phy_set(dev, B43_PHY_HT_TEST, 0x0800);
	पूर्ण अन्यथा अणु
		b43_phy_ht_classअगरier(dev, B43_PHY_HT_CLASS_CTL_OFDM_EN,
				      B43_PHY_HT_CLASS_CTL_OFDM_EN);
		अगर (new_channel->band == NL80211_BAND_2GHZ)
			b43_phy_mask(dev, B43_PHY_HT_TEST, ~0x840);
	पूर्ण

	अगर (1) /* TODO: On N it's क्रम early devices only, what about HT? */
		b43_phy_ht_tx_घातer_fix(dev);

	b43_phy_ht_spur_aव्योम(dev, new_channel);

	b43_phy_ग_लिखो(dev, 0x017e, 0x3830);
पूर्ण

अटल पूर्णांक b43_phy_ht_set_channel(काष्ठा b43_wldev *dev,
				  काष्ठा ieee80211_channel *channel,
				  क्रमागत nl80211_channel_type channel_type)
अणु
	काष्ठा b43_phy *phy = &dev->phy;

	स्थिर काष्ठा b43_phy_ht_channeltab_e_radio2059 *chent_r2059 = शून्य;

	अगर (phy->radio_ver == 0x2059) अणु
		chent_r2059 = b43_phy_ht_get_channeltab_e_r2059(dev,
							channel->center_freq);
		अगर (!chent_r2059)
			वापस -ESRCH;
	पूर्ण अन्यथा अणु
		वापस -ESRCH;
	पूर्ण

	/* TODO: In हाल of N-PHY some bandwidth चयनing goes here */

	अगर (phy->radio_ver == 0x2059) अणु
		b43_radio_2059_channel_setup(dev, chent_r2059);
		b43_phy_ht_channel_setup(dev, &(chent_r2059->phy_regs),
					 channel);
	पूर्ण अन्यथा अणु
		वापस -ESRCH;
	पूर्ण

	वापस 0;
पूर्ण

/**************************************************
 * Basic PHY ops.
 **************************************************/

अटल पूर्णांक b43_phy_ht_op_allocate(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_ht *phy_ht;

	phy_ht = kzalloc(माप(*phy_ht), GFP_KERNEL);
	अगर (!phy_ht)
		वापस -ENOMEM;
	dev->phy.ht = phy_ht;

	वापस 0;
पूर्ण

अटल व्योम b43_phy_ht_op_prepare_काष्ठाs(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_ht *phy_ht = phy->ht;
	पूर्णांक i;

	स_रखो(phy_ht, 0, माप(*phy_ht));

	phy_ht->tx_pwr_ctl = true;
	क्रम (i = 0; i < 3; i++)
		phy_ht->tx_pwr_idx[i] = B43_PHY_HT_TXPCTL_CMD_C1_INIT + 1;

	क्रम (i = 0; i < 3; i++)
		phy_ht->bb_mult_save[i] = -1;
पूर्ण

अटल पूर्णांक b43_phy_ht_op_init(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_ht *phy_ht = dev->phy.ht;
	u16 पंचांगp;
	u16 clip_state[3];
	bool saved_tx_pwr_ctl;

	अगर (dev->dev->bus_type != B43_BUS_BCMA) अणु
		b43err(dev->wl, "HT-PHY is supported only on BCMA bus!\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	b43_phy_ht_tables_init(dev);

	b43_phy_mask(dev, 0x0be, ~0x2);
	b43_phy_set(dev, 0x23f, 0x7ff);
	b43_phy_set(dev, 0x240, 0x7ff);
	b43_phy_set(dev, 0x241, 0x7ff);

	b43_phy_ht_zero_extg(dev);

	b43_phy_mask(dev, B43_PHY_EXTG(0), ~0x3);

	b43_phy_ग_लिखो(dev, B43_PHY_HT_AFE_C1_OVER, 0);
	b43_phy_ग_लिखो(dev, B43_PHY_HT_AFE_C2_OVER, 0);
	b43_phy_ग_लिखो(dev, B43_PHY_HT_AFE_C3_OVER, 0);

	b43_phy_ग_लिखो(dev, B43_PHY_EXTG(0x103), 0x20);
	b43_phy_ग_लिखो(dev, B43_PHY_EXTG(0x101), 0x20);
	b43_phy_ग_लिखो(dev, 0x20d, 0xb8);
	b43_phy_ग_लिखो(dev, B43_PHY_EXTG(0x14f), 0xc8);
	b43_phy_ग_लिखो(dev, 0x70, 0x50);
	b43_phy_ग_लिखो(dev, 0x1ff, 0x30);

	अगर (b43_current_band(dev->wl) == NL80211_BAND_5GHZ)
		b43_phy_ht_classअगरier(dev, B43_PHY_HT_CLASS_CTL_CCK_EN, 0);
	अन्यथा
		b43_phy_ht_classअगरier(dev, B43_PHY_HT_CLASS_CTL_CCK_EN,
				      B43_PHY_HT_CLASS_CTL_CCK_EN);

	b43_phy_set(dev, 0xb1, 0x91);
	b43_phy_ग_लिखो(dev, 0x32f, 0x0003);
	b43_phy_ग_लिखो(dev, 0x077, 0x0010);
	b43_phy_ग_लिखो(dev, 0x0b4, 0x0258);
	b43_phy_mask(dev, 0x17e, ~0x4000);

	b43_phy_ग_लिखो(dev, 0x0b9, 0x0072);

	b43_httab_ग_लिखो_few(dev, B43_HTTAB16(7, 0x14e), 2, 0x010f, 0x010f);
	b43_httab_ग_लिखो_few(dev, B43_HTTAB16(7, 0x15e), 2, 0x010f, 0x010f);
	b43_httab_ग_लिखो_few(dev, B43_HTTAB16(7, 0x16e), 2, 0x010f, 0x010f);

	b43_phy_ht_afe_unk1(dev);

	b43_httab_ग_लिखो_few(dev, B43_HTTAB16(7, 0x130), 9, 0x777, 0x111, 0x111,
			    0x777, 0x111, 0x111, 0x777, 0x111, 0x111);

	b43_httab_ग_लिखो(dev, B43_HTTAB16(7, 0x120), 0x0777);
	b43_httab_ग_लिखो(dev, B43_HTTAB16(7, 0x124), 0x0777);

	b43_httab_ग_लिखो(dev, B43_HTTAB16(8, 0x00), 0x02);
	b43_httab_ग_लिखो(dev, B43_HTTAB16(8, 0x10), 0x02);
	b43_httab_ग_लिखो(dev, B43_HTTAB16(8, 0x20), 0x02);

	b43_httab_ग_लिखो_few(dev, B43_HTTAB16(8, 0x08), 4,
			    0x8e, 0x96, 0x96, 0x96);
	b43_httab_ग_लिखो_few(dev, B43_HTTAB16(8, 0x18), 4,
			    0x8f, 0x9f, 0x9f, 0x9f);
	b43_httab_ग_लिखो_few(dev, B43_HTTAB16(8, 0x28), 4,
			    0x8f, 0x9f, 0x9f, 0x9f);

	b43_httab_ग_लिखो_few(dev, B43_HTTAB16(8, 0x0c), 4, 0x2, 0x2, 0x2, 0x2);
	b43_httab_ग_लिखो_few(dev, B43_HTTAB16(8, 0x1c), 4, 0x2, 0x2, 0x2, 0x2);
	b43_httab_ग_लिखो_few(dev, B43_HTTAB16(8, 0x2c), 4, 0x2, 0x2, 0x2, 0x2);

	b43_phy_maskset(dev, 0x0280, 0xff00, 0x3e);
	b43_phy_maskset(dev, 0x0283, 0xff00, 0x3e);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x0141), 0xff00, 0x46);
	b43_phy_maskset(dev, 0x0283, 0xff00, 0x40);

	b43_httab_ग_लिखो_few(dev, B43_HTTAB16(00, 0x8), 4,
			    0x09, 0x0e, 0x13, 0x18);
	b43_httab_ग_लिखो_few(dev, B43_HTTAB16(01, 0x8), 4,
			    0x09, 0x0e, 0x13, 0x18);
	/* TODO: Did wl mean 2 instead of 40? */
	b43_httab_ग_लिखो_few(dev, B43_HTTAB16(40, 0x8), 4,
			    0x09, 0x0e, 0x13, 0x18);

	b43_phy_maskset(dev, B43_PHY_OFDM(0x24), 0x3f, 0xd);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x64), 0x3f, 0xd);
	b43_phy_maskset(dev, B43_PHY_OFDM(0xa4), 0x3f, 0xd);

	b43_phy_set(dev, B43_PHY_EXTG(0x060), 0x1);
	b43_phy_set(dev, B43_PHY_EXTG(0x064), 0x1);
	b43_phy_set(dev, B43_PHY_EXTG(0x080), 0x1);
	b43_phy_set(dev, B43_PHY_EXTG(0x084), 0x1);

	/* Copy some tables entries */
	पंचांगp = b43_httab_पढ़ो(dev, B43_HTTAB16(7, 0x144));
	b43_httab_ग_लिखो(dev, B43_HTTAB16(7, 0x14a), पंचांगp);
	पंचांगp = b43_httab_पढ़ो(dev, B43_HTTAB16(7, 0x154));
	b43_httab_ग_लिखो(dev, B43_HTTAB16(7, 0x15a), पंचांगp);
	पंचांगp = b43_httab_पढ़ो(dev, B43_HTTAB16(7, 0x164));
	b43_httab_ग_लिखो(dev, B43_HTTAB16(7, 0x16a), पंचांगp);

	/* Reset CCA */
	b43_phy_क्रमce_घड़ी(dev, true);
	पंचांगp = b43_phy_पढ़ो(dev, B43_PHY_HT_BBCFG);
	b43_phy_ग_लिखो(dev, B43_PHY_HT_BBCFG, पंचांगp | B43_PHY_HT_BBCFG_RSTCCA);
	b43_phy_ग_लिखो(dev, B43_PHY_HT_BBCFG, पंचांगp & ~B43_PHY_HT_BBCFG_RSTCCA);
	b43_phy_क्रमce_घड़ी(dev, false);

	b43_mac_phy_घड़ी_set(dev, true);

	b43_phy_ht_pa_override(dev, false);
	b43_phy_ht_क्रमce_rf_sequence(dev, B43_PHY_HT_RF_SEQ_TRIG_RX2TX);
	b43_phy_ht_क्रमce_rf_sequence(dev, B43_PHY_HT_RF_SEQ_TRIG_RST2RX);
	b43_phy_ht_pa_override(dev, true);

	/* TODO: Should we restore it? Or store it in global PHY info? */
	b43_phy_ht_classअगरier(dev, 0, 0);
	b43_phy_ht_पढ़ो_clip_detection(dev, clip_state);

	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
		b43_phy_ht_bphy_init(dev);

	b43_httab_ग_लिखो_bulk(dev, B43_HTTAB32(0x1a, 0xc0),
			B43_HTTAB_1A_C0_LATE_SIZE, b43_httab_0x1a_0xc0_late);

	saved_tx_pwr_ctl = phy_ht->tx_pwr_ctl;
	b43_phy_ht_tx_घातer_fix(dev);
	b43_phy_ht_tx_घातer_ctl(dev, false);
	b43_phy_ht_tx_घातer_ctl_idle_tssi(dev);
	b43_phy_ht_tx_घातer_ctl_setup(dev);
	b43_phy_ht_tssi_setup(dev);
	b43_phy_ht_tx_घातer_ctl(dev, saved_tx_pwr_ctl);

	वापस 0;
पूर्ण

अटल व्योम b43_phy_ht_op_मुक्त(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_ht *phy_ht = phy->ht;

	kमुक्त(phy_ht);
	phy->ht = शून्य;
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/Radio/Switch%20Radio */
अटल व्योम b43_phy_ht_op_software_rfसमाप्त(काष्ठा b43_wldev *dev,
					bool blocked)
अणु
	अगर (b43_पढ़ो32(dev, B43_MMIO_MACCTL) & B43_MACCTL_ENABLED)
		b43err(dev->wl, "MAC not suspended\n");

	अगर (blocked) अणु
		b43_phy_mask(dev, B43_PHY_HT_RF_CTL_CMD,
			     ~B43_PHY_HT_RF_CTL_CMD_CHIP0_PU);
	पूर्ण अन्यथा अणु
		अगर (dev->phy.radio_ver == 0x2059)
			b43_radio_2059_init(dev);
		अन्यथा
			B43_WARN_ON(1);

		b43_चयन_channel(dev, dev->phy.channel);
	पूर्ण
पूर्ण

अटल व्योम b43_phy_ht_op_चयन_analog(काष्ठा b43_wldev *dev, bool on)
अणु
	अगर (on) अणु
		b43_phy_ग_लिखो(dev, B43_PHY_HT_AFE_C1, 0x00cd);
		b43_phy_ग_लिखो(dev, B43_PHY_HT_AFE_C1_OVER, 0x0000);
		b43_phy_ग_लिखो(dev, B43_PHY_HT_AFE_C2, 0x00cd);
		b43_phy_ग_लिखो(dev, B43_PHY_HT_AFE_C2_OVER, 0x0000);
		b43_phy_ग_लिखो(dev, B43_PHY_HT_AFE_C3, 0x00cd);
		b43_phy_ग_लिखो(dev, B43_PHY_HT_AFE_C3_OVER, 0x0000);
	पूर्ण अन्यथा अणु
		b43_phy_ग_लिखो(dev, B43_PHY_HT_AFE_C1_OVER, 0x07ff);
		b43_phy_ग_लिखो(dev, B43_PHY_HT_AFE_C1, 0x00fd);
		b43_phy_ग_लिखो(dev, B43_PHY_HT_AFE_C2_OVER, 0x07ff);
		b43_phy_ग_लिखो(dev, B43_PHY_HT_AFE_C2, 0x00fd);
		b43_phy_ग_लिखो(dev, B43_PHY_HT_AFE_C3_OVER, 0x07ff);
		b43_phy_ग_लिखो(dev, B43_PHY_HT_AFE_C3, 0x00fd);
	पूर्ण
पूर्ण

अटल पूर्णांक b43_phy_ht_op_चयन_channel(काष्ठा b43_wldev *dev,
					अचिन्हित पूर्णांक new_channel)
अणु
	काष्ठा ieee80211_channel *channel = dev->wl->hw->conf.chandef.chan;
	क्रमागत nl80211_channel_type channel_type =
		cfg80211_get_chandef_type(&dev->wl->hw->conf.chandef);

	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
		अगर ((new_channel < 1) || (new_channel > 14))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस b43_phy_ht_set_channel(dev, channel, channel_type);
पूर्ण

अटल अचिन्हित पूर्णांक b43_phy_ht_op_get_शेष_chan(काष्ठा b43_wldev *dev)
अणु
	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
		वापस 11;
	वापस 36;
पूर्ण

/**************************************************
 * R/W ops.
 **************************************************/

अटल व्योम b43_phy_ht_op_maskset(काष्ठा b43_wldev *dev, u16 reg, u16 mask,
				 u16 set)
अणु
	b43_ग_लिखो16f(dev, B43_MMIO_PHY_CONTROL, reg);
	b43_ग_लिखो16(dev, B43_MMIO_PHY_DATA,
		    (b43_पढ़ो16(dev, B43_MMIO_PHY_DATA) & mask) | set);
पूर्ण

अटल u16 b43_phy_ht_op_radio_पढ़ो(काष्ठा b43_wldev *dev, u16 reg)
अणु
	/* HT-PHY needs 0x200 क्रम पढ़ो access */
	reg |= 0x200;

	b43_ग_लिखो16f(dev, B43_MMIO_RADIO24_CONTROL, reg);
	वापस b43_पढ़ो16(dev, B43_MMIO_RADIO24_DATA);
पूर्ण

अटल व्योम b43_phy_ht_op_radio_ग_लिखो(काष्ठा b43_wldev *dev, u16 reg,
				      u16 value)
अणु
	b43_ग_लिखो16f(dev, B43_MMIO_RADIO24_CONTROL, reg);
	b43_ग_लिखो16(dev, B43_MMIO_RADIO24_DATA, value);
पूर्ण

अटल क्रमागत b43_txpwr_result
b43_phy_ht_op_recalc_txघातer(काष्ठा b43_wldev *dev, bool ignore_tssi)
अणु
	वापस B43_TXPWR_RES_DONE;
पूर्ण

अटल व्योम b43_phy_ht_op_adjust_txघातer(काष्ठा b43_wldev *dev)
अणु
पूर्ण

/**************************************************
 * PHY ops काष्ठा.
 **************************************************/

स्थिर काष्ठा b43_phy_operations b43_phyops_ht = अणु
	.allocate		= b43_phy_ht_op_allocate,
	.मुक्त			= b43_phy_ht_op_मुक्त,
	.prepare_काष्ठाs	= b43_phy_ht_op_prepare_काष्ठाs,
	.init			= b43_phy_ht_op_init,
	.phy_maskset		= b43_phy_ht_op_maskset,
	.radio_पढ़ो		= b43_phy_ht_op_radio_पढ़ो,
	.radio_ग_लिखो		= b43_phy_ht_op_radio_ग_लिखो,
	.software_rfसमाप्त	= b43_phy_ht_op_software_rfसमाप्त,
	.चयन_analog		= b43_phy_ht_op_चयन_analog,
	.चयन_channel		= b43_phy_ht_op_चयन_channel,
	.get_शेष_chan	= b43_phy_ht_op_get_शेष_chan,
	.recalc_txघातer		= b43_phy_ht_op_recalc_txघातer,
	.adjust_txघातer		= b43_phy_ht_op_adjust_txघातer,
पूर्ण;
