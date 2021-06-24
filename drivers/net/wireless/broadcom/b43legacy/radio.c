<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Broadcom B43legacy wireless driver

  Copyright (c) 2005 Martin Langer <martin-langer@gmx.de>,
		     Stefano Brivio <stefano.brivio@polimi.it>
		     Michael Buesch <m@bues.ch>
		     Danny van Dyk <kugelfang@gentoo.org>
		     Andreas Jaggi <andreas.jaggi@waterwave.ch>
  Copyright (c) 2007 Larry Finger <Larry.Finger@lwfinger.net>

  Some parts of the code in this file are derived from the ipw2200
  driver  Copyright(c) 2003 - 2004 Intel Corporation.


*/

#समावेश <linux/delay.h>

#समावेश "b43legacy.h"
#समावेश "main.h"
#समावेश "phy.h"
#समावेश "radio.h"
#समावेश "ilt.h"


/* Table क्रम b43legacy_radio_calibrationvalue() */
अटल स्थिर u16 rcc_table[16] = अणु
	0x0002, 0x0003, 0x0001, 0x000F,
	0x0006, 0x0007, 0x0005, 0x000F,
	0x000A, 0x000B, 0x0009, 0x000F,
	0x000E, 0x000F, 0x000D, 0x000F,
पूर्ण;

/* Reverse the bits of a 4bit value.
 * Example:  1101 is flipped 1011
 */
अटल u16 flip_4bit(u16 value)
अणु
	u16 flipped = 0x0000;

	B43legacy_BUG_ON(!((value & ~0x000F) == 0x0000));

	flipped |= (value & 0x0001) << 3;
	flipped |= (value & 0x0002) << 1;
	flipped |= (value & 0x0004) >> 1;
	flipped |= (value & 0x0008) >> 3;

	वापस flipped;
पूर्ण

/* Get the freq, as it has to be written to the device. */
अटल अंतरभूत
u16 channel2freq_bg(u8 channel)
अणु
	/* Frequencies are given as frequencies_bg[index] + 2.4GHz
	 * Starting with channel 1
	 */
	अटल स्थिर u16 frequencies_bg[14] = अणु
		12, 17, 22, 27,
		32, 37, 42, 47,
		52, 57, 62, 67,
		72, 84,
	पूर्ण;

	अगर (unlikely(channel < 1 || channel > 14)) अणु
		prपूर्णांकk(KERN_INFO "b43legacy: Channel %d is out of range\n",
				  channel);
		dump_stack();
		वापस 2412;
	पूर्ण

	वापस frequencies_bg[channel - 1];
पूर्ण

व्योम b43legacy_radio_lock(काष्ठा b43legacy_wldev *dev)
अणु
	u32 status;

	status = b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCTL);
	B43legacy_WARN_ON(status & B43legacy_MACCTL_RADIOLOCK);
	status |= B43legacy_MACCTL_RADIOLOCK;
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_MACCTL, status);
	udelay(10);
पूर्ण

व्योम b43legacy_radio_unlock(काष्ठा b43legacy_wldev *dev)
अणु
	u32 status;

	b43legacy_पढ़ो16(dev, B43legacy_MMIO_PHY_VER); /* dummy पढ़ो */
	status = b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCTL);
	B43legacy_WARN_ON(!(status & B43legacy_MACCTL_RADIOLOCK));
	status &= ~B43legacy_MACCTL_RADIOLOCK;
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_MACCTL, status);
पूर्ण

u16 b43legacy_radio_पढ़ो16(काष्ठा b43legacy_wldev *dev, u16 offset)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;

	चयन (phy->type) अणु
	हाल B43legacy_PHYTYPE_B:
		अगर (phy->radio_ver == 0x2053) अणु
			अगर (offset < 0x70)
				offset += 0x80;
			अन्यथा अगर (offset < 0x80)
				offset += 0x70;
		पूर्ण अन्यथा अगर (phy->radio_ver == 0x2050)
			offset |= 0x80;
		अन्यथा
			B43legacy_WARN_ON(1);
		अवरोध;
	हाल B43legacy_PHYTYPE_G:
		offset |= 0x80;
		अवरोध;
	शेष:
		B43legacy_BUG_ON(1);
	पूर्ण

	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_RADIO_CONTROL, offset);
	वापस b43legacy_पढ़ो16(dev, B43legacy_MMIO_RADIO_DATA_LOW);
पूर्ण

व्योम b43legacy_radio_ग_लिखो16(काष्ठा b43legacy_wldev *dev, u16 offset, u16 val)
अणु
	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_RADIO_CONTROL, offset);
	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_RADIO_DATA_LOW, val);
पूर्ण

अटल व्योम b43legacy_set_all_gains(काष्ठा b43legacy_wldev *dev,
				  s16 first, s16 second, s16 third)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 i;
	u16 start = 0x08;
	u16 end = 0x18;
	u16 offset = 0x0400;
	u16 पंचांगp;

	अगर (phy->rev <= 1) अणु
		offset = 0x5000;
		start = 0x10;
		end = 0x20;
	पूर्ण

	क्रम (i = 0; i < 4; i++)
		b43legacy_ilt_ग_लिखो(dev, offset + i, first);

	क्रम (i = start; i < end; i++)
		b43legacy_ilt_ग_लिखो(dev, offset + i, second);

	अगर (third != -1) अणु
		पंचांगp = ((u16)third << 14) | ((u16)third << 6);
		b43legacy_phy_ग_लिखो(dev, 0x04A0,
				    (b43legacy_phy_पढ़ो(dev, 0x04A0) & 0xBFBF)
				    | पंचांगp);
		b43legacy_phy_ग_लिखो(dev, 0x04A1,
				    (b43legacy_phy_पढ़ो(dev, 0x04A1) & 0xBFBF)
				    | पंचांगp);
		b43legacy_phy_ग_लिखो(dev, 0x04A2,
				    (b43legacy_phy_पढ़ो(dev, 0x04A2) & 0xBFBF)
				    | पंचांगp);
	पूर्ण
	b43legacy_dummy_transmission(dev);
पूर्ण

अटल व्योम b43legacy_set_original_gains(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 i;
	u16 पंचांगp;
	u16 offset = 0x0400;
	u16 start = 0x0008;
	u16 end = 0x0018;

	अगर (phy->rev <= 1) अणु
		offset = 0x5000;
		start = 0x0010;
		end = 0x0020;
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		पंचांगp = (i & 0xFFFC);
		पंचांगp |= (i & 0x0001) << 1;
		पंचांगp |= (i & 0x0002) >> 1;

		b43legacy_ilt_ग_लिखो(dev, offset + i, पंचांगp);
	पूर्ण

	क्रम (i = start; i < end; i++)
		b43legacy_ilt_ग_लिखो(dev, offset + i, i - start);

	b43legacy_phy_ग_लिखो(dev, 0x04A0,
			    (b43legacy_phy_पढ़ो(dev, 0x04A0) & 0xBFBF)
			    | 0x4040);
	b43legacy_phy_ग_लिखो(dev, 0x04A1,
			    (b43legacy_phy_पढ़ो(dev, 0x04A1) & 0xBFBF)
			    | 0x4040);
	b43legacy_phy_ग_लिखो(dev, 0x04A2,
			    (b43legacy_phy_पढ़ो(dev, 0x04A2) & 0xBFBF)
			    | 0x4000);
	b43legacy_dummy_transmission(dev);
पूर्ण

/* Synthetic PU workaround */
अटल व्योम b43legacy_synth_pu_workaround(काष्ठा b43legacy_wldev *dev,
					  u8 channel)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;

	might_sleep();

	अगर (phy->radio_ver != 0x2050 || phy->radio_rev >= 6)
		/* We करो not need the workaround. */
		वापस;

	अगर (channel <= 10)
		b43legacy_ग_लिखो16(dev, B43legacy_MMIO_CHANNEL,
				  channel2freq_bg(channel + 4));
	अन्यथा
		b43legacy_ग_लिखो16(dev, B43legacy_MMIO_CHANNEL,
				  channel2freq_bg(channel));
	msleep(1);
	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_CHANNEL,
			  channel2freq_bg(channel));
पूर्ण

u8 b43legacy_radio_aci_detect(काष्ठा b43legacy_wldev *dev, u8 channel)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u8 ret = 0;
	u16 saved;
	u16 rssi;
	u16 temp;
	पूर्णांक i;
	पूर्णांक j = 0;

	saved = b43legacy_phy_पढ़ो(dev, 0x0403);
	b43legacy_radio_selectchannel(dev, channel, 0);
	b43legacy_phy_ग_लिखो(dev, 0x0403, (saved & 0xFFF8) | 5);
	अगर (phy->aci_hw_rssi)
		rssi = b43legacy_phy_पढ़ो(dev, 0x048A) & 0x3F;
	अन्यथा
		rssi = saved & 0x3F;
	/* clamp temp to चिन्हित 5bit */
	अगर (rssi > 32)
		rssi -= 64;
	क्रम (i = 0; i < 100; i++) अणु
		temp = (b43legacy_phy_पढ़ो(dev, 0x047F) >> 8) & 0x3F;
		अगर (temp > 32)
			temp -= 64;
		अगर (temp < rssi)
			j++;
		अगर (j >= 20)
			ret = 1;
	पूर्ण
	b43legacy_phy_ग_लिखो(dev, 0x0403, saved);

	वापस ret;
पूर्ण

u8 b43legacy_radio_aci_scan(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u8 ret[13] = अणु 0 पूर्ण;
	अचिन्हित पूर्णांक channel = phy->channel;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक j;
	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक end;

	अगर (!((phy->type == B43legacy_PHYTYPE_G) && (phy->rev > 0)))
		वापस 0;

	b43legacy_phy_lock(dev);
	b43legacy_radio_lock(dev);
	b43legacy_phy_ग_लिखो(dev, 0x0802,
			    b43legacy_phy_पढ़ो(dev, 0x0802) & 0xFFFC);
	b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_G_CRS,
			    b43legacy_phy_पढ़ो(dev, B43legacy_PHY_G_CRS)
			    & 0x7FFF);
	b43legacy_set_all_gains(dev, 3, 8, 1);

	start = (channel - 5 > 0) ? channel - 5 : 1;
	end = (channel + 5 < 14) ? channel + 5 : 13;

	क्रम (i = start; i <= end; i++) अणु
		अगर (असल(channel - i) > 2)
			ret[i-1] = b43legacy_radio_aci_detect(dev, i);
	पूर्ण
	b43legacy_radio_selectchannel(dev, channel, 0);
	b43legacy_phy_ग_लिखो(dev, 0x0802,
			    (b43legacy_phy_पढ़ो(dev, 0x0802) & 0xFFFC)
			    | 0x0003);
	b43legacy_phy_ग_लिखो(dev, 0x0403,
			    b43legacy_phy_पढ़ो(dev, 0x0403) & 0xFFF8);
	b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_G_CRS,
			    b43legacy_phy_पढ़ो(dev, B43legacy_PHY_G_CRS)
			    | 0x8000);
	b43legacy_set_original_gains(dev);
	क्रम (i = 0; i < 13; i++) अणु
		अगर (!ret[i])
			जारी;
		end = (i + 5 < 13) ? i + 5 : 13;
		क्रम (j = i; j < end; j++)
			ret[j] = 1;
	पूर्ण
	b43legacy_radio_unlock(dev);
	b43legacy_phy_unlock(dev);

	वापस ret[channel - 1];
पूर्ण

/* https://bcm-specs.sipsolutions.net/NRSSILookupTable */
व्योम b43legacy_nrssi_hw_ग_लिखो(काष्ठा b43legacy_wldev *dev, u16 offset, s16 val)
अणु
	b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_NRSSILT_CTRL, offset);
	b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_NRSSILT_DATA, (u16)val);
पूर्ण

/* https://bcm-specs.sipsolutions.net/NRSSILookupTable */
s16 b43legacy_nrssi_hw_पढ़ो(काष्ठा b43legacy_wldev *dev, u16 offset)
अणु
	u16 val;

	b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_NRSSILT_CTRL, offset);
	val = b43legacy_phy_पढ़ो(dev, B43legacy_PHY_NRSSILT_DATA);

	वापस (s16)val;
