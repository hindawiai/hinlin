<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM cfg80211

#अगर !defined(__RDEV_OPS_TRACE) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __RDEV_OPS_TRACE

#समावेश <linux/tracepoपूर्णांक.h>

#समावेश <linux/rtnetlink.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/cfg80211.h>
#समावेश "core.h"

#घोषणा MAC_ENTRY(entry_mac) __array(u8, entry_mac, ETH_ALEN)
#घोषणा MAC_ASSIGN(entry_mac, given_mac) करो अणु			     \
	अगर (given_mac)						     \
		स_नकल(__entry->entry_mac, given_mac, ETH_ALEN);     \
	अन्यथा							     \
		eth_zero_addr(__entry->entry_mac);		     \
	पूर्ण जबतक (0)
#घोषणा MAC_PR_FMT "%pM"
#घोषणा MAC_PR_ARG(entry_mac) (__entry->entry_mac)

#घोषणा MAXNAME		32
#घोषणा WIPHY_ENTRY	__array(अक्षर, wiphy_name, 32)
#घोषणा WIPHY_ASSIGN	strlcpy(__entry->wiphy_name, wiphy_name(wiphy), MAXNAME)
#घोषणा WIPHY_PR_FMT	"%s"
#घोषणा WIPHY_PR_ARG	__entry->wiphy_name

#घोषणा WDEV_ENTRY	__field(u32, id)
#घोषणा WDEV_ASSIGN	(__entry->id) = (!IS_ERR_OR_शून्य(wdev)	\
					 ? wdev->identअगरier : 0)
#घोषणा WDEV_PR_FMT	"wdev(%u)"
#घोषणा WDEV_PR_ARG	(__entry->id)

#घोषणा NETDEV_ENTRY	__array(अक्षर, name, IFNAMSIZ) \
			__field(पूर्णांक, अगरindex)
#घोषणा NETDEV_ASSIGN					       \
	करो अणु						       \
		स_नकल(__entry->name, netdev->name, IFNAMSIZ); \
		(__entry->अगरindex) = (netdev->अगरindex);	       \
	पूर्ण जबतक (0)
#घोषणा NETDEV_PR_FMT	"netdev:%s(%d)"
#घोषणा NETDEV_PR_ARG	__entry->name, __entry->अगरindex

#घोषणा MESH_CFG_ENTRY __field(u16, करोt11MeshRetryTimeout)		   \
		       __field(u16, करोt11MeshConfirmTimeout)		   \
		       __field(u16, करोt11MeshHoldingTimeout)		   \
		       __field(u16, करोt11MeshMaxPeerLinks)		   \
		       __field(u8, करोt11MeshMaxRetries)			   \
		       __field(u8, करोt11MeshTTL)			   \
		       __field(u8, element_ttl)				   \
		       __field(bool, स्वतः_खोलो_plinks)			   \
		       __field(u32, करोt11MeshNbrOffsetMaxNeighbor)	   \
		       __field(u8, करोt11MeshHWMPmaxPREQretries)		   \
		       __field(u32, path_refresh_समय)			   \
		       __field(u32, करोt11MeshHWMPactivePathTimeout)	   \
		       __field(u16, min_discovery_समयout)		   \
		       __field(u16, करोt11MeshHWMPpreqMinInterval)	   \
		       __field(u16, करोt11MeshHWMPperrMinInterval)	   \
		       __field(u16, करोt11MeshHWMPnetDiameterTraversalTime) \
		       __field(u8, करोt11MeshHWMPRootMode)		   \
		       __field(u16, करोt11MeshHWMPRannInterval)		   \
		       __field(bool, करोt11MeshGateAnnouncementProtocol)	   \
		       __field(bool, करोt11MeshForwarding)		   \
		       __field(s32, rssi_threshold)			   \
		       __field(u16, ht_opmode)				   \
		       __field(u32, करोt11MeshHWMPactivePathToRootTimeout)  \
		       __field(u16, करोt11MeshHWMProotInterval)		   \
		       __field(u16, करोt11MeshHWMPconfirmationInterval)	   \
		       __field(bool, करोt11MeshNolearn)
#घोषणा MESH_CFG_ASSIGN							      \
	करो अणु								      \
		__entry->करोt11MeshRetryTimeout = conf->करोt11MeshRetryTimeout; \
		__entry->करोt11MeshConfirmTimeout =			      \
				conf->करोt11MeshConfirmTimeout;		      \
		__entry->करोt11MeshHoldingTimeout =			      \
				conf->करोt11MeshHoldingTimeout;		      \
		__entry->करोt11MeshMaxPeerLinks = conf->करोt11MeshMaxPeerLinks; \
		__entry->करोt11MeshMaxRetries = conf->करोt11MeshMaxRetries;     \
		__entry->करोt11MeshTTL = conf->करोt11MeshTTL;		      \
		__entry->element_ttl = conf->element_ttl;		      \
		__entry->स्वतः_खोलो_plinks = conf->स्वतः_खोलो_plinks;	      \
		__entry->करोt11MeshNbrOffsetMaxNeighbor =		      \
				conf->करोt11MeshNbrOffsetMaxNeighbor;	      \
		__entry->करोt11MeshHWMPmaxPREQretries =			      \
				conf->करोt11MeshHWMPmaxPREQretries;	      \
		__entry->path_refresh_समय = conf->path_refresh_समय;	      \
		__entry->करोt11MeshHWMPactivePathTimeout =		      \
				conf->करोt11MeshHWMPactivePathTimeout;	      \
		__entry->min_discovery_समयout = conf->min_discovery_समयout; \
		__entry->करोt11MeshHWMPpreqMinInterval =			      \
				conf->करोt11MeshHWMPpreqMinInterval;	      \
		__entry->करोt11MeshHWMPperrMinInterval =			      \
				conf->करोt11MeshHWMPperrMinInterval;	      \
		__entry->करोt11MeshHWMPnetDiameterTraversalTime =	      \
				conf->करोt11MeshHWMPnetDiameterTraversalTime;  \
		__entry->करोt11MeshHWMPRootMode = conf->करोt11MeshHWMPRootMode; \
		__entry->करोt11MeshHWMPRannInterval =			      \
				conf->करोt11MeshHWMPRannInterval;	      \
		__entry->करोt11MeshGateAnnouncementProtocol =		      \
				conf->करोt11MeshGateAnnouncementProtocol;      \
		__entry->करोt11MeshForwarding = conf->करोt11MeshForwarding;     \
		__entry->rssi_threshold = conf->rssi_threshold;		      \
		__entry->ht_opmode = conf->ht_opmode;			      \
		__entry->करोt11MeshHWMPactivePathToRootTimeout =		      \
				conf->करोt11MeshHWMPactivePathToRootTimeout;   \
		__entry->करोt11MeshHWMProotInterval =			      \
				conf->करोt11MeshHWMProotInterval;	      \
		__entry->करोt11MeshHWMPconfirmationInterval =		      \
				conf->करोt11MeshHWMPconfirmationInterval;      \
		__entry->करोt11MeshNolearn = conf->करोt11MeshNolearn;	      \
	पूर्ण जबतक (0)

#घोषणा CHAN_ENTRY __field(क्रमागत nl80211_band, band) \
		   __field(u32, center_freq)		\
		   __field(u16, freq_offset)
#घोषणा CHAN_ASSIGN(chan)					  \
	करो अणु							  \
		अगर (chan) अणु					  \
			__entry->band = chan->band;		  \
			__entry->center_freq = chan->center_freq; \
			__entry->freq_offset = chan->freq_offset; \
		पूर्ण अन्यथा अणु					  \
			__entry->band = 0;			  \
			__entry->center_freq = 0;		  \
			__entry->freq_offset = 0;		  \
		पूर्ण						  \
	पूर्ण जबतक (0)
#घोषणा CHAN_PR_FMT "band: %d, freq: %u.%03u"
#घोषणा CHAN_PR_ARG __entry->band, __entry->center_freq, __entry->freq_offset

#घोषणा CHAN_DEF_ENTRY __field(क्रमागत nl80211_band, band)		\
		       __field(u32, control_freq)			\
		       __field(u32, freq_offset)			\
		       __field(u32, width)				\
		       __field(u32, center_freq1)			\
		       __field(u32, freq1_offset)			\
		       __field(u32, center_freq2)
#घोषणा CHAN_DEF_ASSIGN(chandef)					\
	करो अणु								\
		अगर ((chandef) && (chandef)->chan) अणु			\
			__entry->band = (chandef)->chan->band;		\
			__entry->control_freq =				\
				(chandef)->chan->center_freq;		\
			__entry->freq_offset =				\
				(chandef)->chan->freq_offset;		\
			__entry->width = (chandef)->width;		\
			__entry->center_freq1 = (chandef)->center_freq1;\
			__entry->freq1_offset = (chandef)->freq1_offset;\
			__entry->center_freq2 = (chandef)->center_freq2;\
		पूर्ण अन्यथा अणु						\
			__entry->band = 0;				\
			__entry->control_freq = 0;			\
			__entry->freq_offset = 0;			\
			__entry->width = 0;				\
			__entry->center_freq1 = 0;			\
			__entry->freq1_offset = 0;			\
			__entry->center_freq2 = 0;			\
		पूर्ण							\
	पूर्ण जबतक (0)
#घोषणा CHAN_DEF_PR_FMT							\
	"band: %d, control freq: %u.%03u, width: %d, cf1: %u.%03u, cf2: %u"
#घोषणा CHAN_DEF_PR_ARG __entry->band, __entry->control_freq,		\
			__entry->freq_offset, __entry->width,		\
			__entry->center_freq1, __entry->freq1_offset,	\
			__entry->center_freq2

#घोषणा SINFO_ENTRY __field(पूर्णांक, generation)	    \
		    __field(u32, connected_समय)    \
		    __field(u32, inactive_समय)	    \
		    __field(u32, rx_bytes)	    \
		    __field(u32, tx_bytes)	    \
		    __field(u32, rx_packets)	    \
		    __field(u32, tx_packets)	    \
		    __field(u32, tx_retries)	    \
		    __field(u32, tx_failed)	    \
		    __field(u32, rx_dropped_misc)   \
		    __field(u32, beacon_loss_count) \
		    __field(u16, llid)		    \
		    __field(u16, plid)		    \
		    __field(u8, plink_state)
#घोषणा SINFO_ASSIGN						       \
	करो अणु							       \
		__entry->generation = sinfo->generation;	       \
		__entry->connected_समय = sinfo->connected_समय;       \
		__entry->inactive_समय = sinfo->inactive_समय;	       \
		__entry->rx_bytes = sinfo->rx_bytes;		       \
		__entry->tx_bytes = sinfo->tx_bytes;		       \
		__entry->rx_packets = sinfo->rx_packets;	       \
		__entry->tx_packets = sinfo->tx_packets;	       \
		__entry->tx_retries = sinfo->tx_retries;	       \
		__entry->tx_failed = sinfo->tx_failed;		       \
		__entry->rx_dropped_misc = sinfo->rx_dropped_misc;     \
		__entry->beacon_loss_count = sinfo->beacon_loss_count; \
		__entry->llid = sinfo->llid;			       \
		__entry->plid = sinfo->plid;			       \
		__entry->plink_state = sinfo->plink_state;	       \
	पूर्ण जबतक (0)

#घोषणा BOOL_TO_STR(bo) (bo) ? "true" : "false"

#घोषणा QOS_MAP_ENTRY __field(u8, num_des)			\
		      __array(u8, dscp_exception,		\
			      2 * IEEE80211_QOS_MAP_MAX_EX)	\
		      __array(u8, up, IEEE80211_QOS_MAP_LEN_MIN)
#घोषणा QOS_MAP_ASSIGN(qos_map)					\
	करो अणु							\
		अगर ((qos_map)) अणु				\
			__entry->num_des = (qos_map)->num_des;	\
			स_नकल(__entry->dscp_exception,		\
			       &(qos_map)->dscp_exception,	\
			       2 * IEEE80211_QOS_MAP_MAX_EX);	\
			स_नकल(__entry->up, &(qos_map)->up,	\
			       IEEE80211_QOS_MAP_LEN_MIN);	\
		पूर्ण अन्यथा अणु					\
			__entry->num_des = 0;			\
			स_रखो(__entry->dscp_exception, 0,	\
			       2 * IEEE80211_QOS_MAP_MAX_EX);	\
			स_रखो(__entry->up, 0,			\
			       IEEE80211_QOS_MAP_LEN_MIN);	\
		पूर्ण						\
	पूर्ण जबतक (0)

/*************************************************************
 *			rdev->ops traces		     *
 *************************************************************/

TRACE_EVENT(rdev_suspend,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा cfg80211_wowlan *wow),
	TP_ARGS(wiphy, wow),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		__field(bool, any)
		__field(bool, disconnect)
		__field(bool, magic_pkt)
		__field(bool, gtk_rekey_failure)
		__field(bool, eap_identity_req)
		__field(bool, four_way_handshake)
		__field(bool, rfसमाप्त_release)
		__field(bool, valid_wow)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		अगर (wow) अणु
			__entry->any = wow->any;
			__entry->disconnect = wow->disconnect;
			__entry->magic_pkt = wow->magic_pkt;
			__entry->gtk_rekey_failure = wow->gtk_rekey_failure;
			__entry->eap_identity_req = wow->eap_identity_req;
			__entry->four_way_handshake = wow->four_way_handshake;
			__entry->rfसमाप्त_release = wow->rfसमाप्त_release;
			__entry->valid_wow = true;
		पूर्ण अन्यथा अणु
			__entry->valid_wow = false;
		पूर्ण
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", wow%s - any: %d, disconnect: %d, "
		  "magic pkt: %d, gtk rekey failure: %d, eap identify req: %d, "
		  "four way handshake: %d, rfkill release: %d.",
		  WIPHY_PR_ARG, __entry->valid_wow ? "" : "(Not configured!)",
		  __entry->any, __entry->disconnect, __entry->magic_pkt,
		  __entry->gtk_rekey_failure, __entry->eap_identity_req,
		  __entry->four_way_handshake, __entry->rfसमाप्त_release)
);

TRACE_EVENT(rdev_वापस_पूर्णांक,
	TP_PROTO(काष्ठा wiphy *wiphy, पूर्णांक ret),
	TP_ARGS(wiphy, ret),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		__field(पूर्णांक, ret)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		__entry->ret = ret;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", returned: %d", WIPHY_PR_ARG, __entry->ret)
);

TRACE_EVENT(rdev_scan,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा cfg80211_scan_request *request),
	TP_ARGS(wiphy, request),
	TP_STRUCT__entry(
		WIPHY_ENTRY
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT, WIPHY_PR_ARG)
);

