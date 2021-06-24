<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// ChromeOS EC communication protocol helper functions
//
// Copyright (C) 2015 Google, Inc

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "cros_ec_trace.h"

#घोषणा EC_COMMAND_RETRIES	50

अटल स्थिर पूर्णांक cros_ec_error_map[] = अणु
	[EC_RES_INVALID_COMMAND] = -EOPNOTSUPP,
	[EC_RES_ERROR] = -EIO,
	[EC_RES_INVALID_PARAM] = -EINVAL,
	[EC_RES_ACCESS_DENIED] = -EACCES,
	[EC_RES_INVALID_RESPONSE] = -EPROTO,
	[EC_RES_INVALID_VERSION] = -ENOPROTOOPT,
	[EC_RES_INVALID_CHECKSUM] = -EBADMSG,
	[EC_RES_IN_PROGRESS] = -EINPROGRESS,
	[EC_RES_UNAVAILABLE] = -ENODATA,
	[EC_RES_TIMEOUT] = -ETIMEDOUT,
	[EC_RES_OVERFLOW] = -EOVERFLOW,
	[EC_RES_INVALID_HEADER] = -EBADR,
	[EC_RES_REQUEST_TRUNCATED] = -EBADR,
	[EC_RES_RESPONSE_TOO_BIG] = -EFBIG,
	[EC_RES_BUS_ERROR] = -EFAULT,
	[EC_RES_BUSY] = -EBUSY,
	[EC_RES_INVALID_HEADER_VERSION] = -EBADMSG,
	[EC_RES_INVALID_HEADER_CRC] = -EBADMSG,
	[EC_RES_INVALID_DATA_CRC] = -EBADMSG,
	[EC_RES_DUP_UNAVAILABLE] = -ENODATA,
पूर्ण;

अटल पूर्णांक cros_ec_map_error(uपूर्णांक32_t result)
अणु
	पूर्णांक ret = 0;

	अगर (result != EC_RES_SUCCESS) अणु
		अगर (result < ARRAY_SIZE(cros_ec_error_map) && cros_ec_error_map[result])
			ret = cros_ec_error_map[result];
		अन्यथा
			ret = -EPROTO;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक prepare_packet(काष्ठा cros_ec_device *ec_dev,
			  काष्ठा cros_ec_command *msg)
अणु
	काष्ठा ec_host_request *request;
	u8 *out;
	पूर्णांक i;
	u8 csum = 0;

	BUG_ON(ec_dev->proto_version != EC_HOST_REQUEST_VERSION);
	BUG_ON(msg->outsize + माप(*request) > ec_dev->करोut_size);

	out = ec_dev->करोut;
	request = (काष्ठा ec_host_request *)out;
	request->काष्ठा_version = EC_HOST_REQUEST_VERSION;
	request->checksum = 0;
	request->command = msg->command;
	request->command_version = msg->version;
	request->reserved = 0;
	request->data_len = msg->outsize;

	क्रम (i = 0; i < माप(*request); i++)
		csum += out[i];

	/* Copy data and update checksum */
	स_नकल(out + माप(*request), msg->data, msg->outsize);
	क्रम (i = 0; i < msg->outsize; i++)
		csum += msg->data[i];

	request->checksum = -csum;

	वापस माप(*request) + msg->outsize;
पूर्ण

अटल पूर्णांक send_command(काष्ठा cros_ec_device *ec_dev,
			काष्ठा cros_ec_command *msg)
