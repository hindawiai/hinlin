<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// ISHTP पूर्णांकerface क्रम ChromeOS Embedded Controller
//
// Copyright (c) 2019, Intel Corporation.
//
// ISHTP client driver क्रम talking to the Chrome OS EC firmware running
// on Intel Integrated Sensor Hub (ISH) using the ISH Transport protocol
// (ISH-TP).

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/पूर्णांकel-ish-client-अगर.h>

#समावेश "cros_ec.h"

/*
 * ISH TX/RX ring buffer pool size
 *
 * The AP->ISH messages and corresponding ISH->AP responses are
 * serialized. We need 1 TX and 1 RX buffer क्रम these.
 *
 * The MKBP ISH->AP events are serialized. We need one additional RX
 * buffer क्रम them.
 */
#घोषणा CROS_ISH_CL_TX_RING_SIZE		8
#घोषणा CROS_ISH_CL_RX_RING_SIZE		8

/* ISH CrOS EC Host Commands */
क्रमागत cros_ec_ish_channel अणु
	CROS_EC_COMMAND = 1,			/* AP->ISH message */
	CROS_MKBP_EVENT = 2,			/* ISH->AP events */
पूर्ण;

/*
 * ISH firmware समयout क्रम 1 message send failure is 1Hz, and the
 * firmware will retry 2 बार, so 3Hz is used क्रम समयout.
 */
#घोषणा ISHTP_SEND_TIMEOUT			(3 * HZ)

/* ISH Transport CrOS EC ISH client unique GUID */
अटल स्थिर guid_t cros_ish_guid =
	GUID_INIT(0x7b7154d0, 0x56f4, 0x4bdc,
		  0xb0, 0xd8, 0x9e, 0x7c, 0xda,	0xe0, 0xd6, 0xa0);

काष्ठा header अणु
	u8 channel;
	u8 status;
	u8 token;
	u8 reserved;
पूर्ण __packed;

काष्ठा cros_ish_out_msg अणु
	काष्ठा header hdr;
	काष्ठा ec_host_request ec_request;
पूर्ण __packed;

काष्ठा cros_ish_in_msg अणु
	काष्ठा header hdr;
	काष्ठा ec_host_response ec_response;
पूर्ण __packed;

#घोषणा IN_MSG_EC_RESPONSE_PREAMBLE					\
	दुरत्व(काष्ठा cros_ish_in_msg, ec_response)

#घोषणा OUT_MSG_EC_REQUEST_PREAMBLE					\
	दुरत्व(काष्ठा cros_ish_out_msg, ec_request)

#घोषणा cl_data_to_dev(client_data) ishtp_device((client_data)->cl_device)

/*
 * The Read-Write Semaphore is used to prevent message TX or RX जबतक
 * the ishtp client is being initialized or undergoing reset.
 *
 * The पढ़ोers are the kernel function calls responsible क्रम IA->ISH
 * and ISH->AP messaging.
 *
 * The ग_लिखोrs are .reset() and .probe() function.
 */
अटल DECLARE_RWSEM(init_lock);

/**
 * काष्ठा response_info - Encapsulate firmware response related
 * inक्रमmation क्रम passing between function ish_send() and
 * process_recv() callback.
 *
 * @data: Copy the data received from firmware here.
 * @max_size: Max size allocated क्रम the @data buffer. If the received
 * data exceeds this value, we log an error.
 * @size: Actual size of data received from firmware.
 * @error: 0 क्रम success, negative error code क्रम a failure in process_recv().
 * @token: Expected token क्रम response that we are रुकोing on.
 * @received: Set to true on receiving a valid firmware	response to host command
 * @रुको_queue: Wait queue क्रम host to रुको क्रम firmware response.
 */
काष्ठा response_info अणु
	व्योम *data;
	माप_प्रकार max_size;
	माप_प्रकार size;
	पूर्णांक error;
	u8 token;
	bool received;
	रुको_queue_head_t रुको_queue;
