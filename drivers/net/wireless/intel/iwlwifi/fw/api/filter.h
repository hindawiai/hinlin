<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_filter_h__
#घोषणा __iwl_fw_api_filter_h__

#समावेश "fw/api/mac.h"

#घोषणा MAX_PORT_ID_NUM	2
#घोषणा MAX_MCAST_FILTERING_ADDRESSES 256

/**
 * काष्ठा iwl_mcast_filter_cmd - configure multicast filter.
 * @filter_own: Set 1 to filter out multicast packets sent by station itself
 * @port_id:	Multicast MAC addresses array specअगरier. This is a strange way
 *		to identअगरy network पूर्णांकerface aकरोpted in host-device IF.
 *		It is used by FW as index in array of addresses. This array has
 *		MAX_PORT_ID_NUM members.
 * @count:	Number of MAC addresses in the array
 * @pass_all:	Set 1 to pass all multicast packets.
 * @bssid:	current association BSSID.
 * @reserved:	reserved
 * @addr_list:	Place holder क्रम array of MAC addresses.
 *		IMPORTANT: add padding अगर necessary to ensure DWORD alignment.
 */
काष्ठा iwl_mcast_filter_cmd अणु
	u8 filter_own;
	u8 port_id;
	u8 count;
	u8 pass_all;
	u8 bssid[6];
	u8 reserved[2];
	u8 addr_list[0];
पूर्ण __packed; /* MCAST_FILTERING_CMD_API_S_VER_1 */

#घोषणा MAX_BCAST_FILTERS 8
#घोषणा MAX_BCAST_FILTER_ATTRS 2

/**
 * क्रमागत iwl_mvm_bcast_filter_attr_offset - written by fw क्रम each Rx packet
 * @BCAST_FILTER_OFFSET_PAYLOAD_START: offset is from payload start.
 * @BCAST_FILTER_OFFSET_IP_END: offset is from ip header end (i.e.
 *	start of ip payload).
 */
क्रमागत iwl_mvm_bcast_filter_attr_offset अणु
	BCAST_FILTER_OFFSET_PAYLOAD_START = 0,
	BCAST_FILTER_OFFSET_IP_END = 1,
पूर्ण;

/**
 * काष्ठा iwl_fw_bcast_filter_attr - broadcast filter attribute
 * @offset_type:	&क्रमागत iwl_mvm_bcast_filter_attr_offset.
 * @offset:	starting offset of this pattern.
 * @reserved1:	reserved
 * @val:	value to match - big endian (MSB is the first
 *		byte to match from offset pos).
 * @mask:	mask to match (big endian).
 */
काष्ठा iwl_fw_bcast_filter_attr अणु
	u8 offset_type;
	u8 offset;
	__le16 reserved1;
	__be32 val;
	__be32 mask;
पूर्ण __packed; /* BCAST_FILTER_ATT_S_VER_1 */

/**
 * क्रमागत iwl_mvm_bcast_filter_frame_type - filter frame type
 * @BCAST_FILTER_FRAME_TYPE_ALL: consider all frames.
 * @BCAST_FILTER_FRAME_TYPE_IPV4: consider only ipv4 frames
 */
क्रमागत iwl_mvm_bcast_filter_frame_type अणु
	BCAST_FILTER_FRAME_TYPE_ALL = 0,
	BCAST_FILTER_FRAME_TYPE_IPV4 = 1,
पूर्ण;

/**
 * काष्ठा iwl_fw_bcast_filter - broadcast filter
 * @discard: discard frame (1) or let it pass (0).
 * @frame_type: &क्रमागत iwl_mvm_bcast_filter_frame_type.
 * @reserved1: reserved
 * @num_attrs: number of valid attributes in this filter.
 * @attrs: attributes of this filter. a filter is considered matched
 *	only when all its attributes are matched (i.e. AND relationship)
 */
काष्ठा iwl_fw_bcast_filter अणु
	u8 discard;
	u8 frame_type;
	u8 num_attrs;
	u8 reserved1;
	काष्ठा iwl_fw_bcast_filter_attr attrs[MAX_BCAST_FILTER_ATTRS];
पूर्ण __packed; /* BCAST_FILTER_S_VER_1 */

/**
 * काष्ठा iwl_fw_bcast_mac - per-mac broadcast filtering configuration.
 * @शेष_discard: शेष action क्रम this mac (discard (1) / pass (0)).
 * @reserved1: reserved
 * @attached_filters: biपंचांगap of relevant filters क्रम this mac.
 */
काष्ठा iwl_fw_bcast_mac अणु
	u8 शेष_discard;
	u8 reserved1;
	__le16 attached_filters;
पूर्ण __packed; /* BCAST_MAC_CONTEXT_S_VER_1 */

/**
 * काष्ठा iwl_bcast_filter_cmd - broadcast filtering configuration
 * @disable: enable (0) / disable (1)
 * @max_bcast_filters: max number of filters (MAX_BCAST_FILTERS)
 * @max_macs: max number of macs (NUM_MAC_INDEX_DRIVER)
 * @reserved1: reserved
 * @filters: broadcast filters
 * @macs: broadcast filtering configuration per-mac
 */
काष्ठा iwl_bcast_filter_cmd अणु
	u8 disable;
	u8 max_bcast_filters;
	u8 max_macs;
	u8 reserved1;
	काष्ठा iwl_fw_bcast_filter filters[MAX_BCAST_FILTERS];
	काष्ठा iwl_fw_bcast_mac macs[NUM_MAC_INDEX_DRIVER];
पूर्ण __packed; /* BCAST_FILTERING_HCMD_API_S_VER_1 */

#पूर्ण_अगर /* __iwl_fw_api_filter_h__ */
