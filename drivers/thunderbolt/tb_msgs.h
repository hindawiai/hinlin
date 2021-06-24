<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Thunderbolt control channel messages
 *
 * Copyright (C) 2014 Andreas Noever <andreas.noever@gmail.com>
 * Copyright (C) 2017, Intel Corporation
 */

#अगर_अघोषित _TB_MSGS
#घोषणा _TB_MSGS

#समावेश <linux/types.h>
#समावेश <linux/uuid.h>

क्रमागत tb_cfg_space अणु
	TB_CFG_HOPS = 0,
	TB_CFG_PORT = 1,
	TB_CFG_SWITCH = 2,
	TB_CFG_COUNTERS = 3,
पूर्ण;

क्रमागत tb_cfg_error अणु
	TB_CFG_ERROR_PORT_NOT_CONNECTED = 0,
	TB_CFG_ERROR_LINK_ERROR = 1,
	TB_CFG_ERROR_INVALID_CONFIG_SPACE = 2,
	TB_CFG_ERROR_NO_SUCH_PORT = 4,
	TB_CFG_ERROR_ACK_PLUG_EVENT = 7, /* send as reply to TB_CFG_PKG_EVENT */
	TB_CFG_ERROR_LOOP = 8,
	TB_CFG_ERROR_HEC_ERROR_DETECTED = 12,
	TB_CFG_ERROR_FLOW_CONTROL_ERROR = 13,
	TB_CFG_ERROR_LOCK = 15,
पूर्ण;

/* common header */
काष्ठा tb_cfg_header अणु
	u32 route_hi:22;
	u32 unknown:10; /* highest order bit is set on replies */
	u32 route_lo;
पूर्ण __packed;

/* additional header क्रम पढ़ो/ग_लिखो packets */
काष्ठा tb_cfg_address अणु
	u32 offset:13; /* in dwords */
	u32 length:6; /* in dwords */
	u32 port:6;
	क्रमागत tb_cfg_space space:2;
	u32 seq:2; /* sequence number  */
	u32 zero:3;
पूर्ण __packed;

/* TB_CFG_PKG_READ, response क्रम TB_CFG_PKG_WRITE */
काष्ठा cfg_पढ़ो_pkg अणु
	काष्ठा tb_cfg_header header;
	काष्ठा tb_cfg_address addr;
पूर्ण __packed;

/* TB_CFG_PKG_WRITE, response क्रम TB_CFG_PKG_READ */
काष्ठा cfg_ग_लिखो_pkg अणु
	काष्ठा tb_cfg_header header;
	काष्ठा tb_cfg_address addr;
	u32 data[64]; /* maximum size, tb_cfg_address.length has 6 bits */
पूर्ण __packed;

/* TB_CFG_PKG_ERROR */
काष्ठा cfg_error_pkg अणु
	काष्ठा tb_cfg_header header;
	क्रमागत tb_cfg_error error:4;
	u32 zero1:4;
	u32 port:6;
	u32 zero2:2; /* Both should be zero, still they are dअगरferent fields. */
	u32 zero3:14;
	u32 pg:2;
पूर्ण __packed;

#घोषणा TB_CFG_ERROR_PG_HOT_PLUG	0x2
#घोषणा TB_CFG_ERROR_PG_HOT_UNPLUG	0x3

/* TB_CFG_PKG_EVENT */
काष्ठा cfg_event_pkg अणु
	काष्ठा tb_cfg_header header;
	u32 port:6;
	u32 zero:25;
	bool unplug:1;
पूर्ण __packed;

/* TB_CFG_PKG_RESET */
काष्ठा cfg_reset_pkg अणु
	काष्ठा tb_cfg_header header;
पूर्ण __packed;

/* TB_CFG_PKG_PREPARE_TO_SLEEP */
काष्ठा cfg_pts_pkg अणु
	काष्ठा tb_cfg_header header;
	u32 data;
पूर्ण __packed;

/* ICM messages */

क्रमागत icm_pkg_code अणु
	ICM_GET_TOPOLOGY = 0x1,
	ICM_DRIVER_READY = 0x3,
	ICM_APPROVE_DEVICE = 0x4,
	ICM_CHALLENGE_DEVICE = 0x5,
	ICM_ADD_DEVICE_KEY = 0x6,
	ICM_GET_ROUTE = 0xa,
	ICM_APPROVE_XDOMAIN = 0x10,
	ICM_DISCONNECT_XDOMAIN = 0x11,
	ICM_PREBOOT_ACL = 0x18,
	ICM_USB4_SWITCH_OP = 0x20,
