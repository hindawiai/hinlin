<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, Linaro Limited
 */
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश "optee_private.h"

काष्ठा optee_supp_req अणु
	काष्ठा list_head link;

	bool in_queue;
	u32 func;
	u32 ret;
	माप_प्रकार num_params;
	काष्ठा tee_param *param;

	काष्ठा completion c;
पूर्ण;

व्योम optee_supp_init(काष्ठा optee_supp *supp)
अणु
	स_रखो(supp, 0, माप(*supp));
	mutex_init(&supp->mutex);
	init_completion(&supp->reqs_c);
	idr_init(&supp->idr);
	INIT_LIST_HEAD(&supp->reqs);
	supp->req_id = -1;
पूर्ण

व्योम optee_supp_uninit(काष्ठा optee_supp *supp)
अणु
	mutex_destroy(&supp->mutex);
	idr_destroy(&supp->idr);
पूर्ण

व्योम optee_supp_release(काष्ठा optee_supp *supp)
अणु
	पूर्णांक id;
	काष्ठा optee_supp_req *req;
	काष्ठा optee_supp_req *req_पंचांगp;

	mutex_lock(&supp->mutex);

	/* Abort all request retrieved by supplicant */
	idr_क्रम_each_entry(&supp->idr, req, id) अणु
		idr_हटाओ(&supp->idr, id);
		req->ret = TEEC_ERROR_COMMUNICATION;
		complete(&req->c);
	पूर्ण

	/* Abort all queued requests */
	list_क्रम_each_entry_safe(req, req_पंचांगp, &supp->reqs, link) अणु
		list_del(&req->link);
		req->in_queue = false;
		req->ret = TEEC_ERROR_COMMUNICATION;
		complete(&req->c);
	पूर्ण

	supp->ctx = शून्य;
	supp->req_id = -1;

	mutex_unlock(&supp->mutex);
पूर्ण

/**
 * optee_supp_thrd_req() - request service from supplicant
 * @ctx:	context करोing the request
 * @func:	function requested
 * @num_params:	number of elements in @param array
 * @param:	parameters क्रम function
 *
 * Returns result of operation to be passed to secure world
 */
u32 optee_supp_thrd_req(काष्ठा tee_context *ctx, u32 func, माप_प्रकार num_params,
			काष्ठा tee_param *param)

