<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Broadcom B43 wireless driver

  Copyright (c) 2005 Martin Langer <martin-langer@gmx.de>
  Copyright (c) 2005 Stefano Brivio <stefano.brivio@polimi.it>
  Copyright (c) 2005-2009 Michael Buesch <m@bues.ch>
  Copyright (c) 2005 Danny van Dyk <kugelfang@gentoo.org>
  Copyright (c) 2005 Andreas Jaggi <andreas.jaggi@waterwave.ch>
  Copyright (c) 2010-2011 Rafaध Miधecki <zajec5@gmail.com>

  SDIO support
  Copyright (c) 2009 Albert Herranz <albert_herranz@yahoo.es>

  Some parts of the code in this file are derived from the ipw2200
  driver  Copyright(c) 2003 - 2004 Intel Corporation.


*/

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/firmware.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/पन.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "b43.h"
#समावेश "main.h"
#समावेश "debugfs.h"
#समावेश "phy_common.h"
#समावेश "phy_g.h"
#समावेश "phy_n.h"
#समावेश "dma.h"
#समावेश "pio.h"
#समावेश "sysfs.h"
#समावेश "xmit.h"
#समावेश "lo.h"
#समावेश "sdio.h"
#समावेश <linux/mmc/sdio_func.h>

MODULE_DESCRIPTION("Broadcom B43 wireless driver");
MODULE_AUTHOR("Martin Langer");
MODULE_AUTHOR("Stefano Brivio");
MODULE_AUTHOR("Michael Buesch");
MODULE_AUTHOR("Gथँbor Stefanik");
MODULE_AUTHOR("Rafaध Miधecki");
MODULE_LICENSE("GPL");

MODULE_FIRMWARE("b43/ucode11.fw");
MODULE_FIRMWARE("b43/ucode13.fw");
MODULE_FIRMWARE("b43/ucode14.fw");
MODULE_FIRMWARE("b43/ucode15.fw");
MODULE_FIRMWARE("b43/ucode16_lp.fw");
MODULE_FIRMWARE("b43/ucode16_mimo.fw");
MODULE_FIRMWARE("b43/ucode24_lcn.fw");
MODULE_FIRMWARE("b43/ucode25_lcn.fw");
MODULE_FIRMWARE("b43/ucode25_mimo.fw");
MODULE_FIRMWARE("b43/ucode26_mimo.fw");
MODULE_FIRMWARE("b43/ucode29_mimo.fw");
MODULE_FIRMWARE("b43/ucode33_lcn40.fw");
MODULE_FIRMWARE("b43/ucode30_mimo.fw");
MODULE_FIRMWARE("b43/ucode5.fw");
MODULE_FIRMWARE("b43/ucode40.fw");
MODULE_FIRMWARE("b43/ucode42.fw");
MODULE_FIRMWARE("b43/ucode9.fw");

अटल पूर्णांक modparam_bad_frames_preempt;
module_param_named(bad_frames_preempt, modparam_bad_frames_preempt, पूर्णांक, 0444);
MODULE_PARM_DESC(bad_frames_preempt,
		 "enable(1) / disable(0) Bad Frames Preemption");

अटल अक्षर modparam_fwpostfix[16];
module_param_string(fwpostfix, modparam_fwpostfix, 16, 0444);
MODULE_PARM_DESC(fwpostfix, "Postfix for the .fw files to load.");

अटल पूर्णांक modparam_hwpctl;
module_param_named(hwpctl, modparam_hwpctl, पूर्णांक, 0444);
MODULE_PARM_DESC(hwpctl, "Enable hardware-side power control (default off)");

अटल पूर्णांक modparam_nohwcrypt;
module_param_named(nohwcrypt, modparam_nohwcrypt, पूर्णांक, 0444);
MODULE_PARM_DESC(nohwcrypt, "Disable hardware encryption.");

अटल पूर्णांक modparam_hwtkip;
module_param_named(hwtkip, modparam_hwtkip, पूर्णांक, 0444);
MODULE_PARM_DESC(hwtkip, "Enable hardware tkip.");

अटल पूर्णांक modparam_qos = 1;
module_param_named(qos, modparam_qos, पूर्णांक, 0444);
MODULE_PARM_DESC(qos, "Enable QOS support (default on)");

अटल पूर्णांक modparam_btcoex = 1;
module_param_named(btcoex, modparam_btcoex, पूर्णांक, 0444);
MODULE_PARM_DESC(btcoex, "Enable Bluetooth coexistence (default on)");

पूर्णांक b43_modparam_verbose = B43_VERBOSITY_DEFAULT;
module_param_named(verbose, b43_modparam_verbose, पूर्णांक, 0644);
MODULE_PARM_DESC(verbose, "Log message verbosity: 0=error, 1=warn, 2=info(default), 3=debug");

अटल पूर्णांक b43_modparam_pio = 0;
module_param_named(pio, b43_modparam_pio, पूर्णांक, 0644);
MODULE_PARM_DESC(pio, "Use PIO accesses by default: 0=DMA, 1=PIO");

अटल पूर्णांक modparam_allhwsupport = !IS_ENABLED(CONFIG_BRCMSMAC);
module_param_named(allhwsupport, modparam_allhwsupport, पूर्णांक, 0444);
MODULE_PARM_DESC(allhwsupport, "Enable support for all hardware (even it if overlaps with the brcmsmac driver)");

#अगर_घोषित CONFIG_B43_BCMA
अटल स्थिर काष्ठा bcma_device_id b43_bcma_tbl[] = अणु
	BCMA_CORE(BCMA_MANUF_BCM, BCMA_CORE_80211, 0x11, BCMA_ANY_CLASS),
	BCMA_CORE(BCMA_MANUF_BCM, BCMA_CORE_80211, 0x15, BCMA_ANY_CLASS),
	BCMA_CORE(BCMA_MANUF_BCM, BCMA_CORE_80211, 0x17, BCMA_ANY_CLASS),
	BCMA_CORE(BCMA_MANUF_BCM, BCMA_CORE_80211, 0x18, BCMA_ANY_CLASS),
	BCMA_CORE(BCMA_MANUF_BCM, BCMA_CORE_80211, 0x1C, BCMA_ANY_CLASS),
	BCMA_CORE(BCMA_MANUF_BCM, BCMA_CORE_80211, 0x1D, BCMA_ANY_CLASS),
	BCMA_CORE(BCMA_MANUF_BCM, BCMA_CORE_80211, 0x1E, BCMA_ANY_CLASS),
	BCMA_CORE(BCMA_MANUF_BCM, BCMA_CORE_80211, 0x28, BCMA_ANY_CLASS),
	BCMA_CORE(BCMA_MANUF_BCM, BCMA_CORE_80211, 0x2A, BCMA_ANY_CLASS),
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(bcma, b43_bcma_tbl);
#पूर्ण_अगर

#अगर_घोषित CONFIG_B43_SSB
अटल स्थिर काष्ठा ssb_device_id b43_ssb_tbl[] = अणु
	SSB_DEVICE(SSB_VENDOR_BROADCOM, SSB_DEV_80211, 5),
	SSB_DEVICE(SSB_VENDOR_BROADCOM, SSB_DEV_80211, 6),
	SSB_DEVICE(SSB_VENDOR_BROADCOM, SSB_DEV_80211, 7),
	SSB_DEVICE(SSB_VENDOR_BROADCOM, SSB_DEV_80211, 9),
	SSB_DEVICE(SSB_VENDOR_BROADCOM, SSB_DEV_80211, 10),
	SSB_DEVICE(SSB_VENDOR_BROADCOM, SSB_DEV_80211, 11),
	SSB_DEVICE(SSB_VENDOR_BROADCOM, SSB_DEV_80211, 12),
	SSB_DEVICE(SSB_VENDOR_BROADCOM, SSB_DEV_80211, 13),
	SSB_DEVICE(SSB_VENDOR_BROADCOM, SSB_DEV_80211, 15),
	SSB_DEVICE(SSB_VENDOR_BROADCOM, SSB_DEV_80211, 16),
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(ssb, b43_ssb_tbl);
#पूर्ण_अगर

/* Channel and ratetables are shared क्रम all devices.
 * They can't be स्थिर, because ieee80211 माला_दो some precalculated
 * data in there. This data is the same क्रम all devices, so we करोn't
 * get concurrency issues */
#घोषणा RATETAB_ENT(_rateid, _flags) \
	अणु								\
		.bitrate	= B43_RATE_TO_BASE100KBPS(_rateid),	\
		.hw_value	= (_rateid),				\
		.flags		= (_flags),				\
	पूर्ण

/*
 * NOTE: When changing this, sync with xmit.c's
 *	 b43_plcp_get_bitrate_idx_* functions!
 */
अटल काष्ठा ieee80211_rate __b43_ratetable[] = अणु
	RATETAB_ENT(B43_CCK_RATE_1MB, 0),
	RATETAB_ENT(B43_CCK_RATE_2MB, IEEE80211_RATE_SHORT_PREAMBLE),
	RATETAB_ENT(B43_CCK_RATE_5MB, IEEE80211_RATE_SHORT_PREAMBLE),
	RATETAB_ENT(B43_CCK_RATE_11MB, IEEE80211_RATE_SHORT_PREAMBLE),
	RATETAB_ENT(B43_OFDM_RATE_6MB, 0),
	RATETAB_ENT(B43_OFDM_RATE_9MB, 0),
	RATETAB_ENT(B43_OFDM_RATE_12MB, 0),
	RATETAB_ENT(B43_OFDM_RATE_18MB, 0),
	RATETAB_ENT(B43_OFDM_RATE_24MB, 0),
	RATETAB_ENT(B43_OFDM_RATE_36MB, 0),
	RATETAB_ENT(B43_OFDM_RATE_48MB, 0),
	RATETAB_ENT(B43_OFDM_RATE_54MB, 0),
पूर्ण;

#घोषणा b43_a_ratetable		(__b43_ratetable + 4)
#घोषणा b43_a_ratetable_size	8
#घोषणा b43_b_ratetable		(__b43_ratetable + 0)
#घोषणा b43_b_ratetable_size	4
#घोषणा b43_g_ratetable		(__b43_ratetable + 0)
#घोषणा b43_g_ratetable_size	12

#घोषणा CHAN2G(_channel, _freq, _flags) अणु			\
	.band			= NL80211_BAND_2GHZ,		\
	.center_freq		= (_freq),			\
	.hw_value		= (_channel),			\
	.flags			= (_flags),			\
	.max_antenna_gain	= 0,				\
	.max_घातer		= 30,				\
पूर्ण
अटल काष्ठा ieee80211_channel b43_2ghz_chantable[] = अणु
	CHAN2G(1, 2412, 0),
	CHAN2G(2, 2417, 0),
	CHAN2G(3, 2422, 0),
	CHAN2G(4, 2427, 0),
	CHAN2G(5, 2432, 0),
	CHAN2G(6, 2437, 0),
	CHAN2G(7, 2442, 0),
	CHAN2G(8, 2447, 0),
	CHAN2G(9, 2452, 0),
	CHAN2G(10, 2457, 0),
	CHAN2G(11, 2462, 0),
	CHAN2G(12, 2467, 0),
	CHAN2G(13, 2472, 0),
	CHAN2G(14, 2484, 0),
पूर्ण;

/* No support क्रम the last 3 channels (12, 13, 14) */
#घोषणा b43_2ghz_chantable_limited_size		11
#अघोषित CHAN2G

#घोषणा CHAN4G(_channel, _flags) अणु				\
	.band			= NL80211_BAND_5GHZ,		\
	.center_freq		= 4000 + (5 * (_channel)),	\
	.hw_value		= (_channel),			\
	.flags			= (_flags),			\
	.max_antenna_gain	= 0,				\
	.max_घातer		= 30,				\
पूर्ण
#घोषणा CHAN5G(_channel, _flags) अणु				\
	.band			= NL80211_BAND_5GHZ,		\
	.center_freq		= 5000 + (5 * (_channel)),	\
	.hw_value		= (_channel),			\
	.flags			= (_flags),			\
	.max_antenna_gain	= 0,				\
	.max_घातer		= 30,				\
पूर्ण
अटल काष्ठा ieee80211_channel b43_5ghz_nphy_chantable[] = अणु
	CHAN4G(184, 0),		CHAN4G(186, 0),
	CHAN4G(188, 0),		CHAN4G(190, 0),
	CHAN4G(192, 0),		CHAN4G(194, 0),
	CHAN4G(196, 0),		CHAN4G(198, 0),
	CHAN4G(200, 0),		CHAN4G(202, 0),
	CHAN4G(204, 0),		CHAN4G(206, 0),
	CHAN4G(208, 0),		CHAN4G(210, 0),
	CHAN4G(212, 0),		CHAN4G(214, 0),
	CHAN4G(216, 0),		CHAN4G(218, 0),
	CHAN4G(220, 0),		CHAN4G(222, 0),
	CHAN4G(224, 0),		CHAN4G(226, 0),
	CHAN4G(228, 0),
	CHAN5G(32, 0),		CHAN5G(34, 0),
	CHAN5G(36, 0),		CHAN5G(38, 0),
	CHAN5G(40, 0),		CHAN5G(42, 0),
	CHAN5G(44, 0),		CHAN5G(46, 0),
	CHAN5G(48, 0),		CHAN5G(50, 0),
	CHAN5G(52, 0),		CHAN5G(54, 0),
	CHAN5G(56, 0),		CHAN5G(58, 0),
	CHAN5G(60, 0),		CHAN5G(62, 0),
	CHAN5G(64, 0),		CHAN5G(66, 0),
	CHAN5G(68, 0),		CHAN5G(70, 0),
	CHAN5G(72, 0),		CHAN5G(74, 0),
	CHAN5G(76, 0),		CHAN5G(78, 0),
	CHAN5G(80, 0),		CHAN5G(82, 0),
	CHAN5G(84, 0),		CHAN5G(86, 0),
	CHAN5G(88, 0),		CHAN5G(90, 0),
	CHAN5G(92, 0),		CHAN5G(94, 0),
	CHAN5G(96, 0),		CHAN5G(98, 0),
	CHAN5G(100, 0),		CHAN5G(102, 0),
	CHAN5G(104, 0),		CHAN5G(106, 0),
	CHAN5G(108, 0),		CHAN5G(110, 0),
	CHAN5G(112, 0),		CHAN5G(114, 0),
	CHAN5G(116, 0),		CHAN5G(118, 0),
	CHAN5G(120, 0),		CHAN5G(122, 0),
	CHAN5G(124, 0),		CHAN5G(126, 0),
	CHAN5G(128, 0),		CHAN5G(130, 0),
	CHAN5G(132, 0),		CHAN5G(134, 0),
	CHAN5G(136, 0),		CHAN5G(138, 0),
	CHAN5G(140, 0),		CHAN5G(142, 0),
	CHAN5G(144, 0),		CHAN5G(145, 0),
	CHAN5G(146, 0),		CHAN5G(147, 0),
	CHAN5G(148, 0),		CHAN5G(149, 0),
	CHAN5G(150, 0),		CHAN5G(151, 0),
	CHAN5G(152, 0),		CHAN5G(153, 0),
	CHAN5G(154, 0),		CHAN5G(155, 0),
	CHAN5G(156, 0),		CHAN5G(157, 0),
	CHAN5G(158, 0),		CHAN5G(159, 0),
	CHAN5G(160, 0),		CHAN5G(161, 0),
	CHAN5G(162, 0),		CHAN5G(163, 0),
	CHAN5G(164, 0),		CHAN5G(165, 0),
	CHAN5G(166, 0),		CHAN5G(168, 0),
	CHAN5G(170, 0),		CHAN5G(172, 0),
	CHAN5G(174, 0),		CHAN5G(176, 0),
	CHAN5G(178, 0),		CHAN5G(180, 0),
	CHAN5G(182, 0),
पूर्ण;

अटल काष्ठा ieee80211_channel b43_5ghz_nphy_chantable_limited[] = अणु
	CHAN5G(36, 0),		CHAN5G(40, 0),
	CHAN5G(44, 0),		CHAN5G(48, 0),
	CHAN5G(149, 0),		CHAN5G(153, 0),
	CHAN5G(157, 0),		CHAN5G(161, 0),
	CHAN5G(165, 0),
पूर्ण;

अटल काष्ठा ieee80211_channel b43_5ghz_aphy_chantable[] = अणु
	CHAN5G(34, 0),		CHAN5G(36, 0),
	CHAN5G(38, 0),		CHAN5G(40, 0),
	CHAN5G(42, 0),		CHAN5G(44, 0),
	CHAN5G(46, 0),		CHAN5G(48, 0),
	CHAN5G(52, 0),		CHAN5G(56, 0),
	CHAN5G(60, 0),		CHAN5G(64, 0),
	CHAN5G(100, 0),		CHAN5G(104, 0),
	CHAN5G(108, 0),		CHAN5G(112, 0),
	CHAN5G(116, 0),		CHAN5G(120, 0),
	CHAN5G(124, 0),		CHAN5G(128, 0),
	CHAN5G(132, 0),		CHAN5G(136, 0),
	CHAN5G(140, 0),		CHAN5G(149, 0),
	CHAN5G(153, 0),		CHAN5G(157, 0),
	CHAN5G(161, 0),		CHAN5G(165, 0),
	CHAN5G(184, 0),		CHAN5G(188, 0),
	CHAN5G(192, 0),		CHAN5G(196, 0),
	CHAN5G(200, 0),		CHAN5G(204, 0),
	CHAN5G(208, 0),		CHAN5G(212, 0),
	CHAN5G(216, 0),
पूर्ण;
#अघोषित CHAN4G
#अघोषित CHAN5G

अटल काष्ठा ieee80211_supported_band b43_band_5GHz_nphy = अणु
	.band		= NL80211_BAND_5GHZ,
	.channels	= b43_5ghz_nphy_chantable,
	.n_channels	= ARRAY_SIZE(b43_5ghz_nphy_chantable),
	.bitrates	= b43_a_ratetable,
	.n_bitrates	= b43_a_ratetable_size,
पूर्ण;

अटल काष्ठा ieee80211_supported_band b43_band_5GHz_nphy_limited = अणु
	.band		= NL80211_BAND_5GHZ,
	.channels	= b43_5ghz_nphy_chantable_limited,
	.n_channels	= ARRAY_SIZE(b43_5ghz_nphy_chantable_limited),
	.bitrates	= b43_a_ratetable,
	.n_bitrates	= b43_a_ratetable_size,
पूर्ण;

अटल काष्ठा ieee80211_supported_band b43_band_5GHz_aphy = अणु
	.band		= NL80211_BAND_5GHZ,
	.channels	= b43_5ghz_aphy_chantable,
	.n_channels	= ARRAY_SIZE(b43_5ghz_aphy_chantable),
	.bitrates	= b43_a_ratetable,
	.n_bitrates	= b43_a_ratetable_size,
पूर्ण;

अटल काष्ठा ieee80211_supported_band b43_band_2GHz = अणु
	.band		= NL80211_BAND_2GHZ,
	.channels	= b43_2ghz_chantable,
	.n_channels	= ARRAY_SIZE(b43_2ghz_chantable),
	.bitrates	= b43_g_ratetable,
	.n_bitrates	= b43_g_ratetable_size,
पूर्ण;

अटल काष्ठा ieee80211_supported_band b43_band_2ghz_limited = अणु
	.band		= NL80211_BAND_2GHZ,
	.channels	= b43_2ghz_chantable,
	.n_channels	= b43_2ghz_chantable_limited_size,
	.bitrates	= b43_g_ratetable,
	.n_bitrates	= b43_g_ratetable_size,
पूर्ण;

अटल व्योम b43_wireless_core_निकास(काष्ठा b43_wldev *dev);
अटल पूर्णांक b43_wireless_core_init(काष्ठा b43_wldev *dev);
अटल काष्ठा b43_wldev * b43_wireless_core_stop(काष्ठा b43_wldev *dev);
अटल पूर्णांक b43_wireless_core_start(काष्ठा b43_wldev *dev);
अटल व्योम b43_op_bss_info_changed(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_bss_conf *conf,
				    u32 changed);

अटल पूर्णांक b43_ratelimit(काष्ठा b43_wl *wl)
अणु
	अगर (!wl || !wl->current_dev)
		वापस 1;
	अगर (b43_status(wl->current_dev) < B43_STAT_STARTED)
		वापस 1;
	/* We are up and running.
	 * Ratelimit the messages to aव्योम DoS over the net. */
	वापस net_ratelimit();
पूर्ण

व्योम b43info(काष्ठा b43_wl *wl, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (b43_modparam_verbose < B43_VERBOSITY_INFO)
		वापस;
	अगर (!b43_ratelimit(wl))
		वापस;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	prपूर्णांकk(KERN_INFO "b43-%s: %pV",
	       (wl && wl->hw) ? wiphy_name(wl->hw->wiphy) : "wlan", &vaf);

	बहु_पूर्ण(args);
पूर्ण

व्योम b43err(काष्ठा b43_wl *wl, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (b43_modparam_verbose < B43_VERBOSITY_ERROR)
		वापस;
	अगर (!b43_ratelimit(wl))
		वापस;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	prपूर्णांकk(KERN_ERR "b43-%s ERROR: %pV",
	       (wl && wl->hw) ? wiphy_name(wl->hw->wiphy) : "wlan", &vaf);

	बहु_पूर्ण(args);
पूर्ण

व्योम b43warn(काष्ठा b43_wl *wl, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (b43_modparam_verbose < B43_VERBOSITY_WARN)
		वापस;
	अगर (!b43_ratelimit(wl))
		वापस;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	prपूर्णांकk(KERN_WARNING "b43-%s warning: %pV",
	       (wl && wl->hw) ? wiphy_name(wl->hw->wiphy) : "wlan", &vaf);

	बहु_पूर्ण(args);
पूर्ण

व्योम b43dbg(काष्ठा b43_wl *wl, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (b43_modparam_verbose < B43_VERBOSITY_DEBUG)
		वापस;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	prपूर्णांकk(KERN_DEBUG "b43-%s debug: %pV",
	       (wl && wl->hw) ? wiphy_name(wl->hw->wiphy) : "wlan", &vaf);

	बहु_पूर्ण(args);
पूर्ण

अटल व्योम b43_ram_ग_लिखो(काष्ठा b43_wldev *dev, u16 offset, u32 val)
अणु
	u32 macctl;

	B43_WARN_ON(offset % 4 != 0);

	macctl = b43_पढ़ो32(dev, B43_MMIO_MACCTL);
	अगर (macctl & B43_MACCTL_BE)
		val = swab32(val);

	b43_ग_लिखो32(dev, B43_MMIO_RAM_CONTROL, offset);
	b43_ग_लिखो32(dev, B43_MMIO_RAM_DATA, val);
पूर्ण

अटल अंतरभूत व्योम b43_shm_control_word(काष्ठा b43_wldev *dev,
					u16 routing, u16 offset)
अणु
	u32 control;

	/* "offset" is the WORD offset. */
	control = routing;
	control <<= 16;
	control |= offset;
	b43_ग_लिखो32(dev, B43_MMIO_SHM_CONTROL, control);
पूर्ण

u32 b43_shm_पढ़ो32(काष्ठा b43_wldev *dev, u16 routing, u16 offset)
अणु
	u32 ret;

	अगर (routing == B43_SHM_SHARED) अणु
		B43_WARN_ON(offset & 0x0001);
		अगर (offset & 0x0003) अणु
			/* Unaligned access */
			b43_shm_control_word(dev, routing, offset >> 2);
			ret = b43_पढ़ो16(dev, B43_MMIO_SHM_DATA_UNALIGNED);
			b43_shm_control_word(dev, routing, (offset >> 2) + 1);
			ret |= ((u32)b43_पढ़ो16(dev, B43_MMIO_SHM_DATA)) << 16;

			जाओ out;
		पूर्ण
		offset >>= 2;
	पूर्ण
	b43_shm_control_word(dev, routing, offset);
	ret = b43_पढ़ो32(dev, B43_MMIO_SHM_DATA);
out:
	वापस ret;
पूर्ण

u16 b43_shm_पढ़ो16(काष्ठा b43_wldev *dev, u16 routing, u16 offset)
अणु
	u16 ret;

	अगर (routing == B43_SHM_SHARED) अणु
		B43_WARN_ON(offset & 0x0001);
		अगर (offset & 0x0003) अणु
			/* Unaligned access */
			b43_shm_control_word(dev, routing, offset >> 2);
			ret = b43_पढ़ो16(dev, B43_MMIO_SHM_DATA_UNALIGNED);

			जाओ out;
		पूर्ण
		offset >>= 2;
	पूर्ण
	b43_shm_control_word(dev, routing, offset);
	ret = b43_पढ़ो16(dev, B43_MMIO_SHM_DATA);
out:
	वापस ret;
पूर्ण

व्योम b43_shm_ग_लिखो32(काष्ठा b43_wldev *dev, u16 routing, u16 offset, u32 value)
अणु
	अगर (routing == B43_SHM_SHARED) अणु
		B43_WARN_ON(offset & 0x0001);
		अगर (offset & 0x0003) अणु
			/* Unaligned access */
			b43_shm_control_word(dev, routing, offset >> 2);
			b43_ग_लिखो16(dev, B43_MMIO_SHM_DATA_UNALIGNED,
				    value & 0xFFFF);
			b43_shm_control_word(dev, routing, (offset >> 2) + 1);
			b43_ग_लिखो16(dev, B43_MMIO_SHM_DATA,
				    (value >> 16) & 0xFFFF);
			वापस;
		पूर्ण
		offset >>= 2;
	पूर्ण
	b43_shm_control_word(dev, routing, offset);
	b43_ग_लिखो32(dev, B43_MMIO_SHM_DATA, value);
पूर्ण

व्योम b43_shm_ग_लिखो16(काष्ठा b43_wldev *dev, u16 routing, u16 offset, u16 value)
अणु
	अगर (routing == B43_SHM_SHARED) अणु
		B43_WARN_ON(offset & 0x0001);
		अगर (offset & 0x0003) अणु
			/* Unaligned access */
			b43_shm_control_word(dev, routing, offset >> 2);
			b43_ग_लिखो16(dev, B43_MMIO_SHM_DATA_UNALIGNED, value);
			वापस;
		पूर्ण
		offset >>= 2;
	पूर्ण
	b43_shm_control_word(dev, routing, offset);
	b43_ग_लिखो16(dev, B43_MMIO_SHM_DATA, value);
पूर्ण

/* Read HostFlags */
u64 b43_hf_पढ़ो(काष्ठा b43_wldev *dev)
अणु
	u64 ret;

	ret = b43_shm_पढ़ो16(dev, B43_SHM_SHARED, B43_SHM_SH_HOSTF3);
	ret <<= 16;
	ret |= b43_shm_पढ़ो16(dev, B43_SHM_SHARED, B43_SHM_SH_HOSTF2);
	ret <<= 16;
	ret |= b43_shm_पढ़ो16(dev, B43_SHM_SHARED, B43_SHM_SH_HOSTF1);

	वापस ret;
पूर्ण

/* Write HostFlags */
व्योम b43_hf_ग_लिखो(काष्ठा b43_wldev *dev, u64 value)
अणु
	u16 lo, mi, hi;

	lo = (value & 0x00000000FFFFULL);
	mi = (value & 0x0000FFFF0000ULL) >> 16;
	hi = (value & 0xFFFF00000000ULL) >> 32;
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_HOSTF1, lo);
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_HOSTF2, mi);
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_HOSTF3, hi);
पूर्ण

/* Read the firmware capabilities biपंचांगask (Opensource firmware only) */
अटल u16 b43_fwcapa_पढ़ो(काष्ठा b43_wldev *dev)
अणु
	B43_WARN_ON(!dev->fw.खोलोsource);
	वापस b43_shm_पढ़ो16(dev, B43_SHM_SHARED, B43_SHM_SH_FWCAPA);
पूर्ण

व्योम b43_tsf_पढ़ो(काष्ठा b43_wldev *dev, u64 *tsf)
अणु
	u32 low, high;

	B43_WARN_ON(dev->dev->core_rev < 3);

	/* The hardware guarantees us an atomic पढ़ो, अगर we
	 * पढ़ो the low रेजिस्टर first. */
	low = b43_पढ़ो32(dev, B43_MMIO_REV3PLUS_TSF_LOW);
	high = b43_पढ़ो32(dev, B43_MMIO_REV3PLUS_TSF_HIGH);

	*tsf = high;
	*tsf <<= 32;
	*tsf |= low;
पूर्ण

अटल व्योम b43_समय_lock(काष्ठा b43_wldev *dev)
अणु
	b43_maskset32(dev, B43_MMIO_MACCTL, ~0, B43_MACCTL_TBTTHOLD);
	/* Commit the ग_लिखो */
	b43_पढ़ो32(dev, B43_MMIO_MACCTL);
पूर्ण

अटल व्योम b43_समय_unlock(काष्ठा b43_wldev *dev)
अणु
	b43_maskset32(dev, B43_MMIO_MACCTL, ~B43_MACCTL_TBTTHOLD, 0);
	/* Commit the ग_लिखो */
	b43_पढ़ो32(dev, B43_MMIO_MACCTL);
पूर्ण

अटल व्योम b43_tsf_ग_लिखो_locked(काष्ठा b43_wldev *dev, u64 tsf)
अणु
	u32 low, high;

	B43_WARN_ON(dev->dev->core_rev < 3);

	low = tsf;
	high = (tsf >> 32);
	/* The hardware guarantees us an atomic ग_लिखो, अगर we
	 * ग_लिखो the low रेजिस्टर first. */
	b43_ग_लिखो32(dev, B43_MMIO_REV3PLUS_TSF_LOW, low);
	b43_ग_लिखो32(dev, B43_MMIO_REV3PLUS_TSF_HIGH, high);
पूर्ण

व्योम b43_tsf_ग_लिखो(काष्ठा b43_wldev *dev, u64 tsf)
अणु
	b43_समय_lock(dev);
	b43_tsf_ग_लिखो_locked(dev, tsf);
	b43_समय_unlock(dev);
पूर्ण

अटल
व्योम b43_macfilter_set(काष्ठा b43_wldev *dev, u16 offset, स्थिर u8 *mac)
अणु
	अटल स्थिर u8 zero_addr[ETH_ALEN] = अणु 0 पूर्ण;
	u16 data;

	अगर (!mac)
		mac = zero_addr;

	offset |= 0x0020;
	b43_ग_लिखो16(dev, B43_MMIO_MACFILTER_CONTROL, offset);

	data = mac[0];
	data |= mac[1] << 8;
	b43_ग_लिखो16(dev, B43_MMIO_MACFILTER_DATA, data);
	data = mac[2];
	data |= mac[3] << 8;
	b43_ग_लिखो16(dev, B43_MMIO_MACFILTER_DATA, data);
	data = mac[4];
	data |= mac[5] << 8;
	b43_ग_लिखो16(dev, B43_MMIO_MACFILTER_DATA, data);
पूर्ण

अटल व्योम b43_ग_लिखो_mac_bssid_ढाँचाs(काष्ठा b43_wldev *dev)
अणु
	स्थिर u8 *mac;
	स्थिर u8 *bssid;
	u8 mac_bssid[ETH_ALEN * 2];
	पूर्णांक i;
	u32 पंचांगp;

	bssid = dev->wl->bssid;
	mac = dev->wl->mac_addr;

	b43_macfilter_set(dev, B43_MACFILTER_BSSID, bssid);

	स_नकल(mac_bssid, mac, ETH_ALEN);
	स_नकल(mac_bssid + ETH_ALEN, bssid, ETH_ALEN);

	/* Write our MAC address and BSSID to ढाँचा ram */
	क्रम (i = 0; i < ARRAY_SIZE(mac_bssid); i += माप(u32)) अणु
		पंचांगp = (u32) (mac_bssid[i + 0]);
		पंचांगp |= (u32) (mac_bssid[i + 1]) << 8;
		पंचांगp |= (u32) (mac_bssid[i + 2]) << 16;
		पंचांगp |= (u32) (mac_bssid[i + 3]) << 24;
		b43_ram_ग_लिखो(dev, 0x20 + i, पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम b43_upload_card_macaddress(काष्ठा b43_wldev *dev)
अणु
	b43_ग_लिखो_mac_bssid_ढाँचाs(dev);
	b43_macfilter_set(dev, B43_MACFILTER_SELF, dev->wl->mac_addr);
पूर्ण

अटल व्योम b43_set_slot_समय(काष्ठा b43_wldev *dev, u16 slot_समय)
अणु
	/* slot_समय is in usec. */
	/* This test used to निकास क्रम all but a G PHY. */
	अगर (b43_current_band(dev->wl) == NL80211_BAND_5GHZ)
		वापस;
	b43_ग_लिखो16(dev, B43_MMIO_IFSSLOT, 510 + slot_समय);
	/* Shared memory location 0x0010 is the slot समय and should be
	 * set to slot_समय; however, this रेजिस्टर is initially 0 and changing
	 * the value adversely affects the transmit rate क्रम BCM4311
	 * devices. Until this behavior is unterstood, delete this step
	 *
	 * b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, 0x0010, slot_समय);
	 */
पूर्ण

अटल व्योम b43_लघु_slot_timing_enable(काष्ठा b43_wldev *dev)
अणु
	b43_set_slot_समय(dev, 9);
पूर्ण

अटल व्योम b43_लघु_slot_timing_disable(काष्ठा b43_wldev *dev)
अणु
	b43_set_slot_समय(dev, 20);
पूर्ण

/* DummyTransmission function, as करोcumented on
 * https://bcm-v4.sipsolutions.net/802.11/DummyTransmission
 */
व्योम b43_dummy_transmission(काष्ठा b43_wldev *dev, bool ofdm, bool pa_on)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	अचिन्हित पूर्णांक i, max_loop;
	u16 value;
	u32 buffer[5] = अणु
		0x00000000,
		0x00D40000,
		0x00000000,
		0x01000000,
		0x00000000,
	पूर्ण;

	अगर (ofdm) अणु
		max_loop = 0x1E;
		buffer[0] = 0x000201CC;
	पूर्ण अन्यथा अणु
		max_loop = 0xFA;
		buffer[0] = 0x000B846E;
	पूर्ण

	क्रम (i = 0; i < 5; i++)
		b43_ram_ग_लिखो(dev, i * 4, buffer[i]);

	b43_ग_लिखो16(dev, B43_MMIO_XMTSEL, 0x0000);

	अगर (dev->dev->core_rev < 11)
		b43_ग_लिखो16(dev, B43_MMIO_WEPCTL, 0x0000);
	अन्यथा
		b43_ग_लिखो16(dev, B43_MMIO_WEPCTL, 0x0100);

	value = (ofdm ? 0x41 : 0x40);
	b43_ग_लिखो16(dev, B43_MMIO_TXE0_PHYCTL, value);
	अगर (phy->type == B43_PHYTYPE_N || phy->type == B43_PHYTYPE_LP ||
	    phy->type == B43_PHYTYPE_LCN)
		b43_ग_लिखो16(dev, B43_MMIO_TXE0_PHYCTL1, 0x1A02);

	b43_ग_लिखो16(dev, B43_MMIO_TXE0_WM_0, 0x0000);
	b43_ग_लिखो16(dev, B43_MMIO_TXE0_WM_1, 0x0000);

	b43_ग_लिखो16(dev, B43_MMIO_XMTTPLATETXPTR, 0x0000);
	b43_ग_लिखो16(dev, B43_MMIO_XMTTXCNT, 0x0014);
	b43_ग_लिखो16(dev, B43_MMIO_XMTSEL, 0x0826);
	b43_ग_लिखो16(dev, B43_MMIO_TXE0_CTL, 0x0000);

	अगर (!pa_on && phy->type == B43_PHYTYPE_N) अणु
		; /*b43_nphy_pa_override(dev, false) */
	पूर्ण

	चयन (phy->type) अणु
	हाल B43_PHYTYPE_N:
	हाल B43_PHYTYPE_LCN:
		b43_ग_लिखो16(dev, B43_MMIO_TXE0_AUX, 0x00D0);
		अवरोध;
	हाल B43_PHYTYPE_LP:
		b43_ग_लिखो16(dev, B43_MMIO_TXE0_AUX, 0x0050);
		अवरोध;
	शेष:
		b43_ग_लिखो16(dev, B43_MMIO_TXE0_AUX, 0x0030);
	पूर्ण
	b43_पढ़ो16(dev, B43_MMIO_TXE0_AUX);

	अगर (phy->radio_ver == 0x2050 && phy->radio_rev <= 0x5)
		b43_radio_ग_लिखो16(dev, 0x0051, 0x0017);
	क्रम (i = 0x00; i < max_loop; i++) अणु
		value = b43_पढ़ो16(dev, B43_MMIO_TXE0_STATUS);
		अगर (value & 0x0080)
			अवरोध;
		udelay(10);
	पूर्ण
	क्रम (i = 0x00; i < 0x0A; i++) अणु
		value = b43_पढ़ो16(dev, B43_MMIO_TXE0_STATUS);
		अगर (value & 0x0400)
			अवरोध;
		udelay(10);
	पूर्ण
	क्रम (i = 0x00; i < 0x19; i++) अणु
		value = b43_पढ़ो16(dev, B43_MMIO_IFSSTAT);
		अगर (!(value & 0x0100))
			अवरोध;
		udelay(10);
	पूर्ण
	अगर (phy->radio_ver == 0x2050 && phy->radio_rev <= 0x5)
		b43_radio_ग_लिखो16(dev, 0x0051, 0x0037);
पूर्ण

अटल व्योम key_ग_लिखो(काष्ठा b43_wldev *dev,
		      u8 index, u8 algorithm, स्थिर u8 *key)
अणु
	अचिन्हित पूर्णांक i;
	u32 offset;
	u16 value;
	u16 kidx;

	/* Key index/algo block */
	kidx = b43_kidx_to_fw(dev, index);
	value = ((kidx << 4) | algorithm);
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED,
			B43_SHM_SH_KEYIDXBLOCK + (kidx * 2), value);

	/* Write the key to the Key Table Poपूर्णांकer offset */
	offset = dev->ktp + (index * B43_SEC_KEYSIZE);
	क्रम (i = 0; i < B43_SEC_KEYSIZE; i += 2) अणु
		value = key[i];
		value |= (u16) (key[i + 1]) << 8;
		b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, offset + i, value);
	पूर्ण
