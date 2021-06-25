<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  Broadcom B43legacy wireless driver
 *
 *  Copyright (c) 2005 Martin Langer <martin-langer@gmx.de>
 *  Copyright (c) 2005-2008 Stefano Brivio <stefano.brivio@polimi.it>
 *  Copyright (c) 2005, 2006 Michael Buesch <m@bues.ch>
 *  Copyright (c) 2005 Danny van Dyk <kugelfang@gentoo.org>
 *  Copyright (c) 2005 Andreas Jaggi <andreas.jaggi@waterwave.ch>
 *  Copyright (c) 2007 Larry Finger <Larry.Finger@lwfinger.net>
 *
 *  Some parts of the code in this file are derived from the ipw2200
 *  driver  Copyright(c) 2003 - 2004 Intel Corporation.

 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/firmware.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <net/dst.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "b43legacy.h"
#समावेश "main.h"
#समावेश "debugfs.h"
#समावेश "phy.h"
#समावेश "dma.h"
#समावेश "pio.h"
#समावेश "sysfs.h"
#समावेश "xmit.h"
#समावेश "radio.h"


MODULE_DESCRIPTION("Broadcom B43legacy wireless driver");
MODULE_AUTHOR("Martin Langer");
MODULE_AUTHOR("Stefano Brivio");
MODULE_AUTHOR("Michael Buesch");
MODULE_LICENSE("GPL");

MODULE_FIRMWARE("b43legacy/ucode2.fw");
MODULE_FIRMWARE("b43legacy/ucode4.fw");

#अगर defined(CONFIG_B43LEGACY_DMA) && defined(CONFIG_B43LEGACY_PIO)
अटल पूर्णांक modparam_pio;
module_param_named(pio, modparam_pio, पूर्णांक, 0444);
MODULE_PARM_DESC(pio, "enable(1) / disable(0) PIO mode");
#या_अगर defined(CONFIG_B43LEGACY_DMA)
# define modparam_pio	0
#या_अगर defined(CONFIG_B43LEGACY_PIO)
# define modparam_pio	1
#पूर्ण_अगर

अटल पूर्णांक modparam_bad_frames_preempt;
module_param_named(bad_frames_preempt, modparam_bad_frames_preempt, पूर्णांक, 0444);
MODULE_PARM_DESC(bad_frames_preempt, "enable(1) / disable(0) Bad Frames"
		 " Preemption");

अटल अक्षर modparam_fwpostfix[16];
module_param_string(fwpostfix, modparam_fwpostfix, 16, 0444);
MODULE_PARM_DESC(fwpostfix, "Postfix for the firmware files to load.");

/* The following table supports BCM4301, BCM4303 and BCM4306/2 devices. */
अटल स्थिर काष्ठा ssb_device_id b43legacy_ssb_tbl[] = अणु
	SSB_DEVICE(SSB_VENDOR_BROADCOM, SSB_DEV_80211, 2),
	SSB_DEVICE(SSB_VENDOR_BROADCOM, SSB_DEV_80211, 4),
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(ssb, b43legacy_ssb_tbl);


/* Channel and ratetables are shared क्रम all devices.
 * They can't be स्थिर, because ieee80211 माला_दो some precalculated
 * data in there. This data is the same क्रम all devices, so we करोn't
 * get concurrency issues */
#घोषणा RATETAB_ENT(_rateid, _flags) \
	अणु								\
		.bitrate	= B43legacy_RATE_TO_100KBPS(_rateid),	\
		.hw_value	= (_rateid),				\
		.flags		= (_flags),				\
	पूर्ण
/*
 * NOTE: When changing this, sync with xmit.c's
 *	 b43legacy_plcp_get_bitrate_idx_* functions!
 */
अटल काष्ठा ieee80211_rate __b43legacy_ratetable[] = अणु
	RATETAB_ENT(B43legacy_CCK_RATE_1MB, 0),
	RATETAB_ENT(B43legacy_CCK_RATE_2MB, IEEE80211_RATE_SHORT_PREAMBLE),
	RATETAB_ENT(B43legacy_CCK_RATE_5MB, IEEE80211_RATE_SHORT_PREAMBLE),
	RATETAB_ENT(B43legacy_CCK_RATE_11MB, IEEE80211_RATE_SHORT_PREAMBLE),
	RATETAB_ENT(B43legacy_OFDM_RATE_6MB, 0),
	RATETAB_ENT(B43legacy_OFDM_RATE_9MB, 0),
	RATETAB_ENT(B43legacy_OFDM_RATE_12MB, 0),
	RATETAB_ENT(B43legacy_OFDM_RATE_18MB, 0),
	RATETAB_ENT(B43legacy_OFDM_RATE_24MB, 0),
	RATETAB_ENT(B43legacy_OFDM_RATE_36MB, 0),
	RATETAB_ENT(B43legacy_OFDM_RATE_48MB, 0),
	RATETAB_ENT(B43legacy_OFDM_RATE_54MB, 0),
पूर्ण;
#घोषणा b43legacy_b_ratetable		(__b43legacy_ratetable + 0)
#घोषणा b43legacy_b_ratetable_size	4
#घोषणा b43legacy_g_ratetable		(__b43legacy_ratetable + 0)
#घोषणा b43legacy_g_ratetable_size	12

#घोषणा CHANTAB_ENT(_chanid, _freq) \
	अणु							\
		.center_freq	= (_freq),			\
		.hw_value	= (_chanid),			\
	पूर्ण
अटल काष्ठा ieee80211_channel b43legacy_bg_chantable[] = अणु
	CHANTAB_ENT(1, 2412),
	CHANTAB_ENT(2, 2417),
	CHANTAB_ENT(3, 2422),
	CHANTAB_ENT(4, 2427),
	CHANTAB_ENT(5, 2432),
	CHANTAB_ENT(6, 2437),
	CHANTAB_ENT(7, 2442),
	CHANTAB_ENT(8, 2447),
	CHANTAB_ENT(9, 2452),
	CHANTAB_ENT(10, 2457),
	CHANTAB_ENT(11, 2462),
	CHANTAB_ENT(12, 2467),
	CHANTAB_ENT(13, 2472),
	CHANTAB_ENT(14, 2484),
पूर्ण;

अटल काष्ठा ieee80211_supported_band b43legacy_band_2GHz_BPHY = अणु
	.channels = b43legacy_bg_chantable,
	.n_channels = ARRAY_SIZE(b43legacy_bg_chantable),
	.bitrates = b43legacy_b_ratetable,
	.n_bitrates = b43legacy_b_ratetable_size,
पूर्ण;

अटल काष्ठा ieee80211_supported_band b43legacy_band_2GHz_GPHY = अणु
	.channels = b43legacy_bg_chantable,
	.n_channels = ARRAY_SIZE(b43legacy_bg_chantable),
	.bitrates = b43legacy_g_ratetable,
	.n_bitrates = b43legacy_g_ratetable_size,
पूर्ण;

अटल व्योम b43legacy_wireless_core_निकास(काष्ठा b43legacy_wldev *dev);
अटल पूर्णांक b43legacy_wireless_core_init(काष्ठा b43legacy_wldev *dev);
अटल व्योम b43legacy_wireless_core_stop(काष्ठा b43legacy_wldev *dev);
अटल पूर्णांक b43legacy_wireless_core_start(काष्ठा b43legacy_wldev *dev);


अटल पूर्णांक b43legacy_ratelimit(काष्ठा b43legacy_wl *wl)
अणु
	अगर (!wl || !wl->current_dev)
		वापस 1;
	अगर (b43legacy_status(wl->current_dev) < B43legacy_STAT_STARTED)
		वापस 1;
	/* We are up and running.
	 * Ratelimit the messages to aव्योम DoS over the net. */
	वापस net_ratelimit();
पूर्ण

व्योम b43legacyinfo(काष्ठा b43legacy_wl *wl, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (!b43legacy_ratelimit(wl))
		वापस;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	prपूर्णांकk(KERN_INFO "b43legacy-%s: %pV",
	       (wl && wl->hw) ? wiphy_name(wl->hw->wiphy) : "wlan", &vaf);

	बहु_पूर्ण(args);
पूर्ण

व्योम b43legacyerr(काष्ठा b43legacy_wl *wl, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (!b43legacy_ratelimit(wl))
		वापस;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	prपूर्णांकk(KERN_ERR "b43legacy-%s ERROR: %pV",
	       (wl && wl->hw) ? wiphy_name(wl->hw->wiphy) : "wlan", &vaf);

	बहु_पूर्ण(args);
पूर्ण

व्योम b43legacywarn(काष्ठा b43legacy_wl *wl, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (!b43legacy_ratelimit(wl))
		वापस;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	prपूर्णांकk(KERN_WARNING "b43legacy-%s warning: %pV",
	       (wl && wl->hw) ? wiphy_name(wl->hw->wiphy) : "wlan", &vaf);

	बहु_पूर्ण(args);
पूर्ण

#अगर B43legacy_DEBUG
व्योम b43legacydbg(काष्ठा b43legacy_wl *wl, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	prपूर्णांकk(KERN_DEBUG "b43legacy-%s debug: %pV",
	       (wl && wl->hw) ? wiphy_name(wl->hw->wiphy) : "wlan", &vaf);

	बहु_पूर्ण(args);
पूर्ण
#पूर्ण_अगर /* DEBUG */

अटल व्योम b43legacy_ram_ग_लिखो(काष्ठा b43legacy_wldev *dev, u16 offset,
				u32 val)
अणु
	u32 status;

	B43legacy_WARN_ON(offset % 4 != 0);

	status = b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCTL);
	अगर (status & B43legacy_MACCTL_BE)
		val = swab32(val);

	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_RAM_CONTROL, offset);
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_RAM_DATA, val);
पूर्ण

अटल अंतरभूत
व्योम b43legacy_shm_control_word(काष्ठा b43legacy_wldev *dev,
				u16 routing, u16 offset)
अणु
	u32 control;

	/* "offset" is the WORD offset. */

	control = routing;
	control <<= 16;
	control |= offset;
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_SHM_CONTROL, control);
पूर्ण

u32 b43legacy_shm_पढ़ो32(काष्ठा b43legacy_wldev *dev,
		       u16 routing, u16 offset)
अणु
	u32 ret;

	अगर (routing == B43legacy_SHM_SHARED) अणु
		B43legacy_WARN_ON((offset & 0x0001) != 0);
		अगर (offset & 0x0003) अणु
			/* Unaligned access */
			b43legacy_shm_control_word(dev, routing, offset >> 2);
			ret = b43legacy_पढ़ो16(dev,
				B43legacy_MMIO_SHM_DATA_UNALIGNED);
			ret <<= 16;
			b43legacy_shm_control_word(dev, routing,
						     (offset >> 2) + 1);
			ret |= b43legacy_पढ़ो16(dev, B43legacy_MMIO_SHM_DATA);

			वापस ret;
		पूर्ण
		offset >>= 2;
	पूर्ण
	b43legacy_shm_control_word(dev, routing, offset);
	ret = b43legacy_पढ़ो32(dev, B43legacy_MMIO_SHM_DATA);

	वापस ret;
पूर्ण

u16 b43legacy_shm_पढ़ो16(काष्ठा b43legacy_wldev *dev,
			   u16 routing, u16 offset)
अणु
	u16 ret;

	अगर (routing == B43legacy_SHM_SHARED) अणु
		B43legacy_WARN_ON((offset & 0x0001) != 0);
		अगर (offset & 0x0003) अणु
			/* Unaligned access */
			b43legacy_shm_control_word(dev, routing, offset >> 2);
			ret = b43legacy_पढ़ो16(dev,
					     B43legacy_MMIO_SHM_DATA_UNALIGNED);

			वापस ret;
		पूर्ण
		offset >>= 2;
	पूर्ण
	b43legacy_shm_control_word(dev, routing, offset);
	ret = b43legacy_पढ़ो16(dev, B43legacy_MMIO_SHM_DATA);

	वापस ret;
पूर्ण

व्योम b43legacy_shm_ग_लिखो32(काष्ठा b43legacy_wldev *dev,
			   u16 routing, u16 offset,
			   u32 value)
अणु
	अगर (routing == B43legacy_SHM_SHARED) अणु
		B43legacy_WARN_ON((offset & 0x0001) != 0);
		अगर (offset & 0x0003) अणु
			/* Unaligned access */
			b43legacy_shm_control_word(dev, routing, offset >> 2);
			b43legacy_ग_लिखो16(dev,
					  B43legacy_MMIO_SHM_DATA_UNALIGNED,
					  (value >> 16) & 0xffff);
			b43legacy_shm_control_word(dev, routing,
						   (offset >> 2) + 1);
			b43legacy_ग_लिखो16(dev, B43legacy_MMIO_SHM_DATA,
					  value & 0xffff);
			वापस;
		पूर्ण
		offset >>= 2;
	पूर्ण
	b43legacy_shm_control_word(dev, routing, offset);
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_SHM_DATA, value);
पूर्ण

व्योम b43legacy_shm_ग_लिखो16(काष्ठा b43legacy_wldev *dev, u16 routing, u16 offset,
			   u16 value)
अणु
	अगर (routing == B43legacy_SHM_SHARED) अणु
		B43legacy_WARN_ON((offset & 0x0001) != 0);
		अगर (offset & 0x0003) अणु
			/* Unaligned access */
			b43legacy_shm_control_word(dev, routing, offset >> 2);
			b43legacy_ग_लिखो16(dev,
					  B43legacy_MMIO_SHM_DATA_UNALIGNED,
					  value);
			वापस;
		पूर्ण
		offset >>= 2;
	पूर्ण
	b43legacy_shm_control_word(dev, routing, offset);
	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_SHM_DATA, value);
पूर्ण

/* Read HostFlags */
u32 b43legacy_hf_पढ़ो(काष्ठा b43legacy_wldev *dev)
अणु
	u32 ret;

	ret = b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_SHARED,
				   B43legacy_SHM_SH_HOSTFHI);
	ret <<= 16;
	ret |= b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_SHARED,
				    B43legacy_SHM_SH_HOSTFLO);

	वापस ret;
पूर्ण

/* Write HostFlags */
व्योम b43legacy_hf_ग_लिखो(काष्ठा b43legacy_wldev *dev, u32 value)
अणु
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED,
			      B43legacy_SHM_SH_HOSTFLO,
			      (value & 0x0000FFFF));
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED,
			      B43legacy_SHM_SH_HOSTFHI,
			      ((value & 0xFFFF0000) >> 16));
पूर्ण

व्योम b43legacy_tsf_पढ़ो(काष्ठा b43legacy_wldev *dev, u64 *tsf)
अणु
	/* We need to be careful. As we पढ़ो the TSF from multiple
	 * रेजिस्टरs, we should take care of रेजिस्टर overflows.
	 * In theory, the whole tsf पढ़ो process should be atomic.
	 * We try to be atomic here, by restaring the पढ़ो process,
	 * अगर any of the high रेजिस्टरs changed (overflew).
	 */
	अगर (dev->dev->id.revision >= 3) अणु
		u32 low;
		u32 high;
		u32 high2;

		करो अणु
			high = b43legacy_पढ़ो32(dev,
					B43legacy_MMIO_REV3PLUS_TSF_HIGH);
			low = b43legacy_पढ़ो32(dev,
					B43legacy_MMIO_REV3PLUS_TSF_LOW);
			high2 = b43legacy_पढ़ो32(dev,
					B43legacy_MMIO_REV3PLUS_TSF_HIGH);
		पूर्ण जबतक (unlikely(high != high2));

		*tsf = high;
		*tsf <<= 32;
		*tsf |= low;
	पूर्ण अन्यथा अणु
		u64 पंचांगp;
		u16 v0;
		u16 v1;
		u16 v2;
		u16 v3;
		u16 test1;
		u16 test2;
		u16 test3;

		करो अणु
			v3 = b43legacy_पढ़ो16(dev, B43legacy_MMIO_TSF_3);
			v2 = b43legacy_पढ़ो16(dev, B43legacy_MMIO_TSF_2);
			v1 = b43legacy_पढ़ो16(dev, B43legacy_MMIO_TSF_1);
			v0 = b43legacy_पढ़ो16(dev, B43legacy_MMIO_TSF_0);

			test3 = b43legacy_पढ़ो16(dev, B43legacy_MMIO_TSF_3);
			test2 = b43legacy_पढ़ो16(dev, B43legacy_MMIO_TSF_2);
			test1 = b43legacy_पढ़ो16(dev, B43legacy_MMIO_TSF_1);
		पूर्ण जबतक (v3 != test3 || v2 != test2 || v1 != test1);

		*tsf = v3;
		*tsf <<= 48;
		पंचांगp = v2;
		पंचांगp <<= 32;
		*tsf |= पंचांगp;
		पंचांगp = v1;
		पंचांगp <<= 16;
		*tsf |= पंचांगp;
		*tsf |= v0;
	पूर्ण
पूर्ण

अटल व्योम b43legacy_समय_lock(काष्ठा b43legacy_wldev *dev)
अणु
	u32 status;

	status = b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCTL);
	status |= B43legacy_MACCTL_TBTTHOLD;
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_MACCTL, status);
पूर्ण

अटल व्योम b43legacy_समय_unlock(काष्ठा b43legacy_wldev *dev)
अणु
	u32 status;

	status = b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCTL);
	status &= ~B43legacy_MACCTL_TBTTHOLD;
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_MACCTL, status);
पूर्ण

अटल व्योम b43legacy_tsf_ग_लिखो_locked(काष्ठा b43legacy_wldev *dev, u64 tsf)
अणु
	/* Be careful with the in-progress समयr.
	 * First zero out the low रेजिस्टर, so we have a full
	 * रेजिस्टर-overflow duration to complete the operation.
	 */
	अगर (dev->dev->id.revision >= 3) अणु
		u32 lo = (tsf & 0x00000000FFFFFFFFULL);
		u32 hi = (tsf & 0xFFFFFFFF00000000ULL) >> 32;

		b43legacy_ग_लिखो32(dev, B43legacy_MMIO_REV3PLUS_TSF_LOW, 0);
		b43legacy_ग_लिखो32(dev, B43legacy_MMIO_REV3PLUS_TSF_HIGH,
				    hi);
		b43legacy_ग_लिखो32(dev, B43legacy_MMIO_REV3PLUS_TSF_LOW,
				    lo);
	पूर्ण अन्यथा अणु
		u16 v0 = (tsf & 0x000000000000FFFFULL);
		u16 v1 = (tsf & 0x00000000FFFF0000ULL) >> 16;
		u16 v2 = (tsf & 0x0000FFFF00000000ULL) >> 32;
		u16 v3 = (tsf & 0xFFFF000000000000ULL) >> 48;

		b43legacy_ग_लिखो16(dev, B43legacy_MMIO_TSF_0, 0);
		b43legacy_ग_लिखो16(dev, B43legacy_MMIO_TSF_3, v3);
		b43legacy_ग_लिखो16(dev, B43legacy_MMIO_TSF_2, v2);
		b43legacy_ग_लिखो16(dev, B43legacy_MMIO_TSF_1, v1);
		b43legacy_ग_लिखो16(dev, B43legacy_MMIO_TSF_0, v0);
	पूर्ण
पूर्ण

व्योम b43legacy_tsf_ग_लिखो(काष्ठा b43legacy_wldev *dev, u64 tsf)
अणु
	b43legacy_समय_lock(dev);
	b43legacy_tsf_ग_लिखो_locked(dev, tsf);
	b43legacy_समय_unlock(dev);
पूर्ण

अटल
व्योम b43legacy_macfilter_set(काष्ठा b43legacy_wldev *dev,
			     u16 offset, स्थिर u8 *mac)
अणु
	अटल स्थिर u8 zero_addr[ETH_ALEN] = अणु 0 पूर्ण;
	u16 data;

	अगर (!mac)
		mac = zero_addr;

	offset |= 0x0020;
	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_MACFILTER_CONTROL, offset);

	data = mac[0];
	data |= mac[1] << 8;
	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_MACFILTER_DATA, data);
	data = mac[2];
	data |= mac[3] << 8;
	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_MACFILTER_DATA, data);
	data = mac[4];
	data |= mac[5] << 8;
	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_MACFILTER_DATA, data);
पूर्ण

