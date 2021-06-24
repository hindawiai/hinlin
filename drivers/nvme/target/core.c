<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Common code क्रम the NVMe target.
 * Copyright (c) 2015-2016 HGST, a Western Digital Company.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/rculist.h>
#समावेश <linux/pci-p2pdma.h>
#समावेश <linux/scatterlist.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace.h"

#समावेश "nvmet.h"

काष्ठा workqueue_काष्ठा *buffered_io_wq;
अटल स्थिर काष्ठा nvmet_fabrics_ops *nvmet_transports[NVMF_TRTYPE_MAX];
अटल DEFINE_IDA(cntlid_ida);

/*
 * This पढ़ो/ग_लिखो semaphore is used to synchronize access to configuration
 * inक्रमmation on a target प्रणाली that will result in discovery log page
 * inक्रमmation change क्रम at least one host.
 * The full list of resources to रक्षित by this semaphore is:
 *
 *  - subप्रणालीs list
 *  - per-subप्रणाली allowed hosts list
 *  - allow_any_host subप्रणाली attribute
 *  - nvmet_genctr
 *  - the nvmet_transports array
 *
 * When updating any of those lists/काष्ठाures ग_लिखो lock should be obtained,
 * जबतक when पढ़ोing (popolating discovery log page or checking host-subप्रणाली
 * link) पढ़ो lock is obtained to allow concurrent पढ़ोs.
 */
DECLARE_RWSEM(nvmet_config_sem);

u32 nvmet_ana_group_enabled[NVMET_MAX_ANAGRPS + 1];
u64 nvmet_ana_chgcnt;
DECLARE_RWSEM(nvmet_ana_sem);

अंतरभूत u16 त्रुटि_सं_to_nvme_status(काष्ठा nvmet_req *req, पूर्णांक त्रुटि_सं)
अणु
	u16 status;

	चयन (त्रुटि_सं) अणु
	हाल 0:
		status = NVME_SC_SUCCESS;
		अवरोध;
	हाल -ENOSPC:
		req->error_loc = दुरत्व(काष्ठा nvme_rw_command, length);
		status = NVME_SC_CAP_EXCEEDED | NVME_SC_DNR;
		अवरोध;
	हाल -EREMOTEIO:
		req->error_loc = दुरत्व(काष्ठा nvme_rw_command, slba);
		status = NVME_SC_LBA_RANGE | NVME_SC_DNR;
		अवरोध;
	हाल -EOPNOTSUPP:
		req->error_loc = दुरत्व(काष्ठा nvme_common_command, opcode);
		चयन (req->cmd->common.opcode) अणु
		हाल nvme_cmd_dsm:
		हाल nvme_cmd_ग_लिखो_zeroes:
			status = NVME_SC_ONCS_NOT_SUPPORTED | NVME_SC_DNR;
			अवरोध;
		शेष:
			status = NVME_SC_INVALID_OPCODE | NVME_SC_DNR;
		पूर्ण
		अवरोध;
	हाल -ENODATA:
		req->error_loc = दुरत्व(काष्ठा nvme_rw_command, nsid);
		status = NVME_SC_ACCESS_DENIED;
		अवरोध;
	हाल -EIO:
		fallthrough;
	शेष:
		req->error_loc = दुरत्व(काष्ठा nvme_common_command, opcode);
		status = NVME_SC_INTERNAL | NVME_SC_DNR;
	पूर्ण

	वापस status;
पूर्ण

u16 nvmet_report_invalid_opcode(काष्ठा nvmet_req *req)
अणु
	pr_debug("unhandled cmd %d on qid %d\n", req->cmd->common.opcode,
		 req->sq->qid);

	req->error_loc = दुरत्व(काष्ठा nvme_common_command, opcode);
	वापस NVME_SC_INVALID_OPCODE | NVME_SC_DNR;
पूर्ण

अटल काष्ठा nvmet_subsys *nvmet_find_get_subsys(काष्ठा nvmet_port *port,
		स्थिर अक्षर *subsysnqn);

u16 nvmet_copy_to_sgl(काष्ठा nvmet_req *req, off_t off, स्थिर व्योम *buf,
		माप_प्रकार len)
अणु
	अगर (sg_pcopy_from_buffer(req->sg, req->sg_cnt, buf, len, off) != len) अणु
		req->error_loc = दुरत्व(काष्ठा nvme_common_command, dptr);
		वापस NVME_SC_SGL_INVALID_DATA | NVME_SC_DNR;
	पूर्ण
	वापस 0;
पूर्ण

u16 nvmet_copy_from_sgl(काष्ठा nvmet_req *req, off_t off, व्योम *buf, माप_प्रकार len)
अणु
	अगर (sg_pcopy_to_buffer(req->sg, req->sg_cnt, buf, len, off) != len) अणु
		req->error_loc = दुरत्व(काष्ठा nvme_common_command, dptr);
		वापस NVME_SC_SGL_INVALID_DATA | NVME_SC_DNR;
	पूर्ण
	वापस 0;
पूर्ण

u16 nvmet_zero_sgl(काष्ठा nvmet_req *req, off_t off, माप_प्रकार len)
अणु
	अगर (sg_zero_buffer(req->sg, req->sg_cnt, len, off) != len) अणु
		req->error_loc = दुरत्व(काष्ठा nvme_common_command, dptr);
		वापस NVME_SC_SGL_INVALID_DATA | NVME_SC_DNR;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक nvmet_max_nsid(काष्ठा nvmet_subsys *subsys)
अणु
	अचिन्हित दीर्घ nsid = 0;
	काष्ठा nvmet_ns *cur;
	अचिन्हित दीर्घ idx;

	xa_क्रम_each(&subsys->namespaces, idx, cur)
		nsid = cur->nsid;

	वापस nsid;
पूर्ण

अटल u32 nvmet_async_event_result(काष्ठा nvmet_async_event *aen)
अणु
	वापस aen->event_type | (aen->event_info << 8) | (aen->log_page << 16);
पूर्ण

अटल व्योम nvmet_async_events_failall(काष्ठा nvmet_ctrl *ctrl)
अणु
	u16 status = NVME_SC_INTERNAL | NVME_SC_DNR;
	काष्ठा nvmet_req *req;

	mutex_lock(&ctrl->lock);
	जबतक (ctrl->nr_async_event_cmds) अणु
		req = ctrl->async_event_cmds[--ctrl->nr_async_event_cmds];
		mutex_unlock(&ctrl->lock);
		nvmet_req_complete(req, status);
		mutex_lock(&ctrl->lock);
	पूर्ण
	mutex_unlock(&ctrl->lock);
पूर्ण

अटल व्योम nvmet_async_events_process(काष्ठा nvmet_ctrl *ctrl)
अणु
	काष्ठा nvmet_async_event *aen;
	काष्ठा nvmet_req *req;

	mutex_lock(&ctrl->lock);
	जबतक (ctrl->nr_async_event_cmds && !list_empty(&ctrl->async_events)) अणु
		aen = list_first_entry(&ctrl->async_events,
				       काष्ठा nvmet_async_event, entry);
		req = ctrl->async_event_cmds[--ctrl->nr_async_event_cmds];
		nvmet_set_result(req, nvmet_async_event_result(aen));

		list_del(&aen->entry);
		kमुक्त(aen);

		mutex_unlock(&ctrl->lock);
		trace_nvmet_async_event(ctrl, req->cqe->result.u32);
		nvmet_req_complete(req, 0);
		mutex_lock(&ctrl->lock);
	पूर्ण
	mutex_unlock(&ctrl->lock);
पूर्ण

अटल व्योम nvmet_async_events_मुक्त(काष्ठा nvmet_ctrl *ctrl)
अणु
	काष्ठा nvmet_async_event *aen, *पंचांगp;

	mutex_lock(&ctrl->lock);
	list_क्रम_each_entry_safe(aen, पंचांगp, &ctrl->async_events, entry) अणु
		list_del(&aen->entry);
		kमुक्त(aen);
	पूर्ण
	mutex_unlock(&ctrl->lock);
