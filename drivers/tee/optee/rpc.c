<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015-2016, Linaro Limited
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/tee_drv.h>
#समावेश "optee_private.h"
#समावेश "optee_smc.h"
#समावेश "optee_rpc_cmd.h"

काष्ठा wq_entry अणु
	काष्ठा list_head link;
	काष्ठा completion c;
	u32 key;
पूर्ण;

व्योम optee_रुको_queue_init(काष्ठा optee_रुको_queue *priv)
अणु
	mutex_init(&priv->mu);
	INIT_LIST_HEAD(&priv->db);
पूर्ण

व्योम optee_रुको_queue_निकास(काष्ठा optee_रुको_queue *priv)
अणु
	mutex_destroy(&priv->mu);
पूर्ण

अटल व्योम handle_rpc_func_cmd_get_समय(काष्ठा optee_msg_arg *arg)
अणु
	काष्ठा बारpec64 ts;

	अगर (arg->num_params != 1)
		जाओ bad;
	अगर ((arg->params[0].attr & OPTEE_MSG_ATTR_TYPE_MASK) !=
			OPTEE_MSG_ATTR_TYPE_VALUE_OUTPUT)
		जाओ bad;

	kसमय_get_real_ts64(&ts);
	arg->params[0].u.value.a = ts.tv_sec;
	arg->params[0].u.value.b = ts.tv_nsec;

	arg->ret = TEEC_SUCCESS;
	वापस;
bad:
	arg->ret = TEEC_ERROR_BAD_PARAMETERS;
पूर्ण

#अगर IS_REACHABLE(CONFIG_I2C)
अटल व्योम handle_rpc_func_cmd_i2c_transfer(काष्ठा tee_context *ctx,
					     काष्ठा optee_msg_arg *arg)
अणु
	काष्ठा tee_param *params;
	काष्ठा i2c_adapter *adapter;
	काष्ठा i2c_msg msg = अणु पूर्ण;
	माप_प्रकार i;
	पूर्णांक ret = -EOPNOTSUPP;
	u8 attr[] = अणु
		TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INPUT,
		TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INPUT,
		TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT,
		TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_OUTPUT,
	पूर्ण;

	अगर (arg->num_params != ARRAY_SIZE(attr)) अणु
		arg->ret = TEEC_ERROR_BAD_PARAMETERS;
		वापस;
	पूर्ण

	params = kदो_स्मृति_array(arg->num_params, माप(काष्ठा tee_param),
			       GFP_KERNEL);
	अगर (!params) अणु
		arg->ret = TEEC_ERROR_OUT_OF_MEMORY;
		वापस;
	पूर्ण

	अगर (optee_from_msg_param(params, arg->num_params, arg->params))
		जाओ bad;

	क्रम (i = 0; i < arg->num_params; i++) अणु
		अगर (params[i].attr != attr[i])
			जाओ bad;
	पूर्ण

	adapter = i2c_get_adapter(params[0].u.value.b);
	अगर (!adapter)
		जाओ bad;

	अगर (params[1].u.value.a & OPTEE_RPC_I2C_FLAGS_TEN_BIT) अणु
		अगर (!i2c_check_functionality(adapter,
					     I2C_FUNC_10BIT_ADDR)) अणु
			i2c_put_adapter(adapter);
			जाओ bad;
		पूर्ण

		msg.flags = I2C_M_TEN;
	पूर्ण

	msg.addr = params[0].u.value.c;
	msg.buf  = params[2].u.memref.shm->kaddr;
	msg.len  = params[2].u.memref.size;

	चयन (params[0].u.value.a) अणु
	हाल OPTEE_RPC_I2C_TRANSFER_RD:
		msg.flags |= I2C_M_RD;
		अवरोध;
	हाल OPTEE_RPC_I2C_TRANSFER_WR:
		अवरोध;
	शेष:
		i2c_put_adapter(adapter);
		जाओ bad;
	पूर्ण

	ret = i2c_transfer(adapter, &msg, 1);

	अगर (ret < 0) अणु
		arg->ret = TEEC_ERROR_COMMUNICATION;
	पूर्ण अन्यथा अणु
		params[3].u.value.a = msg.len;
		अगर (optee_to_msg_param(arg->params, arg->num_params, params))
			arg->ret = TEEC_ERROR_BAD_PARAMETERS;
		अन्यथा
			arg->ret = TEEC_SUCCESS;
	पूर्ण

	i2c_put_adapter(adapter);
	kमुक्त(params);
	वापस;
