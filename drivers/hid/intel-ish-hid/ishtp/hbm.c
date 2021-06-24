<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ISHTP bus layer messages handling
 *
 * Copyright (c) 2003-2016, Intel Corporation.
 */

#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/spinlock.h>
#समावेश "ishtp-dev.h"
#समावेश "hbm.h"
#समावेश "client.h"

/**
 * ishtp_hbm_fw_cl_allocate() - Allocate FW clients
 * @dev: ISHTP device instance
 *
 * Allocates storage क्रम fw clients
 */
अटल व्योम ishtp_hbm_fw_cl_allocate(काष्ठा ishtp_device *dev)
अणु
	काष्ठा ishtp_fw_client *clients;
	पूर्णांक b;

	/* count how many ISH clients we have */
	क्रम_each_set_bit(b, dev->fw_clients_map, ISHTP_CLIENTS_MAX)
		dev->fw_clients_num++;

	अगर (dev->fw_clients_num <= 0)
		वापस;

	/* allocate storage क्रम fw clients representation */
	clients = kसुस्मृति(dev->fw_clients_num, माप(काष्ठा ishtp_fw_client),
			  GFP_KERNEL);
	अगर (!clients) अणु
		dev->dev_state = ISHTP_DEV_RESETTING;
		ish_hw_reset(dev);
		वापस;
	पूर्ण
	dev->fw_clients = clients;
पूर्ण

/**
 * ishtp_hbm_cl_hdr() - स्थिरruct client hbm header
 * @cl: client
 * @hbm_cmd: host bus message command
 * @buf: buffer क्रम cl header
 * @len: buffer length
 *
 * Initialize HBM buffer
 */
