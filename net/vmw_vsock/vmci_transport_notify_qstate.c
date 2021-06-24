<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VMware vSockets Driver
 *
 * Copyright (C) 2009-2013 VMware, Inc. All rights reserved.
 */

#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/मानकघोष.स>
#समावेश <net/sock.h>

#समावेश "vmci_transport_notify.h"

#घोषणा PKT_FIELD(vsk, field_name) \
	(vmci_trans(vsk)->notअगरy.pkt_q_state.field_name)

अटल bool vmci_transport_notअगरy_रुकोing_ग_लिखो(काष्ठा vsock_sock *vsk)
अणु
	bool retval;
	u64 notअगरy_limit;

	अगर (!PKT_FIELD(vsk, peer_रुकोing_ग_लिखो))
		वापस false;

	/* When the sender blocks, we take that as a sign that the sender is
	 * faster than the receiver. To reduce the transmit rate of the sender,
	 * we delay the sending of the पढ़ो notअगरication by decreasing the
	 * ग_लिखो_notअगरy_winकरोw. The notअगरication is delayed until the number of
	 * bytes used in the queue drops below the ग_लिखो_notअगरy_winकरोw.
	 */

	अगर (!PKT_FIELD(vsk, peer_रुकोing_ग_लिखो_detected)) अणु
		PKT_FIELD(vsk, peer_रुकोing_ग_लिखो_detected) = true;
		अगर (PKT_FIELD(vsk, ग_लिखो_notअगरy_winकरोw) < PAGE_SIZE) अणु
			PKT_FIELD(vsk, ग_लिखो_notअगरy_winकरोw) =
			    PKT_FIELD(vsk, ग_लिखो_notअगरy_min_winकरोw);
		पूर्ण अन्यथा अणु
			PKT_FIELD(vsk, ग_लिखो_notअगरy_winकरोw) -= PAGE_SIZE;
			अगर (PKT_FIELD(vsk, ग_लिखो_notअगरy_winकरोw) <
			    PKT_FIELD(vsk, ग_लिखो_notअगरy_min_winकरोw))
				PKT_FIELD(vsk, ग_लिखो_notअगरy_winकरोw) =
				    PKT_FIELD(vsk, ग_लिखो_notअगरy_min_winकरोw);

		पूर्ण
	पूर्ण
	notअगरy_limit = vmci_trans(vsk)->consume_size -
		PKT_FIELD(vsk, ग_लिखो_notअगरy_winकरोw);

	/* The notअगरy_limit is used to delay notअगरications in the हाल where
	 * flow control is enabled. Below the test is expressed in terms of
	 * मुक्त space in the queue: अगर मुक्त_space > ConsumeSize -
	 * ग_लिखो_notअगरy_winकरोw then notअगरy An alternate way of expressing this
	 * is to reग_लिखो the expression to use the data पढ़ोy in the receive
	 * queue: अगर ग_लिखो_notअगरy_winकरोw > bufferReady then notअगरy as
	 * मुक्त_space == ConsumeSize - bufferReady.
	 */

	retval = vmci_qpair_consume_मुक्त_space(vmci_trans(vsk)->qpair) >
		notअगरy_limit;

	अगर (retval) अणु
		/* Once we notअगरy the peer, we reset the detected flag so the
		 * next रुको will again cause a decrease in the winकरोw size.
		 */

		PKT_FIELD(vsk, peer_रुकोing_ग_लिखो_detected) = false;
	पूर्ण
	वापस retval;
पूर्ण

अटल व्योम
vmci_transport_handle_पढ़ो(काष्ठा sock *sk,
			   काष्ठा vmci_transport_packet *pkt,
			   bool bottom_half,
			   काष्ठा sockaddr_vm *dst, काष्ठा sockaddr_vm *src)
अणु
	sk->sk_ग_लिखो_space(sk);
पूर्ण

अटल व्योम
vmci_transport_handle_wrote(काष्ठा sock *sk,
			    काष्ठा vmci_transport_packet *pkt,
			    bool bottom_half,
			    काष्ठा sockaddr_vm *dst, काष्ठा sockaddr_vm *src)
अणु
	sk->sk_data_पढ़ोy(sk);
पूर्ण

अटल व्योम vsock_block_update_ग_लिखो_winकरोw(काष्ठा sock *sk)
अणु
	काष्ठा vsock_sock *vsk = vsock_sk(sk);

	अगर (PKT_FIELD(vsk, ग_लिखो_notअगरy_winकरोw) < vmci_trans(vsk)->consume_size)
		PKT_FIELD(vsk, ग_लिखो_notअगरy_winकरोw) =
		    min(PKT_FIELD(vsk, ग_लिखो_notअगरy_winकरोw) + PAGE_SIZE,
			vmci_trans(vsk)->consume_size);
