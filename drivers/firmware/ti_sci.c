<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Texas Instruments System Control Interface Protocol Driver
 *
 * Copyright (C) 2015-2016 Texas Instruments Incorporated - https://www.ti.com/
 *	Nishanth Menon
 */

#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/slab.h>
#समावेश <linux/soc/ti/ti-msgmgr.h>
#समावेश <linux/soc/ti/ti_sci_protocol.h>
#समावेश <linux/reboot.h>

#समावेश "ti_sci.h"

/* List of all TI SCI devices active in प्रणाली */
अटल LIST_HEAD(ti_sci_list);
/* Protection क्रम the entire list */
अटल DEFINE_MUTEX(ti_sci_list_mutex);

/**
 * काष्ठा ti_sci_xfer - Structure representing a message flow
 * @tx_message:	Transmit message
 * @rx_len:	Receive message length
 * @xfer_buf:	Pपुनः_स्मृतिated buffer to store receive message
 *		Since we work with request-ACK protocol, we can
 *		reuse the same buffer क्रम the rx path as we
 *		use क्रम the tx path.
 * @करोne:	completion event
 */
काष्ठा ti_sci_xfer अणु
	काष्ठा ti_msgmgr_message tx_message;
	u8 rx_len;
	u8 *xfer_buf;
	काष्ठा completion करोne;
पूर्ण;

/**
 * काष्ठा ti_sci_xfers_info - Structure to manage transfer inक्रमmation
 * @sem_xfer_count:	Counting Semaphore क्रम managing max simultaneous
 *			Messages.
 * @xfer_block:		Pपुनः_स्मृतिated Message array
 * @xfer_alloc_table:	Biपंचांगap table क्रम allocated messages.
 *			Index of this biपंचांगap table is also used क्रम message
 *			sequence identअगरier.
 * @xfer_lock:		Protection क्रम message allocation
 */
काष्ठा ti_sci_xfers_info अणु
	काष्ठा semaphore sem_xfer_count;
	काष्ठा ti_sci_xfer *xfer_block;
	अचिन्हित दीर्घ *xfer_alloc_table;
	/* protect transfer allocation */
	spinlock_t xfer_lock;
पूर्ण;

/**
 * काष्ठा ti_sci_desc - Description of SoC पूर्णांकegration
 * @शेष_host_id:	Host identअगरier representing the compute entity
 * @max_rx_समयout_ms:	Timeout क्रम communication with SoC (in Milliseconds)
 * @max_msgs: Maximum number of messages that can be pending
 *		  simultaneously in the प्रणाली
 * @max_msg_size: Maximum size of data per message that can be handled.
 */
काष्ठा ti_sci_desc अणु
	u8 शेष_host_id;
	पूर्णांक max_rx_समयout_ms;
	पूर्णांक max_msgs;
	पूर्णांक max_msg_size;
पूर्ण;

/**
 * काष्ठा ti_sci_info - Structure representing a TI SCI instance
 * @dev:	Device poपूर्णांकer
 * @desc:	SoC description क्रम this instance
 * @nb:	Reboot Notअगरier block
 * @d:		Debugfs file entry
 * @debug_region: Memory region where the debug message are available
 * @debug_region_size: Debug region size
 * @debug_buffer: Buffer allocated to copy debug messages.
 * @handle:	Instance of TI SCI handle to send to clients.
 * @cl:		Mailbox Client
 * @chan_tx:	Transmit mailbox channel
 * @chan_rx:	Receive mailbox channel
 * @minfo:	Message info
 * @node:	list head
 * @host_id:	Host ID
 * @users:	Number of users of this instance
 */
काष्ठा ti_sci_info अणु
	काष्ठा device *dev;
	काष्ठा notअगरier_block nb;
	स्थिर काष्ठा ti_sci_desc *desc;
	काष्ठा dentry *d;
	व्योम __iomem *debug_region;
	अक्षर *debug_buffer;
	माप_प्रकार debug_region_size;
	काष्ठा ti_sci_handle handle;
	काष्ठा mbox_client cl;
	काष्ठा mbox_chan *chan_tx;
	काष्ठा mbox_chan *chan_rx;
	काष्ठा ti_sci_xfers_info minfo;
	काष्ठा list_head node;
	u8 host_id;
	/* रक्षित by ti_sci_list_mutex */
	पूर्णांक users;

पूर्ण;

#घोषणा cl_to_ti_sci_info(c)	container_of(c, काष्ठा ti_sci_info, cl)
#घोषणा handle_to_ti_sci_info(h) container_of(h, काष्ठा ti_sci_info, handle)
#घोषणा reboot_to_ti_sci_info(n) container_of(n, काष्ठा ti_sci_info, nb)

#अगर_घोषित CONFIG_DEBUG_FS

/**
 * ti_sci_debug_show() - Helper to dump the debug log
 * @s:	sequence file poपूर्णांकer
 * @unused:	unused.
 *
 * Return: 0
 */
अटल पूर्णांक ti_sci_debug_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा ti_sci_info *info = s->निजी;

	स_नकल_fromio(info->debug_buffer, info->debug_region,
		      info->debug_region_size);
	/*
	 * We करोn't trust firmware to leave शून्य terminated last byte (hence
	 * we have allocated 1 extra 0 byte). Since we cannot guarantee any
	 * specअगरic data क्रमmat क्रम debug messages, We just present the data
	 * in the buffer as is - we expect the messages to be self explanatory.
	 */
	seq_माला_दो(s, info->debug_buffer);
	वापस 0;
पूर्ण

/* Provide the log file operations पूर्णांकerface*/
DEFINE_SHOW_ATTRIBUTE(ti_sci_debug);

/**
 * ti_sci_debugfs_create() - Create log debug file
 * @pdev:	platक्रमm device poपूर्णांकer
 * @info:	Poपूर्णांकer to SCI entity inक्रमmation
 *
 * Return: 0 अगर all went fine, अन्यथा corresponding error.
 */
अटल पूर्णांक ti_sci_debugfs_create(काष्ठा platक्रमm_device *pdev,
				 काष्ठा ti_sci_info *info)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	अक्षर debug_name[50] = "ti_sci_debug@";

	/* Debug region is optional */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
					   "debug_messages");
	info->debug_region = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(info->debug_region))
		वापस 0;
	info->debug_region_size = resource_size(res);

	info->debug_buffer = devm_kसुस्मृति(dev, info->debug_region_size + 1,
					  माप(अक्षर), GFP_KERNEL);
	अगर (!info->debug_buffer)
		वापस -ENOMEM;
	/* Setup शून्य termination */
	info->debug_buffer[info->debug_region_size] = 0;

	info->d = debugfs_create_file(म_जोड़न(debug_name, dev_name(dev),
					      माप(debug_name) -
					      माप("ti_sci_debug@")),
				      0444, शून्य, info, &ti_sci_debug_fops);
	अगर (IS_ERR(info->d))
		वापस PTR_ERR(info->d);

	dev_dbg(dev, "Debug region => %p, size = %zu bytes, resource: %pr\n",
		info->debug_region, info->debug_region_size, res);
	वापस 0;
पूर्ण

/**
 * ti_sci_debugfs_destroy() - clean up log debug file
 * @pdev:	platक्रमm device poपूर्णांकer
 * @info:	Poपूर्णांकer to SCI entity inक्रमmation
 */
अटल व्योम ti_sci_debugfs_destroy(काष्ठा platक्रमm_device *pdev,
				   काष्ठा ti_sci_info *info)
अणु
	अगर (IS_ERR(info->debug_region))
		वापस;

	debugfs_हटाओ(info->d);
पूर्ण
#अन्यथा /* CONFIG_DEBUG_FS */
अटल अंतरभूत पूर्णांक ti_sci_debugfs_create(काष्ठा platक्रमm_device *dev,
					काष्ठा ti_sci_info *info)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ti_sci_debugfs_destroy(काष्ठा platक्रमm_device *dev,
					  काष्ठा ti_sci_info *info)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

/**
 * ti_sci_dump_header_dbg() - Helper to dump a message header.
 * @dev:	Device poपूर्णांकer corresponding to the SCI entity
 * @hdr:	poपूर्णांकer to header.
 */
अटल अंतरभूत व्योम ti_sci_dump_header_dbg(काष्ठा device *dev,
					  काष्ठा ti_sci_msg_hdr *hdr)
अणु
	dev_dbg(dev, "MSGHDR:type=0x%04x host=0x%02x seq=0x%02x flags=0x%08x\n",
		hdr->type, hdr->host, hdr->seq, hdr->flags);
पूर्ण

/**
 * ti_sci_rx_callback() - mailbox client callback क्रम receive messages
 * @cl:	client poपूर्णांकer
 * @m:	mailbox message
 *
 * Processes one received message to appropriate transfer inक्रमmation and
 * संकेतs completion of the transfer.
 *
 * NOTE: This function will be invoked in IRQ context, hence should be
 * as optimal as possible.
 */
अटल व्योम ti_sci_rx_callback(काष्ठा mbox_client *cl, व्योम *m)
अणु
	काष्ठा ti_sci_info *info = cl_to_ti_sci_info(cl);
	काष्ठा device *dev = info->dev;
	काष्ठा ti_sci_xfers_info *minfo = &info->minfo;
	काष्ठा ti_msgmgr_message *mbox_msg = m;
	काष्ठा ti_sci_msg_hdr *hdr = (काष्ठा ti_sci_msg_hdr *)mbox_msg->buf;
	काष्ठा ti_sci_xfer *xfer;
	u8 xfer_id;

	xfer_id = hdr->seq;

	/*
	 * Are we even expecting this?
	 * NOTE: barriers were implicit in locks used क्रम modअगरying the biपंचांगap
	 */
	अगर (!test_bit(xfer_id, minfo->xfer_alloc_table)) अणु
		dev_err(dev, "Message for %d is not expected!\n", xfer_id);
		वापस;
	पूर्ण

	xfer = &minfo->xfer_block[xfer_id];

	/* Is the message of valid length? */
	अगर (mbox_msg->len > info->desc->max_msg_size) अणु
		dev_err(dev, "Unable to handle %zu xfer(max %d)\n",
			mbox_msg->len, info->desc->max_msg_size);
		ti_sci_dump_header_dbg(dev, hdr);
		वापस;
	पूर्ण
	अगर (mbox_msg->len < xfer->rx_len) अणु
		dev_err(dev, "Recv xfer %zu < expected %d length\n",
			mbox_msg->len, xfer->rx_len);
		ti_sci_dump_header_dbg(dev, hdr);
		वापस;
	पूर्ण

	ti_sci_dump_header_dbg(dev, hdr);
	/* Take a copy to the rx buffer.. */
	स_नकल(xfer->xfer_buf, mbox_msg->buf, xfer->rx_len);
	complete(&xfer->करोne);
पूर्ण

/**
 * ti_sci_get_one_xfer() - Allocate one message
 * @info:	Poपूर्णांकer to SCI entity inक्रमmation
 * @msg_type:	Message type
 * @msg_flags:	Flag to set क्रम the message
 * @tx_message_size: transmit message size
 * @rx_message_size: receive message size
 *
 * Helper function which is used by various command functions that are
 * exposed to clients of this driver क्रम allocating a message traffic event.
 *
 * This function can sleep depending on pending requests alपढ़ोy in the प्रणाली
 * क्रम the SCI entity. Further, this also holds a spinlock to मुख्यtain पूर्णांकegrity
 * of पूर्णांकernal data काष्ठाures.
 *
 * Return: 0 अगर all went fine, अन्यथा corresponding error.
 */
अटल काष्ठा ti_sci_xfer *ti_sci_get_one_xfer(काष्ठा ti_sci_info *info,
					       u16 msg_type, u32 msg_flags,
					       माप_प्रकार tx_message_size,
					       माप_प्रकार rx_message_size)
अणु
	काष्ठा ti_sci_xfers_info *minfo = &info->minfo;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा ti_sci_msg_hdr *hdr;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ bit_pos;
	u8 xfer_id;
	पूर्णांक ret;
	पूर्णांक समयout;

	/* Ensure we have sane transfer sizes */
	अगर (rx_message_size > info->desc->max_msg_size ||
	    tx_message_size > info->desc->max_msg_size ||
	    rx_message_size < माप(*hdr) || tx_message_size < माप(*hdr))
		वापस ERR_PTR(-दुस्फल);

	/*
	 * Ensure we have only controlled number of pending messages.
	 * Ideally, we might just have to रुको a single message, be
	 * conservative and रुको 5 बार that..
	 */
	समयout = msecs_to_jअगरfies(info->desc->max_rx_समयout_ms) * 5;
	ret = करोwn_समयout(&minfo->sem_xfer_count, समयout);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	/* Keep the locked section as small as possible */
	spin_lock_irqsave(&minfo->xfer_lock, flags);
	bit_pos = find_first_zero_bit(minfo->xfer_alloc_table,
				      info->desc->max_msgs);
	set_bit(bit_pos, minfo->xfer_alloc_table);
	spin_unlock_irqrestore(&minfo->xfer_lock, flags);

	/*
	 * We alपढ़ोy ensured in probe that we can have max messages that can
	 * fit in  hdr.seq - NOTE: this improves access latencies
	 * to predictable O(1) access, BUT, it खोलोs us to risk अगर
	 * remote misbehaves with corrupted message sequence responses.
	 * If that happens, we are going to be messed up anyways..
	 */
	xfer_id = (u8)bit_pos;

	xfer = &minfo->xfer_block[xfer_id];

	hdr = (काष्ठा ti_sci_msg_hdr *)xfer->tx_message.buf;
	xfer->tx_message.len = tx_message_size;
	xfer->rx_len = (u8)rx_message_size;

	reinit_completion(&xfer->करोne);

	hdr->seq = xfer_id;
	hdr->type = msg_type;
	hdr->host = info->host_id;
	hdr->flags = msg_flags;

	वापस xfer;
पूर्ण

/**
 * ti_sci_put_one_xfer() - Release a message
 * @minfo:	transfer info poपूर्णांकer
 * @xfer:	message that was reserved by ti_sci_get_one_xfer
 *
 * This holds a spinlock to मुख्यtain पूर्णांकegrity of पूर्णांकernal data काष्ठाures.
 */
