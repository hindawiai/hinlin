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

#घोषणा PKT_FIELD(vsk, field_name) (vmci_trans(vsk)->notअगरy.pkt.field_name)

अटल bool vmci_transport_notअगरy_रुकोing_ग_लिखो(काष्ठा vsock_sock *vsk)
अणु
#अगर defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	bool retval;
	u64 notअगरy_limit;

	अगर (!PKT_FIELD(vsk, peer_रुकोing_ग_लिखो))
		वापस false;

#अगर_घोषित VSOCK_OPTIMIZATION_FLOW_CONTROL
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
#अन्यथा
	notअगरy_limit = 0;
#पूर्ण_अगर

	/* For now we ignore the रुको inक्रमmation and just see अगर the मुक्त
	 * space exceeds the notअगरy limit.  Note that improving this function
	 * to be more पूर्णांकelligent will not require a protocol change and will
	 * retain compatibility between endpoपूर्णांकs with mixed versions of this
	 * function.
	 *
	 * The notअगरy_limit is used to delay notअगरications in the हाल where
	 * flow control is enabled. Below the test is expressed in terms of
	 * मुक्त space in the queue: अगर मुक्त_space > ConsumeSize -
	 * ग_लिखो_notअगरy_winकरोw then notअगरy An alternate way of expressing this
	 * is to reग_लिखो the expression to use the data पढ़ोy in the receive
	 * queue: अगर ग_लिखो_notअगरy_winकरोw > bufferReady then notअगरy as
	 * मुक्त_space == ConsumeSize - bufferReady.
	 */
	retval = vmci_qpair_consume_मुक्त_space(vmci_trans(vsk)->qpair) >
		notअगरy_limit;
#अगर_घोषित VSOCK_OPTIMIZATION_FLOW_CONTROL
	अगर (retval) अणु
		/*
		 * Once we notअगरy the peer, we reset the detected flag so the
		 * next रुको will again cause a decrease in the winकरोw size.
		 */

		PKT_FIELD(vsk, peer_रुकोing_ग_लिखो_detected) = false;
	पूर्ण
#पूर्ण_अगर
	वापस retval;
#अन्यथा
	वापस true;
#पूर्ण_अगर
पूर्ण

अटल bool vmci_transport_notअगरy_रुकोing_पढ़ो(काष्ठा vsock_sock *vsk)
अणु
#अगर defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	अगर (!PKT_FIELD(vsk, peer_रुकोing_पढ़ो))
		वापस false;

	/* For now we ignore the रुको inक्रमmation and just see अगर there is any
	 * data क्रम our peer to पढ़ो.  Note that improving this function to be
	 * more पूर्णांकelligent will not require a protocol change and will retain
	 * compatibility between endpoपूर्णांकs with mixed versions of this
	 * function.
	 */
	वापस vmci_qpair_produce_buf_पढ़ोy(vmci_trans(vsk)->qpair) > 0;
#अन्यथा
	वापस true;
#पूर्ण_अगर
पूर्ण

अटल व्योम
vmci_transport_handle_रुकोing_पढ़ो(काष्ठा sock *sk,
				   काष्ठा vmci_transport_packet *pkt,
				   bool bottom_half,
				   काष्ठा sockaddr_vm *dst,
				   काष्ठा sockaddr_vm *src)
अणु
#अगर defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	काष्ठा vsock_sock *vsk;

	vsk = vsock_sk(sk);

	PKT_FIELD(vsk, peer_रुकोing_पढ़ो) = true;
	स_नकल(&PKT_FIELD(vsk, peer_रुकोing_पढ़ो_info), &pkt->u.रुको,
	       माप(PKT_FIELD(vsk, peer_रुकोing_पढ़ो_info)));

	अगर (vmci_transport_notअगरy_रुकोing_पढ़ो(vsk)) अणु
		bool sent;

		अगर (bottom_half)
			sent = vmci_transport_send_wrote_bh(dst, src) > 0;
		अन्यथा
			sent = vmci_transport_send_wrote(sk) > 0;

		अगर (sent)
			PKT_FIELD(vsk, peer_रुकोing_पढ़ो) = false;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम
vmci_transport_handle_रुकोing_ग_लिखो(काष्ठा sock *sk,
				    काष्ठा vmci_transport_packet *pkt,
				    bool bottom_half,
				    काष्ठा sockaddr_vm *dst,
				    काष्ठा sockaddr_vm *src)