अणु
	पूर्णांक ret;
	पूर्णांक (*xfer_fxn)(काष्ठा cros_ec_device *ec, काष्ठा cros_ec_command *msg);

	अगर (ec_dev->proto_version > 2)
		xfer_fxn = ec_dev->pkt_xfer;
	अन्यथा
		xfer_fxn = ec_dev->cmd_xfer;

	अगर (!xfer_fxn) अणु
		/*
		 * This error can happen अगर a communication error happened and
		 * the EC is trying to use protocol v2, on an underlying
		 * communication mechanism that करोes not support v2.
		 */
		dev_err_once(ec_dev->dev,
			     "missing EC transfer API, cannot send command\n");
		वापस -EIO;
	पूर्ण

	trace_cros_ec_request_start(msg);
	ret = (*xfer_fxn)(ec_dev, msg);
	trace_cros_ec_request_करोne(msg, ret);
	अगर (msg->result == EC_RES_IN_PROGRESS) अणु
		पूर्णांक i;
		काष्ठा cros_ec_command *status_msg;
		काष्ठा ec_response_get_comms_status *status;

		status_msg = kदो_स्मृति(माप(*status_msg) + माप(*status),
				     GFP_KERNEL);
		अगर (!status_msg)
			वापस -ENOMEM;

		status_msg->version = 0;
		status_msg->command = EC_CMD_GET_COMMS_STATUS;
		status_msg->insize = माप(*status);
		status_msg->outsize = 0;

		/*
		 * Query the EC's status until it's no दीर्घer busy or
		 * we encounter an error.
		 */
		क्रम (i = 0; i < EC_COMMAND_RETRIES; i++) अणु
			usleep_range(10000, 11000);

			trace_cros_ec_request_start(status_msg);
			ret = (*xfer_fxn)(ec_dev, status_msg);
			trace_cros_ec_request_करोne(status_msg, ret);
			अगर (ret == -EAGAIN)
				जारी;
			अगर (ret < 0)
				अवरोध;

			msg->result = status_msg->result;
			अगर (status_msg->result != EC_RES_SUCCESS)
				अवरोध;

			status = (काष्ठा ec_response_get_comms_status *)
				 status_msg->data;
			अगर (!(status->flags & EC_COMMS_STATUS_PROCESSING))
				अवरोध;
		पूर्ण

		kमुक्त(status_msg);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * cros_ec_prepare_tx() - Prepare an outgoing message in the output buffer.
 * @ec_dev: Device to रेजिस्टर.
 * @msg: Message to ग_लिखो.
 *
 * This is पूर्णांकended to be used by all ChromeOS EC drivers, but at present
 * only SPI uses it. Once LPC uses the same protocol it can start using it.
 * I2C could use it now, with a refactor of the existing code.
 *
 * Return: 0 on success or negative error code.
 */
पूर्णांक cros_ec_prepare_tx(काष्ठा cros_ec_device *ec_dev,
		       काष्ठा cros_ec_command *msg)
अणु
	u8 *out;
	u8 csum;
	पूर्णांक i;

	अगर (ec_dev->proto_version > 2)
		वापस prepare_packet(ec_dev, msg);

	BUG_ON(msg->outsize > EC_PROTO2_MAX_PARAM_SIZE);
	out = ec_dev->करोut;
	out[0] = EC_CMD_VERSION0 + msg->version;
	out[1] = msg->command;
	out[2] = msg->outsize;
	csum = out[0] + out[1] + out[2];
	क्रम (i = 0; i < msg->outsize; i++)
		csum += out[EC_MSG_TX_HEADER_BYTES + i] = msg->data[i];
	out[EC_MSG_TX_HEADER_BYTES + msg->outsize] = csum;

	वापस EC_MSG_TX_PROTO_BYTES + msg->outsize;
पूर्ण
EXPORT_SYMBOL(cros_ec_prepare_tx);

/**
 * cros_ec_check_result() - Check ec_msg->result.
 * @ec_dev: EC device.
 * @msg: Message to check.
 *
 * This is used by ChromeOS EC drivers to check the ec_msg->result क्रम
 * errors and to warn about them.
 *
 * Return: 0 on success or negative error code.
 */
पूर्णांक cros_ec_check_result(काष्ठा cros_ec_device *ec_dev,
			 काष्ठा cros_ec_command *msg)
अणु
	चयन (msg->result) अणु
	हाल EC_RES_SUCCESS:
		वापस 0;
	हाल EC_RES_IN_PROGRESS:
		dev_dbg(ec_dev->dev, "command 0x%02x in progress\n",
			msg->command);
		वापस -EAGAIN;
	शेष:
		dev_dbg(ec_dev->dev, "command 0x%02x returned %d\n",
			msg->command, msg->result);
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(cros_ec_check_result);

/*
 * cros_ec_get_host_event_wake_mask
 *
 * Get the mask of host events that cause wake from suspend.
 *
 * @ec_dev: EC device to call
 * @msg: message काष्ठाure to use
 * @mask: result when function वापसs >=0.
 *
 * LOCKING:
 * the caller has ec_dev->lock mutex, or the caller knows there is
 * no other command in progress.
 */