अटल व्योम b43legacy_ग_लिखो_mac_bssid_ढाँचाs(काष्ठा b43legacy_wldev *dev)
अणु
	अटल स्थिर u8 zero_addr[ETH_ALEN] = अणु 0 पूर्ण;
	स्थिर u8 *mac = dev->wl->mac_addr;
	स्थिर u8 *bssid = dev->wl->bssid;
	u8 mac_bssid[ETH_ALEN * 2];
	पूर्णांक i;
	u32 पंचांगp;

	अगर (!bssid)
		bssid = zero_addr;
	अगर (!mac)
		mac = zero_addr;

	b43legacy_macfilter_set(dev, B43legacy_MACFILTER_BSSID, bssid);

	स_नकल(mac_bssid, mac, ETH_ALEN);
	स_नकल(mac_bssid + ETH_ALEN, bssid, ETH_ALEN);

	/* Write our MAC address and BSSID to ढाँचा ram */
	क्रम (i = 0; i < ARRAY_SIZE(mac_bssid); i += माप(u32)) अणु
		पंचांगp =  (u32)(mac_bssid[i + 0]);
		पंचांगp |= (u32)(mac_bssid[i + 1]) << 8;
		पंचांगp |= (u32)(mac_bssid[i + 2]) << 16;
		पंचांगp |= (u32)(mac_bssid[i + 3]) << 24;
		b43legacy_ram_ग_लिखो(dev, 0x20 + i, पंचांगp);
		b43legacy_ram_ग_लिखो(dev, 0x78 + i, पंचांगp);
		b43legacy_ram_ग_लिखो(dev, 0x478 + i, पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम b43legacy_upload_card_macaddress(काष्ठा b43legacy_wldev *dev)
अणु
	b43legacy_ग_लिखो_mac_bssid_ढाँचाs(dev);
	b43legacy_macfilter_set(dev, B43legacy_MACFILTER_SELF,
				dev->wl->mac_addr);
पूर्ण

अटल व्योम b43legacy_set_slot_समय(काष्ठा b43legacy_wldev *dev,
				    u16 slot_समय)
अणु
	/* slot_समय is in usec. */
	अगर (dev->phy.type != B43legacy_PHYTYPE_G)
		वापस;
	b43legacy_ग_लिखो16(dev, 0x684, 510 + slot_समय);
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED, 0x0010,
			      slot_समय);
पूर्ण

अटल व्योम b43legacy_लघु_slot_timing_enable(काष्ठा b43legacy_wldev *dev)
अणु
	b43legacy_set_slot_समय(dev, 9);
पूर्ण

अटल व्योम b43legacy_लघु_slot_timing_disable(काष्ठा b43legacy_wldev *dev)
अणु
	b43legacy_set_slot_समय(dev, 20);
पूर्ण

/* Synchronize IRQ top- and bottom-half.
 * IRQs must be masked beक्रमe calling this.
 * This must not be called with the irq_lock held.
 */
अटल व्योम b43legacy_synchronize_irq(काष्ठा b43legacy_wldev *dev)
अणु
	synchronize_irq(dev->dev->irq);
	tasklet_समाप्त(&dev->isr_tasklet);
पूर्ण

/* DummyTransmission function, as करोcumented on
 * https://bcm-specs.sipsolutions.net/DummyTransmission
 */
व्योम b43legacy_dummy_transmission(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक max_loop;
	u16 value;
	u32 buffer[5] = अणु
		0x00000000,
		0x00D40000,
		0x00000000,
		0x01000000,
		0x00000000,
	पूर्ण;

	चयन (phy->type) अणु
	हाल B43legacy_PHYTYPE_B:
	हाल B43legacy_PHYTYPE_G:
		max_loop = 0xFA;
		buffer[0] = 0x000B846E;
		अवरोध;
	शेष:
		B43legacy_BUG_ON(1);
		वापस;
	पूर्ण

	क्रम (i = 0; i < 5; i++)
		b43legacy_ram_ग_लिखो(dev, i * 4, buffer[i]);

	/* dummy पढ़ो follows */
	b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCTL);

	b43legacy_ग_लिखो16(dev, 0x0568, 0x0000);
	b43legacy_ग_लिखो16(dev, 0x07C0, 0x0000);
	b43legacy_ग_लिखो16(dev, 0x050C, 0x0000);
	b43legacy_ग_लिखो16(dev, 0x0508, 0x0000);
	b43legacy_ग_लिखो16(dev, 0x050A, 0x0000);
	b43legacy_ग_लिखो16(dev, 0x054C, 0x0000);
	b43legacy_ग_लिखो16(dev, 0x056A, 0x0014);
	b43legacy_ग_लिखो16(dev, 0x0568, 0x0826);
	b43legacy_ग_लिखो16(dev, 0x0500, 0x0000);
	b43legacy_ग_लिखो16(dev, 0x0502, 0x0030);

	अगर (phy->radio_ver == 0x2050 && phy->radio_rev <= 0x5)
		b43legacy_radio_ग_लिखो16(dev, 0x0051, 0x0017);
	क्रम (i = 0x00; i < max_loop; i++) अणु
		value = b43legacy_पढ़ो16(dev, 0x050E);
		अगर (value & 0x0080)
			अवरोध;
		udelay(10);
	पूर्ण
	क्रम (i = 0x00; i < 0x0A; i++) अणु
		value = b43legacy_पढ़ो16(dev, 0x050E);
		अगर (value & 0x0400)
			अवरोध;
		udelay(10);
	पूर्ण
	क्रम (i = 0x00; i < 0x0A; i++) अणु
		value = b43legacy_पढ़ो16(dev, 0x0690);
		अगर (!(value & 0x0100))
			अवरोध;
		udelay(10);
	पूर्ण
	अगर (phy->radio_ver == 0x2050 && phy->radio_rev <= 0x5)
		b43legacy_radio_ग_लिखो16(dev, 0x0051, 0x0037);
पूर्ण

/* Turn the Analog ON/OFF */
अटल व्योम b43legacy_चयन_analog(काष्ठा b43legacy_wldev *dev, पूर्णांक on)
अणु
	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_PHY0, on ? 0 : 0xF4);
पूर्ण

व्योम b43legacy_wireless_core_reset(काष्ठा b43legacy_wldev *dev, u32 flags)
अणु
	u32 पंचांगslow;
	u32 macctl;

	flags |= B43legacy_TMSLOW_PHYCLKEN;
	flags |= B43legacy_TMSLOW_PHYRESET;
	ssb_device_enable(dev->dev, flags);
	msleep(2); /* Wait क्रम the PLL to turn on. */

	/* Now take the PHY out of Reset again */
	पंचांगslow = ssb_पढ़ो32(dev->dev, SSB_TMSLOW);
	पंचांगslow |= SSB_TMSLOW_FGC;
	पंचांगslow &= ~B43legacy_TMSLOW_PHYRESET;
	ssb_ग_लिखो32(dev->dev, SSB_TMSLOW, पंचांगslow);
	ssb_पढ़ो32(dev->dev, SSB_TMSLOW); /* flush */
	msleep(1);
	पंचांगslow &= ~SSB_TMSLOW_FGC;
	ssb_ग_लिखो32(dev->dev, SSB_TMSLOW, पंचांगslow);
	ssb_पढ़ो32(dev->dev, SSB_TMSLOW); /* flush */
	msleep(1);

	/* Turn Analog ON */
	b43legacy_चयन_analog(dev, 1);

	macctl = b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCTL);
	macctl &= ~B43legacy_MACCTL_GMODE;
	अगर (flags & B43legacy_TMSLOW_GMODE) अणु
		macctl |= B43legacy_MACCTL_GMODE;
		dev->phy.gmode = true;
	पूर्ण अन्यथा
		dev->phy.gmode = false;
	macctl |= B43legacy_MACCTL_IHR_ENABLED;
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_MACCTL, macctl);
पूर्ण

अटल व्योम handle_irq_transmit_status(काष्ठा b43legacy_wldev *dev)
अणु
	u32 v0;
	u32 v1;
	u16 पंचांगp;
	काष्ठा b43legacy_txstatus stat;

	जबतक (1) अणु
		v0 = b43legacy_पढ़ो32(dev, B43legacy_MMIO_XMITSTAT_0);
		अगर (!(v0 & 0x00000001))
			अवरोध;
		v1 = b43legacy_पढ़ो32(dev, B43legacy_MMIO_XMITSTAT_1);

		stat.cookie = (v0 >> 16);
		stat.seq = (v1 & 0x0000FFFF);
		stat.phy_stat = ((v1 & 0x00FF0000) >> 16);
		पंचांगp = (v0 & 0x0000FFFF);
		stat.frame_count = ((पंचांगp & 0xF000) >> 12);
		stat.rts_count = ((पंचांगp & 0x0F00) >> 8);
		stat.supp_reason = ((पंचांगp & 0x001C) >> 2);
		stat.pm_indicated = !!(पंचांगp & 0x0080);
		stat.पूर्णांकermediate = !!(पंचांगp & 0x0040);
		stat.क्रम_ampdu = !!(पंचांगp & 0x0020);
		stat.acked = !!(पंचांगp & 0x0002);

		b43legacy_handle_txstatus(dev, &stat);
	पूर्ण
पूर्ण

अटल व्योम drain_txstatus_queue(काष्ठा b43legacy_wldev *dev)
अणु
	u32 dummy;

	अगर (dev->dev->id.revision < 5)
		वापस;
	/* Read all entries from the microcode TXstatus FIFO
	 * and throw them away.
	 */
	जबतक (1) अणु
		dummy = b43legacy_पढ़ो32(dev, B43legacy_MMIO_XMITSTAT_0);
		अगर (!(dummy & 0x00000001))
			अवरोध;
		dummy = b43legacy_पढ़ो32(dev, B43legacy_MMIO_XMITSTAT_1);
	पूर्ण
पूर्ण

अटल u32 b43legacy_jssi_पढ़ो(काष्ठा b43legacy_wldev *dev)
अणु
	u32 val = 0;

	val = b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_SHARED, 0x40A);
	val <<= 16;
	val |= b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_SHARED, 0x408);

	वापस val;
पूर्ण

अटल व्योम b43legacy_jssi_ग_लिखो(काष्ठा b43legacy_wldev *dev, u32 jssi)
अणु
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED, 0x408,
			      (jssi & 0x0000FFFF));
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED, 0x40A,
			      (jssi & 0xFFFF0000) >> 16);
पूर्ण

अटल व्योम b43legacy_generate_noise_sample(काष्ठा b43legacy_wldev *dev)
अणु
	b43legacy_jssi_ग_लिखो(dev, 0x7F7F7F7F);
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_MACCMD,
			  b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCMD)
			  | B43legacy_MACCMD_BGNOISE);
	B43legacy_WARN_ON(dev->noisecalc.channel_at_start !=
			    dev->phy.channel);
पूर्ण

अटल व्योम b43legacy_calculate_link_quality(काष्ठा b43legacy_wldev *dev)
अणु
	/* Top half of Link Quality calculation. */

	अगर (dev->noisecalc.calculation_running)
		वापस;
	dev->noisecalc.channel_at_start = dev->phy.channel;
	dev->noisecalc.calculation_running = true;
	dev->noisecalc.nr_samples = 0;

	b43legacy_generate_noise_sample(dev);
पूर्ण

अटल व्योम handle_irq_noise(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u16 पंचांगp;
	u8 noise[4];
	u8 i;
	u8 j;
	s32 average;

	/* Bottom half of Link Quality calculation. */

	B43legacy_WARN_ON(!dev->noisecalc.calculation_running);
	अगर (dev->noisecalc.channel_at_start != phy->channel)
		जाओ drop_calculation;
	*((__le32 *)noise) = cpu_to_le32(b43legacy_jssi_पढ़ो(dev));
	अगर (noise[0] == 0x7F || noise[1] == 0x7F ||
	    noise[2] == 0x7F || noise[3] == 0x7F)
		जाओ generate_new;

	/* Get the noise samples. */
	B43legacy_WARN_ON(dev->noisecalc.nr_samples >= 8);
	i = dev->noisecalc.nr_samples;
	noise[0] = clamp_val(noise[0], 0, ARRAY_SIZE(phy->nrssi_lt) - 1);
	noise[1] = clamp_val(noise[1], 0, ARRAY_SIZE(phy->nrssi_lt) - 1);
	noise[2] = clamp_val(noise[2], 0, ARRAY_SIZE(phy->nrssi_lt) - 1);
	noise[3] = clamp_val(noise[3], 0, ARRAY_SIZE(phy->nrssi_lt) - 1);
	dev->noisecalc.samples[i][0] = phy->nrssi_lt[noise[0]];
	dev->noisecalc.samples[i][1] = phy->nrssi_lt[noise[1]];
	dev->noisecalc.samples[i][2] = phy->nrssi_lt[noise[2]];
	dev->noisecalc.samples[i][3] = phy->nrssi_lt[noise[3]];
	dev->noisecalc.nr_samples++;
	अगर (dev->noisecalc.nr_samples == 8) अणु
		/* Calculate the Link Quality by the noise samples. */
		average = 0;
		क्रम (i = 0; i < 8; i++) अणु
			क्रम (j = 0; j < 4; j++)
				average += dev->noisecalc.samples[i][j];
		पूर्ण
		average /= (8 * 4);
		average *= 125;
		average += 64;
		average /= 128;
		पंचांगp = b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_SHARED,
					     0x40C);
		पंचांगp = (पंचांगp / 128) & 0x1F;
		अगर (पंचांगp >= 8)
			average += 2;
		अन्यथा
			average -= 25;
		अगर (पंचांगp == 8)
			average -= 72;
		अन्यथा
			average -= 48;

		dev->stats.link_noise = average;
drop_calculation:
		dev->noisecalc.calculation_running = false;
		वापस;
	पूर्ण
generate_new:
	b43legacy_generate_noise_sample(dev);
पूर्ण

अटल व्योम handle_irq_tbtt_indication(काष्ठा b43legacy_wldev *dev)
अणु
	अगर (b43legacy_is_mode(dev->wl, NL80211_IFTYPE_AP)) अणु
		/* TODO: PS TBTT */
	पूर्ण अन्यथा अणु
		अगर (1/*FIXME: the last PSpoll frame was sent successfully */)
			b43legacy_घातer_saving_ctl_bits(dev, -1, -1);
	पूर्ण
	अगर (b43legacy_is_mode(dev->wl, NL80211_IFTYPE_ADHOC))
		dev->dfq_valid = true;
पूर्ण

अटल व्योम handle_irq_atim_end(काष्ठा b43legacy_wldev *dev)
अणु
	अगर (dev->dfq_valid) अणु
		b43legacy_ग_लिखो32(dev, B43legacy_MMIO_MACCMD,
				  b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCMD)
				  | B43legacy_MACCMD_DFQ_VALID);
		dev->dfq_valid = false;
	पूर्ण
पूर्ण

अटल व्योम handle_irq_pmq(काष्ठा b43legacy_wldev *dev)
अणु
	u32 पंचांगp;

	/* TODO: AP mode. */

	जबतक (1) अणु
		पंचांगp = b43legacy_पढ़ो32(dev, B43legacy_MMIO_PS_STATUS);
		अगर (!(पंचांगp & 0x00000008))
			अवरोध;
	पूर्ण
	/* 16bit ग_लिखो is odd, but correct. */
	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_PS_STATUS, 0x0002);
पूर्ण

अटल व्योम b43legacy_ग_लिखो_ढाँचा_common(काष्ठा b43legacy_wldev *dev,
					    स्थिर u8 *data, u16 size,
					    u16 ram_offset,
					    u16 shm_size_offset, u8 rate)
अणु
	u32 i;
	u32 पंचांगp;
	काष्ठा b43legacy_plcp_hdr4 plcp;

	plcp.data = 0;
	b43legacy_generate_plcp_hdr(&plcp, size + FCS_LEN, rate);
	b43legacy_ram_ग_लिखो(dev, ram_offset, le32_to_cpu(plcp.data));
	ram_offset += माप(u32);
	/* The PLCP is 6 bytes दीर्घ, but we only wrote 4 bytes, yet.
	 * So leave the first two bytes of the next ग_लिखो blank.
	 */
	पंचांगp = (u32)(data[0]) << 16;
	पंचांगp |= (u32)(data[1]) << 24;
	b43legacy_ram_ग_लिखो(dev, ram_offset, पंचांगp);
	ram_offset += माप(u32);
	क्रम (i = 2; i < size; i += माप(u32)) अणु
		पंचांगp = (u32)(data[i + 0]);
		अगर (i + 1 < size)
			पंचांगp |= (u32)(data[i + 1]) << 8;
		अगर (i + 2 < size)
			पंचांगp |= (u32)(data[i + 2]) << 16;
		अगर (i + 3 < size)
			पंचांगp |= (u32)(data[i + 3]) << 24;
		b43legacy_ram_ग_लिखो(dev, ram_offset + i - 2, पंचांगp);
	पूर्ण
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED, shm_size_offset,
			      size + माप(काष्ठा b43legacy_plcp_hdr6));
पूर्ण

/* Convert a b43legacy antenna number value to the PHY TX control value. */
अटल u16 b43legacy_antenna_to_phyctl(पूर्णांक antenna)
अणु
	चयन (antenna) अणु
	हाल B43legacy_ANTENNA0:
		वापस B43legacy_TX4_PHY_ANT0;
	हाल B43legacy_ANTENNA1:
		वापस B43legacy_TX4_PHY_ANT1;
	पूर्ण
	वापस B43legacy_TX4_PHY_ANTLAST;
पूर्ण

अटल व्योम b43legacy_ग_लिखो_beacon_ढाँचा(काष्ठा b43legacy_wldev *dev,
					    u16 ram_offset,
					    u16 shm_size_offset)
अणु

	अचिन्हित पूर्णांक i, len, variable_len;
	स्थिर काष्ठा ieee80211_mgmt *bcn;
	स्थिर u8 *ie;
	bool tim_found = false;
	अचिन्हित पूर्णांक rate;
	u16 ctl;
	पूर्णांक antenna;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(dev->wl->current_beacon);

	bcn = (स्थिर काष्ठा ieee80211_mgmt *)(dev->wl->current_beacon->data);
	len = min_t(माप_प्रकार, dev->wl->current_beacon->len,
		  0x200 - माप(काष्ठा b43legacy_plcp_hdr6));
	rate = ieee80211_get_tx_rate(dev->wl->hw, info)->hw_value;

	b43legacy_ग_लिखो_ढाँचा_common(dev, (स्थिर u8 *)bcn, len, ram_offset,
					shm_size_offset, rate);

	/* Write the PHY TX control parameters. */
	antenna = B43legacy_ANTENNA_DEFAULT;
	antenna = b43legacy_antenna_to_phyctl(antenna);
	ctl = b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_SHARED,
				   B43legacy_SHM_SH_BEACPHYCTL);
	/* We can't send beacons with लघु preamble. Would get PHY errors. */
	ctl &= ~B43legacy_TX4_PHY_SHORTPRMBL;
	ctl &= ~B43legacy_TX4_PHY_ANT;
	ctl &= ~B43legacy_TX4_PHY_ENC;
	ctl |= antenna;
	ctl |= B43legacy_TX4_PHY_ENC_CCK;
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED,
			      B43legacy_SHM_SH_BEACPHYCTL, ctl);

	/* Find the position of the TIM and the DTIM_period value
	 * and ग_लिखो them to SHM. */
	ie = bcn->u.beacon.variable;
	variable_len = len - दुरत्व(काष्ठा ieee80211_mgmt, u.beacon.variable);
	क्रम (i = 0; i < variable_len - 2; ) अणु
		uपूर्णांक8_t ie_id, ie_len;

		ie_id = ie[i];
		ie_len = ie[i + 1];
		अगर (ie_id == 5) अणु
			u16 tim_position;
			u16 dtim_period;
			/* This is the TIM Inक्रमmation Element */

			/* Check whether the ie_len is in the beacon data range. */
			अगर (variable_len < ie_len + 2 + i)
				अवरोध;
			/* A valid TIM is at least 4 bytes दीर्घ. */
			अगर (ie_len < 4)
				अवरोध;
			tim_found = true;

			tim_position = माप(काष्ठा b43legacy_plcp_hdr6);
			tim_position += दुरत्व(काष्ठा ieee80211_mgmt,
						 u.beacon.variable);
			tim_position += i;

			dtim_period = ie[i + 3];

			b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED,
					B43legacy_SHM_SH_TIMPOS, tim_position);
			b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED,
					B43legacy_SHM_SH_DTIMP, dtim_period);
			अवरोध;
		पूर्ण
		i += ie_len + 2;
	पूर्ण
	अगर (!tim_found) अणु
		b43legacywarn(dev->wl, "Did not find a valid TIM IE in the "
			      "beacon template packet. AP or IBSS operation "
			      "may be broken.\n");
	पूर्ण अन्यथा
		b43legacydbg(dev->wl, "Updated beacon template\n");