अटल अंतरभूत व्योम ishtp_hbm_cl_hdr(काष्ठा ishtp_cl *cl, uपूर्णांक8_t hbm_cmd,
	व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा ishtp_hbm_cl_cmd *cmd = buf;

	स_रखो(cmd, 0, len);

	cmd->hbm_cmd = hbm_cmd;
	cmd->host_addr = cl->host_client_id;
	cmd->fw_addr = cl->fw_client_id;
पूर्ण

/**
 * ishtp_hbm_cl_addr_equal() - Compare client address
 * @cl: client
 * @buf: Client command buffer
 *
 * Compare client address with the address in command buffer
 *
 * Return: True अगर they have the same address
 */
अटल अंतरभूत bool ishtp_hbm_cl_addr_equal(काष्ठा ishtp_cl *cl, व्योम *buf)
अणु
	काष्ठा ishtp_hbm_cl_cmd *cmd = buf;

	वापस cl->host_client_id == cmd->host_addr &&
		cl->fw_client_id == cmd->fw_addr;
पूर्ण

/**
 * ishtp_hbm_start_रुको() - Wait क्रम HBM start message
 * @dev: ISHTP device instance
 *
 * Wait क्रम HBM start message from firmware
 *
 * Return: 0 अगर HBM start is/was received अन्यथा समयout error
 */
पूर्णांक ishtp_hbm_start_रुको(काष्ठा ishtp_device *dev)
अणु
	पूर्णांक ret;

	अगर (dev->hbm_state > ISHTP_HBM_START)
		वापस 0;

	dev_dbg(dev->devc, "Going to wait for ishtp start. hbm_state=%08X\n",
		dev->hbm_state);
	ret = रुको_event_पूर्णांकerruptible_समयout(dev->रुको_hbm_recvd_msg,
					dev->hbm_state >= ISHTP_HBM_STARTED,
					(ISHTP_INTEROP_TIMEOUT * HZ));

	dev_dbg(dev->devc,
		"Woke up from waiting for ishtp start. hbm_state=%08X\n",
		dev->hbm_state);

	अगर (ret <= 0 && (dev->hbm_state <= ISHTP_HBM_START)) अणु
		dev->hbm_state = ISHTP_HBM_IDLE;
		dev_err(dev->devc,
		"waiting for ishtp start failed. ret=%d hbm_state=%08X\n",
			ret, dev->hbm_state);
		वापस -ETIMEDOUT;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ishtp_hbm_start_req() - Send HBM start message
 * @dev: ISHTP device instance
 *
 * Send HBM start message to firmware
 *
 * Return: 0 अगर success अन्यथा error code
 */
पूर्णांक ishtp_hbm_start_req(काष्ठा ishtp_device *dev)
अणु
	काष्ठा ishtp_msg_hdr hdr;
	काष्ठा hbm_host_version_request start_req = अणु 0 पूर्ण;

	ishtp_hbm_hdr(&hdr, माप(start_req));

	/* host start message */
	start_req.hbm_cmd = HOST_START_REQ_CMD;
	start_req.host_version.major_version = HBM_MAJOR_VERSION;
	start_req.host_version.minor_version = HBM_MINOR_VERSION;

	/*
	 * (!) Response to HBM start may be so quick that this thपढ़ो would get
	 * preempted BEFORE managing to set hbm_state = ISHTP_HBM_START.
	 * So set it at first, change back to ISHTP_HBM_IDLE upon failure
	 */
	dev->hbm_state = ISHTP_HBM_START;
	अगर (ishtp_ग_लिखो_message(dev, &hdr, &start_req)) अणु
		dev_err(dev->devc, "version message send failed\n");
		dev->dev_state = ISHTP_DEV_RESETTING;
		dev->hbm_state = ISHTP_HBM_IDLE;
		ish_hw_reset(dev);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ishtp_hbm_क्रमागत_clients_req() - Send client क्रमागत req
 * @dev: ISHTP device instance
 *
 * Send क्रमागतeration client request message
 *
 * Return: 0 अगर success अन्यथा error code
 */
व्योम ishtp_hbm_क्रमागत_clients_req(काष्ठा ishtp_device *dev)
अणु
	काष्ठा ishtp_msg_hdr hdr;
	काष्ठा hbm_host_क्रमागत_request क्रमागत_req = अणु 0 पूर्ण;

	/* क्रमागतerate clients */
	ishtp_hbm_hdr(&hdr, माप(क्रमागत_req));
	क्रमागत_req.hbm_cmd = HOST_ENUM_REQ_CMD;

	अगर (ishtp_ग_लिखो_message(dev, &hdr, &क्रमागत_req)) अणु
		dev->dev_state = ISHTP_DEV_RESETTING;
		dev_err(dev->devc, "enumeration request send failed\n");
		ish_hw_reset(dev);
	पूर्ण
	dev->hbm_state = ISHTP_HBM_ENUM_CLIENTS;
पूर्ण

/**
 * ishtp_hbm_prop_req() - Request property
 * @dev: ISHTP device instance
 *
 * Request property क्रम a single client
 *
 * Return: 0 अगर success अन्यथा error code
 */
अटल पूर्णांक ishtp_hbm_prop_req(काष्ठा ishtp_device *dev)
अणु
	काष्ठा ishtp_msg_hdr hdr;
	काष्ठा hbm_props_request prop_req = अणु 0 पूर्ण;
	अचिन्हित दीर्घ next_client_index;
	uपूर्णांक8_t client_num;

	client_num = dev->fw_client_presentation_num;

	next_client_index = find_next_bit(dev->fw_clients_map,
		ISHTP_CLIENTS_MAX, dev->fw_client_index);

	/* We got all client properties */
	अगर (next_client_index == ISHTP_CLIENTS_MAX) अणु
		dev->hbm_state = ISHTP_HBM_WORKING;
		dev->dev_state = ISHTP_DEV_ENABLED;

		क्रम (dev->fw_client_presentation_num = 1;
			dev->fw_client_presentation_num < client_num + 1;
				++dev->fw_client_presentation_num)
			/* Add new client device */
			ishtp_bus_new_client(dev);
		वापस 0;
	पूर्ण

	dev->fw_clients[client_num].client_id = next_client_index;

	ishtp_hbm_hdr(&hdr, माप(prop_req));

	prop_req.hbm_cmd = HOST_CLIENT_PROPERTIES_REQ_CMD;
	prop_req.address = next_client_index;

	अगर (ishtp_ग_लिखो_message(dev, &hdr, &prop_req)) अणु
		dev->dev_state = ISHTP_DEV_RESETTING;
		dev_err(dev->devc, "properties request send failed\n");
		ish_hw_reset(dev);
		वापस -EIO;
	पूर्ण

	dev->fw_client_index = next_client_index;

	वापस 0;
पूर्ण

/**
 * ishtp_hbm_stop_req() - Send HBM stop
 * @dev: ISHTP device instance
 *
 * Send stop request message
 */
अटल व्योम ishtp_hbm_stop_req(काष्ठा ishtp_device *dev)
अणु
	काष्ठा ishtp_msg_hdr hdr;
	काष्ठा hbm_host_stop_request stop_req = अणु 0 पूर्ण ;

	ishtp_hbm_hdr(&hdr, माप(stop_req));

	stop_req.hbm_cmd = HOST_STOP_REQ_CMD;
	stop_req.reason = DRIVER_STOP_REQUEST;

	ishtp_ग_लिखो_message(dev, &hdr, &stop_req);
पूर्ण

/**
 * ishtp_hbm_cl_flow_control_req() - Send flow control request
 * @dev: ISHTP device instance
 * @cl: ISHTP client instance
 *
 * Send flow control request
 *
 * Return: 0 अगर success अन्यथा error code
 */
पूर्णांक ishtp_hbm_cl_flow_control_req(काष्ठा ishtp_device *dev,
				  काष्ठा ishtp_cl *cl)
अणु
	काष्ठा ishtp_msg_hdr hdr;
	काष्ठा hbm_flow_control flow_ctrl;
	स्थिर माप_प्रकार len = माप(flow_ctrl);
	पूर्णांक	rv;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&cl->fc_spinlock, flags);

	ishtp_hbm_hdr(&hdr, len);
	ishtp_hbm_cl_hdr(cl, ISHTP_FLOW_CONTROL_CMD, &flow_ctrl, len);

	/*
	 * Sync possible race when RB recycle and packet receive paths
	 * both try to send an out FC
	 */
	अगर (cl->out_flow_ctrl_creds) अणु
		spin_unlock_irqrestore(&cl->fc_spinlock, flags);
		वापस	0;
	पूर्ण

	cl->recv_msg_num_frags = 0;

	rv = ishtp_ग_लिखो_message(dev, &hdr, &flow_ctrl);
	अगर (!rv) अणु
		++cl->out_flow_ctrl_creds;
		++cl->out_flow_ctrl_cnt;
		cl->ts_out_fc = kसमय_get();
		अगर (cl->ts_rx) अणु
			kसमय_प्रकार ts_dअगरf = kसमय_sub(cl->ts_out_fc, cl->ts_rx);
			अगर (kसमय_after(ts_dअगरf, cl->ts_max_fc_delay))
				cl->ts_max_fc_delay = ts_dअगरf;
		पूर्ण
	पूर्ण अन्यथा अणु
		++cl->err_send_fc;
	पूर्ण

	spin_unlock_irqrestore(&cl->fc_spinlock, flags);
	वापस	rv;
