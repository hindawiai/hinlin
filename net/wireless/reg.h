<शैली गुरु>
#अगर_अघोषित __NET_WIRELESS_REG_H
#घोषणा __NET_WIRELESS_REG_H

#समावेश <net/cfg80211.h>

/*
 * Copyright 2008-2011	Luis R. Rodriguez <mcgrof@qca.qualcomm.com>
 * Copyright (C) 2019 Intel Corporation
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

क्रमागत ieee80211_regd_source अणु
	REGD_SOURCE_INTERNAL_DB,
	REGD_SOURCE_CRDA,
	REGD_SOURCE_CACHED,
पूर्ण;

बाह्य स्थिर काष्ठा ieee80211_regकरोमुख्य __rcu *cfg80211_regकरोमुख्य;

bool reg_is_valid_request(स्थिर अक्षर *alpha2);
bool is_world_regकरोm(स्थिर अक्षर *alpha2);
bool reg_supported_dfs_region(क्रमागत nl80211_dfs_regions dfs_region);
क्रमागत nl80211_dfs_regions reg_get_dfs_region(काष्ठा wiphy *wiphy);

पूर्णांक regulatory_hपूर्णांक_user(स्थिर अक्षर *alpha2,
			 क्रमागत nl80211_user_reg_hपूर्णांक_type user_reg_hपूर्णांक_type);

/**
 * regulatory_hपूर्णांक_inकरोor - hपूर्णांक operation in inकरोor env. or not
 * @is_inकरोor: अगर true indicates that user space thinks that the
 * device is operating in an inकरोor environment.
 * @portid: the netlink port ID on which the hपूर्णांक was given.
 */
पूर्णांक regulatory_hपूर्णांक_inकरोor(bool is_inकरोor, u32 portid);

/**
 * regulatory_netlink_notअगरy - notअगरy on released netlink socket
 * @portid: the netlink socket port ID
 */
व्योम regulatory_netlink_notअगरy(u32 portid);

व्योम wiphy_regulatory_रेजिस्टर(काष्ठा wiphy *wiphy);
व्योम wiphy_regulatory_deरेजिस्टर(काष्ठा wiphy *wiphy);

पूर्णांक __init regulatory_init(व्योम);
व्योम regulatory_निकास(व्योम);

पूर्णांक set_regकरोm(स्थिर काष्ठा ieee80211_regकरोमुख्य *rd,
	       क्रमागत ieee80211_regd_source regd_src);

अचिन्हित पूर्णांक reg_get_max_bandwidth(स्थिर काष्ठा ieee80211_regकरोमुख्य *rd,
				   स्थिर काष्ठा ieee80211_reg_rule *rule);

bool reg_last_request_cell_base(व्योम);

/**
 * regulatory_hपूर्णांक_found_beacon - hपूर्णांकs a beacon was found on a channel
 * @wiphy: the wireless device where the beacon was found on
 * @beacon_chan: the channel on which the beacon was found on
 * @gfp: context flags
 *
 * This inक्रमms the wireless core that a beacon from an AP was found on
 * the channel provided. This allows the wireless core to make educated
 * guesses on regulatory to help with world roaming. This is only used क्रम
 * world roaming -- when we करो not know our current location. This is
 * only useful on channels 12, 13 and 14 on the 2 GHz band as channels
 * 1-11 are alपढ़ोy enabled by the world regulatory करोमुख्य; and on
 * non-radar 5 GHz channels.
 *
 * Drivers करो not need to call this, cfg80211 will करो it क्रम after a scan
 * on a newly found BSS. If you cannot make use of this feature you can
 * set the wiphy->disable_beacon_hपूर्णांकs to true.
 */
पूर्णांक regulatory_hपूर्णांक_found_beacon(काष्ठा wiphy *wiphy,
				 काष्ठा ieee80211_channel *beacon_chan,
				 gfp_t gfp);