पूर्ण

अटल पूर्णांक vmci_transport_send_पढ़ो_notअगरication(काष्ठा sock *sk)
अणु
	काष्ठा vsock_sock *vsk;
	bool sent_पढ़ो;
	अचिन्हित पूर्णांक retries;
	पूर्णांक err;

	vsk = vsock_sk(sk);
	sent_पढ़ो = false;
	retries = 0;
	err = 0;

	अगर (vmci_transport_notअगरy_रुकोing_ग_लिखो(vsk)) अणु
		/* Notअगरy the peer that we have पढ़ो, retrying the send on
		 * failure up to our maximum value.  XXX For now we just log
		 * the failure, but later we should schedule a work item to
		 * handle the resend until it succeeds.  That would require
		 * keeping track of work items in the vsk and cleaning them up
		 * upon socket बंद.
		 */
		जबतक (!(vsk->peer_shutकरोwn & RCV_SHUTDOWN) &&
		       !sent_पढ़ो &&
		       retries < VMCI_TRANSPORT_MAX_DGRAM_RESENDS) अणु
			err = vmci_transport_send_पढ़ो(sk);
			अगर (err >= 0)
				sent_पढ़ो = true;

			retries++;
		पूर्ण

		अगर (retries >= VMCI_TRANSPORT_MAX_DGRAM_RESENDS && !sent_पढ़ो)
			pr_err("%p unable to send read notification to peer\n",
			       sk);
		अन्यथा
			PKT_FIELD(vsk, peer_रुकोing_ग_लिखो) = false;

	पूर्ण
	वापस err;
पूर्ण

अटल व्योम vmci_transport_notअगरy_pkt_socket_init(काष्ठा sock *sk)
अणु
	काष्ठा vsock_sock *vsk = vsock_sk(sk);

	PKT_FIELD(vsk, ग_लिखो_notअगरy_winकरोw) = PAGE_SIZE;
	PKT_FIELD(vsk, ग_लिखो_notअगरy_min_winकरोw) = PAGE_SIZE;
	PKT_FIELD(vsk, peer_रुकोing_ग_लिखो) = false;
	PKT_FIELD(vsk, peer_रुकोing_ग_लिखो_detected) = false;
पूर्ण

अटल व्योम vmci_transport_notअगरy_pkt_socket_deकाष्ठा(काष्ठा vsock_sock *vsk)
अणु
	PKT_FIELD(vsk, ग_लिखो_notअगरy_winकरोw) = PAGE_SIZE;
	PKT_FIELD(vsk, ग_लिखो_notअगरy_min_winकरोw) = PAGE_SIZE;
	PKT_FIELD(vsk, peer_रुकोing_ग_लिखो) = false;
	PKT_FIELD(vsk, peer_रुकोing_ग_लिखो_detected) = false;
पूर्ण

अटल पूर्णांक
vmci_transport_notअगरy_pkt_poll_in(काष्ठा sock *sk,
				  माप_प्रकार target, bool *data_पढ़ोy_now)
अणु
	काष्ठा vsock_sock *vsk = vsock_sk(sk);

	अगर (vsock_stream_has_data(vsk)) अणु
		*data_पढ़ोy_now = true;
	पूर्ण अन्यथा अणु
		/* We can't पढ़ो right now because there is nothing in the
		 * queue. Ask क्रम notअगरications when there is something to
		 * पढ़ो.
		 */
		अगर (sk->sk_state == TCP_ESTABLISHED)
			vsock_block_update_ग_लिखो_winकरोw(sk);
		*data_पढ़ोy_now = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
vmci_transport_notअगरy_pkt_poll_out(काष्ठा sock *sk,
				   माप_प्रकार target, bool *space_avail_now)
अणु
	s64 produce_q_मुक्त_space;
	काष्ठा vsock_sock *vsk = vsock_sk(sk);

	produce_q_मुक्त_space = vsock_stream_has_space(vsk);
	अगर (produce_q_मुक्त_space > 0) अणु
		*space_avail_now = true;
		वापस 0;
	पूर्ण अन्यथा अगर (produce_q_मुक्त_space == 0) अणु
		/* This is a connected socket but we can't currently send data.
		 * Nothing अन्यथा to करो.
		 */
		*space_avail_now = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
