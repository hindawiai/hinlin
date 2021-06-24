<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Maपूर्णांकain an RxRPC server socket to करो AFS communications through
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <net/sock.h>
#समावेश <net/af_rxrpc.h>
#समावेश "internal.h"
#समावेश "afs_cm.h"
#समावेश "protocol_yfs.h"

काष्ठा workqueue_काष्ठा *afs_async_calls;

अटल व्योम afs_wake_up_call_रुकोer(काष्ठा sock *, काष्ठा rxrpc_call *, अचिन्हित दीर्घ);
अटल व्योम afs_wake_up_async_call(काष्ठा sock *, काष्ठा rxrpc_call *, अचिन्हित दीर्घ);
अटल व्योम afs_process_async_call(काष्ठा work_काष्ठा *);
अटल व्योम afs_rx_new_call(काष्ठा sock *, काष्ठा rxrpc_call *, अचिन्हित दीर्घ);
अटल व्योम afs_rx_discard_new_call(काष्ठा rxrpc_call *, अचिन्हित दीर्घ);
अटल पूर्णांक afs_deliver_cm_op_id(काष्ठा afs_call *);

/* asynchronous incoming call initial processing */
अटल स्थिर काष्ठा afs_call_type afs_RXCMxxxx = अणु
	.name		= "CB.xxxx",
	.deliver	= afs_deliver_cm_op_id,
पूर्ण;

/*
 * खोलो an RxRPC socket and bind it to be a server क्रम callback notअगरications
 * - the socket is left in blocking mode and non-blocking ops use MSG_DONTWAIT
 */
पूर्णांक afs_खोलो_socket(काष्ठा afs_net *net)
अणु
	काष्ठा sockaddr_rxrpc srx;
	काष्ठा socket *socket;
	पूर्णांक ret;

	_enter("");

	ret = sock_create_kern(net->net, AF_RXRPC, SOCK_DGRAM, PF_INET6, &socket);
	अगर (ret < 0)
		जाओ error_1;

	socket->sk->sk_allocation = GFP_NOFS;

	/* bind the callback manager's address to make this a server socket */
	स_रखो(&srx, 0, माप(srx));
	srx.srx_family			= AF_RXRPC;
	srx.srx_service			= CM_SERVICE;
	srx.transport_type		= SOCK_DGRAM;
	srx.transport_len		= माप(srx.transport.sin6);
	srx.transport.sin6.sin6_family	= AF_INET6;
	srx.transport.sin6.sin6_port	= htons(AFS_CM_PORT);

	ret = rxrpc_sock_set_min_security_level(socket->sk,
						RXRPC_SECURITY_ENCRYPT);
	अगर (ret < 0)
		जाओ error_2;

	ret = kernel_bind(socket, (काष्ठा sockaddr *) &srx, माप(srx));
	अगर (ret == -EADDRINUSE) अणु
		srx.transport.sin6.sin6_port = 0;
		ret = kernel_bind(socket, (काष्ठा sockaddr *) &srx, माप(srx));
	पूर्ण
	अगर (ret < 0)
		जाओ error_2;

	srx.srx_service = YFS_CM_SERVICE;
	ret = kernel_bind(socket, (काष्ठा sockaddr *) &srx, माप(srx));
	अगर (ret < 0)
		जाओ error_2;

	/* Ideally, we'd turn on service upgrade here, but we can't because
	 * OpenAFS is buggy and leaks the userStatus field from packet to
	 * packet and between FS packets and CB packets - so अगर we try to करो an
	 * upgrade on an FS packet, OpenAFS will leak that पूर्णांकo the CB packet
	 * it sends back to us.
	 */

	rxrpc_kernel_new_call_notअगरication(socket, afs_rx_new_call,
					   afs_rx_discard_new_call);

	ret = kernel_listen(socket, पूर्णांक_उच्च);
	अगर (ret < 0)
		जाओ error_2;

	net->socket = socket;
	afs_अक्षरge_pपुनः_स्मृतिation(&net->अक्षरge_pपुनः_स्मृतिation_work);
	_leave(" = 0");
	वापस 0;

error_2:
	sock_release(socket);
error_1:
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * बंद the RxRPC socket AFS was using
 */
