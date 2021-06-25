<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright (c) 2011, Microsoft Corporation.
 *
 * Authors:
 *   Haiyang Zhang <haiyangz@microsoft.com>
 *   Hank Janssen  <hjanssen@microsoft.com>
 *   K. Y. Srinivasan <kys@microsoft.com>
 */

#अगर_अघोषित _HYPERV_NET_H
#घोषणा _HYPERV_NET_H

#समावेश <linux/list.h>
#समावेश <linux/hyperv.h>
#समावेश <linux/rndis.h>

/* RSS related */
#घोषणा OID_GEN_RECEIVE_SCALE_CAPABILITIES 0x00010203  /* query only */
#घोषणा OID_GEN_RECEIVE_SCALE_PARAMETERS 0x00010204  /* query and set */

#घोषणा NDIS_OBJECT_TYPE_RSS_CAPABILITIES 0x88
#घोषणा NDIS_OBJECT_TYPE_RSS_PARAMETERS 0x89
#घोषणा NDIS_OBJECT_TYPE_OFFLOAD	0xa7

#घोषणा NDIS_RECEIVE_SCALE_CAPABILITIES_REVISION_2 2
#घोषणा NDIS_RECEIVE_SCALE_PARAMETERS_REVISION_2 2

काष्ठा ndis_obj_header अणु
	u8 type;
	u8 rev;
	u16 size;
पूर्ण __packed;

/* ndis_recv_scale_cap/cap_flag */
#घोषणा NDIS_RSS_CAPS_MESSAGE_SIGNALED_INTERRUPTS 0x01000000
#घोषणा NDIS_RSS_CAPS_CLASSIFICATION_AT_ISR       0x02000000
#घोषणा NDIS_RSS_CAPS_CLASSIFICATION_AT_DPC       0x04000000
#घोषणा NDIS_RSS_CAPS_USING_MSI_X                 0x08000000
#घोषणा NDIS_RSS_CAPS_RSS_AVAILABLE_ON_PORTS      0x10000000
#घोषणा NDIS_RSS_CAPS_SUPPORTS_MSI_X              0x20000000
#घोषणा NDIS_RSS_CAPS_HASH_TYPE_TCP_IPV4          0x00000100
#घोषणा NDIS_RSS_CAPS_HASH_TYPE_TCP_IPV6          0x00000200
#घोषणा NDIS_RSS_CAPS_HASH_TYPE_TCP_IPV6_EX       0x00000400

काष्ठा ndis_recv_scale_cap अणु /* NDIS_RECEIVE_SCALE_CAPABILITIES */
	काष्ठा ndis_obj_header hdr;
	u32 cap_flag;
	u32 num_पूर्णांक_msg;
	u32 num_recv_que;
	u16 num_indirect_tabent;
पूर्ण __packed;


/* ndis_recv_scale_param flags */
#घोषणा NDIS_RSS_PARAM_FLAG_BASE_CPU_UNCHANGED     0x0001
#घोषणा NDIS_RSS_PARAM_FLAG_HASH_INFO_UNCHANGED    0x0002
#घोषणा NDIS_RSS_PARAM_FLAG_ITABLE_UNCHANGED       0x0004
#घोषणा NDIS_RSS_PARAM_FLAG_HASH_KEY_UNCHANGED     0x0008
#घोषणा NDIS_RSS_PARAM_FLAG_DISABLE_RSS            0x0010

/* Hash info bits */
#घोषणा NDIS_HASH_FUNC_TOEPLITZ 0x00000001
#घोषणा NDIS_HASH_IPV4          0x00000100
#घोषणा NDIS_HASH_TCP_IPV4      0x00000200
#घोषणा NDIS_HASH_IPV6          0x00000400
#घोषणा NDIS_HASH_IPV6_EX       0x00000800
#घोषणा NDIS_HASH_TCP_IPV6      0x00001000
#घोषणा NDIS_HASH_TCP_IPV6_EX   0x00002000

#घोषणा NDIS_RSS_INसूचीECTION_TABLE_MAX_SIZE_REVISION_2 (128 * 4)
#घोषणा NDIS_RSS_HASH_SECRET_KEY_MAX_SIZE_REVISION_2   40

#घोषणा ITAB_NUM 128

काष्ठा ndis_recv_scale_param अणु /* NDIS_RECEIVE_SCALE_PARAMETERS */
	काष्ठा ndis_obj_header hdr;

	/* Qualअगरies the rest of the inक्रमmation */
	u16 flag;

	/* The base CPU number to करो receive processing. not used */
	u16 base_cpu_number;

	/* This describes the hash function and type being enabled */
	u32 hashinfo;

	/* The size of indirection table array */
	u16 indirect_tअसलize;

	/* The offset of the indirection table from the beginning of this
	 * काष्ठाure
	 */
	u32 indirect_taboffset;

	/* The size of the hash secret key */
	u16 hashkey_size;

	/* The offset of the secret key from the beginning of this काष्ठाure */
	u32 hashkey_offset;

	u32 processor_masks_offset;
	u32 num_processor_masks;
	u32 processor_masks_entry_size;
पूर्ण;

काष्ठा ndis_tcp_ip_checksum_info अणु
	जोड़ अणु
		काष्ठा अणु
			u32 is_ipv4:1;
			u32 is_ipv6:1;
			u32 tcp_checksum:1;
			u32 udp_checksum:1;
			u32 ip_header_checksum:1;
			u32 reserved:11;
			u32 tcp_header_offset:10;
		पूर्ण transmit;
		काष्ठा अणु
			u32 tcp_checksum_failed:1;
			u32 udp_checksum_failed:1;
			u32 ip_checksum_failed:1;
			u32 tcp_checksum_succeeded:1;
			u32 udp_checksum_succeeded:1;
			u32 ip_checksum_succeeded:1;
			u32 loopback:1;
			u32 tcp_checksum_value_invalid:1;
			u32 ip_checksum_value_invalid:1;
		पूर्ण receive;
		u32  value;
	पूर्ण;
पूर्ण;

काष्ठा ndis_pkt_8021q_info अणु
	जोड़ अणु
		काष्ठा अणु
			u32 pri:3; /* User Priority */
			u32 cfi:1; /* Canonical Format ID */
			u32 vlanid:12; /* VLAN ID */
			u32 reserved:16;
		पूर्ण;
		u32 value;
	पूर्ण;
पूर्ण;

/*
 * Represent netvsc packet which contains 1 RNDIS and 1 ethernet frame
 * within the RNDIS
 *
 * The size of this काष्ठाure is less than 48 bytes and we can now
 * place this काष्ठाure in the skb->cb field.
 */
काष्ठा hv_netvsc_packet अणु
	/* Bookkeeping stuff */
	u8 cp_partial; /* partial copy पूर्णांकo send buffer */

	u8 rmsg_size; /* RNDIS header and PPI size */
	u8 rmsg_pgcnt; /* page count of RNDIS header and PPI */
	u8 page_buf_cnt;

	u16 q_idx;
	u16 total_packets;

	u32 total_bytes;
	u32 send_buf_index;
	u32 total_data_buflen;
पूर्ण;

#घोषणा NETVSC_HASH_KEYLEN 40

काष्ठा netvsc_device_info अणु
	अचिन्हित अक्षर mac_adr[ETH_ALEN];
	u32  num_chn;
	u32  send_sections;
	u32  recv_sections;
	u32  send_section_size;
	u32  recv_section_size;

	काष्ठा bpf_prog *bprog;

	u8 rss_key[NETVSC_HASH_KEYLEN];
पूर्ण;

क्रमागत rndis_device_state अणु
	RNDIS_DEV_UNINITIALIZED = 0,
	RNDIS_DEV_INITIALIZING,
	RNDIS_DEV_INITIALIZED,
	RNDIS_DEV_DATAINITIALIZED,
पूर्ण;

काष्ठा rndis_device अणु
	काष्ठा net_device *ndev;

	क्रमागत rndis_device_state state;

	atomic_t new_req_id;

	spinlock_t request_lock;
	काष्ठा list_head req_list;

	काष्ठा work_काष्ठा mcast_work;
	u32 filter;

	bool link_state;        /* 0 - link up, 1 - link करोwn */

	u8 hw_mac_adr[ETH_ALEN];
	u8 rss_key[NETVSC_HASH_KEYLEN];
पूर्ण;


/* Interface */
काष्ठा rndis_message;
काष्ठा ndis_offload_params;
काष्ठा netvsc_device;
काष्ठा netvsc_channel;
काष्ठा net_device_context;

बाह्य u32 netvsc_ring_bytes;