vmci_transport_notअगरy_pkt_recv_init(
				काष्ठा sock *sk,
				माप_प्रकार target,
				काष्ठा vmci_transport_recv_notअगरy_data *data)
अणु
	काष्ठा vsock_sock *vsk = vsock_sk(sk);

	data->consume_head = 0;
	data->produce_tail = 0;
	data->notअगरy_on_block = false;

	अगर (PKT_FIELD(vsk, ग_लिखो_notअगरy_min_winकरोw) < target + 1) अणु
		PKT_FIELD(vsk, ग_लिखो_notअगरy_min_winकरोw) = target + 1;
		अगर (PKT_FIELD(vsk, ग_लिखो_notअगरy_winकरोw) <
		    PKT_FIELD(vsk, ग_लिखो_notअगरy_min_winकरोw)) अणु
			/* If the current winकरोw is smaller than the new
			 * minimal winकरोw size, we need to reevaluate whether
			 * we need to notअगरy the sender. If the number of पढ़ोy
			 * bytes are smaller than the new winकरोw, we need to
			 * send a notअगरication to the sender beक्रमe we block.
			 */

			PKT_FIELD(vsk, ग_लिखो_notअगरy_winकरोw) =
			    PKT_FIELD(vsk, ग_लिखो_notअगरy_min_winकरोw);
			data->notअगरy_on_block = true;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
vmci_transport_notअगरy_pkt_recv_pre_block(
				काष्ठा sock *sk,
				माप_प्रकार target,
				काष्ठा vmci_transport_recv_notअगरy_data *data)
अणु
	पूर्णांक err = 0;

	vsock_block_update_ग_लिखो_winकरोw(sk);

	अगर (data->notअगरy_on_block) अणु
		err = vmci_transport_send_पढ़ो_notअगरication(sk);
		अगर (err < 0)
			वापस err;
		data->notअगरy_on_block = false;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक
vmci_transport_notअगरy_pkt_recv_post_dequeue(
				काष्ठा sock *sk,
				माप_प्रकार target,
				sमाप_प्रकार copied,
				bool data_पढ़ो,
				काष्ठा vmci_transport_recv_notअगरy_data *data)
अणु
	काष्ठा vsock_sock *vsk;
	पूर्णांक err;
	bool was_full = false;
	u64 मुक्त_space;

	vsk = vsock_sk(sk);
	err = 0;

	अगर (data_पढ़ो) अणु
		smp_mb();

		मुक्त_space =
			vmci_qpair_consume_मुक्त_space(vmci_trans(vsk)->qpair);
		was_full = मुक्त_space == copied;

		अगर (was_full)
			PKT_FIELD(vsk, peer_रुकोing_ग_लिखो) = true;

		err = vmci_transport_send_पढ़ो_notअगरication(sk);
		अगर (err < 0)
			वापस err;

		/* See the comment in
		 * vmci_transport_notअगरy_pkt_send_post_enqueue().
		 */
		sk->sk_data_पढ़ोy(sk);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक
vmci_transport_notअगरy_pkt_send_init(
				काष्ठा sock *sk,
				काष्ठा vmci_transport_send_notअगरy_data *data)
अणु
	data->consume_head = 0;
	data->produce_tail = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक
vmci_transport_notअगरy_pkt_send_post_enqueue(
				काष्ठा sock *sk,
				sमाप_प्रकार written,
				काष्ठा vmci_transport_send_notअगरy_data *data)
अणु
	पूर्णांक err = 0;
	काष्ठा vsock_sock *vsk;
	bool sent_wrote = false;
	bool was_empty;
	पूर्णांक retries = 0;

	vsk = vsock_sk(sk);

	smp_mb();

	was_empty =
		vmci_qpair_produce_buf_पढ़ोy(vmci_trans(vsk)->qpair) == written;
	अगर (was_empty) अणु
		जबतक (!(vsk->peer_shutकरोwn & RCV_SHUTDOWN) &&
		       !sent_wrote &&
		       retries < VMCI_TRANSPORT_MAX_DGRAM_RESENDS) अणु
			err = vmci_transport_send_wrote(sk);
			अगर (err >= 0)
				sent_wrote = true;

			retries++;
		पूर्ण
	पूर्ण

	अगर (retries >= VMCI_TRANSPORT_MAX_DGRAM_RESENDS && !sent_wrote) अणु
		pr_err("%p unable to send wrote notification to peer\n",
		       sk);
		वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम
vmci_transport_notअगरy_pkt_handle_pkt(
				काष्ठा sock *sk,
				काष्ठा vmci_transport_packet *pkt,
				bool bottom_half,
				काष्ठा sockaddr_vm *dst,
				काष्ठा sockaddr_vm *src, bool *pkt_processed)
अणु
	bool processed = false;

	चयन (pkt->type) अणु
	हाल VMCI_TRANSPORT_PACKET_TYPE_WROTE:
		vmci_transport_handle_wrote(sk, pkt, bottom_half, dst, src);
		processed = true;
		अवरोध;
	हाल VMCI_TRANSPORT_PACKET_TYPE_READ:
		vmci_transport_handle_पढ़ो(sk, pkt, bottom_half, dst, src);
		processed = true;
		अवरोध;
	पूर्ण

	अगर (pkt_processed)
		*pkt_processed = processed;
पूर्ण

अटल व्योम vmci_transport_notअगरy_pkt_process_request(काष्ठा sock *sk)
अणु
	काष्ठा vsock_sock *vsk = vsock_sk(sk);

	PKT_FIELD(vsk, ग_लिखो_notअगरy_winकरोw) = vmci_trans(vsk)->consume_size;
	अगर (vmci_trans(vsk)->consume_size <
		PKT_FIELD(vsk, ग_लिखो_notअगरy_min_winकरोw))
		PKT_FIELD(vsk, ग_लिखो_notअगरy_min_winकरोw) =
			vmci_trans(vsk)->consume_size;
पूर्ण

अटल व्योम vmci_transport_notअगरy_pkt_process_negotiate(काष्ठा sock *sk)
अणु
	काष्ठा vsock_sock *vsk = vsock_sk(sk);

	PKT_FIELD(vsk, ग_लिखो_notअगरy_winकरोw) = vmci_trans(vsk)->consume_size;
	अगर (vmci_trans(vsk)->consume_size <
		PKT_FIELD(vsk, ग_लिखो_notअगरy_min_winकरोw))
		PKT_FIELD(vsk, ग_लिखो_notअगरy_min_winकरोw) =
			vmci_trans(vsk)->consume_size;
पूर्ण

अटल पूर्णांक
vmci_transport_notअगरy_pkt_recv_pre_dequeue(
				काष्ठा sock *sk,
				माप_प्रकार target,
				काष्ठा vmci_transport_recv_notअगरy_data *data)
अणु
	वापस 0; /* NOP क्रम QState. */
पूर्ण

अटल पूर्णांक
vmci_transport_notअगरy_pkt_send_pre_block(
				काष्ठा sock *sk,
				काष्ठा vmci_transport_send_notअगरy_data *data)
अणु
	वापस 0; /* NOP क्रम QState. */
पूर्ण

अटल पूर्णांक
vmci_transport_notअगरy_pkt_send_pre_enqueue(
				काष्ठा sock *sk,
				काष्ठा vmci_transport_send_notअगरy_data *data)
अणु
	वापस 0; /* NOP क्रम QState. */
पूर्ण

/* Socket always on control packet based operations. */
स्थिर काष्ठा vmci_transport_notअगरy_ops vmci_transport_notअगरy_pkt_q_state_ops = अणु
	.socket_init = vmci_transport_notअगरy_pkt_socket_init,
	.socket_deकाष्ठा = vmci_transport_notअगरy_pkt_socket_deकाष्ठा,
	.poll_in = vmci_transport_notअगरy_pkt_poll_in,
	.poll_out = vmci_transport_notअगरy_pkt_poll_out,
	.handle_notअगरy_pkt = vmci_transport_notअगरy_pkt_handle_pkt,
	.recv_init = vmci_transport_notअगरy_pkt_recv_init,
	.recv_pre_block = vmci_transport_notअगरy_pkt_recv_pre_block,
	.recv_pre_dequeue = vmci_transport_notअगरy_pkt_recv_pre_dequeue,
	.recv_post_dequeue = vmci_transport_notअगरy_pkt_recv_post_dequeue,
	.send_init = vmci_transport_notअगरy_pkt_send_init,
	.send_pre_block = vmci_transport_notअगरy_pkt_send_pre_block,
	.send_pre_enqueue = vmci_transport_notअगरy_pkt_send_pre_enqueue,
	.send_post_enqueue = vmci_transport_notअगरy_pkt_send_post_enqueue,
	.process_request = vmci_transport_notअगरy_pkt_process_request,
	.process_negotiate = vmci_transport_notअगरy_pkt_process_negotiate,
पूर्ण;