व्योम afs_बंद_socket(काष्ठा afs_net *net)
अणु
	_enter("");

	kernel_listen(net->socket, 0);
	flush_workqueue(afs_async_calls);

	अगर (net->spare_incoming_call) अणु
		afs_put_call(net->spare_incoming_call);
		net->spare_incoming_call = शून्य;
	पूर्ण

	_debug("outstanding %u", atomic_पढ़ो(&net->nr_outstanding_calls));
	रुको_var_event(&net->nr_outstanding_calls,
		       !atomic_पढ़ो(&net->nr_outstanding_calls));
	_debug("no outstanding calls");

	kernel_sock_shutकरोwn(net->socket, SHUT_RDWR);
	flush_workqueue(afs_async_calls);
	sock_release(net->socket);

	_debug("dework");
	_leave("");
पूर्ण

/*
 * Allocate a call.
 */
अटल काष्ठा afs_call *afs_alloc_call(काष्ठा afs_net *net,
				       स्थिर काष्ठा afs_call_type *type,
				       gfp_t gfp)
अणु
	काष्ठा afs_call *call;
	पूर्णांक o;

	call = kzalloc(माप(*call), gfp);
	अगर (!call)
		वापस शून्य;

	call->type = type;
	call->net = net;
	call->debug_id = atomic_inc_वापस(&rxrpc_debug_id);
	atomic_set(&call->usage, 1);
	INIT_WORK(&call->async_work, afs_process_async_call);
	init_रुकोqueue_head(&call->रुकोq);
	spin_lock_init(&call->state_lock);
	call->iter = &call->def_iter;

	o = atomic_inc_वापस(&net->nr_outstanding_calls);
	trace_afs_call(call, afs_call_trace_alloc, 1, o,
		       __builtin_वापस_address(0));
	वापस call;
पूर्ण

/*
 * Dispose of a reference on a call.
 */
व्योम afs_put_call(काष्ठा afs_call *call)
अणु
	काष्ठा afs_net *net = call->net;
	पूर्णांक n = atomic_dec_वापस(&call->usage);
	पूर्णांक o = atomic_पढ़ो(&net->nr_outstanding_calls);

	trace_afs_call(call, afs_call_trace_put, n, o,
		       __builtin_वापस_address(0));

	ASSERTCMP(n, >=, 0);
	अगर (n == 0) अणु
		ASSERT(!work_pending(&call->async_work));
		ASSERT(call->type->name != शून्य);

		अगर (call->rxcall) अणु
			rxrpc_kernel_end_call(net->socket, call->rxcall);
			call->rxcall = शून्य;
		पूर्ण
		अगर (call->type->deकाष्ठाor)
			call->type->deकाष्ठाor(call);

		afs_unuse_server_noसमय(call->net, call->server, afs_server_trace_put_call);
		afs_put_addrlist(call->alist);
		kमुक्त(call->request);

		trace_afs_call(call, afs_call_trace_मुक्त, 0, o,
			       __builtin_वापस_address(0));
		kमुक्त(call);

		o = atomic_dec_वापस(&net->nr_outstanding_calls);
		अगर (o == 0)
			wake_up_var(&net->nr_outstanding_calls);
	पूर्ण
पूर्ण

अटल काष्ठा afs_call *afs_get_call(काष्ठा afs_call *call,
				     क्रमागत afs_call_trace why)
अणु
	पूर्णांक u = atomic_inc_वापस(&call->usage);

	trace_afs_call(call, why, u,
		       atomic_पढ़ो(&call->net->nr_outstanding_calls),
		       __builtin_वापस_address(0));
	वापस call;
पूर्ण

/*
 * Queue the call क्रम actual work.
 */
अटल व्योम afs_queue_call_work(काष्ठा afs_call *call)
अणु
	अगर (call->type->work) अणु
		INIT_WORK(&call->work, call->type->work);

		afs_get_call(call, afs_call_trace_work);
		अगर (!queue_work(afs_wq, &call->work))
			afs_put_call(call);
	पूर्ण
पूर्ण

/*
 * allocate a call with flat request and reply buffers
 */
काष्ठा afs_call *afs_alloc_flat_call(काष्ठा afs_net *net,
				     स्थिर काष्ठा afs_call_type *type,
				     माप_प्रकार request_size, माप_प्रकार reply_max)