पूर्ण;

क्रमागत icm_event_code अणु
	ICM_EVENT_DEVICE_CONNECTED = 0x3,
	ICM_EVENT_DEVICE_DISCONNECTED = 0x4,
	ICM_EVENT_XDOMAIN_CONNECTED = 0x6,
	ICM_EVENT_XDOMAIN_DISCONNECTED = 0x7,
	ICM_EVENT_RTD3_VETO = 0xa,
पूर्ण;

काष्ठा icm_pkg_header अणु
	u8 code;
	u8 flags;
	u8 packet_id;
	u8 total_packets;
पूर्ण;

#घोषणा ICM_FLAGS_ERROR			BIT(0)
#घोषणा ICM_FLAGS_NO_KEY		BIT(1)
#घोषणा ICM_FLAGS_SLEVEL_SHIFT		3
#घोषणा ICM_FLAGS_SLEVEL_MASK		GENMASK(4, 3)
#घोषणा ICM_FLAGS_DUAL_LANE		BIT(5)
#घोषणा ICM_FLAGS_SPEED_GEN3		BIT(7)
#घोषणा ICM_FLAGS_WRITE			BIT(7)

काष्ठा icm_pkg_driver_पढ़ोy अणु
	काष्ठा icm_pkg_header hdr;
पूर्ण;

/* Falcon Ridge only messages */

काष्ठा icm_fr_pkg_driver_पढ़ोy_response अणु
	काष्ठा icm_pkg_header hdr;
	u8 romver;
	u8 ramver;
	u16 security_level;
पूर्ण;

#घोषणा ICM_FR_SLEVEL_MASK		0xf

/* Falcon Ridge & Alpine Ridge common messages */

काष्ठा icm_fr_pkg_get_topology अणु
	काष्ठा icm_pkg_header hdr;
पूर्ण;

#घोषणा ICM_GET_TOPOLOGY_PACKETS	14

काष्ठा icm_fr_pkg_get_topology_response अणु
	काष्ठा icm_pkg_header hdr;
	u32 route_lo;
	u32 route_hi;
	u8 first_data;
	u8 second_data;
	u8 drom_i2c_address_index;
	u8 चयन_index;
	u32 reserved[2];
	u32 ports[16];
	u32 port_hop_info[16];
पूर्ण;

#घोषणा ICM_SWITCH_USED			BIT(0)
#घोषणा ICM_SWITCH_UPSTREAM_PORT_MASK	GENMASK(7, 1)
#घोषणा ICM_SWITCH_UPSTREAM_PORT_SHIFT	1

#घोषणा ICM_PORT_TYPE_MASK		GENMASK(23, 0)
#घोषणा ICM_PORT_INDEX_SHIFT		24
#घोषणा ICM_PORT_INDEX_MASK		GENMASK(31, 24)

काष्ठा icm_fr_event_device_connected अणु
	काष्ठा icm_pkg_header hdr;
	uuid_t ep_uuid;
	u8 connection_key;
	u8 connection_id;
	u16 link_info;
	u32 ep_name[55];
पूर्ण;

#घोषणा ICM_LINK_INFO_LINK_MASK		0x7
#घोषणा ICM_LINK_INFO_DEPTH_SHIFT	4
#घोषणा ICM_LINK_INFO_DEPTH_MASK	GENMASK(7, 4)
#घोषणा ICM_LINK_INFO_APPROVED		BIT(8)
#घोषणा ICM_LINK_INFO_REJECTED		BIT(9)
#घोषणा ICM_LINK_INFO_BOOT		BIT(10)

काष्ठा icm_fr_pkg_approve_device अणु
	काष्ठा icm_pkg_header hdr;
	uuid_t ep_uuid;
	u8 connection_key;
	u8 connection_id;
	u16 reserved;
पूर्ण;

काष्ठा icm_fr_event_device_disconnected अणु
	काष्ठा icm_pkg_header hdr;
	u16 reserved;
	u16 link_info;
पूर्ण;

