<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, Linaro Limited
 */
#समावेश <linux/arm-smccc.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/tee_drv.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>
#समावेश "optee_private.h"
#समावेश "optee_smc.h"
#घोषणा CREATE_TRACE_POINTS
#समावेश "optee_trace.h"

काष्ठा optee_call_रुकोer अणु
	काष्ठा list_head list_node;
	काष्ठा completion c;
पूर्ण;

अटल व्योम optee_cq_रुको_init(काष्ठा optee_call_queue *cq,
			       काष्ठा optee_call_रुकोer *w)
अणु
	/*
	 * We're preparing to make a call to secure world. In case we can't
	 * allocate a thपढ़ो in secure world we'll end up रुकोing in
	 * optee_cq_रुको_क्रम_completion().
	 *
	 * Normally अगर there's no contention in secure world the call will
	 * complete and we can cleanup directly with optee_cq_रुको_final().
	 */
	mutex_lock(&cq->mutex);

	/*
	 * We add ourselves to the queue, but we करोn't रुको. This
	 * guarantees that we करोn't lose a completion अगर secure world
	 * वापसs busy and another thपढ़ो just निकासed and try to complete
	 * someone.
	 */
	init_completion(&w->c);
	list_add_tail(&w->list_node, &cq->रुकोers);

	mutex_unlock(&cq->mutex);
पूर्ण

अटल व्योम optee_cq_रुको_क्रम_completion(काष्ठा optee_call_queue *cq,
					 काष्ठा optee_call_रुकोer *w)
अणु
	रुको_क्रम_completion(&w->c);

	mutex_lock(&cq->mutex);

	/* Move to end of list to get out of the way क्रम other रुकोers */
	list_del(&w->list_node);
	reinit_completion(&w->c);
	list_add_tail(&w->list_node, &cq->रुकोers);

	mutex_unlock(&cq->mutex);
पूर्ण

अटल व्योम optee_cq_complete_one(काष्ठा optee_call_queue *cq)
अणु
	काष्ठा optee_call_रुकोer *w;

	list_क्रम_each_entry(w, &cq->रुकोers, list_node) अणु
		अगर (!completion_करोne(&w->c)) अणु
			complete(&w->c);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम optee_cq_रुको_final(काष्ठा optee_call_queue *cq,
				काष्ठा optee_call_रुकोer *w)
अणु
	/*
	 * We're करोne with the call to secure world. The thपढ़ो in secure
	 * world that was used क्रम this call is now available क्रम some
	 * other task to use.
	 */
	mutex_lock(&cq->mutex);

	/* Get out of the list */
	list_del(&w->list_node);

	/* Wake up one eventual रुकोing task */
	optee_cq_complete_one(cq);

	/*
	 * If we're completed we've got a completion from another task that
	 * was just करोne with its call to secure world. Since yet another
	 * thपढ़ो now is available in secure world wake up another eventual
	 * रुकोing task.
	 */
	अगर (completion_करोne(&w->c))
		optee_cq_complete_one(cq);

	mutex_unlock(&cq->mutex);
पूर्ण

/* Requires the filpstate mutex to be held */
अटल काष्ठा optee_session *find_session(काष्ठा optee_context_data *ctxdata,
					  u32 session_id)
अणु
	काष्ठा optee_session *sess;

	list_क्रम_each_entry(sess, &ctxdata->sess_list, list_node)
		अगर (sess->session_id == session_id)
			वापस sess;

	वापस शून्य;
पूर्ण

/**
 * optee_करो_call_with_arg() - Do an SMC to OP-TEE in secure world
 * @ctx:	calling context
 * @parg:	physical address of message to pass to secure world
 *
 * Does and SMC to OP-TEE in secure world and handles eventual resulting
 * Remote Procedure Calls (RPC) from OP-TEE.
 *
 * Returns वापस code from secure world, 0 is OK
 */