पूर्ण

/**
 * ishtp_hbm_cl_disconnect_req() - Send disconnect request
 * @dev: ISHTP device instance
 * @cl: ISHTP client instance
 *
 * Send disconnect message to fw
 *
 * Return: 0 अगर success अन्यथा error code
 */
पूर्णांक ishtp_hbm_cl_disconnect_req(काष्ठा ishtp_device *dev, काष्ठा ishtp_cl *cl)
अणु
	काष्ठा ishtp_msg_hdr hdr;
	काष्ठा hbm_client_connect_request disconn_req;
	स्थिर माप_प्रकार len = माप(disconn_req);

	ishtp_hbm_hdr(&hdr, len);
	ishtp_hbm_cl_hdr(cl, CLIENT_DISCONNECT_REQ_CMD, &disconn_req, len);

	वापस ishtp_ग_लिखो_message(dev, &hdr, &disconn_req);
पूर्ण

/**
 * ishtp_hbm_cl_disconnect_res() - Get disconnect response
 * @dev: ISHTP device instance
 * @rs: Response message
 *
 * Received disconnect response from fw
 */
अटल व्योम ishtp_hbm_cl_disconnect_res(काष्ठा ishtp_device *dev,
	काष्ठा hbm_client_connect_response *rs)
अणु
	काष्ठा ishtp_cl *cl = शून्य;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&dev->cl_list_lock, flags);
	list_क्रम_each_entry(cl, &dev->cl_list, link) अणु
		अगर (!rs->status && ishtp_hbm_cl_addr_equal(cl, rs)) अणु
			cl->state = ISHTP_CL_DISCONNECTED;
			wake_up_पूर्णांकerruptible(&cl->रुको_ctrl_res);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dev->cl_list_lock, flags);
पूर्ण

/**
 * ishtp_hbm_cl_connect_req() - Send connect request
 * @dev: ISHTP device instance
 * @cl: client device instance
 *
 * Send connection request to specअगरic fw client
 *
 * Return: 0 अगर success अन्यथा error code
 */
पूर्णांक ishtp_hbm_cl_connect_req(काष्ठा ishtp_device *dev, काष्ठा ishtp_cl *cl)
अणु
	काष्ठा ishtp_msg_hdr hdr;
	काष्ठा hbm_client_connect_request conn_req;
	स्थिर माप_प्रकार len = माप(conn_req);

	ishtp_hbm_hdr(&hdr, len);
	ishtp_hbm_cl_hdr(cl, CLIENT_CONNECT_REQ_CMD, &conn_req, len);

	वापस ishtp_ग_लिखो_message(dev, &hdr, &conn_req);
पूर्ण

/**
 * ishtp_hbm_cl_connect_res() - Get connect response
 * @dev: ISHTP device instance
 * @rs: Response message
 *
 * Received connect response from fw
 */
अटल व्योम ishtp_hbm_cl_connect_res(काष्ठा ishtp_device *dev,
	काष्ठा hbm_client_connect_response *rs)
अणु
	काष्ठा ishtp_cl *cl = शून्य;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&dev->cl_list_lock, flags);
	list_क्रम_each_entry(cl, &dev->cl_list, link) अणु
		अगर (ishtp_hbm_cl_addr_equal(cl, rs)) अणु
			अगर (!rs->status) अणु
				cl->state = ISHTP_CL_CONNECTED;
				cl->status = 0;
			पूर्ण अन्यथा अणु
				cl->state = ISHTP_CL_DISCONNECTED;
				cl->status = -ENODEV;
			पूर्ण
			wake_up_पूर्णांकerruptible(&cl->रुको_ctrl_res);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dev->cl_list_lock, flags);
पूर्ण

/**
 * ishtp_client_disconnect_request() - Receive disconnect request
 * @dev: ISHTP device instance
 * @disconnect_req: disconnect request काष्ठाure
 *
 * Disconnect request bus message from the fw. Send disconnect response.
 */
अटल व्योम ishtp_hbm_fw_disconnect_req(काष्ठा ishtp_device *dev,
	काष्ठा hbm_client_connect_request *disconnect_req)