अणु
#अगर defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	काष्ठा vsock_sock *vsk;

	vsk = vsock_sk(sk);

	PKT_FIELD(vsk, peer_रुकोing_ग_लिखो) = true;
	स_नकल(&PKT_FIELD(vsk, peer_रुकोing_ग_लिखो_info), &pkt->u.रुको,
	       माप(PKT_FIELD(vsk, peer_रुकोing_ग_लिखो_info)));

	अगर (vmci_transport_notअगरy_रुकोing_ग_लिखो(vsk)) अणु
		bool sent;

		अगर (bottom_half)
			sent = vmci_transport_send_पढ़ो_bh(dst, src) > 0;
		अन्यथा
			sent = vmci_transport_send_पढ़ो(sk) > 0;

		अगर (sent)
			PKT_FIELD(vsk, peer_रुकोing_ग_लिखो) = false;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम
vmci_transport_handle_पढ़ो(काष्ठा sock *sk,
			   काष्ठा vmci_transport_packet *pkt,
			   bool bottom_half,
			   काष्ठा sockaddr_vm *dst, काष्ठा sockaddr_vm *src)
अणु
#अगर defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	काष्ठा vsock_sock *vsk;

	vsk = vsock_sk(sk);
	PKT_FIELD(vsk, sent_रुकोing_ग_लिखो) = false;
#पूर्ण_अगर

	sk->sk_ग_लिखो_space(sk);
पूर्ण

अटल bool send_रुकोing_पढ़ो(काष्ठा sock *sk, u64 room_needed)
अणु
#अगर defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	काष्ठा vsock_sock *vsk;
	काष्ठा vmci_transport_रुकोing_info रुकोing_info;
	u64 tail;
	u64 head;
	u64 room_left;
	bool ret;

	vsk = vsock_sk(sk);

	अगर (PKT_FIELD(vsk, sent_रुकोing_पढ़ो))
		वापस true;

	अगर (PKT_FIELD(vsk, ग_लिखो_notअगरy_winकरोw) <
			vmci_trans(vsk)->consume_size)
		PKT_FIELD(vsk, ग_लिखो_notअगरy_winकरोw) =
		    min(PKT_FIELD(vsk, ग_लिखो_notअगरy_winकरोw) + PAGE_SIZE,
			vmci_trans(vsk)->consume_size);

	vmci_qpair_get_consume_indexes(vmci_trans(vsk)->qpair, &tail, &head);
	room_left = vmci_trans(vsk)->consume_size - head;
	अगर (room_needed >= room_left) अणु
		रुकोing_info.offset = room_needed - room_left;
		रुकोing_info.generation =
		    PKT_FIELD(vsk, consume_q_generation) + 1;
	पूर्ण अन्यथा अणु
		रुकोing_info.offset = head + room_needed;
		रुकोing_info.generation = PKT_FIELD(vsk, consume_q_generation);
	पूर्ण

	ret = vmci_transport_send_रुकोing_पढ़ो(sk, &रुकोing_info) > 0;
	अगर (ret)
		PKT_FIELD(vsk, sent_रुकोing_पढ़ो) = true;

	वापस ret;
#अन्यथा
	वापस true;
#पूर्ण_अगर
पूर्ण

अटल bool send_रुकोing_ग_लिखो(काष्ठा sock *sk, u64 room_needed)
अणु
#अगर defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	काष्ठा vsock_sock *vsk;
	काष्ठा vmci_transport_रुकोing_info रुकोing_info;
	u64 tail;
	u64 head;
	u64 room_left;
	bool ret;

	vsk = vsock_sk(sk);

	अगर (PKT_FIELD(vsk, sent_रुकोing_ग_लिखो))
		वापस true;

	vmci_qpair_get_produce_indexes(vmci_trans(vsk)->qpair, &tail, &head);
	room_left = vmci_trans(vsk)->produce_size - tail;
	अगर (room_needed + 1 >= room_left) अणु
		/* Wraps around to current generation. */
		रुकोing_info.offset = room_needed + 1 - room_left;
		रुकोing_info.generation = PKT_FIELD(vsk, produce_q_generation);
	पूर्ण अन्यथा अणु
		रुकोing_info.offset = tail + room_needed + 1;
		रुकोing_info.generation =
		    PKT_FIELD(vsk, produce_q_generation) - 1;
	पूर्ण

	ret = vmci_transport_send_रुकोing_ग_लिखो(sk, &रुकोing_info) > 0;
	अगर (ret)
		PKT_FIELD(vsk, sent_रुकोing_ग_लिखो) = true;

	वापस ret;
#अन्यथा
	वापस true;
