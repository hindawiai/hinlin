<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, Linaro Limited
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/arm-smccc.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/tee_drv.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/workqueue.h>
#समावेश "optee_private.h"
#समावेश "optee_smc.h"
#समावेश "shm_pool.h"

#घोषणा DRIVER_NAME "optee"

#घोषणा OPTEE_SHM_NUM_PRIV_PAGES	CONFIG_OPTEE_SHM_NUM_PRIV_PAGES

/**
 * optee_from_msg_param() - convert from OPTEE_MSG parameters to
 *			    काष्ठा tee_param
 * @params:	subप्रणाली पूर्णांकernal parameter representation
 * @num_params:	number of elements in the parameter arrays
 * @msg_params:	OPTEE_MSG parameters
 * Returns 0 on success or <0 on failure
 */
पूर्णांक optee_from_msg_param(काष्ठा tee_param *params, माप_प्रकार num_params,
			 स्थिर काष्ठा optee_msg_param *msg_params)
अणु
	पूर्णांक rc;
	माप_प्रकार n;
	काष्ठा tee_shm *shm;
	phys_addr_t pa;

	क्रम (n = 0; n < num_params; n++) अणु
		काष्ठा tee_param *p = params + n;
		स्थिर काष्ठा optee_msg_param *mp = msg_params + n;
		u32 attr = mp->attr & OPTEE_MSG_ATTR_TYPE_MASK;

		चयन (attr) अणु
		हाल OPTEE_MSG_ATTR_TYPE_NONE:
			p->attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
			स_रखो(&p->u, 0, माप(p->u));
			अवरोध;
		हाल OPTEE_MSG_ATTR_TYPE_VALUE_INPUT:
		हाल OPTEE_MSG_ATTR_TYPE_VALUE_OUTPUT:
		हाल OPTEE_MSG_ATTR_TYPE_VALUE_INOUT:
			p->attr = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INPUT +
				  attr - OPTEE_MSG_ATTR_TYPE_VALUE_INPUT;
			p->u.value.a = mp->u.value.a;
			p->u.value.b = mp->u.value.b;
			p->u.value.c = mp->u.value.c;
			अवरोध;
		हाल OPTEE_MSG_ATTR_TYPE_TMEM_INPUT:
		हाल OPTEE_MSG_ATTR_TYPE_TMEM_OUTPUT:
		हाल OPTEE_MSG_ATTR_TYPE_TMEM_INOUT:
			p->attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INPUT +
				  attr - OPTEE_MSG_ATTR_TYPE_TMEM_INPUT;
			p->u.memref.size = mp->u.पंचांगem.size;
			shm = (काष्ठा tee_shm *)(अचिन्हित दीर्घ)
				mp->u.पंचांगem.shm_ref;
			अगर (!shm) अणु
				p->u.memref.shm_offs = 0;
				p->u.memref.shm = शून्य;
				अवरोध;
			पूर्ण
			rc = tee_shm_get_pa(shm, 0, &pa);
			अगर (rc)
				वापस rc;
			p->u.memref.shm_offs = mp->u.पंचांगem.buf_ptr - pa;
			p->u.memref.shm = shm;
			अवरोध;
		हाल OPTEE_MSG_ATTR_TYPE_RMEM_INPUT:
		हाल OPTEE_MSG_ATTR_TYPE_RMEM_OUTPUT:
		हाल OPTEE_MSG_ATTR_TYPE_RMEM_INOUT:
			p->attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INPUT +
				  attr - OPTEE_MSG_ATTR_TYPE_RMEM_INPUT;
			p->u.memref.size = mp->u.rmem.size;
			shm = (काष्ठा tee_shm *)(अचिन्हित दीर्घ)
				mp->u.rmem.shm_ref;

			अगर (!shm) अणु
				p->u.memref.shm_offs = 0;
				p->u.memref.shm = शून्य;
				अवरोध;
			पूर्ण
			p->u.memref.shm_offs = mp->u.rmem.offs;
			p->u.memref.shm = shm;

			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक to_msg_param_पंचांगp_mem(काष्ठा optee_msg_param *mp,
				स्थिर काष्ठा tee_param *p)