अणु
	काष्ठा ishtp_cl *cl;
	स्थिर माप_प्रकार len = माप(काष्ठा hbm_client_connect_response);
	अचिन्हित दीर्घ	flags;
	काष्ठा ishtp_msg_hdr hdr;
	अचिन्हित अक्षर data[4];	/* All HBM messages are 4 bytes */

	spin_lock_irqsave(&dev->cl_list_lock, flags);
	list_क्रम_each_entry(cl, &dev->cl_list, link) अणु
		अगर (ishtp_hbm_cl_addr_equal(cl, disconnect_req)) अणु
			cl->state = ISHTP_CL_DISCONNECTED;

			/* send disconnect response */
			ishtp_hbm_hdr(&hdr, len);
			ishtp_hbm_cl_hdr(cl, CLIENT_DISCONNECT_RES_CMD, data,
				len);
			ishtp_ग_लिखो_message(dev, &hdr, data);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dev->cl_list_lock, flags);
पूर्ण

/**
 * ishtp_hbm_dma_xfer_ack(() - Receive transfer ACK
 * @dev: ISHTP device instance
 * @dma_xfer: HBM transfer message
 *
 * Receive ack क्रम ISHTP-over-DMA client message
 */
अटल व्योम ishtp_hbm_dma_xfer_ack(काष्ठा ishtp_device *dev,
				   काष्ठा dma_xfer_hbm *dma_xfer)
अणु
	व्योम	*msg;
	uपूर्णांक64_t	offs;
	काष्ठा ishtp_msg_hdr	*ishtp_hdr =
		(काष्ठा ishtp_msg_hdr *)&dev->ishtp_msg_hdr;
	अचिन्हित पूर्णांक	msg_offs;
	काष्ठा ishtp_cl *cl;

	क्रम (msg_offs = 0; msg_offs < ishtp_hdr->length;
		msg_offs += माप(काष्ठा dma_xfer_hbm)) अणु
		offs = dma_xfer->msg_addr - dev->ishtp_host_dma_tx_buf_phys;
		अगर (offs > dev->ishtp_host_dma_tx_buf_size) अणु
			dev_err(dev->devc, "Bad DMA Tx ack message address\n");
			वापस;
		पूर्ण
		अगर (dma_xfer->msg_length >
				dev->ishtp_host_dma_tx_buf_size - offs) अणु
			dev_err(dev->devc, "Bad DMA Tx ack message size\n");
			वापस;
		पूर्ण

		/* logical address of the acked mem */
		msg = (अचिन्हित अक्षर *)dev->ishtp_host_dma_tx_buf + offs;
		ishtp_cl_release_dma_acked_mem(dev, msg, dma_xfer->msg_length);

		list_क्रम_each_entry(cl, &dev->cl_list, link) अणु
			अगर (cl->fw_client_id == dma_xfer->fw_client_id &&
			    cl->host_client_id == dma_xfer->host_client_id)
				/*
				 * in हाल that a single ack may be sent
				 * over several dma transfers, and the last msg
				 * addr was inside the acked memory, but not in
				 * its start
				 */
				अगर (cl->last_dma_addr >=
							(अचिन्हित अक्षर *)msg &&
						cl->last_dma_addr <
						(अचिन्हित अक्षर *)msg +
						dma_xfer->msg_length) अणु
					cl->last_dma_acked = 1;

					अगर (!list_empty(&cl->tx_list.list) &&
						cl->ishtp_flow_ctrl_creds) अणु
						/*
						 * start sending the first msg
						 */
						ishtp_cl_send_msg(dev, cl);
					पूर्ण
				पूर्ण
		पूर्ण
		++dma_xfer;
	पूर्ण
पूर्ण

/**
 * ishtp_hbm_dma_xfer() - Receive DMA transfer message
 * @dev: ISHTP device instance
 * @dma_xfer: HBM transfer message
 *
 * Receive ISHTP-over-DMA client message
 */
अटल व्योम ishtp_hbm_dma_xfer(काष्ठा ishtp_device *dev,
			       काष्ठा dma_xfer_hbm *dma_xfer)
अणु
	व्योम	*msg;
	uपूर्णांक64_t	offs;
	काष्ठा ishtp_msg_hdr	hdr;
	काष्ठा ishtp_msg_hdr	*ishtp_hdr =
		(काष्ठा ishtp_msg_hdr *) &dev->ishtp_msg_hdr;
	काष्ठा dma_xfer_hbm	*prm = dma_xfer;
	अचिन्हित पूर्णांक	msg_offs;

	क्रम (msg_offs = 0; msg_offs < ishtp_hdr->length;
		msg_offs += माप(काष्ठा dma_xfer_hbm)) अणु

		offs = dma_xfer->msg_addr - dev->ishtp_host_dma_rx_buf_phys;
		अगर (offs > dev->ishtp_host_dma_rx_buf_size) अणु
			dev_err(dev->devc, "Bad DMA Rx message address\n");
			वापस;
		पूर्ण
		अगर (dma_xfer->msg_length >
				dev->ishtp_host_dma_rx_buf_size - offs) अणु
			dev_err(dev->devc, "Bad DMA Rx message size\n");
			वापस;
		पूर्ण
		msg = dev->ishtp_host_dma_rx_buf + offs;
		recv_ishtp_cl_msg_dma(dev, msg, dma_xfer);
		dma_xfer->hbm = DMA_XFER_ACK;	/* Prepare क्रम response */
		++dma_xfer;
	पूर्ण

	/* Send DMA_XFER_ACK [...] */
	ishtp_hbm_hdr(&hdr, ishtp_hdr->length);
	ishtp_ग_लिखो_message(dev, &hdr, (अचिन्हित अक्षर *)prm);
