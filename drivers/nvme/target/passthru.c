<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NVMe Over Fabrics Target Passthrough command implementation.
 *
 * Copyright (c) 2017-2018 Western Digital Corporation or its
 * affiliates.
 * Copyright (c) 2019-2020, Eideticom Inc.
 *
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>

#समावेश "../host/nvme.h"
#समावेश "nvmet.h"

MODULE_IMPORT_NS(NVME_TARGET_PASSTHRU);

/*
 * xarray to मुख्यtain one passthru subप्रणाली per nvme controller.
 */
अटल DEFINE_XARRAY(passthru_subप्रणालीs);

अटल u16 nvmet_passthru_override_id_ctrl(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvmet_ctrl *ctrl = req->sq->ctrl;
	काष्ठा nvme_ctrl *pctrl = ctrl->subsys->passthru_ctrl;
	u16 status = NVME_SC_SUCCESS;
	काष्ठा nvme_id_ctrl *id;
	अचिन्हित पूर्णांक max_hw_sectors;
	पूर्णांक page_shअगरt;

	id = kzalloc(माप(*id), GFP_KERNEL);
	अगर (!id)
		वापस NVME_SC_INTERNAL;

	status = nvmet_copy_from_sgl(req, 0, id, माप(*id));
	अगर (status)
		जाओ out_मुक्त;

	id->cntlid = cpu_to_le16(ctrl->cntlid);
	id->ver = cpu_to_le32(ctrl->subsys->ver);

	/*
	 * The passthru NVMe driver may have a limit on the number of segments
	 * which depends on the host's memory fragementation. To solve this,
	 * ensure mdts is limited to the pages equal to the number of segments.
	 */
	max_hw_sectors = min_not_zero(pctrl->max_segments << (PAGE_SHIFT - 9),
				      pctrl->max_hw_sectors);

	/*
	 * nvmet_passthru_map_sg is limitted to using a single bio so limit
	 * the mdts based on BIO_MAX_VECS as well
	 */
	max_hw_sectors = min_not_zero(BIO_MAX_VECS << (PAGE_SHIFT - 9),
				      max_hw_sectors);

	page_shअगरt = NVME_CAP_MPSMIN(ctrl->cap) + 12;

	id->mdts = ilog2(max_hw_sectors) + 9 - page_shअगरt;

	id->acl = 3;
	/*
	 * We export aerl limit क्रम the fabrics controller, update this when
	 * passthru based aerl support is added.
	 */
	id->aerl = NVMET_ASYNC_EVENTS - 1;

	/* emulate kas as most of the PCIe ctrl करोn't have a support क्रम kas */
	id->kas = cpu_to_le16(NVMET_KAS);

	/* करोn't support host memory buffer */
	id->hmpre = 0;
	id->hmmin = 0;

	id->sqes = min_t(__u8, ((0x6 << 4) | 0x6), id->sqes);
	id->cqes = min_t(__u8, ((0x4 << 4) | 0x4), id->cqes);
	id->maxcmd = cpu_to_le16(NVMET_MAX_CMD);

	/* करोn't support fuse commands */
	id->fuses = 0;

	id->sgls = cpu_to_le32(1 << 0); /* we always support SGLs */
	अगर (ctrl->ops->flags & NVMF_KEYED_SGLS)
		id->sgls |= cpu_to_le32(1 << 2);
	अगर (req->port->अंतरभूत_data_size)
		id->sgls |= cpu_to_le32(1 << 20);

	/*
	 * When passsthru controller is setup using nvme-loop transport it will
	 * export the passthru ctrl subsysnqn (PCIe NVMe ctrl) and will fail in
	 * the nvme/host/core.c in the nvme_init_subप्रणाली()->nvme_active_ctrl()
	 * code path with duplicate ctr subsynqn. In order to prevent that we
	 * mask the passthru-ctrl subsysnqn with the target ctrl subsysnqn.
	 */
	स_नकल(id->subnqn, ctrl->subsysnqn, माप(id->subnqn));

	/* use fabric id-ctrl values */
	id->ioccsz = cpu_to_le32((माप(काष्ठा nvme_command) +
				req->port->अंतरभूत_data_size) / 16);
	id->iorcsz = cpu_to_le32(माप(काष्ठा nvme_completion) / 16);

	id->msdbd = ctrl->ops->msdbd;

	/* Support multipath connections with fabrics */
	id->cmic |= 1 << 1;

	/* Disable reservations, see nvmet_parse_passthru_io_cmd() */
	id->oncs &= cpu_to_le16(~NVME_CTRL_ONCS_RESERVATIONS);

	status = nvmet_copy_to_sgl(req, 0, id, माप(काष्ठा nvme_id_ctrl));

out_मुक्त:
	kमुक्त(id);
	वापस status;
पूर्ण

अटल u16 nvmet_passthru_override_id_ns(काष्ठा nvmet_req *req)
अणु
	u16 status = NVME_SC_SUCCESS;
	काष्ठा nvme_id_ns *id;
	पूर्णांक i;

	id = kzalloc(माप(*id), GFP_KERNEL);
	अगर (!id)
		वापस NVME_SC_INTERNAL;

	status = nvmet_copy_from_sgl(req, 0, id, माप(काष्ठा nvme_id_ns));
	अगर (status)
		जाओ out_मुक्त;

	क्रम (i = 0; i < (id->nlbaf + 1); i++)
		अगर (id->lbaf[i].ms)
			स_रखो(&id->lbaf[i], 0, माप(id->lbaf[i]));

	id->flbas = id->flbas & ~(1 << 4);

	/*
	 * Presently the NVMEof target code करोes not support sending
	 * metadata, so we must disable it here. This should be updated
	 * once target starts supporting metadata.
	 */
	id->mc = 0;

	status = nvmet_copy_to_sgl(req, 0, id, माप(*id));

out_मुक्त:
	kमुक्त(id);
	वापस status;
पूर्ण

अटल व्योम nvmet_passthru_execute_cmd_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा nvmet_req *req = container_of(w, काष्ठा nvmet_req, p.work);
	काष्ठा request *rq = req->p.rq;
	u16 status;

	nvme_execute_passthru_rq(rq);

	status = nvme_req(rq)->status;
	अगर (status == NVME_SC_SUCCESS &&
	    req->cmd->common.opcode == nvme_admin_identअगरy) अणु
		चयन (req->cmd->identअगरy.cns) अणु
		हाल NVME_ID_CNS_CTRL:
			nvmet_passthru_override_id_ctrl(req);
			अवरोध;
		हाल NVME_ID_CNS_NS:
			nvmet_passthru_override_id_ns(req);
			अवरोध;
		पूर्ण
	पूर्ण

	req->cqe->result = nvme_req(rq)->result;
	nvmet_req_complete(req, status);
	blk_mq_मुक्त_request(rq);
पूर्ण

अटल व्योम nvmet_passthru_req_करोne(काष्ठा request *rq,
				    blk_status_t blk_status)
अणु
	काष्ठा nvmet_req *req = rq->end_io_data;

	req->cqe->result = nvme_req(rq)->result;
	nvmet_req_complete(req, nvme_req(rq)->status);
	blk_mq_मुक्त_request(rq);
पूर्ण

अटल पूर्णांक nvmet_passthru_map_sg(काष्ठा nvmet_req *req, काष्ठा request *rq)
अणु
	काष्ठा scatterlist *sg;
	काष्ठा bio *bio;
	पूर्णांक i;

	अगर (req->sg_cnt > BIO_MAX_VECS)
		वापस -EINVAL;

	अगर (nvmet_use_अंतरभूत_bvec(req)) अणु
		bio = &req->p.अंतरभूत_bio;
		bio_init(bio, req->अंतरभूत_bvec, ARRAY_SIZE(req->अंतरभूत_bvec));
	पूर्ण अन्यथा अणु
		bio = bio_alloc(GFP_KERNEL, bio_max_segs(req->sg_cnt));
		bio->bi_end_io = bio_put;
	पूर्ण
	bio->bi_opf = req_op(rq);

	क्रम_each_sg(req->sg, sg, req->sg_cnt, i) अणु
		अगर (bio_add_pc_page(rq->q, bio, sg_page(sg), sg->length,
				    sg->offset) < sg->length) अणु
			अगर (bio != &req->p.अंतरभूत_bio)
				bio_put(bio);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	blk_rq_bio_prep(rq, bio, req->sg_cnt);

	वापस 0;
पूर्ण

अटल व्योम nvmet_passthru_execute_cmd(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvme_ctrl *ctrl = nvmet_req_passthru_ctrl(req);
	काष्ठा request_queue *q = ctrl->admin_q;
	काष्ठा nvme_ns *ns = शून्य;
	काष्ठा request *rq = शून्य;
	अचिन्हित पूर्णांक समयout;
	u32 effects;
	u16 status;
	पूर्णांक ret;

	अगर (likely(req->sq->qid != 0)) अणु
		u32 nsid = le32_to_cpu(req->cmd->common.nsid);

		ns = nvme_find_get_ns(ctrl, nsid);
		अगर (unlikely(!ns)) अणु
			pr_err("failed to get passthru ns nsid:%u\n", nsid);
			status = NVME_SC_INVALID_NS | NVME_SC_DNR;
			जाओ out;
		पूर्ण

		q = ns->queue;
		समयout = nvmet_req_subsys(req)->io_समयout;
	पूर्ण अन्यथा अणु
		समयout = nvmet_req_subsys(req)->admin_समयout;
	पूर्ण

	rq = nvme_alloc_request(q, req->cmd, 0);
	अगर (IS_ERR(rq)) अणु
		status = NVME_SC_INTERNAL;
		जाओ out_put_ns;
	पूर्ण

	अगर (समयout)
		rq->समयout = समयout;

	अगर (req->sg_cnt) अणु
		ret = nvmet_passthru_map_sg(req, rq);
		अगर (unlikely(ret)) अणु
			status = NVME_SC_INTERNAL;
			जाओ out_put_req;
		पूर्ण
	पूर्ण

	/*
	 * If there are effects क्रम the command we are about to execute, or
	 * an end_req function we need to use nvme_execute_passthru_rq()
	 * synchronously in a work item seeing the end_req function and
	 * nvme_passthru_end() can't be called in the request करोne callback
	 * which is typically in पूर्णांकerrupt context.
	 */
	effects = nvme_command_effects(ctrl, ns, req->cmd->common.opcode);
	अगर (req->p.use_workqueue || effects) अणु
		INIT_WORK(&req->p.work, nvmet_passthru_execute_cmd_work);
		req->p.rq = rq;
		schedule_work(&req->p.work);
	पूर्ण अन्यथा अणु
		rq->end_io_data = req;
		blk_execute_rq_noरुको(ns ? ns->disk : शून्य, rq, 0,
				      nvmet_passthru_req_करोne);
	पूर्ण

	अगर (ns)
		nvme_put_ns(ns);

	वापस;

out_put_req:
	blk_mq_मुक्त_request(rq);
out_put_ns:
	अगर (ns)
		nvme_put_ns(ns);
out:
	nvmet_req_complete(req, status);
पूर्ण

/*
 * We need to emulate set host behaviour to ensure that any requested
 * behaviour of the target's host matches the requested behaviour
 * of the device's host and fail otherwise.
 */
अटल व्योम nvmet_passthru_set_host_behaviour(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvme_ctrl *ctrl = nvmet_req_passthru_ctrl(req);
	काष्ठा nvme_feat_host_behavior *host;
	u16 status = NVME_SC_INTERNAL;
	पूर्णांक ret;

	host = kzalloc(माप(*host) * 2, GFP_KERNEL);
	अगर (!host)
		जाओ out_complete_req;

	ret = nvme_get_features(ctrl, NVME_FEAT_HOST_BEHAVIOR, 0,
				host, माप(*host), शून्य);
	अगर (ret)
		जाओ out_मुक्त_host;

	status = nvmet_copy_from_sgl(req, 0, &host[1], माप(*host));
	अगर (status)
		जाओ out_मुक्त_host;

	अगर (स_भेद(&host[0], &host[1], माप(host[0]))) अणु
		pr_warn("target host has requested different behaviour from the local host\n");
		status = NVME_SC_INTERNAL;
	पूर्ण

out_मुक्त_host:
	kमुक्त(host);
out_complete_req:
	nvmet_req_complete(req, status);
पूर्ण

अटल u16 nvmet_setup_passthru_command(काष्ठा nvmet_req *req)
अणु
	req->p.use_workqueue = false;
	req->execute = nvmet_passthru_execute_cmd;
	वापस NVME_SC_SUCCESS;
पूर्ण

u16 nvmet_parse_passthru_io_cmd(काष्ठा nvmet_req *req)
अणु
	/* Reject any commands with non-sgl flags set (ie. fused commands) */
	अगर (req->cmd->common.flags & ~NVME_CMD_SGL_ALL)
		वापस NVME_SC_INVALID_FIELD;

	चयन (req->cmd->common.opcode) अणु
	हाल nvme_cmd_resv_रेजिस्टर:
	हाल nvme_cmd_resv_report:
	हाल nvme_cmd_resv_acquire:
	हाल nvme_cmd_resv_release:
		/*
		 * Reservations cannot be supported properly because the
		 * underlying device has no way of dअगरferentiating dअगरferent
		 * hosts that connect via fabrics. This could potentially be
		 * emulated in the future अगर regular tarमाला_लो grow support क्रम
		 * this feature.
		 */
		वापस NVME_SC_INVALID_OPCODE | NVME_SC_DNR;
	पूर्ण

	वापस nvmet_setup_passthru_command(req);
पूर्ण

/*
 * Only features that are emulated or specअगरically allowed in the list  are
 * passed करोwn to the controller. This function implements the allow list क्रम
 * both get and set features.
 */
अटल u16 nvmet_passthru_get_set_features(काष्ठा nvmet_req *req)
अणु
	चयन (le32_to_cpu(req->cmd->features.fid)) अणु
	हाल NVME_FEAT_ARBITRATION:
	हाल NVME_FEAT_POWER_MGMT:
	हाल NVME_FEAT_LBA_RANGE:
	हाल NVME_FEAT_TEMP_THRESH:
	हाल NVME_FEAT_ERR_RECOVERY:
	हाल NVME_FEAT_VOLATILE_WC:
	हाल NVME_FEAT_WRITE_ATOMIC:
	हाल NVME_FEAT_AUTO_PST:
	हाल NVME_FEAT_TIMESTAMP:
	हाल NVME_FEAT_HCTM:
	हाल NVME_FEAT_NOPSC:
	हाल NVME_FEAT_RRL:
	हाल NVME_FEAT_PLM_CONFIG:
	हाल NVME_FEAT_PLM_WINDOW:
	हाल NVME_FEAT_HOST_BEHAVIOR:
	हाल NVME_FEAT_SANITIZE:
	हाल NVME_FEAT_VENDOR_START ... NVME_FEAT_VENDOR_END:
		वापस nvmet_setup_passthru_command(req);

	हाल NVME_FEAT_ASYNC_EVENT:
		/* There is no support क्रम क्रमwarding ASYNC events */
	हाल NVME_FEAT_IRQ_COALESCE:
	हाल NVME_FEAT_IRQ_CONFIG:
		/* The IRQ settings will not apply to the target controller */
	हाल NVME_FEAT_HOST_MEM_BUF:
		/*
		 * Any HMB that's set will not be passed through and will
		 * not work as expected
		 */
	हाल NVME_FEAT_SW_PROGRESS:
		/*
		 * The Pre-Boot Software Load Count करोesn't make much
		 * sense क्रम a target to export
		 */
	हाल NVME_FEAT_RESV_MASK:
	हाल NVME_FEAT_RESV_PERSIST:
		/* No reservations, see nvmet_parse_passthru_io_cmd() */
	शेष:
		वापस NVME_SC_INVALID_OPCODE | NVME_SC_DNR;
	पूर्ण
पूर्ण

u16 nvmet_parse_passthru_admin_cmd(काष्ठा nvmet_req *req)
अणु
	/* Reject any commands with non-sgl flags set (ie. fused commands) */
	अगर (req->cmd->common.flags & ~NVME_CMD_SGL_ALL)
		वापस NVME_SC_INVALID_FIELD;

	/*
	 * Passthru all venकरोr specअगरic commands
	 */
	अगर (req->cmd->common.opcode >= nvme_admin_venकरोr_start)
		वापस nvmet_setup_passthru_command(req);

	चयन (req->cmd->common.opcode) अणु
	हाल nvme_admin_async_event:
		req->execute = nvmet_execute_async_event;
		वापस NVME_SC_SUCCESS;
	हाल nvme_admin_keep_alive:
		/*
		 * Most PCIe ctrls करोn't support keep alive cmd, we route keep
		 * alive to the non-passthru mode. In future please change this
		 * code when PCIe ctrls with keep alive support available.
		 */
		req->execute = nvmet_execute_keep_alive;
		वापस NVME_SC_SUCCESS;
	हाल nvme_admin_set_features:
		चयन (le32_to_cpu(req->cmd->features.fid)) अणु
		हाल NVME_FEAT_ASYNC_EVENT:
		हाल NVME_FEAT_KATO:
		हाल NVME_FEAT_NUM_QUEUES:
		हाल NVME_FEAT_HOST_ID:
			req->execute = nvmet_execute_set_features;
			वापस NVME_SC_SUCCESS;
		हाल NVME_FEAT_HOST_BEHAVIOR:
			req->execute = nvmet_passthru_set_host_behaviour;
			वापस NVME_SC_SUCCESS;
		शेष:
			वापस nvmet_passthru_get_set_features(req);
		पूर्ण
		अवरोध;
	हाल nvme_admin_get_features:
		चयन (le32_to_cpu(req->cmd->features.fid)) अणु
		हाल NVME_FEAT_ASYNC_EVENT:
		हाल NVME_FEAT_KATO:
		हाल NVME_FEAT_NUM_QUEUES:
		हाल NVME_FEAT_HOST_ID:
			req->execute = nvmet_execute_get_features;
			वापस NVME_SC_SUCCESS;
		शेष:
			वापस nvmet_passthru_get_set_features(req);
		पूर्ण
		अवरोध;
	हाल nvme_admin_identअगरy:
		चयन (req->cmd->identअगरy.cns) अणु
		हाल NVME_ID_CNS_CTRL:
			req->execute = nvmet_passthru_execute_cmd;
			req->p.use_workqueue = true;
			वापस NVME_SC_SUCCESS;
		हाल NVME_ID_CNS_CS_CTRL:
			चयन (req->cmd->identअगरy.csi) अणु
			हाल NVME_CSI_ZNS:
				req->execute = nvmet_passthru_execute_cmd;
				req->p.use_workqueue = true;
				वापस NVME_SC_SUCCESS;
			पूर्ण
			वापस NVME_SC_INVALID_OPCODE | NVME_SC_DNR;
		हाल NVME_ID_CNS_NS:
			req->execute = nvmet_passthru_execute_cmd;
			req->p.use_workqueue = true;
			वापस NVME_SC_SUCCESS;
		हाल NVME_ID_CNS_CS_NS:
			चयन (req->cmd->identअगरy.csi) अणु
			हाल NVME_CSI_ZNS:
				req->execute = nvmet_passthru_execute_cmd;
				req->p.use_workqueue = true;
				वापस NVME_SC_SUCCESS;
			पूर्ण
			वापस NVME_SC_INVALID_OPCODE | NVME_SC_DNR;
		शेष:
			वापस nvmet_setup_passthru_command(req);
		पूर्ण
	हाल nvme_admin_get_log_page:
		वापस nvmet_setup_passthru_command(req);
	शेष:
		/* Reject commands not in the allowlist above */
		वापस nvmet_report_invalid_opcode(req);
	पूर्ण
पूर्ण

पूर्णांक nvmet_passthru_ctrl_enable(काष्ठा nvmet_subsys *subsys)
अणु
	काष्ठा nvme_ctrl *ctrl;
	काष्ठा file *file;
	पूर्णांक ret = -EINVAL;
	व्योम *old;

	mutex_lock(&subsys->lock);
	अगर (!subsys->passthru_ctrl_path)
		जाओ out_unlock;
	अगर (subsys->passthru_ctrl)
		जाओ out_unlock;

	अगर (subsys->nr_namespaces) अणु
		pr_info("cannot enable both passthru and regular namespaces for a single subsystem");
		जाओ out_unlock;
	पूर्ण

	file = filp_खोलो(subsys->passthru_ctrl_path, O_RDWR, 0);
	अगर (IS_ERR(file)) अणु
		ret = PTR_ERR(file);
		जाओ out_unlock;
	पूर्ण

	ctrl = nvme_ctrl_from_file(file);
	अगर (!ctrl) अणु
		pr_err("failed to open nvme controller %s\n",
		       subsys->passthru_ctrl_path);

		जाओ out_put_file;
	पूर्ण

	old = xa_cmpxchg(&passthru_subप्रणालीs, ctrl->cntlid, शून्य,
			 subsys, GFP_KERNEL);
	अगर (xa_is_err(old)) अणु
		ret = xa_err(old);
		जाओ out_put_file;
	पूर्ण

	अगर (old)
		जाओ out_put_file;

	subsys->passthru_ctrl = ctrl;
	subsys->ver = ctrl->vs;

	अगर (subsys->ver < NVME_VS(1, 2, 1)) अणु
		pr_warn("nvme controller version is too old: %llu.%llu.%llu, advertising 1.2.1\n",
			NVME_MAJOR(subsys->ver), NVME_MINOR(subsys->ver),
			NVME_TERTIARY(subsys->ver));
		subsys->ver = NVME_VS(1, 2, 1);
	पूर्ण
	nvme_get_ctrl(ctrl);
	__module_get(subsys->passthru_ctrl->ops->module);
	ret = 0;

out_put_file:
	filp_बंद(file, शून्य);
out_unlock:
	mutex_unlock(&subsys->lock);
	वापस ret;
पूर्ण

अटल व्योम __nvmet_passthru_ctrl_disable(काष्ठा nvmet_subsys *subsys)
अणु
	अगर (subsys->passthru_ctrl) अणु
		xa_erase(&passthru_subप्रणालीs, subsys->passthru_ctrl->cntlid);
		module_put(subsys->passthru_ctrl->ops->module);
		nvme_put_ctrl(subsys->passthru_ctrl);
	पूर्ण
	subsys->passthru_ctrl = शून्य;
	subsys->ver = NVMET_DEFAULT_VS;
पूर्ण

व्योम nvmet_passthru_ctrl_disable(काष्ठा nvmet_subsys *subsys)
अणु
	mutex_lock(&subsys->lock);
	__nvmet_passthru_ctrl_disable(subsys);
	mutex_unlock(&subsys->lock);
पूर्ण

व्योम nvmet_passthru_subsys_मुक्त(काष्ठा nvmet_subsys *subsys)
अणु
	mutex_lock(&subsys->lock);
	__nvmet_passthru_ctrl_disable(subsys);
	mutex_unlock(&subsys->lock);
	kमुक्त(subsys->passthru_ctrl_path);
पूर्ण