पूर्ण

/* https://bcm-specs.sipsolutions.net/NRSSILookupTable */
व्योम b43legacy_nrssi_hw_update(काष्ठा b43legacy_wldev *dev, u16 val)
अणु
	u16 i;
	s16 पंचांगp;

	क्रम (i = 0; i < 64; i++) अणु
		पंचांगp = b43legacy_nrssi_hw_पढ़ो(dev, i);
		पंचांगp -= val;
		पंचांगp = clamp_val(पंचांगp, -32, 31);
		b43legacy_nrssi_hw_ग_लिखो(dev, i, पंचांगp);
	पूर्ण
पूर्ण

/* https://bcm-specs.sipsolutions.net/NRSSILookupTable */
व्योम b43legacy_nrssi_mem_update(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	s16 i;
	s16 delta;
	s32 पंचांगp;

	delta = 0x1F - phy->nrssi[0];
	क्रम (i = 0; i < 64; i++) अणु
		पंचांगp = (i - delta) * phy->nrssislope;
		पंचांगp /= 0x10000;
		पंचांगp += 0x3A;
		पंचांगp = clamp_val(पंचांगp, 0, 0x3F);
		phy->nrssi_lt[i] = पंचांगp;
	पूर्ण
पूर्ण

अटल व्योम b43legacy_calc_nrssi_offset(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 backup[20] = अणु 0 पूर्ण;
	s16 v47F;
	u16 i;
	u16 saved = 0xFFFF;

	backup[0] = b43legacy_phy_पढ़ो(dev, 0x0001);
	backup[1] = b43legacy_phy_पढ़ो(dev, 0x0811);
	backup[2] = b43legacy_phy_पढ़ो(dev, 0x0812);
	backup[3] = b43legacy_phy_पढ़ो(dev, 0x0814);
	backup[4] = b43legacy_phy_पढ़ो(dev, 0x0815);
	backup[5] = b43legacy_phy_पढ़ो(dev, 0x005A);
	backup[6] = b43legacy_phy_पढ़ो(dev, 0x0059);
	backup[7] = b43legacy_phy_पढ़ो(dev, 0x0058);
	backup[8] = b43legacy_phy_पढ़ो(dev, 0x000A);
	backup[9] = b43legacy_phy_पढ़ो(dev, 0x0003);
	backup[10] = b43legacy_radio_पढ़ो16(dev, 0x007A);
	backup[11] = b43legacy_radio_पढ़ो16(dev, 0x0043);

	b43legacy_phy_ग_लिखो(dev, 0x0429,
			    b43legacy_phy_पढ़ो(dev, 0x0429) & 0x7FFF);
	b43legacy_phy_ग_लिखो(dev, 0x0001,
			    (b43legacy_phy_पढ़ो(dev, 0x0001) & 0x3FFF)
			    | 0x4000);
	b43legacy_phy_ग_लिखो(dev, 0x0811,
			    b43legacy_phy_पढ़ो(dev, 0x0811) | 0x000C);
	b43legacy_phy_ग_लिखो(dev, 0x0812,
			    (b43legacy_phy_पढ़ो(dev, 0x0812) & 0xFFF3)
			    | 0x0004);
	b43legacy_phy_ग_लिखो(dev, 0x0802,
			    b43legacy_phy_पढ़ो(dev, 0x0802) & ~(0x1 | 0x2));
	अगर (phy->rev >= 6) अणु
		backup[12] = b43legacy_phy_पढ़ो(dev, 0x002E);
		backup[13] = b43legacy_phy_पढ़ो(dev, 0x002F);
		backup[14] = b43legacy_phy_पढ़ो(dev, 0x080F);
		backup[15] = b43legacy_phy_पढ़ो(dev, 0x0810);
		backup[16] = b43legacy_phy_पढ़ो(dev, 0x0801);
		backup[17] = b43legacy_phy_पढ़ो(dev, 0x0060);
		backup[18] = b43legacy_phy_पढ़ो(dev, 0x0014);
		backup[19] = b43legacy_phy_पढ़ो(dev, 0x0478);

		b43legacy_phy_ग_लिखो(dev, 0x002E, 0);
		b43legacy_phy_ग_लिखो(dev, 0x002F, 0);
		b43legacy_phy_ग_लिखो(dev, 0x080F, 0);
		b43legacy_phy_ग_लिखो(dev, 0x0810, 0);
		b43legacy_phy_ग_लिखो(dev, 0x0478,
				    b43legacy_phy_पढ़ो(dev, 0x0478) | 0x0100);
		b43legacy_phy_ग_लिखो(dev, 0x0801,
				    b43legacy_phy_पढ़ो(dev, 0x0801) | 0x0040);
		b43legacy_phy_ग_लिखो(dev, 0x0060,
				    b43legacy_phy_पढ़ो(dev, 0x0060) | 0x0040);
		b43legacy_phy_ग_लिखो(dev, 0x0014,
				    b43legacy_phy_पढ़ो(dev, 0x0014) | 0x0200);
	पूर्ण
	b43legacy_radio_ग_लिखो16(dev, 0x007A,
				b43legacy_radio_पढ़ो16(dev, 0x007A) | 0x0070);
	b43legacy_radio_ग_लिखो16(dev, 0x007A,
				b43legacy_radio_पढ़ो16(dev, 0x007A) | 0x0080);
	udelay(30);

	v47F = (s16)((b43legacy_phy_पढ़ो(dev, 0x047F) >> 8) & 0x003F);
	अगर (v47F >= 0x20)
		v47F -= 0x40;
	अगर (v47F == 31) अणु
		क्रम (i = 7; i >= 4; i--) अणु
			b43legacy_radio_ग_लिखो16(dev, 0x007B, i);
			udelay(20);
			v47F = (s16)((b43legacy_phy_पढ़ो(dev, 0x047F) >> 8)
							 & 0x003F);
			अगर (v47F >= 0x20)
				v47F -= 0x40;
			अगर (v47F < 31 && saved == 0xFFFF)
				saved = i;
		पूर्ण
		अगर (saved == 0xFFFF)
			saved = 4;
	पूर्ण अन्यथा अणु
		b43legacy_radio_ग_लिखो16(dev, 0x007A,
					b43legacy_radio_पढ़ो16(dev, 0x007A)
					& 0x007F);
		b43legacy_phy_ग_लिखो(dev, 0x0814,
				    b43legacy_phy_पढ़ो(dev, 0x0814) | 0x0001);
		b43legacy_phy_ग_लिखो(dev, 0x0815,
				    b43legacy_phy_पढ़ो(dev, 0x0815) & 0xFFFE);
		b43legacy_phy_ग_लिखो(dev, 0x0811,
				    b43legacy_phy_पढ़ो(dev, 0x0811) | 0x000C);
		b43legacy_phy_ग_लिखो(dev, 0x0812,
				    b43legacy_phy_पढ़ो(dev, 0x0812) | 0x000C);
		b43legacy_phy_ग_लिखो(dev, 0x0811,
				    b43legacy_phy_पढ़ो(dev, 0x0811) | 0x0030);
		b43legacy_phy_ग_लिखो(dev, 0x0812,
				    b43legacy_phy_पढ़ो(dev, 0x0812) | 0x0030);
		b43legacy_phy_ग_लिखो(dev, 0x005A, 0x0480);
		b43legacy_phy_ग_लिखो(dev, 0x0059, 0x0810);
		b43legacy_phy_ग_लिखो(dev, 0x0058, 0x000D);
		अगर (phy->analog == 0)
			b43legacy_phy_ग_लिखो(dev, 0x0003, 0x0122);
		अन्यथा
			b43legacy_phy_ग_लिखो(dev, 0x000A,
					    b43legacy_phy_पढ़ो(dev, 0x000A)
					    | 0x2000);
		b43legacy_phy_ग_लिखो(dev, 0x0814,
				    b43legacy_phy_पढ़ो(dev, 0x0814) | 0x0004);
		b43legacy_phy_ग_लिखो(dev, 0x0815,
				    b43legacy_phy_पढ़ो(dev, 0x0815) & 0xFFFB);
		b43legacy_phy_ग_लिखो(dev, 0x0003,
				    (b43legacy_phy_पढ़ो(dev, 0x0003) & 0xFF9F)
				    | 0x0040);
		b43legacy_radio_ग_लिखो16(dev, 0x007A,
					b43legacy_radio_पढ़ो16(dev, 0x007A)
					| 0x000F);
		b43legacy_set_all_gains(dev, 3, 0, 1);
		b43legacy_radio_ग_लिखो16(dev, 0x0043,
					(b43legacy_radio_पढ़ो16(dev, 0x0043)
					& 0x00F0) | 0x000F);
		udelay(30);
		v47F = (s16)((b43legacy_phy_पढ़ो(dev, 0x047F) >> 8) & 0x003F);
		अगर (v47F >= 0x20)
			v47F -= 0x40;
		अगर (v47F == -32) अणु
			क्रम (i = 0; i < 4; i++) अणु
				b43legacy_radio_ग_लिखो16(dev, 0x007B, i);
				udelay(20);
				v47F = (s16)((b43legacy_phy_पढ़ो(dev, 0x047F) >>
								 8) & 0x003F);
				अगर (v47F >= 0x20)
					v47F -= 0x40;
				अगर (v47F > -31 && saved == 0xFFFF)
					saved = i;
			पूर्ण
			अगर (saved == 0xFFFF)
				saved = 3;
		पूर्ण अन्यथा
			saved = 0;
	पूर्ण
	b43legacy_radio_ग_लिखो16(dev, 0x007B, saved);

	अगर (phy->rev >= 6) अणु
		b43legacy_phy_ग_लिखो(dev, 0x002E, backup[12]);
		b43legacy_phy_ग_लिखो(dev, 0x002F, backup[13]);
		b43legacy_phy_ग_लिखो(dev, 0x080F, backup[14]);
		b43legacy_phy_ग_लिखो(dev, 0x0810, backup[15]);
	पूर्ण
	b43legacy_phy_ग_लिखो(dev, 0x0814, backup[3]);
	b43legacy_phy_ग_लिखो(dev, 0x0815, backup[4]);
	b43legacy_phy_ग_लिखो(dev, 0x005A, backup[5]);
	b43legacy_phy_ग_लिखो(dev, 0x0059, backup[6]);
	b43legacy_phy_ग_लिखो(dev, 0x0058, backup[7]);
	b43legacy_phy_ग_लिखो(dev, 0x000A, backup[8]);
	b43legacy_phy_ग_लिखो(dev, 0x0003, backup[9]);
	b43legacy_radio_ग_लिखो16(dev, 0x0043, backup[11]);
	b43legacy_radio_ग_लिखो16(dev, 0x007A, backup[10]);
	b43legacy_phy_ग_लिखो(dev, 0x0802,
			    b43legacy_phy_पढ़ो(dev, 0x0802) | 0x1 | 0x2);
	b43legacy_phy_ग_लिखो(dev, 0x0429,
			    b43legacy_phy_पढ़ो(dev, 0x0429) | 0x8000);
	b43legacy_set_original_gains(dev);
	अगर (phy->rev >= 6) अणु
		b43legacy_phy_ग_लिखो(dev, 0x0801, backup[16]);
		b43legacy_phy_ग_लिखो(dev, 0x0060, backup[17]);
		b43legacy_phy_ग_लिखो(dev, 0x0014, backup[18]);
		b43legacy_phy_ग_लिखो(dev, 0x0478, backup[19]);
	पूर्ण
	b43legacy_phy_ग_लिखो(dev, 0x0001, backup[0]);
	b43legacy_phy_ग_लिखो(dev, 0x0812, backup[2]);
	b43legacy_phy_ग_लिखो(dev, 0x0811, backup[1]);
पूर्ण

व्योम b43legacy_calc_nrssi_slope(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 backup[18] = अणु 0 पूर्ण;
	u16 पंचांगp;
	s16 nrssi0;
	s16 nrssi1;

	चयन (phy->type) अणु
	हाल B43legacy_PHYTYPE_B:
		backup[0] = b43legacy_radio_पढ़ो16(dev, 0x007A);
		backup[1] = b43legacy_radio_पढ़ो16(dev, 0x0052);
		backup[2] = b43legacy_radio_पढ़ो16(dev, 0x0043);
		backup[3] = b43legacy_phy_पढ़ो(dev, 0x0030);
		backup[4] = b43legacy_phy_पढ़ो(dev, 0x0026);
		backup[5] = b43legacy_phy_पढ़ो(dev, 0x0015);
		backup[6] = b43legacy_phy_पढ़ो(dev, 0x002A);
		backup[7] = b43legacy_phy_पढ़ो(dev, 0x0020);
		backup[8] = b43legacy_phy_पढ़ो(dev, 0x005A);
		backup[9] = b43legacy_phy_पढ़ो(dev, 0x0059);
		backup[10] = b43legacy_phy_पढ़ो(dev, 0x0058);
		backup[11] = b43legacy_पढ़ो16(dev, 0x03E2);
		backup[12] = b43legacy_पढ़ो16(dev, 0x03E6);
		backup[13] = b43legacy_पढ़ो16(dev, B43legacy_MMIO_CHANNEL_EXT);

		पंचांगp  = b43legacy_radio_पढ़ो16(dev, 0x007A);
		पंचांगp &= (phy->rev >= 5) ? 0x007F : 0x000F;
		b43legacy_radio_ग_लिखो16(dev, 0x007A, पंचांगp);
		b43legacy_phy_ग_लिखो(dev, 0x0030, 0x00FF);
		b43legacy_ग_लिखो16(dev, 0x03EC, 0x7F7F);
		b43legacy_phy_ग_लिखो(dev, 0x0026, 0x0000);
		b43legacy_phy_ग_लिखो(dev, 0x0015,
				    b43legacy_phy_पढ़ो(dev, 0x0015) | 0x0020);
		b43legacy_phy_ग_लिखो(dev, 0x002A, 0x08A3);
		b43legacy_radio_ग_लिखो16(dev, 0x007A,
					b43legacy_radio_पढ़ो16(dev, 0x007A)
					| 0x0080);

		nrssi0 = (s16)b43legacy_phy_पढ़ो(dev, 0x0027);
		b43legacy_radio_ग_लिखो16(dev, 0x007A,
					b43legacy_radio_पढ़ो16(dev, 0x007A)
					& 0x007F);
		अगर (phy->analog >= 2)
			b43legacy_ग_लिखो16(dev, 0x03E6, 0x0040);
		अन्यथा अगर (phy->analog == 0)
			b43legacy_ग_लिखो16(dev, 0x03E6, 0x0122);
		अन्यथा
			b43legacy_ग_लिखो16(dev, B43legacy_MMIO_CHANNEL_EXT,
					  b43legacy_पढ़ो16(dev,
					  B43legacy_MMIO_CHANNEL_EXT) & 0x2000);
		b43legacy_phy_ग_लिखो(dev, 0x0020, 0x3F3F);
		b43legacy_phy_ग_लिखो(dev, 0x0015, 0xF330);
		b43legacy_radio_ग_लिखो16(dev, 0x005A, 0x0060);
		b43legacy_radio_ग_लिखो16(dev, 0x0043,
					b43legacy_radio_पढ़ो16(dev, 0x0043)
					& 0x00F0);
		b43legacy_phy_ग_लिखो(dev, 0x005A, 0x0480);
		b43legacy_phy_ग_लिखो(dev, 0x0059, 0x0810);
		b43legacy_phy_ग_लिखो(dev, 0x0058, 0x000D);
		udelay(20);

		nrssi1 = (s16)b43legacy_phy_पढ़ो(dev, 0x0027);
		b43legacy_phy_ग_लिखो(dev, 0x0030, backup[3]);
		b43legacy_radio_ग_लिखो16(dev, 0x007A, backup[0]);
		b43legacy_ग_लिखो16(dev, 0x03E2, backup[11]);
		b43legacy_phy_ग_लिखो(dev, 0x0026, backup[4]);
		b43legacy_phy_ग_लिखो(dev, 0x0015, backup[5]);
		b43legacy_phy_ग_लिखो(dev, 0x002A, backup[6]);
		b43legacy_synth_pu_workaround(dev, phy->channel);
		अगर (phy->analog != 0)
			b43legacy_ग_लिखो16(dev, 0x03F4, backup[13]);

		b43legacy_phy_ग_लिखो(dev, 0x0020, backup[7]);
		b43legacy_phy_ग_लिखो(dev, 0x005A, backup[8]);
		b43legacy_phy_ग_लिखो(dev, 0x0059, backup[9]);
		b43legacy_phy_ग_लिखो(dev, 0x0058, backup[10]);
		b43legacy_radio_ग_लिखो16(dev, 0x0052, backup[1]);
		b43legacy_radio_ग_लिखो16(dev, 0x0043, backup[2]);

		अगर (nrssi0 == nrssi1)
			phy->nrssislope = 0x00010000;
		अन्यथा
			phy->nrssislope = 0x00400000 / (nrssi0 - nrssi1);

		अगर (nrssi0 <= -4) अणु
			phy->nrssi[0] = nrssi0;
			phy->nrssi[1] = nrssi1;
		पूर्ण
		अवरोध;
	हाल B43legacy_PHYTYPE_G:
		अगर (phy->radio_rev >= 9)
			वापस;
		अगर (phy->radio_rev == 8)
			b43legacy_calc_nrssi_offset(dev);

		b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_G_CRS,
				    b43legacy_phy_पढ़ो(dev, B43legacy_PHY_G_CRS)
				    & 0x7FFF);
		b43legacy_phy_ग_लिखो(dev, 0x0802,
				    b43legacy_phy_पढ़ो(dev, 0x0802) & 0xFFFC);
		backup[7] = b43legacy_पढ़ो16(dev, 0x03E2);
		b43legacy_ग_लिखो16(dev, 0x03E2,
				  b43legacy_पढ़ो16(dev, 0x03E2) | 0x8000);
		backup[0] = b43legacy_radio_पढ़ो16(dev, 0x007A);
		backup[1] = b43legacy_radio_पढ़ो16(dev, 0x0052);
		backup[2] = b43legacy_radio_पढ़ो16(dev, 0x0043);
		backup[3] = b43legacy_phy_पढ़ो(dev, 0x0015);
		backup[4] = b43legacy_phy_पढ़ो(dev, 0x005A);
		backup[5] = b43legacy_phy_पढ़ो(dev, 0x0059);
		backup[6] = b43legacy_phy_पढ़ो(dev, 0x0058);
		backup[8] = b43legacy_पढ़ो16(dev, 0x03E6);
		backup[9] = b43legacy_पढ़ो16(dev, B43legacy_MMIO_CHANNEL_EXT);
		अगर (phy->rev >= 3) अणु
			backup[10] = b43legacy_phy_पढ़ो(dev, 0x002E);
			backup[11] = b43legacy_phy_पढ़ो(dev, 0x002F);
			backup[12] = b43legacy_phy_पढ़ो(dev, 0x080F);
			backup[13] = b43legacy_phy_पढ़ो(dev,
						B43legacy_PHY_G_LO_CONTROL);
			backup[14] = b43legacy_phy_पढ़ो(dev, 0x0801);
			backup[15] = b43legacy_phy_पढ़ो(dev, 0x0060);
			backup[16] = b43legacy_phy_पढ़ो(dev, 0x0014);
			backup[17] = b43legacy_phy_पढ़ो(dev, 0x0478);
			b43legacy_phy_ग_लिखो(dev, 0x002E, 0);
			b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_G_LO_CONTROL, 0);
			चयन (phy->rev) अणु
			हाल 4: हाल 6: हाल 7:
				b43legacy_phy_ग_लिखो(dev, 0x0478,
						    b43legacy_phy_पढ़ो(dev,
						    0x0478) | 0x0100);
				b43legacy_phy_ग_लिखो(dev, 0x0801,
						    b43legacy_phy_पढ़ो(dev,
						    0x0801) | 0x0040);
				अवरोध;
			हाल 3: हाल 5:
				b43legacy_phy_ग_लिखो(dev, 0x0801,
						    b43legacy_phy_पढ़ो(dev,
						    0x0801) & 0xFFBF);
				अवरोध;
			पूर्ण
			b43legacy_phy_ग_लिखो(dev, 0x0060,
					    b43legacy_phy_पढ़ो(dev, 0x0060)
					    | 0x0040);
			b43legacy_phy_ग_लिखो(dev, 0x0014,
					    b43legacy_phy_पढ़ो(dev, 0x0014)
					    | 0x0200);
		पूर्ण
		b43legacy_radio_ग_लिखो16(dev, 0x007A,
					b43legacy_radio_पढ़ो16(dev, 0x007A)
					| 0x0070);
		b43legacy_set_all_gains(dev, 0, 8, 0);
		b43legacy_radio_ग_लिखो16(dev, 0x007A,
					b43legacy_radio_पढ़ो16(dev, 0x007A)
					& 0x00F7);
		अगर (phy->rev >= 2) अणु
			b43legacy_phy_ग_लिखो(dev, 0x0811,
					    (b43legacy_phy_पढ़ो(dev, 0x0811)
					    & 0xFFCF) | 0x0030);
			b43legacy_phy_ग_लिखो(dev, 0x0812,
					    (b43legacy_phy_पढ़ो(dev, 0x0812)
					    & 0xFFCF) | 0x0010);
		पूर्ण
		b43legacy_radio_ग_लिखो16(dev, 0x007A,
					b43legacy_radio_पढ़ो16(dev, 0x007A)
					| 0x0080);
		udelay(20);

		nrssi0 = (s16)((b43legacy_phy_पढ़ो(dev, 0x047F) >> 8) & 0x003F);
		अगर (nrssi0 >= 0x0020)
			nrssi0 -= 0x0040;

		b43legacy_radio_ग_लिखो16(dev, 0x007A,
					b43legacy_radio_पढ़ो16(dev, 0x007A)
					& 0x007F);
		अगर (phy->analog >= 2)
			b43legacy_phy_ग_लिखो(dev, 0x0003,
					    (b43legacy_phy_पढ़ो(dev, 0x0003)
					    & 0xFF9F) | 0x0040);

		b43legacy_ग_लिखो16(dev, B43legacy_MMIO_CHANNEL_EXT,
				  b43legacy_पढ़ो16(dev,
				  B43legacy_MMIO_CHANNEL_EXT) | 0x2000);
		b43legacy_radio_ग_लिखो16(dev, 0x007A,
					b43legacy_radio_पढ़ो16(dev, 0x007A)
					| 0x000F);
		b43legacy_phy_ग_लिखो(dev, 0x0015, 0xF330);
		अगर (phy->rev >= 2) अणु
			b43legacy_phy_ग_लिखो(dev, 0x0812,
					    (b43legacy_phy_पढ़ो(dev, 0x0812)
					    & 0xFFCF) | 0x0020);
			b43legacy_phy_ग_लिखो(dev, 0x0811,
					    (b43legacy_phy_पढ़ो(dev, 0x0811)
					    & 0xFFCF) | 0x0020);
		पूर्ण

		b43legacy_set_all_gains(dev, 3, 0, 1);
		अगर (phy->radio_rev == 8)
			b43legacy_radio_ग_लिखो16(dev, 0x0043, 0x001F);
		अन्यथा अणु
			पंचांगp = b43legacy_radio_पढ़ो16(dev, 0x0052) & 0xFF0F;
			b43legacy_radio_ग_लिखो16(dev, 0x0052, पंचांगp | 0x0060);
			पंचांगp = b43legacy_radio_पढ़ो16(dev, 0x0043) & 0xFFF0;
			b43legacy_radio_ग_लिखो16(dev, 0x0043, पंचांगp | 0x0009);
		पूर्ण
		b43legacy_phy_ग_लिखो(dev, 0x005A, 0x0480);
		b43legacy_phy_ग_लिखो(dev, 0x0059, 0x0810);
		b43legacy_phy_ग_लिखो(dev, 0x0058, 0x000D);
		udelay(20);
		nrssi1 = (s16)((b43legacy_phy_पढ़ो(dev, 0x047F) >> 8) & 0x003F);
		अगर (nrssi1 >= 0x0020)
			nrssi1 -= 0x0040;
		अगर (nrssi0 == nrssi1)
			phy->nrssislope = 0x00010000;
		अन्यथा
			phy->nrssislope = 0x00400000 / (nrssi0 - nrssi1);
		अगर (nrssi0 >= -4) अणु
			phy->nrssi[0] = nrssi1;
			phy->nrssi[1] = nrssi0;
		पूर्ण
		अगर (phy->rev >= 3) अणु
			b43legacy_phy_ग_लिखो(dev, 0x002E, backup[10]);
			b43legacy_phy_ग_लिखो(dev, 0x002F, backup[11]);
			b43legacy_phy_ग_लिखो(dev, 0x080F, backup[12]);
			b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_G_LO_CONTROL,
					    backup[13]);
		पूर्ण
		अगर (phy->rev >= 2) अणु
			b43legacy_phy_ग_लिखो(dev, 0x0812,
					    b43legacy_phy_पढ़ो(dev, 0x0812)
					    & 0xFFCF);
			b43legacy_phy_ग_लिखो(dev, 0x0811,
					    b43legacy_phy_पढ़ो(dev, 0x0811)
					    & 0xFFCF);
		पूर्ण

		b43legacy_radio_ग_लिखो16(dev, 0x007A, backup[0]);
		b43legacy_radio_ग_लिखो16(dev, 0x0052, backup[1]);
		b43legacy_radio_ग_लिखो16(dev, 0x0043, backup[2]);
		b43legacy_ग_लिखो16(dev, 0x03E2, backup[7]);
		b43legacy_ग_लिखो16(dev, 0x03E6, backup[8]);
		b43legacy_ग_लिखो16(dev, B43legacy_MMIO_CHANNEL_EXT, backup[9]);
		b43legacy_phy_ग_लिखो(dev, 0x0015, backup[3]);
		b43legacy_phy_ग_लिखो(dev, 0x005A, backup[4]);
		b43legacy_phy_ग_लिखो(dev, 0x0059, backup[5]);
		b43legacy_phy_ग_लिखो(dev, 0x0058, backup[6]);
		b43legacy_synth_pu_workaround(dev, phy->channel);
		b43legacy_phy_ग_लिखो(dev, 0x0802,
				    b43legacy_phy_पढ़ो(dev, 0x0802) | 0x0003);
		b43legacy_set_original_gains(dev);
		b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_G_CRS,
				    b43legacy_phy_पढ़ो(dev, B43legacy_PHY_G_CRS)
				    | 0x8000);
		अगर (phy->rev >= 3) अणु
			b43legacy_phy_ग_लिखो(dev, 0x0801, backup[14]);
			b43legacy_phy_ग_लिखो(dev, 0x0060, backup[15]);
			b43legacy_phy_ग_लिखो(dev, 0x0014, backup[16]);
			b43legacy_phy_ग_लिखो(dev, 0x0478, backup[17]);
		पूर्ण
		b43legacy_nrssi_mem_update(dev);
		b43legacy_calc_nrssi_threshold(dev);
		अवरोध;
	शेष:
		B43legacy_BUG_ON(1);
	पूर्ण
