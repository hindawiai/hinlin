<शैली गुरु>
#अगर_अघोषित __NET_REGULATORY_H
#घोषणा __NET_REGULATORY_H
/*
 * regulatory support काष्ठाures
 *
 * Copyright 2008-2009	Luis R. Rodriguez <mcgrof@qca.qualcomm.com>
 * Copyright (C) 2018 Intel Corporation
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <linux/rcupdate.h>

/**
 * क्रमागत environment_cap - Environment parsed from country IE
 * @ENVIRON_ANY: indicates country IE applies to both inकरोor and
 *	outकरोor operation.
 * @ENVIRON_INDOOR: indicates country IE applies only to inकरोor operation
 * @ENVIRON_OUTDOOR: indicates country IE applies only to outकरोor operation
 */
क्रमागत environment_cap अणु
	ENVIRON_ANY,
	ENVIRON_INDOOR,
	ENVIRON_OUTDOOR,
पूर्ण;

/**
 * काष्ठा regulatory_request - used to keep track of regulatory requests
 *
 * @rcu_head: RCU head काष्ठा used to मुक्त the request
 * @wiphy_idx: this is set अगर this request's initiator is
 *	%REGDOM_SET_BY_COUNTRY_IE or %REGDOM_SET_BY_DRIVER. This
 *	can be used by the wireless core to deal with conflicts
 *	and potentially inक्रमm users of which devices specअगरically
 *	हालd the conflicts.
 * @initiator: indicates who sent this request, could be any of
 *	those set in nl80211_reg_initiator (%NL80211_REGDOM_SET_BY_*)
 * @alpha2: the ISO / IEC 3166 alpha2 country code of the requested
 *	regulatory करोमुख्य. We have a few special codes:
 *	00 - World regulatory करोमुख्य
 *	99 - built by driver but a specअगरic alpha2 cannot be determined
 *	98 - result of an पूर्णांकersection between two regulatory करोमुख्यs
 *	97 - regulatory करोमुख्य has not yet been configured
 * @dfs_region: If CRDA responded with a regulatory करोमुख्य that requires
 *	DFS master operation on a known DFS region (NL80211_DFS_*),
 *	dfs_region represents that region. Drivers can use this and the
 *	@alpha2 to adjust their device's DFS parameters as required.
 * @user_reg_hपूर्णांक_type: अगर the @initiator was of type
 *	%NL80211_REGDOM_SET_BY_USER, this classअगरies the type
 *	of hपूर्णांक passed. This could be any of the %NL80211_USER_REG_HINT_*
 *	types.
 * @पूर्णांकersect: indicates whether the wireless core should पूर्णांकersect
 *	the requested regulatory करोमुख्य with the presently set regulatory
 *	करोमुख्य.
 * @processed: indicates whether or not this requests has alपढ़ोy been
 *	processed. When the last request is processed it means that the
 *	currently regulatory करोमुख्य set on cfg80211 is updated from
 *	CRDA and can be used by other regulatory requests. When a
 *	the last request is not yet processed we must yield until it
 *	is processed beक्रमe processing any new requests.
 * @country_ie_checksum: checksum of the last processed and accepted
 *	country IE
 * @country_ie_env: lets us know अगर the AP is telling us we are outकरोor,
 *	inकरोor, or अगर it करोesn't matter
 * @list: used to insert पूर्णांकo the reg_requests_list linked list
 */
काष्ठा regulatory_request अणु
	काष्ठा rcu_head rcu_head;
	पूर्णांक wiphy_idx;
	क्रमागत nl80211_reg_initiator initiator;
	क्रमागत nl80211_user_reg_hपूर्णांक_type user_reg_hपूर्णांक_type;
	अक्षर alpha2[3];
	क्रमागत nl80211_dfs_regions dfs_region;
	bool पूर्णांकersect;
	bool processed;
	क्रमागत environment_cap country_ie_env;
	काष्ठा list_head list;
पूर्ण;

