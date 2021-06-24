<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * An implementation of file copy service.
 *
 * Copyright (C) 2014, Microsoft, Inc.
 *
 * Author : K. Y. Srinivasan <ksrinivasan@novell.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/nls.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/hyperv.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/hyperv-tlfs.h>

#समावेश "hyperv_vmbus.h"
#समावेश "hv_utils_transport.h"

#घोषणा WIN8_SRV_MAJOR		1
#घोषणा WIN8_SRV_MINOR		1
#घोषणा WIN8_SRV_VERSION	(WIN8_SRV_MAJOR << 16 | WIN8_SRV_MINOR)

#घोषणा FCOPY_VER_COUNT 1
अटल स्थिर पूर्णांक fcopy_versions[] = अणु
	WIN8_SRV_VERSION
पूर्ण;

#घोषणा FW_VER_COUNT 1
अटल स्थिर पूर्णांक fw_versions[] = अणु
	UTIL_FW_VERSION
पूर्ण;

/*
 * Global state मुख्यtained क्रम transaction that is being processed.
 * For a class of पूर्णांकegration services, including the "file copy service",
 * the specअगरied protocol is a "request/response" protocol which means that
 * there can only be single outstanding transaction from the host at any
 * given poपूर्णांक in समय. We use this to simplअगरy memory management in this
 * driver - we cache and process only one message at a समय.
 *
 * While the request/response protocol is guaranteed by the host, we further
 * ensure this by serializing packet processing in this driver - we करो not
 * पढ़ो additional packets from the VMBUs until the current packet is fully
 * handled.
 */

अटल काष्ठा अणु
	पूर्णांक state;   /* hvutil_device_state */
	पूर्णांक recv_len; /* number of bytes received. */
	काष्ठा hv_fcopy_hdr  *fcopy_msg; /* current message */
	काष्ठा vmbus_channel *recv_channel; /* chn we got the request */
	u64 recv_req_id; /* request ID. */
पूर्ण fcopy_transaction;

अटल व्योम fcopy_respond_to_host(पूर्णांक error);
अटल व्योम fcopy_send_data(काष्ठा work_काष्ठा *dummy);
अटल व्योम fcopy_समयout_func(काष्ठा work_काष्ठा *dummy);
अटल DECLARE_DELAYED_WORK(fcopy_समयout_work, fcopy_समयout_func);
अटल DECLARE_WORK(fcopy_send_work, fcopy_send_data);
अटल स्थिर अक्षर fcopy_devname[] = "vmbus/hv_fcopy";
अटल u8 *recv_buffer;
अटल काष्ठा hvutil_transport *hvt;
/*
 * This state मुख्यtains the version number रेजिस्टरed by the daemon.
 */
अटल पूर्णांक dm_reg_value;

अटल व्योम fcopy_poll_wrapper(व्योम *channel)
अणु
	/* Transaction is finished, reset the state here to aव्योम races. */
	fcopy_transaction.state = HVUTIL_READY;
	tasklet_schedule(&((काष्ठा vmbus_channel *)channel)->callback_event);
पूर्ण

अटल व्योम fcopy_समयout_func(काष्ठा work_काष्ठा *dummy)
अणु
	/*
	 * If the समयr fires, the user-mode component has not responded;
	 * process the pending transaction.
	 */
	fcopy_respond_to_host(HV_E_FAIL);
	hv_poll_channel(fcopy_transaction.recv_channel, fcopy_poll_wrapper);
पूर्ण

अटल व्योम fcopy_रेजिस्टर_करोne(व्योम)
अणु
	pr_debug("FCP: userspace daemon registered\n");
	hv_poll_channel(fcopy_transaction.recv_channel, fcopy_poll_wrapper);
पूर्ण