u32 optee_करो_call_with_arg(काष्ठा tee_context *ctx, phys_addr_t parg)
अणु
	काष्ठा optee *optee = tee_get_drvdata(ctx->teedev);
	काष्ठा optee_call_रुकोer w;
	काष्ठा optee_rpc_param param = अणु पूर्ण;
	काष्ठा optee_call_ctx call_ctx = अणु पूर्ण;
	u32 ret;

	param.a0 = OPTEE_SMC_CALL_WITH_ARG;
	reg_pair_from_64(&param.a1, &param.a2, parg);
	/* Initialize रुकोer */
	optee_cq_रुको_init(&optee->call_queue, &w);
	जबतक (true) अणु
		काष्ठा arm_smccc_res res;

		trace_optee_invoke_fn_begin(&param);
		optee->invoke_fn(param.a0, param.a1, param.a2, param.a3,
				 param.a4, param.a5, param.a6, param.a7,
				 &res);
		trace_optee_invoke_fn_end(&param, &res);

		अगर (res.a0 == OPTEE_SMC_RETURN_ETHREAD_LIMIT) अणु
			/*
			 * Out of thपढ़ोs in secure world, रुको क्रम a thपढ़ो
			 * become available.
			 */
			optee_cq_रुको_क्रम_completion(&optee->call_queue, &w);
		पूर्ण अन्यथा अगर (OPTEE_SMC_RETURN_IS_RPC(res.a0)) अणु
			cond_resched();
			param.a0 = res.a0;
			param.a1 = res.a1;
			param.a2 = res.a2;
			param.a3 = res.a3;
			optee_handle_rpc(ctx, &param, &call_ctx);
		पूर्ण अन्यथा अणु
			ret = res.a0;
			अवरोध;
		पूर्ण
	पूर्ण

	optee_rpc_finalize_call(&call_ctx);
	/*
	 * We're done with our thread in secure world, if there's any
	 * thपढ़ो रुकोers wake up one.
	 */
	optee_cq_रुको_final(&optee->call_queue, &w);

	वापस ret;
पूर्ण

अटल काष्ठा tee_shm *get_msg_arg(काष्ठा tee_context *ctx, माप_प्रकार num_params,
				   काष्ठा optee_msg_arg **msg_arg,
				   phys_addr_t *msg_parg)
अणु
	पूर्णांक rc;
	काष्ठा tee_shm *shm;
	काष्ठा optee_msg_arg *ma;

	shm = tee_shm_alloc(ctx, OPTEE_MSG_GET_ARG_SIZE(num_params),
			    TEE_SHM_MAPPED);
	अगर (IS_ERR(shm))
		वापस shm;

	ma = tee_shm_get_va(shm, 0);
	अगर (IS_ERR(ma)) अणु
		rc = PTR_ERR(ma);
		जाओ out;
	पूर्ण

	rc = tee_shm_get_pa(shm, 0, msg_parg);
	अगर (rc)
		जाओ out;

	स_रखो(ma, 0, OPTEE_MSG_GET_ARG_SIZE(num_params));
	ma->num_params = num_params;
	*msg_arg = ma;
out:
	अगर (rc) अणु
		tee_shm_मुक्त(shm);
		वापस ERR_PTR(rc);
	पूर्ण

	वापस shm;
पूर्ण

पूर्णांक optee_खोलो_session(काष्ठा tee_context *ctx,
		       काष्ठा tee_ioctl_खोलो_session_arg *arg,
		       काष्ठा tee_param *param)