पूर्ण

अटल व्योम keymac_ग_लिखो(काष्ठा b43_wldev *dev, u8 index, स्थिर u8 *addr)
अणु
	u32 addrपंचांगp[2] = अणु 0, 0, पूर्ण;
	u8 pairwise_keys_start = B43_NR_GROUP_KEYS * 2;

	अगर (b43_new_kidx_api(dev))
		pairwise_keys_start = B43_NR_GROUP_KEYS;

	B43_WARN_ON(index < pairwise_keys_start);
	/* We have four शेष TX keys and possibly four शेष RX keys.
	 * Physical mac 0 is mapped to physical key 4 or 8, depending
	 * on the firmware version.
	 * So we must adjust the index here.
	 */
	index -= pairwise_keys_start;
	B43_WARN_ON(index >= B43_NR_PAIRWISE_KEYS);

	अगर (addr) अणु
		addrपंचांगp[0] = addr[0];
		addrपंचांगp[0] |= ((u32) (addr[1]) << 8);
		addrपंचांगp[0] |= ((u32) (addr[2]) << 16);
		addrपंचांगp[0] |= ((u32) (addr[3]) << 24);
		addrपंचांगp[1] = addr[4];
		addrपंचांगp[1] |= ((u32) (addr[5]) << 8);
	पूर्ण

	/* Receive match transmitter address (RCMTA) mechanism */
	b43_shm_ग_लिखो32(dev, B43_SHM_RCMTA,
			(index * 2) + 0, addrपंचांगp[0]);
	b43_shm_ग_लिखो16(dev, B43_SHM_RCMTA,
			(index * 2) + 1, addrपंचांगp[1]);
पूर्ण

/* The ucode will use phase1 key with TEK key to decrypt rx packets.
 * When a packet is received, the iv32 is checked.
 * - अगर it करोesn't the packet is वापसed without modअगरication (and software
 *   decryption can be करोne). That's what happen when iv16 wrap.
 * - अगर it करोes, the rc4 key is computed, and decryption is tried.
 *   Either it will success and B43_RX_MAC_DEC is वापसed,
 *   either it fails and B43_RX_MAC_DEC|B43_RX_MAC_DECERR is वापसed
 *   and the packet is not usable (it got modअगरied by the ucode).
 * So in order to never have B43_RX_MAC_DECERR, we should provide
 * a iv32 and phase1key that match. Because we drop packets in हाल of
 * B43_RX_MAC_DECERR, अगर we have a correct iv32 but a wrong phase1key, all
 * packets will be lost without higher layer knowing (ie no resync possible
 * until next wrap).
 *
 * NOTE : this should support 50 key like RCMTA because
 * (B43_SHM_SH_KEYIDXBLOCK - B43_SHM_SH_TKIPTSCTTAK)/14 = 50
 */
अटल व्योम rx_tkip_phase1_ग_लिखो(काष्ठा b43_wldev *dev, u8 index, u32 iv32,
		u16 *phase1key)
अणु
	अचिन्हित पूर्णांक i;
	u32 offset;
	u8 pairwise_keys_start = B43_NR_GROUP_KEYS * 2;

	अगर (!modparam_hwtkip)
		वापस;

	अगर (b43_new_kidx_api(dev))
		pairwise_keys_start = B43_NR_GROUP_KEYS;

	B43_WARN_ON(index < pairwise_keys_start);
	/* We have four शेष TX keys and possibly four शेष RX keys.
	 * Physical mac 0 is mapped to physical key 4 or 8, depending
	 * on the firmware version.
	 * So we must adjust the index here.
	 */
	index -= pairwise_keys_start;
	B43_WARN_ON(index >= B43_NR_PAIRWISE_KEYS);

	अगर (b43_debug(dev, B43_DBG_KEYS)) अणु
		b43dbg(dev->wl, "rx_tkip_phase1_write : idx 0x%x, iv32 0x%x\n",
				index, iv32);
	पूर्ण
	/* Write the key to the  RX tkip shared mem */
	offset = B43_SHM_SH_TKIPTSCTTAK + index * (10 + 4);
	क्रम (i = 0; i < 10; i += 2) अणु
		b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, offset + i,
				phase1key ? phase1key[i / 2] : 0);
	पूर्ण
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, offset + i, iv32);
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, offset + i + 2, iv32 >> 16);
पूर्ण

अटल व्योम b43_op_update_tkip_key(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर,
				   काष्ठा ieee80211_key_conf *keyconf,
				   काष्ठा ieee80211_sta *sta,
				   u32 iv32, u16 *phase1key)
अणु
	काष्ठा b43_wl *wl = hw_to_b43_wl(hw);
	काष्ठा b43_wldev *dev;
	पूर्णांक index = keyconf->hw_key_idx;

	अगर (B43_WARN_ON(!modparam_hwtkip))
		वापस;

	/* This is only called from the RX path through mac80211, where
	 * our mutex is alपढ़ोy locked. */
	B43_WARN_ON(!mutex_is_locked(&wl->mutex));
	dev = wl->current_dev;
	B43_WARN_ON(!dev || b43_status(dev) < B43_STAT_INITIALIZED);

	keymac_ग_लिखो(dev, index, शून्य);	/* First zero out mac to aव्योम race */

	rx_tkip_phase1_ग_लिखो(dev, index, iv32, phase1key);
	/* only pairwise TKIP keys are supported right now */
	अगर (WARN_ON(!sta))
		वापस;
	keymac_ग_लिखो(dev, index, sta->addr);
पूर्ण

अटल व्योम करो_key_ग_लिखो(काष्ठा b43_wldev *dev,
			 u8 index, u8 algorithm,
			 स्थिर u8 *key, माप_प्रकार key_len, स्थिर u8 *mac_addr)
अणु
	u8 buf[B43_SEC_KEYSIZE] = अणु 0, पूर्ण;
	u8 pairwise_keys_start = B43_NR_GROUP_KEYS * 2;

	अगर (b43_new_kidx_api(dev))
		pairwise_keys_start = B43_NR_GROUP_KEYS;

	B43_WARN_ON(index >= ARRAY_SIZE(dev->key));
	B43_WARN_ON(key_len > B43_SEC_KEYSIZE);

	अगर (index >= pairwise_keys_start)
		keymac_ग_लिखो(dev, index, शून्य);	/* First zero out mac. */
	अगर (algorithm == B43_SEC_ALGO_TKIP) अणु
		/*
		 * We should provide an initial iv32, phase1key pair.
		 * We could start with iv32=0 and compute the corresponding
		 * phase1key, but this means calling ieee80211_get_tkip_key
		 * with a fake skb (or export other tkip function).
		 * Because we are lazy we hope iv32 won't start with
		 * 0xffffffff and let's b43_op_update_tkip_key provide a
		 * correct pair.
		 */
		rx_tkip_phase1_ग_लिखो(dev, index, 0xffffffff, (u16*)buf);
	पूर्ण अन्यथा अगर (index >= pairwise_keys_start) /* clear it */
		rx_tkip_phase1_ग_लिखो(dev, index, 0, शून्य);
	अगर (key)
		स_नकल(buf, key, key_len);
	key_ग_लिखो(dev, index, algorithm, buf);
	अगर (index >= pairwise_keys_start)
		keymac_ग_लिखो(dev, index, mac_addr);

	dev->key[index].algorithm = algorithm;
पूर्ण

अटल पूर्णांक b43_key_ग_लिखो(काष्ठा b43_wldev *dev,
			 पूर्णांक index, u8 algorithm,
			 स्थिर u8 *key, माप_प्रकार key_len,
			 स्थिर u8 *mac_addr,
			 काष्ठा ieee80211_key_conf *keyconf)
अणु
	पूर्णांक i;
	पूर्णांक pairwise_keys_start;

	/* For ALG_TKIP the key is encoded as a 256-bit (32 byte) data block:
	 * 	- Temporal Encryption Key (128 bits)
	 * 	- Temporal Authenticator Tx MIC Key (64 bits)
	 * 	- Temporal Authenticator Rx MIC Key (64 bits)
	 *
	 * 	Hardware only store TEK
	 */
	अगर (algorithm == B43_SEC_ALGO_TKIP && key_len == 32)
		key_len = 16;
	अगर (key_len > B43_SEC_KEYSIZE)
		वापस -EINVAL;
	क्रम (i = 0; i < ARRAY_SIZE(dev->key); i++) अणु
		/* Check that we करोn't alपढ़ोy have this key. */
		B43_WARN_ON(dev->key[i].keyconf == keyconf);
	पूर्ण
	अगर (index < 0) अणु
		/* Pairwise key. Get an empty slot क्रम the key. */
		अगर (b43_new_kidx_api(dev))
			pairwise_keys_start = B43_NR_GROUP_KEYS;
		अन्यथा
			pairwise_keys_start = B43_NR_GROUP_KEYS * 2;
		क्रम (i = pairwise_keys_start;
		     i < pairwise_keys_start + B43_NR_PAIRWISE_KEYS;
		     i++) अणु
			B43_WARN_ON(i >= ARRAY_SIZE(dev->key));
			अगर (!dev->key[i].keyconf) अणु
				/* found empty */
				index = i;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (index < 0) अणु
			b43warn(dev->wl, "Out of hardware key memory\n");
			वापस -ENOSPC;
		पूर्ण
	पूर्ण अन्यथा
		B43_WARN_ON(index > 3);

	करो_key_ग_लिखो(dev, index, algorithm, key, key_len, mac_addr);
	अगर ((index <= 3) && !b43_new_kidx_api(dev)) अणु
		/* Default RX key */
		B43_WARN_ON(mac_addr);
		करो_key_ग_लिखो(dev, index + 4, algorithm, key, key_len, शून्य);
	पूर्ण
	keyconf->hw_key_idx = index;
	dev->key[index].keyconf = keyconf;

	वापस 0;
पूर्ण

अटल पूर्णांक b43_key_clear(काष्ठा b43_wldev *dev, पूर्णांक index)
अणु
	अगर (B43_WARN_ON((index < 0) || (index >= ARRAY_SIZE(dev->key))))
		वापस -EINVAL;
	करो_key_ग_लिखो(dev, index, B43_SEC_ALGO_NONE,
		     शून्य, B43_SEC_KEYSIZE, शून्य);
	अगर ((index <= 3) && !b43_new_kidx_api(dev)) अणु
		करो_key_ग_लिखो(dev, index + 4, B43_SEC_ALGO_NONE,
			     शून्य, B43_SEC_KEYSIZE, शून्य);
	पूर्ण
	dev->key[index].keyconf = शून्य;

	वापस 0;
पूर्ण

अटल व्योम b43_clear_keys(काष्ठा b43_wldev *dev)
अणु
	पूर्णांक i, count;

	अगर (b43_new_kidx_api(dev))
		count = B43_NR_GROUP_KEYS + B43_NR_PAIRWISE_KEYS;
	अन्यथा
		count = B43_NR_GROUP_KEYS * 2 + B43_NR_PAIRWISE_KEYS;
	क्रम (i = 0; i < count; i++)
		b43_key_clear(dev, i);
पूर्ण

अटल व्योम b43_dump_keymemory(काष्ठा b43_wldev *dev)
अणु
	अचिन्हित पूर्णांक i, index, count, offset, pairwise_keys_start;
	u8 mac[ETH_ALEN];
	u16 algo;
	u32 rcmta0;
	u16 rcmta1;
	u64 hf;
	काष्ठा b43_key *key;

	अगर (!b43_debug(dev, B43_DBG_KEYS))
		वापस;

	hf = b43_hf_पढ़ो(dev);
	b43dbg(dev->wl, "Hardware key memory dump:  USEDEFKEYS=%u\n",
	       !!(hf & B43_HF_USEDEFKEYS));
	अगर (b43_new_kidx_api(dev)) अणु
		pairwise_keys_start = B43_NR_GROUP_KEYS;
		count = B43_NR_GROUP_KEYS + B43_NR_PAIRWISE_KEYS;
	पूर्ण अन्यथा अणु
		pairwise_keys_start = B43_NR_GROUP_KEYS * 2;
		count = B43_NR_GROUP_KEYS * 2 + B43_NR_PAIRWISE_KEYS;
	पूर्ण
	क्रम (index = 0; index < count; index++) अणु
		key = &(dev->key[index]);
		prपूर्णांकk(KERN_DEBUG "Key slot %02u: %s",
		       index, (key->keyconf == शून्य) ? " " : "*");
		offset = dev->ktp + (index * B43_SEC_KEYSIZE);
		क्रम (i = 0; i < B43_SEC_KEYSIZE; i += 2) अणु
			u16 पंचांगp = b43_shm_पढ़ो16(dev, B43_SHM_SHARED, offset + i);
			prपूर्णांकk("%02X%02X", (पंचांगp & 0xFF), ((पंचांगp >> 8) & 0xFF));
		पूर्ण

		algo = b43_shm_पढ़ो16(dev, B43_SHM_SHARED,
				      B43_SHM_SH_KEYIDXBLOCK + (index * 2));
		prपूर्णांकk("   Algo: %04X/%02X", algo, key->algorithm);

		अगर (index >= pairwise_keys_start) अणु
			अगर (key->algorithm == B43_SEC_ALGO_TKIP) अणु
				prपूर्णांकk("   TKIP: ");
				offset = B43_SHM_SH_TKIPTSCTTAK + (index - 4) * (10 + 4);
				क्रम (i = 0; i < 14; i += 2) अणु
					u16 पंचांगp = b43_shm_पढ़ो16(dev, B43_SHM_SHARED, offset + i);
					prपूर्णांकk("%02X%02X", (पंचांगp & 0xFF), ((पंचांगp >> 8) & 0xFF));
				पूर्ण
			पूर्ण
			rcmta0 = b43_shm_पढ़ो32(dev, B43_SHM_RCMTA,
						((index - pairwise_keys_start) * 2) + 0);
			rcmta1 = b43_shm_पढ़ो16(dev, B43_SHM_RCMTA,
						((index - pairwise_keys_start) * 2) + 1);
			*((__le32 *)(&mac[0])) = cpu_to_le32(rcmta0);
			*((__le16 *)(&mac[4])) = cpu_to_le16(rcmta1);
			prपूर्णांकk("   MAC: %pM", mac);
		पूर्ण अन्यथा
			prपूर्णांकk("   DEFAULT KEY");
		prपूर्णांकk("\n");
	पूर्ण
पूर्ण

व्योम b43_घातer_saving_ctl_bits(काष्ठा b43_wldev *dev, अचिन्हित पूर्णांक ps_flags)
अणु
	u32 macctl;
	u16 ucstat;
	bool hwps;
	bool awake;
	पूर्णांक i;

	B43_WARN_ON((ps_flags & B43_PS_ENABLED) &&
		    (ps_flags & B43_PS_DISABLED));
	B43_WARN_ON((ps_flags & B43_PS_AWAKE) && (ps_flags & B43_PS_ASLEEP));

	अगर (ps_flags & B43_PS_ENABLED) अणु
		hwps = true;
	पूर्ण अन्यथा अगर (ps_flags & B43_PS_DISABLED) अणु
		hwps = false;
	पूर्ण अन्यथा अणु
		//TODO: If घातersave is not off and FIXME is not set and we are not in adhoc
		//      and thus is not an AP and we are associated, set bit 25
	पूर्ण
	अगर (ps_flags & B43_PS_AWAKE) अणु
		awake = true;
	पूर्ण अन्यथा अगर (ps_flags & B43_PS_ASLEEP) अणु
		awake = false;
	पूर्ण अन्यथा अणु
		//TODO: If the device is awake or this is an AP, or we are scanning, or FIXME,
		//      or we are associated, or FIXME, or the latest PS-Poll packet sent was
		//      successful, set bit26
	पूर्ण

/* FIXME: For now we क्रमce awake-on and hwps-off */
	hwps = false;
	awake = true;

	macctl = b43_पढ़ो32(dev, B43_MMIO_MACCTL);
	अगर (hwps)
		macctl |= B43_MACCTL_HWPS;
	अन्यथा
		macctl &= ~B43_MACCTL_HWPS;
	अगर (awake)
		macctl |= B43_MACCTL_AWAKE;
	अन्यथा
		macctl &= ~B43_MACCTL_AWAKE;
	b43_ग_लिखो32(dev, B43_MMIO_MACCTL, macctl);
	/* Commit ग_लिखो */
	b43_पढ़ो32(dev, B43_MMIO_MACCTL);
	अगर (awake && dev->dev->core_rev >= 5) अणु
		/* Wait क्रम the microcode to wake up. */
		क्रम (i = 0; i < 100; i++) अणु
			ucstat = b43_shm_पढ़ो16(dev, B43_SHM_SHARED,
						B43_SHM_SH_UCODESTAT);
			अगर (ucstat != B43_SHM_SH_UCODESTAT_SLEEP)
				अवरोध;
			udelay(10);
		पूर्ण
	पूर्ण
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/BmacCorePllReset */
व्योम b43_wireless_core_phy_pll_reset(काष्ठा b43_wldev *dev)
अणु
	काष्ठा bcma_drv_cc *bcma_cc __maybe_unused;
	काष्ठा ssb_chipcommon *ssb_cc __maybe_unused;

	चयन (dev->dev->bus_type) अणु
#अगर_घोषित CONFIG_B43_BCMA
	हाल B43_BUS_BCMA:
		bcma_cc = &dev->dev->bdev->bus->drv_cc;

		bcma_cc_ग_लिखो32(bcma_cc, BCMA_CC_PMU_CHIPCTL_ADDR, 0);
		bcma_cc_mask32(bcma_cc, BCMA_CC_PMU_CHIPCTL_DATA, ~0x4);
		bcma_cc_set32(bcma_cc, BCMA_CC_PMU_CHIPCTL_DATA, 0x4);
		bcma_cc_mask32(bcma_cc, BCMA_CC_PMU_CHIPCTL_DATA, ~0x4);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SSB
	हाल B43_BUS_SSB:
		ssb_cc = &dev->dev->sdev->bus->chipco;

		chipco_ग_लिखो32(ssb_cc, SSB_CHIPCO_CHIPCTL_ADDR, 0);
		chipco_mask32(ssb_cc, SSB_CHIPCO_CHIPCTL_DATA, ~0x4);
		chipco_set32(ssb_cc, SSB_CHIPCO_CHIPCTL_DATA, 0x4);
		chipco_mask32(ssb_cc, SSB_CHIPCO_CHIPCTL_DATA, ~0x4);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_B43_BCMA
अटल व्योम b43_bcma_phy_reset(काष्ठा b43_wldev *dev)
अणु
	u32 flags;

	/* Put PHY पूर्णांकo reset */
	flags = bcma_aपढ़ो32(dev->dev->bdev, BCMA_IOCTL);
	flags |= B43_BCMA_IOCTL_PHY_RESET;
	flags |= B43_BCMA_IOCTL_PHY_BW_20MHZ; /* Make 20 MHz def */
	bcma_aग_लिखो32(dev->dev->bdev, BCMA_IOCTL, flags);
	udelay(2);

	b43_phy_take_out_of_reset(dev);
पूर्ण

अटल व्योम b43_bcma_wireless_core_reset(काष्ठा b43_wldev *dev, bool gmode)
अणु
	u32 req = B43_BCMA_CLKCTLST_80211_PLL_REQ |
		  B43_BCMA_CLKCTLST_PHY_PLL_REQ;
	u32 status = B43_BCMA_CLKCTLST_80211_PLL_ST |
		     B43_BCMA_CLKCTLST_PHY_PLL_ST;
	u32 flags;

	flags = B43_BCMA_IOCTL_PHY_CLKEN;
	अगर (gmode)
		flags |= B43_BCMA_IOCTL_GMODE;
	b43_device_enable(dev, flags);

	अगर (dev->phy.type == B43_PHYTYPE_AC) अणु
		u16 पंचांगp;

		पंचांगp = bcma_aपढ़ो32(dev->dev->bdev, BCMA_IOCTL);
		पंचांगp &= ~B43_BCMA_IOCTL_DAC;
		पंचांगp |= 0x100;
		bcma_aग_लिखो32(dev->dev->bdev, BCMA_IOCTL, पंचांगp);

		पंचांगp = bcma_aपढ़ो32(dev->dev->bdev, BCMA_IOCTL);
		पंचांगp &= ~B43_BCMA_IOCTL_PHY_CLKEN;
		bcma_aग_लिखो32(dev->dev->bdev, BCMA_IOCTL, पंचांगp);

		पंचांगp = bcma_aपढ़ो32(dev->dev->bdev, BCMA_IOCTL);
		पंचांगp |= B43_BCMA_IOCTL_PHY_CLKEN;
		bcma_aग_लिखो32(dev->dev->bdev, BCMA_IOCTL, पंचांगp);
	पूर्ण

	bcma_core_set_घड़ीmode(dev->dev->bdev, BCMA_CLKMODE_FAST);
	b43_bcma_phy_reset(dev);
	bcma_core_pll_ctl(dev->dev->bdev, req, status, true);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_B43_SSB
अटल व्योम b43_ssb_wireless_core_reset(काष्ठा b43_wldev *dev, bool gmode)
अणु
	u32 flags = 0;

	अगर (gmode)
		flags |= B43_TMSLOW_GMODE;
	flags |= B43_TMSLOW_PHYCLKEN;
	flags |= B43_TMSLOW_PHYRESET;
	अगर (dev->phy.type == B43_PHYTYPE_N)
		flags |= B43_TMSLOW_PHY_BANDWIDTH_20MHZ; /* Make 20 MHz def */
	b43_device_enable(dev, flags);
	msleep(2);		/* Wait क्रम the PLL to turn on. */

	b43_phy_take_out_of_reset(dev);
पूर्ण
#पूर्ण_अगर

व्योम b43_wireless_core_reset(काष्ठा b43_wldev *dev, bool gmode)
अणु
	u32 macctl;

	चयन (dev->dev->bus_type) अणु