अणु
	पूर्णांक rc;
	phys_addr_t pa;

	mp->attr = OPTEE_MSG_ATTR_TYPE_TMEM_INPUT + p->attr -
		   TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INPUT;

	mp->u.पंचांगem.shm_ref = (अचिन्हित दीर्घ)p->u.memref.shm;
	mp->u.पंचांगem.size = p->u.memref.size;

	अगर (!p->u.memref.shm) अणु
		mp->u.पंचांगem.buf_ptr = 0;
		वापस 0;
	पूर्ण

	rc = tee_shm_get_pa(p->u.memref.shm, p->u.memref.shm_offs, &pa);
	अगर (rc)
		वापस rc;

	mp->u.पंचांगem.buf_ptr = pa;
	mp->attr |= OPTEE_MSG_ATTR_CACHE_PREDEFINED <<
		    OPTEE_MSG_ATTR_CACHE_SHIFT;

	वापस 0;
पूर्ण

अटल पूर्णांक to_msg_param_reg_mem(काष्ठा optee_msg_param *mp,
				स्थिर काष्ठा tee_param *p)
अणु
	mp->attr = OPTEE_MSG_ATTR_TYPE_RMEM_INPUT + p->attr -
		   TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INPUT;

	mp->u.rmem.shm_ref = (अचिन्हित दीर्घ)p->u.memref.shm;
	mp->u.rmem.size = p->u.memref.size;
	mp->u.rmem.offs = p->u.memref.shm_offs;
	वापस 0;
पूर्ण

/**
 * optee_to_msg_param() - convert from काष्ठा tee_params to OPTEE_MSG parameters
 * @msg_params:	OPTEE_MSG parameters
 * @num_params:	number of elements in the parameter arrays
 * @params:	subप्रणाली itnernal parameter representation
 * Returns 0 on success or <0 on failure
 */
पूर्णांक optee_to_msg_param(काष्ठा optee_msg_param *msg_params, माप_प्रकार num_params,
		       स्थिर काष्ठा tee_param *params)
अणु
	पूर्णांक rc;
	माप_प्रकार n;

	क्रम (n = 0; n < num_params; n++) अणु
		स्थिर काष्ठा tee_param *p = params + n;
		काष्ठा optee_msg_param *mp = msg_params + n;

		चयन (p->attr) अणु
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_NONE:
			mp->attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
			स_रखो(&mp->u, 0, माप(mp->u));
			अवरोध;
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INPUT:
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_OUTPUT:
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT:
			mp->attr = OPTEE_MSG_ATTR_TYPE_VALUE_INPUT + p->attr -
				   TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INPUT;
			mp->u.value.a = p->u.value.a;
			mp->u.value.b = p->u.value.b;
			mp->u.value.c = p->u.value.c;
			अवरोध;
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INPUT:
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_OUTPUT:
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT:
			अगर (tee_shm_is_रेजिस्टरed(p->u.memref.shm))
				rc = to_msg_param_reg_mem(mp, p);
			अन्यथा
				rc = to_msg_param_पंचांगp_mem(mp, p);
			अगर (rc)
				वापस rc;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम optee_get_version(काष्ठा tee_device *teedev,
			      काष्ठा tee_ioctl_version_data *vers)
अणु
	काष्ठा tee_ioctl_version_data v = अणु
		.impl_id = TEE_IMPL_ID_OPTEE,
		.impl_caps = TEE_OPTEE_CAP_TZ,
		.gen_caps = TEE_GEN_CAP_GP,
	पूर्ण;
	काष्ठा optee *optee = tee_get_drvdata(teedev);

	अगर (optee->sec_caps & OPTEE_SMC_SEC_CAP_DYNAMIC_SHM)
		v.gen_caps |= TEE_GEN_CAP_REG_MEM;
	अगर (optee->sec_caps & OPTEE_SMC_SEC_CAP_MEMREF_शून्य)
		v.gen_caps |= TEE_GEN_CAP_MEMREF_शून्य;
	*vers = v;
