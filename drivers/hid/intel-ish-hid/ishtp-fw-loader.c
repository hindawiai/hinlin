<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ISH-TP client driver क्रम ISH firmware loading
 *
 * Copyright (c) 2019, Intel Corporation.
 */

#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकel-ish-client-अगर.h>
#समावेश <linux/property.h>
#समावेश <यंत्र/cacheflush.h>

/* Number of बार we attempt to load the firmware beक्रमe giving up */
#घोषणा MAX_LOAD_ATTEMPTS			3

/* ISH TX/RX ring buffer pool size */
#घोषणा LOADER_CL_RX_RING_SIZE			1
#घोषणा LOADER_CL_TX_RING_SIZE			1

/*
 * ISH Shim firmware loader reserves 4 Kb buffer in SRAM. The buffer is
 * used to temporarily hold the data transferred from host to Shim
 * firmware loader. Reason क्रम the odd size of 3968 bytes? Each IPC
 * transfer is 128 bytes (= 4 bytes header + 124 bytes payload). So the
 * 4 Kb buffer can hold maximum of 32 IPC transfers, which means we can
 * have a max payload of 3968 bytes (= 32 x 124 payload).
 */
#घोषणा LOADER_SHIM_IPC_BUF_SIZE		3968

/**
 * क्रमागत ish_loader_commands -	ISH loader host commands.
 * LOADER_CMD_XFER_QUERY	Query the Shim firmware loader क्रम
 *				capabilities
 * LOADER_CMD_XFER_FRAGMENT	Transfer one firmware image fragment at a
 *				समय. The command may be executed
 *				multiple बार until the entire firmware
 *				image is करोwnloaded to SRAM.
 * LOADER_CMD_START		Start executing the मुख्य firmware.
 */
क्रमागत ish_loader_commands अणु
	LOADER_CMD_XFER_QUERY = 0,
	LOADER_CMD_XFER_FRAGMENT,
	LOADER_CMD_START,
पूर्ण;

/* Command bit mask */
#घोषणा	CMD_MASK				GENMASK(6, 0)
#घोषणा	IS_RESPONSE				BIT(7)

/*
 * ISH firmware max delay क्रम one transmit failure is 1 Hz,
 * and firmware will retry 2 बार, so 3 Hz is used क्रम समयout.
 */
#घोषणा ISHTP_SEND_TIMEOUT			(3 * HZ)

/*
 * Loader transfer modes:
 *
 * LOADER_XFER_MODE_ISHTP mode uses the existing ISH-TP mechanism to
 * transfer data. This may use IPC or DMA अगर supported in firmware.
 * The buffer size is limited to 4 Kb by the IPC/ISH-TP protocol क्रम
 * both IPC & DMA (legacy).
 *
 * LOADER_XFER_MODE_सूचीECT_DMA - firmware loading is a bit dअगरferent
 * from the sensor data streaming. Here we करोwnload a large (300+ Kb)
 * image directly to ISH SRAM memory. There is limited benefit of
 * DMA'ing 300 Kb image in 4 Kb chucks limit. Hence, we पूर्णांकroduce
 * this "direct dma" mode, where we करो not use ISH-TP क्रम DMA, but
 * instead manage the DMA directly in kernel driver and Shim firmware
 * loader (allocate buffer, अवरोध in chucks and transfer). This allows
 * to overcome 4 Kb limit, and optimize the data flow path in firmware.
 */
#घोषणा LOADER_XFER_MODE_सूचीECT_DMA		BIT(0)
#घोषणा LOADER_XFER_MODE_ISHTP			BIT(1)

/* ISH Transport Loader client unique GUID */
अटल स्थिर guid_t loader_ishtp_guid =
	GUID_INIT(0xc804d06a, 0x55bd, 0x4ea7,
		  0xad, 0xed, 0x1e, 0x31, 0x22, 0x8c, 0x76, 0xdc);

#घोषणा खाताNAME_SIZE				256

/*
 * The firmware loading latency will be minimum अगर we can DMA the
 * entire ISH firmware image in one go. This requires that we allocate
 * a large DMA buffer in kernel, which could be problematic on some
 * platक्रमms. So here we limit the DMA buffer size via a module_param.
 * We शेष to 4 pages, but a customer can set it to higher limit अगर
 * deemed appropriate क्रम his platक्रमm.
 */
अटल पूर्णांक dma_buf_size_limit = 4 * PAGE_SIZE;

/**
 * काष्ठा loader_msg_hdr - Header क्रम ISH Loader commands.
 * @command:		LOADER_CMD* commands. Bit 7 is the response.
 * @status:		Command response status. Non 0, is error
 *			condition.
 *
 * This काष्ठाure is used as header क्रम every command/data sent/received
 * between Host driver and ISH Shim firmware loader.
 */
काष्ठा loader_msg_hdr अणु
	u8 command;
	u8 reserved[2];
	u8 status;
पूर्ण __packed;

काष्ठा loader_xfer_query अणु
	काष्ठा loader_msg_hdr hdr;
	u32 image_size;
पूर्ण __packed;

काष्ठा ish_fw_version अणु
	u16 major;
	u16 minor;
	u16 hotfix;
	u16 build;
पूर्ण __packed;

जोड़ loader_version अणु
	u32 value;
	काष्ठा अणु
		u8 major;
		u8 minor;
		u8 hotfix;
		u8 build;
	पूर्ण;
पूर्ण __packed;

काष्ठा loader_capability अणु
	u32 max_fw_image_size;
	u32 xfer_mode;
	u32 max_dma_buf_size; /* only क्रम dma mode, multiples of cacheline */