पूर्ण

अटल व्योम nvmet_async_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvmet_ctrl *ctrl =
		container_of(work, काष्ठा nvmet_ctrl, async_event_work);

	nvmet_async_events_process(ctrl);
पूर्ण

व्योम nvmet_add_async_event(काष्ठा nvmet_ctrl *ctrl, u8 event_type,
		u8 event_info, u8 log_page)
अणु
	काष्ठा nvmet_async_event *aen;

	aen = kदो_स्मृति(माप(*aen), GFP_KERNEL);
	अगर (!aen)
		वापस;

	aen->event_type = event_type;
	aen->event_info = event_info;
	aen->log_page = log_page;

	mutex_lock(&ctrl->lock);
	list_add_tail(&aen->entry, &ctrl->async_events);
	mutex_unlock(&ctrl->lock);

	schedule_work(&ctrl->async_event_work);
पूर्ण

अटल व्योम nvmet_add_to_changed_ns_log(काष्ठा nvmet_ctrl *ctrl, __le32 nsid)
अणु
	u32 i;

	mutex_lock(&ctrl->lock);
	अगर (ctrl->nr_changed_ns > NVME_MAX_CHANGED_NAMESPACES)
		जाओ out_unlock;

	क्रम (i = 0; i < ctrl->nr_changed_ns; i++) अणु
		अगर (ctrl->changed_ns_list[i] == nsid)
			जाओ out_unlock;
	पूर्ण

	अगर (ctrl->nr_changed_ns == NVME_MAX_CHANGED_NAMESPACES) अणु
		ctrl->changed_ns_list[0] = cpu_to_le32(0xffffffff);
		ctrl->nr_changed_ns = U32_MAX;
		जाओ out_unlock;
	पूर्ण

	ctrl->changed_ns_list[ctrl->nr_changed_ns++] = nsid;
out_unlock:
	mutex_unlock(&ctrl->lock);
पूर्ण

व्योम nvmet_ns_changed(काष्ठा nvmet_subsys *subsys, u32 nsid)
अणु
	काष्ठा nvmet_ctrl *ctrl;

	lockdep_निश्चित_held(&subsys->lock);

	list_क्रम_each_entry(ctrl, &subsys->ctrls, subsys_entry) अणु
		nvmet_add_to_changed_ns_log(ctrl, cpu_to_le32(nsid));
		अगर (nvmet_aen_bit_disabled(ctrl, NVME_AEN_BIT_NS_ATTR))
			जारी;
		nvmet_add_async_event(ctrl, NVME_AER_TYPE_NOTICE,
				NVME_AER_NOTICE_NS_CHANGED,
				NVME_LOG_CHANGED_NS);
	पूर्ण
पूर्ण

व्योम nvmet_send_ana_event(काष्ठा nvmet_subsys *subsys,
		काष्ठा nvmet_port *port)
अणु
	काष्ठा nvmet_ctrl *ctrl;

	mutex_lock(&subsys->lock);
	list_क्रम_each_entry(ctrl, &subsys->ctrls, subsys_entry) अणु
		अगर (port && ctrl->port != port)
			जारी;
		अगर (nvmet_aen_bit_disabled(ctrl, NVME_AEN_BIT_ANA_CHANGE))
			जारी;
		nvmet_add_async_event(ctrl, NVME_AER_TYPE_NOTICE,
				NVME_AER_NOTICE_ANA, NVME_LOG_ANA);
	पूर्ण
	mutex_unlock(&subsys->lock);
पूर्ण

व्योम nvmet_port_send_ana_event(काष्ठा nvmet_port *port)
अणु
	काष्ठा nvmet_subsys_link *p;

	करोwn_पढ़ो(&nvmet_config_sem);
	list_क्रम_each_entry(p, &port->subप्रणालीs, entry)
		nvmet_send_ana_event(p->subsys, port);
	up_पढ़ो(&nvmet_config_sem);
पूर्ण

पूर्णांक nvmet_रेजिस्टर_transport(स्थिर काष्ठा nvmet_fabrics_ops *ops)
अणु
	पूर्णांक ret = 0;

	करोwn_ग_लिखो(&nvmet_config_sem);
	अगर (nvmet_transports[ops->type])
		ret = -EINVAL;
	अन्यथा
		nvmet_transports[ops->type] = ops;
	up_ग_लिखो(&nvmet_config_sem);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nvmet_रेजिस्टर_transport);

व्योम nvmet_unरेजिस्टर_transport(स्थिर काष्ठा nvmet_fabrics_ops *ops)
अणु
	करोwn_ग_लिखो(&nvmet_config_sem);
	nvmet_transports[ops->type] = शून्य;
	up_ग_लिखो(&nvmet_config_sem);
पूर्ण
EXPORT_SYMBOL_GPL(nvmet_unरेजिस्टर_transport);

व्योम nvmet_port_del_ctrls(काष्ठा nvmet_port *port, काष्ठा nvmet_subsys *subsys)
अणु
	काष्ठा nvmet_ctrl *ctrl;

	mutex_lock(&subsys->lock);
	list_क्रम_each_entry(ctrl, &subsys->ctrls, subsys_entry) अणु
		अगर (ctrl->port == port)
			ctrl->ops->delete_ctrl(ctrl);
	पूर्ण
	mutex_unlock(&subsys->lock);
पूर्ण

पूर्णांक nvmet_enable_port(काष्ठा nvmet_port *port)
अणु
	स्थिर काष्ठा nvmet_fabrics_ops *ops;
	पूर्णांक ret;

	lockdep_निश्चित_held(&nvmet_config_sem);

	ops = nvmet_transports[port->disc_addr.trtype];
	अगर (!ops) अणु
		up_ग_लिखो(&nvmet_config_sem);
		request_module("nvmet-transport-%d", port->disc_addr.trtype);
		करोwn_ग_लिखो(&nvmet_config_sem);
		ops = nvmet_transports[port->disc_addr.trtype];
		अगर (!ops) अणु
			pr_err("transport type %d not supported\n",
				port->disc_addr.trtype);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!try_module_get(ops->owner))
		वापस -EINVAL;

	/*
	 * If the user requested PI support and the transport isn't pi capable,
	 * करोn't enable the port.
	 */
	अगर (port->pi_enable && !(ops->flags & NVMF_METADATA_SUPPORTED)) अणु
		pr_err("T10-PI is not supported by transport type %d\n",
		       port->disc_addr.trtype);
		ret = -EINVAL;
		जाओ out_put;
	पूर्ण

	ret = ops->add_port(port);
	अगर (ret)
		जाओ out_put;

	/* If the transport didn't set अंतरभूत_data_size, then disable it. */
	अगर (port->अंतरभूत_data_size < 0)
		port->अंतरभूत_data_size = 0;

	port->enabled = true;
	port->tr_ops = ops;
	वापस 0;

out_put:
	module_put(ops->owner);
	वापस ret;
पूर्ण

व्योम nvmet_disable_port(काष्ठा nvmet_port *port)
अणु
	स्थिर काष्ठा nvmet_fabrics_ops *ops;

	lockdep_निश्चित_held(&nvmet_config_sem);

	port->enabled = false;
	port->tr_ops = शून्य;

	ops = nvmet_transports[port->disc_addr.trtype];
	ops->हटाओ_port(port);
	module_put(ops->owner);
पूर्ण