#अगर_घोषित CONFIG_B43_BCMA
	हाल B43_BUS_BCMA:
		b43_bcma_wireless_core_reset(dev, gmode);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SSB
	हाल B43_BUS_SSB:
		b43_ssb_wireless_core_reset(dev, gmode);
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	/* Turn Analog ON, but only अगर we alपढ़ोy know the PHY-type.
	 * This protects against very early setup where we करोn't know the
	 * PHY-type, yet. wireless_core_reset will be called once again later,
	 * when we know the PHY-type. */
	अगर (dev->phy.ops)
		dev->phy.ops->चयन_analog(dev, 1);

	macctl = b43_पढ़ो32(dev, B43_MMIO_MACCTL);
	macctl &= ~B43_MACCTL_GMODE;
	अगर (gmode)
		macctl |= B43_MACCTL_GMODE;
	macctl |= B43_MACCTL_IHR_ENABLED;
	b43_ग_लिखो32(dev, B43_MMIO_MACCTL, macctl);
पूर्ण

अटल व्योम handle_irq_transmit_status(काष्ठा b43_wldev *dev)
अणु
	u32 v0, v1;
	u16 पंचांगp;
	काष्ठा b43_txstatus stat;

	जबतक (1) अणु
		v0 = b43_पढ़ो32(dev, B43_MMIO_XMITSTAT_0);
		अगर (!(v0 & 0x00000001))
			अवरोध;
		v1 = b43_पढ़ो32(dev, B43_MMIO_XMITSTAT_1);

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

		b43_handle_txstatus(dev, &stat);
	पूर्ण
पूर्ण

अटल व्योम drain_txstatus_queue(काष्ठा b43_wldev *dev)
अणु
	u32 dummy;

	अगर (dev->dev->core_rev < 5)
		वापस;
	/* Read all entries from the microcode TXstatus FIFO
	 * and throw them away.
	 */
	जबतक (1) अणु
		dummy = b43_पढ़ो32(dev, B43_MMIO_XMITSTAT_0);
		अगर (!(dummy & 0x00000001))
			अवरोध;
		dummy = b43_पढ़ो32(dev, B43_MMIO_XMITSTAT_1);
	पूर्ण
पूर्ण

अटल u32 b43_jssi_पढ़ो(काष्ठा b43_wldev *dev)
अणु
	u32 val = 0;

	val = b43_shm_पढ़ो16(dev, B43_SHM_SHARED, B43_SHM_SH_JSSI1);
	val <<= 16;
	val |= b43_shm_पढ़ो16(dev, B43_SHM_SHARED, B43_SHM_SH_JSSI0);

	वापस val;
पूर्ण

अटल व्योम b43_jssi_ग_लिखो(काष्ठा b43_wldev *dev, u32 jssi)
अणु
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_JSSI0,
			(jssi & 0x0000FFFF));
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_JSSI1,
			(jssi & 0xFFFF0000) >> 16);
पूर्ण

अटल व्योम b43_generate_noise_sample(काष्ठा b43_wldev *dev)
अणु
	b43_jssi_ग_लिखो(dev, 0x7F7F7F7F);
	b43_ग_लिखो32(dev, B43_MMIO_MACCMD,
		    b43_पढ़ो32(dev, B43_MMIO_MACCMD) | B43_MACCMD_BGNOISE);
पूर्ण

अटल व्योम b43_calculate_link_quality(काष्ठा b43_wldev *dev)
अणु
	/* Top half of Link Quality calculation. */

	अगर (dev->phy.type != B43_PHYTYPE_G)
		वापस;
	अगर (dev->noisecalc.calculation_running)
		वापस;
	dev->noisecalc.calculation_running = true;
	dev->noisecalc.nr_samples = 0;

	b43_generate_noise_sample(dev);
पूर्ण

अटल व्योम handle_irq_noise(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy_g *phy = dev->phy.g;
	u16 पंचांगp;
	u8 noise[4];
	u8 i, j;
	s32 average;

	/* Bottom half of Link Quality calculation. */

	अगर (dev->phy.type != B43_PHYTYPE_G)
		वापस;

	/* Possible race condition: It might be possible that the user
	 * changed to a dअगरferent channel in the meanसमय since we
	 * started the calculation. We ignore that fact, since it's
	 * not really that much of a problem. The background noise is
	 * an estimation only anyway. Slightly wrong results will get damped
	 * by the averaging of the 8 sample rounds. Additionally the
	 * value is लघुlived. So it will be replaced by the next noise
	 * calculation round soon. */

	B43_WARN_ON(!dev->noisecalc.calculation_running);
	*((__le32 *)noise) = cpu_to_le32(b43_jssi_पढ़ो(dev));
	अगर (noise[0] == 0x7F || noise[1] == 0x7F ||
	    noise[2] == 0x7F || noise[3] == 0x7F)
		जाओ generate_new;

	/* Get the noise samples. */
	B43_WARN_ON(dev->noisecalc.nr_samples >= 8);
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
		पंचांगp = b43_shm_पढ़ो16(dev, B43_SHM_SHARED, 0x40C);
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
		dev->noisecalc.calculation_running = false;
		वापस;
	पूर्ण
generate_new:
	b43_generate_noise_sample(dev);
पूर्ण

अटल व्योम handle_irq_tbtt_indication(काष्ठा b43_wldev *dev)
अणु
	अगर (b43_is_mode(dev->wl, NL80211_IFTYPE_AP)) अणु
		///TODO: PS TBTT
	पूर्ण अन्यथा अणु
		अगर (1 /*FIXME: the last PSpoll frame was sent successfully */ )
			b43_घातer_saving_ctl_bits(dev, 0);
	पूर्ण
	अगर (b43_is_mode(dev->wl, NL80211_IFTYPE_ADHOC))
		dev->dfq_valid = true;
पूर्ण

अटल व्योम handle_irq_atim_end(काष्ठा b43_wldev *dev)
अणु
	अगर (dev->dfq_valid) अणु
		b43_ग_लिखो32(dev, B43_MMIO_MACCMD,
			    b43_पढ़ो32(dev, B43_MMIO_MACCMD)
			    | B43_MACCMD_DFQ_VALID);
		dev->dfq_valid = false;
	पूर्ण
पूर्ण

अटल व्योम handle_irq_pmq(काष्ठा b43_wldev *dev)
अणु
	u32 पंचांगp;

	//TODO: AP mode.

	जबतक (1) अणु
		पंचांगp = b43_पढ़ो32(dev, B43_MMIO_PS_STATUS);
		अगर (!(पंचांगp & 0x00000008))
			अवरोध;
	पूर्ण
	/* 16bit ग_लिखो is odd, but correct. */
	b43_ग_लिखो16(dev, B43_MMIO_PS_STATUS, 0x0002);
पूर्ण

अटल व्योम b43_ग_लिखो_ढाँचा_common(काष्ठा b43_wldev *dev,
				      स्थिर u8 *data, u16 size,
				      u16 ram_offset,
				      u16 shm_size_offset, u8 rate)
अणु
	u32 i, पंचांगp;
	काष्ठा b43_plcp_hdr4 plcp;

	plcp.data = 0;
	b43_generate_plcp_hdr(&plcp, size + FCS_LEN, rate);
	b43_ram_ग_लिखो(dev, ram_offset, le32_to_cpu(plcp.data));
	ram_offset += माप(u32);
	/* The PLCP is 6 bytes दीर्घ, but we only wrote 4 bytes, yet.
	 * So leave the first two bytes of the next ग_लिखो blank.
	 */
	पंचांगp = (u32) (data[0]) << 16;
	पंचांगp |= (u32) (data[1]) << 24;
	b43_ram_ग_लिखो(dev, ram_offset, पंचांगp);
	ram_offset += माप(u32);
	क्रम (i = 2; i < size; i += माप(u32)) अणु
		पंचांगp = (u32) (data[i + 0]);
		अगर (i + 1 < size)
			पंचांगp |= (u32) (data[i + 1]) << 8;
		अगर (i + 2 < size)
			पंचांगp |= (u32) (data[i + 2]) << 16;
		अगर (i + 3 < size)
			पंचांगp |= (u32) (data[i + 3]) << 24;
		b43_ram_ग_लिखो(dev, ram_offset + i - 2, पंचांगp);
	पूर्ण
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, shm_size_offset,
			size + माप(काष्ठा b43_plcp_hdr6));
पूर्ण

/* Check अगर the use of the antenna that ieee80211 told us to
 * use is possible. This will fall back to DEFAULT.
 * "antenna_nr" is the antenna identअगरier we got from ieee80211. */
u8 b43_ieee80211_antenna_sanitize(काष्ठा b43_wldev *dev,
				  u8 antenna_nr)
अणु
	u8 antenna_mask;

	अगर (antenna_nr == 0) अणु
		/* Zero means "use default antenna". That's always OK. */
		वापस 0;
	पूर्ण

	/* Get the mask of available antennas. */
	अगर (dev->phy.gmode)
		antenna_mask = dev->dev->bus_sprom->ant_available_bg;
	अन्यथा
		antenna_mask = dev->dev->bus_sprom->ant_available_a;

	अगर (!(antenna_mask & (1 << (antenna_nr - 1)))) अणु
		/* This antenna is not available. Fall back to शेष. */
		वापस 0;
	पूर्ण

	वापस antenna_nr;
पूर्ण

/* Convert a b43 antenna number value to the PHY TX control value. */
अटल u16 b43_antenna_to_phyctl(पूर्णांक antenna)
अणु
	चयन (antenna) अणु
	हाल B43_ANTENNA0:
		वापस B43_TXH_PHY_ANT0;
	हाल B43_ANTENNA1:
		वापस B43_TXH_PHY_ANT1;
	हाल B43_ANTENNA2:
		वापस B43_TXH_PHY_ANT2;
	हाल B43_ANTENNA3:
		वापस B43_TXH_PHY_ANT3;
	हाल B43_ANTENNA_AUTO0:
	हाल B43_ANTENNA_AUTO1:
		वापस B43_TXH_PHY_ANT01AUTO;
	पूर्ण
	B43_WARN_ON(1);
	वापस 0;
पूर्ण

अटल व्योम b43_ग_लिखो_beacon_ढाँचा(काष्ठा b43_wldev *dev,
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
	काष्ठा ieee80211_tx_info *info;
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff *beacon_skb;

	spin_lock_irqsave(&dev->wl->beacon_lock, flags);
	info = IEEE80211_SKB_CB(dev->wl->current_beacon);
	rate = ieee80211_get_tx_rate(dev->wl->hw, info)->hw_value;
	/* Clone the beacon, so it cannot go away, जबतक we ग_लिखो it to hw. */
	beacon_skb = skb_clone(dev->wl->current_beacon, GFP_ATOMIC);
	spin_unlock_irqrestore(&dev->wl->beacon_lock, flags);

	अगर (!beacon_skb) अणु
		b43dbg(dev->wl, "Could not upload beacon. "
		       "Failed to clone beacon skb.");
		वापस;
	पूर्ण

	bcn = (स्थिर काष्ठा ieee80211_mgmt *)(beacon_skb->data);
	len = min_t(माप_प्रकार, beacon_skb->len,
		    0x200 - माप(काष्ठा b43_plcp_hdr6));

	b43_ग_लिखो_ढाँचा_common(dev, (स्थिर u8 *)bcn,
				  len, ram_offset, shm_size_offset, rate);

	/* Write the PHY TX control parameters. */
	antenna = B43_ANTENNA_DEFAULT;
	antenna = b43_antenna_to_phyctl(antenna);
	ctl = b43_shm_पढ़ो16(dev, B43_SHM_SHARED, B43_SHM_SH_BEACPHYCTL);
	/* We can't send beacons with लघु preamble. Would get PHY errors. */
	ctl &= ~B43_TXH_PHY_SHORTPRMBL;
	ctl &= ~B43_TXH_PHY_ANT;
	ctl &= ~B43_TXH_PHY_ENC;
	ctl |= antenna;
	अगर (b43_is_cck_rate(rate))
		ctl |= B43_TXH_PHY_ENC_CCK;
	अन्यथा
		ctl |= B43_TXH_PHY_ENC_OFDM;
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_BEACPHYCTL, ctl);

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

			tim_position = माप(काष्ठा b43_plcp_hdr6);
			tim_position += दुरत्व(काष्ठा ieee80211_mgmt, u.beacon.variable);
			tim_position += i;

			dtim_period = ie[i + 3];

			b43_shm_ग_लिखो16(dev, B43_SHM_SHARED,
					B43_SHM_SH_TIMBPOS, tim_position);
			b43_shm_ग_लिखो16(dev, B43_SHM_SHARED,
					B43_SHM_SH_DTIMPER, dtim_period);
			अवरोध;
		पूर्ण
		i += ie_len + 2;
	पूर्ण
	अगर (!tim_found) अणु
		/*
		 * If ucode wants to modअगरy TIM करो it behind the beacon, this
		 * will happen, क्रम example, when करोing mesh networking.
		 */
		b43_shm_ग_लिखो16(dev, B43_SHM_SHARED,
				B43_SHM_SH_TIMBPOS,
				len + माप(काष्ठा b43_plcp_hdr6));
		b43_shm_ग_लिखो16(dev, B43_SHM_SHARED,
				B43_SHM_SH_DTIMPER, 0);
	पूर्ण
	b43dbg(dev->wl, "Updated beacon template at 0x%x\n", ram_offset);

	dev_kमुक्त_skb_any(beacon_skb);
पूर्ण