पूर्ण __packed;

काष्ठा shim_fw_info अणु
	काष्ठा ish_fw_version ish_fw_version;
	u32 protocol_version;
	जोड़ loader_version ldr_version;
	काष्ठा loader_capability ldr_capability;
पूर्ण __packed;

काष्ठा loader_xfer_query_response अणु
	काष्ठा loader_msg_hdr hdr;
	काष्ठा shim_fw_info fw_info;
पूर्ण __packed;

काष्ठा loader_xfer_fragment अणु
	काष्ठा loader_msg_hdr hdr;
	u32 xfer_mode;
	u32 offset;
	u32 size;
	u32 is_last;
पूर्ण __packed;

काष्ठा loader_xfer_ipc_fragment अणु
	काष्ठा loader_xfer_fragment fragment;
	u8 data[] ____cacheline_aligned; /* variable length payload here */
पूर्ण __packed;

काष्ठा loader_xfer_dma_fragment अणु
	काष्ठा loader_xfer_fragment fragment;
	u64 ddr_phys_addr;
पूर्ण __packed;

काष्ठा loader_start अणु
	काष्ठा loader_msg_hdr hdr;
पूर्ण __packed;

/**
 * काष्ठा response_info - Encapsulate firmware response related
 *			inक्रमmation क्रम passing between function
 *			loader_cl_send() and process_recv() callback.
 * @data		Copy the data received from firmware here.
 * @max_size		Max size allocated क्रम the @data buffer. If the
 *			received data exceeds this value, we log an
 *			error.
 * @size		Actual size of data received from firmware.
 * @error		Returns 0 क्रम success, negative error code क्रम a
 *			failure in function process_recv().
 * @received		Set to true on receiving a valid firmware
 *			response to host command
 * @रुको_queue		Wait queue क्रम Host firmware loading where the
 *			client sends message to ISH firmware and रुकोs
 *			क्रम response
 */
काष्ठा response_info अणु
	व्योम *data;
	माप_प्रकार max_size;
	माप_प्रकार size;
	पूर्णांक error;
	bool received;
	रुको_queue_head_t रुको_queue;
पूर्ण;

/**
 * काष्ठा ishtp_cl_data - Encapsulate per ISH-TP Client Data.
 * @work_ishtp_reset:	Work queue क्रम reset handling.
 * @work_fw_load:	Work queue क्रम host firmware loading.
 * @flag_retry		Flag क्रम indicating host firmware loading should
 *			be retried.
 * @retry_count		Count the number of retries.
 *
 * This काष्ठाure is used to store data per client.
 */
काष्ठा ishtp_cl_data अणु
	काष्ठा ishtp_cl *loader_ishtp_cl;
	काष्ठा ishtp_cl_device *cl_device;

	/*
	 * Used क्रम passing firmware response inक्रमmation between
	 * loader_cl_send() and process_recv() callback.
	 */
	काष्ठा response_info response;

	काष्ठा work_काष्ठा work_ishtp_reset;
	काष्ठा work_काष्ठा work_fw_load;

	/*
	 * In certain failure scenrios, it makes sense to reset the ISH
	 * subप्रणाली and retry Host firmware loading (e.g. bad message
	 * packet, ENOMEM, etc.). On the other hand, failures due to
	 * protocol mismatch, etc., are not recoverable. We करो not
	 * retry them.
	 *
	 * If set, the flag indicates that we should re-try the
	 * particular failure.
	 */
	bool flag_retry;
	पूर्णांक retry_count;
पूर्ण;

#घोषणा IPC_FRAGMENT_DATA_PREAMBLE				\
	दुरत्व(काष्ठा loader_xfer_ipc_fragment, data)

#घोषणा cl_data_to_dev(client_data) ishtp_device((client_data)->cl_device)

/**
 * get_firmware_variant() - Gets the filename of firmware image to be
 *			loaded based on platक्रमm variant.
 * @client_data		Client data instance.
 * @filename		Returns firmware filename.
 *
 * Queries the firmware-name device property string.
 *
 * Return: 0 क्रम success, negative error code क्रम failure.
 */
अटल पूर्णांक get_firmware_variant(काष्ठा ishtp_cl_data *client_data,
				अक्षर *filename)
अणु
	पूर्णांक rv;
	स्थिर अक्षर *val;
	काष्ठा device *devc = ishtp_get_pci_device(client_data->cl_device);

	rv = device_property_पढ़ो_string(devc, "firmware-name", &val);
	अगर (rv < 0) अणु
		dev_err(devc,
			"Error: ISH firmware-name device property required\n");
		वापस rv;
	पूर्ण
	वापस snम_लिखो(filename, खाताNAME_SIZE, "intel/%s", val);
पूर्ण

/**
 * loader_cl_send()	Send message from host to firmware
 * @client_data:	Client data instance
 * @out_msg		Message buffer to be sent to firmware
 * @out_size		Size of out going message
 * @in_msg		Message buffer where the incoming data copied.
 *			This buffer is allocated by calling
 * @in_size		Max size of incoming message
 *
 * Return: Number of bytes copied in the in_msg on success, negative
 * error code on failure.
 */
अटल पूर्णांक loader_cl_send(काष्ठा ishtp_cl_data *client_data,
			  u8 *out_msg, माप_प्रकार out_size,
			  u8 *in_msg, माप_प्रकार in_size)