पूर्ण

अटल व्योम b43legacy_ग_लिखो_probe_resp_plcp(काष्ठा b43legacy_wldev *dev,
					    u16 shm_offset, u16 size,
					    काष्ठा ieee80211_rate *rate)
अणु
	काष्ठा b43legacy_plcp_hdr4 plcp;
	u32 पंचांगp;
	__le16 dur;

	plcp.data = 0;
	b43legacy_generate_plcp_hdr(&plcp, size + FCS_LEN, rate->hw_value);
	dur = ieee80211_generic_frame_duration(dev->wl->hw,
					       dev->wl->vअगर,
					       NL80211_BAND_2GHZ,
					       size,
					       rate);
	/* Write PLCP in two parts and timing क्रम packet transfer */
	पंचांगp = le32_to_cpu(plcp.data);
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED, shm_offset,
			      पंचांगp & 0xFFFF);
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED, shm_offset + 2,
			      पंचांगp >> 16);
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED, shm_offset + 6,
			      le16_to_cpu(dur));
पूर्ण

/* Instead of using custom probe response ढाँचा, this function
 * just patches custom beacon ढाँचा by:
 * 1) Changing packet type
 * 2) Patching duration field
 * 3) Stripping TIM
 */
अटल स्थिर u8 *b43legacy_generate_probe_resp(काष्ठा b43legacy_wldev *dev,
					       u16 *dest_size,
					       काष्ठा ieee80211_rate *rate)
अणु
	स्थिर u8 *src_data;
	u8 *dest_data;
	u16 src_size, elem_size, src_pos, dest_pos;
	__le16 dur;
	काष्ठा ieee80211_hdr *hdr;
	माप_प्रकार ie_start;

	src_size = dev->wl->current_beacon->len;
	src_data = (स्थिर u8 *)dev->wl->current_beacon->data;

	/* Get the start offset of the variable IEs in the packet. */
	ie_start = दुरत्व(काष्ठा ieee80211_mgmt, u.probe_resp.variable);
	B43legacy_WARN_ON(ie_start != दुरत्व(काष्ठा ieee80211_mgmt,
					       u.beacon.variable));

	अगर (B43legacy_WARN_ON(src_size < ie_start))
		वापस शून्य;

	dest_data = kदो_स्मृति(src_size, GFP_ATOMIC);
	अगर (unlikely(!dest_data))
		वापस शून्य;

	/* Copy the अटल data and all Inक्रमmation Elements, except the TIM. */
	स_नकल(dest_data, src_data, ie_start);
	src_pos = ie_start;
	dest_pos = ie_start;
	क्रम ( ; src_pos < src_size - 2; src_pos += elem_size) अणु
		elem_size = src_data[src_pos + 1] + 2;
		अगर (src_data[src_pos] == 5) अणु
			/* This is the TIM. */
			जारी;
		पूर्ण
		स_नकल(dest_data + dest_pos, src_data + src_pos, elem_size);
		dest_pos += elem_size;
	पूर्ण
	*dest_size = dest_pos;
	hdr = (काष्ठा ieee80211_hdr *)dest_data;

	/* Set the frame control. */
	hdr->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
					 IEEE80211_STYPE_PROBE_RESP);
	dur = ieee80211_generic_frame_duration(dev->wl->hw,
					       dev->wl->vअगर,
					       NL80211_BAND_2GHZ,
					       *dest_size,
					       rate);
	hdr->duration_id = dur;

	वापस dest_data;
पूर्ण

अटल व्योम b43legacy_ग_लिखो_probe_resp_ढाँचा(काष्ठा b43legacy_wldev *dev,
						u16 ram_offset,
						u16 shm_size_offset,
						काष्ठा ieee80211_rate *rate)
अणु
	स्थिर u8 *probe_resp_data;
	u16 size;

	size = dev->wl->current_beacon->len;
	probe_resp_data = b43legacy_generate_probe_resp(dev, &size, rate);
	अगर (unlikely(!probe_resp_data))
		वापस;

	/* Looks like PLCP headers plus packet timings are stored क्रम
	 * all possible basic rates
	 */
	b43legacy_ग_लिखो_probe_resp_plcp(dev, 0x31A, size,
					&b43legacy_b_ratetable[0]);
	b43legacy_ग_लिखो_probe_resp_plcp(dev, 0x32C, size,
					&b43legacy_b_ratetable[1]);
	b43legacy_ग_लिखो_probe_resp_plcp(dev, 0x33E, size,
					&b43legacy_b_ratetable[2]);
	b43legacy_ग_लिखो_probe_resp_plcp(dev, 0x350, size,
					&b43legacy_b_ratetable[3]);

	size = min_t(माप_प्रकार, size,
		   0x200 - माप(काष्ठा b43legacy_plcp_hdr6));
	b43legacy_ग_लिखो_ढाँचा_common(dev, probe_resp_data,
					size, ram_offset,
					shm_size_offset, rate->hw_value);
	kमुक्त(probe_resp_data);
पूर्ण

अटल व्योम b43legacy_upload_beacon0(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_wl *wl = dev->wl;

	अगर (wl->beacon0_uploaded)
		वापस;
	b43legacy_ग_लिखो_beacon_ढाँचा(dev, 0x68, 0x18);
	/* FIXME: Probe resp upload करोesn't really beदीर्घ here,
	 *        but we करोn't use that feature anyway. */
	b43legacy_ग_लिखो_probe_resp_ढाँचा(dev, 0x268, 0x4A,
				      &__b43legacy_ratetable[3]);
	wl->beacon0_uploaded = true;
पूर्ण

अटल व्योम b43legacy_upload_beacon1(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_wl *wl = dev->wl;

	अगर (wl->beacon1_uploaded)
		वापस;
	b43legacy_ग_लिखो_beacon_ढाँचा(dev, 0x468, 0x1A);
	wl->beacon1_uploaded = true;
पूर्ण

अटल व्योम handle_irq_beacon(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_wl *wl = dev->wl;
	u32 cmd, beacon0_valid, beacon1_valid;

	अगर (!b43legacy_is_mode(wl, NL80211_IFTYPE_AP))
		वापस;

	/* This is the bottom half of the asynchronous beacon update. */

	/* Ignore पूर्णांकerrupt in the future. */
	dev->irq_mask &= ~B43legacy_IRQ_BEACON;

	cmd = b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCMD);
	beacon0_valid = (cmd & B43legacy_MACCMD_BEACON0_VALID);
	beacon1_valid = (cmd & B43legacy_MACCMD_BEACON1_VALID);

	/* Schedule पूर्णांकerrupt manually, अगर busy. */
	अगर (beacon0_valid && beacon1_valid) अणु
		b43legacy_ग_लिखो32(dev, B43legacy_MMIO_GEN_IRQ_REASON, B43legacy_IRQ_BEACON);
		dev->irq_mask |= B43legacy_IRQ_BEACON;
		वापस;
	पूर्ण

	अगर (unlikely(wl->beacon_ढाँचाs_virgin)) अणु
		/* We never uploaded a beacon beक्रमe.
		 * Upload both ढाँचाs now, but only mark one valid. */
		wl->beacon_ढाँचाs_virgin = false;
		b43legacy_upload_beacon0(dev);
		b43legacy_upload_beacon1(dev);
		cmd = b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCMD);
		cmd |= B43legacy_MACCMD_BEACON0_VALID;
		b43legacy_ग_लिखो32(dev, B43legacy_MMIO_MACCMD, cmd);
	पूर्ण अन्यथा अणु
		अगर (!beacon0_valid) अणु
			b43legacy_upload_beacon0(dev);
			cmd = b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCMD);
			cmd |= B43legacy_MACCMD_BEACON0_VALID;
			b43legacy_ग_लिखो32(dev, B43legacy_MMIO_MACCMD, cmd);
		पूर्ण अन्यथा अगर (!beacon1_valid) अणु
			b43legacy_upload_beacon1(dev);
			cmd = b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCMD);
			cmd |= B43legacy_MACCMD_BEACON1_VALID;
			b43legacy_ग_लिखो32(dev, B43legacy_MMIO_MACCMD, cmd);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम b43legacy_beacon_update_trigger_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा b43legacy_wl *wl = container_of(work, काष्ठा b43legacy_wl,
					 beacon_update_trigger);
	काष्ठा b43legacy_wldev *dev;

	mutex_lock(&wl->mutex);
	dev = wl->current_dev;
	अगर (likely(dev && (b43legacy_status(dev) >= B43legacy_STAT_INITIALIZED))) अणु
		spin_lock_irq(&wl->irq_lock);
		/* Update beacon right away or defer to IRQ. */
		handle_irq_beacon(dev);
		/* The handler might have updated the IRQ mask. */
		b43legacy_ग_लिखो32(dev, B43legacy_MMIO_GEN_IRQ_MASK,
				  dev->irq_mask);
		spin_unlock_irq(&wl->irq_lock);
	पूर्ण
	mutex_unlock(&wl->mutex);
पूर्ण

/* Asynchronously update the packet ढाँचाs in ढाँचा RAM.
 * Locking: Requires wl->irq_lock to be locked. */
अटल व्योम b43legacy_update_ढाँचाs(काष्ठा b43legacy_wl *wl)
अणु
	काष्ठा sk_buff *beacon;
	/* This is the top half of the ansynchronous beacon update. The bottom
	 * half is the beacon IRQ. Beacon update must be asynchronous to aव्योम
	 * sending an invalid beacon. This can happen क्रम example, अगर the
	 * firmware transmits a beacon जबतक we are updating it. */

	/* We could modअगरy the existing beacon and set the aid bit in the TIM
	 * field, but that would probably require resizing and moving of data
	 * within the beacon ढाँचा. Simply request a new beacon and let
	 * mac80211 करो the hard work. */
	beacon = ieee80211_beacon_get(wl->hw, wl->vअगर);
	अगर (unlikely(!beacon))
		वापस;

	अगर (wl->current_beacon)
		dev_kमुक्त_skb_any(wl->current_beacon);
	wl->current_beacon = beacon;
	wl->beacon0_uploaded = false;
	wl->beacon1_uploaded = false;
	ieee80211_queue_work(wl->hw, &wl->beacon_update_trigger);
पूर्ण

अटल व्योम b43legacy_set_beacon_पूर्णांक(काष्ठा b43legacy_wldev *dev,
				     u16 beacon_पूर्णांक)
अणु
	b43legacy_समय_lock(dev);
	अगर (dev->dev->id.revision >= 3) अणु
		b43legacy_ग_लिखो32(dev, B43legacy_MMIO_TSF_CFP_REP,
				 (beacon_पूर्णांक << 16));
		b43legacy_ग_लिखो32(dev, B43legacy_MMIO_TSF_CFP_START,
				 (beacon_पूर्णांक << 10));
	पूर्ण अन्यथा अणु
		b43legacy_ग_लिखो16(dev, 0x606, (beacon_पूर्णांक >> 6));
		b43legacy_ग_लिखो16(dev, 0x610, beacon_पूर्णांक);
	पूर्ण
	b43legacy_समय_unlock(dev);
	b43legacydbg(dev->wl, "Set beacon interval to %u\n", beacon_पूर्णांक);
पूर्ण

अटल व्योम handle_irq_ucode_debug(काष्ठा b43legacy_wldev *dev)
अणु
पूर्ण

/* Interrupt handler bottom-half */
अटल व्योम b43legacy_पूर्णांकerrupt_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा b43legacy_wldev *dev = from_tasklet(dev, t, isr_tasklet);
	u32 reason;
	u32 dma_reason[ARRAY_SIZE(dev->dma_reason)];
	u32 merged_dma_reason = 0;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->wl->irq_lock, flags);

	B43legacy_WARN_ON(b43legacy_status(dev) <
			  B43legacy_STAT_INITIALIZED);

	reason = dev->irq_reason;
	क्रम (i = 0; i < ARRAY_SIZE(dma_reason); i++) अणु
		dma_reason[i] = dev->dma_reason[i];
		merged_dma_reason |= dma_reason[i];
	पूर्ण

	अगर (unlikely(reason & B43legacy_IRQ_MAC_TXERR))
		b43legacyerr(dev->wl, "MAC transmission error\n");

	अगर (unlikely(reason & B43legacy_IRQ_PHY_TXERR)) अणु
		b43legacyerr(dev->wl, "PHY transmission error\n");
		rmb();
		अगर (unlikely(atomic_dec_and_test(&dev->phy.txerr_cnt))) अणु
			b43legacyerr(dev->wl, "Too many PHY TX errors, "
					      "restarting the controller\n");
			b43legacy_controller_restart(dev, "PHY TX errors");
		पूर्ण
	पूर्ण

	अगर (unlikely(merged_dma_reason & (B43legacy_DMAIRQ_FATALMASK |
					  B43legacy_DMAIRQ_NONFATALMASK))) अणु
		अगर (merged_dma_reason & B43legacy_DMAIRQ_FATALMASK) अणु
			b43legacyerr(dev->wl, "Fatal DMA error: "
			       "0x%08X, 0x%08X, 0x%08X, "
			       "0x%08X, 0x%08X, 0x%08X\n",
			       dma_reason[0], dma_reason[1],
			       dma_reason[2], dma_reason[3],
			       dma_reason[4], dma_reason[5]);
			b43legacy_controller_restart(dev, "DMA error");
			spin_unlock_irqrestore(&dev->wl->irq_lock, flags);
			वापस;
		पूर्ण
		अगर (merged_dma_reason & B43legacy_DMAIRQ_NONFATALMASK)
			b43legacyerr(dev->wl, "DMA error: "
			       "0x%08X, 0x%08X, 0x%08X, "
			       "0x%08X, 0x%08X, 0x%08X\n",
			       dma_reason[0], dma_reason[1],
			       dma_reason[2], dma_reason[3],
			       dma_reason[4], dma_reason[5]);
	पूर्ण

	अगर (unlikely(reason & B43legacy_IRQ_UCODE_DEBUG))
		handle_irq_ucode_debug(dev);
	अगर (reason & B43legacy_IRQ_TBTT_INDI)
		handle_irq_tbtt_indication(dev);
	अगर (reason & B43legacy_IRQ_ATIM_END)
		handle_irq_atim_end(dev);
	अगर (reason & B43legacy_IRQ_BEACON)
		handle_irq_beacon(dev);
	अगर (reason & B43legacy_IRQ_PMQ)
		handle_irq_pmq(dev);
	अगर (reason & B43legacy_IRQ_TXFIFO_FLUSH_OK) अणु
		;/*TODO*/
	पूर्ण
	अगर (reason & B43legacy_IRQ_NOISESAMPLE_OK)
		handle_irq_noise(dev);

	/* Check the DMA reason रेजिस्टरs क्रम received data. */
	अगर (dma_reason[0] & B43legacy_DMAIRQ_RX_DONE) अणु
		अगर (b43legacy_using_pio(dev))
			b43legacy_pio_rx(dev->pio.queue0);
		अन्यथा
			b43legacy_dma_rx(dev->dma.rx_ring0);
	पूर्ण
	B43legacy_WARN_ON(dma_reason[1] & B43legacy_DMAIRQ_RX_DONE);
	B43legacy_WARN_ON(dma_reason[2] & B43legacy_DMAIRQ_RX_DONE);
	अगर (dma_reason[3] & B43legacy_DMAIRQ_RX_DONE) अणु
		अगर (b43legacy_using_pio(dev))
			b43legacy_pio_rx(dev->pio.queue3);
		अन्यथा
			b43legacy_dma_rx(dev->dma.rx_ring3);
	पूर्ण
	B43legacy_WARN_ON(dma_reason[4] & B43legacy_DMAIRQ_RX_DONE);
	B43legacy_WARN_ON(dma_reason[5] & B43legacy_DMAIRQ_RX_DONE);

	अगर (reason & B43legacy_IRQ_TX_OK)
		handle_irq_transmit_status(dev);

	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_GEN_IRQ_MASK, dev->irq_mask);
	spin_unlock_irqrestore(&dev->wl->irq_lock, flags);
पूर्ण

अटल व्योम pio_irq_workaround(काष्ठा b43legacy_wldev *dev,
			       u16 base, पूर्णांक queueidx)
अणु
	u16 rxctl;

	rxctl = b43legacy_पढ़ो16(dev, base + B43legacy_PIO_RXCTL);
	अगर (rxctl & B43legacy_PIO_RXCTL_DATAAVAILABLE)
		dev->dma_reason[queueidx] |= B43legacy_DMAIRQ_RX_DONE;
	अन्यथा
		dev->dma_reason[queueidx] &= ~B43legacy_DMAIRQ_RX_DONE;
पूर्ण

अटल व्योम b43legacy_पूर्णांकerrupt_ack(काष्ठा b43legacy_wldev *dev, u32 reason)
अणु
	अगर (b43legacy_using_pio(dev) &&
	    (dev->dev->id.revision < 3) &&
	    (!(reason & B43legacy_IRQ_PIO_WORKAROUND))) अणु
		/* Apply a PIO specअगरic workaround to the dma_reasons */
		pio_irq_workaround(dev, B43legacy_MMIO_PIO1_BASE, 0);
		pio_irq_workaround(dev, B43legacy_MMIO_PIO2_BASE, 1);
		pio_irq_workaround(dev, B43legacy_MMIO_PIO3_BASE, 2);
		pio_irq_workaround(dev, B43legacy_MMIO_PIO4_BASE, 3);
	पूर्ण

	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_GEN_IRQ_REASON, reason);

	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_DMA0_REASON,
			  dev->dma_reason[0]);
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_DMA1_REASON,
			  dev->dma_reason[1]);
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_DMA2_REASON,
			  dev->dma_reason[2]);
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_DMA3_REASON,
			  dev->dma_reason[3]);
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_DMA4_REASON,
			  dev->dma_reason[4]);
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_DMA5_REASON,
			  dev->dma_reason[5]);
पूर्ण

/* Interrupt handler top-half */
अटल irqवापस_t b43legacy_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	irqवापस_t ret = IRQ_NONE;
	काष्ठा b43legacy_wldev *dev = dev_id;
	u32 reason;

	B43legacy_WARN_ON(!dev);

	spin_lock(&dev->wl->irq_lock);

	अगर (unlikely(b43legacy_status(dev) < B43legacy_STAT_STARTED))
		/* This can only happen on shared IRQ lines. */
		जाओ out;
	reason = b43legacy_पढ़ो32(dev, B43legacy_MMIO_GEN_IRQ_REASON);
	अगर (reason == 0xffffffff) /* shared IRQ */
		जाओ out;
	ret = IRQ_HANDLED;
	reason &= dev->irq_mask;
	अगर (!reason)
		जाओ out;

	dev->dma_reason[0] = b43legacy_पढ़ो32(dev,
					      B43legacy_MMIO_DMA0_REASON)
					      & 0x0001DC00;
	dev->dma_reason[1] = b43legacy_पढ़ो32(dev,
					      B43legacy_MMIO_DMA1_REASON)
					      & 0x0000DC00;
	dev->dma_reason[2] = b43legacy_पढ़ो32(dev,
					      B43legacy_MMIO_DMA2_REASON)
					      & 0x0000DC00;
	dev->dma_reason[3] = b43legacy_पढ़ो32(dev,
					      B43legacy_MMIO_DMA3_REASON)
					      & 0x0001DC00;
	dev->dma_reason[4] = b43legacy_पढ़ो32(dev,
					      B43legacy_MMIO_DMA4_REASON)
					      & 0x0000DC00;
	dev->dma_reason[5] = b43legacy_पढ़ो32(dev,
					      B43legacy_MMIO_DMA5_REASON)
					      & 0x0000DC00;

	b43legacy_पूर्णांकerrupt_ack(dev, reason);
	/* Disable all IRQs. They are enabled again in the bottom half. */
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_GEN_IRQ_MASK, 0);
	/* Save the reason code and call our bottom half. */
	dev->irq_reason = reason;
	tasklet_schedule(&dev->isr_tasklet);
out:
	spin_unlock(&dev->wl->irq_lock);

	वापस ret;
पूर्ण

अटल व्योम b43legacy_release_firmware(काष्ठा b43legacy_wldev *dev)
अणु
	release_firmware(dev->fw.ucode);
	dev->fw.ucode = शून्य;
	release_firmware(dev->fw.pcm);
	dev->fw.pcm = शून्य;
	release_firmware(dev->fw.initvals);
	dev->fw.initvals = शून्य;
	release_firmware(dev->fw.initvals_band);
	dev->fw.initvals_band = शून्य;