अणु
	काष्ठा optee_context_data *ctxdata = ctx->data;
	पूर्णांक rc;
	काष्ठा tee_shm *shm;
	काष्ठा optee_msg_arg *msg_arg;
	phys_addr_t msg_parg;
	काष्ठा optee_session *sess = शून्य;
	uuid_t client_uuid;

	/* +2 क्रम the meta parameters added below */
	shm = get_msg_arg(ctx, arg->num_params + 2, &msg_arg, &msg_parg);
	अगर (IS_ERR(shm))
		वापस PTR_ERR(shm);

	msg_arg->cmd = OPTEE_MSG_CMD_OPEN_SESSION;
	msg_arg->cancel_id = arg->cancel_id;

	/*
	 * Initialize and add the meta parameters needed when खोलोing a
	 * session.
	 */
	msg_arg->params[0].attr = OPTEE_MSG_ATTR_TYPE_VALUE_INPUT |
				  OPTEE_MSG_ATTR_META;
	msg_arg->params[1].attr = OPTEE_MSG_ATTR_TYPE_VALUE_INPUT |
				  OPTEE_MSG_ATTR_META;
	स_नकल(&msg_arg->params[0].u.value, arg->uuid, माप(arg->uuid));
	msg_arg->params[1].u.value.c = arg->clnt_login;

	rc = tee_session_calc_client_uuid(&client_uuid, arg->clnt_login,
					  arg->clnt_uuid);
	अगर (rc)
		जाओ out;
	export_uuid(msg_arg->params[1].u.octets, &client_uuid);

	rc = optee_to_msg_param(msg_arg->params + 2, arg->num_params, param);
	अगर (rc)
		जाओ out;

	sess = kzalloc(माप(*sess), GFP_KERNEL);
	अगर (!sess) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (optee_करो_call_with_arg(ctx, msg_parg)) अणु
		msg_arg->ret = TEEC_ERROR_COMMUNICATION;
		msg_arg->ret_origin = TEEC_ORIGIN_COMMS;
	पूर्ण

	अगर (msg_arg->ret == TEEC_SUCCESS) अणु
		/* A new session has been created, add it to the list. */
		sess->session_id = msg_arg->session;
		mutex_lock(&ctxdata->mutex);
		list_add(&sess->list_node, &ctxdata->sess_list);
		mutex_unlock(&ctxdata->mutex);
	पूर्ण अन्यथा अणु
		kमुक्त(sess);
	पूर्ण

	अगर (optee_from_msg_param(param, arg->num_params, msg_arg->params + 2)) अणु
		arg->ret = TEEC_ERROR_COMMUNICATION;
		arg->ret_origin = TEEC_ORIGIN_COMMS;
		/* Close session again to aव्योम leakage */
		optee_बंद_session(ctx, msg_arg->session);
	पूर्ण अन्यथा अणु
		arg->session = msg_arg->session;
		arg->ret = msg_arg->ret;
		arg->ret_origin = msg_arg->ret_origin;
	पूर्ण
out:
	tee_shm_मुक्त(shm);

	वापस rc;
पूर्ण

पूर्णांक optee_बंद_session(काष्ठा tee_context *ctx, u32 session)
अणु
	काष्ठा optee_context_data *ctxdata = ctx->data;
	काष्ठा tee_shm *shm;
	काष्ठा optee_msg_arg *msg_arg;
	phys_addr_t msg_parg;
	काष्ठा optee_session *sess;

	/* Check that the session is valid and हटाओ it from the list */
	mutex_lock(&ctxdata->mutex);
	sess = find_session(ctxdata, session);
	अगर (sess)
		list_del(&sess->list_node);
	mutex_unlock(&ctxdata->mutex);
	अगर (!sess)
		वापस -EINVAL;
	kमुक्त(sess);

	shm = get_msg_arg(ctx, 0, &msg_arg, &msg_parg);
	अगर (IS_ERR(shm))
		वापस PTR_ERR(shm);

	msg_arg->cmd = OPTEE_MSG_CMD_CLOSE_SESSION;
	msg_arg->session = session;
	optee_करो_call_with_arg(ctx, msg_parg);

	tee_shm_मुक्त(shm);
	वापस 0;
पूर्ण

पूर्णांक optee_invoke_func(काष्ठा tee_context *ctx, काष्ठा tee_ioctl_invoke_arg *arg,
		      काष्ठा tee_param *param)
अणु
	काष्ठा optee_context_data *ctxdata = ctx->data;
	काष्ठा tee_shm *shm;
	काष्ठा optee_msg_arg *msg_arg;
	phys_addr_t msg_parg;
	काष्ठा optee_session *sess;
	पूर्णांक rc;

	/* Check that the session is valid */
	mutex_lock(&ctxdata->mutex);
	sess = find_session(ctxdata, arg->session);
	mutex_unlock(&ctxdata->mutex);
	अगर (!sess)
		वापस -EINVAL;

	shm = get_msg_arg(ctx, arg->num_params, &msg_arg, &msg_parg);
	अगर (IS_ERR(shm))
		वापस PTR_ERR(shm);
	msg_arg->cmd = OPTEE_MSG_CMD_INVOKE_COMMAND;
	msg_arg->func = arg->func;
	msg_arg->session = arg->session;
	msg_arg->cancel_id = arg->cancel_id;

	rc = optee_to_msg_param(msg_arg->params, arg->num_params, param);
	अगर (rc)
		जाओ out;

	अगर (optee_करो_call_with_arg(ctx, msg_parg)) अणु
		msg_arg->ret = TEEC_ERROR_COMMUNICATION;
		msg_arg->ret_origin = TEEC_ORIGIN_COMMS;
	पूर्ण

	अगर (optee_from_msg_param(param, arg->num_params, msg_arg->params)) अणु
		msg_arg->ret = TEEC_ERROR_COMMUNICATION;
		msg_arg->ret_origin = TEEC_ORIGIN_COMMS;
	पूर्ण

	arg->ret = msg_arg->ret;
	arg->ret_origin = msg_arg->ret_origin;
