<शैली गुरु>
/*
 * An implementation of key value pair (KVP) functionality क्रम Linux.
 *
 *
 * Copyright (C) 2010, Novell, Inc.
 * Author : K. Y. Srinivasan <ksrinivasan@novell.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA.
 *
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

/*
 * Pre win8 version numbers used in ws2008 and ws 2008 r2 (win7)
 */
#घोषणा WS2008_SRV_MAJOR	1
#घोषणा WS2008_SRV_MINOR	0
#घोषणा WS2008_SRV_VERSION     (WS2008_SRV_MAJOR << 16 | WS2008_SRV_MINOR)

#घोषणा WIN7_SRV_MAJOR   3
#घोषणा WIN7_SRV_MINOR   0
#घोषणा WIN7_SRV_VERSION     (WIN7_SRV_MAJOR << 16 | WIN7_SRV_MINOR)

#घोषणा WIN8_SRV_MAJOR   4
#घोषणा WIN8_SRV_MINOR   0
#घोषणा WIN8_SRV_VERSION     (WIN8_SRV_MAJOR << 16 | WIN8_SRV_MINOR)

#घोषणा KVP_VER_COUNT 3
अटल स्थिर पूर्णांक kvp_versions[] = अणु
	WIN8_SRV_VERSION,
	WIN7_SRV_VERSION,
	WS2008_SRV_VERSION
पूर्ण;

#घोषणा FW_VER_COUNT 2
अटल स्थिर पूर्णांक fw_versions[] = अणु
	UTIL_FW_VERSION,
	UTIL_WS2K8_FW_VERSION
पूर्ण;

/*
 * Global state मुख्यtained क्रम transaction that is being processed. For a class
 * of पूर्णांकegration services, including the "KVP service", the specअगरied protocol
 * is a "request/response" protocol which means that there can only be single
 * outstanding transaction from the host at any given poपूर्णांक in समय. We use
 * this to simplअगरy memory management in this driver - we cache and process
 * only one message at a समय.
 *
 * While the request/response protocol is guaranteed by the host, we further
 * ensure this by serializing packet processing in this driver - we करो not
 * पढ़ो additional packets from the VMBUS until the current packet is fully
 * handled.
 */

अटल काष्ठा अणु
	पूर्णांक state;   /* hvutil_device_state */
	पूर्णांक recv_len; /* number of bytes received. */
	काष्ठा hv_kvp_msg  *kvp_msg; /* current message */
	काष्ठा vmbus_channel *recv_channel; /* chn we got the request */
	u64 recv_req_id; /* request ID. */
पूर्ण kvp_transaction;

/*
 * This state मुख्यtains the version number रेजिस्टरed by the daemon.
 */
अटल पूर्णांक dm_reg_value;

अटल व्योम kvp_send_key(काष्ठा work_काष्ठा *dummy);


अटल व्योम kvp_respond_to_host(काष्ठा hv_kvp_msg *msg, पूर्णांक error);
अटल व्योम kvp_समयout_func(काष्ठा work_काष्ठा *dummy);
अटल व्योम kvp_host_handshake_func(काष्ठा work_काष्ठा *dummy);
अटल व्योम kvp_रेजिस्टर(पूर्णांक);

अटल DECLARE_DELAYED_WORK(kvp_समयout_work, kvp_समयout_func);
अटल DECLARE_DELAYED_WORK(kvp_host_handshake_work, kvp_host_handshake_func);
अटल DECLARE_WORK(kvp_sendkey_work, kvp_send_key);

अटल स्थिर अक्षर kvp_devname[] = "vmbus/hv_kvp";
अटल u8 *recv_buffer;
अटल काष्ठा hvutil_transport *hvt;
/*
 * Register the kernel component with the user-level daemon.
 * As part of this registration, pass the LIC version number.
 * This number has no meaning, it satisfies the registration protocol.
 */
#घोषणा HV_DRV_VERSION           "3.1"