अणु
	पूर्णांक rv;
	काष्ठा loader_msg_hdr *out_hdr = (काष्ठा loader_msg_hdr *)out_msg;
	काष्ठा ishtp_cl *loader_ishtp_cl = client_data->loader_ishtp_cl;

	dev_dbg(cl_data_to_dev(client_data),
		"%s: command=%02lx is_response=%u status=%02x\n",
		__func__,
		out_hdr->command & CMD_MASK,
		out_hdr->command & IS_RESPONSE ? 1 : 0,
		out_hdr->status);

	/* Setup in coming buffer & size */
	client_data->response.data = in_msg;
	client_data->response.max_size = in_size;
	client_data->response.error = 0;
	client_data->response.received = false;

	rv = ishtp_cl_send(loader_ishtp_cl, out_msg, out_size);
	अगर (rv < 0) अणु
		dev_err(cl_data_to_dev(client_data),
			"ishtp_cl_send error %d\n", rv);
		वापस rv;
	पूर्ण

	रुको_event_पूर्णांकerruptible_समयout(client_data->response.रुको_queue,
					 client_data->response.received,
					 ISHTP_SEND_TIMEOUT);
	अगर (!client_data->response.received) अणु
		dev_err(cl_data_to_dev(client_data),
			"Timed out for response to command=%02lx",
			out_hdr->command & CMD_MASK);
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (client_data->response.error < 0)
		वापस client_data->response.error;

	वापस client_data->response.size;
पूर्ण

/**
 * process_recv() -	Receive and parse incoming packet
 * @loader_ishtp_cl:	Client instance to get stats
 * @rb_in_proc:		ISH received message buffer
 *
 * Parse the incoming packet. If it is a response packet then it will
 * update received and wake up the caller रुकोing to क्रम the response.
 */
अटल व्योम process_recv(काष्ठा ishtp_cl *loader_ishtp_cl,
			 काष्ठा ishtp_cl_rb *rb_in_proc)
अणु
	काष्ठा loader_msg_hdr *hdr;
	माप_प्रकार data_len = rb_in_proc->buf_idx;
	काष्ठा ishtp_cl_data *client_data =
		ishtp_get_client_data(loader_ishtp_cl);

	/* Sanity check */
	अगर (!client_data->response.data) अणु
		dev_err(cl_data_to_dev(client_data),
			"Receiving buffer is null. Should be allocated by calling function\n");
		client_data->response.error = -EINVAL;
		जाओ end;
	पूर्ण

	अगर (client_data->response.received) अणु
		dev_err(cl_data_to_dev(client_data),
			"Previous firmware message not yet processed\n");
		client_data->response.error = -EINVAL;
		जाओ end;
	पूर्ण
	/*
	 * All firmware messages have a header. Check buffer size
	 * beक्रमe accessing elements inside.
	 */
	अगर (!rb_in_proc->buffer.data) अणु
		dev_warn(cl_data_to_dev(client_data),
			 "rb_in_proc->buffer.data returned null");
		client_data->response.error = -EBADMSG;
		जाओ end;
	पूर्ण

	अगर (data_len < माप(काष्ठा loader_msg_hdr)) अणु
		dev_err(cl_data_to_dev(client_data),
			"data size %zu is less than header %zu\n",
			data_len, माप(काष्ठा loader_msg_hdr));
		client_data->response.error = -EMSGSIZE;
		जाओ end;
	पूर्ण

	hdr = (काष्ठा loader_msg_hdr *)rb_in_proc->buffer.data;

	dev_dbg(cl_data_to_dev(client_data),
		"%s: command=%02lx is_response=%u status=%02x\n",
		__func__,
		hdr->command & CMD_MASK,
		hdr->command & IS_RESPONSE ? 1 : 0,
		hdr->status);

	अगर (((hdr->command & CMD_MASK) != LOADER_CMD_XFER_QUERY) &&
	    ((hdr->command & CMD_MASK) != LOADER_CMD_XFER_FRAGMENT) &&
	    ((hdr->command & CMD_MASK) != LOADER_CMD_START)) अणु
		dev_err(cl_data_to_dev(client_data),
			"Invalid command=%02lx\n",
			hdr->command & CMD_MASK);
		client_data->response.error = -EPROTO;
		जाओ end;
	पूर्ण

	अगर (data_len > client_data->response.max_size) अणु
		dev_err(cl_data_to_dev(client_data),
			"Received buffer size %zu is larger than allocated buffer %zu\n",
			data_len, client_data->response.max_size);
		client_data->response.error = -EMSGSIZE;
		जाओ end;
	पूर्ण

	/* We expect only "response" messages from firmware */
	अगर (!(hdr->command & IS_RESPONSE)) अणु
		dev_err(cl_data_to_dev(client_data),
			"Invalid response to command\n");
		client_data->response.error = -EIO;
		जाओ end;
	पूर्ण

	अगर (hdr->status) अणु
		dev_err(cl_data_to_dev(client_data),
			"Loader returned status %d\n",
			hdr->status);
		client_data->response.error = -EIO;
		जाओ end;
	पूर्ण

	/* Update the actual received buffer size */
	client_data->response.size = data_len;

	/*
	 * Copy the buffer received in firmware response क्रम the
	 * calling thपढ़ो.
	 */
	स_नकल(client_data->response.data,
	       rb_in_proc->buffer.data, data_len);

	/* Set flag beक्रमe waking up the caller */
	client_data->response.received = true;

end:
	/* Free the buffer */
	ishtp_cl_io_rb_recycle(rb_in_proc);
	rb_in_proc = शून्य;

	/* Wake the calling thपढ़ो */
	wake_up_पूर्णांकerruptible(&client_data->response.रुको_queue);