अणु
	काष्ठा afs_call *call;

	call = afs_alloc_call(net, type, GFP_NOFS);
	अगर (!call)
		जाओ nomem_call;

	अगर (request_size) अणु
		call->request_size = request_size;
		call->request = kदो_स्मृति(request_size, GFP_NOFS);
		अगर (!call->request)
			जाओ nomem_मुक्त;
	पूर्ण

	अगर (reply_max) अणु
		call->reply_max = reply_max;
		call->buffer = kदो_स्मृति(reply_max, GFP_NOFS);
		अगर (!call->buffer)
			जाओ nomem_मुक्त;
	पूर्ण

	afs_extract_to_buf(call, call->reply_max);
	call->operation_ID = type->op;
	init_रुकोqueue_head(&call->रुकोq);
	वापस call;

nomem_मुक्त:
	afs_put_call(call);
nomem_call:
	वापस शून्य;
पूर्ण

/*
 * clean up a call with flat buffer
 */
व्योम afs_flat_call_deकाष्ठाor(काष्ठा afs_call *call)
अणु
	_enter("");

	kमुक्त(call->request);
	call->request = शून्य;
	kमुक्त(call->buffer);
	call->buffer = शून्य;
पूर्ण

/*
 * Advance the AFS call state when the RxRPC call ends the transmit phase.
 */
अटल व्योम afs_notअगरy_end_request_tx(काष्ठा sock *sock,
				      काष्ठा rxrpc_call *rxcall,
				      अचिन्हित दीर्घ call_user_ID)
अणु
	काष्ठा afs_call *call = (काष्ठा afs_call *)call_user_ID;

	afs_set_call_state(call, AFS_CALL_CL_REQUESTING, AFS_CALL_CL_AWAIT_REPLY);
पूर्ण

/*
 * Initiate a call and synchronously queue up the parameters क्रम dispatch.  Any
 * error is stored पूर्णांकo the call काष्ठा, which the caller must check क्रम.
 */
व्योम afs_make_call(काष्ठा afs_addr_cursor *ac, काष्ठा afs_call *call, gfp_t gfp)
अणु
	काष्ठा sockaddr_rxrpc *srx = &ac->alist->addrs[ac->index];
	काष्ठा rxrpc_call *rxcall;
	काष्ठा msghdr msg;
	काष्ठा kvec iov[1];
	माप_प्रकार len;
	s64 tx_total_len;
	पूर्णांक ret;

	_enter(",{%pISp},", &srx->transport);

	ASSERT(call->type != शून्य);
	ASSERT(call->type->name != शून्य);

	_debug("____MAKE %p{%s,%x} [%d]____",
	       call, call->type->name, key_serial(call->key),
	       atomic_पढ़ो(&call->net->nr_outstanding_calls));

	call->addr_ix = ac->index;
	call->alist = afs_get_addrlist(ac->alist);

	/* Work out the length we're going to transmit.  This is awkward क्रम
	 * calls such as FS.StoreData where there's an extra injection of data
	 * after the initial fixed part.
	 */
	tx_total_len = call->request_size;
	अगर (call->ग_लिखो_iter)
		tx_total_len += iov_iter_count(call->ग_लिखो_iter);

	/* If the call is going to be asynchronous, we need an extra ref क्रम
	 * the call to hold itself so the caller need not hang on to its ref.
	 */
	अगर (call->async) अणु
		afs_get_call(call, afs_call_trace_get);
		call->drop_ref = true;
	पूर्ण

	/* create a call */
	rxcall = rxrpc_kernel_begin_call(call->net->socket, srx, call->key,
					 (अचिन्हित दीर्घ)call,
					 tx_total_len, gfp,
					 (call->async ?
					  afs_wake_up_async_call :
					  afs_wake_up_call_रुकोer),
					 call->upgrade,
					 (call->पूर्णांकr ? RXRPC_PREINTERRUPTIBLE :
					  RXRPC_UNINTERRUPTIBLE),
					 call->debug_id);
	अगर (IS_ERR(rxcall)) अणु
		ret = PTR_ERR(rxcall);
		call->error = ret;
		जाओ error_समाप्त_call;
	पूर्ण

	call->rxcall = rxcall;

	अगर (call->max_lअगरespan)
		rxrpc_kernel_set_max_lअगरe(call->net->socket, rxcall,
					  call->max_lअगरespan);

	/* send the request */
	iov[0].iov_base	= call->request;
	iov[0].iov_len	= call->request_size;

	msg.msg_name		= शून्य;
	msg.msg_namelen		= 0;
	iov_iter_kvec(&msg.msg_iter, WRITE, iov, 1, call->request_size);
	msg.msg_control		= शून्य;
	msg.msg_controllen	= 0;
	msg.msg_flags		= MSG_WAITALL | (call->ग_लिखो_iter ? MSG_MORE : 0);

	ret = rxrpc_kernel_send_data(call->net->socket, rxcall,
				     &msg, call->request_size,
				     afs_notअगरy_end_request_tx);
	अगर (ret < 0)
		जाओ error_करो_पात;

	अगर (call->ग_लिखो_iter) अणु
		msg.msg_iter = *call->ग_लिखो_iter;
		msg.msg_flags &= ~MSG_MORE;
		trace_afs_send_data(call, &msg);

		ret = rxrpc_kernel_send_data(call->net->socket,
					     call->rxcall, &msg,
					     iov_iter_count(&msg.msg_iter),
					     afs_notअगरy_end_request_tx);
		*call->ग_लिखो_iter = msg.msg_iter;

		trace_afs_sent_data(call, &msg, ret);
		अगर (ret < 0)
			जाओ error_करो_पात;
	पूर्ण

	/* Note that at this poपूर्णांक, we may have received the reply or an पात
	 * - and an asynchronous call may alपढ़ोy have completed.
	 *
	 * afs_रुको_क्रम_call_to_complete(call, ac)
	 * must be called to synchronously clean up.
	 */
	वापस;