पूर्ण

अटल व्योम optee_bus_scan(काष्ठा work_काष्ठा *work)
अणु
	WARN_ON(optee_क्रमागतerate_devices(PTA_CMD_GET_DEVICES_SUPP));
पूर्ण

अटल पूर्णांक optee_खोलो(काष्ठा tee_context *ctx)
अणु
	काष्ठा optee_context_data *ctxdata;
	काष्ठा tee_device *teedev = ctx->teedev;
	काष्ठा optee *optee = tee_get_drvdata(teedev);

	ctxdata = kzalloc(माप(*ctxdata), GFP_KERNEL);
	अगर (!ctxdata)
		वापस -ENOMEM;

	अगर (teedev == optee->supp_teedev) अणु
		bool busy = true;

		mutex_lock(&optee->supp.mutex);
		अगर (!optee->supp.ctx) अणु
			busy = false;
			optee->supp.ctx = ctx;
		पूर्ण
		mutex_unlock(&optee->supp.mutex);
		अगर (busy) अणु
			kमुक्त(ctxdata);
			वापस -EBUSY;
		पूर्ण

		अगर (!optee->scan_bus_करोne) अणु
			INIT_WORK(&optee->scan_bus_work, optee_bus_scan);
			optee->scan_bus_wq = create_workqueue("optee_bus_scan");
			अगर (!optee->scan_bus_wq) अणु
				kमुक्त(ctxdata);
				वापस -ECHILD;
			पूर्ण
			queue_work(optee->scan_bus_wq, &optee->scan_bus_work);
			optee->scan_bus_करोne = true;
		पूर्ण
	पूर्ण
	mutex_init(&ctxdata->mutex);
	INIT_LIST_HEAD(&ctxdata->sess_list);

	अगर (optee->sec_caps & OPTEE_SMC_SEC_CAP_MEMREF_शून्य)
		ctx->cap_memref_null  = true;
	अन्यथा
		ctx->cap_memref_null = false;

	ctx->data = ctxdata;
	वापस 0;
पूर्ण

अटल व्योम optee_release(काष्ठा tee_context *ctx)
अणु
	काष्ठा optee_context_data *ctxdata = ctx->data;
	काष्ठा tee_device *teedev = ctx->teedev;
	काष्ठा optee *optee = tee_get_drvdata(teedev);
	काष्ठा tee_shm *shm;
	काष्ठा optee_msg_arg *arg = शून्य;
	phys_addr_t parg;
	काष्ठा optee_session *sess;
	काष्ठा optee_session *sess_पंचांगp;

	अगर (!ctxdata)
		वापस;

	shm = tee_shm_alloc(ctx, माप(काष्ठा optee_msg_arg), TEE_SHM_MAPPED);
	अगर (!IS_ERR(shm)) अणु
		arg = tee_shm_get_va(shm, 0);
		/*
		 * If va2pa fails क्रम some reason, we can't call पूर्णांकo
		 * secure world, only मुक्त the memory. Secure OS will leak
		 * sessions and finally refuse more sessions, but we will
		 * at least let normal world reclaim its memory.
		 */
		अगर (!IS_ERR(arg))
			अगर (tee_shm_va2pa(shm, arg, &parg))
				arg = शून्य; /* prevent usage of parg below */
	पूर्ण

	list_क्रम_each_entry_safe(sess, sess_पंचांगp, &ctxdata->sess_list,
				 list_node) अणु
		list_del(&sess->list_node);
		अगर (!IS_ERR_OR_शून्य(arg)) अणु
			स_रखो(arg, 0, माप(*arg));
			arg->cmd = OPTEE_MSG_CMD_CLOSE_SESSION;
			arg->session = sess->session_id;
			optee_करो_call_with_arg(ctx, parg);
		पूर्ण
		kमुक्त(sess);
	पूर्ण
	kमुक्त(ctxdata);

	अगर (!IS_ERR(shm))
		tee_shm_मुक्त(shm);

	ctx->data = शून्य;

	अगर (teedev == optee->supp_teedev) अणु
		अगर (optee->scan_bus_wq) अणु
			destroy_workqueue(optee->scan_bus_wq);
			optee->scan_bus_wq = शून्य;
		पूर्ण
		optee_supp_release(&optee->supp);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा tee_driver_ops optee_ops = अणु
	.get_version = optee_get_version,
	.खोलो = optee_खोलो,
	.release = optee_release,
	.खोलो_session = optee_खोलो_session,
	.बंद_session = optee_बंद_session,
	.invoke_func = optee_invoke_func,
	.cancel_req = optee_cancel_req,
	.shm_रेजिस्टर = optee_shm_रेजिस्टर,
	.shm_unरेजिस्टर = optee_shm_unरेजिस्टर,