पूर्ण;

/**
 * काष्ठा ishtp_cl_data - Encapsulate per ISH TP Client.
 *
 * @cros_ish_cl: ISHTP firmware client instance.
 * @cl_device: ISHTP client device instance.
 * @response: Response info passing between ish_send() and process_recv().
 * @work_ishtp_reset: Work queue reset handling.
 * @work_ec_evt: Work queue क्रम EC events.
 * @ec_dev: CrOS EC MFD device.
 *
 * This काष्ठाure is used to store per client data.
 */
काष्ठा ishtp_cl_data अणु
	काष्ठा ishtp_cl *cros_ish_cl;
	काष्ठा ishtp_cl_device *cl_device;

	/*
	 * Used क्रम passing firmware response inक्रमmation between
	 * ish_send() and process_recv() callback.
	 */
	काष्ठा response_info response;

	काष्ठा work_काष्ठा work_ishtp_reset;
	काष्ठा work_काष्ठा work_ec_evt;
	काष्ठा cros_ec_device *ec_dev;
पूर्ण;

/**
 * ish_evt_handler - ISH to AP event handler
 * @work: Work काष्ठा
 */
अटल व्योम ish_evt_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ishtp_cl_data *client_data =
		container_of(work, काष्ठा ishtp_cl_data, work_ec_evt);

	cros_ec_irq_thपढ़ो(0, client_data->ec_dev);
पूर्ण

/**
 * ish_send() - Send message from host to firmware
 *
 * @client_data: Client data instance
 * @out_msg: Message buffer to be sent to firmware
 * @out_size: Size of out going message
 * @in_msg: Message buffer where the incoming data is copied. This buffer
 * is allocated by calling
 * @in_size: Max size of incoming message
 *
 * Return: Number of bytes copied in the in_msg on success, negative
 * error code on failure.
 */
अटल पूर्णांक ish_send(काष्ठा ishtp_cl_data *client_data,
		    u8 *out_msg, माप_प्रकार out_size,
		    u8 *in_msg, माप_प्रकार in_size)
अणु
	अटल u8 next_token;
	पूर्णांक rv;
	काष्ठा header *out_hdr = (काष्ठा header *)out_msg;
	काष्ठा ishtp_cl *cros_ish_cl = client_data->cros_ish_cl;

	dev_dbg(cl_data_to_dev(client_data),
		"%s: channel=%02u status=%02u\n",
		__func__, out_hdr->channel, out_hdr->status);

	/* Setup क्रम incoming response */
	client_data->response.data = in_msg;
	client_data->response.max_size = in_size;
	client_data->response.error = 0;
	client_data->response.token = next_token++;
	client_data->response.received = false;

	out_hdr->token = client_data->response.token;

	rv = ishtp_cl_send(cros_ish_cl, out_msg, out_size);
	अगर (rv) अणु
		dev_err(cl_data_to_dev(client_data),
			"ishtp_cl_send error %d\n", rv);
		वापस rv;
	पूर्ण

	रुको_event_पूर्णांकerruptible_समयout(client_data->response.रुको_queue,
					 client_data->response.received,
					 ISHTP_SEND_TIMEOUT);
	अगर (!client_data->response.received) अणु
		dev_err(cl_data_to_dev(client_data),
			"Timed out for response to host message\n");
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (client_data->response.error < 0)
		वापस client_data->response.error;

	वापस client_data->response.size;
पूर्ण

/**
 * process_recv() - Received and parse incoming packet
 * @cros_ish_cl: Client instance to get stats
 * @rb_in_proc: Host पूर्णांकerface message buffer
 * @बारtamp: Timestamp of when parent callback started
 *
 * Parse the incoming packet. If it is a response packet then it will
 * update per instance flags and wake up the caller रुकोing to क्रम the
 * response. If it is an event packet then it will schedule event work.
 */