पूर्ण

/**
 * loader_cl_event_cb() - bus driver callback क्रम incoming message
 * @device:		Poपूर्णांकer to the ishtp client device क्रम which this
 *			message is targeted
 *
 * Remove the packet from the list and process the message by calling
 * process_recv
 */
अटल व्योम loader_cl_event_cb(काष्ठा ishtp_cl_device *cl_device)
अणु
	काष्ठा ishtp_cl_rb *rb_in_proc;
	काष्ठा ishtp_cl	*loader_ishtp_cl = ishtp_get_drvdata(cl_device);

	जबतक ((rb_in_proc = ishtp_cl_rx_get_rb(loader_ishtp_cl)) != शून्य) अणु
		/* Process the data packet from firmware */
		process_recv(loader_ishtp_cl, rb_in_proc);
	पूर्ण
पूर्ण

/**
 * ish_query_loader_prop() -  Query ISH Shim firmware loader
 * @client_data:	Client data instance
 * @fw:			Poiner to firmware data काष्ठा in host memory
 * @fw_info:		Loader firmware properties
 *
 * This function queries the ISH Shim firmware loader क्रम capabilities.
 *
 * Return: 0 क्रम success, negative error code क्रम failure.
 */
अटल पूर्णांक ish_query_loader_prop(काष्ठा ishtp_cl_data *client_data,
				 स्थिर काष्ठा firmware *fw,
				 काष्ठा shim_fw_info *fw_info)
अणु
	पूर्णांक rv;
	काष्ठा loader_xfer_query ldr_xfer_query;
	काष्ठा loader_xfer_query_response ldr_xfer_query_resp;

	स_रखो(&ldr_xfer_query, 0, माप(ldr_xfer_query));
	ldr_xfer_query.hdr.command = LOADER_CMD_XFER_QUERY;
	ldr_xfer_query.image_size = fw->size;
	rv = loader_cl_send(client_data,
			    (u8 *)&ldr_xfer_query,
			    माप(ldr_xfer_query),
			    (u8 *)&ldr_xfer_query_resp,
			    माप(ldr_xfer_query_resp));
	अगर (rv < 0) अणु
		client_data->flag_retry = true;
		*fw_info = (काष्ठा shim_fw_info)अणुपूर्ण;
		वापस rv;
	पूर्ण

	/* On success, the वापस value is the received buffer size */
	अगर (rv != माप(काष्ठा loader_xfer_query_response)) अणु
		dev_err(cl_data_to_dev(client_data),
			"data size %d is not equal to size of loader_xfer_query_response %zu\n",
			rv, माप(काष्ठा loader_xfer_query_response));
		client_data->flag_retry = true;
		*fw_info = (काष्ठा shim_fw_info)अणुपूर्ण;
		वापस -EMSGSIZE;
	पूर्ण

	/* Save fw_info क्रम use outside this function */
	*fw_info = ldr_xfer_query_resp.fw_info;

	/* Loader firmware properties */
	dev_dbg(cl_data_to_dev(client_data),
		"ish_fw_version: major=%d minor=%d hotfix=%d build=%d protocol_version=0x%x loader_version=%d\n",
		fw_info->ish_fw_version.major,
		fw_info->ish_fw_version.minor,
		fw_info->ish_fw_version.hotfix,
		fw_info->ish_fw_version.build,
		fw_info->protocol_version,
		fw_info->ldr_version.value);

	dev_dbg(cl_data_to_dev(client_data),
		"loader_capability: max_fw_image_size=0x%x xfer_mode=%d max_dma_buf_size=0x%x dma_buf_size_limit=0x%x\n",
		fw_info->ldr_capability.max_fw_image_size,
		fw_info->ldr_capability.xfer_mode,
		fw_info->ldr_capability.max_dma_buf_size,
		dma_buf_size_limit);

	/* Sanity checks */
	अगर (fw_info->ldr_capability.max_fw_image_size < fw->size) अणु
		dev_err(cl_data_to_dev(client_data),
			"ISH firmware size %zu is greater than Shim firmware loader max supported %d\n",
			fw->size,
			fw_info->ldr_capability.max_fw_image_size);
		वापस -ENOSPC;
	पूर्ण

	/* For DMA the buffer size should be multiple of cacheline size */
	अगर ((fw_info->ldr_capability.xfer_mode & LOADER_XFER_MODE_सूचीECT_DMA) &&
	    (fw_info->ldr_capability.max_dma_buf_size % L1_CACHE_BYTES)) अणु
		dev_err(cl_data_to_dev(client_data),
			"Shim firmware loader buffer size %d should be multiple of cacheline\n",
			fw_info->ldr_capability.max_dma_buf_size);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ish_fw_xfer_ishtp()	Loads ISH firmware using ishtp पूर्णांकerface
 * @client_data:	Client data instance
 * @fw:			Poपूर्णांकer to firmware data काष्ठा in host memory
 *
 * This function uses ISH-TP to transfer ISH firmware from host to
 * ISH SRAM. Lower layers may use IPC or DMA depending on firmware
 * support.
 *
 * Return: 0 क्रम success, negative error code क्रम failure.
 */
अटल पूर्णांक ish_fw_xfer_ishtp(काष्ठा ishtp_cl_data *client_data,
			     स्थिर काष्ठा firmware *fw)