काष्ठा netvsc_device *netvsc_device_add(काष्ठा hv_device *device,
					स्थिर काष्ठा netvsc_device_info *info);
पूर्णांक netvsc_alloc_recv_comp_ring(काष्ठा netvsc_device *net_device, u32 q_idx);
व्योम netvsc_device_हटाओ(काष्ठा hv_device *device);
पूर्णांक netvsc_send(काष्ठा net_device *net,
		काष्ठा hv_netvsc_packet *packet,
		काष्ठा rndis_message *rndis_msg,
		काष्ठा hv_page_buffer *page_buffer,
		काष्ठा sk_buff *skb,
		bool xdp_tx);
व्योम netvsc_linkstatus_callback(काष्ठा net_device *net,
				काष्ठा rndis_message *resp,
				व्योम *data, u32 data_buflen);
पूर्णांक netvsc_recv_callback(काष्ठा net_device *net,
			 काष्ठा netvsc_device *nvdev,
			 काष्ठा netvsc_channel *nvchan);
व्योम netvsc_channel_cb(व्योम *context);
पूर्णांक netvsc_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);

u32 netvsc_run_xdp(काष्ठा net_device *ndev, काष्ठा netvsc_channel *nvchan,
		   काष्ठा xdp_buff *xdp);
अचिन्हित पूर्णांक netvsc_xdp_fraglen(अचिन्हित पूर्णांक len);
काष्ठा bpf_prog *netvsc_xdp_get(काष्ठा netvsc_device *nvdev);
पूर्णांक netvsc_xdp_set(काष्ठा net_device *dev, काष्ठा bpf_prog *prog,
		   काष्ठा netlink_ext_ack *extack,
		   काष्ठा netvsc_device *nvdev);
पूर्णांक netvsc_vf_setxdp(काष्ठा net_device *vf_netdev, काष्ठा bpf_prog *prog);
पूर्णांक netvsc_bpf(काष्ठा net_device *dev, काष्ठा netdev_bpf *bpf);

पूर्णांक rndis_set_subchannel(काष्ठा net_device *ndev,
			 काष्ठा netvsc_device *nvdev,
			 काष्ठा netvsc_device_info *dev_info);
पूर्णांक rndis_filter_खोलो(काष्ठा netvsc_device *nvdev);
पूर्णांक rndis_filter_बंद(काष्ठा netvsc_device *nvdev);
काष्ठा netvsc_device *rndis_filter_device_add(काष्ठा hv_device *dev,
					      काष्ठा netvsc_device_info *info);
व्योम rndis_filter_update(काष्ठा netvsc_device *nvdev);
व्योम rndis_filter_device_हटाओ(काष्ठा hv_device *dev,
				काष्ठा netvsc_device *nvdev);
पूर्णांक rndis_filter_set_rss_param(काष्ठा rndis_device *rdev,
			       स्थिर u8 *key);
पूर्णांक rndis_filter_set_offload_params(काष्ठा net_device *ndev,
				    काष्ठा netvsc_device *nvdev,
				    काष्ठा ndis_offload_params *req_offloads);
पूर्णांक rndis_filter_receive(काष्ठा net_device *ndev,
			 काष्ठा netvsc_device *net_dev,
			 काष्ठा netvsc_channel *nvchan,
			 व्योम *data, u32 buflen);

पूर्णांक rndis_filter_set_device_mac(काष्ठा netvsc_device *ndev,
				स्थिर अक्षर *mac);

पूर्णांक netvsc_चयन_datapath(काष्ठा net_device *nv_dev, bool vf);

#घोषणा NVSP_INVALID_PROTOCOL_VERSION	((u32)0xFFFFFFFF)

#घोषणा NVSP_PROTOCOL_VERSION_1		2
#घोषणा NVSP_PROTOCOL_VERSION_2		0x30002
#घोषणा NVSP_PROTOCOL_VERSION_4		0x40000
#घोषणा NVSP_PROTOCOL_VERSION_5		0x50000
#घोषणा NVSP_PROTOCOL_VERSION_6		0x60000
#घोषणा NVSP_PROTOCOL_VERSION_61	0x60001

क्रमागत अणु
	NVSP_MSG_TYPE_NONE = 0,

	/* Init Messages */
	NVSP_MSG_TYPE_INIT			= 1,
	NVSP_MSG_TYPE_INIT_COMPLETE		= 2,

	NVSP_VERSION_MSG_START			= 100,

	/* Version 1 Messages */
	NVSP_MSG1_TYPE_SEND_NDIS_VER		= NVSP_VERSION_MSG_START,

	NVSP_MSG1_TYPE_SEND_RECV_BUF,
	NVSP_MSG1_TYPE_SEND_RECV_BUF_COMPLETE,
	NVSP_MSG1_TYPE_REVOKE_RECV_BUF,

	NVSP_MSG1_TYPE_SEND_SEND_BUF,
	NVSP_MSG1_TYPE_SEND_SEND_BUF_COMPLETE,
	NVSP_MSG1_TYPE_REVOKE_SEND_BUF,

	NVSP_MSG1_TYPE_SEND_RNDIS_PKT,
	NVSP_MSG1_TYPE_SEND_RNDIS_PKT_COMPLETE,

	/* Version 2 messages */
	NVSP_MSG2_TYPE_SEND_CHIMNEY_DELEGATED_BUF,
	NVSP_MSG2_TYPE_SEND_CHIMNEY_DELEGATED_BUF_COMP,
	NVSP_MSG2_TYPE_REVOKE_CHIMNEY_DELEGATED_BUF,

	NVSP_MSG2_TYPE_RESUME_CHIMNEY_RX_INDICATION,

	NVSP_MSG2_TYPE_TERMINATE_CHIMNEY,
	NVSP_MSG2_TYPE_TERMINATE_CHIMNEY_COMP,

	NVSP_MSG2_TYPE_INDICATE_CHIMNEY_EVENT,

	NVSP_MSG2_TYPE_SEND_CHIMNEY_PKT,
	NVSP_MSG2_TYPE_SEND_CHIMNEY_PKT_COMP,

	NVSP_MSG2_TYPE_POST_CHIMNEY_RECV_REQ,
	NVSP_MSG2_TYPE_POST_CHIMNEY_RECV_REQ_COMP,

	NVSP_MSG2_TYPE_ALLOC_RXBUF,
	NVSP_MSG2_TYPE_ALLOC_RXBUF_COMP,

	NVSP_MSG2_TYPE_FREE_RXBUF,

	NVSP_MSG2_TYPE_SEND_VMQ_RNDIS_PKT,
	NVSP_MSG2_TYPE_SEND_VMQ_RNDIS_PKT_COMP,

	NVSP_MSG2_TYPE_SEND_NDIS_CONFIG,

	NVSP_MSG2_TYPE_ALLOC_CHIMNEY_HANDLE,
	NVSP_MSG2_TYPE_ALLOC_CHIMNEY_HANDLE_COMP,

	NVSP_MSG2_MAX = NVSP_MSG2_TYPE_ALLOC_CHIMNEY_HANDLE_COMP,

	/* Version 4 messages */
	NVSP_MSG4_TYPE_SEND_VF_ASSOCIATION,
	NVSP_MSG4_TYPE_SWITCH_DATA_PATH,
	NVSP_MSG4_TYPE_UPLINK_CONNECT_STATE_DEPRECATED,

	NVSP_MSG4_MAX = NVSP_MSG4_TYPE_UPLINK_CONNECT_STATE_DEPRECATED,

	/* Version 5 messages */
	NVSP_MSG5_TYPE_OID_QUERY_EX,
	NVSP_MSG5_TYPE_OID_QUERY_EX_COMP,
	NVSP_MSG5_TYPE_SUBCHANNEL,
	NVSP_MSG5_TYPE_SEND_INसूचीECTION_TABLE,

	NVSP_MSG5_MAX = NVSP_MSG5_TYPE_SEND_INसूचीECTION_TABLE,

	/* Version 6 messages */
	NVSP_MSG6_TYPE_PD_API,
	NVSP_MSG6_TYPE_PD_POST_BATCH,

	NVSP_MSG6_MAX = NVSP_MSG6_TYPE_PD_POST_BATCH
पूर्ण;

क्रमागत अणु
	NVSP_STAT_NONE = 0,
	NVSP_STAT_SUCCESS,
	NVSP_STAT_FAIL,
	NVSP_STAT_PROTOCOL_TOO_NEW,
	NVSP_STAT_PROTOCOL_TOO_OLD,
	NVSP_STAT_INVALID_RNDIS_PKT,
	NVSP_STAT_BUSY,
	NVSP_STAT_PROTOCOL_UNSUPPORTED,
	NVSP_STAT_MAX,
