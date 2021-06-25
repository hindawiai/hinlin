<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __NET_CFG80211_H
#घोषणा __NET_CFG80211_H
/*
 * 802.11 device and configuration पूर्णांकerface
 *
 * Copyright 2006-2010	Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2013-2014 Intel Mobile Communications GmbH
 * Copyright 2015-2017	Intel Deutschland GmbH
 * Copyright (C) 2018-2020 Intel Corporation
 */

#समावेश <linux/ethtool.h>
#समावेश <uapi/linux/rfसमाप्त.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/list.h>
#समावेश <linux/bug.h>
#समावेश <linux/netlink.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/nl80211.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/ieee80211.h>
#समावेश <linux/net.h>
#समावेश <net/regulatory.h>

/**
 * DOC: Introduction
 *
 * cfg80211 is the configuration API क्रम 802.11 devices in Linux. It bridges
 * userspace and drivers, and offers some utility functionality associated
 * with 802.11. cfg80211 must, directly or indirectly via mac80211, be used
 * by all modern wireless drivers in Linux, so that they offer a consistent
 * API through nl80211. For backward compatibility, cfg80211 also offers
 * wireless extensions to userspace, but hides them from drivers completely.
 *
 * Additionally, cfg80211 contains code to help enक्रमce regulatory spectrum
 * use restrictions.
 */


/**
 * DOC: Device registration
 *
 * In order क्रम a driver to use cfg80211, it must रेजिस्टर the hardware device
 * with cfg80211. This happens through a number of hardware capability काष्ठाs
 * described below.
 *
 * The fundamental काष्ठाure क्रम each device is the 'wiphy', of which each
 * instance describes a physical wireless device connected to the प्रणाली. Each
 * such wiphy can have zero, one, or many भव पूर्णांकerfaces associated with
 * it, which need to be identअगरied as such by poपूर्णांकing the network पूर्णांकerface's
 * @ieee80211_ptr poपूर्णांकer to a &काष्ठा wireless_dev which further describes
 * the wireless part of the पूर्णांकerface, normally this काष्ठा is embedded in the
 * network पूर्णांकerface's निजी data area. Drivers can optionally allow creating
 * or destroying भव पूर्णांकerfaces on the fly, but without at least one or the
 * ability to create some the wireless device isn't useful.
 *
 * Each wiphy काष्ठाure contains device capability inक्रमmation, and also has
 * a poपूर्णांकer to the various operations the driver offers. The definitions and
 * काष्ठाures here describe these capabilities in detail.
 */

काष्ठा wiphy;

/*
 * wireless hardware capability काष्ठाures
 */

/**
 * क्रमागत ieee80211_channel_flags - channel flags
 *
 * Channel flags set by the regulatory control code.
 *
 * @IEEE80211_CHAN_DISABLED: This channel is disabled.
 * @IEEE80211_CHAN_NO_IR: करो not initiate radiation, this includes
 *	sending probe requests or beaconing.
 * @IEEE80211_CHAN_RADAR: Radar detection is required on this channel.
 * @IEEE80211_CHAN_NO_HT40PLUS: extension channel above this channel
 *	is not permitted.
 * @IEEE80211_CHAN_NO_HT40MINUS: extension channel below this channel
 *	is not permitted.
 * @IEEE80211_CHAN_NO_OFDM: OFDM is not allowed on this channel.
 * @IEEE80211_CHAN_NO_80MHZ: If the driver supports 80 MHz on the band,
 *	this flag indicates that an 80 MHz channel cannot use this
 *	channel as the control or any of the secondary channels.
 *	This may be due to the driver or due to regulatory bandwidth
 *	restrictions.
 * @IEEE80211_CHAN_NO_160MHZ: If the driver supports 160 MHz on the band,
 *	this flag indicates that an 160 MHz channel cannot use this
 *	channel as the control or any of the secondary channels.
 *	This may be due to the driver or due to regulatory bandwidth
 *	restrictions.
 * @IEEE80211_CHAN_INDOOR_ONLY: see %NL80211_FREQUENCY_ATTR_INDOOR_ONLY
 * @IEEE80211_CHAN_IR_CONCURRENT: see %NL80211_FREQUENCY_ATTR_IR_CONCURRENT
 * @IEEE80211_CHAN_NO_20MHZ: 20 MHz bandwidth is not permitted
 *	on this channel.
 * @IEEE80211_CHAN_NO_10MHZ: 10 MHz bandwidth is not permitted
 *	on this channel.
 * @IEEE80211_CHAN_NO_HE: HE operation is not permitted on this channel.
 * @IEEE80211_CHAN_1MHZ: 1 MHz bandwidth is permitted
 *	on this channel.
 * @IEEE80211_CHAN_2MHZ: 2 MHz bandwidth is permitted
 *	on this channel.
 * @IEEE80211_CHAN_4MHZ: 4 MHz bandwidth is permitted
 *	on this channel.
 * @IEEE80211_CHAN_8MHZ: 8 MHz bandwidth is permitted
 *	on this channel.
 * @IEEE80211_CHAN_16MHZ: 16 MHz bandwidth is permitted
 *	on this channel.
 *
 */
क्रमागत ieee80211_channel_flags अणु
	IEEE80211_CHAN_DISABLED		= 1<<0,
	IEEE80211_CHAN_NO_IR		= 1<<1,
	/* hole at 1<<2 */
	IEEE80211_CHAN_RADAR		= 1<<3,
	IEEE80211_CHAN_NO_HT40PLUS	= 1<<4,
	IEEE80211_CHAN_NO_HT40MINUS	= 1<<5,
	IEEE80211_CHAN_NO_OFDM		= 1<<6,
	IEEE80211_CHAN_NO_80MHZ		= 1<<7,
	IEEE80211_CHAN_NO_160MHZ	= 1<<8,
	IEEE80211_CHAN_INDOOR_ONLY	= 1<<9,
	IEEE80211_CHAN_IR_CONCURRENT	= 1<<10,
	IEEE80211_CHAN_NO_20MHZ		= 1<<11,
	IEEE80211_CHAN_NO_10MHZ		= 1<<12,
	IEEE80211_CHAN_NO_HE		= 1<<13,
	IEEE80211_CHAN_1MHZ		= 1<<14,
	IEEE80211_CHAN_2MHZ		= 1<<15,
	IEEE80211_CHAN_4MHZ		= 1<<16,
	IEEE80211_CHAN_8MHZ		= 1<<17,
	IEEE80211_CHAN_16MHZ		= 1<<18,
पूर्ण;

#घोषणा IEEE80211_CHAN_NO_HT40 \
	(IEEE80211_CHAN_NO_HT40PLUS | IEEE80211_CHAN_NO_HT40MINUS)

#घोषणा IEEE80211_DFS_MIN_CAC_TIME_MS		60000
#घोषणा IEEE80211_DFS_MIN_NOP_TIME_MS		(30 * 60 * 1000)

/**
 * काष्ठा ieee80211_channel - channel definition
 *
 * This काष्ठाure describes a single channel क्रम use
 * with cfg80211.
 *
 * @center_freq: center frequency in MHz
 * @freq_offset: offset from @center_freq, in KHz
 * @hw_value: hardware-specअगरic value क्रम the channel
 * @flags: channel flags from &क्रमागत ieee80211_channel_flags.
 * @orig_flags: channel flags at registration समय, used by regulatory
 *	code to support devices with additional restrictions
 * @band: band this channel beदीर्घs to.
 * @max_antenna_gain: maximum antenna gain in dBi
 * @max_घातer: maximum transmission घातer (in dBm)
 * @max_reg_घातer: maximum regulatory transmission घातer (in dBm)
 * @beacon_found: helper to regulatory code to indicate when a beacon
 *	has been found on this channel. Use regulatory_hपूर्णांक_found_beacon()
 *	to enable this, this is useful only on 5 GHz band.
 * @orig_mag: पूर्णांकernal use
 * @orig_mpwr: पूर्णांकernal use
 * @dfs_state: current state of this channel. Only relevant अगर radar is required
 *	on this channel.
 * @dfs_state_entered: बारtamp (jअगरfies) when the dfs state was entered.
 * @dfs_cac_ms: DFS CAC समय in milliseconds, this is valid क्रम DFS channels.
 */
काष्ठा ieee80211_channel अणु
	क्रमागत nl80211_band band;
	u32 center_freq;
	u16 freq_offset;
	u16 hw_value;
	u32 flags;
	पूर्णांक max_antenna_gain;
	पूर्णांक max_घातer;
	पूर्णांक max_reg_घातer;
	bool beacon_found;
	u32 orig_flags;
	पूर्णांक orig_mag, orig_mpwr;
	क्रमागत nl80211_dfs_state dfs_state;
	अचिन्हित दीर्घ dfs_state_entered;
	अचिन्हित पूर्णांक dfs_cac_ms;
पूर्ण;

/**
 * क्रमागत ieee80211_rate_flags - rate flags
 *
 * Hardware/specअगरication flags क्रम rates. These are काष्ठाured
 * in a way that allows using the same bitrate काष्ठाure क्रम
 * dअगरferent bands/PHY modes.
 *
 * @IEEE80211_RATE_SHORT_PREAMBLE: Hardware can send with लघु
 *	preamble on this bitrate; only relevant in 2.4GHz band and
 *	with CCK rates.
 * @IEEE80211_RATE_MANDATORY_A: This bitrate is a mandatory rate
 *	when used with 802.11a (on the 5 GHz band); filled by the
 *	core code when रेजिस्टरing the wiphy.
 * @IEEE80211_RATE_MANDATORY_B: This bitrate is a mandatory rate
 *	when used with 802.11b (on the 2.4 GHz band); filled by the
 *	core code when रेजिस्टरing the wiphy.
 * @IEEE80211_RATE_MANDATORY_G: This bitrate is a mandatory rate
 *	when used with 802.11g (on the 2.4 GHz band); filled by the
 *	core code when रेजिस्टरing the wiphy.
 * @IEEE80211_RATE_ERP_G: This is an ERP rate in 802.11g mode.
 * @IEEE80211_RATE_SUPPORTS_5MHZ: Rate can be used in 5 MHz mode
 * @IEEE80211_RATE_SUPPORTS_10MHZ: Rate can be used in 10 MHz mode
 */
क्रमागत ieee80211_rate_flags अणु
	IEEE80211_RATE_SHORT_PREAMBLE	= 1<<0,
	IEEE80211_RATE_MANDATORY_A	= 1<<1,
	IEEE80211_RATE_MANDATORY_B	= 1<<2,
	IEEE80211_RATE_MANDATORY_G	= 1<<3,
	IEEE80211_RATE_ERP_G		= 1<<4,
	IEEE80211_RATE_SUPPORTS_5MHZ	= 1<<5,
	IEEE80211_RATE_SUPPORTS_10MHZ	= 1<<6,
पूर्ण;

/**
 * क्रमागत ieee80211_bss_type - BSS type filter
 *
 * @IEEE80211_BSS_TYPE_ESS: Infraकाष्ठाure BSS
 * @IEEE80211_BSS_TYPE_PBSS: Personal BSS
 * @IEEE80211_BSS_TYPE_IBSS: Independent BSS
 * @IEEE80211_BSS_TYPE_MBSS: Mesh BSS
 * @IEEE80211_BSS_TYPE_ANY: Wildcard value क्रम matching any BSS type
 */
क्रमागत ieee80211_bss_type अणु
	IEEE80211_BSS_TYPE_ESS,
	IEEE80211_BSS_TYPE_PBSS,
	IEEE80211_BSS_TYPE_IBSS,
	IEEE80211_BSS_TYPE_MBSS,
	IEEE80211_BSS_TYPE_ANY
पूर्ण;

/**
 * क्रमागत ieee80211_privacy - BSS privacy filter
 *
 * @IEEE80211_PRIVACY_ON: privacy bit set
 * @IEEE80211_PRIVACY_OFF: privacy bit clear
 * @IEEE80211_PRIVACY_ANY: Wildcard value क्रम matching any privacy setting
 */
क्रमागत ieee80211_privacy अणु
	IEEE80211_PRIVACY_ON,
	IEEE80211_PRIVACY_OFF,
	IEEE80211_PRIVACY_ANY
पूर्ण;

#घोषणा IEEE80211_PRIVACY(x)	\
	((x) ? IEEE80211_PRIVACY_ON : IEEE80211_PRIVACY_OFF)

/**
 * काष्ठा ieee80211_rate - bitrate definition
 *
 * This काष्ठाure describes a bitrate that an 802.11 PHY can
 * operate with. The two values @hw_value and @hw_value_लघु
 * are only क्रम driver use when poपूर्णांकers to this काष्ठाure are
 * passed around.
 *
 * @flags: rate-specअगरic flags
 * @bitrate: bitrate in units of 100 Kbps
 * @hw_value: driver/hardware value क्रम this rate
 * @hw_value_लघु: driver/hardware value क्रम this rate when
 *	लघु preamble is used
 */
काष्ठा ieee80211_rate अणु
	u32 flags;
	u16 bitrate;
	u16 hw_value, hw_value_लघु;
पूर्ण;

/**
 * काष्ठा ieee80211_he_obss_pd - AP settings क्रम spatial reuse
 *
 * @enable: is the feature enabled.
 * @sr_ctrl: The SR Control field of SRP element.
 * @non_srg_max_offset: non-SRG maximum tx घातer offset
 * @min_offset: minimal tx घातer offset an associated station shall use
 * @max_offset: maximum tx घातer offset an associated station shall use
 * @bss_color_biपंचांगap: biपंचांगap that indicates the BSS color values used by
 *	members of the SRG
 * @partial_bssid_biपंचांगap: biपंचांगap that indicates the partial BSSID values
 *	used by members of the SRG
 */
काष्ठा ieee80211_he_obss_pd अणु
	bool enable;
	u8 sr_ctrl;
	u8 non_srg_max_offset;
	u8 min_offset;
	u8 max_offset;
	u8 bss_color_biपंचांगap[8];
	u8 partial_bssid_biपंचांगap[8];
पूर्ण;

/**
 * काष्ठा cfg80211_he_bss_color - AP settings क्रम BSS coloring
 *
 * @color: the current color.
 * @enabled: HE BSS color is used
 * @partial: define the AID equation.
 */
काष्ठा cfg80211_he_bss_color अणु
	u8 color;
	bool enabled;
	bool partial;
पूर्ण;

/**
 * काष्ठा ieee80211_sta_ht_cap - STA's HT capabilities
 *
 * This काष्ठाure describes most essential parameters needed
 * to describe 802.11n HT capabilities क्रम an STA.
 *
 * @ht_supported: is HT supported by the STA
 * @cap: HT capabilities map as described in 802.11n spec
 * @ampdu_factor: Maximum A-MPDU length factor
 * @ampdu_density: Minimum A-MPDU spacing
 * @mcs: Supported MCS rates
 */
काष्ठा ieee80211_sta_ht_cap अणु
	u16 cap; /* use IEEE80211_HT_CAP_ */
	bool ht_supported;
	u8 ampdu_factor;
	u8 ampdu_density;
	काष्ठा ieee80211_mcs_info mcs;
पूर्ण;

/**
 * काष्ठा ieee80211_sta_vht_cap - STA's VHT capabilities
 *
 * This काष्ठाure describes most essential parameters needed
 * to describe 802.11ac VHT capabilities क्रम an STA.
 *
 * @vht_supported: is VHT supported by the STA
 * @cap: VHT capabilities map as described in 802.11ac spec
 * @vht_mcs: Supported VHT MCS rates
 */
काष्ठा ieee80211_sta_vht_cap अणु
	bool vht_supported;
	u32 cap; /* use IEEE80211_VHT_CAP_ */
	काष्ठा ieee80211_vht_mcs_info vht_mcs;
पूर्ण;

#घोषणा IEEE80211_HE_PPE_THRES_MAX_LEN		25

/**
 * काष्ठा ieee80211_sta_he_cap - STA's HE capabilities
 *
 * This काष्ठाure describes most essential parameters needed
 * to describe 802.11ax HE capabilities क्रम a STA.
 *
 * @has_he: true अगरf HE data is valid.
 * @he_cap_elem: Fixed portion of the HE capabilities element.
 * @he_mcs_nss_supp: The supported NSS/MCS combinations.
 * @ppe_thres: Holds the PPE Thresholds data.
 */
काष्ठा ieee80211_sta_he_cap अणु
	bool has_he;
	काष्ठा ieee80211_he_cap_elem he_cap_elem;
	काष्ठा ieee80211_he_mcs_nss_supp he_mcs_nss_supp;
	u8 ppe_thres[IEEE80211_HE_PPE_THRES_MAX_LEN];
पूर्ण;

/**
 * काष्ठा ieee80211_sband_अगरtype_data - sband data per पूर्णांकerface type
 *
 * This काष्ठाure encapsulates sband data that is relevant क्रम the
 * पूर्णांकerface types defined in @types_mask.  Each type in the
 * @types_mask must be unique across all instances of अगरtype_data.
 *
 * @types_mask: पूर्णांकerface types mask
 * @he_cap: holds the HE capabilities
 * @he_6ghz_capa: HE 6 GHz capabilities, must be filled in क्रम a
 *	6 GHz band channel (and 0 may be valid value).
 */
काष्ठा ieee80211_sband_अगरtype_data अणु
	u16 types_mask;
	काष्ठा ieee80211_sta_he_cap he_cap;
	काष्ठा ieee80211_he_6ghz_capa he_6ghz_capa;
पूर्ण;

/**
 * क्रमागत ieee80211_edmg_bw_config - allowed channel bandwidth configurations
 *
 * @IEEE80211_EDMG_BW_CONFIG_4: 2.16GHz
 * @IEEE80211_EDMG_BW_CONFIG_5: 2.16GHz and 4.32GHz
 * @IEEE80211_EDMG_BW_CONFIG_6: 2.16GHz, 4.32GHz and 6.48GHz
 * @IEEE80211_EDMG_BW_CONFIG_7: 2.16GHz, 4.32GHz, 6.48GHz and 8.64GHz
 * @IEEE80211_EDMG_BW_CONFIG_8: 2.16GHz and 2.16GHz + 2.16GHz
 * @IEEE80211_EDMG_BW_CONFIG_9: 2.16GHz, 4.32GHz and 2.16GHz + 2.16GHz
 * @IEEE80211_EDMG_BW_CONFIG_10: 2.16GHz, 4.32GHz, 6.48GHz and 2.16GHz+2.16GHz
 * @IEEE80211_EDMG_BW_CONFIG_11: 2.16GHz, 4.32GHz, 6.48GHz, 8.64GHz and
 *	2.16GHz+2.16GHz
 * @IEEE80211_EDMG_BW_CONFIG_12: 2.16GHz, 2.16GHz + 2.16GHz and
 *	4.32GHz + 4.32GHz
 * @IEEE80211_EDMG_BW_CONFIG_13: 2.16GHz, 4.32GHz, 2.16GHz + 2.16GHz and
 *	4.32GHz + 4.32GHz
 * @IEEE80211_EDMG_BW_CONFIG_14: 2.16GHz, 4.32GHz, 6.48GHz, 2.16GHz + 2.16GHz
 *	and 4.32GHz + 4.32GHz
 * @IEEE80211_EDMG_BW_CONFIG_15: 2.16GHz, 4.32GHz, 6.48GHz, 8.64GHz,
 *	2.16GHz + 2.16GHz and 4.32GHz + 4.32GHz
 */
क्रमागत ieee80211_edmg_bw_config अणु
	IEEE80211_EDMG_BW_CONFIG_4	= 4,
	IEEE80211_EDMG_BW_CONFIG_5	= 5,
	IEEE80211_EDMG_BW_CONFIG_6	= 6,
	IEEE80211_EDMG_BW_CONFIG_7	= 7,
	IEEE80211_EDMG_BW_CONFIG_8	= 8,
	IEEE80211_EDMG_BW_CONFIG_9	= 9,
	IEEE80211_EDMG_BW_CONFIG_10	= 10,
	IEEE80211_EDMG_BW_CONFIG_11	= 11,
	IEEE80211_EDMG_BW_CONFIG_12	= 12,
	IEEE80211_EDMG_BW_CONFIG_13	= 13,
	IEEE80211_EDMG_BW_CONFIG_14	= 14,
	IEEE80211_EDMG_BW_CONFIG_15	= 15,
पूर्ण;

/**
 * काष्ठा ieee80211_edmg - EDMG configuration
 *
 * This काष्ठाure describes most essential parameters needed
 * to describe 802.11ay EDMG configuration
 *
 * @channels: biपंचांगap that indicates the 2.16 GHz channel(s)
 *	that are allowed to be used क्रम transmissions.
 *	Bit 0 indicates channel 1, bit 1 indicates channel 2, etc.
 *	Set to 0 indicate EDMG not supported.
 * @bw_config: Channel BW Configuration subfield encodes
 *	the allowed channel bandwidth configurations
 */
काष्ठा ieee80211_edmg अणु
	u8 channels;
	क्रमागत ieee80211_edmg_bw_config bw_config;
पूर्ण;

/**
 * काष्ठा ieee80211_sta_s1g_cap - STA's S1G capabilities
 *
 * This काष्ठाure describes most essential parameters needed
 * to describe 802.11ah S1G capabilities क्रम a STA.
 *
 * @s1g_supported: is STA an S1G STA
 * @cap: S1G capabilities inक्रमmation
 * @nss_mcs: Supported NSS MCS set
 */
काष्ठा ieee80211_sta_s1g_cap अणु
	bool s1g;
	u8 cap[10]; /* use S1G_CAPAB_ */
	u8 nss_mcs[5];
पूर्ण;

/**
 * काष्ठा ieee80211_supported_band - frequency band definition
 *
 * This काष्ठाure describes a frequency band a wiphy
 * is able to operate in.
 *
 * @channels: Array of channels the hardware can operate with
 *	in this band.
 * @band: the band this काष्ठाure represents
 * @n_channels: Number of channels in @channels
 * @bitrates: Array of bitrates the hardware can operate with
 *	in this band. Must be sorted to give a valid "supported
 *	rates" IE, i.e. CCK rates first, then OFDM.
 * @n_bitrates: Number of bitrates in @bitrates
 * @ht_cap: HT capabilities in this band
 * @vht_cap: VHT capabilities in this band
 * @s1g_cap: S1G capabilities in this band
 * @edmg_cap: EDMG capabilities in this band
 * @s1g_cap: S1G capabilities in this band (S1B band only, of course)
 * @n_अगरtype_data: number of अगरtype data entries
 * @अगरtype_data: पूर्णांकerface type data entries.  Note that the bits in
 *	@types_mask inside this काष्ठाure cannot overlap (i.e. only
 *	one occurrence of each type is allowed across all instances of
 *	अगरtype_data).
 */
काष्ठा ieee80211_supported_band अणु
	काष्ठा ieee80211_channel *channels;
	काष्ठा ieee80211_rate *bitrates;
	क्रमागत nl80211_band band;
	पूर्णांक n_channels;
	पूर्णांक n_bitrates;
	काष्ठा ieee80211_sta_ht_cap ht_cap;
	काष्ठा ieee80211_sta_vht_cap vht_cap;
	काष्ठा ieee80211_sta_s1g_cap s1g_cap;
	काष्ठा ieee80211_edmg edmg_cap;
	u16 n_अगरtype_data;
	स्थिर काष्ठा ieee80211_sband_अगरtype_data *अगरtype_data;
पूर्ण;

/**
 * ieee80211_get_sband_अगरtype_data - वापस sband data क्रम a given अगरtype
 * @sband: the sband to search क्रम the STA on
 * @अगरtype: क्रमागत nl80211_अगरtype
 *
 * Return: poपूर्णांकer to काष्ठा ieee80211_sband_अगरtype_data, or शून्य is none found
 */
अटल अंतरभूत स्थिर काष्ठा ieee80211_sband_अगरtype_data *
ieee80211_get_sband_अगरtype_data(स्थिर काष्ठा ieee80211_supported_band *sband,
				u8 अगरtype)
अणु
	पूर्णांक i;

	अगर (WARN_ON(अगरtype >= NL80211_IFTYPE_MAX))
		वापस शून्य;

	क्रम (i = 0; i < sband->n_अगरtype_data; i++)  अणु
		स्थिर काष्ठा ieee80211_sband_अगरtype_data *data =
			&sband->अगरtype_data[i];

		अगर (data->types_mask & BIT(अगरtype))
			वापस data;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * ieee80211_get_he_अगरtype_cap - वापस HE capabilities क्रम an sband's अगरtype
 * @sband: the sband to search क्रम the अगरtype on
 * @अगरtype: क्रमागत nl80211_अगरtype
 *
 * Return: poपूर्णांकer to the काष्ठा ieee80211_sta_he_cap, or शून्य is none found
 */
अटल अंतरभूत स्थिर काष्ठा ieee80211_sta_he_cap *
ieee80211_get_he_अगरtype_cap(स्थिर काष्ठा ieee80211_supported_band *sband,
			    u8 अगरtype)
अणु
	स्थिर काष्ठा ieee80211_sband_अगरtype_data *data =
		ieee80211_get_sband_अगरtype_data(sband, अगरtype);

	अगर (data && data->he_cap.has_he)
		वापस &data->he_cap;

	वापस शून्य;
पूर्ण

/**
 * ieee80211_get_he_sta_cap - वापस HE capabilities क्रम an sband's STA
 * @sband: the sband to search क्रम the STA on
 *
 * Return: poपूर्णांकer to the काष्ठा ieee80211_sta_he_cap, or शून्य is none found
 */
अटल अंतरभूत स्थिर काष्ठा ieee80211_sta_he_cap *
ieee80211_get_he_sta_cap(स्थिर काष्ठा ieee80211_supported_band *sband)
अणु
	वापस ieee80211_get_he_अगरtype_cap(sband, NL80211_IFTYPE_STATION);
पूर्ण

/**
 * ieee80211_get_he_6ghz_capa - वापस HE 6 GHz capabilities
 * @sband: the sband to search क्रम the STA on
 * @अगरtype: the अगरtype to search क्रम
 *
 * Return: the 6GHz capabilities
 */
अटल अंतरभूत __le16
ieee80211_get_he_6ghz_capa(स्थिर काष्ठा ieee80211_supported_band *sband,
			   क्रमागत nl80211_अगरtype अगरtype)
अणु
	स्थिर काष्ठा ieee80211_sband_अगरtype_data *data =
		ieee80211_get_sband_अगरtype_data(sband, अगरtype);

	अगर (WARN_ON(!data || !data->he_cap.has_he))
		वापस 0;

	वापस data->he_6ghz_capa.capa;
पूर्ण

/**
 * wiphy_पढ़ो_of_freq_limits - पढ़ो frequency limits from device tree
 *
 * @wiphy: the wireless device to get extra limits क्रम
 *
 * Some devices may have extra limitations specअगरied in DT. This may be useful
 * क्रम chipsets that normally support more bands but are limited due to board
 * design (e.g. by antennas or बाह्यal घातer amplअगरier).
 *
 * This function पढ़ोs info from DT and uses it to *modअगरy* channels (disable
 * unavailable ones). It's usually a *bad* idea to use it in drivers with
 * shared channel data as DT limitations are device specअगरic. You should make
 * sure to call it only अगर channels in wiphy are copied and can be modअगरied
 * without affecting other devices.
 *
 * As this function access device node it has to be called after set_wiphy_dev.
 * It also modअगरies channels so they have to be set first.
 * If using this helper, call it beक्रमe wiphy_रेजिस्टर().
 */
#अगर_घोषित CONFIG_OF
व्योम wiphy_पढ़ो_of_freq_limits(काष्ठा wiphy *wiphy);
#अन्यथा /* CONFIG_OF */
अटल अंतरभूत व्योम wiphy_पढ़ो_of_freq_limits(काष्ठा wiphy *wiphy)
अणु
पूर्ण
#पूर्ण_अगर /* !CONFIG_OF */


/*
 * Wireless hardware/device configuration काष्ठाures and methods
 */

/**
 * DOC: Actions and configuration
 *
 * Each wireless device and each भव पूर्णांकerface offer a set of configuration
 * operations and other actions that are invoked by userspace. Each of these
 * actions is described in the operations काष्ठाure, and the parameters these
 * operations use are described separately.
 *
 * Additionally, some operations are asynchronous and expect to get status
 * inक्रमmation via some functions that drivers need to call.
 *
 * Scanning and BSS list handling with its associated functionality is described
 * in a separate chapter.
 */

#घोषणा VHT_MUMIMO_GROUPS_DATA_LEN (WLAN_MEMBERSHIP_LEN +\
				    WLAN_USER_POSITION_LEN)

/**
 * काष्ठा vअगर_params - describes भव पूर्णांकerface parameters
 * @flags: monitor पूर्णांकerface flags, unchanged अगर 0, otherwise
 *	%MONITOR_FLAG_CHANGED will be set
 * @use_4addr: use 4-address frames
 * @macaddr: address to use क्रम this भव पूर्णांकerface.
 *	If this parameter is set to zero address the driver may
 *	determine the address as needed.
 *	This feature is only fully supported by drivers that enable the
 *	%NL80211_FEATURE_MAC_ON_CREATE flag.  Others may support creating
 **	only p2p devices with specअगरied MAC.
 * @vht_mumimo_groups: MU-MIMO groupID, used क्रम monitoring MU-MIMO packets
 *	beदीर्घing to that MU-MIMO groupID; %शून्य अगर not changed
 * @vht_mumimo_follow_addr: MU-MIMO follow address, used क्रम monitoring
 *	MU-MIMO packets going to the specअगरied station; %शून्य अगर not changed
 */
काष्ठा vअगर_params अणु
	u32 flags;
	पूर्णांक use_4addr;
	u8 macaddr[ETH_ALEN];
	स्थिर u8 *vht_mumimo_groups;
	स्थिर u8 *vht_mumimo_follow_addr;
पूर्ण;

/**
 * काष्ठा key_params - key inक्रमmation
 *
 * Inक्रमmation about a key
 *
 * @key: key material
 * @key_len: length of key material
 * @cipher: cipher suite selector
 * @seq: sequence counter (IV/PN) क्रम TKIP and CCMP keys, only used
 *	with the get_key() callback, must be in little endian,
 *	length given by @seq_len.
 * @seq_len: length of @seq.
 * @vlan_id: vlan_id क्रम VLAN group key (अगर nonzero)
 * @mode: key install mode (RX_TX, NO_TX or SET_TX)
 */
काष्ठा key_params अणु
	स्थिर u8 *key;
	स्थिर u8 *seq;
	पूर्णांक key_len;
	पूर्णांक seq_len;
	u16 vlan_id;
	u32 cipher;
	क्रमागत nl80211_key_mode mode;
पूर्ण;

/**
 * काष्ठा cfg80211_chan_def - channel definition
 * @chan: the (control) channel
 * @width: channel width
 * @center_freq1: center frequency of first segment
 * @center_freq2: center frequency of second segment
 *	(only with 80+80 MHz)
 * @edmg: define the EDMG channels configuration.
 *	If edmg is requested (i.e. the .channels member is non-zero),
 *	chan will define the primary channel and all other
 *	parameters are ignored.
 * @freq1_offset: offset from @center_freq1, in KHz
 */
काष्ठा cfg80211_chan_def अणु
	काष्ठा ieee80211_channel *chan;
	क्रमागत nl80211_chan_width width;
	u32 center_freq1;
	u32 center_freq2;
	काष्ठा ieee80211_edmg edmg;
	u16 freq1_offset;
पूर्ण;

/*
 * cfg80211_bitrate_mask - masks क्रम bitrate control
 */
काष्ठा cfg80211_bitrate_mask अणु
	काष्ठा अणु
		u32 legacy;
		u8 ht_mcs[IEEE80211_HT_MCS_MASK_LEN];
		u16 vht_mcs[NL80211_VHT_NSS_MAX];
		u16 he_mcs[NL80211_HE_NSS_MAX];
		क्रमागत nl80211_txrate_gi gi;
		क्रमागत nl80211_he_gi he_gi;
		क्रमागत nl80211_he_ltf he_ltf;
	पूर्ण control[NUM_NL80211_BANDS];
पूर्ण;


/**
 * काष्ठा cfg80211_tid_cfg - TID specअगरic configuration
 * @config_override: Flag to notअगरy driver to reset TID configuration
 *	of the peer.
 * @tids: biपंचांगap of TIDs to modअगरy
 * @mask: biपंचांगap of attributes indicating which parameter changed,
 *	similar to &nl80211_tid_config_supp.
 * @noack: noack configuration value क्रम the TID
 * @retry_दीर्घ: retry count value
 * @retry_लघु: retry count value
 * @ampdu: Enable/Disable MPDU aggregation
 * @rtscts: Enable/Disable RTS/CTS
 * @amsdu: Enable/Disable MSDU aggregation
 * @txrate_type: Tx bitrate mask type
 * @txrate_mask: Tx bitrate to be applied क्रम the TID
 */
काष्ठा cfg80211_tid_cfg अणु
	bool config_override;
	u8 tids;
	u64 mask;
	क्रमागत nl80211_tid_config noack;
	u8 retry_दीर्घ, retry_लघु;
	क्रमागत nl80211_tid_config ampdu;
	क्रमागत nl80211_tid_config rtscts;
	क्रमागत nl80211_tid_config amsdu;
	क्रमागत nl80211_tx_rate_setting txrate_type;
	काष्ठा cfg80211_bitrate_mask txrate_mask;
पूर्ण;

/**
 * काष्ठा cfg80211_tid_config - TID configuration
 * @peer: Station's MAC address
 * @n_tid_conf: Number of TID specअगरic configurations to be applied
 * @tid_conf: Configuration change info
 */
काष्ठा cfg80211_tid_config अणु
	स्थिर u8 *peer;
	u32 n_tid_conf;
	काष्ठा cfg80211_tid_cfg tid_conf[];
पूर्ण;

/**
 * cfg80211_get_chandef_type - वापस old channel type from chandef
 * @chandef: the channel definition
 *
 * Return: The old channel type (NOHT, HT20, HT40+/-) from a given
 * chandef, which must have a bandwidth allowing this conversion.
 */
अटल अंतरभूत क्रमागत nl80211_channel_type
cfg80211_get_chandef_type(स्थिर काष्ठा cfg80211_chan_def *chandef)
अणु
	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_20_NOHT:
		वापस NL80211_CHAN_NO_HT;
	हाल NL80211_CHAN_WIDTH_20:
		वापस NL80211_CHAN_HT20;
	हाल NL80211_CHAN_WIDTH_40:
		अगर (chandef->center_freq1 > chandef->chan->center_freq)
			वापस NL80211_CHAN_HT40PLUS;
		वापस NL80211_CHAN_HT40MINUS;
	शेष:
		WARN_ON(1);
		वापस NL80211_CHAN_NO_HT;
	पूर्ण
पूर्ण

/**
 * cfg80211_chandef_create - create channel definition using channel type
 * @chandef: the channel definition काष्ठा to fill
 * @channel: the control channel
 * @chantype: the channel type
 *
 * Given a channel type, create a channel definition.
 */
व्योम cfg80211_chandef_create(काष्ठा cfg80211_chan_def *chandef,
			     काष्ठा ieee80211_channel *channel,
			     क्रमागत nl80211_channel_type chantype);

/**
 * cfg80211_chandef_identical - check अगर two channel definitions are identical
 * @chandef1: first channel definition
 * @chandef2: second channel definition
 *
 * Return: %true अगर the channels defined by the channel definitions are
 * identical, %false otherwise.
 */
अटल अंतरभूत bool
cfg80211_chandef_identical(स्थिर काष्ठा cfg80211_chan_def *chandef1,
			   स्थिर काष्ठा cfg80211_chan_def *chandef2)
अणु
	वापस (chandef1->chan == chandef2->chan &&
		chandef1->width == chandef2->width &&
		chandef1->center_freq1 == chandef2->center_freq1 &&
		chandef1->freq1_offset == chandef2->freq1_offset &&
		chandef1->center_freq2 == chandef2->center_freq2);
पूर्ण

/**
 * cfg80211_chandef_is_edmg - check अगर chandef represents an EDMG channel
 *
 * @chandef: the channel definition
 *
 * Return: %true अगर EDMG defined, %false otherwise.
 */
अटल अंतरभूत bool
cfg80211_chandef_is_edmg(स्थिर काष्ठा cfg80211_chan_def *chandef)
अणु
	वापस chandef->edmg.channels || chandef->edmg.bw_config;
पूर्ण

/**
 * cfg80211_chandef_compatible - check अगर two channel definitions are compatible
 * @chandef1: first channel definition
 * @chandef2: second channel definition
 *
 * Return: %शून्य अगर the given channel definitions are incompatible,
 * chandef1 or chandef2 otherwise.
 */
स्थिर काष्ठा cfg80211_chan_def *
cfg80211_chandef_compatible(स्थिर काष्ठा cfg80211_chan_def *chandef1,
			    स्थिर काष्ठा cfg80211_chan_def *chandef2);

/**
 * cfg80211_chandef_valid - check अगर a channel definition is valid
 * @chandef: the channel definition to check
 * Return: %true अगर the channel definition is valid. %false otherwise.
 */
bool cfg80211_chandef_valid(स्थिर काष्ठा cfg80211_chan_def *chandef);

/**
 * cfg80211_chandef_usable - check अगर secondary channels can be used
 * @wiphy: the wiphy to validate against
 * @chandef: the channel definition to check
 * @prohibited_flags: the regulatory channel flags that must not be set
 * Return: %true अगर secondary channels are usable. %false otherwise.
 */
bool cfg80211_chandef_usable(काष्ठा wiphy *wiphy,
			     स्थिर काष्ठा cfg80211_chan_def *chandef,
			     u32 prohibited_flags);

/**
 * cfg80211_chandef_dfs_required - checks अगर radar detection is required
 * @wiphy: the wiphy to validate against
 * @chandef: the channel definition to check
 * @अगरtype: the पूर्णांकerface type as specअगरied in &क्रमागत nl80211_अगरtype
 * Returns:
 *	1 अगर radar detection is required, 0 अगर it is not, < 0 on error
 */
पूर्णांक cfg80211_chandef_dfs_required(काष्ठा wiphy *wiphy,
				  स्थिर काष्ठा cfg80211_chan_def *chandef,
				  क्रमागत nl80211_अगरtype अगरtype);

/**
 * ieee80211_chandef_rate_flags - वापसs rate flags क्रम a channel
 *
 * In some channel types, not all rates may be used - क्रम example CCK
 * rates may not be used in 5/10 MHz channels.
 *
 * @chandef: channel definition क्रम the channel
 *
 * Returns: rate flags which apply क्रम this channel
 */
अटल अंतरभूत क्रमागत ieee80211_rate_flags
ieee80211_chandef_rate_flags(काष्ठा cfg80211_chan_def *chandef)
अणु
	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_5:
		वापस IEEE80211_RATE_SUPPORTS_5MHZ;
	हाल NL80211_CHAN_WIDTH_10:
		वापस IEEE80211_RATE_SUPPORTS_10MHZ;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ieee80211_chandef_max_घातer - maximum transmission घातer क्रम the chandef
 *
 * In some regulations, the transmit घातer may depend on the configured channel
 * bandwidth which may be defined as dBm/MHz. This function वापसs the actual
 * max_घातer क्रम non-standard (20 MHz) channels.
 *
 * @chandef: channel definition क्रम the channel
 *
 * Returns: maximum allowed transmission घातer in dBm क्रम the chandef
 */
अटल अंतरभूत पूर्णांक
ieee80211_chandef_max_घातer(काष्ठा cfg80211_chan_def *chandef)
अणु
	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_5:
		वापस min(chandef->chan->max_reg_घातer - 6,
			   chandef->chan->max_घातer);
	हाल NL80211_CHAN_WIDTH_10:
		वापस min(chandef->chan->max_reg_घातer - 3,
			   chandef->chan->max_घातer);
	शेष:
		अवरोध;
	पूर्ण
	वापस chandef->chan->max_घातer;
पूर्ण

/**
 * क्रमागत survey_info_flags - survey inक्रमmation flags
 *
 * @SURVEY_INFO_NOISE_DBM: noise (in dBm) was filled in
 * @SURVEY_INFO_IN_USE: channel is currently being used
 * @SURVEY_INFO_TIME: active समय (in ms) was filled in
 * @SURVEY_INFO_TIME_BUSY: busy समय was filled in
 * @SURVEY_INFO_TIME_EXT_BUSY: extension channel busy समय was filled in
 * @SURVEY_INFO_TIME_RX: receive समय was filled in
 * @SURVEY_INFO_TIME_TX: transmit समय was filled in
 * @SURVEY_INFO_TIME_SCAN: scan समय was filled in
 * @SURVEY_INFO_TIME_BSS_RX: local BSS receive समय was filled in
 *
 * Used by the driver to indicate which info in &काष्ठा survey_info
 * it has filled in during the get_survey().
 */
क्रमागत survey_info_flags अणु
	SURVEY_INFO_NOISE_DBM		= BIT(0),
	SURVEY_INFO_IN_USE		= BIT(1),
	SURVEY_INFO_TIME		= BIT(2),
	SURVEY_INFO_TIME_BUSY		= BIT(3),
	SURVEY_INFO_TIME_EXT_BUSY	= BIT(4),
	SURVEY_INFO_TIME_RX		= BIT(5),
	SURVEY_INFO_TIME_TX		= BIT(6),
	SURVEY_INFO_TIME_SCAN		= BIT(7),
	SURVEY_INFO_TIME_BSS_RX		= BIT(8),
पूर्ण;

/**
 * काष्ठा survey_info - channel survey response
 *
 * @channel: the channel this survey record reports, may be %शून्य क्रम a single
 *	record to report global statistics
 * @filled: bitflag of flags from &क्रमागत survey_info_flags
 * @noise: channel noise in dBm. This and all following fields are
 *	optional
 * @समय: amount of समय in ms the radio was turn on (on the channel)
 * @समय_busy: amount of समय the primary channel was sensed busy
 * @समय_ext_busy: amount of समय the extension channel was sensed busy
 * @समय_rx: amount of समय the radio spent receiving data
 * @समय_प्रकारx: amount of समय the radio spent transmitting data
 * @समय_scan: amount of समय the radio spent क्रम scanning
 * @समय_bss_rx: amount of समय the radio spent receiving data on a local BSS
 *
 * Used by dump_survey() to report back per-channel survey inक्रमmation.
 *
 * This काष्ठाure can later be expanded with things like
 * channel duty cycle etc.
 */
काष्ठा survey_info अणु
	काष्ठा ieee80211_channel *channel;
	u64 समय;
	u64 समय_busy;
	u64 समय_ext_busy;
	u64 समय_rx;
	u64 समय_प्रकारx;
	u64 समय_scan;
	u64 समय_bss_rx;
	u32 filled;
	s8 noise;
पूर्ण;

#घोषणा CFG80211_MAX_WEP_KEYS	4

/**
 * काष्ठा cfg80211_crypto_settings - Crypto settings
 * @wpa_versions: indicates which, अगर any, WPA versions are enabled
 *	(from क्रमागत nl80211_wpa_versions)
 * @cipher_group: group key cipher suite (or 0 अगर unset)
 * @n_ciphers_pairwise: number of AP supported unicast ciphers
 * @ciphers_pairwise: unicast key cipher suites
 * @n_akm_suites: number of AKM suites
 * @akm_suites: AKM suites
 * @control_port: Whether user space controls IEEE 802.1X port, i.e.,
 *	sets/clears %NL80211_STA_FLAG_AUTHORIZED. If true, the driver is
 *	required to assume that the port is unauthorized until authorized by
 *	user space. Otherwise, port is marked authorized by शेष.
 * @control_port_ethertype: the control port protocol that should be
 *	allowed through even on unauthorized ports
 * @control_port_no_encrypt: TRUE to prevent encryption of control port
 *	protocol frames.
 * @control_port_over_nl80211: TRUE अगर userspace expects to exchange control
 *	port frames over NL80211 instead of the network पूर्णांकerface.
 * @control_port_no_preauth: disables pre-auth rx over the nl80211 control
 *	port क्रम mac80211
 * @wep_keys: अटल WEP keys, अगर not शून्य poपूर्णांकs to an array of
 *	CFG80211_MAX_WEP_KEYS WEP keys
 * @wep_tx_key: key index (0..3) of the शेष TX अटल WEP key
 * @psk: PSK (क्रम devices supporting 4-way-handshake offload)
 * @sae_pwd: password क्रम SAE authentication (क्रम devices supporting SAE
 *	offload)
 * @sae_pwd_len: length of SAE password (क्रम devices supporting SAE offload)
 * @sae_pwe: The mechanisms allowed क्रम SAE PWE derivation:
 *
 *	NL80211_SAE_PWE_UNSPECIFIED
 *	  Not-specअगरied, used to indicate userspace did not specअगरy any
 *	  preference. The driver should follow its पूर्णांकernal policy in
 *	  such a scenario.
 *
 *	NL80211_SAE_PWE_HUNT_AND_PECK
 *	  Allow hunting-and-pecking loop only
 *
 *	NL80211_SAE_PWE_HASH_TO_ELEMENT
 *	  Allow hash-to-element only
 *
 *	NL80211_SAE_PWE_BOTH
 *	  Allow either hunting-and-pecking loop or hash-to-element
 */
काष्ठा cfg80211_crypto_settings अणु
	u32 wpa_versions;
	u32 cipher_group;
	पूर्णांक n_ciphers_pairwise;
	u32 ciphers_pairwise[NL80211_MAX_NR_CIPHER_SUITES];
	पूर्णांक n_akm_suites;
	u32 akm_suites[NL80211_MAX_NR_AKM_SUITES];
	bool control_port;
	__be16 control_port_ethertype;
	bool control_port_no_encrypt;
	bool control_port_over_nl80211;
	bool control_port_no_preauth;
	काष्ठा key_params *wep_keys;
	पूर्णांक wep_tx_key;
	स्थिर u8 *psk;
	स्थिर u8 *sae_pwd;
	u8 sae_pwd_len;
	क्रमागत nl80211_sae_pwe_mechanism sae_pwe;
पूर्ण;

/**
 * काष्ठा cfg80211_beacon_data - beacon data
 * @head: head portion of beacon (beक्रमe TIM IE)
 *	or %शून्य अगर not changed
 * @tail: tail portion of beacon (after TIM IE)
 *	or %शून्य अगर not changed
 * @head_len: length of @head
 * @tail_len: length of @tail
 * @beacon_ies: extra inक्रमmation element(s) to add पूर्णांकo Beacon frames or %शून्य
 * @beacon_ies_len: length of beacon_ies in octets
 * @proberesp_ies: extra inक्रमmation element(s) to add पूर्णांकo Probe Response
 *	frames or %शून्य
 * @proberesp_ies_len: length of proberesp_ies in octets
 * @assocresp_ies: extra inक्रमmation element(s) to add पूर्णांकo (Re)Association
 *	Response frames or %शून्य
 * @assocresp_ies_len: length of assocresp_ies in octets
 * @probe_resp_len: length of probe response ढाँचा (@probe_resp)
 * @probe_resp: probe response ढाँचा (AP mode only)
 * @fपंचांग_responder: enable FTM responder functionality; -1 क्रम no change
 *	(which also implies no change in LCI/civic location data)
 * @lci: Measurement Report element content, starting with Measurement Token
 *	(measurement type 8)
 * @civicloc: Measurement Report element content, starting with Measurement
 *	Token (measurement type 11)
 * @lci_len: LCI data length
 * @civicloc_len: Civic location data length
 */
काष्ठा cfg80211_beacon_data अणु
	स्थिर u8 *head, *tail;
	स्थिर u8 *beacon_ies;
	स्थिर u8 *proberesp_ies;
	स्थिर u8 *assocresp_ies;
	स्थिर u8 *probe_resp;
	स्थिर u8 *lci;
	स्थिर u8 *civicloc;
	s8 fपंचांग_responder;

	माप_प्रकार head_len, tail_len;
	माप_प्रकार beacon_ies_len;
	माप_प्रकार proberesp_ies_len;
	माप_प्रकार assocresp_ies_len;
	माप_प्रकार probe_resp_len;
	माप_प्रकार lci_len;
	माप_प्रकार civicloc_len;
पूर्ण;

काष्ठा mac_address अणु
	u8 addr[ETH_ALEN];
पूर्ण;

/**
 * काष्ठा cfg80211_acl_data - Access control list data
 *
 * @acl_policy: ACL policy to be applied on the station's
 *	entry specअगरied by mac_addr
 * @n_acl_entries: Number of MAC address entries passed
 * @mac_addrs: List of MAC addresses of stations to be used क्रम ACL
 */
काष्ठा cfg80211_acl_data अणु
	क्रमागत nl80211_acl_policy acl_policy;
	पूर्णांक n_acl_entries;

	/* Keep it last */
	काष्ठा mac_address mac_addrs[];
पूर्ण;

/**
 * काष्ठा cfg80211_fils_discovery - FILS discovery parameters from
 * IEEE Std 802.11ai-2016, Annex C.3 MIB detail.
 *
 * @min_पूर्णांकerval: Minimum packet पूर्णांकerval in TUs (0 - 10000)
 * @max_पूर्णांकerval: Maximum packet पूर्णांकerval in TUs (0 - 10000)
 * @पंचांगpl_len: Template length
 * @पंचांगpl: Template data क्रम FILS discovery frame including the action
 *	frame headers.
 */
काष्ठा cfg80211_fils_discovery अणु
	u32 min_पूर्णांकerval;
	u32 max_पूर्णांकerval;
	माप_प्रकार पंचांगpl_len;
	स्थिर u8 *पंचांगpl;
पूर्ण;

/**
 * काष्ठा cfg80211_unsol_bcast_probe_resp - Unsolicited broadcast probe
 *	response parameters in 6GHz.
 *
 * @पूर्णांकerval: Packet पूर्णांकerval in TUs. Maximum allowed is 20 TU, as mentioned
 *	in IEEE P802.11ax/D6.0 26.17.2.3.2 - AP behavior क्रम fast passive
 *	scanning
 * @पंचांगpl_len: Template length
 * @पंचांगpl: Template data क्रम probe response
 */
काष्ठा cfg80211_unsol_bcast_probe_resp अणु
	u32 पूर्णांकerval;
	माप_प्रकार पंचांगpl_len;
	स्थिर u8 *पंचांगpl;
पूर्ण;

/**
 * क्रमागत cfg80211_ap_settings_flags - AP settings flags
 *
 * Used by cfg80211_ap_settings
 *
 * @AP_SETTINGS_EXTERNAL_AUTH_SUPPORT: AP supports बाह्यal authentication
 */
क्रमागत cfg80211_ap_settings_flags अणु
	AP_SETTINGS_EXTERNAL_AUTH_SUPPORT = BIT(0),
पूर्ण;

/**
 * काष्ठा cfg80211_ap_settings - AP configuration
 *
 * Used to configure an AP पूर्णांकerface.
 *
 * @chandef: defines the channel to use
 * @beacon: beacon data
 * @beacon_पूर्णांकerval: beacon पूर्णांकerval
 * @dtim_period: DTIM period
 * @ssid: SSID to be used in the BSS (note: may be %शून्य अगर not provided from
 *	user space)
 * @ssid_len: length of @ssid
 * @hidden_ssid: whether to hide the SSID in Beacon/Probe Response frames
 * @crypto: crypto settings
 * @privacy: the BSS uses privacy
 * @auth_type: Authentication type (algorithm)
 * @smps_mode: SMPS mode
 * @inactivity_समयout: समय in seconds to determine station's inactivity.
 * @p2p_ctwinकरोw: P2P CT Winकरोw
 * @p2p_opp_ps: P2P opportunistic PS
 * @acl: ACL configuration used by the drivers which has support क्रम
 *	MAC address based access control
 * @pbss: If set, start as a PCP instead of AP. Relevant क्रम DMG
 *	networks.
 * @beacon_rate: bitrate to be used क्रम beacons
 * @ht_cap: HT capabilities (or %शून्य अगर HT isn't enabled)
 * @vht_cap: VHT capabilities (or %शून्य अगर VHT isn't enabled)
 * @he_cap: HE capabilities (or %शून्य अगर HE isn't enabled)
 * @ht_required: stations must support HT
 * @vht_required: stations must support VHT
 * @twt_responder: Enable Target Wait Time
 * @he_required: stations must support HE
 * @sae_h2e_required: stations must support direct H2E technique in SAE
 * @flags: flags, as defined in क्रमागत cfg80211_ap_settings_flags
 * @he_obss_pd: OBSS Packet Detection settings
 * @he_bss_color: BSS Color settings
 * @he_oper: HE operation IE (or %शून्य अगर HE isn't enabled)
 * @fils_discovery: FILS discovery transmission parameters
 * @unsol_bcast_probe_resp: Unsolicited broadcast probe response parameters
 */
काष्ठा cfg80211_ap_settings अणु
	काष्ठा cfg80211_chan_def chandef;

	काष्ठा cfg80211_beacon_data beacon;

	पूर्णांक beacon_पूर्णांकerval, dtim_period;
	स्थिर u8 *ssid;
	माप_प्रकार ssid_len;
	क्रमागत nl80211_hidden_ssid hidden_ssid;
	काष्ठा cfg80211_crypto_settings crypto;
	bool privacy;
	क्रमागत nl80211_auth_type auth_type;
	क्रमागत nl80211_smps_mode smps_mode;
	पूर्णांक inactivity_समयout;
	u8 p2p_ctwinकरोw;
	bool p2p_opp_ps;
	स्थिर काष्ठा cfg80211_acl_data *acl;
	bool pbss;
	काष्ठा cfg80211_bitrate_mask beacon_rate;

	स्थिर काष्ठा ieee80211_ht_cap *ht_cap;
	स्थिर काष्ठा ieee80211_vht_cap *vht_cap;
	स्थिर काष्ठा ieee80211_he_cap_elem *he_cap;
	स्थिर काष्ठा ieee80211_he_operation *he_oper;
	bool ht_required, vht_required, he_required, sae_h2e_required;
	bool twt_responder;
	u32 flags;
	काष्ठा ieee80211_he_obss_pd he_obss_pd;
	काष्ठा cfg80211_he_bss_color he_bss_color;
	काष्ठा cfg80211_fils_discovery fils_discovery;
	काष्ठा cfg80211_unsol_bcast_probe_resp unsol_bcast_probe_resp;
पूर्ण;

/**
 * काष्ठा cfg80211_csa_settings - channel चयन settings
 *
 * Used क्रम channel चयन
 *
 * @chandef: defines the channel to use after the चयन
 * @beacon_csa: beacon data जबतक perक्रमming the चयन
 * @counter_offsets_beacon: offsets of the counters within the beacon (tail)
 * @counter_offsets_presp: offsets of the counters within the probe response
 * @n_counter_offsets_beacon: number of csa counters the beacon (tail)
 * @n_counter_offsets_presp: number of csa counters in the probe response
 * @beacon_after: beacon data to be used on the new channel
 * @radar_required: whether radar detection is required on the new channel
 * @block_tx: whether transmissions should be blocked जबतक changing
 * @count: number of beacons until चयन
 */
काष्ठा cfg80211_csa_settings अणु
	काष्ठा cfg80211_chan_def chandef;
	काष्ठा cfg80211_beacon_data beacon_csa;
	स्थिर u16 *counter_offsets_beacon;
	स्थिर u16 *counter_offsets_presp;
	अचिन्हित पूर्णांक n_counter_offsets_beacon;
	अचिन्हित पूर्णांक n_counter_offsets_presp;
	काष्ठा cfg80211_beacon_data beacon_after;
	bool radar_required;
	bool block_tx;
	u8 count;
पूर्ण;

#घोषणा CFG80211_MAX_NUM_DIFFERENT_CHANNELS 10

/**
 * काष्ठा अगरace_combination_params - input parameters क्रम पूर्णांकerface combinations
 *
 * Used to pass पूर्णांकerface combination parameters
 *
 * @num_dअगरferent_channels: the number of dअगरferent channels we want
 *	to use क्रम verअगरication
 * @radar_detect: a biपंचांगap where each bit corresponds to a channel
 *	width where radar detection is needed, as in the definition of
 *	&काष्ठा ieee80211_अगरace_combination.@radar_detect_widths
 * @अगरtype_num: array with the number of पूर्णांकerfaces of each पूर्णांकerface
 *	type.  The index is the पूर्णांकerface type as specअगरied in &क्रमागत
 *	nl80211_अगरtype.
 * @new_beacon_पूर्णांक: set this to the beacon पूर्णांकerval of a new पूर्णांकerface
 *	that's not operating yet, अगर such is to be checked as part of
 *	the verअगरication
 */
काष्ठा अगरace_combination_params अणु
	पूर्णांक num_dअगरferent_channels;
	u8 radar_detect;
	पूर्णांक अगरtype_num[NUM_NL80211_IFTYPES];
	u32 new_beacon_पूर्णांक;
पूर्ण;

/**
 * क्रमागत station_parameters_apply_mask - station parameter values to apply
 * @STATION_PARAM_APPLY_UAPSD: apply new uAPSD parameters (uapsd_queues, max_sp)
 * @STATION_PARAM_APPLY_CAPABILITY: apply new capability
 * @STATION_PARAM_APPLY_PLINK_STATE: apply new plink state
 *
 * Not all station parameters have in-band "no change" संकेतling,
 * क्रम those that करोn't these flags will are used.
 */
क्रमागत station_parameters_apply_mask अणु
	STATION_PARAM_APPLY_UAPSD = BIT(0),
	STATION_PARAM_APPLY_CAPABILITY = BIT(1),
	STATION_PARAM_APPLY_PLINK_STATE = BIT(2),
	STATION_PARAM_APPLY_STA_TXPOWER = BIT(3),
पूर्ण;

/**
 * काष्ठा sta_txpwr - station txघातer configuration
 *
 * Used to configure txघातer क्रम station.
 *
 * @घातer: tx घातer (in dBm) to be used क्रम sending data traffic. If tx घातer
 *	is not provided, the शेष per-पूर्णांकerface tx घातer setting will be
 *	overriding. Driver should be picking up the lowest tx घातer, either tx
 *	घातer per-पूर्णांकerface or per-station.
 * @type: In particular अगर TPC %type is NL80211_TX_POWER_LIMITED then tx घातer
 *	will be less than or equal to specअगरied from userspace, whereas अगर TPC
 *	%type is NL80211_TX_POWER_AUTOMATIC then it indicates शेष tx घातer.
 *	NL80211_TX_POWER_FIXED is not a valid configuration option क्रम
 *	per peer TPC.
 */
काष्ठा sta_txpwr अणु
	s16 घातer;
	क्रमागत nl80211_tx_घातer_setting type;
पूर्ण;

/**
 * काष्ठा station_parameters - station parameters
 *
 * Used to change and create a new station.
 *
 * @vlan: vlan पूर्णांकerface station should beदीर्घ to
 * @supported_rates: supported rates in IEEE 802.11 क्रमmat
 *	(or शून्य क्रम no change)
 * @supported_rates_len: number of supported rates
 * @sta_flags_mask: station flags that changed
 *	(biपंचांगask of BIT(%NL80211_STA_FLAG_...))
 * @sta_flags_set: station flags values
 *	(biपंचांगask of BIT(%NL80211_STA_FLAG_...))
 * @listen_पूर्णांकerval: listen पूर्णांकerval or -1 क्रम no change
 * @aid: AID or zero क्रम no change
 * @vlan_id: VLAN ID क्रम station (अगर nonzero)
 * @peer_aid: mesh peer AID or zero क्रम no change
 * @plink_action: plink action to take
 * @plink_state: set the peer link state क्रम a station
 * @ht_capa: HT capabilities of station
 * @vht_capa: VHT capabilities of station
 * @uapsd_queues: biपंचांगap of queues configured क्रम uapsd. same क्रमmat
 *	as the AC biपंचांगap in the QoS info field
 * @max_sp: max Service Period. same क्रमmat as the MAX_SP in the
 *	QoS info field (but alपढ़ोy shअगरted करोwn)
 * @sta_modअगरy_mask: biपंचांगap indicating which parameters changed
 *	(क्रम those that करोn't have a natural "no change" value),
 *	see &क्रमागत station_parameters_apply_mask
 * @local_pm: local link-specअगरic mesh घातer save mode (no change when set
 *	to unknown)
 * @capability: station capability
 * @ext_capab: extended capabilities of the station
 * @ext_capab_len: number of extended capabilities
 * @supported_channels: supported channels in IEEE 802.11 क्रमmat
 * @supported_channels_len: number of supported channels
 * @supported_oper_classes: supported oper classes in IEEE 802.11 क्रमmat
 * @supported_oper_classes_len: number of supported operating classes
 * @opmode_notअगर: operating mode field from Operating Mode Notअगरication
 * @opmode_notअगर_used: inक्रमmation अगर operating mode field is used
 * @support_p2p_ps: inक्रमmation अगर station supports P2P PS mechanism
 * @he_capa: HE capabilities of station
 * @he_capa_len: the length of the HE capabilities
 * @airसमय_weight: airसमय scheduler weight क्रम this station
 * @txpwr: transmit घातer क्रम an associated station
 * @he_6ghz_capa: HE 6 GHz Band capabilities of station
 */
काष्ठा station_parameters अणु
	स्थिर u8 *supported_rates;
	काष्ठा net_device *vlan;
	u32 sta_flags_mask, sta_flags_set;
	u32 sta_modअगरy_mask;
	पूर्णांक listen_पूर्णांकerval;
	u16 aid;
	u16 vlan_id;
	u16 peer_aid;
	u8 supported_rates_len;
	u8 plink_action;
	u8 plink_state;
	स्थिर काष्ठा ieee80211_ht_cap *ht_capa;
	स्थिर काष्ठा ieee80211_vht_cap *vht_capa;
	u8 uapsd_queues;
	u8 max_sp;
	क्रमागत nl80211_mesh_घातer_mode local_pm;
	u16 capability;
	स्थिर u8 *ext_capab;
	u8 ext_capab_len;
	स्थिर u8 *supported_channels;
	u8 supported_channels_len;
	स्थिर u8 *supported_oper_classes;
	u8 supported_oper_classes_len;
	u8 opmode_notअगर;
	bool opmode_notअगर_used;
	पूर्णांक support_p2p_ps;
	स्थिर काष्ठा ieee80211_he_cap_elem *he_capa;
	u8 he_capa_len;
	u16 airसमय_weight;
	काष्ठा sta_txpwr txpwr;
	स्थिर काष्ठा ieee80211_he_6ghz_capa *he_6ghz_capa;
पूर्ण;

/**
 * काष्ठा station_del_parameters - station deletion parameters
 *
 * Used to delete a station entry (or all stations).
 *
 * @mac: MAC address of the station to हटाओ or शून्य to हटाओ all stations
 * @subtype: Management frame subtype to use क्रम indicating removal
 *	(10 = Disassociation, 12 = Deauthentication)
 * @reason_code: Reason code क्रम the Disassociation/Deauthentication frame
 */
काष्ठा station_del_parameters अणु
	स्थिर u8 *mac;
	u8 subtype;
	u16 reason_code;
पूर्ण;

/**
 * क्रमागत cfg80211_station_type - the type of station being modअगरied
 * @CFG80211_STA_AP_CLIENT: client of an AP पूर्णांकerface
 * @CFG80211_STA_AP_CLIENT_UNASSOC: client of an AP पूर्णांकerface that is still
 *	unassociated (update properties क्रम this type of client is permitted)
 * @CFG80211_STA_AP_MLME_CLIENT: client of an AP पूर्णांकerface that has
 *	the AP MLME in the device
 * @CFG80211_STA_AP_STA: AP station on managed पूर्णांकerface
 * @CFG80211_STA_IBSS: IBSS station
 * @CFG80211_STA_TDLS_PEER_SETUP: TDLS peer on managed पूर्णांकerface (dummy entry
 *	जबतक TDLS setup is in progress, it moves out of this state when
 *	being marked authorized; use this only अगर TDLS with बाह्यal setup is
 *	supported/used)
 * @CFG80211_STA_TDLS_PEER_ACTIVE: TDLS peer on managed पूर्णांकerface (active
 *	entry that is operating, has been marked authorized by userspace)
 * @CFG80211_STA_MESH_PEER_KERNEL: peer on mesh पूर्णांकerface (kernel managed)
 * @CFG80211_STA_MESH_PEER_USER: peer on mesh पूर्णांकerface (user managed)
 */
क्रमागत cfg80211_station_type अणु
	CFG80211_STA_AP_CLIENT,
	CFG80211_STA_AP_CLIENT_UNASSOC,
	CFG80211_STA_AP_MLME_CLIENT,
	CFG80211_STA_AP_STA,
	CFG80211_STA_IBSS,
	CFG80211_STA_TDLS_PEER_SETUP,
	CFG80211_STA_TDLS_PEER_ACTIVE,
	CFG80211_STA_MESH_PEER_KERNEL,
	CFG80211_STA_MESH_PEER_USER,
पूर्ण;

/**
 * cfg80211_check_station_change - validate parameter changes
 * @wiphy: the wiphy this operates on
 * @params: the new parameters क्रम a station
 * @statype: the type of station being modअगरied
 *
 * Utility function क्रम the @change_station driver method. Call this function
 * with the appropriate station type looking up the station (and checking that
 * it exists). It will verअगरy whether the station change is acceptable, and अगर
 * not will वापस an error code. Note that it may modअगरy the parameters क्रम
 * backward compatibility reasons, so करोn't use them beक्रमe calling this.
 */
पूर्णांक cfg80211_check_station_change(काष्ठा wiphy *wiphy,
				  काष्ठा station_parameters *params,
				  क्रमागत cfg80211_station_type statype);

/**
 * क्रमागत rate_info_flags - bitrate info flags
 *
 * Used by the driver to indicate the specअगरic rate transmission
 * type क्रम 802.11n transmissions.
 *
 * @RATE_INFO_FLAGS_MCS: mcs field filled with HT MCS
 * @RATE_INFO_FLAGS_VHT_MCS: mcs field filled with VHT MCS
 * @RATE_INFO_FLAGS_SHORT_GI: 400ns guard पूर्णांकerval
 * @RATE_INFO_FLAGS_DMG: 60GHz MCS
 * @RATE_INFO_FLAGS_HE_MCS: HE MCS inक्रमmation
 * @RATE_INFO_FLAGS_EDMG: 60GHz MCS in EDMG mode
 * @RATE_INFO_FLAGS_EXTENDED_SC_DMG: 60GHz extended SC MCS
 */
क्रमागत rate_info_flags अणु
	RATE_INFO_FLAGS_MCS			= BIT(0),
	RATE_INFO_FLAGS_VHT_MCS			= BIT(1),
	RATE_INFO_FLAGS_SHORT_GI		= BIT(2),
	RATE_INFO_FLAGS_DMG			= BIT(3),
	RATE_INFO_FLAGS_HE_MCS			= BIT(4),
	RATE_INFO_FLAGS_EDMG			= BIT(5),
	RATE_INFO_FLAGS_EXTENDED_SC_DMG		= BIT(6),
पूर्ण;

/**
 * क्रमागत rate_info_bw - rate bandwidth inक्रमmation
 *
 * Used by the driver to indicate the rate bandwidth.
 *
 * @RATE_INFO_BW_5: 5 MHz bandwidth
 * @RATE_INFO_BW_10: 10 MHz bandwidth
 * @RATE_INFO_BW_20: 20 MHz bandwidth
 * @RATE_INFO_BW_40: 40 MHz bandwidth
 * @RATE_INFO_BW_80: 80 MHz bandwidth
 * @RATE_INFO_BW_160: 160 MHz bandwidth
 * @RATE_INFO_BW_HE_RU: bandwidth determined by HE RU allocation
 */
क्रमागत rate_info_bw अणु
	RATE_INFO_BW_20 = 0,
	RATE_INFO_BW_5,
	RATE_INFO_BW_10,
	RATE_INFO_BW_40,
	RATE_INFO_BW_80,
	RATE_INFO_BW_160,
	RATE_INFO_BW_HE_RU,
पूर्ण;

/**
 * काष्ठा rate_info - bitrate inक्रमmation
 *
 * Inक्रमmation about a receiving or transmitting bitrate
 *
 * @flags: bitflag of flags from &क्रमागत rate_info_flags
 * @mcs: mcs index अगर काष्ठा describes an HT/VHT/HE rate
 * @legacy: bitrate in 100kbit/s क्रम 802.11abg
 * @nss: number of streams (VHT & HE only)
 * @bw: bandwidth (from &क्रमागत rate_info_bw)
 * @he_gi: HE guard पूर्णांकerval (from &क्रमागत nl80211_he_gi)
 * @he_dcm: HE DCM value
 * @he_ru_alloc: HE RU allocation (from &क्रमागत nl80211_he_ru_alloc,
 *	only valid अगर bw is %RATE_INFO_BW_HE_RU)
 * @n_bonded_ch: In हाल of EDMG the number of bonded channels (1-4)
 */
काष्ठा rate_info अणु
	u8 flags;
	u8 mcs;
	u16 legacy;
	u8 nss;
	u8 bw;
	u8 he_gi;
	u8 he_dcm;
	u8 he_ru_alloc;
	u8 n_bonded_ch;
पूर्ण;

/**
 * क्रमागत bss_param_flags - bitrate info flags
 *
 * Used by the driver to indicate the specअगरic rate transmission
 * type क्रम 802.11n transmissions.
 *
 * @BSS_PARAM_FLAGS_CTS_PROT: whether CTS protection is enabled
 * @BSS_PARAM_FLAGS_SHORT_PREAMBLE: whether लघु preamble is enabled
 * @BSS_PARAM_FLAGS_SHORT_SLOT_TIME: whether लघु slot समय is enabled
 */
क्रमागत bss_param_flags अणु
	BSS_PARAM_FLAGS_CTS_PROT	= 1<<0,
	BSS_PARAM_FLAGS_SHORT_PREAMBLE	= 1<<1,
	BSS_PARAM_FLAGS_SHORT_SLOT_TIME	= 1<<2,
पूर्ण;

/**
 * काष्ठा sta_bss_parameters - BSS parameters क्रम the attached station
 *
 * Inक्रमmation about the currently associated BSS
 *
 * @flags: bitflag of flags from &क्रमागत bss_param_flags
 * @dtim_period: DTIM period क्रम the BSS
 * @beacon_पूर्णांकerval: beacon पूर्णांकerval
 */
काष्ठा sta_bss_parameters अणु
	u8 flags;
	u8 dtim_period;
	u16 beacon_पूर्णांकerval;
पूर्ण;

/**
 * काष्ठा cfg80211_txq_stats - TXQ statistics क्रम this TID
 * @filled: biपंचांगap of flags using the bits of &क्रमागत nl80211_txq_stats to
 *	indicate the relevant values in this काष्ठा are filled
 * @backlog_bytes: total number of bytes currently backlogged
 * @backlog_packets: total number of packets currently backlogged
 * @flows: number of new flows seen
 * @drops: total number of packets dropped
 * @ecn_marks: total number of packets marked with ECN CE
 * @overlimit: number of drops due to queue space overflow
 * @overmemory: number of drops due to memory limit overflow
 * @collisions: number of hash collisions
 * @tx_bytes: total number of bytes dequeued
 * @tx_packets: total number of packets dequeued
 * @max_flows: maximum number of flows supported
 */
काष्ठा cfg80211_txq_stats अणु
	u32 filled;
	u32 backlog_bytes;
	u32 backlog_packets;
	u32 flows;
	u32 drops;
	u32 ecn_marks;
	u32 overlimit;
	u32 overmemory;
	u32 collisions;
	u32 tx_bytes;
	u32 tx_packets;
	u32 max_flows;
पूर्ण;

/**
 * काष्ठा cfg80211_tid_stats - per-TID statistics
 * @filled: biपंचांगap of flags using the bits of &क्रमागत nl80211_tid_stats to
 *	indicate the relevant values in this काष्ठा are filled
 * @rx_msdu: number of received MSDUs
 * @tx_msdu: number of (attempted) transmitted MSDUs
 * @tx_msdu_retries: number of retries (not counting the first) क्रम
 *	transmitted MSDUs
 * @tx_msdu_failed: number of failed transmitted MSDUs
 * @txq_stats: TXQ statistics
 */
काष्ठा cfg80211_tid_stats अणु
	u32 filled;
	u64 rx_msdu;
	u64 tx_msdu;
	u64 tx_msdu_retries;
	u64 tx_msdu_failed;
	काष्ठा cfg80211_txq_stats txq_stats;
पूर्ण;

#घोषणा IEEE80211_MAX_CHAINS	4

/**
 * काष्ठा station_info - station inक्रमmation
 *
 * Station inक्रमmation filled by driver क्रम get_station() and dump_station.
 *
 * @filled: bitflag of flags using the bits of &क्रमागत nl80211_sta_info to
 *	indicate the relevant values in this काष्ठा क्रम them
 * @connected_समय: समय(in secs) since a station is last connected
 * @inactive_समय: समय since last station activity (tx/rx) in milliseconds
 * @assoc_at: booसमय (ns) of the last association
 * @rx_bytes: bytes (size of MPDUs) received from this station
 * @tx_bytes: bytes (size of MPDUs) transmitted to this station
 * @llid: mesh local link id
 * @plid: mesh peer link id
 * @plink_state: mesh peer link state
 * @संकेत: The संकेत strength, type depends on the wiphy's संकेत_type.
 *	For CFG80211_SIGNAL_TYPE_MBM, value is expressed in _dBm_.
 * @संकेत_avg: Average संकेत strength, type depends on the wiphy's संकेत_type.
 *	For CFG80211_SIGNAL_TYPE_MBM, value is expressed in _dBm_.
 * @chains: biपंचांगask क्रम filled values in @chain_संकेत, @chain_संकेत_avg
 * @chain_संकेत: per-chain संकेत strength of last received packet in dBm
 * @chain_संकेत_avg: per-chain संकेत strength average in dBm
 * @txrate: current unicast bitrate from this station
 * @rxrate: current unicast bitrate to this station
 * @rx_packets: packets (MSDUs & MMPDUs) received from this station
 * @tx_packets: packets (MSDUs & MMPDUs) transmitted to this station
 * @tx_retries: cumulative retry counts (MPDUs)
 * @tx_failed: number of failed transmissions (MPDUs) (retries exceeded, no ACK)
 * @rx_dropped_misc:  Dropped क्रम un-specअगरied reason.
 * @bss_param: current BSS parameters
 * @generation: generation number क्रम nl80211 dumps.
 *	This number should increase every समय the list of stations
 *	changes, i.e. when a station is added or हटाओd, so that
 *	userspace can tell whether it got a consistent snapshot.
 * @assoc_req_ies: IEs from (Re)Association Request.
 *	This is used only when in AP mode with drivers that करो not use
 *	user space MLME/SME implementation. The inक्रमmation is provided क्रम
 *	the cfg80211_new_sta() calls to notअगरy user space of the IEs.
 * @assoc_req_ies_len: Length of assoc_req_ies buffer in octets.
 * @sta_flags: station flags mask & values
 * @beacon_loss_count: Number of बार beacon loss event has triggered.
 * @t_offset: Time offset of the station relative to this host.
 * @local_pm: local mesh STA घातer save mode
 * @peer_pm: peer mesh STA घातer save mode
 * @nonpeer_pm: non-peer mesh STA घातer save mode
 * @expected_throughput: expected throughput in kbps (including 802.11 headers)
 *	towards this station.
 * @rx_beacon: number of beacons received from this peer
 * @rx_beacon_संकेत_avg: संकेत strength average (in dBm) क्रम beacons received
 *	from this peer
 * @connected_to_gate: true अगर mesh STA has a path to mesh gate
 * @rx_duration: aggregate PPDU duration(usecs) क्रम all the frames from a peer
 * @tx_duration: aggregate PPDU duration(usecs) क्रम all the frames to a peer
 * @airसमय_weight: current airसमय scheduling weight
 * @pertid: per-TID statistics, see &काष्ठा cfg80211_tid_stats, using the last
 *	(IEEE80211_NUM_TIDS) index क्रम MSDUs not encapsulated in QoS-MPDUs.
 *	Note that this करोesn't use the @filled bit, but is used अगर non-शून्य.
 * @ack_संकेत: संकेत strength (in dBm) of the last ACK frame.
 * @avg_ack_संकेत: average rssi value of ack packet क्रम the no of msdu's has
 *	been sent.
 * @rx_mpdu_count: number of MPDUs received from this station
 * @fcs_err_count: number of packets (MPDUs) received from this station with
 *	an FCS error. This counter should be incremented only when TA of the
 *	received packet with an FCS error matches the peer MAC address.
 * @airसमय_link_metric: mesh airसमय link metric.
 * @connected_to_as: true अगर mesh STA has a path to authentication server
 */
काष्ठा station_info अणु
	u64 filled;
	u32 connected_समय;
	u32 inactive_समय;
	u64 assoc_at;
	u64 rx_bytes;
	u64 tx_bytes;
	u16 llid;
	u16 plid;
	u8 plink_state;
	s8 संकेत;
	s8 संकेत_avg;

	u8 chains;
	s8 chain_संकेत[IEEE80211_MAX_CHAINS];
	s8 chain_संकेत_avg[IEEE80211_MAX_CHAINS];

	काष्ठा rate_info txrate;
	काष्ठा rate_info rxrate;
	u32 rx_packets;
	u32 tx_packets;
	u32 tx_retries;
	u32 tx_failed;
	u32 rx_dropped_misc;
	काष्ठा sta_bss_parameters bss_param;
	काष्ठा nl80211_sta_flag_update sta_flags;

	पूर्णांक generation;

	स्थिर u8 *assoc_req_ies;
	माप_प्रकार assoc_req_ies_len;

	u32 beacon_loss_count;
	s64 t_offset;
	क्रमागत nl80211_mesh_घातer_mode local_pm;
	क्रमागत nl80211_mesh_घातer_mode peer_pm;
	क्रमागत nl80211_mesh_घातer_mode nonpeer_pm;

	u32 expected_throughput;

	u64 tx_duration;
	u64 rx_duration;
	u64 rx_beacon;
	u8 rx_beacon_संकेत_avg;
	u8 connected_to_gate;

	काष्ठा cfg80211_tid_stats *pertid;
	s8 ack_संकेत;
	s8 avg_ack_संकेत;

	u16 airसमय_weight;

	u32 rx_mpdu_count;
	u32 fcs_err_count;

	u32 airसमय_link_metric;

	u8 connected_to_as;
पूर्ण;

/**
 * काष्ठा cfg80211_sar_sub_specs - sub specs limit
 * @घातer: घातer limitation in 0.25dbm
 * @freq_range_index: index the घातer limitation applies to
 */
काष्ठा cfg80211_sar_sub_specs अणु
	s32 घातer;
	u32 freq_range_index;
पूर्ण;

/**
 * काष्ठा cfg80211_sar_specs - sar limit specs
 * @type: it's set with घातer in 0.25dbm or other types
 * @num_sub_specs: number of sar sub specs
 * @sub_specs: memory to hold the sar sub specs
 */
काष्ठा cfg80211_sar_specs अणु
	क्रमागत nl80211_sar_type type;
	u32 num_sub_specs;
	काष्ठा cfg80211_sar_sub_specs sub_specs[];
पूर्ण;


/**
 * काष्ठा cfg80211_sar_freq_ranges - sar frequency ranges
 * @start_freq:  start range edge frequency
 * @end_freq:    end range edge frequency
 */
काष्ठा cfg80211_sar_freq_ranges अणु
	u32 start_freq;
	u32 end_freq;
पूर्ण;

/**
 * काष्ठा cfg80211_sar_capa - sar limit capability
 * @type: it's set via घातer in 0.25dbm or other types
 * @num_freq_ranges: number of frequency ranges
 * @freq_ranges: memory to hold the freq ranges.
 *
 * Note: WLAN driver may append new ranges or split an existing
 * range to small ones and then append them.
 */
काष्ठा cfg80211_sar_capa अणु
	क्रमागत nl80211_sar_type type;
	u32 num_freq_ranges;
	स्थिर काष्ठा cfg80211_sar_freq_ranges *freq_ranges;
पूर्ण;

#अगर IS_ENABLED(CONFIG_CFG80211)
/**
 * cfg80211_get_station - retrieve inक्रमmation about a given station
 * @dev: the device where the station is supposed to be connected to
 * @mac_addr: the mac address of the station of पूर्णांकerest
 * @sinfo: poपूर्णांकer to the काष्ठाure to fill with the inक्रमmation
 *
 * Returns 0 on success and sinfo is filled with the available inक्रमmation
 * otherwise वापसs a negative error code and the content of sinfo has to be
 * considered undefined.
 */
पूर्णांक cfg80211_get_station(काष्ठा net_device *dev, स्थिर u8 *mac_addr,
			 काष्ठा station_info *sinfo);
#अन्यथा
अटल अंतरभूत पूर्णांक cfg80211_get_station(काष्ठा net_device *dev,
				       स्थिर u8 *mac_addr,
				       काष्ठा station_info *sinfo)
अणु
	वापस -ENOENT;
पूर्ण
#पूर्ण_अगर

/**
 * क्रमागत monitor_flags - monitor flags
 *
 * Monitor पूर्णांकerface configuration flags. Note that these must be the bits
 * according to the nl80211 flags.
 *
 * @MONITOR_FLAG_CHANGED: set अगर the flags were changed
 * @MONITOR_FLAG_FCSFAIL: pass frames with bad FCS
 * @MONITOR_FLAG_PLCPFAIL: pass frames with bad PLCP
 * @MONITOR_FLAG_CONTROL: pass control frames
 * @MONITOR_FLAG_OTHER_BSS: disable BSSID filtering
 * @MONITOR_FLAG_COOK_FRAMES: report frames after processing
 * @MONITOR_FLAG_ACTIVE: active monitor, ACKs frames on its MAC address
 */
क्रमागत monitor_flags अणु
	MONITOR_FLAG_CHANGED		= 1<<__NL80211_MNTR_FLAG_INVALID,
	MONITOR_FLAG_FCSFAIL		= 1<<NL80211_MNTR_FLAG_FCSFAIL,
	MONITOR_FLAG_PLCPFAIL		= 1<<NL80211_MNTR_FLAG_PLCPFAIL,
	MONITOR_FLAG_CONTROL		= 1<<NL80211_MNTR_FLAG_CONTROL,
	MONITOR_FLAG_OTHER_BSS		= 1<<NL80211_MNTR_FLAG_OTHER_BSS,
	MONITOR_FLAG_COOK_FRAMES	= 1<<NL80211_MNTR_FLAG_COOK_FRAMES,
	MONITOR_FLAG_ACTIVE		= 1<<NL80211_MNTR_FLAG_ACTIVE,
पूर्ण;

/**
 * क्रमागत mpath_info_flags -  mesh path inक्रमmation flags
 *
 * Used by the driver to indicate which info in &काष्ठा mpath_info it has filled
 * in during get_station() or dump_station().
 *
 * @MPATH_INFO_FRAME_QLEN: @frame_qlen filled
 * @MPATH_INFO_SN: @sn filled
 * @MPATH_INFO_METRIC: @metric filled
 * @MPATH_INFO_EXPTIME: @expसमय filled
 * @MPATH_INFO_DISCOVERY_TIMEOUT: @discovery_समयout filled
 * @MPATH_INFO_DISCOVERY_RETRIES: @discovery_retries filled
 * @MPATH_INFO_FLAGS: @flags filled
 * @MPATH_INFO_HOP_COUNT: @hop_count filled
 * @MPATH_INFO_PATH_CHANGE: @path_change_count filled
 */
क्रमागत mpath_info_flags अणु
	MPATH_INFO_FRAME_QLEN		= BIT(0),
	MPATH_INFO_SN			= BIT(1),
	MPATH_INFO_METRIC		= BIT(2),
	MPATH_INFO_EXPTIME		= BIT(3),
	MPATH_INFO_DISCOVERY_TIMEOUT	= BIT(4),
	MPATH_INFO_DISCOVERY_RETRIES	= BIT(5),
	MPATH_INFO_FLAGS		= BIT(6),
	MPATH_INFO_HOP_COUNT		= BIT(7),
	MPATH_INFO_PATH_CHANGE		= BIT(8),
पूर्ण;

/**
 * काष्ठा mpath_info - mesh path inक्रमmation
 *
 * Mesh path inक्रमmation filled by driver क्रम get_mpath() and dump_mpath().
 *
 * @filled: bitfield of flags from &क्रमागत mpath_info_flags
 * @frame_qlen: number of queued frames क्रम this destination
 * @sn: target sequence number
 * @metric: metric (cost) of this mesh path
 * @expसमय: expiration समय क्रम the mesh path from now, in msecs
 * @flags: mesh path flags
 * @discovery_समयout: total mesh path discovery समयout, in msecs
 * @discovery_retries: mesh path discovery retries
 * @generation: generation number क्रम nl80211 dumps.
 *	This number should increase every समय the list of mesh paths
 *	changes, i.e. when a station is added or हटाओd, so that
 *	userspace can tell whether it got a consistent snapshot.
 * @hop_count: hops to destination
 * @path_change_count: total number of path changes to destination
 */
काष्ठा mpath_info अणु
	u32 filled;
	u32 frame_qlen;
	u32 sn;
	u32 metric;
	u32 expसमय;
	u32 discovery_समयout;
	u8 discovery_retries;
	u8 flags;
	u8 hop_count;
	u32 path_change_count;

	पूर्णांक generation;
पूर्ण;

/**
 * काष्ठा bss_parameters - BSS parameters
 *
 * Used to change BSS parameters (मुख्यly क्रम AP mode).
 *
 * @use_cts_prot: Whether to use CTS protection
 *	(0 = no, 1 = yes, -1 = करो not change)
 * @use_लघु_preamble: Whether the use of लघु preambles is allowed
 *	(0 = no, 1 = yes, -1 = करो not change)
 * @use_लघु_slot_समय: Whether the use of लघु slot समय is allowed
 *	(0 = no, 1 = yes, -1 = करो not change)
 * @basic_rates: basic rates in IEEE 802.11 क्रमmat
 *	(or शून्य क्रम no change)
 * @basic_rates_len: number of basic rates
 * @ap_isolate: करो not क्रमward packets between connected stations
 *	(0 = no, 1 = yes, -1 = करो not change)
 * @ht_opmode: HT Operation mode
 *	(u16 = opmode, -1 = करो not change)
 * @p2p_ctwinकरोw: P2P CT Winकरोw (-1 = no change)
 * @p2p_opp_ps: P2P opportunistic PS (-1 = no change)
 */
काष्ठा bss_parameters अणु
	पूर्णांक use_cts_prot;
	पूर्णांक use_लघु_preamble;
	पूर्णांक use_लघु_slot_समय;
	स्थिर u8 *basic_rates;
	u8 basic_rates_len;
	पूर्णांक ap_isolate;
	पूर्णांक ht_opmode;
	s8 p2p_ctwinकरोw, p2p_opp_ps;
पूर्ण;

/**
 * काष्ठा mesh_config - 802.11s mesh configuration
 *
 * These parameters can be changed जबतक the mesh is active.
 *
 * @करोt11MeshRetryTimeout: the initial retry समयout in millisecond units used
 *	by the Mesh Peering Open message
 * @करोt11MeshConfirmTimeout: the initial retry समयout in millisecond units
 *	used by the Mesh Peering Open message
 * @करोt11MeshHoldingTimeout: the confirm समयout in millisecond units used by
 *	the mesh peering management to बंद a mesh peering
 * @करोt11MeshMaxPeerLinks: the maximum number of peer links allowed on this
 *	mesh पूर्णांकerface
 * @करोt11MeshMaxRetries: the maximum number of peer link खोलो retries that can
 *	be sent to establish a new peer link instance in a mesh
 * @करोt11MeshTTL: the value of TTL field set at a source mesh STA
 * @element_ttl: the value of TTL field set at a mesh STA क्रम path selection
 *	elements
 * @स्वतः_खोलो_plinks: whether we should स्वतःmatically खोलो peer links when we
 *	detect compatible mesh peers
 * @करोt11MeshNbrOffsetMaxNeighbor: the maximum number of neighbors to
 *	synchronize to क्रम 11s शेष synchronization method
 * @करोt11MeshHWMPmaxPREQretries: the number of action frames containing a PREQ
 *	that an originator mesh STA can send to a particular path target
 * @path_refresh_समय: how frequently to refresh mesh paths in milliseconds
 * @min_discovery_समयout: the minimum length of समय to रुको until giving up on
 *	a path discovery in milliseconds
 * @करोt11MeshHWMPactivePathTimeout: the समय (in TUs) क्रम which mesh STAs
 *	receiving a PREQ shall consider the क्रमwarding inक्रमmation from the
 *	root to be valid. (TU = समय unit)
 * @करोt11MeshHWMPpreqMinInterval: the minimum पूर्णांकerval of समय (in TUs) during
 *	which a mesh STA can send only one action frame containing a PREQ
 *	element
 * @करोt11MeshHWMPperrMinInterval: the minimum पूर्णांकerval of समय (in TUs) during
 *	which a mesh STA can send only one Action frame containing a PERR
 *	element
 * @करोt11MeshHWMPnetDiameterTraversalTime: the पूर्णांकerval of समय (in TUs) that
 *	it takes क्रम an HWMP inक्रमmation element to propagate across the mesh
 * @करोt11MeshHWMPRootMode: the configuration of a mesh STA as root mesh STA
 * @करोt11MeshHWMPRannInterval: the पूर्णांकerval of समय (in TUs) between root
 *	announcements are transmitted
 * @करोt11MeshGateAnnouncementProtocol: whether to advertise that this mesh
 *	station has access to a broader network beyond the MBSS. (This is
 *	missnamed in draft 12.0: करोt11MeshGateAnnouncementProtocol set to true
 *	only means that the station will announce others it's a mesh gate, but
 *	not necessarily using the gate announcement protocol. Still keeping the
 *	same nomenclature to be in sync with the spec)
 * @करोt11MeshForwarding: whether the Mesh STA is क्रमwarding or non-क्रमwarding
 *	entity (शेष is TRUE - क्रमwarding entity)
 * @rssi_threshold: the threshold क्रम average संकेत strength of candidate
 *	station to establish a peer link
 * @ht_opmode: mesh HT protection mode
 *
 * @करोt11MeshHWMPactivePathToRootTimeout: The समय (in TUs) क्रम which mesh STAs
 *	receiving a proactive PREQ shall consider the क्रमwarding inक्रमmation to
 *	the root mesh STA to be valid.
 *
 * @करोt11MeshHWMProotInterval: The पूर्णांकerval of समय (in TUs) between proactive
 *	PREQs are transmitted.
 * @करोt11MeshHWMPconfirmationInterval: The minimum पूर्णांकerval of समय (in TUs)
 *	during which a mesh STA can send only one Action frame containing
 *	a PREQ element क्रम root path confirmation.
 * @घातer_mode: The शेष mesh घातer save mode which will be the initial
 *	setting क्रम new peer links.
 * @करोt11MeshAwakeWinकरोwDuration: The duration in TUs the STA will reमुख्य awake
 *	after transmitting its beacon.
 * @plink_समयout: If no tx activity is seen from a STA we've established
 *	peering with क्रम दीर्घer than this समय (in seconds), then हटाओ it
 *	from the STA's list of peers.  Default is 30 minutes.
 * @करोt11MeshConnectedToMeshGate: अगर set to true, advertise that this STA is
 *      connected to a mesh gate in mesh क्रमmation info.  If false, the
 *      value in mesh क्रमmation is determined by the presence of root paths
 *      in the mesh path table
 * @करोt11MeshNolearn: Try to aव्योम multi-hop path discovery (e.g. PREQ/PREP
 *      क्रम HWMP) अगर the destination is a direct neighbor. Note that this might
 *      not be the optimal decision as a multi-hop route might be better. So
 *      अगर using this setting you will likely also want to disable
 *      करोt11MeshForwarding and use another mesh routing protocol on top.
 */
काष्ठा mesh_config अणु
	u16 करोt11MeshRetryTimeout;
	u16 करोt11MeshConfirmTimeout;
	u16 करोt11MeshHoldingTimeout;
	u16 करोt11MeshMaxPeerLinks;
	u8 करोt11MeshMaxRetries;
	u8 करोt11MeshTTL;
	u8 element_ttl;
	bool स्वतः_खोलो_plinks;
	u32 करोt11MeshNbrOffsetMaxNeighbor;
	u8 करोt11MeshHWMPmaxPREQretries;
	u32 path_refresh_समय;
	u16 min_discovery_समयout;
	u32 करोt11MeshHWMPactivePathTimeout;
	u16 करोt11MeshHWMPpreqMinInterval;
	u16 करोt11MeshHWMPperrMinInterval;
	u16 करोt11MeshHWMPnetDiameterTraversalTime;
	u8 करोt11MeshHWMPRootMode;
	bool करोt11MeshConnectedToMeshGate;
	bool करोt11MeshConnectedToAuthServer;
	u16 करोt11MeshHWMPRannInterval;
	bool करोt11MeshGateAnnouncementProtocol;
	bool करोt11MeshForwarding;
	s32 rssi_threshold;
	u16 ht_opmode;
	u32 करोt11MeshHWMPactivePathToRootTimeout;
	u16 करोt11MeshHWMProotInterval;
	u16 करोt11MeshHWMPconfirmationInterval;
	क्रमागत nl80211_mesh_घातer_mode घातer_mode;
	u16 करोt11MeshAwakeWinकरोwDuration;
	u32 plink_समयout;
	bool करोt11MeshNolearn;
पूर्ण;

/**
 * काष्ठा mesh_setup - 802.11s mesh setup configuration
 * @chandef: defines the channel to use
 * @mesh_id: the mesh ID
 * @mesh_id_len: length of the mesh ID, at least 1 and at most 32 bytes
 * @sync_method: which synchronization method to use
 * @path_sel_proto: which path selection protocol to use
 * @path_metric: which metric to use
 * @auth_id: which authentication method this mesh is using
 * @ie: venकरोr inक्रमmation elements (optional)
 * @ie_len: length of venकरोr inक्रमmation elements
 * @is_authenticated: this mesh requires authentication
 * @is_secure: this mesh uses security
 * @user_mpm: userspace handles all MPM functions
 * @dtim_period: DTIM period to use
 * @beacon_पूर्णांकerval: beacon पूर्णांकerval to use
 * @mcast_rate: multicat rate क्रम Mesh Node [6Mbps is the शेष क्रम 802.11a]
 * @basic_rates: basic rates to use when creating the mesh
 * @beacon_rate: bitrate to be used क्रम beacons
 * @userspace_handles_dfs: whether user space controls DFS operation, i.e.
 *	changes the channel when a radar is detected. This is required
 *	to operate on DFS channels.
 * @control_port_over_nl80211: TRUE अगर userspace expects to exchange control
 *	port frames over NL80211 instead of the network पूर्णांकerface.
 *
 * These parameters are fixed when the mesh is created.
 */
काष्ठा mesh_setup अणु
	काष्ठा cfg80211_chan_def chandef;
	स्थिर u8 *mesh_id;
	u8 mesh_id_len;
	u8 sync_method;
	u8 path_sel_proto;
	u8 path_metric;
	u8 auth_id;
	स्थिर u8 *ie;
	u8 ie_len;
	bool is_authenticated;
	bool is_secure;
	bool user_mpm;
	u8 dtim_period;
	u16 beacon_पूर्णांकerval;
	पूर्णांक mcast_rate[NUM_NL80211_BANDS];
	u32 basic_rates;
	काष्ठा cfg80211_bitrate_mask beacon_rate;
	bool userspace_handles_dfs;
	bool control_port_over_nl80211;
पूर्ण;

/**
 * काष्ठा ocb_setup - 802.11p OCB mode setup configuration
 * @chandef: defines the channel to use
 *
 * These parameters are fixed when connecting to the network
 */
काष्ठा ocb_setup अणु
	काष्ठा cfg80211_chan_def chandef;
पूर्ण;

/**
 * काष्ठा ieee80211_txq_params - TX queue parameters
 * @ac: AC identअगरier
 * @txop: Maximum burst समय in units of 32 usecs, 0 meaning disabled
 * @cwmin: Minimum contention winकरोw [a value of the क्रमm 2^n-1 in the range
 *	1..32767]
 * @cwmax: Maximum contention winकरोw [a value of the क्रमm 2^n-1 in the range
 *	1..32767]
 * @aअगरs: Arbitration पूर्णांकerframe space [0..255]
 */
काष्ठा ieee80211_txq_params अणु
	क्रमागत nl80211_ac ac;
	u16 txop;
	u16 cwmin;
	u16 cwmax;
	u8 aअगरs;
पूर्ण;

/**
 * DOC: Scanning and BSS list handling
 *
 * The scanning process itself is fairly simple, but cfg80211 offers quite
 * a bit of helper functionality. To start a scan, the scan operation will
 * be invoked with a scan definition. This scan definition contains the
 * channels to scan, and the SSIDs to send probe requests क्रम (including the
 * wildcard, अगर desired). A passive scan is indicated by having no SSIDs to
 * probe. Additionally, a scan request may contain extra inक्रमmation elements
 * that should be added to the probe request. The IEs are guaranteed to be
 * well-क्रमmed, and will not exceed the maximum length the driver advertised
 * in the wiphy काष्ठाure.
 *
 * When scanning finds a BSS, cfg80211 needs to be notअगरied of that, because
 * it is responsible क्रम मुख्यtaining the BSS list; the driver should not
 * मुख्यtain a list itself. For this notअगरication, various functions exist.
 *
 * Since drivers करो not मुख्यtain a BSS list, there are also a number of
 * functions to search क्रम a BSS and obtain inक्रमmation about it from the
 * BSS काष्ठाure cfg80211 मुख्यtains. The BSS list is also made available
 * to userspace.
 */

/**
 * काष्ठा cfg80211_ssid - SSID description
 * @ssid: the SSID
 * @ssid_len: length of the ssid
 */
काष्ठा cfg80211_ssid अणु
	u8 ssid[IEEE80211_MAX_SSID_LEN];
	u8 ssid_len;
पूर्ण;

/**
 * काष्ठा cfg80211_scan_info - inक्रमmation about completed scan
 * @scan_start_tsf: scan start समय in terms of the TSF of the BSS that the
 *	wireless device that requested the scan is connected to. If this
 *	inक्रमmation is not available, this field is left zero.
 * @tsf_bssid: the BSSID according to which %scan_start_tsf is set.
 * @पातed: set to true अगर the scan was पातed क्रम any reason,
 *	userspace will be notअगरied of that
 */
काष्ठा cfg80211_scan_info अणु
	u64 scan_start_tsf;
	u8 tsf_bssid[ETH_ALEN] __aligned(2);
	bool पातed;
पूर्ण;

/**
 * काष्ठा cfg80211_scan_6ghz_params - relevant क्रम 6 GHz only
 *
 * @लघु_bssid: लघु ssid to scan क्रम
 * @bssid: bssid to scan क्रम
 * @channel_idx: idx of the channel in the channel array in the scan request
 *	 which the above info relvant to
 * @unsolicited_probe: the AP transmits unsolicited probe response every 20 TU
 * @लघु_ssid_valid: लघु_ssid is valid and can be used
 * @psc_no_listen: when set, and the channel is a PSC channel, no need to रुको
 *       20 TUs beक्रमe starting to send probe requests.
 */
काष्ठा cfg80211_scan_6ghz_params अणु
	u32 लघु_ssid;
	u32 channel_idx;
	u8 bssid[ETH_ALEN];
	bool unsolicited_probe;
	bool लघु_ssid_valid;
	bool psc_no_listen;
पूर्ण;

/**
 * काष्ठा cfg80211_scan_request - scan request description
 *
 * @ssids: SSIDs to scan क्रम (active scan only)
 * @n_ssids: number of SSIDs
 * @channels: channels to scan on.
 * @n_channels: total number of channels to scan
 * @scan_width: channel width क्रम scanning
 * @ie: optional inक्रमmation element(s) to add पूर्णांकo Probe Request or %शून्य
 * @ie_len: length of ie in octets
 * @duration: how दीर्घ to listen on each channel, in TUs. If
 *	%duration_mandatory is not set, this is the maximum dwell समय and
 *	the actual dwell समय may be लघुer.
 * @duration_mandatory: अगर set, the scan duration must be as specअगरied by the
 *	%duration field.
 * @flags: bit field of flags controlling operation
 * @rates: biपंचांगap of rates to advertise क्रम each band
 * @wiphy: the wiphy this was क्रम
 * @scan_start: समय (in jअगरfies) when the scan started
 * @wdev: the wireless device to scan क्रम
 * @info: (पूर्णांकernal) inक्रमmation about completed scan
 * @notअगरied: (पूर्णांकernal) scan request was notअगरied as करोne or पातed
 * @no_cck: used to send probe requests at non CCK rate in 2GHz band
 * @mac_addr: MAC address used with अक्रमomisation
 * @mac_addr_mask: MAC address mask used with अक्रमomisation, bits that
 *	are 0 in the mask should be अक्रमomised, bits that are 1 should
 *	be taken from the @mac_addr
 * @scan_6ghz: relevant क्रम split scan request only,
 *	true अगर this is the second scan request
 * @n_6ghz_params: number of 6 GHz params
 * @scan_6ghz_params: 6 GHz params
 * @bssid: BSSID to scan क्रम (most commonly, the wildcard BSSID)
 */
काष्ठा cfg80211_scan_request अणु
	काष्ठा cfg80211_ssid *ssids;
	पूर्णांक n_ssids;
	u32 n_channels;
	क्रमागत nl80211_bss_scan_width scan_width;
	स्थिर u8 *ie;
	माप_प्रकार ie_len;
	u16 duration;
	bool duration_mandatory;
	u32 flags;

	u32 rates[NUM_NL80211_BANDS];

	काष्ठा wireless_dev *wdev;

	u8 mac_addr[ETH_ALEN] __aligned(2);
	u8 mac_addr_mask[ETH_ALEN] __aligned(2);
	u8 bssid[ETH_ALEN] __aligned(2);

	/* पूर्णांकernal */
	काष्ठा wiphy *wiphy;
	अचिन्हित दीर्घ scan_start;
	काष्ठा cfg80211_scan_info info;
	bool notअगरied;
	bool no_cck;
	bool scan_6ghz;
	u32 n_6ghz_params;
	काष्ठा cfg80211_scan_6ghz_params *scan_6ghz_params;

	/* keep last */
	काष्ठा ieee80211_channel *channels[];
पूर्ण;

अटल अंतरभूत व्योम get_अक्रमom_mask_addr(u8 *buf, स्थिर u8 *addr, स्थिर u8 *mask)
अणु
	पूर्णांक i;

	get_अक्रमom_bytes(buf, ETH_ALEN);
	क्रम (i = 0; i < ETH_ALEN; i++) अणु
		buf[i] &= ~mask[i];
		buf[i] |= addr[i] & mask[i];
	पूर्ण
पूर्ण

/**
 * काष्ठा cfg80211_match_set - sets of attributes to match
 *
 * @ssid: SSID to be matched; may be zero-length in हाल of BSSID match
 *	or no match (RSSI only)
 * @bssid: BSSID to be matched; may be all-zero BSSID in हाल of SSID match
 *	or no match (RSSI only)
 * @rssi_thold: करोn't report scan results below this threshold (in s32 dBm)
 * @per_band_rssi_thold: Minimum rssi threshold क्रम each band to be applied
 *	क्रम filtering out scan results received. Drivers advertize this support
 *	of band specअगरic rssi based filtering through the feature capability
 *	%NL80211_EXT_FEATURE_SCHED_SCAN_BAND_SPECIFIC_RSSI_THOLD. These band
 *	specअगरic rssi thresholds take precedence over rssi_thold, अगर specअगरied.
 *	If not specअगरied क्रम any band, it will be asचिन्हित with rssi_thold of
 *	corresponding matchset.
 */
काष्ठा cfg80211_match_set अणु
	काष्ठा cfg80211_ssid ssid;
	u8 bssid[ETH_ALEN];
	s32 rssi_thold;
	s32 per_band_rssi_thold[NUM_NL80211_BANDS];
पूर्ण;

/**
 * काष्ठा cfg80211_sched_scan_plan - scan plan क्रम scheduled scan
 *
 * @पूर्णांकerval: पूर्णांकerval between scheduled scan iterations. In seconds.
 * @iterations: number of scan iterations in this scan plan. Zero means
 *	infinite loop.
 *	The last scan plan will always have this parameter set to zero,
 *	all other scan plans will have a finite number of iterations.
 */
काष्ठा cfg80211_sched_scan_plan अणु
	u32 पूर्णांकerval;
	u32 iterations;
पूर्ण;

/**
 * काष्ठा cfg80211_bss_select_adjust - BSS selection with RSSI adjusपंचांगent.
 *
 * @band: band of BSS which should match क्रम RSSI level adjusपंचांगent.
 * @delta: value of RSSI level adjusपंचांगent.
 */
काष्ठा cfg80211_bss_select_adjust अणु
	क्रमागत nl80211_band band;
	s8 delta;
पूर्ण;

/**
 * काष्ठा cfg80211_sched_scan_request - scheduled scan request description
 *
 * @reqid: identअगरies this request.
 * @ssids: SSIDs to scan क्रम (passed in the probe_reqs in active scans)
 * @n_ssids: number of SSIDs
 * @n_channels: total number of channels to scan
 * @scan_width: channel width क्रम scanning
 * @ie: optional inक्रमmation element(s) to add पूर्णांकo Probe Request or %शून्य
 * @ie_len: length of ie in octets
 * @flags: bit field of flags controlling operation
 * @match_sets: sets of parameters to be matched क्रम a scan result
 *	entry to be considered valid and to be passed to the host
 *	(others are filtered out).
 *	If ommited, all results are passed.
 * @n_match_sets: number of match sets
 * @report_results: indicates that results were reported क्रम this request
 * @wiphy: the wiphy this was क्रम
 * @dev: the पूर्णांकerface
 * @scan_start: start समय of the scheduled scan
 * @channels: channels to scan
 * @min_rssi_thold: क्रम drivers only supporting a single threshold, this
 *	contains the minimum over all matchsets
 * @mac_addr: MAC address used with अक्रमomisation
 * @mac_addr_mask: MAC address mask used with अक्रमomisation, bits that
 *	are 0 in the mask should be अक्रमomised, bits that are 1 should
 *	be taken from the @mac_addr
 * @scan_plans: scan plans to be executed in this scheduled scan. Lowest
 *	index must be executed first.
 * @n_scan_plans: number of scan plans, at least 1.
 * @rcu_head: RCU callback used to मुक्त the काष्ठा
 * @owner_nlportid: netlink portid of owner (अगर this should is a request
 *	owned by a particular socket)
 * @nl_owner_dead: netlink owner socket was बंदd - this request be मुक्तd
 * @list: क्रम keeping list of requests.
 * @delay: delay in seconds to use beक्रमe starting the first scan
 *	cycle.  The driver may ignore this parameter and start
 *	immediately (or at any other समय), अगर this feature is not
 *	supported.
 * @relative_rssi_set: Indicates whether @relative_rssi is set or not.
 * @relative_rssi: Relative RSSI threshold in dB to restrict scan result
 *	reporting in connected state to हालs where a matching BSS is determined
 *	to have better or slightly worse RSSI than the current connected BSS.
 *	The relative RSSI threshold values are ignored in disconnected state.
 * @rssi_adjust: delta dB of RSSI preference to be given to the BSSs that beदीर्घ
 *	to the specअगरied band जबतक deciding whether a better BSS is reported
 *	using @relative_rssi. If delta is a negative number, the BSSs that
 *	beदीर्घ to the specअगरied band will be penalized by delta dB in relative
 *	comparisions.
 */
काष्ठा cfg80211_sched_scan_request अणु
	u64 reqid;
	काष्ठा cfg80211_ssid *ssids;
	पूर्णांक n_ssids;
	u32 n_channels;
	क्रमागत nl80211_bss_scan_width scan_width;
	स्थिर u8 *ie;
	माप_प्रकार ie_len;
	u32 flags;
	काष्ठा cfg80211_match_set *match_sets;
	पूर्णांक n_match_sets;
	s32 min_rssi_thold;
	u32 delay;
	काष्ठा cfg80211_sched_scan_plan *scan_plans;
	पूर्णांक n_scan_plans;

	u8 mac_addr[ETH_ALEN] __aligned(2);
	u8 mac_addr_mask[ETH_ALEN] __aligned(2);

	bool relative_rssi_set;
	s8 relative_rssi;
	काष्ठा cfg80211_bss_select_adjust rssi_adjust;

	/* पूर्णांकernal */
	काष्ठा wiphy *wiphy;
	काष्ठा net_device *dev;
	अचिन्हित दीर्घ scan_start;
	bool report_results;
	काष्ठा rcu_head rcu_head;
	u32 owner_nlportid;
	bool nl_owner_dead;
	काष्ठा list_head list;

	/* keep last */
	काष्ठा ieee80211_channel *channels[];
पूर्ण;

/**
 * क्रमागत cfg80211_संकेत_type - संकेत type
 *
 * @CFG80211_SIGNAL_TYPE_NONE: no संकेत strength inक्रमmation available
 * @CFG80211_SIGNAL_TYPE_MBM: संकेत strength in mBm (100*dBm)
 * @CFG80211_SIGNAL_TYPE_UNSPEC: संकेत strength, increasing from 0 through 100
 */
क्रमागत cfg80211_संकेत_type अणु
	CFG80211_SIGNAL_TYPE_NONE,
	CFG80211_SIGNAL_TYPE_MBM,
	CFG80211_SIGNAL_TYPE_UNSPEC,
पूर्ण;

/**
 * काष्ठा cfg80211_inक्रमm_bss - BSS inक्रमm data
 * @chan: channel the frame was received on
 * @scan_width: scan width that was used
 * @संकेत: संकेत strength value, according to the wiphy's
 *	संकेत type
 * @bootसमय_ns: बारtamp (CLOCK_BOOTTIME) when the inक्रमmation was
 *	received; should match the समय when the frame was actually
 *	received by the device (not just by the host, in हाल it was
 *	buffered on the device) and be accurate to about 10ms.
 *	If the frame isn't buffered, just passing the वापस value of
 *	kसमय_get_bootसमय_ns() is likely appropriate.
 * @parent_tsf: the समय at the start of reception of the first octet of the
 *	बारtamp field of the frame. The समय is the TSF of the BSS specअगरied
 *	by %parent_bssid.
 * @parent_bssid: the BSS according to which %parent_tsf is set. This is set to
 *	the BSS that requested the scan in which the beacon/probe was received.
 * @chains: biपंचांगask क्रम filled values in @chain_संकेत.
 * @chain_संकेत: per-chain संकेत strength of last received BSS in dBm.
 */
काष्ठा cfg80211_inक्रमm_bss अणु
	काष्ठा ieee80211_channel *chan;
	क्रमागत nl80211_bss_scan_width scan_width;
	s32 संकेत;
	u64 bootसमय_ns;
	u64 parent_tsf;
	u8 parent_bssid[ETH_ALEN] __aligned(2);
	u8 chains;
	s8 chain_संकेत[IEEE80211_MAX_CHAINS];
पूर्ण;

/**
 * काष्ठा cfg80211_bss_ies - BSS entry IE data
 * @tsf: TSF contained in the frame that carried these IEs
 * @rcu_head: पूर्णांकernal use, क्रम मुक्तing
 * @len: length of the IEs
 * @from_beacon: these IEs are known to come from a beacon
 * @data: IE data
 */
काष्ठा cfg80211_bss_ies अणु
	u64 tsf;
	काष्ठा rcu_head rcu_head;
	पूर्णांक len;
	bool from_beacon;
	u8 data[];
पूर्ण;

/**
 * काष्ठा cfg80211_bss - BSS description
 *
 * This काष्ठाure describes a BSS (which may also be a mesh network)
 * क्रम use in scan results and similar.
 *
 * @channel: channel this BSS is on
 * @scan_width: width of the control channel
 * @bssid: BSSID of the BSS
 * @beacon_पूर्णांकerval: the beacon पूर्णांकerval as from the frame
 * @capability: the capability field in host byte order
 * @ies: the inक्रमmation elements (Note that there is no guarantee that these
 *	are well-क्रमmed!); this is a poपूर्णांकer to either the beacon_ies or
 *	proberesp_ies depending on whether Probe Response frame has been
 *	received. It is always non-%शून्य.
 * @beacon_ies: the inक्रमmation elements from the last Beacon frame
 *	(implementation note: अगर @hidden_beacon_bss is set this काष्ठा करोesn't
 *	own the beacon_ies, but they're just poपूर्णांकers to the ones from the
 *	@hidden_beacon_bss काष्ठा)
 * @proberesp_ies: the inक्रमmation elements from the last Probe Response frame
 * @hidden_beacon_bss: in हाल this BSS काष्ठा represents a probe response from
 *	a BSS that hides the SSID in its beacon, this poपूर्णांकs to the BSS काष्ठा
 *	that holds the beacon data. @beacon_ies is still valid, of course, and
 *	poपूर्णांकs to the same data as hidden_beacon_bss->beacon_ies in that हाल.
 * @transmitted_bss: poपूर्णांकer to the transmitted BSS, अगर this is a
 *	non-transmitted one (multi-BSSID support)
 * @nontrans_list: list of non-transmitted BSS, अगर this is a transmitted one
 *	(multi-BSSID support)
 * @संकेत: संकेत strength value (type depends on the wiphy's संकेत_type)
 * @chains: biपंचांगask क्रम filled values in @chain_संकेत.
 * @chain_संकेत: per-chain संकेत strength of last received BSS in dBm.
 * @bssid_index: index in the multiple BSS set
 * @max_bssid_indicator: max number of members in the BSS set
 * @priv: निजी area क्रम driver use, has at least wiphy->bss_priv_size bytes
 */
काष्ठा cfg80211_bss अणु
	काष्ठा ieee80211_channel *channel;
	क्रमागत nl80211_bss_scan_width scan_width;

	स्थिर काष्ठा cfg80211_bss_ies __rcu *ies;
	स्थिर काष्ठा cfg80211_bss_ies __rcu *beacon_ies;
	स्थिर काष्ठा cfg80211_bss_ies __rcu *proberesp_ies;

	काष्ठा cfg80211_bss *hidden_beacon_bss;
	काष्ठा cfg80211_bss *transmitted_bss;
	काष्ठा list_head nontrans_list;

	s32 संकेत;

	u16 beacon_पूर्णांकerval;
	u16 capability;

	u8 bssid[ETH_ALEN];
	u8 chains;
	s8 chain_संकेत[IEEE80211_MAX_CHAINS];

	u8 bssid_index;
	u8 max_bssid_indicator;

	u8 priv[] __aligned(माप(व्योम *));
पूर्ण;

/**
 * ieee80211_bss_get_elem - find element with given ID
 * @bss: the bss to search
 * @id: the element ID
 *
 * Note that the वापस value is an RCU-रक्षित poपूर्णांकer, so
 * rcu_पढ़ो_lock() must be held when calling this function.
 * Return: %शून्य अगर not found.
 */
स्थिर काष्ठा element *ieee80211_bss_get_elem(काष्ठा cfg80211_bss *bss, u8 id);

/**
 * ieee80211_bss_get_ie - find IE with given ID
 * @bss: the bss to search
 * @id: the element ID
 *
 * Note that the वापस value is an RCU-रक्षित poपूर्णांकer, so
 * rcu_पढ़ो_lock() must be held when calling this function.
 * Return: %शून्य अगर not found.
 */
अटल अंतरभूत स्थिर u8 *ieee80211_bss_get_ie(काष्ठा cfg80211_bss *bss, u8 id)
अणु
	वापस (व्योम *)ieee80211_bss_get_elem(bss, id);
पूर्ण


/**
 * काष्ठा cfg80211_auth_request - Authentication request data
 *
 * This काष्ठाure provides inक्रमmation needed to complete IEEE 802.11
 * authentication.
 *
 * @bss: The BSS to authenticate with, the callee must obtain a reference
 *	to it अगर it needs to keep it.
 * @auth_type: Authentication type (algorithm)
 * @ie: Extra IEs to add to Authentication frame or %शून्य
 * @ie_len: Length of ie buffer in octets
 * @key_len: length of WEP key क्रम shared key authentication
 * @key_idx: index of WEP key क्रम shared key authentication
 * @key: WEP key क्रम shared key authentication
 * @auth_data: Fields and elements in Authentication frames. This contains
 *	the authentication frame body (non-IE and IE data), excluding the
 *	Authentication algorithm number, i.e., starting at the Authentication
 *	transaction sequence number field.
 * @auth_data_len: Length of auth_data buffer in octets
 */
काष्ठा cfg80211_auth_request अणु
	काष्ठा cfg80211_bss *bss;
	स्थिर u8 *ie;
	माप_प्रकार ie_len;
	क्रमागत nl80211_auth_type auth_type;
	स्थिर u8 *key;
	u8 key_len, key_idx;
	स्थिर u8 *auth_data;
	माप_प्रकार auth_data_len;
पूर्ण;

/**
 * क्रमागत cfg80211_assoc_req_flags - Over-ride शेष behaviour in association.
 *
 * @ASSOC_REQ_DISABLE_HT:  Disable HT (802.11n)
 * @ASSOC_REQ_DISABLE_VHT:  Disable VHT
 * @ASSOC_REQ_USE_RRM: Declare RRM capability in this association
 * @CONNECT_REQ_EXTERNAL_AUTH_SUPPORT: User space indicates बाह्यal
 *	authentication capability. Drivers can offload authentication to
 *	userspace अगर this flag is set. Only applicable क्रम cfg80211_connect()
 *	request (connect callback).
 * @ASSOC_REQ_DISABLE_HE:  Disable HE
 */
क्रमागत cfg80211_assoc_req_flags अणु
	ASSOC_REQ_DISABLE_HT			= BIT(0),
	ASSOC_REQ_DISABLE_VHT			= BIT(1),
	ASSOC_REQ_USE_RRM			= BIT(2),
	CONNECT_REQ_EXTERNAL_AUTH_SUPPORT	= BIT(3),
	ASSOC_REQ_DISABLE_HE			= BIT(4),
पूर्ण;

/**
 * काष्ठा cfg80211_assoc_request - (Re)Association request data
 *
 * This काष्ठाure provides inक्रमmation needed to complete IEEE 802.11
 * (re)association.
 * @bss: The BSS to associate with. If the call is successful the driver is
 *	given a reference that it must give back to cfg80211_send_rx_assoc()
 *	or to cfg80211_assoc_समयout(). To ensure proper refcounting, new
 *	association requests जबतक alपढ़ोy associating must be rejected.
 * @ie: Extra IEs to add to (Re)Association Request frame or %शून्य
 * @ie_len: Length of ie buffer in octets
 * @use_mfp: Use management frame protection (IEEE 802.11w) in this association
 * @crypto: crypto settings
 * @prev_bssid: previous BSSID, अगर not %शून्य use reassociate frame. This is used
 *	to indicate a request to reassociate within the ESS instead of a request
 *	करो the initial association with the ESS. When included, this is set to
 *	the BSSID of the current association, i.e., to the value that is
 *	included in the Current AP address field of the Reassociation Request
 *	frame.
 * @flags:  See &क्रमागत cfg80211_assoc_req_flags
 * @ht_capa:  HT Capabilities over-rides.  Values set in ht_capa_mask
 *	will be used in ht_capa.  Un-supported values will be ignored.
 * @ht_capa_mask:  The bits of ht_capa which are to be used.
 * @vht_capa: VHT capability override
 * @vht_capa_mask: VHT capability mask indicating which fields to use
 * @fils_kek: FILS KEK क्रम protecting (Re)Association Request/Response frame or
 *	%शून्य अगर FILS is not used.
 * @fils_kek_len: Length of fils_kek in octets
 * @fils_nonces: FILS nonces (part of AAD) क्रम protecting (Re)Association
 *	Request/Response frame or %शून्य अगर FILS is not used. This field starts
 *	with 16 octets of STA Nonce followed by 16 octets of AP Nonce.
 * @s1g_capa: S1G capability override
 * @s1g_capa_mask: S1G capability override mask
 */
काष्ठा cfg80211_assoc_request अणु
	काष्ठा cfg80211_bss *bss;
	स्थिर u8 *ie, *prev_bssid;
	माप_प्रकार ie_len;
	काष्ठा cfg80211_crypto_settings crypto;
	bool use_mfp;
	u32 flags;
	काष्ठा ieee80211_ht_cap ht_capa;
	काष्ठा ieee80211_ht_cap ht_capa_mask;
	काष्ठा ieee80211_vht_cap vht_capa, vht_capa_mask;
	स्थिर u8 *fils_kek;
	माप_प्रकार fils_kek_len;
	स्थिर u8 *fils_nonces;
	काष्ठा ieee80211_s1g_cap s1g_capa, s1g_capa_mask;
पूर्ण;

/**
 * काष्ठा cfg80211_deauth_request - Deauthentication request data
 *
 * This काष्ठाure provides inक्रमmation needed to complete IEEE 802.11
 * deauthentication.
 *
 * @bssid: the BSSID of the BSS to deauthenticate from
 * @ie: Extra IEs to add to Deauthentication frame or %शून्य
 * @ie_len: Length of ie buffer in octets
 * @reason_code: The reason code क्रम the deauthentication
 * @local_state_change: अगर set, change local state only and
 *	करो not set a deauth frame
 */
काष्ठा cfg80211_deauth_request अणु
	स्थिर u8 *bssid;
	स्थिर u8 *ie;
	माप_प्रकार ie_len;
	u16 reason_code;
	bool local_state_change;
पूर्ण;

/**
 * काष्ठा cfg80211_disassoc_request - Disassociation request data
 *
 * This काष्ठाure provides inक्रमmation needed to complete IEEE 802.11
 * disassociation.
 *
 * @bss: the BSS to disassociate from
 * @ie: Extra IEs to add to Disassociation frame or %शून्य
 * @ie_len: Length of ie buffer in octets
 * @reason_code: The reason code क्रम the disassociation
 * @local_state_change: This is a request क्रम a local state only, i.e., no
 *	Disassociation frame is to be transmitted.
 */
काष्ठा cfg80211_disassoc_request अणु
	काष्ठा cfg80211_bss *bss;
	स्थिर u8 *ie;
	माप_प्रकार ie_len;
	u16 reason_code;
	bool local_state_change;
पूर्ण;

/**
 * काष्ठा cfg80211_ibss_params - IBSS parameters
 *
 * This काष्ठाure defines the IBSS parameters क्रम the join_ibss()
 * method.
 *
 * @ssid: The SSID, will always be non-null.
 * @ssid_len: The length of the SSID, will always be non-zero.
 * @bssid: Fixed BSSID requested, maybe be %शून्य, अगर set करो not
 *	search क्रम IBSSs with a dअगरferent BSSID.
 * @chandef: defines the channel to use अगर no other IBSS to join can be found
 * @channel_fixed: The channel should be fixed -- करो not search क्रम
 *	IBSSs to join on other channels.
 * @ie: inक्रमmation element(s) to include in the beacon
 * @ie_len: length of that
 * @beacon_पूर्णांकerval: beacon पूर्णांकerval to use
 * @privacy: this is a रक्षित network, keys will be configured
 *	after joining
 * @control_port: whether user space controls IEEE 802.1X port, i.e.,
 *	sets/clears %NL80211_STA_FLAG_AUTHORIZED. If true, the driver is
 *	required to assume that the port is unauthorized until authorized by
 *	user space. Otherwise, port is marked authorized by शेष.
 * @control_port_over_nl80211: TRUE अगर userspace expects to exchange control
 *	port frames over NL80211 instead of the network पूर्णांकerface.
 * @userspace_handles_dfs: whether user space controls DFS operation, i.e.
 *	changes the channel when a radar is detected. This is required
 *	to operate on DFS channels.
 * @basic_rates: biपंचांगap of basic rates to use when creating the IBSS
 * @mcast_rate: per-band multicast rate index + 1 (0: disabled)
 * @ht_capa:  HT Capabilities over-rides.  Values set in ht_capa_mask
 *	will be used in ht_capa.  Un-supported values will be ignored.
 * @ht_capa_mask:  The bits of ht_capa which are to be used.
 * @wep_keys: अटल WEP keys, अगर not शून्य poपूर्णांकs to an array of
 *	CFG80211_MAX_WEP_KEYS WEP keys
 * @wep_tx_key: key index (0..3) of the शेष TX अटल WEP key
 */
काष्ठा cfg80211_ibss_params अणु
	स्थिर u8 *ssid;
	स्थिर u8 *bssid;
	काष्ठा cfg80211_chan_def chandef;
	स्थिर u8 *ie;
	u8 ssid_len, ie_len;
	u16 beacon_पूर्णांकerval;
	u32 basic_rates;
	bool channel_fixed;
	bool privacy;
	bool control_port;
	bool control_port_over_nl80211;
	bool userspace_handles_dfs;
	पूर्णांक mcast_rate[NUM_NL80211_BANDS];
	काष्ठा ieee80211_ht_cap ht_capa;
	काष्ठा ieee80211_ht_cap ht_capa_mask;
	काष्ठा key_params *wep_keys;
	पूर्णांक wep_tx_key;
पूर्ण;

/**
 * काष्ठा cfg80211_bss_selection - connection parameters क्रम BSS selection.
 *
 * @behaviour: requested BSS selection behaviour.
 * @param: parameters क्रम requestion behaviour.
 * @band_pref: preferred band क्रम %NL80211_BSS_SELECT_ATTR_BAND_PREF.
 * @adjust: parameters क्रम %NL80211_BSS_SELECT_ATTR_RSSI_ADJUST.
 */
काष्ठा cfg80211_bss_selection अणु
	क्रमागत nl80211_bss_select_attr behaviour;
	जोड़ अणु
		क्रमागत nl80211_band band_pref;
		काष्ठा cfg80211_bss_select_adjust adjust;
	पूर्ण param;
पूर्ण;

/**
 * काष्ठा cfg80211_connect_params - Connection parameters
 *
 * This काष्ठाure provides inक्रमmation needed to complete IEEE 802.11
 * authentication and association.
 *
 * @channel: The channel to use or %शून्य अगर not specअगरied (स्वतः-select based
 *	on scan results)
 * @channel_hपूर्णांक: The channel of the recommended BSS क्रम initial connection or
 *	%शून्य अगर not specअगरied
 * @bssid: The AP BSSID or %शून्य अगर not specअगरied (स्वतः-select based on scan
 *	results)
 * @bssid_hपूर्णांक: The recommended AP BSSID क्रम initial connection to the BSS or
 *	%शून्य अगर not specअगरied. Unlike the @bssid parameter, the driver is
 *	allowed to ignore this @bssid_hपूर्णांक अगर it has knowledge of a better BSS
 *	to use.
 * @ssid: SSID
 * @ssid_len: Length of ssid in octets
 * @auth_type: Authentication type (algorithm)
 * @ie: IEs क्रम association request
 * @ie_len: Length of assoc_ie in octets
 * @privacy: indicates whether privacy-enabled APs should be used
 * @mfp: indicate whether management frame protection is used
 * @crypto: crypto settings
 * @key_len: length of WEP key क्रम shared key authentication
 * @key_idx: index of WEP key क्रम shared key authentication
 * @key: WEP key क्रम shared key authentication
 * @flags:  See &क्रमागत cfg80211_assoc_req_flags
 * @bg_scan_period:  Background scan period in seconds
 *	or -1 to indicate that शेष value is to be used.
 * @ht_capa:  HT Capabilities over-rides.  Values set in ht_capa_mask
 *	will be used in ht_capa.  Un-supported values will be ignored.
 * @ht_capa_mask:  The bits of ht_capa which are to be used.
 * @vht_capa:  VHT Capability overrides
 * @vht_capa_mask: The bits of vht_capa which are to be used.
 * @pbss: अगर set, connect to a PCP instead of AP. Valid क्रम DMG
 *	networks.
 * @bss_select: criteria to be used क्रम BSS selection.
 * @prev_bssid: previous BSSID, अगर not %शून्य use reassociate frame. This is used
 *	to indicate a request to reassociate within the ESS instead of a request
 *	करो the initial association with the ESS. When included, this is set to
 *	the BSSID of the current association, i.e., to the value that is
 *	included in the Current AP address field of the Reassociation Request
 *	frame.
 * @fils_erp_username: EAP re-authentication protocol (ERP) username part of the
 *	NAI or %शून्य अगर not specअगरied. This is used to स्थिरruct FILS wrapped
 *	data IE.
 * @fils_erp_username_len: Length of @fils_erp_username in octets.
 * @fils_erp_realm: EAP re-authentication protocol (ERP) realm part of NAI or
 *	%शून्य अगर not specअगरied. This specअगरies the करोमुख्य name of ER server and
 *	is used to स्थिरruct FILS wrapped data IE.
 * @fils_erp_realm_len: Length of @fils_erp_realm in octets.
 * @fils_erp_next_seq_num: The next sequence number to use in the FILS ERP
 *	messages. This is also used to स्थिरruct FILS wrapped data IE.
 * @fils_erp_rrk: ERP re-authentication Root Key (rRK) used to derive additional
 *	keys in FILS or %शून्य अगर not specअगरied.
 * @fils_erp_rrk_len: Length of @fils_erp_rrk in octets.
 * @want_1x: indicates user-space supports and wants to use 802.1X driver
 *	offload of 4-way handshake.
 * @edmg: define the EDMG channels.
 *	This may specअगरy multiple channels and bonding options क्रम the driver
 *	to choose from, based on BSS configuration.
 */
काष्ठा cfg80211_connect_params अणु
	काष्ठा ieee80211_channel *channel;
	काष्ठा ieee80211_channel *channel_hपूर्णांक;
	स्थिर u8 *bssid;
	स्थिर u8 *bssid_hपूर्णांक;
	स्थिर u8 *ssid;
	माप_प्रकार ssid_len;
	क्रमागत nl80211_auth_type auth_type;
	स्थिर u8 *ie;
	माप_प्रकार ie_len;
	bool privacy;
	क्रमागत nl80211_mfp mfp;
	काष्ठा cfg80211_crypto_settings crypto;
	स्थिर u8 *key;
	u8 key_len, key_idx;
	u32 flags;
	पूर्णांक bg_scan_period;
	काष्ठा ieee80211_ht_cap ht_capa;
	काष्ठा ieee80211_ht_cap ht_capa_mask;
	काष्ठा ieee80211_vht_cap vht_capa;
	काष्ठा ieee80211_vht_cap vht_capa_mask;
	bool pbss;
	काष्ठा cfg80211_bss_selection bss_select;
	स्थिर u8 *prev_bssid;
	स्थिर u8 *fils_erp_username;
	माप_प्रकार fils_erp_username_len;
	स्थिर u8 *fils_erp_realm;
	माप_प्रकार fils_erp_realm_len;
	u16 fils_erp_next_seq_num;
	स्थिर u8 *fils_erp_rrk;
	माप_प्रकार fils_erp_rrk_len;
	bool want_1x;
	काष्ठा ieee80211_edmg edmg;
पूर्ण;

/**
 * क्रमागत cfg80211_connect_params_changed - Connection parameters being updated
 *
 * This क्रमागत provides inक्रमmation of all connect parameters that
 * have to be updated as part of update_connect_params() call.
 *
 * @UPDATE_ASSOC_IES: Indicates whether association request IEs are updated
 * @UPDATE_FILS_ERP_INFO: Indicates that FILS connection parameters (realm,
 *	username, erp sequence number and rrk) are updated
 * @UPDATE_AUTH_TYPE: Indicates that authentication type is updated
 */
क्रमागत cfg80211_connect_params_changed अणु
	UPDATE_ASSOC_IES		= BIT(0),
	UPDATE_FILS_ERP_INFO		= BIT(1),
	UPDATE_AUTH_TYPE		= BIT(2),
पूर्ण;

/**
 * क्रमागत wiphy_params_flags - set_wiphy_params bitfield values
 * @WIPHY_PARAM_RETRY_SHORT: wiphy->retry_लघु has changed
 * @WIPHY_PARAM_RETRY_LONG: wiphy->retry_दीर्घ has changed
 * @WIPHY_PARAM_FRAG_THRESHOLD: wiphy->frag_threshold has changed
 * @WIPHY_PARAM_RTS_THRESHOLD: wiphy->rts_threshold has changed
 * @WIPHY_PARAM_COVERAGE_CLASS: coverage class changed
 * @WIPHY_PARAM_DYN_ACK: dynack has been enabled
 * @WIPHY_PARAM_TXQ_LIMIT: TXQ packet limit has been changed
 * @WIPHY_PARAM_TXQ_MEMORY_LIMIT: TXQ memory limit has been changed
 * @WIPHY_PARAM_TXQ_QUANTUM: TXQ scheduler quantum
 */
क्रमागत wiphy_params_flags अणु
	WIPHY_PARAM_RETRY_SHORT		= 1 << 0,
	WIPHY_PARAM_RETRY_LONG		= 1 << 1,
	WIPHY_PARAM_FRAG_THRESHOLD	= 1 << 2,
	WIPHY_PARAM_RTS_THRESHOLD	= 1 << 3,
	WIPHY_PARAM_COVERAGE_CLASS	= 1 << 4,
	WIPHY_PARAM_DYN_ACK		= 1 << 5,
	WIPHY_PARAM_TXQ_LIMIT		= 1 << 6,
	WIPHY_PARAM_TXQ_MEMORY_LIMIT	= 1 << 7,
	WIPHY_PARAM_TXQ_QUANTUM		= 1 << 8,
पूर्ण;

#घोषणा IEEE80211_DEFAULT_AIRTIME_WEIGHT	256

/* The per TXQ device queue limit in airसमय */
#घोषणा IEEE80211_DEFAULT_AQL_TXQ_LIMIT_L	5000
#घोषणा IEEE80211_DEFAULT_AQL_TXQ_LIMIT_H	12000

/* The per पूर्णांकerface airसमय threshold to चयन to lower queue limit */
#घोषणा IEEE80211_AQL_THRESHOLD			24000

/**
 * काष्ठा cfg80211_pmksa - PMK Security Association
 *
 * This काष्ठाure is passed to the set/del_pmksa() method क्रम PMKSA
 * caching.
 *
 * @bssid: The AP's BSSID (may be %शून्य).
 * @pmkid: The identअगरier to refer a PMKSA.
 * @pmk: The PMK क्रम the PMKSA identअगरied by @pmkid. This is used क्रम key
 *	derivation by a FILS STA. Otherwise, %शून्य.
 * @pmk_len: Length of the @pmk. The length of @pmk can dअगरfer depending on
 *	the hash algorithm used to generate this.
 * @ssid: SSID to specअगरy the ESS within which a PMKSA is valid when using FILS
 *	cache identअगरier (may be %शून्य).
 * @ssid_len: Length of the @ssid in octets.
 * @cache_id: 2-octet cache identअगरier advertized by a FILS AP identअगरying the
 *	scope of PMKSA. This is valid only अगर @ssid_len is non-zero (may be
 *	%शून्य).
 * @pmk_lअगरeसमय: Maximum lअगरeसमय क्रम PMKSA in seconds
 *	(करोt11RSNAConfigPMKLअगरeसमय) or 0 अगर not specअगरied.
 *	The configured PMKSA must not be used क्रम PMKSA caching after
 *	expiration and any keys derived from this PMK become invalid on
 *	expiration, i.e., the current association must be dropped अगर the PMK
 *	used क्रम it expires.
 * @pmk_reauth_threshold: Threshold समय क्रम reauthentication (percentage of
 *	PMK lअगरeसमय, करोt11RSNAConfigPMKReauthThreshold) or 0 अगर not specअगरied.
 *	Drivers are expected to trigger a full authentication instead of using
 *	this PMKSA क्रम caching when reassociating to a new BSS after this
 *	threshold to generate a new PMK beक्रमe the current one expires.
 */
काष्ठा cfg80211_pmksa अणु
	स्थिर u8 *bssid;
	स्थिर u8 *pmkid;
	स्थिर u8 *pmk;
	माप_प्रकार pmk_len;
	स्थिर u8 *ssid;
	माप_प्रकार ssid_len;
	स्थिर u8 *cache_id;
	u32 pmk_lअगरeसमय;
	u8 pmk_reauth_threshold;
पूर्ण;

/**
 * काष्ठा cfg80211_pkt_pattern - packet pattern
 * @mask: biपंचांगask where to match pattern and where to ignore bytes,
 *	one bit per byte, in same क्रमmat as nl80211
 * @pattern: bytes to match where biपंचांगask is 1
 * @pattern_len: length of pattern (in bytes)
 * @pkt_offset: packet offset (in bytes)
 *
 * Internal note: @mask and @pattern are allocated in one chunk of
 * memory, मुक्त @mask only!
 */
काष्ठा cfg80211_pkt_pattern अणु
	स्थिर u8 *mask, *pattern;
	पूर्णांक pattern_len;
	पूर्णांक pkt_offset;
पूर्ण;

/**
 * काष्ठा cfg80211_wowlan_tcp - TCP connection parameters
 *
 * @sock: (पूर्णांकernal) socket क्रम source port allocation
 * @src: source IP address
 * @dst: destination IP address
 * @dst_mac: destination MAC address
 * @src_port: source port
 * @dst_port: destination port
 * @payload_len: data payload length
 * @payload: data payload buffer
 * @payload_seq: payload sequence stamping configuration
 * @data_पूर्णांकerval: पूर्णांकerval at which to send data packets
 * @wake_len: wakeup payload match length
 * @wake_data: wakeup payload match data
 * @wake_mask: wakeup payload match mask
 * @tokens_size: length of the tokens buffer
 * @payload_tok: payload token usage configuration
 */
काष्ठा cfg80211_wowlan_tcp अणु
	काष्ठा socket *sock;
	__be32 src, dst;
	u16 src_port, dst_port;
	u8 dst_mac[ETH_ALEN];
	पूर्णांक payload_len;
	स्थिर u8 *payload;
	काष्ठा nl80211_wowlan_tcp_data_seq payload_seq;
	u32 data_पूर्णांकerval;
	u32 wake_len;
	स्थिर u8 *wake_data, *wake_mask;
	u32 tokens_size;
	/* must be last, variable member */
	काष्ठा nl80211_wowlan_tcp_data_token payload_tok;
पूर्ण;

/**
 * काष्ठा cfg80211_wowlan - Wake on Wireless-LAN support info
 *
 * This काष्ठाure defines the enabled WoWLAN triggers क्रम the device.
 * @any: wake up on any activity -- special trigger अगर device जारीs
 *	operating as normal during suspend
 * @disconnect: wake up अगर getting disconnected
 * @magic_pkt: wake up on receiving magic packet
 * @patterns: wake up on receiving packet matching a pattern
 * @n_patterns: number of patterns
 * @gtk_rekey_failure: wake up on GTK rekey failure
 * @eap_identity_req: wake up on EAP identity request packet
 * @four_way_handshake: wake up on 4-way handshake
 * @rfसमाप्त_release: wake up when rfसमाप्त is released
 * @tcp: TCP connection establishment/wakeup parameters, see nl80211.h.
 *	शून्य अगर not configured.
 * @nd_config: configuration क्रम the scan to be used क्रम net detect wake.
 */
काष्ठा cfg80211_wowlan अणु
	bool any, disconnect, magic_pkt, gtk_rekey_failure,
	     eap_identity_req, four_way_handshake,
	     rfसमाप्त_release;
	काष्ठा cfg80211_pkt_pattern *patterns;
	काष्ठा cfg80211_wowlan_tcp *tcp;
	पूर्णांक n_patterns;
	काष्ठा cfg80211_sched_scan_request *nd_config;
पूर्ण;

/**
 * काष्ठा cfg80211_coalesce_rules - Coalesce rule parameters
 *
 * This काष्ठाure defines coalesce rule क्रम the device.
 * @delay: maximum coalescing delay in msecs.
 * @condition: condition क्रम packet coalescence.
 *	see &क्रमागत nl80211_coalesce_condition.
 * @patterns: array of packet patterns
 * @n_patterns: number of patterns
 */
काष्ठा cfg80211_coalesce_rules अणु
	पूर्णांक delay;
	क्रमागत nl80211_coalesce_condition condition;
	काष्ठा cfg80211_pkt_pattern *patterns;
	पूर्णांक n_patterns;
पूर्ण;

/**
 * काष्ठा cfg80211_coalesce - Packet coalescing settings
 *
 * This काष्ठाure defines coalescing settings.
 * @rules: array of coalesce rules
 * @n_rules: number of rules
 */
काष्ठा cfg80211_coalesce अणु
	काष्ठा cfg80211_coalesce_rules *rules;
	पूर्णांक n_rules;
पूर्ण;

/**
 * काष्ठा cfg80211_wowlan_nd_match - inक्रमmation about the match
 *
 * @ssid: SSID of the match that triggered the wake up
 * @n_channels: Number of channels where the match occurred.  This
 *	value may be zero अगर the driver can't report the channels.
 * @channels: center frequencies of the channels where a match
 *	occurred (in MHz)
 */
काष्ठा cfg80211_wowlan_nd_match अणु
	काष्ठा cfg80211_ssid ssid;
	पूर्णांक n_channels;
	u32 channels[];
पूर्ण;

/**
 * काष्ठा cfg80211_wowlan_nd_info - net detect wake up inक्रमmation
 *
 * @n_matches: Number of match inक्रमmation instances provided in
 *	@matches.  This value may be zero अगर the driver can't provide
 *	match inक्रमmation.
 * @matches: Array of poपूर्णांकers to matches containing inक्रमmation about
 *	the matches that triggered the wake up.
 */
काष्ठा cfg80211_wowlan_nd_info अणु
	पूर्णांक n_matches;
	काष्ठा cfg80211_wowlan_nd_match *matches[];
पूर्ण;

/**
 * काष्ठा cfg80211_wowlan_wakeup - wakeup report
 * @disconnect: woke up by getting disconnected
 * @magic_pkt: woke up by receiving magic packet
 * @gtk_rekey_failure: woke up by GTK rekey failure
 * @eap_identity_req: woke up by EAP identity request packet
 * @four_way_handshake: woke up by 4-way handshake
 * @rfसमाप्त_release: woke up by rfसमाप्त being released
 * @pattern_idx: pattern that caused wakeup, -1 अगर not due to pattern
 * @packet_present_len: copied wakeup packet data
 * @packet_len: original wakeup packet length
 * @packet: The packet causing the wakeup, अगर any.
 * @packet_80211:  For pattern match, magic packet and other data
 *	frame triggers an 802.3 frame should be reported, क्रम
 *	disconnect due to deauth 802.11 frame. This indicates which
 *	it is.
 * @tcp_match: TCP wakeup packet received
 * @tcp_connlost: TCP connection lost or failed to establish
 * @tcp_nomoretokens: TCP data ran out of tokens
 * @net_detect: अगर not %शून्य, woke up because of net detect
 */
काष्ठा cfg80211_wowlan_wakeup अणु
	bool disconnect, magic_pkt, gtk_rekey_failure,
	     eap_identity_req, four_way_handshake,
	     rfसमाप्त_release, packet_80211,
	     tcp_match, tcp_connlost, tcp_nomoretokens;
	s32 pattern_idx;
	u32 packet_present_len, packet_len;
	स्थिर व्योम *packet;
	काष्ठा cfg80211_wowlan_nd_info *net_detect;
पूर्ण;

/**
 * काष्ठा cfg80211_gtk_rekey_data - rekey data
 * @kek: key encryption key (@kek_len bytes)
 * @kck: key confirmation key (@kck_len bytes)
 * @replay_ctr: replay counter (NL80211_REPLAY_CTR_LEN bytes)
 * @kek_len: length of kek
 * @kck_len length of kck
 * @akm: akm (oui, id)
 */
काष्ठा cfg80211_gtk_rekey_data अणु
	स्थिर u8 *kek, *kck, *replay_ctr;
	u32 akm;
	u8 kek_len, kck_len;
पूर्ण;

/**
 * काष्ठा cfg80211_update_ft_ies_params - FT IE Inक्रमmation
 *
 * This काष्ठाure provides inक्रमmation needed to update the fast transition IE
 *
 * @md: The Mobility Doमुख्य ID, 2 Octet value
 * @ie: Fast Transition IEs
 * @ie_len: Length of ft_ie in octets
 */
काष्ठा cfg80211_update_ft_ies_params अणु
	u16 md;
	स्थिर u8 *ie;
	माप_प्रकार ie_len;
पूर्ण;

/**
 * काष्ठा cfg80211_mgmt_tx_params - mgmt tx parameters
 *
 * This काष्ठाure provides inक्रमmation needed to transmit a mgmt frame
 *
 * @chan: channel to use
 * @offchan: indicates wether off channel operation is required
 * @रुको: duration क्रम ROC
 * @buf: buffer to transmit
 * @len: buffer length
 * @no_cck: करोn't use cck rates क्रम this frame
 * @करोnt_रुको_क्रम_ack: tells the low level not to रुको क्रम an ack
 * @n_csa_offsets: length of csa_offsets array
 * @csa_offsets: array of all the csa offsets in the frame
 */
काष्ठा cfg80211_mgmt_tx_params अणु
	काष्ठा ieee80211_channel *chan;
	bool offchan;
	अचिन्हित पूर्णांक रुको;
	स्थिर u8 *buf;
	माप_प्रकार len;
	bool no_cck;
	bool करोnt_रुको_क्रम_ack;
	पूर्णांक n_csa_offsets;
	स्थिर u16 *csa_offsets;
पूर्ण;

/**
 * काष्ठा cfg80211_dscp_exception - DSCP exception
 *
 * @dscp: DSCP value that करोes not adhere to the user priority range definition
 * @up: user priority value to which the corresponding DSCP value beदीर्घs
 */
काष्ठा cfg80211_dscp_exception अणु
	u8 dscp;
	u8 up;
पूर्ण;

/**
 * काष्ठा cfg80211_dscp_range - DSCP range definition क्रम user priority
 *
 * @low: lowest DSCP value of this user priority range, inclusive
 * @high: highest DSCP value of this user priority range, inclusive
 */
काष्ठा cfg80211_dscp_range अणु
	u8 low;
	u8 high;
पूर्ण;

/* QoS Map Set element length defined in IEEE Std 802.11-2012, 8.4.2.97 */
#घोषणा IEEE80211_QOS_MAP_MAX_EX	21
#घोषणा IEEE80211_QOS_MAP_LEN_MIN	16
#घोषणा IEEE80211_QOS_MAP_LEN_MAX \
	(IEEE80211_QOS_MAP_LEN_MIN + 2 * IEEE80211_QOS_MAP_MAX_EX)

/**
 * काष्ठा cfg80211_qos_map - QoS Map Inक्रमmation
 *
 * This काष्ठा defines the Interworking QoS map setting क्रम DSCP values
 *
 * @num_des: number of DSCP exceptions (0..21)
 * @dscp_exception: optionally up to maximum of 21 DSCP exceptions from
 *	the user priority DSCP range definition
 * @up: DSCP range definition क्रम a particular user priority
 */
काष्ठा cfg80211_qos_map अणु
	u8 num_des;
	काष्ठा cfg80211_dscp_exception dscp_exception[IEEE80211_QOS_MAP_MAX_EX];
	काष्ठा cfg80211_dscp_range up[8];
पूर्ण;

/**
 * काष्ठा cfg80211_nan_conf - न_अंक configuration
 *
 * This काष्ठा defines न_अंक configuration parameters
 *
 * @master_pref: master preference (1 - 255)
 * @bands: operating bands, a biपंचांगap of &क्रमागत nl80211_band values.
 *	For instance, क्रम NL80211_BAND_2GHZ, bit 0 would be set
 *	(i.e. BIT(NL80211_BAND_2GHZ)).
 */
काष्ठा cfg80211_nan_conf अणु
	u8 master_pref;
	u8 bands;
पूर्ण;

/**
 * क्रमागत cfg80211_nan_conf_changes - indicates changed fields in न_अंक
 * configuration
 *
 * @CFG80211_न_अंक_CONF_CHANGED_PREF: master preference
 * @CFG80211_न_अंक_CONF_CHANGED_BANDS: operating bands
 */
क्रमागत cfg80211_nan_conf_changes अणु
	CFG80211_न_अंक_CONF_CHANGED_PREF = BIT(0),
	CFG80211_न_अंक_CONF_CHANGED_BANDS = BIT(1),
पूर्ण;

/**
 * काष्ठा cfg80211_nan_func_filter - a न_अंक function Rx / Tx filter
 *
 * @filter: the content of the filter
 * @len: the length of the filter
 */
काष्ठा cfg80211_nan_func_filter अणु
	स्थिर u8 *filter;
	u8 len;
पूर्ण;

/**
 * काष्ठा cfg80211_nan_func - a न_अंक function
 *
 * @type: &क्रमागत nl80211_nan_function_type
 * @service_id: the service ID of the function
 * @publish_type: &nl80211_nan_publish_type
 * @बंद_range: अगर true, the range should be limited. Threshold is
 *	implementation specअगरic.
 * @publish_bcast: अगर true, the solicited publish should be broadcasted
 * @subscribe_active: अगर true, the subscribe is active
 * @followup_id: the instance ID क्रम follow up
 * @followup_reqid: the requestor instance ID क्रम follow up
 * @followup_dest: MAC address of the recipient of the follow up
 * @ttl: समय to live counter in DW.
 * @serv_spec_info: Service Specअगरic Info
 * @serv_spec_info_len: Service Specअगरic Info length
 * @srf_include: अगर true, SRF is inclusive
 * @srf_bf: Bloom Filter
 * @srf_bf_len: Bloom Filter length
 * @srf_bf_idx: Bloom Filter index
 * @srf_macs: SRF MAC addresses
 * @srf_num_macs: number of MAC addresses in SRF
 * @rx_filters: rx filters that are matched with corresponding peer's tx_filter
 * @tx_filters: filters that should be transmitted in the SDF.
 * @num_rx_filters: length of &rx_filters.
 * @num_tx_filters: length of &tx_filters.
 * @instance_id: driver allocated id of the function.
 * @cookie: unique न_अंक function identअगरier.
 */
काष्ठा cfg80211_nan_func अणु
	क्रमागत nl80211_nan_function_type type;
	u8 service_id[NL80211_न_अंक_FUNC_SERVICE_ID_LEN];
	u8 publish_type;
	bool बंद_range;
	bool publish_bcast;
	bool subscribe_active;
	u8 followup_id;
	u8 followup_reqid;
	काष्ठा mac_address followup_dest;
	u32 ttl;
	स्थिर u8 *serv_spec_info;
	u8 serv_spec_info_len;
	bool srf_include;
	स्थिर u8 *srf_bf;
	u8 srf_bf_len;
	u8 srf_bf_idx;
	काष्ठा mac_address *srf_macs;
	पूर्णांक srf_num_macs;
	काष्ठा cfg80211_nan_func_filter *rx_filters;
	काष्ठा cfg80211_nan_func_filter *tx_filters;
	u8 num_tx_filters;
	u8 num_rx_filters;
	u8 instance_id;
	u64 cookie;
पूर्ण;

/**
 * काष्ठा cfg80211_pmk_conf - PMK configuration
 *
 * @aa: authenticator address
 * @pmk_len: PMK length in bytes.
 * @pmk: the PMK material
 * @pmk_r0_name: PMK-R0 Name. शून्य अगर not applicable (i.e., the PMK
 *	is not PMK-R0). When pmk_r0_name is not शून्य, the pmk field
 *	holds PMK-R0.
 */
काष्ठा cfg80211_pmk_conf अणु
	स्थिर u8 *aa;
	u8 pmk_len;
	स्थिर u8 *pmk;
	स्थिर u8 *pmk_r0_name;
पूर्ण;

/**
 * काष्ठा cfg80211_बाह्यal_auth_params - Trigger External authentication.
 *
 * Commonly used across the बाह्यal auth request and event पूर्णांकerfaces.
 *
 * @action: action type / trigger क्रम बाह्यal authentication. Only signअगरicant
 *	क्रम the authentication request event पूर्णांकerface (driver to user space).
 * @bssid: BSSID of the peer with which the authentication has
 *	to happen. Used by both the authentication request event and
 *	authentication response command पूर्णांकerface.
 * @ssid: SSID of the AP.  Used by both the authentication request event and
 *	authentication response command पूर्णांकerface.
 * @key_mgmt_suite: AKM suite of the respective authentication. Used by the
 *	authentication request event पूर्णांकerface.
 * @status: status code, %WLAN_STATUS_SUCCESS क्रम successful authentication,
 *	use %WLAN_STATUS_UNSPECIFIED_FAILURE अगर user space cannot give you
 *	the real status code क्रम failures. Used only क्रम the authentication
 *	response command पूर्णांकerface (user space to driver).
 * @pmkid: The identअगरier to refer a PMKSA.
 */
काष्ठा cfg80211_बाह्यal_auth_params अणु
	क्रमागत nl80211_बाह्यal_auth_action action;
	u8 bssid[ETH_ALEN] __aligned(2);
	काष्ठा cfg80211_ssid ssid;
	अचिन्हित पूर्णांक key_mgmt_suite;
	u16 status;
	स्थिर u8 *pmkid;
पूर्ण;

/**
 * काष्ठा cfg80211_fपंचांग_responder_stats - FTM responder statistics
 *
 * @filled: bitflag of flags using the bits of &क्रमागत nl80211_fपंचांग_stats to
 *	indicate the relevant values in this काष्ठा क्रम them
 * @success_num: number of FTM sessions in which all frames were successfully
 *	answered
 * @partial_num: number of FTM sessions in which part of frames were
 *	successfully answered
 * @failed_num: number of failed FTM sessions
 * @asap_num: number of ASAP FTM sessions
 * @non_asap_num: number of  non-ASAP FTM sessions
 * @total_duration_ms: total sessions durations - gives an indication
 *	of how much समय the responder was busy
 * @unknown_triggers_num: number of unknown FTM triggers - triggers from
 *	initiators that didn't finish successfully the negotiation phase with
 *	the responder
 * @reschedule_requests_num: number of FTM reschedule requests - initiator asks
 *	क्रम a new scheduling although it alपढ़ोy has scheduled FTM slot
 * @out_of_winकरोw_triggers_num: total FTM triggers out of scheduled winकरोw
 */
काष्ठा cfg80211_fपंचांग_responder_stats अणु
	u32 filled;
	u32 success_num;
	u32 partial_num;
	u32 failed_num;
	u32 asap_num;
	u32 non_asap_num;
	u64 total_duration_ms;
	u32 unknown_triggers_num;
	u32 reschedule_requests_num;
	u32 out_of_winकरोw_triggers_num;
पूर्ण;

/**
 * काष्ठा cfg80211_pmsr_fपंचांग_result - FTM result
 * @failure_reason: अगर this measurement failed (PMSR status is
 *	%NL80211_PMSR_STATUS_FAILURE), this gives a more precise
 *	reason than just "failure"
 * @burst_index: अगर reporting partial results, this is the index
 *	in [0 .. num_bursts-1] of the burst that's being reported
 * @num_fपंचांगr_attempts: number of FTM request frames transmitted
 * @num_fपंचांगr_successes: number of FTM request frames acked
 * @busy_retry_समय: अगर failure_reason is %NL80211_PMSR_FTM_FAILURE_PEER_BUSY,
 *	fill this to indicate in how many seconds a retry is deemed possible
 *	by the responder
 * @num_bursts_exp: actual number of bursts exponent negotiated
 * @burst_duration: actual burst duration negotiated
 * @fपंचांगs_per_burst: actual FTMs per burst negotiated
 * @lci_len: length of LCI inक्रमmation (अगर present)
 * @civicloc_len: length of civic location inक्रमmation (अगर present)
 * @lci: LCI data (may be %शून्य)
 * @civicloc: civic location data (may be %शून्य)
 * @rssi_avg: average RSSI over FTM action frames reported
 * @rssi_spपढ़ो: spपढ़ो of the RSSI over FTM action frames reported
 * @tx_rate: bitrate क्रम transmitted FTM action frame response
 * @rx_rate: bitrate of received FTM action frame
 * @rtt_avg: average of RTTs measured (must have either this or @dist_avg)
 * @rtt_variance: variance of RTTs measured (note that standard deviation is
 *	the square root of the variance)
 * @rtt_spपढ़ो: spपढ़ो of the RTTs measured
 * @dist_avg: average of distances (mm) measured
 *	(must have either this or @rtt_avg)
 * @dist_variance: variance of distances measured (see also @rtt_variance)
 * @dist_spपढ़ो: spपढ़ो of distances measured (see also @rtt_spपढ़ो)
 * @num_fपंचांगr_attempts_valid: @num_fपंचांगr_attempts is valid
 * @num_fपंचांगr_successes_valid: @num_fपंचांगr_successes is valid
 * @rssi_avg_valid: @rssi_avg is valid
 * @rssi_spपढ़ो_valid: @rssi_spपढ़ो is valid
 * @tx_rate_valid: @tx_rate is valid
 * @rx_rate_valid: @rx_rate is valid
 * @rtt_avg_valid: @rtt_avg is valid
 * @rtt_variance_valid: @rtt_variance is valid
 * @rtt_spपढ़ो_valid: @rtt_spपढ़ो is valid
 * @dist_avg_valid: @dist_avg is valid
 * @dist_variance_valid: @dist_variance is valid
 * @dist_spपढ़ो_valid: @dist_spपढ़ो is valid
 */
काष्ठा cfg80211_pmsr_fपंचांग_result अणु
	स्थिर u8 *lci;
	स्थिर u8 *civicloc;
	अचिन्हित पूर्णांक lci_len;
	अचिन्हित पूर्णांक civicloc_len;
	क्रमागत nl80211_peer_measurement_fपंचांग_failure_reasons failure_reason;
	u32 num_fपंचांगr_attempts, num_fपंचांगr_successes;
	s16 burst_index;
	u8 busy_retry_समय;
	u8 num_bursts_exp;
	u8 burst_duration;
	u8 fपंचांगs_per_burst;
	s32 rssi_avg;
	s32 rssi_spपढ़ो;
	काष्ठा rate_info tx_rate, rx_rate;
	s64 rtt_avg;
	s64 rtt_variance;
	s64 rtt_spपढ़ो;
	s64 dist_avg;
	s64 dist_variance;
	s64 dist_spपढ़ो;

	u16 num_fपंचांगr_attempts_valid:1,
	    num_fपंचांगr_successes_valid:1,
	    rssi_avg_valid:1,
	    rssi_spपढ़ो_valid:1,
	    tx_rate_valid:1,
	    rx_rate_valid:1,
	    rtt_avg_valid:1,
	    rtt_variance_valid:1,
	    rtt_spपढ़ो_valid:1,
	    dist_avg_valid:1,
	    dist_variance_valid:1,
	    dist_spपढ़ो_valid:1;
पूर्ण;

/**
 * काष्ठा cfg80211_pmsr_result - peer measurement result
 * @addr: address of the peer
 * @host_समय: host समय (use kसमय_get_bootसमय() adjust to the समय when the
 *	measurement was made)
 * @ap_tsf: AP's TSF at measurement समय
 * @status: status of the measurement
 * @final: अगर reporting partial results, mark this as the last one; अगर not
 *	reporting partial results always set this flag
 * @ap_tsf_valid: indicates the @ap_tsf value is valid
 * @type: type of the measurement reported, note that we only support reporting
 *	one type at a समय, but you can report multiple results separately and
 *	they're all aggregated क्रम userspace.
 */
काष्ठा cfg80211_pmsr_result अणु
	u64 host_समय, ap_tsf;
	क्रमागत nl80211_peer_measurement_status status;

	u8 addr[ETH_ALEN];

	u8 final:1,
	   ap_tsf_valid:1;

	क्रमागत nl80211_peer_measurement_type type;

	जोड़ अणु
		काष्ठा cfg80211_pmsr_fपंचांग_result fपंचांग;
	पूर्ण;
पूर्ण;

/**
 * काष्ठा cfg80211_pmsr_fपंचांग_request_peer - FTM request data
 * @requested: indicates FTM is requested
 * @preamble: frame preamble to use
 * @burst_period: burst period to use
 * @asap: indicates to use ASAP mode
 * @num_bursts_exp: number of bursts exponent
 * @burst_duration: burst duration
 * @fपंचांगs_per_burst: number of FTMs per burst
 * @fपंचांगr_retries: number of retries क्रम FTM request
 * @request_lci: request LCI inक्रमmation
 * @request_civicloc: request civic location inक्रमmation
 * @trigger_based: use trigger based ranging क्रम the measurement
 *		 If neither @trigger_based nor @non_trigger_based is set,
 *		 EDCA based ranging will be used.
 * @non_trigger_based: use non trigger based ranging क्रम the measurement
 *		 If neither @trigger_based nor @non_trigger_based is set,
 *		 EDCA based ranging will be used.
 * @lmr_feedback: negotiate क्रम I2R LMR feedback. Only valid अगर either
 *	@trigger_based or @non_trigger_based is set.
 *
 * See also nl80211 क्रम the respective attribute करोcumentation.
 */
काष्ठा cfg80211_pmsr_fपंचांग_request_peer अणु
	क्रमागत nl80211_preamble preamble;
	u16 burst_period;
	u8 requested:1,
	   asap:1,
	   request_lci:1,
	   request_civicloc:1,
	   trigger_based:1,
	   non_trigger_based:1,
	   lmr_feedback:1;
	u8 num_bursts_exp;
	u8 burst_duration;
	u8 fपंचांगs_per_burst;
	u8 fपंचांगr_retries;
पूर्ण;

/**
 * काष्ठा cfg80211_pmsr_request_peer - peer data क्रम a peer measurement request
 * @addr: MAC address
 * @chandef: channel to use
 * @report_ap_tsf: report the associated AP's TSF
 * @fपंचांग: FTM data, see &काष्ठा cfg80211_pmsr_fपंचांग_request_peer
 */
काष्ठा cfg80211_pmsr_request_peer अणु
	u8 addr[ETH_ALEN];
	काष्ठा cfg80211_chan_def chandef;
	u8 report_ap_tsf:1;
	काष्ठा cfg80211_pmsr_fपंचांग_request_peer fपंचांग;
पूर्ण;

/**
 * काष्ठा cfg80211_pmsr_request - peer measurement request
 * @cookie: cookie, set by cfg80211
 * @nl_portid: netlink portid - used by cfg80211
 * @drv_data: driver data क्रम this request, अगर required क्रम पातing,
 *	not otherwise मुक्तd or anything by cfg80211
 * @mac_addr: MAC address used क्रम (अक्रमomised) request
 * @mac_addr_mask: MAC address mask used क्रम अक्रमomisation, bits that
 *	are 0 in the mask should be अक्रमomised, bits that are 1 should
 *	be taken from the @mac_addr
 * @list: used by cfg80211 to hold on to the request
 * @समयout: समयout (in milliseconds) क्रम the whole operation, अगर
 *	zero it means there's no समयout
 * @n_peers: number of peers to करो measurements with
 * @peers: per-peer measurement request data
 */
काष्ठा cfg80211_pmsr_request अणु
	u64 cookie;
	व्योम *drv_data;
	u32 n_peers;
	u32 nl_portid;

	u32 समयout;

	u8 mac_addr[ETH_ALEN] __aligned(2);
	u8 mac_addr_mask[ETH_ALEN] __aligned(2);

	काष्ठा list_head list;

	काष्ठा cfg80211_pmsr_request_peer peers[];
पूर्ण;

/**
 * काष्ठा cfg80211_update_owe_info - OWE Inक्रमmation
 *
 * This काष्ठाure provides inक्रमmation needed क्रम the drivers to offload OWE
 * (Opportunistic Wireless Encryption) processing to the user space.
 *
 * Commonly used across update_owe_info request and event पूर्णांकerfaces.
 *
 * @peer: MAC address of the peer device क्रम which the OWE processing
 *	has to be करोne.
 * @status: status code, %WLAN_STATUS_SUCCESS क्रम successful OWE info
 *	processing, use %WLAN_STATUS_UNSPECIFIED_FAILURE अगर user space
 *	cannot give you the real status code क्रम failures. Used only क्रम
 *	OWE update request command पूर्णांकerface (user space to driver).
 * @ie: IEs obtained from the peer or स्थिरructed by the user space. These are
 *	the IEs of the remote peer in the event from the host driver and
 *	the स्थिरructed IEs by the user space in the request पूर्णांकerface.
 * @ie_len: Length of IEs in octets.
 */
काष्ठा cfg80211_update_owe_info अणु
	u8 peer[ETH_ALEN] __aligned(2);
	u16 status;
	स्थिर u8 *ie;
	माप_प्रकार ie_len;
पूर्ण;

/**
 * काष्ठा mgmt_frame_regs - management frame registrations data
 * @global_stypes: biपंचांगap of management frame subtypes रेजिस्टरed
 *	क्रम the entire device
 * @पूर्णांकerface_stypes: biपंचांगap of management frame subtypes रेजिस्टरed
 *	क्रम the given पूर्णांकerface
 * @global_mcast_rx: mcast RX is needed globally क्रम these subtypes
 * @पूर्णांकerface_mcast_stypes: mcast RX is needed on this पूर्णांकerface
 *	क्रम these subtypes
 */
काष्ठा mgmt_frame_regs अणु
	u32 global_stypes, पूर्णांकerface_stypes;
	u32 global_mcast_stypes, पूर्णांकerface_mcast_stypes;
पूर्ण;

/**
 * काष्ठा cfg80211_ops - backend description क्रम wireless configuration
 *
 * This काष्ठा is रेजिस्टरed by fullmac card drivers and/or wireless stacks
 * in order to handle configuration requests on their पूर्णांकerfaces.
 *
 * All callbacks except where otherwise noted should वापस 0
 * on success or a negative error code.
 *
 * All operations are invoked with the wiphy mutex held. The RTNL may be
 * held in addition (due to wireless extensions) but this cannot be relied
 * upon except in हालs where करोcumented below. Note that due to ordering,
 * the RTNL also cannot be acquired in any handlers.
 *
 * @suspend: wiphy device needs to be suspended. The variable @wow will
 *	be %शून्य or contain the enabled Wake-on-Wireless triggers that are
 *	configured क्रम the device.
 * @resume: wiphy device needs to be resumed
 * @set_wakeup: Called when WoWLAN is enabled/disabled, use this callback
 *	to call device_set_wakeup_enable() to enable/disable wakeup from
 *	the device.
 *
 * @add_भव_पूर्णांकf: create a new भव पूर्णांकerface with the given name,
 *	must set the काष्ठा wireless_dev's अगरtype. Beware: You must create
 *	the new netdev in the wiphy's network namespace! Returns the काष्ठा
 *	wireless_dev, or an ERR_PTR. For P2P device wdevs, the driver must
 *	also set the address member in the wdev.
 *	This additionally holds the RTNL to be able to करो netdev changes.
 *
 * @del_भव_पूर्णांकf: हटाओ the भव पूर्णांकerface
 *	This additionally holds the RTNL to be able to करो netdev changes.
 *
 * @change_भव_पूर्णांकf: change type/configuration of भव पूर्णांकerface,
 *	keep the काष्ठा wireless_dev's अगरtype updated.
 *	This additionally holds the RTNL to be able to करो netdev changes.
 *
 * @add_key: add a key with the given parameters. @mac_addr will be %शून्य
 *	when adding a group key.
 *
 * @get_key: get inक्रमmation about the key with the given parameters.
 *	@mac_addr will be %शून्य when requesting inक्रमmation क्रम a group
 *	key. All poपूर्णांकers given to the @callback function need not be valid
 *	after it वापसs. This function should वापस an error अगर it is
 *	not possible to retrieve the key, -ENOENT अगर it करोesn't exist.
 *
 * @del_key: हटाओ a key given the @mac_addr (%शून्य क्रम a group key)
 *	and @key_index, वापस -ENOENT अगर the key करोesn't exist.
 *
 * @set_शेष_key: set the शेष key on an पूर्णांकerface
 *
 * @set_शेष_mgmt_key: set the शेष management frame key on an पूर्णांकerface
 *
 * @set_शेष_beacon_key: set the शेष Beacon frame key on an पूर्णांकerface
 *
 * @set_rekey_data: give the data necessary क्रम GTK rekeying to the driver
 *
 * @start_ap: Start acting in AP mode defined by the parameters.
 * @change_beacon: Change the beacon parameters क्रम an access poपूर्णांक mode
 *	पूर्णांकerface. This should reject the call when AP mode wasn't started.
 * @stop_ap: Stop being an AP, including stopping beaconing.
 *
 * @add_station: Add a new station.
 * @del_station: Remove a station
 * @change_station: Modअगरy a given station. Note that flags changes are not much
 *	validated in cfg80211, in particular the auth/assoc/authorized flags
 *	might come to the driver in invalid combinations -- make sure to check
 *	them, also against the existing state! Drivers must call
 *	cfg80211_check_station_change() to validate the inक्रमmation.
 * @get_station: get station inक्रमmation क्रम the station identअगरied by @mac
 * @dump_station: dump station callback -- resume dump at index @idx
 *
 * @add_mpath: add a fixed mesh path
 * @del_mpath: delete a given mesh path
 * @change_mpath: change a given mesh path
 * @get_mpath: get a mesh path क्रम the given parameters
 * @dump_mpath: dump mesh path callback -- resume dump at index @idx
 * @get_mpp: get a mesh proxy path क्रम the given parameters
 * @dump_mpp: dump mesh proxy path callback -- resume dump at index @idx
 * @join_mesh: join the mesh network with the specअगरied parameters
 *	(invoked with the wireless_dev mutex held)
 * @leave_mesh: leave the current mesh network
 *	(invoked with the wireless_dev mutex held)
 *
 * @get_mesh_config: Get the current mesh configuration
 *
 * @update_mesh_config: Update mesh parameters on a running mesh.
 *	The mask is a bitfield which tells us which parameters to
 *	set, and which to leave alone.
 *
 * @change_bss: Modअगरy parameters क्रम a given BSS.
 *
 * @set_txq_params: Set TX queue parameters
 *
 * @libertas_set_mesh_channel: Only क्रम backward compatibility क्रम libertas,
 *	as it करोesn't implement join_mesh and needs to set the channel to
 *	join the mesh instead.
 *
 * @set_monitor_channel: Set the monitor mode channel क्रम the device. If other
 *	पूर्णांकerfaces are active this callback should reject the configuration.
 *	If no पूर्णांकerfaces are active or the device is करोwn, the channel should
 *	be stored क्रम when a monitor पूर्णांकerface becomes active.
 *
 * @scan: Request to करो a scan. If वापसing zero, the scan request is given
 *	the driver, and will be valid until passed to cfg80211_scan_करोne().
 *	For scan results, call cfg80211_inक्रमm_bss(); you can call this outside
 *	the scan/scan_करोne bracket too.
 * @पात_scan: Tell the driver to पात an ongoing scan. The driver shall
 *	indicate the status of the scan through cfg80211_scan_करोne().
 *
 * @auth: Request to authenticate with the specअगरied peer
 *	(invoked with the wireless_dev mutex held)
 * @assoc: Request to (re)associate with the specअगरied peer
 *	(invoked with the wireless_dev mutex held)
 * @deauth: Request to deauthenticate from the specअगरied peer
 *	(invoked with the wireless_dev mutex held)
 * @disassoc: Request to disassociate from the specअगरied peer
 *	(invoked with the wireless_dev mutex held)
 *
 * @connect: Connect to the ESS with the specअगरied parameters. When connected,
 *	call cfg80211_connect_result()/cfg80211_connect_bss() with status code
 *	%WLAN_STATUS_SUCCESS. If the connection fails क्रम some reason, call
 *	cfg80211_connect_result()/cfg80211_connect_bss() with the status code
 *	from the AP or cfg80211_connect_समयout() अगर no frame with status code
 *	was received.
 *	The driver is allowed to roam to other BSSes within the ESS when the
 *	other BSS matches the connect parameters. When such roaming is initiated
 *	by the driver, the driver is expected to verअगरy that the target matches
 *	the configured security parameters and to use Reassociation Request
 *	frame instead of Association Request frame.
 *	The connect function can also be used to request the driver to perक्रमm a
 *	specअगरic roam when connected to an ESS. In that हाल, the prev_bssid
 *	parameter is set to the BSSID of the currently associated BSS as an
 *	indication of requesting reassociation.
 *	In both the driver-initiated and new connect() call initiated roaming
 *	हालs, the result of roaming is indicated with a call to
 *	cfg80211_roamed(). (invoked with the wireless_dev mutex held)
 * @update_connect_params: Update the connect parameters जबतक connected to a
 *	BSS. The updated parameters can be used by driver/firmware क्रम
 *	subsequent BSS selection (roaming) decisions and to क्रमm the
 *	Authentication/(Re)Association Request frames. This call करोes not
 *	request an immediate disassociation or reassociation with the current
 *	BSS, i.e., this impacts only subsequent (re)associations. The bits in
 *	changed are defined in &क्रमागत cfg80211_connect_params_changed.
 *	(invoked with the wireless_dev mutex held)
 * @disconnect: Disconnect from the BSS/ESS or stop connection attempts अगर
 *      connection is in progress. Once करोne, call cfg80211_disconnected() in
 *      हाल connection was alपढ़ोy established (invoked with the
 *      wireless_dev mutex held), otherwise call cfg80211_connect_समयout().
 *
 * @join_ibss: Join the specअगरied IBSS (or create अगर necessary). Once करोne, call
 *	cfg80211_ibss_joined(), also call that function when changing BSSID due
 *	to a merge.
 *	(invoked with the wireless_dev mutex held)
 * @leave_ibss: Leave the IBSS.
 *	(invoked with the wireless_dev mutex held)
 *
 * @set_mcast_rate: Set the specअगरied multicast rate (only अगर vअगर is in ADHOC or
 *	MESH mode)
 *
 * @set_wiphy_params: Notअगरy that wiphy parameters have changed;
 *	@changed bitfield (see &क्रमागत wiphy_params_flags) describes which values
 *	have changed. The actual parameter values are available in
 *	काष्ठा wiphy. If वापसing an error, no value should be changed.
 *
 * @set_tx_घातer: set the transmit घातer according to the parameters,
 *	the घातer passed is in mBm, to get dBm use MBM_TO_DBM(). The
 *	wdev may be %शून्य अगर घातer was set क्रम the wiphy, and will
 *	always be %शून्य unless the driver supports per-vअगर TX घातer
 *	(as advertised by the nl80211 feature flag.)
 * @get_tx_घातer: store the current TX घातer पूर्णांकo the dbm variable;
 *	वापस 0 अगर successful
 *
 * @rfसमाप्त_poll: polls the hw rfसमाप्त line, use cfg80211 reporting
 *	functions to adjust rfसमाप्त hw state
 *
 * @dump_survey: get site survey inक्रमmation.
 *
 * @reमुख्य_on_channel: Request the driver to reमुख्य awake on the specअगरied
 *	channel क्रम the specअगरied duration to complete an off-channel
 *	operation (e.g., खुला action frame exchange). When the driver is
 *	पढ़ोy on the requested channel, it must indicate this with an event
 *	notअगरication by calling cfg80211_पढ़ोy_on_channel().
 * @cancel_reमुख्य_on_channel: Cancel an on-going reमुख्य-on-channel operation.
 *	This allows the operation to be terminated prior to समयout based on
 *	the duration value.
 * @mgmt_tx: Transmit a management frame.
 * @mgmt_tx_cancel_रुको: Cancel the रुको समय from transmitting a management
 *	frame on another channel
 *
 * @tesपंचांगode_cmd: run a test mode command; @wdev may be %शून्य
 * @tesपंचांगode_dump: Implement a test mode dump. The cb->args[2] and up may be
 *	used by the function, but 0 and 1 must not be touched. Additionally,
 *	वापस error codes other than -ENOBUFS and -ENOENT will terminate the
 *	dump and वापस to userspace with an error, so be careful. If any data
 *	was passed in from userspace then the data/len arguments will be present
 *	and poपूर्णांक to the data contained in %NL80211_ATTR_TESTDATA.
 *
 * @set_bitrate_mask: set the bitrate mask configuration
 *
 * @set_pmksa: Cache a PMKID क्रम a BSSID. This is mostly useful क्रम fullmac
 *	devices running firmwares capable of generating the (re) association
 *	RSN IE. It allows क्रम faster roaming between WPA2 BSSIDs.
 * @del_pmksa: Delete a cached PMKID.
 * @flush_pmksa: Flush all cached PMKIDs.
 * @set_घातer_mgmt: Configure WLAN घातer management. A समयout value of -1
 *	allows the driver to adjust the dynamic ps समयout value.
 * @set_cqm_rssi_config: Configure connection quality monitor RSSI threshold.
 *	After configuration, the driver should (soon) send an event indicating
 *	the current level is above/below the configured threshold; this may
 *	need some care when the configuration is changed (without first being
 *	disabled.)
 * @set_cqm_rssi_range_config: Configure two RSSI thresholds in the
 *	connection quality monitor.  An event is to be sent only when the
 *	संकेत level is found to be outside the two values.  The driver should
 *	set %NL80211_EXT_FEATURE_CQM_RSSI_LIST अगर this method is implemented.
 *	If it is provided then there's no poपूर्णांक providing @set_cqm_rssi_config.
 * @set_cqm_txe_config: Configure connection quality monitor TX error
 *	thresholds.
 * @sched_scan_start: Tell the driver to start a scheduled scan.
 * @sched_scan_stop: Tell the driver to stop an ongoing scheduled scan with
 *	given request id. This call must stop the scheduled scan and be पढ़ोy
 *	क्रम starting a new one beक्रमe it वापसs, i.e. @sched_scan_start may be
 *	called immediately after that again and should not fail in that हाल.
 *	The driver should not call cfg80211_sched_scan_stopped() क्रम a requested
 *	stop (when this method वापसs 0).
 *
 * @update_mgmt_frame_registrations: Notअगरy the driver that management frame
 *	registrations were updated. The callback is allowed to sleep.
 *
 * @set_antenna: Set antenna configuration (tx_ant, rx_ant) on the device.
 *	Parameters are biपंचांगaps of allowed antennas to use क्रम TX/RX. Drivers may
 *	reject TX/RX mask combinations they cannot support by वापसing -EINVAL
 *	(also see nl80211.h @NL80211_ATTR_WIPHY_ANTENNA_TX).
 *
 * @get_antenna: Get current antenna configuration from device (tx_ant, rx_ant).
 *
 * @tdls_mgmt: Transmit a TDLS management frame.
 * @tdls_oper: Perक्रमm a high-level TDLS operation (e.g. TDLS link setup).
 *
 * @probe_client: probe an associated client, must वापस a cookie that it
 *	later passes to cfg80211_probe_status().
 *
 * @set_noack_map: Set the NoAck Map क्रम the TIDs.
 *
 * @get_channel: Get the current operating channel क्रम the भव पूर्णांकerface.
 *	For monitor पूर्णांकerfaces, it should वापस %शून्य unless there's a single
 *	current monitoring channel.
 *
 * @start_p2p_device: Start the given P2P device.
 * @stop_p2p_device: Stop the given P2P device.
 *
 * @set_mac_acl: Sets MAC address control list in AP and P2P GO mode.
 *	Parameters include ACL policy, an array of MAC address of stations
 *	and the number of MAC addresses. If there is alपढ़ोy a list in driver
 *	this new list replaces the existing one. Driver has to clear its ACL
 *	when number of MAC addresses entries is passed as 0. Drivers which
 *	advertise the support क्रम MAC based ACL have to implement this callback.
 *
 * @start_radar_detection: Start radar detection in the driver.
 *
 * @end_cac: End running CAC, probably because a related CAC
 *	was finished on another phy.
 *
 * @update_ft_ies: Provide updated Fast BSS Transition inक्रमmation to the
 *	driver. If the SME is in the driver/firmware, this inक्रमmation can be
 *	used in building Authentication and Reassociation Request frames.
 *
 * @crit_proto_start: Indicates a critical protocol needs more link reliability
 *	क्रम a given duration (milliseconds). The protocol is provided so the
 *	driver can take the most appropriate actions.
 * @crit_proto_stop: Indicates critical protocol no दीर्घer needs increased link
 *	reliability. This operation can not fail.
 * @set_coalesce: Set coalesce parameters.
 *
 * @channel_चयन: initiate channel-चयन procedure (with CSA). Driver is
 *	responsible क्रम veryfing अगर the चयन is possible. Since this is
 *	inherently tricky driver may decide to disconnect an पूर्णांकerface later
 *	with cfg80211_stop_अगरace(). This करोesn't mean driver can accept
 *	everything. It should करो it's best to verअगरy requests and reject them
 *	as soon as possible.
 *
 * @set_qos_map: Set QoS mapping inक्रमmation to the driver
 *
 * @set_ap_chanwidth: Set the AP (including P2P GO) mode channel width क्रम the
 *	given पूर्णांकerface This is used e.g. क्रम dynamic HT 20/40 MHz channel width
 *	changes during the lअगरeसमय of the BSS.
 *
 * @add_tx_ts: validate (अगर admitted_समय is 0) or add a TX TS to the device
 *	with the given parameters; action frame exchange has been handled by
 *	userspace so this just has to modअगरy the TX path to take the TS पूर्णांकo
 *	account.
 *	If the admitted समय is 0 just validate the parameters to make sure
 *	the session can be created at all; it is valid to just always वापस
 *	success क्रम that but that may result in inefficient behaviour (handshake
 *	with the peer followed by immediate tearकरोwn when the addition is later
 *	rejected)
 * @del_tx_ts: हटाओ an existing TX TS
 *
 * @join_ocb: join the OCB network with the specअगरied parameters
 *	(invoked with the wireless_dev mutex held)
 * @leave_ocb: leave the current OCB network
 *	(invoked with the wireless_dev mutex held)
 *
 * @tdls_channel_चयन: Start channel-चयनing with a TDLS peer. The driver
 *	is responsible क्रम continually initiating channel-चयनing operations
 *	and वापसing to the base channel क्रम communication with the AP.
 * @tdls_cancel_channel_चयन: Stop channel-चयनing with a TDLS peer. Both
 *	peers must be on the base channel when the call completes.
 * @start_nan: Start the न_अंक पूर्णांकerface.
 * @stop_nan: Stop the न_अंक पूर्णांकerface.
 * @add_nan_func: Add a न_अंक function. Returns negative value on failure.
 *	On success @nan_func ownership is transferred to the driver and
 *	it may access it outside of the scope of this function. The driver
 *	should मुक्त the @nan_func when no दीर्घer needed by calling
 *	cfg80211_मुक्त_nan_func().
 *	On success the driver should assign an instance_id in the
 *	provided @nan_func.
 * @del_nan_func: Delete a न_अंक function.
 * @nan_change_conf: changes न_अंक configuration. The changed parameters must
 *	be specअगरied in @changes (using &क्रमागत cfg80211_nan_conf_changes);
 *	All other parameters must be ignored.
 *
 * @set_multicast_to_unicast: configure multicast to unicast conversion क्रम BSS
 *
 * @get_txq_stats: Get TXQ stats क्रम पूर्णांकerface or phy. If wdev is %शून्य, this
 *      function should वापस phy stats, and पूर्णांकerface stats otherwise.
 *
 * @set_pmk: configure the PMK to be used क्रम offloaded 802.1X 4-Way handshake.
 *	If not deleted through @del_pmk the PMK reमुख्यs valid until disconnect
 *	upon which the driver should clear it.
 *	(invoked with the wireless_dev mutex held)
 * @del_pmk: delete the previously configured PMK क्रम the given authenticator.
 *	(invoked with the wireless_dev mutex held)
 *
 * @बाह्यal_auth: indicates result of offloaded authentication processing from
 *     user space
 *
 * @tx_control_port: TX a control port frame (EAPoL).  The noencrypt parameter
 *	tells the driver that the frame should not be encrypted.
 *
 * @get_fपंचांग_responder_stats: Retrieve FTM responder statistics, अगर available.
 *	Statistics should be cumulative, currently no way to reset is provided.
 * @start_pmsr: start peer measurement (e.g. FTM)
 * @पात_pmsr: पात peer measurement
 *
 * @update_owe_info: Provide updated OWE info to driver. Driver implementing SME
 *	but offloading OWE processing to the user space will get the updated
 *	DH IE through this पूर्णांकerface.
 *
 * @probe_mesh_link: Probe direct Mesh peer's link quality by sending data frame
 *	and overrule HWMP path selection algorithm.
 * @set_tid_config: TID specअगरic configuration, this can be peer or BSS specअगरic
 *	This callback may sleep.
 * @reset_tid_config: Reset TID specअगरic configuration क्रम the peer, क्रम the
 *	given TIDs. This callback may sleep.
 *
 * @set_sar_specs: Update the SAR (TX घातer) settings.
 */
काष्ठा cfg80211_ops अणु
	पूर्णांक	(*suspend)(काष्ठा wiphy *wiphy, काष्ठा cfg80211_wowlan *wow);
	पूर्णांक	(*resume)(काष्ठा wiphy *wiphy);
	व्योम	(*set_wakeup)(काष्ठा wiphy *wiphy, bool enabled);

	काष्ठा wireless_dev * (*add_भव_पूर्णांकf)(काष्ठा wiphy *wiphy,
						  स्थिर अक्षर *name,
						  अचिन्हित अक्षर name_assign_type,
						  क्रमागत nl80211_अगरtype type,
						  काष्ठा vअगर_params *params);
	पूर्णांक	(*del_भव_पूर्णांकf)(काष्ठा wiphy *wiphy,
				    काष्ठा wireless_dev *wdev);
	पूर्णांक	(*change_भव_पूर्णांकf)(काष्ठा wiphy *wiphy,
				       काष्ठा net_device *dev,
				       क्रमागत nl80211_अगरtype type,
				       काष्ठा vअगर_params *params);

	पूर्णांक	(*add_key)(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
			   u8 key_index, bool pairwise, स्थिर u8 *mac_addr,
			   काष्ठा key_params *params);
	पूर्णांक	(*get_key)(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
			   u8 key_index, bool pairwise, स्थिर u8 *mac_addr,
			   व्योम *cookie,
			   व्योम (*callback)(व्योम *cookie, काष्ठा key_params*));
	पूर्णांक	(*del_key)(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
			   u8 key_index, bool pairwise, स्थिर u8 *mac_addr);
	पूर्णांक	(*set_शेष_key)(काष्ठा wiphy *wiphy,
				   काष्ठा net_device *netdev,
				   u8 key_index, bool unicast, bool multicast);
	पूर्णांक	(*set_शेष_mgmt_key)(काष्ठा wiphy *wiphy,
					काष्ठा net_device *netdev,
					u8 key_index);
	पूर्णांक	(*set_शेष_beacon_key)(काष्ठा wiphy *wiphy,
					  काष्ठा net_device *netdev,
					  u8 key_index);

	पूर्णांक	(*start_ap)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			    काष्ठा cfg80211_ap_settings *settings);
	पूर्णांक	(*change_beacon)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				 काष्ठा cfg80211_beacon_data *info);
	पूर्णांक	(*stop_ap)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev);


	पूर्णांक	(*add_station)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			       स्थिर u8 *mac,
			       काष्ठा station_parameters *params);
	पूर्णांक	(*del_station)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			       काष्ठा station_del_parameters *params);
	पूर्णांक	(*change_station)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				  स्थिर u8 *mac,
				  काष्ठा station_parameters *params);
	पूर्णांक	(*get_station)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			       स्थिर u8 *mac, काष्ठा station_info *sinfo);
	पूर्णांक	(*dump_station)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				पूर्णांक idx, u8 *mac, काष्ठा station_info *sinfo);

	पूर्णांक	(*add_mpath)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			       स्थिर u8 *dst, स्थिर u8 *next_hop);
	पूर्णांक	(*del_mpath)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			       स्थिर u8 *dst);
	पूर्णांक	(*change_mpath)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				  स्थिर u8 *dst, स्थिर u8 *next_hop);
	पूर्णांक	(*get_mpath)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			     u8 *dst, u8 *next_hop, काष्ठा mpath_info *pinfo);
	पूर्णांक	(*dump_mpath)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			      पूर्णांक idx, u8 *dst, u8 *next_hop,
			      काष्ठा mpath_info *pinfo);
	पूर्णांक	(*get_mpp)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			   u8 *dst, u8 *mpp, काष्ठा mpath_info *pinfo);
	पूर्णांक	(*dump_mpp)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			    पूर्णांक idx, u8 *dst, u8 *mpp,
			    काष्ठा mpath_info *pinfo);
	पूर्णांक	(*get_mesh_config)(काष्ठा wiphy *wiphy,
				काष्ठा net_device *dev,
				काष्ठा mesh_config *conf);
	पूर्णांक	(*update_mesh_config)(काष्ठा wiphy *wiphy,
				      काष्ठा net_device *dev, u32 mask,
				      स्थिर काष्ठा mesh_config *nconf);
	पूर्णांक	(*join_mesh)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			     स्थिर काष्ठा mesh_config *conf,
			     स्थिर काष्ठा mesh_setup *setup);
	पूर्णांक	(*leave_mesh)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev);

	पूर्णांक	(*join_ocb)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			    काष्ठा ocb_setup *setup);
	पूर्णांक	(*leave_ocb)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev);

	पूर्णांक	(*change_bss)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			      काष्ठा bss_parameters *params);

	पूर्णांक	(*set_txq_params)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				  काष्ठा ieee80211_txq_params *params);

	पूर्णांक	(*libertas_set_mesh_channel)(काष्ठा wiphy *wiphy,
					     काष्ठा net_device *dev,
					     काष्ठा ieee80211_channel *chan);

	पूर्णांक	(*set_monitor_channel)(काष्ठा wiphy *wiphy,
				       काष्ठा cfg80211_chan_def *chandef);

	पूर्णांक	(*scan)(काष्ठा wiphy *wiphy,
			काष्ठा cfg80211_scan_request *request);
	व्योम	(*पात_scan)(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev);

	पूर्णांक	(*auth)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			काष्ठा cfg80211_auth_request *req);
	पूर्णांक	(*assoc)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			 काष्ठा cfg80211_assoc_request *req);
	पूर्णांक	(*deauth)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			  काष्ठा cfg80211_deauth_request *req);
	पूर्णांक	(*disassoc)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			    काष्ठा cfg80211_disassoc_request *req);

	पूर्णांक	(*connect)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			   काष्ठा cfg80211_connect_params *sme);
	पूर्णांक	(*update_connect_params)(काष्ठा wiphy *wiphy,
					 काष्ठा net_device *dev,
					 काष्ठा cfg80211_connect_params *sme,
					 u32 changed);
	पूर्णांक	(*disconnect)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			      u16 reason_code);

	पूर्णांक	(*join_ibss)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			     काष्ठा cfg80211_ibss_params *params);
	पूर्णांक	(*leave_ibss)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev);

	पूर्णांक	(*set_mcast_rate)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				  पूर्णांक rate[NUM_NL80211_BANDS]);

	पूर्णांक	(*set_wiphy_params)(काष्ठा wiphy *wiphy, u32 changed);

	पूर्णांक	(*set_tx_घातer)(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
				क्रमागत nl80211_tx_घातer_setting type, पूर्णांक mbm);
	पूर्णांक	(*get_tx_घातer)(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
				पूर्णांक *dbm);

	व्योम	(*rfसमाप्त_poll)(काष्ठा wiphy *wiphy);

#अगर_घोषित CONFIG_NL80211_TESTMODE
	पूर्णांक	(*tesपंचांगode_cmd)(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
				व्योम *data, पूर्णांक len);
	पूर्णांक	(*tesपंचांगode_dump)(काष्ठा wiphy *wiphy, काष्ठा sk_buff *skb,
				 काष्ठा netlink_callback *cb,
				 व्योम *data, पूर्णांक len);
#पूर्ण_अगर

	पूर्णांक	(*set_bitrate_mask)(काष्ठा wiphy *wiphy,
				    काष्ठा net_device *dev,
				    स्थिर u8 *peer,
				    स्थिर काष्ठा cfg80211_bitrate_mask *mask);

	पूर्णांक	(*dump_survey)(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
			पूर्णांक idx, काष्ठा survey_info *info);

	पूर्णांक	(*set_pmksa)(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
			     काष्ठा cfg80211_pmksa *pmksa);
	पूर्णांक	(*del_pmksa)(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
			     काष्ठा cfg80211_pmksa *pmksa);
	पूर्णांक	(*flush_pmksa)(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev);

	पूर्णांक	(*reमुख्य_on_channel)(काष्ठा wiphy *wiphy,
				     काष्ठा wireless_dev *wdev,
				     काष्ठा ieee80211_channel *chan,
				     अचिन्हित पूर्णांक duration,
				     u64 *cookie);
	पूर्णांक	(*cancel_reमुख्य_on_channel)(काष्ठा wiphy *wiphy,
					    काष्ठा wireless_dev *wdev,
					    u64 cookie);

	पूर्णांक	(*mgmt_tx)(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
			   काष्ठा cfg80211_mgmt_tx_params *params,
			   u64 *cookie);
	पूर्णांक	(*mgmt_tx_cancel_रुको)(काष्ठा wiphy *wiphy,
				       काष्ठा wireless_dev *wdev,
				       u64 cookie);

	पूर्णांक	(*set_घातer_mgmt)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				  bool enabled, पूर्णांक समयout);

	पूर्णांक	(*set_cqm_rssi_config)(काष्ठा wiphy *wiphy,
				       काष्ठा net_device *dev,
				       s32 rssi_thold, u32 rssi_hyst);

	पूर्णांक	(*set_cqm_rssi_range_config)(काष्ठा wiphy *wiphy,
					     काष्ठा net_device *dev,
					     s32 rssi_low, s32 rssi_high);

	पूर्णांक	(*set_cqm_txe_config)(काष्ठा wiphy *wiphy,
				      काष्ठा net_device *dev,
				      u32 rate, u32 pkts, u32 पूर्णांकvl);

	व्योम	(*update_mgmt_frame_registrations)(काष्ठा wiphy *wiphy,
						   काष्ठा wireless_dev *wdev,
						   काष्ठा mgmt_frame_regs *upd);

	पूर्णांक	(*set_antenna)(काष्ठा wiphy *wiphy, u32 tx_ant, u32 rx_ant);
	पूर्णांक	(*get_antenna)(काष्ठा wiphy *wiphy, u32 *tx_ant, u32 *rx_ant);

	पूर्णांक	(*sched_scan_start)(काष्ठा wiphy *wiphy,
				काष्ठा net_device *dev,
				काष्ठा cfg80211_sched_scan_request *request);
	पूर्णांक	(*sched_scan_stop)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				   u64 reqid);

	पूर्णांक	(*set_rekey_data)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				  काष्ठा cfg80211_gtk_rekey_data *data);

	पूर्णांक	(*tdls_mgmt)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			     स्थिर u8 *peer, u8 action_code,  u8 dialog_token,
			     u16 status_code, u32 peer_capability,
			     bool initiator, स्थिर u8 *buf, माप_प्रकार len);
	पूर्णांक	(*tdls_oper)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			     स्थिर u8 *peer, क्रमागत nl80211_tdls_operation oper);

	पूर्णांक	(*probe_client)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				स्थिर u8 *peer, u64 *cookie);

	पूर्णांक	(*set_noack_map)(काष्ठा wiphy *wiphy,
				  काष्ठा net_device *dev,
				  u16 noack_map);

	पूर्णांक	(*get_channel)(काष्ठा wiphy *wiphy,
			       काष्ठा wireless_dev *wdev,
			       काष्ठा cfg80211_chan_def *chandef);

	पूर्णांक	(*start_p2p_device)(काष्ठा wiphy *wiphy,
				    काष्ठा wireless_dev *wdev);
	व्योम	(*stop_p2p_device)(काष्ठा wiphy *wiphy,
				   काष्ठा wireless_dev *wdev);

	पूर्णांक	(*set_mac_acl)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			       स्थिर काष्ठा cfg80211_acl_data *params);

	पूर्णांक	(*start_radar_detection)(काष्ठा wiphy *wiphy,
					 काष्ठा net_device *dev,
					 काष्ठा cfg80211_chan_def *chandef,
					 u32 cac_समय_ms);
	व्योम	(*end_cac)(काष्ठा wiphy *wiphy,
				काष्ठा net_device *dev);
	पूर्णांक	(*update_ft_ies)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				 काष्ठा cfg80211_update_ft_ies_params *ftie);
	पूर्णांक	(*crit_proto_start)(काष्ठा wiphy *wiphy,
				    काष्ठा wireless_dev *wdev,
				    क्रमागत nl80211_crit_proto_id protocol,
				    u16 duration);
	व्योम	(*crit_proto_stop)(काष्ठा wiphy *wiphy,
				   काष्ठा wireless_dev *wdev);
	पूर्णांक	(*set_coalesce)(काष्ठा wiphy *wiphy,
				काष्ठा cfg80211_coalesce *coalesce);

	पूर्णांक	(*channel_चयन)(काष्ठा wiphy *wiphy,
				  काष्ठा net_device *dev,
				  काष्ठा cfg80211_csa_settings *params);

	पूर्णांक     (*set_qos_map)(काष्ठा wiphy *wiphy,
			       काष्ठा net_device *dev,
			       काष्ठा cfg80211_qos_map *qos_map);

	पूर्णांक	(*set_ap_chanwidth)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				    काष्ठा cfg80211_chan_def *chandef);

	पूर्णांक	(*add_tx_ts)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			     u8 tsid, स्थिर u8 *peer, u8 user_prio,
			     u16 admitted_समय);
	पूर्णांक	(*del_tx_ts)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			     u8 tsid, स्थिर u8 *peer);

	पूर्णांक	(*tdls_channel_चयन)(काष्ठा wiphy *wiphy,
				       काष्ठा net_device *dev,
				       स्थिर u8 *addr, u8 oper_class,
				       काष्ठा cfg80211_chan_def *chandef);
	व्योम	(*tdls_cancel_channel_चयन)(काष्ठा wiphy *wiphy,
					      काष्ठा net_device *dev,
					      स्थिर u8 *addr);
	पूर्णांक	(*start_nan)(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
			     काष्ठा cfg80211_nan_conf *conf);
	व्योम	(*stop_nan)(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev);
	पूर्णांक	(*add_nan_func)(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
				काष्ठा cfg80211_nan_func *nan_func);
	व्योम	(*del_nan_func)(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
			       u64 cookie);
	पूर्णांक	(*nan_change_conf)(काष्ठा wiphy *wiphy,
				   काष्ठा wireless_dev *wdev,
				   काष्ठा cfg80211_nan_conf *conf,
				   u32 changes);

	पूर्णांक	(*set_multicast_to_unicast)(काष्ठा wiphy *wiphy,
					    काष्ठा net_device *dev,
					    स्थिर bool enabled);

	पूर्णांक	(*get_txq_stats)(काष्ठा wiphy *wiphy,
				 काष्ठा wireless_dev *wdev,
				 काष्ठा cfg80211_txq_stats *txqstats);

	पूर्णांक	(*set_pmk)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			   स्थिर काष्ठा cfg80211_pmk_conf *conf);
	पूर्णांक	(*del_pmk)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			   स्थिर u8 *aa);
	पूर्णांक     (*बाह्यal_auth)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				 काष्ठा cfg80211_बाह्यal_auth_params *params);

	पूर्णांक	(*tx_control_port)(काष्ठा wiphy *wiphy,
				   काष्ठा net_device *dev,
				   स्थिर u8 *buf, माप_प्रकार len,
				   स्थिर u8 *dest, स्थिर __be16 proto,
				   स्थिर bool noencrypt,
				   u64 *cookie);

	पूर्णांक	(*get_fपंचांग_responder_stats)(काष्ठा wiphy *wiphy,
				काष्ठा net_device *dev,
				काष्ठा cfg80211_fपंचांग_responder_stats *fपंचांग_stats);

	पूर्णांक	(*start_pmsr)(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
			      काष्ठा cfg80211_pmsr_request *request);
	व्योम	(*पात_pmsr)(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
			      काष्ठा cfg80211_pmsr_request *request);
	पूर्णांक	(*update_owe_info)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				   काष्ठा cfg80211_update_owe_info *owe_info);
	पूर्णांक	(*probe_mesh_link)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				   स्थिर u8 *buf, माप_प्रकार len);
	पूर्णांक     (*set_tid_config)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				  काष्ठा cfg80211_tid_config *tid_conf);
	पूर्णांक	(*reset_tid_config)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				    स्थिर u8 *peer, u8 tids);
	पूर्णांक	(*set_sar_specs)(काष्ठा wiphy *wiphy,
				 काष्ठा cfg80211_sar_specs *sar);
पूर्ण;

/*
 * wireless hardware and networking पूर्णांकerfaces काष्ठाures
 * and registration/helper functions
 */

/**
 * क्रमागत wiphy_flags - wiphy capability flags
 *
 * @WIPHY_FLAG_SPLIT_SCAN_6GHZ: अगर set to true, the scan request will be split
 *	 पूर्णांकo two, first क्रम legacy bands and second क्रम UHB.
 * @WIPHY_FLAG_NETNS_OK: अगर not set, करो not allow changing the netns of this
 *	wiphy at all
 * @WIPHY_FLAG_PS_ON_BY_DEFAULT: अगर set to true, घातersave will be enabled
 *	by शेष -- this flag will be set depending on the kernel's शेष
 *	on wiphy_new(), but can be changed by the driver अगर it has a good
 *	reason to override the शेष
 * @WIPHY_FLAG_4ADDR_AP: supports 4addr mode even on AP (with a single station
 *	on a VLAN पूर्णांकerface). This flag also serves an extra purpose of
 *	supporting 4ADDR AP mode on devices which करो not support AP/VLAN अगरtype.
 * @WIPHY_FLAG_4ADDR_STATION: supports 4addr mode even as a station
 * @WIPHY_FLAG_CONTROL_PORT_PROTOCOL: This device supports setting the
 *	control port protocol ethertype. The device also honours the
 *	control_port_no_encrypt flag.
 * @WIPHY_FLAG_IBSS_RSN: The device supports IBSS RSN.
 * @WIPHY_FLAG_MESH_AUTH: The device supports mesh authentication by routing
 *	auth frames to userspace. See @NL80211_MESH_SETUP_USERSPACE_AUTH.
 * @WIPHY_FLAG_SUPPORTS_FW_ROAM: The device supports roaming feature in the
 *	firmware.
 * @WIPHY_FLAG_AP_UAPSD: The device supports uapsd on AP.
 * @WIPHY_FLAG_SUPPORTS_TDLS: The device supports TDLS (802.11z) operation.
 * @WIPHY_FLAG_TDLS_EXTERNAL_SETUP: The device करोes not handle TDLS (802.11z)
 *	link setup/discovery operations पूर्णांकernally. Setup, discovery and
 *	tearकरोwn packets should be sent through the @NL80211_CMD_TDLS_MGMT
 *	command. When this flag is not set, @NL80211_CMD_TDLS_OPER should be
 *	used क्रम asking the driver/firmware to perक्रमm a TDLS operation.
 * @WIPHY_FLAG_HAVE_AP_SME: device पूर्णांकegrates AP SME
 * @WIPHY_FLAG_REPORTS_OBSS: the device will report beacons from other BSSes
 *	when there are भव पूर्णांकerfaces in AP mode by calling
 *	cfg80211_report_obss_beacon().
 * @WIPHY_FLAG_AP_PROBE_RESP_OFFLOAD: When operating as an AP, the device
 *	responds to probe-requests in hardware.
 * @WIPHY_FLAG_OFFCHAN_TX: Device supports direct off-channel TX.
 * @WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL: Device supports reमुख्य-on-channel call.
 * @WIPHY_FLAG_SUPPORTS_5_10_MHZ: Device supports 5 MHz and 10 MHz channels.
 * @WIPHY_FLAG_HAS_CHANNEL_SWITCH: Device supports channel चयन in
 *	beaconing mode (AP, IBSS, Mesh, ...).
 * @WIPHY_FLAG_HAS_STATIC_WEP: The device supports अटल WEP key installation
 *	beक्रमe connection.
 * @WIPHY_FLAG_SUPPORTS_EXT_KEK_KCK: The device supports bigger kek and kck keys
 */
क्रमागत wiphy_flags अणु
	WIPHY_FLAG_SUPPORTS_EXT_KEK_KCK		= BIT(0),
	/* use hole at 1 */
	WIPHY_FLAG_SPLIT_SCAN_6GHZ		= BIT(2),
	WIPHY_FLAG_NETNS_OK			= BIT(3),
	WIPHY_FLAG_PS_ON_BY_DEFAULT		= BIT(4),
	WIPHY_FLAG_4ADDR_AP			= BIT(5),
	WIPHY_FLAG_4ADDR_STATION		= BIT(6),
	WIPHY_FLAG_CONTROL_PORT_PROTOCOL	= BIT(7),
	WIPHY_FLAG_IBSS_RSN			= BIT(8),
	WIPHY_FLAG_MESH_AUTH			= BIT(10),
	/* use hole at 11 */
	/* use hole at 12 */
	WIPHY_FLAG_SUPPORTS_FW_ROAM		= BIT(13),
	WIPHY_FLAG_AP_UAPSD			= BIT(14),
	WIPHY_FLAG_SUPPORTS_TDLS		= BIT(15),
	WIPHY_FLAG_TDLS_EXTERNAL_SETUP		= BIT(16),
	WIPHY_FLAG_HAVE_AP_SME			= BIT(17),
	WIPHY_FLAG_REPORTS_OBSS			= BIT(18),
	WIPHY_FLAG_AP_PROBE_RESP_OFFLOAD	= BIT(19),
	WIPHY_FLAG_OFFCHAN_TX			= BIT(20),
	WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL	= BIT(21),
	WIPHY_FLAG_SUPPORTS_5_10_MHZ		= BIT(22),
	WIPHY_FLAG_HAS_CHANNEL_SWITCH		= BIT(23),
	WIPHY_FLAG_HAS_STATIC_WEP		= BIT(24),
पूर्ण;

/**
 * काष्ठा ieee80211_अगरace_limit - limit on certain पूर्णांकerface types
 * @max: maximum number of पूर्णांकerfaces of these types
 * @types: पूर्णांकerface types (bits)
 */
काष्ठा ieee80211_अगरace_limit अणु
	u16 max;
	u16 types;
पूर्ण;

/**
 * काष्ठा ieee80211_अगरace_combination - possible पूर्णांकerface combination
 *
 * With this काष्ठाure the driver can describe which पूर्णांकerface
 * combinations it supports concurrently.
 *
 * Examples:
 *
 * 1. Allow #STA <= 1, #AP <= 1, matching BI, channels = 1, 2 total:
 *
 *    .. code-block:: c
 *
 *	काष्ठा ieee80211_अगरace_limit limits1[] = अणु
 *		अणु .max = 1, .types = BIT(NL80211_IFTYPE_STATION), पूर्ण,
 *		अणु .max = 1, .types = BIT(NL80211_IFTYPE_APपूर्ण, पूर्ण,
 *	पूर्ण;
 *	काष्ठा ieee80211_अगरace_combination combination1 = अणु
 *		.limits = limits1,
 *		.n_limits = ARRAY_SIZE(limits1),
 *		.max_पूर्णांकerfaces = 2,
 *		.beacon_पूर्णांक_infra_match = true,
 *	पूर्ण;
 *
 *
 * 2. Allow #अणुAP, P2P-GOपूर्ण <= 8, channels = 1, 8 total:
 *
 *    .. code-block:: c
 *
 *	काष्ठा ieee80211_अगरace_limit limits2[] = अणु
 *		अणु .max = 8, .types = BIT(NL80211_IFTYPE_AP) |
 *				     BIT(NL80211_IFTYPE_P2P_GO), पूर्ण,
 *	पूर्ण;
 *	काष्ठा ieee80211_अगरace_combination combination2 = अणु
 *		.limits = limits2,
 *		.n_limits = ARRAY_SIZE(limits2),
 *		.max_पूर्णांकerfaces = 8,
 *		.num_dअगरferent_channels = 1,
 *	पूर्ण;
 *
 *
 * 3. Allow #STA <= 1, #अणुP2P-client,P2P-GOपूर्ण <= 3 on two channels, 4 total.
 *
 *    This allows क्रम an infraकाष्ठाure connection and three P2P connections.
 *
 *    .. code-block:: c
 *
 *	काष्ठा ieee80211_अगरace_limit limits3[] = अणु
 *		अणु .max = 1, .types = BIT(NL80211_IFTYPE_STATION), पूर्ण,
 *		अणु .max = 3, .types = BIT(NL80211_IFTYPE_P2P_GO) |
 *				     BIT(NL80211_IFTYPE_P2P_CLIENT), पूर्ण,
 *	पूर्ण;
 *	काष्ठा ieee80211_अगरace_combination combination3 = अणु
 *		.limits = limits3,
 *		.n_limits = ARRAY_SIZE(limits3),
 *		.max_पूर्णांकerfaces = 4,
 *		.num_dअगरferent_channels = 2,
 *	पूर्ण;
 *
 */
काष्ठा ieee80211_अगरace_combination अणु
	/**
	 * @limits:
	 * limits क्रम the given पूर्णांकerface types
	 */
	स्थिर काष्ठा ieee80211_अगरace_limit *limits;

	/**
	 * @num_dअगरferent_channels:
	 * can use up to this many dअगरferent channels
	 */
	u32 num_dअगरferent_channels;

	/**
	 * @max_पूर्णांकerfaces:
	 * maximum number of पूर्णांकerfaces in total allowed in this group
	 */
	u16 max_पूर्णांकerfaces;

	/**
	 * @n_limits:
	 * number of limitations
	 */
	u8 n_limits;

	/**
	 * @beacon_पूर्णांक_infra_match:
	 * In this combination, the beacon पूर्णांकervals between infraकाष्ठाure
	 * and AP types must match. This is required only in special हालs.
	 */
	bool beacon_पूर्णांक_infra_match;

	/**
	 * @radar_detect_widths:
	 * biपंचांगap of channel widths supported क्रम radar detection
	 */
	u8 radar_detect_widths;

	/**
	 * @radar_detect_regions:
	 * biपंचांगap of regions supported क्रम radar detection
	 */
	u8 radar_detect_regions;

	/**
	 * @beacon_पूर्णांक_min_gcd:
	 * This पूर्णांकerface combination supports dअगरferent beacon पूर्णांकervals.
	 *
	 * = 0
	 *   all beacon पूर्णांकervals क्रम dअगरferent पूर्णांकerface must be same.
	 * > 0
	 *   any beacon पूर्णांकerval क्रम the पूर्णांकerface part of this combination AND
	 *   GCD of all beacon पूर्णांकervals from beaconing पूर्णांकerfaces of this
	 *   combination must be greater or equal to this value.
	 */
	u32 beacon_पूर्णांक_min_gcd;
पूर्ण;

काष्ठा ieee80211_txrx_stypes अणु
	u16 tx, rx;
पूर्ण;

/**
 * क्रमागत wiphy_wowlan_support_flags - WoWLAN support flags
 * @WIPHY_WOWLAN_ANY: supports wakeup क्रम the special "any"
 *	trigger that keeps the device operating as-is and
 *	wakes up the host on any activity, क्रम example a
 *	received packet that passed filtering; note that the
 *	packet should be preserved in that हाल
 * @WIPHY_WOWLAN_MAGIC_PKT: supports wakeup on magic packet
 *	(see nl80211.h)
 * @WIPHY_WOWLAN_DISCONNECT: supports wakeup on disconnect
 * @WIPHY_WOWLAN_SUPPORTS_GTK_REKEY: supports GTK rekeying जबतक asleep
 * @WIPHY_WOWLAN_GTK_REKEY_FAILURE: supports wakeup on GTK rekey failure
 * @WIPHY_WOWLAN_EAP_IDENTITY_REQ: supports wakeup on EAP identity request
 * @WIPHY_WOWLAN_4WAY_HANDSHAKE: supports wakeup on 4-way handshake failure
 * @WIPHY_WOWLAN_RFKILL_RELEASE: supports wakeup on RF-समाप्त release
 * @WIPHY_WOWLAN_NET_DETECT: supports wakeup on network detection
 */
क्रमागत wiphy_wowlan_support_flags अणु
	WIPHY_WOWLAN_ANY		= BIT(0),
	WIPHY_WOWLAN_MAGIC_PKT		= BIT(1),
	WIPHY_WOWLAN_DISCONNECT		= BIT(2),
	WIPHY_WOWLAN_SUPPORTS_GTK_REKEY	= BIT(3),
	WIPHY_WOWLAN_GTK_REKEY_FAILURE	= BIT(4),
	WIPHY_WOWLAN_EAP_IDENTITY_REQ	= BIT(5),
	WIPHY_WOWLAN_4WAY_HANDSHAKE	= BIT(6),
	WIPHY_WOWLAN_RFKILL_RELEASE	= BIT(7),
	WIPHY_WOWLAN_NET_DETECT		= BIT(8),
पूर्ण;

काष्ठा wiphy_wowlan_tcp_support अणु
	स्थिर काष्ठा nl80211_wowlan_tcp_data_token_feature *tok;
	u32 data_payload_max;
	u32 data_पूर्णांकerval_max;
	u32 wake_payload_max;
	bool seq;
पूर्ण;

/**
 * काष्ठा wiphy_wowlan_support - WoWLAN support data
 * @flags: see &क्रमागत wiphy_wowlan_support_flags
 * @n_patterns: number of supported wakeup patterns
 *	(see nl80211.h क्रम the pattern definition)
 * @pattern_max_len: maximum length of each pattern
 * @pattern_min_len: minimum length of each pattern
 * @max_pkt_offset: maximum Rx packet offset
 * @max_nd_match_sets: maximum number of matchsets क्रम net-detect,
 *	similar, but not necessarily identical, to max_match_sets क्रम
 *	scheduled scans.
 *	See &काष्ठा cfg80211_sched_scan_request.@match_sets क्रम more
 *	details.
 * @tcp: TCP wakeup support inक्रमmation
 */
काष्ठा wiphy_wowlan_support अणु
	u32 flags;
	पूर्णांक n_patterns;
	पूर्णांक pattern_max_len;
	पूर्णांक pattern_min_len;
	पूर्णांक max_pkt_offset;
	पूर्णांक max_nd_match_sets;
	स्थिर काष्ठा wiphy_wowlan_tcp_support *tcp;
पूर्ण;

/**
 * काष्ठा wiphy_coalesce_support - coalesce support data
 * @n_rules: maximum number of coalesce rules
 * @max_delay: maximum supported coalescing delay in msecs
 * @n_patterns: number of supported patterns in a rule
 *	(see nl80211.h क्रम the pattern definition)
 * @pattern_max_len: maximum length of each pattern
 * @pattern_min_len: minimum length of each pattern
 * @max_pkt_offset: maximum Rx packet offset
 */
काष्ठा wiphy_coalesce_support अणु
	पूर्णांक n_rules;
	पूर्णांक max_delay;
	पूर्णांक n_patterns;
	पूर्णांक pattern_max_len;
	पूर्णांक pattern_min_len;
	पूर्णांक max_pkt_offset;
पूर्ण;

/**
 * क्रमागत wiphy_venकरोr_command_flags - validation flags क्रम venकरोr commands
 * @WIPHY_VENDOR_CMD_NEED_WDEV: venकरोr command requires wdev
 * @WIPHY_VENDOR_CMD_NEED_NETDEV: venकरोr command requires netdev
 * @WIPHY_VENDOR_CMD_NEED_RUNNING: पूर्णांकerface/wdev must be up & running
 *	(must be combined with %_WDEV or %_NETDEV)
 */
क्रमागत wiphy_venकरोr_command_flags अणु
	WIPHY_VENDOR_CMD_NEED_WDEV = BIT(0),
	WIPHY_VENDOR_CMD_NEED_NETDEV = BIT(1),
	WIPHY_VENDOR_CMD_NEED_RUNNING = BIT(2),
पूर्ण;

/**
 * क्रमागत wiphy_opmode_flag - Station's ht/vht operation mode inक्रमmation flags
 *
 * @STA_OPMODE_MAX_BW_CHANGED: Max Bandwidth changed
 * @STA_OPMODE_SMPS_MODE_CHANGED: SMPS mode changed
 * @STA_OPMODE_N_SS_CHANGED: max N_SS (number of spatial streams) changed
 *
 */
क्रमागत wiphy_opmode_flag अणु
	STA_OPMODE_MAX_BW_CHANGED	= BIT(0),
	STA_OPMODE_SMPS_MODE_CHANGED	= BIT(1),
	STA_OPMODE_N_SS_CHANGED		= BIT(2),
पूर्ण;

/**
 * काष्ठा sta_opmode_info - Station's ht/vht operation mode inक्रमmation
 * @changed: contains value from &क्रमागत wiphy_opmode_flag
 * @smps_mode: New SMPS mode value from &क्रमागत nl80211_smps_mode of a station
 * @bw: new max bandwidth value from &क्रमागत nl80211_chan_width of a station
 * @rx_nss: new rx_nss value of a station
 */

काष्ठा sta_opmode_info अणु
	u32 changed;
	क्रमागत nl80211_smps_mode smps_mode;
	क्रमागत nl80211_chan_width bw;
	u8 rx_nss;
पूर्ण;

#घोषणा VENDOR_CMD_RAW_DATA ((स्थिर काष्ठा nla_policy *)(दीर्घ)(-ENODATA))

/**
 * काष्ठा wiphy_venकरोr_command - venकरोr command definition
 * @info: venकरोr command identअगरying inक्रमmation, as used in nl80211
 * @flags: flags, see &क्रमागत wiphy_venकरोr_command_flags
 * @करोit: callback क्रम the operation, note that wdev is %शून्य अगर the
 *	flags didn't ask क्रम a wdev and non-%शून्य otherwise; the data
 *	poपूर्णांकer may be %शून्य अगर userspace provided no data at all
 * @dumpit: dump callback, क्रम transferring bigger/multiple items. The
 *	@storage poपूर्णांकs to cb->args[5], ie. is preserved over the multiple
 *	dumpit calls.
 * @policy: policy poपूर्णांकer क्रम attributes within %NL80211_ATTR_VENDOR_DATA.
 *	Set this to %VENDOR_CMD_RAW_DATA अगर no policy can be given and the
 *	attribute is just raw data (e.g. a firmware command).
 * @maxattr: highest attribute number in policy
 * It's recommended to not have the same sub command with both @करोit and
 * @dumpit, so that userspace can assume certain ones are get and others
 * are used with dump requests.
 */
काष्ठा wiphy_venकरोr_command अणु
	काष्ठा nl80211_venकरोr_cmd_info info;
	u32 flags;
	पूर्णांक (*करोit)(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
		    स्थिर व्योम *data, पूर्णांक data_len);
	पूर्णांक (*dumpit)(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
		      काष्ठा sk_buff *skb, स्थिर व्योम *data, पूर्णांक data_len,
		      अचिन्हित दीर्घ *storage);
	स्थिर काष्ठा nla_policy *policy;
	अचिन्हित पूर्णांक maxattr;
पूर्ण;

/**
 * काष्ठा wiphy_अगरtype_ext_capab - extended capabilities per पूर्णांकerface type
 * @अगरtype: पूर्णांकerface type
 * @extended_capabilities: extended capabilities supported by the driver,
 *	additional capabilities might be supported by userspace; these are the
 *	802.11 extended capabilities ("Extended Capabilities element") and are
 *	in the same क्रमmat as in the inक्रमmation element. See IEEE Std
 *	802.11-2012 8.4.2.29 क्रम the defined fields.
 * @extended_capabilities_mask: mask of the valid values
 * @extended_capabilities_len: length of the extended capabilities
 */
काष्ठा wiphy_अगरtype_ext_capab अणु
	क्रमागत nl80211_अगरtype अगरtype;
	स्थिर u8 *extended_capabilities;
	स्थिर u8 *extended_capabilities_mask;
	u8 extended_capabilities_len;
पूर्ण;

/**
 * काष्ठा cfg80211_pmsr_capabilities - cfg80211 peer measurement capabilities
 * @max_peers: maximum number of peers in a single measurement
 * @report_ap_tsf: can report assoc AP's TSF क्रम radio resource measurement
 * @अक्रमomize_mac_addr: can अक्रमomize MAC address क्रम measurement
 * @fपंचांग.supported: FTM measurement is supported
 * @fपंचांग.asap: ASAP-mode is supported
 * @fपंचांग.non_asap: non-ASAP-mode is supported
 * @fपंचांग.request_lci: can request LCI data
 * @fपंचांग.request_civicloc: can request civic location data
 * @fपंचांग.preambles: biपंचांगap of preambles supported (&क्रमागत nl80211_preamble)
 * @fपंचांग.bandwidths: biपंचांगap of bandwidths supported (&क्रमागत nl80211_chan_width)
 * @fपंचांग.max_bursts_exponent: maximum burst exponent supported
 *	(set to -1 अगर not limited; note that setting this will necessarily
 *	क्रमbid using the value 15 to let the responder pick)
 * @fपंचांग.max_fपंचांगs_per_burst: maximum FTMs per burst supported (set to 0 अगर
 *	not limited)
 * @fपंचांग.trigger_based: trigger based ranging measurement is supported
 * @fपंचांग.non_trigger_based: non trigger based ranging measurement is supported
 */
काष्ठा cfg80211_pmsr_capabilities अणु
	अचिन्हित पूर्णांक max_peers;
	u8 report_ap_tsf:1,
	   अक्रमomize_mac_addr:1;

	काष्ठा अणु
		u32 preambles;
		u32 bandwidths;
		s8 max_bursts_exponent;
		u8 max_fपंचांगs_per_burst;
		u8 supported:1,
		   asap:1,
		   non_asap:1,
		   request_lci:1,
		   request_civicloc:1,
		   trigger_based:1,
		   non_trigger_based:1;
	पूर्ण fपंचांग;
पूर्ण;

/**
 * काष्ठा wiphy_अगरtype_akm_suites - This काष्ठाure encapsulates supported akm
 * suites क्रम पूर्णांकerface types defined in @अगरtypes_mask. Each type in the
 * @अगरtypes_mask must be unique across all instances of अगरtype_akm_suites.
 *
 * @अगरtypes_mask: biपंचांगask of पूर्णांकerfaces types
 * @akm_suites: poपूर्णांकs to an array of supported akm suites
 * @n_akm_suites: number of supported AKM suites
 */
काष्ठा wiphy_अगरtype_akm_suites अणु
	u16 अगरtypes_mask;
	स्थिर u32 *akm_suites;
	पूर्णांक n_akm_suites;
पूर्ण;

/**
 * काष्ठा wiphy - wireless hardware description
 * @mtx: mutex क्रम the data (काष्ठाures) of this device
 * @reg_notअगरier: the driver's regulatory notअगरication callback,
 *	note that अगर your driver uses wiphy_apply_custom_regulatory()
 *	the reg_notअगरier's request can be passed as शून्य
 * @regd: the driver's regulatory करोमुख्य, अगर one was requested via
 *	the regulatory_hपूर्णांक() API. This can be used by the driver
 *	on the reg_notअगरier() अगर it chooses to ignore future
 *	regulatory करोमुख्य changes caused by other drivers.
 * @संकेत_type: संकेत type reported in &काष्ठा cfg80211_bss.
 * @cipher_suites: supported cipher suites
 * @n_cipher_suites: number of supported cipher suites
 * @akm_suites: supported AKM suites. These are the शेष AKMs supported अगर
 *	the supported AKMs not advertized क्रम a specअगरic पूर्णांकerface type in
 *	अगरtype_akm_suites.
 * @n_akm_suites: number of supported AKM suites
 * @अगरtype_akm_suites: array of supported akm suites info per पूर्णांकerface type.
 *	Note that the bits in @अगरtypes_mask inside this काष्ठाure cannot
 *	overlap (i.e. only one occurrence of each type is allowed across all
 *	instances of अगरtype_akm_suites).
 * @num_अगरtype_akm_suites: number of पूर्णांकerface types क्रम which supported akm
 *	suites are specअगरied separately.
 * @retry_लघु: Retry limit क्रम लघु frames (करोt11ShortRetryLimit)
 * @retry_दीर्घ: Retry limit क्रम दीर्घ frames (करोt11LongRetryLimit)
 * @frag_threshold: Fragmentation threshold (करोt11FragmentationThreshold);
 *	-1 = fragmentation disabled, only odd values >= 256 used
 * @rts_threshold: RTS threshold (करोt11RTSThreshold); -1 = RTS/CTS disabled
 * @_net: the network namespace this wiphy currently lives in
 * @perm_addr: permanent MAC address of this device
 * @addr_mask: If the device supports multiple MAC addresses by masking,
 *	set this to a mask with variable bits set to 1, e.g. अगर the last
 *	four bits are variable then set it to 00-00-00-00-00-0f. The actual
 *	variable bits shall be determined by the पूर्णांकerfaces added, with
 *	पूर्णांकerfaces not matching the mask being rejected to be brought up.
 * @n_addresses: number of addresses in @addresses.
 * @addresses: If the device has more than one address, set this poपूर्णांकer
 *	to a list of addresses (6 bytes each). The first one will be used
 *	by शेष क्रम perm_addr. In this हाल, the mask should be set to
 *	all-zeroes. In this हाल it is assumed that the device can handle
 *	the same number of arbitrary MAC addresses.
 * @रेजिस्टरed: protects ->resume and ->suspend sysfs callbacks against
 *	unरेजिस्टर hardware
 * @debugfsdir: debugfs directory used क्रम this wiphy (ieee80211/<wiphyname>).
 *	It will be नामd स्वतःmatically on wiphy नामs
 * @dev: (भव) काष्ठा device क्रम this wiphy. The item in
 *	/sys/class/ieee80211/ poपूर्णांकs to this. You need use set_wiphy_dev()
 *	(see below).
 * @wext: wireless extension handlers
 * @priv: driver निजी data (sized according to wiphy_new() parameter)
 * @पूर्णांकerface_modes: biपंचांगask of पूर्णांकerfaces types valid क्रम this wiphy,
 *	must be set by driver
 * @अगरace_combinations: Valid पूर्णांकerface combinations array, should not
 *	list single पूर्णांकerface types.
 * @n_अगरace_combinations: number of entries in @अगरace_combinations array.
 * @software_अगरtypes: biपंचांगask of software पूर्णांकerface types, these are not
 *	subject to any restrictions since they are purely managed in SW.
 * @flags: wiphy flags, see &क्रमागत wiphy_flags
 * @regulatory_flags: wiphy regulatory flags, see
 *	&क्रमागत ieee80211_regulatory_flags
 * @features: features advertised to nl80211, see &क्रमागत nl80211_feature_flags.
 * @ext_features: extended features advertised to nl80211, see
 *	&क्रमागत nl80211_ext_feature_index.
 * @bss_priv_size: each BSS काष्ठा has निजी data allocated with it,
 *	this variable determines its size
 * @max_scan_ssids: maximum number of SSIDs the device can scan क्रम in
 *	any given scan
 * @max_sched_scan_reqs: maximum number of scheduled scan requests that
 *	the device can run concurrently.
 * @max_sched_scan_ssids: maximum number of SSIDs the device can scan
 *	क्रम in any given scheduled scan
 * @max_match_sets: maximum number of match sets the device can handle
 *	when perक्रमming a scheduled scan, 0 अगर filtering is not
 *	supported.
 * @max_scan_ie_len: maximum length of user-controlled IEs device can
 *	add to probe request frames transmitted during a scan, must not
 *	include fixed IEs like supported rates
 * @max_sched_scan_ie_len: same as max_scan_ie_len, but क्रम scheduled
 *	scans
 * @max_sched_scan_plans: maximum number of scan plans (scan पूर्णांकerval and number
 *	of iterations) क्रम scheduled scan supported by the device.
 * @max_sched_scan_plan_पूर्णांकerval: maximum पूर्णांकerval (in seconds) क्रम a
 *	single scan plan supported by the device.
 * @max_sched_scan_plan_iterations: maximum number of iterations क्रम a single
 *	scan plan supported by the device.
 * @coverage_class: current coverage class
 * @fw_version: firmware version क्रम ethtool reporting
 * @hw_version: hardware version क्रम ethtool reporting
 * @max_num_pmkids: maximum number of PMKIDs supported by device
 * @privid: a poपूर्णांकer that drivers can use to identअगरy अगर an arbitrary
 *	wiphy is theirs, e.g. in global notअगरiers
 * @bands: inक्रमmation about bands/channels supported by this device
 *
 * @mgmt_stypes: biपंचांगasks of frame subtypes that can be subscribed to or
 *	transmitted through nl80211, poपूर्णांकs to an array indexed by पूर्णांकerface
 *	type
 *
 * @available_antennas_tx: biपंचांगap of antennas which are available to be
 *	configured as TX antennas. Antenna configuration commands will be
 *	rejected unless this or @available_antennas_rx is set.
 *
 * @available_antennas_rx: biपंचांगap of antennas which are available to be
 *	configured as RX antennas. Antenna configuration commands will be
 *	rejected unless this or @available_antennas_tx is set.
 *
 * @probe_resp_offload:
 *	 Biपंचांगap of supported protocols क्रम probe response offloading.
 *	 See &क्रमागत nl80211_probe_resp_offload_support_attr. Only valid
 *	 when the wiphy flag @WIPHY_FLAG_AP_PROBE_RESP_OFFLOAD is set.
 *
 * @max_reमुख्य_on_channel_duration: Maximum समय a reमुख्य-on-channel operation
 *	may request, अगर implemented.
 *
 * @wowlan: WoWLAN support inक्रमmation
 * @wowlan_config: current WoWLAN configuration; this should usually not be
 *	used since access to it is necessarily racy, use the parameter passed
 *	to the suspend() operation instead.
 *
 * @ap_sme_capa: AP SME capabilities, flags from &क्रमागत nl80211_ap_sme_features.
 * @ht_capa_mod_mask:  Specअगरy what ht_cap values can be over-ridden.
 *	If null, then none can be over-ridden.
 * @vht_capa_mod_mask:  Specअगरy what VHT capabilities can be over-ridden.
 *	If null, then none can be over-ridden.
 *
 * @wdev_list: the list of associated (भव) पूर्णांकerfaces; this list must
 *	not be modअगरied by the driver, but can be पढ़ो with RTNL/RCU protection.
 *
 * @max_acl_mac_addrs: Maximum number of MAC addresses that the device
 *	supports क्रम ACL.
 *
 * @extended_capabilities: extended capabilities supported by the driver,
 *	additional capabilities might be supported by userspace; these are
 *	the 802.11 extended capabilities ("Extended Capabilities element")
 *	and are in the same क्रमmat as in the inक्रमmation element. See
 *	802.11-2012 8.4.2.29 क्रम the defined fields. These are the शेष
 *	extended capabilities to be used अगर the capabilities are not specअगरied
 *	क्रम a specअगरic पूर्णांकerface type in अगरtype_ext_capab.
 * @extended_capabilities_mask: mask of the valid values
 * @extended_capabilities_len: length of the extended capabilities
 * @अगरtype_ext_capab: array of extended capabilities per पूर्णांकerface type
 * @num_अगरtype_ext_capab: number of पूर्णांकerface types क्रम which extended
 *	capabilities are specअगरied separately.
 * @coalesce: packet coalescing support inक्रमmation
 *
 * @venकरोr_commands: array of venकरोr commands supported by the hardware
 * @n_venकरोr_commands: number of venकरोr commands
 * @venकरोr_events: array of venकरोr events supported by the hardware
 * @n_venकरोr_events: number of venकरोr events
 *
 * @max_ap_assoc_sta: maximum number of associated stations supported in AP mode
 *	(including P2P GO) or 0 to indicate no such limit is advertised. The
 *	driver is allowed to advertise a theoretical limit that it can reach in
 *	some हालs, but may not always reach.
 *
 * @max_num_csa_counters: Number of supported csa_counters in beacons
 *	and probe responses.  This value should be set अगर the driver
 *	wishes to limit the number of csa counters. Default (0) means
 *	infinite.
 * @bss_select_support: biपंचांगask indicating the BSS selection criteria supported
 *	by the driver in the .connect() callback. The bit position maps to the
 *	attribute indices defined in &क्रमागत nl80211_bss_select_attr.
 *
 * @nan_supported_bands: bands supported by the device in न_अंक mode, a
 *	biपंचांगap of &क्रमागत nl80211_band values.  For instance, क्रम
 *	NL80211_BAND_2GHZ, bit 0 would be set
 *	(i.e. BIT(NL80211_BAND_2GHZ)).
 *
 * @txq_limit: configuration of पूर्णांकernal TX queue frame limit
 * @txq_memory_limit: configuration पूर्णांकernal TX queue memory limit
 * @txq_quantum: configuration of पूर्णांकernal TX queue scheduler quantum
 *
 * @tx_queue_len: allow setting transmit queue len क्रम drivers not using
 *	wake_tx_queue
 *
 * @support_mbssid: can HW support association with nontransmitted AP
 * @support_only_he_mbssid: करोn't parse MBSSID elements अगर it is not
 *	HE AP, in order to aव्योम compatibility issues.
 *	@support_mbssid must be set क्रम this to have any effect.
 *
 * @pmsr_capa: peer measurement capabilities
 *
 * @tid_config_support: describes the per-TID config support that the
 *	device has
 * @tid_config_support.vअगर: biपंचांगap of attributes (configurations)
 *	supported by the driver क्रम each vअगर
 * @tid_config_support.peer: biपंचांगap of attributes (configurations)
 *	supported by the driver क्रम each peer
 * @tid_config_support.max_retry: maximum supported retry count क्रम
 *	दीर्घ/लघु retry configuration
 *
 * @max_data_retry_count: maximum supported per TID retry count क्रम
 *	configuration through the %NL80211_TID_CONFIG_ATTR_RETRY_SHORT and
 *	%NL80211_TID_CONFIG_ATTR_RETRY_LONG attributes
 * @sar_capa: SAR control capabilities
 */
काष्ठा wiphy अणु
	काष्ठा mutex mtx;

	/* assign these fields beक्रमe you रेजिस्टर the wiphy */

	u8 perm_addr[ETH_ALEN];
	u8 addr_mask[ETH_ALEN];

	काष्ठा mac_address *addresses;

	स्थिर काष्ठा ieee80211_txrx_stypes *mgmt_stypes;

	स्थिर काष्ठा ieee80211_अगरace_combination *अगरace_combinations;
	पूर्णांक n_अगरace_combinations;
	u16 software_अगरtypes;

	u16 n_addresses;

	/* Supported पूर्णांकerface modes, OR together BIT(NL80211_IFTYPE_...) */
	u16 पूर्णांकerface_modes;

	u16 max_acl_mac_addrs;

	u32 flags, regulatory_flags, features;
	u8 ext_features[DIV_ROUND_UP(NUM_NL80211_EXT_FEATURES, 8)];

	u32 ap_sme_capa;

	क्रमागत cfg80211_संकेत_type संकेत_type;

	पूर्णांक bss_priv_size;
	u8 max_scan_ssids;
	u8 max_sched_scan_reqs;
	u8 max_sched_scan_ssids;
	u8 max_match_sets;
	u16 max_scan_ie_len;
	u16 max_sched_scan_ie_len;
	u32 max_sched_scan_plans;
	u32 max_sched_scan_plan_पूर्णांकerval;
	u32 max_sched_scan_plan_iterations;

	पूर्णांक n_cipher_suites;
	स्थिर u32 *cipher_suites;

	पूर्णांक n_akm_suites;
	स्थिर u32 *akm_suites;

	स्थिर काष्ठा wiphy_अगरtype_akm_suites *अगरtype_akm_suites;
	अचिन्हित पूर्णांक num_अगरtype_akm_suites;

	u8 retry_लघु;
	u8 retry_दीर्घ;
	u32 frag_threshold;
	u32 rts_threshold;
	u8 coverage_class;

	अक्षर fw_version[ETHTOOL_FWVERS_LEN];
	u32 hw_version;

#अगर_घोषित CONFIG_PM
	स्थिर काष्ठा wiphy_wowlan_support *wowlan;
	काष्ठा cfg80211_wowlan *wowlan_config;
#पूर्ण_अगर

	u16 max_reमुख्य_on_channel_duration;

	u8 max_num_pmkids;

	u32 available_antennas_tx;
	u32 available_antennas_rx;

	u32 probe_resp_offload;

	स्थिर u8 *extended_capabilities, *extended_capabilities_mask;
	u8 extended_capabilities_len;

	स्थिर काष्ठा wiphy_अगरtype_ext_capab *अगरtype_ext_capab;
	अचिन्हित पूर्णांक num_अगरtype_ext_capab;

	स्थिर व्योम *privid;

	काष्ठा ieee80211_supported_band *bands[NUM_NL80211_BANDS];

	व्योम (*reg_notअगरier)(काष्ठा wiphy *wiphy,
			     काष्ठा regulatory_request *request);

	/* fields below are पढ़ो-only, asचिन्हित by cfg80211 */

	स्थिर काष्ठा ieee80211_regकरोमुख्य __rcu *regd;

	काष्ठा device dev;

	bool रेजिस्टरed;

	काष्ठा dentry *debugfsdir;

	स्थिर काष्ठा ieee80211_ht_cap *ht_capa_mod_mask;
	स्थिर काष्ठा ieee80211_vht_cap *vht_capa_mod_mask;

	काष्ठा list_head wdev_list;

	possible_net_t _net;

#अगर_घोषित CONFIG_CFG80211_WEXT
	स्थिर काष्ठा iw_handler_def *wext;
#पूर्ण_अगर

	स्थिर काष्ठा wiphy_coalesce_support *coalesce;

	स्थिर काष्ठा wiphy_venकरोr_command *venकरोr_commands;
	स्थिर काष्ठा nl80211_venकरोr_cmd_info *venकरोr_events;
	पूर्णांक n_venकरोr_commands, n_venकरोr_events;

	u16 max_ap_assoc_sta;

	u8 max_num_csa_counters;

	u32 bss_select_support;

	u8 nan_supported_bands;

	u32 txq_limit;
	u32 txq_memory_limit;
	u32 txq_quantum;

	अचिन्हित दीर्घ tx_queue_len;

	u8 support_mbssid:1,
	   support_only_he_mbssid:1;

	स्थिर काष्ठा cfg80211_pmsr_capabilities *pmsr_capa;

	काष्ठा अणु
		u64 peer, vअगर;
		u8 max_retry;
	पूर्ण tid_config_support;

	u8 max_data_retry_count;

	स्थिर काष्ठा cfg80211_sar_capa *sar_capa;

	अक्षर priv[] __aligned(NETDEV_ALIGN);
पूर्ण;

अटल अंतरभूत काष्ठा net *wiphy_net(काष्ठा wiphy *wiphy)
अणु
	वापस पढ़ो_pnet(&wiphy->_net);
पूर्ण

अटल अंतरभूत व्योम wiphy_net_set(काष्ठा wiphy *wiphy, काष्ठा net *net)
अणु
	ग_लिखो_pnet(&wiphy->_net, net);
पूर्ण

/**
 * wiphy_priv - वापस priv from wiphy
 *
 * @wiphy: the wiphy whose priv poपूर्णांकer to वापस
 * Return: The priv of @wiphy.
 */
अटल अंतरभूत व्योम *wiphy_priv(काष्ठा wiphy *wiphy)
अणु
	BUG_ON(!wiphy);
	वापस &wiphy->priv;
पूर्ण

/**
 * priv_to_wiphy - वापस the wiphy containing the priv
 *
 * @priv: a poपूर्णांकer previously वापसed by wiphy_priv
 * Return: The wiphy of @priv.
 */
अटल अंतरभूत काष्ठा wiphy *priv_to_wiphy(व्योम *priv)
अणु
	BUG_ON(!priv);
	वापस container_of(priv, काष्ठा wiphy, priv);
पूर्ण

/**
 * set_wiphy_dev - set device poपूर्णांकer क्रम wiphy
 *
 * @wiphy: The wiphy whose device to bind
 * @dev: The device to parent it to
 */
अटल अंतरभूत व्योम set_wiphy_dev(काष्ठा wiphy *wiphy, काष्ठा device *dev)
अणु
	wiphy->dev.parent = dev;
पूर्ण

/**
 * wiphy_dev - get wiphy dev poपूर्णांकer
 *
 * @wiphy: The wiphy whose device काष्ठा to look up
 * Return: The dev of @wiphy.
 */
अटल अंतरभूत काष्ठा device *wiphy_dev(काष्ठा wiphy *wiphy)
अणु
	वापस wiphy->dev.parent;
पूर्ण

/**
 * wiphy_name - get wiphy name
 *
 * @wiphy: The wiphy whose name to वापस
 * Return: The name of @wiphy.
 */
अटल अंतरभूत स्थिर अक्षर *wiphy_name(स्थिर काष्ठा wiphy *wiphy)
अणु
	वापस dev_name(&wiphy->dev);
पूर्ण

/**
 * wiphy_new_nm - create a new wiphy क्रम use with cfg80211
 *
 * @ops: The configuration operations क्रम this device
 * @माप_priv: The size of the निजी area to allocate
 * @requested_name: Request a particular name.
 *	शून्य is valid value, and means use the शेष phy%d naming.
 *
 * Create a new wiphy and associate the given operations with it.
 * @माप_priv bytes are allocated क्रम निजी use.
 *
 * Return: A poपूर्णांकer to the new wiphy. This poपूर्णांकer must be
 * asचिन्हित to each netdev's ieee80211_ptr क्रम proper operation.
 */
काष्ठा wiphy *wiphy_new_nm(स्थिर काष्ठा cfg80211_ops *ops, पूर्णांक माप_priv,
			   स्थिर अक्षर *requested_name);

/**
 * wiphy_new - create a new wiphy क्रम use with cfg80211
 *
 * @ops: The configuration operations क्रम this device
 * @माप_priv: The size of the निजी area to allocate
 *
 * Create a new wiphy and associate the given operations with it.
 * @माप_priv bytes are allocated क्रम निजी use.
 *
 * Return: A poपूर्णांकer to the new wiphy. This poपूर्णांकer must be
 * asचिन्हित to each netdev's ieee80211_ptr क्रम proper operation.
 */
अटल अंतरभूत काष्ठा wiphy *wiphy_new(स्थिर काष्ठा cfg80211_ops *ops,
				      पूर्णांक माप_priv)
अणु
	वापस wiphy_new_nm(ops, माप_priv, शून्य);
पूर्ण

/**
 * wiphy_रेजिस्टर - रेजिस्टर a wiphy with cfg80211
 *
 * @wiphy: The wiphy to रेजिस्टर.
 *
 * Return: A non-negative wiphy index or a negative error code.
 */
पूर्णांक wiphy_रेजिस्टर(काष्ठा wiphy *wiphy);

/* this is a define क्रम better error reporting (file/line) */
#घोषणा lockdep_निश्चित_wiphy(wiphy) lockdep_निश्चित_held(&(wiphy)->mtx)

/**
 * rcu_dereference_wiphy - rcu_dereference with debug checking
 * @wiphy: the wiphy to check the locking on
 * @p: The poपूर्णांकer to पढ़ो, prior to dereferencing
 *
 * Do an rcu_dereference(p), but check caller either holds rcu_पढ़ो_lock()
 * or RTNL. Note: Please prefer wiphy_dereference() or rcu_dereference().
 */
#घोषणा rcu_dereference_wiphy(wiphy, p)				\
        rcu_dereference_check(p, lockdep_is_held(&wiphy->mtx))

/**
 * wiphy_dereference - fetch RCU poपूर्णांकer when updates are prevented by wiphy mtx
 * @wiphy: the wiphy to check the locking on
 * @p: The poपूर्णांकer to पढ़ो, prior to dereferencing
 *
 * Return the value of the specअगरied RCU-रक्षित poपूर्णांकer, but omit the
 * READ_ONCE(), because caller holds the wiphy mutex used क्रम updates.
 */
#घोषणा wiphy_dereference(wiphy, p)				\
        rcu_dereference_रक्षित(p, lockdep_is_held(&wiphy->mtx))

/**
 * get_wiphy_regकरोm - get custom regकरोमुख्य क्रम the given wiphy
 * @wiphy: the wiphy to get the regकरोमुख्य from
 */
स्थिर काष्ठा ieee80211_regकरोमुख्य *get_wiphy_regकरोm(काष्ठा wiphy *wiphy);

/**
 * wiphy_unरेजिस्टर - deरेजिस्टर a wiphy from cfg80211
 *
 * @wiphy: The wiphy to unरेजिस्टर.
 *
 * After this call, no more requests can be made with this priv
 * poपूर्णांकer, but the call may sleep to रुको क्रम an outstanding
 * request that is being handled.
 */
व्योम wiphy_unरेजिस्टर(काष्ठा wiphy *wiphy);

/**
 * wiphy_मुक्त - मुक्त wiphy
 *
 * @wiphy: The wiphy to मुक्त
 */
व्योम wiphy_मुक्त(काष्ठा wiphy *wiphy);

/* पूर्णांकernal काष्ठाs */
काष्ठा cfg80211_conn;
काष्ठा cfg80211_पूर्णांकernal_bss;
काष्ठा cfg80211_cached_keys;
काष्ठा cfg80211_cqm_config;

/**
 * wiphy_lock - lock the wiphy
 * @wiphy: the wiphy to lock
 *
 * This is mostly exposed so it can be करोne around रेजिस्टरing and
 * unरेजिस्टरing netdevs that aren't created through cfg80211 calls,
 * since that requires locking in cfg80211 when the notअगरiers is
 * called, but that cannot dअगरferentiate which way it's called.
 *
 * When cfg80211 ops are called, the wiphy is alपढ़ोy locked.
 */
अटल अंतरभूत व्योम wiphy_lock(काष्ठा wiphy *wiphy)
	__acquires(&wiphy->mtx)
अणु
	mutex_lock(&wiphy->mtx);
	__acquire(&wiphy->mtx);
पूर्ण

/**
 * wiphy_unlock - unlock the wiphy again
 * @wiphy: the wiphy to unlock
 */
अटल अंतरभूत व्योम wiphy_unlock(काष्ठा wiphy *wiphy)
	__releases(&wiphy->mtx)
अणु
	__release(&wiphy->mtx);
	mutex_unlock(&wiphy->mtx);
पूर्ण

/**
 * काष्ठा wireless_dev - wireless device state
 *
 * For netdevs, this काष्ठाure must be allocated by the driver
 * that uses the ieee80211_ptr field in काष्ठा net_device (this
 * is पूर्णांकentional so it can be allocated aदीर्घ with the netdev.)
 * It need not be रेजिस्टरed then as netdev registration will
 * be पूर्णांकercepted by cfg80211 to see the new wireless device,
 * however, drivers must lock the wiphy beक्रमe रेजिस्टरing or
 * unरेजिस्टरing netdevs अगर they pre-create any netdevs (in ops
 * called from cfg80211, the wiphy is alपढ़ोy locked.)
 *
 * For non-netdev uses, it must also be allocated by the driver
 * in response to the cfg80211 callbacks that require it, as
 * there's no netdev registration in that हाल it may not be
 * allocated outside of callback operations that वापस it.
 *
 * @wiphy: poपूर्णांकer to hardware description
 * @अगरtype: पूर्णांकerface type
 * @रेजिस्टरed: is this wdev alपढ़ोy रेजिस्टरed with cfg80211
 * @रेजिस्टरing: indicates we're करोing registration under wiphy lock
 *	क्रम the notअगरier
 * @list: (निजी) Used to collect the पूर्णांकerfaces
 * @netdev: (निजी) Used to reference back to the netdev, may be %शून्य
 * @identअगरier: (निजी) Identअगरier used in nl80211 to identअगरy this
 *	wireless device अगर it has no netdev
 * @current_bss: (निजी) Used by the पूर्णांकernal configuration code
 * @chandef: (निजी) Used by the पूर्णांकernal configuration code to track
 *	the user-set channel definition.
 * @preset_chandef: (निजी) Used by the पूर्णांकernal configuration code to
 *	track the channel to be used क्रम AP later
 * @bssid: (निजी) Used by the पूर्णांकernal configuration code
 * @ssid: (निजी) Used by the पूर्णांकernal configuration code
 * @ssid_len: (निजी) Used by the पूर्णांकernal configuration code
 * @mesh_id_len: (निजी) Used by the पूर्णांकernal configuration code
 * @mesh_id_up_len: (निजी) Used by the पूर्णांकernal configuration code
 * @wext: (निजी) Used by the पूर्णांकernal wireless extensions compat code
 * @wext.ibss: (निजी) IBSS data part of wext handling
 * @wext.connect: (निजी) connection handling data
 * @wext.keys: (निजी) (WEP) key data
 * @wext.ie: (निजी) extra elements क्रम association
 * @wext.ie_len: (निजी) length of extra elements
 * @wext.bssid: (निजी) selected network BSSID
 * @wext.ssid: (निजी) selected network SSID
 * @wext.शेष_key: (निजी) selected शेष key index
 * @wext.शेष_mgmt_key: (निजी) selected शेष management key index
 * @wext.prev_bssid: (निजी) previous BSSID क्रम reassociation
 * @wext.prev_bssid_valid: (निजी) previous BSSID validity
 * @use_4addr: indicates 4addr mode is used on this पूर्णांकerface, must be
 *	set by driver (अगर supported) on add_पूर्णांकerface BEFORE रेजिस्टरing the
 *	netdev and may otherwise be used by driver पढ़ो-only, will be update
 *	by cfg80211 on change_पूर्णांकerface
 * @mgmt_registrations: list of registrations क्रम management frames
 * @mgmt_registrations_lock: lock क्रम the list
 * @mgmt_registrations_need_update: mgmt registrations were updated,
 *	need to propagate the update to the driver
 * @mtx: mutex used to lock data in this काष्ठा, may be used by drivers
 *	and some API functions require it held
 * @beacon_पूर्णांकerval: beacon पूर्णांकerval used on this device क्रम transmitting
 *	beacons, 0 when not valid
 * @address: The address क्रम this device, valid only अगर @netdev is %शून्य
 * @is_running: true अगर this is a non-netdev device that has been started, e.g.
 *	the P2P Device.
 * @cac_started: true अगर DFS channel availability check has been started
 * @cac_start_समय: बारtamp (jअगरfies) when the dfs state was entered.
 * @cac_समय_ms: CAC समय in ms
 * @ps: घातersave mode is enabled
 * @ps_समयout: dynamic घातersave समयout
 * @ap_unexpected_nlportid: (निजी) netlink port ID of application
 *	रेजिस्टरed क्रम unexpected class 3 frames (AP mode)
 * @conn: (निजी) cfg80211 software SME connection state machine data
 * @connect_keys: (निजी) keys to set after connection is established
 * @conn_bss_type: connecting/connected BSS type
 * @conn_owner_nlportid: (निजी) connection owner socket port ID
 * @disconnect_wk: (निजी) स्वतः-disconnect work
 * @disconnect_bssid: (निजी) the BSSID to use क्रम स्वतः-disconnect
 * @ibss_fixed: (निजी) IBSS is using fixed BSSID
 * @ibss_dfs_possible: (निजी) IBSS may change to a DFS channel
 * @event_list: (निजी) list क्रम पूर्णांकernal event processing
 * @event_lock: (निजी) lock क्रम event list
 * @owner_nlportid: (निजी) owner socket port ID
 * @nl_owner_dead: (निजी) owner socket went away
 * @cqm_config: (निजी) nl80211 RSSI monitor state
 * @pmsr_list: (निजी) peer measurement requests
 * @pmsr_lock: (निजी) peer measurements requests/results lock
 * @pmsr_मुक्त_wk: (निजी) peer measurements cleanup work
 * @unprot_beacon_reported: (निजी) बारtamp of last
 *	unरक्षित beacon report
 */
काष्ठा wireless_dev अणु
	काष्ठा wiphy *wiphy;
	क्रमागत nl80211_अगरtype अगरtype;

	/* the reमुख्यder of this काष्ठा should be निजी to cfg80211 */
	काष्ठा list_head list;
	काष्ठा net_device *netdev;

	u32 identअगरier;

	काष्ठा list_head mgmt_registrations;
	spinlock_t mgmt_registrations_lock;
	u8 mgmt_registrations_need_update:1;

	काष्ठा mutex mtx;

	bool use_4addr, is_running, रेजिस्टरed, रेजिस्टरing;

	u8 address[ETH_ALEN] __aligned(माप(u16));

	/* currently used क्रम IBSS and SME - might be rearranged later */
	u8 ssid[IEEE80211_MAX_SSID_LEN];
	u8 ssid_len, mesh_id_len, mesh_id_up_len;
	काष्ठा cfg80211_conn *conn;
	काष्ठा cfg80211_cached_keys *connect_keys;
	क्रमागत ieee80211_bss_type conn_bss_type;
	u32 conn_owner_nlportid;

	काष्ठा work_काष्ठा disconnect_wk;
	u8 disconnect_bssid[ETH_ALEN];

	काष्ठा list_head event_list;
	spinlock_t event_lock;

	काष्ठा cfg80211_पूर्णांकernal_bss *current_bss; /* associated / joined */
	काष्ठा cfg80211_chan_def preset_chandef;
	काष्ठा cfg80211_chan_def chandef;

	bool ibss_fixed;
	bool ibss_dfs_possible;

	bool ps;
	पूर्णांक ps_समयout;

	पूर्णांक beacon_पूर्णांकerval;

	u32 ap_unexpected_nlportid;

	u32 owner_nlportid;
	bool nl_owner_dead;

	bool cac_started;
	अचिन्हित दीर्घ cac_start_समय;
	अचिन्हित पूर्णांक cac_समय_ms;

#अगर_घोषित CONFIG_CFG80211_WEXT
	/* wext data */
	काष्ठा अणु
		काष्ठा cfg80211_ibss_params ibss;
		काष्ठा cfg80211_connect_params connect;
		काष्ठा cfg80211_cached_keys *keys;
		स्थिर u8 *ie;
		माप_प्रकार ie_len;
		u8 bssid[ETH_ALEN];
		u8 prev_bssid[ETH_ALEN];
		u8 ssid[IEEE80211_MAX_SSID_LEN];
		s8 शेष_key, शेष_mgmt_key;
		bool prev_bssid_valid;
	पूर्ण wext;
#पूर्ण_अगर

	काष्ठा cfg80211_cqm_config *cqm_config;

	काष्ठा list_head pmsr_list;
	spinlock_t pmsr_lock;
	काष्ठा work_काष्ठा pmsr_मुक्त_wk;

	अचिन्हित दीर्घ unprot_beacon_reported;
पूर्ण;

अटल अंतरभूत u8 *wdev_address(काष्ठा wireless_dev *wdev)
अणु
	अगर (wdev->netdev)
		वापस wdev->netdev->dev_addr;
	वापस wdev->address;
पूर्ण

अटल अंतरभूत bool wdev_running(काष्ठा wireless_dev *wdev)
अणु
	अगर (wdev->netdev)
		वापस netअगर_running(wdev->netdev);
	वापस wdev->is_running;
पूर्ण

/**
 * wdev_priv - वापस wiphy priv from wireless_dev
 *
 * @wdev: The wireless device whose wiphy's priv poपूर्णांकer to वापस
 * Return: The wiphy priv of @wdev.
 */
अटल अंतरभूत व्योम *wdev_priv(काष्ठा wireless_dev *wdev)
अणु
	BUG_ON(!wdev);
	वापस wiphy_priv(wdev->wiphy);
पूर्ण

/**
 * DOC: Utility functions
 *
 * cfg80211 offers a number of utility functions that can be useful.
 */

/**
 * ieee80211_channel_equal - compare two काष्ठा ieee80211_channel
 *
 * @a: 1st काष्ठा ieee80211_channel
 * @b: 2nd काष्ठा ieee80211_channel
 * Return: true अगर center frequency of @a == @b
 */
अटल अंतरभूत bool
ieee80211_channel_equal(काष्ठा ieee80211_channel *a,
			काष्ठा ieee80211_channel *b)
अणु
	वापस (a->center_freq == b->center_freq &&
		a->freq_offset == b->freq_offset);
पूर्ण

/**
 * ieee80211_channel_to_khz - convert ieee80211_channel to frequency in KHz
 * @chan: काष्ठा ieee80211_channel to convert
 * Return: The corresponding frequency (in KHz)
 */
अटल अंतरभूत u32
ieee80211_channel_to_khz(स्थिर काष्ठा ieee80211_channel *chan)
अणु
	वापस MHZ_TO_KHZ(chan->center_freq) + chan->freq_offset;
पूर्ण

/**
 * ieee80211_s1g_channel_width - get allowed channel width from @chan
 *
 * Only allowed क्रम band NL80211_BAND_S1GHZ
 * @chan: channel
 * Return: The allowed channel width क्रम this center_freq
 */
क्रमागत nl80211_chan_width
ieee80211_s1g_channel_width(स्थिर काष्ठा ieee80211_channel *chan);

/**
 * ieee80211_channel_to_freq_khz - convert channel number to frequency
 * @chan: channel number
 * @band: band, necessary due to channel number overlap
 * Return: The corresponding frequency (in KHz), or 0 अगर the conversion failed.
 */
u32 ieee80211_channel_to_freq_khz(पूर्णांक chan, क्रमागत nl80211_band band);

/**
 * ieee80211_channel_to_frequency - convert channel number to frequency
 * @chan: channel number
 * @band: band, necessary due to channel number overlap
 * Return: The corresponding frequency (in MHz), or 0 अगर the conversion failed.
 */
अटल अंतरभूत पूर्णांक
ieee80211_channel_to_frequency(पूर्णांक chan, क्रमागत nl80211_band band)
अणु
	वापस KHZ_TO_MHZ(ieee80211_channel_to_freq_khz(chan, band));
पूर्ण

/**
 * ieee80211_freq_khz_to_channel - convert frequency to channel number
 * @freq: center frequency in KHz
 * Return: The corresponding channel, or 0 अगर the conversion failed.
 */
पूर्णांक ieee80211_freq_khz_to_channel(u32 freq);

/**
 * ieee80211_frequency_to_channel - convert frequency to channel number
 * @freq: center frequency in MHz
 * Return: The corresponding channel, or 0 अगर the conversion failed.
 */
अटल अंतरभूत पूर्णांक
ieee80211_frequency_to_channel(पूर्णांक freq)
अणु
	वापस ieee80211_freq_khz_to_channel(MHZ_TO_KHZ(freq));
पूर्ण

/**
 * ieee80211_get_channel_khz - get channel काष्ठा from wiphy क्रम specअगरied
 * frequency
 * @wiphy: the काष्ठा wiphy to get the channel क्रम
 * @freq: the center frequency (in KHz) of the channel
 * Return: The channel काष्ठा from @wiphy at @freq.
 */
काष्ठा ieee80211_channel *
ieee80211_get_channel_khz(काष्ठा wiphy *wiphy, u32 freq);

/**
 * ieee80211_get_channel - get channel काष्ठा from wiphy क्रम specअगरied frequency
 *
 * @wiphy: the काष्ठा wiphy to get the channel क्रम
 * @freq: the center frequency (in MHz) of the channel
 * Return: The channel काष्ठा from @wiphy at @freq.
 */
अटल अंतरभूत काष्ठा ieee80211_channel *
ieee80211_get_channel(काष्ठा wiphy *wiphy, पूर्णांक freq)
अणु
	वापस ieee80211_get_channel_khz(wiphy, MHZ_TO_KHZ(freq));
पूर्ण

/**
 * cfg80211_channel_is_psc - Check अगर the channel is a 6 GHz PSC
 * @chan: control channel to check
 *
 * The Preferred Scanning Channels (PSC) are defined in
 * Draft IEEE P802.11ax/D5.0, 26.17.2.3.3
 */
अटल अंतरभूत bool cfg80211_channel_is_psc(काष्ठा ieee80211_channel *chan)
अणु
	अगर (chan->band != NL80211_BAND_6GHZ)
		वापस false;

	वापस ieee80211_frequency_to_channel(chan->center_freq) % 16 == 5;
पूर्ण

/**
 * ieee80211_get_response_rate - get basic rate क्रम a given rate
 *
 * @sband: the band to look क्रम rates in
 * @basic_rates: biपंचांगap of basic rates
 * @bitrate: the bitrate क्रम which to find the basic rate
 *
 * Return: The basic rate corresponding to a given bitrate, that
 * is the next lower bitrate contained in the basic rate map,
 * which is, क्रम this function, given as a biपंचांगap of indices of
 * rates in the band's bitrate table.
 */
स्थिर काष्ठा ieee80211_rate *
ieee80211_get_response_rate(काष्ठा ieee80211_supported_band *sband,
			    u32 basic_rates, पूर्णांक bitrate);

/**
 * ieee80211_mandatory_rates - get mandatory rates क्रम a given band
 * @sband: the band to look क्रम rates in
 * @scan_width: width of the control channel
 *
 * This function वापसs a biपंचांगap of the mandatory rates क्रम the given
 * band, bits are set according to the rate position in the bitrates array.
 */
u32 ieee80211_mandatory_rates(काष्ठा ieee80211_supported_band *sband,
			      क्रमागत nl80211_bss_scan_width scan_width);

/*
 * Radiotap parsing functions -- क्रम controlled injection support
 *
 * Implemented in net/wireless/radiotap.c
 * Documentation in Documentation/networking/radiotap-headers.rst
 */

काष्ठा radiotap_align_size अणु
	uपूर्णांक8_t align:4, size:4;
पूर्ण;

काष्ठा ieee80211_radiotap_namespace अणु
	स्थिर काष्ठा radiotap_align_size *align_size;
	पूर्णांक n_bits;
	uपूर्णांक32_t oui;
	uपूर्णांक8_t subns;
पूर्ण;

काष्ठा ieee80211_radiotap_venकरोr_namespaces अणु
	स्थिर काष्ठा ieee80211_radiotap_namespace *ns;
	पूर्णांक n_ns;
पूर्ण;

/**
 * काष्ठा ieee80211_radiotap_iterator - tracks walk thru present radiotap args
 * @this_arg_index: index of current arg, valid after each successful call
 *	to ieee80211_radiotap_iterator_next()
 * @this_arg: poपूर्णांकer to current radiotap arg; it is valid after each
 *	call to ieee80211_radiotap_iterator_next() but also after
 *	ieee80211_radiotap_iterator_init() where it will poपूर्णांक to
 *	the beginning of the actual data portion
 * @this_arg_size: length of the current arg, क्रम convenience
 * @current_namespace: poपूर्णांकer to the current namespace definition
 *	(or पूर्णांकernally %शून्य अगर the current namespace is unknown)
 * @is_radiotap_ns: indicates whether the current namespace is the शेष
 *	radiotap namespace or not
 *
 * @_rtheader: poपूर्णांकer to the radiotap header we are walking through
 * @_max_length: length of radiotap header in cpu byte ordering
 * @_arg_index: next argument index
 * @_arg: next argument poपूर्णांकer
 * @_next_biपंचांगap: पूर्णांकernal poपूर्णांकer to next present u32
 * @_biपंचांगap_shअगरter: पूर्णांकernal shअगरter क्रम curr u32 biपंचांगap, b0 set == arg present
 * @_vns: venकरोr namespace definitions
 * @_next_ns_data: beginning of the next namespace's data
 * @_reset_on_ext: पूर्णांकernal; reset the arg index to 0 when going to the
 *	next biपंचांगap word
 *
 * Describes the radiotap parser state. Fields prefixed with an underscore
 * must not be used by users of the parser, only by the parser पूर्णांकernally.
 */

काष्ठा ieee80211_radiotap_iterator अणु
	काष्ठा ieee80211_radiotap_header *_rtheader;
	स्थिर काष्ठा ieee80211_radiotap_venकरोr_namespaces *_vns;
	स्थिर काष्ठा ieee80211_radiotap_namespace *current_namespace;

	अचिन्हित अक्षर *_arg, *_next_ns_data;
	__le32 *_next_biपंचांगap;

	अचिन्हित अक्षर *this_arg;
	पूर्णांक this_arg_index;
	पूर्णांक this_arg_size;

	पूर्णांक is_radiotap_ns;

	पूर्णांक _max_length;
	पूर्णांक _arg_index;
	uपूर्णांक32_t _biपंचांगap_shअगरter;
	पूर्णांक _reset_on_ext;
पूर्ण;

पूर्णांक
ieee80211_radiotap_iterator_init(काष्ठा ieee80211_radiotap_iterator *iterator,
				 काष्ठा ieee80211_radiotap_header *radiotap_header,
				 पूर्णांक max_length,
				 स्थिर काष्ठा ieee80211_radiotap_venकरोr_namespaces *vns);

पूर्णांक
ieee80211_radiotap_iterator_next(काष्ठा ieee80211_radiotap_iterator *iterator);


बाह्य स्थिर अचिन्हित अक्षर rfc1042_header[6];
बाह्य स्थिर अचिन्हित अक्षर bridge_tunnel_header[6];

/**
 * ieee80211_get_hdrlen_from_skb - get header length from data
 *
 * @skb: the frame
 *
 * Given an skb with a raw 802.11 header at the data poपूर्णांकer this function
 * वापसs the 802.11 header length.
 *
 * Return: The 802.11 header length in bytes (not including encryption
 * headers). Or 0 अगर the data in the sk_buff is too लघु to contain a valid
 * 802.11 header.
 */
अचिन्हित पूर्णांक ieee80211_get_hdrlen_from_skb(स्थिर काष्ठा sk_buff *skb);

/**
 * ieee80211_hdrlen - get header length in bytes from frame control
 * @fc: frame control field in little-endian क्रमmat
 * Return: The header length in bytes.
 */
अचिन्हित पूर्णांक __attribute_स्थिर__ ieee80211_hdrlen(__le16 fc);

/**
 * ieee80211_get_mesh_hdrlen - get mesh extension header length
 * @meshhdr: the mesh extension header, only the flags field
 *	(first byte) will be accessed
 * Return: The length of the extension header, which is always at
 * least 6 bytes and at most 18 अगर address 5 and 6 are present.
 */
अचिन्हित पूर्णांक ieee80211_get_mesh_hdrlen(काष्ठा ieee80211s_hdr *meshhdr);

/**
 * DOC: Data path helpers
 *
 * In addition to generic utilities, cfg80211 also offers
 * functions that help implement the data path क्रम devices
 * that करो not करो the 802.11/802.3 conversion on the device.
 */

/**
 * ieee80211_data_to_8023_exthdr - convert an 802.11 data frame to 802.3
 * @skb: the 802.11 data frame
 * @ehdr: poपूर्णांकer to a &काष्ठा ethhdr that will get the header, instead
 *	of it being pushed पूर्णांकo the SKB
 * @addr: the device MAC address
 * @अगरtype: the भव पूर्णांकerface type
 * @data_offset: offset of payload after the 802.11 header
 * Return: 0 on success. Non-zero on error.
 */
पूर्णांक ieee80211_data_to_8023_exthdr(काष्ठा sk_buff *skb, काष्ठा ethhdr *ehdr,
				  स्थिर u8 *addr, क्रमागत nl80211_अगरtype अगरtype,
				  u8 data_offset, bool is_amsdu);

/**
 * ieee80211_data_to_8023 - convert an 802.11 data frame to 802.3
 * @skb: the 802.11 data frame
 * @addr: the device MAC address
 * @अगरtype: the भव पूर्णांकerface type
 * Return: 0 on success. Non-zero on error.
 */
अटल अंतरभूत पूर्णांक ieee80211_data_to_8023(काष्ठा sk_buff *skb, स्थिर u8 *addr,
					 क्रमागत nl80211_अगरtype अगरtype)
अणु
	वापस ieee80211_data_to_8023_exthdr(skb, शून्य, addr, अगरtype, 0, false);
पूर्ण

/**
 * ieee80211_amsdu_to_8023s - decode an IEEE 802.11n A-MSDU frame
 *
 * Decode an IEEE 802.11 A-MSDU and convert it to a list of 802.3 frames.
 * The @list will be empty अगर the decode fails. The @skb must be fully
 * header-less beक्रमe being passed in here; it is मुक्तd in this function.
 *
 * @skb: The input A-MSDU frame without any headers.
 * @list: The output list of 802.3 frames. It must be allocated and
 *	initialized by the caller.
 * @addr: The device MAC address.
 * @अगरtype: The device पूर्णांकerface type.
 * @extra_headroom: The hardware extra headroom क्रम SKBs in the @list.
 * @check_da: DA to check in the inner ethernet header, or शून्य
 * @check_sa: SA to check in the inner ethernet header, or शून्य
 */
व्योम ieee80211_amsdu_to_8023s(काष्ठा sk_buff *skb, काष्ठा sk_buff_head *list,
			      स्थिर u8 *addr, क्रमागत nl80211_अगरtype अगरtype,
			      स्थिर अचिन्हित पूर्णांक extra_headroom,
			      स्थिर u8 *check_da, स्थिर u8 *check_sa);

/**
 * cfg80211_classअगरy8021d - determine the 802.1p/1d tag क्रम a data frame
 * @skb: the data frame
 * @qos_map: Interworking QoS mapping or %शून्य अगर not in use
 * Return: The 802.1p/1d tag.
 */
अचिन्हित पूर्णांक cfg80211_classअगरy8021d(काष्ठा sk_buff *skb,
				    काष्ठा cfg80211_qos_map *qos_map);

/**
 * cfg80211_find_elem_match - match inक्रमmation element and byte array in data
 *
 * @eid: element ID
 * @ies: data consisting of IEs
 * @len: length of data
 * @match: byte array to match
 * @match_len: number of bytes in the match array
 * @match_offset: offset in the IE data where the byte array should match.
 *	Note the dअगरference to cfg80211_find_ie_match() which considers
 *	the offset to start from the element ID byte, but here we take
 *	the data portion instead.
 *
 * Return: %शून्य अगर the element ID could not be found or अगर
 * the element is invalid (claims to be दीर्घer than the given
 * data) or अगर the byte array करोesn't match; otherwise वापस the
 * requested element काष्ठा.
 *
 * Note: There are no checks on the element length other than
 * having to fit पूर्णांकo the given data and being large enough क्रम the
 * byte array to match.
 */
स्थिर काष्ठा element *
cfg80211_find_elem_match(u8 eid, स्थिर u8 *ies, अचिन्हित पूर्णांक len,
			 स्थिर u8 *match, अचिन्हित पूर्णांक match_len,
			 अचिन्हित पूर्णांक match_offset);

/**
 * cfg80211_find_ie_match - match inक्रमmation element and byte array in data
 *
 * @eid: element ID
 * @ies: data consisting of IEs
 * @len: length of data
 * @match: byte array to match
 * @match_len: number of bytes in the match array
 * @match_offset: offset in the IE where the byte array should match.
 *	If match_len is zero, this must also be set to zero.
 *	Otherwise this must be set to 2 or more, because the first
 *	byte is the element id, which is alपढ़ोy compared to eid, and
 *	the second byte is the IE length.
 *
 * Return: %शून्य अगर the element ID could not be found or अगर
 * the element is invalid (claims to be दीर्घer than the given
 * data) or अगर the byte array करोesn't match, or a poपूर्णांकer to the first
 * byte of the requested element, that is the byte containing the
 * element ID.
 *
 * Note: There are no checks on the element length other than
 * having to fit पूर्णांकo the given data and being large enough क्रम the
 * byte array to match.
 */
अटल अंतरभूत स्थिर u8 *
cfg80211_find_ie_match(u8 eid, स्थिर u8 *ies, अचिन्हित पूर्णांक len,
		       स्थिर u8 *match, अचिन्हित पूर्णांक match_len,
		       अचिन्हित पूर्णांक match_offset)
अणु
	/* match_offset can't be smaller than 2, unless match_len is
	 * zero, in which हाल match_offset must be zero as well.
	 */
	अगर (WARN_ON((match_len && match_offset < 2) ||
		    (!match_len && match_offset)))
		वापस शून्य;

	वापस (व्योम *)cfg80211_find_elem_match(eid, ies, len,
						match, match_len,
						match_offset ?
							match_offset - 2 : 0);
पूर्ण

/**
 * cfg80211_find_elem - find inक्रमmation element in data
 *
 * @eid: element ID
 * @ies: data consisting of IEs
 * @len: length of data
 *
 * Return: %शून्य अगर the element ID could not be found or अगर
 * the element is invalid (claims to be दीर्घer than the given
 * data) or अगर the byte array करोesn't match; otherwise वापस the
 * requested element काष्ठा.
 *
 * Note: There are no checks on the element length other than
 * having to fit पूर्णांकo the given data.
 */
अटल अंतरभूत स्थिर काष्ठा element *
cfg80211_find_elem(u8 eid, स्थिर u8 *ies, पूर्णांक len)
अणु
	वापस cfg80211_find_elem_match(eid, ies, len, शून्य, 0, 0);
पूर्ण

/**
 * cfg80211_find_ie - find inक्रमmation element in data
 *
 * @eid: element ID
 * @ies: data consisting of IEs
 * @len: length of data
 *
 * Return: %शून्य अगर the element ID could not be found or अगर
 * the element is invalid (claims to be दीर्घer than the given
 * data), or a poपूर्णांकer to the first byte of the requested
 * element, that is the byte containing the element ID.
 *
 * Note: There are no checks on the element length other than
 * having to fit पूर्णांकo the given data.
 */
अटल अंतरभूत स्थिर u8 *cfg80211_find_ie(u8 eid, स्थिर u8 *ies, पूर्णांक len)
अणु
	वापस cfg80211_find_ie_match(eid, ies, len, शून्य, 0, 0);
पूर्ण

/**
 * cfg80211_find_ext_elem - find inक्रमmation element with EID Extension in data
 *
 * @ext_eid: element ID Extension
 * @ies: data consisting of IEs
 * @len: length of data
 *
 * Return: %शून्य अगर the etended element could not be found or अगर
 * the element is invalid (claims to be दीर्घer than the given
 * data) or अगर the byte array करोesn't match; otherwise वापस the
 * requested element काष्ठा.
 *
 * Note: There are no checks on the element length other than
 * having to fit पूर्णांकo the given data.
 */
अटल अंतरभूत स्थिर काष्ठा element *
cfg80211_find_ext_elem(u8 ext_eid, स्थिर u8 *ies, पूर्णांक len)
अणु
	वापस cfg80211_find_elem_match(WLAN_EID_EXTENSION, ies, len,
					&ext_eid, 1, 0);
पूर्ण

/**
 * cfg80211_find_ext_ie - find inक्रमmation element with EID Extension in data
 *
 * @ext_eid: element ID Extension
 * @ies: data consisting of IEs
 * @len: length of data
 *
 * Return: %शून्य अगर the extended element ID could not be found or अगर
 * the element is invalid (claims to be दीर्घer than the given
 * data), or a poपूर्णांकer to the first byte of the requested
 * element, that is the byte containing the element ID.
 *
 * Note: There are no checks on the element length other than
 * having to fit पूर्णांकo the given data.
 */
अटल अंतरभूत स्थिर u8 *cfg80211_find_ext_ie(u8 ext_eid, स्थिर u8 *ies, पूर्णांक len)
अणु
	वापस cfg80211_find_ie_match(WLAN_EID_EXTENSION, ies, len,
				      &ext_eid, 1, 2);
पूर्ण

/**
 * cfg80211_find_venकरोr_elem - find venकरोr specअगरic inक्रमmation element in data
 *
 * @oui: venकरोr OUI
 * @oui_type: venकरोr-specअगरic OUI type (must be < 0xff), negative means any
 * @ies: data consisting of IEs
 * @len: length of data
 *
 * Return: %शून्य अगर the venकरोr specअगरic element ID could not be found or अगर the
 * element is invalid (claims to be दीर्घer than the given data); otherwise
 * वापस the element काष्ठाure क्रम the requested element.
 *
 * Note: There are no checks on the element length other than having to fit पूर्णांकo
 * the given data.
 */
स्थिर काष्ठा element *cfg80211_find_venकरोr_elem(अचिन्हित पूर्णांक oui, पूर्णांक oui_type,
						स्थिर u8 *ies,
						अचिन्हित पूर्णांक len);

/**
 * cfg80211_find_venकरोr_ie - find venकरोr specअगरic inक्रमmation element in data
 *
 * @oui: venकरोr OUI
 * @oui_type: venकरोr-specअगरic OUI type (must be < 0xff), negative means any
 * @ies: data consisting of IEs
 * @len: length of data
 *
 * Return: %शून्य अगर the venकरोr specअगरic element ID could not be found or अगर the
 * element is invalid (claims to be दीर्घer than the given data), or a poपूर्णांकer to
 * the first byte of the requested element, that is the byte containing the
 * element ID.
 *
 * Note: There are no checks on the element length other than having to fit पूर्णांकo
 * the given data.
 */
अटल अंतरभूत स्थिर u8 *
cfg80211_find_venकरोr_ie(अचिन्हित पूर्णांक oui, पूर्णांक oui_type,
			स्थिर u8 *ies, अचिन्हित पूर्णांक len)
अणु
	वापस (व्योम *)cfg80211_find_venकरोr_elem(oui, oui_type, ies, len);
पूर्ण

/**
 * cfg80211_send_layer2_update - send layer 2 update frame
 *
 * @dev: network device
 * @addr: STA MAC address
 *
 * Wireless drivers can use this function to update क्रमwarding tables in bridge
 * devices upon STA association.
 */
व्योम cfg80211_send_layer2_update(काष्ठा net_device *dev, स्थिर u8 *addr);

/**
 * DOC: Regulatory enक्रमcement infraकाष्ठाure
 *
 * TODO
 */

/**
 * regulatory_hपूर्णांक - driver hपूर्णांक to the wireless core a regulatory करोमुख्य
 * @wiphy: the wireless device giving the hपूर्णांक (used only क्रम reporting
 *	conflicts)
 * @alpha2: the ISO/IEC 3166 alpha2 the driver claims its regulatory करोमुख्य
 *	should be in. If @rd is set this should be शून्य. Note that अगर you
 *	set this to शून्य you should still set rd->alpha2 to some accepted
 *	alpha2.
 *
 * Wireless drivers can use this function to hपूर्णांक to the wireless core
 * what it believes should be the current regulatory करोमुख्य by
 * giving it an ISO/IEC 3166 alpha2 country code it knows its regulatory
 * करोमुख्य should be in or by providing a completely build regulatory करोमुख्य.
 * If the driver provides an ISO/IEC 3166 alpha2 userspace will be queried
 * क्रम a regulatory करोमुख्य काष्ठाure क्रम the respective country.
 *
 * The wiphy must have been रेजिस्टरed to cfg80211 prior to this call.
 * For cfg80211 drivers this means you must first use wiphy_रेजिस्टर(),
 * क्रम mac80211 drivers you must first use ieee80211_रेजिस्टर_hw().
 *
 * Drivers should check the वापस value, its possible you can get
 * an -ENOMEM.
 *
 * Return: 0 on success. -ENOMEM.
 */
पूर्णांक regulatory_hपूर्णांक(काष्ठा wiphy *wiphy, स्थिर अक्षर *alpha2);

/**
 * regulatory_set_wiphy_regd - set regकरोm info क्रम self managed drivers
 * @wiphy: the wireless device we want to process the regulatory करोमुख्य on
 * @rd: the regulatory करोमुख्य inक्रमmम_से_पn to use क्रम this wiphy
 *
 * Set the regulatory करोमुख्य inक्रमmation क्रम self-managed wiphys, only they
 * may use this function. See %REGULATORY_WIPHY_SELF_MANAGED क्रम more
 * inक्रमmation.
 *
 * Return: 0 on success. -EINVAL, -EPERM
 */
पूर्णांक regulatory_set_wiphy_regd(काष्ठा wiphy *wiphy,
			      काष्ठा ieee80211_regकरोमुख्य *rd);

/**
 * regulatory_set_wiphy_regd_sync - set regकरोm क्रम self-managed drivers
 * @wiphy: the wireless device we want to process the regulatory करोमुख्य on
 * @rd: the regulatory करोमुख्य inक्रमmation to use क्रम this wiphy
 *
 * This functions requires the RTNL and the wiphy mutex to be held and
 * applies the new regकरोमुख्य synchronously to this wiphy. For more details
 * see regulatory_set_wiphy_regd().
 *
 * Return: 0 on success. -EINVAL, -EPERM
 */
पूर्णांक regulatory_set_wiphy_regd_sync(काष्ठा wiphy *wiphy,
				   काष्ठा ieee80211_regकरोमुख्य *rd);

/**
 * wiphy_apply_custom_regulatory - apply a custom driver regulatory करोमुख्य
 * @wiphy: the wireless device we want to process the regulatory करोमुख्य on
 * @regd: the custom regulatory करोमुख्य to use क्रम this wiphy
 *
 * Drivers can someबार have custom regulatory करोमुख्यs which करो not apply
 * to a specअगरic country. Drivers can use this to apply such custom regulatory
 * करोमुख्यs. This routine must be called prior to wiphy registration. The
 * custom regulatory करोमुख्य will be trusted completely and as such previous
 * शेष channel settings will be disregarded. If no rule is found क्रम a
 * channel on the regulatory करोमुख्य the channel will be disabled.
 * Drivers using this क्रम a wiphy should also set the wiphy flag
 * REGULATORY_CUSTOM_REG or cfg80211 will set it क्रम the wiphy
 * that called this helper.
 */
व्योम wiphy_apply_custom_regulatory(काष्ठा wiphy *wiphy,
				   स्थिर काष्ठा ieee80211_regकरोमुख्य *regd);

/**
 * freq_reg_info - get regulatory inक्रमmation क्रम the given frequency
 * @wiphy: the wiphy क्रम which we want to process this rule क्रम
 * @center_freq: Frequency in KHz क्रम which we want regulatory inक्रमmation क्रम
 *
 * Use this function to get the regulatory rule क्रम a specअगरic frequency on
 * a given wireless device. If the device has a specअगरic regulatory करोमुख्य
 * it wants to follow we respect that unless a country IE has been received
 * and processed alपढ़ोy.
 *
 * Return: A valid poपूर्णांकer, or, when an error occurs, क्रम example अगर no rule
 * can be found, the वापस value is encoded using ERR_PTR(). Use IS_ERR() to
 * check and PTR_ERR() to obtain the numeric वापस value. The numeric वापस
 * value will be -दुस्फल अगर we determine the given center_freq करोes not even
 * have a regulatory rule क्रम a frequency range in the center_freq's band.
 * See freq_in_rule_band() क्रम our current definition of a band -- this is
 * purely subjective and right now it's 802.11 specअगरic.
 */
स्थिर काष्ठा ieee80211_reg_rule *freq_reg_info(काष्ठा wiphy *wiphy,
					       u32 center_freq);

/**
 * reg_initiator_name - map regulatory request initiator क्रमागत to name
 * @initiator: the regulatory request initiator
 *
 * You can use this to map the regulatory request initiator क्रमागत to a
 * proper string representation.
 */
स्थिर अक्षर *reg_initiator_name(क्रमागत nl80211_reg_initiator initiator);

/**
 * regulatory_pre_cac_allowed - check अगर pre-CAC allowed in the current regकरोm
 * @wiphy: wiphy क्रम which pre-CAC capability is checked.
 *
 * Pre-CAC is allowed only in some regकरोमुख्यs (notable ETSI).
 */
bool regulatory_pre_cac_allowed(काष्ठा wiphy *wiphy);

/**
 * DOC: Internal regulatory db functions
 *
 */

/**
 * reg_query_regdb_wmm -  Query पूर्णांकernal regulatory db क्रम wmm rule
 * Regulatory self-managed driver can use it to proactively
 *
 * @alpha2: the ISO/IEC 3166 alpha2 wmm rule to be queried.
 * @freq: the freqency(in MHz) to be queried.
 * @rule: poपूर्णांकer to store the wmm rule from the regulatory db.
 *
 * Self-managed wireless drivers can use this function to  query
 * the पूर्णांकernal regulatory database to check whether the given
 * ISO/IEC 3166 alpha2 country and freq have wmm rule limitations.
 *
 * Drivers should check the वापस value, its possible you can get
 * an -ENODATA.
 *
 * Return: 0 on success. -ENODATA.
 */
पूर्णांक reg_query_regdb_wmm(अक्षर *alpha2, पूर्णांक freq,
			काष्ठा ieee80211_reg_rule *rule);

/*
 * callbacks क्रम asynchronous cfg80211 methods, notअगरication
 * functions and BSS handling helpers
 */

/**
 * cfg80211_scan_करोne - notअगरy that scan finished
 *
 * @request: the corresponding scan request
 * @info: inक्रमmation about the completed scan
 */
व्योम cfg80211_scan_करोne(काष्ठा cfg80211_scan_request *request,
			काष्ठा cfg80211_scan_info *info);

/**
 * cfg80211_sched_scan_results - notअगरy that new scan results are available
 *
 * @wiphy: the wiphy which got scheduled scan results
 * @reqid: identअगरier क्रम the related scheduled scan request
 */
व्योम cfg80211_sched_scan_results(काष्ठा wiphy *wiphy, u64 reqid);

/**
 * cfg80211_sched_scan_stopped - notअगरy that the scheduled scan has stopped
 *
 * @wiphy: the wiphy on which the scheduled scan stopped
 * @reqid: identअगरier क्रम the related scheduled scan request
 *
 * The driver can call this function to inक्रमm cfg80211 that the
 * scheduled scan had to be stopped, क्रम whatever reason.  The driver
 * is then called back via the sched_scan_stop operation when करोne.
 */
व्योम cfg80211_sched_scan_stopped(काष्ठा wiphy *wiphy, u64 reqid);

/**
 * cfg80211_sched_scan_stopped_locked - notअगरy that the scheduled scan has stopped
 *
 * @wiphy: the wiphy on which the scheduled scan stopped
 * @reqid: identअगरier क्रम the related scheduled scan request
 *
 * The driver can call this function to inक्रमm cfg80211 that the
 * scheduled scan had to be stopped, क्रम whatever reason.  The driver
 * is then called back via the sched_scan_stop operation when करोne.
 * This function should be called with the wiphy mutex held.
 */
व्योम cfg80211_sched_scan_stopped_locked(काष्ठा wiphy *wiphy, u64 reqid);

/**
 * cfg80211_inक्रमm_bss_frame_data - inक्रमm cfg80211 of a received BSS frame
 * @wiphy: the wiphy reporting the BSS
 * @data: the BSS metadata
 * @mgmt: the management frame (probe response or beacon)
 * @len: length of the management frame
 * @gfp: context flags
 *
 * This inक्रमms cfg80211 that BSS inक्रमmation was found and
 * the BSS should be updated/added.
 *
 * Return: A referenced काष्ठा, must be released with cfg80211_put_bss()!
 * Or %शून्य on error.
 */
काष्ठा cfg80211_bss * __must_check
cfg80211_inक्रमm_bss_frame_data(काष्ठा wiphy *wiphy,
			       काष्ठा cfg80211_inक्रमm_bss *data,
			       काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len,
			       gfp_t gfp);

अटल अंतरभूत काष्ठा cfg80211_bss * __must_check
cfg80211_inक्रमm_bss_width_frame(काष्ठा wiphy *wiphy,
				काष्ठा ieee80211_channel *rx_channel,
				क्रमागत nl80211_bss_scan_width scan_width,
				काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len,
				s32 संकेत, gfp_t gfp)
अणु
	काष्ठा cfg80211_inक्रमm_bss data = अणु
		.chan = rx_channel,
		.scan_width = scan_width,
		.संकेत = संकेत,
	पूर्ण;

	वापस cfg80211_inक्रमm_bss_frame_data(wiphy, &data, mgmt, len, gfp);
पूर्ण

अटल अंतरभूत काष्ठा cfg80211_bss * __must_check
cfg80211_inक्रमm_bss_frame(काष्ठा wiphy *wiphy,
			  काष्ठा ieee80211_channel *rx_channel,
			  काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len,
			  s32 संकेत, gfp_t gfp)
अणु
	काष्ठा cfg80211_inक्रमm_bss data = अणु
		.chan = rx_channel,
		.scan_width = NL80211_BSS_CHAN_WIDTH_20,
		.संकेत = संकेत,
	पूर्ण;

	वापस cfg80211_inक्रमm_bss_frame_data(wiphy, &data, mgmt, len, gfp);
पूर्ण

/**
 * cfg80211_gen_new_bssid - generate a nontransmitted BSSID क्रम multi-BSSID
 * @bssid: transmitter BSSID
 * @max_bssid: max BSSID indicator, taken from Multiple BSSID element
 * @mbssid_index: BSSID index, taken from Multiple BSSID index element
 * @new_bssid: calculated nontransmitted BSSID
 */
अटल अंतरभूत व्योम cfg80211_gen_new_bssid(स्थिर u8 *bssid, u8 max_bssid,
					  u8 mbssid_index, u8 *new_bssid)
अणु
	u64 bssid_u64 = ether_addr_to_u64(bssid);
	u64 mask = GENMASK_ULL(max_bssid - 1, 0);
	u64 new_bssid_u64;

	new_bssid_u64 = bssid_u64 & ~mask;

	new_bssid_u64 |= ((bssid_u64 & mask) + mbssid_index) & mask;

	u64_to_ether_addr(new_bssid_u64, new_bssid);
पूर्ण

/**
 * cfg80211_is_element_inherited - वापसs अगर element ID should be inherited
 * @element: element to check
 * @non_inherit_element: non inheritance element
 */
bool cfg80211_is_element_inherited(स्थिर काष्ठा element *element,
				   स्थिर काष्ठा element *non_inherit_element);

/**
 * cfg80211_merge_profile - merges a MBSSID profile अगर it is split between IEs
 * @ie: ies
 * @ielen: length of IEs
 * @mbssid_elem: current MBSSID element
 * @sub_elem: current MBSSID subelement (profile)
 * @merged_ie: location of the merged profile
 * @max_copy_len: max merged profile length
 */
माप_प्रकार cfg80211_merge_profile(स्थिर u8 *ie, माप_प्रकार ielen,
			      स्थिर काष्ठा element *mbssid_elem,
			      स्थिर काष्ठा element *sub_elem,
			      u8 *merged_ie, माप_प्रकार max_copy_len);

/**
 * क्रमागत cfg80211_bss_frame_type - frame type that the BSS data came from
 * @CFG80211_BSS_FTYPE_UNKNOWN: driver करोesn't know whether the data is
 *	from a beacon or probe response
 * @CFG80211_BSS_FTYPE_BEACON: data comes from a beacon
 * @CFG80211_BSS_FTYPE_PRESP: data comes from a probe response
 */
क्रमागत cfg80211_bss_frame_type अणु
	CFG80211_BSS_FTYPE_UNKNOWN,
	CFG80211_BSS_FTYPE_BEACON,
	CFG80211_BSS_FTYPE_PRESP,
पूर्ण;

/**
 * cfg80211_inक्रमm_bss_data - inक्रमm cfg80211 of a new BSS
 *
 * @wiphy: the wiphy reporting the BSS
 * @data: the BSS metadata
 * @ftype: frame type (अगर known)
 * @bssid: the BSSID of the BSS
 * @tsf: the TSF sent by the peer in the beacon/probe response (or 0)
 * @capability: the capability field sent by the peer
 * @beacon_पूर्णांकerval: the beacon पूर्णांकerval announced by the peer
 * @ie: additional IEs sent by the peer
 * @ielen: length of the additional IEs
 * @gfp: context flags
 *
 * This inक्रमms cfg80211 that BSS inक्रमmation was found and
 * the BSS should be updated/added.
 *
 * Return: A referenced काष्ठा, must be released with cfg80211_put_bss()!
 * Or %शून्य on error.
 */
काष्ठा cfg80211_bss * __must_check
cfg80211_inक्रमm_bss_data(काष्ठा wiphy *wiphy,
			 काष्ठा cfg80211_inक्रमm_bss *data,
			 क्रमागत cfg80211_bss_frame_type ftype,
			 स्थिर u8 *bssid, u64 tsf, u16 capability,
			 u16 beacon_पूर्णांकerval, स्थिर u8 *ie, माप_प्रकार ielen,
			 gfp_t gfp);

अटल अंतरभूत काष्ठा cfg80211_bss * __must_check
cfg80211_inक्रमm_bss_width(काष्ठा wiphy *wiphy,
			  काष्ठा ieee80211_channel *rx_channel,
			  क्रमागत nl80211_bss_scan_width scan_width,
			  क्रमागत cfg80211_bss_frame_type ftype,
			  स्थिर u8 *bssid, u64 tsf, u16 capability,
			  u16 beacon_पूर्णांकerval, स्थिर u8 *ie, माप_प्रकार ielen,
			  s32 संकेत, gfp_t gfp)
अणु
	काष्ठा cfg80211_inक्रमm_bss data = अणु
		.chan = rx_channel,
		.scan_width = scan_width,
		.संकेत = संकेत,
	पूर्ण;

	वापस cfg80211_inक्रमm_bss_data(wiphy, &data, ftype, bssid, tsf,
					capability, beacon_पूर्णांकerval, ie, ielen,
					gfp);
पूर्ण

अटल अंतरभूत काष्ठा cfg80211_bss * __must_check
cfg80211_inक्रमm_bss(काष्ठा wiphy *wiphy,
		    काष्ठा ieee80211_channel *rx_channel,
		    क्रमागत cfg80211_bss_frame_type ftype,
		    स्थिर u8 *bssid, u64 tsf, u16 capability,
		    u16 beacon_पूर्णांकerval, स्थिर u8 *ie, माप_प्रकार ielen,
		    s32 संकेत, gfp_t gfp)
अणु
	काष्ठा cfg80211_inक्रमm_bss data = अणु
		.chan = rx_channel,
		.scan_width = NL80211_BSS_CHAN_WIDTH_20,
		.संकेत = संकेत,
	पूर्ण;

	वापस cfg80211_inक्रमm_bss_data(wiphy, &data, ftype, bssid, tsf,
					capability, beacon_पूर्णांकerval, ie, ielen,
					gfp);
पूर्ण

/**
 * cfg80211_get_bss - get a BSS reference
 * @wiphy: the wiphy this BSS काष्ठा beदीर्घs to
 * @channel: the channel to search on (or %शून्य)
 * @bssid: the desired BSSID (or %शून्य)
 * @ssid: the desired SSID (or %शून्य)
 * @ssid_len: length of the SSID (or 0)
 * @bss_type: type of BSS, see &क्रमागत ieee80211_bss_type
 * @privacy: privacy filter, see &क्रमागत ieee80211_privacy
 */
काष्ठा cfg80211_bss *cfg80211_get_bss(काष्ठा wiphy *wiphy,
				      काष्ठा ieee80211_channel *channel,
				      स्थिर u8 *bssid,
				      स्थिर u8 *ssid, माप_प्रकार ssid_len,
				      क्रमागत ieee80211_bss_type bss_type,
				      क्रमागत ieee80211_privacy privacy);
अटल अंतरभूत काष्ठा cfg80211_bss *
cfg80211_get_ibss(काष्ठा wiphy *wiphy,
		  काष्ठा ieee80211_channel *channel,
		  स्थिर u8 *ssid, माप_प्रकार ssid_len)
अणु
	वापस cfg80211_get_bss(wiphy, channel, शून्य, ssid, ssid_len,
				IEEE80211_BSS_TYPE_IBSS,
				IEEE80211_PRIVACY_ANY);
पूर्ण

/**
 * cfg80211_ref_bss - reference BSS काष्ठा
 * @wiphy: the wiphy this BSS काष्ठा beदीर्घs to
 * @bss: the BSS काष्ठा to reference
 *
 * Increments the refcount of the given BSS काष्ठा.
 */
व्योम cfg80211_ref_bss(काष्ठा wiphy *wiphy, काष्ठा cfg80211_bss *bss);

/**
 * cfg80211_put_bss - unref BSS काष्ठा
 * @wiphy: the wiphy this BSS काष्ठा beदीर्घs to
 * @bss: the BSS काष्ठा
 *
 * Decrements the refcount of the given BSS काष्ठा.
 */
व्योम cfg80211_put_bss(काष्ठा wiphy *wiphy, काष्ठा cfg80211_bss *bss);

/**
 * cfg80211_unlink_bss - unlink BSS from पूर्णांकernal data काष्ठाures
 * @wiphy: the wiphy
 * @bss: the bss to हटाओ
 *
 * This function हटाओs the given BSS from the पूर्णांकernal data काष्ठाures
 * thereby making it no दीर्घer show up in scan results etc. Use this
 * function when you detect a BSS is gone. Normally BSSes will also समय
 * out, so it is not necessary to use this function at all.
 */
व्योम cfg80211_unlink_bss(काष्ठा wiphy *wiphy, काष्ठा cfg80211_bss *bss);

/**
 * cfg80211_bss_iter - iterate all BSS entries
 *
 * This function iterates over the BSS entries associated with the given wiphy
 * and calls the callback क्रम the iterated BSS. The iterator function is not
 * allowed to call functions that might modअगरy the पूर्णांकernal state of the BSS DB.
 *
 * @wiphy: the wiphy
 * @chandef: अगर given, the iterator function will be called only अगर the channel
 *     of the currently iterated BSS is a subset of the given channel.
 * @iter: the iterator function to call
 * @iter_data: an argument to the iterator function
 */
व्योम cfg80211_bss_iter(काष्ठा wiphy *wiphy,
		       काष्ठा cfg80211_chan_def *chandef,
		       व्योम (*iter)(काष्ठा wiphy *wiphy,
				    काष्ठा cfg80211_bss *bss,
				    व्योम *data),
		       व्योम *iter_data);

अटल अंतरभूत क्रमागत nl80211_bss_scan_width
cfg80211_chandef_to_scan_width(स्थिर काष्ठा cfg80211_chan_def *chandef)
अणु
	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_5:
		वापस NL80211_BSS_CHAN_WIDTH_5;
	हाल NL80211_CHAN_WIDTH_10:
		वापस NL80211_BSS_CHAN_WIDTH_10;
	शेष:
		वापस NL80211_BSS_CHAN_WIDTH_20;
	पूर्ण
पूर्ण

/**
 * cfg80211_rx_mlme_mgmt - notअगरication of processed MLME management frame
 * @dev: network device
 * @buf: authentication frame (header + body)
 * @len: length of the frame data
 *
 * This function is called whenever an authentication, disassociation or
 * deauthentication frame has been received and processed in station mode.
 * After being asked to authenticate via cfg80211_ops::auth() the driver must
 * call either this function or cfg80211_auth_समयout().
 * After being asked to associate via cfg80211_ops::assoc() the driver must
 * call either this function or cfg80211_auth_समयout().
 * While connected, the driver must calls this क्रम received and processed
 * disassociation and deauthentication frames. If the frame couldn't be used
 * because it was unरक्षित, the driver must call the function
 * cfg80211_rx_unprot_mlme_mgmt() instead.
 *
 * This function may sleep. The caller must hold the corresponding wdev's mutex.
 */
व्योम cfg80211_rx_mlme_mgmt(काष्ठा net_device *dev, स्थिर u8 *buf, माप_प्रकार len);

/**
 * cfg80211_auth_समयout - notअगरication of समयd out authentication
 * @dev: network device
 * @addr: The MAC address of the device with which the authentication समयd out
 *
 * This function may sleep. The caller must hold the corresponding wdev's
 * mutex.
 */
व्योम cfg80211_auth_समयout(काष्ठा net_device *dev, स्थिर u8 *addr);

/**
 * cfg80211_rx_assoc_resp - notअगरication of processed association response
 * @dev: network device
 * @bss: the BSS that association was requested with, ownership of the poपूर्णांकer
 *	moves to cfg80211 in this call
 * @buf: (Re)Association Response frame (header + body)
 * @len: length of the frame data
 * @uapsd_queues: biपंचांगap of queues configured क्रम uapsd. Same क्रमmat
 *	as the AC biपंचांगap in the QoS info field
 * @req_ies: inक्रमmation elements from the (Re)Association Request frame
 * @req_ies_len: length of req_ies data
 *
 * After being asked to associate via cfg80211_ops::assoc() the driver must
 * call either this function or cfg80211_auth_समयout().
 *
 * This function may sleep. The caller must hold the corresponding wdev's mutex.
 */
व्योम cfg80211_rx_assoc_resp(काष्ठा net_device *dev,
			    काष्ठा cfg80211_bss *bss,
			    स्थिर u8 *buf, माप_प्रकार len,
			    पूर्णांक uapsd_queues,
			    स्थिर u8 *req_ies, माप_प्रकार req_ies_len);

/**
 * cfg80211_assoc_समयout - notअगरication of समयd out association
 * @dev: network device
 * @bss: The BSS entry with which association समयd out.
 *
 * This function may sleep. The caller must hold the corresponding wdev's mutex.
 */
व्योम cfg80211_assoc_समयout(काष्ठा net_device *dev, काष्ठा cfg80211_bss *bss);

/**
 * cfg80211_abanकरोn_assoc - notअगरy cfg80211 of abanकरोned association attempt
 * @dev: network device
 * @bss: The BSS entry with which association was abanकरोned.
 *
 * Call this whenever - क्रम reasons reported through other API, like deauth RX,
 * an association attempt was abanकरोned.
 * This function may sleep. The caller must hold the corresponding wdev's mutex.
 */
व्योम cfg80211_abanकरोn_assoc(काष्ठा net_device *dev, काष्ठा cfg80211_bss *bss);

/**
 * cfg80211_tx_mlme_mgmt - notअगरication of transmitted deauth/disassoc frame
 * @dev: network device
 * @buf: 802.11 frame (header + body)
 * @len: length of the frame data
 * @reconnect: immediate reconnect is desired (include the nl80211 attribute)
 *
 * This function is called whenever deauthentication has been processed in
 * station mode. This includes both received deauthentication frames and
 * locally generated ones. This function may sleep. The caller must hold the
 * corresponding wdev's mutex.
 */
व्योम cfg80211_tx_mlme_mgmt(काष्ठा net_device *dev, स्थिर u8 *buf, माप_प्रकार len,
			   bool reconnect);

/**
 * cfg80211_rx_unprot_mlme_mgmt - notअगरication of unरक्षित mlme mgmt frame
 * @dev: network device
 * @buf: received management frame (header + body)
 * @len: length of the frame data
 *
 * This function is called whenever a received deauthentication or dissassoc
 * frame has been dropped in station mode because of MFP being used but the
 * frame was not रक्षित. This is also used to notअगरy reception of a Beacon
 * frame that was dropped because it did not include a valid MME MIC जबतक
 * beacon protection was enabled (BIGTK configured in station mode).
 *
 * This function may sleep.
 */
व्योम cfg80211_rx_unprot_mlme_mgmt(काष्ठा net_device *dev,
				  स्थिर u8 *buf, माप_प्रकार len);

/**
 * cfg80211_michael_mic_failure - notअगरication of Michael MIC failure (TKIP)
 * @dev: network device
 * @addr: The source MAC address of the frame
 * @key_type: The key type that the received frame used
 * @key_id: Key identअगरier (0..3). Can be -1 अगर missing.
 * @tsc: The TSC value of the frame that generated the MIC failure (6 octets)
 * @gfp: allocation flags
 *
 * This function is called whenever the local MAC detects a MIC failure in a
 * received frame. This matches with MLME-MICHAELMICFAILURE.indication()
 * primitive.
 */
व्योम cfg80211_michael_mic_failure(काष्ठा net_device *dev, स्थिर u8 *addr,
				  क्रमागत nl80211_key_type key_type, पूर्णांक key_id,
				  स्थिर u8 *tsc, gfp_t gfp);

/**
 * cfg80211_ibss_joined - notअगरy cfg80211 that device joined an IBSS
 *
 * @dev: network device
 * @bssid: the BSSID of the IBSS joined
 * @channel: the channel of the IBSS joined
 * @gfp: allocation flags
 *
 * This function notअगरies cfg80211 that the device joined an IBSS or
 * चयनed to a dअगरferent BSSID. Beक्रमe this function can be called,
 * either a beacon has to have been received from the IBSS, or one of
 * the cfg80211_inक्रमm_bssअणु,_frameपूर्ण functions must have been called
 * with the locally generated beacon -- this guarantees that there is
 * always a scan result क्रम this IBSS. cfg80211 will handle the rest.
 */
व्योम cfg80211_ibss_joined(काष्ठा net_device *dev, स्थिर u8 *bssid,
			  काष्ठा ieee80211_channel *channel, gfp_t gfp);

/**
 * cfg80211_notअगरy_new_peer_candidate - notअगरy cfg80211 of a new mesh peer
 * 					candidate
 *
 * @dev: network device
 * @macaddr: the MAC address of the new candidate
 * @ie: inक्रमmation elements advertised by the peer candidate
 * @ie_len: length of the inक्रमmation elements buffer
 * @gfp: allocation flags
 *
 * This function notअगरies cfg80211 that the mesh peer candidate has been
 * detected, most likely via a beacon or, less likely, via a probe response.
 * cfg80211 then sends a notअगरication to userspace.
 */
व्योम cfg80211_notअगरy_new_peer_candidate(काष्ठा net_device *dev,
		स्थिर u8 *macaddr, स्थिर u8 *ie, u8 ie_len,
		पूर्णांक sig_dbm, gfp_t gfp);

/**
 * DOC: RFसमाप्त पूर्णांकegration
 *
 * RFसमाप्त पूर्णांकegration in cfg80211 is almost invisible to drivers,
 * as cfg80211 स्वतःmatically रेजिस्टरs an rfसमाप्त instance क्रम each
 * wireless device it knows about. Soft समाप्त is also translated
 * पूर्णांकo disconnecting and turning all पूर्णांकerfaces off, drivers are
 * expected to turn off the device when all पूर्णांकerfaces are करोwn.
 *
 * However, devices may have a hard RFसमाप्त line, in which हाल they
 * also need to पूर्णांकeract with the rfसमाप्त subप्रणाली, via cfg80211.
 * They can करो this with a few helper functions करोcumented here.
 */

/**
 * wiphy_rfसमाप्त_set_hw_state_reason - notअगरy cfg80211 about hw block state
 * @wiphy: the wiphy
 * @blocked: block status
 * @reason: one of reasons in &क्रमागत rfसमाप्त_hard_block_reasons
 */
व्योम wiphy_rfसमाप्त_set_hw_state_reason(काष्ठा wiphy *wiphy, bool blocked,
				      क्रमागत rfसमाप्त_hard_block_reasons reason);

अटल अंतरभूत व्योम wiphy_rfसमाप्त_set_hw_state(काष्ठा wiphy *wiphy, bool blocked)
अणु
	wiphy_rfसमाप्त_set_hw_state_reason(wiphy, blocked,
					 RFKILL_HARD_BLOCK_SIGNAL);
पूर्ण

/**
 * wiphy_rfसमाप्त_start_polling - start polling rfसमाप्त
 * @wiphy: the wiphy
 */
व्योम wiphy_rfसमाप्त_start_polling(काष्ठा wiphy *wiphy);

/**
 * wiphy_rfसमाप्त_stop_polling - stop polling rfसमाप्त
 * @wiphy: the wiphy
 */
व्योम wiphy_rfसमाप्त_stop_polling(काष्ठा wiphy *wiphy);

/**
 * DOC: Venकरोr commands
 *
 * Occasionally, there are special protocol or firmware features that
 * can't be implemented very खोलोly. For this and similar हालs, the
 * venकरोr command functionality allows implementing the features with
 * (typically बंदd-source) userspace and firmware, using nl80211 as
 * the configuration mechanism.
 *
 * A driver supporting venकरोr commands must रेजिस्टर them as an array
 * in काष्ठा wiphy, with handlers क्रम each one, each command has an
 * OUI and sub command ID to identअगरy it.
 *
 * Note that this feature should not be (ab)used to implement protocol
 * features that could खोलोly be shared across drivers. In particular,
 * it must never be required to use venकरोr commands to implement any
 * "normal" functionality that higher-level userspace like connection
 * managers etc. need.
 */

काष्ठा sk_buff *__cfg80211_alloc_reply_skb(काष्ठा wiphy *wiphy,
					   क्रमागत nl80211_commands cmd,
					   क्रमागत nl80211_attrs attr,
					   पूर्णांक approxlen);

काष्ठा sk_buff *__cfg80211_alloc_event_skb(काष्ठा wiphy *wiphy,
					   काष्ठा wireless_dev *wdev,
					   क्रमागत nl80211_commands cmd,
					   क्रमागत nl80211_attrs attr,
					   अचिन्हित पूर्णांक portid,
					   पूर्णांक venकरोr_event_idx,
					   पूर्णांक approxlen, gfp_t gfp);

व्योम __cfg80211_send_event_skb(काष्ठा sk_buff *skb, gfp_t gfp);

/**
 * cfg80211_venकरोr_cmd_alloc_reply_skb - allocate venकरोr command reply
 * @wiphy: the wiphy
 * @approxlen: an upper bound of the length of the data that will
 *	be put पूर्णांकo the skb
 *
 * This function allocates and pre-fills an skb क्रम a reply to
 * a venकरोr command. Since it is पूर्णांकended क्रम a reply, calling
 * it outside of a venकरोr command's करोit() operation is invalid.
 *
 * The वापसed skb is pre-filled with some identअगरying data in
 * a way that any data that is put पूर्णांकo the skb (with skb_put(),
 * nla_put() or similar) will end up being within the
 * %NL80211_ATTR_VENDOR_DATA attribute, so all that needs to be करोne
 * with the skb is adding data क्रम the corresponding userspace tool
 * which can then पढ़ो that data out of the venकरोr data attribute.
 * You must not modअगरy the skb in any other way.
 *
 * When करोne, call cfg80211_venकरोr_cmd_reply() with the skb and वापस
 * its error code as the result of the करोit() operation.
 *
 * Return: An allocated and pre-filled skb. %शून्य अगर any errors happen.
 */
अटल अंतरभूत काष्ठा sk_buff *
cfg80211_venकरोr_cmd_alloc_reply_skb(काष्ठा wiphy *wiphy, पूर्णांक approxlen)
अणु
	वापस __cfg80211_alloc_reply_skb(wiphy, NL80211_CMD_VENDOR,
					  NL80211_ATTR_VENDOR_DATA, approxlen);
पूर्ण

/**
 * cfg80211_venकरोr_cmd_reply - send the reply skb
 * @skb: The skb, must have been allocated with
 *	cfg80211_venकरोr_cmd_alloc_reply_skb()
 *
 * Since calling this function will usually be the last thing
 * beक्रमe वापसing from the venकरोr command करोit() you should
 * वापस the error code.  Note that this function consumes the
 * skb regardless of the वापस value.
 *
 * Return: An error code or 0 on success.
 */
पूर्णांक cfg80211_venकरोr_cmd_reply(काष्ठा sk_buff *skb);

/**
 * cfg80211_venकरोr_cmd_get_sender - get the current sender netlink ID
 * @wiphy: the wiphy
 *
 * Return the current netlink port ID in a venकरोr command handler.
 * Valid to call only there.
 */
अचिन्हित पूर्णांक cfg80211_venकरोr_cmd_get_sender(काष्ठा wiphy *wiphy);

/**
 * cfg80211_venकरोr_event_alloc - allocate venकरोr-specअगरic event skb
 * @wiphy: the wiphy
 * @wdev: the wireless device
 * @event_idx: index of the venकरोr event in the wiphy's venकरोr_events
 * @approxlen: an upper bound of the length of the data that will
 *	be put पूर्णांकo the skb
 * @gfp: allocation flags
 *
 * This function allocates and pre-fills an skb क्रम an event on the
 * venकरोr-specअगरic multicast group.
 *
 * If wdev != शून्य, both the अगरindex and identअगरier of the specअगरied
 * wireless device are added to the event message beक्रमe the venकरोr data
 * attribute.
 *
 * When करोne filling the skb, call cfg80211_venकरोr_event() with the
 * skb to send the event.
 *
 * Return: An allocated and pre-filled skb. %शून्य अगर any errors happen.
 */
अटल अंतरभूत काष्ठा sk_buff *
cfg80211_venकरोr_event_alloc(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
			     पूर्णांक approxlen, पूर्णांक event_idx, gfp_t gfp)
अणु
	वापस __cfg80211_alloc_event_skb(wiphy, wdev, NL80211_CMD_VENDOR,
					  NL80211_ATTR_VENDOR_DATA,
					  0, event_idx, approxlen, gfp);
पूर्ण

/**
 * cfg80211_venकरोr_event_alloc_ucast - alloc unicast venकरोr-specअगरic event skb
 * @wiphy: the wiphy
 * @wdev: the wireless device
 * @event_idx: index of the venकरोr event in the wiphy's venकरोr_events
 * @portid: port ID of the receiver
 * @approxlen: an upper bound of the length of the data that will
 *	be put पूर्णांकo the skb
 * @gfp: allocation flags
 *
 * This function allocates and pre-fills an skb क्रम an event to send to
 * a specअगरic (userland) socket. This socket would previously have been
 * obtained by cfg80211_venकरोr_cmd_get_sender(), and the caller MUST take
 * care to रेजिस्टर a netlink notअगरier to see when the socket बंदs.
 *
 * If wdev != शून्य, both the अगरindex and identअगरier of the specअगरied
 * wireless device are added to the event message beक्रमe the venकरोr data
 * attribute.
 *
 * When करोne filling the skb, call cfg80211_venकरोr_event() with the
 * skb to send the event.
 *
 * Return: An allocated and pre-filled skb. %शून्य अगर any errors happen.
 */
अटल अंतरभूत काष्ठा sk_buff *
cfg80211_venकरोr_event_alloc_ucast(काष्ठा wiphy *wiphy,
				  काष्ठा wireless_dev *wdev,
				  अचिन्हित पूर्णांक portid, पूर्णांक approxlen,
				  पूर्णांक event_idx, gfp_t gfp)
अणु
	वापस __cfg80211_alloc_event_skb(wiphy, wdev, NL80211_CMD_VENDOR,
					  NL80211_ATTR_VENDOR_DATA,
					  portid, event_idx, approxlen, gfp);
पूर्ण

/**
 * cfg80211_venकरोr_event - send the event
 * @skb: The skb, must have been allocated with cfg80211_venकरोr_event_alloc()
 * @gfp: allocation flags
 *
 * This function sends the given @skb, which must have been allocated
 * by cfg80211_venकरोr_event_alloc(), as an event. It always consumes it.
 */
अटल अंतरभूत व्योम cfg80211_venकरोr_event(काष्ठा sk_buff *skb, gfp_t gfp)
अणु
	__cfg80211_send_event_skb(skb, gfp);
पूर्ण

#अगर_घोषित CONFIG_NL80211_TESTMODE
/**
 * DOC: Test mode
 *
 * Test mode is a set of utility functions to allow drivers to
 * पूर्णांकeract with driver-specअगरic tools to aid, क्रम instance,
 * factory programming.
 *
 * This chapter describes how drivers पूर्णांकeract with it, क्रम more
 * inक्रमmation see the nl80211 book's chapter on it.
 */

/**
 * cfg80211_tesपंचांगode_alloc_reply_skb - allocate tesपंचांगode reply
 * @wiphy: the wiphy
 * @approxlen: an upper bound of the length of the data that will
 *	be put पूर्णांकo the skb
 *
 * This function allocates and pre-fills an skb क्रम a reply to
 * the tesपंचांगode command. Since it is पूर्णांकended क्रम a reply, calling
 * it outside of the @tesपंचांगode_cmd operation is invalid.
 *
 * The वापसed skb is pre-filled with the wiphy index and set up in
 * a way that any data that is put पूर्णांकo the skb (with skb_put(),
 * nla_put() or similar) will end up being within the
 * %NL80211_ATTR_TESTDATA attribute, so all that needs to be करोne
 * with the skb is adding data क्रम the corresponding userspace tool
 * which can then पढ़ो that data out of the testdata attribute. You
 * must not modअगरy the skb in any other way.
 *
 * When करोne, call cfg80211_tesपंचांगode_reply() with the skb and वापस
 * its error code as the result of the @tesपंचांगode_cmd operation.
 *
 * Return: An allocated and pre-filled skb. %शून्य अगर any errors happen.
 */
अटल अंतरभूत काष्ठा sk_buff *
cfg80211_tesपंचांगode_alloc_reply_skb(काष्ठा wiphy *wiphy, पूर्णांक approxlen)
अणु
	वापस __cfg80211_alloc_reply_skb(wiphy, NL80211_CMD_TESTMODE,
					  NL80211_ATTR_TESTDATA, approxlen);
पूर्ण

/**
 * cfg80211_tesपंचांगode_reply - send the reply skb
 * @skb: The skb, must have been allocated with
 *	cfg80211_tesपंचांगode_alloc_reply_skb()
 *
 * Since calling this function will usually be the last thing
 * beक्रमe वापसing from the @tesपंचांगode_cmd you should वापस
 * the error code.  Note that this function consumes the skb
 * regardless of the वापस value.
 *
 * Return: An error code or 0 on success.
 */
अटल अंतरभूत पूर्णांक cfg80211_tesपंचांगode_reply(काष्ठा sk_buff *skb)
अणु
	वापस cfg80211_venकरोr_cmd_reply(skb);
पूर्ण

/**
 * cfg80211_tesपंचांगode_alloc_event_skb - allocate tesपंचांगode event
 * @wiphy: the wiphy
 * @approxlen: an upper bound of the length of the data that will
 *	be put पूर्णांकo the skb
 * @gfp: allocation flags
 *
 * This function allocates and pre-fills an skb क्रम an event on the
 * tesपंचांगode multicast group.
 *
 * The वापसed skb is set up in the same way as with
 * cfg80211_tesपंचांगode_alloc_reply_skb() but prepared क्रम an event. As
 * there, you should simply add data to it that will then end up in the
 * %NL80211_ATTR_TESTDATA attribute. Again, you must not modअगरy the skb
 * in any other way.
 *
 * When करोne filling the skb, call cfg80211_tesपंचांगode_event() with the
 * skb to send the event.
 *
 * Return: An allocated and pre-filled skb. %शून्य अगर any errors happen.
 */
अटल अंतरभूत काष्ठा sk_buff *
cfg80211_tesपंचांगode_alloc_event_skb(काष्ठा wiphy *wiphy, पूर्णांक approxlen, gfp_t gfp)
अणु
	वापस __cfg80211_alloc_event_skb(wiphy, शून्य, NL80211_CMD_TESTMODE,
					  NL80211_ATTR_TESTDATA, 0, -1,
					  approxlen, gfp);
पूर्ण

/**
 * cfg80211_tesपंचांगode_event - send the event
 * @skb: The skb, must have been allocated with
 *	cfg80211_tesपंचांगode_alloc_event_skb()
 * @gfp: allocation flags
 *
 * This function sends the given @skb, which must have been allocated
 * by cfg80211_tesपंचांगode_alloc_event_skb(), as an event. It always
 * consumes it.
 */
अटल अंतरभूत व्योम cfg80211_tesपंचांगode_event(काष्ठा sk_buff *skb, gfp_t gfp)
अणु
	__cfg80211_send_event_skb(skb, gfp);
पूर्ण

#घोषणा CFG80211_TESTMODE_CMD(cmd)	.tesपंचांगode_cmd = (cmd),
#घोषणा CFG80211_TESTMODE_DUMP(cmd)	.tesपंचांगode_dump = (cmd),
#अन्यथा
#घोषणा CFG80211_TESTMODE_CMD(cmd)
#घोषणा CFG80211_TESTMODE_DUMP(cmd)
#पूर्ण_अगर

/**
 * काष्ठा cfg80211_fils_resp_params - FILS connection response params
 * @kek: KEK derived from a successful FILS connection (may be %शून्य)
 * @kek_len: Length of @fils_kek in octets
 * @update_erp_next_seq_num: Boolean value to specअगरy whether the value in
 *	@erp_next_seq_num is valid.
 * @erp_next_seq_num: The next sequence number to use in ERP message in
 *	FILS Authentication. This value should be specअगरied irrespective of the
 *	status क्रम a FILS connection.
 * @pmk: A new PMK अगर derived from a successful FILS connection (may be %शून्य).
 * @pmk_len: Length of @pmk in octets
 * @pmkid: A new PMKID अगर derived from a successful FILS connection or the PMKID
 *	used क्रम this FILS connection (may be %शून्य).
 */
काष्ठा cfg80211_fils_resp_params अणु
	स्थिर u8 *kek;
	माप_प्रकार kek_len;
	bool update_erp_next_seq_num;
	u16 erp_next_seq_num;
	स्थिर u8 *pmk;
	माप_प्रकार pmk_len;
	स्थिर u8 *pmkid;
पूर्ण;

/**
 * काष्ठा cfg80211_connect_resp_params - Connection response params
 * @status: Status code, %WLAN_STATUS_SUCCESS क्रम successful connection, use
 *	%WLAN_STATUS_UNSPECIFIED_FAILURE अगर your device cannot give you
 *	the real status code क्रम failures. If this call is used to report a
 *	failure due to a समयout (e.g., not receiving an Authentication frame
 *	from the AP) instead of an explicit rejection by the AP, -1 is used to
 *	indicate that this is a failure, but without a status code.
 *	@समयout_reason is used to report the reason क्रम the समयout in that
 *	हाल.
 * @bssid: The BSSID of the AP (may be %शून्य)
 * @bss: Entry of bss to which STA got connected to, can be obtained through
 *	cfg80211_get_bss() (may be %शून्य). But it is recommended to store the
 *	bss from the connect_request and hold a reference to it and वापस
 *	through this param to aव्योम a warning अगर the bss is expired during the
 *	connection, esp. क्रम those drivers implementing connect op.
 *	Only one parameter among @bssid and @bss needs to be specअगरied.
 * @req_ie: Association request IEs (may be %शून्य)
 * @req_ie_len: Association request IEs length
 * @resp_ie: Association response IEs (may be %शून्य)
 * @resp_ie_len: Association response IEs length
 * @fils: FILS connection response parameters.
 * @समयout_reason: Reason क्रम connection समयout. This is used when the
 *	connection fails due to a समयout instead of an explicit rejection from
 *	the AP. %NL80211_TIMEOUT_UNSPECIFIED is used when the समयout reason is
 *	not known. This value is used only अगर @status < 0 to indicate that the
 *	failure is due to a समयout and not due to explicit rejection by the AP.
 *	This value is ignored in other हालs (@status >= 0).
 */
काष्ठा cfg80211_connect_resp_params अणु
	पूर्णांक status;
	स्थिर u8 *bssid;
	काष्ठा cfg80211_bss *bss;
	स्थिर u8 *req_ie;
	माप_प्रकार req_ie_len;
	स्थिर u8 *resp_ie;
	माप_प्रकार resp_ie_len;
	काष्ठा cfg80211_fils_resp_params fils;
	क्रमागत nl80211_समयout_reason समयout_reason;
पूर्ण;

/**
 * cfg80211_connect_करोne - notअगरy cfg80211 of connection result
 *
 * @dev: network device
 * @params: connection response parameters
 * @gfp: allocation flags
 *
 * It should be called by the underlying driver once execution of the connection
 * request from connect() has been completed. This is similar to
 * cfg80211_connect_bss(), but takes a काष्ठाure poपूर्णांकer क्रम connection response
 * parameters. Only one of the functions among cfg80211_connect_bss(),
 * cfg80211_connect_result(), cfg80211_connect_समयout(),
 * and cfg80211_connect_करोne() should be called.
 */
व्योम cfg80211_connect_करोne(काष्ठा net_device *dev,
			   काष्ठा cfg80211_connect_resp_params *params,
			   gfp_t gfp);

/**
 * cfg80211_connect_bss - notअगरy cfg80211 of connection result
 *
 * @dev: network device
 * @bssid: the BSSID of the AP
 * @bss: Entry of bss to which STA got connected to, can be obtained through
 *	cfg80211_get_bss() (may be %शून्य). But it is recommended to store the
 *	bss from the connect_request and hold a reference to it and वापस
 *	through this param to aव्योम a warning अगर the bss is expired during the
 *	connection, esp. क्रम those drivers implementing connect op.
 *	Only one parameter among @bssid and @bss needs to be specअगरied.
 * @req_ie: association request IEs (maybe be %शून्य)
 * @req_ie_len: association request IEs length
 * @resp_ie: association response IEs (may be %शून्य)
 * @resp_ie_len: assoc response IEs length
 * @status: status code, %WLAN_STATUS_SUCCESS क्रम successful connection, use
 *	%WLAN_STATUS_UNSPECIFIED_FAILURE अगर your device cannot give you
 *	the real status code क्रम failures. If this call is used to report a
 *	failure due to a समयout (e.g., not receiving an Authentication frame
 *	from the AP) instead of an explicit rejection by the AP, -1 is used to
 *	indicate that this is a failure, but without a status code.
 *	@समयout_reason is used to report the reason क्रम the समयout in that
 *	हाल.
 * @gfp: allocation flags
 * @समयout_reason: reason क्रम connection समयout. This is used when the
 *	connection fails due to a समयout instead of an explicit rejection from
 *	the AP. %NL80211_TIMEOUT_UNSPECIFIED is used when the समयout reason is
 *	not known. This value is used only अगर @status < 0 to indicate that the
 *	failure is due to a समयout and not due to explicit rejection by the AP.
 *	This value is ignored in other हालs (@status >= 0).
 *
 * It should be called by the underlying driver once execution of the connection
 * request from connect() has been completed. This is similar to
 * cfg80211_connect_result(), but with the option of identअगरying the exact bss
 * entry क्रम the connection. Only one of the functions among
 * cfg80211_connect_bss(), cfg80211_connect_result(),
 * cfg80211_connect_समयout(), and cfg80211_connect_करोne() should be called.
 */
अटल अंतरभूत व्योम
cfg80211_connect_bss(काष्ठा net_device *dev, स्थिर u8 *bssid,
		     काष्ठा cfg80211_bss *bss, स्थिर u8 *req_ie,
		     माप_प्रकार req_ie_len, स्थिर u8 *resp_ie,
		     माप_प्रकार resp_ie_len, पूर्णांक status, gfp_t gfp,
		     क्रमागत nl80211_समयout_reason समयout_reason)
अणु
	काष्ठा cfg80211_connect_resp_params params;

	स_रखो(&params, 0, माप(params));
	params.status = status;
	params.bssid = bssid;
	params.bss = bss;
	params.req_ie = req_ie;
	params.req_ie_len = req_ie_len;
	params.resp_ie = resp_ie;
	params.resp_ie_len = resp_ie_len;
	params.समयout_reason = समयout_reason;

	cfg80211_connect_करोne(dev, &params, gfp);
पूर्ण

/**
 * cfg80211_connect_result - notअगरy cfg80211 of connection result
 *
 * @dev: network device
 * @bssid: the BSSID of the AP
 * @req_ie: association request IEs (maybe be %शून्य)
 * @req_ie_len: association request IEs length
 * @resp_ie: association response IEs (may be %शून्य)
 * @resp_ie_len: assoc response IEs length
 * @status: status code, %WLAN_STATUS_SUCCESS क्रम successful connection, use
 *	%WLAN_STATUS_UNSPECIFIED_FAILURE अगर your device cannot give you
 *	the real status code क्रम failures.
 * @gfp: allocation flags
 *
 * It should be called by the underlying driver once execution of the connection
 * request from connect() has been completed. This is similar to
 * cfg80211_connect_bss() which allows the exact bss entry to be specअगरied. Only
 * one of the functions among cfg80211_connect_bss(), cfg80211_connect_result(),
 * cfg80211_connect_समयout(), and cfg80211_connect_करोne() should be called.
 */
अटल अंतरभूत व्योम
cfg80211_connect_result(काष्ठा net_device *dev, स्थिर u8 *bssid,
			स्थिर u8 *req_ie, माप_प्रकार req_ie_len,
			स्थिर u8 *resp_ie, माप_प्रकार resp_ie_len,
			u16 status, gfp_t gfp)
अणु
	cfg80211_connect_bss(dev, bssid, शून्य, req_ie, req_ie_len, resp_ie,
			     resp_ie_len, status, gfp,
			     NL80211_TIMEOUT_UNSPECIFIED);
पूर्ण

/**
 * cfg80211_connect_समयout - notअगरy cfg80211 of connection समयout
 *
 * @dev: network device
 * @bssid: the BSSID of the AP
 * @req_ie: association request IEs (maybe be %शून्य)
 * @req_ie_len: association request IEs length
 * @gfp: allocation flags
 * @समयout_reason: reason क्रम connection समयout.
 *
 * It should be called by the underlying driver whenever connect() has failed
 * in a sequence where no explicit authentication/association rejection was
 * received from the AP. This could happen, e.g., due to not being able to send
 * out the Authentication or Association Request frame or timing out जबतक
 * रुकोing क्रम the response. Only one of the functions among
 * cfg80211_connect_bss(), cfg80211_connect_result(),
 * cfg80211_connect_समयout(), and cfg80211_connect_करोne() should be called.
 */
अटल अंतरभूत व्योम
cfg80211_connect_समयout(काष्ठा net_device *dev, स्थिर u8 *bssid,
			 स्थिर u8 *req_ie, माप_प्रकार req_ie_len, gfp_t gfp,
			 क्रमागत nl80211_समयout_reason समयout_reason)
अणु
	cfg80211_connect_bss(dev, bssid, शून्य, req_ie, req_ie_len, शून्य, 0, -1,
			     gfp, समयout_reason);
पूर्ण

/**
 * काष्ठा cfg80211_roam_info - driver initiated roaming inक्रमmation
 *
 * @channel: the channel of the new AP
 * @bss: entry of bss to which STA got roamed (may be %शून्य अगर %bssid is set)
 * @bssid: the BSSID of the new AP (may be %शून्य अगर %bss is set)
 * @req_ie: association request IEs (maybe be %शून्य)
 * @req_ie_len: association request IEs length
 * @resp_ie: association response IEs (may be %शून्य)
 * @resp_ie_len: assoc response IEs length
 * @fils: FILS related roaming inक्रमmation.
 */
काष्ठा cfg80211_roam_info अणु
	काष्ठा ieee80211_channel *channel;
	काष्ठा cfg80211_bss *bss;
	स्थिर u8 *bssid;
	स्थिर u8 *req_ie;
	माप_प्रकार req_ie_len;
	स्थिर u8 *resp_ie;
	माप_प्रकार resp_ie_len;
	काष्ठा cfg80211_fils_resp_params fils;
पूर्ण;

/**
 * cfg80211_roamed - notअगरy cfg80211 of roaming
 *
 * @dev: network device
 * @info: inक्रमmation about the new BSS. काष्ठा &cfg80211_roam_info.
 * @gfp: allocation flags
 *
 * This function may be called with the driver passing either the BSSID of the
 * new AP or passing the bss entry to aव्योम a race in समयout of the bss entry.
 * It should be called by the underlying driver whenever it roamed from one AP
 * to another जबतक connected. Drivers which have roaming implemented in
 * firmware should pass the bss entry to aव्योम a race in bss entry समयout where
 * the bss entry of the new AP is seen in the driver, but माला_लो समयd out by the
 * समय it is accessed in __cfg80211_roamed() due to delay in scheduling
 * rdev->event_work. In हाल of any failures, the reference is released
 * either in cfg80211_roamed() or in __cfg80211_romed(), Otherwise, it will be
 * released जबतक disconnecting from the current bss.
 */
व्योम cfg80211_roamed(काष्ठा net_device *dev, काष्ठा cfg80211_roam_info *info,
		     gfp_t gfp);

/**
 * cfg80211_port_authorized - notअगरy cfg80211 of successful security association
 *
 * @dev: network device
 * @bssid: the BSSID of the AP
 * @gfp: allocation flags
 *
 * This function should be called by a driver that supports 4 way handshake
 * offload after a security association was successfully established (i.e.,
 * the 4 way handshake was completed successfully). The call to this function
 * should be preceded with a call to cfg80211_connect_result(),
 * cfg80211_connect_करोne(), cfg80211_connect_bss() or cfg80211_roamed() to
 * indicate the 802.11 association.
 */
व्योम cfg80211_port_authorized(काष्ठा net_device *dev, स्थिर u8 *bssid,
			      gfp_t gfp);

/**
 * cfg80211_disconnected - notअगरy cfg80211 that connection was dropped
 *
 * @dev: network device
 * @ie: inक्रमmation elements of the deauth/disassoc frame (may be %शून्य)
 * @ie_len: length of IEs
 * @reason: reason code क्रम the disconnection, set it to 0 अगर unknown
 * @locally_generated: disconnection was requested locally
 * @gfp: allocation flags
 *
 * After it calls this function, the driver should enter an idle state
 * and not try to connect to any AP any more.
 */
व्योम cfg80211_disconnected(काष्ठा net_device *dev, u16 reason,
			   स्थिर u8 *ie, माप_प्रकार ie_len,
			   bool locally_generated, gfp_t gfp);

/**
 * cfg80211_पढ़ोy_on_channel - notअगरication of reमुख्य_on_channel start
 * @wdev: wireless device
 * @cookie: the request cookie
 * @chan: The current channel (from reमुख्य_on_channel request)
 * @duration: Duration in milliseconds that the driver पूर्णांकents to reमुख्य on the
 *	channel
 * @gfp: allocation flags
 */
व्योम cfg80211_पढ़ोy_on_channel(काष्ठा wireless_dev *wdev, u64 cookie,
			       काष्ठा ieee80211_channel *chan,
			       अचिन्हित पूर्णांक duration, gfp_t gfp);

/**
 * cfg80211_reमुख्य_on_channel_expired - reमुख्य_on_channel duration expired
 * @wdev: wireless device
 * @cookie: the request cookie
 * @chan: The current channel (from reमुख्य_on_channel request)
 * @gfp: allocation flags
 */
व्योम cfg80211_reमुख्य_on_channel_expired(काष्ठा wireless_dev *wdev, u64 cookie,
					काष्ठा ieee80211_channel *chan,
					gfp_t gfp);

/**
 * cfg80211_tx_mgmt_expired - tx_mgmt duration expired
 * @wdev: wireless device
 * @cookie: the requested cookie
 * @chan: The current channel (from tx_mgmt request)
 * @gfp: allocation flags
 */
व्योम cfg80211_tx_mgmt_expired(काष्ठा wireless_dev *wdev, u64 cookie,
			      काष्ठा ieee80211_channel *chan, gfp_t gfp);

/**
 * cfg80211_sinfo_alloc_tid_stats - allocate per-tid statistics.
 *
 * @sinfo: the station inक्रमmation
 * @gfp: allocation flags
 */
पूर्णांक cfg80211_sinfo_alloc_tid_stats(काष्ठा station_info *sinfo, gfp_t gfp);

/**
 * cfg80211_sinfo_release_content - release contents of station info
 * @sinfo: the station inक्रमmation
 *
 * Releases any potentially allocated sub-inक्रमmation of the station
 * inक्रमmation, but not the काष्ठा itself (since it's typically on
 * the stack.)
 */
अटल अंतरभूत व्योम cfg80211_sinfo_release_content(काष्ठा station_info *sinfo)
अणु
	kमुक्त(sinfo->pertid);
पूर्ण

/**
 * cfg80211_new_sta - notअगरy userspace about station
 *
 * @dev: the netdev
 * @mac_addr: the station's address
 * @sinfo: the station inक्रमmation
 * @gfp: allocation flags
 */
व्योम cfg80211_new_sta(काष्ठा net_device *dev, स्थिर u8 *mac_addr,
		      काष्ठा station_info *sinfo, gfp_t gfp);

/**
 * cfg80211_del_sta_sinfo - notअगरy userspace about deletion of a station
 * @dev: the netdev
 * @mac_addr: the station's address
 * @sinfo: the station inक्रमmation/statistics
 * @gfp: allocation flags
 */
व्योम cfg80211_del_sta_sinfo(काष्ठा net_device *dev, स्थिर u8 *mac_addr,
			    काष्ठा station_info *sinfo, gfp_t gfp);

/**
 * cfg80211_del_sta - notअगरy userspace about deletion of a station
 *
 * @dev: the netdev
 * @mac_addr: the station's address
 * @gfp: allocation flags
 */
अटल अंतरभूत व्योम cfg80211_del_sta(काष्ठा net_device *dev,
				    स्थिर u8 *mac_addr, gfp_t gfp)
अणु
	cfg80211_del_sta_sinfo(dev, mac_addr, शून्य, gfp);
पूर्ण

/**
 * cfg80211_conn_failed - connection request failed notअगरication
 *
 * @dev: the netdev
 * @mac_addr: the station's address
 * @reason: the reason क्रम connection failure
 * @gfp: allocation flags
 *
 * Whenever a station tries to connect to an AP and अगर the station
 * could not connect to the AP as the AP has rejected the connection
 * क्रम some reasons, this function is called.
 *
 * The reason क्रम connection failure can be any of the value from
 * nl80211_connect_failed_reason क्रमागत
 */
व्योम cfg80211_conn_failed(काष्ठा net_device *dev, स्थिर u8 *mac_addr,
			  क्रमागत nl80211_connect_failed_reason reason,
			  gfp_t gfp);

/**
 * cfg80211_rx_mgmt_khz - notअगरication of received, unprocessed management frame
 * @wdev: wireless device receiving the frame
 * @freq: Frequency on which the frame was received in KHz
 * @sig_dbm: संकेत strength in dBm, or 0 अगर unknown
 * @buf: Management frame (header + body)
 * @len: length of the frame data
 * @flags: flags, as defined in क्रमागत nl80211_rxmgmt_flags
 *
 * This function is called whenever an Action frame is received क्रम a station
 * mode पूर्णांकerface, but is not processed in kernel.
 *
 * Return: %true अगर a user space application has रेजिस्टरed क्रम this frame.
 * For action frames, that makes it responsible क्रम rejecting unrecognized
 * action frames; %false otherwise, in which हाल क्रम action frames the
 * driver is responsible क्रम rejecting the frame.
 */
bool cfg80211_rx_mgmt_khz(काष्ठा wireless_dev *wdev, पूर्णांक freq, पूर्णांक sig_dbm,
			  स्थिर u8 *buf, माप_प्रकार len, u32 flags);

/**
 * cfg80211_rx_mgmt - notअगरication of received, unprocessed management frame
 * @wdev: wireless device receiving the frame
 * @freq: Frequency on which the frame was received in MHz
 * @sig_dbm: संकेत strength in dBm, or 0 अगर unknown
 * @buf: Management frame (header + body)
 * @len: length of the frame data
 * @flags: flags, as defined in क्रमागत nl80211_rxmgmt_flags
 *
 * This function is called whenever an Action frame is received क्रम a station
 * mode पूर्णांकerface, but is not processed in kernel.
 *
 * Return: %true अगर a user space application has रेजिस्टरed क्रम this frame.
 * For action frames, that makes it responsible क्रम rejecting unrecognized
 * action frames; %false otherwise, in which हाल क्रम action frames the
 * driver is responsible क्रम rejecting the frame.
 */
अटल अंतरभूत bool cfg80211_rx_mgmt(काष्ठा wireless_dev *wdev, पूर्णांक freq,
				    पूर्णांक sig_dbm, स्थिर u8 *buf, माप_प्रकार len,
				    u32 flags)
अणु
	वापस cfg80211_rx_mgmt_khz(wdev, MHZ_TO_KHZ(freq), sig_dbm, buf, len,
				    flags);
पूर्ण

/**
 * cfg80211_mgmt_tx_status - notअगरication of TX status क्रम management frame
 * @wdev: wireless device receiving the frame
 * @cookie: Cookie वापसed by cfg80211_ops::mgmt_tx()
 * @buf: Management frame (header + body)
 * @len: length of the frame data
 * @ack: Whether frame was acknowledged
 * @gfp: context flags
 *
 * This function is called whenever a management frame was requested to be
 * transmitted with cfg80211_ops::mgmt_tx() to report the TX status of the
 * transmission attempt.
 */
व्योम cfg80211_mgmt_tx_status(काष्ठा wireless_dev *wdev, u64 cookie,
			     स्थिर u8 *buf, माप_प्रकार len, bool ack, gfp_t gfp);

/**
 * cfg80211_control_port_tx_status - notअगरication of TX status क्रम control
 *                                   port frames
 * @wdev: wireless device receiving the frame
 * @cookie: Cookie वापसed by cfg80211_ops::tx_control_port()
 * @buf: Data frame (header + body)
 * @len: length of the frame data
 * @ack: Whether frame was acknowledged
 * @gfp: context flags
 *
 * This function is called whenever a control port frame was requested to be
 * transmitted with cfg80211_ops::tx_control_port() to report the TX status of
 * the transmission attempt.
 */
व्योम cfg80211_control_port_tx_status(काष्ठा wireless_dev *wdev, u64 cookie,
				     स्थिर u8 *buf, माप_प्रकार len, bool ack,
				     gfp_t gfp);

/**
 * cfg80211_rx_control_port - notअगरication about a received control port frame
 * @dev: The device the frame matched to
 * @skb: The skbuf with the control port frame.  It is assumed that the skbuf
 *	is 802.3 क्रमmatted (with 802.3 header).  The skb can be non-linear.
 *	This function करोes not take ownership of the skb, so the caller is
 *	responsible क्रम any cleanup.  The caller must also ensure that
 *	skb->protocol is set appropriately.
 * @unencrypted: Whether the frame was received unencrypted
 *
 * This function is used to inक्रमm userspace about a received control port
 * frame.  It should only be used अगर userspace indicated it wants to receive
 * control port frames over nl80211.
 *
 * The frame is the data portion of the 802.3 or 802.11 data frame with all
 * network layer headers हटाओd (e.g. the raw EAPoL frame).
 *
 * Return: %true अगर the frame was passed to userspace
 */
bool cfg80211_rx_control_port(काष्ठा net_device *dev,
			      काष्ठा sk_buff *skb, bool unencrypted);

/**
 * cfg80211_cqm_rssi_notअगरy - connection quality monitoring rssi event
 * @dev: network device
 * @rssi_event: the triggered RSSI event
 * @rssi_level: new RSSI level value or 0 अगर not available
 * @gfp: context flags
 *
 * This function is called when a configured connection quality monitoring
 * rssi threshold reached event occurs.
 */
व्योम cfg80211_cqm_rssi_notअगरy(काष्ठा net_device *dev,
			      क्रमागत nl80211_cqm_rssi_threshold_event rssi_event,
			      s32 rssi_level, gfp_t gfp);

/**
 * cfg80211_cqm_pktloss_notअगरy - notअगरy userspace about packetloss to peer
 * @dev: network device
 * @peer: peer's MAC address
 * @num_packets: how many packets were lost -- should be a fixed threshold
 *	but probably no less than maybe 50, or maybe a throughput dependent
 *	threshold (to account क्रम temporary पूर्णांकerference)
 * @gfp: context flags
 */
व्योम cfg80211_cqm_pktloss_notअगरy(काष्ठा net_device *dev,
				 स्थिर u8 *peer, u32 num_packets, gfp_t gfp);

/**
 * cfg80211_cqm_txe_notअगरy - TX error rate event
 * @dev: network device
 * @peer: peer's MAC address
 * @num_packets: how many packets were lost
 * @rate: % of packets which failed transmission
 * @पूर्णांकvl: पूर्णांकerval (in s) over which the TX failure threshold was breached.
 * @gfp: context flags
 *
 * Notअगरy userspace when configured % TX failures over number of packets in a
 * given पूर्णांकerval is exceeded.
 */
व्योम cfg80211_cqm_txe_notअगरy(काष्ठा net_device *dev, स्थिर u8 *peer,
			     u32 num_packets, u32 rate, u32 पूर्णांकvl, gfp_t gfp);

/**
 * cfg80211_cqm_beacon_loss_notअगरy - beacon loss event
 * @dev: network device
 * @gfp: context flags
 *
 * Notअगरy userspace about beacon loss from the connected AP.
 */
व्योम cfg80211_cqm_beacon_loss_notअगरy(काष्ठा net_device *dev, gfp_t gfp);

/**
 * cfg80211_radar_event - radar detection event
 * @wiphy: the wiphy
 * @chandef: chandef क्रम the current channel
 * @gfp: context flags
 *
 * This function is called when a radar is detected on the current chanenl.
 */
व्योम cfg80211_radar_event(काष्ठा wiphy *wiphy,
			  काष्ठा cfg80211_chan_def *chandef, gfp_t gfp);

/**
 * cfg80211_sta_opmode_change_notअगरy - STA's ht/vht operation mode change event
 * @dev: network device
 * @mac: MAC address of a station which opmode got modअगरied
 * @sta_opmode: station's current opmode value
 * @gfp: context flags
 *
 * Driver should call this function when station's opmode modअगरied via action
 * frame.
 */
व्योम cfg80211_sta_opmode_change_notअगरy(काष्ठा net_device *dev, स्थिर u8 *mac,
				       काष्ठा sta_opmode_info *sta_opmode,
				       gfp_t gfp);

/**
 * cfg80211_cac_event - Channel availability check (CAC) event
 * @netdev: network device
 * @chandef: chandef क्रम the current channel
 * @event: type of event
 * @gfp: context flags
 *
 * This function is called when a Channel availability check (CAC) is finished
 * or पातed. This must be called to notअगरy the completion of a CAC process,
 * also by full-MAC drivers.
 */
व्योम cfg80211_cac_event(काष्ठा net_device *netdev,
			स्थिर काष्ठा cfg80211_chan_def *chandef,
			क्रमागत nl80211_radar_event event, gfp_t gfp);


/**
 * cfg80211_gtk_rekey_notअगरy - notअगरy userspace about driver rekeying
 * @dev: network device
 * @bssid: BSSID of AP (to aव्योम races)
 * @replay_ctr: new replay counter
 * @gfp: allocation flags
 */
व्योम cfg80211_gtk_rekey_notअगरy(काष्ठा net_device *dev, स्थिर u8 *bssid,
			       स्थिर u8 *replay_ctr, gfp_t gfp);

/**
 * cfg80211_pmksa_candidate_notअगरy - notअगरy about PMKSA caching candidate
 * @dev: network device
 * @index: candidate index (the smaller the index, the higher the priority)
 * @bssid: BSSID of AP
 * @preauth: Whether AP advertises support क्रम RSN pre-authentication
 * @gfp: allocation flags
 */
व्योम cfg80211_pmksa_candidate_notअगरy(काष्ठा net_device *dev, पूर्णांक index,
				     स्थिर u8 *bssid, bool preauth, gfp_t gfp);

/**
 * cfg80211_rx_spurious_frame - inक्रमm userspace about a spurious frame
 * @dev: The device the frame matched to
 * @addr: the transmitter address
 * @gfp: context flags
 *
 * This function is used in AP mode (only!) to inक्रमm userspace that
 * a spurious class 3 frame was received, to be able to deauth the
 * sender.
 * Return: %true अगर the frame was passed to userspace (or this failed
 * क्रम a reason other than not having a subscription.)
 */
bool cfg80211_rx_spurious_frame(काष्ठा net_device *dev,
				स्थिर u8 *addr, gfp_t gfp);

/**
 * cfg80211_rx_unexpected_4addr_frame - inक्रमm about unexpected WDS frame
 * @dev: The device the frame matched to
 * @addr: the transmitter address
 * @gfp: context flags
 *
 * This function is used in AP mode (only!) to inक्रमm userspace that
 * an associated station sent a 4addr frame but that wasn't expected.
 * It is allowed and desirable to send this event only once क्रम each
 * station to aव्योम event flooding.
 * Return: %true अगर the frame was passed to userspace (or this failed
 * क्रम a reason other than not having a subscription.)
 */
bool cfg80211_rx_unexpected_4addr_frame(काष्ठा net_device *dev,
					स्थिर u8 *addr, gfp_t gfp);

/**
 * cfg80211_probe_status - notअगरy userspace about probe status
 * @dev: the device the probe was sent on
 * @addr: the address of the peer
 * @cookie: the cookie filled in @probe_client previously
 * @acked: indicates whether probe was acked or not
 * @ack_संकेत: संकेत strength (in dBm) of the ACK frame.
 * @is_valid_ack_संकेत: indicates the ack_संकेत is valid or not.
 * @gfp: allocation flags
 */
व्योम cfg80211_probe_status(काष्ठा net_device *dev, स्थिर u8 *addr,
			   u64 cookie, bool acked, s32 ack_संकेत,
			   bool is_valid_ack_संकेत, gfp_t gfp);

/**
 * cfg80211_report_obss_beacon_khz - report beacon from other APs
 * @wiphy: The wiphy that received the beacon
 * @frame: the frame
 * @len: length of the frame
 * @freq: frequency the frame was received on in KHz
 * @sig_dbm: संकेत strength in dBm, or 0 अगर unknown
 *
 * Use this function to report to userspace when a beacon was
 * received. It is not useful to call this when there is no
 * netdev that is in AP/GO mode.
 */
व्योम cfg80211_report_obss_beacon_khz(काष्ठा wiphy *wiphy, स्थिर u8 *frame,
				     माप_प्रकार len, पूर्णांक freq, पूर्णांक sig_dbm);

/**
 * cfg80211_report_obss_beacon - report beacon from other APs
 * @wiphy: The wiphy that received the beacon
 * @frame: the frame
 * @len: length of the frame
 * @freq: frequency the frame was received on
 * @sig_dbm: संकेत strength in dBm, or 0 अगर unknown
 *
 * Use this function to report to userspace when a beacon was
 * received. It is not useful to call this when there is no
 * netdev that is in AP/GO mode.
 */
अटल अंतरभूत व्योम cfg80211_report_obss_beacon(काष्ठा wiphy *wiphy,
					       स्थिर u8 *frame, माप_प्रकार len,
					       पूर्णांक freq, पूर्णांक sig_dbm)
अणु
	cfg80211_report_obss_beacon_khz(wiphy, frame, len, MHZ_TO_KHZ(freq),
					sig_dbm);
पूर्ण

/**
 * cfg80211_reg_can_beacon - check अगर beaconing is allowed
 * @wiphy: the wiphy
 * @chandef: the channel definition
 * @अगरtype: पूर्णांकerface type
 *
 * Return: %true अगर there is no secondary channel or the secondary channel(s)
 * can be used क्रम beaconing (i.e. is not a radar channel etc.)
 */
bool cfg80211_reg_can_beacon(काष्ठा wiphy *wiphy,
			     काष्ठा cfg80211_chan_def *chandef,
			     क्रमागत nl80211_अगरtype अगरtype);

/**
 * cfg80211_reg_can_beacon_relax - check अगर beaconing is allowed with relaxation
 * @wiphy: the wiphy
 * @chandef: the channel definition
 * @अगरtype: पूर्णांकerface type
 *
 * Return: %true अगर there is no secondary channel or the secondary channel(s)
 * can be used क्रम beaconing (i.e. is not a radar channel etc.). This version
 * also checks अगर IR-relaxation conditions apply, to allow beaconing under
 * more permissive conditions.
 *
 * Requires the wiphy mutex to be held.
 */
bool cfg80211_reg_can_beacon_relax(काष्ठा wiphy *wiphy,
				   काष्ठा cfg80211_chan_def *chandef,
				   क्रमागत nl80211_अगरtype अगरtype);

/*
 * cfg80211_ch_चयन_notअगरy - update wdev channel and notअगरy userspace
 * @dev: the device which चयनed channels
 * @chandef: the new channel definition
 *
 * Caller must acquire wdev_lock, thereक्रमe must only be called from sleepable
 * driver context!
 */
व्योम cfg80211_ch_चयन_notअगरy(काष्ठा net_device *dev,
			       काष्ठा cfg80211_chan_def *chandef);

/*
 * cfg80211_ch_चयन_started_notअगरy - notअगरy channel चयन start
 * @dev: the device on which the channel चयन started
 * @chandef: the future channel definition
 * @count: the number of TBTTs until the channel चयन happens
 * @quiet: whether or not immediate quiet was requested by the AP
 *
 * Inक्रमm the userspace about the channel चयन that has just
 * started, so that it can take appropriate actions (eg. starting
 * channel चयन on other vअगरs), अगर necessary.
 */
व्योम cfg80211_ch_चयन_started_notअगरy(काष्ठा net_device *dev,
				       काष्ठा cfg80211_chan_def *chandef,
				       u8 count, bool quiet);

/**
 * ieee80211_operating_class_to_band - convert operating class to band
 *
 * @operating_class: the operating class to convert
 * @band: band poपूर्णांकer to fill
 *
 * Returns %true अगर the conversion was successful, %false otherwise.
 */
bool ieee80211_operating_class_to_band(u8 operating_class,
				       क्रमागत nl80211_band *band);

/**
 * ieee80211_chandef_to_operating_class - convert chandef to operation class
 *
 * @chandef: the chandef to convert
 * @op_class: a poपूर्णांकer to the resulting operating class
 *
 * Returns %true अगर the conversion was successful, %false otherwise.
 */
bool ieee80211_chandef_to_operating_class(काष्ठा cfg80211_chan_def *chandef,
					  u8 *op_class);

/**
 * ieee80211_chandef_to_khz - convert chandef to frequency in KHz
 *
 * @chandef: the chandef to convert
 *
 * Returns the center frequency of chandef (1st segment) in KHz.
 */
अटल अंतरभूत u32
ieee80211_chandef_to_khz(स्थिर काष्ठा cfg80211_chan_def *chandef)
अणु
	वापस MHZ_TO_KHZ(chandef->center_freq1) + chandef->freq1_offset;
पूर्ण

/*
 * cfg80211_tdls_oper_request - request userspace to perक्रमm TDLS operation
 * @dev: the device on which the operation is requested
 * @peer: the MAC address of the peer device
 * @oper: the requested TDLS operation (NL80211_TDLS_SETUP or
 *	NL80211_TDLS_TEARDOWN)
 * @reason_code: the reason code क्रम tearकरोwn request
 * @gfp: allocation flags
 *
 * This function is used to request userspace to perक्रमm TDLS operation that
 * requires knowledge of keys, i.e., link setup or tearकरोwn when the AP
 * connection uses encryption. This is optional mechanism क्रम the driver to use
 * अगर it can स्वतःmatically determine when a TDLS link could be useful (e.g.,
 * based on traffic and संकेत strength क्रम a peer).
 */
व्योम cfg80211_tdls_oper_request(काष्ठा net_device *dev, स्थिर u8 *peer,
				क्रमागत nl80211_tdls_operation oper,
				u16 reason_code, gfp_t gfp);

/*
 * cfg80211_calculate_bitrate - calculate actual bitrate (in 100Kbps units)
 * @rate: given rate_info to calculate bitrate from
 *
 * वापस 0 अगर MCS index >= 32
 */
u32 cfg80211_calculate_bitrate(काष्ठा rate_info *rate);

/**
 * cfg80211_unरेजिस्टर_wdev - हटाओ the given wdev
 * @wdev: काष्ठा wireless_dev to हटाओ
 *
 * This function हटाओs the device so it can no दीर्घer be used. It is necessary
 * to call this function even when cfg80211 requests the removal of the device
 * by calling the del_भव_पूर्णांकf() callback. The function must also be called
 * when the driver wishes to unरेजिस्टर the wdev, e.g. when the hardware device
 * is unbound from the driver.
 *
 * Requires the RTNL and wiphy mutex to be held.
 */
व्योम cfg80211_unरेजिस्टर_wdev(काष्ठा wireless_dev *wdev);

/**
 * cfg80211_रेजिस्टर_netdevice - रेजिस्टर the given netdev
 * @dev: the netdev to रेजिस्टर
 *
 * Note: In contexts coming from cfg80211 callbacks, you must call this rather
 * than रेजिस्टर_netdevice(), unरेजिस्टर_netdev() is impossible as the RTNL is
 * held. Otherwise, both रेजिस्टर_netdevice() and रेजिस्टर_netdev() are usable
 * instead as well.
 *
 * Requires the RTNL and wiphy mutex to be held.
 */
पूर्णांक cfg80211_रेजिस्टर_netdevice(काष्ठा net_device *dev);

/**
 * cfg80211_unरेजिस्टर_netdevice - unरेजिस्टर the given netdev
 * @dev: the netdev to रेजिस्टर
 *
 * Note: In contexts coming from cfg80211 callbacks, you must call this rather
 * than unरेजिस्टर_netdevice(), unरेजिस्टर_netdev() is impossible as the RTNL
 * is held. Otherwise, both unरेजिस्टर_netdevice() and unरेजिस्टर_netdev() are
 * usable instead as well.
 *
 * Requires the RTNL and wiphy mutex to be held.
 */
अटल अंतरभूत व्योम cfg80211_unरेजिस्टर_netdevice(काष्ठा net_device *dev)
अणु
	cfg80211_unरेजिस्टर_wdev(dev->ieee80211_ptr);
पूर्ण

/**
 * काष्ठा cfg80211_ft_event_params - FT Inक्रमmation Elements
 * @ies: FT IEs
 * @ies_len: length of the FT IE in bytes
 * @target_ap: target AP's MAC address
 * @ric_ies: RIC IE
 * @ric_ies_len: length of the RIC IE in bytes
 */
काष्ठा cfg80211_ft_event_params अणु
	स्थिर u8 *ies;
	माप_प्रकार ies_len;
	स्थिर u8 *target_ap;
	स्थिर u8 *ric_ies;
	माप_प्रकार ric_ies_len;
पूर्ण;

/**
 * cfg80211_ft_event - notअगरy userspace about FT IE and RIC IE
 * @netdev: network device
 * @ft_event: IE inक्रमmation
 */
व्योम cfg80211_ft_event(काष्ठा net_device *netdev,
		       काष्ठा cfg80211_ft_event_params *ft_event);

/**
 * cfg80211_get_p2p_attr - find and copy a P2P attribute from IE buffer
 * @ies: the input IE buffer
 * @len: the input length
 * @attr: the attribute ID to find
 * @buf: output buffer, can be %शून्य अगर the data isn't needed, e.g.
 *	अगर the function is only called to get the needed buffer size
 * @bufsize: size of the output buffer
 *
 * The function finds a given P2P attribute in the (venकरोr) IEs and
 * copies its contents to the given buffer.
 *
 * Return: A negative error code (-%EILSEQ or -%ENOENT) अगर the data is
 * malक्रमmed or the attribute can't be found (respectively), or the
 * length of the found attribute (which can be zero).
 */
पूर्णांक cfg80211_get_p2p_attr(स्थिर u8 *ies, अचिन्हित पूर्णांक len,
			  क्रमागत ieee80211_p2p_attr_id attr,
			  u8 *buf, अचिन्हित पूर्णांक bufsize);

/**
 * ieee80211_ie_split_ric - split an IE buffer according to ordering (with RIC)
 * @ies: the IE buffer
 * @ielen: the length of the IE buffer
 * @ids: an array with element IDs that are allowed beक्रमe
 *	the split. A WLAN_EID_EXTENSION value means that the next
 *	EID in the list is a sub-element of the EXTENSION IE.
 * @n_ids: the size of the element ID array
 * @after_ric: array IE types that come after the RIC element
 * @n_after_ric: size of the @after_ric array
 * @offset: offset where to start splitting in the buffer
 *
 * This function splits an IE buffer by updating the @offset
 * variable to poपूर्णांक to the location where the buffer should be
 * split.
 *
 * It assumes that the given IE buffer is well-क्रमmed, this
 * has to be guaranteed by the caller!
 *
 * It also assumes that the IEs in the buffer are ordered
 * correctly, अगर not the result of using this function will not
 * be ordered correctly either, i.e. it करोes no reordering.
 *
 * The function वापसs the offset where the next part of the
 * buffer starts, which may be @ielen अगर the entire (reमुख्यder)
 * of the buffer should be used.
 */
माप_प्रकार ieee80211_ie_split_ric(स्थिर u8 *ies, माप_प्रकार ielen,
			      स्थिर u8 *ids, पूर्णांक n_ids,
			      स्थिर u8 *after_ric, पूर्णांक n_after_ric,
			      माप_प्रकार offset);

/**
 * ieee80211_ie_split - split an IE buffer according to ordering
 * @ies: the IE buffer
 * @ielen: the length of the IE buffer
 * @ids: an array with element IDs that are allowed beक्रमe
 *	the split. A WLAN_EID_EXTENSION value means that the next
 *	EID in the list is a sub-element of the EXTENSION IE.
 * @n_ids: the size of the element ID array
 * @offset: offset where to start splitting in the buffer
 *
 * This function splits an IE buffer by updating the @offset
 * variable to poपूर्णांक to the location where the buffer should be
 * split.
 *
 * It assumes that the given IE buffer is well-क्रमmed, this
 * has to be guaranteed by the caller!
 *
 * It also assumes that the IEs in the buffer are ordered
 * correctly, अगर not the result of using this function will not
 * be ordered correctly either, i.e. it करोes no reordering.
 *
 * The function वापसs the offset where the next part of the
 * buffer starts, which may be @ielen अगर the entire (reमुख्यder)
 * of the buffer should be used.
 */
अटल अंतरभूत माप_प्रकार ieee80211_ie_split(स्थिर u8 *ies, माप_प्रकार ielen,
					स्थिर u8 *ids, पूर्णांक n_ids, माप_प्रकार offset)
अणु
	वापस ieee80211_ie_split_ric(ies, ielen, ids, n_ids, शून्य, 0, offset);
पूर्ण

/**
 * cfg80211_report_wowlan_wakeup - report wakeup from WoWLAN
 * @wdev: the wireless device reporting the wakeup
 * @wakeup: the wakeup report
 * @gfp: allocation flags
 *
 * This function reports that the given device woke up. If it
 * caused the wakeup, report the reason(s), otherwise you may
 * pass %शून्य as the @wakeup parameter to advertise that something
 * अन्यथा caused the wakeup.
 */
व्योम cfg80211_report_wowlan_wakeup(काष्ठा wireless_dev *wdev,
				   काष्ठा cfg80211_wowlan_wakeup *wakeup,
				   gfp_t gfp);

/**
 * cfg80211_crit_proto_stopped() - indicate critical protocol stopped by driver.
 *
 * @wdev: the wireless device क्रम which critical protocol is stopped.
 * @gfp: allocation flags
 *
 * This function can be called by the driver to indicate it has reverted
 * operation back to normal. One reason could be that the duration given
 * by .crit_proto_start() has expired.
 */
व्योम cfg80211_crit_proto_stopped(काष्ठा wireless_dev *wdev, gfp_t gfp);

/**
 * ieee80211_get_num_supported_channels - get number of channels device has
 * @wiphy: the wiphy
 *
 * Return: the number of channels supported by the device.
 */
अचिन्हित पूर्णांक ieee80211_get_num_supported_channels(काष्ठा wiphy *wiphy);

/**
 * cfg80211_check_combinations - check पूर्णांकerface combinations
 *
 * @wiphy: the wiphy
 * @params: the पूर्णांकerface combinations parameter
 *
 * This function can be called by the driver to check whether a
 * combination of पूर्णांकerfaces and their types are allowed according to
 * the पूर्णांकerface combinations.
 */
पूर्णांक cfg80211_check_combinations(काष्ठा wiphy *wiphy,
				काष्ठा अगरace_combination_params *params);

/**
 * cfg80211_iter_combinations - iterate over matching combinations
 *
 * @wiphy: the wiphy
 * @params: the पूर्णांकerface combinations parameter
 * @iter: function to call क्रम each matching combination
 * @data: poपूर्णांकer to pass to iter function
 *
 * This function can be called by the driver to check what possible
 * combinations it fits in at a given moment, e.g. क्रम channel चयनing
 * purposes.
 */
पूर्णांक cfg80211_iter_combinations(काष्ठा wiphy *wiphy,
			       काष्ठा अगरace_combination_params *params,
			       व्योम (*iter)(स्थिर काष्ठा ieee80211_अगरace_combination *c,
					    व्योम *data),
			       व्योम *data);

/*
 * cfg80211_stop_अगरace - trigger पूर्णांकerface disconnection
 *
 * @wiphy: the wiphy
 * @wdev: wireless device
 * @gfp: context flags
 *
 * Trigger पूर्णांकerface to be stopped as अगर AP was stopped, IBSS/mesh left, STA
 * disconnected.
 *
 * Note: This करोesn't need any locks and is asynchronous.
 */
व्योम cfg80211_stop_अगरace(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
			 gfp_t gfp);

/**
 * cfg80211_shutकरोwn_all_पूर्णांकerfaces - shut करोwn all पूर्णांकerfaces क्रम a wiphy
 * @wiphy: the wiphy to shut करोwn
 *
 * This function shuts करोwn all पूर्णांकerfaces beदीर्घing to this wiphy by
 * calling dev_बंद() (and treating non-netdev पूर्णांकerfaces as needed).
 * It shouldn't really be used unless there are some fatal device errors
 * that really can't be recovered in any other way.
 *
 * Callers must hold the RTNL and be able to deal with callbacks पूर्णांकo
 * the driver जबतक the function is running.
 */
व्योम cfg80211_shutकरोwn_all_पूर्णांकerfaces(काष्ठा wiphy *wiphy);

/**
 * wiphy_ext_feature_set - set the extended feature flag
 *
 * @wiphy: the wiphy to modअगरy.
 * @ftidx: extended feature bit index.
 *
 * The extended features are flagged in multiple bytes (see
 * &काष्ठा wiphy.@ext_features)
 */
अटल अंतरभूत व्योम wiphy_ext_feature_set(काष्ठा wiphy *wiphy,
					 क्रमागत nl80211_ext_feature_index ftidx)
अणु
	u8 *ft_byte;

	ft_byte = &wiphy->ext_features[ftidx / 8];
	*ft_byte |= BIT(ftidx % 8);
पूर्ण

/**
 * wiphy_ext_feature_isset - check the extended feature flag
 *
 * @wiphy: the wiphy to modअगरy.
 * @ftidx: extended feature bit index.
 *
 * The extended features are flagged in multiple bytes (see
 * &काष्ठा wiphy.@ext_features)
 */
अटल अंतरभूत bool
wiphy_ext_feature_isset(काष्ठा wiphy *wiphy,
			क्रमागत nl80211_ext_feature_index ftidx)
अणु
	u8 ft_byte;

	ft_byte = wiphy->ext_features[ftidx / 8];
	वापस (ft_byte & BIT(ftidx % 8)) != 0;
पूर्ण

/**
 * cfg80211_मुक्त_nan_func - मुक्त न_अंक function
 * @f: न_अंक function that should be मुक्तd
 *
 * Frees all the न_अंक function and all it's allocated members.
 */
व्योम cfg80211_मुक्त_nan_func(काष्ठा cfg80211_nan_func *f);

/**
 * काष्ठा cfg80211_nan_match_params - न_अंक match parameters
 * @type: the type of the function that triggered a match. If it is
 *	 %NL80211_न_अंक_FUNC_SUBSCRIBE it means that we replied to a subscriber.
 *	 If it is %NL80211_न_अंक_FUNC_PUBLISH, it means that we got a discovery
 *	 result.
 *	 If it is %NL80211_न_अंक_FUNC_FOLLOW_UP, we received a follow up.
 * @inst_id: the local instance id
 * @peer_inst_id: the instance id of the peer's function
 * @addr: the MAC address of the peer
 * @info_len: the length of the &info
 * @info: the Service Specअगरic Info from the peer (अगर any)
 * @cookie: unique identअगरier of the corresponding function
 */
काष्ठा cfg80211_nan_match_params अणु
	क्रमागत nl80211_nan_function_type type;
	u8 inst_id;
	u8 peer_inst_id;
	स्थिर u8 *addr;
	u8 info_len;
	स्थिर u8 *info;
	u64 cookie;
पूर्ण;

/**
 * cfg80211_nan_match - report a match क्रम a न_अंक function.
 * @wdev: the wireless device reporting the match
 * @match: match notअगरication parameters
 * @gfp: allocation flags
 *
 * This function reports that the a न_अंक function had a match. This
 * can be a subscribe that had a match or a solicited publish that
 * was sent. It can also be a follow up that was received.
 */
व्योम cfg80211_nan_match(काष्ठा wireless_dev *wdev,
			काष्ठा cfg80211_nan_match_params *match, gfp_t gfp);

/**
 * cfg80211_nan_func_terminated - notअगरy about न_अंक function termination.
 *
 * @wdev: the wireless device reporting the match
 * @inst_id: the local instance id
 * @reason: termination reason (one of the NL80211_न_अंक_FUNC_TERM_REASON_*)
 * @cookie: unique न_अंक function identअगरier
 * @gfp: allocation flags
 *
 * This function reports that the a न_अंक function is terminated.
 */
व्योम cfg80211_nan_func_terminated(काष्ठा wireless_dev *wdev,
				  u8 inst_id,
				  क्रमागत nl80211_nan_func_term_reason reason,
				  u64 cookie, gfp_t gfp);

/* ethtool helper */
व्योम cfg80211_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info);

/**
 * cfg80211_बाह्यal_auth_request - userspace request क्रम authentication
 * @netdev: network device
 * @params: External authentication parameters
 * @gfp: allocation flags
 * Returns: 0 on success, < 0 on error
 */
पूर्णांक cfg80211_बाह्यal_auth_request(काष्ठा net_device *netdev,
				   काष्ठा cfg80211_बाह्यal_auth_params *params,
				   gfp_t gfp);

/**
 * cfg80211_pmsr_report - report peer measurement result data
 * @wdev: the wireless device reporting the measurement
 * @req: the original measurement request
 * @result: the result data
 * @gfp: allocation flags
 */
व्योम cfg80211_pmsr_report(काष्ठा wireless_dev *wdev,
			  काष्ठा cfg80211_pmsr_request *req,
			  काष्ठा cfg80211_pmsr_result *result,
			  gfp_t gfp);

/**
 * cfg80211_pmsr_complete - report peer measurement completed
 * @wdev: the wireless device reporting the measurement
 * @req: the original measurement request
 * @gfp: allocation flags
 *
 * Report that the entire measurement completed, after this
 * the request poपूर्णांकer will no दीर्घer be valid.
 */
व्योम cfg80211_pmsr_complete(काष्ठा wireless_dev *wdev,
			    काष्ठा cfg80211_pmsr_request *req,
			    gfp_t gfp);

/**
 * cfg80211_अगरtype_allowed - check whether the पूर्णांकerface can be allowed
 * @wiphy: the wiphy
 * @अगरtype: पूर्णांकerface type
 * @is_4addr: use_4addr flag, must be '0' when check_swif is '1'
 * @check_swअगर: check अगरtype against software पूर्णांकerfaces
 *
 * Check whether the पूर्णांकerface is allowed to operate; additionally, this API
 * can be used to check अगरtype against the software पूर्णांकerfaces when
 * check_swअगर is '1'.
 */
bool cfg80211_अगरtype_allowed(काष्ठा wiphy *wiphy, क्रमागत nl80211_अगरtype अगरtype,
			     bool is_4addr, u8 check_swअगर);


/* Logging, debugging and troubleshooting/diagnostic helpers. */

/* wiphy_prपूर्णांकk helpers, similar to dev_prपूर्णांकk */

#घोषणा wiphy_prपूर्णांकk(level, wiphy, क्रमmat, args...)		\
	dev_prपूर्णांकk(level, &(wiphy)->dev, क्रमmat, ##args)
#घोषणा wiphy_emerg(wiphy, क्रमmat, args...)			\
	dev_emerg(&(wiphy)->dev, क्रमmat, ##args)
#घोषणा wiphy_alert(wiphy, क्रमmat, args...)			\
	dev_alert(&(wiphy)->dev, क्रमmat, ##args)
#घोषणा wiphy_crit(wiphy, क्रमmat, args...)			\
	dev_crit(&(wiphy)->dev, क्रमmat, ##args)
#घोषणा wiphy_err(wiphy, क्रमmat, args...)			\
	dev_err(&(wiphy)->dev, क्रमmat, ##args)
#घोषणा wiphy_warn(wiphy, क्रमmat, args...)			\
	dev_warn(&(wiphy)->dev, क्रमmat, ##args)
#घोषणा wiphy_notice(wiphy, क्रमmat, args...)			\
	dev_notice(&(wiphy)->dev, क्रमmat, ##args)
#घोषणा wiphy_info(wiphy, क्रमmat, args...)			\
	dev_info(&(wiphy)->dev, क्रमmat, ##args)

#घोषणा wiphy_err_ratelimited(wiphy, क्रमmat, args...)		\
	dev_err_ratelimited(&(wiphy)->dev, क्रमmat, ##args)
#घोषणा wiphy_warn_ratelimited(wiphy, क्रमmat, args...)		\
	dev_warn_ratelimited(&(wiphy)->dev, क्रमmat, ##args)

#घोषणा wiphy_debug(wiphy, क्रमmat, args...)			\
	wiphy_prपूर्णांकk(KERN_DEBUG, wiphy, क्रमmat, ##args)

#घोषणा wiphy_dbg(wiphy, क्रमmat, args...)			\
	dev_dbg(&(wiphy)->dev, क्रमmat, ##args)

#अगर defined(VERBOSE_DEBUG)
#घोषणा wiphy_vdbg	wiphy_dbg
#अन्यथा
#घोषणा wiphy_vdbg(wiphy, क्रमmat, args...)				\
(अणु									\
	अगर (0)								\
		wiphy_prपूर्णांकk(KERN_DEBUG, wiphy, क्रमmat, ##args);	\
	0;								\
पूर्ण)
#पूर्ण_अगर

/*
 * wiphy_WARN() acts like wiphy_prपूर्णांकk(), but with the key dअगरference
 * of using a WARN/WARN_ON to get the message out, including the
 * file/line inक्रमmation and a backtrace.
 */
#घोषणा wiphy_WARN(wiphy, क्रमmat, args...)			\
	WARN(1, "wiphy: %s\n" क्रमmat, wiphy_name(wiphy), ##args);

/**
 * cfg80211_update_owe_info_event - Notअगरy the peer's OWE info to user space
 * @netdev: network device
 * @owe_info: peer's owe info
 * @gfp: allocation flags
 */
व्योम cfg80211_update_owe_info_event(काष्ठा net_device *netdev,
				    काष्ठा cfg80211_update_owe_info *owe_info,
				    gfp_t gfp);

/**
 * cfg80211_bss_flush - resets all the scan entries
 * @wiphy: the wiphy
 */
व्योम cfg80211_bss_flush(काष्ठा wiphy *wiphy);

#पूर्ण_अगर /* __NET_CFG80211_H */
