<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NVMe over Fabrics loopback device.
 * Copyright (c) 2015-2016 HGST, a Western Digital Company.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/scatterlist.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/nvme.h>
#समावेश <linux/module.h>
#समावेश <linux/parser.h>
#समावेश "nvmet.h"
#समावेश "../host/nvme.h"
#समावेश "../host/fabrics.h"

#घोषणा NVME_LOOP_MAX_SEGMENTS		256

काष्ठा nvme_loop_iod अणु
	काष्ठा nvme_request	nvme_req;
	काष्ठा nvme_command	cmd;
	काष्ठा nvme_completion	cqe;
	काष्ठा nvmet_req	req;
	काष्ठा nvme_loop_queue	*queue;
	काष्ठा work_काष्ठा	work;
	काष्ठा sg_table		sg_table;
	काष्ठा scatterlist	first_sgl[];
पूर्ण;

काष्ठा nvme_loop_ctrl अणु
	काष्ठा nvme_loop_queue	*queues;

	काष्ठा blk_mq_tag_set	admin_tag_set;

	काष्ठा list_head	list;
	काष्ठा blk_mq_tag_set	tag_set;
	काष्ठा nvme_loop_iod	async_event_iod;
	काष्ठा nvme_ctrl	ctrl;

	काष्ठा nvmet_port	*port;
पूर्ण;

अटल अंतरभूत काष्ठा nvme_loop_ctrl *to_loop_ctrl(काष्ठा nvme_ctrl *ctrl)
अणु
	वापस container_of(ctrl, काष्ठा nvme_loop_ctrl, ctrl);
पूर्ण

क्रमागत nvme_loop_queue_flags अणु
	NVME_LOOP_Q_LIVE	= 0,
पूर्ण;

काष्ठा nvme_loop_queue अणु
	काष्ठा nvmet_cq		nvme_cq;
	काष्ठा nvmet_sq		nvme_sq;
	काष्ठा nvme_loop_ctrl	*ctrl;
	अचिन्हित दीर्घ		flags;
पूर्ण;

अटल LIST_HEAD(nvme_loop_ports);
अटल DEFINE_MUTEX(nvme_loop_ports_mutex);

अटल LIST_HEAD(nvme_loop_ctrl_list);
अटल DEFINE_MUTEX(nvme_loop_ctrl_mutex);

अटल व्योम nvme_loop_queue_response(काष्ठा nvmet_req *nvme_req);
अटल व्योम nvme_loop_delete_ctrl(काष्ठा nvmet_ctrl *ctrl);

अटल स्थिर काष्ठा nvmet_fabrics_ops nvme_loop_ops;

अटल अंतरभूत पूर्णांक nvme_loop_queue_idx(काष्ठा nvme_loop_queue *queue)
अणु
	वापस queue - queue->ctrl->queues;
पूर्ण

अटल व्योम nvme_loop_complete_rq(काष्ठा request *req)
अणु
	काष्ठा nvme_loop_iod *iod = blk_mq_rq_to_pdu(req);

	sg_मुक्त_table_chained(&iod->sg_table, NVME_INLINE_SG_CNT);
	nvme_complete_rq(req);
पूर्ण

अटल काष्ठा blk_mq_tags *nvme_loop_tagset(काष्ठा nvme_loop_queue *queue)
अणु
	u32 queue_idx = nvme_loop_queue_idx(queue);

	अगर (queue_idx == 0)
		वापस queue->ctrl->admin_tag_set.tags[queue_idx];
	वापस queue->ctrl->tag_set.tags[queue_idx - 1];
पूर्ण

