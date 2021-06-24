<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mac80211_hwsim - software simulator of 802.11 radio(s) क्रम mac80211
 * Copyright (c) 2008, Jouni Malinen <j@w1.fi>
 * Copyright (c) 2011, Javier Lopez <jlopex@gmail.com>
 * Copyright (c) 2016 - 2017 Intel Deutschland GmbH
 * Copyright (C) 2018 - 2020 Intel Corporation
 */

/*
 * TODO:
 * - Add TSF sync and fix IBSS beacon transmission by adding
 *   competition क्रम "air time" at TBTT
 * - RX filtering based on filter configuration (data->rx_filter)
 */

#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <net/dst.h>
#समावेश <net/xfrm.h>
#समावेश <net/mac80211.h>
#समावेश <net/ieee80211_radiotap.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/module.h>
#समावेश <linux/kसमय.स>
#समावेश <net/genetlink.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/nospec.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_ids.h>
#समावेश <linux/virtio_config.h>
#समावेश "mac80211_hwsim.h"

#घोषणा WARN_QUEUE 100
#घोषणा MAX_QUEUE 200

MODULE_AUTHOR("Jouni Malinen");
MODULE_DESCRIPTION("Software simulator of 802.11 radio(s) for mac80211");
MODULE_LICENSE("GPL");

अटल पूर्णांक radios = 2;
module_param(radios, पूर्णांक, 0444);
MODULE_PARM_DESC(radios, "Number of simulated radios");

अटल पूर्णांक channels = 1;
module_param(channels, पूर्णांक, 0444);
MODULE_PARM_DESC(channels, "Number of concurrent channels");

अटल bool paged_rx = false;
module_param(paged_rx, bool, 0644);
MODULE_PARM_DESC(paged_rx, "Use paged SKBs for RX instead of linear ones");

अटल bool rctbl = false;
module_param(rctbl, bool, 0444);
MODULE_PARM_DESC(rctbl, "Handle rate control table");

अटल bool support_p2p_device = true;
module_param(support_p2p_device, bool, 0444);
MODULE_PARM_DESC(support_p2p_device, "Support P2P-Device interface type");

/**
 * क्रमागत hwsim_regtest - the type of regulatory tests we offer
 *
 * These are the dअगरferent values you can use क्रम the regtest
 * module parameter. This is useful to help test world roaming
 * and the driver regulatory_hपूर्णांक() call and combinations of these.
 * If you want to करो specअगरic alpha2 regulatory करोमुख्य tests simply
 * use the userspace regulatory request as that will be respected as
 * well without the need of this module parameter. This is deचिन्हित
 * only क्रम testing the driver regulatory request, world roaming
 * and all possible combinations.
 *
 * @HWSIM_REGTEST_DISABLED: No regulatory tests are perक्रमmed,
 * 	this is the शेष value.
 * @HWSIM_REGTEST_DRIVER_REG_FOLLOW: Used क्रम testing the driver regulatory
 *	hपूर्णांक, only one driver regulatory hपूर्णांक will be sent as such the
 * 	secondary radios are expected to follow.
 * @HWSIM_REGTEST_DRIVER_REG_ALL: Used क्रम testing the driver regulatory
 * 	request with all radios reporting the same regulatory करोमुख्य.
 * @HWSIM_REGTEST_DIFF_COUNTRY: Used क्रम testing the drivers calling
 * 	dअगरferent regulatory करोमुख्यs requests. Expected behaviour is क्रम
 * 	an पूर्णांकersection to occur but each device will still use their
 * 	respective regulatory requested करोमुख्यs. Subsequent radios will
 * 	use the resulting पूर्णांकersection.
 * @HWSIM_REGTEST_WORLD_ROAM: Used क्रम testing the world roaming. We accomplish
 *	this by using a custom beacon-capable regulatory करोमुख्य क्रम the first
 *	radio. All other device world roam.
 * @HWSIM_REGTEST_CUSTOM_WORLD: Used क्रम testing the custom world regulatory
 * 	करोमुख्य requests. All radios will adhere to this custom world regulatory
 * 	करोमुख्य.
 * @HWSIM_REGTEST_CUSTOM_WORLD_2: Used क्रम testing 2 custom world regulatory
 * 	करोमुख्य requests. The first radio will adhere to the first custom world
 * 	regulatory करोमुख्य, the second one to the second custom world regulatory
 * 	करोमुख्य. All other devices will world roam.
 * @HWSIM_REGTEST_STRICT_FOLLOW: Used क्रम testing strict regulatory करोमुख्य
 *	settings, only the first radio will send a regulatory करोमुख्य request
 *	and use strict settings. The rest of the radios are expected to follow.
 * @HWSIM_REGTEST_STRICT_ALL: Used क्रम testing strict regulatory करोमुख्य
 *	settings. All radios will adhere to this.
 * @HWSIM_REGTEST_STRICT_AND_DRIVER_REG: Used क्रम testing strict regulatory
 *	करोमुख्य settings, combined with secondary driver regulatory करोमुख्य
 *	settings. The first radio will get a strict regulatory करोमुख्य setting
 *	using the first driver regulatory request and the second radio will use
 *	non-strict settings using the second driver regulatory request. All
 *	other devices should follow the पूर्णांकersection created between the
 *	first two.
 * @HWSIM_REGTEST_ALL: Used क्रम testing every possible mix. You will need
 * 	at least 6 radios क्रम a complete test. We will test in this order:
 * 	1 - driver custom world regulatory करोमुख्य
 * 	2 - second custom world regulatory करोमुख्य
 * 	3 - first driver regulatory करोमुख्य request
 * 	4 - second driver regulatory करोमुख्य request
 * 	5 - strict regulatory करोमुख्य settings using the third driver regulatory
 * 	    करोमुख्य request
 * 	6 and on - should follow the पूर्णांकersection of the 3rd, 4rth and 5th radio
 * 	           regulatory requests.
 */
क्रमागत hwsim_regtest अणु
	HWSIM_REGTEST_DISABLED = 0,
	HWSIM_REGTEST_DRIVER_REG_FOLLOW = 1,
	HWSIM_REGTEST_DRIVER_REG_ALL = 2,
	HWSIM_REGTEST_DIFF_COUNTRY = 3,
	HWSIM_REGTEST_WORLD_ROAM = 4,
	HWSIM_REGTEST_CUSTOM_WORLD = 5,
	HWSIM_REGTEST_CUSTOM_WORLD_2 = 6,
	HWSIM_REGTEST_STRICT_FOLLOW = 7,
	HWSIM_REGTEST_STRICT_ALL = 8,
	HWSIM_REGTEST_STRICT_AND_DRIVER_REG = 9,
	HWSIM_REGTEST_ALL = 10,
पूर्ण;

/* Set to one of the HWSIM_REGTEST_* values above */
अटल पूर्णांक regtest = HWSIM_REGTEST_DISABLED;
module_param(regtest, पूर्णांक, 0444);
MODULE_PARM_DESC(regtest, "The type of regulatory test we want to run");

अटल स्थिर अक्षर *hwsim_alpha2s[] = अणु
	"FI",
	"AL",
	"US",
	"DE",
	"JP",
	"AL",
पूर्ण;

अटल स्थिर काष्ठा ieee80211_regकरोमुख्य hwsim_world_regकरोm_custom_01 = अणु
	.n_reg_rules = 5,
	.alpha2 =  "99",
	.reg_rules = अणु
		REG_RULE(2412-10, 2462+10, 40, 0, 20, 0),
		REG_RULE(2484-10, 2484+10, 40, 0, 20, 0),
		REG_RULE(5150-10, 5240+10, 40, 0, 30, 0),
		REG_RULE(5745-10, 5825+10, 40, 0, 30, 0),
		REG_RULE(5855-10, 5925+10, 40, 0, 33, 0),
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ieee80211_regकरोमुख्य hwsim_world_regकरोm_custom_02 = अणु
	.n_reg_rules = 3,
	.alpha2 =  "99",
	.reg_rules = अणु
		REG_RULE(2412-10, 2462+10, 40, 0, 20, 0),
		REG_RULE(5725-10, 5850+10, 40, 0, 30,
			 NL80211_RRF_NO_IR),
		REG_RULE(5855-10, 5925+10, 40, 0, 33, 0),
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ieee80211_regकरोमुख्य *hwsim_world_regकरोm_custom[] = अणु
	&hwsim_world_regकरोm_custom_01,
	&hwsim_world_regकरोm_custom_02,
पूर्ण;

काष्ठा hwsim_vअगर_priv अणु
	u32 magic;
	u8 bssid[ETH_ALEN];
	bool assoc;
	bool bcn_en;
	u16 aid;
पूर्ण;

#घोषणा HWSIM_VIF_MAGIC	0x69537748

