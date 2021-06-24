<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NVMe admin command implementation.
 * Copyright (c) 2015-2016 HGST, a Western Digital Company.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/rculist.h>
#समावेश <linux/part_स्थिति.स>

#समावेश <generated/utsrelease.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "nvmet.h"

u32 nvmet_get_log_page_len(काष्ठा nvme_command *cmd)
अणु
	u32 len = le16_to_cpu(cmd->get_log_page.numdu);

	len <<= 16;
	len += le16_to_cpu(cmd->get_log_page.numdl);
	/* NUMD is a 0's based value */
	len += 1;
	len *= माप(u32);

	वापस len;
पूर्ण

अटल u32 nvmet_feat_data_len(काष्ठा nvmet_req *req, u32 cdw10)
अणु
	चयन (cdw10 & 0xff) अणु
	हाल NVME_FEAT_HOST_ID:
		वापस माप(req->sq->ctrl->hostid);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

u64 nvmet_get_log_page_offset(काष्ठा nvme_command *cmd)
अणु
	वापस le64_to_cpu(cmd->get_log_page.lpo);
पूर्ण

अटल व्योम nvmet_execute_get_log_page_noop(काष्ठा nvmet_req *req)
अणु
	nvmet_req_complete(req, nvmet_zero_sgl(req, 0, req->transfer_len));
पूर्ण