अटल पूर्णांक fcopy_handle_handshake(u32 version)
अणु
	u32 our_ver = FCOPY_CURRENT_VERSION;

	चयन (version) अणु
	हाल FCOPY_VERSION_0:
		/* Daemon करोesn't expect us to reply */
		dm_reg_value = version;
		अवरोध;
	हाल FCOPY_VERSION_1:
		/* Daemon expects us to reply with our own version */
		अगर (hvutil_transport_send(hvt, &our_ver, माप(our_ver),
		    fcopy_रेजिस्टर_करोne))
			वापस -EFAULT;
		dm_reg_value = version;
		अवरोध;
	शेष:
		/*
		 * For now we will fail the registration.
		 * If and when we have multiple versions to
		 * deal with, we will be backward compatible.
		 * We will add this code when needed.
		 */
		वापस -EINVAL;
	पूर्ण
	pr_debug("FCP: userspace daemon ver. %d connected\n", version);
	वापस 0;
पूर्ण

अटल व्योम fcopy_send_data(काष्ठा work_काष्ठा *dummy)
अणु
	काष्ठा hv_start_fcopy *smsg_out = शून्य;
	पूर्णांक operation = fcopy_transaction.fcopy_msg->operation;
	काष्ठा hv_start_fcopy *smsg_in;
	व्योम *out_src;
	पूर्णांक rc, out_len;

	/*
	 * The  strings sent from the host are encoded in
	 * in utf16; convert it to utf8 strings.
	 * The host assures us that the utf16 strings will not exceed
	 * the max lengths specअगरied. We will however, reserve room
	 * क्रम the string terminating अक्षरacter - in the utf16s_utf8s()
	 * function we limit the size of the buffer where the converted
	 * string is placed to W_MAX_PATH -1 to guarantee
	 * that the strings can be properly terminated!
	 */

	चयन (operation) अणु
	हाल START_खाता_COPY:
		out_len = माप(काष्ठा hv_start_fcopy);
		smsg_out = kzalloc(माप(*smsg_out), GFP_KERNEL);
		अगर (!smsg_out)
			वापस;

		smsg_out->hdr.operation = operation;
		smsg_in = (काष्ठा hv_start_fcopy *)fcopy_transaction.fcopy_msg;

		utf16s_to_utf8s((ब_अक्षर_प्रकार *)smsg_in->file_name, W_MAX_PATH,
				UTF16_LITTLE_ENDIAN,
				(__u8 *)&smsg_out->file_name, W_MAX_PATH - 1);

		utf16s_to_utf8s((ब_अक्षर_प्रकार *)smsg_in->path_name, W_MAX_PATH,
				UTF16_LITTLE_ENDIAN,
				(__u8 *)&smsg_out->path_name, W_MAX_PATH - 1);

		smsg_out->copy_flags = smsg_in->copy_flags;
		smsg_out->file_size = smsg_in->file_size;
		out_src = smsg_out;
		अवरोध;

	हाल WRITE_TO_खाता:
		out_src = fcopy_transaction.fcopy_msg;
		out_len = माप(काष्ठा hv_करो_fcopy);
		अवरोध;
	शेष:
		out_src = fcopy_transaction.fcopy_msg;
		out_len = fcopy_transaction.recv_len;
		अवरोध;
	पूर्ण

	fcopy_transaction.state = HVUTIL_USERSPACE_REQ;
	rc = hvutil_transport_send(hvt, out_src, out_len, शून्य);
	अगर (rc) अणु
		pr_debug("FCP: failed to communicate to the daemon: %d\n", rc);
		अगर (cancel_delayed_work_sync(&fcopy_समयout_work)) अणु
			fcopy_respond_to_host(HV_E_FAIL);
			fcopy_transaction.state = HVUTIL_READY;
		पूर्ण
	पूर्ण
	kमुक्त(smsg_out);
पूर्ण

/*
 * Send a response back to the host.
 */

अटल व्योम
fcopy_respond_to_host(पूर्णांक error)
अणु
	काष्ठा icmsg_hdr *icmsghdr;
	u32 buf_len;
	काष्ठा vmbus_channel *channel;
	u64 req_id;

	/*
	 * Copy the global state क्रम completing the transaction. Note that
	 * only one transaction can be active at a समय. This is guaranteed
	 * by the file copy protocol implemented by the host. Furthermore,
	 * the "transaction active" state we मुख्यtain ensures that there can
	 * only be one active transaction at a समय.
	 */

	buf_len = fcopy_transaction.recv_len;
	channel = fcopy_transaction.recv_channel;
	req_id = fcopy_transaction.recv_req_id;

	icmsghdr = (काष्ठा icmsg_hdr *)
			&recv_buffer[माप(काष्ठा vmbuspipe_hdr)];

	अगर (channel->onchannel_callback == शून्य)
		/*
		 * We have raced with util driver being unloaded;
		 * silently वापस.
		 */
		वापस;

	icmsghdr->status = error;
	icmsghdr->icflags = ICMSGHDRFLAG_TRANSACTION | ICMSGHDRFLAG_RESPONSE;
	vmbus_sendpacket(channel, recv_buffer, buf_len, req_id,
				VM_PKT_DATA_INBAND, 0);