अटल व्योम b43_upload_beacon0(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_wl *wl = dev->wl;

	अगर (wl->beacon0_uploaded)
		वापस;
	b43_ग_लिखो_beacon_ढाँचा(dev, B43_SHM_SH_BT_BASE0, B43_SHM_SH_BTL0);
	wl->beacon0_uploaded = true;
पूर्ण

अटल व्योम b43_upload_beacon1(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_wl *wl = dev->wl;

	अगर (wl->beacon1_uploaded)
		वापस;
	b43_ग_लिखो_beacon_ढाँचा(dev, B43_SHM_SH_BT_BASE1, B43_SHM_SH_BTL1);
	wl->beacon1_uploaded = true;
पूर्ण

अटल व्योम handle_irq_beacon(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_wl *wl = dev->wl;
	u32 cmd, beacon0_valid, beacon1_valid;

	अगर (!b43_is_mode(wl, NL80211_IFTYPE_AP) &&
	    !b43_is_mode(wl, NL80211_IFTYPE_MESH_POINT) &&
	    !b43_is_mode(wl, NL80211_IFTYPE_ADHOC))
		वापस;

	/* This is the bottom half of the asynchronous beacon update. */

	/* Ignore पूर्णांकerrupt in the future. */
	dev->irq_mask &= ~B43_IRQ_BEACON;

	cmd = b43_पढ़ो32(dev, B43_MMIO_MACCMD);
	beacon0_valid = (cmd & B43_MACCMD_BEACON0_VALID);
	beacon1_valid = (cmd & B43_MACCMD_BEACON1_VALID);

	/* Schedule पूर्णांकerrupt manually, अगर busy. */
	अगर (beacon0_valid && beacon1_valid) अणु
		b43_ग_लिखो32(dev, B43_MMIO_GEN_IRQ_REASON, B43_IRQ_BEACON);
		dev->irq_mask |= B43_IRQ_BEACON;
		वापस;
	पूर्ण

	अगर (unlikely(wl->beacon_ढाँचाs_virgin)) अणु
		/* We never uploaded a beacon beक्रमe.
		 * Upload both ढाँचाs now, but only mark one valid. */
		wl->beacon_ढाँचाs_virgin = false;
		b43_upload_beacon0(dev);
		b43_upload_beacon1(dev);
		cmd = b43_पढ़ो32(dev, B43_MMIO_MACCMD);
		cmd |= B43_MACCMD_BEACON0_VALID;
		b43_ग_लिखो32(dev, B43_MMIO_MACCMD, cmd);
	पूर्ण अन्यथा अणु
		अगर (!beacon0_valid) अणु
			b43_upload_beacon0(dev);
			cmd = b43_पढ़ो32(dev, B43_MMIO_MACCMD);
			cmd |= B43_MACCMD_BEACON0_VALID;
			b43_ग_लिखो32(dev, B43_MMIO_MACCMD, cmd);
		पूर्ण अन्यथा अगर (!beacon1_valid) अणु
			b43_upload_beacon1(dev);
			cmd = b43_पढ़ो32(dev, B43_MMIO_MACCMD);
			cmd |= B43_MACCMD_BEACON1_VALID;
			b43_ग_लिखो32(dev, B43_MMIO_MACCMD, cmd);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम b43_करो_beacon_update_trigger_work(काष्ठा b43_wldev *dev)
अणु
	u32 old_irq_mask = dev->irq_mask;

	/* update beacon right away or defer to irq */
	handle_irq_beacon(dev);
	अगर (old_irq_mask != dev->irq_mask) अणु
		/* The handler updated the IRQ mask. */
		B43_WARN_ON(!dev->irq_mask);
		अगर (b43_पढ़ो32(dev, B43_MMIO_GEN_IRQ_MASK)) अणु
			b43_ग_लिखो32(dev, B43_MMIO_GEN_IRQ_MASK, dev->irq_mask);
		पूर्ण अन्यथा अणु
			/* Device पूर्णांकerrupts are currently disabled. That means
			 * we just ran the hardirq handler and scheduled the
			 * IRQ thपढ़ो. The thपढ़ो will ग_लिखो the IRQ mask when
			 * it finished, so there's nothing to करो here. Writing
			 * the mask _here_ would incorrectly re-enable IRQs. */
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम b43_beacon_update_trigger_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा b43_wl *wl = container_of(work, काष्ठा b43_wl,
					 beacon_update_trigger);
	काष्ठा b43_wldev *dev;

	mutex_lock(&wl->mutex);
	dev = wl->current_dev;
	अगर (likely(dev && (b43_status(dev) >= B43_STAT_INITIALIZED))) अणु
		अगर (b43_bus_host_is_sdio(dev->dev)) अणु
			/* wl->mutex is enough. */
			b43_करो_beacon_update_trigger_work(dev);
		पूर्ण अन्यथा अणु
			spin_lock_irq(&wl->hardirq_lock);
			b43_करो_beacon_update_trigger_work(dev);
			spin_unlock_irq(&wl->hardirq_lock);
		पूर्ण
	पूर्ण
	mutex_unlock(&wl->mutex);
पूर्ण

/* Asynchronously update the packet ढाँचाs in ढाँचा RAM. */
अटल व्योम b43_update_ढाँचाs(काष्ठा b43_wl *wl)
अणु
	काष्ठा sk_buff *beacon, *old_beacon;
	अचिन्हित दीर्घ flags;

	/* This is the top half of the asynchronous beacon update.
	 * The bottom half is the beacon IRQ.
	 * Beacon update must be asynchronous to aव्योम sending an
	 * invalid beacon. This can happen क्रम example, अगर the firmware
	 * transmits a beacon जबतक we are updating it. */

	/* We could modअगरy the existing beacon and set the aid bit in
	 * the TIM field, but that would probably require resizing and
	 * moving of data within the beacon ढाँचा.
	 * Simply request a new beacon and let mac80211 करो the hard work. */
	beacon = ieee80211_beacon_get(wl->hw, wl->vअगर);
	अगर (unlikely(!beacon))
		वापस;

	spin_lock_irqsave(&wl->beacon_lock, flags);
	old_beacon = wl->current_beacon;
	wl->current_beacon = beacon;
	wl->beacon0_uploaded = false;
	wl->beacon1_uploaded = false;
	spin_unlock_irqrestore(&wl->beacon_lock, flags);

	ieee80211_queue_work(wl->hw, &wl->beacon_update_trigger);

	अगर (old_beacon)
		dev_kमुक्त_skb_any(old_beacon);
पूर्ण

अटल व्योम b43_set_beacon_पूर्णांक(काष्ठा b43_wldev *dev, u16 beacon_पूर्णांक)
अणु
	b43_समय_lock(dev);
	अगर (dev->dev->core_rev >= 3) अणु
		b43_ग_लिखो32(dev, B43_MMIO_TSF_CFP_REP, (beacon_पूर्णांक << 16));
		b43_ग_लिखो32(dev, B43_MMIO_TSF_CFP_START, (beacon_पूर्णांक << 10));
	पूर्ण अन्यथा अणु
		b43_ग_लिखो16(dev, 0x606, (beacon_पूर्णांक >> 6));
		b43_ग_लिखो16(dev, 0x610, beacon_पूर्णांक);
	पूर्ण
	b43_समय_unlock(dev);
	b43dbg(dev->wl, "Set beacon interval to %u\n", beacon_पूर्णांक);
पूर्ण

अटल व्योम b43_handle_firmware_panic(काष्ठा b43_wldev *dev)
अणु
	u16 reason;

	/* Read the रेजिस्टर that contains the reason code क्रम the panic. */
	reason = b43_shm_पढ़ो16(dev, B43_SHM_SCRATCH, B43_FWPANIC_REASON_REG);
	b43err(dev->wl, "Whoopsy, firmware panic! Reason: %u\n", reason);

	चयन (reason) अणु
	शेष:
		b43dbg(dev->wl, "The panic reason is unknown.\n");
		fallthrough;
	हाल B43_FWPANIC_DIE:
		/* Do not restart the controller or firmware.
		 * The device is nonfunctional from now on.
		 * Restarting would result in this panic to trigger again,
		 * so we aव्योम that recursion. */
		अवरोध;
	हाल B43_FWPANIC_RESTART:
		b43_controller_restart(dev, "Microcode panic");
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम handle_irq_ucode_debug(काष्ठा b43_wldev *dev)
अणु
	अचिन्हित पूर्णांक i, cnt;
	u16 reason, marker_id, marker_line;
	__le16 *buf;

	/* The proprietary firmware करोesn't have this IRQ. */
	अगर (!dev->fw.खोलोsource)
		वापस;

	/* Read the रेजिस्टर that contains the reason code क्रम this IRQ. */
	reason = b43_shm_पढ़ो16(dev, B43_SHM_SCRATCH, B43_DEBUGIRQ_REASON_REG);

	चयन (reason) अणु
	हाल B43_DEBUGIRQ_PANIC:
		b43_handle_firmware_panic(dev);
		अवरोध;
	हाल B43_DEBUGIRQ_DUMP_SHM:
		अगर (!B43_DEBUG)
			अवरोध; /* Only with driver debugging enabled. */
		buf = kदो_स्मृति(4096, GFP_ATOMIC);
		अगर (!buf) अणु
			b43dbg(dev->wl, "SHM-dump: Failed to allocate memory\n");
			जाओ out;
		पूर्ण
		क्रम (i = 0; i < 4096; i += 2) अणु
			u16 पंचांगp = b43_shm_पढ़ो16(dev, B43_SHM_SHARED, i);
			buf[i / 2] = cpu_to_le16(पंचांगp);
		पूर्ण
		b43info(dev->wl, "Shared memory dump:\n");
		prपूर्णांक_hex_dump(KERN_INFO, "", DUMP_PREFIX_OFFSET,
			       16, 2, buf, 4096, 1);
		kमुक्त(buf);
		अवरोध;
	हाल B43_DEBUGIRQ_DUMP_REGS:
		अगर (!B43_DEBUG)
			अवरोध; /* Only with driver debugging enabled. */
		b43info(dev->wl, "Microcode register dump:\n");
		क्रम (i = 0, cnt = 0; i < 64; i++) अणु
			u16 पंचांगp = b43_shm_पढ़ो16(dev, B43_SHM_SCRATCH, i);
			अगर (cnt == 0)
				prपूर्णांकk(KERN_INFO);
			prपूर्णांकk("r%02u: 0x%04X  ", i, पंचांगp);
			cnt++;
			अगर (cnt == 6) अणु
				prपूर्णांकk("\n");
				cnt = 0;
			पूर्ण
		पूर्ण
		prपूर्णांकk("\n");
		अवरोध;
	हाल B43_DEBUGIRQ_MARKER:
		अगर (!B43_DEBUG)
			अवरोध; /* Only with driver debugging enabled. */
		marker_id = b43_shm_पढ़ो16(dev, B43_SHM_SCRATCH,
					   B43_MARKER_ID_REG);
		marker_line = b43_shm_पढ़ो16(dev, B43_SHM_SCRATCH,
					     B43_MARKER_LINE_REG);
		b43info(dev->wl, "The firmware just executed the MARKER(%u) "
			"at line number %u\n",
			marker_id, marker_line);
		अवरोध;
	शेष:
		b43dbg(dev->wl, "Debug-IRQ triggered for unknown reason: %u\n",
		       reason);
	पूर्ण
out:
	/* Acknowledge the debug-IRQ, so the firmware can जारी. */
	b43_shm_ग_लिखो16(dev, B43_SHM_SCRATCH,
			B43_DEBUGIRQ_REASON_REG, B43_DEBUGIRQ_ACK);
पूर्ण

अटल व्योम b43_करो_पूर्णांकerrupt_thपढ़ो(काष्ठा b43_wldev *dev)
अणु
	u32 reason;
	u32 dma_reason[ARRAY_SIZE(dev->dma_reason)];
	u32 merged_dma_reason = 0;
	पूर्णांक i;

	अगर (unlikely(b43_status(dev) != B43_STAT_STARTED))
		वापस;

	reason = dev->irq_reason;
	क्रम (i = 0; i < ARRAY_SIZE(dma_reason); i++) अणु
		dma_reason[i] = dev->dma_reason[i];
		merged_dma_reason |= dma_reason[i];
	पूर्ण

	अगर (unlikely(reason & B43_IRQ_MAC_TXERR))
		b43err(dev->wl, "MAC transmission error\n");

	अगर (unlikely(reason & B43_IRQ_PHY_TXERR)) अणु
		b43err(dev->wl, "PHY transmission error\n");
		rmb();
		अगर (unlikely(atomic_dec_and_test(&dev->phy.txerr_cnt))) अणु
			atomic_set(&dev->phy.txerr_cnt,
				   B43_PHY_TX_BADNESS_LIMIT);
			b43err(dev->wl, "Too many PHY TX errors, "
					"restarting the controller\n");
			b43_controller_restart(dev, "PHY TX errors");
		पूर्ण
	पूर्ण

	अगर (unlikely(merged_dma_reason & (B43_DMAIRQ_FATALMASK))) अणु
		b43err(dev->wl,
			"Fatal DMA error: 0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X\n",
			dma_reason[0], dma_reason[1],
			dma_reason[2], dma_reason[3],
			dma_reason[4], dma_reason[5]);
		b43err(dev->wl, "This device does not support DMA "
			       "on your system. It will now be switched to PIO.\n");
		/* Fall back to PIO transfers अगर we get fatal DMA errors! */
		dev->use_pio = true;
		b43_controller_restart(dev, "DMA error");
		वापस;
	पूर्ण

	अगर (unlikely(reason & B43_IRQ_UCODE_DEBUG))
		handle_irq_ucode_debug(dev);
	अगर (reason & B43_IRQ_TBTT_INDI)
		handle_irq_tbtt_indication(dev);
	अगर (reason & B43_IRQ_ATIM_END)
		handle_irq_atim_end(dev);
	अगर (reason & B43_IRQ_BEACON)
		handle_irq_beacon(dev);
	अगर (reason & B43_IRQ_PMQ)
		handle_irq_pmq(dev);
	अगर (reason & B43_IRQ_TXFIFO_FLUSH_OK) अणु
		;/* TODO */
	पूर्ण
	अगर (reason & B43_IRQ_NOISESAMPLE_OK)
		handle_irq_noise(dev);

	/* Check the DMA reason रेजिस्टरs क्रम received data. */
	अगर (dma_reason[0] & B43_DMAIRQ_RDESC_UFLOW) अणु
		अगर (B43_DEBUG)
			b43warn(dev->wl, "RX descriptor underrun\n");
		b43_dma_handle_rx_overflow(dev->dma.rx_ring);
	पूर्ण
	अगर (dma_reason[0] & B43_DMAIRQ_RX_DONE) अणु
		अगर (b43_using_pio_transfers(dev))
			b43_pio_rx(dev->pio.rx_queue);
		अन्यथा
			b43_dma_rx(dev->dma.rx_ring);
	पूर्ण
	B43_WARN_ON(dma_reason[1] & B43_DMAIRQ_RX_DONE);
	B43_WARN_ON(dma_reason[2] & B43_DMAIRQ_RX_DONE);
	B43_WARN_ON(dma_reason[3] & B43_DMAIRQ_RX_DONE);
	B43_WARN_ON(dma_reason[4] & B43_DMAIRQ_RX_DONE);
	B43_WARN_ON(dma_reason[5] & B43_DMAIRQ_RX_DONE);

	अगर (reason & B43_IRQ_TX_OK)
		handle_irq_transmit_status(dev);

	/* Re-enable पूर्णांकerrupts on the device by restoring the current पूर्णांकerrupt mask. */
	b43_ग_लिखो32(dev, B43_MMIO_GEN_IRQ_MASK, dev->irq_mask);

#अगर B43_DEBUG
	अगर (b43_debug(dev, B43_DBG_VERBOSESTATS)) अणु
		dev->irq_count++;
		क्रम (i = 0; i < ARRAY_SIZE(dev->irq_bit_count); i++) अणु
			अगर (reason & (1 << i))
				dev->irq_bit_count[i]++;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

/* Interrupt thपढ़ो handler. Handles device पूर्णांकerrupts in thपढ़ो context. */
अटल irqवापस_t b43_पूर्णांकerrupt_thपढ़ो_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा b43_wldev *dev = dev_id;

	mutex_lock(&dev->wl->mutex);
	b43_करो_पूर्णांकerrupt_thपढ़ो(dev);
	mutex_unlock(&dev->wl->mutex);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t b43_करो_पूर्णांकerrupt(काष्ठा b43_wldev *dev)
अणु
	u32 reason;

	/* This code runs under wl->hardirq_lock, but _only_ on non-SDIO busses.
	 * On SDIO, this runs under wl->mutex. */

	reason = b43_पढ़ो32(dev, B43_MMIO_GEN_IRQ_REASON);
	अगर (reason == 0xffffffff)	/* shared IRQ */
		वापस IRQ_NONE;
	reason &= dev->irq_mask;
	अगर (!reason)
		वापस IRQ_NONE;

	dev->dma_reason[0] = b43_पढ़ो32(dev, B43_MMIO_DMA0_REASON)
	    & 0x0001FC00;
	dev->dma_reason[1] = b43_पढ़ो32(dev, B43_MMIO_DMA1_REASON)
	    & 0x0000DC00;
	dev->dma_reason[2] = b43_पढ़ो32(dev, B43_MMIO_DMA2_REASON)
	    & 0x0000DC00;
	dev->dma_reason[3] = b43_पढ़ो32(dev, B43_MMIO_DMA3_REASON)
	    & 0x0001DC00;
	dev->dma_reason[4] = b43_पढ़ो32(dev, B43_MMIO_DMA4_REASON)
	    & 0x0000DC00;
/* Unused ring
	dev->dma_reason[5] = b43_पढ़ो32(dev, B43_MMIO_DMA5_REASON)
	    & 0x0000DC00;
*/

	/* ACK the पूर्णांकerrupt. */
	b43_ग_लिखो32(dev, B43_MMIO_GEN_IRQ_REASON, reason);
	b43_ग_लिखो32(dev, B43_MMIO_DMA0_REASON, dev->dma_reason[0]);
	b43_ग_लिखो32(dev, B43_MMIO_DMA1_REASON, dev->dma_reason[1]);
	b43_ग_लिखो32(dev, B43_MMIO_DMA2_REASON, dev->dma_reason[2]);
	b43_ग_लिखो32(dev, B43_MMIO_DMA3_REASON, dev->dma_reason[3]);
	b43_ग_लिखो32(dev, B43_MMIO_DMA4_REASON, dev->dma_reason[4]);
/* Unused ring
	b43_ग_लिखो32(dev, B43_MMIO_DMA5_REASON, dev->dma_reason[5]);
*/

	/* Disable IRQs on the device. The IRQ thपढ़ो handler will re-enable them. */
	b43_ग_लिखो32(dev, B43_MMIO_GEN_IRQ_MASK, 0);
	/* Save the reason biपंचांगasks क्रम the IRQ thपढ़ो handler. */
	dev->irq_reason = reason;

	वापस IRQ_WAKE_THREAD;
पूर्ण

/* Interrupt handler top-half. This runs with पूर्णांकerrupts disabled. */
अटल irqवापस_t b43_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा b43_wldev *dev = dev_id;
	irqवापस_t ret;

	अगर (unlikely(b43_status(dev) < B43_STAT_STARTED))
		वापस IRQ_NONE;

	spin_lock(&dev->wl->hardirq_lock);
	ret = b43_करो_पूर्णांकerrupt(dev);
	spin_unlock(&dev->wl->hardirq_lock);

	वापस ret;
पूर्ण

/* SDIO पूर्णांकerrupt handler. This runs in process context. */
अटल व्योम b43_sdio_पूर्णांकerrupt_handler(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_wl *wl = dev->wl;
	irqवापस_t ret;

	mutex_lock(&wl->mutex);

	ret = b43_करो_पूर्णांकerrupt(dev);
	अगर (ret == IRQ_WAKE_THREAD)
		b43_करो_पूर्णांकerrupt_thपढ़ो(dev);

	mutex_unlock(&wl->mutex);
पूर्ण

व्योम b43_करो_release_fw(काष्ठा b43_firmware_file *fw)
अणु
	release_firmware(fw->data);
	fw->data = शून्य;
	fw->filename = शून्य;
पूर्ण

अटल व्योम b43_release_firmware(काष्ठा b43_wldev *dev)
अणु
	complete(&dev->fw_load_complete);
	b43_करो_release_fw(&dev->fw.ucode);
	b43_करो_release_fw(&dev->fw.pcm);
	b43_करो_release_fw(&dev->fw.initvals);
	b43_करो_release_fw(&dev->fw.initvals_band);
पूर्ण

अटल व्योम b43_prपूर्णांक_fw_helptext(काष्ठा b43_wl *wl, bool error)
अणु
	स्थिर अक्षर text[] =
		"You must go to " \
		"https://wireless.wiki.kernel.org/en/users/Drivers/b43#devicefirmware " \
		"and download the correct firmware for this driver version. " \
		"Please carefully read all instructions on this website.\n";

	अगर (error)
		b43err(wl, text);
	अन्यथा
		b43warn(wl, text);
पूर्ण

अटल व्योम b43_fw_cb(स्थिर काष्ठा firmware *firmware, व्योम *context)
अणु
	काष्ठा b43_request_fw_context *ctx = context;

	ctx->blob = firmware;
	complete(&ctx->dev->fw_load_complete);
पूर्ण

पूर्णांक b43_करो_request_fw(काष्ठा b43_request_fw_context *ctx,
		      स्थिर अक्षर *name,
		      काष्ठा b43_firmware_file *fw, bool async)
अणु
	काष्ठा b43_fw_header *hdr;
	u32 size;
	पूर्णांक err;

	अगर (!name) अणु
		/* Don't fetch anything. Free possibly cached firmware. */
		/* FIXME: We should probably keep it anyway, to save some headache
		 * on suspend/resume with multiband devices. */
		b43_करो_release_fw(fw);
		वापस 0;
	पूर्ण
	अगर (fw->filename) अणु
		अगर ((fw->type == ctx->req_type) &&
		    (म_भेद(fw->filename, name) == 0))
			वापस 0; /* Alपढ़ोy have this fw. */
		/* Free the cached firmware first. */
		/* FIXME: We should probably करो this later after we successfully
		 * got the new fw. This could reduce headache with multiband devices.
		 * We could also redesign this to cache the firmware क्रम all possible
		 * bands all the समय. */
		b43_करो_release_fw(fw);
	पूर्ण

	चयन (ctx->req_type) अणु
	हाल B43_FWTYPE_PROPRIETARY:
		snम_लिखो(ctx->fwname, माप(ctx->fwname),
			 "b43%s/%s.fw",
			 modparam_fwpostfix, name);
		अवरोध;
	हाल B43_FWTYPE_OPENSOURCE:
		snम_लिखो(ctx->fwname, माप(ctx->fwname),
			 "b43-open%s/%s.fw",
			 modparam_fwpostfix, name);
		अवरोध;
	शेष:
		B43_WARN_ON(1);
		वापस -ENOSYS;
	पूर्ण
	अगर (async) अणु
		/* करो this part asynchronously */
		init_completion(&ctx->dev->fw_load_complete);
		err = request_firmware_noरुको(THIS_MODULE, 1, ctx->fwname,
					      ctx->dev->dev->dev, GFP_KERNEL,
					      ctx, b43_fw_cb);
		अगर (err < 0) अणु
			pr_err("Unable to load firmware\n");
			वापस err;
		पूर्ण
		रुको_क्रम_completion(&ctx->dev->fw_load_complete);
		अगर (ctx->blob)
			जाओ fw_पढ़ोy;
	/* On some ARM प्रणालीs, the async request will fail, but the next sync
	 * request works. For this reason, we fall through here
	 */
	पूर्ण
	err = request_firmware(&ctx->blob, ctx->fwname,
			       ctx->dev->dev->dev);
	अगर (err == -ENOENT) अणु
		snम_लिखो(ctx->errors[ctx->req_type],
			 माप(ctx->errors[ctx->req_type]),
			 "Firmware file \"%s\" not found\n",
			 ctx->fwname);
		वापस err;
	पूर्ण अन्यथा अगर (err) अणु
		snम_लिखो(ctx->errors[ctx->req_type],
			 माप(ctx->errors[ctx->req_type]),
			 "Firmware file \"%s\" request failed (err=%d)\n",
			 ctx->fwname, err);
		वापस err;
	पूर्ण
fw_पढ़ोy:
	अगर (ctx->blob->size < माप(काष्ठा b43_fw_header))
		जाओ err_क्रमmat;
	hdr = (काष्ठा b43_fw_header *)(ctx->blob->data);
	चयन (hdr->type) अणु
	हाल B43_FW_TYPE_UCODE:
	हाल B43_FW_TYPE_PCM:
		size = be32_to_cpu(hdr->size);
		अगर (size != ctx->blob->size - माप(काष्ठा b43_fw_header))
			जाओ err_क्रमmat;
		fallthrough;
	हाल B43_FW_TYPE_IV:
		अगर (hdr->ver != 1)
			जाओ err_क्रमmat;
		अवरोध;
	शेष:
		जाओ err_क्रमmat;
	पूर्ण

	fw->data = ctx->blob;
	fw->filename = name;
	fw->type = ctx->req_type;

	वापस 0;

err_क्रमmat:
	snम_लिखो(ctx->errors[ctx->req_type],
		 माप(ctx->errors[ctx->req_type]),
		 "Firmware file \"%s\" format error.\n", ctx->fwname);
	release_firmware(ctx->blob);

	वापस -EPROTO;
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/Init/Firmware */
अटल पूर्णांक b43_try_request_fw(काष्ठा b43_request_fw_context *ctx)
अणु
	काष्ठा b43_wldev *dev = ctx->dev;
	काष्ठा b43_firmware *fw = &ctx->dev->fw;
	काष्ठा b43_phy *phy = &dev->phy;
	स्थिर u8 rev = ctx->dev->dev->core_rev;
	स्थिर अक्षर *filename;
	पूर्णांक err;

	/* Get microcode */
	filename = शून्य;
	चयन (rev) अणु
	हाल 42:
		अगर (phy->type == B43_PHYTYPE_AC)
			filename = "ucode42";
		अवरोध;
	हाल 40:
		अगर (phy->type == B43_PHYTYPE_AC)
			filename = "ucode40";
		अवरोध;
	हाल 33:
		अगर (phy->type == B43_PHYTYPE_LCN40)
			filename = "ucode33_lcn40";
		अवरोध;
	हाल 30:
		अगर (phy->type == B43_PHYTYPE_N)
			filename = "ucode30_mimo";
		अवरोध;
	हाल 29:
		अगर (phy->type == B43_PHYTYPE_HT)
			filename = "ucode29_mimo";
		अवरोध;
	हाल 26:
		अगर (phy->type == B43_PHYTYPE_HT)
			filename = "ucode26_mimo";
		अवरोध;
	हाल 28:
	हाल 25:
		अगर (phy->type == B43_PHYTYPE_N)
			filename = "ucode25_mimo";
		अन्यथा अगर (phy->type == B43_PHYTYPE_LCN)
			filename = "ucode25_lcn";
		अवरोध;
	हाल 24:
		अगर (phy->type == B43_PHYTYPE_LCN)
			filename = "ucode24_lcn";
		अवरोध;
	हाल 23:
		अगर (phy->type == B43_PHYTYPE_N)
			filename = "ucode16_mimo";
		अवरोध;
	हाल 16 ... 19:
		अगर (phy->type == B43_PHYTYPE_N)
			filename = "ucode16_mimo";
		अन्यथा अगर (phy->type == B43_PHYTYPE_LP)
			filename = "ucode16_lp";
		अवरोध;
	हाल 15:
		filename = "ucode15";
		अवरोध;
	हाल 14:
		filename = "ucode14";
		अवरोध;
	हाल 13:
		filename = "ucode13";
		अवरोध;
	हाल 11 ... 12:
		filename = "ucode11";
		अवरोध;
	हाल 5 ... 10:
		filename = "ucode5";
		अवरोध;
	पूर्ण
	अगर (!filename)
		जाओ err_no_ucode;
	err = b43_करो_request_fw(ctx, filename, &fw->ucode, true);
	अगर (err)
		जाओ err_load;

	/* Get PCM code */
	अगर ((rev >= 5) && (rev <= 10))
		filename = "pcm5";
	अन्यथा अगर (rev >= 11)
		filename = शून्य;
	अन्यथा
		जाओ err_no_pcm;
	fw->pcm_request_failed = false;
	err = b43_करो_request_fw(ctx, filename, &fw->pcm, false);
	अगर (err == -ENOENT) अणु
		/* We did not find a PCM file? Not fatal, but
		 * core rev <= 10 must करो without hwcrypto then. */
		fw->pcm_request_failed = true;
	पूर्ण अन्यथा अगर (err)
		जाओ err_load;

	/* Get initvals */
	filename = शून्य;
	चयन (dev->phy.type) अणु
	हाल B43_PHYTYPE_G:
		अगर (rev == 13)
			filename = "b0g0initvals13";
		अन्यथा अगर (rev >= 5 && rev <= 10)
			filename = "b0g0initvals5";
		अवरोध;
	हाल B43_PHYTYPE_N:
		अगर (rev == 30)
			filename = "n16initvals30";
		अन्यथा अगर (rev == 28 || rev == 25)
			filename = "n0initvals25";
		अन्यथा अगर (rev == 24)
			filename = "n0initvals24";
		अन्यथा अगर (rev == 23)
			filename = "n0initvals16"; /* What about n0initvals22? */
		अन्यथा अगर (rev >= 16 && rev <= 18)
			filename = "n0initvals16";
		अन्यथा अगर (rev >= 11 && rev <= 12)
			filename = "n0initvals11";
		अवरोध;
	हाल B43_PHYTYPE_LP:
		अगर (rev >= 16 && rev <= 18)
			filename = "lp0initvals16";
		अन्यथा अगर (rev == 15)
			filename = "lp0initvals15";
		अन्यथा अगर (rev == 14)
			filename = "lp0initvals14";
		अन्यथा अगर (rev == 13)
			filename = "lp0initvals13";
		अवरोध;
	हाल B43_PHYTYPE_HT:
		अगर (rev == 29)
			filename = "ht0initvals29";
		अन्यथा अगर (rev == 26)
			filename = "ht0initvals26";
		अवरोध;
	हाल B43_PHYTYPE_LCN:
		अगर (rev == 24)
			filename = "lcn0initvals24";
		अवरोध;
	हाल B43_PHYTYPE_LCN40:
		अगर (rev == 33)
			filename = "lcn400initvals33";
		अवरोध;
	हाल B43_PHYTYPE_AC:
		अगर (rev == 42)
			filename = "ac1initvals42";
		अन्यथा अगर (rev == 40)
			filename = "ac0initvals40";
		अवरोध;
	पूर्ण
	अगर (!filename)
		जाओ err_no_initvals;
	err = b43_करो_request_fw(ctx, filename, &fw->initvals, false);
	अगर (err)
		जाओ err_load;

	/* Get bandचयन initvals */
	filename = शून्य;
	चयन (dev->phy.type) अणु
	हाल B43_PHYTYPE_G:
		अगर (rev == 13)
			filename = "b0g0bsinitvals13";
		अन्यथा अगर (rev >= 5 && rev <= 10)
			filename = "b0g0bsinitvals5";
		अवरोध;
	हाल B43_PHYTYPE_N:
		अगर (rev == 30)
			filename = "n16bsinitvals30";
		अन्यथा अगर (rev == 28 || rev == 25)
			filename = "n0bsinitvals25";
		अन्यथा अगर (rev == 24)
			filename = "n0bsinitvals24";
		अन्यथा अगर (rev == 23)
			filename = "n0bsinitvals16"; /* What about n0bsinitvals22? */
		अन्यथा अगर (rev >= 16 && rev <= 18)
			filename = "n0bsinitvals16";
		अन्यथा अगर (rev >= 11 && rev <= 12)
			filename = "n0bsinitvals11";
		अवरोध;
	हाल B43_PHYTYPE_LP:
		अगर (rev >= 16 && rev <= 18)
			filename = "lp0bsinitvals16";
		अन्यथा अगर (rev == 15)
			filename = "lp0bsinitvals15";
		अन्यथा अगर (rev == 14)
			filename = "lp0bsinitvals14";
		अन्यथा अगर (rev == 13)
			filename = "lp0bsinitvals13";
		अवरोध;
	हाल B43_PHYTYPE_HT:
		अगर (rev == 29)
			filename = "ht0bsinitvals29";
		अन्यथा अगर (rev == 26)
			filename = "ht0bsinitvals26";
		अवरोध;
	हाल B43_PHYTYPE_LCN:
		अगर (rev == 24)
			filename = "lcn0bsinitvals24";
		अवरोध;
	हाल B43_PHYTYPE_LCN40:
		अगर (rev == 33)
			filename = "lcn400bsinitvals33";
		अवरोध;
	हाल B43_PHYTYPE_AC:
		अगर (rev == 42)
			filename = "ac1bsinitvals42";
		अन्यथा अगर (rev == 40)
			filename = "ac0bsinitvals40";
		अवरोध;
	पूर्ण
	अगर (!filename)
		जाओ err_no_initvals;
	err = b43_करो_request_fw(ctx, filename, &fw->initvals_band, false);
	अगर (err)
		जाओ err_load;

	fw->खोलोsource = (ctx->req_type == B43_FWTYPE_OPENSOURCE);

	वापस 0;

err_no_ucode:
	err = ctx->fatal_failure = -EOPNOTSUPP;
	b43err(dev->wl, "The driver does not know which firmware (ucode) "
	       "is required for your device (wl-core rev %u)\n", rev);
	जाओ error;

err_no_pcm:
	err = ctx->fatal_failure = -EOPNOTSUPP;
	b43err(dev->wl, "The driver does not know which firmware (PCM) "
	       "is required for your device (wl-core rev %u)\n", rev);
	जाओ error;

err_no_initvals:
	err = ctx->fatal_failure = -EOPNOTSUPP;
	b43err(dev->wl, "The driver does not know which firmware (initvals) "
	       "is required for your device (wl-core rev %u)\n", rev);
	जाओ error;

err_load:
	/* We failed to load this firmware image. The error message
	 * alपढ़ोy is in ctx->errors. Return and let our caller decide
	 * what to करो. */
	जाओ error;

error:
	b43_release_firmware(dev);
	वापस err;
पूर्ण

अटल पूर्णांक b43_one_core_attach(काष्ठा b43_bus_dev *dev, काष्ठा b43_wl *wl);
अटल व्योम b43_one_core_detach(काष्ठा b43_bus_dev *dev);
अटल पूर्णांक b43_rng_init(काष्ठा b43_wl *wl);

अटल व्योम b43_request_firmware(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा b43_wl *wl = container_of(work,
			    काष्ठा b43_wl, firmware_load);
	काष्ठा b43_wldev *dev = wl->current_dev;
	काष्ठा b43_request_fw_context *ctx;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;
	स्थिर अक्षर *errmsg;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस;
	ctx->dev = dev;

	ctx->req_type = B43_FWTYPE_PROPRIETARY;
	err = b43_try_request_fw(ctx);
	अगर (!err)
		जाओ start_ieee80211; /* Successfully loaded it. */
	/* Was fw version known? */
	अगर (ctx->fatal_failure)
		जाओ out;

	/* proprietary fw not found, try खोलो source */
	ctx->req_type = B43_FWTYPE_OPENSOURCE;
	err = b43_try_request_fw(ctx);
	अगर (!err)
		जाओ start_ieee80211; /* Successfully loaded it. */
	अगर(ctx->fatal_failure)
		जाओ out;

	/* Could not find a usable firmware. Prपूर्णांक the errors. */
	क्रम (i = 0; i < B43_NR_FWTYPES; i++) अणु
		errmsg = ctx->errors[i];
		अगर (म_माप(errmsg))
			b43err(dev->wl, "%s", errmsg);
	पूर्ण
	b43_prपूर्णांक_fw_helptext(dev->wl, 1);
	जाओ out;

start_ieee80211:
	wl->hw->queues = B43_QOS_QUEUE_NUM;
	अगर (!modparam_qos || dev->fw.खोलोsource)
		wl->hw->queues = 1;

	err = ieee80211_रेजिस्टर_hw(wl->hw);
	अगर (err)
		जाओ out;
	wl->hw_रेजिस्टरed = true;
	b43_leds_रेजिस्टर(wl->current_dev);

	/* Register HW RNG driver */
	b43_rng_init(wl);

out:
	kमुक्त(ctx);
पूर्ण

अटल पूर्णांक b43_upload_microcode(काष्ठा b43_wldev *dev)
अणु
	काष्ठा wiphy *wiphy = dev->wl->hw->wiphy;
	स्थिर माप_प्रकार hdr_len = माप(काष्ठा b43_fw_header);
	स्थिर __be32 *data;
	अचिन्हित पूर्णांक i, len;
	u16 fwrev, fwpatch, fwdate, fwसमय;
	u32 पंचांगp, macctl;
	पूर्णांक err = 0;

	/* Jump the microcode PSM to offset 0 */
	macctl = b43_पढ़ो32(dev, B43_MMIO_MACCTL);
	B43_WARN_ON(macctl & B43_MACCTL_PSM_RUN);
	macctl |= B43_MACCTL_PSM_JMP0;
	b43_ग_लिखो32(dev, B43_MMIO_MACCTL, macctl);
	/* Zero out all microcode PSM रेजिस्टरs and shared memory. */
	क्रम (i = 0; i < 64; i++)
		b43_shm_ग_लिखो16(dev, B43_SHM_SCRATCH, i, 0);
	क्रम (i = 0; i < 4096; i += 2)
		b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, i, 0);

	/* Upload Microcode. */
	data = (__be32 *) (dev->fw.ucode.data->data + hdr_len);
	len = (dev->fw.ucode.data->size - hdr_len) / माप(__be32);
	b43_shm_control_word(dev, B43_SHM_UCODE | B43_SHM_AUTOINC_W, 0x0000);
	क्रम (i = 0; i < len; i++) अणु
		b43_ग_लिखो32(dev, B43_MMIO_SHM_DATA, be32_to_cpu(data[i]));
		udelay(10);
	पूर्ण

	अगर (dev->fw.pcm.data) अणु
		/* Upload PCM data. */
		data = (__be32 *) (dev->fw.pcm.data->data + hdr_len);
		len = (dev->fw.pcm.data->size - hdr_len) / माप(__be32);
		b43_shm_control_word(dev, B43_SHM_HW, 0x01EA);
		b43_ग_लिखो32(dev, B43_MMIO_SHM_DATA, 0x00004000);
		/* No need क्रम स्वतःinc bit in SHM_HW */
		b43_shm_control_word(dev, B43_SHM_HW, 0x01EB);
		क्रम (i = 0; i < len; i++) अणु
			b43_ग_लिखो32(dev, B43_MMIO_SHM_DATA, be32_to_cpu(data[i]));
			udelay(10);
		पूर्ण
	पूर्ण

	b43_ग_लिखो32(dev, B43_MMIO_GEN_IRQ_REASON, B43_IRQ_ALL);

	/* Start the microcode PSM */
	b43_maskset32(dev, B43_MMIO_MACCTL, ~B43_MACCTL_PSM_JMP0,
		      B43_MACCTL_PSM_RUN);

	/* Wait क्रम the microcode to load and respond */
	i = 0;
	जबतक (1) अणु
		पंचांगp = b43_पढ़ो32(dev, B43_MMIO_GEN_IRQ_REASON);
		अगर (पंचांगp == B43_IRQ_MAC_SUSPENDED)
			अवरोध;
		i++;
		अगर (i >= 20) अणु
			b43err(dev->wl, "Microcode not responding\n");
			b43_prपूर्णांक_fw_helptext(dev->wl, 1);
			err = -ENODEV;
			जाओ error;
		पूर्ण
		msleep(50);
	पूर्ण
	b43_पढ़ो32(dev, B43_MMIO_GEN_IRQ_REASON);	/* dummy पढ़ो */

	/* Get and check the revisions. */
	fwrev = b43_shm_पढ़ो16(dev, B43_SHM_SHARED, B43_SHM_SH_UCODEREV);
	fwpatch = b43_shm_पढ़ो16(dev, B43_SHM_SHARED, B43_SHM_SH_UCODEPATCH);
	fwdate = b43_shm_पढ़ो16(dev, B43_SHM_SHARED, B43_SHM_SH_UCODEDATE);
	fwसमय = b43_shm_पढ़ो16(dev, B43_SHM_SHARED, B43_SHM_SH_UCODETIME);

	अगर (fwrev <= 0x128) अणु
		b43err(dev->wl, "YOUR FIRMWARE IS TOO OLD. Firmware from "
		       "binary drivers older than version 4.x is unsupported. "
		       "You must upgrade your firmware files.\n");
		b43_prपूर्णांक_fw_helptext(dev->wl, 1);
		err = -EOPNOTSUPP;
		जाओ error;
	पूर्ण
	dev->fw.rev = fwrev;
	dev->fw.patch = fwpatch;
	अगर (dev->fw.rev >= 598)
		dev->fw.hdr_क्रमmat = B43_FW_HDR_598;
	अन्यथा अगर (dev->fw.rev >= 410)
		dev->fw.hdr_क्रमmat = B43_FW_HDR_410;
	अन्यथा
		dev->fw.hdr_क्रमmat = B43_FW_HDR_351;
	WARN_ON(dev->fw.खोलोsource != (fwdate == 0xFFFF));

	dev->qos_enabled = dev->wl->hw->queues > 1;
	/* Default to firmware/hardware crypto acceleration. */
	dev->hwcrypto_enabled = true;

	अगर (dev->fw.खोलोsource) अणु
		u16 fwcapa;

		/* Patchlevel info is encoded in the "time" field. */
		dev->fw.patch = fwसमय;
		b43info(dev->wl, "Loading OpenSource firmware version %u.%u\n",
			dev->fw.rev, dev->fw.patch);

		fwcapa = b43_fwcapa_पढ़ो(dev);
		अगर (!(fwcapa & B43_FWCAPA_HWCRYPTO) || dev->fw.pcm_request_failed) अणु
			b43info(dev->wl, "Hardware crypto acceleration not supported by firmware\n");
			/* Disable hardware crypto and fall back to software crypto. */
			dev->hwcrypto_enabled = false;
		पूर्ण
		/* adding QoS support should use an offline discovery mechanism */
		WARN(fwcapa & B43_FWCAPA_QOS, "QoS in OpenFW not supported\n");
	पूर्ण अन्यथा अणु
		b43info(dev->wl, "Loading firmware version %u.%u "
			"(20%.2i-%.2i-%.2i %.2i:%.2i:%.2i)\n",
			fwrev, fwpatch,
			(fwdate >> 12) & 0xF, (fwdate >> 8) & 0xF, fwdate & 0xFF,
			(fwसमय >> 11) & 0x1F, (fwसमय >> 5) & 0x3F, fwसमय & 0x1F);
		अगर (dev->fw.pcm_request_failed) अणु
			b43warn(dev->wl, "No \"pcm5.fw\" firmware file found. "
				"Hardware accelerated cryptography is disabled.\n");
			b43_prपूर्णांक_fw_helptext(dev->wl, 0);
		पूर्ण
	पूर्ण

	snम_लिखो(wiphy->fw_version, माप(wiphy->fw_version), "%u.%u",
			dev->fw.rev, dev->fw.patch);
	wiphy->hw_version = dev->dev->core_id;

	अगर (dev->fw.hdr_क्रमmat == B43_FW_HDR_351) अणु
		/* We're over the deadline, but we keep support क्रम old fw
		 * until it turns out to be in major conflict with something new. */
		b43warn(dev->wl, "You are using an old firmware image. "
			"Support for old firmware will be removed soon "
			"(official deadline was July 2008).\n");
		b43_prपूर्णांक_fw_helptext(dev->wl, 0);
	पूर्ण

	वापस 0;

error:
	/* Stop the microcode PSM. */
	b43_maskset32(dev, B43_MMIO_MACCTL, ~B43_MACCTL_PSM_RUN,
		      B43_MACCTL_PSM_JMP0);

	वापस err;
पूर्ण

अटल पूर्णांक b43_ग_लिखो_initvals(काष्ठा b43_wldev *dev,
			      स्थिर काष्ठा b43_iv *ivals,
			      माप_प्रकार count,
			      माप_प्रकार array_size)
अणु
	स्थिर काष्ठा b43_iv *iv;
	u16 offset;
	माप_प्रकार i;
	bool bit32;

	BUILD_BUG_ON(माप(काष्ठा b43_iv) != 6);
	iv = ivals;
	क्रम (i = 0; i < count; i++) अणु
		अगर (array_size < माप(iv->offset_size))
			जाओ err_क्रमmat;
		array_size -= माप(iv->offset_size);
		offset = be16_to_cpu(iv->offset_size);
		bit32 = !!(offset & B43_IV_32BIT);
		offset &= B43_IV_OFFSET_MASK;
		अगर (offset >= 0x1000)
			जाओ err_क्रमmat;
		अगर (bit32) अणु
			u32 value;

			अगर (array_size < माप(iv->data.d32))
				जाओ err_क्रमmat;
			array_size -= माप(iv->data.d32);

			value = get_unaligned_be32(&iv->data.d32);
			b43_ग_लिखो32(dev, offset, value);

			iv = (स्थिर काष्ठा b43_iv *)((स्थिर uपूर्णांक8_t *)iv +
							माप(__be16) +
							माप(__be32));
		पूर्ण अन्यथा अणु
			u16 value;

			अगर (array_size < माप(iv->data.d16))
				जाओ err_क्रमmat;
			array_size -= माप(iv->data.d16);

			value = be16_to_cpu(iv->data.d16);
			b43_ग_लिखो16(dev, offset, value);

			iv = (स्थिर काष्ठा b43_iv *)((स्थिर uपूर्णांक8_t *)iv +
							माप(__be16) +
							माप(__be16));
		पूर्ण
	पूर्ण
	अगर (array_size)
		जाओ err_क्रमmat;

	वापस 0;

err_क्रमmat:
	b43err(dev->wl, "Initial Values Firmware file-format error.\n");
	b43_prपूर्णांक_fw_helptext(dev->wl, 1);

	वापस -EPROTO;
पूर्ण

अटल पूर्णांक b43_upload_initvals(काष्ठा b43_wldev *dev)
अणु
	स्थिर माप_प्रकार hdr_len = माप(काष्ठा b43_fw_header);
	स्थिर काष्ठा b43_fw_header *hdr;
	काष्ठा b43_firmware *fw = &dev->fw;
	स्थिर काष्ठा b43_iv *ivals;
	माप_प्रकार count;

	hdr = (स्थिर काष्ठा b43_fw_header *)(fw->initvals.data->data);
	ivals = (स्थिर काष्ठा b43_iv *)(fw->initvals.data->data + hdr_len);
	count = be32_to_cpu(hdr->size);
	वापस b43_ग_लिखो_initvals(dev, ivals, count,
				 fw->initvals.data->size - hdr_len);
पूर्ण

अटल पूर्णांक b43_upload_initvals_band(काष्ठा b43_wldev *dev)
अणु
	स्थिर माप_प्रकार hdr_len = माप(काष्ठा b43_fw_header);
	स्थिर काष्ठा b43_fw_header *hdr;
	काष्ठा b43_firmware *fw = &dev->fw;
	स्थिर काष्ठा b43_iv *ivals;
	माप_प्रकार count;

	अगर (!fw->initvals_band.data)
		वापस 0;

	hdr = (स्थिर काष्ठा b43_fw_header *)(fw->initvals_band.data->data);
	ivals = (स्थिर काष्ठा b43_iv *)(fw->initvals_band.data->data + hdr_len);
	count = be32_to_cpu(hdr->size);
	वापस b43_ग_लिखो_initvals(dev, ivals, count,
				  fw->initvals_band.data->size - hdr_len);
पूर्ण

/* Initialize the GPIOs
 * https://bcm-specs.sipsolutions.net/GPIO
 */

#अगर_घोषित CONFIG_B43_SSB
अटल काष्ठा ssb_device *b43_ssb_gpio_dev(काष्ठा b43_wldev *dev)
अणु
	काष्ठा ssb_bus *bus = dev->dev->sdev->bus;

#अगर_घोषित CONFIG_SSB_DRIVER_PCICORE
	वापस (bus->chipco.dev ? bus->chipco.dev : bus->pcicore.dev);
#अन्यथा
	वापस bus->chipco.dev;
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक b43_gpio_init(काष्ठा b43_wldev *dev)
अणु
#अगर_घोषित CONFIG_B43_SSB
	काष्ठा ssb_device *gpiodev;
#पूर्ण_अगर
	u32 mask, set;

	b43_maskset32(dev, B43_MMIO_MACCTL, ~B43_MACCTL_GPOUTSMSK, 0);
	b43_maskset16(dev, B43_MMIO_GPIO_MASK, ~0, 0xF);

	mask = 0x0000001F;
	set = 0x0000000F;
	अगर (dev->dev->chip_id == 0x4301) अणु
		mask |= 0x0060;
		set |= 0x0060;
	पूर्ण अन्यथा अगर (dev->dev->chip_id == 0x5354) अणु
		/* Don't allow overtaking buttons GPIOs */
		set &= 0x2; /* 0x2 is LED GPIO on BCM5354 */
	पूर्ण

	अगर (0 /* FIXME: conditional unknown */ ) अणु
		b43_ग_लिखो16(dev, B43_MMIO_GPIO_MASK,
			    b43_पढ़ो16(dev, B43_MMIO_GPIO_MASK)
			    | 0x0100);
		/* BT Coexistance Input */
		mask |= 0x0080;
		set |= 0x0080;
		/* BT Coexistance Out */
		mask |= 0x0100;
		set |= 0x0100;
	पूर्ण
	अगर (dev->dev->bus_sprom->boardflags_lo & B43_BFL_PACTRL) अणु
		/* PA is controlled by gpio 9, let ucode handle it */
		b43_ग_लिखो16(dev, B43_MMIO_GPIO_MASK,
			    b43_पढ़ो16(dev, B43_MMIO_GPIO_MASK)
			    | 0x0200);
		mask |= 0x0200;
		set |= 0x0200;
	पूर्ण

	चयन (dev->dev->bus_type) अणु
#अगर_घोषित CONFIG_B43_BCMA
	हाल B43_BUS_BCMA:
		bcma_chipco_gpio_control(&dev->dev->bdev->bus->drv_cc, mask, set);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SSB
	हाल B43_BUS_SSB:
		gpiodev = b43_ssb_gpio_dev(dev);
		अगर (gpiodev)
			ssb_ग_लिखो32(gpiodev, B43_GPIO_CONTROL,
				    (ssb_पढ़ो32(gpiodev, B43_GPIO_CONTROL)
				    & ~mask) | set);
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

/* Turn off all GPIO stuff. Call this on module unload, क्रम example. */
अटल व्योम b43_gpio_cleanup(काष्ठा b43_wldev *dev)
अणु
#अगर_घोषित CONFIG_B43_SSB
	काष्ठा ssb_device *gpiodev;
#पूर्ण_अगर

	चयन (dev->dev->bus_type) अणु
#अगर_घोषित CONFIG_B43_BCMA
	हाल B43_BUS_BCMA:
		bcma_chipco_gpio_control(&dev->dev->bdev->bus->drv_cc, ~0, 0);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SSB
	हाल B43_BUS_SSB:
		gpiodev = b43_ssb_gpio_dev(dev);
		अगर (gpiodev)
			ssb_ग_लिखो32(gpiodev, B43_GPIO_CONTROL, 0);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
पूर्ण

/* http://bcm-specs.sipsolutions.net/EnableMac */
व्योम b43_mac_enable(काष्ठा b43_wldev *dev)
अणु
	अगर (b43_debug(dev, B43_DBG_FIRMWARE)) अणु
		u16 fwstate;

		fwstate = b43_shm_पढ़ो16(dev, B43_SHM_SHARED,
					 B43_SHM_SH_UCODESTAT);
		अगर ((fwstate != B43_SHM_SH_UCODESTAT_SUSP) &&
		    (fwstate != B43_SHM_SH_UCODESTAT_SLEEP)) अणु
			b43err(dev->wl, "b43_mac_enable(): The firmware "
			       "should be suspended, but current state is %u\n",
			       fwstate);
		पूर्ण
	पूर्ण

	dev->mac_suspended--;
	B43_WARN_ON(dev->mac_suspended < 0);
	अगर (dev->mac_suspended == 0) अणु
		b43_maskset32(dev, B43_MMIO_MACCTL, ~0, B43_MACCTL_ENABLED);
		b43_ग_लिखो32(dev, B43_MMIO_GEN_IRQ_REASON,
			    B43_IRQ_MAC_SUSPENDED);
		/* Commit ग_लिखोs */
		b43_पढ़ो32(dev, B43_MMIO_MACCTL);
		b43_पढ़ो32(dev, B43_MMIO_GEN_IRQ_REASON);
		b43_घातer_saving_ctl_bits(dev, 0);
	पूर्ण
पूर्ण

/* https://bcm-specs.sipsolutions.net/SuspendMAC */
व्योम b43_mac_suspend(काष्ठा b43_wldev *dev)
अणु
	पूर्णांक i;
	u32 पंचांगp;

	might_sleep();
	B43_WARN_ON(dev->mac_suspended < 0);

	अगर (dev->mac_suspended == 0) अणु
		b43_घातer_saving_ctl_bits(dev, B43_PS_AWAKE);
		b43_maskset32(dev, B43_MMIO_MACCTL, ~B43_MACCTL_ENABLED, 0);
		/* क्रमce pci to flush the ग_लिखो */
		b43_पढ़ो32(dev, B43_MMIO_MACCTL);
		क्रम (i = 35; i; i--) अणु
			पंचांगp = b43_पढ़ो32(dev, B43_MMIO_GEN_IRQ_REASON);
			अगर (पंचांगp & B43_IRQ_MAC_SUSPENDED)
				जाओ out;
			udelay(10);
		पूर्ण
		/* Hm, it seems this will take some समय. Use msleep(). */
		क्रम (i = 40; i; i--) अणु
			पंचांगp = b43_पढ़ो32(dev, B43_MMIO_GEN_IRQ_REASON);
			अगर (पंचांगp & B43_IRQ_MAC_SUSPENDED)
				जाओ out;
			msleep(1);
		पूर्ण
		b43err(dev->wl, "MAC suspend failed\n");
	पूर्ण
out:
	dev->mac_suspended++;
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/MacPhyClkSet */
व्योम b43_mac_phy_घड़ी_set(काष्ठा b43_wldev *dev, bool on)
अणु
	u32 पंचांगp;

	चयन (dev->dev->bus_type) अणु
#अगर_घोषित CONFIG_B43_BCMA
	हाल B43_BUS_BCMA:
		पंचांगp = bcma_aपढ़ो32(dev->dev->bdev, BCMA_IOCTL);
		अगर (on)
			पंचांगp |= B43_BCMA_IOCTL_MACPHYCLKEN;
		अन्यथा
			पंचांगp &= ~B43_BCMA_IOCTL_MACPHYCLKEN;
		bcma_aग_लिखो32(dev->dev->bdev, BCMA_IOCTL, पंचांगp);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SSB
	हाल B43_BUS_SSB:
		पंचांगp = ssb_पढ़ो32(dev->dev->sdev, SSB_TMSLOW);
		अगर (on)
			पंचांगp |= B43_TMSLOW_MACPHYCLKEN;
		अन्यथा
			पंचांगp &= ~B43_TMSLOW_MACPHYCLKEN;
		ssb_ग_लिखो32(dev->dev->sdev, SSB_TMSLOW, पंचांगp);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
पूर्ण

/* brcms_b_चयन_macfreq */
व्योम b43_mac_चयन_freq(काष्ठा b43_wldev *dev, u8 spurmode)
अणु
	u16 chip_id = dev->dev->chip_id;

	अगर (chip_id == BCMA_CHIP_ID_BCM4331) अणु
		चयन (spurmode) अणु
		हाल 2: /* 168 Mhz: 2^26/168 = 0x61862 */
			b43_ग_लिखो16(dev, B43_MMIO_TSF_CLK_FRAC_LOW, 0x1862);
			b43_ग_लिखो16(dev, B43_MMIO_TSF_CLK_FRAC_HIGH, 0x6);
			अवरोध;
		हाल 1: /* 164 Mhz: 2^26/164 = 0x63e70 */
			b43_ग_लिखो16(dev, B43_MMIO_TSF_CLK_FRAC_LOW, 0x3e70);
			b43_ग_लिखो16(dev, B43_MMIO_TSF_CLK_FRAC_HIGH, 0x6);
			अवरोध;
		शेष: /* 160 Mhz: 2^26/160 = 0x66666 */
			b43_ग_लिखो16(dev, B43_MMIO_TSF_CLK_FRAC_LOW, 0x6666);
			b43_ग_लिखो16(dev, B43_MMIO_TSF_CLK_FRAC_HIGH, 0x6);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (chip_id == BCMA_CHIP_ID_BCM43131 ||
	    chip_id == BCMA_CHIP_ID_BCM43217 ||
	    chip_id == BCMA_CHIP_ID_BCM43222 ||
	    chip_id == BCMA_CHIP_ID_BCM43224 ||
	    chip_id == BCMA_CHIP_ID_BCM43225 ||
	    chip_id == BCMA_CHIP_ID_BCM43227 ||
	    chip_id == BCMA_CHIP_ID_BCM43228) अणु
		चयन (spurmode) अणु
		हाल 2: /* 126 Mhz */
			b43_ग_लिखो16(dev, B43_MMIO_TSF_CLK_FRAC_LOW, 0x2082);
			b43_ग_लिखो16(dev, B43_MMIO_TSF_CLK_FRAC_HIGH, 0x8);
			अवरोध;
		हाल 1: /* 123 Mhz */
			b43_ग_लिखो16(dev, B43_MMIO_TSF_CLK_FRAC_LOW, 0x5341);
			b43_ग_लिखो16(dev, B43_MMIO_TSF_CLK_FRAC_HIGH, 0x8);
			अवरोध;
		शेष: /* 120 Mhz */
			b43_ग_लिखो16(dev, B43_MMIO_TSF_CLK_FRAC_LOW, 0x8889);
			b43_ग_लिखो16(dev, B43_MMIO_TSF_CLK_FRAC_HIGH, 0x8);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (dev->phy.type == B43_PHYTYPE_LCN) अणु
		चयन (spurmode) अणु
		हाल 1: /* 82 Mhz */
			b43_ग_लिखो16(dev, B43_MMIO_TSF_CLK_FRAC_LOW, 0x7CE0);
			b43_ग_लिखो16(dev, B43_MMIO_TSF_CLK_FRAC_HIGH, 0xC);
			अवरोध;
		शेष: /* 80 Mhz */
			b43_ग_लिखो16(dev, B43_MMIO_TSF_CLK_FRAC_LOW, 0xCCCD);
			b43_ग_लिखो16(dev, B43_MMIO_TSF_CLK_FRAC_HIGH, 0xC);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम b43_adjust_opmode(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_wl *wl = dev->wl;
	u32 ctl;
	u16 cfp_pretbtt;

	ctl = b43_पढ़ो32(dev, B43_MMIO_MACCTL);
	/* Reset status to STA infraकाष्ठाure mode. */
	ctl &= ~B43_MACCTL_AP;
	ctl &= ~B43_MACCTL_KEEP_CTL;
	ctl &= ~B43_MACCTL_KEEP_BADPLCP;
	ctl &= ~B43_MACCTL_KEEP_BAD;
	ctl &= ~B43_MACCTL_PROMISC;
	ctl &= ~B43_MACCTL_BEACPROMISC;
	ctl |= B43_MACCTL_INFRA;

	अगर (b43_is_mode(wl, NL80211_IFTYPE_AP) ||
	    b43_is_mode(wl, NL80211_IFTYPE_MESH_POINT))
		ctl |= B43_MACCTL_AP;
	अन्यथा अगर (b43_is_mode(wl, NL80211_IFTYPE_ADHOC))
		ctl &= ~B43_MACCTL_INFRA;

	अगर (wl->filter_flags & FIF_CONTROL)
		ctl |= B43_MACCTL_KEEP_CTL;
	अगर (wl->filter_flags & FIF_FCSFAIL)
		ctl |= B43_MACCTL_KEEP_BAD;
	अगर (wl->filter_flags & FIF_PLCPFAIL)
		ctl |= B43_MACCTL_KEEP_BADPLCP;
	अगर (wl->filter_flags & FIF_BCN_PRBRESP_PROMISC)
		ctl |= B43_MACCTL_BEACPROMISC;

	/* Workaround: On old hardware the HW-MAC-address-filter
	 * करोesn't work properly, so always run promisc in filter
	 * it in software. */
	अगर (dev->dev->core_rev <= 4)
		ctl |= B43_MACCTL_PROMISC;

	b43_ग_लिखो32(dev, B43_MMIO_MACCTL, ctl);

	cfp_pretbtt = 2;
	अगर ((ctl & B43_MACCTL_INFRA) && !(ctl & B43_MACCTL_AP)) अणु
		अगर (dev->dev->chip_id == 0x4306 &&
		    dev->dev->chip_rev == 3)
			cfp_pretbtt = 100;
		अन्यथा
			cfp_pretbtt = 50;
	पूर्ण
	b43_ग_लिखो16(dev, 0x612, cfp_pretbtt);

	/* FIXME: We करोn't currently implement the PMQ mechanism,
	 *        so always disable it. If we want to implement PMQ,
	 *        we need to enable it here (clear DISCPMQ) in AP mode.
	 */
	अगर (0  /* ctl & B43_MACCTL_AP */)
		b43_maskset32(dev, B43_MMIO_MACCTL, ~B43_MACCTL_DISCPMQ, 0);
	अन्यथा
		b43_maskset32(dev, B43_MMIO_MACCTL, ~0, B43_MACCTL_DISCPMQ);
पूर्ण

अटल व्योम b43_rate_memory_ग_लिखो(काष्ठा b43_wldev *dev, u16 rate, पूर्णांक is_ofdm)
अणु
	u16 offset;

	अगर (is_ofdm) अणु
		offset = 0x480;
		offset += (b43_plcp_get_ratecode_ofdm(rate) & 0x000F) * 2;
	पूर्ण अन्यथा अणु
		offset = 0x4C0;
		offset += (b43_plcp_get_ratecode_cck(rate) & 0x000F) * 2;
	पूर्ण
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, offset + 0x20,
			b43_shm_पढ़ो16(dev, B43_SHM_SHARED, offset));
पूर्ण

अटल व्योम b43_rate_memory_init(काष्ठा b43_wldev *dev)
अणु
	चयन (dev->phy.type) अणु
	हाल B43_PHYTYPE_G:
	हाल B43_PHYTYPE_N:
	हाल B43_PHYTYPE_LP:
	हाल B43_PHYTYPE_HT:
	हाल B43_PHYTYPE_LCN:
		b43_rate_memory_ग_लिखो(dev, B43_OFDM_RATE_6MB, 1);
		b43_rate_memory_ग_लिखो(dev, B43_OFDM_RATE_9MB, 1);
		b43_rate_memory_ग_लिखो(dev, B43_OFDM_RATE_12MB, 1);
		b43_rate_memory_ग_लिखो(dev, B43_OFDM_RATE_18MB, 1);
		b43_rate_memory_ग_लिखो(dev, B43_OFDM_RATE_24MB, 1);
		b43_rate_memory_ग_लिखो(dev, B43_OFDM_RATE_36MB, 1);
		b43_rate_memory_ग_लिखो(dev, B43_OFDM_RATE_48MB, 1);
		b43_rate_memory_ग_लिखो(dev, B43_OFDM_RATE_54MB, 1);
		fallthrough;
	हाल B43_PHYTYPE_B:
		b43_rate_memory_ग_लिखो(dev, B43_CCK_RATE_1MB, 0);
		b43_rate_memory_ग_लिखो(dev, B43_CCK_RATE_2MB, 0);
		b43_rate_memory_ग_लिखो(dev, B43_CCK_RATE_5MB, 0);
		b43_rate_memory_ग_लिखो(dev, B43_CCK_RATE_11MB, 0);
		अवरोध;
	शेष:
		B43_WARN_ON(1);
	पूर्ण
पूर्ण

/* Set the शेष values क्रम the PHY TX Control Words. */
अटल व्योम b43_set_phytxctl_शेषs(काष्ठा b43_wldev *dev)
अणु
	u16 ctl = 0;

	ctl |= B43_TXH_PHY_ENC_CCK;
	ctl |= B43_TXH_PHY_ANT01AUTO;
	ctl |= B43_TXH_PHY_TXPWR;

	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_BEACPHYCTL, ctl);
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_ACKCTSPHYCTL, ctl);
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_PRPHYCTL, ctl);
पूर्ण

/* Set the TX-Antenna क्रम management frames sent by firmware. */
अटल व्योम b43_mgmtframe_txantenna(काष्ठा b43_wldev *dev, पूर्णांक antenna)
अणु
	u16 ant;
	u16 पंचांगp;

	ant = b43_antenna_to_phyctl(antenna);

	/* For ACK/CTS */
	पंचांगp = b43_shm_पढ़ो16(dev, B43_SHM_SHARED, B43_SHM_SH_ACKCTSPHYCTL);
	पंचांगp = (पंचांगp & ~B43_TXH_PHY_ANT) | ant;
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_ACKCTSPHYCTL, पंचांगp);
	/* For Probe Resposes */
	पंचांगp = b43_shm_पढ़ो16(dev, B43_SHM_SHARED, B43_SHM_SH_PRPHYCTL);
	पंचांगp = (पंचांगp & ~B43_TXH_PHY_ANT) | ant;
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_PRPHYCTL, पंचांगp);
पूर्ण