out:
	tee_shm_मुक्त(shm);
	वापस rc;
पूर्ण

पूर्णांक optee_cancel_req(काष्ठा tee_context *ctx, u32 cancel_id, u32 session)
अणु
	काष्ठा optee_context_data *ctxdata = ctx->data;
	काष्ठा tee_shm *shm;
	काष्ठा optee_msg_arg *msg_arg;
	phys_addr_t msg_parg;
	काष्ठा optee_session *sess;

	/* Check that the session is valid */
	mutex_lock(&ctxdata->mutex);
	sess = find_session(ctxdata, session);
	mutex_unlock(&ctxdata->mutex);
	अगर (!sess)
		वापस -EINVAL;

	shm = get_msg_arg(ctx, 0, &msg_arg, &msg_parg);
	अगर (IS_ERR(shm))
		वापस PTR_ERR(shm);

	msg_arg->cmd = OPTEE_MSG_CMD_CANCEL;
	msg_arg->session = session;
	msg_arg->cancel_id = cancel_id;
	optee_करो_call_with_arg(ctx, msg_parg);

	tee_shm_मुक्त(shm);
	वापस 0;
पूर्ण

/**
 * optee_enable_shm_cache() - Enables caching of some shared memory allocation
 *			      in OP-TEE
 * @optee:	मुख्य service काष्ठा
 */
व्योम optee_enable_shm_cache(काष्ठा optee *optee)
अणु
	काष्ठा optee_call_रुकोer w;

	/* We need to retry until secure world isn't busy. */
	optee_cq_रुको_init(&optee->call_queue, &w);
	जबतक (true) अणु
		काष्ठा arm_smccc_res res;

		optee->invoke_fn(OPTEE_SMC_ENABLE_SHM_CACHE, 0, 0, 0, 0, 0, 0,
				 0, &res);
		अगर (res.a0 == OPTEE_SMC_RETURN_OK)
			अवरोध;
		optee_cq_रुको_क्रम_completion(&optee->call_queue, &w);
	पूर्ण
	optee_cq_रुको_final(&optee->call_queue, &w);
पूर्ण

/**
 * optee_disable_shm_cache() - Disables caching of some shared memory allocation
 *			      in OP-TEE
 * @optee:	मुख्य service काष्ठा
 */
व्योम optee_disable_shm_cache(काष्ठा optee *optee)
अणु
	काष्ठा optee_call_रुकोer w;

	/* We need to retry until secure world isn't busy. */
	optee_cq_रुको_init(&optee->call_queue, &w);
	जबतक (true) अणु
		जोड़ अणु
			काष्ठा arm_smccc_res smccc;
			काष्ठा optee_smc_disable_shm_cache_result result;
		पूर्ण res;

		optee->invoke_fn(OPTEE_SMC_DISABLE_SHM_CACHE, 0, 0, 0, 0, 0, 0,
				 0, &res.smccc);
		अगर (res.result.status == OPTEE_SMC_RETURN_ENOTAVAIL)
			अवरोध; /* All shm's मुक्तd */
		अगर (res.result.status == OPTEE_SMC_RETURN_OK) अणु
			काष्ठा tee_shm *shm;

			shm = reg_pair_to_ptr(res.result.shm_upper32,
					      res.result.shm_lower32);
			tee_shm_मुक्त(shm);
		पूर्ण अन्यथा अणु
			optee_cq_रुको_क्रम_completion(&optee->call_queue, &w);
		पूर्ण
	पूर्ण
	optee_cq_रुको_final(&optee->call_queue, &w);
पूर्ण

#घोषणा PAGELIST_ENTRIES_PER_PAGE				\
	((OPTEE_MSG_NONCONTIG_PAGE_SIZE / माप(u64)) - 1)

