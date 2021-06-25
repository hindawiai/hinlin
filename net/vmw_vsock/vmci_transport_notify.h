<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * VMware vSockets Driver
 *
 * Copyright (C) 2009-2013 VMware, Inc. All rights reserved.
 */

#अगर_अघोषित __VMCI_TRANSPORT_NOTIFY_H__
#घोषणा __VMCI_TRANSPORT_NOTIFY_H__

#समावेश <linux/types.h>
#समावेश <linux/vmw_vmci_defs.h>
#समावेश <linux/vmw_vmci_api.h>

#समावेश "vmci_transport.h"

/* Comment this out to compare with old protocol. */
#घोषणा VSOCK_OPTIMIZATION_WAITING_NOTIFY 1
#अगर defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
/* Comment this out to हटाओ flow control क्रम "new" protocol */
#घोषणा VSOCK_OPTIMIZATION_FLOW_CONTROL 1
#पूर्ण_अगर

#घोषणा VMCI_TRANSPORT_MAX_DGRAM_RESENDS       10

काष्ठा vmci_transport_recv_notअगरy_data अणु
	u64 consume_head;
	u64 produce_tail;
	bool notअगरy_on_block;
पूर्ण;

काष्ठा vmci_transport_send_notअगरy_data अणु
	u64 consume_head;
	u64 produce_tail;
पूर्ण;

/* Socket notअगरication callbacks. */
काष्ठा vmci_transport_notअगरy_ops अणु
	व्योम (*socket_init) (काष्ठा sock *sk);
	व्योम (*socket_deकाष्ठा) (काष्ठा vsock_sock *vsk);
	पूर्णांक (*poll_in) (काष्ठा sock *sk, माप_प्रकार target,
			  bool *data_पढ़ोy_now);
	पूर्णांक (*poll_out) (काष्ठा sock *sk, माप_प्रकार target,
			   bool *space_avail_now);
	व्योम (*handle_notअगरy_pkt) (काष्ठा sock *sk,
				   काष्ठा vmci_transport_packet *pkt,
				   bool bottom_half, काष्ठा sockaddr_vm *dst,
				   काष्ठा sockaddr_vm *src,
				   bool *pkt_processed);
	पूर्णांक (*recv_init) (काष्ठा sock *sk, माप_प्रकार target,
			  काष्ठा vmci_transport_recv_notअगरy_data *data);
	पूर्णांक (*recv_pre_block) (काष्ठा sock *sk, माप_प्रकार target,
			       काष्ठा vmci_transport_recv_notअगरy_data *data);
	पूर्णांक (*recv_pre_dequeue) (काष्ठा sock *sk, माप_प्रकार target,
				 काष्ठा vmci_transport_recv_notअगरy_data *data);
	पूर्णांक (*recv_post_dequeue) (काष्ठा sock *sk, माप_प्रकार target,
				  sमाप_प्रकार copied, bool data_पढ़ो,
				  काष्ठा vmci_transport_recv_notअगरy_data *data);
	पूर्णांक (*send_init) (काष्ठा sock *sk,
			  काष्ठा vmci_transport_send_notअगरy_data *data);
	पूर्णांक (*send_pre_block) (काष्ठा sock *sk,
			       काष्ठा vmci_transport_send_notअगरy_data *data);
	पूर्णांक (*send_pre_enqueue) (काष्ठा sock *sk,
				 काष्ठा vmci_transport_send_notअगरy_data *data);
	पूर्णांक (*send_post_enqueue) (काष्ठा sock *sk, sमाप_प्रकार written,
				  काष्ठा vmci_transport_send_notअगरy_data *data);
	व्योम (*process_request) (काष्ठा sock *sk);
	व्योम (*process_negotiate) (काष्ठा sock *sk);
पूर्ण;

बाह्य स्थिर काष्ठा vmci_transport_notअगरy_ops vmci_transport_notअगरy_pkt_ops;
बाह्य स्थिर
काष्ठा vmci_transport_notअगरy_ops vmci_transport_notअगरy_pkt_q_state_ops;

#पूर्ण_अगर /* __VMCI_TRANSPORT_NOTIFY_H__ */
