<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Discovery service क्रम the NVMe over Fabrics target.
 * Copyright (C) 2016 Intel Corporation. All rights reserved.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/slab.h>
#समावेश <generated/utsrelease.h>
#समावेश "nvmet.h"

काष्ठा nvmet_subsys *nvmet_disc_subsys;

अटल u64 nvmet_genctr;

अटल व्योम __nvmet_disc_changed(काष्ठा nvmet_port *port,
				 काष्ठा nvmet_ctrl *ctrl)
अणु
	अगर (ctrl->port != port)
		वापस;

	अगर (nvmet_aen_bit_disabled(ctrl, NVME_AEN_BIT_DISC_CHANGE))
		वापस;

	nvmet_add_async_event(ctrl, NVME_AER_TYPE_NOTICE,
			      NVME_AER_NOTICE_DISC_CHANGED, NVME_LOG_DISC);
पूर्ण

व्योम nvmet_port_disc_changed(काष्ठा nvmet_port *port,
			     काष्ठा nvmet_subsys *subsys)
अणु
	काष्ठा nvmet_ctrl *ctrl;

	lockdep_निश्चित_held(&nvmet_config_sem);
	nvmet_genctr++;

	mutex_lock(&nvmet_disc_subsys->lock);
	list_क्रम_each_entry(ctrl, &nvmet_disc_subsys->ctrls, subsys_entry) अणु
		अगर (subsys && !nvmet_host_allowed(subsys, ctrl->hostnqn))
			जारी;

		__nvmet_disc_changed(port, ctrl);
	पूर्ण
	mutex_unlock(&nvmet_disc_subsys->lock);

	/* If transport can संकेत change, notअगरy transport */
	अगर (port->tr_ops && port->tr_ops->discovery_chg)
		port->tr_ops->discovery_chg(port);
पूर्ण

अटल व्योम __nvmet_subsys_disc_changed(काष्ठा nvmet_port *port,
					काष्ठा nvmet_subsys *subsys,
					काष्ठा nvmet_host *host)
अणु
	काष्ठा nvmet_ctrl *ctrl;

	mutex_lock(&nvmet_disc_subsys->lock);
	list_क्रम_each_entry(ctrl, &nvmet_disc_subsys->ctrls, subsys_entry) अणु
		अगर (host && म_भेद(nvmet_host_name(host), ctrl->hostnqn))
			जारी;

		__nvmet_disc_changed(port, ctrl);
	पूर्ण
	mutex_unlock(&nvmet_disc_subsys->lock);
पूर्ण

व्योम nvmet_subsys_disc_changed(काष्ठा nvmet_subsys *subsys,
			       काष्ठा nvmet_host *host)
अणु
	काष्ठा nvmet_port *port;
	काष्ठा nvmet_subsys_link *s;

	lockdep_निश्चित_held(&nvmet_config_sem);
	nvmet_genctr++;

	list_क्रम_each_entry(port, nvmet_ports, global_entry)
		list_क्रम_each_entry(s, &port->subप्रणालीs, entry) अणु
			अगर (s->subsys != subsys)
				जारी;
			__nvmet_subsys_disc_changed(port, subsys, host);
		पूर्ण
पूर्ण

व्योम nvmet_referral_enable(काष्ठा nvmet_port *parent, काष्ठा nvmet_port *port)
अणु
	करोwn_ग_लिखो(&nvmet_config_sem);
	अगर (list_empty(&port->entry)) अणु
		list_add_tail(&port->entry, &parent->referrals);
		port->enabled = true;
		nvmet_port_disc_changed(parent, शून्य);
	पूर्ण
	up_ग_लिखो(&nvmet_config_sem);
पूर्ण

व्योम nvmet_referral_disable(काष्ठा nvmet_port *parent, काष्ठा nvmet_port *port)
अणु
	करोwn_ग_लिखो(&nvmet_config_sem);
	अगर (!list_empty(&port->entry)) अणु
		port->enabled = false;
		list_del_init(&port->entry);
		nvmet_port_disc_changed(parent, शून्य);
	पूर्ण
	up_ग_लिखो(&nvmet_config_sem);