DECLARE_EVENT_CLASS(wiphy_only_evt,
	TP_PROTO(काष्ठा wiphy *wiphy),
	TP_ARGS(wiphy),
	TP_STRUCT__entry(
		WIPHY_ENTRY
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT, WIPHY_PR_ARG)
);

DEFINE_EVENT(wiphy_only_evt, rdev_resume,
	TP_PROTO(काष्ठा wiphy *wiphy),
	TP_ARGS(wiphy)
);

DEFINE_EVENT(wiphy_only_evt, rdev_वापस_व्योम,
	TP_PROTO(काष्ठा wiphy *wiphy),
	TP_ARGS(wiphy)
);

DEFINE_EVENT(wiphy_only_evt, rdev_get_antenna,
	TP_PROTO(काष्ठा wiphy *wiphy),
	TP_ARGS(wiphy)
);

DEFINE_EVENT(wiphy_only_evt, rdev_rfसमाप्त_poll,
	TP_PROTO(काष्ठा wiphy *wiphy),
	TP_ARGS(wiphy)
);

DECLARE_EVENT_CLASS(wiphy_enabled_evt,
	TP_PROTO(काष्ठा wiphy *wiphy, bool enabled),
	TP_ARGS(wiphy, enabled),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		__field(bool, enabled)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		__entry->enabled = enabled;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", %senabled ",
		  WIPHY_PR_ARG, __entry->enabled ? "" : "not ")
);

DEFINE_EVENT(wiphy_enabled_evt, rdev_set_wakeup,
	TP_PROTO(काष्ठा wiphy *wiphy, bool enabled),
	TP_ARGS(wiphy, enabled)
);

TRACE_EVENT(rdev_add_भव_पूर्णांकf,
	TP_PROTO(काष्ठा wiphy *wiphy, अक्षर *name, क्रमागत nl80211_अगरtype type),
	TP_ARGS(wiphy, name, type),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		__string(vir_पूर्णांकf_name, name ? name : "<noname>")
		__field(क्रमागत nl80211_अगरtype, type)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		__assign_str(vir_पूर्णांकf_name, name ? name : "<noname>");
		__entry->type = type;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", virtual intf name: %s, type: %d",
		  WIPHY_PR_ARG, __get_str(vir_पूर्णांकf_name), __entry->type)
);

DECLARE_EVENT_CLASS(wiphy_wdev_evt,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev),
	TP_ARGS(wiphy, wdev),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		WDEV_ENTRY
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		WDEV_ASSIGN;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " WDEV_PR_FMT, WIPHY_PR_ARG, WDEV_PR_ARG)
);

DECLARE_EVENT_CLASS(wiphy_wdev_cookie_evt,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev, u64 cookie),
	TP_ARGS(wiphy, wdev, cookie),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		WDEV_ENTRY
		__field(u64, cookie)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		WDEV_ASSIGN;
		__entry->cookie = cookie;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " WDEV_PR_FMT ", cookie: %lld",
		  WIPHY_PR_ARG, WDEV_PR_ARG,
		  (अचिन्हित दीर्घ दीर्घ)__entry->cookie)
);

DEFINE_EVENT(wiphy_wdev_evt, rdev_वापस_wdev,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev),
	TP_ARGS(wiphy, wdev)
);

DEFINE_EVENT(wiphy_wdev_evt, rdev_del_भव_पूर्णांकf,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev),
	TP_ARGS(wiphy, wdev)
);

TRACE_EVENT(rdev_change_भव_पूर्णांकf,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 क्रमागत nl80211_अगरtype type),
	TP_ARGS(wiphy, netdev, type),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		__field(क्रमागत nl80211_अगरtype, type)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		__entry->type = type;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", type: %d",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, __entry->type)
);

DECLARE_EVENT_CLASS(key_handle,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, u8 key_index,
		 bool pairwise, स्थिर u8 *mac_addr),
	TP_ARGS(wiphy, netdev, key_index, pairwise, mac_addr),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(mac_addr)
		__field(u8, key_index)
		__field(bool, pairwise)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(mac_addr, mac_addr);
		__entry->key_index = key_index;
		__entry->pairwise = pairwise;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", key_index: %u, pairwise: %s, mac addr: " MAC_PR_FMT,
		  WIPHY_PR_ARG, NETDEV_PR_ARG, __entry->key_index,
		  BOOL_TO_STR(__entry->pairwise), MAC_PR_ARG(mac_addr))
);

DEFINE_EVENT(key_handle, rdev_get_key,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, u8 key_index,
		 bool pairwise, स्थिर u8 *mac_addr),
	TP_ARGS(wiphy, netdev, key_index, pairwise, mac_addr)
);

DEFINE_EVENT(key_handle, rdev_del_key,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, u8 key_index,
		 bool pairwise, स्थिर u8 *mac_addr),
	TP_ARGS(wiphy, netdev, key_index, pairwise, mac_addr)
);

TRACE_EVENT(rdev_add_key,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, u8 key_index,
		 bool pairwise, स्थिर u8 *mac_addr, u8 mode),
	TP_ARGS(wiphy, netdev, key_index, pairwise, mac_addr, mode),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(mac_addr)
		__field(u8, key_index)
		__field(bool, pairwise)
		__field(u8, mode)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(mac_addr, mac_addr);
		__entry->key_index = key_index;
		__entry->pairwise = pairwise;
		__entry->mode = mode;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", key_index: %u, "
		  "mode: %u, pairwise: %s, mac addr: " MAC_PR_FMT,
		  WIPHY_PR_ARG, NETDEV_PR_ARG, __entry->key_index,
		  __entry->mode, BOOL_TO_STR(__entry->pairwise),
		  MAC_PR_ARG(mac_addr))
);

TRACE_EVENT(rdev_set_शेष_key,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, u8 key_index,
		 bool unicast, bool multicast),
	TP_ARGS(wiphy, netdev, key_index, unicast, multicast),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		__field(u8, key_index)
		__field(bool, unicast)
		__field(bool, multicast)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		__entry->key_index = key_index;
		__entry->unicast = unicast;
		__entry->multicast = multicast;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", key index: %u, unicast: %s, multicast: %s",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, __entry->key_index,
		  BOOL_TO_STR(__entry->unicast),
		  BOOL_TO_STR(__entry->multicast))
);

TRACE_EVENT(rdev_set_शेष_mgmt_key,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, u8 key_index),
	TP_ARGS(wiphy, netdev, key_index),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		__field(u8, key_index)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		__entry->key_index = key_index;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", key index: %u",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, __entry->key_index)
);

TRACE_EVENT(rdev_set_शेष_beacon_key,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, u8 key_index),
	TP_ARGS(wiphy, netdev, key_index),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		__field(u8, key_index)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		__entry->key_index = key_index;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", key index: %u",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, __entry->key_index)
);

TRACE_EVENT(rdev_start_ap,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा cfg80211_ap_settings *settings),
	TP_ARGS(wiphy, netdev, settings),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		CHAN_DEF_ENTRY
		__field(पूर्णांक, beacon_पूर्णांकerval)
		__field(पूर्णांक, dtim_period)
		__array(अक्षर, ssid, IEEE80211_MAX_SSID_LEN + 1)
		__field(क्रमागत nl80211_hidden_ssid, hidden_ssid)
		__field(u32, wpa_ver)
		__field(bool, privacy)
		__field(क्रमागत nl80211_auth_type, auth_type)
		__field(पूर्णांक, inactivity_समयout)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		CHAN_DEF_ASSIGN(&settings->chandef);
		__entry->beacon_पूर्णांकerval = settings->beacon_पूर्णांकerval;
		__entry->dtim_period = settings->dtim_period;
		__entry->hidden_ssid = settings->hidden_ssid;
		__entry->wpa_ver = settings->crypto.wpa_versions;
		__entry->privacy = settings->privacy;
		__entry->auth_type = settings->auth_type;
		__entry->inactivity_समयout = settings->inactivity_समयout;
		स_रखो(__entry->ssid, 0, IEEE80211_MAX_SSID_LEN + 1);
		स_नकल(__entry->ssid, settings->ssid, settings->ssid_len);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", AP settings - ssid: %s, "
		  CHAN_DEF_PR_FMT ", beacon interval: %d, dtim period: %d, "
		  "hidden ssid: %d, wpa versions: %u, privacy: %s, "
		  "auth type: %d, inactivity timeout: %d",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, __entry->ssid, CHAN_DEF_PR_ARG,
		  __entry->beacon_पूर्णांकerval, __entry->dtim_period,
		  __entry->hidden_ssid, __entry->wpa_ver,
		  BOOL_TO_STR(__entry->privacy), __entry->auth_type,
		  __entry->inactivity_समयout)
);

TRACE_EVENT(rdev_change_beacon,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा cfg80211_beacon_data *info),
	TP_ARGS(wiphy, netdev, info),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		__dynamic_array(u8, head, info ? info->head_len : 0)
		__dynamic_array(u8, tail, info ? info->tail_len : 0)
		__dynamic_array(u8, beacon_ies, info ? info->beacon_ies_len : 0)
		__dynamic_array(u8, proberesp_ies,
				info ? info->proberesp_ies_len : 0)
		__dynamic_array(u8, assocresp_ies,
				info ? info->assocresp_ies_len : 0)
		__dynamic_array(u8, probe_resp, info ? info->probe_resp_len : 0)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		अगर (info) अणु
			अगर (info->head)
				स_नकल(__get_dynamic_array(head), info->head,
				       info->head_len);
			अगर (info->tail)
				स_नकल(__get_dynamic_array(tail), info->tail,
				       info->tail_len);
			अगर (info->beacon_ies)
				स_नकल(__get_dynamic_array(beacon_ies),
				       info->beacon_ies, info->beacon_ies_len);
			अगर (info->proberesp_ies)
				स_नकल(__get_dynamic_array(proberesp_ies),
				       info->proberesp_ies,
				       info->proberesp_ies_len);
			अगर (info->assocresp_ies)
				स_नकल(__get_dynamic_array(assocresp_ies),
				       info->assocresp_ies,
				       info->assocresp_ies_len);
			अगर (info->probe_resp)
				स_नकल(__get_dynamic_array(probe_resp),
				       info->probe_resp, info->probe_resp_len);
		पूर्ण
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT, WIPHY_PR_ARG, NETDEV_PR_ARG)
);

DECLARE_EVENT_CLASS(wiphy_netdev_evt,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev),
	TP_ARGS(wiphy, netdev),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT, WIPHY_PR_ARG, NETDEV_PR_ARG)
);

DEFINE_EVENT(wiphy_netdev_evt, rdev_stop_ap,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev),
	TP_ARGS(wiphy, netdev)
);

DEFINE_EVENT(wiphy_netdev_evt, rdev_set_rekey_data,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev),
	TP_ARGS(wiphy, netdev)
);

DEFINE_EVENT(wiphy_netdev_evt, rdev_get_mesh_config,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev),
	TP_ARGS(wiphy, netdev)
);

DEFINE_EVENT(wiphy_netdev_evt, rdev_leave_mesh,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev),
	TP_ARGS(wiphy, netdev)
);

DEFINE_EVENT(wiphy_netdev_evt, rdev_leave_ibss,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev),
	TP_ARGS(wiphy, netdev)
);

DEFINE_EVENT(wiphy_netdev_evt, rdev_leave_ocb,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev),
	TP_ARGS(wiphy, netdev)
);

DEFINE_EVENT(wiphy_netdev_evt, rdev_flush_pmksa,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev),
	TP_ARGS(wiphy, netdev)
);

DEFINE_EVENT(wiphy_netdev_evt, rdev_end_cac,
	     TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev),
	     TP_ARGS(wiphy, netdev)
);

DECLARE_EVENT_CLASS(station_add_change,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, u8 *mac,
		 काष्ठा station_parameters *params),
	TP_ARGS(wiphy, netdev, mac, params),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(sta_mac)
		__field(u32, sta_flags_mask)
		__field(u32, sta_flags_set)
		__field(u32, sta_modअगरy_mask)
		__field(पूर्णांक, listen_पूर्णांकerval)
		__field(u16, capability)
		__field(u16, aid)
		__field(u8, plink_action)
		__field(u8, plink_state)
		__field(u8, uapsd_queues)
		__field(u8, max_sp)
		__field(u8, opmode_notअगर)
		__field(bool, opmode_notअगर_used)
		__array(u8, ht_capa, (पूर्णांक)माप(काष्ठा ieee80211_ht_cap))
		__array(u8, vht_capa, (पूर्णांक)माप(काष्ठा ieee80211_vht_cap))
		__array(अक्षर, vlan, IFNAMSIZ)
		__dynamic_array(u8, supported_rates,
				params->supported_rates_len)
		__dynamic_array(u8, ext_capab, params->ext_capab_len)
		__dynamic_array(u8, supported_channels,
				params->supported_channels_len)
		__dynamic_array(u8, supported_oper_classes,
				params->supported_oper_classes_len)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(sta_mac, mac);
		__entry->sta_flags_mask = params->sta_flags_mask;
		__entry->sta_flags_set = params->sta_flags_set;
		__entry->sta_modअगरy_mask = params->sta_modअगरy_mask;
		__entry->listen_पूर्णांकerval = params->listen_पूर्णांकerval;
		__entry->aid = params->aid;
		__entry->plink_action = params->plink_action;
		__entry->plink_state = params->plink_state;
		__entry->uapsd_queues = params->uapsd_queues;
		स_रखो(__entry->ht_capa, 0, माप(काष्ठा ieee80211_ht_cap));
		अगर (params->ht_capa)
			स_नकल(__entry->ht_capa, params->ht_capa,
			       माप(काष्ठा ieee80211_ht_cap));
		स_रखो(__entry->vht_capa, 0, माप(काष्ठा ieee80211_vht_cap));
		अगर (params->vht_capa)
			स_नकल(__entry->vht_capa, params->vht_capa,
			       माप(काष्ठा ieee80211_vht_cap));
		स_रखो(__entry->vlan, 0, माप(__entry->vlan));
		अगर (params->vlan)
			स_नकल(__entry->vlan, params->vlan->name, IFNAMSIZ);
		अगर (params->supported_rates && params->supported_rates_len)
			स_नकल(__get_dynamic_array(supported_rates),
			       params->supported_rates,
			       params->supported_rates_len);
		अगर (params->ext_capab && params->ext_capab_len)
			स_नकल(__get_dynamic_array(ext_capab),
			       params->ext_capab,
			       params->ext_capab_len);
		अगर (params->supported_channels &&
		    params->supported_channels_len)
			स_नकल(__get_dynamic_array(supported_channels),
			       params->supported_channels,
			       params->supported_channels_len);
		अगर (params->supported_oper_classes &&
		    params->supported_oper_classes_len)
			स_नकल(__get_dynamic_array(supported_oper_classes),
			       params->supported_oper_classes,
			       params->supported_oper_classes_len);
		__entry->max_sp = params->max_sp;
		__entry->capability = params->capability;
		__entry->opmode_notअगर = params->opmode_notअगर;
		__entry->opmode_notअगर_used = params->opmode_notअगर_used;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", station mac: " MAC_PR_FMT
		  ", station flags mask: %u, station flags set: %u, "
		  "station modify mask: %u, listen interval: %d, aid: %u, "
		  "plink action: %u, plink state: %u, uapsd queues: %u, vlan:%s",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(sta_mac),
		  __entry->sta_flags_mask, __entry->sta_flags_set,
		  __entry->sta_modअगरy_mask, __entry->listen_पूर्णांकerval,
		  __entry->aid, __entry->plink_action, __entry->plink_state,
		  __entry->uapsd_queues, __entry->vlan)
);

