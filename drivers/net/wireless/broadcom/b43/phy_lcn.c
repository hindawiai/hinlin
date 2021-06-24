<शैली गुरु>
/*

  Broadcom B43 wireless driver
  IEEE 802.11n LCN-PHY support

  Copyright (c) 2011 Rafaध Miधecki <zajec5@gmail.com>

  This program is मुक्त software; you can redistribute it and/or modअगरy
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License क्रम more details.

  You should have received a copy of the GNU General Public License
  aदीर्घ with this program; see the file COPYING.  If not, ग_लिखो to
  the Free Software Foundation, Inc., 51 Franklin Steet, Fअगरth Floor,
  Boston, MA 02110-1301, USA.

  This file incorporates work covered by the following copyright and
  permission notice:

      Copyright (c) 2010 Broadcom Corporation

      Permission to use, copy, modअगरy, and/or distribute this software क्रम any
      purpose with or without fee is hereby granted, provided that the above
      copyright notice and this permission notice appear in all copies.
*/

#समावेश <linux/slab.h>

#समावेश "b43.h"
#समावेश "phy_lcn.h"
#समावेश "tables_phy_lcn.h"
#समावेश "main.h"

काष्ठा lcn_tx_gains अणु
	u16 gm_gain;
	u16 pga_gain;
	u16 pad_gain;
	u16 dac_gain;
पूर्ण;

काष्ठा lcn_tx_iir_filter अणु
	u8 type;
	u16 values[16];
पूर्ण;

क्रमागत lcn_sense_type अणु
	B43_SENSE_TEMP,
	B43_SENSE_VBAT,
पूर्ण;

/**************************************************
 * Radio 2064.
 **************************************************/

/* wlc_lcnphy_radio_2064_channel_tune_4313 */
अटल व्योम b43_radio_2064_channel_setup(काष्ठा b43_wldev *dev)
अणु
	u16 save[2];

	b43_radio_set(dev, 0x09d, 0x4);
	b43_radio_ग_लिखो(dev, 0x09e, 0xf);

	/* Channel specअगरic values in theory, in practice always the same */
	b43_radio_ग_लिखो(dev, 0x02a, 0xb);
	b43_radio_maskset(dev, 0x030, ~0x3, 0xa);
	b43_radio_maskset(dev, 0x091, ~0x3, 0);
	b43_radio_maskset(dev, 0x038, ~0xf, 0x7);
	b43_radio_maskset(dev, 0x030, ~0xc, 0x8);
	b43_radio_maskset(dev, 0x05e, ~0xf, 0x8);
	b43_radio_maskset(dev, 0x05e, ~0xf0, 0x80);
	b43_radio_ग_लिखो(dev, 0x06c, 0x80);

	save[0] = b43_radio_पढ़ो(dev, 0x044);
	save[1] = b43_radio_पढ़ो(dev, 0x12b);

	b43_radio_set(dev, 0x044, 0x7);
	b43_radio_set(dev, 0x12b, 0xe);

	/* TODO */

	b43_radio_ग_लिखो(dev, 0x040, 0xfb);

	b43_radio_ग_लिखो(dev, 0x041, 0x9a);
	b43_radio_ग_लिखो(dev, 0x042, 0xa3);
	b43_radio_ग_लिखो(dev, 0x043, 0x0c);

	/* TODO */

	b43_radio_set(dev, 0x044, 0x0c);
	udelay(1);

	b43_radio_ग_लिखो(dev, 0x044, save[0]);
	b43_radio_ग_लिखो(dev, 0x12b, save[1]);

	अगर (dev->phy.rev == 1) अणु
		/* brcmsmac uses outdated 0x3 क्रम 0x038 */
		b43_radio_ग_लिखो(dev, 0x038, 0x0);
		b43_radio_ग_लिखो(dev, 0x091, 0x7);
	पूर्ण
पूर्ण

/* wlc_radio_2064_init */
अटल व्योम b43_radio_2064_init(काष्ठा b43_wldev *dev)
अणु
	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
		b43_radio_ग_लिखो(dev, 0x09c, 0x0020);
		b43_radio_ग_लिखो(dev, 0x105, 0x0008);
	पूर्ण अन्यथा अणु
		/* TODO */
	पूर्ण
	b43_radio_ग_लिखो(dev, 0x032, 0x0062);
	b43_radio_ग_लिखो(dev, 0x033, 0x0019);
	b43_radio_ग_लिखो(dev, 0x090, 0x0010);
	b43_radio_ग_लिखो(dev, 0x010, 0x0000);
	अगर (dev->phy.rev == 1) अणु
		b43_radio_ग_लिखो(dev, 0x060, 0x007f);
		b43_radio_ग_लिखो(dev, 0x061, 0x0072);
		b43_radio_ग_लिखो(dev, 0x062, 0x007f);
	पूर्ण
	b43_radio_ग_लिखो(dev, 0x01d, 0x0002);
	b43_radio_ग_लिखो(dev, 0x01e, 0x0006);

	b43_phy_ग_लिखो(dev, 0x4ea, 0x4688);
	b43_phy_maskset(dev, 0x4eb, ~0x7, 0x2);
	b43_phy_mask(dev, 0x4eb, ~0x01c0);
	b43_phy_maskset(dev, 0x46a, 0xff00, 0x19);

	b43_lcntab_ग_लिखो(dev, B43_LCNTAB16(0x00, 0x55), 0);

	b43_radio_mask(dev, 0x05b, (u16) ~0xff02);
	b43_radio_set(dev, 0x004, 0x40);
	b43_radio_set(dev, 0x120, 0x10);
	b43_radio_set(dev, 0x078, 0x80);
	b43_radio_set(dev, 0x129, 0x2);
	b43_radio_set(dev, 0x057, 0x1);
	b43_radio_set(dev, 0x05b, 0x2);

	/* TODO: रुको क्रम some bit to be set */
	b43_radio_पढ़ो(dev, 0x05c);

	b43_radio_mask(dev, 0x05b, (u16) ~0xff02);
	b43_radio_mask(dev, 0x057, (u16) ~0xff01);

	b43_phy_ग_लिखो(dev, 0x933, 0x2d6b);
	b43_phy_ग_लिखो(dev, 0x934, 0x2d6b);
	b43_phy_ग_लिखो(dev, 0x935, 0x2d6b);
	b43_phy_ग_लिखो(dev, 0x936, 0x2d6b);
	b43_phy_ग_लिखो(dev, 0x937, 0x016b);

	b43_radio_mask(dev, 0x057, (u16) ~0xff02);
	b43_radio_ग_लिखो(dev, 0x0c2, 0x006f);