अटल व्योम nvme_loop_queue_response(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvme_loop_queue *queue =
		container_of(req->sq, काष्ठा nvme_loop_queue, nvme_sq);
	काष्ठा nvme_completion *cqe = req->cqe;

	/*
	 * AEN requests are special as they करोn't समय out and can
	 * survive any kind of queue मुक्तze and often करोn't respond to
	 * पातs.  We करोn't even bother to allocate a काष्ठा request
	 * क्रम them but rather special हाल them here.
	 */
	अगर (unlikely(nvme_is_aen_req(nvme_loop_queue_idx(queue),
				     cqe->command_id))) अणु
		nvme_complete_async_event(&queue->ctrl->ctrl, cqe->status,
				&cqe->result);
	पूर्ण अन्यथा अणु
		काष्ठा request *rq;

		rq = blk_mq_tag_to_rq(nvme_loop_tagset(queue), cqe->command_id);
		अगर (!rq) अणु
			dev_err(queue->ctrl->ctrl.device,
				"tag 0x%x on queue %d not found\n",
				cqe->command_id, nvme_loop_queue_idx(queue));
			वापस;
		पूर्ण

		अगर (!nvme_try_complete_req(rq, cqe->status, cqe->result))
			nvme_loop_complete_rq(rq);
	पूर्ण
पूर्ण

अटल व्योम nvme_loop_execute_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvme_loop_iod *iod =
		container_of(work, काष्ठा nvme_loop_iod, work);

	iod->req.execute(&iod->req);
पूर्ण

अटल blk_status_t nvme_loop_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
		स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा nvme_ns *ns = hctx->queue->queuedata;
	काष्ठा nvme_loop_queue *queue = hctx->driver_data;
	काष्ठा request *req = bd->rq;
	काष्ठा nvme_loop_iod *iod = blk_mq_rq_to_pdu(req);
	bool queue_पढ़ोy = test_bit(NVME_LOOP_Q_LIVE, &queue->flags);
	blk_status_t ret;

	अगर (!nvme_check_पढ़ोy(&queue->ctrl->ctrl, req, queue_पढ़ोy))
		वापस nvme_fail_nonपढ़ोy_command(&queue->ctrl->ctrl, req);

	ret = nvme_setup_cmd(ns, req);
	अगर (ret)
		वापस ret;

	blk_mq_start_request(req);
	iod->cmd.common.flags |= NVME_CMD_SGL_METABUF;
	iod->req.port = queue->ctrl->port;
	अगर (!nvmet_req_init(&iod->req, &queue->nvme_cq,
			&queue->nvme_sq, &nvme_loop_ops))
		वापस BLK_STS_OK;

	अगर (blk_rq_nr_phys_segments(req)) अणु
		iod->sg_table.sgl = iod->first_sgl;
		अगर (sg_alloc_table_chained(&iod->sg_table,
				blk_rq_nr_phys_segments(req),
				iod->sg_table.sgl, NVME_INLINE_SG_CNT)) अणु
			nvme_cleanup_cmd(req);
			वापस BLK_STS_RESOURCE;
		पूर्ण

		iod->req.sg = iod->sg_table.sgl;
		iod->req.sg_cnt = blk_rq_map_sg(req->q, req, iod->sg_table.sgl);
		iod->req.transfer_len = blk_rq_payload_bytes(req);
	पूर्ण

	schedule_work(&iod->work);
	वापस BLK_STS_OK;
पूर्ण

अटल व्योम nvme_loop_submit_async_event(काष्ठा nvme_ctrl *arg)
अणु
	काष्ठा nvme_loop_ctrl *ctrl = to_loop_ctrl(arg);
	काष्ठा nvme_loop_queue *queue = &ctrl->queues[0];
	काष्ठा nvme_loop_iod *iod = &ctrl->async_event_iod;

	स_रखो(&iod->cmd, 0, माप(iod->cmd));
	iod->cmd.common.opcode = nvme_admin_async_event;
	iod->cmd.common.command_id = NVME_AQ_BLK_MQ_DEPTH;
	iod->cmd.common.flags |= NVME_CMD_SGL_METABUF;

	अगर (!nvmet_req_init(&iod->req, &queue->nvme_cq, &queue->nvme_sq,
			&nvme_loop_ops)) अणु
		dev_err(ctrl->ctrl.device, "failed async event work\n");
		वापस;
	पूर्ण

	schedule_work(&iod->work);
पूर्ण

अटल पूर्णांक nvme_loop_init_iod(काष्ठा nvme_loop_ctrl *ctrl,
		काष्ठा nvme_loop_iod *iod, अचिन्हित पूर्णांक queue_idx)
अणु
	iod->req.cmd = &iod->cmd;
	iod->req.cqe = &iod->cqe;
	iod->queue = &ctrl->queues[queue_idx];
	INIT_WORK(&iod->work, nvme_loop_execute_work);
	वापस 0;
पूर्ण

अटल पूर्णांक nvme_loop_init_request(काष्ठा blk_mq_tag_set *set,
		काष्ठा request *req, अचिन्हित पूर्णांक hctx_idx,
		अचिन्हित पूर्णांक numa_node)
अणु
	काष्ठा nvme_loop_ctrl *ctrl = set->driver_data;
	काष्ठा nvme_loop_iod *iod = blk_mq_rq_to_pdu(req);

	nvme_req(req)->ctrl = &ctrl->ctrl;
	nvme_req(req)->cmd = &iod->cmd;
	वापस nvme_loop_init_iod(ctrl, blk_mq_rq_to_pdu(req),
			(set == &ctrl->tag_set) ? hctx_idx + 1 : 0);
पूर्ण

अटल काष्ठा lock_class_key loop_hctx_fq_lock_key;

अटल पूर्णांक nvme_loop_init_hctx(काष्ठा blk_mq_hw_ctx *hctx, व्योम *data,
		अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा nvme_loop_ctrl *ctrl = data;
	काष्ठा nvme_loop_queue *queue = &ctrl->queues[hctx_idx + 1];

	BUG_ON(hctx_idx >= ctrl->ctrl.queue_count);

	/*
	 * flush_end_io() can be called recursively क्रम us, so use our own
	 * lock class key क्रम aव्योमing lockdep possible recursive locking,
	 * then we can हटाओ the dynamically allocated lock class क्रम each
	 * flush queue, that way may cause horrible boot delay.
	 */
	blk_mq_hctx_set_fq_lock_class(hctx, &loop_hctx_fq_lock_key);

	hctx->driver_data = queue;
	वापस 0;
पूर्ण

अटल पूर्णांक nvme_loop_init_admin_hctx(काष्ठा blk_mq_hw_ctx *hctx, व्योम *data,
		अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा nvme_loop_ctrl *ctrl = data;
	काष्ठा nvme_loop_queue *queue = &ctrl->queues[0];

	BUG_ON(hctx_idx != 0);

	hctx->driver_data = queue;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा blk_mq_ops nvme_loop_mq_ops = अणु
	.queue_rq	= nvme_loop_queue_rq,
	.complete	= nvme_loop_complete_rq,
	.init_request	= nvme_loop_init_request,
	.init_hctx	= nvme_loop_init_hctx,
पूर्ण;

अटल स्थिर काष्ठा blk_mq_ops nvme_loop_admin_mq_ops = अणु
	.queue_rq	= nvme_loop_queue_rq,
	.complete	= nvme_loop_complete_rq,
	.init_request	= nvme_loop_init_request,
	.init_hctx	= nvme_loop_init_admin_hctx,
पूर्ण;

अटल व्योम nvme_loop_destroy_admin_queue(काष्ठा nvme_loop_ctrl *ctrl)
अणु
	अगर (!test_and_clear_bit(NVME_LOOP_Q_LIVE, &ctrl->queues[0].flags))
		वापस;
	nvmet_sq_destroy(&ctrl->queues[0].nvme_sq);
	blk_cleanup_queue(ctrl->ctrl.admin_q);
	blk_cleanup_queue(ctrl->ctrl.fabrics_q);
	blk_mq_मुक्त_tag_set(&ctrl->admin_tag_set);
पूर्ण

अटल व्योम nvme_loop_मुक्त_ctrl(काष्ठा nvme_ctrl *nctrl)
अणु
	काष्ठा nvme_loop_ctrl *ctrl = to_loop_ctrl(nctrl);

	अगर (list_empty(&ctrl->list))
		जाओ मुक्त_ctrl;

	mutex_lock(&nvme_loop_ctrl_mutex);
	list_del(&ctrl->list);
	mutex_unlock(&nvme_loop_ctrl_mutex);

	अगर (nctrl->tagset) अणु
		blk_cleanup_queue(ctrl->ctrl.connect_q);
		blk_mq_मुक्त_tag_set(&ctrl->tag_set);
	पूर्ण
	kमुक्त(ctrl->queues);
	nvmf_मुक्त_options(nctrl->opts);
मुक्त_ctrl:
	kमुक्त(ctrl);
पूर्ण

अटल व्योम nvme_loop_destroy_io_queues(काष्ठा nvme_loop_ctrl *ctrl)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < ctrl->ctrl.queue_count; i++) अणु
		clear_bit(NVME_LOOP_Q_LIVE, &ctrl->queues[i].flags);
		nvmet_sq_destroy(&ctrl->queues[i].nvme_sq);
	पूर्ण
	ctrl->ctrl.queue_count = 1;
पूर्ण

अटल पूर्णांक nvme_loop_init_io_queues(काष्ठा nvme_loop_ctrl *ctrl)
अणु
	काष्ठा nvmf_ctrl_options *opts = ctrl->ctrl.opts;
	अचिन्हित पूर्णांक nr_io_queues;
	पूर्णांक ret, i;

	nr_io_queues = min(opts->nr_io_queues, num_online_cpus());
	ret = nvme_set_queue_count(&ctrl->ctrl, &nr_io_queues);
	अगर (ret || !nr_io_queues)
		वापस ret;

	dev_info(ctrl->ctrl.device, "creating %d I/O queues.\n", nr_io_queues);

	क्रम (i = 1; i <= nr_io_queues; i++) अणु
		ctrl->queues[i].ctrl = ctrl;
		ret = nvmet_sq_init(&ctrl->queues[i].nvme_sq);
		अगर (ret)
			जाओ out_destroy_queues;

		ctrl->ctrl.queue_count++;
	पूर्ण

	वापस 0;

out_destroy_queues:
	nvme_loop_destroy_io_queues(ctrl);
	वापस ret;
पूर्ण

अटल पूर्णांक nvme_loop_connect_io_queues(काष्ठा nvme_loop_ctrl *ctrl)
अणु
	पूर्णांक i, ret;

	क्रम (i = 1; i < ctrl->ctrl.queue_count; i++) अणु
		ret = nvmf_connect_io_queue(&ctrl->ctrl, i, false);
		अगर (ret)
			वापस ret;
		set_bit(NVME_LOOP_Q_LIVE, &ctrl->queues[i].flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nvme_loop_configure_admin_queue(काष्ठा nvme_loop_ctrl *ctrl)
अणु
	पूर्णांक error;

	स_रखो(&ctrl->admin_tag_set, 0, माप(ctrl->admin_tag_set));
	ctrl->admin_tag_set.ops = &nvme_loop_admin_mq_ops;
	ctrl->admin_tag_set.queue_depth = NVME_AQ_MQ_TAG_DEPTH;
	ctrl->admin_tag_set.reserved_tags = NVMF_RESERVED_TAGS;
	ctrl->admin_tag_set.numa_node = ctrl->ctrl.numa_node;
	ctrl->admin_tag_set.cmd_size = माप(काष्ठा nvme_loop_iod) +
		NVME_INLINE_SG_CNT * माप(काष्ठा scatterlist);
	ctrl->admin_tag_set.driver_data = ctrl;
	ctrl->admin_tag_set.nr_hw_queues = 1;
	ctrl->admin_tag_set.समयout = NVME_ADMIN_TIMEOUT;
	ctrl->admin_tag_set.flags = BLK_MQ_F_NO_SCHED;

	ctrl->queues[0].ctrl = ctrl;
	error = nvmet_sq_init(&ctrl->queues[0].nvme_sq);
	अगर (error)
		वापस error;
	ctrl->ctrl.queue_count = 1;

	error = blk_mq_alloc_tag_set(&ctrl->admin_tag_set);
	अगर (error)
		जाओ out_मुक्त_sq;
	ctrl->ctrl.admin_tagset = &ctrl->admin_tag_set;

	ctrl->ctrl.fabrics_q = blk_mq_init_queue(&ctrl->admin_tag_set);
	अगर (IS_ERR(ctrl->ctrl.fabrics_q)) अणु
		error = PTR_ERR(ctrl->ctrl.fabrics_q);
		जाओ out_मुक्त_tagset;
	पूर्ण

	ctrl->ctrl.admin_q = blk_mq_init_queue(&ctrl->admin_tag_set);
	अगर (IS_ERR(ctrl->ctrl.admin_q)) अणु
		error = PTR_ERR(ctrl->ctrl.admin_q);
		जाओ out_cleanup_fabrics_q;
	पूर्ण

	error = nvmf_connect_admin_queue(&ctrl->ctrl);
	अगर (error)
		जाओ out_cleanup_queue;

	set_bit(NVME_LOOP_Q_LIVE, &ctrl->queues[0].flags);

	error = nvme_enable_ctrl(&ctrl->ctrl);
	अगर (error)
		जाओ out_cleanup_queue;

	ctrl->ctrl.max_hw_sectors =
		(NVME_LOOP_MAX_SEGMENTS - 1) << (PAGE_SHIFT - 9);

	blk_mq_unquiesce_queue(ctrl->ctrl.admin_q);

	error = nvme_init_ctrl_finish(&ctrl->ctrl);
	अगर (error)
		जाओ out_cleanup_queue;

	वापस 0;

out_cleanup_queue:
	clear_bit(NVME_LOOP_Q_LIVE, &ctrl->queues[0].flags);
	blk_cleanup_queue(ctrl->ctrl.admin_q);
out_cleanup_fabrics_q:
	blk_cleanup_queue(ctrl->ctrl.fabrics_q);
out_मुक्त_tagset:
	blk_mq_मुक्त_tag_set(&ctrl->admin_tag_set);
out_मुक्त_sq:
	nvmet_sq_destroy(&ctrl->queues[0].nvme_sq);
	वापस error;
पूर्ण

अटल व्योम nvme_loop_shutकरोwn_ctrl(काष्ठा nvme_loop_ctrl *ctrl)
अणु
	अगर (ctrl->ctrl.queue_count > 1) अणु
		nvme_stop_queues(&ctrl->ctrl);
		blk_mq_tagset_busy_iter(&ctrl->tag_set,
					nvme_cancel_request, &ctrl->ctrl);
		blk_mq_tagset_रुको_completed_request(&ctrl->tag_set);
		nvme_loop_destroy_io_queues(ctrl);
	पूर्ण

	blk_mq_quiesce_queue(ctrl->ctrl.admin_q);
	अगर (ctrl->ctrl.state == NVME_CTRL_LIVE)
		nvme_shutकरोwn_ctrl(&ctrl->ctrl);

	blk_mq_tagset_busy_iter(&ctrl->admin_tag_set,
				nvme_cancel_request, &ctrl->ctrl);
	blk_mq_tagset_रुको_completed_request(&ctrl->admin_tag_set);
	nvme_loop_destroy_admin_queue(ctrl);
पूर्ण

अटल व्योम nvme_loop_delete_ctrl_host(काष्ठा nvme_ctrl *ctrl)
अणु
	nvme_loop_shutकरोwn_ctrl(to_loop_ctrl(ctrl));
पूर्ण

अटल व्योम nvme_loop_delete_ctrl(काष्ठा nvmet_ctrl *nctrl)
अणु
	काष्ठा nvme_loop_ctrl *ctrl;

	mutex_lock(&nvme_loop_ctrl_mutex);
	list_क्रम_each_entry(ctrl, &nvme_loop_ctrl_list, list) अणु
		अगर (ctrl->ctrl.cntlid == nctrl->cntlid)
			nvme_delete_ctrl(&ctrl->ctrl);
	पूर्ण
	mutex_unlock(&nvme_loop_ctrl_mutex);
पूर्ण

अटल व्योम nvme_loop_reset_ctrl_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvme_loop_ctrl *ctrl =
		container_of(work, काष्ठा nvme_loop_ctrl, ctrl.reset_work);
	पूर्णांक ret;

	nvme_stop_ctrl(&ctrl->ctrl);
	nvme_loop_shutकरोwn_ctrl(ctrl);

	अगर (!nvme_change_ctrl_state(&ctrl->ctrl, NVME_CTRL_CONNECTING)) अणु
		अगर (ctrl->ctrl.state != NVME_CTRL_DELETING &&
		    ctrl->ctrl.state != NVME_CTRL_DELETING_NOIO)
			/* state change failure क्रम non-deleted ctrl? */
			WARN_ON_ONCE(1);
		वापस;
	पूर्ण

	ret = nvme_loop_configure_admin_queue(ctrl);
	अगर (ret)
		जाओ out_disable;

	ret = nvme_loop_init_io_queues(ctrl);
	अगर (ret)
		जाओ out_destroy_admin;

	ret = nvme_loop_connect_io_queues(ctrl);
	अगर (ret)
		जाओ out_destroy_io;

	blk_mq_update_nr_hw_queues(&ctrl->tag_set,
			ctrl->ctrl.queue_count - 1);

	अगर (!nvme_change_ctrl_state(&ctrl->ctrl, NVME_CTRL_LIVE))
		WARN_ON_ONCE(1);

	nvme_start_ctrl(&ctrl->ctrl);

	वापस;

out_destroy_io:
	nvme_loop_destroy_io_queues(ctrl);
out_destroy_admin:
	nvme_loop_destroy_admin_queue(ctrl);
out_disable:
	dev_warn(ctrl->ctrl.device, "Removing after reset failure\n");
	nvme_uninit_ctrl(&ctrl->ctrl);
पूर्ण

अटल स्थिर काष्ठा nvme_ctrl_ops nvme_loop_ctrl_ops = अणु
	.name			= "loop",
	.module			= THIS_MODULE,
	.flags			= NVME_F_FABRICS,
	.reg_पढ़ो32		= nvmf_reg_पढ़ो32,
	.reg_पढ़ो64		= nvmf_reg_पढ़ो64,
	.reg_ग_लिखो32		= nvmf_reg_ग_लिखो32,
	.मुक्त_ctrl		= nvme_loop_मुक्त_ctrl,
	.submit_async_event	= nvme_loop_submit_async_event,
	.delete_ctrl		= nvme_loop_delete_ctrl_host,
	.get_address		= nvmf_get_address,
पूर्ण;

अटल पूर्णांक nvme_loop_create_io_queues(काष्ठा nvme_loop_ctrl *ctrl)
अणु
	पूर्णांक ret;

	ret = nvme_loop_init_io_queues(ctrl);
	अगर (ret)
		वापस ret;

	स_रखो(&ctrl->tag_set, 0, माप(ctrl->tag_set));
	ctrl->tag_set.ops = &nvme_loop_mq_ops;
	ctrl->tag_set.queue_depth = ctrl->ctrl.opts->queue_size;
	ctrl->tag_set.reserved_tags = NVMF_RESERVED_TAGS;
	ctrl->tag_set.numa_node = ctrl->ctrl.numa_node;
	ctrl->tag_set.flags = BLK_MQ_F_SHOULD_MERGE;
	ctrl->tag_set.cmd_size = माप(काष्ठा nvme_loop_iod) +
		NVME_INLINE_SG_CNT * माप(काष्ठा scatterlist);
	ctrl->tag_set.driver_data = ctrl;
	ctrl->tag_set.nr_hw_queues = ctrl->ctrl.queue_count - 1;
	ctrl->tag_set.समयout = NVME_IO_TIMEOUT;
	ctrl->ctrl.tagset = &ctrl->tag_set;

	ret = blk_mq_alloc_tag_set(&ctrl->tag_set);
	अगर (ret)
		जाओ out_destroy_queues;

	ctrl->ctrl.connect_q = blk_mq_init_queue(&ctrl->tag_set);
	अगर (IS_ERR(ctrl->ctrl.connect_q)) अणु
		ret = PTR_ERR(ctrl->ctrl.connect_q);
		जाओ out_मुक्त_tagset;
	पूर्ण

	ret = nvme_loop_connect_io_queues(ctrl);
	अगर (ret)
		जाओ out_cleanup_connect_q;

	वापस 0;

out_cleanup_connect_q:
	blk_cleanup_queue(ctrl->ctrl.connect_q);
out_मुक्त_tagset:
	blk_mq_मुक्त_tag_set(&ctrl->tag_set);
out_destroy_queues:
	nvme_loop_destroy_io_queues(ctrl);
	वापस ret;
पूर्ण

अटल काष्ठा nvmet_port *nvme_loop_find_port(काष्ठा nvme_ctrl *ctrl)
अणु
	काष्ठा nvmet_port *p, *found = शून्य;

	mutex_lock(&nvme_loop_ports_mutex);
	list_क्रम_each_entry(p, &nvme_loop_ports, entry) अणु
		/* अगर no transport address is specअगरied use the first port */
		अगर ((ctrl->opts->mask & NVMF_OPT_TRADDR) &&
		    म_भेद(ctrl->opts->traddr, p->disc_addr.traddr))
			जारी;
		found = p;
		अवरोध;
	पूर्ण
	mutex_unlock(&nvme_loop_ports_mutex);
	वापस found;
पूर्ण

अटल काष्ठा nvme_ctrl *nvme_loop_create_ctrl(काष्ठा device *dev,
		काष्ठा nvmf_ctrl_options *opts)
अणु
	काष्ठा nvme_loop_ctrl *ctrl;
	पूर्णांक ret;

	ctrl = kzalloc(माप(*ctrl), GFP_KERNEL);
	अगर (!ctrl)
		वापस ERR_PTR(-ENOMEM);
	ctrl->ctrl.opts = opts;
	INIT_LIST_HEAD(&ctrl->list);

	INIT_WORK(&ctrl->ctrl.reset_work, nvme_loop_reset_ctrl_work);

	ret = nvme_init_ctrl(&ctrl->ctrl, dev, &nvme_loop_ctrl_ops,
				0 /* no quirks, we're perfect! */);
	अगर (ret) अणु
		kमुक्त(ctrl);
		जाओ out;
	पूर्ण

	अगर (!nvme_change_ctrl_state(&ctrl->ctrl, NVME_CTRL_CONNECTING))
		WARN_ON_ONCE(1);

	ret = -ENOMEM;

	ctrl->ctrl.sqsize = opts->queue_size - 1;
	ctrl->ctrl.kato = opts->kato;
	ctrl->port = nvme_loop_find_port(&ctrl->ctrl);

	ctrl->queues = kसुस्मृति(opts->nr_io_queues + 1, माप(*ctrl->queues),
			GFP_KERNEL);
	अगर (!ctrl->queues)
		जाओ out_uninit_ctrl;

	ret = nvme_loop_configure_admin_queue(ctrl);
	अगर (ret)
		जाओ out_मुक्त_queues;

	अगर (opts->queue_size > ctrl->ctrl.maxcmd) अणु
		/* warn अगर maxcmd is lower than queue_size */
		dev_warn(ctrl->ctrl.device,
			"queue_size %zu > ctrl maxcmd %u, clamping down\n",
			opts->queue_size, ctrl->ctrl.maxcmd);
		opts->queue_size = ctrl->ctrl.maxcmd;
	पूर्ण

	अगर (opts->nr_io_queues) अणु
		ret = nvme_loop_create_io_queues(ctrl);
		अगर (ret)
			जाओ out_हटाओ_admin_queue;
	पूर्ण

	nvme_loop_init_iod(ctrl, &ctrl->async_event_iod, 0);

	dev_info(ctrl->ctrl.device,
		 "new ctrl: \"%s\"\n", ctrl->ctrl.opts->subsysnqn);

	अगर (!nvme_change_ctrl_state(&ctrl->ctrl, NVME_CTRL_LIVE))
		WARN_ON_ONCE(1);

	mutex_lock(&nvme_loop_ctrl_mutex);
	list_add_tail(&ctrl->list, &nvme_loop_ctrl_list);
	mutex_unlock(&nvme_loop_ctrl_mutex);

	nvme_start_ctrl(&ctrl->ctrl);

	वापस &ctrl->ctrl;

out_हटाओ_admin_queue:
	nvme_loop_destroy_admin_queue(ctrl);
out_मुक्त_queues:
	kमुक्त(ctrl->queues);
out_uninit_ctrl:
	nvme_uninit_ctrl(&ctrl->ctrl);
	nvme_put_ctrl(&ctrl->ctrl);
out:
	अगर (ret > 0)
		ret = -EIO;
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक nvme_loop_add_port(काष्ठा nvmet_port *port)
अणु
	mutex_lock(&nvme_loop_ports_mutex);
	list_add_tail(&port->entry, &nvme_loop_ports);
	mutex_unlock(&nvme_loop_ports_mutex);
	वापस 0;
पूर्ण

अटल व्योम nvme_loop_हटाओ_port(काष्ठा nvmet_port *port)
अणु
	mutex_lock(&nvme_loop_ports_mutex);
	list_del_init(&port->entry);
	mutex_unlock(&nvme_loop_ports_mutex);

	/*
	 * Ensure any ctrls that are in the process of being
	 * deleted are in fact deleted beक्रमe we वापस
	 * and मुक्त the port. This is to prevent active
	 * ctrls from using a port after it's मुक्तd.
	 */
	flush_workqueue(nvme_delete_wq);
पूर्ण

अटल स्थिर काष्ठा nvmet_fabrics_ops nvme_loop_ops = अणु
	.owner		= THIS_MODULE,
	.type		= NVMF_TRTYPE_LOOP,
	.add_port	= nvme_loop_add_port,
	.हटाओ_port	= nvme_loop_हटाओ_port,
	.queue_response = nvme_loop_queue_response,
	.delete_ctrl	= nvme_loop_delete_ctrl,
पूर्ण;

अटल काष्ठा nvmf_transport_ops nvme_loop_transport = अणु
	.name		= "loop",
	.module		= THIS_MODULE,
	.create_ctrl	= nvme_loop_create_ctrl,
	.allowed_opts	= NVMF_OPT_TRADDR,
पूर्ण;

अटल पूर्णांक __init nvme_loop_init_module(व्योम)
अणु
	पूर्णांक ret;

	ret = nvmet_रेजिस्टर_transport(&nvme_loop_ops);
	अगर (ret)
		वापस ret;

	ret = nvmf_रेजिस्टर_transport(&nvme_loop_transport);
	अगर (ret)
		nvmet_unरेजिस्टर_transport(&nvme_loop_ops);

	वापस ret;
पूर्ण

अटल व्योम __निकास nvme_loop_cleanup_module(व्योम)
अणु
	काष्ठा nvme_loop_ctrl *ctrl, *next;

	nvmf_unरेजिस्टर_transport(&nvme_loop_transport);
	nvmet_unरेजिस्टर_transport(&nvme_loop_ops);

	mutex_lock(&nvme_loop_ctrl_mutex);
	list_क्रम_each_entry_safe(ctrl, next, &nvme_loop_ctrl_list, list)
		nvme_delete_ctrl(&ctrl->ctrl);
	mutex_unlock(&nvme_loop_ctrl_mutex);

	flush_workqueue(nvme_delete_wq);
पूर्ण

module_init(nvme_loop_init_module);
module_निकास(nvme_loop_cleanup_module);

MODULE_LICENSE("GPL v2");
MODULE_ALIAS("nvmet-transport-254"); /* 254 == NVMF_TRTYPE_LOOP */