अटल पूर्णांक cros_ec_get_host_event_wake_mask(काष्ठा cros_ec_device *ec_dev,
					    काष्ठा cros_ec_command *msg,
					    uपूर्णांक32_t *mask)
अणु
	काष्ठा ec_response_host_event_mask *r;
	पूर्णांक ret;

	msg->command = EC_CMD_HOST_EVENT_GET_WAKE_MASK;
	msg->version = 0;
	msg->outsize = 0;
	msg->insize = माप(*r);

	ret = send_command(ec_dev, msg);
	अगर (ret >= 0) अणु
		अगर (msg->result == EC_RES_INVALID_COMMAND)
			वापस -EOPNOTSUPP;
		अगर (msg->result != EC_RES_SUCCESS)
			वापस -EPROTO;
	पूर्ण
	अगर (ret > 0) अणु
		r = (काष्ठा ec_response_host_event_mask *)msg->data;
		*mask = r->mask;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cros_ec_host_command_proto_query(काष्ठा cros_ec_device *ec_dev,
					    पूर्णांक devidx,
					    काष्ठा cros_ec_command *msg)
अणु
	/*
	 * Try using v3+ to query क्रम supported protocols. If this
	 * command fails, fall back to v2. Returns the highest protocol
	 * supported by the EC.
	 * Also sets the max request/response/passthru size.
	 */
	पूर्णांक ret;

	अगर (!ec_dev->pkt_xfer)
		वापस -EPROTONOSUPPORT;

	स_रखो(msg, 0, माप(*msg));
	msg->command = EC_CMD_PASSTHRU_OFFSET(devidx) | EC_CMD_GET_PROTOCOL_INFO;
	msg->insize = माप(काष्ठा ec_response_get_protocol_info);

	ret = send_command(ec_dev, msg);

	अगर (ret < 0) अणु
		dev_dbg(ec_dev->dev,
			"failed to check for EC[%d] protocol version: %d\n",
			devidx, ret);
		वापस ret;
	पूर्ण

	अगर (devidx > 0 && msg->result == EC_RES_INVALID_COMMAND)
		वापस -ENODEV;
	अन्यथा अगर (msg->result != EC_RES_SUCCESS)
		वापस msg->result;

	वापस 0;
पूर्ण