पूर्ण;

काष्ठा nvsp_message_header अणु
	u32 msg_type;
पूर्ण;

/* Init Messages */

/*
 * This message is used by the VSC to initialize the channel after the channels
 * has been खोलोed. This message should never include anything other then
 * versioning (i.e. this message will be the same क्रम ever).
 */
काष्ठा nvsp_message_init अणु
	u32 min_protocol_ver;
	u32 max_protocol_ver;
पूर्ण __packed;

/*
 * This message is used by the VSP to complete the initialization of the
 * channel. This message should never include anything other then versioning
 * (i.e. this message will be the same क्रम ever).
 */
काष्ठा nvsp_message_init_complete अणु
	u32 negotiated_protocol_ver;
	u32 max_mdl_chain_len;
	u32 status;
पूर्ण __packed;

जोड़ nvsp_message_init_uber अणु
	काष्ठा nvsp_message_init init;
	काष्ठा nvsp_message_init_complete init_complete;
पूर्ण __packed;

/* Version 1 Messages */

/*
 * This message is used by the VSC to send the NDIS version to the VSP. The VSP
 * can use this inक्रमmation when handling OIDs sent by the VSC.
 */
काष्ठा nvsp_1_message_send_ndis_version अणु
	u32 ndis_major_ver;
	u32 ndis_minor_ver;
पूर्ण __packed;

/*
 * This message is used by the VSC to send a receive buffer to the VSP. The VSP
 * can then use the receive buffer to send data to the VSC.
 */
काष्ठा nvsp_1_message_send_receive_buffer अणु
	u32 gpadl_handle;
	u16 id;
पूर्ण __packed;

काष्ठा nvsp_1_receive_buffer_section अणु
	u32 offset;
	u32 sub_alloc_size;
	u32 num_sub_allocs;
	u32 end_offset;
पूर्ण __packed;

/*
 * This message is used by the VSP to acknowledge a receive buffer send by the
 * VSC. This message must be sent by the VSP beक्रमe the VSP uses the receive
 * buffer.
 */
काष्ठा nvsp_1_message_send_receive_buffer_complete अणु
	u32 status;
	u32 num_sections;

	/*
	 * The receive buffer is split पूर्णांकo two parts, a large suballocation
	 * section and a small suballocation section. These sections are then
	 * suballocated by a certain size.
	 */

	/*
	 * For example, the following अवरोध up of the receive buffer has 6
	 * large suballocations and 10 small suballocations.
	 */

	/*
	 * |            Large Section          |  |   Small Section   |
	 * ------------------------------------------------------------
	 * |     |     |     |     |     |     |  | | | | | | | | | | |
	 * |                                      |
	 *  LargeOffset                            SmallOffset
	 */

	काष्ठा nvsp_1_receive_buffer_section sections[1];
पूर्ण __packed;

/*
 * This message is sent by the VSC to revoke the receive buffer.  After the VSP
 * completes this transaction, the vsp should never use the receive buffer
 * again.
 */
काष्ठा nvsp_1_message_revoke_receive_buffer अणु
	u16 id;
पूर्ण;

/*
 * This message is used by the VSC to send a send buffer to the VSP. The VSC
 * can then use the send buffer to send data to the VSP.
 */
काष्ठा nvsp_1_message_send_send_buffer अणु
	u32 gpadl_handle;
	u16 id;
पूर्ण __packed;

/*
 * This message is used by the VSP to acknowledge a send buffer sent by the
 * VSC. This message must be sent by the VSP beक्रमe the VSP uses the sent
 * buffer.
 */
काष्ठा nvsp_1_message_send_send_buffer_complete अणु
	u32 status;

	/*
	 * The VSC माला_लो to choose the size of the send buffer and the VSP माला_लो
	 * to choose the sections size of the buffer.  This was करोne to enable
	 * dynamic reconfigurations when the cost of GPA-direct buffers
	 * decreases.
	 */
	u32 section_size;
पूर्ण __packed;

/*
 * This message is sent by the VSC to revoke the send buffer.  After the VSP
 * completes this transaction, the vsp should never use the send buffer again.
 */
काष्ठा nvsp_1_message_revoke_send_buffer अणु
	u16 id;
पूर्ण;

/*
 * This message is used by both the VSP and the VSC to send a RNDIS message to
 * the opposite channel endpoपूर्णांक.
 */
काष्ठा nvsp_1_message_send_rndis_packet अणु
	/*
	 * This field is specअगरied by RNDIS. They assume there's two dअगरferent
	 * channels of communication. However, the Network VSP only has one.
	 * Thereक्रमe, the channel travels with the RNDIS packet.
	 */
	u32 channel_type;

	/*
	 * This field is used to send part or all of the data through a send
	 * buffer. This values specअगरies an index पूर्णांकo the send buffer. If the
	 * index is 0xFFFFFFFF, then the send buffer is not being used and all
	 * of the data was sent through other VMBus mechanisms.
	 */
	u32 send_buf_section_index;
	u32 send_buf_section_size;
पूर्ण __packed;

/*
 * This message is used by both the VSP and the VSC to complete a RNDIS message
 * to the opposite channel endpoपूर्णांक. At this poपूर्णांक, the initiator of this
 * message cannot use any resources associated with the original RNDIS packet.
 */
काष्ठा nvsp_1_message_send_rndis_packet_complete अणु
	u32 status;
पूर्ण;

जोड़ nvsp_1_message_uber अणु
	काष्ठा nvsp_1_message_send_ndis_version send_ndis_ver;

	काष्ठा nvsp_1_message_send_receive_buffer send_recv_buf;
	काष्ठा nvsp_1_message_send_receive_buffer_complete
						send_recv_buf_complete;
	काष्ठा nvsp_1_message_revoke_receive_buffer revoke_recv_buf;

	काष्ठा nvsp_1_message_send_send_buffer send_send_buf;
	काष्ठा nvsp_1_message_send_send_buffer_complete send_send_buf_complete;
	काष्ठा nvsp_1_message_revoke_send_buffer revoke_send_buf;

	काष्ठा nvsp_1_message_send_rndis_packet send_rndis_pkt;
	काष्ठा nvsp_1_message_send_rndis_packet_complete
						send_rndis_pkt_complete;
पूर्ण __packed;


/*
 * Network VSP protocol version 2 messages:
 */
काष्ठा nvsp_2_vsc_capability अणु
	जोड़ अणु
		u64 data;
		काष्ठा अणु
			u64 vmq:1;
			u64 chimney:1;
			u64 sriov:1;
			u64 ieee8021q:1;
			u64 correlation_id:1;
			u64 teaming:1;
			u64 vsubnetid:1;
			u64 rsc:1;
		पूर्ण;
	पूर्ण;
पूर्ण __packed;

काष्ठा nvsp_2_send_ndis_config अणु
	u32 mtu;
	u32 reserved;
	काष्ठा nvsp_2_vsc_capability capability;
पूर्ण __packed;

/* Allocate receive buffer */
काष्ठा nvsp_2_alloc_rxbuf अणु
	/* Allocation ID to match the allocation request and response */
	u32 alloc_id;

	/* Length of the VM shared memory receive buffer that needs to
	 * be allocated
	 */
	u32 len;
पूर्ण __packed;

/* Allocate receive buffer complete */
काष्ठा nvsp_2_alloc_rxbuf_comp अणु
	/* The NDIS_STATUS code क्रम buffer allocation */
	u32 status;

	u32 alloc_id;

	/* GPADL handle क्रम the allocated receive buffer */
	u32 gpadl_handle;

	/* Receive buffer ID */
	u64 recv_buf_id;
पूर्ण __packed;

काष्ठा nvsp_2_मुक्त_rxbuf अणु
	u64 recv_buf_id;
पूर्ण __packed;

जोड़ nvsp_2_message_uber अणु
	काष्ठा nvsp_2_send_ndis_config send_ndis_config;
	काष्ठा nvsp_2_alloc_rxbuf alloc_rxbuf;
	काष्ठा nvsp_2_alloc_rxbuf_comp alloc_rxbuf_comp;
	काष्ठा nvsp_2_मुक्त_rxbuf मुक्त_rxbuf;
पूर्ण __packed;

काष्ठा nvsp_4_send_vf_association अणु
	/* 1: allocated, serial number is valid. 0: not allocated */
	u32 allocated;

	/* Serial number of the VF to team with */
	u32 serial;
पूर्ण __packed;

क्रमागत nvsp_vm_datapath अणु
	NVSP_DATAPATH_SYNTHETIC = 0,
	NVSP_DATAPATH_VF,
	NVSP_DATAPATH_MAX