अटल व्योम ti_sci_put_one_xfer(काष्ठा ti_sci_xfers_info *minfo,
				काष्ठा ti_sci_xfer *xfer)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ti_sci_msg_hdr *hdr;
	u8 xfer_id;

	hdr = (काष्ठा ti_sci_msg_hdr *)xfer->tx_message.buf;
	xfer_id = hdr->seq;

	/*
	 * Keep the locked section as small as possible
	 * NOTE: we might escape with smp_mb and no lock here..
	 * but just be conservative and symmetric.
	 */
	spin_lock_irqsave(&minfo->xfer_lock, flags);
	clear_bit(xfer_id, minfo->xfer_alloc_table);
	spin_unlock_irqrestore(&minfo->xfer_lock, flags);

	/* Increment the count क्रम the next user to get through */
	up(&minfo->sem_xfer_count);
पूर्ण

/**
 * ti_sci_करो_xfer() - Do one transfer
 * @info:	Poपूर्णांकer to SCI entity inक्रमmation
 * @xfer:	Transfer to initiate and रुको क्रम response
 *
 * Return: -ETIMEDOUT in हाल of no response, अगर transmit error,
 *	   वापस corresponding error, अन्यथा अगर all goes well,
 *	   वापस 0.
 */
अटल अंतरभूत पूर्णांक ti_sci_करो_xfer(काष्ठा ti_sci_info *info,
				 काष्ठा ti_sci_xfer *xfer)
अणु
	पूर्णांक ret;
	पूर्णांक समयout;
	काष्ठा device *dev = info->dev;

	ret = mbox_send_message(info->chan_tx, &xfer->tx_message);
	अगर (ret < 0)
		वापस ret;

	ret = 0;

	/* And we रुको क्रम the response. */
	समयout = msecs_to_jअगरfies(info->desc->max_rx_समयout_ms);
	अगर (!रुको_क्रम_completion_समयout(&xfer->करोne, समयout)) अणु
		dev_err(dev, "Mbox timedout in resp(caller: %pS)\n",
			(व्योम *)_RET_IP_);
		ret = -ETIMEDOUT;
	पूर्ण
	/*
	 * NOTE: we might prefer not to need the mailbox ticker to manage the
	 * transfer queueing since the protocol layer queues things by itself.
	 * Unक्रमtunately, we have to kick the mailbox framework after we have
	 * received our message.
	 */
	mbox_client_txकरोne(info->chan_tx, ret);

	वापस ret;
पूर्ण

/**
 * ti_sci_cmd_get_revision() - command to get the revision of the SCI entity
 * @info:	Poपूर्णांकer to SCI entity inक्रमmation
 *
 * Updates the SCI inक्रमmation in the पूर्णांकernal data काष्ठाure.
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल पूर्णांक ti_sci_cmd_get_revision(काष्ठा ti_sci_info *info)
अणु
	काष्ठा device *dev = info->dev;
	काष्ठा ti_sci_handle *handle = &info->handle;
	काष्ठा ti_sci_version_info *ver = &handle->version;
	काष्ठा ti_sci_msg_resp_version *rev_info;
	काष्ठा ti_sci_xfer *xfer;
	पूर्णांक ret;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_VERSION,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(काष्ठा ti_sci_msg_hdr),
				   माप(*rev_info));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message alloc failed(%d)\n", ret);
		वापस ret;
	पूर्ण

	rev_info = (काष्ठा ti_sci_msg_resp_version *)xfer->xfer_buf;

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "Mbox send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	ver->abi_major = rev_info->abi_major;
	ver->abi_minor = rev_info->abi_minor;
	ver->firmware_revision = rev_info->firmware_revision;
	म_नकलन(ver->firmware_description, rev_info->firmware_description,
		माप(ver->firmware_description));

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);
	वापस ret;
पूर्ण

/**
 * ti_sci_is_response_ack() - Generic ACK/NACK message checkup
 * @r:	poपूर्णांकer to response buffer
 *
 * Return: true अगर the response was an ACK, अन्यथा वापसs false.
 */
अटल अंतरभूत bool ti_sci_is_response_ack(व्योम *r)
अणु
	काष्ठा ti_sci_msg_hdr *hdr = r;

	वापस hdr->flags & TI_SCI_FLAG_RESP_GENERIC_ACK ? true : false;
पूर्ण

/**
 * ti_sci_set_device_state() - Set device state helper
 * @handle:	poपूर्णांकer to TI SCI handle
 * @id:		Device identअगरier
 * @flags:	flags to setup क्रम the device
 * @state:	State to move the device to
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 */
अटल पूर्णांक ti_sci_set_device_state(स्थिर काष्ठा ti_sci_handle *handle,
				   u32 id, u32 flags, u8 state)
अणु
	काष्ठा ti_sci_info *info;
	काष्ठा ti_sci_msg_req_set_device_state *req;
	काष्ठा ti_sci_msg_hdr *resp;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);
	अगर (!handle)
		वापस -EINVAL;

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_SET_DEVICE_STATE,
				   flags | TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message alloc failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_req_set_device_state *)xfer->xfer_buf;
	req->id = id;
	req->state = state;

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "Mbox send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_hdr *)xfer->xfer_buf;

	ret = ti_sci_is_response_ack(resp) ? 0 : -ENODEV;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);

	वापस ret;
पूर्ण

/**
 * ti_sci_get_device_state() - Get device state helper
 * @handle:	Handle to the device
 * @id:		Device Identअगरier
 * @clcnt:	Poपूर्णांकer to Context Loss Count
 * @resets:	poपूर्णांकer to resets
 * @p_state:	poपूर्णांकer to p_state
 * @c_state:	poपूर्णांकer to c_state
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल पूर्णांक ti_sci_get_device_state(स्थिर काष्ठा ti_sci_handle *handle,
				   u32 id,  u32 *clcnt,  u32 *resets,
				    u8 *p_state,  u8 *c_state)
अणु
	काष्ठा ti_sci_info *info;
	काष्ठा ti_sci_msg_req_get_device_state *req;
	काष्ठा ti_sci_msg_resp_get_device_state *resp;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);
	अगर (!handle)
		वापस -EINVAL;

	अगर (!clcnt && !resets && !p_state && !c_state)
		वापस -EINVAL;

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_GET_DEVICE_STATE,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message alloc failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_req_get_device_state *)xfer->xfer_buf;
	req->id = id;

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "Mbox send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_resp_get_device_state *)xfer->xfer_buf;
	अगर (!ti_sci_is_response_ack(resp)) अणु
		ret = -ENODEV;
		जाओ fail;
	पूर्ण

	अगर (clcnt)
		*clcnt = resp->context_loss_count;
	अगर (resets)
		*resets = resp->resets;
	अगर (p_state)
		*p_state = resp->programmed_state;
	अगर (c_state)
		*c_state = resp->current_state;
fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);

	वापस ret;
पूर्ण

/**
 * ti_sci_cmd_get_device() - command to request क्रम device managed by TISCI
 *			     that can be shared with other hosts.
 * @handle:	Poपूर्णांकer to TISCI handle as retrieved by *ti_sci_get_handle
 * @id:		Device Identअगरier
 *
 * Request क्रम the device - NOTE: the client MUST मुख्यtain पूर्णांकegrity of
 * usage count by balancing get_device with put_device. No refcounting is
 * managed by driver क्रम that purpose.
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल पूर्णांक ti_sci_cmd_get_device(स्थिर काष्ठा ti_sci_handle *handle, u32 id)
अणु
	वापस ti_sci_set_device_state(handle, id, 0,
				       MSG_DEVICE_SW_STATE_ON);
पूर्ण

/**
 * ti_sci_cmd_get_device_exclusive() - command to request क्रम device managed by
 *				       TISCI that is exclusively owned by the
 *				       requesting host.
 * @handle:	Poपूर्णांकer to TISCI handle as retrieved by *ti_sci_get_handle
 * @id:		Device Identअगरier
 *
 * Request क्रम the device - NOTE: the client MUST मुख्यtain पूर्णांकegrity of
 * usage count by balancing get_device with put_device. No refcounting is
 * managed by driver क्रम that purpose.
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल पूर्णांक ti_sci_cmd_get_device_exclusive(स्थिर काष्ठा ti_sci_handle *handle,
					   u32 id)
अणु
	वापस ti_sci_set_device_state(handle, id,
				       MSG_FLAG_DEVICE_EXCLUSIVE,
				       MSG_DEVICE_SW_STATE_ON);
पूर्ण

/**
 * ti_sci_cmd_idle_device() - Command to idle a device managed by TISCI
 * @handle:	Poपूर्णांकer to TISCI handle as retrieved by *ti_sci_get_handle
 * @id:		Device Identअगरier
 *
 * Request क्रम the device - NOTE: the client MUST मुख्यtain पूर्णांकegrity of
 * usage count by balancing get_device with put_device. No refcounting is
 * managed by driver क्रम that purpose.
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल पूर्णांक ti_sci_cmd_idle_device(स्थिर काष्ठा ti_sci_handle *handle, u32 id)
अणु
	वापस ti_sci_set_device_state(handle, id, 0,
				       MSG_DEVICE_SW_STATE_RETENTION);
पूर्ण

/**
 * ti_sci_cmd_idle_device_exclusive() - Command to idle a device managed by
 *					TISCI that is exclusively owned by
 *					requesting host.
 * @handle:	Poपूर्णांकer to TISCI handle as retrieved by *ti_sci_get_handle
 * @id:		Device Identअगरier
 *
 * Request क्रम the device - NOTE: the client MUST मुख्यtain पूर्णांकegrity of
 * usage count by balancing get_device with put_device. No refcounting is
 * managed by driver क्रम that purpose.
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल पूर्णांक ti_sci_cmd_idle_device_exclusive(स्थिर काष्ठा ti_sci_handle *handle,
					    u32 id)
अणु
	वापस ti_sci_set_device_state(handle, id,
				       MSG_FLAG_DEVICE_EXCLUSIVE,
				       MSG_DEVICE_SW_STATE_RETENTION);
पूर्ण

/**
 * ti_sci_cmd_put_device() - command to release a device managed by TISCI
 * @handle:	Poपूर्णांकer to TISCI handle as retrieved by *ti_sci_get_handle
 * @id:		Device Identअगरier
 *
 * Request क्रम the device - NOTE: the client MUST मुख्यtain पूर्णांकegrity of
 * usage count by balancing get_device with put_device. No refcounting is
 * managed by driver क्रम that purpose.
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल पूर्णांक ti_sci_cmd_put_device(स्थिर काष्ठा ti_sci_handle *handle, u32 id)
अणु
	वापस ti_sci_set_device_state(handle, id,
				       0, MSG_DEVICE_SW_STATE_AUTO_OFF);
पूर्ण

/**
 * ti_sci_cmd_dev_is_valid() - Is the device valid
 * @handle:	Poपूर्णांकer to TISCI handle as retrieved by *ti_sci_get_handle
 * @id:		Device Identअगरier
 *
 * Return: 0 अगर all went fine and the device ID is valid, अन्यथा वापस
 * appropriate error.
 */
अटल पूर्णांक ti_sci_cmd_dev_is_valid(स्थिर काष्ठा ti_sci_handle *handle, u32 id)
अणु
	u8 unused;

	/* check the device state which will also tell us अगर the ID is valid */
	वापस ti_sci_get_device_state(handle, id, शून्य, शून्य, शून्य, &unused);
पूर्ण

/**
 * ti_sci_cmd_dev_get_clcnt() - Get context loss counter
 * @handle:	Poपूर्णांकer to TISCI handle
 * @id:		Device Identअगरier
 * @count:	Poपूर्णांकer to Context Loss counter to populate
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल पूर्णांक ti_sci_cmd_dev_get_clcnt(स्थिर काष्ठा ti_sci_handle *handle, u32 id,
				    u32 *count)
अणु
	वापस ti_sci_get_device_state(handle, id, count, शून्य, शून्य, शून्य);
पूर्ण

/**
 * ti_sci_cmd_dev_is_idle() - Check अगर the device is requested to be idle
 * @handle:	Poपूर्णांकer to TISCI handle
 * @id:		Device Identअगरier
 * @r_state:	true अगर requested to be idle
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल पूर्णांक ti_sci_cmd_dev_is_idle(स्थिर काष्ठा ti_sci_handle *handle, u32 id,
				  bool *r_state)
अणु
	पूर्णांक ret;
	u8 state;

	अगर (!r_state)
		वापस -EINVAL;

	ret = ti_sci_get_device_state(handle, id, शून्य, शून्य, &state, शून्य);
	अगर (ret)
		वापस ret;

	*r_state = (state == MSG_DEVICE_SW_STATE_RETENTION);

	वापस 0;
पूर्ण

/**
 * ti_sci_cmd_dev_is_stop() - Check अगर the device is requested to be stopped
 * @handle:	Poपूर्णांकer to TISCI handle
 * @id:		Device Identअगरier
 * @r_state:	true अगर requested to be stopped
 * @curr_state:	true अगर currently stopped.
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल पूर्णांक ti_sci_cmd_dev_is_stop(स्थिर काष्ठा ti_sci_handle *handle, u32 id,
				  bool *r_state,  bool *curr_state)
अणु
	पूर्णांक ret;
	u8 p_state, c_state;

	अगर (!r_state && !curr_state)
		वापस -EINVAL;

	ret =
	    ti_sci_get_device_state(handle, id, शून्य, शून्य, &p_state, &c_state);
	अगर (ret)
		वापस ret;

	अगर (r_state)
		*r_state = (p_state == MSG_DEVICE_SW_STATE_AUTO_OFF);
	अगर (curr_state)
		*curr_state = (c_state == MSG_DEVICE_HW_STATE_OFF);

	वापस 0;
पूर्ण

/**
 * ti_sci_cmd_dev_is_on() - Check अगर the device is requested to be ON
 * @handle:	Poपूर्णांकer to TISCI handle
 * @id:		Device Identअगरier
 * @r_state:	true अगर requested to be ON
 * @curr_state:	true अगर currently ON and active
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल पूर्णांक ti_sci_cmd_dev_is_on(स्थिर काष्ठा ti_sci_handle *handle, u32 id,
				bool *r_state,  bool *curr_state)
अणु
	पूर्णांक ret;
	u8 p_state, c_state;

	अगर (!r_state && !curr_state)
		वापस -EINVAL;

	ret =
	    ti_sci_get_device_state(handle, id, शून्य, शून्य, &p_state, &c_state);
	अगर (ret)
		वापस ret;

	अगर (r_state)
		*r_state = (p_state == MSG_DEVICE_SW_STATE_ON);
	अगर (curr_state)
		*curr_state = (c_state == MSG_DEVICE_HW_STATE_ON);

	वापस 0;
पूर्ण

/**
 * ti_sci_cmd_dev_is_trans() - Check अगर the device is currently transitioning
 * @handle:	Poपूर्णांकer to TISCI handle
 * @id:		Device Identअगरier
 * @curr_state:	true अगर currently transitioning.
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल पूर्णांक ti_sci_cmd_dev_is_trans(स्थिर काष्ठा ti_sci_handle *handle, u32 id,
				   bool *curr_state)
अणु
	पूर्णांक ret;
	u8 state;

	अगर (!curr_state)
		वापस -EINVAL;

	ret = ti_sci_get_device_state(handle, id, शून्य, शून्य, शून्य, &state);
	अगर (ret)
		वापस ret;

	*curr_state = (state == MSG_DEVICE_HW_STATE_TRANS);

	वापस 0;
पूर्ण

/**
 * ti_sci_cmd_set_device_resets() - command to set resets क्रम device managed
 *				    by TISCI
 * @handle:	Poपूर्णांकer to TISCI handle as retrieved by *ti_sci_get_handle
 * @id:		Device Identअगरier
 * @reset_state: Device specअगरic reset bit field
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल पूर्णांक ti_sci_cmd_set_device_resets(स्थिर काष्ठा ti_sci_handle *handle,
					u32 id, u32 reset_state)
अणु
	काष्ठा ti_sci_info *info;
	काष्ठा ti_sci_msg_req_set_device_resets *req;
	काष्ठा ti_sci_msg_hdr *resp;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);
	अगर (!handle)
		वापस -EINVAL;

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_SET_DEVICE_RESETS,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message alloc failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_req_set_device_resets *)xfer->xfer_buf;
	req->id = id;
	req->resets = reset_state;

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "Mbox send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_hdr *)xfer->xfer_buf;

	ret = ti_sci_is_response_ack(resp) ? 0 : -ENODEV;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);

	वापस ret;
पूर्ण

/**
 * ti_sci_cmd_get_device_resets() - Get reset state क्रम device managed
 *				    by TISCI
 * @handle:		Poपूर्णांकer to TISCI handle
 * @id:			Device Identअगरier
 * @reset_state:	Poपूर्णांकer to reset state to populate
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल पूर्णांक ti_sci_cmd_get_device_resets(स्थिर काष्ठा ti_sci_handle *handle,
					u32 id, u32 *reset_state)
अणु
	वापस ti_sci_get_device_state(handle, id, शून्य, reset_state, शून्य,
				       शून्य);
पूर्ण

/**
 * ti_sci_set_घड़ी_state() - Set घड़ी state helper
 * @handle:	poपूर्णांकer to TI SCI handle
 * @dev_id:	Device identअगरier this request is क्रम
 * @clk_id:	Clock identअगरier क्रम the device क्रम this request.
 *		Each device has it's own set of घड़ी inमाला_दो. This indexes
 *		which घड़ी input to modअगरy.
 * @flags:	Header flags as needed
 * @state:	State to request क्रम the घड़ी.
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 */
अटल पूर्णांक ti_sci_set_घड़ी_state(स्थिर काष्ठा ti_sci_handle *handle,
				  u32 dev_id, u32 clk_id,
				  u32 flags, u8 state)