पूर्ण

अटल व्योम b43legacy_prपूर्णांक_fw_helptext(काष्ठा b43legacy_wl *wl)
अणु
	b43legacyerr(wl, "You must go to https://wireless.wiki.kernel.org/en/"
		     "users/Drivers/b43#devicefirmware "
		     "and download the correct firmware (version 3).\n");
पूर्ण

अटल व्योम b43legacy_fw_cb(स्थिर काष्ठा firmware *firmware, व्योम *context)
अणु
	काष्ठा b43legacy_wldev *dev = context;

	dev->fwp = firmware;
	complete(&dev->fw_load_complete);
पूर्ण

अटल पूर्णांक करो_request_fw(काष्ठा b43legacy_wldev *dev,
			 स्थिर अक्षर *name,
			 स्थिर काष्ठा firmware **fw, bool async)
अणु
	अक्षर path[माप(modparam_fwpostfix) + 32];
	काष्ठा b43legacy_fw_header *hdr;
	u32 size;
	पूर्णांक err;

	अगर (!name)
		वापस 0;

	snम_लिखो(path, ARRAY_SIZE(path),
		 "b43legacy%s/%s.fw",
		 modparam_fwpostfix, name);
	b43legacyinfo(dev->wl, "Loading firmware %s\n", path);
	अगर (async) अणु
		init_completion(&dev->fw_load_complete);
		err = request_firmware_noरुको(THIS_MODULE, 1, path,
					      dev->dev->dev, GFP_KERNEL,
					      dev, b43legacy_fw_cb);
		अगर (err) अणु
			b43legacyerr(dev->wl, "Unable to load firmware\n");
			वापस err;
		पूर्ण
		/* stall here until fw पढ़ोy */
		रुको_क्रम_completion(&dev->fw_load_complete);
		अगर (!dev->fwp)
			err = -EINVAL;
		*fw = dev->fwp;
	पूर्ण अन्यथा अणु
		err = request_firmware(fw, path, dev->dev->dev);
	पूर्ण
	अगर (err) अणु
		b43legacyerr(dev->wl, "Firmware file \"%s\" not found "
		       "or load failed.\n", path);
		वापस err;
	पूर्ण
	अगर ((*fw)->size < माप(काष्ठा b43legacy_fw_header))
		जाओ err_क्रमmat;
	hdr = (काष्ठा b43legacy_fw_header *)((*fw)->data);
	चयन (hdr->type) अणु
	हाल B43legacy_FW_TYPE_UCODE:
	हाल B43legacy_FW_TYPE_PCM:
		size = be32_to_cpu(hdr->size);
		अगर (size != (*fw)->size - माप(काष्ठा b43legacy_fw_header))
			जाओ err_क्रमmat;
		fallthrough;
	हाल B43legacy_FW_TYPE_IV:
		अगर (hdr->ver != 1)
			जाओ err_क्रमmat;
		अवरोध;
	शेष:
		जाओ err_क्रमmat;
	पूर्ण

	वापस err;

err_क्रमmat:
	b43legacyerr(dev->wl, "Firmware file \"%s\" format error.\n", path);
	वापस -EPROTO;
पूर्ण

अटल पूर्णांक b43legacy_one_core_attach(काष्ठा ssb_device *dev,
				     काष्ठा b43legacy_wl *wl);
अटल व्योम b43legacy_one_core_detach(काष्ठा ssb_device *dev);

अटल व्योम b43legacy_request_firmware(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा b43legacy_wl *wl = container_of(work,
				  काष्ठा b43legacy_wl, firmware_load);
	काष्ठा b43legacy_wldev *dev = wl->current_dev;
	काष्ठा b43legacy_firmware *fw = &dev->fw;
	स्थिर u8 rev = dev->dev->id.revision;
	स्थिर अक्षर *filename;
	पूर्णांक err;

	अगर (!fw->ucode) अणु
		अगर (rev == 2)
			filename = "ucode2";
		अन्यथा अगर (rev == 4)
			filename = "ucode4";
		अन्यथा
			filename = "ucode5";
		err = करो_request_fw(dev, filename, &fw->ucode, true);
		अगर (err)
			जाओ err_load;
	पूर्ण
	अगर (!fw->pcm) अणु
		अगर (rev < 5)
			filename = "pcm4";
		अन्यथा
			filename = "pcm5";
		err = करो_request_fw(dev, filename, &fw->pcm, false);
		अगर (err)
			जाओ err_load;
	पूर्ण
	अगर (!fw->initvals) अणु
		चयन (dev->phy.type) अणु
		हाल B43legacy_PHYTYPE_B:
		हाल B43legacy_PHYTYPE_G:
			अगर ((rev >= 5) && (rev <= 10))
				filename = "b0g0initvals5";
			अन्यथा अगर (rev == 2 || rev == 4)
				filename = "b0g0initvals2";
			अन्यथा
				जाओ err_no_initvals;
			अवरोध;
		शेष:
			जाओ err_no_initvals;
		पूर्ण
		err = करो_request_fw(dev, filename, &fw->initvals, false);
		अगर (err)
			जाओ err_load;
	पूर्ण
	अगर (!fw->initvals_band) अणु
		चयन (dev->phy.type) अणु
		हाल B43legacy_PHYTYPE_B:
		हाल B43legacy_PHYTYPE_G:
			अगर ((rev >= 5) && (rev <= 10))
				filename = "b0g0bsinitvals5";
			अन्यथा अगर (rev >= 11)
				filename = शून्य;
			अन्यथा अगर (rev == 2 || rev == 4)
				filename = शून्य;
			अन्यथा
				जाओ err_no_initvals;
			अवरोध;
		शेष:
			जाओ err_no_initvals;
		पूर्ण
		err = करो_request_fw(dev, filename, &fw->initvals_band, false);
		अगर (err)
			जाओ err_load;
	पूर्ण
	err = ieee80211_रेजिस्टर_hw(wl->hw);
	अगर (err)
		जाओ err_one_core_detach;
	वापस;

err_one_core_detach:
	b43legacy_one_core_detach(dev->dev);
	जाओ error;

err_load:
	b43legacy_prपूर्णांक_fw_helptext(dev->wl);
	जाओ error;

err_no_initvals:
	err = -ENODEV;
	b43legacyerr(dev->wl, "No Initial Values firmware file for PHY %u, "
	       "core rev %u\n", dev->phy.type, rev);
	जाओ error;

error:
	b43legacy_release_firmware(dev);
	वापस;
पूर्ण

अटल पूर्णांक b43legacy_upload_microcode(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा wiphy *wiphy = dev->wl->hw->wiphy;
	स्थिर माप_प्रकार hdr_len = माप(काष्ठा b43legacy_fw_header);
	स्थिर __be32 *data;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक len;
	u16 fwrev;
	u16 fwpatch;
	u16 fwdate;
	u16 fwसमय;
	u32 पंचांगp, macctl;
	पूर्णांक err = 0;

	/* Jump the microcode PSM to offset 0 */
	macctl = b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCTL);
	B43legacy_WARN_ON(macctl & B43legacy_MACCTL_PSM_RUN);
	macctl |= B43legacy_MACCTL_PSM_JMP0;
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_MACCTL, macctl);
	/* Zero out all microcode PSM रेजिस्टरs and shared memory. */
	क्रम (i = 0; i < 64; i++)
		b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_WIRELESS, i, 0);
	क्रम (i = 0; i < 4096; i += 2)
		b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED, i, 0);

	/* Upload Microcode. */
	data = (__be32 *) (dev->fw.ucode->data + hdr_len);
	len = (dev->fw.ucode->size - hdr_len) / माप(__be32);
	b43legacy_shm_control_word(dev,
				   B43legacy_SHM_UCODE |
				   B43legacy_SHM_AUTOINC_W,
				   0x0000);
	क्रम (i = 0; i < len; i++) अणु
		b43legacy_ग_लिखो32(dev, B43legacy_MMIO_SHM_DATA,
				    be32_to_cpu(data[i]));
		udelay(10);
	पूर्ण

	अगर (dev->fw.pcm) अणु
		/* Upload PCM data. */
		data = (__be32 *) (dev->fw.pcm->data + hdr_len);
		len = (dev->fw.pcm->size - hdr_len) / माप(__be32);
		b43legacy_shm_control_word(dev, B43legacy_SHM_HW, 0x01EA);
		b43legacy_ग_लिखो32(dev, B43legacy_MMIO_SHM_DATA, 0x00004000);
		/* No need क्रम स्वतःinc bit in SHM_HW */
		b43legacy_shm_control_word(dev, B43legacy_SHM_HW, 0x01EB);
		क्रम (i = 0; i < len; i++) अणु
			b43legacy_ग_लिखो32(dev, B43legacy_MMIO_SHM_DATA,
					  be32_to_cpu(data[i]));
			udelay(10);
		पूर्ण
	पूर्ण

	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_GEN_IRQ_REASON,
			  B43legacy_IRQ_ALL);

	/* Start the microcode PSM */
	macctl = b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCTL);
	macctl &= ~B43legacy_MACCTL_PSM_JMP0;
	macctl |= B43legacy_MACCTL_PSM_RUN;
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_MACCTL, macctl);

	/* Wait क्रम the microcode to load and respond */
	i = 0;
	जबतक (1) अणु
		पंचांगp = b43legacy_पढ़ो32(dev, B43legacy_MMIO_GEN_IRQ_REASON);
		अगर (पंचांगp == B43legacy_IRQ_MAC_SUSPENDED)
			अवरोध;
		i++;
		अगर (i >= B43legacy_IRQWAIT_MAX_RETRIES) अणु
			b43legacyerr(dev->wl, "Microcode not responding\n");
			b43legacy_prपूर्णांक_fw_helptext(dev->wl);
			err = -ENODEV;
			जाओ error;
		पूर्ण
		msleep_पूर्णांकerruptible(50);
		अगर (संकेत_pending(current)) अणु
			err = -EINTR;
			जाओ error;
		पूर्ण
	पूर्ण
	/* dummy पढ़ो follows */
	b43legacy_पढ़ो32(dev, B43legacy_MMIO_GEN_IRQ_REASON);

	/* Get and check the revisions. */
	fwrev = b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_SHARED,
				     B43legacy_SHM_SH_UCODEREV);
	fwpatch = b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_SHARED,
				       B43legacy_SHM_SH_UCODEPATCH);
	fwdate = b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_SHARED,
				      B43legacy_SHM_SH_UCODEDATE);
	fwसमय = b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_SHARED,
				      B43legacy_SHM_SH_UCODETIME);

	अगर (fwrev > 0x128) अणु
		b43legacyerr(dev->wl, "YOU ARE TRYING TO LOAD V4 FIRMWARE."
			     " Only firmware from binary drivers version 3.x"
			     " is supported. You must change your firmware"
			     " files.\n");
		b43legacy_prपूर्णांक_fw_helptext(dev->wl);
		err = -EOPNOTSUPP;
		जाओ error;
	पूर्ण
	b43legacyinfo(dev->wl, "Loading firmware version 0x%X, patch level %u "
		      "(20%.2i-%.2i-%.2i %.2i:%.2i:%.2i)\n", fwrev, fwpatch,
		      (fwdate >> 12) & 0xF, (fwdate >> 8) & 0xF, fwdate & 0xFF,
		      (fwसमय >> 11) & 0x1F, (fwसमय >> 5) & 0x3F,
		      fwसमय & 0x1F);

	dev->fw.rev = fwrev;
	dev->fw.patch = fwpatch;

	snम_लिखो(wiphy->fw_version, माप(wiphy->fw_version), "%u.%u",
			dev->fw.rev, dev->fw.patch);
	wiphy->hw_version = dev->dev->id.coreid;

	वापस 0;

error:
	macctl = b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCTL);
	macctl &= ~B43legacy_MACCTL_PSM_RUN;
	macctl |= B43legacy_MACCTL_PSM_JMP0;
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_MACCTL, macctl);

	वापस err;
पूर्ण

अटल पूर्णांक b43legacy_ग_लिखो_initvals(काष्ठा b43legacy_wldev *dev,
				    स्थिर काष्ठा b43legacy_iv *ivals,
				    माप_प्रकार count,
				    माप_प्रकार array_size)
अणु
	स्थिर काष्ठा b43legacy_iv *iv;
	u16 offset;
	माप_प्रकार i;
	bool bit32;

	BUILD_BUG_ON(माप(काष्ठा b43legacy_iv) != 6);
	iv = ivals;
	क्रम (i = 0; i < count; i++) अणु
		अगर (array_size < माप(iv->offset_size))
			जाओ err_क्रमmat;
		array_size -= माप(iv->offset_size);
		offset = be16_to_cpu(iv->offset_size);
		bit32 = !!(offset & B43legacy_IV_32BIT);
		offset &= B43legacy_IV_OFFSET_MASK;
		अगर (offset >= 0x1000)
			जाओ err_क्रमmat;
		अगर (bit32) अणु
			u32 value;

			अगर (array_size < माप(iv->data.d32))
				जाओ err_क्रमmat;
			array_size -= माप(iv->data.d32);

			value = get_unaligned_be32(&iv->data.d32);
			b43legacy_ग_लिखो32(dev, offset, value);

			iv = (स्थिर काष्ठा b43legacy_iv *)((स्थिर uपूर्णांक8_t *)iv +
							माप(__be16) +
							माप(__be32));
		पूर्ण अन्यथा अणु
			u16 value;

			अगर (array_size < माप(iv->data.d16))
				जाओ err_क्रमmat;
			array_size -= माप(iv->data.d16);

			value = be16_to_cpu(iv->data.d16);
			b43legacy_ग_लिखो16(dev, offset, value);

			iv = (स्थिर काष्ठा b43legacy_iv *)((स्थिर uपूर्णांक8_t *)iv +
							माप(__be16) +
							माप(__be16));
		पूर्ण
	पूर्ण
	अगर (array_size)
		जाओ err_क्रमmat;

	वापस 0;

err_क्रमmat:
	b43legacyerr(dev->wl, "Initial Values Firmware file-format error.\n");
	b43legacy_prपूर्णांक_fw_helptext(dev->wl);

	वापस -EPROTO;
पूर्ण

अटल पूर्णांक b43legacy_upload_initvals(काष्ठा b43legacy_wldev *dev)
अणु
	स्थिर माप_प्रकार hdr_len = माप(काष्ठा b43legacy_fw_header);
	स्थिर काष्ठा b43legacy_fw_header *hdr;
	काष्ठा b43legacy_firmware *fw = &dev->fw;
	स्थिर काष्ठा b43legacy_iv *ivals;
	माप_प्रकार count;
	पूर्णांक err;

	hdr = (स्थिर काष्ठा b43legacy_fw_header *)(fw->initvals->data);
	ivals = (स्थिर काष्ठा b43legacy_iv *)(fw->initvals->data + hdr_len);
	count = be32_to_cpu(hdr->size);
	err = b43legacy_ग_लिखो_initvals(dev, ivals, count,
				 fw->initvals->size - hdr_len);
	अगर (err)
		जाओ out;
	अगर (fw->initvals_band) अणु
		hdr = (स्थिर काष्ठा b43legacy_fw_header *)
		      (fw->initvals_band->data);
		ivals = (स्थिर काष्ठा b43legacy_iv *)(fw->initvals_band->data
			+ hdr_len);
		count = be32_to_cpu(hdr->size);
		err = b43legacy_ग_लिखो_initvals(dev, ivals, count,
					 fw->initvals_band->size - hdr_len);
		अगर (err)
			जाओ out;
	पूर्ण
out:

	वापस err;
पूर्ण

/* Initialize the GPIOs
 * https://bcm-specs.sipsolutions.net/GPIO
 */
अटल पूर्णांक b43legacy_gpio_init(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा ssb_bus *bus = dev->dev->bus;
	काष्ठा ssb_device *gpiodev, *pcidev = शून्य;
	u32 mask;
	u32 set;

	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_MACCTL,
			  b43legacy_पढ़ो32(dev,
			  B43legacy_MMIO_MACCTL)
			  & 0xFFFF3FFF);

	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_GPIO_MASK,
			  b43legacy_पढ़ो16(dev,
			  B43legacy_MMIO_GPIO_MASK)
			  | 0x000F);

	mask = 0x0000001F;
	set = 0x0000000F;
	अगर (dev->dev->bus->chip_id == 0x4301) अणु
		mask |= 0x0060;
		set |= 0x0060;
	पूर्ण
	अगर (dev->dev->bus->sprom.boardflags_lo & B43legacy_BFL_PACTRL) अणु
		b43legacy_ग_लिखो16(dev, B43legacy_MMIO_GPIO_MASK,
				  b43legacy_पढ़ो16(dev,
				  B43legacy_MMIO_GPIO_MASK)
				  | 0x0200);
		mask |= 0x0200;
		set |= 0x0200;
	पूर्ण
	अगर (dev->dev->id.revision >= 2)
		mask  |= 0x0010; /* FIXME: This is redundant. */

#अगर_घोषित CONFIG_SSB_DRIVER_PCICORE
	pcidev = bus->pcicore.dev;
#पूर्ण_अगर
	gpiodev = bus->chipco.dev ? : pcidev;
	अगर (!gpiodev)
		वापस 0;
	ssb_ग_लिखो32(gpiodev, B43legacy_GPIO_CONTROL,
		    (ssb_पढ़ो32(gpiodev, B43legacy_GPIO_CONTROL)
		     & ~mask) | set);

	वापस 0;
पूर्ण

/* Turn off all GPIO stuff. Call this on module unload, क्रम example. */
अटल व्योम b43legacy_gpio_cleanup(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा ssb_bus *bus = dev->dev->bus;
	काष्ठा ssb_device *gpiodev, *pcidev = शून्य;

#अगर_घोषित CONFIG_SSB_DRIVER_PCICORE
	pcidev = bus->pcicore.dev;
#पूर्ण_अगर
	gpiodev = bus->chipco.dev ? : pcidev;
	अगर (!gpiodev)
		वापस;
	ssb_ग_लिखो32(gpiodev, B43legacy_GPIO_CONTROL, 0);
पूर्ण

/* http://bcm-specs.sipsolutions.net/EnableMac */
व्योम b43legacy_mac_enable(काष्ठा b43legacy_wldev *dev)
अणु
	dev->mac_suspended--;
	B43legacy_WARN_ON(dev->mac_suspended < 0);
	B43legacy_WARN_ON(irqs_disabled());
	अगर (dev->mac_suspended == 0) अणु
		b43legacy_ग_लिखो32(dev, B43legacy_MMIO_MACCTL,
				  b43legacy_पढ़ो32(dev,
				  B43legacy_MMIO_MACCTL)
				  | B43legacy_MACCTL_ENABLED);
		b43legacy_ग_लिखो32(dev, B43legacy_MMIO_GEN_IRQ_REASON,
				  B43legacy_IRQ_MAC_SUSPENDED);
		/* the next two are dummy पढ़ोs */
		b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCTL);
		b43legacy_पढ़ो32(dev, B43legacy_MMIO_GEN_IRQ_REASON);
		b43legacy_घातer_saving_ctl_bits(dev, -1, -1);

		/* Re-enable IRQs. */
		spin_lock_irq(&dev->wl->irq_lock);
		b43legacy_ग_लिखो32(dev, B43legacy_MMIO_GEN_IRQ_MASK,
				  dev->irq_mask);
		spin_unlock_irq(&dev->wl->irq_lock);
	पूर्ण
पूर्ण

/* https://bcm-specs.sipsolutions.net/SuspendMAC */
व्योम b43legacy_mac_suspend(काष्ठा b43legacy_wldev *dev)
अणु
	पूर्णांक i;
	u32 पंचांगp;

	might_sleep();
	B43legacy_WARN_ON(irqs_disabled());
	B43legacy_WARN_ON(dev->mac_suspended < 0);

	अगर (dev->mac_suspended == 0) अणु
		/* Mask IRQs beक्रमe suspending MAC. Otherwise
		 * the MAC stays busy and won't suspend. */
		spin_lock_irq(&dev->wl->irq_lock);
		b43legacy_ग_लिखो32(dev, B43legacy_MMIO_GEN_IRQ_MASK, 0);
		spin_unlock_irq(&dev->wl->irq_lock);
		b43legacy_synchronize_irq(dev);

		b43legacy_घातer_saving_ctl_bits(dev, -1, 1);
		b43legacy_ग_लिखो32(dev, B43legacy_MMIO_MACCTL,
				  b43legacy_पढ़ो32(dev,
				  B43legacy_MMIO_MACCTL)
				  & ~B43legacy_MACCTL_ENABLED);
		b43legacy_पढ़ो32(dev, B43legacy_MMIO_GEN_IRQ_REASON);
		क्रम (i = 40; i; i--) अणु
			पंचांगp = b43legacy_पढ़ो32(dev,
					       B43legacy_MMIO_GEN_IRQ_REASON);
			अगर (पंचांगp & B43legacy_IRQ_MAC_SUSPENDED)
				जाओ out;
			msleep(1);
		पूर्ण
		b43legacyerr(dev->wl, "MAC suspend failed\n");
	पूर्ण