पूर्ण

व्योम b43legacy_calc_nrssi_threshold(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	s32 threshold;
	s32 a;
	s32 b;
	s16 पंचांगp16;
	u16 पंचांगp_u16;

	चयन (phy->type) अणु
	हाल B43legacy_PHYTYPE_B: अणु
		अगर (phy->radio_ver != 0x2050)
			वापस;
		अगर (!(dev->dev->bus->sprom.boardflags_lo &
		    B43legacy_BFL_RSSI))
			वापस;

		अगर (phy->radio_rev >= 6) अणु
			threshold = (phy->nrssi[1] - phy->nrssi[0]) * 32;
			threshold += 20 * (phy->nrssi[0] + 1);
			threshold /= 40;
		पूर्ण अन्यथा
			threshold = phy->nrssi[1] - 5;

		threshold = clamp_val(threshold, 0, 0x3E);
		b43legacy_phy_पढ़ो(dev, 0x0020); /* dummy पढ़ो */
		b43legacy_phy_ग_लिखो(dev, 0x0020, (((u16)threshold) << 8)
				    | 0x001C);

		अगर (phy->radio_rev >= 6) अणु
			b43legacy_phy_ग_लिखो(dev, 0x0087, 0x0E0D);
			b43legacy_phy_ग_लिखो(dev, 0x0086, 0x0C0B);
			b43legacy_phy_ग_लिखो(dev, 0x0085, 0x0A09);
			b43legacy_phy_ग_लिखो(dev, 0x0084, 0x0808);
			b43legacy_phy_ग_लिखो(dev, 0x0083, 0x0808);
			b43legacy_phy_ग_लिखो(dev, 0x0082, 0x0604);
			b43legacy_phy_ग_लिखो(dev, 0x0081, 0x0302);
			b43legacy_phy_ग_लिखो(dev, 0x0080, 0x0100);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल B43legacy_PHYTYPE_G:
		अगर (!phy->gmode ||
		    !(dev->dev->bus->sprom.boardflags_lo &
		    B43legacy_BFL_RSSI)) अणु
			पंचांगp16 = b43legacy_nrssi_hw_पढ़ो(dev, 0x20);
			अगर (पंचांगp16 >= 0x20)
				पंचांगp16 -= 0x40;
			अगर (पंचांगp16 < 3)
				b43legacy_phy_ग_लिखो(dev, 0x048A,
						    (b43legacy_phy_पढ़ो(dev,
						    0x048A) & 0xF000) | 0x09EB);
			अन्यथा
				b43legacy_phy_ग_लिखो(dev, 0x048A,
						    (b43legacy_phy_पढ़ो(dev,
						    0x048A) & 0xF000) | 0x0AED);
		पूर्ण अन्यथा अणु
			अगर (phy->पूर्णांकerभ_शेषe ==
			    B43legacy_RADIO_INTERFMODE_NONWLAN) अणु
				a = 0xE;
				b = 0xA;
			पूर्ण अन्यथा अगर (!phy->aci_wlan_स्वतःmatic &&
				    phy->aci_enable) अणु
				a = 0x13;
				b = 0x12;
			पूर्ण अन्यथा अणु
				a = 0xE;
				b = 0x11;
			पूर्ण

			a = a * (phy->nrssi[1] - phy->nrssi[0]);
			a += (phy->nrssi[0] << 6);
			अगर (a < 32)
				a += 31;
			अन्यथा
				a += 32;
			a = a >> 6;
			a = clamp_val(a, -31, 31);

			b = b * (phy->nrssi[1] - phy->nrssi[0]);
			b += (phy->nrssi[0] << 6);
			अगर (b < 32)
				b += 31;
			अन्यथा
				b += 32;
			b = b >> 6;
			b = clamp_val(b, -31, 31);

			पंचांगp_u16 = b43legacy_phy_पढ़ो(dev, 0x048A) & 0xF000;
			पंचांगp_u16 |= ((u32)b & 0x0000003F);
			पंचांगp_u16 |= (((u32)a & 0x0000003F) << 6);
			b43legacy_phy_ग_लिखो(dev, 0x048A, पंचांगp_u16);
		पूर्ण
		अवरोध;
	शेष:
		B43legacy_BUG_ON(1);
	पूर्ण
पूर्ण

/* Stack implementation to save/restore values from the
 * पूर्णांकerference mitigation code.
 * It is save to restore values in अक्रमom order.
 */
अटल व्योम _stack_save(u32 *_stackptr, माप_प्रकार *stackidx,
			u8 id, u16 offset, u16 value)
अणु
	u32 *stackptr = &(_stackptr[*stackidx]);

	B43legacy_WARN_ON(!((offset & 0xE000) == 0x0000));
	B43legacy_WARN_ON(!((id & 0xF8) == 0x00));
	*stackptr = offset;
	*stackptr |= ((u32)id) << 13;
	*stackptr |= ((u32)value) << 16;
	(*stackidx)++;
	B43legacy_WARN_ON(!(*stackidx < B43legacy_INTERFSTACK_SIZE));
पूर्ण

अटल u16 _stack_restore(u32 *stackptr,
			  u8 id, u16 offset)
अणु
	माप_प्रकार i;

	B43legacy_WARN_ON(!((offset & 0xE000) == 0x0000));
	B43legacy_WARN_ON(!((id & 0xF8) == 0x00));
	क्रम (i = 0; i < B43legacy_INTERFSTACK_SIZE; i++, stackptr++) अणु
		अगर ((*stackptr & 0x00001FFF) != offset)
			जारी;
		अगर (((*stackptr & 0x00007000) >> 13) != id)
			जारी;
		वापस ((*stackptr & 0xFFFF0000) >> 16);
	पूर्ण
	B43legacy_BUG_ON(1);

	वापस 0;
पूर्ण

#घोषणा phy_stacksave(offset)					\
	करो अणु							\
		_stack_save(stack, &stackidx, 0x1, (offset),	\
			    b43legacy_phy_पढ़ो(dev, (offset)));	\
	पूर्ण जबतक (0)
#घोषणा phy_stackrestore(offset)				\
	करो अणु							\
		b43legacy_phy_ग_लिखो(dev, (offset),		\
				    _stack_restore(stack, 0x1,	\
				    (offset)));			\
	पूर्ण जबतक (0)
#घोषणा radio_stacksave(offset)						\
	करो अणु								\
		_stack_save(stack, &stackidx, 0x2, (offset),		\
			    b43legacy_radio_पढ़ो16(dev, (offset)));	\
	पूर्ण जबतक (0)
#घोषणा radio_stackrestore(offset)					\
	करो अणु								\
		b43legacy_radio_ग_लिखो16(dev, (offset),			\
					_stack_restore(stack, 0x2,	\
					(offset)));			\
	पूर्ण जबतक (0)
#घोषणा ilt_stacksave(offset)					\
	करो अणु							\
		_stack_save(stack, &stackidx, 0x3, (offset),	\
			    b43legacy_ilt_पढ़ो(dev, (offset)));	\
	पूर्ण जबतक (0)
#घोषणा ilt_stackrestore(offset)				\
	करो अणु							\
		b43legacy_ilt_ग_लिखो(dev, (offset),		\
				  _stack_restore(stack, 0x3,	\
						 (offset)));	\
	पूर्ण जबतक (0)

अटल व्योम
b43legacy_radio_पूर्णांकerference_mitigation_enable(काष्ठा b43legacy_wldev *dev,
					       पूर्णांक mode)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 पंचांगp;
	u16 flipped;
	u32 पंचांगp32;
	माप_प्रकार stackidx = 0;
	u32 *stack = phy->पूर्णांकerfstack;

	चयन (mode) अणु
	हाल B43legacy_RADIO_INTERFMODE_NONWLAN:
		अगर (phy->rev != 1) अणु
			b43legacy_phy_ग_लिखो(dev, 0x042B,
					    b43legacy_phy_पढ़ो(dev, 0x042B)
					    | 0x0800);
			b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_G_CRS,
					    b43legacy_phy_पढ़ो(dev,
					    B43legacy_PHY_G_CRS) & ~0x4000);
			अवरोध;
		पूर्ण
		radio_stacksave(0x0078);
		पंचांगp = (b43legacy_radio_पढ़ो16(dev, 0x0078) & 0x001E);
		flipped = flip_4bit(पंचांगp);
		अगर (flipped < 10 && flipped >= 8)
			flipped = 7;
		अन्यथा अगर (flipped >= 10)
			flipped -= 3;
		flipped = flip_4bit(flipped);
		flipped = (flipped << 1) | 0x0020;
		b43legacy_radio_ग_लिखो16(dev, 0x0078, flipped);

		b43legacy_calc_nrssi_threshold(dev);

		phy_stacksave(0x0406);
		b43legacy_phy_ग_लिखो(dev, 0x0406, 0x7E28);

		b43legacy_phy_ग_लिखो(dev, 0x042B,
				    b43legacy_phy_पढ़ो(dev, 0x042B) | 0x0800);
		b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_RADIO_BITFIELD,
				    b43legacy_phy_पढ़ो(dev,
				    B43legacy_PHY_RADIO_BITFIELD) | 0x1000);

		phy_stacksave(0x04A0);
		b43legacy_phy_ग_लिखो(dev, 0x04A0,
				    (b43legacy_phy_पढ़ो(dev, 0x04A0) & 0xC0C0)
				    | 0x0008);
		phy_stacksave(0x04A1);
		b43legacy_phy_ग_लिखो(dev, 0x04A1,
				    (b43legacy_phy_पढ़ो(dev, 0x04A1) & 0xC0C0)
				    | 0x0605);
		phy_stacksave(0x04A2);
		b43legacy_phy_ग_लिखो(dev, 0x04A2,
				    (b43legacy_phy_पढ़ो(dev, 0x04A2) & 0xC0C0)
				    | 0x0204);
		phy_stacksave(0x04A8);
		b43legacy_phy_ग_लिखो(dev, 0x04A8,
				    (b43legacy_phy_पढ़ो(dev, 0x04A8) & 0xC0C0)
				    | 0x0803);
		phy_stacksave(0x04AB);
		b43legacy_phy_ग_लिखो(dev, 0x04AB,
				    (b43legacy_phy_पढ़ो(dev, 0x04AB) & 0xC0C0)
				    | 0x0605);

		phy_stacksave(0x04A7);
		b43legacy_phy_ग_लिखो(dev, 0x04A7, 0x0002);
		phy_stacksave(0x04A3);
		b43legacy_phy_ग_लिखो(dev, 0x04A3, 0x287A);
		phy_stacksave(0x04A9);
		b43legacy_phy_ग_लिखो(dev, 0x04A9, 0x2027);
		phy_stacksave(0x0493);
		b43legacy_phy_ग_लिखो(dev, 0x0493, 0x32F5);
		phy_stacksave(0x04AA);
		b43legacy_phy_ग_लिखो(dev, 0x04AA, 0x2027);
		phy_stacksave(0x04AC);
		b43legacy_phy_ग_लिखो(dev, 0x04AC, 0x32F5);
		अवरोध;
	हाल B43legacy_RADIO_INTERFMODE_MANUALWLAN:
		अगर (b43legacy_phy_पढ़ो(dev, 0x0033) & 0x0800)
			अवरोध;

		phy->aci_enable = true;

		phy_stacksave(B43legacy_PHY_RADIO_BITFIELD);
		phy_stacksave(B43legacy_PHY_G_CRS);
		अगर (phy->rev < 2)
			phy_stacksave(0x0406);
		अन्यथा अणु
			phy_stacksave(0x04C0);
			phy_stacksave(0x04C1);
		पूर्ण
		phy_stacksave(0x0033);
		phy_stacksave(0x04A7);
		phy_stacksave(0x04A3);
		phy_stacksave(0x04A9);
		phy_stacksave(0x04AA);
		phy_stacksave(0x04AC);
		phy_stacksave(0x0493);
		phy_stacksave(0x04A1);
		phy_stacksave(0x04A0);
		phy_stacksave(0x04A2);
		phy_stacksave(0x048A);
		phy_stacksave(0x04A8);
		phy_stacksave(0x04AB);
		अगर (phy->rev == 2) अणु
			phy_stacksave(0x04AD);
			phy_stacksave(0x04AE);
		पूर्ण अन्यथा अगर (phy->rev >= 3) अणु
			phy_stacksave(0x04AD);
			phy_stacksave(0x0415);
			phy_stacksave(0x0416);
			phy_stacksave(0x0417);
			ilt_stacksave(0x1A00 + 0x2);
			ilt_stacksave(0x1A00 + 0x3);
		पूर्ण
		phy_stacksave(0x042B);
		phy_stacksave(0x048C);

		b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_RADIO_BITFIELD,
				    b43legacy_phy_पढ़ो(dev,
				    B43legacy_PHY_RADIO_BITFIELD) & ~0x1000);
		b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_G_CRS,
				    (b43legacy_phy_पढ़ो(dev,
				    B43legacy_PHY_G_CRS)
				    & 0xFFFC) | 0x0002);

		b43legacy_phy_ग_लिखो(dev, 0x0033, 0x0800);
		b43legacy_phy_ग_लिखो(dev, 0x04A3, 0x2027);
		b43legacy_phy_ग_लिखो(dev, 0x04A9, 0x1CA8);
		b43legacy_phy_ग_लिखो(dev, 0x0493, 0x287A);
		b43legacy_phy_ग_लिखो(dev, 0x04AA, 0x1CA8);
		b43legacy_phy_ग_लिखो(dev, 0x04AC, 0x287A);

		b43legacy_phy_ग_लिखो(dev, 0x04A0,
				    (b43legacy_phy_पढ़ो(dev, 0x04A0)
				    & 0xFFC0) | 0x001A);
		b43legacy_phy_ग_लिखो(dev, 0x04A7, 0x000D);

		अगर (phy->rev < 2)
			b43legacy_phy_ग_लिखो(dev, 0x0406, 0xFF0D);
		अन्यथा अगर (phy->rev == 2) अणु
			b43legacy_phy_ग_लिखो(dev, 0x04C0, 0xFFFF);
			b43legacy_phy_ग_लिखो(dev, 0x04C1, 0x00A9);
		पूर्ण अन्यथा अणु
			b43legacy_phy_ग_लिखो(dev, 0x04C0, 0x00C1);
			b43legacy_phy_ग_लिखो(dev, 0x04C1, 0x0059);
		पूर्ण

		b43legacy_phy_ग_लिखो(dev, 0x04A1,
				    (b43legacy_phy_पढ़ो(dev, 0x04A1)
				    & 0xC0FF) | 0x1800);
		b43legacy_phy_ग_लिखो(dev, 0x04A1,
				    (b43legacy_phy_पढ़ो(dev, 0x04A1)
				    & 0xFFC0) | 0x0015);
		b43legacy_phy_ग_लिखो(dev, 0x04A8,
				    (b43legacy_phy_पढ़ो(dev, 0x04A8)
				    & 0xCFFF) | 0x1000);
		b43legacy_phy_ग_लिखो(dev, 0x04A8,
				    (b43legacy_phy_पढ़ो(dev, 0x04A8)
				    & 0xF0FF) | 0x0A00);
		b43legacy_phy_ग_लिखो(dev, 0x04AB,
				    (b43legacy_phy_पढ़ो(dev, 0x04AB)
				    & 0xCFFF) | 0x1000);
		b43legacy_phy_ग_लिखो(dev, 0x04AB,
				    (b43legacy_phy_पढ़ो(dev, 0x04AB)
				    & 0xF0FF) | 0x0800);
		b43legacy_phy_ग_लिखो(dev, 0x04AB,
				    (b43legacy_phy_पढ़ो(dev, 0x04AB)
				    & 0xFFCF) | 0x0010);
		b43legacy_phy_ग_लिखो(dev, 0x04AB,
				    (b43legacy_phy_पढ़ो(dev, 0x04AB)
				    & 0xFFF0) | 0x0005);
		b43legacy_phy_ग_लिखो(dev, 0x04A8,
				    (b43legacy_phy_पढ़ो(dev, 0x04A8)
				    & 0xFFCF) | 0x0010);
		b43legacy_phy_ग_लिखो(dev, 0x04A8,
				    (b43legacy_phy_पढ़ो(dev, 0x04A8)
				    & 0xFFF0) | 0x0006);
		b43legacy_phy_ग_लिखो(dev, 0x04A2,
				    (b43legacy_phy_पढ़ो(dev, 0x04A2)
				    & 0xF0FF) | 0x0800);
		b43legacy_phy_ग_लिखो(dev, 0x04A0,
				    (b43legacy_phy_पढ़ो(dev, 0x04A0)
				    & 0xF0FF) | 0x0500);
		b43legacy_phy_ग_लिखो(dev, 0x04A2,
				    (b43legacy_phy_पढ़ो(dev, 0x04A2)
				    & 0xFFF0) | 0x000B);

		अगर (phy->rev >= 3) अणु
			b43legacy_phy_ग_लिखो(dev, 0x048A,
					    b43legacy_phy_पढ़ो(dev, 0x048A)
					    & ~0x8000);
			b43legacy_phy_ग_लिखो(dev, 0x0415,
					    (b43legacy_phy_पढ़ो(dev, 0x0415)
					    & 0x8000) | 0x36D8);
			b43legacy_phy_ग_लिखो(dev, 0x0416,
					    (b43legacy_phy_पढ़ो(dev, 0x0416)
					    & 0x8000) | 0x36D8);
			b43legacy_phy_ग_लिखो(dev, 0x0417,
					    (b43legacy_phy_पढ़ो(dev, 0x0417)
					    & 0xFE00) | 0x016D);
		पूर्ण अन्यथा अणु
			b43legacy_phy_ग_लिखो(dev, 0x048A,
					    b43legacy_phy_पढ़ो(dev, 0x048A)
					    | 0x1000);
			b43legacy_phy_ग_लिखो(dev, 0x048A,
					    (b43legacy_phy_पढ़ो(dev, 0x048A)
					    & 0x9FFF) | 0x2000);
			पंचांगp32 = b43legacy_shm_पढ़ो32(dev, B43legacy_SHM_SHARED,
					    B43legacy_UCODEFLAGS_OFFSET);
			अगर (!(पंचांगp32 & 0x800)) अणु
				पंचांगp32 |= 0x800;
				b43legacy_shm_ग_लिखो32(dev, B43legacy_SHM_SHARED,
					    B43legacy_UCODEFLAGS_OFFSET,
					    पंचांगp32);
			पूर्ण
		पूर्ण
		अगर (phy->rev >= 2)
			b43legacy_phy_ग_लिखो(dev, 0x042B,
					    b43legacy_phy_पढ़ो(dev, 0x042B)
					    | 0x0800);
		b43legacy_phy_ग_लिखो(dev, 0x048C,
				    (b43legacy_phy_पढ़ो(dev, 0x048C)
				    & 0xF0FF) | 0x0200);
		अगर (phy->rev == 2) अणु
			b43legacy_phy_ग_लिखो(dev, 0x04AE,
					    (b43legacy_phy_पढ़ो(dev, 0x04AE)
					    & 0xFF00) | 0x007F);
			b43legacy_phy_ग_लिखो(dev, 0x04AD,
					    (b43legacy_phy_पढ़ो(dev, 0x04AD)
					    & 0x00FF) | 0x1300);
		पूर्ण अन्यथा अगर (phy->rev >= 6) अणु
			b43legacy_ilt_ग_लिखो(dev, 0x1A00 + 0x3, 0x007F);
			b43legacy_ilt_ग_लिखो(dev, 0x1A00 + 0x2, 0x007F);
			b43legacy_phy_ग_लिखो(dev, 0x04AD,
					    b43legacy_phy_पढ़ो(dev, 0x04AD)
					    & 0x00FF);
		पूर्ण
		b43legacy_calc_nrssi_slope(dev);
		अवरोध;
	शेष:
		B43legacy_BUG_ON(1);
	पूर्ण