#पूर्ण_अगर
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

		अगर (retries >= VMCI_TRANSPORT_MAX_DGRAM_RESENDS)
			pr_err("%p unable to send read notify to peer\n", sk);
		अन्यथा
#अगर defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
			PKT_FIELD(vsk, peer_रुकोing_ग_लिखो) = false;
#पूर्ण_अगर

	पूर्ण
	वापस err;
पूर्ण

अटल व्योम
vmci_transport_handle_wrote(काष्ठा sock *sk,
			    काष्ठा vmci_transport_packet *pkt,
			    bool bottom_half,
			    काष्ठा sockaddr_vm *dst, काष्ठा sockaddr_vm *src)
अणु
#अगर defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	काष्ठा vsock_sock *vsk = vsock_sk(sk);
	PKT_FIELD(vsk, sent_रुकोing_पढ़ो) = false;
#पूर्ण_अगर
	sk->sk_data_पढ़ोy(sk);
पूर्ण

अटल व्योम vmci_transport_notअगरy_pkt_socket_init(काष्ठा sock *sk)
अणु
	काष्ठा vsock_sock *vsk = vsock_sk(sk);

	PKT_FIELD(vsk, ग_लिखो_notअगरy_winकरोw) = PAGE_SIZE;
	PKT_FIELD(vsk, ग_लिखो_notअगरy_min_winकरोw) = PAGE_SIZE;
	PKT_FIELD(vsk, peer_रुकोing_पढ़ो) = false;
	PKT_FIELD(vsk, peer_रुकोing_ग_लिखो) = false;
	PKT_FIELD(vsk, peer_रुकोing_ग_लिखो_detected) = false;
	PKT_FIELD(vsk, sent_रुकोing_पढ़ो) = false;
	PKT_FIELD(vsk, sent_रुकोing_ग_लिखो) = false;
	PKT_FIELD(vsk, produce_q_generation) = 0;
	PKT_FIELD(vsk, consume_q_generation) = 0;

	स_रखो(&PKT_FIELD(vsk, peer_रुकोing_पढ़ो_info), 0,
	       माप(PKT_FIELD(vsk, peer_रुकोing_पढ़ो_info)));
	स_रखो(&PKT_FIELD(vsk, peer_रुकोing_ग_लिखो_info), 0,
	       माप(PKT_FIELD(vsk, peer_रुकोing_ग_लिखो_info)));
पूर्ण

अटल व्योम vmci_transport_notअगरy_pkt_socket_deकाष्ठा(काष्ठा vsock_sock *vsk)
अणु
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
		अगर (sk->sk_state == TCP_ESTABLISHED) अणु
			अगर (!send_रुकोing_पढ़ो(sk, 1))
				वापस -1;

		पूर्ण
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
		 * Notअगरy the peer that we are रुकोing अगर the queue is full. We
		 * only send a रुकोing ग_लिखो अगर the queue is full because
		 * otherwise we end up in an infinite WAITING_WRITE, READ,
		 * WAITING_WRITE, READ, etc. loop. Treat failing to send the
		 * notअगरication as a socket error, passing that back through
		 * the mask.
		 */
		अगर (!send_रुकोing_ग_लिखो(sk, 1))
			वापस -1;

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

#अगर_घोषित VSOCK_OPTIMIZATION_WAITING_NOTIFY
	data->consume_head = 0;
	data->produce_tail = 0;
#अगर_घोषित VSOCK_OPTIMIZATION_FLOW_CONTROL
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
#पूर्ण_अगर
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक
vmci_transport_notअगरy_pkt_recv_pre_block(
				काष्ठा sock *sk,
				माप_प्रकार target,
				काष्ठा vmci_transport_recv_notअगरy_data *data)
अणु
	पूर्णांक err = 0;

	/* Notअगरy our peer that we are रुकोing क्रम data to पढ़ो. */
	अगर (!send_रुकोing_पढ़ो(sk, target)) अणु
		err = -EHOSTUNREACH;
		वापस err;
	पूर्ण
#अगर_घोषित VSOCK_OPTIMIZATION_FLOW_CONTROL
	अगर (data->notअगरy_on_block) अणु
		err = vmci_transport_send_पढ़ो_notअगरication(sk);
		अगर (err < 0)
			वापस err;

		data->notअगरy_on_block = false;
	पूर्ण
#पूर्ण_अगर

	वापस err;
पूर्ण

अटल पूर्णांक
vmci_transport_notअगरy_pkt_recv_pre_dequeue(
				काष्ठा sock *sk,
				माप_प्रकार target,
				काष्ठा vmci_transport_recv_notअगरy_data *data)