पूर्ण

/**
 * ishtp_hbm_dispatch() - HBM dispatch function
 * @dev: ISHTP device instance
 * @hdr: bus message
 *
 * Bottom half पढ़ो routine after ISR to handle the पढ़ो bus message cmd
 * processing
 */
व्योम ishtp_hbm_dispatch(काष्ठा ishtp_device *dev,
			काष्ठा ishtp_bus_message *hdr)
अणु
	काष्ठा ishtp_bus_message *ishtp_msg;
	काष्ठा ishtp_fw_client *fw_client;
	काष्ठा hbm_host_version_response *version_res;
	काष्ठा hbm_client_connect_response *connect_res;
	काष्ठा hbm_client_connect_response *disconnect_res;
	काष्ठा hbm_client_connect_request *disconnect_req;
	काष्ठा hbm_props_response *props_res;
	काष्ठा hbm_host_क्रमागत_response *क्रमागत_res;
	काष्ठा ishtp_msg_hdr ishtp_hdr;
	काष्ठा dma_alloc_notअगरy	dma_alloc_notअगरy;
	काष्ठा dma_xfer_hbm	*dma_xfer;

	ishtp_msg = hdr;

	चयन (ishtp_msg->hbm_cmd) अणु
	हाल HOST_START_RES_CMD:
		version_res = (काष्ठा hbm_host_version_response *)ishtp_msg;
		अगर (!version_res->host_version_supported) अणु
			dev->version = version_res->fw_max_version;

			dev->hbm_state = ISHTP_HBM_STOPPED;
			ishtp_hbm_stop_req(dev);
			वापस;
		पूर्ण

		dev->version.major_version = HBM_MAJOR_VERSION;
		dev->version.minor_version = HBM_MINOR_VERSION;
		अगर (dev->dev_state == ISHTP_DEV_INIT_CLIENTS &&
				dev->hbm_state == ISHTP_HBM_START) अणु
			dev->hbm_state = ISHTP_HBM_STARTED;
			ishtp_hbm_क्रमागत_clients_req(dev);
		पूर्ण अन्यथा अणु
			dev_err(dev->devc,
				"reset: wrong host start response\n");
			/* BUG: why करो we arrive here? */
			ish_hw_reset(dev);
			वापस;
		पूर्ण

		wake_up_पूर्णांकerruptible(&dev->रुको_hbm_recvd_msg);
		अवरोध;

	हाल CLIENT_CONNECT_RES_CMD:
		connect_res = (काष्ठा hbm_client_connect_response *)ishtp_msg;
		ishtp_hbm_cl_connect_res(dev, connect_res);
		अवरोध;

	हाल CLIENT_DISCONNECT_RES_CMD:
		disconnect_res =
			(काष्ठा hbm_client_connect_response *)ishtp_msg;
		ishtp_hbm_cl_disconnect_res(dev, disconnect_res);
		अवरोध;

	हाल HOST_CLIENT_PROPERTIES_RES_CMD:
		props_res = (काष्ठा hbm_props_response *)ishtp_msg;
		fw_client = &dev->fw_clients[dev->fw_client_presentation_num];

		अगर (props_res->status || !dev->fw_clients) अणु
			dev_err(dev->devc,
			"reset: properties response hbm wrong status\n");
			ish_hw_reset(dev);
			वापस;
		पूर्ण

		अगर (fw_client->client_id != props_res->address) अणु
			dev_err(dev->devc,
				"reset: host properties response address mismatch [%02X %02X]\n",
				fw_client->client_id, props_res->address);
			ish_hw_reset(dev);
			वापस;
		पूर्ण

		अगर (dev->dev_state != ISHTP_DEV_INIT_CLIENTS ||
			dev->hbm_state != ISHTP_HBM_CLIENT_PROPERTIES) अणु
			dev_err(dev->devc,
				"reset: unexpected properties response\n");
			ish_hw_reset(dev);
			वापस;
		पूर्ण

		fw_client->props = props_res->client_properties;
		dev->fw_client_index++;
		dev->fw_client_presentation_num++;

		/* request property क्रम the next client */
		ishtp_hbm_prop_req(dev);

		अगर (dev->dev_state != ISHTP_DEV_ENABLED)
			अवरोध;

		अगर (!ishtp_use_dma_transfer())
			अवरोध;

		dev_dbg(dev->devc, "Requesting to use DMA\n");
		ishtp_cl_alloc_dma_buf(dev);
		अगर (dev->ishtp_host_dma_rx_buf) अणु
			स्थिर माप_प्रकार len = माप(dma_alloc_notअगरy);

			स_रखो(&dma_alloc_notअगरy, 0, माप(dma_alloc_notअगरy));
			dma_alloc_notअगरy.hbm = DMA_BUFFER_ALLOC_NOTIFY;
			dma_alloc_notअगरy.buf_size =
					dev->ishtp_host_dma_rx_buf_size;
			dma_alloc_notअगरy.buf_address =
					dev->ishtp_host_dma_rx_buf_phys;
			ishtp_hbm_hdr(&ishtp_hdr, len);
			ishtp_ग_लिखो_message(dev, &ishtp_hdr,
				(अचिन्हित अक्षर *)&dma_alloc_notअगरy);
		पूर्ण

		अवरोध;

	हाल HOST_ENUM_RES_CMD:
		क्रमागत_res = (काष्ठा hbm_host_क्रमागत_response *) ishtp_msg;
		स_नकल(dev->fw_clients_map, क्रमागत_res->valid_addresses, 32);
		अगर (dev->dev_state == ISHTP_DEV_INIT_CLIENTS &&
			dev->hbm_state == ISHTP_HBM_ENUM_CLIENTS) अणु
			dev->fw_client_presentation_num = 0;
			dev->fw_client_index = 0;

			ishtp_hbm_fw_cl_allocate(dev);
			dev->hbm_state = ISHTP_HBM_CLIENT_PROPERTIES;

			/* first property request */
			ishtp_hbm_prop_req(dev);
		पूर्ण अन्यथा अणु
			dev_err(dev->devc,
			      "reset: unexpected enumeration response hbm\n");
			ish_hw_reset(dev);
			वापस;
		पूर्ण
		अवरोध;

	हाल HOST_STOP_RES_CMD:
		अगर (dev->hbm_state != ISHTP_HBM_STOPPED)
			dev_err(dev->devc, "unexpected stop response\n");

		dev->dev_state = ISHTP_DEV_DISABLED;
		dev_info(dev->devc, "reset: FW stop response\n");
		ish_hw_reset(dev);
		अवरोध;

	हाल CLIENT_DISCONNECT_REQ_CMD:
		/* search क्रम client */
		disconnect_req =
			(काष्ठा hbm_client_connect_request *)ishtp_msg;
		ishtp_hbm_fw_disconnect_req(dev, disconnect_req);
		अवरोध;

	हाल FW_STOP_REQ_CMD:
		dev->hbm_state = ISHTP_HBM_STOPPED;
		अवरोध;

	हाल DMA_BUFFER_ALLOC_RESPONSE:
		dev->ishtp_host_dma_enabled = 1;
		अवरोध;

	हाल DMA_XFER:
		dma_xfer = (काष्ठा dma_xfer_hbm *)ishtp_msg;
		अगर (!dev->ishtp_host_dma_enabled) अणु
			dev_err(dev->devc,
				"DMA XFER requested but DMA is not enabled\n");
			अवरोध;
		पूर्ण
		ishtp_hbm_dma_xfer(dev, dma_xfer);
		अवरोध;

	हाल DMA_XFER_ACK:
		dma_xfer = (काष्ठा dma_xfer_hbm *)ishtp_msg;
		अगर (!dev->ishtp_host_dma_enabled ||
		    !dev->ishtp_host_dma_tx_buf) अणु
			dev_err(dev->devc,
				"DMA XFER acked but DMA Tx is not enabled\n");
			अवरोध;
		पूर्ण
		ishtp_hbm_dma_xfer_ack(dev, dma_xfer);
		अवरोध;

	शेष:
		dev_err(dev->devc, "unknown HBM: %u\n",
			(अचिन्हित पूर्णांक)ishtp_msg->hbm_cmd);

		अवरोध;
	पूर्ण
