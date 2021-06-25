<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HighPoपूर्णांक RR3xxx/4xxx controller driver क्रम Linux
 * Copyright (C) 2006-2015 HighPoपूर्णांक Technologies, Inc. All Rights Reserved.
 *
 * Please report bugs/comments/suggestions to linux@highpoपूर्णांक-tech.com
 *
 * For more inक्रमmation, visit http://www.highpoपूर्णांक-tech.com
 */
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/gfp.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/भाग64.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_host.h>

#समावेश "hptiop.h"

MODULE_AUTHOR("HighPoint Technologies, Inc.");
MODULE_DESCRIPTION("HighPoint RocketRAID 3xxx/4xxx Controller Driver");

अटल अक्षर driver_name[] = "hptiop";
अटल स्थिर अक्षर driver_name_दीर्घ[] = "RocketRAID 3xxx/4xxx Controller driver";
अटल स्थिर अक्षर driver_ver[] = "v1.10.0";

अटल पूर्णांक iop_send_sync_msg(काष्ठा hptiop_hba *hba, u32 msg, u32 millisec);
अटल व्योम hptiop_finish_scsi_req(काष्ठा hptiop_hba *hba, u32 tag,
				काष्ठा hpt_iop_request_scsi_command *req);
अटल व्योम hptiop_host_request_callback_itl(काष्ठा hptiop_hba *hba, u32 tag);
अटल व्योम hptiop_iop_request_callback_itl(काष्ठा hptiop_hba *hba, u32 tag);
अटल व्योम hptiop_message_callback(काष्ठा hptiop_hba *hba, u32 msg);

अटल पूर्णांक iop_रुको_पढ़ोy_itl(काष्ठा hptiop_hba *hba, u32 millisec)
अणु
	u32 req = 0;
	पूर्णांक i;

	क्रम (i = 0; i < millisec; i++) अणु
		req = पढ़ोl(&hba->u.itl.iop->inbound_queue);
		अगर (req != IOPMU_QUEUE_EMPTY)
			अवरोध;
		msleep(1);
	पूर्ण

	अगर (req != IOPMU_QUEUE_EMPTY) अणु
		ग_लिखोl(req, &hba->u.itl.iop->outbound_queue);
		पढ़ोl(&hba->u.itl.iop->outbound_पूर्णांकstatus);
		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक iop_रुको_पढ़ोy_mv(काष्ठा hptiop_hba *hba, u32 millisec)
अणु
	वापस iop_send_sync_msg(hba, IOPMU_INBOUND_MSG0_NOP, millisec);
पूर्ण

अटल पूर्णांक iop_रुको_पढ़ोy_mvfrey(काष्ठा hptiop_hba *hba, u32 millisec)
अणु
	वापस iop_send_sync_msg(hba, IOPMU_INBOUND_MSG0_NOP, millisec);
पूर्ण

अटल व्योम hptiop_request_callback_itl(काष्ठा hptiop_hba *hba, u32 tag)
अणु
	अगर (tag & IOPMU_QUEUE_ADDR_HOST_BIT)
		hptiop_host_request_callback_itl(hba,
				tag & ~IOPMU_QUEUE_ADDR_HOST_BIT);
	अन्यथा
		hptiop_iop_request_callback_itl(hba, tag);
पूर्ण

अटल व्योम hptiop_drain_outbound_queue_itl(काष्ठा hptiop_hba *hba)
अणु
	u32 req;

	जबतक ((req = पढ़ोl(&hba->u.itl.iop->outbound_queue)) !=
						IOPMU_QUEUE_EMPTY) अणु

		अगर (req & IOPMU_QUEUE_MASK_HOST_BITS)
			hptiop_request_callback_itl(hba, req);
		अन्यथा अणु
			काष्ठा hpt_iop_request_header __iomem * p;

			p = (काष्ठा hpt_iop_request_header __iomem *)
				((अक्षर __iomem *)hba->u.itl.iop + req);

			अगर (पढ़ोl(&p->flags) & IOP_REQUEST_FLAG_SYNC_REQUEST) अणु
				अगर (पढ़ोl(&p->context))
					hptiop_request_callback_itl(hba, req);
				अन्यथा
					ग_लिखोl(1, &p->context);
			पूर्ण
			अन्यथा
				hptiop_request_callback_itl(hba, req);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक iop_पूर्णांकr_itl(काष्ठा hptiop_hba *hba)
अणु
	काष्ठा hpt_iopmu_itl __iomem *iop = hba->u.itl.iop;
	व्योम __iomem *plx = hba->u.itl.plx;
	u32 status;
	पूर्णांक ret = 0;

	अगर (plx && पढ़ोl(plx + 0x11C5C) & 0xf)
		ग_लिखोl(1, plx + 0x11C60);

	status = पढ़ोl(&iop->outbound_पूर्णांकstatus);

	अगर (status & IOPMU_OUTBOUND_INT_MSG0) अणु
		u32 msg = पढ़ोl(&iop->outbound_msgaddr0);

		dprपूर्णांकk("received outbound msg %x\n", msg);
		ग_लिखोl(IOPMU_OUTBOUND_INT_MSG0, &iop->outbound_पूर्णांकstatus);
		hptiop_message_callback(hba, msg);
		ret = 1;
	पूर्ण

	अगर (status & IOPMU_OUTBOUND_INT_POSTQUEUE) अणु
		hptiop_drain_outbound_queue_itl(hba);
		ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

अटल u64 mv_outbound_पढ़ो(काष्ठा hpt_iopmu_mv __iomem *mu)
अणु
	u32 outbound_tail = पढ़ोl(&mu->outbound_tail);
	u32 outbound_head = पढ़ोl(&mu->outbound_head);

	अगर (outbound_tail != outbound_head) अणु
		u64 p;

		स_नकल_fromio(&p, &mu->outbound_q[mu->outbound_tail], 8);
		outbound_tail++;

		अगर (outbound_tail == MVIOP_QUEUE_LEN)
			outbound_tail = 0;
		ग_लिखोl(outbound_tail, &mu->outbound_tail);
		वापस p;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

अटल व्योम mv_inbound_ग_लिखो(u64 p, काष्ठा hptiop_hba *hba)
अणु
	u32 inbound_head = पढ़ोl(&hba->u.mv.mu->inbound_head);
	u32 head = inbound_head + 1;

	अगर (head == MVIOP_QUEUE_LEN)
		head = 0;

	स_नकल_toio(&hba->u.mv.mu->inbound_q[inbound_head], &p, 8);
	ग_लिखोl(head, &hba->u.mv.mu->inbound_head);
	ग_लिखोl(MVIOP_MU_INBOUND_INT_POSTQUEUE,
			&hba->u.mv.regs->inbound_करोorbell);
पूर्ण

अटल व्योम hptiop_request_callback_mv(काष्ठा hptiop_hba *hba, u64 tag)
अणु
	u32 req_type = (tag >> 5) & 0x7;
	काष्ठा hpt_iop_request_scsi_command *req;

	dprपूर्णांकk("hptiop_request_callback_mv: tag=%llx\n", tag);

	BUG_ON((tag & MVIOP_MU_QUEUE_REQUEST_RETURN_CONTEXT) == 0);

	चयन (req_type) अणु
	हाल IOP_REQUEST_TYPE_GET_CONFIG:
	हाल IOP_REQUEST_TYPE_SET_CONFIG:
		hba->msg_करोne = 1;
		अवरोध;

	हाल IOP_REQUEST_TYPE_SCSI_COMMAND:
		req = hba->reqs[tag >> 8].req_virt;
		अगर (likely(tag & MVIOP_MU_QUEUE_REQUEST_RESULT_BIT))
			req->header.result = cpu_to_le32(IOP_RESULT_SUCCESS);

		hptiop_finish_scsi_req(hba, tag>>8, req);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक iop_पूर्णांकr_mv(काष्ठा hptiop_hba *hba)
अणु
	u32 status;
	पूर्णांक ret = 0;

	status = पढ़ोl(&hba->u.mv.regs->outbound_करोorbell);
	ग_लिखोl(~status, &hba->u.mv.regs->outbound_करोorbell);

	अगर (status & MVIOP_MU_OUTBOUND_INT_MSG) अणु
		u32 msg;
		msg = पढ़ोl(&hba->u.mv.mu->outbound_msg);
		dprपूर्णांकk("received outbound msg %x\n", msg);
		hptiop_message_callback(hba, msg);
		ret = 1;
	पूर्ण

	अगर (status & MVIOP_MU_OUTBOUND_INT_POSTQUEUE) अणु
		u64 tag;

		जबतक ((tag = mv_outbound_पढ़ो(hba->u.mv.mu)))
			hptiop_request_callback_mv(hba, tag);
		ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम hptiop_request_callback_mvfrey(काष्ठा hptiop_hba *hba, u32 _tag)
