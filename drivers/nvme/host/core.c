<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NVM Express device driver
 * Copyright (c) 2011-2014, Intel Corporation.
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/compat.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/hdreg.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/list_sort.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/pr.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/nvme_ioctl.h>
#समावेश <linux/pm_qos.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "nvme.h"
#समावेश "fabrics.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace.h"

#घोषणा NVME_MINORS		(1U << MINORBITS)

अचिन्हित पूर्णांक admin_समयout = 60;
module_param(admin_समयout, uपूर्णांक, 0644);
MODULE_PARM_DESC(admin_समयout, "timeout in seconds for admin commands");
EXPORT_SYMBOL_GPL(admin_समयout);

अचिन्हित पूर्णांक nvme_io_समयout = 30;
module_param_named(io_समयout, nvme_io_समयout, uपूर्णांक, 0644);
MODULE_PARM_DESC(io_समयout, "timeout in seconds for I/O");
EXPORT_SYMBOL_GPL(nvme_io_समयout);

अटल अचिन्हित अक्षर shutकरोwn_समयout = 5;
module_param(shutकरोwn_समयout, byte, 0644);
MODULE_PARM_DESC(shutकरोwn_समयout, "timeout in seconds for controller shutdown");

अटल u8 nvme_max_retries = 5;
module_param_named(max_retries, nvme_max_retries, byte, 0644);
MODULE_PARM_DESC(max_retries, "max number of retries a command may have");

अटल अचिन्हित दीर्घ शेष_ps_max_latency_us = 100000;
module_param(शेष_ps_max_latency_us, uदीर्घ, 0644);
MODULE_PARM_DESC(शेष_ps_max_latency_us,
		 "max power saving latency for new devices; use PM QOS to change per device");

अटल bool क्रमce_apst;
module_param(क्रमce_apst, bool, 0644);
MODULE_PARM_DESC(क्रमce_apst, "allow APST for newly enumerated devices even if quirked off");

अटल bool streams;
module_param(streams, bool, 0644);
MODULE_PARM_DESC(streams, "turn on support for Streams write directives");

/*
 * nvme_wq - hosts nvme related works that are not reset or delete
 * nvme_reset_wq - hosts nvme reset works
 * nvme_delete_wq - hosts nvme delete works
 *
 * nvme_wq will host works such as scan, aen handling, fw activation,
 * keep-alive, periodic reconnects etc. nvme_reset_wq
 * runs reset works which also flush works hosted on nvme_wq क्रम
 * serialization purposes. nvme_delete_wq host controller deletion
 * works which flush reset works क्रम serialization.
 */
काष्ठा workqueue_काष्ठा *nvme_wq;
EXPORT_SYMBOL_GPL(nvme_wq);

काष्ठा workqueue_काष्ठा *nvme_reset_wq;
EXPORT_SYMBOL_GPL(nvme_reset_wq);

काष्ठा workqueue_काष्ठा *nvme_delete_wq;
EXPORT_SYMBOL_GPL(nvme_delete_wq);

अटल LIST_HEAD(nvme_subप्रणालीs);
अटल DEFINE_MUTEX(nvme_subप्रणालीs_lock);

अटल DEFINE_IDA(nvme_instance_ida);
अटल dev_t nvme_ctrl_base_chr_devt;
अटल काष्ठा class *nvme_class;
अटल काष्ठा class *nvme_subsys_class;

अटल DEFINE_IDA(nvme_ns_chr_minor_ida);
अटल dev_t nvme_ns_chr_devt;
अटल काष्ठा class *nvme_ns_chr_class;

अटल व्योम nvme_put_subप्रणाली(काष्ठा nvme_subप्रणाली *subsys);
अटल व्योम nvme_हटाओ_invalid_namespaces(काष्ठा nvme_ctrl *ctrl,
					   अचिन्हित nsid);

/*
 * Prepare a queue क्रम tearकरोwn.
 *
 * This must क्रमcibly unquiesce queues to aव्योम blocking dispatch, and only set
 * the capacity to 0 after that to aव्योम blocking dispatchers that may be
 * holding bd_butex.  This will end buffered ग_लिखोrs dirtying pages that can't
 * be synced.
 */
अटल व्योम nvme_set_queue_dying(काष्ठा nvme_ns *ns)
अणु
	अगर (test_and_set_bit(NVME_NS_DEAD, &ns->flags))
		वापस;

	blk_set_queue_dying(ns->queue);
	blk_mq_unquiesce_queue(ns->queue);

	set_capacity_and_notअगरy(ns->disk, 0);
पूर्ण

व्योम nvme_queue_scan(काष्ठा nvme_ctrl *ctrl)
अणु
	/*
	 * Only new queue scan work when admin and IO queues are both alive
	 */
	अगर (ctrl->state == NVME_CTRL_LIVE && ctrl->tagset)
		queue_work(nvme_wq, &ctrl->scan_work);
पूर्ण

/*
 * Use this function to proceed with scheduling reset_work क्रम a controller
 * that had previously been set to the resetting state. This is पूर्णांकended क्रम
 * code paths that can't be पूर्णांकerrupted by other reset attempts. A hot removal
 * may prevent this from succeeding.
 */
पूर्णांक nvme_try_sched_reset(काष्ठा nvme_ctrl *ctrl)
अणु
	अगर (ctrl->state != NVME_CTRL_RESETTING)
		वापस -EBUSY;
	अगर (!queue_work(nvme_reset_wq, &ctrl->reset_work))
		वापस -EBUSY;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nvme_try_sched_reset);

अटल व्योम nvme_failfast_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvme_ctrl *ctrl = container_of(to_delayed_work(work),
			काष्ठा nvme_ctrl, failfast_work);

	अगर (ctrl->state != NVME_CTRL_CONNECTING)
		वापस;

	set_bit(NVME_CTRL_FAILFAST_EXPIRED, &ctrl->flags);
	dev_info(ctrl->device, "failfast expired\n");
	nvme_kick_requeue_lists(ctrl);
पूर्ण

अटल अंतरभूत व्योम nvme_start_failfast_work(काष्ठा nvme_ctrl *ctrl)
अणु
	अगर (!ctrl->opts || ctrl->opts->fast_io_fail_पंचांगo == -1)
		वापस;

	schedule_delayed_work(&ctrl->failfast_work,
			      ctrl->opts->fast_io_fail_पंचांगo * HZ);
पूर्ण

अटल अंतरभूत व्योम nvme_stop_failfast_work(काष्ठा nvme_ctrl *ctrl)
अणु
	अगर (!ctrl->opts)
		वापस;

	cancel_delayed_work_sync(&ctrl->failfast_work);
	clear_bit(NVME_CTRL_FAILFAST_EXPIRED, &ctrl->flags);
पूर्ण


पूर्णांक nvme_reset_ctrl(काष्ठा nvme_ctrl *ctrl)
अणु
	अगर (!nvme_change_ctrl_state(ctrl, NVME_CTRL_RESETTING))
		वापस -EBUSY;
	अगर (!queue_work(nvme_reset_wq, &ctrl->reset_work))
		वापस -EBUSY;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nvme_reset_ctrl);

पूर्णांक nvme_reset_ctrl_sync(काष्ठा nvme_ctrl *ctrl)
अणु
	पूर्णांक ret;

	ret = nvme_reset_ctrl(ctrl);
	अगर (!ret) अणु
		flush_work(&ctrl->reset_work);
		अगर (ctrl->state != NVME_CTRL_LIVE)
			ret = -ENETRESET;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम nvme_करो_delete_ctrl(काष्ठा nvme_ctrl *ctrl)
अणु
	dev_info(ctrl->device,
		 "Removing ctrl: NQN \"%s\"\n", ctrl->opts->subsysnqn);

	flush_work(&ctrl->reset_work);
	nvme_stop_ctrl(ctrl);
	nvme_हटाओ_namespaces(ctrl);
	ctrl->ops->delete_ctrl(ctrl);
	nvme_uninit_ctrl(ctrl);
पूर्ण

अटल व्योम nvme_delete_ctrl_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvme_ctrl *ctrl =
		container_of(work, काष्ठा nvme_ctrl, delete_work);

	nvme_करो_delete_ctrl(ctrl);
पूर्ण

पूर्णांक nvme_delete_ctrl(काष्ठा nvme_ctrl *ctrl)
अणु
	अगर (!nvme_change_ctrl_state(ctrl, NVME_CTRL_DELETING))
		वापस -EBUSY;
	अगर (!queue_work(nvme_delete_wq, &ctrl->delete_work))
		वापस -EBUSY;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nvme_delete_ctrl);

अटल व्योम nvme_delete_ctrl_sync(काष्ठा nvme_ctrl *ctrl)
अणु
	/*
	 * Keep a reference until nvme_करो_delete_ctrl() complete,
	 * since ->delete_ctrl can मुक्त the controller.
	 */
	nvme_get_ctrl(ctrl);
	अगर (nvme_change_ctrl_state(ctrl, NVME_CTRL_DELETING))
		nvme_करो_delete_ctrl(ctrl);
	nvme_put_ctrl(ctrl);
पूर्ण

अटल blk_status_t nvme_error_status(u16 status)
अणु
	चयन (status & 0x7ff) अणु
	हाल NVME_SC_SUCCESS:
		वापस BLK_STS_OK;
	हाल NVME_SC_CAP_EXCEEDED:
		वापस BLK_STS_NOSPC;
	हाल NVME_SC_LBA_RANGE:
	हाल NVME_SC_CMD_INTERRUPTED:
	हाल NVME_SC_NS_NOT_READY:
		वापस BLK_STS_TARGET;
	हाल NVME_SC_BAD_ATTRIBUTES:
	हाल NVME_SC_ONCS_NOT_SUPPORTED:
	हाल NVME_SC_INVALID_OPCODE:
	हाल NVME_SC_INVALID_FIELD:
	हाल NVME_SC_INVALID_NS:
		वापस BLK_STS_NOTSUPP;
	हाल NVME_SC_WRITE_FAULT:
	हाल NVME_SC_READ_ERROR:
	हाल NVME_SC_UNWRITTEN_BLOCK:
	हाल NVME_SC_ACCESS_DENIED:
	हाल NVME_SC_READ_ONLY:
	हाल NVME_SC_COMPARE_FAILED:
		वापस BLK_STS_MEDIUM;
	हाल NVME_SC_GUARD_CHECK:
	हाल NVME_SC_APPTAG_CHECK:
	हाल NVME_SC_REFTAG_CHECK:
	हाल NVME_SC_INVALID_PI:
		वापस BLK_STS_PROTECTION;
	हाल NVME_SC_RESERVATION_CONFLICT:
		वापस BLK_STS_NEXUS;
	हाल NVME_SC_HOST_PATH_ERROR:
		वापस BLK_STS_TRANSPORT;
	हाल NVME_SC_ZONE_TOO_MANY_ACTIVE:
		वापस BLK_STS_ZONE_ACTIVE_RESOURCE;
	हाल NVME_SC_ZONE_TOO_MANY_OPEN:
		वापस BLK_STS_ZONE_OPEN_RESOURCE;
	शेष:
		वापस BLK_STS_IOERR;
	पूर्ण
पूर्ण

अटल व्योम nvme_retry_req(काष्ठा request *req)
अणु
	अचिन्हित दीर्घ delay = 0;
	u16 crd;

	/* The mask and shअगरt result must be <= 3 */
	crd = (nvme_req(req)->status & NVME_SC_CRD) >> 11;
	अगर (crd)
		delay = nvme_req(req)->ctrl->crdt[crd - 1] * 100;

	nvme_req(req)->retries++;
	blk_mq_requeue_request(req, false);
	blk_mq_delay_kick_requeue_list(req->q, delay);
पूर्ण

क्रमागत nvme_disposition अणु
	COMPLETE,
	RETRY,
	FAILOVER,
पूर्ण;

अटल अंतरभूत क्रमागत nvme_disposition nvme_decide_disposition(काष्ठा request *req)
अणु
	अगर (likely(nvme_req(req)->status == 0))
		वापस COMPLETE;

	अगर (blk_noretry_request(req) ||
	    (nvme_req(req)->status & NVME_SC_DNR) ||
	    nvme_req(req)->retries >= nvme_max_retries)
		वापस COMPLETE;

	अगर (req->cmd_flags & REQ_NVME_MPATH) अणु
		अगर (nvme_is_path_error(nvme_req(req)->status) ||
		    blk_queue_dying(req->q))
			वापस FAILOVER;
	पूर्ण अन्यथा अणु
		अगर (blk_queue_dying(req->q))
			वापस COMPLETE;
	पूर्ण

	वापस RETRY;
पूर्ण

अटल अंतरभूत व्योम nvme_end_req(काष्ठा request *req)
अणु
	blk_status_t status = nvme_error_status(nvme_req(req)->status);

	अगर (IS_ENABLED(CONFIG_BLK_DEV_ZONED) &&
	    req_op(req) == REQ_OP_ZONE_APPEND)
		req->__sector = nvme_lba_to_sect(req->q->queuedata,
			le64_to_cpu(nvme_req(req)->result.u64));

	nvme_trace_bio_complete(req);
	blk_mq_end_request(req, status);
पूर्ण

व्योम nvme_complete_rq(काष्ठा request *req)
अणु
	trace_nvme_complete_rq(req);
	nvme_cleanup_cmd(req);

	अगर (nvme_req(req)->ctrl->kas)
		nvme_req(req)->ctrl->comp_seen = true;

	चयन (nvme_decide_disposition(req)) अणु
	हाल COMPLETE:
		nvme_end_req(req);
		वापस;
	हाल RETRY:
		nvme_retry_req(req);
		वापस;
	हाल FAILOVER:
		nvme_failover_req(req);
		वापस;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nvme_complete_rq);

/*
 * Called to unwind from ->queue_rq on a failed command submission so that the
 * multipathing code माला_लो called to potentially failover to another path.
 * The caller needs to unwind all transport specअगरic resource allocations and
 * must वापस propagate the वापस value.
 */
blk_status_t nvme_host_path_error(काष्ठा request *req)
अणु
	nvme_req(req)->status = NVME_SC_HOST_PATH_ERROR;
	blk_mq_set_request_complete(req);
	nvme_complete_rq(req);
	वापस BLK_STS_OK;
पूर्ण
EXPORT_SYMBOL_GPL(nvme_host_path_error);

bool nvme_cancel_request(काष्ठा request *req, व्योम *data, bool reserved)
अणु
	dev_dbg_ratelimited(((काष्ठा nvme_ctrl *) data)->device,
				"Cancelling I/O %d", req->tag);

	/* करोn't पात one completed request */
	अगर (blk_mq_request_completed(req))
		वापस true;

	nvme_req(req)->status = NVME_SC_HOST_ABORTED_CMD;
	nvme_req(req)->flags |= NVME_REQ_CANCELLED;
	blk_mq_complete_request(req);
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(nvme_cancel_request);

व्योम nvme_cancel_tagset(काष्ठा nvme_ctrl *ctrl)
अणु
	अगर (ctrl->tagset) अणु
		blk_mq_tagset_busy_iter(ctrl->tagset,
				nvme_cancel_request, ctrl);
		blk_mq_tagset_रुको_completed_request(ctrl->tagset);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nvme_cancel_tagset);

व्योम nvme_cancel_admin_tagset(काष्ठा nvme_ctrl *ctrl)
अणु
	अगर (ctrl->admin_tagset) अणु
		blk_mq_tagset_busy_iter(ctrl->admin_tagset,
				nvme_cancel_request, ctrl);
		blk_mq_tagset_रुको_completed_request(ctrl->admin_tagset);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nvme_cancel_admin_tagset);

bool nvme_change_ctrl_state(काष्ठा nvme_ctrl *ctrl,
		क्रमागत nvme_ctrl_state new_state)
अणु
	क्रमागत nvme_ctrl_state old_state;
	अचिन्हित दीर्घ flags;
	bool changed = false;

	spin_lock_irqsave(&ctrl->lock, flags);

	old_state = ctrl->state;
	चयन (new_state) अणु
	हाल NVME_CTRL_LIVE:
		चयन (old_state) अणु
		हाल NVME_CTRL_NEW:
		हाल NVME_CTRL_RESETTING:
		हाल NVME_CTRL_CONNECTING:
			changed = true;
			fallthrough;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल NVME_CTRL_RESETTING:
		चयन (old_state) अणु
		हाल NVME_CTRL_NEW:
		हाल NVME_CTRL_LIVE:
			changed = true;
			fallthrough;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल NVME_CTRL_CONNECTING:
		चयन (old_state) अणु
		हाल NVME_CTRL_NEW:
		हाल NVME_CTRL_RESETTING:
			changed = true;
			fallthrough;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल NVME_CTRL_DELETING:
		चयन (old_state) अणु
		हाल NVME_CTRL_LIVE:
		हाल NVME_CTRL_RESETTING:
		हाल NVME_CTRL_CONNECTING:
			changed = true;
			fallthrough;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल NVME_CTRL_DELETING_NOIO:
		चयन (old_state) अणु
		हाल NVME_CTRL_DELETING:
		हाल NVME_CTRL_DEAD:
			changed = true;
			fallthrough;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल NVME_CTRL_DEAD:
		चयन (old_state) अणु
		हाल NVME_CTRL_DELETING:
			changed = true;
			fallthrough;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (changed) अणु
		ctrl->state = new_state;
		wake_up_all(&ctrl->state_wq);
	पूर्ण

	spin_unlock_irqrestore(&ctrl->lock, flags);
	अगर (!changed)
		वापस false;

	अगर (ctrl->state == NVME_CTRL_LIVE) अणु
		अगर (old_state == NVME_CTRL_CONNECTING)
			nvme_stop_failfast_work(ctrl);
		nvme_kick_requeue_lists(ctrl);
	पूर्ण अन्यथा अगर (ctrl->state == NVME_CTRL_CONNECTING &&
		old_state == NVME_CTRL_RESETTING) अणु
		nvme_start_failfast_work(ctrl);
	पूर्ण
	वापस changed;
पूर्ण
EXPORT_SYMBOL_GPL(nvme_change_ctrl_state);

/*
 * Returns true क्रम sink states that can't ever transition back to live.
 */
अटल bool nvme_state_terminal(काष्ठा nvme_ctrl *ctrl)
अणु
	चयन (ctrl->state) अणु
	हाल NVME_CTRL_NEW:
	हाल NVME_CTRL_LIVE:
	हाल NVME_CTRL_RESETTING:
	हाल NVME_CTRL_CONNECTING:
		वापस false;
	हाल NVME_CTRL_DELETING:
	हाल NVME_CTRL_DELETING_NOIO:
	हाल NVME_CTRL_DEAD:
		वापस true;
	शेष:
		WARN_ONCE(1, "Unhandled ctrl state:%d", ctrl->state);
		वापस true;
	पूर्ण
पूर्ण

/*
 * Waits क्रम the controller state to be resetting, or वापसs false अगर it is
 * not possible to ever transition to that state.
 */
bool nvme_रुको_reset(काष्ठा nvme_ctrl *ctrl)
अणु
	रुको_event(ctrl->state_wq,
		   nvme_change_ctrl_state(ctrl, NVME_CTRL_RESETTING) ||
		   nvme_state_terminal(ctrl));
	वापस ctrl->state == NVME_CTRL_RESETTING;
पूर्ण
EXPORT_SYMBOL_GPL(nvme_रुको_reset);

अटल व्योम nvme_मुक्त_ns_head(काष्ठा kref *ref)
अणु
	काष्ठा nvme_ns_head *head =
		container_of(ref, काष्ठा nvme_ns_head, ref);

	nvme_mpath_हटाओ_disk(head);
	ida_simple_हटाओ(&head->subsys->ns_ida, head->instance);
	cleanup_srcu_काष्ठा(&head->srcu);
	nvme_put_subप्रणाली(head->subsys);
	kमुक्त(head);
पूर्ण

bool nvme_tryget_ns_head(काष्ठा nvme_ns_head *head)
अणु
	वापस kref_get_unless_zero(&head->ref);
पूर्ण

व्योम nvme_put_ns_head(काष्ठा nvme_ns_head *head)
अणु
	kref_put(&head->ref, nvme_मुक्त_ns_head);
पूर्ण

अटल व्योम nvme_मुक्त_ns(काष्ठा kref *kref)
अणु
	काष्ठा nvme_ns *ns = container_of(kref, काष्ठा nvme_ns, kref);

	अगर (ns->ndev)
		nvme_nvm_unरेजिस्टर(ns);

	put_disk(ns->disk);
	nvme_put_ns_head(ns->head);
	nvme_put_ctrl(ns->ctrl);
	kमुक्त(ns);
पूर्ण

अटल अंतरभूत bool nvme_get_ns(काष्ठा nvme_ns *ns)
अणु
	वापस kref_get_unless_zero(&ns->kref);
पूर्ण

व्योम nvme_put_ns(काष्ठा nvme_ns *ns)
अणु
	kref_put(&ns->kref, nvme_मुक्त_ns);
पूर्ण
EXPORT_SYMBOL_NS_GPL(nvme_put_ns, NVME_TARGET_PASSTHRU);

अटल अंतरभूत व्योम nvme_clear_nvme_request(काष्ठा request *req)
अणु
	nvme_req(req)->retries = 0;
	nvme_req(req)->flags = 0;
	req->rq_flags |= RQF_DONTPREP;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक nvme_req_op(काष्ठा nvme_command *cmd)
अणु
	वापस nvme_is_ग_लिखो(cmd) ? REQ_OP_DRV_OUT : REQ_OP_DRV_IN;
पूर्ण

अटल अंतरभूत व्योम nvme_init_request(काष्ठा request *req,
		काष्ठा nvme_command *cmd)
अणु
	अगर (req->q->queuedata)
		req->समयout = NVME_IO_TIMEOUT;
	अन्यथा /* no queuedata implies admin queue */
		req->समयout = NVME_ADMIN_TIMEOUT;

	/* passthru commands should let the driver set the SGL flags */
	cmd->common.flags &= ~NVME_CMD_SGL_ALL;

	req->cmd_flags |= REQ_FAILFAST_DRIVER;
	nvme_clear_nvme_request(req);
	स_नकल(nvme_req(req)->cmd, cmd, माप(*cmd));
पूर्ण

काष्ठा request *nvme_alloc_request(काष्ठा request_queue *q,
		काष्ठा nvme_command *cmd, blk_mq_req_flags_t flags)
अणु
	काष्ठा request *req;

	req = blk_mq_alloc_request(q, nvme_req_op(cmd), flags);
	अगर (!IS_ERR(req))
		nvme_init_request(req, cmd);
	वापस req;
पूर्ण
EXPORT_SYMBOL_GPL(nvme_alloc_request);

अटल काष्ठा request *nvme_alloc_request_qid(काष्ठा request_queue *q,
		काष्ठा nvme_command *cmd, blk_mq_req_flags_t flags, पूर्णांक qid)