अणु
	काष्ठा ti_sci_info *info;
	काष्ठा ti_sci_msg_req_set_घड़ी_state *req;
	काष्ठा ti_sci_msg_hdr *resp;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);
	अगर (!handle)
		वापस -EINVAL;

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_SET_CLOCK_STATE,
				   flags | TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message alloc failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_req_set_घड़ी_state *)xfer->xfer_buf;
	req->dev_id = dev_id;
	अगर (clk_id < 255) अणु
		req->clk_id = clk_id;
	पूर्ण अन्यथा अणु
		req->clk_id = 255;
		req->clk_id_32 = clk_id;
	पूर्ण
	req->request_state = state;

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "Mbox send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_hdr *)xfer->xfer_buf;

	ret = ti_sci_is_response_ack(resp) ? 0 : -ENODEV;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);

	वापस ret;
पूर्ण

/**
 * ti_sci_cmd_get_घड़ी_state() - Get घड़ी state helper
 * @handle:	poपूर्णांकer to TI SCI handle
 * @dev_id:	Device identअगरier this request is क्रम
 * @clk_id:	Clock identअगरier क्रम the device क्रम this request.
 *		Each device has it's own set of घड़ी inमाला_दो. This indexes
 *		which घड़ी input to modअगरy.
 * @programmed_state:	State requested क्रम घड़ी to move to
 * @current_state:	State that the घड़ी is currently in
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 */
अटल पूर्णांक ti_sci_cmd_get_घड़ी_state(स्थिर काष्ठा ti_sci_handle *handle,
				      u32 dev_id, u32 clk_id,
				      u8 *programmed_state, u8 *current_state)
अणु
	काष्ठा ti_sci_info *info;
	काष्ठा ti_sci_msg_req_get_घड़ी_state *req;
	काष्ठा ti_sci_msg_resp_get_घड़ी_state *resp;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);
	अगर (!handle)
		वापस -EINVAL;

	अगर (!programmed_state && !current_state)
		वापस -EINVAL;

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_GET_CLOCK_STATE,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message alloc failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_req_get_घड़ी_state *)xfer->xfer_buf;
	req->dev_id = dev_id;
	अगर (clk_id < 255) अणु
		req->clk_id = clk_id;
	पूर्ण अन्यथा अणु
		req->clk_id = 255;
		req->clk_id_32 = clk_id;
	पूर्ण

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "Mbox send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_resp_get_घड़ी_state *)xfer->xfer_buf;

	अगर (!ti_sci_is_response_ack(resp)) अणु
		ret = -ENODEV;
		जाओ fail;
	पूर्ण

	अगर (programmed_state)
		*programmed_state = resp->programmed_state;
	अगर (current_state)
		*current_state = resp->current_state;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);

	वापस ret;
पूर्ण

/**
 * ti_sci_cmd_get_घड़ी() - Get control of a घड़ी from TI SCI
 * @handle:	poपूर्णांकer to TI SCI handle
 * @dev_id:	Device identअगरier this request is क्रम
 * @clk_id:	Clock identअगरier क्रम the device क्रम this request.
 *		Each device has it's own set of घड़ी inमाला_दो. This indexes
 *		which घड़ी input to modअगरy.
 * @needs_ssc: 'true' if Spread Spectrum clock is desired, else 'false'
 * @can_change_freq: 'true' if frequency change is desired, else 'false'
 * @enable_input_term: 'true' if input termination is desired, else 'false'
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 */
अटल पूर्णांक ti_sci_cmd_get_घड़ी(स्थिर काष्ठा ti_sci_handle *handle, u32 dev_id,
				u32 clk_id, bool needs_ssc,
				bool can_change_freq, bool enable_input_term)
अणु
	u32 flags = 0;

	flags |= needs_ssc ? MSG_FLAG_CLOCK_ALLOW_SSC : 0;
	flags |= can_change_freq ? MSG_FLAG_CLOCK_ALLOW_FREQ_CHANGE : 0;
	flags |= enable_input_term ? MSG_FLAG_CLOCK_INPUT_TERM : 0;

	वापस ti_sci_set_घड़ी_state(handle, dev_id, clk_id, flags,
				      MSG_CLOCK_SW_STATE_REQ);
पूर्ण

/**
 * ti_sci_cmd_idle_घड़ी() - Idle a घड़ी which is in our control
 * @handle:	poपूर्णांकer to TI SCI handle
 * @dev_id:	Device identअगरier this request is क्रम
 * @clk_id:	Clock identअगरier क्रम the device क्रम this request.
 *		Each device has it's own set of घड़ी inमाला_दो. This indexes
 *		which घड़ी input to modअगरy.
 *
 * NOTE: This घड़ी must have been requested by get_घड़ी previously.
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 */
अटल पूर्णांक ti_sci_cmd_idle_घड़ी(स्थिर काष्ठा ti_sci_handle *handle,
				 u32 dev_id, u32 clk_id)
अणु
	वापस ti_sci_set_घड़ी_state(handle, dev_id, clk_id,
				      MSG_FLAG_CLOCK_ALLOW_FREQ_CHANGE,
				      MSG_CLOCK_SW_STATE_UNREQ);
पूर्ण

/**
 * ti_sci_cmd_put_घड़ी() - Release a घड़ी from our control back to TISCI
 * @handle:	poपूर्णांकer to TI SCI handle
 * @dev_id:	Device identअगरier this request is क्रम
 * @clk_id:	Clock identअगरier क्रम the device क्रम this request.
 *		Each device has it's own set of घड़ी inमाला_दो. This indexes
 *		which घड़ी input to modअगरy.
 *
 * NOTE: This घड़ी must have been requested by get_घड़ी previously.
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 */
अटल पूर्णांक ti_sci_cmd_put_घड़ी(स्थिर काष्ठा ti_sci_handle *handle,
				u32 dev_id, u32 clk_id)
अणु
	वापस ti_sci_set_घड़ी_state(handle, dev_id, clk_id,
				      MSG_FLAG_CLOCK_ALLOW_FREQ_CHANGE,
				      MSG_CLOCK_SW_STATE_AUTO);
पूर्ण

/**
 * ti_sci_cmd_clk_is_स्वतः() - Is the घड़ी being स्वतः managed
 * @handle:	poपूर्णांकer to TI SCI handle
 * @dev_id:	Device identअगरier this request is क्रम
 * @clk_id:	Clock identअगरier क्रम the device क्रम this request.
 *		Each device has it's own set of घड़ी inमाला_दो. This indexes
 *		which घड़ी input to modअगरy.
 * @req_state: state indicating अगर the घड़ी is स्वतः managed
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 */
अटल पूर्णांक ti_sci_cmd_clk_is_स्वतः(स्थिर काष्ठा ti_sci_handle *handle,
				  u32 dev_id, u32 clk_id, bool *req_state)
अणु
	u8 state = 0;
	पूर्णांक ret;

	अगर (!req_state)
		वापस -EINVAL;

	ret = ti_sci_cmd_get_घड़ी_state(handle, dev_id, clk_id, &state, शून्य);
	अगर (ret)
		वापस ret;

	*req_state = (state == MSG_CLOCK_SW_STATE_AUTO);
	वापस 0;
पूर्ण

/**
 * ti_sci_cmd_clk_is_on() - Is the घड़ी ON
 * @handle:	poपूर्णांकer to TI SCI handle
 * @dev_id:	Device identअगरier this request is क्रम
 * @clk_id:	Clock identअगरier क्रम the device क्रम this request.
 *		Each device has it's own set of घड़ी inमाला_दो. This indexes
 *		which घड़ी input to modअगरy.
 * @req_state: state indicating अगर the घड़ी is managed by us and enabled
 * @curr_state: state indicating अगर the घड़ी is पढ़ोy क्रम operation
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 */
अटल पूर्णांक ti_sci_cmd_clk_is_on(स्थिर काष्ठा ti_sci_handle *handle, u32 dev_id,
				u32 clk_id, bool *req_state, bool *curr_state)
अणु
	u8 c_state = 0, r_state = 0;
	पूर्णांक ret;

	अगर (!req_state && !curr_state)
		वापस -EINVAL;

	ret = ti_sci_cmd_get_घड़ी_state(handle, dev_id, clk_id,
					 &r_state, &c_state);
	अगर (ret)
		वापस ret;

	अगर (req_state)
		*req_state = (r_state == MSG_CLOCK_SW_STATE_REQ);
	अगर (curr_state)
		*curr_state = (c_state == MSG_CLOCK_HW_STATE_READY);
	वापस 0;
पूर्ण

/**
 * ti_sci_cmd_clk_is_off() - Is the घड़ी OFF
 * @handle:	poपूर्णांकer to TI SCI handle
 * @dev_id:	Device identअगरier this request is क्रम
 * @clk_id:	Clock identअगरier क्रम the device क्रम this request.
 *		Each device has it's own set of घड़ी inमाला_दो. This indexes
 *		which घड़ी input to modअगरy.
 * @req_state: state indicating अगर the घड़ी is managed by us and disabled
 * @curr_state: state indicating अगर the घड़ी is NOT पढ़ोy क्रम operation
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 */
अटल पूर्णांक ti_sci_cmd_clk_is_off(स्थिर काष्ठा ti_sci_handle *handle, u32 dev_id,
				 u32 clk_id, bool *req_state, bool *curr_state)
अणु
	u8 c_state = 0, r_state = 0;
	पूर्णांक ret;

	अगर (!req_state && !curr_state)
		वापस -EINVAL;

	ret = ti_sci_cmd_get_घड़ी_state(handle, dev_id, clk_id,
					 &r_state, &c_state);
	अगर (ret)
		वापस ret;

	अगर (req_state)
		*req_state = (r_state == MSG_CLOCK_SW_STATE_UNREQ);
	अगर (curr_state)
		*curr_state = (c_state == MSG_CLOCK_HW_STATE_NOT_READY);
	वापस 0;
पूर्ण

/**
 * ti_sci_cmd_clk_set_parent() - Set the घड़ी source of a specअगरic device घड़ी
 * @handle:	poपूर्णांकer to TI SCI handle
 * @dev_id:	Device identअगरier this request is क्रम
 * @clk_id:	Clock identअगरier क्रम the device क्रम this request.
 *		Each device has it's own set of घड़ी inमाला_दो. This indexes
 *		which घड़ी input to modअगरy.
 * @parent_id:	Parent घड़ी identअगरier to set
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 */
अटल पूर्णांक ti_sci_cmd_clk_set_parent(स्थिर काष्ठा ti_sci_handle *handle,
				     u32 dev_id, u32 clk_id, u32 parent_id)
अणु
	काष्ठा ti_sci_info *info;
	काष्ठा ti_sci_msg_req_set_घड़ी_parent *req;
	काष्ठा ti_sci_msg_hdr *resp;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);
	अगर (!handle)
		वापस -EINVAL;

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_SET_CLOCK_PARENT,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message alloc failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_req_set_घड़ी_parent *)xfer->xfer_buf;
	req->dev_id = dev_id;
	अगर (clk_id < 255) अणु
		req->clk_id = clk_id;
	पूर्ण अन्यथा अणु
		req->clk_id = 255;
		req->clk_id_32 = clk_id;
	पूर्ण
	अगर (parent_id < 255) अणु
		req->parent_id = parent_id;
	पूर्ण अन्यथा अणु
		req->parent_id = 255;
		req->parent_id_32 = parent_id;
	पूर्ण

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "Mbox send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_hdr *)xfer->xfer_buf;

	ret = ti_sci_is_response_ack(resp) ? 0 : -ENODEV;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);

	वापस ret;