error_करो_पात:
	अगर (ret != -ECONNABORTED) अणु
		rxrpc_kernel_पात_call(call->net->socket, rxcall,
					RX_USER_ABORT, ret, "KSD");
	पूर्ण अन्यथा अणु
		len = 0;
		iov_iter_kvec(&msg.msg_iter, READ, शून्य, 0, 0);
		rxrpc_kernel_recv_data(call->net->socket, rxcall,
				       &msg.msg_iter, &len, false,
				       &call->पात_code, &call->service_id);
		ac->पात_code = call->पात_code;
		ac->responded = true;
	पूर्ण
	call->error = ret;
	trace_afs_call_करोne(call);
error_समाप्त_call:
	अगर (call->type->करोne)
		call->type->करोne(call);

	/* We need to dispose of the extra ref we grabbed क्रम an async call.
	 * The call, however, might be queued on afs_async_calls and we need to
	 * make sure we करोn't get any more notअगरications that might requeue it.
	 */
	अगर (call->rxcall) अणु
		rxrpc_kernel_end_call(call->net->socket, call->rxcall);
		call->rxcall = शून्य;
	पूर्ण
	अगर (call->async) अणु
		अगर (cancel_work_sync(&call->async_work))
			afs_put_call(call);
		afs_put_call(call);
	पूर्ण

	ac->error = ret;
	call->state = AFS_CALL_COMPLETE;
	_leave(" = %d", ret);
पूर्ण

/*
 * Log remote पात codes that indicate that we have a protocol disagreement
 * with the server.
 */
अटल व्योम afs_log_error(काष्ठा afs_call *call, s32 remote_पात)
अणु
	अटल पूर्णांक max = 0;
	स्थिर अक्षर *msg;
	पूर्णांक m;

	चयन (remote_पात) अणु
	हाल RX_खातापूर्ण:		 msg = "unexpected EOF";	अवरोध;
	हाल RXGEN_CC_MARSHAL:	 msg = "client marshalling";	अवरोध;
	हाल RXGEN_CC_UNMARSHAL: msg = "client unmarshalling";	अवरोध;
	हाल RXGEN_SS_MARSHAL:	 msg = "server marshalling";	अवरोध;
	हाल RXGEN_SS_UNMARSHAL: msg = "server unmarshalling";	अवरोध;
	हाल RXGEN_DECODE:	 msg = "opcode decode";		अवरोध;
	हाल RXGEN_SS_XDRFREE:	 msg = "server XDR cleanup";	अवरोध;
	हाल RXGEN_CC_XDRFREE:	 msg = "client XDR cleanup";	अवरोध;
	हाल -32:		 msg = "insufficient data";	अवरोध;
	शेष:
		वापस;
	पूर्ण

	m = max;
	अगर (m < 3) अणु
		max = m + 1;
		pr_notice("kAFS: Peer reported %s failure on %s [%pISp]\n",
			  msg, call->type->name,
			  &call->alist->addrs[call->addr_ix].transport);
	पूर्ण