अणु
	पूर्णांक rv;
	u32 fragment_offset, fragment_size, payload_max_size;
	काष्ठा loader_xfer_ipc_fragment *ldr_xfer_ipc_frag;
	काष्ठा loader_msg_hdr ldr_xfer_ipc_ack;

	payload_max_size =
		LOADER_SHIM_IPC_BUF_SIZE - IPC_FRAGMENT_DATA_PREAMBLE;

	ldr_xfer_ipc_frag = kzalloc(LOADER_SHIM_IPC_BUF_SIZE, GFP_KERNEL);
	अगर (!ldr_xfer_ipc_frag) अणु
		client_data->flag_retry = true;
		वापस -ENOMEM;
	पूर्ण

	ldr_xfer_ipc_frag->fragment.hdr.command = LOADER_CMD_XFER_FRAGMENT;
	ldr_xfer_ipc_frag->fragment.xfer_mode = LOADER_XFER_MODE_ISHTP;

	/* Break the firmware image पूर्णांकo fragments and send as ISH-TP payload */
	fragment_offset = 0;
	जबतक (fragment_offset < fw->size) अणु
		अगर (fragment_offset + payload_max_size < fw->size) अणु
			fragment_size = payload_max_size;
			ldr_xfer_ipc_frag->fragment.is_last = 0;
		पूर्ण अन्यथा अणु
			fragment_size = fw->size - fragment_offset;
			ldr_xfer_ipc_frag->fragment.is_last = 1;
		पूर्ण

		ldr_xfer_ipc_frag->fragment.offset = fragment_offset;
		ldr_xfer_ipc_frag->fragment.size = fragment_size;
		स_नकल(ldr_xfer_ipc_frag->data,
		       &fw->data[fragment_offset],
		       fragment_size);

		dev_dbg(cl_data_to_dev(client_data),
			"xfer_mode=ipc offset=0x%08x size=0x%08x is_last=%d\n",
			ldr_xfer_ipc_frag->fragment.offset,
			ldr_xfer_ipc_frag->fragment.size,
			ldr_xfer_ipc_frag->fragment.is_last);

		rv = loader_cl_send(client_data,
				    (u8 *)ldr_xfer_ipc_frag,
				    IPC_FRAGMENT_DATA_PREAMBLE + fragment_size,
				    (u8 *)&ldr_xfer_ipc_ack,
				    माप(ldr_xfer_ipc_ack));
		अगर (rv < 0) अणु
			client_data->flag_retry = true;
			जाओ end_err_resp_buf_release;
		पूर्ण

		fragment_offset += fragment_size;
	पूर्ण

	kमुक्त(ldr_xfer_ipc_frag);
	वापस 0;

end_err_resp_buf_release:
	/* Free ISH buffer अगर not करोne alपढ़ोy, in error हाल */
	kमुक्त(ldr_xfer_ipc_frag);
	वापस rv;
पूर्ण

/**
 * ish_fw_xfer_direct_dma() - Loads ISH firmware using direct dma
 * @client_data:	Client data instance
 * @fw:			Poपूर्णांकer to firmware data काष्ठा in host memory
 * @fw_info:		Loader firmware properties
 *
 * Host firmware load is a unique हाल where we need to करोwnload
 * a large firmware image (200+ Kb). This function implements
 * direct DMA transfer in kernel and ISH firmware. This allows
 * us to overcome the ISH-TP 4 Kb limit, and allows us to DMA
 * directly to ISH UMA at location of choice.
 * Function depends on corresponding support in ISH firmware.
 *
 * Return: 0 क्रम success, negative error code क्रम failure.
 */
अटल पूर्णांक ish_fw_xfer_direct_dma(काष्ठा ishtp_cl_data *client_data,
				  स्थिर काष्ठा firmware *fw,
				  स्थिर काष्ठा shim_fw_info fw_info)