अटल व्योम kvp_poll_wrapper(व्योम *channel)
अणु
	/* Transaction is finished, reset the state here to aव्योम races. */
	kvp_transaction.state = HVUTIL_READY;
	tasklet_schedule(&((काष्ठा vmbus_channel *)channel)->callback_event);
पूर्ण

अटल व्योम kvp_रेजिस्टर_करोne(व्योम)
अणु
	/*
	 * If we're still negotiating with the host cancel the समयout
	 * work to not poll the channel twice.
	 */
	pr_debug("KVP: userspace daemon registered\n");
	cancel_delayed_work_sync(&kvp_host_handshake_work);
	hv_poll_channel(kvp_transaction.recv_channel, kvp_poll_wrapper);
पूर्ण

अटल व्योम
kvp_रेजिस्टर(पूर्णांक reg_value)
अणु

	काष्ठा hv_kvp_msg *kvp_msg;
	अक्षर *version;

	kvp_msg = kzalloc(माप(*kvp_msg), GFP_KERNEL);

	अगर (kvp_msg) अणु
		version = kvp_msg->body.kvp_रेजिस्टर.version;
		kvp_msg->kvp_hdr.operation = reg_value;
		म_नकल(version, HV_DRV_VERSION);

		hvutil_transport_send(hvt, kvp_msg, माप(*kvp_msg),
				      kvp_रेजिस्टर_करोne);
		kमुक्त(kvp_msg);
	पूर्ण
पूर्ण

अटल व्योम kvp_समयout_func(काष्ठा work_काष्ठा *dummy)
अणु
	/*
	 * If the समयr fires, the user-mode component has not responded;
	 * process the pending transaction.
	 */
	kvp_respond_to_host(शून्य, HV_E_FAIL);

	hv_poll_channel(kvp_transaction.recv_channel, kvp_poll_wrapper);
पूर्ण

अटल व्योम kvp_host_handshake_func(काष्ठा work_काष्ठा *dummy)
अणु
	tasklet_schedule(&kvp_transaction.recv_channel->callback_event);
पूर्ण

अटल पूर्णांक kvp_handle_handshake(काष्ठा hv_kvp_msg *msg)
अणु
	चयन (msg->kvp_hdr.operation) अणु
	हाल KVP_OP_REGISTER:
		dm_reg_value = KVP_OP_REGISTER;
		pr_info("KVP: IP injection functionality not available\n");
		pr_info("KVP: Upgrade the KVP daemon\n");
		अवरोध;
	हाल KVP_OP_REGISTER1:
		dm_reg_value = KVP_OP_REGISTER1;
		अवरोध;
	शेष:
		pr_info("KVP: incompatible daemon\n");
		pr_info("KVP: KVP version: %d, Daemon version: %d\n",
			KVP_OP_REGISTER1, msg->kvp_hdr.operation);
		वापस -EINVAL;
	पूर्ण

	/*
	 * We have a compatible daemon; complete the handshake.
	 */
	pr_debug("KVP: userspace daemon ver. %d connected\n",
		 msg->kvp_hdr.operation);
	kvp_रेजिस्टर(dm_reg_value);

	वापस 0;
पूर्ण


/*
 * Callback when data is received from user mode.
 */