DEFINE_EVENT(station_add_change, rdev_add_station,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, u8 *mac,
		 काष्ठा station_parameters *params),
	TP_ARGS(wiphy, netdev, mac, params)
);

DEFINE_EVENT(station_add_change, rdev_change_station,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, u8 *mac,
		 काष्ठा station_parameters *params),
	TP_ARGS(wiphy, netdev, mac, params)
);

DECLARE_EVENT_CLASS(wiphy_netdev_mac_evt,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, स्थिर u8 *mac),
	TP_ARGS(wiphy, netdev, mac),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(sta_mac)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(sta_mac, mac);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", mac: " MAC_PR_FMT,
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(sta_mac))
);

DECLARE_EVENT_CLASS(station_del,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा station_del_parameters *params),
	TP_ARGS(wiphy, netdev, params),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(sta_mac)
		__field(u8, subtype)
		__field(u16, reason_code)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(sta_mac, params->mac);
		__entry->subtype = params->subtype;
		__entry->reason_code = params->reason_code;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", station mac: " MAC_PR_FMT
		  ", subtype: %u, reason_code: %u",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(sta_mac),
		  __entry->subtype, __entry->reason_code)
);

DEFINE_EVENT(station_del, rdev_del_station,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा station_del_parameters *params),
	TP_ARGS(wiphy, netdev, params)
);

DEFINE_EVENT(wiphy_netdev_mac_evt, rdev_get_station,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, स्थिर u8 *mac),
	TP_ARGS(wiphy, netdev, mac)
);

DEFINE_EVENT(wiphy_netdev_mac_evt, rdev_del_mpath,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, स्थिर u8 *mac),
	TP_ARGS(wiphy, netdev, mac)
);

TRACE_EVENT(rdev_dump_station,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, पूर्णांक _idx,
		 u8 *mac),
	TP_ARGS(wiphy, netdev, _idx, mac),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(sta_mac)
		__field(पूर्णांक, idx)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(sta_mac, mac);
		__entry->idx = _idx;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", station mac: " MAC_PR_FMT ", idx: %d",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(sta_mac),
		  __entry->idx)
);

TRACE_EVENT(rdev_वापस_पूर्णांक_station_info,
	TP_PROTO(काष्ठा wiphy *wiphy, पूर्णांक ret, काष्ठा station_info *sinfo),
	TP_ARGS(wiphy, ret, sinfo),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		__field(पूर्णांक, ret)
		SINFO_ENTRY
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		__entry->ret = ret;
		SINFO_ASSIGN;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", returned %d" ,
		  WIPHY_PR_ARG, __entry->ret)
);

DECLARE_EVENT_CLASS(mpath_evt,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, u8 *dst,
		 u8 *next_hop),
	TP_ARGS(wiphy, netdev, dst, next_hop),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(dst)
		MAC_ENTRY(next_hop)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(dst, dst);
		MAC_ASSIGN(next_hop, next_hop);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", destination: " MAC_PR_FMT ", next hop: " MAC_PR_FMT,
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(dst),
		  MAC_PR_ARG(next_hop))
);

DEFINE_EVENT(mpath_evt, rdev_add_mpath,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, u8 *dst,
		 u8 *next_hop),
	TP_ARGS(wiphy, netdev, dst, next_hop)
);

DEFINE_EVENT(mpath_evt, rdev_change_mpath,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, u8 *dst,
		 u8 *next_hop),
	TP_ARGS(wiphy, netdev, dst, next_hop)
);

DEFINE_EVENT(mpath_evt, rdev_get_mpath,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, u8 *dst,
		 u8 *next_hop),
	TP_ARGS(wiphy, netdev, dst, next_hop)
);

TRACE_EVENT(rdev_dump_mpath,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, पूर्णांक _idx,
		 u8 *dst, u8 *next_hop),
	TP_ARGS(wiphy, netdev, _idx, dst, next_hop),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(dst)
		MAC_ENTRY(next_hop)
		__field(पूर्णांक, idx)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(dst, dst);
		MAC_ASSIGN(next_hop, next_hop);
		__entry->idx = _idx;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", index: %d, destination: "
		  MAC_PR_FMT ", next hop: " MAC_PR_FMT,
		  WIPHY_PR_ARG, NETDEV_PR_ARG, __entry->idx, MAC_PR_ARG(dst),
		  MAC_PR_ARG(next_hop))
);

TRACE_EVENT(rdev_get_mpp,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 u8 *dst, u8 *mpp),
	TP_ARGS(wiphy, netdev, dst, mpp),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(dst)
		MAC_ENTRY(mpp)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(dst, dst);
		MAC_ASSIGN(mpp, mpp);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", destination: " MAC_PR_FMT
		  ", mpp: " MAC_PR_FMT, WIPHY_PR_ARG, NETDEV_PR_ARG,
		  MAC_PR_ARG(dst), MAC_PR_ARG(mpp))
);

TRACE_EVENT(rdev_dump_mpp,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, पूर्णांक _idx,
		 u8 *dst, u8 *mpp),
	TP_ARGS(wiphy, netdev, _idx, mpp, dst),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(dst)
		MAC_ENTRY(mpp)
		__field(पूर्णांक, idx)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(dst, dst);
		MAC_ASSIGN(mpp, mpp);
		__entry->idx = _idx;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", index: %d, destination: "
		  MAC_PR_FMT ", mpp: " MAC_PR_FMT,
		  WIPHY_PR_ARG, NETDEV_PR_ARG, __entry->idx, MAC_PR_ARG(dst),
		  MAC_PR_ARG(mpp))
);

TRACE_EVENT(rdev_वापस_पूर्णांक_mpath_info,
	TP_PROTO(काष्ठा wiphy *wiphy, पूर्णांक ret, काष्ठा mpath_info *pinfo),
	TP_ARGS(wiphy, ret, pinfo),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		__field(पूर्णांक, ret)
		__field(पूर्णांक, generation)
		__field(u32, filled)
		__field(u32, frame_qlen)
		__field(u32, sn)
		__field(u32, metric)
		__field(u32, expसमय)
		__field(u32, discovery_समयout)
		__field(u8, discovery_retries)
		__field(u8, flags)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		__entry->ret = ret;
		__entry->generation = pinfo->generation;
		__entry->filled = pinfo->filled;
		__entry->frame_qlen = pinfo->frame_qlen;
		__entry->sn = pinfo->sn;
		__entry->metric = pinfo->metric;
		__entry->expसमय = pinfo->expसमय;
		__entry->discovery_समयout = pinfo->discovery_समयout;
		__entry->discovery_retries = pinfo->discovery_retries;
		__entry->flags = pinfo->flags;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", returned %d. mpath info - generation: %d, "
		  "filled: %u, frame qlen: %u, sn: %u, metric: %u, exptime: %u,"
		  " discovery timeout: %u, discovery retries: %u, flags: %u",
		  WIPHY_PR_ARG, __entry->ret, __entry->generation,
		  __entry->filled, __entry->frame_qlen, __entry->sn,
		  __entry->metric, __entry->expसमय, __entry->discovery_समयout,
		  __entry->discovery_retries, __entry->flags)
);

TRACE_EVENT(rdev_वापस_पूर्णांक_mesh_config,
	TP_PROTO(काष्ठा wiphy *wiphy, पूर्णांक ret, काष्ठा mesh_config *conf),
	TP_ARGS(wiphy, ret, conf),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		MESH_CFG_ENTRY
		__field(पूर्णांक, ret)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		MESH_CFG_ASSIGN;
		__entry->ret = ret;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", returned: %d",
		  WIPHY_PR_ARG, __entry->ret)
);

TRACE_EVENT(rdev_update_mesh_config,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, u32 mask,
		 स्थिर काष्ठा mesh_config *conf),
	TP_ARGS(wiphy, netdev, mask, conf),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MESH_CFG_ENTRY
		__field(u32, mask)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MESH_CFG_ASSIGN;
		__entry->mask = mask;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", mask: %u",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, __entry->mask)
);

TRACE_EVENT(rdev_join_mesh,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 स्थिर काष्ठा mesh_config *conf,
		 स्थिर काष्ठा mesh_setup *setup),
	TP_ARGS(wiphy, netdev, conf, setup),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MESH_CFG_ENTRY
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MESH_CFG_ASSIGN;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT,
		  WIPHY_PR_ARG, NETDEV_PR_ARG)
);

TRACE_EVENT(rdev_change_bss,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा bss_parameters *params),
	TP_ARGS(wiphy, netdev, params),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		__field(पूर्णांक, use_cts_prot)
		__field(पूर्णांक, use_लघु_preamble)
		__field(पूर्णांक, use_लघु_slot_समय)
		__field(पूर्णांक, ap_isolate)
		__field(पूर्णांक, ht_opmode)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		__entry->use_cts_prot = params->use_cts_prot;
		__entry->use_लघु_preamble = params->use_लघु_preamble;
		__entry->use_लघु_slot_समय = params->use_लघु_slot_समय;
		__entry->ap_isolate = params->ap_isolate;
		__entry->ht_opmode = params->ht_opmode;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", use cts prot: %d, "
		  "use short preamble: %d, use short slot time: %d, "
		  "ap isolate: %d, ht opmode: %d",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, __entry->use_cts_prot,
		  __entry->use_लघु_preamble, __entry->use_लघु_slot_समय,
		  __entry->ap_isolate, __entry->ht_opmode)
);

TRACE_EVENT(rdev_set_txq_params,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा ieee80211_txq_params *params),
	TP_ARGS(wiphy, netdev, params),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		__field(क्रमागत nl80211_ac, ac)
		__field(u16, txop)
		__field(u16, cwmin)
		__field(u16, cwmax)
		__field(u8, aअगरs)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		__entry->ac = params->ac;
		__entry->txop = params->txop;
		__entry->cwmin = params->cwmin;
		__entry->cwmax = params->cwmax;
		__entry->aअगरs = params->aअगरs;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", ac: %d, txop: %u, cwmin: %u, cwmax: %u, aifs: %u",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, __entry->ac, __entry->txop,
		  __entry->cwmin, __entry->cwmax, __entry->aअगरs)
);

TRACE_EVENT(rdev_libertas_set_mesh_channel,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा ieee80211_channel *chan),
	TP_ARGS(wiphy, netdev, chan),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		CHAN_ENTRY
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		CHAN_ASSIGN(chan);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", " CHAN_PR_FMT, WIPHY_PR_ARG,
		  NETDEV_PR_ARG, CHAN_PR_ARG)
);

TRACE_EVENT(rdev_set_monitor_channel,
	TP_PROTO(काष्ठा wiphy *wiphy,
		 काष्ठा cfg80211_chan_def *chandef),
	TP_ARGS(wiphy, chandef),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		CHAN_DEF_ENTRY
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		CHAN_DEF_ASSIGN(chandef);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " CHAN_DEF_PR_FMT,
		  WIPHY_PR_ARG, CHAN_DEF_PR_ARG)
);

TRACE_EVENT(rdev_auth,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा cfg80211_auth_request *req),
	TP_ARGS(wiphy, netdev, req),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(bssid)
		__field(क्रमागत nl80211_auth_type, auth_type)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		अगर (req->bss)
			MAC_ASSIGN(bssid, req->bss->bssid);
		अन्यथा
			eth_zero_addr(__entry->bssid);
		__entry->auth_type = req->auth_type;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", auth type: %d, bssid: " MAC_PR_FMT,
		  WIPHY_PR_ARG, NETDEV_PR_ARG, __entry->auth_type,
		  MAC_PR_ARG(bssid))
);

TRACE_EVENT(rdev_assoc,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा cfg80211_assoc_request *req),
	TP_ARGS(wiphy, netdev, req),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(bssid)
		MAC_ENTRY(prev_bssid)
		__field(bool, use_mfp)
		__field(u32, flags)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		अगर (req->bss)
			MAC_ASSIGN(bssid, req->bss->bssid);
		अन्यथा
			eth_zero_addr(__entry->bssid);
		MAC_ASSIGN(prev_bssid, req->prev_bssid);
		__entry->use_mfp = req->use_mfp;
		__entry->flags = req->flags;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", bssid: " MAC_PR_FMT
		  ", previous bssid: " MAC_PR_FMT ", use mfp: %s, flags: %u",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(bssid),
		  MAC_PR_ARG(prev_bssid), BOOL_TO_STR(__entry->use_mfp),
		  __entry->flags)
);

TRACE_EVENT(rdev_deauth,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा cfg80211_deauth_request *req),
	TP_ARGS(wiphy, netdev, req),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(bssid)
		__field(u16, reason_code)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(bssid, req->bssid);
		__entry->reason_code = req->reason_code;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", bssid: " MAC_PR_FMT ", reason: %u",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(bssid),
		  __entry->reason_code)
);

TRACE_EVENT(rdev_disassoc,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा cfg80211_disassoc_request *req),
	TP_ARGS(wiphy, netdev, req),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(bssid)
		__field(u16, reason_code)
		__field(bool, local_state_change)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		अगर (req->bss)
			MAC_ASSIGN(bssid, req->bss->bssid);
		अन्यथा
			eth_zero_addr(__entry->bssid);
		__entry->reason_code = req->reason_code;
		__entry->local_state_change = req->local_state_change;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", bssid: " MAC_PR_FMT
		  ", reason: %u, local state change: %s",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(bssid),
		  __entry->reason_code,
		  BOOL_TO_STR(__entry->local_state_change))
);

TRACE_EVENT(rdev_mgmt_tx_cancel_रुको,
	TP_PROTO(काष्ठा wiphy *wiphy,
		 काष्ठा wireless_dev *wdev, u64 cookie),
	TP_ARGS(wiphy, wdev, cookie),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		WDEV_ENTRY
		__field(u64, cookie)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		WDEV_ASSIGN;
		__entry->cookie = cookie;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " WDEV_PR_FMT ", cookie: %llu ",
		  WIPHY_PR_ARG, WDEV_PR_ARG, __entry->cookie)
);