पूर्ण

/**
 * bh_hbm_work_fn() - HBM work function
 * @work: work काष्ठा
 *
 * Bottom half processing work function (instead of thपढ़ो handler)
 * क्रम processing hbm messages
 */
व्योम	bh_hbm_work_fn(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ	flags;
	काष्ठा ishtp_device	*dev;
	अचिन्हित अक्षर	hbm[IPC_PAYLOAD_SIZE];

	dev = container_of(work, काष्ठा ishtp_device, bh_hbm_work);
	spin_lock_irqsave(&dev->rd_msg_spinlock, flags);
	अगर (dev->rd_msg_fअगरo_head != dev->rd_msg_fअगरo_tail) अणु
		स_नकल(hbm, dev->rd_msg_fअगरo + dev->rd_msg_fअगरo_head,
			IPC_PAYLOAD_SIZE);
		dev->rd_msg_fअगरo_head =
			(dev->rd_msg_fअगरo_head + IPC_PAYLOAD_SIZE) %
			(RD_INT_FIFO_SIZE * IPC_PAYLOAD_SIZE);
		spin_unlock_irqrestore(&dev->rd_msg_spinlock, flags);
		ishtp_hbm_dispatch(dev, (काष्ठा ishtp_bus_message *)hbm);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&dev->rd_msg_spinlock, flags);
	पूर्ण
पूर्ण

/**
 * recv_hbm() - Receive HBM message
 * @dev: ISHTP device instance
 * @ishtp_hdr: received bus message
 *
 * Receive and process ISHTP bus messages in ISR context. This will schedule
 * work function to process message
 */