अणु
	काष्ठा optee *optee = tee_get_drvdata(ctx->teedev);
	काष्ठा optee_supp *supp = &optee->supp;
	काष्ठा optee_supp_req *req;
	bool पूर्णांकerruptable;
	u32 ret;

	/*
	 * Return in हाल there is no supplicant available and
	 * non-blocking request.
	 */
	अगर (!supp->ctx && ctx->supp_noरुको)
		वापस TEEC_ERROR_COMMUNICATION;

	req = kzalloc(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस TEEC_ERROR_OUT_OF_MEMORY;

	init_completion(&req->c);
	req->func = func;
	req->num_params = num_params;
	req->param = param;

	/* Insert the request in the request list */
	mutex_lock(&supp->mutex);
	list_add_tail(&req->link, &supp->reqs);
	req->in_queue = true;
	mutex_unlock(&supp->mutex);

	/* Tell an eventual रुकोer there's a new request */
	complete(&supp->reqs_c);

	/*
	 * Wait क्रम supplicant to process and वापस result, once we've
	 * वापसed from रुको_क्रम_completion(&req->c) successfully we have
	 * exclusive access again.
	 */
	जबतक (रुको_क्रम_completion_पूर्णांकerruptible(&req->c)) अणु
		mutex_lock(&supp->mutex);
		पूर्णांकerruptable = !supp->ctx;
		अगर (पूर्णांकerruptable) अणु
			/*
			 * There's no supplicant available and since the
			 * supp->mutex currently is held none can
			 * become available until the mutex released
			 * again.
			 *
			 * Interrupting an RPC to supplicant is only
			 * allowed as a way of slightly improving the user
			 * experience in हाल the supplicant hasn't been
			 * started yet. During normal operation the supplicant
			 * will serve all requests in a समयly manner and
			 * पूर्णांकerrupting then wouldn't make sense.
			 */
			अगर (req->in_queue) अणु
				list_del(&req->link);
				req->in_queue = false;
			पूर्ण
		पूर्ण
		mutex_unlock(&supp->mutex);

		अगर (पूर्णांकerruptable) अणु
			req->ret = TEEC_ERROR_COMMUNICATION;
			अवरोध;
		पूर्ण
	पूर्ण

	ret = req->ret;
	kमुक्त(req);

	वापस ret;
पूर्ण

अटल काष्ठा optee_supp_req  *supp_pop_entry(काष्ठा optee_supp *supp,
					      पूर्णांक num_params, पूर्णांक *id)
अणु
	काष्ठा optee_supp_req *req;

	अगर (supp->req_id != -1) अणु
		/*
		 * Supplicant should not mix synchronous and asnynchronous
		 * requests.
		 */
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (list_empty(&supp->reqs))
		वापस शून्य;

	req = list_first_entry(&supp->reqs, काष्ठा optee_supp_req, link);

	अगर (num_params < req->num_params) अणु
		/* Not enough room क्रम parameters */
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	*id = idr_alloc(&supp->idr, req, 1, 0, GFP_KERNEL);
	अगर (*id < 0)
		वापस ERR_PTR(-ENOMEM);

	list_del(&req->link);
	req->in_queue = false;

	वापस req;
पूर्ण

अटल पूर्णांक supp_check_recv_params(माप_प्रकार num_params, काष्ठा tee_param *params,
				  माप_प्रकार *num_meta)
अणु
	माप_प्रकार n;

	अगर (!num_params)
		वापस -EINVAL;

	/*
	 * If there's memrefs we need to decrease those as they where
	 * increased earlier and we'll even refuse to accept any below.
	 */
	क्रम (n = 0; n < num_params; n++)
		अगर (tee_param_is_memref(params + n) && params[n].u.memref.shm)
			tee_shm_put(params[n].u.memref.shm);

	/*
	 * We only expect parameters as TEE_IOCTL_PARAM_ATTR_TYPE_NONE with
	 * or without the TEE_IOCTL_PARAM_ATTR_META bit set.
	 */
	क्रम (n = 0; n < num_params; n++)
		अगर (params[n].attr &&
		    params[n].attr != TEE_IOCTL_PARAM_ATTR_META)
			वापस -EINVAL;

	/* At most we'll need one meta parameter so no need to check क्रम more */
	अगर (params->attr == TEE_IOCTL_PARAM_ATTR_META)
		*num_meta = 1;
	अन्यथा
		*num_meta = 0;

	वापस 0;
पूर्ण

/**
 * optee_supp_recv() - receive request क्रम supplicant
 * @ctx:	context receiving the request
 * @func:	requested function in supplicant
 * @num_params:	number of elements allocated in @param, updated with number
 *		used elements
 * @param:	space क्रम parameters क्रम @func
 *
 * Returns 0 on success or <0 on failure
 */
पूर्णांक optee_supp_recv(काष्ठा tee_context *ctx, u32 *func, u32 *num_params,
		    काष्ठा tee_param *param)
अणु
	काष्ठा tee_device *teedev = ctx->teedev;
	काष्ठा optee *optee = tee_get_drvdata(teedev);
	काष्ठा optee_supp *supp = &optee->supp;
	काष्ठा optee_supp_req *req = शून्य;
	पूर्णांक id;
	माप_प्रकार num_meta;
	पूर्णांक rc;

	rc = supp_check_recv_params(*num_params, param, &num_meta);
	अगर (rc)
		वापस rc;

	जबतक (true) अणु
		mutex_lock(&supp->mutex);
		req = supp_pop_entry(supp, *num_params - num_meta, &id);
		mutex_unlock(&supp->mutex);

		अगर (req) अणु
			अगर (IS_ERR(req))
				वापस PTR_ERR(req);
			अवरोध;
		पूर्ण

		/*
		 * If we didn't get a request we'll block in
		 * रुको_क्रम_completion() to aव्योम needless spinning.
		 *
		 * This is where supplicant will be hanging most of
		 * the समय, let's make this पूर्णांकerruptable so we
		 * can easily restart supplicant अगर needed.
		 */
		अगर (रुको_क्रम_completion_पूर्णांकerruptible(&supp->reqs_c))
			वापस -ERESTARTSYS;
	पूर्ण

	अगर (num_meta) अणु
		/*
		 * tee-supplicant support meta parameters -> requsts can be
		 * processed asynchronously.
		 */
		param->attr = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT |
			      TEE_IOCTL_PARAM_ATTR_META;
		param->u.value.a = id;
		param->u.value.b = 0;
		param->u.value.c = 0;
	पूर्ण अन्यथा अणु
		mutex_lock(&supp->mutex);
		supp->req_id = id;
		mutex_unlock(&supp->mutex);
	पूर्ण

	*func = req->func;
	*num_params = req->num_params + num_meta;
	स_नकल(param + num_meta, req->param,
	       माप(काष्ठा tee_param) * req->num_params);

	वापस 0;
पूर्ण

अटल काष्ठा optee_supp_req *supp_pop_req(काष्ठा optee_supp *supp,
					   माप_प्रकार num_params,
					   काष्ठा tee_param *param,
					   माप_प्रकार *num_meta)
अणु
	काष्ठा optee_supp_req *req;
	पूर्णांक id;
	माप_प्रकार nm;
	स्थिर u32 attr = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT |
			 TEE_IOCTL_PARAM_ATTR_META;

	अगर (!num_params)
		वापस ERR_PTR(-EINVAL);

	अगर (supp->req_id == -1) अणु
		अगर (param->attr != attr)
			वापस ERR_PTR(-EINVAL);
		id = param->u.value.a;
		nm = 1;
	पूर्ण अन्यथा अणु
		id = supp->req_id;
		nm = 0;
	पूर्ण

	req = idr_find(&supp->idr, id);
	अगर (!req)
		वापस ERR_PTR(-ENOENT);

	अगर ((num_params - nm) != req->num_params)
		वापस ERR_PTR(-EINVAL);

	idr_हटाओ(&supp->idr, id);
	supp->req_id = -1;
	*num_meta = nm;

	वापस req;
पूर्ण

/**
 * optee_supp_send() - send result of request from supplicant
 * @ctx:	context sending result
 * @ret:	वापस value of request
 * @num_params:	number of parameters वापसed
 * @param:	वापसed parameters
 *
 * Returns 0 on success or <0 on failure.
 */
पूर्णांक optee_supp_send(काष्ठा tee_context *ctx, u32 ret, u32 num_params,
		    काष्ठा tee_param *param)
अणु
	काष्ठा tee_device *teedev = ctx->teedev;
	काष्ठा optee *optee = tee_get_drvdata(teedev);
	काष्ठा optee_supp *supp = &optee->supp;
	काष्ठा optee_supp_req *req;
	माप_प्रकार n;
	माप_प्रकार num_meta;

	mutex_lock(&supp->mutex);
	req = supp_pop_req(supp, num_params, param, &num_meta);
	mutex_unlock(&supp->mutex);

	अगर (IS_ERR(req)) अणु
		/* Something is wrong, let supplicant restart. */
		वापस PTR_ERR(req);
	पूर्ण

	/* Update out and in/out parameters */
	क्रम (n = 0; n < req->num_params; n++) अणु
		काष्ठा tee_param *p = req->param + n;

		चयन (p->attr & TEE_IOCTL_PARAM_ATTR_TYPE_MASK) अणु
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_OUTPUT:
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT:
			p->u.value.a = param[n + num_meta].u.value.a;
			p->u.value.b = param[n + num_meta].u.value.b;
			p->u.value.c = param[n + num_meta].u.value.c;
			अवरोध;
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_OUTPUT:
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT:
			p->u.memref.size = param[n + num_meta].u.memref.size;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	req->ret = ret;

	/* Let the requesting thपढ़ो जारी */
	complete(&req->c);

	वापस 0;
पूर्ण