अटल व्योम nvmet_keep_alive_समयr(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvmet_ctrl *ctrl = container_of(to_delayed_work(work),
			काष्ठा nvmet_ctrl, ka_work);
	bool reset_tbkas = ctrl->reset_tbkas;

	ctrl->reset_tbkas = false;
	अगर (reset_tbkas) अणु
		pr_debug("ctrl %d reschedule traffic based keep-alive timer\n",
			ctrl->cntlid);
		schedule_delayed_work(&ctrl->ka_work, ctrl->kato * HZ);
		वापस;
	पूर्ण

	pr_err("ctrl %d keep-alive timer (%d seconds) expired!\n",
		ctrl->cntlid, ctrl->kato);

	nvmet_ctrl_fatal_error(ctrl);
पूर्ण

व्योम nvmet_start_keep_alive_समयr(काष्ठा nvmet_ctrl *ctrl)
अणु
	अगर (unlikely(ctrl->kato == 0))
		वापस;

	pr_debug("ctrl %d start keep-alive timer for %d secs\n",
		ctrl->cntlid, ctrl->kato);

	INIT_DELAYED_WORK(&ctrl->ka_work, nvmet_keep_alive_समयr);
	schedule_delayed_work(&ctrl->ka_work, ctrl->kato * HZ);
पूर्ण

व्योम nvmet_stop_keep_alive_समयr(काष्ठा nvmet_ctrl *ctrl)
अणु
	अगर (unlikely(ctrl->kato == 0))
		वापस;

	pr_debug("ctrl %d stop keep-alive\n", ctrl->cntlid);

	cancel_delayed_work_sync(&ctrl->ka_work);
पूर्ण

u16 nvmet_req_find_ns(काष्ठा nvmet_req *req)
अणु
	u32 nsid = le32_to_cpu(req->cmd->common.nsid);

	req->ns = xa_load(&nvmet_req_subsys(req)->namespaces, nsid);
	अगर (unlikely(!req->ns)) अणु
		req->error_loc = दुरत्व(काष्ठा nvme_common_command, nsid);
		वापस NVME_SC_INVALID_NS | NVME_SC_DNR;
	पूर्ण

	percpu_ref_get(&req->ns->ref);
	वापस NVME_SC_SUCCESS;
पूर्ण

अटल व्योम nvmet_destroy_namespace(काष्ठा percpu_ref *ref)
अणु
	काष्ठा nvmet_ns *ns = container_of(ref, काष्ठा nvmet_ns, ref);

	complete(&ns->disable_करोne);
पूर्ण

व्योम nvmet_put_namespace(काष्ठा nvmet_ns *ns)
अणु
	percpu_ref_put(&ns->ref);
पूर्ण

अटल व्योम nvmet_ns_dev_disable(काष्ठा nvmet_ns *ns)
अणु
	nvmet_bdev_ns_disable(ns);
	nvmet_file_ns_disable(ns);
पूर्ण

अटल पूर्णांक nvmet_p2pmem_ns_enable(काष्ठा nvmet_ns *ns)
अणु
	पूर्णांक ret;
	काष्ठा pci_dev *p2p_dev;

	अगर (!ns->use_p2pmem)
		वापस 0;

	अगर (!ns->bdev) अणु
		pr_err("peer-to-peer DMA is not supported by non-block device namespaces\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!blk_queue_pci_p2pdma(ns->bdev->bd_disk->queue)) अणु
		pr_err("peer-to-peer DMA is not supported by the driver of %s\n",
		       ns->device_path);
		वापस -EINVAL;
	पूर्ण

	अगर (ns->p2p_dev) अणु
		ret = pci_p2pdma_distance(ns->p2p_dev, nvmet_ns_dev(ns), true);
		अगर (ret < 0)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/*
		 * Right now we just check that there is p2pmem available so
		 * we can report an error to the user right away अगर there
		 * is not. We'll find the actual device to use once we
		 * setup the controller when the port's device is available.
		 */

		p2p_dev = pci_p2pmem_find(nvmet_ns_dev(ns));
		अगर (!p2p_dev) अणु
			pr_err("no peer-to-peer memory is available for %s\n",
			       ns->device_path);
			वापस -EINVAL;
		पूर्ण

		pci_dev_put(p2p_dev);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Note: ctrl->subsys->lock should be held when calling this function
 */
अटल व्योम nvmet_p2pmem_ns_add_p2p(काष्ठा nvmet_ctrl *ctrl,
				    काष्ठा nvmet_ns *ns)
अणु
	काष्ठा device *clients[2];
	काष्ठा pci_dev *p2p_dev;
	पूर्णांक ret;

	अगर (!ctrl->p2p_client || !ns->use_p2pmem)
		वापस;

	अगर (ns->p2p_dev) अणु
		ret = pci_p2pdma_distance(ns->p2p_dev, ctrl->p2p_client, true);
		अगर (ret < 0)
			वापस;

		p2p_dev = pci_dev_get(ns->p2p_dev);
	पूर्ण अन्यथा अणु
		clients[0] = ctrl->p2p_client;
		clients[1] = nvmet_ns_dev(ns);

		p2p_dev = pci_p2pmem_find_many(clients, ARRAY_SIZE(clients));
		अगर (!p2p_dev) अणु
			pr_err("no peer-to-peer memory is available that's supported by %s and %s\n",
			       dev_name(ctrl->p2p_client), ns->device_path);
			वापस;
		पूर्ण
	पूर्ण

	ret = radix_tree_insert(&ctrl->p2p_ns_map, ns->nsid, p2p_dev);
	अगर (ret < 0)
		pci_dev_put(p2p_dev);

	pr_info("using p2pmem on %s for nsid %d\n", pci_name(p2p_dev),
		ns->nsid);
पूर्ण

व्योम nvmet_ns_revalidate(काष्ठा nvmet_ns *ns)
अणु
	loff_t oldsize = ns->size;

	अगर (ns->bdev)
		nvmet_bdev_ns_revalidate(ns);
	अन्यथा
		nvmet_file_ns_revalidate(ns);

	अगर (oldsize != ns->size)
		nvmet_ns_changed(ns->subsys, ns->nsid);
पूर्ण

पूर्णांक nvmet_ns_enable(काष्ठा nvmet_ns *ns)
अणु
	काष्ठा nvmet_subsys *subsys = ns->subsys;
	काष्ठा nvmet_ctrl *ctrl;
	पूर्णांक ret;

	mutex_lock(&subsys->lock);
	ret = 0;

	अगर (nvmet_passthru_ctrl(subsys)) अणु
		pr_info("cannot enable both passthru and regular namespaces for a single subsystem");
		जाओ out_unlock;
	पूर्ण

	अगर (ns->enabled)
		जाओ out_unlock;

	ret = -EMखाता;
	अगर (subsys->nr_namespaces == NVMET_MAX_NAMESPACES)
		जाओ out_unlock;

	ret = nvmet_bdev_ns_enable(ns);
	अगर (ret == -ENOTBLK)
		ret = nvmet_file_ns_enable(ns);
	अगर (ret)
		जाओ out_unlock;

	ret = nvmet_p2pmem_ns_enable(ns);
	अगर (ret)
		जाओ out_dev_disable;

	list_क्रम_each_entry(ctrl, &subsys->ctrls, subsys_entry)
		nvmet_p2pmem_ns_add_p2p(ctrl, ns);

	ret = percpu_ref_init(&ns->ref, nvmet_destroy_namespace,
				0, GFP_KERNEL);
	अगर (ret)
		जाओ out_dev_put;

	अगर (ns->nsid > subsys->max_nsid)
		subsys->max_nsid = ns->nsid;

	ret = xa_insert(&subsys->namespaces, ns->nsid, ns, GFP_KERNEL);
	अगर (ret)
		जाओ out_restore_subsys_maxnsid;

	subsys->nr_namespaces++;

	nvmet_ns_changed(subsys, ns->nsid);
	ns->enabled = true;
	ret = 0;
out_unlock:
	mutex_unlock(&subsys->lock);
	वापस ret;

out_restore_subsys_maxnsid:
	subsys->max_nsid = nvmet_max_nsid(subsys);
	percpu_ref_निकास(&ns->ref);
out_dev_put:
	list_क्रम_each_entry(ctrl, &subsys->ctrls, subsys_entry)
		pci_dev_put(radix_tree_delete(&ctrl->p2p_ns_map, ns->nsid));
out_dev_disable:
	nvmet_ns_dev_disable(ns);
	जाओ out_unlock;
पूर्ण

व्योम nvmet_ns_disable(काष्ठा nvmet_ns *ns)
अणु
	काष्ठा nvmet_subsys *subsys = ns->subsys;
	काष्ठा nvmet_ctrl *ctrl;

	mutex_lock(&subsys->lock);
	अगर (!ns->enabled)
		जाओ out_unlock;

	ns->enabled = false;
	xa_erase(&ns->subsys->namespaces, ns->nsid);
	अगर (ns->nsid == subsys->max_nsid)
		subsys->max_nsid = nvmet_max_nsid(subsys);

	list_क्रम_each_entry(ctrl, &subsys->ctrls, subsys_entry)
		pci_dev_put(radix_tree_delete(&ctrl->p2p_ns_map, ns->nsid));

	mutex_unlock(&subsys->lock);

	/*
	 * Now that we हटाओd the namespaces from the lookup list, we
	 * can समाप्त the per_cpu ref and रुको क्रम any reमुख्यing references
	 * to be dropped, as well as a RCU grace period क्रम anyone only
	 * using the namepace under rcu_पढ़ो_lock().  Note that we can't
	 * use call_rcu here as we need to ensure the namespaces have
	 * been fully destroyed beक्रमe unloading the module.
	 */
	percpu_ref_समाप्त(&ns->ref);
	synchronize_rcu();
	रुको_क्रम_completion(&ns->disable_करोne);
	percpu_ref_निकास(&ns->ref);

	mutex_lock(&subsys->lock);

	subsys->nr_namespaces--;
	nvmet_ns_changed(subsys, ns->nsid);
	nvmet_ns_dev_disable(ns);
out_unlock:
	mutex_unlock(&subsys->lock);
पूर्ण

व्योम nvmet_ns_मुक्त(काष्ठा nvmet_ns *ns)
अणु
	nvmet_ns_disable(ns);

	करोwn_ग_लिखो(&nvmet_ana_sem);
	nvmet_ana_group_enabled[ns->anagrpid]--;
	up_ग_लिखो(&nvmet_ana_sem);

	kमुक्त(ns->device_path);
	kमुक्त(ns);
पूर्ण

काष्ठा nvmet_ns *nvmet_ns_alloc(काष्ठा nvmet_subsys *subsys, u32 nsid)
अणु
	काष्ठा nvmet_ns *ns;

	ns = kzalloc(माप(*ns), GFP_KERNEL);
	अगर (!ns)
		वापस शून्य;

	init_completion(&ns->disable_करोne);

	ns->nsid = nsid;
	ns->subsys = subsys;

	करोwn_ग_लिखो(&nvmet_ana_sem);
	ns->anagrpid = NVMET_DEFAULT_ANA_GRPID;
	nvmet_ana_group_enabled[ns->anagrpid]++;
	up_ग_लिखो(&nvmet_ana_sem);

	uuid_gen(&ns->uuid);
	ns->buffered_io = false;

	वापस ns;
पूर्ण

अटल व्योम nvmet_update_sq_head(काष्ठा nvmet_req *req)
अणु
	अगर (req->sq->size) अणु
		u32 old_sqhd, new_sqhd;

		करो अणु
			old_sqhd = req->sq->sqhd;
			new_sqhd = (old_sqhd + 1) % req->sq->size;
		पूर्ण जबतक (cmpxchg(&req->sq->sqhd, old_sqhd, new_sqhd) !=
					old_sqhd);
	पूर्ण
	req->cqe->sq_head = cpu_to_le16(req->sq->sqhd & 0x0000FFFF);
पूर्ण

अटल व्योम nvmet_set_error(काष्ठा nvmet_req *req, u16 status)
अणु
	काष्ठा nvmet_ctrl *ctrl = req->sq->ctrl;
	काष्ठा nvme_error_slot *new_error_slot;
	अचिन्हित दीर्घ flags;

	req->cqe->status = cpu_to_le16(status << 1);

	अगर (!ctrl || req->error_loc == NVMET_NO_ERROR_LOC)
		वापस;

	spin_lock_irqsave(&ctrl->error_lock, flags);
	ctrl->err_counter++;
	new_error_slot =
		&ctrl->slots[ctrl->err_counter % NVMET_ERROR_LOG_SLOTS];

	new_error_slot->error_count = cpu_to_le64(ctrl->err_counter);
	new_error_slot->sqid = cpu_to_le16(req->sq->qid);
	new_error_slot->cmdid = cpu_to_le16(req->cmd->common.command_id);
	new_error_slot->status_field = cpu_to_le16(status << 1);
	new_error_slot->param_error_location = cpu_to_le16(req->error_loc);
	new_error_slot->lba = cpu_to_le64(req->error_slba);
	new_error_slot->nsid = req->cmd->common.nsid;
	spin_unlock_irqrestore(&ctrl->error_lock, flags);

	/* set the more bit क्रम this request */
	req->cqe->status |= cpu_to_le16(1 << 14);
पूर्ण

अटल व्योम __nvmet_req_complete(काष्ठा nvmet_req *req, u16 status)
अणु
	अगर (!req->sq->sqhd_disabled)
		nvmet_update_sq_head(req);
	req->cqe->sq_id = cpu_to_le16(req->sq->qid);
	req->cqe->command_id = req->cmd->common.command_id;

	अगर (unlikely(status))
		nvmet_set_error(req, status);

	trace_nvmet_req_complete(req);

	अगर (req->ns)
		nvmet_put_namespace(req->ns);
	req->ops->queue_response(req);
पूर्ण

व्योम nvmet_req_complete(काष्ठा nvmet_req *req, u16 status)
अणु
	__nvmet_req_complete(req, status);
	percpu_ref_put(&req->sq->ref);
पूर्ण
EXPORT_SYMBOL_GPL(nvmet_req_complete);

व्योम nvmet_cq_setup(काष्ठा nvmet_ctrl *ctrl, काष्ठा nvmet_cq *cq,
		u16 qid, u16 size)
अणु
	cq->qid = qid;
	cq->size = size;
पूर्ण

व्योम nvmet_sq_setup(काष्ठा nvmet_ctrl *ctrl, काष्ठा nvmet_sq *sq,
		u16 qid, u16 size)
अणु
	sq->sqhd = 0;
	sq->qid = qid;
	sq->size = size;

	ctrl->sqs[qid] = sq;
पूर्ण

अटल व्योम nvmet_confirm_sq(काष्ठा percpu_ref *ref)
अणु
	काष्ठा nvmet_sq *sq = container_of(ref, काष्ठा nvmet_sq, ref);

	complete(&sq->confirm_करोne);
पूर्ण

व्योम nvmet_sq_destroy(काष्ठा nvmet_sq *sq)
अणु
	काष्ठा nvmet_ctrl *ctrl = sq->ctrl;

	/*
	 * If this is the admin queue, complete all AERs so that our
	 * queue करोesn't have outstanding requests on it.
	 */
	अगर (ctrl && ctrl->sqs && ctrl->sqs[0] == sq)
		nvmet_async_events_failall(ctrl);
	percpu_ref_समाप्त_and_confirm(&sq->ref, nvmet_confirm_sq);
	रुको_क्रम_completion(&sq->confirm_करोne);
	रुको_क्रम_completion(&sq->मुक्त_करोne);
	percpu_ref_निकास(&sq->ref);

	अगर (ctrl) अणु
		/*
		 * The tearकरोwn flow may take some समय, and the host may not
		 * send us keep-alive during this period, hence reset the
		 * traffic based keep-alive समयr so we करोn't trigger a
		 * controller tearकरोwn as a result of a keep-alive expiration.
		 */
		ctrl->reset_tbkas = true;
		nvmet_ctrl_put(ctrl);
		sq->ctrl = शून्य; /* allows reusing the queue later */
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nvmet_sq_destroy);

अटल व्योम nvmet_sq_मुक्त(काष्ठा percpu_ref *ref)
अणु
	काष्ठा nvmet_sq *sq = container_of(ref, काष्ठा nvmet_sq, ref);

	complete(&sq->मुक्त_करोne);
पूर्ण

पूर्णांक nvmet_sq_init(काष्ठा nvmet_sq *sq)
अणु
	पूर्णांक ret;

	ret = percpu_ref_init(&sq->ref, nvmet_sq_मुक्त, 0, GFP_KERNEL);
	अगर (ret) अणु
		pr_err("percpu_ref init failed!\n");
		वापस ret;
	पूर्ण
	init_completion(&sq->मुक्त_करोne);
	init_completion(&sq->confirm_करोne);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nvmet_sq_init);