अटल पूर्णांक cros_ec_host_command_proto_query_v2(काष्ठा cros_ec_device *ec_dev)
अणु
	काष्ठा cros_ec_command *msg;
	काष्ठा ec_params_hello *hello_params;
	काष्ठा ec_response_hello *hello_response;
	पूर्णांक ret;
	पूर्णांक len = max(माप(*hello_params), माप(*hello_response));

	msg = kदो_स्मृति(माप(*msg) + len, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	msg->version = 0;
	msg->command = EC_CMD_HELLO;
	hello_params = (काष्ठा ec_params_hello *)msg->data;
	msg->outsize = माप(*hello_params);
	hello_response = (काष्ठा ec_response_hello *)msg->data;
	msg->insize = माप(*hello_response);

	hello_params->in_data = 0xa0b0c0d0;

	ret = send_command(ec_dev, msg);

	अगर (ret < 0) अणु
		dev_dbg(ec_dev->dev,
			"EC failed to respond to v2 hello: %d\n",
			ret);
		जाओ निकास;
	पूर्ण अन्यथा अगर (msg->result != EC_RES_SUCCESS) अणु
		dev_err(ec_dev->dev,
			"EC responded to v2 hello with error: %d\n",
			msg->result);
		ret = msg->result;
		जाओ निकास;
	पूर्ण अन्यथा अगर (hello_response->out_data != 0xa1b2c3d4) अणु
		dev_err(ec_dev->dev,
			"EC responded to v2 hello with bad result: %u\n",
			hello_response->out_data);
		ret = -EBADMSG;
		जाओ निकास;
	पूर्ण

	ret = 0;

 निकास:
	kमुक्त(msg);
	वापस ret;
पूर्ण

/*
 * cros_ec_get_host_command_version_mask
 *
 * Get the version mask of a given command.
 *
 * @ec_dev: EC device to call
 * @msg: message काष्ठाure to use
 * @cmd: command to get the version of.
 * @mask: result when function वापसs 0.
 *
 * @वापस 0 on success, error code otherwise
 *
 * LOCKING:
 * the caller has ec_dev->lock mutex or the caller knows there is
 * no other command in progress.
 */
अटल पूर्णांक cros_ec_get_host_command_version_mask(काष्ठा cros_ec_device *ec_dev,
	u16 cmd, u32 *mask)
अणु
	काष्ठा ec_params_get_cmd_versions *pver;
	काष्ठा ec_response_get_cmd_versions *rver;
	काष्ठा cros_ec_command *msg;
	पूर्णांक ret;

	msg = kदो_स्मृति(माप(*msg) + max(माप(*rver), माप(*pver)),
		      GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	msg->version = 0;
	msg->command = EC_CMD_GET_CMD_VERSIONS;
	msg->insize = माप(*rver);
	msg->outsize = माप(*pver);

	pver = (काष्ठा ec_params_get_cmd_versions *)msg->data;
	pver->cmd = cmd;

	ret = send_command(ec_dev, msg);
	अगर (ret > 0) अणु
		rver = (काष्ठा ec_response_get_cmd_versions *)msg->data;
		*mask = rver->version_mask;
	पूर्ण

	kमुक्त(msg);

	वापस ret;
पूर्ण

/**
 * cros_ec_query_all() -  Query the protocol version supported by the
 *         ChromeOS EC.
 * @ec_dev: Device to रेजिस्टर.
 *
 * Return: 0 on success or negative error code.
 */
पूर्णांक cros_ec_query_all(काष्ठा cros_ec_device *ec_dev)
अणु
	काष्ठा device *dev = ec_dev->dev;
	काष्ठा cros_ec_command *proto_msg;
	काष्ठा ec_response_get_protocol_info *proto_info;
	u32 ver_mask = 0;
	पूर्णांक ret;

	proto_msg = kzalloc(माप(*proto_msg) + माप(*proto_info),
			    GFP_KERNEL);
	अगर (!proto_msg)
		वापस -ENOMEM;

	/* First try sending with proto v3. */
	ec_dev->proto_version = 3;
	ret = cros_ec_host_command_proto_query(ec_dev, 0, proto_msg);

	अगर (ret == 0) अणु
		proto_info = (काष्ठा ec_response_get_protocol_info *)
			proto_msg->data;
		ec_dev->max_request = proto_info->max_request_packet_size -
			माप(काष्ठा ec_host_request);
		ec_dev->max_response = proto_info->max_response_packet_size -
			माप(काष्ठा ec_host_response);
		ec_dev->proto_version =
			min(EC_HOST_REQUEST_VERSION,
					fls(proto_info->protocol_versions) - 1);
		dev_dbg(ec_dev->dev,
			"using proto v%u\n",
			ec_dev->proto_version);

		ec_dev->din_size = ec_dev->max_response +
			माप(काष्ठा ec_host_response) +
			EC_MAX_RESPONSE_OVERHEAD;
		ec_dev->करोut_size = ec_dev->max_request +
			माप(काष्ठा ec_host_request) +
			EC_MAX_REQUEST_OVERHEAD;

		/*
		 * Check क्रम PD
		 */
		ret = cros_ec_host_command_proto_query(ec_dev, 1, proto_msg);

		अगर (ret) अणु
			dev_dbg(ec_dev->dev, "no PD chip found: %d\n", ret);
			ec_dev->max_passthru = 0;
		पूर्ण अन्यथा अणु
			dev_dbg(ec_dev->dev, "found PD chip\n");
			ec_dev->max_passthru =
				proto_info->max_request_packet_size -
				माप(काष्ठा ec_host_request);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Try querying with a v2 hello message. */
		ec_dev->proto_version = 2;
		ret = cros_ec_host_command_proto_query_v2(ec_dev);

		अगर (ret == 0) अणु
			/* V2 hello succeeded. */
			dev_dbg(ec_dev->dev, "falling back to proto v2\n");

			ec_dev->max_request = EC_PROTO2_MAX_PARAM_SIZE;
			ec_dev->max_response = EC_PROTO2_MAX_PARAM_SIZE;
			ec_dev->max_passthru = 0;
			ec_dev->pkt_xfer = शून्य;
			ec_dev->din_size = EC_PROTO2_MSG_BYTES;
			ec_dev->करोut_size = EC_PROTO2_MSG_BYTES;
		पूर्ण अन्यथा अणु
			/*
			 * It's possible क्रम a test to occur too early when
			 * the EC isn't listening. If this happens, we'll
			 * test later when the first command is run.
			 */
			ec_dev->proto_version = EC_PROTO_VERSION_UNKNOWN;
			dev_dbg(ec_dev->dev, "EC query failed: %d\n", ret);
			जाओ निकास;
		पूर्ण
	पूर्ण

	devm_kमुक्त(dev, ec_dev->din);
	devm_kमुक्त(dev, ec_dev->करोut);

	ec_dev->din = devm_kzalloc(dev, ec_dev->din_size, GFP_KERNEL);
	अगर (!ec_dev->din) अणु
		ret = -ENOMEM;
		जाओ निकास;
	पूर्ण

	ec_dev->करोut = devm_kzalloc(dev, ec_dev->करोut_size, GFP_KERNEL);
	अगर (!ec_dev->करोut) अणु
		devm_kमुक्त(dev, ec_dev->din);
		ret = -ENOMEM;
		जाओ निकास;
	पूर्ण

	/* Probe अगर MKBP event is supported */
	ret = cros_ec_get_host_command_version_mask(ec_dev,
						    EC_CMD_GET_NEXT_EVENT,
						    &ver_mask);
	अगर (ret < 0 || ver_mask == 0)
		ec_dev->mkbp_event_supported = 0;
	अन्यथा
		ec_dev->mkbp_event_supported = fls(ver_mask);

	dev_dbg(ec_dev->dev, "MKBP support version %u\n",
		ec_dev->mkbp_event_supported - 1);

	/* Probe अगर host sleep v1 is supported क्रम S0ix failure detection. */
	ret = cros_ec_get_host_command_version_mask(ec_dev,
						    EC_CMD_HOST_SLEEP_EVENT,
						    &ver_mask);
	ec_dev->host_sleep_v1 = (ret >= 0 && (ver_mask & EC_VER_MASK(1)));

	/* Get host event wake mask. */
	ret = cros_ec_get_host_event_wake_mask(ec_dev, proto_msg,
					       &ec_dev->host_event_wake_mask);
	अगर (ret < 0) अणु
		/*
		 * If the EC करोesn't support EC_CMD_HOST_EVENT_GET_WAKE_MASK,
		 * use a reasonable शेष. Note that we ignore various
		 * battery, AC status, and घातer-state events, because (a)
		 * those can be quite common (e.g., when sitting at full
		 * अक्षरge, on AC) and (b) these are not actionable wake events;
		 * अगर anything, we'd like to जारी suspending (to save
		 * घातer), not wake up.
		 */
		ec_dev->host_event_wake_mask = U32_MAX &
			~(EC_HOST_EVENT_MASK(EC_HOST_EVENT_LID_CLOSED) |
			  EC_HOST_EVENT_MASK(EC_HOST_EVENT_AC_DISCONNECTED) |
			  EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTERY_LOW) |
			  EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTERY_CRITICAL) |
			  EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTERY) |
			  EC_HOST_EVENT_MASK(EC_HOST_EVENT_PD_MCU) |
			  EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTERY_STATUS));
		/*
		 * Old ECs may not support this command. Complain about all
		 * other errors.
		 */
		अगर (ret != -EOPNOTSUPP)
			dev_err(ec_dev->dev,
				"failed to retrieve wake mask: %d\n", ret);
	पूर्ण

	ret = 0;