अटल व्योम process_recv(काष्ठा ishtp_cl *cros_ish_cl,
			 काष्ठा ishtp_cl_rb *rb_in_proc, kसमय_प्रकार बारtamp)
अणु
	माप_प्रकार data_len = rb_in_proc->buf_idx;
	काष्ठा ishtp_cl_data *client_data =
		ishtp_get_client_data(cros_ish_cl);
	काष्ठा device *dev = cl_data_to_dev(client_data);
	काष्ठा cros_ish_in_msg *in_msg =
		(काष्ठा cros_ish_in_msg *)rb_in_proc->buffer.data;

	/* Proceed only अगर reset or init is not in progress */
	अगर (!करोwn_पढ़ो_trylock(&init_lock)) अणु
		/* Free the buffer */
		ishtp_cl_io_rb_recycle(rb_in_proc);
		dev_warn(dev,
			 "Host is not ready to receive incoming messages\n");
		वापस;
	पूर्ण

	/*
	 * All firmware messages contain a header. Check the buffer size
	 * beक्रमe accessing elements inside.
	 */
	अगर (!rb_in_proc->buffer.data) अणु
		dev_warn(dev, "rb_in_proc->buffer.data returned null");
		client_data->response.error = -EBADMSG;
		जाओ end_error;
	पूर्ण

	अगर (data_len < माप(काष्ठा header)) अणु
		dev_err(dev, "data size %zu is less than header %zu\n",
			data_len, माप(काष्ठा header));
		client_data->response.error = -EMSGSIZE;
		जाओ end_error;
	पूर्ण

	dev_dbg(dev, "channel=%02u status=%02u\n",
		in_msg->hdr.channel, in_msg->hdr.status);

	चयन (in_msg->hdr.channel) अणु
	हाल CROS_EC_COMMAND:
		अगर (client_data->response.received) अणु
			dev_err(dev,
				"Previous firmware message not yet processed\n");
			जाओ end_error;
		पूर्ण

		अगर (client_data->response.token != in_msg->hdr.token) अणु
			dev_err_ratelimited(dev,
					    "Dropping old response token %d\n",
					    in_msg->hdr.token);
			जाओ end_error;
		पूर्ण

		/* Sanity check */
		अगर (!client_data->response.data) अणु
			dev_err(dev,
				"Receiving buffer is null. Should be allocated by calling function\n");
			client_data->response.error = -EINVAL;
			जाओ error_wake_up;
		पूर्ण

		अगर (data_len > client_data->response.max_size) अणु
			dev_err(dev,
				"Received buffer size %zu is larger than allocated buffer %zu\n",
				data_len, client_data->response.max_size);
			client_data->response.error = -EMSGSIZE;
			जाओ error_wake_up;
		पूर्ण

		अगर (in_msg->hdr.status) अणु
			dev_err(dev, "firmware returned status %d\n",
				in_msg->hdr.status);
			client_data->response.error = -EIO;
			जाओ error_wake_up;
		पूर्ण

		/* Update the actual received buffer size */
		client_data->response.size = data_len;

		/*
		 * Copy the buffer received in firmware response क्रम the
		 * calling thपढ़ो.
		 */
		स_नकल(client_data->response.data,
		       rb_in_proc->buffer.data, data_len);

error_wake_up:
		/* Free the buffer since we copied data or didn't need it */
		ishtp_cl_io_rb_recycle(rb_in_proc);
		rb_in_proc = शून्य;

		/* Set flag beक्रमe waking up the caller */
		client_data->response.received = true;

		/* Wake the calling thपढ़ो */
		wake_up_पूर्णांकerruptible(&client_data->response.रुको_queue);

		अवरोध;

	हाल CROS_MKBP_EVENT:
		/* Free the buffer. This is just an event without data */
		ishtp_cl_io_rb_recycle(rb_in_proc);
		rb_in_proc = शून्य;
		/*
		 * Set बारtamp from beginning of function since we actually
		 * got an incoming MKBP event
		 */
		client_data->ec_dev->last_event_समय = बारtamp;
		schedule_work(&client_data->work_ec_evt);

		अवरोध;

	शेष:
		dev_err(dev, "Invalid channel=%02d\n", in_msg->hdr.channel);
	पूर्ण