पूर्ण

/*
 * deliver messages to a call
 */
अटल व्योम afs_deliver_to_call(काष्ठा afs_call *call)
अणु
	क्रमागत afs_call_state state;
	माप_प्रकार len;
	u32 पात_code, remote_पात = 0;
	पूर्णांक ret;

	_enter("%s", call->type->name);

	जबतक (state = READ_ONCE(call->state),
	       state == AFS_CALL_CL_AWAIT_REPLY ||
	       state == AFS_CALL_SV_AWAIT_OP_ID ||
	       state == AFS_CALL_SV_AWAIT_REQUEST ||
	       state == AFS_CALL_SV_AWAIT_ACK
	       ) अणु
		अगर (state == AFS_CALL_SV_AWAIT_ACK) अणु
			len = 0;
			iov_iter_kvec(&call->def_iter, READ, शून्य, 0, 0);
			ret = rxrpc_kernel_recv_data(call->net->socket,
						     call->rxcall, &call->def_iter,
						     &len, false, &remote_पात,
						     &call->service_id);
			trace_afs_receive_data(call, &call->def_iter, false, ret);

			अगर (ret == -EINPROGRESS || ret == -EAGAIN)
				वापस;
			अगर (ret < 0 || ret == 1) अणु
				अगर (ret == 1)
					ret = 0;
				जाओ call_complete;
			पूर्ण
			वापस;
		पूर्ण

		अगर (!call->have_reply_समय &&
		    rxrpc_kernel_get_reply_समय(call->net->socket,
						call->rxcall,
						&call->reply_समय))
			call->have_reply_समय = true;

		ret = call->type->deliver(call);
		state = READ_ONCE(call->state);
		अगर (ret == 0 && call->unmarshalling_error)
			ret = -EBADMSG;
		चयन (ret) अणु
		हाल 0:
			afs_queue_call_work(call);
			अगर (state == AFS_CALL_CL_PROC_REPLY) अणु
				अगर (call->op)
					set_bit(AFS_SERVER_FL_MAY_HAVE_CB,
						&call->op->server->flags);
				जाओ call_complete;
			पूर्ण
			ASSERTCMP(state, >, AFS_CALL_CL_PROC_REPLY);
			जाओ करोne;
		हाल -EINPROGRESS:
		हाल -EAGAIN:
			जाओ out;
		हाल -ECONNABORTED:
			ASSERTCMP(state, ==, AFS_CALL_COMPLETE);
			afs_log_error(call, call->पात_code);
			जाओ करोne;
		हाल -ENOTSUPP:
			पात_code = RXGEN_OPCODE;
			rxrpc_kernel_पात_call(call->net->socket, call->rxcall,
						पात_code, ret, "KIV");
			जाओ local_पात;
		हाल -EIO:
			pr_err("kAFS: Call %u in bad state %u\n",
			       call->debug_id, state);
			fallthrough;
		हाल -ENODATA:
		हाल -EBADMSG:
		हाल -EMSGSIZE:
			पात_code = RXGEN_CC_UNMARSHAL;
			अगर (state != AFS_CALL_CL_AWAIT_REPLY)
				पात_code = RXGEN_SS_UNMARSHAL;
			rxrpc_kernel_पात_call(call->net->socket, call->rxcall,
						पात_code, ret, "KUM");
			जाओ local_पात;
		शेष:
			पात_code = RX_USER_ABORT;
			rxrpc_kernel_पात_call(call->net->socket, call->rxcall,
						पात_code, ret, "KER");
			जाओ local_पात;
		पूर्ण
	पूर्ण

करोne:
	अगर (call->type->करोne)
		call->type->करोne(call);
out:
	_leave("");
	वापस;

local_पात:
	पात_code = 0;