/* This is the opposite of b43_chip_init() */
अटल व्योम b43_chip_निकास(काष्ठा b43_wldev *dev)
अणु
	b43_phy_निकास(dev);
	b43_gpio_cleanup(dev);
	/* firmware is released later */
पूर्ण

/* Initialize the chip
 * https://bcm-specs.sipsolutions.net/ChipInit
 */
अटल पूर्णांक b43_chip_init(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	पूर्णांक err;
	u32 macctl;
	u16 value16;

	/* Initialize the MAC control */
	macctl = B43_MACCTL_IHR_ENABLED | B43_MACCTL_SHM_ENABLED;
	अगर (dev->phy.gmode)
		macctl |= B43_MACCTL_GMODE;
	macctl |= B43_MACCTL_INFRA;
	b43_ग_लिखो32(dev, B43_MMIO_MACCTL, macctl);

	err = b43_upload_microcode(dev);
	अगर (err)
		जाओ out;	/* firmware is released later */

	err = b43_gpio_init(dev);
	अगर (err)
		जाओ out;	/* firmware is released later */

	err = b43_upload_initvals(dev);
	अगर (err)
		जाओ err_gpio_clean;

	err = b43_upload_initvals_band(dev);
	अगर (err)
		जाओ err_gpio_clean;

	/* Turn the Analog on and initialize the PHY. */
	phy->ops->चयन_analog(dev, 1);
	err = b43_phy_init(dev);
	अगर (err)
		जाओ err_gpio_clean;

	/* Disable Interference Mitigation. */
	अगर (phy->ops->पूर्णांकerf_mitigation)
		phy->ops->पूर्णांकerf_mitigation(dev, B43_INTERFMODE_NONE);

	/* Select the antennae */
	अगर (phy->ops->set_rx_antenna)
		phy->ops->set_rx_antenna(dev, B43_ANTENNA_DEFAULT);
	b43_mgmtframe_txantenna(dev, B43_ANTENNA_DEFAULT);

	अगर (phy->type == B43_PHYTYPE_B) अणु
		value16 = b43_पढ़ो16(dev, 0x005E);
		value16 |= 0x0004;
		b43_ग_लिखो16(dev, 0x005E, value16);
	पूर्ण
	b43_ग_लिखो32(dev, 0x0100, 0x01000000);
	अगर (dev->dev->core_rev < 5)
		b43_ग_लिखो32(dev, 0x010C, 0x01000000);

	b43_maskset32(dev, B43_MMIO_MACCTL, ~B43_MACCTL_INFRA, 0);
	b43_maskset32(dev, B43_MMIO_MACCTL, ~0, B43_MACCTL_INFRA);

	/* Probe Response Timeout value */
	/* FIXME: Default to 0, has to be set by ioctl probably... :-/ */
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_PRMAXTIME, 0);

	/* Initially set the wireless operation mode. */
	b43_adjust_opmode(dev);

	अगर (dev->dev->core_rev < 3) अणु
		b43_ग_लिखो16(dev, 0x060E, 0x0000);
		b43_ग_लिखो16(dev, 0x0610, 0x8000);
		b43_ग_लिखो16(dev, 0x0604, 0x0000);
		b43_ग_लिखो16(dev, 0x0606, 0x0200);
	पूर्ण अन्यथा अणु
		b43_ग_लिखो32(dev, 0x0188, 0x80000000);
		b43_ग_लिखो32(dev, 0x018C, 0x02000000);
	पूर्ण
	b43_ग_लिखो32(dev, B43_MMIO_GEN_IRQ_REASON, 0x00004000);
	b43_ग_लिखो32(dev, B43_MMIO_DMA0_IRQ_MASK, 0x0001FC00);
	b43_ग_लिखो32(dev, B43_MMIO_DMA1_IRQ_MASK, 0x0000DC00);
	b43_ग_लिखो32(dev, B43_MMIO_DMA2_IRQ_MASK, 0x0000DC00);
	b43_ग_लिखो32(dev, B43_MMIO_DMA3_IRQ_MASK, 0x0001DC00);
	b43_ग_लिखो32(dev, B43_MMIO_DMA4_IRQ_MASK, 0x0000DC00);
	b43_ग_लिखो32(dev, B43_MMIO_DMA5_IRQ_MASK, 0x0000DC00);

	b43_mac_phy_घड़ी_set(dev, true);

	चयन (dev->dev->bus_type) अणु
#अगर_घोषित CONFIG_B43_BCMA
	हाल B43_BUS_BCMA:
		/* FIXME: 0xE74 is quite common, but should be पढ़ो from CC */
		b43_ग_लिखो16(dev, B43_MMIO_POWERUP_DELAY, 0xE74);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SSB
	हाल B43_BUS_SSB:
		b43_ग_लिखो16(dev, B43_MMIO_POWERUP_DELAY,
			    dev->dev->sdev->bus->chipco.fast_pwrup_delay);
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	err = 0;
	b43dbg(dev->wl, "Chip initialized\n");
out:
	वापस err;

err_gpio_clean:
	b43_gpio_cleanup(dev);
	वापस err;
पूर्ण

अटल व्योम b43_periodic_every60sec(काष्ठा b43_wldev *dev)
अणु
	स्थिर काष्ठा b43_phy_operations *ops = dev->phy.ops;

	अगर (ops->pwork_60sec)
		ops->pwork_60sec(dev);

	/* Force check the TX घातer emission now. */
	b43_phy_txघातer_check(dev, B43_TXPWR_IGNORE_TIME);
पूर्ण

अटल व्योम b43_periodic_every30sec(काष्ठा b43_wldev *dev)
अणु
	/* Update device statistics. */
	b43_calculate_link_quality(dev);
पूर्ण

अटल व्योम b43_periodic_every15sec(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	u16 wdr;

	अगर (dev->fw.खोलोsource) अणु
		/* Check अगर the firmware is still alive.
		 * It will reset the watchकरोg counter to 0 in its idle loop. */
		wdr = b43_shm_पढ़ो16(dev, B43_SHM_SCRATCH, B43_WATCHDOG_REG);
		अगर (unlikely(wdr)) अणु
			b43err(dev->wl, "Firmware watchdog: The firmware died!\n");
			b43_controller_restart(dev, "Firmware watchdog");
			वापस;
		पूर्ण अन्यथा अणु
			b43_shm_ग_लिखो16(dev, B43_SHM_SCRATCH,
					B43_WATCHDOG_REG, 1);
		पूर्ण
	पूर्ण

	अगर (phy->ops->pwork_15sec)
		phy->ops->pwork_15sec(dev);

	atomic_set(&phy->txerr_cnt, B43_PHY_TX_BADNESS_LIMIT);
	wmb();

#अगर B43_DEBUG
	अगर (b43_debug(dev, B43_DBG_VERBOSESTATS)) अणु
		अचिन्हित पूर्णांक i;

		b43dbg(dev->wl, "Stats: %7u IRQs/sec, %7u TX/sec, %7u RX/sec\n",
		       dev->irq_count / 15,
		       dev->tx_count / 15,
		       dev->rx_count / 15);
		dev->irq_count = 0;
		dev->tx_count = 0;
		dev->rx_count = 0;
		क्रम (i = 0; i < ARRAY_SIZE(dev->irq_bit_count); i++) अणु
			अगर (dev->irq_bit_count[i]) अणु
				b43dbg(dev->wl, "Stats: %7u IRQ-%02u/sec (0x%08X)\n",
				       dev->irq_bit_count[i] / 15, i, (1 << i));
				dev->irq_bit_count[i] = 0;
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम करो_periodic_work(काष्ठा b43_wldev *dev)
अणु
	अचिन्हित पूर्णांक state;

	state = dev->periodic_state;
	अगर (state % 4 == 0)
		b43_periodic_every60sec(dev);
	अगर (state % 2 == 0)
		b43_periodic_every30sec(dev);
	b43_periodic_every15sec(dev);
पूर्ण

/* Periodic work locking policy:
 * 	The whole periodic work handler is रक्षित by
 * 	wl->mutex. If another lock is needed somewhere in the
 * 	pwork callchain, it's acquired in-place, where it's needed.
 */
अटल व्योम b43_periodic_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा b43_wldev *dev = container_of(work, काष्ठा b43_wldev,
					     periodic_work.work);
	काष्ठा b43_wl *wl = dev->wl;
	अचिन्हित दीर्घ delay;

	mutex_lock(&wl->mutex);

	अगर (unlikely(b43_status(dev) != B43_STAT_STARTED))
		जाओ out;
	अगर (b43_debug(dev, B43_DBG_PWORK_STOP))
		जाओ out_requeue;

	करो_periodic_work(dev);

	dev->periodic_state++;
out_requeue:
	अगर (b43_debug(dev, B43_DBG_PWORK_FAST))
		delay = msecs_to_jअगरfies(50);
	अन्यथा
		delay = round_jअगरfies_relative(HZ * 15);
	ieee80211_queue_delayed_work(wl->hw, &dev->periodic_work, delay);
out:
	mutex_unlock(&wl->mutex);
पूर्ण

अटल व्योम b43_periodic_tasks_setup(काष्ठा b43_wldev *dev)
अणु
	काष्ठा delayed_work *work = &dev->periodic_work;

	dev->periodic_state = 0;
	INIT_DELAYED_WORK(work, b43_periodic_work_handler);
	ieee80211_queue_delayed_work(dev->wl->hw, work, 0);
पूर्ण

/* Check अगर communication with the device works correctly. */
अटल पूर्णांक b43_validate_chipaccess(काष्ठा b43_wldev *dev)
अणु
	u32 v, backup0, backup4;

	backup0 = b43_shm_पढ़ो32(dev, B43_SHM_SHARED, 0);
	backup4 = b43_shm_पढ़ो32(dev, B43_SHM_SHARED, 4);

	/* Check क्रम पढ़ो/ग_लिखो and endianness problems. */
	b43_shm_ग_लिखो32(dev, B43_SHM_SHARED, 0, 0x55AAAA55);
	अगर (b43_shm_पढ़ो32(dev, B43_SHM_SHARED, 0) != 0x55AAAA55)
		जाओ error;
	b43_shm_ग_लिखो32(dev, B43_SHM_SHARED, 0, 0xAA5555AA);
	अगर (b43_shm_पढ़ो32(dev, B43_SHM_SHARED, 0) != 0xAA5555AA)
		जाओ error;

	/* Check अगर unaligned 32bit SHM_SHARED access works properly.
	 * However, करोn't bail out on failure, because it's noncritical. */
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, 0, 0x1122);
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, 2, 0x3344);
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, 4, 0x5566);
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, 6, 0x7788);
	अगर (b43_shm_पढ़ो32(dev, B43_SHM_SHARED, 2) != 0x55663344)
		b43warn(dev->wl, "Unaligned 32bit SHM read access is broken\n");
	b43_shm_ग_लिखो32(dev, B43_SHM_SHARED, 2, 0xAABBCCDD);
	अगर (b43_shm_पढ़ो16(dev, B43_SHM_SHARED, 0) != 0x1122 ||
	    b43_shm_पढ़ो16(dev, B43_SHM_SHARED, 2) != 0xCCDD ||
	    b43_shm_पढ़ो16(dev, B43_SHM_SHARED, 4) != 0xAABB ||
	    b43_shm_पढ़ो16(dev, B43_SHM_SHARED, 6) != 0x7788)
		b43warn(dev->wl, "Unaligned 32bit SHM write access is broken\n");

	b43_shm_ग_लिखो32(dev, B43_SHM_SHARED, 0, backup0);
	b43_shm_ग_लिखो32(dev, B43_SHM_SHARED, 4, backup4);

	अगर ((dev->dev->core_rev >= 3) && (dev->dev->core_rev <= 10)) अणु
		/* The 32bit रेजिस्टर shaकरोws the two 16bit रेजिस्टरs
		 * with update sideeffects. Validate this. */
		b43_ग_लिखो16(dev, B43_MMIO_TSF_CFP_START, 0xAAAA);
		b43_ग_लिखो32(dev, B43_MMIO_TSF_CFP_START, 0xCCCCBBBB);
		अगर (b43_पढ़ो16(dev, B43_MMIO_TSF_CFP_START_LOW) != 0xBBBB)
			जाओ error;
		अगर (b43_पढ़ो16(dev, B43_MMIO_TSF_CFP_START_HIGH) != 0xCCCC)
			जाओ error;
	पूर्ण
	b43_ग_लिखो32(dev, B43_MMIO_TSF_CFP_START, 0);

	v = b43_पढ़ो32(dev, B43_MMIO_MACCTL);
	v |= B43_MACCTL_GMODE;
	अगर (v != (B43_MACCTL_GMODE | B43_MACCTL_IHR_ENABLED))
		जाओ error;

	वापस 0;