out:
	dev->mac_suspended++;
पूर्ण

अटल व्योम b43legacy_adjust_opmode(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_wl *wl = dev->wl;
	u32 ctl;
	u16 cfp_pretbtt;

	ctl = b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCTL);
	/* Reset status to STA infraकाष्ठाure mode. */
	ctl &= ~B43legacy_MACCTL_AP;
	ctl &= ~B43legacy_MACCTL_KEEP_CTL;
	ctl &= ~B43legacy_MACCTL_KEEP_BADPLCP;
	ctl &= ~B43legacy_MACCTL_KEEP_BAD;
	ctl &= ~B43legacy_MACCTL_PROMISC;
	ctl &= ~B43legacy_MACCTL_BEACPROMISC;
	ctl |= B43legacy_MACCTL_INFRA;

	अगर (b43legacy_is_mode(wl, NL80211_IFTYPE_AP))
		ctl |= B43legacy_MACCTL_AP;
	अन्यथा अगर (b43legacy_is_mode(wl, NL80211_IFTYPE_ADHOC))
		ctl &= ~B43legacy_MACCTL_INFRA;

	अगर (wl->filter_flags & FIF_CONTROL)
		ctl |= B43legacy_MACCTL_KEEP_CTL;
	अगर (wl->filter_flags & FIF_FCSFAIL)
		ctl |= B43legacy_MACCTL_KEEP_BAD;
	अगर (wl->filter_flags & FIF_PLCPFAIL)
		ctl |= B43legacy_MACCTL_KEEP_BADPLCP;
	अगर (wl->filter_flags & FIF_BCN_PRBRESP_PROMISC)
		ctl |= B43legacy_MACCTL_BEACPROMISC;

	/* Workaround: On old hardware the HW-MAC-address-filter
	 * करोesn't work properly, so always run promisc in filter
	 * it in software. */
	अगर (dev->dev->id.revision <= 4)
		ctl |= B43legacy_MACCTL_PROMISC;

	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_MACCTL, ctl);

	cfp_pretbtt = 2;
	अगर ((ctl & B43legacy_MACCTL_INFRA) &&
	    !(ctl & B43legacy_MACCTL_AP)) अणु
		अगर (dev->dev->bus->chip_id == 0x4306 &&
		    dev->dev->bus->chip_rev == 3)
			cfp_pretbtt = 100;
		अन्यथा
			cfp_pretbtt = 50;
	पूर्ण
	b43legacy_ग_लिखो16(dev, 0x612, cfp_pretbtt);
पूर्ण

अटल व्योम b43legacy_rate_memory_ग_लिखो(काष्ठा b43legacy_wldev *dev,
					u16 rate,
					पूर्णांक is_ofdm)
अणु
	u16 offset;

	अगर (is_ofdm) अणु
		offset = 0x480;
		offset += (b43legacy_plcp_get_ratecode_ofdm(rate) & 0x000F) * 2;
	पूर्ण अन्यथा अणु
		offset = 0x4C0;
		offset += (b43legacy_plcp_get_ratecode_cck(rate) & 0x000F) * 2;
	पूर्ण
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED, offset + 0x20,
			      b43legacy_shm_पढ़ो16(dev,
			      B43legacy_SHM_SHARED, offset));
पूर्ण

अटल व्योम b43legacy_rate_memory_init(काष्ठा b43legacy_wldev *dev)
अणु
	चयन (dev->phy.type) अणु
	हाल B43legacy_PHYTYPE_G:
		b43legacy_rate_memory_ग_लिखो(dev, B43legacy_OFDM_RATE_6MB, 1);
		b43legacy_rate_memory_ग_लिखो(dev, B43legacy_OFDM_RATE_12MB, 1);
		b43legacy_rate_memory_ग_लिखो(dev, B43legacy_OFDM_RATE_18MB, 1);
		b43legacy_rate_memory_ग_लिखो(dev, B43legacy_OFDM_RATE_24MB, 1);
		b43legacy_rate_memory_ग_लिखो(dev, B43legacy_OFDM_RATE_36MB, 1);
		b43legacy_rate_memory_ग_लिखो(dev, B43legacy_OFDM_RATE_48MB, 1);
		b43legacy_rate_memory_ग_लिखो(dev, B43legacy_OFDM_RATE_54MB, 1);
		fallthrough;
	हाल B43legacy_PHYTYPE_B:
		b43legacy_rate_memory_ग_लिखो(dev, B43legacy_CCK_RATE_1MB, 0);
		b43legacy_rate_memory_ग_लिखो(dev, B43legacy_CCK_RATE_2MB, 0);
		b43legacy_rate_memory_ग_लिखो(dev, B43legacy_CCK_RATE_5MB, 0);
		b43legacy_rate_memory_ग_लिखो(dev, B43legacy_CCK_RATE_11MB, 0);
		अवरोध;
	शेष:
		B43legacy_BUG_ON(1);
	पूर्ण
पूर्ण

/* Set the TX-Antenna क्रम management frames sent by firmware. */
अटल व्योम b43legacy_mgmtframe_txantenna(काष्ठा b43legacy_wldev *dev,
					  पूर्णांक antenna)
अणु
	u16 ant = 0;
	u16 पंचांगp;

	चयन (antenna) अणु
	हाल B43legacy_ANTENNA0:
		ant |= B43legacy_TX4_PHY_ANT0;
		अवरोध;
	हाल B43legacy_ANTENNA1:
		ant |= B43legacy_TX4_PHY_ANT1;
		अवरोध;
	हाल B43legacy_ANTENNA_AUTO:
		ant |= B43legacy_TX4_PHY_ANTLAST;
		अवरोध;
	शेष:
		B43legacy_BUG_ON(1);
	पूर्ण

	/* FIXME We also need to set the other flags of the PHY control
	 * field somewhere. */

	/* For Beacons */
	पंचांगp = b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_SHARED,
				   B43legacy_SHM_SH_BEACPHYCTL);
	पंचांगp = (पंचांगp & ~B43legacy_TX4_PHY_ANT) | ant;
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED,
			      B43legacy_SHM_SH_BEACPHYCTL, पंचांगp);
	/* For ACK/CTS */
	पंचांगp = b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_SHARED,
				   B43legacy_SHM_SH_ACKCTSPHYCTL);
	पंचांगp = (पंचांगp & ~B43legacy_TX4_PHY_ANT) | ant;
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED,
			      B43legacy_SHM_SH_ACKCTSPHYCTL, पंचांगp);
	/* For Probe Resposes */
	पंचांगp = b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_SHARED,
				   B43legacy_SHM_SH_PRPHYCTL);
	पंचांगp = (पंचांगp & ~B43legacy_TX4_PHY_ANT) | ant;
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED,
			      B43legacy_SHM_SH_PRPHYCTL, पंचांगp);
पूर्ण

/* This is the opposite of b43legacy_chip_init() */
अटल व्योम b43legacy_chip_निकास(काष्ठा b43legacy_wldev *dev)
अणु
	b43legacy_radio_turn_off(dev, 1);
	b43legacy_gpio_cleanup(dev);
	/* firmware is released later */
पूर्ण

/* Initialize the chip
 * https://bcm-specs.sipsolutions.net/ChipInit
 */
अटल पूर्णांक b43legacy_chip_init(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	पूर्णांक err;
	पूर्णांक पंचांगp;
	u32 value32, macctl;
	u16 value16;

	/* Initialize the MAC control */
	macctl = B43legacy_MACCTL_IHR_ENABLED | B43legacy_MACCTL_SHM_ENABLED;
	अगर (dev->phy.gmode)
		macctl |= B43legacy_MACCTL_GMODE;
	macctl |= B43legacy_MACCTL_INFRA;
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_MACCTL, macctl);

	err = b43legacy_upload_microcode(dev);
	अगर (err)
		जाओ out; /* firmware is released later */

	err = b43legacy_gpio_init(dev);
	अगर (err)
		जाओ out; /* firmware is released later */

	err = b43legacy_upload_initvals(dev);
	अगर (err)
		जाओ err_gpio_clean;
	b43legacy_radio_turn_on(dev);

	b43legacy_ग_लिखो16(dev, 0x03E6, 0x0000);
	err = b43legacy_phy_init(dev);
	अगर (err)
		जाओ err_radio_off;

	/* Select initial Interference Mitigation. */
	पंचांगp = phy->पूर्णांकerभ_शेषe;
	phy->पूर्णांकerभ_शेषe = B43legacy_INTERFMODE_NONE;
	b43legacy_radio_set_पूर्णांकerference_mitigation(dev, पंचांगp);

	b43legacy_phy_set_antenna_भागersity(dev);
	b43legacy_mgmtframe_txantenna(dev, B43legacy_ANTENNA_DEFAULT);

	अगर (phy->type == B43legacy_PHYTYPE_B) अणु
		value16 = b43legacy_पढ़ो16(dev, 0x005E);
		value16 |= 0x0004;
		b43legacy_ग_लिखो16(dev, 0x005E, value16);
	पूर्ण
	b43legacy_ग_लिखो32(dev, 0x0100, 0x01000000);
	अगर (dev->dev->id.revision < 5)
		b43legacy_ग_लिखो32(dev, 0x010C, 0x01000000);

	value32 = b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCTL);
	value32 &= ~B43legacy_MACCTL_INFRA;
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_MACCTL, value32);
	value32 = b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCTL);
	value32 |= B43legacy_MACCTL_INFRA;
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_MACCTL, value32);

	अगर (b43legacy_using_pio(dev)) अणु
		b43legacy_ग_लिखो32(dev, 0x0210, 0x00000100);
		b43legacy_ग_लिखो32(dev, 0x0230, 0x00000100);
		b43legacy_ग_लिखो32(dev, 0x0250, 0x00000100);
		b43legacy_ग_लिखो32(dev, 0x0270, 0x00000100);
		b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED, 0x0034,
				      0x0000);
	पूर्ण

	/* Probe Response Timeout value */
	/* FIXME: Default to 0, has to be set by ioctl probably... :-/ */
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED, 0x0074, 0x0000);

	/* Initially set the wireless operation mode. */
	b43legacy_adjust_opmode(dev);

	अगर (dev->dev->id.revision < 3) अणु
		b43legacy_ग_लिखो16(dev, 0x060E, 0x0000);
		b43legacy_ग_लिखो16(dev, 0x0610, 0x8000);
		b43legacy_ग_लिखो16(dev, 0x0604, 0x0000);
		b43legacy_ग_लिखो16(dev, 0x0606, 0x0200);
	पूर्ण अन्यथा अणु
		b43legacy_ग_लिखो32(dev, 0x0188, 0x80000000);
		b43legacy_ग_लिखो32(dev, 0x018C, 0x02000000);
	पूर्ण
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_GEN_IRQ_REASON, 0x00004000);
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_DMA0_IRQ_MASK, 0x0001DC00);
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_DMA1_IRQ_MASK, 0x0000DC00);
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_DMA2_IRQ_MASK, 0x0000DC00);
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_DMA3_IRQ_MASK, 0x0001DC00);
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_DMA4_IRQ_MASK, 0x0000DC00);
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_DMA5_IRQ_MASK, 0x0000DC00);

	value32 = ssb_पढ़ो32(dev->dev, SSB_TMSLOW);
	value32 |= B43legacy_TMSLOW_MACPHYCLKEN;
	ssb_ग_लिखो32(dev->dev, SSB_TMSLOW, value32);

	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_POWERUP_DELAY,
			  dev->dev->bus->chipco.fast_pwrup_delay);

	/* PHY TX errors counter. */
	atomic_set(&phy->txerr_cnt, B43legacy_PHY_TX_BADNESS_LIMIT);

	B43legacy_WARN_ON(err != 0);
	b43legacydbg(dev->wl, "Chip initialized\n");
out:
	वापस err;

err_radio_off:
	b43legacy_radio_turn_off(dev, 1);
err_gpio_clean:
	b43legacy_gpio_cleanup(dev);
	जाओ out;
पूर्ण

अटल व्योम b43legacy_periodic_every120sec(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;

	अगर (phy->type != B43legacy_PHYTYPE_G || phy->rev < 2)
		वापस;

	b43legacy_mac_suspend(dev);
	b43legacy_phy_lo_g_measure(dev);
	b43legacy_mac_enable(dev);
पूर्ण

अटल व्योम b43legacy_periodic_every60sec(काष्ठा b43legacy_wldev *dev)
अणु
	b43legacy_phy_lo_mark_all_unused(dev);
	अगर (dev->dev->bus->sprom.boardflags_lo & B43legacy_BFL_RSSI) अणु
		b43legacy_mac_suspend(dev);
		b43legacy_calc_nrssi_slope(dev);
		b43legacy_mac_enable(dev);
	पूर्ण
पूर्ण

अटल व्योम b43legacy_periodic_every30sec(काष्ठा b43legacy_wldev *dev)
अणु
	/* Update device statistics. */
	b43legacy_calculate_link_quality(dev);
पूर्ण

अटल व्योम b43legacy_periodic_every15sec(काष्ठा b43legacy_wldev *dev)
अणु
	b43legacy_phy_xmitघातer(dev); /* FIXME: unless scanning? */

	atomic_set(&dev->phy.txerr_cnt, B43legacy_PHY_TX_BADNESS_LIMIT);
	wmb();
पूर्ण

अटल व्योम करो_periodic_work(काष्ठा b43legacy_wldev *dev)
अणु
	अचिन्हित पूर्णांक state;

	state = dev->periodic_state;
	अगर (state % 8 == 0)
		b43legacy_periodic_every120sec(dev);
	अगर (state % 4 == 0)
		b43legacy_periodic_every60sec(dev);
	अगर (state % 2 == 0)
		b43legacy_periodic_every30sec(dev);
	b43legacy_periodic_every15sec(dev);
पूर्ण

/* Periodic work locking policy:
 * 	The whole periodic work handler is रक्षित by
 * 	wl->mutex. If another lock is needed somewhere in the
 * 	pwork callchain, it's acquired in-place, where it's needed.
 */
अटल व्योम b43legacy_periodic_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा b43legacy_wldev *dev = container_of(work, काष्ठा b43legacy_wldev,
					     periodic_work.work);
	काष्ठा b43legacy_wl *wl = dev->wl;
	अचिन्हित दीर्घ delay;

	mutex_lock(&wl->mutex);

	अगर (unlikely(b43legacy_status(dev) != B43legacy_STAT_STARTED))
		जाओ out;
	अगर (b43legacy_debug(dev, B43legacy_DBG_PWORK_STOP))
		जाओ out_requeue;

	करो_periodic_work(dev);

	dev->periodic_state++;
out_requeue:
	अगर (b43legacy_debug(dev, B43legacy_DBG_PWORK_FAST))
		delay = msecs_to_jअगरfies(50);
	अन्यथा
		delay = round_jअगरfies_relative(HZ * 15);
	ieee80211_queue_delayed_work(wl->hw, &dev->periodic_work, delay);
out:
	mutex_unlock(&wl->mutex);
पूर्ण

अटल व्योम b43legacy_periodic_tasks_setup(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा delayed_work *work = &dev->periodic_work;

	dev->periodic_state = 0;
	INIT_DELAYED_WORK(work, b43legacy_periodic_work_handler);
	ieee80211_queue_delayed_work(dev->wl->hw, work, 0);
पूर्ण

/* Validate access to the chip (SHM) */
अटल पूर्णांक b43legacy_validate_chipaccess(काष्ठा b43legacy_wldev *dev)
अणु
	u32 value;
	u32 shm_backup;

	shm_backup = b43legacy_shm_पढ़ो32(dev, B43legacy_SHM_SHARED, 0);
	b43legacy_shm_ग_लिखो32(dev, B43legacy_SHM_SHARED, 0, 0xAA5555AA);
	अगर (b43legacy_shm_पढ़ो32(dev, B43legacy_SHM_SHARED, 0) !=
				 0xAA5555AA)
		जाओ error;
	b43legacy_shm_ग_लिखो32(dev, B43legacy_SHM_SHARED, 0, 0x55AAAA55);
	अगर (b43legacy_shm_पढ़ो32(dev, B43legacy_SHM_SHARED, 0) !=
				 0x55AAAA55)
		जाओ error;
	b43legacy_shm_ग_लिखो32(dev, B43legacy_SHM_SHARED, 0, shm_backup);

	value = b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCTL);
	अगर ((value | B43legacy_MACCTL_GMODE) !=
	    (B43legacy_MACCTL_GMODE | B43legacy_MACCTL_IHR_ENABLED))
		जाओ error;

	value = b43legacy_पढ़ो32(dev, B43legacy_MMIO_GEN_IRQ_REASON);
	अगर (value)
		जाओ error;

	वापस 0;
error:
	b43legacyerr(dev->wl, "Failed to validate the chipaccess\n");
	वापस -ENODEV;
पूर्ण

अटल व्योम b43legacy_security_init(काष्ठा b43legacy_wldev *dev)
अणु
	dev->max_nr_keys = (dev->dev->id.revision >= 5) ? 58 : 20;
	B43legacy_WARN_ON(dev->max_nr_keys > ARRAY_SIZE(dev->key));
	dev->ktp = b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_SHARED,
					0x0056);
	/* KTP is a word address, but we address SHM bytewise.
	 * So multiply by two.
	 */
	dev->ktp *= 2;
	अगर (dev->dev->id.revision >= 5)
		/* Number of RCMTA address slots */
		b43legacy_ग_लिखो16(dev, B43legacy_MMIO_RCMTA_COUNT,
				  dev->max_nr_keys - 8);
पूर्ण

#अगर_घोषित CONFIG_B43LEGACY_HWRNG
अटल पूर्णांक b43legacy_rng_पढ़ो(काष्ठा hwrng *rng, u32 *data)
अणु
	काष्ठा b43legacy_wl *wl = (काष्ठा b43legacy_wl *)rng->priv;
	अचिन्हित दीर्घ flags;

	/* Don't take wl->mutex here, as it could deadlock with
	 * hwrng पूर्णांकernal locking. It's not needed to take
	 * wl->mutex here, anyway. */

	spin_lock_irqsave(&wl->irq_lock, flags);
	*data = b43legacy_पढ़ो16(wl->current_dev, B43legacy_MMIO_RNG);
	spin_unlock_irqrestore(&wl->irq_lock, flags);

	वापस (माप(u16));
पूर्ण
#पूर्ण_अगर

अटल व्योम b43legacy_rng_निकास(काष्ठा b43legacy_wl *wl)
अणु
#अगर_घोषित CONFIG_B43LEGACY_HWRNG
	अगर (wl->rng_initialized)
		hwrng_unरेजिस्टर(&wl->rng);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक b43legacy_rng_init(काष्ठा b43legacy_wl *wl)
अणु
	पूर्णांक err = 0;

#अगर_घोषित CONFIG_B43LEGACY_HWRNG
	snम_लिखो(wl->rng_name, ARRAY_SIZE(wl->rng_name),
		 "%s_%s", KBUILD_MODNAME, wiphy_name(wl->hw->wiphy));
	wl->rng.name = wl->rng_name;
	wl->rng.data_पढ़ो = b43legacy_rng_पढ़ो;
	wl->rng.priv = (अचिन्हित दीर्घ)wl;
	wl->rng_initialized = 1;
	err = hwrng_रेजिस्टर(&wl->rng);
	अगर (err) अणु
		wl->rng_initialized = 0;
		b43legacyerr(wl, "Failed to register the random "
		       "number generator (%d)\n", err);
	पूर्ण

#पूर्ण_अगर
	वापस err;
पूर्ण