निकास:
	kमुक्त(proto_msg);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(cros_ec_query_all);

/**
 * cros_ec_cmd_xfer_status() - Send a command to the ChromeOS EC.
 * @ec_dev: EC device.
 * @msg: Message to ग_लिखो.
 *
 * Call this to send a command to the ChromeOS EC. This should be used instead of calling the EC's
 * cmd_xfer() callback directly. It वापसs success status only अगर both the command was transmitted
 * successfully and the EC replied with success status.
 *
 * Return:
 * >=0 - The number of bytes transferred
 * <0 - Linux error code
 */
पूर्णांक cros_ec_cmd_xfer_status(काष्ठा cros_ec_device *ec_dev,
			    काष्ठा cros_ec_command *msg)
अणु
	पूर्णांक ret, mapped;

	mutex_lock(&ec_dev->lock);
	अगर (ec_dev->proto_version == EC_PROTO_VERSION_UNKNOWN) अणु
		ret = cros_ec_query_all(ec_dev);
		अगर (ret) अणु
			dev_err(ec_dev->dev,
				"EC version unknown and query failed; aborting command\n");
			mutex_unlock(&ec_dev->lock);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (msg->insize > ec_dev->max_response) अणु
		dev_dbg(ec_dev->dev, "clamping message receive buffer\n");
		msg->insize = ec_dev->max_response;
	पूर्ण

	अगर (msg->command < EC_CMD_PASSTHRU_OFFSET(1)) अणु
		अगर (msg->outsize > ec_dev->max_request) अणु
			dev_err(ec_dev->dev,
				"request of size %u is too big (max: %u)\n",
				msg->outsize,
				ec_dev->max_request);
			mutex_unlock(&ec_dev->lock);
			वापस -EMSGSIZE;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (msg->outsize > ec_dev->max_passthru) अणु
			dev_err(ec_dev->dev,
				"passthru rq of size %u is too big (max: %u)\n",
				msg->outsize,
				ec_dev->max_passthru);
			mutex_unlock(&ec_dev->lock);
			वापस -EMSGSIZE;
		पूर्ण
	पूर्ण

	ret = send_command(ec_dev, msg);
	mutex_unlock(&ec_dev->lock);

	mapped = cros_ec_map_error(msg->result);
	अगर (mapped) अणु
		dev_dbg(ec_dev->dev, "Command result (err: %d [%d])\n",
			msg->result, mapped);
		ret = mapped;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(cros_ec_cmd_xfer_status);