अटल पूर्णांक kvp_on_msg(व्योम *msg, पूर्णांक len)
अणु
	काष्ठा hv_kvp_msg *message = (काष्ठा hv_kvp_msg *)msg;
	काष्ठा hv_kvp_msg_क्रमागतerate *data;
	पूर्णांक	error = 0;

	अगर (len < माप(*message))
		वापस -EINVAL;

	/*
	 * If we are negotiating the version inक्रमmation
	 * with the daemon; handle that first.
	 */

	अगर (kvp_transaction.state < HVUTIL_READY) अणु
		वापस kvp_handle_handshake(message);
	पूर्ण

	/* We didn't send anything to userspace so the reply is spurious */
	अगर (kvp_transaction.state < HVUTIL_USERSPACE_REQ)
		वापस -EINVAL;

	kvp_transaction.state = HVUTIL_USERSPACE_RECV;

	/*
	 * Based on the version of the daemon, we propagate errors from the
	 * daemon dअगरferently.
	 */

	data = &message->body.kvp_क्रमागत_data;

	चयन (dm_reg_value) अणु
	हाल KVP_OP_REGISTER:
		/*
		 * Null string is used to pass back error condition.
		 */
		अगर (data->data.key[0] == 0)
			error = HV_S_CONT;
		अवरोध;

	हाल KVP_OP_REGISTER1:
		/*
		 * We use the message header inक्रमmation from
		 * the user level daemon to transmit errors.
		 */
		error = message->error;
		अवरोध;
	पूर्ण

	/*
	 * Complete the transaction by क्रमwarding the key value
	 * to the host. But first, cancel the समयout.
	 */
	अगर (cancel_delayed_work_sync(&kvp_समयout_work)) अणु
		kvp_respond_to_host(message, error);
		hv_poll_channel(kvp_transaction.recv_channel, kvp_poll_wrapper);
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक process_ob_ipinfo(व्योम *in_msg, व्योम *out_msg, पूर्णांक op)
अणु
	काष्ठा hv_kvp_msg *in = in_msg;
	काष्ठा hv_kvp_ip_msg *out = out_msg;
	पूर्णांक len;

	चयन (op) अणु
	हाल KVP_OP_GET_IP_INFO:
		/*
		 * Transक्रमm all parameters पूर्णांकo utf16 encoding.
		 */
		len = utf8s_to_utf16s((अक्षर *)in->body.kvp_ip_val.ip_addr,
				म_माप((अक्षर *)in->body.kvp_ip_val.ip_addr),
				UTF16_HOST_ENDIAN,
				(ब_अक्षर_प्रकार *)out->kvp_ip_val.ip_addr,
				MAX_IP_ADDR_SIZE);
		अगर (len < 0)
			वापस len;

		len = utf8s_to_utf16s((अक्षर *)in->body.kvp_ip_val.sub_net,
				म_माप((अक्षर *)in->body.kvp_ip_val.sub_net),
				UTF16_HOST_ENDIAN,
				(ब_अक्षर_प्रकार *)out->kvp_ip_val.sub_net,
				MAX_IP_ADDR_SIZE);
		अगर (len < 0)
			वापस len;

		len = utf8s_to_utf16s((अक्षर *)in->body.kvp_ip_val.gate_way,
				म_माप((अक्षर *)in->body.kvp_ip_val.gate_way),
				UTF16_HOST_ENDIAN,
				(ब_अक्षर_प्रकार *)out->kvp_ip_val.gate_way,
				MAX_GATEWAY_SIZE);
		अगर (len < 0)
			वापस len;

		len = utf8s_to_utf16s((अक्षर *)in->body.kvp_ip_val.dns_addr,
				म_माप((अक्षर *)in->body.kvp_ip_val.dns_addr),
				UTF16_HOST_ENDIAN,
				(ब_अक्षर_प्रकार *)out->kvp_ip_val.dns_addr,
				MAX_IP_ADDR_SIZE);
		अगर (len < 0)
			वापस len;

		len = utf8s_to_utf16s((अक्षर *)in->body.kvp_ip_val.adapter_id,
				म_माप((अक्षर *)in->body.kvp_ip_val.adapter_id),
				UTF16_HOST_ENDIAN,
				(ब_अक्षर_प्रकार *)out->kvp_ip_val.adapter_id,
				MAX_ADAPTER_ID_SIZE);
		अगर (len < 0)
			वापस len;

		out->kvp_ip_val.dhcp_enabled =
			in->body.kvp_ip_val.dhcp_enabled;
		out->kvp_ip_val.addr_family =
			in->body.kvp_ip_val.addr_family;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम process_ib_ipinfo(व्योम *in_msg, व्योम *out_msg, पूर्णांक op)