अटल अंतरभूत व्योम hwsim_check_magic(काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा hwsim_vअगर_priv *vp = (व्योम *)vअगर->drv_priv;
	WARN(vp->magic != HWSIM_VIF_MAGIC,
	     "Invalid VIF (%p) magic %#x, %pM, %d/%d\n",
	     vअगर, vp->magic, vअगर->addr, vअगर->type, vअगर->p2p);
पूर्ण

अटल अंतरभूत व्योम hwsim_set_magic(काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा hwsim_vअगर_priv *vp = (व्योम *)vअगर->drv_priv;
	vp->magic = HWSIM_VIF_MAGIC;
पूर्ण

अटल अंतरभूत व्योम hwsim_clear_magic(काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा hwsim_vअगर_priv *vp = (व्योम *)vअगर->drv_priv;
	vp->magic = 0;
पूर्ण

काष्ठा hwsim_sta_priv अणु
	u32 magic;
पूर्ण;

#घोषणा HWSIM_STA_MAGIC	0x6d537749

अटल अंतरभूत व्योम hwsim_check_sta_magic(काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा hwsim_sta_priv *sp = (व्योम *)sta->drv_priv;
	WARN_ON(sp->magic != HWSIM_STA_MAGIC);
पूर्ण

अटल अंतरभूत व्योम hwsim_set_sta_magic(काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा hwsim_sta_priv *sp = (व्योम *)sta->drv_priv;
	sp->magic = HWSIM_STA_MAGIC;
पूर्ण

अटल अंतरभूत व्योम hwsim_clear_sta_magic(काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा hwsim_sta_priv *sp = (व्योम *)sta->drv_priv;
	sp->magic = 0;
पूर्ण

काष्ठा hwsim_chanctx_priv अणु
	u32 magic;
पूर्ण;

#घोषणा HWSIM_CHANCTX_MAGIC 0x6d53774a

अटल अंतरभूत व्योम hwsim_check_chanctx_magic(काष्ठा ieee80211_chanctx_conf *c)
अणु
	काष्ठा hwsim_chanctx_priv *cp = (व्योम *)c->drv_priv;
	WARN_ON(cp->magic != HWSIM_CHANCTX_MAGIC);
पूर्ण

अटल अंतरभूत व्योम hwsim_set_chanctx_magic(काष्ठा ieee80211_chanctx_conf *c)
अणु
	काष्ठा hwsim_chanctx_priv *cp = (व्योम *)c->drv_priv;
	cp->magic = HWSIM_CHANCTX_MAGIC;
पूर्ण

अटल अंतरभूत व्योम hwsim_clear_chanctx_magic(काष्ठा ieee80211_chanctx_conf *c)
अणु
	काष्ठा hwsim_chanctx_priv *cp = (व्योम *)c->drv_priv;
	cp->magic = 0;
पूर्ण

अटल अचिन्हित पूर्णांक hwsim_net_id;

अटल DEFINE_IDA(hwsim_netgroup_ida);

काष्ठा hwsim_net अणु
	पूर्णांक netgroup;
	u32 wmediumd;
पूर्ण;

अटल अंतरभूत पूर्णांक hwsim_net_get_netgroup(काष्ठा net *net)
अणु
	काष्ठा hwsim_net *hwsim_net = net_generic(net, hwsim_net_id);

	वापस hwsim_net->netgroup;
पूर्ण

अटल अंतरभूत पूर्णांक hwsim_net_set_netgroup(काष्ठा net *net)
अणु
	काष्ठा hwsim_net *hwsim_net = net_generic(net, hwsim_net_id);

	hwsim_net->netgroup = ida_simple_get(&hwsim_netgroup_ida,
					     0, 0, GFP_KERNEL);
	वापस hwsim_net->netgroup >= 0 ? 0 : -ENOMEM;
पूर्ण

अटल अंतरभूत u32 hwsim_net_get_wmediumd(काष्ठा net *net)
अणु
	काष्ठा hwsim_net *hwsim_net = net_generic(net, hwsim_net_id);

	वापस hwsim_net->wmediumd;
पूर्ण

अटल अंतरभूत व्योम hwsim_net_set_wmediumd(काष्ठा net *net, u32 portid)
अणु
	काष्ठा hwsim_net *hwsim_net = net_generic(net, hwsim_net_id);

	hwsim_net->wmediumd = portid;
पूर्ण

अटल काष्ठा class *hwsim_class;

अटल काष्ठा net_device *hwsim_mon; /* global monitor netdev */

#घोषणा CHAN2G(_freq)  अणु \
	.band = NL80211_BAND_2GHZ, \
	.center_freq = (_freq), \
	.hw_value = (_freq), \
पूर्ण

#घोषणा CHAN5G(_freq) अणु \
	.band = NL80211_BAND_5GHZ, \
	.center_freq = (_freq), \
	.hw_value = (_freq), \
पूर्ण

#घोषणा CHAN6G(_freq) अणु \
	.band = NL80211_BAND_6GHZ, \
	.center_freq = (_freq), \
	.hw_value = (_freq), \
पूर्ण

अटल स्थिर काष्ठा ieee80211_channel hwsim_channels_2ghz[] = अणु
	CHAN2G(2412), /* Channel 1 */
	CHAN2G(2417), /* Channel 2 */
	CHAN2G(2422), /* Channel 3 */
	CHAN2G(2427), /* Channel 4 */
	CHAN2G(2432), /* Channel 5 */
	CHAN2G(2437), /* Channel 6 */
	CHAN2G(2442), /* Channel 7 */
	CHAN2G(2447), /* Channel 8 */
	CHAN2G(2452), /* Channel 9 */
	CHAN2G(2457), /* Channel 10 */
	CHAN2G(2462), /* Channel 11 */
	CHAN2G(2467), /* Channel 12 */
	CHAN2G(2472), /* Channel 13 */
	CHAN2G(2484), /* Channel 14 */
पूर्ण;

अटल स्थिर काष्ठा ieee80211_channel hwsim_channels_5ghz[] = अणु
	CHAN5G(5180), /* Channel 36 */
	CHAN5G(5200), /* Channel 40 */
	CHAN5G(5220), /* Channel 44 */
	CHAN5G(5240), /* Channel 48 */

	CHAN5G(5260), /* Channel 52 */
	CHAN5G(5280), /* Channel 56 */
	CHAN5G(5300), /* Channel 60 */
	CHAN5G(5320), /* Channel 64 */

	CHAN5G(5500), /* Channel 100 */
	CHAN5G(5520), /* Channel 104 */
	CHAN5G(5540), /* Channel 108 */
	CHAN5G(5560), /* Channel 112 */
	CHAN5G(5580), /* Channel 116 */
	CHAN5G(5600), /* Channel 120 */
	CHAN5G(5620), /* Channel 124 */
	CHAN5G(5640), /* Channel 128 */
	CHAN5G(5660), /* Channel 132 */
	CHAN5G(5680), /* Channel 136 */
	CHAN5G(5700), /* Channel 140 */

	CHAN5G(5745), /* Channel 149 */
	CHAN5G(5765), /* Channel 153 */
	CHAN5G(5785), /* Channel 157 */
	CHAN5G(5805), /* Channel 161 */
	CHAN5G(5825), /* Channel 165 */
	CHAN5G(5845), /* Channel 169 */

	CHAN5G(5855), /* Channel 171 */
	CHAN5G(5860), /* Channel 172 */
	CHAN5G(5865), /* Channel 173 */
	CHAN5G(5870), /* Channel 174 */

	CHAN5G(5875), /* Channel 175 */
	CHAN5G(5880), /* Channel 176 */
	CHAN5G(5885), /* Channel 177 */
	CHAN5G(5890), /* Channel 178 */
	CHAN5G(5895), /* Channel 179 */
	CHAN5G(5900), /* Channel 180 */
	CHAN5G(5905), /* Channel 181 */

	CHAN5G(5910), /* Channel 182 */
	CHAN5G(5915), /* Channel 183 */
	CHAN5G(5920), /* Channel 184 */
	CHAN5G(5925), /* Channel 185 */
पूर्ण;

अटल स्थिर काष्ठा ieee80211_channel hwsim_channels_6ghz[] = अणु
	CHAN6G(5955), /* Channel 1 */
	CHAN6G(5975), /* Channel 5 */
	CHAN6G(5995), /* Channel 9 */
	CHAN6G(6015), /* Channel 13 */
	CHAN6G(6035), /* Channel 17 */
	CHAN6G(6055), /* Channel 21 */
	CHAN6G(6075), /* Channel 25 */
	CHAN6G(6095), /* Channel 29 */
	CHAN6G(6115), /* Channel 33 */
	CHAN6G(6135), /* Channel 37 */
	CHAN6G(6155), /* Channel 41 */
	CHAN6G(6175), /* Channel 45 */
	CHAN6G(6195), /* Channel 49 */
	CHAN6G(6215), /* Channel 53 */
	CHAN6G(6235), /* Channel 57 */
	CHAN6G(6255), /* Channel 61 */
	CHAN6G(6275), /* Channel 65 */
	CHAN6G(6295), /* Channel 69 */
	CHAN6G(6315), /* Channel 73 */
	CHAN6G(6335), /* Channel 77 */
	CHAN6G(6355), /* Channel 81 */
	CHAN6G(6375), /* Channel 85 */
	CHAN6G(6395), /* Channel 89 */
	CHAN6G(6415), /* Channel 93 */
	CHAN6G(6435), /* Channel 97 */
	CHAN6G(6455), /* Channel 181 */
	CHAN6G(6475), /* Channel 105 */
	CHAN6G(6495), /* Channel 109 */
	CHAN6G(6515), /* Channel 113 */
	CHAN6G(6535), /* Channel 117 */
	CHAN6G(6555), /* Channel 121 */
	CHAN6G(6575), /* Channel 125 */
	CHAN6G(6595), /* Channel 129 */
	CHAN6G(6615), /* Channel 133 */
	CHAN6G(6635), /* Channel 137 */
	CHAN6G(6655), /* Channel 141 */
	CHAN6G(6675), /* Channel 145 */
	CHAN6G(6695), /* Channel 149 */
	CHAN6G(6715), /* Channel 153 */
	CHAN6G(6735), /* Channel 157 */
	CHAN6G(6755), /* Channel 161 */
	CHAN6G(6775), /* Channel 165 */
	CHAN6G(6795), /* Channel 169 */
	CHAN6G(6815), /* Channel 173 */
	CHAN6G(6835), /* Channel 177 */
	CHAN6G(6855), /* Channel 181 */
	CHAN6G(6875), /* Channel 185 */
	CHAN6G(6895), /* Channel 189 */
	CHAN6G(6915), /* Channel 193 */
	CHAN6G(6935), /* Channel 197 */
	CHAN6G(6955), /* Channel 201 */
	CHAN6G(6975), /* Channel 205 */
	CHAN6G(6995), /* Channel 209 */
	CHAN6G(7015), /* Channel 213 */
	CHAN6G(7035), /* Channel 217 */
	CHAN6G(7055), /* Channel 221 */
	CHAN6G(7075), /* Channel 225 */
	CHAN6G(7095), /* Channel 229 */
	CHAN6G(7115), /* Channel 233 */
पूर्ण;

#घोषणा NUM_S1G_CHANS_US 51
अटल काष्ठा ieee80211_channel hwsim_channels_s1g[NUM_S1G_CHANS_US];

अटल स्थिर काष्ठा ieee80211_sta_s1g_cap hwsim_s1g_cap = अणु
	.s1g = true,
	.cap = अणु S1G_CAP0_SGI_1MHZ | S1G_CAP0_SGI_2MHZ,
		 0,
		 0,
		 S1G_CAP3_MAX_MPDU_LEN,
		 0,
		 S1G_CAP5_AMPDU,
		 0,
		 S1G_CAP7_DUP_1MHZ,
		 S1G_CAP8_TWT_RESPOND | S1G_CAP8_TWT_REQUEST,
		 0पूर्ण,
	.nss_mcs = अणु 0xfc | 1, /* MCS 7 क्रम 1 SS */
	/* RX Highest Supported Long GI Data Rate 0:7 */
		     0,
	/* RX Highest Supported Long GI Data Rate 0:7 */
	/* TX S1G MCS Map 0:6 */
		     0xfa,
	/* TX S1G MCS Map :7 */
	/* TX Highest Supported Long GI Data Rate 0:6 */
		     0x80,
	/* TX Highest Supported Long GI Data Rate 7:8 */
	/* Rx Single spatial stream and S1G-MCS Map क्रम 1MHz */
	/* Tx Single spatial stream and S1G-MCS Map क्रम 1MHz */
		     0 पूर्ण,
पूर्ण;

अटल व्योम hwsim_init_s1g_channels(काष्ठा ieee80211_channel *channels)
अणु
	पूर्णांक ch, freq;

	क्रम (ch = 0; ch < NUM_S1G_CHANS_US; ch++) अणु
		freq = 902000 + (ch + 1) * 500;
		channels[ch].band = NL80211_BAND_S1GHZ;
		channels[ch].center_freq = KHZ_TO_MHZ(freq);
		channels[ch].freq_offset = freq % 1000;
		channels[ch].hw_value = ch + 1;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ieee80211_rate hwsim_rates[] = अणु
	अणु .bitrate = 10 पूर्ण,
	अणु .bitrate = 20, .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 55, .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 110, .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 60 पूर्ण,
	अणु .bitrate = 90 पूर्ण,
	अणु .bitrate = 120 पूर्ण,
	अणु .bitrate = 180 पूर्ण,
	अणु .bitrate = 240 पूर्ण,
	अणु .bitrate = 360 पूर्ण,
	अणु .bitrate = 480 पूर्ण,
	अणु .bitrate = 540 पूर्ण
पूर्ण;

अटल स्थिर u32 hwsim_ciphers[] = अणु
	WLAN_CIPHER_SUITE_WEP40,
	WLAN_CIPHER_SUITE_WEP104,
	WLAN_CIPHER_SUITE_TKIP,
	WLAN_CIPHER_SUITE_CCMP,
	WLAN_CIPHER_SUITE_CCMP_256,
	WLAN_CIPHER_SUITE_GCMP,
	WLAN_CIPHER_SUITE_GCMP_256,
	WLAN_CIPHER_SUITE_AES_CMAC,
	WLAN_CIPHER_SUITE_BIP_CMAC_256,
	WLAN_CIPHER_SUITE_BIP_GMAC_128,
	WLAN_CIPHER_SUITE_BIP_GMAC_256,
पूर्ण;

#घोषणा OUI_QCA 0x001374
#घोषणा QCA_NL80211_SUBCMD_TEST 1
क्रमागत qca_nl80211_venकरोr_subcmds अणु
	QCA_WLAN_VENDOR_ATTR_TEST = 8,
	QCA_WLAN_VENDOR_ATTR_MAX = QCA_WLAN_VENDOR_ATTR_TEST
पूर्ण;

अटल स्थिर काष्ठा nla_policy
hwsim_venकरोr_test_policy[QCA_WLAN_VENDOR_ATTR_MAX + 1] = अणु
	[QCA_WLAN_VENDOR_ATTR_MAX] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक mac80211_hwsim_venकरोr_cmd_test(काष्ठा wiphy *wiphy,
					  काष्ठा wireless_dev *wdev,
					  स्थिर व्योम *data, पूर्णांक data_len)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा nlattr *tb[QCA_WLAN_VENDOR_ATTR_MAX + 1];
	पूर्णांक err;
	u32 val;

	err = nla_parse_deprecated(tb, QCA_WLAN_VENDOR_ATTR_MAX, data,
				   data_len, hwsim_venकरोr_test_policy, शून्य);
	अगर (err)
		वापस err;
	अगर (!tb[QCA_WLAN_VENDOR_ATTR_TEST])
		वापस -EINVAL;
	val = nla_get_u32(tb[QCA_WLAN_VENDOR_ATTR_TEST]);
	wiphy_dbg(wiphy, "%s: test=%u\n", __func__, val);

	/* Send a venकरोr event as a test. Note that this would not normally be
	 * करोne within a command handler, but rather, based on some other
	 * trigger. For simplicity, this command is used to trigger the event
	 * here.
	 *
	 * event_idx = 0 (index in mac80211_hwsim_venकरोr_commands)
	 */
	skb = cfg80211_venकरोr_event_alloc(wiphy, wdev, 100, 0, GFP_KERNEL);
	अगर (skb) अणु
		/* skb_put() or nla_put() will fill up data within
		 * NL80211_ATTR_VENDOR_DATA.
		 */

		/* Add venकरोr data */
		nla_put_u32(skb, QCA_WLAN_VENDOR_ATTR_TEST, val + 1);

		/* Send the event - this will call nla_nest_end() */
		cfg80211_venकरोr_event(skb, GFP_KERNEL);
	पूर्ण

	/* Send a response to the command */
	skb = cfg80211_venकरोr_cmd_alloc_reply_skb(wiphy, 10);
	अगर (!skb)
		वापस -ENOMEM;

	/* skb_put() or nla_put() will fill up data within
	 * NL80211_ATTR_VENDOR_DATA
	 */
	nla_put_u32(skb, QCA_WLAN_VENDOR_ATTR_TEST, val + 2);

	वापस cfg80211_venकरोr_cmd_reply(skb);
पूर्ण

अटल काष्ठा wiphy_venकरोr_command mac80211_hwsim_venकरोr_commands[] = अणु
	अणु
		.info = अणु .venकरोr_id = OUI_QCA,
			  .subcmd = QCA_NL80211_SUBCMD_TEST पूर्ण,
		.flags = WIPHY_VENDOR_CMD_NEED_NETDEV,
		.करोit = mac80211_hwsim_venकरोr_cmd_test,
		.policy = hwsim_venकरोr_test_policy,
		.maxattr = QCA_WLAN_VENDOR_ATTR_MAX,
	पूर्ण
पूर्ण;

/* Advertise support venकरोr specअगरic events */
अटल स्थिर काष्ठा nl80211_venकरोr_cmd_info mac80211_hwsim_venकरोr_events[] = अणु
	अणु .venकरोr_id = OUI_QCA, .subcmd = 1 पूर्ण,
पूर्ण;

अटल DEFINE_SPINLOCK(hwsim_radio_lock);
अटल LIST_HEAD(hwsim_radios);
अटल काष्ठा rhashtable hwsim_radios_rht;
अटल पूर्णांक hwsim_radio_idx;
अटल पूर्णांक hwsim_radios_generation = 1;

अटल काष्ठा platक्रमm_driver mac80211_hwsim_driver = अणु
	.driver = अणु
		.name = "mac80211_hwsim",
	पूर्ण,
पूर्ण;

काष्ठा mac80211_hwsim_data अणु
	काष्ठा list_head list;
	काष्ठा rhash_head rht;
	काष्ठा ieee80211_hw *hw;
	काष्ठा device *dev;
	काष्ठा ieee80211_supported_band bands[NUM_NL80211_BANDS];
	काष्ठा ieee80211_channel channels_2ghz[ARRAY_SIZE(hwsim_channels_2ghz)];
	काष्ठा ieee80211_channel channels_5ghz[ARRAY_SIZE(hwsim_channels_5ghz)];
	काष्ठा ieee80211_channel channels_6ghz[ARRAY_SIZE(hwsim_channels_6ghz)];
	काष्ठा ieee80211_channel channels_s1g[ARRAY_SIZE(hwsim_channels_s1g)];
	काष्ठा ieee80211_rate rates[ARRAY_SIZE(hwsim_rates)];
	काष्ठा ieee80211_अगरace_combination अगर_combination;
	काष्ठा ieee80211_अगरace_limit अगर_limits[3];
	पूर्णांक n_अगर_limits;

	u32 ciphers[ARRAY_SIZE(hwsim_ciphers)];

	काष्ठा mac_address addresses[2];
	पूर्णांक channels, idx;
	bool use_chanctx;
	bool destroy_on_बंद;
	u32 portid;
	अक्षर alpha2[2];
	स्थिर काष्ठा ieee80211_regकरोमुख्य *regd;

	काष्ठा ieee80211_channel *पंचांगp_chan;
	काष्ठा ieee80211_channel *roc_chan;
	u32 roc_duration;
	काष्ठा delayed_work roc_start;
	काष्ठा delayed_work roc_करोne;
	काष्ठा delayed_work hw_scan;
	काष्ठा cfg80211_scan_request *hw_scan_request;
	काष्ठा ieee80211_vअगर *hw_scan_vअगर;
	पूर्णांक scan_chan_idx;
	u8 scan_addr[ETH_ALEN];
	काष्ठा अणु
		काष्ठा ieee80211_channel *channel;
		अचिन्हित दीर्घ next_start, start, end;
	पूर्ण survey_data[ARRAY_SIZE(hwsim_channels_2ghz) +
		      ARRAY_SIZE(hwsim_channels_5ghz) +
		      ARRAY_SIZE(hwsim_channels_6ghz)];

	काष्ठा ieee80211_channel *channel;
	u64 beacon_पूर्णांक	/* beacon पूर्णांकerval in us */;
	अचिन्हित पूर्णांक rx_filter;
	bool started, idle, scanning;
	काष्ठा mutex mutex;
	काष्ठा hrसमयr beacon_समयr;
	क्रमागत ps_mode अणु
		PS_DISABLED, PS_ENABLED, PS_AUTO_POLL, PS_MANUAL_POLL
	पूर्ण ps;
	bool ps_poll_pending;
	काष्ठा dentry *debugfs;

	uपूर्णांकptr_t pending_cookie;
	काष्ठा sk_buff_head pending;	/* packets pending */
	/*
	 * Only radios in the same group can communicate together (the
	 * channel has to match too). Each bit represents a group. A
	 * radio can be in more than one group.
	 */
	u64 group;

	/* group shared by radios created in the same netns */
	पूर्णांक netgroup;
	/* wmediumd portid responsible क्रम netgroup of this radio */
	u32 wmediumd;

	/* dअगरference between this hw's घड़ी and the real घड़ी, in usecs */
	s64 tsf_offset;
	s64 bcn_delta;
	/* असलolute beacon transmission समय. Used to cover up "tx" delay. */
	u64 असल_bcn_ts;

	/* Stats */
	u64 tx_pkts;
	u64 rx_pkts;
	u64 tx_bytes;
	u64 rx_bytes;
	u64 tx_dropped;
	u64 tx_failed;
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params hwsim_rht_params = अणु
	.nelem_hपूर्णांक = 2,
	.स्वतःmatic_shrinking = true,
	.key_len = ETH_ALEN,
	.key_offset = दुरत्व(काष्ठा mac80211_hwsim_data, addresses[1]),
	.head_offset = दुरत्व(काष्ठा mac80211_hwsim_data, rht),
पूर्ण;

काष्ठा hwsim_radiotap_hdr अणु
	काष्ठा ieee80211_radiotap_header hdr;
	__le64 rt_tsft;
	u8 rt_flags;
	u8 rt_rate;
	__le16 rt_channel;
	__le16 rt_chbiपंचांगask;
पूर्ण __packed;

काष्ठा hwsim_radiotap_ack_hdr अणु
	काष्ठा ieee80211_radiotap_header hdr;
	u8 rt_flags;
	u8 pad;
	__le16 rt_channel;
	__le16 rt_chbiपंचांगask;
पूर्ण __packed;

/* MAC80211_HWSIM netlink family */
अटल काष्ठा genl_family hwsim_genl_family;

क्रमागत hwsim_multicast_groups अणु
	HWSIM_MCGRP_CONFIG,
पूर्ण;

अटल स्थिर काष्ठा genl_multicast_group hwsim_mcgrps[] = अणु
	[HWSIM_MCGRP_CONFIG] = अणु .name = "config", पूर्ण,
पूर्ण;

/* MAC80211_HWSIM netlink policy */

अटल स्थिर काष्ठा nla_policy hwsim_genl_policy[HWSIM_ATTR_MAX + 1] = अणु
	[HWSIM_ATTR_ADDR_RECEIVER] = NLA_POLICY_ETH_ADDR_COMPAT,
	[HWSIM_ATTR_ADDR_TRANSMITTER] = NLA_POLICY_ETH_ADDR_COMPAT,
	[HWSIM_ATTR_FRAME] = अणु .type = NLA_BINARY,
			       .len = IEEE80211_MAX_DATA_LEN पूर्ण,
	[HWSIM_ATTR_FLAGS] = अणु .type = NLA_U32 पूर्ण,
	[HWSIM_ATTR_RX_RATE] = अणु .type = NLA_U32 पूर्ण,
	[HWSIM_ATTR_SIGNAL] = अणु .type = NLA_U32 पूर्ण,
	[HWSIM_ATTR_TX_INFO] = अणु .type = NLA_BINARY,
				 .len = IEEE80211_TX_MAX_RATES *
					माप(काष्ठा hwsim_tx_rate)पूर्ण,
	[HWSIM_ATTR_COOKIE] = अणु .type = NLA_U64 पूर्ण,
	[HWSIM_ATTR_CHANNELS] = अणु .type = NLA_U32 पूर्ण,
	[HWSIM_ATTR_RADIO_ID] = अणु .type = NLA_U32 पूर्ण,
	[HWSIM_ATTR_REG_HINT_ALPHA2] = अणु .type = NLA_STRING, .len = 2 पूर्ण,
	[HWSIM_ATTR_REG_CUSTOM_REG] = अणु .type = NLA_U32 पूर्ण,
	[HWSIM_ATTR_REG_STRICT_REG] = अणु .type = NLA_FLAG पूर्ण,
	[HWSIM_ATTR_SUPPORT_P2P_DEVICE] = अणु .type = NLA_FLAG पूर्ण,
	[HWSIM_ATTR_USE_CHANCTX] = अणु .type = NLA_FLAG पूर्ण,
	[HWSIM_ATTR_DESTROY_RADIO_ON_CLOSE] = अणु .type = NLA_FLAG पूर्ण,
	[HWSIM_ATTR_RADIO_NAME] = अणु .type = NLA_STRING पूर्ण,
	[HWSIM_ATTR_NO_VIF] = अणु .type = NLA_FLAG पूर्ण,
	[HWSIM_ATTR_FREQ] = अणु .type = NLA_U32 पूर्ण,
	[HWSIM_ATTR_TX_INFO_FLAGS] = अणु .type = NLA_BINARY पूर्ण,
	[HWSIM_ATTR_PERM_ADDR] = NLA_POLICY_ETH_ADDR_COMPAT,
	[HWSIM_ATTR_IFTYPE_SUPPORT] = अणु .type = NLA_U32 पूर्ण,
	[HWSIM_ATTR_CIPHER_SUPPORT] = अणु .type = NLA_BINARY पूर्ण,
पूर्ण;

#अगर IS_REACHABLE(CONFIG_VIRTIO)

/* MAC80211_HWSIM virtio queues */
अटल काष्ठा virtqueue *hwsim_vqs[HWSIM_NUM_VQS];
अटल bool hwsim_virtio_enabled;
अटल DEFINE_SPINLOCK(hwsim_virtio_lock);

अटल व्योम hwsim_virtio_rx_work(काष्ठा work_काष्ठा *work);
अटल DECLARE_WORK(hwsim_virtio_rx, hwsim_virtio_rx_work);

अटल पूर्णांक hwsim_tx_virtio(काष्ठा mac80211_hwsim_data *data,
			   काष्ठा sk_buff *skb)
अणु
	काष्ठा scatterlist sg[1];
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&hwsim_virtio_lock, flags);
	अगर (!hwsim_virtio_enabled) अणु
		err = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	sg_init_one(sg, skb->head, skb_end_offset(skb));
	err = virtqueue_add_outbuf(hwsim_vqs[HWSIM_VQ_TX], sg, 1, skb,
				   GFP_ATOMIC);
	अगर (err)
		जाओ out_मुक्त;
	virtqueue_kick(hwsim_vqs[HWSIM_VQ_TX]);
	spin_unlock_irqrestore(&hwsim_virtio_lock, flags);
	वापस 0;

out_मुक्त:
	spin_unlock_irqrestore(&hwsim_virtio_lock, flags);
	nlmsg_मुक्त(skb);
	वापस err;
पूर्ण
#अन्यथा
/* cause a linker error अगर this ends up being needed */
बाह्य पूर्णांक hwsim_tx_virtio(काष्ठा mac80211_hwsim_data *data,
			   काष्ठा sk_buff *skb);
#घोषणा hwsim_virtio_enabled false
#पूर्ण_अगर

अटल व्योम mac80211_hwsim_tx_frame(काष्ठा ieee80211_hw *hw,
				    काष्ठा sk_buff *skb,
				    काष्ठा ieee80211_channel *chan);

/* sysfs attributes */
अटल व्योम hwsim_send_ps_poll(व्योम *dat, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mac80211_hwsim_data *data = dat;
	काष्ठा hwsim_vअगर_priv *vp = (व्योम *)vअगर->drv_priv;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_pspoll *pspoll;

	अगर (!vp->assoc)
		वापस;

	wiphy_dbg(data->hw->wiphy,
		  "%s: send PS-Poll to %pM for aid %d\n",
		  __func__, vp->bssid, vp->aid);

	skb = dev_alloc_skb(माप(*pspoll));
	अगर (!skb)
		वापस;
	pspoll = skb_put(skb, माप(*pspoll));
	pspoll->frame_control = cpu_to_le16(IEEE80211_FTYPE_CTL |
					    IEEE80211_STYPE_PSPOLL |
					    IEEE80211_FCTL_PM);
	pspoll->aid = cpu_to_le16(0xc000 | vp->aid);
	स_नकल(pspoll->bssid, vp->bssid, ETH_ALEN);
	स_नकल(pspoll->ta, mac, ETH_ALEN);

	rcu_पढ़ो_lock();
	mac80211_hwsim_tx_frame(data->hw, skb,
				rcu_dereference(vअगर->chanctx_conf)->def.chan);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम hwsim_send_nullfunc(काष्ठा mac80211_hwsim_data *data, u8 *mac,
				काष्ठा ieee80211_vअगर *vअगर, पूर्णांक ps)
अणु
	काष्ठा hwsim_vअगर_priv *vp = (व्योम *)vअगर->drv_priv;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_hdr *hdr;

	अगर (!vp->assoc)
		वापस;

	wiphy_dbg(data->hw->wiphy,
		  "%s: send data::nullfunc to %pM ps=%d\n",
		  __func__, vp->bssid, ps);

	skb = dev_alloc_skb(माप(*hdr));
	अगर (!skb)
		वापस;
	hdr = skb_put(skb, माप(*hdr) - ETH_ALEN);
	hdr->frame_control = cpu_to_le16(IEEE80211_FTYPE_DATA |
					 IEEE80211_STYPE_शून्यFUNC |
					 IEEE80211_FCTL_TODS |
					 (ps ? IEEE80211_FCTL_PM : 0));
	hdr->duration_id = cpu_to_le16(0);
	स_नकल(hdr->addr1, vp->bssid, ETH_ALEN);
	स_नकल(hdr->addr2, mac, ETH_ALEN);
	स_नकल(hdr->addr3, vp->bssid, ETH_ALEN);

	rcu_पढ़ो_lock();
	mac80211_hwsim_tx_frame(data->hw, skb,
				rcu_dereference(vअगर->chanctx_conf)->def.chan);
	rcu_पढ़ो_unlock();
पूर्ण


अटल व्योम hwsim_send_nullfunc_ps(व्योम *dat, u8 *mac,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mac80211_hwsim_data *data = dat;
	hwsim_send_nullfunc(data, mac, vअगर, 1);
पूर्ण

अटल व्योम hwsim_send_nullfunc_no_ps(व्योम *dat, u8 *mac,
				      काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mac80211_hwsim_data *data = dat;
	hwsim_send_nullfunc(data, mac, vअगर, 0);
पूर्ण

अटल पूर्णांक hwsim_fops_ps_पढ़ो(व्योम *dat, u64 *val)
अणु
	काष्ठा mac80211_hwsim_data *data = dat;
	*val = data->ps;
	वापस 0;
पूर्ण

अटल पूर्णांक hwsim_fops_ps_ग_लिखो(व्योम *dat, u64 val)
अणु
	काष्ठा mac80211_hwsim_data *data = dat;
	क्रमागत ps_mode old_ps;

	अगर (val != PS_DISABLED && val != PS_ENABLED && val != PS_AUTO_POLL &&
	    val != PS_MANUAL_POLL)
		वापस -EINVAL;

	अगर (val == PS_MANUAL_POLL) अणु
		अगर (data->ps != PS_ENABLED)
			वापस -EINVAL;
		local_bh_disable();
		ieee80211_iterate_active_पूर्णांकerfaces_atomic(
			data->hw, IEEE80211_IFACE_ITER_NORMAL,
			hwsim_send_ps_poll, data);
		local_bh_enable();
		वापस 0;
	पूर्ण
	old_ps = data->ps;
	data->ps = val;

	local_bh_disable();
	अगर (old_ps == PS_DISABLED && val != PS_DISABLED) अणु
		ieee80211_iterate_active_पूर्णांकerfaces_atomic(
			data->hw, IEEE80211_IFACE_ITER_NORMAL,
			hwsim_send_nullfunc_ps, data);
	पूर्ण अन्यथा अगर (old_ps != PS_DISABLED && val == PS_DISABLED) अणु
		ieee80211_iterate_active_पूर्णांकerfaces_atomic(
			data->hw, IEEE80211_IFACE_ITER_NORMAL,
			hwsim_send_nullfunc_no_ps, data);
	पूर्ण
	local_bh_enable();

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(hwsim_fops_ps, hwsim_fops_ps_पढ़ो, hwsim_fops_ps_ग_लिखो,
			 "%llu\n");

अटल पूर्णांक hwsim_ग_लिखो_simulate_radar(व्योम *dat, u64 val)
अणु
	काष्ठा mac80211_hwsim_data *data = dat;

	ieee80211_radar_detected(data->hw);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(hwsim_simulate_radar, शून्य,
			 hwsim_ग_लिखो_simulate_radar, "%llu\n");

अटल पूर्णांक hwsim_fops_group_पढ़ो(व्योम *dat, u64 *val)
अणु
	काष्ठा mac80211_hwsim_data *data = dat;
	*val = data->group;
	वापस 0;
पूर्ण

अटल पूर्णांक hwsim_fops_group_ग_लिखो(व्योम *dat, u64 val)
अणु
	काष्ठा mac80211_hwsim_data *data = dat;
	data->group = val;
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(hwsim_fops_group,
			 hwsim_fops_group_पढ़ो, hwsim_fops_group_ग_लिखो,
			 "%llx\n");

अटल netdev_tx_t hwsim_mon_xmit(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev)
अणु
	/* TODO: allow packet injection */
	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल अंतरभूत u64 mac80211_hwsim_get_tsf_raw(व्योम)
अणु
	वापस kसमय_प्रकारo_us(kसमय_get_real());
पूर्ण

अटल __le64 __mac80211_hwsim_get_tsf(काष्ठा mac80211_hwsim_data *data)
अणु
	u64 now = mac80211_hwsim_get_tsf_raw();
	वापस cpu_to_le64(now + data->tsf_offset);
पूर्ण

अटल u64 mac80211_hwsim_get_tsf(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mac80211_hwsim_data *data = hw->priv;
	वापस le64_to_cpu(__mac80211_hwsim_get_tsf(data));
पूर्ण

अटल व्योम mac80211_hwsim_set_tsf(काष्ठा ieee80211_hw *hw,
		काष्ठा ieee80211_vअगर *vअगर, u64 tsf)
अणु
	काष्ठा mac80211_hwsim_data *data = hw->priv;
	u64 now = mac80211_hwsim_get_tsf(hw, vअगर);
	u32 bcn_पूर्णांक = data->beacon_पूर्णांक;
	u64 delta = असल(tsf - now);

	/* adjust after beaconing with new बारtamp at old TBTT */
	अगर (tsf > now) अणु
		data->tsf_offset += delta;
		data->bcn_delta = करो_भाग(delta, bcn_पूर्णांक);
	पूर्ण अन्यथा अणु
		data->tsf_offset -= delta;
		data->bcn_delta = -(s64)करो_भाग(delta, bcn_पूर्णांक);
	पूर्ण
पूर्ण

अटल व्योम mac80211_hwsim_monitor_rx(काष्ठा ieee80211_hw *hw,
				      काष्ठा sk_buff *tx_skb,
				      काष्ठा ieee80211_channel *chan)
अणु
	काष्ठा mac80211_hwsim_data *data = hw->priv;
	काष्ठा sk_buff *skb;
	काष्ठा hwsim_radiotap_hdr *hdr;
	u16 flags, bitrate;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(tx_skb);
	काष्ठा ieee80211_rate *txrate = ieee80211_get_tx_rate(hw, info);

	अगर (!txrate)
		bitrate = 0;
	अन्यथा
		bitrate = txrate->bitrate;

	अगर (!netअगर_running(hwsim_mon))
		वापस;

	skb = skb_copy_expand(tx_skb, माप(*hdr), 0, GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस;

	hdr = skb_push(skb, माप(*hdr));
	hdr->hdr.it_version = PKTHDR_RADIOTAP_VERSION;
	hdr->hdr.it_pad = 0;
	hdr->hdr.it_len = cpu_to_le16(माप(*hdr));
	hdr->hdr.it_present = cpu_to_le32((1 << IEEE80211_RADIOTAP_FLAGS) |
					  (1 << IEEE80211_RADIOTAP_RATE) |
					  (1 << IEEE80211_RADIOTAP_TSFT) |
					  (1 << IEEE80211_RADIOTAP_CHANNEL));
	hdr->rt_tsft = __mac80211_hwsim_get_tsf(data);
	hdr->rt_flags = 0;
	hdr->rt_rate = bitrate / 5;
	hdr->rt_channel = cpu_to_le16(chan->center_freq);
	flags = IEEE80211_CHAN_2GHZ;
	अगर (txrate && txrate->flags & IEEE80211_RATE_ERP_G)
		flags |= IEEE80211_CHAN_OFDM;
	अन्यथा
		flags |= IEEE80211_CHAN_CCK;
	hdr->rt_chbiपंचांगask = cpu_to_le16(flags);

	skb->dev = hwsim_mon;
	skb_reset_mac_header(skb);
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb->pkt_type = PACKET_OTHERHOST;
	skb->protocol = htons(ETH_P_802_2);
	स_रखो(skb->cb, 0, माप(skb->cb));
	netअगर_rx(skb);
पूर्ण


अटल व्योम mac80211_hwsim_monitor_ack(काष्ठा ieee80211_channel *chan,
				       स्थिर u8 *addr)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा hwsim_radiotap_ack_hdr *hdr;
	u16 flags;
	काष्ठा ieee80211_hdr *hdr11;

	अगर (!netअगर_running(hwsim_mon))
		वापस;

	skb = dev_alloc_skb(100);
	अगर (skb == शून्य)
		वापस;

	hdr = skb_put(skb, माप(*hdr));
	hdr->hdr.it_version = PKTHDR_RADIOTAP_VERSION;
	hdr->hdr.it_pad = 0;
	hdr->hdr.it_len = cpu_to_le16(माप(*hdr));
	hdr->hdr.it_present = cpu_to_le32((1 << IEEE80211_RADIOTAP_FLAGS) |
					  (1 << IEEE80211_RADIOTAP_CHANNEL));
	hdr->rt_flags = 0;
	hdr->pad = 0;
	hdr->rt_channel = cpu_to_le16(chan->center_freq);
	flags = IEEE80211_CHAN_2GHZ;
	hdr->rt_chbiपंचांगask = cpu_to_le16(flags);

	hdr11 = skb_put(skb, 10);
	hdr11->frame_control = cpu_to_le16(IEEE80211_FTYPE_CTL |
					   IEEE80211_STYPE_ACK);
	hdr11->duration_id = cpu_to_le16(0);
	स_नकल(hdr11->addr1, addr, ETH_ALEN);

	skb->dev = hwsim_mon;
	skb_reset_mac_header(skb);
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb->pkt_type = PACKET_OTHERHOST;
	skb->protocol = htons(ETH_P_802_2);
	स_रखो(skb->cb, 0, माप(skb->cb));
	netअगर_rx(skb);
पूर्ण

काष्ठा mac80211_hwsim_addr_match_data अणु
	u8 addr[ETH_ALEN];
	bool ret;
पूर्ण;

अटल व्योम mac80211_hwsim_addr_iter(व्योम *data, u8 *mac,
				     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mac80211_hwsim_addr_match_data *md = data;

	अगर (स_भेद(mac, md->addr, ETH_ALEN) == 0)
		md->ret = true;
पूर्ण

अटल bool mac80211_hwsim_addr_match(काष्ठा mac80211_hwsim_data *data,
				      स्थिर u8 *addr)
अणु
	काष्ठा mac80211_hwsim_addr_match_data md = अणु
		.ret = false,
	पूर्ण;

	अगर (data->scanning && स_भेद(addr, data->scan_addr, ETH_ALEN) == 0)
		वापस true;

	स_नकल(md.addr, addr, ETH_ALEN);

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(data->hw,
						   IEEE80211_IFACE_ITER_NORMAL,
						   mac80211_hwsim_addr_iter,
						   &md);

	वापस md.ret;
पूर्ण

अटल bool hwsim_ps_rx_ok(काष्ठा mac80211_hwsim_data *data,
			   काष्ठा sk_buff *skb)
अणु
	चयन (data->ps) अणु
	हाल PS_DISABLED:
		वापस true;
	हाल PS_ENABLED:
		वापस false;
	हाल PS_AUTO_POLL:
		/* TODO: accept (some) Beacons by शेष and other frames only
		 * अगर pending PS-Poll has been sent */
		वापस true;
	हाल PS_MANUAL_POLL:
		/* Allow unicast frames to own address अगर there is a pending
		 * PS-Poll */
		अगर (data->ps_poll_pending &&
		    mac80211_hwsim_addr_match(data, skb->data + 4)) अणु
			data->ps_poll_pending = false;
			वापस true;
		पूर्ण
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक hwsim_unicast_netgroup(काष्ठा mac80211_hwsim_data *data,
				  काष्ठा sk_buff *skb, पूर्णांक portid)
अणु
	काष्ठा net *net;
	bool found = false;
	पूर्णांक res = -ENOENT;

	rcu_पढ़ो_lock();
	क्रम_each_net_rcu(net) अणु
		अगर (data->netgroup == hwsim_net_get_netgroup(net)) अणु
			res = genlmsg_unicast(net, skb, portid);
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (!found)
		nlmsg_मुक्त(skb);

	वापस res;
पूर्ण

अटल व्योम mac80211_hwsim_config_mac_nl(काष्ठा ieee80211_hw *hw,
					 स्थिर u8 *addr, bool add)
अणु
	काष्ठा mac80211_hwsim_data *data = hw->priv;
	u32 _portid = READ_ONCE(data->wmediumd);
	काष्ठा sk_buff *skb;
	व्योम *msg_head;

	अगर (!_portid && !hwsim_virtio_enabled)
		वापस;

	skb = genlmsg_new(GENLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	अगर (!skb)
		वापस;

	msg_head = genlmsg_put(skb, 0, 0, &hwsim_genl_family, 0,
			       add ? HWSIM_CMD_ADD_MAC_ADDR :
				     HWSIM_CMD_DEL_MAC_ADDR);
	अगर (!msg_head) अणु
		pr_debug("mac80211_hwsim: problem with msg_head\n");
		जाओ nla_put_failure;
	पूर्ण

	अगर (nla_put(skb, HWSIM_ATTR_ADDR_TRANSMITTER,
		    ETH_ALEN, data->addresses[1].addr))
		जाओ nla_put_failure;

	अगर (nla_put(skb, HWSIM_ATTR_ADDR_RECEIVER, ETH_ALEN, addr))
		जाओ nla_put_failure;

	genlmsg_end(skb, msg_head);

	अगर (hwsim_virtio_enabled)
		hwsim_tx_virtio(data, skb);
	अन्यथा
		hwsim_unicast_netgroup(data, skb, _portid);
	वापस;
nla_put_failure:
	nlmsg_मुक्त(skb);
पूर्ण

अटल अंतरभूत u16 trans_tx_rate_flags_ieee2hwsim(काष्ठा ieee80211_tx_rate *rate)
अणु
	u16 result = 0;

	अगर (rate->flags & IEEE80211_TX_RC_USE_RTS_CTS)
		result |= MAC80211_HWSIM_TX_RC_USE_RTS_CTS;
	अगर (rate->flags & IEEE80211_TX_RC_USE_CTS_PROTECT)
		result |= MAC80211_HWSIM_TX_RC_USE_CTS_PROTECT;
	अगर (rate->flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE)
		result |= MAC80211_HWSIM_TX_RC_USE_SHORT_PREAMBLE;
	अगर (rate->flags & IEEE80211_TX_RC_MCS)
		result |= MAC80211_HWSIM_TX_RC_MCS;
	अगर (rate->flags & IEEE80211_TX_RC_GREEN_FIELD)
		result |= MAC80211_HWSIM_TX_RC_GREEN_FIELD;
	अगर (rate->flags & IEEE80211_TX_RC_40_MHZ_WIDTH)
		result |= MAC80211_HWSIM_TX_RC_40_MHZ_WIDTH;
	अगर (rate->flags & IEEE80211_TX_RC_DUP_DATA)
		result |= MAC80211_HWSIM_TX_RC_DUP_DATA;
	अगर (rate->flags & IEEE80211_TX_RC_SHORT_GI)
		result |= MAC80211_HWSIM_TX_RC_SHORT_GI;
	अगर (rate->flags & IEEE80211_TX_RC_VHT_MCS)
		result |= MAC80211_HWSIM_TX_RC_VHT_MCS;
	अगर (rate->flags & IEEE80211_TX_RC_80_MHZ_WIDTH)
		result |= MAC80211_HWSIM_TX_RC_80_MHZ_WIDTH;
	अगर (rate->flags & IEEE80211_TX_RC_160_MHZ_WIDTH)
		result |= MAC80211_HWSIM_TX_RC_160_MHZ_WIDTH;

	वापस result;
पूर्ण

अटल व्योम mac80211_hwsim_tx_frame_nl(काष्ठा ieee80211_hw *hw,
				       काष्ठा sk_buff *my_skb,
				       पूर्णांक dst_portid)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा mac80211_hwsim_data *data = hw->priv;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) my_skb->data;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(my_skb);
	व्योम *msg_head;
	अचिन्हित पूर्णांक hwsim_flags = 0;
	पूर्णांक i;
	काष्ठा hwsim_tx_rate tx_attempts[IEEE80211_TX_MAX_RATES];
	काष्ठा hwsim_tx_rate_flag tx_attempts_flags[IEEE80211_TX_MAX_RATES];
	uपूर्णांकptr_t cookie;

	अगर (data->ps != PS_DISABLED)
		hdr->frame_control |= cpu_to_le16(IEEE80211_FCTL_PM);
	/* If the queue contains MAX_QUEUE skb's drop some */
	अगर (skb_queue_len(&data->pending) >= MAX_QUEUE) अणु
		/* Droping until WARN_QUEUE level */
		जबतक (skb_queue_len(&data->pending) >= WARN_QUEUE) अणु
			ieee80211_मुक्त_txskb(hw, skb_dequeue(&data->pending));
			data->tx_dropped++;
		पूर्ण
	पूर्ण

	skb = genlmsg_new(GENLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	अगर (skb == शून्य)
		जाओ nla_put_failure;

	msg_head = genlmsg_put(skb, 0, 0, &hwsim_genl_family, 0,
			       HWSIM_CMD_FRAME);
	अगर (msg_head == शून्य) अणु
		pr_debug("mac80211_hwsim: problem with msg_head\n");
		जाओ nla_put_failure;
	पूर्ण

	अगर (nla_put(skb, HWSIM_ATTR_ADDR_TRANSMITTER,
		    ETH_ALEN, data->addresses[1].addr))
		जाओ nla_put_failure;

	/* We get the skb->data */
	अगर (nla_put(skb, HWSIM_ATTR_FRAME, my_skb->len, my_skb->data))
		जाओ nla_put_failure;

	/* We get the flags क्रम this transmission, and we translate them to
	   wmediumd flags  */

	अगर (info->flags & IEEE80211_TX_CTL_REQ_TX_STATUS)
		hwsim_flags |= HWSIM_TX_CTL_REQ_TX_STATUS;

	अगर (info->flags & IEEE80211_TX_CTL_NO_ACK)
		hwsim_flags |= HWSIM_TX_CTL_NO_ACK;

	अगर (nla_put_u32(skb, HWSIM_ATTR_FLAGS, hwsim_flags))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, HWSIM_ATTR_FREQ, data->channel->center_freq))
		जाओ nla_put_failure;

	/* We get the tx control (rate and retries) info*/

	क्रम (i = 0; i < IEEE80211_TX_MAX_RATES; i++) अणु
		tx_attempts[i].idx = info->status.rates[i].idx;
		tx_attempts_flags[i].idx = info->status.rates[i].idx;
		tx_attempts[i].count = info->status.rates[i].count;
		tx_attempts_flags[i].flags =
				trans_tx_rate_flags_ieee2hwsim(
						&info->status.rates[i]);
	पूर्ण

	अगर (nla_put(skb, HWSIM_ATTR_TX_INFO,
		    माप(काष्ठा hwsim_tx_rate)*IEEE80211_TX_MAX_RATES,
		    tx_attempts))
		जाओ nla_put_failure;

	अगर (nla_put(skb, HWSIM_ATTR_TX_INFO_FLAGS,
		    माप(काष्ठा hwsim_tx_rate_flag) * IEEE80211_TX_MAX_RATES,
		    tx_attempts_flags))
		जाओ nla_put_failure;

	/* We create a cookie to identअगरy this skb */
	data->pending_cookie++;
	cookie = data->pending_cookie;
	info->rate_driver_data[0] = (व्योम *)cookie;
	अगर (nla_put_u64_64bit(skb, HWSIM_ATTR_COOKIE, cookie, HWSIM_ATTR_PAD))
		जाओ nla_put_failure;

	genlmsg_end(skb, msg_head);

	अगर (hwsim_virtio_enabled) अणु
		अगर (hwsim_tx_virtio(data, skb))
			जाओ err_मुक्त_txskb;
	पूर्ण अन्यथा अणु
		अगर (hwsim_unicast_netgroup(data, skb, dst_portid))
			जाओ err_मुक्त_txskb;
	पूर्ण

	/* Enqueue the packet */
	skb_queue_tail(&data->pending, my_skb);
	data->tx_pkts++;
	data->tx_bytes += my_skb->len;
	वापस;

nla_put_failure:
	nlmsg_मुक्त(skb);
err_मुक्त_txskb:
	pr_debug("mac80211_hwsim: error occurred in %s\n", __func__);
	ieee80211_मुक्त_txskb(hw, my_skb);
	data->tx_failed++;
पूर्ण

अटल bool hwsim_chans_compat(काष्ठा ieee80211_channel *c1,
			       काष्ठा ieee80211_channel *c2)
अणु
	अगर (!c1 || !c2)
		वापस false;

	वापस c1->center_freq == c2->center_freq;
पूर्ण

काष्ठा tx_iter_data अणु
	काष्ठा ieee80211_channel *channel;
	bool receive;
पूर्ण;

अटल व्योम mac80211_hwsim_tx_iter(व्योम *_data, u8 *addr,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा tx_iter_data *data = _data;

	अगर (!vअगर->chanctx_conf)
		वापस;

	अगर (!hwsim_chans_compat(data->channel,
				rcu_dereference(vअगर->chanctx_conf)->def.chan))
		वापस;

	data->receive = true;
पूर्ण

अटल व्योम mac80211_hwsim_add_venकरोr_rtap(काष्ठा sk_buff *skb)
अणु
	/*
	 * To enable this code, #घोषणा the HWSIM_RADIOTAP_OUI,
	 * e.g. like this:
	 * #घोषणा HWSIM_RADIOTAP_OUI "\x02\x00\x00"
	 * (but you should use a valid OUI, not that)
	 *
	 * If anyone wants to 'donate' a radiotap OUI/subns code
	 * please send a patch removing this #अगर_घोषित and changing
	 * the values accordingly.
	 */
#अगर_घोषित HWSIM_RADIOTAP_OUI
	काष्ठा ieee80211_venकरोr_radiotap *rtap;

	/*
	 * Note that this code requires the headroom in the SKB
	 * that was allocated earlier.
	 */
	rtap = skb_push(skb, माप(*rtap) + 8 + 4);
	rtap->oui[0] = HWSIM_RADIOTAP_OUI[0];
	rtap->oui[1] = HWSIM_RADIOTAP_OUI[1];
	rtap->oui[2] = HWSIM_RADIOTAP_OUI[2];
	rtap->subns = 127;

	/*
	 * Radiotap venकरोr namespaces can (and should) also be
	 * split पूर्णांकo fields by using the standard radiotap
	 * presence biपंचांगap mechanism. Use just BIT(0) here क्रम
	 * the presence biपंचांगap.
	 */
	rtap->present = BIT(0);
	/* We have 8 bytes of (dummy) data */
	rtap->len = 8;
	/* For testing, also require it to be aligned */
	rtap->align = 8;
	/* And also test that padding works, 4 bytes */
	rtap->pad = 4;
	/* push the data */
	स_नकल(rtap->data, "ABCDEFGH", 8);
	/* make sure to clear padding, mac80211 करोesn't */
	स_रखो(rtap->data + 8, 0, 4);

	IEEE80211_SKB_RXCB(skb)->flag |= RX_FLAG_RADIOTAP_VENDOR_DATA;
#पूर्ण_अगर
पूर्ण

अटल bool mac80211_hwsim_tx_frame_no_nl(काष्ठा ieee80211_hw *hw,
					  काष्ठा sk_buff *skb,
					  काष्ठा ieee80211_channel *chan)
अणु
	काष्ठा mac80211_hwsim_data *data = hw->priv, *data2;
	bool ack = false;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_rx_status rx_status;
	u64 now;

	स_रखो(&rx_status, 0, माप(rx_status));
	rx_status.flag |= RX_FLAG_MACTIME_START;
	rx_status.freq = chan->center_freq;
	rx_status.freq_offset = chan->freq_offset ? 1 : 0;
	rx_status.band = chan->band;
	अगर (info->control.rates[0].flags & IEEE80211_TX_RC_VHT_MCS) अणु
		rx_status.rate_idx =
			ieee80211_rate_get_vht_mcs(&info->control.rates[0]);
		rx_status.nss =
			ieee80211_rate_get_vht_nss(&info->control.rates[0]);
		rx_status.encoding = RX_ENC_VHT;
	पूर्ण अन्यथा अणु
		rx_status.rate_idx = info->control.rates[0].idx;
		अगर (info->control.rates[0].flags & IEEE80211_TX_RC_MCS)
			rx_status.encoding = RX_ENC_HT;
	पूर्ण
	अगर (info->control.rates[0].flags & IEEE80211_TX_RC_40_MHZ_WIDTH)
		rx_status.bw = RATE_INFO_BW_40;
	अन्यथा अगर (info->control.rates[0].flags & IEEE80211_TX_RC_80_MHZ_WIDTH)
		rx_status.bw = RATE_INFO_BW_80;
	अन्यथा अगर (info->control.rates[0].flags & IEEE80211_TX_RC_160_MHZ_WIDTH)
		rx_status.bw = RATE_INFO_BW_160;
	अन्यथा
		rx_status.bw = RATE_INFO_BW_20;
	अगर (info->control.rates[0].flags & IEEE80211_TX_RC_SHORT_GI)
		rx_status.enc_flags |= RX_ENC_FLAG_SHORT_GI;
	/* TODO: simulate real संकेत strength (and optional packet loss) */
	rx_status.संकेत = -50;
	अगर (info->control.vअगर)
		rx_status.संकेत += info->control.vअगर->bss_conf.txघातer;

	अगर (data->ps != PS_DISABLED)
		hdr->frame_control |= cpu_to_le16(IEEE80211_FCTL_PM);

	/* release the skb's source info */
	skb_orphan(skb);
	skb_dst_drop(skb);
	skb->mark = 0;
	skb_ext_reset(skb);
	nf_reset_ct(skb);

	/*
	 * Get असलolute maस_समय here so all HWs RX at the "same time", and
	 * असलolute TX समय क्रम beacon maस_समय so the बारtamp matches.
	 * Giving beacons a dअगरferent maस_समय than non-beacons looks messy, but
	 * it helps the Toffset be exact and a ~10us maस_समय discrepancy
	 * probably करोesn't really matter.
	 */
	अगर (ieee80211_is_beacon(hdr->frame_control) ||
	    ieee80211_is_probe_resp(hdr->frame_control)) अणु
		rx_status.bootसमय_ns = kसमय_get_bootसमय_ns();
		now = data->असल_bcn_ts;
	पूर्ण अन्यथा अणु
		now = mac80211_hwsim_get_tsf_raw();
	पूर्ण

	/* Copy skb to all enabled radios that are on the current frequency */
	spin_lock(&hwsim_radio_lock);
	list_क्रम_each_entry(data2, &hwsim_radios, list) अणु
		काष्ठा sk_buff *nskb;
		काष्ठा tx_iter_data tx_iter_data = अणु
			.receive = false,
			.channel = chan,
		पूर्ण;

		अगर (data == data2)
			जारी;

		अगर (!data2->started || (data2->idle && !data2->पंचांगp_chan) ||
		    !hwsim_ps_rx_ok(data2, skb))
			जारी;

		अगर (!(data->group & data2->group))
			जारी;

		अगर (data->netgroup != data2->netgroup)
			जारी;

		अगर (!hwsim_chans_compat(chan, data2->पंचांगp_chan) &&
		    !hwsim_chans_compat(chan, data2->channel)) अणु
			ieee80211_iterate_active_पूर्णांकerfaces_atomic(
				data2->hw, IEEE80211_IFACE_ITER_NORMAL,
				mac80211_hwsim_tx_iter, &tx_iter_data);
			अगर (!tx_iter_data.receive)
				जारी;
		पूर्ण

		/*
		 * reserve some space क्रम our venकरोr and the normal
		 * radiotap header, since we're copying anyway
		 */
		अगर (skb->len < PAGE_SIZE && paged_rx) अणु
			काष्ठा page *page = alloc_page(GFP_ATOMIC);

			अगर (!page)
				जारी;

			nskb = dev_alloc_skb(128);
			अगर (!nskb) अणु
				__मुक्त_page(page);
				जारी;
			पूर्ण

			स_नकल(page_address(page), skb->data, skb->len);
			skb_add_rx_frag(nskb, 0, page, 0, skb->len, skb->len);
		पूर्ण अन्यथा अणु
			nskb = skb_copy(skb, GFP_ATOMIC);
			अगर (!nskb)
				जारी;
		पूर्ण

		अगर (mac80211_hwsim_addr_match(data2, hdr->addr1))
			ack = true;

		rx_status.maस_समय = now + data2->tsf_offset;

		स_नकल(IEEE80211_SKB_RXCB(nskb), &rx_status, माप(rx_status));

		mac80211_hwsim_add_venकरोr_rtap(nskb);

		data2->rx_pkts++;
		data2->rx_bytes += nskb->len;
		ieee80211_rx_irqsafe(data2->hw, nskb);
	पूर्ण
	spin_unlock(&hwsim_radio_lock);

	वापस ack;
पूर्ण

अटल व्योम mac80211_hwsim_tx(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_tx_control *control,
			      काष्ठा sk_buff *skb)
अणु
	काष्ठा mac80211_hwsim_data *data = hw->priv;
	काष्ठा ieee80211_tx_info *txi = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	काष्ठा ieee80211_channel *channel;
	bool ack;
	u32 _portid;

	अगर (WARN_ON(skb->len < 10)) अणु
		/* Should not happen; just a sanity check क्रम addr1 use */
		ieee80211_मुक्त_txskb(hw, skb);
		वापस;
	पूर्ण

	अगर (!data->use_chanctx) अणु
		channel = data->channel;
	पूर्ण अन्यथा अगर (txi->hw_queue == 4) अणु
		channel = data->पंचांगp_chan;
	पूर्ण अन्यथा अणु
		chanctx_conf = rcu_dereference(txi->control.vअगर->chanctx_conf);
		अगर (chanctx_conf)
			channel = chanctx_conf->def.chan;
		अन्यथा
			channel = शून्य;
	पूर्ण

	अगर (WARN(!channel, "TX w/o channel - queue = %d\n", txi->hw_queue)) अणु
		ieee80211_मुक्त_txskb(hw, skb);
		वापस;
	पूर्ण

	अगर (data->idle && !data->पंचांगp_chan) अणु
		wiphy_dbg(hw->wiphy, "Trying to TX when idle - reject\n");
		ieee80211_मुक्त_txskb(hw, skb);
		वापस;
	पूर्ण

	अगर (txi->control.vअगर)
		hwsim_check_magic(txi->control.vअगर);
	अगर (control->sta)
		hwsim_check_sta_magic(control->sta);

	अगर (ieee80211_hw_check(hw, SUPPORTS_RC_TABLE))
		ieee80211_get_tx_rates(txi->control.vअगर, control->sta, skb,
				       txi->control.rates,
				       ARRAY_SIZE(txi->control.rates));

	अगर (skb->len >= 24 + 8 &&
	    ieee80211_is_probe_resp(hdr->frame_control)) अणु
		/* fake header transmission समय */
		काष्ठा ieee80211_mgmt *mgmt;
		काष्ठा ieee80211_rate *txrate;
		/* TODO: get MCS */
		पूर्णांक bitrate = 100;
		u64 ts;

		mgmt = (काष्ठा ieee80211_mgmt *)skb->data;
		txrate = ieee80211_get_tx_rate(hw, txi);
		अगर (txrate)
			bitrate = txrate->bitrate;
		ts = mac80211_hwsim_get_tsf_raw();
		mgmt->u.probe_resp.बारtamp =
			cpu_to_le64(ts + data->tsf_offset +
				    24 * 8 * 10 / bitrate);
	पूर्ण

	mac80211_hwsim_monitor_rx(hw, skb, channel);

	/* wmediumd mode check */
	_portid = READ_ONCE(data->wmediumd);

	अगर (_portid || hwsim_virtio_enabled)
		वापस mac80211_hwsim_tx_frame_nl(hw, skb, _portid);

	/* NO wmediumd detected, perfect medium simulation */
	data->tx_pkts++;
	data->tx_bytes += skb->len;
	ack = mac80211_hwsim_tx_frame_no_nl(hw, skb, channel);

	अगर (ack && skb->len >= 16)
		mac80211_hwsim_monitor_ack(channel, hdr->addr2);

	ieee80211_tx_info_clear_status(txi);

	/* frame was transmitted at most favorable rate at first attempt */
	txi->control.rates[0].count = 1;
	txi->control.rates[1].idx = -1;

	अगर (!(txi->flags & IEEE80211_TX_CTL_NO_ACK) && ack)
		txi->flags |= IEEE80211_TX_STAT_ACK;
	ieee80211_tx_status_irqsafe(hw, skb);
पूर्ण


अटल पूर्णांक mac80211_hwsim_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mac80211_hwsim_data *data = hw->priv;
	wiphy_dbg(hw->wiphy, "%s\n", __func__);
	data->started = true;
	वापस 0;
पूर्ण


अटल व्योम mac80211_hwsim_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mac80211_hwsim_data *data = hw->priv;

	data->started = false;
	hrसमयr_cancel(&data->beacon_समयr);

	जबतक (!skb_queue_empty(&data->pending))
		ieee80211_मुक्त_txskb(hw, skb_dequeue(&data->pending));

	wiphy_dbg(hw->wiphy, "%s\n", __func__);
पूर्ण


अटल पूर्णांक mac80211_hwsim_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
					काष्ठा ieee80211_vअगर *vअगर)
अणु
	wiphy_dbg(hw->wiphy, "%s (type=%d mac_addr=%pM)\n",
		  __func__, ieee80211_vअगर_type_p2p(vअगर),
		  vअगर->addr);
	hwsim_set_magic(vअगर);

	अगर (vअगर->type != NL80211_IFTYPE_MONITOR)
		mac80211_hwsim_config_mac_nl(hw, vअगर->addr, true);

	vअगर->cab_queue = 0;
	vअगर->hw_queue[IEEE80211_AC_VO] = 0;
	vअगर->hw_queue[IEEE80211_AC_VI] = 1;
	vअगर->hw_queue[IEEE80211_AC_BE] = 2;
	vअगर->hw_queue[IEEE80211_AC_BK] = 3;

	वापस 0;
पूर्ण


अटल पूर्णांक mac80211_hwsim_change_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
					   काष्ठा ieee80211_vअगर *vअगर,
					   क्रमागत nl80211_अगरtype newtype,
					   bool newp2p)
अणु
	newtype = ieee80211_अगरtype_p2p(newtype, newp2p);
	wiphy_dbg(hw->wiphy,
		  "%s (old type=%d, new type=%d, mac_addr=%pM)\n",
		  __func__, ieee80211_vअगर_type_p2p(vअगर),
		    newtype, vअगर->addr);
	hwsim_check_magic(vअगर);

	/*
	 * पूर्णांकerface may change from non-AP to AP in
	 * which हाल this needs to be set up again
	 */
	vअगर->cab_queue = 0;

	वापस 0;
पूर्ण

अटल व्योम mac80211_hwsim_हटाओ_पूर्णांकerface(
	काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	wiphy_dbg(hw->wiphy, "%s (type=%d mac_addr=%pM)\n",
		  __func__, ieee80211_vअगर_type_p2p(vअगर),
		  vअगर->addr);
	hwsim_check_magic(vअगर);
	hwsim_clear_magic(vअगर);
	अगर (vअगर->type != NL80211_IFTYPE_MONITOR)
		mac80211_hwsim_config_mac_nl(hw, vअगर->addr, false);
पूर्ण

अटल व्योम mac80211_hwsim_tx_frame(काष्ठा ieee80211_hw *hw,
				    काष्ठा sk_buff *skb,
				    काष्ठा ieee80211_channel *chan)
अणु
	काष्ठा mac80211_hwsim_data *data = hw->priv;
	u32 _pid = READ_ONCE(data->wmediumd);

	अगर (ieee80211_hw_check(hw, SUPPORTS_RC_TABLE)) अणु
		काष्ठा ieee80211_tx_info *txi = IEEE80211_SKB_CB(skb);
		ieee80211_get_tx_rates(txi->control.vअगर, शून्य, skb,
				       txi->control.rates,
				       ARRAY_SIZE(txi->control.rates));
	पूर्ण

	mac80211_hwsim_monitor_rx(hw, skb, chan);

	अगर (_pid || hwsim_virtio_enabled)
		वापस mac80211_hwsim_tx_frame_nl(hw, skb, _pid);

	mac80211_hwsim_tx_frame_no_nl(hw, skb, chan);
	dev_kमुक्त_skb(skb);
पूर्ण

अटल व्योम mac80211_hwsim_beacon_tx(व्योम *arg, u8 *mac,
				     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mac80211_hwsim_data *data = arg;
	काष्ठा ieee80211_hw *hw = data->hw;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211_rate *txrate;
	काष्ठा ieee80211_mgmt *mgmt;
	काष्ठा sk_buff *skb;
	/* TODO: get MCS */
	पूर्णांक bitrate = 100;

	hwsim_check_magic(vअगर);

	अगर (vअगर->type != NL80211_IFTYPE_AP &&
	    vअगर->type != NL80211_IFTYPE_MESH_POINT &&
	    vअगर->type != NL80211_IFTYPE_ADHOC &&
	    vअगर->type != NL80211_IFTYPE_OCB)
		वापस;

	skb = ieee80211_beacon_get(hw, vअगर);
	अगर (skb == शून्य)
		वापस;
	info = IEEE80211_SKB_CB(skb);
	अगर (ieee80211_hw_check(hw, SUPPORTS_RC_TABLE))
		ieee80211_get_tx_rates(vअगर, शून्य, skb,
				       info->control.rates,
				       ARRAY_SIZE(info->control.rates));

	txrate = ieee80211_get_tx_rate(hw, info);
	अगर (txrate)
		bitrate = txrate->bitrate;

	mgmt = (काष्ठा ieee80211_mgmt *) skb->data;
	/* fake header transmission समय */
	data->असल_bcn_ts = mac80211_hwsim_get_tsf_raw();
	अगर (ieee80211_is_s1g_beacon(mgmt->frame_control)) अणु
		काष्ठा ieee80211_ext *ext = (व्योम *) mgmt;

		ext->u.s1g_beacon.बारtamp = cpu_to_le32(data->असल_bcn_ts +
							  data->tsf_offset +
							  10 * 8 * 10 /
							  bitrate);
	पूर्ण अन्यथा अणु
		mgmt->u.beacon.बारtamp = cpu_to_le64(data->असल_bcn_ts +
						       data->tsf_offset +
						       24 * 8 * 10 /
						       bitrate);
	पूर्ण

	mac80211_hwsim_tx_frame(hw, skb,
				rcu_dereference(vअगर->chanctx_conf)->def.chan);

	जबतक ((skb = ieee80211_get_buffered_bc(hw, vअगर)) != शून्य) अणु
		mac80211_hwsim_tx_frame(hw, skb,
				rcu_dereference(vअगर->chanctx_conf)->def.chan);
	पूर्ण

	अगर (vअगर->csa_active && ieee80211_beacon_cntdwn_is_complete(vअगर))
		ieee80211_csa_finish(vअगर);
पूर्ण

अटल क्रमागत hrसमयr_restart
mac80211_hwsim_beacon(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा mac80211_hwsim_data *data =
		container_of(समयr, काष्ठा mac80211_hwsim_data, beacon_समयr);
	काष्ठा ieee80211_hw *hw = data->hw;
	u64 bcn_पूर्णांक = data->beacon_पूर्णांक;

	अगर (!data->started)
		वापस HRTIMER_NORESTART;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(
		hw, IEEE80211_IFACE_ITER_NORMAL,
		mac80211_hwsim_beacon_tx, data);

	/* beacon at new TBTT + beacon पूर्णांकerval */
	अगर (data->bcn_delta) अणु
		bcn_पूर्णांक -= data->bcn_delta;
		data->bcn_delta = 0;
	पूर्ण
	hrसमयr_क्रमward(&data->beacon_समयr, hrसमयr_get_expires(समयr),
			ns_to_kसमय(bcn_पूर्णांक * NSEC_PER_USEC));
	वापस HRTIMER_RESTART;
पूर्ण

अटल स्थिर अक्षर * स्थिर hwsim_chanwidths[] = अणु
	[NL80211_CHAN_WIDTH_5] = "ht5",
	[NL80211_CHAN_WIDTH_10] = "ht10",
	[NL80211_CHAN_WIDTH_20_NOHT] = "noht",
	[NL80211_CHAN_WIDTH_20] = "ht20",
	[NL80211_CHAN_WIDTH_40] = "ht40",
	[NL80211_CHAN_WIDTH_80] = "vht80",
	[NL80211_CHAN_WIDTH_80P80] = "vht80p80",
	[NL80211_CHAN_WIDTH_160] = "vht160",
	[NL80211_CHAN_WIDTH_1] = "1MHz",
	[NL80211_CHAN_WIDTH_2] = "2MHz",
	[NL80211_CHAN_WIDTH_4] = "4MHz",
	[NL80211_CHAN_WIDTH_8] = "8MHz",
	[NL80211_CHAN_WIDTH_16] = "16MHz",
पूर्ण;

अटल पूर्णांक mac80211_hwsim_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा mac80211_hwsim_data *data = hw->priv;
	काष्ठा ieee80211_conf *conf = &hw->conf;
	अटल स्थिर अक्षर *smps_modes[IEEE80211_SMPS_NUM_MODES] = अणु
		[IEEE80211_SMPS_AUTOMATIC] = "auto",
		[IEEE80211_SMPS_OFF] = "off",
		[IEEE80211_SMPS_STATIC] = "static",
		[IEEE80211_SMPS_DYNAMIC] = "dynamic",
	पूर्ण;
	पूर्णांक idx;

	अगर (conf->chandef.chan)
		wiphy_dbg(hw->wiphy,
			  "%s (freq=%d(%d - %d)/%s idle=%d ps=%d smps=%s)\n",
			  __func__,
			  conf->chandef.chan->center_freq,
			  conf->chandef.center_freq1,
			  conf->chandef.center_freq2,
			  hwsim_chanwidths[conf->chandef.width],
			  !!(conf->flags & IEEE80211_CONF_IDLE),
			  !!(conf->flags & IEEE80211_CONF_PS),
			  smps_modes[conf->smps_mode]);
	अन्यथा
		wiphy_dbg(hw->wiphy,
			  "%s (freq=0 idle=%d ps=%d smps=%s)\n",
			  __func__,
			  !!(conf->flags & IEEE80211_CONF_IDLE),
			  !!(conf->flags & IEEE80211_CONF_PS),
			  smps_modes[conf->smps_mode]);

	data->idle = !!(conf->flags & IEEE80211_CONF_IDLE);

	WARN_ON(conf->chandef.chan && data->use_chanctx);

	mutex_lock(&data->mutex);
	अगर (data->scanning && conf->chandef.chan) अणु
		क्रम (idx = 0; idx < ARRAY_SIZE(data->survey_data); idx++) अणु
			अगर (data->survey_data[idx].channel == data->channel) अणु
				data->survey_data[idx].start =
					data->survey_data[idx].next_start;
				data->survey_data[idx].end = jअगरfies;
				अवरोध;
			पूर्ण
		पूर्ण

		data->channel = conf->chandef.chan;

		क्रम (idx = 0; idx < ARRAY_SIZE(data->survey_data); idx++) अणु
			अगर (data->survey_data[idx].channel &&
			    data->survey_data[idx].channel != data->channel)
				जारी;
			data->survey_data[idx].channel = data->channel;
			data->survey_data[idx].next_start = jअगरfies;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		data->channel = conf->chandef.chan;
	पूर्ण
	mutex_unlock(&data->mutex);

	अगर (!data->started || !data->beacon_पूर्णांक)
		hrसमयr_cancel(&data->beacon_समयr);
	अन्यथा अगर (!hrसमयr_is_queued(&data->beacon_समयr)) अणु
		u64 tsf = mac80211_hwsim_get_tsf(hw, शून्य);
		u32 bcn_पूर्णांक = data->beacon_पूर्णांक;
		u64 until_tbtt = bcn_पूर्णांक - करो_भाग(tsf, bcn_पूर्णांक);

		hrसमयr_start(&data->beacon_समयr,
			      ns_to_kसमय(until_tbtt * NSEC_PER_USEC),
			      HRTIMER_MODE_REL_SOFT);
	पूर्ण

	वापस 0;
पूर्ण


अटल व्योम mac80211_hwsim_configure_filter(काष्ठा ieee80211_hw *hw,
					    अचिन्हित पूर्णांक changed_flags,
					    अचिन्हित पूर्णांक *total_flags,u64 multicast)
अणु
	काष्ठा mac80211_hwsim_data *data = hw->priv;

	wiphy_dbg(hw->wiphy, "%s\n", __func__);

	data->rx_filter = 0;
	अगर (*total_flags & FIF_ALLMULTI)
		data->rx_filter |= FIF_ALLMULTI;
	अगर (*total_flags & FIF_MCAST_ACTION)
		data->rx_filter |= FIF_MCAST_ACTION;

	*total_flags = data->rx_filter;
पूर्ण

अटल व्योम mac80211_hwsim_bcn_en_iter(व्योम *data, u8 *mac,
				       काष्ठा ieee80211_vअगर *vअगर)
अणु
	अचिन्हित पूर्णांक *count = data;
	काष्ठा hwsim_vअगर_priv *vp = (व्योम *)vअगर->drv_priv;

	अगर (vp->bcn_en)
		(*count)++;
पूर्ण

अटल व्योम mac80211_hwsim_bss_info_changed(काष्ठा ieee80211_hw *hw,
					    काष्ठा ieee80211_vअगर *vअगर,
					    काष्ठा ieee80211_bss_conf *info,
					    u32 changed)
अणु
	काष्ठा hwsim_vअगर_priv *vp = (व्योम *)vअगर->drv_priv;
	काष्ठा mac80211_hwsim_data *data = hw->priv;

	hwsim_check_magic(vअगर);

	wiphy_dbg(hw->wiphy, "%s(changed=0x%x vif->addr=%pM)\n",
		  __func__, changed, vअगर->addr);

	अगर (changed & BSS_CHANGED_BSSID) अणु
		wiphy_dbg(hw->wiphy, "%s: BSSID changed: %pM\n",
			  __func__, info->bssid);
		स_नकल(vp->bssid, info->bssid, ETH_ALEN);
	पूर्ण

	अगर (changed & BSS_CHANGED_ASSOC) अणु
		wiphy_dbg(hw->wiphy, "  ASSOC: assoc=%d aid=%d\n",
			  info->assoc, info->aid);
		vp->assoc = info->assoc;
		vp->aid = info->aid;
	पूर्ण

	अगर (changed & BSS_CHANGED_BEACON_ENABLED) अणु
		wiphy_dbg(hw->wiphy, "  BCN EN: %d (BI=%u)\n",
			  info->enable_beacon, info->beacon_पूर्णांक);
		vp->bcn_en = info->enable_beacon;
		अगर (data->started &&
		    !hrसमयr_is_queued(&data->beacon_समयr) &&
		    info->enable_beacon) अणु
			u64 tsf, until_tbtt;
			u32 bcn_पूर्णांक;
			data->beacon_पूर्णांक = info->beacon_पूर्णांक * 1024;
			tsf = mac80211_hwsim_get_tsf(hw, vअगर);
			bcn_पूर्णांक = data->beacon_पूर्णांक;
			until_tbtt = bcn_पूर्णांक - करो_भाग(tsf, bcn_पूर्णांक);

			hrसमयr_start(&data->beacon_समयr,
				      ns_to_kसमय(until_tbtt * NSEC_PER_USEC),
				      HRTIMER_MODE_REL_SOFT);
		पूर्ण अन्यथा अगर (!info->enable_beacon) अणु
			अचिन्हित पूर्णांक count = 0;
			ieee80211_iterate_active_पूर्णांकerfaces_atomic(
				data->hw, IEEE80211_IFACE_ITER_NORMAL,
				mac80211_hwsim_bcn_en_iter, &count);
			wiphy_dbg(hw->wiphy, "  beaconing vifs remaining: %u",
				  count);
			अगर (count == 0) अणु
				hrसमयr_cancel(&data->beacon_समयr);
				data->beacon_पूर्णांक = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_CTS_PROT) अणु
		wiphy_dbg(hw->wiphy, "  ERP_CTS_PROT: %d\n",
			  info->use_cts_prot);
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_PREAMBLE) अणु
		wiphy_dbg(hw->wiphy, "  ERP_PREAMBLE: %d\n",
			  info->use_लघु_preamble);
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		wiphy_dbg(hw->wiphy, "  ERP_SLOT: %d\n", info->use_लघु_slot);
	पूर्ण

	अगर (changed & BSS_CHANGED_HT) अणु
		wiphy_dbg(hw->wiphy, "  HT: op_mode=0x%x\n",
			  info->ht_operation_mode);
	पूर्ण

	अगर (changed & BSS_CHANGED_BASIC_RATES) अणु
		wiphy_dbg(hw->wiphy, "  BASIC_RATES: 0x%llx\n",
			  (अचिन्हित दीर्घ दीर्घ) info->basic_rates);
	पूर्ण

	अगर (changed & BSS_CHANGED_TXPOWER)
		wiphy_dbg(hw->wiphy, "  TX Power: %d dBm\n", info->txघातer);
पूर्ण

अटल पूर्णांक mac80211_hwsim_sta_add(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर,
				  काष्ठा ieee80211_sta *sta)
अणु
	hwsim_check_magic(vअगर);
	hwsim_set_sta_magic(sta);

	वापस 0;
पूर्ण

अटल पूर्णांक mac80211_hwsim_sta_हटाओ(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर,
				     काष्ठा ieee80211_sta *sta)
अणु
	hwsim_check_magic(vअगर);
	hwsim_clear_sta_magic(sta);

	वापस 0;
पूर्ण

अटल व्योम mac80211_hwsim_sta_notअगरy(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_vअगर *vअगर,
				      क्रमागत sta_notअगरy_cmd cmd,
				      काष्ठा ieee80211_sta *sta)
अणु
	hwsim_check_magic(vअगर);

	चयन (cmd) अणु
	हाल STA_NOTIFY_SLEEP:
	हाल STA_NOTIFY_AWAKE:
		/* TODO: make good use of these flags */
		अवरोध;
	शेष:
		WARN(1, "Invalid sta notify: %d\n", cmd);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक mac80211_hwsim_set_tim(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_sta *sta,
				  bool set)
अणु
	hwsim_check_sta_magic(sta);
	वापस 0;
पूर्ण

अटल पूर्णांक mac80211_hwsim_conf_tx(
	काष्ठा ieee80211_hw *hw,
	काष्ठा ieee80211_vअगर *vअगर, u16 queue,
	स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	wiphy_dbg(hw->wiphy,
		  "%s (queue=%d txop=%d cw_min=%d cw_max=%d aifs=%d)\n",
		  __func__, queue,
		  params->txop, params->cw_min,
		  params->cw_max, params->aअगरs);
	वापस 0;
पूर्ण

अटल पूर्णांक mac80211_hwsim_get_survey(काष्ठा ieee80211_hw *hw, पूर्णांक idx,
				     काष्ठा survey_info *survey)
अणु
	काष्ठा mac80211_hwsim_data *hwsim = hw->priv;

	अगर (idx < 0 || idx >= ARRAY_SIZE(hwsim->survey_data))
		वापस -ENOENT;

	mutex_lock(&hwsim->mutex);
	survey->channel = hwsim->survey_data[idx].channel;
	अगर (!survey->channel) अणु
		mutex_unlock(&hwsim->mutex);
		वापस -ENOENT;
	पूर्ण

	/*
	 * Magically conjured dummy values --- this is only ok क्रम simulated hardware.
	 *
	 * A real driver which cannot determine real values noise MUST NOT
	 * report any, especially not a magically conjured ones :-)
	 */
	survey->filled = SURVEY_INFO_NOISE_DBM |
			 SURVEY_INFO_TIME |
			 SURVEY_INFO_TIME_BUSY;
	survey->noise = -92;
	survey->समय =
		jअगरfies_to_msecs(hwsim->survey_data[idx].end -
				 hwsim->survey_data[idx].start);
	/* report 12.5% of channel समय is used */
	survey->समय_busy = survey->समय/8;
	mutex_unlock(&hwsim->mutex);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NL80211_TESTMODE
/*
 * This section contains example code क्रम using netlink
 * attributes with the tesपंचांगode command in nl80211.
 */

/* These क्रमागतs need to be kept in sync with userspace */
क्रमागत hwsim_tesपंचांगode_attr अणु
	__HWSIM_TM_ATTR_INVALID	= 0,
	HWSIM_TM_ATTR_CMD	= 1,
	HWSIM_TM_ATTR_PS	= 2,

	/* keep last */
	__HWSIM_TM_ATTR_AFTER_LAST,
	HWSIM_TM_ATTR_MAX	= __HWSIM_TM_ATTR_AFTER_LAST - 1
पूर्ण;

क्रमागत hwsim_tesपंचांगode_cmd अणु
	HWSIM_TM_CMD_SET_PS		= 0,
	HWSIM_TM_CMD_GET_PS		= 1,
	HWSIM_TM_CMD_STOP_QUEUES	= 2,
	HWSIM_TM_CMD_WAKE_QUEUES	= 3,
पूर्ण;

अटल स्थिर काष्ठा nla_policy hwsim_tesपंचांगode_policy[HWSIM_TM_ATTR_MAX + 1] = अणु
	[HWSIM_TM_ATTR_CMD] = अणु .type = NLA_U32 पूर्ण,
	[HWSIM_TM_ATTR_PS] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक mac80211_hwsim_tesपंचांगode_cmd(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर,
				       व्योम *data, पूर्णांक len)
अणु
	काष्ठा mac80211_hwsim_data *hwsim = hw->priv;
	काष्ठा nlattr *tb[HWSIM_TM_ATTR_MAX + 1];
	काष्ठा sk_buff *skb;
	पूर्णांक err, ps;

	err = nla_parse_deprecated(tb, HWSIM_TM_ATTR_MAX, data, len,
				   hwsim_tesपंचांगode_policy, शून्य);
	अगर (err)
		वापस err;

	अगर (!tb[HWSIM_TM_ATTR_CMD])
		वापस -EINVAL;

	चयन (nla_get_u32(tb[HWSIM_TM_ATTR_CMD])) अणु
	हाल HWSIM_TM_CMD_SET_PS:
		अगर (!tb[HWSIM_TM_ATTR_PS])
			वापस -EINVAL;
		ps = nla_get_u32(tb[HWSIM_TM_ATTR_PS]);
		वापस hwsim_fops_ps_ग_लिखो(hwsim, ps);
	हाल HWSIM_TM_CMD_GET_PS:
		skb = cfg80211_tesपंचांगode_alloc_reply_skb(hw->wiphy,
						nla_total_size(माप(u32)));
		अगर (!skb)
			वापस -ENOMEM;
		अगर (nla_put_u32(skb, HWSIM_TM_ATTR_PS, hwsim->ps))
			जाओ nla_put_failure;
		वापस cfg80211_tesपंचांगode_reply(skb);
	हाल HWSIM_TM_CMD_STOP_QUEUES:
		ieee80211_stop_queues(hw);
		वापस 0;
	हाल HWSIM_TM_CMD_WAKE_QUEUES:
		ieee80211_wake_queues(hw);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

 nla_put_failure:
	kमुक्त_skb(skb);
	वापस -ENOBUFS;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mac80211_hwsim_ampdu_action(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा ieee80211_ampdu_params *params)
अणु
	काष्ठा ieee80211_sta *sta = params->sta;
	क्रमागत ieee80211_ampdu_mlme_action action = params->action;
	u16 tid = params->tid;

	चयन (action) अणु
	हाल IEEE80211_AMPDU_TX_START:
		वापस IEEE80211_AMPDU_TX_START_IMMEDIATE;
	हाल IEEE80211_AMPDU_TX_STOP_CONT:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		ieee80211_stop_tx_ba_cb_irqsafe(vअगर, sta->addr, tid);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_OPERATIONAL:
		अवरोध;
	हाल IEEE80211_AMPDU_RX_START:
	हाल IEEE80211_AMPDU_RX_STOP:
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mac80211_hwsim_flush(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर,
				 u32 queues, bool drop)
अणु
	/* Not implemented, queues only on kernel side */
पूर्ण

अटल व्योम hw_scan_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mac80211_hwsim_data *hwsim =
		container_of(work, काष्ठा mac80211_hwsim_data, hw_scan.work);
	काष्ठा cfg80211_scan_request *req = hwsim->hw_scan_request;
	पूर्णांक dwell, i;

	mutex_lock(&hwsim->mutex);
	अगर (hwsim->scan_chan_idx >= req->n_channels) अणु
		काष्ठा cfg80211_scan_info info = अणु
			.पातed = false,
		पूर्ण;

		wiphy_dbg(hwsim->hw->wiphy, "hw scan complete\n");
		ieee80211_scan_completed(hwsim->hw, &info);
		hwsim->hw_scan_request = शून्य;
		hwsim->hw_scan_vअगर = शून्य;
		hwsim->पंचांगp_chan = शून्य;
		mutex_unlock(&hwsim->mutex);
		mac80211_hwsim_config_mac_nl(hwsim->hw, hwsim->scan_addr,
					     false);
		वापस;
	पूर्ण

	wiphy_dbg(hwsim->hw->wiphy, "hw scan %d MHz\n",
		  req->channels[hwsim->scan_chan_idx]->center_freq);

	hwsim->पंचांगp_chan = req->channels[hwsim->scan_chan_idx];
	अगर (hwsim->पंचांगp_chan->flags & (IEEE80211_CHAN_NO_IR |
				      IEEE80211_CHAN_RADAR) ||
	    !req->n_ssids) अणु
		dwell = 120;
	पूर्ण अन्यथा अणु
		dwell = 30;
		/* send probes */
		क्रम (i = 0; i < req->n_ssids; i++) अणु
			काष्ठा sk_buff *probe;
			काष्ठा ieee80211_mgmt *mgmt;

			probe = ieee80211_probereq_get(hwsim->hw,
						       hwsim->scan_addr,
						       req->ssids[i].ssid,
						       req->ssids[i].ssid_len,
						       req->ie_len);
			अगर (!probe)
				जारी;

			mgmt = (काष्ठा ieee80211_mgmt *) probe->data;
			स_नकल(mgmt->da, req->bssid, ETH_ALEN);
			स_नकल(mgmt->bssid, req->bssid, ETH_ALEN);

			अगर (req->ie_len)
				skb_put_data(probe, req->ie, req->ie_len);

			local_bh_disable();
			mac80211_hwsim_tx_frame(hwsim->hw, probe,
						hwsim->पंचांगp_chan);
			local_bh_enable();
		पूर्ण
	पूर्ण
	ieee80211_queue_delayed_work(hwsim->hw, &hwsim->hw_scan,
				     msecs_to_jअगरfies(dwell));
	hwsim->survey_data[hwsim->scan_chan_idx].channel = hwsim->पंचांगp_chan;
	hwsim->survey_data[hwsim->scan_chan_idx].start = jअगरfies;
	hwsim->survey_data[hwsim->scan_chan_idx].end =
		jअगरfies + msecs_to_jअगरfies(dwell);
	hwsim->scan_chan_idx++;
	mutex_unlock(&hwsim->mutex);
पूर्ण

अटल पूर्णांक mac80211_hwsim_hw_scan(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर,
				  काष्ठा ieee80211_scan_request *hw_req)
अणु
	काष्ठा mac80211_hwsim_data *hwsim = hw->priv;
	काष्ठा cfg80211_scan_request *req = &hw_req->req;

	mutex_lock(&hwsim->mutex);
	अगर (WARN_ON(hwsim->पंचांगp_chan || hwsim->hw_scan_request)) अणु
		mutex_unlock(&hwsim->mutex);
		वापस -EBUSY;
	पूर्ण
	hwsim->hw_scan_request = req;
	hwsim->hw_scan_vअगर = vअगर;
	hwsim->scan_chan_idx = 0;
	अगर (req->flags & NL80211_SCAN_FLAG_RANDOM_ADDR)
		get_अक्रमom_mask_addr(hwsim->scan_addr,
				     hw_req->req.mac_addr,
				     hw_req->req.mac_addr_mask);
	अन्यथा
		स_नकल(hwsim->scan_addr, vअगर->addr, ETH_ALEN);
	स_रखो(hwsim->survey_data, 0, माप(hwsim->survey_data));
	mutex_unlock(&hwsim->mutex);

	mac80211_hwsim_config_mac_nl(hw, hwsim->scan_addr, true);
	wiphy_dbg(hw->wiphy, "hwsim hw_scan request\n");

	ieee80211_queue_delayed_work(hwsim->hw, &hwsim->hw_scan, 0);

	वापस 0;
पूर्ण

अटल व्योम mac80211_hwsim_cancel_hw_scan(काष्ठा ieee80211_hw *hw,
					  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mac80211_hwsim_data *hwsim = hw->priv;
	काष्ठा cfg80211_scan_info info = अणु
		.पातed = true,
	पूर्ण;

	wiphy_dbg(hw->wiphy, "hwsim cancel_hw_scan\n");

	cancel_delayed_work_sync(&hwsim->hw_scan);

	mutex_lock(&hwsim->mutex);
	ieee80211_scan_completed(hwsim->hw, &info);
	hwsim->पंचांगp_chan = शून्य;
	hwsim->hw_scan_request = शून्य;
	hwsim->hw_scan_vअगर = शून्य;
	mutex_unlock(&hwsim->mutex);
पूर्ण

अटल व्योम mac80211_hwsim_sw_scan(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर,
				   स्थिर u8 *mac_addr)
अणु
	काष्ठा mac80211_hwsim_data *hwsim = hw->priv;

	mutex_lock(&hwsim->mutex);

	अगर (hwsim->scanning) अणु
		pr_debug("two hwsim sw_scans detected!\n");
		जाओ out;
	पूर्ण

	pr_debug("hwsim sw_scan request, prepping stuff\n");

	स_नकल(hwsim->scan_addr, mac_addr, ETH_ALEN);
	mac80211_hwsim_config_mac_nl(hw, hwsim->scan_addr, true);
	hwsim->scanning = true;
	स_रखो(hwsim->survey_data, 0, माप(hwsim->survey_data));

out:
	mutex_unlock(&hwsim->mutex);
पूर्ण

अटल व्योम mac80211_hwsim_sw_scan_complete(काष्ठा ieee80211_hw *hw,
					    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mac80211_hwsim_data *hwsim = hw->priv;

	mutex_lock(&hwsim->mutex);

	pr_debug("hwsim sw_scan_complete\n");
	hwsim->scanning = false;
	mac80211_hwsim_config_mac_nl(hw, hwsim->scan_addr, false);
	eth_zero_addr(hwsim->scan_addr);

	mutex_unlock(&hwsim->mutex);
पूर्ण

अटल व्योम hw_roc_start(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mac80211_hwsim_data *hwsim =
		container_of(work, काष्ठा mac80211_hwsim_data, roc_start.work);

	mutex_lock(&hwsim->mutex);

	wiphy_dbg(hwsim->hw->wiphy, "hwsim ROC begins\n");
	hwsim->पंचांगp_chan = hwsim->roc_chan;
	ieee80211_पढ़ोy_on_channel(hwsim->hw);

	ieee80211_queue_delayed_work(hwsim->hw, &hwsim->roc_करोne,
				     msecs_to_jअगरfies(hwsim->roc_duration));

	mutex_unlock(&hwsim->mutex);
पूर्ण

अटल व्योम hw_roc_करोne(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mac80211_hwsim_data *hwsim =
		container_of(work, काष्ठा mac80211_hwsim_data, roc_करोne.work);

	mutex_lock(&hwsim->mutex);
	ieee80211_reमुख्य_on_channel_expired(hwsim->hw);
	hwsim->पंचांगp_chan = शून्य;
	mutex_unlock(&hwsim->mutex);

	wiphy_dbg(hwsim->hw->wiphy, "hwsim ROC expired\n");
पूर्ण

अटल पूर्णांक mac80211_hwsim_roc(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा ieee80211_channel *chan,
			      पूर्णांक duration,
			      क्रमागत ieee80211_roc_type type)
अणु
	काष्ठा mac80211_hwsim_data *hwsim = hw->priv;

	mutex_lock(&hwsim->mutex);
	अगर (WARN_ON(hwsim->पंचांगp_chan || hwsim->hw_scan_request)) अणु
		mutex_unlock(&hwsim->mutex);
		वापस -EBUSY;
	पूर्ण

	hwsim->roc_chan = chan;
	hwsim->roc_duration = duration;
	mutex_unlock(&hwsim->mutex);

	wiphy_dbg(hw->wiphy, "hwsim ROC (%d MHz, %d ms)\n",
		  chan->center_freq, duration);
	ieee80211_queue_delayed_work(hw, &hwsim->roc_start, HZ/50);

	वापस 0;
पूर्ण

अटल पूर्णांक mac80211_hwsim_croc(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mac80211_hwsim_data *hwsim = hw->priv;

	cancel_delayed_work_sync(&hwsim->roc_start);
	cancel_delayed_work_sync(&hwsim->roc_करोne);

	mutex_lock(&hwsim->mutex);
	hwsim->पंचांगp_chan = शून्य;
	mutex_unlock(&hwsim->mutex);

	wiphy_dbg(hw->wiphy, "hwsim ROC canceled\n");

	वापस 0;
पूर्ण

अटल पूर्णांक mac80211_hwsim_add_chanctx(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	hwsim_set_chanctx_magic(ctx);
	wiphy_dbg(hw->wiphy,
		  "add channel context control: %d MHz/width: %d/cfreqs:%d/%d MHz\n",
		  ctx->def.chan->center_freq, ctx->def.width,
		  ctx->def.center_freq1, ctx->def.center_freq2);
	वापस 0;
पूर्ण

अटल व्योम mac80211_hwsim_हटाओ_chanctx(काष्ठा ieee80211_hw *hw,
					  काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	wiphy_dbg(hw->wiphy,
		  "remove channel context control: %d MHz/width: %d/cfreqs:%d/%d MHz\n",
		  ctx->def.chan->center_freq, ctx->def.width,
		  ctx->def.center_freq1, ctx->def.center_freq2);
	hwsim_check_chanctx_magic(ctx);
	hwsim_clear_chanctx_magic(ctx);
पूर्ण

अटल व्योम mac80211_hwsim_change_chanctx(काष्ठा ieee80211_hw *hw,
					  काष्ठा ieee80211_chanctx_conf *ctx,
					  u32 changed)
अणु
	hwsim_check_chanctx_magic(ctx);
	wiphy_dbg(hw->wiphy,
		  "change channel context control: %d MHz/width: %d/cfreqs:%d/%d MHz\n",
		  ctx->def.chan->center_freq, ctx->def.width,
		  ctx->def.center_freq1, ctx->def.center_freq2);
पूर्ण

अटल पूर्णांक mac80211_hwsim_assign_vअगर_chanctx(काष्ठा ieee80211_hw *hw,
					     काष्ठा ieee80211_vअगर *vअगर,
					     काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	hwsim_check_magic(vअगर);
	hwsim_check_chanctx_magic(ctx);

	वापस 0;
पूर्ण

अटल व्योम mac80211_hwsim_unassign_vअगर_chanctx(काष्ठा ieee80211_hw *hw,
						काष्ठा ieee80211_vअगर *vअगर,
						काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	hwsim_check_magic(vअगर);
	hwsim_check_chanctx_magic(ctx);
पूर्ण

अटल स्थिर अक्षर mac80211_hwsim_gstrings_stats[][ETH_GSTRING_LEN] = अणु
	"tx_pkts_nic",
	"tx_bytes_nic",
	"rx_pkts_nic",
	"rx_bytes_nic",
	"d_tx_dropped",
	"d_tx_failed",
	"d_ps_mode",
	"d_group",
पूर्ण;

#घोषणा MAC80211_HWSIM_SSTATS_LEN ARRAY_SIZE(mac80211_hwsim_gstrings_stats)

अटल व्योम mac80211_hwsim_get_et_strings(काष्ठा ieee80211_hw *hw,
					  काष्ठा ieee80211_vअगर *vअगर,
					  u32 sset, u8 *data)
अणु
	अगर (sset == ETH_SS_STATS)
		स_नकल(data, *mac80211_hwsim_gstrings_stats,
		       माप(mac80211_hwsim_gstrings_stats));
पूर्ण

अटल पूर्णांक mac80211_hwsim_get_et_sset_count(काष्ठा ieee80211_hw *hw,
					    काष्ठा ieee80211_vअगर *vअगर, पूर्णांक sset)
अणु
	अगर (sset == ETH_SS_STATS)
		वापस MAC80211_HWSIM_SSTATS_LEN;
	वापस 0;
पूर्ण

अटल व्योम mac80211_hwsim_get_et_stats(काष्ठा ieee80211_hw *hw,
					काष्ठा ieee80211_vअगर *vअगर,
					काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा mac80211_hwsim_data *ar = hw->priv;
	पूर्णांक i = 0;

	data[i++] = ar->tx_pkts;
	data[i++] = ar->tx_bytes;
	data[i++] = ar->rx_pkts;
	data[i++] = ar->rx_bytes;
	data[i++] = ar->tx_dropped;
	data[i++] = ar->tx_failed;
	data[i++] = ar->ps;
	data[i++] = ar->group;

	WARN_ON(i != MAC80211_HWSIM_SSTATS_LEN);
पूर्ण

अटल पूर्णांक mac80211_hwsim_tx_last_beacon(काष्ठा ieee80211_hw *hw)
अणु
	वापस 1;
पूर्ण

#घोषणा HWSIM_COMMON_OPS					\
	.tx = mac80211_hwsim_tx,				\
	.start = mac80211_hwsim_start,				\
	.stop = mac80211_hwsim_stop,				\
	.add_पूर्णांकerface = mac80211_hwsim_add_पूर्णांकerface,		\
	.change_पूर्णांकerface = mac80211_hwsim_change_पूर्णांकerface,	\
	.हटाओ_पूर्णांकerface = mac80211_hwsim_हटाओ_पूर्णांकerface,	\
	.config = mac80211_hwsim_config,			\
	.configure_filter = mac80211_hwsim_configure_filter,	\
	.bss_info_changed = mac80211_hwsim_bss_info_changed,	\
	.tx_last_beacon = mac80211_hwsim_tx_last_beacon,	\
	.sta_add = mac80211_hwsim_sta_add,			\
	.sta_हटाओ = mac80211_hwsim_sta_हटाओ,		\
	.sta_notअगरy = mac80211_hwsim_sta_notअगरy,		\
	.set_tim = mac80211_hwsim_set_tim,			\
	.conf_tx = mac80211_hwsim_conf_tx,			\
	.get_survey = mac80211_hwsim_get_survey,		\
	CFG80211_TESTMODE_CMD(mac80211_hwsim_tesपंचांगode_cmd)	\
	.ampdu_action = mac80211_hwsim_ampdu_action,		\
	.flush = mac80211_hwsim_flush,				\
	.get_tsf = mac80211_hwsim_get_tsf,			\
	.set_tsf = mac80211_hwsim_set_tsf,			\
	.get_et_sset_count = mac80211_hwsim_get_et_sset_count,	\
	.get_et_stats = mac80211_hwsim_get_et_stats,		\
	.get_et_strings = mac80211_hwsim_get_et_strings,

अटल स्थिर काष्ठा ieee80211_ops mac80211_hwsim_ops = अणु
	HWSIM_COMMON_OPS
	.sw_scan_start = mac80211_hwsim_sw_scan,
	.sw_scan_complete = mac80211_hwsim_sw_scan_complete,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_ops mac80211_hwsim_mchan_ops = अणु
	HWSIM_COMMON_OPS
	.hw_scan = mac80211_hwsim_hw_scan,
	.cancel_hw_scan = mac80211_hwsim_cancel_hw_scan,
	.sw_scan_start = शून्य,
	.sw_scan_complete = शून्य,
	.reमुख्य_on_channel = mac80211_hwsim_roc,
	.cancel_reमुख्य_on_channel = mac80211_hwsim_croc,
	.add_chanctx = mac80211_hwsim_add_chanctx,
	.हटाओ_chanctx = mac80211_hwsim_हटाओ_chanctx,
	.change_chanctx = mac80211_hwsim_change_chanctx,
	.assign_vअगर_chanctx = mac80211_hwsim_assign_vअगर_chanctx,
	.unassign_vअगर_chanctx = mac80211_hwsim_unassign_vअगर_chanctx,
पूर्ण;

काष्ठा hwsim_new_radio_params अणु
	अचिन्हित पूर्णांक channels;
	स्थिर अक्षर *reg_alpha2;
	स्थिर काष्ठा ieee80211_regकरोमुख्य *regd;
	bool reg_strict;
	bool p2p_device;
	bool use_chanctx;
	bool destroy_on_बंद;
	स्थिर अक्षर *hwname;
	bool no_vअगर;
	स्थिर u8 *perm_addr;
	u32 अगरtypes;
	u32 *ciphers;
	u8 n_ciphers;
पूर्ण;

अटल व्योम hwsim_mcast_config_msg(काष्ठा sk_buff *mcast_skb,
				   काष्ठा genl_info *info)
अणु
	अगर (info)
		genl_notअगरy(&hwsim_genl_family, mcast_skb, info,
			    HWSIM_MCGRP_CONFIG, GFP_KERNEL);
	अन्यथा
		genlmsg_multicast(&hwsim_genl_family, mcast_skb, 0,
				  HWSIM_MCGRP_CONFIG, GFP_KERNEL);
पूर्ण

अटल पूर्णांक append_radio_msg(काष्ठा sk_buff *skb, पूर्णांक id,
			    काष्ठा hwsim_new_radio_params *param)
अणु
	पूर्णांक ret;

	ret = nla_put_u32(skb, HWSIM_ATTR_RADIO_ID, id);
	अगर (ret < 0)
		वापस ret;

	अगर (param->channels) अणु
		ret = nla_put_u32(skb, HWSIM_ATTR_CHANNELS, param->channels);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (param->reg_alpha2) अणु
		ret = nla_put(skb, HWSIM_ATTR_REG_HINT_ALPHA2, 2,
			      param->reg_alpha2);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (param->regd) अणु
		पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(hwsim_world_regकरोm_custom); i++) अणु
			अगर (hwsim_world_regकरोm_custom[i] != param->regd)
				जारी;

			ret = nla_put_u32(skb, HWSIM_ATTR_REG_CUSTOM_REG, i);
			अगर (ret < 0)
				वापस ret;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (param->reg_strict) अणु
		ret = nla_put_flag(skb, HWSIM_ATTR_REG_STRICT_REG);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (param->p2p_device) अणु
		ret = nla_put_flag(skb, HWSIM_ATTR_SUPPORT_P2P_DEVICE);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (param->use_chanctx) अणु
		ret = nla_put_flag(skb, HWSIM_ATTR_USE_CHANCTX);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (param->hwname) अणु
		ret = nla_put(skb, HWSIM_ATTR_RADIO_NAME,
			      म_माप(param->hwname), param->hwname);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hwsim_mcast_new_radio(पूर्णांक id, काष्ठा genl_info *info,
				  काष्ठा hwsim_new_radio_params *param)
अणु
	काष्ठा sk_buff *mcast_skb;
	व्योम *data;

	mcast_skb = genlmsg_new(GENLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!mcast_skb)
		वापस;

	data = genlmsg_put(mcast_skb, 0, 0, &hwsim_genl_family, 0,
			   HWSIM_CMD_NEW_RADIO);
	अगर (!data)
		जाओ out_err;

	अगर (append_radio_msg(mcast_skb, id, param) < 0)
		जाओ out_err;

	genlmsg_end(mcast_skb, data);

	hwsim_mcast_config_msg(mcast_skb, info);
	वापस;

out_err:
	nlmsg_मुक्त(mcast_skb);
पूर्ण

अटल स्थिर काष्ठा ieee80211_sband_अगरtype_data he_capa_2ghz[] = अणु
	अणु
		/* TODO: should we support other types, e.g., P2P?*/
		.types_mask = BIT(NL80211_IFTYPE_STATION) |
			      BIT(NL80211_IFTYPE_AP),
		.he_cap = अणु
			.has_he = true,
			.he_cap_elem = अणु
				.mac_cap_info[0] =
					IEEE80211_HE_MAC_CAP0_HTC_HE,
				.mac_cap_info[1] =
					IEEE80211_HE_MAC_CAP1_TF_MAC_PAD_DUR_16US |
					IEEE80211_HE_MAC_CAP1_MULTI_TID_AGG_RX_QOS_8,
				.mac_cap_info[2] =
					IEEE80211_HE_MAC_CAP2_BSR |
					IEEE80211_HE_MAC_CAP2_MU_CASCADING |
					IEEE80211_HE_MAC_CAP2_ACK_EN,
				.mac_cap_info[3] =
					IEEE80211_HE_MAC_CAP3_OMI_CONTROL |
					IEEE80211_HE_MAC_CAP3_MAX_AMPDU_LEN_EXP_EXT_3,
				.mac_cap_info[4] = IEEE80211_HE_MAC_CAP4_AMSDU_IN_AMPDU,
				.phy_cap_info[1] =
					IEEE80211_HE_PHY_CAP1_PREAMBLE_PUNC_RX_MASK |
					IEEE80211_HE_PHY_CAP1_DEVICE_CLASS_A |
					IEEE80211_HE_PHY_CAP1_LDPC_CODING_IN_PAYLOAD |
					IEEE80211_HE_PHY_CAP1_MIDAMBLE_RX_TX_MAX_NSTS,
				.phy_cap_info[2] =
					IEEE80211_HE_PHY_CAP2_NDP_4x_LTF_AND_3_2US |
					IEEE80211_HE_PHY_CAP2_STBC_TX_UNDER_80MHZ |
					IEEE80211_HE_PHY_CAP2_STBC_RX_UNDER_80MHZ |
					IEEE80211_HE_PHY_CAP2_UL_MU_FULL_MU_MIMO |
					IEEE80211_HE_PHY_CAP2_UL_MU_PARTIAL_MU_MIMO,

				/* Leave all the other PHY capability bytes
				 * unset, as DCM, beam क्रमming, RU and PPE
				 * threshold inक्रमmation are not supported
				 */
			पूर्ण,
			.he_mcs_nss_supp = अणु
				.rx_mcs_80 = cpu_to_le16(0xfffa),
				.tx_mcs_80 = cpu_to_le16(0xfffa),
				.rx_mcs_160 = cpu_to_le16(0xffff),
				.tx_mcs_160 = cpu_to_le16(0xffff),
				.rx_mcs_80p80 = cpu_to_le16(0xffff),
				.tx_mcs_80p80 = cpu_to_le16(0xffff),
			पूर्ण,
		पूर्ण,
	पूर्ण,
#अगर_घोषित CONFIG_MAC80211_MESH
	अणु
		/* TODO: should we support other types, e.g., IBSS?*/
		.types_mask = BIT(NL80211_IFTYPE_MESH_POINT),
		.he_cap = अणु
			.has_he = true,
			.he_cap_elem = अणु
				.mac_cap_info[0] =
					IEEE80211_HE_MAC_CAP0_HTC_HE,
				.mac_cap_info[1] =
					IEEE80211_HE_MAC_CAP1_MULTI_TID_AGG_RX_QOS_8,
				.mac_cap_info[2] =
					IEEE80211_HE_MAC_CAP2_ACK_EN,
				.mac_cap_info[3] =
					IEEE80211_HE_MAC_CAP3_OMI_CONTROL |
					IEEE80211_HE_MAC_CAP3_MAX_AMPDU_LEN_EXP_EXT_3,
				.mac_cap_info[4] = IEEE80211_HE_MAC_CAP4_AMSDU_IN_AMPDU,
				.phy_cap_info[1] =
					IEEE80211_HE_PHY_CAP1_PREAMBLE_PUNC_RX_MASK |
					IEEE80211_HE_PHY_CAP1_DEVICE_CLASS_A |
					IEEE80211_HE_PHY_CAP1_LDPC_CODING_IN_PAYLOAD |
					IEEE80211_HE_PHY_CAP1_MIDAMBLE_RX_TX_MAX_NSTS,
				.phy_cap_info[2] = 0,

				/* Leave all the other PHY capability bytes
				 * unset, as DCM, beam क्रमming, RU and PPE
				 * threshold inक्रमmation are not supported
				 */
			पूर्ण,
			.he_mcs_nss_supp = अणु
				.rx_mcs_80 = cpu_to_le16(0xfffa),
				.tx_mcs_80 = cpu_to_le16(0xfffa),
				.rx_mcs_160 = cpu_to_le16(0xffff),
				.tx_mcs_160 = cpu_to_le16(0xffff),
				.rx_mcs_80p80 = cpu_to_le16(0xffff),
				.tx_mcs_80p80 = cpu_to_le16(0xffff),
			पूर्ण,
		पूर्ण,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा ieee80211_sband_अगरtype_data he_capa_5ghz[] = अणु
	अणु
		/* TODO: should we support other types, e.g., P2P?*/
		.types_mask = BIT(NL80211_IFTYPE_STATION) |
			      BIT(NL80211_IFTYPE_AP),
		.he_cap = अणु
			.has_he = true,
			.he_cap_elem = अणु
				.mac_cap_info[0] =
					IEEE80211_HE_MAC_CAP0_HTC_HE,
				.mac_cap_info[1] =
					IEEE80211_HE_MAC_CAP1_TF_MAC_PAD_DUR_16US |
					IEEE80211_HE_MAC_CAP1_MULTI_TID_AGG_RX_QOS_8,
				.mac_cap_info[2] =
					IEEE80211_HE_MAC_CAP2_BSR |
					IEEE80211_HE_MAC_CAP2_MU_CASCADING |
					IEEE80211_HE_MAC_CAP2_ACK_EN,
				.mac_cap_info[3] =
					IEEE80211_HE_MAC_CAP3_OMI_CONTROL |
					IEEE80211_HE_MAC_CAP3_MAX_AMPDU_LEN_EXP_EXT_3,
				.mac_cap_info[4] = IEEE80211_HE_MAC_CAP4_AMSDU_IN_AMPDU,
				.phy_cap_info[0] =
					IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_40MHZ_80MHZ_IN_5G |
					IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_160MHZ_IN_5G |
					IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_80PLUS80_MHZ_IN_5G,
				.phy_cap_info[1] =
					IEEE80211_HE_PHY_CAP1_PREAMBLE_PUNC_RX_MASK |
					IEEE80211_HE_PHY_CAP1_DEVICE_CLASS_A |
					IEEE80211_HE_PHY_CAP1_LDPC_CODING_IN_PAYLOAD |
					IEEE80211_HE_PHY_CAP1_MIDAMBLE_RX_TX_MAX_NSTS,
				.phy_cap_info[2] =
					IEEE80211_HE_PHY_CAP2_NDP_4x_LTF_AND_3_2US |
					IEEE80211_HE_PHY_CAP2_STBC_TX_UNDER_80MHZ |
					IEEE80211_HE_PHY_CAP2_STBC_RX_UNDER_80MHZ |
					IEEE80211_HE_PHY_CAP2_UL_MU_FULL_MU_MIMO |
					IEEE80211_HE_PHY_CAP2_UL_MU_PARTIAL_MU_MIMO,

				/* Leave all the other PHY capability bytes
				 * unset, as DCM, beam क्रमming, RU and PPE
				 * threshold inक्रमmation are not supported
				 */
			पूर्ण,
			.he_mcs_nss_supp = अणु
				.rx_mcs_80 = cpu_to_le16(0xfffa),
				.tx_mcs_80 = cpu_to_le16(0xfffa),
				.rx_mcs_160 = cpu_to_le16(0xfffa),
				.tx_mcs_160 = cpu_to_le16(0xfffa),
				.rx_mcs_80p80 = cpu_to_le16(0xfffa),
				.tx_mcs_80p80 = cpu_to_le16(0xfffa),
			पूर्ण,
		पूर्ण,
	पूर्ण,
#अगर_घोषित CONFIG_MAC80211_MESH
	अणु
		/* TODO: should we support other types, e.g., IBSS?*/
		.types_mask = BIT(NL80211_IFTYPE_MESH_POINT),
		.he_cap = अणु
			.has_he = true,
			.he_cap_elem = अणु
				.mac_cap_info[0] =
					IEEE80211_HE_MAC_CAP0_HTC_HE,
				.mac_cap_info[1] =
					IEEE80211_HE_MAC_CAP1_MULTI_TID_AGG_RX_QOS_8,
				.mac_cap_info[2] =
					IEEE80211_HE_MAC_CAP2_ACK_EN,
				.mac_cap_info[3] =
					IEEE80211_HE_MAC_CAP3_OMI_CONTROL |
					IEEE80211_HE_MAC_CAP3_MAX_AMPDU_LEN_EXP_EXT_3,
				.mac_cap_info[4] = IEEE80211_HE_MAC_CAP4_AMSDU_IN_AMPDU,
				.phy_cap_info[0] =
					IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_40MHZ_80MHZ_IN_5G |
					IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_160MHZ_IN_5G |
					IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_80PLUS80_MHZ_IN_5G,
				.phy_cap_info[1] =
					IEEE80211_HE_PHY_CAP1_PREAMBLE_PUNC_RX_MASK |
					IEEE80211_HE_PHY_CAP1_DEVICE_CLASS_A |
					IEEE80211_HE_PHY_CAP1_LDPC_CODING_IN_PAYLOAD |
					IEEE80211_HE_PHY_CAP1_MIDAMBLE_RX_TX_MAX_NSTS,
				.phy_cap_info[2] = 0,

				/* Leave all the other PHY capability bytes
				 * unset, as DCM, beam क्रमming, RU and PPE
				 * threshold inक्रमmation are not supported
				 */
			पूर्ण,
			.he_mcs_nss_supp = अणु
				.rx_mcs_80 = cpu_to_le16(0xfffa),
				.tx_mcs_80 = cpu_to_le16(0xfffa),
				.rx_mcs_160 = cpu_to_le16(0xfffa),
				.tx_mcs_160 = cpu_to_le16(0xfffa),
				.rx_mcs_80p80 = cpu_to_le16(0xfffa),
				.tx_mcs_80p80 = cpu_to_le16(0xfffa),
			पूर्ण,
		पूर्ण,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल व्योम mac80211_hwsim_he_capab(काष्ठा ieee80211_supported_band *sband)
अणु
	u16 n_अगरtype_data;

	अगर (sband->band == NL80211_BAND_2GHZ) अणु
		n_अगरtype_data = ARRAY_SIZE(he_capa_2ghz);
		sband->अगरtype_data =
			(काष्ठा ieee80211_sband_अगरtype_data *)he_capa_2ghz;
	पूर्ण अन्यथा अगर (sband->band == NL80211_BAND_5GHZ) अणु
		n_अगरtype_data = ARRAY_SIZE(he_capa_5ghz);
		sband->अगरtype_data =
			(काष्ठा ieee80211_sband_अगरtype_data *)he_capa_5ghz;
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	sband->n_अगरtype_data = n_अगरtype_data;
पूर्ण

#अगर_घोषित CONFIG_MAC80211_MESH
#घोषणा HWSIM_MESH_BIT BIT(NL80211_IFTYPE_MESH_POINT)
#अन्यथा
#घोषणा HWSIM_MESH_BIT 0
#पूर्ण_अगर

#घोषणा HWSIM_DEFAULT_IF_LIMIT \
	(BIT(NL80211_IFTYPE_STATION) | \
	 BIT(NL80211_IFTYPE_P2P_CLIENT) | \
	 BIT(NL80211_IFTYPE_AP) | \
	 BIT(NL80211_IFTYPE_P2P_GO) | \
	 HWSIM_MESH_BIT)

#घोषणा HWSIM_IFTYPE_SUPPORT_MASK \
	(BIT(NL80211_IFTYPE_STATION) | \
	 BIT(NL80211_IFTYPE_AP) | \
	 BIT(NL80211_IFTYPE_P2P_CLIENT) | \
	 BIT(NL80211_IFTYPE_P2P_GO) | \
	 BIT(NL80211_IFTYPE_ADHOC) | \
	 BIT(NL80211_IFTYPE_MESH_POINT) | \
	 BIT(NL80211_IFTYPE_OCB))

अटल पूर्णांक mac80211_hwsim_new_radio(काष्ठा genl_info *info,
				    काष्ठा hwsim_new_radio_params *param)
अणु
	पूर्णांक err;
	u8 addr[ETH_ALEN];
	काष्ठा mac80211_hwsim_data *data;
	काष्ठा ieee80211_hw *hw;
	क्रमागत nl80211_band band;
	स्थिर काष्ठा ieee80211_ops *ops = &mac80211_hwsim_ops;
	काष्ठा net *net;
	पूर्णांक idx, i;
	पूर्णांक n_limits = 0;

	अगर (WARN_ON(param->channels > 1 && !param->use_chanctx))
		वापस -EINVAL;

	spin_lock_bh(&hwsim_radio_lock);
	idx = hwsim_radio_idx++;
	spin_unlock_bh(&hwsim_radio_lock);

	अगर (param->use_chanctx)
		ops = &mac80211_hwsim_mchan_ops;
	hw = ieee80211_alloc_hw_nm(माप(*data), ops, param->hwname);
	अगर (!hw) अणु
		pr_debug("mac80211_hwsim: ieee80211_alloc_hw failed\n");
		err = -ENOMEM;
		जाओ failed;
	पूर्ण

	/* ieee80211_alloc_hw_nm may have used a शेष name */
	param->hwname = wiphy_name(hw->wiphy);

	अगर (info)
		net = genl_info_net(info);
	अन्यथा
		net = &init_net;
	wiphy_net_set(hw->wiphy, net);

	data = hw->priv;
	data->hw = hw;

	data->dev = device_create(hwsim_class, शून्य, 0, hw, "hwsim%d", idx);
	अगर (IS_ERR(data->dev)) अणु
		prपूर्णांकk(KERN_DEBUG
		       "mac80211_hwsim: device_create failed (%ld)\n",
		       PTR_ERR(data->dev));
		err = -ENOMEM;
		जाओ failed_drvdata;
	पूर्ण
	data->dev->driver = &mac80211_hwsim_driver.driver;
	err = device_bind_driver(data->dev);
	अगर (err != 0) अणु
		pr_debug("mac80211_hwsim: device_bind_driver failed (%d)\n",
		       err);
		जाओ failed_bind;
	पूर्ण

	skb_queue_head_init(&data->pending);

	SET_IEEE80211_DEV(hw, data->dev);
	अगर (!param->perm_addr) अणु
		eth_zero_addr(addr);
		addr[0] = 0x02;
		addr[3] = idx >> 8;
		addr[4] = idx;
		स_नकल(data->addresses[0].addr, addr, ETH_ALEN);
		/* Why need here second address ? */
		स_नकल(data->addresses[1].addr, addr, ETH_ALEN);
		data->addresses[1].addr[0] |= 0x40;
		hw->wiphy->n_addresses = 2;
		hw->wiphy->addresses = data->addresses;
		/* possible address clash is checked at hash table insertion */
	पूर्ण अन्यथा अणु
		स_नकल(data->addresses[0].addr, param->perm_addr, ETH_ALEN);
		/* compatibility with स्वतःmatically generated mac addr */
		स_नकल(data->addresses[1].addr, param->perm_addr, ETH_ALEN);
		hw->wiphy->n_addresses = 2;
		hw->wiphy->addresses = data->addresses;
	पूर्ण

	data->channels = param->channels;
	data->use_chanctx = param->use_chanctx;
	data->idx = idx;
	data->destroy_on_बंद = param->destroy_on_बंद;
	अगर (info)
		data->portid = info->snd_portid;

	/* setup पूर्णांकerface limits, only on पूर्णांकerface types we support */
	अगर (param->अगरtypes & BIT(NL80211_IFTYPE_ADHOC)) अणु
		data->अगर_limits[n_limits].max = 1;
		data->अगर_limits[n_limits].types = BIT(NL80211_IFTYPE_ADHOC);
		n_limits++;
	पूर्ण

	अगर (param->अगरtypes & HWSIM_DEFAULT_IF_LIMIT) अणु
		data->अगर_limits[n_limits].max = 2048;
		/*
		 * For this हाल, we may only support a subset of
		 * HWSIM_DEFAULT_IF_LIMIT, thereक्रमe we only want to add the
		 * bits that both param->अगरtype & HWSIM_DEFAULT_IF_LIMIT have.
		 */
		data->अगर_limits[n_limits].types =
					HWSIM_DEFAULT_IF_LIMIT & param->अगरtypes;
		n_limits++;
	पूर्ण

	अगर (param->अगरtypes & BIT(NL80211_IFTYPE_P2P_DEVICE)) अणु
		data->अगर_limits[n_limits].max = 1;
		data->अगर_limits[n_limits].types =
						BIT(NL80211_IFTYPE_P2P_DEVICE);
		n_limits++;
	पूर्ण

	अगर (data->use_chanctx) अणु
		hw->wiphy->max_scan_ssids = 255;
		hw->wiphy->max_scan_ie_len = IEEE80211_MAX_DATA_LEN;
		hw->wiphy->max_reमुख्य_on_channel_duration = 1000;
		data->अगर_combination.radar_detect_widths = 0;
		data->अगर_combination.num_dअगरferent_channels = data->channels;
	पूर्ण अन्यथा अणु
		data->अगर_combination.num_dअगरferent_channels = 1;
		data->अगर_combination.radar_detect_widths =
					BIT(NL80211_CHAN_WIDTH_5) |
					BIT(NL80211_CHAN_WIDTH_10) |
					BIT(NL80211_CHAN_WIDTH_20_NOHT) |
					BIT(NL80211_CHAN_WIDTH_20) |
					BIT(NL80211_CHAN_WIDTH_40) |
					BIT(NL80211_CHAN_WIDTH_80) |
					BIT(NL80211_CHAN_WIDTH_160);
	पूर्ण

	अगर (!n_limits) अणु
		err = -EINVAL;
		जाओ failed_hw;
	पूर्ण

	data->अगर_combination.max_पूर्णांकerfaces = 0;
	क्रम (i = 0; i < n_limits; i++)
		data->अगर_combination.max_पूर्णांकerfaces +=
			data->अगर_limits[i].max;

	data->अगर_combination.n_limits = n_limits;
	data->अगर_combination.limits = data->अगर_limits;

	/*
	 * If we actually were asked to support combinations,
	 * advertise them - अगर there's only a single thing like
	 * only IBSS then करोn't advertise it as combinations.
	 */
	अगर (data->अगर_combination.max_पूर्णांकerfaces > 1) अणु
		hw->wiphy->अगरace_combinations = &data->अगर_combination;
		hw->wiphy->n_अगरace_combinations = 1;
	पूर्ण

	अगर (param->ciphers) अणु
		स_नकल(data->ciphers, param->ciphers,
		       param->n_ciphers * माप(u32));
		hw->wiphy->cipher_suites = data->ciphers;
		hw->wiphy->n_cipher_suites = param->n_ciphers;
	पूर्ण

	INIT_DELAYED_WORK(&data->roc_start, hw_roc_start);
	INIT_DELAYED_WORK(&data->roc_करोne, hw_roc_करोne);
	INIT_DELAYED_WORK(&data->hw_scan, hw_scan_work);

	hw->queues = 5;
	hw->offchannel_tx_hw_queue = 4;

	ieee80211_hw_set(hw, SUPPORT_FAST_XMIT);
	ieee80211_hw_set(hw, CHANCTX_STA_CSA);
	ieee80211_hw_set(hw, SUPPORTS_HT_CCK_RATES);
	ieee80211_hw_set(hw, QUEUE_CONTROL);
	ieee80211_hw_set(hw, WANT_MONITOR_VIF);
	ieee80211_hw_set(hw, AMPDU_AGGREGATION);
	ieee80211_hw_set(hw, MFP_CAPABLE);
	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, SUPPORTS_PS);
	ieee80211_hw_set(hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, HOST_BROADCAST_PS_BUFFERING);
	ieee80211_hw_set(hw, PS_शून्यFUNC_STACK);
	ieee80211_hw_set(hw, TDLS_WIDER_BW);
	अगर (rctbl)
		ieee80211_hw_set(hw, SUPPORTS_RC_TABLE);
	ieee80211_hw_set(hw, SUPPORTS_MULTI_BSSID);

	hw->wiphy->flags &= ~WIPHY_FLAG_PS_ON_BY_DEFAULT;
	hw->wiphy->flags |= WIPHY_FLAG_SUPPORTS_TDLS |
			    WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL |
			    WIPHY_FLAG_AP_UAPSD |
			    WIPHY_FLAG_SUPPORTS_5_10_MHZ |
			    WIPHY_FLAG_HAS_CHANNEL_SWITCH;
	hw->wiphy->features |= NL80211_FEATURE_ACTIVE_MONITOR |
			       NL80211_FEATURE_AP_MODE_CHAN_WIDTH_CHANGE |
			       NL80211_FEATURE_STATIC_SMPS |
			       NL80211_FEATURE_DYNAMIC_SMPS |
			       NL80211_FEATURE_SCAN_RANDOM_MAC_ADDR;
	wiphy_ext_feature_set(hw->wiphy, NL80211_EXT_FEATURE_VHT_IBSS);
	wiphy_ext_feature_set(hw->wiphy, NL80211_EXT_FEATURE_BEACON_PROTECTION);
	wiphy_ext_feature_set(hw->wiphy,
			      NL80211_EXT_FEATURE_MULTICAST_REGISTRATIONS);
	wiphy_ext_feature_set(hw->wiphy,
			      NL80211_EXT_FEATURE_BEACON_RATE_LEGACY);

	hw->wiphy->पूर्णांकerface_modes = param->अगरtypes;

	/* ask mac80211 to reserve space क्रम magic */
	hw->vअगर_data_size = माप(काष्ठा hwsim_vअगर_priv);
	hw->sta_data_size = माप(काष्ठा hwsim_sta_priv);
	hw->chanctx_data_size = माप(काष्ठा hwsim_chanctx_priv);

	स_नकल(data->channels_2ghz, hwsim_channels_2ghz,
		माप(hwsim_channels_2ghz));
	स_नकल(data->channels_5ghz, hwsim_channels_5ghz,
		माप(hwsim_channels_5ghz));
	स_नकल(data->channels_6ghz, hwsim_channels_6ghz,
		माप(hwsim_channels_6ghz));
	स_नकल(data->channels_s1g, hwsim_channels_s1g,
	       माप(hwsim_channels_s1g));
	स_नकल(data->rates, hwsim_rates, माप(hwsim_rates));

	क्रम (band = NL80211_BAND_2GHZ; band < NUM_NL80211_BANDS; band++) अणु
		काष्ठा ieee80211_supported_band *sband = &data->bands[band];

		sband->band = band;

		चयन (band) अणु
		हाल NL80211_BAND_2GHZ:
			sband->channels = data->channels_2ghz;
			sband->n_channels = ARRAY_SIZE(hwsim_channels_2ghz);
			sband->bitrates = data->rates;
			sband->n_bitrates = ARRAY_SIZE(hwsim_rates);
			अवरोध;
		हाल NL80211_BAND_5GHZ:
			sband->channels = data->channels_5ghz;
			sband->n_channels = ARRAY_SIZE(hwsim_channels_5ghz);
			sband->bitrates = data->rates + 4;
			sband->n_bitrates = ARRAY_SIZE(hwsim_rates) - 4;

			sband->vht_cap.vht_supported = true;
			sband->vht_cap.cap =
				IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454 |
				IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ |
				IEEE80211_VHT_CAP_RXLDPC |
				IEEE80211_VHT_CAP_SHORT_GI_80 |
				IEEE80211_VHT_CAP_SHORT_GI_160 |
				IEEE80211_VHT_CAP_TXSTBC |
				IEEE80211_VHT_CAP_RXSTBC_4 |
				IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK;
			sband->vht_cap.vht_mcs.rx_mcs_map =
				cpu_to_le16(IEEE80211_VHT_MCS_SUPPORT_0_9 << 0 |
					    IEEE80211_VHT_MCS_SUPPORT_0_9 << 2 |
					    IEEE80211_VHT_MCS_SUPPORT_0_9 << 4 |
					    IEEE80211_VHT_MCS_SUPPORT_0_9 << 6 |
					    IEEE80211_VHT_MCS_SUPPORT_0_9 << 8 |
					    IEEE80211_VHT_MCS_SUPPORT_0_9 << 10 |
					    IEEE80211_VHT_MCS_SUPPORT_0_9 << 12 |
					    IEEE80211_VHT_MCS_SUPPORT_0_9 << 14);
			sband->vht_cap.vht_mcs.tx_mcs_map =
				sband->vht_cap.vht_mcs.rx_mcs_map;
			अवरोध;
		हाल NL80211_BAND_S1GHZ:
			स_नकल(&sband->s1g_cap, &hwsim_s1g_cap,
			       माप(sband->s1g_cap));
			sband->channels = data->channels_s1g;
			sband->n_channels = ARRAY_SIZE(hwsim_channels_s1g);
			अवरोध;
		शेष:
			जारी;
		पूर्ण

		sband->ht_cap.ht_supported = true;
		sband->ht_cap.cap = IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
				    IEEE80211_HT_CAP_GRN_FLD |
				    IEEE80211_HT_CAP_SGI_20 |
				    IEEE80211_HT_CAP_SGI_40 |
				    IEEE80211_HT_CAP_DSSSCCK40;
		sband->ht_cap.ampdu_factor = 0x3;
		sband->ht_cap.ampdu_density = 0x6;
		स_रखो(&sband->ht_cap.mcs, 0,
		       माप(sband->ht_cap.mcs));
		sband->ht_cap.mcs.rx_mask[0] = 0xff;
		sband->ht_cap.mcs.rx_mask[1] = 0xff;
		sband->ht_cap.mcs.tx_params = IEEE80211_HT_MCS_TX_DEFINED;

		mac80211_hwsim_he_capab(sband);

		hw->wiphy->bands[band] = sband;
	पूर्ण

	/* By शेष all radios beदीर्घ to the first group */
	data->group = 1;
	mutex_init(&data->mutex);

	data->netgroup = hwsim_net_get_netgroup(net);
	data->wmediumd = hwsim_net_get_wmediumd(net);

	/* Enable frame retransmissions क्रम lossy channels */
	hw->max_rates = 4;
	hw->max_rate_tries = 11;

	hw->wiphy->venकरोr_commands = mac80211_hwsim_venकरोr_commands;
	hw->wiphy->n_venकरोr_commands =
		ARRAY_SIZE(mac80211_hwsim_venकरोr_commands);
	hw->wiphy->venकरोr_events = mac80211_hwsim_venकरोr_events;
	hw->wiphy->n_venकरोr_events = ARRAY_SIZE(mac80211_hwsim_venकरोr_events);

	अगर (param->reg_strict)
		hw->wiphy->regulatory_flags |= REGULATORY_STRICT_REG;
	अगर (param->regd) अणु
		data->regd = param->regd;
		hw->wiphy->regulatory_flags |= REGULATORY_CUSTOM_REG;
		wiphy_apply_custom_regulatory(hw->wiphy, param->regd);
		/* give the regulatory workqueue a chance to run */
		schedule_समयout_पूर्णांकerruptible(1);
	पूर्ण

	अगर (param->no_vअगर)
		ieee80211_hw_set(hw, NO_AUTO_VIF);

	wiphy_ext_feature_set(hw->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	hrसमयr_init(&data->beacon_समयr, CLOCK_MONOTONIC,
		     HRTIMER_MODE_ABS_SOFT);
	data->beacon_समयr.function = mac80211_hwsim_beacon;

	err = ieee80211_रेजिस्टर_hw(hw);
	अगर (err < 0) अणु
		pr_debug("mac80211_hwsim: ieee80211_register_hw failed (%d)\n",
		       err);
		जाओ failed_hw;
	पूर्ण

	wiphy_dbg(hw->wiphy, "hwaddr %pM registered\n", hw->wiphy->perm_addr);

	अगर (param->reg_alpha2) अणु
		data->alpha2[0] = param->reg_alpha2[0];
		data->alpha2[1] = param->reg_alpha2[1];
		regulatory_hपूर्णांक(hw->wiphy, param->reg_alpha2);
	पूर्ण

	data->debugfs = debugfs_create_dir("hwsim", hw->wiphy->debugfsdir);
	debugfs_create_file("ps", 0666, data->debugfs, data, &hwsim_fops_ps);
	debugfs_create_file("group", 0666, data->debugfs, data,
			    &hwsim_fops_group);
	अगर (!data->use_chanctx)
		debugfs_create_file("dfs_simulate_radar", 0222,
				    data->debugfs,
				    data, &hwsim_simulate_radar);

	spin_lock_bh(&hwsim_radio_lock);
	err = rhashtable_insert_fast(&hwsim_radios_rht, &data->rht,
				     hwsim_rht_params);
	अगर (err < 0) अणु
		अगर (info) अणु
			GENL_SET_ERR_MSG(info, "perm addr already present");
			NL_SET_BAD_ATTR(info->extack,
					info->attrs[HWSIM_ATTR_PERM_ADDR]);
		पूर्ण
		spin_unlock_bh(&hwsim_radio_lock);
		जाओ failed_final_insert;
	पूर्ण

	list_add_tail(&data->list, &hwsim_radios);
	hwsim_radios_generation++;
	spin_unlock_bh(&hwsim_radio_lock);

	hwsim_mcast_new_radio(idx, info, param);

	वापस idx;

failed_final_insert:
	debugfs_हटाओ_recursive(data->debugfs);
	ieee80211_unरेजिस्टर_hw(data->hw);
failed_hw:
	device_release_driver(data->dev);
failed_bind:
	device_unरेजिस्टर(data->dev);
failed_drvdata:
	ieee80211_मुक्त_hw(hw);
failed:
	वापस err;
पूर्ण

अटल व्योम hwsim_mcast_del_radio(पूर्णांक id, स्थिर अक्षर *hwname,
				  काष्ठा genl_info *info)
अणु
	काष्ठा sk_buff *skb;
	व्योम *data;
	पूर्णांक ret;

	skb = genlmsg_new(GENLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!skb)
		वापस;

	data = genlmsg_put(skb, 0, 0, &hwsim_genl_family, 0,
			   HWSIM_CMD_DEL_RADIO);
	अगर (!data)
		जाओ error;

	ret = nla_put_u32(skb, HWSIM_ATTR_RADIO_ID, id);
	अगर (ret < 0)
		जाओ error;

	ret = nla_put(skb, HWSIM_ATTR_RADIO_NAME, म_माप(hwname),
		      hwname);
	अगर (ret < 0)
		जाओ error;

	genlmsg_end(skb, data);

	hwsim_mcast_config_msg(skb, info);

	वापस;

error:
	nlmsg_मुक्त(skb);
पूर्ण

अटल व्योम mac80211_hwsim_del_radio(काष्ठा mac80211_hwsim_data *data,
				     स्थिर अक्षर *hwname,
				     काष्ठा genl_info *info)
अणु
	hwsim_mcast_del_radio(data->idx, hwname, info);
	debugfs_हटाओ_recursive(data->debugfs);
	ieee80211_unरेजिस्टर_hw(data->hw);
	device_release_driver(data->dev);
	device_unरेजिस्टर(data->dev);
	ieee80211_मुक्त_hw(data->hw);
पूर्ण

अटल पूर्णांक mac80211_hwsim_get_radio(काष्ठा sk_buff *skb,
				    काष्ठा mac80211_hwsim_data *data,
				    u32 portid, u32 seq,
				    काष्ठा netlink_callback *cb, पूर्णांक flags)
अणु
	व्योम *hdr;
	काष्ठा hwsim_new_radio_params param = अणु पूर्ण;
	पूर्णांक res = -EMSGSIZE;

	hdr = genlmsg_put(skb, portid, seq, &hwsim_genl_family, flags,
			  HWSIM_CMD_GET_RADIO);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (cb)
		genl_dump_check_consistent(cb, hdr);

	अगर (data->alpha2[0] && data->alpha2[1])
		param.reg_alpha2 = data->alpha2;

	param.reg_strict = !!(data->hw->wiphy->regulatory_flags &
					REGULATORY_STRICT_REG);
	param.p2p_device = !!(data->hw->wiphy->पूर्णांकerface_modes &
					BIT(NL80211_IFTYPE_P2P_DEVICE));
	param.use_chanctx = data->use_chanctx;
	param.regd = data->regd;
	param.channels = data->channels;
	param.hwname = wiphy_name(data->hw->wiphy);

	res = append_radio_msg(skb, data->idx, &param);
	अगर (res < 0)
		जाओ out_err;

	genlmsg_end(skb, hdr);
	वापस 0;

out_err:
	genlmsg_cancel(skb, hdr);
	वापस res;
पूर्ण

अटल व्योम mac80211_hwsim_मुक्त(व्योम)
अणु
	काष्ठा mac80211_hwsim_data *data;

	spin_lock_bh(&hwsim_radio_lock);
	जबतक ((data = list_first_entry_or_null(&hwsim_radios,
						काष्ठा mac80211_hwsim_data,
						list))) अणु
		list_del(&data->list);
		spin_unlock_bh(&hwsim_radio_lock);
		mac80211_hwsim_del_radio(data, wiphy_name(data->hw->wiphy),
					 शून्य);
		spin_lock_bh(&hwsim_radio_lock);
	पूर्ण
	spin_unlock_bh(&hwsim_radio_lock);
	class_destroy(hwsim_class);
पूर्ण

अटल स्थिर काष्ठा net_device_ops hwsim_netdev_ops = अणु
	.nकरो_start_xmit 	= hwsim_mon_xmit,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल व्योम hwsim_mon_setup(काष्ठा net_device *dev)
अणु
	dev->netdev_ops = &hwsim_netdev_ops;
	dev->needs_मुक्त_netdev = true;
	ether_setup(dev);
	dev->priv_flags |= IFF_NO_QUEUE;
	dev->type = ARPHRD_IEEE80211_RADIOTAP;
	eth_zero_addr(dev->dev_addr);
	dev->dev_addr[0] = 0x12;
पूर्ण

अटल काष्ठा mac80211_hwsim_data *get_hwsim_data_ref_from_addr(स्थिर u8 *addr)
अणु
	वापस rhashtable_lookup_fast(&hwsim_radios_rht,
				      addr,
				      hwsim_rht_params);
पूर्ण

अटल व्योम hwsim_रेजिस्टर_wmediumd(काष्ठा net *net, u32 portid)
अणु
	काष्ठा mac80211_hwsim_data *data;

	hwsim_net_set_wmediumd(net, portid);

	spin_lock_bh(&hwsim_radio_lock);
	list_क्रम_each_entry(data, &hwsim_radios, list) अणु
		अगर (data->netgroup == hwsim_net_get_netgroup(net))
			data->wmediumd = portid;
	पूर्ण
	spin_unlock_bh(&hwsim_radio_lock);
पूर्ण

अटल पूर्णांक hwsim_tx_info_frame_received_nl(काष्ठा sk_buff *skb_2,
					   काष्ठा genl_info *info)
अणु

	काष्ठा ieee80211_hdr *hdr;
	काष्ठा mac80211_hwsim_data *data2;
	काष्ठा ieee80211_tx_info *txi;
	काष्ठा hwsim_tx_rate *tx_attempts;
	u64 ret_skb_cookie;
	काष्ठा sk_buff *skb, *पंचांगp;
	स्थिर u8 *src;
	अचिन्हित पूर्णांक hwsim_flags;
	पूर्णांक i;
	bool found = false;

	अगर (!info->attrs[HWSIM_ATTR_ADDR_TRANSMITTER] ||
	    !info->attrs[HWSIM_ATTR_FLAGS] ||
	    !info->attrs[HWSIM_ATTR_COOKIE] ||
	    !info->attrs[HWSIM_ATTR_SIGNAL] ||
	    !info->attrs[HWSIM_ATTR_TX_INFO])
		जाओ out;

	src = (व्योम *)nla_data(info->attrs[HWSIM_ATTR_ADDR_TRANSMITTER]);
	hwsim_flags = nla_get_u32(info->attrs[HWSIM_ATTR_FLAGS]);
	ret_skb_cookie = nla_get_u64(info->attrs[HWSIM_ATTR_COOKIE]);

	data2 = get_hwsim_data_ref_from_addr(src);
	अगर (!data2)
		जाओ out;

	अगर (!hwsim_virtio_enabled) अणु
		अगर (hwsim_net_get_netgroup(genl_info_net(info)) !=
		    data2->netgroup)
			जाओ out;

		अगर (info->snd_portid != data2->wmediumd)
			जाओ out;
	पूर्ण

	/* look क्रम the skb matching the cookie passed back from user */
	skb_queue_walk_safe(&data2->pending, skb, पंचांगp) अणु
		u64 skb_cookie;

		txi = IEEE80211_SKB_CB(skb);
		skb_cookie = (u64)(uपूर्णांकptr_t)txi->rate_driver_data[0];

		अगर (skb_cookie == ret_skb_cookie) अणु
			skb_unlink(skb, &data2->pending);
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	/* not found */
	अगर (!found)
		जाओ out;

	/* Tx info received because the frame was broadcasted on user space,
	 so we get all the necessary info: tx attempts and skb control buff */

	tx_attempts = (काष्ठा hwsim_tx_rate *)nla_data(
		       info->attrs[HWSIM_ATTR_TX_INFO]);

	/* now send back TX status */
	txi = IEEE80211_SKB_CB(skb);

	ieee80211_tx_info_clear_status(txi);

	क्रम (i = 0; i < IEEE80211_TX_MAX_RATES; i++) अणु
		txi->status.rates[i].idx = tx_attempts[i].idx;
		txi->status.rates[i].count = tx_attempts[i].count;
	पूर्ण

	txi->status.ack_संकेत = nla_get_u32(info->attrs[HWSIM_ATTR_SIGNAL]);

	अगर (!(hwsim_flags & HWSIM_TX_CTL_NO_ACK) &&
	   (hwsim_flags & HWSIM_TX_STAT_ACK)) अणु
		अगर (skb->len >= 16) अणु
			hdr = (काष्ठा ieee80211_hdr *) skb->data;
			mac80211_hwsim_monitor_ack(data2->channel,
						   hdr->addr2);
		पूर्ण
		txi->flags |= IEEE80211_TX_STAT_ACK;
	पूर्ण
	ieee80211_tx_status_irqsafe(data2->hw, skb);
	वापस 0;
out:
	वापस -EINVAL;

पूर्ण

अटल पूर्णांक hwsim_cloned_frame_received_nl(काष्ठा sk_buff *skb_2,
					  काष्ठा genl_info *info)
अणु
	काष्ठा mac80211_hwsim_data *data2;
	काष्ठा ieee80211_rx_status rx_status;
	काष्ठा ieee80211_hdr *hdr;
	स्थिर u8 *dst;
	पूर्णांक frame_data_len;
	व्योम *frame_data;
	काष्ठा sk_buff *skb = शून्य;

	अगर (!info->attrs[HWSIM_ATTR_ADDR_RECEIVER] ||
	    !info->attrs[HWSIM_ATTR_FRAME] ||
	    !info->attrs[HWSIM_ATTR_RX_RATE] ||
	    !info->attrs[HWSIM_ATTR_SIGNAL])
		जाओ out;

	dst = (व्योम *)nla_data(info->attrs[HWSIM_ATTR_ADDR_RECEIVER]);
	frame_data_len = nla_len(info->attrs[HWSIM_ATTR_FRAME]);
	frame_data = (व्योम *)nla_data(info->attrs[HWSIM_ATTR_FRAME]);

	/* Allocate new skb here */
	skb = alloc_skb(frame_data_len, GFP_KERNEL);
	अगर (skb == शून्य)
		जाओ err;

	अगर (frame_data_len > IEEE80211_MAX_DATA_LEN)
		जाओ err;

	/* Copy the data */
	skb_put_data(skb, frame_data, frame_data_len);

	data2 = get_hwsim_data_ref_from_addr(dst);
	अगर (!data2)
		जाओ out;

	अगर (!hwsim_virtio_enabled) अणु
		अगर (hwsim_net_get_netgroup(genl_info_net(info)) !=
		    data2->netgroup)
			जाओ out;

		अगर (info->snd_portid != data2->wmediumd)
			जाओ out;
	पूर्ण

	/* check अगर radio is configured properly */

	अगर (data2->idle || !data2->started)
		जाओ out;

	/* A frame is received from user space */
	स_रखो(&rx_status, 0, माप(rx_status));
	अगर (info->attrs[HWSIM_ATTR_FREQ]) अणु
		/* throw away off-channel packets, but allow both the temporary
		 * ("hw" scan/reमुख्य-on-channel) and regular channel, since the
		 * पूर्णांकernal datapath also allows this
		 */
		mutex_lock(&data2->mutex);
		rx_status.freq = nla_get_u32(info->attrs[HWSIM_ATTR_FREQ]);

		अगर (rx_status.freq != data2->channel->center_freq &&
		    (!data2->पंचांगp_chan ||
		     rx_status.freq != data2->पंचांगp_chan->center_freq)) अणु
			mutex_unlock(&data2->mutex);
			जाओ out;
		पूर्ण
		mutex_unlock(&data2->mutex);
	पूर्ण अन्यथा अणु
		rx_status.freq = data2->channel->center_freq;
	पूर्ण

	rx_status.band = data2->channel->band;
	rx_status.rate_idx = nla_get_u32(info->attrs[HWSIM_ATTR_RX_RATE]);
	rx_status.संकेत = nla_get_u32(info->attrs[HWSIM_ATTR_SIGNAL]);

	hdr = (व्योम *)skb->data;

	अगर (ieee80211_is_beacon(hdr->frame_control) ||
	    ieee80211_is_probe_resp(hdr->frame_control))
		rx_status.bootसमय_ns = kसमय_get_bootसमय_ns();

	स_नकल(IEEE80211_SKB_RXCB(skb), &rx_status, माप(rx_status));
	data2->rx_pkts++;
	data2->rx_bytes += skb->len;
	ieee80211_rx_irqsafe(data2->hw, skb);

	वापस 0;
err:
	pr_debug("mac80211_hwsim: error occurred in %s\n", __func__);
out:
	dev_kमुक्त_skb(skb);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hwsim_रेजिस्टर_received_nl(काष्ठा sk_buff *skb_2,
				      काष्ठा genl_info *info)
अणु
	काष्ठा net *net = genl_info_net(info);
	काष्ठा mac80211_hwsim_data *data;
	पूर्णांक chans = 1;

	spin_lock_bh(&hwsim_radio_lock);
	list_क्रम_each_entry(data, &hwsim_radios, list)
		chans = max(chans, data->channels);
	spin_unlock_bh(&hwsim_radio_lock);

	/* In the future we should revise the userspace API and allow it
	 * to set a flag that it करोes support multi-channel, then we can
	 * let this pass conditionally on the flag.
	 * For current userspace, prohibit it since it won't work right.
	 */
	अगर (chans > 1)
		वापस -EOPNOTSUPP;

	अगर (hwsim_net_get_wmediumd(net))
		वापस -EBUSY;

	hwsim_रेजिस्टर_wmediumd(net, info->snd_portid);

	pr_debug("mac80211_hwsim: received a REGISTER, "
	       "switching to wmediumd mode with pid %d\n", info->snd_portid);

	वापस 0;
पूर्ण

/* ensures ciphers only include ciphers listed in 'hwsim_ciphers' array */
अटल bool hwsim_known_ciphers(स्थिर u32 *ciphers, पूर्णांक n_ciphers)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n_ciphers; i++) अणु
		पूर्णांक j;
		पूर्णांक found = 0;

		क्रम (j = 0; j < ARRAY_SIZE(hwsim_ciphers); j++) अणु
			अगर (ciphers[i] == hwsim_ciphers[j]) अणु
				found = 1;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!found)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक hwsim_new_radio_nl(काष्ठा sk_buff *msg, काष्ठा genl_info *info)
अणु
	काष्ठा hwsim_new_radio_params param = अणु 0 पूर्ण;
	स्थिर अक्षर *hwname = शून्य;
	पूर्णांक ret;

	param.reg_strict = info->attrs[HWSIM_ATTR_REG_STRICT_REG];
	param.p2p_device = info->attrs[HWSIM_ATTR_SUPPORT_P2P_DEVICE];
	param.channels = channels;
	param.destroy_on_बंद =
		info->attrs[HWSIM_ATTR_DESTROY_RADIO_ON_CLOSE];

	अगर (info->attrs[HWSIM_ATTR_CHANNELS])
		param.channels = nla_get_u32(info->attrs[HWSIM_ATTR_CHANNELS]);

	अगर (param.channels < 1) अणु
		GENL_SET_ERR_MSG(info, "must have at least one channel");
		वापस -EINVAL;
	पूर्ण

	अगर (param.channels > CFG80211_MAX_NUM_DIFFERENT_CHANNELS) अणु
		GENL_SET_ERR_MSG(info, "too many channels specified");
		वापस -EINVAL;
	पूर्ण

	अगर (info->attrs[HWSIM_ATTR_NO_VIF])
		param.no_vअगर = true;

	अगर (info->attrs[HWSIM_ATTR_USE_CHANCTX])
		param.use_chanctx = true;
	अन्यथा
		param.use_chanctx = (param.channels > 1);

	अगर (info->attrs[HWSIM_ATTR_REG_HINT_ALPHA2])
		param.reg_alpha2 =
			nla_data(info->attrs[HWSIM_ATTR_REG_HINT_ALPHA2]);

	अगर (info->attrs[HWSIM_ATTR_REG_CUSTOM_REG]) अणु
		u32 idx = nla_get_u32(info->attrs[HWSIM_ATTR_REG_CUSTOM_REG]);

		अगर (idx >= ARRAY_SIZE(hwsim_world_regकरोm_custom))
			वापस -EINVAL;

		idx = array_index_nospec(idx,
					 ARRAY_SIZE(hwsim_world_regकरोm_custom));
		param.regd = hwsim_world_regकरोm_custom[idx];
	पूर्ण

	अगर (info->attrs[HWSIM_ATTR_PERM_ADDR]) अणु
		अगर (!is_valid_ether_addr(
				nla_data(info->attrs[HWSIM_ATTR_PERM_ADDR]))) अणु
			GENL_SET_ERR_MSG(info,"MAC is no valid source addr");
			NL_SET_BAD_ATTR(info->extack,
					info->attrs[HWSIM_ATTR_PERM_ADDR]);
			वापस -EINVAL;
		पूर्ण

		param.perm_addr = nla_data(info->attrs[HWSIM_ATTR_PERM_ADDR]);
	पूर्ण

	अगर (info->attrs[HWSIM_ATTR_IFTYPE_SUPPORT]) अणु
		param.अगरtypes =
			nla_get_u32(info->attrs[HWSIM_ATTR_IFTYPE_SUPPORT]);

		अगर (param.अगरtypes & ~HWSIM_IFTYPE_SUPPORT_MASK) अणु
			NL_SET_ERR_MSG_ATTR(info->extack,
					    info->attrs[HWSIM_ATTR_IFTYPE_SUPPORT],
					    "cannot support more iftypes than kernel");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		param.अगरtypes = HWSIM_IFTYPE_SUPPORT_MASK;
	पूर्ण

	/* ensure both flag and अगरtype support is honored */
	अगर (param.p2p_device ||
	    param.अगरtypes & BIT(NL80211_IFTYPE_P2P_DEVICE)) अणु
		param.अगरtypes |= BIT(NL80211_IFTYPE_P2P_DEVICE);
		param.p2p_device = true;
	पूर्ण

	अगर (info->attrs[HWSIM_ATTR_CIPHER_SUPPORT]) अणु
		u32 len = nla_len(info->attrs[HWSIM_ATTR_CIPHER_SUPPORT]);

		param.ciphers =
			nla_data(info->attrs[HWSIM_ATTR_CIPHER_SUPPORT]);

		अगर (len % माप(u32)) अणु
			NL_SET_ERR_MSG_ATTR(info->extack,
					    info->attrs[HWSIM_ATTR_CIPHER_SUPPORT],
					    "bad cipher list length");
			वापस -EINVAL;
		पूर्ण

		param.n_ciphers = len / माप(u32);

		अगर (param.n_ciphers > ARRAY_SIZE(hwsim_ciphers)) अणु
			NL_SET_ERR_MSG_ATTR(info->extack,
					    info->attrs[HWSIM_ATTR_CIPHER_SUPPORT],
					    "too many ciphers specified");
			वापस -EINVAL;
		पूर्ण

		अगर (!hwsim_known_ciphers(param.ciphers, param.n_ciphers)) अणु
			NL_SET_ERR_MSG_ATTR(info->extack,
					    info->attrs[HWSIM_ATTR_CIPHER_SUPPORT],
					    "unsupported ciphers specified");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (info->attrs[HWSIM_ATTR_RADIO_NAME]) अणु
		hwname = kstrndup((अक्षर *)nla_data(info->attrs[HWSIM_ATTR_RADIO_NAME]),
				  nla_len(info->attrs[HWSIM_ATTR_RADIO_NAME]),
				  GFP_KERNEL);
		अगर (!hwname)
			वापस -ENOMEM;
		param.hwname = hwname;
	पूर्ण

	ret = mac80211_hwsim_new_radio(info, &param);
	kमुक्त(hwname);
	वापस ret;
पूर्ण

अटल पूर्णांक hwsim_del_radio_nl(काष्ठा sk_buff *msg, काष्ठा genl_info *info)
अणु
	काष्ठा mac80211_hwsim_data *data;
	s64 idx = -1;
	स्थिर अक्षर *hwname = शून्य;

	अगर (info->attrs[HWSIM_ATTR_RADIO_ID]) अणु
		idx = nla_get_u32(info->attrs[HWSIM_ATTR_RADIO_ID]);
	पूर्ण अन्यथा अगर (info->attrs[HWSIM_ATTR_RADIO_NAME]) अणु
		hwname = kstrndup((अक्षर *)nla_data(info->attrs[HWSIM_ATTR_RADIO_NAME]),
				  nla_len(info->attrs[HWSIM_ATTR_RADIO_NAME]),
				  GFP_KERNEL);
		अगर (!hwname)
			वापस -ENOMEM;
	पूर्ण अन्यथा
		वापस -EINVAL;

	spin_lock_bh(&hwsim_radio_lock);
	list_क्रम_each_entry(data, &hwsim_radios, list) अणु
		अगर (idx >= 0) अणु
			अगर (data->idx != idx)
				जारी;
		पूर्ण अन्यथा अणु
			अगर (!hwname ||
			    म_भेद(hwname, wiphy_name(data->hw->wiphy)))
				जारी;
		पूर्ण

		अगर (!net_eq(wiphy_net(data->hw->wiphy), genl_info_net(info)))
			जारी;

		list_del(&data->list);
		rhashtable_हटाओ_fast(&hwsim_radios_rht, &data->rht,
				       hwsim_rht_params);
		hwsim_radios_generation++;
		spin_unlock_bh(&hwsim_radio_lock);
		mac80211_hwsim_del_radio(data, wiphy_name(data->hw->wiphy),
					 info);
		kमुक्त(hwname);
		वापस 0;
	पूर्ण
	spin_unlock_bh(&hwsim_radio_lock);

	kमुक्त(hwname);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक hwsim_get_radio_nl(काष्ठा sk_buff *msg, काष्ठा genl_info *info)
अणु
	काष्ठा mac80211_hwsim_data *data;
	काष्ठा sk_buff *skb;
	पूर्णांक idx, res = -ENODEV;

	अगर (!info->attrs[HWSIM_ATTR_RADIO_ID])
		वापस -EINVAL;
	idx = nla_get_u32(info->attrs[HWSIM_ATTR_RADIO_ID]);

	spin_lock_bh(&hwsim_radio_lock);
	list_क्रम_each_entry(data, &hwsim_radios, list) अणु
		अगर (data->idx != idx)
			जारी;

		अगर (!net_eq(wiphy_net(data->hw->wiphy), genl_info_net(info)))
			जारी;

		skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
		अगर (!skb) अणु
			res = -ENOMEM;
			जाओ out_err;
		पूर्ण

		res = mac80211_hwsim_get_radio(skb, data, info->snd_portid,
					       info->snd_seq, शून्य, 0);
		अगर (res < 0) अणु
			nlmsg_मुक्त(skb);
			जाओ out_err;
		पूर्ण

		res = genlmsg_reply(skb, info);
		अवरोध;
	पूर्ण

out_err:
	spin_unlock_bh(&hwsim_radio_lock);

	वापस res;
पूर्ण

अटल पूर्णांक hwsim_dump_radio_nl(काष्ठा sk_buff *skb,
			       काष्ठा netlink_callback *cb)
अणु
	पूर्णांक last_idx = cb->args[0] - 1;
	काष्ठा mac80211_hwsim_data *data = शून्य;
	पूर्णांक res = 0;
	व्योम *hdr;

	spin_lock_bh(&hwsim_radio_lock);
	cb->seq = hwsim_radios_generation;

	अगर (last_idx >= hwsim_radio_idx-1)
		जाओ करोne;

	list_क्रम_each_entry(data, &hwsim_radios, list) अणु
		अगर (data->idx <= last_idx)
			जारी;

		अगर (!net_eq(wiphy_net(data->hw->wiphy), sock_net(skb->sk)))
			जारी;

		res = mac80211_hwsim_get_radio(skb, data,
					       NETLINK_CB(cb->skb).portid,
					       cb->nlh->nlmsg_seq, cb,
					       NLM_F_MULTI);
		अगर (res < 0)
			अवरोध;

		last_idx = data->idx;
	पूर्ण

	cb->args[0] = last_idx + 1;

	/* list changed, but no new element sent, set पूर्णांकerrupted flag */
	अगर (skb->len == 0 && cb->prev_seq && cb->seq != cb->prev_seq) अणु
		hdr = genlmsg_put(skb, NETLINK_CB(cb->skb).portid,
				  cb->nlh->nlmsg_seq, &hwsim_genl_family,
				  NLM_F_MULTI, HWSIM_CMD_GET_RADIO);
		अगर (hdr) अणु
			genl_dump_check_consistent(cb, hdr);
			genlmsg_end(skb, hdr);
		पूर्ण अन्यथा अणु
			res = -EMSGSIZE;
		पूर्ण
	पूर्ण

करोne:
	spin_unlock_bh(&hwsim_radio_lock);
	वापस res ?: skb->len;
पूर्ण

/* Generic Netlink operations array */
अटल स्थिर काष्ठा genl_small_ops hwsim_ops[] = अणु
	अणु
		.cmd = HWSIM_CMD_REGISTER,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = hwsim_रेजिस्टर_received_nl,
		.flags = GENL_UNS_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = HWSIM_CMD_FRAME,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = hwsim_cloned_frame_received_nl,
	पूर्ण,
	अणु
		.cmd = HWSIM_CMD_TX_INFO_FRAME,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = hwsim_tx_info_frame_received_nl,
	पूर्ण,
	अणु
		.cmd = HWSIM_CMD_NEW_RADIO,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = hwsim_new_radio_nl,
		.flags = GENL_UNS_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = HWSIM_CMD_DEL_RADIO,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = hwsim_del_radio_nl,
		.flags = GENL_UNS_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = HWSIM_CMD_GET_RADIO,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = hwsim_get_radio_nl,
		.dumpit = hwsim_dump_radio_nl,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family hwsim_genl_family __ro_after_init = अणु
	.name = "MAC80211_HWSIM",
	.version = 1,
	.maxattr = HWSIM_ATTR_MAX,
	.policy = hwsim_genl_policy,
	.netnsok = true,
	.module = THIS_MODULE,
	.small_ops = hwsim_ops,
	.n_small_ops = ARRAY_SIZE(hwsim_ops),
	.mcgrps = hwsim_mcgrps,
	.n_mcgrps = ARRAY_SIZE(hwsim_mcgrps),
पूर्ण;

अटल व्योम हटाओ_user_radios(u32 portid)
अणु
	काष्ठा mac80211_hwsim_data *entry, *पंचांगp;
	LIST_HEAD(list);

	spin_lock_bh(&hwsim_radio_lock);
	list_क्रम_each_entry_safe(entry, पंचांगp, &hwsim_radios, list) अणु
		अगर (entry->destroy_on_बंद && entry->portid == portid) अणु
			list_move(&entry->list, &list);
			rhashtable_हटाओ_fast(&hwsim_radios_rht, &entry->rht,
					       hwsim_rht_params);
			hwsim_radios_generation++;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&hwsim_radio_lock);

	list_क्रम_each_entry_safe(entry, पंचांगp, &list, list) अणु
		list_del(&entry->list);
		mac80211_hwsim_del_radio(entry, wiphy_name(entry->hw->wiphy),
					 शून्य);
	पूर्ण
पूर्ण

अटल पूर्णांक mac80211_hwsim_netlink_notअगरy(काष्ठा notअगरier_block *nb,
					 अचिन्हित दीर्घ state,
					 व्योम *_notअगरy)
अणु
	काष्ठा netlink_notअगरy *notअगरy = _notअगरy;

	अगर (state != NETLINK_URELEASE)
		वापस NOTIFY_DONE;

	हटाओ_user_radios(notअगरy->portid);

	अगर (notअगरy->portid == hwsim_net_get_wmediumd(notअगरy->net)) अणु
		prपूर्णांकk(KERN_INFO "mac80211_hwsim: wmediumd released netlink"
		       " socket, switching to perfect channel medium\n");
		hwsim_रेजिस्टर_wmediumd(notअगरy->net, 0);
	पूर्ण
	वापस NOTIFY_DONE;

पूर्ण

अटल काष्ठा notअगरier_block hwsim_netlink_notअगरier = अणु
	.notअगरier_call = mac80211_hwsim_netlink_notअगरy,
पूर्ण;

अटल पूर्णांक __init hwsim_init_netlink(व्योम)
अणु
	पूर्णांक rc;

	prपूर्णांकk(KERN_INFO "mac80211_hwsim: initializing netlink\n");

	rc = genl_रेजिस्टर_family(&hwsim_genl_family);
	अगर (rc)
		जाओ failure;

	rc = netlink_रेजिस्टर_notअगरier(&hwsim_netlink_notअगरier);
	अगर (rc) अणु
		genl_unरेजिस्टर_family(&hwsim_genl_family);
		जाओ failure;
	पूर्ण

	वापस 0;

failure:
	pr_debug("mac80211_hwsim: error occurred in %s\n", __func__);
	वापस -EINVAL;
पूर्ण

अटल __net_init पूर्णांक hwsim_init_net(काष्ठा net *net)
अणु
	वापस hwsim_net_set_netgroup(net);
पूर्ण

अटल व्योम __net_निकास hwsim_निकास_net(काष्ठा net *net)
अणु
	काष्ठा mac80211_hwsim_data *data, *पंचांगp;
	LIST_HEAD(list);

	spin_lock_bh(&hwsim_radio_lock);
	list_क्रम_each_entry_safe(data, पंचांगp, &hwsim_radios, list) अणु
		अगर (!net_eq(wiphy_net(data->hw->wiphy), net))
			जारी;

		/* Radios created in init_net are वापसed to init_net. */
		अगर (data->netgroup == hwsim_net_get_netgroup(&init_net))
			जारी;

		list_move(&data->list, &list);
		rhashtable_हटाओ_fast(&hwsim_radios_rht, &data->rht,
				       hwsim_rht_params);
		hwsim_radios_generation++;
	पूर्ण
	spin_unlock_bh(&hwsim_radio_lock);

	list_क्रम_each_entry_safe(data, पंचांगp, &list, list) अणु
		list_del(&data->list);
		mac80211_hwsim_del_radio(data,
					 wiphy_name(data->hw->wiphy),
					 शून्य);
	पूर्ण

	ida_simple_हटाओ(&hwsim_netgroup_ida, hwsim_net_get_netgroup(net));
पूर्ण

अटल काष्ठा pernet_operations hwsim_net_ops = अणु
	.init = hwsim_init_net,
	.निकास = hwsim_निकास_net,
	.id   = &hwsim_net_id,
	.size = माप(काष्ठा hwsim_net),
पूर्ण;

अटल व्योम hwsim_निकास_netlink(व्योम)
अणु
	/* unरेजिस्टर the notअगरier */
	netlink_unरेजिस्टर_notअगरier(&hwsim_netlink_notअगरier);
	/* unरेजिस्टर the family */
	genl_unरेजिस्टर_family(&hwsim_genl_family);
पूर्ण

#अगर IS_REACHABLE(CONFIG_VIRTIO)
अटल व्योम hwsim_virtio_tx_करोne(काष्ठा virtqueue *vq)
अणु
	अचिन्हित पूर्णांक len;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hwsim_virtio_lock, flags);
	जबतक ((skb = virtqueue_get_buf(vq, &len)))
		nlmsg_मुक्त(skb);
	spin_unlock_irqrestore(&hwsim_virtio_lock, flags);
पूर्ण

अटल पूर्णांक hwsim_virtio_handle_cmd(काष्ठा sk_buff *skb)
अणु
	काष्ठा nlmsghdr *nlh;
	काष्ठा genlmsghdr *gnlh;
	काष्ठा nlattr *tb[HWSIM_ATTR_MAX + 1];
	काष्ठा genl_info info = अणुपूर्ण;
	पूर्णांक err;

	nlh = nlmsg_hdr(skb);
	gnlh = nlmsg_data(nlh);
	err = genlmsg_parse(nlh, &hwsim_genl_family, tb, HWSIM_ATTR_MAX,
			    hwsim_genl_policy, शून्य);
	अगर (err) अणु
		pr_err_ratelimited("hwsim: genlmsg_parse returned %d\n", err);
		वापस err;
	पूर्ण

	info.attrs = tb;

	चयन (gnlh->cmd) अणु
	हाल HWSIM_CMD_FRAME:
		hwsim_cloned_frame_received_nl(skb, &info);
		अवरोध;
	हाल HWSIM_CMD_TX_INFO_FRAME:
		hwsim_tx_info_frame_received_nl(skb, &info);
		अवरोध;
	शेष:
		pr_err_ratelimited("hwsim: invalid cmd: %d\n", gnlh->cmd);
		वापस -EPROTO;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम hwsim_virtio_rx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virtqueue *vq;
	अचिन्हित पूर्णांक len;
	काष्ठा sk_buff *skb;
	काष्ठा scatterlist sg[1];
	पूर्णांक err;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hwsim_virtio_lock, flags);
	अगर (!hwsim_virtio_enabled)
		जाओ out_unlock;

	skb = virtqueue_get_buf(hwsim_vqs[HWSIM_VQ_RX], &len);
	अगर (!skb)
		जाओ out_unlock;
	spin_unlock_irqrestore(&hwsim_virtio_lock, flags);

	skb->data = skb->head;
	skb_set_tail_poपूर्णांकer(skb, len);
	hwsim_virtio_handle_cmd(skb);

	spin_lock_irqsave(&hwsim_virtio_lock, flags);
	अगर (!hwsim_virtio_enabled) अणु
		nlmsg_मुक्त(skb);
		जाओ out_unlock;
	पूर्ण
	vq = hwsim_vqs[HWSIM_VQ_RX];
	sg_init_one(sg, skb->head, skb_end_offset(skb));
	err = virtqueue_add_inbuf(vq, sg, 1, skb, GFP_ATOMIC);
	अगर (WARN(err, "virtqueue_add_inbuf returned %d\n", err))
		nlmsg_मुक्त(skb);
	अन्यथा
		virtqueue_kick(vq);
	schedule_work(&hwsim_virtio_rx);

out_unlock:
	spin_unlock_irqrestore(&hwsim_virtio_lock, flags);
पूर्ण

अटल व्योम hwsim_virtio_rx_करोne(काष्ठा virtqueue *vq)
अणु
	schedule_work(&hwsim_virtio_rx);
पूर्ण

अटल पूर्णांक init_vqs(काष्ठा virtio_device *vdev)
अणु
	vq_callback_t *callbacks[HWSIM_NUM_VQS] = अणु
		[HWSIM_VQ_TX] = hwsim_virtio_tx_करोne,
		[HWSIM_VQ_RX] = hwsim_virtio_rx_करोne,
	पूर्ण;
	स्थिर अक्षर *names[HWSIM_NUM_VQS] = अणु
		[HWSIM_VQ_TX] = "tx",
		[HWSIM_VQ_RX] = "rx",
	पूर्ण;

	वापस virtio_find_vqs(vdev, HWSIM_NUM_VQS,
			       hwsim_vqs, callbacks, names, शून्य);
पूर्ण

अटल पूर्णांक fill_vq(काष्ठा virtqueue *vq)
अणु
	पूर्णांक i, err;
	काष्ठा sk_buff *skb;
	काष्ठा scatterlist sg[1];

	क्रम (i = 0; i < virtqueue_get_vring_size(vq); i++) अणु
		skb = genlmsg_new(GENLMSG_DEFAULT_SIZE, GFP_KERNEL);
		अगर (!skb)
			वापस -ENOMEM;

		sg_init_one(sg, skb->head, skb_end_offset(skb));
		err = virtqueue_add_inbuf(vq, sg, 1, skb, GFP_KERNEL);
		अगर (err) अणु
			nlmsg_मुक्त(skb);
			वापस err;
		पूर्ण
	पूर्ण
	virtqueue_kick(vq);
	वापस 0;
पूर्ण

अटल व्योम हटाओ_vqs(काष्ठा virtio_device *vdev)
अणु
	पूर्णांक i;

	vdev->config->reset(vdev);

	क्रम (i = 0; i < ARRAY_SIZE(hwsim_vqs); i++) अणु
		काष्ठा virtqueue *vq = hwsim_vqs[i];
		काष्ठा sk_buff *skb;

		जबतक ((skb = virtqueue_detach_unused_buf(vq)))
			nlmsg_मुक्त(skb);
	पूर्ण

	vdev->config->del_vqs(vdev);
पूर्ण

अटल पूर्णांक hwsim_virtio_probe(काष्ठा virtio_device *vdev)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hwsim_virtio_lock, flags);
	अगर (hwsim_virtio_enabled) अणु
		spin_unlock_irqrestore(&hwsim_virtio_lock, flags);
		वापस -EEXIST;
	पूर्ण
	spin_unlock_irqrestore(&hwsim_virtio_lock, flags);

	err = init_vqs(vdev);
	अगर (err)
		वापस err;

	err = fill_vq(hwsim_vqs[HWSIM_VQ_RX]);
	अगर (err)
		जाओ out_हटाओ;

	spin_lock_irqsave(&hwsim_virtio_lock, flags);
	hwsim_virtio_enabled = true;
	spin_unlock_irqrestore(&hwsim_virtio_lock, flags);

	schedule_work(&hwsim_virtio_rx);
	वापस 0;

out_हटाओ:
	हटाओ_vqs(vdev);
	वापस err;
पूर्ण

अटल व्योम hwsim_virtio_हटाओ(काष्ठा virtio_device *vdev)
अणु
	hwsim_virtio_enabled = false;

	cancel_work_sync(&hwsim_virtio_rx);

	हटाओ_vqs(vdev);
पूर्ण

/* MAC80211_HWSIM virtio device id table */
अटल स्थिर काष्ठा virtio_device_id id_table[] = अणु
	अणु VIRTIO_ID_MAC80211_HWSIM, VIRTIO_DEV_ANY_ID पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(virtio, id_table);

अटल काष्ठा virtio_driver virtio_hwsim = अणु
	.driver.name = KBUILD_MODNAME,
	.driver.owner = THIS_MODULE,
	.id_table = id_table,
	.probe = hwsim_virtio_probe,
	.हटाओ = hwsim_virtio_हटाओ,
पूर्ण;

अटल पूर्णांक hwsim_रेजिस्टर_virtio_driver(व्योम)
अणु
	वापस रेजिस्टर_virtio_driver(&virtio_hwsim);
पूर्ण

अटल व्योम hwsim_unरेजिस्टर_virtio_driver(व्योम)
अणु
	unरेजिस्टर_virtio_driver(&virtio_hwsim);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक hwsim_रेजिस्टर_virtio_driver(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम hwsim_unरेजिस्टर_virtio_driver(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init init_mac80211_hwsim(व्योम)
अणु
	पूर्णांक i, err;

	अगर (radios < 0 || radios > 100)
		वापस -EINVAL;

	अगर (channels < 1)
		वापस -EINVAL;

	err = rhashtable_init(&hwsim_radios_rht, &hwsim_rht_params);
	अगर (err)
		वापस err;

	err = रेजिस्टर_pernet_device(&hwsim_net_ops);
	अगर (err)
		जाओ out_मुक्त_rht;

	err = platक्रमm_driver_रेजिस्टर(&mac80211_hwsim_driver);
	अगर (err)
		जाओ out_unरेजिस्टर_pernet;

	err = hwsim_init_netlink();
	अगर (err)
		जाओ out_unरेजिस्टर_driver;

	err = hwsim_रेजिस्टर_virtio_driver();
	अगर (err)
		जाओ out_निकास_netlink;

	hwsim_class = class_create(THIS_MODULE, "mac80211_hwsim");
	अगर (IS_ERR(hwsim_class)) अणु
		err = PTR_ERR(hwsim_class);
		जाओ out_निकास_virtio;
	पूर्ण

	hwsim_init_s1g_channels(hwsim_channels_s1g);

	क्रम (i = 0; i < radios; i++) अणु
		काष्ठा hwsim_new_radio_params param = अणु 0 पूर्ण;

		param.channels = channels;

		चयन (regtest) अणु
		हाल HWSIM_REGTEST_DIFF_COUNTRY:
			अगर (i < ARRAY_SIZE(hwsim_alpha2s))
				param.reg_alpha2 = hwsim_alpha2s[i];
			अवरोध;
		हाल HWSIM_REGTEST_DRIVER_REG_FOLLOW:
			अगर (!i)
				param.reg_alpha2 = hwsim_alpha2s[0];
			अवरोध;
		हाल HWSIM_REGTEST_STRICT_ALL:
			param.reg_strict = true;
			fallthrough;
		हाल HWSIM_REGTEST_DRIVER_REG_ALL:
			param.reg_alpha2 = hwsim_alpha2s[0];
			अवरोध;
		हाल HWSIM_REGTEST_WORLD_ROAM:
			अगर (i == 0)
				param.regd = &hwsim_world_regकरोm_custom_01;
			अवरोध;
		हाल HWSIM_REGTEST_CUSTOM_WORLD:
			param.regd = &hwsim_world_regकरोm_custom_01;
			अवरोध;
		हाल HWSIM_REGTEST_CUSTOM_WORLD_2:
			अगर (i == 0)
				param.regd = &hwsim_world_regकरोm_custom_01;
			अन्यथा अगर (i == 1)
				param.regd = &hwsim_world_regकरोm_custom_02;
			अवरोध;
		हाल HWSIM_REGTEST_STRICT_FOLLOW:
			अगर (i == 0) अणु
				param.reg_strict = true;
				param.reg_alpha2 = hwsim_alpha2s[0];
			पूर्ण
			अवरोध;
		हाल HWSIM_REGTEST_STRICT_AND_DRIVER_REG:
			अगर (i == 0) अणु
				param.reg_strict = true;
				param.reg_alpha2 = hwsim_alpha2s[0];
			पूर्ण अन्यथा अगर (i == 1) अणु
				param.reg_alpha2 = hwsim_alpha2s[1];
			पूर्ण
			अवरोध;
		हाल HWSIM_REGTEST_ALL:
			चयन (i) अणु
			हाल 0:
				param.regd = &hwsim_world_regकरोm_custom_01;
				अवरोध;
			हाल 1:
				param.regd = &hwsim_world_regकरोm_custom_02;
				अवरोध;
			हाल 2:
				param.reg_alpha2 = hwsim_alpha2s[0];
				अवरोध;
			हाल 3:
				param.reg_alpha2 = hwsim_alpha2s[1];
				अवरोध;
			हाल 4:
				param.reg_strict = true;
				param.reg_alpha2 = hwsim_alpha2s[2];
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		param.p2p_device = support_p2p_device;
		param.use_chanctx = channels > 1;
		param.अगरtypes = HWSIM_IFTYPE_SUPPORT_MASK;
		अगर (param.p2p_device)
			param.अगरtypes |= BIT(NL80211_IFTYPE_P2P_DEVICE);

		err = mac80211_hwsim_new_radio(शून्य, &param);
		अगर (err < 0)
			जाओ out_मुक्त_radios;
	पूर्ण

	hwsim_mon = alloc_netdev(0, "hwsim%d", NET_NAME_UNKNOWN,
				 hwsim_mon_setup);
	अगर (hwsim_mon == शून्य) अणु
		err = -ENOMEM;
		जाओ out_मुक्त_radios;
	पूर्ण

	rtnl_lock();
	err = dev_alloc_name(hwsim_mon, hwsim_mon->name);
	अगर (err < 0) अणु
		rtnl_unlock();
		जाओ out_मुक्त_mon;
	पूर्ण

	err = रेजिस्टर_netdevice(hwsim_mon);
	अगर (err < 0) अणु
		rtnl_unlock();
		जाओ out_मुक्त_mon;
	पूर्ण
	rtnl_unlock();

	वापस 0;

out_मुक्त_mon:
	मुक्त_netdev(hwsim_mon);
out_मुक्त_radios:
	mac80211_hwsim_मुक्त();
out_निकास_virtio:
	hwsim_unरेजिस्टर_virtio_driver();
out_निकास_netlink:
	hwsim_निकास_netlink();
out_unरेजिस्टर_driver:
	platक्रमm_driver_unरेजिस्टर(&mac80211_hwsim_driver);
out_unरेजिस्टर_pernet:
	unरेजिस्टर_pernet_device(&hwsim_net_ops);
out_मुक्त_rht:
	rhashtable_destroy(&hwsim_radios_rht);
	वापस err;
पूर्ण
module_init(init_mac80211_hwsim);

अटल व्योम __निकास निकास_mac80211_hwsim(व्योम)
अणु
	pr_debug("mac80211_hwsim: unregister radios\n");

	hwsim_unरेजिस्टर_virtio_driver();
	hwsim_निकास_netlink();

	mac80211_hwsim_मुक्त();

	rhashtable_destroy(&hwsim_radios_rht);
	unरेजिस्टर_netdev(hwsim_mon);
	platक्रमm_driver_unरेजिस्टर(&mac80211_hwsim_driver);
	unरेजिस्टर_pernet_device(&hwsim_net_ops);
पूर्ण
module_निकास(निकास_mac80211_hwsim);