अटल पूर्णांक get_next_event_xfer(काष्ठा cros_ec_device *ec_dev,
			       काष्ठा cros_ec_command *msg,
			       काष्ठा ec_response_get_next_event_v1 *event,
			       पूर्णांक version, uपूर्णांक32_t size)
अणु
	पूर्णांक ret;

	msg->version = version;
	msg->command = EC_CMD_GET_NEXT_EVENT;
	msg->insize = size;
	msg->outsize = 0;

	ret = cros_ec_cmd_xfer_status(ec_dev, msg);
	अगर (ret > 0) अणु
		ec_dev->event_size = ret - 1;
		ec_dev->event_data = *event;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक get_next_event(काष्ठा cros_ec_device *ec_dev)
अणु
	काष्ठा अणु
		काष्ठा cros_ec_command msg;
		काष्ठा ec_response_get_next_event_v1 event;
	पूर्ण __packed buf;
	काष्ठा cros_ec_command *msg = &buf.msg;
	काष्ठा ec_response_get_next_event_v1 *event = &buf.event;
	स्थिर पूर्णांक cmd_version = ec_dev->mkbp_event_supported - 1;

	स_रखो(msg, 0, माप(*msg));
	अगर (ec_dev->suspended) अणु
		dev_dbg(ec_dev->dev, "Device suspended.\n");
		वापस -EHOSTDOWN;
	पूर्ण

	अगर (cmd_version == 0)
		वापस get_next_event_xfer(ec_dev, msg, event, 0,
				  माप(काष्ठा ec_response_get_next_event));

	वापस get_next_event_xfer(ec_dev, msg, event, cmd_version,
				माप(काष्ठा ec_response_get_next_event_v1));
पूर्ण

अटल पूर्णांक get_keyboard_state_event(काष्ठा cros_ec_device *ec_dev)
अणु
	u8 buffer[माप(काष्ठा cros_ec_command) +
		  माप(ec_dev->event_data.data)];
	काष्ठा cros_ec_command *msg = (काष्ठा cros_ec_command *)&buffer;

	msg->version = 0;
	msg->command = EC_CMD_MKBP_STATE;
	msg->insize = माप(ec_dev->event_data.data);
	msg->outsize = 0;

	ec_dev->event_size = cros_ec_cmd_xfer_status(ec_dev, msg);
	ec_dev->event_data.event_type = EC_MKBP_EVENT_KEY_MATRIX;
	स_नकल(&ec_dev->event_data.data, msg->data,
	       माप(ec_dev->event_data.data));

	वापस ec_dev->event_size;
