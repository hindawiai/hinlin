<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2003-2020, Intel Corporation. All rights reserved.
 * Intel Management Engine Interface (Intel MEI) Linux driver
 */
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>

#समावेश <linux/mei.h>

#समावेश "mei_dev.h"
#समावेश "hbm.h"
#समावेश "client.h"

अटल स्थिर अक्षर *mei_hbm_status_str(क्रमागत mei_hbm_status status)
अणु
#घोषणा MEI_HBM_STATUS(status) हाल MEI_HBMS_##status: वापस #status
	चयन (status) अणु
	MEI_HBM_STATUS(SUCCESS);
	MEI_HBM_STATUS(CLIENT_NOT_FOUND);
	MEI_HBM_STATUS(ALREADY_EXISTS);
	MEI_HBM_STATUS(REJECTED);
	MEI_HBM_STATUS(INVALID_PARAMETER);
	MEI_HBM_STATUS(NOT_ALLOWED);
	MEI_HBM_STATUS(ALREADY_STARTED);
	MEI_HBM_STATUS(NOT_STARTED);
	शेष: वापस "unknown";
	पूर्ण
#अघोषित MEI_HBM_STATUS
पूर्ण;

अटल स्थिर अक्षर *mei_cl_conn_status_str(क्रमागत mei_cl_connect_status status)
अणु
#घोषणा MEI_CL_CS(status) हाल MEI_CL_CONN_##status: वापस #status
	चयन (status) अणु
	MEI_CL_CS(SUCCESS);
	MEI_CL_CS(NOT_FOUND);
	MEI_CL_CS(ALREADY_STARTED);
	MEI_CL_CS(OUT_OF_RESOURCES);
	MEI_CL_CS(MESSAGE_SMALL);
	MEI_CL_CS(NOT_ALLOWED);
	शेष: वापस "unknown";
	पूर्ण
#अघोषित MEI_CL_CCS
पूर्ण

स्थिर अक्षर *mei_hbm_state_str(क्रमागत mei_hbm_state state)
अणु
#घोषणा MEI_HBM_STATE(state) हाल MEI_HBM_##state: वापस #state
	चयन (state) अणु
	MEI_HBM_STATE(IDLE);
	MEI_HBM_STATE(STARTING);
	MEI_HBM_STATE(STARTED);
	MEI_HBM_STATE(DR_SETUP);
	MEI_HBM_STATE(ENUM_CLIENTS);
	MEI_HBM_STATE(CLIENT_PROPERTIES);
	MEI_HBM_STATE(STOPPED);
	शेष:
		वापस "unknown";
	पूर्ण
#अघोषित MEI_HBM_STATE
पूर्ण

/**
 * mei_cl_conn_status_to_त्रुटि_सं - convert client connect response
 * status to error code
 *
 * @status: client connect response status
 *
 * Return: corresponding error code
 */
अटल पूर्णांक mei_cl_conn_status_to_त्रुटि_सं(क्रमागत mei_cl_connect_status status)
अणु
	चयन (status) अणु
	हाल MEI_CL_CONN_SUCCESS:          वापस 0;
	हाल MEI_CL_CONN_NOT_FOUND:        वापस -ENOTTY;
	हाल MEI_CL_CONN_ALREADY_STARTED:  वापस -EBUSY;
	हाल MEI_CL_CONN_OUT_OF_RESOURCES: वापस -EBUSY;
	हाल MEI_CL_CONN_MESSAGE_SMALL:    वापस -EINVAL;
	हाल MEI_CL_CONN_NOT_ALLOWED:      वापस -EBUSY;
	शेष:                           वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * mei_hbm_ग_लिखो_message - wrapper क्रम sending hbm messages.
 *
 * @dev: mei device
 * @hdr: mei header
 * @data: payload
 */
अटल अंतरभूत पूर्णांक mei_hbm_ग_लिखो_message(काष्ठा mei_device *dev,
					काष्ठा mei_msg_hdr *hdr,
					स्थिर व्योम *data)
अणु
	वापस mei_ग_लिखो_message(dev, hdr, माप(*hdr), data, hdr->length);
पूर्ण

/**
 * mei_hbm_idle - set hbm to idle state
 *
 * @dev: the device काष्ठाure
 */
व्योम mei_hbm_idle(काष्ठा mei_device *dev)
अणु
	dev->init_clients_समयr = 0;
	dev->hbm_state = MEI_HBM_IDLE;
पूर्ण

/**
 * mei_hbm_reset - reset hbm counters and book keeping data काष्ठाurs
 *
 * @dev: the device काष्ठाure
 */
व्योम mei_hbm_reset(काष्ठा mei_device *dev)
अणु
	mei_me_cl_rm_all(dev);

	mei_hbm_idle(dev);
पूर्ण

/**
 * mei_hbm_hdr - स्थिरruct hbm header
 *
 * @mei_hdr: hbm header
 * @length: payload length
 */

अटल अंतरभूत व्योम mei_hbm_hdr(काष्ठा mei_msg_hdr *mei_hdr, माप_प्रकार length)
अणु
	स_रखो(mei_hdr, 0, माप(*mei_hdr));
	mei_hdr->length = length;
	mei_hdr->msg_complete = 1;
पूर्ण

/**
 * mei_hbm_cl_hdr - स्थिरruct client hbm header
 *
 * @cl: client
 * @hbm_cmd: host bus message command
 * @buf: buffer क्रम cl header
 * @len: buffer length
 */
