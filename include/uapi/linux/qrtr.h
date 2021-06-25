<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_QRTR_H
#घोषणा _LINUX_QRTR_H

#समावेश <linux/socket.h>
#समावेश <linux/types.h>

#घोषणा QRTR_NODE_BCAST	0xffffffffu
#घोषणा QRTR_PORT_CTRL	0xfffffffeu

काष्ठा sockaddr_qrtr अणु
	__kernel_sa_family_t sq_family;
	__u32 sq_node;
	__u32 sq_port;
पूर्ण;

क्रमागत qrtr_pkt_type अणु
	QRTR_TYPE_DATA		= 1,
	QRTR_TYPE_HELLO		= 2,
	QRTR_TYPE_BYE		= 3,
	QRTR_TYPE_NEW_SERVER	= 4,
	QRTR_TYPE_DEL_SERVER	= 5,
	QRTR_TYPE_DEL_CLIENT	= 6,
	QRTR_TYPE_RESUME_TX	= 7,
	QRTR_TYPE_EXIT          = 8,
	QRTR_TYPE_PING          = 9,
	QRTR_TYPE_NEW_LOOKUP	= 10,
	QRTR_TYPE_DEL_LOOKUP	= 11,
पूर्ण;

काष्ठा qrtr_ctrl_pkt अणु
	__le32 cmd;

	जोड़ अणु
		काष्ठा अणु
			__le32 service;
			__le32 instance;
			__le32 node;
			__le32 port;
		पूर्ण server;

		काष्ठा अणु
			__le32 node;
			__le32 port;
		पूर्ण client;
	पूर्ण;
पूर्ण __packed;

#पूर्ण_अगर /* _LINUX_QRTR_H */