error:
	b43err(dev->wl, "Failed to validate the chipaccess\n");
	वापस -ENODEV;
पूर्ण

अटल व्योम b43_security_init(काष्ठा b43_wldev *dev)
अणु
	dev->ktp = b43_shm_पढ़ो16(dev, B43_SHM_SHARED, B43_SHM_SH_KTP);
	/* KTP is a word address, but we address SHM bytewise.
	 * So multiply by two.
	 */
	dev->ktp *= 2;
	/* Number of RCMTA address slots */
	b43_ग_लिखो16(dev, B43_MMIO_RCMTA_COUNT, B43_NR_PAIRWISE_KEYS);
	/* Clear the key memory. */
	b43_clear_keys(dev);
पूर्ण

#अगर_घोषित CONFIG_B43_HWRNG
अटल पूर्णांक b43_rng_पढ़ो(काष्ठा hwrng *rng, u32 *data)
अणु
	काष्ठा b43_wl *wl = (काष्ठा b43_wl *)rng->priv;
	काष्ठा b43_wldev *dev;
	पूर्णांक count = -ENODEV;

	mutex_lock(&wl->mutex);
	dev = wl->current_dev;
	अगर (likely(dev && b43_status(dev) >= B43_STAT_INITIALIZED)) अणु
		*data = b43_पढ़ो16(dev, B43_MMIO_RNG);
		count = माप(u16);
	पूर्ण
	mutex_unlock(&wl->mutex);

	वापस count;
पूर्ण
#पूर्ण_अगर /* CONFIG_B43_HWRNG */

अटल व्योम b43_rng_निकास(काष्ठा b43_wl *wl)
अणु
#अगर_घोषित CONFIG_B43_HWRNG
	अगर (wl->rng_initialized)
		hwrng_unरेजिस्टर(&wl->rng);
#पूर्ण_अगर /* CONFIG_B43_HWRNG */
पूर्ण

अटल पूर्णांक b43_rng_init(काष्ठा b43_wl *wl)
अणु
	पूर्णांक err = 0;

#अगर_घोषित CONFIG_B43_HWRNG
	snम_लिखो(wl->rng_name, ARRAY_SIZE(wl->rng_name),
		 "%s_%s", KBUILD_MODNAME, wiphy_name(wl->hw->wiphy));
	wl->rng.name = wl->rng_name;
	wl->rng.data_पढ़ो = b43_rng_पढ़ो;
	wl->rng.priv = (अचिन्हित दीर्घ)wl;
	wl->rng_initialized = true;
	err = hwrng_रेजिस्टर(&wl->rng);
	अगर (err) अणु
		wl->rng_initialized = false;
		b43err(wl, "Failed to register the random "
		       "number generator (%d)\n", err);
	पूर्ण
#पूर्ण_अगर /* CONFIG_B43_HWRNG */

	वापस err;
पूर्ण

अटल व्योम b43_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा b43_wl *wl = container_of(work, काष्ठा b43_wl, tx_work);
	काष्ठा b43_wldev *dev;
	काष्ठा sk_buff *skb;
	पूर्णांक queue_num;
	पूर्णांक err = 0;

	mutex_lock(&wl->mutex);
	dev = wl->current_dev;
	अगर (unlikely(!dev || b43_status(dev) < B43_STAT_STARTED)) अणु
		mutex_unlock(&wl->mutex);
		वापस;
	पूर्ण

	क्रम (queue_num = 0; queue_num < B43_QOS_QUEUE_NUM; queue_num++) अणु
		जबतक (skb_queue_len(&wl->tx_queue[queue_num])) अणु
			skb = skb_dequeue(&wl->tx_queue[queue_num]);
			अगर (b43_using_pio_transfers(dev))
				err = b43_pio_tx(dev, skb);
			अन्यथा
				err = b43_dma_tx(dev, skb);
			अगर (err == -ENOSPC) अणु
				wl->tx_queue_stopped[queue_num] = true;
				ieee80211_stop_queue(wl->hw, queue_num);
				skb_queue_head(&wl->tx_queue[queue_num], skb);
				अवरोध;
			पूर्ण
			अगर (unlikely(err))
				ieee80211_मुक्त_txskb(wl->hw, skb);
			err = 0;
		पूर्ण

		अगर (!err)
			wl->tx_queue_stopped[queue_num] = false;
	पूर्ण

#अगर B43_DEBUG
	dev->tx_count++;
#पूर्ण_अगर
	mutex_unlock(&wl->mutex);
पूर्ण

अटल व्योम b43_op_tx(काष्ठा ieee80211_hw *hw,
		      काष्ठा ieee80211_tx_control *control,
		      काष्ठा sk_buff *skb)
अणु
	काष्ठा b43_wl *wl = hw_to_b43_wl(hw);

	अगर (unlikely(skb->len < 2 + 2 + 6)) अणु
		/* Too लघु, this can't be a valid frame. */
		ieee80211_मुक्त_txskb(hw, skb);
		वापस;
	पूर्ण
	B43_WARN_ON(skb_shinfo(skb)->nr_frags);

	skb_queue_tail(&wl->tx_queue[skb->queue_mapping], skb);
	अगर (!wl->tx_queue_stopped[skb->queue_mapping]) अणु
		ieee80211_queue_work(wl->hw, &wl->tx_work);
	पूर्ण अन्यथा अणु
		ieee80211_stop_queue(wl->hw, skb->queue_mapping);
	पूर्ण
पूर्ण

अटल व्योम b43_qos_params_upload(काष्ठा b43_wldev *dev,
				  स्थिर काष्ठा ieee80211_tx_queue_params *p,
				  u16 shm_offset)
अणु
	u16 params[B43_NR_QOSPARAMS];
	पूर्णांक bslots, पंचांगp;
	अचिन्हित पूर्णांक i;

	अगर (!dev->qos_enabled)
		वापस;

	bslots = b43_पढ़ो16(dev, B43_MMIO_RNG) & p->cw_min;

	स_रखो(&params, 0, माप(params));

	params[B43_QOSPARAM_TXOP] = p->txop * 32;
	params[B43_QOSPARAM_CWMIN] = p->cw_min;
	params[B43_QOSPARAM_CWMAX] = p->cw_max;
	params[B43_QOSPARAM_CWCUR] = p->cw_min;
	params[B43_QOSPARAM_AIFS] = p->aअगरs;
	params[B43_QOSPARAM_BSLOTS] = bslots;
	params[B43_QOSPARAM_REGGAP] = bslots + p->aअगरs;

	क्रम (i = 0; i < ARRAY_SIZE(params); i++) अणु
		अगर (i == B43_QOSPARAM_STATUS) अणु
			पंचांगp = b43_shm_पढ़ो16(dev, B43_SHM_SHARED,
					     shm_offset + (i * 2));
			/* Mark the parameters as updated. */
			पंचांगp |= 0x100;
			b43_shm_ग_लिखो16(dev, B43_SHM_SHARED,
					shm_offset + (i * 2),
					पंचांगp);
		पूर्ण अन्यथा अणु
			b43_shm_ग_लिखो16(dev, B43_SHM_SHARED,
					shm_offset + (i * 2),
					params[i]);
		पूर्ण
	पूर्ण
पूर्ण

/* Mapping of mac80211 queue numbers to b43 QoS SHM offsets. */
अटल स्थिर u16 b43_qos_shm_offsets[] = अणु
	/* [mac80211-queue-nr] = SHM_OFFSET, */
	[0] = B43_QOS_VOICE,
	[1] = B43_QOS_VIDEO,
	[2] = B43_QOS_BESTEFFORT,
	[3] = B43_QOS_BACKGROUND,
पूर्ण;

/* Update all QOS parameters in hardware. */
अटल व्योम b43_qos_upload_all(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_wl *wl = dev->wl;
	काष्ठा b43_qos_params *params;
	अचिन्हित पूर्णांक i;

	अगर (!dev->qos_enabled)
		वापस;

	BUILD_BUG_ON(ARRAY_SIZE(b43_qos_shm_offsets) !=
		     ARRAY_SIZE(wl->qos_params));

	b43_mac_suspend(dev);
	क्रम (i = 0; i < ARRAY_SIZE(wl->qos_params); i++) अणु
		params = &(wl->qos_params[i]);
		b43_qos_params_upload(dev, &(params->p),
				      b43_qos_shm_offsets[i]);
	पूर्ण
	b43_mac_enable(dev);
पूर्ण

अटल व्योम b43_qos_clear(काष्ठा b43_wl *wl)
अणु
	काष्ठा b43_qos_params *params;
	अचिन्हित पूर्णांक i;

	/* Initialize QoS parameters to sane शेषs. */

	BUILD_BUG_ON(ARRAY_SIZE(b43_qos_shm_offsets) !=
		     ARRAY_SIZE(wl->qos_params));

	क्रम (i = 0; i < ARRAY_SIZE(wl->qos_params); i++) अणु
		params = &(wl->qos_params[i]);

		चयन (b43_qos_shm_offsets[i]) अणु
		हाल B43_QOS_VOICE:
			params->p.txop = 0;
			params->p.aअगरs = 2;
			params->p.cw_min = 0x0001;
			params->p.cw_max = 0x0001;
			अवरोध;
		हाल B43_QOS_VIDEO:
			params->p.txop = 0;
			params->p.aअगरs = 2;
			params->p.cw_min = 0x0001;
			params->p.cw_max = 0x0001;
			अवरोध;
		हाल B43_QOS_BESTEFFORT:
			params->p.txop = 0;
			params->p.aअगरs = 3;
			params->p.cw_min = 0x0001;
			params->p.cw_max = 0x03FF;
			अवरोध;
		हाल B43_QOS_BACKGROUND:
			params->p.txop = 0;
			params->p.aअगरs = 7;
			params->p.cw_min = 0x0001;
			params->p.cw_max = 0x03FF;
			अवरोध;
		शेष:
			B43_WARN_ON(1);
		पूर्ण
	पूर्ण
पूर्ण

/* Initialize the core's QOS capabilities */
अटल व्योम b43_qos_init(काष्ठा b43_wldev *dev)
अणु
	अगर (!dev->qos_enabled) अणु
		/* Disable QOS support. */
		b43_hf_ग_लिखो(dev, b43_hf_पढ़ो(dev) & ~B43_HF_EDCF);
		b43_ग_लिखो16(dev, B43_MMIO_IFSCTL,
			    b43_पढ़ो16(dev, B43_MMIO_IFSCTL)
			    & ~B43_MMIO_IFSCTL_USE_EDCF);
		b43dbg(dev->wl, "QoS disabled\n");
		वापस;
	पूर्ण

	/* Upload the current QOS parameters. */
	b43_qos_upload_all(dev);

	/* Enable QOS support. */
	b43_hf_ग_लिखो(dev, b43_hf_पढ़ो(dev) | B43_HF_EDCF);
	b43_ग_लिखो16(dev, B43_MMIO_IFSCTL,
		    b43_पढ़ो16(dev, B43_MMIO_IFSCTL)
		    | B43_MMIO_IFSCTL_USE_EDCF);
	b43dbg(dev->wl, "QoS enabled\n");
पूर्ण

अटल पूर्णांक b43_op_conf_tx(काष्ठा ieee80211_hw *hw,
			  काष्ठा ieee80211_vअगर *vअगर, u16 _queue,
			  स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा b43_wl *wl = hw_to_b43_wl(hw);
	काष्ठा b43_wldev *dev;
	अचिन्हित पूर्णांक queue = (अचिन्हित पूर्णांक)_queue;
	पूर्णांक err = -ENODEV;

	अगर (queue >= ARRAY_SIZE(wl->qos_params)) अणु
		/* Queue not available or करोn't support setting
		 * params on this queue. Return success to not
		 * confuse mac80211. */
		वापस 0;
	पूर्ण
	BUILD_BUG_ON(ARRAY_SIZE(b43_qos_shm_offsets) !=
		     ARRAY_SIZE(wl->qos_params));

	mutex_lock(&wl->mutex);
	dev = wl->current_dev;
	अगर (unlikely(!dev || (b43_status(dev) < B43_STAT_INITIALIZED)))
		जाओ out_unlock;

	स_नकल(&(wl->qos_params[queue].p), params, माप(*params));
	b43_mac_suspend(dev);
	b43_qos_params_upload(dev, &(wl->qos_params[queue].p),
			      b43_qos_shm_offsets[queue]);
	b43_mac_enable(dev);
	err = 0;

out_unlock:
	mutex_unlock(&wl->mutex);

	वापस err;
पूर्ण

अटल पूर्णांक b43_op_get_stats(काष्ठा ieee80211_hw *hw,
			    काष्ठा ieee80211_low_level_stats *stats)
अणु
	काष्ठा b43_wl *wl = hw_to_b43_wl(hw);

	mutex_lock(&wl->mutex);
	स_नकल(stats, &wl->ieee_stats, माप(*stats));
	mutex_unlock(&wl->mutex);

	वापस 0;
पूर्ण

अटल u64 b43_op_get_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा b43_wl *wl = hw_to_b43_wl(hw);
	काष्ठा b43_wldev *dev;
	u64 tsf;

	mutex_lock(&wl->mutex);
	dev = wl->current_dev;

	अगर (dev && (b43_status(dev) >= B43_STAT_INITIALIZED))
		b43_tsf_पढ़ो(dev, &tsf);
	अन्यथा
		tsf = 0;

	mutex_unlock(&wl->mutex);

	वापस tsf;
पूर्ण

अटल व्योम b43_op_set_tsf(काष्ठा ieee80211_hw *hw,
			   काष्ठा ieee80211_vअगर *vअगर, u64 tsf)
अणु
	काष्ठा b43_wl *wl = hw_to_b43_wl(hw);
	काष्ठा b43_wldev *dev;

	mutex_lock(&wl->mutex);
	dev = wl->current_dev;

	अगर (dev && (b43_status(dev) >= B43_STAT_INITIALIZED))
		b43_tsf_ग_लिखो(dev, tsf);

	mutex_unlock(&wl->mutex);
पूर्ण

अटल स्थिर अक्षर *band_to_string(क्रमागत nl80211_band band)
अणु
	चयन (band) अणु
	हाल NL80211_BAND_5GHZ:
		वापस "5";
	हाल NL80211_BAND_2GHZ:
		वापस "2.4";
	शेष:
		अवरोध;
	पूर्ण
	B43_WARN_ON(1);
	वापस "";
पूर्ण

/* Expects wl->mutex locked */
अटल पूर्णांक b43_चयन_band(काष्ठा b43_wldev *dev,
			   काष्ठा ieee80211_channel *chan)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	bool gmode;
	u32 पंचांगp;

	चयन (chan->band) अणु
	हाल NL80211_BAND_5GHZ:
		gmode = false;
		अवरोध;
	हाल NL80211_BAND_2GHZ:
		gmode = true;
		अवरोध;
	शेष:
		B43_WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	अगर (!((gmode && phy->supports_2ghz) ||
	      (!gmode && phy->supports_5ghz))) अणु
		b43err(dev->wl, "This device doesn't support %s-GHz band\n",
		       band_to_string(chan->band));
		वापस -ENODEV;
	पूर्ण

	अगर (!!phy->gmode == !!gmode) अणु
		/* This device is alपढ़ोy running. */
		वापस 0;
	पूर्ण

	b43dbg(dev->wl, "Switching to %s GHz band\n",
	       band_to_string(chan->band));

	/* Some new devices करोn't need disabling radio क्रम band चयनing */
	अगर (!(phy->type == B43_PHYTYPE_N && phy->rev >= 3))
		b43_software_rfसमाप्त(dev, true);

	phy->gmode = gmode;
	b43_phy_put_पूर्णांकo_reset(dev);
	चयन (dev->dev->bus_type) अणु
#अगर_घोषित CONFIG_B43_BCMA
	हाल B43_BUS_BCMA:
		पंचांगp = bcma_aपढ़ो32(dev->dev->bdev, BCMA_IOCTL);
		अगर (gmode)
			पंचांगp |= B43_BCMA_IOCTL_GMODE;
		अन्यथा
			पंचांगp &= ~B43_BCMA_IOCTL_GMODE;
		bcma_aग_लिखो32(dev->dev->bdev, BCMA_IOCTL, पंचांगp);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SSB
	हाल B43_BUS_SSB:
		पंचांगp = ssb_पढ़ो32(dev->dev->sdev, SSB_TMSLOW);
		अगर (gmode)
			पंचांगp |= B43_TMSLOW_GMODE;
		अन्यथा
			पंचांगp &= ~B43_TMSLOW_GMODE;
		ssb_ग_लिखो32(dev->dev->sdev, SSB_TMSLOW, पंचांगp);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
	b43_phy_take_out_of_reset(dev);

	b43_upload_initvals_band(dev);

	b43_phy_init(dev);

	वापस 0;
पूर्ण

अटल व्योम b43_set_beacon_listen_पूर्णांकerval(काष्ठा b43_wldev *dev, u16 पूर्णांकerval)
अणु
	पूर्णांकerval = min_t(u16, पूर्णांकerval, (u16)0xFF);
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_BCN_LI, पूर्णांकerval);
पूर्ण

/* Write the लघु and दीर्घ frame retry limit values. */
अटल व्योम b43_set_retry_limits(काष्ठा b43_wldev *dev,
				 अचिन्हित पूर्णांक लघु_retry,
				 अचिन्हित पूर्णांक दीर्घ_retry)
अणु
	/* The retry limit is a 4-bit counter. Enक्रमce this to aव्योम overflowing
	 * the chip-पूर्णांकernal counter. */
	लघु_retry = min(लघु_retry, (अचिन्हित पूर्णांक)0xF);
	दीर्घ_retry = min(दीर्घ_retry, (अचिन्हित पूर्णांक)0xF);

	b43_shm_ग_लिखो16(dev, B43_SHM_SCRATCH, B43_SHM_SC_SRLIMIT,
			लघु_retry);
	b43_shm_ग_लिखो16(dev, B43_SHM_SCRATCH, B43_SHM_SC_LRLIMIT,
			दीर्घ_retry);
पूर्ण

अटल पूर्णांक b43_op_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा b43_wl *wl = hw_to_b43_wl(hw);
	काष्ठा b43_wldev *dev = wl->current_dev;
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा ieee80211_conf *conf = &hw->conf;
	पूर्णांक antenna;
	पूर्णांक err = 0;

	mutex_lock(&wl->mutex);
	b43_mac_suspend(dev);

	अगर (changed & IEEE80211_CONF_CHANGE_LISTEN_INTERVAL)
		b43_set_beacon_listen_पूर्णांकerval(dev, conf->listen_पूर्णांकerval);

	अगर (changed & IEEE80211_CONF_CHANGE_CHANNEL) अणु
		phy->chandef = &conf->chandef;
		phy->channel = conf->chandef.chan->hw_value;

		/* Switch the band (अगर necessary). */
		err = b43_चयन_band(dev, conf->chandef.chan);
		अगर (err)
			जाओ out_mac_enable;

		/* Switch to the requested channel.
		 * The firmware takes care of races with the TX handler.
		 */
		b43_चयन_channel(dev, phy->channel);
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_RETRY_LIMITS)
		b43_set_retry_limits(dev, conf->लघु_frame_max_tx_count,
					  conf->दीर्घ_frame_max_tx_count);
	changed &= ~IEEE80211_CONF_CHANGE_RETRY_LIMITS;
	अगर (!changed)
		जाओ out_mac_enable;

	dev->wl->radiotap_enabled = !!(conf->flags & IEEE80211_CONF_MONITOR);

	/* Adjust the desired TX घातer level. */
	अगर (conf->घातer_level != 0) अणु
		अगर (conf->घातer_level != phy->desired_txघातer) अणु
			phy->desired_txघातer = conf->घातer_level;
			b43_phy_txघातer_check(dev, B43_TXPWR_IGNORE_TIME |
						   B43_TXPWR_IGNORE_TSSI);
		पूर्ण
	पूर्ण

	/* Antennas क्रम RX and management frame TX. */
	antenna = B43_ANTENNA_DEFAULT;
	b43_mgmtframe_txantenna(dev, antenna);
	antenna = B43_ANTENNA_DEFAULT;
	अगर (phy->ops->set_rx_antenna)
		phy->ops->set_rx_antenna(dev, antenna);

	अगर (wl->radio_enabled != phy->radio_on) अणु
		अगर (wl->radio_enabled) अणु
			b43_software_rfसमाप्त(dev, false);
			b43info(dev->wl, "Radio turned on by software\n");
			अगर (!dev->radio_hw_enable) अणु
				b43info(dev->wl, "The hardware RF-kill button "
					"still turns the radio physically off. "
					"Press the button to turn it on.\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			b43_software_rfसमाप्त(dev, true);
			b43info(dev->wl, "Radio turned off by software\n");
		पूर्ण
	पूर्ण

out_mac_enable:
	b43_mac_enable(dev);
	mutex_unlock(&wl->mutex);

	वापस err;
पूर्ण

अटल व्योम b43_update_basic_rates(काष्ठा b43_wldev *dev, u32 brates)
अणु
	काष्ठा ieee80211_supported_band *sband =
		dev->wl->hw->wiphy->bands[b43_current_band(dev->wl)];
	स्थिर काष्ठा ieee80211_rate *rate;
	पूर्णांक i;
	u16 basic, direct, offset, basic_offset, rateptr;

	क्रम (i = 0; i < sband->n_bitrates; i++) अणु
		rate = &sband->bitrates[i];

		अगर (b43_is_cck_rate(rate->hw_value)) अणु
			direct = B43_SHM_SH_CCKसूचीECT;
			basic = B43_SHM_SH_CCKBASIC;
			offset = b43_plcp_get_ratecode_cck(rate->hw_value);
			offset &= 0xF;
		पूर्ण अन्यथा अणु
			direct = B43_SHM_SH_OFDMसूचीECT;
			basic = B43_SHM_SH_OFDMBASIC;
			offset = b43_plcp_get_ratecode_ofdm(rate->hw_value);
			offset &= 0xF;
		पूर्ण

		rate = ieee80211_get_response_rate(sband, brates, rate->bitrate);

		अगर (b43_is_cck_rate(rate->hw_value)) अणु
			basic_offset = b43_plcp_get_ratecode_cck(rate->hw_value);
			basic_offset &= 0xF;
		पूर्ण अन्यथा अणु
			basic_offset = b43_plcp_get_ratecode_ofdm(rate->hw_value);
			basic_offset &= 0xF;
		पूर्ण

		/*
		 * Get the poपूर्णांकer that we need to poपूर्णांक to
		 * from the direct map
		 */
		rateptr = b43_shm_पढ़ो16(dev, B43_SHM_SHARED,
					 direct + 2 * basic_offset);
		/* and ग_लिखो it to the basic map */
		b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, basic + 2 * offset,
				rateptr);
	पूर्ण
पूर्ण

अटल व्योम b43_op_bss_info_changed(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_bss_conf *conf,
				    u32 changed)
अणु
	काष्ठा b43_wl *wl = hw_to_b43_wl(hw);
	काष्ठा b43_wldev *dev;

	mutex_lock(&wl->mutex);

	dev = wl->current_dev;
	अगर (!dev || b43_status(dev) < B43_STAT_STARTED)
		जाओ out_unlock_mutex;

	B43_WARN_ON(wl->vअगर != vअगर);

	अगर (changed & BSS_CHANGED_BSSID) अणु
		अगर (conf->bssid)
			स_नकल(wl->bssid, conf->bssid, ETH_ALEN);
		अन्यथा
			eth_zero_addr(wl->bssid);
	पूर्ण

	अगर (b43_status(dev) >= B43_STAT_INITIALIZED) अणु
		अगर (changed & BSS_CHANGED_BEACON &&
		    (b43_is_mode(wl, NL80211_IFTYPE_AP) ||
		     b43_is_mode(wl, NL80211_IFTYPE_MESH_POINT) ||
		     b43_is_mode(wl, NL80211_IFTYPE_ADHOC)))
			b43_update_ढाँचाs(wl);

		अगर (changed & BSS_CHANGED_BSSID)
			b43_ग_लिखो_mac_bssid_ढाँचाs(dev);
	पूर्ण

	b43_mac_suspend(dev);

	/* Update ढाँचाs क्रम AP/mesh mode. */
	अगर (changed & BSS_CHANGED_BEACON_INT &&
	    (b43_is_mode(wl, NL80211_IFTYPE_AP) ||
	     b43_is_mode(wl, NL80211_IFTYPE_MESH_POINT) ||
	     b43_is_mode(wl, NL80211_IFTYPE_ADHOC)) &&
	    conf->beacon_पूर्णांक)
		b43_set_beacon_पूर्णांक(dev, conf->beacon_पूर्णांक);

	अगर (changed & BSS_CHANGED_BASIC_RATES)
		b43_update_basic_rates(dev, conf->basic_rates);

	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		अगर (conf->use_लघु_slot)
			b43_लघु_slot_timing_enable(dev);
		अन्यथा
			b43_लघु_slot_timing_disable(dev);
	पूर्ण

	b43_mac_enable(dev);
out_unlock_mutex:
	mutex_unlock(&wl->mutex);
पूर्ण