अणु
	u32 req_type = _tag & 0xf;
	काष्ठा hpt_iop_request_scsi_command *req;

	चयन (req_type) अणु
	हाल IOP_REQUEST_TYPE_GET_CONFIG:
	हाल IOP_REQUEST_TYPE_SET_CONFIG:
		hba->msg_करोne = 1;
		अवरोध;

	हाल IOP_REQUEST_TYPE_SCSI_COMMAND:
		req = hba->reqs[(_tag >> 4) & 0xff].req_virt;
		अगर (likely(_tag & IOPMU_QUEUE_REQUEST_RESULT_BIT))
			req->header.result = IOP_RESULT_SUCCESS;
		hptiop_finish_scsi_req(hba, (_tag >> 4) & 0xff, req);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक iop_पूर्णांकr_mvfrey(काष्ठा hptiop_hba *hba)
अणु
	u32 _tag, status, cptr, cur_rptr;
	पूर्णांक ret = 0;

	अगर (hba->initialized)
		ग_लिखोl(0, &(hba->u.mvfrey.mu->pcie_f0_पूर्णांक_enable));

	status = पढ़ोl(&(hba->u.mvfrey.mu->f0_करोorbell));
	अगर (status) अणु
		ग_लिखोl(status, &(hba->u.mvfrey.mu->f0_करोorbell));
		अगर (status & CPU_TO_F0_DRBL_MSG_BIT) अणु
			u32 msg = पढ़ोl(&(hba->u.mvfrey.mu->cpu_to_f0_msg_a));
			dprपूर्णांकk("received outbound msg %x\n", msg);
			hptiop_message_callback(hba, msg);
		पूर्ण
		ret = 1;
	पूर्ण

	status = पढ़ोl(&(hba->u.mvfrey.mu->isr_cause));
	अगर (status) अणु
		ग_लिखोl(status, &(hba->u.mvfrey.mu->isr_cause));
		करो अणु
			cptr = *hba->u.mvfrey.outlist_cptr & 0xff;
			cur_rptr = hba->u.mvfrey.outlist_rptr;
			जबतक (cur_rptr != cptr) अणु
				cur_rptr++;
				अगर (cur_rptr ==	hba->u.mvfrey.list_count)
					cur_rptr = 0;

				_tag = hba->u.mvfrey.outlist[cur_rptr].val;
				BUG_ON(!(_tag & IOPMU_QUEUE_MASK_HOST_BITS));
				hptiop_request_callback_mvfrey(hba, _tag);
				ret = 1;
			पूर्ण
			hba->u.mvfrey.outlist_rptr = cur_rptr;
		पूर्ण जबतक (cptr != (*hba->u.mvfrey.outlist_cptr & 0xff));
	पूर्ण

	अगर (hba->initialized)
		ग_लिखोl(0x1010, &(hba->u.mvfrey.mu->pcie_f0_पूर्णांक_enable));

	वापस ret;
पूर्ण

अटल पूर्णांक iop_send_sync_request_itl(काष्ठा hptiop_hba *hba,
					व्योम __iomem *_req, u32 millisec)
अणु
	काष्ठा hpt_iop_request_header __iomem *req = _req;
	u32 i;

	ग_लिखोl(पढ़ोl(&req->flags) | IOP_REQUEST_FLAG_SYNC_REQUEST, &req->flags);
	ग_लिखोl(0, &req->context);
	ग_लिखोl((अचिन्हित दीर्घ)req - (अचिन्हित दीर्घ)hba->u.itl.iop,
			&hba->u.itl.iop->inbound_queue);
	पढ़ोl(&hba->u.itl.iop->outbound_पूर्णांकstatus);

	क्रम (i = 0; i < millisec; i++) अणु
		iop_पूर्णांकr_itl(hba);
		अगर (पढ़ोl(&req->context))
			वापस 0;
		msleep(1);
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक iop_send_sync_request_mv(काष्ठा hptiop_hba *hba,
					u32 size_bits, u32 millisec)
अणु
	काष्ठा hpt_iop_request_header *reqhdr = hba->u.mv.पूर्णांकernal_req;
	u32 i;

	hba->msg_करोne = 0;
	reqhdr->flags |= cpu_to_le32(IOP_REQUEST_FLAG_SYNC_REQUEST);
	mv_inbound_ग_लिखो(hba->u.mv.पूर्णांकernal_req_phy |
			MVIOP_MU_QUEUE_ADDR_HOST_BIT | size_bits, hba);

	क्रम (i = 0; i < millisec; i++) अणु
		iop_पूर्णांकr_mv(hba);
		अगर (hba->msg_करोne)
			वापस 0;
		msleep(1);
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक iop_send_sync_request_mvfrey(काष्ठा hptiop_hba *hba,
					u32 size_bits, u32 millisec)
अणु
	काष्ठा hpt_iop_request_header *reqhdr =
		hba->u.mvfrey.पूर्णांकernal_req.req_virt;
	u32 i;

	hba->msg_करोne = 0;
	reqhdr->flags |= cpu_to_le32(IOP_REQUEST_FLAG_SYNC_REQUEST);
	hba->ops->post_req(hba, &(hba->u.mvfrey.पूर्णांकernal_req));

	क्रम (i = 0; i < millisec; i++) अणु
		iop_पूर्णांकr_mvfrey(hba);
		अगर (hba->msg_करोne)
			अवरोध;
		msleep(1);
	पूर्ण
	वापस hba->msg_करोne ? 0 : -1;
पूर्ण

अटल व्योम hptiop_post_msg_itl(काष्ठा hptiop_hba *hba, u32 msg)
अणु
	ग_लिखोl(msg, &hba->u.itl.iop->inbound_msgaddr0);
	पढ़ोl(&hba->u.itl.iop->outbound_पूर्णांकstatus);
पूर्ण

अटल व्योम hptiop_post_msg_mv(काष्ठा hptiop_hba *hba, u32 msg)
अणु
	ग_लिखोl(msg, &hba->u.mv.mu->inbound_msg);
	ग_लिखोl(MVIOP_MU_INBOUND_INT_MSG, &hba->u.mv.regs->inbound_करोorbell);
	पढ़ोl(&hba->u.mv.regs->inbound_करोorbell);
पूर्ण

अटल व्योम hptiop_post_msg_mvfrey(काष्ठा hptiop_hba *hba, u32 msg)
अणु
	ग_लिखोl(msg, &(hba->u.mvfrey.mu->f0_to_cpu_msg_a));
	पढ़ोl(&(hba->u.mvfrey.mu->f0_to_cpu_msg_a));
पूर्ण

अटल पूर्णांक iop_send_sync_msg(काष्ठा hptiop_hba *hba, u32 msg, u32 millisec)
अणु
	u32 i;

	hba->msg_करोne = 0;
	hba->ops->disable_पूर्णांकr(hba);
	hba->ops->post_msg(hba, msg);

	क्रम (i = 0; i < millisec; i++) अणु
		spin_lock_irq(hba->host->host_lock);
		hba->ops->iop_पूर्णांकr(hba);
		spin_unlock_irq(hba->host->host_lock);
		अगर (hba->msg_करोne)
			अवरोध;
		msleep(1);
	पूर्ण

	hba->ops->enable_पूर्णांकr(hba);
	वापस hba->msg_करोne? 0 : -1;
पूर्ण

अटल पूर्णांक iop_get_config_itl(काष्ठा hptiop_hba *hba,
				काष्ठा hpt_iop_request_get_config *config)
अणु
	u32 req32;
	काष्ठा hpt_iop_request_get_config __iomem *req;

	req32 = पढ़ोl(&hba->u.itl.iop->inbound_queue);
	अगर (req32 == IOPMU_QUEUE_EMPTY)
		वापस -1;

	req = (काष्ठा hpt_iop_request_get_config __iomem *)
			((अचिन्हित दीर्घ)hba->u.itl.iop + req32);

	ग_लिखोl(0, &req->header.flags);
	ग_लिखोl(IOP_REQUEST_TYPE_GET_CONFIG, &req->header.type);
	ग_लिखोl(माप(काष्ठा hpt_iop_request_get_config), &req->header.size);
	ग_लिखोl(IOP_RESULT_PENDING, &req->header.result);

	अगर (iop_send_sync_request_itl(hba, req, 20000)) अणु
		dprपूर्णांकk("Get config send cmd failed\n");
		वापस -1;
	पूर्ण

	स_नकल_fromio(config, req, माप(*config));
	ग_लिखोl(req32, &hba->u.itl.iop->outbound_queue);
	वापस 0;
पूर्ण

अटल पूर्णांक iop_get_config_mv(काष्ठा hptiop_hba *hba,
				काष्ठा hpt_iop_request_get_config *config)
अणु
	काष्ठा hpt_iop_request_get_config *req = hba->u.mv.पूर्णांकernal_req;

	req->header.flags = cpu_to_le32(IOP_REQUEST_FLAG_OUTPUT_CONTEXT);
	req->header.type = cpu_to_le32(IOP_REQUEST_TYPE_GET_CONFIG);
	req->header.size =
		cpu_to_le32(माप(काष्ठा hpt_iop_request_get_config));
	req->header.result = cpu_to_le32(IOP_RESULT_PENDING);
	req->header.context = cpu_to_le32(IOP_REQUEST_TYPE_GET_CONFIG<<5);
	req->header.context_hi32 = 0;

	अगर (iop_send_sync_request_mv(hba, 0, 20000)) अणु
		dprपूर्णांकk("Get config send cmd failed\n");
		वापस -1;
	पूर्ण

	स_नकल(config, req, माप(काष्ठा hpt_iop_request_get_config));
	वापस 0;