end_error:
	/* Free the buffer अगर we alपढ़ोy haven't */
	अगर (rb_in_proc)
		ishtp_cl_io_rb_recycle(rb_in_proc);

	up_पढ़ो(&init_lock);
पूर्ण

/**
 * ish_event_cb() - bus driver callback क्रम incoming message
 * @cl_device: ISHTP client device क्रम which this message is targeted.
 *
 * Remove the packet from the list and process the message by calling
 * process_recv.
 */
अटल व्योम ish_event_cb(काष्ठा ishtp_cl_device *cl_device)
अणु
	काष्ठा ishtp_cl_rb *rb_in_proc;
	काष्ठा ishtp_cl	*cros_ish_cl = ishtp_get_drvdata(cl_device);
	kसमय_प्रकार बारtamp;

	/*
	 * Take बारtamp as बंद to hardware पूर्णांकerrupt as possible क्रम sensor
	 * बारtamps.
	 */
	बारtamp = cros_ec_get_समय_ns();

	जबतक ((rb_in_proc = ishtp_cl_rx_get_rb(cros_ish_cl)) != शून्य) अणु
		/* Decide what to करो with received data */
		process_recv(cros_ish_cl, rb_in_proc, बारtamp);
	पूर्ण
पूर्ण

/**
 * cros_ish_init() - Init function क्रम ISHTP client
 * @cros_ish_cl: ISHTP client instance
 *
 * This function complete the initializtion of the client.
 *
 * Return: 0 क्रम success, negative error code क्रम failure.
 */
अटल पूर्णांक cros_ish_init(काष्ठा ishtp_cl *cros_ish_cl)
अणु
	पूर्णांक rv;
	काष्ठा ishtp_device *dev;
	काष्ठा ishtp_fw_client *fw_client;
	काष्ठा ishtp_cl_data *client_data = ishtp_get_client_data(cros_ish_cl);

	rv = ishtp_cl_link(cros_ish_cl);
	अगर (rv) अणु
		dev_err(cl_data_to_dev(client_data),
			"ishtp_cl_link failed\n");
		वापस rv;
	पूर्ण

	dev = ishtp_get_ishtp_device(cros_ish_cl);

	/* Connect to firmware client */
	ishtp_set_tx_ring_size(cros_ish_cl, CROS_ISH_CL_TX_RING_SIZE);
	ishtp_set_rx_ring_size(cros_ish_cl, CROS_ISH_CL_RX_RING_SIZE);

	fw_client = ishtp_fw_cl_get_client(dev, &cros_ish_guid);
	अगर (!fw_client) अणु
		dev_err(cl_data_to_dev(client_data),
			"ish client uuid not found\n");
		rv = -ENOENT;
		जाओ err_cl_unlink;
	पूर्ण

	ishtp_cl_set_fw_client_id(cros_ish_cl,
				  ishtp_get_fw_client_id(fw_client));
	ishtp_set_connection_state(cros_ish_cl, ISHTP_CL_CONNECTING);

	rv = ishtp_cl_connect(cros_ish_cl);
	अगर (rv) अणु
		dev_err(cl_data_to_dev(client_data),
			"client connect fail\n");
		जाओ err_cl_unlink;
	पूर्ण

	ishtp_रेजिस्टर_event_cb(client_data->cl_device, ish_event_cb);
	वापस 0;

err_cl_unlink:
	ishtp_cl_unlink(cros_ish_cl);
	वापस rv;
पूर्ण