/**
 * optee_fill_pages_list() - ग_लिखो list of user pages to given shared
 * buffer.
 *
 * @dst: page-aligned buffer where list of pages will be stored
 * @pages: array of pages that represents shared buffer
 * @num_pages: number of entries in @pages
 * @page_offset: offset of user buffer from page start
 *
 * @dst should be big enough to hold list of user page addresses and
 *	links to the next pages of buffer
 */
व्योम optee_fill_pages_list(u64 *dst, काष्ठा page **pages, पूर्णांक num_pages,
			   माप_प्रकार page_offset)
अणु
	पूर्णांक n = 0;
	phys_addr_t optee_page;
	/*
	 * Refer to OPTEE_MSG_ATTR_NONCONTIG description in optee_msg.h
	 * क्रम details.
	 */
	काष्ठा अणु
		u64 pages_list[PAGELIST_ENTRIES_PER_PAGE];
		u64 next_page_data;
	पूर्ण *pages_data;

	/*
	 * Currently OP-TEE uses 4k page size and it करोes not looks
	 * like this will change in the future.  On other hand, there are
	 * no know ARM architectures with page size < 4k.
	 * Thus the next built निश्चित looks redundant. But the following
	 * code heavily relies on this assumption, so it is better be
	 * safe than sorry.
	 */
	BUILD_BUG_ON(PAGE_SIZE < OPTEE_MSG_NONCONTIG_PAGE_SIZE);

	pages_data = (व्योम *)dst;
	/*
	 * If linux page is bigger than 4k, and user buffer offset is
	 * larger than 4k/8k/12k/etc this will skip first 4k pages,
	 * because they bear no value data क्रम OP-TEE.
	 */
	optee_page = page_to_phys(*pages) +
		round_करोwn(page_offset, OPTEE_MSG_NONCONTIG_PAGE_SIZE);

	जबतक (true) अणु
		pages_data->pages_list[n++] = optee_page;

		अगर (n == PAGELIST_ENTRIES_PER_PAGE) अणु
			pages_data->next_page_data =
				virt_to_phys(pages_data + 1);
			pages_data++;
			n = 0;
		पूर्ण

		optee_page += OPTEE_MSG_NONCONTIG_PAGE_SIZE;
		अगर (!(optee_page & ~PAGE_MASK)) अणु
			अगर (!--num_pages)
				अवरोध;
			pages++;
			optee_page = page_to_phys(*pages);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * The final entry in each pagelist page is a poपूर्णांकer to the next
 * pagelist page.
 */
अटल माप_प्रकार get_pages_list_size(माप_प्रकार num_entries)
अणु
	पूर्णांक pages = DIV_ROUND_UP(num_entries, PAGELIST_ENTRIES_PER_PAGE);

	वापस pages * OPTEE_MSG_NONCONTIG_PAGE_SIZE;
पूर्ण

u64 *optee_allocate_pages_list(माप_प्रकार num_entries)
अणु
	वापस alloc_pages_exact(get_pages_list_size(num_entries), GFP_KERNEL);
पूर्ण

व्योम optee_मुक्त_pages_list(व्योम *list, माप_प्रकार num_entries)
अणु
	मुक्त_pages_exact(list, get_pages_list_size(num_entries));
पूर्ण

अटल bool is_normal_memory(pgprot_t p)
अणु
#अगर defined(CONFIG_ARM)
	वापस (((pgprot_val(p) & L_PTE_MT_MASK) == L_PTE_MT_WRITEALLOC) ||
		((pgprot_val(p) & L_PTE_MT_MASK) == L_PTE_MT_WRITEBACK));
#या_अगर defined(CONFIG_ARM64)
	वापस (pgprot_val(p) & PTE_ATTRINDX_MASK) == PTE_ATTRINDX(MT_NORMAL);
#अन्यथा
#त्रुटि "Unuspported architecture"
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __check_mem_type(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ end)
अणु
	जबतक (vma && is_normal_memory(vma->vm_page_prot)) अणु
		अगर (vma->vm_end >= end)
			वापस 0;
		vma = vma->vm_next;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक check_mem_type(अचिन्हित दीर्घ start, माप_प्रकार num_pages)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	पूर्णांक rc;

	/*
	 * Allow kernel address to रेजिस्टर with OP-TEE as kernel
	 * pages are configured as normal memory only.
	 */
	अगर (virt_addr_valid(start))
		वापस 0;

	mmap_पढ़ो_lock(mm);
	rc = __check_mem_type(find_vma(mm, start),
			      start + num_pages * PAGE_SIZE);
	mmap_पढ़ो_unlock(mm);

	वापस rc;