पूर्ण

अटल व्योम
b43legacy_radio_पूर्णांकerference_mitigation_disable(काष्ठा b43legacy_wldev *dev,
						पूर्णांक mode)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u32 पंचांगp32;
	u32 *stack = phy->पूर्णांकerfstack;

	चयन (mode) अणु
	हाल B43legacy_RADIO_INTERFMODE_NONWLAN:
		अगर (phy->rev != 1) अणु
			b43legacy_phy_ग_लिखो(dev, 0x042B,
					    b43legacy_phy_पढ़ो(dev, 0x042B)
					    & ~0x0800);
			b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_G_CRS,
					    b43legacy_phy_पढ़ो(dev,
					    B43legacy_PHY_G_CRS) | 0x4000);
			अवरोध;
		पूर्ण
		phy_stackrestore(0x0078);
		b43legacy_calc_nrssi_threshold(dev);
		phy_stackrestore(0x0406);
		b43legacy_phy_ग_लिखो(dev, 0x042B,
				    b43legacy_phy_पढ़ो(dev, 0x042B) & ~0x0800);
		अगर (!dev->bad_frames_preempt)
			b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_RADIO_BITFIELD,
					    b43legacy_phy_पढ़ो(dev,
					    B43legacy_PHY_RADIO_BITFIELD)
					    & ~(1 << 11));
		b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_G_CRS,
				    b43legacy_phy_पढ़ो(dev, B43legacy_PHY_G_CRS)
				    | 0x4000);
		phy_stackrestore(0x04A0);
		phy_stackrestore(0x04A1);
		phy_stackrestore(0x04A2);
		phy_stackrestore(0x04A8);
		phy_stackrestore(0x04AB);
		phy_stackrestore(0x04A7);
		phy_stackrestore(0x04A3);
		phy_stackrestore(0x04A9);
		phy_stackrestore(0x0493);
		phy_stackrestore(0x04AA);
		phy_stackrestore(0x04AC);
		अवरोध;
	हाल B43legacy_RADIO_INTERFMODE_MANUALWLAN:
		अगर (!(b43legacy_phy_पढ़ो(dev, 0x0033) & 0x0800))
			अवरोध;

		phy->aci_enable = false;

		phy_stackrestore(B43legacy_PHY_RADIO_BITFIELD);
		phy_stackrestore(B43legacy_PHY_G_CRS);
		phy_stackrestore(0x0033);
		phy_stackrestore(0x04A3);
		phy_stackrestore(0x04A9);
		phy_stackrestore(0x0493);
		phy_stackrestore(0x04AA);
		phy_stackrestore(0x04AC);
		phy_stackrestore(0x04A0);
		phy_stackrestore(0x04A7);
		अगर (phy->rev >= 2) अणु
			phy_stackrestore(0x04C0);
			phy_stackrestore(0x04C1);
		पूर्ण अन्यथा
			phy_stackrestore(0x0406);
		phy_stackrestore(0x04A1);
		phy_stackrestore(0x04AB);
		phy_stackrestore(0x04A8);
		अगर (phy->rev == 2) अणु
			phy_stackrestore(0x04AD);
			phy_stackrestore(0x04AE);
		पूर्ण अन्यथा अगर (phy->rev >= 3) अणु
			phy_stackrestore(0x04AD);
			phy_stackrestore(0x0415);
			phy_stackrestore(0x0416);
			phy_stackrestore(0x0417);
			ilt_stackrestore(0x1A00 + 0x2);
			ilt_stackrestore(0x1A00 + 0x3);
		पूर्ण
		phy_stackrestore(0x04A2);
		phy_stackrestore(0x04A8);
		phy_stackrestore(0x042B);
		phy_stackrestore(0x048C);
		पंचांगp32 = b43legacy_shm_पढ़ो32(dev, B43legacy_SHM_SHARED,
					     B43legacy_UCODEFLAGS_OFFSET);
		अगर (पंचांगp32 & 0x800) अणु
			पंचांगp32 &= ~0x800;
			b43legacy_shm_ग_लिखो32(dev, B43legacy_SHM_SHARED,
					      B43legacy_UCODEFLAGS_OFFSET,
					      पंचांगp32);
		पूर्ण
		b43legacy_calc_nrssi_slope(dev);
		अवरोध;
	शेष:
		B43legacy_BUG_ON(1);
	पूर्ण
