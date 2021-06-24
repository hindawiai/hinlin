<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* AFS Cache Manager Service
 *
 * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/ip.h>
#समावेश "internal.h"
#समावेश "afs_cm.h"
#समावेश "protocol_yfs.h"

अटल पूर्णांक afs_deliver_cb_init_call_back_state(काष्ठा afs_call *);
अटल पूर्णांक afs_deliver_cb_init_call_back_state3(काष्ठा afs_call *);
अटल पूर्णांक afs_deliver_cb_probe(काष्ठा afs_call *);
अटल पूर्णांक afs_deliver_cb_callback(काष्ठा afs_call *);
अटल पूर्णांक afs_deliver_cb_probe_uuid(काष्ठा afs_call *);
अटल पूर्णांक afs_deliver_cb_tell_me_about_yourself(काष्ठा afs_call *);
अटल व्योम afs_cm_deकाष्ठाor(काष्ठा afs_call *);
अटल व्योम SRXAFSCB_CallBack(काष्ठा work_काष्ठा *);
अटल व्योम SRXAFSCB_InitCallBackState(काष्ठा work_काष्ठा *);
अटल व्योम SRXAFSCB_Probe(काष्ठा work_काष्ठा *);
अटल व्योम SRXAFSCB_ProbeUuid(काष्ठा work_काष्ठा *);
अटल व्योम SRXAFSCB_TellMeAboutYourself(काष्ठा work_काष्ठा *);

अटल पूर्णांक afs_deliver_yfs_cb_callback(काष्ठा afs_call *);

#घोषणा CM_NAME(name) \
	अक्षर afs_SRXCB##name##_name[] __tracepoपूर्णांक_string =	\
		"CB." #name

/*
 * CB.CallBack operation type
 */
अटल CM_NAME(CallBack);
अटल स्थिर काष्ठा afs_call_type afs_SRXCBCallBack = अणु
	.name		= afs_SRXCBCallBack_name,
	.deliver	= afs_deliver_cb_callback,
	.deकाष्ठाor	= afs_cm_deकाष्ठाor,
	.work		= SRXAFSCB_CallBack,
पूर्ण;

/*
 * CB.InitCallBackState operation type
 */
अटल CM_NAME(InitCallBackState);
अटल स्थिर काष्ठा afs_call_type afs_SRXCBInitCallBackState = अणु
	.name		= afs_SRXCBInitCallBackState_name,
	.deliver	= afs_deliver_cb_init_call_back_state,
	.deकाष्ठाor	= afs_cm_deकाष्ठाor,
	.work		= SRXAFSCB_InitCallBackState,
पूर्ण;

/*
 * CB.InitCallBackState3 operation type
 */
अटल CM_NAME(InitCallBackState3);
अटल स्थिर काष्ठा afs_call_type afs_SRXCBInitCallBackState3 = अणु
	.name		= afs_SRXCBInitCallBackState3_name,
	.deliver	= afs_deliver_cb_init_call_back_state3,
	.deकाष्ठाor	= afs_cm_deकाष्ठाor,
	.work		= SRXAFSCB_InitCallBackState,
पूर्ण;

/*
 * CB.Probe operation type
 */
अटल CM_NAME(Probe);
अटल स्थिर काष्ठा afs_call_type afs_SRXCBProbe = अणु
	.name		= afs_SRXCBProbe_name,
	.deliver	= afs_deliver_cb_probe,
	.deकाष्ठाor	= afs_cm_deकाष्ठाor,
	.work		= SRXAFSCB_Probe,
पूर्ण;

/*
 * CB.ProbeUuid operation type
 */
अटल CM_NAME(ProbeUuid);
अटल स्थिर काष्ठा afs_call_type afs_SRXCBProbeUuid = अणु
	.name		= afs_SRXCBProbeUuid_name,
	.deliver	= afs_deliver_cb_probe_uuid,
	.deकाष्ठाor	= afs_cm_deकाष्ठाor,
	.work		= SRXAFSCB_ProbeUuid,
पूर्ण;

/*
 * CB.TellMeAboutYourself operation type
 */
अटल CM_NAME(TellMeAboutYourself);
अटल स्थिर काष्ठा afs_call_type afs_SRXCBTellMeAboutYourself = अणु
	.name		= afs_SRXCBTellMeAboutYourself_name,
	.deliver	= afs_deliver_cb_tell_me_about_yourself,
	.deकाष्ठाor	= afs_cm_deकाष्ठाor,
	.work		= SRXAFSCB_TellMeAboutYourself,
पूर्ण;

/*
 * YFS CB.CallBack operation type
 */