TRACE_EVENT(rdev_set_घातer_mgmt,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 bool enabled, पूर्णांक समयout),
	TP_ARGS(wiphy, netdev, enabled, समयout),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		__field(bool, enabled)
		__field(पूर्णांक, समयout)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		__entry->enabled = enabled;
		__entry->समयout = समयout;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", %senabled, timeout: %d ",
		  WIPHY_PR_ARG, NETDEV_PR_ARG,
		  __entry->enabled ? "" : "not ", __entry->समयout)
);

TRACE_EVENT(rdev_connect,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा cfg80211_connect_params *sme),
	TP_ARGS(wiphy, netdev, sme),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(bssid)
		__array(अक्षर, ssid, IEEE80211_MAX_SSID_LEN + 1)
		__field(क्रमागत nl80211_auth_type, auth_type)
		__field(bool, privacy)
		__field(u32, wpa_versions)
		__field(u32, flags)
		MAC_ENTRY(prev_bssid)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(bssid, sme->bssid);
		स_रखो(__entry->ssid, 0, IEEE80211_MAX_SSID_LEN + 1);
		स_नकल(__entry->ssid, sme->ssid, sme->ssid_len);
		__entry->auth_type = sme->auth_type;
		__entry->privacy = sme->privacy;
		__entry->wpa_versions = sme->crypto.wpa_versions;
		__entry->flags = sme->flags;
		MAC_ASSIGN(prev_bssid, sme->prev_bssid);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", bssid: " MAC_PR_FMT
		  ", ssid: %s, auth type: %d, privacy: %s, wpa versions: %u, "
		  "flags: %u, previous bssid: " MAC_PR_FMT,
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(bssid), __entry->ssid,
		  __entry->auth_type, BOOL_TO_STR(__entry->privacy),
		  __entry->wpa_versions, __entry->flags, MAC_PR_ARG(prev_bssid))
);

TRACE_EVENT(rdev_update_connect_params,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा cfg80211_connect_params *sme, u32 changed),
	TP_ARGS(wiphy, netdev, sme, changed),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		__field(u32, changed)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		__entry->changed = changed;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", parameters changed: %u",
		  WIPHY_PR_ARG, NETDEV_PR_ARG,  __entry->changed)
);

TRACE_EVENT(rdev_set_cqm_rssi_config,
	TP_PROTO(काष्ठा wiphy *wiphy,
		 काष्ठा net_device *netdev, s32 rssi_thold,
		 u32 rssi_hyst),
	TP_ARGS(wiphy, netdev, rssi_thold, rssi_hyst),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		__field(s32, rssi_thold)
		__field(u32, rssi_hyst)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		__entry->rssi_thold = rssi_thold;
		__entry->rssi_hyst = rssi_hyst;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT
		  ", rssi_thold: %d, rssi_hyst: %u ",
		  WIPHY_PR_ARG, NETDEV_PR_ARG,
		 __entry->rssi_thold, __entry->rssi_hyst)
);

TRACE_EVENT(rdev_set_cqm_rssi_range_config,
	TP_PROTO(काष्ठा wiphy *wiphy,
		 काष्ठा net_device *netdev, s32 low, s32 high),
	TP_ARGS(wiphy, netdev, low, high),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		__field(s32, rssi_low)
		__field(s32, rssi_high)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		__entry->rssi_low = low;
		__entry->rssi_high = high;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT
		  ", range: %d - %d ",
		  WIPHY_PR_ARG, NETDEV_PR_ARG,
		  __entry->rssi_low, __entry->rssi_high)
);

TRACE_EVENT(rdev_set_cqm_txe_config,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, u32 rate,
		 u32 pkts, u32 पूर्णांकvl),
	TP_ARGS(wiphy, netdev, rate, pkts, पूर्णांकvl),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		__field(u32, rate)
		__field(u32, pkts)
		__field(u32, पूर्णांकvl)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		__entry->rate = rate;
		__entry->pkts = pkts;
		__entry->पूर्णांकvl = पूर्णांकvl;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", rate: %u, packets: %u, interval: %u",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, __entry->rate, __entry->pkts,
		  __entry->पूर्णांकvl)
);

TRACE_EVENT(rdev_disconnect,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 u16 reason_code),
	TP_ARGS(wiphy, netdev, reason_code),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		__field(u16, reason_code)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		__entry->reason_code = reason_code;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", reason code: %u", WIPHY_PR_ARG,
		  NETDEV_PR_ARG, __entry->reason_code)
);

TRACE_EVENT(rdev_join_ibss,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा cfg80211_ibss_params *params),
	TP_ARGS(wiphy, netdev, params),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(bssid)
		__array(अक्षर, ssid, IEEE80211_MAX_SSID_LEN + 1)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(bssid, params->bssid);
		स_रखो(__entry->ssid, 0, IEEE80211_MAX_SSID_LEN + 1);
		स_नकल(__entry->ssid, params->ssid, params->ssid_len);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", bssid: " MAC_PR_FMT ", ssid: %s",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(bssid), __entry->ssid)
);

TRACE_EVENT(rdev_join_ocb,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 स्थिर काष्ठा ocb_setup *setup),
	TP_ARGS(wiphy, netdev, setup),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT,
		  WIPHY_PR_ARG, NETDEV_PR_ARG)
);

TRACE_EVENT(rdev_set_wiphy_params,
	TP_PROTO(काष्ठा wiphy *wiphy, u32 changed),
	TP_ARGS(wiphy, changed),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		__field(u32, changed)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		__entry->changed = changed;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", changed: %u",
		  WIPHY_PR_ARG, __entry->changed)
);

DEFINE_EVENT(wiphy_wdev_evt, rdev_get_tx_घातer,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev),
	TP_ARGS(wiphy, wdev)
);

TRACE_EVENT(rdev_set_tx_घातer,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
		 क्रमागत nl80211_tx_घातer_setting type, पूर्णांक mbm),
	TP_ARGS(wiphy, wdev, type, mbm),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		WDEV_ENTRY
		__field(क्रमागत nl80211_tx_घातer_setting, type)
		__field(पूर्णांक, mbm)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		WDEV_ASSIGN;
		__entry->type = type;
		__entry->mbm = mbm;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " WDEV_PR_FMT ", type: %u, mbm: %d",
		  WIPHY_PR_ARG, WDEV_PR_ARG,__entry->type, __entry->mbm)
);

TRACE_EVENT(rdev_वापस_पूर्णांक_पूर्णांक,
	TP_PROTO(काष्ठा wiphy *wiphy, पूर्णांक func_ret, पूर्णांक func_fill),
	TP_ARGS(wiphy, func_ret, func_fill),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		__field(पूर्णांक, func_ret)
		__field(पूर्णांक, func_fill)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		__entry->func_ret = func_ret;
		__entry->func_fill = func_fill;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", function returns: %d, function filled: %d",
		  WIPHY_PR_ARG, __entry->func_ret, __entry->func_fill)
);

#अगर_घोषित CONFIG_NL80211_TESTMODE
TRACE_EVENT(rdev_tesपंचांगode_cmd,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev),
	TP_ARGS(wiphy, wdev),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		WDEV_ENTRY
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		WDEV_ASSIGN;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT WDEV_PR_FMT, WIPHY_PR_ARG, WDEV_PR_ARG)
);

TRACE_EVENT(rdev_tesपंचांगode_dump,
	TP_PROTO(काष्ठा wiphy *wiphy),
	TP_ARGS(wiphy),
	TP_STRUCT__entry(
		WIPHY_ENTRY
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT, WIPHY_PR_ARG)
);
#पूर्ण_अगर /* CONFIG_NL80211_TESTMODE */

TRACE_EVENT(rdev_set_bitrate_mask,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 स्थिर u8 *peer, स्थिर काष्ठा cfg80211_bitrate_mask *mask),
	TP_ARGS(wiphy, netdev, peer, mask),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(peer)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(peer, peer);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", peer: " MAC_PR_FMT,
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(peer))
);

TRACE_EVENT(rdev_update_mgmt_frame_registrations,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
		 काष्ठा mgmt_frame_regs *upd),
	TP_ARGS(wiphy, wdev, upd),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		WDEV_ENTRY
		__field(u16, global_stypes)
		__field(u16, पूर्णांकerface_stypes)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		WDEV_ASSIGN;
		__entry->global_stypes = upd->global_stypes;
		__entry->पूर्णांकerface_stypes = upd->पूर्णांकerface_stypes;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " WDEV_PR_FMT ", global: 0x%.2x, intf: 0x%.2x",
		  WIPHY_PR_ARG, WDEV_PR_ARG,
		  __entry->global_stypes, __entry->पूर्णांकerface_stypes)
);

TRACE_EVENT(rdev_वापस_पूर्णांक_tx_rx,
	TP_PROTO(काष्ठा wiphy *wiphy, पूर्णांक ret, u32 tx, u32 rx),
	TP_ARGS(wiphy, ret, tx, rx),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		__field(पूर्णांक, ret)
		__field(u32, tx)
		__field(u32, rx)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		__entry->ret = ret;
		__entry->tx = tx;
		__entry->rx = rx;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", returned %d, tx: %u, rx: %u",
		  WIPHY_PR_ARG, __entry->ret, __entry->tx, __entry->rx)
);

TRACE_EVENT(rdev_वापस_व्योम_tx_rx,
	TP_PROTO(काष्ठा wiphy *wiphy, u32 tx, u32 tx_max,
		 u32 rx, u32 rx_max),
	TP_ARGS(wiphy, tx, tx_max, rx, rx_max),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		__field(u32, tx)
		__field(u32, tx_max)
		__field(u32, rx)
		__field(u32, rx_max)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		__entry->tx = tx;
		__entry->tx_max = tx_max;
		__entry->rx = rx;
		__entry->rx_max = rx_max;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", tx: %u, tx_max: %u, rx: %u, rx_max: %u ",
		  WIPHY_PR_ARG, __entry->tx, __entry->tx_max, __entry->rx,
		  __entry->rx_max)
);

DECLARE_EVENT_CLASS(tx_rx_evt,
	TP_PROTO(काष्ठा wiphy *wiphy, u32 tx, u32 rx),
	TP_ARGS(wiphy, rx, tx),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		__field(u32, tx)
		__field(u32, rx)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		__entry->tx = tx;
		__entry->rx = rx;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", tx: %u, rx: %u ",
		  WIPHY_PR_ARG, __entry->tx, __entry->rx)
);

DEFINE_EVENT(tx_rx_evt, rdev_set_antenna,
	TP_PROTO(काष्ठा wiphy *wiphy, u32 tx, u32 rx),
	TP_ARGS(wiphy, rx, tx)
);

DECLARE_EVENT_CLASS(wiphy_netdev_id_evt,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, u64 id),
	TP_ARGS(wiphy, netdev, id),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		__field(u64, id)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		__entry->id = id;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", id: %llu",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, __entry->id)
);

DEFINE_EVENT(wiphy_netdev_id_evt, rdev_sched_scan_start,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, u64 id),
	TP_ARGS(wiphy, netdev, id)
);

DEFINE_EVENT(wiphy_netdev_id_evt, rdev_sched_scan_stop,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, u64 id),
	TP_ARGS(wiphy, netdev, id)
);

TRACE_EVENT(rdev_tdls_mgmt,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 u8 *peer, u8 action_code, u8 dialog_token,
		 u16 status_code, u32 peer_capability,
		 bool initiator, स्थिर u8 *buf, माप_प्रकार len),
	TP_ARGS(wiphy, netdev, peer, action_code, dialog_token, status_code,
		peer_capability, initiator, buf, len),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(peer)
		__field(u8, action_code)
		__field(u8, dialog_token)
		__field(u16, status_code)
		__field(u32, peer_capability)
		__field(bool, initiator)
		__dynamic_array(u8, buf, len)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(peer, peer);
		__entry->action_code = action_code;
		__entry->dialog_token = dialog_token;
		__entry->status_code = status_code;
		__entry->peer_capability = peer_capability;
		__entry->initiator = initiator;
		स_नकल(__get_dynamic_array(buf), buf, len);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", " MAC_PR_FMT ", action_code: %u, "
		  "dialog_token: %u, status_code: %u, peer_capability: %u "
		  "initiator: %s buf: %#.2x ",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(peer),
		  __entry->action_code, __entry->dialog_token,
		  __entry->status_code, __entry->peer_capability,
		  BOOL_TO_STR(__entry->initiator),
		  ((u8 *)__get_dynamic_array(buf))[0])
);

TRACE_EVENT(rdev_dump_survey,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, पूर्णांक _idx),
	TP_ARGS(wiphy, netdev, _idx),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		__field(पूर्णांक, idx)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		__entry->idx = _idx;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", index: %d",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, __entry->idx)
);

TRACE_EVENT(rdev_वापस_पूर्णांक_survey_info,
	TP_PROTO(काष्ठा wiphy *wiphy, पूर्णांक ret, काष्ठा survey_info *info),
	TP_ARGS(wiphy, ret, info),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		CHAN_ENTRY
		__field(पूर्णांक, ret)
		__field(u64, समय)
		__field(u64, समय_busy)
		__field(u64, समय_ext_busy)
		__field(u64, समय_rx)
		__field(u64, समय_प्रकारx)
		__field(u64, समय_scan)
		__field(u32, filled)
		__field(s8, noise)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		CHAN_ASSIGN(info->channel);
		__entry->ret = ret;
		__entry->समय = info->समय;
		__entry->समय_busy = info->समय_busy;
		__entry->समय_ext_busy = info->समय_ext_busy;
		__entry->समय_rx = info->समय_rx;
		__entry->समय_प्रकारx = info->समय_प्रकारx;
		__entry->समय_scan = info->समय_scan;
		__entry->filled = info->filled;
		__entry->noise = info->noise;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", returned: %d, " CHAN_PR_FMT
		  ", channel time: %llu, channel time busy: %llu, "
		  "channel time extension busy: %llu, channel time rx: %llu, "
		  "channel time tx: %llu, scan time: %llu, filled: %u, noise: %d",
		  WIPHY_PR_ARG, __entry->ret, CHAN_PR_ARG,
		  __entry->समय, __entry->समय_busy,
		  __entry->समय_ext_busy, __entry->समय_rx,
		  __entry->समय_प्रकारx, __entry->समय_scan,
		  __entry->filled, __entry->noise)
);

TRACE_EVENT(rdev_tdls_oper,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 u8 *peer, क्रमागत nl80211_tdls_operation oper),
	TP_ARGS(wiphy, netdev, peer, oper),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(peer)
		__field(क्रमागत nl80211_tdls_operation, oper)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(peer, peer);
		__entry->oper = oper;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", " MAC_PR_FMT ", oper: %d",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(peer), __entry->oper)
);

DECLARE_EVENT_CLASS(rdev_pmksa,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा cfg80211_pmksa *pmksa),
	TP_ARGS(wiphy, netdev, pmksa),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(bssid)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(bssid, pmksa->bssid);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", bssid: " MAC_PR_FMT,
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(bssid))
);