पूर्ण

/**
 * ti_sci_cmd_clk_get_parent() - Get current parent घड़ी source
 * @handle:	poपूर्णांकer to TI SCI handle
 * @dev_id:	Device identअगरier this request is क्रम
 * @clk_id:	Clock identअगरier क्रम the device क्रम this request.
 *		Each device has it's own set of घड़ी inमाला_दो. This indexes
 *		which घड़ी input to modअगरy.
 * @parent_id:	Current घड़ी parent
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 */
अटल पूर्णांक ti_sci_cmd_clk_get_parent(स्थिर काष्ठा ti_sci_handle *handle,
				     u32 dev_id, u32 clk_id, u32 *parent_id)
अणु
	काष्ठा ti_sci_info *info;
	काष्ठा ti_sci_msg_req_get_घड़ी_parent *req;
	काष्ठा ti_sci_msg_resp_get_घड़ी_parent *resp;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);
	अगर (!handle || !parent_id)
		वापस -EINVAL;

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_GET_CLOCK_PARENT,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message alloc failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_req_get_घड़ी_parent *)xfer->xfer_buf;
	req->dev_id = dev_id;
	अगर (clk_id < 255) अणु
		req->clk_id = clk_id;
	पूर्ण अन्यथा अणु
		req->clk_id = 255;
		req->clk_id_32 = clk_id;
	पूर्ण

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "Mbox send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_resp_get_घड़ी_parent *)xfer->xfer_buf;

	अगर (!ti_sci_is_response_ack(resp)) अणु
		ret = -ENODEV;
	पूर्ण अन्यथा अणु
		अगर (resp->parent_id < 255)
			*parent_id = resp->parent_id;
		अन्यथा
			*parent_id = resp->parent_id_32;
	पूर्ण

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);

	वापस ret;
पूर्ण

/**
 * ti_sci_cmd_clk_get_num_parents() - Get num parents of the current clk source
 * @handle:	poपूर्णांकer to TI SCI handle
 * @dev_id:	Device identअगरier this request is क्रम
 * @clk_id:	Clock identअगरier क्रम the device क्रम this request.
 *		Each device has it's own set of घड़ी inमाला_दो. This indexes
 *		which घड़ी input to modअगरy.
 * @num_parents: Returns he number of parents to the current घड़ी.
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 */
अटल पूर्णांक ti_sci_cmd_clk_get_num_parents(स्थिर काष्ठा ti_sci_handle *handle,
					  u32 dev_id, u32 clk_id,
					  u32 *num_parents)
अणु
	काष्ठा ti_sci_info *info;
	काष्ठा ti_sci_msg_req_get_घड़ी_num_parents *req;
	काष्ठा ti_sci_msg_resp_get_घड़ी_num_parents *resp;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);
	अगर (!handle || !num_parents)
		वापस -EINVAL;

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_GET_NUM_CLOCK_PARENTS,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message alloc failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_req_get_घड़ी_num_parents *)xfer->xfer_buf;
	req->dev_id = dev_id;
	अगर (clk_id < 255) अणु
		req->clk_id = clk_id;
	पूर्ण अन्यथा अणु
		req->clk_id = 255;
		req->clk_id_32 = clk_id;
	पूर्ण

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "Mbox send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_resp_get_घड़ी_num_parents *)xfer->xfer_buf;

	अगर (!ti_sci_is_response_ack(resp)) अणु
		ret = -ENODEV;
	पूर्ण अन्यथा अणु
		अगर (resp->num_parents < 255)
			*num_parents = resp->num_parents;
		अन्यथा
			*num_parents = resp->num_parents_32;
	पूर्ण

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);

	वापस ret;
पूर्ण

/**
 * ti_sci_cmd_clk_get_match_freq() - Find a good match क्रम frequency
 * @handle:	poपूर्णांकer to TI SCI handle
 * @dev_id:	Device identअगरier this request is क्रम
 * @clk_id:	Clock identअगरier क्रम the device क्रम this request.
 *		Each device has it's own set of घड़ी inमाला_दो. This indexes
 *		which घड़ी input to modअगरy.
 * @min_freq:	The minimum allowable frequency in Hz. This is the minimum
 *		allowable programmed frequency and करोes not account क्रम घड़ी
 *		tolerances and jitter.
 * @target_freq: The target घड़ी frequency in Hz. A frequency will be
 *		processed as बंद to this target frequency as possible.
 * @max_freq:	The maximum allowable frequency in Hz. This is the maximum
 *		allowable programmed frequency and करोes not account क्रम घड़ी
 *		tolerances and jitter.
 * @match_freq:	Frequency match in Hz response.
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 */
अटल पूर्णांक ti_sci_cmd_clk_get_match_freq(स्थिर काष्ठा ti_sci_handle *handle,
					 u32 dev_id, u32 clk_id, u64 min_freq,
					 u64 target_freq, u64 max_freq,
					 u64 *match_freq)
अणु
	काष्ठा ti_sci_info *info;
	काष्ठा ti_sci_msg_req_query_घड़ी_freq *req;
	काष्ठा ti_sci_msg_resp_query_घड़ी_freq *resp;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);
	अगर (!handle || !match_freq)
		वापस -EINVAL;

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_QUERY_CLOCK_FREQ,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message alloc failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_req_query_घड़ी_freq *)xfer->xfer_buf;
	req->dev_id = dev_id;
	अगर (clk_id < 255) अणु
		req->clk_id = clk_id;
	पूर्ण अन्यथा अणु
		req->clk_id = 255;
		req->clk_id_32 = clk_id;
	पूर्ण
	req->min_freq_hz = min_freq;
	req->target_freq_hz = target_freq;
	req->max_freq_hz = max_freq;

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "Mbox send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_resp_query_घड़ी_freq *)xfer->xfer_buf;

	अगर (!ti_sci_is_response_ack(resp))
		ret = -ENODEV;
	अन्यथा
		*match_freq = resp->freq_hz;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);

	वापस ret;
पूर्ण

/**
 * ti_sci_cmd_clk_set_freq() - Set a frequency क्रम घड़ी
 * @handle:	poपूर्णांकer to TI SCI handle
 * @dev_id:	Device identअगरier this request is क्रम
 * @clk_id:	Clock identअगरier क्रम the device क्रम this request.
 *		Each device has it's own set of घड़ी inमाला_दो. This indexes
 *		which घड़ी input to modअगरy.
 * @min_freq:	The minimum allowable frequency in Hz. This is the minimum
 *		allowable programmed frequency and करोes not account क्रम घड़ी
 *		tolerances and jitter.
 * @target_freq: The target घड़ी frequency in Hz. A frequency will be
 *		processed as बंद to this target frequency as possible.
 * @max_freq:	The maximum allowable frequency in Hz. This is the maximum
 *		allowable programmed frequency and करोes not account क्रम घड़ी
 *		tolerances and jitter.
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 */
अटल पूर्णांक ti_sci_cmd_clk_set_freq(स्थिर काष्ठा ti_sci_handle *handle,
				   u32 dev_id, u32 clk_id, u64 min_freq,
				   u64 target_freq, u64 max_freq)
अणु
	काष्ठा ti_sci_info *info;
	काष्ठा ti_sci_msg_req_set_घड़ी_freq *req;
	काष्ठा ti_sci_msg_hdr *resp;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);
	अगर (!handle)
		वापस -EINVAL;

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_SET_CLOCK_FREQ,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message alloc failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_req_set_घड़ी_freq *)xfer->xfer_buf;
	req->dev_id = dev_id;
	अगर (clk_id < 255) अणु
		req->clk_id = clk_id;
	पूर्ण अन्यथा अणु
		req->clk_id = 255;
		req->clk_id_32 = clk_id;
	पूर्ण
	req->min_freq_hz = min_freq;
	req->target_freq_hz = target_freq;
	req->max_freq_hz = max_freq;

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "Mbox send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_hdr *)xfer->xfer_buf;

	ret = ti_sci_is_response_ack(resp) ? 0 : -ENODEV;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);

	वापस ret;
पूर्ण

/**
 * ti_sci_cmd_clk_get_freq() - Get current frequency
 * @handle:	poपूर्णांकer to TI SCI handle
 * @dev_id:	Device identअगरier this request is क्रम
 * @clk_id:	Clock identअगरier क्रम the device क्रम this request.
 *		Each device has it's own set of घड़ी inमाला_दो. This indexes
 *		which घड़ी input to modअगरy.
 * @freq:	Currently frequency in Hz
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 */
अटल पूर्णांक ti_sci_cmd_clk_get_freq(स्थिर काष्ठा ti_sci_handle *handle,
				   u32 dev_id, u32 clk_id, u64 *freq)
अणु
	काष्ठा ti_sci_info *info;
	काष्ठा ti_sci_msg_req_get_घड़ी_freq *req;
	काष्ठा ti_sci_msg_resp_get_घड़ी_freq *resp;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);
	अगर (!handle || !freq)
		वापस -EINVAL;

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_GET_CLOCK_FREQ,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message alloc failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_req_get_घड़ी_freq *)xfer->xfer_buf;
	req->dev_id = dev_id;
	अगर (clk_id < 255) अणु
		req->clk_id = clk_id;
	पूर्ण अन्यथा अणु
		req->clk_id = 255;
		req->clk_id_32 = clk_id;
	पूर्ण

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "Mbox send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_resp_get_घड़ी_freq *)xfer->xfer_buf;

	अगर (!ti_sci_is_response_ack(resp))
		ret = -ENODEV;
	अन्यथा
		*freq = resp->freq_hz;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);

	वापस ret;
पूर्ण

अटल पूर्णांक ti_sci_cmd_core_reboot(स्थिर काष्ठा ti_sci_handle *handle)
अणु
	काष्ठा ti_sci_info *info;
	काष्ठा ti_sci_msg_req_reboot *req;
	काष्ठा ti_sci_msg_hdr *resp;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);
	अगर (!handle)
		वापस -EINVAL;

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_SYS_RESET,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message alloc failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_req_reboot *)xfer->xfer_buf;

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "Mbox send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_hdr *)xfer->xfer_buf;

	अगर (!ti_sci_is_response_ack(resp))
		ret = -ENODEV;
	अन्यथा
		ret = 0;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);

	वापस ret;
पूर्ण

/**
 * ti_sci_get_resource_range - Helper to get a range of resources asचिन्हित
 *			       to a host. Resource is uniquely identअगरied by
 *			       type and subtype.
 * @handle:		Poपूर्णांकer to TISCI handle.
 * @dev_id:		TISCI device ID.
 * @subtype:		Resource assignment subtype that is being requested
 *			from the given device.
 * @s_host:		Host processor ID to which the resources are allocated
 * @desc:		Poपूर्णांकer to ti_sci_resource_desc to be updated with the
 *			resource range start index and number of resources
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल पूर्णांक ti_sci_get_resource_range(स्थिर काष्ठा ti_sci_handle *handle,
				     u32 dev_id, u8 subtype, u8 s_host,
				     काष्ठा ti_sci_resource_desc *desc)
अणु
	काष्ठा ti_sci_msg_resp_get_resource_range *resp;
	काष्ठा ti_sci_msg_req_get_resource_range *req;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा ti_sci_info *info;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);
	अगर (!handle || !desc)
		वापस -EINVAL;

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_GET_RESOURCE_RANGE,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message alloc failed(%d)\n", ret);
		वापस ret;
	पूर्ण

	req = (काष्ठा ti_sci_msg_req_get_resource_range *)xfer->xfer_buf;
	req->secondary_host = s_host;
	req->type = dev_id & MSG_RM_RESOURCE_TYPE_MASK;
	req->subtype = subtype & MSG_RM_RESOURCE_SUBTYPE_MASK;

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "Mbox send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_resp_get_resource_range *)xfer->xfer_buf;

	अगर (!ti_sci_is_response_ack(resp)) अणु
		ret = -ENODEV;
	पूर्ण अन्यथा अगर (!resp->range_num && !resp->range_num_sec) अणु
		/* Neither of the two resource range is valid */
		ret = -ENODEV;
	पूर्ण अन्यथा अणु
		desc->start = resp->range_start;
		desc->num = resp->range_num;
		desc->start_sec = resp->range_start_sec;
		desc->num_sec = resp->range_num_sec;
	पूर्ण;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);

	वापस ret;
पूर्ण

