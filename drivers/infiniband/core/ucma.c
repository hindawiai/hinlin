<शैली गुरु>
/*
 * Copyright (c) 2005-2006 Intel Corporation.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *	copyright notice, this list of conditions and the following
 *	disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *	copyright notice, this list of conditions and the following
 *	disclaimer in the करोcumentation and/or other materials
 *	provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/completion.h>
#समावेश <linux/file.h>
#समावेश <linux/mutex.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched.h>
#समावेश <linux/idr.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/module.h>
#समावेश <linux/nsproxy.h>

#समावेश <linux/nospec.h>

#समावेश <rdma/rdma_user_cm.h>
#समावेश <rdma/ib_marshall.h>
#समावेश <rdma/rdma_cm.h>
#समावेश <rdma/rdma_cm_ib.h>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib.h>
#समावेश <rdma/ib_cm.h>
#समावेश <rdma/rdma_netlink.h>
#समावेश "core_priv.h"

MODULE_AUTHOR("Sean Hefty");
MODULE_DESCRIPTION("RDMA Userspace Connection Manager Access");
MODULE_LICENSE("Dual BSD/GPL");

अटल अचिन्हित पूर्णांक max_backlog = 1024;

अटल काष्ठा ctl_table_header *ucma_ctl_table_hdr;
अटल काष्ठा ctl_table ucma_ctl_table[] = अणु
	अणु
		.procname	= "max_backlog",
		.data		= &max_backlog,
		.maxlen		= माप max_backlog,
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

काष्ठा ucma_file अणु
	काष्ठा mutex		mut;
	काष्ठा file		*filp;
	काष्ठा list_head	ctx_list;
	काष्ठा list_head	event_list;
	रुको_queue_head_t	poll_रुको;
पूर्ण;

काष्ठा ucma_context अणु
	u32			id;
	काष्ठा completion	comp;
	refcount_t		ref;
	पूर्णांक			events_reported;
	atomic_t		backlog;

	काष्ठा ucma_file	*file;
	काष्ठा rdma_cm_id	*cm_id;
	काष्ठा mutex		mutex;
	u64			uid;

	काष्ठा list_head	list;
	काष्ठा work_काष्ठा	बंद_work;
पूर्ण;

काष्ठा ucma_multicast अणु
	काष्ठा ucma_context	*ctx;
	u32			id;
	पूर्णांक			events_reported;

	u64			uid;
	u8			join_state;
	काष्ठा sockaddr_storage	addr;
पूर्ण;

काष्ठा ucma_event अणु
	काष्ठा ucma_context	*ctx;
	काष्ठा ucma_context	*conn_req_ctx;
	काष्ठा ucma_multicast	*mc;
	काष्ठा list_head	list;
	काष्ठा rdma_ucm_event_resp resp;
पूर्ण;

अटल DEFINE_XARRAY_ALLOC(ctx_table);
अटल DEFINE_XARRAY_ALLOC(multicast_table);

अटल स्थिर काष्ठा file_operations ucma_fops;
अटल पूर्णांक ucma_destroy_निजी_ctx(काष्ठा ucma_context *ctx);

अटल अंतरभूत काष्ठा ucma_context *_ucma_find_context(पूर्णांक id,
						      काष्ठा ucma_file *file)
अणु
	काष्ठा ucma_context *ctx;

	ctx = xa_load(&ctx_table, id);
	अगर (!ctx)
		ctx = ERR_PTR(-ENOENT);
	अन्यथा अगर (ctx->file != file)
		ctx = ERR_PTR(-EINVAL);
	वापस ctx;
पूर्ण

अटल काष्ठा ucma_context *ucma_get_ctx(काष्ठा ucma_file *file, पूर्णांक id)
अणु
	काष्ठा ucma_context *ctx;

	xa_lock(&ctx_table);
	ctx = _ucma_find_context(id, file);
	अगर (!IS_ERR(ctx))
		अगर (!refcount_inc_not_zero(&ctx->ref))
			ctx = ERR_PTR(-ENXIO);
	xa_unlock(&ctx_table);
	वापस ctx;
पूर्ण

अटल व्योम ucma_put_ctx(काष्ठा ucma_context *ctx)
अणु
	अगर (refcount_dec_and_test(&ctx->ref))
		complete(&ctx->comp);
पूर्ण

/*
 * Same as ucm_get_ctx but requires that ->cm_id->device is valid, eg that the
 * CM_ID is bound.
 */
अटल काष्ठा ucma_context *ucma_get_ctx_dev(काष्ठा ucma_file *file, पूर्णांक id)
अणु
	काष्ठा ucma_context *ctx = ucma_get_ctx(file, id);

	अगर (IS_ERR(ctx))
		वापस ctx;
	अगर (!ctx->cm_id->device) अणु
		ucma_put_ctx(ctx);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	वापस ctx;
पूर्ण