call_complete:
	afs_set_call_complete(call, ret, remote_पात);
	state = AFS_CALL_COMPLETE;
	जाओ करोne;
पूर्ण

/*
 * Wait synchronously क्रम a call to complete and clean up the call काष्ठा.
 */
दीर्घ afs_रुको_क्रम_call_to_complete(काष्ठा afs_call *call,
				   काष्ठा afs_addr_cursor *ac)
अणु
	दीर्घ ret;
	bool rxrpc_complete = false;

	DECLARE_WAITQUEUE(myself, current);

	_enter("");

	ret = call->error;
	अगर (ret < 0)
		जाओ out;

	add_रुको_queue(&call->रुकोq, &myself);
	क्रम (;;) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);

		/* deliver any messages that are in the queue */
		अगर (!afs_check_call_state(call, AFS_CALL_COMPLETE) &&
		    call->need_attention) अणु
			call->need_attention = false;
			__set_current_state(TASK_RUNNING);
			afs_deliver_to_call(call);
			जारी;
		पूर्ण

		अगर (afs_check_call_state(call, AFS_CALL_COMPLETE))
			अवरोध;

		अगर (!rxrpc_kernel_check_lअगरe(call->net->socket, call->rxcall)) अणु
			/* rxrpc terminated the call. */
			rxrpc_complete = true;
			अवरोध;
		पूर्ण

		schedule();
	पूर्ण

	हटाओ_रुको_queue(&call->रुकोq, &myself);
	__set_current_state(TASK_RUNNING);

	अगर (!afs_check_call_state(call, AFS_CALL_COMPLETE)) अणु
		अगर (rxrpc_complete) अणु
			afs_set_call_complete(call, call->error, call->पात_code);
		पूर्ण अन्यथा अणु
			/* Kill off the call अगर it's still live. */
			_debug("call interrupted");
			अगर (rxrpc_kernel_पात_call(call->net->socket, call->rxcall,
						    RX_USER_ABORT, -EINTR, "KWI"))
				afs_set_call_complete(call, -EINTR, 0);
		पूर्ण
	पूर्ण

	spin_lock_bh(&call->state_lock);
	ac->पात_code = call->पात_code;
	ac->error = call->error;
	spin_unlock_bh(&call->state_lock);

	ret = ac->error;
	चयन (ret) अणु
	हाल 0:
		ret = call->ret0;
		call->ret0 = 0;

		fallthrough;
	हाल -ECONNABORTED:
		ac->responded = true;
		अवरोध;
	पूर्ण

out:
	_debug("call complete");
	afs_put_call(call);
	_leave(" = %p", (व्योम *)ret);
	वापस ret;
पूर्ण

/*
 * wake up a रुकोing call
 */
अटल व्योम afs_wake_up_call_रुकोer(काष्ठा sock *sk, काष्ठा rxrpc_call *rxcall,
				    अचिन्हित दीर्घ call_user_ID)
अणु
	काष्ठा afs_call *call = (काष्ठा afs_call *)call_user_ID;

	call->need_attention = true;
	wake_up(&call->रुकोq);
पूर्ण

/*
 * wake up an asynchronous call
 */
अटल व्योम afs_wake_up_async_call(काष्ठा sock *sk, काष्ठा rxrpc_call *rxcall,
				   अचिन्हित दीर्घ call_user_ID)
अणु
	काष्ठा afs_call *call = (काष्ठा afs_call *)call_user_ID;
	पूर्णांक u;

	trace_afs_notअगरy_call(rxcall, call);
	call->need_attention = true;

	u = atomic_fetch_add_unless(&call->usage, 1, 0);
	अगर (u != 0) अणु
		trace_afs_call(call, afs_call_trace_wake, u + 1,
			       atomic_पढ़ो(&call->net->nr_outstanding_calls),
			       __builtin_वापस_address(0));

		अगर (!queue_work(afs_async_calls, &call->async_work))
			afs_put_call(call);
	पूर्ण
पूर्ण

/*
 * Perक्रमm I/O processing on an asynchronous call.  The work item carries a ref
 * to the call काष्ठा that we either need to release or to pass on.
 */