अटल व्योम nvmet_execute_get_log_page_error(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvmet_ctrl *ctrl = req->sq->ctrl;
	अचिन्हित दीर्घ flags;
	off_t offset = 0;
	u64 slot;
	u64 i;

	spin_lock_irqsave(&ctrl->error_lock, flags);
	slot = ctrl->err_counter % NVMET_ERROR_LOG_SLOTS;

	क्रम (i = 0; i < NVMET_ERROR_LOG_SLOTS; i++) अणु
		अगर (nvmet_copy_to_sgl(req, offset, &ctrl->slots[slot],
				माप(काष्ठा nvme_error_slot)))
			अवरोध;

		अगर (slot == 0)
			slot = NVMET_ERROR_LOG_SLOTS - 1;
		अन्यथा
			slot--;
		offset += माप(काष्ठा nvme_error_slot);
	पूर्ण
	spin_unlock_irqrestore(&ctrl->error_lock, flags);
	nvmet_req_complete(req, 0);
पूर्ण

अटल u16 nvmet_get_smart_log_nsid(काष्ठा nvmet_req *req,
		काष्ठा nvme_smart_log *slog)
अणु
	u64 host_पढ़ोs, host_ग_लिखोs, data_units_पढ़ो, data_units_written;
	u16 status;

	status = nvmet_req_find_ns(req);
	अगर (status)
		वापस status;

	/* we करोn't have the right data क्रम file backed ns */
	अगर (!req->ns->bdev)
		वापस NVME_SC_SUCCESS;

	host_पढ़ोs = part_stat_पढ़ो(req->ns->bdev, ios[READ]);
	data_units_पढ़ो =
		DIV_ROUND_UP(part_stat_पढ़ो(req->ns->bdev, sectors[READ]), 1000);
	host_ग_लिखोs = part_stat_पढ़ो(req->ns->bdev, ios[WRITE]);
	data_units_written =
		DIV_ROUND_UP(part_stat_पढ़ो(req->ns->bdev, sectors[WRITE]), 1000);

	put_unaligned_le64(host_पढ़ोs, &slog->host_पढ़ोs[0]);
	put_unaligned_le64(data_units_पढ़ो, &slog->data_units_पढ़ो[0]);
	put_unaligned_le64(host_ग_लिखोs, &slog->host_ग_लिखोs[0]);
	put_unaligned_le64(data_units_written, &slog->data_units_written[0]);

	वापस NVME_SC_SUCCESS;
पूर्ण

अटल u16 nvmet_get_smart_log_all(काष्ठा nvmet_req *req,
		काष्ठा nvme_smart_log *slog)
अणु
	u64 host_पढ़ोs = 0, host_ग_लिखोs = 0;
	u64 data_units_पढ़ो = 0, data_units_written = 0;
	काष्ठा nvmet_ns *ns;
	काष्ठा nvmet_ctrl *ctrl;
	अचिन्हित दीर्घ idx;

	ctrl = req->sq->ctrl;
	xa_क्रम_each(&ctrl->subsys->namespaces, idx, ns) अणु
		/* we करोn't have the right data क्रम file backed ns */
		अगर (!ns->bdev)
			जारी;
		host_पढ़ोs += part_stat_पढ़ो(ns->bdev, ios[READ]);
		data_units_पढ़ो += DIV_ROUND_UP(
			part_stat_पढ़ो(ns->bdev, sectors[READ]), 1000);
		host_ग_लिखोs += part_stat_पढ़ो(ns->bdev, ios[WRITE]);
		data_units_written += DIV_ROUND_UP(
			part_stat_पढ़ो(ns->bdev, sectors[WRITE]), 1000);
	पूर्ण

	put_unaligned_le64(host_पढ़ोs, &slog->host_पढ़ोs[0]);
	put_unaligned_le64(data_units_पढ़ो, &slog->data_units_पढ़ो[0]);
	put_unaligned_le64(host_ग_लिखोs, &slog->host_ग_लिखोs[0]);
	put_unaligned_le64(data_units_written, &slog->data_units_written[0]);

	वापस NVME_SC_SUCCESS;
पूर्ण

अटल व्योम nvmet_execute_get_log_page_smart(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvme_smart_log *log;
	u16 status = NVME_SC_INTERNAL;
	अचिन्हित दीर्घ flags;

	अगर (req->transfer_len != माप(*log))
		जाओ out;

	log = kzalloc(माप(*log), GFP_KERNEL);
	अगर (!log)
		जाओ out;

	अगर (req->cmd->get_log_page.nsid == cpu_to_le32(NVME_NSID_ALL))
		status = nvmet_get_smart_log_all(req, log);
	अन्यथा
		status = nvmet_get_smart_log_nsid(req, log);
	अगर (status)
		जाओ out_मुक्त_log;

	spin_lock_irqsave(&req->sq->ctrl->error_lock, flags);
	put_unaligned_le64(req->sq->ctrl->err_counter,
			&log->num_err_log_entries);
	spin_unlock_irqrestore(&req->sq->ctrl->error_lock, flags);

	status = nvmet_copy_to_sgl(req, 0, log, माप(*log));
out_मुक्त_log:
	kमुक्त(log);
out:
	nvmet_req_complete(req, status);
पूर्ण

अटल व्योम nvmet_execute_get_log_cmd_effects_ns(काष्ठा nvmet_req *req)
अणु
	u16 status = NVME_SC_INTERNAL;
	काष्ठा nvme_effects_log *log;

	log = kzalloc(माप(*log), GFP_KERNEL);
	अगर (!log)
		जाओ out;

	log->acs[nvme_admin_get_log_page]	= cpu_to_le32(1 << 0);
	log->acs[nvme_admin_identअगरy]		= cpu_to_le32(1 << 0);
	log->acs[nvme_admin_पात_cmd]		= cpu_to_le32(1 << 0);
	log->acs[nvme_admin_set_features]	= cpu_to_le32(1 << 0);
	log->acs[nvme_admin_get_features]	= cpu_to_le32(1 << 0);
	log->acs[nvme_admin_async_event]	= cpu_to_le32(1 << 0);
	log->acs[nvme_admin_keep_alive]		= cpu_to_le32(1 << 0);

	log->iocs[nvme_cmd_पढ़ो]		= cpu_to_le32(1 << 0);
	log->iocs[nvme_cmd_ग_लिखो]		= cpu_to_le32(1 << 0);
	log->iocs[nvme_cmd_flush]		= cpu_to_le32(1 << 0);
	log->iocs[nvme_cmd_dsm]			= cpu_to_le32(1 << 0);
	log->iocs[nvme_cmd_ग_लिखो_zeroes]	= cpu_to_le32(1 << 0);

	status = nvmet_copy_to_sgl(req, 0, log, माप(*log));

	kमुक्त(log);
out:
	nvmet_req_complete(req, status);
पूर्ण

अटल व्योम nvmet_execute_get_log_changed_ns(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvmet_ctrl *ctrl = req->sq->ctrl;
	u16 status = NVME_SC_INTERNAL;
	माप_प्रकार len;

	अगर (req->transfer_len != NVME_MAX_CHANGED_NAMESPACES * माप(__le32))
		जाओ out;

	mutex_lock(&ctrl->lock);
	अगर (ctrl->nr_changed_ns == U32_MAX)
		len = माप(__le32);
	अन्यथा
		len = ctrl->nr_changed_ns * माप(__le32);
	status = nvmet_copy_to_sgl(req, 0, ctrl->changed_ns_list, len);
	अगर (!status)
		status = nvmet_zero_sgl(req, len, req->transfer_len - len);
	ctrl->nr_changed_ns = 0;
	nvmet_clear_aen_bit(req, NVME_AEN_BIT_NS_ATTR);
	mutex_unlock(&ctrl->lock);
out:
	nvmet_req_complete(req, status);
पूर्ण

अटल u32 nvmet_क्रमmat_ana_group(काष्ठा nvmet_req *req, u32 grpid,
		काष्ठा nvme_ana_group_desc *desc)
अणु
	काष्ठा nvmet_ctrl *ctrl = req->sq->ctrl;
	काष्ठा nvmet_ns *ns;
	अचिन्हित दीर्घ idx;
	u32 count = 0;

	अगर (!(req->cmd->get_log_page.lsp & NVME_ANA_LOG_RGO)) अणु
		xa_क्रम_each(&ctrl->subsys->namespaces, idx, ns)
			अगर (ns->anagrpid == grpid)
				desc->nsids[count++] = cpu_to_le32(ns->nsid);
	पूर्ण

	desc->grpid = cpu_to_le32(grpid);
	desc->nnsids = cpu_to_le32(count);
	desc->chgcnt = cpu_to_le64(nvmet_ana_chgcnt);
	desc->state = req->port->ana_state[grpid];
	स_रखो(desc->rsvd17, 0, माप(desc->rsvd17));
	वापस माप(काष्ठा nvme_ana_group_desc) + count * माप(__le32);
पूर्ण

अटल व्योम nvmet_execute_get_log_page_ana(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvme_ana_rsp_hdr hdr = अणु 0, पूर्ण;
	काष्ठा nvme_ana_group_desc *desc;
	माप_प्रकार offset = माप(काष्ठा nvme_ana_rsp_hdr); /* start beyond hdr */
	माप_प्रकार len;
	u32 grpid;
	u16 ngrps = 0;
	u16 status;

	status = NVME_SC_INTERNAL;
	desc = kदो_स्मृति(माप(काष्ठा nvme_ana_group_desc) +
			NVMET_MAX_NAMESPACES * माप(__le32), GFP_KERNEL);
	अगर (!desc)
		जाओ out;

	करोwn_पढ़ो(&nvmet_ana_sem);
	क्रम (grpid = 1; grpid <= NVMET_MAX_ANAGRPS; grpid++) अणु
		अगर (!nvmet_ana_group_enabled[grpid])
			जारी;
		len = nvmet_क्रमmat_ana_group(req, grpid, desc);
		status = nvmet_copy_to_sgl(req, offset, desc, len);
		अगर (status)
			अवरोध;
		offset += len;
		ngrps++;
	पूर्ण
	क्रम ( ; grpid <= NVMET_MAX_ANAGRPS; grpid++) अणु
		अगर (nvmet_ana_group_enabled[grpid])
			ngrps++;
	पूर्ण

	hdr.chgcnt = cpu_to_le64(nvmet_ana_chgcnt);
	hdr.ngrps = cpu_to_le16(ngrps);
	nvmet_clear_aen_bit(req, NVME_AEN_BIT_ANA_CHANGE);
	up_पढ़ो(&nvmet_ana_sem);

	kमुक्त(desc);

	/* copy the header last once we know the number of groups */
	status = nvmet_copy_to_sgl(req, 0, &hdr, माप(hdr));
out:
	nvmet_req_complete(req, status);
पूर्ण

अटल व्योम nvmet_execute_get_log_page(काष्ठा nvmet_req *req)
अणु
	अगर (!nvmet_check_transfer_len(req, nvmet_get_log_page_len(req->cmd)))
		वापस;

	चयन (req->cmd->get_log_page.lid) अणु
	हाल NVME_LOG_ERROR:
		वापस nvmet_execute_get_log_page_error(req);
	हाल NVME_LOG_SMART:
		वापस nvmet_execute_get_log_page_smart(req);
	हाल NVME_LOG_FW_SLOT:
		/*
		 * We only support a single firmware slot which always is
		 * active, so we can zero out the whole firmware slot log and
		 * still claim to fully implement this mandatory log page.
		 */
		वापस nvmet_execute_get_log_page_noop(req);
	हाल NVME_LOG_CHANGED_NS:
		वापस nvmet_execute_get_log_changed_ns(req);
	हाल NVME_LOG_CMD_EFFECTS:
		वापस nvmet_execute_get_log_cmd_effects_ns(req);
	हाल NVME_LOG_ANA:
		वापस nvmet_execute_get_log_page_ana(req);
	पूर्ण
	pr_debug("unhandled lid %d on qid %d\n",
	       req->cmd->get_log_page.lid, req->sq->qid);
	req->error_loc = दुरत्व(काष्ठा nvme_get_log_page_command, lid);
	nvmet_req_complete(req, NVME_SC_INVALID_FIELD | NVME_SC_DNR);
पूर्ण

अटल u16 nvmet_set_model_number(काष्ठा nvmet_subsys *subsys)
अणु
	u16 status = 0;

	mutex_lock(&subsys->lock);
	अगर (!subsys->model_number) अणु
		subsys->model_number =
			kstrdup(NVMET_DEFAULT_CTRL_MODEL, GFP_KERNEL);
		अगर (!subsys->model_number)
			status = NVME_SC_INTERNAL;
	पूर्ण
	mutex_unlock(&subsys->lock);

	वापस status;
पूर्ण

अटल व्योम nvmet_execute_identअगरy_ctrl(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvmet_ctrl *ctrl = req->sq->ctrl;
	काष्ठा nvmet_subsys *subsys = ctrl->subsys;
	काष्ठा nvme_id_ctrl *id;
	u32 cmd_capsule_size;
	u16 status = 0;

	/*
	 * If there is no model number yet, set it now.  It will then reमुख्य
	 * stable क्रम the lअगरe समय of the subप्रणाली.
	 */
	अगर (!subsys->model_number) अणु
		status = nvmet_set_model_number(subsys);
		अगर (status)
			जाओ out;
	पूर्ण

	id = kzalloc(माप(*id), GFP_KERNEL);
	अगर (!id) अणु
		status = NVME_SC_INTERNAL;
		जाओ out;
	पूर्ण

	/* XXX: figure out how to assign real venकरोrs IDs. */
	id->vid = 0;
	id->ssvid = 0;

	स_रखो(id->sn, ' ', माप(id->sn));
	bin2hex(id->sn, &ctrl->subsys->serial,
		min(माप(ctrl->subsys->serial), माप(id->sn) / 2));
	स_नकल_and_pad(id->mn, माप(id->mn), subsys->model_number,
		       म_माप(subsys->model_number), ' ');
	स_नकल_and_pad(id->fr, माप(id->fr),
		       UTS_RELEASE, म_माप(UTS_RELEASE), ' ');

	id->rab = 6;

	/*
	 * XXX: figure out how we can assign a IEEE OUI, but until then
	 * the safest is to leave it as zeroes.
	 */

	/* we support multiple ports, multiples hosts and ANA: */
	id->cmic = (1 << 0) | (1 << 1) | (1 << 3);

	/* Limit MDTS according to transport capability */
	अगर (ctrl->ops->get_mdts)
		id->mdts = ctrl->ops->get_mdts(ctrl);
	अन्यथा
		id->mdts = 0;

	id->cntlid = cpu_to_le16(ctrl->cntlid);
	id->ver = cpu_to_le32(ctrl->subsys->ver);

	/* XXX: figure out what to करो about RTD3R/RTD3 */
	id->oaes = cpu_to_le32(NVMET_AEN_CFG_OPTIONAL);
	id->ctratt = cpu_to_le32(NVME_CTRL_ATTR_HID_128_BIT |
		NVME_CTRL_ATTR_TBKAS);

	id->oacs = 0;

	/*
	 * We करोn't really have a practical limit on the number of पात
	 * comands.  But we करोn't करो anything useful क्रम पात either, so
	 * no poपूर्णांक in allowing more पात commands than the spec requires.
	 */
	id->acl = 3;

	id->aerl = NVMET_ASYNC_EVENTS - 1;

	/* first slot is पढ़ो-only, only one slot supported */
	id->frmw = (1 << 0) | (1 << 1);
	id->lpa = (1 << 0) | (1 << 1) | (1 << 2);
	id->elpe = NVMET_ERROR_LOG_SLOTS - 1;
	id->npss = 0;

	/* We support keep-alive समयout in granularity of seconds */
	id->kas = cpu_to_le16(NVMET_KAS);

	id->sqes = (0x6 << 4) | 0x6;
	id->cqes = (0x4 << 4) | 0x4;

	/* no enक्रमcement soft-limit क्रम maxcmd - pick arbitrary high value */
	id->maxcmd = cpu_to_le16(NVMET_MAX_CMD);

	id->nn = cpu_to_le32(ctrl->subsys->max_nsid);
	id->mnan = cpu_to_le32(NVMET_MAX_NAMESPACES);
	id->oncs = cpu_to_le16(NVME_CTRL_ONCS_DSM |
			NVME_CTRL_ONCS_WRITE_ZEROES);

	/* XXX: करोn't report vwc अगर the underlying device is ग_लिखो through */
	id->vwc = NVME_CTRL_VWC_PRESENT;

	/*
	 * We can't support atomic ग_लिखोs bigger than a LBA without support
	 * from the backend device.
	 */
	id->awun = 0;
	id->awupf = 0;

	id->sgls = cpu_to_le32(1 << 0);	/* we always support SGLs */
	अगर (ctrl->ops->flags & NVMF_KEYED_SGLS)
		id->sgls |= cpu_to_le32(1 << 2);
	अगर (req->port->अंतरभूत_data_size)
		id->sgls |= cpu_to_le32(1 << 20);

	strlcpy(id->subnqn, ctrl->subsys->subsysnqn, माप(id->subnqn));

	/*
	 * Max command capsule size is sqe + in-capsule data size.
	 * Disable in-capsule data क्रम Metadata capable controllers.
	 */
	cmd_capsule_size = माप(काष्ठा nvme_command);
	अगर (!ctrl->pi_support)
		cmd_capsule_size += req->port->अंतरभूत_data_size;
	id->ioccsz = cpu_to_le32(cmd_capsule_size / 16);

	/* Max response capsule size is cqe */
	id->iorcsz = cpu_to_le32(माप(काष्ठा nvme_completion) / 16);

	id->msdbd = ctrl->ops->msdbd;

	id->anacap = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4);
	id->anatt = 10; /* अक्रमom value */
	id->anagrpmax = cpu_to_le32(NVMET_MAX_ANAGRPS);
	id->nanagrpid = cpu_to_le32(NVMET_MAX_ANAGRPS);

	/*
	 * Meh, we करोn't really support any घातer state.  Fake up the same
	 * values that qemu करोes.
	 */
	id->psd[0].max_घातer = cpu_to_le16(0x9c4);
	id->psd[0].entry_lat = cpu_to_le32(0x10);
	id->psd[0].निकास_lat = cpu_to_le32(0x4);

	id->nwpc = 1 << 0; /* ग_लिखो protect and no ग_लिखो protect */

	status = nvmet_copy_to_sgl(req, 0, id, माप(*id));

	kमुक्त(id);
out:
	nvmet_req_complete(req, status);
पूर्ण

अटल व्योम nvmet_execute_identअगरy_ns(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvme_id_ns *id;
	u16 status;

	अगर (le32_to_cpu(req->cmd->identअगरy.nsid) == NVME_NSID_ALL) अणु
		req->error_loc = दुरत्व(काष्ठा nvme_identअगरy, nsid);
		status = NVME_SC_INVALID_NS | NVME_SC_DNR;
		जाओ out;
	पूर्ण

	id = kzalloc(माप(*id), GFP_KERNEL);
	अगर (!id) अणु
		status = NVME_SC_INTERNAL;
		जाओ out;
	पूर्ण

	/* वापस an all zeroed buffer अगर we can't find an active namespace */
	status = nvmet_req_find_ns(req);
	अगर (status) अणु
		status = 0;
		जाओ करोne;
	पूर्ण

	nvmet_ns_revalidate(req->ns);

	/*
	 * nuse = ncap = nsze isn't always true, but we have no way to find
	 * that out from the underlying device.
	 */
	id->ncap = id->nsze =
		cpu_to_le64(req->ns->size >> req->ns->blksize_shअगरt);
	चयन (req->port->ana_state[req->ns->anagrpid]) अणु
	हाल NVME_ANA_INACCESSIBLE:
	हाल NVME_ANA_PERSISTENT_LOSS:
		अवरोध;
	शेष:
		id->nuse = id->nsze;
		अवरोध;
	पूर्ण

	अगर (req->ns->bdev)
		nvmet_bdev_set_limits(req->ns->bdev, id);

	/*
	 * We just provide a single LBA क्रमmat that matches what the
	 * underlying device reports.
	 */
	id->nlbaf = 0;
	id->flbas = 0;

	/*
	 * Our namespace might always be shared.  Not just with other
	 * controllers, but also with any other user of the block device.
	 */
	id->nmic = (1 << 0);
	id->anagrpid = cpu_to_le32(req->ns->anagrpid);

	स_नकल(&id->nguid, &req->ns->nguid, माप(id->nguid));

	id->lbaf[0].ds = req->ns->blksize_shअगरt;

	अगर (req->sq->ctrl->pi_support && nvmet_ns_has_pi(req->ns)) अणु
		id->dpc = NVME_NS_DPC_PI_FIRST | NVME_NS_DPC_PI_LAST |
			  NVME_NS_DPC_PI_TYPE1 | NVME_NS_DPC_PI_TYPE2 |
			  NVME_NS_DPC_PI_TYPE3;
		id->mc = NVME_MC_EXTENDED_LBA;
		id->dps = req->ns->pi_type;
		id->flbas = NVME_NS_FLBAS_META_EXT;
		id->lbaf[0].ms = cpu_to_le16(req->ns->metadata_size);
	पूर्ण

	अगर (req->ns->पढ़ोonly)
		id->nsattr |= (1 << 0);
करोne:
	अगर (!status)
		status = nvmet_copy_to_sgl(req, 0, id, माप(*id));

	kमुक्त(id);
out:
	nvmet_req_complete(req, status);
पूर्ण

अटल व्योम nvmet_execute_identअगरy_nslist(काष्ठा nvmet_req *req)
अणु
	अटल स्थिर पूर्णांक buf_size = NVME_IDENTIFY_DATA_SIZE;
	काष्ठा nvmet_ctrl *ctrl = req->sq->ctrl;
	काष्ठा nvmet_ns *ns;
	अचिन्हित दीर्घ idx;
	u32 min_nsid = le32_to_cpu(req->cmd->identअगरy.nsid);
	__le32 *list;
	u16 status = 0;
	पूर्णांक i = 0;

	list = kzalloc(buf_size, GFP_KERNEL);
	अगर (!list) अणु
		status = NVME_SC_INTERNAL;
		जाओ out;
	पूर्ण

	xa_क्रम_each(&ctrl->subsys->namespaces, idx, ns) अणु
		अगर (ns->nsid <= min_nsid)
			जारी;
		list[i++] = cpu_to_le32(ns->nsid);
		अगर (i == buf_size / माप(__le32))
			अवरोध;
	पूर्ण

	status = nvmet_copy_to_sgl(req, 0, list, buf_size);

	kमुक्त(list);
out:
	nvmet_req_complete(req, status);
पूर्ण

अटल u16 nvmet_copy_ns_identअगरier(काष्ठा nvmet_req *req, u8 type, u8 len,
				    व्योम *id, off_t *off)
अणु
	काष्ठा nvme_ns_id_desc desc = अणु
		.nidt = type,
		.nidl = len,
	पूर्ण;
	u16 status;

	status = nvmet_copy_to_sgl(req, *off, &desc, माप(desc));
	अगर (status)
		वापस status;
	*off += माप(desc);

	status = nvmet_copy_to_sgl(req, *off, id, len);
	अगर (status)
		वापस status;
	*off += len;

	वापस 0;
पूर्ण

अटल व्योम nvmet_execute_identअगरy_desclist(काष्ठा nvmet_req *req)
अणु
	off_t off = 0;
	u16 status;

	status = nvmet_req_find_ns(req);
	अगर (status)
		जाओ out;

	अगर (स_प्रथम_inv(&req->ns->uuid, 0, माप(req->ns->uuid))) अणु
		status = nvmet_copy_ns_identअगरier(req, NVME_NIDT_UUID,
						  NVME_NIDT_UUID_LEN,
						  &req->ns->uuid, &off);
		अगर (status)
			जाओ out;
	पूर्ण
	अगर (स_प्रथम_inv(req->ns->nguid, 0, माप(req->ns->nguid))) अणु
		status = nvmet_copy_ns_identअगरier(req, NVME_NIDT_NGUID,
						  NVME_NIDT_NGUID_LEN,
						  &req->ns->nguid, &off);
		अगर (status)
			जाओ out;
	पूर्ण

	अगर (sg_zero_buffer(req->sg, req->sg_cnt, NVME_IDENTIFY_DATA_SIZE - off,
			off) != NVME_IDENTIFY_DATA_SIZE - off)
		status = NVME_SC_INTERNAL | NVME_SC_DNR;

out:
	nvmet_req_complete(req, status);
पूर्ण

अटल व्योम nvmet_execute_identअगरy(काष्ठा nvmet_req *req)
अणु
	अगर (!nvmet_check_transfer_len(req, NVME_IDENTIFY_DATA_SIZE))
		वापस;

	चयन (req->cmd->identअगरy.cns) अणु
	हाल NVME_ID_CNS_NS:
		वापस nvmet_execute_identअगरy_ns(req);
	हाल NVME_ID_CNS_CTRL:
		वापस nvmet_execute_identअगरy_ctrl(req);
	हाल NVME_ID_CNS_NS_ACTIVE_LIST:
		वापस nvmet_execute_identअगरy_nslist(req);
	हाल NVME_ID_CNS_NS_DESC_LIST:
		वापस nvmet_execute_identअगरy_desclist(req);
	पूर्ण

	pr_debug("unhandled identify cns %d on qid %d\n",
	       req->cmd->identअगरy.cns, req->sq->qid);
	req->error_loc = दुरत्व(काष्ठा nvme_identअगरy, cns);
	nvmet_req_complete(req, NVME_SC_INVALID_FIELD | NVME_SC_DNR);
पूर्ण

/*
 * A "minimum viable" पात implementation: the command is mandatory in the
 * spec, but we are not required to करो any useful work.  We couldn't really
 * करो a useful पात, so करोn't bother even with रुकोing क्रम the command
 * to be exectuted and वापस immediately telling the command to पात
 * wasn't found.
 */
अटल व्योम nvmet_execute_पात(काष्ठा nvmet_req *req)
अणु
	अगर (!nvmet_check_transfer_len(req, 0))
		वापस;
	nvmet_set_result(req, 1);
	nvmet_req_complete(req, 0);
पूर्ण

अटल u16 nvmet_ग_लिखो_protect_flush_sync(काष्ठा nvmet_req *req)
अणु
	u16 status;

	अगर (req->ns->file)
		status = nvmet_file_flush(req);
	अन्यथा
		status = nvmet_bdev_flush(req);

	अगर (status)
		pr_err("write protect flush failed nsid: %u\n", req->ns->nsid);
	वापस status;
पूर्ण

अटल u16 nvmet_set_feat_ग_लिखो_protect(काष्ठा nvmet_req *req)
अणु
	u32 ग_लिखो_protect = le32_to_cpu(req->cmd->common.cdw11);
	काष्ठा nvmet_subsys *subsys = nvmet_req_subsys(req);
	u16 status;

	status = nvmet_req_find_ns(req);
	अगर (status)
		वापस status;

	mutex_lock(&subsys->lock);
	चयन (ग_लिखो_protect) अणु
	हाल NVME_NS_WRITE_PROTECT:
		req->ns->पढ़ोonly = true;
		status = nvmet_ग_लिखो_protect_flush_sync(req);
		अगर (status)
			req->ns->पढ़ोonly = false;
		अवरोध;
	हाल NVME_NS_NO_WRITE_PROTECT:
		req->ns->पढ़ोonly = false;
		status = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!status)
		nvmet_ns_changed(subsys, req->ns->nsid);
	mutex_unlock(&subsys->lock);
	वापस status;
पूर्ण

u16 nvmet_set_feat_kato(काष्ठा nvmet_req *req)
अणु
	u32 val32 = le32_to_cpu(req->cmd->common.cdw11);

	nvmet_stop_keep_alive_समयr(req->sq->ctrl);
	req->sq->ctrl->kato = DIV_ROUND_UP(val32, 1000);
	nvmet_start_keep_alive_समयr(req->sq->ctrl);

	nvmet_set_result(req, req->sq->ctrl->kato);

	वापस 0;
पूर्ण

u16 nvmet_set_feat_async_event(काष्ठा nvmet_req *req, u32 mask)
अणु
	u32 val32 = le32_to_cpu(req->cmd->common.cdw11);

	अगर (val32 & ~mask) अणु
		req->error_loc = दुरत्व(काष्ठा nvme_common_command, cdw11);
		वापस NVME_SC_INVALID_FIELD | NVME_SC_DNR;
	पूर्ण

	WRITE_ONCE(req->sq->ctrl->aen_enabled, val32);
	nvmet_set_result(req, val32);

	वापस 0;
पूर्ण

व्योम nvmet_execute_set_features(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvmet_subsys *subsys = nvmet_req_subsys(req);
	u32 cdw10 = le32_to_cpu(req->cmd->common.cdw10);
	u32 cdw11 = le32_to_cpu(req->cmd->common.cdw11);
	u16 status = 0;
	u16 nsqr;
	u16 ncqr;

	अगर (!nvmet_check_transfer_len(req, 0))
		वापस;

	चयन (cdw10 & 0xff) अणु
	हाल NVME_FEAT_NUM_QUEUES:
		ncqr = (cdw11 >> 16) & 0xffff;
		nsqr = cdw11 & 0xffff;
		अगर (ncqr == 0xffff || nsqr == 0xffff) अणु
			status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
			अवरोध;
		पूर्ण
		nvmet_set_result(req,
			(subsys->max_qid - 1) | ((subsys->max_qid - 1) << 16));
		अवरोध;
	हाल NVME_FEAT_KATO:
		status = nvmet_set_feat_kato(req);
		अवरोध;
	हाल NVME_FEAT_ASYNC_EVENT:
		status = nvmet_set_feat_async_event(req, NVMET_AEN_CFG_ALL);
		अवरोध;
	हाल NVME_FEAT_HOST_ID:
		status = NVME_SC_CMD_SEQ_ERROR | NVME_SC_DNR;
		अवरोध;
	हाल NVME_FEAT_WRITE_PROTECT:
		status = nvmet_set_feat_ग_लिखो_protect(req);
		अवरोध;
	शेष:
		req->error_loc = दुरत्व(काष्ठा nvme_common_command, cdw10);
		status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
		अवरोध;
	पूर्ण

	nvmet_req_complete(req, status);
पूर्ण

अटल u16 nvmet_get_feat_ग_लिखो_protect(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvmet_subsys *subsys = nvmet_req_subsys(req);
	u32 result;

	result = nvmet_req_find_ns(req);
	अगर (result)
		वापस result;

	mutex_lock(&subsys->lock);
	अगर (req->ns->पढ़ोonly == true)
		result = NVME_NS_WRITE_PROTECT;
	अन्यथा
		result = NVME_NS_NO_WRITE_PROTECT;
	nvmet_set_result(req, result);
	mutex_unlock(&subsys->lock);

	वापस 0;
पूर्ण

व्योम nvmet_get_feat_kato(काष्ठा nvmet_req *req)
अणु
	nvmet_set_result(req, req->sq->ctrl->kato * 1000);
पूर्ण

व्योम nvmet_get_feat_async_event(काष्ठा nvmet_req *req)
अणु
	nvmet_set_result(req, READ_ONCE(req->sq->ctrl->aen_enabled));
पूर्ण

व्योम nvmet_execute_get_features(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvmet_subsys *subsys = nvmet_req_subsys(req);
	u32 cdw10 = le32_to_cpu(req->cmd->common.cdw10);
	u16 status = 0;

	अगर (!nvmet_check_transfer_len(req, nvmet_feat_data_len(req, cdw10)))
		वापस;

	चयन (cdw10 & 0xff) अणु
	/*
	 * These features are mandatory in the spec, but we करोn't
	 * have a useful way to implement them.  We'll eventually
	 * need to come up with some fake values क्रम these.
	 */
#अगर 0
	हाल NVME_FEAT_ARBITRATION:
		अवरोध;
	हाल NVME_FEAT_POWER_MGMT:
		अवरोध;
	हाल NVME_FEAT_TEMP_THRESH:
		अवरोध;
	हाल NVME_FEAT_ERR_RECOVERY:
		अवरोध;
	हाल NVME_FEAT_IRQ_COALESCE:
		अवरोध;
	हाल NVME_FEAT_IRQ_CONFIG:
		अवरोध;
	हाल NVME_FEAT_WRITE_ATOMIC:
		अवरोध;
#पूर्ण_अगर
	हाल NVME_FEAT_ASYNC_EVENT:
		nvmet_get_feat_async_event(req);
		अवरोध;
	हाल NVME_FEAT_VOLATILE_WC:
		nvmet_set_result(req, 1);
		अवरोध;
	हाल NVME_FEAT_NUM_QUEUES:
		nvmet_set_result(req,
			(subsys->max_qid-1) | ((subsys->max_qid-1) << 16));
		अवरोध;
	हाल NVME_FEAT_KATO:
		nvmet_get_feat_kato(req);
		अवरोध;
	हाल NVME_FEAT_HOST_ID:
		/* need 128-bit host identअगरier flag */
		अगर (!(req->cmd->common.cdw11 & cpu_to_le32(1 << 0))) अणु
			req->error_loc =
				दुरत्व(काष्ठा nvme_common_command, cdw11);
			status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
			अवरोध;
		पूर्ण

		status = nvmet_copy_to_sgl(req, 0, &req->sq->ctrl->hostid,
				माप(req->sq->ctrl->hostid));
		अवरोध;
	हाल NVME_FEAT_WRITE_PROTECT:
		status = nvmet_get_feat_ग_लिखो_protect(req);
		अवरोध;
	शेष:
		req->error_loc =
			दुरत्व(काष्ठा nvme_common_command, cdw10);
		status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
		अवरोध;
	पूर्ण

	nvmet_req_complete(req, status);
पूर्ण

व्योम nvmet_execute_async_event(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvmet_ctrl *ctrl = req->sq->ctrl;

	अगर (!nvmet_check_transfer_len(req, 0))
		वापस;

	mutex_lock(&ctrl->lock);
	अगर (ctrl->nr_async_event_cmds >= NVMET_ASYNC_EVENTS) अणु
		mutex_unlock(&ctrl->lock);
		nvmet_req_complete(req, NVME_SC_ASYNC_LIMIT | NVME_SC_DNR);
		वापस;
	पूर्ण
	ctrl->async_event_cmds[ctrl->nr_async_event_cmds++] = req;
	mutex_unlock(&ctrl->lock);

	schedule_work(&ctrl->async_event_work);
पूर्ण

व्योम nvmet_execute_keep_alive(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvmet_ctrl *ctrl = req->sq->ctrl;
	u16 status = 0;

	अगर (!nvmet_check_transfer_len(req, 0))
		वापस;

	अगर (!ctrl->kato) अणु
		status = NVME_SC_KA_TIMEOUT_INVALID;
		जाओ out;
	पूर्ण

	pr_debug("ctrl %d update keep-alive timer for %d secs\n",
		ctrl->cntlid, ctrl->kato);
	mod_delayed_work(प्रणाली_wq, &ctrl->ka_work, ctrl->kato * HZ);
out:
	nvmet_req_complete(req, status);
पूर्ण

u16 nvmet_parse_admin_cmd(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvme_command *cmd = req->cmd;
	u16 ret;

	अगर (nvme_is_fabrics(cmd))
		वापस nvmet_parse_fabrics_cmd(req);
	अगर (nvmet_req_subsys(req)->type == NVME_NQN_DISC)
		वापस nvmet_parse_discovery_cmd(req);

	ret = nvmet_check_ctrl_status(req);
	अगर (unlikely(ret))
		वापस ret;

	अगर (nvmet_req_passthru_ctrl(req))
		वापस nvmet_parse_passthru_admin_cmd(req);

	चयन (cmd->common.opcode) अणु
	हाल nvme_admin_get_log_page:
		req->execute = nvmet_execute_get_log_page;
		वापस 0;
	हाल nvme_admin_identअगरy:
		req->execute = nvmet_execute_identअगरy;
		वापस 0;
	हाल nvme_admin_पात_cmd:
		req->execute = nvmet_execute_पात;
		वापस 0;
	हाल nvme_admin_set_features:
		req->execute = nvmet_execute_set_features;
		वापस 0;
	हाल nvme_admin_get_features:
		req->execute = nvmet_execute_get_features;
		वापस 0;
	हाल nvme_admin_async_event:
		req->execute = nvmet_execute_async_event;
		वापस 0;
	हाल nvme_admin_keep_alive:
		req->execute = nvmet_execute_keep_alive;
		वापस 0;
	शेष:
		वापस nvmet_report_invalid_opcode(req);
	पूर्ण
पूर्ण