पूर्ण

/**************************************************
 * Various PHY ops
 **************************************************/

/* wlc_lcnphy_toggle_afe_pwdn */
अटल व्योम b43_phy_lcn_afe_set_unset(काष्ठा b43_wldev *dev)
अणु
	u16 afe_ctl2 = b43_phy_पढ़ो(dev, B43_PHY_LCN_AFE_CTL2);
	u16 afe_ctl1 = b43_phy_पढ़ो(dev, B43_PHY_LCN_AFE_CTL1);

	b43_phy_ग_लिखो(dev, B43_PHY_LCN_AFE_CTL2, afe_ctl2 | 0x1);
	b43_phy_ग_लिखो(dev, B43_PHY_LCN_AFE_CTL1, afe_ctl1 | 0x1);

	b43_phy_ग_लिखो(dev, B43_PHY_LCN_AFE_CTL2, afe_ctl2 & ~0x1);
	b43_phy_ग_लिखो(dev, B43_PHY_LCN_AFE_CTL1, afe_ctl1 & ~0x1);

	b43_phy_ग_लिखो(dev, B43_PHY_LCN_AFE_CTL2, afe_ctl2);
	b43_phy_ग_लिखो(dev, B43_PHY_LCN_AFE_CTL1, afe_ctl1);
पूर्ण

/* wlc_lcnphy_get_pa_gain */
अटल u16 b43_phy_lcn_get_pa_gain(काष्ठा b43_wldev *dev)
अणु
	वापस (b43_phy_पढ़ो(dev, 0x4fb) & 0x7f00) >> 8;
पूर्ण

/* wlc_lcnphy_set_dac_gain */
अटल व्योम b43_phy_lcn_set_dac_gain(काष्ठा b43_wldev *dev, u16 dac_gain)
अणु
	u16 dac_ctrl;

	dac_ctrl = b43_phy_पढ़ो(dev, 0x439);
	dac_ctrl = dac_ctrl & 0xc7f;
	dac_ctrl = dac_ctrl | (dac_gain << 7);
	b43_phy_maskset(dev, 0x439, ~0xfff, dac_ctrl);
पूर्ण

/* wlc_lcnphy_set_bbmult */
अटल व्योम b43_phy_lcn_set_bbmult(काष्ठा b43_wldev *dev, u8 m0)
अणु
	b43_lcntab_ग_लिखो(dev, B43_LCNTAB16(0x00, 0x57), m0 << 8);
पूर्ण

/* wlc_lcnphy_clear_tx_घातer_offsets */
अटल व्योम b43_phy_lcn_clear_tx_घातer_offsets(काष्ठा b43_wldev *dev)
अणु
	u8 i;

	अगर (1) अणु /* FIXME */
		b43_phy_ग_लिखो(dev, B43_PHY_LCN_TABLE_ADDR, (0x7 << 10) | 0x340);
		क्रम (i = 0; i < 30; i++) अणु
			b43_phy_ग_लिखो(dev, B43_PHY_LCN_TABLE_DATAHI, 0);
			b43_phy_ग_लिखो(dev, B43_PHY_LCN_TABLE_DATALO, 0);
		पूर्ण
	पूर्ण

	b43_phy_ग_लिखो(dev, B43_PHY_LCN_TABLE_ADDR, (0x7 << 10) | 0x80);
	क्रम (i = 0; i < 64; i++) अणु
		b43_phy_ग_लिखो(dev, B43_PHY_LCN_TABLE_DATAHI, 0);
		b43_phy_ग_लिखो(dev, B43_PHY_LCN_TABLE_DATALO, 0);
	पूर्ण
पूर्ण