पूर्ण

अटल व्योम nvmet_क्रमmat_discovery_entry(काष्ठा nvmf_disc_rsp_page_hdr *hdr,
		काष्ठा nvmet_port *port, अक्षर *subsys_nqn, अक्षर *traddr,
		u8 type, u32 numrec)
अणु
	काष्ठा nvmf_disc_rsp_page_entry *e = &hdr->entries[numrec];

	e->trtype = port->disc_addr.trtype;
	e->adrfam = port->disc_addr.adrfam;
	e->treq = port->disc_addr.treq;
	e->portid = port->disc_addr.portid;
	/* we support only dynamic controllers */
	e->cntlid = cpu_to_le16(NVME_CNTLID_DYNAMIC);
	e->asqsz = cpu_to_le16(NVME_AQ_DEPTH);
	e->subtype = type;
	स_नकल(e->trsvcid, port->disc_addr.trsvcid, NVMF_TRSVCID_SIZE);
	स_नकल(e->traddr, traddr, NVMF_TRADDR_SIZE);
	स_नकल(e->tsas.common, port->disc_addr.tsas.common, NVMF_TSAS_SIZE);
	म_नकलन(e->subnqn, subsys_nqn, NVMF_NQN_SIZE);
पूर्ण

/*
 * nvmet_set_disc_traddr - set a correct discovery log entry traddr
 *
 * IP based transports (e.g RDMA) can listen on "any" ipv4/ipv6 addresses
 * (INADDR_ANY or IN6ADDR_ANY_INIT). The discovery log page traddr reply
 * must not contain that "any" IP address. If the transport implements
 * .disc_traddr, use it. this callback will set the discovery traddr
 * from the req->port address in हाल the port in question listens
 * "any" IP address.
 */
अटल व्योम nvmet_set_disc_traddr(काष्ठा nvmet_req *req, काष्ठा nvmet_port *port,
		अक्षर *traddr)
अणु
	अगर (req->ops->disc_traddr)
		req->ops->disc_traddr(req, port, traddr);
	अन्यथा
		स_नकल(traddr, port->disc_addr.traddr, NVMF_TRADDR_SIZE);
पूर्ण