अणु
	काष्ठा request *req;

	req = blk_mq_alloc_request_hctx(q, nvme_req_op(cmd), flags,
			qid ? qid - 1 : 0);
	अगर (!IS_ERR(req))
		nvme_init_request(req, cmd);
	वापस req;
पूर्ण

/*
 * For something we're not in a state to send to the device the शेष action
 * is to busy it and retry it after the controller state is recovered.  However,
 * अगर the controller is deleting or अगर anything is marked क्रम failfast or
 * nvme multipath it is immediately failed.
 *
 * Note: commands used to initialize the controller will be marked क्रम failfast.
 * Note: nvme cli/ioctl commands are marked क्रम failfast.
 */
blk_status_t nvme_fail_nonपढ़ोy_command(काष्ठा nvme_ctrl *ctrl,
		काष्ठा request *rq)
अणु
	अगर (ctrl->state != NVME_CTRL_DELETING_NOIO &&
	    ctrl->state != NVME_CTRL_DEAD &&
	    !test_bit(NVME_CTRL_FAILFAST_EXPIRED, &ctrl->flags) &&
	    !blk_noretry_request(rq) && !(rq->cmd_flags & REQ_NVME_MPATH))
		वापस BLK_STS_RESOURCE;
	वापस nvme_host_path_error(rq);
पूर्ण
EXPORT_SYMBOL_GPL(nvme_fail_nonपढ़ोy_command);

bool __nvme_check_पढ़ोy(काष्ठा nvme_ctrl *ctrl, काष्ठा request *rq,
		bool queue_live)
अणु
	काष्ठा nvme_request *req = nvme_req(rq);

	/*
	 * currently we have a problem sending passthru commands
	 * on the admin_q अगर the controller is not LIVE because we can't
	 * make sure that they are going out after the admin connect,
	 * controller enable and/or other commands in the initialization
	 * sequence. until the controller will be LIVE, fail with
	 * BLK_STS_RESOURCE so that they will be rescheduled.
	 */
	अगर (rq->q == ctrl->admin_q && (req->flags & NVME_REQ_USERCMD))
		वापस false;

	अगर (ctrl->ops->flags & NVME_F_FABRICS) अणु
		/*
		 * Only allow commands on a live queue, except क्रम the connect
		 * command, which is require to set the queue live in the
		 * appropinquate states.
		 */
		चयन (ctrl->state) अणु
		हाल NVME_CTRL_CONNECTING:
			अगर (blk_rq_is_passthrough(rq) && nvme_is_fabrics(req->cmd) &&
			    req->cmd->fabrics.fctype == nvme_fabrics_type_connect)
				वापस true;
			अवरोध;
		शेष:
			अवरोध;
		हाल NVME_CTRL_DEAD:
			वापस false;
		पूर्ण
	पूर्ण

	वापस queue_live;
पूर्ण
EXPORT_SYMBOL_GPL(__nvme_check_पढ़ोy);

अटल पूर्णांक nvme_toggle_streams(काष्ठा nvme_ctrl *ctrl, bool enable)
अणु
	काष्ठा nvme_command c;

	स_रखो(&c, 0, माप(c));

	c.directive.opcode = nvme_admin_directive_send;
	c.directive.nsid = cpu_to_le32(NVME_NSID_ALL);
	c.directive.करोper = NVME_सूची_SND_ID_OP_ENABLE;
	c.directive.dtype = NVME_सूची_IDENTIFY;
	c.directive.tdtype = NVME_सूची_STREAMS;
	c.directive.endir = enable ? NVME_सूची_ENसूची : 0;

	वापस nvme_submit_sync_cmd(ctrl->admin_q, &c, शून्य, 0);
पूर्ण

अटल पूर्णांक nvme_disable_streams(काष्ठा nvme_ctrl *ctrl)
अणु
	वापस nvme_toggle_streams(ctrl, false);
पूर्ण

अटल पूर्णांक nvme_enable_streams(काष्ठा nvme_ctrl *ctrl)
अणु
	वापस nvme_toggle_streams(ctrl, true);
पूर्ण

अटल पूर्णांक nvme_get_stream_params(काष्ठा nvme_ctrl *ctrl,
				  काष्ठा streams_directive_params *s, u32 nsid)
अणु
	काष्ठा nvme_command c;

	स_रखो(&c, 0, माप(c));
	स_रखो(s, 0, माप(*s));

	c.directive.opcode = nvme_admin_directive_recv;
	c.directive.nsid = cpu_to_le32(nsid);
	c.directive.numd = cpu_to_le32(nvme_bytes_to_numd(माप(*s)));
	c.directive.करोper = NVME_सूची_RCV_ST_OP_PARAM;
	c.directive.dtype = NVME_सूची_STREAMS;

	वापस nvme_submit_sync_cmd(ctrl->admin_q, &c, s, माप(*s));
पूर्ण

अटल पूर्णांक nvme_configure_directives(काष्ठा nvme_ctrl *ctrl)
अणु
	काष्ठा streams_directive_params s;
	पूर्णांक ret;

	अगर (!(ctrl->oacs & NVME_CTRL_OACS_सूचीECTIVES))
		वापस 0;
	अगर (!streams)
		वापस 0;

	ret = nvme_enable_streams(ctrl);
	अगर (ret)
		वापस ret;

	ret = nvme_get_stream_params(ctrl, &s, NVME_NSID_ALL);
	अगर (ret)
		जाओ out_disable_stream;

	ctrl->nssa = le16_to_cpu(s.nssa);
	अगर (ctrl->nssa < BLK_MAX_WRITE_HINTS - 1) अणु
		dev_info(ctrl->device, "too few streams (%u) available\n",
					ctrl->nssa);
		जाओ out_disable_stream;
	पूर्ण

	ctrl->nr_streams = min_t(u16, ctrl->nssa, BLK_MAX_WRITE_HINTS - 1);
	dev_info(ctrl->device, "Using %u streams\n", ctrl->nr_streams);
	वापस 0;

out_disable_stream:
	nvme_disable_streams(ctrl);
	वापस ret;
पूर्ण

/*
 * Check अगर 'req' has a ग_लिखो hपूर्णांक associated with it. If it करोes, assign
 * a valid namespace stream to the ग_लिखो.
 */
अटल व्योम nvme_assign_ग_लिखो_stream(काष्ठा nvme_ctrl *ctrl,
				     काष्ठा request *req, u16 *control,
				     u32 *dsmgmt)
अणु
	क्रमागत rw_hपूर्णांक streamid = req->ग_लिखो_hपूर्णांक;

	अगर (streamid == WRITE_LIFE_NOT_SET || streamid == WRITE_LIFE_NONE)
		streamid = 0;
	अन्यथा अणु
		streamid--;
		अगर (WARN_ON_ONCE(streamid > ctrl->nr_streams))
			वापस;

		*control |= NVME_RW_DTYPE_STREAMS;
		*dsmgmt |= streamid << 16;
	पूर्ण

	अगर (streamid < ARRAY_SIZE(req->q->ग_लिखो_hपूर्णांकs))
		req->q->ग_लिखो_hपूर्णांकs[streamid] += blk_rq_bytes(req) >> 9;
पूर्ण

अटल अंतरभूत व्योम nvme_setup_flush(काष्ठा nvme_ns *ns,
		काष्ठा nvme_command *cmnd)
अणु
	cmnd->common.opcode = nvme_cmd_flush;
	cmnd->common.nsid = cpu_to_le32(ns->head->ns_id);
पूर्ण

अटल blk_status_t nvme_setup_discard(काष्ठा nvme_ns *ns, काष्ठा request *req,
		काष्ठा nvme_command *cmnd)
अणु
	अचिन्हित लघु segments = blk_rq_nr_discard_segments(req), n = 0;
	काष्ठा nvme_dsm_range *range;
	काष्ठा bio *bio;

	/*
	 * Some devices करो not consider the DSM 'Number of Ranges' field when
	 * determining how much data to DMA. Always allocate memory क्रम maximum
	 * number of segments to prevent device पढ़ोing beyond end of buffer.
	 */
	अटल स्थिर माप_प्रकार alloc_size = माप(*range) * NVME_DSM_MAX_RANGES;

	range = kzalloc(alloc_size, GFP_ATOMIC | __GFP_NOWARN);
	अगर (!range) अणु
		/*
		 * If we fail allocation our range, fallback to the controller
		 * discard page. If that's also busy, it's safe to वापस
		 * busy, as we know we can make progress once that's मुक्तd.
		 */
		अगर (test_and_set_bit_lock(0, &ns->ctrl->discard_page_busy))
			वापस BLK_STS_RESOURCE;

		range = page_address(ns->ctrl->discard_page);
	पूर्ण

	__rq_क्रम_each_bio(bio, req) अणु
		u64 slba = nvme_sect_to_lba(ns, bio->bi_iter.bi_sector);
		u32 nlb = bio->bi_iter.bi_size >> ns->lba_shअगरt;

		अगर (n < segments) अणु
			range[n].cattr = cpu_to_le32(0);
			range[n].nlb = cpu_to_le32(nlb);
			range[n].slba = cpu_to_le64(slba);
		पूर्ण
		n++;
	पूर्ण

	अगर (WARN_ON_ONCE(n != segments)) अणु
		अगर (virt_to_page(range) == ns->ctrl->discard_page)
			clear_bit_unlock(0, &ns->ctrl->discard_page_busy);
		अन्यथा
			kमुक्त(range);
		वापस BLK_STS_IOERR;
	पूर्ण

	cmnd->dsm.opcode = nvme_cmd_dsm;
	cmnd->dsm.nsid = cpu_to_le32(ns->head->ns_id);
	cmnd->dsm.nr = cpu_to_le32(segments - 1);
	cmnd->dsm.attributes = cpu_to_le32(NVME_DSMGMT_AD);

	req->special_vec.bv_page = virt_to_page(range);
	req->special_vec.bv_offset = offset_in_page(range);
	req->special_vec.bv_len = alloc_size;
	req->rq_flags |= RQF_SPECIAL_PAYLOAD;

	वापस BLK_STS_OK;
पूर्ण

अटल अंतरभूत blk_status_t nvme_setup_ग_लिखो_zeroes(काष्ठा nvme_ns *ns,
		काष्ठा request *req, काष्ठा nvme_command *cmnd)
अणु
	अगर (ns->ctrl->quirks & NVME_QUIRK_DEALLOCATE_ZEROES)
		वापस nvme_setup_discard(ns, req, cmnd);

	cmnd->ग_लिखो_zeroes.opcode = nvme_cmd_ग_लिखो_zeroes;
	cmnd->ग_लिखो_zeroes.nsid = cpu_to_le32(ns->head->ns_id);
	cmnd->ग_लिखो_zeroes.slba =
		cpu_to_le64(nvme_sect_to_lba(ns, blk_rq_pos(req)));
	cmnd->ग_लिखो_zeroes.length =
		cpu_to_le16((blk_rq_bytes(req) >> ns->lba_shअगरt) - 1);
	cmnd->ग_लिखो_zeroes.control = 0;
	वापस BLK_STS_OK;
पूर्ण

अटल अंतरभूत blk_status_t nvme_setup_rw(काष्ठा nvme_ns *ns,
		काष्ठा request *req, काष्ठा nvme_command *cmnd,
		क्रमागत nvme_opcode op)
अणु
	काष्ठा nvme_ctrl *ctrl = ns->ctrl;
	u16 control = 0;
	u32 dsmgmt = 0;

	अगर (req->cmd_flags & REQ_FUA)
		control |= NVME_RW_FUA;
	अगर (req->cmd_flags & (REQ_FAILFAST_DEV | REQ_RAHEAD))
		control |= NVME_RW_LR;

	अगर (req->cmd_flags & REQ_RAHEAD)
		dsmgmt |= NVME_RW_DSM_FREQ_PREFETCH;

	cmnd->rw.opcode = op;
	cmnd->rw.nsid = cpu_to_le32(ns->head->ns_id);
	cmnd->rw.slba = cpu_to_le64(nvme_sect_to_lba(ns, blk_rq_pos(req)));
	cmnd->rw.length = cpu_to_le16((blk_rq_bytes(req) >> ns->lba_shअगरt) - 1);

	अगर (req_op(req) == REQ_OP_WRITE && ctrl->nr_streams)
		nvme_assign_ग_लिखो_stream(ctrl, req, &control, &dsmgmt);

	अगर (ns->ms) अणु
		/*
		 * If क्रमmated with metadata, the block layer always provides a
		 * metadata buffer अगर CONFIG_BLK_DEV_INTEGRITY is enabled.  Else
		 * we enable the PRACT bit क्रम protection inक्रमmation or set the
		 * namespace capacity to zero to prevent any I/O.
		 */
		अगर (!blk_पूर्णांकegrity_rq(req)) अणु
			अगर (WARN_ON_ONCE(!nvme_ns_has_pi(ns)))
				वापस BLK_STS_NOTSUPP;
			control |= NVME_RW_PRINFO_PRACT;
		पूर्ण

		चयन (ns->pi_type) अणु
		हाल NVME_NS_DPS_PI_TYPE3:
			control |= NVME_RW_PRINFO_PRCHK_GUARD;
			अवरोध;
		हाल NVME_NS_DPS_PI_TYPE1:
		हाल NVME_NS_DPS_PI_TYPE2:
			control |= NVME_RW_PRINFO_PRCHK_GUARD |
					NVME_RW_PRINFO_PRCHK_REF;
			अगर (op == nvme_cmd_zone_append)
				control |= NVME_RW_APPEND_PIREMAP;
			cmnd->rw.reftag = cpu_to_le32(t10_pi_ref_tag(req));
			अवरोध;
		पूर्ण
	पूर्ण

	cmnd->rw.control = cpu_to_le16(control);
	cmnd->rw.dsmgmt = cpu_to_le32(dsmgmt);
	वापस 0;
पूर्ण

व्योम nvme_cleanup_cmd(काष्ठा request *req)
अणु
	अगर (req->rq_flags & RQF_SPECIAL_PAYLOAD) अणु
		काष्ठा nvme_ctrl *ctrl = nvme_req(req)->ctrl;
		काष्ठा page *page = req->special_vec.bv_page;

		अगर (page == ctrl->discard_page)
			clear_bit_unlock(0, &ctrl->discard_page_busy);
		अन्यथा
			kमुक्त(page_address(page) + req->special_vec.bv_offset);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nvme_cleanup_cmd);

blk_status_t nvme_setup_cmd(काष्ठा nvme_ns *ns, काष्ठा request *req)
अणु
	काष्ठा nvme_command *cmd = nvme_req(req)->cmd;
	blk_status_t ret = BLK_STS_OK;

	अगर (!(req->rq_flags & RQF_DONTPREP)) अणु
		nvme_clear_nvme_request(req);
		स_रखो(cmd, 0, माप(*cmd));
	पूर्ण

	चयन (req_op(req)) अणु
	हाल REQ_OP_DRV_IN:
	हाल REQ_OP_DRV_OUT:
		/* these are setup prior to execution in nvme_init_request() */
		अवरोध;
	हाल REQ_OP_FLUSH:
		nvme_setup_flush(ns, cmd);
		अवरोध;
	हाल REQ_OP_ZONE_RESET_ALL:
	हाल REQ_OP_ZONE_RESET:
		ret = nvme_setup_zone_mgmt_send(ns, req, cmd, NVME_ZONE_RESET);
		अवरोध;
	हाल REQ_OP_ZONE_OPEN:
		ret = nvme_setup_zone_mgmt_send(ns, req, cmd, NVME_ZONE_OPEN);
		अवरोध;
	हाल REQ_OP_ZONE_CLOSE:
		ret = nvme_setup_zone_mgmt_send(ns, req, cmd, NVME_ZONE_CLOSE);
		अवरोध;
	हाल REQ_OP_ZONE_FINISH:
		ret = nvme_setup_zone_mgmt_send(ns, req, cmd, NVME_ZONE_FINISH);
		अवरोध;
	हाल REQ_OP_WRITE_ZEROES:
		ret = nvme_setup_ग_लिखो_zeroes(ns, req, cmd);
		अवरोध;
	हाल REQ_OP_DISCARD:
		ret = nvme_setup_discard(ns, req, cmd);
		अवरोध;
	हाल REQ_OP_READ:
		ret = nvme_setup_rw(ns, req, cmd, nvme_cmd_पढ़ो);
		अवरोध;
	हाल REQ_OP_WRITE:
		ret = nvme_setup_rw(ns, req, cmd, nvme_cmd_ग_लिखो);
		अवरोध;
	हाल REQ_OP_ZONE_APPEND:
		ret = nvme_setup_rw(ns, req, cmd, nvme_cmd_zone_append);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस BLK_STS_IOERR;
	पूर्ण

	cmd->common.command_id = req->tag;
	trace_nvme_setup_cmd(req, cmd);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nvme_setup_cmd);

अटल व्योम nvme_end_sync_rq(काष्ठा request *rq, blk_status_t error)
अणु
	काष्ठा completion *रुकोing = rq->end_io_data;

	rq->end_io_data = शून्य;
	complete(रुकोing);
पूर्ण

अटल व्योम nvme_execute_rq_polled(काष्ठा request_queue *q,
		काष्ठा gendisk *bd_disk, काष्ठा request *rq, पूर्णांक at_head)
अणु
	DECLARE_COMPLETION_ONSTACK(रुको);

	WARN_ON_ONCE(!test_bit(QUEUE_FLAG_POLL, &q->queue_flags));

	rq->cmd_flags |= REQ_HIPRI;
	rq->end_io_data = &रुको;
	blk_execute_rq_noरुको(bd_disk, rq, at_head, nvme_end_sync_rq);

	जबतक (!completion_करोne(&रुको)) अणु
		blk_poll(q, request_to_qc_t(rq->mq_hctx, rq), true);
		cond_resched();
	पूर्ण
पूर्ण

/*
 * Returns 0 on success.  If the result is negative, it's a Linux error code;
 * अगर the result is positive, it's an NVM Express status code
 */
पूर्णांक __nvme_submit_sync_cmd(काष्ठा request_queue *q, काष्ठा nvme_command *cmd,
		जोड़ nvme_result *result, व्योम *buffer, अचिन्हित bufflen,
		अचिन्हित समयout, पूर्णांक qid, पूर्णांक at_head,
		blk_mq_req_flags_t flags, bool poll)
अणु
	काष्ठा request *req;
	पूर्णांक ret;

	अगर (qid == NVME_QID_ANY)
		req = nvme_alloc_request(q, cmd, flags);
	अन्यथा
		req = nvme_alloc_request_qid(q, cmd, flags, qid);
	अगर (IS_ERR(req))
		वापस PTR_ERR(req);

	अगर (समयout)
		req->समयout = समयout;

	अगर (buffer && bufflen) अणु
		ret = blk_rq_map_kern(q, req, buffer, bufflen, GFP_KERNEL);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (poll)
		nvme_execute_rq_polled(req->q, शून्य, req, at_head);
	अन्यथा
		blk_execute_rq(शून्य, req, at_head);
	अगर (result)
		*result = nvme_req(req)->result;
	अगर (nvme_req(req)->flags & NVME_REQ_CANCELLED)
		ret = -EINTR;
	अन्यथा
		ret = nvme_req(req)->status;
 out:
	blk_mq_मुक्त_request(req);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__nvme_submit_sync_cmd);

पूर्णांक nvme_submit_sync_cmd(काष्ठा request_queue *q, काष्ठा nvme_command *cmd,
		व्योम *buffer, अचिन्हित bufflen)
अणु
	वापस __nvme_submit_sync_cmd(q, cmd, शून्य, buffer, bufflen, 0,
			NVME_QID_ANY, 0, 0, false);
पूर्ण
EXPORT_SYMBOL_GPL(nvme_submit_sync_cmd);

अटल u32 nvme_known_admin_effects(u8 opcode)
अणु
	चयन (opcode) अणु
	हाल nvme_admin_क्रमmat_nvm:
		वापस NVME_CMD_EFFECTS_LBCC | NVME_CMD_EFFECTS_NCC |
			NVME_CMD_EFFECTS_CSE_MASK;
	हाल nvme_admin_sanitize_nvm:
		वापस NVME_CMD_EFFECTS_LBCC | NVME_CMD_EFFECTS_CSE_MASK;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

u32 nvme_command_effects(काष्ठा nvme_ctrl *ctrl, काष्ठा nvme_ns *ns, u8 opcode)
अणु
	u32 effects = 0;

	अगर (ns) अणु
		अगर (ns->head->effects)
			effects = le32_to_cpu(ns->head->effects->iocs[opcode]);
		अगर (effects & ~(NVME_CMD_EFFECTS_CSUPP | NVME_CMD_EFFECTS_LBCC))
			dev_warn_once(ctrl->device,
				"IO command:%02x has unhandled effects:%08x\n",
				opcode, effects);
		वापस 0;
	पूर्ण

	अगर (ctrl->effects)
		effects = le32_to_cpu(ctrl->effects->acs[opcode]);
	effects |= nvme_known_admin_effects(opcode);

	वापस effects;
पूर्ण
EXPORT_SYMBOL_NS_GPL(nvme_command_effects, NVME_TARGET_PASSTHRU);

अटल u32 nvme_passthru_start(काष्ठा nvme_ctrl *ctrl, काष्ठा nvme_ns *ns,
			       u8 opcode)
अणु
	u32 effects = nvme_command_effects(ctrl, ns, opcode);

	/*
	 * For simplicity, IO to all namespaces is quiesced even अगर the command
	 * effects say only one namespace is affected.
	 */
	अगर (effects & NVME_CMD_EFFECTS_CSE_MASK) अणु
		mutex_lock(&ctrl->scan_lock);
		mutex_lock(&ctrl->subsys->lock);
		nvme_mpath_start_मुक्तze(ctrl->subsys);
		nvme_mpath_रुको_मुक्तze(ctrl->subsys);
		nvme_start_मुक्तze(ctrl);
		nvme_रुको_मुक्तze(ctrl);
	पूर्ण
	वापस effects;
पूर्ण

अटल व्योम nvme_passthru_end(काष्ठा nvme_ctrl *ctrl, u32 effects)
अणु
	अगर (effects & NVME_CMD_EFFECTS_CSE_MASK) अणु
		nvme_unमुक्तze(ctrl);
		nvme_mpath_unमुक्तze(ctrl->subsys);
		mutex_unlock(&ctrl->subsys->lock);
		nvme_हटाओ_invalid_namespaces(ctrl, NVME_NSID_ALL);
		mutex_unlock(&ctrl->scan_lock);
	पूर्ण
	अगर (effects & NVME_CMD_EFFECTS_CCC)
		nvme_init_ctrl_finish(ctrl);
	अगर (effects & (NVME_CMD_EFFECTS_NIC | NVME_CMD_EFFECTS_NCC)) अणु
		nvme_queue_scan(ctrl);
		flush_work(&ctrl->scan_work);
	पूर्ण
पूर्ण