अटल अंतरभूत u16 nvmet_check_ana_state(काष्ठा nvmet_port *port,
		काष्ठा nvmet_ns *ns)
अणु
	क्रमागत nvme_ana_state state = port->ana_state[ns->anagrpid];

	अगर (unlikely(state == NVME_ANA_INACCESSIBLE))
		वापस NVME_SC_ANA_INACCESSIBLE;
	अगर (unlikely(state == NVME_ANA_PERSISTENT_LOSS))
		वापस NVME_SC_ANA_PERSISTENT_LOSS;
	अगर (unlikely(state == NVME_ANA_CHANGE))
		वापस NVME_SC_ANA_TRANSITION;
	वापस 0;
पूर्ण

अटल अंतरभूत u16 nvmet_io_cmd_check_access(काष्ठा nvmet_req *req)
अणु
	अगर (unlikely(req->ns->पढ़ोonly)) अणु
		चयन (req->cmd->common.opcode) अणु
		हाल nvme_cmd_पढ़ो:
		हाल nvme_cmd_flush:
			अवरोध;
		शेष:
			वापस NVME_SC_NS_WRITE_PROTECTED;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल u16 nvmet_parse_io_cmd(काष्ठा nvmet_req *req)
अणु
	u16 ret;

	ret = nvmet_check_ctrl_status(req);
	अगर (unlikely(ret))
		वापस ret;

	अगर (nvmet_req_passthru_ctrl(req))
		वापस nvmet_parse_passthru_io_cmd(req);

	ret = nvmet_req_find_ns(req);
	अगर (unlikely(ret))
		वापस ret;

	ret = nvmet_check_ana_state(req->port, req->ns);
	अगर (unlikely(ret)) अणु
		req->error_loc = दुरत्व(काष्ठा nvme_common_command, nsid);
		वापस ret;
	पूर्ण
	ret = nvmet_io_cmd_check_access(req);
	अगर (unlikely(ret)) अणु
		req->error_loc = दुरत्व(काष्ठा nvme_common_command, nsid);
		वापस ret;
	पूर्ण

	अगर (req->ns->file)
		वापस nvmet_file_parse_io_cmd(req);

	वापस nvmet_bdev_parse_io_cmd(req);