पूर्ण;

अटल स्थिर काष्ठा tee_desc optee_desc = अणु
	.name = DRIVER_NAME "-clnt",
	.ops = &optee_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा tee_driver_ops optee_supp_ops = अणु
	.get_version = optee_get_version,
	.खोलो = optee_खोलो,
	.release = optee_release,
	.supp_recv = optee_supp_recv,
	.supp_send = optee_supp_send,
	.shm_रेजिस्टर = optee_shm_रेजिस्टर_supp,
	.shm_unरेजिस्टर = optee_shm_unरेजिस्टर_supp,
पूर्ण;

अटल स्थिर काष्ठा tee_desc optee_supp_desc = अणु
	.name = DRIVER_NAME "-supp",
	.ops = &optee_supp_ops,
	.owner = THIS_MODULE,
	.flags = TEE_DESC_PRIVILEGED,
पूर्ण;

अटल bool optee_msg_api_uid_is_optee_api(optee_invoke_fn *invoke_fn)
अणु
	काष्ठा arm_smccc_res res;

	invoke_fn(OPTEE_SMC_CALLS_UID, 0, 0, 0, 0, 0, 0, 0, &res);

	अगर (res.a0 == OPTEE_MSG_UID_0 && res.a1 == OPTEE_MSG_UID_1 &&
	    res.a2 == OPTEE_MSG_UID_2 && res.a3 == OPTEE_MSG_UID_3)
		वापस true;
	वापस false;
पूर्ण

अटल व्योम optee_msg_get_os_revision(optee_invoke_fn *invoke_fn)
अणु
	जोड़ अणु
		काष्ठा arm_smccc_res smccc;
		काष्ठा optee_smc_call_get_os_revision_result result;
	पूर्ण res = अणु
		.result = अणु
			.build_id = 0
		पूर्ण
	पूर्ण;

	invoke_fn(OPTEE_SMC_CALL_GET_OS_REVISION, 0, 0, 0, 0, 0, 0, 0,
		  &res.smccc);

	अगर (res.result.build_id)
		pr_info("revision %lu.%lu (%08lx)", res.result.major,
			res.result.minor, res.result.build_id);
	अन्यथा
		pr_info("revision %lu.%lu", res.result.major, res.result.minor);
पूर्ण

अटल bool optee_msg_api_revision_is_compatible(optee_invoke_fn *invoke_fn)
अणु
	जोड़ अणु
		काष्ठा arm_smccc_res smccc;
		काष्ठा optee_smc_calls_revision_result result;
	पूर्ण res;

	invoke_fn(OPTEE_SMC_CALLS_REVISION, 0, 0, 0, 0, 0, 0, 0, &res.smccc);

	अगर (res.result.major == OPTEE_MSG_REVISION_MAJOR &&
	    (पूर्णांक)res.result.minor >= OPTEE_MSG_REVISION_MINOR)
		वापस true;
	वापस false;
पूर्ण

अटल bool optee_msg_exchange_capabilities(optee_invoke_fn *invoke_fn,
					    u32 *sec_caps)