काष्ठा icm_fr_event_xकरोमुख्य_connected अणु
	काष्ठा icm_pkg_header hdr;
	u16 reserved;
	u16 link_info;
	uuid_t remote_uuid;
	uuid_t local_uuid;
	u32 local_route_hi;
	u32 local_route_lo;
	u32 remote_route_hi;
	u32 remote_route_lo;
पूर्ण;

काष्ठा icm_fr_event_xकरोमुख्य_disconnected अणु
	काष्ठा icm_pkg_header hdr;
	u16 reserved;
	u16 link_info;
	uuid_t remote_uuid;
पूर्ण;

काष्ठा icm_fr_pkg_add_device_key अणु
	काष्ठा icm_pkg_header hdr;
	uuid_t ep_uuid;
	u8 connection_key;
	u8 connection_id;
	u16 reserved;
	u32 key[8];
पूर्ण;

काष्ठा icm_fr_pkg_add_device_key_response अणु
	काष्ठा icm_pkg_header hdr;
	uuid_t ep_uuid;
	u8 connection_key;
	u8 connection_id;
	u16 reserved;
पूर्ण;

काष्ठा icm_fr_pkg_challenge_device अणु
	काष्ठा icm_pkg_header hdr;
	uuid_t ep_uuid;
	u8 connection_key;
	u8 connection_id;
	u16 reserved;
	u32 challenge[8];
पूर्ण;

काष्ठा icm_fr_pkg_challenge_device_response अणु
	काष्ठा icm_pkg_header hdr;
	uuid_t ep_uuid;
	u8 connection_key;
	u8 connection_id;
	u16 reserved;
	u32 challenge[8];
	u32 response[8];
पूर्ण;

काष्ठा icm_fr_pkg_approve_xकरोमुख्य अणु
	काष्ठा icm_pkg_header hdr;
	u16 reserved;
	u16 link_info;
	uuid_t remote_uuid;
	u16 transmit_path;
	u16 transmit_ring;
	u16 receive_path;
	u16 receive_ring;
पूर्ण;

काष्ठा icm_fr_pkg_approve_xकरोमुख्य_response अणु
	काष्ठा icm_pkg_header hdr;
	u16 reserved;
	u16 link_info;
	uuid_t remote_uuid;
	u16 transmit_path;
	u16 transmit_ring;
	u16 receive_path;
	u16 receive_ring;
पूर्ण;

/* Alpine Ridge only messages */

काष्ठा icm_ar_pkg_driver_पढ़ोy_response अणु
	काष्ठा icm_pkg_header hdr;
	u8 romver;
	u8 ramver;
	u16 info;
पूर्ण;

#घोषणा ICM_AR_FLAGS_RTD3		BIT(6)

#घोषणा ICM_AR_INFO_SLEVEL_MASK		GENMASK(3, 0)
#घोषणा ICM_AR_INFO_BOOT_ACL_SHIFT	7
#घोषणा ICM_AR_INFO_BOOT_ACL_MASK	GENMASK(11, 7)
#घोषणा ICM_AR_INFO_BOOT_ACL_SUPPORTED	BIT(13)

काष्ठा icm_ar_pkg_get_route अणु
	काष्ठा icm_pkg_header hdr;
	u16 reserved;
	u16 link_info;
पूर्ण;

काष्ठा icm_ar_pkg_get_route_response अणु
	काष्ठा icm_pkg_header hdr;
	u16 reserved;
	u16 link_info;
	u32 route_hi;
	u32 route_lo;
पूर्ण;

काष्ठा icm_ar_boot_acl_entry अणु
	u32 uuid_lo;
	u32 uuid_hi;
पूर्ण;

#घोषणा ICM_AR_PREBOOT_ACL_ENTRIES	16

काष्ठा icm_ar_pkg_preboot_acl अणु
	काष्ठा icm_pkg_header hdr;
	काष्ठा icm_ar_boot_acl_entry acl[ICM_AR_PREBOOT_ACL_ENTRIES];
पूर्ण;

काष्ठा icm_ar_pkg_preboot_acl_response अणु
	काष्ठा icm_pkg_header hdr;
	काष्ठा icm_ar_boot_acl_entry acl[ICM_AR_PREBOOT_ACL_ENTRIES];
पूर्ण;

/* Titan Ridge messages */