पूर्ण

/**
 * cros_ec_get_next_event() - Fetch next event from the ChromeOS EC.
 * @ec_dev: Device to fetch event from.
 * @wake_event: Poपूर्णांकer to a bool set to true upon वापस अगर the event might be
 *              treated as a wake event. Ignored अगर null.
 * @has_more_events: Poपूर्णांकer to bool set to true अगर more than one event is
 *              pending.
 *              Some EC will set this flag to indicate cros_ec_get_next_event()
 *              can be called multiple बार in a row.
 *              It is an optimization to prevent issuing a EC command क्रम
 *              nothing or रुको क्रम another पूर्णांकerrupt from the EC to process
 *              the next message.
 *              Ignored अगर null.
 *
 * Return: negative error code on errors; 0 क्रम no data; or अन्यथा number of
 * bytes received (i.e., an event was retrieved successfully). Event types are
 * written out to @ec_dev->event_data.event_type on success.
 */
पूर्णांक cros_ec_get_next_event(काष्ठा cros_ec_device *ec_dev,
			   bool *wake_event,
			   bool *has_more_events)
अणु
	u8 event_type;
	u32 host_event;
	पूर्णांक ret;

	/*
	 * Default value क्रम wake_event.
	 * Wake up on keyboard event, wake up क्रम spurious पूर्णांकerrupt or link
	 * error to the EC.
	 */
	अगर (wake_event)
		*wake_event = true;

	/*
	 * Default value क्रम has_more_events.
	 * EC will उठाओ another पूर्णांकerrupt अगर AP करोes not process all events
	 * anyway.
	 */
	अगर (has_more_events)
		*has_more_events = false;

	अगर (!ec_dev->mkbp_event_supported)
		वापस get_keyboard_state_event(ec_dev);

	ret = get_next_event(ec_dev);
	अगर (ret <= 0)
		वापस ret;

	अगर (has_more_events)
		*has_more_events = ec_dev->event_data.event_type &
			EC_MKBP_HAS_MORE_EVENTS;
	ec_dev->event_data.event_type &= EC_MKBP_EVENT_TYPE_MASK;

	अगर (wake_event) अणु
		event_type = ec_dev->event_data.event_type;
		host_event = cros_ec_get_host_event(ec_dev);

		/*
		 * Sensor events need to be parsed by the sensor sub-device.
		 * Defer them, and करोn't report the wakeup here.
		 */
		अगर (event_type == EC_MKBP_EVENT_SENSOR_FIFO) अणु
			*wake_event = false;
		पूर्ण अन्यथा अगर (host_event) अणु
			/* rtc_update_irq() alपढ़ोy handles wakeup events. */
			अगर (host_event & EC_HOST_EVENT_MASK(EC_HOST_EVENT_RTC))
				*wake_event = false;
			/* Masked host-events should not count as wake events. */
			अगर (!(host_event & ec_dev->host_event_wake_mask))
				*wake_event = false;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(cros_ec_get_next_event);

/**
 * cros_ec_get_host_event() - Return a mask of event set by the ChromeOS EC.
 * @ec_dev: Device to fetch event from.
 *
 * When MKBP is supported, when the EC उठाओs an पूर्णांकerrupt, we collect the
 * events उठाओd and call the functions in the ec notअगरier. This function
 * is a helper to know which events are उठाओd.
 *
 * Return: 0 on error or non-zero biपंचांगask of one or more EC_HOST_EVENT_*.
 */
u32 cros_ec_get_host_event(काष्ठा cros_ec_device *ec_dev)
अणु
	u32 host_event;

	BUG_ON(!ec_dev->mkbp_event_supported);

	अगर (ec_dev->event_data.event_type != EC_MKBP_EVENT_HOST_EVENT)
		वापस 0;

	अगर (ec_dev->event_size != माप(host_event)) अणु
		dev_warn(ec_dev->dev, "Invalid host event size\n");
		वापस 0;
	पूर्ण

	host_event = get_unaligned_le32(&ec_dev->event_data.data.host_event);

	वापस host_event;
पूर्ण
EXPORT_SYMBOL(cros_ec_get_host_event);