अणु
	पूर्णांक rv;
	व्योम *dma_buf;
	dma_addr_t dma_buf_phy;
	u32 fragment_offset, fragment_size, payload_max_size;
	काष्ठा loader_msg_hdr ldr_xfer_dma_frag_ack;
	काष्ठा loader_xfer_dma_fragment ldr_xfer_dma_frag;
	काष्ठा device *devc = ishtp_get_pci_device(client_data->cl_device);
	u32 shim_fw_buf_size =
		fw_info.ldr_capability.max_dma_buf_size;

	/*
	 * payload_max_size should be set to minimum of
	 *  (1) Size of firmware to be loaded,
	 *  (2) Max DMA buffer size supported by Shim firmware,
	 *  (3) DMA buffer size limit set by boot_param dma_buf_size_limit.
	 */
	payload_max_size = min3(fw->size,
				(माप_प्रकार)shim_fw_buf_size,
				(माप_प्रकार)dma_buf_size_limit);

	/*
	 * Buffer size should be multiple of cacheline size
	 * अगर it's not, select the previous cacheline boundary.
	 */
	payload_max_size &= ~(L1_CACHE_BYTES - 1);

	dma_buf = kदो_स्मृति(payload_max_size, GFP_KERNEL | GFP_DMA32);
	अगर (!dma_buf) अणु
		client_data->flag_retry = true;
		वापस -ENOMEM;
	पूर्ण

	dma_buf_phy = dma_map_single(devc, dma_buf, payload_max_size,
				     DMA_TO_DEVICE);
	अगर (dma_mapping_error(devc, dma_buf_phy)) अणु
		dev_err(cl_data_to_dev(client_data), "DMA map failed\n");
		client_data->flag_retry = true;
		rv = -ENOMEM;
		जाओ end_err_dma_buf_release;
	पूर्ण

	ldr_xfer_dma_frag.fragment.hdr.command = LOADER_CMD_XFER_FRAGMENT;
	ldr_xfer_dma_frag.fragment.xfer_mode = LOADER_XFER_MODE_सूचीECT_DMA;
	ldr_xfer_dma_frag.ddr_phys_addr = (u64)dma_buf_phy;

	/* Send the firmware image in chucks of payload_max_size */
	fragment_offset = 0;
	जबतक (fragment_offset < fw->size) अणु
		अगर (fragment_offset + payload_max_size < fw->size) अणु
			fragment_size = payload_max_size;
			ldr_xfer_dma_frag.fragment.is_last = 0;
		पूर्ण अन्यथा अणु
			fragment_size = fw->size - fragment_offset;
			ldr_xfer_dma_frag.fragment.is_last = 1;
		पूर्ण

		ldr_xfer_dma_frag.fragment.offset = fragment_offset;
		ldr_xfer_dma_frag.fragment.size = fragment_size;
		स_नकल(dma_buf, &fw->data[fragment_offset], fragment_size);

		dma_sync_single_क्रम_device(devc, dma_buf_phy,
					   payload_max_size,
					   DMA_TO_DEVICE);

		/*
		 * Flush cache here because the dma_sync_single_क्रम_device()
		 * करोes not करो क्रम x86.
		 */
		clflush_cache_range(dma_buf, payload_max_size);

		dev_dbg(cl_data_to_dev(client_data),
			"xfer_mode=dma offset=0x%08x size=0x%x is_last=%d ddr_phys_addr=0x%016llx\n",
			ldr_xfer_dma_frag.fragment.offset,
			ldr_xfer_dma_frag.fragment.size,
			ldr_xfer_dma_frag.fragment.is_last,
			ldr_xfer_dma_frag.ddr_phys_addr);

		rv = loader_cl_send(client_data,
				    (u8 *)&ldr_xfer_dma_frag,
				    माप(ldr_xfer_dma_frag),
				    (u8 *)&ldr_xfer_dma_frag_ack,
				    माप(ldr_xfer_dma_frag_ack));
		अगर (rv < 0) अणु
			client_data->flag_retry = true;
			जाओ end_err_resp_buf_release;
		पूर्ण

		fragment_offset += fragment_size;
	पूर्ण

	dma_unmap_single(devc, dma_buf_phy, payload_max_size, DMA_TO_DEVICE);
	kमुक्त(dma_buf);
	वापस 0;

end_err_resp_buf_release:
	/* Free ISH buffer अगर not करोne alपढ़ोy, in error हाल */
	dma_unmap_single(devc, dma_buf_phy, payload_max_size, DMA_TO_DEVICE);
end_err_dma_buf_release:
	kमुक्त(dma_buf);
	वापस rv;
पूर्ण

/**
 * ish_fw_start()	Start executing ISH मुख्य firmware
 * @client_data:	client data instance
 *
 * This function sends message to Shim firmware loader to start
 * the execution of ISH मुख्य firmware.
 *
 * Return: 0 क्रम success, negative error code क्रम failure.
 */
अटल पूर्णांक ish_fw_start(काष्ठा ishtp_cl_data *client_data)
अणु
	काष्ठा loader_start ldr_start;
	काष्ठा loader_msg_hdr ldr_start_ack;

	स_रखो(&ldr_start, 0, माप(ldr_start));
	ldr_start.hdr.command = LOADER_CMD_START;
	वापस loader_cl_send(client_data,
			    (u8 *)&ldr_start,
			    माप(ldr_start),
			    (u8 *)&ldr_start_ack,
			    माप(ldr_start_ack));
पूर्ण

/**
 * load_fw_from_host()	Loads ISH firmware from host
 * @client_data:	Client data instance
 *
 * This function loads the ISH firmware to ISH SRAM and starts execution
 *
 * Return: 0 क्रम success, negative error code क्रम failure.
 */
अटल पूर्णांक load_fw_from_host(काष्ठा ishtp_cl_data *client_data)
अणु
	पूर्णांक rv;
	u32 xfer_mode;
	अक्षर *filename;
	स्थिर काष्ठा firmware *fw;
	काष्ठा shim_fw_info fw_info;
	काष्ठा ishtp_cl *loader_ishtp_cl = client_data->loader_ishtp_cl;

	client_data->flag_retry = false;

	filename = kzalloc(खाताNAME_SIZE, GFP_KERNEL);
	अगर (!filename) अणु
		client_data->flag_retry = true;
		rv = -ENOMEM;
		जाओ end_error;
	पूर्ण

	/* Get filename of the ISH firmware to be loaded */
	rv = get_firmware_variant(client_data, filename);
	अगर (rv < 0)
		जाओ end_err_filename_buf_release;

	rv = request_firmware(&fw, filename, cl_data_to_dev(client_data));
	अगर (rv < 0)
		जाओ end_err_filename_buf_release;

	/* Step 1: Query Shim firmware loader properties */

	rv = ish_query_loader_prop(client_data, fw, &fw_info);
	अगर (rv < 0)
		जाओ end_err_fw_release;

	/* Step 2: Send the मुख्य firmware image to be loaded, to ISH SRAM */

	xfer_mode = fw_info.ldr_capability.xfer_mode;
	अगर (xfer_mode & LOADER_XFER_MODE_सूचीECT_DMA) अणु
		rv = ish_fw_xfer_direct_dma(client_data, fw, fw_info);
	पूर्ण अन्यथा अगर (xfer_mode & LOADER_XFER_MODE_ISHTP) अणु
		rv = ish_fw_xfer_ishtp(client_data, fw);
	पूर्ण अन्यथा अणु
		dev_err(cl_data_to_dev(client_data),
			"No transfer mode selected in firmware\n");
		rv = -EINVAL;
	पूर्ण
	अगर (rv < 0)
		जाओ end_err_fw_release;

	/* Step 3: Start ISH मुख्य firmware exeuction */

	rv = ish_fw_start(client_data);
	अगर (rv < 0)
		जाओ end_err_fw_release;

	release_firmware(fw);
	dev_info(cl_data_to_dev(client_data), "ISH firmware %s loaded\n",
		 filename);
	kमुक्त(filename);
	वापस 0;