/**
 * ti_sci_cmd_get_resource_range - Get a range of resources asचिन्हित to host
 *				   that is same as ti sci पूर्णांकerface host.
 * @handle:		Poपूर्णांकer to TISCI handle.
 * @dev_id:		TISCI device ID.
 * @subtype:		Resource assignment subtype that is being requested
 *			from the given device.
 * @desc:		Poपूर्णांकer to ti_sci_resource_desc to be updated with the
 *			resource range start index and number of resources
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल पूर्णांक ti_sci_cmd_get_resource_range(स्थिर काष्ठा ti_sci_handle *handle,
					 u32 dev_id, u8 subtype,
					 काष्ठा ti_sci_resource_desc *desc)
अणु
	वापस ti_sci_get_resource_range(handle, dev_id, subtype,
					 TI_SCI_IRQ_SECONDARY_HOST_INVALID,
					 desc);
पूर्ण

/**
 * ti_sci_cmd_get_resource_range_from_shost - Get a range of resources
 *					      asचिन्हित to a specअगरied host.
 * @handle:		Poपूर्णांकer to TISCI handle.
 * @dev_id:		TISCI device ID.
 * @subtype:		Resource assignment subtype that is being requested
 *			from the given device.
 * @s_host:		Host processor ID to which the resources are allocated
 * @desc:		Poपूर्णांकer to ti_sci_resource_desc to be updated with the
 *			resource range start index and number of resources
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल
पूर्णांक ti_sci_cmd_get_resource_range_from_shost(स्थिर काष्ठा ti_sci_handle *handle,
					     u32 dev_id, u8 subtype, u8 s_host,
					     काष्ठा ti_sci_resource_desc *desc)
अणु
	वापस ti_sci_get_resource_range(handle, dev_id, subtype, s_host, desc);
पूर्ण

/**
 * ti_sci_manage_irq() - Helper api to configure/release the irq route between
 *			 the requested source and destination
 * @handle:		Poपूर्णांकer to TISCI handle.
 * @valid_params:	Bit fields defining the validity of certain params
 * @src_id:		Device ID of the IRQ source
 * @src_index:		IRQ source index within the source device
 * @dst_id:		Device ID of the IRQ destination
 * @dst_host_irq:	IRQ number of the destination device
 * @ia_id:		Device ID of the IA, अगर the IRQ flows through this IA
 * @vपूर्णांक:		Virtual पूर्णांकerrupt to be used within the IA
 * @global_event:	Global event number to be used क्रम the requesting event
 * @vपूर्णांक_status_bit:	Virtual पूर्णांकerrupt status bit to be used क्रम the event
 * @s_host:		Secondary host ID to which the irq/event is being
 *			requested क्रम.
 * @type:		Request type irq set or release.
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल पूर्णांक ti_sci_manage_irq(स्थिर काष्ठा ti_sci_handle *handle,
			     u32 valid_params, u16 src_id, u16 src_index,
			     u16 dst_id, u16 dst_host_irq, u16 ia_id, u16 vपूर्णांक,
			     u16 global_event, u8 vपूर्णांक_status_bit, u8 s_host,
			     u16 type)
अणु
	काष्ठा ti_sci_msg_req_manage_irq *req;
	काष्ठा ti_sci_msg_hdr *resp;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा ti_sci_info *info;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);
	अगर (!handle)
		वापस -EINVAL;

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, type, TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message alloc failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_req_manage_irq *)xfer->xfer_buf;
	req->valid_params = valid_params;
	req->src_id = src_id;
	req->src_index = src_index;
	req->dst_id = dst_id;
	req->dst_host_irq = dst_host_irq;
	req->ia_id = ia_id;
	req->vपूर्णांक = vपूर्णांक;
	req->global_event = global_event;
	req->vपूर्णांक_status_bit = vपूर्णांक_status_bit;
	req->secondary_host = s_host;

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "Mbox send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_hdr *)xfer->xfer_buf;

	ret = ti_sci_is_response_ack(resp) ? 0 : -ENODEV;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);

	वापस ret;
पूर्ण

/**
 * ti_sci_set_irq() - Helper api to configure the irq route between the
 *		      requested source and destination
 * @handle:		Poपूर्णांकer to TISCI handle.
 * @valid_params:	Bit fields defining the validity of certain params
 * @src_id:		Device ID of the IRQ source
 * @src_index:		IRQ source index within the source device
 * @dst_id:		Device ID of the IRQ destination
 * @dst_host_irq:	IRQ number of the destination device
 * @ia_id:		Device ID of the IA, अगर the IRQ flows through this IA
 * @vपूर्णांक:		Virtual पूर्णांकerrupt to be used within the IA
 * @global_event:	Global event number to be used क्रम the requesting event
 * @vपूर्णांक_status_bit:	Virtual पूर्णांकerrupt status bit to be used क्रम the event
 * @s_host:		Secondary host ID to which the irq/event is being
 *			requested क्रम.
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल पूर्णांक ti_sci_set_irq(स्थिर काष्ठा ti_sci_handle *handle, u32 valid_params,
			  u16 src_id, u16 src_index, u16 dst_id,
			  u16 dst_host_irq, u16 ia_id, u16 vपूर्णांक,
			  u16 global_event, u8 vपूर्णांक_status_bit, u8 s_host)
अणु
	pr_debug("%s: IRQ set with valid_params = 0x%x from src = %d, index = %d, to dst = %d, irq = %d,via ia_id = %d, vint = %d, global event = %d,status_bit = %d\n",
		 __func__, valid_params, src_id, src_index,
		 dst_id, dst_host_irq, ia_id, vपूर्णांक, global_event,
		 vपूर्णांक_status_bit);

	वापस ti_sci_manage_irq(handle, valid_params, src_id, src_index,
				 dst_id, dst_host_irq, ia_id, vपूर्णांक,
				 global_event, vपूर्णांक_status_bit, s_host,
				 TI_SCI_MSG_SET_IRQ);
पूर्ण

/**
 * ti_sci_मुक्त_irq() - Helper api to मुक्त the irq route between the
 *			   requested source and destination
 * @handle:		Poपूर्णांकer to TISCI handle.
 * @valid_params:	Bit fields defining the validity of certain params
 * @src_id:		Device ID of the IRQ source
 * @src_index:		IRQ source index within the source device
 * @dst_id:		Device ID of the IRQ destination
 * @dst_host_irq:	IRQ number of the destination device
 * @ia_id:		Device ID of the IA, अगर the IRQ flows through this IA
 * @vपूर्णांक:		Virtual पूर्णांकerrupt to be used within the IA
 * @global_event:	Global event number to be used क्रम the requesting event
 * @vपूर्णांक_status_bit:	Virtual पूर्णांकerrupt status bit to be used क्रम the event
 * @s_host:		Secondary host ID to which the irq/event is being
 *			requested क्रम.
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल पूर्णांक ti_sci_मुक्त_irq(स्थिर काष्ठा ti_sci_handle *handle, u32 valid_params,
			   u16 src_id, u16 src_index, u16 dst_id,
			   u16 dst_host_irq, u16 ia_id, u16 vपूर्णांक,
			   u16 global_event, u8 vपूर्णांक_status_bit, u8 s_host)
अणु
	pr_debug("%s: IRQ release with valid_params = 0x%x from src = %d, index = %d, to dst = %d, irq = %d,via ia_id = %d, vint = %d, global event = %d,status_bit = %d\n",
		 __func__, valid_params, src_id, src_index,
		 dst_id, dst_host_irq, ia_id, vपूर्णांक, global_event,
		 vपूर्णांक_status_bit);

	वापस ti_sci_manage_irq(handle, valid_params, src_id, src_index,
				 dst_id, dst_host_irq, ia_id, vपूर्णांक,
				 global_event, vपूर्णांक_status_bit, s_host,
				 TI_SCI_MSG_FREE_IRQ);
पूर्ण

/**
 * ti_sci_cmd_set_irq() - Configure a host irq route between the requested
 *			  source and destination.
 * @handle:		Poपूर्णांकer to TISCI handle.
 * @src_id:		Device ID of the IRQ source
 * @src_index:		IRQ source index within the source device
 * @dst_id:		Device ID of the IRQ destination
 * @dst_host_irq:	IRQ number of the destination device
 * @vपूर्णांक_irq:		Boolean specअगरying अगर this पूर्णांकerrupt beदीर्घs to
 *			Interrupt Aggregator.
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल पूर्णांक ti_sci_cmd_set_irq(स्थिर काष्ठा ti_sci_handle *handle, u16 src_id,
			      u16 src_index, u16 dst_id, u16 dst_host_irq)
अणु
	u32 valid_params = MSG_FLAG_DST_ID_VALID | MSG_FLAG_DST_HOST_IRQ_VALID;

	वापस ti_sci_set_irq(handle, valid_params, src_id, src_index, dst_id,
			      dst_host_irq, 0, 0, 0, 0, 0);
पूर्ण

/**
 * ti_sci_cmd_set_event_map() - Configure an event based irq route between the
 *				requested source and Interrupt Aggregator.
 * @handle:		Poपूर्णांकer to TISCI handle.
 * @src_id:		Device ID of the IRQ source
 * @src_index:		IRQ source index within the source device
 * @ia_id:		Device ID of the IA, अगर the IRQ flows through this IA
 * @vपूर्णांक:		Virtual पूर्णांकerrupt to be used within the IA
 * @global_event:	Global event number to be used क्रम the requesting event
 * @vपूर्णांक_status_bit:	Virtual पूर्णांकerrupt status bit to be used क्रम the event
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल पूर्णांक ti_sci_cmd_set_event_map(स्थिर काष्ठा ti_sci_handle *handle,
				    u16 src_id, u16 src_index, u16 ia_id,
				    u16 vपूर्णांक, u16 global_event,
				    u8 vपूर्णांक_status_bit)
अणु
	u32 valid_params = MSG_FLAG_IA_ID_VALID | MSG_FLAG_VINT_VALID |
			   MSG_FLAG_GLB_EVNT_VALID |
			   MSG_FLAG_VINT_STS_BIT_VALID;

	वापस ti_sci_set_irq(handle, valid_params, src_id, src_index, 0, 0,
			      ia_id, vपूर्णांक, global_event, vपूर्णांक_status_bit, 0);
पूर्ण

/**
 * ti_sci_cmd_मुक्त_irq() - Free a host irq route between the between the
 *			   requested source and destination.
 * @handle:		Poपूर्णांकer to TISCI handle.
 * @src_id:		Device ID of the IRQ source
 * @src_index:		IRQ source index within the source device
 * @dst_id:		Device ID of the IRQ destination
 * @dst_host_irq:	IRQ number of the destination device
 * @vपूर्णांक_irq:		Boolean specअगरying अगर this पूर्णांकerrupt beदीर्घs to
 *			Interrupt Aggregator.
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल पूर्णांक ti_sci_cmd_मुक्त_irq(स्थिर काष्ठा ti_sci_handle *handle, u16 src_id,
			       u16 src_index, u16 dst_id, u16 dst_host_irq)
अणु
	u32 valid_params = MSG_FLAG_DST_ID_VALID | MSG_FLAG_DST_HOST_IRQ_VALID;

	वापस ti_sci_मुक्त_irq(handle, valid_params, src_id, src_index, dst_id,
			       dst_host_irq, 0, 0, 0, 0, 0);
पूर्ण

/**
 * ti_sci_cmd_मुक्त_event_map() - Free an event map between the requested source
 *				 and Interrupt Aggregator.
 * @handle:		Poपूर्णांकer to TISCI handle.
 * @src_id:		Device ID of the IRQ source
 * @src_index:		IRQ source index within the source device
 * @ia_id:		Device ID of the IA, अगर the IRQ flows through this IA
 * @vपूर्णांक:		Virtual पूर्णांकerrupt to be used within the IA
 * @global_event:	Global event number to be used क्रम the requesting event
 * @vपूर्णांक_status_bit:	Virtual पूर्णांकerrupt status bit to be used क्रम the event
 *
 * Return: 0 अगर all went fine, अन्यथा वापस appropriate error.
 */
अटल पूर्णांक ti_sci_cmd_मुक्त_event_map(स्थिर काष्ठा ti_sci_handle *handle,
				     u16 src_id, u16 src_index, u16 ia_id,
				     u16 vपूर्णांक, u16 global_event,
				     u8 vपूर्णांक_status_bit)
अणु
	u32 valid_params = MSG_FLAG_IA_ID_VALID |
			   MSG_FLAG_VINT_VALID | MSG_FLAG_GLB_EVNT_VALID |
			   MSG_FLAG_VINT_STS_BIT_VALID;

	वापस ti_sci_मुक्त_irq(handle, valid_params, src_id, src_index, 0, 0,
			       ia_id, vपूर्णांक, global_event, vपूर्णांक_status_bit, 0);
पूर्ण

/**
 * ti_sci_cmd_rm_ring_cfg() - Configure a NAVSS ring
 * @handle:	Poपूर्णांकer to TI SCI handle.
 * @params:	Poपूर्णांकer to ti_sci_msg_rm_ring_cfg ring config काष्ठाure
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 *
 * See @ti_sci_msg_rm_ring_cfg and @ti_sci_msg_rm_ring_cfg_req क्रम
 * more info.
 */
अटल पूर्णांक ti_sci_cmd_rm_ring_cfg(स्थिर काष्ठा ti_sci_handle *handle,
				  स्थिर काष्ठा ti_sci_msg_rm_ring_cfg *params)
अणु
	काष्ठा ti_sci_msg_rm_ring_cfg_req *req;
	काष्ठा ti_sci_msg_hdr *resp;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा ti_sci_info *info;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (IS_ERR_OR_शून्य(handle))
		वापस -EINVAL;

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_RM_RING_CFG,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "RM_RA:Message config failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_rm_ring_cfg_req *)xfer->xfer_buf;
	req->valid_params = params->valid_params;
	req->nav_id = params->nav_id;
	req->index = params->index;
	req->addr_lo = params->addr_lo;
	req->addr_hi = params->addr_hi;
	req->count = params->count;
	req->mode = params->mode;
	req->size = params->size;
	req->order_id = params->order_id;
	req->virtid = params->virtid;
	req->asel = params->asel;

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "RM_RA:Mbox config send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_hdr *)xfer->xfer_buf;
	ret = ti_sci_is_response_ack(resp) ? 0 : -EINVAL;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);
	dev_dbg(dev, "RM_RA:config ring %u ret:%d\n", params->index, ret);
	वापस ret;
पूर्ण

/**
 * ti_sci_cmd_rm_psil_pair() - Pair PSI-L source to destination thपढ़ो
 * @handle:	Poपूर्णांकer to TI SCI handle.
 * @nav_id:	Device ID of Navigator Subप्रणाली which should be used क्रम
 *		pairing
 * @src_thपढ़ो:	Source PSI-L thपढ़ो ID
 * @dst_thपढ़ो: Destination PSI-L thपढ़ो ID
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 */
अटल पूर्णांक ti_sci_cmd_rm_psil_pair(स्थिर काष्ठा ti_sci_handle *handle,
				   u32 nav_id, u32 src_thपढ़ो, u32 dst_thपढ़ो)
अणु
	काष्ठा ti_sci_msg_psil_pair *req;
	काष्ठा ti_sci_msg_hdr *resp;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा ti_sci_info *info;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);
	अगर (!handle)
		वापस -EINVAL;

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_RM_PSIL_PAIR,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "RM_PSIL:Message reconfig failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_psil_pair *)xfer->xfer_buf;
	req->nav_id = nav_id;
	req->src_thपढ़ो = src_thपढ़ो;
	req->dst_thपढ़ो = dst_thपढ़ो;

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "RM_PSIL:Mbox send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_hdr *)xfer->xfer_buf;
	ret = ti_sci_is_response_ack(resp) ? 0 : -EINVAL;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);

	वापस ret;
पूर्ण

/**
 * ti_sci_cmd_rm_psil_unpair() - Unpair PSI-L source from destination thपढ़ो
 * @handle:	Poपूर्णांकer to TI SCI handle.
 * @nav_id:	Device ID of Navigator Subप्रणाली which should be used क्रम
 *		unpairing
 * @src_thपढ़ो:	Source PSI-L thपढ़ो ID
 * @dst_thपढ़ो:	Destination PSI-L thपढ़ो ID
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 */
अटल पूर्णांक ti_sci_cmd_rm_psil_unpair(स्थिर काष्ठा ti_sci_handle *handle,
				     u32 nav_id, u32 src_thपढ़ो, u32 dst_thपढ़ो)