अटल व्योम b43legacy_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा b43legacy_wl *wl = container_of(work, काष्ठा b43legacy_wl,
				  tx_work);
	काष्ठा b43legacy_wldev *dev;
	काष्ठा sk_buff *skb;
	पूर्णांक queue_num;
	पूर्णांक err = 0;

	mutex_lock(&wl->mutex);
	dev = wl->current_dev;
	अगर (unlikely(!dev || b43legacy_status(dev) < B43legacy_STAT_STARTED)) अणु
		mutex_unlock(&wl->mutex);
		वापस;
	पूर्ण

	क्रम (queue_num = 0; queue_num < B43legacy_QOS_QUEUE_NUM; queue_num++) अणु
		जबतक (skb_queue_len(&wl->tx_queue[queue_num])) अणु
			skb = skb_dequeue(&wl->tx_queue[queue_num]);
			अगर (b43legacy_using_pio(dev))
				err = b43legacy_pio_tx(dev, skb);
			अन्यथा
				err = b43legacy_dma_tx(dev, skb);
			अगर (err == -ENOSPC) अणु
				wl->tx_queue_stopped[queue_num] = 1;
				ieee80211_stop_queue(wl->hw, queue_num);
				skb_queue_head(&wl->tx_queue[queue_num], skb);
				अवरोध;
			पूर्ण
			अगर (unlikely(err))
				dev_kमुक्त_skb(skb); /* Drop it */
			err = 0;
		पूर्ण

		अगर (!err)
			wl->tx_queue_stopped[queue_num] = 0;
	पूर्ण

	mutex_unlock(&wl->mutex);
पूर्ण

अटल व्योम b43legacy_op_tx(काष्ठा ieee80211_hw *hw,
			    काष्ठा ieee80211_tx_control *control,
			    काष्ठा sk_buff *skb)
अणु
	काष्ठा b43legacy_wl *wl = hw_to_b43legacy_wl(hw);

	अगर (unlikely(skb->len < 2 + 2 + 6)) अणु
		/* Too लघु, this can't be a valid frame. */
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण
	B43legacy_WARN_ON(skb_shinfo(skb)->nr_frags);

	skb_queue_tail(&wl->tx_queue[skb->queue_mapping], skb);
	अगर (!wl->tx_queue_stopped[skb->queue_mapping])
		ieee80211_queue_work(wl->hw, &wl->tx_work);
	अन्यथा
		ieee80211_stop_queue(wl->hw, skb->queue_mapping);
पूर्ण

अटल पूर्णांक b43legacy_op_conf_tx(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर, u16 queue,
				स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक b43legacy_op_get_stats(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_low_level_stats *stats)
अणु
	काष्ठा b43legacy_wl *wl = hw_to_b43legacy_wl(hw);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wl->irq_lock, flags);
	स_नकल(stats, &wl->ieee_stats, माप(*stats));
	spin_unlock_irqrestore(&wl->irq_lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *phymode_to_string(अचिन्हित पूर्णांक phymode)
अणु
	चयन (phymode) अणु
	हाल B43legacy_PHYMODE_B:
		वापस "B";
	हाल B43legacy_PHYMODE_G:
		वापस "G";
	शेष:
		B43legacy_BUG_ON(1);
	पूर्ण
	वापस "";
पूर्ण

अटल पूर्णांक find_wldev_क्रम_phymode(काष्ठा b43legacy_wl *wl,
				  अचिन्हित पूर्णांक phymode,
				  काष्ठा b43legacy_wldev **dev,
				  bool *gmode)
अणु
	काष्ठा b43legacy_wldev *d;

	list_क्रम_each_entry(d, &wl->devlist, list) अणु
		अगर (d->phy.possible_phymodes & phymode) अणु
			/* Ok, this device supports the PHY-mode.
			 * Set the gmode bit. */
			*gmode = true;
			*dev = d;

			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ESRCH;
पूर्ण

अटल व्योम b43legacy_put_phy_पूर्णांकo_reset(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा ssb_device *sdev = dev->dev;
	u32 पंचांगslow;

	पंचांगslow = ssb_पढ़ो32(sdev, SSB_TMSLOW);
	पंचांगslow &= ~B43legacy_TMSLOW_GMODE;
	पंचांगslow |= B43legacy_TMSLOW_PHYRESET;
	पंचांगslow |= SSB_TMSLOW_FGC;
	ssb_ग_लिखो32(sdev, SSB_TMSLOW, पंचांगslow);
	msleep(1);

	पंचांगslow = ssb_पढ़ो32(sdev, SSB_TMSLOW);
	पंचांगslow &= ~SSB_TMSLOW_FGC;
	पंचांगslow |= B43legacy_TMSLOW_PHYRESET;
	ssb_ग_लिखो32(sdev, SSB_TMSLOW, पंचांगslow);
	msleep(1);
पूर्ण

/* Expects wl->mutex locked */
अटल पूर्णांक b43legacy_चयन_phymode(काष्ठा b43legacy_wl *wl,
				      अचिन्हित पूर्णांक new_mode)
अणु
	काष्ठा b43legacy_wldev *up_dev;
	काष्ठा b43legacy_wldev *करोwn_dev;
	पूर्णांक err;
	bool gmode = false;
	पूर्णांक prev_status;

	err = find_wldev_क्रम_phymode(wl, new_mode, &up_dev, &gmode);
	अगर (err) अणु
		b43legacyerr(wl, "Could not find a device for %s-PHY mode\n",
		       phymode_to_string(new_mode));
		वापस err;
	पूर्ण
	अगर ((up_dev == wl->current_dev) &&
	    (!!wl->current_dev->phy.gmode == !!gmode))
		/* This device is alपढ़ोy running. */
		वापस 0;
	b43legacydbg(wl, "Reconfiguring PHYmode to %s-PHY\n",
	       phymode_to_string(new_mode));
	करोwn_dev = wl->current_dev;

	prev_status = b43legacy_status(करोwn_dev);
	/* Shutकरोwn the currently running core. */
	अगर (prev_status >= B43legacy_STAT_STARTED)
		b43legacy_wireless_core_stop(करोwn_dev);
	अगर (prev_status >= B43legacy_STAT_INITIALIZED)
		b43legacy_wireless_core_निकास(करोwn_dev);

	अगर (करोwn_dev != up_dev)
		/* We चयन to a dअगरferent core, so we put PHY पूर्णांकo
		 * RESET on the old core. */
		b43legacy_put_phy_पूर्णांकo_reset(करोwn_dev);

	/* Now start the new core. */
	up_dev->phy.gmode = gmode;
	अगर (prev_status >= B43legacy_STAT_INITIALIZED) अणु
		err = b43legacy_wireless_core_init(up_dev);
		अगर (err) अणु
			b43legacyerr(wl, "Fatal: Could not initialize device"
				     " for newly selected %s-PHY mode\n",
				     phymode_to_string(new_mode));
			जाओ init_failure;
		पूर्ण
	पूर्ण
	अगर (prev_status >= B43legacy_STAT_STARTED) अणु
		err = b43legacy_wireless_core_start(up_dev);
		अगर (err) अणु
			b43legacyerr(wl, "Fatal: Could not start device for "
			       "newly selected %s-PHY mode\n",
			       phymode_to_string(new_mode));
			b43legacy_wireless_core_निकास(up_dev);
			जाओ init_failure;
		पूर्ण
	पूर्ण
	B43legacy_WARN_ON(b43legacy_status(up_dev) != prev_status);

	b43legacy_shm_ग_लिखो32(up_dev, B43legacy_SHM_SHARED, 0x003E, 0);

	wl->current_dev = up_dev;

	वापस 0;
init_failure:
	/* Whoops, failed to init the new core. No core is operating now. */
	wl->current_dev = शून्य;
	वापस err;
पूर्ण

/* Write the लघु and दीर्घ frame retry limit values. */
अटल व्योम b43legacy_set_retry_limits(काष्ठा b43legacy_wldev *dev,
				       अचिन्हित पूर्णांक लघु_retry,
				       अचिन्हित पूर्णांक दीर्घ_retry)
अणु
	/* The retry limit is a 4-bit counter. Enक्रमce this to aव्योम overflowing
	 * the chip-पूर्णांकernal counter. */
	लघु_retry = min(लघु_retry, (अचिन्हित पूर्णांक)0xF);
	दीर्घ_retry = min(दीर्घ_retry, (अचिन्हित पूर्णांक)0xF);

	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_WIRELESS, 0x0006, लघु_retry);
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_WIRELESS, 0x0007, दीर्घ_retry);
पूर्ण

अटल पूर्णांक b43legacy_op_dev_config(काष्ठा ieee80211_hw *hw,
				   u32 changed)
अणु
	काष्ठा b43legacy_wl *wl = hw_to_b43legacy_wl(hw);
	काष्ठा b43legacy_wldev *dev;
	काष्ठा b43legacy_phy *phy;
	काष्ठा ieee80211_conf *conf = &hw->conf;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक new_phymode = 0xFFFF;
	पूर्णांक antenna_tx;
	पूर्णांक err = 0;

	antenna_tx = B43legacy_ANTENNA_DEFAULT;

	mutex_lock(&wl->mutex);
	dev = wl->current_dev;
	phy = &dev->phy;

	अगर (changed & IEEE80211_CONF_CHANGE_RETRY_LIMITS)
		b43legacy_set_retry_limits(dev,
					   conf->लघु_frame_max_tx_count,
					   conf->दीर्घ_frame_max_tx_count);
	changed &= ~IEEE80211_CONF_CHANGE_RETRY_LIMITS;
	अगर (!changed)
		जाओ out_unlock_mutex;

	/* Switch the PHY mode (अगर necessary). */
	चयन (conf->chandef.chan->band) अणु
	हाल NL80211_BAND_2GHZ:
		अगर (phy->type == B43legacy_PHYTYPE_B)
			new_phymode = B43legacy_PHYMODE_B;
		अन्यथा
			new_phymode = B43legacy_PHYMODE_G;
		अवरोध;
	शेष:
		B43legacy_WARN_ON(1);
	पूर्ण
	err = b43legacy_चयन_phymode(wl, new_phymode);
	अगर (err)
		जाओ out_unlock_mutex;

	/* Disable IRQs जबतक reconfiguring the device.
	 * This makes it possible to drop the spinlock throughout
	 * the reconfiguration process. */
	spin_lock_irqsave(&wl->irq_lock, flags);
	अगर (b43legacy_status(dev) < B43legacy_STAT_STARTED) अणु
		spin_unlock_irqrestore(&wl->irq_lock, flags);
		जाओ out_unlock_mutex;
	पूर्ण
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_GEN_IRQ_MASK, 0);
	spin_unlock_irqrestore(&wl->irq_lock, flags);
	b43legacy_synchronize_irq(dev);

	/* Switch to the requested channel.
	 * The firmware takes care of races with the TX handler. */
	अगर (conf->chandef.chan->hw_value != phy->channel)
		b43legacy_radio_selectchannel(dev, conf->chandef.chan->hw_value,
					      0);

	dev->wl->radiotap_enabled = !!(conf->flags & IEEE80211_CONF_MONITOR);

	/* Adjust the desired TX घातer level. */
	अगर (conf->घातer_level != 0) अणु
		अगर (conf->घातer_level != phy->घातer_level) अणु
			phy->घातer_level = conf->घातer_level;
			b43legacy_phy_xmitघातer(dev);
		पूर्ण
	पूर्ण

	/* Antennas क्रम RX and management frame TX. */
	b43legacy_mgmtframe_txantenna(dev, antenna_tx);

	अगर (wl->radio_enabled != phy->radio_on) अणु
		अगर (wl->radio_enabled) अणु
			b43legacy_radio_turn_on(dev);
			b43legacyinfo(dev->wl, "Radio turned on by software\n");
			अगर (!dev->radio_hw_enable)
				b43legacyinfo(dev->wl, "The hardware RF-kill"
					      " button still turns the radio"
					      " physically off. Press the"
					      " button to turn it on.\n");
		पूर्ण अन्यथा अणु
			b43legacy_radio_turn_off(dev, 0);
			b43legacyinfo(dev->wl, "Radio turned off by"
				      " software\n");
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&wl->irq_lock, flags);
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_GEN_IRQ_MASK, dev->irq_mask);
	spin_unlock_irqrestore(&wl->irq_lock, flags);
out_unlock_mutex:
	mutex_unlock(&wl->mutex);

	वापस err;
पूर्ण

अटल व्योम b43legacy_update_basic_rates(काष्ठा b43legacy_wldev *dev, u32 brates)
अणु
	काष्ठा ieee80211_supported_band *sband =
		dev->wl->hw->wiphy->bands[NL80211_BAND_2GHZ];
	स्थिर काष्ठा ieee80211_rate *rate;
	पूर्णांक i;
	u16 basic, direct, offset, basic_offset, rateptr;

	क्रम (i = 0; i < sband->n_bitrates; i++) अणु
		rate = &sband->bitrates[i];

		अगर (b43legacy_is_cck_rate(rate->hw_value)) अणु
			direct = B43legacy_SHM_SH_CCKसूचीECT;
			basic = B43legacy_SHM_SH_CCKBASIC;
			offset = b43legacy_plcp_get_ratecode_cck(rate->hw_value);
			offset &= 0xF;
		पूर्ण अन्यथा अणु
			direct = B43legacy_SHM_SH_OFDMसूचीECT;
			basic = B43legacy_SHM_SH_OFDMBASIC;
			offset = b43legacy_plcp_get_ratecode_ofdm(rate->hw_value);
			offset &= 0xF;
		पूर्ण

		rate = ieee80211_get_response_rate(sband, brates, rate->bitrate);

		अगर (b43legacy_is_cck_rate(rate->hw_value)) अणु
			basic_offset = b43legacy_plcp_get_ratecode_cck(rate->hw_value);
			basic_offset &= 0xF;
		पूर्ण अन्यथा अणु
			basic_offset = b43legacy_plcp_get_ratecode_ofdm(rate->hw_value);
			basic_offset &= 0xF;
		पूर्ण

		/*
		 * Get the poपूर्णांकer that we need to poपूर्णांक to
		 * from the direct map
		 */
		rateptr = b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_SHARED,
					       direct + 2 * basic_offset);
		/* and ग_लिखो it to the basic map */
		b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED,
				      basic + 2 * offset, rateptr);
	पूर्ण
पूर्ण

अटल व्योम b43legacy_op_bss_info_changed(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_bss_conf *conf,
				    u32 changed)
अणु
	काष्ठा b43legacy_wl *wl = hw_to_b43legacy_wl(hw);
	काष्ठा b43legacy_wldev *dev;
	अचिन्हित दीर्घ flags;

	mutex_lock(&wl->mutex);
	B43legacy_WARN_ON(wl->vअगर != vअगर);

	dev = wl->current_dev;

	/* Disable IRQs जबतक reconfiguring the device.
	 * This makes it possible to drop the spinlock throughout
	 * the reconfiguration process. */
	spin_lock_irqsave(&wl->irq_lock, flags);
	अगर (b43legacy_status(dev) < B43legacy_STAT_STARTED) अणु
		spin_unlock_irqrestore(&wl->irq_lock, flags);
		जाओ out_unlock_mutex;
	पूर्ण
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_GEN_IRQ_MASK, 0);

	अगर (changed & BSS_CHANGED_BSSID) अणु
		b43legacy_synchronize_irq(dev);

		अगर (conf->bssid)
			स_नकल(wl->bssid, conf->bssid, ETH_ALEN);
		अन्यथा
			eth_zero_addr(wl->bssid);
	पूर्ण

	अगर (b43legacy_status(dev) >= B43legacy_STAT_INITIALIZED) अणु
		अगर (changed & BSS_CHANGED_BEACON &&
		    (b43legacy_is_mode(wl, NL80211_IFTYPE_AP) ||
		     b43legacy_is_mode(wl, NL80211_IFTYPE_ADHOC)))
			b43legacy_update_ढाँचाs(wl);

		अगर (changed & BSS_CHANGED_BSSID)
			b43legacy_ग_लिखो_mac_bssid_ढाँचाs(dev);
	पूर्ण
	spin_unlock_irqrestore(&wl->irq_lock, flags);

	b43legacy_mac_suspend(dev);

	अगर (changed & BSS_CHANGED_BEACON_INT &&
	    (b43legacy_is_mode(wl, NL80211_IFTYPE_AP) ||
	     b43legacy_is_mode(wl, NL80211_IFTYPE_ADHOC)))
		b43legacy_set_beacon_पूर्णांक(dev, conf->beacon_पूर्णांक);

	अगर (changed & BSS_CHANGED_BASIC_RATES)
		b43legacy_update_basic_rates(dev, conf->basic_rates);

	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		अगर (conf->use_लघु_slot)
			b43legacy_लघु_slot_timing_enable(dev);
		अन्यथा
			b43legacy_लघु_slot_timing_disable(dev);
	पूर्ण

	b43legacy_mac_enable(dev);

	spin_lock_irqsave(&wl->irq_lock, flags);
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_GEN_IRQ_MASK, dev->irq_mask);
	/* XXX: why? */
	spin_unlock_irqrestore(&wl->irq_lock, flags);
 out_unlock_mutex:
	mutex_unlock(&wl->mutex);
पूर्ण

अटल व्योम b43legacy_op_configure_filter(काष्ठा ieee80211_hw *hw,
					  अचिन्हित पूर्णांक changed,
					  अचिन्हित पूर्णांक *fflags,u64 multicast)
अणु
	काष्ठा b43legacy_wl *wl = hw_to_b43legacy_wl(hw);
	काष्ठा b43legacy_wldev *dev = wl->current_dev;
	अचिन्हित दीर्घ flags;

	अगर (!dev) अणु
		*fflags = 0;
		वापस;
	पूर्ण

	spin_lock_irqsave(&wl->irq_lock, flags);
	*fflags &= FIF_ALLMULTI |
		  FIF_FCSFAIL |
		  FIF_PLCPFAIL |
		  FIF_CONTROL |
		  FIF_OTHER_BSS |
		  FIF_BCN_PRBRESP_PROMISC;

	changed &= FIF_ALLMULTI |
		   FIF_FCSFAIL |
		   FIF_PLCPFAIL |
		   FIF_CONTROL |
		   FIF_OTHER_BSS |
		   FIF_BCN_PRBRESP_PROMISC;

	wl->filter_flags = *fflags;

	अगर (changed && b43legacy_status(dev) >= B43legacy_STAT_INITIALIZED)
		b43legacy_adjust_opmode(dev);
	spin_unlock_irqrestore(&wl->irq_lock, flags);
पूर्ण

/* Locking: wl->mutex */
अटल व्योम b43legacy_wireless_core_stop(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_wl *wl = dev->wl;
	अचिन्हित दीर्घ flags;
	पूर्णांक queue_num;

	अगर (b43legacy_status(dev) < B43legacy_STAT_STARTED)
		वापस;

	/* Disable and sync पूर्णांकerrupts. We must करो this beक्रमe than
	 * setting the status to INITIALIZED, as the पूर्णांकerrupt handler
	 * won't care about IRQs then. */
	spin_lock_irqsave(&wl->irq_lock, flags);
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_GEN_IRQ_MASK, 0);
	b43legacy_पढ़ो32(dev, B43legacy_MMIO_GEN_IRQ_MASK); /* flush */
	spin_unlock_irqrestore(&wl->irq_lock, flags);
	b43legacy_synchronize_irq(dev);

	b43legacy_set_status(dev, B43legacy_STAT_INITIALIZED);

	mutex_unlock(&wl->mutex);
	/* Must unlock as it would otherwise deadlock. No races here.
	 * Cancel the possibly running self-rearming periodic work. */
	cancel_delayed_work_sync(&dev->periodic_work);
	cancel_work_sync(&wl->tx_work);
	mutex_lock(&wl->mutex);

	/* Drain all TX queues. */
	क्रम (queue_num = 0; queue_num < B43legacy_QOS_QUEUE_NUM; queue_num++) अणु
		जबतक (skb_queue_len(&wl->tx_queue[queue_num]))
			dev_kमुक्त_skb(skb_dequeue(&wl->tx_queue[queue_num]));
	पूर्ण

b43legacy_mac_suspend(dev);
	मुक्त_irq(dev->dev->irq, dev);
	b43legacydbg(wl, "Wireless interface stopped\n");
पूर्ण