/* wlc_lcnphy_rev0_baseband_init */
अटल व्योम b43_phy_lcn_rev0_baseband_init(काष्ठा b43_wldev *dev)
अणु
	b43_radio_ग_लिखो(dev, 0x11c, 0);

	b43_phy_ग_लिखो(dev, 0x43b, 0);
	b43_phy_ग_लिखो(dev, 0x43c, 0);
	b43_phy_ग_लिखो(dev, 0x44c, 0);
	b43_phy_ग_लिखो(dev, 0x4e6, 0);
	b43_phy_ग_लिखो(dev, 0x4f9, 0);
	b43_phy_ग_लिखो(dev, 0x4b0, 0);
	b43_phy_ग_लिखो(dev, 0x938, 0);
	b43_phy_ग_लिखो(dev, 0x4b0, 0);
	b43_phy_ग_लिखो(dev, 0x44e, 0);

	b43_phy_set(dev, 0x567, 0x03);

	b43_phy_set(dev, 0x44a, 0x44);
	b43_phy_ग_लिखो(dev, 0x44a, 0x80);

	अगर (!(dev->dev->bus_sprom->boardflags_lo & B43_BFL_FEM))
		; /* TODO */
	b43_phy_maskset(dev, 0x634, ~0xff, 0xc);
	अगर (dev->dev->bus_sprom->boardflags_lo & B43_BFL_FEM) अणु
		b43_phy_maskset(dev, 0x634, ~0xff, 0xa);
		b43_phy_ग_लिखो(dev, 0x910, 0x1);
	पूर्ण

	b43_phy_ग_लिखो(dev, 0x910, 0x1);

	b43_phy_maskset(dev, 0x448, ~0x300, 0x100);
	b43_phy_maskset(dev, 0x608, ~0xff, 0x17);
	b43_phy_maskset(dev, 0x604, ~0x7ff, 0x3ea);
पूर्ण

/* wlc_lcnphy_bu_tweaks */
अटल व्योम b43_phy_lcn_bu_tweaks(काष्ठा b43_wldev *dev)
अणु
	b43_phy_set(dev, 0x805, 0x1);

	b43_phy_maskset(dev, 0x42f, ~0x7, 0x3);
	b43_phy_maskset(dev, 0x030, ~0x7, 0x3);

	b43_phy_ग_लिखो(dev, 0x414, 0x1e10);
	b43_phy_ग_लिखो(dev, 0x415, 0x0640);

	b43_phy_maskset(dev, 0x4df, (u16) ~0xff00, 0xf700);

	b43_phy_set(dev, 0x44a, 0x44);
	b43_phy_ग_लिखो(dev, 0x44a, 0x80);

	b43_phy_maskset(dev, 0x434, ~0xff, 0xfd);
	b43_phy_maskset(dev, 0x420, ~0xff, 0x10);

	अगर (dev->dev->bus_sprom->board_rev >= 0x1204)
		b43_radio_set(dev, 0x09b, 0xf0);

	b43_phy_ग_लिखो(dev, 0x7d6, 0x0902);

	b43_phy_maskset(dev, 0x429, ~0xf, 0x9);
	b43_phy_maskset(dev, 0x429, ~(0x3f << 4), 0xe << 4);

	अगर (dev->phy.rev == 1) अणु
		b43_phy_maskset(dev, 0x423, ~0xff, 0x46);
		b43_phy_maskset(dev, 0x411, ~0xff, 1);
		b43_phy_set(dev, 0x434, 0xff); /* FIXME: update to wl */

		/* TODO: wl operates on PHY 0x416, brcmsmac is outdated here */

		b43_phy_maskset(dev, 0x656, ~0xf, 2);
		b43_phy_set(dev, 0x44d, 4);

		b43_radio_set(dev, 0x0f7, 0x4);
		b43_radio_mask(dev, 0x0f1, ~0x3);
		b43_radio_maskset(dev, 0x0f2, ~0xf8, 0x90);
		b43_radio_maskset(dev, 0x0f3, ~0x3, 0x2);
		b43_radio_maskset(dev, 0x0f3, ~0xf0, 0xa0);

		b43_radio_set(dev, 0x11f, 0x2);

		b43_phy_lcn_clear_tx_घातer_offsets(dev);

		/* TODO: something more? */
	पूर्ण
पूर्ण

/* wlc_lcnphy_vbat_temp_sense_setup */
अटल व्योम b43_phy_lcn_sense_setup(काष्ठा b43_wldev *dev,
				    क्रमागत lcn_sense_type sense_type)