bad:
	kमुक्त(params);
	arg->ret = TEEC_ERROR_BAD_PARAMETERS;
पूर्ण
#अन्यथा
अटल व्योम handle_rpc_func_cmd_i2c_transfer(काष्ठा tee_context *ctx,
					     काष्ठा optee_msg_arg *arg)
अणु
	arg->ret = TEEC_ERROR_NOT_SUPPORTED;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा wq_entry *wq_entry_get(काष्ठा optee_रुको_queue *wq, u32 key)
अणु
	काष्ठा wq_entry *w;

	mutex_lock(&wq->mu);

	list_क्रम_each_entry(w, &wq->db, link)
		अगर (w->key == key)
			जाओ out;

	w = kदो_स्मृति(माप(*w), GFP_KERNEL);
	अगर (w) अणु
		init_completion(&w->c);
		w->key = key;
		list_add_tail(&w->link, &wq->db);
	पूर्ण
out:
	mutex_unlock(&wq->mu);
	वापस w;
पूर्ण

अटल व्योम wq_sleep(काष्ठा optee_रुको_queue *wq, u32 key)
अणु
	काष्ठा wq_entry *w = wq_entry_get(wq, key);

	अगर (w) अणु
		रुको_क्रम_completion(&w->c);
		mutex_lock(&wq->mu);
		list_del(&w->link);
		mutex_unlock(&wq->mu);
		kमुक्त(w);
	पूर्ण
पूर्ण

अटल व्योम wq_wakeup(काष्ठा optee_रुको_queue *wq, u32 key)
अणु
	काष्ठा wq_entry *w = wq_entry_get(wq, key);

	अगर (w)
		complete(&w->c);
पूर्ण

अटल व्योम handle_rpc_func_cmd_wq(काष्ठा optee *optee,
				   काष्ठा optee_msg_arg *arg)
अणु
	अगर (arg->num_params != 1)
		जाओ bad;

	अगर ((arg->params[0].attr & OPTEE_MSG_ATTR_TYPE_MASK) !=
			OPTEE_MSG_ATTR_TYPE_VALUE_INPUT)
		जाओ bad;

	चयन (arg->params[0].u.value.a) अणु
	हाल OPTEE_RPC_WAIT_QUEUE_SLEEP:
		wq_sleep(&optee->रुको_queue, arg->params[0].u.value.b);
		अवरोध;
	हाल OPTEE_RPC_WAIT_QUEUE_WAKEUP:
		wq_wakeup(&optee->रुको_queue, arg->params[0].u.value.b);
		अवरोध;
	शेष:
		जाओ bad;
	पूर्ण

	arg->ret = TEEC_SUCCESS;
	वापस;
bad:
	arg->ret = TEEC_ERROR_BAD_PARAMETERS;
पूर्ण

अटल व्योम handle_rpc_func_cmd_रुको(काष्ठा optee_msg_arg *arg)
अणु
	u32 msec_to_रुको;

	अगर (arg->num_params != 1)
		जाओ bad;

	अगर ((arg->params[0].attr & OPTEE_MSG_ATTR_TYPE_MASK) !=
			OPTEE_MSG_ATTR_TYPE_VALUE_INPUT)
		जाओ bad;

	msec_to_रुको = arg->params[0].u.value.a;

	/* Go to पूर्णांकerruptible sleep */
	msleep_पूर्णांकerruptible(msec_to_रुको);

	arg->ret = TEEC_SUCCESS;
	वापस;
bad:
	arg->ret = TEEC_ERROR_BAD_PARAMETERS;
पूर्ण

अटल व्योम handle_rpc_supp_cmd(काष्ठा tee_context *ctx,
				काष्ठा optee_msg_arg *arg)