अणु
	जोड़ अणु
		काष्ठा arm_smccc_res smccc;
		काष्ठा optee_smc_exchange_capabilities_result result;
	पूर्ण res;
	u32 a1 = 0;

	/*
	 * TODO This isn't enough to tell if it's UP प्रणाली (from kernel
	 * poपूर्णांक of view) or not, is_smp() वापसs the the inक्रमmation
	 * needed, but can't be called directly from here.
	 */
	अगर (!IS_ENABLED(CONFIG_SMP) || nr_cpu_ids == 1)
		a1 |= OPTEE_SMC_NSEC_CAP_UNIPROCESSOR;

	invoke_fn(OPTEE_SMC_EXCHANGE_CAPABILITIES, a1, 0, 0, 0, 0, 0, 0,
		  &res.smccc);

	अगर (res.result.status != OPTEE_SMC_RETURN_OK)
		वापस false;

	*sec_caps = res.result.capabilities;
	वापस true;
पूर्ण

अटल काष्ठा tee_shm_pool *optee_config_dyn_shm(व्योम)
अणु
	काष्ठा tee_shm_pool_mgr *priv_mgr;
	काष्ठा tee_shm_pool_mgr *dmabuf_mgr;
	व्योम *rc;

	rc = optee_shm_pool_alloc_pages();
	अगर (IS_ERR(rc))
		वापस rc;
	priv_mgr = rc;

	rc = optee_shm_pool_alloc_pages();
	अगर (IS_ERR(rc)) अणु
		tee_shm_pool_mgr_destroy(priv_mgr);
		वापस rc;
	पूर्ण
	dmabuf_mgr = rc;

	rc = tee_shm_pool_alloc(priv_mgr, dmabuf_mgr);
	अगर (IS_ERR(rc)) अणु
		tee_shm_pool_mgr_destroy(priv_mgr);
		tee_shm_pool_mgr_destroy(dmabuf_mgr);
	पूर्ण

	वापस rc;
पूर्ण