अटल पूर्णांक b43_op_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
			  काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
			  काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा b43_wl *wl = hw_to_b43_wl(hw);
	काष्ठा b43_wldev *dev;
	u8 algorithm;
	u8 index;
	पूर्णांक err;
	अटल स्थिर u8 bcast_addr[ETH_ALEN] = अणु 0xff, 0xff, 0xff, 0xff, 0xff, 0xff पूर्ण;

	अगर (modparam_nohwcrypt)
		वापस -ENOSPC; /* User disabled HW-crypto */

	अगर ((vअगर->type == NL80211_IFTYPE_ADHOC ||
	     vअगर->type == NL80211_IFTYPE_MESH_POINT) &&
	    (key->cipher == WLAN_CIPHER_SUITE_TKIP ||
	     key->cipher == WLAN_CIPHER_SUITE_CCMP) &&
	    !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE)) अणु
		/*
		 * For now, disable hw crypto क्रम the RSN IBSS group keys. This
		 * could be optimized in the future, but until that माला_लो
		 * implemented, use of software crypto क्रम group addressed
		 * frames is a acceptable to allow RSN IBSS to be used.
		 */
		वापस -EOPNOTSUPP;
	पूर्ण

	mutex_lock(&wl->mutex);

	dev = wl->current_dev;
	err = -ENODEV;
	अगर (!dev || b43_status(dev) < B43_STAT_INITIALIZED)
		जाओ out_unlock;

	अगर (dev->fw.pcm_request_failed || !dev->hwcrypto_enabled) अणु
		/* We करोn't have firmware क्रम the crypto engine.
		 * Must use software-crypto. */
		err = -EOPNOTSUPP;
		जाओ out_unlock;
	पूर्ण

	err = -EINVAL;
	चयन (key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
		algorithm = B43_SEC_ALGO_WEP40;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_WEP104:
		algorithm = B43_SEC_ALGO_WEP104;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		algorithm = B43_SEC_ALGO_TKIP;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		algorithm = B43_SEC_ALGO_AES;
		अवरोध;
	शेष:
		B43_WARN_ON(1);
		जाओ out_unlock;
	पूर्ण
	index = (u8) (key->keyidx);
	अगर (index > 3)
		जाओ out_unlock;

	चयन (cmd) अणु
	हाल SET_KEY:
		अगर (algorithm == B43_SEC_ALGO_TKIP &&
		    (!(key->flags & IEEE80211_KEY_FLAG_PAIRWISE) ||
		    !modparam_hwtkip)) अणु
			/* We support only pairwise key */
			err = -EOPNOTSUPP;
			जाओ out_unlock;
		पूर्ण

		अगर (key->flags & IEEE80211_KEY_FLAG_PAIRWISE) अणु
			अगर (WARN_ON(!sta)) अणु
				err = -EOPNOTSUPP;
				जाओ out_unlock;
			पूर्ण
			/* Pairwise key with an asचिन्हित MAC address. */
			err = b43_key_ग_लिखो(dev, -1, algorithm,
					    key->key, key->keylen,
					    sta->addr, key);
		पूर्ण अन्यथा अणु
			/* Group key */
			err = b43_key_ग_लिखो(dev, index, algorithm,
					    key->key, key->keylen, शून्य, key);
		पूर्ण
		अगर (err)
			जाओ out_unlock;

		अगर (algorithm == B43_SEC_ALGO_WEP40 ||
		    algorithm == B43_SEC_ALGO_WEP104) अणु
			b43_hf_ग_लिखो(dev, b43_hf_पढ़ो(dev) | B43_HF_USEDEFKEYS);
		पूर्ण अन्यथा अणु
			b43_hf_ग_लिखो(dev,
				     b43_hf_पढ़ो(dev) & ~B43_HF_USEDEFKEYS);
		पूर्ण
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
		अगर (algorithm == B43_SEC_ALGO_TKIP)
			key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIC;
		अवरोध;
	हाल DISABLE_KEY: अणु
		err = b43_key_clear(dev, key->hw_key_idx);
		अगर (err)
			जाओ out_unlock;
		अवरोध;
	पूर्ण
	शेष:
		B43_WARN_ON(1);
	पूर्ण

out_unlock:
	अगर (!err) अणु
		b43dbg(wl, "%s hardware based encryption for keyidx: %d, "
		       "mac: %pM\n",
		       cmd == SET_KEY ? "Using" : "Disabling", key->keyidx,
		       sta ? sta->addr : bcast_addr);
		b43_dump_keymemory(dev);
	पूर्ण
	mutex_unlock(&wl->mutex);

	वापस err;
पूर्ण

अटल व्योम b43_op_configure_filter(काष्ठा ieee80211_hw *hw,
				    अचिन्हित पूर्णांक changed, अचिन्हित पूर्णांक *fflags,
				    u64 multicast)
अणु
	काष्ठा b43_wl *wl = hw_to_b43_wl(hw);
	काष्ठा b43_wldev *dev;

	mutex_lock(&wl->mutex);
	dev = wl->current_dev;
	अगर (!dev) अणु
		*fflags = 0;
		जाओ out_unlock;
	पूर्ण

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

	अगर (changed && b43_status(dev) >= B43_STAT_INITIALIZED)
		b43_adjust_opmode(dev);

out_unlock:
	mutex_unlock(&wl->mutex);
पूर्ण

/* Locking: wl->mutex
 * Returns the current dev. This might be dअगरferent from the passed in dev,
 * because the core might be gone away जबतक we unlocked the mutex. */
अटल काष्ठा b43_wldev * b43_wireless_core_stop(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_wl *wl;
	काष्ठा b43_wldev *orig_dev;
	u32 mask;
	पूर्णांक queue_num;

	अगर (!dev)
		वापस शून्य;
	wl = dev->wl;
reकरो:
	अगर (!dev || b43_status(dev) < B43_STAT_STARTED)
		वापस dev;

	/* Cancel work. Unlock to aव्योम deadlocks. */
	mutex_unlock(&wl->mutex);
	cancel_delayed_work_sync(&dev->periodic_work);
	cancel_work_sync(&wl->tx_work);
	b43_leds_stop(dev);
	mutex_lock(&wl->mutex);
	dev = wl->current_dev;
	अगर (!dev || b43_status(dev) < B43_STAT_STARTED) अणु
		/* Whoops, aliens ate up the device जबतक we were unlocked. */
		वापस dev;
	पूर्ण

	/* Disable पूर्णांकerrupts on the device. */
	b43_set_status(dev, B43_STAT_INITIALIZED);
	अगर (b43_bus_host_is_sdio(dev->dev)) अणु
		/* wl->mutex is locked. That is enough. */
		b43_ग_लिखो32(dev, B43_MMIO_GEN_IRQ_MASK, 0);
		b43_पढ़ो32(dev, B43_MMIO_GEN_IRQ_MASK);	/* Flush */
	पूर्ण अन्यथा अणु
		spin_lock_irq(&wl->hardirq_lock);
		b43_ग_लिखो32(dev, B43_MMIO_GEN_IRQ_MASK, 0);
		b43_पढ़ो32(dev, B43_MMIO_GEN_IRQ_MASK);	/* Flush */
		spin_unlock_irq(&wl->hardirq_lock);
	पूर्ण
	/* Synchronize and मुक्त the पूर्णांकerrupt handlers. Unlock to aव्योम deadlocks. */
	orig_dev = dev;
	mutex_unlock(&wl->mutex);
	अगर (b43_bus_host_is_sdio(dev->dev))
		b43_sdio_मुक्त_irq(dev);
	अन्यथा
		मुक्त_irq(dev->dev->irq, dev);
	mutex_lock(&wl->mutex);
	dev = wl->current_dev;
	अगर (!dev)
		वापस dev;
	अगर (dev != orig_dev) अणु
		अगर (b43_status(dev) >= B43_STAT_STARTED)
			जाओ reकरो;
		वापस dev;
	पूर्ण
	mask = b43_पढ़ो32(dev, B43_MMIO_GEN_IRQ_MASK);
	B43_WARN_ON(mask != 0xFFFFFFFF && mask);

	/* Drain all TX queues. */
	क्रम (queue_num = 0; queue_num < B43_QOS_QUEUE_NUM; queue_num++) अणु
		जबतक (skb_queue_len(&wl->tx_queue[queue_num])) अणु
			काष्ठा sk_buff *skb;

			skb = skb_dequeue(&wl->tx_queue[queue_num]);
			ieee80211_मुक्त_txskb(wl->hw, skb);
		पूर्ण
	पूर्ण

	b43_mac_suspend(dev);
	b43_leds_निकास(dev);
	b43dbg(wl, "Wireless interface stopped\n");

	वापस dev;
पूर्ण

/* Locking: wl->mutex */
अटल पूर्णांक b43_wireless_core_start(काष्ठा b43_wldev *dev)
अणु
	पूर्णांक err;

	B43_WARN_ON(b43_status(dev) != B43_STAT_INITIALIZED);

	drain_txstatus_queue(dev);
	अगर (b43_bus_host_is_sdio(dev->dev)) अणु
		err = b43_sdio_request_irq(dev, b43_sdio_पूर्णांकerrupt_handler);
		अगर (err) अणु
			b43err(dev->wl, "Cannot request SDIO IRQ\n");
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = request_thपढ़ोed_irq(dev->dev->irq, b43_पूर्णांकerrupt_handler,
					   b43_पूर्णांकerrupt_thपढ़ो_handler,
					   IRQF_SHARED, KBUILD_MODNAME, dev);
		अगर (err) अणु
			b43err(dev->wl, "Cannot request IRQ-%d\n",
			       dev->dev->irq);
			जाओ out;
		पूर्ण
	पूर्ण

	/* We are पढ़ोy to run. */
	ieee80211_wake_queues(dev->wl->hw);
	b43_set_status(dev, B43_STAT_STARTED);

	/* Start data flow (TX/RX). */
	b43_mac_enable(dev);
	b43_ग_लिखो32(dev, B43_MMIO_GEN_IRQ_MASK, dev->irq_mask);

	/* Start मुख्यtenance work */
	b43_periodic_tasks_setup(dev);

	b43_leds_init(dev);

	b43dbg(dev->wl, "Wireless interface started\n");
out:
	वापस err;
पूर्ण

अटल अक्षर *b43_phy_name(काष्ठा b43_wldev *dev, u8 phy_type)
अणु
	चयन (phy_type) अणु
	हाल B43_PHYTYPE_A:
		वापस "A";
	हाल B43_PHYTYPE_B:
		वापस "B";
	हाल B43_PHYTYPE_G:
		वापस "G";
	हाल B43_PHYTYPE_N:
		वापस "N";
	हाल B43_PHYTYPE_LP:
		वापस "LP";
	हाल B43_PHYTYPE_SSLPN:
		वापस "SSLPN";
	हाल B43_PHYTYPE_HT:
		वापस "HT";
	हाल B43_PHYTYPE_LCN:
		वापस "LCN";
	हाल B43_PHYTYPE_LCNXN:
		वापस "LCNXN";
	हाल B43_PHYTYPE_LCN40:
		वापस "LCN40";
	हाल B43_PHYTYPE_AC:
		वापस "AC";
	पूर्ण
	वापस "UNKNOWN";
पूर्ण

/* Get PHY and RADIO versioning numbers */
अटल पूर्णांक b43_phy_versioning(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	स्थिर u8 core_rev = dev->dev->core_rev;
	u32 पंचांगp;
	u8 analog_type;
	u8 phy_type;
	u8 phy_rev;
	u16 radio_manuf;
	u16 radio_id;
	u16 radio_rev;
	u8 radio_ver;
	पूर्णांक unsupported = 0;

	/* Get PHY versioning */
	पंचांगp = b43_पढ़ो16(dev, B43_MMIO_PHY_VER);
	analog_type = (पंचांगp & B43_PHYVER_ANALOG) >> B43_PHYVER_ANALOG_SHIFT;
	phy_type = (पंचांगp & B43_PHYVER_TYPE) >> B43_PHYVER_TYPE_SHIFT;
	phy_rev = (पंचांगp & B43_PHYVER_VERSION);

	/* LCNXN is continuation of N which run out of revisions */
	अगर (phy_type == B43_PHYTYPE_LCNXN) अणु
		phy_type = B43_PHYTYPE_N;
		phy_rev += 16;
	पूर्ण

	चयन (phy_type) अणु
#अगर_घोषित CONFIG_B43_PHY_G
	हाल B43_PHYTYPE_G:
		अगर (phy_rev > 9)
			unsupported = 1;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_PHY_N
	हाल B43_PHYTYPE_N:
		अगर (phy_rev >= 19)
			unsupported = 1;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_PHY_LP
	हाल B43_PHYTYPE_LP:
		अगर (phy_rev > 2)
			unsupported = 1;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_PHY_HT
	हाल B43_PHYTYPE_HT:
		अगर (phy_rev > 1)
			unsupported = 1;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_PHY_LCN
	हाल B43_PHYTYPE_LCN:
		अगर (phy_rev > 1)
			unsupported = 1;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_PHY_AC
	हाल B43_PHYTYPE_AC:
		अगर (phy_rev > 1)
			unsupported = 1;
		अवरोध;
#पूर्ण_अगर
	शेष:
		unsupported = 1;
	पूर्ण
	अगर (unsupported) अणु
		b43err(dev->wl, "FOUND UNSUPPORTED PHY (Analog %u, Type %d (%s), Revision %u)\n",
		       analog_type, phy_type, b43_phy_name(dev, phy_type),
		       phy_rev);
		वापस -EOPNOTSUPP;
	पूर्ण
	b43info(dev->wl, "Found PHY: Analog %u, Type %d (%s), Revision %u\n",
		analog_type, phy_type, b43_phy_name(dev, phy_type), phy_rev);

	/* Get RADIO versioning */
	अगर (core_rev == 40 || core_rev == 42) अणु
		radio_manuf = 0x17F;

		b43_ग_लिखो16f(dev, B43_MMIO_RADIO24_CONTROL, 0);
		radio_rev = b43_पढ़ो16(dev, B43_MMIO_RADIO24_DATA);

		b43_ग_लिखो16f(dev, B43_MMIO_RADIO24_CONTROL, 1);
		radio_id = b43_पढ़ो16(dev, B43_MMIO_RADIO24_DATA);

		radio_ver = 0; /* Is there version somewhere? */
	पूर्ण अन्यथा अगर (core_rev >= 24) अणु
		u16 radio24[3];

		क्रम (पंचांगp = 0; पंचांगp < 3; पंचांगp++) अणु
			b43_ग_लिखो16f(dev, B43_MMIO_RADIO24_CONTROL, पंचांगp);
			radio24[पंचांगp] = b43_पढ़ो16(dev, B43_MMIO_RADIO24_DATA);
		पूर्ण

		radio_manuf = 0x17F;
		radio_id = (radio24[2] << 8) | radio24[1];
		radio_rev = (radio24[0] & 0xF);
		radio_ver = (radio24[0] & 0xF0) >> 4;
	पूर्ण अन्यथा अणु
		अगर (dev->dev->chip_id == 0x4317) अणु
			अगर (dev->dev->chip_rev == 0)
				पंचांगp = 0x3205017F;
			अन्यथा अगर (dev->dev->chip_rev == 1)
				पंचांगp = 0x4205017F;
			अन्यथा
				पंचांगp = 0x5205017F;
		पूर्ण अन्यथा अणु
			b43_ग_लिखो16f(dev, B43_MMIO_RADIO_CONTROL,
				     B43_RADIOCTL_ID);
			पंचांगp = b43_पढ़ो16(dev, B43_MMIO_RADIO_DATA_LOW);
			b43_ग_लिखो16f(dev, B43_MMIO_RADIO_CONTROL,
				     B43_RADIOCTL_ID);
			पंचांगp |= b43_पढ़ो16(dev, B43_MMIO_RADIO_DATA_HIGH) << 16;
		पूर्ण
		radio_manuf = (पंचांगp & 0x00000FFF);
		radio_id = (पंचांगp & 0x0FFFF000) >> 12;
		radio_rev = (पंचांगp & 0xF0000000) >> 28;
		radio_ver = 0; /* Probably not available on old hw */
	पूर्ण

	अगर (radio_manuf != 0x17F /* Broadcom */)
		unsupported = 1;
	चयन (phy_type) अणु
	हाल B43_PHYTYPE_B:
		अगर ((radio_id & 0xFFF0) != 0x2050)
			unsupported = 1;
		अवरोध;
	हाल B43_PHYTYPE_G:
		अगर (radio_id != 0x2050)
			unsupported = 1;
		अवरोध;
	हाल B43_PHYTYPE_N:
		अगर (radio_id != 0x2055 && radio_id != 0x2056 &&
		    radio_id != 0x2057)
			unsupported = 1;
		अगर (radio_id == 0x2057 &&
		    !(radio_rev == 9 || radio_rev == 14))
			unsupported = 1;
		अवरोध;
	हाल B43_PHYTYPE_LP:
		अगर (radio_id != 0x2062 && radio_id != 0x2063)
			unsupported = 1;
		अवरोध;
	हाल B43_PHYTYPE_HT:
		अगर (radio_id != 0x2059)
			unsupported = 1;
		अवरोध;
	हाल B43_PHYTYPE_LCN:
		अगर (radio_id != 0x2064)
			unsupported = 1;
		अवरोध;
	हाल B43_PHYTYPE_AC:
		अगर (radio_id != 0x2069)
			unsupported = 1;
		अवरोध;
	शेष:
		B43_WARN_ON(1);
	पूर्ण
	अगर (unsupported) अणु
		b43err(dev->wl,
		       "FOUND UNSUPPORTED RADIO (Manuf 0x%X, ID 0x%X, Revision %u, Version %u)\n",
		       radio_manuf, radio_id, radio_rev, radio_ver);
		वापस -EOPNOTSUPP;
	पूर्ण
	b43info(dev->wl,
		"Found Radio: Manuf 0x%X, ID 0x%X, Revision %u, Version %u\n",
		radio_manuf, radio_id, radio_rev, radio_ver);

	/* FIXME: b43 treats "id" as "ver" and ignores the real "ver" */
	phy->radio_manuf = radio_manuf;
	phy->radio_ver = radio_id;
	phy->radio_rev = radio_rev;

	phy->analog = analog_type;
	phy->type = phy_type;
	phy->rev = phy_rev;

	वापस 0;
पूर्ण

अटल व्योम setup_काष्ठा_phy_क्रम_init(काष्ठा b43_wldev *dev,
				      काष्ठा b43_phy *phy)
अणु
	phy->hardware_घातer_control = !!modparam_hwpctl;
	phy->next_txpwr_check_समय = jअगरfies;
	/* PHY TX errors counter. */
	atomic_set(&phy->txerr_cnt, B43_PHY_TX_BADNESS_LIMIT);

#अगर B43_DEBUG
	phy->phy_locked = false;
	phy->radio_locked = false;
#पूर्ण_अगर
पूर्ण

अटल व्योम setup_काष्ठा_wldev_क्रम_init(काष्ठा b43_wldev *dev)
अणु
	dev->dfq_valid = false;

	/* Assume the radio is enabled. If it's not enabled, the state will
	 * immediately get fixed on the first periodic work run. */
	dev->radio_hw_enable = true;

	/* Stats */
	स_रखो(&dev->stats, 0, माप(dev->stats));

	setup_काष्ठा_phy_क्रम_init(dev, &dev->phy);

	/* IRQ related flags */
	dev->irq_reason = 0;
	स_रखो(dev->dma_reason, 0, माप(dev->dma_reason));
	dev->irq_mask = B43_IRQ_MASKTEMPLATE;
	अगर (b43_modparam_verbose < B43_VERBOSITY_DEBUG)
		dev->irq_mask &= ~B43_IRQ_PHY_TXERR;

	dev->mac_suspended = 1;

	/* Noise calculation context */
	स_रखो(&dev->noisecalc, 0, माप(dev->noisecalc));
पूर्ण

अटल व्योम b43_bluetooth_coext_enable(काष्ठा b43_wldev *dev)
अणु
	काष्ठा ssb_sprom *sprom = dev->dev->bus_sprom;
	u64 hf;

	अगर (!modparam_btcoex)
		वापस;
	अगर (!(sprom->boardflags_lo & B43_BFL_BTCOEXIST))
		वापस;
	अगर (dev->phy.type != B43_PHYTYPE_B && !dev->phy.gmode)
		वापस;

	hf = b43_hf_पढ़ो(dev);
	अगर (sprom->boardflags_lo & B43_BFL_BTCMOD)
		hf |= B43_HF_BTCOEXALT;
	अन्यथा
		hf |= B43_HF_BTCOEX;
	b43_hf_ग_लिखो(dev, hf);
पूर्ण

अटल व्योम b43_bluetooth_coext_disable(काष्ठा b43_wldev *dev)
अणु
	अगर (!modparam_btcoex)
		वापस;
	//TODO
पूर्ण

अटल व्योम b43_imcfglo_समयouts_workaround(काष्ठा b43_wldev *dev)
अणु
	काष्ठा ssb_bus *bus;
	u32 पंचांगp;

#अगर_घोषित CONFIG_B43_SSB
	अगर (dev->dev->bus_type != B43_BUS_SSB)
		वापस;
#अन्यथा
	वापस;
#पूर्ण_अगर

	bus = dev->dev->sdev->bus;

	अगर ((bus->chip_id == 0x4311 && bus->chip_rev == 2) ||
	    (bus->chip_id == 0x4312)) अणु
		पंचांगp = ssb_पढ़ो32(dev->dev->sdev, SSB_IMCFGLO);
		पंचांगp &= ~SSB_IMCFGLO_REQTO;
		पंचांगp &= ~SSB_IMCFGLO_SERTO;
		पंचांगp |= 0x3;
		ssb_ग_लिखो32(dev->dev->sdev, SSB_IMCFGLO, पंचांगp);
		ssb_commit_settings(bus);
	पूर्ण
पूर्ण

अटल व्योम b43_set_synth_pu_delay(काष्ठा b43_wldev *dev, bool idle)
अणु
	u16 pu_delay;

	/* The समय value is in microseconds. */
	pu_delay = 1050;
	अगर (b43_is_mode(dev->wl, NL80211_IFTYPE_ADHOC) || idle)
		pu_delay = 500;
	अगर ((dev->phy.radio_ver == 0x2050) && (dev->phy.radio_rev == 8))
		pu_delay = max(pu_delay, (u16)2400);

	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_SPUWKUP, pu_delay);
पूर्ण

/* Set the TSF CFP pre-TargetBeaconTransmissionTime. */
अटल व्योम b43_set_pretbtt(काष्ठा b43_wldev *dev)
अणु
	u16 pretbtt;

	/* The समय value is in microseconds. */
	अगर (b43_is_mode(dev->wl, NL80211_IFTYPE_ADHOC))
		pretbtt = 2;
	अन्यथा
		pretbtt = 250;
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_PRETBTT, pretbtt);
	b43_ग_लिखो16(dev, B43_MMIO_TSF_CFP_PRETBTT, pretbtt);
पूर्ण

/* Shutकरोwn a wireless core */
/* Locking: wl->mutex */
अटल व्योम b43_wireless_core_निकास(काष्ठा b43_wldev *dev)
अणु
	B43_WARN_ON(dev && b43_status(dev) > B43_STAT_INITIALIZED);
	अगर (!dev || b43_status(dev) != B43_STAT_INITIALIZED)
		वापस;

	b43_set_status(dev, B43_STAT_UNINIT);

	/* Stop the microcode PSM. */
	b43_maskset32(dev, B43_MMIO_MACCTL, ~B43_MACCTL_PSM_RUN,
		      B43_MACCTL_PSM_JMP0);

	चयन (dev->dev->bus_type) अणु
#अगर_घोषित CONFIG_B43_BCMA
	हाल B43_BUS_BCMA:
		bcma_host_pci_करोwn(dev->dev->bdev->bus);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SSB
	हाल B43_BUS_SSB:
		/* TODO */
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	b43_dma_मुक्त(dev);
	b43_pio_मुक्त(dev);
	b43_chip_निकास(dev);
	dev->phy.ops->चयन_analog(dev, 0);
	अगर (dev->wl->current_beacon) अणु
		dev_kमुक्त_skb_any(dev->wl->current_beacon);
		dev->wl->current_beacon = शून्य;
	पूर्ण

	b43_device_disable(dev, 0);
	b43_bus_may_घातerकरोwn(dev);
पूर्ण

/* Initialize a wireless core */
अटल पूर्णांक b43_wireless_core_init(काष्ठा b43_wldev *dev)
अणु
	काष्ठा ssb_sprom *sprom = dev->dev->bus_sprom;
	काष्ठा b43_phy *phy = &dev->phy;
	पूर्णांक err;
	u64 hf;

	B43_WARN_ON(b43_status(dev) != B43_STAT_UNINIT);

	err = b43_bus_घातerup(dev, 0);
	अगर (err)
		जाओ out;
	अगर (!b43_device_is_enabled(dev))
		b43_wireless_core_reset(dev, phy->gmode);

	/* Reset all data काष्ठाures. */
	setup_काष्ठा_wldev_क्रम_init(dev);
	phy->ops->prepare_काष्ठाs(dev);

	/* Enable IRQ routing to this device. */
	चयन (dev->dev->bus_type) अणु
#अगर_घोषित CONFIG_B43_BCMA
	हाल B43_BUS_BCMA:
		bcma_host_pci_irq_ctl(dev->dev->bdev->bus,
				      dev->dev->bdev, true);
		bcma_host_pci_up(dev->dev->bdev->bus);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SSB
	हाल B43_BUS_SSB:
		ssb_pcicore_dev_irqvecs_enable(&dev->dev->sdev->bus->pcicore,
					       dev->dev->sdev);
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	b43_imcfglo_समयouts_workaround(dev);
	b43_bluetooth_coext_disable(dev);
	अगर (phy->ops->prepare_hardware) अणु
		err = phy->ops->prepare_hardware(dev);
		अगर (err)
			जाओ err_busकरोwn;
	पूर्ण
	err = b43_chip_init(dev);
	अगर (err)
		जाओ err_busकरोwn;
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED,
			B43_SHM_SH_WLCOREREV, dev->dev->core_rev);
	hf = b43_hf_पढ़ो(dev);
	अगर (phy->type == B43_PHYTYPE_G) अणु
		hf |= B43_HF_SYMW;
		अगर (phy->rev == 1)
			hf |= B43_HF_GDCW;
		अगर (sprom->boardflags_lo & B43_BFL_PACTRL)
			hf |= B43_HF_OFDMPABOOST;
	पूर्ण
	अगर (phy->radio_ver == 0x2050) अणु
		अगर (phy->radio_rev == 6)
			hf |= B43_HF_4318TSSI;
		अगर (phy->radio_rev < 6)
			hf |= B43_HF_VCORECALC;
	पूर्ण
	अगर (sprom->boardflags_lo & B43_BFL_XTAL_NOSLOW)
		hf |= B43_HF_DSCRQ; /* Disable slowघड़ी requests from ucode. */
#अगर defined(CONFIG_B43_SSB) && defined(CONFIG_SSB_DRIVER_PCICORE)
	अगर (dev->dev->bus_type == B43_BUS_SSB &&
	    dev->dev->sdev->bus->bustype == SSB_BUSTYPE_PCI &&
	    dev->dev->sdev->bus->pcicore.dev->id.revision <= 10)
		hf |= B43_HF_PCISCW; /* PCI slow घड़ी workaround. */
#पूर्ण_अगर
	hf &= ~B43_HF_SKCFPUP;
	b43_hf_ग_लिखो(dev, hf);

	/* tell the ucode MAC capabilities */
	अगर (dev->dev->core_rev >= 13) अणु
		u32 mac_hw_cap = b43_पढ़ो32(dev, B43_MMIO_MAC_HW_CAP);

		b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_MACHW_L,
				mac_hw_cap & 0xffff);
		b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_MACHW_H,
				(mac_hw_cap >> 16) & 0xffff);
	पूर्ण

	b43_set_retry_limits(dev, B43_DEFAULT_SHORT_RETRY_LIMIT,
			     B43_DEFAULT_LONG_RETRY_LIMIT);
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_SFFBLIM, 3);
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_LFFBLIM, 2);

	/* Disable sending probe responses from firmware.
	 * Setting the MaxTime to one usec will always trigger
	 * a समयout, so we never send any probe resp.
	 * A समयout of zero is infinite. */
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_PRMAXTIME, 1);

	b43_rate_memory_init(dev);
	b43_set_phytxctl_शेषs(dev);

	/* Minimum Contention Winकरोw */
	अगर (phy->type == B43_PHYTYPE_B)
		b43_shm_ग_लिखो16(dev, B43_SHM_SCRATCH, B43_SHM_SC_MINCONT, 0x1F);
	अन्यथा
		b43_shm_ग_लिखो16(dev, B43_SHM_SCRATCH, B43_SHM_SC_MINCONT, 0xF);
	/* Maximum Contention Winकरोw */
	b43_shm_ग_लिखो16(dev, B43_SHM_SCRATCH, B43_SHM_SC_MAXCONT, 0x3FF);

	/* ग_लिखो phytype and phyvers */
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_PHYTYPE, phy->type);
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_PHYVER, phy->rev);

	अगर (b43_bus_host_is_pcmcia(dev->dev) ||
	    b43_bus_host_is_sdio(dev->dev)) अणु
		dev->__using_pio_transfers = true;
		err = b43_pio_init(dev);
	पूर्ण अन्यथा अगर (dev->use_pio) अणु
		b43warn(dev->wl, "Forced PIO by use_pio module parameter. "
			"This should not be needed and will result in lower "
			"performance.\n");
		dev->__using_pio_transfers = true;
		err = b43_pio_init(dev);
	पूर्ण अन्यथा अणु
		dev->__using_pio_transfers = false;
		err = b43_dma_init(dev);
	पूर्ण
	अगर (err)
		जाओ err_chip_निकास;
	b43_qos_init(dev);
	b43_set_synth_pu_delay(dev, 1);
	b43_bluetooth_coext_enable(dev);

	b43_bus_घातerup(dev, !(sprom->boardflags_lo & B43_BFL_XTAL_NOSLOW));
	b43_upload_card_macaddress(dev);
	b43_security_init(dev);

	ieee80211_wake_queues(dev->wl->hw);

	b43_set_status(dev, B43_STAT_INITIALIZED);

out:
	वापस err;

err_chip_निकास:
	b43_chip_निकास(dev);
err_busकरोwn:
	b43_bus_may_घातerकरोwn(dev);
	B43_WARN_ON(b43_status(dev) != B43_STAT_UNINIT);
	वापस err;
पूर्ण

अटल पूर्णांक b43_op_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा b43_wl *wl = hw_to_b43_wl(hw);
	काष्ठा b43_wldev *dev;
	पूर्णांक err = -EOPNOTSUPP;

	/* TODO: allow AP devices to coexist */

	अगर (vअगर->type != NL80211_IFTYPE_AP &&
	    vअगर->type != NL80211_IFTYPE_MESH_POINT &&
	    vअगर->type != NL80211_IFTYPE_STATION &&
	    vअगर->type != NL80211_IFTYPE_ADHOC)
		वापस -EOPNOTSUPP;

	mutex_lock(&wl->mutex);
	अगर (wl->operating)
		जाओ out_mutex_unlock;

	b43dbg(wl, "Adding Interface type %d\n", vअगर->type);

	dev = wl->current_dev;
	wl->operating = true;
	wl->vअगर = vअगर;
	wl->अगर_type = vअगर->type;
	स_नकल(wl->mac_addr, vअगर->addr, ETH_ALEN);

	b43_adjust_opmode(dev);
	b43_set_pretbtt(dev);
	b43_set_synth_pu_delay(dev, 0);
	b43_upload_card_macaddress(dev);

	err = 0;
 out_mutex_unlock:
	mutex_unlock(&wl->mutex);

	अगर (err == 0)
		b43_op_bss_info_changed(hw, vअगर, &vअगर->bss_conf, ~0);

	वापस err;
पूर्ण

अटल व्योम b43_op_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा b43_wl *wl = hw_to_b43_wl(hw);
	काष्ठा b43_wldev *dev = wl->current_dev;

	b43dbg(wl, "Removing Interface type %d\n", vअगर->type);

	mutex_lock(&wl->mutex);

	B43_WARN_ON(!wl->operating);
	B43_WARN_ON(wl->vअगर != vअगर);
	wl->vअगर = शून्य;

	wl->operating = false;

	b43_adjust_opmode(dev);
	eth_zero_addr(wl->mac_addr);
	b43_upload_card_macaddress(dev);

	mutex_unlock(&wl->mutex);
पूर्ण

अटल पूर्णांक b43_op_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा b43_wl *wl = hw_to_b43_wl(hw);
	काष्ठा b43_wldev *dev = wl->current_dev;
	पूर्णांक did_init = 0;
	पूर्णांक err = 0;

	/* Kill all old instance specअगरic inक्रमmation to make sure
	 * the card won't use it in the लघु समयframe between start
	 * and mac80211 reconfiguring it. */
	eth_zero_addr(wl->bssid);
	eth_zero_addr(wl->mac_addr);
	wl->filter_flags = 0;
	wl->radiotap_enabled = false;
	b43_qos_clear(wl);
	wl->beacon0_uploaded = false;
	wl->beacon1_uploaded = false;
	wl->beacon_ढाँचाs_virgin = true;
	wl->radio_enabled = true;

	mutex_lock(&wl->mutex);

	अगर (b43_status(dev) < B43_STAT_INITIALIZED) अणु
		err = b43_wireless_core_init(dev);
		अगर (err)
			जाओ out_mutex_unlock;
		did_init = 1;
	पूर्ण

	अगर (b43_status(dev) < B43_STAT_STARTED) अणु
		err = b43_wireless_core_start(dev);
		अगर (err) अणु
			अगर (did_init)
				b43_wireless_core_निकास(dev);
			जाओ out_mutex_unlock;
		पूर्ण
	पूर्ण

	/* XXX: only करो अगर device करोesn't support rfसमाप्त irq */
	wiphy_rfसमाप्त_start_polling(hw->wiphy);

 out_mutex_unlock:
	mutex_unlock(&wl->mutex);

	/*
	 * Configuration may have been overwritten during initialization.
	 * Reload the configuration, but only अगर initialization was
	 * successful. Reloading the configuration after a failed init
	 * may hang the प्रणाली.
	 */
	अगर (!err)
		b43_op_config(hw, ~0);

	वापस err;