पूर्ण

#अघोषित phy_stacksave
#अघोषित phy_stackrestore
#अघोषित radio_stacksave
#अघोषित radio_stackrestore
#अघोषित ilt_stacksave
#अघोषित ilt_stackrestore

पूर्णांक b43legacy_radio_set_पूर्णांकerference_mitigation(काष्ठा b43legacy_wldev *dev,
						पूर्णांक mode)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	पूर्णांक currenपंचांगode;

	अगर ((phy->type != B43legacy_PHYTYPE_G) ||
	    (phy->rev == 0) || (!phy->gmode))
		वापस -ENODEV;

	phy->aci_wlan_स्वतःmatic = false;
	चयन (mode) अणु
	हाल B43legacy_RADIO_INTERFMODE_AUTOWLAN:
		phy->aci_wlan_स्वतःmatic = true;
		अगर (phy->aci_enable)
			mode = B43legacy_RADIO_INTERFMODE_MANUALWLAN;
		अन्यथा
			mode = B43legacy_RADIO_INTERFMODE_NONE;
		अवरोध;
	हाल B43legacy_RADIO_INTERFMODE_NONE:
	हाल B43legacy_RADIO_INTERFMODE_NONWLAN:
	हाल B43legacy_RADIO_INTERFMODE_MANUALWLAN:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	currenपंचांगode = phy->पूर्णांकerभ_शेषe;
	अगर (currenपंचांगode == mode)
		वापस 0;
	अगर (currenपंचांगode != B43legacy_RADIO_INTERFMODE_NONE)
		b43legacy_radio_पूर्णांकerference_mitigation_disable(dev,
								currenपंचांगode);

	अगर (mode == B43legacy_RADIO_INTERFMODE_NONE) अणु
		phy->aci_enable = false;
		phy->aci_hw_rssi = false;
	पूर्ण अन्यथा
		b43legacy_radio_पूर्णांकerference_mitigation_enable(dev, mode);
	phy->पूर्णांकerभ_शेषe = mode;

	वापस 0;