पूर्ण

व्योम hv_fcopy_onchannelcallback(व्योम *context)
अणु
	काष्ठा vmbus_channel *channel = context;
	u32 recvlen;
	u64 requestid;
	काष्ठा hv_fcopy_hdr *fcopy_msg;
	काष्ठा icmsg_hdr *icmsghdr;
	पूर्णांक fcopy_srv_version;

	अगर (fcopy_transaction.state > HVUTIL_READY)
		वापस;

	अगर (vmbus_recvpacket(channel, recv_buffer, HV_HYP_PAGE_SIZE * 2, &recvlen, &requestid)) अणु
		pr_err_ratelimited("Fcopy request received. Could not read into recv buf\n");
		वापस;
	पूर्ण

	अगर (!recvlen)
		वापस;

	/* Ensure recvlen is big enough to पढ़ो header data */
	अगर (recvlen < ICMSG_HDR) अणु
		pr_err_ratelimited("Fcopy request received. Packet length too small: %d\n",
				   recvlen);
		वापस;
	पूर्ण

	icmsghdr = (काष्ठा icmsg_hdr *)&recv_buffer[
			माप(काष्ठा vmbuspipe_hdr)];

	अगर (icmsghdr->icmsgtype == ICMSGTYPE_NEGOTIATE) अणु
		अगर (vmbus_prep_negotiate_resp(icmsghdr,
				recv_buffer, recvlen,
				fw_versions, FW_VER_COUNT,
				fcopy_versions, FCOPY_VER_COUNT,
				शून्य, &fcopy_srv_version)) अणु

			pr_info("FCopy IC version %d.%d\n",
				fcopy_srv_version >> 16,
				fcopy_srv_version & 0xFFFF);
		पूर्ण
	पूर्ण अन्यथा अगर (icmsghdr->icmsgtype == ICMSGTYPE_FCOPY) अणु
		/* Ensure recvlen is big enough to contain hv_fcopy_hdr */
		अगर (recvlen < ICMSG_HDR + माप(काष्ठा hv_fcopy_hdr)) अणु
			pr_err_ratelimited("Invalid Fcopy hdr. Packet length too small: %u\n",
					   recvlen);
			वापस;
		पूर्ण
		fcopy_msg = (काष्ठा hv_fcopy_hdr *)&recv_buffer[ICMSG_HDR];

		/*
		 * Stash away this global state क्रम completing the
		 * transaction; note transactions are serialized.
		 */

		fcopy_transaction.recv_len = recvlen;
		fcopy_transaction.recv_req_id = requestid;
		fcopy_transaction.fcopy_msg = fcopy_msg;

		अगर (fcopy_transaction.state < HVUTIL_READY) अणु
			/* Userspace is not रेजिस्टरed yet */
			fcopy_respond_to_host(HV_E_FAIL);
			वापस;
		पूर्ण
		fcopy_transaction.state = HVUTIL_HOSTMSG_RECEIVED;

		/*
		 * Send the inक्रमmation to the user-level daemon.
		 */
		schedule_work(&fcopy_send_work);
		schedule_delayed_work(&fcopy_समयout_work,
				      HV_UTIL_TIMEOUT * HZ);
		वापस;
	पूर्ण अन्यथा अणु
		pr_err_ratelimited("Fcopy request received. Invalid msg type: %d\n",
				   icmsghdr->icmsgtype);
		वापस;
	पूर्ण
	icmsghdr->icflags = ICMSGHDRFLAG_TRANSACTION | ICMSGHDRFLAG_RESPONSE;
	vmbus_sendpacket(channel, recv_buffer, recvlen, requestid,
			VM_PKT_DATA_INBAND, 0);