TRACE_EVENT(rdev_probe_client,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 स्थिर u8 *peer),
	TP_ARGS(wiphy, netdev, peer),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(peer)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(peer, peer);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", " MAC_PR_FMT,
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(peer))
);

DEFINE_EVENT(rdev_pmksa, rdev_set_pmksa,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा cfg80211_pmksa *pmksa),
	TP_ARGS(wiphy, netdev, pmksa)
);

DEFINE_EVENT(rdev_pmksa, rdev_del_pmksa,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा cfg80211_pmksa *pmksa),
	TP_ARGS(wiphy, netdev, pmksa)
);

TRACE_EVENT(rdev_reमुख्य_on_channel,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
		 काष्ठा ieee80211_channel *chan,
		 अचिन्हित पूर्णांक duration),
	TP_ARGS(wiphy, wdev, chan, duration),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		WDEV_ENTRY
		CHAN_ENTRY
		__field(अचिन्हित पूर्णांक, duration)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		WDEV_ASSIGN;
		CHAN_ASSIGN(chan);
		__entry->duration = duration;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " WDEV_PR_FMT ", " CHAN_PR_FMT ", duration: %u",
		  WIPHY_PR_ARG, WDEV_PR_ARG, CHAN_PR_ARG, __entry->duration)
);

TRACE_EVENT(rdev_वापस_पूर्णांक_cookie,
	TP_PROTO(काष्ठा wiphy *wiphy, पूर्णांक ret, u64 cookie),
	TP_ARGS(wiphy, ret, cookie),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		__field(पूर्णांक, ret)
		__field(u64, cookie)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		__entry->ret = ret;
		__entry->cookie = cookie;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", returned %d, cookie: %llu",
		  WIPHY_PR_ARG, __entry->ret, __entry->cookie)
);

TRACE_EVENT(rdev_cancel_reमुख्य_on_channel,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev, u64 cookie),
	TP_ARGS(wiphy, wdev, cookie),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		WDEV_ENTRY
		__field(u64, cookie)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		WDEV_ASSIGN;
		__entry->cookie = cookie;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " WDEV_PR_FMT ", cookie: %llu",
		  WIPHY_PR_ARG, WDEV_PR_ARG, __entry->cookie)
);

TRACE_EVENT(rdev_mgmt_tx,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
		 काष्ठा cfg80211_mgmt_tx_params *params),
	TP_ARGS(wiphy, wdev, params),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		WDEV_ENTRY
		CHAN_ENTRY
		__field(bool, offchan)
		__field(अचिन्हित पूर्णांक, रुको)
		__field(bool, no_cck)
		__field(bool, करोnt_रुको_क्रम_ack)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		WDEV_ASSIGN;
		CHAN_ASSIGN(params->chan);
		__entry->offchan = params->offchan;
		__entry->रुको = params->रुको;
		__entry->no_cck = params->no_cck;
		__entry->करोnt_रुको_क्रम_ack = params->करोnt_रुको_क्रम_ack;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " WDEV_PR_FMT ", " CHAN_PR_FMT ", offchan: %s,"
		  " wait: %u, no cck: %s, dont wait for ack: %s",
		  WIPHY_PR_ARG, WDEV_PR_ARG, CHAN_PR_ARG,
		  BOOL_TO_STR(__entry->offchan), __entry->रुको,
		  BOOL_TO_STR(__entry->no_cck),
		  BOOL_TO_STR(__entry->करोnt_रुको_क्रम_ack))
);

TRACE_EVENT(rdev_tx_control_port,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 स्थिर u8 *buf, माप_प्रकार len, स्थिर u8 *dest, __be16 proto,
		 bool unencrypted),
	TP_ARGS(wiphy, netdev, buf, len, dest, proto, unencrypted),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(dest)
		__field(__be16, proto)
		__field(bool, unencrypted)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(dest, dest);
		__entry->proto = proto;
		__entry->unencrypted = unencrypted;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", " MAC_PR_FMT ","
		  " proto: 0x%x, unencrypted: %s",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(dest),
		  be16_to_cpu(__entry->proto),
		  BOOL_TO_STR(__entry->unencrypted))
);

TRACE_EVENT(rdev_set_noack_map,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 u16 noack_map),
	TP_ARGS(wiphy, netdev, noack_map),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		__field(u16, noack_map)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		__entry->noack_map = noack_map;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", noack_map: %u",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, __entry->noack_map)
);

DEFINE_EVENT(wiphy_wdev_evt, rdev_get_channel,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev),
	TP_ARGS(wiphy, wdev)
);

TRACE_EVENT(rdev_वापस_chandef,
	TP_PROTO(काष्ठा wiphy *wiphy, पूर्णांक ret,
		 काष्ठा cfg80211_chan_def *chandef),
	TP_ARGS(wiphy, ret, chandef),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		__field(पूर्णांक, ret)
		CHAN_DEF_ENTRY
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		अगर (ret == 0)
			CHAN_DEF_ASSIGN(chandef);
		अन्यथा
			CHAN_DEF_ASSIGN((काष्ठा cfg80211_chan_def *)शून्य);
		__entry->ret = ret;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " CHAN_DEF_PR_FMT ", ret: %d",
		  WIPHY_PR_ARG, CHAN_DEF_PR_ARG, __entry->ret)
);

DEFINE_EVENT(wiphy_wdev_evt, rdev_start_p2p_device,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev),
	TP_ARGS(wiphy, wdev)
);

DEFINE_EVENT(wiphy_wdev_evt, rdev_stop_p2p_device,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev),
	TP_ARGS(wiphy, wdev)
);

TRACE_EVENT(rdev_start_nan,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
		 काष्ठा cfg80211_nan_conf *conf),
	TP_ARGS(wiphy, wdev, conf),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		WDEV_ENTRY
		__field(u8, master_pref)
		__field(u8, bands)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		WDEV_ASSIGN;
		__entry->master_pref = conf->master_pref;
		__entry->bands = conf->bands;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " WDEV_PR_FMT
		  ", master preference: %u, bands: 0x%0x",
		  WIPHY_PR_ARG, WDEV_PR_ARG, __entry->master_pref,
		  __entry->bands)
);

TRACE_EVENT(rdev_nan_change_conf,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
		 काष्ठा cfg80211_nan_conf *conf, u32 changes),
	TP_ARGS(wiphy, wdev, conf, changes),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		WDEV_ENTRY
		__field(u8, master_pref)
		__field(u8, bands)
		__field(u32, changes)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		WDEV_ASSIGN;
		__entry->master_pref = conf->master_pref;
		__entry->bands = conf->bands;
		__entry->changes = changes;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " WDEV_PR_FMT
		  ", master preference: %u, bands: 0x%0x, changes: %x",
		  WIPHY_PR_ARG, WDEV_PR_ARG, __entry->master_pref,
		  __entry->bands, __entry->changes)
);

DEFINE_EVENT(wiphy_wdev_evt, rdev_stop_nan,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev),
	TP_ARGS(wiphy, wdev)
);

TRACE_EVENT(rdev_add_nan_func,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
		 स्थिर काष्ठा cfg80211_nan_func *func),
	TP_ARGS(wiphy, wdev, func),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		WDEV_ENTRY
		__field(u8, func_type)
		__field(u64, cookie)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		WDEV_ASSIGN;
		__entry->func_type = func->type;
		__entry->cookie = func->cookie
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " WDEV_PR_FMT ", type=%u, cookie=%llu",
		  WIPHY_PR_ARG, WDEV_PR_ARG, __entry->func_type,
		  __entry->cookie)
);

TRACE_EVENT(rdev_del_nan_func,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
		 u64 cookie),
	TP_ARGS(wiphy, wdev, cookie),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		WDEV_ENTRY
		__field(u64, cookie)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		WDEV_ASSIGN;
		__entry->cookie = cookie;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " WDEV_PR_FMT ", cookie=%llu",
		  WIPHY_PR_ARG, WDEV_PR_ARG, __entry->cookie)
);

TRACE_EVENT(rdev_set_mac_acl,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा cfg80211_acl_data *params),
	TP_ARGS(wiphy, netdev, params),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		__field(u32, acl_policy)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		__entry->acl_policy = params->acl_policy;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", acl policy: %d",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, __entry->acl_policy)
);

TRACE_EVENT(rdev_update_ft_ies,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा cfg80211_update_ft_ies_params *ftie),
	TP_ARGS(wiphy, netdev, ftie),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		__field(u16, md)
		__dynamic_array(u8, ie, ftie->ie_len)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		__entry->md = ftie->md;
		स_नकल(__get_dynamic_array(ie), ftie->ie, ftie->ie_len);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", md: 0x%x",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, __entry->md)
);

TRACE_EVENT(rdev_crit_proto_start,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
		 क्रमागत nl80211_crit_proto_id protocol, u16 duration),
	TP_ARGS(wiphy, wdev, protocol, duration),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		WDEV_ENTRY
		__field(u16, proto)
		__field(u16, duration)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		WDEV_ASSIGN;
		__entry->proto = protocol;
		__entry->duration = duration;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " WDEV_PR_FMT ", proto=%x, duration=%u",
		  WIPHY_PR_ARG, WDEV_PR_ARG, __entry->proto, __entry->duration)
);

TRACE_EVENT(rdev_crit_proto_stop,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev),
	TP_ARGS(wiphy, wdev),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		WDEV_ENTRY
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		WDEV_ASSIGN;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " WDEV_PR_FMT,
		  WIPHY_PR_ARG, WDEV_PR_ARG)
);

TRACE_EVENT(rdev_channel_चयन,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा cfg80211_csa_settings *params),
	TP_ARGS(wiphy, netdev, params),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		CHAN_DEF_ENTRY
		__field(bool, radar_required)
		__field(bool, block_tx)
		__field(u8, count)
		__dynamic_array(u16, bcn_ofs, params->n_counter_offsets_beacon)
		__dynamic_array(u16, pres_ofs, params->n_counter_offsets_presp)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		CHAN_DEF_ASSIGN(&params->chandef);
		__entry->radar_required = params->radar_required;
		__entry->block_tx = params->block_tx;
		__entry->count = params->count;
		स_नकल(__get_dynamic_array(bcn_ofs),
		       params->counter_offsets_beacon,
		       params->n_counter_offsets_beacon * माप(u16));

		/* probe response offsets are optional */
		अगर (params->n_counter_offsets_presp)
			स_नकल(__get_dynamic_array(pres_ofs),
			       params->counter_offsets_presp,
			       params->n_counter_offsets_presp * माप(u16));
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", " CHAN_DEF_PR_FMT
		  ", block_tx: %d, count: %u, radar_required: %d",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, CHAN_DEF_PR_ARG,
		  __entry->block_tx, __entry->count, __entry->radar_required)
);

TRACE_EVENT(rdev_set_qos_map,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा cfg80211_qos_map *qos_map),
	TP_ARGS(wiphy, netdev, qos_map),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		QOS_MAP_ENTRY
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		QOS_MAP_ASSIGN(qos_map);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", num_des: %u",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, __entry->num_des)
);

TRACE_EVENT(rdev_set_ap_chanwidth,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा cfg80211_chan_def *chandef),
	TP_ARGS(wiphy, netdev, chandef),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		CHAN_DEF_ENTRY
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		CHAN_DEF_ASSIGN(chandef);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", " CHAN_DEF_PR_FMT,
		  WIPHY_PR_ARG, NETDEV_PR_ARG, CHAN_DEF_PR_ARG)
);

TRACE_EVENT(rdev_add_tx_ts,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 u8 tsid, स्थिर u8 *peer, u8 user_prio, u16 admitted_समय),
	TP_ARGS(wiphy, netdev, tsid, peer, user_prio, admitted_समय),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(peer)
		__field(u8, tsid)
		__field(u8, user_prio)
		__field(u16, admitted_समय)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(peer, peer);
		__entry->tsid = tsid;
		__entry->user_prio = user_prio;
		__entry->admitted_समय = admitted_समय;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", " MAC_PR_FMT ", TSID %d, UP %d, time %d",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(peer),
		  __entry->tsid, __entry->user_prio, __entry->admitted_समय)
);

TRACE_EVENT(rdev_del_tx_ts,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 u8 tsid, स्थिर u8 *peer),
	TP_ARGS(wiphy, netdev, tsid, peer),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(peer)
		__field(u8, tsid)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(peer, peer);
		__entry->tsid = tsid;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", " MAC_PR_FMT ", TSID %d",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(peer), __entry->tsid)
);

TRACE_EVENT(rdev_tdls_channel_चयन,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 स्थिर u8 *addr, u8 oper_class,
		 काष्ठा cfg80211_chan_def *chandef),
	TP_ARGS(wiphy, netdev, addr, oper_class, chandef),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(addr)
		__field(u8, oper_class)
		CHAN_DEF_ENTRY
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(addr, addr);
		CHAN_DEF_ASSIGN(chandef);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", " MAC_PR_FMT
		  " oper class %d, " CHAN_DEF_PR_FMT,
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(addr),
		  __entry->oper_class, CHAN_DEF_PR_ARG)
);

TRACE_EVENT(rdev_tdls_cancel_channel_चयन,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 स्थिर u8 *addr),
	TP_ARGS(wiphy, netdev, addr),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(addr)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(addr, addr);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", " MAC_PR_FMT,
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(addr))
);

TRACE_EVENT(rdev_set_pmk,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा cfg80211_pmk_conf *pmk_conf),

	TP_ARGS(wiphy, netdev, pmk_conf),

	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(aa)
		__field(u8, pmk_len)
		__field(u8, pmk_r0_name_len)
		__dynamic_array(u8, pmk, pmk_conf->pmk_len)
		__dynamic_array(u8, pmk_r0_name, WLAN_PMK_NAME_LEN)
	),

	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(aa, pmk_conf->aa);
		__entry->pmk_len = pmk_conf->pmk_len;
		__entry->pmk_r0_name_len =
		pmk_conf->pmk_r0_name ? WLAN_PMK_NAME_LEN : 0;
		स_नकल(__get_dynamic_array(pmk), pmk_conf->pmk,
		       pmk_conf->pmk_len);
		स_नकल(__get_dynamic_array(pmk_r0_name), pmk_conf->pmk_r0_name,
		       pmk_conf->pmk_r0_name ? WLAN_PMK_NAME_LEN : 0);
	),

	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", " MAC_PR_FMT
		  "pmk_len=%u, pmk: %s pmk_r0_name: %s", WIPHY_PR_ARG,
		  NETDEV_PR_ARG, MAC_PR_ARG(aa), __entry->pmk_len,
		  __prपूर्णांक_array(__get_dynamic_array(pmk),
				__get_dynamic_array_len(pmk), 1),
		  __entry->pmk_r0_name_len ?
		  __prपूर्णांक_array(__get_dynamic_array(pmk_r0_name),
				__get_dynamic_array_len(pmk_r0_name), 1) : "")
);