व्योम	recv_hbm(काष्ठा ishtp_device *dev, काष्ठा ishtp_msg_hdr *ishtp_hdr)
अणु
	uपूर्णांक8_t	rd_msg_buf[ISHTP_RD_MSG_BUF_SIZE];
	काष्ठा ishtp_bus_message	*ishtp_msg =
		(काष्ठा ishtp_bus_message *)rd_msg_buf;
	अचिन्हित दीर्घ	flags;

	dev->ops->ishtp_पढ़ो(dev, rd_msg_buf, ishtp_hdr->length);

	/* Flow control - handle in place */
	अगर (ishtp_msg->hbm_cmd == ISHTP_FLOW_CONTROL_CMD) अणु
		काष्ठा hbm_flow_control *flow_control =
			(काष्ठा hbm_flow_control *)ishtp_msg;
		काष्ठा ishtp_cl *cl = शून्य;
		अचिन्हित दीर्घ	flags, tx_flags;

		spin_lock_irqsave(&dev->cl_list_lock, flags);
		list_क्रम_each_entry(cl, &dev->cl_list, link) अणु
			अगर (cl->host_client_id == flow_control->host_addr &&
					cl->fw_client_id ==
					flow_control->fw_addr) अणु
				/*
				 * NOTE: It's valid only क्रम counting
				 * flow-control implementation to receive a
				 * FC in the middle of sending. Meanजबतक not
				 * supported
				 */
				अगर (cl->ishtp_flow_ctrl_creds)
					dev_err(dev->devc,
					 "recv extra FC from FW client %u (host client %u) (FC count was %d)\n",
					 (अचिन्हित पूर्णांक)cl->fw_client_id,
					 (अचिन्हित पूर्णांक)cl->host_client_id,
					 cl->ishtp_flow_ctrl_creds);
				अन्यथा अणु
					++cl->ishtp_flow_ctrl_creds;
					++cl->ishtp_flow_ctrl_cnt;
					cl->last_ipc_acked = 1;
					spin_lock_irqsave(
							&cl->tx_list_spinlock,
							tx_flags);
					अगर (!list_empty(&cl->tx_list.list)) अणु
						/*
						 * start sending the first msg
						 *	= the callback function
						 */
						spin_unlock_irqrestore(
							&cl->tx_list_spinlock,
							tx_flags);
						ishtp_cl_send_msg(dev, cl);
					पूर्ण अन्यथा अणु
						spin_unlock_irqrestore(
							&cl->tx_list_spinlock,
							tx_flags);
					पूर्ण
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&dev->cl_list_lock, flags);
		जाओ	eoi;
	पूर्ण

	/*
	 * Some messages that are safe क्रम ISR processing and important
	 * to be करोne "quickly" and in-order, go here
	 */
	अगर (ishtp_msg->hbm_cmd == CLIENT_CONNECT_RES_CMD ||
			ishtp_msg->hbm_cmd == CLIENT_DISCONNECT_RES_CMD ||
			ishtp_msg->hbm_cmd == CLIENT_DISCONNECT_REQ_CMD ||
			ishtp_msg->hbm_cmd == DMA_XFER) अणु
		ishtp_hbm_dispatch(dev, ishtp_msg);
		जाओ	eoi;
	पूर्ण

	/*
	 * All other HBMs go here.
	 * We schedule HBMs क्रम processing serially by using प्रणाली wq,
	 * possibly there will be multiple HBMs scheduled at the same समय.
	 */
	spin_lock_irqsave(&dev->rd_msg_spinlock, flags);
	अगर ((dev->rd_msg_fअगरo_tail + IPC_PAYLOAD_SIZE) %
			(RD_INT_FIFO_SIZE * IPC_PAYLOAD_SIZE) ==
			dev->rd_msg_fअगरo_head) अणु
		spin_unlock_irqrestore(&dev->rd_msg_spinlock, flags);
		dev_err(dev->devc, "BH buffer overflow, dropping HBM %u\n",
			(अचिन्हित पूर्णांक)ishtp_msg->hbm_cmd);
		जाओ	eoi;
	पूर्ण
	स_नकल(dev->rd_msg_fअगरo + dev->rd_msg_fअगरo_tail, ishtp_msg,
		ishtp_hdr->length);
	dev->rd_msg_fअगरo_tail = (dev->rd_msg_fअगरo_tail + IPC_PAYLOAD_SIZE) %
		(RD_INT_FIFO_SIZE * IPC_PAYLOAD_SIZE);
	spin_unlock_irqrestore(&dev->rd_msg_spinlock, flags);
	schedule_work(&dev->bh_hbm_work);
eoi:
	वापस;
पूर्ण

/**
 * recv_fixed_cl_msg() - Receive fixed client message
 * @dev: ISHTP device instance
 * @ishtp_hdr: received bus message
 *
 * Receive and process ISHTP fixed client messages (address == 0)
 * in ISR context
 */
व्योम recv_fixed_cl_msg(काष्ठा ishtp_device *dev,
	काष्ठा ishtp_msg_hdr *ishtp_hdr)