अणु
	काष्ठा ti_sci_msg_psil_unpair *req;
	काष्ठा ti_sci_msg_hdr *resp;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा ti_sci_info *info;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);
	अगर (!handle)
		वापस -EINVAL;

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_RM_PSIL_UNPAIR,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "RM_PSIL:Message reconfig failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_psil_unpair *)xfer->xfer_buf;
	req->nav_id = nav_id;
	req->src_thपढ़ो = src_thपढ़ो;
	req->dst_thपढ़ो = dst_thपढ़ो;

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "RM_PSIL:Mbox send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_hdr *)xfer->xfer_buf;
	ret = ti_sci_is_response_ack(resp) ? 0 : -EINVAL;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);

	वापस ret;
पूर्ण

/**
 * ti_sci_cmd_rm_udmap_tx_ch_cfg() - Configure a UDMAP TX channel
 * @handle:	Poपूर्णांकer to TI SCI handle.
 * @params:	Poपूर्णांकer to ti_sci_msg_rm_udmap_tx_ch_cfg TX channel config
 *		काष्ठाure
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 *
 * See @ti_sci_msg_rm_udmap_tx_ch_cfg and @ti_sci_msg_rm_udmap_tx_ch_cfg_req क्रम
 * more info.
 */
अटल पूर्णांक ti_sci_cmd_rm_udmap_tx_ch_cfg(स्थिर काष्ठा ti_sci_handle *handle,
			स्थिर काष्ठा ti_sci_msg_rm_udmap_tx_ch_cfg *params)
अणु
	काष्ठा ti_sci_msg_rm_udmap_tx_ch_cfg_req *req;
	काष्ठा ti_sci_msg_hdr *resp;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा ti_sci_info *info;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (IS_ERR_OR_शून्य(handle))
		वापस -EINVAL;

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TISCI_MSG_RM_UDMAP_TX_CH_CFG,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message TX_CH_CFG alloc failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_rm_udmap_tx_ch_cfg_req *)xfer->xfer_buf;
	req->valid_params = params->valid_params;
	req->nav_id = params->nav_id;
	req->index = params->index;
	req->tx_छोड़ो_on_err = params->tx_छोड़ो_on_err;
	req->tx_filt_einfo = params->tx_filt_einfo;
	req->tx_filt_pswords = params->tx_filt_pswords;
	req->tx_atype = params->tx_atype;
	req->tx_chan_type = params->tx_chan_type;
	req->tx_supr_tdpkt = params->tx_supr_tdpkt;
	req->tx_fetch_size = params->tx_fetch_size;
	req->tx_credit_count = params->tx_credit_count;
	req->txcq_qnum = params->txcq_qnum;
	req->tx_priority = params->tx_priority;
	req->tx_qos = params->tx_qos;
	req->tx_orderid = params->tx_orderid;
	req->fdepth = params->fdepth;
	req->tx_sched_priority = params->tx_sched_priority;
	req->tx_burst_size = params->tx_burst_size;
	req->tx_tdtype = params->tx_tdtype;
	req->extended_ch_type = params->extended_ch_type;

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "Mbox send TX_CH_CFG fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_hdr *)xfer->xfer_buf;
	ret = ti_sci_is_response_ack(resp) ? 0 : -EINVAL;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);
	dev_dbg(dev, "TX_CH_CFG: chn %u ret:%u\n", params->index, ret);
	वापस ret;
पूर्ण

/**
 * ti_sci_cmd_rm_udmap_rx_ch_cfg() - Configure a UDMAP RX channel
 * @handle:	Poपूर्णांकer to TI SCI handle.
 * @params:	Poपूर्णांकer to ti_sci_msg_rm_udmap_rx_ch_cfg RX channel config
 *		काष्ठाure
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 *
 * See @ti_sci_msg_rm_udmap_rx_ch_cfg and @ti_sci_msg_rm_udmap_rx_ch_cfg_req क्रम
 * more info.
 */
अटल पूर्णांक ti_sci_cmd_rm_udmap_rx_ch_cfg(स्थिर काष्ठा ti_sci_handle *handle,
			स्थिर काष्ठा ti_sci_msg_rm_udmap_rx_ch_cfg *params)
अणु
	काष्ठा ti_sci_msg_rm_udmap_rx_ch_cfg_req *req;
	काष्ठा ti_sci_msg_hdr *resp;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा ti_sci_info *info;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (IS_ERR_OR_शून्य(handle))
		वापस -EINVAL;

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TISCI_MSG_RM_UDMAP_RX_CH_CFG,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message RX_CH_CFG alloc failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_rm_udmap_rx_ch_cfg_req *)xfer->xfer_buf;
	req->valid_params = params->valid_params;
	req->nav_id = params->nav_id;
	req->index = params->index;
	req->rx_fetch_size = params->rx_fetch_size;
	req->rxcq_qnum = params->rxcq_qnum;
	req->rx_priority = params->rx_priority;
	req->rx_qos = params->rx_qos;
	req->rx_orderid = params->rx_orderid;
	req->rx_sched_priority = params->rx_sched_priority;
	req->flowid_start = params->flowid_start;
	req->flowid_cnt = params->flowid_cnt;
	req->rx_छोड़ो_on_err = params->rx_छोड़ो_on_err;
	req->rx_atype = params->rx_atype;
	req->rx_chan_type = params->rx_chan_type;
	req->rx_ignore_लघु = params->rx_ignore_लघु;
	req->rx_ignore_दीर्घ = params->rx_ignore_दीर्घ;
	req->rx_burst_size = params->rx_burst_size;

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "Mbox send RX_CH_CFG fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_hdr *)xfer->xfer_buf;
	ret = ti_sci_is_response_ack(resp) ? 0 : -EINVAL;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);
	dev_dbg(dev, "RX_CH_CFG: chn %u ret:%d\n", params->index, ret);
	वापस ret;
पूर्ण

/**
 * ti_sci_cmd_rm_udmap_rx_flow_cfg() - Configure UDMAP RX FLOW
 * @handle:	Poपूर्णांकer to TI SCI handle.
 * @params:	Poपूर्णांकer to ti_sci_msg_rm_udmap_flow_cfg RX FLOW config
 *		काष्ठाure
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 *
 * See @ti_sci_msg_rm_udmap_flow_cfg and @ti_sci_msg_rm_udmap_flow_cfg_req क्रम
 * more info.
 */
अटल पूर्णांक ti_sci_cmd_rm_udmap_rx_flow_cfg(स्थिर काष्ठा ti_sci_handle *handle,
			स्थिर काष्ठा ti_sci_msg_rm_udmap_flow_cfg *params)
अणु
	काष्ठा ti_sci_msg_rm_udmap_flow_cfg_req *req;
	काष्ठा ti_sci_msg_hdr *resp;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा ti_sci_info *info;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (IS_ERR_OR_शून्य(handle))
		वापस -EINVAL;

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TISCI_MSG_RM_UDMAP_FLOW_CFG,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "RX_FL_CFG: Message alloc failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_rm_udmap_flow_cfg_req *)xfer->xfer_buf;
	req->valid_params = params->valid_params;
	req->nav_id = params->nav_id;
	req->flow_index = params->flow_index;
	req->rx_einfo_present = params->rx_einfo_present;
	req->rx_psinfo_present = params->rx_psinfo_present;
	req->rx_error_handling = params->rx_error_handling;
	req->rx_desc_type = params->rx_desc_type;
	req->rx_sop_offset = params->rx_sop_offset;
	req->rx_dest_qnum = params->rx_dest_qnum;
	req->rx_src_tag_hi = params->rx_src_tag_hi;
	req->rx_src_tag_lo = params->rx_src_tag_lo;
	req->rx_dest_tag_hi = params->rx_dest_tag_hi;
	req->rx_dest_tag_lo = params->rx_dest_tag_lo;
	req->rx_src_tag_hi_sel = params->rx_src_tag_hi_sel;
	req->rx_src_tag_lo_sel = params->rx_src_tag_lo_sel;
	req->rx_dest_tag_hi_sel = params->rx_dest_tag_hi_sel;
	req->rx_dest_tag_lo_sel = params->rx_dest_tag_lo_sel;
	req->rx_fdq0_sz0_qnum = params->rx_fdq0_sz0_qnum;
	req->rx_fdq1_qnum = params->rx_fdq1_qnum;
	req->rx_fdq2_qnum = params->rx_fdq2_qnum;
	req->rx_fdq3_qnum = params->rx_fdq3_qnum;
	req->rx_ps_location = params->rx_ps_location;

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "RX_FL_CFG: Mbox send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_hdr *)xfer->xfer_buf;
	ret = ti_sci_is_response_ack(resp) ? 0 : -EINVAL;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);
	dev_dbg(info->dev, "RX_FL_CFG: %u ret:%d\n", params->flow_index, ret);
	वापस ret;
पूर्ण

/**
 * ti_sci_cmd_proc_request() - Command to request a physical processor control
 * @handle:	Poपूर्णांकer to TI SCI handle
 * @proc_id:	Processor ID this request is क्रम
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 */
अटल पूर्णांक ti_sci_cmd_proc_request(स्थिर काष्ठा ti_sci_handle *handle,
				   u8 proc_id)
अणु
	काष्ठा ti_sci_msg_req_proc_request *req;
	काष्ठा ti_sci_msg_hdr *resp;
	काष्ठा ti_sci_info *info;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (!handle)
		वापस -EINVAL;
	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_PROC_REQUEST,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message alloc failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_req_proc_request *)xfer->xfer_buf;
	req->processor_id = proc_id;

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "Mbox send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_hdr *)xfer->tx_message.buf;

	ret = ti_sci_is_response_ack(resp) ? 0 : -ENODEV;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);

	वापस ret;
पूर्ण

/**
 * ti_sci_cmd_proc_release() - Command to release a physical processor control
 * @handle:	Poपूर्णांकer to TI SCI handle
 * @proc_id:	Processor ID this request is क्रम
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 */
अटल पूर्णांक ti_sci_cmd_proc_release(स्थिर काष्ठा ti_sci_handle *handle,
				   u8 proc_id)
अणु
	काष्ठा ti_sci_msg_req_proc_release *req;
	काष्ठा ti_sci_msg_hdr *resp;
	काष्ठा ti_sci_info *info;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (!handle)
		वापस -EINVAL;
	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_PROC_RELEASE,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message alloc failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_req_proc_release *)xfer->xfer_buf;
	req->processor_id = proc_id;

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "Mbox send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_hdr *)xfer->tx_message.buf;

	ret = ti_sci_is_response_ack(resp) ? 0 : -ENODEV;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);

	वापस ret;
पूर्ण

/**
 * ti_sci_cmd_proc_hanकरोver() - Command to hanकरोver a physical processor
 *				control to a host in the processor's access
 *				control list.
 * @handle:	Poपूर्णांकer to TI SCI handle
 * @proc_id:	Processor ID this request is क्रम
 * @host_id:	Host ID to get the control of the processor
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 */
अटल पूर्णांक ti_sci_cmd_proc_hanकरोver(स्थिर काष्ठा ti_sci_handle *handle,
				    u8 proc_id, u8 host_id)
अणु
	काष्ठा ti_sci_msg_req_proc_hanकरोver *req;
	काष्ठा ti_sci_msg_hdr *resp;
	काष्ठा ti_sci_info *info;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (!handle)
		वापस -EINVAL;
	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_PROC_HANDOVER,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message alloc failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_req_proc_hanकरोver *)xfer->xfer_buf;
	req->processor_id = proc_id;
	req->host_id = host_id;

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "Mbox send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_hdr *)xfer->tx_message.buf;

	ret = ti_sci_is_response_ack(resp) ? 0 : -ENODEV;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);

	वापस ret;
पूर्ण

/**
 * ti_sci_cmd_proc_set_config() - Command to set the processor boot
 *				    configuration flags
 * @handle:		Poपूर्णांकer to TI SCI handle
 * @proc_id:		Processor ID this request is क्रम
 * @config_flags_set:	Configuration flags to be set
 * @config_flags_clear:	Configuration flags to be cleared.
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 */
अटल पूर्णांक ti_sci_cmd_proc_set_config(स्थिर काष्ठा ti_sci_handle *handle,
				      u8 proc_id, u64 bootvector,
				      u32 config_flags_set,
				      u32 config_flags_clear)
अणु
	काष्ठा ti_sci_msg_req_set_config *req;
	काष्ठा ti_sci_msg_hdr *resp;
	काष्ठा ti_sci_info *info;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (!handle)
		वापस -EINVAL;
	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_SET_CONFIG,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message alloc failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_req_set_config *)xfer->xfer_buf;
	req->processor_id = proc_id;
	req->bootvector_low = bootvector & TI_SCI_ADDR_LOW_MASK;
	req->bootvector_high = (bootvector & TI_SCI_ADDR_HIGH_MASK) >>
				TI_SCI_ADDR_HIGH_SHIFT;
	req->config_flags_set = config_flags_set;
	req->config_flags_clear = config_flags_clear;

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "Mbox send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_hdr *)xfer->tx_message.buf;

	ret = ti_sci_is_response_ack(resp) ? 0 : -ENODEV;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);

	वापस ret;
पूर्ण

/**
 * ti_sci_cmd_proc_set_control() - Command to set the processor boot
 *				     control flags
 * @handle:			Poपूर्णांकer to TI SCI handle
 * @proc_id:			Processor ID this request is क्रम
 * @control_flags_set:		Control flags to be set
 * @control_flags_clear:	Control flags to be cleared
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 */
अटल पूर्णांक ti_sci_cmd_proc_set_control(स्थिर काष्ठा ti_sci_handle *handle,
				       u8 proc_id, u32 control_flags_set,
				       u32 control_flags_clear)
अणु
	काष्ठा ti_sci_msg_req_set_ctrl *req;
	काष्ठा ti_sci_msg_hdr *resp;
	काष्ठा ti_sci_info *info;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (!handle)
		वापस -EINVAL;
	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_SET_CTRL,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message alloc failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_req_set_ctrl *)xfer->xfer_buf;
	req->processor_id = proc_id;
	req->control_flags_set = control_flags_set;
	req->control_flags_clear = control_flags_clear;

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "Mbox send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_hdr *)xfer->tx_message.buf;

	ret = ti_sci_is_response_ack(resp) ? 0 : -ENODEV;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);

	वापस ret;
पूर्ण

/**
 * ti_sci_cmd_get_boot_status() - Command to get the processor boot status
 * @handle:	Poपूर्णांकer to TI SCI handle
 * @proc_id:	Processor ID this request is क्रम
 *
 * Return: 0 अगर all went well, अन्यथा वापसs appropriate error value.
 */