/**
 * क्रमागत ieee80211_regulatory_flags - device regulatory flags
 *
 * @REGULATORY_CUSTOM_REG: tells us the driver क्रम this device
 *	has its own custom regulatory करोमुख्य and cannot identअगरy the
 *	ISO / IEC 3166 alpha2 it beदीर्घs to. When this is enabled
 *	we will disregard the first regulatory hपूर्णांक (when the
 *	initiator is %REGDOM_SET_BY_CORE). Drivers that use
 *	wiphy_apply_custom_regulatory() should have this flag set
 *	or the regulatory core will set it क्रम the wiphy.
 *	If you use regulatory_hपूर्णांक() *after* using
 *	wiphy_apply_custom_regulatory() the wireless core will
 *	clear the REGULATORY_CUSTOM_REG क्रम your wiphy as it would be
 *	implied that the device somehow gained knowledge of its region.
 * @REGULATORY_STRICT_REG: tells us that the wiphy क्रम this device
 *	has regulatory करोमुख्य that it wishes to be considered as the
 *	superset क्रम regulatory rules. After this device माला_लो its regulatory
 *	करोमुख्य programmed further regulatory hपूर्णांकs shall only be considered
 *	क्रम this device to enhance regulatory compliance, क्रमcing the
 *	device to only possibly use subsets of the original regulatory
 *	rules. For example अगर channel 13 and 14 are disabled by this
 *	device's regulatory करोमुख्य no user specअगरied regulatory hपूर्णांक which
 *	has these channels enabled would enable them क्रम this wiphy,
 *	the device's original regulatory करोमुख्य will be trusted as the
 *	base. You can program the superset of regulatory rules क्रम this
 *	wiphy with regulatory_hपूर्णांक() क्रम cards programmed with an
 *	ISO3166-alpha2 country code. wiphys that use regulatory_hपूर्णांक()
 *	will have their wiphy->regd programmed once the regulatory
 *	करोमुख्य is set, and all other regulatory hपूर्णांकs will be ignored
 *	until their own regulatory करोमुख्य माला_लो programmed.
 * @REGULATORY_DISABLE_BEACON_HINTS: enable this अगर your driver needs to
 *	ensure that passive scan flags and beaconing flags may not be lअगरted by
 *	cfg80211 due to regulatory beacon hपूर्णांकs. For more inक्रमmation on beacon
 *	hपूर्णांकs पढ़ो the करोcumenation क्रम regulatory_hपूर्णांक_found_beacon()
 * @REGULATORY_COUNTRY_IE_FOLLOW_POWER:  क्रम devices that have a preference
 *	that even though they may have programmed their own custom घातer
 *	setting prior to wiphy registration, they want to ensure their channel
 *	घातer settings are updated क्रम this connection with the घातer settings
 *	derived from the regulatory करोमुख्य. The regulatory करोमुख्य used will be
 *	based on the ISO3166-alpha2 from country IE provided through
 *	regulatory_hपूर्णांक_country_ie()
 * @REGULATORY_COUNTRY_IE_IGNORE: क्रम devices that have a preference to ignore
 * 	all country IE inक्रमmation processed by the regulatory core. This will
 * 	override %REGULATORY_COUNTRY_IE_FOLLOW_POWER as all country IEs will
 * 	be ignored.
 * @REGULATORY_ENABLE_RELAX_NO_IR: क्रम devices that wish to allow the
 *      NO_IR relaxation, which enables transmissions on channels on which
 *      otherwise initiating radiation is not allowed. This will enable the
 *      relaxations enabled under the CFG80211_REG_RELAX_NO_IR configuration
 *      option
 * @REGULATORY_IGNORE_STALE_KICKOFF: the regulatory core will _not_ make sure
 *	all पूर्णांकerfaces on this wiphy reside on allowed channels. If this flag
 *	is not set, upon a regकरोमुख्य change, the पूर्णांकerfaces are given a grace
 *	period (currently 60 seconds) to disconnect or move to an allowed
 *	channel. Interfaces on क्रमbidden channels are क्रमcibly disconnected.
 *	Currently these types of पूर्णांकerfaces are supported क्रम enक्रमcement:
 *	NL80211_IFTYPE_ADHOC, NL80211_IFTYPE_STATION, NL80211_IFTYPE_AP,
 *	NL80211_IFTYPE_AP_VLAN, NL80211_IFTYPE_MONITOR,
 *	NL80211_IFTYPE_P2P_CLIENT, NL80211_IFTYPE_P2P_GO,
 *	NL80211_IFTYPE_P2P_DEVICE. The flag will be set by शेष अगर a device
 *	includes any modes unsupported क्रम enक्रमcement checking.
 * @REGULATORY_WIPHY_SELF_MANAGED: क्रम devices that employ wiphy-specअगरic
 *	regकरोm management. These devices will ignore all regकरोm changes not
 *	originating from their own wiphy.
 *	A self-managed wiphys only employs regulatory inक्रमmation obtained from
 *	the FW and driver and करोes not use other cfg80211 sources like
 *	beacon-hपूर्णांकs, country-code IEs and hपूर्णांकs from other devices on the same
 *	प्रणाली. Conversely, a self-managed wiphy करोes not share its regulatory
 *	hपूर्णांकs with other devices in the प्रणाली. If a प्रणाली contains several
 *	devices, one or more of which are self-managed, there might be
 *	contradictory regulatory settings between them. Usage of flag is
 *	generally discouraged. Only use it अगर the FW/driver is incompatible
 *	with non-locally originated hपूर्णांकs.
 *	This flag is incompatible with the flags: %REGULATORY_CUSTOM_REG,
 *	%REGULATORY_STRICT_REG, %REGULATORY_COUNTRY_IE_FOLLOW_POWER,
 *	%REGULATORY_COUNTRY_IE_IGNORE and %REGULATORY_DISABLE_BEACON_HINTS.
 *	Mixing any of the above flags with this flag will result in a failure
 *	to रेजिस्टर the wiphy. This flag implies
 *	%REGULATORY_DISABLE_BEACON_HINTS and %REGULATORY_COUNTRY_IE_IGNORE.
 */