पूर्ण

/* Callback when data is received from userspace */
अटल पूर्णांक fcopy_on_msg(व्योम *msg, पूर्णांक len)
अणु
	पूर्णांक *val = (पूर्णांक *)msg;

	अगर (len != माप(पूर्णांक))
		वापस -EINVAL;

	अगर (fcopy_transaction.state == HVUTIL_DEVICE_INIT)
		वापस fcopy_handle_handshake(*val);

	अगर (fcopy_transaction.state != HVUTIL_USERSPACE_REQ)
		वापस -EINVAL;

	/*
	 * Complete the transaction by क्रमwarding the result
	 * to the host. But first, cancel the समयout.
	 */
	अगर (cancel_delayed_work_sync(&fcopy_समयout_work)) अणु
		fcopy_transaction.state = HVUTIL_USERSPACE_RECV;
		fcopy_respond_to_host(*val);
		hv_poll_channel(fcopy_transaction.recv_channel,
				fcopy_poll_wrapper);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fcopy_on_reset(व्योम)
अणु
	/*
	 * The daemon has निकासed; reset the state.
	 */
	fcopy_transaction.state = HVUTIL_DEVICE_INIT;

	अगर (cancel_delayed_work_sync(&fcopy_समयout_work))
		fcopy_respond_to_host(HV_E_FAIL);
पूर्ण

पूर्णांक hv_fcopy_init(काष्ठा hv_util_service *srv)
अणु
	recv_buffer = srv->recv_buffer;
	fcopy_transaction.recv_channel = srv->channel;

	/*
	 * When this driver loads, the user level daemon that
	 * processes the host requests may not yet be running.
	 * Defer processing channel callbacks until the daemon
	 * has रेजिस्टरed.
	 */
	fcopy_transaction.state = HVUTIL_DEVICE_INIT;

	hvt = hvutil_transport_init(fcopy_devname, 0, 0,
				    fcopy_on_msg, fcopy_on_reset);
	अगर (!hvt)
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल व्योम hv_fcopy_cancel_work(व्योम)
अणु
	cancel_delayed_work_sync(&fcopy_समयout_work);
	cancel_work_sync(&fcopy_send_work);
पूर्ण

पूर्णांक hv_fcopy_pre_suspend(व्योम)
अणु
	काष्ठा vmbus_channel *channel = fcopy_transaction.recv_channel;
	काष्ठा hv_fcopy_hdr *fcopy_msg;

	/*
	 * Fake a CANCEL_FCOPY message क्रम the user space daemon in हाल the
	 * daemon is in the middle of copying some file. It करोesn't matter अगर
	 * there is alपढ़ोy a message pending to be delivered to the user
	 * space since we क्रमce fcopy_transaction.state to be HVUTIL_READY, so
	 * the user space daemon's ग_लिखो() will fail with EINVAL (see
	 * fcopy_on_msg()), and the daemon will reset the device by closing
	 * and re-खोलोing it.
	 */
	fcopy_msg = kzalloc(माप(*fcopy_msg), GFP_KERNEL);
	अगर (!fcopy_msg)
		वापस -ENOMEM;

	tasklet_disable(&channel->callback_event);

	fcopy_msg->operation = CANCEL_FCOPY;

	hv_fcopy_cancel_work();

	/* We करोn't care about the वापस value. */
	hvutil_transport_send(hvt, fcopy_msg, माप(*fcopy_msg), शून्य);

	kमुक्त(fcopy_msg);

	fcopy_transaction.state = HVUTIL_READY;

	/* tasklet_enable() will be called in hv_fcopy_pre_resume(). */
	वापस 0;
पूर्ण

पूर्णांक hv_fcopy_pre_resume(व्योम)
अणु
	काष्ठा vmbus_channel *channel = fcopy_transaction.recv_channel;

	tasklet_enable(&channel->callback_event);

	वापस 0;
पूर्ण

व्योम hv_fcopy_deinit(व्योम)
अणु
	fcopy_transaction.state = HVUTIL_DEVICE_DYING;

	hv_fcopy_cancel_work();

	hvutil_transport_destroy(hvt);
पूर्ण