अटल पूर्णांक ti_sci_cmd_proc_get_status(स्थिर काष्ठा ti_sci_handle *handle,
				      u8 proc_id, u64 *bv, u32 *cfg_flags,
				      u32 *ctrl_flags, u32 *sts_flags)
अणु
	काष्ठा ti_sci_msg_resp_get_status *resp;
	काष्ठा ti_sci_msg_req_get_status *req;
	काष्ठा ti_sci_info *info;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (!handle)
		वापस -EINVAL;
	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_GET_STATUS,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   माप(*req), माप(*resp));
	अगर (IS_ERR(xfer)) अणु
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message alloc failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	req = (काष्ठा ti_sci_msg_req_get_status *)xfer->xfer_buf;
	req->processor_id = proc_id;

	ret = ti_sci_करो_xfer(info, xfer);
	अगर (ret) अणु
		dev_err(dev, "Mbox send fail %d\n", ret);
		जाओ fail;
	पूर्ण

	resp = (काष्ठा ti_sci_msg_resp_get_status *)xfer->tx_message.buf;

	अगर (!ti_sci_is_response_ack(resp)) अणु
		ret = -ENODEV;
	पूर्ण अन्यथा अणु
		*bv = (resp->bootvector_low & TI_SCI_ADDR_LOW_MASK) |
		      (((u64)resp->bootvector_high << TI_SCI_ADDR_HIGH_SHIFT) &
		       TI_SCI_ADDR_HIGH_MASK);
		*cfg_flags = resp->config_flags;
		*ctrl_flags = resp->control_flags;
		*sts_flags = resp->status_flags;
	पूर्ण

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);

	वापस ret;
पूर्ण

/*
 * ti_sci_setup_ops() - Setup the operations काष्ठाures
 * @info:	poपूर्णांकer to TISCI poपूर्णांकer
 */
अटल व्योम ti_sci_setup_ops(काष्ठा ti_sci_info *info)
अणु
	काष्ठा ti_sci_ops *ops = &info->handle.ops;
	काष्ठा ti_sci_core_ops *core_ops = &ops->core_ops;
	काष्ठा ti_sci_dev_ops *करोps = &ops->dev_ops;
	काष्ठा ti_sci_clk_ops *cops = &ops->clk_ops;
	काष्ठा ti_sci_rm_core_ops *rm_core_ops = &ops->rm_core_ops;
	काष्ठा ti_sci_rm_irq_ops *iops = &ops->rm_irq_ops;
	काष्ठा ti_sci_rm_ringacc_ops *rops = &ops->rm_ring_ops;
	काष्ठा ti_sci_rm_psil_ops *psilops = &ops->rm_psil_ops;
	काष्ठा ti_sci_rm_udmap_ops *udmap_ops = &ops->rm_udmap_ops;
	काष्ठा ti_sci_proc_ops *pops = &ops->proc_ops;

	core_ops->reboot_device = ti_sci_cmd_core_reboot;

	करोps->get_device = ti_sci_cmd_get_device;
	करोps->get_device_exclusive = ti_sci_cmd_get_device_exclusive;
	करोps->idle_device = ti_sci_cmd_idle_device;
	करोps->idle_device_exclusive = ti_sci_cmd_idle_device_exclusive;
	करोps->put_device = ti_sci_cmd_put_device;

	करोps->is_valid = ti_sci_cmd_dev_is_valid;
	करोps->get_context_loss_count = ti_sci_cmd_dev_get_clcnt;
	करोps->is_idle = ti_sci_cmd_dev_is_idle;
	करोps->is_stop = ti_sci_cmd_dev_is_stop;
	करोps->is_on = ti_sci_cmd_dev_is_on;
	करोps->is_transitioning = ti_sci_cmd_dev_is_trans;
	करोps->set_device_resets = ti_sci_cmd_set_device_resets;
	करोps->get_device_resets = ti_sci_cmd_get_device_resets;

	cops->get_घड़ी = ti_sci_cmd_get_घड़ी;
	cops->idle_घड़ी = ti_sci_cmd_idle_घड़ी;
	cops->put_घड़ी = ti_sci_cmd_put_घड़ी;
	cops->is_स्वतः = ti_sci_cmd_clk_is_स्वतः;
	cops->is_on = ti_sci_cmd_clk_is_on;
	cops->is_off = ti_sci_cmd_clk_is_off;

	cops->set_parent = ti_sci_cmd_clk_set_parent;
	cops->get_parent = ti_sci_cmd_clk_get_parent;
	cops->get_num_parents = ti_sci_cmd_clk_get_num_parents;

	cops->get_best_match_freq = ti_sci_cmd_clk_get_match_freq;
	cops->set_freq = ti_sci_cmd_clk_set_freq;
	cops->get_freq = ti_sci_cmd_clk_get_freq;

	rm_core_ops->get_range = ti_sci_cmd_get_resource_range;
	rm_core_ops->get_range_from_shost =
				ti_sci_cmd_get_resource_range_from_shost;

	iops->set_irq = ti_sci_cmd_set_irq;
	iops->set_event_map = ti_sci_cmd_set_event_map;
	iops->मुक्त_irq = ti_sci_cmd_मुक्त_irq;
	iops->मुक्त_event_map = ti_sci_cmd_मुक्त_event_map;

	rops->set_cfg = ti_sci_cmd_rm_ring_cfg;

	psilops->pair = ti_sci_cmd_rm_psil_pair;
	psilops->unpair = ti_sci_cmd_rm_psil_unpair;

	udmap_ops->tx_ch_cfg = ti_sci_cmd_rm_udmap_tx_ch_cfg;
	udmap_ops->rx_ch_cfg = ti_sci_cmd_rm_udmap_rx_ch_cfg;
	udmap_ops->rx_flow_cfg = ti_sci_cmd_rm_udmap_rx_flow_cfg;

	pops->request = ti_sci_cmd_proc_request;
	pops->release = ti_sci_cmd_proc_release;
	pops->hanकरोver = ti_sci_cmd_proc_hanकरोver;
	pops->set_config = ti_sci_cmd_proc_set_config;
	pops->set_control = ti_sci_cmd_proc_set_control;
	pops->get_status = ti_sci_cmd_proc_get_status;
पूर्ण

/**
 * ti_sci_get_handle() - Get the TI SCI handle क्रम a device
 * @dev:	Poपूर्णांकer to device क्रम which we want SCI handle
 *
 * NOTE: The function करोes not track inभागidual clients of the framework
 * and is expected to be मुख्यtained by caller of TI SCI protocol library.
 * ti_sci_put_handle must be balanced with successful ti_sci_get_handle
 * Return: poपूर्णांकer to handle अगर successful, अन्यथा:
 * -EPROBE_DEFER अगर the instance is not पढ़ोy
 * -ENODEV अगर the required node handler is missing
 * -EINVAL अगर invalid conditions are encountered.
 */
स्थिर काष्ठा ti_sci_handle *ti_sci_get_handle(काष्ठा device *dev)
अणु
	काष्ठा device_node *ti_sci_np;
	काष्ठा list_head *p;
	काष्ठा ti_sci_handle *handle = शून्य;
	काष्ठा ti_sci_info *info;

	अगर (!dev) अणु
		pr_err("I need a device pointer\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	ti_sci_np = of_get_parent(dev->of_node);
	अगर (!ti_sci_np) अणु
		dev_err(dev, "No OF information\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	mutex_lock(&ti_sci_list_mutex);
	list_क्रम_each(p, &ti_sci_list) अणु
		info = list_entry(p, काष्ठा ti_sci_info, node);
		अगर (ti_sci_np == info->dev->of_node) अणु
			handle = &info->handle;
			info->users++;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&ti_sci_list_mutex);
	of_node_put(ti_sci_np);

	अगर (!handle)
		वापस ERR_PTR(-EPROBE_DEFER);

	वापस handle;
पूर्ण
EXPORT_SYMBOL_GPL(ti_sci_get_handle);

/**
 * ti_sci_put_handle() - Release the handle acquired by ti_sci_get_handle
 * @handle:	Handle acquired by ti_sci_get_handle
 *
 * NOTE: The function करोes not track inभागidual clients of the framework
 * and is expected to be मुख्यtained by caller of TI SCI protocol library.
 * ti_sci_put_handle must be balanced with successful ti_sci_get_handle
 *
 * Return: 0 is successfully released
 * अगर an error poपूर्णांकer was passed, it वापसs the error value back,
 * अगर null was passed, it वापसs -EINVAL;
 */
पूर्णांक ti_sci_put_handle(स्थिर काष्ठा ti_sci_handle *handle)
अणु
	काष्ठा ti_sci_info *info;

	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);
	अगर (!handle)
		वापस -EINVAL;

	info = handle_to_ti_sci_info(handle);
	mutex_lock(&ti_sci_list_mutex);
	अगर (!WARN_ON(!info->users))
		info->users--;
	mutex_unlock(&ti_sci_list_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ti_sci_put_handle);

अटल व्योम devm_ti_sci_release(काष्ठा device *dev, व्योम *res)
अणु
	स्थिर काष्ठा ti_sci_handle **ptr = res;
	स्थिर काष्ठा ti_sci_handle *handle = *ptr;
	पूर्णांक ret;

	ret = ti_sci_put_handle(handle);
	अगर (ret)
		dev_err(dev, "failed to put handle %d\n", ret);
पूर्ण

/**
 * devm_ti_sci_get_handle() - Managed get handle
 * @dev:	device क्रम which we want SCI handle क्रम.
 *
 * NOTE: This releases the handle once the device resources are
 * no दीर्घer needed. MUST NOT BE released with ti_sci_put_handle.
 * The function करोes not track inभागidual clients of the framework
 * and is expected to be मुख्यtained by caller of TI SCI protocol library.
 *
 * Return: 0 अगर all went fine, अन्यथा corresponding error.
 */
स्थिर काष्ठा ti_sci_handle *devm_ti_sci_get_handle(काष्ठा device *dev)
अणु
	स्थिर काष्ठा ti_sci_handle **ptr;
	स्थिर काष्ठा ti_sci_handle *handle;

	ptr = devres_alloc(devm_ti_sci_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);
	handle = ti_sci_get_handle(dev);

	अगर (!IS_ERR(handle)) अणु
		*ptr = handle;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस handle;
पूर्ण
EXPORT_SYMBOL_GPL(devm_ti_sci_get_handle);

/**
 * ti_sci_get_by_phandle() - Get the TI SCI handle using DT phandle
 * @np:		device node
 * @property:	property name containing phandle on TISCI node
 *
 * NOTE: The function करोes not track inभागidual clients of the framework
 * and is expected to be मुख्यtained by caller of TI SCI protocol library.
 * ti_sci_put_handle must be balanced with successful ti_sci_get_by_phandle
 * Return: poपूर्णांकer to handle अगर successful, अन्यथा:
 * -EPROBE_DEFER अगर the instance is not पढ़ोy
 * -ENODEV अगर the required node handler is missing
 * -EINVAL अगर invalid conditions are encountered.
 */
स्थिर काष्ठा ti_sci_handle *ti_sci_get_by_phandle(काष्ठा device_node *np,
						  स्थिर अक्षर *property)
अणु
	काष्ठा ti_sci_handle *handle = शून्य;
	काष्ठा device_node *ti_sci_np;
	काष्ठा ti_sci_info *info;
	काष्ठा list_head *p;

	अगर (!np) अणु
		pr_err("I need a device pointer\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	ti_sci_np = of_parse_phandle(np, property, 0);
	अगर (!ti_sci_np)
		वापस ERR_PTR(-ENODEV);

	mutex_lock(&ti_sci_list_mutex);
	list_क्रम_each(p, &ti_sci_list) अणु
		info = list_entry(p, काष्ठा ti_sci_info, node);
		अगर (ti_sci_np == info->dev->of_node) अणु
			handle = &info->handle;
			info->users++;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&ti_sci_list_mutex);
	of_node_put(ti_sci_np);

	अगर (!handle)
		वापस ERR_PTR(-EPROBE_DEFER);

	वापस handle;
पूर्ण
EXPORT_SYMBOL_GPL(ti_sci_get_by_phandle);

/**
 * devm_ti_sci_get_by_phandle() - Managed get handle using phandle
 * @dev:	Device poपूर्णांकer requesting TISCI handle
 * @property:	property name containing phandle on TISCI node
 *
 * NOTE: This releases the handle once the device resources are
 * no दीर्घer needed. MUST NOT BE released with ti_sci_put_handle.
 * The function करोes not track inभागidual clients of the framework
 * and is expected to be मुख्यtained by caller of TI SCI protocol library.
 *
 * Return: 0 अगर all went fine, अन्यथा corresponding error.
 */
स्थिर काष्ठा ti_sci_handle *devm_ti_sci_get_by_phandle(काष्ठा device *dev,
						       स्थिर अक्षर *property)
अणु
	स्थिर काष्ठा ti_sci_handle *handle;
	स्थिर काष्ठा ti_sci_handle **ptr;

	ptr = devres_alloc(devm_ti_sci_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);
	handle = ti_sci_get_by_phandle(dev_of_node(dev), property);

	अगर (!IS_ERR(handle)) अणु
		*ptr = handle;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस handle;
पूर्ण
EXPORT_SYMBOL_GPL(devm_ti_sci_get_by_phandle);

/**
 * ti_sci_get_मुक्त_resource() - Get a मुक्त resource from TISCI resource.
 * @res:	Poपूर्णांकer to the TISCI resource
 *
 * Return: resource num अगर all went ok अन्यथा TI_SCI_RESOURCE_शून्य.
 */
u16 ti_sci_get_मुक्त_resource(काष्ठा ti_sci_resource *res)
अणु
	अचिन्हित दीर्घ flags;
	u16 set, मुक्त_bit;

	raw_spin_lock_irqsave(&res->lock, flags);
	क्रम (set = 0; set < res->sets; set++) अणु
		काष्ठा ti_sci_resource_desc *desc = &res->desc[set];
		पूर्णांक res_count = desc->num + desc->num_sec;

		मुक्त_bit = find_first_zero_bit(desc->res_map, res_count);
		अगर (मुक्त_bit != res_count) अणु
			set_bit(मुक्त_bit, desc->res_map);
			raw_spin_unlock_irqrestore(&res->lock, flags);

			अगर (desc->num && मुक्त_bit < desc->num)
				वापस desc->start + मुक्त_bit;
			अन्यथा
				वापस desc->start_sec + मुक्त_bit;
		पूर्ण
	पूर्ण
	raw_spin_unlock_irqrestore(&res->lock, flags);

	वापस TI_SCI_RESOURCE_शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(ti_sci_get_मुक्त_resource);