अणु
	u8 auxpga_vmidcourse, auxpga_vmidfine, auxpga_gain;
	u16 auxpga_vmid;
	u8 tx_pwr_idx;
	u8 i;

	u16 save_radio_regs[6][2] = अणु
		अणु 0x007, 0 पूर्ण, अणु 0x0ff, 0 पूर्ण, अणु 0x11f, 0 पूर्ण, अणु 0x005, 0 पूर्ण,
		अणु 0x025, 0 पूर्ण, अणु 0x112, 0 पूर्ण,
	पूर्ण;
	u16 save_phy_regs[14][2] = अणु
		अणु 0x503, 0 पूर्ण, अणु 0x4a4, 0 पूर्ण, अणु 0x4d0, 0 पूर्ण, अणु 0x4d9, 0 पूर्ण,
		अणु 0x4da, 0 पूर्ण, अणु 0x4a6, 0 पूर्ण, अणु 0x938, 0 पूर्ण, अणु 0x939, 0 पूर्ण,
		अणु 0x4d8, 0 पूर्ण, अणु 0x4d0, 0 पूर्ण, अणु 0x4d7, 0 पूर्ण, अणु 0x4a5, 0 पूर्ण,
		अणु 0x40d, 0 पूर्ण, अणु 0x4a2, 0 पूर्ण,
	पूर्ण;
	u16 save_radio_4a4;

	msleep(1);

	/* Save */
	क्रम (i = 0; i < 6; i++)
		save_radio_regs[i][1] = b43_radio_पढ़ो(dev,
						       save_radio_regs[i][0]);
	क्रम (i = 0; i < 14; i++)
		save_phy_regs[i][1] = b43_phy_पढ़ो(dev, save_phy_regs[i][0]);
	b43_mac_suspend(dev);
	save_radio_4a4 = b43_radio_पढ़ो(dev, 0x4a4);
	/* wlc_lcnphy_set_tx_pwr_ctrl(pi, LCNPHY_TX_PWR_CTRL_OFF); */
	tx_pwr_idx = dev->phy.lcn->tx_pwr_curr_idx;

	/* Setup */
	/* TODO: wlc_lcnphy_set_tx_pwr_by_index(pi, 127); */
	b43_radio_set(dev, 0x007, 0x1);
	b43_radio_set(dev, 0x0ff, 0x10);
	b43_radio_set(dev, 0x11f, 0x4);

	b43_phy_mask(dev, 0x503, ~0x1);
	b43_phy_mask(dev, 0x503, ~0x4);
	b43_phy_mask(dev, 0x4a4, ~0x4000);
	b43_phy_mask(dev, 0x4a4, (u16) ~0x8000);
	b43_phy_mask(dev, 0x4d0, ~0x20);
	b43_phy_set(dev, 0x4a5, 0xff);
	b43_phy_maskset(dev, 0x4a5, ~0x7000, 0x5000);
	b43_phy_mask(dev, 0x4a5, ~0x700);
	b43_phy_maskset(dev, 0x40d, ~0xff, 64);
	b43_phy_maskset(dev, 0x40d, ~0x700, 0x600);
	b43_phy_maskset(dev, 0x4a2, ~0xff, 64);
	b43_phy_maskset(dev, 0x4a2, ~0x700, 0x600);
	b43_phy_maskset(dev, 0x4d9, ~0x70, 0x20);
	b43_phy_maskset(dev, 0x4d9, ~0x700, 0x300);
	b43_phy_maskset(dev, 0x4d9, ~0x7000, 0x1000);
	b43_phy_mask(dev, 0x4da, ~0x1000);
	b43_phy_set(dev, 0x4da, 0x2000);
	b43_phy_set(dev, 0x4a6, 0x8000);

	b43_radio_ग_लिखो(dev, 0x025, 0xc);
	b43_radio_set(dev, 0x005, 0x8);
	b43_phy_set(dev, 0x938, 0x4);
	b43_phy_set(dev, 0x939, 0x4);
	b43_phy_set(dev, 0x4a4, 0x1000);

	/* FIXME: करोn't hardcode */
	b43_lcntab_ग_लिखो(dev, B43_LCNTAB16(0x8, 0x6), 0x640);

	चयन (sense_type) अणु
	हाल B43_SENSE_TEMP:
		b43_phy_set(dev, 0x4d7, 0x8);
		b43_phy_maskset(dev, 0x4d7, ~0x7000, 0x1000);
		auxpga_vmidcourse = 8;
		auxpga_vmidfine = 0x4;
		auxpga_gain = 2;
		b43_radio_set(dev, 0x082, 0x20);
		अवरोध;
	हाल B43_SENSE_VBAT:
		b43_phy_set(dev, 0x4d7, 0x8);
		b43_phy_maskset(dev, 0x4d7, ~0x7000, 0x3000);
		auxpga_vmidcourse = 7;
		auxpga_vmidfine = 0xa;
		auxpga_gain = 2;
		अवरोध;
	पूर्ण
	auxpga_vmid = (0x200 | (auxpga_vmidcourse << 4) | auxpga_vmidfine);

	b43_phy_set(dev, 0x4d8, 0x1);
	b43_phy_maskset(dev, 0x4d8, ~(0x3ff << 2), auxpga_vmid << 2);
	b43_phy_set(dev, 0x4d8, 0x2);
	b43_phy_maskset(dev, 0x4d8, ~(0x7 << 12), auxpga_gain << 12);
	b43_phy_set(dev, 0x4d0, 0x20);
	b43_radio_ग_लिखो(dev, 0x112, 0x6);

	b43_dummy_transmission(dev, true, false);
	/* Wait अगर not करोne */
	अगर (!(b43_phy_पढ़ो(dev, 0x476) & 0x8000))
		udelay(10);

	/* Restore */
	क्रम (i = 0; i < 6; i++)
		b43_radio_ग_लिखो(dev, save_radio_regs[i][0],
				save_radio_regs[i][1]);
	क्रम (i = 0; i < 14; i++)
		b43_phy_ग_लिखो(dev, save_phy_regs[i][0], save_phy_regs[i][1]);
	/* TODO: wlc_lcnphy_set_tx_pwr_by_index(tx_pwr_idx) */
	b43_radio_ग_लिखो(dev, 0x4a4, save_radio_4a4);

	b43_mac_enable(dev);

	msleep(1);
पूर्ण

अटल bool b43_phy_lcn_load_tx_iir_cck_filter(काष्ठा b43_wldev *dev,
					       u8 filter_type)