पूर्ण

u16 b43legacy_radio_calibrationvalue(काष्ठा b43legacy_wldev *dev)
अणु
	u16 reg;
	u16 index;
	u16 ret;

	reg = b43legacy_radio_पढ़ो16(dev, 0x0060);
	index = (reg & 0x001E) >> 1;
	ret = rcc_table[index] << 1;
	ret |= (reg & 0x0001);
	ret |= 0x0020;

	वापस ret;
पूर्ण

#घोषणा LPD(L, P, D)    (((L) << 2) | ((P) << 1) | ((D) << 0))
अटल u16 b43legacy_get_812_value(काष्ठा b43legacy_wldev *dev, u8 lpd)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 loop_or = 0;
	u16 adj_loopback_gain = phy->loopback_gain[0];
	u8 loop;
	u16 बाह्य_lna_control;

	अगर (!phy->gmode)
		वापस 0;
	अगर (!has_loopback_gain(phy)) अणु
		अगर (phy->rev < 7 || !(dev->dev->bus->sprom.boardflags_lo
		    & B43legacy_BFL_EXTLNA)) अणु
			चयन (lpd) अणु
			हाल LPD(0, 1, 1):
				वापस 0x0FB2;
			हाल LPD(0, 0, 1):
				वापस 0x00B2;
			हाल LPD(1, 0, 1):
				वापस 0x30B2;
			हाल LPD(1, 0, 0):
				वापस 0x30B3;
			शेष:
				B43legacy_BUG_ON(1);
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (lpd) अणु
			हाल LPD(0, 1, 1):
				वापस 0x8FB2;
			हाल LPD(0, 0, 1):
				वापस 0x80B2;
			हाल LPD(1, 0, 1):
				वापस 0x20B2;
			हाल LPD(1, 0, 0):
				वापस 0x20B3;
			शेष:
				B43legacy_BUG_ON(1);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (phy->radio_rev == 8)
			adj_loopback_gain += 0x003E;
		अन्यथा
			adj_loopback_gain += 0x0026;
		अगर (adj_loopback_gain >= 0x46) अणु
			adj_loopback_gain -= 0x46;
			बाह्य_lna_control = 0x3000;
		पूर्ण अन्यथा अगर (adj_loopback_gain >= 0x3A) अणु
			adj_loopback_gain -= 0x3A;
			बाह्य_lna_control = 0x2000;
		पूर्ण अन्यथा अगर (adj_loopback_gain >= 0x2E) अणु
			adj_loopback_gain -= 0x2E;
			बाह्य_lna_control = 0x1000;
		पूर्ण अन्यथा अणु
			adj_loopback_gain -= 0x10;
			बाह्य_lna_control = 0x0000;
		पूर्ण
		क्रम (loop = 0; loop < 16; loop++) अणु
			u16 पंचांगp = adj_loopback_gain - 6 * loop;
			अगर (पंचांगp < 6)
				अवरोध;
		पूर्ण

		loop_or = (loop << 8) | बाह्य_lna_control;
		अगर (phy->rev >= 7 && dev->dev->bus->sprom.boardflags_lo
		    & B43legacy_BFL_EXTLNA) अणु
			अगर (बाह्य_lna_control)
				loop_or |= 0x8000;
			चयन (lpd) अणु
			हाल LPD(0, 1, 1):
				वापस 0x8F92;
			हाल LPD(0, 0, 1):
				वापस (0x8092 | loop_or);
			हाल LPD(1, 0, 1):
				वापस (0x2092 | loop_or);
			हाल LPD(1, 0, 0):
				वापस (0x2093 | loop_or);
			शेष:
				B43legacy_BUG_ON(1);
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (lpd) अणु
			हाल LPD(0, 1, 1):
				वापस 0x0F92;
			हाल LPD(0, 0, 1):
			हाल LPD(1, 0, 1):
				वापस (0x0092 | loop_or);
			हाल LPD(1, 0, 0):
				वापस (0x0093 | loop_or);
			शेष:
				B43legacy_BUG_ON(1);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

