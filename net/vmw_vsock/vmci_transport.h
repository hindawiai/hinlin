<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * VMware vSockets Driver
 *
 * Copyright (C) 2013 VMware, Inc. All rights reserved.
 */

#अगर_अघोषित _VMCI_TRANSPORT_H_
#घोषणा _VMCI_TRANSPORT_H_

#समावेश <linux/vmw_vmci_defs.h>
#समावेश <linux/vmw_vmci_api.h>

#समावेश <net/vsock_addr.h>
#समावेश <net/af_vsock.h>

/* If the packet क्रमmat changes in a release then this should change too. */
#घोषणा VMCI_TRANSPORT_PACKET_VERSION 1

/* The resource ID on which control packets are sent. */
#घोषणा VMCI_TRANSPORT_PACKET_RID 1

/* The resource ID on which control packets are sent to the hypervisor. */
#घोषणा VMCI_TRANSPORT_HYPERVISOR_PACKET_RID 15

#घोषणा VSOCK_PROTO_INVALID        0
#घोषणा VSOCK_PROTO_PKT_ON_NOTIFY (1 << 0)
#घोषणा VSOCK_PROTO_ALL_SUPPORTED (VSOCK_PROTO_PKT_ON_NOTIFY)

#घोषणा vmci_trans(_vsk) ((काष्ठा vmci_transport *)((_vsk)->trans))

क्रमागत vmci_transport_packet_type अणु
	VMCI_TRANSPORT_PACKET_TYPE_INVALID = 0,
	VMCI_TRANSPORT_PACKET_TYPE_REQUEST,
	VMCI_TRANSPORT_PACKET_TYPE_NEGOTIATE,
	VMCI_TRANSPORT_PACKET_TYPE_OFFER,
	VMCI_TRANSPORT_PACKET_TYPE_ATTACH,
	VMCI_TRANSPORT_PACKET_TYPE_WROTE,
	VMCI_TRANSPORT_PACKET_TYPE_READ,
	VMCI_TRANSPORT_PACKET_TYPE_RST,
	VMCI_TRANSPORT_PACKET_TYPE_SHUTDOWN,
	VMCI_TRANSPORT_PACKET_TYPE_WAITING_WRITE,
	VMCI_TRANSPORT_PACKET_TYPE_WAITING_READ,
	VMCI_TRANSPORT_PACKET_TYPE_REQUEST2,
	VMCI_TRANSPORT_PACKET_TYPE_NEGOTIATE2,
	VMCI_TRANSPORT_PACKET_TYPE_MAX
पूर्ण;

काष्ठा vmci_transport_रुकोing_info अणु
	u64 generation;
	u64 offset;
पूर्ण;

/* Control packet type क्रम STREAM sockets.  DGRAMs have no control packets nor
 * special packet header क्रम data packets, they are just raw VMCI DGRAM
 * messages.  For STREAMs, control packets are sent over the control channel
 * जबतक data is written and पढ़ो directly from queue pairs with no packet
 * क्रमmat.
 */
काष्ठा vmci_transport_packet अणु
	काष्ठा vmci_datagram dg;
	u8 version;
	u8 type;
	u16 proto;
	u32 src_port;
	u32 dst_port;
	u32 _reserved2;
	जोड़ अणु
		u64 size;
		u64 mode;
		काष्ठा vmci_handle handle;
		काष्ठा vmci_transport_रुकोing_info रुको;
	पूर्ण u;
पूर्ण;

काष्ठा vmci_transport_notअगरy_pkt अणु
	u64 ग_लिखो_notअगरy_winकरोw;
	u64 ग_लिखो_notअगरy_min_winकरोw;
	bool peer_रुकोing_पढ़ो;
	bool peer_रुकोing_ग_लिखो;
	bool peer_रुकोing_ग_लिखो_detected;
	bool sent_रुकोing_पढ़ो;
	bool sent_रुकोing_ग_लिखो;
	काष्ठा vmci_transport_रुकोing_info peer_रुकोing_पढ़ो_info;
	काष्ठा vmci_transport_रुकोing_info peer_रुकोing_ग_लिखो_info;
	u64 produce_q_generation;
	u64 consume_q_generation;
पूर्ण;

काष्ठा vmci_transport_notअगरy_pkt_q_state अणु
	u64 ग_लिखो_notअगरy_winकरोw;
	u64 ग_लिखो_notअगरy_min_winकरोw;
	bool peer_रुकोing_ग_लिखो;
	bool peer_रुकोing_ग_लिखो_detected;
पूर्ण;

जोड़ vmci_transport_notअगरy अणु
	काष्ठा vmci_transport_notअगरy_pkt pkt;
	काष्ठा vmci_transport_notअगरy_pkt_q_state pkt_q_state;
पूर्ण;

/* Our transport-specअगरic data. */
काष्ठा vmci_transport अणु
	/* For DGRAMs. */
	काष्ठा vmci_handle dg_handle;
	/* For STREAMs. */
	काष्ठा vmci_handle qp_handle;
	काष्ठा vmci_qp *qpair;
	u64 produce_size;
	u64 consume_size;
	u32 detach_sub_id;
	जोड़ vmci_transport_notअगरy notअगरy;
	स्थिर काष्ठा vmci_transport_notअगरy_ops *notअगरy_ops;
	काष्ठा list_head elem;
	काष्ठा sock *sk;
	spinlock_t lock; /* protects sk. */
पूर्ण;

पूर्णांक vmci_transport_रेजिस्टर(व्योम);
व्योम vmci_transport_unरेजिस्टर(व्योम);

पूर्णांक vmci_transport_send_wrote_bh(काष्ठा sockaddr_vm *dst,
				 काष्ठा sockaddr_vm *src);
पूर्णांक vmci_transport_send_पढ़ो_bh(काष्ठा sockaddr_vm *dst,
				काष्ठा sockaddr_vm *src);
पूर्णांक vmci_transport_send_wrote(काष्ठा sock *sk);
पूर्णांक vmci_transport_send_पढ़ो(काष्ठा sock *sk);
पूर्णांक vmci_transport_send_रुकोing_ग_लिखो(काष्ठा sock *sk,
				      काष्ठा vmci_transport_रुकोing_info *रुको);
पूर्णांक vmci_transport_send_रुकोing_पढ़ो(काष्ठा sock *sk,
				     काष्ठा vmci_transport_रुकोing_info *रुको);

#पूर्ण_अगर