अणु
	पूर्णांक i, j;
	u16 phy_regs[] = अणु 0x910, 0x91e, 0x91f, 0x924, 0x925, 0x926, 0x920,
			   0x921, 0x927, 0x928, 0x929, 0x922, 0x923, 0x930,
			   0x931, 0x932 पूर्ण;
	/* Table is from brcmsmac, values क्रम type 25 were outdated, probably
	 * others need updating too */
	काष्ठा lcn_tx_iir_filter tx_iir_filters_cck[] = अणु
		अणु 0,  अणु 1, 415, 1874, 64, 128, 64, 792, 1656, 64, 128, 64, 778,
			1582, 64, 128, 64 पूर्ण पूर्ण,
		अणु 1,  अणु 1, 402, 1847, 259, 59, 259, 671, 1794, 68, 54, 68, 608,
			1863, 93, 167, 93 पूर्ण पूर्ण,
		अणु 2,  अणु 1, 415, 1874, 64, 128, 64, 792, 1656, 192, 384, 192,
			778, 1582, 64, 128, 64 पूर्ण पूर्ण,
		अणु 3,  अणु 1, 302, 1841, 129, 258, 129, 658, 1720, 205, 410, 205,
			754, 1760, 170, 340, 170 पूर्ण पूर्ण,
		अणु 20, अणु 1, 360, 1884, 242, 1734, 242, 752, 1720, 205, 1845, 205,
			767, 1760, 256, 185, 256 पूर्ण पूर्ण,
		अणु 21, अणु 1, 360, 1884, 149, 1874, 149, 752, 1720, 205, 1883, 205,
			767, 1760, 256, 273, 256 पूर्ण पूर्ण,
		अणु 22, अणु 1, 360, 1884, 98, 1948, 98, 752, 1720, 205, 1924, 205,
			767, 1760, 256, 352, 256 पूर्ण पूर्ण,
		अणु 23, अणु 1, 350, 1884, 116, 1966, 116, 752, 1720, 205, 2008, 205,
			767, 1760, 128, 233, 128 पूर्ण पूर्ण,
		अणु 24, अणु 1, 325, 1884, 32, 40, 32, 756, 1720, 256, 471, 256, 766,
			1760, 256, 1881, 256 पूर्ण पूर्ण,
		अणु 25, अणु 1, 299, 1884, 51, 64, 51, 736, 1720, 256, 471, 256, 765,
			1760, 262, 1878, 262 पूर्ण पूर्ण,
		/* brcmsmac version अणु 25, अणु 1, 299, 1884, 51, 64, 51, 736, 1720,
		 * 256, 471, 256, 765, 1760, 256, 1881, 256 पूर्ण पूर्ण, */
		अणु 26, अणु 1, 277, 1943, 39, 117, 88, 637, 1838, 64, 192, 144, 614,
			1864, 128, 384, 288 पूर्ण पूर्ण,
		अणु 27, अणु 1, 245, 1943, 49, 147, 110, 626, 1838, 256, 768, 576,
			613, 1864, 128, 384, 288 पूर्ण पूर्ण,
		अणु 30, अणु 1, 302, 1841, 61, 122, 61, 658, 1720, 205, 410, 205,
			754, 1760, 170, 340, 170 पूर्ण पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(tx_iir_filters_cck); i++) अणु
		अगर (tx_iir_filters_cck[i].type == filter_type) अणु
			क्रम (j = 0; j < 16; j++)
				b43_phy_ग_लिखो(dev, phy_regs[j],
					      tx_iir_filters_cck[i].values[j]);
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool b43_phy_lcn_load_tx_iir_ofdm_filter(काष्ठा b43_wldev *dev,
						u8 filter_type)
अणु
	पूर्णांक i, j;
	u16 phy_regs[] = अणु 0x90f, 0x900, 0x901, 0x906, 0x907, 0x908, 0x902,
			   0x903, 0x909, 0x90a, 0x90b, 0x904, 0x905, 0x90c,
			   0x90d, 0x90e पूर्ण;
	काष्ठा lcn_tx_iir_filter tx_iir_filters_ofdm[] = अणु
		अणु 0, अणु 0, 0xa2, 0x0, 0x100, 0x100, 0x0, 0x0, 0x0, 0x100, 0x0,
		       0x0, 0x278, 0xfea0, 0x80, 0x100, 0x80 पूर्ण पूर्ण,
		अणु 1, अणु 0, 374, 0xFF79, 16, 32, 16, 799, 0xFE74, 50, 32, 50, 750,
		       0xFE2B, 212, 0xFFCE, 212 पूर्ण पूर्ण,
		अणु 2, अणु 0, 375, 0xFF16, 37, 76, 37, 799, 0xFE74, 32, 20, 32, 748,
		       0xFEF2, 128, 0xFFE2, 128 पूर्ण पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(tx_iir_filters_ofdm); i++) अणु
		अगर (tx_iir_filters_ofdm[i].type == filter_type) अणु
			क्रम (j = 0; j < 16; j++)
				b43_phy_ग_लिखो(dev, phy_regs[j],
					      tx_iir_filters_ofdm[i].values[j]);
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

/* wlc_lcnphy_set_tx_gain_override */
अटल व्योम b43_phy_lcn_set_tx_gain_override(काष्ठा b43_wldev *dev, bool enable)
अणु
	b43_phy_maskset(dev, 0x4b0, ~(0x1 << 7), enable << 7);
	b43_phy_maskset(dev, 0x4b0, ~(0x1 << 14), enable << 14);
	b43_phy_maskset(dev, 0x43b, ~(0x1 << 6), enable << 6);
