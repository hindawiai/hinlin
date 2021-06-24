<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
  BNEP protocol definition क्रम Linux Bluetooth stack (BlueZ).
  Copyright (C) 2002 Maxim Krasnyansky <maxk@qualcomm.com>

*/

#अगर_अघोषित _BNEP_H
#घोषणा _BNEP_H

#समावेश <linux/types.h>
#समावेश <linux/crc32.h>
#समावेश <net/bluetooth/bluetooth.h>

/* Limits */
#घोषणा BNEP_MAX_PROTO_FILTERS		5
#घोषणा BNEP_MAX_MULTICAST_FILTERS	20

/* UUIDs */
#घोषणा BNEP_BASE_UUID	0x0000000000001000800000805F9B34FB
#घोषणा BNEP_UUID16	0x02
#घोषणा BNEP_UUID32	0x04
#घोषणा BNEP_UUID128	0x16

#घोषणा BNEP_SVC_PANU	0x1115
#घोषणा BNEP_SVC_NAP	0x1116
#घोषणा BNEP_SVC_GN	0x1117

/* Packet types */
#घोषणा BNEP_GENERAL			0x00
#घोषणा BNEP_CONTROL			0x01
#घोषणा BNEP_COMPRESSED			0x02
#घोषणा BNEP_COMPRESSED_SRC_ONLY	0x03
#घोषणा BNEP_COMPRESSED_DST_ONLY	0x04

/* Control types */
#घोषणा BNEP_CMD_NOT_UNDERSTOOD		0x00
#घोषणा BNEP_SETUP_CONN_REQ		0x01
#घोषणा BNEP_SETUP_CONN_RSP		0x02
#घोषणा BNEP_FILTER_NET_TYPE_SET	0x03
#घोषणा BNEP_FILTER_NET_TYPE_RSP	0x04
#घोषणा BNEP_FILTER_MULTI_ADDR_SET	0x05
#घोषणा BNEP_FILTER_MULTI_ADDR_RSP	0x06

/* Extension types */
#घोषणा BNEP_EXT_CONTROL 0x00

/* Response messages */
#घोषणा BNEP_SUCCESS 0x00

#घोषणा BNEP_CONN_INVALID_DST 0x01
#घोषणा BNEP_CONN_INVALID_SRC 0x02
#घोषणा BNEP_CONN_INVALID_SVC 0x03
#घोषणा BNEP_CONN_NOT_ALLOWED 0x04

#घोषणा BNEP_FILTER_UNSUPPORTED_REQ	0x01
#घोषणा BNEP_FILTER_INVALID_RANGE	0x02
#घोषणा BNEP_FILTER_INVALID_MCADDR	0x02
#घोषणा BNEP_FILTER_LIMIT_REACHED	0x03
#घोषणा BNEP_FILTER_DENIED_SECURITY	0x04

/* L2CAP settings */
#घोषणा BNEP_MTU	1691
#घोषणा BNEP_PSM	0x0f
#घोषणा BNEP_FLUSH_TO	0xffff
#घोषणा BNEP_CONNECT_TO	15
#घोषणा BNEP_FILTER_TO	15

/* Headers */
#घोषणा BNEP_TYPE_MASK	0x7f
#घोषणा BNEP_EXT_HEADER	0x80

काष्ठा bnep_setup_conn_req अणु
	__u8 type;
	__u8 ctrl;
	__u8 uuid_size;
	__u8 service[];
पूर्ण __packed;

काष्ठा bnep_set_filter_req अणु
	__u8 type;
	__u8 ctrl;
	__be16 len;
	__u8 list[];
पूर्ण __packed;

काष्ठा bnep_control_rsp अणु
	__u8 type;
	__u8 ctrl;
	__be16 resp;
पूर्ण __packed;

काष्ठा bnep_ext_hdr अणु
	__u8 type;
	__u8 len;
	__u8 data[];
पूर्ण __packed;

/* BNEP ioctl defines */
#घोषणा BNEPCONNADD	_IOW('B', 200, पूर्णांक)
#घोषणा BNEPCONNDEL	_IOW('B', 201, पूर्णांक)
#घोषणा BNEPGETCONNLIST	_IOR('B', 210, पूर्णांक)
#घोषणा BNEPGETCONNINFO	_IOR('B', 211, पूर्णांक)
#घोषणा BNEPGETSUPPFEAT	_IOR('B', 212, पूर्णांक)

#घोषणा BNEP_SETUP_RESPONSE	0
#घोषणा BNEP_SETUP_RSP_SENT	10

काष्ठा bnep_connadd_req अणु
	पूर्णांक   sock;		/* Connected socket */
	__u32 flags;
	__u16 role;
	अक्षर  device[16];	/* Name of the Ethernet device */
पूर्ण;

काष्ठा bnep_conndel_req अणु
	__u32 flags;
	__u8  dst[ETH_ALEN];
पूर्ण;

काष्ठा bnep_conninfo अणु
	__u32 flags;
	__u16 role;
	__u16 state;
	__u8  dst[ETH_ALEN];
	अक्षर  device[16];
पूर्ण;

काष्ठा bnep_connlist_req अणु
	__u32  cnum;
	काष्ठा bnep_conninfo __user *ci;
पूर्ण;

काष्ठा bnep_proto_filter अणु
	__u16 start;
	__u16 end;
पूर्ण;

पूर्णांक bnep_add_connection(काष्ठा bnep_connadd_req *req, काष्ठा socket *sock);
पूर्णांक bnep_del_connection(काष्ठा bnep_conndel_req *req);
पूर्णांक bnep_get_connlist(काष्ठा bnep_connlist_req *req);
पूर्णांक bnep_get_conninfo(काष्ठा bnep_conninfo *ci);

/* BNEP sessions */
काष्ठा bnep_session अणु
	काष्ठा list_head list;

	अचिन्हित पूर्णांक  role;
	अचिन्हित दीर्घ state;
	अचिन्हित दीर्घ flags;
	atomic_t      terminate;
	काष्ठा task_काष्ठा *task;

	काष्ठा ethhdr eh;
	काष्ठा msghdr msg;

	काष्ठा bnep_proto_filter proto_filter[BNEP_MAX_PROTO_FILTERS];
	अचिन्हित दीर्घ दीर्घ mc_filter;

	काष्ठा socket    *sock;
	काष्ठा net_device *dev;
पूर्ण;

व्योम bnep_net_setup(काष्ठा net_device *dev);
पूर्णांक bnep_sock_init(व्योम);
व्योम bnep_sock_cleanup(व्योम);

अटल अंतरभूत पूर्णांक bnep_mc_hash(__u8 *addr)
अणु
	वापस crc32_be(~0, addr, ETH_ALEN) >> 26;
पूर्ण

#पूर्ण_अगर