व्योम nvme_execute_passthru_rq(काष्ठा request *rq)
अणु
	काष्ठा nvme_command *cmd = nvme_req(rq)->cmd;
	काष्ठा nvme_ctrl *ctrl = nvme_req(rq)->ctrl;
	काष्ठा nvme_ns *ns = rq->q->queuedata;
	काष्ठा gendisk *disk = ns ? ns->disk : शून्य;
	u32 effects;

	effects = nvme_passthru_start(ctrl, ns, cmd->common.opcode);
	blk_execute_rq(disk, rq, 0);
	अगर (effects) /* nothing to be करोne क्रम zero cmd effects */
		nvme_passthru_end(ctrl, effects);
पूर्ण
EXPORT_SYMBOL_NS_GPL(nvme_execute_passthru_rq, NVME_TARGET_PASSTHRU);

/*
 * Recommended frequency क्रम KATO commands per NVMe 1.4 section 7.12.1:
 * 
 *   The host should send Keep Alive commands at half of the Keep Alive Timeout
 *   accounting क्रम transport roundtrip बार [..].
 */
अटल व्योम nvme_queue_keep_alive_work(काष्ठा nvme_ctrl *ctrl)
अणु
	queue_delayed_work(nvme_wq, &ctrl->ka_work, ctrl->kato * HZ / 2);
पूर्ण

अटल व्योम nvme_keep_alive_end_io(काष्ठा request *rq, blk_status_t status)
अणु
	काष्ठा nvme_ctrl *ctrl = rq->end_io_data;
	अचिन्हित दीर्घ flags;
	bool startka = false;

	blk_mq_मुक्त_request(rq);

	अगर (status) अणु
		dev_err(ctrl->device,
			"failed nvme_keep_alive_end_io error=%d\n",
				status);
		वापस;
	पूर्ण

	ctrl->comp_seen = false;
	spin_lock_irqsave(&ctrl->lock, flags);
	अगर (ctrl->state == NVME_CTRL_LIVE ||
	    ctrl->state == NVME_CTRL_CONNECTING)
		startka = true;
	spin_unlock_irqrestore(&ctrl->lock, flags);
	अगर (startka)
		nvme_queue_keep_alive_work(ctrl);
पूर्ण

अटल व्योम nvme_keep_alive_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvme_ctrl *ctrl = container_of(to_delayed_work(work),
			काष्ठा nvme_ctrl, ka_work);
	bool comp_seen = ctrl->comp_seen;
	काष्ठा request *rq;

	अगर ((ctrl->ctratt & NVME_CTRL_ATTR_TBKAS) && comp_seen) अणु
		dev_dbg(ctrl->device,
			"reschedule traffic based keep-alive timer\n");
		ctrl->comp_seen = false;
		nvme_queue_keep_alive_work(ctrl);
		वापस;
	पूर्ण

	rq = nvme_alloc_request(ctrl->admin_q, &ctrl->ka_cmd,
				BLK_MQ_REQ_RESERVED | BLK_MQ_REQ_NOWAIT);
	अगर (IS_ERR(rq)) अणु
		/* allocation failure, reset the controller */
		dev_err(ctrl->device, "keep-alive failed: %ld\n", PTR_ERR(rq));
		nvme_reset_ctrl(ctrl);
		वापस;
	पूर्ण

	rq->समयout = ctrl->kato * HZ;
	rq->end_io_data = ctrl;
	blk_execute_rq_noरुको(शून्य, rq, 0, nvme_keep_alive_end_io);
पूर्ण

अटल व्योम nvme_start_keep_alive(काष्ठा nvme_ctrl *ctrl)
अणु
	अगर (unlikely(ctrl->kato == 0))
		वापस;

	nvme_queue_keep_alive_work(ctrl);
पूर्ण

व्योम nvme_stop_keep_alive(काष्ठा nvme_ctrl *ctrl)
अणु
	अगर (unlikely(ctrl->kato == 0))
		वापस;

	cancel_delayed_work_sync(&ctrl->ka_work);
पूर्ण
EXPORT_SYMBOL_GPL(nvme_stop_keep_alive);

/*
 * In NVMe 1.0 the CNS field was just a binary controller or namespace
 * flag, thus sending any new CNS opcodes has a big chance of not working.
 * Qemu unक्रमtunately had that bug after reporting a 1.1 version compliance
 * (but not क्रम any later version).
 */
अटल bool nvme_ctrl_limited_cns(काष्ठा nvme_ctrl *ctrl)
अणु
	अगर (ctrl->quirks & NVME_QUIRK_IDENTIFY_CNS)
		वापस ctrl->vs < NVME_VS(1, 2, 0);
	वापस ctrl->vs < NVME_VS(1, 1, 0);
पूर्ण

अटल पूर्णांक nvme_identअगरy_ctrl(काष्ठा nvme_ctrl *dev, काष्ठा nvme_id_ctrl **id)
अणु
	काष्ठा nvme_command c = अणु पूर्ण;
	पूर्णांक error;

	/* gcc-4.4.4 (at least) has issues with initializers and anon जोड़s */
	c.identअगरy.opcode = nvme_admin_identअगरy;
	c.identअगरy.cns = NVME_ID_CNS_CTRL;

	*id = kदो_स्मृति(माप(काष्ठा nvme_id_ctrl), GFP_KERNEL);
	अगर (!*id)
		वापस -ENOMEM;

	error = nvme_submit_sync_cmd(dev->admin_q, &c, *id,
			माप(काष्ठा nvme_id_ctrl));
	अगर (error)
		kमुक्त(*id);
	वापस error;
पूर्ण

अटल bool nvme_multi_css(काष्ठा nvme_ctrl *ctrl)
अणु
	वापस (ctrl->ctrl_config & NVME_CC_CSS_MASK) == NVME_CC_CSS_CSI;
पूर्ण

अटल पूर्णांक nvme_process_ns_desc(काष्ठा nvme_ctrl *ctrl, काष्ठा nvme_ns_ids *ids,
		काष्ठा nvme_ns_id_desc *cur, bool *csi_seen)
अणु
	स्थिर अक्षर *warn_str = "ctrl returned bogus length:";
	व्योम *data = cur;

	चयन (cur->nidt) अणु
	हाल NVME_NIDT_EUI64:
		अगर (cur->nidl != NVME_NIDT_EUI64_LEN) अणु
			dev_warn(ctrl->device, "%s %d for NVME_NIDT_EUI64\n",
				 warn_str, cur->nidl);
			वापस -1;
		पूर्ण
		स_नकल(ids->eui64, data + माप(*cur), NVME_NIDT_EUI64_LEN);
		वापस NVME_NIDT_EUI64_LEN;
	हाल NVME_NIDT_NGUID:
		अगर (cur->nidl != NVME_NIDT_NGUID_LEN) अणु
			dev_warn(ctrl->device, "%s %d for NVME_NIDT_NGUID\n",
				 warn_str, cur->nidl);
			वापस -1;
		पूर्ण
		स_नकल(ids->nguid, data + माप(*cur), NVME_NIDT_NGUID_LEN);
		वापस NVME_NIDT_NGUID_LEN;
	हाल NVME_NIDT_UUID:
		अगर (cur->nidl != NVME_NIDT_UUID_LEN) अणु
			dev_warn(ctrl->device, "%s %d for NVME_NIDT_UUID\n",
				 warn_str, cur->nidl);
			वापस -1;
		पूर्ण
		uuid_copy(&ids->uuid, data + माप(*cur));
		वापस NVME_NIDT_UUID_LEN;
	हाल NVME_NIDT_CSI:
		अगर (cur->nidl != NVME_NIDT_CSI_LEN) अणु
			dev_warn(ctrl->device, "%s %d for NVME_NIDT_CSI\n",
				 warn_str, cur->nidl);
			वापस -1;
		पूर्ण
		स_नकल(&ids->csi, data + माप(*cur), NVME_NIDT_CSI_LEN);
		*csi_seen = true;
		वापस NVME_NIDT_CSI_LEN;
	शेष:
		/* Skip unknown types */
		वापस cur->nidl;
	पूर्ण
पूर्ण

अटल पूर्णांक nvme_identअगरy_ns_descs(काष्ठा nvme_ctrl *ctrl, अचिन्हित nsid,
		काष्ठा nvme_ns_ids *ids)
अणु
	काष्ठा nvme_command c = अणु पूर्ण;
	bool csi_seen = false;
	पूर्णांक status, pos, len;
	व्योम *data;

	अगर (ctrl->vs < NVME_VS(1, 3, 0) && !nvme_multi_css(ctrl))
		वापस 0;
	अगर (ctrl->quirks & NVME_QUIRK_NO_NS_DESC_LIST)
		वापस 0;

	c.identअगरy.opcode = nvme_admin_identअगरy;
	c.identअगरy.nsid = cpu_to_le32(nsid);
	c.identअगरy.cns = NVME_ID_CNS_NS_DESC_LIST;

	data = kzalloc(NVME_IDENTIFY_DATA_SIZE, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	status = nvme_submit_sync_cmd(ctrl->admin_q, &c, data,
				      NVME_IDENTIFY_DATA_SIZE);
	अगर (status) अणु
		dev_warn(ctrl->device,
			"Identify Descriptors failed (nsid=%u, status=0x%x)\n",
			nsid, status);
		जाओ मुक्त_data;
	पूर्ण

	क्रम (pos = 0; pos < NVME_IDENTIFY_DATA_SIZE; pos += len) अणु
		काष्ठा nvme_ns_id_desc *cur = data + pos;

		अगर (cur->nidl == 0)
			अवरोध;

		len = nvme_process_ns_desc(ctrl, ids, cur, &csi_seen);
		अगर (len < 0)
			अवरोध;

		len += माप(*cur);
	पूर्ण

	अगर (nvme_multi_css(ctrl) && !csi_seen) अणु
		dev_warn(ctrl->device, "Command set not reported for nsid:%d\n",
			 nsid);
		status = -EINVAL;
	पूर्ण

मुक्त_data:
	kमुक्त(data);
	वापस status;
पूर्ण

अटल पूर्णांक nvme_identअगरy_ns(काष्ठा nvme_ctrl *ctrl, अचिन्हित nsid,
			काष्ठा nvme_ns_ids *ids, काष्ठा nvme_id_ns **id)
अणु
	काष्ठा nvme_command c = अणु पूर्ण;
	पूर्णांक error;

	/* gcc-4.4.4 (at least) has issues with initializers and anon जोड़s */
	c.identअगरy.opcode = nvme_admin_identअगरy;
	c.identअगरy.nsid = cpu_to_le32(nsid);
	c.identअगरy.cns = NVME_ID_CNS_NS;

	*id = kदो_स्मृति(माप(**id), GFP_KERNEL);
	अगर (!*id)
		वापस -ENOMEM;

	error = nvme_submit_sync_cmd(ctrl->admin_q, &c, *id, माप(**id));
	अगर (error) अणु
		dev_warn(ctrl->device, "Identify namespace failed (%d)\n", error);
		जाओ out_मुक्त_id;
	पूर्ण

	error = NVME_SC_INVALID_NS | NVME_SC_DNR;
	अगर ((*id)->ncap == 0) /* namespace not allocated or attached */
		जाओ out_मुक्त_id;

	अगर (ctrl->vs >= NVME_VS(1, 1, 0) &&
	    !स_प्रथम_inv(ids->eui64, 0, माप(ids->eui64)))
		स_नकल(ids->eui64, (*id)->eui64, माप(ids->eui64));
	अगर (ctrl->vs >= NVME_VS(1, 2, 0) &&
	    !स_प्रथम_inv(ids->nguid, 0, माप(ids->nguid)))
		स_नकल(ids->nguid, (*id)->nguid, माप(ids->nguid));

	वापस 0;

out_मुक्त_id:
	kमुक्त(*id);
	वापस error;
पूर्ण

अटल पूर्णांक nvme_features(काष्ठा nvme_ctrl *dev, u8 op, अचिन्हित पूर्णांक fid,
		अचिन्हित पूर्णांक dword11, व्योम *buffer, माप_प्रकार buflen, u32 *result)
अणु
	जोड़ nvme_result res = अणु 0 पूर्ण;
	काष्ठा nvme_command c;
	पूर्णांक ret;

	स_रखो(&c, 0, माप(c));
	c.features.opcode = op;
	c.features.fid = cpu_to_le32(fid);
	c.features.dword11 = cpu_to_le32(dword11);

	ret = __nvme_submit_sync_cmd(dev->admin_q, &c, &res,
			buffer, buflen, 0, NVME_QID_ANY, 0, 0, false);
	अगर (ret >= 0 && result)
		*result = le32_to_cpu(res.u32);
	वापस ret;
पूर्ण

पूर्णांक nvme_set_features(काष्ठा nvme_ctrl *dev, अचिन्हित पूर्णांक fid,
		      अचिन्हित पूर्णांक dword11, व्योम *buffer, माप_प्रकार buflen,
		      u32 *result)
अणु
	वापस nvme_features(dev, nvme_admin_set_features, fid, dword11, buffer,
			     buflen, result);
पूर्ण
EXPORT_SYMBOL_GPL(nvme_set_features);

पूर्णांक nvme_get_features(काष्ठा nvme_ctrl *dev, अचिन्हित पूर्णांक fid,
		      अचिन्हित पूर्णांक dword11, व्योम *buffer, माप_प्रकार buflen,
		      u32 *result)
अणु
	वापस nvme_features(dev, nvme_admin_get_features, fid, dword11, buffer,
			     buflen, result);
पूर्ण
EXPORT_SYMBOL_GPL(nvme_get_features);

पूर्णांक nvme_set_queue_count(काष्ठा nvme_ctrl *ctrl, पूर्णांक *count)
अणु
	u32 q_count = (*count - 1) | ((*count - 1) << 16);
	u32 result;
	पूर्णांक status, nr_io_queues;

	status = nvme_set_features(ctrl, NVME_FEAT_NUM_QUEUES, q_count, शून्य, 0,
			&result);
	अगर (status < 0)
		वापस status;

	/*
	 * Degraded controllers might वापस an error when setting the queue
	 * count.  We still want to be able to bring them online and offer
	 * access to the admin queue, as that might be only way to fix them up.
	 */
	अगर (status > 0) अणु
		dev_err(ctrl->device, "Could not set queue count (%d)\n", status);
		*count = 0;
	पूर्ण अन्यथा अणु
		nr_io_queues = min(result & 0xffff, result >> 16) + 1;
		*count = min(*count, nr_io_queues);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nvme_set_queue_count);

#घोषणा NVME_AEN_SUPPORTED \
	(NVME_AEN_CFG_NS_ATTR | NVME_AEN_CFG_FW_ACT | \
	 NVME_AEN_CFG_ANA_CHANGE | NVME_AEN_CFG_DISC_CHANGE)

अटल व्योम nvme_enable_aen(काष्ठा nvme_ctrl *ctrl)
अणु
	u32 result, supported_aens = ctrl->oaes & NVME_AEN_SUPPORTED;
	पूर्णांक status;

	अगर (!supported_aens)
		वापस;

	status = nvme_set_features(ctrl, NVME_FEAT_ASYNC_EVENT, supported_aens,
			शून्य, 0, &result);
	अगर (status)
		dev_warn(ctrl->device, "Failed to configure AEN (cfg %x)\n",
			 supported_aens);

	queue_work(nvme_wq, &ctrl->async_event_work);
पूर्ण

/*
 * Issue ioctl requests on the first available path.  Note that unlike normal
 * block layer requests we will not retry failed request on another controller.
 */
काष्ठा nvme_ns *nvme_get_ns_from_disk(काष्ठा gendisk *disk,
		काष्ठा nvme_ns_head **head, पूर्णांक *srcu_idx)
अणु
#अगर_घोषित CONFIG_NVME_MULTIPATH
	अगर (disk->fops == &nvme_ns_head_ops) अणु
		काष्ठा nvme_ns *ns;

		*head = disk->निजी_data;
		*srcu_idx = srcu_पढ़ो_lock(&(*head)->srcu);
		ns = nvme_find_path(*head);
		अगर (!ns)
			srcu_पढ़ो_unlock(&(*head)->srcu, *srcu_idx);
		वापस ns;
	पूर्ण
#पूर्ण_अगर
	*head = शून्य;
	*srcu_idx = -1;
	वापस disk->निजी_data;
पूर्ण

व्योम nvme_put_ns_from_disk(काष्ठा nvme_ns_head *head, पूर्णांक idx)
अणु
	अगर (head)
		srcu_पढ़ो_unlock(&head->srcu, idx);
पूर्ण

अटल पूर्णांक nvme_ns_खोलो(काष्ठा nvme_ns *ns)
अणु

	/* should never be called due to GENHD_FL_HIDDEN */
	अगर (WARN_ON_ONCE(nvme_ns_head_multipath(ns->head)))
		जाओ fail;
	अगर (!nvme_get_ns(ns))
		जाओ fail;
	अगर (!try_module_get(ns->ctrl->ops->module))
		जाओ fail_put_ns;

	वापस 0;

fail_put_ns:
	nvme_put_ns(ns);
fail:
	वापस -ENXIO;
पूर्ण

अटल व्योम nvme_ns_release(काष्ठा nvme_ns *ns)
अणु

	module_put(ns->ctrl->ops->module);
	nvme_put_ns(ns);
पूर्ण

अटल पूर्णांक nvme_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	वापस nvme_ns_खोलो(bdev->bd_disk->निजी_data);
पूर्ण

अटल व्योम nvme_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	nvme_ns_release(disk->निजी_data);
पूर्ण

पूर्णांक nvme_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo)
अणु
	/* some standard values */
	geo->heads = 1 << 6;
	geo->sectors = 1 << 5;
	geo->cylinders = get_capacity(bdev->bd_disk) >> 11;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_INTEGRITY
अटल व्योम nvme_init_पूर्णांकegrity(काष्ठा gendisk *disk, u16 ms, u8 pi_type,
				u32 max_पूर्णांकegrity_segments)
अणु
	काष्ठा blk_पूर्णांकegrity पूर्णांकegrity;

	स_रखो(&पूर्णांकegrity, 0, माप(पूर्णांकegrity));
	चयन (pi_type) अणु
	हाल NVME_NS_DPS_PI_TYPE3:
		पूर्णांकegrity.profile = &t10_pi_type3_crc;
		पूर्णांकegrity.tag_size = माप(u16) + माप(u32);
		पूर्णांकegrity.flags |= BLK_INTEGRITY_DEVICE_CAPABLE;
		अवरोध;
	हाल NVME_NS_DPS_PI_TYPE1:
	हाल NVME_NS_DPS_PI_TYPE2:
		पूर्णांकegrity.profile = &t10_pi_type1_crc;
		पूर्णांकegrity.tag_size = माप(u16);
		पूर्णांकegrity.flags |= BLK_INTEGRITY_DEVICE_CAPABLE;
		अवरोध;
	शेष:
		पूर्णांकegrity.profile = शून्य;
		अवरोध;
	पूर्ण
	पूर्णांकegrity.tuple_size = ms;
	blk_पूर्णांकegrity_रेजिस्टर(disk, &पूर्णांकegrity);
	blk_queue_max_पूर्णांकegrity_segments(disk->queue, max_पूर्णांकegrity_segments);
पूर्ण
#अन्यथा
अटल व्योम nvme_init_पूर्णांकegrity(काष्ठा gendisk *disk, u16 ms, u8 pi_type,
				u32 max_पूर्णांकegrity_segments)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_DEV_INTEGRITY */

अटल व्योम nvme_config_discard(काष्ठा gendisk *disk, काष्ठा nvme_ns *ns)
अणु
	काष्ठा nvme_ctrl *ctrl = ns->ctrl;
	काष्ठा request_queue *queue = disk->queue;
	u32 size = queue_logical_block_size(queue);

	अगर (ctrl->max_discard_sectors == 0) अणु
		blk_queue_flag_clear(QUEUE_FLAG_DISCARD, queue);
		वापस;
	पूर्ण

	अगर (ctrl->nr_streams && ns->sws && ns->sgs)
		size *= ns->sws * ns->sgs;

	BUILD_BUG_ON(PAGE_SIZE / माप(काष्ठा nvme_dsm_range) <
			NVME_DSM_MAX_RANGES);

	queue->limits.discard_alignment = 0;
	queue->limits.discard_granularity = size;

	/* If discard is alपढ़ोy enabled, करोn't reset queue limits */
	अगर (blk_queue_flag_test_and_set(QUEUE_FLAG_DISCARD, queue))
		वापस;

	blk_queue_max_discard_sectors(queue, ctrl->max_discard_sectors);
	blk_queue_max_discard_segments(queue, ctrl->max_discard_segments);

	अगर (ctrl->quirks & NVME_QUIRK_DEALLOCATE_ZEROES)
		blk_queue_max_ग_लिखो_zeroes_sectors(queue, अच_पूर्णांक_उच्च);
पूर्ण

अटल bool nvme_ns_ids_valid(काष्ठा nvme_ns_ids *ids)
अणु
	वापस !uuid_is_null(&ids->uuid) ||
		स_प्रथम_inv(ids->nguid, 0, माप(ids->nguid)) ||
		स_प्रथम_inv(ids->eui64, 0, माप(ids->eui64));
पूर्ण

अटल bool nvme_ns_ids_equal(काष्ठा nvme_ns_ids *a, काष्ठा nvme_ns_ids *b)
अणु
	वापस uuid_equal(&a->uuid, &b->uuid) &&
		स_भेद(&a->nguid, &b->nguid, माप(a->nguid)) == 0 &&
		स_भेद(&a->eui64, &b->eui64, माप(a->eui64)) == 0 &&
		a->csi == b->csi;
पूर्ण

अटल पूर्णांक nvme_setup_streams_ns(काष्ठा nvme_ctrl *ctrl, काष्ठा nvme_ns *ns,
				 u32 *phys_bs, u32 *io_opt)
अणु
	काष्ठा streams_directive_params s;
	पूर्णांक ret;

	अगर (!ctrl->nr_streams)
		वापस 0;

	ret = nvme_get_stream_params(ctrl, &s, ns->head->ns_id);
	अगर (ret)
		वापस ret;

	ns->sws = le32_to_cpu(s.sws);
	ns->sgs = le16_to_cpu(s.sgs);

	अगर (ns->sws) अणु
		*phys_bs = ns->sws * (1 << ns->lba_shअगरt);
		अगर (ns->sgs)
			*io_opt = *phys_bs * ns->sgs;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nvme_configure_metadata(काष्ठा nvme_ns *ns, काष्ठा nvme_id_ns *id)