अणु
	काष्ठा hv_kvp_ip_msg *in = in_msg;
	काष्ठा hv_kvp_msg *out = out_msg;

	चयन (op) अणु
	हाल KVP_OP_SET_IP_INFO:
		/*
		 * Transक्रमm all parameters पूर्णांकo utf8 encoding.
		 */
		utf16s_to_utf8s((ब_अक्षर_प्रकार *)in->kvp_ip_val.ip_addr,
				MAX_IP_ADDR_SIZE,
				UTF16_LITTLE_ENDIAN,
				(__u8 *)out->body.kvp_ip_val.ip_addr,
				MAX_IP_ADDR_SIZE);

		utf16s_to_utf8s((ब_अक्षर_प्रकार *)in->kvp_ip_val.sub_net,
				MAX_IP_ADDR_SIZE,
				UTF16_LITTLE_ENDIAN,
				(__u8 *)out->body.kvp_ip_val.sub_net,
				MAX_IP_ADDR_SIZE);

		utf16s_to_utf8s((ब_अक्षर_प्रकार *)in->kvp_ip_val.gate_way,
				MAX_GATEWAY_SIZE,
				UTF16_LITTLE_ENDIAN,
				(__u8 *)out->body.kvp_ip_val.gate_way,
				MAX_GATEWAY_SIZE);

		utf16s_to_utf8s((ब_अक्षर_प्रकार *)in->kvp_ip_val.dns_addr,
				MAX_IP_ADDR_SIZE,
				UTF16_LITTLE_ENDIAN,
				(__u8 *)out->body.kvp_ip_val.dns_addr,
				MAX_IP_ADDR_SIZE);

		out->body.kvp_ip_val.dhcp_enabled = in->kvp_ip_val.dhcp_enabled;

		fallthrough;

	हाल KVP_OP_GET_IP_INFO:
		utf16s_to_utf8s((ब_अक्षर_प्रकार *)in->kvp_ip_val.adapter_id,
				MAX_ADAPTER_ID_SIZE,
				UTF16_LITTLE_ENDIAN,
				(__u8 *)out->body.kvp_ip_val.adapter_id,
				MAX_ADAPTER_ID_SIZE);

		out->body.kvp_ip_val.addr_family = in->kvp_ip_val.addr_family;
	पूर्ण
पूर्ण