पूर्ण

अटल व्योम b43_op_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा b43_wl *wl = hw_to_b43_wl(hw);
	काष्ठा b43_wldev *dev = wl->current_dev;

	cancel_work_sync(&(wl->beacon_update_trigger));

	अगर (!dev)
		जाओ out;

	mutex_lock(&wl->mutex);
	अगर (b43_status(dev) >= B43_STAT_STARTED) अणु
		dev = b43_wireless_core_stop(dev);
		अगर (!dev)
			जाओ out_unlock;
	पूर्ण
	b43_wireless_core_निकास(dev);
	wl->radio_enabled = false;

out_unlock:
	mutex_unlock(&wl->mutex);
out:
	cancel_work_sync(&(wl->txघातer_adjust_work));
पूर्ण

अटल पूर्णांक b43_op_beacon_set_tim(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_sta *sta, bool set)
अणु
	काष्ठा b43_wl *wl = hw_to_b43_wl(hw);

	b43_update_ढाँचाs(wl);

	वापस 0;
पूर्ण

अटल व्योम b43_op_sta_notअगरy(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      क्रमागत sta_notअगरy_cmd notअगरy_cmd,
			      काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा b43_wl *wl = hw_to_b43_wl(hw);

	B43_WARN_ON(!vअगर || wl->vअगर != vअगर);
पूर्ण

अटल व्योम b43_op_sw_scan_start_notअगरier(काष्ठा ieee80211_hw *hw,
					  काष्ठा ieee80211_vअगर *vअगर,
					  स्थिर u8 *mac_addr)
अणु
	काष्ठा b43_wl *wl = hw_to_b43_wl(hw);
	काष्ठा b43_wldev *dev;

	mutex_lock(&wl->mutex);
	dev = wl->current_dev;
	अगर (dev && (b43_status(dev) >= B43_STAT_INITIALIZED)) अणु
		/* Disable CFP update during scan on other channels. */
		b43_hf_ग_लिखो(dev, b43_hf_पढ़ो(dev) | B43_HF_SKCFPUP);
	पूर्ण
	mutex_unlock(&wl->mutex);
पूर्ण

अटल व्योम b43_op_sw_scan_complete_notअगरier(काष्ठा ieee80211_hw *hw,
					     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा b43_wl *wl = hw_to_b43_wl(hw);
	काष्ठा b43_wldev *dev;

	mutex_lock(&wl->mutex);
	dev = wl->current_dev;
	अगर (dev && (b43_status(dev) >= B43_STAT_INITIALIZED)) अणु
		/* Re-enable CFP update. */
		b43_hf_ग_लिखो(dev, b43_hf_पढ़ो(dev) & ~B43_HF_SKCFPUP);
	पूर्ण
	mutex_unlock(&wl->mutex);
पूर्ण

अटल पूर्णांक b43_op_get_survey(काष्ठा ieee80211_hw *hw, पूर्णांक idx,
			     काष्ठा survey_info *survey)
अणु
	काष्ठा b43_wl *wl = hw_to_b43_wl(hw);
	काष्ठा b43_wldev *dev = wl->current_dev;
	काष्ठा ieee80211_conf *conf = &hw->conf;

	अगर (idx != 0)
		वापस -ENOENT;

	survey->channel = conf->chandef.chan;
	survey->filled = SURVEY_INFO_NOISE_DBM;
	survey->noise = dev->stats.link_noise;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops b43_hw_ops = अणु
	.tx			= b43_op_tx,
	.conf_tx		= b43_op_conf_tx,
	.add_पूर्णांकerface		= b43_op_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface	= b43_op_हटाओ_पूर्णांकerface,
	.config			= b43_op_config,
	.bss_info_changed	= b43_op_bss_info_changed,
	.configure_filter	= b43_op_configure_filter,
	.set_key		= b43_op_set_key,
	.update_tkip_key	= b43_op_update_tkip_key,
	.get_stats		= b43_op_get_stats,
	.get_tsf		= b43_op_get_tsf,
	.set_tsf		= b43_op_set_tsf,
	.start			= b43_op_start,
	.stop			= b43_op_stop,
	.set_tim		= b43_op_beacon_set_tim,
	.sta_notअगरy		= b43_op_sta_notअगरy,
	.sw_scan_start		= b43_op_sw_scan_start_notअगरier,
	.sw_scan_complete	= b43_op_sw_scan_complete_notअगरier,
	.get_survey		= b43_op_get_survey,
	.rfसमाप्त_poll		= b43_rfसमाप्त_poll,
पूर्ण;

/* Hard-reset the chip. Do not call this directly.
 * Use b43_controller_restart()
 */
अटल व्योम b43_chip_reset(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा b43_wldev *dev =
	    container_of(work, काष्ठा b43_wldev, restart_work);
	काष्ठा b43_wl *wl = dev->wl;
	पूर्णांक err = 0;
	पूर्णांक prev_status;

	mutex_lock(&wl->mutex);

	prev_status = b43_status(dev);
	/* Bring the device करोwn... */
	अगर (prev_status >= B43_STAT_STARTED) अणु
		dev = b43_wireless_core_stop(dev);
		अगर (!dev) अणु
			err = -ENODEV;
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (prev_status >= B43_STAT_INITIALIZED)
		b43_wireless_core_निकास(dev);

	/* ...and up again. */
	अगर (prev_status >= B43_STAT_INITIALIZED) अणु
		err = b43_wireless_core_init(dev);
		अगर (err)
			जाओ out;
	पूर्ण
	अगर (prev_status >= B43_STAT_STARTED) अणु
		err = b43_wireless_core_start(dev);
		अगर (err) अणु
			b43_wireless_core_निकास(dev);
			जाओ out;
		पूर्ण
	पूर्ण
out:
	अगर (err)
		wl->current_dev = शून्य; /* Failed to init the dev. */
	mutex_unlock(&wl->mutex);

	अगर (err) अणु
		b43err(wl, "Controller restart FAILED\n");
		वापस;
	पूर्ण

	/* reload configuration */
	b43_op_config(wl->hw, ~0);
	अगर (wl->vअगर)
		b43_op_bss_info_changed(wl->hw, wl->vअगर, &wl->vअगर->bss_conf, ~0);

	b43info(wl, "Controller restarted\n");
पूर्ण

अटल पूर्णांक b43_setup_bands(काष्ठा b43_wldev *dev,
			   bool have_2ghz_phy, bool have_5ghz_phy)
अणु
	काष्ठा ieee80211_hw *hw = dev->wl->hw;
	काष्ठा b43_phy *phy = &dev->phy;
	bool limited_2g;
	bool limited_5g;

	/* We करोn't support all 2 GHz channels on some devices */
	limited_2g = phy->radio_ver == 0x2057 &&
		     (phy->radio_rev == 9 || phy->radio_rev == 14);
	limited_5g = phy->radio_ver == 0x2057 &&
		     phy->radio_rev == 9;

	अगर (have_2ghz_phy)
		hw->wiphy->bands[NL80211_BAND_2GHZ] = limited_2g ?
			&b43_band_2ghz_limited : &b43_band_2GHz;
	अगर (dev->phy.type == B43_PHYTYPE_N) अणु
		अगर (have_5ghz_phy)
			hw->wiphy->bands[NL80211_BAND_5GHZ] = limited_5g ?
				&b43_band_5GHz_nphy_limited :
				&b43_band_5GHz_nphy;
	पूर्ण अन्यथा अणु
		अगर (have_5ghz_phy)
			hw->wiphy->bands[NL80211_BAND_5GHZ] = &b43_band_5GHz_aphy;
	पूर्ण

	dev->phy.supports_2ghz = have_2ghz_phy;
	dev->phy.supports_5ghz = have_5ghz_phy;

	वापस 0;
पूर्ण

अटल व्योम b43_wireless_core_detach(काष्ठा b43_wldev *dev)
अणु
	/* We release firmware that late to not be required to re-request
	 * is all the समय when we reinit the core. */
	b43_release_firmware(dev);
	b43_phy_मुक्त(dev);
पूर्ण

अटल व्योम b43_supported_bands(काष्ठा b43_wldev *dev, bool *have_2ghz_phy,
				bool *have_5ghz_phy)
अणु
	u16 dev_id = 0;

#अगर_घोषित CONFIG_B43_BCMA
	अगर (dev->dev->bus_type == B43_BUS_BCMA &&
	    dev->dev->bdev->bus->hosttype == BCMA_HOSTTYPE_PCI)
		dev_id = dev->dev->bdev->bus->host_pci->device;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SSB
	अगर (dev->dev->bus_type == B43_BUS_SSB &&
	    dev->dev->sdev->bus->bustype == SSB_BUSTYPE_PCI)
		dev_id = dev->dev->sdev->bus->host_pci->device;
#पूर्ण_अगर
	/* Override with SPROM value अगर available */
	अगर (dev->dev->bus_sprom->dev_id)
		dev_id = dev->dev->bus_sprom->dev_id;

	/* Note: below IDs can be "virtual" (not maching e.g. real PCI ID) */
	चयन (dev_id) अणु
	हाल 0x4324: /* BCM4306 */
	हाल 0x4312: /* BCM4311 */
	हाल 0x4319: /* BCM4318 */
	हाल 0x4328: /* BCM4321 */
	हाल 0x432b: /* BCM4322 */
	हाल 0x4350: /* BCM43222 */
	हाल 0x4353: /* BCM43224 */
	हाल 0x0576: /* BCM43224 */
	हाल 0x435f: /* BCM6362 */
	हाल 0x4331: /* BCM4331 */
	हाल 0x4359: /* BCM43228 */
	हाल 0x43a0: /* BCM4360 */
	हाल 0x43b1: /* BCM4352 */
		/* Dual band devices */
		*have_2ghz_phy = true;
		*have_5ghz_phy = true;
		वापस;
	हाल 0x4321: /* BCM4306 */
		/* There are 14e4:4321 PCI devs with 2.4 GHz BCM4321 (N-PHY) */
		अगर (dev->phy.type != B43_PHYTYPE_G)
			अवरोध;
		fallthrough;
	हाल 0x4313: /* BCM4311 */
	हाल 0x431a: /* BCM4318 */
	हाल 0x432a: /* BCM4321 */
	हाल 0x432d: /* BCM4322 */
	हाल 0x4352: /* BCM43222 */
	हाल 0x435a: /* BCM43228 */
	हाल 0x4333: /* BCM4331 */
	हाल 0x43a2: /* BCM4360 */
	हाल 0x43b3: /* BCM4352 */
		/* 5 GHz only devices */
		*have_2ghz_phy = false;
		*have_5ghz_phy = true;
		वापस;
	पूर्ण

	/* As a fallback, try to guess using PHY type */
	चयन (dev->phy.type) अणु
	हाल B43_PHYTYPE_G:
	हाल B43_PHYTYPE_N:
	हाल B43_PHYTYPE_LP:
	हाल B43_PHYTYPE_HT:
	हाल B43_PHYTYPE_LCN:
		*have_2ghz_phy = true;
		*have_5ghz_phy = false;
		वापस;
	पूर्ण

	B43_WARN_ON(1);
पूर्ण

अटल पूर्णांक b43_wireless_core_attach(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_wl *wl = dev->wl;
	काष्ठा b43_phy *phy = &dev->phy;
	पूर्णांक err;
	u32 पंचांगp;
	bool have_2ghz_phy = false, have_5ghz_phy = false;

	/* Do NOT करो any device initialization here.
	 * Do it in wireless_core_init() instead.
	 * This function is क्रम gathering basic inक्रमmation about the HW, only.
	 * Also some काष्ठाs may be set up here. But most likely you want to have
	 * that in core_init(), too.
	 */

	err = b43_bus_घातerup(dev, 0);
	अगर (err) अणु
		b43err(wl, "Bus powerup failed\n");
		जाओ out;
	पूर्ण

	phy->करो_full_init = true;

	/* Try to guess supported bands क्रम the first init needs */
	चयन (dev->dev->bus_type) अणु
#अगर_घोषित CONFIG_B43_BCMA
	हाल B43_BUS_BCMA:
		पंचांगp = bcma_aपढ़ो32(dev->dev->bdev, BCMA_IOST);
		have_2ghz_phy = !!(पंचांगp & B43_BCMA_IOST_2G_PHY);
		have_5ghz_phy = !!(पंचांगp & B43_BCMA_IOST_5G_PHY);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SSB
	हाल B43_BUS_SSB:
		अगर (dev->dev->core_rev >= 5) अणु
			पंचांगp = ssb_पढ़ो32(dev->dev->sdev, SSB_TMSHIGH);
			have_2ghz_phy = !!(पंचांगp & B43_TMSHIGH_HAVE_2GHZ_PHY);
			have_5ghz_phy = !!(पंचांगp & B43_TMSHIGH_HAVE_5GHZ_PHY);
		पूर्ण अन्यथा
			B43_WARN_ON(1);
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	dev->phy.gmode = have_2ghz_phy;
	b43_wireless_core_reset(dev, dev->phy.gmode);

	/* Get the PHY type. */
	err = b43_phy_versioning(dev);
	अगर (err)
		जाओ err_घातerकरोwn;

	/* Get real info about supported bands */
	b43_supported_bands(dev, &have_2ghz_phy, &have_5ghz_phy);

	/* We करोn't support 5 GHz on some PHYs yet */
	अगर (have_5ghz_phy) अणु
		चयन (dev->phy.type) अणु
		हाल B43_PHYTYPE_G:
		हाल B43_PHYTYPE_LP:
		हाल B43_PHYTYPE_HT:
			b43warn(wl, "5 GHz band is unsupported on this PHY\n");
			have_5ghz_phy = false;
		पूर्ण
	पूर्ण

	अगर (!have_2ghz_phy && !have_5ghz_phy) अणु
		b43err(wl, "b43 can't support any band on this device\n");
		err = -EOPNOTSUPP;
		जाओ err_घातerकरोwn;
	पूर्ण

	err = b43_phy_allocate(dev);
	अगर (err)
		जाओ err_घातerकरोwn;

	dev->phy.gmode = have_2ghz_phy;
	b43_wireless_core_reset(dev, dev->phy.gmode);

	err = b43_validate_chipaccess(dev);
	अगर (err)
		जाओ err_phy_मुक्त;
	err = b43_setup_bands(dev, have_2ghz_phy, have_5ghz_phy);
	अगर (err)
		जाओ err_phy_मुक्त;

	/* Now set some शेष "current_dev" */
	अगर (!wl->current_dev)
		wl->current_dev = dev;
	INIT_WORK(&dev->restart_work, b43_chip_reset);

	dev->phy.ops->चयन_analog(dev, 0);
	b43_device_disable(dev, 0);
	b43_bus_may_घातerकरोwn(dev);

out:
	वापस err;

err_phy_मुक्त:
	b43_phy_मुक्त(dev);
err_घातerकरोwn:
	b43_bus_may_घातerकरोwn(dev);
	वापस err;
पूर्ण

अटल व्योम b43_one_core_detach(काष्ठा b43_bus_dev *dev)
अणु
	काष्ठा b43_wldev *wldev;

	/* Do not cancel ieee80211-workqueue based work here.
	 * See comment in b43_हटाओ(). */

	wldev = b43_bus_get_wldev(dev);
	b43_debugfs_हटाओ_device(wldev);
	b43_wireless_core_detach(wldev);
	list_del(&wldev->list);
	b43_bus_set_wldev(dev, शून्य);
	kमुक्त(wldev);
पूर्ण

अटल पूर्णांक b43_one_core_attach(काष्ठा b43_bus_dev *dev, काष्ठा b43_wl *wl)
अणु
	काष्ठा b43_wldev *wldev;
	पूर्णांक err = -ENOMEM;

	wldev = kzalloc(माप(*wldev), GFP_KERNEL);
	अगर (!wldev)
		जाओ out;

	wldev->use_pio = b43_modparam_pio;
	wldev->dev = dev;
	wldev->wl = wl;
	b43_set_status(wldev, B43_STAT_UNINIT);
	wldev->bad_frames_preempt = modparam_bad_frames_preempt;
	INIT_LIST_HEAD(&wldev->list);

	err = b43_wireless_core_attach(wldev);
	अगर (err)
		जाओ err_kमुक्त_wldev;

	b43_bus_set_wldev(dev, wldev);
	b43_debugfs_add_device(wldev);

      out:
	वापस err;

      err_kमुक्त_wldev:
	kमुक्त(wldev);
	वापस err;
पूर्ण

#घोषणा IS_PDEV(pdev, _venकरोr, _device, _subvenकरोr, _subdevice)		( \
	(pdev->venकरोr == PCI_VENDOR_ID_##_venकरोr) &&			\
	(pdev->device == _device) &&					\
	(pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_##_subvenकरोr) &&	\
	(pdev->subप्रणाली_device == _subdevice)				)

#अगर_घोषित CONFIG_B43_SSB
अटल व्योम b43_sprom_fixup(काष्ठा ssb_bus *bus)
अणु
	काष्ठा pci_dev *pdev;

	/* boardflags workarounds */
	अगर (bus->boardinfo.venकरोr == SSB_BOARDVENDOR_DELL &&
	    bus->chip_id == 0x4301 && bus->sprom.board_rev == 0x74)
		bus->sprom.boardflags_lo |= B43_BFL_BTCOEXIST;
	अगर (bus->boardinfo.venकरोr == PCI_VENDOR_ID_APPLE &&
	    bus->boardinfo.type == 0x4E && bus->sprom.board_rev > 0x40)
		bus->sprom.boardflags_lo |= B43_BFL_PACTRL;
	अगर (bus->bustype == SSB_BUSTYPE_PCI) अणु
		pdev = bus->host_pci;
		अगर (IS_PDEV(pdev, BROADCOM, 0x4318, ASUSTEK, 0x100F) ||
		    IS_PDEV(pdev, BROADCOM, 0x4320,    DELL, 0x0003) ||
		    IS_PDEV(pdev, BROADCOM, 0x4320,      HP, 0x12f8) ||
		    IS_PDEV(pdev, BROADCOM, 0x4320, LINKSYS, 0x0015) ||
		    IS_PDEV(pdev, BROADCOM, 0x4320, LINKSYS, 0x0014) ||
		    IS_PDEV(pdev, BROADCOM, 0x4320, LINKSYS, 0x0013) ||
		    IS_PDEV(pdev, BROADCOM, 0x4320, MOTOROLA, 0x7010))
			bus->sprom.boardflags_lo &= ~B43_BFL_BTCOEXIST;
	पूर्ण
पूर्ण

अटल व्योम b43_wireless_निकास(काष्ठा b43_bus_dev *dev, काष्ठा b43_wl *wl)
अणु
	काष्ठा ieee80211_hw *hw = wl->hw;

	ssb_set_devtypedata(dev->sdev, शून्य);
	ieee80211_मुक्त_hw(hw);
पूर्ण
#पूर्ण_अगर

अटल काष्ठा b43_wl *b43_wireless_init(काष्ठा b43_bus_dev *dev)
अणु
	काष्ठा ssb_sprom *sprom = dev->bus_sprom;
	काष्ठा ieee80211_hw *hw;
	काष्ठा b43_wl *wl;
	अक्षर chip_name[6];
	पूर्णांक queue_num;

	hw = ieee80211_alloc_hw(माप(*wl), &b43_hw_ops);
	अगर (!hw) अणु
		b43err(शून्य, "Could not allocate ieee80211 device\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	wl = hw_to_b43_wl(hw);

	/* fill hw info */
	ieee80211_hw_set(hw, RX_INCLUDES_FCS);
	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, MFP_CAPABLE);
	hw->wiphy->पूर्णांकerface_modes =
		BIT(NL80211_IFTYPE_AP) |
		BIT(NL80211_IFTYPE_MESH_POINT) |
		BIT(NL80211_IFTYPE_STATION) |
		BIT(NL80211_IFTYPE_ADHOC);

	hw->wiphy->flags |= WIPHY_FLAG_IBSS_RSN;

	wiphy_ext_feature_set(hw->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	wl->hw_रेजिस्टरed = false;
	hw->max_rates = 2;
	SET_IEEE80211_DEV(hw, dev->dev);
	अगर (is_valid_ether_addr(sprom->et1mac))
		SET_IEEE80211_PERM_ADDR(hw, sprom->et1mac);
	अन्यथा
		SET_IEEE80211_PERM_ADDR(hw, sprom->il0mac);

	/* Initialize काष्ठा b43_wl */
	wl->hw = hw;
	mutex_init(&wl->mutex);
	spin_lock_init(&wl->hardirq_lock);
	spin_lock_init(&wl->beacon_lock);
	INIT_WORK(&wl->beacon_update_trigger, b43_beacon_update_trigger_work);
	INIT_WORK(&wl->txघातer_adjust_work, b43_phy_txघातer_adjust_work);
	INIT_WORK(&wl->tx_work, b43_tx_work);

	/* Initialize queues and flags. */
	क्रम (queue_num = 0; queue_num < B43_QOS_QUEUE_NUM; queue_num++) अणु
		skb_queue_head_init(&wl->tx_queue[queue_num]);
		wl->tx_queue_stopped[queue_num] = false;
	पूर्ण

	snम_लिखो(chip_name, ARRAY_SIZE(chip_name),
		 (dev->chip_id > 0x9999) ? "%d" : "%04X", dev->chip_id);
	b43info(wl, "Broadcom %s WLAN found (core revision %u)\n", chip_name,
		dev->core_rev);
	वापस wl;
पूर्ण

#अगर_घोषित CONFIG_B43_BCMA
अटल पूर्णांक b43_bcma_probe(काष्ठा bcma_device *core)
अणु
	काष्ठा b43_bus_dev *dev;
	काष्ठा b43_wl *wl;
	पूर्णांक err;

	अगर (!modparam_allhwsupport &&
	    (core->id.rev == 0x17 || core->id.rev == 0x18)) अणु
		pr_err("Support for cores revisions 0x17 and 0x18 disabled by module param allhwsupport=0. Try b43.allhwsupport=1\n");
		वापस -ENOTSUPP;
	पूर्ण

	dev = b43_bus_dev_bcma_init(core);
	अगर (!dev)
		वापस -ENODEV;

	wl = b43_wireless_init(dev);
	अगर (IS_ERR(wl)) अणु
		err = PTR_ERR(wl);
		जाओ bcma_out;
	पूर्ण

	err = b43_one_core_attach(dev, wl);
	अगर (err)
		जाओ bcma_err_wireless_निकास;

	/* setup and start work to load firmware */
	INIT_WORK(&wl->firmware_load, b43_request_firmware);
	schedule_work(&wl->firmware_load);

	वापस err;

bcma_err_wireless_निकास:
	ieee80211_मुक्त_hw(wl->hw);
bcma_out:
	kमुक्त(dev);
	वापस err;
पूर्ण

अटल व्योम b43_bcma_हटाओ(काष्ठा bcma_device *core)
अणु
	काष्ठा b43_wldev *wldev = bcma_get_drvdata(core);
	काष्ठा b43_wl *wl = wldev->wl;

	/* We must cancel any work here beक्रमe unरेजिस्टरing from ieee80211,
	 * as the ieee80211 unreg will destroy the workqueue. */
	cancel_work_sync(&wldev->restart_work);
	cancel_work_sync(&wl->firmware_load);

	B43_WARN_ON(!wl);
	अगर (!wldev->fw.ucode.data)
		वापस;			/* शून्य अगर firmware never loaded */
	अगर (wl->current_dev == wldev && wl->hw_रेजिस्टरed) अणु
		b43_leds_stop(wldev);
		ieee80211_unरेजिस्टर_hw(wl->hw);
	पूर्ण

	b43_one_core_detach(wldev->dev);

	/* Unरेजिस्टर HW RNG driver */
	b43_rng_निकास(wl);

	b43_leds_unरेजिस्टर(wl);
	ieee80211_मुक्त_hw(wl->hw);
	kमुक्त(wldev->dev);
पूर्ण

अटल काष्ठा bcma_driver b43_bcma_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= b43_bcma_tbl,
	.probe		= b43_bcma_probe,
	.हटाओ		= b43_bcma_हटाओ,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_B43_SSB
अटल
पूर्णांक b43_ssb_probe(काष्ठा ssb_device *sdev, स्थिर काष्ठा ssb_device_id *id)
अणु
	काष्ठा b43_bus_dev *dev;
	काष्ठा b43_wl *wl;
	पूर्णांक err;

	dev = b43_bus_dev_ssb_init(sdev);
	अगर (!dev)
		वापस -ENOMEM;

	wl = ssb_get_devtypedata(sdev);
	अगर (wl) अणु
		b43err(शून्य, "Dual-core devices are not supported\n");
		err = -ENOTSUPP;
		जाओ err_ssb_kमुक्त_dev;
	पूर्ण

	b43_sprom_fixup(sdev->bus);

	wl = b43_wireless_init(dev);
	अगर (IS_ERR(wl)) अणु
		err = PTR_ERR(wl);
		जाओ err_ssb_kमुक्त_dev;
	पूर्ण
	ssb_set_devtypedata(sdev, wl);
	B43_WARN_ON(ssb_get_devtypedata(sdev) != wl);

	err = b43_one_core_attach(dev, wl);
	अगर (err)
		जाओ err_ssb_wireless_निकास;

	/* setup and start work to load firmware */
	INIT_WORK(&wl->firmware_load, b43_request_firmware);
	schedule_work(&wl->firmware_load);

	वापस err;

err_ssb_wireless_निकास:
	b43_wireless_निकास(dev, wl);
err_ssb_kमुक्त_dev:
	kमुक्त(dev);
	वापस err;
पूर्ण

अटल व्योम b43_ssb_हटाओ(काष्ठा ssb_device *sdev)
अणु
	काष्ठा b43_wl *wl = ssb_get_devtypedata(sdev);
	काष्ठा b43_wldev *wldev = ssb_get_drvdata(sdev);
	काष्ठा b43_bus_dev *dev = wldev->dev;

	/* We must cancel any work here beक्रमe unरेजिस्टरing from ieee80211,
	 * as the ieee80211 unreg will destroy the workqueue. */
	cancel_work_sync(&wldev->restart_work);
	cancel_work_sync(&wl->firmware_load);

	B43_WARN_ON(!wl);
	अगर (!wldev->fw.ucode.data)
		वापस;			/* शून्य अगर firmware never loaded */
	अगर (wl->current_dev == wldev && wl->hw_रेजिस्टरed) अणु
		b43_leds_stop(wldev);
		ieee80211_unरेजिस्टर_hw(wl->hw);
	पूर्ण

	b43_one_core_detach(dev);

	/* Unरेजिस्टर HW RNG driver */
	b43_rng_निकास(wl);

	b43_leds_unरेजिस्टर(wl);
	b43_wireless_निकास(dev, wl);
	kमुक्त(dev);
पूर्ण

अटल काष्ठा ssb_driver b43_ssb_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= b43_ssb_tbl,
	.probe		= b43_ssb_probe,
	.हटाओ		= b43_ssb_हटाओ,
पूर्ण;
#पूर्ण_अगर /* CONFIG_B43_SSB */

/* Perक्रमm a hardware reset. This can be called from any context. */
व्योम b43_controller_restart(काष्ठा b43_wldev *dev, स्थिर अक्षर *reason)
अणु
	/* Must aव्योम requeueing, अगर we are in shutकरोwn. */
	अगर (b43_status(dev) < B43_STAT_INITIALIZED)
		वापस;
	b43info(dev->wl, "Controller RESET (%s) ...\n", reason);
	ieee80211_queue_work(dev->wl->hw, &dev->restart_work);
पूर्ण

अटल व्योम b43_prपूर्णांक_driverinfo(व्योम)
अणु
	स्थिर अक्षर *feat_pci = "", *feat_pcmcia = "", *feat_nphy = "",
		   *feat_leds = "", *feat_sdio = "";

#अगर_घोषित CONFIG_B43_PCI_AUTOSELECT
	feat_pci = "P";
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_PCMCIA
	feat_pcmcia = "M";
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_PHY_N
	feat_nphy = "N";
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_LEDS
	feat_leds = "L";
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SDIO
	feat_sdio = "S";
#पूर्ण_अगर
	prपूर्णांकk(KERN_INFO "Broadcom 43xx driver loaded "
	       "[ Features: %s%s%s%s%s ]\n",
	       feat_pci, feat_pcmcia, feat_nphy,
	       feat_leds, feat_sdio);
पूर्ण

अटल पूर्णांक __init b43_init(व्योम)
अणु
	पूर्णांक err;

	b43_debugfs_init();
	err = b43_sdio_init();
	अगर (err)
		जाओ err_dfs_निकास;
#अगर_घोषित CONFIG_B43_BCMA
	err = bcma_driver_रेजिस्टर(&b43_bcma_driver);
	अगर (err)
		जाओ err_sdio_निकास;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SSB
	err = ssb_driver_रेजिस्टर(&b43_ssb_driver);
	अगर (err)
		जाओ err_bcma_driver_निकास;
#पूर्ण_अगर
	b43_prपूर्णांक_driverinfo();

	वापस err;

#अगर_घोषित CONFIG_B43_SSB
err_bcma_driver_निकास:
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_BCMA
	bcma_driver_unरेजिस्टर(&b43_bcma_driver);
err_sdio_निकास:
#पूर्ण_अगर
	b43_sdio_निकास();
err_dfs_निकास:
	b43_debugfs_निकास();
	वापस err;
पूर्ण

अटल व्योम __निकास b43_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_B43_SSB
	ssb_driver_unरेजिस्टर(&b43_ssb_driver);
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_BCMA
	bcma_driver_unरेजिस्टर(&b43_bcma_driver);
#पूर्ण_अगर
	b43_sdio_निकास();
	b43_debugfs_निकास();
पूर्ण

module_init(b43_init)
module_निकास(b43_निकास)