पूर्ण

bool nvmet_req_init(काष्ठा nvmet_req *req, काष्ठा nvmet_cq *cq,
		काष्ठा nvmet_sq *sq, स्थिर काष्ठा nvmet_fabrics_ops *ops)
अणु
	u8 flags = req->cmd->common.flags;
	u16 status;

	req->cq = cq;
	req->sq = sq;
	req->ops = ops;
	req->sg = शून्य;
	req->metadata_sg = शून्य;
	req->sg_cnt = 0;
	req->metadata_sg_cnt = 0;
	req->transfer_len = 0;
	req->metadata_len = 0;
	req->cqe->status = 0;
	req->cqe->sq_head = 0;
	req->ns = शून्य;
	req->error_loc = NVMET_NO_ERROR_LOC;
	req->error_slba = 0;

	/* no support क्रम fused commands yet */
	अगर (unlikely(flags & (NVME_CMD_FUSE_FIRST | NVME_CMD_FUSE_SECOND))) अणु
		req->error_loc = दुरत्व(काष्ठा nvme_common_command, flags);
		status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
		जाओ fail;
	पूर्ण

	/*
	 * For fabrics, PSDT field shall describe metadata poपूर्णांकer (MPTR) that
	 * contains an address of a single contiguous physical buffer that is
	 * byte aligned.
	 */
	अगर (unlikely((flags & NVME_CMD_SGL_ALL) != NVME_CMD_SGL_METABUF)) अणु
		req->error_loc = दुरत्व(काष्ठा nvme_common_command, flags);
		status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
		जाओ fail;
	पूर्ण

	अगर (unlikely(!req->sq->ctrl))
		/* will वापस an error क्रम any non-connect command: */
		status = nvmet_parse_connect_cmd(req);
	अन्यथा अगर (likely(req->sq->qid != 0))
		status = nvmet_parse_io_cmd(req);
	अन्यथा
		status = nvmet_parse_admin_cmd(req);

	अगर (status)
		जाओ fail;

	trace_nvmet_req_init(req, req->cmd);

	अगर (unlikely(!percpu_ref_tryget_live(&sq->ref))) अणु
		status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
		जाओ fail;
	पूर्ण

	अगर (sq->ctrl)
		sq->ctrl->reset_tbkas = true;

	वापस true;

fail:
	__nvmet_req_complete(req, status);
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(nvmet_req_init);

व्योम nvmet_req_uninit(काष्ठा nvmet_req *req)
अणु
	percpu_ref_put(&req->sq->ref);
	अगर (req->ns)
		nvmet_put_namespace(req->ns);
पूर्ण
EXPORT_SYMBOL_GPL(nvmet_req_uninit);

bool nvmet_check_transfer_len(काष्ठा nvmet_req *req, माप_प्रकार len)
अणु
	अगर (unlikely(len != req->transfer_len)) अणु
		req->error_loc = दुरत्व(काष्ठा nvme_common_command, dptr);
		nvmet_req_complete(req, NVME_SC_SGL_INVALID_DATA | NVME_SC_DNR);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(nvmet_check_transfer_len);

bool nvmet_check_data_len_lte(काष्ठा nvmet_req *req, माप_प्रकार data_len)
अणु
	अगर (unlikely(data_len > req->transfer_len)) अणु
		req->error_loc = दुरत्व(काष्ठा nvme_common_command, dptr);
		nvmet_req_complete(req, NVME_SC_SGL_INVALID_DATA | NVME_SC_DNR);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल अचिन्हित पूर्णांक nvmet_data_transfer_len(काष्ठा nvmet_req *req)
अणु
	वापस req->transfer_len - req->metadata_len;
पूर्ण

अटल पूर्णांक nvmet_req_alloc_p2pmem_sgls(काष्ठा pci_dev *p2p_dev,
		काष्ठा nvmet_req *req)
अणु
	req->sg = pci_p2pmem_alloc_sgl(p2p_dev, &req->sg_cnt,
			nvmet_data_transfer_len(req));
	अगर (!req->sg)
		जाओ out_err;

	अगर (req->metadata_len) अणु
		req->metadata_sg = pci_p2pmem_alloc_sgl(p2p_dev,
				&req->metadata_sg_cnt, req->metadata_len);
		अगर (!req->metadata_sg)
			जाओ out_मुक्त_sg;
	पूर्ण

	req->p2p_dev = p2p_dev;

	वापस 0;