पूर्ण;

काष्ठा nvsp_4_sw_datapath अणु
	u32 active_datapath; /* active data path in VM */
पूर्ण __packed;

जोड़ nvsp_4_message_uber अणु
	काष्ठा nvsp_4_send_vf_association vf_assoc;
	काष्ठा nvsp_4_sw_datapath active_dp;
पूर्ण __packed;

क्रमागत nvsp_subchannel_operation अणु
	NVSP_SUBCHANNEL_NONE = 0,
	NVSP_SUBCHANNEL_ALLOCATE,
	NVSP_SUBCHANNEL_MAX
पूर्ण;

काष्ठा nvsp_5_subchannel_request अणु
	u32 op;
	u32 num_subchannels;
पूर्ण __packed;

काष्ठा nvsp_5_subchannel_complete अणु
	u32 status;
	u32 num_subchannels; /* Actual number of subchannels allocated */
पूर्ण __packed;

काष्ठा nvsp_5_send_indirect_table अणु
	/* The number of entries in the send indirection table */
	u32 count;

	/* The offset of the send indirection table from the beginning of
	 * काष्ठा nvsp_message.
	 * The send indirection table tells which channel to put the send
	 * traffic on. Each entry is a channel number.
	 */
	u32 offset;
पूर्ण __packed;

जोड़ nvsp_5_message_uber अणु
	काष्ठा nvsp_5_subchannel_request subchn_req;
	काष्ठा nvsp_5_subchannel_complete subchn_comp;
	काष्ठा nvsp_5_send_indirect_table send_table;
पूर्ण __packed;

क्रमागत nvsp_6_pd_api_op अणु
	PD_API_OP_CONFIG = 1,
	PD_API_OP_SW_DATAPATH, /* Switch Datapath */
	PD_API_OP_OPEN_PROVIDER,
	PD_API_OP_CLOSE_PROVIDER,
	PD_API_OP_CREATE_QUEUE,
	PD_API_OP_FLUSH_QUEUE,
	PD_API_OP_FREE_QUEUE,
	PD_API_OP_ALLOC_COM_BUF, /* Allocate Common Buffer */
	PD_API_OP_FREE_COM_BUF, /* Free Common Buffer */
	PD_API_OP_MAX
पूर्ण;

काष्ठा grp_affinity अणु
	u64 mask;
	u16 grp;
	u16 reserved[3];
पूर्ण __packed;

काष्ठा nvsp_6_pd_api_req अणु
	u32 op;

	जोड़ अणु
		/* MMIO inक्रमmation is sent from the VM to VSP */
		काष्ठा __packed अणु
			u64 mmio_pa; /* MMIO Physical Address */
			u32 mmio_len;

			/* Number of PD queues a VM can support */
			u16 num_subchn;
		पूर्ण config;

		/* Switch Datapath */
		काष्ठा __packed अणु
			/* Host Datapath Is PacketDirect */
			u8 host_dpath_is_pd;

			/* Guest PacketDirect Is Enabled */
			u8 guest_pd_enabled;
		पूर्ण sw_dpath;

		/* Open Provider*/
		काष्ठा __packed अणु
			u32 prov_id; /* Provider id */
			u32 flag;
		पूर्ण खोलो_prov;

		/* Close Provider */
		काष्ठा __packed अणु
			u32 prov_id;
		पूर्ण cls_prov;

		/* Create Queue*/
		काष्ठा __packed अणु
			u32 prov_id;
			u16 q_id;
			u16 q_size;
			u8 is_recv_q;
			u8 is_rss_q;
			u32 recv_data_len;
			काष्ठा grp_affinity affy;
		पूर्ण cr_q;

		/* Delete Queue*/
		काष्ठा __packed अणु
			u32 prov_id;
			u16 q_id;
		पूर्ण del_q;

		/* Flush Queue */
		काष्ठा __packed अणु
			u32 prov_id;
			u16 q_id;
		पूर्ण flush_q;

		/* Allocate Common Buffer */
		काष्ठा __packed अणु
			u32 len;
			u32 pf_node; /* Preferred Node */
			u16 region_id;
		पूर्ण alloc_com_buf;

		/* Free Common Buffer */
		काष्ठा __packed अणु
			u32 len;
			u64 pa; /* Physical Address */
			u32 pf_node; /* Preferred Node */
			u16 region_id;
			u8 cache_type;
		पूर्ण मुक्त_com_buf;
	पूर्ण __packed;
पूर्ण __packed;

काष्ठा nvsp_6_pd_api_comp अणु
	u32 op;
	u32 status;

	जोड़ अणु
		काष्ठा __packed अणु
			/* actual number of PD queues allocated to the VM */
			u16 num_pd_q;

			/* Num Receive Rss PD Queues */
			u8 num_rss_q;

			u8 is_supported; /* Is supported by VSP */
			u8 is_enabled; /* Is enabled by VSP */
		पूर्ण config;

		/* Open Provider */
		काष्ठा __packed अणु
			u32 prov_id;
		पूर्ण खोलो_prov;

		/* Create Queue */
		काष्ठा __packed अणु
			u32 prov_id;
			u16 q_id;
			u16 q_size;
			u32 recv_data_len;
			काष्ठा grp_affinity affy;
		पूर्ण cr_q;

		/* Allocate Common Buffer */
		काष्ठा __packed अणु
			u64 pa; /* Physical Address */
			u32 len;
			u32 pf_node; /* Preferred Node */
			u16 region_id;
			u8 cache_type;
		पूर्ण alloc_com_buf;
	पूर्ण __packed;
पूर्ण __packed;

काष्ठा nvsp_6_pd_buf अणु
	u32 region_offset;
	u16 region_id;
	u16 is_partial:1;
	u16 reserved:15;
पूर्ण __packed;

काष्ठा nvsp_6_pd_batch_msg अणु
	काष्ठा nvsp_message_header hdr;
	u16 count;
	u16 guest2host:1;
	u16 is_recv:1;
	u16 reserved:14;
	काष्ठा nvsp_6_pd_buf pd_buf[0];
पूर्ण __packed;

जोड़ nvsp_6_message_uber अणु
	काष्ठा nvsp_6_pd_api_req pd_req;
	काष्ठा nvsp_6_pd_api_comp pd_comp;
पूर्ण __packed;

जोड़ nvsp_all_messages अणु
	जोड़ nvsp_message_init_uber init_msg;
	जोड़ nvsp_1_message_uber v1_msg;
	जोड़ nvsp_2_message_uber v2_msg;
	जोड़ nvsp_4_message_uber v4_msg;
	जोड़ nvsp_5_message_uber v5_msg;
	जोड़ nvsp_6_message_uber v6_msg;
पूर्ण __packed;

/* ALL Messages */
काष्ठा nvsp_message अणु
	काष्ठा nvsp_message_header hdr;
	जोड़ nvsp_all_messages msg;
पूर्ण __packed;


#घोषणा NETVSC_MTU 65535
#घोषणा NETVSC_MTU_MIN ETH_MIN_MTU

/* Max buffer sizes allowed by a host */
#घोषणा NETVSC_RECEIVE_BUFFER_SIZE		(1024 * 1024 * 31) /* 31MB */
#घोषणा NETVSC_RECEIVE_BUFFER_SIZE_LEGACY	(1024 * 1024 * 15) /* 15MB */
#घोषणा NETVSC_RECEIVE_BUFFER_DEFAULT		(1024 * 1024 * 16)

#घोषणा NETVSC_SEND_BUFFER_SIZE			(1024 * 1024 * 15)  /* 15MB */
#घोषणा NETVSC_SEND_BUFFER_DEFAULT		(1024 * 1024)

#घोषणा NETVSC_INVALID_INDEX			-1

#घोषणा NETVSC_SEND_SECTION_SIZE		6144
#घोषणा NETVSC_RECV_SECTION_SIZE		1728

/* Default size of TX buf: 1MB, RX buf: 16MB */
#घोषणा NETVSC_MIN_TX_SECTIONS	10
#घोषणा NETVSC_DEFAULT_TX	(NETVSC_SEND_BUFFER_DEFAULT \
				 / NETVSC_SEND_SECTION_SIZE)
#घोषणा NETVSC_MIN_RX_SECTIONS	10
#घोषणा NETVSC_DEFAULT_RX	(NETVSC_RECEIVE_BUFFER_DEFAULT \
				 / NETVSC_RECV_SECTION_SIZE)

#घोषणा NETVSC_RECEIVE_BUFFER_ID		0xcafe
#घोषणा NETVSC_SEND_BUFFER_ID			0

