<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NVMe Fabrics command implementation.
 * Copyright (c) 2015-2016 HGST, a Western Digital Company.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/blkdev.h>
#समावेश "nvmet.h"

अटल व्योम nvmet_execute_prop_set(काष्ठा nvmet_req *req)
अणु
	u64 val = le64_to_cpu(req->cmd->prop_set.value);
	u16 status = 0;

	अगर (!nvmet_check_transfer_len(req, 0))
		वापस;

	अगर (req->cmd->prop_set.attrib & 1) अणु
		req->error_loc =
			दुरत्व(काष्ठा nvmf_property_set_command, attrib);
		status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
		जाओ out;
	पूर्ण

	चयन (le32_to_cpu(req->cmd->prop_set.offset)) अणु
	हाल NVME_REG_CC:
		nvmet_update_cc(req->sq->ctrl, val);
		अवरोध;
	शेष:
		req->error_loc =
			दुरत्व(काष्ठा nvmf_property_set_command, offset);
		status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
	पूर्ण
out:
	nvmet_req_complete(req, status);
पूर्ण

अटल व्योम nvmet_execute_prop_get(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvmet_ctrl *ctrl = req->sq->ctrl;
	u16 status = 0;
	u64 val = 0;

	अगर (!nvmet_check_transfer_len(req, 0))
		वापस;

	अगर (req->cmd->prop_get.attrib & 1) अणु
		चयन (le32_to_cpu(req->cmd->prop_get.offset)) अणु
		हाल NVME_REG_CAP:
			val = ctrl->cap;
			अवरोध;
		शेष:
			status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (le32_to_cpu(req->cmd->prop_get.offset)) अणु
		हाल NVME_REG_VS:
			val = ctrl->subsys->ver;
			अवरोध;
		हाल NVME_REG_CC:
			val = ctrl->cc;
			अवरोध;
		हाल NVME_REG_CSTS:
			val = ctrl->csts;
			अवरोध;
		शेष:
			status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (status && req->cmd->prop_get.attrib & 1) अणु
		req->error_loc =
			दुरत्व(काष्ठा nvmf_property_get_command, offset);
	पूर्ण अन्यथा अणु
		req->error_loc =
			दुरत्व(काष्ठा nvmf_property_get_command, attrib);
	पूर्ण

	req->cqe->result.u64 = cpu_to_le64(val);
	nvmet_req_complete(req, status);
पूर्ण

u16 nvmet_parse_fabrics_cmd(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvme_command *cmd = req->cmd;

	चयन (cmd->fabrics.fctype) अणु
	हाल nvme_fabrics_type_property_set:
		req->execute = nvmet_execute_prop_set;
		अवरोध;
	हाल nvme_fabrics_type_property_get:
		req->execute = nvmet_execute_prop_get;
		अवरोध;
	शेष:
		pr_debug("received unknown capsule type 0x%x\n",
			cmd->fabrics.fctype);
		req->error_loc = दुरत्व(काष्ठा nvmf_common_command, fctype);
		वापस NVME_SC_INVALID_OPCODE | NVME_SC_DNR;
	पूर्ण

	वापस 0;
पूर्ण

अटल u16 nvmet_install_queue(काष्ठा nvmet_ctrl *ctrl, काष्ठा nvmet_req *req)
अणु
	काष्ठा nvmf_connect_command *c = &req->cmd->connect;
	u16 qid = le16_to_cpu(c->qid);
	u16 sqsize = le16_to_cpu(c->sqsize);
	काष्ठा nvmet_ctrl *old;
	u16 ret;

	old = cmpxchg(&req->sq->ctrl, शून्य, ctrl);
	अगर (old) अणु
		pr_warn("queue already connected!\n");
		req->error_loc = दुरत्व(काष्ठा nvmf_connect_command, opcode);
		वापस NVME_SC_CONNECT_CTRL_BUSY | NVME_SC_DNR;
	पूर्ण
	अगर (!sqsize) अणु
		pr_warn("queue size zero!\n");
		req->error_loc = दुरत्व(काष्ठा nvmf_connect_command, sqsize);
		ret = NVME_SC_CONNECT_INVALID_PARAM | NVME_SC_DNR;
		जाओ err;
	पूर्ण

	/* note: convert queue size from 0's-based value to 1's-based value */
	nvmet_cq_setup(ctrl, req->cq, qid, sqsize + 1);
	nvmet_sq_setup(ctrl, req->sq, qid, sqsize + 1);

	अगर (c->cattr & NVME_CONNECT_DISABLE_SQFLOW) अणु
		req->sq->sqhd_disabled = true;
		req->cqe->sq_head = cpu_to_le16(0xffff);
	पूर्ण

	अगर (ctrl->ops->install_queue) अणु
		ret = ctrl->ops->install_queue(req->sq);
		अगर (ret) अणु
			pr_err("failed to install queue %d cntlid %d ret %x\n",
				qid, ctrl->cntlid, ret);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	req->sq->ctrl = शून्य;
	वापस ret;
पूर्ण

अटल व्योम nvmet_execute_admin_connect(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvmf_connect_command *c = &req->cmd->connect;
	काष्ठा nvmf_connect_data *d;
	काष्ठा nvmet_ctrl *ctrl = शून्य;
	u16 status = 0;

	अगर (!nvmet_check_transfer_len(req, माप(काष्ठा nvmf_connect_data)))
		वापस;

	d = kदो_स्मृति(माप(*d), GFP_KERNEL);
	अगर (!d) अणु
		status = NVME_SC_INTERNAL;
		जाओ complete;
	पूर्ण

	status = nvmet_copy_from_sgl(req, 0, d, माप(*d));
	अगर (status)
		जाओ out;

	/* zero out initial completion result, assign values as needed */
	req->cqe->result.u32 = 0;

	अगर (c->recfmt != 0) अणु
		pr_warn("invalid connect version (%d).\n",
			le16_to_cpu(c->recfmt));
		req->error_loc = दुरत्व(काष्ठा nvmf_connect_command, recfmt);
		status = NVME_SC_CONNECT_FORMAT | NVME_SC_DNR;
		जाओ out;
	पूर्ण

	अगर (unlikely(d->cntlid != cpu_to_le16(0xffff))) अणु
		pr_warn("connect attempt for invalid controller ID %#x\n",
			d->cntlid);
		status = NVME_SC_CONNECT_INVALID_PARAM | NVME_SC_DNR;
		req->cqe->result.u32 = IPO_IATTR_CONNECT_DATA(cntlid);
		जाओ out;
	पूर्ण

	status = nvmet_alloc_ctrl(d->subsysnqn, d->hostnqn, req,
				  le32_to_cpu(c->kato), &ctrl);
	अगर (status)
		जाओ out;

	ctrl->pi_support = ctrl->port->pi_enable && ctrl->subsys->pi_support;

	uuid_copy(&ctrl->hostid, &d->hostid);

	status = nvmet_install_queue(ctrl, req);
	अगर (status) अणु
		nvmet_ctrl_put(ctrl);
		जाओ out;
	पूर्ण

	pr_info("creating controller %d for subsystem %s for NQN %s%s.\n",
		ctrl->cntlid, ctrl->subsys->subsysnqn, ctrl->hostnqn,
		ctrl->pi_support ? " T10-PI is enabled" : "");
	req->cqe->result.u16 = cpu_to_le16(ctrl->cntlid);

out:
	kमुक्त(d);
complete:
	nvmet_req_complete(req, status);
पूर्ण

अटल व्योम nvmet_execute_io_connect(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvmf_connect_command *c = &req->cmd->connect;
	काष्ठा nvmf_connect_data *d;
	काष्ठा nvmet_ctrl *ctrl;
	u16 qid = le16_to_cpu(c->qid);
	u16 status = 0;

	अगर (!nvmet_check_transfer_len(req, माप(काष्ठा nvmf_connect_data)))
		वापस;

	d = kदो_स्मृति(माप(*d), GFP_KERNEL);
	अगर (!d) अणु
		status = NVME_SC_INTERNAL;
		जाओ complete;
	पूर्ण

	status = nvmet_copy_from_sgl(req, 0, d, माप(*d));
	अगर (status)
		जाओ out;

	/* zero out initial completion result, assign values as needed */
	req->cqe->result.u32 = 0;

	अगर (c->recfmt != 0) अणु
		pr_warn("invalid connect version (%d).\n",
			le16_to_cpu(c->recfmt));
		status = NVME_SC_CONNECT_FORMAT | NVME_SC_DNR;
		जाओ out;
	पूर्ण

	ctrl = nvmet_ctrl_find_get(d->subsysnqn, d->hostnqn,
				   le16_to_cpu(d->cntlid), req);
	अगर (!ctrl) अणु
		status = NVME_SC_CONNECT_INVALID_PARAM | NVME_SC_DNR;
		जाओ out;
	पूर्ण

	अगर (unlikely(qid > ctrl->subsys->max_qid)) अणु
		pr_warn("invalid queue id (%d)\n", qid);
		status = NVME_SC_CONNECT_INVALID_PARAM | NVME_SC_DNR;
		req->cqe->result.u32 = IPO_IATTR_CONNECT_SQE(qid);
		जाओ out_ctrl_put;
	पूर्ण

	status = nvmet_install_queue(ctrl, req);
	अगर (status) अणु
		/* pass back cntlid that had the issue of installing queue */
		req->cqe->result.u16 = cpu_to_le16(ctrl->cntlid);
		जाओ out_ctrl_put;
	पूर्ण

	pr_debug("adding queue %d to ctrl %d.\n", qid, ctrl->cntlid);

out:
	kमुक्त(d);
complete:
	nvmet_req_complete(req, status);
	वापस;

out_ctrl_put:
	nvmet_ctrl_put(ctrl);
	जाओ out;
पूर्ण

u16 nvmet_parse_connect_cmd(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvme_command *cmd = req->cmd;

	अगर (!nvme_is_fabrics(cmd)) अणु
		pr_debug("invalid command 0x%x on unconnected queue.\n",
			cmd->fabrics.opcode);
		req->error_loc = दुरत्व(काष्ठा nvme_common_command, opcode);
		वापस NVME_SC_INVALID_OPCODE | NVME_SC_DNR;
	पूर्ण
	अगर (cmd->fabrics.fctype != nvme_fabrics_type_connect) अणु
		pr_debug("invalid capsule type 0x%x on unconnected queue.\n",
			cmd->fabrics.fctype);
		req->error_loc = दुरत्व(काष्ठा nvmf_common_command, fctype);
		वापस NVME_SC_INVALID_OPCODE | NVME_SC_DNR;
	पूर्ण

	अगर (cmd->connect.qid == 0)
		req->execute = nvmet_execute_admin_connect;
	अन्यथा
		req->execute = nvmet_execute_io_connect;
	वापस 0;
पूर्ण