पूर्ण

पूर्णांक optee_shm_रेजिस्टर(काष्ठा tee_context *ctx, काष्ठा tee_shm *shm,
		       काष्ठा page **pages, माप_प्रकार num_pages,
		       अचिन्हित दीर्घ start)
अणु
	काष्ठा tee_shm *shm_arg = शून्य;
	काष्ठा optee_msg_arg *msg_arg;
	u64 *pages_list;
	phys_addr_t msg_parg;
	पूर्णांक rc;

	अगर (!num_pages)
		वापस -EINVAL;

	rc = check_mem_type(start, num_pages);
	अगर (rc)
		वापस rc;

	pages_list = optee_allocate_pages_list(num_pages);
	अगर (!pages_list)
		वापस -ENOMEM;

	shm_arg = get_msg_arg(ctx, 1, &msg_arg, &msg_parg);
	अगर (IS_ERR(shm_arg)) अणु
		rc = PTR_ERR(shm_arg);
		जाओ out;
	पूर्ण

	optee_fill_pages_list(pages_list, pages, num_pages,
			      tee_shm_get_page_offset(shm));

	msg_arg->cmd = OPTEE_MSG_CMD_REGISTER_SHM;
	msg_arg->params->attr = OPTEE_MSG_ATTR_TYPE_TMEM_OUTPUT |
				OPTEE_MSG_ATTR_NONCONTIG;
	msg_arg->params->u.पंचांगem.shm_ref = (अचिन्हित दीर्घ)shm;
	msg_arg->params->u.पंचांगem.size = tee_shm_get_size(shm);
	/*
	 * In the least bits of msg_arg->params->u.पंचांगem.buf_ptr we
	 * store buffer offset from 4k page, as described in OP-TEE ABI.
	 */
	msg_arg->params->u.पंचांगem.buf_ptr = virt_to_phys(pages_list) |
	  (tee_shm_get_page_offset(shm) & (OPTEE_MSG_NONCONTIG_PAGE_SIZE - 1));

	अगर (optee_करो_call_with_arg(ctx, msg_parg) ||
	    msg_arg->ret != TEEC_SUCCESS)
		rc = -EINVAL;

	tee_shm_मुक्त(shm_arg);
out:
	optee_मुक्त_pages_list(pages_list, num_pages);
	वापस rc;
पूर्ण

पूर्णांक optee_shm_unरेजिस्टर(काष्ठा tee_context *ctx, काष्ठा tee_shm *shm)
अणु
	काष्ठा tee_shm *shm_arg;
	काष्ठा optee_msg_arg *msg_arg;
	phys_addr_t msg_parg;
	पूर्णांक rc = 0;

	shm_arg = get_msg_arg(ctx, 1, &msg_arg, &msg_parg);
	अगर (IS_ERR(shm_arg))
		वापस PTR_ERR(shm_arg);

	msg_arg->cmd = OPTEE_MSG_CMD_UNREGISTER_SHM;

	msg_arg->params[0].attr = OPTEE_MSG_ATTR_TYPE_RMEM_INPUT;
	msg_arg->params[0].u.rmem.shm_ref = (अचिन्हित दीर्घ)shm;

	अगर (optee_करो_call_with_arg(ctx, msg_parg) ||
	    msg_arg->ret != TEEC_SUCCESS)
		rc = -EINVAL;
	tee_shm_मुक्त(shm_arg);
	वापस rc;
पूर्ण

पूर्णांक optee_shm_रेजिस्टर_supp(काष्ठा tee_context *ctx, काष्ठा tee_shm *shm,
			    काष्ठा page **pages, माप_प्रकार num_pages,
			    अचिन्हित दीर्घ start)
अणु
	/*
	 * We करोn't want to रेजिस्टर supplicant memory in OP-TEE.
	 * Instead inक्रमmation about it will be passed in RPC code.
	 */
	वापस check_mem_type(start, num_pages);
पूर्ण

पूर्णांक optee_shm_unरेजिस्टर_supp(काष्ठा tee_context *ctx, काष्ठा tee_shm *shm)
अणु
	वापस 0;
पूर्ण