#घोषणा NETVSC_SUPPORTED_HW_FEATURES (NETIF_F_RXCSUM | NETIF_F_IP_CSUM | \
				      NETIF_F_TSO | NETIF_F_IPV6_CSUM | \
				      NETIF_F_TSO6 | NETIF_F_LRO | \
				      NETIF_F_SG | NETIF_F_RXHASH)

#घोषणा VRSS_SEND_TAB_SIZE 16  /* must be घातer of 2 */
#घोषणा VRSS_CHANNEL_MAX 64
#घोषणा VRSS_CHANNEL_DEFAULT 8

#घोषणा RNDIS_MAX_PKT_DEFAULT 8
#घोषणा RNDIS_PKT_ALIGN_DEFAULT 8

#घोषणा NETVSC_XDP_HDRM 256

#घोषणा NETVSC_MIN_OUT_MSG_SIZE (माप(काष्ठा vmpacket_descriptor) + \
				 माप(काष्ठा nvsp_message))
#घोषणा NETVSC_MIN_IN_MSG_SIZE माप(काष्ठा vmpacket_descriptor)

/* Estimated requestor size:
 * out_ring_size/min_out_msg_size + in_ring_size/min_in_msg_size
 */
अटल अंतरभूत u32 netvsc_rqstor_size(अचिन्हित दीर्घ ringbytes)
अणु
	वापस ringbytes / NETVSC_MIN_OUT_MSG_SIZE +
		ringbytes / NETVSC_MIN_IN_MSG_SIZE;
पूर्ण

#घोषणा NETVSC_XFER_HEADER_SIZE(rng_cnt) \
		(दुरत्व(काष्ठा vmtransfer_page_packet_header, ranges) + \
		(rng_cnt) * माप(काष्ठा vmtransfer_page_range))

काष्ठा multi_send_data अणु
	काष्ठा sk_buff *skb; /* skb containing the pkt */
	काष्ठा hv_netvsc_packet *pkt; /* netvsc pkt pending */
	u32 count; /* counter of batched packets */
पूर्ण;

काष्ठा recv_comp_data अणु
	u64 tid; /* transaction id */
	u32 status;
पूर्ण;

काष्ठा multi_recv_comp अणु
	काष्ठा recv_comp_data *slots;
	u32 first;	/* first data entry */
	u32 next;	/* next entry क्रम writing */
पूर्ण;

#घोषणा NVSP_RSC_MAX 562 /* Max #RSC frags in a vmbus xfer page pkt */

काष्ठा nvsc_rsc अणु
	काष्ठा ndis_pkt_8021q_info vlan;
	काष्ठा ndis_tcp_ip_checksum_info csum_info;
	u32 hash_info;
	u8 ppi_flags; /* valid/present bits क्रम the above PPIs */
	u8 is_last; /* last RNDIS msg in a vmtransfer_page */
	u32 cnt; /* #fragments in an RSC packet */
	u32 pktlen; /* Full packet length */
	व्योम *data[NVSP_RSC_MAX];
	u32 len[NVSP_RSC_MAX];
पूर्ण;

#घोषणा NVSC_RSC_VLAN		BIT(0)	/* valid/present bit क्रम 'vlan' */
#घोषणा NVSC_RSC_CSUM_INFO	BIT(1)	/* valid/present bit क्रम 'csum_info' */
#घोषणा NVSC_RSC_HASH_INFO	BIT(2)	/* valid/present bit क्रम 'hash_info' */

काष्ठा netvsc_stats अणु
	u64 packets;
	u64 bytes;
	u64 broadcast;
	u64 multicast;
	u64 xdp_drop;
	काष्ठा u64_stats_sync syncp;
पूर्ण;

काष्ठा netvsc_ethtool_stats अणु
	अचिन्हित दीर्घ tx_scattered;
	अचिन्हित दीर्घ tx_no_memory;
	अचिन्हित दीर्घ tx_no_space;
	अचिन्हित दीर्घ tx_too_big;
	अचिन्हित दीर्घ tx_busy;
	अचिन्हित दीर्घ tx_send_full;
	अचिन्हित दीर्घ rx_comp_busy;
	अचिन्हित दीर्घ rx_no_memory;
	अचिन्हित दीर्घ stop_queue;
	अचिन्हित दीर्घ wake_queue;
	अचिन्हित दीर्घ vlan_error;
पूर्ण;

काष्ठा netvsc_ethtool_pcpu_stats अणु
	u64     rx_packets;
	u64     rx_bytes;
	u64     tx_packets;
	u64     tx_bytes;
	u64     vf_rx_packets;
	u64     vf_rx_bytes;
	u64     vf_tx_packets;
	u64     vf_tx_bytes;
पूर्ण;

काष्ठा netvsc_vf_pcpu_stats अणु
	u64     rx_packets;
	u64     rx_bytes;
	u64     tx_packets;
	u64     tx_bytes;
	काष्ठा u64_stats_sync   syncp;
	u32	tx_dropped;
पूर्ण;

काष्ठा netvsc_reconfig अणु
	काष्ठा list_head list;
	u32 event;
पूर्ण;

/* L4 hash bits क्रम dअगरferent protocols */
#घोषणा HV_TCP4_L4HASH 1
#घोषणा HV_TCP6_L4HASH 2
#घोषणा HV_UDP4_L4HASH 4
#घोषणा HV_UDP6_L4HASH 8
#घोषणा HV_DEFAULT_L4HASH (HV_TCP4_L4HASH | HV_TCP6_L4HASH | HV_UDP4_L4HASH | \
			   HV_UDP6_L4HASH)

/* The context of the netvsc device  */
काष्ठा net_device_context अणु
	/* poपूर्णांक back to our device context */
	काष्ठा hv_device *device_ctx;
	/* netvsc_device */
	काष्ठा netvsc_device __rcu *nvdev;
	/* list of netvsc net_devices */
	काष्ठा list_head list;
	/* reconfigure work */
	काष्ठा delayed_work dwork;
	/* last reconfig समय */
	अचिन्हित दीर्घ last_reconfig;
	/* reconfig events */
	काष्ठा list_head reconfig_events;
	/* list protection */
	spinlock_t lock;

	u32 msg_enable; /* debug level */

	u32 tx_checksum_mask;

	u32 tx_table[VRSS_SEND_TAB_SIZE];

	u16 rx_table[ITAB_NUM];

	/* Ethtool settings */
	u8 duplex;
	u32 speed;
	u32 l4_hash; /* L4 hash settings */
	काष्ठा netvsc_ethtool_stats eth_stats;

	/* State to manage the associated VF पूर्णांकerface. */
	काष्ठा net_device __rcu *vf_netdev;
	काष्ठा netvsc_vf_pcpu_stats __percpu *vf_stats;
	काष्ठा delayed_work vf_takeover;

	/* 1: allocated, serial number is valid. 0: not allocated */
	u32 vf_alloc;
	/* Serial number of the VF to team with */
	u32 vf_serial;

	/* Is the current data path through the VF NIC? */
	bool  data_path_is_vf;

	/* Used to temporarily save the config info across hibernation */
	काष्ठा netvsc_device_info *saved_netvsc_dev_info;
पूर्ण;

/* Per channel data */
काष्ठा netvsc_channel अणु
	काष्ठा vmbus_channel *channel;
	काष्ठा netvsc_device *net_device;
	व्योम *recv_buf; /* buffer to copy packets out from the receive buffer */
	स्थिर काष्ठा vmpacket_descriptor *desc;
	काष्ठा napi_काष्ठा napi;
	काष्ठा multi_send_data msd;
	काष्ठा multi_recv_comp mrc;
	atomic_t queue_sends;
	काष्ठा nvsc_rsc rsc;

	काष्ठा bpf_prog __rcu *bpf_prog;
	काष्ठा xdp_rxq_info xdp_rxq;

	काष्ठा netvsc_stats tx_stats;
	काष्ठा netvsc_stats rx_stats;
पूर्ण;