अणु
	काष्ठा nvme_ctrl *ctrl = ns->ctrl;

	/*
	 * The PI implementation requires the metadata size to be equal to the
	 * t10 pi tuple size.
	 */
	ns->ms = le16_to_cpu(id->lbaf[id->flbas & NVME_NS_FLBAS_LBA_MASK].ms);
	अगर (ns->ms == माप(काष्ठा t10_pi_tuple))
		ns->pi_type = id->dps & NVME_NS_DPS_PI_MASK;
	अन्यथा
		ns->pi_type = 0;

	ns->features &= ~(NVME_NS_METADATA_SUPPORTED | NVME_NS_EXT_LBAS);
	अगर (!ns->ms || !(ctrl->ops->flags & NVME_F_METADATA_SUPPORTED))
		वापस 0;
	अगर (ctrl->ops->flags & NVME_F_FABRICS) अणु
		/*
		 * The NVMe over Fabrics specअगरication only supports metadata as
		 * part of the extended data LBA.  We rely on HCA/HBA support to
		 * remap the separate metadata buffer from the block layer.
		 */
		अगर (WARN_ON_ONCE(!(id->flbas & NVME_NS_FLBAS_META_EXT)))
			वापस -EINVAL;
		अगर (ctrl->max_पूर्णांकegrity_segments)
			ns->features |=
				(NVME_NS_METADATA_SUPPORTED | NVME_NS_EXT_LBAS);
	पूर्ण अन्यथा अणु
		/*
		 * For PCIe controllers, we can't easily remap the separate
		 * metadata buffer from the block layer and thus require a
		 * separate metadata buffer क्रम block layer metadata/PI support.
		 * We allow extended LBAs क्रम the passthrough पूर्णांकerface, though.
		 */
		अगर (id->flbas & NVME_NS_FLBAS_META_EXT)
			ns->features |= NVME_NS_EXT_LBAS;
		अन्यथा
			ns->features |= NVME_NS_METADATA_SUPPORTED;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nvme_set_queue_limits(काष्ठा nvme_ctrl *ctrl,
		काष्ठा request_queue *q)
अणु
	bool vwc = ctrl->vwc & NVME_CTRL_VWC_PRESENT;

	अगर (ctrl->max_hw_sectors) अणु
		u32 max_segments =
			(ctrl->max_hw_sectors / (NVME_CTRL_PAGE_SIZE >> 9)) + 1;

		max_segments = min_not_zero(max_segments, ctrl->max_segments);
		blk_queue_max_hw_sectors(q, ctrl->max_hw_sectors);
		blk_queue_max_segments(q, min_t(u32, max_segments, अच_लघु_उच्च));
	पूर्ण
	blk_queue_virt_boundary(q, NVME_CTRL_PAGE_SIZE - 1);
	blk_queue_dma_alignment(q, 7);
	blk_queue_ग_लिखो_cache(q, vwc, vwc);
पूर्ण

अटल व्योम nvme_update_disk_info(काष्ठा gendisk *disk,
		काष्ठा nvme_ns *ns, काष्ठा nvme_id_ns *id)
अणु
	sector_t capacity = nvme_lba_to_sect(ns, le64_to_cpu(id->nsze));
	अचिन्हित लघु bs = 1 << ns->lba_shअगरt;
	u32 atomic_bs, phys_bs, io_opt = 0;

	/*
	 * The block layer can't support LBA sizes larger than the page size
	 * yet, so catch this early and करोn't allow block I/O.
	 */
	अगर (ns->lba_shअगरt > PAGE_SHIFT) अणु
		capacity = 0;
		bs = (1 << 9);
	पूर्ण

	blk_पूर्णांकegrity_unरेजिस्टर(disk);

	atomic_bs = phys_bs = bs;
	nvme_setup_streams_ns(ns->ctrl, ns, &phys_bs, &io_opt);
	अगर (id->nabo == 0) अणु
		/*
		 * Bit 1 indicates whether NAWUPF is defined क्रम this namespace
		 * and whether it should be used instead of AWUPF. If NAWUPF ==
		 * 0 then AWUPF must be used instead.
		 */
		अगर (id->nsfeat & NVME_NS_FEAT_ATOMICS && id->nawupf)
			atomic_bs = (1 + le16_to_cpu(id->nawupf)) * bs;
		अन्यथा
			atomic_bs = (1 + ns->ctrl->subsys->awupf) * bs;
	पूर्ण

	अगर (id->nsfeat & NVME_NS_FEAT_IO_OPT) अणु
		/* NPWG = Namespace Preferred Write Granularity */
		phys_bs = bs * (1 + le16_to_cpu(id->npwg));
		/* NOWS = Namespace Optimal Write Size */
		io_opt = bs * (1 + le16_to_cpu(id->nows));
	पूर्ण

	blk_queue_logical_block_size(disk->queue, bs);
	/*
	 * Linux fileप्रणालीs assume writing a single physical block is
	 * an atomic operation. Hence limit the physical block size to the
	 * value of the Atomic Write Unit Power Fail parameter.
	 */
	blk_queue_physical_block_size(disk->queue, min(phys_bs, atomic_bs));
	blk_queue_io_min(disk->queue, phys_bs);
	blk_queue_io_opt(disk->queue, io_opt);

	/*
	 * Register a metadata profile क्रम PI, or the plain non-पूर्णांकegrity NVMe
	 * metadata masquerading as Type 0 अगर supported, otherwise reject block
	 * I/O to namespaces with metadata except when the namespace supports
	 * PI, as it can strip/insert in that हाल.
	 */
	अगर (ns->ms) अणु
		अगर (IS_ENABLED(CONFIG_BLK_DEV_INTEGRITY) &&
		    (ns->features & NVME_NS_METADATA_SUPPORTED))
			nvme_init_पूर्णांकegrity(disk, ns->ms, ns->pi_type,
					    ns->ctrl->max_पूर्णांकegrity_segments);
		अन्यथा अगर (!nvme_ns_has_pi(ns))
			capacity = 0;
	पूर्ण

	set_capacity_and_notअगरy(disk, capacity);

	nvme_config_discard(disk, ns);
	blk_queue_max_ग_लिखो_zeroes_sectors(disk->queue,
					   ns->ctrl->max_zeroes_sectors);

	set_disk_ro(disk, (id->nsattr & NVME_NS_ATTR_RO) ||
		test_bit(NVME_NS_FORCE_RO, &ns->flags));
पूर्ण

अटल अंतरभूत bool nvme_first_scan(काष्ठा gendisk *disk)
अणु
	/* nvme_alloc_ns() scans the disk prior to adding it */
	वापस !(disk->flags & GENHD_FL_UP);
पूर्ण

अटल व्योम nvme_set_chunk_sectors(काष्ठा nvme_ns *ns, काष्ठा nvme_id_ns *id)
अणु
	काष्ठा nvme_ctrl *ctrl = ns->ctrl;
	u32 iob;

	अगर ((ctrl->quirks & NVME_QUIRK_STRIPE_SIZE) &&
	    is_घातer_of_2(ctrl->max_hw_sectors))
		iob = ctrl->max_hw_sectors;
	अन्यथा
		iob = nvme_lba_to_sect(ns, le16_to_cpu(id->noiob));

	अगर (!iob)
		वापस;

	अगर (!is_घातer_of_2(iob)) अणु
		अगर (nvme_first_scan(ns->disk))
			pr_warn("%s: ignoring unaligned IO boundary:%u\n",
				ns->disk->disk_name, iob);
		वापस;
	पूर्ण

	अगर (blk_queue_is_zoned(ns->disk->queue)) अणु
		अगर (nvme_first_scan(ns->disk))
			pr_warn("%s: ignoring zoned namespace IO boundary\n",
				ns->disk->disk_name);
		वापस;
	पूर्ण

	blk_queue_chunk_sectors(ns->queue, iob);
पूर्ण

अटल पूर्णांक nvme_update_ns_info(काष्ठा nvme_ns *ns, काष्ठा nvme_id_ns *id)
अणु
	अचिन्हित lbaf = id->flbas & NVME_NS_FLBAS_LBA_MASK;
	पूर्णांक ret;

	blk_mq_मुक्तze_queue(ns->disk->queue);
	ns->lba_shअगरt = id->lbaf[lbaf].ds;
	nvme_set_queue_limits(ns->ctrl, ns->queue);

	ret = nvme_configure_metadata(ns, id);
	अगर (ret)
		जाओ out_unमुक्तze;
	nvme_set_chunk_sectors(ns, id);
	nvme_update_disk_info(ns->disk, ns, id);

	अगर (ns->head->ids.csi == NVME_CSI_ZNS) अणु
		ret = nvme_update_zone_info(ns, lbaf);
		अगर (ret)
			जाओ out_unमुक्तze;
	पूर्ण

	blk_mq_unमुक्तze_queue(ns->disk->queue);

	अगर (blk_queue_is_zoned(ns->queue)) अणु
		ret = nvme_revalidate_zones(ns);
		अगर (ret && !nvme_first_scan(ns->disk))
			जाओ out;
	पूर्ण

	अगर (nvme_ns_head_multipath(ns->head)) अणु
		blk_mq_मुक्तze_queue(ns->head->disk->queue);
		nvme_update_disk_info(ns->head->disk, ns, id);
		blk_stack_limits(&ns->head->disk->queue->limits,
				 &ns->queue->limits, 0);
		blk_queue_update_पढ़ोahead(ns->head->disk->queue);
		blk_mq_unमुक्तze_queue(ns->head->disk->queue);
	पूर्ण
	वापस 0;

out_unमुक्तze:
	blk_mq_unमुक्तze_queue(ns->disk->queue);
out:
	/*
	 * If probing fails due an unsupported feature, hide the block device,
	 * but still allow other access.
	 */
	अगर (ret == -ENODEV) अणु
		ns->disk->flags |= GENHD_FL_HIDDEN;
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

अटल अक्षर nvme_pr_type(क्रमागत pr_type type)
अणु
	चयन (type) अणु
	हाल PR_WRITE_EXCLUSIVE:
		वापस 1;
	हाल PR_EXCLUSIVE_ACCESS:
		वापस 2;
	हाल PR_WRITE_EXCLUSIVE_REG_ONLY:
		वापस 3;
	हाल PR_EXCLUSIVE_ACCESS_REG_ONLY:
		वापस 4;
	हाल PR_WRITE_EXCLUSIVE_ALL_REGS:
		वापस 5;
	हाल PR_EXCLUSIVE_ACCESS_ALL_REGS:
		वापस 6;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण;

अटल पूर्णांक nvme_pr_command(काष्ठा block_device *bdev, u32 cdw10,
				u64 key, u64 sa_key, u8 op)
अणु
	काष्ठा nvme_ns_head *head = शून्य;
	काष्ठा nvme_ns *ns;
	काष्ठा nvme_command c;
	पूर्णांक srcu_idx, ret;
	u8 data[16] = अणु 0, पूर्ण;

	ns = nvme_get_ns_from_disk(bdev->bd_disk, &head, &srcu_idx);
	अगर (unlikely(!ns))
		वापस -EWOULDBLOCK;

	put_unaligned_le64(key, &data[0]);
	put_unaligned_le64(sa_key, &data[8]);

	स_रखो(&c, 0, माप(c));
	c.common.opcode = op;
	c.common.nsid = cpu_to_le32(ns->head->ns_id);
	c.common.cdw10 = cpu_to_le32(cdw10);

	ret = nvme_submit_sync_cmd(ns->queue, &c, data, 16);
	nvme_put_ns_from_disk(head, srcu_idx);
	वापस ret;
पूर्ण

अटल पूर्णांक nvme_pr_रेजिस्टर(काष्ठा block_device *bdev, u64 old,
		u64 new, अचिन्हित flags)
अणु
	u32 cdw10;

	अगर (flags & ~PR_FL_IGNORE_KEY)
		वापस -EOPNOTSUPP;

	cdw10 = old ? 2 : 0;
	cdw10 |= (flags & PR_FL_IGNORE_KEY) ? 1 << 3 : 0;
	cdw10 |= (1 << 30) | (1 << 31); /* PTPL=1 */
	वापस nvme_pr_command(bdev, cdw10, old, new, nvme_cmd_resv_रेजिस्टर);
पूर्ण

अटल पूर्णांक nvme_pr_reserve(काष्ठा block_device *bdev, u64 key,
		क्रमागत pr_type type, अचिन्हित flags)
अणु
	u32 cdw10;

	अगर (flags & ~PR_FL_IGNORE_KEY)
		वापस -EOPNOTSUPP;

	cdw10 = nvme_pr_type(type) << 8;
	cdw10 |= ((flags & PR_FL_IGNORE_KEY) ? 1 << 3 : 0);
	वापस nvme_pr_command(bdev, cdw10, key, 0, nvme_cmd_resv_acquire);
पूर्ण

अटल पूर्णांक nvme_pr_preempt(काष्ठा block_device *bdev, u64 old, u64 new,
		क्रमागत pr_type type, bool पात)
अणु
	u32 cdw10 = nvme_pr_type(type) << 8 | (पात ? 2 : 1);

	वापस nvme_pr_command(bdev, cdw10, old, new, nvme_cmd_resv_acquire);
पूर्ण

अटल पूर्णांक nvme_pr_clear(काष्ठा block_device *bdev, u64 key)
अणु
	u32 cdw10 = 1 | (key ? 1 << 3 : 0);

	वापस nvme_pr_command(bdev, cdw10, key, 0, nvme_cmd_resv_रेजिस्टर);
पूर्ण

अटल पूर्णांक nvme_pr_release(काष्ठा block_device *bdev, u64 key, क्रमागत pr_type type)
अणु
	u32 cdw10 = nvme_pr_type(type) << 8 | (key ? 1 << 3 : 0);

	वापस nvme_pr_command(bdev, cdw10, key, 0, nvme_cmd_resv_release);
पूर्ण

स्थिर काष्ठा pr_ops nvme_pr_ops = अणु
	.pr_रेजिस्टर	= nvme_pr_रेजिस्टर,
	.pr_reserve	= nvme_pr_reserve,
	.pr_release	= nvme_pr_release,
	.pr_preempt	= nvme_pr_preempt,
	.pr_clear	= nvme_pr_clear,
पूर्ण;

#अगर_घोषित CONFIG_BLK_SED_OPAL
पूर्णांक nvme_sec_submit(व्योम *data, u16 spsp, u8 secp, व्योम *buffer, माप_प्रकार len,
		bool send)
अणु
	काष्ठा nvme_ctrl *ctrl = data;
	काष्ठा nvme_command cmd;

	स_रखो(&cmd, 0, माप(cmd));
	अगर (send)
		cmd.common.opcode = nvme_admin_security_send;
	अन्यथा
		cmd.common.opcode = nvme_admin_security_recv;
	cmd.common.nsid = 0;
	cmd.common.cdw10 = cpu_to_le32(((u32)secp) << 24 | ((u32)spsp) << 8);
	cmd.common.cdw11 = cpu_to_le32(len);

	वापस __nvme_submit_sync_cmd(ctrl->admin_q, &cmd, शून्य, buffer, len, 0,
			NVME_QID_ANY, 1, 0, false);
पूर्ण
EXPORT_SYMBOL_GPL(nvme_sec_submit);
#पूर्ण_अगर /* CONFIG_BLK_SED_OPAL */

अटल स्थिर काष्ठा block_device_operations nvme_bdev_ops = अणु
	.owner		= THIS_MODULE,
	.ioctl		= nvme_ioctl,
	.खोलो		= nvme_खोलो,
	.release	= nvme_release,
	.getgeo		= nvme_getgeo,
	.report_zones	= nvme_report_zones,
	.pr_ops		= &nvme_pr_ops,
पूर्ण;

अटल पूर्णांक nvme_रुको_पढ़ोy(काष्ठा nvme_ctrl *ctrl, u64 cap, bool enabled)
अणु
	अचिन्हित दीर्घ समयout =
		((NVME_CAP_TIMEOUT(cap) + 1) * HZ / 2) + jअगरfies;
	u32 csts, bit = enabled ? NVME_CSTS_RDY : 0;
	पूर्णांक ret;

	जबतक ((ret = ctrl->ops->reg_पढ़ो32(ctrl, NVME_REG_CSTS, &csts)) == 0) अणु
		अगर (csts == ~0)
			वापस -ENODEV;
		अगर ((csts & NVME_CSTS_RDY) == bit)
			अवरोध;

		usleep_range(1000, 2000);
		अगर (fatal_संकेत_pending(current))
			वापस -EINTR;
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_err(ctrl->device,
				"Device not ready; aborting %s, CSTS=0x%x\n",
				enabled ? "initialisation" : "reset", csts);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * If the device has been passed off to us in an enabled state, just clear
 * the enabled bit.  The spec says we should set the 'shutकरोwn notअगरication
 * bits', but करोing so may cause the device to complete commands to the
 * admin queue ... and we करोn't know what memory that might be poपूर्णांकing at!
 */
पूर्णांक nvme_disable_ctrl(काष्ठा nvme_ctrl *ctrl)
अणु
	पूर्णांक ret;

	ctrl->ctrl_config &= ~NVME_CC_SHN_MASK;
	ctrl->ctrl_config &= ~NVME_CC_ENABLE;

	ret = ctrl->ops->reg_ग_लिखो32(ctrl, NVME_REG_CC, ctrl->ctrl_config);
	अगर (ret)
		वापस ret;

	अगर (ctrl->quirks & NVME_QUIRK_DELAY_BEFORE_CHK_RDY)
		msleep(NVME_QUIRK_DELAY_AMOUNT);

	वापस nvme_रुको_पढ़ोy(ctrl, ctrl->cap, false);
पूर्ण
EXPORT_SYMBOL_GPL(nvme_disable_ctrl);

पूर्णांक nvme_enable_ctrl(काष्ठा nvme_ctrl *ctrl)
अणु
	अचिन्हित dev_page_min;
	पूर्णांक ret;

	ret = ctrl->ops->reg_पढ़ो64(ctrl, NVME_REG_CAP, &ctrl->cap);
	अगर (ret) अणु
		dev_err(ctrl->device, "Reading CAP failed (%d)\n", ret);
		वापस ret;
	पूर्ण
	dev_page_min = NVME_CAP_MPSMIN(ctrl->cap) + 12;

	अगर (NVME_CTRL_PAGE_SHIFT < dev_page_min) अणु
		dev_err(ctrl->device,
			"Minimum device page size %u too large for host (%u)\n",
			1 << dev_page_min, 1 << NVME_CTRL_PAGE_SHIFT);
		वापस -ENODEV;
	पूर्ण

	अगर (NVME_CAP_CSS(ctrl->cap) & NVME_CAP_CSS_CSI)
		ctrl->ctrl_config = NVME_CC_CSS_CSI;
	अन्यथा
		ctrl->ctrl_config = NVME_CC_CSS_NVM;
	ctrl->ctrl_config |= (NVME_CTRL_PAGE_SHIFT - 12) << NVME_CC_MPS_SHIFT;
	ctrl->ctrl_config |= NVME_CC_AMS_RR | NVME_CC_SHN_NONE;
	ctrl->ctrl_config |= NVME_CC_IOSQES | NVME_CC_IOCQES;
	ctrl->ctrl_config |= NVME_CC_ENABLE;

	ret = ctrl->ops->reg_ग_लिखो32(ctrl, NVME_REG_CC, ctrl->ctrl_config);
	अगर (ret)
		वापस ret;
	वापस nvme_रुको_पढ़ोy(ctrl, ctrl->cap, true);
पूर्ण
EXPORT_SYMBOL_GPL(nvme_enable_ctrl);