अणु
	काष्ठा tee_param *params;

	arg->ret_origin = TEEC_ORIGIN_COMMS;

	params = kदो_स्मृति_array(arg->num_params, माप(काष्ठा tee_param),
			       GFP_KERNEL);
	अगर (!params) अणु
		arg->ret = TEEC_ERROR_OUT_OF_MEMORY;
		वापस;
	पूर्ण

	अगर (optee_from_msg_param(params, arg->num_params, arg->params)) अणु
		arg->ret = TEEC_ERROR_BAD_PARAMETERS;
		जाओ out;
	पूर्ण

	arg->ret = optee_supp_thrd_req(ctx, arg->cmd, arg->num_params, params);

	अगर (optee_to_msg_param(arg->params, arg->num_params, params))
		arg->ret = TEEC_ERROR_BAD_PARAMETERS;
out:
	kमुक्त(params);
पूर्ण

अटल काष्ठा tee_shm *cmd_alloc_suppl(काष्ठा tee_context *ctx, माप_प्रकार sz)
अणु
	u32 ret;
	काष्ठा tee_param param;
	काष्ठा optee *optee = tee_get_drvdata(ctx->teedev);
	काष्ठा tee_shm *shm;

	param.attr = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT;
	param.u.value.a = OPTEE_RPC_SHM_TYPE_APPL;
	param.u.value.b = sz;
	param.u.value.c = 0;

	ret = optee_supp_thrd_req(ctx, OPTEE_RPC_CMD_SHM_ALLOC, 1, &param);
	अगर (ret)
		वापस ERR_PTR(-ENOMEM);

	mutex_lock(&optee->supp.mutex);
	/* Increases count as secure world करोesn't have a reference */
	shm = tee_shm_get_from_id(optee->supp.ctx, param.u.value.c);
	mutex_unlock(&optee->supp.mutex);
	वापस shm;
पूर्ण

अटल व्योम handle_rpc_func_cmd_shm_alloc(काष्ठा tee_context *ctx,
					  काष्ठा optee_msg_arg *arg,
					  काष्ठा optee_call_ctx *call_ctx)
अणु
	phys_addr_t pa;
	काष्ठा tee_shm *shm;
	माप_प्रकार sz;
	माप_प्रकार n;

	arg->ret_origin = TEEC_ORIGIN_COMMS;

	अगर (!arg->num_params ||
	    arg->params[0].attr != OPTEE_MSG_ATTR_TYPE_VALUE_INPUT) अणु
		arg->ret = TEEC_ERROR_BAD_PARAMETERS;
		वापस;
	पूर्ण

	क्रम (n = 1; n < arg->num_params; n++) अणु
		अगर (arg->params[n].attr != OPTEE_MSG_ATTR_TYPE_NONE) अणु
			arg->ret = TEEC_ERROR_BAD_PARAMETERS;
			वापस;
		पूर्ण
	पूर्ण

	sz = arg->params[0].u.value.b;
	चयन (arg->params[0].u.value.a) अणु
	हाल OPTEE_RPC_SHM_TYPE_APPL:
		shm = cmd_alloc_suppl(ctx, sz);
		अवरोध;
	हाल OPTEE_RPC_SHM_TYPE_KERNEL:
		shm = tee_shm_alloc(ctx, sz, TEE_SHM_MAPPED);
		अवरोध;
	शेष:
		arg->ret = TEEC_ERROR_BAD_PARAMETERS;
		वापस;
	पूर्ण

	अगर (IS_ERR(shm)) अणु
		arg->ret = TEEC_ERROR_OUT_OF_MEMORY;
		वापस;
	पूर्ण

	अगर (tee_shm_get_pa(shm, 0, &pa)) अणु
		arg->ret = TEEC_ERROR_BAD_PARAMETERS;
		जाओ bad;
	पूर्ण

	sz = tee_shm_get_size(shm);

	अगर (tee_shm_is_रेजिस्टरed(shm)) अणु
		काष्ठा page **pages;
		u64 *pages_list;
		माप_प्रकार page_num;

		pages = tee_shm_get_pages(shm, &page_num);
		अगर (!pages || !page_num) अणु
			arg->ret = TEEC_ERROR_OUT_OF_MEMORY;
			जाओ bad;
		पूर्ण

		pages_list = optee_allocate_pages_list(page_num);
		अगर (!pages_list) अणु
			arg->ret = TEEC_ERROR_OUT_OF_MEMORY;
			जाओ bad;
		पूर्ण

		call_ctx->pages_list = pages_list;
		call_ctx->num_entries = page_num;

		arg->params[0].attr = OPTEE_MSG_ATTR_TYPE_TMEM_OUTPUT |
				      OPTEE_MSG_ATTR_NONCONTIG;
		/*
		 * In the least bits of u.पंचांगem.buf_ptr we store buffer offset
		 * from 4k page, as described in OP-TEE ABI.
		 */
		arg->params[0].u.पंचांगem.buf_ptr = virt_to_phys(pages_list) |
			(tee_shm_get_page_offset(shm) &
			 (OPTEE_MSG_NONCONTIG_PAGE_SIZE - 1));
		arg->params[0].u.पंचांगem.size = tee_shm_get_size(shm);
		arg->params[0].u.पंचांगem.shm_ref = (अचिन्हित दीर्घ)shm;

		optee_fill_pages_list(pages_list, pages, page_num,
				      tee_shm_get_page_offset(shm));
	पूर्ण अन्यथा अणु
		arg->params[0].attr = OPTEE_MSG_ATTR_TYPE_TMEM_OUTPUT;
		arg->params[0].u.पंचांगem.buf_ptr = pa;
		arg->params[0].u.पंचांगem.size = sz;
		arg->params[0].u.पंचांगem.shm_ref = (अचिन्हित दीर्घ)shm;
	पूर्ण

	arg->ret = TEEC_SUCCESS;
	वापस;