अटल CM_NAME(YFS_CallBack);
अटल स्थिर काष्ठा afs_call_type afs_SRXYFSCB_CallBack = अणु
	.name		= afs_SRXCBYFS_CallBack_name,
	.deliver	= afs_deliver_yfs_cb_callback,
	.deकाष्ठाor	= afs_cm_deकाष्ठाor,
	.work		= SRXAFSCB_CallBack,
पूर्ण;

/*
 * route an incoming cache manager call
 * - वापस T अगर supported, F अगर not
 */
bool afs_cm_incoming_call(काष्ठा afs_call *call)
अणु
	_enter("{%u, CB.OP %u}", call->service_id, call->operation_ID);

	चयन (call->operation_ID) अणु
	हाल CBCallBack:
		call->type = &afs_SRXCBCallBack;
		वापस true;
	हाल CBInitCallBackState:
		call->type = &afs_SRXCBInitCallBackState;
		वापस true;
	हाल CBInitCallBackState3:
		call->type = &afs_SRXCBInitCallBackState3;
		वापस true;
	हाल CBProbe:
		call->type = &afs_SRXCBProbe;
		वापस true;
	हाल CBProbeUuid:
		call->type = &afs_SRXCBProbeUuid;
		वापस true;
	हाल CBTellMeAboutYourself:
		call->type = &afs_SRXCBTellMeAboutYourself;
		वापस true;
	हाल YFSCBCallBack:
		अगर (call->service_id != YFS_CM_SERVICE)
			वापस false;
		call->type = &afs_SRXYFSCB_CallBack;
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * Find the server record by peer address and record a probe to the cache
 * manager from a server.
 */
अटल पूर्णांक afs_find_cm_server_by_peer(काष्ठा afs_call *call)
अणु
	काष्ठा sockaddr_rxrpc srx;
	काष्ठा afs_server *server;

	rxrpc_kernel_get_peer(call->net->socket, call->rxcall, &srx);

	server = afs_find_server(call->net, &srx);
	अगर (!server) अणु
		trace_afs_cm_no_server(call, &srx);
		वापस 0;
	पूर्ण

	call->server = server;
	वापस 0;
पूर्ण

/*
 * Find the server record by server UUID and record a probe to the cache
 * manager from a server.
 */
अटल पूर्णांक afs_find_cm_server_by_uuid(काष्ठा afs_call *call,
				      काष्ठा afs_uuid *uuid)
अणु
	काष्ठा afs_server *server;

	rcu_पढ़ो_lock();
	server = afs_find_server_by_uuid(call->net, call->request);
	rcu_पढ़ो_unlock();
	अगर (!server) अणु
		trace_afs_cm_no_server_u(call, call->request);
		वापस 0;
	पूर्ण

	call->server = server;
	वापस 0;
पूर्ण

/*
 * Clean up a cache manager call.
 */
अटल व्योम afs_cm_deकाष्ठाor(काष्ठा afs_call *call)
अणु
	kमुक्त(call->buffer);
	call->buffer = शून्य;
पूर्ण

/*
 * Abort a service call from within an action function.
 */
अटल व्योम afs_पात_service_call(काष्ठा afs_call *call, u32 पात_code, पूर्णांक error,
				   स्थिर अक्षर *why)
अणु
	rxrpc_kernel_पात_call(call->net->socket, call->rxcall,
				पात_code, error, why);
	afs_set_call_complete(call, error, 0);
पूर्ण

/*
 * The server supplied a list of callbacks that it wanted to अवरोध.
 */
