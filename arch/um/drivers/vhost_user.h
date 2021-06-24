<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Vhost-user protocol */

#अगर_अघोषित __VHOST_USER_H__
#घोषणा __VHOST_USER_H__

/* Message flags */
#घोषणा VHOST_USER_FLAG_REPLY		BIT(2)
#घोषणा VHOST_USER_FLAG_NEED_REPLY	BIT(3)
/* Feature bits */
#घोषणा VHOST_USER_F_PROTOCOL_FEATURES	30
/* Protocol feature bits */
#घोषणा VHOST_USER_PROTOCOL_F_REPLY_ACK			3
#घोषणा VHOST_USER_PROTOCOL_F_SLAVE_REQ			5
#घोषणा VHOST_USER_PROTOCOL_F_CONFIG			9
#घोषणा VHOST_USER_PROTOCOL_F_INBAND_NOTIFICATIONS	14
/* Vring state index masks */
#घोषणा VHOST_USER_VRING_INDEX_MASK	0xff
#घोषणा VHOST_USER_VRING_POLL_MASK	BIT(8)

/* Supported version */
#घोषणा VHOST_USER_VERSION		1
/* Supported transport features */
#घोषणा VHOST_USER_SUPPORTED_F		BIT_ULL(VHOST_USER_F_PROTOCOL_FEATURES)
/* Supported protocol features */
#घोषणा VHOST_USER_SUPPORTED_PROTOCOL_F	(BIT_ULL(VHOST_USER_PROTOCOL_F_REPLY_ACK) | \
					 BIT_ULL(VHOST_USER_PROTOCOL_F_SLAVE_REQ) | \
					 BIT_ULL(VHOST_USER_PROTOCOL_F_CONFIG) | \
					 BIT_ULL(VHOST_USER_PROTOCOL_F_INBAND_NOTIFICATIONS))

क्रमागत vhost_user_request अणु
	VHOST_USER_GET_FEATURES = 1,
	VHOST_USER_SET_FEATURES = 2,
	VHOST_USER_SET_OWNER = 3,
	VHOST_USER_RESET_OWNER = 4,
	VHOST_USER_SET_MEM_TABLE = 5,
	VHOST_USER_SET_LOG_BASE = 6,
	VHOST_USER_SET_LOG_FD = 7,
	VHOST_USER_SET_VRING_NUM = 8,
	VHOST_USER_SET_VRING_ADDR = 9,
	VHOST_USER_SET_VRING_BASE = 10,
	VHOST_USER_GET_VRING_BASE = 11,
	VHOST_USER_SET_VRING_KICK = 12,
	VHOST_USER_SET_VRING_CALL = 13,
	VHOST_USER_SET_VRING_ERR = 14,
	VHOST_USER_GET_PROTOCOL_FEATURES = 15,
	VHOST_USER_SET_PROTOCOL_FEATURES = 16,
	VHOST_USER_GET_QUEUE_NUM = 17,
	VHOST_USER_SET_VRING_ENABLE = 18,
	VHOST_USER_SEND_RARP = 19,
	VHOST_USER_NET_SEND_MTU = 20,
	VHOST_USER_SET_SLAVE_REQ_FD = 21,
	VHOST_USER_IOTLB_MSG = 22,
	VHOST_USER_SET_VRING_ENDIAN = 23,
	VHOST_USER_GET_CONFIG = 24,
	VHOST_USER_SET_CONFIG = 25,
	VHOST_USER_VRING_KICK = 35,
पूर्ण;

क्रमागत vhost_user_slave_request अणु
	VHOST_USER_SLAVE_IOTLB_MSG = 1,
	VHOST_USER_SLAVE_CONFIG_CHANGE_MSG = 2,
	VHOST_USER_SLAVE_VRING_HOST_NOTIFIER_MSG = 3,
	VHOST_USER_SLAVE_VRING_CALL = 4,
पूर्ण;

काष्ठा vhost_user_header अणु
	/*
	 * Use क्रमागत vhost_user_request क्रम outgoing messages,
	 * uses क्रमागत vhost_user_slave_request क्रम incoming ones.
	 */
	u32 request;
	u32 flags;
	u32 size;
पूर्ण __packed;

काष्ठा vhost_user_config अणु
	u32 offset;
	u32 size;
	u32 flags;
	u8 payload[]; /* Variable length */
पूर्ण __packed;

काष्ठा vhost_user_vring_state अणु
	u32 index;
	u32 num;
पूर्ण __packed;

काष्ठा vhost_user_vring_addr अणु
	u32 index;
	u32 flags;
	u64 desc, used, avail, log;
पूर्ण __packed;

काष्ठा vhost_user_mem_region अणु
	u64 guest_addr;
	u64 size;
	u64 user_addr;
	u64 mmap_offset;
पूर्ण __packed;

काष्ठा vhost_user_mem_regions अणु
	u32 num;
	u32 padding;
	काष्ठा vhost_user_mem_region regions[2]; /* Currently supporting 2 */
पूर्ण __packed;

जोड़ vhost_user_payload अणु
	u64 पूर्णांकeger;
	काष्ठा vhost_user_config config;
	काष्ठा vhost_user_vring_state vring_state;
	काष्ठा vhost_user_vring_addr vring_addr;
	काष्ठा vhost_user_mem_regions mem_regions;
पूर्ण;

काष्ठा vhost_user_msg अणु
	काष्ठा vhost_user_header header;
	जोड़ vhost_user_payload payload;
पूर्ण __packed;

#पूर्ण_अगर