bad:
	tee_shm_मुक्त(shm);
पूर्ण

अटल व्योम cmd_मुक्त_suppl(काष्ठा tee_context *ctx, काष्ठा tee_shm *shm)
अणु
	काष्ठा tee_param param;

	param.attr = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT;
	param.u.value.a = OPTEE_RPC_SHM_TYPE_APPL;
	param.u.value.b = tee_shm_get_id(shm);
	param.u.value.c = 0;

	/*
	 * Match the tee_shm_get_from_id() in cmd_alloc_suppl() as secure
	 * world has released its reference.
	 *
	 * It's better to करो this beक्रमe sending the request to supplicant
	 * as we'd like to let the process करोing the initial allocation to
	 * करो release the last reference too in order to aव्योम stacking
	 * many pending fput() on the client process. This could otherwise
	 * happen अगर secure world करोes many allocate and मुक्त in a single
	 * invoke.
	 */
	tee_shm_put(shm);

	optee_supp_thrd_req(ctx, OPTEE_RPC_CMD_SHM_FREE, 1, &param);
पूर्ण

अटल व्योम handle_rpc_func_cmd_shm_मुक्त(काष्ठा tee_context *ctx,
					 काष्ठा optee_msg_arg *arg)
अणु
	काष्ठा tee_shm *shm;

	arg->ret_origin = TEEC_ORIGIN_COMMS;

	अगर (arg->num_params != 1 ||
	    arg->params[0].attr != OPTEE_MSG_ATTR_TYPE_VALUE_INPUT) अणु
		arg->ret = TEEC_ERROR_BAD_PARAMETERS;
		वापस;
	पूर्ण

	shm = (काष्ठा tee_shm *)(अचिन्हित दीर्घ)arg->params[0].u.value.b;
	चयन (arg->params[0].u.value.a) अणु
	हाल OPTEE_RPC_SHM_TYPE_APPL:
		cmd_मुक्त_suppl(ctx, shm);
		अवरोध;
	हाल OPTEE_RPC_SHM_TYPE_KERNEL:
		tee_shm_मुक्त(shm);
		अवरोध;
	शेष:
		arg->ret = TEEC_ERROR_BAD_PARAMETERS;
	पूर्ण
	arg->ret = TEEC_SUCCESS;
पूर्ण

अटल व्योम मुक्त_pages_list(काष्ठा optee_call_ctx *call_ctx)
अणु
	अगर (call_ctx->pages_list) अणु
		optee_मुक्त_pages_list(call_ctx->pages_list,
				      call_ctx->num_entries);
		call_ctx->pages_list = शून्य;
		call_ctx->num_entries = 0;
	पूर्ण
पूर्ण

व्योम optee_rpc_finalize_call(काष्ठा optee_call_ctx *call_ctx)
अणु
	मुक्त_pages_list(call_ctx);
पूर्ण