अटल व्योम SRXAFSCB_CallBack(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा afs_call *call = container_of(work, काष्ठा afs_call, work);

	_enter("");

	/* We need to अवरोध the callbacks beक्रमe sending the reply as the
	 * server holds up change visibility till it receives our reply so as
	 * to मुख्यtain cache coherency.
	 */
	अगर (call->server) अणु
		trace_afs_server(call->server,
				 atomic_पढ़ो(&call->server->ref),
				 atomic_पढ़ो(&call->server->active),
				 afs_server_trace_callback);
		afs_अवरोध_callbacks(call->server, call->count, call->request);
	पूर्ण

	afs_send_empty_reply(call);
	afs_put_call(call);
	_leave("");
पूर्ण

/*
 * deliver request data to a CB.CallBack call
 */
अटल पूर्णांक afs_deliver_cb_callback(काष्ठा afs_call *call)
अणु
	काष्ठा afs_callback_अवरोध *cb;
	__be32 *bp;
	पूर्णांक ret, loop;

	_enter("{%u}", call->unmarshall);

	चयन (call->unmarshall) अणु
	हाल 0:
		afs_extract_to_पंचांगp(call);
		call->unmarshall++;

		/* extract the FID array and its count in two steps */
		fallthrough;
	हाल 1:
		_debug("extract FID count");
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		call->count = ntohl(call->पंचांगp);
		_debug("FID count: %u", call->count);
		अगर (call->count > AFSCBMAX)
			वापस afs_protocol_error(call, afs_eproto_cb_fid_count);

		call->buffer = kदो_स्मृति(array3_size(call->count, 3, 4),
				       GFP_KERNEL);
		अगर (!call->buffer)
			वापस -ENOMEM;
		afs_extract_to_buf(call, call->count * 3 * 4);
		call->unmarshall++;

		fallthrough;
	हाल 2:
		_debug("extract FID array");
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		_debug("unmarshall FID array");
		call->request = kसुस्मृति(call->count,
					माप(काष्ठा afs_callback_अवरोध),
					GFP_KERNEL);
		अगर (!call->request)
			वापस -ENOMEM;

		cb = call->request;
		bp = call->buffer;
		क्रम (loop = call->count; loop > 0; loop--, cb++) अणु
			cb->fid.vid	= ntohl(*bp++);
			cb->fid.vnode	= ntohl(*bp++);
			cb->fid.unique	= ntohl(*bp++);
		पूर्ण

		afs_extract_to_पंचांगp(call);
		call->unmarshall++;

		/* extract the callback array and its count in two steps */
		fallthrough;
	हाल 3:
		_debug("extract CB count");
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		call->count2 = ntohl(call->पंचांगp);
		_debug("CB count: %u", call->count2);
		अगर (call->count2 != call->count && call->count2 != 0)
			वापस afs_protocol_error(call, afs_eproto_cb_count);
		call->iter = &call->def_iter;
		iov_iter_discard(&call->def_iter, READ, call->count2 * 3 * 4);
		call->unmarshall++;

		fallthrough;
	हाल 4:
		_debug("extract discard %zu/%u",
		       iov_iter_count(call->iter), call->count2 * 3 * 4);

		ret = afs_extract_data(call, false);
		अगर (ret < 0)
			वापस ret;

		call->unmarshall++;
		fallthrough;

	हाल 5:
		अवरोध;
	पूर्ण

	अगर (!afs_check_call_state(call, AFS_CALL_SV_REPLYING))
		वापस afs_io_error(call, afs_io_error_cm_reply);

	/* we'll need the file server record as that tells us which set of
	 * vnodes to operate upon */
	वापस afs_find_cm_server_by_peer(call);
पूर्ण

/*
 * allow the fileserver to request callback state (re-)initialisation
 */
अटल व्योम SRXAFSCB_InitCallBackState(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा afs_call *call = container_of(work, काष्ठा afs_call, work);

	_enter("{%p}", call->server);

	अगर (call->server)
		afs_init_callback_state(call->server);
	afs_send_empty_reply(call);
	afs_put_call(call);
	_leave("");
पूर्ण

/*
 * deliver request data to a CB.InitCallBackState call
 */
अटल पूर्णांक afs_deliver_cb_init_call_back_state(काष्ठा afs_call *call)
अणु
	पूर्णांक ret;

	_enter("");

	afs_extract_discard(call, 0);
	ret = afs_extract_data(call, false);
	अगर (ret < 0)
		वापस ret;

	/* we'll need the file server record as that tells us which set of
	 * vnodes to operate upon */
	वापस afs_find_cm_server_by_peer(call);
पूर्ण

/*
 * deliver request data to a CB.InitCallBackState3 call
 */
अटल पूर्णांक afs_deliver_cb_init_call_back_state3(काष्ठा afs_call *call)
अणु
	काष्ठा afs_uuid *r;
	अचिन्हित loop;
	__be32 *b;
	पूर्णांक ret;

	_enter("");

	_enter("{%u}", call->unmarshall);

	चयन (call->unmarshall) अणु
	हाल 0:
		call->buffer = kदो_स्मृति_array(11, माप(__be32), GFP_KERNEL);
		अगर (!call->buffer)
			वापस -ENOMEM;
		afs_extract_to_buf(call, 11 * माप(__be32));
		call->unmarshall++;

		fallthrough;
	हाल 1:
		_debug("extract UUID");
		ret = afs_extract_data(call, false);
		चयन (ret) अणु
		हाल 0:		अवरोध;
		हाल -EAGAIN:	वापस 0;
		शेष:	वापस ret;
		पूर्ण

		_debug("unmarshall UUID");
		call->request = kदो_स्मृति(माप(काष्ठा afs_uuid), GFP_KERNEL);
		अगर (!call->request)
			वापस -ENOMEM;

		b = call->buffer;
		r = call->request;
		r->समय_low			= b[0];
		r->समय_mid			= htons(ntohl(b[1]));
		r->समय_hi_and_version		= htons(ntohl(b[2]));
		r->घड़ी_seq_hi_and_reserved 	= ntohl(b[3]);
		r->घड़ी_seq_low		= ntohl(b[4]);

		क्रम (loop = 0; loop < 6; loop++)
			r->node[loop] = ntohl(b[loop + 5]);

		call->unmarshall++;
		fallthrough;

	हाल 2:
		अवरोध;
	पूर्ण

	अगर (!afs_check_call_state(call, AFS_CALL_SV_REPLYING))
		वापस afs_io_error(call, afs_io_error_cm_reply);

	/* we'll need the file server record as that tells us which set of
	 * vnodes to operate upon */
	वापस afs_find_cm_server_by_uuid(call, call->request);
पूर्ण

/*
 * allow the fileserver to see अगर the cache manager is still alive
 */
अटल व्योम SRXAFSCB_Probe(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा afs_call *call = container_of(work, काष्ठा afs_call, work);

	_enter("");
	afs_send_empty_reply(call);
	afs_put_call(call);
	_leave("");
पूर्ण

/*
 * deliver request data to a CB.Probe call
 */
अटल पूर्णांक afs_deliver_cb_probe(काष्ठा afs_call *call)
अणु
	पूर्णांक ret;

	_enter("");

	afs_extract_discard(call, 0);
	ret = afs_extract_data(call, false);
	अगर (ret < 0)
		वापस ret;

	अगर (!afs_check_call_state(call, AFS_CALL_SV_REPLYING))
		वापस afs_io_error(call, afs_io_error_cm_reply);
	वापस afs_find_cm_server_by_peer(call);
पूर्ण

/*
 * Allow the fileserver to quickly find out अगर the cache manager has been
 * rebooted.
 */
अटल व्योम SRXAFSCB_ProbeUuid(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा afs_call *call = container_of(work, काष्ठा afs_call, work);
	काष्ठा afs_uuid *r = call->request;

	_enter("");

	अगर (स_भेद(r, &call->net->uuid, माप(call->net->uuid)) == 0)
		afs_send_empty_reply(call);
	अन्यथा
		afs_पात_service_call(call, 1, 1, "K-1");

	afs_put_call(call);
	_leave("");
पूर्ण

/*
 * deliver request data to a CB.ProbeUuid call
 */
अटल पूर्णांक afs_deliver_cb_probe_uuid(काष्ठा afs_call *call)
अणु
	काष्ठा afs_uuid *r;
	अचिन्हित loop;
	__be32 *b;
	पूर्णांक ret;

	_enter("{%u}", call->unmarshall);

	चयन (call->unmarshall) अणु
	हाल 0:
		call->buffer = kदो_स्मृति_array(11, माप(__be32), GFP_KERNEL);
		अगर (!call->buffer)
			वापस -ENOMEM;
		afs_extract_to_buf(call, 11 * माप(__be32));
		call->unmarshall++;

		fallthrough;
	हाल 1:
		_debug("extract UUID");
		ret = afs_extract_data(call, false);
		चयन (ret) अणु
		हाल 0:		अवरोध;
		हाल -EAGAIN:	वापस 0;
		शेष:	वापस ret;
		पूर्ण

		_debug("unmarshall UUID");
		call->request = kदो_स्मृति(माप(काष्ठा afs_uuid), GFP_KERNEL);
		अगर (!call->request)
			वापस -ENOMEM;

		b = call->buffer;
		r = call->request;
		r->समय_low			= b[0];
		r->समय_mid			= htons(ntohl(b[1]));
		r->समय_hi_and_version		= htons(ntohl(b[2]));
		r->घड़ी_seq_hi_and_reserved 	= ntohl(b[3]);
		r->घड़ी_seq_low		= ntohl(b[4]);

		क्रम (loop = 0; loop < 6; loop++)
			r->node[loop] = ntohl(b[loop + 5]);

		call->unmarshall++;
		fallthrough;

	हाल 2:
		अवरोध;
	पूर्ण

	अगर (!afs_check_call_state(call, AFS_CALL_SV_REPLYING))
		वापस afs_io_error(call, afs_io_error_cm_reply);
	वापस afs_find_cm_server_by_peer(call);
पूर्ण

/*
 * allow the fileserver to ask about the cache manager's capabilities
 */
अटल व्योम SRXAFSCB_TellMeAboutYourself(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा afs_call *call = container_of(work, काष्ठा afs_call, work);
	पूर्णांक loop;

	काष्ठा अणु
		काष्ठा /* InterfaceAddr */ अणु
			__be32 nअगरs;
			__be32 uuid[11];
			__be32 अगरaddr[32];
			__be32 neपंचांगask[32];
			__be32 mtu[32];
		पूर्ण ia;
		काष्ठा /* Capabilities */ अणु
			__be32 capcount;
			__be32 caps[1];
		पूर्ण cap;
	पूर्ण reply;

	_enter("");

	स_रखो(&reply, 0, माप(reply));

	reply.ia.uuid[0] = call->net->uuid.समय_low;
	reply.ia.uuid[1] = htonl(ntohs(call->net->uuid.समय_mid));
	reply.ia.uuid[2] = htonl(ntohs(call->net->uuid.समय_hi_and_version));
	reply.ia.uuid[3] = htonl((s8) call->net->uuid.घड़ी_seq_hi_and_reserved);
	reply.ia.uuid[4] = htonl((s8) call->net->uuid.घड़ी_seq_low);
	क्रम (loop = 0; loop < 6; loop++)
		reply.ia.uuid[loop + 5] = htonl((s8) call->net->uuid.node[loop]);

	reply.cap.capcount = htonl(1);
	reply.cap.caps[0] = htonl(AFS_CAP_ERROR_TRANSLATION);
	afs_send_simple_reply(call, &reply, माप(reply));
	afs_put_call(call);
	_leave("");
पूर्ण

/*
 * deliver request data to a CB.TellMeAboutYourself call
 */
अटल पूर्णांक afs_deliver_cb_tell_me_about_yourself(काष्ठा afs_call *call)
अणु
	पूर्णांक ret;

	_enter("");

	afs_extract_discard(call, 0);
	ret = afs_extract_data(call, false);
	अगर (ret < 0)
		वापस ret;

	अगर (!afs_check_call_state(call, AFS_CALL_SV_REPLYING))
		वापस afs_io_error(call, afs_io_error_cm_reply);
	वापस afs_find_cm_server_by_peer(call);
पूर्ण

/*
 * deliver request data to a YFS CB.CallBack call
 */
अटल पूर्णांक afs_deliver_yfs_cb_callback(काष्ठा afs_call *call)
अणु
	काष्ठा afs_callback_अवरोध *cb;
	काष्ठा yfs_xdr_YFSFid *bp;
	माप_प्रकार size;
	पूर्णांक ret, loop;

	_enter("{%u}", call->unmarshall);

	चयन (call->unmarshall) अणु
	हाल 0:
		afs_extract_to_पंचांगp(call);
		call->unmarshall++;

		/* extract the FID array and its count in two steps */
		fallthrough;
	हाल 1:
		_debug("extract FID count");
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		call->count = ntohl(call->पंचांगp);
		_debug("FID count: %u", call->count);
		अगर (call->count > YFSCBMAX)
			वापस afs_protocol_error(call, afs_eproto_cb_fid_count);

		size = array_size(call->count, माप(काष्ठा yfs_xdr_YFSFid));
		call->buffer = kदो_स्मृति(size, GFP_KERNEL);
		अगर (!call->buffer)
			वापस -ENOMEM;
		afs_extract_to_buf(call, size);
		call->unmarshall++;

		fallthrough;
	हाल 2:
		_debug("extract FID array");
		ret = afs_extract_data(call, false);
		अगर (ret < 0)
			वापस ret;

		_debug("unmarshall FID array");
		call->request = kसुस्मृति(call->count,
					माप(काष्ठा afs_callback_अवरोध),
					GFP_KERNEL);
		अगर (!call->request)
			वापस -ENOMEM;

		cb = call->request;
		bp = call->buffer;
		क्रम (loop = call->count; loop > 0; loop--, cb++) अणु
			cb->fid.vid	= xdr_to_u64(bp->volume);
			cb->fid.vnode	= xdr_to_u64(bp->vnode.lo);
			cb->fid.vnode_hi = ntohl(bp->vnode.hi);
			cb->fid.unique	= ntohl(bp->vnode.unique);
			bp++;
		पूर्ण

		afs_extract_to_पंचांगp(call);
		call->unmarshall++;
		fallthrough;

	हाल 3:
		अवरोध;
	पूर्ण

	अगर (!afs_check_call_state(call, AFS_CALL_SV_REPLYING))
		वापस afs_io_error(call, afs_io_error_cm_reply);

	/* We'll need the file server record as that tells us which set of
	 * vnodes to operate upon.
	 */
	वापस afs_find_cm_server_by_peer(call);
पूर्ण