क्रमागत ieee80211_regulatory_flags अणु
	REGULATORY_CUSTOM_REG			= BIT(0),
	REGULATORY_STRICT_REG			= BIT(1),
	REGULATORY_DISABLE_BEACON_HINTS		= BIT(2),
	REGULATORY_COUNTRY_IE_FOLLOW_POWER	= BIT(3),
	REGULATORY_COUNTRY_IE_IGNORE		= BIT(4),
	REGULATORY_ENABLE_RELAX_NO_IR           = BIT(5),
	REGULATORY_IGNORE_STALE_KICKOFF         = BIT(6),
	REGULATORY_WIPHY_SELF_MANAGED		= BIT(7),
पूर्ण;

काष्ठा ieee80211_freq_range अणु
	u32 start_freq_khz;
	u32 end_freq_khz;
	u32 max_bandwidth_khz;
पूर्ण;

काष्ठा ieee80211_घातer_rule अणु
	u32 max_antenna_gain;
	u32 max_eirp;
पूर्ण;

/**
 * काष्ठा ieee80211_wmm_ac - used to store per ac wmm regulatory limitation
 *
 * The inक्रमmation provided in this काष्ठाure is required क्रम QoS
 * transmit queue configuration. Cf. IEEE 802.11 7.3.2.29.
 *
 * @cw_min: minimum contention winकरोw [a value of the क्रमm
 *      2^n-1 in the range 1..32767]
 * @cw_max: maximum contention winकरोw [like @cw_min]
 * @cot: maximum burst समय in units of 32 usecs, 0 meaning disabled
 * @aअगरsn: arbitration पूर्णांकerframe space [0..255]
 *
 */
काष्ठा ieee80211_wmm_ac अणु
	u16 cw_min;
	u16 cw_max;
	u16 cot;
	u8 aअगरsn;
पूर्ण;

काष्ठा ieee80211_wmm_rule अणु
	काष्ठा ieee80211_wmm_ac client[IEEE80211_NUM_ACS];
	काष्ठा ieee80211_wmm_ac ap[IEEE80211_NUM_ACS];
पूर्ण;

काष्ठा ieee80211_reg_rule अणु
	काष्ठा ieee80211_freq_range freq_range;
	काष्ठा ieee80211_घातer_rule घातer_rule;
	काष्ठा ieee80211_wmm_rule wmm_rule;
	u32 flags;
	u32 dfs_cac_ms;
	bool has_wmm;
पूर्ण;

काष्ठा ieee80211_regकरोमुख्य अणु
	काष्ठा rcu_head rcu_head;
	u32 n_reg_rules;
	अक्षर alpha2[3];
	क्रमागत nl80211_dfs_regions dfs_region;
	काष्ठा ieee80211_reg_rule reg_rules[];
पूर्ण;

#घोषणा REG_RULE_EXT(start, end, bw, gain, eirp, dfs_cac, reg_flags)	\
अणु									\
	.freq_range.start_freq_khz = MHZ_TO_KHZ(start),			\
	.freq_range.end_freq_khz = MHZ_TO_KHZ(end),			\
	.freq_range.max_bandwidth_khz = MHZ_TO_KHZ(bw),			\
	.घातer_rule.max_antenna_gain = DBI_TO_MBI(gain),		\
	.घातer_rule.max_eirp = DBM_TO_MBM(eirp),			\
	.flags = reg_flags,						\
	.dfs_cac_ms = dfs_cac,						\
पूर्ण

#घोषणा REG_RULE(start, end, bw, gain, eirp, reg_flags) \
	REG_RULE_EXT(start, end, bw, gain, eirp, 0, reg_flags)

#पूर्ण_अगर