पूर्णांक nvme_shutकरोwn_ctrl(काष्ठा nvme_ctrl *ctrl)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + (ctrl->shutकरोwn_समयout * HZ);
	u32 csts;
	पूर्णांक ret;

	ctrl->ctrl_config &= ~NVME_CC_SHN_MASK;
	ctrl->ctrl_config |= NVME_CC_SHN_NORMAL;

	ret = ctrl->ops->reg_ग_लिखो32(ctrl, NVME_REG_CC, ctrl->ctrl_config);
	अगर (ret)
		वापस ret;

	जबतक ((ret = ctrl->ops->reg_पढ़ो32(ctrl, NVME_REG_CSTS, &csts)) == 0) अणु
		अगर ((csts & NVME_CSTS_SHST_MASK) == NVME_CSTS_SHST_CMPLT)
			अवरोध;

		msleep(100);
		अगर (fatal_संकेत_pending(current))
			वापस -EINTR;
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_err(ctrl->device,
				"Device shutdown incomplete; abort shutdown\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nvme_shutकरोwn_ctrl);

अटल पूर्णांक nvme_configure_बारtamp(काष्ठा nvme_ctrl *ctrl)
अणु
	__le64 ts;
	पूर्णांक ret;

	अगर (!(ctrl->oncs & NVME_CTRL_ONCS_TIMESTAMP))
		वापस 0;

	ts = cpu_to_le64(kसमय_प्रकारo_ms(kसमय_get_real()));
	ret = nvme_set_features(ctrl, NVME_FEAT_TIMESTAMP, 0, &ts, माप(ts),
			शून्य);
	अगर (ret)
		dev_warn_once(ctrl->device,
			"could not set timestamp (%d)\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक nvme_configure_acre(काष्ठा nvme_ctrl *ctrl)
अणु
	काष्ठा nvme_feat_host_behavior *host;
	पूर्णांक ret;

	/* Don't bother enabling the feature अगर retry delay is not reported */
	अगर (!ctrl->crdt[0])
		वापस 0;

	host = kzalloc(माप(*host), GFP_KERNEL);
	अगर (!host)
		वापस 0;

	host->acre = NVME_ENABLE_ACRE;
	ret = nvme_set_features(ctrl, NVME_FEAT_HOST_BEHAVIOR, 0,
				host, माप(*host), शून्य);
	kमुक्त(host);
	वापस ret;
पूर्ण

/*
 * APST (Autonomous Power State Transition) lets us program a table of घातer
 * state transitions that the controller will perक्रमm स्वतःmatically.
 * We configure it with a simple heuristic: we are willing to spend at most 2%
 * of the समय transitioning between घातer states.  Thereक्रमe, when running in
 * any given state, we will enter the next lower-घातer non-operational state
 * after रुकोing 50 * (enlat + exlat) microseconds, as दीर्घ as that state's निकास
 * latency is under the requested maximum latency.
 *
 * We will not स्वतःnomously enter any non-operational state क्रम which the total
 * latency exceeds ps_max_latency_us.
 *
 * Users can set ps_max_latency_us to zero to turn off APST.
 */
अटल पूर्णांक nvme_configure_apst(काष्ठा nvme_ctrl *ctrl)
अणु
	काष्ठा nvme_feat_स्वतः_pst *table;
	अचिन्हित apste = 0;
	u64 max_lat_us = 0;
	__le64 target = 0;
	पूर्णांक max_ps = -1;
	पूर्णांक state;
	पूर्णांक ret;

	/*
	 * If APST isn't supported or if we haven't been initialized yet,
	 * then करोn't करो anything.
	 */
	अगर (!ctrl->apsta)
		वापस 0;

	अगर (ctrl->npss > 31) अणु
		dev_warn(ctrl->device, "NPSS is invalid; not using APST\n");
		वापस 0;
	पूर्ण

	table = kzalloc(माप(*table), GFP_KERNEL);
	अगर (!table)
		वापस 0;

	अगर (!ctrl->apst_enabled || ctrl->ps_max_latency_us == 0) अणु
		/* Turn off APST. */
		dev_dbg(ctrl->device, "APST disabled\n");
		जाओ करोne;
	पूर्ण

	/*
	 * Walk through all states from lowest- to highest-घातer.
	 * According to the spec, lower-numbered states use more घातer.  NPSS,
	 * despite the name, is the index of the lowest-घातer state, not the
	 * number of states.
	 */
	क्रम (state = (पूर्णांक)ctrl->npss; state >= 0; state--) अणु
		u64 total_latency_us, निकास_latency_us, transition_ms;

		अगर (target)
			table->entries[state] = target;

		/*
		 * Don't allow transitions to the deepest state if it's quirked
		 * off.
		 */
		अगर (state == ctrl->npss &&
		    (ctrl->quirks & NVME_QUIRK_NO_DEEPEST_PS))
			जारी;

		/*
		 * Is this state a useful non-operational state क्रम higher-घातer
		 * states to स्वतःnomously transition to?
		 */
		अगर (!(ctrl->psd[state].flags & NVME_PS_FLAGS_NON_OP_STATE))
			जारी;

		निकास_latency_us = (u64)le32_to_cpu(ctrl->psd[state].निकास_lat);
		अगर (निकास_latency_us > ctrl->ps_max_latency_us)
			जारी;

		total_latency_us = निकास_latency_us +
			le32_to_cpu(ctrl->psd[state].entry_lat);

		/*
		 * This state is good.  Use it as the APST idle target क्रम
		 * higher घातer states.
		 */
		transition_ms = total_latency_us + 19;
		करो_भाग(transition_ms, 20);
		अगर (transition_ms > (1 << 24) - 1)
			transition_ms = (1 << 24) - 1;

		target = cpu_to_le64((state << 3) | (transition_ms << 8));
		अगर (max_ps == -1)
			max_ps = state;
		अगर (total_latency_us > max_lat_us)
			max_lat_us = total_latency_us;
	पूर्ण

	अगर (max_ps == -1)
		dev_dbg(ctrl->device, "APST enabled but no non-operational states are available\n");
	अन्यथा
		dev_dbg(ctrl->device, "APST enabled: max PS = %d, max round-trip latency = %lluus, table = %*phN\n",
			max_ps, max_lat_us, (पूर्णांक)माप(*table), table);
	apste = 1;

करोne:
	ret = nvme_set_features(ctrl, NVME_FEAT_AUTO_PST, apste,
				table, माप(*table), शून्य);
	अगर (ret)
		dev_err(ctrl->device, "failed to set APST feature (%d)\n", ret);
	kमुक्त(table);
	वापस ret;
पूर्ण

अटल व्योम nvme_set_latency_tolerance(काष्ठा device *dev, s32 val)
अणु
	काष्ठा nvme_ctrl *ctrl = dev_get_drvdata(dev);
	u64 latency;

	चयन (val) अणु
	हाल PM_QOS_LATENCY_TOLERANCE_NO_CONSTRAINT:
	हाल PM_QOS_LATENCY_ANY:
		latency = U64_MAX;
		अवरोध;

	शेष:
		latency = val;
	पूर्ण

	अगर (ctrl->ps_max_latency_us != latency) अणु
		ctrl->ps_max_latency_us = latency;
		अगर (ctrl->state == NVME_CTRL_LIVE)
			nvme_configure_apst(ctrl);
	पूर्ण
पूर्ण

काष्ठा nvme_core_quirk_entry अणु
	/*
	 * NVMe model and firmware strings are padded with spaces.  For
	 * simplicity, strings in the quirk table are padded with शून्यs
	 * instead.
	 */
	u16 vid;
	स्थिर अक्षर *mn;
	स्थिर अक्षर *fr;
	अचिन्हित दीर्घ quirks;
पूर्ण;

अटल स्थिर काष्ठा nvme_core_quirk_entry core_quirks[] = अणु
	अणु
		/*
		 * This Toshiba device seems to die using any APST states.  See:
		 * https://bugs.launchpad.net/ubuntu/+source/linux/+bug/1678184/comments/11
		 */
		.vid = 0x1179,
		.mn = "THNSF5256GPUK TOSHIBA",
		.quirks = NVME_QUIRK_NO_APST,
	पूर्ण,
	अणु
		/*
		 * This LiteON CL1-3D*-Q11 firmware version has a race
		 * condition associated with actions related to suspend to idle
		 * LiteON has resolved the problem in future firmware
		 */
		.vid = 0x14a4,
		.fr = "22301111",
		.quirks = NVME_QUIRK_SIMPLE_SUSPEND,
	पूर्ण
पूर्ण;

/* match is null-terminated but idstr is space-padded. */
अटल bool string_matches(स्थिर अक्षर *idstr, स्थिर अक्षर *match, माप_प्रकार len)
अणु
	माप_प्रकार matchlen;

	अगर (!match)
		वापस true;

	matchlen = म_माप(match);
	WARN_ON_ONCE(matchlen > len);

	अगर (स_भेद(idstr, match, matchlen))
		वापस false;

	क्रम (; matchlen < len; matchlen++)
		अगर (idstr[matchlen] != ' ')
			वापस false;

	वापस true;
पूर्ण

अटल bool quirk_matches(स्थिर काष्ठा nvme_id_ctrl *id,
			  स्थिर काष्ठा nvme_core_quirk_entry *q)
अणु
	वापस q->vid == le16_to_cpu(id->vid) &&
		string_matches(id->mn, q->mn, माप(id->mn)) &&
		string_matches(id->fr, q->fr, माप(id->fr));
पूर्ण

अटल व्योम nvme_init_subnqn(काष्ठा nvme_subप्रणाली *subsys, काष्ठा nvme_ctrl *ctrl,
		काष्ठा nvme_id_ctrl *id)
अणु
	माप_प्रकार nqnlen;
	पूर्णांक off;

	अगर(!(ctrl->quirks & NVME_QUIRK_IGNORE_DEV_SUBNQN)) अणु
		nqnlen = strnlen(id->subnqn, NVMF_NQN_SIZE);
		अगर (nqnlen > 0 && nqnlen < NVMF_NQN_SIZE) अणु
			strlcpy(subsys->subnqn, id->subnqn, NVMF_NQN_SIZE);
			वापस;
		पूर्ण

		अगर (ctrl->vs >= NVME_VS(1, 2, 1))
			dev_warn(ctrl->device, "missing or invalid SUBNQN field.\n");
	पूर्ण

	/* Generate a "fake" NQN per Figure 254 in NVMe 1.3 + ECN 001 */
	off = snम_लिखो(subsys->subnqn, NVMF_NQN_SIZE,
			"nqn.2014.08.org.nvmexpress:%04x%04x",
			le16_to_cpu(id->vid), le16_to_cpu(id->ssvid));
	स_नकल(subsys->subnqn + off, id->sn, माप(id->sn));
	off += माप(id->sn);
	स_नकल(subsys->subnqn + off, id->mn, माप(id->mn));
	off += माप(id->mn);
	स_रखो(subsys->subnqn + off, 0, माप(subsys->subnqn) - off);
पूर्ण

अटल व्योम nvme_release_subप्रणाली(काष्ठा device *dev)
अणु
	काष्ठा nvme_subप्रणाली *subsys =
		container_of(dev, काष्ठा nvme_subप्रणाली, dev);

	अगर (subsys->instance >= 0)
		ida_simple_हटाओ(&nvme_instance_ida, subsys->instance);
	kमुक्त(subsys);
पूर्ण

अटल व्योम nvme_destroy_subप्रणाली(काष्ठा kref *ref)
अणु
	काष्ठा nvme_subप्रणाली *subsys =
			container_of(ref, काष्ठा nvme_subप्रणाली, ref);

	mutex_lock(&nvme_subप्रणालीs_lock);
	list_del(&subsys->entry);
	mutex_unlock(&nvme_subप्रणालीs_lock);

	ida_destroy(&subsys->ns_ida);
	device_del(&subsys->dev);
	put_device(&subsys->dev);
पूर्ण

अटल व्योम nvme_put_subप्रणाली(काष्ठा nvme_subप्रणाली *subsys)
अणु
	kref_put(&subsys->ref, nvme_destroy_subप्रणाली);
पूर्ण

अटल काष्ठा nvme_subप्रणाली *__nvme_find_get_subप्रणाली(स्थिर अक्षर *subsysnqn)
अणु
	काष्ठा nvme_subप्रणाली *subsys;

	lockdep_निश्चित_held(&nvme_subप्रणालीs_lock);

	/*
	 * Fail matches क्रम discovery subप्रणालीs. This results
	 * in each discovery controller bound to a unique subप्रणाली.
	 * This aव्योमs issues with validating controller values
	 * that can only be true when there is a single unique subप्रणाली.
	 * There may be multiple and completely independent entities
	 * that provide discovery controllers.
	 */
	अगर (!म_भेद(subsysnqn, NVME_DISC_SUBSYS_NAME))
		वापस शून्य;

	list_क्रम_each_entry(subsys, &nvme_subप्रणालीs, entry) अणु
		अगर (म_भेद(subsys->subnqn, subsysnqn))
			जारी;
		अगर (!kref_get_unless_zero(&subsys->ref))
			जारी;
		वापस subsys;
	पूर्ण

	वापस शून्य;
पूर्ण

#घोषणा SUBSYS_ATTR_RO(_name, _mode, _show)			\
	काष्ठा device_attribute subsys_attr_##_name = \
		__ATTR(_name, _mode, _show, शून्य)

अटल sमाप_प्रकार nvme_subsys_show_nqn(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा nvme_subप्रणाली *subsys =
		container_of(dev, काष्ठा nvme_subप्रणाली, dev);

	वापस sysfs_emit(buf, "%s\n", subsys->subnqn);
पूर्ण
अटल SUBSYS_ATTR_RO(subsysnqn, S_IRUGO, nvme_subsys_show_nqn);

#घोषणा nvme_subsys_show_str_function(field)				\
अटल sमाप_प्रकार subsys_##field##_show(काष्ठा device *dev,		\
			    काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा nvme_subप्रणाली *subsys =					\
		container_of(dev, काष्ठा nvme_subप्रणाली, dev);		\
	वापस sysfs_emit(buf, "%.*s\n",				\
			   (पूर्णांक)माप(subsys->field), subsys->field);	\
पूर्ण									\
अटल SUBSYS_ATTR_RO(field, S_IRUGO, subsys_##field##_show);

nvme_subsys_show_str_function(model);
nvme_subsys_show_str_function(serial);
nvme_subsys_show_str_function(firmware_rev);

अटल काष्ठा attribute *nvme_subsys_attrs[] = अणु
	&subsys_attr_model.attr,
	&subsys_attr_serial.attr,
	&subsys_attr_firmware_rev.attr,
	&subsys_attr_subsysnqn.attr,
#अगर_घोषित CONFIG_NVME_MULTIPATH
	&subsys_attr_iopolicy.attr,
#पूर्ण_अगर
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group nvme_subsys_attrs_group = अणु
	.attrs = nvme_subsys_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *nvme_subsys_attrs_groups[] = अणु
	&nvme_subsys_attrs_group,
	शून्य,
पूर्ण;

अटल अंतरभूत bool nvme_discovery_ctrl(काष्ठा nvme_ctrl *ctrl)
अणु
	वापस ctrl->opts && ctrl->opts->discovery_nqn;
पूर्ण

अटल bool nvme_validate_cntlid(काष्ठा nvme_subप्रणाली *subsys,
		काष्ठा nvme_ctrl *ctrl, काष्ठा nvme_id_ctrl *id)
अणु
	काष्ठा nvme_ctrl *पंचांगp;

	lockdep_निश्चित_held(&nvme_subप्रणालीs_lock);

	list_क्रम_each_entry(पंचांगp, &subsys->ctrls, subsys_entry) अणु
		अगर (nvme_state_terminal(पंचांगp))
			जारी;

		अगर (पंचांगp->cntlid == ctrl->cntlid) अणु
			dev_err(ctrl->device,
				"Duplicate cntlid %u with %s, rejecting\n",
				ctrl->cntlid, dev_name(पंचांगp->device));
			वापस false;
		पूर्ण

		अगर ((id->cmic & NVME_CTRL_CMIC_MULTI_CTRL) ||
		    nvme_discovery_ctrl(ctrl))
			जारी;

		dev_err(ctrl->device,
			"Subsystem does not support multiple controllers\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक nvme_init_subप्रणाली(काष्ठा nvme_ctrl *ctrl, काष्ठा nvme_id_ctrl *id)
अणु
	काष्ठा nvme_subप्रणाली *subsys, *found;
	पूर्णांक ret;

	subsys = kzalloc(माप(*subsys), GFP_KERNEL);
	अगर (!subsys)
		वापस -ENOMEM;

	subsys->instance = -1;
	mutex_init(&subsys->lock);
	kref_init(&subsys->ref);
	INIT_LIST_HEAD(&subsys->ctrls);
	INIT_LIST_HEAD(&subsys->nsheads);
	nvme_init_subnqn(subsys, ctrl, id);
	स_नकल(subsys->serial, id->sn, माप(subsys->serial));
	स_नकल(subsys->model, id->mn, माप(subsys->model));
	स_नकल(subsys->firmware_rev, id->fr, माप(subsys->firmware_rev));
	subsys->venकरोr_id = le16_to_cpu(id->vid);
	subsys->cmic = id->cmic;
	subsys->awupf = le16_to_cpu(id->awupf);
#अगर_घोषित CONFIG_NVME_MULTIPATH
	subsys->iopolicy = NVME_IOPOLICY_NUMA;
#पूर्ण_अगर

	subsys->dev.class = nvme_subsys_class;
	subsys->dev.release = nvme_release_subप्रणाली;
	subsys->dev.groups = nvme_subsys_attrs_groups;
	dev_set_name(&subsys->dev, "nvme-subsys%d", ctrl->instance);
	device_initialize(&subsys->dev);

	mutex_lock(&nvme_subप्रणालीs_lock);
	found = __nvme_find_get_subप्रणाली(subsys->subnqn);
	अगर (found) अणु
		put_device(&subsys->dev);
		subsys = found;

		अगर (!nvme_validate_cntlid(subsys, ctrl, id)) अणु
			ret = -EINVAL;
			जाओ out_put_subप्रणाली;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = device_add(&subsys->dev);
		अगर (ret) अणु
			dev_err(ctrl->device,
				"failed to register subsystem device.\n");
			put_device(&subsys->dev);
			जाओ out_unlock;
		पूर्ण
		ida_init(&subsys->ns_ida);
		list_add_tail(&subsys->entry, &nvme_subप्रणालीs);
	पूर्ण

	ret = sysfs_create_link(&subsys->dev.kobj, &ctrl->device->kobj,
				dev_name(ctrl->device));
	अगर (ret) अणु
		dev_err(ctrl->device,
			"failed to create sysfs link from subsystem.\n");
		जाओ out_put_subप्रणाली;
	पूर्ण

	अगर (!found)
		subsys->instance = ctrl->instance;
	ctrl->subsys = subsys;
	list_add_tail(&ctrl->subsys_entry, &subsys->ctrls);
	mutex_unlock(&nvme_subप्रणालीs_lock);
	वापस 0;

out_put_subप्रणाली:
	nvme_put_subप्रणाली(subsys);
out_unlock:
	mutex_unlock(&nvme_subप्रणालीs_lock);
	वापस ret;
पूर्ण

पूर्णांक nvme_get_log(काष्ठा nvme_ctrl *ctrl, u32 nsid, u8 log_page, u8 lsp, u8 csi,
		व्योम *log, माप_प्रकार size, u64 offset)
अणु
	काष्ठा nvme_command c = अणु पूर्ण;
	u32 dwlen = nvme_bytes_to_numd(size);

	c.get_log_page.opcode = nvme_admin_get_log_page;
	c.get_log_page.nsid = cpu_to_le32(nsid);
	c.get_log_page.lid = log_page;
	c.get_log_page.lsp = lsp;
	c.get_log_page.numdl = cpu_to_le16(dwlen & ((1 << 16) - 1));
	c.get_log_page.numdu = cpu_to_le16(dwlen >> 16);
	c.get_log_page.lpol = cpu_to_le32(lower_32_bits(offset));
	c.get_log_page.lpou = cpu_to_le32(upper_32_bits(offset));
	c.get_log_page.csi = csi;

	वापस nvme_submit_sync_cmd(ctrl->admin_q, &c, log, size);
पूर्ण

अटल पूर्णांक nvme_get_effects_log(काष्ठा nvme_ctrl *ctrl, u8 csi,
				काष्ठा nvme_effects_log **log)
अणु
	काष्ठा nvme_effects_log	*cel = xa_load(&ctrl->cels, csi);
	पूर्णांक ret;

	अगर (cel)
		जाओ out;

	cel = kzalloc(माप(*cel), GFP_KERNEL);
	अगर (!cel)
		वापस -ENOMEM;

	ret = nvme_get_log(ctrl, 0x00, NVME_LOG_CMD_EFFECTS, 0, csi,
			cel, माप(*cel), 0);
	अगर (ret) अणु
		kमुक्त(cel);
		वापस ret;
	पूर्ण

	xa_store(&ctrl->cels, csi, cel, GFP_KERNEL);
out:
	*log = cel;
	वापस 0;
पूर्ण

अटल अंतरभूत u32 nvme_mps_to_sectors(काष्ठा nvme_ctrl *ctrl, u32 units)
अणु
	u32 page_shअगरt = NVME_CAP_MPSMIN(ctrl->cap) + 12, val;

	अगर (check_shl_overflow(1U, units + page_shअगरt - 9, &val))
		वापस अच_पूर्णांक_उच्च;
	वापस val;
पूर्ण

अटल पूर्णांक nvme_init_non_mdts_limits(काष्ठा nvme_ctrl *ctrl)
अणु
	काष्ठा nvme_command c = अणु पूर्ण;
	काष्ठा nvme_id_ctrl_nvm *id;
	पूर्णांक ret;

	अगर (ctrl->oncs & NVME_CTRL_ONCS_DSM) अणु
		ctrl->max_discard_sectors = अच_पूर्णांक_उच्च;
		ctrl->max_discard_segments = NVME_DSM_MAX_RANGES;
	पूर्ण अन्यथा अणु
		ctrl->max_discard_sectors = 0;
		ctrl->max_discard_segments = 0;
	पूर्ण

	/*
	 * Even though NVMe spec explicitly states that MDTS is not applicable
	 * to the ग_लिखो-zeroes, we are cautious and limit the size to the
	 * controllers max_hw_sectors value, which is based on the MDTS field
	 * and possibly other limiting factors.
	 */
	अगर ((ctrl->oncs & NVME_CTRL_ONCS_WRITE_ZEROES) &&
	    !(ctrl->quirks & NVME_QUIRK_DISABLE_WRITE_ZEROES))
		ctrl->max_zeroes_sectors = ctrl->max_hw_sectors;
	अन्यथा
		ctrl->max_zeroes_sectors = 0;

	अगर (nvme_ctrl_limited_cns(ctrl))
		वापस 0;

	id = kzalloc(माप(*id), GFP_KERNEL);
	अगर (!id)
		वापस 0;

	c.identअगरy.opcode = nvme_admin_identअगरy;
	c.identअगरy.cns = NVME_ID_CNS_CS_CTRL;
	c.identअगरy.csi = NVME_CSI_NVM;

	ret = nvme_submit_sync_cmd(ctrl->admin_q, &c, id, माप(*id));
	अगर (ret)
		जाओ मुक्त_data;

	अगर (id->dmrl)
		ctrl->max_discard_segments = id->dmrl;
	अगर (id->dmrsl)
		ctrl->max_discard_sectors = le32_to_cpu(id->dmrsl);
	अगर (id->wzsl)
		ctrl->max_zeroes_sectors = nvme_mps_to_sectors(ctrl, id->wzsl);

मुक्त_data:
	kमुक्त(id);
	वापस ret;
पूर्ण

अटल पूर्णांक nvme_init_identअगरy(काष्ठा nvme_ctrl *ctrl)
अणु
	काष्ठा nvme_id_ctrl *id;
	u32 max_hw_sectors;
	bool prev_apst_enabled;
	पूर्णांक ret;

	ret = nvme_identअगरy_ctrl(ctrl, &id);
	अगर (ret) अणु
		dev_err(ctrl->device, "Identify Controller failed (%d)\n", ret);
		वापस -EIO;
	पूर्ण

	अगर (id->lpa & NVME_CTRL_LPA_CMD_EFFECTS_LOG) अणु
		ret = nvme_get_effects_log(ctrl, NVME_CSI_NVM, &ctrl->effects);
		अगर (ret < 0)
			जाओ out_मुक्त;
	पूर्ण

	अगर (!(ctrl->ops->flags & NVME_F_FABRICS))
		ctrl->cntlid = le16_to_cpu(id->cntlid);

	अगर (!ctrl->identअगरied) अणु
		अचिन्हित पूर्णांक i;

		ret = nvme_init_subप्रणाली(ctrl, id);
		अगर (ret)
			जाओ out_मुक्त;

		/*
		 * Check क्रम quirks.  Quirk can depend on firmware version,
		 * so, in principle, the set of quirks present can change
		 * across a reset.  As a possible future enhancement, we
		 * could re-scan क्रम quirks every समय we reinitialize
		 * the device, but we'd have to make sure that the driver
		 * behaves पूर्णांकelligently अगर the quirks change.
		 */
		क्रम (i = 0; i < ARRAY_SIZE(core_quirks); i++) अणु
			अगर (quirk_matches(id, &core_quirks[i]))
				ctrl->quirks |= core_quirks[i].quirks;
		पूर्ण
	पूर्ण

	अगर (क्रमce_apst && (ctrl->quirks & NVME_QUIRK_NO_DEEPEST_PS)) अणु
		dev_warn(ctrl->device, "forcibly allowing all power states due to nvme_core.force_apst -- use at your own risk\n");
		ctrl->quirks &= ~NVME_QUIRK_NO_DEEPEST_PS;
	पूर्ण

	ctrl->crdt[0] = le16_to_cpu(id->crdt1);
	ctrl->crdt[1] = le16_to_cpu(id->crdt2);
	ctrl->crdt[2] = le16_to_cpu(id->crdt3);

	ctrl->oacs = le16_to_cpu(id->oacs);
	ctrl->oncs = le16_to_cpu(id->oncs);
	ctrl->mtfa = le16_to_cpu(id->mtfa);
	ctrl->oaes = le32_to_cpu(id->oaes);
	ctrl->wctemp = le16_to_cpu(id->wctemp);
	ctrl->cctemp = le16_to_cpu(id->cctemp);

	atomic_set(&ctrl->पात_limit, id->acl + 1);
	ctrl->vwc = id->vwc;
	अगर (id->mdts)
		max_hw_sectors = nvme_mps_to_sectors(ctrl, id->mdts);
	अन्यथा
		max_hw_sectors = अच_पूर्णांक_उच्च;
	ctrl->max_hw_sectors =
		min_not_zero(ctrl->max_hw_sectors, max_hw_sectors);

	nvme_set_queue_limits(ctrl, ctrl->admin_q);
	ctrl->sgls = le32_to_cpu(id->sgls);
	ctrl->kas = le16_to_cpu(id->kas);
	ctrl->max_namespaces = le32_to_cpu(id->mnan);
	ctrl->ctratt = le32_to_cpu(id->ctratt);

	अगर (id->rtd3e) अणु
		/* us -> s */
		u32 transition_समय = le32_to_cpu(id->rtd3e) / USEC_PER_SEC;

		ctrl->shutकरोwn_समयout = clamp_t(अचिन्हित पूर्णांक, transition_समय,
						 shutकरोwn_समयout, 60);

		अगर (ctrl->shutकरोwn_समयout != shutकरोwn_समयout)
			dev_info(ctrl->device,
				 "Shutdown timeout set to %u seconds\n",
				 ctrl->shutकरोwn_समयout);
	पूर्ण अन्यथा
		ctrl->shutकरोwn_समयout = shutकरोwn_समयout;

	ctrl->npss = id->npss;
	ctrl->apsta = id->apsta;
	prev_apst_enabled = ctrl->apst_enabled;
	अगर (ctrl->quirks & NVME_QUIRK_NO_APST) अणु
		अगर (क्रमce_apst && id->apsta) अणु
			dev_warn(ctrl->device, "forcibly allowing APST due to nvme_core.force_apst -- use at your own risk\n");
			ctrl->apst_enabled = true;
		पूर्ण अन्यथा अणु
			ctrl->apst_enabled = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		ctrl->apst_enabled = id->apsta;
	पूर्ण
	स_नकल(ctrl->psd, id->psd, माप(ctrl->psd));

	अगर (ctrl->ops->flags & NVME_F_FABRICS) अणु
		ctrl->icकरोff = le16_to_cpu(id->icकरोff);
		ctrl->ioccsz = le32_to_cpu(id->ioccsz);
		ctrl->iorcsz = le32_to_cpu(id->iorcsz);
		ctrl->maxcmd = le16_to_cpu(id->maxcmd);

		/*
		 * In fabrics we need to verअगरy the cntlid matches the
		 * admin connect
		 */
		अगर (ctrl->cntlid != le16_to_cpu(id->cntlid)) अणु
			dev_err(ctrl->device,
				"Mismatching cntlid: Connect %u vs Identify "
				"%u, rejecting\n",
				ctrl->cntlid, le16_to_cpu(id->cntlid));
			ret = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण

		अगर (!nvme_discovery_ctrl(ctrl) && !ctrl->kas) अणु
			dev_err(ctrl->device,
				"keep-alive support is mandatory for fabrics\n");
			ret = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण अन्यथा अणु
		ctrl->hmpre = le32_to_cpu(id->hmpre);
		ctrl->hmmin = le32_to_cpu(id->hmmin);
		ctrl->hmminds = le32_to_cpu(id->hmminds);
		ctrl->hmmaxd = le16_to_cpu(id->hmmaxd);
	पूर्ण

	ret = nvme_mpath_init_identअगरy(ctrl, id);
	अगर (ret < 0)
		जाओ out_मुक्त;

	अगर (ctrl->apst_enabled && !prev_apst_enabled)
		dev_pm_qos_expose_latency_tolerance(ctrl->device);
	अन्यथा अगर (!ctrl->apst_enabled && prev_apst_enabled)
		dev_pm_qos_hide_latency_tolerance(ctrl->device);

out_मुक्त:
	kमुक्त(id);
	वापस ret;
पूर्ण

/*
 * Initialize the cached copies of the Identअगरy data and various controller
 * रेजिस्टर in our nvme_ctrl काष्ठाure.  This should be called as soon as
 * the admin queue is fully up and running.
 */
पूर्णांक nvme_init_ctrl_finish(काष्ठा nvme_ctrl *ctrl)
अणु
	पूर्णांक ret;

	ret = ctrl->ops->reg_पढ़ो32(ctrl, NVME_REG_VS, &ctrl->vs);
	अगर (ret) अणु
		dev_err(ctrl->device, "Reading VS failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	ctrl->sqsize = min_t(u16, NVME_CAP_MQES(ctrl->cap), ctrl->sqsize);

	अगर (ctrl->vs >= NVME_VS(1, 1, 0))
		ctrl->subप्रणाली = NVME_CAP_NSSRC(ctrl->cap);

	ret = nvme_init_identअगरy(ctrl);
	अगर (ret)
		वापस ret;

	ret = nvme_init_non_mdts_limits(ctrl);
	अगर (ret < 0)
		वापस ret;

	ret = nvme_configure_apst(ctrl);
	अगर (ret < 0)
		वापस ret;

	ret = nvme_configure_बारtamp(ctrl);
	अगर (ret < 0)
		वापस ret;

	ret = nvme_configure_directives(ctrl);
	अगर (ret < 0)
		वापस ret;

	ret = nvme_configure_acre(ctrl);
	अगर (ret < 0)
		वापस ret;

	अगर (!ctrl->identअगरied && !nvme_discovery_ctrl(ctrl)) अणु
		ret = nvme_hwmon_init(ctrl);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ctrl->identअगरied = true;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nvme_init_ctrl_finish);

अटल पूर्णांक nvme_dev_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा nvme_ctrl *ctrl =
		container_of(inode->i_cdev, काष्ठा nvme_ctrl, cdev);

	चयन (ctrl->state) अणु
	हाल NVME_CTRL_LIVE:
		अवरोध;
	शेष:
		वापस -EWOULDBLOCK;
	पूर्ण

	nvme_get_ctrl(ctrl);
	अगर (!try_module_get(ctrl->ops->module)) अणु
		nvme_put_ctrl(ctrl);
		वापस -EINVAL;
	पूर्ण

	file->निजी_data = ctrl;
	वापस 0;
पूर्ण

अटल पूर्णांक nvme_dev_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा nvme_ctrl *ctrl =
		container_of(inode->i_cdev, काष्ठा nvme_ctrl, cdev);

	module_put(ctrl->ops->module);
	nvme_put_ctrl(ctrl);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations nvme_dev_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= nvme_dev_खोलो,
	.release	= nvme_dev_release,
	.unlocked_ioctl	= nvme_dev_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
पूर्ण;

अटल sमाप_प्रकार nvme_sysfs_reset(काष्ठा device *dev,
				काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	काष्ठा nvme_ctrl *ctrl = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = nvme_reset_ctrl_sync(ctrl);
	अगर (ret < 0)
		वापस ret;
	वापस count;
पूर्ण
अटल DEVICE_ATTR(reset_controller, S_IWUSR, शून्य, nvme_sysfs_reset);

अटल sमाप_प्रकार nvme_sysfs_rescan(काष्ठा device *dev,
				काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	काष्ठा nvme_ctrl *ctrl = dev_get_drvdata(dev);

	nvme_queue_scan(ctrl);
	वापस count;
पूर्ण
अटल DEVICE_ATTR(rescan_controller, S_IWUSR, शून्य, nvme_sysfs_rescan);

अटल अंतरभूत काष्ठा nvme_ns_head *dev_to_ns_head(काष्ठा device *dev)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);

	अगर (disk->fops == &nvme_bdev_ops)
		वापस nvme_get_ns_from_dev(dev)->head;
	अन्यथा
		वापस disk->निजी_data;
पूर्ण

अटल sमाप_प्रकार wwid_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा nvme_ns_head *head = dev_to_ns_head(dev);
	काष्ठा nvme_ns_ids *ids = &head->ids;
	काष्ठा nvme_subप्रणाली *subsys = head->subsys;
	पूर्णांक serial_len = माप(subsys->serial);
	पूर्णांक model_len = माप(subsys->model);

	अगर (!uuid_is_null(&ids->uuid))
		वापस sysfs_emit(buf, "uuid.%pU\n", &ids->uuid);

	अगर (स_प्रथम_inv(ids->nguid, 0, माप(ids->nguid)))
		वापस sysfs_emit(buf, "eui.%16phN\n", ids->nguid);

	अगर (स_प्रथम_inv(ids->eui64, 0, माप(ids->eui64)))
		वापस sysfs_emit(buf, "eui.%8phN\n", ids->eui64);

	जबतक (serial_len > 0 && (subsys->serial[serial_len - 1] == ' ' ||
				  subsys->serial[serial_len - 1] == '\0'))
		serial_len--;
	जबतक (model_len > 0 && (subsys->model[model_len - 1] == ' ' ||
				 subsys->model[model_len - 1] == '\0'))
		model_len--;

	वापस sysfs_emit(buf, "nvme.%04x-%*phN-%*phN-%08x\n", subsys->venकरोr_id,
		serial_len, subsys->serial, model_len, subsys->model,
		head->ns_id);
पूर्ण
अटल DEVICE_ATTR_RO(wwid);

अटल sमाप_प्रकार nguid_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%pU\n", dev_to_ns_head(dev)->ids.nguid);
पूर्ण
अटल DEVICE_ATTR_RO(nguid);

अटल sमाप_प्रकार uuid_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा nvme_ns_ids *ids = &dev_to_ns_head(dev)->ids;

	/* For backward compatibility expose the NGUID to userspace अगर
	 * we have no UUID set
	 */
	अगर (uuid_is_null(&ids->uuid)) अणु
		prपूर्णांकk_ratelimited(KERN_WARNING
				   "No UUID available providing old NGUID\n");
		वापस sysfs_emit(buf, "%pU\n", ids->nguid);
	पूर्ण
	वापस sysfs_emit(buf, "%pU\n", &ids->uuid);
पूर्ण
अटल DEVICE_ATTR_RO(uuid);

अटल sमाप_प्रकार eui_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%8ph\n", dev_to_ns_head(dev)->ids.eui64);
पूर्ण
अटल DEVICE_ATTR_RO(eui);

अटल sमाप_प्रकार nsid_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", dev_to_ns_head(dev)->ns_id);
पूर्ण
अटल DEVICE_ATTR_RO(nsid);

अटल काष्ठा attribute *nvme_ns_id_attrs[] = अणु
	&dev_attr_wwid.attr,
	&dev_attr_uuid.attr,
	&dev_attr_nguid.attr,
	&dev_attr_eui.attr,
	&dev_attr_nsid.attr,
#अगर_घोषित CONFIG_NVME_MULTIPATH
	&dev_attr_ana_grpid.attr,
	&dev_attr_ana_state.attr,
#पूर्ण_अगर
	शून्य,
पूर्ण;

अटल umode_t nvme_ns_id_attrs_are_visible(काष्ठा kobject *kobj,
		काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा nvme_ns_ids *ids = &dev_to_ns_head(dev)->ids;

	अगर (a == &dev_attr_uuid.attr) अणु
		अगर (uuid_is_null(&ids->uuid) &&
		    !स_प्रथम_inv(ids->nguid, 0, माप(ids->nguid)))
			वापस 0;
	पूर्ण
	अगर (a == &dev_attr_nguid.attr) अणु
		अगर (!स_प्रथम_inv(ids->nguid, 0, माप(ids->nguid)))
			वापस 0;
	पूर्ण
	अगर (a == &dev_attr_eui.attr) अणु
		अगर (!स_प्रथम_inv(ids->eui64, 0, माप(ids->eui64)))
			वापस 0;
	पूर्ण
#अगर_घोषित CONFIG_NVME_MULTIPATH
	अगर (a == &dev_attr_ana_grpid.attr || a == &dev_attr_ana_state.attr) अणु
		अगर (dev_to_disk(dev)->fops != &nvme_bdev_ops) /* per-path attr */
			वापस 0;
		अगर (!nvme_ctrl_use_ana(nvme_get_ns_from_dev(dev)->ctrl))
			वापस 0;
	पूर्ण
#पूर्ण_अगर
	वापस a->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group nvme_ns_id_attr_group = अणु
	.attrs		= nvme_ns_id_attrs,
	.is_visible	= nvme_ns_id_attrs_are_visible,
पूर्ण;

स्थिर काष्ठा attribute_group *nvme_ns_id_attr_groups[] = अणु
	&nvme_ns_id_attr_group,
#अगर_घोषित CONFIG_NVM
	&nvme_nvm_attr_group,
#पूर्ण_अगर
	शून्य,
पूर्ण;

#घोषणा nvme_show_str_function(field)						\
अटल sमाप_प्रकार  field##_show(काष्ठा device *dev,				\
			    काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु										\
        काष्ठा nvme_ctrl *ctrl = dev_get_drvdata(dev);				\
        वापस sysfs_emit(buf, "%.*s\n",					\
		(पूर्णांक)माप(ctrl->subsys->field), ctrl->subsys->field);		\
पूर्ण										\
अटल DEVICE_ATTR(field, S_IRUGO, field##_show, शून्य);

nvme_show_str_function(model);
nvme_show_str_function(serial);
nvme_show_str_function(firmware_rev);

#घोषणा nvme_show_पूर्णांक_function(field)						\
अटल sमाप_प्रकार  field##_show(काष्ठा device *dev,				\
			    काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु										\
        काष्ठा nvme_ctrl *ctrl = dev_get_drvdata(dev);				\
        वापस sysfs_emit(buf, "%d\n", ctrl->field);				\
पूर्ण										\
अटल DEVICE_ATTR(field, S_IRUGO, field##_show, शून्य);

nvme_show_पूर्णांक_function(cntlid);
nvme_show_पूर्णांक_function(numa_node);
nvme_show_पूर्णांक_function(queue_count);
nvme_show_पूर्णांक_function(sqsize);
nvme_show_पूर्णांक_function(kato);

अटल sमाप_प्रकार nvme_sysfs_delete(काष्ठा device *dev,
				काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	काष्ठा nvme_ctrl *ctrl = dev_get_drvdata(dev);

	अगर (device_हटाओ_file_self(dev, attr))
		nvme_delete_ctrl_sync(ctrl);
	वापस count;
पूर्ण
अटल DEVICE_ATTR(delete_controller, S_IWUSR, शून्य, nvme_sysfs_delete);

अटल sमाप_प्रकार nvme_sysfs_show_transport(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा nvme_ctrl *ctrl = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%s\n", ctrl->ops->name);
पूर्ण
अटल DEVICE_ATTR(transport, S_IRUGO, nvme_sysfs_show_transport, शून्य);

अटल sमाप_प्रकार nvme_sysfs_show_state(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा nvme_ctrl *ctrl = dev_get_drvdata(dev);
	अटल स्थिर अक्षर *स्थिर state_name[] = अणु
		[NVME_CTRL_NEW]		= "new",
		[NVME_CTRL_LIVE]	= "live",
		[NVME_CTRL_RESETTING]	= "resetting",
		[NVME_CTRL_CONNECTING]	= "connecting",
		[NVME_CTRL_DELETING]	= "deleting",
		[NVME_CTRL_DELETING_NOIO]= "deleting (no IO)",
		[NVME_CTRL_DEAD]	= "dead",
	पूर्ण;

	अगर ((अचिन्हित)ctrl->state < ARRAY_SIZE(state_name) &&
	    state_name[ctrl->state])
		वापस sysfs_emit(buf, "%s\n", state_name[ctrl->state]);

	वापस sysfs_emit(buf, "unknown state\n");
पूर्ण

अटल DEVICE_ATTR(state, S_IRUGO, nvme_sysfs_show_state, शून्य);

अटल sमाप_प्रकार nvme_sysfs_show_subsysnqn(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा nvme_ctrl *ctrl = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%s\n", ctrl->subsys->subnqn);
पूर्ण
अटल DEVICE_ATTR(subsysnqn, S_IRUGO, nvme_sysfs_show_subsysnqn, शून्य);

अटल sमाप_प्रकार nvme_sysfs_show_hostnqn(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा nvme_ctrl *ctrl = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%s\n", ctrl->opts->host->nqn);
पूर्ण
अटल DEVICE_ATTR(hostnqn, S_IRUGO, nvme_sysfs_show_hostnqn, शून्य);

अटल sमाप_प्रकार nvme_sysfs_show_hostid(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा nvme_ctrl *ctrl = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%pU\n", &ctrl->opts->host->id);
पूर्ण
अटल DEVICE_ATTR(hostid, S_IRUGO, nvme_sysfs_show_hostid, शून्य);

अटल sमाप_प्रकार nvme_sysfs_show_address(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा nvme_ctrl *ctrl = dev_get_drvdata(dev);

	वापस ctrl->ops->get_address(ctrl, buf, PAGE_SIZE);
पूर्ण
अटल DEVICE_ATTR(address, S_IRUGO, nvme_sysfs_show_address, शून्य);

अटल sमाप_प्रकार nvme_ctrl_loss_पंचांगo_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvme_ctrl *ctrl = dev_get_drvdata(dev);
	काष्ठा nvmf_ctrl_options *opts = ctrl->opts;

	अगर (ctrl->opts->max_reconnects == -1)
		वापस sysfs_emit(buf, "off\n");
	वापस sysfs_emit(buf, "%d\n",
			  opts->max_reconnects * opts->reconnect_delay);
पूर्ण

अटल sमाप_प्रकार nvme_ctrl_loss_पंचांगo_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nvme_ctrl *ctrl = dev_get_drvdata(dev);
	काष्ठा nvmf_ctrl_options *opts = ctrl->opts;
	पूर्णांक ctrl_loss_पंचांगo, err;

	err = kstrtoपूर्णांक(buf, 10, &ctrl_loss_पंचांगo);
	अगर (err)
		वापस -EINVAL;

	अगर (ctrl_loss_पंचांगo < 0)
		opts->max_reconnects = -1;
	अन्यथा
		opts->max_reconnects = DIV_ROUND_UP(ctrl_loss_पंचांगo,
						opts->reconnect_delay);
	वापस count;
पूर्ण
अटल DEVICE_ATTR(ctrl_loss_पंचांगo, S_IRUGO | S_IWUSR,
	nvme_ctrl_loss_पंचांगo_show, nvme_ctrl_loss_पंचांगo_store);

अटल sमाप_प्रकार nvme_ctrl_reconnect_delay_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvme_ctrl *ctrl = dev_get_drvdata(dev);

	अगर (ctrl->opts->reconnect_delay == -1)
		वापस sysfs_emit(buf, "off\n");
	वापस sysfs_emit(buf, "%d\n", ctrl->opts->reconnect_delay);
पूर्ण

अटल sमाप_प्रकार nvme_ctrl_reconnect_delay_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nvme_ctrl *ctrl = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक v;
	पूर्णांक err;

	err = kstrtou32(buf, 10, &v);
	अगर (err)
		वापस err;

	ctrl->opts->reconnect_delay = v;
	वापस count;
पूर्ण
अटल DEVICE_ATTR(reconnect_delay, S_IRUGO | S_IWUSR,
	nvme_ctrl_reconnect_delay_show, nvme_ctrl_reconnect_delay_store);

अटल sमाप_प्रकार nvme_ctrl_fast_io_fail_पंचांगo_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvme_ctrl *ctrl = dev_get_drvdata(dev);

	अगर (ctrl->opts->fast_io_fail_पंचांगo == -1)
		वापस sysfs_emit(buf, "off\n");
	वापस sysfs_emit(buf, "%d\n", ctrl->opts->fast_io_fail_पंचांगo);
पूर्ण

अटल sमाप_प्रकार nvme_ctrl_fast_io_fail_पंचांगo_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nvme_ctrl *ctrl = dev_get_drvdata(dev);
	काष्ठा nvmf_ctrl_options *opts = ctrl->opts;
	पूर्णांक fast_io_fail_पंचांगo, err;

	err = kstrtoपूर्णांक(buf, 10, &fast_io_fail_पंचांगo);
	अगर (err)
		वापस -EINVAL;

	अगर (fast_io_fail_पंचांगo < 0)
		opts->fast_io_fail_पंचांगo = -1;
	अन्यथा
		opts->fast_io_fail_पंचांगo = fast_io_fail_पंचांगo;
	वापस count;
पूर्ण
अटल DEVICE_ATTR(fast_io_fail_पंचांगo, S_IRUGO | S_IWUSR,
	nvme_ctrl_fast_io_fail_पंचांगo_show, nvme_ctrl_fast_io_fail_पंचांगo_store);

अटल काष्ठा attribute *nvme_dev_attrs[] = अणु
	&dev_attr_reset_controller.attr,
	&dev_attr_rescan_controller.attr,
	&dev_attr_model.attr,
	&dev_attr_serial.attr,
	&dev_attr_firmware_rev.attr,
	&dev_attr_cntlid.attr,
	&dev_attr_delete_controller.attr,
	&dev_attr_transport.attr,
	&dev_attr_subsysnqn.attr,
	&dev_attr_address.attr,
	&dev_attr_state.attr,
	&dev_attr_numa_node.attr,
	&dev_attr_queue_count.attr,
	&dev_attr_sqsize.attr,
	&dev_attr_hostnqn.attr,
	&dev_attr_hostid.attr,
	&dev_attr_ctrl_loss_पंचांगo.attr,
	&dev_attr_reconnect_delay.attr,
	&dev_attr_fast_io_fail_पंचांगo.attr,
	&dev_attr_kato.attr,
	शून्य
पूर्ण;

अटल umode_t nvme_dev_attrs_are_visible(काष्ठा kobject *kobj,
		काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा nvme_ctrl *ctrl = dev_get_drvdata(dev);

	अगर (a == &dev_attr_delete_controller.attr && !ctrl->ops->delete_ctrl)
		वापस 0;
	अगर (a == &dev_attr_address.attr && !ctrl->ops->get_address)
		वापस 0;
	अगर (a == &dev_attr_hostnqn.attr && !ctrl->opts)
		वापस 0;
	अगर (a == &dev_attr_hostid.attr && !ctrl->opts)
		वापस 0;
	अगर (a == &dev_attr_ctrl_loss_पंचांगo.attr && !ctrl->opts)
		वापस 0;
	अगर (a == &dev_attr_reconnect_delay.attr && !ctrl->opts)
		वापस 0;
	अगर (a == &dev_attr_fast_io_fail_पंचांगo.attr && !ctrl->opts)
		वापस 0;

	वापस a->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group nvme_dev_attrs_group = अणु
	.attrs		= nvme_dev_attrs,
	.is_visible	= nvme_dev_attrs_are_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *nvme_dev_attr_groups[] = अणु
	&nvme_dev_attrs_group,
	शून्य,
पूर्ण;

अटल काष्ठा nvme_ns_head *nvme_find_ns_head(काष्ठा nvme_subप्रणाली *subsys,
		अचिन्हित nsid)
अणु
	काष्ठा nvme_ns_head *h;

	lockdep_निश्चित_held(&subsys->lock);

	list_क्रम_each_entry(h, &subsys->nsheads, entry) अणु
		अगर (h->ns_id == nsid && nvme_tryget_ns_head(h))
			वापस h;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक __nvme_check_ids(काष्ठा nvme_subप्रणाली *subsys,
		काष्ठा nvme_ns_head *new)
अणु
	काष्ठा nvme_ns_head *h;

	lockdep_निश्चित_held(&subsys->lock);

	list_क्रम_each_entry(h, &subsys->nsheads, entry) अणु
		अगर (nvme_ns_ids_valid(&new->ids) &&
		    nvme_ns_ids_equal(&new->ids, &h->ids))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम nvme_cdev_del(काष्ठा cdev *cdev, काष्ठा device *cdev_device)
अणु
	cdev_device_del(cdev, cdev_device);
	ida_simple_हटाओ(&nvme_ns_chr_minor_ida, MINOR(cdev_device->devt));
पूर्ण

पूर्णांक nvme_cdev_add(काष्ठा cdev *cdev, काष्ठा device *cdev_device,
		स्थिर काष्ठा file_operations *fops, काष्ठा module *owner)
अणु
	पूर्णांक minor, ret;

	minor = ida_simple_get(&nvme_ns_chr_minor_ida, 0, 0, GFP_KERNEL);
	अगर (minor < 0)
		वापस minor;
	cdev_device->devt = MKDEV(MAJOR(nvme_ns_chr_devt), minor);
	cdev_device->class = nvme_ns_chr_class;
	device_initialize(cdev_device);
	cdev_init(cdev, fops);
	cdev->owner = owner;
	ret = cdev_device_add(cdev, cdev_device);
	अगर (ret) अणु
		put_device(cdev_device);
		ida_simple_हटाओ(&nvme_ns_chr_minor_ida, minor);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक nvme_ns_chr_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस nvme_ns_खोलो(container_of(inode->i_cdev, काष्ठा nvme_ns, cdev));
पूर्ण

अटल पूर्णांक nvme_ns_chr_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	nvme_ns_release(container_of(inode->i_cdev, काष्ठा nvme_ns, cdev));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations nvme_ns_chr_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= nvme_ns_chr_खोलो,
	.release	= nvme_ns_chr_release,
	.unlocked_ioctl	= nvme_ns_chr_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
पूर्ण;

अटल पूर्णांक nvme_add_ns_cdev(काष्ठा nvme_ns *ns)
अणु
	पूर्णांक ret;

	ns->cdev_device.parent = ns->ctrl->device;
	ret = dev_set_name(&ns->cdev_device, "ng%dn%d",
			   ns->ctrl->instance, ns->head->instance);
	अगर (ret)
		वापस ret;
	ret = nvme_cdev_add(&ns->cdev, &ns->cdev_device, &nvme_ns_chr_fops,
			    ns->ctrl->ops->module);
	अगर (ret)
		kमुक्त_स्थिर(ns->cdev_device.kobj.name);
	वापस ret;
पूर्ण

अटल काष्ठा nvme_ns_head *nvme_alloc_ns_head(काष्ठा nvme_ctrl *ctrl,
		अचिन्हित nsid, काष्ठा nvme_ns_ids *ids)
अणु
	काष्ठा nvme_ns_head *head;
	माप_प्रकार size = माप(*head);
	पूर्णांक ret = -ENOMEM;

#अगर_घोषित CONFIG_NVME_MULTIPATH
	size += num_possible_nodes() * माप(काष्ठा nvme_ns *);
#पूर्ण_अगर

	head = kzalloc(size, GFP_KERNEL);
	अगर (!head)
		जाओ out;
	ret = ida_simple_get(&ctrl->subsys->ns_ida, 1, 0, GFP_KERNEL);
	अगर (ret < 0)
		जाओ out_मुक्त_head;
	head->instance = ret;
	INIT_LIST_HEAD(&head->list);
	ret = init_srcu_काष्ठा(&head->srcu);
	अगर (ret)
		जाओ out_ida_हटाओ;
	head->subsys = ctrl->subsys;
	head->ns_id = nsid;
	head->ids = *ids;
	kref_init(&head->ref);

	ret = __nvme_check_ids(ctrl->subsys, head);
	अगर (ret) अणु
		dev_err(ctrl->device,
			"duplicate IDs for nsid %d\n", nsid);
		जाओ out_cleanup_srcu;
	पूर्ण

	अगर (head->ids.csi) अणु
		ret = nvme_get_effects_log(ctrl, head->ids.csi, &head->effects);
		अगर (ret)
			जाओ out_cleanup_srcu;
	पूर्ण अन्यथा
		head->effects = ctrl->effects;

	ret = nvme_mpath_alloc_disk(ctrl, head);
	अगर (ret)
		जाओ out_cleanup_srcu;

	list_add_tail(&head->entry, &ctrl->subsys->nsheads);

	kref_get(&ctrl->subsys->ref);

	वापस head;
out_cleanup_srcu:
	cleanup_srcu_काष्ठा(&head->srcu);
out_ida_हटाओ:
	ida_simple_हटाओ(&ctrl->subsys->ns_ida, head->instance);
out_मुक्त_head:
	kमुक्त(head);
out:
	अगर (ret > 0)
		ret = blk_status_to_त्रुटि_सं(nvme_error_status(ret));
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक nvme_init_ns_head(काष्ठा nvme_ns *ns, अचिन्हित nsid,
		काष्ठा nvme_ns_ids *ids, bool is_shared)
अणु
	काष्ठा nvme_ctrl *ctrl = ns->ctrl;
	काष्ठा nvme_ns_head *head = शून्य;
	पूर्णांक ret = 0;

	mutex_lock(&ctrl->subsys->lock);
	head = nvme_find_ns_head(ctrl->subsys, nsid);
	अगर (!head) अणु
		head = nvme_alloc_ns_head(ctrl, nsid, ids);
		अगर (IS_ERR(head)) अणु
			ret = PTR_ERR(head);
			जाओ out_unlock;
		पूर्ण
		head->shared = is_shared;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		अगर (!is_shared || !head->shared) अणु
			dev_err(ctrl->device,
				"Duplicate unshared namespace %d\n", nsid);
			जाओ out_put_ns_head;
		पूर्ण
		अगर (!nvme_ns_ids_equal(&head->ids, ids)) अणु
			dev_err(ctrl->device,
				"IDs don't match for shared namespace %d\n",
					nsid);
			जाओ out_put_ns_head;
		पूर्ण
	पूर्ण

	list_add_tail_rcu(&ns->siblings, &head->list);
	ns->head = head;
	mutex_unlock(&ctrl->subsys->lock);
	वापस 0;

out_put_ns_head:
	nvme_put_ns_head(head);
out_unlock:
	mutex_unlock(&ctrl->subsys->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ns_cmp(व्योम *priv, स्थिर काष्ठा list_head *a,
		स्थिर काष्ठा list_head *b)
अणु
	काष्ठा nvme_ns *nsa = container_of(a, काष्ठा nvme_ns, list);
	काष्ठा nvme_ns *nsb = container_of(b, काष्ठा nvme_ns, list);

	वापस nsa->head->ns_id - nsb->head->ns_id;
पूर्ण

काष्ठा nvme_ns *nvme_find_get_ns(काष्ठा nvme_ctrl *ctrl, अचिन्हित nsid)
अणु
	काष्ठा nvme_ns *ns, *ret = शून्य;

	करोwn_पढ़ो(&ctrl->namespaces_rwsem);
	list_क्रम_each_entry(ns, &ctrl->namespaces, list) अणु
		अगर (ns->head->ns_id == nsid) अणु
			अगर (!nvme_get_ns(ns))
				जारी;
			ret = ns;
			अवरोध;
		पूर्ण
		अगर (ns->head->ns_id > nsid)
			अवरोध;
	पूर्ण
	up_पढ़ो(&ctrl->namespaces_rwsem);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_NS_GPL(nvme_find_get_ns, NVME_TARGET_PASSTHRU);

अटल व्योम nvme_alloc_ns(काष्ठा nvme_ctrl *ctrl, अचिन्हित nsid,
		काष्ठा nvme_ns_ids *ids)
अणु
	काष्ठा nvme_ns *ns;
	काष्ठा gendisk *disk;
	काष्ठा nvme_id_ns *id;
	पूर्णांक node = ctrl->numa_node;

	अगर (nvme_identअगरy_ns(ctrl, nsid, ids, &id))
		वापस;

	ns = kzalloc_node(माप(*ns), GFP_KERNEL, node);
	अगर (!ns)
		जाओ out_मुक्त_id;

	ns->queue = blk_mq_init_queue(ctrl->tagset);
	अगर (IS_ERR(ns->queue))
		जाओ out_मुक्त_ns;

	अगर (ctrl->opts && ctrl->opts->data_digest)
		blk_queue_flag_set(QUEUE_FLAG_STABLE_WRITES, ns->queue);

	blk_queue_flag_set(QUEUE_FLAG_NONROT, ns->queue);
	अगर (ctrl->ops->flags & NVME_F_PCI_P2PDMA)
		blk_queue_flag_set(QUEUE_FLAG_PCI_P2PDMA, ns->queue);

	ns->queue->queuedata = ns;
	ns->ctrl = ctrl;
	kref_init(&ns->kref);

	अगर (nvme_init_ns_head(ns, nsid, ids, id->nmic & NVME_NS_NMIC_SHARED))
		जाओ out_मुक्त_queue;

	disk = alloc_disk_node(0, node);
	अगर (!disk)
		जाओ out_unlink_ns;

	disk->fops = &nvme_bdev_ops;
	disk->निजी_data = ns;
	disk->queue = ns->queue;
	disk->flags = GENHD_FL_EXT_DEVT;
	/*
	 * Without the multipath code enabled, multiple controller per
	 * subप्रणालीs are visible as devices and thus we cannot use the
	 * subप्रणाली instance.
	 */
	अगर (!nvme_mpath_set_disk_name(ns, disk->disk_name, &disk->flags))
		प्र_लिखो(disk->disk_name, "nvme%dn%d", ctrl->instance,
			ns->head->instance);
	ns->disk = disk;

	अगर (nvme_update_ns_info(ns, id))
		जाओ out_put_disk;

	अगर ((ctrl->quirks & NVME_QUIRK_LIGHTNVM) && id->vs[0] == 0x1) अणु
		अगर (nvme_nvm_रेजिस्टर(ns, disk->disk_name, node)) अणु
			dev_warn(ctrl->device, "LightNVM init failure\n");
			जाओ out_put_disk;
		पूर्ण
	पूर्ण

	करोwn_ग_लिखो(&ctrl->namespaces_rwsem);
	list_add_tail(&ns->list, &ctrl->namespaces);
	up_ग_लिखो(&ctrl->namespaces_rwsem);

	nvme_get_ctrl(ctrl);

	device_add_disk(ctrl->device, ns->disk, nvme_ns_id_attr_groups);
	अगर (!nvme_ns_head_multipath(ns->head))
		nvme_add_ns_cdev(ns);

	nvme_mpath_add_disk(ns, id);
	nvme_fault_inject_init(&ns->fault_inject, ns->disk->disk_name);
	kमुक्त(id);

	वापस;
 out_put_disk:
	/* prevent द्विगुन queue cleanup */
	ns->disk->queue = शून्य;
	put_disk(ns->disk);
 out_unlink_ns:
	mutex_lock(&ctrl->subsys->lock);
	list_del_rcu(&ns->siblings);
	अगर (list_empty(&ns->head->list))
		list_del_init(&ns->head->entry);
	mutex_unlock(&ctrl->subsys->lock);
	nvme_put_ns_head(ns->head);
 out_मुक्त_queue:
	blk_cleanup_queue(ns->queue);
 out_मुक्त_ns:
	kमुक्त(ns);
 out_मुक्त_id:
	kमुक्त(id);
पूर्ण

अटल व्योम nvme_ns_हटाओ(काष्ठा nvme_ns *ns)
अणु
	अगर (test_and_set_bit(NVME_NS_REMOVING, &ns->flags))
		वापस;

	set_capacity(ns->disk, 0);
	nvme_fault_inject_fini(&ns->fault_inject);

	mutex_lock(&ns->ctrl->subsys->lock);
	list_del_rcu(&ns->siblings);
	अगर (list_empty(&ns->head->list))
		list_del_init(&ns->head->entry);
	mutex_unlock(&ns->ctrl->subsys->lock);

	synchronize_rcu(); /* guarantee not available in head->list */
	nvme_mpath_clear_current_path(ns);
	synchronize_srcu(&ns->head->srcu); /* रुको क्रम concurrent submissions */

	अगर (ns->disk->flags & GENHD_FL_UP) अणु
		अगर (!nvme_ns_head_multipath(ns->head))
			nvme_cdev_del(&ns->cdev, &ns->cdev_device);
		del_gendisk(ns->disk);
		blk_cleanup_queue(ns->queue);
		अगर (blk_get_पूर्णांकegrity(ns->disk))
			blk_पूर्णांकegrity_unरेजिस्टर(ns->disk);
	पूर्ण

	करोwn_ग_लिखो(&ns->ctrl->namespaces_rwsem);
	list_del_init(&ns->list);
	up_ग_लिखो(&ns->ctrl->namespaces_rwsem);

	nvme_mpath_check_last_path(ns);
	nvme_put_ns(ns);
पूर्ण

अटल व्योम nvme_ns_हटाओ_by_nsid(काष्ठा nvme_ctrl *ctrl, u32 nsid)
अणु
	काष्ठा nvme_ns *ns = nvme_find_get_ns(ctrl, nsid);

	अगर (ns) अणु
		nvme_ns_हटाओ(ns);
		nvme_put_ns(ns);
	पूर्ण
पूर्ण

अटल व्योम nvme_validate_ns(काष्ठा nvme_ns *ns, काष्ठा nvme_ns_ids *ids)
अणु
	काष्ठा nvme_id_ns *id;
	पूर्णांक ret = NVME_SC_INVALID_NS | NVME_SC_DNR;

	अगर (test_bit(NVME_NS_DEAD, &ns->flags))
		जाओ out;

	ret = nvme_identअगरy_ns(ns->ctrl, ns->head->ns_id, ids, &id);
	अगर (ret)
		जाओ out;

	ret = NVME_SC_INVALID_NS | NVME_SC_DNR;
	अगर (!nvme_ns_ids_equal(&ns->head->ids, ids)) अणु
		dev_err(ns->ctrl->device,
			"identifiers changed for nsid %d\n", ns->head->ns_id);
		जाओ out_मुक्त_id;
	पूर्ण

	ret = nvme_update_ns_info(ns, id);

out_मुक्त_id:
	kमुक्त(id);
out:
	/*
	 * Only हटाओ the namespace अगर we got a fatal error back from the
	 * device, otherwise ignore the error and just move on.
	 *
	 * TODO: we should probably schedule a delayed retry here.
	 */
	अगर (ret > 0 && (ret & NVME_SC_DNR))
		nvme_ns_हटाओ(ns);
पूर्ण

अटल व्योम nvme_validate_or_alloc_ns(काष्ठा nvme_ctrl *ctrl, अचिन्हित nsid)
अणु
	काष्ठा nvme_ns_ids ids = अणु पूर्ण;
	काष्ठा nvme_ns *ns;

	अगर (nvme_identअगरy_ns_descs(ctrl, nsid, &ids))
		वापस;

	ns = nvme_find_get_ns(ctrl, nsid);
	अगर (ns) अणु
		nvme_validate_ns(ns, &ids);
		nvme_put_ns(ns);
		वापस;
	पूर्ण

	चयन (ids.csi) अणु
	हाल NVME_CSI_NVM:
		nvme_alloc_ns(ctrl, nsid, &ids);
		अवरोध;
	हाल NVME_CSI_ZNS:
		अगर (!IS_ENABLED(CONFIG_BLK_DEV_ZONED)) अणु
			dev_warn(ctrl->device,
				"nsid %u not supported without CONFIG_BLK_DEV_ZONED\n",
				nsid);
			अवरोध;
		पूर्ण
		अगर (!nvme_multi_css(ctrl)) अणु
			dev_warn(ctrl->device,
				"command set not reported for nsid: %d\n",
				nsid);
			अवरोध;
		पूर्ण
		nvme_alloc_ns(ctrl, nsid, &ids);
		अवरोध;
	शेष:
		dev_warn(ctrl->device, "unknown csi %u for nsid %u\n",
			ids.csi, nsid);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम nvme_हटाओ_invalid_namespaces(काष्ठा nvme_ctrl *ctrl,
					अचिन्हित nsid)
अणु
	काष्ठा nvme_ns *ns, *next;
	LIST_HEAD(rm_list);

	करोwn_ग_लिखो(&ctrl->namespaces_rwsem);
	list_क्रम_each_entry_safe(ns, next, &ctrl->namespaces, list) अणु
		अगर (ns->head->ns_id > nsid || test_bit(NVME_NS_DEAD, &ns->flags))
			list_move_tail(&ns->list, &rm_list);
	पूर्ण
	up_ग_लिखो(&ctrl->namespaces_rwsem);

	list_क्रम_each_entry_safe(ns, next, &rm_list, list)
		nvme_ns_हटाओ(ns);

पूर्ण

अटल पूर्णांक nvme_scan_ns_list(काष्ठा nvme_ctrl *ctrl)
अणु
	स्थिर पूर्णांक nr_entries = NVME_IDENTIFY_DATA_SIZE / माप(__le32);
	__le32 *ns_list;
	u32 prev = 0;
	पूर्णांक ret = 0, i;

	अगर (nvme_ctrl_limited_cns(ctrl))
		वापस -EOPNOTSUPP;

	ns_list = kzalloc(NVME_IDENTIFY_DATA_SIZE, GFP_KERNEL);
	अगर (!ns_list)
		वापस -ENOMEM;

	क्रम (;;) अणु
		काष्ठा nvme_command cmd = अणु
			.identअगरy.opcode	= nvme_admin_identअगरy,
			.identअगरy.cns		= NVME_ID_CNS_NS_ACTIVE_LIST,
			.identअगरy.nsid		= cpu_to_le32(prev),
		पूर्ण;

		ret = nvme_submit_sync_cmd(ctrl->admin_q, &cmd, ns_list,
					    NVME_IDENTIFY_DATA_SIZE);
		अगर (ret) अणु
			dev_warn(ctrl->device,
				"Identify NS List failed (status=0x%x)\n", ret);
			जाओ मुक्त;
		पूर्ण

		क्रम (i = 0; i < nr_entries; i++) अणु
			u32 nsid = le32_to_cpu(ns_list[i]);

			अगर (!nsid)	/* end of the list? */
				जाओ out;
			nvme_validate_or_alloc_ns(ctrl, nsid);
			जबतक (++prev < nsid)
				nvme_ns_हटाओ_by_nsid(ctrl, prev);
		पूर्ण
	पूर्ण
 out:
	nvme_हटाओ_invalid_namespaces(ctrl, prev);
 मुक्त:
	kमुक्त(ns_list);
	वापस ret;
पूर्ण

अटल व्योम nvme_scan_ns_sequential(काष्ठा nvme_ctrl *ctrl)
अणु
	काष्ठा nvme_id_ctrl *id;
	u32 nn, i;

	अगर (nvme_identअगरy_ctrl(ctrl, &id))
		वापस;
	nn = le32_to_cpu(id->nn);
	kमुक्त(id);

	क्रम (i = 1; i <= nn; i++)
		nvme_validate_or_alloc_ns(ctrl, i);

	nvme_हटाओ_invalid_namespaces(ctrl, nn);
पूर्ण

अटल व्योम nvme_clear_changed_ns_log(काष्ठा nvme_ctrl *ctrl)
अणु
	माप_प्रकार log_size = NVME_MAX_CHANGED_NAMESPACES * माप(__le32);
	__le32 *log;
	पूर्णांक error;

	log = kzalloc(log_size, GFP_KERNEL);
	अगर (!log)
		वापस;

	/*
	 * We need to पढ़ो the log to clear the AEN, but we करोn't want to rely
	 * on it क्रम the changed namespace inक्रमmation as userspace could have
	 * raced with us in पढ़ोing the log page, which could cause us to miss
	 * updates.
	 */
	error = nvme_get_log(ctrl, NVME_NSID_ALL, NVME_LOG_CHANGED_NS, 0,
			NVME_CSI_NVM, log, log_size, 0);
	अगर (error)
		dev_warn(ctrl->device,
			"reading changed ns log failed: %d\n", error);

	kमुक्त(log);
पूर्ण

अटल व्योम nvme_scan_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvme_ctrl *ctrl =
		container_of(work, काष्ठा nvme_ctrl, scan_work);

	/* No tagset on a live ctrl means IO queues could not created */
	अगर (ctrl->state != NVME_CTRL_LIVE || !ctrl->tagset)
		वापस;

	अगर (test_and_clear_bit(NVME_AER_NOTICE_NS_CHANGED, &ctrl->events)) अणु
		dev_info(ctrl->device, "rescanning namespaces.\n");
		nvme_clear_changed_ns_log(ctrl);
	पूर्ण

	mutex_lock(&ctrl->scan_lock);
	अगर (nvme_scan_ns_list(ctrl) != 0)
		nvme_scan_ns_sequential(ctrl);
	mutex_unlock(&ctrl->scan_lock);

	करोwn_ग_लिखो(&ctrl->namespaces_rwsem);
	list_sort(शून्य, &ctrl->namespaces, ns_cmp);
	up_ग_लिखो(&ctrl->namespaces_rwsem);
पूर्ण

/*
 * This function iterates the namespace list unlocked to allow recovery from
 * controller failure. It is up to the caller to ensure the namespace list is
 * not modअगरied by scan work जबतक this function is executing.
 */
व्योम nvme_हटाओ_namespaces(काष्ठा nvme_ctrl *ctrl)
अणु
	काष्ठा nvme_ns *ns, *next;
	LIST_HEAD(ns_list);

	/*
	 * make sure to requeue I/O to all namespaces as these
	 * might result from the scan itself and must complete
	 * क्रम the scan_work to make progress
	 */
	nvme_mpath_clear_ctrl_paths(ctrl);

	/* prevent racing with ns scanning */
	flush_work(&ctrl->scan_work);

	/*
	 * The dead states indicates the controller was not gracefully
	 * disconnected. In that हाल, we won't be able to flush any data जबतक
	 * removing the namespaces' disks; fail all the queues now to aव्योम
	 * potentially having to clean up the failed sync later.
	 */
	अगर (ctrl->state == NVME_CTRL_DEAD)
		nvme_समाप्त_queues(ctrl);

	/* this is a no-op when called from the controller reset handler */
	nvme_change_ctrl_state(ctrl, NVME_CTRL_DELETING_NOIO);

	करोwn_ग_लिखो(&ctrl->namespaces_rwsem);
	list_splice_init(&ctrl->namespaces, &ns_list);
	up_ग_लिखो(&ctrl->namespaces_rwsem);

	list_क्रम_each_entry_safe(ns, next, &ns_list, list)
		nvme_ns_हटाओ(ns);
पूर्ण
EXPORT_SYMBOL_GPL(nvme_हटाओ_namespaces);

अटल पूर्णांक nvme_class_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा nvme_ctrl *ctrl =
		container_of(dev, काष्ठा nvme_ctrl, ctrl_device);
	काष्ठा nvmf_ctrl_options *opts = ctrl->opts;
	पूर्णांक ret;

	ret = add_uevent_var(env, "NVME_TRTYPE=%s", ctrl->ops->name);
	अगर (ret)
		वापस ret;

	अगर (opts) अणु
		ret = add_uevent_var(env, "NVME_TRADDR=%s", opts->traddr);
		अगर (ret)
			वापस ret;

		ret = add_uevent_var(env, "NVME_TRSVCID=%s",
				opts->trsvcid ?: "none");
		अगर (ret)
			वापस ret;

		ret = add_uevent_var(env, "NVME_HOST_TRADDR=%s",
				opts->host_traddr ?: "none");
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम nvme_aen_uevent(काष्ठा nvme_ctrl *ctrl)
अणु
	अक्षर *envp[2] = अणु शून्य, शून्य पूर्ण;
	u32 aen_result = ctrl->aen_result;

	ctrl->aen_result = 0;
	अगर (!aen_result)
		वापस;

	envp[0] = kaप्र_लिखो(GFP_KERNEL, "NVME_AEN=%#08x", aen_result);
	अगर (!envp[0])
		वापस;
	kobject_uevent_env(&ctrl->device->kobj, KOBJ_CHANGE, envp);
	kमुक्त(envp[0]);
पूर्ण

अटल व्योम nvme_async_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvme_ctrl *ctrl =
		container_of(work, काष्ठा nvme_ctrl, async_event_work);

	nvme_aen_uevent(ctrl);
	ctrl->ops->submit_async_event(ctrl);
पूर्ण

अटल bool nvme_ctrl_pp_status(काष्ठा nvme_ctrl *ctrl)
अणु

	u32 csts;

	अगर (ctrl->ops->reg_पढ़ो32(ctrl, NVME_REG_CSTS, &csts))
		वापस false;

	अगर (csts == ~0)
		वापस false;

	वापस ((ctrl->ctrl_config & NVME_CC_ENABLE) && (csts & NVME_CSTS_PP));
पूर्ण

अटल व्योम nvme_get_fw_slot_info(काष्ठा nvme_ctrl *ctrl)
अणु
	काष्ठा nvme_fw_slot_info_log *log;

	log = kदो_स्मृति(माप(*log), GFP_KERNEL);
	अगर (!log)
		वापस;

	अगर (nvme_get_log(ctrl, NVME_NSID_ALL, NVME_LOG_FW_SLOT, 0, NVME_CSI_NVM,
			log, माप(*log), 0))
		dev_warn(ctrl->device, "Get FW SLOT INFO log error\n");
	kमुक्त(log);
पूर्ण

अटल व्योम nvme_fw_act_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvme_ctrl *ctrl = container_of(work,
				काष्ठा nvme_ctrl, fw_act_work);
	अचिन्हित दीर्घ fw_act_समयout;

	अगर (ctrl->mtfa)
		fw_act_समयout = jअगरfies +
				msecs_to_jअगरfies(ctrl->mtfa * 100);
	अन्यथा
		fw_act_समयout = jअगरfies +
				msecs_to_jअगरfies(admin_समयout * 1000);

	nvme_stop_queues(ctrl);
	जबतक (nvme_ctrl_pp_status(ctrl)) अणु
		अगर (समय_after(jअगरfies, fw_act_समयout)) अणु
			dev_warn(ctrl->device,
				"Fw activation timeout, reset controller\n");
			nvme_try_sched_reset(ctrl);
			वापस;
		पूर्ण
		msleep(100);
	पूर्ण

	अगर (!nvme_change_ctrl_state(ctrl, NVME_CTRL_LIVE))
		वापस;

	nvme_start_queues(ctrl);
	/* पढ़ो FW slot inक्रमmation to clear the AER */
	nvme_get_fw_slot_info(ctrl);
पूर्ण

अटल व्योम nvme_handle_aen_notice(काष्ठा nvme_ctrl *ctrl, u32 result)
अणु
	u32 aer_notice_type = (result & 0xff00) >> 8;

	trace_nvme_async_event(ctrl, aer_notice_type);

	चयन (aer_notice_type) अणु
	हाल NVME_AER_NOTICE_NS_CHANGED:
		set_bit(NVME_AER_NOTICE_NS_CHANGED, &ctrl->events);
		nvme_queue_scan(ctrl);
		अवरोध;
	हाल NVME_AER_NOTICE_FW_ACT_STARTING:
		/*
		 * We are (ab)using the RESETTING state to prevent subsequent
		 * recovery actions from पूर्णांकerfering with the controller's
		 * firmware activation.
		 */
		अगर (nvme_change_ctrl_state(ctrl, NVME_CTRL_RESETTING))
			queue_work(nvme_wq, &ctrl->fw_act_work);
		अवरोध;
#अगर_घोषित CONFIG_NVME_MULTIPATH
	हाल NVME_AER_NOTICE_ANA:
		अगर (!ctrl->ana_log_buf)
			अवरोध;
		queue_work(nvme_wq, &ctrl->ana_work);
		अवरोध;
#पूर्ण_अगर
	हाल NVME_AER_NOTICE_DISC_CHANGED:
		ctrl->aen_result = result;
		अवरोध;
	शेष:
		dev_warn(ctrl->device, "async event result %08x\n", result);
	पूर्ण
पूर्ण

व्योम nvme_complete_async_event(काष्ठा nvme_ctrl *ctrl, __le16 status,
		अस्थिर जोड़ nvme_result *res)
अणु
	u32 result = le32_to_cpu(res->u32);
	u32 aer_type = result & 0x07;

	अगर (le16_to_cpu(status) >> 1 != NVME_SC_SUCCESS)
		वापस;

	चयन (aer_type) अणु
	हाल NVME_AER_NOTICE:
		nvme_handle_aen_notice(ctrl, result);
		अवरोध;
	हाल NVME_AER_ERROR:
	हाल NVME_AER_SMART:
	हाल NVME_AER_CSS:
	हाल NVME_AER_VS:
		trace_nvme_async_event(ctrl, aer_type);
		ctrl->aen_result = result;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	queue_work(nvme_wq, &ctrl->async_event_work);
पूर्ण
EXPORT_SYMBOL_GPL(nvme_complete_async_event);

व्योम nvme_stop_ctrl(काष्ठा nvme_ctrl *ctrl)
अणु
	nvme_mpath_stop(ctrl);
	nvme_stop_keep_alive(ctrl);
	nvme_stop_failfast_work(ctrl);
	flush_work(&ctrl->async_event_work);
	cancel_work_sync(&ctrl->fw_act_work);
पूर्ण
EXPORT_SYMBOL_GPL(nvme_stop_ctrl);

व्योम nvme_start_ctrl(काष्ठा nvme_ctrl *ctrl)
अणु
	nvme_start_keep_alive(ctrl);

	nvme_enable_aen(ctrl);

	अगर (ctrl->queue_count > 1) अणु
		nvme_queue_scan(ctrl);
		nvme_start_queues(ctrl);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nvme_start_ctrl);

व्योम nvme_uninit_ctrl(काष्ठा nvme_ctrl *ctrl)
अणु
	nvme_hwmon_निकास(ctrl);
	nvme_fault_inject_fini(&ctrl->fault_inject);
	dev_pm_qos_hide_latency_tolerance(ctrl->device);
	cdev_device_del(&ctrl->cdev, ctrl->device);
	nvme_put_ctrl(ctrl);
पूर्ण
EXPORT_SYMBOL_GPL(nvme_uninit_ctrl);

अटल व्योम nvme_मुक्त_cels(काष्ठा nvme_ctrl *ctrl)
अणु
	काष्ठा nvme_effects_log	*cel;
	अचिन्हित दीर्घ i;

	xa_क्रम_each(&ctrl->cels, i, cel) अणु
		xa_erase(&ctrl->cels, i);
		kमुक्त(cel);
	पूर्ण

	xa_destroy(&ctrl->cels);
पूर्ण

अटल व्योम nvme_मुक्त_ctrl(काष्ठा device *dev)
अणु
	काष्ठा nvme_ctrl *ctrl =
		container_of(dev, काष्ठा nvme_ctrl, ctrl_device);
	काष्ठा nvme_subप्रणाली *subsys = ctrl->subsys;

	अगर (!subsys || ctrl->instance != subsys->instance)
		ida_simple_हटाओ(&nvme_instance_ida, ctrl->instance);

	nvme_मुक्त_cels(ctrl);
	nvme_mpath_uninit(ctrl);
	__मुक्त_page(ctrl->discard_page);

	अगर (subsys) अणु
		mutex_lock(&nvme_subप्रणालीs_lock);
		list_del(&ctrl->subsys_entry);
		sysfs_हटाओ_link(&subsys->dev.kobj, dev_name(ctrl->device));
		mutex_unlock(&nvme_subप्रणालीs_lock);
	पूर्ण

	ctrl->ops->मुक्त_ctrl(ctrl);

	अगर (subsys)
		nvme_put_subप्रणाली(subsys);
पूर्ण

/*
 * Initialize a NVMe controller काष्ठाures.  This needs to be called during
 * earliest initialization so that we have the initialized काष्ठाured around
 * during probing.
 */
पूर्णांक nvme_init_ctrl(काष्ठा nvme_ctrl *ctrl, काष्ठा device *dev,
		स्थिर काष्ठा nvme_ctrl_ops *ops, अचिन्हित दीर्घ quirks)
अणु
	पूर्णांक ret;

	ctrl->state = NVME_CTRL_NEW;
	clear_bit(NVME_CTRL_FAILFAST_EXPIRED, &ctrl->flags);
	spin_lock_init(&ctrl->lock);
	mutex_init(&ctrl->scan_lock);
	INIT_LIST_HEAD(&ctrl->namespaces);
	xa_init(&ctrl->cels);
	init_rwsem(&ctrl->namespaces_rwsem);
	ctrl->dev = dev;
	ctrl->ops = ops;
	ctrl->quirks = quirks;
	ctrl->numa_node = NUMA_NO_NODE;
	INIT_WORK(&ctrl->scan_work, nvme_scan_work);
	INIT_WORK(&ctrl->async_event_work, nvme_async_event_work);
	INIT_WORK(&ctrl->fw_act_work, nvme_fw_act_work);
	INIT_WORK(&ctrl->delete_work, nvme_delete_ctrl_work);
	init_रुकोqueue_head(&ctrl->state_wq);

	INIT_DELAYED_WORK(&ctrl->ka_work, nvme_keep_alive_work);
	INIT_DELAYED_WORK(&ctrl->failfast_work, nvme_failfast_work);
	स_रखो(&ctrl->ka_cmd, 0, माप(ctrl->ka_cmd));
	ctrl->ka_cmd.common.opcode = nvme_admin_keep_alive;

	BUILD_BUG_ON(NVME_DSM_MAX_RANGES * माप(काष्ठा nvme_dsm_range) >
			PAGE_SIZE);
	ctrl->discard_page = alloc_page(GFP_KERNEL);
	अगर (!ctrl->discard_page) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = ida_simple_get(&nvme_instance_ida, 0, 0, GFP_KERNEL);
	अगर (ret < 0)
		जाओ out;
	ctrl->instance = ret;

	device_initialize(&ctrl->ctrl_device);
	ctrl->device = &ctrl->ctrl_device;
	ctrl->device->devt = MKDEV(MAJOR(nvme_ctrl_base_chr_devt),
			ctrl->instance);
	ctrl->device->class = nvme_class;
	ctrl->device->parent = ctrl->dev;
	ctrl->device->groups = nvme_dev_attr_groups;
	ctrl->device->release = nvme_मुक्त_ctrl;
	dev_set_drvdata(ctrl->device, ctrl);
	ret = dev_set_name(ctrl->device, "nvme%d", ctrl->instance);
	अगर (ret)
		जाओ out_release_instance;

	nvme_get_ctrl(ctrl);
	cdev_init(&ctrl->cdev, &nvme_dev_fops);
	ctrl->cdev.owner = ops->module;
	ret = cdev_device_add(&ctrl->cdev, ctrl->device);
	अगर (ret)
		जाओ out_मुक्त_name;

	/*
	 * Initialize latency tolerance controls.  The sysfs files won't
	 * be visible to userspace unless the device actually supports APST.
	 */
	ctrl->device->घातer.set_latency_tolerance = nvme_set_latency_tolerance;
	dev_pm_qos_update_user_latency_tolerance(ctrl->device,
		min(शेष_ps_max_latency_us, (अचिन्हित दीर्घ)S32_MAX));

	nvme_fault_inject_init(&ctrl->fault_inject, dev_name(ctrl->device));
	nvme_mpath_init_ctrl(ctrl);

	वापस 0;
out_मुक्त_name:
	nvme_put_ctrl(ctrl);
	kमुक्त_स्थिर(ctrl->device->kobj.name);
out_release_instance:
	ida_simple_हटाओ(&nvme_instance_ida, ctrl->instance);
out:
	अगर (ctrl->discard_page)
		__मुक्त_page(ctrl->discard_page);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nvme_init_ctrl);

/**
 * nvme_समाप्त_queues(): Ends all namespace queues
 * @ctrl: the dead controller that needs to end
 *
 * Call this function when the driver determines it is unable to get the
 * controller in a state capable of servicing IO.
 */
व्योम nvme_समाप्त_queues(काष्ठा nvme_ctrl *ctrl)
अणु
	काष्ठा nvme_ns *ns;

	करोwn_पढ़ो(&ctrl->namespaces_rwsem);

	/* Forcibly unquiesce queues to aव्योम blocking dispatch */
	अगर (ctrl->admin_q && !blk_queue_dying(ctrl->admin_q))
		blk_mq_unquiesce_queue(ctrl->admin_q);

	list_क्रम_each_entry(ns, &ctrl->namespaces, list)
		nvme_set_queue_dying(ns);

	up_पढ़ो(&ctrl->namespaces_rwsem);
पूर्ण
EXPORT_SYMBOL_GPL(nvme_समाप्त_queues);

व्योम nvme_unमुक्तze(काष्ठा nvme_ctrl *ctrl)
अणु
	काष्ठा nvme_ns *ns;

	करोwn_पढ़ो(&ctrl->namespaces_rwsem);
	list_क्रम_each_entry(ns, &ctrl->namespaces, list)
		blk_mq_unमुक्तze_queue(ns->queue);
	up_पढ़ो(&ctrl->namespaces_rwsem);
पूर्ण
EXPORT_SYMBOL_GPL(nvme_unमुक्तze);

पूर्णांक nvme_रुको_मुक्तze_समयout(काष्ठा nvme_ctrl *ctrl, दीर्घ समयout)
अणु
	काष्ठा nvme_ns *ns;

	करोwn_पढ़ो(&ctrl->namespaces_rwsem);
	list_क्रम_each_entry(ns, &ctrl->namespaces, list) अणु
		समयout = blk_mq_मुक्तze_queue_रुको_समयout(ns->queue, समयout);
		अगर (समयout <= 0)
			अवरोध;
	पूर्ण
	up_पढ़ो(&ctrl->namespaces_rwsem);
	वापस समयout;
पूर्ण
EXPORT_SYMBOL_GPL(nvme_रुको_मुक्तze_समयout);

व्योम nvme_रुको_मुक्तze(काष्ठा nvme_ctrl *ctrl)
अणु
	काष्ठा nvme_ns *ns;

	करोwn_पढ़ो(&ctrl->namespaces_rwsem);
	list_क्रम_each_entry(ns, &ctrl->namespaces, list)
		blk_mq_मुक्तze_queue_रुको(ns->queue);
	up_पढ़ो(&ctrl->namespaces_rwsem);
पूर्ण
EXPORT_SYMBOL_GPL(nvme_रुको_मुक्तze);

व्योम nvme_start_मुक्तze(काष्ठा nvme_ctrl *ctrl)
अणु
	काष्ठा nvme_ns *ns;

	करोwn_पढ़ो(&ctrl->namespaces_rwsem);
	list_क्रम_each_entry(ns, &ctrl->namespaces, list)
		blk_मुक्तze_queue_start(ns->queue);
	up_पढ़ो(&ctrl->namespaces_rwsem);
पूर्ण
EXPORT_SYMBOL_GPL(nvme_start_मुक्तze);

व्योम nvme_stop_queues(काष्ठा nvme_ctrl *ctrl)
अणु
	काष्ठा nvme_ns *ns;

	करोwn_पढ़ो(&ctrl->namespaces_rwsem);
	list_क्रम_each_entry(ns, &ctrl->namespaces, list)
		blk_mq_quiesce_queue(ns->queue);
	up_पढ़ो(&ctrl->namespaces_rwsem);
पूर्ण
EXPORT_SYMBOL_GPL(nvme_stop_queues);

व्योम nvme_start_queues(काष्ठा nvme_ctrl *ctrl)
अणु
	काष्ठा nvme_ns *ns;

	करोwn_पढ़ो(&ctrl->namespaces_rwsem);
	list_क्रम_each_entry(ns, &ctrl->namespaces, list)
		blk_mq_unquiesce_queue(ns->queue);
	up_पढ़ो(&ctrl->namespaces_rwsem);
पूर्ण
EXPORT_SYMBOL_GPL(nvme_start_queues);

व्योम nvme_sync_io_queues(काष्ठा nvme_ctrl *ctrl)
अणु
	काष्ठा nvme_ns *ns;

	करोwn_पढ़ो(&ctrl->namespaces_rwsem);
	list_क्रम_each_entry(ns, &ctrl->namespaces, list)
		blk_sync_queue(ns->queue);
	up_पढ़ो(&ctrl->namespaces_rwsem);
पूर्ण
EXPORT_SYMBOL_GPL(nvme_sync_io_queues);

व्योम nvme_sync_queues(काष्ठा nvme_ctrl *ctrl)
अणु
	nvme_sync_io_queues(ctrl);
	अगर (ctrl->admin_q)
		blk_sync_queue(ctrl->admin_q);
पूर्ण
EXPORT_SYMBOL_GPL(nvme_sync_queues);

काष्ठा nvme_ctrl *nvme_ctrl_from_file(काष्ठा file *file)
अणु
	अगर (file->f_op != &nvme_dev_fops)
		वापस शून्य;
	वापस file->निजी_data;
पूर्ण
EXPORT_SYMBOL_NS_GPL(nvme_ctrl_from_file, NVME_TARGET_PASSTHRU);

/*
 * Check we didn't inadvertently grow the command काष्ठाure sizes:
 */
अटल अंतरभूत व्योम _nvme_check_size(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा nvme_common_command) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvme_rw_command) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvme_identअगरy) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvme_features) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvme_करोwnload_firmware) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvme_क्रमmat_cmd) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvme_dsm_cmd) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvme_ग_लिखो_zeroes_cmd) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvme_पात_cmd) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvme_get_log_page_command) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvme_command) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvme_id_ctrl) != NVME_IDENTIFY_DATA_SIZE);
	BUILD_BUG_ON(माप(काष्ठा nvme_id_ns) != NVME_IDENTIFY_DATA_SIZE);
	BUILD_BUG_ON(माप(काष्ठा nvme_id_ns_zns) != NVME_IDENTIFY_DATA_SIZE);
	BUILD_BUG_ON(माप(काष्ठा nvme_id_ctrl_zns) != NVME_IDENTIFY_DATA_SIZE);
	BUILD_BUG_ON(माप(काष्ठा nvme_id_ctrl_nvm) != NVME_IDENTIFY_DATA_SIZE);
	BUILD_BUG_ON(माप(काष्ठा nvme_lba_range_type) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvme_smart_log) != 512);
	BUILD_BUG_ON(माप(काष्ठा nvme_dbbuf) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvme_directive_cmd) != 64);
पूर्ण


अटल पूर्णांक __init nvme_core_init(व्योम)
अणु
	पूर्णांक result = -ENOMEM;

	_nvme_check_size();

	nvme_wq = alloc_workqueue("nvme-wq",
			WQ_UNBOUND | WQ_MEM_RECLAIM | WQ_SYSFS, 0);
	अगर (!nvme_wq)
		जाओ out;

	nvme_reset_wq = alloc_workqueue("nvme-reset-wq",
			WQ_UNBOUND | WQ_MEM_RECLAIM | WQ_SYSFS, 0);
	अगर (!nvme_reset_wq)
		जाओ destroy_wq;

	nvme_delete_wq = alloc_workqueue("nvme-delete-wq",
			WQ_UNBOUND | WQ_MEM_RECLAIM | WQ_SYSFS, 0);
	अगर (!nvme_delete_wq)
		जाओ destroy_reset_wq;

	result = alloc_chrdev_region(&nvme_ctrl_base_chr_devt, 0,
			NVME_MINORS, "nvme");
	अगर (result < 0)
		जाओ destroy_delete_wq;

	nvme_class = class_create(THIS_MODULE, "nvme");
	अगर (IS_ERR(nvme_class)) अणु
		result = PTR_ERR(nvme_class);
		जाओ unरेजिस्टर_chrdev;
	पूर्ण
	nvme_class->dev_uevent = nvme_class_uevent;

	nvme_subsys_class = class_create(THIS_MODULE, "nvme-subsystem");
	अगर (IS_ERR(nvme_subsys_class)) अणु
		result = PTR_ERR(nvme_subsys_class);
		जाओ destroy_class;
	पूर्ण

	result = alloc_chrdev_region(&nvme_ns_chr_devt, 0, NVME_MINORS,
				     "nvme-generic");
	अगर (result < 0)
		जाओ destroy_subsys_class;

	nvme_ns_chr_class = class_create(THIS_MODULE, "nvme-generic");
	अगर (IS_ERR(nvme_ns_chr_class)) अणु
		result = PTR_ERR(nvme_ns_chr_class);
		जाओ unरेजिस्टर_generic_ns;
	पूर्ण

	वापस 0;

unरेजिस्टर_generic_ns:
	unरेजिस्टर_chrdev_region(nvme_ns_chr_devt, NVME_MINORS);
destroy_subsys_class:
	class_destroy(nvme_subsys_class);
destroy_class:
	class_destroy(nvme_class);
unरेजिस्टर_chrdev:
	unरेजिस्टर_chrdev_region(nvme_ctrl_base_chr_devt, NVME_MINORS);
destroy_delete_wq:
	destroy_workqueue(nvme_delete_wq);
destroy_reset_wq:
	destroy_workqueue(nvme_reset_wq);
destroy_wq:
	destroy_workqueue(nvme_wq);
out:
	वापस result;
पूर्ण

अटल व्योम __निकास nvme_core_निकास(व्योम)
अणु
	class_destroy(nvme_ns_chr_class);
	class_destroy(nvme_subsys_class);
	class_destroy(nvme_class);
	unरेजिस्टर_chrdev_region(nvme_ns_chr_devt, NVME_MINORS);
	unरेजिस्टर_chrdev_region(nvme_ctrl_base_chr_devt, NVME_MINORS);
	destroy_workqueue(nvme_delete_wq);
	destroy_workqueue(nvme_reset_wq);
	destroy_workqueue(nvme_wq);
	ida_destroy(&nvme_ns_chr_minor_ida);
	ida_destroy(&nvme_instance_ida);
पूर्ण

MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
module_init(nvme_core_init);
module_निकास(nvme_core_निकास);