काष्ठा icm_tr_pkg_driver_पढ़ोy_response अणु
	काष्ठा icm_pkg_header hdr;
	u16 reserved1;
	u16 info;
	u32 nvm_version;
	u16 device_id;
	u16 reserved2;
पूर्ण;

#घोषणा ICM_TR_FLAGS_RTD3		BIT(6)

#घोषणा ICM_TR_INFO_SLEVEL_MASK		GENMASK(2, 0)
#घोषणा ICM_TR_INFO_PROTO_VERSION_MASK	GENMASK(6, 4)
#घोषणा ICM_TR_INFO_PROTO_VERSION_SHIFT	4
#घोषणा ICM_TR_INFO_BOOT_ACL_SHIFT	7
#घोषणा ICM_TR_INFO_BOOT_ACL_MASK	GENMASK(12, 7)

काष्ठा icm_tr_event_device_connected अणु
	काष्ठा icm_pkg_header hdr;
	uuid_t ep_uuid;
	u32 route_hi;
	u32 route_lo;
	u8 connection_id;
	u8 reserved;
	u16 link_info;
	u32 ep_name[55];
पूर्ण;

काष्ठा icm_tr_event_device_disconnected अणु
	काष्ठा icm_pkg_header hdr;
	u32 route_hi;
	u32 route_lo;
पूर्ण;

काष्ठा icm_tr_event_xकरोमुख्य_connected अणु
	काष्ठा icm_pkg_header hdr;
	u16 reserved;
	u16 link_info;
	uuid_t remote_uuid;
	uuid_t local_uuid;
	u32 local_route_hi;
	u32 local_route_lo;
	u32 remote_route_hi;
	u32 remote_route_lo;
पूर्ण;

काष्ठा icm_tr_event_xकरोमुख्य_disconnected अणु
	काष्ठा icm_pkg_header hdr;
	u32 route_hi;
	u32 route_lo;
	uuid_t remote_uuid;
पूर्ण;

काष्ठा icm_tr_pkg_approve_device अणु
	काष्ठा icm_pkg_header hdr;
	uuid_t ep_uuid;
	u32 route_hi;
	u32 route_lo;
	u8 connection_id;
	u8 reserved1[3];
पूर्ण;

काष्ठा icm_tr_pkg_add_device_key अणु
	काष्ठा icm_pkg_header hdr;
	uuid_t ep_uuid;
	u32 route_hi;
	u32 route_lo;
	u8 connection_id;
	u8 reserved[3];
	u32 key[8];
पूर्ण;

काष्ठा icm_tr_pkg_challenge_device अणु
	काष्ठा icm_pkg_header hdr;
	uuid_t ep_uuid;
	u32 route_hi;
	u32 route_lo;
	u8 connection_id;
	u8 reserved[3];
	u32 challenge[8];
पूर्ण;

काष्ठा icm_tr_pkg_approve_xकरोमुख्य अणु
	काष्ठा icm_pkg_header hdr;
	u32 route_hi;
	u32 route_lo;
	uuid_t remote_uuid;
	u16 transmit_path;
	u16 transmit_ring;
	u16 receive_path;
	u16 receive_ring;
पूर्ण;

काष्ठा icm_tr_pkg_disconnect_xकरोमुख्य अणु
	काष्ठा icm_pkg_header hdr;
	u8 stage;
	u8 reserved[3];
	u32 route_hi;
	u32 route_lo;
	uuid_t remote_uuid;
पूर्ण;

काष्ठा icm_tr_pkg_challenge_device_response अणु
	काष्ठा icm_pkg_header hdr;
	uuid_t ep_uuid;
	u32 route_hi;
	u32 route_lo;
	u8 connection_id;
	u8 reserved[3];
	u32 challenge[8];
	u32 response[8];
पूर्ण;

काष्ठा icm_tr_pkg_add_device_key_response अणु
	काष्ठा icm_pkg_header hdr;
	uuid_t ep_uuid;
	u32 route_hi;
	u32 route_lo;
	u8 connection_id;
	u8 reserved[3];
पूर्ण;

काष्ठा icm_tr_pkg_approve_xकरोमुख्य_response अणु
	काष्ठा icm_pkg_header hdr;
	u32 route_hi;
	u32 route_lo;
	uuid_t remote_uuid;
	u16 transmit_path;
	u16 transmit_ring;
	u16 receive_path;
	u16 receive_ring;
पूर्ण;