out_मुक्त_sg:
	pci_p2pmem_मुक्त_sgl(req->p2p_dev, req->sg);
out_err:
	वापस -ENOMEM;
पूर्ण

अटल काष्ठा pci_dev *nvmet_req_find_p2p_dev(काष्ठा nvmet_req *req)
अणु
	अगर (!IS_ENABLED(CONFIG_PCI_P2PDMA) ||
	    !req->sq->ctrl || !req->sq->qid || !req->ns)
		वापस शून्य;
	वापस radix_tree_lookup(&req->sq->ctrl->p2p_ns_map, req->ns->nsid);
पूर्ण

पूर्णांक nvmet_req_alloc_sgls(काष्ठा nvmet_req *req)
अणु
	काष्ठा pci_dev *p2p_dev = nvmet_req_find_p2p_dev(req);

	अगर (p2p_dev && !nvmet_req_alloc_p2pmem_sgls(p2p_dev, req))
		वापस 0;

	req->sg = sgl_alloc(nvmet_data_transfer_len(req), GFP_KERNEL,
			    &req->sg_cnt);
	अगर (unlikely(!req->sg))
		जाओ out;

	अगर (req->metadata_len) अणु
		req->metadata_sg = sgl_alloc(req->metadata_len, GFP_KERNEL,
					     &req->metadata_sg_cnt);
		अगर (unlikely(!req->metadata_sg))
			जाओ out_मुक्त;
	पूर्ण

	वापस 0;
out_मुक्त:
	sgl_मुक्त(req->sg);
out:
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL_GPL(nvmet_req_alloc_sgls);

व्योम nvmet_req_मुक्त_sgls(काष्ठा nvmet_req *req)
अणु
	अगर (req->p2p_dev) अणु
		pci_p2pmem_मुक्त_sgl(req->p2p_dev, req->sg);
		अगर (req->metadata_sg)
			pci_p2pmem_मुक्त_sgl(req->p2p_dev, req->metadata_sg);
		req->p2p_dev = शून्य;
	पूर्ण अन्यथा अणु
		sgl_मुक्त(req->sg);
		अगर (req->metadata_sg)
			sgl_मुक्त(req->metadata_sg);
	पूर्ण

	req->sg = शून्य;
	req->metadata_sg = शून्य;
	req->sg_cnt = 0;
	req->metadata_sg_cnt = 0;
पूर्ण
EXPORT_SYMBOL_GPL(nvmet_req_मुक्त_sgls);

अटल अंतरभूत bool nvmet_cc_en(u32 cc)
अणु
	वापस (cc >> NVME_CC_EN_SHIFT) & 0x1;
पूर्ण

अटल अंतरभूत u8 nvmet_cc_css(u32 cc)
अणु
	वापस (cc >> NVME_CC_CSS_SHIFT) & 0x7;
पूर्ण

अटल अंतरभूत u8 nvmet_cc_mps(u32 cc)
अणु
	वापस (cc >> NVME_CC_MPS_SHIFT) & 0xf;
पूर्ण

अटल अंतरभूत u8 nvmet_cc_ams(u32 cc)
अणु
	वापस (cc >> NVME_CC_AMS_SHIFT) & 0x7;
पूर्ण

अटल अंतरभूत u8 nvmet_cc_shn(u32 cc)
अणु
	वापस (cc >> NVME_CC_SHN_SHIFT) & 0x3;
पूर्ण

अटल अंतरभूत u8 nvmet_cc_iosqes(u32 cc)
अणु
	वापस (cc >> NVME_CC_IOSQES_SHIFT) & 0xf;
पूर्ण

अटल अंतरभूत u8 nvmet_cc_iocqes(u32 cc)
अणु
	वापस (cc >> NVME_CC_IOCQES_SHIFT) & 0xf;
पूर्ण

अटल व्योम nvmet_start_ctrl(काष्ठा nvmet_ctrl *ctrl)
अणु
	lockdep_निश्चित_held(&ctrl->lock);

	/*
	 * Only I/O controllers should verअगरy iosqes,iocqes.
	 * Strictly speaking, the spec says a discovery controller
	 * should verअगरy iosqes,iocqes are zeroed, however that
	 * would अवरोध backwards compatibility, so करोn't enक्रमce it.
	 */
	अगर (ctrl->subsys->type != NVME_NQN_DISC &&
	    (nvmet_cc_iosqes(ctrl->cc) != NVME_NVM_IOSQES ||
	     nvmet_cc_iocqes(ctrl->cc) != NVME_NVM_IOCQES)) अणु
		ctrl->csts = NVME_CSTS_CFS;
		वापस;
	पूर्ण

	अगर (nvmet_cc_mps(ctrl->cc) != 0 ||
	    nvmet_cc_ams(ctrl->cc) != 0 ||
	    nvmet_cc_css(ctrl->cc) != 0) अणु
		ctrl->csts = NVME_CSTS_CFS;
		वापस;
	पूर्ण

	ctrl->csts = NVME_CSTS_RDY;

	/*
	 * Controllers that are not yet enabled should not really enक्रमce the
	 * keep alive समयout, but we still want to track a समयout and cleanup
	 * in हाल a host died beक्रमe it enabled the controller.  Hence, simply
	 * reset the keep alive समयr when the controller is enabled.
	 */
	अगर (ctrl->kato)
		mod_delayed_work(प्रणाली_wq, &ctrl->ka_work, ctrl->kato * HZ);
पूर्ण

अटल व्योम nvmet_clear_ctrl(काष्ठा nvmet_ctrl *ctrl)
अणु
	lockdep_निश्चित_held(&ctrl->lock);

	/* XXX: tear करोwn queues? */
	ctrl->csts &= ~NVME_CSTS_RDY;
	ctrl->cc = 0;
पूर्ण

व्योम nvmet_update_cc(काष्ठा nvmet_ctrl *ctrl, u32 new)
अणु
	u32 old;

	mutex_lock(&ctrl->lock);
	old = ctrl->cc;
	ctrl->cc = new;

	अगर (nvmet_cc_en(new) && !nvmet_cc_en(old))
		nvmet_start_ctrl(ctrl);
	अगर (!nvmet_cc_en(new) && nvmet_cc_en(old))
		nvmet_clear_ctrl(ctrl);
	अगर (nvmet_cc_shn(new) && !nvmet_cc_shn(old)) अणु
		nvmet_clear_ctrl(ctrl);
		ctrl->csts |= NVME_CSTS_SHST_CMPLT;
	पूर्ण
	अगर (!nvmet_cc_shn(new) && nvmet_cc_shn(old))
		ctrl->csts &= ~NVME_CSTS_SHST_CMPLT;
	mutex_unlock(&ctrl->lock);
पूर्ण

अटल व्योम nvmet_init_cap(काष्ठा nvmet_ctrl *ctrl)
अणु
	/* command sets supported: NVMe command set: */
	ctrl->cap = (1ULL << 37);
	/* CC.EN समयout in 500msec units: */
	ctrl->cap |= (15ULL << 24);
	/* maximum queue entries supported: */
	ctrl->cap |= NVMET_QUEUE_SIZE - 1;
पूर्ण

काष्ठा nvmet_ctrl *nvmet_ctrl_find_get(स्थिर अक्षर *subsysnqn,
				       स्थिर अक्षर *hostnqn, u16 cntlid,
				       काष्ठा nvmet_req *req)