/* Per netvsc device */
काष्ठा netvsc_device अणु
	u32 nvsp_version;

	रुको_queue_head_t रुको_drain;
	bool destroy;
	bool tx_disable; /* अगर true, करो not wake up queue again */

	/* Receive buffer allocated by us but manages by NetVSP */
	व्योम *recv_buf;
	u32 recv_buf_size; /* allocated bytes */
	u32 recv_buf_gpadl_handle;
	u32 recv_section_cnt;
	u32 recv_section_size;
	u32 recv_completion_cnt;

	/* Send buffer allocated by us */
	व्योम *send_buf;
	u32 send_buf_gpadl_handle;
	u32 send_section_cnt;
	u32 send_section_size;
	अचिन्हित दीर्घ *send_section_map;

	/* Used क्रम NetVSP initialization protocol */
	काष्ठा completion channel_init_रुको;
	काष्ठा nvsp_message channel_init_pkt;

	काष्ठा nvsp_message revoke_packet;

	u32 max_chn;
	u32 num_chn;

	atomic_t खोलो_chn;
	काष्ठा work_काष्ठा subchan_work;
	रुको_queue_head_t subchan_खोलो;

	काष्ठा rndis_device *extension;

	u32 max_pkt; /* max number of pkt in one send, e.g. 8 */
	u32 pkt_align; /* alignment bytes, e.g. 8 */

	काष्ठा netvsc_channel chan_table[VRSS_CHANNEL_MAX];

	काष्ठा rcu_head rcu;
पूर्ण;

/* NdisInitialize message */
काष्ठा rndis_initialize_request अणु
	u32 req_id;
	u32 major_ver;
	u32 minor_ver;
	u32 max_xfer_size;
पूर्ण;

/* Response to NdisInitialize */
काष्ठा rndis_initialize_complete अणु
	u32 req_id;
	u32 status;
	u32 major_ver;
	u32 minor_ver;
	u32 dev_flags;
	u32 medium;
	u32 max_pkt_per_msg;
	u32 max_xfer_size;
	u32 pkt_alignment_factor;
	u32 af_list_offset;
	u32 af_list_size;
पूर्ण;

/* Call manager devices only: Inक्रमmation about an address family */
/* supported by the device is appended to the response to NdisInitialize. */
काष्ठा rndis_co_address_family अणु
	u32 address_family;
	u32 major_ver;
	u32 minor_ver;
पूर्ण;

/* NdisHalt message */
काष्ठा rndis_halt_request अणु
	u32 req_id;
पूर्ण;

/* NdisQueryRequest message */
काष्ठा rndis_query_request अणु
	u32 req_id;
	u32 oid;
	u32 info_buflen;
	u32 info_buf_offset;
	u32 dev_vc_handle;
पूर्ण;

/* Response to NdisQueryRequest */
काष्ठा rndis_query_complete अणु
	u32 req_id;
	u32 status;
	u32 info_buflen;
	u32 info_buf_offset;
पूर्ण;

/* NdisSetRequest message */
काष्ठा rndis_set_request अणु
	u32 req_id;
	u32 oid;
	u32 info_buflen;
	u32 info_buf_offset;
	u32 dev_vc_handle;
पूर्ण;

/* Response to NdisSetRequest */
काष्ठा rndis_set_complete अणु
	u32 req_id;
	u32 status;
पूर्ण;

/* NdisReset message */
काष्ठा rndis_reset_request अणु
	u32 reserved;
पूर्ण;

/* Response to NdisReset */
काष्ठा rndis_reset_complete अणु
	u32 status;
	u32 addressing_reset;
पूर्ण;

/* NdisMIndicateStatus message */
काष्ठा rndis_indicate_status अणु
	u32 status;
	u32 status_buflen;
	u32 status_buf_offset;
पूर्ण;

/* Diagnostic inक्रमmation passed as the status buffer in */
/* काष्ठा rndis_indicate_status messages signअगरying error conditions. */
काष्ठा rndis_diagnostic_info अणु
	u32 diag_status;
	u32 error_offset;
पूर्ण;

/* NdisKeepAlive message */
काष्ठा rndis_keepalive_request अणु
	u32 req_id;
पूर्ण;

/* Response to NdisKeepAlive */
काष्ठा rndis_keepalive_complete अणु
	u32 req_id;
	u32 status;
पूर्ण;

/*
 * Data message. All Offset fields contain byte offsets from the beginning of
 * काष्ठा rndis_packet. All Length fields are in bytes.  VcHandle is set
 * to 0 क्रम connectionless data, otherwise it contains the VC handle.
 */
काष्ठा rndis_packet अणु
	u32 data_offset;
	u32 data_len;
	u32 oob_data_offset;
	u32 oob_data_len;
	u32 num_oob_data_elements;
	u32 per_pkt_info_offset;
	u32 per_pkt_info_len;
	u32 vc_handle;
	u32 reserved;
पूर्ण;

/* Optional Out of Band data associated with a Data message. */
काष्ठा rndis_oobd अणु
	u32 size;
	u32 type;
	u32 class_info_offset;
पूर्ण;

/* Packet extension field contents associated with a Data message. */
काष्ठा rndis_per_packet_info अणु
	u32 size;
	u32 type:31;
	u32 पूर्णांकernal:1;
	u32 ppi_offset;
पूर्ण;

क्रमागत ndis_per_pkt_info_type अणु
	TCPIP_CHKSUM_PKTINFO,
	IPSEC_PKTINFO,
	TCP_LARGESEND_PKTINFO,
	CLASSIFICATION_HANDLE_PKTINFO,
	NDIS_RESERVED,
	SG_LIST_PKTINFO,
	IEEE_8021Q_INFO,
	ORIGINAL_PKTINFO,
	PACKET_CANCEL_ID,
	NBL_HASH_VALUE = PACKET_CANCEL_ID,
	ORIGINAL_NET_BUFLIST,
	CACHED_NET_BUFLIST,
	SHORT_PKT_PADINFO,
	MAX_PER_PKT_INFO
पूर्ण;

क्रमागत rndis_per_pkt_info_पूर्णांकeral_type अणु
	RNDIS_PKTINFO_ID = 1,
	/* Add more members here */

	RNDIS_PKTINFO_MAX
पूर्ण;

#घोषणा RNDIS_PKTINFO_SUBALLOC BIT(0)
#घोषणा RNDIS_PKTINFO_1ST_FRAG BIT(1)
#घोषणा RNDIS_PKTINFO_LAST_FRAG BIT(2)

#घोषणा RNDIS_PKTINFO_ID_V1 1

काष्ठा rndis_pktinfo_id अणु
	u8 ver;
	u8 flag;
	u16 pkt_id;
पूर्ण;

काष्ठा ndis_object_header अणु
	u8 type;
	u8 revision;
	u16 size;
पूर्ण;

#घोषणा NDIS_OBJECT_TYPE_DEFAULT	0x80
#घोषणा NDIS_OFFLOAD_PARAMETERS_REVISION_3 3
#घोषणा NDIS_OFFLOAD_PARAMETERS_REVISION_2 2
#घोषणा NDIS_OFFLOAD_PARAMETERS_REVISION_1 1

#घोषणा NDIS_OFFLOAD_PARAMETERS_NO_CHANGE 0
#घोषणा NDIS_OFFLOAD_PARAMETERS_LSOV2_DISABLED 1
#घोषणा NDIS_OFFLOAD_PARAMETERS_LSOV2_ENABLED  2
#घोषणा NDIS_OFFLOAD_PARAMETERS_LSOV1_ENABLED  2
#घोषणा NDIS_OFFLOAD_PARAMETERS_RSC_DISABLED 1
#घोषणा NDIS_OFFLOAD_PARAMETERS_RSC_ENABLED 2
#घोषणा NDIS_OFFLOAD_PARAMETERS_TX_RX_DISABLED 1
#घोषणा NDIS_OFFLOAD_PARAMETERS_TX_ENABLED_RX_DISABLED 2
#घोषणा NDIS_OFFLOAD_PARAMETERS_RX_ENABLED_TX_DISABLED 3
#घोषणा NDIS_OFFLOAD_PARAMETERS_TX_RX_ENABLED 4

#घोषणा NDIS_TCP_LARGE_SEND_OFFLOAD_V2_TYPE	1
#घोषणा NDIS_TCP_LARGE_SEND_OFFLOAD_IPV4	0
#घोषणा NDIS_TCP_LARGE_SEND_OFFLOAD_IPV6	1

#घोषणा VERSION_4_OFFLOAD_SIZE			22
/*
 * New offload OIDs क्रम NDIS 6
 */
#घोषणा OID_TCP_OFFLOAD_CURRENT_CONFIG 0xFC01020B /* query only */
#घोषणा OID_TCP_OFFLOAD_PARAMETERS 0xFC01020C		/* set only */
#घोषणा OID_TCP_OFFLOAD_HARDWARE_CAPABILITIES 0xFC01020D/* query only */
#घोषणा OID_TCP_CONNECTION_OFFLOAD_CURRENT_CONFIG 0xFC01020E /* query only */
#घोषणा OID_TCP_CONNECTION_OFFLOAD_HARDWARE_CAPABILITIES 0xFC01020F /* query */
#घोषणा OID_OFFLOAD_ENCAPSULATION 0x0101010A /* set/query */