पूर्ण

/* wlc_lcnphy_set_tx_gain */
अटल व्योम b43_phy_lcn_set_tx_gain(काष्ठा b43_wldev *dev,
				    काष्ठा lcn_tx_gains *target_gains)
अणु
	u16 pa_gain = b43_phy_lcn_get_pa_gain(dev);

	b43_phy_ग_लिखो(dev, 0x4b5,
		      (target_gains->gm_gain | (target_gains->pga_gain << 8)));
	b43_phy_maskset(dev, 0x4fb, ~0x7fff,
			(target_gains->pad_gain | (pa_gain << 8)));
	b43_phy_ग_लिखो(dev, 0x4fc,
		      (target_gains->gm_gain | (target_gains->pga_gain << 8)));
	b43_phy_maskset(dev, 0x4fd, ~0x7fff,
			(target_gains->pad_gain | (pa_gain << 8)));

	b43_phy_lcn_set_dac_gain(dev, target_gains->dac_gain);
	b43_phy_lcn_set_tx_gain_override(dev, true);
पूर्ण

/* wlc_lcnphy_tx_pwr_ctrl_init */
अटल व्योम b43_phy_lcn_tx_pwr_ctl_init(काष्ठा b43_wldev *dev)
अणु
	काष्ठा lcn_tx_gains tx_gains;
	u8 bbmult;

	b43_mac_suspend(dev);

	अगर (!dev->phy.lcn->hw_pwr_ctl_capable) अणु
		अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) अणु
			tx_gains.gm_gain = 4;
			tx_gains.pga_gain = 12;
			tx_gains.pad_gain = 12;
			tx_gains.dac_gain = 0;
			bbmult = 150;
		पूर्ण अन्यथा अणु
			tx_gains.gm_gain = 7;
			tx_gains.pga_gain = 15;
			tx_gains.pad_gain = 14;
			tx_gains.dac_gain = 0;
			bbmult = 150;
		पूर्ण
		b43_phy_lcn_set_tx_gain(dev, &tx_gains);
		b43_phy_lcn_set_bbmult(dev, bbmult);
		b43_phy_lcn_sense_setup(dev, B43_SENSE_TEMP);
	पूर्ण अन्यथा अणु
		b43err(dev->wl, "TX power control not supported for this HW\n");
	पूर्ण

	b43_mac_enable(dev);
पूर्ण

/* wlc_lcnphy_txrx_spur_aव्योमance_mode */
अटल व्योम b43_phy_lcn_txrx_spur_aव्योमance_mode(काष्ठा b43_wldev *dev,
						 bool enable)
अणु
	अगर (enable) अणु
		b43_phy_ग_लिखो(dev, 0x942, 0x7);
		b43_phy_ग_लिखो(dev, 0x93b, ((1 << 13) + 23));
		b43_phy_ग_लिखो(dev, 0x93c, ((1 << 13) + 1989));

		b43_phy_ग_लिखो(dev, 0x44a, 0x084);
		b43_phy_ग_लिखो(dev, 0x44a, 0x080);
		b43_phy_ग_लिखो(dev, 0x6d3, 0x2222);
		b43_phy_ग_लिखो(dev, 0x6d3, 0x2220);
	पूर्ण अन्यथा अणु
		b43_phy_ग_लिखो(dev, 0x942, 0x0);
		b43_phy_ग_लिखो(dev, 0x93b, ((0 << 13) + 23));
		b43_phy_ग_लिखो(dev, 0x93c, ((0 << 13) + 1989));
	पूर्ण
	b43_mac_चयन_freq(dev, enable);
पूर्ण

/**************************************************
 * Channel चयनing ops.
 **************************************************/

/* wlc_lcnphy_set_chanspec_tweaks */
अटल व्योम b43_phy_lcn_set_channel_tweaks(काष्ठा b43_wldev *dev, पूर्णांक channel)
अणु
	काष्ठा bcma_drv_cc *cc = &dev->dev->bdev->bus->drv_cc;

	b43_phy_maskset(dev, 0x448, ~0x300, (channel == 14) ? 0x200 : 0x100);

	अगर (channel == 1 || channel == 2 || channel == 3 || channel == 4 ||
	    channel == 9 || channel == 10 || channel == 11 || channel == 12) अणु
		bcma_chipco_pll_ग_लिखो(cc, 0x2, 0x03000c04);
		bcma_chipco_pll_maskset(cc, 0x3, 0x00ffffff, 0x0);
		bcma_chipco_pll_ग_लिखो(cc, 0x4, 0x200005c0);

		bcma_cc_set32(cc, BCMA_CC_PMU_CTL, 0x400);

		b43_phy_ग_लिखो(dev, 0x942, 0);

		b43_phy_lcn_txrx_spur_aव्योमance_mode(dev, false);
		b43_phy_maskset(dev, 0x424, (u16) ~0xff00, 0x1b00);
		b43_phy_ग_लिखो(dev, 0x425, 0x5907);
	पूर्ण अन्यथा अणु
		bcma_chipco_pll_ग_लिखो(cc, 0x2, 0x03140c04);
		bcma_chipco_pll_maskset(cc, 0x3, 0x00ffffff, 0x333333);
		bcma_chipco_pll_ग_लिखो(cc, 0x4, 0x202c2820);

		bcma_cc_set32(cc, BCMA_CC_PMU_CTL, 0x400);

		b43_phy_ग_लिखो(dev, 0x942, 0);

		b43_phy_lcn_txrx_spur_aव्योमance_mode(dev, true);
		b43_phy_maskset(dev, 0x424, (u16) ~0xff00, 0x1f00);
		b43_phy_ग_लिखो(dev, 0x425, 0x590a);
	पूर्ण

	b43_phy_set(dev, 0x44a, 0x44);
	b43_phy_ग_लिखो(dev, 0x44a, 0x80);