TRACE_EVENT(rdev_del_pmk,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, स्थिर u8 *aa),

	TP_ARGS(wiphy, netdev, aa),

	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(aa)
	),

	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(aa, aa);
	),

	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", " MAC_PR_FMT,
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(aa))
);

TRACE_EVENT(rdev_बाह्यal_auth,
	    TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		     काष्ठा cfg80211_बाह्यal_auth_params *params),
	    TP_ARGS(wiphy, netdev, params),
	    TP_STRUCT__entry(WIPHY_ENTRY
			     NETDEV_ENTRY
			     MAC_ENTRY(bssid)
			     __array(u8, ssid, IEEE80211_MAX_SSID_LEN + 1)
			     __field(u16, status)
	    ),
	    TP_fast_assign(WIPHY_ASSIGN;
			   NETDEV_ASSIGN;
			   MAC_ASSIGN(bssid, params->bssid);
			   स_रखो(__entry->ssid, 0, IEEE80211_MAX_SSID_LEN + 1);
			   स_नकल(__entry->ssid, params->ssid.ssid,
				  params->ssid.ssid_len);
			   __entry->status = params->status;
	    ),
	    TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", bssid: " MAC_PR_FMT
		      ", ssid: %s, status: %u", WIPHY_PR_ARG, NETDEV_PR_ARG,
		      __entry->bssid, __entry->ssid, __entry->status)
);

TRACE_EVENT(rdev_start_radar_detection,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा cfg80211_chan_def *chandef,
		 u32 cac_समय_ms),
	TP_ARGS(wiphy, netdev, chandef, cac_समय_ms),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		CHAN_DEF_ENTRY
		__field(u32, cac_समय_ms)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		CHAN_DEF_ASSIGN(chandef);
		__entry->cac_समय_ms = cac_समय_ms;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", " CHAN_DEF_PR_FMT
		  ", cac_time_ms=%u",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, CHAN_DEF_PR_ARG,
		  __entry->cac_समय_ms)
);

TRACE_EVENT(rdev_set_mcast_rate,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 पूर्णांक *mcast_rate),
	TP_ARGS(wiphy, netdev, mcast_rate),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		__array(पूर्णांक, mcast_rate, NUM_NL80211_BANDS)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		स_नकल(__entry->mcast_rate, mcast_rate,
		       माप(पूर्णांक) * NUM_NL80211_BANDS);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", "
		  "mcast_rates [2.4GHz=0x%x, 5.2GHz=0x%x, 6GHz=0x%x, 60GHz=0x%x]",
		  WIPHY_PR_ARG, NETDEV_PR_ARG,
		  __entry->mcast_rate[NL80211_BAND_2GHZ],
		  __entry->mcast_rate[NL80211_BAND_5GHZ],
		  __entry->mcast_rate[NL80211_BAND_6GHZ],
		  __entry->mcast_rate[NL80211_BAND_60GHZ])
);

TRACE_EVENT(rdev_set_coalesce,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा cfg80211_coalesce *coalesce),
	TP_ARGS(wiphy, coalesce),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		__field(पूर्णांक, n_rules)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		__entry->n_rules = coalesce ? coalesce->n_rules : 0;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", n_rules=%d",
		  WIPHY_PR_ARG, __entry->n_rules)
);

DEFINE_EVENT(wiphy_wdev_evt, rdev_पात_scan,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev),
	TP_ARGS(wiphy, wdev)
);

TRACE_EVENT(rdev_set_multicast_to_unicast,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 स्थिर bool enabled),
	TP_ARGS(wiphy, netdev, enabled),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		__field(bool, enabled)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		__entry->enabled = enabled;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", unicast: %s",
		  WIPHY_PR_ARG, NETDEV_PR_ARG,
		  BOOL_TO_STR(__entry->enabled))
);

DEFINE_EVENT(wiphy_wdev_evt, rdev_get_txq_stats,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev),
	TP_ARGS(wiphy, wdev)
);

TRACE_EVENT(rdev_get_fपंचांग_responder_stats,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा cfg80211_fपंचांग_responder_stats *fपंचांग_stats),

	TP_ARGS(wiphy, netdev, fपंचांग_stats),

	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		__field(u64, बारtamp)
		__field(u32, success_num)
		__field(u32, partial_num)
		__field(u32, failed_num)
		__field(u32, asap_num)
		__field(u32, non_asap_num)
		__field(u64, duration)
		__field(u32, unknown_triggers)
		__field(u32, reschedule)
		__field(u32, out_of_winकरोw)
	),

	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		__entry->success_num = fपंचांग_stats->success_num;
		__entry->partial_num = fपंचांग_stats->partial_num;
		__entry->failed_num = fपंचांग_stats->failed_num;
		__entry->asap_num = fपंचांग_stats->asap_num;
		__entry->non_asap_num = fपंचांग_stats->non_asap_num;
		__entry->duration = fपंचांग_stats->total_duration_ms;
		__entry->unknown_triggers = fपंचांग_stats->unknown_triggers_num;
		__entry->reschedule = fपंचांग_stats->reschedule_requests_num;
		__entry->out_of_winकरोw = fपंचांग_stats->out_of_winकरोw_triggers_num;
	),

	TP_prपूर्णांकk(WIPHY_PR_FMT "Ftm responder stats: success %u, partial %u, "
		"failed %u, asap %u, non asap %u, total duration %llu, unknown "
		"triggers %u, rescheduled %u, out of window %u", WIPHY_PR_ARG,
		__entry->success_num, __entry->partial_num, __entry->failed_num,
		__entry->asap_num, __entry->non_asap_num, __entry->duration,
		__entry->unknown_triggers, __entry->reschedule,
		__entry->out_of_winकरोw)
);

DEFINE_EVENT(wiphy_wdev_cookie_evt, rdev_start_pmsr,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev, u64 cookie),
	TP_ARGS(wiphy, wdev, cookie)
);

DEFINE_EVENT(wiphy_wdev_cookie_evt, rdev_पात_pmsr,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev, u64 cookie),
	TP_ARGS(wiphy, wdev, cookie)
);

/*************************************************************
 *	     cfg80211 exported functions traces		     *
 *************************************************************/

TRACE_EVENT(cfg80211_वापस_bool,
	TP_PROTO(bool ret),
	TP_ARGS(ret),
	TP_STRUCT__entry(
		__field(bool, ret)
	),
	TP_fast_assign(
		__entry->ret = ret;
	),
	TP_prपूर्णांकk("returned %s", BOOL_TO_STR(__entry->ret))
);

DECLARE_EVENT_CLASS(cfg80211_netdev_mac_evt,
	TP_PROTO(काष्ठा net_device *netdev, स्थिर u8 *macaddr),
	TP_ARGS(netdev, macaddr),
	TP_STRUCT__entry(
		NETDEV_ENTRY
		MAC_ENTRY(macaddr)
	),
	TP_fast_assign(
		NETDEV_ASSIGN;
		MAC_ASSIGN(macaddr, macaddr);
	),
	TP_prपूर्णांकk(NETDEV_PR_FMT ", mac: " MAC_PR_FMT,
		  NETDEV_PR_ARG, MAC_PR_ARG(macaddr))
);

DEFINE_EVENT(cfg80211_netdev_mac_evt, cfg80211_notअगरy_new_peer_candidate,
	TP_PROTO(काष्ठा net_device *netdev, स्थिर u8 *macaddr),
	TP_ARGS(netdev, macaddr)
);

DECLARE_EVENT_CLASS(netdev_evt_only,
	TP_PROTO(काष्ठा net_device *netdev),
	TP_ARGS(netdev),
	TP_STRUCT__entry(
		NETDEV_ENTRY
	),
	TP_fast_assign(
		NETDEV_ASSIGN;
	),
	TP_prपूर्णांकk(NETDEV_PR_FMT , NETDEV_PR_ARG)
);

DEFINE_EVENT(netdev_evt_only, cfg80211_send_rx_auth,
	TP_PROTO(काष्ठा net_device *netdev),
	TP_ARGS(netdev)
);

TRACE_EVENT(cfg80211_send_rx_assoc,
	TP_PROTO(काष्ठा net_device *netdev, काष्ठा cfg80211_bss *bss),
	TP_ARGS(netdev, bss),
	TP_STRUCT__entry(
		NETDEV_ENTRY
		MAC_ENTRY(bssid)
		CHAN_ENTRY
	),
	TP_fast_assign(
		NETDEV_ASSIGN;
		MAC_ASSIGN(bssid, bss->bssid);
		CHAN_ASSIGN(bss->channel);
	),
	TP_prपूर्णांकk(NETDEV_PR_FMT ", " MAC_PR_FMT ", " CHAN_PR_FMT,
		  NETDEV_PR_ARG, MAC_PR_ARG(bssid), CHAN_PR_ARG)
);

DECLARE_EVENT_CLASS(netdev_frame_event,
	TP_PROTO(काष्ठा net_device *netdev, स्थिर u8 *buf, पूर्णांक len),
	TP_ARGS(netdev, buf, len),
	TP_STRUCT__entry(
		NETDEV_ENTRY
		__dynamic_array(u8, frame, len)
	),
	TP_fast_assign(
		NETDEV_ASSIGN;
		स_नकल(__get_dynamic_array(frame), buf, len);
	),
	TP_prपूर्णांकk(NETDEV_PR_FMT ", ftype:0x%.2x",
		  NETDEV_PR_ARG,
		  le16_to_cpup((__le16 *)__get_dynamic_array(frame)))
);

DEFINE_EVENT(netdev_frame_event, cfg80211_rx_unprot_mlme_mgmt,
	TP_PROTO(काष्ठा net_device *netdev, स्थिर u8 *buf, पूर्णांक len),
	TP_ARGS(netdev, buf, len)
);

DEFINE_EVENT(netdev_frame_event, cfg80211_rx_mlme_mgmt,
	TP_PROTO(काष्ठा net_device *netdev, स्थिर u8 *buf, पूर्णांक len),
	TP_ARGS(netdev, buf, len)
);

TRACE_EVENT(cfg80211_tx_mlme_mgmt,
	TP_PROTO(काष्ठा net_device *netdev, स्थिर u8 *buf, पूर्णांक len,
		 bool reconnect),
	TP_ARGS(netdev, buf, len, reconnect),
	TP_STRUCT__entry(
		NETDEV_ENTRY
		__dynamic_array(u8, frame, len)
		__field(पूर्णांक, reconnect)
	),
	TP_fast_assign(
		NETDEV_ASSIGN;
		स_नकल(__get_dynamic_array(frame), buf, len);
		__entry->reconnect = reconnect;
	),
	TP_prपूर्णांकk(NETDEV_PR_FMT ", ftype:0x%.2x reconnect:%d",
		  NETDEV_PR_ARG,
		  le16_to_cpup((__le16 *)__get_dynamic_array(frame)),
		  __entry->reconnect)
);

DECLARE_EVENT_CLASS(netdev_mac_evt,
	TP_PROTO(काष्ठा net_device *netdev, स्थिर u8 *mac),
	TP_ARGS(netdev, mac),
	TP_STRUCT__entry(
		NETDEV_ENTRY
		MAC_ENTRY(mac)
	),
	TP_fast_assign(
		NETDEV_ASSIGN;
		MAC_ASSIGN(mac, mac)
	),
	TP_prपूर्णांकk(NETDEV_PR_FMT ", mac: " MAC_PR_FMT,
		  NETDEV_PR_ARG, MAC_PR_ARG(mac))
);

DEFINE_EVENT(netdev_mac_evt, cfg80211_send_auth_समयout,
	TP_PROTO(काष्ठा net_device *netdev, स्थिर u8 *mac),
	TP_ARGS(netdev, mac)
);

DEFINE_EVENT(netdev_mac_evt, cfg80211_send_assoc_समयout,
	TP_PROTO(काष्ठा net_device *netdev, स्थिर u8 *mac),
	TP_ARGS(netdev, mac)
);

TRACE_EVENT(cfg80211_michael_mic_failure,
	TP_PROTO(काष्ठा net_device *netdev, स्थिर u8 *addr,
		 क्रमागत nl80211_key_type key_type, पूर्णांक key_id, स्थिर u8 *tsc),
	TP_ARGS(netdev, addr, key_type, key_id, tsc),
	TP_STRUCT__entry(
		NETDEV_ENTRY
		MAC_ENTRY(addr)
		__field(क्रमागत nl80211_key_type, key_type)
		__field(पूर्णांक, key_id)
		__array(u8, tsc, 6)
	),
	TP_fast_assign(
		NETDEV_ASSIGN;
		MAC_ASSIGN(addr, addr);
		__entry->key_type = key_type;
		__entry->key_id = key_id;
		अगर (tsc)
			स_नकल(__entry->tsc, tsc, 6);
	),
	TP_prपूर्णांकk(NETDEV_PR_FMT ", " MAC_PR_FMT ", key type: %d, key id: %d, tsc: %pm",
		  NETDEV_PR_ARG, MAC_PR_ARG(addr), __entry->key_type,
		  __entry->key_id, __entry->tsc)
);

TRACE_EVENT(cfg80211_पढ़ोy_on_channel,
	TP_PROTO(काष्ठा wireless_dev *wdev, u64 cookie,
		 काष्ठा ieee80211_channel *chan,
		 अचिन्हित पूर्णांक duration),
	TP_ARGS(wdev, cookie, chan, duration),
	TP_STRUCT__entry(
		WDEV_ENTRY
		__field(u64, cookie)
		CHAN_ENTRY
		__field(अचिन्हित पूर्णांक, duration)
	),
	TP_fast_assign(
		WDEV_ASSIGN;
		__entry->cookie = cookie;
		CHAN_ASSIGN(chan);
		__entry->duration = duration;
	),
	TP_prपूर्णांकk(WDEV_PR_FMT ", cookie: %llu, " CHAN_PR_FMT ", duration: %u",
		  WDEV_PR_ARG, __entry->cookie, CHAN_PR_ARG,
		  __entry->duration)
);

TRACE_EVENT(cfg80211_पढ़ोy_on_channel_expired,
	TP_PROTO(काष्ठा wireless_dev *wdev, u64 cookie,
		 काष्ठा ieee80211_channel *chan),
	TP_ARGS(wdev, cookie, chan),
	TP_STRUCT__entry(
		WDEV_ENTRY
		__field(u64, cookie)
		CHAN_ENTRY
	),
	TP_fast_assign(
		WDEV_ASSIGN;
		__entry->cookie = cookie;
		CHAN_ASSIGN(chan);
	),
	TP_prपूर्णांकk(WDEV_PR_FMT ", cookie: %llu, " CHAN_PR_FMT,
		  WDEV_PR_ARG, __entry->cookie, CHAN_PR_ARG)
);