/*
 * OID_TCP_OFFLOAD_HARDWARE_CAPABILITIES
 * ndis_type: NDIS_OBJTYPE_OFFLOAD
 */

#घोषणा	NDIS_OFFLOAD_ENCAP_NONE		0x0000
#घोषणा	NDIS_OFFLOAD_ENCAP_शून्य		0x0001
#घोषणा	NDIS_OFFLOAD_ENCAP_8023		0x0002
#घोषणा	NDIS_OFFLOAD_ENCAP_8023PQ	0x0004
#घोषणा	NDIS_OFFLOAD_ENCAP_8023PQ_OOB	0x0008
#घोषणा	NDIS_OFFLOAD_ENCAP_RFC1483	0x0010

काष्ठा ndis_csum_offload अणु
	u32	ip4_txenc;
	u32	ip4_txcsum;
#घोषणा	NDIS_TXCSUM_CAP_IP4OPT		0x001
#घोषणा	NDIS_TXCSUM_CAP_TCP4OPT		0x004
#घोषणा	NDIS_TXCSUM_CAP_TCP4		0x010
#घोषणा	NDIS_TXCSUM_CAP_UDP4		0x040
#घोषणा	NDIS_TXCSUM_CAP_IP4		0x100

#घोषणा NDIS_TXCSUM_ALL_TCP4	(NDIS_TXCSUM_CAP_TCP4 | NDIS_TXCSUM_CAP_TCP4OPT)

	u32	ip4_rxenc;
	u32	ip4_rxcsum;
#घोषणा	NDIS_RXCSUM_CAP_IP4OPT		0x001
#घोषणा	NDIS_RXCSUM_CAP_TCP4OPT		0x004
#घोषणा	NDIS_RXCSUM_CAP_TCP4		0x010
#घोषणा	NDIS_RXCSUM_CAP_UDP4		0x040
#घोषणा	NDIS_RXCSUM_CAP_IP4		0x100
	u32	ip6_txenc;
	u32	ip6_txcsum;
#घोषणा	NDIS_TXCSUM_CAP_IP6EXT		0x001
#घोषणा	NDIS_TXCSUM_CAP_TCP6OPT		0x004
#घोषणा	NDIS_TXCSUM_CAP_TCP6		0x010
#घोषणा	NDIS_TXCSUM_CAP_UDP6		0x040
	u32	ip6_rxenc;
	u32	ip6_rxcsum;
#घोषणा	NDIS_RXCSUM_CAP_IP6EXT		0x001
#घोषणा	NDIS_RXCSUM_CAP_TCP6OPT		0x004
#घोषणा	NDIS_RXCSUM_CAP_TCP6		0x010
#घोषणा	NDIS_RXCSUM_CAP_UDP6		0x040

#घोषणा NDIS_TXCSUM_ALL_TCP6	(NDIS_TXCSUM_CAP_TCP6 |		\
				 NDIS_TXCSUM_CAP_TCP6OPT |	\
				 NDIS_TXCSUM_CAP_IP6EXT)
पूर्ण;

काष्ठा ndis_lsov1_offload अणु
	u32	encap;
	u32	maxsize;
	u32	minsegs;
	u32	opts;
पूर्ण;

काष्ठा ndis_ipsecv1_offload अणु
	u32	encap;
	u32	ah_esp;
	u32	xport_tun;
	u32	ip4_opts;
	u32	flags;
	u32	ip4_ah;
	u32	ip4_esp;
पूर्ण;

काष्ठा ndis_lsov2_offload अणु
	u32	ip4_encap;
	u32	ip4_maxsz;
	u32	ip4_minsg;
	u32	ip6_encap;
	u32	ip6_maxsz;
	u32	ip6_minsg;
	u32	ip6_opts;
#घोषणा	NDIS_LSOV2_CAP_IP6EXT		0x001
#घोषणा	NDIS_LSOV2_CAP_TCP6OPT		0x004

#घोषणा NDIS_LSOV2_CAP_IP6		(NDIS_LSOV2_CAP_IP6EXT | \
					 NDIS_LSOV2_CAP_TCP6OPT)
पूर्ण;

काष्ठा ndis_ipsecv2_offload अणु
	u32	encap;
	u8	ip6;
	u8	ip4opt;
	u8	ip6ext;
	u8	ah;
	u8	esp;
	u8	ah_esp;
	u8	xport;
	u8	tun;
	u8	xport_tun;
	u8	lso;
	u8	extseq;
	u32	udp_esp;
	u32	auth;
	u32	crypto;
	u32	sa_caps;
पूर्ण;

काष्ठा ndis_rsc_offload अणु
	u8	ip4;
	u8	ip6;
पूर्ण;

काष्ठा ndis_encap_offload अणु
	u32	flags;
	u32	maxhdr;
पूर्ण;

काष्ठा ndis_offload अणु
	काष्ठा ndis_object_header	header;
	काष्ठा ndis_csum_offload	csum;
	काष्ठा ndis_lsov1_offload	lsov1;
	काष्ठा ndis_ipsecv1_offload	ipsecv1;
	काष्ठा ndis_lsov2_offload	lsov2;
	u32				flags;
	/* NDIS >= 6.1 */
	काष्ठा ndis_ipsecv2_offload	ipsecv2;
	/* NDIS >= 6.30 */
	काष्ठा ndis_rsc_offload		rsc;
	काष्ठा ndis_encap_offload	encap_gre;
पूर्ण;

#घोषणा	NDIS_OFFLOAD_SIZE		माप(काष्ठा ndis_offload)
#घोषणा	NDIS_OFFLOAD_SIZE_6_0		दुरत्व(काष्ठा ndis_offload, ipsecv2)
#घोषणा	NDIS_OFFLOAD_SIZE_6_1		दुरत्व(काष्ठा ndis_offload, rsc)

काष्ठा ndis_offload_params अणु
	काष्ठा ndis_object_header header;
	u8 ip_v4_csum;
	u8 tcp_ip_v4_csum;
	u8 udp_ip_v4_csum;
	u8 tcp_ip_v6_csum;
	u8 udp_ip_v6_csum;
	u8 lso_v1;
	u8 ip_sec_v1;
	u8 lso_v2_ipv4;
	u8 lso_v2_ipv6;
	u8 tcp_connection_ip_v4;
	u8 tcp_connection_ip_v6;
	u32 flags;
	u8 ip_sec_v2;
	u8 ip_sec_v2_ip_v4;
	काष्ठा अणु
		u8 rsc_ip_v4;
		u8 rsc_ip_v6;
	पूर्ण;
	काष्ठा अणु
		u8 encapsulated_packet_task_offload;
		u8 encapsulation_types;
	पूर्ण;
पूर्ण;

काष्ठा ndis_tcp_lso_info अणु
	जोड़ अणु
		काष्ठा अणु
			u32 unused:30;
			u32 type:1;
			u32 reserved2:1;
		पूर्ण transmit;
		काष्ठा अणु
			u32 mss:20;
			u32 tcp_header_offset:10;
			u32 type:1;
			u32 reserved2:1;
		पूर्ण lso_v1_transmit;
		काष्ठा अणु
			u32 tcp_payload:30;
			u32 type:1;
			u32 reserved2:1;
		पूर्ण lso_v1_transmit_complete;
		काष्ठा अणु
			u32 mss:20;
			u32 tcp_header_offset:10;
			u32 type:1;
			u32 ip_version:1;
		पूर्ण lso_v2_transmit;
		काष्ठा अणु
			u32 reserved:30;
			u32 type:1;
			u32 reserved2:1;
		पूर्ण lso_v2_transmit_complete;
		u32  value;
	पूर्ण;
पूर्ण;

#घोषणा NDIS_VLAN_PPI_SIZE (माप(काष्ठा rndis_per_packet_info) + \
		माप(काष्ठा ndis_pkt_8021q_info))

#घोषणा NDIS_CSUM_PPI_SIZE (माप(काष्ठा rndis_per_packet_info) + \
		माप(काष्ठा ndis_tcp_ip_checksum_info))

#घोषणा NDIS_LSO_PPI_SIZE (माप(काष्ठा rndis_per_packet_info) + \
		माप(काष्ठा ndis_tcp_lso_info))

#घोषणा NDIS_HASH_PPI_SIZE (माप(काष्ठा rndis_per_packet_info) + \
		माप(u32))

/* Total size of all PPI data */
#घोषणा NDIS_ALL_PPI_SIZE (NDIS_VLAN_PPI_SIZE + NDIS_CSUM_PPI_SIZE + \
			   NDIS_LSO_PPI_SIZE + NDIS_HASH_PPI_SIZE)