u16 b43legacy_radio_init2050(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 backup[21] = अणु 0 पूर्ण;
	u16 ret;
	u16 i;
	u16 j;
	u32 पंचांगp1 = 0;
	u32 पंचांगp2 = 0;

	backup[0] = b43legacy_radio_पढ़ो16(dev, 0x0043);
	backup[14] = b43legacy_radio_पढ़ो16(dev, 0x0051);
	backup[15] = b43legacy_radio_पढ़ो16(dev, 0x0052);
	backup[1] = b43legacy_phy_पढ़ो(dev, 0x0015);
	backup[16] = b43legacy_phy_पढ़ो(dev, 0x005A);
	backup[17] = b43legacy_phy_पढ़ो(dev, 0x0059);
	backup[18] = b43legacy_phy_पढ़ो(dev, 0x0058);
	अगर (phy->type == B43legacy_PHYTYPE_B) अणु
		backup[2] = b43legacy_phy_पढ़ो(dev, 0x0030);
		backup[3] = b43legacy_पढ़ो16(dev, 0x03EC);
		b43legacy_phy_ग_लिखो(dev, 0x0030, 0x00FF);
		b43legacy_ग_लिखो16(dev, 0x03EC, 0x3F3F);
	पूर्ण अन्यथा अणु
		अगर (phy->gmode) अणु
			backup[4] = b43legacy_phy_पढ़ो(dev, 0x0811);
			backup[5] = b43legacy_phy_पढ़ो(dev, 0x0812);
			backup[6] = b43legacy_phy_पढ़ो(dev, 0x0814);
			backup[7] = b43legacy_phy_पढ़ो(dev, 0x0815);
			backup[8] = b43legacy_phy_पढ़ो(dev,
						       B43legacy_PHY_G_CRS);
			backup[9] = b43legacy_phy_पढ़ो(dev, 0x0802);
			b43legacy_phy_ग_लिखो(dev, 0x0814,
					    (b43legacy_phy_पढ़ो(dev, 0x0814)
					    | 0x0003));
			b43legacy_phy_ग_लिखो(dev, 0x0815,
					    (b43legacy_phy_पढ़ो(dev, 0x0815)
					    & 0xFFFC));
			b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_G_CRS,
					    (b43legacy_phy_पढ़ो(dev,
					    B43legacy_PHY_G_CRS) & 0x7FFF));
			b43legacy_phy_ग_लिखो(dev, 0x0802,
					    (b43legacy_phy_पढ़ो(dev, 0x0802)
					    & 0xFFFC));
			अगर (phy->rev > 1) अणु /* loopback gain enabled */
				backup[19] = b43legacy_phy_पढ़ो(dev, 0x080F);
				backup[20] = b43legacy_phy_पढ़ो(dev, 0x0810);
				अगर (phy->rev >= 3)
					b43legacy_phy_ग_लिखो(dev, 0x080F,
							    0xC020);
				अन्यथा
					b43legacy_phy_ग_लिखो(dev, 0x080F,
							    0x8020);
				b43legacy_phy_ग_लिखो(dev, 0x0810, 0x0000);
			पूर्ण
			b43legacy_phy_ग_लिखो(dev, 0x0812,
					    b43legacy_get_812_value(dev,
					    LPD(0, 1, 1)));
			अगर (phy->rev < 7 ||
			    !(dev->dev->bus->sprom.boardflags_lo
			    & B43legacy_BFL_EXTLNA))
				b43legacy_phy_ग_लिखो(dev, 0x0811, 0x01B3);
			अन्यथा
				b43legacy_phy_ग_लिखो(dev, 0x0811, 0x09B3);
		पूर्ण
	पूर्ण
	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_PHY_RADIO,
			(b43legacy_पढ़ो16(dev, B43legacy_MMIO_PHY_RADIO)
					  | 0x8000));
	backup[10] = b43legacy_phy_पढ़ो(dev, 0x0035);
	b43legacy_phy_ग_लिखो(dev, 0x0035,
			    (b43legacy_phy_पढ़ो(dev, 0x0035) & 0xFF7F));
	backup[11] = b43legacy_पढ़ो16(dev, 0x03E6);
	backup[12] = b43legacy_पढ़ो16(dev, B43legacy_MMIO_CHANNEL_EXT);

	/* Initialization */
	अगर (phy->analog == 0)
		b43legacy_ग_लिखो16(dev, 0x03E6, 0x0122);
	अन्यथा अणु
		अगर (phy->analog >= 2)
			b43legacy_phy_ग_लिखो(dev, 0x0003,
					    (b43legacy_phy_पढ़ो(dev, 0x0003)
					    & 0xFFBF) | 0x0040);
		b43legacy_ग_लिखो16(dev, B43legacy_MMIO_CHANNEL_EXT,
				  (b43legacy_पढ़ो16(dev,
				  B43legacy_MMIO_CHANNEL_EXT) | 0x2000));
	पूर्ण

	ret = b43legacy_radio_calibrationvalue(dev);

	अगर (phy->type == B43legacy_PHYTYPE_B)
		b43legacy_radio_ग_लिखो16(dev, 0x0078, 0x0026);

	अगर (phy->gmode)
		b43legacy_phy_ग_लिखो(dev, 0x0812,
				    b43legacy_get_812_value(dev,
				    LPD(0, 1, 1)));
	b43legacy_phy_ग_लिखो(dev, 0x0015, 0xBFAF);
	b43legacy_phy_ग_लिखो(dev, 0x002B, 0x1403);
	अगर (phy->gmode)
		b43legacy_phy_ग_लिखो(dev, 0x0812,
				    b43legacy_get_812_value(dev,
				    LPD(0, 0, 1)));
	b43legacy_phy_ग_लिखो(dev, 0x0015, 0xBFA0);
	b43legacy_radio_ग_लिखो16(dev, 0x0051,
				(b43legacy_radio_पढ़ो16(dev, 0x0051)
				| 0x0004));
	अगर (phy->radio_rev == 8)
		b43legacy_radio_ग_लिखो16(dev, 0x0043, 0x001F);
	अन्यथा अणु
		b43legacy_radio_ग_लिखो16(dev, 0x0052, 0x0000);
		b43legacy_radio_ग_लिखो16(dev, 0x0043,
					(b43legacy_radio_पढ़ो16(dev, 0x0043)
					& 0xFFF0) | 0x0009);
	पूर्ण
	b43legacy_phy_ग_लिखो(dev, 0x0058, 0x0000);

	क्रम (i = 0; i < 16; i++) अणु
		b43legacy_phy_ग_लिखो(dev, 0x005A, 0x0480);
		b43legacy_phy_ग_लिखो(dev, 0x0059, 0xC810);
		b43legacy_phy_ग_लिखो(dev, 0x0058, 0x000D);
		अगर (phy->gmode)
			b43legacy_phy_ग_लिखो(dev, 0x0812,
					    b43legacy_get_812_value(dev,
					    LPD(1, 0, 1)));
		b43legacy_phy_ग_लिखो(dev, 0x0015, 0xAFB0);
		udelay(10);
		अगर (phy->gmode)
			b43legacy_phy_ग_लिखो(dev, 0x0812,
					    b43legacy_get_812_value(dev,
					    LPD(1, 0, 1)));
		b43legacy_phy_ग_लिखो(dev, 0x0015, 0xEFB0);
		udelay(10);
		अगर (phy->gmode)
			b43legacy_phy_ग_लिखो(dev, 0x0812,
					    b43legacy_get_812_value(dev,
					    LPD(1, 0, 0)));
		b43legacy_phy_ग_लिखो(dev, 0x0015, 0xFFF0);
		udelay(20);
		पंचांगp1 += b43legacy_phy_पढ़ो(dev, 0x002D);
		b43legacy_phy_ग_लिखो(dev, 0x0058, 0x0000);
		अगर (phy->gmode)
			b43legacy_phy_ग_लिखो(dev, 0x0812,
					    b43legacy_get_812_value(dev,
					    LPD(1, 0, 1)));
		b43legacy_phy_ग_लिखो(dev, 0x0015, 0xAFB0);
	पूर्ण

	पंचांगp1++;
	पंचांगp1 >>= 9;
	udelay(10);
	b43legacy_phy_ग_लिखो(dev, 0x0058, 0x0000);

	क्रम (i = 0; i < 16; i++) अणु
		b43legacy_radio_ग_लिखो16(dev, 0x0078, (flip_4bit(i) << 1)
					| 0x0020);
		backup[13] = b43legacy_radio_पढ़ो16(dev, 0x0078);
		udelay(10);
		क्रम (j = 0; j < 16; j++) अणु
			b43legacy_phy_ग_लिखो(dev, 0x005A, 0x0D80);
			b43legacy_phy_ग_लिखो(dev, 0x0059, 0xC810);
			b43legacy_phy_ग_लिखो(dev, 0x0058, 0x000D);
			अगर (phy->gmode)
				b43legacy_phy_ग_लिखो(dev, 0x0812,
						    b43legacy_get_812_value(dev,
						    LPD(1, 0, 1)));
			b43legacy_phy_ग_लिखो(dev, 0x0015, 0xAFB0);
			udelay(10);
			अगर (phy->gmode)
				b43legacy_phy_ग_लिखो(dev, 0x0812,
						    b43legacy_get_812_value(dev,
						    LPD(1, 0, 1)));
			b43legacy_phy_ग_लिखो(dev, 0x0015, 0xEFB0);
			udelay(10);
			अगर (phy->gmode)
				b43legacy_phy_ग_लिखो(dev, 0x0812,
						    b43legacy_get_812_value(dev,
						    LPD(1, 0, 0)));
			b43legacy_phy_ग_लिखो(dev, 0x0015, 0xFFF0);
			udelay(10);
			पंचांगp2 += b43legacy_phy_पढ़ो(dev, 0x002D);
			b43legacy_phy_ग_लिखो(dev, 0x0058, 0x0000);
			अगर (phy->gmode)
				b43legacy_phy_ग_लिखो(dev, 0x0812,
						    b43legacy_get_812_value(dev,
						    LPD(1, 0, 1)));
			b43legacy_phy_ग_लिखो(dev, 0x0015, 0xAFB0);
		पूर्ण
		पंचांगp2++;
		पंचांगp2 >>= 8;
		अगर (पंचांगp1 < पंचांगp2)
			अवरोध;
	पूर्ण

	/* Restore the रेजिस्टरs */
	b43legacy_phy_ग_लिखो(dev, 0x0015, backup[1]);
	b43legacy_radio_ग_लिखो16(dev, 0x0051, backup[14]);
	b43legacy_radio_ग_लिखो16(dev, 0x0052, backup[15]);
	b43legacy_radio_ग_लिखो16(dev, 0x0043, backup[0]);
	b43legacy_phy_ग_लिखो(dev, 0x005A, backup[16]);
	b43legacy_phy_ग_लिखो(dev, 0x0059, backup[17]);
	b43legacy_phy_ग_लिखो(dev, 0x0058, backup[18]);
	b43legacy_ग_लिखो16(dev, 0x03E6, backup[11]);
	अगर (phy->analog != 0)
		b43legacy_ग_लिखो16(dev, B43legacy_MMIO_CHANNEL_EXT, backup[12]);
	b43legacy_phy_ग_लिखो(dev, 0x0035, backup[10]);
	b43legacy_radio_selectchannel(dev, phy->channel, 1);
	अगर (phy->type == B43legacy_PHYTYPE_B) अणु
		b43legacy_phy_ग_लिखो(dev, 0x0030, backup[2]);
		b43legacy_ग_लिखो16(dev, 0x03EC, backup[3]);
	पूर्ण अन्यथा अणु
		अगर (phy->gmode) अणु
			b43legacy_ग_लिखो16(dev, B43legacy_MMIO_PHY_RADIO,
					  (b43legacy_पढ़ो16(dev,
					  B43legacy_MMIO_PHY_RADIO) & 0x7FFF));
			b43legacy_phy_ग_लिखो(dev, 0x0811, backup[4]);
			b43legacy_phy_ग_लिखो(dev, 0x0812, backup[5]);
			b43legacy_phy_ग_लिखो(dev, 0x0814, backup[6]);
			b43legacy_phy_ग_लिखो(dev, 0x0815, backup[7]);
			b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_G_CRS,
					    backup[8]);
			b43legacy_phy_ग_लिखो(dev, 0x0802, backup[9]);
			अगर (phy->rev > 1) अणु
				b43legacy_phy_ग_लिखो(dev, 0x080F, backup[19]);
				b43legacy_phy_ग_लिखो(dev, 0x0810, backup[20]);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (i >= 15)
		ret = backup[13];

	वापस ret;
पूर्ण

अटल अंतरभूत
u16 freq_r3A_value(u16 frequency)
अणु
	u16 value;

	अगर (frequency < 5091)
		value = 0x0040;
	अन्यथा अगर (frequency < 5321)
		value = 0x0000;
	अन्यथा अगर (frequency < 5806)
		value = 0x0080;
	अन्यथा
		value = 0x0040;

	वापस value;
पूर्ण

पूर्णांक b43legacy_radio_selectchannel(काष्ठा b43legacy_wldev *dev,
				  u8 channel,
				  पूर्णांक synthetic_pu_workaround)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;

	अगर (channel == 0xFF) अणु
		चयन (phy->type) अणु
		हाल B43legacy_PHYTYPE_B:
		हाल B43legacy_PHYTYPE_G:
			channel = B43legacy_RADIO_DEFAULT_CHANNEL_BG;
			अवरोध;
		शेष:
			B43legacy_WARN_ON(1);
		पूर्ण
	पूर्ण

/* TODO: Check अगर channel is valid - वापस -EINVAL अगर not */
	अगर (synthetic_pu_workaround)
		b43legacy_synth_pu_workaround(dev, channel);

	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_CHANNEL,
			  channel2freq_bg(channel));

	अगर (channel == 14) अणु
		अगर (dev->dev->bus->sprom.country_code == 5)   /* JAPAN) */
			b43legacy_shm_ग_लिखो32(dev, B43legacy_SHM_SHARED,
					      B43legacy_UCODEFLAGS_OFFSET,
					      b43legacy_shm_पढ़ो32(dev,
					      B43legacy_SHM_SHARED,
					      B43legacy_UCODEFLAGS_OFFSET)
					      & ~(1 << 7));
		अन्यथा
			b43legacy_shm_ग_लिखो32(dev, B43legacy_SHM_SHARED,
					      B43legacy_UCODEFLAGS_OFFSET,
					      b43legacy_shm_पढ़ो32(dev,
					      B43legacy_SHM_SHARED,
					      B43legacy_UCODEFLAGS_OFFSET)
					      | (1 << 7));
		b43legacy_ग_लिखो16(dev, B43legacy_MMIO_CHANNEL_EXT,
				  b43legacy_पढ़ो16(dev,
				  B43legacy_MMIO_CHANNEL_EXT) | (1 << 11));
	पूर्ण अन्यथा
		b43legacy_ग_लिखो16(dev, B43legacy_MMIO_CHANNEL_EXT,
				  b43legacy_पढ़ो16(dev,
				  B43legacy_MMIO_CHANNEL_EXT) & 0xF7BF);

	phy->channel = channel;
	/*XXX: Using the दीर्घer of 2 समयouts (8000 vs 2000 usecs). Specs states
	 *     that 2000 usecs might suffice. */
	msleep(8);

	वापस 0;