अटल व्योम
kvp_send_key(काष्ठा work_काष्ठा *dummy)
अणु
	काष्ठा hv_kvp_msg *message;
	काष्ठा hv_kvp_msg *in_msg;
	__u8 operation = kvp_transaction.kvp_msg->kvp_hdr.operation;
	__u8 pool = kvp_transaction.kvp_msg->kvp_hdr.pool;
	__u32 val32;
	__u64 val64;
	पूर्णांक rc;

	/* The transaction state is wrong. */
	अगर (kvp_transaction.state != HVUTIL_HOSTMSG_RECEIVED)
		वापस;

	message = kzalloc(माप(*message), GFP_KERNEL);
	अगर (!message)
		वापस;

	message->kvp_hdr.operation = operation;
	message->kvp_hdr.pool = pool;
	in_msg = kvp_transaction.kvp_msg;

	/*
	 * The key/value strings sent from the host are encoded in
	 * in utf16; convert it to utf8 strings.
	 * The host assures us that the utf16 strings will not exceed
	 * the max lengths specअगरied. We will however, reserve room
	 * क्रम the string terminating अक्षरacter - in the utf16s_utf8s()
	 * function we limit the size of the buffer where the converted
	 * string is placed to HV_KVP_EXCHANGE_MAX_*_SIZE -1 to guarantee
	 * that the strings can be properly terminated!
	 */

	चयन (message->kvp_hdr.operation) अणु
	हाल KVP_OP_SET_IP_INFO:
		process_ib_ipinfo(in_msg, message, KVP_OP_SET_IP_INFO);
		अवरोध;
	हाल KVP_OP_GET_IP_INFO:
		/*
		 * We only need to pass on the info of operation, adapter_id
		 * and addr_family to the userland kvp daemon.
		 */
		process_ib_ipinfo(in_msg, message, KVP_OP_GET_IP_INFO);
		अवरोध;
	हाल KVP_OP_SET:
		चयन (in_msg->body.kvp_set.data.value_type) अणु
		हाल REG_SZ:
			/*
			 * The value is a string - utf16 encoding.
			 */
			message->body.kvp_set.data.value_size =
				utf16s_to_utf8s(
				(ब_अक्षर_प्रकार *)in_msg->body.kvp_set.data.value,
				in_msg->body.kvp_set.data.value_size,
				UTF16_LITTLE_ENDIAN,
				message->body.kvp_set.data.value,
				HV_KVP_EXCHANGE_MAX_VALUE_SIZE - 1) + 1;
			अवरोध;

		हाल REG_U32:
			/*
			 * The value is a 32 bit scalar.
			 * We save this as a utf8 string.
			 */
			val32 = in_msg->body.kvp_set.data.value_u32;
			message->body.kvp_set.data.value_size =
				प्र_लिखो(message->body.kvp_set.data.value,
					"%u", val32) + 1;
			अवरोध;

		हाल REG_U64:
			/*
			 * The value is a 64 bit scalar.
			 * We save this as a utf8 string.
			 */
			val64 = in_msg->body.kvp_set.data.value_u64;
			message->body.kvp_set.data.value_size =
				प्र_लिखो(message->body.kvp_set.data.value,
					"%llu", val64) + 1;
			अवरोध;

		पूर्ण

		/*
		 * The key is always a string - utf16 encoding.
		 */
		message->body.kvp_set.data.key_size =
			utf16s_to_utf8s(
			(ब_अक्षर_प्रकार *)in_msg->body.kvp_set.data.key,
			in_msg->body.kvp_set.data.key_size,
			UTF16_LITTLE_ENDIAN,
			message->body.kvp_set.data.key,
			HV_KVP_EXCHANGE_MAX_KEY_SIZE - 1) + 1;

		अवरोध;

	हाल KVP_OP_GET:
		message->body.kvp_get.data.key_size =
			utf16s_to_utf8s(
			(ब_अक्षर_प्रकार *)in_msg->body.kvp_get.data.key,
			in_msg->body.kvp_get.data.key_size,
			UTF16_LITTLE_ENDIAN,
			message->body.kvp_get.data.key,
			HV_KVP_EXCHANGE_MAX_KEY_SIZE - 1) + 1;
		अवरोध;

	हाल KVP_OP_DELETE:
		message->body.kvp_delete.key_size =
			utf16s_to_utf8s(
			(ब_अक्षर_प्रकार *)in_msg->body.kvp_delete.key,
			in_msg->body.kvp_delete.key_size,
			UTF16_LITTLE_ENDIAN,
			message->body.kvp_delete.key,
			HV_KVP_EXCHANGE_MAX_KEY_SIZE - 1) + 1;
		अवरोध;

	हाल KVP_OP_ENUMERATE:
		message->body.kvp_क्रमागत_data.index =
			in_msg->body.kvp_क्रमागत_data.index;
		अवरोध;
	पूर्ण

	kvp_transaction.state = HVUTIL_USERSPACE_REQ;
	rc = hvutil_transport_send(hvt, message, माप(*message), शून्य);
	अगर (rc) अणु
		pr_debug("KVP: failed to communicate to the daemon: %d\n", rc);
		अगर (cancel_delayed_work_sync(&kvp_समयout_work)) अणु
			kvp_respond_to_host(message, HV_E_FAIL);
			kvp_transaction.state = HVUTIL_READY;
		पूर्ण
	पूर्ण

	kमुक्त(message);
पूर्ण

/*
 * Send a response back to the host.
 */