काष्ठा icm_tr_pkg_disconnect_xकरोमुख्य_response अणु
	काष्ठा icm_pkg_header hdr;
	u8 stage;
	u8 reserved[3];
	u32 route_hi;
	u32 route_lo;
	uuid_t remote_uuid;
पूर्ण;

/* Ice Lake messages */

काष्ठा icm_icl_event_rtd3_veto अणु
	काष्ठा icm_pkg_header hdr;
	u32 veto_reason;
पूर्ण;

/* USB4 ICM messages */

काष्ठा icm_usb4_चयन_op अणु
	काष्ठा icm_pkg_header hdr;
	u32 route_hi;
	u32 route_lo;
	u32 metadata;
	u16 opcode;
	u16 data_len_valid;
	u32 data[16];
पूर्ण;

#घोषणा ICM_USB4_SWITCH_DATA_LEN_MASK	GENMASK(3, 0)
#घोषणा ICM_USB4_SWITCH_DATA_VALID	BIT(4)

काष्ठा icm_usb4_चयन_op_response अणु
	काष्ठा icm_pkg_header hdr;
	u32 route_hi;
	u32 route_lo;
	u32 metadata;
	u16 opcode;
	u16 status;
	u32 data[16];
पूर्ण;

/* XDoमुख्य messages */

काष्ठा tb_xकरोमुख्य_header अणु
	u32 route_hi;
	u32 route_lo;
	u32 length_sn;
पूर्ण;

#घोषणा TB_XDOMAIN_LENGTH_MASK	GENMASK(5, 0)
#घोषणा TB_XDOMAIN_SN_MASK	GENMASK(28, 27)
#घोषणा TB_XDOMAIN_SN_SHIFT	27

क्रमागत tb_xdp_type अणु
	UUID_REQUEST_OLD = 1,
	UUID_RESPONSE = 2,
	PROPERTIES_REQUEST,
	PROPERTIES_RESPONSE,
	PROPERTIES_CHANGED_REQUEST,
	PROPERTIES_CHANGED_RESPONSE,
	ERROR_RESPONSE,
	UUID_REQUEST = 12,
पूर्ण;

काष्ठा tb_xdp_header अणु
	काष्ठा tb_xकरोमुख्य_header xd_hdr;
	uuid_t uuid;
	u32 type;
पूर्ण;

काष्ठा tb_xdp_uuid अणु
	काष्ठा tb_xdp_header hdr;
पूर्ण;

काष्ठा tb_xdp_uuid_response अणु
	काष्ठा tb_xdp_header hdr;
	uuid_t src_uuid;
	u32 src_route_hi;
	u32 src_route_lo;
पूर्ण;

काष्ठा tb_xdp_properties अणु
	काष्ठा tb_xdp_header hdr;
	uuid_t src_uuid;
	uuid_t dst_uuid;
	u16 offset;
	u16 reserved;
पूर्ण;

काष्ठा tb_xdp_properties_response अणु
	काष्ठा tb_xdp_header hdr;
	uuid_t src_uuid;
	uuid_t dst_uuid;
	u16 offset;
	u16 data_length;
	u32 generation;
	u32 data[0];
पूर्ण;

/*
 * Max length of data array single XDoमुख्य property response is allowed
 * to carry.
 */
#घोषणा TB_XDP_PROPERTIES_MAX_DATA_LENGTH	\
	(((256 - 4 - माप(काष्ठा tb_xdp_properties_response))) / 4)

/* Maximum size of the total property block in dwords we allow */
#घोषणा TB_XDP_PROPERTIES_MAX_LENGTH		500

काष्ठा tb_xdp_properties_changed अणु
	काष्ठा tb_xdp_header hdr;
	uuid_t src_uuid;
पूर्ण;

काष्ठा tb_xdp_properties_changed_response अणु
	काष्ठा tb_xdp_header hdr;
पूर्ण;

क्रमागत tb_xdp_error अणु
	ERROR_SUCCESS,
	ERROR_UNKNOWN_PACKET,
	ERROR_UNKNOWN_DOMAIN,
	ERROR_NOT_SUPPORTED,
	ERROR_NOT_READY,
पूर्ण;

काष्ठा tb_xdp_error_response अणु
	काष्ठा tb_xdp_header hdr;
	u32 error;
पूर्ण;

#पूर्ण_अगर