/* Format of Inक्रमmation buffer passed in a SetRequest क्रम the OID */
/* OID_GEN_RNDIS_CONFIG_PARAMETER. */
काष्ठा rndis_config_parameter_info अणु
	u32 parameter_name_offset;
	u32 parameter_name_length;
	u32 parameter_type;
	u32 parameter_value_offset;
	u32 parameter_value_length;
पूर्ण;

/* Values क्रम ParameterType in काष्ठा rndis_config_parameter_info */
#घोषणा RNDIS_CONFIG_PARAM_TYPE_INTEGER     0
#घोषणा RNDIS_CONFIG_PARAM_TYPE_STRING      2

/* CONDIS Miniport messages क्रम connection oriented devices */
/* that करो not implement a call manager. */

/* CoNdisMiniportCreateVc message */
काष्ठा rcondis_mp_create_vc अणु
	u32 req_id;
	u32 ndis_vc_handle;
पूर्ण;

/* Response to CoNdisMiniportCreateVc */
काष्ठा rcondis_mp_create_vc_complete अणु
	u32 req_id;
	u32 dev_vc_handle;
	u32 status;
पूर्ण;

/* CoNdisMiniportDeleteVc message */
काष्ठा rcondis_mp_delete_vc अणु
	u32 req_id;
	u32 dev_vc_handle;
पूर्ण;

/* Response to CoNdisMiniportDeleteVc */
काष्ठा rcondis_mp_delete_vc_complete अणु
	u32 req_id;
	u32 status;
पूर्ण;

/* CoNdisMiniportQueryRequest message */
काष्ठा rcondis_mp_query_request अणु
	u32 req_id;
	u32 request_type;
	u32 oid;
	u32 dev_vc_handle;
	u32 info_buflen;
	u32 info_buf_offset;
पूर्ण;

/* CoNdisMiniportSetRequest message */
काष्ठा rcondis_mp_set_request अणु
	u32 req_id;
	u32 request_type;
	u32 oid;
	u32 dev_vc_handle;
	u32 info_buflen;
	u32 info_buf_offset;
पूर्ण;

/* CoNdisIndicateStatus message */
काष्ठा rcondis_indicate_status अणु
	u32 ndis_vc_handle;
	u32 status;
	u32 status_buflen;
	u32 status_buf_offset;
पूर्ण;

/* CONDIS Call/VC parameters */
काष्ठा rcondis_specअगरic_parameters अणु
	u32 parameter_type;
	u32 parameter_length;
	u32 parameter_lffset;
पूर्ण;

काष्ठा rcondis_media_parameters अणु
	u32 flags;
	u32 reserved1;
	u32 reserved2;
	काष्ठा rcondis_specअगरic_parameters media_specअगरic;
पूर्ण;

काष्ठा rndis_flowspec अणु
	u32 token_rate;
	u32 token_bucket_size;
	u32 peak_bandwidth;
	u32 latency;
	u32 delay_variation;
	u32 service_type;
	u32 max_sdu_size;
	u32 minimum_policed_size;
पूर्ण;

काष्ठा rcondis_call_manager_parameters अणु
	काष्ठा rndis_flowspec transmit;
	काष्ठा rndis_flowspec receive;
	काष्ठा rcondis_specअगरic_parameters call_mgr_specअगरic;
पूर्ण;

/* CoNdisMiniportActivateVc message */
काष्ठा rcondis_mp_activate_vc_request अणु
	u32 req_id;
	u32 flags;
	u32 dev_vc_handle;
	u32 media_params_offset;
	u32 media_params_length;
	u32 call_mgr_params_offset;
	u32 call_mgr_params_length;
पूर्ण;

/* Response to CoNdisMiniportActivateVc */
काष्ठा rcondis_mp_activate_vc_complete अणु
	u32 req_id;
	u32 status;
पूर्ण;

/* CoNdisMiniportDeactivateVc message */
काष्ठा rcondis_mp_deactivate_vc_request अणु
	u32 req_id;
	u32 flags;
	u32 dev_vc_handle;
पूर्ण;

/* Response to CoNdisMiniportDeactivateVc */
काष्ठा rcondis_mp_deactivate_vc_complete अणु
	u32 req_id;
	u32 status;
पूर्ण;


/* जोड़ with all of the RNDIS messages */
जोड़ rndis_message_container अणु
	काष्ठा rndis_packet pkt;
	काष्ठा rndis_initialize_request init_req;
	काष्ठा rndis_halt_request halt_req;
	काष्ठा rndis_query_request query_req;
	काष्ठा rndis_set_request set_req;
	काष्ठा rndis_reset_request reset_req;
	काष्ठा rndis_keepalive_request keep_alive_req;
	काष्ठा rndis_indicate_status indicate_status;
	काष्ठा rndis_initialize_complete init_complete;
	काष्ठा rndis_query_complete query_complete;
	काष्ठा rndis_set_complete set_complete;
	काष्ठा rndis_reset_complete reset_complete;
	काष्ठा rndis_keepalive_complete keep_alive_complete;
	काष्ठा rcondis_mp_create_vc co_miniport_create_vc;
	काष्ठा rcondis_mp_delete_vc co_miniport_delete_vc;
	काष्ठा rcondis_indicate_status co_indicate_status;
	काष्ठा rcondis_mp_activate_vc_request co_miniport_activate_vc;
	काष्ठा rcondis_mp_deactivate_vc_request co_miniport_deactivate_vc;
	काष्ठा rcondis_mp_create_vc_complete co_miniport_create_vc_complete;
	काष्ठा rcondis_mp_delete_vc_complete co_miniport_delete_vc_complete;
	काष्ठा rcondis_mp_activate_vc_complete co_miniport_activate_vc_complete;
	काष्ठा rcondis_mp_deactivate_vc_complete
		co_miniport_deactivate_vc_complete;
पूर्ण;

/* Remote NDIS message क्रमmat */
काष्ठा rndis_message अणु
	u32 ndis_msg_type;

	/* Total length of this message, from the beginning */
	/* of the काष्ठा rndis_message, in bytes. */
	u32 msg_len;

	/* Actual message */
	जोड़ rndis_message_container msg;
पूर्ण;


/* Handy macros */

/* get the size of an RNDIS message. Pass in the message type, */
/* काष्ठा rndis_set_request, काष्ठा rndis_packet क्रम example */
#घोषणा RNDIS_MESSAGE_SIZE(msg)				\
	(माप(msg) + (माप(काष्ठा rndis_message) -	\
	 माप(जोड़ rndis_message_container)))

#घोषणा RNDIS_HEADER_SIZE	(माप(काष्ठा rndis_message) - \
				 माप(जोड़ rndis_message_container))

#घोषणा RNDIS_AND_PPI_SIZE (माप(काष्ठा rndis_message) + NDIS_ALL_PPI_SIZE)

#घोषणा NDIS_PACKET_TYPE_सूचीECTED	0x00000001
#घोषणा NDIS_PACKET_TYPE_MULTICAST	0x00000002
#घोषणा NDIS_PACKET_TYPE_ALL_MULTICAST	0x00000004
#घोषणा NDIS_PACKET_TYPE_BROADCAST	0x00000008
#घोषणा NDIS_PACKET_TYPE_SOURCE_ROUTING	0x00000010
#घोषणा NDIS_PACKET_TYPE_PROMISCUOUS	0x00000020
#घोषणा NDIS_PACKET_TYPE_SMT		0x00000040
#घोषणा NDIS_PACKET_TYPE_ALL_LOCAL	0x00000080
#घोषणा NDIS_PACKET_TYPE_GROUP		0x00000100
#घोषणा NDIS_PACKET_TYPE_ALL_FUNCTIONAL	0x00000200
#घोषणा NDIS_PACKET_TYPE_FUNCTIONAL	0x00000400
#घोषणा NDIS_PACKET_TYPE_MAC_FRAME	0x00000800

#घोषणा TRANSPORT_INFO_NOT_IP   0
#घोषणा TRANSPORT_INFO_IPV4_TCP 0x01
#घोषणा TRANSPORT_INFO_IPV4_UDP 0x02
#घोषणा TRANSPORT_INFO_IPV6_TCP 0x10
#घोषणा TRANSPORT_INFO_IPV6_UDP 0x20

#घोषणा RETRY_US_LO	5000
#घोषणा RETRY_US_HI	10000
#घोषणा RETRY_MAX	2000	/* >10 sec */

#पूर्ण_अगर /* _HYPERV_NET_H */