/* Locking: wl->mutex */
अटल पूर्णांक b43legacy_wireless_core_start(काष्ठा b43legacy_wldev *dev)
अणु
	पूर्णांक err;

	B43legacy_WARN_ON(b43legacy_status(dev) != B43legacy_STAT_INITIALIZED);

	drain_txstatus_queue(dev);
	err = request_irq(dev->dev->irq, b43legacy_पूर्णांकerrupt_handler,
			  IRQF_SHARED, KBUILD_MODNAME, dev);
	अगर (err) अणु
		b43legacyerr(dev->wl, "Cannot request IRQ-%d\n",
		       dev->dev->irq);
		जाओ out;
	पूर्ण
	/* We are पढ़ोy to run. */
	ieee80211_wake_queues(dev->wl->hw);
	b43legacy_set_status(dev, B43legacy_STAT_STARTED);

	/* Start data flow (TX/RX) */
	b43legacy_mac_enable(dev);
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_GEN_IRQ_MASK, dev->irq_mask);

	/* Start मुख्यtenance work */
	b43legacy_periodic_tasks_setup(dev);

	b43legacydbg(dev->wl, "Wireless interface started\n");
out:
	वापस err;
पूर्ण

/* Get PHY and RADIO versioning numbers */
अटल पूर्णांक b43legacy_phy_versioning(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u32 पंचांगp;
	u8 analog_type;
	u8 phy_type;
	u8 phy_rev;
	u16 radio_manuf;
	u16 radio_ver;
	u16 radio_rev;
	पूर्णांक unsupported = 0;

	/* Get PHY versioning */
	पंचांगp = b43legacy_पढ़ो16(dev, B43legacy_MMIO_PHY_VER);
	analog_type = (पंचांगp & B43legacy_PHYVER_ANALOG)
		      >> B43legacy_PHYVER_ANALOG_SHIFT;
	phy_type = (पंचांगp & B43legacy_PHYVER_TYPE) >> B43legacy_PHYVER_TYPE_SHIFT;
	phy_rev = (पंचांगp & B43legacy_PHYVER_VERSION);
	चयन (phy_type) अणु
	हाल B43legacy_PHYTYPE_B:
		अगर (phy_rev != 2 && phy_rev != 4
		    && phy_rev != 6 && phy_rev != 7)
			unsupported = 1;
		अवरोध;
	हाल B43legacy_PHYTYPE_G:
		अगर (phy_rev > 8)
			unsupported = 1;
		अवरोध;
	शेष:
		unsupported = 1;
	पूर्ण
	अगर (unsupported) अणु
		b43legacyerr(dev->wl, "FOUND UNSUPPORTED PHY "
		       "(Analog %u, Type %u, Revision %u)\n",
		       analog_type, phy_type, phy_rev);
		वापस -EOPNOTSUPP;
	पूर्ण
	b43legacydbg(dev->wl, "Found PHY: Analog %u, Type %u, Revision %u\n",
	       analog_type, phy_type, phy_rev);


	/* Get RADIO versioning */
	अगर (dev->dev->bus->chip_id == 0x4317) अणु
		अगर (dev->dev->bus->chip_rev == 0)
			पंचांगp = 0x3205017F;
		अन्यथा अगर (dev->dev->bus->chip_rev == 1)
			पंचांगp = 0x4205017F;
		अन्यथा
			पंचांगp = 0x5205017F;
	पूर्ण अन्यथा अणु
		b43legacy_ग_लिखो16(dev, B43legacy_MMIO_RADIO_CONTROL,
				  B43legacy_RADIOCTL_ID);
		पंचांगp = b43legacy_पढ़ो16(dev, B43legacy_MMIO_RADIO_DATA_HIGH);
		पंचांगp <<= 16;
		b43legacy_ग_लिखो16(dev, B43legacy_MMIO_RADIO_CONTROL,
				  B43legacy_RADIOCTL_ID);
		पंचांगp |= b43legacy_पढ़ो16(dev, B43legacy_MMIO_RADIO_DATA_LOW);
	पूर्ण
	radio_manuf = (पंचांगp & 0x00000FFF);
	radio_ver = (पंचांगp & 0x0FFFF000) >> 12;
	radio_rev = (पंचांगp & 0xF0000000) >> 28;
	चयन (phy_type) अणु
	हाल B43legacy_PHYTYPE_B:
		अगर ((radio_ver & 0xFFF0) != 0x2050)
			unsupported = 1;
		अवरोध;
	हाल B43legacy_PHYTYPE_G:
		अगर (radio_ver != 0x2050)
			unsupported = 1;
		अवरोध;
	शेष:
		B43legacy_BUG_ON(1);
	पूर्ण
	अगर (unsupported) अणु
		b43legacyerr(dev->wl, "FOUND UNSUPPORTED RADIO "
		       "(Manuf 0x%X, Version 0x%X, Revision %u)\n",
		       radio_manuf, radio_ver, radio_rev);
		वापस -EOPNOTSUPP;
	पूर्ण
	b43legacydbg(dev->wl, "Found Radio: Manuf 0x%X, Version 0x%X,"
		     " Revision %u\n", radio_manuf, radio_ver, radio_rev);


	phy->radio_manuf = radio_manuf;
	phy->radio_ver = radio_ver;
	phy->radio_rev = radio_rev;

	phy->analog = analog_type;
	phy->type = phy_type;
	phy->rev = phy_rev;

	वापस 0;
पूर्ण

अटल व्योम setup_काष्ठा_phy_क्रम_init(काष्ठा b43legacy_wldev *dev,
				      काष्ठा b43legacy_phy *phy)
अणु
	काष्ठा b43legacy_lopair *lo;
	पूर्णांक i;

	स_रखो(phy->minlowsig, 0xFF, माप(phy->minlowsig));
	स_रखो(phy->minlowsigpos, 0, माप(phy->minlowsigpos));

	/* Assume the radio is enabled. If it's not enabled, the state will
	 * immediately get fixed on the first periodic work run. */
	dev->radio_hw_enable = true;

	phy->savedpctlreg = 0xFFFF;
	phy->aci_enable = false;
	phy->aci_wlan_स्वतःmatic = false;
	phy->aci_hw_rssi = false;

	lo = phy->_lo_pairs;
	अगर (lo)
		स_रखो(lo, 0, माप(काष्ठा b43legacy_lopair) *
				     B43legacy_LO_COUNT);
	phy->max_lb_gain = 0;
	phy->trsw_rx_gain = 0;

	/* Set शेष attenuation values. */
	phy->bbatt = b43legacy_शेष_baseband_attenuation(dev);
	phy->rfatt = b43legacy_शेष_radio_attenuation(dev);
	phy->txctl1 = b43legacy_शेष_txctl1(dev);
	phy->txpwr_offset = 0;

	/* NRSSI */
	phy->nrssislope = 0;
	क्रम (i = 0; i < ARRAY_SIZE(phy->nrssi); i++)
		phy->nrssi[i] = -1000;
	क्रम (i = 0; i < ARRAY_SIZE(phy->nrssi_lt); i++)
		phy->nrssi_lt[i] = i;

	phy->lofcal = 0xFFFF;
	phy->initval = 0xFFFF;

	phy->पूर्णांकerभ_शेषe = B43legacy_INTERFMODE_NONE;
	phy->channel = 0xFF;
पूर्ण

अटल व्योम setup_काष्ठा_wldev_क्रम_init(काष्ठा b43legacy_wldev *dev)
अणु
	/* Flags */
	dev->dfq_valid = false;

	/* Stats */
	स_रखो(&dev->stats, 0, माप(dev->stats));

	setup_काष्ठा_phy_क्रम_init(dev, &dev->phy);

	/* IRQ related flags */
	dev->irq_reason = 0;
	स_रखो(dev->dma_reason, 0, माप(dev->dma_reason));
	dev->irq_mask = B43legacy_IRQ_MASKTEMPLATE;

	dev->mac_suspended = 1;

	/* Noise calculation context */
	स_रखो(&dev->noisecalc, 0, माप(dev->noisecalc));
पूर्ण

अटल व्योम b43legacy_set_synth_pu_delay(काष्ठा b43legacy_wldev *dev,
					  bool idle) अणु
	u16 pu_delay = 1050;

	अगर (b43legacy_is_mode(dev->wl, NL80211_IFTYPE_ADHOC) || idle)
		pu_delay = 500;
	अगर ((dev->phy.radio_ver == 0x2050) && (dev->phy.radio_rev == 8))
		pu_delay = max(pu_delay, (u16)2400);

	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED,
			      B43legacy_SHM_SH_SPUWKUP, pu_delay);
पूर्ण

/* Set the TSF CFP pre-TargetBeaconTransmissionTime. */
अटल व्योम b43legacy_set_pretbtt(काष्ठा b43legacy_wldev *dev)
अणु
	u16 pretbtt;

	/* The समय value is in microseconds. */
	अगर (b43legacy_is_mode(dev->wl, NL80211_IFTYPE_ADHOC))
		pretbtt = 2;
	अन्यथा
		pretbtt = 250;
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED,
			      B43legacy_SHM_SH_PRETBTT, pretbtt);
	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_TSF_CFP_PRETBTT, pretbtt);
पूर्ण

/* Shutकरोwn a wireless core */
/* Locking: wl->mutex */
अटल व्योम b43legacy_wireless_core_निकास(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	u32 macctl;

	B43legacy_WARN_ON(b43legacy_status(dev) > B43legacy_STAT_INITIALIZED);
	अगर (b43legacy_status(dev) != B43legacy_STAT_INITIALIZED)
		वापस;
	b43legacy_set_status(dev, B43legacy_STAT_UNINIT);

	/* Stop the microcode PSM. */
	macctl = b43legacy_पढ़ो32(dev, B43legacy_MMIO_MACCTL);
	macctl &= ~B43legacy_MACCTL_PSM_RUN;
	macctl |= B43legacy_MACCTL_PSM_JMP0;
	b43legacy_ग_लिखो32(dev, B43legacy_MMIO_MACCTL, macctl);

	b43legacy_leds_निकास(dev);
	b43legacy_rng_निकास(dev->wl);
	b43legacy_pio_मुक्त(dev);
	b43legacy_dma_मुक्त(dev);
	b43legacy_chip_निकास(dev);
	b43legacy_radio_turn_off(dev, 1);
	b43legacy_चयन_analog(dev, 0);
	अगर (phy->dyn_tssi_tbl)
		kमुक्त(phy->tssi2dbm);
	kमुक्त(phy->lo_control);
	phy->lo_control = शून्य;
	अगर (dev->wl->current_beacon) अणु
		dev_kमुक्त_skb_any(dev->wl->current_beacon);
		dev->wl->current_beacon = शून्य;
	पूर्ण

	ssb_device_disable(dev->dev, 0);
	ssb_bus_may_घातerकरोwn(dev->dev->bus);
पूर्ण

अटल व्योम prepare_phy_data_क्रम_init(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	पूर्णांक i;

	/* Set शेष attenuation values. */
	phy->bbatt = b43legacy_शेष_baseband_attenuation(dev);
	phy->rfatt = b43legacy_शेष_radio_attenuation(dev);
	phy->txctl1 = b43legacy_शेष_txctl1(dev);
	phy->txctl2 = 0xFFFF;
	phy->txpwr_offset = 0;

	/* NRSSI */
	phy->nrssislope = 0;
	क्रम (i = 0; i < ARRAY_SIZE(phy->nrssi); i++)
		phy->nrssi[i] = -1000;
	क्रम (i = 0; i < ARRAY_SIZE(phy->nrssi_lt); i++)
		phy->nrssi_lt[i] = i;

	phy->lofcal = 0xFFFF;
	phy->initval = 0xFFFF;

	phy->aci_enable = false;
	phy->aci_wlan_स्वतःmatic = false;
	phy->aci_hw_rssi = false;

	phy->antenna_भागersity = 0xFFFF;
	स_रखो(phy->minlowsig, 0xFF, माप(phy->minlowsig));
	स_रखो(phy->minlowsigpos, 0, माप(phy->minlowsigpos));

	/* Flags */
	phy->calibrated = 0;

	अगर (phy->_lo_pairs)
		स_रखो(phy->_lo_pairs, 0,
		       माप(काष्ठा b43legacy_lopair) * B43legacy_LO_COUNT);
	स_रखो(phy->loopback_gain, 0, माप(phy->loopback_gain));
पूर्ण

/* Initialize a wireless core */
अटल पूर्णांक b43legacy_wireless_core_init(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_wl *wl = dev->wl;
	काष्ठा ssb_bus *bus = dev->dev->bus;
	काष्ठा b43legacy_phy *phy = &dev->phy;
	काष्ठा ssb_sprom *sprom = &dev->dev->bus->sprom;
	पूर्णांक err;
	u32 hf;
	u32 पंचांगp;

	B43legacy_WARN_ON(b43legacy_status(dev) != B43legacy_STAT_UNINIT);

	err = ssb_bus_घातerup(bus, 0);
	अगर (err)
		जाओ out;
	अगर (!ssb_device_is_enabled(dev->dev)) अणु
		पंचांगp = phy->gmode ? B43legacy_TMSLOW_GMODE : 0;
		b43legacy_wireless_core_reset(dev, पंचांगp);
	पूर्ण

	अगर ((phy->type == B43legacy_PHYTYPE_B) ||
	    (phy->type == B43legacy_PHYTYPE_G)) अणु
		phy->_lo_pairs = kसुस्मृति(B43legacy_LO_COUNT,
					 माप(काष्ठा b43legacy_lopair),
					 GFP_KERNEL);
		अगर (!phy->_lo_pairs)
			वापस -ENOMEM;
	पूर्ण
	setup_काष्ठा_wldev_क्रम_init(dev);

	err = b43legacy_phy_init_tssi2dbm_table(dev);
	अगर (err)
		जाओ err_kमुक्त_lo_control;

	/* Enable IRQ routing to this device. */
	ssb_pcicore_dev_irqvecs_enable(&bus->pcicore, dev->dev);

	prepare_phy_data_क्रम_init(dev);
	b43legacy_phy_calibrate(dev);
	err = b43legacy_chip_init(dev);
	अगर (err)
		जाओ err_kमुक्त_tssitbl;
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED,
			      B43legacy_SHM_SH_WLCOREREV,
			      dev->dev->id.revision);
	hf = b43legacy_hf_पढ़ो(dev);
	अगर (phy->type == B43legacy_PHYTYPE_G) अणु
		hf |= B43legacy_HF_SYMW;
		अगर (phy->rev == 1)
			hf |= B43legacy_HF_GDCW;
		अगर (sprom->boardflags_lo & B43legacy_BFL_PACTRL)
			hf |= B43legacy_HF_OFDMPABOOST;
	पूर्ण अन्यथा अगर (phy->type == B43legacy_PHYTYPE_B) अणु
		hf |= B43legacy_HF_SYMW;
		अगर (phy->rev >= 2 && phy->radio_ver == 0x2050)
			hf &= ~B43legacy_HF_GDCW;
	पूर्ण
	b43legacy_hf_ग_लिखो(dev, hf);

	b43legacy_set_retry_limits(dev,
				   B43legacy_DEFAULT_SHORT_RETRY_LIMIT,
				   B43legacy_DEFAULT_LONG_RETRY_LIMIT);

	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED,
			      0x0044, 3);
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED,
			      0x0046, 2);

	/* Disable sending probe responses from firmware.
	 * Setting the MaxTime to one usec will always trigger
	 * a समयout, so we never send any probe resp.
	 * A समयout of zero is infinite. */
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_SHARED,
			      B43legacy_SHM_SH_PRMAXTIME, 1);

	b43legacy_rate_memory_init(dev);

	/* Minimum Contention Winकरोw */
	अगर (phy->type == B43legacy_PHYTYPE_B)
		b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_WIRELESS,
				      0x0003, 31);
	अन्यथा
		b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_WIRELESS,
				      0x0003, 15);
	/* Maximum Contention Winकरोw */
	b43legacy_shm_ग_लिखो16(dev, B43legacy_SHM_WIRELESS,
			      0x0004, 1023);

	करो अणु
		अगर (b43legacy_using_pio(dev))
			err = b43legacy_pio_init(dev);
		अन्यथा अणु
			err = b43legacy_dma_init(dev);
			अगर (!err)
				b43legacy_qos_init(dev);
		पूर्ण
	पूर्ण जबतक (err == -EAGAIN);
	अगर (err)
		जाओ err_chip_निकास;

	b43legacy_set_synth_pu_delay(dev, 1);

	ssb_bus_घातerup(bus, 1); /* Enable dynamic PCTL */
	b43legacy_upload_card_macaddress(dev);
	b43legacy_security_init(dev);
	b43legacy_rng_init(wl);

	ieee80211_wake_queues(dev->wl->hw);
	b43legacy_set_status(dev, B43legacy_STAT_INITIALIZED);

	b43legacy_leds_init(dev);
out:
	वापस err;

err_chip_निकास:
	b43legacy_chip_निकास(dev);
err_kमुक्त_tssitbl:
	अगर (phy->dyn_tssi_tbl)
		kमुक्त(phy->tssi2dbm);
err_kमुक्त_lo_control:
	kमुक्त(phy->lo_control);
	phy->lo_control = शून्य;
	ssb_bus_may_घातerकरोwn(bus);
	B43legacy_WARN_ON(b43legacy_status(dev) != B43legacy_STAT_UNINIT);
	वापस err;
पूर्ण

अटल पूर्णांक b43legacy_op_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा b43legacy_wl *wl = hw_to_b43legacy_wl(hw);
	काष्ठा b43legacy_wldev *dev;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = -EOPNOTSUPP;

	/* TODO: allow AP devices to coexist */

	अगर (vअगर->type != NL80211_IFTYPE_AP &&
	    vअगर->type != NL80211_IFTYPE_STATION &&
	    vअगर->type != NL80211_IFTYPE_ADHOC)
		वापस -EOPNOTSUPP;

	mutex_lock(&wl->mutex);
	अगर (wl->operating)
		जाओ out_mutex_unlock;

	b43legacydbg(wl, "Adding Interface type %d\n", vअगर->type);

	dev = wl->current_dev;
	wl->operating = true;
	wl->vअगर = vअगर;
	wl->अगर_type = vअगर->type;
	स_नकल(wl->mac_addr, vअगर->addr, ETH_ALEN);

	spin_lock_irqsave(&wl->irq_lock, flags);
	b43legacy_adjust_opmode(dev);
	b43legacy_set_pretbtt(dev);
	b43legacy_set_synth_pu_delay(dev, 0);
	b43legacy_upload_card_macaddress(dev);
	spin_unlock_irqrestore(&wl->irq_lock, flags);

	err = 0;
 out_mutex_unlock:
	mutex_unlock(&wl->mutex);

	वापस err;
पूर्ण

अटल व्योम b43legacy_op_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
					  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा b43legacy_wl *wl = hw_to_b43legacy_wl(hw);
	काष्ठा b43legacy_wldev *dev = wl->current_dev;
	अचिन्हित दीर्घ flags;

	b43legacydbg(wl, "Removing Interface type %d\n", vअगर->type);

	mutex_lock(&wl->mutex);

	B43legacy_WARN_ON(!wl->operating);
	B43legacy_WARN_ON(wl->vअगर != vअगर);
	wl->vअगर = शून्य;

	wl->operating = false;

	spin_lock_irqsave(&wl->irq_lock, flags);
	b43legacy_adjust_opmode(dev);
	eth_zero_addr(wl->mac_addr);
	b43legacy_upload_card_macaddress(dev);
	spin_unlock_irqrestore(&wl->irq_lock, flags);

	mutex_unlock(&wl->mutex);
पूर्ण

अटल पूर्णांक b43legacy_op_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा b43legacy_wl *wl = hw_to_b43legacy_wl(hw);
	काष्ठा b43legacy_wldev *dev = wl->current_dev;
	पूर्णांक did_init = 0;
	पूर्णांक err = 0;

	/* Kill all old instance specअगरic inक्रमmation to make sure
	 * the card won't use it in the लघु समयframe between start
	 * and mac80211 reconfiguring it. */
	eth_zero_addr(wl->bssid);
	eth_zero_addr(wl->mac_addr);
	wl->filter_flags = 0;
	wl->beacon0_uploaded = false;
	wl->beacon1_uploaded = false;
	wl->beacon_ढाँचाs_virgin = true;
	wl->radio_enabled = true;

	mutex_lock(&wl->mutex);

	अगर (b43legacy_status(dev) < B43legacy_STAT_INITIALIZED) अणु
		err = b43legacy_wireless_core_init(dev);
		अगर (err)
			जाओ out_mutex_unlock;
		did_init = 1;
	पूर्ण

	अगर (b43legacy_status(dev) < B43legacy_STAT_STARTED) अणु
		err = b43legacy_wireless_core_start(dev);
		अगर (err) अणु
			अगर (did_init)
				b43legacy_wireless_core_निकास(dev);
			जाओ out_mutex_unlock;
		पूर्ण
	पूर्ण

	wiphy_rfसमाप्त_start_polling(hw->wiphy);