अटल व्योम handle_rpc_func_cmd(काष्ठा tee_context *ctx, काष्ठा optee *optee,
				काष्ठा tee_shm *shm,
				काष्ठा optee_call_ctx *call_ctx)
अणु
	काष्ठा optee_msg_arg *arg;

	arg = tee_shm_get_va(shm, 0);
	अगर (IS_ERR(arg)) अणु
		pr_err("%s: tee_shm_get_va %p failed\n", __func__, shm);
		वापस;
	पूर्ण

	चयन (arg->cmd) अणु
	हाल OPTEE_RPC_CMD_GET_TIME:
		handle_rpc_func_cmd_get_समय(arg);
		अवरोध;
	हाल OPTEE_RPC_CMD_WAIT_QUEUE:
		handle_rpc_func_cmd_wq(optee, arg);
		अवरोध;
	हाल OPTEE_RPC_CMD_SUSPEND:
		handle_rpc_func_cmd_रुको(arg);
		अवरोध;
	हाल OPTEE_RPC_CMD_SHM_ALLOC:
		मुक्त_pages_list(call_ctx);
		handle_rpc_func_cmd_shm_alloc(ctx, arg, call_ctx);
		अवरोध;
	हाल OPTEE_RPC_CMD_SHM_FREE:
		handle_rpc_func_cmd_shm_मुक्त(ctx, arg);
		अवरोध;
	हाल OPTEE_RPC_CMD_I2C_TRANSFER:
		handle_rpc_func_cmd_i2c_transfer(ctx, arg);
		अवरोध;
	शेष:
		handle_rpc_supp_cmd(ctx, arg);
	पूर्ण
पूर्ण

/**
 * optee_handle_rpc() - handle RPC from secure world
 * @ctx:	context करोing the RPC
 * @param:	value of रेजिस्टरs क्रम the RPC
 * @call_ctx:	call context. Preserved during one OP-TEE invocation
 *
 * Result of RPC is written back पूर्णांकo @param.
 */
व्योम optee_handle_rpc(काष्ठा tee_context *ctx, काष्ठा optee_rpc_param *param,
		      काष्ठा optee_call_ctx *call_ctx)
अणु
	काष्ठा tee_device *teedev = ctx->teedev;
	काष्ठा optee *optee = tee_get_drvdata(teedev);
	काष्ठा tee_shm *shm;
	phys_addr_t pa;

	चयन (OPTEE_SMC_RETURN_GET_RPC_FUNC(param->a0)) अणु
	हाल OPTEE_SMC_RPC_FUNC_ALLOC:
		shm = tee_shm_alloc(ctx, param->a1, TEE_SHM_MAPPED);
		अगर (!IS_ERR(shm) && !tee_shm_get_pa(shm, 0, &pa)) अणु
			reg_pair_from_64(&param->a1, &param->a2, pa);
			reg_pair_from_64(&param->a4, &param->a5,
					 (अचिन्हित दीर्घ)shm);
		पूर्ण अन्यथा अणु
			param->a1 = 0;
			param->a2 = 0;
			param->a4 = 0;
			param->a5 = 0;
		पूर्ण
		अवरोध;
	हाल OPTEE_SMC_RPC_FUNC_FREE:
		shm = reg_pair_to_ptr(param->a1, param->a2);
		tee_shm_मुक्त(shm);
		अवरोध;
	हाल OPTEE_SMC_RPC_FUNC_FOREIGN_INTR:
		/*
		 * A क्रमeign पूर्णांकerrupt was उठाओd जबतक secure world was
		 * executing, since they are handled in Linux a dummy RPC is
		 * perक्रमmed to let Linux take the पूर्णांकerrupt through the normal
		 * vector.
		 */
		अवरोध;
	हाल OPTEE_SMC_RPC_FUNC_CMD:
		shm = reg_pair_to_ptr(param->a1, param->a2);
		handle_rpc_func_cmd(ctx, optee, shm, call_ctx);
		अवरोध;
	शेष:
		pr_warn("Unknown RPC func 0x%x\n",
			(u32)OPTEE_SMC_RETURN_GET_RPC_FUNC(param->a0));
		अवरोध;
	पूर्ण

	param->a0 = OPTEE_SMC_CALL_RETURN_FROM_RPC;
पूर्ण