TRACE_EVENT(cfg80211_tx_mgmt_expired,
	TP_PROTO(काष्ठा wireless_dev *wdev, u64 cookie,
		 काष्ठा ieee80211_channel *chan),
	TP_ARGS(wdev, cookie, chan),
	TP_STRUCT__entry(
		WDEV_ENTRY
		__field(u64, cookie)
		CHAN_ENTRY
	),
	TP_fast_assign(
		WDEV_ASSIGN;
		__entry->cookie = cookie;
		CHAN_ASSIGN(chan);
	),
	TP_prपूर्णांकk(WDEV_PR_FMT ", cookie: %llu, " CHAN_PR_FMT,
		  WDEV_PR_ARG, __entry->cookie, CHAN_PR_ARG)
);

TRACE_EVENT(cfg80211_new_sta,
	TP_PROTO(काष्ठा net_device *netdev, स्थिर u8 *mac_addr,
		 काष्ठा station_info *sinfo),
	TP_ARGS(netdev, mac_addr, sinfo),
	TP_STRUCT__entry(
		NETDEV_ENTRY
		MAC_ENTRY(mac_addr)
		SINFO_ENTRY
	),
	TP_fast_assign(
		NETDEV_ASSIGN;
		MAC_ASSIGN(mac_addr, mac_addr);
		SINFO_ASSIGN;
	),
	TP_prपूर्णांकk(NETDEV_PR_FMT ", " MAC_PR_FMT,
		  NETDEV_PR_ARG, MAC_PR_ARG(mac_addr))
);

DEFINE_EVENT(cfg80211_netdev_mac_evt, cfg80211_del_sta,
	TP_PROTO(काष्ठा net_device *netdev, स्थिर u8 *macaddr),
	TP_ARGS(netdev, macaddr)
);

TRACE_EVENT(cfg80211_rx_mgmt,
	TP_PROTO(काष्ठा wireless_dev *wdev, पूर्णांक freq, पूर्णांक sig_dbm),
	TP_ARGS(wdev, freq, sig_dbm),
	TP_STRUCT__entry(
		WDEV_ENTRY
		__field(पूर्णांक, freq)
		__field(पूर्णांक, sig_dbm)
	),
	TP_fast_assign(
		WDEV_ASSIGN;
		__entry->freq = freq;
		__entry->sig_dbm = sig_dbm;
	),
	TP_prपूर्णांकk(WDEV_PR_FMT ", freq: "KHZ_F", sig dbm: %d",
		  WDEV_PR_ARG, PR_KHZ(__entry->freq), __entry->sig_dbm)
);

TRACE_EVENT(cfg80211_mgmt_tx_status,
	TP_PROTO(काष्ठा wireless_dev *wdev, u64 cookie, bool ack),
	TP_ARGS(wdev, cookie, ack),
	TP_STRUCT__entry(
		WDEV_ENTRY
		__field(u64, cookie)
		__field(bool, ack)
	),
	TP_fast_assign(
		WDEV_ASSIGN;
		__entry->cookie = cookie;
		__entry->ack = ack;
	),
	TP_prपूर्णांकk(WDEV_PR_FMT", cookie: %llu, ack: %s",
		  WDEV_PR_ARG, __entry->cookie, BOOL_TO_STR(__entry->ack))
);

TRACE_EVENT(cfg80211_control_port_tx_status,
	TP_PROTO(काष्ठा wireless_dev *wdev, u64 cookie, bool ack),
	TP_ARGS(wdev, cookie, ack),
	TP_STRUCT__entry(
		WDEV_ENTRY
		__field(u64, cookie)
		__field(bool, ack)
	),
	TP_fast_assign(
		WDEV_ASSIGN;
		__entry->cookie = cookie;
		__entry->ack = ack;
	),
	TP_prपूर्णांकk(WDEV_PR_FMT", cookie: %llu, ack: %s",
		  WDEV_PR_ARG, __entry->cookie, BOOL_TO_STR(__entry->ack))
);

TRACE_EVENT(cfg80211_rx_control_port,
	TP_PROTO(काष्ठा net_device *netdev, काष्ठा sk_buff *skb,
		 bool unencrypted),
	TP_ARGS(netdev, skb, unencrypted),
	TP_STRUCT__entry(
		NETDEV_ENTRY
		__field(पूर्णांक, len)
		MAC_ENTRY(from)
		__field(u16, proto)
		__field(bool, unencrypted)
	),
	TP_fast_assign(
		NETDEV_ASSIGN;
		__entry->len = skb->len;
		MAC_ASSIGN(from, eth_hdr(skb)->h_source);
		__entry->proto = be16_to_cpu(skb->protocol);
		__entry->unencrypted = unencrypted;
	),
	TP_prपूर्णांकk(NETDEV_PR_FMT ", len=%d, " MAC_PR_FMT ", proto: 0x%x, unencrypted: %s",
		  NETDEV_PR_ARG, __entry->len, MAC_PR_ARG(from),
		  __entry->proto, BOOL_TO_STR(__entry->unencrypted))
);

TRACE_EVENT(cfg80211_cqm_rssi_notअगरy,
	TP_PROTO(काष्ठा net_device *netdev,
		 क्रमागत nl80211_cqm_rssi_threshold_event rssi_event,
		 s32 rssi_level),
	TP_ARGS(netdev, rssi_event, rssi_level),
	TP_STRUCT__entry(
		NETDEV_ENTRY
		__field(क्रमागत nl80211_cqm_rssi_threshold_event, rssi_event)
		__field(s32, rssi_level)
	),
	TP_fast_assign(
		NETDEV_ASSIGN;
		__entry->rssi_event = rssi_event;
		__entry->rssi_level = rssi_level;
	),
	TP_prपूर्णांकk(NETDEV_PR_FMT ", rssi event: %d, level: %d",
		  NETDEV_PR_ARG, __entry->rssi_event, __entry->rssi_level)
);

TRACE_EVENT(cfg80211_reg_can_beacon,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा cfg80211_chan_def *chandef,
		 क्रमागत nl80211_अगरtype अगरtype, bool check_no_ir),
	TP_ARGS(wiphy, chandef, अगरtype, check_no_ir),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		CHAN_DEF_ENTRY
		__field(क्रमागत nl80211_अगरtype, अगरtype)
		__field(bool, check_no_ir)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		CHAN_DEF_ASSIGN(chandef);
		__entry->अगरtype = अगरtype;
		__entry->check_no_ir = check_no_ir;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " CHAN_DEF_PR_FMT ", iftype=%d check_no_ir=%s",
		  WIPHY_PR_ARG, CHAN_DEF_PR_ARG, __entry->अगरtype,
		  BOOL_TO_STR(__entry->check_no_ir))
);

TRACE_EVENT(cfg80211_chandef_dfs_required,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा cfg80211_chan_def *chandef),
	TP_ARGS(wiphy, chandef),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		CHAN_DEF_ENTRY
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		CHAN_DEF_ASSIGN(chandef);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " CHAN_DEF_PR_FMT,
		  WIPHY_PR_ARG, CHAN_DEF_PR_ARG)
);

TRACE_EVENT(cfg80211_ch_चयन_notअगरy,
	TP_PROTO(काष्ठा net_device *netdev,
		 काष्ठा cfg80211_chan_def *chandef),
	TP_ARGS(netdev, chandef),
	TP_STRUCT__entry(
		NETDEV_ENTRY
		CHAN_DEF_ENTRY
	),
	TP_fast_assign(
		NETDEV_ASSIGN;
		CHAN_DEF_ASSIGN(chandef);
	),
	TP_prपूर्णांकk(NETDEV_PR_FMT ", " CHAN_DEF_PR_FMT,
		  NETDEV_PR_ARG, CHAN_DEF_PR_ARG)
);

TRACE_EVENT(cfg80211_ch_चयन_started_notअगरy,
	TP_PROTO(काष्ठा net_device *netdev,
		 काष्ठा cfg80211_chan_def *chandef),
	TP_ARGS(netdev, chandef),
	TP_STRUCT__entry(
		NETDEV_ENTRY
		CHAN_DEF_ENTRY
	),
	TP_fast_assign(
		NETDEV_ASSIGN;
		CHAN_DEF_ASSIGN(chandef);
	),
	TP_prपूर्णांकk(NETDEV_PR_FMT ", " CHAN_DEF_PR_FMT,
		  NETDEV_PR_ARG, CHAN_DEF_PR_ARG)
);

TRACE_EVENT(cfg80211_radar_event,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा cfg80211_chan_def *chandef),
	TP_ARGS(wiphy, chandef),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		CHAN_DEF_ENTRY
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		CHAN_DEF_ASSIGN(chandef);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " CHAN_DEF_PR_FMT,
		  WIPHY_PR_ARG, CHAN_DEF_PR_ARG)
);

TRACE_EVENT(cfg80211_cac_event,
	TP_PROTO(काष्ठा net_device *netdev, क्रमागत nl80211_radar_event evt),
	TP_ARGS(netdev, evt),
	TP_STRUCT__entry(
		NETDEV_ENTRY
		__field(क्रमागत nl80211_radar_event, evt)
	),
	TP_fast_assign(
		NETDEV_ASSIGN;
		__entry->evt = evt;
	),
	TP_prपूर्णांकk(NETDEV_PR_FMT ",  event: %d",
		  NETDEV_PR_ARG, __entry->evt)
);

DECLARE_EVENT_CLASS(cfg80211_rx_evt,
	TP_PROTO(काष्ठा net_device *netdev, स्थिर u8 *addr),
	TP_ARGS(netdev, addr),
	TP_STRUCT__entry(
		NETDEV_ENTRY
		MAC_ENTRY(addr)
	),
	TP_fast_assign(
		NETDEV_ASSIGN;
		MAC_ASSIGN(addr, addr);
	),
	TP_prपूर्णांकk(NETDEV_PR_FMT ", " MAC_PR_FMT, NETDEV_PR_ARG, MAC_PR_ARG(addr))
);

DEFINE_EVENT(cfg80211_rx_evt, cfg80211_rx_spurious_frame,
	TP_PROTO(काष्ठा net_device *netdev, स्थिर u8 *addr),
	TP_ARGS(netdev, addr)
);

DEFINE_EVENT(cfg80211_rx_evt, cfg80211_rx_unexpected_4addr_frame,
	TP_PROTO(काष्ठा net_device *netdev, स्थिर u8 *addr),
	TP_ARGS(netdev, addr)
);

TRACE_EVENT(cfg80211_ibss_joined,
	TP_PROTO(काष्ठा net_device *netdev, स्थिर u8 *bssid,
		 काष्ठा ieee80211_channel *channel),
	TP_ARGS(netdev, bssid, channel),
	TP_STRUCT__entry(
		NETDEV_ENTRY
		MAC_ENTRY(bssid)
		CHAN_ENTRY
	),
	TP_fast_assign(
		NETDEV_ASSIGN;
		MAC_ASSIGN(bssid, bssid);
		CHAN_ASSIGN(channel);
	),
	TP_prपूर्णांकk(NETDEV_PR_FMT ", bssid: " MAC_PR_FMT ", " CHAN_PR_FMT,
		  NETDEV_PR_ARG, MAC_PR_ARG(bssid), CHAN_PR_ARG)
);

TRACE_EVENT(cfg80211_probe_status,
	TP_PROTO(काष्ठा net_device *netdev, स्थिर u8 *addr, u64 cookie,
		 bool acked),
	TP_ARGS(netdev, addr, cookie, acked),
	TP_STRUCT__entry(
		NETDEV_ENTRY
		MAC_ENTRY(addr)
		__field(u64, cookie)
		__field(bool, acked)
	),
	TP_fast_assign(
		NETDEV_ASSIGN;
		MAC_ASSIGN(addr, addr);
		__entry->cookie = cookie;
		__entry->acked = acked;
	),
	TP_prपूर्णांकk(NETDEV_PR_FMT " addr:" MAC_PR_FMT ", cookie: %llu, acked: %s",
		  NETDEV_PR_ARG, MAC_PR_ARG(addr), __entry->cookie,
		  BOOL_TO_STR(__entry->acked))
);

TRACE_EVENT(cfg80211_cqm_pktloss_notअगरy,
	TP_PROTO(काष्ठा net_device *netdev, स्थिर u8 *peer, u32 num_packets),
	TP_ARGS(netdev, peer, num_packets),
	TP_STRUCT__entry(
		NETDEV_ENTRY
		MAC_ENTRY(peer)
		__field(u32, num_packets)
	),
	TP_fast_assign(
		NETDEV_ASSIGN;
		MAC_ASSIGN(peer, peer);
		__entry->num_packets = num_packets;
	),
	TP_prपूर्णांकk(NETDEV_PR_FMT ", peer: " MAC_PR_FMT ", num of lost packets: %u",
		  NETDEV_PR_ARG, MAC_PR_ARG(peer), __entry->num_packets)
);

DEFINE_EVENT(cfg80211_netdev_mac_evt, cfg80211_gtk_rekey_notअगरy,
	TP_PROTO(काष्ठा net_device *netdev, स्थिर u8 *macaddr),
	TP_ARGS(netdev, macaddr)
);

TRACE_EVENT(cfg80211_pmksa_candidate_notअगरy,
	TP_PROTO(काष्ठा net_device *netdev, पूर्णांक index, स्थिर u8 *bssid,
		 bool preauth),
	TP_ARGS(netdev, index, bssid, preauth),
	TP_STRUCT__entry(
		NETDEV_ENTRY
		__field(पूर्णांक, index)
		MAC_ENTRY(bssid)
		__field(bool, preauth)
	),
	TP_fast_assign(
		NETDEV_ASSIGN;
		__entry->index = index;
		MAC_ASSIGN(bssid, bssid);
		__entry->preauth = preauth;
	),
	TP_prपूर्णांकk(NETDEV_PR_FMT ", index:%d, bssid: " MAC_PR_FMT ", pre auth: %s",
		  NETDEV_PR_ARG, __entry->index, MAC_PR_ARG(bssid),
		  BOOL_TO_STR(__entry->preauth))
);

TRACE_EVENT(cfg80211_report_obss_beacon,
	TP_PROTO(काष्ठा wiphy *wiphy, स्थिर u8 *frame, माप_प्रकार len,
		 पूर्णांक freq, पूर्णांक sig_dbm),
	TP_ARGS(wiphy, frame, len, freq, sig_dbm),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		__field(पूर्णांक, freq)
		__field(पूर्णांक, sig_dbm)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		__entry->freq = freq;
		__entry->sig_dbm = sig_dbm;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", freq: "KHZ_F", sig_dbm: %d",
		  WIPHY_PR_ARG, PR_KHZ(__entry->freq), __entry->sig_dbm)
);