end_err_fw_release:
	release_firmware(fw);
end_err_filename_buf_release:
	kमुक्त(filename);
end_error:
	/* Keep a count of retries, and give up after 3 attempts */
	अगर (client_data->flag_retry &&
	    client_data->retry_count++ < MAX_LOAD_ATTEMPTS) अणु
		dev_warn(cl_data_to_dev(client_data),
			 "ISH host firmware load failed %d. Resetting ISH, and trying again..\n",
			 rv);
		ish_hw_reset(ishtp_get_ishtp_device(loader_ishtp_cl));
	पूर्ण अन्यथा अणु
		dev_err(cl_data_to_dev(client_data),
			"ISH host firmware load failed %d\n", rv);
	पूर्ण
	वापस rv;
पूर्ण

अटल व्योम load_fw_from_host_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ishtp_cl_data *client_data;

	client_data = container_of(work, काष्ठा ishtp_cl_data,
				   work_fw_load);
	load_fw_from_host(client_data);
पूर्ण

/**
 * loader_init() -	Init function क्रम ISH-TP client
 * @loader_ishtp_cl:	ISH-TP client instance
 * @reset:		true अगर called क्रम init after reset
 *
 * Return: 0 क्रम success, negative error code क्रम failure
 */
अटल पूर्णांक loader_init(काष्ठा ishtp_cl *loader_ishtp_cl, पूर्णांक reset)
अणु
	पूर्णांक rv;
	काष्ठा ishtp_fw_client *fw_client;
	काष्ठा ishtp_cl_data *client_data =
		ishtp_get_client_data(loader_ishtp_cl);

	dev_dbg(cl_data_to_dev(client_data), "reset flag: %d\n", reset);

	rv = ishtp_cl_link(loader_ishtp_cl);
	अगर (rv < 0) अणु
		dev_err(cl_data_to_dev(client_data), "ishtp_cl_link failed\n");
		वापस rv;
	पूर्ण

	/* Connect to firmware client */
	ishtp_set_tx_ring_size(loader_ishtp_cl, LOADER_CL_TX_RING_SIZE);
	ishtp_set_rx_ring_size(loader_ishtp_cl, LOADER_CL_RX_RING_SIZE);

	fw_client =
		ishtp_fw_cl_get_client(ishtp_get_ishtp_device(loader_ishtp_cl),
				       &loader_ishtp_guid);
	अगर (!fw_client) अणु
		dev_err(cl_data_to_dev(client_data),
			"ISH client uuid not found\n");
		rv = -ENOENT;
		जाओ err_cl_unlink;
	पूर्ण

	ishtp_cl_set_fw_client_id(loader_ishtp_cl,
				  ishtp_get_fw_client_id(fw_client));
	ishtp_set_connection_state(loader_ishtp_cl, ISHTP_CL_CONNECTING);

	rv = ishtp_cl_connect(loader_ishtp_cl);
	अगर (rv < 0) अणु
		dev_err(cl_data_to_dev(client_data), "Client connect fail\n");
		जाओ err_cl_unlink;
	पूर्ण

	dev_dbg(cl_data_to_dev(client_data), "Client connected\n");

	ishtp_रेजिस्टर_event_cb(client_data->cl_device, loader_cl_event_cb);

	वापस 0;

err_cl_unlink:
	ishtp_cl_unlink(loader_ishtp_cl);
	वापस rv;
पूर्ण

अटल व्योम loader_deinit(काष्ठा ishtp_cl *loader_ishtp_cl)
अणु
	ishtp_set_connection_state(loader_ishtp_cl, ISHTP_CL_DISCONNECTING);
	ishtp_cl_disconnect(loader_ishtp_cl);
	ishtp_cl_unlink(loader_ishtp_cl);
	ishtp_cl_flush_queues(loader_ishtp_cl);

	/* Disband and मुक्त all Tx and Rx client-level rings */
	ishtp_cl_मुक्त(loader_ishtp_cl);
पूर्ण