/**
 * cros_ish_deinit() - Deinit function क्रम ISHTP client
 * @cros_ish_cl: ISHTP client instance
 *
 * Unlink and मुक्त cros_ec client
 */
अटल व्योम cros_ish_deinit(काष्ठा ishtp_cl *cros_ish_cl)
अणु
	ishtp_set_connection_state(cros_ish_cl, ISHTP_CL_DISCONNECTING);
	ishtp_cl_disconnect(cros_ish_cl);
	ishtp_cl_unlink(cros_ish_cl);
	ishtp_cl_flush_queues(cros_ish_cl);

	/* Disband and मुक्त all Tx and Rx client-level rings */
	ishtp_cl_मुक्त(cros_ish_cl);
पूर्ण

/**
 * prepare_cros_ec_rx() - Check & prepare receive buffer
 * @ec_dev: CrOS EC MFD device.
 * @in_msg: Incoming message buffer
 * @msg: cros_ec command used to send & receive data
 *
 * Return: 0 क्रम success, negative error code क्रम failure.
 *
 * Check the received buffer. Convert to cros_ec_command क्रमmat.
 */
अटल पूर्णांक prepare_cros_ec_rx(काष्ठा cros_ec_device *ec_dev,
			      स्थिर काष्ठा cros_ish_in_msg *in_msg,
			      काष्ठा cros_ec_command *msg)
अणु
	u8 sum = 0;
	पूर्णांक i, rv, offset;

	/* Check response error code */
	msg->result = in_msg->ec_response.result;
	rv = cros_ec_check_result(ec_dev, msg);
	अगर (rv < 0)
		वापस rv;

	अगर (in_msg->ec_response.data_len > msg->insize) अणु
		dev_err(ec_dev->dev, "Packet too long (%d bytes, expected %d)",
			in_msg->ec_response.data_len, msg->insize);
		वापस -ENOSPC;
	पूर्ण

	/* Copy response packet payload and compute checksum */
	क्रम (i = 0; i < माप(काष्ठा ec_host_response); i++)
		sum += ((u8 *)in_msg)[IN_MSG_EC_RESPONSE_PREAMBLE + i];

	offset = माप(काष्ठा cros_ish_in_msg);
	क्रम (i = 0; i < in_msg->ec_response.data_len; i++)
		sum += msg->data[i] = ((u8 *)in_msg)[offset + i];

	अगर (sum) अणु
		dev_dbg(ec_dev->dev, "Bad received packet checksum %d\n", sum);
		वापस -EBADMSG;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cros_ec_pkt_xfer_ish(काष्ठा cros_ec_device *ec_dev,
				काष्ठा cros_ec_command *msg)