पूर्ण

व्योम b43legacy_radio_set_txantenna(काष्ठा b43legacy_wldev *dev, u32 val)
अणु
	u16 पंचांगp;

	val <<= 8;
	पंचांगp = b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_SHARED, 0x0022) & 0xFCFF;
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED, 0x0022, पंचांगp | val);
	पंचांगp = b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_SHARED, 0x03A8) & 0xFCFF;
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED, 0x03A8, पंचांगp | val);
	पंचांगp = b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_SHARED, 0x0054) & 0xFCFF;
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED, 0x0054, पंचांगp | val);
पूर्ण

/* http://bcm-specs.sipsolutions.net/TX_Gain_Base_Band */
अटल u16 b43legacy_get_txgain_base_band(u16 txघातer)
अणु
	u16 ret;

	B43legacy_WARN_ON(txघातer > 63);

	अगर (txघातer >= 54)
		ret = 2;
	अन्यथा अगर (txघातer >= 49)
		ret = 4;
	अन्यथा अगर (txघातer >= 44)
		ret = 5;
	अन्यथा
		ret = 6;

	वापस ret;
पूर्ण

/* http://bcm-specs.sipsolutions.net/TX_Gain_Radio_Frequency_Power_Amplअगरier */
अटल u16 b43legacy_get_txgain_freq_घातer_amp(u16 txघातer)
अणु
	u16 ret;

	B43legacy_WARN_ON(txघातer > 63);

	अगर (txघातer >= 32)
		ret = 0;
	अन्यथा अगर (txघातer >= 25)
		ret = 1;
	अन्यथा अगर (txघातer >= 20)
		ret = 2;
	अन्यथा अगर (txघातer >= 12)
		ret = 3;
	अन्यथा
		ret = 4;

	वापस ret;
पूर्ण

/* http://bcm-specs.sipsolutions.net/TX_Gain_Digital_Analog_Converter */
अटल u16 b43legacy_get_txgain_dac(u16 txघातer)
अणु
	u16 ret;

	B43legacy_WARN_ON(txघातer > 63);

	अगर (txघातer >= 54)
		ret = txघातer - 53;
	अन्यथा अगर (txघातer >= 49)
		ret = txघातer - 42;
	अन्यथा अगर (txघातer >= 44)
		ret = txघातer - 37;
	अन्यथा अगर (txघातer >= 32)
		ret = txघातer - 32;
	अन्यथा अगर (txघातer >= 25)
		ret = txघातer - 20;
	अन्यथा अगर (txघातer >= 20)
		ret = txघातer - 13;
	अन्यथा अगर (txघातer >= 12)
		ret = txघातer - 8;
	अन्यथा
		ret = txघातer;

	वापस ret;
पूर्ण

व्योम b43legacy_radio_set_txघातer_a(काष्ठा b43legacy_wldev *dev, u16 txघातer)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 pamp;
	u16 base;
	u16 dac;
	u16 ilt;

	txघातer = clamp_val(txघातer, 0, 63);

	pamp = b43legacy_get_txgain_freq_घातer_amp(txघातer);
	pamp <<= 5;
	pamp &= 0x00E0;
	b43legacy_phy_ग_लिखो(dev, 0x0019, pamp);

	base = b43legacy_get_txgain_base_band(txघातer);
	base &= 0x000F;
	b43legacy_phy_ग_लिखो(dev, 0x0017, base | 0x0020);

	ilt = b43legacy_ilt_पढ़ो(dev, 0x3001);
	ilt &= 0x0007;

	dac = b43legacy_get_txgain_dac(txघातer);
	dac <<= 3;
	dac |= ilt;

	b43legacy_ilt_ग_लिखो(dev, 0x3001, dac);

	phy->txpwr_offset = txघातer;

	/* TODO: FuncPlaceholder (Adjust BB loft cancel) */
पूर्ण

व्योम b43legacy_radio_set_txघातer_bg(काष्ठा b43legacy_wldev *dev,
				    u16 baseband_attenuation,
				    u16 radio_attenuation,
				    u16 txघातer)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;

	अगर (baseband_attenuation == 0xFFFF)
		baseband_attenuation = phy->bbatt;
	अगर (radio_attenuation == 0xFFFF)
		radio_attenuation = phy->rfatt;
	अगर (txघातer == 0xFFFF)
		txघातer = phy->txctl1;
	phy->bbatt = baseband_attenuation;
	phy->rfatt = radio_attenuation;
	phy->txctl1 = txघातer;

	B43legacy_WARN_ON(baseband_attenuation > 11);
	अगर (phy->radio_rev < 6)
		B43legacy_WARN_ON(radio_attenuation > 9);
	अन्यथा
		B43legacy_WARN_ON(radio_attenuation > 31);
	B43legacy_WARN_ON(txघातer > 7);

	b43legacy_phy_set_baseband_attenuation(dev, baseband_attenuation);
	b43legacy_radio_ग_लिखो16(dev, 0x0043, radio_attenuation);
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED, 0x0064,
			      radio_attenuation);
	अगर (phy->radio_ver == 0x2050)
		b43legacy_radio_ग_लिखो16(dev, 0x0052,
					(b43legacy_radio_पढ़ो16(dev, 0x0052)
					& ~0x0070) | ((txघातer << 4) & 0x0070));
	/* FIXME: The spec is very weird and unclear here. */
	अगर (phy->type == B43legacy_PHYTYPE_G)
		b43legacy_phy_lo_adjust(dev, 0);
पूर्ण

u16 b43legacy_शेष_baseband_attenuation(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;

	अगर (phy->radio_ver == 0x2050 && phy->radio_rev < 6)
		वापस 0;
	वापस 2;
पूर्ण

u16 b43legacy_शेष_radio_attenuation(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 att = 0xFFFF;

	चयन (phy->radio_ver) अणु
	हाल 0x2053:
		चयन (phy->radio_rev) अणु
		हाल 1:
			att = 6;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 0x2050:
		चयन (phy->radio_rev) अणु
		हाल 0:
			att = 5;
			अवरोध;
		हाल 1:
			अगर (phy->type == B43legacy_PHYTYPE_G) अणु
				अगर (is_bcm_board_venकरोr(dev) &&
				    dev->dev->bus->boardinfo.type == 0x421 &&
				    dev->dev->bus->sprom.board_rev >= 30)
					att = 3;
				अन्यथा अगर (is_bcm_board_venकरोr(dev) &&
					 dev->dev->bus->boardinfo.type == 0x416)
					att = 3;
				अन्यथा
					att = 1;
			पूर्ण अन्यथा अणु
				अगर (is_bcm_board_venकरोr(dev) &&
				    dev->dev->bus->boardinfo.type == 0x421 &&
				    dev->dev->bus->sprom.board_rev >= 30)
					att = 7;
				अन्यथा
					att = 6;
			पूर्ण
			अवरोध;
		हाल 2:
			अगर (phy->type == B43legacy_PHYTYPE_G) अणु
				अगर (is_bcm_board_venकरोr(dev) &&
				    dev->dev->bus->boardinfo.type == 0x421 &&
				    dev->dev->bus->sprom.board_rev >= 30)
					att = 3;
				अन्यथा अगर (is_bcm_board_venकरोr(dev) &&
					 dev->dev->bus->boardinfo.type ==
					 0x416)
					att = 5;
				अन्यथा अगर (dev->dev->bus->chip_id == 0x4320)
					att = 4;
				अन्यथा
					att = 3;
			पूर्ण अन्यथा
				att = 6;
			अवरोध;
		हाल 3:
			att = 5;
			अवरोध;
		हाल 4:
		हाल 5:
			att = 1;
			अवरोध;
		हाल 6:
		हाल 7:
			att = 5;
			अवरोध;
		हाल 8:
			att = 0x1A;
			अवरोध;
		हाल 9:
		शेष:
			att = 5;
		पूर्ण
	पूर्ण
	अगर (is_bcm_board_venकरोr(dev) &&
	    dev->dev->bus->boardinfo.type == 0x421) अणु
		अगर (dev->dev->bus->sprom.board_rev < 0x43)
			att = 2;
		अन्यथा अगर (dev->dev->bus->sprom.board_rev < 0x51)
			att = 3;
	पूर्ण
	अगर (att == 0xFFFF)
		att = 5;

	वापस att;
पूर्ण

u16 b43legacy_शेष_txctl1(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;

	अगर (phy->radio_ver != 0x2050)
		वापस 0;
	अगर (phy->radio_rev == 1)
		वापस 3;
	अगर (phy->radio_rev < 6)
		वापस 2;
	अगर (phy->radio_rev == 8)
		वापस 1;
	वापस 0;
पूर्ण

व्योम b43legacy_radio_turn_on(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	पूर्णांक err;
	u8 channel;

	might_sleep();

	अगर (phy->radio_on)
		वापस;

	चयन (phy->type) अणु
	हाल B43legacy_PHYTYPE_B:
	हाल B43legacy_PHYTYPE_G:
		b43legacy_phy_ग_लिखो(dev, 0x0015, 0x8000);
		b43legacy_phy_ग_लिखो(dev, 0x0015, 0xCC00);
		b43legacy_phy_ग_लिखो(dev, 0x0015,
				    (phy->gmode ? 0x00C0 : 0x0000));
		अगर (phy->radio_off_context.valid) अणु
			/* Restore the RFover values. */
			b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_RFOVER,
					    phy->radio_off_context.rfover);
			b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_RFOVERVAL,
					    phy->radio_off_context.rfoverval);
			phy->radio_off_context.valid = false;
		पूर्ण
		channel = phy->channel;
		err = b43legacy_radio_selectchannel(dev,
					B43legacy_RADIO_DEFAULT_CHANNEL_BG, 1);
		err |= b43legacy_radio_selectchannel(dev, channel, 0);
		B43legacy_WARN_ON(err);
		अवरोध;
	शेष:
		B43legacy_BUG_ON(1);
	पूर्ण
	phy->radio_on = true;
पूर्ण

व्योम b43legacy_radio_turn_off(काष्ठा b43legacy_wldev *dev, bool क्रमce)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;

	अगर (!phy->radio_on && !क्रमce)
		वापस;

	अगर (phy->type == B43legacy_PHYTYPE_G && dev->dev->id.revision >= 5) अणु
		u16 rfover, rfoverval;

		rfover = b43legacy_phy_पढ़ो(dev, B43legacy_PHY_RFOVER);
		rfoverval = b43legacy_phy_पढ़ो(dev, B43legacy_PHY_RFOVERVAL);
		अगर (!क्रमce) अणु
			phy->radio_off_context.rfover = rfover;
			phy->radio_off_context.rfoverval = rfoverval;
			phy->radio_off_context.valid = true;
		पूर्ण
		b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_RFOVER, rfover | 0x008C);
		b43legacy_phy_ग_लिखो(dev, B43legacy_PHY_RFOVERVAL,
				    rfoverval & 0xFF73);
	पूर्ण अन्यथा
		b43legacy_phy_ग_लिखो(dev, 0x0015, 0xAA00);
	phy->radio_on = false;
	b43legacydbg(dev->wl, "Radio initialized\n");
पूर्ण

व्योम b43legacy_radio_clear_tssi(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;

	चयन (phy->type) अणु
	हाल B43legacy_PHYTYPE_B:
	हाल B43legacy_PHYTYPE_G:
		b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED, 0x0058,
				      0x7F7F);
		b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED, 0x005a,
				      0x7F7F);
		b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED, 0x0070,
				      0x7F7F);
		b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED, 0x0072,
				      0x7F7F);
		अवरोध;
	पूर्ण
पूर्ण