पूर्ण

/* wlc_phy_chanspec_set_lcnphy */
अटल पूर्णांक b43_phy_lcn_set_channel(काष्ठा b43_wldev *dev,
				   काष्ठा ieee80211_channel *channel,
				   क्रमागत nl80211_channel_type channel_type)
अणु
	अटल स्थिर u16 sfo_cfg[14][2] = अणु
		अणु965, 1087पूर्ण, अणु967, 1085पूर्ण, अणु969, 1082पूर्ण, अणु971, 1080पूर्ण, अणु973, 1078पूर्ण,
		अणु975, 1076पूर्ण, अणु977, 1073पूर्ण, अणु979, 1071पूर्ण, अणु981, 1069पूर्ण, अणु983, 1067पूर्ण,
		अणु985, 1065पूर्ण, अणु987, 1063पूर्ण, अणु989, 1060पूर्ण, अणु994, 1055पूर्ण,
	पूर्ण;

	b43_phy_lcn_set_channel_tweaks(dev, channel->hw_value);

	b43_phy_set(dev, 0x44a, 0x44);
	b43_phy_ग_लिखो(dev, 0x44a, 0x80);

	b43_radio_2064_channel_setup(dev);
	mdelay(1);

	b43_phy_lcn_afe_set_unset(dev);

	b43_phy_ग_लिखो(dev, 0x657, sfo_cfg[channel->hw_value - 1][0]);
	b43_phy_ग_लिखो(dev, 0x658, sfo_cfg[channel->hw_value - 1][1]);

	अगर (channel->hw_value == 14) अणु
		b43_phy_maskset(dev, 0x448, ~(0x3 << 8), (2) << 8);
		b43_phy_lcn_load_tx_iir_cck_filter(dev, 3);
	पूर्ण अन्यथा अणु
		b43_phy_maskset(dev, 0x448, ~(0x3 << 8), (1) << 8);
		/* brcmsmac uses filter_type 2, we follow wl with 25 */
		b43_phy_lcn_load_tx_iir_cck_filter(dev, 25);
	पूर्ण
	/* brcmsmac uses filter_type 2, we follow wl with 0 */
	b43_phy_lcn_load_tx_iir_ofdm_filter(dev, 0);

	b43_phy_maskset(dev, 0x4eb, ~(0x7 << 3), 0x1 << 3);

	वापस 0;
पूर्ण

/**************************************************
 * Basic PHY ops.
 **************************************************/