अटल व्योम
kvp_respond_to_host(काष्ठा hv_kvp_msg *msg_to_host, पूर्णांक error)
अणु
	काष्ठा hv_kvp_msg  *kvp_msg;
	काष्ठा hv_kvp_exchg_msg_value  *kvp_data;
	अक्षर	*key_name;
	अक्षर	*value;
	काष्ठा icmsg_hdr *icmsghdrp;
	पूर्णांक	keylen = 0;
	पूर्णांक	valuelen = 0;
	u32	buf_len;
	काष्ठा vmbus_channel *channel;
	u64	req_id;
	पूर्णांक ret;

	/*
	 * Copy the global state क्रम completing the transaction. Note that
	 * only one transaction can be active at a समय.
	 */

	buf_len = kvp_transaction.recv_len;
	channel = kvp_transaction.recv_channel;
	req_id = kvp_transaction.recv_req_id;

	icmsghdrp = (काष्ठा icmsg_hdr *)
			&recv_buffer[माप(काष्ठा vmbuspipe_hdr)];

	अगर (channel->onchannel_callback == शून्य)
		/*
		 * We have raced with util driver being unloaded;
		 * silently वापस.
		 */
		वापस;

	icmsghdrp->status = error;

	/*
	 * If the error parameter is set, terminate the host's क्रमागतeration
	 * on this pool.
	 */
	अगर (error) अणु
		/*
		 * Something failed or we have समयd out;
		 * terminate the current host-side iteration.
		 */
		जाओ response_करोne;
	पूर्ण

	kvp_msg = (काष्ठा hv_kvp_msg *)
			&recv_buffer[माप(काष्ठा vmbuspipe_hdr) +
			माप(काष्ठा icmsg_hdr)];

	चयन (kvp_transaction.kvp_msg->kvp_hdr.operation) अणु
	हाल KVP_OP_GET_IP_INFO:
		ret = process_ob_ipinfo(msg_to_host,
				 (काष्ठा hv_kvp_ip_msg *)kvp_msg,
				 KVP_OP_GET_IP_INFO);
		अगर (ret < 0)
			icmsghdrp->status = HV_E_FAIL;

		जाओ response_करोne;
	हाल KVP_OP_SET_IP_INFO:
		जाओ response_करोne;
	हाल KVP_OP_GET:
		kvp_data = &kvp_msg->body.kvp_get.data;
		जाओ copy_value;

	हाल KVP_OP_SET:
	हाल KVP_OP_DELETE:
		जाओ response_करोne;

	शेष:
		अवरोध;
	पूर्ण

	kvp_data = &kvp_msg->body.kvp_क्रमागत_data.data;
	key_name = msg_to_host->body.kvp_क्रमागत_data.data.key;

	/*
	 * The winकरोws host expects the key/value pair to be encoded
	 * in utf16. Ensure that the key/value size reported to the host
	 * will be less than or equal to the MAX size (including the
	 * terminating अक्षरacter).
	 */
	keylen = utf8s_to_utf16s(key_name, म_माप(key_name), UTF16_HOST_ENDIAN,
				(ब_अक्षर_प्रकार *) kvp_data->key,
				(HV_KVP_EXCHANGE_MAX_KEY_SIZE / 2) - 2);
	kvp_data->key_size = 2*(keylen + 1); /* utf16 encoding */

copy_value:
	value = msg_to_host->body.kvp_क्रमागत_data.data.value;
	valuelen = utf8s_to_utf16s(value, म_माप(value), UTF16_HOST_ENDIAN,
				(ब_अक्षर_प्रकार *) kvp_data->value,
				(HV_KVP_EXCHANGE_MAX_VALUE_SIZE / 2) - 2);
	kvp_data->value_size = 2*(valuelen + 1); /* utf16 encoding */

	/*
	 * If the utf8s to utf16s conversion failed; notअगरy host
	 * of the error.
	 */
	अगर ((keylen < 0) || (valuelen < 0))
		icmsghdrp->status = HV_E_FAIL;

	kvp_data->value_type = REG_SZ; /* all our values are strings */

