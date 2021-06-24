<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Target based USB-Gadget
 *
 * UAS protocol handling, target callbacks, configfs handling,
 * BBB (USB Mass Storage Class Bulk-Only (BBB) and Transport protocol handling.
 *
 * Author: Sebastian Andrzej Siewior <bigeasy at linutronix करोt de>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/configfs.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/composite.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/storage.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "tcm.h"
#समावेश "u_tcm.h"
#समावेश "configfs.h"

#घोषणा TPG_INSTANCES		1

काष्ठा tpg_instance अणु
	काष्ठा usb_function_instance	*func_inst;
	काष्ठा usbg_tpg			*tpg;
पूर्ण;

अटल काष्ठा tpg_instance tpg_instances[TPG_INSTANCES];

अटल DEFINE_MUTEX(tpg_instances_lock);

अटल अंतरभूत काष्ठा f_uas *to_f_uas(काष्ठा usb_function *f)
अणु
	वापस container_of(f, काष्ठा f_uas, function);
पूर्ण

/* Start bot.c code */

अटल पूर्णांक bot_enqueue_cmd_cbw(काष्ठा f_uas *fu)
अणु
	पूर्णांक ret;

	अगर (fu->flags & USBG_BOT_CMD_PEND)
		वापस 0;

	ret = usb_ep_queue(fu->ep_out, fu->cmd.req, GFP_ATOMIC);
	अगर (!ret)
		fu->flags |= USBG_BOT_CMD_PEND;
	वापस ret;
पूर्ण

अटल व्योम bot_status_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा usbg_cmd *cmd = req->context;
	काष्ठा f_uas *fu = cmd->fu;

	transport_generic_मुक्त_cmd(&cmd->se_cmd, 0);
	अगर (req->status < 0) अणु
		pr_err("ERR %s(%d)\n", __func__, __LINE__);
		वापस;
	पूर्ण

	/* CSW completed, रुको क्रम next CBW */
	bot_enqueue_cmd_cbw(fu);
पूर्ण

अटल व्योम bot_enqueue_sense_code(काष्ठा f_uas *fu, काष्ठा usbg_cmd *cmd)
अणु
	काष्ठा bulk_cs_wrap *csw = &fu->bot_status.csw;
	पूर्णांक ret;
	अचिन्हित पूर्णांक csw_stat;

	csw_stat = cmd->csw_code;
	csw->Tag = cmd->bot_tag;
	csw->Status = csw_stat;
	fu->bot_status.req->context = cmd;
	ret = usb_ep_queue(fu->ep_in, fu->bot_status.req, GFP_ATOMIC);
	अगर (ret)
		pr_err("%s(%d) ERR: %d\n", __func__, __LINE__, ret);
पूर्ण

अटल व्योम bot_err_compl(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा usbg_cmd *cmd = req->context;
	काष्ठा f_uas *fu = cmd->fu;

	अगर (req->status < 0)
		pr_err("ERR %s(%d)\n", __func__, __LINE__);

	अगर (cmd->data_len) अणु
		अगर (cmd->data_len > ep->maxpacket) अणु
			req->length = ep->maxpacket;
			cmd->data_len -= ep->maxpacket;
		पूर्ण अन्यथा अणु
			req->length = cmd->data_len;
			cmd->data_len = 0;
		पूर्ण

		usb_ep_queue(ep, req, GFP_ATOMIC);
		वापस;
	पूर्ण
	bot_enqueue_sense_code(fu, cmd);
पूर्ण

अटल व्योम bot_send_bad_status(काष्ठा usbg_cmd *cmd)
अणु
	काष्ठा f_uas *fu = cmd->fu;
	काष्ठा bulk_cs_wrap *csw = &fu->bot_status.csw;
	काष्ठा usb_request *req;
	काष्ठा usb_ep *ep;

	csw->Residue = cpu_to_le32(cmd->data_len);

	अगर (cmd->data_len) अणु
		अगर (cmd->is_पढ़ो) अणु
			ep = fu->ep_in;
			req = fu->bot_req_in;
		पूर्ण अन्यथा अणु
			ep = fu->ep_out;
			req = fu->bot_req_out;
		पूर्ण

		अगर (cmd->data_len > fu->ep_in->maxpacket) अणु
			req->length = ep->maxpacket;
			cmd->data_len -= ep->maxpacket;
		पूर्ण अन्यथा अणु
			req->length = cmd->data_len;
			cmd->data_len = 0;
		पूर्ण
		req->complete = bot_err_compl;
		req->context = cmd;
		req->buf = fu->cmd.buf;
		usb_ep_queue(ep, req, GFP_KERNEL);
	पूर्ण अन्यथा अणु
		bot_enqueue_sense_code(fu, cmd);
	पूर्ण
पूर्ण

अटल पूर्णांक bot_send_status(काष्ठा usbg_cmd *cmd, bool moved_data)
अणु
	काष्ठा f_uas *fu = cmd->fu;
	काष्ठा bulk_cs_wrap *csw = &fu->bot_status.csw;
	पूर्णांक ret;

	अगर (cmd->se_cmd.scsi_status == SAM_STAT_GOOD) अणु
		अगर (!moved_data && cmd->data_len) अणु
			/*
			 * the host wants to move data, we करोn't. Fill / empty
			 * the pipe and then send the csw with reside set.
			 */
			cmd->csw_code = US_BULK_STAT_OK;
			bot_send_bad_status(cmd);
			वापस 0;
		पूर्ण

		csw->Tag = cmd->bot_tag;
		csw->Residue = cpu_to_le32(0);
		csw->Status = US_BULK_STAT_OK;
		fu->bot_status.req->context = cmd;

		ret = usb_ep_queue(fu->ep_in, fu->bot_status.req, GFP_KERNEL);
		अगर (ret)
			pr_err("%s(%d) ERR: %d\n", __func__, __LINE__, ret);
	पूर्ण अन्यथा अणु
		cmd->csw_code = US_BULK_STAT_FAIL;
		bot_send_bad_status(cmd);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Called after command (no data transfer) or after the ग_लिखो (to device)
 * operation is completed
 */
अटल पूर्णांक bot_send_status_response(काष्ठा usbg_cmd *cmd)
अणु
	bool moved_data = false;

	अगर (!cmd->is_पढ़ो)
		moved_data = true;
	वापस bot_send_status(cmd, moved_data);
पूर्ण

/* Read request completed, now we have to send the CSW */
अटल व्योम bot_पढ़ो_compl(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा usbg_cmd *cmd = req->context;

	अगर (req->status < 0)
		pr_err("ERR %s(%d)\n", __func__, __LINE__);

	bot_send_status(cmd, true);
पूर्ण

अटल पूर्णांक bot_send_पढ़ो_response(काष्ठा usbg_cmd *cmd)
अणु
	काष्ठा f_uas *fu = cmd->fu;
	काष्ठा se_cmd *se_cmd = &cmd->se_cmd;
	काष्ठा usb_gadget *gadget = fuas_to_gadget(fu);
	पूर्णांक ret;

	अगर (!cmd->data_len) अणु
		cmd->csw_code = US_BULK_STAT_PHASE;
		bot_send_bad_status(cmd);
		वापस 0;
	पूर्ण

	अगर (!gadget->sg_supported) अणु
		cmd->data_buf = kदो_स्मृति(se_cmd->data_length, GFP_ATOMIC);
		अगर (!cmd->data_buf)
			वापस -ENOMEM;

		sg_copy_to_buffer(se_cmd->t_data_sg,
				se_cmd->t_data_nents,
				cmd->data_buf,
				se_cmd->data_length);

		fu->bot_req_in->buf = cmd->data_buf;
	पूर्ण अन्यथा अणु
		fu->bot_req_in->buf = शून्य;
		fu->bot_req_in->num_sgs = se_cmd->t_data_nents;
		fu->bot_req_in->sg = se_cmd->t_data_sg;
	पूर्ण

	fu->bot_req_in->complete = bot_पढ़ो_compl;
	fu->bot_req_in->length = se_cmd->data_length;
	fu->bot_req_in->context = cmd;
	ret = usb_ep_queue(fu->ep_in, fu->bot_req_in, GFP_ATOMIC);
	अगर (ret)
		pr_err("%s(%d)\n", __func__, __LINE__);
	वापस 0;
पूर्ण

अटल व्योम usbg_data_ग_लिखो_cmpl(काष्ठा usb_ep *, काष्ठा usb_request *);
अटल पूर्णांक usbg_prepare_w_request(काष्ठा usbg_cmd *, काष्ठा usb_request *);

अटल पूर्णांक bot_send_ग_लिखो_request(काष्ठा usbg_cmd *cmd)
अणु
	काष्ठा f_uas *fu = cmd->fu;
	काष्ठा se_cmd *se_cmd = &cmd->se_cmd;
	काष्ठा usb_gadget *gadget = fuas_to_gadget(fu);
	पूर्णांक ret;

	init_completion(&cmd->ग_लिखो_complete);
	cmd->fu = fu;

	अगर (!cmd->data_len) अणु
		cmd->csw_code = US_BULK_STAT_PHASE;
		वापस -EINVAL;
	पूर्ण

	अगर (!gadget->sg_supported) अणु
		cmd->data_buf = kदो_स्मृति(se_cmd->data_length, GFP_KERNEL);
		अगर (!cmd->data_buf)
			वापस -ENOMEM;

		fu->bot_req_out->buf = cmd->data_buf;
	पूर्ण अन्यथा अणु
		fu->bot_req_out->buf = शून्य;
		fu->bot_req_out->num_sgs = se_cmd->t_data_nents;
		fu->bot_req_out->sg = se_cmd->t_data_sg;
	पूर्ण

	fu->bot_req_out->complete = usbg_data_ग_लिखो_cmpl;
	fu->bot_req_out->length = se_cmd->data_length;
	fu->bot_req_out->context = cmd;

	ret = usbg_prepare_w_request(cmd, fu->bot_req_out);
	अगर (ret)
		जाओ cleanup;
	ret = usb_ep_queue(fu->ep_out, fu->bot_req_out, GFP_KERNEL);
	अगर (ret)
		pr_err("%s(%d)\n", __func__, __LINE__);

	रुको_क्रम_completion(&cmd->ग_लिखो_complete);
	target_execute_cmd(se_cmd);
cleanup:
	वापस ret;
पूर्ण

अटल पूर्णांक bot_submit_command(काष्ठा f_uas *, व्योम *, अचिन्हित पूर्णांक);

अटल व्योम bot_cmd_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा f_uas *fu = req->context;
	पूर्णांक ret;

	fu->flags &= ~USBG_BOT_CMD_PEND;

	अगर (req->status < 0)
		वापस;

	ret = bot_submit_command(fu, req->buf, req->actual);
	अगर (ret)
		pr_err("%s(%d): %d\n", __func__, __LINE__, ret);
पूर्ण

अटल पूर्णांक bot_prepare_reqs(काष्ठा f_uas *fu)
अणु
	पूर्णांक ret;

	fu->bot_req_in = usb_ep_alloc_request(fu->ep_in, GFP_KERNEL);
	अगर (!fu->bot_req_in)
		जाओ err;

	fu->bot_req_out = usb_ep_alloc_request(fu->ep_out, GFP_KERNEL);
	अगर (!fu->bot_req_out)
		जाओ err_out;

	fu->cmd.req = usb_ep_alloc_request(fu->ep_out, GFP_KERNEL);
	अगर (!fu->cmd.req)
		जाओ err_cmd;

	fu->bot_status.req = usb_ep_alloc_request(fu->ep_in, GFP_KERNEL);
	अगर (!fu->bot_status.req)
		जाओ err_sts;

	fu->bot_status.req->buf = &fu->bot_status.csw;
	fu->bot_status.req->length = US_BULK_CS_WRAP_LEN;
	fu->bot_status.req->complete = bot_status_complete;
	fu->bot_status.csw.Signature = cpu_to_le32(US_BULK_CS_SIGN);

	fu->cmd.buf = kदो_स्मृति(fu->ep_out->maxpacket, GFP_KERNEL);
	अगर (!fu->cmd.buf)
		जाओ err_buf;

	fu->cmd.req->complete = bot_cmd_complete;
	fu->cmd.req->buf = fu->cmd.buf;
	fu->cmd.req->length = fu->ep_out->maxpacket;
	fu->cmd.req->context = fu;

	ret = bot_enqueue_cmd_cbw(fu);
	अगर (ret)
		जाओ err_queue;
	वापस 0;
err_queue:
	kमुक्त(fu->cmd.buf);
	fu->cmd.buf = शून्य;
err_buf:
	usb_ep_मुक्त_request(fu->ep_in, fu->bot_status.req);
err_sts:
	usb_ep_मुक्त_request(fu->ep_out, fu->cmd.req);
	fu->cmd.req = शून्य;
err_cmd:
	usb_ep_मुक्त_request(fu->ep_out, fu->bot_req_out);
	fu->bot_req_out = शून्य;
err_out:
	usb_ep_मुक्त_request(fu->ep_in, fu->bot_req_in);
	fu->bot_req_in = शून्य;
err:
	pr_err("BOT: endpoint setup failed\n");
	वापस -ENOMEM;
पूर्ण

अटल व्योम bot_cleanup_old_alt(काष्ठा f_uas *fu)
अणु
	अगर (!(fu->flags & USBG_ENABLED))
		वापस;

	usb_ep_disable(fu->ep_in);
	usb_ep_disable(fu->ep_out);

	अगर (!fu->bot_req_in)
		वापस;

	usb_ep_मुक्त_request(fu->ep_in, fu->bot_req_in);
	usb_ep_मुक्त_request(fu->ep_out, fu->bot_req_out);
	usb_ep_मुक्त_request(fu->ep_out, fu->cmd.req);
	usb_ep_मुक्त_request(fu->ep_in, fu->bot_status.req);

	kमुक्त(fu->cmd.buf);

	fu->bot_req_in = शून्य;
	fu->bot_req_out = शून्य;
	fu->cmd.req = शून्य;
	fu->bot_status.req = शून्य;
	fu->cmd.buf = शून्य;
पूर्ण

अटल व्योम bot_set_alt(काष्ठा f_uas *fu)
अणु
	काष्ठा usb_function *f = &fu->function;
	काष्ठा usb_gadget *gadget = f->config->cdev->gadget;
	पूर्णांक ret;

	fu->flags = USBG_IS_BOT;

	config_ep_by_speed_and_alt(gadget, f, fu->ep_in, USB_G_ALT_INT_BBB);
	ret = usb_ep_enable(fu->ep_in);
	अगर (ret)
		जाओ err_b_in;

	config_ep_by_speed_and_alt(gadget, f, fu->ep_out, USB_G_ALT_INT_BBB);
	ret = usb_ep_enable(fu->ep_out);
	अगर (ret)
		जाओ err_b_out;

	ret = bot_prepare_reqs(fu);
	अगर (ret)
		जाओ err_wq;
	fu->flags |= USBG_ENABLED;
	pr_info("Using the BOT protocol\n");
	वापस;
err_wq:
	usb_ep_disable(fu->ep_out);
err_b_out:
	usb_ep_disable(fu->ep_in);
err_b_in:
	fu->flags = USBG_IS_BOT;
पूर्ण

अटल पूर्णांक usbg_bot_setup(काष्ठा usb_function *f,
		स्थिर काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा f_uas *fu = to_f_uas(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;
	u16 w_value = le16_to_cpu(ctrl->wValue);
	u16 w_length = le16_to_cpu(ctrl->wLength);
	पूर्णांक luns;
	u8 *ret_lun;

	चयन (ctrl->bRequest) अणु
	हाल US_BULK_GET_MAX_LUN:
		अगर (ctrl->bRequestType != (USB_सूची_IN | USB_TYPE_CLASS |
					USB_RECIP_INTERFACE))
			वापस -ENOTSUPP;

		अगर (w_length < 1)
			वापस -EINVAL;
		अगर (w_value != 0)
			वापस -EINVAL;
		luns = atomic_पढ़ो(&fu->tpg->tpg_port_count);
		अगर (!luns) अणु
			pr_err("No LUNs configured?\n");
			वापस -EINVAL;
		पूर्ण
		/*
		 * If 4 LUNs are present we वापस 3 i.e. LUN 0..3 can be
		 * accessed. The upper limit is 0xf
		 */
		luns--;
		अगर (luns > 0xf) अणु
			pr_info_once("Limiting the number of luns to 16\n");
			luns = 0xf;
		पूर्ण
		ret_lun = cdev->req->buf;
		*ret_lun = luns;
		cdev->req->length = 1;
		वापस usb_ep_queue(cdev->gadget->ep0, cdev->req, GFP_ATOMIC);

	हाल US_BULK_RESET_REQUEST:
		/* XXX maybe we should हटाओ previous requests क्रम IN + OUT */
		bot_enqueue_cmd_cbw(fu);
		वापस 0;
	पूर्ण
	वापस -ENOTSUPP;
पूर्ण

/* Start uas.c code */

अटल व्योम uasp_cleanup_one_stream(काष्ठा f_uas *fu, काष्ठा uas_stream *stream)
अणु
	/* We have either all three allocated or none */
	अगर (!stream->req_in)
		वापस;

	usb_ep_मुक्त_request(fu->ep_in, stream->req_in);
	usb_ep_मुक्त_request(fu->ep_out, stream->req_out);
	usb_ep_मुक्त_request(fu->ep_status, stream->req_status);

	stream->req_in = शून्य;
	stream->req_out = शून्य;
	stream->req_status = शून्य;
पूर्ण

अटल व्योम uasp_मुक्त_cmdreq(काष्ठा f_uas *fu)
अणु
	usb_ep_मुक्त_request(fu->ep_cmd, fu->cmd.req);
	kमुक्त(fu->cmd.buf);
	fu->cmd.req = शून्य;
	fu->cmd.buf = शून्य;
पूर्ण

अटल व्योम uasp_cleanup_old_alt(काष्ठा f_uas *fu)
अणु
	पूर्णांक i;

	अगर (!(fu->flags & USBG_ENABLED))
		वापस;

	usb_ep_disable(fu->ep_in);
	usb_ep_disable(fu->ep_out);
	usb_ep_disable(fu->ep_status);
	usb_ep_disable(fu->ep_cmd);

	क्रम (i = 0; i < UASP_SS_EP_COMP_NUM_STREAMS; i++)
		uasp_cleanup_one_stream(fu, &fu->stream[i]);
	uasp_मुक्त_cmdreq(fu);
पूर्ण

अटल व्योम uasp_status_data_cmpl(काष्ठा usb_ep *ep, काष्ठा usb_request *req);

अटल पूर्णांक uasp_prepare_r_request(काष्ठा usbg_cmd *cmd)
अणु
	काष्ठा se_cmd *se_cmd = &cmd->se_cmd;
	काष्ठा f_uas *fu = cmd->fu;
	काष्ठा usb_gadget *gadget = fuas_to_gadget(fu);
	काष्ठा uas_stream *stream = cmd->stream;

	अगर (!gadget->sg_supported) अणु
		cmd->data_buf = kदो_स्मृति(se_cmd->data_length, GFP_ATOMIC);
		अगर (!cmd->data_buf)
			वापस -ENOMEM;

		sg_copy_to_buffer(se_cmd->t_data_sg,
				se_cmd->t_data_nents,
				cmd->data_buf,
				se_cmd->data_length);

		stream->req_in->buf = cmd->data_buf;
	पूर्ण अन्यथा अणु
		stream->req_in->buf = शून्य;
		stream->req_in->num_sgs = se_cmd->t_data_nents;
		stream->req_in->sg = se_cmd->t_data_sg;
	पूर्ण

	stream->req_in->is_last = 1;
	stream->req_in->complete = uasp_status_data_cmpl;
	stream->req_in->length = se_cmd->data_length;
	stream->req_in->context = cmd;

	cmd->state = UASP_SEND_STATUS;
	वापस 0;
पूर्ण

अटल व्योम uasp_prepare_status(काष्ठा usbg_cmd *cmd)
अणु
	काष्ठा se_cmd *se_cmd = &cmd->se_cmd;
	काष्ठा sense_iu *iu = &cmd->sense_iu;
	काष्ठा uas_stream *stream = cmd->stream;

	cmd->state = UASP_QUEUE_COMMAND;
	iu->iu_id = IU_ID_STATUS;
	iu->tag = cpu_to_be16(cmd->tag);

	/*
	 * iu->status_qual = cpu_to_be16(STATUS QUALIFIER SAM-4. Where R U?);
	 */
	iu->len = cpu_to_be16(se_cmd->scsi_sense_length);
	iu->status = se_cmd->scsi_status;
	stream->req_status->is_last = 1;
	stream->req_status->context = cmd;
	stream->req_status->length = se_cmd->scsi_sense_length + 16;
	stream->req_status->buf = iu;
	stream->req_status->complete = uasp_status_data_cmpl;
पूर्ण

अटल व्योम uasp_status_data_cmpl(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा usbg_cmd *cmd = req->context;
	काष्ठा uas_stream *stream = cmd->stream;
	काष्ठा f_uas *fu = cmd->fu;
	पूर्णांक ret;

	अगर (req->status < 0)
		जाओ cleanup;

	चयन (cmd->state) अणु
	हाल UASP_SEND_DATA:
		ret = uasp_prepare_r_request(cmd);
		अगर (ret)
			जाओ cleanup;
		ret = usb_ep_queue(fu->ep_in, stream->req_in, GFP_ATOMIC);
		अगर (ret)
			pr_err("%s(%d) => %d\n", __func__, __LINE__, ret);
		अवरोध;

	हाल UASP_RECEIVE_DATA:
		ret = usbg_prepare_w_request(cmd, stream->req_out);
		अगर (ret)
			जाओ cleanup;
		ret = usb_ep_queue(fu->ep_out, stream->req_out, GFP_ATOMIC);
		अगर (ret)
			pr_err("%s(%d) => %d\n", __func__, __LINE__, ret);
		अवरोध;

	हाल UASP_SEND_STATUS:
		uasp_prepare_status(cmd);
		ret = usb_ep_queue(fu->ep_status, stream->req_status,
				GFP_ATOMIC);
		अगर (ret)
			pr_err("%s(%d) => %d\n", __func__, __LINE__, ret);
		अवरोध;

	हाल UASP_QUEUE_COMMAND:
		transport_generic_मुक्त_cmd(&cmd->se_cmd, 0);
		usb_ep_queue(fu->ep_cmd, fu->cmd.req, GFP_ATOMIC);
		अवरोध;

	शेष:
		BUG();
	पूर्ण
	वापस;

cleanup:
	transport_generic_मुक्त_cmd(&cmd->se_cmd, 0);
पूर्ण

अटल पूर्णांक uasp_send_status_response(काष्ठा usbg_cmd *cmd)
अणु
	काष्ठा f_uas *fu = cmd->fu;
	काष्ठा uas_stream *stream = cmd->stream;
	काष्ठा sense_iu *iu = &cmd->sense_iu;

	iu->tag = cpu_to_be16(cmd->tag);
	stream->req_status->complete = uasp_status_data_cmpl;
	stream->req_status->context = cmd;
	cmd->fu = fu;
	uasp_prepare_status(cmd);
	वापस usb_ep_queue(fu->ep_status, stream->req_status, GFP_ATOMIC);
पूर्ण

अटल पूर्णांक uasp_send_पढ़ो_response(काष्ठा usbg_cmd *cmd)
अणु
	काष्ठा f_uas *fu = cmd->fu;
	काष्ठा uas_stream *stream = cmd->stream;
	काष्ठा sense_iu *iu = &cmd->sense_iu;
	पूर्णांक ret;

	cmd->fu = fu;

	iu->tag = cpu_to_be16(cmd->tag);
	अगर (fu->flags & USBG_USE_STREAMS) अणु

		ret = uasp_prepare_r_request(cmd);
		अगर (ret)
			जाओ out;
		ret = usb_ep_queue(fu->ep_in, stream->req_in, GFP_ATOMIC);
		अगर (ret) अणु
			pr_err("%s(%d) => %d\n", __func__, __LINE__, ret);
			kमुक्त(cmd->data_buf);
			cmd->data_buf = शून्य;
		पूर्ण

	पूर्ण अन्यथा अणु

		iu->iu_id = IU_ID_READ_READY;
		iu->tag = cpu_to_be16(cmd->tag);

		stream->req_status->complete = uasp_status_data_cmpl;
		stream->req_status->context = cmd;

		cmd->state = UASP_SEND_DATA;
		stream->req_status->buf = iu;
		stream->req_status->length = माप(काष्ठा iu);

		ret = usb_ep_queue(fu->ep_status, stream->req_status,
				GFP_ATOMIC);
		अगर (ret)
			pr_err("%s(%d) => %d\n", __func__, __LINE__, ret);
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक uasp_send_ग_लिखो_request(काष्ठा usbg_cmd *cmd)
अणु
	काष्ठा f_uas *fu = cmd->fu;
	काष्ठा se_cmd *se_cmd = &cmd->se_cmd;
	काष्ठा uas_stream *stream = cmd->stream;
	काष्ठा sense_iu *iu = &cmd->sense_iu;
	पूर्णांक ret;

	init_completion(&cmd->ग_लिखो_complete);
	cmd->fu = fu;

	iu->tag = cpu_to_be16(cmd->tag);

	अगर (fu->flags & USBG_USE_STREAMS) अणु

		ret = usbg_prepare_w_request(cmd, stream->req_out);
		अगर (ret)
			जाओ cleanup;
		ret = usb_ep_queue(fu->ep_out, stream->req_out, GFP_ATOMIC);
		अगर (ret)
			pr_err("%s(%d)\n", __func__, __LINE__);

	पूर्ण अन्यथा अणु

		iu->iu_id = IU_ID_WRITE_READY;
		iu->tag = cpu_to_be16(cmd->tag);

		stream->req_status->complete = uasp_status_data_cmpl;
		stream->req_status->context = cmd;

		cmd->state = UASP_RECEIVE_DATA;
		stream->req_status->buf = iu;
		stream->req_status->length = माप(काष्ठा iu);

		ret = usb_ep_queue(fu->ep_status, stream->req_status,
				GFP_ATOMIC);
		अगर (ret)
			pr_err("%s(%d)\n", __func__, __LINE__);
	पूर्ण

	रुको_क्रम_completion(&cmd->ग_लिखो_complete);
	target_execute_cmd(se_cmd);
cleanup:
	वापस ret;
पूर्ण

अटल पूर्णांक usbg_submit_command(काष्ठा f_uas *, व्योम *, अचिन्हित पूर्णांक);

अटल व्योम uasp_cmd_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा f_uas *fu = req->context;
	पूर्णांक ret;

	अगर (req->status < 0)
		वापस;

	ret = usbg_submit_command(fu, req->buf, req->actual);
	/*
	 * Once we tune क्रम perक्रमmance enqueue the command req here again so
	 * we can receive a second command जबतक we processing this one. Pay
	 * attention to properly sync STAUS endpoपूर्णांक with DATA IN + OUT so you
	 * करोn't अवरोध HS.
	 */
	अगर (!ret)
		वापस;
	usb_ep_queue(fu->ep_cmd, fu->cmd.req, GFP_ATOMIC);
पूर्ण

अटल पूर्णांक uasp_alloc_stream_res(काष्ठा f_uas *fu, काष्ठा uas_stream *stream)
अणु
	stream->req_in = usb_ep_alloc_request(fu->ep_in, GFP_KERNEL);
	अगर (!stream->req_in)
		जाओ out;

	stream->req_out = usb_ep_alloc_request(fu->ep_out, GFP_KERNEL);
	अगर (!stream->req_out)
		जाओ err_out;

	stream->req_status = usb_ep_alloc_request(fu->ep_status, GFP_KERNEL);
	अगर (!stream->req_status)
		जाओ err_sts;

	वापस 0;

err_sts:
	usb_ep_मुक्त_request(fu->ep_out, stream->req_out);
	stream->req_out = शून्य;
err_out:
	usb_ep_मुक्त_request(fu->ep_in, stream->req_in);
	stream->req_in = शून्य;
out:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक uasp_alloc_cmd(काष्ठा f_uas *fu)
अणु
	fu->cmd.req = usb_ep_alloc_request(fu->ep_cmd, GFP_KERNEL);
	अगर (!fu->cmd.req)
		जाओ err;

	fu->cmd.buf = kदो_स्मृति(fu->ep_cmd->maxpacket, GFP_KERNEL);
	अगर (!fu->cmd.buf)
		जाओ err_buf;

	fu->cmd.req->complete = uasp_cmd_complete;
	fu->cmd.req->buf = fu->cmd.buf;
	fu->cmd.req->length = fu->ep_cmd->maxpacket;
	fu->cmd.req->context = fu;
	वापस 0;

err_buf:
	usb_ep_मुक्त_request(fu->ep_cmd, fu->cmd.req);
err:
	वापस -ENOMEM;
पूर्ण

अटल व्योम uasp_setup_stream_res(काष्ठा f_uas *fu, पूर्णांक max_streams)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < max_streams; i++) अणु
		काष्ठा uas_stream *s = &fu->stream[i];

		s->req_in->stream_id = i + 1;
		s->req_out->stream_id = i + 1;
		s->req_status->stream_id = i + 1;
	पूर्ण
पूर्ण

अटल पूर्णांक uasp_prepare_reqs(काष्ठा f_uas *fu)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक max_streams;

	अगर (fu->flags & USBG_USE_STREAMS)
		max_streams = UASP_SS_EP_COMP_NUM_STREAMS;
	अन्यथा
		max_streams = 1;

	क्रम (i = 0; i < max_streams; i++) अणु
		ret = uasp_alloc_stream_res(fu, &fu->stream[i]);
		अगर (ret)
			जाओ err_cleanup;
	पूर्ण

	ret = uasp_alloc_cmd(fu);
	अगर (ret)
		जाओ err_मुक्त_stream;
	uasp_setup_stream_res(fu, max_streams);

	ret = usb_ep_queue(fu->ep_cmd, fu->cmd.req, GFP_ATOMIC);
	अगर (ret)
		जाओ err_मुक्त_stream;

	वापस 0;

err_मुक्त_stream:
	uasp_मुक्त_cmdreq(fu);

err_cleanup:
	अगर (i) अणु
		करो अणु
			uasp_cleanup_one_stream(fu, &fu->stream[i - 1]);
			i--;
		पूर्ण जबतक (i);
	पूर्ण
	pr_err("UASP: endpoint setup failed\n");
	वापस ret;
पूर्ण

अटल व्योम uasp_set_alt(काष्ठा f_uas *fu)
अणु
	काष्ठा usb_function *f = &fu->function;
	काष्ठा usb_gadget *gadget = f->config->cdev->gadget;
	पूर्णांक ret;

	fu->flags = USBG_IS_UAS;

	अगर (gadget->speed >= USB_SPEED_SUPER)
		fu->flags |= USBG_USE_STREAMS;

	config_ep_by_speed_and_alt(gadget, f, fu->ep_in, USB_G_ALT_INT_UAS);
	ret = usb_ep_enable(fu->ep_in);
	अगर (ret)
		जाओ err_b_in;

	config_ep_by_speed_and_alt(gadget, f, fu->ep_out, USB_G_ALT_INT_UAS);
	ret = usb_ep_enable(fu->ep_out);
	अगर (ret)
		जाओ err_b_out;

	config_ep_by_speed_and_alt(gadget, f, fu->ep_cmd, USB_G_ALT_INT_UAS);
	ret = usb_ep_enable(fu->ep_cmd);
	अगर (ret)
		जाओ err_cmd;
	config_ep_by_speed_and_alt(gadget, f, fu->ep_status, USB_G_ALT_INT_UAS);
	ret = usb_ep_enable(fu->ep_status);
	अगर (ret)
		जाओ err_status;

	ret = uasp_prepare_reqs(fu);
	अगर (ret)
		जाओ err_wq;
	fu->flags |= USBG_ENABLED;

	pr_info("Using the UAS protocol\n");
	वापस;
err_wq:
	usb_ep_disable(fu->ep_status);
err_status:
	usb_ep_disable(fu->ep_cmd);
err_cmd:
	usb_ep_disable(fu->ep_out);
err_b_out:
	usb_ep_disable(fu->ep_in);
err_b_in:
	fu->flags = 0;
पूर्ण

अटल पूर्णांक get_cmd_dir(स्थिर अचिन्हित अक्षर *cdb)
अणु
	पूर्णांक ret;

	चयन (cdb[0]) अणु
	हाल READ_6:
	हाल READ_10:
	हाल READ_12:
	हाल READ_16:
	हाल INQUIRY:
	हाल MODE_SENSE:
	हाल MODE_SENSE_10:
	हाल SERVICE_ACTION_IN_16:
	हाल MAINTEन_अंकCE_IN:
	हाल PERSISTENT_RESERVE_IN:
	हाल SECURITY_PROTOCOL_IN:
	हाल ACCESS_CONTROL_IN:
	हाल REPORT_LUNS:
	हाल READ_BLOCK_LIMITS:
	हाल READ_POSITION:
	हाल READ_CAPACITY:
	हाल READ_TOC:
	हाल READ_FORMAT_CAPACITIES:
	हाल REQUEST_SENSE:
		ret = DMA_FROM_DEVICE;
		अवरोध;

	हाल WRITE_6:
	हाल WRITE_10:
	हाल WRITE_12:
	हाल WRITE_16:
	हाल MODE_SELECT:
	हाल MODE_SELECT_10:
	हाल WRITE_VERIFY:
	हाल WRITE_VERIFY_12:
	हाल PERSISTENT_RESERVE_OUT:
	हाल MAINTEन_अंकCE_OUT:
	हाल SECURITY_PROTOCOL_OUT:
	हाल ACCESS_CONTROL_OUT:
		ret = DMA_TO_DEVICE;
		अवरोध;
	हाल ALLOW_MEDIUM_REMOVAL:
	हाल TEST_UNIT_READY:
	हाल SYNCHRONIZE_CACHE:
	हाल START_STOP:
	हाल ERASE:
	हाल REZERO_UNIT:
	हाल SEEK_10:
	हाल SPACE:
	हाल VERIFY:
	हाल WRITE_खाताMARKS:
		ret = DMA_NONE;
		अवरोध;
	शेष:
#घोषणा CMD_सूची_MSG "target: Unknown data direction for SCSI Opcode 0x%02x\n"
		pr_warn(CMD_सूची_MSG, cdb[0]);
#अघोषित CMD_सूची_MSG
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम usbg_data_ग_लिखो_cmpl(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा usbg_cmd *cmd = req->context;
	काष्ठा se_cmd *se_cmd = &cmd->se_cmd;

	अगर (req->status < 0) अणु
		pr_err("%s() state %d transfer failed\n", __func__, cmd->state);
		जाओ cleanup;
	पूर्ण

	अगर (req->num_sgs == 0) अणु
		sg_copy_from_buffer(se_cmd->t_data_sg,
				se_cmd->t_data_nents,
				cmd->data_buf,
				se_cmd->data_length);
	पूर्ण

	complete(&cmd->ग_लिखो_complete);
	वापस;

cleanup:
	transport_generic_मुक्त_cmd(&cmd->se_cmd, 0);
पूर्ण

अटल पूर्णांक usbg_prepare_w_request(काष्ठा usbg_cmd *cmd, काष्ठा usb_request *req)
अणु
	काष्ठा se_cmd *se_cmd = &cmd->se_cmd;
	काष्ठा f_uas *fu = cmd->fu;
	काष्ठा usb_gadget *gadget = fuas_to_gadget(fu);

	अगर (!gadget->sg_supported) अणु
		cmd->data_buf = kदो_स्मृति(se_cmd->data_length, GFP_ATOMIC);
		अगर (!cmd->data_buf)
			वापस -ENOMEM;

		req->buf = cmd->data_buf;
	पूर्ण अन्यथा अणु
		req->buf = शून्य;
		req->num_sgs = se_cmd->t_data_nents;
		req->sg = se_cmd->t_data_sg;
	पूर्ण

	req->is_last = 1;
	req->complete = usbg_data_ग_लिखो_cmpl;
	req->length = se_cmd->data_length;
	req->context = cmd;
	वापस 0;
पूर्ण

अटल पूर्णांक usbg_send_status_response(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा usbg_cmd *cmd = container_of(se_cmd, काष्ठा usbg_cmd,
			se_cmd);
	काष्ठा f_uas *fu = cmd->fu;

	अगर (fu->flags & USBG_IS_BOT)
		वापस bot_send_status_response(cmd);
	अन्यथा
		वापस uasp_send_status_response(cmd);
पूर्ण

अटल पूर्णांक usbg_send_ग_लिखो_request(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा usbg_cmd *cmd = container_of(se_cmd, काष्ठा usbg_cmd,
			se_cmd);
	काष्ठा f_uas *fu = cmd->fu;

	अगर (fu->flags & USBG_IS_BOT)
		वापस bot_send_ग_लिखो_request(cmd);
	अन्यथा
		वापस uasp_send_ग_लिखो_request(cmd);
पूर्ण

अटल पूर्णांक usbg_send_पढ़ो_response(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा usbg_cmd *cmd = container_of(se_cmd, काष्ठा usbg_cmd,
			se_cmd);
	काष्ठा f_uas *fu = cmd->fu;

	अगर (fu->flags & USBG_IS_BOT)
		वापस bot_send_पढ़ो_response(cmd);
	अन्यथा
		वापस uasp_send_पढ़ो_response(cmd);
पूर्ण

अटल व्योम usbg_cmd_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा usbg_cmd *cmd = container_of(work, काष्ठा usbg_cmd, work);
	काष्ठा se_cmd *se_cmd;
	काष्ठा tcm_usbg_nexus *tv_nexus;
	काष्ठा usbg_tpg *tpg;
	पूर्णांक dir, flags = (TARGET_SCF_UNKNOWN_SIZE | TARGET_SCF_ACK_KREF);

	se_cmd = &cmd->se_cmd;
	tpg = cmd->fu->tpg;
	tv_nexus = tpg->tpg_nexus;
	dir = get_cmd_dir(cmd->cmd_buf);
	अगर (dir < 0) अणु
		__target_init_cmd(se_cmd,
				  tv_nexus->tvn_se_sess->se_tpg->se_tpg_tfo,
				  tv_nexus->tvn_se_sess, cmd->data_len, DMA_NONE,
				  cmd->prio_attr, cmd->sense_iu.sense,
				  cmd->unpacked_lun);
		जाओ out;
	पूर्ण

	target_submit_cmd(se_cmd, tv_nexus->tvn_se_sess, cmd->cmd_buf,
			  cmd->sense_iu.sense, cmd->unpacked_lun, 0,
			  cmd->prio_attr, dir, flags);
	वापस;

out:
	transport_send_check_condition_and_sense(se_cmd,
			TCM_UNSUPPORTED_SCSI_OPCODE, 1);
	transport_generic_मुक्त_cmd(&cmd->se_cmd, 0);
पूर्ण

अटल काष्ठा usbg_cmd *usbg_get_cmd(काष्ठा f_uas *fu,
		काष्ठा tcm_usbg_nexus *tv_nexus, u32 scsi_tag)
अणु
	काष्ठा se_session *se_sess = tv_nexus->tvn_se_sess;
	काष्ठा usbg_cmd *cmd;
	पूर्णांक tag, cpu;

	tag = sbiपंचांगap_queue_get(&se_sess->sess_tag_pool, &cpu);
	अगर (tag < 0)
		वापस ERR_PTR(-ENOMEM);

	cmd = &((काष्ठा usbg_cmd *)se_sess->sess_cmd_map)[tag];
	स_रखो(cmd, 0, माप(*cmd));
	cmd->se_cmd.map_tag = tag;
	cmd->se_cmd.map_cpu = cpu;
	cmd->se_cmd.tag = cmd->tag = scsi_tag;
	cmd->fu = fu;

	वापस cmd;
पूर्ण

अटल व्योम usbg_release_cmd(काष्ठा se_cmd *);

अटल पूर्णांक usbg_submit_command(काष्ठा f_uas *fu,
		व्योम *cmdbuf, अचिन्हित पूर्णांक len)
अणु
	काष्ठा command_iu *cmd_iu = cmdbuf;
	काष्ठा usbg_cmd *cmd;
	काष्ठा usbg_tpg *tpg = fu->tpg;
	काष्ठा tcm_usbg_nexus *tv_nexus;
	u32 cmd_len;
	u16 scsi_tag;

	अगर (cmd_iu->iu_id != IU_ID_COMMAND) अणु
		pr_err("Unsupported type %d\n", cmd_iu->iu_id);
		वापस -EINVAL;
	पूर्ण

	tv_nexus = tpg->tpg_nexus;
	अगर (!tv_nexus) अणु
		pr_err("Missing nexus, ignoring command\n");
		वापस -EINVAL;
	पूर्ण

	cmd_len = (cmd_iu->len & ~0x3) + 16;
	अगर (cmd_len > USBG_MAX_CMD)
		वापस -EINVAL;

	scsi_tag = be16_to_cpup(&cmd_iu->tag);
	cmd = usbg_get_cmd(fu, tv_nexus, scsi_tag);
	अगर (IS_ERR(cmd)) अणु
		pr_err("usbg_get_cmd failed\n");
		वापस -ENOMEM;
	पूर्ण
	स_नकल(cmd->cmd_buf, cmd_iu->cdb, cmd_len);

	अगर (fu->flags & USBG_USE_STREAMS) अणु
		अगर (cmd->tag > UASP_SS_EP_COMP_NUM_STREAMS)
			जाओ err;
		अगर (!cmd->tag)
			cmd->stream = &fu->stream[0];
		अन्यथा
			cmd->stream = &fu->stream[cmd->tag - 1];
	पूर्ण अन्यथा अणु
		cmd->stream = &fu->stream[0];
	पूर्ण

	चयन (cmd_iu->prio_attr & 0x7) अणु
	हाल UAS_HEAD_TAG:
		cmd->prio_attr = TCM_HEAD_TAG;
		अवरोध;
	हाल UAS_ORDERED_TAG:
		cmd->prio_attr = TCM_ORDERED_TAG;
		अवरोध;
	हाल UAS_ACA:
		cmd->prio_attr = TCM_ACA_TAG;
		अवरोध;
	शेष:
		pr_debug_once("Unsupported prio_attr: %02x.\n",
				cmd_iu->prio_attr);
		fallthrough;
	हाल UAS_SIMPLE_TAG:
		cmd->prio_attr = TCM_SIMPLE_TAG;
		अवरोध;
	पूर्ण

	cmd->unpacked_lun = scsilun_to_पूर्णांक(&cmd_iu->lun);

	INIT_WORK(&cmd->work, usbg_cmd_work);
	queue_work(tpg->workqueue, &cmd->work);

	वापस 0;
err:
	usbg_release_cmd(&cmd->se_cmd);
	वापस -EINVAL;
पूर्ण

अटल व्योम bot_cmd_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा usbg_cmd *cmd = container_of(work, काष्ठा usbg_cmd, work);
	काष्ठा se_cmd *se_cmd;
	काष्ठा tcm_usbg_nexus *tv_nexus;
	काष्ठा usbg_tpg *tpg;
	पूर्णांक dir;

	se_cmd = &cmd->se_cmd;
	tpg = cmd->fu->tpg;
	tv_nexus = tpg->tpg_nexus;
	dir = get_cmd_dir(cmd->cmd_buf);
	अगर (dir < 0) अणु
		__target_init_cmd(se_cmd,
				  tv_nexus->tvn_se_sess->se_tpg->se_tpg_tfo,
				  tv_nexus->tvn_se_sess, cmd->data_len, DMA_NONE,
				  cmd->prio_attr, cmd->sense_iu.sense,
				  cmd->unpacked_lun);
		जाओ out;
	पूर्ण

	target_submit_cmd(se_cmd, tv_nexus->tvn_se_sess,
			  cmd->cmd_buf, cmd->sense_iu.sense, cmd->unpacked_lun,
			  cmd->data_len, cmd->prio_attr, dir, 0);
	वापस;

out:
	transport_send_check_condition_and_sense(se_cmd,
				TCM_UNSUPPORTED_SCSI_OPCODE, 1);
	transport_generic_मुक्त_cmd(&cmd->se_cmd, 0);
पूर्ण

अटल पूर्णांक bot_submit_command(काष्ठा f_uas *fu,
		व्योम *cmdbuf, अचिन्हित पूर्णांक len)
अणु
	काष्ठा bulk_cb_wrap *cbw = cmdbuf;
	काष्ठा usbg_cmd *cmd;
	काष्ठा usbg_tpg *tpg = fu->tpg;
	काष्ठा tcm_usbg_nexus *tv_nexus;
	u32 cmd_len;

	अगर (cbw->Signature != cpu_to_le32(US_BULK_CB_SIGN)) अणु
		pr_err("Wrong signature on CBW\n");
		वापस -EINVAL;
	पूर्ण
	अगर (len != 31) अणु
		pr_err("Wrong length for CBW\n");
		वापस -EINVAL;
	पूर्ण

	cmd_len = cbw->Length;
	अगर (cmd_len < 1 || cmd_len > 16)
		वापस -EINVAL;

	tv_nexus = tpg->tpg_nexus;
	अगर (!tv_nexus) अणु
		pr_err("Missing nexus, ignoring command\n");
		वापस -ENODEV;
	पूर्ण

	cmd = usbg_get_cmd(fu, tv_nexus, cbw->Tag);
	अगर (IS_ERR(cmd)) अणु
		pr_err("usbg_get_cmd failed\n");
		वापस -ENOMEM;
	पूर्ण
	स_नकल(cmd->cmd_buf, cbw->CDB, cmd_len);

	cmd->bot_tag = cbw->Tag;
	cmd->prio_attr = TCM_SIMPLE_TAG;
	cmd->unpacked_lun = cbw->Lun;
	cmd->is_पढ़ो = cbw->Flags & US_BULK_FLAG_IN ? 1 : 0;
	cmd->data_len = le32_to_cpu(cbw->DataTransferLength);
	cmd->se_cmd.tag = le32_to_cpu(cmd->bot_tag);

	INIT_WORK(&cmd->work, bot_cmd_work);
	queue_work(tpg->workqueue, &cmd->work);

	वापस 0;
पूर्ण

/* Start fabric.c code */

अटल पूर्णांक usbg_check_true(काष्ठा se_portal_group *se_tpg)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक usbg_check_false(काष्ठा se_portal_group *se_tpg)
अणु
	वापस 0;
पूर्ण

अटल अक्षर *usbg_get_fabric_wwn(काष्ठा se_portal_group *se_tpg)
अणु
	काष्ठा usbg_tpg *tpg = container_of(se_tpg,
				काष्ठा usbg_tpg, se_tpg);
	काष्ठा usbg_tport *tport = tpg->tport;

	वापस &tport->tport_name[0];
पूर्ण

अटल u16 usbg_get_tag(काष्ठा se_portal_group *se_tpg)
अणु
	काष्ठा usbg_tpg *tpg = container_of(se_tpg,
				काष्ठा usbg_tpg, se_tpg);
	वापस tpg->tport_tpgt;
पूर्ण

अटल u32 usbg_tpg_get_inst_index(काष्ठा se_portal_group *se_tpg)
अणु
	वापस 1;
पूर्ण

अटल व्योम usbg_release_cmd(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा usbg_cmd *cmd = container_of(se_cmd, काष्ठा usbg_cmd,
			se_cmd);
	काष्ठा se_session *se_sess = se_cmd->se_sess;

	kमुक्त(cmd->data_buf);
	target_मुक्त_tag(se_sess, se_cmd);
पूर्ण

अटल u32 usbg_sess_get_index(काष्ठा se_session *se_sess)
अणु
	वापस 0;
पूर्ण

अटल व्योम usbg_set_शेष_node_attrs(काष्ठा se_node_acl *nacl)
अणु
पूर्ण

अटल पूर्णांक usbg_get_cmd_state(काष्ठा se_cmd *se_cmd)
अणु
	वापस 0;
पूर्ण

अटल व्योम usbg_queue_पंचांग_rsp(काष्ठा se_cmd *se_cmd)
अणु
पूर्ण

अटल व्योम usbg_पातed_task(काष्ठा se_cmd *se_cmd)
अणु
पूर्ण

अटल स्थिर अक्षर *usbg_check_wwn(स्थिर अक्षर *name)
अणु
	स्थिर अक्षर *n;
	अचिन्हित पूर्णांक len;

	n = म_माला(name, "naa.");
	अगर (!n)
		वापस शून्य;
	n += 4;
	len = म_माप(n);
	अगर (len == 0 || len > USBG_NAMELEN - 1)
		वापस शून्य;
	वापस n;
पूर्ण

अटल पूर्णांक usbg_init_nodeacl(काष्ठा se_node_acl *se_nacl, स्थिर अक्षर *name)
अणु
	अगर (!usbg_check_wwn(name))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल काष्ठा se_portal_group *usbg_make_tpg(काष्ठा se_wwn *wwn,
					     स्थिर अक्षर *name)
अणु
	काष्ठा usbg_tport *tport = container_of(wwn, काष्ठा usbg_tport,
			tport_wwn);
	काष्ठा usbg_tpg *tpg;
	अचिन्हित दीर्घ tpgt;
	पूर्णांक ret;
	काष्ठा f_tcm_opts *opts;
	अचिन्हित i;

	अगर (म_माला(name, "tpgt_") != name)
		वापस ERR_PTR(-EINVAL);
	अगर (kम_से_अदीर्घ(name + 5, 0, &tpgt) || tpgt > अच_पूर्णांक_उच्च)
		वापस ERR_PTR(-EINVAL);
	ret = -ENODEV;
	mutex_lock(&tpg_instances_lock);
	क्रम (i = 0; i < TPG_INSTANCES; ++i)
		अगर (tpg_instances[i].func_inst && !tpg_instances[i].tpg)
			अवरोध;
	अगर (i == TPG_INSTANCES)
		जाओ unlock_inst;

	opts = container_of(tpg_instances[i].func_inst, काष्ठा f_tcm_opts,
		func_inst);
	mutex_lock(&opts->dep_lock);
	अगर (!opts->पढ़ोy)
		जाओ unlock_dep;

	अगर (opts->has_dep) अणु
		अगर (!try_module_get(opts->dependent))
			जाओ unlock_dep;
	पूर्ण अन्यथा अणु
		ret = configfs_depend_item_unlocked(
			wwn->wwn_group.cg_subsys,
			&opts->func_inst.group.cg_item);
		अगर (ret)
			जाओ unlock_dep;
	पूर्ण

	tpg = kzalloc(माप(काष्ठा usbg_tpg), GFP_KERNEL);
	ret = -ENOMEM;
	अगर (!tpg)
		जाओ unref_dep;
	mutex_init(&tpg->tpg_mutex);
	atomic_set(&tpg->tpg_port_count, 0);
	tpg->workqueue = alloc_workqueue("tcm_usb_gadget", 0, 1);
	अगर (!tpg->workqueue)
		जाओ मुक्त_tpg;

	tpg->tport = tport;
	tpg->tport_tpgt = tpgt;

	/*
	 * SPC करोesn't assign a protocol identअगरier क्रम USB-SCSI, so we
	 * pretend to be SAS..
	 */
	ret = core_tpg_रेजिस्टर(wwn, &tpg->se_tpg, SCSI_PROTOCOL_SAS);
	अगर (ret < 0)
		जाओ मुक्त_workqueue;

	tpg_instances[i].tpg = tpg;
	tpg->fi = tpg_instances[i].func_inst;
	mutex_unlock(&opts->dep_lock);
	mutex_unlock(&tpg_instances_lock);
	वापस &tpg->se_tpg;

मुक्त_workqueue:
	destroy_workqueue(tpg->workqueue);
मुक्त_tpg:
	kमुक्त(tpg);
unref_dep:
	अगर (opts->has_dep)
		module_put(opts->dependent);
	अन्यथा
		configfs_undepend_item_unlocked(&opts->func_inst.group.cg_item);
unlock_dep:
	mutex_unlock(&opts->dep_lock);
unlock_inst:
	mutex_unlock(&tpg_instances_lock);

	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक tcm_usbg_drop_nexus(काष्ठा usbg_tpg *);

अटल व्योम usbg_drop_tpg(काष्ठा se_portal_group *se_tpg)
अणु
	काष्ठा usbg_tpg *tpg = container_of(se_tpg,
				काष्ठा usbg_tpg, se_tpg);
	अचिन्हित i;
	काष्ठा f_tcm_opts *opts;

	tcm_usbg_drop_nexus(tpg);
	core_tpg_deरेजिस्टर(se_tpg);
	destroy_workqueue(tpg->workqueue);

	mutex_lock(&tpg_instances_lock);
	क्रम (i = 0; i < TPG_INSTANCES; ++i)
		अगर (tpg_instances[i].tpg == tpg)
			अवरोध;
	अगर (i < TPG_INSTANCES) अणु
		tpg_instances[i].tpg = शून्य;
		opts = container_of(tpg_instances[i].func_inst,
			काष्ठा f_tcm_opts, func_inst);
		mutex_lock(&opts->dep_lock);
		अगर (opts->has_dep)
			module_put(opts->dependent);
		अन्यथा
			configfs_undepend_item_unlocked(
				&opts->func_inst.group.cg_item);
		mutex_unlock(&opts->dep_lock);
	पूर्ण
	mutex_unlock(&tpg_instances_lock);

	kमुक्त(tpg);
पूर्ण

अटल काष्ठा se_wwn *usbg_make_tport(
	काष्ठा target_fabric_configfs *tf,
	काष्ठा config_group *group,
	स्थिर अक्षर *name)
अणु
	काष्ठा usbg_tport *tport;
	स्थिर अक्षर *wnn_name;
	u64 wwpn = 0;

	wnn_name = usbg_check_wwn(name);
	अगर (!wnn_name)
		वापस ERR_PTR(-EINVAL);

	tport = kzalloc(माप(काष्ठा usbg_tport), GFP_KERNEL);
	अगर (!(tport))
		वापस ERR_PTR(-ENOMEM);

	tport->tport_wwpn = wwpn;
	snम_लिखो(tport->tport_name, माप(tport->tport_name), "%s", wnn_name);
	वापस &tport->tport_wwn;
पूर्ण

अटल व्योम usbg_drop_tport(काष्ठा se_wwn *wwn)
अणु
	काष्ठा usbg_tport *tport = container_of(wwn,
				काष्ठा usbg_tport, tport_wwn);
	kमुक्त(tport);
पूर्ण

/*
 * If somebody feels like dropping the version property, go ahead.
 */
अटल sमाप_प्रकार usbg_wwn_version_show(काष्ठा config_item *item,  अक्षर *page)
अणु
	वापस प्र_लिखो(page, "usb-gadget fabric module\n");
पूर्ण

CONFIGFS_ATTR_RO(usbg_wwn_, version);

अटल काष्ठा configfs_attribute *usbg_wwn_attrs[] = अणु
	&usbg_wwn_attr_version,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार tcm_usbg_tpg_enable_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_portal_group *se_tpg = to_tpg(item);
	काष्ठा usbg_tpg  *tpg = container_of(se_tpg, काष्ठा usbg_tpg, se_tpg);

	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", tpg->gadget_connect);
पूर्ण

अटल पूर्णांक usbg_attach(काष्ठा usbg_tpg *);
अटल व्योम usbg_detach(काष्ठा usbg_tpg *);

अटल sमाप_प्रकार tcm_usbg_tpg_enable_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_portal_group *se_tpg = to_tpg(item);
	काष्ठा usbg_tpg  *tpg = container_of(se_tpg, काष्ठा usbg_tpg, se_tpg);
	bool op;
	sमाप_प्रकार ret;

	ret = strtobool(page, &op);
	अगर (ret)
		वापस ret;

	अगर ((op && tpg->gadget_connect) || (!op && !tpg->gadget_connect))
		वापस -EINVAL;

	अगर (op)
		ret = usbg_attach(tpg);
	अन्यथा
		usbg_detach(tpg);
	अगर (ret)
		वापस ret;

	tpg->gadget_connect = op;

	वापस count;
पूर्ण

अटल sमाप_प्रकार tcm_usbg_tpg_nexus_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_portal_group *se_tpg = to_tpg(item);
	काष्ठा usbg_tpg *tpg = container_of(se_tpg, काष्ठा usbg_tpg, se_tpg);
	काष्ठा tcm_usbg_nexus *tv_nexus;
	sमाप_प्रकार ret;

	mutex_lock(&tpg->tpg_mutex);
	tv_nexus = tpg->tpg_nexus;
	अगर (!tv_nexus) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण
	ret = snम_लिखो(page, PAGE_SIZE, "%s\n",
			tv_nexus->tvn_se_sess->se_node_acl->initiatorname);
out:
	mutex_unlock(&tpg->tpg_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक usbg_alloc_sess_cb(काष्ठा se_portal_group *se_tpg,
			      काष्ठा se_session *se_sess, व्योम *p)
अणु
	काष्ठा usbg_tpg *tpg = container_of(se_tpg,
				काष्ठा usbg_tpg, se_tpg);

	tpg->tpg_nexus = p;
	वापस 0;
पूर्ण

अटल पूर्णांक tcm_usbg_make_nexus(काष्ठा usbg_tpg *tpg, अक्षर *name)
अणु
	काष्ठा tcm_usbg_nexus *tv_nexus;
	पूर्णांक ret = 0;

	mutex_lock(&tpg->tpg_mutex);
	अगर (tpg->tpg_nexus) अणु
		ret = -EEXIST;
		pr_debug("tpg->tpg_nexus already exists\n");
		जाओ out_unlock;
	पूर्ण

	tv_nexus = kzalloc(माप(*tv_nexus), GFP_KERNEL);
	अगर (!tv_nexus) अणु
		ret = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	tv_nexus->tvn_se_sess = target_setup_session(&tpg->se_tpg,
						     USB_G_DEFAULT_SESSION_TAGS,
						     माप(काष्ठा usbg_cmd),
						     TARGET_PROT_NORMAL, name,
						     tv_nexus, usbg_alloc_sess_cb);
	अगर (IS_ERR(tv_nexus->tvn_se_sess)) अणु
#घोषणा MAKE_NEXUS_MSG "core_tpg_check_initiator_node_acl() failed for %s\n"
		pr_debug(MAKE_NEXUS_MSG, name);
#अघोषित MAKE_NEXUS_MSG
		ret = PTR_ERR(tv_nexus->tvn_se_sess);
		kमुक्त(tv_nexus);
	पूर्ण

out_unlock:
	mutex_unlock(&tpg->tpg_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक tcm_usbg_drop_nexus(काष्ठा usbg_tpg *tpg)
अणु
	काष्ठा se_session *se_sess;
	काष्ठा tcm_usbg_nexus *tv_nexus;
	पूर्णांक ret = -ENODEV;

	mutex_lock(&tpg->tpg_mutex);
	tv_nexus = tpg->tpg_nexus;
	अगर (!tv_nexus)
		जाओ out;

	se_sess = tv_nexus->tvn_se_sess;
	अगर (!se_sess)
		जाओ out;

	अगर (atomic_पढ़ो(&tpg->tpg_port_count)) अणु
		ret = -EPERM;
#घोषणा MSG "Unable to remove Host I_T Nexus with active TPG port count: %d\n"
		pr_err(MSG, atomic_पढ़ो(&tpg->tpg_port_count));
#अघोषित MSG
		जाओ out;
	पूर्ण

	pr_debug("Removing I_T Nexus to Initiator Port: %s\n",
			tv_nexus->tvn_se_sess->se_node_acl->initiatorname);
	/*
	 * Release the SCSI I_T Nexus to the emulated vHost Target Port
	 */
	target_हटाओ_session(se_sess);
	tpg->tpg_nexus = शून्य;

	kमुक्त(tv_nexus);
	ret = 0;
out:
	mutex_unlock(&tpg->tpg_mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार tcm_usbg_tpg_nexus_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_portal_group *se_tpg = to_tpg(item);
	काष्ठा usbg_tpg *tpg = container_of(se_tpg, काष्ठा usbg_tpg, se_tpg);
	अचिन्हित अक्षर i_port[USBG_NAMELEN], *ptr;
	पूर्णांक ret;

	अगर (!म_भेदन(page, "NULL", 4)) अणु
		ret = tcm_usbg_drop_nexus(tpg);
		वापस (!ret) ? count : ret;
	पूर्ण
	अगर (म_माप(page) >= USBG_NAMELEN) अणु

#घोषणा NEXUS_STORE_MSG "Emulated NAA Sas Address: %s, exceeds max: %d\n"
		pr_err(NEXUS_STORE_MSG, page, USBG_NAMELEN);
#अघोषित NEXUS_STORE_MSG
		वापस -EINVAL;
	पूर्ण
	snम_लिखो(i_port, USBG_NAMELEN, "%s", page);

	ptr = म_माला(i_port, "naa.");
	अगर (!ptr) अणु
		pr_err("Missing 'naa.' prefix\n");
		वापस -EINVAL;
	पूर्ण

	अगर (i_port[म_माप(i_port) - 1] == '\n')
		i_port[म_माप(i_port) - 1] = '\0';

	ret = tcm_usbg_make_nexus(tpg, &i_port[0]);
	अगर (ret < 0)
		वापस ret;
	वापस count;
पूर्ण

CONFIGFS_ATTR(tcm_usbg_tpg_, enable);
CONFIGFS_ATTR(tcm_usbg_tpg_, nexus);

अटल काष्ठा configfs_attribute *usbg_base_attrs[] = अणु
	&tcm_usbg_tpg_attr_enable,
	&tcm_usbg_tpg_attr_nexus,
	शून्य,
पूर्ण;

अटल पूर्णांक usbg_port_link(काष्ठा se_portal_group *se_tpg, काष्ठा se_lun *lun)
अणु
	काष्ठा usbg_tpg *tpg = container_of(se_tpg, काष्ठा usbg_tpg, se_tpg);

	atomic_inc(&tpg->tpg_port_count);
	smp_mb__after_atomic();
	वापस 0;
पूर्ण

अटल व्योम usbg_port_unlink(काष्ठा se_portal_group *se_tpg,
		काष्ठा se_lun *se_lun)
अणु
	काष्ठा usbg_tpg *tpg = container_of(se_tpg, काष्ठा usbg_tpg, se_tpg);

	atomic_dec(&tpg->tpg_port_count);
	smp_mb__after_atomic();
पूर्ण

अटल पूर्णांक usbg_check_stop_मुक्त(काष्ठा se_cmd *se_cmd)
अणु
	वापस target_put_sess_cmd(se_cmd);
पूर्ण

अटल स्थिर काष्ठा target_core_fabric_ops usbg_ops = अणु
	.module				= THIS_MODULE,
	.fabric_name			= "usb_gadget",
	.tpg_get_wwn			= usbg_get_fabric_wwn,
	.tpg_get_tag			= usbg_get_tag,
	.tpg_check_demo_mode		= usbg_check_true,
	.tpg_check_demo_mode_cache	= usbg_check_false,
	.tpg_check_demo_mode_ग_लिखो_protect = usbg_check_false,
	.tpg_check_prod_mode_ग_लिखो_protect = usbg_check_false,
	.tpg_get_inst_index		= usbg_tpg_get_inst_index,
	.release_cmd			= usbg_release_cmd,
	.sess_get_index			= usbg_sess_get_index,
	.sess_get_initiator_sid		= शून्य,
	.ग_लिखो_pending			= usbg_send_ग_लिखो_request,
	.set_शेष_node_attributes	= usbg_set_शेष_node_attrs,
	.get_cmd_state			= usbg_get_cmd_state,
	.queue_data_in			= usbg_send_पढ़ो_response,
	.queue_status			= usbg_send_status_response,
	.queue_पंचांग_rsp			= usbg_queue_पंचांग_rsp,
	.पातed_task			= usbg_पातed_task,
	.check_stop_मुक्त		= usbg_check_stop_मुक्त,

	.fabric_make_wwn		= usbg_make_tport,
	.fabric_drop_wwn		= usbg_drop_tport,
	.fabric_make_tpg		= usbg_make_tpg,
	.fabric_drop_tpg		= usbg_drop_tpg,
	.fabric_post_link		= usbg_port_link,
	.fabric_pre_unlink		= usbg_port_unlink,
	.fabric_init_nodeacl		= usbg_init_nodeacl,

	.tfc_wwn_attrs			= usbg_wwn_attrs,
	.tfc_tpg_base_attrs		= usbg_base_attrs,
पूर्ण;

/* Start gadget.c code */

अटल काष्ठा usb_पूर्णांकerface_descriptor bot_पूर्णांकf_desc = अणु
	.bLength =              माप(bot_पूर्णांकf_desc),
	.bDescriptorType =      USB_DT_INTERFACE,
	.bNumEndpoपूर्णांकs =        2,
	.bAlternateSetting =	USB_G_ALT_INT_BBB,
	.bInterfaceClass =      USB_CLASS_MASS_STORAGE,
	.bInterfaceSubClass =   USB_SC_SCSI,
	.bInterfaceProtocol =   USB_PR_BULK,
पूर्ण;

अटल काष्ठा usb_पूर्णांकerface_descriptor uasp_पूर्णांकf_desc = अणु
	.bLength =		माप(uasp_पूर्णांकf_desc),
	.bDescriptorType =	USB_DT_INTERFACE,
	.bNumEndpoपूर्णांकs =	4,
	.bAlternateSetting =	USB_G_ALT_INT_UAS,
	.bInterfaceClass =	USB_CLASS_MASS_STORAGE,
	.bInterfaceSubClass =	USB_SC_SCSI,
	.bInterfaceProtocol =	USB_PR_UAS,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor uasp_bi_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor uasp_fs_bi_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_pipe_usage_descriptor uasp_bi_pipe_desc = अणु
	.bLength =		माप(uasp_bi_pipe_desc),
	.bDescriptorType =	USB_DT_PIPE_USAGE,
	.bPipeID =		DATA_IN_PIPE_ID,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor uasp_ss_bi_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor uasp_bi_ep_comp_desc = अणु
	.bLength =		माप(uasp_bi_ep_comp_desc),
	.bDescriptorType =	USB_DT_SS_ENDPOINT_COMP,
	.bMaxBurst =		0,
	.bmAttributes =		UASP_SS_EP_COMP_LOG_STREAMS,
	.wBytesPerInterval =	0,
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor bot_bi_ep_comp_desc = अणु
	.bLength =		माप(bot_bi_ep_comp_desc),
	.bDescriptorType =	USB_DT_SS_ENDPOINT_COMP,
	.bMaxBurst =		0,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor uasp_bo_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor uasp_fs_bo_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_pipe_usage_descriptor uasp_bo_pipe_desc = अणु
	.bLength =		माप(uasp_bo_pipe_desc),
	.bDescriptorType =	USB_DT_PIPE_USAGE,
	.bPipeID =		DATA_OUT_PIPE_ID,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor uasp_ss_bo_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(0x400),
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor uasp_bo_ep_comp_desc = अणु
	.bLength =		माप(uasp_bo_ep_comp_desc),
	.bDescriptorType =	USB_DT_SS_ENDPOINT_COMP,
	.bmAttributes =		UASP_SS_EP_COMP_LOG_STREAMS,
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor bot_bo_ep_comp_desc = अणु
	.bLength =		माप(bot_bo_ep_comp_desc),
	.bDescriptorType =	USB_DT_SS_ENDPOINT_COMP,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor uasp_status_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor uasp_fs_status_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_pipe_usage_descriptor uasp_status_pipe_desc = अणु
	.bLength =		माप(uasp_status_pipe_desc),
	.bDescriptorType =	USB_DT_PIPE_USAGE,
	.bPipeID =		STATUS_PIPE_ID,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor uasp_ss_status_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor uasp_status_in_ep_comp_desc = अणु
	.bLength =		माप(uasp_status_in_ep_comp_desc),
	.bDescriptorType =	USB_DT_SS_ENDPOINT_COMP,
	.bmAttributes =		UASP_SS_EP_COMP_LOG_STREAMS,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor uasp_cmd_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor uasp_fs_cmd_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_pipe_usage_descriptor uasp_cmd_pipe_desc = अणु
	.bLength =		माप(uasp_cmd_pipe_desc),
	.bDescriptorType =	USB_DT_PIPE_USAGE,
	.bPipeID =		CMD_PIPE_ID,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor uasp_ss_cmd_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor uasp_cmd_comp_desc = अणु
	.bLength =		माप(uasp_cmd_comp_desc),
	.bDescriptorType =	USB_DT_SS_ENDPOINT_COMP,
पूर्ण;

अटल काष्ठा usb_descriptor_header *uasp_fs_function_desc[] = अणु
	(काष्ठा usb_descriptor_header *) &bot_पूर्णांकf_desc,
	(काष्ठा usb_descriptor_header *) &uasp_fs_bi_desc,
	(काष्ठा usb_descriptor_header *) &uasp_fs_bo_desc,

	(काष्ठा usb_descriptor_header *) &uasp_पूर्णांकf_desc,
	(काष्ठा usb_descriptor_header *) &uasp_fs_bi_desc,
	(काष्ठा usb_descriptor_header *) &uasp_bi_pipe_desc,
	(काष्ठा usb_descriptor_header *) &uasp_fs_bo_desc,
	(काष्ठा usb_descriptor_header *) &uasp_bo_pipe_desc,
	(काष्ठा usb_descriptor_header *) &uasp_fs_status_desc,
	(काष्ठा usb_descriptor_header *) &uasp_status_pipe_desc,
	(काष्ठा usb_descriptor_header *) &uasp_fs_cmd_desc,
	(काष्ठा usb_descriptor_header *) &uasp_cmd_pipe_desc,
	शून्य,
पूर्ण;

अटल काष्ठा usb_descriptor_header *uasp_hs_function_desc[] = अणु
	(काष्ठा usb_descriptor_header *) &bot_पूर्णांकf_desc,
	(काष्ठा usb_descriptor_header *) &uasp_bi_desc,
	(काष्ठा usb_descriptor_header *) &uasp_bo_desc,

	(काष्ठा usb_descriptor_header *) &uasp_पूर्णांकf_desc,
	(काष्ठा usb_descriptor_header *) &uasp_bi_desc,
	(काष्ठा usb_descriptor_header *) &uasp_bi_pipe_desc,
	(काष्ठा usb_descriptor_header *) &uasp_bo_desc,
	(काष्ठा usb_descriptor_header *) &uasp_bo_pipe_desc,
	(काष्ठा usb_descriptor_header *) &uasp_status_desc,
	(काष्ठा usb_descriptor_header *) &uasp_status_pipe_desc,
	(काष्ठा usb_descriptor_header *) &uasp_cmd_desc,
	(काष्ठा usb_descriptor_header *) &uasp_cmd_pipe_desc,
	शून्य,
पूर्ण;

अटल काष्ठा usb_descriptor_header *uasp_ss_function_desc[] = अणु
	(काष्ठा usb_descriptor_header *) &bot_पूर्णांकf_desc,
	(काष्ठा usb_descriptor_header *) &uasp_ss_bi_desc,
	(काष्ठा usb_descriptor_header *) &bot_bi_ep_comp_desc,
	(काष्ठा usb_descriptor_header *) &uasp_ss_bo_desc,
	(काष्ठा usb_descriptor_header *) &bot_bo_ep_comp_desc,

	(काष्ठा usb_descriptor_header *) &uasp_पूर्णांकf_desc,
	(काष्ठा usb_descriptor_header *) &uasp_ss_bi_desc,
	(काष्ठा usb_descriptor_header *) &uasp_bi_ep_comp_desc,
	(काष्ठा usb_descriptor_header *) &uasp_bi_pipe_desc,
	(काष्ठा usb_descriptor_header *) &uasp_ss_bo_desc,
	(काष्ठा usb_descriptor_header *) &uasp_bo_ep_comp_desc,
	(काष्ठा usb_descriptor_header *) &uasp_bo_pipe_desc,
	(काष्ठा usb_descriptor_header *) &uasp_ss_status_desc,
	(काष्ठा usb_descriptor_header *) &uasp_status_in_ep_comp_desc,
	(काष्ठा usb_descriptor_header *) &uasp_status_pipe_desc,
	(काष्ठा usb_descriptor_header *) &uasp_ss_cmd_desc,
	(काष्ठा usb_descriptor_header *) &uasp_cmd_comp_desc,
	(काष्ठा usb_descriptor_header *) &uasp_cmd_pipe_desc,
	शून्य,
पूर्ण;

अटल काष्ठा usb_string	tcm_us_strings[] = अणु
	[USB_G_STR_INT_UAS].s		= "USB Attached SCSI",
	[USB_G_STR_INT_BBB].s		= "Bulk Only Transport",
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा usb_gadget_strings tcm_stringtab = अणु
	.language = 0x0409,
	.strings = tcm_us_strings,
पूर्ण;

अटल काष्ठा usb_gadget_strings *tcm_strings[] = अणु
	&tcm_stringtab,
	शून्य,
पूर्ण;

अटल पूर्णांक tcm_bind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा f_uas		*fu = to_f_uas(f);
	काष्ठा usb_string	*us;
	काष्ठा usb_gadget	*gadget = c->cdev->gadget;
	काष्ठा usb_ep		*ep;
	काष्ठा f_tcm_opts	*opts;
	पूर्णांक			अगरace;
	पूर्णांक			ret;

	opts = container_of(f->fi, काष्ठा f_tcm_opts, func_inst);

	mutex_lock(&opts->dep_lock);
	अगर (!opts->can_attach) अणु
		mutex_unlock(&opts->dep_lock);
		वापस -ENODEV;
	पूर्ण
	mutex_unlock(&opts->dep_lock);
	us = usb_gstrings_attach(c->cdev, tcm_strings,
		ARRAY_SIZE(tcm_us_strings));
	अगर (IS_ERR(us))
		वापस PTR_ERR(us);
	bot_पूर्णांकf_desc.iInterface = us[USB_G_STR_INT_BBB].id;
	uasp_पूर्णांकf_desc.iInterface = us[USB_G_STR_INT_UAS].id;

	अगरace = usb_पूर्णांकerface_id(c, f);
	अगर (अगरace < 0)
		वापस अगरace;

	bot_पूर्णांकf_desc.bInterfaceNumber = अगरace;
	uasp_पूर्णांकf_desc.bInterfaceNumber = अगरace;
	fu->अगरace = अगरace;
	ep = usb_ep_स्वतःconfig_ss(gadget, &uasp_ss_bi_desc,
			&uasp_bi_ep_comp_desc);
	अगर (!ep)
		जाओ ep_fail;

	fu->ep_in = ep;

	ep = usb_ep_स्वतःconfig_ss(gadget, &uasp_ss_bo_desc,
			&uasp_bo_ep_comp_desc);
	अगर (!ep)
		जाओ ep_fail;
	fu->ep_out = ep;

	ep = usb_ep_स्वतःconfig_ss(gadget, &uasp_ss_status_desc,
			&uasp_status_in_ep_comp_desc);
	अगर (!ep)
		जाओ ep_fail;
	fu->ep_status = ep;

	ep = usb_ep_स्वतःconfig_ss(gadget, &uasp_ss_cmd_desc,
			&uasp_cmd_comp_desc);
	अगर (!ep)
		जाओ ep_fail;
	fu->ep_cmd = ep;

	/* Assume endpoपूर्णांक addresses are the same क्रम both speeds */
	uasp_bi_desc.bEndpoपूर्णांकAddress =	uasp_ss_bi_desc.bEndpoपूर्णांकAddress;
	uasp_bo_desc.bEndpoपूर्णांकAddress = uasp_ss_bo_desc.bEndpoपूर्णांकAddress;
	uasp_status_desc.bEndpoपूर्णांकAddress =
		uasp_ss_status_desc.bEndpoपूर्णांकAddress;
	uasp_cmd_desc.bEndpoपूर्णांकAddress = uasp_ss_cmd_desc.bEndpoपूर्णांकAddress;

	uasp_fs_bi_desc.bEndpoपूर्णांकAddress = uasp_ss_bi_desc.bEndpoपूर्णांकAddress;
	uasp_fs_bo_desc.bEndpoपूर्णांकAddress = uasp_ss_bo_desc.bEndpoपूर्णांकAddress;
	uasp_fs_status_desc.bEndpoपूर्णांकAddress =
		uasp_ss_status_desc.bEndpoपूर्णांकAddress;
	uasp_fs_cmd_desc.bEndpoपूर्णांकAddress = uasp_ss_cmd_desc.bEndpoपूर्णांकAddress;

	ret = usb_assign_descriptors(f, uasp_fs_function_desc,
			uasp_hs_function_desc, uasp_ss_function_desc,
			uasp_ss_function_desc);
	अगर (ret)
		जाओ ep_fail;

	वापस 0;
ep_fail:
	pr_err("Can't claim all required eps\n");

	वापस -ENOTSUPP;
पूर्ण

काष्ठा guas_setup_wq अणु
	काष्ठा work_काष्ठा work;
	काष्ठा f_uas *fu;
	अचिन्हित पूर्णांक alt;
पूर्ण;

अटल व्योम tcm_delayed_set_alt(काष्ठा work_काष्ठा *wq)
अणु
	काष्ठा guas_setup_wq *work = container_of(wq, काष्ठा guas_setup_wq,
			work);
	काष्ठा f_uas *fu = work->fu;
	पूर्णांक alt = work->alt;

	kमुक्त(work);

	अगर (fu->flags & USBG_IS_BOT)
		bot_cleanup_old_alt(fu);
	अगर (fu->flags & USBG_IS_UAS)
		uasp_cleanup_old_alt(fu);

	अगर (alt == USB_G_ALT_INT_BBB)
		bot_set_alt(fu);
	अन्यथा अगर (alt == USB_G_ALT_INT_UAS)
		uasp_set_alt(fu);
	usb_composite_setup_जारी(fu->function.config->cdev);
पूर्ण

अटल पूर्णांक tcm_get_alt(काष्ठा usb_function *f, अचिन्हित पूर्णांकf)
अणु
	अगर (पूर्णांकf == bot_पूर्णांकf_desc.bInterfaceNumber)
		वापस USB_G_ALT_INT_BBB;
	अगर (पूर्णांकf == uasp_पूर्णांकf_desc.bInterfaceNumber)
		वापस USB_G_ALT_INT_UAS;

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक tcm_set_alt(काष्ठा usb_function *f, अचिन्हित पूर्णांकf, अचिन्हित alt)
अणु
	काष्ठा f_uas *fu = to_f_uas(f);

	अगर ((alt == USB_G_ALT_INT_BBB) || (alt == USB_G_ALT_INT_UAS)) अणु
		काष्ठा guas_setup_wq *work;

		work = kदो_स्मृति(माप(*work), GFP_ATOMIC);
		अगर (!work)
			वापस -ENOMEM;
		INIT_WORK(&work->work, tcm_delayed_set_alt);
		work->fu = fu;
		work->alt = alt;
		schedule_work(&work->work);
		वापस USB_GADGET_DELAYED_STATUS;
	पूर्ण
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम tcm_disable(काष्ठा usb_function *f)
अणु
	काष्ठा f_uas *fu = to_f_uas(f);

	अगर (fu->flags & USBG_IS_UAS)
		uasp_cleanup_old_alt(fu);
	अन्यथा अगर (fu->flags & USBG_IS_BOT)
		bot_cleanup_old_alt(fu);
	fu->flags = 0;
पूर्ण

अटल पूर्णांक tcm_setup(काष्ठा usb_function *f,
		स्थिर काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा f_uas *fu = to_f_uas(f);

	अगर (!(fu->flags & USBG_IS_BOT))
		वापस -EOPNOTSUPP;

	वापस usbg_bot_setup(f, ctrl);
पूर्ण

अटल अंतरभूत काष्ठा f_tcm_opts *to_f_tcm_opts(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा f_tcm_opts,
		func_inst.group);
पूर्ण

अटल व्योम tcm_attr_release(काष्ठा config_item *item)
अणु
	काष्ठा f_tcm_opts *opts = to_f_tcm_opts(item);

	usb_put_function_instance(&opts->func_inst);
पूर्ण

अटल काष्ठा configfs_item_operations tcm_item_ops = अणु
	.release		= tcm_attr_release,
पूर्ण;

अटल स्थिर काष्ठा config_item_type tcm_func_type = अणु
	.ct_item_ops	= &tcm_item_ops,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल व्योम tcm_मुक्त_inst(काष्ठा usb_function_instance *f)
अणु
	काष्ठा f_tcm_opts *opts;
	अचिन्हित i;

	opts = container_of(f, काष्ठा f_tcm_opts, func_inst);

	mutex_lock(&tpg_instances_lock);
	क्रम (i = 0; i < TPG_INSTANCES; ++i)
		अगर (tpg_instances[i].func_inst == f)
			अवरोध;
	अगर (i < TPG_INSTANCES)
		tpg_instances[i].func_inst = शून्य;
	mutex_unlock(&tpg_instances_lock);

	kमुक्त(opts);
पूर्ण

अटल पूर्णांक tcm_रेजिस्टर_callback(काष्ठा usb_function_instance *f)
अणु
	काष्ठा f_tcm_opts *opts = container_of(f, काष्ठा f_tcm_opts, func_inst);

	mutex_lock(&opts->dep_lock);
	opts->can_attach = true;
	mutex_unlock(&opts->dep_lock);

	वापस 0;
पूर्ण

अटल व्योम tcm_unरेजिस्टर_callback(काष्ठा usb_function_instance *f)
अणु
	काष्ठा f_tcm_opts *opts = container_of(f, काष्ठा f_tcm_opts, func_inst);

	mutex_lock(&opts->dep_lock);
	unरेजिस्टर_gadget_item(opts->
		func_inst.group.cg_item.ci_parent->ci_parent);
	opts->can_attach = false;
	mutex_unlock(&opts->dep_lock);
पूर्ण

अटल पूर्णांक usbg_attach(काष्ठा usbg_tpg *tpg)
अणु
	काष्ठा usb_function_instance *f = tpg->fi;
	काष्ठा f_tcm_opts *opts = container_of(f, काष्ठा f_tcm_opts, func_inst);

	अगर (opts->tcm_रेजिस्टर_callback)
		वापस opts->tcm_रेजिस्टर_callback(f);

	वापस 0;
पूर्ण

अटल व्योम usbg_detach(काष्ठा usbg_tpg *tpg)
अणु
	काष्ठा usb_function_instance *f = tpg->fi;
	काष्ठा f_tcm_opts *opts = container_of(f, काष्ठा f_tcm_opts, func_inst);

	अगर (opts->tcm_unरेजिस्टर_callback)
		opts->tcm_unरेजिस्टर_callback(f);
पूर्ण

अटल पूर्णांक tcm_set_name(काष्ठा usb_function_instance *f, स्थिर अक्षर *name)
अणु
	काष्ठा f_tcm_opts *opts = container_of(f, काष्ठा f_tcm_opts, func_inst);

	pr_debug("tcm: Activating %s\n", name);

	mutex_lock(&opts->dep_lock);
	opts->पढ़ोy = true;
	mutex_unlock(&opts->dep_lock);

	वापस 0;
पूर्ण

अटल काष्ठा usb_function_instance *tcm_alloc_inst(व्योम)
अणु
	काष्ठा f_tcm_opts *opts;
	पूर्णांक i;


	opts = kzalloc(माप(*opts), GFP_KERNEL);
	अगर (!opts)
		वापस ERR_PTR(-ENOMEM);

	mutex_lock(&tpg_instances_lock);
	क्रम (i = 0; i < TPG_INSTANCES; ++i)
		अगर (!tpg_instances[i].func_inst)
			अवरोध;

	अगर (i == TPG_INSTANCES) अणु
		mutex_unlock(&tpg_instances_lock);
		kमुक्त(opts);
		वापस ERR_PTR(-EBUSY);
	पूर्ण
	tpg_instances[i].func_inst = &opts->func_inst;
	mutex_unlock(&tpg_instances_lock);

	mutex_init(&opts->dep_lock);
	opts->func_inst.set_inst_name = tcm_set_name;
	opts->func_inst.मुक्त_func_inst = tcm_मुक्त_inst;
	opts->tcm_रेजिस्टर_callback = tcm_रेजिस्टर_callback;
	opts->tcm_unरेजिस्टर_callback = tcm_unरेजिस्टर_callback;

	config_group_init_type_name(&opts->func_inst.group, "",
			&tcm_func_type);

	वापस &opts->func_inst;
पूर्ण

अटल व्योम tcm_मुक्त(काष्ठा usb_function *f)
अणु
	काष्ठा f_uas *tcm = to_f_uas(f);

	kमुक्त(tcm);
पूर्ण

अटल व्योम tcm_unbind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	usb_मुक्त_all_descriptors(f);
पूर्ण

अटल काष्ठा usb_function *tcm_alloc(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा f_uas *fu;
	अचिन्हित i;

	mutex_lock(&tpg_instances_lock);
	क्रम (i = 0; i < TPG_INSTANCES; ++i)
		अगर (tpg_instances[i].func_inst == fi)
			अवरोध;
	अगर (i == TPG_INSTANCES) अणु
		mutex_unlock(&tpg_instances_lock);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	fu = kzalloc(माप(*fu), GFP_KERNEL);
	अगर (!fu) अणु
		mutex_unlock(&tpg_instances_lock);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	fu->function.name = "Target Function";
	fu->function.bind = tcm_bind;
	fu->function.unbind = tcm_unbind;
	fu->function.set_alt = tcm_set_alt;
	fu->function.get_alt = tcm_get_alt;
	fu->function.setup = tcm_setup;
	fu->function.disable = tcm_disable;
	fu->function.मुक्त_func = tcm_मुक्त;
	fu->tpg = tpg_instances[i].tpg;
	mutex_unlock(&tpg_instances_lock);

	वापस &fu->function;
पूर्ण

DECLARE_USB_FUNCTION(tcm, tcm_alloc_inst, tcm_alloc);

अटल पूर्णांक tcm_init(व्योम)
अणु
	पूर्णांक ret;

	ret = usb_function_रेजिस्टर(&tcmusb_func);
	अगर (ret)
		वापस ret;

	ret = target_रेजिस्टर_ढाँचा(&usbg_ops);
	अगर (ret)
		usb_function_unरेजिस्टर(&tcmusb_func);

	वापस ret;
पूर्ण
module_init(tcm_init);

अटल व्योम tcm_निकास(व्योम)
अणु
	target_unरेजिस्टर_ढाँचा(&usbg_ops);
	usb_function_unरेजिस्टर(&tcmusb_func);
पूर्ण
module_निकास(tcm_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sebastian Andrzej Siewior");