अणु
	पूर्णांक rv;
	काष्ठा ishtp_cl *cros_ish_cl = ec_dev->priv;
	काष्ठा ishtp_cl_data *client_data = ishtp_get_client_data(cros_ish_cl);
	काष्ठा device *dev = cl_data_to_dev(client_data);
	काष्ठा cros_ish_in_msg *in_msg = (काष्ठा cros_ish_in_msg *)ec_dev->din;
	काष्ठा cros_ish_out_msg *out_msg =
		(काष्ठा cros_ish_out_msg *)ec_dev->करोut;
	माप_प्रकार in_size = माप(काष्ठा cros_ish_in_msg) + msg->insize;
	माप_प्रकार out_size = माप(काष्ठा cros_ish_out_msg) + msg->outsize;

	/* Sanity checks */
	अगर (in_size > ec_dev->din_size) अणु
		dev_err(dev,
			"Incoming payload size %zu is too large for ec_dev->din_size %d\n",
			in_size, ec_dev->din_size);
		वापस -EMSGSIZE;
	पूर्ण

	अगर (out_size > ec_dev->करोut_size) अणु
		dev_err(dev,
			"Outgoing payload size %zu is too large for ec_dev->dout_size %d\n",
			out_size, ec_dev->करोut_size);
		वापस -EMSGSIZE;
	पूर्ण

	/* Proceed only अगर reset-init is not in progress */
	अगर (!करोwn_पढ़ो_trylock(&init_lock)) अणु
		dev_warn(dev,
			 "Host is not ready to send messages to ISH. Try again\n");
		वापस -EAGAIN;
	पूर्ण

	/* Prepare the package to be sent over ISH TP */
	out_msg->hdr.channel = CROS_EC_COMMAND;
	out_msg->hdr.status = 0;

	ec_dev->करोut += OUT_MSG_EC_REQUEST_PREAMBLE;
	cros_ec_prepare_tx(ec_dev, msg);
	ec_dev->करोut -= OUT_MSG_EC_REQUEST_PREAMBLE;

	dev_dbg(dev,
		"out_msg: struct_ver=0x%x checksum=0x%x command=0x%x command_ver=0x%x data_len=0x%x\n",
		out_msg->ec_request.काष्ठा_version,
		out_msg->ec_request.checksum,
		out_msg->ec_request.command,
		out_msg->ec_request.command_version,
		out_msg->ec_request.data_len);

	/* Send command to ISH EC firmware and पढ़ो response */
	rv = ish_send(client_data,
		      (u8 *)out_msg, out_size,
		      (u8 *)in_msg, in_size);
	अगर (rv < 0)
		जाओ end_error;

	rv = prepare_cros_ec_rx(ec_dev, in_msg, msg);
	अगर (rv)
		जाओ end_error;

	rv = in_msg->ec_response.data_len;

	dev_dbg(dev,
		"in_msg: struct_ver=0x%x checksum=0x%x result=0x%x data_len=0x%x\n",
		in_msg->ec_response.काष्ठा_version,
		in_msg->ec_response.checksum,
		in_msg->ec_response.result,
		in_msg->ec_response.data_len);

end_error:
	अगर (msg->command == EC_CMD_REBOOT_EC)
		msleep(EC_REBOOT_DELAY_MS);

	up_पढ़ो(&init_lock);

	वापस rv;
पूर्ण

अटल पूर्णांक cros_ec_dev_init(काष्ठा ishtp_cl_data *client_data)
अणु
	काष्ठा cros_ec_device *ec_dev;
	काष्ठा device *dev = cl_data_to_dev(client_data);

	ec_dev = devm_kzalloc(dev, माप(*ec_dev), GFP_KERNEL);
	अगर (!ec_dev)
		वापस -ENOMEM;

	client_data->ec_dev = ec_dev;
	dev->driver_data = ec_dev;

	ec_dev->dev = dev;
	ec_dev->priv = client_data->cros_ish_cl;
	ec_dev->cmd_xfer = शून्य;
	ec_dev->pkt_xfer = cros_ec_pkt_xfer_ish;
	ec_dev->phys_name = dev_name(dev);
	ec_dev->din_size = माप(काष्ठा cros_ish_in_msg) +
			   माप(काष्ठा ec_response_get_protocol_info);
	ec_dev->करोut_size = माप(काष्ठा cros_ish_out_msg);

	वापस cros_ec_रेजिस्टर(ec_dev);
पूर्ण