/**
 * regulatory_hपूर्णांक_country_ie - hपूर्णांकs a country IE as a regulatory करोमुख्य
 * @wiphy: the wireless device giving the hपूर्णांक (used only क्रम reporting
 *	conflicts)
 * @band: the band on which the country IE was received on. This determines
 *	the band we'll process the country IE channel triplets क्रम.
 * @country_ie: poपूर्णांकer to the country IE
 * @country_ie_len: length of the country IE
 *
 * We will पूर्णांकersect the rd with the what CRDA tells us should apply
 * क्रम the alpha2 this country IE beदीर्घs to, this prevents APs from
 * sending us incorrect or outdated inक्रमmation against a country.
 *
 * The AP is expected to provide Country IE channel triplets क्रम the
 * band it is on. It is technically possible क्रम APs to send channel
 * country IE triplets even क्रम channels outside of the band they are
 * in but क्रम that they would have to use the regulatory extension
 * in combination with a triplet but this behaviour is currently
 * not observed. For this reason अगर a triplet is seen with channel
 * inक्रमmation क्रम a band the BSS is not present in it will be ignored.
 */
व्योम regulatory_hपूर्णांक_country_ie(काष्ठा wiphy *wiphy,
			 क्रमागत nl80211_band band,
			 स्थिर u8 *country_ie,
			 u8 country_ie_len);

/**
 * regulatory_hपूर्णांक_disconnect - inक्रमms all devices have been disconnected
 *
 * Regulotory rules can be enhanced further upon scanning and upon
 * connection to an AP. These rules become stale अगर we disconnect
 * and go to another country, whether or not we suspend and resume.
 * If we suspend, go to another country and resume we'll स्वतःmatically
 * get disconnected लघुly after resuming and things will be reset as well.
 * This routine is a helper to restore regulatory settings to how they were
 * prior to our first connect attempt. This includes ignoring country IE and
 * beacon regulatory hपूर्णांकs. The ieee80211_regकरोm module parameter will always
 * be respected but अगर a user had set the regulatory करोमुख्य that will take
 * precedence.
 *
 * Must be called from process context.
 */
व्योम regulatory_hपूर्णांक_disconnect(व्योम);

/**
 * cfg80211_get_unii - get the U-NII band क्रम the frequency
 * @freq: the frequency क्रम which we want to get the UNII band.

 * Get a value specअगरying the U-NII band frequency beदीर्घs to.
 * U-NII bands are defined by the FCC in C.F.R 47 part 15.
 *
 * Returns -EINVAL अगर freq is invalid, 0 क्रम UNII-1, 1 क्रम UNII-2A,
 * 2 क्रम UNII-2B, 3 क्रम UNII-2C and 4 क्रम UNII-3.
 */
पूर्णांक cfg80211_get_unii(पूर्णांक freq);

/**
 * regulatory_inकरोor_allowed - is inकरोor operation allowed
 */
bool regulatory_inकरोor_allowed(व्योम);

/*
 * Grace period to समयout pre-CAC results on the dfs channels. This समयout
 * value is used क्रम Non-ETSI करोमुख्य.
 * TODO: May be make this समयout available through regdb?
 */
#घोषणा REG_PRE_CAC_EXPIRY_GRACE_MS 2000

/**
 * regulatory_propagate_dfs_state - Propagate DFS channel state to other wiphys
 * @wiphy - wiphy on which radar is detected and the event will be propagated
 *	to other available wiphys having the same DFS करोमुख्य
 * @chandef - Channel definition of radar detected channel
 * @dfs_state - DFS channel state to be set
 * @event - Type of radar event which triggered this DFS state change
 *
 * This function should be called with rtnl lock held.
 */
व्योम regulatory_propagate_dfs_state(काष्ठा wiphy *wiphy,
				    काष्ठा cfg80211_chan_def *chandef,
				    क्रमागत nl80211_dfs_state dfs_state,
				    क्रमागत nl80211_radar_event event);

/**
 * reg_dfs_करोमुख्य_same - Checks अगर both wiphy have same DFS करोमुख्य configured
 * @wiphy1 - wiphy it's dfs_region to be checked against that of wiphy2
 * @wiphy2 - wiphy it's dfs_region to be checked against that of wiphy1
 */
bool reg_dfs_करोमुख्य_same(काष्ठा wiphy *wiphy1, काष्ठा wiphy *wiphy2);

/**
 * reg_reload_regdb - reload the regulatory.db firmware file
 */
पूर्णांक reg_reload_regdb(व्योम);

बाह्य स्थिर u8 shipped_regdb_certs[];
बाह्य अचिन्हित पूर्णांक shipped_regdb_certs_len;
बाह्य स्थिर u8 extra_regdb_certs[];
बाह्य अचिन्हित पूर्णांक extra_regdb_certs_len;

#पूर्ण_अगर  /* __NET_WIRELESS_REG_H */