अणु
	uपूर्णांक8_t rd_msg_buf[ISHTP_RD_MSG_BUF_SIZE];

	dev->prपूर्णांक_log(dev,
		"%s() got fixed client msg from client #%d\n",
		__func__, ishtp_hdr->fw_addr);
	dev->ops->ishtp_पढ़ो(dev, rd_msg_buf, ishtp_hdr->length);
	अगर (ishtp_hdr->fw_addr == ISHTP_SYSTEM_STATE_CLIENT_ADDR) अणु
		काष्ठा ish_प्रणाली_states_header *msg_hdr =
			(काष्ठा ish_प्रणाली_states_header *)rd_msg_buf;
		अगर (msg_hdr->cmd == SYSTEM_STATE_SUBSCRIBE)
			ishtp_send_resume(dev);
		/* अगर FW request arrived here, the प्रणाली is not suspended */
		अन्यथा
			dev_err(dev->devc, "unknown fixed client msg [%02X]\n",
				msg_hdr->cmd);
	पूर्ण
पूर्ण

/**
 * fix_cl_hdr() - Initialize fixed client header
 * @hdr: message header
 * @length: length of message
 * @cl_addr: Client address
 *
 * Initialize message header क्रम fixed client
 */
अटल अंतरभूत व्योम fix_cl_hdr(काष्ठा ishtp_msg_hdr *hdr, माप_प्रकार length,
	uपूर्णांक8_t cl_addr)
अणु
	hdr->host_addr = 0;
	hdr->fw_addr = cl_addr;
	hdr->length = length;
	hdr->msg_complete = 1;
	hdr->reserved = 0;
पूर्ण

/*** Suspend and resume notअगरication ***/

अटल uपूर्णांक32_t current_state;
अटल uपूर्णांक32_t supported_states = 0 | SUSPEND_STATE_BIT;

/**
 * ishtp_send_suspend() - Send suspend message to FW
 * @dev: ISHTP device instance
 *
 * Send suspend message to FW. This is useful क्रम प्रणाली मुक्तze (non S3) हाल
 */
व्योम ishtp_send_suspend(काष्ठा ishtp_device *dev)
अणु
	काष्ठा ishtp_msg_hdr	ishtp_hdr;
	काष्ठा ish_प्रणाली_states_status state_status_msg;
	स्थिर माप_प्रकार len = माप(काष्ठा ish_प्रणाली_states_status);

	fix_cl_hdr(&ishtp_hdr, len, ISHTP_SYSTEM_STATE_CLIENT_ADDR);

	स_रखो(&state_status_msg, 0, len);
	state_status_msg.hdr.cmd = SYSTEM_STATE_STATUS;
	state_status_msg.supported_states = supported_states;
	current_state |= SUSPEND_STATE_BIT;
	dev->prपूर्णांक_log(dev, "%s() sends SUSPEND notification\n", __func__);
	state_status_msg.states_status = current_state;

	ishtp_ग_लिखो_message(dev, &ishtp_hdr,
		(अचिन्हित अक्षर *)&state_status_msg);
पूर्ण
EXPORT_SYMBOL(ishtp_send_suspend);

/**
 * ishtp_send_resume() - Send resume message to FW
 * @dev: ISHTP device instance
 *
 * Send resume message to FW. This is useful क्रम प्रणाली मुक्तze (non S3) हाल
 */
व्योम ishtp_send_resume(काष्ठा ishtp_device *dev)
अणु
	काष्ठा ishtp_msg_hdr	ishtp_hdr;
	काष्ठा ish_प्रणाली_states_status state_status_msg;
	स्थिर माप_प्रकार len = माप(काष्ठा ish_प्रणाली_states_status);

	fix_cl_hdr(&ishtp_hdr, len, ISHTP_SYSTEM_STATE_CLIENT_ADDR);

	स_रखो(&state_status_msg, 0, len);
	state_status_msg.hdr.cmd = SYSTEM_STATE_STATUS;
	state_status_msg.supported_states = supported_states;
	current_state &= ~SUSPEND_STATE_BIT;
	dev->prपूर्णांक_log(dev, "%s() sends RESUME notification\n", __func__);
	state_status_msg.states_status = current_state;

	ishtp_ग_लिखो_message(dev, &ishtp_hdr,
		(अचिन्हित अक्षर *)&state_status_msg);
पूर्ण
EXPORT_SYMBOL(ishtp_send_resume);

/**
 * ishtp_query_subscribers() - Send query subscribers message
 * @dev: ISHTP device instance
 *
 * Send message to query subscribers
 */
व्योम ishtp_query_subscribers(काष्ठा ishtp_device *dev)
अणु
	काष्ठा ishtp_msg_hdr	ishtp_hdr;
	काष्ठा ish_प्रणाली_states_query_subscribers query_subscribers_msg;
	स्थिर माप_प्रकार len = माप(काष्ठा ish_प्रणाली_states_query_subscribers);

	fix_cl_hdr(&ishtp_hdr, len, ISHTP_SYSTEM_STATE_CLIENT_ADDR);

	स_रखो(&query_subscribers_msg, 0, len);
	query_subscribers_msg.hdr.cmd = SYSTEM_STATE_QUERY_SUBSCRIBERS;

	ishtp_ग_लिखो_message(dev, &ishtp_hdr,
		(अचिन्हित अक्षर *)&query_subscribers_msg);
पूर्ण
