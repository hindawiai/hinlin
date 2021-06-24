<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * An implementation of host initiated guest snapshot.
 *
 * Copyright (C) 2013, Microsoft, Inc.
 * Author : K. Y. Srinivasan <kys@microsoft.com>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/net.h>
#समावेश <linux/nls.h>
#समावेश <linux/connector.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/hyperv.h>
#समावेश <यंत्र/hyperv-tlfs.h>

#समावेश "hyperv_vmbus.h"
#समावेश "hv_utils_transport.h"

#घोषणा VSS_MAJOR  5
#घोषणा VSS_MINOR  0
#घोषणा VSS_VERSION    (VSS_MAJOR << 16 | VSS_MINOR)

#घोषणा VSS_VER_COUNT 1
अटल स्थिर पूर्णांक vss_versions[] = अणु
	VSS_VERSION
पूर्ण;

#घोषणा FW_VER_COUNT 1
अटल स्थिर पूर्णांक fw_versions[] = अणु
	UTIL_FW_VERSION
पूर्ण;

/*
 * Timeout values are based on expecations from host
 */
#घोषणा VSS_FREEZE_TIMEOUT (15 * 60)

/*
 * Global state मुख्यtained क्रम transaction that is being processed. For a class
 * of पूर्णांकegration services, including the "VSS service", the specअगरied protocol
 * is a "request/response" protocol which means that there can only be single
 * outstanding transaction from the host at any given poपूर्णांक in समय. We use
 * this to simplअगरy memory management in this driver - we cache and process
 * only one message at a समय.
 *
 * While the request/response protocol is guaranteed by the host, we further
 * ensure this by serializing packet processing in this driver - we करो not
 * पढ़ो additional packets from the VMBUs until the current packet is fully
 * handled.
 */

अटल काष्ठा अणु
	पूर्णांक state;   /* hvutil_device_state */
	पूर्णांक recv_len; /* number of bytes received. */
	काष्ठा vmbus_channel *recv_channel; /* chn we got the request */
	u64 recv_req_id; /* request ID. */
	काष्ठा hv_vss_msg  *msg; /* current message */
पूर्ण vss_transaction;


अटल व्योम vss_respond_to_host(पूर्णांक error);

/*
 * This state मुख्यtains the version number रेजिस्टरed by the daemon.
 */
अटल पूर्णांक dm_reg_value;

अटल स्थिर अक्षर vss_devname[] = "vmbus/hv_vss";
अटल __u8 *recv_buffer;
अटल काष्ठा hvutil_transport *hvt;

अटल व्योम vss_समयout_func(काष्ठा work_काष्ठा *dummy);
अटल व्योम vss_handle_request(काष्ठा work_काष्ठा *dummy);

अटल DECLARE_DELAYED_WORK(vss_समयout_work, vss_समयout_func);
अटल DECLARE_WORK(vss_handle_request_work, vss_handle_request);

अटल व्योम vss_poll_wrapper(व्योम *channel)
अणु
	/* Transaction is finished, reset the state here to aव्योम races. */
	vss_transaction.state = HVUTIL_READY;
	tasklet_schedule(&((काष्ठा vmbus_channel *)channel)->callback_event);
पूर्ण

/*
 * Callback when data is received from user mode.
 */

अटल व्योम vss_समयout_func(काष्ठा work_काष्ठा *dummy)
अणु
	/*
	 * Timeout रुकोing क्रम userspace component to reply happened.
	 */
	pr_warn("VSS: timeout waiting for daemon to reply\n");
	vss_respond_to_host(HV_E_FAIL);

	hv_poll_channel(vss_transaction.recv_channel, vss_poll_wrapper);
पूर्ण

अटल व्योम vss_रेजिस्टर_करोne(व्योम)
अणु
	hv_poll_channel(vss_transaction.recv_channel, vss_poll_wrapper);
	pr_debug("VSS: userspace daemon registered\n");
पूर्ण