अटल व्योम afs_process_async_call(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा afs_call *call = container_of(work, काष्ठा afs_call, async_work);

	_enter("");

	अगर (call->state < AFS_CALL_COMPLETE && call->need_attention) अणु
		call->need_attention = false;
		afs_deliver_to_call(call);
	पूर्ण

	afs_put_call(call);
	_leave("");
पूर्ण

अटल व्योम afs_rx_attach(काष्ठा rxrpc_call *rxcall, अचिन्हित दीर्घ user_call_ID)
अणु
	काष्ठा afs_call *call = (काष्ठा afs_call *)user_call_ID;

	call->rxcall = rxcall;
पूर्ण

/*
 * Charge the incoming call pपुनः_स्मृतिation.
 */
व्योम afs_अक्षरge_pपुनः_स्मृतिation(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा afs_net *net =
		container_of(work, काष्ठा afs_net, अक्षरge_pपुनः_स्मृतिation_work);
	काष्ठा afs_call *call = net->spare_incoming_call;

	क्रम (;;) अणु
		अगर (!call) अणु
			call = afs_alloc_call(net, &afs_RXCMxxxx, GFP_KERNEL);
			अगर (!call)
				अवरोध;

			call->drop_ref = true;
			call->async = true;
			call->state = AFS_CALL_SV_AWAIT_OP_ID;
			init_रुकोqueue_head(&call->रुकोq);
			afs_extract_to_पंचांगp(call);
		पूर्ण

		अगर (rxrpc_kernel_अक्षरge_accept(net->socket,
					       afs_wake_up_async_call,
					       afs_rx_attach,
					       (अचिन्हित दीर्घ)call,
					       GFP_KERNEL,
					       call->debug_id) < 0)
			अवरोध;
		call = शून्य;
	पूर्ण
	net->spare_incoming_call = call;
पूर्ण

/*
 * Discard a pपुनः_स्मृतिated call when a socket is shut करोwn.
 */
अटल व्योम afs_rx_discard_new_call(काष्ठा rxrpc_call *rxcall,
				    अचिन्हित दीर्घ user_call_ID)
अणु
	काष्ठा afs_call *call = (काष्ठा afs_call *)user_call_ID;

	call->rxcall = शून्य;
	afs_put_call(call);
पूर्ण

/*
 * Notअगरication of an incoming call.
 */
अटल व्योम afs_rx_new_call(काष्ठा sock *sk, काष्ठा rxrpc_call *rxcall,
			    अचिन्हित दीर्घ user_call_ID)
अणु
	काष्ठा afs_net *net = afs_sock2net(sk);

	queue_work(afs_wq, &net->अक्षरge_pपुनः_स्मृतिation_work);
पूर्ण

/*
 * Grab the operation ID from an incoming cache manager call.  The socket
 * buffer is discarded on error or अगर we करोn't yet have sufficient data.
 */
अटल पूर्णांक afs_deliver_cm_op_id(काष्ठा afs_call *call)
अणु
	पूर्णांक ret;

	_enter("{%zu}", iov_iter_count(call->iter));

	/* the operation ID क्रमms the first four bytes of the request data */
	ret = afs_extract_data(call, true);
	अगर (ret < 0)
		वापस ret;

	call->operation_ID = ntohl(call->पंचांगp);
	afs_set_call_state(call, AFS_CALL_SV_AWAIT_OP_ID, AFS_CALL_SV_AWAIT_REQUEST);

	/* ask the cache manager to route the call (it'll change the call type
	 * अगर successful) */
	अगर (!afs_cm_incoming_call(call))
		वापस -ENOTSUPP;

	trace_afs_cb_call(call);

	/* pass responsibility क्रम the reमुख्यer of this message off to the
	 * cache manager op */
	वापस call->type->deliver(call);
पूर्ण

/*
 * Advance the AFS call state when an RxRPC service call ends the transmit
 * phase.
 */
अटल व्योम afs_notअगरy_end_reply_tx(काष्ठा sock *sock,
				    काष्ठा rxrpc_call *rxcall,
				    अचिन्हित दीर्घ call_user_ID)
अणु
	काष्ठा afs_call *call = (काष्ठा afs_call *)call_user_ID;

	afs_set_call_state(call, AFS_CALL_SV_REPLYING, AFS_CALL_SV_AWAIT_ACK);
पूर्ण

/*
 * send an empty reply
 */
व्योम afs_send_empty_reply(काष्ठा afs_call *call)
अणु
	काष्ठा afs_net *net = call->net;
	काष्ठा msghdr msg;

	_enter("");

	rxrpc_kernel_set_tx_length(net->socket, call->rxcall, 0);

	msg.msg_name		= शून्य;
	msg.msg_namelen		= 0;
	iov_iter_kvec(&msg.msg_iter, WRITE, शून्य, 0, 0);
	msg.msg_control		= शून्य;
	msg.msg_controllen	= 0;
	msg.msg_flags		= 0;

	चयन (rxrpc_kernel_send_data(net->socket, call->rxcall, &msg, 0,
				       afs_notअगरy_end_reply_tx)) अणु
	हाल 0:
		_leave(" [replied]");
		वापस;

	हाल -ENOMEM:
		_debug("oom");
		rxrpc_kernel_पात_call(net->socket, call->rxcall,
					RX_USER_ABORT, -ENOMEM, "KOO");
		fallthrough;
	शेष:
		_leave(" [error]");
		वापस;
	पूर्ण
पूर्ण

/*
 * send a simple reply
 */
व्योम afs_send_simple_reply(काष्ठा afs_call *call, स्थिर व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा afs_net *net = call->net;
	काष्ठा msghdr msg;
	काष्ठा kvec iov[1];
	पूर्णांक n;

	_enter("");

	rxrpc_kernel_set_tx_length(net->socket, call->rxcall, len);

	iov[0].iov_base		= (व्योम *) buf;
	iov[0].iov_len		= len;
	msg.msg_name		= शून्य;
	msg.msg_namelen		= 0;
	iov_iter_kvec(&msg.msg_iter, WRITE, iov, 1, len);
	msg.msg_control		= शून्य;
	msg.msg_controllen	= 0;
	msg.msg_flags		= 0;

	n = rxrpc_kernel_send_data(net->socket, call->rxcall, &msg, len,
				   afs_notअगरy_end_reply_tx);
	अगर (n >= 0) अणु
		/* Success */
		_leave(" [replied]");
		वापस;
	पूर्ण

	अगर (n == -ENOMEM) अणु
		_debug("oom");
		rxrpc_kernel_पात_call(net->socket, call->rxcall,
					RX_USER_ABORT, -ENOMEM, "KOO");
	पूर्ण
	_leave(" [error]");
पूर्ण

/*
 * Extract a piece of data from the received data socket buffers.
 */
पूर्णांक afs_extract_data(काष्ठा afs_call *call, bool want_more)
अणु
	काष्ठा afs_net *net = call->net;
	काष्ठा iov_iter *iter = call->iter;
	क्रमागत afs_call_state state;
	u32 remote_पात = 0;
	पूर्णांक ret;

	_enter("{%s,%zu,%zu},%d",
	       call->type->name, call->iov_len, iov_iter_count(iter), want_more);

	ret = rxrpc_kernel_recv_data(net->socket, call->rxcall, iter,
				     &call->iov_len, want_more, &remote_पात,
				     &call->service_id);
	अगर (ret == 0 || ret == -EAGAIN)
		वापस ret;

	state = READ_ONCE(call->state);
	अगर (ret == 1) अणु
		चयन (state) अणु
		हाल AFS_CALL_CL_AWAIT_REPLY:
			afs_set_call_state(call, state, AFS_CALL_CL_PROC_REPLY);
			अवरोध;
		हाल AFS_CALL_SV_AWAIT_REQUEST:
			afs_set_call_state(call, state, AFS_CALL_SV_REPLYING);
			अवरोध;
		हाल AFS_CALL_COMPLETE:
			kdebug("prem complete %d", call->error);
			वापस afs_io_error(call, afs_io_error_extract);
		शेष:
			अवरोध;
		पूर्ण
		वापस 0;
	पूर्ण

	afs_set_call_complete(call, ret, remote_पात);
	वापस ret;
पूर्ण

/*
 * Log protocol error production.
 */
noअंतरभूत पूर्णांक afs_protocol_error(काष्ठा afs_call *call,
				क्रमागत afs_eproto_cause cause)
अणु
	trace_afs_protocol_error(call, cause);
	अगर (call)
		call->unmarshalling_error = true;
	वापस -EBADMSG;
पूर्ण