अटल माप_प्रकार discovery_log_entries(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvmet_ctrl *ctrl = req->sq->ctrl;
	काष्ठा nvmet_subsys_link *p;
	काष्ठा nvmet_port *r;
	माप_प्रकार entries = 0;

	list_क्रम_each_entry(p, &req->port->subप्रणालीs, entry) अणु
		अगर (!nvmet_host_allowed(p->subsys, ctrl->hostnqn))
			जारी;
		entries++;
	पूर्ण
	list_क्रम_each_entry(r, &req->port->referrals, entry)
		entries++;
	वापस entries;
पूर्ण

अटल व्योम nvmet_execute_disc_get_log_page(काष्ठा nvmet_req *req)
अणु
	स्थिर पूर्णांक entry_size = माप(काष्ठा nvmf_disc_rsp_page_entry);
	काष्ठा nvmet_ctrl *ctrl = req->sq->ctrl;
	काष्ठा nvmf_disc_rsp_page_hdr *hdr;
	u64 offset = nvmet_get_log_page_offset(req->cmd);
	माप_प्रकार data_len = nvmet_get_log_page_len(req->cmd);
	माप_प्रकार alloc_len;
	काष्ठा nvmet_subsys_link *p;
	काष्ठा nvmet_port *r;
	u32 numrec = 0;
	u16 status = 0;
	व्योम *buffer;

	अगर (!nvmet_check_transfer_len(req, data_len))
		वापस;

	अगर (req->cmd->get_log_page.lid != NVME_LOG_DISC) अणु
		req->error_loc =
			दुरत्व(काष्ठा nvme_get_log_page_command, lid);
		status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
		जाओ out;
	पूर्ण

	/* Spec requires dword aligned offsets */
	अगर (offset & 0x3) अणु
		req->error_loc =
			दुरत्व(काष्ठा nvme_get_log_page_command, lpo);
		status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
		जाओ out;
	पूर्ण

	/*
	 * Make sure we're passing at least a buffer of response header size.
	 * If host provided data len is less than the header size, only the
	 * number of bytes requested by host will be sent to host.
	 */
	करोwn_पढ़ो(&nvmet_config_sem);
	alloc_len = माप(*hdr) + entry_size * discovery_log_entries(req);
	buffer = kzalloc(alloc_len, GFP_KERNEL);
	अगर (!buffer) अणु
		up_पढ़ो(&nvmet_config_sem);
		status = NVME_SC_INTERNAL;
		जाओ out;
	पूर्ण

	hdr = buffer;
	list_क्रम_each_entry(p, &req->port->subप्रणालीs, entry) अणु
		अक्षर traddr[NVMF_TRADDR_SIZE];

		अगर (!nvmet_host_allowed(p->subsys, ctrl->hostnqn))
			जारी;

		nvmet_set_disc_traddr(req, req->port, traddr);
		nvmet_क्रमmat_discovery_entry(hdr, req->port,
				p->subsys->subsysnqn, traddr,
				NVME_NQN_NVME, numrec);
		numrec++;
	पूर्ण

	list_क्रम_each_entry(r, &req->port->referrals, entry) अणु
		nvmet_क्रमmat_discovery_entry(hdr, r,
				NVME_DISC_SUBSYS_NAME,
				r->disc_addr.traddr,
				NVME_NQN_DISC, numrec);
		numrec++;
	पूर्ण

	hdr->genctr = cpu_to_le64(nvmet_genctr);
	hdr->numrec = cpu_to_le64(numrec);
	hdr->recfmt = cpu_to_le16(0);

	nvmet_clear_aen_bit(req, NVME_AEN_BIT_DISC_CHANGE);

	up_पढ़ो(&nvmet_config_sem);

	status = nvmet_copy_to_sgl(req, 0, buffer + offset, data_len);
	kमुक्त(buffer);
out:
	nvmet_req_complete(req, status);
पूर्ण

अटल व्योम nvmet_execute_disc_identअगरy(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvmet_ctrl *ctrl = req->sq->ctrl;
	काष्ठा nvme_id_ctrl *id;
	स्थिर अक्षर model[] = "Linux";
	u16 status = 0;

	अगर (!nvmet_check_transfer_len(req, NVME_IDENTIFY_DATA_SIZE))
		वापस;

	अगर (req->cmd->identअगरy.cns != NVME_ID_CNS_CTRL) अणु
		req->error_loc = दुरत्व(काष्ठा nvme_identअगरy, cns);
		status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
		जाओ out;
	पूर्ण

	id = kzalloc(माप(*id), GFP_KERNEL);
	अगर (!id) अणु
		status = NVME_SC_INTERNAL;
		जाओ out;
	पूर्ण

	स_रखो(id->sn, ' ', माप(id->sn));
	bin2hex(id->sn, &ctrl->subsys->serial,
		min(माप(ctrl->subsys->serial), माप(id->sn) / 2));
	स_रखो(id->fr, ' ', माप(id->fr));
	स_नकल_and_pad(id->mn, माप(id->mn), model, माप(model) - 1, ' ');
	स_नकल_and_pad(id->fr, माप(id->fr),
		       UTS_RELEASE, म_माप(UTS_RELEASE), ' ');

	/* no limit on data transfer sizes क्रम now */
	id->mdts = 0;
	id->cntlid = cpu_to_le16(ctrl->cntlid);
	id->ver = cpu_to_le32(ctrl->subsys->ver);
	id->lpa = (1 << 2);

	/* no enक्रमcement soft-limit क्रम maxcmd - pick arbitrary high value */
	id->maxcmd = cpu_to_le16(NVMET_MAX_CMD);

	id->sgls = cpu_to_le32(1 << 0);	/* we always support SGLs */
	अगर (ctrl->ops->flags & NVMF_KEYED_SGLS)
		id->sgls |= cpu_to_le32(1 << 2);
	अगर (req->port->अंतरभूत_data_size)
		id->sgls |= cpu_to_le32(1 << 20);

	id->oaes = cpu_to_le32(NVMET_DISC_AEN_CFG_OPTIONAL);

	strlcpy(id->subnqn, ctrl->subsys->subsysnqn, माप(id->subnqn));

	status = nvmet_copy_to_sgl(req, 0, id, माप(*id));

	kमुक्त(id);
out:
	nvmet_req_complete(req, status);
पूर्ण

अटल व्योम nvmet_execute_disc_set_features(काष्ठा nvmet_req *req)
अणु
	u32 cdw10 = le32_to_cpu(req->cmd->common.cdw10);
	u16 stat;

	अगर (!nvmet_check_transfer_len(req, 0))
		वापस;

	चयन (cdw10 & 0xff) अणु
	हाल NVME_FEAT_KATO:
		stat = nvmet_set_feat_kato(req);
		अवरोध;
	हाल NVME_FEAT_ASYNC_EVENT:
		stat = nvmet_set_feat_async_event(req,
						  NVMET_DISC_AEN_CFG_OPTIONAL);
		अवरोध;
	शेष:
		req->error_loc =
			दुरत्व(काष्ठा nvme_common_command, cdw10);
		stat = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
		अवरोध;
	पूर्ण

	nvmet_req_complete(req, stat);
पूर्ण

अटल व्योम nvmet_execute_disc_get_features(काष्ठा nvmet_req *req)
अणु
	u32 cdw10 = le32_to_cpu(req->cmd->common.cdw10);
	u16 stat = 0;

	अगर (!nvmet_check_transfer_len(req, 0))
		वापस;

	चयन (cdw10 & 0xff) अणु
	हाल NVME_FEAT_KATO:
		nvmet_get_feat_kato(req);
		अवरोध;
	हाल NVME_FEAT_ASYNC_EVENT:
		nvmet_get_feat_async_event(req);
		अवरोध;
	शेष:
		req->error_loc =
			दुरत्व(काष्ठा nvme_common_command, cdw10);
		stat = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
		अवरोध;
	पूर्ण

	nvmet_req_complete(req, stat);
पूर्ण

u16 nvmet_parse_discovery_cmd(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvme_command *cmd = req->cmd;

	अगर (unlikely(!(req->sq->ctrl->csts & NVME_CSTS_RDY))) अणु
		pr_err("got cmd %d while not ready\n",
		       cmd->common.opcode);
		req->error_loc =
			दुरत्व(काष्ठा nvme_common_command, opcode);
		वापस NVME_SC_INVALID_OPCODE | NVME_SC_DNR;
	पूर्ण

	चयन (cmd->common.opcode) अणु
	हाल nvme_admin_set_features:
		req->execute = nvmet_execute_disc_set_features;
		वापस 0;
	हाल nvme_admin_get_features:
		req->execute = nvmet_execute_disc_get_features;
		वापस 0;
	हाल nvme_admin_async_event:
		req->execute = nvmet_execute_async_event;
		वापस 0;
	हाल nvme_admin_keep_alive:
		req->execute = nvmet_execute_keep_alive;
		वापस 0;
	हाल nvme_admin_get_log_page:
		req->execute = nvmet_execute_disc_get_log_page;
		वापस 0;
	हाल nvme_admin_identअगरy:
		req->execute = nvmet_execute_disc_identअगरy;
		वापस 0;
	शेष:
		pr_debug("unhandled cmd %d\n", cmd->common.opcode);
		req->error_loc = दुरत्व(काष्ठा nvme_common_command, opcode);
		वापस NVME_SC_INVALID_OPCODE | NVME_SC_DNR;
	पूर्ण

पूर्ण

पूर्णांक __init nvmet_init_discovery(व्योम)
अणु
	nvmet_disc_subsys =
		nvmet_subsys_alloc(NVME_DISC_SUBSYS_NAME, NVME_NQN_DISC);
	वापस PTR_ERR_OR_ZERO(nvmet_disc_subsys);
पूर्ण

व्योम nvmet_निकास_discovery(व्योम)
अणु
	nvmet_subsys_put(nvmet_disc_subsys);
पूर्ण
