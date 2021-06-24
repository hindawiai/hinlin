<शैली गुरु>
#अगर_अघोषित __LINUX_NL80211_H
#घोषणा __LINUX_NL80211_H
/*
 * 802.11 netlink पूर्णांकerface खुला header
 *
 * Copyright 2006-2010 Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2008 Michael Wu <flamingice@sourmilk.net>
 * Copyright 2008 Luis Carlos Cobo <luisca@cozybit.com>
 * Copyright 2008 Michael Buesch <m@bues.ch>
 * Copyright 2008, 2009 Luis R. Rodriguez <lrodriguez@atheros.com>
 * Copyright 2008 Jouni Malinen <jouni.malinen@atheros.com>
 * Copyright 2008 Colin McCabe <colin@cozybit.com>
 * Copyright 2015-2017	Intel Deutschland GmbH
 * Copyright (C) 2018-2020 Intel Corporation
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
 *
 */

/*
 * This header file defines the userspace API to the wireless stack. Please
 * be careful not to अवरोध things - i.e. करोn't move anything around or so
 * unless you can demonstrate that it अवरोधs neither API nor ABI.
 *
 * Additions to the API should be accompanied by actual implementations in
 * an upstream driver, so that example implementations exist in हाल there
 * are ever concerns about the precise semantics of the API or changes are
 * needed, and to ensure that code क्रम dead (no दीर्घer implemented) API
 * can actually be identअगरied and हटाओd.
 * Nonetheless, semantics should also be करोcumented carefully in this file.
 */

#समावेश <linux/types.h>

#घोषणा NL80211_GENL_NAME "nl80211"

#घोषणा NL80211_MULTICAST_GROUP_CONFIG		"config"
#घोषणा NL80211_MULTICAST_GROUP_SCAN		"scan"
#घोषणा NL80211_MULTICAST_GROUP_REG		"regulatory"
#घोषणा NL80211_MULTICAST_GROUP_MLME		"mlme"
#घोषणा NL80211_MULTICAST_GROUP_VENDOR		"vendor"
#घोषणा NL80211_MULTICAST_GROUP_न_अंक		"nan"
#घोषणा NL80211_MULTICAST_GROUP_TESTMODE	"testmode"

#घोषणा NL80211_EDMG_BW_CONFIG_MIN	4
#घोषणा NL80211_EDMG_BW_CONFIG_MAX	15
#घोषणा NL80211_EDMG_CHANNELS_MIN	1
#घोषणा NL80211_EDMG_CHANNELS_MAX	0x3c /* 0b00111100 */

/**
 * DOC: Station handling
 *
 * Stations are added per पूर्णांकerface, but a special हाल exists with VLAN
 * पूर्णांकerfaces. When a station is bound to an AP पूर्णांकerface, it may be moved
 * पूर्णांकo a VLAN identअगरied by a VLAN पूर्णांकerface index (%NL80211_ATTR_STA_VLAN).
 * The station is still assumed to beदीर्घ to the AP पूर्णांकerface it was added
 * to.
 *
 * Station handling varies per पूर्णांकerface type and depending on the driver's
 * capabilities.
 *
 * For drivers supporting TDLS with बाह्यal setup (WIPHY_FLAG_SUPPORTS_TDLS
 * and WIPHY_FLAG_TDLS_EXTERNAL_SETUP), the station lअगरeसमय is as follows:
 *  - a setup station entry is added, not yet authorized, without any rate
 *    or capability inक्रमmation, this just exists to aव्योम race conditions
 *  - when the TDLS setup is करोne, a single NL80211_CMD_SET_STATION is valid
 *    to add rate and capability inक्रमmation to the station and at the same
 *    समय mark it authorized.
 *  - %NL80211_TDLS_ENABLE_LINK is then used
 *  - after this, the only valid operation is to हटाओ it by tearing करोwn
 *    the TDLS link (%NL80211_TDLS_DISABLE_LINK)
 *
 * TODO: need more info क्रम other पूर्णांकerface types
 */

/**
 * DOC: Frame transmission/registration support
 *
 * Frame transmission and registration support exists to allow userspace
 * management entities such as wpa_supplicant react to management frames
 * that are not being handled by the kernel. This includes, क्रम example,
 * certain classes of action frames that cannot be handled in the kernel
 * क्रम various reasons.
 *
 * Frame registration is करोne on a per-पूर्णांकerface basis and registrations
 * cannot be हटाओd other than by closing the socket. It is possible to
 * specअगरy a registration filter to रेजिस्टर, क्रम example, only क्रम a
 * certain type of action frame. In particular with action frames, those
 * that userspace रेजिस्टरs क्रम will not be वापसed as unhandled by the
 * driver, so that the रेजिस्टरed application has to take responsibility
 * क्रम करोing that.
 *
 * The type of frame that can be रेजिस्टरed क्रम is also dependent on the
 * driver and पूर्णांकerface type. The frame types are advertised in wiphy
 * attributes so applications know what to expect.
 *
 * NOTE: When an पूर्णांकerface changes type जबतक registrations are active,
 *       these registrations are ignored until the पूर्णांकerface type is
 *       changed again. This means that changing the पूर्णांकerface type can
 *       lead to a situation that couldn't otherwise be produced, but
 *       any such registrations will be करोrmant in the sense that they
 *       will not be serviced, i.e. they will not receive any frames.
 *
 * Frame transmission allows userspace to send क्रम example the required
 * responses to action frames. It is subject to some sanity checking,
 * but many frames can be transmitted. When a frame was transmitted, its
 * status is indicated to the sending socket.
 *
 * For more technical details, see the corresponding command descriptions
 * below.
 */

/**
 * DOC: Virtual पूर्णांकerface / concurrency capabilities
 *
 * Some devices are able to operate with भव MACs, they can have
 * more than one भव पूर्णांकerface. The capability handling क्रम this
 * is a bit complex though, as there may be a number of restrictions
 * on the types of concurrency that are supported.
 *
 * To start with, each device supports the पूर्णांकerface types listed in
 * the %NL80211_ATTR_SUPPORTED_IFTYPES attribute, but by listing the
 * types there no concurrency is implied.
 *
 * Once concurrency is desired, more attributes must be observed:
 * To start with, since some पूर्णांकerface types are purely managed in
 * software, like the AP-VLAN type in mac80211 क्रम example, there's
 * an additional list of these, they can be added at any समय and
 * are only restricted by some semantic restrictions (e.g. AP-VLAN
 * cannot be added without a corresponding AP पूर्णांकerface). This list
 * is exported in the %NL80211_ATTR_SOFTWARE_IFTYPES attribute.
 *
 * Further, the list of supported combinations is exported. This is
 * in the %NL80211_ATTR_INTERFACE_COMBINATIONS attribute. Basically,
 * it exports a list of "groups", and at any poपूर्णांक in समय the
 * पूर्णांकerfaces that are currently active must fall पूर्णांकo any one of
 * the advertised groups. Within each group, there are restrictions
 * on the number of पूर्णांकerfaces of dअगरferent types that are supported
 * and also the number of dअगरferent channels, aदीर्घ with potentially
 * some other restrictions. See &क्रमागत nl80211_अगर_combination_attrs.
 *
 * All together, these attributes define the concurrency of भव
 * पूर्णांकerfaces that a given device supports.
 */

/**
 * DOC: packet coalesce support
 *
 * In most हालs, host that receives IPv4 and IPv6 multicast/broadcast
 * packets करोes not करो anything with these packets. Thereक्रमe the
 * reception of these unwanted packets causes unnecessary processing
 * and घातer consumption.
 *
 * Packet coalesce feature helps to reduce number of received पूर्णांकerrupts
 * to host by buffering these packets in firmware/hardware क्रम some
 * predefined समय. Received पूर्णांकerrupt will be generated when one of the
 * following events occur.
 * a) Expiration of hardware समयr whose expiration समय is set to maximum
 * coalescing delay of matching coalesce rule.
 * b) Coalescing buffer in hardware reaches it's limit.
 * c) Packet करोesn't match any of the configured coalesce rules.
 *
 * User needs to configure following parameters क्रम creating a coalesce
 * rule.
 * a) Maximum coalescing delay
 * b) List of packet patterns which needs to be matched
 * c) Condition क्रम coalescence. pattern 'match' or 'no match'
 * Multiple such rules can be created.
 */

/**
 * DOC: WPA/WPA2 EAPOL handshake offload
 *
 * By setting @NL80211_EXT_FEATURE_4WAY_HANDSHAKE_STA_PSK flag drivers
 * can indicate they support offloading EAPOL handshakes क्रम WPA/WPA2
 * preshared key authentication in station mode. In %NL80211_CMD_CONNECT
 * the preshared key should be specअगरied using %NL80211_ATTR_PMK. Drivers
 * supporting this offload may reject the %NL80211_CMD_CONNECT when no
 * preshared key material is provided, क्रम example when that driver करोes
 * not support setting the temporal keys through %NL80211_CMD_NEW_KEY.
 *
 * Similarly @NL80211_EXT_FEATURE_4WAY_HANDSHAKE_STA_1X flag can be
 * set by drivers indicating offload support of the PTK/GTK EAPOL
 * handshakes during 802.1X authentication in station mode. In order to
 * use the offload the %NL80211_CMD_CONNECT should have
 * %NL80211_ATTR_WANT_1X_4WAY_HS attribute flag. Drivers supporting this
 * offload may reject the %NL80211_CMD_CONNECT when the attribute flag is
 * not present.
 *
 * By setting @NL80211_EXT_FEATURE_4WAY_HANDSHAKE_AP_PSK flag drivers
 * can indicate they support offloading EAPOL handshakes क्रम WPA/WPA2
 * preshared key authentication in AP mode. In %NL80211_CMD_START_AP
 * the preshared key should be specअगरied using %NL80211_ATTR_PMK. Drivers
 * supporting this offload may reject the %NL80211_CMD_START_AP when no
 * preshared key material is provided, क्रम example when that driver करोes
 * not support setting the temporal keys through %NL80211_CMD_NEW_KEY.
 *
 * For 802.1X the PMK or PMK-R0 are set by providing %NL80211_ATTR_PMK
 * using %NL80211_CMD_SET_PMK. For offloaded FT support also
 * %NL80211_ATTR_PMKR0_NAME must be provided.
 */

/**
 * DOC: FILS shared key authentication offload
 *
 * FILS shared key authentication offload can be advertized by drivers by
 * setting @NL80211_EXT_FEATURE_FILS_SK_OFFLOAD flag. The drivers that support
 * FILS shared key authentication offload should be able to स्थिरruct the
 * authentication and association frames क्रम FILS shared key authentication and
 * eventually करो a key derivation as per IEEE 802.11ai. The below additional
 * parameters should be given to driver in %NL80211_CMD_CONNECT and/or in
 * %NL80211_CMD_UPDATE_CONNECT_PARAMS.
 *	%NL80211_ATTR_FILS_ERP_USERNAME - used to स्थिरruct keyname_nai
 *	%NL80211_ATTR_FILS_ERP_REALM - used to स्थिरruct keyname_nai
 *	%NL80211_ATTR_FILS_ERP_NEXT_SEQ_NUM - used to स्थिरruct erp message
 *	%NL80211_ATTR_FILS_ERP_RRK - used to generate the rIK and rMSK
 * rIK should be used to generate an authentication tag on the ERP message and
 * rMSK should be used to derive a PMKSA.
 * rIK, rMSK should be generated and keyname_nai, sequence number should be used
 * as specअगरied in IETF RFC 6696.
 *
 * When FILS shared key authentication is completed, driver needs to provide the
 * below additional parameters to userspace, which can be either after setting
 * up a connection or after roaming.
 *	%NL80211_ATTR_FILS_KEK - used क्रम key renewal
 *	%NL80211_ATTR_FILS_ERP_NEXT_SEQ_NUM - used in further EAP-RP exchanges
 *	%NL80211_ATTR_PMKID - used to identअगरy the PMKSA used/generated
 *	%Nl80211_ATTR_PMK - used to update PMKSA cache in userspace
 * The PMKSA can be मुख्यtained in userspace persistently so that it can be used
 * later after reboots or wअगरi turn off/on also.
 *
 * %NL80211_ATTR_FILS_CACHE_ID is the cache identअगरier advertized by a FILS
 * capable AP supporting PMK caching. It specअगरies the scope within which the
 * PMKSAs are cached in an ESS. %NL80211_CMD_SET_PMKSA and
 * %NL80211_CMD_DEL_PMKSA are enhanced to allow support क्रम PMKSA caching based
 * on FILS cache identअगरier. Additionally %NL80211_ATTR_PMK is used with
 * %NL80211_SET_PMKSA to specअगरy the PMK corresponding to a PMKSA क्रम driver to
 * use in a FILS shared key connection with PMKSA caching.
 */

/**
 * DOC: SAE authentication offload
 *
 * By setting @NL80211_EXT_FEATURE_SAE_OFFLOAD flag drivers can indicate they
 * support offloading SAE authentication क्रम WPA3-Personal networks in station
 * mode. Similarly @NL80211_EXT_FEATURE_SAE_OFFLOAD_AP flag can be set by
 * drivers indicating the offload support in AP mode.
 *
 * The password क्रम SAE should be specअगरied using %NL80211_ATTR_SAE_PASSWORD in
 * %NL80211_CMD_CONNECT and %NL80211_CMD_START_AP क्रम station and AP mode
 * respectively.
 */

/**
 * DOC: VLAN offload support क्रम setting group keys and binding STAs to VLANs
 *
 * By setting @NL80211_EXT_FEATURE_VLAN_OFFLOAD flag drivers can indicate they
 * support offloading VLAN functionality in a manner where the driver exposes a
 * single netdev that uses VLAN tagged frames and separate VLAN-specअगरic netdevs
 * can then be added using RTM_NEWLINK/IFLA_VLAN_ID similarly to the Ethernet
 * हाल. Frames received from stations that are not asचिन्हित to any VLAN are
 * delivered on the मुख्य netdev and frames to such stations can be sent through
 * that मुख्य netdev.
 *
 * %NL80211_CMD_NEW_KEY (क्रम group keys), %NL80211_CMD_NEW_STATION, and
 * %NL80211_CMD_SET_STATION will optionally specअगरy vlan_id using
 * %NL80211_ATTR_VLAN_ID.
 */

/**
 * DOC: TID configuration
 *
 * TID config support can be checked in the %NL80211_ATTR_TID_CONFIG
 * attribute given in wiphy capabilities.
 *
 * The necessary configuration parameters are mentioned in
 * &क्रमागत nl80211_tid_config_attr and it will be passed to the
 * %NL80211_CMD_SET_TID_CONFIG command in %NL80211_ATTR_TID_CONFIG.
 *
 * If the configuration needs to be applied क्रम specअगरic peer then the MAC
 * address of the peer needs to be passed in %NL80211_ATTR_MAC, otherwise the
 * configuration will be applied क्रम all the connected peers in the vअगर except
 * any peers that have peer specअगरic configuration क्रम the TID by शेष; अगर
 * the %NL80211_TID_CONFIG_ATTR_OVERRIDE flag is set, peer specअगरic values
 * will be overwritten.
 *
 * All this configuration is valid only क्रम STA's current connection
 * i.e. the configuration will be reset to शेष when the STA connects back
 * after disconnection/roaming, and this configuration will be cleared when
 * the पूर्णांकerface goes करोwn.
 */

/**
 * क्रमागत nl80211_commands - supported nl80211 commands
 *
 * @NL80211_CMD_UNSPEC: unspecअगरied command to catch errors
 *
 * @NL80211_CMD_GET_WIPHY: request inक्रमmation about a wiphy or dump request
 *	to get a list of all present wiphys.
 * @NL80211_CMD_SET_WIPHY: set wiphy parameters, needs %NL80211_ATTR_WIPHY or
 *	%NL80211_ATTR_IFINDEX; can be used to set %NL80211_ATTR_WIPHY_NAME,
 *	%NL80211_ATTR_WIPHY_TXQ_PARAMS, %NL80211_ATTR_WIPHY_FREQ,
 *	%NL80211_ATTR_WIPHY_FREQ_OFFSET (and the attributes determining the
 *	channel width; this is used क्रम setting monitor mode channel),
 *	%NL80211_ATTR_WIPHY_RETRY_SHORT, %NL80211_ATTR_WIPHY_RETRY_LONG,
 *	%NL80211_ATTR_WIPHY_FRAG_THRESHOLD, and/or
 *	%NL80211_ATTR_WIPHY_RTS_THRESHOLD.  However, क्रम setting the channel,
 *	see %NL80211_CMD_SET_CHANNEL instead, the support here is क्रम backward
 *	compatibility only.
 * @NL80211_CMD_NEW_WIPHY: Newly created wiphy, response to get request
 *	or नाम notअगरication. Has attributes %NL80211_ATTR_WIPHY and
 *	%NL80211_ATTR_WIPHY_NAME.
 * @NL80211_CMD_DEL_WIPHY: Wiphy deleted. Has attributes
 *	%NL80211_ATTR_WIPHY and %NL80211_ATTR_WIPHY_NAME.
 *
 * @NL80211_CMD_GET_INTERFACE: Request an पूर्णांकerface's configuration;
 *	either a dump request क्रम all पूर्णांकerfaces or a specअगरic get with a
 *	single %NL80211_ATTR_IFINDEX is supported.
 * @NL80211_CMD_SET_INTERFACE: Set type of a भव पूर्णांकerface, requires
 *	%NL80211_ATTR_IFINDEX and %NL80211_ATTR_IFTYPE.
 * @NL80211_CMD_NEW_INTERFACE: Newly created भव पूर्णांकerface or response
 *	to %NL80211_CMD_GET_INTERFACE. Has %NL80211_ATTR_IFINDEX,
 *	%NL80211_ATTR_WIPHY and %NL80211_ATTR_IFTYPE attributes. Can also
 *	be sent from userspace to request creation of a new भव पूर्णांकerface,
 *	then requires attributes %NL80211_ATTR_WIPHY, %NL80211_ATTR_IFTYPE and
 *	%NL80211_ATTR_IFNAME.
 * @NL80211_CMD_DEL_INTERFACE: Virtual पूर्णांकerface was deleted, has attributes
 *	%NL80211_ATTR_IFINDEX and %NL80211_ATTR_WIPHY. Can also be sent from
 *	userspace to request deletion of a भव पूर्णांकerface, then requires
 *	attribute %NL80211_ATTR_IFINDEX.
 *
 * @NL80211_CMD_GET_KEY: Get sequence counter inक्रमmation क्रम a key specअगरied
 *	by %NL80211_ATTR_KEY_IDX and/or %NL80211_ATTR_MAC.
 * @NL80211_CMD_SET_KEY: Set key attributes %NL80211_ATTR_KEY_DEFAULT,
 *	%NL80211_ATTR_KEY_DEFAULT_MGMT, or %NL80211_ATTR_KEY_THRESHOLD.
 * @NL80211_CMD_NEW_KEY: add a key with given %NL80211_ATTR_KEY_DATA,
 *	%NL80211_ATTR_KEY_IDX, %NL80211_ATTR_MAC, %NL80211_ATTR_KEY_CIPHER,
 *	and %NL80211_ATTR_KEY_SEQ attributes.
 * @NL80211_CMD_DEL_KEY: delete a key identअगरied by %NL80211_ATTR_KEY_IDX
 *	or %NL80211_ATTR_MAC.
 *
 * @NL80211_CMD_GET_BEACON: (not used)
 * @NL80211_CMD_SET_BEACON: change the beacon on an access poपूर्णांक पूर्णांकerface
 *	using the %NL80211_ATTR_BEACON_HEAD and %NL80211_ATTR_BEACON_TAIL
 *	attributes. For drivers that generate the beacon and probe responses
 *	पूर्णांकernally, the following attributes must be provided: %NL80211_ATTR_IE,
 *	%NL80211_ATTR_IE_PROBE_RESP and %NL80211_ATTR_IE_ASSOC_RESP.
 * @NL80211_CMD_START_AP: Start AP operation on an AP पूर्णांकerface, parameters
 *	are like क्रम %NL80211_CMD_SET_BEACON, and additionally parameters that
 *	करो not change are used, these include %NL80211_ATTR_BEACON_INTERVAL,
 *	%NL80211_ATTR_DTIM_PERIOD, %NL80211_ATTR_SSID,
 *	%NL80211_ATTR_HIDDEN_SSID, %NL80211_ATTR_CIPHERS_PAIRWISE,
 *	%NL80211_ATTR_CIPHER_GROUP, %NL80211_ATTR_WPA_VERSIONS,
 *	%NL80211_ATTR_AKM_SUITES, %NL80211_ATTR_PRIVACY,
 *	%NL80211_ATTR_AUTH_TYPE, %NL80211_ATTR_INACTIVITY_TIMEOUT,
 *	%NL80211_ATTR_ACL_POLICY and %NL80211_ATTR_MAC_ADDRS.
 *	The channel to use can be set on the पूर्णांकerface or be given using the
 *	%NL80211_ATTR_WIPHY_FREQ and %NL80211_ATTR_WIPHY_FREQ_OFFSET, and the
 *	attributes determining channel width.
 * @NL80211_CMD_NEW_BEACON: old alias क्रम %NL80211_CMD_START_AP
 * @NL80211_CMD_STOP_AP: Stop AP operation on the given पूर्णांकerface
 * @NL80211_CMD_DEL_BEACON: old alias क्रम %NL80211_CMD_STOP_AP
 *
 * @NL80211_CMD_GET_STATION: Get station attributes क्रम station identअगरied by
 *	%NL80211_ATTR_MAC on the पूर्णांकerface identअगरied by %NL80211_ATTR_IFINDEX.
 * @NL80211_CMD_SET_STATION: Set station attributes क्रम station identअगरied by
 *	%NL80211_ATTR_MAC on the पूर्णांकerface identअगरied by %NL80211_ATTR_IFINDEX.
 * @NL80211_CMD_NEW_STATION: Add a station with given attributes to the
 *	पूर्णांकerface identअगरied by %NL80211_ATTR_IFINDEX.
 * @NL80211_CMD_DEL_STATION: Remove a station identअगरied by %NL80211_ATTR_MAC
 *	or, अगर no MAC address given, all stations, on the पूर्णांकerface identअगरied
 *	by %NL80211_ATTR_IFINDEX. %NL80211_ATTR_MGMT_SUBTYPE and
 *	%NL80211_ATTR_REASON_CODE can optionally be used to specअगरy which type
 *	of disconnection indication should be sent to the station
 *	(Deauthentication or Disassociation frame and reason code क्रम that
 *	frame).
 *
 * @NL80211_CMD_GET_MPATH: Get mesh path attributes क्रम mesh path to
 * 	destination %NL80211_ATTR_MAC on the पूर्णांकerface identअगरied by
 * 	%NL80211_ATTR_IFINDEX.
 * @NL80211_CMD_SET_MPATH:  Set mesh path attributes क्रम mesh path to
 * 	destination %NL80211_ATTR_MAC on the पूर्णांकerface identअगरied by
 * 	%NL80211_ATTR_IFINDEX.
 * @NL80211_CMD_NEW_MPATH: Create a new mesh path क्रम the destination given by
 *	%NL80211_ATTR_MAC via %NL80211_ATTR_MPATH_NEXT_HOP.
 * @NL80211_CMD_DEL_MPATH: Delete a mesh path to the destination given by
 *	%NL80211_ATTR_MAC.
 * @NL80211_CMD_NEW_PATH: Add a mesh path with given attributes to the
 *	पूर्णांकerface identअगरied by %NL80211_ATTR_IFINDEX.
 * @NL80211_CMD_DEL_PATH: Remove a mesh path identअगरied by %NL80211_ATTR_MAC
 *	or, अगर no MAC address given, all mesh paths, on the पूर्णांकerface identअगरied
 *	by %NL80211_ATTR_IFINDEX.
 * @NL80211_CMD_SET_BSS: Set BSS attributes क्रम BSS identअगरied by
 *	%NL80211_ATTR_IFINDEX.
 *
 * @NL80211_CMD_GET_REG: ask the wireless core to send us its currently set
 *	regulatory करोमुख्य. If %NL80211_ATTR_WIPHY is specअगरied and the device
 *	has a निजी regulatory करोमुख्य, it will be वापसed. Otherwise, the
 *	global regकरोमुख्य will be वापसed.
 *	A device will have a निजी regulatory करोमुख्य अगर it uses the
 *	regulatory_hपूर्णांक() API. Even when a निजी regकरोमुख्य is used the channel
 *	inक्रमmation will still be mended according to further hपूर्णांकs from
 *	the regulatory core to help with compliance. A dump version of this API
 *	is now available which will वापसs the global regकरोमुख्य as well as
 *	all निजी regकरोमुख्यs of present wiphys (क्रम those that have it).
 *	If a wiphy is self-managed (%NL80211_ATTR_WIPHY_SELF_MANAGED_REG), then
 *	its निजी regकरोमुख्य is the only valid one क्रम it. The regulatory
 *	core is not used to help with compliance in this हाल.
 * @NL80211_CMD_SET_REG: Set current regulatory करोमुख्य. CRDA sends this command
 *	after being queried by the kernel. CRDA replies by sending a regulatory
 *	करोमुख्य काष्ठाure which consists of %NL80211_ATTR_REG_ALPHA set to our
 *	current alpha2 अगर it found a match. It also provides
 * 	NL80211_ATTR_REG_RULE_FLAGS, and a set of regulatory rules. Each
 * 	regulatory rule is a nested set of attributes  given by
 * 	%NL80211_ATTR_REG_RULE_FREQ_[START|END] and
 * 	%NL80211_ATTR_FREQ_RANGE_MAX_BW with an attached घातer rule given by
 * 	%NL80211_ATTR_REG_RULE_POWER_MAX_ANT_GAIN and
 * 	%NL80211_ATTR_REG_RULE_POWER_MAX_EIRP.
 * @NL80211_CMD_REQ_SET_REG: ask the wireless core to set the regulatory करोमुख्य
 * 	to the specअगरied ISO/IEC 3166-1 alpha2 country code. The core will
 * 	store this as a valid request and then query userspace क्रम it.
 *
 * @NL80211_CMD_GET_MESH_CONFIG: Get mesh networking properties क्रम the
 *	पूर्णांकerface identअगरied by %NL80211_ATTR_IFINDEX
 *
 * @NL80211_CMD_SET_MESH_CONFIG: Set mesh networking properties क्रम the
 *      पूर्णांकerface identअगरied by %NL80211_ATTR_IFINDEX
 *
 * @NL80211_CMD_SET_MGMT_EXTRA_IE: Set extra IEs क्रम management frames. The
 *	पूर्णांकerface is identअगरied with %NL80211_ATTR_IFINDEX and the management
 *	frame subtype with %NL80211_ATTR_MGMT_SUBTYPE. The extra IE data to be
 *	added to the end of the specअगरied management frame is specअगरied with
 *	%NL80211_ATTR_IE. If the command succeeds, the requested data will be
 *	added to all specअगरied management frames generated by
 *	kernel/firmware/driver.
 *	Note: This command has been हटाओd and it is only reserved at this
 *	poपूर्णांक to aव्योम re-using existing command number. The functionality this
 *	command was planned क्रम has been provided with cleaner design with the
 *	option to specअगरy additional IEs in NL80211_CMD_TRIGGER_SCAN,
 *	NL80211_CMD_AUTHENTICATE, NL80211_CMD_ASSOCIATE,
 *	NL80211_CMD_DEAUTHENTICATE, and NL80211_CMD_DISASSOCIATE.
 *
 * @NL80211_CMD_GET_SCAN: get scan results
 * @NL80211_CMD_TRIGGER_SCAN: trigger a new scan with the given parameters
 *	%NL80211_ATTR_TX_NO_CCK_RATE is used to decide whether to send the
 *	probe requests at CCK rate or not. %NL80211_ATTR_BSSID can be used to
 *	specअगरy a BSSID to scan क्रम; अगर not included, the wildcard BSSID will
 *	be used.
 * @NL80211_CMD_NEW_SCAN_RESULTS: scan notअगरication (as a reply to
 *	NL80211_CMD_GET_SCAN and on the "scan" multicast group)
 * @NL80211_CMD_SCAN_ABORTED: scan was पातed, क्रम unspecअगरied reasons,
 *	partial scan results may be available
 *
 * @NL80211_CMD_START_SCHED_SCAN: start a scheduled scan at certain
 *	पूर्णांकervals and certain number of cycles, as specअगरied by
 *	%NL80211_ATTR_SCHED_SCAN_PLANS. If %NL80211_ATTR_SCHED_SCAN_PLANS is
 *	not specअगरied and only %NL80211_ATTR_SCHED_SCAN_INTERVAL is specअगरied,
 *	scheduled scan will run in an infinite loop with the specअगरied पूर्णांकerval.
 *	These attributes are mutually exculsive,
 *	i.e. NL80211_ATTR_SCHED_SCAN_INTERVAL must not be passed अगर
 *	NL80211_ATTR_SCHED_SCAN_PLANS is defined.
 *	If क्रम some reason scheduled scan is पातed by the driver, all scan
 *	plans are canceled (including scan plans that did not start yet).
 *	Like with normal scans, अगर SSIDs (%NL80211_ATTR_SCAN_SSIDS)
 *	are passed, they are used in the probe requests.  For
 *	broadcast, a broadcast SSID must be passed (ie. an empty
 *	string).  If no SSID is passed, no probe requests are sent and
 *	a passive scan is perक्रमmed.  %NL80211_ATTR_SCAN_FREQUENCIES,
 *	अगर passed, define which channels should be scanned; अगर not
 *	passed, all channels allowed क्रम the current regulatory करोमुख्य
 *	are used.  Extra IEs can also be passed from the userspace by
 *	using the %NL80211_ATTR_IE attribute.  The first cycle of the
 *	scheduled scan can be delayed by %NL80211_ATTR_SCHED_SCAN_DELAY
 *	is supplied. If the device supports multiple concurrent scheduled
 *	scans, it will allow such when the caller provides the flag attribute
 *	%NL80211_ATTR_SCHED_SCAN_MULTI to indicate user-space support क्रम it.
 * @NL80211_CMD_STOP_SCHED_SCAN: stop a scheduled scan. Returns -ENOENT अगर
 *	scheduled scan is not running. The caller may assume that as soon
 *	as the call वापसs, it is safe to start a new scheduled scan again.
 * @NL80211_CMD_SCHED_SCAN_RESULTS: indicates that there are scheduled scan
 *	results available.
 * @NL80211_CMD_SCHED_SCAN_STOPPED: indicates that the scheduled scan has
 *	stopped.  The driver may issue this event at any समय during a
 *	scheduled scan.  One reason क्रम stopping the scan is अगर the hardware
 *	करोes not support starting an association or a normal scan जबतक running
 *	a scheduled scan.  This event is also sent when the
 *	%NL80211_CMD_STOP_SCHED_SCAN command is received or when the पूर्णांकerface
 *	is brought करोwn जबतक a scheduled scan was running.
 *
 * @NL80211_CMD_GET_SURVEY: get survey resuls, e.g. channel occupation
 *      or noise level
 * @NL80211_CMD_NEW_SURVEY_RESULTS: survey data notअगरication (as a reply to
 *	NL80211_CMD_GET_SURVEY and on the "scan" multicast group)
 *
 * @NL80211_CMD_SET_PMKSA: Add a PMKSA cache entry using %NL80211_ATTR_MAC
 *	(क्रम the BSSID), %NL80211_ATTR_PMKID, and optionally %NL80211_ATTR_PMK
 *	(PMK is used क्रम PTKSA derivation in हाल of FILS shared key offload) or
 *	using %NL80211_ATTR_SSID, %NL80211_ATTR_FILS_CACHE_ID,
 *	%NL80211_ATTR_PMKID, and %NL80211_ATTR_PMK in हाल of FILS
 *	authentication where %NL80211_ATTR_FILS_CACHE_ID is the identअगरier
 *	advertized by a FILS capable AP identअगरying the scope of PMKSA in an
 *	ESS.
 * @NL80211_CMD_DEL_PMKSA: Delete a PMKSA cache entry, using %NL80211_ATTR_MAC
 *	(क्रम the BSSID) and %NL80211_ATTR_PMKID or using %NL80211_ATTR_SSID,
 *	%NL80211_ATTR_FILS_CACHE_ID, and %NL80211_ATTR_PMKID in हाल of FILS
 *	authentication.
 * @NL80211_CMD_FLUSH_PMKSA: Flush all PMKSA cache entries.
 *
 * @NL80211_CMD_REG_CHANGE: indicates to userspace the regulatory करोमुख्य
 * 	has been changed and provides details of the request inक्रमmation
 * 	that caused the change such as who initiated the regulatory request
 * 	(%NL80211_ATTR_REG_INITIATOR), the wiphy_idx
 * 	(%NL80211_ATTR_REG_ALPHA2) on which the request was made from अगर
 * 	the initiator was %NL80211_REGDOM_SET_BY_COUNTRY_IE or
 * 	%NL80211_REGDOM_SET_BY_DRIVER, the type of regulatory करोमुख्य
 * 	set (%NL80211_ATTR_REG_TYPE), अगर the type of regulatory करोमुख्य is
 * 	%NL80211_REG_TYPE_COUNTRY the alpha2 to which we have moved on
 * 	to (%NL80211_ATTR_REG_ALPHA2).
 * @NL80211_CMD_REG_BEACON_HINT: indicates to userspace that an AP beacon
 * 	has been found जबतक world roaming thus enabling active scan or
 * 	any mode of operation that initiates TX (beacons) on a channel
 * 	where we would not have been able to करो either beक्रमe. As an example
 * 	अगर you are world roaming (regulatory करोमुख्य set to world or अगर your
 * 	driver is using a custom world roaming regulatory करोमुख्य) and जबतक
 * 	करोing a passive scan on the 5 GHz band you find an AP there (अगर not
 * 	on a DFS channel) you will now be able to actively scan क्रम that AP
 * 	or use AP mode on your card on that same channel. Note that this will
 * 	never be used क्रम channels 1-11 on the 2 GHz band as they are always
 * 	enabled world wide. This beacon hपूर्णांक is only sent अगर your device had
 * 	either disabled active scanning or beaconing on a channel. We send to
 * 	userspace the wiphy on which we हटाओd a restriction from
 * 	(%NL80211_ATTR_WIPHY) and the channel on which this occurred
 * 	beक्रमe (%NL80211_ATTR_FREQ_BEFORE) and after (%NL80211_ATTR_FREQ_AFTER)
 * 	the beacon hपूर्णांक was processed.
 *
 * @NL80211_CMD_AUTHENTICATE: authentication request and notअगरication.
 *	This command is used both as a command (request to authenticate) and
 *	as an event on the "mlme" multicast group indicating completion of the
 *	authentication process.
 *	When used as a command, %NL80211_ATTR_IFINDEX is used to identअगरy the
 *	पूर्णांकerface. %NL80211_ATTR_MAC is used to specअगरy PeerSTAAddress (and
 *	BSSID in हाल of station mode). %NL80211_ATTR_SSID is used to specअगरy
 *	the SSID (मुख्यly क्रम association, but is included in authentication
 *	request, too, to help BSS selection. %NL80211_ATTR_WIPHY_FREQ +
 *	%NL80211_ATTR_WIPHY_FREQ_OFFSET is used to specअगरy the frequence of the
 *	channel in MHz. %NL80211_ATTR_AUTH_TYPE is used to specअगरy the
 *	authentication type. %NL80211_ATTR_IE is used to define IEs
 *	(VenकरोrSpecअगरicInfo, but also including RSN IE and FT IEs) to be added
 *	to the frame.
 *	When used as an event, this reports reception of an Authentication
 *	frame in station and IBSS modes when the local MLME processed the
 *	frame, i.e., it was क्रम the local STA and was received in correct
 *	state. This is similar to MLME-AUTHENTICATE.confirm primitive in the
 *	MLME SAP पूर्णांकerface (kernel providing MLME, userspace SME). The
 *	included %NL80211_ATTR_FRAME attribute contains the management frame
 *	(including both the header and frame body, but not FCS). This event is
 *	also used to indicate अगर the authentication attempt समयd out. In that
 *	हाल the %NL80211_ATTR_FRAME attribute is replaced with a
 *	%NL80211_ATTR_TIMED_OUT flag (and %NL80211_ATTR_MAC to indicate which
 *	pending authentication समयd out).
 * @NL80211_CMD_ASSOCIATE: association request and notअगरication; like
 *	NL80211_CMD_AUTHENTICATE but क्रम Association and Reassociation
 *	(similar to MLME-ASSOCIATE.request, MLME-REASSOCIATE.request,
 *	MLME-ASSOCIATE.confirm or MLME-REASSOCIATE.confirm primitives). The
 *	%NL80211_ATTR_PREV_BSSID attribute is used to specअगरy whether the
 *	request is क्रम the initial association to an ESS (that attribute not
 *	included) or क्रम reassociation within the ESS (that attribute is
 *	included).
 * @NL80211_CMD_DEAUTHENTICATE: deauthentication request and notअगरication; like
 *	NL80211_CMD_AUTHENTICATE but क्रम Deauthentication frames (similar to
 *	MLME-DEAUTHENTICATION.request and MLME-DEAUTHENTICATE.indication
 *	primitives).
 * @NL80211_CMD_DISASSOCIATE: disassociation request and notअगरication; like
 *	NL80211_CMD_AUTHENTICATE but क्रम Disassociation frames (similar to
 *	MLME-DISASSOCIATE.request and MLME-DISASSOCIATE.indication primitives).
 *
 * @NL80211_CMD_MICHAEL_MIC_FAILURE: notअगरication of a locally detected Michael
 *	MIC (part of TKIP) failure; sent on the "mlme" multicast group; the
 *	event includes %NL80211_ATTR_MAC to describe the source MAC address of
 *	the frame with invalid MIC, %NL80211_ATTR_KEY_TYPE to show the key
 *	type, %NL80211_ATTR_KEY_IDX to indicate the key identअगरier, and
 *	%NL80211_ATTR_KEY_SEQ to indicate the TSC value of the frame; this
 *	event matches with MLME-MICHAELMICFAILURE.indication() primitive
 *
 * @NL80211_CMD_JOIN_IBSS: Join a new IBSS -- given at least an SSID and a
 *	FREQ attribute (क्रम the initial frequency अगर no peer can be found)
 *	and optionally a MAC (as BSSID) and FREQ_FIXED attribute अगर those
 *	should be fixed rather than स्वतःmatically determined. Can only be
 *	executed on a network पूर्णांकerface that is UP, and fixed BSSID/FREQ
 *	may be rejected. Another optional parameter is the beacon पूर्णांकerval,
 *	given in the %NL80211_ATTR_BEACON_INTERVAL attribute, which अगर not
 *	given शेषs to 100 TU (102.4ms).
 * @NL80211_CMD_LEAVE_IBSS: Leave the IBSS -- no special arguments, the IBSS is
 *	determined by the network पूर्णांकerface.
 *
 * @NL80211_CMD_TESTMODE: tesपंचांगode command, takes a wiphy (or अगरindex) attribute
 *	to identअगरy the device, and the TESTDATA blob attribute to pass through
 *	to the driver.
 *
 * @NL80211_CMD_CONNECT: connection request and notअगरication; this command
 *	requests to connect to a specअगरied network but without separating
 *	auth and assoc steps. For this, you need to specअगरy the SSID in a
 *	%NL80211_ATTR_SSID attribute, and can optionally specअगरy the association
 *	IEs in %NL80211_ATTR_IE, %NL80211_ATTR_AUTH_TYPE,
 *	%NL80211_ATTR_USE_MFP, %NL80211_ATTR_MAC, %NL80211_ATTR_WIPHY_FREQ,
 *	%NL80211_ATTR_WIPHY_FREQ_OFFSET, %NL80211_ATTR_CONTROL_PORT,
 *	%NL80211_ATTR_CONTROL_PORT_ETHERTYPE,
 *	%NL80211_ATTR_CONTROL_PORT_NO_ENCRYPT,
 *	%NL80211_ATTR_CONTROL_PORT_OVER_NL80211, %NL80211_ATTR_MAC_HINT, and
 *	%NL80211_ATTR_WIPHY_FREQ_HINT.
 *	If included, %NL80211_ATTR_MAC and %NL80211_ATTR_WIPHY_FREQ are
 *	restrictions on BSS selection, i.e., they effectively prevent roaming
 *	within the ESS. %NL80211_ATTR_MAC_HINT and %NL80211_ATTR_WIPHY_FREQ_HINT
 *	can be included to provide a recommendation of the initial BSS जबतक
 *	allowing the driver to roam to other BSSes within the ESS and also to
 *	ignore this recommendation अगर the indicated BSS is not ideal. Only one
 *	set of BSSID,frequency parameters is used (i.e., either the enक्रमcing
 *	%NL80211_ATTR_MAC,%NL80211_ATTR_WIPHY_FREQ or the less strict
 *	%NL80211_ATTR_MAC_HINT and %NL80211_ATTR_WIPHY_FREQ_HINT).
 *	Driver shall not modअगरy the IEs specअगरied through %NL80211_ATTR_IE अगर
 *	%NL80211_ATTR_MAC is included. However, अगर %NL80211_ATTR_MAC_HINT is
 *	included, these IEs through %NL80211_ATTR_IE are specअगरied by the user
 *	space based on the best possible BSS selected. Thus, अगर the driver ends
 *	up selecting a dअगरferent BSS, it can modअगरy these IEs accordingly (e.g.
 *	userspace asks the driver to perक्रमm PMKSA caching with BSS1 and the
 *	driver ends up selecting BSS2 with dअगरferent PMKSA cache entry; RSNIE
 *	has to get updated with the apt PMKID).
 *	%NL80211_ATTR_PREV_BSSID can be used to request a reassociation within
 *	the ESS in हाल the device is alपढ़ोy associated and an association with
 *	a dअगरferent BSS is desired.
 *	Background scan period can optionally be
 *	specअगरied in %NL80211_ATTR_BG_SCAN_PERIOD,
 *	अगर not specअगरied शेष background scan configuration
 *	in driver is used and अगर period value is 0, bg scan will be disabled.
 *	This attribute is ignored अगर driver करोes not support roam scan.
 *	It is also sent as an event, with the BSSID and response IEs when the
 *	connection is established or failed to be established. This can be
 *	determined by the %NL80211_ATTR_STATUS_CODE attribute (0 = success,
 *	non-zero = failure). If %NL80211_ATTR_TIMED_OUT is included in the
 *	event, the connection attempt failed due to not being able to initiate
 *	authentication/association or not receiving a response from the AP.
 *	Non-zero %NL80211_ATTR_STATUS_CODE value is indicated in that हाल as
 *	well to reमुख्य backwards compatible.
 * @NL80211_CMD_ROAM: Notअगरication indicating the card/driver roamed by itself.
 *	When a security association was established on an 802.1X network using
 *	fast transition, this event should be followed by an
 *	%NL80211_CMD_PORT_AUTHORIZED event.
 *	Following a %NL80211_CMD_ROAM event userspace can issue
 *	%NL80211_CMD_GET_SCAN in order to obtain the scan inक्रमmation क्रम the
 *	new BSS the card/driver roamed to.
 * @NL80211_CMD_DISCONNECT: drop a given connection; also used to notअगरy
 *	userspace that a connection was dropped by the AP or due to other
 *	reasons, क्रम this the %NL80211_ATTR_DISCONNECTED_BY_AP and
 *	%NL80211_ATTR_REASON_CODE attributes are used.
 *
 * @NL80211_CMD_SET_WIPHY_NETNS: Set a wiphy's netns. Note that all devices
 *	associated with this wiphy must be करोwn and will follow.
 *
 * @NL80211_CMD_REMAIN_ON_CHANNEL: Request to reमुख्य awake on the specअगरied
 *	channel क्रम the specअगरied amount of समय. This can be used to करो
 *	off-channel operations like transmit a Public Action frame and रुको क्रम
 *	a response जबतक being associated to an AP on another channel.
 *	%NL80211_ATTR_IFINDEX is used to specअगरy which पूर्णांकerface (and thus
 *	radio) is used. %NL80211_ATTR_WIPHY_FREQ is used to specअगरy the
 *	frequency क्रम the operation.
 *	%NL80211_ATTR_DURATION is used to specअगरy the duration in milliseconds
 *	to reमुख्य on the channel. This command is also used as an event to
 *	notअगरy when the requested duration starts (it may take a जबतक क्रम the
 *	driver to schedule this समय due to other concurrent needs क्रम the
 *	radio).
 *	When called, this operation वापसs a cookie (%NL80211_ATTR_COOKIE)
 *	that will be included with any events pertaining to this request;
 *	the cookie is also used to cancel the request.
 * @NL80211_CMD_CANCEL_REMAIN_ON_CHANNEL: This command can be used to cancel a
 *	pending reमुख्य-on-channel duration अगर the desired operation has been
 *	completed prior to expiration of the originally requested duration.
 *	%NL80211_ATTR_WIPHY or %NL80211_ATTR_IFINDEX is used to specअगरy the
 *	radio. The %NL80211_ATTR_COOKIE attribute must be given as well to
 *	uniquely identअगरy the request.
 *	This command is also used as an event to notअगरy when a requested
 *	reमुख्य-on-channel duration has expired.
 *
 * @NL80211_CMD_SET_TX_BITRATE_MASK: Set the mask of rates to be used in TX
 *	rate selection. %NL80211_ATTR_IFINDEX is used to specअगरy the पूर्णांकerface
 *	and @NL80211_ATTR_TX_RATES the set of allowed rates.
 *
 * @NL80211_CMD_REGISTER_FRAME: Register क्रम receiving certain mgmt frames
 *	(via @NL80211_CMD_FRAME) क्रम processing in userspace. This command
 *	requires an पूर्णांकerface index, a frame type attribute (optional क्रम
 *	backward compatibility reasons, अगर not given assumes action frames)
 *	and a match attribute containing the first few bytes of the frame
 *	that should match, e.g. a single byte क्रम only a category match or
 *	four bytes क्रम venकरोr frames including the OUI. The registration
 *	cannot be dropped, but is हटाओd स्वतःmatically when the netlink
 *	socket is बंदd. Multiple registrations can be made.
 *	The %NL80211_ATTR_RECEIVE_MULTICAST flag attribute can be given अगर
 *	%NL80211_EXT_FEATURE_MULTICAST_REGISTRATIONS is available, in which
 *	हाल the registration can also be modअगरied to include/exclude the
 *	flag, rather than requiring unregistration to change it.
 * @NL80211_CMD_REGISTER_ACTION: Alias क्रम @NL80211_CMD_REGISTER_FRAME क्रम
 *	backward compatibility
 * @NL80211_CMD_FRAME: Management frame TX request and RX notअगरication. This
 *	command is used both as a request to transmit a management frame and
 *	as an event indicating reception of a frame that was not processed in
 *	kernel code, but is क्रम us (i.e., which may need to be processed in a
 *	user space application). %NL80211_ATTR_FRAME is used to specअगरy the
 *	frame contents (including header). %NL80211_ATTR_WIPHY_FREQ is used
 *	to indicate on which channel the frame is to be transmitted or was
 *	received. If this channel is not the current channel (reमुख्य-on-channel
 *	or the operational channel) the device will चयन to the given channel
 *	and transmit the frame, optionally रुकोing क्रम a response क्रम the समय
 *	specअगरied using %NL80211_ATTR_DURATION. When called, this operation
 *	वापसs a cookie (%NL80211_ATTR_COOKIE) that will be included with the
 *	TX status event pertaining to the TX request.
 *	%NL80211_ATTR_TX_NO_CCK_RATE is used to decide whether to send the
 *	management frames at CCK rate or not in 2GHz band.
 *	%NL80211_ATTR_CSA_C_OFFSETS_TX is an array of offsets to CSA
 *	counters which will be updated to the current value. This attribute
 *	is used during CSA period.
 * @NL80211_CMD_FRAME_WAIT_CANCEL: When an off-channel TX was requested, this
 *	command may be used with the corresponding cookie to cancel the रुको
 *	समय अगर it is known that it is no दीर्घer necessary.  This command is
 *	also sent as an event whenever the driver has completed the off-channel
 *	रुको समय.
 * @NL80211_CMD_ACTION: Alias क्रम @NL80211_CMD_FRAME क्रम backward compatibility.
 * @NL80211_CMD_FRAME_TX_STATUS: Report TX status of a management frame
 *	transmitted with %NL80211_CMD_FRAME. %NL80211_ATTR_COOKIE identअगरies
 *	the TX command and %NL80211_ATTR_FRAME includes the contents of the
 *	frame. %NL80211_ATTR_ACK flag is included अगर the recipient acknowledged
 *	the frame.
 * @NL80211_CMD_ACTION_TX_STATUS: Alias क्रम @NL80211_CMD_FRAME_TX_STATUS क्रम
 *	backward compatibility.
 *
 * @NL80211_CMD_SET_POWER_SAVE: Set घातersave, using %NL80211_ATTR_PS_STATE
 * @NL80211_CMD_GET_POWER_SAVE: Get घातersave status in %NL80211_ATTR_PS_STATE
 *
 * @NL80211_CMD_SET_CQM: Connection quality monitor configuration. This command
 *	is used to configure connection quality monitoring notअगरication trigger
 *	levels.
 * @NL80211_CMD_NOTIFY_CQM: Connection quality monitor notअगरication. This
 *	command is used as an event to indicate the that a trigger level was
 *	reached.
 * @NL80211_CMD_SET_CHANNEL: Set the channel (using %NL80211_ATTR_WIPHY_FREQ
 *	and the attributes determining channel width) the given पूर्णांकerface
 *	(identअगरed by %NL80211_ATTR_IFINDEX) shall operate on.
 *	In हाल multiple channels are supported by the device, the mechanism
 *	with which it चयनes channels is implementation-defined.
 *	When a monitor पूर्णांकerface is given, it can only चयन channel जबतक
 *	no other पूर्णांकerfaces are operating to aव्योम disturbing the operation
 *	of any other पूर्णांकerfaces, and other पूर्णांकerfaces will again take
 *	precedence when they are used.
 *
 * @NL80211_CMD_SET_WDS_PEER: Set the MAC address of the peer on a WDS पूर्णांकerface
 *	(no दीर्घer supported).
 *
 * @NL80211_CMD_SET_MULTICAST_TO_UNICAST: Configure अगर this AP should perक्रमm
 *	multicast to unicast conversion. When enabled, all multicast packets
 *	with ethertype ARP, IPv4 or IPv6 (possibly within an 802.1Q header)
 *	will be sent out to each station once with the destination (multicast)
 *	MAC address replaced by the station's MAC address. Note that this may
 *	अवरोध certain expectations of the receiver, e.g. the ability to drop
 *	unicast IP packets encapsulated in multicast L2 frames, or the ability
 *	to not send destination unreachable messages in such हालs.
 *	This can only be toggled per BSS. Configure this on an पूर्णांकerface of
 *	type %NL80211_IFTYPE_AP. It applies to all its VLAN पूर्णांकerfaces
 *	(%NL80211_IFTYPE_AP_VLAN), except क्रम those in 4addr (WDS) mode.
 *	If %NL80211_ATTR_MULTICAST_TO_UNICAST_ENABLED is not present with this
 *	command, the feature is disabled.
 *
 * @NL80211_CMD_JOIN_MESH: Join a mesh. The mesh ID must be given, and initial
 *	mesh config parameters may be given.
 * @NL80211_CMD_LEAVE_MESH: Leave the mesh network -- no special arguments, the
 *	network is determined by the network पूर्णांकerface.
 *
 * @NL80211_CMD_UNPROT_DEAUTHENTICATE: Unरक्षित deauthentication frame
 *	notअगरication. This event is used to indicate that an unरक्षित
 *	deauthentication frame was dropped when MFP is in use.
 * @NL80211_CMD_UNPROT_DISASSOCIATE: Unरक्षित disassociation frame
 *	notअगरication. This event is used to indicate that an unरक्षित
 *	disassociation frame was dropped when MFP is in use.
 *
 * @NL80211_CMD_NEW_PEER_CANDIDATE: Notअगरication on the reception of a
 *      beacon or probe response from a compatible mesh peer.  This is only
 *      sent जबतक no station inक्रमmation (sta_info) exists क्रम the new peer
 *      candidate and when @NL80211_MESH_SETUP_USERSPACE_AUTH,
 *      @NL80211_MESH_SETUP_USERSPACE_AMPE, or
 *      @NL80211_MESH_SETUP_USERSPACE_MPM is set.  On reception of this
 *      notअगरication, userspace may decide to create a new station
 *      (@NL80211_CMD_NEW_STATION).  To stop this notअगरication from
 *      reoccurring, the userspace authentication daemon may want to create the
 *      new station with the AUTHENTICATED flag unset and maybe change it later
 *      depending on the authentication result.
 *
 * @NL80211_CMD_GET_WOWLAN: get Wake-on-Wireless-LAN (WoWLAN) settings.
 * @NL80211_CMD_SET_WOWLAN: set Wake-on-Wireless-LAN (WoWLAN) settings.
 *	Since wireless is more complex than wired ethernet, it supports
 *	various triggers. These triggers can be configured through this
 *	command with the %NL80211_ATTR_WOWLAN_TRIGGERS attribute. For
 *	more background inक्रमmation, see
 *	https://wireless.wiki.kernel.org/en/users/Documentation/WoWLAN.
 *	The @NL80211_CMD_SET_WOWLAN command can also be used as a notअगरication
 *	from the driver reporting the wakeup reason. In this हाल, the
 *	@NL80211_ATTR_WOWLAN_TRIGGERS attribute will contain the reason
 *	क्रम the wakeup, अगर it was caused by wireless. If it is not present
 *	in the wakeup notअगरication, the wireless device didn't cause the
 *	wakeup but reports that it was woken up.
 *
 * @NL80211_CMD_SET_REKEY_OFFLOAD: This command is used give the driver
 *	the necessary inक्रमmation क्रम supporting GTK rekey offload. This
 *	feature is typically used during WoWLAN. The configuration data
 *	is contained in %NL80211_ATTR_REKEY_DATA (which is nested and
 *	contains the data in sub-attributes). After rekeying happened,
 *	this command may also be sent by the driver as an MLME event to
 *	inक्रमm userspace of the new replay counter.
 *
 * @NL80211_CMD_PMKSA_CANDIDATE: This is used as an event to inक्रमm userspace
 *	of PMKSA caching dandidates.
 *
 * @NL80211_CMD_TDLS_OPER: Perक्रमm a high-level TDLS command (e.g. link setup).
 *	In addition, this can be used as an event to request userspace to take
 *	actions on TDLS links (set up a new link or tear करोwn an existing one).
 *	In such events, %NL80211_ATTR_TDLS_OPERATION indicates the requested
 *	operation, %NL80211_ATTR_MAC contains the peer MAC address, and
 *	%NL80211_ATTR_REASON_CODE the reason code to be used (only with
 *	%NL80211_TDLS_TEARDOWN).
 * @NL80211_CMD_TDLS_MGMT: Send a TDLS management frame. The
 *	%NL80211_ATTR_TDLS_ACTION attribute determines the type of frame to be
 *	sent. Public Action codes (802.11-2012 8.1.5.1) will be sent as
 *	802.11 management frames, जबतक TDLS action codes (802.11-2012
 *	8.5.13.1) will be encapsulated and sent as data frames. The currently
 *	supported Public Action code is %WLAN_PUB_ACTION_TDLS_DISCOVER_RES
 *	and the currently supported TDLS actions codes are given in
 *	&क्रमागत ieee80211_tdls_actioncode.
 *
 * @NL80211_CMD_UNEXPECTED_FRAME: Used by an application controlling an AP
 *	(or GO) पूर्णांकerface (i.e. hostapd) to ask क्रम unexpected frames to
 *	implement sending deauth to stations that send unexpected class 3
 *	frames. Also used as the event sent by the kernel when such a frame
 *	is received.
 *	For the event, the %NL80211_ATTR_MAC attribute carries the TA and
 *	other attributes like the पूर्णांकerface index are present.
 *	If used as the command it must have an पूर्णांकerface index and you can
 *	only unsubscribe from the event by closing the socket. Subscription
 *	is also क्रम %NL80211_CMD_UNEXPECTED_4ADDR_FRAME events.
 *
 * @NL80211_CMD_UNEXPECTED_4ADDR_FRAME: Sent as an event indicating that the
 *	associated station identअगरied by %NL80211_ATTR_MAC sent a 4addr frame
 *	and wasn't alपढ़ोy in a 4-addr VLAN. The event will be sent similarly
 *	to the %NL80211_CMD_UNEXPECTED_FRAME event, to the same listener.
 *
 * @NL80211_CMD_PROBE_CLIENT: Probe an associated station on an AP पूर्णांकerface
 *	by sending a null data frame to it and reporting when the frame is
 *	acknowleged. This is used to allow timing out inactive clients. Uses
 *	%NL80211_ATTR_IFINDEX and %NL80211_ATTR_MAC. The command वापसs a
 *	direct reply with an %NL80211_ATTR_COOKIE that is later used to match
 *	up the event with the request. The event includes the same data and
 *	has %NL80211_ATTR_ACK set अगर the frame was ACKed.
 *
 * @NL80211_CMD_REGISTER_BEACONS: Register this socket to receive beacons from
 *	other BSSes when any पूर्णांकerfaces are in AP mode. This helps implement
 *	OLBC handling in hostapd. Beacons are reported in %NL80211_CMD_FRAME
 *	messages. Note that per PHY only one application may रेजिस्टर.
 *
 * @NL80211_CMD_SET_NOACK_MAP: sets a biपंचांगap क्रम the inभागidual TIDs whether
 *      No Acknowledgement Policy should be applied.
 *
 * @NL80211_CMD_CH_SWITCH_NOTIFY: An AP or GO may decide to चयन channels
 *	independently of the userspace SME, send this event indicating
 *	%NL80211_ATTR_IFINDEX is now on %NL80211_ATTR_WIPHY_FREQ and the
 *	attributes determining channel width.  This indication may also be
 *	sent when a remotely-initiated चयन (e.g., when a STA receives a CSA
 *	from the remote AP) is completed;
 *
 * @NL80211_CMD_CH_SWITCH_STARTED_NOTIFY: Notअगरy that a channel चयन
 *	has been started on an पूर्णांकerface, regardless of the initiator
 *	(ie. whether it was requested from a remote device or
 *	initiated on our own).  It indicates that
 *	%NL80211_ATTR_IFINDEX will be on %NL80211_ATTR_WIPHY_FREQ
 *	after %NL80211_ATTR_CH_SWITCH_COUNT TBTT's.  The userspace may
 *	decide to react to this indication by requesting other
 *	पूर्णांकerfaces to change channel as well.
 *
 * @NL80211_CMD_START_P2P_DEVICE: Start the given P2P Device, identअगरied by
 *	its %NL80211_ATTR_WDEV identअगरier. It must have been created with
 *	%NL80211_CMD_NEW_INTERFACE previously. After it has been started, the
 *	P2P Device can be used क्रम P2P operations, e.g. reमुख्य-on-channel and
 *	खुला action frame TX.
 * @NL80211_CMD_STOP_P2P_DEVICE: Stop the given P2P Device, identअगरied by
 *	its %NL80211_ATTR_WDEV identअगरier.
 *
 * @NL80211_CMD_CONN_FAILED: connection request to an AP failed; used to
 *	notअगरy userspace that AP has rejected the connection request from a
 *	station, due to particular reason. %NL80211_ATTR_CONN_FAILED_REASON
 *	is used क्रम this.
 *
 * @NL80211_CMD_SET_MCAST_RATE: Change the rate used to send multicast frames
 *	क्रम IBSS or MESH vअगर.
 *
 * @NL80211_CMD_SET_MAC_ACL: sets ACL क्रम MAC address based access control.
 *	This is to be used with the drivers advertising the support of MAC
 *	address based access control. List of MAC addresses is passed in
 *	%NL80211_ATTR_MAC_ADDRS and ACL policy is passed in
 *	%NL80211_ATTR_ACL_POLICY. Driver will enable ACL with this list, अगर it
 *	is not alपढ़ोy करोne. The new list will replace any existing list. Driver
 *	will clear its ACL when the list of MAC addresses passed is empty. This
 *	command is used in AP/P2P GO mode. Driver has to make sure to clear its
 *	ACL list during %NL80211_CMD_STOP_AP.
 *
 * @NL80211_CMD_RADAR_DETECT: Start a Channel availability check (CAC). Once
 *	a radar is detected or the channel availability scan (CAC) has finished
 *	or was पातed, or a radar was detected, usermode will be notअगरied with
 *	this event. This command is also used to notअगरy userspace about radars
 *	जबतक operating on this channel.
 *	%NL80211_ATTR_RADAR_EVENT is used to inक्रमm about the type of the
 *	event.
 *
 * @NL80211_CMD_GET_PROTOCOL_FEATURES: Get global nl80211 protocol features,
 *	i.e. features क्रम the nl80211 protocol rather than device features.
 *	Returns the features in the %NL80211_ATTR_PROTOCOL_FEATURES biपंचांगap.
 *
 * @NL80211_CMD_UPDATE_FT_IES: Pass करोwn the most up-to-date Fast Transition
 *	Inक्रमmation Element to the WLAN driver
 *
 * @NL80211_CMD_FT_EVENT: Send a Fast transition event from the WLAN driver
 *	to the supplicant. This will carry the target AP's MAC address aदीर्घ
 *	with the relevant Inक्रमmation Elements. This event is used to report
 *	received FT IEs (MDIE, FTIE, RSN IE, TIE, RICIE).
 *
 * @NL80211_CMD_CRIT_PROTOCOL_START: Indicates user-space will start running
 *	a critical protocol that needs more reliability in the connection to
 *	complete.
 *
 * @NL80211_CMD_CRIT_PROTOCOL_STOP: Indicates the connection reliability can
 *	वापस back to normal.
 *
 * @NL80211_CMD_GET_COALESCE: Get currently supported coalesce rules.
 * @NL80211_CMD_SET_COALESCE: Configure coalesce rules or clear existing rules.
 *
 * @NL80211_CMD_CHANNEL_SWITCH: Perक्रमm a channel चयन by announcing the
 *	new channel inक्रमmation (Channel Switch Announcement - CSA)
 *	in the beacon क्रम some समय (as defined in the
 *	%NL80211_ATTR_CH_SWITCH_COUNT parameter) and then change to the
 *	new channel. Userspace provides the new channel inक्रमmation (using
 *	%NL80211_ATTR_WIPHY_FREQ and the attributes determining channel
 *	width). %NL80211_ATTR_CH_SWITCH_BLOCK_TX may be supplied to inक्रमm
 *	other station that transmission must be blocked until the channel
 *	चयन is complete.
 *
 * @NL80211_CMD_VENDOR: Venकरोr-specअगरied command/event. The command is specअगरied
 *	by the %NL80211_ATTR_VENDOR_ID attribute and a sub-command in
 *	%NL80211_ATTR_VENDOR_SUBCMD. Parameter(s) can be transported in
 *	%NL80211_ATTR_VENDOR_DATA.
 *	For feature advertisement, the %NL80211_ATTR_VENDOR_DATA attribute is
 *	used in the wiphy data as a nested attribute containing descriptions
 *	(&काष्ठा nl80211_venकरोr_cmd_info) of the supported venकरोr commands.
 *	This may also be sent as an event with the same attributes.
 *
 * @NL80211_CMD_SET_QOS_MAP: Set Interworking QoS mapping क्रम IP DSCP values.
 *	The QoS mapping inक्रमmation is included in %NL80211_ATTR_QOS_MAP. If
 *	that attribute is not included, QoS mapping is disabled. Since this
 *	QoS mapping is relevant क्रम IP packets, it is only valid during an
 *	association. This is cleared on disassociation and AP restart.
 *
 * @NL80211_CMD_ADD_TX_TS: Ask the kernel to add a traffic stream क्रम the given
 *	%NL80211_ATTR_TSID and %NL80211_ATTR_MAC with %NL80211_ATTR_USER_PRIO
 *	and %NL80211_ATTR_ADMITTED_TIME parameters.
 *	Note that the action frame handshake with the AP shall be handled by
 *	userspace via the normal management RX/TX framework, this only sets
 *	up the TX TS in the driver/device.
 *	If the admitted समय attribute is not added then the request just checks
 *	अगर a subsequent setup could be successful, the पूर्णांकent is to use this to
 *	aव्योम setting up a session with the AP when local restrictions would
 *	make that impossible. However, the subsequent "real" setup may still
 *	fail even अगर the check was successful.
 * @NL80211_CMD_DEL_TX_TS: Remove an existing TS with the %NL80211_ATTR_TSID
 *	and %NL80211_ATTR_MAC parameters. It isn't necessary to call this
 *	beक्रमe removing a station entry entirely, or beक्रमe disassociating
 *	or similar, cleanup will happen in the driver/device in this हाल.
 *
 * @NL80211_CMD_GET_MPP: Get mesh path attributes क्रम mesh proxy path to
 *	destination %NL80211_ATTR_MAC on the पूर्णांकerface identअगरied by
 *	%NL80211_ATTR_IFINDEX.
 *
 * @NL80211_CMD_JOIN_OCB: Join the OCB network. The center frequency and
 *	bandwidth of a channel must be given.
 * @NL80211_CMD_LEAVE_OCB: Leave the OCB network -- no special arguments, the
 *	network is determined by the network पूर्णांकerface.
 *
 * @NL80211_CMD_TDLS_CHANNEL_SWITCH: Start channel-चयनing with a TDLS peer,
 *	identअगरied by the %NL80211_ATTR_MAC parameter. A target channel is
 *	provided via %NL80211_ATTR_WIPHY_FREQ and other attributes determining
 *	channel width/type. The target operating class is given via
 *	%NL80211_ATTR_OPER_CLASS.
 *	The driver is responsible क्रम continually initiating channel-चयनing
 *	operations and वापसing to the base channel क्रम communication with the
 *	AP.
 * @NL80211_CMD_TDLS_CANCEL_CHANNEL_SWITCH: Stop channel-चयनing with a TDLS
 *	peer given by %NL80211_ATTR_MAC. Both peers must be on the base channel
 *	when this command completes.
 *
 * @NL80211_CMD_WIPHY_REG_CHANGE: Similar to %NL80211_CMD_REG_CHANGE, but used
 *	as an event to indicate changes क्रम devices with wiphy-specअगरic regकरोm
 *	management.
 *
 * @NL80211_CMD_ABORT_SCAN: Stop an ongoing scan. Returns -ENOENT अगर a scan is
 *	not running. The driver indicates the status of the scan through
 *	cfg80211_scan_करोne().
 *
 * @NL80211_CMD_START_न_अंक: Start न_अंक operation, identअगरied by its
 *	%NL80211_ATTR_WDEV पूर्णांकerface. This पूर्णांकerface must have been
 *	previously created with %NL80211_CMD_NEW_INTERFACE. After it
 *	has been started, the न_अंक पूर्णांकerface will create or join a
 *	cluster. This command must have a valid
 *	%NL80211_ATTR_न_अंक_MASTER_PREF attribute and optional
 *	%NL80211_ATTR_BANDS attributes.  If %NL80211_ATTR_BANDS is
 *	omitted or set to 0, it means करोn't-care and the device will
 *	decide what to use.  After this command न_अंक functions can be
 *	added.
 * @NL80211_CMD_STOP_न_अंक: Stop the न_अंक operation, identअगरied by
 *	its %NL80211_ATTR_WDEV पूर्णांकerface.
 * @NL80211_CMD_ADD_न_अंक_FUNCTION: Add a न_अंक function. The function is defined
 *	with %NL80211_ATTR_न_अंक_FUNC nested attribute. When called, this
 *	operation वापसs the strictly positive and unique instance id
 *	(%NL80211_ATTR_न_अंक_FUNC_INST_ID) and a cookie (%NL80211_ATTR_COOKIE)
 *	of the function upon success.
 *	Since instance ID's can be re-used, this cookie is the right
 *	way to identअगरy the function. This will aव्योम races when a termination
 *	event is handled by the user space after it has alपढ़ोy added a new
 *	function that got the same instance id from the kernel as the one
 *	which just terminated.
 *	This cookie may be used in न_अंक events even beक्रमe the command
 *	वापसs, so userspace shouldn't process न_अंक events until it processes
 *	the response to this command.
 *	Look at %NL80211_ATTR_SOCKET_OWNER as well.
 * @NL80211_CMD_DEL_न_अंक_FUNCTION: Delete a न_अंक function by cookie.
 *	This command is also used as a notअगरication sent when a न_अंक function is
 *	terminated. This will contain a %NL80211_ATTR_न_अंक_FUNC_INST_ID
 *	and %NL80211_ATTR_COOKIE attributes.
 * @NL80211_CMD_CHANGE_न_अंक_CONFIG: Change current न_अंक
 *	configuration. न_अंक must be operational (%NL80211_CMD_START_न_अंक
 *	was executed).  It must contain at least one of the following
 *	attributes: %NL80211_ATTR_न_अंक_MASTER_PREF,
 *	%NL80211_ATTR_BANDS.  If %NL80211_ATTR_BANDS is omitted, the
 *	current configuration is not changed.  If it is present but
 *	set to zero, the configuration is changed to करोn't-care
 *	(i.e. the device can decide what to करो).
 * @NL80211_CMD_न_अंक_FUNC_MATCH: Notअगरication sent when a match is reported.
 *	This will contain a %NL80211_ATTR_न_अंक_MATCH nested attribute and
 *	%NL80211_ATTR_COOKIE.
 *
 * @NL80211_CMD_UPDATE_CONNECT_PARAMS: Update one or more connect parameters
 *	क्रम subsequent roaming हालs अगर the driver or firmware uses पूर्णांकernal
 *	BSS selection. This command can be issued only जबतक connected and it
 *	करोes not result in a change क्रम the current association. Currently,
 *	only the %NL80211_ATTR_IE data is used and updated with this command.
 *
 * @NL80211_CMD_SET_PMK: For offloaded 4-Way handshake, set the PMK or PMK-R0
 *	क्रम the given authenticator address (specअगरied with %NL80211_ATTR_MAC).
 *	When %NL80211_ATTR_PMKR0_NAME is set, %NL80211_ATTR_PMK specअगरies the
 *	PMK-R0, otherwise it specअगरies the PMK.
 * @NL80211_CMD_DEL_PMK: For offloaded 4-Way handshake, delete the previously
 *	configured PMK क्रम the authenticator address identअगरied by
 *	%NL80211_ATTR_MAC.
 * @NL80211_CMD_PORT_AUTHORIZED: An event that indicates an 802.1X FT roam was
 *	completed successfully. Drivers that support 4 way handshake offload
 *	should send this event after indicating 802.1X FT assocation with
 *	%NL80211_CMD_ROAM. If the 4 way handshake failed %NL80211_CMD_DISCONNECT
 *	should be indicated instead.
 * @NL80211_CMD_CONTROL_PORT_FRAME: Control Port (e.g. PAE) frame TX request
 *	and RX notअगरication.  This command is used both as a request to transmit
 *	a control port frame and as a notअगरication that a control port frame
 *	has been received. %NL80211_ATTR_FRAME is used to specअगरy the
 *	frame contents.  The frame is the raw EAPoL data, without ethernet or
 *	802.11 headers.
 *	When used as an event indication %NL80211_ATTR_CONTROL_PORT_ETHERTYPE,
 *	%NL80211_ATTR_CONTROL_PORT_NO_ENCRYPT and %NL80211_ATTR_MAC are added
 *	indicating the protocol type of the received frame; whether the frame
 *	was received unencrypted and the MAC address of the peer respectively.
 *
 * @NL80211_CMD_RELOAD_REGDB: Request that the regdb firmware file is reloaded.
 *
 * @NL80211_CMD_EXTERNAL_AUTH: This पूर्णांकerface is exclusively defined क्रम host
 *	drivers that करो not define separate commands क्रम authentication and
 *	association, but rely on user space क्रम the authentication to happen.
 *	This पूर्णांकerface acts both as the event request (driver to user space)
 *	to trigger the authentication and command response (userspace to
 *	driver) to indicate the authentication status.
 *
 *	User space uses the %NL80211_CMD_CONNECT command to the host driver to
 *	trigger a connection. The host driver selects a BSS and further uses
 *	this पूर्णांकerface to offload only the authentication part to the user
 *	space. Authentication frames are passed between the driver and user
 *	space through the %NL80211_CMD_FRAME पूर्णांकerface. Host driver proceeds
 *	further with the association after getting successful authentication
 *	status. User space indicates the authentication status through
 *	%NL80211_ATTR_STATUS_CODE attribute in %NL80211_CMD_EXTERNAL_AUTH
 *	command पूर्णांकerface.
 *
 *	Host driver reports this status on an authentication failure to the
 *	user space through the connect result as the user space would have
 *	initiated the connection through the connect request.
 *
 * @NL80211_CMD_STA_OPMODE_CHANGED: An event that notअगरy station's
 *	ht opmode or vht opmode changes using any of %NL80211_ATTR_SMPS_MODE,
 *	%NL80211_ATTR_CHANNEL_WIDTH,%NL80211_ATTR_NSS attributes with its
 *	address(specअगरied in %NL80211_ATTR_MAC).
 *
 * @NL80211_CMD_GET_FTM_RESPONDER_STATS: Retrieve FTM responder statistics, in
 *	the %NL80211_ATTR_FTM_RESPONDER_STATS attribute.
 *
 * @NL80211_CMD_PEER_MEASUREMENT_START: start a (set of) peer measurement(s)
 *	with the given parameters, which are encapsulated in the nested
 *	%NL80211_ATTR_PEER_MEASUREMENTS attribute. Optionally, MAC address
 *	अक्रमomization may be enabled and configured by specअगरying the
 *	%NL80211_ATTR_MAC and %NL80211_ATTR_MAC_MASK attributes.
 *	If a समयout is requested, use the %NL80211_ATTR_TIMEOUT attribute.
 *	A u64 cookie क्रम further %NL80211_ATTR_COOKIE use is वापसed in
 *	the netlink extended ack message.
 *
 *	To cancel a measurement, बंद the socket that requested it.
 *
 *	Measurement results are reported to the socket that requested the
 *	measurement using @NL80211_CMD_PEER_MEASUREMENT_RESULT when they
 *	become available, so applications must ensure a large enough socket
 *	buffer size.
 *
 *	Depending on driver support it may or may not be possible to start
 *	multiple concurrent measurements.
 * @NL80211_CMD_PEER_MEASUREMENT_RESULT: This command number is used क्रम the
 *	result notअगरication from the driver to the requesting socket.
 * @NL80211_CMD_PEER_MEASUREMENT_COMPLETE: Notअगरication only, indicating that
 *	the measurement completed, using the measurement cookie
 *	(%NL80211_ATTR_COOKIE).
 *
 * @NL80211_CMD_NOTIFY_RADAR: Notअगरy the kernel that a radar संकेत was
 *	detected and reported by a neighboring device on the channel
 *	indicated by %NL80211_ATTR_WIPHY_FREQ and other attributes
 *	determining the width and type.
 *
 * @NL80211_CMD_UPDATE_OWE_INFO: This पूर्णांकerface allows the host driver to
 *	offload OWE processing to user space. This पूर्णांकends to support
 *	OWE AKM by the host drivers that implement SME but rely
 *	on the user space क्रम the cryptographic/DH IE processing in AP mode.
 *
 * @NL80211_CMD_PROBE_MESH_LINK: The requirement क्रम mesh link metric
 *	refreshing, is that from one mesh poपूर्णांक we be able to send some data
 *	frames to other mesh poपूर्णांकs which are not currently selected as a
 *	primary traffic path, but which are only 1 hop away. The असलence of
 *	the primary path to the chosen node makes it necessary to apply some
 *	क्रमm of marking on a chosen packet stream so that the packets can be
 *	properly steered to the selected node क्रम testing, and not by the
 *	regular mesh path lookup. Further, the packets must be of type data
 *	so that the rate control (often embedded in firmware) is used क्रम
 *	rate selection.
 *
 *	Here attribute %NL80211_ATTR_MAC is used to specअगरy connected mesh
 *	peer MAC address and %NL80211_ATTR_FRAME is used to specअगरy the frame
 *	content. The frame is ethernet data.
 *
 * @NL80211_CMD_SET_TID_CONFIG: Data frame TID specअगरic configuration
 *	is passed using %NL80211_ATTR_TID_CONFIG attribute.
 *
 * @NL80211_CMD_UNPROT_BEACON: Unरक्षित or incorrectly रक्षित Beacon
 *	frame. This event is used to indicate that a received Beacon frame was
 *	dropped because it did not include a valid MME MIC जबतक beacon
 *	protection was enabled (BIGTK configured in station mode).
 *
 * @NL80211_CMD_CONTROL_PORT_FRAME_TX_STATUS: Report TX status of a control
 *	port frame transmitted with %NL80211_CMD_CONTROL_PORT_FRAME.
 *	%NL80211_ATTR_COOKIE identअगरies the TX command and %NL80211_ATTR_FRAME
 *	includes the contents of the frame. %NL80211_ATTR_ACK flag is included
 *	अगर the recipient acknowledged the frame.
 *
 * @NL80211_CMD_SET_SAR_SPECS: SAR घातer limitation configuration is
 *	passed using %NL80211_ATTR_SAR_SPEC. %NL80211_ATTR_WIPHY is used to
 *	specअगरy the wiphy index to be applied to.
 *
 * @NL80211_CMD_MAX: highest used command number
 * @__NL80211_CMD_AFTER_LAST: पूर्णांकernal use
 */
क्रमागत nl80211_commands अणु
/* करोn't change the order or add anything between, this is ABI! */
	NL80211_CMD_UNSPEC,

	NL80211_CMD_GET_WIPHY,		/* can dump */
	NL80211_CMD_SET_WIPHY,
	NL80211_CMD_NEW_WIPHY,
	NL80211_CMD_DEL_WIPHY,

	NL80211_CMD_GET_INTERFACE,	/* can dump */
	NL80211_CMD_SET_INTERFACE,
	NL80211_CMD_NEW_INTERFACE,
	NL80211_CMD_DEL_INTERFACE,

	NL80211_CMD_GET_KEY,
	NL80211_CMD_SET_KEY,
	NL80211_CMD_NEW_KEY,
	NL80211_CMD_DEL_KEY,

	NL80211_CMD_GET_BEACON,
	NL80211_CMD_SET_BEACON,
	NL80211_CMD_START_AP,
	NL80211_CMD_NEW_BEACON = NL80211_CMD_START_AP,
	NL80211_CMD_STOP_AP,
	NL80211_CMD_DEL_BEACON = NL80211_CMD_STOP_AP,

	NL80211_CMD_GET_STATION,
	NL80211_CMD_SET_STATION,
	NL80211_CMD_NEW_STATION,
	NL80211_CMD_DEL_STATION,

	NL80211_CMD_GET_MPATH,
	NL80211_CMD_SET_MPATH,
	NL80211_CMD_NEW_MPATH,
	NL80211_CMD_DEL_MPATH,

	NL80211_CMD_SET_BSS,

	NL80211_CMD_SET_REG,
	NL80211_CMD_REQ_SET_REG,

	NL80211_CMD_GET_MESH_CONFIG,
	NL80211_CMD_SET_MESH_CONFIG,

	NL80211_CMD_SET_MGMT_EXTRA_IE /* reserved; not used */,

	NL80211_CMD_GET_REG,

	NL80211_CMD_GET_SCAN,
	NL80211_CMD_TRIGGER_SCAN,
	NL80211_CMD_NEW_SCAN_RESULTS,
	NL80211_CMD_SCAN_ABORTED,

	NL80211_CMD_REG_CHANGE,

	NL80211_CMD_AUTHENTICATE,
	NL80211_CMD_ASSOCIATE,
	NL80211_CMD_DEAUTHENTICATE,
	NL80211_CMD_DISASSOCIATE,

	NL80211_CMD_MICHAEL_MIC_FAILURE,

	NL80211_CMD_REG_BEACON_HINT,

	NL80211_CMD_JOIN_IBSS,
	NL80211_CMD_LEAVE_IBSS,

	NL80211_CMD_TESTMODE,

	NL80211_CMD_CONNECT,
	NL80211_CMD_ROAM,
	NL80211_CMD_DISCONNECT,

	NL80211_CMD_SET_WIPHY_NETNS,

	NL80211_CMD_GET_SURVEY,
	NL80211_CMD_NEW_SURVEY_RESULTS,

	NL80211_CMD_SET_PMKSA,
	NL80211_CMD_DEL_PMKSA,
	NL80211_CMD_FLUSH_PMKSA,

	NL80211_CMD_REMAIN_ON_CHANNEL,
	NL80211_CMD_CANCEL_REMAIN_ON_CHANNEL,

	NL80211_CMD_SET_TX_BITRATE_MASK,

	NL80211_CMD_REGISTER_FRAME,
	NL80211_CMD_REGISTER_ACTION = NL80211_CMD_REGISTER_FRAME,
	NL80211_CMD_FRAME,
	NL80211_CMD_ACTION = NL80211_CMD_FRAME,
	NL80211_CMD_FRAME_TX_STATUS,
	NL80211_CMD_ACTION_TX_STATUS = NL80211_CMD_FRAME_TX_STATUS,

	NL80211_CMD_SET_POWER_SAVE,
	NL80211_CMD_GET_POWER_SAVE,

	NL80211_CMD_SET_CQM,
	NL80211_CMD_NOTIFY_CQM,

	NL80211_CMD_SET_CHANNEL,
	NL80211_CMD_SET_WDS_PEER,

	NL80211_CMD_FRAME_WAIT_CANCEL,

	NL80211_CMD_JOIN_MESH,
	NL80211_CMD_LEAVE_MESH,

	NL80211_CMD_UNPROT_DEAUTHENTICATE,
	NL80211_CMD_UNPROT_DISASSOCIATE,

	NL80211_CMD_NEW_PEER_CANDIDATE,

	NL80211_CMD_GET_WOWLAN,
	NL80211_CMD_SET_WOWLAN,

	NL80211_CMD_START_SCHED_SCAN,
	NL80211_CMD_STOP_SCHED_SCAN,
	NL80211_CMD_SCHED_SCAN_RESULTS,
	NL80211_CMD_SCHED_SCAN_STOPPED,

	NL80211_CMD_SET_REKEY_OFFLOAD,

	NL80211_CMD_PMKSA_CANDIDATE,

	NL80211_CMD_TDLS_OPER,
	NL80211_CMD_TDLS_MGMT,

	NL80211_CMD_UNEXPECTED_FRAME,

	NL80211_CMD_PROBE_CLIENT,

	NL80211_CMD_REGISTER_BEACONS,

	NL80211_CMD_UNEXPECTED_4ADDR_FRAME,

	NL80211_CMD_SET_NOACK_MAP,

	NL80211_CMD_CH_SWITCH_NOTIFY,

	NL80211_CMD_START_P2P_DEVICE,
	NL80211_CMD_STOP_P2P_DEVICE,

	NL80211_CMD_CONN_FAILED,

	NL80211_CMD_SET_MCAST_RATE,

	NL80211_CMD_SET_MAC_ACL,

	NL80211_CMD_RADAR_DETECT,

	NL80211_CMD_GET_PROTOCOL_FEATURES,

	NL80211_CMD_UPDATE_FT_IES,
	NL80211_CMD_FT_EVENT,

	NL80211_CMD_CRIT_PROTOCOL_START,
	NL80211_CMD_CRIT_PROTOCOL_STOP,

	NL80211_CMD_GET_COALESCE,
	NL80211_CMD_SET_COALESCE,

	NL80211_CMD_CHANNEL_SWITCH,

	NL80211_CMD_VENDOR,

	NL80211_CMD_SET_QOS_MAP,

	NL80211_CMD_ADD_TX_TS,
	NL80211_CMD_DEL_TX_TS,

	NL80211_CMD_GET_MPP,

	NL80211_CMD_JOIN_OCB,
	NL80211_CMD_LEAVE_OCB,

	NL80211_CMD_CH_SWITCH_STARTED_NOTIFY,

	NL80211_CMD_TDLS_CHANNEL_SWITCH,
	NL80211_CMD_TDLS_CANCEL_CHANNEL_SWITCH,

	NL80211_CMD_WIPHY_REG_CHANGE,

	NL80211_CMD_ABORT_SCAN,

	NL80211_CMD_START_न_अंक,
	NL80211_CMD_STOP_न_अंक,
	NL80211_CMD_ADD_न_अंक_FUNCTION,
	NL80211_CMD_DEL_न_अंक_FUNCTION,
	NL80211_CMD_CHANGE_न_अंक_CONFIG,
	NL80211_CMD_न_अंक_MATCH,

	NL80211_CMD_SET_MULTICAST_TO_UNICAST,

	NL80211_CMD_UPDATE_CONNECT_PARAMS,

	NL80211_CMD_SET_PMK,
	NL80211_CMD_DEL_PMK,

	NL80211_CMD_PORT_AUTHORIZED,

	NL80211_CMD_RELOAD_REGDB,

	NL80211_CMD_EXTERNAL_AUTH,

	NL80211_CMD_STA_OPMODE_CHANGED,

	NL80211_CMD_CONTROL_PORT_FRAME,

	NL80211_CMD_GET_FTM_RESPONDER_STATS,

	NL80211_CMD_PEER_MEASUREMENT_START,
	NL80211_CMD_PEER_MEASUREMENT_RESULT,
	NL80211_CMD_PEER_MEASUREMENT_COMPLETE,

	NL80211_CMD_NOTIFY_RADAR,

	NL80211_CMD_UPDATE_OWE_INFO,

	NL80211_CMD_PROBE_MESH_LINK,

	NL80211_CMD_SET_TID_CONFIG,

	NL80211_CMD_UNPROT_BEACON,

	NL80211_CMD_CONTROL_PORT_FRAME_TX_STATUS,

	NL80211_CMD_SET_SAR_SPECS,

	/* add new commands above here */

	/* used to define NL80211_CMD_MAX below */
	__NL80211_CMD_AFTER_LAST,
	NL80211_CMD_MAX = __NL80211_CMD_AFTER_LAST - 1
पूर्ण;

/*
 * Allow user space programs to use #अगर_घोषित on new commands by defining them
 * here
 */
#घोषणा NL80211_CMD_SET_BSS NL80211_CMD_SET_BSS
#घोषणा NL80211_CMD_SET_MGMT_EXTRA_IE NL80211_CMD_SET_MGMT_EXTRA_IE
#घोषणा NL80211_CMD_REG_CHANGE NL80211_CMD_REG_CHANGE
#घोषणा NL80211_CMD_AUTHENTICATE NL80211_CMD_AUTHENTICATE
#घोषणा NL80211_CMD_ASSOCIATE NL80211_CMD_ASSOCIATE
#घोषणा NL80211_CMD_DEAUTHENTICATE NL80211_CMD_DEAUTHENTICATE
#घोषणा NL80211_CMD_DISASSOCIATE NL80211_CMD_DISASSOCIATE
#घोषणा NL80211_CMD_REG_BEACON_HINT NL80211_CMD_REG_BEACON_HINT

#घोषणा NL80211_ATTR_FEATURE_FLAGS NL80211_ATTR_FEATURE_FLAGS

/* source-level API compatibility */
#घोषणा NL80211_CMD_GET_MESH_PARAMS NL80211_CMD_GET_MESH_CONFIG
#घोषणा NL80211_CMD_SET_MESH_PARAMS NL80211_CMD_SET_MESH_CONFIG
#घोषणा NL80211_MESH_SETUP_VENDOR_PATH_SEL_IE NL80211_MESH_SETUP_IE

/**
 * क्रमागत nl80211_attrs - nl80211 netlink attributes
 *
 * @NL80211_ATTR_UNSPEC: unspecअगरied attribute to catch errors
 *
 * @NL80211_ATTR_WIPHY: index of wiphy to operate on, cf.
 *	/sys/class/ieee80211/<phyname>/index
 * @NL80211_ATTR_WIPHY_NAME: wiphy name (used क्रम renaming)
 * @NL80211_ATTR_WIPHY_TXQ_PARAMS: a nested array of TX queue parameters
 * @NL80211_ATTR_WIPHY_FREQ: frequency of the selected channel in MHz,
 *	defines the channel together with the (deprecated)
 *	%NL80211_ATTR_WIPHY_CHANNEL_TYPE attribute or the attributes
 *	%NL80211_ATTR_CHANNEL_WIDTH and अगर needed %NL80211_ATTR_CENTER_FREQ1
 *	and %NL80211_ATTR_CENTER_FREQ2
 * @NL80211_ATTR_CHANNEL_WIDTH: u32 attribute containing one of the values
 *	of &क्रमागत nl80211_chan_width, describing the channel width. See the
 *	करोcumentation of the क्रमागत क्रम more inक्रमmation.
 * @NL80211_ATTR_CENTER_FREQ1: Center frequency of the first part of the
 *	channel, used क्रम anything but 20 MHz bandwidth. In S1G this is the
 *	operating channel center frequency.
 * @NL80211_ATTR_CENTER_FREQ2: Center frequency of the second part of the
 *	channel, used only क्रम 80+80 MHz bandwidth
 * @NL80211_ATTR_WIPHY_CHANNEL_TYPE: included with NL80211_ATTR_WIPHY_FREQ
 *	अगर HT20 or HT40 are to be used (i.e., HT disabled अगर not included):
 *	NL80211_CHAN_NO_HT = HT not allowed (i.e., same as not including
 *		this attribute)
 *	NL80211_CHAN_HT20 = HT20 only
 *	NL80211_CHAN_HT40MINUS = secondary channel is below the primary channel
 *	NL80211_CHAN_HT40PLUS = secondary channel is above the primary channel
 *	This attribute is now deprecated.
 * @NL80211_ATTR_WIPHY_RETRY_SHORT: TX retry limit क्रम frames whose length is
 *	less than or equal to the RTS threshold; allowed range: 1..255;
 *	करोt11ShortRetryLimit; u8
 * @NL80211_ATTR_WIPHY_RETRY_LONG: TX retry limit क्रम frames whose length is
 *	greater than the RTS threshold; allowed range: 1..255;
 *	करोt11ShortLongLimit; u8
 * @NL80211_ATTR_WIPHY_FRAG_THRESHOLD: fragmentation threshold, i.e., maximum
 *	length in octets क्रम frames; allowed range: 256..8000, disable
 *	fragmentation with (u32)-1; करोt11FragmentationThreshold; u32
 * @NL80211_ATTR_WIPHY_RTS_THRESHOLD: RTS threshold (TX frames with length
 *	larger than or equal to this use RTS/CTS handshake); allowed range:
 *	0..65536, disable with (u32)-1; करोt11RTSThreshold; u32
 * @NL80211_ATTR_WIPHY_COVERAGE_CLASS: Coverage Class as defined by IEEE 802.11
 *	section 7.3.2.9; करोt11CoverageClass; u8
 *
 * @NL80211_ATTR_IFINDEX: network पूर्णांकerface index of the device to operate on
 * @NL80211_ATTR_IFNAME: network पूर्णांकerface name
 * @NL80211_ATTR_IFTYPE: type of भव पूर्णांकerface, see &क्रमागत nl80211_अगरtype
 *
 * @NL80211_ATTR_WDEV: wireless device identअगरier, used क्रम pseuकरो-devices
 *	that करोn't have a netdev (u64)
 *
 * @NL80211_ATTR_MAC: MAC address (various uses)
 *
 * @NL80211_ATTR_KEY_DATA: (temporal) key data; क्रम TKIP this consists of
 *	16 bytes encryption key followed by 8 bytes each क्रम TX and RX MIC
 *	keys
 * @NL80211_ATTR_KEY_IDX: key ID (u8, 0-3)
 * @NL80211_ATTR_KEY_CIPHER: key cipher suite (u32, as defined by IEEE 802.11
 *	section 7.3.2.25.1, e.g. 0x000FAC04)
 * @NL80211_ATTR_KEY_SEQ: transmit key sequence number (IV/PN) क्रम TKIP and
 *	CCMP keys, each six bytes in little endian
 * @NL80211_ATTR_KEY_DEFAULT: Flag attribute indicating the key is शेष key
 * @NL80211_ATTR_KEY_DEFAULT_MGMT: Flag attribute indicating the key is the
 *	शेष management key
 * @NL80211_ATTR_CIPHER_SUITES_PAIRWISE: For crypto settings क्रम connect or
 *	other commands, indicates which pairwise cipher suites are used
 * @NL80211_ATTR_CIPHER_SUITE_GROUP: For crypto settings क्रम connect or
 *	other commands, indicates which group cipher suite is used
 *
 * @NL80211_ATTR_BEACON_INTERVAL: beacon पूर्णांकerval in TU
 * @NL80211_ATTR_DTIM_PERIOD: DTIM period क्रम beaconing
 * @NL80211_ATTR_BEACON_HEAD: portion of the beacon beक्रमe the TIM IE
 * @NL80211_ATTR_BEACON_TAIL: portion of the beacon after the TIM IE
 *
 * @NL80211_ATTR_STA_AID: Association ID क्रम the station (u16)
 * @NL80211_ATTR_STA_FLAGS: flags, nested element with NLA_FLAG attributes of
 *	&क्रमागत nl80211_sta_flags (deprecated, use %NL80211_ATTR_STA_FLAGS2)
 * @NL80211_ATTR_STA_LISTEN_INTERVAL: listen पूर्णांकerval as defined by
 *	IEEE 802.11 7.3.1.6 (u16).
 * @NL80211_ATTR_STA_SUPPORTED_RATES: supported rates, array of supported
 *	rates as defined by IEEE 802.11 7.3.2.2 but without the length
 *	restriction (at most %NL80211_MAX_SUPP_RATES).
 * @NL80211_ATTR_STA_VLAN: पूर्णांकerface index of VLAN पूर्णांकerface to move station
 *	to, or the AP पूर्णांकerface the station was originally added to.
 * @NL80211_ATTR_STA_INFO: inक्रमmation about a station, part of station info
 *	given क्रम %NL80211_CMD_GET_STATION, nested attribute containing
 *	info as possible, see &क्रमागत nl80211_sta_info.
 *
 * @NL80211_ATTR_WIPHY_BANDS: Inक्रमmation about an operating bands,
 *	consisting of a nested array.
 *
 * @NL80211_ATTR_MESH_ID: mesh id (1-32 bytes).
 * @NL80211_ATTR_STA_PLINK_ACTION: action to perक्रमm on the mesh peer link
 *	(see &क्रमागत nl80211_plink_action).
 * @NL80211_ATTR_MPATH_NEXT_HOP: MAC address of the next hop क्रम a mesh path.
 * @NL80211_ATTR_MPATH_INFO: inक्रमmation about a mesh_path, part of mesh path
 * 	info given क्रम %NL80211_CMD_GET_MPATH, nested attribute described at
 *	&क्रमागत nl80211_mpath_info.
 *
 * @NL80211_ATTR_MNTR_FLAGS: flags, nested element with NLA_FLAG attributes of
 *      &क्रमागत nl80211_mntr_flags.
 *
 * @NL80211_ATTR_REG_ALPHA2: an ISO-3166-alpha2 country code क्रम which the
 * 	current regulatory करोमुख्य should be set to or is alपढ़ोy set to.
 * 	For example, 'CR', क्रम Costa Rica. This attribute is used by the kernel
 * 	to query the CRDA to retrieve one regulatory करोमुख्य. This attribute can
 * 	also be used by userspace to query the kernel क्रम the currently set
 * 	regulatory करोमुख्य. We chose an alpha2 as that is also used by the
 * 	IEEE-802.11 country inक्रमmation element to identअगरy a country.
 * 	Users can also simply ask the wireless core to set regulatory करोमुख्य
 * 	to a specअगरic alpha2.
 * @NL80211_ATTR_REG_RULES: a nested array of regulatory करोमुख्य regulatory
 *	rules.
 *
 * @NL80211_ATTR_BSS_CTS_PROT: whether CTS protection is enabled (u8, 0 or 1)
 * @NL80211_ATTR_BSS_SHORT_PREAMBLE: whether लघु preamble is enabled
 *	(u8, 0 or 1)
 * @NL80211_ATTR_BSS_SHORT_SLOT_TIME: whether लघु slot समय enabled
 *	(u8, 0 or 1)
 * @NL80211_ATTR_BSS_BASIC_RATES: basic rates, array of basic
 *	rates in क्रमmat defined by IEEE 802.11 7.3.2.2 but without the length
 *	restriction (at most %NL80211_MAX_SUPP_RATES).
 *
 * @NL80211_ATTR_HT_CAPABILITY: HT Capability inक्रमmation element (from
 *	association request when used with NL80211_CMD_NEW_STATION)
 *
 * @NL80211_ATTR_SUPPORTED_IFTYPES: nested attribute containing all
 *	supported पूर्णांकerface types, each a flag attribute with the number
 *	of the पूर्णांकerface mode.
 *
 * @NL80211_ATTR_MGMT_SUBTYPE: Management frame subtype क्रम
 *	%NL80211_CMD_SET_MGMT_EXTRA_IE.
 *
 * @NL80211_ATTR_IE: Inक्रमmation element(s) data (used, e.g., with
 *	%NL80211_CMD_SET_MGMT_EXTRA_IE).
 *
 * @NL80211_ATTR_MAX_NUM_SCAN_SSIDS: number of SSIDs you can scan with
 *	a single scan request, a wiphy attribute.
 * @NL80211_ATTR_MAX_NUM_SCHED_SCAN_SSIDS: number of SSIDs you can
 *	scan with a single scheduled scan request, a wiphy attribute.
 * @NL80211_ATTR_MAX_SCAN_IE_LEN: maximum length of inक्रमmation elements
 *	that can be added to a scan request
 * @NL80211_ATTR_MAX_SCHED_SCAN_IE_LEN: maximum length of inक्रमmation
 *	elements that can be added to a scheduled scan request
 * @NL80211_ATTR_MAX_MATCH_SETS: maximum number of sets that can be
 *	used with @NL80211_ATTR_SCHED_SCAN_MATCH, a wiphy attribute.
 *
 * @NL80211_ATTR_SCAN_FREQUENCIES: nested attribute with frequencies (in MHz)
 * @NL80211_ATTR_SCAN_SSIDS: nested attribute with SSIDs, leave out क्रम passive
 *	scanning and include a zero-length SSID (wildcard) क्रम wildcard scan
 * @NL80211_ATTR_BSS: scan result BSS
 *
 * @NL80211_ATTR_REG_INITIATOR: indicates who requested the regulatory करोमुख्य
 * 	currently in effect. This could be any of the %NL80211_REGDOM_SET_BY_*
 * @NL80211_ATTR_REG_TYPE: indicates the type of the regulatory करोमुख्य currently
 * 	set. This can be one of the nl80211_reg_type (%NL80211_REGDOM_TYPE_*)
 *
 * @NL80211_ATTR_SUPPORTED_COMMANDS: wiphy attribute that specअगरies
 *	an array of command numbers (i.e. a mapping index to command number)
 *	that the driver क्रम the given wiphy supports.
 *
 * @NL80211_ATTR_FRAME: frame data (binary attribute), including frame header
 *	and body, but not FCS; used, e.g., with NL80211_CMD_AUTHENTICATE and
 *	NL80211_CMD_ASSOCIATE events
 * @NL80211_ATTR_SSID: SSID (binary attribute, 0..32 octets)
 * @NL80211_ATTR_AUTH_TYPE: AuthenticationType, see &क्रमागत nl80211_auth_type,
 *	represented as a u32
 * @NL80211_ATTR_REASON_CODE: ReasonCode क्रम %NL80211_CMD_DEAUTHENTICATE and
 *	%NL80211_CMD_DISASSOCIATE, u16
 *
 * @NL80211_ATTR_KEY_TYPE: Key Type, see &क्रमागत nl80211_key_type, represented as
 *	a u32
 *
 * @NL80211_ATTR_FREQ_BEFORE: A channel which has suffered a regulatory change
 * 	due to considerations from a beacon hपूर्णांक. This attribute reflects
 * 	the state of the channel _beक्रमe_ the beacon hपूर्णांक processing. This
 * 	attributes consists of a nested attribute containing
 * 	NL80211_FREQUENCY_ATTR_*
 * @NL80211_ATTR_FREQ_AFTER: A channel which has suffered a regulatory change
 * 	due to considerations from a beacon hपूर्णांक. This attribute reflects
 * 	the state of the channel _after_ the beacon hपूर्णांक processing. This
 * 	attributes consists of a nested attribute containing
 * 	NL80211_FREQUENCY_ATTR_*
 *
 * @NL80211_ATTR_CIPHER_SUITES: a set of u32 values indicating the supported
 *	cipher suites
 *
 * @NL80211_ATTR_FREQ_FIXED: a flag indicating the IBSS should not try to look
 *	क्रम other networks on dअगरferent channels
 *
 * @NL80211_ATTR_TIMED_OUT: a flag indicating than an operation समयd out; this
 *	is used, e.g., with %NL80211_CMD_AUTHENTICATE event
 *
 * @NL80211_ATTR_USE_MFP: Whether management frame protection (IEEE 802.11w) is
 *	used क्रम the association (&क्रमागत nl80211_mfp, represented as a u32);
 *	this attribute can be used with %NL80211_CMD_ASSOCIATE and
 *	%NL80211_CMD_CONNECT requests. %NL80211_MFP_OPTIONAL is not allowed क्रम
 *	%NL80211_CMD_ASSOCIATE since user space SME is expected and hence, it
 *	must have decided whether to use management frame protection or not.
 *	Setting %NL80211_MFP_OPTIONAL with a %NL80211_CMD_CONNECT request will
 *	let the driver (or the firmware) decide whether to use MFP or not.
 *
 * @NL80211_ATTR_STA_FLAGS2: Attribute containing a
 *	&काष्ठा nl80211_sta_flag_update.
 *
 * @NL80211_ATTR_CONTROL_PORT: A flag indicating whether user space controls
 *	IEEE 802.1X port, i.e., sets/clears %NL80211_STA_FLAG_AUTHORIZED, in
 *	station mode. If the flag is included in %NL80211_CMD_ASSOCIATE
 *	request, the driver will assume that the port is unauthorized until
 *	authorized by user space. Otherwise, port is marked authorized by
 *	शेष in station mode.
 * @NL80211_ATTR_CONTROL_PORT_ETHERTYPE: A 16-bit value indicating the
 *	ethertype that will be used क्रम key negotiation. It can be
 *	specअगरied with the associate and connect commands. If it is not
 *	specअगरied, the value शेषs to 0x888E (PAE, 802.1X). This
 *	attribute is also used as a flag in the wiphy inक्रमmation to
 *	indicate that protocols other than PAE are supported.
 * @NL80211_ATTR_CONTROL_PORT_NO_ENCRYPT: When included aदीर्घ with
 *	%NL80211_ATTR_CONTROL_PORT_ETHERTYPE, indicates that the custom
 *	ethertype frames used क्रम key negotiation must not be encrypted.
 * @NL80211_ATTR_CONTROL_PORT_OVER_NL80211: A flag indicating whether control
 *	port frames (e.g. of type given in %NL80211_ATTR_CONTROL_PORT_ETHERTYPE)
 *	will be sent directly to the network पूर्णांकerface or sent via the NL80211
 *	socket.  If this attribute is missing, then legacy behavior of sending
 *	control port frames directly to the network पूर्णांकerface is used.  If the
 *	flag is included, then control port frames are sent over NL80211 instead
 *	using %CMD_CONTROL_PORT_FRAME.  If control port routing over NL80211 is
 *	to be used then userspace must also use the %NL80211_ATTR_SOCKET_OWNER
 *	flag. When used with %NL80211_ATTR_CONTROL_PORT_NO_PREAUTH, pre-auth
 *	frames are not क्रमwared over the control port.
 *
 * @NL80211_ATTR_TESTDATA: Tesपंचांगode data blob, passed through to the driver.
 *	We recommend using nested, driver-specअगरic attributes within this.
 *
 * @NL80211_ATTR_DISCONNECTED_BY_AP: A flag indicating that the DISCONNECT
 *	event was due to the AP disconnecting the station, and not due to
 *	a local disconnect request.
 * @NL80211_ATTR_STATUS_CODE: StatusCode क्रम the %NL80211_CMD_CONNECT
 *	event (u16)
 * @NL80211_ATTR_PRIVACY: Flag attribute, used with connect(), indicating
 *	that रक्षित APs should be used. This is also used with NEW_BEACON to
 *	indicate that the BSS is to use protection.
 *
 * @NL80211_ATTR_CIPHERS_PAIRWISE: Used with CONNECT, ASSOCIATE, and NEW_BEACON
 *	to indicate which unicast key ciphers will be used with the connection
 *	(an array of u32).
 * @NL80211_ATTR_CIPHER_GROUP: Used with CONNECT, ASSOCIATE, and NEW_BEACON to
 *	indicate which group key cipher will be used with the connection (a
 *	u32).
 * @NL80211_ATTR_WPA_VERSIONS: Used with CONNECT, ASSOCIATE, and NEW_BEACON to
 *	indicate which WPA version(s) the AP we want to associate with is using
 *	(a u32 with flags from &क्रमागत nl80211_wpa_versions).
 * @NL80211_ATTR_AKM_SUITES: Used with CONNECT, ASSOCIATE, and NEW_BEACON to
 *	indicate which key management algorithm(s) to use (an array of u32).
 *	This attribute is also sent in response to @NL80211_CMD_GET_WIPHY,
 *	indicating the supported AKM suites, पूर्णांकended क्रम specअगरic drivers which
 *	implement SME and have स्थिरraपूर्णांकs on which AKMs are supported and also
 *	the हालs where an AKM support is offloaded to the driver/firmware.
 *	If there is no such notअगरication from the driver, user space should
 *	assume the driver supports all the AKM suites.
 *
 * @NL80211_ATTR_REQ_IE: (Re)association request inक्रमmation elements as
 *	sent out by the card, क्रम ROAM and successful CONNECT events.
 * @NL80211_ATTR_RESP_IE: (Re)association response inक्रमmation elements as
 *	sent by peer, क्रम ROAM and successful CONNECT events.
 *
 * @NL80211_ATTR_PREV_BSSID: previous BSSID, to be used in ASSOCIATE and CONNECT
 *	commands to specअगरy a request to reassociate within an ESS, i.e., to use
 *	Reassociate Request frame (with the value of this attribute in the
 *	Current AP address field) instead of Association Request frame which is
 *	used क्रम the initial association to an ESS.
 *
 * @NL80211_ATTR_KEY: key inक्रमmation in a nested attribute with
 *	%NL80211_KEY_* sub-attributes
 * @NL80211_ATTR_KEYS: array of keys क्रम अटल WEP keys क्रम connect()
 *	and join_ibss(), key inक्रमmation is in a nested attribute each
 *	with %NL80211_KEY_* sub-attributes
 *
 * @NL80211_ATTR_PID: Process ID of a network namespace.
 *
 * @NL80211_ATTR_GENERATION: Used to indicate consistent snapshots क्रम
 *	dumps. This number increases whenever the object list being
 *	dumped changes, and as such userspace can verअगरy that it has
 *	obtained a complete and consistent snapshot by verअगरying that
 *	all dump messages contain the same generation number. If it
 *	changed then the list changed and the dump should be repeated
 *	completely from scratch.
 *
 * @NL80211_ATTR_4ADDR: Use 4-address frames on a भव पूर्णांकerface
 *
 * @NL80211_ATTR_SURVEY_INFO: survey inक्रमmation about a channel, part of
 *      the survey response क्रम %NL80211_CMD_GET_SURVEY, nested attribute
 *      containing info as possible, see &क्रमागत survey_info.
 *
 * @NL80211_ATTR_PMKID: PMK material क्रम PMKSA caching.
 * @NL80211_ATTR_MAX_NUM_PMKIDS: maximum number of PMKIDs a firmware can
 *	cache, a wiphy attribute.
 *
 * @NL80211_ATTR_DURATION: Duration of an operation in milliseconds, u32.
 * @NL80211_ATTR_MAX_REMAIN_ON_CHANNEL_DURATION: Device attribute that
 *	specअगरies the maximum duration that can be requested with the
 *	reमुख्य-on-channel operation, in milliseconds, u32.
 *
 * @NL80211_ATTR_COOKIE: Generic 64-bit cookie to identअगरy objects.
 *
 * @NL80211_ATTR_TX_RATES: Nested set of attributes
 *	(क्रमागत nl80211_tx_rate_attributes) describing TX rates per band. The
 *	क्रमागत nl80211_band value is used as the index (nla_type() of the nested
 *	data. If a band is not included, it will be configured to allow all
 *	rates based on negotiated supported rates inक्रमmation. This attribute
 *	is used with %NL80211_CMD_SET_TX_BITRATE_MASK and with starting AP,
 *	and joining mesh networks (not IBSS yet). In the later हाल, it must
 *	specअगरy just a single bitrate, which is to be used क्रम the beacon.
 *	The driver must also specअगरy support क्रम this with the extended
 *	features NL80211_EXT_FEATURE_BEACON_RATE_LEGACY,
 *	NL80211_EXT_FEATURE_BEACON_RATE_HT,
 *	NL80211_EXT_FEATURE_BEACON_RATE_VHT and
 *	NL80211_EXT_FEATURE_BEACON_RATE_HE.
 *
 * @NL80211_ATTR_FRAME_MATCH: A binary attribute which typically must contain
 *	at least one byte, currently used with @NL80211_CMD_REGISTER_FRAME.
 * @NL80211_ATTR_FRAME_TYPE: A u16 indicating the frame type/subtype क्रम the
 *	@NL80211_CMD_REGISTER_FRAME command.
 * @NL80211_ATTR_TX_FRAME_TYPES: wiphy capability attribute, which is a
 *	nested attribute of %NL80211_ATTR_FRAME_TYPE attributes, containing
 *	inक्रमmation about which frame types can be transmitted with
 *	%NL80211_CMD_FRAME.
 * @NL80211_ATTR_RX_FRAME_TYPES: wiphy capability attribute, which is a
 *	nested attribute of %NL80211_ATTR_FRAME_TYPE attributes, containing
 *	inक्रमmation about which frame types can be रेजिस्टरed क्रम RX.
 *
 * @NL80211_ATTR_ACK: Flag attribute indicating that the frame was
 *	acknowledged by the recipient.
 *
 * @NL80211_ATTR_PS_STATE: घातersave state, using &क्रमागत nl80211_ps_state values.
 *
 * @NL80211_ATTR_CQM: connection quality monitor configuration in a
 *	nested attribute with %NL80211_ATTR_CQM_* sub-attributes.
 *
 * @NL80211_ATTR_LOCAL_STATE_CHANGE: Flag attribute to indicate that a command
 *	is requesting a local authentication/association state change without
 *	invoking actual management frame exchange. This can be used with
 *	NL80211_CMD_AUTHENTICATE, NL80211_CMD_DEAUTHENTICATE,
 *	NL80211_CMD_DISASSOCIATE.
 *
 * @NL80211_ATTR_AP_ISOLATE: (AP mode) Do not क्रमward traffic between stations
 *	connected to this BSS.
 *
 * @NL80211_ATTR_WIPHY_TX_POWER_SETTING: Transmit घातer setting type. See
 *      &क्रमागत nl80211_tx_घातer_setting क्रम possible values.
 * @NL80211_ATTR_WIPHY_TX_POWER_LEVEL: Transmit घातer level in चिन्हित mBm units.
 *      This is used in association with @NL80211_ATTR_WIPHY_TX_POWER_SETTING
 *      क्रम non-स्वतःmatic settings.
 *
 * @NL80211_ATTR_SUPPORT_IBSS_RSN: The device supports IBSS RSN, which mostly
 *	means support क्रम per-station GTKs.
 *
 * @NL80211_ATTR_WIPHY_ANTENNA_TX: Biपंचांगap of allowed antennas क्रम transmitting.
 *	This can be used to mask out antennas which are not attached or should
 *	not be used क्रम transmitting. If an antenna is not selected in this
 *	biपंचांगap the hardware is not allowed to transmit on this antenna.
 *
 *	Each bit represents one antenna, starting with antenna 1 at the first
 *	bit. Depending on which antennas are selected in the biपंचांगap, 802.11n
 *	drivers can derive which chainmasks to use (अगर all antennas beदीर्घing to
 *	a particular chain are disabled this chain should be disabled) and अगर
 *	a chain has भागersity antennas wether भागersity should be used or not.
 *	HT capabilities (STBC, TX Beamक्रमming, Antenna selection) can be
 *	derived from the available chains after applying the antenna mask.
 *	Non-802.11n drivers can derive wether to use भागersity or not.
 *	Drivers may reject configurations or RX/TX mask combinations they cannot
 *	support by वापसing -EINVAL.
 *
 * @NL80211_ATTR_WIPHY_ANTENNA_RX: Biपंचांगap of allowed antennas क्रम receiving.
 *	This can be used to mask out antennas which are not attached or should
 *	not be used क्रम receiving. If an antenna is not selected in this biपंचांगap
 *	the hardware should not be configured to receive on this antenna.
 *	For a more detailed description see @NL80211_ATTR_WIPHY_ANTENNA_TX.
 *
 * @NL80211_ATTR_WIPHY_ANTENNA_AVAIL_TX: Biपंचांगap of antennas which are available
 *	क्रम configuration as TX antennas via the above parameters.
 *
 * @NL80211_ATTR_WIPHY_ANTENNA_AVAIL_RX: Biपंचांगap of antennas which are available
 *	क्रम configuration as RX antennas via the above parameters.
 *
 * @NL80211_ATTR_MCAST_RATE: Multicast tx rate (in 100 kbps) क्रम IBSS
 *
 * @NL80211_ATTR_OFFCHANNEL_TX_OK: For management frame TX, the frame may be
 *	transmitted on another channel when the channel given करोesn't match
 *	the current channel. If the current channel करोesn't match and this
 *	flag isn't set, the frame will be rejected. This is also used as an
 *	nl80211 capability flag.
 *
 * @NL80211_ATTR_BSS_HT_OPMODE: HT operation mode (u16)
 *
 * @NL80211_ATTR_KEY_DEFAULT_TYPES: A nested attribute containing flags
 *	attributes, specअगरying what a key should be set as शेष as.
 *	See &क्रमागत nl80211_key_शेष_types.
 *
 * @NL80211_ATTR_MESH_SETUP: Optional mesh setup parameters.  These cannot be
 *	changed once the mesh is active.
 * @NL80211_ATTR_MESH_CONFIG: Mesh configuration parameters, a nested attribute
 *	containing attributes from &क्रमागत nl80211_meshconf_params.
 * @NL80211_ATTR_SUPPORT_MESH_AUTH: Currently, this means the underlying driver
 *	allows auth frames in a mesh to be passed to userspace क्रम processing via
 *	the @NL80211_MESH_SETUP_USERSPACE_AUTH flag.
 * @NL80211_ATTR_STA_PLINK_STATE: The state of a mesh peer link as defined in
 *	&क्रमागत nl80211_plink_state. Used when userspace is driving the peer link
 *	management state machine.  @NL80211_MESH_SETUP_USERSPACE_AMPE or
 *	@NL80211_MESH_SETUP_USERSPACE_MPM must be enabled.
 *
 * @NL80211_ATTR_WOWLAN_TRIGGERS_SUPPORTED: indicates, as part of the wiphy
 *	capabilities, the supported WoWLAN triggers
 * @NL80211_ATTR_WOWLAN_TRIGGERS: used by %NL80211_CMD_SET_WOWLAN to
 *	indicate which WoW triggers should be enabled. This is also
 *	used by %NL80211_CMD_GET_WOWLAN to get the currently enabled WoWLAN
 *	triggers.
 *
 * @NL80211_ATTR_SCHED_SCAN_INTERVAL: Interval between scheduled scan
 *	cycles, in msecs.
 *
 * @NL80211_ATTR_SCHED_SCAN_MATCH: Nested attribute with one or more
 *	sets of attributes to match during scheduled scans.  Only BSSs
 *	that match any of the sets will be reported.  These are
 *	pass-thru filter rules.
 *	For a match to succeed, the BSS must match all attributes of a
 *	set.  Since not every hardware supports matching all types of
 *	attributes, there is no guarantee that the reported BSSs are
 *	fully complying with the match sets and userspace needs to be
 *	able to ignore them by itself.
 *	Thus, the implementation is somewhat hardware-dependent, but
 *	this is only an optimization and the userspace application
 *	needs to handle all the non-filtered results anyway.
 *	If the match attributes करोn't make sense when combined with
 *	the values passed in @NL80211_ATTR_SCAN_SSIDS (eg. अगर an SSID
 *	is included in the probe request, but the match attributes
 *	will never let it go through), -EINVAL may be वापसed.
 *	If omitted, no filtering is करोne.
 *
 * @NL80211_ATTR_INTERFACE_COMBINATIONS: Nested attribute listing the supported
 *	पूर्णांकerface combinations. In each nested item, it contains attributes
 *	defined in &क्रमागत nl80211_अगर_combination_attrs.
 * @NL80211_ATTR_SOFTWARE_IFTYPES: Nested attribute (just like
 *	%NL80211_ATTR_SUPPORTED_IFTYPES) containing the पूर्णांकerface types that
 *	are managed in software: पूर्णांकerfaces of these types aren't subject to
 *	any restrictions in their number or combinations.
 *
 * @NL80211_ATTR_REKEY_DATA: nested attribute containing the inक्रमmation
 *	necessary क्रम GTK rekeying in the device, see &क्रमागत nl80211_rekey_data.
 *
 * @NL80211_ATTR_SCAN_SUPP_RATES: rates per to be advertised as supported in scan,
 *	nested array attribute containing an entry क्रम each band, with the entry
 *	being a list of supported rates as defined by IEEE 802.11 7.3.2.2 but
 *	without the length restriction (at most %NL80211_MAX_SUPP_RATES).
 *
 * @NL80211_ATTR_HIDDEN_SSID: indicates whether SSID is to be hidden from Beacon
 *	and Probe Response (when response to wildcard Probe Request); see
 *	&क्रमागत nl80211_hidden_ssid, represented as a u32
 *
 * @NL80211_ATTR_IE_PROBE_RESP: Inक्रमmation element(s) क्रम Probe Response frame.
 *	This is used with %NL80211_CMD_NEW_BEACON and %NL80211_CMD_SET_BEACON to
 *	provide extra IEs (e.g., WPS/P2P IE) पूर्णांकo Probe Response frames when the
 *	driver (or firmware) replies to Probe Request frames.
 * @NL80211_ATTR_IE_ASSOC_RESP: Inक्रमmation element(s) क्रम (Re)Association
 *	Response frames. This is used with %NL80211_CMD_NEW_BEACON and
 *	%NL80211_CMD_SET_BEACON to provide extra IEs (e.g., WPS/P2P IE) पूर्णांकo
 *	(Re)Association Response frames when the driver (or firmware) replies to
 *	(Re)Association Request frames.
 *
 * @NL80211_ATTR_STA_WME: Nested attribute containing the wme configuration
 *	of the station, see &क्रमागत nl80211_sta_wme_attr.
 * @NL80211_ATTR_SUPPORT_AP_UAPSD: the device supports uapsd when working
 *	as AP.
 *
 * @NL80211_ATTR_ROAM_SUPPORT: Indicates whether the firmware is capable of
 *	roaming to another AP in the same ESS अगर the संकेत lever is low.
 *
 * @NL80211_ATTR_PMKSA_CANDIDATE: Nested attribute containing the PMKSA caching
 *	candidate inक्रमmation, see &क्रमागत nl80211_pmksa_candidate_attr.
 *
 * @NL80211_ATTR_TX_NO_CCK_RATE: Indicates whether to use CCK rate or not
 *	क्रम management frames transmission. In order to aव्योम p2p probe/action
 *	frames are being transmitted at CCK rate in 2GHz band, the user space
 *	applications use this attribute.
 *	This attribute is used with %NL80211_CMD_TRIGGER_SCAN and
 *	%NL80211_CMD_FRAME commands.
 *
 * @NL80211_ATTR_TDLS_ACTION: Low level TDLS action code (e.g. link setup
 *	request, link setup confirm, link tearकरोwn, etc.). Values are
 *	described in the TDLS (802.11z) specअगरication.
 * @NL80211_ATTR_TDLS_DIALOG_TOKEN: Non-zero token क्रम uniquely identअगरying a
 *	TDLS conversation between two devices.
 * @NL80211_ATTR_TDLS_OPERATION: High level TDLS operation; see
 *	&क्रमागत nl80211_tdls_operation, represented as a u8.
 * @NL80211_ATTR_TDLS_SUPPORT: A flag indicating the device can operate
 *	as a TDLS peer sta.
 * @NL80211_ATTR_TDLS_EXTERNAL_SETUP: The TDLS discovery/setup and tearकरोwn
 *	procedures should be perक्रमmed by sending TDLS packets via
 *	%NL80211_CMD_TDLS_MGMT. Otherwise %NL80211_CMD_TDLS_OPER should be
 *	used क्रम asking the driver to perक्रमm a TDLS operation.
 *
 * @NL80211_ATTR_DEVICE_AP_SME: This u32 attribute may be listed क्रम devices
 *	that have AP support to indicate that they have the AP SME पूर्णांकegrated
 *	with support क्रम the features listed in this attribute, see
 *	&क्रमागत nl80211_ap_sme_features.
 *
 * @NL80211_ATTR_DONT_WAIT_FOR_ACK: Used with %NL80211_CMD_FRAME, this tells
 *	the driver to not रुको क्रम an acknowledgement. Note that due to this,
 *	it will also not give a status callback nor वापस a cookie. This is
 *	mostly useful क्रम probe responses to save airसमय.
 *
 * @NL80211_ATTR_FEATURE_FLAGS: This u32 attribute contains flags from
 *	&क्रमागत nl80211_feature_flags and is advertised in wiphy inक्रमmation.
 * @NL80211_ATTR_PROBE_RESP_OFFLOAD: Indicates that the HW responds to probe
 *	requests जबतक operating in AP-mode.
 *	This attribute holds a biपंचांगap of the supported protocols क्रम
 *	offloading (see &क्रमागत nl80211_probe_resp_offload_support_attr).
 *
 * @NL80211_ATTR_PROBE_RESP: Probe Response ढाँचा data. Contains the entire
 *	probe-response frame. The DA field in the 802.11 header is zero-ed out,
 *	to be filled by the FW.
 * @NL80211_ATTR_DISABLE_HT: Force HT capable पूर्णांकerfaces to disable
 *      this feature during association. This is a flag attribute.
 *	Currently only supported in mac80211 drivers.
 * @NL80211_ATTR_DISABLE_VHT: Force VHT capable पूर्णांकerfaces to disable
 *      this feature during association. This is a flag attribute.
 *	Currently only supported in mac80211 drivers.
 * @NL80211_ATTR_DISABLE_HE: Force HE capable पूर्णांकerfaces to disable
 *      this feature during association. This is a flag attribute.
 *	Currently only supported in mac80211 drivers.
 * @NL80211_ATTR_HT_CAPABILITY_MASK: Specअगरy which bits of the
 *      ATTR_HT_CAPABILITY to which attention should be paid.
 *      Currently, only mac80211 NICs support this feature.
 *      The values that may be configured are:
 *       MCS rates, MAX-AMSDU, HT-20-40 and HT_CAP_SGI_40
 *       AMPDU density and AMPDU factor.
 *      All values are treated as suggestions and may be ignored
 *      by the driver as required.  The actual values may be seen in
 *      the station debugfs ht_caps file.
 *
 * @NL80211_ATTR_DFS_REGION: region क्रम regulatory rules which this country
 *    abides to when initiating radiation on DFS channels. A country maps
 *    to one DFS region.
 *
 * @NL80211_ATTR_NOACK_MAP: This u16 biपंचांगap contains the No Ack Policy of
 *      up to 16 TIDs.
 *
 * @NL80211_ATTR_INACTIVITY_TIMEOUT: समयout value in seconds, this can be
 *	used by the drivers which has MLME in firmware and करोes not have support
 *	to report per station tx/rx activity to मुक्त up the station entry from
 *	the list. This needs to be used when the driver advertises the
 *	capability to समयout the stations.
 *
 * @NL80211_ATTR_RX_SIGNAL_DBM: संकेत strength in dBm (as a 32-bit पूर्णांक);
 *	this attribute is (depending on the driver capabilities) added to
 *	received frames indicated with %NL80211_CMD_FRAME.
 *
 * @NL80211_ATTR_BG_SCAN_PERIOD: Background scan period in seconds
 *      or 0 to disable background scan.
 *
 * @NL80211_ATTR_USER_REG_HINT_TYPE: type of regulatory hपूर्णांक passed from
 *	userspace. If unset it is assumed the hपूर्णांक comes directly from
 *	a user. If set code could specअगरy exactly what type of source
 *	was used to provide the hपूर्णांक. For the dअगरferent types of
 *	allowed user regulatory hपूर्णांकs see nl80211_user_reg_hपूर्णांक_type.
 *
 * @NL80211_ATTR_CONN_FAILED_REASON: The reason क्रम which AP has rejected
 *	the connection request from a station. nl80211_connect_failed_reason
 *	क्रमागत has dअगरferent reasons of connection failure.
 *
 * @NL80211_ATTR_AUTH_DATA: Fields and elements in Authentication frames.
 *	This contains the authentication frame body (non-IE and IE data),
 *	excluding the Authentication algorithm number, i.e., starting at the
 *	Authentication transaction sequence number field. It is used with
 *	authentication algorithms that need special fields to be added पूर्णांकo
 *	the frames (SAE and FILS). Currently, only the SAE हालs use the
 *	initial two fields (Authentication transaction sequence number and
 *	Status code). However, those fields are included in the attribute data
 *	क्रम all authentication algorithms to keep the attribute definition
 *	consistent.
 *
 * @NL80211_ATTR_VHT_CAPABILITY: VHT Capability inक्रमmation element (from
 *	association request when used with NL80211_CMD_NEW_STATION)
 *
 * @NL80211_ATTR_SCAN_FLAGS: scan request control flags (u32)
 *
 * @NL80211_ATTR_P2P_CTWINDOW: P2P GO Client Traffic Winकरोw (u8), used with
 *	the START_AP and SET_BSS commands
 * @NL80211_ATTR_P2P_OPPPS: P2P GO opportunistic PS (u8), used with the
 *	START_AP and SET_BSS commands. This can have the values 0 or 1;
 *	अगर not given in START_AP 0 is assumed, अगर not given in SET_BSS
 *	no change is made.
 *
 * @NL80211_ATTR_LOCAL_MESH_POWER_MODE: local mesh STA link-specअगरic घातer mode
 *	defined in &क्रमागत nl80211_mesh_घातer_mode.
 *
 * @NL80211_ATTR_ACL_POLICY: ACL policy, see &क्रमागत nl80211_acl_policy,
 *	carried in a u32 attribute
 *
 * @NL80211_ATTR_MAC_ADDRS: Array of nested MAC addresses, used क्रम
 *	MAC ACL.
 *
 * @NL80211_ATTR_MAC_ACL_MAX: u32 attribute to advertise the maximum
 *	number of MAC addresses that a device can support क्रम MAC
 *	ACL.
 *
 * @NL80211_ATTR_RADAR_EVENT: Type of radar event क्रम notअगरication to userspace,
 *	contains a value of क्रमागत nl80211_radar_event (u32).
 *
 * @NL80211_ATTR_EXT_CAPA: 802.11 extended capabilities that the kernel driver
 *	has and handles. The क्रमmat is the same as the IE contents. See
 *	802.11-2012 8.4.2.29 क्रम more inक्रमmation.
 * @NL80211_ATTR_EXT_CAPA_MASK: Extended capabilities that the kernel driver
 *	has set in the %NL80211_ATTR_EXT_CAPA value, क्रम multibit fields.
 *
 * @NL80211_ATTR_STA_CAPABILITY: Station capabilities (u16) are advertised to
 *	the driver, e.g., to enable TDLS घातer save (PU-APSD).
 *
 * @NL80211_ATTR_STA_EXT_CAPABILITY: Station extended capabilities are
 *	advertised to the driver, e.g., to enable TDLS off channel operations
 *	and PU-APSD.
 *
 * @NL80211_ATTR_PROTOCOL_FEATURES: global nl80211 feature flags, see
 *	&क्रमागत nl80211_protocol_features, the attribute is a u32.
 *
 * @NL80211_ATTR_SPLIT_WIPHY_DUMP: flag attribute, userspace supports
 *	receiving the data क्रम a single wiphy split across multiple
 *	messages, given with wiphy dump message
 *
 * @NL80211_ATTR_MDID: Mobility Doमुख्य Identअगरier
 *
 * @NL80211_ATTR_IE_RIC: Resource Inक्रमmation Container Inक्रमmation
 *	Element
 *
 * @NL80211_ATTR_CRIT_PROT_ID: critical protocol identअगरier requiring increased
 *	reliability, see &क्रमागत nl80211_crit_proto_id (u16).
 * @NL80211_ATTR_MAX_CRIT_PROT_DURATION: duration in milliseconds in which
 *      the connection should have increased reliability (u16).
 *
 * @NL80211_ATTR_PEER_AID: Association ID क्रम the peer TDLS station (u16).
 *	This is similar to @NL80211_ATTR_STA_AID but with a dअगरference of being
 *	allowed to be used with the first @NL80211_CMD_SET_STATION command to
 *	update a TDLS peer STA entry.
 *
 * @NL80211_ATTR_COALESCE_RULE: Coalesce rule inक्रमmation.
 *
 * @NL80211_ATTR_CH_SWITCH_COUNT: u32 attribute specअगरying the number of TBTT's
 *	until the channel चयन event.
 * @NL80211_ATTR_CH_SWITCH_BLOCK_TX: flag attribute specअगरying that transmission
 *	must be blocked on the current channel (beक्रमe the channel चयन
 *	operation). Also included in the channel चयन started event अगर quiet
 *	was requested by the AP.
 * @NL80211_ATTR_CSA_IES: Nested set of attributes containing the IE inक्रमmation
 *	क्रम the समय जबतक perक्रमming a channel चयन.
 * @NL80211_ATTR_CNTDWN_OFFS_BEACON: An array of offsets (u16) to the channel
 *	चयन or color change counters in the beacons tail (%NL80211_ATTR_BEACON_TAIL).
 * @NL80211_ATTR_CNTDWN_OFFS_PRESP: An array of offsets (u16) to the channel
 *	चयन or color change counters in the probe response (%NL80211_ATTR_PROBE_RESP).
 *
 * @NL80211_ATTR_RXMGMT_FLAGS: flags क्रम nl80211_send_mgmt(), u32.
 *	As specअगरied in the &क्रमागत nl80211_rxmgmt_flags.
 *
 * @NL80211_ATTR_STA_SUPPORTED_CHANNELS: array of supported channels.
 *
 * @NL80211_ATTR_STA_SUPPORTED_OPER_CLASSES: array of supported
 *      operating classes.
 *
 * @NL80211_ATTR_HANDLE_DFS: A flag indicating whether user space
 *	controls DFS operation in IBSS mode. If the flag is included in
 *	%NL80211_CMD_JOIN_IBSS request, the driver will allow use of DFS
 *	channels and reports radar events to userspace. Userspace is required
 *	to react to radar events, e.g. initiate a channel चयन or leave the
 *	IBSS network.
 *
 * @NL80211_ATTR_SUPPORT_5_MHZ: A flag indicating that the device supports
 *	5 MHz channel bandwidth.
 * @NL80211_ATTR_SUPPORT_10_MHZ: A flag indicating that the device supports
 *	10 MHz channel bandwidth.
 *
 * @NL80211_ATTR_OPMODE_NOTIF: Operating mode field from Operating Mode
 *	Notअगरication Element based on association request when used with
 *	%NL80211_CMD_NEW_STATION or %NL80211_CMD_SET_STATION (only when
 *	%NL80211_FEATURE_FULL_AP_CLIENT_STATE is supported, or with TDLS);
 *	u8 attribute.
 *
 * @NL80211_ATTR_VENDOR_ID: The venकरोr ID, either a 24-bit OUI or, अगर
 *	%NL80211_VENDOR_ID_IS_LINUX is set, a special Linux ID (not used yet)
 * @NL80211_ATTR_VENDOR_SUBCMD: venकरोr sub-command
 * @NL80211_ATTR_VENDOR_DATA: data क्रम the venकरोr command, अगर any; this
 *	attribute is also used क्रम venकरोr command feature advertisement
 * @NL80211_ATTR_VENDOR_EVENTS: used क्रम event list advertising in the wiphy
 *	info, containing a nested array of possible events
 *
 * @NL80211_ATTR_QOS_MAP: IP DSCP mapping क्रम Interworking QoS mapping. This
 *	data is in the क्रमmat defined क्रम the payload of the QoS Map Set element
 *	in IEEE Std 802.11-2012, 8.4.2.97.
 *
 * @NL80211_ATTR_MAC_HINT: MAC address recommendation as initial BSS
 * @NL80211_ATTR_WIPHY_FREQ_HINT: frequency of the recommended initial BSS
 *
 * @NL80211_ATTR_MAX_AP_ASSOC_STA: Device attribute that indicates how many
 *	associated stations are supported in AP mode (including P2P GO); u32.
 *	Since drivers may not have a fixed limit on the maximum number (e.g.,
 *	other concurrent operations may affect this), drivers are allowed to
 *	advertise values that cannot always be met. In such हालs, an attempt
 *	to add a new station entry with @NL80211_CMD_NEW_STATION may fail.
 *
 * @NL80211_ATTR_CSA_C_OFFSETS_TX: An array of csa counter offsets (u16) which
 *	should be updated when the frame is transmitted.
 * @NL80211_ATTR_MAX_CSA_COUNTERS: U8 attribute used to advertise the maximum
 *	supported number of csa counters.
 *
 * @NL80211_ATTR_TDLS_PEER_CAPABILITY: flags क्रम TDLS peer capabilities, u32.
 *	As specअगरied in the &क्रमागत nl80211_tdls_peer_capability.
 *
 * @NL80211_ATTR_SOCKET_OWNER: Flag attribute, अगर set during पूर्णांकerface
 *	creation then the new पूर्णांकerface will be owned by the netlink socket
 *	that created it and will be destroyed when the socket is बंदd.
 *	If set during scheduled scan start then the new scan req will be
 *	owned by the netlink socket that created it and the scheduled scan will
 *	be stopped when the socket is बंदd.
 *	If set during configuration of regulatory inकरोor operation then the
 *	regulatory inकरोor configuration would be owned by the netlink socket
 *	that configured the inकरोor setting, and the inकरोor operation would be
 *	cleared when the socket is बंदd.
 *	If set during न_अंक पूर्णांकerface creation, the पूर्णांकerface will be destroyed
 *	अगर the socket is बंदd just like any other पूर्णांकerface. Moreover, न_अंक
 *	notअगरications will be sent in unicast to that socket. Without this
 *	attribute, the notअगरications will be sent to the %NL80211_MCGRP_न_अंक
 *	multicast group.
 *	If set during %NL80211_CMD_ASSOCIATE or %NL80211_CMD_CONNECT the
 *	station will deauthenticate when the socket is बंदd.
 *	If set during %NL80211_CMD_JOIN_IBSS the IBSS will be स्वतःmatically
 *	torn करोwn when the socket is बंदd.
 *	If set during %NL80211_CMD_JOIN_MESH the mesh setup will be
 *	स्वतःmatically torn करोwn when the socket is बंदd.
 *	If set during %NL80211_CMD_START_AP the AP will be स्वतःmatically
 *	disabled when the socket is बंदd.
 *
 * @NL80211_ATTR_TDLS_INITIATOR: flag attribute indicating the current end is
 *	the TDLS link initiator.
 *
 * @NL80211_ATTR_USE_RRM: flag क्रम indicating whether the current connection
 *	shall support Radio Resource Measurements (11k). This attribute can be
 *	used with %NL80211_CMD_ASSOCIATE and %NL80211_CMD_CONNECT requests.
 *	User space applications are expected to use this flag only अगर the
 *	underlying device supports these minimal RRM features:
 *		%NL80211_FEATURE_DS_PARAM_SET_IE_IN_PROBES,
 *		%NL80211_FEATURE_QUIET,
 *	Or, अगर global RRM is supported, see:
 *		%NL80211_EXT_FEATURE_RRM
 *	If this flag is used, driver must add the Power Capabilities IE to the
 *	association request. In addition, it must also set the RRM capability
 *	flag in the association request's Capability Info field.
 *
 * @NL80211_ATTR_WIPHY_DYN_ACK: flag attribute used to enable ACK समयout
 *	estimation algorithm (dynack). In order to activate dynack
 *	%NL80211_FEATURE_ACKTO_ESTIMATION feature flag must be set by lower
 *	drivers to indicate dynack capability. Dynack is स्वतःmatically disabled
 *	setting valid value क्रम coverage class.
 *
 * @NL80211_ATTR_TSID: a TSID value (u8 attribute)
 * @NL80211_ATTR_USER_PRIO: user priority value (u8 attribute)
 * @NL80211_ATTR_ADMITTED_TIME: admitted समय in units of 32 microseconds
 *	(per second) (u16 attribute)
 *
 * @NL80211_ATTR_SMPS_MODE: SMPS mode to use (ap mode). see
 *	&क्रमागत nl80211_smps_mode.
 *
 * @NL80211_ATTR_OPER_CLASS: operating class
 *
 * @NL80211_ATTR_MAC_MASK: MAC address mask
 *
 * @NL80211_ATTR_WIPHY_SELF_MANAGED_REG: flag attribute indicating this device
 *	is self-managing its regulatory inक्रमmation and any regulatory करोमुख्य
 *	obtained from it is coming from the device's wiphy and not the global
 *	cfg80211 regकरोमुख्य.
 *
 * @NL80211_ATTR_EXT_FEATURES: extended feature flags contained in a byte
 *	array. The feature flags are identअगरied by their bit index (see &क्रमागत
 *	nl80211_ext_feature_index). The bit index is ordered starting at the
 *	least-signअगरicant bit of the first byte in the array, ie. bit index 0
 *	is located at bit 0 of byte 0. bit index 25 would be located at bit 1
 *	of byte 3 (u8 array).
 *
 * @NL80211_ATTR_SURVEY_RADIO_STATS: Request overall radio statistics to be
 *	वापसed aदीर्घ with other survey data. If set, @NL80211_CMD_GET_SURVEY
 *	may वापस a survey entry without a channel indicating global radio
 *	statistics (only some values are valid and make sense.)
 *	For devices that करोn't वापस such an entry even then, the inक्रमmation
 *	should be contained in the result as the sum of the respective counters
 *	over all channels.
 *
 * @NL80211_ATTR_SCHED_SCAN_DELAY: delay beक्रमe the first cycle of a
 *	scheduled scan is started.  Or the delay beक्रमe a WoWLAN
 *	net-detect scan is started, counting from the moment the
 *	प्रणाली is suspended.  This value is a u32, in seconds.

 * @NL80211_ATTR_REG_INDOOR: flag attribute, अगर set indicates that the device
 *      is operating in an inकरोor environment.
 *
 * @NL80211_ATTR_MAX_NUM_SCHED_SCAN_PLANS: maximum number of scan plans क्रम
 *	scheduled scan supported by the device (u32), a wiphy attribute.
 * @NL80211_ATTR_MAX_SCAN_PLAN_INTERVAL: maximum पूर्णांकerval (in seconds) क्रम
 *	a scan plan (u32), a wiphy attribute.
 * @NL80211_ATTR_MAX_SCAN_PLAN_ITERATIONS: maximum number of iterations in
 *	a scan plan (u32), a wiphy attribute.
 * @NL80211_ATTR_SCHED_SCAN_PLANS: a list of scan plans क्रम scheduled scan.
 *	Each scan plan defines the number of scan iterations and the पूर्णांकerval
 *	between scans. The last scan plan will always run infinitely,
 *	thus it must not specअगरy the number of iterations, only the पूर्णांकerval
 *	between scans. The scan plans are executed sequentially.
 *	Each scan plan is a nested attribute of &क्रमागत nl80211_sched_scan_plan.
 * @NL80211_ATTR_PBSS: flag attribute. If set it means operate
 *	in a PBSS. Specअगरied in %NL80211_CMD_CONNECT to request
 *	connecting to a PCP, and in %NL80211_CMD_START_AP to start
 *	a PCP instead of AP. Relevant क्रम DMG networks only.
 * @NL80211_ATTR_BSS_SELECT: nested attribute क्रम driver supporting the
 *	BSS selection feature. When used with %NL80211_CMD_GET_WIPHY it contains
 *	attributes according &क्रमागत nl80211_bss_select_attr to indicate what
 *	BSS selection behaviours are supported. When used with %NL80211_CMD_CONNECT
 *	it contains the behaviour-specअगरic attribute containing the parameters क्रम
 *	BSS selection to be करोne by driver and/or firmware.
 *
 * @NL80211_ATTR_STA_SUPPORT_P2P_PS: whether P2P PS mechanism supported
 *	or not. u8, one of the values of &क्रमागत nl80211_sta_p2p_ps_status
 *
 * @NL80211_ATTR_PAD: attribute used क्रम padding क्रम 64-bit alignment
 *
 * @NL80211_ATTR_IFTYPE_EXT_CAPA: Nested attribute of the following attributes:
 *	%NL80211_ATTR_IFTYPE, %NL80211_ATTR_EXT_CAPA,
 *	%NL80211_ATTR_EXT_CAPA_MASK, to specअगरy the extended capabilities per
 *	पूर्णांकerface type.
 *
 * @NL80211_ATTR_MU_MIMO_GROUP_DATA: array of 24 bytes that defines a MU-MIMO
 *	groupID क्रम monitor mode.
 *	The first 8 bytes are a mask that defines the membership in each
 *	group (there are 64 groups, group 0 and 63 are reserved),
 *	each bit represents a group and set to 1 क्रम being a member in
 *	that group and 0 क्रम not being a member.
 *	The reमुख्यing 16 bytes define the position in each group: 2 bits क्रम
 *	each group.
 *	(smaller group numbers represented on most signअगरicant bits and bigger
 *	group numbers on least signअगरicant bits.)
 *	This attribute is used only अगर all पूर्णांकerfaces are in monitor mode.
 *	Set this attribute in order to monitor packets using the given MU-MIMO
 *	groupID data.
 *	to turn off that feature set all the bits of the groupID to zero.
 * @NL80211_ATTR_MU_MIMO_FOLLOW_MAC_ADDR: mac address क्रम the snअगरfer to follow
 *	when using MU-MIMO air snअगरfer.
 *	to turn that feature off set an invalid mac address
 *	(e.g. FF:FF:FF:FF:FF:FF)
 *
 * @NL80211_ATTR_SCAN_START_TIME_TSF: The समय at which the scan was actually
 *	started (u64). The समय is the TSF of the BSS the पूर्णांकerface that
 *	requested the scan is connected to (अगर available, otherwise this
 *	attribute must not be included).
 * @NL80211_ATTR_SCAN_START_TIME_TSF_BSSID: The BSS according to which
 *	%NL80211_ATTR_SCAN_START_TIME_TSF is set.
 * @NL80211_ATTR_MEASUREMENT_DURATION: measurement duration in TUs (u16). If
 *	%NL80211_ATTR_MEASUREMENT_DURATION_MANDATORY is not set, this is the
 *	maximum measurement duration allowed. This attribute is used with
 *	measurement requests. It can also be used with %NL80211_CMD_TRIGGER_SCAN
 *	अगर the scan is used क्रम beacon report radio measurement.
 * @NL80211_ATTR_MEASUREMENT_DURATION_MANDATORY: flag attribute that indicates
 *	that the duration specअगरied with %NL80211_ATTR_MEASUREMENT_DURATION is
 *	mandatory. If this flag is not set, the duration is the maximum duration
 *	and the actual measurement duration may be लघुer.
 *
 * @NL80211_ATTR_MESH_PEER_AID: Association ID क्रम the mesh peer (u16). This is
 *	used to pull the stored data क्रम mesh peer in घातer save state.
 *
 * @NL80211_ATTR_न_अंक_MASTER_PREF: the master preference to be used by
 *	%NL80211_CMD_START_न_अंक and optionally with
 *	%NL80211_CMD_CHANGE_न_अंक_CONFIG. Its type is u8 and it can't be 0.
 *	Also, values 1 and 255 are reserved क्रम certअगरication purposes and
 *	should not be used during a normal device operation.
 * @NL80211_ATTR_BANDS: operating bands configuration.  This is a u32
 *	biपंचांगask of BIT(NL80211_BAND_*) as described in %क्रमागत
 *	nl80211_band.  For instance, क्रम NL80211_BAND_2GHZ, bit 0
 *	would be set.  This attribute is used with
 *	%NL80211_CMD_START_न_अंक and %NL80211_CMD_CHANGE_न_अंक_CONFIG, and
 *	it is optional.  If no bands are set, it means करोn't-care and
 *	the device will decide what to use.
 * @NL80211_ATTR_न_अंक_FUNC: a function that can be added to न_अंक. See
 *	&क्रमागत nl80211_nan_func_attributes क्रम description of this nested
 *	attribute.
 * @NL80211_ATTR_न_अंक_MATCH: used to report a match. This is a nested attribute.
 *	See &क्रमागत nl80211_nan_match_attributes.
 * @NL80211_ATTR_FILS_KEK: KEK क्रम FILS (Re)Association Request/Response frame
 *	protection.
 * @NL80211_ATTR_FILS_NONCES: Nonces (part of AAD) क्रम FILS (Re)Association
 *	Request/Response frame protection. This attribute contains the 16 octet
 *	STA Nonce followed by 16 octets of AP Nonce.
 *
 * @NL80211_ATTR_MULTICAST_TO_UNICAST_ENABLED: Indicates whether or not multicast
 *	packets should be send out as unicast to all stations (flag attribute).
 *
 * @NL80211_ATTR_BSSID: The BSSID of the AP. Note that %NL80211_ATTR_MAC is also
 *	used in various commands/events क्रम specअगरying the BSSID.
 *
 * @NL80211_ATTR_SCHED_SCAN_RELATIVE_RSSI: Relative RSSI threshold by which
 *	other BSSs has to be better or slightly worse than the current
 *	connected BSS so that they get reported to user space.
 *	This will give an opportunity to userspace to consider connecting to
 *	other matching BSSs which have better or slightly worse RSSI than
 *	the current connected BSS by using an offloaded operation to aव्योम
 *	unnecessary wakeups.
 *
 * @NL80211_ATTR_SCHED_SCAN_RSSI_ADJUST: When present the RSSI level क्रम BSSs in
 *	the specअगरied band is to be adjusted beक्रमe करोing
 *	%NL80211_ATTR_SCHED_SCAN_RELATIVE_RSSI based comparison to figure out
 *	better BSSs. The attribute value is a packed काष्ठाure
 *	value as specअगरied by &काष्ठा nl80211_bss_select_rssi_adjust.
 *
 * @NL80211_ATTR_TIMEOUT_REASON: The reason क्रम which an operation समयd out.
 *	u32 attribute with an &क्रमागत nl80211_समयout_reason value. This is used,
 *	e.g., with %NL80211_CMD_CONNECT event.
 *
 * @NL80211_ATTR_FILS_ERP_USERNAME: EAP Re-authentication Protocol (ERP)
 *	username part of NAI used to refer keys rRK and rIK. This is used with
 *	%NL80211_CMD_CONNECT.
 *
 * @NL80211_ATTR_FILS_ERP_REALM: EAP Re-authentication Protocol (ERP) realm part
 *	of NAI specअगरying the करोमुख्य name of the ER server. This is used with
 *	%NL80211_CMD_CONNECT.
 *
 * @NL80211_ATTR_FILS_ERP_NEXT_SEQ_NUM: Unचिन्हित 16-bit ERP next sequence number
 *	to use in ERP messages. This is used in generating the FILS wrapped data
 *	क्रम FILS authentication and is used with %NL80211_CMD_CONNECT.
 *
 * @NL80211_ATTR_FILS_ERP_RRK: ERP re-authentication Root Key (rRK) क्रम the
 *	NAI specअगरied by %NL80211_ATTR_FILS_ERP_USERNAME and
 *	%NL80211_ATTR_FILS_ERP_REALM. This is used क्रम generating rIK and rMSK
 *	from successful FILS authentication and is used with
 *	%NL80211_CMD_CONNECT.
 *
 * @NL80211_ATTR_FILS_CACHE_ID: A 2-octet identअगरier advertized by a FILS AP
 *	identअगरying the scope of PMKSAs. This is used with
 *	@NL80211_CMD_SET_PMKSA and @NL80211_CMD_DEL_PMKSA.
 *
 * @NL80211_ATTR_PMK: attribute क्रम passing PMK key material. Used with
 *	%NL80211_CMD_SET_PMKSA क्रम the PMKSA identअगरied by %NL80211_ATTR_PMKID.
 *	For %NL80211_CMD_CONNECT and %NL80211_CMD_START_AP it is used to provide
 *	PSK क्रम offloading 4-way handshake क्रम WPA/WPA2-PSK networks. For 802.1X
 *	authentication it is used with %NL80211_CMD_SET_PMK. For offloaded FT
 *	support this attribute specअगरies the PMK-R0 अगर NL80211_ATTR_PMKR0_NAME
 *	is included as well.
 *
 * @NL80211_ATTR_SCHED_SCAN_MULTI: flag attribute which user-space shall use to
 *	indicate that it supports multiple active scheduled scan requests.
 * @NL80211_ATTR_SCHED_SCAN_MAX_REQS: indicates maximum number of scheduled
 *	scan request that may be active क्रम the device (u32).
 *
 * @NL80211_ATTR_WANT_1X_4WAY_HS: flag attribute which user-space can include
 *	in %NL80211_CMD_CONNECT to indicate that क्रम 802.1X authentication it
 *	wants to use the supported offload of the 4-way handshake.
 * @NL80211_ATTR_PMKR0_NAME: PMK-R0 Name क्रम offloaded FT.
 * @NL80211_ATTR_PORT_AUTHORIZED: (reserved)
 *
 * @NL80211_ATTR_EXTERNAL_AUTH_ACTION: Identअगरy the requested बाह्यal
 *     authentication operation (u32 attribute with an
 *     &क्रमागत nl80211_बाह्यal_auth_action value). This is used with the
 *     %NL80211_CMD_EXTERNAL_AUTH request event.
 * @NL80211_ATTR_EXTERNAL_AUTH_SUPPORT: Flag attribute indicating that the user
 *	space supports बाह्यal authentication. This attribute shall be used
 *	with %NL80211_CMD_CONNECT and %NL80211_CMD_START_AP request. The driver
 *	may offload authentication processing to user space अगर this capability
 *	is indicated in the respective requests from the user space.
 *
 * @NL80211_ATTR_NSS: Station's New/updated  RX_NSS value notअगरied using this
 *	u8 attribute. This is used with %NL80211_CMD_STA_OPMODE_CHANGED.
 *
 * @NL80211_ATTR_TXQ_STATS: TXQ statistics (nested attribute, see &क्रमागत
 *      nl80211_txq_stats)
 * @NL80211_ATTR_TXQ_LIMIT: Total packet limit क्रम the TXQ queues क्रम this phy.
 *      The smaller of this and the memory limit is enक्रमced.
 * @NL80211_ATTR_TXQ_MEMORY_LIMIT: Total memory limit (in bytes) क्रम the
 *      TXQ queues क्रम this phy. The smaller of this and the packet limit is
 *      enक्रमced.
 * @NL80211_ATTR_TXQ_QUANTUM: TXQ scheduler quantum (bytes). Number of bytes
 *      a flow is asचिन्हित on each round of the DRR scheduler.
 * @NL80211_ATTR_HE_CAPABILITY: HE Capability inक्रमmation element (from
 *	association request when used with NL80211_CMD_NEW_STATION). Can be set
 *	only अगर %NL80211_STA_FLAG_WME is set.
 *
 * @NL80211_ATTR_FTM_RESPONDER: nested attribute which user-space can include
 *	in %NL80211_CMD_START_AP or %NL80211_CMD_SET_BEACON क्रम fine timing
 *	measurement (FTM) responder functionality and containing parameters as
 *	possible, see &क्रमागत nl80211_fपंचांग_responder_attr
 *
 * @NL80211_ATTR_FTM_RESPONDER_STATS: Nested attribute with FTM responder
 *	statistics, see &क्रमागत nl80211_fपंचांग_responder_stats.
 *
 * @NL80211_ATTR_TIMEOUT: Timeout क्रम the given operation in milliseconds (u32),
 *	अगर the attribute is not given no समयout is requested. Note that 0 is an
 *	invalid value.
 *
 * @NL80211_ATTR_PEER_MEASUREMENTS: peer measurements request (and result)
 *	data, uses nested attributes specअगरied in
 *	&क्रमागत nl80211_peer_measurement_attrs.
 *	This is also used क्रम capability advertisement in the wiphy inक्रमmation,
 *	with the appropriate sub-attributes.
 *
 * @NL80211_ATTR_AIRTIME_WEIGHT: Station's weight when scheduled by the airसमय
 *	scheduler.
 *
 * @NL80211_ATTR_STA_TX_POWER_SETTING: Transmit घातer setting type (u8) क्रम
 *	station associated with the AP. See &क्रमागत nl80211_tx_घातer_setting क्रम
 *	possible values.
 * @NL80211_ATTR_STA_TX_POWER: Transmit घातer level (s16) in dBm units. This
 *	allows to set Tx घातer क्रम a station. If this attribute is not included,
 *	the शेष per-पूर्णांकerface tx घातer setting will be overriding. Driver
 *	should be picking up the lowest tx घातer, either tx घातer per-पूर्णांकerface
 *	or per-station.
 *
 * @NL80211_ATTR_SAE_PASSWORD: attribute क्रम passing SAE password material. It
 *	is used with %NL80211_CMD_CONNECT to provide password क्रम offloading
 *	SAE authentication क्रम WPA3-Personal networks.
 *
 * @NL80211_ATTR_TWT_RESPONDER: Enable target रुको समय responder support.
 *
 * @NL80211_ATTR_HE_OBSS_PD: nested attribute क्रम OBSS Packet Detection
 *	functionality.
 *
 * @NL80211_ATTR_WIPHY_EDMG_CHANNELS: biपंचांगap that indicates the 2.16 GHz
 *	channel(s) that are allowed to be used क्रम EDMG transmissions.
 *	Defined by IEEE P802.11ay/D4.0 section 9.4.2.251. (u8 attribute)
 * @NL80211_ATTR_WIPHY_EDMG_BW_CONFIG: Channel BW Configuration subfield encodes
 *	the allowed channel bandwidth configurations. (u8 attribute)
 *	Defined by IEEE P802.11ay/D4.0 section 9.4.2.251, Table 13.
 *
 * @NL80211_ATTR_VLAN_ID: VLAN ID (1..4094) क्रम the station and VLAN group key
 *	(u16).
 *
 * @NL80211_ATTR_HE_BSS_COLOR: nested attribute क्रम BSS Color Settings.
 *
 * @NL80211_ATTR_IFTYPE_AKM_SUITES: nested array attribute, with each entry
 *	using attributes from &क्रमागत nl80211_अगरtype_akm_attributes. This
 *	attribute is sent in a response to %NL80211_CMD_GET_WIPHY indicating
 *	supported AKM suites capability per पूर्णांकerface. AKMs advertised in
 *	%NL80211_ATTR_AKM_SUITES are शेष capabilities अगर AKM suites not
 *	advertised क्रम a specअगरic पूर्णांकerface type.
 *
 * @NL80211_ATTR_TID_CONFIG: TID specअगरic configuration in a
 *	nested attribute with &क्रमागत nl80211_tid_config_attr sub-attributes;
 *	on output (in wiphy attributes) it contains only the feature sub-
 *	attributes.
 *
 * @NL80211_ATTR_CONTROL_PORT_NO_PREAUTH: disable preauth frame rx on control
 *	port in order to क्रमward/receive them as ordinary data frames.
 *
 * @NL80211_ATTR_PMK_LIFETIME: Maximum lअगरeसमय क्रम PMKSA in seconds (u32,
 *	करोt11RSNAConfigPMKReauthThreshold; 0 is not a valid value).
 *	An optional parameter configured through %NL80211_CMD_SET_PMKSA.
 *	Drivers that trigger roaming need to know the lअगरeसमय of the
 *	configured PMKSA क्रम triggering the full vs. PMKSA caching based
 *	authentication. This समयout helps authentication methods like SAE,
 *	where PMK माला_लो updated only by going through a full (new SAE)
 *	authentication instead of getting updated during an association क्रम EAP
 *	authentication. No new full authentication within the PMK expiry shall
 *	result in a disassociation at the end of the lअगरeसमय.
 *
 * @NL80211_ATTR_PMK_REAUTH_THRESHOLD: Reauthentication threshold समय, in
 *	terms of percentage of %NL80211_ATTR_PMK_LIFETIME
 *	(u8, करोt11RSNAConfigPMKReauthThreshold, 1..100). This is an optional
 *	parameter configured through %NL80211_CMD_SET_PMKSA. Requests the
 *	driver to trigger a full authentication roam (without PMKSA caching)
 *	after the reauthentication threshold समय, but beक्रमe the PMK lअगरeसमय
 *	has expired.
 *
 *	Authentication methods like SAE need to be able to generate a new PMKSA
 *	entry without having to क्रमce a disconnection after the PMK समयout. If
 *	no roaming occurs between the reauth threshold and PMK expiration,
 *	disassociation is still क्रमced.
 * @NL80211_ATTR_RECEIVE_MULTICAST: multicast flag क्रम the
 *	%NL80211_CMD_REGISTER_FRAME command, see the description there.
 * @NL80211_ATTR_WIPHY_FREQ_OFFSET: offset of the associated
 *	%NL80211_ATTR_WIPHY_FREQ in positive KHz. Only valid when supplied with
 *	an %NL80211_ATTR_WIPHY_FREQ_OFFSET.
 * @NL80211_ATTR_CENTER_FREQ1_OFFSET: Center frequency offset in KHz क्रम the
 *	first channel segment specअगरied in %NL80211_ATTR_CENTER_FREQ1.
 * @NL80211_ATTR_SCAN_FREQ_KHZ: nested attribute with KHz frequencies
 *
 * @NL80211_ATTR_HE_6GHZ_CAPABILITY: HE 6 GHz Band Capability element (from
 *	association request when used with NL80211_CMD_NEW_STATION).
 *
 * @NL80211_ATTR_FILS_DISCOVERY: Optional parameter to configure FILS
 *	discovery. It is a nested attribute, see
 *	&क्रमागत nl80211_fils_discovery_attributes.
 *
 * @NL80211_ATTR_UNSOL_BCAST_PROBE_RESP: Optional parameter to configure
 *	unsolicited broadcast probe response. It is a nested attribute, see
 *	&क्रमागत nl80211_unsol_bcast_probe_resp_attributes.
 *
 * @NL80211_ATTR_S1G_CAPABILITY: S1G Capability inक्रमmation element (from
 *	association request when used with NL80211_CMD_NEW_STATION)
 * @NL80211_ATTR_S1G_CAPABILITY_MASK: S1G Capability Inक्रमmation element
 *	override mask. Used with NL80211_ATTR_S1G_CAPABILITY in
 *	NL80211_CMD_ASSOCIATE or NL80211_CMD_CONNECT.
 *
 * @NL80211_ATTR_SAE_PWE: Indicates the mechanism(s) allowed क्रम SAE PWE
 *	derivation in WPA3-Personal networks which are using SAE authentication.
 *	This is a u8 attribute that encapsulates one of the values from
 *	&क्रमागत nl80211_sae_pwe_mechanism.
 *
 * @NL80211_ATTR_SAR_SPEC: SAR घातer limitation specअगरication when
 *	used with %NL80211_CMD_SET_SAR_SPECS. The message contains fields
 *	of %nl80211_sar_attrs which specअगरies the sar type and related
 *	sar specs. Sar specs contains array of %nl80211_sar_specs_attrs.
 *
 * @NL80211_ATTR_RECONNECT_REQUESTED: flag attribute, used with deauth and
 *	disassoc events to indicate that an immediate reconnect to the AP
 *	is desired.
 *
 * @NUM_NL80211_ATTR: total number of nl80211_attrs available
 * @NL80211_ATTR_MAX: highest attribute number currently defined
 * @__NL80211_ATTR_AFTER_LAST: पूर्णांकernal use
 */
क्रमागत nl80211_attrs अणु
/* करोn't change the order or add anything between, this is ABI! */
	NL80211_ATTR_UNSPEC,

	NL80211_ATTR_WIPHY,
	NL80211_ATTR_WIPHY_NAME,

	NL80211_ATTR_IFINDEX,
	NL80211_ATTR_IFNAME,
	NL80211_ATTR_IFTYPE,

	NL80211_ATTR_MAC,

	NL80211_ATTR_KEY_DATA,
	NL80211_ATTR_KEY_IDX,
	NL80211_ATTR_KEY_CIPHER,
	NL80211_ATTR_KEY_SEQ,
	NL80211_ATTR_KEY_DEFAULT,

	NL80211_ATTR_BEACON_INTERVAL,
	NL80211_ATTR_DTIM_PERIOD,
	NL80211_ATTR_BEACON_HEAD,
	NL80211_ATTR_BEACON_TAIL,

	NL80211_ATTR_STA_AID,
	NL80211_ATTR_STA_FLAGS,
	NL80211_ATTR_STA_LISTEN_INTERVAL,
	NL80211_ATTR_STA_SUPPORTED_RATES,
	NL80211_ATTR_STA_VLAN,
	NL80211_ATTR_STA_INFO,

	NL80211_ATTR_WIPHY_BANDS,

	NL80211_ATTR_MNTR_FLAGS,

	NL80211_ATTR_MESH_ID,
	NL80211_ATTR_STA_PLINK_ACTION,
	NL80211_ATTR_MPATH_NEXT_HOP,
	NL80211_ATTR_MPATH_INFO,

	NL80211_ATTR_BSS_CTS_PROT,
	NL80211_ATTR_BSS_SHORT_PREAMBLE,
	NL80211_ATTR_BSS_SHORT_SLOT_TIME,

	NL80211_ATTR_HT_CAPABILITY,

	NL80211_ATTR_SUPPORTED_IFTYPES,

	NL80211_ATTR_REG_ALPHA2,
	NL80211_ATTR_REG_RULES,

	NL80211_ATTR_MESH_CONFIG,

	NL80211_ATTR_BSS_BASIC_RATES,

	NL80211_ATTR_WIPHY_TXQ_PARAMS,
	NL80211_ATTR_WIPHY_FREQ,
	NL80211_ATTR_WIPHY_CHANNEL_TYPE,

	NL80211_ATTR_KEY_DEFAULT_MGMT,

	NL80211_ATTR_MGMT_SUBTYPE,
	NL80211_ATTR_IE,

	NL80211_ATTR_MAX_NUM_SCAN_SSIDS,

	NL80211_ATTR_SCAN_FREQUENCIES,
	NL80211_ATTR_SCAN_SSIDS,
	NL80211_ATTR_GENERATION, /* replaces old SCAN_GENERATION */
	NL80211_ATTR_BSS,

	NL80211_ATTR_REG_INITIATOR,
	NL80211_ATTR_REG_TYPE,

	NL80211_ATTR_SUPPORTED_COMMANDS,

	NL80211_ATTR_FRAME,
	NL80211_ATTR_SSID,
	NL80211_ATTR_AUTH_TYPE,
	NL80211_ATTR_REASON_CODE,

	NL80211_ATTR_KEY_TYPE,

	NL80211_ATTR_MAX_SCAN_IE_LEN,
	NL80211_ATTR_CIPHER_SUITES,

	NL80211_ATTR_FREQ_BEFORE,
	NL80211_ATTR_FREQ_AFTER,

	NL80211_ATTR_FREQ_FIXED,


	NL80211_ATTR_WIPHY_RETRY_SHORT,
	NL80211_ATTR_WIPHY_RETRY_LONG,
	NL80211_ATTR_WIPHY_FRAG_THRESHOLD,
	NL80211_ATTR_WIPHY_RTS_THRESHOLD,

	NL80211_ATTR_TIMED_OUT,

	NL80211_ATTR_USE_MFP,

	NL80211_ATTR_STA_FLAGS2,

	NL80211_ATTR_CONTROL_PORT,

	NL80211_ATTR_TESTDATA,

	NL80211_ATTR_PRIVACY,

	NL80211_ATTR_DISCONNECTED_BY_AP,
	NL80211_ATTR_STATUS_CODE,

	NL80211_ATTR_CIPHER_SUITES_PAIRWISE,
	NL80211_ATTR_CIPHER_SUITE_GROUP,
	NL80211_ATTR_WPA_VERSIONS,
	NL80211_ATTR_AKM_SUITES,

	NL80211_ATTR_REQ_IE,
	NL80211_ATTR_RESP_IE,

	NL80211_ATTR_PREV_BSSID,

	NL80211_ATTR_KEY,
	NL80211_ATTR_KEYS,

	NL80211_ATTR_PID,

	NL80211_ATTR_4ADDR,

	NL80211_ATTR_SURVEY_INFO,

	NL80211_ATTR_PMKID,
	NL80211_ATTR_MAX_NUM_PMKIDS,

	NL80211_ATTR_DURATION,

	NL80211_ATTR_COOKIE,

	NL80211_ATTR_WIPHY_COVERAGE_CLASS,

	NL80211_ATTR_TX_RATES,

	NL80211_ATTR_FRAME_MATCH,

	NL80211_ATTR_ACK,

	NL80211_ATTR_PS_STATE,

	NL80211_ATTR_CQM,

	NL80211_ATTR_LOCAL_STATE_CHANGE,

	NL80211_ATTR_AP_ISOLATE,

	NL80211_ATTR_WIPHY_TX_POWER_SETTING,
	NL80211_ATTR_WIPHY_TX_POWER_LEVEL,

	NL80211_ATTR_TX_FRAME_TYPES,
	NL80211_ATTR_RX_FRAME_TYPES,
	NL80211_ATTR_FRAME_TYPE,

	NL80211_ATTR_CONTROL_PORT_ETHERTYPE,
	NL80211_ATTR_CONTROL_PORT_NO_ENCRYPT,

	NL80211_ATTR_SUPPORT_IBSS_RSN,

	NL80211_ATTR_WIPHY_ANTENNA_TX,
	NL80211_ATTR_WIPHY_ANTENNA_RX,

	NL80211_ATTR_MCAST_RATE,

	NL80211_ATTR_OFFCHANNEL_TX_OK,

	NL80211_ATTR_BSS_HT_OPMODE,

	NL80211_ATTR_KEY_DEFAULT_TYPES,

	NL80211_ATTR_MAX_REMAIN_ON_CHANNEL_DURATION,

	NL80211_ATTR_MESH_SETUP,

	NL80211_ATTR_WIPHY_ANTENNA_AVAIL_TX,
	NL80211_ATTR_WIPHY_ANTENNA_AVAIL_RX,

	NL80211_ATTR_SUPPORT_MESH_AUTH,
	NL80211_ATTR_STA_PLINK_STATE,

	NL80211_ATTR_WOWLAN_TRIGGERS,
	NL80211_ATTR_WOWLAN_TRIGGERS_SUPPORTED,

	NL80211_ATTR_SCHED_SCAN_INTERVAL,

	NL80211_ATTR_INTERFACE_COMBINATIONS,
	NL80211_ATTR_SOFTWARE_IFTYPES,

	NL80211_ATTR_REKEY_DATA,

	NL80211_ATTR_MAX_NUM_SCHED_SCAN_SSIDS,
	NL80211_ATTR_MAX_SCHED_SCAN_IE_LEN,

	NL80211_ATTR_SCAN_SUPP_RATES,

	NL80211_ATTR_HIDDEN_SSID,

	NL80211_ATTR_IE_PROBE_RESP,
	NL80211_ATTR_IE_ASSOC_RESP,

	NL80211_ATTR_STA_WME,
	NL80211_ATTR_SUPPORT_AP_UAPSD,

	NL80211_ATTR_ROAM_SUPPORT,

	NL80211_ATTR_SCHED_SCAN_MATCH,
	NL80211_ATTR_MAX_MATCH_SETS,

	NL80211_ATTR_PMKSA_CANDIDATE,

	NL80211_ATTR_TX_NO_CCK_RATE,

	NL80211_ATTR_TDLS_ACTION,
	NL80211_ATTR_TDLS_DIALOG_TOKEN,
	NL80211_ATTR_TDLS_OPERATION,
	NL80211_ATTR_TDLS_SUPPORT,
	NL80211_ATTR_TDLS_EXTERNAL_SETUP,

	NL80211_ATTR_DEVICE_AP_SME,

	NL80211_ATTR_DONT_WAIT_FOR_ACK,

	NL80211_ATTR_FEATURE_FLAGS,

	NL80211_ATTR_PROBE_RESP_OFFLOAD,

	NL80211_ATTR_PROBE_RESP,

	NL80211_ATTR_DFS_REGION,

	NL80211_ATTR_DISABLE_HT,
	NL80211_ATTR_HT_CAPABILITY_MASK,

	NL80211_ATTR_NOACK_MAP,

	NL80211_ATTR_INACTIVITY_TIMEOUT,

	NL80211_ATTR_RX_SIGNAL_DBM,

	NL80211_ATTR_BG_SCAN_PERIOD,

	NL80211_ATTR_WDEV,

	NL80211_ATTR_USER_REG_HINT_TYPE,

	NL80211_ATTR_CONN_FAILED_REASON,

	NL80211_ATTR_AUTH_DATA,

	NL80211_ATTR_VHT_CAPABILITY,

	NL80211_ATTR_SCAN_FLAGS,

	NL80211_ATTR_CHANNEL_WIDTH,
	NL80211_ATTR_CENTER_FREQ1,
	NL80211_ATTR_CENTER_FREQ2,

	NL80211_ATTR_P2P_CTWINDOW,
	NL80211_ATTR_P2P_OPPPS,

	NL80211_ATTR_LOCAL_MESH_POWER_MODE,

	NL80211_ATTR_ACL_POLICY,

	NL80211_ATTR_MAC_ADDRS,

	NL80211_ATTR_MAC_ACL_MAX,

	NL80211_ATTR_RADAR_EVENT,

	NL80211_ATTR_EXT_CAPA,
	NL80211_ATTR_EXT_CAPA_MASK,

	NL80211_ATTR_STA_CAPABILITY,
	NL80211_ATTR_STA_EXT_CAPABILITY,

	NL80211_ATTR_PROTOCOL_FEATURES,
	NL80211_ATTR_SPLIT_WIPHY_DUMP,

	NL80211_ATTR_DISABLE_VHT,
	NL80211_ATTR_VHT_CAPABILITY_MASK,

	NL80211_ATTR_MDID,
	NL80211_ATTR_IE_RIC,

	NL80211_ATTR_CRIT_PROT_ID,
	NL80211_ATTR_MAX_CRIT_PROT_DURATION,

	NL80211_ATTR_PEER_AID,

	NL80211_ATTR_COALESCE_RULE,

	NL80211_ATTR_CH_SWITCH_COUNT,
	NL80211_ATTR_CH_SWITCH_BLOCK_TX,
	NL80211_ATTR_CSA_IES,
	NL80211_ATTR_CNTDWN_OFFS_BEACON,
	NL80211_ATTR_CNTDWN_OFFS_PRESP,

	NL80211_ATTR_RXMGMT_FLAGS,

	NL80211_ATTR_STA_SUPPORTED_CHANNELS,

	NL80211_ATTR_STA_SUPPORTED_OPER_CLASSES,

	NL80211_ATTR_HANDLE_DFS,

	NL80211_ATTR_SUPPORT_5_MHZ,
	NL80211_ATTR_SUPPORT_10_MHZ,

	NL80211_ATTR_OPMODE_NOTIF,

	NL80211_ATTR_VENDOR_ID,
	NL80211_ATTR_VENDOR_SUBCMD,
	NL80211_ATTR_VENDOR_DATA,
	NL80211_ATTR_VENDOR_EVENTS,

	NL80211_ATTR_QOS_MAP,

	NL80211_ATTR_MAC_HINT,
	NL80211_ATTR_WIPHY_FREQ_HINT,

	NL80211_ATTR_MAX_AP_ASSOC_STA,

	NL80211_ATTR_TDLS_PEER_CAPABILITY,

	NL80211_ATTR_SOCKET_OWNER,

	NL80211_ATTR_CSA_C_OFFSETS_TX,
	NL80211_ATTR_MAX_CSA_COUNTERS,

	NL80211_ATTR_TDLS_INITIATOR,

	NL80211_ATTR_USE_RRM,

	NL80211_ATTR_WIPHY_DYN_ACK,

	NL80211_ATTR_TSID,
	NL80211_ATTR_USER_PRIO,
	NL80211_ATTR_ADMITTED_TIME,

	NL80211_ATTR_SMPS_MODE,

	NL80211_ATTR_OPER_CLASS,

	NL80211_ATTR_MAC_MASK,

	NL80211_ATTR_WIPHY_SELF_MANAGED_REG,

	NL80211_ATTR_EXT_FEATURES,

	NL80211_ATTR_SURVEY_RADIO_STATS,

	NL80211_ATTR_NETNS_FD,

	NL80211_ATTR_SCHED_SCAN_DELAY,

	NL80211_ATTR_REG_INDOOR,

	NL80211_ATTR_MAX_NUM_SCHED_SCAN_PLANS,
	NL80211_ATTR_MAX_SCAN_PLAN_INTERVAL,
	NL80211_ATTR_MAX_SCAN_PLAN_ITERATIONS,
	NL80211_ATTR_SCHED_SCAN_PLANS,

	NL80211_ATTR_PBSS,

	NL80211_ATTR_BSS_SELECT,

	NL80211_ATTR_STA_SUPPORT_P2P_PS,

	NL80211_ATTR_PAD,

	NL80211_ATTR_IFTYPE_EXT_CAPA,

	NL80211_ATTR_MU_MIMO_GROUP_DATA,
	NL80211_ATTR_MU_MIMO_FOLLOW_MAC_ADDR,

	NL80211_ATTR_SCAN_START_TIME_TSF,
	NL80211_ATTR_SCAN_START_TIME_TSF_BSSID,
	NL80211_ATTR_MEASUREMENT_DURATION,
	NL80211_ATTR_MEASUREMENT_DURATION_MANDATORY,

	NL80211_ATTR_MESH_PEER_AID,

	NL80211_ATTR_न_अंक_MASTER_PREF,
	NL80211_ATTR_BANDS,
	NL80211_ATTR_न_अंक_FUNC,
	NL80211_ATTR_न_अंक_MATCH,

	NL80211_ATTR_FILS_KEK,
	NL80211_ATTR_FILS_NONCES,

	NL80211_ATTR_MULTICAST_TO_UNICAST_ENABLED,

	NL80211_ATTR_BSSID,

	NL80211_ATTR_SCHED_SCAN_RELATIVE_RSSI,
	NL80211_ATTR_SCHED_SCAN_RSSI_ADJUST,

	NL80211_ATTR_TIMEOUT_REASON,

	NL80211_ATTR_FILS_ERP_USERNAME,
	NL80211_ATTR_FILS_ERP_REALM,
	NL80211_ATTR_FILS_ERP_NEXT_SEQ_NUM,
	NL80211_ATTR_FILS_ERP_RRK,
	NL80211_ATTR_FILS_CACHE_ID,

	NL80211_ATTR_PMK,

	NL80211_ATTR_SCHED_SCAN_MULTI,
	NL80211_ATTR_SCHED_SCAN_MAX_REQS,

	NL80211_ATTR_WANT_1X_4WAY_HS,
	NL80211_ATTR_PMKR0_NAME,
	NL80211_ATTR_PORT_AUTHORIZED,

	NL80211_ATTR_EXTERNAL_AUTH_ACTION,
	NL80211_ATTR_EXTERNAL_AUTH_SUPPORT,

	NL80211_ATTR_NSS,
	NL80211_ATTR_ACK_SIGNAL,

	NL80211_ATTR_CONTROL_PORT_OVER_NL80211,

	NL80211_ATTR_TXQ_STATS,
	NL80211_ATTR_TXQ_LIMIT,
	NL80211_ATTR_TXQ_MEMORY_LIMIT,
	NL80211_ATTR_TXQ_QUANTUM,

	NL80211_ATTR_HE_CAPABILITY,

	NL80211_ATTR_FTM_RESPONDER,

	NL80211_ATTR_FTM_RESPONDER_STATS,

	NL80211_ATTR_TIMEOUT,

	NL80211_ATTR_PEER_MEASUREMENTS,

	NL80211_ATTR_AIRTIME_WEIGHT,
	NL80211_ATTR_STA_TX_POWER_SETTING,
	NL80211_ATTR_STA_TX_POWER,

	NL80211_ATTR_SAE_PASSWORD,

	NL80211_ATTR_TWT_RESPONDER,

	NL80211_ATTR_HE_OBSS_PD,

	NL80211_ATTR_WIPHY_EDMG_CHANNELS,
	NL80211_ATTR_WIPHY_EDMG_BW_CONFIG,

	NL80211_ATTR_VLAN_ID,

	NL80211_ATTR_HE_BSS_COLOR,

	NL80211_ATTR_IFTYPE_AKM_SUITES,

	NL80211_ATTR_TID_CONFIG,

	NL80211_ATTR_CONTROL_PORT_NO_PREAUTH,

	NL80211_ATTR_PMK_LIFETIME,
	NL80211_ATTR_PMK_REAUTH_THRESHOLD,

	NL80211_ATTR_RECEIVE_MULTICAST,
	NL80211_ATTR_WIPHY_FREQ_OFFSET,
	NL80211_ATTR_CENTER_FREQ1_OFFSET,
	NL80211_ATTR_SCAN_FREQ_KHZ,

	NL80211_ATTR_HE_6GHZ_CAPABILITY,

	NL80211_ATTR_FILS_DISCOVERY,

	NL80211_ATTR_UNSOL_BCAST_PROBE_RESP,

	NL80211_ATTR_S1G_CAPABILITY,
	NL80211_ATTR_S1G_CAPABILITY_MASK,

	NL80211_ATTR_SAE_PWE,

	NL80211_ATTR_RECONNECT_REQUESTED,

	NL80211_ATTR_SAR_SPEC,

	NL80211_ATTR_DISABLE_HE,

	/* add attributes here, update the policy in nl80211.c */

	__NL80211_ATTR_AFTER_LAST,
	NUM_NL80211_ATTR = __NL80211_ATTR_AFTER_LAST,
	NL80211_ATTR_MAX = __NL80211_ATTR_AFTER_LAST - 1
पूर्ण;

/* source-level API compatibility */
#घोषणा NL80211_ATTR_SCAN_GENERATION NL80211_ATTR_GENERATION
#घोषणा	NL80211_ATTR_MESH_PARAMS NL80211_ATTR_MESH_CONFIG
#घोषणा NL80211_ATTR_IFACE_SOCKET_OWNER NL80211_ATTR_SOCKET_OWNER
#घोषणा NL80211_ATTR_SAE_DATA NL80211_ATTR_AUTH_DATA
#घोषणा NL80211_ATTR_CSA_C_OFF_BEACON NL80211_ATTR_CNTDWN_OFFS_BEACON
#घोषणा NL80211_ATTR_CSA_C_OFF_PRESP NL80211_ATTR_CNTDWN_OFFS_PRESP

/*
 * Allow user space programs to use #अगर_घोषित on new attributes by defining them
 * here
 */
#घोषणा NL80211_CMD_CONNECT NL80211_CMD_CONNECT
#घोषणा NL80211_ATTR_HT_CAPABILITY NL80211_ATTR_HT_CAPABILITY
#घोषणा NL80211_ATTR_BSS_BASIC_RATES NL80211_ATTR_BSS_BASIC_RATES
#घोषणा NL80211_ATTR_WIPHY_TXQ_PARAMS NL80211_ATTR_WIPHY_TXQ_PARAMS
#घोषणा NL80211_ATTR_WIPHY_FREQ NL80211_ATTR_WIPHY_FREQ
#घोषणा NL80211_ATTR_WIPHY_CHANNEL_TYPE NL80211_ATTR_WIPHY_CHANNEL_TYPE
#घोषणा NL80211_ATTR_MGMT_SUBTYPE NL80211_ATTR_MGMT_SUBTYPE
#घोषणा NL80211_ATTR_IE NL80211_ATTR_IE
#घोषणा NL80211_ATTR_REG_INITIATOR NL80211_ATTR_REG_INITIATOR
#घोषणा NL80211_ATTR_REG_TYPE NL80211_ATTR_REG_TYPE
#घोषणा NL80211_ATTR_FRAME NL80211_ATTR_FRAME
#घोषणा NL80211_ATTR_SSID NL80211_ATTR_SSID
#घोषणा NL80211_ATTR_AUTH_TYPE NL80211_ATTR_AUTH_TYPE
#घोषणा NL80211_ATTR_REASON_CODE NL80211_ATTR_REASON_CODE
#घोषणा NL80211_ATTR_CIPHER_SUITES_PAIRWISE NL80211_ATTR_CIPHER_SUITES_PAIRWISE
#घोषणा NL80211_ATTR_CIPHER_SUITE_GROUP NL80211_ATTR_CIPHER_SUITE_GROUP
#घोषणा NL80211_ATTR_WPA_VERSIONS NL80211_ATTR_WPA_VERSIONS
#घोषणा NL80211_ATTR_AKM_SUITES NL80211_ATTR_AKM_SUITES
#घोषणा NL80211_ATTR_KEY NL80211_ATTR_KEY
#घोषणा NL80211_ATTR_KEYS NL80211_ATTR_KEYS
#घोषणा NL80211_ATTR_FEATURE_FLAGS NL80211_ATTR_FEATURE_FLAGS

#घोषणा NL80211_WIPHY_NAME_MAXLEN		64

#घोषणा NL80211_MAX_SUPP_RATES			32
#घोषणा NL80211_MAX_SUPP_HT_RATES		77
#घोषणा NL80211_MAX_SUPP_REG_RULES		128
#घोषणा NL80211_TKIP_DATA_OFFSET_ENCR_KEY	0
#घोषणा NL80211_TKIP_DATA_OFFSET_TX_MIC_KEY	16
#घोषणा NL80211_TKIP_DATA_OFFSET_RX_MIC_KEY	24
#घोषणा NL80211_HT_CAPABILITY_LEN		26
#घोषणा NL80211_VHT_CAPABILITY_LEN		12
#घोषणा NL80211_HE_MIN_CAPABILITY_LEN           16
#घोषणा NL80211_HE_MAX_CAPABILITY_LEN           54
#घोषणा NL80211_MAX_NR_CIPHER_SUITES		5
#घोषणा NL80211_MAX_NR_AKM_SUITES		2

#घोषणा NL80211_MIN_REMAIN_ON_CHANNEL_TIME	10

/* शेष RSSI threshold क्रम scan results अगर none specअगरied. */
#घोषणा NL80211_SCAN_RSSI_THOLD_OFF		-300

#घोषणा NL80211_CQM_TXE_MAX_INTVL		1800

/**
 * क्रमागत nl80211_अगरtype - (भव) पूर्णांकerface types
 *
 * @NL80211_IFTYPE_UNSPECIFIED: unspecअगरied type, driver decides
 * @NL80211_IFTYPE_ADHOC: independent BSS member
 * @NL80211_IFTYPE_STATION: managed BSS member
 * @NL80211_IFTYPE_AP: access poपूर्णांक
 * @NL80211_IFTYPE_AP_VLAN: VLAN पूर्णांकerface क्रम access poपूर्णांकs; VLAN पूर्णांकerfaces
 *	are a bit special in that they must always be tied to a pre-existing
 *	AP type पूर्णांकerface.
 * @NL80211_IFTYPE_WDS: wireless distribution पूर्णांकerface
 * @NL80211_IFTYPE_MONITOR: monitor पूर्णांकerface receiving all frames
 * @NL80211_IFTYPE_MESH_POINT: mesh poपूर्णांक
 * @NL80211_IFTYPE_P2P_CLIENT: P2P client
 * @NL80211_IFTYPE_P2P_GO: P2P group owner
 * @NL80211_IFTYPE_P2P_DEVICE: P2P device पूर्णांकerface type, this is not a netdev
 *	and thereक्रमe can't be created in the normal ways, use the
 *	%NL80211_CMD_START_P2P_DEVICE and %NL80211_CMD_STOP_P2P_DEVICE
 *	commands to create and destroy one
 * @NL80211_IF_TYPE_OCB: Outside Context of a BSS
 *	This mode corresponds to the MIB variable करोt11OCBActivated=true
 * @NL80211_IFTYPE_न_अंक: न_अंक device पूर्णांकerface type (not a netdev)
 * @NL80211_IFTYPE_MAX: highest पूर्णांकerface type number currently defined
 * @NUM_NL80211_IFTYPES: number of defined पूर्णांकerface types
 *
 * These values are used with the %NL80211_ATTR_IFTYPE
 * to set the type of an पूर्णांकerface.
 *
 */
क्रमागत nl80211_अगरtype अणु
	NL80211_IFTYPE_UNSPECIFIED,
	NL80211_IFTYPE_ADHOC,
	NL80211_IFTYPE_STATION,
	NL80211_IFTYPE_AP,
	NL80211_IFTYPE_AP_VLAN,
	NL80211_IFTYPE_WDS,
	NL80211_IFTYPE_MONITOR,
	NL80211_IFTYPE_MESH_POINT,
	NL80211_IFTYPE_P2P_CLIENT,
	NL80211_IFTYPE_P2P_GO,
	NL80211_IFTYPE_P2P_DEVICE,
	NL80211_IFTYPE_OCB,
	NL80211_IFTYPE_न_अंक,

	/* keep last */
	NUM_NL80211_IFTYPES,
	NL80211_IFTYPE_MAX = NUM_NL80211_IFTYPES - 1
पूर्ण;

/**
 * क्रमागत nl80211_sta_flags - station flags
 *
 * Station flags. When a station is added to an AP पूर्णांकerface, it is
 * assumed to be alपढ़ोy associated (and hence authenticated.)
 *
 * @__NL80211_STA_FLAG_INVALID: attribute number 0 is reserved
 * @NL80211_STA_FLAG_AUTHORIZED: station is authorized (802.1X)
 * @NL80211_STA_FLAG_SHORT_PREAMBLE: station is capable of receiving frames
 *	with लघु barker preamble
 * @NL80211_STA_FLAG_WME: station is WME/QoS capable
 * @NL80211_STA_FLAG_MFP: station uses management frame protection
 * @NL80211_STA_FLAG_AUTHENTICATED: station is authenticated
 * @NL80211_STA_FLAG_TDLS_PEER: station is a TDLS peer -- this flag should
 *	only be used in managed mode (even in the flags mask). Note that the
 *	flag can't be changed, it is only valid जबतक adding a station, and
 *	attempts to change it will silently be ignored (rather than rejected
 *	as errors.)
 * @NL80211_STA_FLAG_ASSOCIATED: station is associated; used with drivers
 *	that support %NL80211_FEATURE_FULL_AP_CLIENT_STATE to transition a
 *	previously added station पूर्णांकo associated state
 * @NL80211_STA_FLAG_MAX: highest station flag number currently defined
 * @__NL80211_STA_FLAG_AFTER_LAST: पूर्णांकernal use
 */
क्रमागत nl80211_sta_flags अणु
	__NL80211_STA_FLAG_INVALID,
	NL80211_STA_FLAG_AUTHORIZED,
	NL80211_STA_FLAG_SHORT_PREAMBLE,
	NL80211_STA_FLAG_WME,
	NL80211_STA_FLAG_MFP,
	NL80211_STA_FLAG_AUTHENTICATED,
	NL80211_STA_FLAG_TDLS_PEER,
	NL80211_STA_FLAG_ASSOCIATED,

	/* keep last */
	__NL80211_STA_FLAG_AFTER_LAST,
	NL80211_STA_FLAG_MAX = __NL80211_STA_FLAG_AFTER_LAST - 1
पूर्ण;

/**
 * क्रमागत nl80211_sta_p2p_ps_status - station support of P2P PS
 *
 * @NL80211_P2P_PS_UNSUPPORTED: station करोesn't support P2P PS mechanism
 * @@NL80211_P2P_PS_SUPPORTED: station supports P2P PS mechanism
 * @NUM_NL80211_P2P_PS_STATUS: number of values
 */
क्रमागत nl80211_sta_p2p_ps_status अणु
	NL80211_P2P_PS_UNSUPPORTED = 0,
	NL80211_P2P_PS_SUPPORTED,

	NUM_NL80211_P2P_PS_STATUS,
पूर्ण;

#घोषणा NL80211_STA_FLAG_MAX_OLD_API	NL80211_STA_FLAG_TDLS_PEER

/**
 * काष्ठा nl80211_sta_flag_update - station flags mask/set
 * @mask: mask of station flags to set
 * @set: which values to set them to
 *
 * Both mask and set contain bits as per &क्रमागत nl80211_sta_flags.
 */
काष्ठा nl80211_sta_flag_update अणु
	__u32 mask;
	__u32 set;
पूर्ण __attribute__((packed));

/**
 * क्रमागत nl80211_he_gi - HE guard पूर्णांकerval
 * @NL80211_RATE_INFO_HE_GI_0_8: 0.8 usec
 * @NL80211_RATE_INFO_HE_GI_1_6: 1.6 usec
 * @NL80211_RATE_INFO_HE_GI_3_2: 3.2 usec
 */
क्रमागत nl80211_he_gi अणु
	NL80211_RATE_INFO_HE_GI_0_8,
	NL80211_RATE_INFO_HE_GI_1_6,
	NL80211_RATE_INFO_HE_GI_3_2,
पूर्ण;

/**
 * क्रमागत nl80211_he_ltf - HE दीर्घ training field
 * @NL80211_RATE_INFO_HE_1xLTF: 3.2 usec
 * @NL80211_RATE_INFO_HE_2xLTF: 6.4 usec
 * @NL80211_RATE_INFO_HE_4xLTF: 12.8 usec
 */
क्रमागत nl80211_he_ltf अणु
	NL80211_RATE_INFO_HE_1XLTF,
	NL80211_RATE_INFO_HE_2XLTF,
	NL80211_RATE_INFO_HE_4XLTF,
पूर्ण;

/**
 * क्रमागत nl80211_he_ru_alloc - HE RU allocation values
 * @NL80211_RATE_INFO_HE_RU_ALLOC_26: 26-tone RU allocation
 * @NL80211_RATE_INFO_HE_RU_ALLOC_52: 52-tone RU allocation
 * @NL80211_RATE_INFO_HE_RU_ALLOC_106: 106-tone RU allocation
 * @NL80211_RATE_INFO_HE_RU_ALLOC_242: 242-tone RU allocation
 * @NL80211_RATE_INFO_HE_RU_ALLOC_484: 484-tone RU allocation
 * @NL80211_RATE_INFO_HE_RU_ALLOC_996: 996-tone RU allocation
 * @NL80211_RATE_INFO_HE_RU_ALLOC_2x996: 2x996-tone RU allocation
 */
क्रमागत nl80211_he_ru_alloc अणु
	NL80211_RATE_INFO_HE_RU_ALLOC_26,
	NL80211_RATE_INFO_HE_RU_ALLOC_52,
	NL80211_RATE_INFO_HE_RU_ALLOC_106,
	NL80211_RATE_INFO_HE_RU_ALLOC_242,
	NL80211_RATE_INFO_HE_RU_ALLOC_484,
	NL80211_RATE_INFO_HE_RU_ALLOC_996,
	NL80211_RATE_INFO_HE_RU_ALLOC_2x996,
पूर्ण;

/**
 * क्रमागत nl80211_rate_info - bitrate inक्रमmation
 *
 * These attribute types are used with %NL80211_STA_INFO_TXRATE
 * when getting inक्रमmation about the bitrate of a station.
 * There are 2 attributes क्रम bitrate, a legacy one that represents
 * a 16-bit value, and new one that represents a 32-bit value.
 * If the rate value fits पूर्णांकo 16 bit, both attributes are reported
 * with the same value. If the rate is too high to fit पूर्णांकo 16 bits
 * (>6.5535Gbps) only 32-bit attribute is included.
 * User space tools encouraged to use the 32-bit attribute and fall
 * back to the 16-bit one क्रम compatibility with older kernels.
 *
 * @__NL80211_RATE_INFO_INVALID: attribute number 0 is reserved
 * @NL80211_RATE_INFO_BITRATE: total bitrate (u16, 100kbit/s)
 * @NL80211_RATE_INFO_MCS: mcs index क्रम 802.11n (u8)
 * @NL80211_RATE_INFO_40_MHZ_WIDTH: 40 MHz dualchannel bitrate
 * @NL80211_RATE_INFO_SHORT_GI: 400ns guard पूर्णांकerval
 * @NL80211_RATE_INFO_BITRATE32: total bitrate (u32, 100kbit/s)
 * @NL80211_RATE_INFO_MAX: highest rate_info number currently defined
 * @NL80211_RATE_INFO_VHT_MCS: MCS index क्रम VHT (u8)
 * @NL80211_RATE_INFO_VHT_NSS: number of streams in VHT (u8)
 * @NL80211_RATE_INFO_80_MHZ_WIDTH: 80 MHz VHT rate
 * @NL80211_RATE_INFO_80P80_MHZ_WIDTH: unused - 80+80 is treated the
 *	same as 160 क्रम purposes of the bitrates
 * @NL80211_RATE_INFO_160_MHZ_WIDTH: 160 MHz VHT rate
 * @NL80211_RATE_INFO_10_MHZ_WIDTH: 10 MHz width - note that this is
 *	a legacy rate and will be reported as the actual bitrate, i.e.
 *	half the base (20 MHz) rate
 * @NL80211_RATE_INFO_5_MHZ_WIDTH: 5 MHz width - note that this is
 *	a legacy rate and will be reported as the actual bitrate, i.e.
 *	a quarter of the base (20 MHz) rate
 * @NL80211_RATE_INFO_HE_MCS: HE MCS index (u8, 0-11)
 * @NL80211_RATE_INFO_HE_NSS: HE NSS value (u8, 1-8)
 * @NL80211_RATE_INFO_HE_GI: HE guard पूर्णांकerval identअगरier
 *	(u8, see &क्रमागत nl80211_he_gi)
 * @NL80211_RATE_INFO_HE_DCM: HE DCM value (u8, 0/1)
 * @NL80211_RATE_INFO_RU_ALLOC: HE RU allocation, अगर not present then
 *	non-OFDMA was used (u8, see &क्रमागत nl80211_he_ru_alloc)
 * @__NL80211_RATE_INFO_AFTER_LAST: पूर्णांकernal use
 */
क्रमागत nl80211_rate_info अणु
	__NL80211_RATE_INFO_INVALID,
	NL80211_RATE_INFO_BITRATE,
	NL80211_RATE_INFO_MCS,
	NL80211_RATE_INFO_40_MHZ_WIDTH,
	NL80211_RATE_INFO_SHORT_GI,
	NL80211_RATE_INFO_BITRATE32,
	NL80211_RATE_INFO_VHT_MCS,
	NL80211_RATE_INFO_VHT_NSS,
	NL80211_RATE_INFO_80_MHZ_WIDTH,
	NL80211_RATE_INFO_80P80_MHZ_WIDTH,
	NL80211_RATE_INFO_160_MHZ_WIDTH,
	NL80211_RATE_INFO_10_MHZ_WIDTH,
	NL80211_RATE_INFO_5_MHZ_WIDTH,
	NL80211_RATE_INFO_HE_MCS,
	NL80211_RATE_INFO_HE_NSS,
	NL80211_RATE_INFO_HE_GI,
	NL80211_RATE_INFO_HE_DCM,
	NL80211_RATE_INFO_HE_RU_ALLOC,

	/* keep last */
	__NL80211_RATE_INFO_AFTER_LAST,
	NL80211_RATE_INFO_MAX = __NL80211_RATE_INFO_AFTER_LAST - 1
पूर्ण;

/**
 * क्रमागत nl80211_sta_bss_param - BSS inक्रमmation collected by STA
 *
 * These attribute types are used with %NL80211_STA_INFO_BSS_PARAM
 * when getting inक्रमmation about the bitrate of a station.
 *
 * @__NL80211_STA_BSS_PARAM_INVALID: attribute number 0 is reserved
 * @NL80211_STA_BSS_PARAM_CTS_PROT: whether CTS protection is enabled (flag)
 * @NL80211_STA_BSS_PARAM_SHORT_PREAMBLE:  whether लघु preamble is enabled
 *	(flag)
 * @NL80211_STA_BSS_PARAM_SHORT_SLOT_TIME:  whether लघु slot समय is enabled
 *	(flag)
 * @NL80211_STA_BSS_PARAM_DTIM_PERIOD: DTIM period क्रम beaconing (u8)
 * @NL80211_STA_BSS_PARAM_BEACON_INTERVAL: Beacon पूर्णांकerval (u16)
 * @NL80211_STA_BSS_PARAM_MAX: highest sta_bss_param number currently defined
 * @__NL80211_STA_BSS_PARAM_AFTER_LAST: पूर्णांकernal use
 */
क्रमागत nl80211_sta_bss_param अणु
	__NL80211_STA_BSS_PARAM_INVALID,
	NL80211_STA_BSS_PARAM_CTS_PROT,
	NL80211_STA_BSS_PARAM_SHORT_PREAMBLE,
	NL80211_STA_BSS_PARAM_SHORT_SLOT_TIME,
	NL80211_STA_BSS_PARAM_DTIM_PERIOD,
	NL80211_STA_BSS_PARAM_BEACON_INTERVAL,

	/* keep last */
	__NL80211_STA_BSS_PARAM_AFTER_LAST,
	NL80211_STA_BSS_PARAM_MAX = __NL80211_STA_BSS_PARAM_AFTER_LAST - 1
पूर्ण;

/**
 * क्रमागत nl80211_sta_info - station inक्रमmation
 *
 * These attribute types are used with %NL80211_ATTR_STA_INFO
 * when getting inक्रमmation about a station.
 *
 * @__NL80211_STA_INFO_INVALID: attribute number 0 is reserved
 * @NL80211_STA_INFO_INACTIVE_TIME: समय since last activity (u32, msecs)
 * @NL80211_STA_INFO_RX_BYTES: total received bytes (MPDU length)
 *	(u32, from this station)
 * @NL80211_STA_INFO_TX_BYTES: total transmitted bytes (MPDU length)
 *	(u32, to this station)
 * @NL80211_STA_INFO_RX_BYTES64: total received bytes (MPDU length)
 *	(u64, from this station)
 * @NL80211_STA_INFO_TX_BYTES64: total transmitted bytes (MPDU length)
 *	(u64, to this station)
 * @NL80211_STA_INFO_SIGNAL: संकेत strength of last received PPDU (u8, dBm)
 * @NL80211_STA_INFO_TX_BITRATE: current unicast tx rate, nested attribute
 * 	containing info as possible, see &क्रमागत nl80211_rate_info
 * @NL80211_STA_INFO_RX_PACKETS: total received packet (MSDUs and MMPDUs)
 *	(u32, from this station)
 * @NL80211_STA_INFO_TX_PACKETS: total transmitted packets (MSDUs and MMPDUs)
 *	(u32, to this station)
 * @NL80211_STA_INFO_TX_RETRIES: total retries (MPDUs) (u32, to this station)
 * @NL80211_STA_INFO_TX_FAILED: total failed packets (MPDUs)
 *	(u32, to this station)
 * @NL80211_STA_INFO_SIGNAL_AVG: संकेत strength average (u8, dBm)
 * @NL80211_STA_INFO_LLID: the station's mesh LLID
 * @NL80211_STA_INFO_PLID: the station's mesh PLID
 * @NL80211_STA_INFO_PLINK_STATE: peer link state क्रम the station
 *	(see %क्रमागत nl80211_plink_state)
 * @NL80211_STA_INFO_RX_BITRATE: last unicast data frame rx rate, nested
 *	attribute, like NL80211_STA_INFO_TX_BITRATE.
 * @NL80211_STA_INFO_BSS_PARAM: current station's view of BSS, nested attribute
 *     containing info as possible, see &क्रमागत nl80211_sta_bss_param
 * @NL80211_STA_INFO_CONNECTED_TIME: समय since the station is last connected
 * @NL80211_STA_INFO_STA_FLAGS: Contains a काष्ठा nl80211_sta_flag_update.
 * @NL80211_STA_INFO_BEACON_LOSS: count of बार beacon loss was detected (u32)
 * @NL80211_STA_INFO_T_OFFSET: timing offset with respect to this STA (s64)
 * @NL80211_STA_INFO_LOCAL_PM: local mesh STA link-specअगरic घातer mode
 * @NL80211_STA_INFO_PEER_PM: peer mesh STA link-specअगरic घातer mode
 * @NL80211_STA_INFO_NONPEER_PM: neighbor mesh STA घातer save mode towards
 *	non-peer STA
 * @NL80211_STA_INFO_CHAIN_SIGNAL: per-chain संकेत strength of last PPDU
 *	Contains a nested array of संकेत strength attributes (u8, dBm)
 * @NL80211_STA_INFO_CHAIN_SIGNAL_AVG: per-chain संकेत strength average
 *	Same क्रमmat as NL80211_STA_INFO_CHAIN_SIGNAL.
 * @NL80211_STA_EXPECTED_THROUGHPUT: expected throughput considering also the
 *	802.11 header (u32, kbps)
 * @NL80211_STA_INFO_RX_DROP_MISC: RX packets dropped क्रम unspecअगरied reasons
 *	(u64)
 * @NL80211_STA_INFO_BEACON_RX: number of beacons received from this peer (u64)
 * @NL80211_STA_INFO_BEACON_SIGNAL_AVG: संकेत strength average
 *	क्रम beacons only (u8, dBm)
 * @NL80211_STA_INFO_TID_STATS: per-TID statistics (see &क्रमागत nl80211_tid_stats)
 *	This is a nested attribute where each the inner attribute number is the
 *	TID+1 and the special TID 16 (i.e. value 17) is used क्रम non-QoS frames;
 *	each one of those is again nested with &क्रमागत nl80211_tid_stats
 *	attributes carrying the actual values.
 * @NL80211_STA_INFO_RX_DURATION: aggregate PPDU duration क्रम all frames
 *	received from the station (u64, usec)
 * @NL80211_STA_INFO_PAD: attribute used क्रम padding क्रम 64-bit alignment
 * @NL80211_STA_INFO_ACK_SIGNAL: संकेत strength of the last ACK frame(u8, dBm)
 * @NL80211_STA_INFO_ACK_SIGNAL_AVG: avg संकेत strength of ACK frames (s8, dBm)
 * @NL80211_STA_INFO_RX_MPDUS: total number of received packets (MPDUs)
 *	(u32, from this station)
 * @NL80211_STA_INFO_FCS_ERROR_COUNT: total number of packets (MPDUs) received
 *	with an FCS error (u32, from this station). This count may not include
 *	some packets with an FCS error due to TA corruption. Hence this counter
 *	might not be fully accurate.
 * @NL80211_STA_INFO_CONNECTED_TO_GATE: set to true अगर STA has a path to a
 *	mesh gate (u8, 0 or 1)
 * @NL80211_STA_INFO_TX_DURATION: aggregate PPDU duration क्रम all frames
 *	sent to the station (u64, usec)
 * @NL80211_STA_INFO_AIRTIME_WEIGHT: current airसमय weight क्रम station (u16)
 * @NL80211_STA_INFO_AIRTIME_LINK_METRIC: airसमय link metric क्रम mesh station
 * @NL80211_STA_INFO_ASSOC_AT_BOOTTIME: Timestamp (CLOCK_BOOTTIME, nanoseconds)
 *	of STA's association
 * @NL80211_STA_INFO_CONNECTED_TO_AS: set to true अगर STA has a path to a
 *	authentication server (u8, 0 or 1)
 * @__NL80211_STA_INFO_AFTER_LAST: पूर्णांकernal
 * @NL80211_STA_INFO_MAX: highest possible station info attribute
 */
क्रमागत nl80211_sta_info अणु
	__NL80211_STA_INFO_INVALID,
	NL80211_STA_INFO_INACTIVE_TIME,
	NL80211_STA_INFO_RX_BYTES,
	NL80211_STA_INFO_TX_BYTES,
	NL80211_STA_INFO_LLID,
	NL80211_STA_INFO_PLID,
	NL80211_STA_INFO_PLINK_STATE,
	NL80211_STA_INFO_SIGNAL,
	NL80211_STA_INFO_TX_BITRATE,
	NL80211_STA_INFO_RX_PACKETS,
	NL80211_STA_INFO_TX_PACKETS,
	NL80211_STA_INFO_TX_RETRIES,
	NL80211_STA_INFO_TX_FAILED,
	NL80211_STA_INFO_SIGNAL_AVG,
	NL80211_STA_INFO_RX_BITRATE,
	NL80211_STA_INFO_BSS_PARAM,
	NL80211_STA_INFO_CONNECTED_TIME,
	NL80211_STA_INFO_STA_FLAGS,
	NL80211_STA_INFO_BEACON_LOSS,
	NL80211_STA_INFO_T_OFFSET,
	NL80211_STA_INFO_LOCAL_PM,
	NL80211_STA_INFO_PEER_PM,
	NL80211_STA_INFO_NONPEER_PM,
	NL80211_STA_INFO_RX_BYTES64,
	NL80211_STA_INFO_TX_BYTES64,
	NL80211_STA_INFO_CHAIN_SIGNAL,
	NL80211_STA_INFO_CHAIN_SIGNAL_AVG,
	NL80211_STA_INFO_EXPECTED_THROUGHPUT,
	NL80211_STA_INFO_RX_DROP_MISC,
	NL80211_STA_INFO_BEACON_RX,
	NL80211_STA_INFO_BEACON_SIGNAL_AVG,
	NL80211_STA_INFO_TID_STATS,
	NL80211_STA_INFO_RX_DURATION,
	NL80211_STA_INFO_PAD,
	NL80211_STA_INFO_ACK_SIGNAL,
	NL80211_STA_INFO_ACK_SIGNAL_AVG,
	NL80211_STA_INFO_RX_MPDUS,
	NL80211_STA_INFO_FCS_ERROR_COUNT,
	NL80211_STA_INFO_CONNECTED_TO_GATE,
	NL80211_STA_INFO_TX_DURATION,
	NL80211_STA_INFO_AIRTIME_WEIGHT,
	NL80211_STA_INFO_AIRTIME_LINK_METRIC,
	NL80211_STA_INFO_ASSOC_AT_BOOTTIME,
	NL80211_STA_INFO_CONNECTED_TO_AS,

	/* keep last */
	__NL80211_STA_INFO_AFTER_LAST,
	NL80211_STA_INFO_MAX = __NL80211_STA_INFO_AFTER_LAST - 1
पूर्ण;

/* we नामd this - stay compatible */
#घोषणा NL80211_STA_INFO_DATA_ACK_SIGNAL_AVG NL80211_STA_INFO_ACK_SIGNAL_AVG


/**
 * क्रमागत nl80211_tid_stats - per TID statistics attributes
 * @__NL80211_TID_STATS_INVALID: attribute number 0 is reserved
 * @NL80211_TID_STATS_RX_MSDU: number of MSDUs received (u64)
 * @NL80211_TID_STATS_TX_MSDU: number of MSDUs transmitted (or
 *	attempted to transmit; u64)
 * @NL80211_TID_STATS_TX_MSDU_RETRIES: number of retries क्रम
 *	transmitted MSDUs (not counting the first attempt; u64)
 * @NL80211_TID_STATS_TX_MSDU_FAILED: number of failed transmitted
 *	MSDUs (u64)
 * @NL80211_TID_STATS_PAD: attribute used क्रम padding क्रम 64-bit alignment
 * @NL80211_TID_STATS_TXQ_STATS: TXQ stats (nested attribute)
 * @NUM_NL80211_TID_STATS: number of attributes here
 * @NL80211_TID_STATS_MAX: highest numbered attribute here
 */
क्रमागत nl80211_tid_stats अणु
	__NL80211_TID_STATS_INVALID,
	NL80211_TID_STATS_RX_MSDU,
	NL80211_TID_STATS_TX_MSDU,
	NL80211_TID_STATS_TX_MSDU_RETRIES,
	NL80211_TID_STATS_TX_MSDU_FAILED,
	NL80211_TID_STATS_PAD,
	NL80211_TID_STATS_TXQ_STATS,

	/* keep last */
	NUM_NL80211_TID_STATS,
	NL80211_TID_STATS_MAX = NUM_NL80211_TID_STATS - 1
पूर्ण;

/**
 * क्रमागत nl80211_txq_stats - per TXQ statistics attributes
 * @__NL80211_TXQ_STATS_INVALID: attribute number 0 is reserved
 * @NUM_NL80211_TXQ_STATS: number of attributes here
 * @NL80211_TXQ_STATS_BACKLOG_BYTES: number of bytes currently backlogged
 * @NL80211_TXQ_STATS_BACKLOG_PACKETS: number of packets currently
 *      backlogged
 * @NL80211_TXQ_STATS_FLOWS: total number of new flows seen
 * @NL80211_TXQ_STATS_DROPS: total number of packet drops
 * @NL80211_TXQ_STATS_ECN_MARKS: total number of packet ECN marks
 * @NL80211_TXQ_STATS_OVERLIMIT: number of drops due to queue space overflow
 * @NL80211_TXQ_STATS_OVERMEMORY: number of drops due to memory limit overflow
 *      (only क्रम per-phy stats)
 * @NL80211_TXQ_STATS_COLLISIONS: number of hash collisions
 * @NL80211_TXQ_STATS_TX_BYTES: total number of bytes dequeued from TXQ
 * @NL80211_TXQ_STATS_TX_PACKETS: total number of packets dequeued from TXQ
 * @NL80211_TXQ_STATS_MAX_FLOWS: number of flow buckets क्रम PHY
 * @NL80211_TXQ_STATS_MAX: highest numbered attribute here
 */
क्रमागत nl80211_txq_stats अणु
	__NL80211_TXQ_STATS_INVALID,
	NL80211_TXQ_STATS_BACKLOG_BYTES,
	NL80211_TXQ_STATS_BACKLOG_PACKETS,
	NL80211_TXQ_STATS_FLOWS,
	NL80211_TXQ_STATS_DROPS,
	NL80211_TXQ_STATS_ECN_MARKS,
	NL80211_TXQ_STATS_OVERLIMIT,
	NL80211_TXQ_STATS_OVERMEMORY,
	NL80211_TXQ_STATS_COLLISIONS,
	NL80211_TXQ_STATS_TX_BYTES,
	NL80211_TXQ_STATS_TX_PACKETS,
	NL80211_TXQ_STATS_MAX_FLOWS,

	/* keep last */
	NUM_NL80211_TXQ_STATS,
	NL80211_TXQ_STATS_MAX = NUM_NL80211_TXQ_STATS - 1
पूर्ण;

/**
 * क्रमागत nl80211_mpath_flags - nl80211 mesh path flags
 *
 * @NL80211_MPATH_FLAG_ACTIVE: the mesh path is active
 * @NL80211_MPATH_FLAG_RESOLVING: the mesh path discovery process is running
 * @NL80211_MPATH_FLAG_SN_VALID: the mesh path contains a valid SN
 * @NL80211_MPATH_FLAG_FIXED: the mesh path has been manually set
 * @NL80211_MPATH_FLAG_RESOLVED: the mesh path discovery process succeeded
 */
क्रमागत nl80211_mpath_flags अणु
	NL80211_MPATH_FLAG_ACTIVE =	1<<0,
	NL80211_MPATH_FLAG_RESOLVING =	1<<1,
	NL80211_MPATH_FLAG_SN_VALID =	1<<2,
	NL80211_MPATH_FLAG_FIXED =	1<<3,
	NL80211_MPATH_FLAG_RESOLVED =	1<<4,
पूर्ण;

/**
 * क्रमागत nl80211_mpath_info - mesh path inक्रमmation
 *
 * These attribute types are used with %NL80211_ATTR_MPATH_INFO when getting
 * inक्रमmation about a mesh path.
 *
 * @__NL80211_MPATH_INFO_INVALID: attribute number 0 is reserved
 * @NL80211_MPATH_INFO_FRAME_QLEN: number of queued frames क्रम this destination
 * @NL80211_MPATH_INFO_SN: destination sequence number
 * @NL80211_MPATH_INFO_METRIC: metric (cost) of this mesh path
 * @NL80211_MPATH_INFO_EXPTIME: expiration समय क्रम the path, in msec from now
 * @NL80211_MPATH_INFO_FLAGS: mesh path flags, क्रमागतerated in
 * 	&क्रमागत nl80211_mpath_flags;
 * @NL80211_MPATH_INFO_DISCOVERY_TIMEOUT: total path discovery समयout, in msec
 * @NL80211_MPATH_INFO_DISCOVERY_RETRIES: mesh path discovery retries
 * @NL80211_MPATH_INFO_HOP_COUNT: hop count to destination
 * @NL80211_MPATH_INFO_PATH_CHANGE: total number of path changes to destination
 * @NL80211_MPATH_INFO_MAX: highest mesh path inक्रमmation attribute number
 *	currently defined
 * @__NL80211_MPATH_INFO_AFTER_LAST: पूर्णांकernal use
 */
क्रमागत nl80211_mpath_info अणु
	__NL80211_MPATH_INFO_INVALID,
	NL80211_MPATH_INFO_FRAME_QLEN,
	NL80211_MPATH_INFO_SN,
	NL80211_MPATH_INFO_METRIC,
	NL80211_MPATH_INFO_EXPTIME,
	NL80211_MPATH_INFO_FLAGS,
	NL80211_MPATH_INFO_DISCOVERY_TIMEOUT,
	NL80211_MPATH_INFO_DISCOVERY_RETRIES,
	NL80211_MPATH_INFO_HOP_COUNT,
	NL80211_MPATH_INFO_PATH_CHANGE,

	/* keep last */
	__NL80211_MPATH_INFO_AFTER_LAST,
	NL80211_MPATH_INFO_MAX = __NL80211_MPATH_INFO_AFTER_LAST - 1
पूर्ण;

/**
 * क्रमागत nl80211_band_अगरtype_attr - Interface type data attributes
 *
 * @__NL80211_BAND_IFTYPE_ATTR_INVALID: attribute number 0 is reserved
 * @NL80211_BAND_IFTYPE_ATTR_IFTYPES: nested attribute containing a flag attribute
 *     क्रम each पूर्णांकerface type that supports the band data
 * @NL80211_BAND_IFTYPE_ATTR_HE_CAP_MAC: HE MAC capabilities as in HE
 *     capabilities IE
 * @NL80211_BAND_IFTYPE_ATTR_HE_CAP_PHY: HE PHY capabilities as in HE
 *     capabilities IE
 * @NL80211_BAND_IFTYPE_ATTR_HE_CAP_MCS_SET: HE supported NSS/MCS as in HE
 *     capabilities IE
 * @NL80211_BAND_IFTYPE_ATTR_HE_CAP_PPE: HE PPE thresholds inक्रमmation as
 *     defined in HE capabilities IE
 * @NL80211_BAND_IFTYPE_ATTR_MAX: highest band HE capability attribute currently
 *     defined
 * @NL80211_BAND_IFTYPE_ATTR_HE_6GHZ_CAPA: HE 6GHz band capabilities (__le16),
 *	given क्रम all 6 GHz band channels
 * @__NL80211_BAND_IFTYPE_ATTR_AFTER_LAST: पूर्णांकernal use
 */
क्रमागत nl80211_band_अगरtype_attr अणु
	__NL80211_BAND_IFTYPE_ATTR_INVALID,

	NL80211_BAND_IFTYPE_ATTR_IFTYPES,
	NL80211_BAND_IFTYPE_ATTR_HE_CAP_MAC,
	NL80211_BAND_IFTYPE_ATTR_HE_CAP_PHY,
	NL80211_BAND_IFTYPE_ATTR_HE_CAP_MCS_SET,
	NL80211_BAND_IFTYPE_ATTR_HE_CAP_PPE,
	NL80211_BAND_IFTYPE_ATTR_HE_6GHZ_CAPA,

	/* keep last */
	__NL80211_BAND_IFTYPE_ATTR_AFTER_LAST,
	NL80211_BAND_IFTYPE_ATTR_MAX = __NL80211_BAND_IFTYPE_ATTR_AFTER_LAST - 1
पूर्ण;

/**
 * क्रमागत nl80211_band_attr - band attributes
 * @__NL80211_BAND_ATTR_INVALID: attribute number 0 is reserved
 * @NL80211_BAND_ATTR_FREQS: supported frequencies in this band,
 *	an array of nested frequency attributes
 * @NL80211_BAND_ATTR_RATES: supported bitrates in this band,
 *	an array of nested bitrate attributes
 * @NL80211_BAND_ATTR_HT_MCS_SET: 16-byte attribute containing the MCS set as
 *	defined in 802.11n
 * @NL80211_BAND_ATTR_HT_CAPA: HT capabilities, as in the HT inक्रमmation IE
 * @NL80211_BAND_ATTR_HT_AMPDU_FACTOR: A-MPDU factor, as in 11n
 * @NL80211_BAND_ATTR_HT_AMPDU_DENSITY: A-MPDU density, as in 11n
 * @NL80211_BAND_ATTR_VHT_MCS_SET: 32-byte attribute containing the MCS set as
 *	defined in 802.11ac
 * @NL80211_BAND_ATTR_VHT_CAPA: VHT capabilities, as in the HT inक्रमmation IE
 * @NL80211_BAND_ATTR_IFTYPE_DATA: nested array attribute, with each entry using
 *	attributes from &क्रमागत nl80211_band_अगरtype_attr
 * @NL80211_BAND_ATTR_EDMG_CHANNELS: biपंचांगap that indicates the 2.16 GHz
 *	channel(s) that are allowed to be used क्रम EDMG transmissions.
 *	Defined by IEEE P802.11ay/D4.0 section 9.4.2.251.
 * @NL80211_BAND_ATTR_EDMG_BW_CONFIG: Channel BW Configuration subfield encodes
 *	the allowed channel bandwidth configurations.
 *	Defined by IEEE P802.11ay/D4.0 section 9.4.2.251, Table 13.
 * @NL80211_BAND_ATTR_MAX: highest band attribute currently defined
 * @__NL80211_BAND_ATTR_AFTER_LAST: पूर्णांकernal use
 */
क्रमागत nl80211_band_attr अणु
	__NL80211_BAND_ATTR_INVALID,
	NL80211_BAND_ATTR_FREQS,
	NL80211_BAND_ATTR_RATES,

	NL80211_BAND_ATTR_HT_MCS_SET,
	NL80211_BAND_ATTR_HT_CAPA,
	NL80211_BAND_ATTR_HT_AMPDU_FACTOR,
	NL80211_BAND_ATTR_HT_AMPDU_DENSITY,

	NL80211_BAND_ATTR_VHT_MCS_SET,
	NL80211_BAND_ATTR_VHT_CAPA,
	NL80211_BAND_ATTR_IFTYPE_DATA,

	NL80211_BAND_ATTR_EDMG_CHANNELS,
	NL80211_BAND_ATTR_EDMG_BW_CONFIG,

	/* keep last */
	__NL80211_BAND_ATTR_AFTER_LAST,
	NL80211_BAND_ATTR_MAX = __NL80211_BAND_ATTR_AFTER_LAST - 1
पूर्ण;

#घोषणा NL80211_BAND_ATTR_HT_CAPA NL80211_BAND_ATTR_HT_CAPA

/**
 * क्रमागत nl80211_wmm_rule - regulatory wmm rule
 *
 * @__NL80211_WMMR_INVALID: attribute number 0 is reserved
 * @NL80211_WMMR_CW_MIN: Minimum contention winकरोw slot.
 * @NL80211_WMMR_CW_MAX: Maximum contention winकरोw slot.
 * @NL80211_WMMR_AIFSN: Arbitration Inter Frame Space.
 * @NL80211_WMMR_TXOP: Maximum allowed tx operation समय.
 * @nl80211_WMMR_MAX: highest possible wmm rule.
 * @__NL80211_WMMR_LAST: Internal use.
 */
क्रमागत nl80211_wmm_rule अणु
	__NL80211_WMMR_INVALID,
	NL80211_WMMR_CW_MIN,
	NL80211_WMMR_CW_MAX,
	NL80211_WMMR_AIFSN,
	NL80211_WMMR_TXOP,

	/* keep last */
	__NL80211_WMMR_LAST,
	NL80211_WMMR_MAX = __NL80211_WMMR_LAST - 1
पूर्ण;

/**
 * क्रमागत nl80211_frequency_attr - frequency attributes
 * @__NL80211_FREQUENCY_ATTR_INVALID: attribute number 0 is reserved
 * @NL80211_FREQUENCY_ATTR_FREQ: Frequency in MHz
 * @NL80211_FREQUENCY_ATTR_DISABLED: Channel is disabled in current
 *	regulatory करोमुख्य.
 * @NL80211_FREQUENCY_ATTR_NO_IR: no mechanisms that initiate radiation
 * 	are permitted on this channel, this includes sending probe
 * 	requests, or modes of operation that require beaconing.
 * @NL80211_FREQUENCY_ATTR_RADAR: Radar detection is mandatory
 *	on this channel in current regulatory करोमुख्य.
 * @NL80211_FREQUENCY_ATTR_MAX_TX_POWER: Maximum transmission घातer in mBm
 *	(100 * dBm).
 * @NL80211_FREQUENCY_ATTR_DFS_STATE: current state क्रम DFS
 *	(क्रमागत nl80211_dfs_state)
 * @NL80211_FREQUENCY_ATTR_DFS_TIME: समय in miliseconds क्रम how दीर्घ
 *	this channel is in this DFS state.
 * @NL80211_FREQUENCY_ATTR_NO_HT40_MINUS: HT40- isn't possible with this
 *	channel as the control channel
 * @NL80211_FREQUENCY_ATTR_NO_HT40_PLUS: HT40+ isn't possible with this
 *	channel as the control channel
 * @NL80211_FREQUENCY_ATTR_NO_80MHZ: any 80 MHz channel using this channel
 *	as the primary or any of the secondary channels isn't possible,
 *	this includes 80+80 channels
 * @NL80211_FREQUENCY_ATTR_NO_160MHZ: any 160 MHz (but not 80+80) channel
 *	using this channel as the primary or any of the secondary channels
 *	isn't possible
 * @NL80211_FREQUENCY_ATTR_DFS_CAC_TIME: DFS CAC समय in milliseconds.
 * @NL80211_FREQUENCY_ATTR_INDOOR_ONLY: Only inकरोor use is permitted on this
 *	channel. A channel that has the INDOOR_ONLY attribute can only be
 *	used when there is a clear assessment that the device is operating in
 *	an inकरोor surroundings, i.e., it is connected to AC घातer (and not
 *	through portable DC inverters) or is under the control of a master
 *	that is acting as an AP and is connected to AC घातer.
 * @NL80211_FREQUENCY_ATTR_IR_CONCURRENT: IR operation is allowed on this
 *	channel अगर it's connected concurrently to a BSS on the same channel on
 *	the 2 GHz band or to a channel in the same UNII band (on the 5 GHz
 *	band), and IEEE80211_CHAN_RADAR is not set. Instantiating a GO or TDLS
 *	off-channel on a channel that has the IR_CONCURRENT attribute set can be
 *	करोne when there is a clear assessment that the device is operating under
 *	the guidance of an authorized master, i.e., setting up a GO or TDLS
 *	off-channel जबतक the device is also connected to an AP with DFS and
 *	radar detection on the UNII band (it is up to user-space, i.e.,
 *	wpa_supplicant to perक्रमm the required verअगरications). Using this
 *	attribute क्रम IR is disallowed क्रम master पूर्णांकerfaces (IBSS, AP).
 * @NL80211_FREQUENCY_ATTR_NO_20MHZ: 20 MHz operation is not allowed
 *	on this channel in current regulatory करोमुख्य.
 * @NL80211_FREQUENCY_ATTR_NO_10MHZ: 10 MHz operation is not allowed
 *	on this channel in current regulatory करोमुख्य.
 * @NL80211_FREQUENCY_ATTR_WMM: this channel has wmm limitations.
 *	This is a nested attribute that contains the wmm limitation per AC.
 *	(see &क्रमागत nl80211_wmm_rule)
 * @NL80211_FREQUENCY_ATTR_NO_HE: HE operation is not allowed on this channel
 *	in current regulatory करोमुख्य.
 * @NL80211_FREQUENCY_ATTR_OFFSET: frequency offset in KHz
 * @NL80211_FREQUENCY_ATTR_1MHZ: 1 MHz operation is allowed
 *	on this channel in current regulatory करोमुख्य.
 * @NL80211_FREQUENCY_ATTR_2MHZ: 2 MHz operation is allowed
 *	on this channel in current regulatory करोमुख्य.
 * @NL80211_FREQUENCY_ATTR_4MHZ: 4 MHz operation is allowed
 *	on this channel in current regulatory करोमुख्य.
 * @NL80211_FREQUENCY_ATTR_8MHZ: 8 MHz operation is allowed
 *	on this channel in current regulatory करोमुख्य.
 * @NL80211_FREQUENCY_ATTR_16MHZ: 16 MHz operation is allowed
 *	on this channel in current regulatory करोमुख्य.
 * @NL80211_FREQUENCY_ATTR_MAX: highest frequency attribute number
 *	currently defined
 * @__NL80211_FREQUENCY_ATTR_AFTER_LAST: पूर्णांकernal use
 *
 * See https://apps.fcc.gov/eas/comments/GetPublishedDocument.hपंचांगl?id=327&tn=528122
 * क्रम more inक्रमmation on the FCC description of the relaxations allowed
 * by NL80211_FREQUENCY_ATTR_INDOOR_ONLY and
 * NL80211_FREQUENCY_ATTR_IR_CONCURRENT.
 */
क्रमागत nl80211_frequency_attr अणु
	__NL80211_FREQUENCY_ATTR_INVALID,
	NL80211_FREQUENCY_ATTR_FREQ,
	NL80211_FREQUENCY_ATTR_DISABLED,
	NL80211_FREQUENCY_ATTR_NO_IR,
	__NL80211_FREQUENCY_ATTR_NO_IBSS,
	NL80211_FREQUENCY_ATTR_RADAR,
	NL80211_FREQUENCY_ATTR_MAX_TX_POWER,
	NL80211_FREQUENCY_ATTR_DFS_STATE,
	NL80211_FREQUENCY_ATTR_DFS_TIME,
	NL80211_FREQUENCY_ATTR_NO_HT40_MINUS,
	NL80211_FREQUENCY_ATTR_NO_HT40_PLUS,
	NL80211_FREQUENCY_ATTR_NO_80MHZ,
	NL80211_FREQUENCY_ATTR_NO_160MHZ,
	NL80211_FREQUENCY_ATTR_DFS_CAC_TIME,
	NL80211_FREQUENCY_ATTR_INDOOR_ONLY,
	NL80211_FREQUENCY_ATTR_IR_CONCURRENT,
	NL80211_FREQUENCY_ATTR_NO_20MHZ,
	NL80211_FREQUENCY_ATTR_NO_10MHZ,
	NL80211_FREQUENCY_ATTR_WMM,
	NL80211_FREQUENCY_ATTR_NO_HE,
	NL80211_FREQUENCY_ATTR_OFFSET,
	NL80211_FREQUENCY_ATTR_1MHZ,
	NL80211_FREQUENCY_ATTR_2MHZ,
	NL80211_FREQUENCY_ATTR_4MHZ,
	NL80211_FREQUENCY_ATTR_8MHZ,
	NL80211_FREQUENCY_ATTR_16MHZ,

	/* keep last */
	__NL80211_FREQUENCY_ATTR_AFTER_LAST,
	NL80211_FREQUENCY_ATTR_MAX = __NL80211_FREQUENCY_ATTR_AFTER_LAST - 1
पूर्ण;

#घोषणा NL80211_FREQUENCY_ATTR_MAX_TX_POWER NL80211_FREQUENCY_ATTR_MAX_TX_POWER
#घोषणा NL80211_FREQUENCY_ATTR_PASSIVE_SCAN	NL80211_FREQUENCY_ATTR_NO_IR
#घोषणा NL80211_FREQUENCY_ATTR_NO_IBSS		NL80211_FREQUENCY_ATTR_NO_IR
#घोषणा NL80211_FREQUENCY_ATTR_NO_IR		NL80211_FREQUENCY_ATTR_NO_IR
#घोषणा NL80211_FREQUENCY_ATTR_GO_CONCURRENT \
					NL80211_FREQUENCY_ATTR_IR_CONCURRENT

/**
 * क्रमागत nl80211_bitrate_attr - bitrate attributes
 * @__NL80211_BITRATE_ATTR_INVALID: attribute number 0 is reserved
 * @NL80211_BITRATE_ATTR_RATE: Bitrate in units of 100 kbps
 * @NL80211_BITRATE_ATTR_2GHZ_SHORTPREAMBLE: Short preamble supported
 *	in 2.4 GHz band.
 * @NL80211_BITRATE_ATTR_MAX: highest bitrate attribute number
 *	currently defined
 * @__NL80211_BITRATE_ATTR_AFTER_LAST: पूर्णांकernal use
 */
क्रमागत nl80211_bitrate_attr अणु
	__NL80211_BITRATE_ATTR_INVALID,
	NL80211_BITRATE_ATTR_RATE,
	NL80211_BITRATE_ATTR_2GHZ_SHORTPREAMBLE,

	/* keep last */
	__NL80211_BITRATE_ATTR_AFTER_LAST,
	NL80211_BITRATE_ATTR_MAX = __NL80211_BITRATE_ATTR_AFTER_LAST - 1
पूर्ण;

/**
 * क्रमागत nl80211_initiator - Indicates the initiator of a reg करोमुख्य request
 * @NL80211_REGDOM_SET_BY_CORE: Core queried CRDA क्रम a dynamic world
 * 	regulatory करोमुख्य.
 * @NL80211_REGDOM_SET_BY_USER: User asked the wireless core to set the
 * 	regulatory करोमुख्य.
 * @NL80211_REGDOM_SET_BY_DRIVER: a wireless drivers has hपूर्णांकed to the
 * 	wireless core it thinks its knows the regulatory करोमुख्य we should be in.
 * @NL80211_REGDOM_SET_BY_COUNTRY_IE: the wireless core has received an
 * 	802.11 country inक्रमmation element with regulatory inक्रमmation it
 * 	thinks we should consider. cfg80211 only processes the country
 *	code from the IE, and relies on the regulatory करोमुख्य inक्रमmation
 *	काष्ठाure passed by userspace (CRDA) from our wireless-regdb.
 *	If a channel is enabled but the country code indicates it should
 *	be disabled we disable the channel and re-enable it upon disassociation.
 */
क्रमागत nl80211_reg_initiator अणु
	NL80211_REGDOM_SET_BY_CORE,
	NL80211_REGDOM_SET_BY_USER,
	NL80211_REGDOM_SET_BY_DRIVER,
	NL80211_REGDOM_SET_BY_COUNTRY_IE,
पूर्ण;

/**
 * क्रमागत nl80211_reg_type - specअगरies the type of regulatory करोमुख्य
 * @NL80211_REGDOM_TYPE_COUNTRY: the regulatory करोमुख्य set is one that pertains
 *	to a specअगरic country. When this is set you can count on the
 *	ISO / IEC 3166 alpha2 country code being valid.
 * @NL80211_REGDOM_TYPE_WORLD: the regulatory set करोमुख्य is the world regulatory
 * 	करोमुख्य.
 * @NL80211_REGDOM_TYPE_CUSTOM_WORLD: the regulatory करोमुख्य set is a custom
 * 	driver specअगरic world regulatory करोमुख्य. These करो not apply प्रणाली-wide
 * 	and are only applicable to the inभागidual devices which have requested
 * 	them to be applied.
 * @NL80211_REGDOM_TYPE_INTERSECTION: the regulatory करोमुख्य set is the product
 *	of an पूर्णांकersection between two regulatory करोमुख्यs -- the previously
 *	set regulatory करोमुख्य on the प्रणाली and the last accepted regulatory
 *	करोमुख्य request to be processed.
 */
क्रमागत nl80211_reg_type अणु
	NL80211_REGDOM_TYPE_COUNTRY,
	NL80211_REGDOM_TYPE_WORLD,
	NL80211_REGDOM_TYPE_CUSTOM_WORLD,
	NL80211_REGDOM_TYPE_INTERSECTION,
पूर्ण;

/**
 * क्रमागत nl80211_reg_rule_attr - regulatory rule attributes
 * @__NL80211_REG_RULE_ATTR_INVALID: attribute number 0 is reserved
 * @NL80211_ATTR_REG_RULE_FLAGS: a set of flags which specअगरy additional
 * 	considerations क्रम a given frequency range. These are the
 * 	&क्रमागत nl80211_reg_rule_flags.
 * @NL80211_ATTR_FREQ_RANGE_START: starting frequencry क्रम the regulatory
 * 	rule in KHz. This is not a center of frequency but an actual regulatory
 * 	band edge.
 * @NL80211_ATTR_FREQ_RANGE_END: ending frequency क्रम the regulatory rule
 * 	in KHz. This is not a center a frequency but an actual regulatory
 * 	band edge.
 * @NL80211_ATTR_FREQ_RANGE_MAX_BW: maximum allowed bandwidth क्रम this
 *	frequency range, in KHz.
 * @NL80211_ATTR_POWER_RULE_MAX_ANT_GAIN: the maximum allowed antenna gain
 * 	क्रम a given frequency range. The value is in mBi (100 * dBi).
 * 	If you करोn't have one then don't send this.
 * @NL80211_ATTR_POWER_RULE_MAX_EIRP: the maximum allowed EIRP क्रम
 * 	a given frequency range. The value is in mBm (100 * dBm).
 * @NL80211_ATTR_DFS_CAC_TIME: DFS CAC समय in milliseconds.
 *	If not present or 0 शेष CAC समय will be used.
 * @NL80211_REG_RULE_ATTR_MAX: highest regulatory rule attribute number
 *	currently defined
 * @__NL80211_REG_RULE_ATTR_AFTER_LAST: पूर्णांकernal use
 */
क्रमागत nl80211_reg_rule_attr अणु
	__NL80211_REG_RULE_ATTR_INVALID,
	NL80211_ATTR_REG_RULE_FLAGS,

	NL80211_ATTR_FREQ_RANGE_START,
	NL80211_ATTR_FREQ_RANGE_END,
	NL80211_ATTR_FREQ_RANGE_MAX_BW,

	NL80211_ATTR_POWER_RULE_MAX_ANT_GAIN,
	NL80211_ATTR_POWER_RULE_MAX_EIRP,

	NL80211_ATTR_DFS_CAC_TIME,

	/* keep last */
	__NL80211_REG_RULE_ATTR_AFTER_LAST,
	NL80211_REG_RULE_ATTR_MAX = __NL80211_REG_RULE_ATTR_AFTER_LAST - 1
पूर्ण;

/**
 * क्रमागत nl80211_sched_scan_match_attr - scheduled scan match attributes
 * @__NL80211_SCHED_SCAN_MATCH_ATTR_INVALID: attribute number 0 is reserved
 * @NL80211_SCHED_SCAN_MATCH_ATTR_SSID: SSID to be used क्रम matching,
 *	only report BSS with matching SSID.
 *	(This cannot be used together with BSSID.)
 * @NL80211_SCHED_SCAN_MATCH_ATTR_RSSI: RSSI threshold (in dBm) क्रम reporting a
 *	BSS in scan results. Filtering is turned off अगर not specअगरied. Note that
 *	अगर this attribute is in a match set of its own, then it is treated as
 *	the शेष value क्रम all matchsets with an SSID, rather than being a
 *	matchset of its own without an RSSI filter. This is due to problems with
 *	how this API was implemented in the past. Also, due to the same problem,
 *	the only way to create a matchset with only an RSSI filter (with this
 *	attribute) is अगर there's only a single matchset with the RSSI attribute.
 * @NL80211_SCHED_SCAN_MATCH_ATTR_RELATIVE_RSSI: Flag indicating whether
 *	%NL80211_SCHED_SCAN_MATCH_ATTR_RSSI to be used as असलolute RSSI or
 *	relative to current bss's RSSI.
 * @NL80211_SCHED_SCAN_MATCH_ATTR_RSSI_ADJUST: When present the RSSI level क्रम
 *	BSS-es in the specअगरied band is to be adjusted beक्रमe करोing
 *	RSSI-based BSS selection. The attribute value is a packed काष्ठाure
 *	value as specअगरied by &काष्ठा nl80211_bss_select_rssi_adjust.
 * @NL80211_SCHED_SCAN_MATCH_ATTR_BSSID: BSSID to be used क्रम matching
 *	(this cannot be used together with SSID).
 * @NL80211_SCHED_SCAN_MATCH_PER_BAND_RSSI: Nested attribute that carries the
 *	band specअगरic minimum rssi thresholds क्रम the bands defined in
 *	क्रमागत nl80211_band. The minimum rssi threshold value(s32) specअगरic to a
 *	band shall be encapsulated in attribute with type value equals to one
 *	of the NL80211_BAND_* defined in क्रमागत nl80211_band. For example, the
 *	minimum rssi threshold value क्रम 2.4GHZ band shall be encapsulated
 *	within an attribute of type NL80211_BAND_2GHZ. And one or more of such
 *	attributes will be nested within this attribute.
 * @NL80211_SCHED_SCAN_MATCH_ATTR_MAX: highest scheduled scan filter
 *	attribute number currently defined
 * @__NL80211_SCHED_SCAN_MATCH_ATTR_AFTER_LAST: पूर्णांकernal use
 */
क्रमागत nl80211_sched_scan_match_attr अणु
	__NL80211_SCHED_SCAN_MATCH_ATTR_INVALID,

	NL80211_SCHED_SCAN_MATCH_ATTR_SSID,
	NL80211_SCHED_SCAN_MATCH_ATTR_RSSI,
	NL80211_SCHED_SCAN_MATCH_ATTR_RELATIVE_RSSI,
	NL80211_SCHED_SCAN_MATCH_ATTR_RSSI_ADJUST,
	NL80211_SCHED_SCAN_MATCH_ATTR_BSSID,
	NL80211_SCHED_SCAN_MATCH_PER_BAND_RSSI,

	/* keep last */
	__NL80211_SCHED_SCAN_MATCH_ATTR_AFTER_LAST,
	NL80211_SCHED_SCAN_MATCH_ATTR_MAX =
		__NL80211_SCHED_SCAN_MATCH_ATTR_AFTER_LAST - 1
पूर्ण;

/* only क्रम backward compatibility */
#घोषणा NL80211_ATTR_SCHED_SCAN_MATCH_SSID NL80211_SCHED_SCAN_MATCH_ATTR_SSID

/**
 * क्रमागत nl80211_reg_rule_flags - regulatory rule flags
 *
 * @NL80211_RRF_NO_OFDM: OFDM modulation not allowed
 * @NL80211_RRF_NO_CCK: CCK modulation not allowed
 * @NL80211_RRF_NO_INDOOR: inकरोor operation not allowed
 * @NL80211_RRF_NO_OUTDOOR: outकरोor operation not allowed
 * @NL80211_RRF_DFS: DFS support is required to be used
 * @NL80211_RRF_PTP_ONLY: this is only क्रम Poपूर्णांक To Poपूर्णांक links
 * @NL80211_RRF_PTMP_ONLY: this is only क्रम Poपूर्णांक To Multi Poपूर्णांक links
 * @NL80211_RRF_NO_IR: no mechanisms that initiate radiation are allowed,
 * 	this includes probe requests or modes of operation that require
 * 	beaconing.
 * @NL80211_RRF_AUTO_BW: maximum available bandwidth should be calculated
 *	base on contiguous rules and wider channels will be allowed to cross
 *	multiple contiguous/overlapping frequency ranges.
 * @NL80211_RRF_IR_CONCURRENT: See %NL80211_FREQUENCY_ATTR_IR_CONCURRENT
 * @NL80211_RRF_NO_HT40MINUS: channels can't be used in HT40- operation
 * @NL80211_RRF_NO_HT40PLUS: channels can't be used in HT40+ operation
 * @NL80211_RRF_NO_80MHZ: 80MHz operation not allowed
 * @NL80211_RRF_NO_160MHZ: 160MHz operation not allowed
 * @NL80211_RRF_NO_HE: HE operation not allowed
 */
क्रमागत nl80211_reg_rule_flags अणु
	NL80211_RRF_NO_OFDM		= 1<<0,
	NL80211_RRF_NO_CCK		= 1<<1,
	NL80211_RRF_NO_INDOOR		= 1<<2,
	NL80211_RRF_NO_OUTDOOR		= 1<<3,
	NL80211_RRF_DFS			= 1<<4,
	NL80211_RRF_PTP_ONLY		= 1<<5,
	NL80211_RRF_PTMP_ONLY		= 1<<6,
	NL80211_RRF_NO_IR		= 1<<7,
	__NL80211_RRF_NO_IBSS		= 1<<8,
	NL80211_RRF_AUTO_BW		= 1<<11,
	NL80211_RRF_IR_CONCURRENT	= 1<<12,
	NL80211_RRF_NO_HT40MINUS	= 1<<13,
	NL80211_RRF_NO_HT40PLUS		= 1<<14,
	NL80211_RRF_NO_80MHZ		= 1<<15,
	NL80211_RRF_NO_160MHZ		= 1<<16,
	NL80211_RRF_NO_HE		= 1<<17,
पूर्ण;

#घोषणा NL80211_RRF_PASSIVE_SCAN	NL80211_RRF_NO_IR
#घोषणा NL80211_RRF_NO_IBSS		NL80211_RRF_NO_IR
#घोषणा NL80211_RRF_NO_IR		NL80211_RRF_NO_IR
#घोषणा NL80211_RRF_NO_HT40		(NL80211_RRF_NO_HT40MINUS |\
					 NL80211_RRF_NO_HT40PLUS)
#घोषणा NL80211_RRF_GO_CONCURRENT	NL80211_RRF_IR_CONCURRENT

/* For backport compatibility with older userspace */
#घोषणा NL80211_RRF_NO_IR_ALL		(NL80211_RRF_NO_IR | __NL80211_RRF_NO_IBSS)

/**
 * क्रमागत nl80211_dfs_regions - regulatory DFS regions
 *
 * @NL80211_DFS_UNSET: Country has no DFS master region specअगरied
 * @NL80211_DFS_FCC: Country follows DFS master rules from FCC
 * @NL80211_DFS_ETSI: Country follows DFS master rules from ETSI
 * @NL80211_DFS_JP: Country follows DFS master rules from JP/MKK/Telec
 */
क्रमागत nl80211_dfs_regions अणु
	NL80211_DFS_UNSET	= 0,
	NL80211_DFS_FCC		= 1,
	NL80211_DFS_ETSI	= 2,
	NL80211_DFS_JP		= 3,
पूर्ण;

/**
 * क्रमागत nl80211_user_reg_hपूर्णांक_type - type of user regulatory hपूर्णांक
 *
 * @NL80211_USER_REG_HINT_USER: a user sent the hपूर्णांक. This is always
 *	assumed अगर the attribute is not set.
 * @NL80211_USER_REG_HINT_CELL_BASE: the hपूर्णांक comes from a cellular
 *	base station. Device drivers that have been tested to work
 *	properly to support this type of hपूर्णांक can enable these hपूर्णांकs
 *	by setting the NL80211_FEATURE_CELL_BASE_REG_HINTS feature
 *	capability on the काष्ठा wiphy. The wireless core will
 *	ignore all cell base station hपूर्णांकs until at least one device
 *	present has been रेजिस्टरed with the wireless core that
 *	has listed NL80211_FEATURE_CELL_BASE_REG_HINTS as a
 *	supported feature.
 * @NL80211_USER_REG_HINT_INDOOR: a user sent an hपूर्णांक indicating that the
 *	platक्रमm is operating in an inकरोor environment.
 */
क्रमागत nl80211_user_reg_hपूर्णांक_type अणु
	NL80211_USER_REG_HINT_USER	= 0,
	NL80211_USER_REG_HINT_CELL_BASE = 1,
	NL80211_USER_REG_HINT_INDOOR    = 2,
पूर्ण;

/**
 * क्रमागत nl80211_survey_info - survey inक्रमmation
 *
 * These attribute types are used with %NL80211_ATTR_SURVEY_INFO
 * when getting inक्रमmation about a survey.
 *
 * @__NL80211_SURVEY_INFO_INVALID: attribute number 0 is reserved
 * @NL80211_SURVEY_INFO_FREQUENCY: center frequency of channel
 * @NL80211_SURVEY_INFO_NOISE: noise level of channel (u8, dBm)
 * @NL80211_SURVEY_INFO_IN_USE: channel is currently being used
 * @NL80211_SURVEY_INFO_TIME: amount of समय (in ms) that the radio
 *	was turned on (on channel or globally)
 * @NL80211_SURVEY_INFO_TIME_BUSY: amount of the समय the primary
 *	channel was sensed busy (either due to activity or energy detect)
 * @NL80211_SURVEY_INFO_TIME_EXT_BUSY: amount of समय the extension
 *	channel was sensed busy
 * @NL80211_SURVEY_INFO_TIME_RX: amount of समय the radio spent
 *	receiving data (on channel or globally)
 * @NL80211_SURVEY_INFO_TIME_TX: amount of समय the radio spent
 *	transmitting data (on channel or globally)
 * @NL80211_SURVEY_INFO_TIME_SCAN: समय the radio spent क्रम scan
 *	(on this channel or globally)
 * @NL80211_SURVEY_INFO_PAD: attribute used क्रम padding क्रम 64-bit alignment
 * @NL80211_SURVEY_INFO_TIME_BSS_RX: amount of समय the radio spent
 *	receiving frames destined to the local BSS
 * @NL80211_SURVEY_INFO_MAX: highest survey info attribute number
 *	currently defined
 * @NL80211_SURVEY_INFO_FREQUENCY_OFFSET: center frequency offset in KHz
 * @__NL80211_SURVEY_INFO_AFTER_LAST: पूर्णांकernal use
 */
क्रमागत nl80211_survey_info अणु
	__NL80211_SURVEY_INFO_INVALID,
	NL80211_SURVEY_INFO_FREQUENCY,
	NL80211_SURVEY_INFO_NOISE,
	NL80211_SURVEY_INFO_IN_USE,
	NL80211_SURVEY_INFO_TIME,
	NL80211_SURVEY_INFO_TIME_BUSY,
	NL80211_SURVEY_INFO_TIME_EXT_BUSY,
	NL80211_SURVEY_INFO_TIME_RX,
	NL80211_SURVEY_INFO_TIME_TX,
	NL80211_SURVEY_INFO_TIME_SCAN,
	NL80211_SURVEY_INFO_PAD,
	NL80211_SURVEY_INFO_TIME_BSS_RX,
	NL80211_SURVEY_INFO_FREQUENCY_OFFSET,

	/* keep last */
	__NL80211_SURVEY_INFO_AFTER_LAST,
	NL80211_SURVEY_INFO_MAX = __NL80211_SURVEY_INFO_AFTER_LAST - 1
पूर्ण;

/* keep old names क्रम compatibility */
#घोषणा NL80211_SURVEY_INFO_CHANNEL_TIME		NL80211_SURVEY_INFO_TIME
#घोषणा NL80211_SURVEY_INFO_CHANNEL_TIME_BUSY		NL80211_SURVEY_INFO_TIME_BUSY
#घोषणा NL80211_SURVEY_INFO_CHANNEL_TIME_EXT_BUSY	NL80211_SURVEY_INFO_TIME_EXT_BUSY
#घोषणा NL80211_SURVEY_INFO_CHANNEL_TIME_RX		NL80211_SURVEY_INFO_TIME_RX
#घोषणा NL80211_SURVEY_INFO_CHANNEL_TIME_TX		NL80211_SURVEY_INFO_TIME_TX

/**
 * क्रमागत nl80211_mntr_flags - monitor configuration flags
 *
 * Monitor configuration flags.
 *
 * @__NL80211_MNTR_FLAG_INVALID: reserved
 *
 * @NL80211_MNTR_FLAG_FCSFAIL: pass frames with bad FCS
 * @NL80211_MNTR_FLAG_PLCPFAIL: pass frames with bad PLCP
 * @NL80211_MNTR_FLAG_CONTROL: pass control frames
 * @NL80211_MNTR_FLAG_OTHER_BSS: disable BSSID filtering
 * @NL80211_MNTR_FLAG_COOK_FRAMES: report frames after processing.
 *	overrides all other flags.
 * @NL80211_MNTR_FLAG_ACTIVE: use the configured MAC address
 *	and ACK incoming unicast packets.
 *
 * @__NL80211_MNTR_FLAG_AFTER_LAST: पूर्णांकernal use
 * @NL80211_MNTR_FLAG_MAX: highest possible monitor flag
 */
क्रमागत nl80211_mntr_flags अणु
	__NL80211_MNTR_FLAG_INVALID,
	NL80211_MNTR_FLAG_FCSFAIL,
	NL80211_MNTR_FLAG_PLCPFAIL,
	NL80211_MNTR_FLAG_CONTROL,
	NL80211_MNTR_FLAG_OTHER_BSS,
	NL80211_MNTR_FLAG_COOK_FRAMES,
	NL80211_MNTR_FLAG_ACTIVE,

	/* keep last */
	__NL80211_MNTR_FLAG_AFTER_LAST,
	NL80211_MNTR_FLAG_MAX = __NL80211_MNTR_FLAG_AFTER_LAST - 1
पूर्ण;

/**
 * क्रमागत nl80211_mesh_घातer_mode - mesh घातer save modes
 *
 * @NL80211_MESH_POWER_UNKNOWN: The mesh घातer mode of the mesh STA is
 *	not known or has not been set yet.
 * @NL80211_MESH_POWER_ACTIVE: Active mesh घातer mode. The mesh STA is
 *	in Awake state all the समय.
 * @NL80211_MESH_POWER_LIGHT_SLEEP: Light sleep mode. The mesh STA will
 *	alternate between Active and Doze states, but will wake up क्रम
 *	neighbor's beacons.
 * @NL80211_MESH_POWER_DEEP_SLEEP: Deep sleep mode. The mesh STA will
 *	alternate between Active and Doze states, but may not wake up
 *	क्रम neighbor's beacons.
 *
 * @__NL80211_MESH_POWER_AFTER_LAST - पूर्णांकernal use
 * @NL80211_MESH_POWER_MAX - highest possible घातer save level
 */

क्रमागत nl80211_mesh_घातer_mode अणु
	NL80211_MESH_POWER_UNKNOWN,
	NL80211_MESH_POWER_ACTIVE,
	NL80211_MESH_POWER_LIGHT_SLEEP,
	NL80211_MESH_POWER_DEEP_SLEEP,

	__NL80211_MESH_POWER_AFTER_LAST,
	NL80211_MESH_POWER_MAX = __NL80211_MESH_POWER_AFTER_LAST - 1
पूर्ण;

/**
 * क्रमागत nl80211_meshconf_params - mesh configuration parameters
 *
 * Mesh configuration parameters. These can be changed जबतक the mesh is
 * active.
 *
 * @__NL80211_MESHCONF_INVALID: पूर्णांकernal use
 *
 * @NL80211_MESHCONF_RETRY_TIMEOUT: specअगरies the initial retry समयout in
 *	millisecond units, used by the Peer Link Open message
 *
 * @NL80211_MESHCONF_CONFIRM_TIMEOUT: specअगरies the initial confirm समयout, in
 *	millisecond units, used by the peer link management to बंद a peer link
 *
 * @NL80211_MESHCONF_HOLDING_TIMEOUT: specअगरies the holding समयout, in
 *	millisecond units
 *
 * @NL80211_MESHCONF_MAX_PEER_LINKS: maximum number of peer links allowed
 *	on this mesh पूर्णांकerface
 *
 * @NL80211_MESHCONF_MAX_RETRIES: specअगरies the maximum number of peer link
 *	खोलो retries that can be sent to establish a new peer link instance in a
 *	mesh
 *
 * @NL80211_MESHCONF_TTL: specअगरies the value of TTL field set at a source mesh
 *	poपूर्णांक.
 *
 * @NL80211_MESHCONF_AUTO_OPEN_PLINKS: whether we should स्वतःmatically खोलो
 *	peer links when we detect compatible mesh peers. Disabled अगर
 *	@NL80211_MESH_SETUP_USERSPACE_MPM or @NL80211_MESH_SETUP_USERSPACE_AMPE are
 *	set.
 *
 * @NL80211_MESHCONF_HWMP_MAX_PREQ_RETRIES: the number of action frames
 *	containing a PREQ that an MP can send to a particular destination (path
 *	target)
 *
 * @NL80211_MESHCONF_PATH_REFRESH_TIME: how frequently to refresh mesh paths
 *	(in milliseconds)
 *
 * @NL80211_MESHCONF_MIN_DISCOVERY_TIMEOUT: minimum length of समय to रुको
 *	until giving up on a path discovery (in milliseconds)
 *
 * @NL80211_MESHCONF_HWMP_ACTIVE_PATH_TIMEOUT: The समय (in TUs) क्रम which mesh
 *	poपूर्णांकs receiving a PREQ shall consider the क्रमwarding inक्रमmation from
 *	the root to be valid. (TU = समय unit)
 *
 * @NL80211_MESHCONF_HWMP_PREQ_MIN_INTERVAL: The minimum पूर्णांकerval of समय (in
 *	TUs) during which an MP can send only one action frame containing a PREQ
 *	reference element
 *
 * @NL80211_MESHCONF_HWMP_NET_DIAM_TRVS_TIME: The पूर्णांकerval of समय (in TUs)
 *	that it takes क्रम an HWMP inक्रमmation element to propagate across the
 *	mesh
 *
 * @NL80211_MESHCONF_HWMP_ROOTMODE: whether root mode is enabled or not
 *
 * @NL80211_MESHCONF_ELEMENT_TTL: specअगरies the value of TTL field set at a
 *	source mesh poपूर्णांक क्रम path selection elements.
 *
 * @NL80211_MESHCONF_HWMP_RANN_INTERVAL:  The पूर्णांकerval of समय (in TUs) between
 *	root announcements are transmitted.
 *
 * @NL80211_MESHCONF_GATE_ANNOUNCEMENTS: Advertise that this mesh station has
 *	access to a broader network beyond the MBSS.  This is करोne via Root
 *	Announcement frames.
 *
 * @NL80211_MESHCONF_HWMP_PERR_MIN_INTERVAL: The minimum पूर्णांकerval of समय (in
 *	TUs) during which a mesh STA can send only one Action frame containing a
 *	PERR element.
 *
 * @NL80211_MESHCONF_FORWARDING: set Mesh STA as क्रमwarding or non-क्रमwarding
 *	or क्रमwarding entity (शेष is TRUE - क्रमwarding entity)
 *
 * @NL80211_MESHCONF_RSSI_THRESHOLD: RSSI threshold in dBm. This specअगरies the
 *	threshold क्रम average संकेत strength of candidate station to establish
 *	a peer link.
 *
 * @NL80211_MESHCONF_SYNC_OFFSET_MAX_NEIGHBOR: maximum number of neighbors
 *	to synchronize to क्रम 11s शेष synchronization method
 *	(see 11C.12.2.2)
 *
 * @NL80211_MESHCONF_HT_OPMODE: set mesh HT protection mode.
 *
 * @NL80211_MESHCONF_ATTR_MAX: highest possible mesh configuration attribute
 *
 * @NL80211_MESHCONF_HWMP_PATH_TO_ROOT_TIMEOUT: The समय (in TUs) क्रम
 *	which mesh STAs receiving a proactive PREQ shall consider the क्रमwarding
 *	inक्रमmation to the root mesh STA to be valid.
 *
 * @NL80211_MESHCONF_HWMP_ROOT_INTERVAL: The पूर्णांकerval of समय (in TUs) between
 *	proactive PREQs are transmitted.
 *
 * @NL80211_MESHCONF_HWMP_CONFIRMATION_INTERVAL: The minimum पूर्णांकerval of समय
 *	(in TUs) during which a mesh STA can send only one Action frame
 *	containing a PREQ element क्रम root path confirmation.
 *
 * @NL80211_MESHCONF_POWER_MODE: Default mesh घातer mode क्रम new peer links.
 *	type &क्रमागत nl80211_mesh_घातer_mode (u32)
 *
 * @NL80211_MESHCONF_AWAKE_WINDOW: awake winकरोw duration (in TUs)
 *
 * @NL80211_MESHCONF_PLINK_TIMEOUT: If no tx activity is seen from a STA we've
 *	established peering with क्रम दीर्घer than this समय (in seconds), then
 *	हटाओ it from the STA's list of peers. You may set this to 0 to disable
 *	the removal of the STA. Default is 30 minutes.
 *
 * @NL80211_MESHCONF_CONNECTED_TO_GATE: If set to true then this mesh STA
 *	will advertise that it is connected to a gate in the mesh क्रमmation
 *	field.  If left unset then the mesh क्रमmation field will only
 *	advertise such अगर there is an active root mesh path.
 *
 * @NL80211_MESHCONF_NOLEARN: Try to aव्योम multi-hop path discovery (e.g.
 *      PREQ/PREP क्रम HWMP) अगर the destination is a direct neighbor. Note that
 *      this might not be the optimal decision as a multi-hop route might be
 *      better. So अगर using this setting you will likely also want to disable
 *      करोt11MeshForwarding and use another mesh routing protocol on top.
 *
 * @NL80211_MESHCONF_CONNECTED_TO_AS: If set to true then this mesh STA
 *	will advertise that it is connected to a authentication server
 *	in the mesh क्रमmation field.
 *
 * @__NL80211_MESHCONF_ATTR_AFTER_LAST: पूर्णांकernal use
 */
क्रमागत nl80211_meshconf_params अणु
	__NL80211_MESHCONF_INVALID,
	NL80211_MESHCONF_RETRY_TIMEOUT,
	NL80211_MESHCONF_CONFIRM_TIMEOUT,
	NL80211_MESHCONF_HOLDING_TIMEOUT,
	NL80211_MESHCONF_MAX_PEER_LINKS,
	NL80211_MESHCONF_MAX_RETRIES,
	NL80211_MESHCONF_TTL,
	NL80211_MESHCONF_AUTO_OPEN_PLINKS,
	NL80211_MESHCONF_HWMP_MAX_PREQ_RETRIES,
	NL80211_MESHCONF_PATH_REFRESH_TIME,
	NL80211_MESHCONF_MIN_DISCOVERY_TIMEOUT,
	NL80211_MESHCONF_HWMP_ACTIVE_PATH_TIMEOUT,
	NL80211_MESHCONF_HWMP_PREQ_MIN_INTERVAL,
	NL80211_MESHCONF_HWMP_NET_DIAM_TRVS_TIME,
	NL80211_MESHCONF_HWMP_ROOTMODE,
	NL80211_MESHCONF_ELEMENT_TTL,
	NL80211_MESHCONF_HWMP_RANN_INTERVAL,
	NL80211_MESHCONF_GATE_ANNOUNCEMENTS,
	NL80211_MESHCONF_HWMP_PERR_MIN_INTERVAL,
	NL80211_MESHCONF_FORWARDING,
	NL80211_MESHCONF_RSSI_THRESHOLD,
	NL80211_MESHCONF_SYNC_OFFSET_MAX_NEIGHBOR,
	NL80211_MESHCONF_HT_OPMODE,
	NL80211_MESHCONF_HWMP_PATH_TO_ROOT_TIMEOUT,
	NL80211_MESHCONF_HWMP_ROOT_INTERVAL,
	NL80211_MESHCONF_HWMP_CONFIRMATION_INTERVAL,
	NL80211_MESHCONF_POWER_MODE,
	NL80211_MESHCONF_AWAKE_WINDOW,
	NL80211_MESHCONF_PLINK_TIMEOUT,
	NL80211_MESHCONF_CONNECTED_TO_GATE,
	NL80211_MESHCONF_NOLEARN,
	NL80211_MESHCONF_CONNECTED_TO_AS,

	/* keep last */
	__NL80211_MESHCONF_ATTR_AFTER_LAST,
	NL80211_MESHCONF_ATTR_MAX = __NL80211_MESHCONF_ATTR_AFTER_LAST - 1
पूर्ण;

/**
 * क्रमागत nl80211_mesh_setup_params - mesh setup parameters
 *
 * Mesh setup parameters.  These are used to start/join a mesh and cannot be
 * changed जबतक the mesh is active.
 *
 * @__NL80211_MESH_SETUP_INVALID: Internal use
 *
 * @NL80211_MESH_SETUP_ENABLE_VENDOR_PATH_SEL: Enable this option to use a
 *	venकरोr specअगरic path selection algorithm or disable it to use the
 *	शेष HWMP.
 *
 * @NL80211_MESH_SETUP_ENABLE_VENDOR_METRIC: Enable this option to use a
 *	venकरोr specअगरic path metric or disable it to use the शेष Airसमय
 *	metric.
 *
 * @NL80211_MESH_SETUP_IE: Inक्रमmation elements क्रम this mesh, क्रम instance, a
 *	robust security network ie, or a venकरोr specअगरic inक्रमmation element
 *	that venकरोrs will use to identअगरy the path selection methods and
 *	metrics in use.
 *
 * @NL80211_MESH_SETUP_USERSPACE_AUTH: Enable this option अगर an authentication
 *	daemon will be authenticating mesh candidates.
 *
 * @NL80211_MESH_SETUP_USERSPACE_AMPE: Enable this option अगर an authentication
 *	daemon will be securing peer link frames.  AMPE is a secured version of
 *	Mesh Peering Management (MPM) and is implemented with the assistance of
 *	a userspace daemon.  When this flag is set, the kernel will send peer
 *	management frames to a userspace daemon that will implement AMPE
 *	functionality (security capabilities selection, key confirmation, and
 *	key management).  When the flag is unset (शेष), the kernel can
 *	स्वतःnomously complete (unsecured) mesh peering without the need of a
 *	userspace daemon.
 *
 * @NL80211_MESH_SETUP_ENABLE_VENDOR_SYNC: Enable this option to use a
 *	venकरोr specअगरic synchronization method or disable it to use the शेष
 *	neighbor offset synchronization
 *
 * @NL80211_MESH_SETUP_USERSPACE_MPM: Enable this option अगर userspace will
 *	implement an MPM which handles peer allocation and state.
 *
 * @NL80211_MESH_SETUP_AUTH_PROTOCOL: Inक्रमm the kernel of the authentication
 *	method (u8, as defined in IEEE 8.4.2.100.6, e.g. 0x1 क्रम SAE).
 *	Default is no authentication method required.
 *
 * @NL80211_MESH_SETUP_ATTR_MAX: highest possible mesh setup attribute number
 *
 * @__NL80211_MESH_SETUP_ATTR_AFTER_LAST: Internal use
 */
क्रमागत nl80211_mesh_setup_params अणु
	__NL80211_MESH_SETUP_INVALID,
	NL80211_MESH_SETUP_ENABLE_VENDOR_PATH_SEL,
	NL80211_MESH_SETUP_ENABLE_VENDOR_METRIC,
	NL80211_MESH_SETUP_IE,
	NL80211_MESH_SETUP_USERSPACE_AUTH,
	NL80211_MESH_SETUP_USERSPACE_AMPE,
	NL80211_MESH_SETUP_ENABLE_VENDOR_SYNC,
	NL80211_MESH_SETUP_USERSPACE_MPM,
	NL80211_MESH_SETUP_AUTH_PROTOCOL,

	/* keep last */
	__NL80211_MESH_SETUP_ATTR_AFTER_LAST,
	NL80211_MESH_SETUP_ATTR_MAX = __NL80211_MESH_SETUP_ATTR_AFTER_LAST - 1
पूर्ण;

/**
 * क्रमागत nl80211_txq_attr - TX queue parameter attributes
 * @__NL80211_TXQ_ATTR_INVALID: Attribute number 0 is reserved
 * @NL80211_TXQ_ATTR_AC: AC identअगरier (NL80211_AC_*)
 * @NL80211_TXQ_ATTR_TXOP: Maximum burst समय in units of 32 usecs, 0 meaning
 *	disabled
 * @NL80211_TXQ_ATTR_CWMIN: Minimum contention winकरोw [a value of the क्रमm
 *	2^n-1 in the range 1..32767]
 * @NL80211_TXQ_ATTR_CWMAX: Maximum contention winकरोw [a value of the क्रमm
 *	2^n-1 in the range 1..32767]
 * @NL80211_TXQ_ATTR_AIFS: Arbitration पूर्णांकerframe space [0..255]
 * @__NL80211_TXQ_ATTR_AFTER_LAST: Internal
 * @NL80211_TXQ_ATTR_MAX: Maximum TXQ attribute number
 */
क्रमागत nl80211_txq_attr अणु
	__NL80211_TXQ_ATTR_INVALID,
	NL80211_TXQ_ATTR_AC,
	NL80211_TXQ_ATTR_TXOP,
	NL80211_TXQ_ATTR_CWMIN,
	NL80211_TXQ_ATTR_CWMAX,
	NL80211_TXQ_ATTR_AIFS,

	/* keep last */
	__NL80211_TXQ_ATTR_AFTER_LAST,
	NL80211_TXQ_ATTR_MAX = __NL80211_TXQ_ATTR_AFTER_LAST - 1
पूर्ण;

क्रमागत nl80211_ac अणु
	NL80211_AC_VO,
	NL80211_AC_VI,
	NL80211_AC_BE,
	NL80211_AC_BK,
	NL80211_NUM_ACS
पूर्ण;

/* backward compat */
#घोषणा NL80211_TXQ_ATTR_QUEUE	NL80211_TXQ_ATTR_AC
#घोषणा NL80211_TXQ_Q_VO	NL80211_AC_VO
#घोषणा NL80211_TXQ_Q_VI	NL80211_AC_VI
#घोषणा NL80211_TXQ_Q_BE	NL80211_AC_BE
#घोषणा NL80211_TXQ_Q_BK	NL80211_AC_BK

/**
 * क्रमागत nl80211_channel_type - channel type
 * @NL80211_CHAN_NO_HT: 20 MHz, non-HT channel
 * @NL80211_CHAN_HT20: 20 MHz HT channel
 * @NL80211_CHAN_HT40MINUS: HT40 channel, secondary channel
 *	below the control channel
 * @NL80211_CHAN_HT40PLUS: HT40 channel, secondary channel
 *	above the control channel
 */
क्रमागत nl80211_channel_type अणु
	NL80211_CHAN_NO_HT,
	NL80211_CHAN_HT20,
	NL80211_CHAN_HT40MINUS,
	NL80211_CHAN_HT40PLUS
पूर्ण;

/**
 * क्रमागत nl80211_key_mode - Key mode
 *
 * @NL80211_KEY_RX_TX: (Default)
 *	Key can be used क्रम Rx and Tx immediately
 *
 * The following modes can only be selected क्रम unicast keys and when the
 * driver supports @NL80211_EXT_FEATURE_EXT_KEY_ID:
 *
 * @NL80211_KEY_NO_TX: Only allowed in combination with @NL80211_CMD_NEW_KEY:
 *	Unicast key can only be used क्रम Rx, Tx not allowed, yet
 * @NL80211_KEY_SET_TX: Only allowed in combination with @NL80211_CMD_SET_KEY:
 *	The unicast key identअगरied by idx and mac is cleared क्रम Tx and becomes
 *	the preferred Tx key क्रम the station.
 */
क्रमागत nl80211_key_mode अणु
	NL80211_KEY_RX_TX,
	NL80211_KEY_NO_TX,
	NL80211_KEY_SET_TX
पूर्ण;

/**
 * क्रमागत nl80211_chan_width - channel width definitions
 *
 * These values are used with the %NL80211_ATTR_CHANNEL_WIDTH
 * attribute.
 *
 * @NL80211_CHAN_WIDTH_20_NOHT: 20 MHz, non-HT channel
 * @NL80211_CHAN_WIDTH_20: 20 MHz HT channel
 * @NL80211_CHAN_WIDTH_40: 40 MHz channel, the %NL80211_ATTR_CENTER_FREQ1
 *	attribute must be provided as well
 * @NL80211_CHAN_WIDTH_80: 80 MHz channel, the %NL80211_ATTR_CENTER_FREQ1
 *	attribute must be provided as well
 * @NL80211_CHAN_WIDTH_80P80: 80+80 MHz channel, the %NL80211_ATTR_CENTER_FREQ1
 *	and %NL80211_ATTR_CENTER_FREQ2 attributes must be provided as well
 * @NL80211_CHAN_WIDTH_160: 160 MHz channel, the %NL80211_ATTR_CENTER_FREQ1
 *	attribute must be provided as well
 * @NL80211_CHAN_WIDTH_5: 5 MHz OFDM channel
 * @NL80211_CHAN_WIDTH_10: 10 MHz OFDM channel
 * @NL80211_CHAN_WIDTH_1: 1 MHz OFDM channel
 * @NL80211_CHAN_WIDTH_2: 2 MHz OFDM channel
 * @NL80211_CHAN_WIDTH_4: 4 MHz OFDM channel
 * @NL80211_CHAN_WIDTH_8: 8 MHz OFDM channel
 * @NL80211_CHAN_WIDTH_16: 16 MHz OFDM channel
 */
क्रमागत nl80211_chan_width अणु
	NL80211_CHAN_WIDTH_20_NOHT,
	NL80211_CHAN_WIDTH_20,
	NL80211_CHAN_WIDTH_40,
	NL80211_CHAN_WIDTH_80,
	NL80211_CHAN_WIDTH_80P80,
	NL80211_CHAN_WIDTH_160,
	NL80211_CHAN_WIDTH_5,
	NL80211_CHAN_WIDTH_10,
	NL80211_CHAN_WIDTH_1,
	NL80211_CHAN_WIDTH_2,
	NL80211_CHAN_WIDTH_4,
	NL80211_CHAN_WIDTH_8,
	NL80211_CHAN_WIDTH_16,
पूर्ण;

/**
 * क्रमागत nl80211_bss_scan_width - control channel width क्रम a BSS
 *
 * These values are used with the %NL80211_BSS_CHAN_WIDTH attribute.
 *
 * @NL80211_BSS_CHAN_WIDTH_20: control channel is 20 MHz wide or compatible
 * @NL80211_BSS_CHAN_WIDTH_10: control channel is 10 MHz wide
 * @NL80211_BSS_CHAN_WIDTH_5: control channel is 5 MHz wide
 * @NL80211_BSS_CHAN_WIDTH_1: control channel is 1 MHz wide
 * @NL80211_BSS_CHAN_WIDTH_2: control channel is 2 MHz wide
 */
क्रमागत nl80211_bss_scan_width अणु
	NL80211_BSS_CHAN_WIDTH_20,
	NL80211_BSS_CHAN_WIDTH_10,
	NL80211_BSS_CHAN_WIDTH_5,
	NL80211_BSS_CHAN_WIDTH_1,
	NL80211_BSS_CHAN_WIDTH_2,
पूर्ण;

/**
 * क्रमागत nl80211_bss - netlink attributes क्रम a BSS
 *
 * @__NL80211_BSS_INVALID: invalid
 * @NL80211_BSS_BSSID: BSSID of the BSS (6 octets)
 * @NL80211_BSS_FREQUENCY: frequency in MHz (u32)
 * @NL80211_BSS_TSF: TSF of the received probe response/beacon (u64)
 *	(अगर @NL80211_BSS_PRESP_DATA is present then this is known to be
 *	from a probe response, otherwise it may be from the same beacon
 *	that the NL80211_BSS_BEACON_TSF will be from)
 * @NL80211_BSS_BEACON_INTERVAL: beacon पूर्णांकerval of the (I)BSS (u16)
 * @NL80211_BSS_CAPABILITY: capability field (CPU order, u16)
 * @NL80211_BSS_INFORMATION_ELEMENTS: binary attribute containing the
 *	raw inक्रमmation elements from the probe response/beacon (bin);
 *	अगर the %NL80211_BSS_BEACON_IES attribute is present and the data is
 *	dअगरferent then the IEs here are from a Probe Response frame; otherwise
 *	they are from a Beacon frame.
 *	However, अगर the driver करोes not indicate the source of the IEs, these
 *	IEs may be from either frame subtype.
 *	If present, the @NL80211_BSS_PRESP_DATA attribute indicates that the
 *	data here is known to be from a probe response, without any heuristics.
 * @NL80211_BSS_SIGNAL_MBM: संकेत strength of probe response/beacon
 *	in mBm (100 * dBm) (s32)
 * @NL80211_BSS_SIGNAL_UNSPEC: संकेत strength of the probe response/beacon
 *	in unspecअगरied units, scaled to 0..100 (u8)
 * @NL80211_BSS_STATUS: status, अगर this BSS is "used"
 * @NL80211_BSS_SEEN_MS_AGO: age of this BSS entry in ms
 * @NL80211_BSS_BEACON_IES: binary attribute containing the raw inक्रमmation
 *	elements from a Beacon frame (bin); not present अगर no Beacon frame has
 *	yet been received
 * @NL80211_BSS_CHAN_WIDTH: channel width of the control channel
 *	(u32, क्रमागत nl80211_bss_scan_width)
 * @NL80211_BSS_BEACON_TSF: TSF of the last received beacon (u64)
 *	(not present अगर no beacon frame has been received yet)
 * @NL80211_BSS_PRESP_DATA: the data in @NL80211_BSS_INFORMATION_ELEMENTS and
 *	@NL80211_BSS_TSF is known to be from a probe response (flag attribute)
 * @NL80211_BSS_LAST_SEEN_BOOTTIME: CLOCK_BOOTTIME बारtamp when this entry
 *	was last updated by a received frame. The value is expected to be
 *	accurate to about 10ms. (u64, nanoseconds)
 * @NL80211_BSS_PAD: attribute used क्रम padding क्रम 64-bit alignment
 * @NL80211_BSS_PARENT_TSF: the समय at the start of reception of the first
 *	octet of the बारtamp field of the last beacon/probe received क्रम
 *	this BSS. The समय is the TSF of the BSS specअगरied by
 *	@NL80211_BSS_PARENT_BSSID. (u64).
 * @NL80211_BSS_PARENT_BSSID: the BSS according to which @NL80211_BSS_PARENT_TSF
 *	is set.
 * @NL80211_BSS_CHAIN_SIGNAL: per-chain संकेत strength of last BSS update.
 *	Contains a nested array of संकेत strength attributes (u8, dBm),
 *	using the nesting index as the antenna number.
 * @NL80211_BSS_FREQUENCY_OFFSET: frequency offset in KHz
 * @__NL80211_BSS_AFTER_LAST: पूर्णांकernal
 * @NL80211_BSS_MAX: highest BSS attribute
 */
क्रमागत nl80211_bss अणु
	__NL80211_BSS_INVALID,
	NL80211_BSS_BSSID,
	NL80211_BSS_FREQUENCY,
	NL80211_BSS_TSF,
	NL80211_BSS_BEACON_INTERVAL,
	NL80211_BSS_CAPABILITY,
	NL80211_BSS_INFORMATION_ELEMENTS,
	NL80211_BSS_SIGNAL_MBM,
	NL80211_BSS_SIGNAL_UNSPEC,
	NL80211_BSS_STATUS,
	NL80211_BSS_SEEN_MS_AGO,
	NL80211_BSS_BEACON_IES,
	NL80211_BSS_CHAN_WIDTH,
	NL80211_BSS_BEACON_TSF,
	NL80211_BSS_PRESP_DATA,
	NL80211_BSS_LAST_SEEN_BOOTTIME,
	NL80211_BSS_PAD,
	NL80211_BSS_PARENT_TSF,
	NL80211_BSS_PARENT_BSSID,
	NL80211_BSS_CHAIN_SIGNAL,
	NL80211_BSS_FREQUENCY_OFFSET,

	/* keep last */
	__NL80211_BSS_AFTER_LAST,
	NL80211_BSS_MAX = __NL80211_BSS_AFTER_LAST - 1
पूर्ण;

/**
 * क्रमागत nl80211_bss_status - BSS "status"
 * @NL80211_BSS_STATUS_AUTHENTICATED: Authenticated with this BSS.
 *	Note that this is no दीर्घer used since cfg80211 no दीर्घer
 *	keeps track of whether or not authentication was करोne with
 *	a given BSS.
 * @NL80211_BSS_STATUS_ASSOCIATED: Associated with this BSS.
 * @NL80211_BSS_STATUS_IBSS_JOINED: Joined to this IBSS.
 *
 * The BSS status is a BSS attribute in scan dumps, which
 * indicates the status the पूर्णांकerface has wrt. this BSS.
 */
क्रमागत nl80211_bss_status अणु
	NL80211_BSS_STATUS_AUTHENTICATED,
	NL80211_BSS_STATUS_ASSOCIATED,
	NL80211_BSS_STATUS_IBSS_JOINED,
पूर्ण;

/**
 * क्रमागत nl80211_auth_type - AuthenticationType
 *
 * @NL80211_AUTHTYPE_OPEN_SYSTEM: Open System authentication
 * @NL80211_AUTHTYPE_SHARED_KEY: Shared Key authentication (WEP only)
 * @NL80211_AUTHTYPE_FT: Fast BSS Transition (IEEE 802.11r)
 * @NL80211_AUTHTYPE_NETWORK_EAP: Network EAP (some Cisco APs and मुख्यly LEAP)
 * @NL80211_AUTHTYPE_SAE: Simultaneous authentication of equals
 * @NL80211_AUTHTYPE_FILS_SK: Fast Initial Link Setup shared key
 * @NL80211_AUTHTYPE_FILS_SK_PFS: Fast Initial Link Setup shared key with PFS
 * @NL80211_AUTHTYPE_FILS_PK: Fast Initial Link Setup खुला key
 * @__NL80211_AUTHTYPE_NUM: पूर्णांकernal
 * @NL80211_AUTHTYPE_MAX: maximum valid auth algorithm
 * @NL80211_AUTHTYPE_AUTOMATIC: determine स्वतःmatically (अगर necessary by
 *	trying multiple बार); this is invalid in netlink -- leave out
 *	the attribute क्रम this on CONNECT commands.
 */
क्रमागत nl80211_auth_type अणु
	NL80211_AUTHTYPE_OPEN_SYSTEM,
	NL80211_AUTHTYPE_SHARED_KEY,
	NL80211_AUTHTYPE_FT,
	NL80211_AUTHTYPE_NETWORK_EAP,
	NL80211_AUTHTYPE_SAE,
	NL80211_AUTHTYPE_FILS_SK,
	NL80211_AUTHTYPE_FILS_SK_PFS,
	NL80211_AUTHTYPE_FILS_PK,

	/* keep last */
	__NL80211_AUTHTYPE_NUM,
	NL80211_AUTHTYPE_MAX = __NL80211_AUTHTYPE_NUM - 1,
	NL80211_AUTHTYPE_AUTOMATIC
पूर्ण;

/**
 * क्रमागत nl80211_key_type - Key Type
 * @NL80211_KEYTYPE_GROUP: Group (broadcast/multicast) key
 * @NL80211_KEYTYPE_PAIRWISE: Pairwise (unicast/inभागidual) key
 * @NL80211_KEYTYPE_PEERKEY: PeerKey (DLS)
 * @NUM_NL80211_KEYTYPES: number of defined key types
 */
क्रमागत nl80211_key_type अणु
	NL80211_KEYTYPE_GROUP,
	NL80211_KEYTYPE_PAIRWISE,
	NL80211_KEYTYPE_PEERKEY,

	NUM_NL80211_KEYTYPES
पूर्ण;

/**
 * क्रमागत nl80211_mfp - Management frame protection state
 * @NL80211_MFP_NO: Management frame protection not used
 * @NL80211_MFP_REQUIRED: Management frame protection required
 * @NL80211_MFP_OPTIONAL: Management frame protection is optional
 */
क्रमागत nl80211_mfp अणु
	NL80211_MFP_NO,
	NL80211_MFP_REQUIRED,
	NL80211_MFP_OPTIONAL,
पूर्ण;

क्रमागत nl80211_wpa_versions अणु
	NL80211_WPA_VERSION_1 = 1 << 0,
	NL80211_WPA_VERSION_2 = 1 << 1,
	NL80211_WPA_VERSION_3 = 1 << 2,
पूर्ण;

/**
 * क्रमागत nl80211_key_शेष_types - key शेष types
 * @__NL80211_KEY_DEFAULT_TYPE_INVALID: invalid
 * @NL80211_KEY_DEFAULT_TYPE_UNICAST: key should be used as शेष
 *	unicast key
 * @NL80211_KEY_DEFAULT_TYPE_MULTICAST: key should be used as शेष
 *	multicast key
 * @NUM_NL80211_KEY_DEFAULT_TYPES: number of शेष types
 */
क्रमागत nl80211_key_शेष_types अणु
	__NL80211_KEY_DEFAULT_TYPE_INVALID,
	NL80211_KEY_DEFAULT_TYPE_UNICAST,
	NL80211_KEY_DEFAULT_TYPE_MULTICAST,

	NUM_NL80211_KEY_DEFAULT_TYPES
पूर्ण;

/**
 * क्रमागत nl80211_key_attributes - key attributes
 * @__NL80211_KEY_INVALID: invalid
 * @NL80211_KEY_DATA: (temporal) key data; क्रम TKIP this consists of
 *	16 bytes encryption key followed by 8 bytes each क्रम TX and RX MIC
 *	keys
 * @NL80211_KEY_IDX: key ID (u8, 0-3)
 * @NL80211_KEY_CIPHER: key cipher suite (u32, as defined by IEEE 802.11
 *	section 7.3.2.25.1, e.g. 0x000FAC04)
 * @NL80211_KEY_SEQ: transmit key sequence number (IV/PN) क्रम TKIP and
 *	CCMP keys, each six bytes in little endian
 * @NL80211_KEY_DEFAULT: flag indicating शेष key
 * @NL80211_KEY_DEFAULT_MGMT: flag indicating शेष management key
 * @NL80211_KEY_TYPE: the key type from क्रमागत nl80211_key_type, अगर not
 *	specअगरied the शेष depends on whether a MAC address was
 *	given with the command using the key or not (u32)
 * @NL80211_KEY_DEFAULT_TYPES: A nested attribute containing flags
 *	attributes, specअगरying what a key should be set as शेष as.
 *	See &क्रमागत nl80211_key_शेष_types.
 * @NL80211_KEY_MODE: the mode from क्रमागत nl80211_key_mode.
 *	Defaults to @NL80211_KEY_RX_TX.
 * @NL80211_KEY_DEFAULT_BEACON: flag indicating शेष Beacon frame key
 *
 * @__NL80211_KEY_AFTER_LAST: पूर्णांकernal
 * @NL80211_KEY_MAX: highest key attribute
 */
क्रमागत nl80211_key_attributes अणु
	__NL80211_KEY_INVALID,
	NL80211_KEY_DATA,
	NL80211_KEY_IDX,
	NL80211_KEY_CIPHER,
	NL80211_KEY_SEQ,
	NL80211_KEY_DEFAULT,
	NL80211_KEY_DEFAULT_MGMT,
	NL80211_KEY_TYPE,
	NL80211_KEY_DEFAULT_TYPES,
	NL80211_KEY_MODE,
	NL80211_KEY_DEFAULT_BEACON,

	/* keep last */
	__NL80211_KEY_AFTER_LAST,
	NL80211_KEY_MAX = __NL80211_KEY_AFTER_LAST - 1
पूर्ण;

/**
 * क्रमागत nl80211_tx_rate_attributes - TX rate set attributes
 * @__NL80211_TXRATE_INVALID: invalid
 * @NL80211_TXRATE_LEGACY: Legacy (non-MCS) rates allowed क्रम TX rate selection
 *	in an array of rates as defined in IEEE 802.11 7.3.2.2 (u8 values with
 *	1 = 500 kbps) but without the IE length restriction (at most
 *	%NL80211_MAX_SUPP_RATES in a single array).
 * @NL80211_TXRATE_HT: HT (MCS) rates allowed क्रम TX rate selection
 *	in an array of MCS numbers.
 * @NL80211_TXRATE_VHT: VHT rates allowed क्रम TX rate selection,
 *	see &काष्ठा nl80211_txrate_vht
 * @NL80211_TXRATE_GI: configure GI, see &क्रमागत nl80211_txrate_gi
 * @NL80211_TXRATE_HE: HE rates allowed क्रम TX rate selection,
 *	see &काष्ठा nl80211_txrate_he
 * @NL80211_TXRATE_HE_GI: configure HE GI, 0.8us, 1.6us and 3.2us.
 * @NL80211_TXRATE_HE_LTF: configure HE LTF, 1XLTF, 2XLTF and 4XLTF.
 * @__NL80211_TXRATE_AFTER_LAST: पूर्णांकernal
 * @NL80211_TXRATE_MAX: highest TX rate attribute
 */
क्रमागत nl80211_tx_rate_attributes अणु
	__NL80211_TXRATE_INVALID,
	NL80211_TXRATE_LEGACY,
	NL80211_TXRATE_HT,
	NL80211_TXRATE_VHT,
	NL80211_TXRATE_GI,
	NL80211_TXRATE_HE,
	NL80211_TXRATE_HE_GI,
	NL80211_TXRATE_HE_LTF,

	/* keep last */
	__NL80211_TXRATE_AFTER_LAST,
	NL80211_TXRATE_MAX = __NL80211_TXRATE_AFTER_LAST - 1
पूर्ण;

#घोषणा NL80211_TXRATE_MCS NL80211_TXRATE_HT
#घोषणा NL80211_VHT_NSS_MAX		8

/**
 * काष्ठा nl80211_txrate_vht - VHT MCS/NSS txrate biपंचांगap
 * @mcs: MCS biपंचांगap table क्रम each NSS (array index 0 क्रम 1 stream, etc.)
 */
काष्ठा nl80211_txrate_vht अणु
	__u16 mcs[NL80211_VHT_NSS_MAX];
पूर्ण;

#घोषणा NL80211_HE_NSS_MAX		8
/**
 * काष्ठा nl80211_txrate_he - HE MCS/NSS txrate biपंचांगap
 * @mcs: MCS biपंचांगap table क्रम each NSS (array index 0 क्रम 1 stream, etc.)
 */
काष्ठा nl80211_txrate_he अणु
	__u16 mcs[NL80211_HE_NSS_MAX];
पूर्ण;

क्रमागत nl80211_txrate_gi अणु
	NL80211_TXRATE_DEFAULT_GI,
	NL80211_TXRATE_FORCE_SGI,
	NL80211_TXRATE_FORCE_LGI,
पूर्ण;

/**
 * क्रमागत nl80211_band - Frequency band
 * @NL80211_BAND_2GHZ: 2.4 GHz ISM band
 * @NL80211_BAND_5GHZ: around 5 GHz band (4.9 - 5.7 GHz)
 * @NL80211_BAND_60GHZ: around 60 GHz band (58.32 - 69.12 GHz)
 * @NL80211_BAND_6GHZ: around 6 GHz band (5.9 - 7.2 GHz)
 * @NL80211_BAND_S1GHZ: around 900MHz, supported by S1G PHYs
 * @NUM_NL80211_BANDS: number of bands, aव्योम using this in userspace
 *	since newer kernel versions may support more bands
 */
क्रमागत nl80211_band अणु
	NL80211_BAND_2GHZ,
	NL80211_BAND_5GHZ,
	NL80211_BAND_60GHZ,
	NL80211_BAND_6GHZ,
	NL80211_BAND_S1GHZ,

	NUM_NL80211_BANDS,
पूर्ण;

/**
 * क्रमागत nl80211_ps_state - घातersave state
 * @NL80211_PS_DISABLED: घातersave is disabled
 * @NL80211_PS_ENABLED: घातersave is enabled
 */
क्रमागत nl80211_ps_state अणु
	NL80211_PS_DISABLED,
	NL80211_PS_ENABLED,
पूर्ण;

/**
 * क्रमागत nl80211_attr_cqm - connection quality monitor attributes
 * @__NL80211_ATTR_CQM_INVALID: invalid
 * @NL80211_ATTR_CQM_RSSI_THOLD: RSSI threshold in dBm. This value specअगरies
 *	the threshold क्रम the RSSI level at which an event will be sent. Zero
 *	to disable.  Alternatively, अगर %NL80211_EXT_FEATURE_CQM_RSSI_LIST is
 *	set, multiple values can be supplied as a low-to-high sorted array of
 *	threshold values in dBm.  Events will be sent when the RSSI value
 *	crosses any of the thresholds.
 * @NL80211_ATTR_CQM_RSSI_HYST: RSSI hysteresis in dBm. This value specअगरies
 *	the minimum amount the RSSI level must change after an event beक्रमe a
 *	new event may be issued (to reduce effects of RSSI oscillation).
 * @NL80211_ATTR_CQM_RSSI_THRESHOLD_EVENT: RSSI threshold event
 * @NL80211_ATTR_CQM_PKT_LOSS_EVENT: a u32 value indicating that this many
 *	consecutive packets were not acknowledged by the peer
 * @NL80211_ATTR_CQM_TXE_RATE: TX error rate in %. Minimum % of TX failures
 *	during the given %NL80211_ATTR_CQM_TXE_INTVL beक्रमe an
 *	%NL80211_CMD_NOTIFY_CQM with reported %NL80211_ATTR_CQM_TXE_RATE and
 *	%NL80211_ATTR_CQM_TXE_PKTS is generated.
 * @NL80211_ATTR_CQM_TXE_PKTS: number of attempted packets in a given
 *	%NL80211_ATTR_CQM_TXE_INTVL beक्रमe %NL80211_ATTR_CQM_TXE_RATE is
 *	checked.
 * @NL80211_ATTR_CQM_TXE_INTVL: पूर्णांकerval in seconds. Specअगरies the periodic
 *	पूर्णांकerval in which %NL80211_ATTR_CQM_TXE_PKTS and
 *	%NL80211_ATTR_CQM_TXE_RATE must be satisfied beक्रमe generating an
 *	%NL80211_CMD_NOTIFY_CQM. Set to 0 to turn off TX error reporting.
 * @NL80211_ATTR_CQM_BEACON_LOSS_EVENT: flag attribute that's set in a beacon
 *	loss event
 * @NL80211_ATTR_CQM_RSSI_LEVEL: the RSSI value in dBm that triggered the
 *	RSSI threshold event.
 * @__NL80211_ATTR_CQM_AFTER_LAST: पूर्णांकernal
 * @NL80211_ATTR_CQM_MAX: highest key attribute
 */
क्रमागत nl80211_attr_cqm अणु
	__NL80211_ATTR_CQM_INVALID,
	NL80211_ATTR_CQM_RSSI_THOLD,
	NL80211_ATTR_CQM_RSSI_HYST,
	NL80211_ATTR_CQM_RSSI_THRESHOLD_EVENT,
	NL80211_ATTR_CQM_PKT_LOSS_EVENT,
	NL80211_ATTR_CQM_TXE_RATE,
	NL80211_ATTR_CQM_TXE_PKTS,
	NL80211_ATTR_CQM_TXE_INTVL,
	NL80211_ATTR_CQM_BEACON_LOSS_EVENT,
	NL80211_ATTR_CQM_RSSI_LEVEL,

	/* keep last */
	__NL80211_ATTR_CQM_AFTER_LAST,
	NL80211_ATTR_CQM_MAX = __NL80211_ATTR_CQM_AFTER_LAST - 1
पूर्ण;

/**
 * क्रमागत nl80211_cqm_rssi_threshold_event - RSSI threshold event
 * @NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW: The RSSI level is lower than the
 *      configured threshold
 * @NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH: The RSSI is higher than the
 *      configured threshold
 * @NL80211_CQM_RSSI_BEACON_LOSS_EVENT: (reserved, never sent)
 */
क्रमागत nl80211_cqm_rssi_threshold_event अणु
	NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW,
	NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH,
	NL80211_CQM_RSSI_BEACON_LOSS_EVENT,
पूर्ण;


/**
 * क्रमागत nl80211_tx_घातer_setting - TX घातer adjusपंचांगent
 * @NL80211_TX_POWER_AUTOMATIC: स्वतःmatically determine transmit घातer
 * @NL80211_TX_POWER_LIMITED: limit TX घातer by the mBm parameter
 * @NL80211_TX_POWER_FIXED: fix TX घातer to the mBm parameter
 */
क्रमागत nl80211_tx_घातer_setting अणु
	NL80211_TX_POWER_AUTOMATIC,
	NL80211_TX_POWER_LIMITED,
	NL80211_TX_POWER_FIXED,
पूर्ण;

/**
 * क्रमागत nl80211_tid_config - TID config state
 * @NL80211_TID_CONFIG_ENABLE: Enable config क्रम the TID
 * @NL80211_TID_CONFIG_DISABLE: Disable config क्रम the TID
 */
क्रमागत nl80211_tid_config अणु
	NL80211_TID_CONFIG_ENABLE,
	NL80211_TID_CONFIG_DISABLE,
पूर्ण;

/* क्रमागत nl80211_tx_rate_setting - TX rate configuration type
 * @NL80211_TX_RATE_AUTOMATIC: स्वतःmatically determine TX rate
 * @NL80211_TX_RATE_LIMITED: limit the TX rate by the TX rate parameter
 * @NL80211_TX_RATE_FIXED: fix TX rate to the TX rate parameter
 */
क्रमागत nl80211_tx_rate_setting अणु
	NL80211_TX_RATE_AUTOMATIC,
	NL80211_TX_RATE_LIMITED,
	NL80211_TX_RATE_FIXED,
पूर्ण;

/* क्रमागत nl80211_tid_config_attr - TID specअगरic configuration.
 * @NL80211_TID_CONFIG_ATTR_PAD: pad attribute क्रम 64-bit values
 * @NL80211_TID_CONFIG_ATTR_VIF_SUPP: a biपंचांगap (u64) of attributes supported
 *	क्रम per-vअगर configuration; करोesn't list the ones that are generic
 *	(%NL80211_TID_CONFIG_ATTR_TIDS, %NL80211_TID_CONFIG_ATTR_OVERRIDE).
 * @NL80211_TID_CONFIG_ATTR_PEER_SUPP: same as the previous per-vअगर one, but
 *	per peer instead.
 * @NL80211_TID_CONFIG_ATTR_OVERRIDE: flag attribue, अगर set indicates
 *	that the new configuration overrides all previous peer
 *	configurations, otherwise previous peer specअगरic configurations
 *	should be left untouched.
 * @NL80211_TID_CONFIG_ATTR_TIDS: a biपंचांगask value of TIDs (bit 0 to 7)
 *	Its type is u16.
 * @NL80211_TID_CONFIG_ATTR_NOACK: Configure ack policy क्रम the TID.
 *	specअगरied in %NL80211_TID_CONFIG_ATTR_TID. see %क्रमागत nl80211_tid_config.
 *	Its type is u8.
 * @NL80211_TID_CONFIG_ATTR_RETRY_SHORT: Number of retries used with data frame
 *	transmission, user-space sets this configuration in
 *	&NL80211_CMD_SET_TID_CONFIG. It is u8 type, min value is 1 and
 *	the max value is advertised by the driver in this attribute on
 *	output in wiphy capabilities.
 * @NL80211_TID_CONFIG_ATTR_RETRY_LONG: Number of retries used with data frame
 *	transmission, user-space sets this configuration in
 *	&NL80211_CMD_SET_TID_CONFIG. Its type is u8, min value is 1 and
 *	the max value is advertised by the driver in this attribute on
 *	output in wiphy capabilities.
 * @NL80211_TID_CONFIG_ATTR_AMPDU_CTRL: Enable/Disable MPDU aggregation
 *	क्रम the TIDs specअगरied in %NL80211_TID_CONFIG_ATTR_TIDS.
 *	Its type is u8, using the values from &nl80211_tid_config.
 * @NL80211_TID_CONFIG_ATTR_RTSCTS_CTRL: Enable/Disable RTS_CTS क्रम the TIDs
 *	specअगरied in %NL80211_TID_CONFIG_ATTR_TIDS. It is u8 type, using
 *	the values from &nl80211_tid_config.
 * @NL80211_TID_CONFIG_ATTR_AMSDU_CTRL: Enable/Disable MSDU aggregation
 *	क्रम the TIDs specअगरied in %NL80211_TID_CONFIG_ATTR_TIDS.
 *	Its type is u8, using the values from &nl80211_tid_config.
 * @NL80211_TID_CONFIG_ATTR_TX_RATE_TYPE: This attribute will be useful
 *	to notfiy the driver that what type of txrate should be used
 *	क्रम the TIDs specअगरied in %NL80211_TID_CONFIG_ATTR_TIDS. using
 *	the values क्रमm &nl80211_tx_rate_setting.
 * @NL80211_TID_CONFIG_ATTR_TX_RATE: Data frame TX rate mask should be applied
 *	with the parameters passed through %NL80211_ATTR_TX_RATES.
 *	configuration is applied to the data frame क्रम the tid to that connected
 *	station.
 */
क्रमागत nl80211_tid_config_attr अणु
	__NL80211_TID_CONFIG_ATTR_INVALID,
	NL80211_TID_CONFIG_ATTR_PAD,
	NL80211_TID_CONFIG_ATTR_VIF_SUPP,
	NL80211_TID_CONFIG_ATTR_PEER_SUPP,
	NL80211_TID_CONFIG_ATTR_OVERRIDE,
	NL80211_TID_CONFIG_ATTR_TIDS,
	NL80211_TID_CONFIG_ATTR_NOACK,
	NL80211_TID_CONFIG_ATTR_RETRY_SHORT,
	NL80211_TID_CONFIG_ATTR_RETRY_LONG,
	NL80211_TID_CONFIG_ATTR_AMPDU_CTRL,
	NL80211_TID_CONFIG_ATTR_RTSCTS_CTRL,
	NL80211_TID_CONFIG_ATTR_AMSDU_CTRL,
	NL80211_TID_CONFIG_ATTR_TX_RATE_TYPE,
	NL80211_TID_CONFIG_ATTR_TX_RATE,

	/* keep last */
	__NL80211_TID_CONFIG_ATTR_AFTER_LAST,
	NL80211_TID_CONFIG_ATTR_MAX = __NL80211_TID_CONFIG_ATTR_AFTER_LAST - 1
पूर्ण;

/**
 * क्रमागत nl80211_packet_pattern_attr - packet pattern attribute
 * @__NL80211_PKTPAT_INVALID: invalid number क्रम nested attribute
 * @NL80211_PKTPAT_PATTERN: the pattern, values where the mask has
 *	a zero bit are ignored
 * @NL80211_PKTPAT_MASK: pattern mask, must be दीर्घ enough to have
 *	a bit क्रम each byte in the pattern. The lowest-order bit corresponds
 *	to the first byte of the pattern, but the bytes of the pattern are
 *	in a little-endian-like क्रमmat, i.e. the 9th byte of the pattern
 *	corresponds to the lowest-order bit in the second byte of the mask.
 *	For example: The match 00:xx:00:00:xx:00:00:00:00:xx:xx:xx (where
 *	xx indicates "don't care") would be represented by a pattern of
 *	twelve zero bytes, and a mask of "0xed,0x01".
 *	Note that the pattern matching is करोne as though frames were not
 *	802.11 frames but 802.3 frames, i.e. the frame is fully unpacked
 *	first (including SNAP header unpacking) and then matched.
 * @NL80211_PKTPAT_OFFSET: packet offset, pattern is matched after
 *	these fixed number of bytes of received packet
 * @NUM_NL80211_PKTPAT: number of attributes
 * @MAX_NL80211_PKTPAT: max attribute number
 */
क्रमागत nl80211_packet_pattern_attr अणु
	__NL80211_PKTPAT_INVALID,
	NL80211_PKTPAT_MASK,
	NL80211_PKTPAT_PATTERN,
	NL80211_PKTPAT_OFFSET,

	NUM_NL80211_PKTPAT,
	MAX_NL80211_PKTPAT = NUM_NL80211_PKTPAT - 1,
पूर्ण;

/**
 * काष्ठा nl80211_pattern_support - packet pattern support inक्रमmation
 * @max_patterns: maximum number of patterns supported
 * @min_pattern_len: minimum length of each pattern
 * @max_pattern_len: maximum length of each pattern
 * @max_pkt_offset: maximum Rx packet offset
 *
 * This काष्ठा is carried in %NL80211_WOWLAN_TRIG_PKT_PATTERN when
 * that is part of %NL80211_ATTR_WOWLAN_TRIGGERS_SUPPORTED or in
 * %NL80211_ATTR_COALESCE_RULE_PKT_PATTERN when that is part of
 * %NL80211_ATTR_COALESCE_RULE in the capability inक्रमmation given
 * by the kernel to userspace.
 */
काष्ठा nl80211_pattern_support अणु
	__u32 max_patterns;
	__u32 min_pattern_len;
	__u32 max_pattern_len;
	__u32 max_pkt_offset;
पूर्ण __attribute__((packed));

/* only क्रम backward compatibility */
#घोषणा __NL80211_WOWLAN_PKTPAT_INVALID __NL80211_PKTPAT_INVALID
#घोषणा NL80211_WOWLAN_PKTPAT_MASK NL80211_PKTPAT_MASK
#घोषणा NL80211_WOWLAN_PKTPAT_PATTERN NL80211_PKTPAT_PATTERN
#घोषणा NL80211_WOWLAN_PKTPAT_OFFSET NL80211_PKTPAT_OFFSET
#घोषणा NUM_NL80211_WOWLAN_PKTPAT NUM_NL80211_PKTPAT
#घोषणा MAX_NL80211_WOWLAN_PKTPAT MAX_NL80211_PKTPAT
#घोषणा nl80211_wowlan_pattern_support nl80211_pattern_support

/**
 * क्रमागत nl80211_wowlan_triggers - WoWLAN trigger definitions
 * @__NL80211_WOWLAN_TRIG_INVALID: invalid number क्रम nested attributes
 * @NL80211_WOWLAN_TRIG_ANY: wake up on any activity, करो not really put
 *	the chip पूर्णांकo a special state -- works best with chips that have
 *	support क्रम low-घातer operation alपढ़ोy (flag)
 *	Note that this mode is incompatible with all of the others, अगर
 *	any others are even supported by the device.
 * @NL80211_WOWLAN_TRIG_DISCONNECT: wake up on disconnect, the way disconnect
 *	is detected is implementation-specअगरic (flag)
 * @NL80211_WOWLAN_TRIG_MAGIC_PKT: wake up on magic packet (6x 0xff, followed
 *	by 16 repetitions of MAC addr, anywhere in payload) (flag)
 * @NL80211_WOWLAN_TRIG_PKT_PATTERN: wake up on the specअगरied packet patterns
 *	which are passed in an array of nested attributes, each nested attribute
 *	defining a with attributes from &काष्ठा nl80211_wowlan_trig_pkt_pattern.
 *	Each pattern defines a wakeup packet. Packet offset is associated with
 *	each pattern which is used जबतक matching the pattern. The matching is
 *	करोne on the MSDU, i.e. as though the packet was an 802.3 packet, so the
 *	pattern matching is करोne after the packet is converted to the MSDU.
 *
 *	In %NL80211_ATTR_WOWLAN_TRIGGERS_SUPPORTED, it is a binary attribute
 *	carrying a &काष्ठा nl80211_pattern_support.
 *
 *	When reporting wakeup. it is a u32 attribute containing the 0-based
 *	index of the pattern that caused the wakeup, in the patterns passed
 *	to the kernel when configuring.
 * @NL80211_WOWLAN_TRIG_GTK_REKEY_SUPPORTED: Not a real trigger, and cannot be
 *	used when setting, used only to indicate that GTK rekeying is supported
 *	by the device (flag)
 * @NL80211_WOWLAN_TRIG_GTK_REKEY_FAILURE: wake up on GTK rekey failure (अगर
 *	करोne by the device) (flag)
 * @NL80211_WOWLAN_TRIG_EAP_IDENT_REQUEST: wake up on EAP Identity Request
 *	packet (flag)
 * @NL80211_WOWLAN_TRIG_4WAY_HANDSHAKE: wake up on 4-way handshake (flag)
 * @NL80211_WOWLAN_TRIG_RFKILL_RELEASE: wake up when rfसमाप्त is released
 *	(on devices that have rfसमाप्त in the device) (flag)
 * @NL80211_WOWLAN_TRIG_WAKEUP_PKT_80211: For wakeup reporting only, contains
 *	the 802.11 packet that caused the wakeup, e.g. a deauth frame. The frame
 *	may be truncated, the @NL80211_WOWLAN_TRIG_WAKEUP_PKT_80211_LEN
 *	attribute contains the original length.
 * @NL80211_WOWLAN_TRIG_WAKEUP_PKT_80211_LEN: Original length of the 802.11
 *	packet, may be bigger than the @NL80211_WOWLAN_TRIG_WAKEUP_PKT_80211
 *	attribute अगर the packet was truncated somewhere.
 * @NL80211_WOWLAN_TRIG_WAKEUP_PKT_8023: For wakeup reporting only, contains the
 *	802.11 packet that caused the wakeup, e.g. a magic packet. The frame may
 *	be truncated, the @NL80211_WOWLAN_TRIG_WAKEUP_PKT_8023_LEN attribute
 *	contains the original length.
 * @NL80211_WOWLAN_TRIG_WAKEUP_PKT_8023_LEN: Original length of the 802.3
 *	packet, may be bigger than the @NL80211_WOWLAN_TRIG_WAKEUP_PKT_8023
 *	attribute अगर the packet was truncated somewhere.
 * @NL80211_WOWLAN_TRIG_TCP_CONNECTION: TCP connection wake, see DOC section
 *	"TCP connection wakeup" क्रम more details. This is a nested attribute
 *	containing the exact inक्रमmation क्रम establishing and keeping alive
 *	the TCP connection.
 * @NL80211_WOWLAN_TRIG_TCP_WAKEUP_MATCH: For wakeup reporting only, the
 *	wakeup packet was received on the TCP connection
 * @NL80211_WOWLAN_TRIG_WAKEUP_TCP_CONNLOST: For wakeup reporting only, the
 *	TCP connection was lost or failed to be established
 * @NL80211_WOWLAN_TRIG_WAKEUP_TCP_NOMORETOKENS: For wakeup reporting only,
 *	the TCP connection ran out of tokens to use क्रम data to send to the
 *	service
 * @NL80211_WOWLAN_TRIG_NET_DETECT: wake up when a configured network
 *	is detected.  This is a nested attribute that contains the
 *	same attributes used with @NL80211_CMD_START_SCHED_SCAN.  It
 *	specअगरies how the scan is perक्रमmed (e.g. the पूर्णांकerval, the
 *	channels to scan and the initial delay) as well as the scan
 *	results that will trigger a wake (i.e. the matchsets).  This
 *	attribute is also sent in a response to
 *	@NL80211_CMD_GET_WIPHY, indicating the number of match sets
 *	supported by the driver (u32).
 * @NL80211_WOWLAN_TRIG_NET_DETECT_RESULTS: nested attribute
 *	containing an array with inक्रमmation about what triggered the
 *	wake up.  If no elements are present in the array, it means
 *	that the inक्रमmation is not available.  If more than one
 *	element is present, it means that more than one match
 *	occurred.
 *	Each element in the array is a nested attribute that contains
 *	one optional %NL80211_ATTR_SSID attribute and one optional
 *	%NL80211_ATTR_SCAN_FREQUENCIES attribute.  At least one of
 *	these attributes must be present.  If
 *	%NL80211_ATTR_SCAN_FREQUENCIES contains more than one
 *	frequency, it means that the match occurred in more than one
 *	channel.
 * @NUM_NL80211_WOWLAN_TRIG: number of wake on wireless triggers
 * @MAX_NL80211_WOWLAN_TRIG: highest wowlan trigger attribute number
 *
 * These nested attributes are used to configure the wakeup triggers and
 * to report the wakeup reason(s).
 */
क्रमागत nl80211_wowlan_triggers अणु
	__NL80211_WOWLAN_TRIG_INVALID,
	NL80211_WOWLAN_TRIG_ANY,
	NL80211_WOWLAN_TRIG_DISCONNECT,
	NL80211_WOWLAN_TRIG_MAGIC_PKT,
	NL80211_WOWLAN_TRIG_PKT_PATTERN,
	NL80211_WOWLAN_TRIG_GTK_REKEY_SUPPORTED,
	NL80211_WOWLAN_TRIG_GTK_REKEY_FAILURE,
	NL80211_WOWLAN_TRIG_EAP_IDENT_REQUEST,
	NL80211_WOWLAN_TRIG_4WAY_HANDSHAKE,
	NL80211_WOWLAN_TRIG_RFKILL_RELEASE,
	NL80211_WOWLAN_TRIG_WAKEUP_PKT_80211,
	NL80211_WOWLAN_TRIG_WAKEUP_PKT_80211_LEN,
	NL80211_WOWLAN_TRIG_WAKEUP_PKT_8023,
	NL80211_WOWLAN_TRIG_WAKEUP_PKT_8023_LEN,
	NL80211_WOWLAN_TRIG_TCP_CONNECTION,
	NL80211_WOWLAN_TRIG_WAKEUP_TCP_MATCH,
	NL80211_WOWLAN_TRIG_WAKEUP_TCP_CONNLOST,
	NL80211_WOWLAN_TRIG_WAKEUP_TCP_NOMORETOKENS,
	NL80211_WOWLAN_TRIG_NET_DETECT,
	NL80211_WOWLAN_TRIG_NET_DETECT_RESULTS,

	/* keep last */
	NUM_NL80211_WOWLAN_TRIG,
	MAX_NL80211_WOWLAN_TRIG = NUM_NL80211_WOWLAN_TRIG - 1
पूर्ण;

/**
 * DOC: TCP connection wakeup
 *
 * Some devices can establish a TCP connection in order to be woken up by a
 * packet coming in from outside their network segment, or behind NAT. If
 * configured, the device will establish a TCP connection to the given
 * service, and periodically send data to that service. The first data
 * packet is usually transmitted after SYN/ACK, also ACKing the SYN/ACK.
 * The data packets can optionally include a (little endian) sequence
 * number (in the TCP payload!) that is generated by the device, and, also
 * optionally, a token from a list of tokens. This serves as a keep-alive
 * with the service, and क्रम NATed connections, etc.
 *
 * During this keep-alive period, the server करोesn't send any data to the
 * client. When receiving data, it is compared against the wakeup pattern
 * (and mask) and अगर it matches, the host is woken up. Similarly, अगर the
 * connection अवरोधs or cannot be established to start with, the host is
 * also woken up.
 *
 * Developer's note: ARP offload is required क्रम this, otherwise TCP
 * response packets might not go through correctly.
 */

/**
 * काष्ठा nl80211_wowlan_tcp_data_seq - WoWLAN TCP data sequence
 * @start: starting value
 * @offset: offset of sequence number in packet
 * @len: length of the sequence value to ग_लिखो, 1 through 4
 *
 * Note: करोn't confuse with the TCP sequence number(s), this is क्रम the
 * keepalive packet payload. The actual value is written पूर्णांकo the packet
 * in little endian.
 */
काष्ठा nl80211_wowlan_tcp_data_seq अणु
	__u32 start, offset, len;
पूर्ण;

/**
 * काष्ठा nl80211_wowlan_tcp_data_token - WoWLAN TCP data token config
 * @offset: offset of token in packet
 * @len: length of each token
 * @token_stream: stream of data to be used क्रम the tokens, the length must
 *	be a multiple of @len क्रम this to make sense
 */
काष्ठा nl80211_wowlan_tcp_data_token अणु
	__u32 offset, len;
	__u8 token_stream[];
पूर्ण;

/**
 * काष्ठा nl80211_wowlan_tcp_data_token_feature - data token features
 * @min_len: minimum token length
 * @max_len: maximum token length
 * @bufsize: total available token buffer size (max size of @token_stream)
 */
काष्ठा nl80211_wowlan_tcp_data_token_feature अणु
	__u32 min_len, max_len, bufsize;
पूर्ण;

/**
 * क्रमागत nl80211_wowlan_tcp_attrs - WoWLAN TCP connection parameters
 * @__NL80211_WOWLAN_TCP_INVALID: invalid number क्रम nested attributes
 * @NL80211_WOWLAN_TCP_SRC_IPV4: source IPv4 address (in network byte order)
 * @NL80211_WOWLAN_TCP_DST_IPV4: destination IPv4 address
 *	(in network byte order)
 * @NL80211_WOWLAN_TCP_DST_MAC: destination MAC address, this is given because
 *	route lookup when configured might be invalid by the समय we suspend,
 *	and करोing a route lookup when suspending is no दीर्घer possible as it
 *	might require ARP querying.
 * @NL80211_WOWLAN_TCP_SRC_PORT: source port (u16); optional, अगर not given a
 *	socket and port will be allocated
 * @NL80211_WOWLAN_TCP_DST_PORT: destination port (u16)
 * @NL80211_WOWLAN_TCP_DATA_PAYLOAD: data packet payload, at least one byte.
 *	For feature advertising, a u32 attribute holding the maximum length
 *	of the data payload.
 * @NL80211_WOWLAN_TCP_DATA_PAYLOAD_SEQ: data packet sequence configuration
 *	(अगर desired), a &काष्ठा nl80211_wowlan_tcp_data_seq. For feature
 *	advertising it is just a flag
 * @NL80211_WOWLAN_TCP_DATA_PAYLOAD_TOKEN: data packet token configuration,
 *	see &काष्ठा nl80211_wowlan_tcp_data_token and क्रम advertising see
 *	&काष्ठा nl80211_wowlan_tcp_data_token_feature.
 * @NL80211_WOWLAN_TCP_DATA_INTERVAL: data पूर्णांकerval in seconds, maximum
 *	पूर्णांकerval in feature advertising (u32)
 * @NL80211_WOWLAN_TCP_WAKE_PAYLOAD: wake packet payload, क्रम advertising a
 *	u32 attribute holding the maximum length
 * @NL80211_WOWLAN_TCP_WAKE_MASK: Wake packet payload mask, not used क्रम
 *	feature advertising. The mask works like @NL80211_PKTPAT_MASK
 *	but on the TCP payload only.
 * @NUM_NL80211_WOWLAN_TCP: number of TCP attributes
 * @MAX_NL80211_WOWLAN_TCP: highest attribute number
 */
क्रमागत nl80211_wowlan_tcp_attrs अणु
	__NL80211_WOWLAN_TCP_INVALID,
	NL80211_WOWLAN_TCP_SRC_IPV4,
	NL80211_WOWLAN_TCP_DST_IPV4,
	NL80211_WOWLAN_TCP_DST_MAC,
	NL80211_WOWLAN_TCP_SRC_PORT,
	NL80211_WOWLAN_TCP_DST_PORT,
	NL80211_WOWLAN_TCP_DATA_PAYLOAD,
	NL80211_WOWLAN_TCP_DATA_PAYLOAD_SEQ,
	NL80211_WOWLAN_TCP_DATA_PAYLOAD_TOKEN,
	NL80211_WOWLAN_TCP_DATA_INTERVAL,
	NL80211_WOWLAN_TCP_WAKE_PAYLOAD,
	NL80211_WOWLAN_TCP_WAKE_MASK,

	/* keep last */
	NUM_NL80211_WOWLAN_TCP,
	MAX_NL80211_WOWLAN_TCP = NUM_NL80211_WOWLAN_TCP - 1
पूर्ण;

/**
 * काष्ठा nl80211_coalesce_rule_support - coalesce rule support inक्रमmation
 * @max_rules: maximum number of rules supported
 * @pat: packet pattern support inक्रमmation
 * @max_delay: maximum supported coalescing delay in msecs
 *
 * This काष्ठा is carried in %NL80211_ATTR_COALESCE_RULE in the
 * capability inक्रमmation given by the kernel to userspace.
 */
काष्ठा nl80211_coalesce_rule_support अणु
	__u32 max_rules;
	काष्ठा nl80211_pattern_support pat;
	__u32 max_delay;
पूर्ण __attribute__((packed));

/**
 * क्रमागत nl80211_attr_coalesce_rule - coalesce rule attribute
 * @__NL80211_COALESCE_RULE_INVALID: invalid number क्रम nested attribute
 * @NL80211_ATTR_COALESCE_RULE_DELAY: delay in msecs used क्रम packet coalescing
 * @NL80211_ATTR_COALESCE_RULE_CONDITION: condition क्रम packet coalescence,
 *	see &क्रमागत nl80211_coalesce_condition.
 * @NL80211_ATTR_COALESCE_RULE_PKT_PATTERN: packet offset, pattern is matched
 *	after these fixed number of bytes of received packet
 * @NUM_NL80211_ATTR_COALESCE_RULE: number of attributes
 * @NL80211_ATTR_COALESCE_RULE_MAX: max attribute number
 */
क्रमागत nl80211_attr_coalesce_rule अणु
	__NL80211_COALESCE_RULE_INVALID,
	NL80211_ATTR_COALESCE_RULE_DELAY,
	NL80211_ATTR_COALESCE_RULE_CONDITION,
	NL80211_ATTR_COALESCE_RULE_PKT_PATTERN,

	/* keep last */
	NUM_NL80211_ATTR_COALESCE_RULE,
	NL80211_ATTR_COALESCE_RULE_MAX = NUM_NL80211_ATTR_COALESCE_RULE - 1
पूर्ण;

/**
 * क्रमागत nl80211_coalesce_condition - coalesce rule conditions
 * @NL80211_COALESCE_CONDITION_MATCH: coalaesce Rx packets when patterns
 *	in a rule are matched.
 * @NL80211_COALESCE_CONDITION_NO_MATCH: coalesce Rx packets when patterns
 *	in a rule are not matched.
 */
क्रमागत nl80211_coalesce_condition अणु
	NL80211_COALESCE_CONDITION_MATCH,
	NL80211_COALESCE_CONDITION_NO_MATCH
पूर्ण;

/**
 * क्रमागत nl80211_अगरace_limit_attrs - limit attributes
 * @NL80211_IFACE_LIMIT_UNSPEC: (reserved)
 * @NL80211_IFACE_LIMIT_MAX: maximum number of पूर्णांकerfaces that
 *	can be chosen from this set of पूर्णांकerface types (u32)
 * @NL80211_IFACE_LIMIT_TYPES: nested attribute containing a
 *	flag attribute क्रम each पूर्णांकerface type in this set
 * @NUM_NL80211_IFACE_LIMIT: number of attributes
 * @MAX_NL80211_IFACE_LIMIT: highest attribute number
 */
क्रमागत nl80211_अगरace_limit_attrs अणु
	NL80211_IFACE_LIMIT_UNSPEC,
	NL80211_IFACE_LIMIT_MAX,
	NL80211_IFACE_LIMIT_TYPES,

	/* keep last */
	NUM_NL80211_IFACE_LIMIT,
	MAX_NL80211_IFACE_LIMIT = NUM_NL80211_IFACE_LIMIT - 1
पूर्ण;

/**
 * क्रमागत nl80211_अगर_combination_attrs -- पूर्णांकerface combination attributes
 *
 * @NL80211_IFACE_COMB_UNSPEC: (reserved)
 * @NL80211_IFACE_COMB_LIMITS: Nested attributes containing the limits
 *	क्रम given पूर्णांकerface types, see &क्रमागत nl80211_अगरace_limit_attrs.
 * @NL80211_IFACE_COMB_MAXNUM: u32 attribute giving the total number of
 *	पूर्णांकerfaces that can be created in this group. This number करोesn't
 *	apply to पूर्णांकerfaces purely managed in software, which are listed
 *	in a separate attribute %NL80211_ATTR_INTERFACES_SOFTWARE.
 * @NL80211_IFACE_COMB_STA_AP_BI_MATCH: flag attribute specअगरying that
 *	beacon पूर्णांकervals within this group must be all the same even क्रम
 *	infraकाष्ठाure and AP/GO combinations, i.e. the GO(s) must aकरोpt
 *	the infraकाष्ठाure network's beacon पूर्णांकerval.
 * @NL80211_IFACE_COMB_NUM_CHANNELS: u32 attribute specअगरying how many
 *	dअगरferent channels may be used within this group.
 * @NL80211_IFACE_COMB_RADAR_DETECT_WIDTHS: u32 attribute containing the biपंचांगap
 *	of supported channel widths क्रम radar detection.
 * @NL80211_IFACE_COMB_RADAR_DETECT_REGIONS: u32 attribute containing the biपंचांगap
 *	of supported regulatory regions क्रम radar detection.
 * @NL80211_IFACE_COMB_BI_MIN_GCD: u32 attribute specअगरying the minimum GCD of
 *	dअगरferent beacon पूर्णांकervals supported by all the पूर्णांकerface combinations
 *	in this group (अगर not present, all beacon पूर्णांकervals be identical).
 * @NUM_NL80211_IFACE_COMB: number of attributes
 * @MAX_NL80211_IFACE_COMB: highest attribute number
 *
 * Examples:
 *	limits = [ #अणुSTAपूर्ण <= 1, #अणुAPपूर्ण <= 1 ], matching BI, channels = 1, max = 2
 *	=> allows an AP and a STA that must match BIs
 *
 *	numbers = [ #अणुAP, P2P-GOपूर्ण <= 8 ], BI min gcd, channels = 1, max = 8,
 *	=> allows 8 of AP/GO that can have BI gcd >= min gcd
 *
 *	numbers = [ #अणुSTAपूर्ण <= 2 ], channels = 2, max = 2
 *	=> allows two STAs on dअगरferent channels
 *
 *	numbers = [ #अणुSTAपूर्ण <= 1, #अणुP2P-client,P2P-GOपूर्ण <= 3 ], max = 4
 *	=> allows a STA plus three P2P पूर्णांकerfaces
 *
 * The list of these four possibilities could completely be contained
 * within the %NL80211_ATTR_INTERFACE_COMBINATIONS attribute to indicate
 * that any of these groups must match.
 *
 * "Combinations" of just a single पूर्णांकerface will not be listed here,
 * a single पूर्णांकerface of any valid पूर्णांकerface type is assumed to always
 * be possible by itself. This means that implicitly, क्रम each valid
 * पूर्णांकerface type, the following group always exists:
 *	numbers = [ #अणु<type>पूर्ण <= 1 ], channels = 1, max = 1
 */
क्रमागत nl80211_अगर_combination_attrs अणु
	NL80211_IFACE_COMB_UNSPEC,
	NL80211_IFACE_COMB_LIMITS,
	NL80211_IFACE_COMB_MAXNUM,
	NL80211_IFACE_COMB_STA_AP_BI_MATCH,
	NL80211_IFACE_COMB_NUM_CHANNELS,
	NL80211_IFACE_COMB_RADAR_DETECT_WIDTHS,
	NL80211_IFACE_COMB_RADAR_DETECT_REGIONS,
	NL80211_IFACE_COMB_BI_MIN_GCD,

	/* keep last */
	NUM_NL80211_IFACE_COMB,
	MAX_NL80211_IFACE_COMB = NUM_NL80211_IFACE_COMB - 1
पूर्ण;


/**
 * क्रमागत nl80211_plink_state - state of a mesh peer link finite state machine
 *
 * @NL80211_PLINK_LISTEN: initial state, considered the implicit
 *	state of non existent mesh peer links
 * @NL80211_PLINK_OPN_SNT: mesh plink खोलो frame has been sent to
 *	this mesh peer
 * @NL80211_PLINK_OPN_RCVD: mesh plink खोलो frame has been received
 *	from this mesh peer
 * @NL80211_PLINK_CNF_RCVD: mesh plink confirm frame has been
 *	received from this mesh peer
 * @NL80211_PLINK_ESTAB: mesh peer link is established
 * @NL80211_PLINK_HOLDING: mesh peer link is being बंदd or cancelled
 * @NL80211_PLINK_BLOCKED: all frames transmitted from this mesh
 *	plink are discarded
 * @NUM_NL80211_PLINK_STATES: number of peer link states
 * @MAX_NL80211_PLINK_STATES: highest numerical value of plink states
 */
क्रमागत nl80211_plink_state अणु
	NL80211_PLINK_LISTEN,
	NL80211_PLINK_OPN_SNT,
	NL80211_PLINK_OPN_RCVD,
	NL80211_PLINK_CNF_RCVD,
	NL80211_PLINK_ESTAB,
	NL80211_PLINK_HOLDING,
	NL80211_PLINK_BLOCKED,

	/* keep last */
	NUM_NL80211_PLINK_STATES,
	MAX_NL80211_PLINK_STATES = NUM_NL80211_PLINK_STATES - 1
पूर्ण;

/**
 * क्रमागत nl80211_plink_action - actions to perक्रमm in mesh peers
 *
 * @NL80211_PLINK_ACTION_NO_ACTION: perक्रमm no action
 * @NL80211_PLINK_ACTION_OPEN: start mesh peer link establishment
 * @NL80211_PLINK_ACTION_BLOCK: block traffic from this mesh peer
 * @NUM_NL80211_PLINK_ACTIONS: number of possible actions
 */
क्रमागत plink_actions अणु
	NL80211_PLINK_ACTION_NO_ACTION,
	NL80211_PLINK_ACTION_OPEN,
	NL80211_PLINK_ACTION_BLOCK,

	NUM_NL80211_PLINK_ACTIONS,
पूर्ण;


#घोषणा NL80211_KCK_LEN			16
#घोषणा NL80211_KEK_LEN			16
#घोषणा NL80211_KCK_EXT_LEN		24
#घोषणा NL80211_KEK_EXT_LEN		32
#घोषणा NL80211_REPLAY_CTR_LEN		8

/**
 * क्रमागत nl80211_rekey_data - attributes क्रम GTK rekey offload
 * @__NL80211_REKEY_DATA_INVALID: invalid number क्रम nested attributes
 * @NL80211_REKEY_DATA_KEK: key encryption key (binary)
 * @NL80211_REKEY_DATA_KCK: key confirmation key (binary)
 * @NL80211_REKEY_DATA_REPLAY_CTR: replay counter (binary)
 * @NL80211_REKEY_DATA_AKM: AKM data (OUI, suite type)
 * @NUM_NL80211_REKEY_DATA: number of rekey attributes (पूर्णांकernal)
 * @MAX_NL80211_REKEY_DATA: highest rekey attribute (पूर्णांकernal)
 */
क्रमागत nl80211_rekey_data अणु
	__NL80211_REKEY_DATA_INVALID,
	NL80211_REKEY_DATA_KEK,
	NL80211_REKEY_DATA_KCK,
	NL80211_REKEY_DATA_REPLAY_CTR,
	NL80211_REKEY_DATA_AKM,

	/* keep last */
	NUM_NL80211_REKEY_DATA,
	MAX_NL80211_REKEY_DATA = NUM_NL80211_REKEY_DATA - 1
पूर्ण;

/**
 * क्रमागत nl80211_hidden_ssid - values क्रम %NL80211_ATTR_HIDDEN_SSID
 * @NL80211_HIDDEN_SSID_NOT_IN_USE: करो not hide SSID (i.e., broadcast it in
 *	Beacon frames)
 * @NL80211_HIDDEN_SSID_ZERO_LEN: hide SSID by using zero-length SSID element
 *	in Beacon frames
 * @NL80211_HIDDEN_SSID_ZERO_CONTENTS: hide SSID by using correct length of SSID
 *	element in Beacon frames but zero out each byte in the SSID
 */
क्रमागत nl80211_hidden_ssid अणु
	NL80211_HIDDEN_SSID_NOT_IN_USE,
	NL80211_HIDDEN_SSID_ZERO_LEN,
	NL80211_HIDDEN_SSID_ZERO_CONTENTS
पूर्ण;

/**
 * क्रमागत nl80211_sta_wme_attr - station WME attributes
 * @__NL80211_STA_WME_INVALID: invalid number क्रम nested attribute
 * @NL80211_STA_WME_UAPSD_QUEUES: biपंचांगap of uapsd queues. the क्रमmat
 *	is the same as the AC biपंचांगap in the QoS info field.
 * @NL80211_STA_WME_MAX_SP: max service period. the क्रमmat is the same
 *	as the MAX_SP field in the QoS info field (but alपढ़ोy shअगरted करोwn).
 * @__NL80211_STA_WME_AFTER_LAST: पूर्णांकernal
 * @NL80211_STA_WME_MAX: highest station WME attribute
 */
क्रमागत nl80211_sta_wme_attr अणु
	__NL80211_STA_WME_INVALID,
	NL80211_STA_WME_UAPSD_QUEUES,
	NL80211_STA_WME_MAX_SP,

	/* keep last */
	__NL80211_STA_WME_AFTER_LAST,
	NL80211_STA_WME_MAX = __NL80211_STA_WME_AFTER_LAST - 1
पूर्ण;

/**
 * क्रमागत nl80211_pmksa_candidate_attr - attributes क्रम PMKSA caching candidates
 * @__NL80211_PMKSA_CANDIDATE_INVALID: invalid number क्रम nested attributes
 * @NL80211_PMKSA_CANDIDATE_INDEX: candidate index (u32; the smaller, the higher
 *	priority)
 * @NL80211_PMKSA_CANDIDATE_BSSID: candidate BSSID (6 octets)
 * @NL80211_PMKSA_CANDIDATE_PREAUTH: RSN pre-authentication supported (flag)
 * @NUM_NL80211_PMKSA_CANDIDATE: number of PMKSA caching candidate attributes
 *	(पूर्णांकernal)
 * @MAX_NL80211_PMKSA_CANDIDATE: highest PMKSA caching candidate attribute
 *	(पूर्णांकernal)
 */
क्रमागत nl80211_pmksa_candidate_attr अणु
	__NL80211_PMKSA_CANDIDATE_INVALID,
	NL80211_PMKSA_CANDIDATE_INDEX,
	NL80211_PMKSA_CANDIDATE_BSSID,
	NL80211_PMKSA_CANDIDATE_PREAUTH,

	/* keep last */
	NUM_NL80211_PMKSA_CANDIDATE,
	MAX_NL80211_PMKSA_CANDIDATE = NUM_NL80211_PMKSA_CANDIDATE - 1
पूर्ण;

/**
 * क्रमागत nl80211_tdls_operation - values क्रम %NL80211_ATTR_TDLS_OPERATION
 * @NL80211_TDLS_DISCOVERY_REQ: Send a TDLS discovery request
 * @NL80211_TDLS_SETUP: Setup TDLS link
 * @NL80211_TDLS_TEARDOWN: Tearकरोwn a TDLS link which is alपढ़ोy established
 * @NL80211_TDLS_ENABLE_LINK: Enable TDLS link
 * @NL80211_TDLS_DISABLE_LINK: Disable TDLS link
 */
क्रमागत nl80211_tdls_operation अणु
	NL80211_TDLS_DISCOVERY_REQ,
	NL80211_TDLS_SETUP,
	NL80211_TDLS_TEARDOWN,
	NL80211_TDLS_ENABLE_LINK,
	NL80211_TDLS_DISABLE_LINK,
पूर्ण;

/*
 * क्रमागत nl80211_ap_sme_features - device-पूर्णांकegrated AP features
 * Reserved क्रम future use, no bits are defined in
 * NL80211_ATTR_DEVICE_AP_SME yet.
क्रमागत nl80211_ap_sme_features अणु
पूर्ण;
 */

/**
 * क्रमागत nl80211_feature_flags - device/driver features
 * @NL80211_FEATURE_SK_TX_STATUS: This driver supports reflecting back
 *	TX status to the socket error queue when requested with the
 *	socket option.
 * @NL80211_FEATURE_HT_IBSS: This driver supports IBSS with HT datarates.
 * @NL80211_FEATURE_INACTIVITY_TIMER: This driver takes care of मुक्तing up
 *	the connected inactive stations in AP mode.
 * @NL80211_FEATURE_CELL_BASE_REG_HINTS: This driver has been tested
 *	to work properly to suppport receiving regulatory hपूर्णांकs from
 *	cellular base stations.
 * @NL80211_FEATURE_P2P_DEVICE_NEEDS_CHANNEL: (no दीर्घer available, only
 *	here to reserve the value क्रम API/ABI compatibility)
 * @NL80211_FEATURE_SAE: This driver supports simultaneous authentication of
 *	equals (SAE) with user space SME (NL80211_CMD_AUTHENTICATE) in station
 *	mode
 * @NL80211_FEATURE_LOW_PRIORITY_SCAN: This driver supports low priority scan
 * @NL80211_FEATURE_SCAN_FLUSH: Scan flush is supported
 * @NL80211_FEATURE_AP_SCAN: Support scanning using an AP vअगर
 * @NL80211_FEATURE_VIF_TXPOWER: The driver supports per-vअगर TX घातer setting
 * @NL80211_FEATURE_NEED_OBSS_SCAN: The driver expects userspace to perक्रमm
 *	OBSS scans and generate 20/40 BSS coex reports. This flag is used only
 *	क्रम drivers implementing the CONNECT API, क्रम AUTH/ASSOC it is implied.
 * @NL80211_FEATURE_P2P_GO_CTWIN: P2P GO implementation supports CT Winकरोw
 *	setting
 * @NL80211_FEATURE_P2P_GO_OPPPS: P2P GO implementation supports opportunistic
 *	घातersave
 * @NL80211_FEATURE_FULL_AP_CLIENT_STATE: The driver supports full state
 *	transitions क्रम AP clients. Without this flag (and अगर the driver
 *	करोesn't have the AP SME in the device) the driver supports adding
 *	stations only when they're associated and adds them in associated
 *	state (to later be transitioned पूर्णांकo authorized), with this flag
 *	they should be added beक्रमe even sending the authentication reply
 *	and then transitioned पूर्णांकo authenticated, associated and authorized
 *	states using station flags.
 *	Note that even क्रम drivers that support this, the शेष is to add
 *	stations in authenticated/associated state, so to add unauthenticated
 *	stations the authenticated/associated bits have to be set in the mask.
 * @NL80211_FEATURE_ADVERTISE_CHAN_LIMITS: cfg80211 advertises channel limits
 *	(HT40, VHT 80/160 MHz) अगर this flag is set
 * @NL80211_FEATURE_USERSPACE_MPM: This driver supports a userspace Mesh
 *	Peering Management entity which may be implemented by रेजिस्टरing क्रम
 *	beacons or NL80211_CMD_NEW_PEER_CANDIDATE events. The mesh beacon is
 *	still generated by the driver.
 * @NL80211_FEATURE_ACTIVE_MONITOR: This driver supports an active monitor
 *	पूर्णांकerface. An active monitor पूर्णांकerface behaves like a normal monitor
 *	पूर्णांकerface, but माला_लो added to the driver. It ensures that incoming
 *	unicast packets directed at the configured पूर्णांकerface address get ACKed.
 * @NL80211_FEATURE_AP_MODE_CHAN_WIDTH_CHANGE: This driver supports dynamic
 *	channel bandwidth change (e.g., HT 20 <-> 40 MHz channel) during the
 *	lअगरeसमय of a BSS.
 * @NL80211_FEATURE_DS_PARAM_SET_IE_IN_PROBES: This device adds a DS Parameter
 *	Set IE to probe requests.
 * @NL80211_FEATURE_WFA_TPC_IE_IN_PROBES: This device adds a WFA TPC Report IE
 *	to probe requests.
 * @NL80211_FEATURE_QUIET: This device, in client mode, supports Quiet Period
 *	requests sent to it by an AP.
 * @NL80211_FEATURE_TX_POWER_INSERTION: This device is capable of inserting the
 *	current tx घातer value पूर्णांकo the TPC Report IE in the spectrum
 *	management TPC Report action frame, and in the Radio Measurement Link
 *	Measurement Report action frame.
 * @NL80211_FEATURE_ACKTO_ESTIMATION: This driver supports dynamic ACK समयout
 *	estimation (dynack). %NL80211_ATTR_WIPHY_DYN_ACK flag attribute is used
 *	to enable dynack.
 * @NL80211_FEATURE_STATIC_SMPS: Device supports अटल spatial
 *	multiplexing घातersave, ie. can turn off all but one chain
 *	even on HT connections that should be using more chains.
 * @NL80211_FEATURE_DYNAMIC_SMPS: Device supports dynamic spatial
 *	multiplexing घातersave, ie. can turn off all but one chain
 *	and then wake the rest up as required after, क्रम example,
 *	rts/cts handshake.
 * @NL80211_FEATURE_SUPPORTS_WMM_ADMISSION: the device supports setting up WMM
 *	TSPEC sessions (TID aka TSID 0-7) with the %NL80211_CMD_ADD_TX_TS
 *	command. Standard IEEE 802.11 TSPEC setup is not yet supported, it
 *	needs to be able to handle Block-Ack agreements and other things.
 * @NL80211_FEATURE_MAC_ON_CREATE: Device supports configuring
 *	the vअगर's MAC address upon creation.
 *	See 'macaddr' field in the vअगर_params (cfg80211.h).
 * @NL80211_FEATURE_TDLS_CHANNEL_SWITCH: Driver supports channel चयनing when
 *	operating as a TDLS peer.
 * @NL80211_FEATURE_SCAN_RANDOM_MAC_ADDR: This device/driver supports using a
 *	अक्रमom MAC address during scan (अगर the device is unassociated); the
 *	%NL80211_SCAN_FLAG_RANDOM_ADDR flag may be set क्रम scans and the MAC
 *	address mask/value will be used.
 * @NL80211_FEATURE_SCHED_SCAN_RANDOM_MAC_ADDR: This device/driver supports
 *	using a अक्रमom MAC address क्रम every scan iteration during scheduled
 *	scan (जबतक not associated), the %NL80211_SCAN_FLAG_RANDOM_ADDR may
 *	be set क्रम scheduled scan and the MAC address mask/value will be used.
 * @NL80211_FEATURE_ND_RANDOM_MAC_ADDR: This device/driver supports using a
 *	अक्रमom MAC address क्रम every scan iteration during "net detect", i.e.
 *	scan in unassociated WoWLAN, the %NL80211_SCAN_FLAG_RANDOM_ADDR may
 *	be set क्रम scheduled scan and the MAC address mask/value will be used.
 */
क्रमागत nl80211_feature_flags अणु
	NL80211_FEATURE_SK_TX_STATUS			= 1 << 0,
	NL80211_FEATURE_HT_IBSS				= 1 << 1,
	NL80211_FEATURE_INACTIVITY_TIMER		= 1 << 2,
	NL80211_FEATURE_CELL_BASE_REG_HINTS		= 1 << 3,
	NL80211_FEATURE_P2P_DEVICE_NEEDS_CHANNEL	= 1 << 4,
	NL80211_FEATURE_SAE				= 1 << 5,
	NL80211_FEATURE_LOW_PRIORITY_SCAN		= 1 << 6,
	NL80211_FEATURE_SCAN_FLUSH			= 1 << 7,
	NL80211_FEATURE_AP_SCAN				= 1 << 8,
	NL80211_FEATURE_VIF_TXPOWER			= 1 << 9,
	NL80211_FEATURE_NEED_OBSS_SCAN			= 1 << 10,
	NL80211_FEATURE_P2P_GO_CTWIN			= 1 << 11,
	NL80211_FEATURE_P2P_GO_OPPPS			= 1 << 12,
	/* bit 13 is reserved */
	NL80211_FEATURE_ADVERTISE_CHAN_LIMITS		= 1 << 14,
	NL80211_FEATURE_FULL_AP_CLIENT_STATE		= 1 << 15,
	NL80211_FEATURE_USERSPACE_MPM			= 1 << 16,
	NL80211_FEATURE_ACTIVE_MONITOR			= 1 << 17,
	NL80211_FEATURE_AP_MODE_CHAN_WIDTH_CHANGE	= 1 << 18,
	NL80211_FEATURE_DS_PARAM_SET_IE_IN_PROBES	= 1 << 19,
	NL80211_FEATURE_WFA_TPC_IE_IN_PROBES		= 1 << 20,
	NL80211_FEATURE_QUIET				= 1 << 21,
	NL80211_FEATURE_TX_POWER_INSERTION		= 1 << 22,
	NL80211_FEATURE_ACKTO_ESTIMATION		= 1 << 23,
	NL80211_FEATURE_STATIC_SMPS			= 1 << 24,
	NL80211_FEATURE_DYNAMIC_SMPS			= 1 << 25,
	NL80211_FEATURE_SUPPORTS_WMM_ADMISSION		= 1 << 26,
	NL80211_FEATURE_MAC_ON_CREATE			= 1 << 27,
	NL80211_FEATURE_TDLS_CHANNEL_SWITCH		= 1 << 28,
	NL80211_FEATURE_SCAN_RANDOM_MAC_ADDR		= 1 << 29,
	NL80211_FEATURE_SCHED_SCAN_RANDOM_MAC_ADDR	= 1 << 30,
	NL80211_FEATURE_ND_RANDOM_MAC_ADDR		= 1U << 31,
पूर्ण;

/**
 * क्रमागत nl80211_ext_feature_index - bit index of extended features.
 * @NL80211_EXT_FEATURE_VHT_IBSS: This driver supports IBSS with VHT datarates.
 * @NL80211_EXT_FEATURE_RRM: This driver supports RRM. When featured, user can
 *	request to use RRM (see %NL80211_ATTR_USE_RRM) with
 *	%NL80211_CMD_ASSOCIATE and %NL80211_CMD_CONNECT requests, which will set
 *	the ASSOC_REQ_USE_RRM flag in the association request even अगर
 *	NL80211_FEATURE_QUIET is not advertized.
 * @NL80211_EXT_FEATURE_MU_MIMO_AIR_SNIFFER: This device supports MU-MIMO air
 *	snअगरfer which means that it can be configured to hear packets from
 *	certain groups which can be configured by the
 *	%NL80211_ATTR_MU_MIMO_GROUP_DATA attribute,
 *	or can be configured to follow a station by configuring the
 *	%NL80211_ATTR_MU_MIMO_FOLLOW_MAC_ADDR attribute.
 * @NL80211_EXT_FEATURE_SCAN_START_TIME: This driver includes the actual
 *	समय the scan started in scan results event. The समय is the TSF of
 *	the BSS that the पूर्णांकerface that requested the scan is connected to
 *	(अगर available).
 * @NL80211_EXT_FEATURE_BSS_PARENT_TSF: Per BSS, this driver reports the
 *	समय the last beacon/probe was received. The समय is the TSF of the
 *	BSS that the पूर्णांकerface that requested the scan is connected to
 *	(अगर available).
 * @NL80211_EXT_FEATURE_SET_SCAN_DWELL: This driver supports configuration of
 *	channel dwell समय.
 * @NL80211_EXT_FEATURE_BEACON_RATE_LEGACY: Driver supports beacon rate
 *	configuration (AP/mesh), supporting a legacy (non HT/VHT) rate.
 * @NL80211_EXT_FEATURE_BEACON_RATE_HT: Driver supports beacon rate
 *	configuration (AP/mesh) with HT rates.
 * @NL80211_EXT_FEATURE_BEACON_RATE_VHT: Driver supports beacon rate
 *	configuration (AP/mesh) with VHT rates.
 * @NL80211_EXT_FEATURE_FILS_STA: This driver supports Fast Initial Link Setup
 *	with user space SME (NL80211_CMD_AUTHENTICATE) in station mode.
 * @NL80211_EXT_FEATURE_MGMT_TX_RANDOM_TA: This driver supports अक्रमomized TA
 *	in @NL80211_CMD_FRAME जबतक not associated.
 * @NL80211_EXT_FEATURE_MGMT_TX_RANDOM_TA_CONNECTED: This driver supports
 *	अक्रमomized TA in @NL80211_CMD_FRAME जबतक associated.
 * @NL80211_EXT_FEATURE_SCHED_SCAN_RELATIVE_RSSI: The driver supports sched_scan
 *	क्रम reporting BSSs with better RSSI than the current connected BSS
 *	(%NL80211_ATTR_SCHED_SCAN_RELATIVE_RSSI).
 * @NL80211_EXT_FEATURE_CQM_RSSI_LIST: With this driver the
 *	%NL80211_ATTR_CQM_RSSI_THOLD attribute accepts a list of zero or more
 *	RSSI threshold values to monitor rather than exactly one threshold.
 * @NL80211_EXT_FEATURE_FILS_SK_OFFLOAD: Driver SME supports FILS shared key
 *	authentication with %NL80211_CMD_CONNECT.
 * @NL80211_EXT_FEATURE_4WAY_HANDSHAKE_STA_PSK: Device wants to करो 4-way
 *	handshake with PSK in station mode (PSK is passed as part of the connect
 *	and associate commands), करोing it in the host might not be supported.
 * @NL80211_EXT_FEATURE_4WAY_HANDSHAKE_STA_1X: Device wants to करो करोing 4-way
 *	handshake with 802.1X in station mode (will pass EAP frames to the host
 *	and accept the set_pmk/del_pmk commands), करोing it in the host might not
 *	be supported.
 * @NL80211_EXT_FEATURE_FILS_MAX_CHANNEL_TIME: Driver is capable of overriding
 *	the max channel attribute in the FILS request params IE with the
 *	actual dwell समय.
 * @NL80211_EXT_FEATURE_ACCEPT_BCAST_PROBE_RESP: Driver accepts broadcast probe
 *	response
 * @NL80211_EXT_FEATURE_OCE_PROBE_REQ_HIGH_TX_RATE: Driver supports sending
 *	the first probe request in each channel at rate of at least 5.5Mbps.
 * @NL80211_EXT_FEATURE_OCE_PROBE_REQ_DEFERRAL_SUPPRESSION: Driver supports
 *	probe request tx deferral and suppression
 * @NL80211_EXT_FEATURE_MFP_OPTIONAL: Driver supports the %NL80211_MFP_OPTIONAL
 *	value in %NL80211_ATTR_USE_MFP.
 * @NL80211_EXT_FEATURE_LOW_SPAN_SCAN: Driver supports low span scan.
 * @NL80211_EXT_FEATURE_LOW_POWER_SCAN: Driver supports low घातer scan.
 * @NL80211_EXT_FEATURE_HIGH_ACCURACY_SCAN: Driver supports high accuracy scan.
 * @NL80211_EXT_FEATURE_DFS_OFFLOAD: HW/driver will offload DFS actions.
 *	Device or driver will करो all DFS-related actions by itself,
 *	inक्रमming user-space about CAC progress, radar detection event,
 *	channel change triggered by radar detection event.
 *	No need to start CAC from user-space, no need to react to
 *	"radar detected" event.
 * @NL80211_EXT_FEATURE_CONTROL_PORT_OVER_NL80211: Driver supports sending and
 *	receiving control port frames over nl80211 instead of the netdevice.
 * @NL80211_EXT_FEATURE_ACK_SIGNAL_SUPPORT: This driver/device supports
 *	(average) ACK संकेत strength reporting.
 * @NL80211_EXT_FEATURE_TXQS: Driver supports FQ-CoDel-enabled पूर्णांकermediate
 *      TXQs.
 * @NL80211_EXT_FEATURE_SCAN_RANDOM_SN: Driver/device supports अक्रमomizing the
 *	SN in probe request frames अगर requested by %NL80211_SCAN_FLAG_RANDOM_SN.
 * @NL80211_EXT_FEATURE_SCAN_MIN_PREQ_CONTENT: Driver/device can omit all data
 *	except क्रम supported rates from the probe request content अगर requested
 *	by the %NL80211_SCAN_FLAG_MIN_PREQ_CONTENT flag.
 * @NL80211_EXT_FEATURE_ENABLE_FTM_RESPONDER: Driver supports enabling fine
 *	timing measurement responder role.
 *
 * @NL80211_EXT_FEATURE_CAN_REPLACE_PTK0: Driver/device confirm that they are
 *      able to rekey an in-use key correctly. Userspace must not rekey PTK keys
 *      अगर this flag is not set. Ignoring this can leak clear text packets and/or
 *      मुक्तze the connection.
 * @NL80211_EXT_FEATURE_EXT_KEY_ID: Driver supports "Extended Key ID क्रम
 *      Inभागidually Addressed Frames" from IEEE802.11-2016.
 *
 * @NL80211_EXT_FEATURE_AIRTIME_FAIRNESS: Driver supports getting airसमय
 *	fairness क्रम transmitted packets and has enabled airसमय fairness
 *	scheduling.
 *
 * @NL80211_EXT_FEATURE_AP_PMKSA_CACHING: Driver/device supports PMKSA caching
 *	(set/del PMKSA operations) in AP mode.
 *
 * @NL80211_EXT_FEATURE_SCHED_SCAN_BAND_SPECIFIC_RSSI_THOLD: Driver supports
 *	filtering of sched scan results using band specअगरic RSSI thresholds.
 *
 * @NL80211_EXT_FEATURE_STA_TX_PWR: This driver supports controlling tx घातer
 *	to a station.
 *
 * @NL80211_EXT_FEATURE_SAE_OFFLOAD: Device wants to करो SAE authentication in
 *	station mode (SAE password is passed as part of the connect command).
 *
 * @NL80211_EXT_FEATURE_VLAN_OFFLOAD: The driver supports a single netdev
 *	with VLAN tagged frames and separate VLAN-specअगरic netdevs added using
 *	vconfig similarly to the Ethernet हाल.
 *
 * @NL80211_EXT_FEATURE_AQL: The driver supports the Airसमय Queue Limit (AQL)
 *	feature, which prevents bufferbloat by using the expected transmission
 *	समय to limit the amount of data buffered in the hardware.
 *
 * @NL80211_EXT_FEATURE_BEACON_PROTECTION: The driver supports Beacon protection
 *	and can receive key configuration क्रम BIGTK using key indexes 6 and 7.
 * @NL80211_EXT_FEATURE_BEACON_PROTECTION_CLIENT: The driver supports Beacon
 *	protection as a client only and cannot transmit रक्षित beacons.
 *
 * @NL80211_EXT_FEATURE_CONTROL_PORT_NO_PREAUTH: The driver can disable the
 *	क्रमwarding of preauth frames over the control port. They are then
 *	handled as ordinary data frames.
 *
 * @NL80211_EXT_FEATURE_PROTECTED_TWT: Driver supports रक्षित TWT frames
 *
 * @NL80211_EXT_FEATURE_DEL_IBSS_STA: The driver supports removing stations
 *      in IBSS mode, essentially by dropping their state.
 *
 * @NL80211_EXT_FEATURE_MULTICAST_REGISTRATIONS: management frame registrations
 *	are possible क्रम multicast frames and those will be reported properly.
 *
 * @NL80211_EXT_FEATURE_SCAN_FREQ_KHZ: This driver supports receiving and
 *	reporting scan request with %NL80211_ATTR_SCAN_FREQ_KHZ. In order to
 *	report %NL80211_ATTR_SCAN_FREQ_KHZ, %NL80211_SCAN_FLAG_FREQ_KHZ must be
 *	included in the scan request.
 *
 * @NL80211_EXT_FEATURE_CONTROL_PORT_OVER_NL80211_TX_STATUS: The driver
 *	can report tx status क्रम control port over nl80211 tx operations.
 *
 * @NL80211_EXT_FEATURE_OPERATING_CHANNEL_VALIDATION: Driver supports Operating
 *	Channel Validation (OCV) when using driver's SME क्रम RSNA handshakes.
 *
 * @NL80211_EXT_FEATURE_4WAY_HANDSHAKE_AP_PSK: Device wants to करो 4-way
 *	handshake with PSK in AP mode (PSK is passed as part of the start AP
 *	command).
 *
 * @NL80211_EXT_FEATURE_SAE_OFFLOAD_AP: Device wants to करो SAE authentication
 *	in AP mode (SAE password is passed as part of the start AP command).
 *
 * @NL80211_EXT_FEATURE_FILS_DISCOVERY: Driver/device supports FILS discovery
 *	frames transmission
 *
 * @NL80211_EXT_FEATURE_UNSOL_BCAST_PROBE_RESP: Driver/device supports
 *	unsolicited broadcast probe response transmission
 *
 * @NL80211_EXT_FEATURE_BEACON_RATE_HE: Driver supports beacon rate
 *	configuration (AP/mesh) with HE rates.
 *
 * @NL80211_EXT_FEATURE_SECURE_LTF: Device supports secure LTF measurement
 *      exchange protocol.
 *
 * @NL80211_EXT_FEATURE_SECURE_RTT: Device supports secure RTT measurement
 *      exchange protocol.
 *
 * @NL80211_EXT_FEATURE_PROT_RANGE_NEGO_AND_MEASURE: Device supports management
 *      frame protection क्रम all management frames exchanged during the
 *      negotiation and range measurement procedure.
 *
 * @NUM_NL80211_EXT_FEATURES: number of extended features.
 * @MAX_NL80211_EXT_FEATURES: highest extended feature index.
 */
क्रमागत nl80211_ext_feature_index अणु
	NL80211_EXT_FEATURE_VHT_IBSS,
	NL80211_EXT_FEATURE_RRM,
	NL80211_EXT_FEATURE_MU_MIMO_AIR_SNIFFER,
	NL80211_EXT_FEATURE_SCAN_START_TIME,
	NL80211_EXT_FEATURE_BSS_PARENT_TSF,
	NL80211_EXT_FEATURE_SET_SCAN_DWELL,
	NL80211_EXT_FEATURE_BEACON_RATE_LEGACY,
	NL80211_EXT_FEATURE_BEACON_RATE_HT,
	NL80211_EXT_FEATURE_BEACON_RATE_VHT,
	NL80211_EXT_FEATURE_FILS_STA,
	NL80211_EXT_FEATURE_MGMT_TX_RANDOM_TA,
	NL80211_EXT_FEATURE_MGMT_TX_RANDOM_TA_CONNECTED,
	NL80211_EXT_FEATURE_SCHED_SCAN_RELATIVE_RSSI,
	NL80211_EXT_FEATURE_CQM_RSSI_LIST,
	NL80211_EXT_FEATURE_FILS_SK_OFFLOAD,
	NL80211_EXT_FEATURE_4WAY_HANDSHAKE_STA_PSK,
	NL80211_EXT_FEATURE_4WAY_HANDSHAKE_STA_1X,
	NL80211_EXT_FEATURE_FILS_MAX_CHANNEL_TIME,
	NL80211_EXT_FEATURE_ACCEPT_BCAST_PROBE_RESP,
	NL80211_EXT_FEATURE_OCE_PROBE_REQ_HIGH_TX_RATE,
	NL80211_EXT_FEATURE_OCE_PROBE_REQ_DEFERRAL_SUPPRESSION,
	NL80211_EXT_FEATURE_MFP_OPTIONAL,
	NL80211_EXT_FEATURE_LOW_SPAN_SCAN,
	NL80211_EXT_FEATURE_LOW_POWER_SCAN,
	NL80211_EXT_FEATURE_HIGH_ACCURACY_SCAN,
	NL80211_EXT_FEATURE_DFS_OFFLOAD,
	NL80211_EXT_FEATURE_CONTROL_PORT_OVER_NL80211,
	NL80211_EXT_FEATURE_ACK_SIGNAL_SUPPORT,
	/* we नामd this - stay compatible */
	NL80211_EXT_FEATURE_DATA_ACK_SIGNAL_SUPPORT = NL80211_EXT_FEATURE_ACK_SIGNAL_SUPPORT,
	NL80211_EXT_FEATURE_TXQS,
	NL80211_EXT_FEATURE_SCAN_RANDOM_SN,
	NL80211_EXT_FEATURE_SCAN_MIN_PREQ_CONTENT,
	NL80211_EXT_FEATURE_CAN_REPLACE_PTK0,
	NL80211_EXT_FEATURE_ENABLE_FTM_RESPONDER,
	NL80211_EXT_FEATURE_AIRTIME_FAIRNESS,
	NL80211_EXT_FEATURE_AP_PMKSA_CACHING,
	NL80211_EXT_FEATURE_SCHED_SCAN_BAND_SPECIFIC_RSSI_THOLD,
	NL80211_EXT_FEATURE_EXT_KEY_ID,
	NL80211_EXT_FEATURE_STA_TX_PWR,
	NL80211_EXT_FEATURE_SAE_OFFLOAD,
	NL80211_EXT_FEATURE_VLAN_OFFLOAD,
	NL80211_EXT_FEATURE_AQL,
	NL80211_EXT_FEATURE_BEACON_PROTECTION,
	NL80211_EXT_FEATURE_CONTROL_PORT_NO_PREAUTH,
	NL80211_EXT_FEATURE_PROTECTED_TWT,
	NL80211_EXT_FEATURE_DEL_IBSS_STA,
	NL80211_EXT_FEATURE_MULTICAST_REGISTRATIONS,
	NL80211_EXT_FEATURE_BEACON_PROTECTION_CLIENT,
	NL80211_EXT_FEATURE_SCAN_FREQ_KHZ,
	NL80211_EXT_FEATURE_CONTROL_PORT_OVER_NL80211_TX_STATUS,
	NL80211_EXT_FEATURE_OPERATING_CHANNEL_VALIDATION,
	NL80211_EXT_FEATURE_4WAY_HANDSHAKE_AP_PSK,
	NL80211_EXT_FEATURE_SAE_OFFLOAD_AP,
	NL80211_EXT_FEATURE_FILS_DISCOVERY,
	NL80211_EXT_FEATURE_UNSOL_BCAST_PROBE_RESP,
	NL80211_EXT_FEATURE_BEACON_RATE_HE,
	NL80211_EXT_FEATURE_SECURE_LTF,
	NL80211_EXT_FEATURE_SECURE_RTT,
	NL80211_EXT_FEATURE_PROT_RANGE_NEGO_AND_MEASURE,

	/* add new features beक्रमe the definition below */
	NUM_NL80211_EXT_FEATURES,
	MAX_NL80211_EXT_FEATURES = NUM_NL80211_EXT_FEATURES - 1
पूर्ण;

/**
 * क्रमागत nl80211_probe_resp_offload_support_attr - optional supported
 *	protocols क्रम probe-response offloading by the driver/FW.
 *	To be used with the %NL80211_ATTR_PROBE_RESP_OFFLOAD attribute.
 *	Each क्रमागत value represents a bit in the biपंचांगap of supported
 *	protocols. Typically a subset of probe-requests beदीर्घing to a
 *	supported protocol will be excluded from offload and uploaded
 *	to the host.
 *
 * @NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS: Support क्रम WPS ver. 1
 * @NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS2: Support क्रम WPS ver. 2
 * @NL80211_PROBE_RESP_OFFLOAD_SUPPORT_P2P: Support क्रम P2P
 * @NL80211_PROBE_RESP_OFFLOAD_SUPPORT_80211U: Support क्रम 802.11u
 */
क्रमागत nl80211_probe_resp_offload_support_attr अणु
	NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS =	1<<0,
	NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS2 =	1<<1,
	NL80211_PROBE_RESP_OFFLOAD_SUPPORT_P2P =	1<<2,
	NL80211_PROBE_RESP_OFFLOAD_SUPPORT_80211U =	1<<3,
पूर्ण;

/**
 * क्रमागत nl80211_connect_failed_reason - connection request failed reasons
 * @NL80211_CONN_FAIL_MAX_CLIENTS: Maximum number of clients that can be
 *	handled by the AP is reached.
 * @NL80211_CONN_FAIL_BLOCKED_CLIENT: Connection request is rejected due to ACL.
 */
क्रमागत nl80211_connect_failed_reason अणु
	NL80211_CONN_FAIL_MAX_CLIENTS,
	NL80211_CONN_FAIL_BLOCKED_CLIENT,
पूर्ण;

/**
 * क्रमागत nl80211_समयout_reason - समयout reasons
 *
 * @NL80211_TIMEOUT_UNSPECIFIED: Timeout reason unspecअगरied.
 * @NL80211_TIMEOUT_SCAN: Scan (AP discovery) समयd out.
 * @NL80211_TIMEOUT_AUTH: Authentication समयd out.
 * @NL80211_TIMEOUT_ASSOC: Association समयd out.
 */
क्रमागत nl80211_समयout_reason अणु
	NL80211_TIMEOUT_UNSPECIFIED,
	NL80211_TIMEOUT_SCAN,
	NL80211_TIMEOUT_AUTH,
	NL80211_TIMEOUT_ASSOC,
पूर्ण;

/**
 * क्रमागत nl80211_scan_flags -  scan request control flags
 *
 * Scan request control flags are used to control the handling
 * of NL80211_CMD_TRIGGER_SCAN and NL80211_CMD_START_SCHED_SCAN
 * requests.
 *
 * NL80211_SCAN_FLAG_LOW_SPAN, NL80211_SCAN_FLAG_LOW_POWER, and
 * NL80211_SCAN_FLAG_HIGH_ACCURACY flags are exclusive of each other, i.e., only
 * one of them can be used in the request.
 *
 * @NL80211_SCAN_FLAG_LOW_PRIORITY: scan request has low priority
 * @NL80211_SCAN_FLAG_FLUSH: flush cache beक्रमe scanning
 * @NL80211_SCAN_FLAG_AP: क्रमce a scan even अगर the पूर्णांकerface is configured
 *	as AP and the beaconing has alपढ़ोy been configured. This attribute is
 *	dangerous because will destroy stations perक्रमmance as a lot of frames
 *	will be lost जबतक scanning off-channel, thereक्रमe it must be used only
 *	when really needed
 * @NL80211_SCAN_FLAG_RANDOM_ADDR: use a अक्रमom MAC address क्रम this scan (or
 *	क्रम scheduled scan: a dअगरferent one क्रम every scan iteration). When the
 *	flag is set, depending on device capabilities the @NL80211_ATTR_MAC and
 *	@NL80211_ATTR_MAC_MASK attributes may also be given in which हाल only
 *	the masked bits will be preserved from the MAC address and the reमुख्यder
 *	अक्रमomised. If the attributes are not given full अक्रमomisation (46 bits,
 *	locally administered 1, multicast 0) is assumed.
 *	This flag must not be requested when the feature isn't supported, check
 *	the nl80211 feature flags क्रम the device.
 * @NL80211_SCAN_FLAG_FILS_MAX_CHANNEL_TIME: fill the dwell समय in the FILS
 *	request parameters IE in the probe request
 * @NL80211_SCAN_FLAG_ACCEPT_BCAST_PROBE_RESP: accept broadcast probe responses
 * @NL80211_SCAN_FLAG_OCE_PROBE_REQ_HIGH_TX_RATE: send probe request frames at
 *	rate of at least 5.5M. In हाल non OCE AP is discovered in the channel,
 *	only the first probe req in the channel will be sent in high rate.
 * @NL80211_SCAN_FLAG_OCE_PROBE_REQ_DEFERRAL_SUPPRESSION: allow probe request
 *	tx deferral (करोt11FILSProbeDelay shall be set to 15ms)
 *	and suppression (अगर it has received a broadcast Probe Response frame,
 *	Beacon frame or FILS Discovery frame from an AP that the STA considers
 *	a suitable candidate क्रम (re-)association - suitable in terms of
 *	SSID and/or RSSI.
 * @NL80211_SCAN_FLAG_LOW_SPAN: Span corresponds to the total समय taken to
 *	accomplish the scan. Thus, this flag पूर्णांकends the driver to perक्रमm the
 *	scan request with lesser span/duration. It is specअगरic to the driver
 *	implementations on how this is accomplished. Scan accuracy may get
 *	impacted with this flag.
 * @NL80211_SCAN_FLAG_LOW_POWER: This flag पूर्णांकends the scan attempts to consume
 *	optimal possible घातer. Drivers can resort to their specअगरic means to
 *	optimize the घातer. Scan accuracy may get impacted with this flag.
 * @NL80211_SCAN_FLAG_HIGH_ACCURACY: Accuracy here पूर्णांकends to the extent of scan
 *	results obtained. Thus HIGH_ACCURACY scan flag aims to get maximum
 *	possible scan results. This flag hपूर्णांकs the driver to use the best
 *	possible scan configuration to improve the accuracy in scanning.
 *	Latency and घातer use may get impacted with this flag.
 * @NL80211_SCAN_FLAG_RANDOM_SN: अक्रमomize the sequence number in probe
 *	request frames from this scan to aव्योम correlation/tracking being
 *	possible.
 * @NL80211_SCAN_FLAG_MIN_PREQ_CONTENT: minimize probe request content to
 *	only have supported rates and no additional capabilities (unless
 *	added by userspace explicitly.)
 * @NL80211_SCAN_FLAG_FREQ_KHZ: report scan results with
 *	%NL80211_ATTR_SCAN_FREQ_KHZ. This also means
 *	%NL80211_ATTR_SCAN_FREQUENCIES will not be included.
 * @NL80211_SCAN_FLAG_COLOCATED_6GHZ: scan क्रम colocated APs reported by
 *	2.4/5 GHz APs
 */
क्रमागत nl80211_scan_flags अणु
	NL80211_SCAN_FLAG_LOW_PRIORITY				= 1<<0,
	NL80211_SCAN_FLAG_FLUSH					= 1<<1,
	NL80211_SCAN_FLAG_AP					= 1<<2,
	NL80211_SCAN_FLAG_RANDOM_ADDR				= 1<<3,
	NL80211_SCAN_FLAG_FILS_MAX_CHANNEL_TIME			= 1<<4,
	NL80211_SCAN_FLAG_ACCEPT_BCAST_PROBE_RESP		= 1<<5,
	NL80211_SCAN_FLAG_OCE_PROBE_REQ_HIGH_TX_RATE		= 1<<6,
	NL80211_SCAN_FLAG_OCE_PROBE_REQ_DEFERRAL_SUPPRESSION	= 1<<7,
	NL80211_SCAN_FLAG_LOW_SPAN				= 1<<8,
	NL80211_SCAN_FLAG_LOW_POWER				= 1<<9,
	NL80211_SCAN_FLAG_HIGH_ACCURACY				= 1<<10,
	NL80211_SCAN_FLAG_RANDOM_SN				= 1<<11,
	NL80211_SCAN_FLAG_MIN_PREQ_CONTENT			= 1<<12,
	NL80211_SCAN_FLAG_FREQ_KHZ				= 1<<13,
	NL80211_SCAN_FLAG_COLOCATED_6GHZ			= 1<<14,
पूर्ण;

/**
 * क्रमागत nl80211_acl_policy - access control policy
 *
 * Access control policy is applied on a MAC list set by
 * %NL80211_CMD_START_AP and %NL80211_CMD_SET_MAC_ACL, to
 * be used with %NL80211_ATTR_ACL_POLICY.
 *
 * @NL80211_ACL_POLICY_ACCEPT_UNLESS_LISTED: Deny stations which are
 *	listed in ACL, i.e. allow all the stations which are not listed
 *	in ACL to authenticate.
 * @NL80211_ACL_POLICY_DENY_UNLESS_LISTED: Allow the stations which are listed
 *	in ACL, i.e. deny all the stations which are not listed in ACL.
 */
क्रमागत nl80211_acl_policy अणु
	NL80211_ACL_POLICY_ACCEPT_UNLESS_LISTED,
	NL80211_ACL_POLICY_DENY_UNLESS_LISTED,
पूर्ण;

/**
 * क्रमागत nl80211_smps_mode - SMPS mode
 *
 * Requested SMPS mode (क्रम AP mode)
 *
 * @NL80211_SMPS_OFF: SMPS off (use all antennas).
 * @NL80211_SMPS_STATIC: अटल SMPS (use a single antenna)
 * @NL80211_SMPS_DYNAMIC: dynamic smps (start with a single antenna and
 *	turn on other antennas after CTS/RTS).
 */
क्रमागत nl80211_smps_mode अणु
	NL80211_SMPS_OFF,
	NL80211_SMPS_STATIC,
	NL80211_SMPS_DYNAMIC,

	__NL80211_SMPS_AFTER_LAST,
	NL80211_SMPS_MAX = __NL80211_SMPS_AFTER_LAST - 1
पूर्ण;

/**
 * क्रमागत nl80211_radar_event - type of radar event क्रम DFS operation
 *
 * Type of event to be used with NL80211_ATTR_RADAR_EVENT to inक्रमm userspace
 * about detected radars or success of the channel available check (CAC)
 *
 * @NL80211_RADAR_DETECTED: A radar pattern has been detected. The channel is
 *	now unusable.
 * @NL80211_RADAR_CAC_FINISHED: Channel Availability Check has been finished,
 *	the channel is now available.
 * @NL80211_RADAR_CAC_ABORTED: Channel Availability Check has been पातed, no
 *	change to the channel status.
 * @NL80211_RADAR_NOP_FINISHED: The Non-Occupancy Period क्रम this channel is
 *	over, channel becomes usable.
 * @NL80211_RADAR_PRE_CAC_EXPIRED: Channel Availability Check करोne on this
 *	non-operating channel is expired and no दीर्घer valid. New CAC must
 *	be करोne on this channel beक्रमe starting the operation. This is not
 *	applicable क्रम ETSI dfs करोमुख्य where pre-CAC is valid क्रम ever.
 * @NL80211_RADAR_CAC_STARTED: Channel Availability Check has been started,
 *	should be generated by HW अगर NL80211_EXT_FEATURE_DFS_OFFLOAD is enabled.
 */
क्रमागत nl80211_radar_event अणु
	NL80211_RADAR_DETECTED,
	NL80211_RADAR_CAC_FINISHED,
	NL80211_RADAR_CAC_ABORTED,
	NL80211_RADAR_NOP_FINISHED,
	NL80211_RADAR_PRE_CAC_EXPIRED,
	NL80211_RADAR_CAC_STARTED,
पूर्ण;

/**
 * क्रमागत nl80211_dfs_state - DFS states क्रम channels
 *
 * Channel states used by the DFS code.
 *
 * @NL80211_DFS_USABLE: The channel can be used, but channel availability
 *	check (CAC) must be perक्रमmed beक्रमe using it क्रम AP or IBSS.
 * @NL80211_DFS_UNAVAILABLE: A radar has been detected on this channel, it
 *	is thereक्रमe marked as not available.
 * @NL80211_DFS_AVAILABLE: The channel has been CAC checked and is available.
 */
क्रमागत nl80211_dfs_state अणु
	NL80211_DFS_USABLE,
	NL80211_DFS_UNAVAILABLE,
	NL80211_DFS_AVAILABLE,
पूर्ण;

/**
 * क्रमागत nl80211_protocol_features - nl80211 protocol features
 * @NL80211_PROTOCOL_FEATURE_SPLIT_WIPHY_DUMP: nl80211 supports splitting
 *	wiphy dumps (अगर requested by the application with the attribute
 *	%NL80211_ATTR_SPLIT_WIPHY_DUMP. Also supported is filtering the
 *	wiphy dump by %NL80211_ATTR_WIPHY, %NL80211_ATTR_IFINDEX or
 *	%NL80211_ATTR_WDEV.
 */
क्रमागत nl80211_protocol_features अणु
	NL80211_PROTOCOL_FEATURE_SPLIT_WIPHY_DUMP =	1 << 0,
पूर्ण;

/**
 * क्रमागत nl80211_crit_proto_id - nl80211 critical protocol identअगरiers
 *
 * @NL80211_CRIT_PROTO_UNSPEC: protocol unspecअगरied.
 * @NL80211_CRIT_PROTO_DHCP: BOOTP or DHCPv6 protocol.
 * @NL80211_CRIT_PROTO_EAPOL: EAPOL protocol.
 * @NL80211_CRIT_PROTO_APIPA: APIPA protocol.
 * @NUM_NL80211_CRIT_PROTO: must be kept last.
 */
क्रमागत nl80211_crit_proto_id अणु
	NL80211_CRIT_PROTO_UNSPEC,
	NL80211_CRIT_PROTO_DHCP,
	NL80211_CRIT_PROTO_EAPOL,
	NL80211_CRIT_PROTO_APIPA,
	/* add other protocols beक्रमe this one */
	NUM_NL80211_CRIT_PROTO
पूर्ण;

/* maximum duration क्रम critical protocol measures */
#घोषणा NL80211_CRIT_PROTO_MAX_DURATION		5000 /* msec */

/**
 * क्रमागत nl80211_rxmgmt_flags - flags क्रम received management frame.
 *
 * Used by cfg80211_rx_mgmt()
 *
 * @NL80211_RXMGMT_FLAG_ANSWERED: frame was answered by device/driver.
 * @NL80211_RXMGMT_FLAG_EXTERNAL_AUTH: Host driver पूर्णांकends to offload
 *	the authentication. Exclusively defined क्रम host drivers that
 *	advertises the SME functionality but would like the userspace
 *	to handle certain authentication algorithms (e.g. SAE).
 */
क्रमागत nl80211_rxmgmt_flags अणु
	NL80211_RXMGMT_FLAG_ANSWERED = 1 << 0,
	NL80211_RXMGMT_FLAG_EXTERNAL_AUTH = 1 << 1,
पूर्ण;

/*
 * If this flag is unset, the lower 24 bits are an OUI, अगर set
 * a Linux nl80211 venकरोr ID is used (no such IDs are allocated
 * yet, so that's not valid so far)
 */
#घोषणा NL80211_VENDOR_ID_IS_LINUX	0x80000000

/**
 * काष्ठा nl80211_venकरोr_cmd_info - venकरोr command data
 * @venकरोr_id: If the %NL80211_VENDOR_ID_IS_LINUX flag is clear, then the
 *	value is a 24-bit OUI; अगर it is set then a separately allocated ID
 *	may be used, but no such IDs are allocated yet. New IDs should be
 *	added to this file when needed.
 * @subcmd: sub-command ID क्रम the command
 */
काष्ठा nl80211_venकरोr_cmd_info अणु
	__u32 venकरोr_id;
	__u32 subcmd;
पूर्ण;

/**
 * क्रमागत nl80211_tdls_peer_capability - TDLS peer flags.
 *
 * Used by tdls_mgmt() to determine which conditional elements need
 * to be added to TDLS Setup frames.
 *
 * @NL80211_TDLS_PEER_HT: TDLS peer is HT capable.
 * @NL80211_TDLS_PEER_VHT: TDLS peer is VHT capable.
 * @NL80211_TDLS_PEER_WMM: TDLS peer is WMM capable.
 * @NL80211_TDLS_PEER_HE: TDLS peer is HE capable.
 */
क्रमागत nl80211_tdls_peer_capability अणु
	NL80211_TDLS_PEER_HT = 1<<0,
	NL80211_TDLS_PEER_VHT = 1<<1,
	NL80211_TDLS_PEER_WMM = 1<<2,
	NL80211_TDLS_PEER_HE = 1<<3,
पूर्ण;

/**
 * क्रमागत nl80211_sched_scan_plan - scanning plan क्रम scheduled scan
 * @__NL80211_SCHED_SCAN_PLAN_INVALID: attribute number 0 is reserved
 * @NL80211_SCHED_SCAN_PLAN_INTERVAL: पूर्णांकerval between scan iterations. In
 *	seconds (u32).
 * @NL80211_SCHED_SCAN_PLAN_ITERATIONS: number of scan iterations in this
 *	scan plan (u32). The last scan plan must not specअगरy this attribute
 *	because it will run infinitely. A value of zero is invalid as it will
 *	make the scan plan meaningless.
 * @NL80211_SCHED_SCAN_PLAN_MAX: highest scheduled scan plan attribute number
 *	currently defined
 * @__NL80211_SCHED_SCAN_PLAN_AFTER_LAST: पूर्णांकernal use
 */
क्रमागत nl80211_sched_scan_plan अणु
	__NL80211_SCHED_SCAN_PLAN_INVALID,
	NL80211_SCHED_SCAN_PLAN_INTERVAL,
	NL80211_SCHED_SCAN_PLAN_ITERATIONS,

	/* keep last */
	__NL80211_SCHED_SCAN_PLAN_AFTER_LAST,
	NL80211_SCHED_SCAN_PLAN_MAX =
		__NL80211_SCHED_SCAN_PLAN_AFTER_LAST - 1
पूर्ण;

/**
 * काष्ठा nl80211_bss_select_rssi_adjust - RSSI adjusपंचांगent parameters.
 *
 * @band: band of BSS that must match क्रम RSSI value adjusपंचांगent. The value
 *	of this field is according to &क्रमागत nl80211_band.
 * @delta: value used to adjust the RSSI value of matching BSS in dB.
 */
काष्ठा nl80211_bss_select_rssi_adjust अणु
	__u8 band;
	__s8 delta;
पूर्ण __attribute__((packed));

/**
 * क्रमागत nl80211_bss_select_attr - attributes क्रम bss selection.
 *
 * @__NL80211_BSS_SELECT_ATTR_INVALID: reserved.
 * @NL80211_BSS_SELECT_ATTR_RSSI: Flag indicating only RSSI-based BSS selection
 *	is requested.
 * @NL80211_BSS_SELECT_ATTR_BAND_PREF: attribute indicating BSS
 *	selection should be करोne such that the specअगरied band is preferred.
 *	When there are multiple BSS-es in the preferred band, the driver
 *	shall use RSSI-based BSS selection as a second step. The value of
 *	this attribute is according to &क्रमागत nl80211_band (u32).
 * @NL80211_BSS_SELECT_ATTR_RSSI_ADJUST: When present the RSSI level क्रम
 *	BSS-es in the specअगरied band is to be adjusted beक्रमe करोing
 *	RSSI-based BSS selection. The attribute value is a packed काष्ठाure
 *	value as specअगरied by &काष्ठा nl80211_bss_select_rssi_adjust.
 * @NL80211_BSS_SELECT_ATTR_MAX: highest bss select attribute number.
 * @__NL80211_BSS_SELECT_ATTR_AFTER_LAST: पूर्णांकernal use.
 *
 * One and only one of these attributes are found within %NL80211_ATTR_BSS_SELECT
 * क्रम %NL80211_CMD_CONNECT. It specअगरies the required BSS selection behaviour
 * which the driver shall use.
 */
क्रमागत nl80211_bss_select_attr अणु
	__NL80211_BSS_SELECT_ATTR_INVALID,
	NL80211_BSS_SELECT_ATTR_RSSI,
	NL80211_BSS_SELECT_ATTR_BAND_PREF,
	NL80211_BSS_SELECT_ATTR_RSSI_ADJUST,

	/* keep last */
	__NL80211_BSS_SELECT_ATTR_AFTER_LAST,
	NL80211_BSS_SELECT_ATTR_MAX = __NL80211_BSS_SELECT_ATTR_AFTER_LAST - 1
पूर्ण;

/**
 * क्रमागत nl80211_nan_function_type - न_अंक function type
 *
 * Defines the function type of a न_अंक function
 *
 * @NL80211_न_अंक_FUNC_PUBLISH: function is publish
 * @NL80211_न_अंक_FUNC_SUBSCRIBE: function is subscribe
 * @NL80211_न_अंक_FUNC_FOLLOW_UP: function is follow-up
 */
क्रमागत nl80211_nan_function_type अणु
	NL80211_न_अंक_FUNC_PUBLISH,
	NL80211_न_अंक_FUNC_SUBSCRIBE,
	NL80211_न_अंक_FUNC_FOLLOW_UP,

	/* keep last */
	__NL80211_न_अंक_FUNC_TYPE_AFTER_LAST,
	NL80211_न_अंक_FUNC_MAX_TYPE = __NL80211_न_अंक_FUNC_TYPE_AFTER_LAST - 1,
पूर्ण;

/**
 * क्रमागत nl80211_nan_publish_type - न_अंक publish tx type
 *
 * Defines how to send publish Service Discovery Frames
 *
 * @NL80211_न_अंक_SOLICITED_PUBLISH: publish function is solicited
 * @NL80211_न_अंक_UNSOLICITED_PUBLISH: publish function is unsolicited
 */
क्रमागत nl80211_nan_publish_type अणु
	NL80211_न_अंक_SOLICITED_PUBLISH = 1 << 0,
	NL80211_न_अंक_UNSOLICITED_PUBLISH = 1 << 1,
पूर्ण;

/**
 * क्रमागत nl80211_nan_func_term_reason - न_अंक functions termination reason
 *
 * Defines termination reasons of a न_अंक function
 *
 * @NL80211_न_अंक_FUNC_TERM_REASON_USER_REQUEST: requested by user
 * @NL80211_न_अंक_FUNC_TERM_REASON_TTL_EXPIRED: समयout
 * @NL80211_न_अंक_FUNC_TERM_REASON_ERROR: errored
 */
क्रमागत nl80211_nan_func_term_reason अणु
	NL80211_न_अंक_FUNC_TERM_REASON_USER_REQUEST,
	NL80211_न_अंक_FUNC_TERM_REASON_TTL_EXPIRED,
	NL80211_न_अंक_FUNC_TERM_REASON_ERROR,
पूर्ण;

#घोषणा NL80211_न_अंक_FUNC_SERVICE_ID_LEN 6
#घोषणा NL80211_न_अंक_FUNC_SERVICE_SPEC_INFO_MAX_LEN 0xff
#घोषणा NL80211_न_अंक_FUNC_SRF_MAX_LEN 0xff

/**
 * क्रमागत nl80211_nan_func_attributes - न_अंक function attributes
 * @__NL80211_न_अंक_FUNC_INVALID: invalid
 * @NL80211_न_अंक_FUNC_TYPE: &क्रमागत nl80211_nan_function_type (u8).
 * @NL80211_न_अंक_FUNC_SERVICE_ID: 6 bytes of the service ID hash as
 *	specअगरied in न_अंक spec. This is a binary attribute.
 * @NL80211_न_अंक_FUNC_PUBLISH_TYPE: relevant अगर the function's type is
 *	publish. Defines the transmission type क्रम the publish Service Discovery
 *	Frame, see &क्रमागत nl80211_nan_publish_type. Its type is u8.
 * @NL80211_न_अंक_FUNC_PUBLISH_BCAST: relevant अगर the function is a solicited
 *	publish. Should the solicited publish Service Discovery Frame be sent to
 *	the न_अंक Broadcast address. This is a flag.
 * @NL80211_न_अंक_FUNC_SUBSCRIBE_ACTIVE: relevant अगर the function's type is
 *	subscribe. Is the subscribe active. This is a flag.
 * @NL80211_न_अंक_FUNC_FOLLOW_UP_ID: relevant अगर the function's type is follow up.
 *	The instance ID क्रम the follow up Service Discovery Frame. This is u8.
 * @NL80211_न_अंक_FUNC_FOLLOW_UP_REQ_ID: relevant अगर the function's type
 *	is follow up. This is a u8.
 *	The requestor instance ID क्रम the follow up Service Discovery Frame.
 * @NL80211_न_अंक_FUNC_FOLLOW_UP_DEST: the MAC address of the recipient of the
 *	follow up Service Discovery Frame. This is a binary attribute.
 * @NL80211_न_अंक_FUNC_CLOSE_RANGE: is this function limited क्रम devices in a
 *	बंद range. The range itself (RSSI) is defined by the device.
 *	This is a flag.
 * @NL80211_न_अंक_FUNC_TTL: strictly positive number of DWs this function should
 *	stay active. If not present infinite TTL is assumed. This is a u32.
 * @NL80211_न_अंक_FUNC_SERVICE_INFO: array of bytes describing the service
 *	specअगरic info. This is a binary attribute.
 * @NL80211_न_अंक_FUNC_SRF: Service Receive Filter. This is a nested attribute.
 *	See &क्रमागत nl80211_nan_srf_attributes.
 * @NL80211_न_अंक_FUNC_RX_MATCH_FILTER: Receive Matching filter. This is a nested
 *	attribute. It is a list of binary values.
 * @NL80211_न_अंक_FUNC_TX_MATCH_FILTER: Transmit Matching filter. This is a
 *	nested attribute. It is a list of binary values.
 * @NL80211_न_अंक_FUNC_INSTANCE_ID: The instance ID of the function.
 *	Its type is u8 and it cannot be 0.
 * @NL80211_न_अंक_FUNC_TERM_REASON: न_अंक function termination reason.
 *	See &क्रमागत nl80211_nan_func_term_reason.
 *
 * @NUM_NL80211_न_अंक_FUNC_ATTR: पूर्णांकernal
 * @NL80211_न_अंक_FUNC_ATTR_MAX: highest न_अंक function attribute
 */
क्रमागत nl80211_nan_func_attributes अणु
	__NL80211_न_अंक_FUNC_INVALID,
	NL80211_न_अंक_FUNC_TYPE,
	NL80211_न_अंक_FUNC_SERVICE_ID,
	NL80211_न_अंक_FUNC_PUBLISH_TYPE,
	NL80211_न_अंक_FUNC_PUBLISH_BCAST,
	NL80211_न_अंक_FUNC_SUBSCRIBE_ACTIVE,
	NL80211_न_अंक_FUNC_FOLLOW_UP_ID,
	NL80211_न_अंक_FUNC_FOLLOW_UP_REQ_ID,
	NL80211_न_अंक_FUNC_FOLLOW_UP_DEST,
	NL80211_न_अंक_FUNC_CLOSE_RANGE,
	NL80211_न_अंक_FUNC_TTL,
	NL80211_न_अंक_FUNC_SERVICE_INFO,
	NL80211_न_अंक_FUNC_SRF,
	NL80211_न_अंक_FUNC_RX_MATCH_FILTER,
	NL80211_न_अंक_FUNC_TX_MATCH_FILTER,
	NL80211_न_अंक_FUNC_INSTANCE_ID,
	NL80211_न_अंक_FUNC_TERM_REASON,

	/* keep last */
	NUM_NL80211_न_अंक_FUNC_ATTR,
	NL80211_न_अंक_FUNC_ATTR_MAX = NUM_NL80211_न_अंक_FUNC_ATTR - 1
पूर्ण;

/**
 * क्रमागत nl80211_nan_srf_attributes - न_अंक Service Response filter attributes
 * @__NL80211_न_अंक_SRF_INVALID: invalid
 * @NL80211_न_अंक_SRF_INCLUDE: present अगर the include bit of the SRF set.
 *	This is a flag.
 * @NL80211_न_अंक_SRF_BF: Bloom Filter. Present अगर and only अगर
 *	%NL80211_न_अंक_SRF_MAC_ADDRS isn't present. This attribute is binary.
 * @NL80211_न_अंक_SRF_BF_IDX: index of the Bloom Filter. Mandatory अगर
 *	%NL80211_न_अंक_SRF_BF is present. This is a u8.
 * @NL80211_न_अंक_SRF_MAC_ADDRS: list of MAC addresses क्रम the SRF. Present अगर
 *	and only अगर %NL80211_न_अंक_SRF_BF isn't present. This is a nested
 *	attribute. Each nested attribute is a MAC address.
 * @NUM_NL80211_न_अंक_SRF_ATTR: पूर्णांकernal
 * @NL80211_न_अंक_SRF_ATTR_MAX: highest न_अंक SRF attribute
 */
क्रमागत nl80211_nan_srf_attributes अणु
	__NL80211_न_अंक_SRF_INVALID,
	NL80211_न_अंक_SRF_INCLUDE,
	NL80211_न_अंक_SRF_BF,
	NL80211_न_अंक_SRF_BF_IDX,
	NL80211_न_अंक_SRF_MAC_ADDRS,

	/* keep last */
	NUM_NL80211_न_अंक_SRF_ATTR,
	NL80211_न_अंक_SRF_ATTR_MAX = NUM_NL80211_न_अंक_SRF_ATTR - 1,
पूर्ण;

/**
 * क्रमागत nl80211_nan_match_attributes - न_अंक match attributes
 * @__NL80211_न_अंक_MATCH_INVALID: invalid
 * @NL80211_न_अंक_MATCH_FUNC_LOCAL: the local function that had the
 *	match. This is a nested attribute.
 *	See &क्रमागत nl80211_nan_func_attributes.
 * @NL80211_न_अंक_MATCH_FUNC_PEER: the peer function
 *	that caused the match. This is a nested attribute.
 *	See &क्रमागत nl80211_nan_func_attributes.
 *
 * @NUM_NL80211_न_अंक_MATCH_ATTR: पूर्णांकernal
 * @NL80211_न_अंक_MATCH_ATTR_MAX: highest न_अंक match attribute
 */
क्रमागत nl80211_nan_match_attributes अणु
	__NL80211_न_अंक_MATCH_INVALID,
	NL80211_न_अंक_MATCH_FUNC_LOCAL,
	NL80211_न_अंक_MATCH_FUNC_PEER,

	/* keep last */
	NUM_NL80211_न_अंक_MATCH_ATTR,
	NL80211_न_अंक_MATCH_ATTR_MAX = NUM_NL80211_न_अंक_MATCH_ATTR - 1
पूर्ण;

/**
 * nl80211_बाह्यal_auth_action - Action to perक्रमm with बाह्यal
 *     authentication request. Used by NL80211_ATTR_EXTERNAL_AUTH_ACTION.
 * @NL80211_EXTERNAL_AUTH_START: Start the authentication.
 * @NL80211_EXTERNAL_AUTH_ABORT: Abort the ongoing authentication.
 */
क्रमागत nl80211_बाह्यal_auth_action अणु
	NL80211_EXTERNAL_AUTH_START,
	NL80211_EXTERNAL_AUTH_ABORT,
पूर्ण;

/**
 * क्रमागत nl80211_fपंचांग_responder_attributes - fine timing measurement
 *	responder attributes
 * @__NL80211_FTM_RESP_ATTR_INVALID: Invalid
 * @NL80211_FTM_RESP_ATTR_ENABLED: FTM responder is enabled
 * @NL80211_FTM_RESP_ATTR_LCI: The content of Measurement Report Element
 *	(9.4.2.22 in 802.11-2016) with type 8 - LCI (9.4.2.22.10),
 *	i.e. starting with the measurement token
 * @NL80211_FTM_RESP_ATTR_CIVIC: The content of Measurement Report Element
 *	(9.4.2.22 in 802.11-2016) with type 11 - Civic (Section 9.4.2.22.13),
 *	i.e. starting with the measurement token
 * @__NL80211_FTM_RESP_ATTR_LAST: Internal
 * @NL80211_FTM_RESP_ATTR_MAX: highest FTM responder attribute.
 */
क्रमागत nl80211_fपंचांग_responder_attributes अणु
	__NL80211_FTM_RESP_ATTR_INVALID,

	NL80211_FTM_RESP_ATTR_ENABLED,
	NL80211_FTM_RESP_ATTR_LCI,
	NL80211_FTM_RESP_ATTR_CIVICLOC,

	/* keep last */
	__NL80211_FTM_RESP_ATTR_LAST,
	NL80211_FTM_RESP_ATTR_MAX = __NL80211_FTM_RESP_ATTR_LAST - 1,
पूर्ण;

/*
 * क्रमागत nl80211_fपंचांग_responder_stats - FTM responder statistics
 *
 * These attribute types are used with %NL80211_ATTR_FTM_RESPONDER_STATS
 * when getting FTM responder statistics.
 *
 * @__NL80211_FTM_STATS_INVALID: attribute number 0 is reserved
 * @NL80211_FTM_STATS_SUCCESS_NUM: number of FTM sessions in which all frames
 *	were ssfully answered (u32)
 * @NL80211_FTM_STATS_PARTIAL_NUM: number of FTM sessions in which part of the
 *	frames were successfully answered (u32)
 * @NL80211_FTM_STATS_FAILED_NUM: number of failed FTM sessions (u32)
 * @NL80211_FTM_STATS_ASAP_NUM: number of ASAP sessions (u32)
 * @NL80211_FTM_STATS_NON_ASAP_NUM: number of non-ASAP sessions (u32)
 * @NL80211_FTM_STATS_TOTAL_DURATION_MSEC: total sessions durations - gives an
 *	indication of how much समय the responder was busy (u64, msec)
 * @NL80211_FTM_STATS_UNKNOWN_TRIGGERS_NUM: number of unknown FTM triggers -
 *	triggers from initiators that didn't finish successfully the negotiation
 *	phase with the responder (u32)
 * @NL80211_FTM_STATS_RESCHEDULE_REQUESTS_NUM: number of FTM reschedule requests
 *	- initiator asks क्रम a new scheduling although it alपढ़ोy has scheduled
 *	FTM slot (u32)
 * @NL80211_FTM_STATS_OUT_OF_WINDOW_TRIGGERS_NUM: number of FTM triggers out of
 *	scheduled winकरोw (u32)
 * @NL80211_FTM_STATS_PAD: used क्रम padding, ignore
 * @__NL80211_TXQ_ATTR_AFTER_LAST: Internal
 * @NL80211_FTM_STATS_MAX: highest possible FTM responder stats attribute
 */
क्रमागत nl80211_fपंचांग_responder_stats अणु
	__NL80211_FTM_STATS_INVALID,
	NL80211_FTM_STATS_SUCCESS_NUM,
	NL80211_FTM_STATS_PARTIAL_NUM,
	NL80211_FTM_STATS_FAILED_NUM,
	NL80211_FTM_STATS_ASAP_NUM,
	NL80211_FTM_STATS_NON_ASAP_NUM,
	NL80211_FTM_STATS_TOTAL_DURATION_MSEC,
	NL80211_FTM_STATS_UNKNOWN_TRIGGERS_NUM,
	NL80211_FTM_STATS_RESCHEDULE_REQUESTS_NUM,
	NL80211_FTM_STATS_OUT_OF_WINDOW_TRIGGERS_NUM,
	NL80211_FTM_STATS_PAD,

	/* keep last */
	__NL80211_FTM_STATS_AFTER_LAST,
	NL80211_FTM_STATS_MAX = __NL80211_FTM_STATS_AFTER_LAST - 1
पूर्ण;

/**
 * क्रमागत nl80211_preamble - frame preamble types
 * @NL80211_PREAMBLE_LEGACY: legacy (HR/DSSS, OFDM, ERP PHY) preamble
 * @NL80211_PREAMBLE_HT: HT preamble
 * @NL80211_PREAMBLE_VHT: VHT preamble
 * @NL80211_PREAMBLE_DMG: DMG preamble
 * @NL80211_PREAMBLE_HE: HE preamble
 */
क्रमागत nl80211_preamble अणु
	NL80211_PREAMBLE_LEGACY,
	NL80211_PREAMBLE_HT,
	NL80211_PREAMBLE_VHT,
	NL80211_PREAMBLE_DMG,
	NL80211_PREAMBLE_HE,
पूर्ण;

/**
 * क्रमागत nl80211_peer_measurement_type - peer measurement types
 * @NL80211_PMSR_TYPE_INVALID: invalid/unused, needed as we use
 *	these numbers also क्रम attributes
 *
 * @NL80211_PMSR_TYPE_FTM: flight समय measurement
 *
 * @NUM_NL80211_PMSR_TYPES: पूर्णांकernal
 * @NL80211_PMSR_TYPE_MAX: highest type number
 */
क्रमागत nl80211_peer_measurement_type अणु
	NL80211_PMSR_TYPE_INVALID,

	NL80211_PMSR_TYPE_FTM,

	NUM_NL80211_PMSR_TYPES,
	NL80211_PMSR_TYPE_MAX = NUM_NL80211_PMSR_TYPES - 1
पूर्ण;

/**
 * क्रमागत nl80211_peer_measurement_status - peer measurement status
 * @NL80211_PMSR_STATUS_SUCCESS: measurement completed successfully
 * @NL80211_PMSR_STATUS_REFUSED: measurement was locally refused
 * @NL80211_PMSR_STATUS_TIMEOUT: measurement समयd out
 * @NL80211_PMSR_STATUS_FAILURE: measurement failed, a type-dependent
 *	reason may be available in the response data
 */
क्रमागत nl80211_peer_measurement_status अणु
	NL80211_PMSR_STATUS_SUCCESS,
	NL80211_PMSR_STATUS_REFUSED,
	NL80211_PMSR_STATUS_TIMEOUT,
	NL80211_PMSR_STATUS_FAILURE,
पूर्ण;

/**
 * क्रमागत nl80211_peer_measurement_req - peer measurement request attributes
 * @__NL80211_PMSR_REQ_ATTR_INVALID: invalid
 *
 * @NL80211_PMSR_REQ_ATTR_DATA: This is a nested attribute with measurement
 *	type-specअगरic request data inside. The attributes used are from the
 *	क्रमागतs named nl80211_peer_measurement_<type>_req.
 * @NL80211_PMSR_REQ_ATTR_GET_AP_TSF: include AP TSF बारtamp, अगर supported
 *	(flag attribute)
 *
 * @NUM_NL80211_PMSR_REQ_ATTRS: पूर्णांकernal
 * @NL80211_PMSR_REQ_ATTR_MAX: highest attribute number
 */
क्रमागत nl80211_peer_measurement_req अणु
	__NL80211_PMSR_REQ_ATTR_INVALID,

	NL80211_PMSR_REQ_ATTR_DATA,
	NL80211_PMSR_REQ_ATTR_GET_AP_TSF,

	/* keep last */
	NUM_NL80211_PMSR_REQ_ATTRS,
	NL80211_PMSR_REQ_ATTR_MAX = NUM_NL80211_PMSR_REQ_ATTRS - 1
पूर्ण;

/**
 * क्रमागत nl80211_peer_measurement_resp - peer measurement response attributes
 * @__NL80211_PMSR_RESP_ATTR_INVALID: invalid
 *
 * @NL80211_PMSR_RESP_ATTR_DATA: This is a nested attribute with measurement
 *	type-specअगरic results inside. The attributes used are from the क्रमागतs
 *	named nl80211_peer_measurement_<type>_resp.
 * @NL80211_PMSR_RESP_ATTR_STATUS: u32 value with the measurement status
 *	(using values from &क्रमागत nl80211_peer_measurement_status.)
 * @NL80211_PMSR_RESP_ATTR_HOST_TIME: host समय (%CLOCK_BOOTTIME) when the
 *	result was measured; this value is not expected to be accurate to
 *	more than 20ms. (u64, nanoseconds)
 * @NL80211_PMSR_RESP_ATTR_AP_TSF: TSF of the AP that the पूर्णांकerface
 *	करोing the measurement is connected to when the result was measured.
 *	This shall be accurately reported अगर supported and requested
 *	(u64, usec)
 * @NL80211_PMSR_RESP_ATTR_FINAL: If results are sent to the host partially
 *	(*e.g. with FTM per-burst data) this flag will be cleared on all but
 *	the last result; अगर all results are combined it's set on the single
 *	result.
 * @NL80211_PMSR_RESP_ATTR_PAD: padding क्रम 64-bit attributes, ignore
 *
 * @NUM_NL80211_PMSR_RESP_ATTRS: पूर्णांकernal
 * @NL80211_PMSR_RESP_ATTR_MAX: highest attribute number
 */
क्रमागत nl80211_peer_measurement_resp अणु
	__NL80211_PMSR_RESP_ATTR_INVALID,

	NL80211_PMSR_RESP_ATTR_DATA,
	NL80211_PMSR_RESP_ATTR_STATUS,
	NL80211_PMSR_RESP_ATTR_HOST_TIME,
	NL80211_PMSR_RESP_ATTR_AP_TSF,
	NL80211_PMSR_RESP_ATTR_FINAL,
	NL80211_PMSR_RESP_ATTR_PAD,

	/* keep last */
	NUM_NL80211_PMSR_RESP_ATTRS,
	NL80211_PMSR_RESP_ATTR_MAX = NUM_NL80211_PMSR_RESP_ATTRS - 1
पूर्ण;

/**
 * क्रमागत nl80211_peer_measurement_peer_attrs - peer attributes क्रम measurement
 * @__NL80211_PMSR_PEER_ATTR_INVALID: invalid
 *
 * @NL80211_PMSR_PEER_ATTR_ADDR: peer's MAC address
 * @NL80211_PMSR_PEER_ATTR_CHAN: channel definition, nested, using top-level
 *	attributes like %NL80211_ATTR_WIPHY_FREQ etc.
 * @NL80211_PMSR_PEER_ATTR_REQ: This is a nested attribute indexed by
 *	measurement type, with attributes from the
 *	&क्रमागत nl80211_peer_measurement_req inside.
 * @NL80211_PMSR_PEER_ATTR_RESP: This is a nested attribute indexed by
 *	measurement type, with attributes from the
 *	&क्रमागत nl80211_peer_measurement_resp inside.
 *
 * @NUM_NL80211_PMSR_PEER_ATTRS: पूर्णांकernal
 * @NL80211_PMSR_PEER_ATTR_MAX: highest attribute number
 */
क्रमागत nl80211_peer_measurement_peer_attrs अणु
	__NL80211_PMSR_PEER_ATTR_INVALID,

	NL80211_PMSR_PEER_ATTR_ADDR,
	NL80211_PMSR_PEER_ATTR_CHAN,
	NL80211_PMSR_PEER_ATTR_REQ,
	NL80211_PMSR_PEER_ATTR_RESP,

	/* keep last */
	NUM_NL80211_PMSR_PEER_ATTRS,
	NL80211_PMSR_PEER_ATTR_MAX = NUM_NL80211_PMSR_PEER_ATTRS - 1,
पूर्ण;

/**
 * क्रमागत nl80211_peer_measurement_attrs - peer measurement attributes
 * @__NL80211_PMSR_ATTR_INVALID: invalid
 *
 * @NL80211_PMSR_ATTR_MAX_PEERS: u32 attribute used क्रम capability
 *	advertisement only, indicates the maximum number of peers
 *	measurements can be करोne with in a single request
 * @NL80211_PMSR_ATTR_REPORT_AP_TSF: flag attribute in capability
 *	indicating that the connected AP's TSF can be reported in
 *	measurement results
 * @NL80211_PMSR_ATTR_RANDOMIZE_MAC_ADDR: flag attribute in capability
 *	indicating that MAC address अक्रमomization is supported.
 * @NL80211_PMSR_ATTR_TYPE_CAPA: capabilities reported by the device,
 *	this contains a nesting indexed by measurement type, and
 *	type-specअगरic capabilities inside, which are from the क्रमागतs
 *	named nl80211_peer_measurement_<type>_capa.
 * @NL80211_PMSR_ATTR_PEERS: nested attribute, the nesting index is
 *	meaningless, just a list of peers to measure with, with the
 *	sub-attributes taken from
 *	&क्रमागत nl80211_peer_measurement_peer_attrs.
 *
 * @NUM_NL80211_PMSR_ATTR: पूर्णांकernal
 * @NL80211_PMSR_ATTR_MAX: highest attribute number
 */
क्रमागत nl80211_peer_measurement_attrs अणु
	__NL80211_PMSR_ATTR_INVALID,

	NL80211_PMSR_ATTR_MAX_PEERS,
	NL80211_PMSR_ATTR_REPORT_AP_TSF,
	NL80211_PMSR_ATTR_RANDOMIZE_MAC_ADDR,
	NL80211_PMSR_ATTR_TYPE_CAPA,
	NL80211_PMSR_ATTR_PEERS,

	/* keep last */
	NUM_NL80211_PMSR_ATTR,
	NL80211_PMSR_ATTR_MAX = NUM_NL80211_PMSR_ATTR - 1
पूर्ण;

/**
 * क्रमागत nl80211_peer_measurement_fपंचांग_capa - FTM capabilities
 * @__NL80211_PMSR_FTM_CAPA_ATTR_INVALID: invalid
 *
 * @NL80211_PMSR_FTM_CAPA_ATTR_ASAP: flag attribute indicating ASAP mode
 *	is supported
 * @NL80211_PMSR_FTM_CAPA_ATTR_NON_ASAP: flag attribute indicating non-ASAP
 *	mode is supported
 * @NL80211_PMSR_FTM_CAPA_ATTR_REQ_LCI: flag attribute indicating अगर LCI
 *	data can be requested during the measurement
 * @NL80211_PMSR_FTM_CAPA_ATTR_REQ_CIVICLOC: flag attribute indicating अगर civic
 *	location data can be requested during the measurement
 * @NL80211_PMSR_FTM_CAPA_ATTR_PREAMBLES: u32 biपंचांगap attribute of bits
 *	from &क्रमागत nl80211_preamble.
 * @NL80211_PMSR_FTM_CAPA_ATTR_BANDWIDTHS: biपंचांगap of values from
 *	&क्रमागत nl80211_chan_width indicating the supported channel
 *	bandwidths क्रम FTM. Note that a higher channel bandwidth may be
 *	configured to allow क्रम other measurements types with dअगरferent
 *	bandwidth requirement in the same measurement.
 * @NL80211_PMSR_FTM_CAPA_ATTR_MAX_BURSTS_EXPONENT: u32 attribute indicating
 *	the maximum bursts exponent that can be used (अगर not present anything
 *	is valid)
 * @NL80211_PMSR_FTM_CAPA_ATTR_MAX_FTMS_PER_BURST: u32 attribute indicating
 *	the maximum FTMs per burst (अगर not present anything is valid)
 * @NL80211_PMSR_FTM_CAPA_ATTR_TRIGGER_BASED: flag attribute indicating अगर
 *	trigger based ranging measurement is supported
 * @NL80211_PMSR_FTM_CAPA_ATTR_NON_TRIGGER_BASED: flag attribute indicating
 *	अगर non trigger based ranging measurement is supported
 *
 * @NUM_NL80211_PMSR_FTM_CAPA_ATTR: पूर्णांकernal
 * @NL80211_PMSR_FTM_CAPA_ATTR_MAX: highest attribute number
 */
क्रमागत nl80211_peer_measurement_fपंचांग_capa अणु
	__NL80211_PMSR_FTM_CAPA_ATTR_INVALID,

	NL80211_PMSR_FTM_CAPA_ATTR_ASAP,
	NL80211_PMSR_FTM_CAPA_ATTR_NON_ASAP,
	NL80211_PMSR_FTM_CAPA_ATTR_REQ_LCI,
	NL80211_PMSR_FTM_CAPA_ATTR_REQ_CIVICLOC,
	NL80211_PMSR_FTM_CAPA_ATTR_PREAMBLES,
	NL80211_PMSR_FTM_CAPA_ATTR_BANDWIDTHS,
	NL80211_PMSR_FTM_CAPA_ATTR_MAX_BURSTS_EXPONENT,
	NL80211_PMSR_FTM_CAPA_ATTR_MAX_FTMS_PER_BURST,
	NL80211_PMSR_FTM_CAPA_ATTR_TRIGGER_BASED,
	NL80211_PMSR_FTM_CAPA_ATTR_NON_TRIGGER_BASED,

	/* keep last */
	NUM_NL80211_PMSR_FTM_CAPA_ATTR,
	NL80211_PMSR_FTM_CAPA_ATTR_MAX = NUM_NL80211_PMSR_FTM_CAPA_ATTR - 1
पूर्ण;

/**
 * क्रमागत nl80211_peer_measurement_fपंचांग_req - FTM request attributes
 * @__NL80211_PMSR_FTM_REQ_ATTR_INVALID: invalid
 *
 * @NL80211_PMSR_FTM_REQ_ATTR_ASAP: ASAP mode requested (flag)
 * @NL80211_PMSR_FTM_REQ_ATTR_PREAMBLE: preamble type (see
 *	&क्रमागत nl80211_preamble), optional क्रम DMG (u32)
 * @NL80211_PMSR_FTM_REQ_ATTR_NUM_BURSTS_EXP: number of bursts exponent as in
 *	802.11-2016 9.4.2.168 "Fine Timing Measurement Parameters element"
 *	(u8, 0-15, optional with शेष 15 i.e. "no preference")
 * @NL80211_PMSR_FTM_REQ_ATTR_BURST_PERIOD: पूर्णांकerval between bursts in units
 *	of 100ms (u16, optional with शेष 0)
 * @NL80211_PMSR_FTM_REQ_ATTR_BURST_DURATION: burst duration, as in 802.11-2016
 *	Table 9-257 "Burst Duration field encoding" (u8, 0-15, optional with
 *	शेष 15 i.e. "no preference")
 * @NL80211_PMSR_FTM_REQ_ATTR_FTMS_PER_BURST: number of successful FTM frames
 *	requested per burst
 *	(u8, 0-31, optional with शेष 0 i.e. "no preference")
 * @NL80211_PMSR_FTM_REQ_ATTR_NUM_FTMR_RETRIES: number of FTMR frame retries
 *	(u8, शेष 3)
 * @NL80211_PMSR_FTM_REQ_ATTR_REQUEST_LCI: request LCI data (flag)
 * @NL80211_PMSR_FTM_REQ_ATTR_REQUEST_CIVICLOC: request civic location data
 *	(flag)
 * @NL80211_PMSR_FTM_REQ_ATTR_TRIGGER_BASED: request trigger based ranging
 *	measurement (flag).
 *	This attribute and %NL80211_PMSR_FTM_REQ_ATTR_NON_TRIGGER_BASED are
 *	mutually exclusive.
 *      अगर neither %NL80211_PMSR_FTM_REQ_ATTR_TRIGGER_BASED nor
 *	%NL80211_PMSR_FTM_REQ_ATTR_NON_TRIGGER_BASED is set, EDCA based
 *	ranging will be used.
 * @NL80211_PMSR_FTM_REQ_ATTR_NON_TRIGGER_BASED: request non trigger based
 *	ranging measurement (flag)
 *	This attribute and %NL80211_PMSR_FTM_REQ_ATTR_TRIGGER_BASED are
 *	mutually exclusive.
 *      अगर neither %NL80211_PMSR_FTM_REQ_ATTR_TRIGGER_BASED nor
 *	%NL80211_PMSR_FTM_REQ_ATTR_NON_TRIGGER_BASED is set, EDCA based
 *	ranging will be used.
 * @NL80211_PMSR_FTM_REQ_ATTR_LMR_FEEDBACK: negotiate क्रम LMR feedback. Only
 *	valid अगर either %NL80211_PMSR_FTM_REQ_ATTR_TRIGGER_BASED or
 *	%NL80211_PMSR_FTM_REQ_ATTR_NON_TRIGGER_BASED is set.
 *
 * @NUM_NL80211_PMSR_FTM_REQ_ATTR: पूर्णांकernal
 * @NL80211_PMSR_FTM_REQ_ATTR_MAX: highest attribute number
 */
क्रमागत nl80211_peer_measurement_fपंचांग_req अणु
	__NL80211_PMSR_FTM_REQ_ATTR_INVALID,

	NL80211_PMSR_FTM_REQ_ATTR_ASAP,
	NL80211_PMSR_FTM_REQ_ATTR_PREAMBLE,
	NL80211_PMSR_FTM_REQ_ATTR_NUM_BURSTS_EXP,
	NL80211_PMSR_FTM_REQ_ATTR_BURST_PERIOD,
	NL80211_PMSR_FTM_REQ_ATTR_BURST_DURATION,
	NL80211_PMSR_FTM_REQ_ATTR_FTMS_PER_BURST,
	NL80211_PMSR_FTM_REQ_ATTR_NUM_FTMR_RETRIES,
	NL80211_PMSR_FTM_REQ_ATTR_REQUEST_LCI,
	NL80211_PMSR_FTM_REQ_ATTR_REQUEST_CIVICLOC,
	NL80211_PMSR_FTM_REQ_ATTR_TRIGGER_BASED,
	NL80211_PMSR_FTM_REQ_ATTR_NON_TRIGGER_BASED,
	NL80211_PMSR_FTM_REQ_ATTR_LMR_FEEDBACK,

	/* keep last */
	NUM_NL80211_PMSR_FTM_REQ_ATTR,
	NL80211_PMSR_FTM_REQ_ATTR_MAX = NUM_NL80211_PMSR_FTM_REQ_ATTR - 1
पूर्ण;

/**
 * क्रमागत nl80211_peer_measurement_fपंचांग_failure_reasons - FTM failure reasons
 * @NL80211_PMSR_FTM_FAILURE_UNSPECIFIED: unspecअगरied failure, not used
 * @NL80211_PMSR_FTM_FAILURE_NO_RESPONSE: no response from the FTM responder
 * @NL80211_PMSR_FTM_FAILURE_REJECTED: FTM responder rejected measurement
 * @NL80211_PMSR_FTM_FAILURE_WRONG_CHANNEL: we alपढ़ोy know the peer is
 *	on a dअगरferent channel, so can't measure (if we didn't know, we'd
 *	try and get no response)
 * @NL80211_PMSR_FTM_FAILURE_PEER_NOT_CAPABLE: peer can't actually करो FTM
 * @NL80211_PMSR_FTM_FAILURE_INVALID_TIMESTAMP: invalid T1/T4 बारtamps
 *	received
 * @NL80211_PMSR_FTM_FAILURE_PEER_BUSY: peer reports busy, you may retry
 *	later (see %NL80211_PMSR_FTM_RESP_ATTR_BUSY_RETRY_TIME)
 * @NL80211_PMSR_FTM_FAILURE_BAD_CHANGED_PARAMS: parameters were changed
 *	by the peer and are no दीर्घer supported
 */
क्रमागत nl80211_peer_measurement_fपंचांग_failure_reasons अणु
	NL80211_PMSR_FTM_FAILURE_UNSPECIFIED,
	NL80211_PMSR_FTM_FAILURE_NO_RESPONSE,
	NL80211_PMSR_FTM_FAILURE_REJECTED,
	NL80211_PMSR_FTM_FAILURE_WRONG_CHANNEL,
	NL80211_PMSR_FTM_FAILURE_PEER_NOT_CAPABLE,
	NL80211_PMSR_FTM_FAILURE_INVALID_TIMESTAMP,
	NL80211_PMSR_FTM_FAILURE_PEER_BUSY,
	NL80211_PMSR_FTM_FAILURE_BAD_CHANGED_PARAMS,
पूर्ण;

/**
 * क्रमागत nl80211_peer_measurement_fपंचांग_resp - FTM response attributes
 * @__NL80211_PMSR_FTM_RESP_ATTR_INVALID: invalid
 *
 * @NL80211_PMSR_FTM_RESP_ATTR_FAIL_REASON: FTM-specअगरic failure reason
 *	(u32, optional)
 * @NL80211_PMSR_FTM_RESP_ATTR_BURST_INDEX: optional, अगर bursts are reported
 *	as separate results then it will be the burst index 0...(N-1) and
 *	the top level will indicate partial results (u32)
 * @NL80211_PMSR_FTM_RESP_ATTR_NUM_FTMR_ATTEMPTS: number of FTM Request frames
 *	transmitted (u32, optional)
 * @NL80211_PMSR_FTM_RESP_ATTR_NUM_FTMR_SUCCESSES: number of FTM Request frames
 *	that were acknowleged (u32, optional)
 * @NL80211_PMSR_FTM_RESP_ATTR_BUSY_RETRY_TIME: retry समय received from the
 *	busy peer (u32, seconds)
 * @NL80211_PMSR_FTM_RESP_ATTR_NUM_BURSTS_EXP: actual number of bursts exponent
 *	used by the responder (similar to request, u8)
 * @NL80211_PMSR_FTM_RESP_ATTR_BURST_DURATION: actual burst duration used by
 *	the responder (similar to request, u8)
 * @NL80211_PMSR_FTM_RESP_ATTR_FTMS_PER_BURST: actual FTMs per burst used
 *	by the responder (similar to request, u8)
 * @NL80211_PMSR_FTM_RESP_ATTR_RSSI_AVG: average RSSI across all FTM action
 *	frames (optional, s32, 1/2 dBm)
 * @NL80211_PMSR_FTM_RESP_ATTR_RSSI_SPREAD: RSSI spपढ़ो across all FTM action
 *	frames (optional, s32, 1/2 dBm)
 * @NL80211_PMSR_FTM_RESP_ATTR_TX_RATE: bitrate we used क्रम the response to the
 *	FTM action frame (optional, nested, using &क्रमागत nl80211_rate_info
 *	attributes)
 * @NL80211_PMSR_FTM_RESP_ATTR_RX_RATE: bitrate the responder used क्रम the FTM
 *	action frame (optional, nested, using &क्रमागत nl80211_rate_info attrs)
 * @NL80211_PMSR_FTM_RESP_ATTR_RTT_AVG: average RTT (s64, picoseconds, optional
 *	but one of RTT/DIST must be present)
 * @NL80211_PMSR_FTM_RESP_ATTR_RTT_VARIANCE: RTT variance (u64, ps^2, note that
 *	standard deviation is the square root of variance, optional)
 * @NL80211_PMSR_FTM_RESP_ATTR_RTT_SPREAD: RTT spपढ़ो (u64, picoseconds,
 *	optional)
 * @NL80211_PMSR_FTM_RESP_ATTR_DIST_AVG: average distance (s64, mm, optional
 *	but one of RTT/DIST must be present)
 * @NL80211_PMSR_FTM_RESP_ATTR_DIST_VARIANCE: distance variance (u64, mm^2, note
 *	that standard deviation is the square root of variance, optional)
 * @NL80211_PMSR_FTM_RESP_ATTR_DIST_SPREAD: distance spपढ़ो (u64, mm, optional)
 * @NL80211_PMSR_FTM_RESP_ATTR_LCI: LCI data from peer (binary, optional);
 *	this is the contents of the Measurement Report Element (802.11-2016
 *	9.4.2.22.1) starting with the Measurement Token, with Measurement
 *	Type 8.
 * @NL80211_PMSR_FTM_RESP_ATTR_CIVICLOC: civic location data from peer
 *	(binary, optional);
 *	this is the contents of the Measurement Report Element (802.11-2016
 *	9.4.2.22.1) starting with the Measurement Token, with Measurement
 *	Type 11.
 * @NL80211_PMSR_FTM_RESP_ATTR_PAD: ignore, क्रम u64/s64 padding only
 *
 * @NUM_NL80211_PMSR_FTM_RESP_ATTR: पूर्णांकernal
 * @NL80211_PMSR_FTM_RESP_ATTR_MAX: highest attribute number
 */
क्रमागत nl80211_peer_measurement_fपंचांग_resp अणु
	__NL80211_PMSR_FTM_RESP_ATTR_INVALID,

	NL80211_PMSR_FTM_RESP_ATTR_FAIL_REASON,
	NL80211_PMSR_FTM_RESP_ATTR_BURST_INDEX,
	NL80211_PMSR_FTM_RESP_ATTR_NUM_FTMR_ATTEMPTS,
	NL80211_PMSR_FTM_RESP_ATTR_NUM_FTMR_SUCCESSES,
	NL80211_PMSR_FTM_RESP_ATTR_BUSY_RETRY_TIME,
	NL80211_PMSR_FTM_RESP_ATTR_NUM_BURSTS_EXP,
	NL80211_PMSR_FTM_RESP_ATTR_BURST_DURATION,
	NL80211_PMSR_FTM_RESP_ATTR_FTMS_PER_BURST,
	NL80211_PMSR_FTM_RESP_ATTR_RSSI_AVG,
	NL80211_PMSR_FTM_RESP_ATTR_RSSI_SPREAD,
	NL80211_PMSR_FTM_RESP_ATTR_TX_RATE,
	NL80211_PMSR_FTM_RESP_ATTR_RX_RATE,
	NL80211_PMSR_FTM_RESP_ATTR_RTT_AVG,
	NL80211_PMSR_FTM_RESP_ATTR_RTT_VARIANCE,
	NL80211_PMSR_FTM_RESP_ATTR_RTT_SPREAD,
	NL80211_PMSR_FTM_RESP_ATTR_DIST_AVG,
	NL80211_PMSR_FTM_RESP_ATTR_DIST_VARIANCE,
	NL80211_PMSR_FTM_RESP_ATTR_DIST_SPREAD,
	NL80211_PMSR_FTM_RESP_ATTR_LCI,
	NL80211_PMSR_FTM_RESP_ATTR_CIVICLOC,
	NL80211_PMSR_FTM_RESP_ATTR_PAD,

	/* keep last */
	NUM_NL80211_PMSR_FTM_RESP_ATTR,
	NL80211_PMSR_FTM_RESP_ATTR_MAX = NUM_NL80211_PMSR_FTM_RESP_ATTR - 1
पूर्ण;

/**
 * क्रमागत nl80211_obss_pd_attributes - OBSS packet detection attributes
 * @__NL80211_HE_OBSS_PD_ATTR_INVALID: Invalid
 *
 * @NL80211_HE_OBSS_PD_ATTR_MIN_OFFSET: the OBSS PD minimum tx घातer offset.
 * @NL80211_HE_OBSS_PD_ATTR_MAX_OFFSET: the OBSS PD maximum tx घातer offset.
 * @NL80211_HE_OBSS_PD_ATTR_NON_SRG_MAX_OFFSET: the non-SRG OBSS PD maximum
 *	tx घातer offset.
 * @NL80211_HE_OBSS_PD_ATTR_BSS_COLOR_BITMAP: biपंचांगap that indicates the BSS color
 *	values used by members of the SRG.
 * @NL80211_HE_OBSS_PD_ATTR_PARTIAL_BSSID_BITMAP: biपंचांगap that indicates the partial
 *	BSSID values used by members of the SRG.
 * @NL80211_HE_OBSS_PD_ATTR_SR_CTRL: The SR Control field of SRP element.
 *
 * @__NL80211_HE_OBSS_PD_ATTR_LAST: Internal
 * @NL80211_HE_OBSS_PD_ATTR_MAX: highest OBSS PD attribute.
 */
क्रमागत nl80211_obss_pd_attributes अणु
	__NL80211_HE_OBSS_PD_ATTR_INVALID,

	NL80211_HE_OBSS_PD_ATTR_MIN_OFFSET,
	NL80211_HE_OBSS_PD_ATTR_MAX_OFFSET,
	NL80211_HE_OBSS_PD_ATTR_NON_SRG_MAX_OFFSET,
	NL80211_HE_OBSS_PD_ATTR_BSS_COLOR_BITMAP,
	NL80211_HE_OBSS_PD_ATTR_PARTIAL_BSSID_BITMAP,
	NL80211_HE_OBSS_PD_ATTR_SR_CTRL,

	/* keep last */
	__NL80211_HE_OBSS_PD_ATTR_LAST,
	NL80211_HE_OBSS_PD_ATTR_MAX = __NL80211_HE_OBSS_PD_ATTR_LAST - 1,
पूर्ण;

/**
 * क्रमागत nl80211_bss_color_attributes - BSS Color attributes
 * @__NL80211_HE_BSS_COLOR_ATTR_INVALID: Invalid
 *
 * @NL80211_HE_BSS_COLOR_ATTR_COLOR: the current BSS Color.
 * @NL80211_HE_BSS_COLOR_ATTR_DISABLED: is BSS coloring disabled.
 * @NL80211_HE_BSS_COLOR_ATTR_PARTIAL: the AID equation to be used..
 *
 * @__NL80211_HE_BSS_COLOR_ATTR_LAST: Internal
 * @NL80211_HE_BSS_COLOR_ATTR_MAX: highest BSS Color attribute.
 */
क्रमागत nl80211_bss_color_attributes अणु
	__NL80211_HE_BSS_COLOR_ATTR_INVALID,

	NL80211_HE_BSS_COLOR_ATTR_COLOR,
	NL80211_HE_BSS_COLOR_ATTR_DISABLED,
	NL80211_HE_BSS_COLOR_ATTR_PARTIAL,

	/* keep last */
	__NL80211_HE_BSS_COLOR_ATTR_LAST,
	NL80211_HE_BSS_COLOR_ATTR_MAX = __NL80211_HE_BSS_COLOR_ATTR_LAST - 1,
पूर्ण;

/**
 * क्रमागत nl80211_अगरtype_akm_attributes - पूर्णांकerface type AKM attributes
 * @__NL80211_IFTYPE_AKM_ATTR_INVALID: Invalid
 *
 * @NL80211_IFTYPE_AKM_ATTR_IFTYPES: nested attribute containing a flag
 *	attribute क्रम each पूर्णांकerface type that supports AKM suites specअगरied in
 *	%NL80211_IFTYPE_AKM_ATTR_SUITES
 * @NL80211_IFTYPE_AKM_ATTR_SUITES: an array of u32. Used to indicate supported
 *	AKM suites क्रम the specअगरied पूर्णांकerface types.
 *
 * @__NL80211_IFTYPE_AKM_ATTR_LAST: Internal
 * @NL80211_IFTYPE_AKM_ATTR_MAX: highest पूर्णांकerface type AKM attribute.
 */
क्रमागत nl80211_अगरtype_akm_attributes अणु
	__NL80211_IFTYPE_AKM_ATTR_INVALID,

	NL80211_IFTYPE_AKM_ATTR_IFTYPES,
	NL80211_IFTYPE_AKM_ATTR_SUITES,

	/* keep last */
	__NL80211_IFTYPE_AKM_ATTR_LAST,
	NL80211_IFTYPE_AKM_ATTR_MAX = __NL80211_IFTYPE_AKM_ATTR_LAST - 1,
पूर्ण;

/**
 * क्रमागत nl80211_fils_discovery_attributes - FILS discovery configuration
 * from IEEE Std 802.11ai-2016, Annex C.3 MIB detail.
 *
 * @__NL80211_FILS_DISCOVERY_ATTR_INVALID: Invalid
 *
 * @NL80211_FILS_DISCOVERY_ATTR_पूर्णांक_न्यून: Minimum packet पूर्णांकerval (u32, TU).
 *	Allowed range: 0..10000 (TU = Time Unit)
 * @NL80211_FILS_DISCOVERY_ATTR_पूर्णांक_उच्च: Maximum packet पूर्णांकerval (u32, TU).
 *	Allowed range: 0..10000 (TU = Time Unit)
 * @NL80211_FILS_DISCOVERY_ATTR_TMPL: Template data क्रम FILS discovery action
 *	frame including the headers.
 *
 * @__NL80211_FILS_DISCOVERY_ATTR_LAST: Internal
 * @NL80211_FILS_DISCOVERY_ATTR_MAX: highest attribute
 */
क्रमागत nl80211_fils_discovery_attributes अणु
	__NL80211_FILS_DISCOVERY_ATTR_INVALID,

	NL80211_FILS_DISCOVERY_ATTR_पूर्णांक_न्यून,
	NL80211_FILS_DISCOVERY_ATTR_पूर्णांक_उच्च,
	NL80211_FILS_DISCOVERY_ATTR_TMPL,

	/* keep last */
	__NL80211_FILS_DISCOVERY_ATTR_LAST,
	NL80211_FILS_DISCOVERY_ATTR_MAX = __NL80211_FILS_DISCOVERY_ATTR_LAST - 1
पूर्ण;

/*
 * FILS discovery ढाँचा minimum length with action frame headers and
 * mandatory fields.
 */
#घोषणा NL80211_FILS_DISCOVERY_TMPL_MIN_LEN 42

/**
 * क्रमागत nl80211_unsol_bcast_probe_resp_attributes - Unsolicited broadcast probe
 *	response configuration. Applicable only in 6GHz.
 *
 * @__NL80211_UNSOL_BCAST_PROBE_RESP_ATTR_INVALID: Invalid
 *
 * @NL80211_UNSOL_BCAST_PROBE_RESP_ATTR_INT: Maximum packet पूर्णांकerval (u32, TU).
 *	Allowed range: 0..20 (TU = Time Unit). IEEE P802.11ax/D6.0
 *	26.17.2.3.2 (AP behavior क्रम fast passive scanning).
 * @NL80211_UNSOL_BCAST_PROBE_RESP_ATTR_TMPL: Unsolicited broadcast probe response
 *	frame ढाँचा (binary).
 *
 * @__NL80211_UNSOL_BCAST_PROBE_RESP_ATTR_LAST: Internal
 * @NL80211_UNSOL_BCAST_PROBE_RESP_ATTR_MAX: highest attribute
 */
क्रमागत nl80211_unsol_bcast_probe_resp_attributes अणु
	__NL80211_UNSOL_BCAST_PROBE_RESP_ATTR_INVALID,

	NL80211_UNSOL_BCAST_PROBE_RESP_ATTR_INT,
	NL80211_UNSOL_BCAST_PROBE_RESP_ATTR_TMPL,

	/* keep last */
	__NL80211_UNSOL_BCAST_PROBE_RESP_ATTR_LAST,
	NL80211_UNSOL_BCAST_PROBE_RESP_ATTR_MAX =
		__NL80211_UNSOL_BCAST_PROBE_RESP_ATTR_LAST - 1
पूर्ण;

/**
 * क्रमागत nl80211_sae_pwe_mechanism - The mechanism(s) allowed क्रम SAE PWE
 *	derivation. Applicable only when WPA3-Personal SAE authentication is
 *	used.
 *
 * @NL80211_SAE_PWE_UNSPECIFIED: not specअगरied, used पूर्णांकernally to indicate that
 *	attribute is not present from userspace.
 * @NL80211_SAE_PWE_HUNT_AND_PECK: hunting-and-pecking loop only
 * @NL80211_SAE_PWE_HASH_TO_ELEMENT: hash-to-element only
 * @NL80211_SAE_PWE_BOTH: both hunting-and-pecking loop and hash-to-element
 *	can be used.
 */
क्रमागत nl80211_sae_pwe_mechanism अणु
	NL80211_SAE_PWE_UNSPECIFIED,
	NL80211_SAE_PWE_HUNT_AND_PECK,
	NL80211_SAE_PWE_HASH_TO_ELEMENT,
	NL80211_SAE_PWE_BOTH,
पूर्ण;

/**
 * क्रमागत nl80211_sar_type - type of SAR specs
 *
 * @NL80211_SAR_TYPE_POWER: घातer limitation specअगरied in 0.25dBm unit
 *
 */
क्रमागत nl80211_sar_type अणु
	NL80211_SAR_TYPE_POWER,

	/* add new type here */

	/* Keep last */
	NUM_NL80211_SAR_TYPE,
पूर्ण;

/**
 * क्रमागत nl80211_sar_attrs - Attributes क्रम SAR spec
 *
 * @NL80211_SAR_ATTR_TYPE: the SAR type as defined in &क्रमागत nl80211_sar_type.
 *
 * @NL80211_SAR_ATTR_SPECS: Nested array of SAR घातer
 *	limit specअगरications. Each specअगरication contains a set
 *	of %nl80211_sar_specs_attrs.
 *
 *	For SET operation, it contains array of %NL80211_SAR_ATTR_SPECS_POWER
 *	and %NL80211_SAR_ATTR_SPECS_RANGE_INDEX.
 *
 *	For sar_capa dump, it contains array of
 *	%NL80211_SAR_ATTR_SPECS_START_FREQ
 *	and %NL80211_SAR_ATTR_SPECS_END_FREQ.
 *
 * @__NL80211_SAR_ATTR_LAST: Internal
 * @NL80211_SAR_ATTR_MAX: highest sar attribute
 *
 * These attributes are used with %NL80211_CMD_SET_SAR_SPEC
 */
क्रमागत nl80211_sar_attrs अणु
	__NL80211_SAR_ATTR_INVALID,

	NL80211_SAR_ATTR_TYPE,
	NL80211_SAR_ATTR_SPECS,

	__NL80211_SAR_ATTR_LAST,
	NL80211_SAR_ATTR_MAX = __NL80211_SAR_ATTR_LAST - 1,
पूर्ण;

/**
 * क्रमागत nl80211_sar_specs_attrs - Attributes क्रम SAR घातer limit specs
 *
 * @NL80211_SAR_ATTR_SPECS_POWER: Required (s32)value to specअगरy the actual
 *	घातer limit value in units of 0.25 dBm अगर type is
 *	NL80211_SAR_TYPE_POWER. (i.e., a value of 44 represents 11 dBm).
 *	0 means userspace करोesn't have SAR limitation on this associated range.
 *
 * @NL80211_SAR_ATTR_SPECS_RANGE_INDEX: Required (u32) value to specअगरy the
 *	index of exported freq range table and the associated घातer limitation
 *	is applied to this range.
 *
 *	Userspace isn't required to set all the ranges advertised by WLAN driver,
 *	and userspace can skip some certain ranges. These skipped ranges करोn't
 *	have SAR limitations, and they are same as setting the
 *	%NL80211_SAR_ATTR_SPECS_POWER to any unreasonable high value because any
 *	value higher than regulatory allowed value just means SAR घातer
 *	limitation is हटाओd, but it's required to set at least one range.
 *	It's not allowed to set duplicated range in one SET operation.
 *
 *	Every SET operation overग_लिखोs previous SET operation.
 *
 * @NL80211_SAR_ATTR_SPECS_START_FREQ: Required (u32) value to specअगरy the start
 *	frequency of this range edge when रेजिस्टरing SAR capability to wiphy.
 *	It's not a channel center frequency. The unit is kHz.
 *
 * @NL80211_SAR_ATTR_SPECS_END_FREQ: Required (u32) value to specअगरy the end
 *	frequency of this range edge when रेजिस्टरing SAR capability to wiphy.
 *	It's not a channel center frequency. The unit is kHz.
 *
 * @__NL80211_SAR_ATTR_SPECS_LAST: Internal
 * @NL80211_SAR_ATTR_SPECS_MAX: highest sar specs attribute
 */
क्रमागत nl80211_sar_specs_attrs अणु
	__NL80211_SAR_ATTR_SPECS_INVALID,

	NL80211_SAR_ATTR_SPECS_POWER,
	NL80211_SAR_ATTR_SPECS_RANGE_INDEX,
	NL80211_SAR_ATTR_SPECS_START_FREQ,
	NL80211_SAR_ATTR_SPECS_END_FREQ,

	__NL80211_SAR_ATTR_SPECS_LAST,
	NL80211_SAR_ATTR_SPECS_MAX = __NL80211_SAR_ATTR_SPECS_LAST - 1,
पूर्ण;

#पूर्ण_अगर /* __LINUX_NL80211_H */