out_mutex_unlock:
	mutex_unlock(&wl->mutex);

	वापस err;
पूर्ण

अटल व्योम b43legacy_op_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा b43legacy_wl *wl = hw_to_b43legacy_wl(hw);
	काष्ठा b43legacy_wldev *dev = wl->current_dev;

	cancel_work_sync(&(wl->beacon_update_trigger));

	mutex_lock(&wl->mutex);
	अगर (b43legacy_status(dev) >= B43legacy_STAT_STARTED)
		b43legacy_wireless_core_stop(dev);
	b43legacy_wireless_core_निकास(dev);
	wl->radio_enabled = false;
	mutex_unlock(&wl->mutex);
पूर्ण

अटल पूर्णांक b43legacy_op_beacon_set_tim(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_sta *sta, bool set)
अणु
	काष्ठा b43legacy_wl *wl = hw_to_b43legacy_wl(hw);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wl->irq_lock, flags);
	b43legacy_update_ढाँचाs(wl);
	spin_unlock_irqrestore(&wl->irq_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक b43legacy_op_get_survey(काष्ठा ieee80211_hw *hw, पूर्णांक idx,
				   काष्ठा survey_info *survey)
अणु
	काष्ठा b43legacy_wl *wl = hw_to_b43legacy_wl(hw);
	काष्ठा b43legacy_wldev *dev = wl->current_dev;
	काष्ठा ieee80211_conf *conf = &hw->conf;

	अगर (idx != 0)
		वापस -ENOENT;

	survey->channel = conf->chandef.chan;
	survey->filled = SURVEY_INFO_NOISE_DBM;
	survey->noise = dev->stats.link_noise;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops b43legacy_hw_ops = अणु
	.tx			= b43legacy_op_tx,
	.conf_tx		= b43legacy_op_conf_tx,
	.add_पूर्णांकerface		= b43legacy_op_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface	= b43legacy_op_हटाओ_पूर्णांकerface,
	.config			= b43legacy_op_dev_config,
	.bss_info_changed	= b43legacy_op_bss_info_changed,
	.configure_filter	= b43legacy_op_configure_filter,
	.get_stats		= b43legacy_op_get_stats,
	.start			= b43legacy_op_start,
	.stop			= b43legacy_op_stop,
	.set_tim		= b43legacy_op_beacon_set_tim,
	.get_survey		= b43legacy_op_get_survey,
	.rfसमाप्त_poll		= b43legacy_rfसमाप्त_poll,
पूर्ण;

/* Hard-reset the chip. Do not call this directly.
 * Use b43legacy_controller_restart()
 */
अटल व्योम b43legacy_chip_reset(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा b43legacy_wldev *dev =
		container_of(work, काष्ठा b43legacy_wldev, restart_work);
	काष्ठा b43legacy_wl *wl = dev->wl;
	पूर्णांक err = 0;
	पूर्णांक prev_status;

	mutex_lock(&wl->mutex);

	prev_status = b43legacy_status(dev);
	/* Bring the device करोwn... */
	अगर (prev_status >= B43legacy_STAT_STARTED)
		b43legacy_wireless_core_stop(dev);
	अगर (prev_status >= B43legacy_STAT_INITIALIZED)
		b43legacy_wireless_core_निकास(dev);

	/* ...and up again. */
	अगर (prev_status >= B43legacy_STAT_INITIALIZED) अणु
		err = b43legacy_wireless_core_init(dev);
		अगर (err)
			जाओ out;
	पूर्ण
	अगर (prev_status >= B43legacy_STAT_STARTED) अणु
		err = b43legacy_wireless_core_start(dev);
		अगर (err) अणु
			b43legacy_wireless_core_निकास(dev);
			जाओ out;
		पूर्ण
	पूर्ण
out:
	अगर (err)
		wl->current_dev = शून्य; /* Failed to init the dev. */
	mutex_unlock(&wl->mutex);
	अगर (err)
		b43legacyerr(wl, "Controller restart FAILED\n");
	अन्यथा
		b43legacyinfo(wl, "Controller restarted\n");
पूर्ण

अटल पूर्णांक b43legacy_setup_modes(काष्ठा b43legacy_wldev *dev,
				 पूर्णांक have_bphy,
				 पूर्णांक have_gphy)
अणु
	काष्ठा ieee80211_hw *hw = dev->wl->hw;
	काष्ठा b43legacy_phy *phy = &dev->phy;

	phy->possible_phymodes = 0;
	अगर (have_bphy) अणु
		hw->wiphy->bands[NL80211_BAND_2GHZ] =
			&b43legacy_band_2GHz_BPHY;
		phy->possible_phymodes |= B43legacy_PHYMODE_B;
	पूर्ण

	अगर (have_gphy) अणु
		hw->wiphy->bands[NL80211_BAND_2GHZ] =
			&b43legacy_band_2GHz_GPHY;
		phy->possible_phymodes |= B43legacy_PHYMODE_G;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम b43legacy_wireless_core_detach(काष्ठा b43legacy_wldev *dev)
अणु
	/* We release firmware that late to not be required to re-request
	 * is all the समय when we reinit the core. */
	b43legacy_release_firmware(dev);
पूर्ण

अटल पूर्णांक b43legacy_wireless_core_attach(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_wl *wl = dev->wl;
	काष्ठा ssb_bus *bus = dev->dev->bus;
	काष्ठा pci_dev *pdev = (bus->bustype == SSB_BUSTYPE_PCI) ? bus->host_pci : शून्य;
	पूर्णांक err;
	पूर्णांक have_bphy = 0;
	पूर्णांक have_gphy = 0;
	u32 पंचांगp;

	/* Do NOT करो any device initialization here.
	 * Do it in wireless_core_init() instead.
	 * This function is क्रम gathering basic inक्रमmation about the HW, only.
	 * Also some काष्ठाs may be set up here. But most likely you want to
	 * have that in core_init(), too.
	 */

	err = ssb_bus_घातerup(bus, 0);
	अगर (err) अणु
		b43legacyerr(wl, "Bus powerup failed\n");
		जाओ out;
	पूर्ण
	/* Get the PHY type. */
	अगर (dev->dev->id.revision >= 5) अणु
		u32 पंचांगshigh;

		पंचांगshigh = ssb_पढ़ो32(dev->dev, SSB_TMSHIGH);
		have_gphy = !!(पंचांगshigh & B43legacy_TMSHIGH_GPHY);
		अगर (!have_gphy)
			have_bphy = 1;
	पूर्ण अन्यथा अगर (dev->dev->id.revision == 4)
		have_gphy = 1;
	अन्यथा
		have_bphy = 1;

	dev->phy.gmode = (have_gphy || have_bphy);
	dev->phy.radio_on = true;
	पंचांगp = dev->phy.gmode ? B43legacy_TMSLOW_GMODE : 0;
	b43legacy_wireless_core_reset(dev, पंचांगp);

	err = b43legacy_phy_versioning(dev);
	अगर (err)
		जाओ err_घातerकरोwn;
	/* Check अगर this device supports multiband. */
	अगर (!pdev ||
	    (pdev->device != 0x4312 &&
	     pdev->device != 0x4319 &&
	     pdev->device != 0x4324)) अणु
		/* No multiband support. */
		have_bphy = 0;
		have_gphy = 0;
		चयन (dev->phy.type) अणु
		हाल B43legacy_PHYTYPE_B:
			have_bphy = 1;
			अवरोध;
		हाल B43legacy_PHYTYPE_G:
			have_gphy = 1;
			अवरोध;
		शेष:
			B43legacy_BUG_ON(1);
		पूर्ण
	पूर्ण
	dev->phy.gmode = (have_gphy || have_bphy);
	पंचांगp = dev->phy.gmode ? B43legacy_TMSLOW_GMODE : 0;
	b43legacy_wireless_core_reset(dev, पंचांगp);

	err = b43legacy_validate_chipaccess(dev);
	अगर (err)
		जाओ err_घातerकरोwn;
	err = b43legacy_setup_modes(dev, have_bphy, have_gphy);
	अगर (err)
		जाओ err_घातerकरोwn;

	/* Now set some शेष "current_dev" */
	अगर (!wl->current_dev)
		wl->current_dev = dev;
	INIT_WORK(&dev->restart_work, b43legacy_chip_reset);

	b43legacy_radio_turn_off(dev, 1);
	b43legacy_चयन_analog(dev, 0);
	ssb_device_disable(dev->dev, 0);
	ssb_bus_may_घातerकरोwn(bus);

out:
	वापस err;

err_घातerकरोwn:
	ssb_bus_may_घातerकरोwn(bus);
	वापस err;
पूर्ण

अटल व्योम b43legacy_one_core_detach(काष्ठा ssb_device *dev)
अणु
	काष्ठा b43legacy_wldev *wldev;
	काष्ठा b43legacy_wl *wl;

	/* Do not cancel ieee80211-workqueue based work here.
	 * See comment in b43legacy_हटाओ(). */

	wldev = ssb_get_drvdata(dev);
	wl = wldev->wl;
	b43legacy_debugfs_हटाओ_device(wldev);
	b43legacy_wireless_core_detach(wldev);
	list_del(&wldev->list);
	wl->nr_devs--;
	ssb_set_drvdata(dev, शून्य);
	kमुक्त(wldev);
पूर्ण

अटल पूर्णांक b43legacy_one_core_attach(काष्ठा ssb_device *dev,
				     काष्ठा b43legacy_wl *wl)
अणु
	काष्ठा b43legacy_wldev *wldev;
	पूर्णांक err = -ENOMEM;

	wldev = kzalloc(माप(*wldev), GFP_KERNEL);
	अगर (!wldev)
		जाओ out;

	wldev->dev = dev;
	wldev->wl = wl;
	b43legacy_set_status(wldev, B43legacy_STAT_UNINIT);
	wldev->bad_frames_preempt = modparam_bad_frames_preempt;
	tasklet_setup(&wldev->isr_tasklet, b43legacy_पूर्णांकerrupt_tasklet);
	अगर (modparam_pio)
		wldev->__using_pio = true;
	INIT_LIST_HEAD(&wldev->list);

	err = b43legacy_wireless_core_attach(wldev);
	अगर (err)
		जाओ err_kमुक्त_wldev;

	list_add(&wldev->list, &wl->devlist);
	wl->nr_devs++;
	ssb_set_drvdata(dev, wldev);
	b43legacy_debugfs_add_device(wldev);
out:
	वापस err;

err_kमुक्त_wldev:
	kमुक्त(wldev);
	वापस err;
पूर्ण

अटल व्योम b43legacy_sprom_fixup(काष्ठा ssb_bus *bus)
अणु
	/* boardflags workarounds */
	अगर (bus->boardinfo.venकरोr == PCI_VENDOR_ID_APPLE &&
	    bus->boardinfo.type == 0x4E &&
	    bus->sprom.board_rev > 0x40)
		bus->sprom.boardflags_lo |= B43legacy_BFL_PACTRL;
पूर्ण

अटल व्योम b43legacy_wireless_निकास(काष्ठा ssb_device *dev,
				  काष्ठा b43legacy_wl *wl)
अणु
	काष्ठा ieee80211_hw *hw = wl->hw;

	ssb_set_devtypedata(dev, शून्य);
	ieee80211_मुक्त_hw(hw);
पूर्ण

अटल पूर्णांक b43legacy_wireless_init(काष्ठा ssb_device *dev)
अणु
	काष्ठा ssb_sprom *sprom = &dev->bus->sprom;
	काष्ठा ieee80211_hw *hw;
	काष्ठा b43legacy_wl *wl;
	पूर्णांक err = -ENOMEM;
	पूर्णांक queue_num;

	b43legacy_sprom_fixup(dev->bus);

	hw = ieee80211_alloc_hw(माप(*wl), &b43legacy_hw_ops);
	अगर (!hw) अणु
		b43legacyerr(शून्य, "Could not allocate ieee80211 device\n");
		जाओ out;
	पूर्ण

	/* fill hw info */
	ieee80211_hw_set(hw, RX_INCLUDES_FCS);
	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, MFP_CAPABLE); /* Allow WPA3 in software */

	hw->wiphy->पूर्णांकerface_modes =
		BIT(NL80211_IFTYPE_AP) |
		BIT(NL80211_IFTYPE_STATION) |
		BIT(NL80211_IFTYPE_ADHOC);
	hw->queues = 1; /* FIXME: hardware has more queues */
	hw->max_rates = 2;
	SET_IEEE80211_DEV(hw, dev->dev);
	अगर (is_valid_ether_addr(sprom->et1mac))
		SET_IEEE80211_PERM_ADDR(hw, sprom->et1mac);
	अन्यथा
		SET_IEEE80211_PERM_ADDR(hw, sprom->il0mac);

	wiphy_ext_feature_set(hw->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	/* Get and initialize काष्ठा b43legacy_wl */
	wl = hw_to_b43legacy_wl(hw);
	स_रखो(wl, 0, माप(*wl));
	wl->hw = hw;
	spin_lock_init(&wl->irq_lock);
	spin_lock_init(&wl->leds_lock);
	mutex_init(&wl->mutex);
	INIT_LIST_HEAD(&wl->devlist);
	INIT_WORK(&wl->beacon_update_trigger, b43legacy_beacon_update_trigger_work);
	INIT_WORK(&wl->tx_work, b43legacy_tx_work);

	/* Initialize queues and flags. */
	क्रम (queue_num = 0; queue_num < B43legacy_QOS_QUEUE_NUM; queue_num++) अणु
		skb_queue_head_init(&wl->tx_queue[queue_num]);
		wl->tx_queue_stopped[queue_num] = 0;
	पूर्ण

	ssb_set_devtypedata(dev, wl);
	b43legacyinfo(wl, "Broadcom %04X WLAN found (core revision %u)\n",
		      dev->bus->chip_id, dev->id.revision);
	err = 0;
out:
	वापस err;
पूर्ण

अटल पूर्णांक b43legacy_probe(काष्ठा ssb_device *dev,
			 स्थिर काष्ठा ssb_device_id *id)
अणु
	काष्ठा b43legacy_wl *wl;
	पूर्णांक err;
	पूर्णांक first = 0;

	wl = ssb_get_devtypedata(dev);
	अगर (!wl) अणु
		/* Probing the first core - setup common काष्ठा b43legacy_wl */
		first = 1;
		err = b43legacy_wireless_init(dev);
		अगर (err)
			जाओ out;
		wl = ssb_get_devtypedata(dev);
		B43legacy_WARN_ON(!wl);
	पूर्ण
	err = b43legacy_one_core_attach(dev, wl);
	अगर (err)
		जाओ err_wireless_निकास;

	/* setup and start work to load firmware */
	INIT_WORK(&wl->firmware_load, b43legacy_request_firmware);
	schedule_work(&wl->firmware_load);

out:
	वापस err;

err_wireless_निकास:
	अगर (first)
		b43legacy_wireless_निकास(dev, wl);
	वापस err;
पूर्ण

अटल व्योम b43legacy_हटाओ(काष्ठा ssb_device *dev)
अणु
	काष्ठा b43legacy_wl *wl = ssb_get_devtypedata(dev);
	काष्ठा b43legacy_wldev *wldev = ssb_get_drvdata(dev);

	/* We must cancel any work here beक्रमe unरेजिस्टरing from ieee80211,
	 * as the ieee80211 unreg will destroy the workqueue. */
	cancel_work_sync(&wldev->restart_work);
	cancel_work_sync(&wl->firmware_load);
	complete(&wldev->fw_load_complete);

	B43legacy_WARN_ON(!wl);
	अगर (!wldev->fw.ucode)
		वापस;			/* शून्य अगर fw never loaded */
	अगर (wl->current_dev == wldev)
		ieee80211_unरेजिस्टर_hw(wl->hw);

	b43legacy_one_core_detach(dev);

	अगर (list_empty(&wl->devlist))
		/* Last core on the chip unरेजिस्टरed.
		 * We can destroy common काष्ठा b43legacy_wl.
		 */
		b43legacy_wireless_निकास(dev, wl);
पूर्ण

/* Perक्रमm a hardware reset. This can be called from any context. */
व्योम b43legacy_controller_restart(काष्ठा b43legacy_wldev *dev,
				  स्थिर अक्षर *reason)
अणु
	/* Must aव्योम requeueing, अगर we are in shutकरोwn. */
	अगर (b43legacy_status(dev) < B43legacy_STAT_INITIALIZED)
		वापस;
	b43legacyinfo(dev->wl, "Controller RESET (%s) ...\n", reason);
	ieee80211_queue_work(dev->wl->hw, &dev->restart_work);
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक b43legacy_suspend(काष्ठा ssb_device *dev, pm_message_t state)
अणु
	काष्ठा b43legacy_wldev *wldev = ssb_get_drvdata(dev);
	काष्ठा b43legacy_wl *wl = wldev->wl;

	b43legacydbg(wl, "Suspending...\n");

	mutex_lock(&wl->mutex);
	wldev->suspend_init_status = b43legacy_status(wldev);
	अगर (wldev->suspend_init_status >= B43legacy_STAT_STARTED)
		b43legacy_wireless_core_stop(wldev);
	अगर (wldev->suspend_init_status >= B43legacy_STAT_INITIALIZED)
		b43legacy_wireless_core_निकास(wldev);
	mutex_unlock(&wl->mutex);

	b43legacydbg(wl, "Device suspended.\n");

	वापस 0;
पूर्ण

अटल पूर्णांक b43legacy_resume(काष्ठा ssb_device *dev)
अणु
	काष्ठा b43legacy_wldev *wldev = ssb_get_drvdata(dev);
	काष्ठा b43legacy_wl *wl = wldev->wl;
	पूर्णांक err = 0;

	b43legacydbg(wl, "Resuming...\n");

	mutex_lock(&wl->mutex);
	अगर (wldev->suspend_init_status >= B43legacy_STAT_INITIALIZED) अणु
		err = b43legacy_wireless_core_init(wldev);
		अगर (err) अणु
			b43legacyerr(wl, "Resume failed at core init\n");
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (wldev->suspend_init_status >= B43legacy_STAT_STARTED) अणु
		err = b43legacy_wireless_core_start(wldev);
		अगर (err) अणु
			b43legacy_wireless_core_निकास(wldev);
			b43legacyerr(wl, "Resume failed at core start\n");
			जाओ out;
		पूर्ण
	पूर्ण

	b43legacydbg(wl, "Device resumed.\n");
out:
	mutex_unlock(&wl->mutex);
	वापस err;
पूर्ण

#अन्यथा	/* CONFIG_PM */
# define b43legacy_suspend	शून्य
# define b43legacy_resume		शून्य
#पूर्ण_अगर	/* CONFIG_PM */

अटल काष्ठा ssb_driver b43legacy_ssb_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= b43legacy_ssb_tbl,
	.probe		= b43legacy_probe,
	.हटाओ		= b43legacy_हटाओ,
	.suspend	= b43legacy_suspend,
	.resume		= b43legacy_resume,
पूर्ण;

अटल व्योम b43legacy_prपूर्णांक_driverinfo(व्योम)
अणु
	स्थिर अक्षर *feat_pci = "", *feat_leds = "",
		   *feat_pio = "", *feat_dma = "";

#अगर_घोषित CONFIG_B43LEGACY_PCI_AUTOSELECT
	feat_pci = "P";
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43LEGACY_LEDS
	feat_leds = "L";
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43LEGACY_PIO
	feat_pio = "I";
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43LEGACY_DMA
	feat_dma = "D";
#पूर्ण_अगर
	prपूर्णांकk(KERN_INFO "Broadcom 43xx-legacy driver loaded "
	       "[ Features: %s%s%s%s ]\n",
	       feat_pci, feat_leds, feat_pio, feat_dma);
पूर्ण

अटल पूर्णांक __init b43legacy_init(व्योम)
अणु
	पूर्णांक err;

	b43legacy_debugfs_init();

	err = ssb_driver_रेजिस्टर(&b43legacy_ssb_driver);
	अगर (err)
		जाओ err_dfs_निकास;

	b43legacy_prपूर्णांक_driverinfo();

	वापस err;

err_dfs_निकास:
	b43legacy_debugfs_निकास();
	वापस err;
पूर्ण

अटल व्योम __निकास b43legacy_निकास(व्योम)
अणु
	ssb_driver_unरेजिस्टर(&b43legacy_ssb_driver);
	b43legacy_debugfs_निकास();
पूर्ण

module_init(b43legacy_init)
module_निकास(b43legacy_निकास)
