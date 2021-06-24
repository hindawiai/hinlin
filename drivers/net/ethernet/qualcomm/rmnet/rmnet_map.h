<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2013-2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _RMNET_MAP_H_
#घोषणा _RMNET_MAP_H_
#समावेश <linux/अगर_rmnet.h>

काष्ठा rmnet_map_control_command अणु
	u8  command_name;
	u8  cmd_type:2;
	u8  reserved:6;
	u16 reserved2;
	u32 transaction_id;
	जोड़ अणु
		काष्ठा अणु
			u16 ip_family:2;
			u16 reserved:14;
			__be16 flow_control_seq_num;
			__be32 qos_id;
		पूर्ण flow_control;
		u8 data[0];
	पूर्ण;
पूर्ण  __aligned(1);

क्रमागत rmnet_map_commands अणु
	RMNET_MAP_COMMAND_NONE,
	RMNET_MAP_COMMAND_FLOW_DISABLE,
	RMNET_MAP_COMMAND_FLOW_ENABLE,
	/* These should always be the last 2 elements */
	RMNET_MAP_COMMAND_UNKNOWN,
	RMNET_MAP_COMMAND_ENUM_LENGTH
पूर्ण;

#घोषणा RMNET_MAP_COMMAND_REQUEST     0
#घोषणा RMNET_MAP_COMMAND_ACK         1
#घोषणा RMNET_MAP_COMMAND_UNSUPPORTED 2
#घोषणा RMNET_MAP_COMMAND_INVALID     3

#घोषणा RMNET_MAP_NO_PAD_BYTES        0
#घोषणा RMNET_MAP_ADD_PAD_BYTES       1

काष्ठा sk_buff *rmnet_map_deaggregate(काष्ठा sk_buff *skb,
				      काष्ठा rmnet_port *port);
काष्ठा rmnet_map_header *rmnet_map_add_map_header(काष्ठा sk_buff *skb,
						  पूर्णांक hdrlen, पूर्णांक pad);
व्योम rmnet_map_command(काष्ठा sk_buff *skb, काष्ठा rmnet_port *port);
पूर्णांक rmnet_map_checksum_करोwnlink_packet(काष्ठा sk_buff *skb, u16 len);
व्योम rmnet_map_checksum_uplink_packet(काष्ठा sk_buff *skb,
				      काष्ठा net_device *orig_dev);

#पूर्ण_अगर /* _RMNET_MAP_H_ */