response_करोne:
	icmsghdrp->icflags = ICMSGHDRFLAG_TRANSACTION | ICMSGHDRFLAG_RESPONSE;

	vmbus_sendpacket(channel, recv_buffer, buf_len, req_id,
				VM_PKT_DATA_INBAND, 0);
पूर्ण

/*
 * This callback is invoked when we get a KVP message from the host.
 * The host ensures that only one KVP transaction can be active at a समय.
 * KVP implementation in Linux needs to क्रमward the key to a user-mde
 * component to retrieve the corresponding value. Consequently, we cannot
 * respond to the host in the context of this callback. Since the host
 * guarantees that at most only one transaction can be active at a समय,
 * we stash away the transaction state in a set of global variables.
 */

व्योम hv_kvp_onchannelcallback(व्योम *context)
अणु
	काष्ठा vmbus_channel *channel = context;
	u32 recvlen;
	u64 requestid;

	काष्ठा hv_kvp_msg *kvp_msg;

	काष्ठा icmsg_hdr *icmsghdrp;
	पूर्णांक kvp_srv_version;
	अटल क्रमागत अणुNEGO_NOT_STARTED,
		     NEGO_IN_PROGRESS,
		     NEGO_FINISHEDपूर्ण host_negotiatied = NEGO_NOT_STARTED;

	अगर (kvp_transaction.state < HVUTIL_READY) अणु
		/*
		 * If userspace daemon is not connected and host is asking
		 * us to negotiate we need to delay to not lose messages.
		 * This is important क्रम Failover IP setting.
		 */
		अगर (host_negotiatied == NEGO_NOT_STARTED) अणु
			host_negotiatied = NEGO_IN_PROGRESS;
			schedule_delayed_work(&kvp_host_handshake_work,
				      HV_UTIL_NEGO_TIMEOUT * HZ);
		पूर्ण
		वापस;
	पूर्ण
	अगर (kvp_transaction.state > HVUTIL_READY)
		वापस;

	अगर (vmbus_recvpacket(channel, recv_buffer, HV_HYP_PAGE_SIZE * 4, &recvlen, &requestid)) अणु
		pr_err_ratelimited("KVP request received. Could not read into recv buf\n");
		वापस;
	पूर्ण

	अगर (!recvlen)
		वापस;

	/* Ensure recvlen is big enough to पढ़ो header data */
	अगर (recvlen < ICMSG_HDR) अणु
		pr_err_ratelimited("KVP request received. Packet length too small: %d\n",
				   recvlen);
		वापस;
	पूर्ण

	icmsghdrp = (काष्ठा icmsg_hdr *)&recv_buffer[माप(काष्ठा vmbuspipe_hdr)];

	अगर (icmsghdrp->icmsgtype == ICMSGTYPE_NEGOTIATE) अणु
		अगर (vmbus_prep_negotiate_resp(icmsghdrp,
				recv_buffer, recvlen,
				fw_versions, FW_VER_COUNT,
				kvp_versions, KVP_VER_COUNT,
				शून्य, &kvp_srv_version)) अणु
			pr_info("KVP IC version %d.%d\n",
				kvp_srv_version >> 16,
				kvp_srv_version & 0xFFFF);
		पूर्ण
	पूर्ण अन्यथा अगर (icmsghdrp->icmsgtype == ICMSGTYPE_KVPEXCHANGE) अणु
		/*
		 * recvlen is not checked against माप(काष्ठा kvp_msg) because kvp_msg contains
		 * a जोड़ of काष्ठाs and the msg type received is not known. Code using this
		 * काष्ठा should provide validation when accessing its fields.
		 */
		kvp_msg = (काष्ठा hv_kvp_msg *)&recv_buffer[ICMSG_HDR];

		/*
		 * Stash away this global state क्रम completing the
		 * transaction; note transactions are serialized.
		 */

		kvp_transaction.recv_len = recvlen;
		kvp_transaction.recv_req_id = requestid;
		kvp_transaction.kvp_msg = kvp_msg;

		अगर (kvp_transaction.state < HVUTIL_READY) अणु
			/* Userspace is not रेजिस्टरed yet */
			kvp_respond_to_host(शून्य, HV_E_FAIL);
			वापस;
		पूर्ण
		kvp_transaction.state = HVUTIL_HOSTMSG_RECEIVED;

		/*
		 * Get the inक्रमmation from the
		 * user-mode component.
		 * component. This transaction will be
		 * completed when we get the value from
		 * the user-mode component.
		 * Set a समयout to deal with
		 * user-mode not responding.
		 */
		schedule_work(&kvp_sendkey_work);
		schedule_delayed_work(&kvp_समयout_work,
					HV_UTIL_TIMEOUT * HZ);

		वापस;

	पूर्ण अन्यथा अणु
		pr_err_ratelimited("KVP request received. Invalid msg type: %d\n",
				   icmsghdrp->icmsgtype);
		वापस;
	पूर्ण

	icmsghdrp->icflags = ICMSGHDRFLAG_TRANSACTION
		| ICMSGHDRFLAG_RESPONSE;

	vmbus_sendpacket(channel, recv_buffer,
			 recvlen, requestid,
			 VM_PKT_DATA_INBAND, 0);

	host_negotiatied = NEGO_FINISHED;
	hv_poll_channel(kvp_transaction.recv_channel, kvp_poll_wrapper);