/**
 * ti_sci_release_resource() - Release a resource from TISCI resource.
 * @res:	Poपूर्णांकer to the TISCI resource
 * @id:		Resource id to be released.
 */
व्योम ti_sci_release_resource(काष्ठा ti_sci_resource *res, u16 id)
अणु
	अचिन्हित दीर्घ flags;
	u16 set;

	raw_spin_lock_irqsave(&res->lock, flags);
	क्रम (set = 0; set < res->sets; set++) अणु
		काष्ठा ti_sci_resource_desc *desc = &res->desc[set];

		अगर (desc->num && desc->start <= id &&
		    (desc->start + desc->num) > id)
			clear_bit(id - desc->start, desc->res_map);
		अन्यथा अगर (desc->num_sec && desc->start_sec <= id &&
			 (desc->start_sec + desc->num_sec) > id)
			clear_bit(id - desc->start_sec, desc->res_map);
	पूर्ण
	raw_spin_unlock_irqrestore(&res->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ti_sci_release_resource);

/**
 * ti_sci_get_num_resources() - Get the number of resources in TISCI resource
 * @res:	Poपूर्णांकer to the TISCI resource
 *
 * Return: Total number of available resources.
 */
u32 ti_sci_get_num_resources(काष्ठा ti_sci_resource *res)
अणु
	u32 set, count = 0;

	क्रम (set = 0; set < res->sets; set++)
		count += res->desc[set].num + res->desc[set].num_sec;

	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(ti_sci_get_num_resources);

/**
 * devm_ti_sci_get_resource_sets() - Get a TISCI resources asचिन्हित to a device
 * @handle:	TISCI handle
 * @dev:	Device poपूर्णांकer to which the resource is asचिन्हित
 * @dev_id:	TISCI device id to which the resource is asचिन्हित
 * @sub_types:	Array of sub_types asचिन्हित corresponding to device
 * @sets:	Number of sub_types
 *
 * Return: Poपूर्णांकer to ti_sci_resource अगर all went well अन्यथा appropriate
 *	   error poपूर्णांकer.
 */
अटल काष्ठा ti_sci_resource *
devm_ti_sci_get_resource_sets(स्थिर काष्ठा ti_sci_handle *handle,
			      काष्ठा device *dev, u32 dev_id, u32 *sub_types,
			      u32 sets)
अणु
	काष्ठा ti_sci_resource *res;
	bool valid_set = false;
	पूर्णांक i, ret, res_count;

	res = devm_kzalloc(dev, माप(*res), GFP_KERNEL);
	अगर (!res)
		वापस ERR_PTR(-ENOMEM);

	res->sets = sets;
	res->desc = devm_kसुस्मृति(dev, res->sets, माप(*res->desc),
				 GFP_KERNEL);
	अगर (!res->desc)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < res->sets; i++) अणु
		ret = handle->ops.rm_core_ops.get_range(handle, dev_id,
							sub_types[i],
							&res->desc[i]);
		अगर (ret) अणु
			dev_dbg(dev, "dev = %d subtype %d not allocated for this host\n",
				dev_id, sub_types[i]);
			स_रखो(&res->desc[i], 0, माप(res->desc[i]));
			जारी;
		पूर्ण

		dev_dbg(dev, "dev/sub_type: %d/%d, start/num: %d/%d | %d/%d\n",
			dev_id, sub_types[i], res->desc[i].start,
			res->desc[i].num, res->desc[i].start_sec,
			res->desc[i].num_sec);

		valid_set = true;
		res_count = res->desc[i].num + res->desc[i].num_sec;
		res->desc[i].res_map =
			devm_kzalloc(dev, BITS_TO_LONGS(res_count) *
				     माप(*res->desc[i].res_map), GFP_KERNEL);
		अगर (!res->desc[i].res_map)
			वापस ERR_PTR(-ENOMEM);
	पूर्ण
	raw_spin_lock_init(&res->lock);

	अगर (valid_set)
		वापस res;

	वापस ERR_PTR(-EINVAL);
पूर्ण

/**
 * devm_ti_sci_get_of_resource() - Get a TISCI resource asचिन्हित to a device
 * @handle:	TISCI handle
 * @dev:	Device poपूर्णांकer to which the resource is asचिन्हित
 * @dev_id:	TISCI device id to which the resource is asचिन्हित
 * @of_prop:	property name by which the resource are represented
 *
 * Return: Poपूर्णांकer to ti_sci_resource अगर all went well अन्यथा appropriate
 *	   error poपूर्णांकer.
 */
काष्ठा ti_sci_resource *
devm_ti_sci_get_of_resource(स्थिर काष्ठा ti_sci_handle *handle,
			    काष्ठा device *dev, u32 dev_id, अक्षर *of_prop)
अणु
	काष्ठा ti_sci_resource *res;
	u32 *sub_types;
	पूर्णांक sets;

	sets = of_property_count_elems_of_size(dev_of_node(dev), of_prop,
					       माप(u32));
	अगर (sets < 0) अणु
		dev_err(dev, "%s resource type ids not available\n", of_prop);
		वापस ERR_PTR(sets);
	पूर्ण

	sub_types = kसुस्मृति(sets, माप(*sub_types), GFP_KERNEL);
	अगर (!sub_types)
		वापस ERR_PTR(-ENOMEM);

	of_property_पढ़ो_u32_array(dev_of_node(dev), of_prop, sub_types, sets);
	res = devm_ti_sci_get_resource_sets(handle, dev, dev_id, sub_types,
					    sets);

	kमुक्त(sub_types);
	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(devm_ti_sci_get_of_resource);

/**
 * devm_ti_sci_get_resource() - Get a resource range asचिन्हित to the device
 * @handle:	TISCI handle
 * @dev:	Device poपूर्णांकer to which the resource is asचिन्हित
 * @dev_id:	TISCI device id to which the resource is asचिन्हित
 * @suub_type:	TISCI resource subytpe representing the resource.
 *
 * Return: Poपूर्णांकer to ti_sci_resource अगर all went well अन्यथा appropriate
 *	   error poपूर्णांकer.
 */
काष्ठा ti_sci_resource *
devm_ti_sci_get_resource(स्थिर काष्ठा ti_sci_handle *handle, काष्ठा device *dev,
			 u32 dev_id, u32 sub_type)
अणु
	वापस devm_ti_sci_get_resource_sets(handle, dev, dev_id, &sub_type, 1);
पूर्ण
EXPORT_SYMBOL_GPL(devm_ti_sci_get_resource);

अटल पूर्णांक tisci_reboot_handler(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ mode,
				व्योम *cmd)
अणु
	काष्ठा ti_sci_info *info = reboot_to_ti_sci_info(nb);
	स्थिर काष्ठा ti_sci_handle *handle = &info->handle;

	ti_sci_cmd_core_reboot(handle);

	/* call fail OR pass, we should not be here in the first place */
	वापस NOTIFY_BAD;
पूर्ण

/* Description क्रम K2G */
अटल स्थिर काष्ठा ti_sci_desc ti_sci_pmmc_k2g_desc = अणु
	.शेष_host_id = 2,
	/* Conservative duration */
	.max_rx_समयout_ms = 1000,
	/* Limited by MBOX_TX_QUEUE_LEN. K2G can handle upto 128 messages! */
	.max_msgs = 20,
	.max_msg_size = 64,
पूर्ण;

/* Description क्रम AM654 */
अटल स्थिर काष्ठा ti_sci_desc ti_sci_pmmc_am654_desc = अणु
	.शेष_host_id = 12,
	/* Conservative duration */
	.max_rx_समयout_ms = 10000,
	/* Limited by MBOX_TX_QUEUE_LEN. K2G can handle upto 128 messages! */
	.max_msgs = 20,
	.max_msg_size = 60,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ti_sci_of_match[] = अणु
	अणु.compatible = "ti,k2g-sci", .data = &ti_sci_pmmc_k2g_descपूर्ण,
	अणु.compatible = "ti,am654-sci", .data = &ti_sci_pmmc_am654_descपूर्ण,
	अणु /* Sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ti_sci_of_match);

अटल पूर्णांक ti_sci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा of_device_id *of_id;
	स्थिर काष्ठा ti_sci_desc *desc;
	काष्ठा ti_sci_xfer *xfer;
	काष्ठा ti_sci_info *info = शून्य;
	काष्ठा ti_sci_xfers_info *minfo;
	काष्ठा mbox_client *cl;
	पूर्णांक ret = -EINVAL;
	पूर्णांक i;
	पूर्णांक reboot = 0;
	u32 h_id;

	of_id = of_match_device(ti_sci_of_match, dev);
	अगर (!of_id) अणु
		dev_err(dev, "OF data missing\n");
		वापस -EINVAL;
	पूर्ण
	desc = of_id->data;

	info = devm_kzalloc(dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->dev = dev;
	info->desc = desc;
	ret = of_property_पढ़ो_u32(dev->of_node, "ti,host-id", &h_id);
	/* अगर the property is not present in DT, use a शेष from desc */
	अगर (ret < 0) अणु
		info->host_id = info->desc->शेष_host_id;
	पूर्ण अन्यथा अणु
		अगर (!h_id) अणु
			dev_warn(dev, "Host ID 0 is reserved for firmware\n");
			info->host_id = info->desc->शेष_host_id;
		पूर्ण अन्यथा अणु
			info->host_id = h_id;
		पूर्ण
	पूर्ण

	reboot = of_property_पढ़ो_bool(dev->of_node,
				       "ti,system-reboot-controller");
	INIT_LIST_HEAD(&info->node);
	minfo = &info->minfo;

	/*
	 * Pre-allocate messages
	 * NEVER allocate more than what we can indicate in hdr.seq
	 * अगर we have data description bug, क्रमce a fix..
	 */
	अगर (WARN_ON(desc->max_msgs >=
		    1 << 8 * माप(((काष्ठा ti_sci_msg_hdr *)0)->seq)))
		वापस -EINVAL;

	minfo->xfer_block = devm_kसुस्मृति(dev,
					 desc->max_msgs,
					 माप(*minfo->xfer_block),
					 GFP_KERNEL);
	अगर (!minfo->xfer_block)
		वापस -ENOMEM;

	minfo->xfer_alloc_table = devm_kसुस्मृति(dev,
					       BITS_TO_LONGS(desc->max_msgs),
					       माप(अचिन्हित दीर्घ),
					       GFP_KERNEL);
	अगर (!minfo->xfer_alloc_table)
		वापस -ENOMEM;
	biपंचांगap_zero(minfo->xfer_alloc_table, desc->max_msgs);

	/* Pre-initialize the buffer poपूर्णांकer to pre-allocated buffers */
	क्रम (i = 0, xfer = minfo->xfer_block; i < desc->max_msgs; i++, xfer++) अणु
		xfer->xfer_buf = devm_kसुस्मृति(dev, 1, desc->max_msg_size,
					      GFP_KERNEL);
		अगर (!xfer->xfer_buf)
			वापस -ENOMEM;

		xfer->tx_message.buf = xfer->xfer_buf;
		init_completion(&xfer->करोne);
	पूर्ण

	ret = ti_sci_debugfs_create(pdev, info);
	अगर (ret)
		dev_warn(dev, "Failed to create debug file\n");

	platक्रमm_set_drvdata(pdev, info);

	cl = &info->cl;
	cl->dev = dev;
	cl->tx_block = false;
	cl->rx_callback = ti_sci_rx_callback;
	cl->knows_txकरोne = true;

	spin_lock_init(&minfo->xfer_lock);
	sema_init(&minfo->sem_xfer_count, desc->max_msgs);

	info->chan_rx = mbox_request_channel_byname(cl, "rx");
	अगर (IS_ERR(info->chan_rx)) अणु
		ret = PTR_ERR(info->chan_rx);
		जाओ out;
	पूर्ण

	info->chan_tx = mbox_request_channel_byname(cl, "tx");
	अगर (IS_ERR(info->chan_tx)) अणु
		ret = PTR_ERR(info->chan_tx);
		जाओ out;
	पूर्ण
	ret = ti_sci_cmd_get_revision(info);
	अगर (ret) अणु
		dev_err(dev, "Unable to communicate with TISCI(%d)\n", ret);
		जाओ out;
	पूर्ण

	ti_sci_setup_ops(info);

	अगर (reboot) अणु
		info->nb.notअगरier_call = tisci_reboot_handler;
		info->nb.priority = 128;

		ret = रेजिस्टर_restart_handler(&info->nb);
		अगर (ret) अणु
			dev_err(dev, "reboot registration fail(%d)\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	dev_info(dev, "ABI: %d.%d (firmware rev 0x%04x '%s')\n",
		 info->handle.version.abi_major, info->handle.version.abi_minor,
		 info->handle.version.firmware_revision,
		 info->handle.version.firmware_description);

	mutex_lock(&ti_sci_list_mutex);
	list_add_tail(&info->node, &ti_sci_list);
	mutex_unlock(&ti_sci_list_mutex);

	वापस of_platक्रमm_populate(dev->of_node, शून्य, शून्य, dev);
out:
	अगर (!IS_ERR(info->chan_tx))
		mbox_मुक्त_channel(info->chan_tx);
	अगर (!IS_ERR(info->chan_rx))
		mbox_मुक्त_channel(info->chan_rx);
	debugfs_हटाओ(info->d);
	वापस ret;
पूर्ण

अटल पूर्णांक ti_sci_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ti_sci_info *info;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret = 0;

	of_platक्रमm_depopulate(dev);

	info = platक्रमm_get_drvdata(pdev);

	अगर (info->nb.notअगरier_call)
		unरेजिस्टर_restart_handler(&info->nb);

	mutex_lock(&ti_sci_list_mutex);
	अगर (info->users)
		ret = -EBUSY;
	अन्यथा
		list_del(&info->node);
	mutex_unlock(&ti_sci_list_mutex);

	अगर (!ret) अणु
		ti_sci_debugfs_destroy(pdev, info);

		/* Safe to मुक्त channels since no more users */
		mbox_मुक्त_channel(info->chan_tx);
		mbox_मुक्त_channel(info->chan_rx);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver ti_sci_driver = अणु
	.probe = ti_sci_probe,
	.हटाओ = ti_sci_हटाओ,
	.driver = अणु
		   .name = "ti-sci",
		   .of_match_table = of_match_ptr(ti_sci_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ti_sci_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("TI System Control Interface(SCI) driver");
MODULE_AUTHOR("Nishanth Menon");
MODULE_ALIAS("platform:ti-sci");