अटल काष्ठा tee_shm_pool *
optee_config_shm_memremap(optee_invoke_fn *invoke_fn, व्योम **memremaped_shm)
अणु
	जोड़ अणु
		काष्ठा arm_smccc_res smccc;
		काष्ठा optee_smc_get_shm_config_result result;
	पूर्ण res;
	अचिन्हित दीर्घ vaddr;
	phys_addr_t paddr;
	माप_प्रकार size;
	phys_addr_t begin;
	phys_addr_t end;
	व्योम *va;
	काष्ठा tee_shm_pool_mgr *priv_mgr;
	काष्ठा tee_shm_pool_mgr *dmabuf_mgr;
	व्योम *rc;
	स्थिर पूर्णांक sz = OPTEE_SHM_NUM_PRIV_PAGES * PAGE_SIZE;

	invoke_fn(OPTEE_SMC_GET_SHM_CONFIG, 0, 0, 0, 0, 0, 0, 0, &res.smccc);
	अगर (res.result.status != OPTEE_SMC_RETURN_OK) अणु
		pr_err("static shm service not available\n");
		वापस ERR_PTR(-ENOENT);
	पूर्ण

	अगर (res.result.settings != OPTEE_SMC_SHM_CACHED) अणु
		pr_err("only normal cached shared memory supported\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	begin = roundup(res.result.start, PAGE_SIZE);
	end = roundकरोwn(res.result.start + res.result.size, PAGE_SIZE);
	paddr = begin;
	size = end - begin;

	अगर (size < 2 * OPTEE_SHM_NUM_PRIV_PAGES * PAGE_SIZE) अणु
		pr_err("too small shared memory area\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	va = memremap(paddr, size, MEMREMAP_WB);
	अगर (!va) अणु
		pr_err("shared memory ioremap failed\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	vaddr = (अचिन्हित दीर्घ)va;

	rc = tee_shm_pool_mgr_alloc_res_mem(vaddr, paddr, sz,
					    3 /* 8 bytes aligned */);
	अगर (IS_ERR(rc))
		जाओ err_memunmap;
	priv_mgr = rc;

	vaddr += sz;
	paddr += sz;
	size -= sz;

	rc = tee_shm_pool_mgr_alloc_res_mem(vaddr, paddr, size, PAGE_SHIFT);
	अगर (IS_ERR(rc))
		जाओ err_मुक्त_priv_mgr;
	dmabuf_mgr = rc;

	rc = tee_shm_pool_alloc(priv_mgr, dmabuf_mgr);
	अगर (IS_ERR(rc))
		जाओ err_मुक्त_dmabuf_mgr;

	*memremaped_shm = va;

	वापस rc;

err_मुक्त_dmabuf_mgr:
	tee_shm_pool_mgr_destroy(dmabuf_mgr);
err_मुक्त_priv_mgr:
	tee_shm_pool_mgr_destroy(priv_mgr);
err_memunmap:
	memunmap(va);
	वापस rc;
पूर्ण

/* Simple wrapper functions to be able to use a function poपूर्णांकer */
अटल व्योम optee_smccc_smc(अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1,
			    अचिन्हित दीर्घ a2, अचिन्हित दीर्घ a3,
			    अचिन्हित दीर्घ a4, अचिन्हित दीर्घ a5,
			    अचिन्हित दीर्घ a6, अचिन्हित दीर्घ a7,
			    काष्ठा arm_smccc_res *res)
अणु
	arm_smccc_smc(a0, a1, a2, a3, a4, a5, a6, a7, res);
पूर्ण

अटल व्योम optee_smccc_hvc(अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1,
			    अचिन्हित दीर्घ a2, अचिन्हित दीर्घ a3,
			    अचिन्हित दीर्घ a4, अचिन्हित दीर्घ a5,
			    अचिन्हित दीर्घ a6, अचिन्हित दीर्घ a7,
			    काष्ठा arm_smccc_res *res)
अणु
	arm_smccc_hvc(a0, a1, a2, a3, a4, a5, a6, a7, res);
पूर्ण

अटल optee_invoke_fn *get_invoke_func(काष्ठा device *dev)
अणु
	स्थिर अक्षर *method;

	pr_info("probing for conduit method.\n");

	अगर (device_property_पढ़ो_string(dev, "method", &method)) अणु
		pr_warn("missing \"method\" property\n");
		वापस ERR_PTR(-ENXIO);
	पूर्ण

	अगर (!म_भेद("hvc", method))
		वापस optee_smccc_hvc;
	अन्यथा अगर (!म_भेद("smc", method))
		वापस optee_smccc_smc;

	pr_warn("invalid \"method\" property: %s\n", method);
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल पूर्णांक optee_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा optee *optee = platक्रमm_get_drvdata(pdev);

	/*
	 * Ask OP-TEE to मुक्त all cached shared memory objects to decrease
	 * reference counters and also aव्योम wild poपूर्णांकers in secure world
	 * पूर्णांकo the old shared memory range.
	 */
	optee_disable_shm_cache(optee);

	/*
	 * The two devices have to be unरेजिस्टरed beक्रमe we can मुक्त the
	 * other resources.
	 */
	tee_device_unरेजिस्टर(optee->supp_teedev);
	tee_device_unरेजिस्टर(optee->teedev);

	tee_shm_pool_मुक्त(optee->pool);
	अगर (optee->memremaped_shm)
		memunmap(optee->memremaped_shm);
	optee_रुको_queue_निकास(&optee->रुको_queue);
	optee_supp_uninit(&optee->supp);
	mutex_destroy(&optee->call_queue.mutex);

	kमुक्त(optee);

	वापस 0;
पूर्ण

अटल पूर्णांक optee_probe(काष्ठा platक्रमm_device *pdev)
अणु
	optee_invoke_fn *invoke_fn;
	काष्ठा tee_shm_pool *pool = ERR_PTR(-EINVAL);
	काष्ठा optee *optee = शून्य;
	व्योम *memremaped_shm = शून्य;
	काष्ठा tee_device *teedev;
	u32 sec_caps;
	पूर्णांक rc;

	invoke_fn = get_invoke_func(&pdev->dev);
	अगर (IS_ERR(invoke_fn))
		वापस PTR_ERR(invoke_fn);

	अगर (!optee_msg_api_uid_is_optee_api(invoke_fn)) अणु
		pr_warn("api uid mismatch\n");
		वापस -EINVAL;
	पूर्ण

	optee_msg_get_os_revision(invoke_fn);

	अगर (!optee_msg_api_revision_is_compatible(invoke_fn)) अणु
		pr_warn("api revision mismatch\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!optee_msg_exchange_capabilities(invoke_fn, &sec_caps)) अणु
		pr_warn("capabilities mismatch\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Try to use dynamic shared memory अगर possible
	 */
	अगर (sec_caps & OPTEE_SMC_SEC_CAP_DYNAMIC_SHM)
		pool = optee_config_dyn_shm();

	/*
	 * If dynamic shared memory is not available or failed - try अटल one
	 */
	अगर (IS_ERR(pool) && (sec_caps & OPTEE_SMC_SEC_CAP_HAVE_RESERVED_SHM))
		pool = optee_config_shm_memremap(invoke_fn, &memremaped_shm);

	अगर (IS_ERR(pool))
		वापस PTR_ERR(pool);

	optee = kzalloc(माप(*optee), GFP_KERNEL);
	अगर (!optee) अणु
		rc = -ENOMEM;
		जाओ err;
	पूर्ण

	optee->invoke_fn = invoke_fn;
	optee->sec_caps = sec_caps;

	teedev = tee_device_alloc(&optee_desc, शून्य, pool, optee);
	अगर (IS_ERR(teedev)) अणु
		rc = PTR_ERR(teedev);
		जाओ err;
	पूर्ण
	optee->teedev = teedev;

	teedev = tee_device_alloc(&optee_supp_desc, शून्य, pool, optee);
	अगर (IS_ERR(teedev)) अणु
		rc = PTR_ERR(teedev);
		जाओ err;
	पूर्ण
	optee->supp_teedev = teedev;

	rc = tee_device_रेजिस्टर(optee->teedev);
	अगर (rc)
		जाओ err;

	rc = tee_device_रेजिस्टर(optee->supp_teedev);
	अगर (rc)
		जाओ err;

	mutex_init(&optee->call_queue.mutex);
	INIT_LIST_HEAD(&optee->call_queue.रुकोers);
	optee_रुको_queue_init(&optee->रुको_queue);
	optee_supp_init(&optee->supp);
	optee->memremaped_shm = memremaped_shm;
	optee->pool = pool;

	optee_enable_shm_cache(optee);

	अगर (optee->sec_caps & OPTEE_SMC_SEC_CAP_DYNAMIC_SHM)
		pr_info("dynamic shared memory is enabled\n");

	platक्रमm_set_drvdata(pdev, optee);

	rc = optee_क्रमागतerate_devices(PTA_CMD_GET_DEVICES);
	अगर (rc) अणु
		optee_हटाओ(pdev);
		वापस rc;
	पूर्ण

	pr_info("initialized driver\n");
	वापस 0;
err:
	अगर (optee) अणु
		/*
		 * tee_device_unरेजिस्टर() is safe to call even अगर the
		 * devices hasn't been रेजिस्टरed with
		 * tee_device_रेजिस्टर() yet.
		 */
		tee_device_unरेजिस्टर(optee->supp_teedev);
		tee_device_unरेजिस्टर(optee->teedev);
		kमुक्त(optee);
	पूर्ण
	अगर (pool)
		tee_shm_pool_मुक्त(pool);
	अगर (memremaped_shm)
		memunmap(memremaped_shm);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा of_device_id optee_dt_match[] = अणु
	अणु .compatible = "linaro,optee-tz" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, optee_dt_match);

अटल काष्ठा platक्रमm_driver optee_driver = अणु
	.probe  = optee_probe,
	.हटाओ = optee_हटाओ,
	.driver = अणु
		.name = "optee",
		.of_match_table = optee_dt_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(optee_driver);

MODULE_AUTHOR("Linaro");
MODULE_DESCRIPTION("OP-TEE driver");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:optee");