अणु
	काष्ठा nvmet_ctrl *ctrl = शून्य;
	काष्ठा nvmet_subsys *subsys;

	subsys = nvmet_find_get_subsys(req->port, subsysnqn);
	अगर (!subsys) अणु
		pr_warn("connect request for invalid subsystem %s!\n",
			subsysnqn);
		req->cqe->result.u32 = IPO_IATTR_CONNECT_DATA(subsysnqn);
		जाओ out;
	पूर्ण

	mutex_lock(&subsys->lock);
	list_क्रम_each_entry(ctrl, &subsys->ctrls, subsys_entry) अणु
		अगर (ctrl->cntlid == cntlid) अणु
			अगर (म_भेदन(hostnqn, ctrl->hostnqn, NVMF_NQN_SIZE)) अणु
				pr_warn("hostnqn mismatch.\n");
				जारी;
			पूर्ण
			अगर (!kref_get_unless_zero(&ctrl->ref))
				जारी;

			/* ctrl found */
			जाओ found;
		पूर्ण
	पूर्ण

	ctrl = शून्य; /* ctrl not found */
	pr_warn("could not find controller %d for subsys %s / host %s\n",
		cntlid, subsysnqn, hostnqn);
	req->cqe->result.u32 = IPO_IATTR_CONNECT_DATA(cntlid);

found:
	mutex_unlock(&subsys->lock);
	nvmet_subsys_put(subsys);
out:
	वापस ctrl;
पूर्ण

u16 nvmet_check_ctrl_status(काष्ठा nvmet_req *req)
अणु
	अगर (unlikely(!(req->sq->ctrl->cc & NVME_CC_ENABLE))) अणु
		pr_err("got cmd %d while CC.EN == 0 on qid = %d\n",
		       req->cmd->common.opcode, req->sq->qid);
		वापस NVME_SC_CMD_SEQ_ERROR | NVME_SC_DNR;
	पूर्ण

	अगर (unlikely(!(req->sq->ctrl->csts & NVME_CSTS_RDY))) अणु
		pr_err("got cmd %d while CSTS.RDY == 0 on qid = %d\n",
		       req->cmd->common.opcode, req->sq->qid);
		वापस NVME_SC_CMD_SEQ_ERROR | NVME_SC_DNR;
	पूर्ण
	वापस 0;
पूर्ण

bool nvmet_host_allowed(काष्ठा nvmet_subsys *subsys, स्थिर अक्षर *hostnqn)
अणु
	काष्ठा nvmet_host_link *p;

	lockdep_निश्चित_held(&nvmet_config_sem);

	अगर (subsys->allow_any_host)
		वापस true;

	अगर (subsys->type == NVME_NQN_DISC) /* allow all access to disc subsys */
		वापस true;

	list_क्रम_each_entry(p, &subsys->hosts, entry) अणु
		अगर (!म_भेद(nvmet_host_name(p->host), hostnqn))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Note: ctrl->subsys->lock should be held when calling this function
 */
अटल व्योम nvmet_setup_p2p_ns_map(काष्ठा nvmet_ctrl *ctrl,
		काष्ठा nvmet_req *req)
अणु
	काष्ठा nvmet_ns *ns;
	अचिन्हित दीर्घ idx;

	अगर (!req->p2p_client)
		वापस;

	ctrl->p2p_client = get_device(req->p2p_client);

	xa_क्रम_each(&ctrl->subsys->namespaces, idx, ns)
		nvmet_p2pmem_ns_add_p2p(ctrl, ns);
पूर्ण

/*
 * Note: ctrl->subsys->lock should be held when calling this function
 */
अटल व्योम nvmet_release_p2p_ns_map(काष्ठा nvmet_ctrl *ctrl)
अणु
	काष्ठा radix_tree_iter iter;
	व्योम __rcu **slot;

	radix_tree_क्रम_each_slot(slot, &ctrl->p2p_ns_map, &iter, 0)
		pci_dev_put(radix_tree_deref_slot(slot));

	put_device(ctrl->p2p_client);
पूर्ण

अटल व्योम nvmet_fatal_error_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvmet_ctrl *ctrl =
			container_of(work, काष्ठा nvmet_ctrl, fatal_err_work);

	pr_err("ctrl %d fatal error occurred!\n", ctrl->cntlid);
	ctrl->ops->delete_ctrl(ctrl);
पूर्ण

u16 nvmet_alloc_ctrl(स्थिर अक्षर *subsysnqn, स्थिर अक्षर *hostnqn,
		काष्ठा nvmet_req *req, u32 kato, काष्ठा nvmet_ctrl **ctrlp)
अणु
	काष्ठा nvmet_subsys *subsys;
	काष्ठा nvmet_ctrl *ctrl;
	पूर्णांक ret;
	u16 status;

	status = NVME_SC_CONNECT_INVALID_PARAM | NVME_SC_DNR;
	subsys = nvmet_find_get_subsys(req->port, subsysnqn);
	अगर (!subsys) अणु
		pr_warn("connect request for invalid subsystem %s!\n",
			subsysnqn);
		req->cqe->result.u32 = IPO_IATTR_CONNECT_DATA(subsysnqn);
		req->error_loc = दुरत्व(काष्ठा nvme_common_command, dptr);
		जाओ out;
	पूर्ण

	करोwn_पढ़ो(&nvmet_config_sem);
	अगर (!nvmet_host_allowed(subsys, hostnqn)) अणु
		pr_info("connect by host %s for subsystem %s not allowed\n",
			hostnqn, subsysnqn);
		req->cqe->result.u32 = IPO_IATTR_CONNECT_DATA(hostnqn);
		up_पढ़ो(&nvmet_config_sem);
		status = NVME_SC_CONNECT_INVALID_HOST | NVME_SC_DNR;
		req->error_loc = दुरत्व(काष्ठा nvme_common_command, dptr);
		जाओ out_put_subप्रणाली;
	पूर्ण
	up_पढ़ो(&nvmet_config_sem);

	status = NVME_SC_INTERNAL;
	ctrl = kzalloc(माप(*ctrl), GFP_KERNEL);
	अगर (!ctrl)
		जाओ out_put_subप्रणाली;
	mutex_init(&ctrl->lock);

	nvmet_init_cap(ctrl);

	ctrl->port = req->port;

	INIT_WORK(&ctrl->async_event_work, nvmet_async_event_work);
	INIT_LIST_HEAD(&ctrl->async_events);
	INIT_RADIX_TREE(&ctrl->p2p_ns_map, GFP_KERNEL);
	INIT_WORK(&ctrl->fatal_err_work, nvmet_fatal_error_handler);

	स_नकल(ctrl->subsysnqn, subsysnqn, NVMF_NQN_SIZE);
	स_नकल(ctrl->hostnqn, hostnqn, NVMF_NQN_SIZE);

	kref_init(&ctrl->ref);
	ctrl->subsys = subsys;
	WRITE_ONCE(ctrl->aen_enabled, NVMET_AEN_CFG_OPTIONAL);

	ctrl->changed_ns_list = kदो_स्मृति_array(NVME_MAX_CHANGED_NAMESPACES,
			माप(__le32), GFP_KERNEL);
	अगर (!ctrl->changed_ns_list)
		जाओ out_मुक्त_ctrl;

	ctrl->sqs = kसुस्मृति(subsys->max_qid + 1,
			माप(काष्ठा nvmet_sq *),
			GFP_KERNEL);
	अगर (!ctrl->sqs)
		जाओ out_मुक्त_changed_ns_list;

	अगर (subsys->cntlid_min > subsys->cntlid_max)
		जाओ out_मुक्त_sqs;

	ret = ida_simple_get(&cntlid_ida,
			     subsys->cntlid_min, subsys->cntlid_max,
			     GFP_KERNEL);
	अगर (ret < 0) अणु
		status = NVME_SC_CONNECT_CTRL_BUSY | NVME_SC_DNR;
		जाओ out_मुक्त_sqs;
	पूर्ण
	ctrl->cntlid = ret;

	ctrl->ops = req->ops;

	/*
	 * Discovery controllers may use some arbitrary high value
	 * in order to cleanup stale discovery sessions
	 */
	अगर ((ctrl->subsys->type == NVME_NQN_DISC) && !kato)
		kato = NVMET_DISC_KATO_MS;

	/* keep-alive समयout in seconds */
	ctrl->kato = DIV_ROUND_UP(kato, 1000);

	ctrl->err_counter = 0;
	spin_lock_init(&ctrl->error_lock);

	nvmet_start_keep_alive_समयr(ctrl);

	mutex_lock(&subsys->lock);
	list_add_tail(&ctrl->subsys_entry, &subsys->ctrls);
	nvmet_setup_p2p_ns_map(ctrl, req);
	mutex_unlock(&subsys->lock);

	*ctrlp = ctrl;
	वापस 0;