/**
 * cros_ec_check_features() - Test क्रम the presence of EC features
 *
 * @ec: EC device, करोes not have to be connected directly to the AP,
 *      can be daisy chained through another device.
 * @feature: One of ec_feature_code bit.
 *
 * Call this function to test whether the ChromeOS EC supports a feature.
 *
 * Return: 1 अगर supported, 0 अगर not
 */
पूर्णांक cros_ec_check_features(काष्ठा cros_ec_dev *ec, पूर्णांक feature)
अणु
	काष्ठा cros_ec_command *msg;
	पूर्णांक ret;

	अगर (ec->features[0] == -1U && ec->features[1] == -1U) अणु
		/* features biपंचांगap not पढ़ो yet */
		msg = kzalloc(माप(*msg) + माप(ec->features), GFP_KERNEL);
		अगर (!msg)
			वापस -ENOMEM;

		msg->command = EC_CMD_GET_FEATURES + ec->cmd_offset;
		msg->insize = माप(ec->features);

		ret = cros_ec_cmd_xfer_status(ec->ec_dev, msg);
		अगर (ret < 0) अणु
			dev_warn(ec->dev, "cannot get EC features: %d/%d\n",
				 ret, msg->result);
			स_रखो(ec->features, 0, माप(ec->features));
		पूर्ण अन्यथा अणु
			स_नकल(ec->features, msg->data, माप(ec->features));
		पूर्ण

		dev_dbg(ec->dev, "EC features %08x %08x\n",
			ec->features[0], ec->features[1]);

		kमुक्त(msg);
	पूर्ण

	वापस ec->features[feature / 32] & EC_FEATURE_MASK_0(feature);
पूर्ण
EXPORT_SYMBOL_GPL(cros_ec_check_features);

/**
 * cros_ec_get_sensor_count() - Return the number of MEMS sensors supported.
 *
 * @ec: EC device, करोes not have to be connected directly to the AP,
 *      can be daisy chained through another device.
 * Return: < 0 in हाल of error.
 */
पूर्णांक cros_ec_get_sensor_count(काष्ठा cros_ec_dev *ec)
अणु
	/*
	 * Issue a command to get the number of sensor reported.
	 * If not supported, check क्रम legacy mode.
	 */
	पूर्णांक ret, sensor_count;
	काष्ठा ec_params_motion_sense *params;
	काष्ठा ec_response_motion_sense *resp;
	काष्ठा cros_ec_command *msg;
	काष्ठा cros_ec_device *ec_dev = ec->ec_dev;
	u8 status;

	msg = kzalloc(माप(*msg) + max(माप(*params), माप(*resp)),
		      GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	msg->version = 1;
	msg->command = EC_CMD_MOTION_SENSE_CMD + ec->cmd_offset;
	msg->outsize = माप(*params);
	msg->insize = माप(*resp);

	params = (काष्ठा ec_params_motion_sense *)msg->data;
	params->cmd = MOTIONSENSE_CMD_DUMP;

	ret = cros_ec_cmd_xfer_status(ec->ec_dev, msg);
	अगर (ret < 0) अणु
		sensor_count = ret;
	पूर्ण अन्यथा अणु
		resp = (काष्ठा ec_response_motion_sense *)msg->data;
		sensor_count = resp->dump.sensor_count;
	पूर्ण
	kमुक्त(msg);

	/*
	 * Check legacy mode: Let's find out अगर sensors are accessible
	 * via LPC पूर्णांकerface.
	 */
	अगर (sensor_count < 0 && ec->cmd_offset == 0 && ec_dev->cmd_पढ़ोmem) अणु
		ret = ec_dev->cmd_पढ़ोmem(ec_dev, EC_MEMMAP_ACC_STATUS,
				1, &status);
		अगर (ret >= 0 &&
		    (status & EC_MEMMAP_ACC_STATUS_PRESENCE_BIT)) अणु
			/*
			 * We have 2 sensors, one in the lid, one in the base.
			 */
			sensor_count = 2;
		पूर्ण अन्यथा अणु
			/*
			 * EC uses LPC पूर्णांकerface and no sensors are presented.
			 */
			sensor_count = 0;
		पूर्ण
	पूर्ण
	वापस sensor_count;
पूर्ण
EXPORT_SYMBOL_GPL(cros_ec_get_sensor_count);