अटल पूर्णांक b43_phy_lcn_op_allocate(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_lcn *phy_lcn;

	phy_lcn = kzalloc(माप(*phy_lcn), GFP_KERNEL);
	अगर (!phy_lcn)
		वापस -ENOMEM;
	dev->phy.lcn = phy_lcn;

	वापस 0;
पूर्ण

अटल व्योम b43_phy_lcn_op_मुक्त(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_lcn *phy_lcn = phy->lcn;

	kमुक्त(phy_lcn);
	phy->lcn = शून्य;
पूर्ण

अटल व्योम b43_phy_lcn_op_prepare_काष्ठाs(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_lcn *phy_lcn = phy->lcn;

	स_रखो(phy_lcn, 0, माप(*phy_lcn));
पूर्ण

/* wlc_phy_init_lcnphy */
अटल पूर्णांक b43_phy_lcn_op_init(काष्ठा b43_wldev *dev)
अणु
	काष्ठा bcma_drv_cc *cc = &dev->dev->bdev->bus->drv_cc;

	b43_phy_set(dev, 0x44a, 0x80);
	b43_phy_mask(dev, 0x44a, 0x7f);
	b43_phy_set(dev, 0x6d1, 0x80);
	b43_phy_ग_लिखो(dev, 0x6d0, 0x7);

	b43_phy_lcn_afe_set_unset(dev);

	b43_phy_ग_लिखो(dev, 0x60a, 0xa0);
	b43_phy_ग_लिखो(dev, 0x46a, 0x19);
	b43_phy_maskset(dev, 0x663, 0xFF00, 0x64);

	b43_phy_lcn_tables_init(dev);

	b43_phy_lcn_rev0_baseband_init(dev);
	b43_phy_lcn_bu_tweaks(dev);

	अगर (dev->phy.radio_ver == 0x2064)
		b43_radio_2064_init(dev);
	अन्यथा
		B43_WARN_ON(1);

	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
		b43_phy_lcn_tx_pwr_ctl_init(dev);

	b43_चयन_channel(dev, dev->phy.channel);

	bcma_chipco_regctl_maskset(cc, 0, 0xf, 0x9);
	bcma_chipco_chipctl_maskset(cc, 0, 0, 0x03cddddd);

	/* TODO */

	b43_phy_set(dev, 0x448, 0x4000);
	udelay(100);
	b43_phy_mask(dev, 0x448, ~0x4000);

	/* TODO */

	वापस 0;
पूर्ण

अटल व्योम b43_phy_lcn_op_software_rfसमाप्त(काष्ठा b43_wldev *dev,
					bool blocked)
अणु
	अगर (b43_पढ़ो32(dev, B43_MMIO_MACCTL) & B43_MACCTL_ENABLED)
		b43err(dev->wl, "MAC not suspended\n");

	अगर (blocked) अणु
		b43_phy_mask(dev, B43_PHY_LCN_RF_CTL2, ~0x7c00);
		b43_phy_set(dev, B43_PHY_LCN_RF_CTL1, 0x1f00);

		b43_phy_mask(dev, B43_PHY_LCN_RF_CTL5, ~0x7f00);
		b43_phy_mask(dev, B43_PHY_LCN_RF_CTL4, ~0x2);
		b43_phy_set(dev, B43_PHY_LCN_RF_CTL3, 0x808);

		b43_phy_mask(dev, B43_PHY_LCN_RF_CTL7, ~0x8);
		b43_phy_set(dev, B43_PHY_LCN_RF_CTL6, 0x8);
	पूर्ण अन्यथा अणु
		b43_phy_mask(dev, B43_PHY_LCN_RF_CTL1, ~0x1f00);
		b43_phy_mask(dev, B43_PHY_LCN_RF_CTL3, ~0x808);
		b43_phy_mask(dev, B43_PHY_LCN_RF_CTL6, ~0x8);
	पूर्ण
पूर्ण

अटल व्योम b43_phy_lcn_op_चयन_analog(काष्ठा b43_wldev *dev, bool on)
अणु
	अगर (on) अणु
		b43_phy_mask(dev, B43_PHY_LCN_AFE_CTL1, ~0x7);
	पूर्ण अन्यथा अणु
		b43_phy_set(dev, B43_PHY_LCN_AFE_CTL2, 0x7);
		b43_phy_set(dev, B43_PHY_LCN_AFE_CTL1, 0x7);
	पूर्ण
पूर्ण

अटल पूर्णांक b43_phy_lcn_op_चयन_channel(काष्ठा b43_wldev *dev,
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

	वापस b43_phy_lcn_set_channel(dev, channel, channel_type);
पूर्ण

अटल अचिन्हित पूर्णांक b43_phy_lcn_op_get_शेष_chan(काष्ठा b43_wldev *dev)
अणु
	अगर (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
		वापस 1;
	वापस 36;
पूर्ण

अटल क्रमागत b43_txpwr_result
b43_phy_lcn_op_recalc_txघातer(काष्ठा b43_wldev *dev, bool ignore_tssi)
अणु
	वापस B43_TXPWR_RES_DONE;
पूर्ण

अटल व्योम b43_phy_lcn_op_adjust_txघातer(काष्ठा b43_wldev *dev)
अणु
पूर्ण

/**************************************************
 * R/W ops.
 **************************************************/

अटल व्योम b43_phy_lcn_op_maskset(काष्ठा b43_wldev *dev, u16 reg, u16 mask,
				   u16 set)
अणु
	b43_ग_लिखो16f(dev, B43_MMIO_PHY_CONTROL, reg);
	b43_ग_लिखो16(dev, B43_MMIO_PHY_DATA,
		    (b43_पढ़ो16(dev, B43_MMIO_PHY_DATA) & mask) | set);
पूर्ण

अटल u16 b43_phy_lcn_op_radio_पढ़ो(काष्ठा b43_wldev *dev, u16 reg)
अणु
	/* LCN-PHY needs 0x200 क्रम पढ़ो access */
	reg |= 0x200;

	b43_ग_लिखो16f(dev, B43_MMIO_RADIO24_CONTROL, reg);
	वापस b43_पढ़ो16(dev, B43_MMIO_RADIO24_DATA);
पूर्ण

अटल व्योम b43_phy_lcn_op_radio_ग_लिखो(काष्ठा b43_wldev *dev, u16 reg,
				       u16 value)
अणु
	b43_ग_लिखो16f(dev, B43_MMIO_RADIO24_CONTROL, reg);
	b43_ग_लिखो16(dev, B43_MMIO_RADIO24_DATA, value);
पूर्ण

/**************************************************
 * PHY ops काष्ठा.
 **************************************************/

स्थिर काष्ठा b43_phy_operations b43_phyops_lcn = अणु
	.allocate		= b43_phy_lcn_op_allocate,
	.मुक्त			= b43_phy_lcn_op_मुक्त,
	.prepare_काष्ठाs	= b43_phy_lcn_op_prepare_काष्ठाs,
	.init			= b43_phy_lcn_op_init,
	.phy_maskset		= b43_phy_lcn_op_maskset,
	.radio_पढ़ो		= b43_phy_lcn_op_radio_पढ़ो,
	.radio_ग_लिखो		= b43_phy_lcn_op_radio_ग_लिखो,
	.software_rfसमाप्त	= b43_phy_lcn_op_software_rfसमाप्त,
	.चयन_analog		= b43_phy_lcn_op_चयन_analog,
	.चयन_channel		= b43_phy_lcn_op_चयन_channel,
	.get_शेष_chan	= b43_phy_lcn_op_get_शेष_chan,
	.recalc_txघातer		= b43_phy_lcn_op_recalc_txघातer,
	.adjust_txघातer		= b43_phy_lcn_op_adjust_txघातer,
पूर्ण;