अणु
	काष्ठा vsock_sock *vsk = vsock_sk(sk);

	/* Now consume up to len bytes from the queue.  Note that since we have
	 * the socket locked we should copy at least पढ़ोy bytes.
	 */
#अगर defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	vmci_qpair_get_consume_indexes(vmci_trans(vsk)->qpair,
				       &data->produce_tail,
				       &data->consume_head);
#पूर्ण_अगर

	वापस 0;
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

	vsk = vsock_sk(sk);
	err = 0;

	अगर (data_पढ़ो) अणु
#अगर defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
		/* Detect a wrap-around to मुख्यtain queue generation.  Note
		 * that this is safe since we hold the socket lock across the
		 * two queue pair operations.
		 */
		अगर (copied >=
			vmci_trans(vsk)->consume_size - data->consume_head)
			PKT_FIELD(vsk, consume_q_generation)++;
#पूर्ण_अगर

		err = vmci_transport_send_पढ़ो_notअगरication(sk);
		अगर (err < 0)
			वापस err;

	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक
vmci_transport_notअगरy_pkt_send_init(
			काष्ठा sock *sk,
			काष्ठा vmci_transport_send_notअगरy_data *data)
अणु
#अगर_घोषित VSOCK_OPTIMIZATION_WAITING_NOTIFY
	data->consume_head = 0;
	data->produce_tail = 0;
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक
vmci_transport_notअगरy_pkt_send_pre_block(
				काष्ठा sock *sk,
				काष्ठा vmci_transport_send_notअगरy_data *data)
अणु
	/* Notअगरy our peer that we are रुकोing क्रम room to ग_लिखो. */
	अगर (!send_रुकोing_ग_लिखो(sk, 1))
		वापस -EHOSTUNREACH;

	वापस 0;
पूर्ण

अटल पूर्णांक
vmci_transport_notअगरy_pkt_send_pre_enqueue(
				काष्ठा sock *sk,
				काष्ठा vmci_transport_send_notअगरy_data *data)
अणु
	काष्ठा vsock_sock *vsk = vsock_sk(sk);

#अगर defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	vmci_qpair_get_produce_indexes(vmci_trans(vsk)->qpair,
				       &data->produce_tail,
				       &data->consume_head);
#पूर्ण_अगर

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
	पूर्णांक retries = 0;

	vsk = vsock_sk(sk);

#अगर defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	/* Detect a wrap-around to मुख्यtain queue generation.  Note that this
	 * is safe since we hold the socket lock across the two queue pair
	 * operations.
	 */
	अगर (written >= vmci_trans(vsk)->produce_size - data->produce_tail)
		PKT_FIELD(vsk, produce_q_generation)++;

#पूर्ण_अगर

	अगर (vmci_transport_notअगरy_रुकोing_पढ़ो(vsk)) अणु
		/* Notअगरy the peer that we have written, retrying the send on
		 * failure up to our maximum value. See the XXX comment क्रम the
		 * corresponding piece of code in StreamRecvmsg() क्रम potential
		 * improvements.
		 */
		जबतक (!(vsk->peer_shutकरोwn & RCV_SHUTDOWN) &&
		       !sent_wrote &&
		       retries < VMCI_TRANSPORT_MAX_DGRAM_RESENDS) अणु
			err = vmci_transport_send_wrote(sk);
			अगर (err >= 0)
				sent_wrote = true;

			retries++;
		पूर्ण

		अगर (retries >= VMCI_TRANSPORT_MAX_DGRAM_RESENDS) अणु
			pr_err("%p unable to send wrote notify to peer\n", sk);
			वापस err;
		पूर्ण अन्यथा अणु
#अगर defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
			PKT_FIELD(vsk, peer_रुकोing_पढ़ो) = false;
#पूर्ण_अगर
		पूर्ण
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
	हाल VMCI_TRANSPORT_PACKET_TYPE_WAITING_WRITE:
		vmci_transport_handle_रुकोing_ग_लिखो(sk, pkt, bottom_half,
						    dst, src);
		processed = true;
		अवरोध;

	हाल VMCI_TRANSPORT_PACKET_TYPE_WAITING_READ:
		vmci_transport_handle_रुकोing_पढ़ो(sk, pkt, bottom_half,
						   dst, src);
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

/* Socket control packet based operations. */
स्थिर काष्ठा vmci_transport_notअगरy_ops vmci_transport_notअगरy_pkt_ops = अणु
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