अटल व्योम reset_handler(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक rv;
	काष्ठा ishtp_cl_data *client_data;
	काष्ठा ishtp_cl *loader_ishtp_cl;
	काष्ठा ishtp_cl_device *cl_device;

	client_data = container_of(work, काष्ठा ishtp_cl_data,
				   work_ishtp_reset);

	loader_ishtp_cl = client_data->loader_ishtp_cl;
	cl_device = client_data->cl_device;

	/* Unlink, flush queues & start again */
	ishtp_cl_unlink(loader_ishtp_cl);
	ishtp_cl_flush_queues(loader_ishtp_cl);
	ishtp_cl_मुक्त(loader_ishtp_cl);

	loader_ishtp_cl = ishtp_cl_allocate(cl_device);
	अगर (!loader_ishtp_cl)
		वापस;

	ishtp_set_drvdata(cl_device, loader_ishtp_cl);
	ishtp_set_client_data(loader_ishtp_cl, client_data);
	client_data->loader_ishtp_cl = loader_ishtp_cl;
	client_data->cl_device = cl_device;

	rv = loader_init(loader_ishtp_cl, 1);
	अगर (rv < 0) अणु
		dev_err(ishtp_device(cl_device), "Reset Failed\n");
		वापस;
	पूर्ण

	/* ISH firmware loading from host */
	load_fw_from_host(client_data);
पूर्ण

/**
 * loader_ishtp_cl_probe() - ISH-TP client driver probe
 * @cl_device:		ISH-TP client device instance
 *
 * This function माला_लो called on device create on ISH-TP bus
 *
 * Return: 0 क्रम success, negative error code क्रम failure
 */
अटल पूर्णांक loader_ishtp_cl_probe(काष्ठा ishtp_cl_device *cl_device)
अणु
	काष्ठा ishtp_cl *loader_ishtp_cl;
	काष्ठा ishtp_cl_data *client_data;
	पूर्णांक rv;

	client_data = devm_kzalloc(ishtp_device(cl_device),
				   माप(*client_data),
				   GFP_KERNEL);
	अगर (!client_data)
		वापस -ENOMEM;

	loader_ishtp_cl = ishtp_cl_allocate(cl_device);
	अगर (!loader_ishtp_cl)
		वापस -ENOMEM;

	ishtp_set_drvdata(cl_device, loader_ishtp_cl);
	ishtp_set_client_data(loader_ishtp_cl, client_data);
	client_data->loader_ishtp_cl = loader_ishtp_cl;
	client_data->cl_device = cl_device;

	init_रुकोqueue_head(&client_data->response.रुको_queue);

	INIT_WORK(&client_data->work_ishtp_reset,
		  reset_handler);
	INIT_WORK(&client_data->work_fw_load,
		  load_fw_from_host_handler);

	rv = loader_init(loader_ishtp_cl, 0);
	अगर (rv < 0) अणु
		ishtp_cl_मुक्त(loader_ishtp_cl);
		वापस rv;
	पूर्ण
	ishtp_get_device(cl_device);

	client_data->retry_count = 0;

	/* ISH firmware loading from host */
	schedule_work(&client_data->work_fw_load);

	वापस 0;
पूर्ण

/**
 * loader_ishtp_cl_हटाओ() - ISH-TP client driver हटाओ
 * @cl_device:		ISH-TP client device instance
 *
 * This function माला_लो called on device हटाओ on ISH-TP bus
 *
 * Return: 0
 */
अटल पूर्णांक loader_ishtp_cl_हटाओ(काष्ठा ishtp_cl_device *cl_device)
अणु
	काष्ठा ishtp_cl_data *client_data;
	काष्ठा ishtp_cl	*loader_ishtp_cl = ishtp_get_drvdata(cl_device);

	client_data = ishtp_get_client_data(loader_ishtp_cl);

	/*
	 * The sequence of the following two cancel_work_sync() is
	 * important. The work_fw_load can in turn schedue
	 * work_ishtp_reset, so first cancel work_fw_load then
	 * cancel work_ishtp_reset.
	 */
	cancel_work_sync(&client_data->work_fw_load);
	cancel_work_sync(&client_data->work_ishtp_reset);
	loader_deinit(loader_ishtp_cl);
	ishtp_put_device(cl_device);

	वापस 0;
पूर्ण

/**
 * loader_ishtp_cl_reset() - ISH-TP client driver reset
 * @cl_device:		ISH-TP client device instance
 *
 * This function माला_लो called on device reset on ISH-TP bus
 *
 * Return: 0
 */
अटल पूर्णांक loader_ishtp_cl_reset(काष्ठा ishtp_cl_device *cl_device)
अणु
	काष्ठा ishtp_cl_data *client_data;
	काष्ठा ishtp_cl	*loader_ishtp_cl = ishtp_get_drvdata(cl_device);

	client_data = ishtp_get_client_data(loader_ishtp_cl);

	schedule_work(&client_data->work_ishtp_reset);

	वापस 0;
पूर्ण

अटल काष्ठा ishtp_cl_driver	loader_ishtp_cl_driver = अणु
	.name = "ish-loader",
	.guid = &loader_ishtp_guid,
	.probe = loader_ishtp_cl_probe,
	.हटाओ = loader_ishtp_cl_हटाओ,
	.reset = loader_ishtp_cl_reset,
पूर्ण;

अटल पूर्णांक __init ish_loader_init(व्योम)
अणु
	वापस ishtp_cl_driver_रेजिस्टर(&loader_ishtp_cl_driver, THIS_MODULE);
पूर्ण

अटल व्योम __निकास ish_loader_निकास(व्योम)
अणु
	ishtp_cl_driver_unरेजिस्टर(&loader_ishtp_cl_driver);
पूर्ण

late_initcall(ish_loader_init);
module_निकास(ish_loader_निकास);

module_param(dma_buf_size_limit, पूर्णांक, 0644);
MODULE_PARM_DESC(dma_buf_size_limit, "Limit the DMA buf size to this value in bytes");

MODULE_DESCRIPTION("ISH ISH-TP Host firmware Loader Client Driver");
MODULE_AUTHOR("Rushikesh S Kadam <rushikesh.s.kadam@intel.com>");

MODULE_LICENSE("GPL v2");
MODULE_ALIAS("ishtp:*");