out_मुक्त_sqs:
	kमुक्त(ctrl->sqs);
out_मुक्त_changed_ns_list:
	kमुक्त(ctrl->changed_ns_list);
out_मुक्त_ctrl:
	kमुक्त(ctrl);
out_put_subप्रणाली:
	nvmet_subsys_put(subsys);
out:
	वापस status;
पूर्ण

अटल व्योम nvmet_ctrl_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा nvmet_ctrl *ctrl = container_of(ref, काष्ठा nvmet_ctrl, ref);
	काष्ठा nvmet_subsys *subsys = ctrl->subsys;

	mutex_lock(&subsys->lock);
	nvmet_release_p2p_ns_map(ctrl);
	list_del(&ctrl->subsys_entry);
	mutex_unlock(&subsys->lock);

	nvmet_stop_keep_alive_समयr(ctrl);

	flush_work(&ctrl->async_event_work);
	cancel_work_sync(&ctrl->fatal_err_work);

	ida_simple_हटाओ(&cntlid_ida, ctrl->cntlid);

	nvmet_async_events_मुक्त(ctrl);
	kमुक्त(ctrl->sqs);
	kमुक्त(ctrl->changed_ns_list);
	kमुक्त(ctrl);

	nvmet_subsys_put(subsys);
पूर्ण

व्योम nvmet_ctrl_put(काष्ठा nvmet_ctrl *ctrl)
अणु
	kref_put(&ctrl->ref, nvmet_ctrl_मुक्त);
पूर्ण

व्योम nvmet_ctrl_fatal_error(काष्ठा nvmet_ctrl *ctrl)
अणु
	mutex_lock(&ctrl->lock);
	अगर (!(ctrl->csts & NVME_CSTS_CFS)) अणु
		ctrl->csts |= NVME_CSTS_CFS;
		schedule_work(&ctrl->fatal_err_work);
	पूर्ण
	mutex_unlock(&ctrl->lock);
पूर्ण
EXPORT_SYMBOL_GPL(nvmet_ctrl_fatal_error);

अटल काष्ठा nvmet_subsys *nvmet_find_get_subsys(काष्ठा nvmet_port *port,
		स्थिर अक्षर *subsysnqn)
अणु
	काष्ठा nvmet_subsys_link *p;

	अगर (!port)
		वापस शून्य;

	अगर (!म_भेद(NVME_DISC_SUBSYS_NAME, subsysnqn)) अणु
		अगर (!kref_get_unless_zero(&nvmet_disc_subsys->ref))
			वापस शून्य;
		वापस nvmet_disc_subsys;
	पूर्ण

	करोwn_पढ़ो(&nvmet_config_sem);
	list_क्रम_each_entry(p, &port->subप्रणालीs, entry) अणु
		अगर (!म_भेदन(p->subsys->subsysnqn, subsysnqn,
				NVMF_NQN_SIZE)) अणु
			अगर (!kref_get_unless_zero(&p->subsys->ref))
				अवरोध;
			up_पढ़ो(&nvmet_config_sem);
			वापस p->subsys;
		पूर्ण
	पूर्ण
	up_पढ़ो(&nvmet_config_sem);
	वापस शून्य;
पूर्ण

काष्ठा nvmet_subsys *nvmet_subsys_alloc(स्थिर अक्षर *subsysnqn,
		क्रमागत nvme_subsys_type type)
अणु
	काष्ठा nvmet_subsys *subsys;

	subsys = kzalloc(माप(*subsys), GFP_KERNEL);
	अगर (!subsys)
		वापस ERR_PTR(-ENOMEM);

	subsys->ver = NVMET_DEFAULT_VS;
	/* generate a अक्रमom serial number as our controllers are ephemeral: */
	get_अक्रमom_bytes(&subsys->serial, माप(subsys->serial));

	चयन (type) अणु
	हाल NVME_NQN_NVME:
		subsys->max_qid = NVMET_NR_QUEUES;
		अवरोध;
	हाल NVME_NQN_DISC:
		subsys->max_qid = 0;
		अवरोध;
	शेष:
		pr_err("%s: Unknown Subsystem type - %d\n", __func__, type);
		kमुक्त(subsys);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	subsys->type = type;
	subsys->subsysnqn = kstrndup(subsysnqn, NVMF_NQN_SIZE,
			GFP_KERNEL);
	अगर (!subsys->subsysnqn) अणु
		kमुक्त(subsys);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	subsys->cntlid_min = NVME_CNTLID_MIN;
	subsys->cntlid_max = NVME_CNTLID_MAX;
	kref_init(&subsys->ref);

	mutex_init(&subsys->lock);
	xa_init(&subsys->namespaces);
	INIT_LIST_HEAD(&subsys->ctrls);
	INIT_LIST_HEAD(&subsys->hosts);

	वापस subsys;
पूर्ण

अटल व्योम nvmet_subsys_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा nvmet_subsys *subsys =
		container_of(ref, काष्ठा nvmet_subsys, ref);

	WARN_ON_ONCE(!xa_empty(&subsys->namespaces));

	xa_destroy(&subsys->namespaces);
	nvmet_passthru_subsys_मुक्त(subsys);

	kमुक्त(subsys->subsysnqn);
	kमुक्त(subsys->model_number);
	kमुक्त(subsys);
पूर्ण

व्योम nvmet_subsys_del_ctrls(काष्ठा nvmet_subsys *subsys)
अणु
	काष्ठा nvmet_ctrl *ctrl;

	mutex_lock(&subsys->lock);
	list_क्रम_each_entry(ctrl, &subsys->ctrls, subsys_entry)
		ctrl->ops->delete_ctrl(ctrl);
	mutex_unlock(&subsys->lock);
पूर्ण

व्योम nvmet_subsys_put(काष्ठा nvmet_subsys *subsys)
अणु
	kref_put(&subsys->ref, nvmet_subsys_मुक्त);
पूर्ण

अटल पूर्णांक __init nvmet_init(व्योम)
अणु
	पूर्णांक error;

	nvmet_ana_group_enabled[NVMET_DEFAULT_ANA_GRPID] = 1;

	buffered_io_wq = alloc_workqueue("nvmet-buffered-io-wq",
			WQ_MEM_RECLAIM, 0);
	अगर (!buffered_io_wq) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण

	error = nvmet_init_discovery();
	अगर (error)
		जाओ out_मुक्त_work_queue;

	error = nvmet_init_configfs();
	अगर (error)
		जाओ out_निकास_discovery;
	वापस 0;

out_निकास_discovery:
	nvmet_निकास_discovery();
out_मुक्त_work_queue:
	destroy_workqueue(buffered_io_wq);
out:
	वापस error;
पूर्ण

अटल व्योम __निकास nvmet_निकास(व्योम)
अणु
	nvmet_निकास_configfs();
	nvmet_निकास_discovery();
	ida_destroy(&cntlid_ida);
	destroy_workqueue(buffered_io_wq);

	BUILD_BUG_ON(माप(काष्ठा nvmf_disc_rsp_page_entry) != 1024);
	BUILD_BUG_ON(माप(काष्ठा nvmf_disc_rsp_page_hdr) != 1024);
पूर्ण

module_init(nvmet_init);
module_निकास(nvmet_निकास);

MODULE_LICENSE("GPL v2");