अटल अंतरभूत
व्योम mei_hbm_cl_hdr(काष्ठा mei_cl *cl, u8 hbm_cmd, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा mei_hbm_cl_cmd *cmd = buf;

	स_रखो(cmd, 0, len);

	cmd->hbm_cmd = hbm_cmd;
	cmd->host_addr = mei_cl_host_addr(cl);
	cmd->me_addr = mei_cl_me_id(cl);
पूर्ण

/**
 * mei_hbm_cl_ग_लिखो - ग_लिखो simple hbm client message
 *
 * @dev: the device काष्ठाure
 * @cl: client
 * @hbm_cmd: host bus message command
 * @buf: message buffer
 * @len: buffer length
 *
 * Return: 0 on success, <0 on failure.
 */
अटल अंतरभूत पूर्णांक mei_hbm_cl_ग_लिखो(काष्ठा mei_device *dev, काष्ठा mei_cl *cl,
				   u8 hbm_cmd, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा mei_msg_hdr mei_hdr;

	mei_hbm_hdr(&mei_hdr, len);
	mei_hbm_cl_hdr(cl, hbm_cmd, buf, len);

	वापस mei_hbm_ग_लिखो_message(dev, &mei_hdr, buf);
पूर्ण

/**
 * mei_hbm_cl_addr_equal - check अगर the client's and
 *	the message address match
 *
 * @cl: client
 * @cmd: hbm client message
 *
 * Return: true अगर addresses are the same
 */
अटल अंतरभूत
bool mei_hbm_cl_addr_equal(काष्ठा mei_cl *cl, काष्ठा mei_hbm_cl_cmd *cmd)
अणु
	वापस  mei_cl_host_addr(cl) == cmd->host_addr &&
		mei_cl_me_id(cl) == cmd->me_addr;
पूर्ण

/**
 * mei_hbm_cl_find_by_cmd - find recipient client
 *
 * @dev: the device काष्ठाure
 * @buf: a buffer with hbm cl command
 *
 * Return: the recipient client or शून्य अगर not found
 */
अटल अंतरभूत
काष्ठा mei_cl *mei_hbm_cl_find_by_cmd(काष्ठा mei_device *dev, व्योम *buf)
अणु
	काष्ठा mei_hbm_cl_cmd *cmd = (काष्ठा mei_hbm_cl_cmd *)buf;
	काष्ठा mei_cl *cl;

	list_क्रम_each_entry(cl, &dev->file_list, link)
		अगर (mei_hbm_cl_addr_equal(cl, cmd))
			वापस cl;
	वापस शून्य;
पूर्ण


/**
 * mei_hbm_start_रुको - रुको क्रम start response message.
 *
 * @dev: the device काष्ठाure
 *
 * Return: 0 on success and < 0 on failure
 */
पूर्णांक mei_hbm_start_रुको(काष्ठा mei_device *dev)
अणु
	पूर्णांक ret;

	अगर (dev->hbm_state > MEI_HBM_STARTING)
		वापस 0;

	mutex_unlock(&dev->device_lock);
	ret = रुको_event_समयout(dev->रुको_hbm_start,
			dev->hbm_state != MEI_HBM_STARTING,
			mei_secs_to_jअगरfies(MEI_HBM_TIMEOUT));
	mutex_lock(&dev->device_lock);

	अगर (ret == 0 && (dev->hbm_state <= MEI_HBM_STARTING)) अणु
		dev->hbm_state = MEI_HBM_IDLE;
		dev_err(dev->dev, "waiting for mei start failed\n");
		वापस -ETIME;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * mei_hbm_start_req - sends start request message.
 *
 * @dev: the device काष्ठाure
 *
 * Return: 0 on success and < 0 on failure
 */
पूर्णांक mei_hbm_start_req(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_msg_hdr mei_hdr;
	काष्ठा hbm_host_version_request req;
	पूर्णांक ret;

	mei_hbm_reset(dev);

	mei_hbm_hdr(&mei_hdr, माप(req));

	/* host start message */
	स_रखो(&req, 0, माप(req));
	req.hbm_cmd = HOST_START_REQ_CMD;
	req.host_version.major_version = HBM_MAJOR_VERSION;
	req.host_version.minor_version = HBM_MINOR_VERSION;

	dev->hbm_state = MEI_HBM_IDLE;
	ret = mei_hbm_ग_लिखो_message(dev, &mei_hdr, &req);
	अगर (ret) अणु
		dev_err(dev->dev, "version message write failed: ret = %d\n",
			ret);
		वापस ret;
	पूर्ण

	dev->hbm_state = MEI_HBM_STARTING;
	dev->init_clients_समयr = MEI_CLIENTS_INIT_TIMEOUT;
	mei_schedule_stall_समयr(dev);
	वापस 0;
पूर्ण

/**
 * mei_hbm_dma_setup_req() - setup DMA request
 * @dev: the device काष्ठाure
 *
 * Return: 0 on success and < 0 on failure
 */
अटल पूर्णांक mei_hbm_dma_setup_req(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_msg_hdr mei_hdr;
	काष्ठा hbm_dma_setup_request req;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	mei_hbm_hdr(&mei_hdr, माप(req));

	स_रखो(&req, 0, माप(req));
	req.hbm_cmd = MEI_HBM_DMA_SETUP_REQ_CMD;
	क्रम (i = 0; i < DMA_DSCR_NUM; i++) अणु
		phys_addr_t paddr;

		paddr = dev->dr_dscr[i].daddr;
		req.dma_dscr[i].addr_hi = upper_32_bits(paddr);
		req.dma_dscr[i].addr_lo = lower_32_bits(paddr);
		req.dma_dscr[i].size = dev->dr_dscr[i].size;
	पूर्ण

	mei_dma_ring_reset(dev);

	ret = mei_hbm_ग_लिखो_message(dev, &mei_hdr, &req);
	अगर (ret) अणु
		dev_err(dev->dev, "dma setup request write failed: ret = %d.\n",
			ret);
		वापस ret;
	पूर्ण

	dev->hbm_state = MEI_HBM_DR_SETUP;
	dev->init_clients_समयr = MEI_CLIENTS_INIT_TIMEOUT;
	mei_schedule_stall_समयr(dev);
	वापस 0;
पूर्ण

/**
 * mei_hbm_capabilities_req - request capabilities
 *
 * @dev: the device काष्ठाure
 *
 * Return: 0 on success and < 0 on failure
 */
अटल पूर्णांक mei_hbm_capabilities_req(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_msg_hdr mei_hdr;
	काष्ठा hbm_capability_request req;
	पूर्णांक ret;

	mei_hbm_hdr(&mei_hdr, माप(req));

	स_रखो(&req, 0, माप(req));
	req.hbm_cmd = MEI_HBM_CAPABILITIES_REQ_CMD;
	अगर (dev->hbm_f_vt_supported)
		req.capability_requested[0] |= HBM_CAP_VT;
	अगर (dev->hbm_f_cd_supported)
		req.capability_requested[0] |= HBM_CAP_CD;

	ret = mei_hbm_ग_लिखो_message(dev, &mei_hdr, &req);
	अगर (ret) अणु
		dev_err(dev->dev,
			"capabilities request write failed: ret = %d.\n", ret);
		वापस ret;
	पूर्ण

	dev->hbm_state = MEI_HBM_CAP_SETUP;
	dev->init_clients_समयr = MEI_CLIENTS_INIT_TIMEOUT;
	mei_schedule_stall_समयr(dev);
	वापस 0;
पूर्ण

/**
 * mei_hbm_क्रमागत_clients_req - sends क्रमागतeration client request message.
 *
 * @dev: the device काष्ठाure
 *
 * Return: 0 on success and < 0 on failure
 */
अटल पूर्णांक mei_hbm_क्रमागत_clients_req(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_msg_hdr mei_hdr;
	काष्ठा hbm_host_क्रमागत_request req;
	पूर्णांक ret;

	/* क्रमागतerate clients */
	mei_hbm_hdr(&mei_hdr, माप(req));

	स_रखो(&req, 0, माप(req));
	req.hbm_cmd = HOST_ENUM_REQ_CMD;
	req.flags |= dev->hbm_f_dc_supported ? MEI_HBM_ENUM_F_ALLOW_ADD : 0;
	req.flags |= dev->hbm_f_ie_supported ?
			  MEI_HBM_ENUM_F_IMMEDIATE_ENUM : 0;

	ret = mei_hbm_ग_लिखो_message(dev, &mei_hdr, &req);
	अगर (ret) अणु
		dev_err(dev->dev, "enumeration request write failed: ret = %d.\n",
			ret);
		वापस ret;
	पूर्ण
	dev->hbm_state = MEI_HBM_ENUM_CLIENTS;
	dev->init_clients_समयr = MEI_CLIENTS_INIT_TIMEOUT;
	mei_schedule_stall_समयr(dev);
	वापस 0;
पूर्ण

/**
 * mei_hbm_me_cl_add - add new me client to the list
 *
 * @dev: the device काष्ठाure
 * @res: hbm property response
 *
 * Return: 0 on success and -ENOMEM on allocation failure
 */

अटल पूर्णांक mei_hbm_me_cl_add(काष्ठा mei_device *dev,
			     काष्ठा hbm_props_response *res)
अणु
	काष्ठा mei_me_client *me_cl;
	स्थिर uuid_le *uuid = &res->client_properties.protocol_name;

	mei_me_cl_rm_by_uuid(dev, uuid);

	me_cl = kzalloc(माप(*me_cl), GFP_KERNEL);
	अगर (!me_cl)
		वापस -ENOMEM;

	mei_me_cl_init(me_cl);

	me_cl->props = res->client_properties;
	me_cl->client_id = res->me_addr;
	me_cl->tx_flow_ctrl_creds = 0;

	mei_me_cl_add(dev, me_cl);

	वापस 0;
पूर्ण

/**
 * mei_hbm_add_cl_resp - send response to fw on client add request
 *
 * @dev: the device काष्ठाure
 * @addr: me address
 * @status: response status
 *
 * Return: 0 on success and < 0 on failure
 */
अटल पूर्णांक mei_hbm_add_cl_resp(काष्ठा mei_device *dev, u8 addr, u8 status)
अणु
	काष्ठा mei_msg_hdr mei_hdr;
	काष्ठा hbm_add_client_response resp;
	पूर्णांक ret;

	dev_dbg(dev->dev, "adding client response\n");

	mei_hbm_hdr(&mei_hdr, माप(resp));

	स_रखो(&resp, 0, माप(resp));
	resp.hbm_cmd = MEI_HBM_ADD_CLIENT_RES_CMD;
	resp.me_addr = addr;
	resp.status  = status;

	ret = mei_hbm_ग_लिखो_message(dev, &mei_hdr, &resp);
	अगर (ret)
		dev_err(dev->dev, "add client response write failed: ret = %d\n",
			ret);
	वापस ret;
पूर्ण

/**
 * mei_hbm_fw_add_cl_req - request from the fw to add a client
 *
 * @dev: the device काष्ठाure
 * @req: add client request
 *
 * Return: 0 on success and < 0 on failure
 */
अटल पूर्णांक mei_hbm_fw_add_cl_req(काष्ठा mei_device *dev,
			      काष्ठा hbm_add_client_request *req)
अणु
	पूर्णांक ret;
	u8 status = MEI_HBMS_SUCCESS;

	BUILD_BUG_ON(माप(काष्ठा hbm_add_client_request) !=
			माप(काष्ठा hbm_props_response));

	ret = mei_hbm_me_cl_add(dev, (काष्ठा hbm_props_response *)req);
	अगर (ret)
		status = !MEI_HBMS_SUCCESS;

	अगर (dev->dev_state == MEI_DEV_ENABLED)
		schedule_work(&dev->bus_rescan_work);

	वापस mei_hbm_add_cl_resp(dev, req->me_addr, status);
पूर्ण

/**
 * mei_hbm_cl_notअगरy_req - send notअगरication request
 *
 * @dev: the device काष्ठाure
 * @cl: a client to disconnect from
 * @start: true क्रम start false क्रम stop
 *
 * Return: 0 on success and -EIO on ग_लिखो failure
 */
पूर्णांक mei_hbm_cl_notअगरy_req(काष्ठा mei_device *dev,
			  काष्ठा mei_cl *cl, u8 start)
अणु

	काष्ठा mei_msg_hdr mei_hdr;
	काष्ठा hbm_notअगरication_request req;
	पूर्णांक ret;

	mei_hbm_hdr(&mei_hdr, माप(req));
	mei_hbm_cl_hdr(cl, MEI_HBM_NOTIFY_REQ_CMD, &req, माप(req));

	req.start = start;

	ret = mei_hbm_ग_लिखो_message(dev, &mei_hdr, &req);
	अगर (ret)
		dev_err(dev->dev, "notify request failed: ret = %d\n", ret);

	वापस ret;
पूर्ण

/**
 *  notअगरy_res_to_fop - convert notअगरication response to the proper
 *      notअगरication FOP
 *
 * @cmd: client notअगरication start response command
 *
 * Return:  MEI_FOP_NOTIFY_START or MEI_FOP_NOTIFY_STOP;
 */
अटल अंतरभूत क्रमागत mei_cb_file_ops notअगरy_res_to_fop(काष्ठा mei_hbm_cl_cmd *cmd)
अणु
	काष्ठा hbm_notअगरication_response *rs =
		(काष्ठा hbm_notअगरication_response *)cmd;

	वापस mei_cl_notअगरy_req2fop(rs->start);
पूर्ण

/**
 * mei_hbm_cl_notअगरy_start_res - update the client state according
 *       notअगरy start response
 *
 * @dev: the device काष्ठाure
 * @cl: mei host client
 * @cmd: client notअगरication start response command
 */
अटल व्योम mei_hbm_cl_notअगरy_start_res(काष्ठा mei_device *dev,
					काष्ठा mei_cl *cl,
					काष्ठा mei_hbm_cl_cmd *cmd)
अणु
	काष्ठा hbm_notअगरication_response *rs =
		(काष्ठा hbm_notअगरication_response *)cmd;

	cl_dbg(dev, cl, "hbm: notify start response status=%d\n", rs->status);

	अगर (rs->status == MEI_HBMS_SUCCESS ||
	    rs->status == MEI_HBMS_ALREADY_STARTED) अणु
		cl->notअगरy_en = true;
		cl->status = 0;
	पूर्ण अन्यथा अणु
		cl->status = -EINVAL;
	पूर्ण
पूर्ण

/**
 * mei_hbm_cl_notअगरy_stop_res - update the client state according
 *       notअगरy stop response
 *
 * @dev: the device काष्ठाure
 * @cl: mei host client
 * @cmd: client notअगरication stop response command
 */
अटल व्योम mei_hbm_cl_notअगरy_stop_res(काष्ठा mei_device *dev,
				       काष्ठा mei_cl *cl,
				       काष्ठा mei_hbm_cl_cmd *cmd)
अणु
	काष्ठा hbm_notअगरication_response *rs =
		(काष्ठा hbm_notअगरication_response *)cmd;

	cl_dbg(dev, cl, "hbm: notify stop response status=%d\n", rs->status);

	अगर (rs->status == MEI_HBMS_SUCCESS ||
	    rs->status == MEI_HBMS_NOT_STARTED) अणु
		cl->notअगरy_en = false;
		cl->status = 0;
	पूर्ण अन्यथा अणु
		/* TODO: spec is not clear yet about other possible issues */
		cl->status = -EINVAL;
	पूर्ण
पूर्ण

/**
 * mei_hbm_cl_notअगरy - संकेत notअगरication event
 *
 * @dev: the device काष्ठाure
 * @cmd: notअगरication client message
 */
अटल व्योम mei_hbm_cl_notअगरy(काष्ठा mei_device *dev,
			      काष्ठा mei_hbm_cl_cmd *cmd)
अणु
	काष्ठा mei_cl *cl;

	cl = mei_hbm_cl_find_by_cmd(dev, cmd);
	अगर (cl)
		mei_cl_notअगरy(cl);
पूर्ण

/**
 * mei_hbm_cl_dma_map_req - send client dma map request
 *
 * @dev: the device काष्ठाure
 * @cl: mei host client
 *
 * Return: 0 on success and -EIO on ग_लिखो failure
 */
पूर्णांक mei_hbm_cl_dma_map_req(काष्ठा mei_device *dev, काष्ठा mei_cl *cl)
अणु
	काष्ठा mei_msg_hdr mei_hdr;
	काष्ठा hbm_client_dma_map_request req;
	पूर्णांक ret;

	mei_hbm_hdr(&mei_hdr, माप(req));

	स_रखो(&req, 0, माप(req));

	req.hbm_cmd = MEI_HBM_CLIENT_DMA_MAP_REQ_CMD;
	req.client_buffer_id = cl->dma.buffer_id;
	req.address_lsb = lower_32_bits(cl->dma.daddr);
	req.address_msb = upper_32_bits(cl->dma.daddr);
	req.size = cl->dma.size;

	ret = mei_hbm_ग_लिखो_message(dev, &mei_hdr, &req);
	अगर (ret)
		dev_err(dev->dev, "dma map request failed: ret = %d\n", ret);

	वापस ret;
पूर्ण

/**
 * mei_hbm_cl_dma_unmap_req - send client dma unmap request
 *
 * @dev: the device काष्ठाure
 * @cl: mei host client
 *
 * Return: 0 on success and -EIO on ग_लिखो failure
 */
पूर्णांक mei_hbm_cl_dma_unmap_req(काष्ठा mei_device *dev, काष्ठा mei_cl *cl)
अणु
	काष्ठा mei_msg_hdr mei_hdr;
	काष्ठा hbm_client_dma_unmap_request req;
	पूर्णांक ret;

	mei_hbm_hdr(&mei_hdr, माप(req));

	स_रखो(&req, 0, माप(req));

	req.hbm_cmd = MEI_HBM_CLIENT_DMA_UNMAP_REQ_CMD;
	req.client_buffer_id = cl->dma.buffer_id;

	ret = mei_hbm_ग_लिखो_message(dev, &mei_hdr, &req);
	अगर (ret)
		dev_err(dev->dev, "dma unmap request failed: ret = %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम mei_hbm_cl_dma_map_res(काष्ठा mei_device *dev,
				   काष्ठा hbm_client_dma_response *res)
अणु
	काष्ठा mei_cl *cl;
	काष्ठा mei_cl_cb *cb, *next;

	cl = शून्य;
	list_क्रम_each_entry_safe(cb, next, &dev->ctrl_rd_list, list) अणु
		अगर (cb->fop_type != MEI_FOP_DMA_MAP)
			जारी;
		अगर (!cb->cl->dma.buffer_id || cb->cl->dma_mapped)
			जारी;

		cl = cb->cl;
		अवरोध;
	पूर्ण
	अगर (!cl)
		वापस;

	dev_dbg(dev->dev, "cl dma map result = %d\n", res->status);
	cl->status = res->status;
	अगर (!cl->status)
		cl->dma_mapped = 1;
	wake_up(&cl->रुको);
पूर्ण

अटल व्योम mei_hbm_cl_dma_unmap_res(काष्ठा mei_device *dev,
				     काष्ठा hbm_client_dma_response *res)
अणु
	काष्ठा mei_cl *cl;
	काष्ठा mei_cl_cb *cb, *next;

	cl = शून्य;
	list_क्रम_each_entry_safe(cb, next, &dev->ctrl_rd_list, list) अणु
		अगर (cb->fop_type != MEI_FOP_DMA_UNMAP)
			जारी;
		अगर (!cb->cl->dma.buffer_id || !cb->cl->dma_mapped)
			जारी;

		cl = cb->cl;
		अवरोध;
	पूर्ण
	अगर (!cl)
		वापस;

	dev_dbg(dev->dev, "cl dma unmap result = %d\n", res->status);
	cl->status = res->status;
	अगर (!cl->status)
		cl->dma_mapped = 0;
	wake_up(&cl->रुको);
पूर्ण

/**
 * mei_hbm_prop_req - request property क्रम a single client
 *
 * @dev: the device काष्ठाure
 * @start_idx: client index to start search
 *
 * Return: 0 on success and < 0 on failure
 */
अटल पूर्णांक mei_hbm_prop_req(काष्ठा mei_device *dev, अचिन्हित दीर्घ start_idx)
अणु
	काष्ठा mei_msg_hdr mei_hdr;
	काष्ठा hbm_props_request req;
	अचिन्हित दीर्घ addr;
	पूर्णांक ret;

	addr = find_next_bit(dev->me_clients_map, MEI_CLIENTS_MAX, start_idx);

	/* We got all client properties */
	अगर (addr == MEI_CLIENTS_MAX) अणु
		dev->hbm_state = MEI_HBM_STARTED;
		mei_host_client_init(dev);
		वापस 0;
	पूर्ण

	mei_hbm_hdr(&mei_hdr, माप(req));

	स_रखो(&req, 0, माप(req));

	req.hbm_cmd = HOST_CLIENT_PROPERTIES_REQ_CMD;
	req.me_addr = addr;

	ret = mei_hbm_ग_लिखो_message(dev, &mei_hdr, &req);
	अगर (ret) अणु
		dev_err(dev->dev, "properties request write failed: ret = %d\n",
			ret);
		वापस ret;
	पूर्ण

	dev->init_clients_समयr = MEI_CLIENTS_INIT_TIMEOUT;
	mei_schedule_stall_समयr(dev);

	वापस 0;
पूर्ण

/**
 * mei_hbm_pg - sends pg command
 *
 * @dev: the device काष्ठाure
 * @pg_cmd: the pg command code
 *
 * Return: -EIO on ग_लिखो failure
 *         -EOPNOTSUPP अगर the operation is not supported by the protocol
 */
पूर्णांक mei_hbm_pg(काष्ठा mei_device *dev, u8 pg_cmd)
अणु
	काष्ठा mei_msg_hdr mei_hdr;
	काष्ठा hbm_घातer_gate req;
	पूर्णांक ret;

	अगर (!dev->hbm_f_pg_supported)
		वापस -EOPNOTSUPP;

	mei_hbm_hdr(&mei_hdr, माप(req));

	स_रखो(&req, 0, माप(req));
	req.hbm_cmd = pg_cmd;

	ret = mei_hbm_ग_लिखो_message(dev, &mei_hdr, &req);
	अगर (ret)
		dev_err(dev->dev, "power gate command write failed.\n");
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mei_hbm_pg);

/**
 * mei_hbm_stop_req - send stop request message
 *
 * @dev: mei device
 *
 * Return: -EIO on ग_लिखो failure
 */
अटल पूर्णांक mei_hbm_stop_req(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_msg_hdr mei_hdr;
	काष्ठा hbm_host_stop_request req;

	mei_hbm_hdr(&mei_hdr, माप(req));

	स_रखो(&req, 0, माप(req));
	req.hbm_cmd = HOST_STOP_REQ_CMD;
	req.reason = DRIVER_STOP_REQUEST;

	वापस mei_hbm_ग_लिखो_message(dev, &mei_hdr, &req);
पूर्ण

/**
 * mei_hbm_cl_flow_control_req - sends flow control request.
 *
 * @dev: the device काष्ठाure
 * @cl: client info
 *
 * Return: -EIO on ग_लिखो failure
 */
पूर्णांक mei_hbm_cl_flow_control_req(काष्ठा mei_device *dev, काष्ठा mei_cl *cl)
अणु
	काष्ठा hbm_flow_control req;

	cl_dbg(dev, cl, "sending flow control\n");
	वापस mei_hbm_cl_ग_लिखो(dev, cl, MEI_FLOW_CONTROL_CMD,
				&req, माप(req));
पूर्ण

/**
 * mei_hbm_add_single_tx_flow_ctrl_creds - adds single buffer credentials.
 *
 * @dev: the device काष्ठाure
 * @fctrl: flow control response bus message
 *
 * Return: 0 on success, < 0 otherwise
 */
अटल पूर्णांक mei_hbm_add_single_tx_flow_ctrl_creds(काष्ठा mei_device *dev,
						 काष्ठा hbm_flow_control *fctrl)
अणु
	काष्ठा mei_me_client *me_cl;
	पूर्णांक rets;

	me_cl = mei_me_cl_by_id(dev, fctrl->me_addr);
	अगर (!me_cl) अणु
		dev_err(dev->dev, "no such me client %d\n", fctrl->me_addr);
		वापस -ENOENT;
	पूर्ण

	अगर (WARN_ON(me_cl->props.single_recv_buf == 0)) अणु
		rets = -EINVAL;
		जाओ out;
	पूर्ण

	me_cl->tx_flow_ctrl_creds++;
	dev_dbg(dev->dev, "recv flow ctrl msg ME %d (single) creds = %d.\n",
		fctrl->me_addr, me_cl->tx_flow_ctrl_creds);

	rets = 0;
out:
	mei_me_cl_put(me_cl);
	वापस rets;
पूर्ण

/**
 * mei_hbm_cl_flow_control_res - flow control response from me
 *
 * @dev: the device काष्ठाure
 * @fctrl: flow control response bus message
 */
अटल व्योम mei_hbm_cl_tx_flow_ctrl_creds_res(काष्ठा mei_device *dev,
					       काष्ठा hbm_flow_control *fctrl)
अणु
	काष्ठा mei_cl *cl;

	अगर (!fctrl->host_addr) अणु
		/* single receive buffer */
		mei_hbm_add_single_tx_flow_ctrl_creds(dev, fctrl);
		वापस;
	पूर्ण

	cl = mei_hbm_cl_find_by_cmd(dev, fctrl);
	अगर (cl) अणु
		cl->tx_flow_ctrl_creds++;
		cl_dbg(dev, cl, "flow control creds = %d.\n",
				cl->tx_flow_ctrl_creds);
	पूर्ण
पूर्ण


/**
 * mei_hbm_cl_disconnect_req - sends disconnect message to fw.
 *
 * @dev: the device काष्ठाure
 * @cl: a client to disconnect from
 *
 * Return: -EIO on ग_लिखो failure
 */
पूर्णांक mei_hbm_cl_disconnect_req(काष्ठा mei_device *dev, काष्ठा mei_cl *cl)
अणु
	काष्ठा hbm_client_connect_request req;

	वापस mei_hbm_cl_ग_लिखो(dev, cl, CLIENT_DISCONNECT_REQ_CMD,
				&req, माप(req));
पूर्ण

/**
 * mei_hbm_cl_disconnect_rsp - sends disconnect respose to the FW
 *
 * @dev: the device काष्ठाure
 * @cl: a client to disconnect from
 *
 * Return: -EIO on ग_लिखो failure
 */
पूर्णांक mei_hbm_cl_disconnect_rsp(काष्ठा mei_device *dev, काष्ठा mei_cl *cl)
अणु
	काष्ठा hbm_client_connect_response resp;

	वापस mei_hbm_cl_ग_लिखो(dev, cl, CLIENT_DISCONNECT_RES_CMD,
				&resp, माप(resp));
पूर्ण

/**
 * mei_hbm_cl_disconnect_res - update the client state according
 *       disconnect response
 *
 * @dev: the device काष्ठाure
 * @cl: mei host client
 * @cmd: disconnect client response host bus message
 */
अटल व्योम mei_hbm_cl_disconnect_res(काष्ठा mei_device *dev, काष्ठा mei_cl *cl,
				      काष्ठा mei_hbm_cl_cmd *cmd)
अणु
	काष्ठा hbm_client_connect_response *rs =
		(काष्ठा hbm_client_connect_response *)cmd;

	cl_dbg(dev, cl, "hbm: disconnect response status=%d\n", rs->status);

	अगर (rs->status == MEI_CL_DISCONN_SUCCESS)
		cl->state = MEI_खाता_DISCONNECT_REPLY;
	cl->status = 0;
पूर्ण

/**
 * mei_hbm_cl_connect_req - send connection request to specअगरic me client
 *
 * @dev: the device काष्ठाure
 * @cl: a client to connect to
 *
 * Return: -EIO on ग_लिखो failure
 */
पूर्णांक mei_hbm_cl_connect_req(काष्ठा mei_device *dev, काष्ठा mei_cl *cl)
अणु
	काष्ठा hbm_client_connect_request req;

	वापस mei_hbm_cl_ग_लिखो(dev, cl, CLIENT_CONNECT_REQ_CMD,
				&req, माप(req));
पूर्ण

/**
 * mei_hbm_cl_connect_res - update the client state according
 *        connection response
 *
 * @dev: the device काष्ठाure
 * @cl: mei host client
 * @cmd: connect client response host bus message
 */
अटल व्योम mei_hbm_cl_connect_res(काष्ठा mei_device *dev, काष्ठा mei_cl *cl,
				   काष्ठा mei_hbm_cl_cmd *cmd)
अणु
	काष्ठा hbm_client_connect_response *rs =
		(काष्ठा hbm_client_connect_response *)cmd;

	cl_dbg(dev, cl, "hbm: connect response status=%s\n",
			mei_cl_conn_status_str(rs->status));

	अगर (rs->status == MEI_CL_CONN_SUCCESS)
		cl->state = MEI_खाता_CONNECTED;
	अन्यथा अणु
		cl->state = MEI_खाता_DISCONNECT_REPLY;
		अगर (rs->status == MEI_CL_CONN_NOT_FOUND) अणु
			mei_me_cl_del(dev, cl->me_cl);
			अगर (dev->dev_state == MEI_DEV_ENABLED)
				schedule_work(&dev->bus_rescan_work);
		पूर्ण
	पूर्ण
	cl->status = mei_cl_conn_status_to_त्रुटि_सं(rs->status);
पूर्ण

/**
 * mei_hbm_cl_res - process hbm response received on behalf
 *         an client
 *
 * @dev: the device काष्ठाure
 * @rs:  hbm client message
 * @fop_type: file operation type
 */
अटल व्योम mei_hbm_cl_res(काष्ठा mei_device *dev,
			   काष्ठा mei_hbm_cl_cmd *rs,
			   क्रमागत mei_cb_file_ops fop_type)
अणु
	काष्ठा mei_cl *cl;
	काष्ठा mei_cl_cb *cb, *next;

	cl = शून्य;
	list_क्रम_each_entry_safe(cb, next, &dev->ctrl_rd_list, list) अणु

		cl = cb->cl;

		अगर (cb->fop_type != fop_type)
			जारी;

		अगर (mei_hbm_cl_addr_equal(cl, rs)) अणु
			list_del_init(&cb->list);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!cl)
		वापस;

	चयन (fop_type) अणु
	हाल MEI_FOP_CONNECT:
		mei_hbm_cl_connect_res(dev, cl, rs);
		अवरोध;
	हाल MEI_FOP_DISCONNECT:
		mei_hbm_cl_disconnect_res(dev, cl, rs);
		अवरोध;
	हाल MEI_FOP_NOTIFY_START:
		mei_hbm_cl_notअगरy_start_res(dev, cl, rs);
		अवरोध;
	हाल MEI_FOP_NOTIFY_STOP:
		mei_hbm_cl_notअगरy_stop_res(dev, cl, rs);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	cl->समयr_count = 0;
	wake_up(&cl->रुको);
पूर्ण


/**
 * mei_hbm_fw_disconnect_req - disconnect request initiated by ME firmware
 *  host sends disconnect response
 *
 * @dev: the device काष्ठाure.
 * @disconnect_req: disconnect request bus message from the me
 *
 * Return: -ENOMEM on allocation failure
 */
अटल पूर्णांक mei_hbm_fw_disconnect_req(काष्ठा mei_device *dev,
		काष्ठा hbm_client_connect_request *disconnect_req)
अणु
	काष्ठा mei_cl *cl;
	काष्ठा mei_cl_cb *cb;

	cl = mei_hbm_cl_find_by_cmd(dev, disconnect_req);
	अगर (cl) अणु
		cl_warn(dev, cl, "fw disconnect request received\n");
		cl->state = MEI_खाता_DISCONNECTING;
		cl->समयr_count = 0;

		cb = mei_cl_enqueue_ctrl_wr_cb(cl, 0, MEI_FOP_DISCONNECT_RSP,
					       शून्य);
		अगर (!cb)
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * mei_hbm_pg_enter_res - PG enter response received
 *
 * @dev: the device काष्ठाure.
 *
 * Return: 0 on success, -EPROTO on state mismatch
 */
अटल पूर्णांक mei_hbm_pg_enter_res(काष्ठा mei_device *dev)
अणु
	अगर (mei_pg_state(dev) != MEI_PG_OFF ||
	    dev->pg_event != MEI_PG_EVENT_WAIT) अणु
		dev_err(dev->dev, "hbm: pg entry response: state mismatch [%s, %d]\n",
			mei_pg_state_str(mei_pg_state(dev)), dev->pg_event);
		वापस -EPROTO;
	पूर्ण

	dev->pg_event = MEI_PG_EVENT_RECEIVED;
	wake_up(&dev->रुको_pg);

	वापस 0;
पूर्ण

/**
 * mei_hbm_pg_resume - process with PG resume
 *
 * @dev: the device काष्ठाure.
 */
व्योम mei_hbm_pg_resume(काष्ठा mei_device *dev)
अणु
	pm_request_resume(dev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(mei_hbm_pg_resume);

/**
 * mei_hbm_pg_निकास_res - PG निकास response received
 *
 * @dev: the device काष्ठाure.
 *
 * Return: 0 on success, -EPROTO on state mismatch
 */
अटल पूर्णांक mei_hbm_pg_निकास_res(काष्ठा mei_device *dev)
अणु
	अगर (mei_pg_state(dev) != MEI_PG_ON ||
	    (dev->pg_event != MEI_PG_EVENT_WAIT &&
	     dev->pg_event != MEI_PG_EVENT_IDLE)) अणु
		dev_err(dev->dev, "hbm: pg exit response: state mismatch [%s, %d]\n",
			mei_pg_state_str(mei_pg_state(dev)), dev->pg_event);
		वापस -EPROTO;
	पूर्ण

	चयन (dev->pg_event) अणु
	हाल MEI_PG_EVENT_WAIT:
		dev->pg_event = MEI_PG_EVENT_RECEIVED;
		wake_up(&dev->रुको_pg);
		अवरोध;
	हाल MEI_PG_EVENT_IDLE:
		/*
		* If the driver is not रुकोing on this then
		* this is HW initiated निकास from PG.
		* Start runसमय pm resume sequence to निकास from PG.
		*/
		dev->pg_event = MEI_PG_EVENT_RECEIVED;
		mei_hbm_pg_resume(dev);
		अवरोध;
	शेष:
		WARN(1, "hbm: pg exit response: unexpected pg event = %d\n",
		     dev->pg_event);
		वापस -EPROTO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * mei_hbm_config_features - check what hbm features and commands
 *        are supported by the fw
 *
 * @dev: the device काष्ठाure
 */
अटल व्योम mei_hbm_config_features(काष्ठा mei_device *dev)
अणु
	/* Power Gating Isolation Support */
	dev->hbm_f_pg_supported = 0;
	अगर (dev->version.major_version > HBM_MAJOR_VERSION_PGI)
		dev->hbm_f_pg_supported = 1;

	अगर (dev->version.major_version == HBM_MAJOR_VERSION_PGI &&
	    dev->version.minor_version >= HBM_MINOR_VERSION_PGI)
		dev->hbm_f_pg_supported = 1;

	dev->hbm_f_dc_supported = 0;
	अगर (dev->version.major_version >= HBM_MAJOR_VERSION_DC)
		dev->hbm_f_dc_supported = 1;

	dev->hbm_f_ie_supported = 0;
	अगर (dev->version.major_version >= HBM_MAJOR_VERSION_IE)
		dev->hbm_f_ie_supported = 1;

	/* disconnect on connect समयout instead of link reset */
	dev->hbm_f_करोt_supported = 0;
	अगर (dev->version.major_version >= HBM_MAJOR_VERSION_DOT)
		dev->hbm_f_करोt_supported = 1;

	/* Notअगरication Event Support */
	dev->hbm_f_ev_supported = 0;
	अगर (dev->version.major_version >= HBM_MAJOR_VERSION_EV)
		dev->hbm_f_ev_supported = 1;

	/* Fixed Address Client Support */
	dev->hbm_f_fa_supported = 0;
	अगर (dev->version.major_version >= HBM_MAJOR_VERSION_FA)
		dev->hbm_f_fa_supported = 1;

	/* OS ver message Support */
	dev->hbm_f_os_supported = 0;
	अगर (dev->version.major_version >= HBM_MAJOR_VERSION_OS)
		dev->hbm_f_os_supported = 1;

	/* DMA Ring Support */
	dev->hbm_f_dr_supported = 0;
	अगर (dev->version.major_version > HBM_MAJOR_VERSION_DR ||
	    (dev->version.major_version == HBM_MAJOR_VERSION_DR &&
	     dev->version.minor_version >= HBM_MINOR_VERSION_DR))
		dev->hbm_f_dr_supported = 1;

	/* VTag Support */
	dev->hbm_f_vt_supported = 0;
	अगर (dev->version.major_version > HBM_MAJOR_VERSION_VT ||
	    (dev->version.major_version == HBM_MAJOR_VERSION_VT &&
	     dev->version.minor_version >= HBM_MINOR_VERSION_VT))
		dev->hbm_f_vt_supported = 1;

	/* Capability message Support */
	dev->hbm_f_cap_supported = 0;
	अगर (dev->version.major_version > HBM_MAJOR_VERSION_CAP ||
	    (dev->version.major_version == HBM_MAJOR_VERSION_CAP &&
	     dev->version.minor_version >= HBM_MINOR_VERSION_CAP))
		dev->hbm_f_cap_supported = 1;

	/* Client DMA Support */
	dev->hbm_f_cd_supported = 0;
	अगर (dev->version.major_version > HBM_MAJOR_VERSION_CD ||
	    (dev->version.major_version == HBM_MAJOR_VERSION_CD &&
	     dev->version.minor_version >= HBM_MINOR_VERSION_CD))
		dev->hbm_f_cd_supported = 1;
पूर्ण

/**
 * mei_hbm_version_is_supported - checks whether the driver can
 *     support the hbm version of the device
 *
 * @dev: the device काष्ठाure
 * Return: true अगर driver can support hbm version of the device
 */
bool mei_hbm_version_is_supported(काष्ठा mei_device *dev)
अणु
	वापस	(dev->version.major_version < HBM_MAJOR_VERSION) ||
		(dev->version.major_version == HBM_MAJOR_VERSION &&
		 dev->version.minor_version <= HBM_MINOR_VERSION);
पूर्ण

/**
 * mei_hbm_dispatch - bottom half पढ़ो routine after ISR to
 * handle the पढ़ो bus message cmd processing.
 *
 * @dev: the device काष्ठाure
 * @hdr: header of bus message
 *
 * Return: 0 on success and < 0 on failure
 */
पूर्णांक mei_hbm_dispatch(काष्ठा mei_device *dev, काष्ठा mei_msg_hdr *hdr)
अणु
	काष्ठा mei_bus_message *mei_msg;
	काष्ठा hbm_host_version_response *version_res;
	काष्ठा hbm_props_response *props_res;
	काष्ठा hbm_host_क्रमागत_response *क्रमागत_res;
	काष्ठा hbm_dma_setup_response *dma_setup_res;
	काष्ठा hbm_add_client_request *add_cl_req;
	काष्ठा hbm_capability_response *capability_res;
	पूर्णांक ret;

	काष्ठा mei_hbm_cl_cmd *cl_cmd;
	काष्ठा hbm_client_connect_request *disconnect_req;
	काष्ठा hbm_flow_control *fctrl;
	काष्ठा hbm_client_dma_response *client_dma_res;

	/* पढ़ो the message to our buffer */
	BUG_ON(hdr->length >= माप(dev->rd_msg_buf));
	mei_पढ़ो_slots(dev, dev->rd_msg_buf, hdr->length);
	mei_msg = (काष्ठा mei_bus_message *)dev->rd_msg_buf;
	cl_cmd  = (काष्ठा mei_hbm_cl_cmd *)mei_msg;

	/* ignore spurious message and prevent reset nesting
	 * hbm is put to idle during प्रणाली reset
	 */
	अगर (dev->hbm_state == MEI_HBM_IDLE) अणु
		dev_dbg(dev->dev, "hbm: state is idle ignore spurious messages\n");
		वापस 0;
	पूर्ण

	चयन (mei_msg->hbm_cmd) अणु
	हाल HOST_START_RES_CMD:
		dev_dbg(dev->dev, "hbm: start: response message received.\n");

		dev->init_clients_समयr = 0;

		version_res = (काष्ठा hbm_host_version_response *)mei_msg;

		dev_dbg(dev->dev, "HBM VERSION: DRIVER=%02d:%02d DEVICE=%02d:%02d\n",
				HBM_MAJOR_VERSION, HBM_MINOR_VERSION,
				version_res->me_max_version.major_version,
				version_res->me_max_version.minor_version);

		अगर (version_res->host_version_supported) अणु
			dev->version.major_version = HBM_MAJOR_VERSION;
			dev->version.minor_version = HBM_MINOR_VERSION;
		पूर्ण अन्यथा अणु
			dev->version.major_version =
				version_res->me_max_version.major_version;
			dev->version.minor_version =
				version_res->me_max_version.minor_version;
		पूर्ण

		अगर (!mei_hbm_version_is_supported(dev)) अणु
			dev_warn(dev->dev, "hbm: start: version mismatch - stopping the driver.\n");

			dev->hbm_state = MEI_HBM_STOPPED;
			अगर (mei_hbm_stop_req(dev)) अणु
				dev_err(dev->dev, "hbm: start: failed to send stop request\n");
				वापस -EIO;
			पूर्ण
			अवरोध;
		पूर्ण

		mei_hbm_config_features(dev);

		अगर (dev->dev_state != MEI_DEV_INIT_CLIENTS ||
		    dev->hbm_state != MEI_HBM_STARTING) अणु
			अगर (dev->dev_state == MEI_DEV_POWER_DOWN) अणु
				dev_dbg(dev->dev, "hbm: start: on shutdown, ignoring\n");
				वापस 0;
			पूर्ण
			dev_err(dev->dev, "hbm: start: state mismatch, [%d, %d]\n",
				dev->dev_state, dev->hbm_state);
			वापस -EPROTO;
		पूर्ण

		अगर (dev->hbm_f_cap_supported) अणु
			अगर (mei_hbm_capabilities_req(dev))
				वापस -EIO;
			wake_up(&dev->रुको_hbm_start);
			अवरोध;
		पूर्ण

		अगर (dev->hbm_f_dr_supported) अणु
			अगर (mei_dmam_ring_alloc(dev))
				dev_info(dev->dev, "running w/o dma ring\n");
			अगर (mei_dma_ring_is_allocated(dev)) अणु
				अगर (mei_hbm_dma_setup_req(dev))
					वापस -EIO;

				wake_up(&dev->रुको_hbm_start);
				अवरोध;
			पूर्ण
		पूर्ण

		dev->hbm_f_dr_supported = 0;
		mei_dmam_ring_मुक्त(dev);

		अगर (mei_hbm_क्रमागत_clients_req(dev))
			वापस -EIO;

		wake_up(&dev->रुको_hbm_start);
		अवरोध;

	हाल MEI_HBM_CAPABILITIES_RES_CMD:
		dev_dbg(dev->dev, "hbm: capabilities response: message received.\n");

		dev->init_clients_समयr = 0;

		अगर (dev->dev_state != MEI_DEV_INIT_CLIENTS ||
		    dev->hbm_state != MEI_HBM_CAP_SETUP) अणु
			अगर (dev->dev_state == MEI_DEV_POWER_DOWN) अणु
				dev_dbg(dev->dev, "hbm: capabilities response: on shutdown, ignoring\n");
				वापस 0;
			पूर्ण
			dev_err(dev->dev, "hbm: capabilities response: state mismatch, [%d, %d]\n",
				dev->dev_state, dev->hbm_state);
			वापस -EPROTO;
		पूर्ण

		capability_res = (काष्ठा hbm_capability_response *)mei_msg;
		अगर (!(capability_res->capability_granted[0] & HBM_CAP_VT))
			dev->hbm_f_vt_supported = 0;
		अगर (!(capability_res->capability_granted[0] & HBM_CAP_CD))
			dev->hbm_f_cd_supported = 0;

		अगर (dev->hbm_f_dr_supported) अणु
			अगर (mei_dmam_ring_alloc(dev))
				dev_info(dev->dev, "running w/o dma ring\n");
			अगर (mei_dma_ring_is_allocated(dev)) अणु
				अगर (mei_hbm_dma_setup_req(dev))
					वापस -EIO;
				अवरोध;
			पूर्ण
		पूर्ण

		dev->hbm_f_dr_supported = 0;
		mei_dmam_ring_मुक्त(dev);

		अगर (mei_hbm_क्रमागत_clients_req(dev))
			वापस -EIO;
		अवरोध;

	हाल MEI_HBM_DMA_SETUP_RES_CMD:
		dev_dbg(dev->dev, "hbm: dma setup response: message received.\n");

		dev->init_clients_समयr = 0;

		अगर (dev->dev_state != MEI_DEV_INIT_CLIENTS ||
		    dev->hbm_state != MEI_HBM_DR_SETUP) अणु
			अगर (dev->dev_state == MEI_DEV_POWER_DOWN) अणु
				dev_dbg(dev->dev, "hbm: dma setup response: on shutdown, ignoring\n");
				वापस 0;
			पूर्ण
			dev_err(dev->dev, "hbm: dma setup response: state mismatch, [%d, %d]\n",
				dev->dev_state, dev->hbm_state);
			वापस -EPROTO;
		पूर्ण

		dma_setup_res = (काष्ठा hbm_dma_setup_response *)mei_msg;

		अगर (dma_setup_res->status) अणु
			u8 status = dma_setup_res->status;

			अगर (status == MEI_HBMS_NOT_ALLOWED) अणु
				dev_dbg(dev->dev, "hbm: dma setup not allowed\n");
			पूर्ण अन्यथा अणु
				dev_info(dev->dev, "hbm: dma setup response: failure = %d %s\n",
					 status,
					 mei_hbm_status_str(status));
			पूर्ण
			dev->hbm_f_dr_supported = 0;
			mei_dmam_ring_मुक्त(dev);
		पूर्ण

		अगर (mei_hbm_क्रमागत_clients_req(dev))
			वापस -EIO;
		अवरोध;

	हाल CLIENT_CONNECT_RES_CMD:
		dev_dbg(dev->dev, "hbm: client connect response: message received.\n");
		mei_hbm_cl_res(dev, cl_cmd, MEI_FOP_CONNECT);
		अवरोध;

	हाल CLIENT_DISCONNECT_RES_CMD:
		dev_dbg(dev->dev, "hbm: client disconnect response: message received.\n");
		mei_hbm_cl_res(dev, cl_cmd, MEI_FOP_DISCONNECT);
		अवरोध;

	हाल MEI_FLOW_CONTROL_CMD:
		dev_dbg(dev->dev, "hbm: client flow control response: message received.\n");

		fctrl = (काष्ठा hbm_flow_control *)mei_msg;
		mei_hbm_cl_tx_flow_ctrl_creds_res(dev, fctrl);
		अवरोध;

	हाल MEI_PG_ISOLATION_ENTRY_RES_CMD:
		dev_dbg(dev->dev, "hbm: power gate isolation entry response received\n");
		ret = mei_hbm_pg_enter_res(dev);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल MEI_PG_ISOLATION_EXIT_REQ_CMD:
		dev_dbg(dev->dev, "hbm: power gate isolation exit request received\n");
		ret = mei_hbm_pg_निकास_res(dev);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल HOST_CLIENT_PROPERTIES_RES_CMD:
		dev_dbg(dev->dev, "hbm: properties response: message received.\n");

		dev->init_clients_समयr = 0;

		अगर (dev->dev_state != MEI_DEV_INIT_CLIENTS ||
		    dev->hbm_state != MEI_HBM_CLIENT_PROPERTIES) अणु
			अगर (dev->dev_state == MEI_DEV_POWER_DOWN) अणु
				dev_dbg(dev->dev, "hbm: properties response: on shutdown, ignoring\n");
				वापस 0;
			पूर्ण
			dev_err(dev->dev, "hbm: properties response: state mismatch, [%d, %d]\n",
				dev->dev_state, dev->hbm_state);
			वापस -EPROTO;
		पूर्ण

		props_res = (काष्ठा hbm_props_response *)mei_msg;

		अगर (props_res->status == MEI_HBMS_CLIENT_NOT_FOUND) अणु
			dev_dbg(dev->dev, "hbm: properties response: %d CLIENT_NOT_FOUND\n",
				props_res->me_addr);
		पूर्ण अन्यथा अगर (props_res->status) अणु
			dev_err(dev->dev, "hbm: properties response: wrong status = %d %s\n",
				props_res->status,
				mei_hbm_status_str(props_res->status));
			वापस -EPROTO;
		पूर्ण अन्यथा अणु
			mei_hbm_me_cl_add(dev, props_res);
		पूर्ण

		/* request property क्रम the next client */
		अगर (mei_hbm_prop_req(dev, props_res->me_addr + 1))
			वापस -EIO;

		अवरोध;

	हाल HOST_ENUM_RES_CMD:
		dev_dbg(dev->dev, "hbm: enumeration response: message received\n");

		dev->init_clients_समयr = 0;

		क्रमागत_res = (काष्ठा hbm_host_क्रमागत_response *) mei_msg;
		BUILD_BUG_ON(माप(dev->me_clients_map)
				< माप(क्रमागत_res->valid_addresses));
		स_नकल(dev->me_clients_map, क्रमागत_res->valid_addresses,
				माप(क्रमागत_res->valid_addresses));

		अगर (dev->dev_state != MEI_DEV_INIT_CLIENTS ||
		    dev->hbm_state != MEI_HBM_ENUM_CLIENTS) अणु
			अगर (dev->dev_state == MEI_DEV_POWER_DOWN) अणु
				dev_dbg(dev->dev, "hbm: enumeration response: on shutdown, ignoring\n");
				वापस 0;
			पूर्ण
			dev_err(dev->dev, "hbm: enumeration response: state mismatch, [%d, %d]\n",
				dev->dev_state, dev->hbm_state);
			वापस -EPROTO;
		पूर्ण

		dev->hbm_state = MEI_HBM_CLIENT_PROPERTIES;

		/* first property request */
		अगर (mei_hbm_prop_req(dev, 0))
			वापस -EIO;

		अवरोध;

	हाल HOST_STOP_RES_CMD:
		dev_dbg(dev->dev, "hbm: stop response: message received\n");

		dev->init_clients_समयr = 0;

		अगर (dev->hbm_state != MEI_HBM_STOPPED) अणु
			dev_err(dev->dev, "hbm: stop response: state mismatch, [%d, %d]\n",
				dev->dev_state, dev->hbm_state);
			वापस -EPROTO;
		पूर्ण

		mei_set_devstate(dev, MEI_DEV_POWER_DOWN);
		dev_info(dev->dev, "hbm: stop response: resetting.\n");
		/* क्रमce the reset */
		वापस -EPROTO;

	हाल CLIENT_DISCONNECT_REQ_CMD:
		dev_dbg(dev->dev, "hbm: disconnect request: message received\n");

		disconnect_req = (काष्ठा hbm_client_connect_request *)mei_msg;
		mei_hbm_fw_disconnect_req(dev, disconnect_req);
		अवरोध;

	हाल ME_STOP_REQ_CMD:
		dev_dbg(dev->dev, "hbm: stop request: message received\n");
		dev->hbm_state = MEI_HBM_STOPPED;
		अगर (mei_hbm_stop_req(dev)) अणु
			dev_err(dev->dev, "hbm: stop request: failed to send stop request\n");
			वापस -EIO;
		पूर्ण
		अवरोध;

	हाल MEI_HBM_ADD_CLIENT_REQ_CMD:
		dev_dbg(dev->dev, "hbm: add client request received\n");
		/*
		 * after the host receives the क्रमागत_resp
		 * message clients may be added or हटाओd
		 */
		अगर (dev->hbm_state <= MEI_HBM_ENUM_CLIENTS ||
		    dev->hbm_state >= MEI_HBM_STOPPED) अणु
			dev_err(dev->dev, "hbm: add client: state mismatch, [%d, %d]\n",
				dev->dev_state, dev->hbm_state);
			वापस -EPROTO;
		पूर्ण
		add_cl_req = (काष्ठा hbm_add_client_request *)mei_msg;
		ret = mei_hbm_fw_add_cl_req(dev, add_cl_req);
		अगर (ret) अणु
			dev_err(dev->dev, "hbm: add client: failed to send response %d\n",
				ret);
			वापस -EIO;
		पूर्ण
		dev_dbg(dev->dev, "hbm: add client request processed\n");
		अवरोध;

	हाल MEI_HBM_NOTIFY_RES_CMD:
		dev_dbg(dev->dev, "hbm: notify response received\n");
		mei_hbm_cl_res(dev, cl_cmd, notअगरy_res_to_fop(cl_cmd));
		अवरोध;

	हाल MEI_HBM_NOTIFICATION_CMD:
		dev_dbg(dev->dev, "hbm: notification\n");
		mei_hbm_cl_notअगरy(dev, cl_cmd);
		अवरोध;

	हाल MEI_HBM_CLIENT_DMA_MAP_RES_CMD:
		dev_dbg(dev->dev, "hbm: client dma map response: message received.\n");
		client_dma_res = (काष्ठा hbm_client_dma_response *)mei_msg;
		mei_hbm_cl_dma_map_res(dev, client_dma_res);
		अवरोध;

	हाल MEI_HBM_CLIENT_DMA_UNMAP_RES_CMD:
		dev_dbg(dev->dev, "hbm: client dma unmap response: message received.\n");
		client_dma_res = (काष्ठा hbm_client_dma_response *)mei_msg;
		mei_hbm_cl_dma_unmap_res(dev, client_dma_res);
		अवरोध;

	शेष:
		WARN(1, "hbm: wrong command %d\n", mei_msg->hbm_cmd);
		वापस -EPROTO;

	पूर्ण
	वापस 0;
पूर्ण