पूर्ण

अटल व्योम kvp_on_reset(व्योम)
अणु
	अगर (cancel_delayed_work_sync(&kvp_समयout_work))
		kvp_respond_to_host(शून्य, HV_E_FAIL);
	kvp_transaction.state = HVUTIL_DEVICE_INIT;
पूर्ण

पूर्णांक
hv_kvp_init(काष्ठा hv_util_service *srv)
अणु
	recv_buffer = srv->recv_buffer;
	kvp_transaction.recv_channel = srv->channel;

	/*
	 * When this driver loads, the user level daemon that
	 * processes the host requests may not yet be running.
	 * Defer processing channel callbacks until the daemon
	 * has रेजिस्टरed.
	 */
	kvp_transaction.state = HVUTIL_DEVICE_INIT;

	hvt = hvutil_transport_init(kvp_devname, CN_KVP_IDX, CN_KVP_VAL,
				    kvp_on_msg, kvp_on_reset);
	अगर (!hvt)
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल व्योम hv_kvp_cancel_work(व्योम)
अणु
	cancel_delayed_work_sync(&kvp_host_handshake_work);
	cancel_delayed_work_sync(&kvp_समयout_work);
	cancel_work_sync(&kvp_sendkey_work);
पूर्ण

पूर्णांक hv_kvp_pre_suspend(व्योम)
अणु
	काष्ठा vmbus_channel *channel = kvp_transaction.recv_channel;

	tasklet_disable(&channel->callback_event);

	/*
	 * If there is a pending transtion, it's unnecessary to tell the host
	 * that the transaction will fail, because that is implied when
	 * util_suspend() calls vmbus_बंद() later.
	 */
	hv_kvp_cancel_work();

	/*
	 * Forece the state to READY to handle the ICMSGTYPE_NEGOTIATE message
	 * later. The user space daemon may go out of order and its ग_लिखो()
	 * may fail with EINVAL: this करोesn't matter since the daemon will
	 * reset the device by closing and re-खोलोing it.
	 */
	kvp_transaction.state = HVUTIL_READY;
	वापस 0;
पूर्ण

पूर्णांक hv_kvp_pre_resume(व्योम)
अणु
	काष्ठा vmbus_channel *channel = kvp_transaction.recv_channel;

	tasklet_enable(&channel->callback_event);

	वापस 0;
पूर्ण

व्योम hv_kvp_deinit(व्योम)
अणु
	kvp_transaction.state = HVUTIL_DEVICE_DYING;

	hv_kvp_cancel_work();

	hvutil_transport_destroy(hvt);
पूर्ण