अटल व्योम ucma_बंद_id(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ucma_context *ctx =  container_of(work, काष्ठा ucma_context, बंद_work);

	/* once all inflight tasks are finished, we बंद all underlying
	 * resources. The context is still alive till its explicit destryoing
	 * by its creator. This माला_दो back the xarray's reference.
	 */
	ucma_put_ctx(ctx);
	रुको_क्रम_completion(&ctx->comp);
	/* No new events will be generated after destroying the id. */
	rdma_destroy_id(ctx->cm_id);

	/* Reading the cm_id without holding a positive ref is not allowed */
	ctx->cm_id = शून्य;
पूर्ण

अटल काष्ठा ucma_context *ucma_alloc_ctx(काष्ठा ucma_file *file)
अणु
	काष्ठा ucma_context *ctx;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस शून्य;

	INIT_WORK(&ctx->बंद_work, ucma_बंद_id);
	init_completion(&ctx->comp);
	/* So list_del() will work अगर we करोn't करो ucma_finish_ctx() */
	INIT_LIST_HEAD(&ctx->list);
	ctx->file = file;
	mutex_init(&ctx->mutex);

	अगर (xa_alloc(&ctx_table, &ctx->id, शून्य, xa_limit_32b, GFP_KERNEL)) अणु
		kमुक्त(ctx);
		वापस शून्य;
	पूर्ण
	वापस ctx;
पूर्ण

अटल व्योम ucma_set_ctx_cm_id(काष्ठा ucma_context *ctx,
			       काष्ठा rdma_cm_id *cm_id)
अणु
	refcount_set(&ctx->ref, 1);
	ctx->cm_id = cm_id;
पूर्ण

अटल व्योम ucma_finish_ctx(काष्ठा ucma_context *ctx)
अणु
	lockdep_निश्चित_held(&ctx->file->mut);
	list_add_tail(&ctx->list, &ctx->file->ctx_list);
	xa_store(&ctx_table, ctx->id, ctx, GFP_KERNEL);
पूर्ण

अटल व्योम ucma_copy_conn_event(काष्ठा rdma_ucm_conn_param *dst,
				 काष्ठा rdma_conn_param *src)
अणु
	अगर (src->निजी_data_len)
		स_नकल(dst->निजी_data, src->निजी_data,
		       src->निजी_data_len);
	dst->निजी_data_len = src->निजी_data_len;
	dst->responder_resources = src->responder_resources;
	dst->initiator_depth = src->initiator_depth;
	dst->flow_control = src->flow_control;
	dst->retry_count = src->retry_count;
	dst->rnr_retry_count = src->rnr_retry_count;
	dst->srq = src->srq;
	dst->qp_num = src->qp_num;
पूर्ण

अटल व्योम ucma_copy_ud_event(काष्ठा ib_device *device,
			       काष्ठा rdma_ucm_ud_param *dst,
			       काष्ठा rdma_ud_param *src)
अणु
	अगर (src->निजी_data_len)
		स_नकल(dst->निजी_data, src->निजी_data,
		       src->निजी_data_len);
	dst->निजी_data_len = src->निजी_data_len;
	ib_copy_ah_attr_to_user(device, &dst->ah_attr, &src->ah_attr);
	dst->qp_num = src->qp_num;
	dst->qkey = src->qkey;
पूर्ण

अटल काष्ठा ucma_event *ucma_create_uevent(काष्ठा ucma_context *ctx,
					     काष्ठा rdma_cm_event *event)
अणु
	काष्ठा ucma_event *uevent;

	uevent = kzalloc(माप(*uevent), GFP_KERNEL);
	अगर (!uevent)
		वापस शून्य;

	uevent->ctx = ctx;
	चयन (event->event) अणु
	हाल RDMA_CM_EVENT_MULTICAST_JOIN:
	हाल RDMA_CM_EVENT_MULTICAST_ERROR:
		uevent->mc = (काष्ठा ucma_multicast *)
			     event->param.ud.निजी_data;
		uevent->resp.uid = uevent->mc->uid;
		uevent->resp.id = uevent->mc->id;
		अवरोध;
	शेष:
		uevent->resp.uid = ctx->uid;
		uevent->resp.id = ctx->id;
		अवरोध;
	पूर्ण
	uevent->resp.event = event->event;
	uevent->resp.status = event->status;
	अगर (ctx->cm_id->qp_type == IB_QPT_UD)
		ucma_copy_ud_event(ctx->cm_id->device, &uevent->resp.param.ud,
				   &event->param.ud);
	अन्यथा
		ucma_copy_conn_event(&uevent->resp.param.conn,
				     &event->param.conn);

	uevent->resp.ece.venकरोr_id = event->ece.venकरोr_id;
	uevent->resp.ece.attr_mod = event->ece.attr_mod;
	वापस uevent;
पूर्ण

अटल पूर्णांक ucma_connect_event_handler(काष्ठा rdma_cm_id *cm_id,
				      काष्ठा rdma_cm_event *event)
अणु
	काष्ठा ucma_context *listen_ctx = cm_id->context;
	काष्ठा ucma_context *ctx;
	काष्ठा ucma_event *uevent;

	अगर (!atomic_add_unless(&listen_ctx->backlog, -1, 0))
		वापस -ENOMEM;
	ctx = ucma_alloc_ctx(listen_ctx->file);
	अगर (!ctx)
		जाओ err_backlog;
	ucma_set_ctx_cm_id(ctx, cm_id);

	uevent = ucma_create_uevent(listen_ctx, event);
	अगर (!uevent)
		जाओ err_alloc;
	uevent->conn_req_ctx = ctx;
	uevent->resp.id = ctx->id;

	ctx->cm_id->context = ctx;

	mutex_lock(&ctx->file->mut);
	ucma_finish_ctx(ctx);
	list_add_tail(&uevent->list, &ctx->file->event_list);
	mutex_unlock(&ctx->file->mut);
	wake_up_पूर्णांकerruptible(&ctx->file->poll_रुको);
	वापस 0;

err_alloc:
	ucma_destroy_निजी_ctx(ctx);
err_backlog:
	atomic_inc(&listen_ctx->backlog);
	/* Returning error causes the new ID to be destroyed */
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक ucma_event_handler(काष्ठा rdma_cm_id *cm_id,
			      काष्ठा rdma_cm_event *event)
अणु
	काष्ठा ucma_event *uevent;
	काष्ठा ucma_context *ctx = cm_id->context;

	अगर (event->event == RDMA_CM_EVENT_CONNECT_REQUEST)
		वापस ucma_connect_event_handler(cm_id, event);

	/*
	 * We ignore events क्रम new connections until userspace has set their
	 * context.  This can only happen अगर an error occurs on a new connection
	 * beक्रमe the user accepts it.  This is okay, since the accept will just
	 * fail later. However, we करो need to release the underlying HW
	 * resources in हाल of a device removal event.
	 */
	अगर (ctx->uid) अणु
		uevent = ucma_create_uevent(ctx, event);
		अगर (!uevent)
			वापस 0;

		mutex_lock(&ctx->file->mut);
		list_add_tail(&uevent->list, &ctx->file->event_list);
		mutex_unlock(&ctx->file->mut);
		wake_up_पूर्णांकerruptible(&ctx->file->poll_रुको);
	पूर्ण

	अगर (event->event == RDMA_CM_EVENT_DEVICE_REMOVAL) अणु
		xa_lock(&ctx_table);
		अगर (xa_load(&ctx_table, ctx->id) == ctx)
			queue_work(प्रणाली_unbound_wq, &ctx->बंद_work);
		xa_unlock(&ctx_table);
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार ucma_get_event(काष्ठा ucma_file *file, स्थिर अक्षर __user *inbuf,
			      पूर्णांक in_len, पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_get_event cmd;
	काष्ठा ucma_event *uevent;

	/*
	 * Old 32 bit user space करोes not send the 4 byte padding in the
	 * reserved field. We करोn't care, allow it to keep working.
	 */
	अगर (out_len < माप(uevent->resp) - माप(uevent->resp.reserved) -
			      माप(uevent->resp.ece))
		वापस -ENOSPC;

	अगर (copy_from_user(&cmd, inbuf, माप(cmd)))
		वापस -EFAULT;

	mutex_lock(&file->mut);
	जबतक (list_empty(&file->event_list)) अणु
		mutex_unlock(&file->mut);

		अगर (file->filp->f_flags & O_NONBLOCK)
			वापस -EAGAIN;

		अगर (रुको_event_पूर्णांकerruptible(file->poll_रुको,
					     !list_empty(&file->event_list)))
			वापस -ERESTARTSYS;

		mutex_lock(&file->mut);
	पूर्ण

	uevent = list_first_entry(&file->event_list, काष्ठा ucma_event, list);

	अगर (copy_to_user(u64_to_user_ptr(cmd.response),
			 &uevent->resp,
			 min_t(माप_प्रकार, out_len, माप(uevent->resp)))) अणु
		mutex_unlock(&file->mut);
		वापस -EFAULT;
	पूर्ण

	list_del(&uevent->list);
	uevent->ctx->events_reported++;
	अगर (uevent->mc)
		uevent->mc->events_reported++;
	अगर (uevent->resp.event == RDMA_CM_EVENT_CONNECT_REQUEST)
		atomic_inc(&uevent->ctx->backlog);
	mutex_unlock(&file->mut);

	kमुक्त(uevent);
	वापस 0;
पूर्ण

अटल पूर्णांक ucma_get_qp_type(काष्ठा rdma_ucm_create_id *cmd, क्रमागत ib_qp_type *qp_type)
अणु
	चयन (cmd->ps) अणु
	हाल RDMA_PS_TCP:
		*qp_type = IB_QPT_RC;
		वापस 0;
	हाल RDMA_PS_UDP:
	हाल RDMA_PS_IPOIB:
		*qp_type = IB_QPT_UD;
		वापस 0;
	हाल RDMA_PS_IB:
		*qp_type = cmd->qp_type;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार ucma_create_id(काष्ठा ucma_file *file, स्थिर अक्षर __user *inbuf,
			      पूर्णांक in_len, पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_create_id cmd;
	काष्ठा rdma_ucm_create_id_resp resp;
	काष्ठा ucma_context *ctx;
	काष्ठा rdma_cm_id *cm_id;
	क्रमागत ib_qp_type qp_type;
	पूर्णांक ret;

	अगर (out_len < माप(resp))
		वापस -ENOSPC;

	अगर (copy_from_user(&cmd, inbuf, माप(cmd)))
		वापस -EFAULT;

	ret = ucma_get_qp_type(&cmd, &qp_type);
	अगर (ret)
		वापस ret;

	ctx = ucma_alloc_ctx(file);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->uid = cmd.uid;
	cm_id = rdma_create_user_id(ucma_event_handler, ctx, cmd.ps, qp_type);
	अगर (IS_ERR(cm_id)) अणु
		ret = PTR_ERR(cm_id);
		जाओ err1;
	पूर्ण
	ucma_set_ctx_cm_id(ctx, cm_id);

	resp.id = ctx->id;
	अगर (copy_to_user(u64_to_user_ptr(cmd.response),
			 &resp, माप(resp))) अणु
		ucma_destroy_निजी_ctx(ctx);
		वापस -EFAULT;
	पूर्ण

	mutex_lock(&file->mut);
	ucma_finish_ctx(ctx);
	mutex_unlock(&file->mut);
	वापस 0;

err1:
	ucma_destroy_निजी_ctx(ctx);
	वापस ret;
पूर्ण

अटल व्योम ucma_cleanup_multicast(काष्ठा ucma_context *ctx)
अणु
	काष्ठा ucma_multicast *mc;
	अचिन्हित दीर्घ index;

	xa_क्रम_each(&multicast_table, index, mc) अणु
		अगर (mc->ctx != ctx)
			जारी;
		/*
		 * At this poपूर्णांक mc->ctx->ref is 0 so the mc cannot leave the
		 * lock on the पढ़ोer and this is enough serialization
		 */
		xa_erase(&multicast_table, index);
		kमुक्त(mc);
	पूर्ण
पूर्ण

अटल व्योम ucma_cleanup_mc_events(काष्ठा ucma_multicast *mc)
अणु
	काष्ठा ucma_event *uevent, *पंचांगp;

	rdma_lock_handler(mc->ctx->cm_id);
	mutex_lock(&mc->ctx->file->mut);
	list_क्रम_each_entry_safe(uevent, पंचांगp, &mc->ctx->file->event_list, list) अणु
		अगर (uevent->mc != mc)
			जारी;

		list_del(&uevent->list);
		kमुक्त(uevent);
	पूर्ण
	mutex_unlock(&mc->ctx->file->mut);
	rdma_unlock_handler(mc->ctx->cm_id);
पूर्ण

अटल पूर्णांक ucma_cleanup_ctx_events(काष्ठा ucma_context *ctx)
अणु
	पूर्णांक events_reported;
	काष्ठा ucma_event *uevent, *पंचांगp;
	LIST_HEAD(list);

	/* Cleanup events not yet reported to the user.*/
	mutex_lock(&ctx->file->mut);
	list_क्रम_each_entry_safe(uevent, पंचांगp, &ctx->file->event_list, list) अणु
		अगर (uevent->ctx != ctx)
			जारी;

		अगर (uevent->resp.event == RDMA_CM_EVENT_CONNECT_REQUEST &&
		    xa_cmpxchg(&ctx_table, uevent->conn_req_ctx->id,
			       uevent->conn_req_ctx, XA_ZERO_ENTRY,
			       GFP_KERNEL) == uevent->conn_req_ctx) अणु
			list_move_tail(&uevent->list, &list);
			जारी;
		पूर्ण
		list_del(&uevent->list);
		kमुक्त(uevent);
	पूर्ण
	list_del(&ctx->list);
	events_reported = ctx->events_reported;
	mutex_unlock(&ctx->file->mut);

	/*
	 * If this was a listening ID then any connections spawned from it that
	 * have not been delivered to userspace are cleaned up too. Must be करोne
	 * outside any locks.
	 */
	list_क्रम_each_entry_safe(uevent, पंचांगp, &list, list) अणु
		ucma_destroy_निजी_ctx(uevent->conn_req_ctx);
		kमुक्त(uevent);
	पूर्ण
	वापस events_reported;
पूर्ण

/*
 * When this is called the xarray must have a XA_ZERO_ENTRY in the ctx->id (ie
 * the ctx is not खुला to the user). This either because:
 *  - ucma_finish_ctx() hasn't been called
 *  - xa_cmpxchg() succeed to हटाओ the entry (only one thपढ़ो can succeed)
 */
अटल पूर्णांक ucma_destroy_निजी_ctx(काष्ठा ucma_context *ctx)
अणु
	पूर्णांक events_reported;

	/*
	 * Destroy the underlying cm_id. New work queuing is prevented now by
	 * the removal from the xarray. Once the work is cancled ref will either
	 * be 0 because the work ran to completion and consumed the ref from the
	 * xarray, or it will be positive because we still have the ref from the
	 * xarray. This can also be 0 in हालs where cm_id was never set
	 */
	cancel_work_sync(&ctx->बंद_work);
	अगर (refcount_पढ़ो(&ctx->ref))
		ucma_बंद_id(&ctx->बंद_work);

	events_reported = ucma_cleanup_ctx_events(ctx);
	ucma_cleanup_multicast(ctx);

	WARN_ON(xa_cmpxchg(&ctx_table, ctx->id, XA_ZERO_ENTRY, शून्य,
			   GFP_KERNEL) != शून्य);
	mutex_destroy(&ctx->mutex);
	kमुक्त(ctx);
	वापस events_reported;
पूर्ण

अटल sमाप_प्रकार ucma_destroy_id(काष्ठा ucma_file *file, स्थिर अक्षर __user *inbuf,
			       पूर्णांक in_len, पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_destroy_id cmd;
	काष्ठा rdma_ucm_destroy_id_resp resp;
	काष्ठा ucma_context *ctx;
	पूर्णांक ret = 0;

	अगर (out_len < माप(resp))
		वापस -ENOSPC;

	अगर (copy_from_user(&cmd, inbuf, माप(cmd)))
		वापस -EFAULT;

	xa_lock(&ctx_table);
	ctx = _ucma_find_context(cmd.id, file);
	अगर (!IS_ERR(ctx)) अणु
		अगर (__xa_cmpxchg(&ctx_table, ctx->id, ctx, XA_ZERO_ENTRY,
				 GFP_KERNEL) != ctx)
			ctx = ERR_PTR(-ENOENT);
	पूर्ण
	xa_unlock(&ctx_table);

	अगर (IS_ERR(ctx))
		वापस PTR_ERR(ctx);

	resp.events_reported = ucma_destroy_निजी_ctx(ctx);
	अगर (copy_to_user(u64_to_user_ptr(cmd.response),
			 &resp, माप(resp)))
		ret = -EFAULT;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ucma_bind_ip(काष्ठा ucma_file *file, स्थिर अक्षर __user *inbuf,
			      पूर्णांक in_len, पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_bind_ip cmd;
	काष्ठा ucma_context *ctx;
	पूर्णांक ret;

	अगर (copy_from_user(&cmd, inbuf, माप(cmd)))
		वापस -EFAULT;

	अगर (!rdma_addr_size_in6(&cmd.addr))
		वापस -EINVAL;

	ctx = ucma_get_ctx(file, cmd.id);
	अगर (IS_ERR(ctx))
		वापस PTR_ERR(ctx);

	mutex_lock(&ctx->mutex);
	ret = rdma_bind_addr(ctx->cm_id, (काष्ठा sockaddr *) &cmd.addr);
	mutex_unlock(&ctx->mutex);

	ucma_put_ctx(ctx);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ucma_bind(काष्ठा ucma_file *file, स्थिर अक्षर __user *inbuf,
			 पूर्णांक in_len, पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_bind cmd;
	काष्ठा ucma_context *ctx;
	पूर्णांक ret;

	अगर (copy_from_user(&cmd, inbuf, माप(cmd)))
		वापस -EFAULT;

	अगर (cmd.reserved || !cmd.addr_size ||
	    cmd.addr_size != rdma_addr_size_kss(&cmd.addr))
		वापस -EINVAL;

	ctx = ucma_get_ctx(file, cmd.id);
	अगर (IS_ERR(ctx))
		वापस PTR_ERR(ctx);

	mutex_lock(&ctx->mutex);
	ret = rdma_bind_addr(ctx->cm_id, (काष्ठा sockaddr *) &cmd.addr);
	mutex_unlock(&ctx->mutex);
	ucma_put_ctx(ctx);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ucma_resolve_ip(काष्ठा ucma_file *file,
			       स्थिर अक्षर __user *inbuf,
			       पूर्णांक in_len, पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_resolve_ip cmd;
	काष्ठा ucma_context *ctx;
	पूर्णांक ret;

	अगर (copy_from_user(&cmd, inbuf, माप(cmd)))
		वापस -EFAULT;

	अगर ((cmd.src_addr.sin6_family && !rdma_addr_size_in6(&cmd.src_addr)) ||
	    !rdma_addr_size_in6(&cmd.dst_addr))
		वापस -EINVAL;

	ctx = ucma_get_ctx(file, cmd.id);
	अगर (IS_ERR(ctx))
		वापस PTR_ERR(ctx);

	mutex_lock(&ctx->mutex);
	ret = rdma_resolve_addr(ctx->cm_id, (काष्ठा sockaddr *) &cmd.src_addr,
				(काष्ठा sockaddr *) &cmd.dst_addr, cmd.समयout_ms);
	mutex_unlock(&ctx->mutex);
	ucma_put_ctx(ctx);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ucma_resolve_addr(काष्ठा ucma_file *file,
				 स्थिर अक्षर __user *inbuf,
				 पूर्णांक in_len, पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_resolve_addr cmd;
	काष्ठा ucma_context *ctx;
	पूर्णांक ret;

	अगर (copy_from_user(&cmd, inbuf, माप(cmd)))
		वापस -EFAULT;

	अगर (cmd.reserved ||
	    (cmd.src_size && (cmd.src_size != rdma_addr_size_kss(&cmd.src_addr))) ||
	    !cmd.dst_size || (cmd.dst_size != rdma_addr_size_kss(&cmd.dst_addr)))
		वापस -EINVAL;

	ctx = ucma_get_ctx(file, cmd.id);
	अगर (IS_ERR(ctx))
		वापस PTR_ERR(ctx);

	mutex_lock(&ctx->mutex);
	ret = rdma_resolve_addr(ctx->cm_id, (काष्ठा sockaddr *) &cmd.src_addr,
				(काष्ठा sockaddr *) &cmd.dst_addr, cmd.समयout_ms);
	mutex_unlock(&ctx->mutex);
	ucma_put_ctx(ctx);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ucma_resolve_route(काष्ठा ucma_file *file,
				  स्थिर अक्षर __user *inbuf,
				  पूर्णांक in_len, पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_resolve_route cmd;
	काष्ठा ucma_context *ctx;
	पूर्णांक ret;

	अगर (copy_from_user(&cmd, inbuf, माप(cmd)))
		वापस -EFAULT;

	ctx = ucma_get_ctx_dev(file, cmd.id);
	अगर (IS_ERR(ctx))
		वापस PTR_ERR(ctx);

	mutex_lock(&ctx->mutex);
	ret = rdma_resolve_route(ctx->cm_id, cmd.समयout_ms);
	mutex_unlock(&ctx->mutex);
	ucma_put_ctx(ctx);
	वापस ret;
पूर्ण

अटल व्योम ucma_copy_ib_route(काष्ठा rdma_ucm_query_route_resp *resp,
			       काष्ठा rdma_route *route)
अणु
	काष्ठा rdma_dev_addr *dev_addr;

	resp->num_paths = route->num_paths;
	चयन (route->num_paths) अणु
	हाल 0:
		dev_addr = &route->addr.dev_addr;
		rdma_addr_get_dgid(dev_addr,
				   (जोड़ ib_gid *) &resp->ib_route[0].dgid);
		rdma_addr_get_sgid(dev_addr,
				   (जोड़ ib_gid *) &resp->ib_route[0].sgid);
		resp->ib_route[0].pkey = cpu_to_be16(ib_addr_get_pkey(dev_addr));
		अवरोध;
	हाल 2:
		ib_copy_path_rec_to_user(&resp->ib_route[1],
					 &route->path_rec[1]);
		fallthrough;
	हाल 1:
		ib_copy_path_rec_to_user(&resp->ib_route[0],
					 &route->path_rec[0]);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ucma_copy_iboe_route(काष्ठा rdma_ucm_query_route_resp *resp,
				 काष्ठा rdma_route *route)
अणु

	resp->num_paths = route->num_paths;
	चयन (route->num_paths) अणु
	हाल 0:
		rdma_ip2gid((काष्ठा sockaddr *)&route->addr.dst_addr,
			    (जोड़ ib_gid *)&resp->ib_route[0].dgid);
		rdma_ip2gid((काष्ठा sockaddr *)&route->addr.src_addr,
			    (जोड़ ib_gid *)&resp->ib_route[0].sgid);
		resp->ib_route[0].pkey = cpu_to_be16(0xffff);
		अवरोध;
	हाल 2:
		ib_copy_path_rec_to_user(&resp->ib_route[1],
					 &route->path_rec[1]);
		fallthrough;
	हाल 1:
		ib_copy_path_rec_to_user(&resp->ib_route[0],
					 &route->path_rec[0]);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ucma_copy_iw_route(काष्ठा rdma_ucm_query_route_resp *resp,
			       काष्ठा rdma_route *route)
अणु
	काष्ठा rdma_dev_addr *dev_addr;

	dev_addr = &route->addr.dev_addr;
	rdma_addr_get_dgid(dev_addr, (जोड़ ib_gid *) &resp->ib_route[0].dgid);
	rdma_addr_get_sgid(dev_addr, (जोड़ ib_gid *) &resp->ib_route[0].sgid);
पूर्ण

अटल sमाप_प्रकार ucma_query_route(काष्ठा ucma_file *file,
				स्थिर अक्षर __user *inbuf,
				पूर्णांक in_len, पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_query cmd;
	काष्ठा rdma_ucm_query_route_resp resp;
	काष्ठा ucma_context *ctx;
	काष्ठा sockaddr *addr;
	पूर्णांक ret = 0;

	अगर (out_len < दुरत्व(काष्ठा rdma_ucm_query_route_resp, ibdev_index))
		वापस -ENOSPC;

	अगर (copy_from_user(&cmd, inbuf, माप(cmd)))
		वापस -EFAULT;

	ctx = ucma_get_ctx(file, cmd.id);
	अगर (IS_ERR(ctx))
		वापस PTR_ERR(ctx);

	mutex_lock(&ctx->mutex);
	स_रखो(&resp, 0, माप resp);
	addr = (काष्ठा sockaddr *) &ctx->cm_id->route.addr.src_addr;
	स_नकल(&resp.src_addr, addr, addr->sa_family == AF_INET ?
				     माप(काष्ठा sockaddr_in) :
				     माप(काष्ठा sockaddr_in6));
	addr = (काष्ठा sockaddr *) &ctx->cm_id->route.addr.dst_addr;
	स_नकल(&resp.dst_addr, addr, addr->sa_family == AF_INET ?
				     माप(काष्ठा sockaddr_in) :
				     माप(काष्ठा sockaddr_in6));
	अगर (!ctx->cm_id->device)
		जाओ out;

	resp.node_guid = (__क्रमce __u64) ctx->cm_id->device->node_guid;
	resp.ibdev_index = ctx->cm_id->device->index;
	resp.port_num = ctx->cm_id->port_num;

	अगर (rdma_cap_ib_sa(ctx->cm_id->device, ctx->cm_id->port_num))
		ucma_copy_ib_route(&resp, &ctx->cm_id->route);
	अन्यथा अगर (rdma_protocol_roce(ctx->cm_id->device, ctx->cm_id->port_num))
		ucma_copy_iboe_route(&resp, &ctx->cm_id->route);
	अन्यथा अगर (rdma_protocol_iwarp(ctx->cm_id->device, ctx->cm_id->port_num))
		ucma_copy_iw_route(&resp, &ctx->cm_id->route);

out:
	mutex_unlock(&ctx->mutex);
	अगर (copy_to_user(u64_to_user_ptr(cmd.response), &resp,
			 min_t(माप_प्रकार, out_len, माप(resp))))
		ret = -EFAULT;

	ucma_put_ctx(ctx);
	वापस ret;
पूर्ण

अटल व्योम ucma_query_device_addr(काष्ठा rdma_cm_id *cm_id,
				   काष्ठा rdma_ucm_query_addr_resp *resp)
अणु
	अगर (!cm_id->device)
		वापस;

	resp->node_guid = (__क्रमce __u64) cm_id->device->node_guid;
	resp->ibdev_index = cm_id->device->index;
	resp->port_num = cm_id->port_num;
	resp->pkey = (__क्रमce __u16) cpu_to_be16(
		     ib_addr_get_pkey(&cm_id->route.addr.dev_addr));
पूर्ण

अटल sमाप_प्रकार ucma_query_addr(काष्ठा ucma_context *ctx,
			       व्योम __user *response, पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_query_addr_resp resp;
	काष्ठा sockaddr *addr;
	पूर्णांक ret = 0;

	अगर (out_len < दुरत्व(काष्ठा rdma_ucm_query_addr_resp, ibdev_index))
		वापस -ENOSPC;

	स_रखो(&resp, 0, माप resp);

	addr = (काष्ठा sockaddr *) &ctx->cm_id->route.addr.src_addr;
	resp.src_size = rdma_addr_size(addr);
	स_नकल(&resp.src_addr, addr, resp.src_size);

	addr = (काष्ठा sockaddr *) &ctx->cm_id->route.addr.dst_addr;
	resp.dst_size = rdma_addr_size(addr);
	स_नकल(&resp.dst_addr, addr, resp.dst_size);

	ucma_query_device_addr(ctx->cm_id, &resp);

	अगर (copy_to_user(response, &resp, min_t(माप_प्रकार, out_len, माप(resp))))
		ret = -EFAULT;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ucma_query_path(काष्ठा ucma_context *ctx,
			       व्योम __user *response, पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_query_path_resp *resp;
	पूर्णांक i, ret = 0;

	अगर (out_len < माप(*resp))
		वापस -ENOSPC;

	resp = kzalloc(out_len, GFP_KERNEL);
	अगर (!resp)
		वापस -ENOMEM;

	resp->num_paths = ctx->cm_id->route.num_paths;
	क्रम (i = 0, out_len -= माप(*resp);
	     i < resp->num_paths && out_len > माप(काष्ठा ib_path_rec_data);
	     i++, out_len -= माप(काष्ठा ib_path_rec_data)) अणु
		काष्ठा sa_path_rec *rec = &ctx->cm_id->route.path_rec[i];

		resp->path_data[i].flags = IB_PATH_GMP | IB_PATH_PRIMARY |
					   IB_PATH_BIसूचीECTIONAL;
		अगर (rec->rec_type == SA_PATH_REC_TYPE_OPA) अणु
			काष्ठा sa_path_rec ib;

			sa_convert_path_opa_to_ib(&ib, rec);
			ib_sa_pack_path(&ib, &resp->path_data[i].path_rec);

		पूर्ण अन्यथा अणु
			ib_sa_pack_path(rec, &resp->path_data[i].path_rec);
		पूर्ण
	पूर्ण

	अगर (copy_to_user(response, resp, काष्ठा_size(resp, path_data, i)))
		ret = -EFAULT;

	kमुक्त(resp);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ucma_query_gid(काष्ठा ucma_context *ctx,
			      व्योम __user *response, पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_query_addr_resp resp;
	काष्ठा sockaddr_ib *addr;
	पूर्णांक ret = 0;

	अगर (out_len < दुरत्व(काष्ठा rdma_ucm_query_addr_resp, ibdev_index))
		वापस -ENOSPC;

	स_रखो(&resp, 0, माप resp);

	ucma_query_device_addr(ctx->cm_id, &resp);

	addr = (काष्ठा sockaddr_ib *) &resp.src_addr;
	resp.src_size = माप(*addr);
	अगर (ctx->cm_id->route.addr.src_addr.ss_family == AF_IB) अणु
		स_नकल(addr, &ctx->cm_id->route.addr.src_addr, resp.src_size);
	पूर्ण अन्यथा अणु
		addr->sib_family = AF_IB;
		addr->sib_pkey = (__क्रमce __be16) resp.pkey;
		rdma_पढ़ो_gids(ctx->cm_id, (जोड़ ib_gid *)&addr->sib_addr,
			       शून्य);
		addr->sib_sid = rdma_get_service_id(ctx->cm_id, (काष्ठा sockaddr *)
						    &ctx->cm_id->route.addr.src_addr);
	पूर्ण

	addr = (काष्ठा sockaddr_ib *) &resp.dst_addr;
	resp.dst_size = माप(*addr);
	अगर (ctx->cm_id->route.addr.dst_addr.ss_family == AF_IB) अणु
		स_नकल(addr, &ctx->cm_id->route.addr.dst_addr, resp.dst_size);
	पूर्ण अन्यथा अणु
		addr->sib_family = AF_IB;
		addr->sib_pkey = (__क्रमce __be16) resp.pkey;
		rdma_पढ़ो_gids(ctx->cm_id, शून्य,
			       (जोड़ ib_gid *)&addr->sib_addr);
		addr->sib_sid = rdma_get_service_id(ctx->cm_id, (काष्ठा sockaddr *)
						    &ctx->cm_id->route.addr.dst_addr);
	पूर्ण

	अगर (copy_to_user(response, &resp, min_t(माप_प्रकार, out_len, माप(resp))))
		ret = -EFAULT;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ucma_query(काष्ठा ucma_file *file,
			  स्थिर अक्षर __user *inbuf,
			  पूर्णांक in_len, पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_query cmd;
	काष्ठा ucma_context *ctx;
	व्योम __user *response;
	पूर्णांक ret;

	अगर (copy_from_user(&cmd, inbuf, माप(cmd)))
		वापस -EFAULT;

	response = u64_to_user_ptr(cmd.response);
	ctx = ucma_get_ctx(file, cmd.id);
	अगर (IS_ERR(ctx))
		वापस PTR_ERR(ctx);

	mutex_lock(&ctx->mutex);
	चयन (cmd.option) अणु
	हाल RDMA_USER_CM_QUERY_ADDR:
		ret = ucma_query_addr(ctx, response, out_len);
		अवरोध;
	हाल RDMA_USER_CM_QUERY_PATH:
		ret = ucma_query_path(ctx, response, out_len);
		अवरोध;
	हाल RDMA_USER_CM_QUERY_GID:
		ret = ucma_query_gid(ctx, response, out_len);
		अवरोध;
	शेष:
		ret = -ENOSYS;
		अवरोध;
	पूर्ण
	mutex_unlock(&ctx->mutex);

	ucma_put_ctx(ctx);
	वापस ret;
पूर्ण

अटल व्योम ucma_copy_conn_param(काष्ठा rdma_cm_id *id,
				 काष्ठा rdma_conn_param *dst,
				 काष्ठा rdma_ucm_conn_param *src)
अणु
	dst->निजी_data = src->निजी_data;
	dst->निजी_data_len = src->निजी_data_len;
	dst->responder_resources = src->responder_resources;
	dst->initiator_depth = src->initiator_depth;
	dst->flow_control = src->flow_control;
	dst->retry_count = src->retry_count;
	dst->rnr_retry_count = src->rnr_retry_count;
	dst->srq = src->srq;
	dst->qp_num = src->qp_num & 0xFFFFFF;
	dst->qkey = (id->route.addr.src_addr.ss_family == AF_IB) ? src->qkey : 0;
पूर्ण

अटल sमाप_प्रकार ucma_connect(काष्ठा ucma_file *file, स्थिर अक्षर __user *inbuf,
			    पूर्णांक in_len, पूर्णांक out_len)
अणु
	काष्ठा rdma_conn_param conn_param;
	काष्ठा rdma_ucm_ece ece = अणुपूर्ण;
	काष्ठा rdma_ucm_connect cmd;
	काष्ठा ucma_context *ctx;
	माप_प्रकार in_size;
	पूर्णांक ret;

	अगर (in_len < दुरत्वend(typeof(cmd), reserved))
		वापस -EINVAL;
	in_size = min_t(माप_प्रकार, in_len, माप(cmd));
	अगर (copy_from_user(&cmd, inbuf, in_size))
		वापस -EFAULT;

	अगर (!cmd.conn_param.valid)
		वापस -EINVAL;

	ctx = ucma_get_ctx_dev(file, cmd.id);
	अगर (IS_ERR(ctx))
		वापस PTR_ERR(ctx);

	ucma_copy_conn_param(ctx->cm_id, &conn_param, &cmd.conn_param);
	अगर (दुरत्वend(typeof(cmd), ece) <= in_size) अणु
		ece.venकरोr_id = cmd.ece.venकरोr_id;
		ece.attr_mod = cmd.ece.attr_mod;
	पूर्ण

	mutex_lock(&ctx->mutex);
	ret = rdma_connect_ece(ctx->cm_id, &conn_param, &ece);
	mutex_unlock(&ctx->mutex);
	ucma_put_ctx(ctx);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ucma_listen(काष्ठा ucma_file *file, स्थिर अक्षर __user *inbuf,
			   पूर्णांक in_len, पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_listen cmd;
	काष्ठा ucma_context *ctx;
	पूर्णांक ret;

	अगर (copy_from_user(&cmd, inbuf, माप(cmd)))
		वापस -EFAULT;

	ctx = ucma_get_ctx(file, cmd.id);
	अगर (IS_ERR(ctx))
		वापस PTR_ERR(ctx);

	अगर (cmd.backlog <= 0 || cmd.backlog > max_backlog)
		cmd.backlog = max_backlog;
	atomic_set(&ctx->backlog, cmd.backlog);

	mutex_lock(&ctx->mutex);
	ret = rdma_listen(ctx->cm_id, cmd.backlog);
	mutex_unlock(&ctx->mutex);
	ucma_put_ctx(ctx);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ucma_accept(काष्ठा ucma_file *file, स्थिर अक्षर __user *inbuf,
			   पूर्णांक in_len, पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_accept cmd;
	काष्ठा rdma_conn_param conn_param;
	काष्ठा rdma_ucm_ece ece = अणुपूर्ण;
	काष्ठा ucma_context *ctx;
	माप_प्रकार in_size;
	पूर्णांक ret;

	अगर (in_len < दुरत्वend(typeof(cmd), reserved))
		वापस -EINVAL;
	in_size = min_t(माप_प्रकार, in_len, माप(cmd));
	अगर (copy_from_user(&cmd, inbuf, in_size))
		वापस -EFAULT;

	ctx = ucma_get_ctx_dev(file, cmd.id);
	अगर (IS_ERR(ctx))
		वापस PTR_ERR(ctx);

	अगर (दुरत्वend(typeof(cmd), ece) <= in_size) अणु
		ece.venकरोr_id = cmd.ece.venकरोr_id;
		ece.attr_mod = cmd.ece.attr_mod;
	पूर्ण

	अगर (cmd.conn_param.valid) अणु
		ucma_copy_conn_param(ctx->cm_id, &conn_param, &cmd.conn_param);
		mutex_lock(&ctx->mutex);
		rdma_lock_handler(ctx->cm_id);
		ret = rdma_accept_ece(ctx->cm_id, &conn_param, &ece);
		अगर (!ret) अणु
			/* The uid must be set atomically with the handler */
			ctx->uid = cmd.uid;
		पूर्ण
		rdma_unlock_handler(ctx->cm_id);
		mutex_unlock(&ctx->mutex);
	पूर्ण अन्यथा अणु
		mutex_lock(&ctx->mutex);
		rdma_lock_handler(ctx->cm_id);
		ret = rdma_accept_ece(ctx->cm_id, शून्य, &ece);
		rdma_unlock_handler(ctx->cm_id);
		mutex_unlock(&ctx->mutex);
	पूर्ण
	ucma_put_ctx(ctx);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ucma_reject(काष्ठा ucma_file *file, स्थिर अक्षर __user *inbuf,
			   पूर्णांक in_len, पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_reject cmd;
	काष्ठा ucma_context *ctx;
	पूर्णांक ret;

	अगर (copy_from_user(&cmd, inbuf, माप(cmd)))
		वापस -EFAULT;

	अगर (!cmd.reason)
		cmd.reason = IB_CM_REJ_CONSUMER_DEFINED;

	चयन (cmd.reason) अणु
	हाल IB_CM_REJ_CONSUMER_DEFINED:
	हाल IB_CM_REJ_VENDOR_OPTION_NOT_SUPPORTED:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ctx = ucma_get_ctx_dev(file, cmd.id);
	अगर (IS_ERR(ctx))
		वापस PTR_ERR(ctx);

	mutex_lock(&ctx->mutex);
	ret = rdma_reject(ctx->cm_id, cmd.निजी_data, cmd.निजी_data_len,
			  cmd.reason);
	mutex_unlock(&ctx->mutex);
	ucma_put_ctx(ctx);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ucma_disconnect(काष्ठा ucma_file *file, स्थिर अक्षर __user *inbuf,
			       पूर्णांक in_len, पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_disconnect cmd;
	काष्ठा ucma_context *ctx;
	पूर्णांक ret;

	अगर (copy_from_user(&cmd, inbuf, माप(cmd)))
		वापस -EFAULT;

	ctx = ucma_get_ctx_dev(file, cmd.id);
	अगर (IS_ERR(ctx))
		वापस PTR_ERR(ctx);

	mutex_lock(&ctx->mutex);
	ret = rdma_disconnect(ctx->cm_id);
	mutex_unlock(&ctx->mutex);
	ucma_put_ctx(ctx);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ucma_init_qp_attr(काष्ठा ucma_file *file,
				 स्थिर अक्षर __user *inbuf,
				 पूर्णांक in_len, पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_init_qp_attr cmd;
	काष्ठा ib_uverbs_qp_attr resp;
	काष्ठा ucma_context *ctx;
	काष्ठा ib_qp_attr qp_attr;
	पूर्णांक ret;

	अगर (out_len < माप(resp))
		वापस -ENOSPC;

	अगर (copy_from_user(&cmd, inbuf, माप(cmd)))
		वापस -EFAULT;

	अगर (cmd.qp_state > IB_QPS_ERR)
		वापस -EINVAL;

	ctx = ucma_get_ctx_dev(file, cmd.id);
	अगर (IS_ERR(ctx))
		वापस PTR_ERR(ctx);

	resp.qp_attr_mask = 0;
	स_रखो(&qp_attr, 0, माप qp_attr);
	qp_attr.qp_state = cmd.qp_state;
	mutex_lock(&ctx->mutex);
	ret = rdma_init_qp_attr(ctx->cm_id, &qp_attr, &resp.qp_attr_mask);
	mutex_unlock(&ctx->mutex);
	अगर (ret)
		जाओ out;

	ib_copy_qp_attr_to_user(ctx->cm_id->device, &resp, &qp_attr);
	अगर (copy_to_user(u64_to_user_ptr(cmd.response),
			 &resp, माप(resp)))
		ret = -EFAULT;

out:
	ucma_put_ctx(ctx);
	वापस ret;
पूर्ण

अटल पूर्णांक ucma_set_option_id(काष्ठा ucma_context *ctx, पूर्णांक optname,
			      व्योम *optval, माप_प्रकार optlen)
अणु
	पूर्णांक ret = 0;

	चयन (optname) अणु
	हाल RDMA_OPTION_ID_TOS:
		अगर (optlen != माप(u8)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		rdma_set_service_type(ctx->cm_id, *((u8 *) optval));
		अवरोध;
	हाल RDMA_OPTION_ID_REUSEADDR:
		अगर (optlen != माप(पूर्णांक)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ret = rdma_set_reuseaddr(ctx->cm_id, *((पूर्णांक *) optval) ? 1 : 0);
		अवरोध;
	हाल RDMA_OPTION_ID_AFONLY:
		अगर (optlen != माप(पूर्णांक)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ret = rdma_set_afonly(ctx->cm_id, *((पूर्णांक *) optval) ? 1 : 0);
		अवरोध;
	हाल RDMA_OPTION_ID_ACK_TIMEOUT:
		अगर (optlen != माप(u8)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ret = rdma_set_ack_समयout(ctx->cm_id, *((u8 *)optval));
		अवरोध;
	शेष:
		ret = -ENOSYS;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ucma_set_ib_path(काष्ठा ucma_context *ctx,
			    काष्ठा ib_path_rec_data *path_data, माप_प्रकार optlen)
अणु
	काष्ठा sa_path_rec sa_path;
	काष्ठा rdma_cm_event event;
	पूर्णांक ret;

	अगर (optlen % माप(*path_data))
		वापस -EINVAL;

	क्रम (; optlen; optlen -= माप(*path_data), path_data++) अणु
		अगर (path_data->flags == (IB_PATH_GMP | IB_PATH_PRIMARY |
					 IB_PATH_BIसूचीECTIONAL))
			अवरोध;
	पूर्ण

	अगर (!optlen)
		वापस -EINVAL;

	अगर (!ctx->cm_id->device)
		वापस -EINVAL;

	स_रखो(&sa_path, 0, माप(sa_path));

	sa_path.rec_type = SA_PATH_REC_TYPE_IB;
	ib_sa_unpack_path(path_data->path_rec, &sa_path);

	अगर (rdma_cap_opa_ah(ctx->cm_id->device, ctx->cm_id->port_num)) अणु
		काष्ठा sa_path_rec opa;

		sa_convert_path_ib_to_opa(&opa, &sa_path);
		mutex_lock(&ctx->mutex);
		ret = rdma_set_ib_path(ctx->cm_id, &opa);
		mutex_unlock(&ctx->mutex);
	पूर्ण अन्यथा अणु
		mutex_lock(&ctx->mutex);
		ret = rdma_set_ib_path(ctx->cm_id, &sa_path);
		mutex_unlock(&ctx->mutex);
	पूर्ण
	अगर (ret)
		वापस ret;

	स_रखो(&event, 0, माप event);
	event.event = RDMA_CM_EVENT_ROUTE_RESOLVED;
	वापस ucma_event_handler(ctx->cm_id, &event);
पूर्ण

अटल पूर्णांक ucma_set_option_ib(काष्ठा ucma_context *ctx, पूर्णांक optname,
			      व्योम *optval, माप_प्रकार optlen)
अणु
	पूर्णांक ret;

	चयन (optname) अणु
	हाल RDMA_OPTION_IB_PATH:
		ret = ucma_set_ib_path(ctx, optval, optlen);
		अवरोध;
	शेष:
		ret = -ENOSYS;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ucma_set_option_level(काष्ठा ucma_context *ctx, पूर्णांक level,
				 पूर्णांक optname, व्योम *optval, माप_प्रकार optlen)
अणु
	पूर्णांक ret;

	चयन (level) अणु
	हाल RDMA_OPTION_ID:
		mutex_lock(&ctx->mutex);
		ret = ucma_set_option_id(ctx, optname, optval, optlen);
		mutex_unlock(&ctx->mutex);
		अवरोध;
	हाल RDMA_OPTION_IB:
		ret = ucma_set_option_ib(ctx, optname, optval, optlen);
		अवरोध;
	शेष:
		ret = -ENOSYS;
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ucma_set_option(काष्ठा ucma_file *file, स्थिर अक्षर __user *inbuf,
			       पूर्णांक in_len, पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_set_option cmd;
	काष्ठा ucma_context *ctx;
	व्योम *optval;
	पूर्णांक ret;

	अगर (copy_from_user(&cmd, inbuf, माप(cmd)))
		वापस -EFAULT;

	अगर (unlikely(cmd.optlen > KMALLOC_MAX_SIZE))
		वापस -EINVAL;

	ctx = ucma_get_ctx(file, cmd.id);
	अगर (IS_ERR(ctx))
		वापस PTR_ERR(ctx);

	optval = memdup_user(u64_to_user_ptr(cmd.optval),
			     cmd.optlen);
	अगर (IS_ERR(optval)) अणु
		ret = PTR_ERR(optval);
		जाओ out;
	पूर्ण

	ret = ucma_set_option_level(ctx, cmd.level, cmd.optname, optval,
				    cmd.optlen);
	kमुक्त(optval);

out:
	ucma_put_ctx(ctx);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ucma_notअगरy(काष्ठा ucma_file *file, स्थिर अक्षर __user *inbuf,
			   पूर्णांक in_len, पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_notअगरy cmd;
	काष्ठा ucma_context *ctx;
	पूर्णांक ret = -EINVAL;

	अगर (copy_from_user(&cmd, inbuf, माप(cmd)))
		वापस -EFAULT;

	ctx = ucma_get_ctx(file, cmd.id);
	अगर (IS_ERR(ctx))
		वापस PTR_ERR(ctx);

	mutex_lock(&ctx->mutex);
	अगर (ctx->cm_id->device)
		ret = rdma_notअगरy(ctx->cm_id, (क्रमागत ib_event_type)cmd.event);
	mutex_unlock(&ctx->mutex);

	ucma_put_ctx(ctx);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ucma_process_join(काष्ठा ucma_file *file,
				 काष्ठा rdma_ucm_join_mcast *cmd,  पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_create_id_resp resp;
	काष्ठा ucma_context *ctx;
	काष्ठा ucma_multicast *mc;
	काष्ठा sockaddr *addr;
	पूर्णांक ret;
	u8 join_state;

	अगर (out_len < माप(resp))
		वापस -ENOSPC;

	addr = (काष्ठा sockaddr *) &cmd->addr;
	अगर (cmd->addr_size != rdma_addr_size(addr))
		वापस -EINVAL;

	अगर (cmd->join_flags == RDMA_MC_JOIN_FLAG_FULLMEMBER)
		join_state = BIT(FULLMEMBER_JOIN);
	अन्यथा अगर (cmd->join_flags == RDMA_MC_JOIN_FLAG_SENDONLY_FULLMEMBER)
		join_state = BIT(SENDONLY_FULLMEMBER_JOIN);
	अन्यथा
		वापस -EINVAL;

	ctx = ucma_get_ctx_dev(file, cmd->id);
	अगर (IS_ERR(ctx))
		वापस PTR_ERR(ctx);

	mc = kzalloc(माप(*mc), GFP_KERNEL);
	अगर (!mc) अणु
		ret = -ENOMEM;
		जाओ err_put_ctx;
	पूर्ण

	mc->ctx = ctx;
	mc->join_state = join_state;
	mc->uid = cmd->uid;
	स_नकल(&mc->addr, addr, cmd->addr_size);

	अगर (xa_alloc(&multicast_table, &mc->id, शून्य, xa_limit_32b,
		     GFP_KERNEL)) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_mc;
	पूर्ण

	mutex_lock(&ctx->mutex);
	ret = rdma_join_multicast(ctx->cm_id, (काष्ठा sockaddr *)&mc->addr,
				  join_state, mc);
	mutex_unlock(&ctx->mutex);
	अगर (ret)
		जाओ err_xa_erase;

	resp.id = mc->id;
	अगर (copy_to_user(u64_to_user_ptr(cmd->response),
			 &resp, माप(resp))) अणु
		ret = -EFAULT;
		जाओ err_leave_multicast;
	पूर्ण

	xa_store(&multicast_table, mc->id, mc, 0);

	ucma_put_ctx(ctx);
	वापस 0;

err_leave_multicast:
	mutex_lock(&ctx->mutex);
	rdma_leave_multicast(ctx->cm_id, (काष्ठा sockaddr *) &mc->addr);
	mutex_unlock(&ctx->mutex);
	ucma_cleanup_mc_events(mc);
err_xa_erase:
	xa_erase(&multicast_table, mc->id);
err_मुक्त_mc:
	kमुक्त(mc);
err_put_ctx:
	ucma_put_ctx(ctx);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ucma_join_ip_multicast(काष्ठा ucma_file *file,
				      स्थिर अक्षर __user *inbuf,
				      पूर्णांक in_len, पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_join_ip_mcast cmd;
	काष्ठा rdma_ucm_join_mcast join_cmd;

	अगर (copy_from_user(&cmd, inbuf, माप(cmd)))
		वापस -EFAULT;

	join_cmd.response = cmd.response;
	join_cmd.uid = cmd.uid;
	join_cmd.id = cmd.id;
	join_cmd.addr_size = rdma_addr_size_in6(&cmd.addr);
	अगर (!join_cmd.addr_size)
		वापस -EINVAL;

	join_cmd.join_flags = RDMA_MC_JOIN_FLAG_FULLMEMBER;
	स_नकल(&join_cmd.addr, &cmd.addr, join_cmd.addr_size);

	वापस ucma_process_join(file, &join_cmd, out_len);
पूर्ण

अटल sमाप_प्रकार ucma_join_multicast(काष्ठा ucma_file *file,
				   स्थिर अक्षर __user *inbuf,
				   पूर्णांक in_len, पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_join_mcast cmd;

	अगर (copy_from_user(&cmd, inbuf, माप(cmd)))
		वापस -EFAULT;

	अगर (!rdma_addr_size_kss(&cmd.addr))
		वापस -EINVAL;

	वापस ucma_process_join(file, &cmd, out_len);
पूर्ण

अटल sमाप_प्रकार ucma_leave_multicast(काष्ठा ucma_file *file,
				    स्थिर अक्षर __user *inbuf,
				    पूर्णांक in_len, पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_destroy_id cmd;
	काष्ठा rdma_ucm_destroy_id_resp resp;
	काष्ठा ucma_multicast *mc;
	पूर्णांक ret = 0;

	अगर (out_len < माप(resp))
		वापस -ENOSPC;

	अगर (copy_from_user(&cmd, inbuf, माप(cmd)))
		वापस -EFAULT;

	xa_lock(&multicast_table);
	mc = xa_load(&multicast_table, cmd.id);
	अगर (!mc)
		mc = ERR_PTR(-ENOENT);
	अन्यथा अगर (READ_ONCE(mc->ctx->file) != file)
		mc = ERR_PTR(-EINVAL);
	अन्यथा अगर (!refcount_inc_not_zero(&mc->ctx->ref))
		mc = ERR_PTR(-ENXIO);
	अन्यथा
		__xa_erase(&multicast_table, mc->id);
	xa_unlock(&multicast_table);

	अगर (IS_ERR(mc)) अणु
		ret = PTR_ERR(mc);
		जाओ out;
	पूर्ण

	mutex_lock(&mc->ctx->mutex);
	rdma_leave_multicast(mc->ctx->cm_id, (काष्ठा sockaddr *) &mc->addr);
	mutex_unlock(&mc->ctx->mutex);

	ucma_cleanup_mc_events(mc);

	ucma_put_ctx(mc->ctx);
	resp.events_reported = mc->events_reported;
	kमुक्त(mc);

	अगर (copy_to_user(u64_to_user_ptr(cmd.response),
			 &resp, माप(resp)))
		ret = -EFAULT;
out:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ucma_migrate_id(काष्ठा ucma_file *new_file,
			       स्थिर अक्षर __user *inbuf,
			       पूर्णांक in_len, पूर्णांक out_len)
अणु
	काष्ठा rdma_ucm_migrate_id cmd;
	काष्ठा rdma_ucm_migrate_resp resp;
	काष्ठा ucma_event *uevent, *पंचांगp;
	काष्ठा ucma_context *ctx;
	LIST_HEAD(event_list);
	काष्ठा fd f;
	काष्ठा ucma_file *cur_file;
	पूर्णांक ret = 0;

	अगर (copy_from_user(&cmd, inbuf, माप(cmd)))
		वापस -EFAULT;

	/* Get current fd to protect against it being बंदd */
	f = fdget(cmd.fd);
	अगर (!f.file)
		वापस -ENOENT;
	अगर (f.file->f_op != &ucma_fops) अणु
		ret = -EINVAL;
		जाओ file_put;
	पूर्ण
	cur_file = f.file->निजी_data;

	/* Validate current fd and prevent deकाष्ठाion of id. */
	ctx = ucma_get_ctx(cur_file, cmd.id);
	अगर (IS_ERR(ctx)) अणु
		ret = PTR_ERR(ctx);
		जाओ file_put;
	पूर्ण

	rdma_lock_handler(ctx->cm_id);
	/*
	 * ctx->file can only be changed under the handler & xa_lock. xa_load()
	 * must be checked again to ensure the ctx hasn't begun deकाष्ठाion
	 * since the ucma_get_ctx().
	 */
	xa_lock(&ctx_table);
	अगर (_ucma_find_context(cmd.id, cur_file) != ctx) अणु
		xa_unlock(&ctx_table);
		ret = -ENOENT;
		जाओ err_unlock;
	पूर्ण
	ctx->file = new_file;
	xa_unlock(&ctx_table);

	mutex_lock(&cur_file->mut);
	list_del(&ctx->list);
	/*
	 * At this poपूर्णांक lock_handler() prevents addition of new uevents क्रम
	 * this ctx.
	 */
	list_क्रम_each_entry_safe(uevent, पंचांगp, &cur_file->event_list, list)
		अगर (uevent->ctx == ctx)
			list_move_tail(&uevent->list, &event_list);
	resp.events_reported = ctx->events_reported;
	mutex_unlock(&cur_file->mut);

	mutex_lock(&new_file->mut);
	list_add_tail(&ctx->list, &new_file->ctx_list);
	list_splice_tail(&event_list, &new_file->event_list);
	mutex_unlock(&new_file->mut);

	अगर (copy_to_user(u64_to_user_ptr(cmd.response),
			 &resp, माप(resp)))
		ret = -EFAULT;

err_unlock:
	rdma_unlock_handler(ctx->cm_id);
	ucma_put_ctx(ctx);
file_put:
	fdput(f);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार (*ucma_cmd_table[])(काष्ठा ucma_file *file,
				   स्थिर अक्षर __user *inbuf,
				   पूर्णांक in_len, पूर्णांक out_len) = अणु
	[RDMA_USER_CM_CMD_CREATE_ID] 	 = ucma_create_id,
	[RDMA_USER_CM_CMD_DESTROY_ID]	 = ucma_destroy_id,
	[RDMA_USER_CM_CMD_BIND_IP]	 = ucma_bind_ip,
	[RDMA_USER_CM_CMD_RESOLVE_IP]	 = ucma_resolve_ip,
	[RDMA_USER_CM_CMD_RESOLVE_ROUTE] = ucma_resolve_route,
	[RDMA_USER_CM_CMD_QUERY_ROUTE]	 = ucma_query_route,
	[RDMA_USER_CM_CMD_CONNECT]	 = ucma_connect,
	[RDMA_USER_CM_CMD_LISTEN]	 = ucma_listen,
	[RDMA_USER_CM_CMD_ACCEPT]	 = ucma_accept,
	[RDMA_USER_CM_CMD_REJECT]	 = ucma_reject,
	[RDMA_USER_CM_CMD_DISCONNECT]	 = ucma_disconnect,
	[RDMA_USER_CM_CMD_INIT_QP_ATTR]	 = ucma_init_qp_attr,
	[RDMA_USER_CM_CMD_GET_EVENT]	 = ucma_get_event,
	[RDMA_USER_CM_CMD_GET_OPTION]	 = शून्य,
	[RDMA_USER_CM_CMD_SET_OPTION]	 = ucma_set_option,
	[RDMA_USER_CM_CMD_NOTIFY]	 = ucma_notअगरy,
	[RDMA_USER_CM_CMD_JOIN_IP_MCAST] = ucma_join_ip_multicast,
	[RDMA_USER_CM_CMD_LEAVE_MCAST]	 = ucma_leave_multicast,
	[RDMA_USER_CM_CMD_MIGRATE_ID]	 = ucma_migrate_id,
	[RDMA_USER_CM_CMD_QUERY]	 = ucma_query,
	[RDMA_USER_CM_CMD_BIND]		 = ucma_bind,
	[RDMA_USER_CM_CMD_RESOLVE_ADDR]	 = ucma_resolve_addr,
	[RDMA_USER_CM_CMD_JOIN_MCAST]	 = ucma_join_multicast
पूर्ण;

अटल sमाप_प्रकार ucma_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			  माप_प्रकार len, loff_t *pos)
अणु
	काष्ठा ucma_file *file = filp->निजी_data;
	काष्ठा rdma_ucm_cmd_hdr hdr;
	sमाप_प्रकार ret;

	अगर (!ib_safe_file_access(filp)) अणु
		pr_err_once("%s: process %d (%s) changed security contexts after opening file descriptor, this is not allowed.\n",
			    __func__, task_tgid_vnr(current), current->comm);
		वापस -EACCES;
	पूर्ण

	अगर (len < माप(hdr))
		वापस -EINVAL;

	अगर (copy_from_user(&hdr, buf, माप(hdr)))
		वापस -EFAULT;

	अगर (hdr.cmd >= ARRAY_SIZE(ucma_cmd_table))
		वापस -EINVAL;
	hdr.cmd = array_index_nospec(hdr.cmd, ARRAY_SIZE(ucma_cmd_table));

	अगर (hdr.in + माप(hdr) > len)
		वापस -EINVAL;

	अगर (!ucma_cmd_table[hdr.cmd])
		वापस -ENOSYS;

	ret = ucma_cmd_table[hdr.cmd](file, buf + माप(hdr), hdr.in, hdr.out);
	अगर (!ret)
		ret = len;

	वापस ret;
पूर्ण

अटल __poll_t ucma_poll(काष्ठा file *filp, काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा ucma_file *file = filp->निजी_data;
	__poll_t mask = 0;

	poll_रुको(filp, &file->poll_रुको, रुको);

	अगर (!list_empty(&file->event_list))
		mask = EPOLLIN | EPOLLRDNORM;

	वापस mask;
पूर्ण

/*
 * ucma_खोलो() करोes not need the BKL:
 *
 *  - no global state is referred to;
 *  - there is no ioctl method to race against;
 *  - no further module initialization is required क्रम खोलो to work
 *    after the device is रेजिस्टरed.
 */
अटल पूर्णांक ucma_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा ucma_file *file;

	file = kदो_स्मृति(माप *file, GFP_KERNEL);
	अगर (!file)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&file->event_list);
	INIT_LIST_HEAD(&file->ctx_list);
	init_रुकोqueue_head(&file->poll_रुको);
	mutex_init(&file->mut);

	filp->निजी_data = file;
	file->filp = filp;

	वापस stream_खोलो(inode, filp);
पूर्ण

अटल पूर्णांक ucma_बंद(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा ucma_file *file = filp->निजी_data;

	/*
	 * All paths that touch ctx_list or ctx_list starting from ग_लिखो() are
	 * prevented by this being a FD release function. The list_add_tail() in
	 * ucma_connect_event_handler() can run concurrently, however it only
	 * adds to the list *after* a listening ID. By only पढ़ोing the first of
	 * the list, and relying on ucma_destroy_निजी_ctx() to block
	 * ucma_connect_event_handler(), no additional locking is needed.
	 */
	जबतक (!list_empty(&file->ctx_list)) अणु
		काष्ठा ucma_context *ctx = list_first_entry(
			&file->ctx_list, काष्ठा ucma_context, list);

		WARN_ON(xa_cmpxchg(&ctx_table, ctx->id, ctx, XA_ZERO_ENTRY,
				   GFP_KERNEL) != ctx);
		ucma_destroy_निजी_ctx(ctx);
	पूर्ण
	kमुक्त(file);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations ucma_fops = अणु
	.owner 	 = THIS_MODULE,
	.खोलो 	 = ucma_खोलो,
	.release = ucma_बंद,
	.ग_लिखो	 = ucma_ग_लिखो,
	.poll    = ucma_poll,
	.llseek	 = no_llseek,
पूर्ण;

अटल काष्ठा miscdevice ucma_misc = अणु
	.minor		= MISC_DYNAMIC_MINOR,
	.name		= "rdma_cm",
	.nodename	= "infiniband/rdma_cm",
	.mode		= 0666,
	.fops		= &ucma_fops,
पूर्ण;

अटल पूर्णांक ucma_get_global_nl_info(काष्ठा ib_client_nl_info *res)
अणु
	res->abi = RDMA_USER_CM_ABI_VERSION;
	res->cdev = ucma_misc.this_device;
	वापस 0;
पूर्ण

अटल काष्ठा ib_client rdma_cma_client = अणु
	.name = "rdma_cm",
	.get_global_nl_info = ucma_get_global_nl_info,
पूर्ण;
MODULE_ALIAS_RDMA_CLIENT("rdma_cm");

अटल sमाप_प्रकार show_abi_version(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", RDMA_USER_CM_ABI_VERSION);
पूर्ण
अटल DEVICE_ATTR(abi_version, S_IRUGO, show_abi_version, शून्य);

अटल पूर्णांक __init ucma_init(व्योम)
अणु
	पूर्णांक ret;

	ret = misc_रेजिस्टर(&ucma_misc);
	अगर (ret)
		वापस ret;

	ret = device_create_file(ucma_misc.this_device, &dev_attr_abi_version);
	अगर (ret) अणु
		pr_err("rdma_ucm: couldn't create abi_version attr\n");
		जाओ err1;
	पूर्ण

	ucma_ctl_table_hdr = रेजिस्टर_net_sysctl(&init_net, "net/rdma_ucm", ucma_ctl_table);
	अगर (!ucma_ctl_table_hdr) अणु
		pr_err("rdma_ucm: couldn't register sysctl paths\n");
		ret = -ENOMEM;
		जाओ err2;
	पूर्ण

	ret = ib_रेजिस्टर_client(&rdma_cma_client);
	अगर (ret)
		जाओ err3;

	वापस 0;
err3:
	unरेजिस्टर_net_sysctl_table(ucma_ctl_table_hdr);
err2:
	device_हटाओ_file(ucma_misc.this_device, &dev_attr_abi_version);
err1:
	misc_deरेजिस्टर(&ucma_misc);
	वापस ret;
पूर्ण

अटल व्योम __निकास ucma_cleanup(व्योम)
अणु
	ib_unरेजिस्टर_client(&rdma_cma_client);
	unरेजिस्टर_net_sysctl_table(ucma_ctl_table_hdr);
	device_हटाओ_file(ucma_misc.this_device, &dev_attr_abi_version);
	misc_deरेजिस्टर(&ucma_misc);
पूर्ण

module_init(ucma_init);
module_निकास(ucma_cleanup);