TRACE_EVENT(cfg80211_tdls_oper_request,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, स्थिर u8 *peer,
		 क्रमागत nl80211_tdls_operation oper, u16 reason_code),
	TP_ARGS(wiphy, netdev, peer, oper, reason_code),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(peer)
		__field(क्रमागत nl80211_tdls_operation, oper)
		__field(u16, reason_code)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(peer, peer);
		__entry->oper = oper;
		__entry->reason_code = reason_code;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", peer: " MAC_PR_FMT ", oper: %d, reason_code %u",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(peer), __entry->oper,
		  __entry->reason_code)
	);

TRACE_EVENT(cfg80211_scan_करोne,
	TP_PROTO(काष्ठा cfg80211_scan_request *request,
		 काष्ठा cfg80211_scan_info *info),
	TP_ARGS(request, info),
	TP_STRUCT__entry(
		__field(u32, n_channels)
		__dynamic_array(u8, ie, request ? request->ie_len : 0)
		__array(u32, rates, NUM_NL80211_BANDS)
		__field(u32, wdev_id)
		MAC_ENTRY(wiphy_mac)
		__field(bool, no_cck)
		__field(bool, पातed)
		__field(u64, scan_start_tsf)
		MAC_ENTRY(tsf_bssid)
	),
	TP_fast_assign(
		अगर (request) अणु
			स_नकल(__get_dynamic_array(ie), request->ie,
			       request->ie_len);
			स_नकल(__entry->rates, request->rates,
			       NUM_NL80211_BANDS);
			__entry->wdev_id = request->wdev ?
					request->wdev->identअगरier : 0;
			अगर (request->wiphy)
				MAC_ASSIGN(wiphy_mac,
					   request->wiphy->perm_addr);
			__entry->no_cck = request->no_cck;
		पूर्ण
		अगर (info) अणु
			__entry->पातed = info->पातed;
			__entry->scan_start_tsf = info->scan_start_tsf;
			MAC_ASSIGN(tsf_bssid, info->tsf_bssid);
		पूर्ण
	),
	TP_prपूर्णांकk("aborted: %s, scan start (TSF): %llu, tsf_bssid: " MAC_PR_FMT,
		  BOOL_TO_STR(__entry->पातed),
		  (अचिन्हित दीर्घ दीर्घ)__entry->scan_start_tsf,
		  MAC_PR_ARG(tsf_bssid))
);

DECLARE_EVENT_CLASS(wiphy_id_evt,
	TP_PROTO(काष्ठा wiphy *wiphy, u64 id),
	TP_ARGS(wiphy, id),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		__field(u64, id)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		__entry->id = id;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", id: %llu", WIPHY_PR_ARG, __entry->id)
);

DEFINE_EVENT(wiphy_id_evt, cfg80211_sched_scan_stopped,
	TP_PROTO(काष्ठा wiphy *wiphy, u64 id),
	TP_ARGS(wiphy, id)
);

DEFINE_EVENT(wiphy_id_evt, cfg80211_sched_scan_results,
	TP_PROTO(काष्ठा wiphy *wiphy, u64 id),
	TP_ARGS(wiphy, id)
);

TRACE_EVENT(cfg80211_get_bss,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा ieee80211_channel *channel,
		 स्थिर u8 *bssid, स्थिर u8 *ssid, माप_प्रकार ssid_len,
		 क्रमागत ieee80211_bss_type bss_type,
		 क्रमागत ieee80211_privacy privacy),
	TP_ARGS(wiphy, channel, bssid, ssid, ssid_len, bss_type, privacy),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		CHAN_ENTRY
		MAC_ENTRY(bssid)
		__dynamic_array(u8, ssid, ssid_len)
		__field(क्रमागत ieee80211_bss_type, bss_type)
		__field(क्रमागत ieee80211_privacy, privacy)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		CHAN_ASSIGN(channel);
		MAC_ASSIGN(bssid, bssid);
		स_नकल(__get_dynamic_array(ssid), ssid, ssid_len);
		__entry->bss_type = bss_type;
		__entry->privacy = privacy;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " CHAN_PR_FMT ", " MAC_PR_FMT
		  ", buf: %#.2x, bss_type: %d, privacy: %d",
		  WIPHY_PR_ARG, CHAN_PR_ARG, MAC_PR_ARG(bssid),
		  ((u8 *)__get_dynamic_array(ssid))[0], __entry->bss_type,
		  __entry->privacy)
);

TRACE_EVENT(cfg80211_inक्रमm_bss_frame,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा cfg80211_inक्रमm_bss *data,
		 काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len),
	TP_ARGS(wiphy, data, mgmt, len),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		CHAN_ENTRY
		__field(क्रमागत nl80211_bss_scan_width, scan_width)
		__dynamic_array(u8, mgmt, len)
		__field(s32, संकेत)
		__field(u64, ts_bootसमय)
		__field(u64, parent_tsf)
		MAC_ENTRY(parent_bssid)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		CHAN_ASSIGN(data->chan);
		__entry->scan_width = data->scan_width;
		अगर (mgmt)
			स_नकल(__get_dynamic_array(mgmt), mgmt, len);
		__entry->संकेत = data->संकेत;
		__entry->ts_bootसमय = data->bootसमय_ns;
		__entry->parent_tsf = data->parent_tsf;
		MAC_ASSIGN(parent_bssid, data->parent_bssid);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " CHAN_PR_FMT
		  "(scan_width: %d) signal: %d, tsb:%llu, detect_tsf:%llu, tsf_bssid: "
		  MAC_PR_FMT, WIPHY_PR_ARG, CHAN_PR_ARG, __entry->scan_width,
		  __entry->संकेत, (अचिन्हित दीर्घ दीर्घ)__entry->ts_bootसमय,
		  (अचिन्हित दीर्घ दीर्घ)__entry->parent_tsf,
		  MAC_PR_ARG(parent_bssid))
);

DECLARE_EVENT_CLASS(cfg80211_bss_evt,
	TP_PROTO(काष्ठा cfg80211_bss *pub),
	TP_ARGS(pub),
	TP_STRUCT__entry(
		MAC_ENTRY(bssid)
		CHAN_ENTRY
	),
	TP_fast_assign(
		MAC_ASSIGN(bssid, pub->bssid);
		CHAN_ASSIGN(pub->channel);
	),
	TP_prपूर्णांकk(MAC_PR_FMT ", " CHAN_PR_FMT, MAC_PR_ARG(bssid), CHAN_PR_ARG)
);

DEFINE_EVENT(cfg80211_bss_evt, cfg80211_वापस_bss,
	TP_PROTO(काष्ठा cfg80211_bss *pub),
	TP_ARGS(pub)
);

TRACE_EVENT(cfg80211_वापस_uपूर्णांक,
	TP_PROTO(अचिन्हित पूर्णांक ret),
	TP_ARGS(ret),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, ret)
	),
	TP_fast_assign(
		__entry->ret = ret;
	),
	TP_prपूर्णांकk("ret: %d", __entry->ret)
);

TRACE_EVENT(cfg80211_वापस_u32,
	TP_PROTO(u32 ret),
	TP_ARGS(ret),
	TP_STRUCT__entry(
		__field(u32, ret)
	),
	TP_fast_assign(
		__entry->ret = ret;
	),
	TP_prपूर्णांकk("ret: %u", __entry->ret)
);

TRACE_EVENT(cfg80211_report_wowlan_wakeup,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
		 काष्ठा cfg80211_wowlan_wakeup *wakeup),
	TP_ARGS(wiphy, wdev, wakeup),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		WDEV_ENTRY
		__field(bool, non_wireless)
		__field(bool, disconnect)
		__field(bool, magic_pkt)
		__field(bool, gtk_rekey_failure)
		__field(bool, eap_identity_req)
		__field(bool, four_way_handshake)
		__field(bool, rfसमाप्त_release)
		__field(s32, pattern_idx)
		__field(u32, packet_len)
		__dynamic_array(u8, packet,
				wakeup ? wakeup->packet_present_len : 0)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		WDEV_ASSIGN;
		__entry->non_wireless = !wakeup;
		__entry->disconnect = wakeup ? wakeup->disconnect : false;
		__entry->magic_pkt = wakeup ? wakeup->magic_pkt : false;
		__entry->gtk_rekey_failure = wakeup ? wakeup->gtk_rekey_failure : false;
		__entry->eap_identity_req = wakeup ? wakeup->eap_identity_req : false;
		__entry->four_way_handshake = wakeup ? wakeup->four_way_handshake : false;
		__entry->rfसमाप्त_release = wakeup ? wakeup->rfसमाप्त_release : false;
		__entry->pattern_idx = wakeup ? wakeup->pattern_idx : false;
		__entry->packet_len = wakeup ? wakeup->packet_len : false;
		अगर (wakeup && wakeup->packet && wakeup->packet_present_len)
			स_नकल(__get_dynamic_array(packet), wakeup->packet,
			       wakeup->packet_present_len);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " WDEV_PR_FMT, WIPHY_PR_ARG, WDEV_PR_ARG)
);

TRACE_EVENT(cfg80211_ft_event,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा cfg80211_ft_event_params *ft_event),
	TP_ARGS(wiphy, netdev, ft_event),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		__dynamic_array(u8, ies, ft_event->ies_len)
		MAC_ENTRY(target_ap)
		__dynamic_array(u8, ric_ies, ft_event->ric_ies_len)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		अगर (ft_event->ies)
			स_नकल(__get_dynamic_array(ies), ft_event->ies,
			       ft_event->ies_len);
		MAC_ASSIGN(target_ap, ft_event->target_ap);
		अगर (ft_event->ric_ies)
			स_नकल(__get_dynamic_array(ric_ies), ft_event->ric_ies,
			       ft_event->ric_ies_len);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", target_ap: " MAC_PR_FMT,
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(target_ap))
);

TRACE_EVENT(cfg80211_stop_अगरace,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev),
	TP_ARGS(wiphy, wdev),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		WDEV_ENTRY
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		WDEV_ASSIGN;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " WDEV_PR_FMT,
		  WIPHY_PR_ARG, WDEV_PR_ARG)
);

TRACE_EVENT(cfg80211_pmsr_report,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
		 u64 cookie, स्थिर u8 *addr),
	TP_ARGS(wiphy, wdev, cookie, addr),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		WDEV_ENTRY
		__field(u64, cookie)
		MAC_ENTRY(addr)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		WDEV_ASSIGN;
		__entry->cookie = cookie;
		MAC_ASSIGN(addr, addr);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " WDEV_PR_FMT ", cookie:%lld, " MAC_PR_FMT,
		  WIPHY_PR_ARG, WDEV_PR_ARG,
		  (अचिन्हित दीर्घ दीर्घ)__entry->cookie,
		  MAC_PR_ARG(addr))
);

TRACE_EVENT(cfg80211_pmsr_complete,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev, u64 cookie),
	TP_ARGS(wiphy, wdev, cookie),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		WDEV_ENTRY
		__field(u64, cookie)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		WDEV_ASSIGN;
		__entry->cookie = cookie;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " WDEV_PR_FMT ", cookie:%lld",
		  WIPHY_PR_ARG, WDEV_PR_ARG,
		  (अचिन्हित दीर्घ दीर्घ)__entry->cookie)
);

TRACE_EVENT(rdev_update_owe_info,
	    TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		     काष्ठा cfg80211_update_owe_info *owe_info),
	    TP_ARGS(wiphy, netdev, owe_info),
	    TP_STRUCT__entry(WIPHY_ENTRY
			     NETDEV_ENTRY
			     MAC_ENTRY(peer)
			     __field(u16, status)
			     __dynamic_array(u8, ie, owe_info->ie_len)),
	    TP_fast_assign(WIPHY_ASSIGN;
			   NETDEV_ASSIGN;
			   MAC_ASSIGN(peer, owe_info->peer);
			   __entry->status = owe_info->status;
			   स_नकल(__get_dynamic_array(ie),
				  owe_info->ie, owe_info->ie_len);),
	    TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", peer: " MAC_PR_FMT
		  " status %d", WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(peer),
		  __entry->status)
);

TRACE_EVENT(cfg80211_update_owe_info_event,
	    TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		     काष्ठा cfg80211_update_owe_info *owe_info),
	    TP_ARGS(wiphy, netdev, owe_info),
	    TP_STRUCT__entry(WIPHY_ENTRY
			     NETDEV_ENTRY
			     MAC_ENTRY(peer)
			     __dynamic_array(u8, ie, owe_info->ie_len)),
	    TP_fast_assign(WIPHY_ASSIGN;
			   NETDEV_ASSIGN;
			   MAC_ASSIGN(peer, owe_info->peer);
			   स_नकल(__get_dynamic_array(ie), owe_info->ie,
				  owe_info->ie_len);),
	    TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", peer: " MAC_PR_FMT,
		      WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(peer))
);

TRACE_EVENT(rdev_probe_mesh_link,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 स्थिर u8 *dest, स्थिर u8 *buf, माप_प्रकार len),
	TP_ARGS(wiphy, netdev, dest, buf, len),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(dest)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(dest, dest);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", " MAC_PR_FMT,
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(dest))
);

TRACE_EVENT(rdev_set_tid_config,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 काष्ठा cfg80211_tid_config *tid_conf),
	TP_ARGS(wiphy, netdev, tid_conf),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(peer)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(peer, tid_conf->peer);
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", peer: " MAC_PR_FMT,
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(peer))
);

TRACE_EVENT(rdev_reset_tid_config,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		 स्थिर u8 *peer, u8 tids),
	TP_ARGS(wiphy, netdev, peer, tids),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		NETDEV_ENTRY
		MAC_ENTRY(peer)
		__field(u8, tids)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		NETDEV_ASSIGN;
		MAC_ASSIGN(peer, peer);
		__entry->tids = tids;
	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", " NETDEV_PR_FMT ", peer: " MAC_PR_FMT ", tids: 0x%x",
		  WIPHY_PR_ARG, NETDEV_PR_ARG, MAC_PR_ARG(peer), __entry->tids)
);

TRACE_EVENT(rdev_set_sar_specs,
	TP_PROTO(काष्ठा wiphy *wiphy, काष्ठा cfg80211_sar_specs *sar),
	TP_ARGS(wiphy, sar),
	TP_STRUCT__entry(
		WIPHY_ENTRY
		__field(u16, type)
		__field(u16, num)
	),
	TP_fast_assign(
		WIPHY_ASSIGN;
		__entry->type = sar->type;
		__entry->num = sar->num_sub_specs;

	),
	TP_prपूर्णांकk(WIPHY_PR_FMT ", Set type:%d, num_specs:%d",
		  WIPHY_PR_ARG, __entry->type, __entry->num)
);

#पूर्ण_अगर /* !__RDEV_OPS_TRACE || TRACE_HEADER_MULTI_READ */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace
#समावेश <trace/define_trace.h>