अटल पूर्णांक vss_handle_handshake(काष्ठा hv_vss_msg *vss_msg)
अणु
	u32 our_ver = VSS_OP_REGISTER1;

	चयन (vss_msg->vss_hdr.operation) अणु
	हाल VSS_OP_REGISTER:
		/* Daemon करोesn't expect us to reply */
		dm_reg_value = VSS_OP_REGISTER;
		अवरोध;
	हाल VSS_OP_REGISTER1:
		/* Daemon expects us to reply with our own version */
		अगर (hvutil_transport_send(hvt, &our_ver, माप(our_ver),
					  vss_रेजिस्टर_करोne))
			वापस -EFAULT;
		dm_reg_value = VSS_OP_REGISTER1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	pr_info("VSS: userspace daemon ver. %d connected\n", dm_reg_value);
	वापस 0;
पूर्ण

अटल पूर्णांक vss_on_msg(व्योम *msg, पूर्णांक len)
अणु
	काष्ठा hv_vss_msg *vss_msg = (काष्ठा hv_vss_msg *)msg;

	अगर (len != माप(*vss_msg)) अणु
		pr_debug("VSS: Message size does not match length\n");
		वापस -EINVAL;
	पूर्ण

	अगर (vss_msg->vss_hdr.operation == VSS_OP_REGISTER ||
	    vss_msg->vss_hdr.operation == VSS_OP_REGISTER1) अणु
		/*
		 * Don't process registration messages if we're in the middle
		 * of a transaction processing.
		 */
		अगर (vss_transaction.state > HVUTIL_READY) अणु
			pr_debug("VSS: Got unexpected registration request\n");
			वापस -EINVAL;
		पूर्ण

		वापस vss_handle_handshake(vss_msg);
	पूर्ण अन्यथा अगर (vss_transaction.state == HVUTIL_USERSPACE_REQ) अणु
		vss_transaction.state = HVUTIL_USERSPACE_RECV;

		अगर (vss_msg->vss_hdr.operation == VSS_OP_HOT_BACKUP)
			vss_transaction.msg->vss_cf.flags =
				VSS_HBU_NO_AUTO_RECOVERY;

		अगर (cancel_delayed_work_sync(&vss_समयout_work)) अणु
			vss_respond_to_host(vss_msg->error);
			/* Transaction is finished, reset the state. */
			hv_poll_channel(vss_transaction.recv_channel,
					vss_poll_wrapper);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* This is a spurious call! */
		pr_debug("VSS: Transaction not active\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम vss_send_op(व्योम)
अणु
	पूर्णांक op = vss_transaction.msg->vss_hdr.operation;
	पूर्णांक rc;
	काष्ठा hv_vss_msg *vss_msg;

	/* The transaction state is wrong. */
	अगर (vss_transaction.state != HVUTIL_HOSTMSG_RECEIVED) अणु
		pr_debug("VSS: Unexpected attempt to send to daemon\n");
		वापस;
	पूर्ण

	vss_msg = kzalloc(माप(*vss_msg), GFP_KERNEL);
	अगर (!vss_msg)
		वापस;

	vss_msg->vss_hdr.operation = op;

	vss_transaction.state = HVUTIL_USERSPACE_REQ;

	schedule_delayed_work(&vss_समयout_work, op == VSS_OP_FREEZE ?
			VSS_FREEZE_TIMEOUT * HZ : HV_UTIL_TIMEOUT * HZ);

	rc = hvutil_transport_send(hvt, vss_msg, माप(*vss_msg), शून्य);
	अगर (rc) अणु
		pr_warn("VSS: failed to communicate to the daemon: %d\n", rc);
		अगर (cancel_delayed_work_sync(&vss_समयout_work)) अणु
			vss_respond_to_host(HV_E_FAIL);
			vss_transaction.state = HVUTIL_READY;
		पूर्ण
	पूर्ण

	kमुक्त(vss_msg);
पूर्ण

अटल व्योम vss_handle_request(काष्ठा work_काष्ठा *dummy)
अणु
	चयन (vss_transaction.msg->vss_hdr.operation) अणु
	/*
	 * Initiate a "freeze/thaw" operation in the guest.
	 * We respond to the host once the operation is complete.
	 *
	 * We send the message to the user space daemon and the operation is
	 * perक्रमmed in the daemon.
	 */
	हाल VSS_OP_THAW:
	हाल VSS_OP_FREEZE:
	हाल VSS_OP_HOT_BACKUP:
		अगर (vss_transaction.state < HVUTIL_READY) अणु
			/* Userspace is not रेजिस्टरed yet */
			pr_debug("VSS: Not ready for request.\n");
			vss_respond_to_host(HV_E_FAIL);
			वापस;
		पूर्ण

		pr_debug("VSS: Received request for op code: %d\n",
			vss_transaction.msg->vss_hdr.operation);
		vss_transaction.state = HVUTIL_HOSTMSG_RECEIVED;
		vss_send_op();
		वापस;
	हाल VSS_OP_GET_DM_INFO:
		vss_transaction.msg->dm_info.flags = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	vss_respond_to_host(0);
	hv_poll_channel(vss_transaction.recv_channel, vss_poll_wrapper);
पूर्ण

/*
 * Send a response back to the host.
 */

अटल व्योम
vss_respond_to_host(पूर्णांक error)
अणु
	काष्ठा icmsg_hdr *icmsghdrp;
	u32	buf_len;
	काष्ठा vmbus_channel *channel;
	u64	req_id;

	/*
	 * Copy the global state क्रम completing the transaction. Note that
	 * only one transaction can be active at a समय.
	 */

	buf_len = vss_transaction.recv_len;
	channel = vss_transaction.recv_channel;
	req_id = vss_transaction.recv_req_id;

	icmsghdrp = (काष्ठा icmsg_hdr *)
			&recv_buffer[माप(काष्ठा vmbuspipe_hdr)];

	अगर (channel->onchannel_callback == शून्य)
		/*
		 * We have raced with util driver being unloaded;
		 * silently वापस.
		 */
		वापस;

	icmsghdrp->status = error;

	icmsghdrp->icflags = ICMSGHDRFLAG_TRANSACTION | ICMSGHDRFLAG_RESPONSE;

	vmbus_sendpacket(channel, recv_buffer, buf_len, req_id,
				VM_PKT_DATA_INBAND, 0);

पूर्ण

/*
 * This callback is invoked when we get a VSS message from the host.
 * The host ensures that only one VSS transaction can be active at a समय.
 */

व्योम hv_vss_onchannelcallback(व्योम *context)
अणु
	काष्ठा vmbus_channel *channel = context;
	u32 recvlen;
	u64 requestid;
	काष्ठा hv_vss_msg *vss_msg;
	पूर्णांक vss_srv_version;

	काष्ठा icmsg_hdr *icmsghdrp;

	अगर (vss_transaction.state > HVUTIL_READY)
		वापस;

	अगर (vmbus_recvpacket(channel, recv_buffer, HV_HYP_PAGE_SIZE * 2, &recvlen, &requestid)) अणु
		pr_err_ratelimited("VSS request received. Could not read into recv buf\n");
		वापस;
	पूर्ण

	अगर (!recvlen)
		वापस;

	/* Ensure recvlen is big enough to पढ़ो header data */
	अगर (recvlen < ICMSG_HDR) अणु
		pr_err_ratelimited("VSS request received. Packet length too small: %d\n",
				   recvlen);
		वापस;
	पूर्ण

	icmsghdrp = (काष्ठा icmsg_hdr *)&recv_buffer[माप(काष्ठा vmbuspipe_hdr)];

	अगर (icmsghdrp->icmsgtype == ICMSGTYPE_NEGOTIATE) अणु
		अगर (vmbus_prep_negotiate_resp(icmsghdrp,
				recv_buffer, recvlen,
				fw_versions, FW_VER_COUNT,
				vss_versions, VSS_VER_COUNT,
				शून्य, &vss_srv_version)) अणु

			pr_info("VSS IC version %d.%d\n",
				vss_srv_version >> 16,
				vss_srv_version & 0xFFFF);
		पूर्ण
	पूर्ण अन्यथा अगर (icmsghdrp->icmsgtype == ICMSGTYPE_VSS) अणु
		/* Ensure recvlen is big enough to contain hv_vss_msg */
		अगर (recvlen < ICMSG_HDR + माप(काष्ठा hv_vss_msg)) अणु
			pr_err_ratelimited("Invalid VSS msg. Packet length too small: %u\n",
					   recvlen);
			वापस;
		पूर्ण
		vss_msg = (काष्ठा hv_vss_msg *)&recv_buffer[ICMSG_HDR];

		/*
		 * Stash away this global state क्रम completing the
		 * transaction; note transactions are serialized.
		 */

		vss_transaction.recv_len = recvlen;
		vss_transaction.recv_req_id = requestid;
		vss_transaction.msg = (काष्ठा hv_vss_msg *)vss_msg;

		schedule_work(&vss_handle_request_work);
		वापस;
	पूर्ण अन्यथा अणु
		pr_err_ratelimited("VSS request received. Invalid msg type: %d\n",
				   icmsghdrp->icmsgtype);
		वापस;
	पूर्ण

	icmsghdrp->icflags = ICMSGHDRFLAG_TRANSACTION |
		ICMSGHDRFLAG_RESPONSE;
	vmbus_sendpacket(channel, recv_buffer, recvlen, requestid,
			 VM_PKT_DATA_INBAND, 0);
पूर्ण

अटल व्योम vss_on_reset(व्योम)
अणु
	अगर (cancel_delayed_work_sync(&vss_समयout_work))
		vss_respond_to_host(HV_E_FAIL);
	vss_transaction.state = HVUTIL_DEVICE_INIT;
पूर्ण

पूर्णांक
hv_vss_init(काष्ठा hv_util_service *srv)
अणु
	अगर (vmbus_proto_version < VERSION_WIN8_1) अणु
		pr_warn("Integration service 'Backup (volume snapshot)'"
			" not supported on this host version.\n");
		वापस -ENOTSUPP;
	पूर्ण
	recv_buffer = srv->recv_buffer;
	vss_transaction.recv_channel = srv->channel;

	/*
	 * When this driver loads, the user level daemon that
	 * processes the host requests may not yet be running.
	 * Defer processing channel callbacks until the daemon
	 * has रेजिस्टरed.
	 */
	vss_transaction.state = HVUTIL_DEVICE_INIT;

	hvt = hvutil_transport_init(vss_devname, CN_VSS_IDX, CN_VSS_VAL,
				    vss_on_msg, vss_on_reset);
	अगर (!hvt) अणु
		pr_warn("VSS: Failed to initialize transport\n");
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hv_vss_cancel_work(व्योम)
अणु
	cancel_delayed_work_sync(&vss_समयout_work);
	cancel_work_sync(&vss_handle_request_work);
पूर्ण

पूर्णांक hv_vss_pre_suspend(व्योम)
अणु
	काष्ठा vmbus_channel *channel = vss_transaction.recv_channel;
	काष्ठा hv_vss_msg *vss_msg;

	/*
	 * Fake a THAW message क्रम the user space daemon in हाल the daemon
	 * has frozen the file प्रणालीs. It करोesn't matter अगर there is alपढ़ोy
	 * a message pending to be delivered to the user space since we क्रमce
	 * vss_transaction.state to be HVUTIL_READY, so the user space daemon's
	 * ग_लिखो() will fail with EINVAL (see vss_on_msg()), and the daemon
	 * will reset the device by closing and re-खोलोing it.
	 */
	vss_msg = kzalloc(माप(*vss_msg), GFP_KERNEL);
	अगर (!vss_msg)
		वापस -ENOMEM;

	tasklet_disable(&channel->callback_event);

	vss_msg->vss_hdr.operation = VSS_OP_THAW;

	/* Cancel any possible pending work. */
	hv_vss_cancel_work();

	/* We करोn't care about the वापस value. */
	hvutil_transport_send(hvt, vss_msg, माप(*vss_msg), शून्य);

	kमुक्त(vss_msg);

	vss_transaction.state = HVUTIL_READY;

	/* tasklet_enable() will be called in hv_vss_pre_resume(). */
	वापस 0;
पूर्ण

पूर्णांक hv_vss_pre_resume(व्योम)
अणु
	काष्ठा vmbus_channel *channel = vss_transaction.recv_channel;

	tasklet_enable(&channel->callback_event);

	वापस 0;
पूर्ण

व्योम hv_vss_deinit(व्योम)
अणु
	vss_transaction.state = HVUTIL_DEVICE_DYING;

	hv_vss_cancel_work();

	hvutil_transport_destroy(hvt);
पूर्ण