अटल व्योम reset_handler(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक rv;
	काष्ठा device *dev;
	काष्ठा ishtp_cl *cros_ish_cl;
	काष्ठा ishtp_cl_device *cl_device;
	काष्ठा ishtp_cl_data *client_data =
		container_of(work, काष्ठा ishtp_cl_data, work_ishtp_reset);

	/* Lock क्रम reset to complete */
	करोwn_ग_लिखो(&init_lock);

	cros_ish_cl = client_data->cros_ish_cl;
	cl_device = client_data->cl_device;

	/* Unlink, flush queues & start again */
	ishtp_cl_unlink(cros_ish_cl);
	ishtp_cl_flush_queues(cros_ish_cl);
	ishtp_cl_मुक्त(cros_ish_cl);

	cros_ish_cl = ishtp_cl_allocate(cl_device);
	अगर (!cros_ish_cl) अणु
		up_ग_लिखो(&init_lock);
		वापस;
	पूर्ण

	ishtp_set_drvdata(cl_device, cros_ish_cl);
	ishtp_set_client_data(cros_ish_cl, client_data);
	client_data->cros_ish_cl = cros_ish_cl;

	rv = cros_ish_init(cros_ish_cl);
	अगर (rv) अणु
		ishtp_cl_मुक्त(cros_ish_cl);
		dev_err(cl_data_to_dev(client_data), "Reset Failed\n");
		up_ग_लिखो(&init_lock);
		वापस;
	पूर्ण

	/* Refresh ec_dev device poपूर्णांकers */
	client_data->ec_dev->priv = client_data->cros_ish_cl;
	dev = cl_data_to_dev(client_data);
	dev->driver_data = client_data->ec_dev;

	dev_info(cl_data_to_dev(client_data), "Chrome EC ISH reset done\n");

	up_ग_लिखो(&init_lock);
पूर्ण

/**
 * cros_ec_ishtp_probe() - ISHTP client driver probe callback
 * @cl_device: ISHTP client device instance
 *
 * Return: 0 क्रम success, negative error code क्रम failure.
 */
अटल पूर्णांक cros_ec_ishtp_probe(काष्ठा ishtp_cl_device *cl_device)
अणु
	पूर्णांक rv;
	काष्ठा ishtp_cl *cros_ish_cl;
	काष्ठा ishtp_cl_data *client_data =
		devm_kzalloc(ishtp_device(cl_device),
			     माप(*client_data), GFP_KERNEL);
	अगर (!client_data)
		वापस -ENOMEM;

	/* Lock क्रम initialization to complete */
	करोwn_ग_लिखो(&init_lock);

	cros_ish_cl = ishtp_cl_allocate(cl_device);
	अगर (!cros_ish_cl) अणु
		rv = -ENOMEM;
		जाओ end_ishtp_cl_alloc_error;
	पूर्ण

	ishtp_set_drvdata(cl_device, cros_ish_cl);
	ishtp_set_client_data(cros_ish_cl, client_data);
	client_data->cros_ish_cl = cros_ish_cl;
	client_data->cl_device = cl_device;

	init_रुकोqueue_head(&client_data->response.रुको_queue);

	INIT_WORK(&client_data->work_ishtp_reset,
		  reset_handler);
	INIT_WORK(&client_data->work_ec_evt,
		  ish_evt_handler);

	rv = cros_ish_init(cros_ish_cl);
	अगर (rv)
		जाओ end_ishtp_cl_init_error;

	ishtp_get_device(cl_device);

	up_ग_लिखो(&init_lock);

	/* Register croc_ec_dev mfd */
	rv = cros_ec_dev_init(client_data);
	अगर (rv) अणु
		करोwn_ग_लिखो(&init_lock);
		जाओ end_cros_ec_dev_init_error;
	पूर्ण

	वापस 0;

end_cros_ec_dev_init_error:
	ishtp_set_connection_state(cros_ish_cl, ISHTP_CL_DISCONNECTING);
	ishtp_cl_disconnect(cros_ish_cl);
	ishtp_cl_unlink(cros_ish_cl);
	ishtp_cl_flush_queues(cros_ish_cl);
	ishtp_put_device(cl_device);
end_ishtp_cl_init_error:
	ishtp_cl_मुक्त(cros_ish_cl);
end_ishtp_cl_alloc_error:
	up_ग_लिखो(&init_lock);
	वापस rv;
पूर्ण

/**
 * cros_ec_ishtp_हटाओ() - ISHTP client driver हटाओ callback
 * @cl_device: ISHTP client device instance
 *
 * Return: 0
 */
अटल पूर्णांक cros_ec_ishtp_हटाओ(काष्ठा ishtp_cl_device *cl_device)
अणु
	काष्ठा ishtp_cl	*cros_ish_cl = ishtp_get_drvdata(cl_device);
	काष्ठा ishtp_cl_data *client_data = ishtp_get_client_data(cros_ish_cl);

	cancel_work_sync(&client_data->work_ishtp_reset);
	cancel_work_sync(&client_data->work_ec_evt);
	cros_ish_deinit(cros_ish_cl);
	ishtp_put_device(cl_device);

	वापस 0;
पूर्ण

/**
 * cros_ec_ishtp_reset() - ISHTP client driver reset callback
 * @cl_device: ISHTP client device instance
 *
 * Return: 0
 */
अटल पूर्णांक cros_ec_ishtp_reset(काष्ठा ishtp_cl_device *cl_device)
अणु
	काष्ठा ishtp_cl	*cros_ish_cl = ishtp_get_drvdata(cl_device);
	काष्ठा ishtp_cl_data *client_data = ishtp_get_client_data(cros_ish_cl);

	schedule_work(&client_data->work_ishtp_reset);

	वापस 0;
पूर्ण

/**
 * cros_ec_ishtp_suspend() - ISHTP client driver suspend callback
 * @device: device instance
 *
 * Return: 0 क्रम success, negative error code क्रम failure.
 */
अटल पूर्णांक __maybe_unused cros_ec_ishtp_suspend(काष्ठा device *device)
अणु
	काष्ठा ishtp_cl_device *cl_device = ishtp_dev_to_cl_device(device);
	काष्ठा ishtp_cl	*cros_ish_cl = ishtp_get_drvdata(cl_device);
	काष्ठा ishtp_cl_data *client_data = ishtp_get_client_data(cros_ish_cl);

	वापस cros_ec_suspend(client_data->ec_dev);
पूर्ण

/**
 * cros_ec_ishtp_resume() - ISHTP client driver resume callback
 * @device: device instance
 *
 * Return: 0 क्रम success, negative error code क्रम failure.
 */
अटल पूर्णांक __maybe_unused cros_ec_ishtp_resume(काष्ठा device *device)
अणु
	काष्ठा ishtp_cl_device *cl_device = ishtp_dev_to_cl_device(device);
	काष्ठा ishtp_cl	*cros_ish_cl = ishtp_get_drvdata(cl_device);
	काष्ठा ishtp_cl_data *client_data = ishtp_get_client_data(cros_ish_cl);

	वापस cros_ec_resume(client_data->ec_dev);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(cros_ec_ishtp_pm_ops, cros_ec_ishtp_suspend,
			 cros_ec_ishtp_resume);

अटल काष्ठा ishtp_cl_driver	cros_ec_ishtp_driver = अणु
	.name = "cros_ec_ishtp",
	.guid = &cros_ish_guid,
	.probe = cros_ec_ishtp_probe,
	.हटाओ = cros_ec_ishtp_हटाओ,
	.reset = cros_ec_ishtp_reset,
	.driver = अणु
		.pm = &cros_ec_ishtp_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init cros_ec_ishtp_mod_init(व्योम)
अणु
	वापस ishtp_cl_driver_रेजिस्टर(&cros_ec_ishtp_driver, THIS_MODULE);
पूर्ण

अटल व्योम __निकास cros_ec_ishtp_mod_निकास(व्योम)
अणु
	ishtp_cl_driver_unरेजिस्टर(&cros_ec_ishtp_driver);
पूर्ण

module_init(cros_ec_ishtp_mod_init);
module_निकास(cros_ec_ishtp_mod_निकास);

MODULE_DESCRIPTION("ChromeOS EC ISHTP Client Driver");
MODULE_AUTHOR("Rushikesh S Kadam <rushikesh.s.kadam@intel.com>");

MODULE_LICENSE("GPL v2");
MODULE_ALIAS("ishtp:*");