पूर्ण

अटल पूर्णांक iop_get_config_mvfrey(काष्ठा hptiop_hba *hba,
				काष्ठा hpt_iop_request_get_config *config)
अणु
	काष्ठा hpt_iop_request_get_config *info = hba->u.mvfrey.config;

	अगर (info->header.size != माप(काष्ठा hpt_iop_request_get_config) ||
			info->header.type != IOP_REQUEST_TYPE_GET_CONFIG)
		वापस -1;

	config->पूर्णांकerface_version = info->पूर्णांकerface_version;
	config->firmware_version = info->firmware_version;
	config->max_requests = info->max_requests;
	config->request_size = info->request_size;
	config->max_sg_count = info->max_sg_count;
	config->data_transfer_length = info->data_transfer_length;
	config->alignment_mask = info->alignment_mask;
	config->max_devices = info->max_devices;
	config->sdram_size = info->sdram_size;

	वापस 0;
पूर्ण

अटल पूर्णांक iop_set_config_itl(काष्ठा hptiop_hba *hba,
				काष्ठा hpt_iop_request_set_config *config)
अणु
	u32 req32;
	काष्ठा hpt_iop_request_set_config __iomem *req;

	req32 = पढ़ोl(&hba->u.itl.iop->inbound_queue);
	अगर (req32 == IOPMU_QUEUE_EMPTY)
		वापस -1;

	req = (काष्ठा hpt_iop_request_set_config __iomem *)
			((अचिन्हित दीर्घ)hba->u.itl.iop + req32);

	स_नकल_toio((u8 __iomem *)req + माप(काष्ठा hpt_iop_request_header),
		(u8 *)config + माप(काष्ठा hpt_iop_request_header),
		माप(काष्ठा hpt_iop_request_set_config) -
			माप(काष्ठा hpt_iop_request_header));

	ग_लिखोl(0, &req->header.flags);
	ग_लिखोl(IOP_REQUEST_TYPE_SET_CONFIG, &req->header.type);
	ग_लिखोl(माप(काष्ठा hpt_iop_request_set_config), &req->header.size);
	ग_लिखोl(IOP_RESULT_PENDING, &req->header.result);

	अगर (iop_send_sync_request_itl(hba, req, 20000)) अणु
		dprपूर्णांकk("Set config send cmd failed\n");
		वापस -1;
	पूर्ण

	ग_लिखोl(req32, &hba->u.itl.iop->outbound_queue);
	वापस 0;
पूर्ण

अटल पूर्णांक iop_set_config_mv(काष्ठा hptiop_hba *hba,
				काष्ठा hpt_iop_request_set_config *config)
अणु
	काष्ठा hpt_iop_request_set_config *req = hba->u.mv.पूर्णांकernal_req;

	स_नकल(req, config, माप(काष्ठा hpt_iop_request_set_config));
	req->header.flags = cpu_to_le32(IOP_REQUEST_FLAG_OUTPUT_CONTEXT);
	req->header.type = cpu_to_le32(IOP_REQUEST_TYPE_SET_CONFIG);
	req->header.size =
		cpu_to_le32(माप(काष्ठा hpt_iop_request_set_config));
	req->header.result = cpu_to_le32(IOP_RESULT_PENDING);
	req->header.context = cpu_to_le32(IOP_REQUEST_TYPE_SET_CONFIG<<5);
	req->header.context_hi32 = 0;

	अगर (iop_send_sync_request_mv(hba, 0, 20000)) अणु
		dprपूर्णांकk("Set config send cmd failed\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iop_set_config_mvfrey(काष्ठा hptiop_hba *hba,
				काष्ठा hpt_iop_request_set_config *config)
अणु
	काष्ठा hpt_iop_request_set_config *req =
		hba->u.mvfrey.पूर्णांकernal_req.req_virt;

	स_नकल(req, config, माप(काष्ठा hpt_iop_request_set_config));
	req->header.flags = cpu_to_le32(IOP_REQUEST_FLAG_OUTPUT_CONTEXT);
	req->header.type = cpu_to_le32(IOP_REQUEST_TYPE_SET_CONFIG);
	req->header.size =
		cpu_to_le32(माप(काष्ठा hpt_iop_request_set_config));
	req->header.result = cpu_to_le32(IOP_RESULT_PENDING);
	req->header.context = cpu_to_le32(IOP_REQUEST_TYPE_SET_CONFIG<<5);
	req->header.context_hi32 = 0;

	अगर (iop_send_sync_request_mvfrey(hba, 0, 20000)) अणु
		dprपूर्णांकk("Set config send cmd failed\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hptiop_enable_पूर्णांकr_itl(काष्ठा hptiop_hba *hba)
अणु
	ग_लिखोl(~(IOPMU_OUTBOUND_INT_POSTQUEUE | IOPMU_OUTBOUND_INT_MSG0),
		&hba->u.itl.iop->outbound_पूर्णांकmask);
पूर्ण

अटल व्योम hptiop_enable_पूर्णांकr_mv(काष्ठा hptiop_hba *hba)
अणु
	ग_लिखोl(MVIOP_MU_OUTBOUND_INT_POSTQUEUE | MVIOP_MU_OUTBOUND_INT_MSG,
		&hba->u.mv.regs->outbound_पूर्णांकmask);
पूर्ण

अटल व्योम hptiop_enable_पूर्णांकr_mvfrey(काष्ठा hptiop_hba *hba)
अणु
	ग_लिखोl(CPU_TO_F0_DRBL_MSG_BIT, &(hba->u.mvfrey.mu->f0_करोorbell_enable));
	ग_लिखोl(0x1, &(hba->u.mvfrey.mu->isr_enable));
	ग_लिखोl(0x1010, &(hba->u.mvfrey.mu->pcie_f0_पूर्णांक_enable));
पूर्ण

अटल पूर्णांक hptiop_initialize_iop(काष्ठा hptiop_hba *hba)
अणु
	/* enable पूर्णांकerrupts */
	hba->ops->enable_पूर्णांकr(hba);

	hba->initialized = 1;

	/* start background tasks */
	अगर (iop_send_sync_msg(hba,
			IOPMU_INBOUND_MSG0_START_BACKGROUND_TASK, 5000)) अणु
		prपूर्णांकk(KERN_ERR "scsi%d: fail to start background task\n",
			hba->host->host_no);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __iomem *hptiop_map_pci_bar(काष्ठा hptiop_hba *hba, पूर्णांक index)
अणु
	u32 mem_base_phy, length;
	व्योम __iomem *mem_base_virt;

	काष्ठा pci_dev *pcidev = hba->pcidev;


	अगर (!(pci_resource_flags(pcidev, index) & IORESOURCE_MEM)) अणु
		prपूर्णांकk(KERN_ERR "scsi%d: pci resource invalid\n",
				hba->host->host_no);
		वापस शून्य;
	पूर्ण

	mem_base_phy = pci_resource_start(pcidev, index);
	length = pci_resource_len(pcidev, index);
	mem_base_virt = ioremap(mem_base_phy, length);

	अगर (!mem_base_virt) अणु
		prपूर्णांकk(KERN_ERR "scsi%d: Fail to ioremap memory space\n",
				hba->host->host_no);
		वापस शून्य;
	पूर्ण
	वापस mem_base_virt;
पूर्ण

अटल पूर्णांक hptiop_map_pci_bar_itl(काष्ठा hptiop_hba *hba)
अणु
	काष्ठा pci_dev *pcidev = hba->pcidev;
	hba->u.itl.iop = hptiop_map_pci_bar(hba, 0);
	अगर (hba->u.itl.iop == शून्य)
		वापस -1;
	अगर ((pcidev->device & 0xff00) == 0x4400) अणु
		hba->u.itl.plx = hba->u.itl.iop;
		hba->u.itl.iop = hptiop_map_pci_bar(hba, 2);
		अगर (hba->u.itl.iop == शून्य) अणु
			iounmap(hba->u.itl.plx);
			वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम hptiop_unmap_pci_bar_itl(काष्ठा hptiop_hba *hba)
अणु
	अगर (hba->u.itl.plx)
		iounmap(hba->u.itl.plx);
	iounmap(hba->u.itl.iop);
पूर्ण

अटल पूर्णांक hptiop_map_pci_bar_mv(काष्ठा hptiop_hba *hba)
अणु
	hba->u.mv.regs = hptiop_map_pci_bar(hba, 0);
	अगर (hba->u.mv.regs == शून्य)
		वापस -1;

	hba->u.mv.mu = hptiop_map_pci_bar(hba, 2);
	अगर (hba->u.mv.mu == शून्य) अणु
		iounmap(hba->u.mv.regs);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hptiop_map_pci_bar_mvfrey(काष्ठा hptiop_hba *hba)
अणु
	hba->u.mvfrey.config = hptiop_map_pci_bar(hba, 0);
	अगर (hba->u.mvfrey.config == शून्य)
		वापस -1;

	hba->u.mvfrey.mu = hptiop_map_pci_bar(hba, 2);
	अगर (hba->u.mvfrey.mu == शून्य) अणु
		iounmap(hba->u.mvfrey.config);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hptiop_unmap_pci_bar_mv(काष्ठा hptiop_hba *hba)
अणु
	iounmap(hba->u.mv.regs);
	iounmap(hba->u.mv.mu);
पूर्ण

अटल व्योम hptiop_unmap_pci_bar_mvfrey(काष्ठा hptiop_hba *hba)
अणु
	iounmap(hba->u.mvfrey.config);
	iounmap(hba->u.mvfrey.mu);
पूर्ण

अटल व्योम hptiop_message_callback(काष्ठा hptiop_hba *hba, u32 msg)
अणु
	dprपूर्णांकk("iop message 0x%x\n", msg);

	अगर (msg == IOPMU_INBOUND_MSG0_NOP ||
		msg == IOPMU_INBOUND_MSG0_RESET_COMM)
		hba->msg_करोne = 1;

	अगर (!hba->initialized)
		वापस;

	अगर (msg == IOPMU_INBOUND_MSG0_RESET) अणु
		atomic_set(&hba->resetting, 0);
		wake_up(&hba->reset_wq);
	पूर्ण
	अन्यथा अगर (msg <= IOPMU_INBOUND_MSG0_MAX)
		hba->msg_करोne = 1;
पूर्ण

अटल काष्ठा hptiop_request *get_req(काष्ठा hptiop_hba *hba)
अणु
	काष्ठा hptiop_request *ret;

	dprपूर्णांकk("get_req : req=%p\n", hba->req_list);

	ret = hba->req_list;
	अगर (ret)
		hba->req_list = ret->next;

	वापस ret;
पूर्ण

अटल व्योम मुक्त_req(काष्ठा hptiop_hba *hba, काष्ठा hptiop_request *req)
अणु
	dprपूर्णांकk("free_req(%d, %p)\n", req->index, req);
	req->next = hba->req_list;
	hba->req_list = req;
पूर्ण

अटल व्योम hptiop_finish_scsi_req(काष्ठा hptiop_hba *hba, u32 tag,
				काष्ठा hpt_iop_request_scsi_command *req)
अणु
	काष्ठा scsi_cmnd *scp;

	dprपूर्णांकk("hptiop_finish_scsi_req: req=%p, type=%d, "
			"result=%d, context=0x%x tag=%d\n",
			req, req->header.type, req->header.result,
			req->header.context, tag);

	BUG_ON(!req->header.result);
	BUG_ON(req->header.type != cpu_to_le32(IOP_REQUEST_TYPE_SCSI_COMMAND));

	scp = hba->reqs[tag].scp;

	अगर (HPT_SCP(scp)->mapped)
		scsi_dma_unmap(scp);

	चयन (le32_to_cpu(req->header.result)) अणु
	हाल IOP_RESULT_SUCCESS:
		scsi_set_resid(scp,
			scsi_bufflen(scp) - le32_to_cpu(req->dataxfer_length));
		scp->result = (DID_OK<<16);
		अवरोध;
	हाल IOP_RESULT_BAD_TARGET:
		scp->result = (DID_BAD_TARGET<<16);
		अवरोध;
	हाल IOP_RESULT_BUSY:
		scp->result = (DID_BUS_BUSY<<16);
		अवरोध;
	हाल IOP_RESULT_RESET:
		scp->result = (DID_RESET<<16);
		अवरोध;
	हाल IOP_RESULT_FAIL:
		scp->result = (DID_ERROR<<16);
		अवरोध;
	हाल IOP_RESULT_INVALID_REQUEST:
		scp->result = (DID_ABORT<<16);
		अवरोध;
	हाल IOP_RESULT_CHECK_CONDITION:
		scsi_set_resid(scp,
			scsi_bufflen(scp) - le32_to_cpu(req->dataxfer_length));
		scp->result = SAM_STAT_CHECK_CONDITION;
		स_नकल(scp->sense_buffer, &req->sg_list, SCSI_SENSE_BUFFERSIZE);
		जाओ skip_resid;

	शेष:
		scp->result = DRIVER_INVALID << 24 | DID_ABORT << 16;
		अवरोध;
	पूर्ण

	scsi_set_resid(scp,
		scsi_bufflen(scp) - le32_to_cpu(req->dataxfer_length));

skip_resid:
	dprपूर्णांकk("scsi_done(%p)\n", scp);
	scp->scsi_करोne(scp);
	मुक्त_req(hba, &hba->reqs[tag]);
पूर्ण

अटल व्योम hptiop_host_request_callback_itl(काष्ठा hptiop_hba *hba, u32 _tag)
अणु
	काष्ठा hpt_iop_request_scsi_command *req;
	u32 tag;

	अगर (hba->iopपूर्णांकf_v2) अणु
		tag = _tag & ~IOPMU_QUEUE_REQUEST_RESULT_BIT;
		req = hba->reqs[tag].req_virt;
		अगर (likely(_tag & IOPMU_QUEUE_REQUEST_RESULT_BIT))
			req->header.result = cpu_to_le32(IOP_RESULT_SUCCESS);
	पूर्ण अन्यथा अणु
		tag = _tag;
		req = hba->reqs[tag].req_virt;
	पूर्ण

	hptiop_finish_scsi_req(hba, tag, req);
पूर्ण

अटल व्योम hptiop_iop_request_callback_itl(काष्ठा hptiop_hba *hba, u32 tag)
अणु
	काष्ठा hpt_iop_request_header __iomem *req;
	काष्ठा hpt_iop_request_ioctl_command __iomem *p;
	काष्ठा hpt_ioctl_k *arg;

	req = (काष्ठा hpt_iop_request_header __iomem *)
			((अचिन्हित दीर्घ)hba->u.itl.iop + tag);
	dprपूर्णांकk("hptiop_iop_request_callback_itl: req=%p, type=%d, "
			"result=%d, context=0x%x tag=%d\n",
			req, पढ़ोl(&req->type), पढ़ोl(&req->result),
			पढ़ोl(&req->context), tag);

	BUG_ON(!पढ़ोl(&req->result));
	BUG_ON(पढ़ोl(&req->type) != IOP_REQUEST_TYPE_IOCTL_COMMAND);

	p = (काष्ठा hpt_iop_request_ioctl_command __iomem *)req;
	arg = (काष्ठा hpt_ioctl_k *)(अचिन्हित दीर्घ)
		(पढ़ोl(&req->context) |
			((u64)पढ़ोl(&req->context_hi32)<<32));

	अगर (पढ़ोl(&req->result) == IOP_RESULT_SUCCESS) अणु
		arg->result = HPT_IOCTL_RESULT_OK;

		अगर (arg->outbuf_size)
			स_नकल_fromio(arg->outbuf,
				&p->buf[(पढ़ोl(&p->inbuf_size) + 3)& ~3],
				arg->outbuf_size);

		अगर (arg->bytes_वापसed)
			*arg->bytes_वापसed = arg->outbuf_size;
	पूर्ण
	अन्यथा
		arg->result = HPT_IOCTL_RESULT_FAILED;

	arg->करोne(arg);
	ग_लिखोl(tag, &hba->u.itl.iop->outbound_queue);
पूर्ण

अटल irqवापस_t hptiop_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा hptiop_hba  *hba = dev_id;
	पूर्णांक  handled;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(hba->host->host_lock, flags);
	handled = hba->ops->iop_पूर्णांकr(hba);
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	वापस handled;
पूर्ण

अटल पूर्णांक hptiop_buildsgl(काष्ठा scsi_cmnd *scp, काष्ठा hpt_iopsg *psg)
अणु
	काष्ठा Scsi_Host *host = scp->device->host;
	काष्ठा hptiop_hba *hba = (काष्ठा hptiop_hba *)host->hostdata;
	काष्ठा scatterlist *sg;
	पूर्णांक idx, nseg;

	nseg = scsi_dma_map(scp);
	BUG_ON(nseg < 0);
	अगर (!nseg)
		वापस 0;

	HPT_SCP(scp)->sgcnt = nseg;
	HPT_SCP(scp)->mapped = 1;

	BUG_ON(HPT_SCP(scp)->sgcnt > hba->max_sg_descriptors);

	scsi_क्रम_each_sg(scp, sg, HPT_SCP(scp)->sgcnt, idx) अणु
		psg[idx].pci_address = cpu_to_le64(sg_dma_address(sg)) |
			hba->ops->host_phy_flag;
		psg[idx].size = cpu_to_le32(sg_dma_len(sg));
		psg[idx].eot = (idx == HPT_SCP(scp)->sgcnt - 1) ?
			cpu_to_le32(1) : 0;
	पूर्ण
	वापस HPT_SCP(scp)->sgcnt;
पूर्ण

अटल व्योम hptiop_post_req_itl(काष्ठा hptiop_hba *hba,
					काष्ठा hptiop_request *_req)
अणु
	काष्ठा hpt_iop_request_header *reqhdr = _req->req_virt;

	reqhdr->context = cpu_to_le32(IOPMU_QUEUE_ADDR_HOST_BIT |
							(u32)_req->index);
	reqhdr->context_hi32 = 0;

	अगर (hba->iopपूर्णांकf_v2) अणु
		u32 size, size_bits;

		size = le32_to_cpu(reqhdr->size);
		अगर (size < 256)
			size_bits = IOPMU_QUEUE_REQUEST_SIZE_BIT;
		अन्यथा अगर (size < 512)
			size_bits = IOPMU_QUEUE_ADDR_HOST_BIT;
		अन्यथा
			size_bits = IOPMU_QUEUE_REQUEST_SIZE_BIT |
						IOPMU_QUEUE_ADDR_HOST_BIT;
		ग_लिखोl(_req->req_shअगरted_phy | size_bits,
			&hba->u.itl.iop->inbound_queue);
	पूर्ण अन्यथा
		ग_लिखोl(_req->req_shअगरted_phy | IOPMU_QUEUE_ADDR_HOST_BIT,
					&hba->u.itl.iop->inbound_queue);
पूर्ण

अटल व्योम hptiop_post_req_mv(काष्ठा hptiop_hba *hba,
					काष्ठा hptiop_request *_req)
अणु
	काष्ठा hpt_iop_request_header *reqhdr = _req->req_virt;
	u32 size, size_bit;

	reqhdr->context = cpu_to_le32(_req->index<<8 |
					IOP_REQUEST_TYPE_SCSI_COMMAND<<5);
	reqhdr->context_hi32 = 0;
	size = le32_to_cpu(reqhdr->size);

	अगर (size <= 256)
		size_bit = 0;
	अन्यथा अगर (size <= 256*2)
		size_bit = 1;
	अन्यथा अगर (size <= 256*3)
		size_bit = 2;
	अन्यथा
		size_bit = 3;

	mv_inbound_ग_लिखो((_req->req_shअगरted_phy << 5) |
		MVIOP_MU_QUEUE_ADDR_HOST_BIT | size_bit, hba);
पूर्ण

अटल व्योम hptiop_post_req_mvfrey(काष्ठा hptiop_hba *hba,
					काष्ठा hptiop_request *_req)
अणु
	काष्ठा hpt_iop_request_header *reqhdr = _req->req_virt;
	u32 index;

	reqhdr->flags |= cpu_to_le32(IOP_REQUEST_FLAG_OUTPUT_CONTEXT |
			IOP_REQUEST_FLAG_ADDR_BITS |
			((_req->req_shअगरted_phy >> 11) & 0xffff0000));
	reqhdr->context = cpu_to_le32(IOPMU_QUEUE_ADDR_HOST_BIT |
			(_req->index << 4) | reqhdr->type);
	reqhdr->context_hi32 = cpu_to_le32((_req->req_shअगरted_phy << 5) &
			0xffffffff);

	hba->u.mvfrey.inlist_wptr++;
	index = hba->u.mvfrey.inlist_wptr & 0x3fff;

	अगर (index == hba->u.mvfrey.list_count) अणु
		index = 0;
		hba->u.mvfrey.inlist_wptr &= ~0x3fff;
		hba->u.mvfrey.inlist_wptr ^= CL_POINTER_TOGGLE;
	पूर्ण

	hba->u.mvfrey.inlist[index].addr =
			(dma_addr_t)_req->req_shअगरted_phy << 5;
	hba->u.mvfrey.inlist[index].पूर्णांकrfc_len = (reqhdr->size + 3) / 4;
	ग_लिखोl(hba->u.mvfrey.inlist_wptr,
		&(hba->u.mvfrey.mu->inbound_ग_लिखो_ptr));
	पढ़ोl(&(hba->u.mvfrey.mu->inbound_ग_लिखो_ptr));
पूर्ण

अटल पूर्णांक hptiop_reset_comm_itl(काष्ठा hptiop_hba *hba)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक hptiop_reset_comm_mv(काष्ठा hptiop_hba *hba)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक hptiop_reset_comm_mvfrey(काष्ठा hptiop_hba *hba)
अणु
	u32 list_count = hba->u.mvfrey.list_count;

	अगर (iop_send_sync_msg(hba, IOPMU_INBOUND_MSG0_RESET_COMM, 3000))
		वापस -1;

	/* रुको 100ms क्रम MCU पढ़ोy */
	msleep(100);

	ग_लिखोl(cpu_to_le32(hba->u.mvfrey.inlist_phy & 0xffffffff),
			&(hba->u.mvfrey.mu->inbound_base));
	ग_लिखोl(cpu_to_le32((hba->u.mvfrey.inlist_phy >> 16) >> 16),
			&(hba->u.mvfrey.mu->inbound_base_high));

	ग_लिखोl(cpu_to_le32(hba->u.mvfrey.outlist_phy & 0xffffffff),
			&(hba->u.mvfrey.mu->outbound_base));
	ग_लिखोl(cpu_to_le32((hba->u.mvfrey.outlist_phy >> 16) >> 16),
			&(hba->u.mvfrey.mu->outbound_base_high));

	ग_लिखोl(cpu_to_le32(hba->u.mvfrey.outlist_cptr_phy & 0xffffffff),
			&(hba->u.mvfrey.mu->outbound_shaकरोw_base));
	ग_लिखोl(cpu_to_le32((hba->u.mvfrey.outlist_cptr_phy >> 16) >> 16),
			&(hba->u.mvfrey.mu->outbound_shaकरोw_base_high));

	hba->u.mvfrey.inlist_wptr = (list_count - 1) | CL_POINTER_TOGGLE;
	*hba->u.mvfrey.outlist_cptr = (list_count - 1) | CL_POINTER_TOGGLE;
	hba->u.mvfrey.outlist_rptr = list_count - 1;
	वापस 0;
पूर्ण

अटल पूर्णांक hptiop_queuecommand_lck(काष्ठा scsi_cmnd *scp,
				व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	काष्ठा Scsi_Host *host = scp->device->host;
	काष्ठा hptiop_hba *hba = (काष्ठा hptiop_hba *)host->hostdata;
	काष्ठा hpt_iop_request_scsi_command *req;
	पूर्णांक sg_count = 0;
	काष्ठा hptiop_request *_req;

	BUG_ON(!करोne);
	scp->scsi_करोne = करोne;

	_req = get_req(hba);
	अगर (_req == शून्य) अणु
		dprपूर्णांकk("hptiop_queuecmd : no free req\n");
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	_req->scp = scp;

	dprपूर्णांकk("hptiop_queuecmd(scp=%p) %d/%d/%d/%llu cdb=(%08x-%08x-%08x-%08x) "
			"req_index=%d, req=%p\n",
			scp,
			host->host_no, scp->device->channel,
			scp->device->id, scp->device->lun,
			cpu_to_be32(((u32 *)scp->cmnd)[0]),
			cpu_to_be32(((u32 *)scp->cmnd)[1]),
			cpu_to_be32(((u32 *)scp->cmnd)[2]),
			cpu_to_be32(((u32 *)scp->cmnd)[3]),
			_req->index, _req->req_virt);

	scp->result = 0;

	अगर (scp->device->channel ||
			(scp->device->id > hba->max_devices) ||
			((scp->device->id == (hba->max_devices-1)) && scp->device->lun)) अणु
		scp->result = DID_BAD_TARGET << 16;
		मुक्त_req(hba, _req);
		जाओ cmd_करोne;
	पूर्ण

	req = _req->req_virt;

	/* build S/G table */
	sg_count = hptiop_buildsgl(scp, req->sg_list);
	अगर (!sg_count)
		HPT_SCP(scp)->mapped = 0;

	req->header.flags = cpu_to_le32(IOP_REQUEST_FLAG_OUTPUT_CONTEXT);
	req->header.type = cpu_to_le32(IOP_REQUEST_TYPE_SCSI_COMMAND);
	req->header.result = cpu_to_le32(IOP_RESULT_PENDING);
	req->dataxfer_length = cpu_to_le32(scsi_bufflen(scp));
	req->channel = scp->device->channel;
	req->target = scp->device->id;
	req->lun = scp->device->lun;
	req->header.size = cpu_to_le32(
				माप(काष्ठा hpt_iop_request_scsi_command)
				 - माप(काष्ठा hpt_iopsg)
				 + sg_count * माप(काष्ठा hpt_iopsg));

	स_नकल(req->cdb, scp->cmnd, माप(req->cdb));
	hba->ops->post_req(hba, _req);
	वापस 0;

cmd_करोne:
	dprपूर्णांकk("scsi_done(scp=%p)\n", scp);
	scp->scsi_करोne(scp);
	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(hptiop_queuecommand)

अटल स्थिर अक्षर *hptiop_info(काष्ठा Scsi_Host *host)
अणु
	वापस driver_name_दीर्घ;
पूर्ण

अटल पूर्णांक hptiop_reset_hba(काष्ठा hptiop_hba *hba)
अणु
	अगर (atomic_xchg(&hba->resetting, 1) == 0) अणु
		atomic_inc(&hba->reset_count);
		hba->ops->post_msg(hba, IOPMU_INBOUND_MSG0_RESET);
	पूर्ण

	रुको_event_समयout(hba->reset_wq,
			atomic_पढ़ो(&hba->resetting) == 0, 60 * HZ);

	अगर (atomic_पढ़ो(&hba->resetting)) अणु
		/* IOP is in unknown state, पात reset */
		prपूर्णांकk(KERN_ERR "scsi%d: reset failed\n", hba->host->host_no);
		वापस -1;
	पूर्ण

	अगर (iop_send_sync_msg(hba,
		IOPMU_INBOUND_MSG0_START_BACKGROUND_TASK, 5000)) अणु
		dprपूर्णांकk("scsi%d: fail to start background task\n",
				hba->host->host_no);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hptiop_reset(काष्ठा scsi_cmnd *scp)
अणु
	काष्ठा hptiop_hba * hba = (काष्ठा hptiop_hba *)scp->device->host->hostdata;

	prपूर्णांकk(KERN_WARNING "hptiop_reset(%d/%d/%d)\n",
	       scp->device->host->host_no, -1, -1);

	वापस hptiop_reset_hba(hba)? FAILED : SUCCESS;
पूर्ण

अटल पूर्णांक hptiop_adjust_disk_queue_depth(काष्ठा scsi_device *sdev,
					  पूर्णांक queue_depth)
अणु
	काष्ठा hptiop_hba *hba = (काष्ठा hptiop_hba *)sdev->host->hostdata;

	अगर (queue_depth > hba->max_requests)
		queue_depth = hba->max_requests;
	वापस scsi_change_queue_depth(sdev, queue_depth);
पूर्ण

अटल sमाप_प्रकार hptiop_show_version(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", driver_ver);
पूर्ण

अटल sमाप_प्रकार hptiop_show_fw_version(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *host = class_to_shost(dev);
	काष्ठा hptiop_hba *hba = (काष्ठा hptiop_hba *)host->hostdata;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d.%d.%d.%d\n",
				hba->firmware_version >> 24,
				(hba->firmware_version >> 16) & 0xff,
				(hba->firmware_version >> 8) & 0xff,
				hba->firmware_version & 0xff);
पूर्ण

अटल काष्ठा device_attribute hptiop_attr_version = अणु
	.attr = अणु
		.name = "driver-version",
		.mode = S_IRUGO,
	पूर्ण,
	.show = hptiop_show_version,
पूर्ण;

अटल काष्ठा device_attribute hptiop_attr_fw_version = अणु
	.attr = अणु
		.name = "firmware-version",
		.mode = S_IRUGO,
	पूर्ण,
	.show = hptiop_show_fw_version,
पूर्ण;

अटल काष्ठा device_attribute *hptiop_attrs[] = अणु
	&hptiop_attr_version,
	&hptiop_attr_fw_version,
	शून्य
पूर्ण;

अटल पूर्णांक hptiop_slave_config(काष्ठा scsi_device *sdev)
अणु
	अगर (sdev->type == TYPE_TAPE)
		blk_queue_max_hw_sectors(sdev->request_queue, 8192);

	वापस 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा driver_ढाँचा = अणु
	.module                     = THIS_MODULE,
	.name                       = driver_name,
	.queuecommand               = hptiop_queuecommand,
	.eh_host_reset_handler      = hptiop_reset,
	.info                       = hptiop_info,
	.emulated                   = 0,
	.proc_name                  = driver_name,
	.shost_attrs                = hptiop_attrs,
	.slave_configure            = hptiop_slave_config,
	.this_id                    = -1,
	.change_queue_depth         = hptiop_adjust_disk_queue_depth,
पूर्ण;

अटल पूर्णांक hptiop_पूर्णांकernal_meदो_स्मृति_itl(काष्ठा hptiop_hba *hba)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक hptiop_पूर्णांकernal_meदो_स्मृति_mv(काष्ठा hptiop_hba *hba)
अणु
	hba->u.mv.पूर्णांकernal_req = dma_alloc_coherent(&hba->pcidev->dev,
			0x800, &hba->u.mv.पूर्णांकernal_req_phy, GFP_KERNEL);
	अगर (hba->u.mv.पूर्णांकernal_req)
		वापस 0;
	अन्यथा
		वापस -1;
पूर्ण

अटल पूर्णांक hptiop_पूर्णांकernal_meदो_स्मृति_mvfrey(काष्ठा hptiop_hba *hba)
अणु
	u32 list_count = पढ़ोl(&hba->u.mvfrey.mu->inbound_conf_ctl);
	अक्षर *p;
	dma_addr_t phy;

	BUG_ON(hba->max_request_size == 0);

	अगर (list_count == 0) अणु
		BUG_ON(1);
		वापस -1;
	पूर्ण

	list_count >>= 16;

	hba->u.mvfrey.list_count = list_count;
	hba->u.mvfrey.पूर्णांकernal_mem_size = 0x800 +
			list_count * माप(काष्ठा mvfrey_inlist_entry) +
			list_count * माप(काष्ठा mvfrey_outlist_entry) +
			माप(पूर्णांक);

	p = dma_alloc_coherent(&hba->pcidev->dev,
			hba->u.mvfrey.पूर्णांकernal_mem_size, &phy, GFP_KERNEL);
	अगर (!p)
		वापस -1;

	hba->u.mvfrey.पूर्णांकernal_req.req_virt = p;
	hba->u.mvfrey.पूर्णांकernal_req.req_shअगरted_phy = phy >> 5;
	hba->u.mvfrey.पूर्णांकernal_req.scp = शून्य;
	hba->u.mvfrey.पूर्णांकernal_req.next = शून्य;

	p += 0x800;
	phy += 0x800;

	hba->u.mvfrey.inlist = (काष्ठा mvfrey_inlist_entry *)p;
	hba->u.mvfrey.inlist_phy = phy;

	p += list_count * माप(काष्ठा mvfrey_inlist_entry);
	phy += list_count * माप(काष्ठा mvfrey_inlist_entry);

	hba->u.mvfrey.outlist = (काष्ठा mvfrey_outlist_entry *)p;
	hba->u.mvfrey.outlist_phy = phy;

	p += list_count * माप(काष्ठा mvfrey_outlist_entry);
	phy += list_count * माप(काष्ठा mvfrey_outlist_entry);

	hba->u.mvfrey.outlist_cptr = (__le32 *)p;
	hba->u.mvfrey.outlist_cptr_phy = phy;

	वापस 0;
पूर्ण

अटल पूर्णांक hptiop_पूर्णांकernal_memमुक्त_itl(काष्ठा hptiop_hba *hba)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक hptiop_पूर्णांकernal_memमुक्त_mv(काष्ठा hptiop_hba *hba)
अणु
	अगर (hba->u.mv.पूर्णांकernal_req) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, 0x800,
			hba->u.mv.पूर्णांकernal_req, hba->u.mv.पूर्णांकernal_req_phy);
		वापस 0;
	पूर्ण अन्यथा
		वापस -1;
पूर्ण

अटल पूर्णांक hptiop_पूर्णांकernal_memमुक्त_mvfrey(काष्ठा hptiop_hba *hba)
अणु
	अगर (hba->u.mvfrey.पूर्णांकernal_req.req_virt) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev,
			hba->u.mvfrey.पूर्णांकernal_mem_size,
			hba->u.mvfrey.पूर्णांकernal_req.req_virt,
			(dma_addr_t)
			hba->u.mvfrey.पूर्णांकernal_req.req_shअगरted_phy << 5);
		वापस 0;
	पूर्ण अन्यथा
		वापस -1;
पूर्ण

अटल पूर्णांक hptiop_probe(काष्ठा pci_dev *pcidev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा Scsi_Host *host = शून्य;
	काष्ठा hptiop_hba *hba;
	काष्ठा hptiop_adapter_ops *iop_ops;
	काष्ठा hpt_iop_request_get_config iop_config;
	काष्ठा hpt_iop_request_set_config set_config;
	dma_addr_t start_phy;
	व्योम *start_virt;
	u32 offset, i, req_size;
	पूर्णांक rc;

	dprपूर्णांकk("hptiop_probe(%p)\n", pcidev);

	अगर (pci_enable_device(pcidev)) अणु
		prपूर्णांकk(KERN_ERR "hptiop: fail to enable pci device\n");
		वापस -ENODEV;
	पूर्ण

	prपूर्णांकk(KERN_INFO "adapter at PCI %d:%d:%d, IRQ %d\n",
		pcidev->bus->number, pcidev->devfn >> 3, pcidev->devfn & 7,
		pcidev->irq);

	pci_set_master(pcidev);

	/* Enable 64bit DMA अगर possible */
	iop_ops = (काष्ठा hptiop_adapter_ops *)id->driver_data;
	rc = dma_set_mask(&pcidev->dev,
			  DMA_BIT_MASK(iop_ops->hw_dma_bit_mask));
	अगर (rc)
		rc = dma_set_mask(&pcidev->dev, DMA_BIT_MASK(32));

	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "hptiop: fail to set dma_mask\n");
		जाओ disable_pci_device;
	पूर्ण

	अगर (pci_request_regions(pcidev, driver_name)) अणु
		prपूर्णांकk(KERN_ERR "hptiop: pci_request_regions failed\n");
		जाओ disable_pci_device;
	पूर्ण

	host = scsi_host_alloc(&driver_ढाँचा, माप(काष्ठा hptiop_hba));
	अगर (!host) अणु
		prपूर्णांकk(KERN_ERR "hptiop: fail to alloc scsi host\n");
		जाओ मुक्त_pci_regions;
	पूर्ण

	hba = (काष्ठा hptiop_hba *)host->hostdata;
	स_रखो(hba, 0, माप(काष्ठा hptiop_hba));

	hba->ops = iop_ops;
	hba->pcidev = pcidev;
	hba->host = host;
	hba->initialized = 0;
	hba->iopपूर्णांकf_v2 = 0;

	atomic_set(&hba->resetting, 0);
	atomic_set(&hba->reset_count, 0);

	init_रुकोqueue_head(&hba->reset_wq);
	init_रुकोqueue_head(&hba->ioctl_wq);

	host->max_lun = 128;
	host->max_channel = 0;
	host->io_port = 0;
	host->n_io_port = 0;
	host->irq = pcidev->irq;

	अगर (hba->ops->map_pci_bar(hba))
		जाओ मुक्त_scsi_host;

	अगर (hba->ops->iop_रुको_पढ़ोy(hba, 20000)) अणु
		prपूर्णांकk(KERN_ERR "scsi%d: firmware not ready\n",
				hba->host->host_no);
		जाओ unmap_pci_bar;
	पूर्ण

	अगर (hba->ops->family == MV_BASED_IOP) अणु
		अगर (hba->ops->पूर्णांकernal_meदो_स्मृति(hba)) अणु
			prपूर्णांकk(KERN_ERR "scsi%d: internal_memalloc failed\n",
				hba->host->host_no);
			जाओ unmap_pci_bar;
		पूर्ण
	पूर्ण

	अगर (hba->ops->get_config(hba, &iop_config)) अणु
		prपूर्णांकk(KERN_ERR "scsi%d: get config failed\n",
				hba->host->host_no);
		जाओ unmap_pci_bar;
	पूर्ण

	hba->max_requests = min(le32_to_cpu(iop_config.max_requests),
				HPTIOP_MAX_REQUESTS);
	hba->max_devices = le32_to_cpu(iop_config.max_devices);
	hba->max_request_size = le32_to_cpu(iop_config.request_size);
	hba->max_sg_descriptors = le32_to_cpu(iop_config.max_sg_count);
	hba->firmware_version = le32_to_cpu(iop_config.firmware_version);
	hba->पूर्णांकerface_version = le32_to_cpu(iop_config.पूर्णांकerface_version);
	hba->sdram_size = le32_to_cpu(iop_config.sdram_size);

	अगर (hba->ops->family == MVFREY_BASED_IOP) अणु
		अगर (hba->ops->पूर्णांकernal_meदो_स्मृति(hba)) अणु
			prपूर्णांकk(KERN_ERR "scsi%d: internal_memalloc failed\n",
				hba->host->host_no);
			जाओ unmap_pci_bar;
		पूर्ण
		अगर (hba->ops->reset_comm(hba)) अणु
			prपूर्णांकk(KERN_ERR "scsi%d: reset comm failed\n",
					hba->host->host_no);
			जाओ unmap_pci_bar;
		पूर्ण
	पूर्ण

	अगर (hba->firmware_version > 0x01020000 ||
			hba->पूर्णांकerface_version > 0x01020000)
		hba->iopपूर्णांकf_v2 = 1;

	host->max_sectors = le32_to_cpu(iop_config.data_transfer_length) >> 9;
	host->max_id = le32_to_cpu(iop_config.max_devices);
	host->sg_tablesize = le32_to_cpu(iop_config.max_sg_count);
	host->can_queue = le32_to_cpu(iop_config.max_requests);
	host->cmd_per_lun = le32_to_cpu(iop_config.max_requests);
	host->max_cmd_len = 16;

	req_size = माप(काष्ठा hpt_iop_request_scsi_command)
		+ माप(काष्ठा hpt_iopsg) * (hba->max_sg_descriptors - 1);
	अगर ((req_size & 0x1f) != 0)
		req_size = (req_size + 0x1f) & ~0x1f;

	स_रखो(&set_config, 0, माप(काष्ठा hpt_iop_request_set_config));
	set_config.iop_id = cpu_to_le32(host->host_no);
	set_config.vbus_id = cpu_to_le16(host->host_no);
	set_config.max_host_request_size = cpu_to_le16(req_size);

	अगर (hba->ops->set_config(hba, &set_config)) अणु
		prपूर्णांकk(KERN_ERR "scsi%d: set config failed\n",
				hba->host->host_no);
		जाओ unmap_pci_bar;
	पूर्ण

	pci_set_drvdata(pcidev, host);

	अगर (request_irq(pcidev->irq, hptiop_पूर्णांकr, IRQF_SHARED,
					driver_name, hba)) अणु
		prपूर्णांकk(KERN_ERR "scsi%d: request irq %d failed\n",
					hba->host->host_no, pcidev->irq);
		जाओ unmap_pci_bar;
	पूर्ण

	/* Allocate request mem */

	dprपूर्णांकk("req_size=%d, max_requests=%d\n", req_size, hba->max_requests);

	hba->req_size = req_size;
	hba->req_list = शून्य;

	क्रम (i = 0; i < hba->max_requests; i++) अणु
		start_virt = dma_alloc_coherent(&pcidev->dev,
					hba->req_size + 0x20,
					&start_phy, GFP_KERNEL);

		अगर (!start_virt) अणु
			prपूर्णांकk(KERN_ERR "scsi%d: fail to alloc request mem\n",
						hba->host->host_no);
			जाओ मुक्त_request_mem;
		पूर्ण

		hba->dma_coherent[i] = start_virt;
		hba->dma_coherent_handle[i] = start_phy;

		अगर ((start_phy & 0x1f) != 0) अणु
			offset = ((start_phy + 0x1f) & ~0x1f) - start_phy;
			start_phy += offset;
			start_virt += offset;
		पूर्ण

		hba->reqs[i].next = शून्य;
		hba->reqs[i].req_virt = start_virt;
		hba->reqs[i].req_shअगरted_phy = start_phy >> 5;
		hba->reqs[i].index = i;
		मुक्त_req(hba, &hba->reqs[i]);
	पूर्ण

	/* Enable Interrupt and start background task */
	अगर (hptiop_initialize_iop(hba))
		जाओ मुक्त_request_mem;

	अगर (scsi_add_host(host, &pcidev->dev)) अणु
		prपूर्णांकk(KERN_ERR "scsi%d: scsi_add_host failed\n",
					hba->host->host_no);
		जाओ मुक्त_request_mem;
	पूर्ण

	scsi_scan_host(host);

	dprपूर्णांकk("scsi%d: hptiop_probe successfully\n", hba->host->host_no);
	वापस 0;

मुक्त_request_mem:
	क्रम (i = 0; i < hba->max_requests; i++) अणु
		अगर (hba->dma_coherent[i] && hba->dma_coherent_handle[i])
			dma_मुक्त_coherent(&hba->pcidev->dev,
					hba->req_size + 0x20,
					hba->dma_coherent[i],
					hba->dma_coherent_handle[i]);
		अन्यथा
			अवरोध;
	पूर्ण

	मुक्त_irq(hba->pcidev->irq, hba);

unmap_pci_bar:
	hba->ops->पूर्णांकernal_memमुक्त(hba);

	hba->ops->unmap_pci_bar(hba);

मुक्त_scsi_host:
	scsi_host_put(host);

मुक्त_pci_regions:
	pci_release_regions(pcidev);

disable_pci_device:
	pci_disable_device(pcidev);

	dprपूर्णांकk("scsi%d: hptiop_probe fail\n", host ? host->host_no : 0);
	वापस -ENODEV;
पूर्ण

अटल व्योम hptiop_shutकरोwn(काष्ठा pci_dev *pcidev)
अणु
	काष्ठा Scsi_Host *host = pci_get_drvdata(pcidev);
	काष्ठा hptiop_hba *hba = (काष्ठा hptiop_hba *)host->hostdata;

	dprपूर्णांकk("hptiop_shutdown(%p)\n", hba);

	/* stop the iop */
	अगर (iop_send_sync_msg(hba, IOPMU_INBOUND_MSG0_SHUTDOWN, 60000))
		prपूर्णांकk(KERN_ERR "scsi%d: shutdown the iop timeout\n",
					hba->host->host_no);

	/* disable all outbound पूर्णांकerrupts */
	hba->ops->disable_पूर्णांकr(hba);
पूर्ण

अटल व्योम hptiop_disable_पूर्णांकr_itl(काष्ठा hptiop_hba *hba)
अणु
	u32 पूर्णांक_mask;

	पूर्णांक_mask = पढ़ोl(&hba->u.itl.iop->outbound_पूर्णांकmask);
	ग_लिखोl(पूर्णांक_mask |
		IOPMU_OUTBOUND_INT_MSG0 | IOPMU_OUTBOUND_INT_POSTQUEUE,
		&hba->u.itl.iop->outbound_पूर्णांकmask);
	पढ़ोl(&hba->u.itl.iop->outbound_पूर्णांकmask);
पूर्ण

अटल व्योम hptiop_disable_पूर्णांकr_mv(काष्ठा hptiop_hba *hba)
अणु
	ग_लिखोl(0, &hba->u.mv.regs->outbound_पूर्णांकmask);
	पढ़ोl(&hba->u.mv.regs->outbound_पूर्णांकmask);
पूर्ण

अटल व्योम hptiop_disable_पूर्णांकr_mvfrey(काष्ठा hptiop_hba *hba)
अणु
	ग_लिखोl(0, &(hba->u.mvfrey.mu->f0_करोorbell_enable));
	पढ़ोl(&(hba->u.mvfrey.mu->f0_करोorbell_enable));
	ग_लिखोl(0, &(hba->u.mvfrey.mu->isr_enable));
	पढ़ोl(&(hba->u.mvfrey.mu->isr_enable));
	ग_लिखोl(0, &(hba->u.mvfrey.mu->pcie_f0_पूर्णांक_enable));
	पढ़ोl(&(hba->u.mvfrey.mu->pcie_f0_पूर्णांक_enable));
पूर्ण

अटल व्योम hptiop_हटाओ(काष्ठा pci_dev *pcidev)
अणु
	काष्ठा Scsi_Host *host = pci_get_drvdata(pcidev);
	काष्ठा hptiop_hba *hba = (काष्ठा hptiop_hba *)host->hostdata;
	u32 i;

	dprपूर्णांकk("scsi%d: hptiop_remove\n", hba->host->host_no);

	scsi_हटाओ_host(host);

	hptiop_shutकरोwn(pcidev);

	मुक्त_irq(hba->pcidev->irq, hba);

	क्रम (i = 0; i < hba->max_requests; i++) अणु
		अगर (hba->dma_coherent[i] && hba->dma_coherent_handle[i])
			dma_मुक्त_coherent(&hba->pcidev->dev,
					hba->req_size + 0x20,
					hba->dma_coherent[i],
					hba->dma_coherent_handle[i]);
		अन्यथा
			अवरोध;
	पूर्ण

	hba->ops->पूर्णांकernal_memमुक्त(hba);

	hba->ops->unmap_pci_bar(hba);

	pci_release_regions(hba->pcidev);
	pci_set_drvdata(hba->pcidev, शून्य);
	pci_disable_device(hba->pcidev);

	scsi_host_put(host);
पूर्ण

अटल काष्ठा hptiop_adapter_ops hptiop_itl_ops = अणु
	.family            = INTEL_BASED_IOP,
	.iop_रुको_पढ़ोy    = iop_रुको_पढ़ोy_itl,
	.पूर्णांकernal_meदो_स्मृति = hptiop_पूर्णांकernal_meदो_स्मृति_itl,
	.पूर्णांकernal_memमुक्त  = hptiop_पूर्णांकernal_memमुक्त_itl,
	.map_pci_bar       = hptiop_map_pci_bar_itl,
	.unmap_pci_bar     = hptiop_unmap_pci_bar_itl,
	.enable_पूर्णांकr       = hptiop_enable_पूर्णांकr_itl,
	.disable_पूर्णांकr      = hptiop_disable_पूर्णांकr_itl,
	.get_config        = iop_get_config_itl,
	.set_config        = iop_set_config_itl,
	.iop_पूर्णांकr          = iop_पूर्णांकr_itl,
	.post_msg          = hptiop_post_msg_itl,
	.post_req          = hptiop_post_req_itl,
	.hw_dma_bit_mask   = 64,
	.reset_comm        = hptiop_reset_comm_itl,
	.host_phy_flag     = cpu_to_le64(0),
पूर्ण;

अटल काष्ठा hptiop_adapter_ops hptiop_mv_ops = अणु
	.family            = MV_BASED_IOP,
	.iop_रुको_पढ़ोy    = iop_रुको_पढ़ोy_mv,
	.पूर्णांकernal_meदो_स्मृति = hptiop_पूर्णांकernal_meदो_स्मृति_mv,
	.पूर्णांकernal_memमुक्त  = hptiop_पूर्णांकernal_memमुक्त_mv,
	.map_pci_bar       = hptiop_map_pci_bar_mv,
	.unmap_pci_bar     = hptiop_unmap_pci_bar_mv,
	.enable_पूर्णांकr       = hptiop_enable_पूर्णांकr_mv,
	.disable_पूर्णांकr      = hptiop_disable_पूर्णांकr_mv,
	.get_config        = iop_get_config_mv,
	.set_config        = iop_set_config_mv,
	.iop_पूर्णांकr          = iop_पूर्णांकr_mv,
	.post_msg          = hptiop_post_msg_mv,
	.post_req          = hptiop_post_req_mv,
	.hw_dma_bit_mask   = 33,
	.reset_comm        = hptiop_reset_comm_mv,
	.host_phy_flag     = cpu_to_le64(0),
पूर्ण;

अटल काष्ठा hptiop_adapter_ops hptiop_mvfrey_ops = अणु
	.family            = MVFREY_BASED_IOP,
	.iop_रुको_पढ़ोy    = iop_रुको_पढ़ोy_mvfrey,
	.पूर्णांकernal_meदो_स्मृति = hptiop_पूर्णांकernal_meदो_स्मृति_mvfrey,
	.पूर्णांकernal_memमुक्त  = hptiop_पूर्णांकernal_memमुक्त_mvfrey,
	.map_pci_bar       = hptiop_map_pci_bar_mvfrey,
	.unmap_pci_bar     = hptiop_unmap_pci_bar_mvfrey,
	.enable_पूर्णांकr       = hptiop_enable_पूर्णांकr_mvfrey,
	.disable_पूर्णांकr      = hptiop_disable_पूर्णांकr_mvfrey,
	.get_config        = iop_get_config_mvfrey,
	.set_config        = iop_set_config_mvfrey,
	.iop_पूर्णांकr          = iop_पूर्णांकr_mvfrey,
	.post_msg          = hptiop_post_msg_mvfrey,
	.post_req          = hptiop_post_req_mvfrey,
	.hw_dma_bit_mask   = 64,
	.reset_comm        = hptiop_reset_comm_mvfrey,
	.host_phy_flag     = cpu_to_le64(1),
पूर्ण;

अटल काष्ठा pci_device_id hptiop_id_table[] = अणु
	अणु PCI_VDEVICE(TTI, 0x3220), (kernel_uदीर्घ_t)&hptiop_itl_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x3320), (kernel_uदीर्घ_t)&hptiop_itl_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x3410), (kernel_uदीर्घ_t)&hptiop_itl_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x3510), (kernel_uदीर्घ_t)&hptiop_itl_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x3511), (kernel_uदीर्घ_t)&hptiop_itl_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x3520), (kernel_uदीर्घ_t)&hptiop_itl_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x3521), (kernel_uदीर्घ_t)&hptiop_itl_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x3522), (kernel_uदीर्घ_t)&hptiop_itl_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x3530), (kernel_uदीर्घ_t)&hptiop_itl_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x3540), (kernel_uदीर्घ_t)&hptiop_itl_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x3560), (kernel_uदीर्घ_t)&hptiop_itl_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x4210), (kernel_uदीर्घ_t)&hptiop_itl_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x4211), (kernel_uदीर्घ_t)&hptiop_itl_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x4310), (kernel_uदीर्घ_t)&hptiop_itl_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x4311), (kernel_uदीर्घ_t)&hptiop_itl_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x4320), (kernel_uदीर्घ_t)&hptiop_itl_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x4321), (kernel_uदीर्घ_t)&hptiop_itl_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x4322), (kernel_uदीर्घ_t)&hptiop_itl_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x4400), (kernel_uदीर्घ_t)&hptiop_itl_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x3120), (kernel_uदीर्घ_t)&hptiop_mv_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x3122), (kernel_uदीर्घ_t)&hptiop_mv_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x3020), (kernel_uदीर्घ_t)&hptiop_mv_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x4520), (kernel_uदीर्घ_t)&hptiop_mvfrey_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x4522), (kernel_uदीर्घ_t)&hptiop_mvfrey_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x3610), (kernel_uदीर्घ_t)&hptiop_mvfrey_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x3611), (kernel_uदीर्घ_t)&hptiop_mvfrey_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x3620), (kernel_uदीर्घ_t)&hptiop_mvfrey_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x3622), (kernel_uदीर्घ_t)&hptiop_mvfrey_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x3640), (kernel_uदीर्घ_t)&hptiop_mvfrey_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x3660), (kernel_uदीर्घ_t)&hptiop_mvfrey_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x3680), (kernel_uदीर्घ_t)&hptiop_mvfrey_ops पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x3690), (kernel_uदीर्घ_t)&hptiop_mvfrey_ops पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, hptiop_id_table);

अटल काष्ठा pci_driver hptiop_pci_driver = अणु
	.name       = driver_name,
	.id_table   = hptiop_id_table,
	.probe      = hptiop_probe,
	.हटाओ     = hptiop_हटाओ,
	.shutकरोwn   = hptiop_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init hptiop_module_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "%s %s\n", driver_name_दीर्घ, driver_ver);
	वापस pci_रेजिस्टर_driver(&hptiop_pci_driver);
पूर्ण

अटल व्योम __निकास hptiop_module_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&hptiop_pci_driver);
पूर्ण


module_init(hptiop_module_init);
module_निकास(hptiop_module_निकास);

MODULE_LICENSE("GPL");

