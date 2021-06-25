<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015-2016, Linaro Limited
 */

#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

#समावेश <linux/cdev.h>
#समावेश <linux/cred.h>
#समावेश <linux/fs.h>
#समावेश <linux/idr.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/tee_drv.h>
#समावेश <linux/uaccess.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/sha1.h>
#समावेश "tee_private.h"

#घोषणा TEE_NUM_DEVICES	32

#घोषणा TEE_IOCTL_PARAM_SIZE(x) (माप(काष्ठा tee_param) * (x))

#घोषणा TEE_UUID_NS_NAME_SIZE	128

/*
 * TEE Client UUID name space identअगरier (UUIDv4)
 *
 * Value here is अक्रमom UUID that is allocated as name space identअगरier क्रम
 * क्रमming Client UUID's क्रम TEE environment using UUIDv5 scheme.
 */
अटल स्थिर uuid_t tee_client_uuid_ns = UUID_INIT(0x58ac9ca0, 0x2086, 0x4683,
						   0xa1, 0xb8, 0xec, 0x4b,
						   0xc0, 0x8e, 0x01, 0xb6);

/*
 * Unprivileged devices in the lower half range and privileged devices in
 * the upper half range.
 */
अटल DECLARE_BITMAP(dev_mask, TEE_NUM_DEVICES);
अटल DEFINE_SPINLOCK(driver_lock);

अटल काष्ठा class *tee_class;
अटल dev_t tee_devt;

अटल काष्ठा tee_context *teedev_खोलो(काष्ठा tee_device *teedev)
अणु
	पूर्णांक rc;
	काष्ठा tee_context *ctx;

	अगर (!tee_device_get(teedev))
		वापस ERR_PTR(-EINVAL);

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx) अणु
		rc = -ENOMEM;
		जाओ err;
	पूर्ण

	kref_init(&ctx->refcount);
	ctx->teedev = teedev;
	rc = teedev->desc->ops->खोलो(ctx);
	अगर (rc)
		जाओ err;

	वापस ctx;
err:
	kमुक्त(ctx);
	tee_device_put(teedev);
	वापस ERR_PTR(rc);

पूर्ण

व्योम teedev_ctx_get(काष्ठा tee_context *ctx)
अणु
	अगर (ctx->releasing)
		वापस;

	kref_get(&ctx->refcount);
पूर्ण

अटल व्योम teedev_ctx_release(काष्ठा kref *ref)
अणु
	काष्ठा tee_context *ctx = container_of(ref, काष्ठा tee_context,
					       refcount);
	ctx->releasing = true;
	ctx->teedev->desc->ops->release(ctx);
	kमुक्त(ctx);
पूर्ण

व्योम teedev_ctx_put(काष्ठा tee_context *ctx)
अणु
	अगर (ctx->releasing)
		वापस;

	kref_put(&ctx->refcount, teedev_ctx_release);
पूर्ण

अटल व्योम teedev_बंद_context(काष्ठा tee_context *ctx)
अणु
	tee_device_put(ctx->teedev);
	teedev_ctx_put(ctx);
पूर्ण

अटल पूर्णांक tee_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा tee_context *ctx;

	ctx = teedev_खोलो(container_of(inode->i_cdev, काष्ठा tee_device, cdev));
	अगर (IS_ERR(ctx))
		वापस PTR_ERR(ctx);

	/*
	 * Default user-space behaviour is to रुको क्रम tee-supplicant
	 * अगर not present क्रम any requests in this context.
	 */
	ctx->supp_noरुको = false;
	filp->निजी_data = ctx;
	वापस 0;
पूर्ण

अटल पूर्णांक tee_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	teedev_बंद_context(filp->निजी_data);
	वापस 0;
पूर्ण

/**
 * uuid_v5() - Calculate UUIDv5
 * @uuid: Resulting UUID
 * @ns: Name space ID क्रम UUIDv5 function
 * @name: Name क्रम UUIDv5 function
 * @size: Size of name
 *
 * UUIDv5 is specअगरic in RFC 4122.
 *
 * This implements section (क्रम SHA-1):
 * 4.3.  Algorithm क्रम Creating a Name-Based UUID
 */
अटल पूर्णांक uuid_v5(uuid_t *uuid, स्थिर uuid_t *ns, स्थिर व्योम *name,
		   माप_प्रकार size)
अणु
	अचिन्हित अक्षर hash[SHA1_DIGEST_SIZE];
	काष्ठा crypto_shash *shash = शून्य;
	काष्ठा shash_desc *desc = शून्य;
	पूर्णांक rc;

	shash = crypto_alloc_shash("sha1", 0, 0);
	अगर (IS_ERR(shash)) अणु
		rc = PTR_ERR(shash);
		pr_err("shash(sha1) allocation failed\n");
		वापस rc;
	पूर्ण

	desc = kzalloc(माप(*desc) + crypto_shash_descsize(shash),
		       GFP_KERNEL);
	अगर (!desc) अणु
		rc = -ENOMEM;
		जाओ out_मुक्त_shash;
	पूर्ण

	desc->tfm = shash;

	rc = crypto_shash_init(desc);
	अगर (rc < 0)
		जाओ out_मुक्त_desc;

	rc = crypto_shash_update(desc, (स्थिर u8 *)ns, माप(*ns));
	अगर (rc < 0)
		जाओ out_मुक्त_desc;

	rc = crypto_shash_update(desc, (स्थिर u8 *)name, size);
	अगर (rc < 0)
		जाओ out_मुक्त_desc;

	rc = crypto_shash_final(desc, hash);
	अगर (rc < 0)
		जाओ out_मुक्त_desc;

	स_नकल(uuid->b, hash, UUID_SIZE);

	/* Tag क्रम version 5 */
	uuid->b[6] = (hash[6] & 0x0F) | 0x50;
	uuid->b[8] = (hash[8] & 0x3F) | 0x80;

out_मुक्त_desc:
	kमुक्त(desc);

out_मुक्त_shash:
	crypto_मुक्त_shash(shash);
	वापस rc;
पूर्ण

पूर्णांक tee_session_calc_client_uuid(uuid_t *uuid, u32 connection_method,
				 स्थिर u8 connection_data[TEE_IOCTL_UUID_LEN])
अणु
	gid_t ns_grp = (gid_t)-1;
	kgid_t grp = INVALID_GID;
	अक्षर *name = शून्य;
	पूर्णांक name_len;
	पूर्णांक rc;

	अगर (connection_method == TEE_IOCTL_LOGIN_PUBLIC ||
	    connection_method == TEE_IOCTL_LOGIN_REE_KERNEL) अणु
		/* Nil UUID to be passed to TEE environment */
		uuid_copy(uuid, &uuid_null);
		वापस 0;
	पूर्ण

	/*
	 * In Linux environment client UUID is based on UUIDv5.
	 *
	 * Determine client UUID with following semantics क्रम 'name':
	 *
	 * For TEEC_LOGIN_USER:
	 * uid=<uid>
	 *
	 * For TEEC_LOGIN_GROUP:
	 * gid=<gid>
	 *
	 */

	name = kzalloc(TEE_UUID_NS_NAME_SIZE, GFP_KERNEL);
	अगर (!name)
		वापस -ENOMEM;

	चयन (connection_method) अणु
	हाल TEE_IOCTL_LOGIN_USER:
		name_len = snम_लिखो(name, TEE_UUID_NS_NAME_SIZE, "uid=%x",
				    current_euid().val);
		अगर (name_len >= TEE_UUID_NS_NAME_SIZE) अणु
			rc = -E2BIG;
			जाओ out_मुक्त_name;
		पूर्ण
		अवरोध;

	हाल TEE_IOCTL_LOGIN_GROUP:
		स_नकल(&ns_grp, connection_data, माप(gid_t));
		grp = make_kgid(current_user_ns(), ns_grp);
		अगर (!gid_valid(grp) || !in_egroup_p(grp)) अणु
			rc = -EPERM;
			जाओ out_मुक्त_name;
		पूर्ण

		name_len = snम_लिखो(name, TEE_UUID_NS_NAME_SIZE, "gid=%x",
				    grp.val);
		अगर (name_len >= TEE_UUID_NS_NAME_SIZE) अणु
			rc = -E2BIG;
			जाओ out_मुक्त_name;
		पूर्ण
		अवरोध;

	शेष:
		rc = -EINVAL;
		जाओ out_मुक्त_name;
	पूर्ण

	rc = uuid_v5(uuid, &tee_client_uuid_ns, name, name_len);
out_मुक्त_name:
	kमुक्त(name);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(tee_session_calc_client_uuid);

अटल पूर्णांक tee_ioctl_version(काष्ठा tee_context *ctx,
			     काष्ठा tee_ioctl_version_data __user *uvers)
अणु
	काष्ठा tee_ioctl_version_data vers;

	ctx->teedev->desc->ops->get_version(ctx->teedev, &vers);

	अगर (ctx->teedev->desc->flags & TEE_DESC_PRIVILEGED)
		vers.gen_caps |= TEE_GEN_CAP_PRIVILEGED;

	अगर (copy_to_user(uvers, &vers, माप(vers)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक tee_ioctl_shm_alloc(काष्ठा tee_context *ctx,
			       काष्ठा tee_ioctl_shm_alloc_data __user *udata)
अणु
	दीर्घ ret;
	काष्ठा tee_ioctl_shm_alloc_data data;
	काष्ठा tee_shm *shm;

	अगर (copy_from_user(&data, udata, माप(data)))
		वापस -EFAULT;

	/* Currently no input flags are supported */
	अगर (data.flags)
		वापस -EINVAL;

	shm = tee_shm_alloc(ctx, data.size, TEE_SHM_MAPPED | TEE_SHM_DMA_BUF);
	अगर (IS_ERR(shm))
		वापस PTR_ERR(shm);

	data.id = shm->id;
	data.flags = shm->flags;
	data.size = shm->size;

	अगर (copy_to_user(udata, &data, माप(data)))
		ret = -EFAULT;
	अन्यथा
		ret = tee_shm_get_fd(shm);

	/*
	 * When user space बंदs the file descriptor the shared memory
	 * should be मुक्तd or अगर tee_shm_get_fd() failed then it will
	 * be मुक्तd immediately.
	 */
	tee_shm_put(shm);
	वापस ret;
पूर्ण

अटल पूर्णांक
tee_ioctl_shm_रेजिस्टर(काष्ठा tee_context *ctx,
		       काष्ठा tee_ioctl_shm_रेजिस्टर_data __user *udata)
अणु
	दीर्घ ret;
	काष्ठा tee_ioctl_shm_रेजिस्टर_data data;
	काष्ठा tee_shm *shm;

	अगर (copy_from_user(&data, udata, माप(data)))
		वापस -EFAULT;

	/* Currently no input flags are supported */
	अगर (data.flags)
		वापस -EINVAL;

	shm = tee_shm_रेजिस्टर(ctx, data.addr, data.length,
			       TEE_SHM_DMA_BUF | TEE_SHM_USER_MAPPED);
	अगर (IS_ERR(shm))
		वापस PTR_ERR(shm);

	data.id = shm->id;
	data.flags = shm->flags;
	data.length = shm->size;

	अगर (copy_to_user(udata, &data, माप(data)))
		ret = -EFAULT;
	अन्यथा
		ret = tee_shm_get_fd(shm);
	/*
	 * When user space बंदs the file descriptor the shared memory
	 * should be मुक्तd or अगर tee_shm_get_fd() failed then it will
	 * be मुक्तd immediately.
	 */
	tee_shm_put(shm);
	वापस ret;
पूर्ण

अटल पूर्णांक params_from_user(काष्ठा tee_context *ctx, काष्ठा tee_param *params,
			    माप_प्रकार num_params,
			    काष्ठा tee_ioctl_param __user *uparams)
अणु
	माप_प्रकार n;

	क्रम (n = 0; n < num_params; n++) अणु
		काष्ठा tee_shm *shm;
		काष्ठा tee_ioctl_param ip;

		अगर (copy_from_user(&ip, uparams + n, माप(ip)))
			वापस -EFAULT;

		/* All unused attribute bits has to be zero */
		अगर (ip.attr & ~TEE_IOCTL_PARAM_ATTR_MASK)
			वापस -EINVAL;

		params[n].attr = ip.attr;
		चयन (ip.attr & TEE_IOCTL_PARAM_ATTR_TYPE_MASK) अणु
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_NONE:
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_OUTPUT:
			अवरोध;
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INPUT:
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT:
			params[n].u.value.a = ip.a;
			params[n].u.value.b = ip.b;
			params[n].u.value.c = ip.c;
			अवरोध;
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INPUT:
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_OUTPUT:
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT:
			/*
			 * If a शून्य poपूर्णांकer is passed to a TA in the TEE,
			 * the ip.c IOCTL parameters is set to TEE_MEMREF_शून्य
			 * indicating a शून्य memory reference.
			 */
			अगर (ip.c != TEE_MEMREF_शून्य) अणु
				/*
				 * If we fail to get a poपूर्णांकer to a shared
				 * memory object (and increase the ref count)
				 * from an identअगरier we वापस an error. All
				 * poपूर्णांकers that has been added in params have
				 * an increased ref count. It's the callers
				 * responibility to करो tee_shm_put() on all
				 * resolved poपूर्णांकers.
				 */
				shm = tee_shm_get_from_id(ctx, ip.c);
				अगर (IS_ERR(shm))
					वापस PTR_ERR(shm);

				/*
				 * Ensure offset + size करोes not overflow
				 * offset and करोes not overflow the size of
				 * the referred shared memory object.
				 */
				अगर ((ip.a + ip.b) < ip.a ||
				    (ip.a + ip.b) > shm->size) अणु
					tee_shm_put(shm);
					वापस -EINVAL;
				पूर्ण
			पूर्ण अन्यथा अगर (ctx->cap_memref_null) अणु
				/* Pass शून्य poपूर्णांकer to OP-TEE */
				shm = शून्य;
			पूर्ण अन्यथा अणु
				वापस -EINVAL;
			पूर्ण

			params[n].u.memref.shm_offs = ip.a;
			params[n].u.memref.size = ip.b;
			params[n].u.memref.shm = shm;
			अवरोध;
		शेष:
			/* Unknown attribute */
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक params_to_user(काष्ठा tee_ioctl_param __user *uparams,
			  माप_प्रकार num_params, काष्ठा tee_param *params)
अणु
	माप_प्रकार n;

	क्रम (n = 0; n < num_params; n++) अणु
		काष्ठा tee_ioctl_param __user *up = uparams + n;
		काष्ठा tee_param *p = params + n;

		चयन (p->attr) अणु
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_OUTPUT:
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT:
			अगर (put_user(p->u.value.a, &up->a) ||
			    put_user(p->u.value.b, &up->b) ||
			    put_user(p->u.value.c, &up->c))
				वापस -EFAULT;
			अवरोध;
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_OUTPUT:
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT:
			अगर (put_user((u64)p->u.memref.size, &up->b))
				वापस -EFAULT;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tee_ioctl_खोलो_session(काष्ठा tee_context *ctx,
				  काष्ठा tee_ioctl_buf_data __user *ubuf)
अणु
	पूर्णांक rc;
	माप_प्रकार n;
	काष्ठा tee_ioctl_buf_data buf;
	काष्ठा tee_ioctl_खोलो_session_arg __user *uarg;
	काष्ठा tee_ioctl_खोलो_session_arg arg;
	काष्ठा tee_ioctl_param __user *uparams = शून्य;
	काष्ठा tee_param *params = शून्य;
	bool have_session = false;

	अगर (!ctx->teedev->desc->ops->खोलो_session)
		वापस -EINVAL;

	अगर (copy_from_user(&buf, ubuf, माप(buf)))
		वापस -EFAULT;

	अगर (buf.buf_len > TEE_MAX_ARG_SIZE ||
	    buf.buf_len < माप(काष्ठा tee_ioctl_खोलो_session_arg))
		वापस -EINVAL;

	uarg = u64_to_user_ptr(buf.buf_ptr);
	अगर (copy_from_user(&arg, uarg, माप(arg)))
		वापस -EFAULT;

	अगर (माप(arg) + TEE_IOCTL_PARAM_SIZE(arg.num_params) != buf.buf_len)
		वापस -EINVAL;

	अगर (arg.num_params) अणु
		params = kसुस्मृति(arg.num_params, माप(काष्ठा tee_param),
				 GFP_KERNEL);
		अगर (!params)
			वापस -ENOMEM;
		uparams = uarg->params;
		rc = params_from_user(ctx, params, arg.num_params, uparams);
		अगर (rc)
			जाओ out;
	पूर्ण

	अगर (arg.clnt_login >= TEE_IOCTL_LOGIN_REE_KERNEL_MIN &&
	    arg.clnt_login <= TEE_IOCTL_LOGIN_REE_KERNEL_MAX) अणु
		pr_debug("login method not allowed for user-space client\n");
		rc = -EPERM;
		जाओ out;
	पूर्ण

	rc = ctx->teedev->desc->ops->खोलो_session(ctx, &arg, params);
	अगर (rc)
		जाओ out;
	have_session = true;

	अगर (put_user(arg.session, &uarg->session) ||
	    put_user(arg.ret, &uarg->ret) ||
	    put_user(arg.ret_origin, &uarg->ret_origin)) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण
	rc = params_to_user(uparams, arg.num_params, params);
out:
	/*
	 * If we've succeeded to खोलो the session but failed to communicate
	 * it back to user space, बंद the session again to aव्योम leakage.
	 */
	अगर (rc && have_session && ctx->teedev->desc->ops->बंद_session)
		ctx->teedev->desc->ops->बंद_session(ctx, arg.session);

	अगर (params) अणु
		/* Decrease ref count क्रम all valid shared memory poपूर्णांकers */
		क्रम (n = 0; n < arg.num_params; n++)
			अगर (tee_param_is_memref(params + n) &&
			    params[n].u.memref.shm)
				tee_shm_put(params[n].u.memref.shm);
		kमुक्त(params);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक tee_ioctl_invoke(काष्ठा tee_context *ctx,
			    काष्ठा tee_ioctl_buf_data __user *ubuf)
अणु
	पूर्णांक rc;
	माप_प्रकार n;
	काष्ठा tee_ioctl_buf_data buf;
	काष्ठा tee_ioctl_invoke_arg __user *uarg;
	काष्ठा tee_ioctl_invoke_arg arg;
	काष्ठा tee_ioctl_param __user *uparams = शून्य;
	काष्ठा tee_param *params = शून्य;

	अगर (!ctx->teedev->desc->ops->invoke_func)
		वापस -EINVAL;

	अगर (copy_from_user(&buf, ubuf, माप(buf)))
		वापस -EFAULT;

	अगर (buf.buf_len > TEE_MAX_ARG_SIZE ||
	    buf.buf_len < माप(काष्ठा tee_ioctl_invoke_arg))
		वापस -EINVAL;

	uarg = u64_to_user_ptr(buf.buf_ptr);
	अगर (copy_from_user(&arg, uarg, माप(arg)))
		वापस -EFAULT;

	अगर (माप(arg) + TEE_IOCTL_PARAM_SIZE(arg.num_params) != buf.buf_len)
		वापस -EINVAL;

	अगर (arg.num_params) अणु
		params = kसुस्मृति(arg.num_params, माप(काष्ठा tee_param),
				 GFP_KERNEL);
		अगर (!params)
			वापस -ENOMEM;
		uparams = uarg->params;
		rc = params_from_user(ctx, params, arg.num_params, uparams);
		अगर (rc)
			जाओ out;
	पूर्ण

	rc = ctx->teedev->desc->ops->invoke_func(ctx, &arg, params);
	अगर (rc)
		जाओ out;

	अगर (put_user(arg.ret, &uarg->ret) ||
	    put_user(arg.ret_origin, &uarg->ret_origin)) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण
	rc = params_to_user(uparams, arg.num_params, params);
out:
	अगर (params) अणु
		/* Decrease ref count क्रम all valid shared memory poपूर्णांकers */
		क्रम (n = 0; n < arg.num_params; n++)
			अगर (tee_param_is_memref(params + n) &&
			    params[n].u.memref.shm)
				tee_shm_put(params[n].u.memref.shm);
		kमुक्त(params);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक tee_ioctl_cancel(काष्ठा tee_context *ctx,
			    काष्ठा tee_ioctl_cancel_arg __user *uarg)
अणु
	काष्ठा tee_ioctl_cancel_arg arg;

	अगर (!ctx->teedev->desc->ops->cancel_req)
		वापस -EINVAL;

	अगर (copy_from_user(&arg, uarg, माप(arg)))
		वापस -EFAULT;

	वापस ctx->teedev->desc->ops->cancel_req(ctx, arg.cancel_id,
						  arg.session);
पूर्ण

अटल पूर्णांक
tee_ioctl_बंद_session(काष्ठा tee_context *ctx,
			काष्ठा tee_ioctl_बंद_session_arg __user *uarg)
अणु
	काष्ठा tee_ioctl_बंद_session_arg arg;

	अगर (!ctx->teedev->desc->ops->बंद_session)
		वापस -EINVAL;

	अगर (copy_from_user(&arg, uarg, माप(arg)))
		वापस -EFAULT;

	वापस ctx->teedev->desc->ops->बंद_session(ctx, arg.session);
पूर्ण

अटल पूर्णांक params_to_supp(काष्ठा tee_context *ctx,
			  काष्ठा tee_ioctl_param __user *uparams,
			  माप_प्रकार num_params, काष्ठा tee_param *params)
अणु
	माप_प्रकार n;

	क्रम (n = 0; n < num_params; n++) अणु
		काष्ठा tee_ioctl_param ip;
		काष्ठा tee_param *p = params + n;

		ip.attr = p->attr;
		चयन (p->attr & TEE_IOCTL_PARAM_ATTR_TYPE_MASK) अणु
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INPUT:
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT:
			ip.a = p->u.value.a;
			ip.b = p->u.value.b;
			ip.c = p->u.value.c;
			अवरोध;
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INPUT:
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_OUTPUT:
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT:
			ip.b = p->u.memref.size;
			अगर (!p->u.memref.shm) अणु
				ip.a = 0;
				ip.c = (u64)-1; /* invalid shm id */
				अवरोध;
			पूर्ण
			ip.a = p->u.memref.shm_offs;
			ip.c = p->u.memref.shm->id;
			अवरोध;
		शेष:
			ip.a = 0;
			ip.b = 0;
			ip.c = 0;
			अवरोध;
		पूर्ण

		अगर (copy_to_user(uparams + n, &ip, माप(ip)))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tee_ioctl_supp_recv(काष्ठा tee_context *ctx,
			       काष्ठा tee_ioctl_buf_data __user *ubuf)
अणु
	पूर्णांक rc;
	काष्ठा tee_ioctl_buf_data buf;
	काष्ठा tee_iocl_supp_recv_arg __user *uarg;
	काष्ठा tee_param *params;
	u32 num_params;
	u32 func;

	अगर (!ctx->teedev->desc->ops->supp_recv)
		वापस -EINVAL;

	अगर (copy_from_user(&buf, ubuf, माप(buf)))
		वापस -EFAULT;

	अगर (buf.buf_len > TEE_MAX_ARG_SIZE ||
	    buf.buf_len < माप(काष्ठा tee_iocl_supp_recv_arg))
		वापस -EINVAL;

	uarg = u64_to_user_ptr(buf.buf_ptr);
	अगर (get_user(num_params, &uarg->num_params))
		वापस -EFAULT;

	अगर (माप(*uarg) + TEE_IOCTL_PARAM_SIZE(num_params) != buf.buf_len)
		वापस -EINVAL;

	params = kसुस्मृति(num_params, माप(काष्ठा tee_param), GFP_KERNEL);
	अगर (!params)
		वापस -ENOMEM;

	rc = params_from_user(ctx, params, num_params, uarg->params);
	अगर (rc)
		जाओ out;

	rc = ctx->teedev->desc->ops->supp_recv(ctx, &func, &num_params, params);
	अगर (rc)
		जाओ out;

	अगर (put_user(func, &uarg->func) ||
	    put_user(num_params, &uarg->num_params)) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	rc = params_to_supp(ctx, uarg->params, num_params, params);
out:
	kमुक्त(params);
	वापस rc;
पूर्ण

अटल पूर्णांक params_from_supp(काष्ठा tee_param *params, माप_प्रकार num_params,
			    काष्ठा tee_ioctl_param __user *uparams)
अणु
	माप_प्रकार n;

	क्रम (n = 0; n < num_params; n++) अणु
		काष्ठा tee_param *p = params + n;
		काष्ठा tee_ioctl_param ip;

		अगर (copy_from_user(&ip, uparams + n, माप(ip)))
			वापस -EFAULT;

		/* All unused attribute bits has to be zero */
		अगर (ip.attr & ~TEE_IOCTL_PARAM_ATTR_MASK)
			वापस -EINVAL;

		p->attr = ip.attr;
		चयन (ip.attr & TEE_IOCTL_PARAM_ATTR_TYPE_MASK) अणु
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_OUTPUT:
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT:
			/* Only out and in/out values can be updated */
			p->u.value.a = ip.a;
			p->u.value.b = ip.b;
			p->u.value.c = ip.c;
			अवरोध;
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_OUTPUT:
		हाल TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT:
			/*
			 * Only the size of the memref can be updated.
			 * Since we करोn't have access to the original
			 * parameters here, only store the supplied size.
			 * The driver will copy the updated size पूर्णांकo the
			 * original parameters.
			 */
			p->u.memref.shm = शून्य;
			p->u.memref.shm_offs = 0;
			p->u.memref.size = ip.b;
			अवरोध;
		शेष:
			स_रखो(&p->u, 0, माप(p->u));
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tee_ioctl_supp_send(काष्ठा tee_context *ctx,
			       काष्ठा tee_ioctl_buf_data __user *ubuf)
अणु
	दीर्घ rc;
	काष्ठा tee_ioctl_buf_data buf;
	काष्ठा tee_iocl_supp_send_arg __user *uarg;
	काष्ठा tee_param *params;
	u32 num_params;
	u32 ret;

	/* Not valid क्रम this driver */
	अगर (!ctx->teedev->desc->ops->supp_send)
		वापस -EINVAL;

	अगर (copy_from_user(&buf, ubuf, माप(buf)))
		वापस -EFAULT;

	अगर (buf.buf_len > TEE_MAX_ARG_SIZE ||
	    buf.buf_len < माप(काष्ठा tee_iocl_supp_send_arg))
		वापस -EINVAL;

	uarg = u64_to_user_ptr(buf.buf_ptr);
	अगर (get_user(ret, &uarg->ret) ||
	    get_user(num_params, &uarg->num_params))
		वापस -EFAULT;

	अगर (माप(*uarg) + TEE_IOCTL_PARAM_SIZE(num_params) > buf.buf_len)
		वापस -EINVAL;

	params = kसुस्मृति(num_params, माप(काष्ठा tee_param), GFP_KERNEL);
	अगर (!params)
		वापस -ENOMEM;

	rc = params_from_supp(params, num_params, uarg->params);
	अगर (rc)
		जाओ out;

	rc = ctx->teedev->desc->ops->supp_send(ctx, ret, num_params, params);
out:
	kमुक्त(params);
	वापस rc;
पूर्ण

अटल दीर्घ tee_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा tee_context *ctx = filp->निजी_data;
	व्योम __user *uarg = (व्योम __user *)arg;

	चयन (cmd) अणु
	हाल TEE_IOC_VERSION:
		वापस tee_ioctl_version(ctx, uarg);
	हाल TEE_IOC_SHM_ALLOC:
		वापस tee_ioctl_shm_alloc(ctx, uarg);
	हाल TEE_IOC_SHM_REGISTER:
		वापस tee_ioctl_shm_रेजिस्टर(ctx, uarg);
	हाल TEE_IOC_OPEN_SESSION:
		वापस tee_ioctl_खोलो_session(ctx, uarg);
	हाल TEE_IOC_INVOKE:
		वापस tee_ioctl_invoke(ctx, uarg);
	हाल TEE_IOC_CANCEL:
		वापस tee_ioctl_cancel(ctx, uarg);
	हाल TEE_IOC_CLOSE_SESSION:
		वापस tee_ioctl_बंद_session(ctx, uarg);
	हाल TEE_IOC_SUPPL_RECV:
		वापस tee_ioctl_supp_recv(ctx, uarg);
	हाल TEE_IOC_SUPPL_SEND:
		वापस tee_ioctl_supp_send(ctx, uarg);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा file_operations tee_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = tee_खोलो,
	.release = tee_release,
	.unlocked_ioctl = tee_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
पूर्ण;

अटल व्योम tee_release_device(काष्ठा device *dev)
अणु
	काष्ठा tee_device *teedev = container_of(dev, काष्ठा tee_device, dev);

	spin_lock(&driver_lock);
	clear_bit(teedev->id, dev_mask);
	spin_unlock(&driver_lock);
	mutex_destroy(&teedev->mutex);
	idr_destroy(&teedev->idr);
	kमुक्त(teedev);
पूर्ण

/**
 * tee_device_alloc() - Allocate a new काष्ठा tee_device instance
 * @teedesc:	Descriptor क्रम this driver
 * @dev:	Parent device क्रम this device
 * @pool:	Shared memory pool, शून्य अगर not used
 * @driver_data: Private driver data क्रम this device
 *
 * Allocates a new काष्ठा tee_device instance. The device is
 * हटाओd by tee_device_unरेजिस्टर().
 *
 * @वापसs a poपूर्णांकer to a 'struct tee_device' or an ERR_PTR on failure
 */
काष्ठा tee_device *tee_device_alloc(स्थिर काष्ठा tee_desc *teedesc,
				    काष्ठा device *dev,
				    काष्ठा tee_shm_pool *pool,
				    व्योम *driver_data)
अणु
	काष्ठा tee_device *teedev;
	व्योम *ret;
	पूर्णांक rc, max_id;
	पूर्णांक offs = 0;

	अगर (!teedesc || !teedesc->name || !teedesc->ops ||
	    !teedesc->ops->get_version || !teedesc->ops->खोलो ||
	    !teedesc->ops->release || !pool)
		वापस ERR_PTR(-EINVAL);

	teedev = kzalloc(माप(*teedev), GFP_KERNEL);
	अगर (!teedev) अणु
		ret = ERR_PTR(-ENOMEM);
		जाओ err;
	पूर्ण

	max_id = TEE_NUM_DEVICES / 2;

	अगर (teedesc->flags & TEE_DESC_PRIVILEGED) अणु
		offs = TEE_NUM_DEVICES / 2;
		max_id = TEE_NUM_DEVICES;
	पूर्ण

	spin_lock(&driver_lock);
	teedev->id = find_next_zero_bit(dev_mask, max_id, offs);
	अगर (teedev->id < max_id)
		set_bit(teedev->id, dev_mask);
	spin_unlock(&driver_lock);

	अगर (teedev->id >= max_id) अणु
		ret = ERR_PTR(-ENOMEM);
		जाओ err;
	पूर्ण

	snम_लिखो(teedev->name, माप(teedev->name), "tee%s%d",
		 teedesc->flags & TEE_DESC_PRIVILEGED ? "priv" : "",
		 teedev->id - offs);

	teedev->dev.class = tee_class;
	teedev->dev.release = tee_release_device;
	teedev->dev.parent = dev;

	teedev->dev.devt = MKDEV(MAJOR(tee_devt), teedev->id);

	rc = dev_set_name(&teedev->dev, "%s", teedev->name);
	अगर (rc) अणु
		ret = ERR_PTR(rc);
		जाओ err_devt;
	पूर्ण

	cdev_init(&teedev->cdev, &tee_fops);
	teedev->cdev.owner = teedesc->owner;

	dev_set_drvdata(&teedev->dev, driver_data);
	device_initialize(&teedev->dev);

	/* 1 as tee_device_unरेजिस्टर() करोes one final tee_device_put() */
	teedev->num_users = 1;
	init_completion(&teedev->c_no_users);
	mutex_init(&teedev->mutex);
	idr_init(&teedev->idr);

	teedev->desc = teedesc;
	teedev->pool = pool;

	वापस teedev;
err_devt:
	unरेजिस्टर_chrdev_region(teedev->dev.devt, 1);
err:
	pr_err("could not register %s driver\n",
	       teedesc->flags & TEE_DESC_PRIVILEGED ? "privileged" : "client");
	अगर (teedev && teedev->id < TEE_NUM_DEVICES) अणु
		spin_lock(&driver_lock);
		clear_bit(teedev->id, dev_mask);
		spin_unlock(&driver_lock);
	पूर्ण
	kमुक्त(teedev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(tee_device_alloc);

अटल sमाप_प्रकार implementation_id_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tee_device *teedev = container_of(dev, काष्ठा tee_device, dev);
	काष्ठा tee_ioctl_version_data vers;

	teedev->desc->ops->get_version(teedev, &vers);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", vers.impl_id);
पूर्ण
अटल DEVICE_ATTR_RO(implementation_id);

अटल काष्ठा attribute *tee_dev_attrs[] = अणु
	&dev_attr_implementation_id.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(tee_dev);

/**
 * tee_device_रेजिस्टर() - Registers a TEE device
 * @teedev:	Device to रेजिस्टर
 *
 * tee_device_unरेजिस्टर() need to be called to हटाओ the @teedev अगर
 * this function fails.
 *
 * @वापसs < 0 on failure
 */
पूर्णांक tee_device_रेजिस्टर(काष्ठा tee_device *teedev)
अणु
	पूर्णांक rc;

	अगर (teedev->flags & TEE_DEVICE_FLAG_REGISTERED) अणु
		dev_err(&teedev->dev, "attempt to register twice\n");
		वापस -EINVAL;
	पूर्ण

	teedev->dev.groups = tee_dev_groups;

	rc = cdev_device_add(&teedev->cdev, &teedev->dev);
	अगर (rc) अणु
		dev_err(&teedev->dev,
			"unable to cdev_device_add() %s, major %d, minor %d, err=%d\n",
			teedev->name, MAJOR(teedev->dev.devt),
			MINOR(teedev->dev.devt), rc);
		वापस rc;
	पूर्ण

	teedev->flags |= TEE_DEVICE_FLAG_REGISTERED;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tee_device_रेजिस्टर);

व्योम tee_device_put(काष्ठा tee_device *teedev)
अणु
	mutex_lock(&teedev->mutex);
	/* Shouldn't put in this state */
	अगर (!WARN_ON(!teedev->desc)) अणु
		teedev->num_users--;
		अगर (!teedev->num_users) अणु
			teedev->desc = शून्य;
			complete(&teedev->c_no_users);
		पूर्ण
	पूर्ण
	mutex_unlock(&teedev->mutex);
पूर्ण

bool tee_device_get(काष्ठा tee_device *teedev)
अणु
	mutex_lock(&teedev->mutex);
	अगर (!teedev->desc) अणु
		mutex_unlock(&teedev->mutex);
		वापस false;
	पूर्ण
	teedev->num_users++;
	mutex_unlock(&teedev->mutex);
	वापस true;
पूर्ण

/**
 * tee_device_unरेजिस्टर() - Removes a TEE device
 * @teedev:	Device to unरेजिस्टर
 *
 * This function should be called to हटाओ the @teedev even अगर
 * tee_device_रेजिस्टर() hasn't been called yet. Does nothing अगर
 * @teedev is शून्य.
 */
व्योम tee_device_unरेजिस्टर(काष्ठा tee_device *teedev)
अणु
	अगर (!teedev)
		वापस;

	अगर (teedev->flags & TEE_DEVICE_FLAG_REGISTERED)
		cdev_device_del(&teedev->cdev, &teedev->dev);

	tee_device_put(teedev);
	रुको_क्रम_completion(&teedev->c_no_users);

	/*
	 * No need to take a mutex any दीर्घer now since teedev->desc was
	 * set to शून्य beक्रमe teedev->c_no_users was completed.
	 */

	teedev->pool = शून्य;

	put_device(&teedev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(tee_device_unरेजिस्टर);

/**
 * tee_get_drvdata() - Return driver_data poपूर्णांकer
 * @teedev:	Device containing the driver_data poपूर्णांकer
 * @वापसs the driver_data poपूर्णांकer supplied to tee_रेजिस्टर().
 */
व्योम *tee_get_drvdata(काष्ठा tee_device *teedev)
अणु
	वापस dev_get_drvdata(&teedev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(tee_get_drvdata);

काष्ठा match_dev_data अणु
	काष्ठा tee_ioctl_version_data *vers;
	स्थिर व्योम *data;
	पूर्णांक (*match)(काष्ठा tee_ioctl_version_data *, स्थिर व्योम *);
पूर्ण;

अटल पूर्णांक match_dev(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	स्थिर काष्ठा match_dev_data *match_data = data;
	काष्ठा tee_device *teedev = container_of(dev, काष्ठा tee_device, dev);

	teedev->desc->ops->get_version(teedev, match_data->vers);
	वापस match_data->match(match_data->vers, match_data->data);
पूर्ण

काष्ठा tee_context *
tee_client_खोलो_context(काष्ठा tee_context *start,
			पूर्णांक (*match)(काष्ठा tee_ioctl_version_data *,
				     स्थिर व्योम *),
			स्थिर व्योम *data, काष्ठा tee_ioctl_version_data *vers)
अणु
	काष्ठा device *dev = शून्य;
	काष्ठा device *put_dev = शून्य;
	काष्ठा tee_context *ctx = शून्य;
	काष्ठा tee_ioctl_version_data v;
	काष्ठा match_dev_data match_data = अणु vers ? vers : &v, data, match पूर्ण;

	अगर (start)
		dev = &start->teedev->dev;

	करो अणु
		dev = class_find_device(tee_class, dev, &match_data, match_dev);
		अगर (!dev) अणु
			ctx = ERR_PTR(-ENOENT);
			अवरोध;
		पूर्ण

		put_device(put_dev);
		put_dev = dev;

		ctx = teedev_खोलो(container_of(dev, काष्ठा tee_device, dev));
	पूर्ण जबतक (IS_ERR(ctx) && PTR_ERR(ctx) != -ENOMEM);

	put_device(put_dev);
	/*
	 * Default behaviour क्रम in kernel client is to not रुको क्रम
	 * tee-supplicant अगर not present क्रम any requests in this context.
	 * Also this flag could be configured again beक्रमe call to
	 * tee_client_खोलो_session() अगर any in kernel client requires
	 * dअगरferent behaviour.
	 */
	अगर (!IS_ERR(ctx))
		ctx->supp_noरुको = true;

	वापस ctx;
पूर्ण
EXPORT_SYMBOL_GPL(tee_client_खोलो_context);

व्योम tee_client_बंद_context(काष्ठा tee_context *ctx)
अणु
	teedev_बंद_context(ctx);
पूर्ण
EXPORT_SYMBOL_GPL(tee_client_बंद_context);

व्योम tee_client_get_version(काष्ठा tee_context *ctx,
			    काष्ठा tee_ioctl_version_data *vers)
अणु
	ctx->teedev->desc->ops->get_version(ctx->teedev, vers);
पूर्ण
EXPORT_SYMBOL_GPL(tee_client_get_version);

पूर्णांक tee_client_खोलो_session(काष्ठा tee_context *ctx,
			    काष्ठा tee_ioctl_खोलो_session_arg *arg,
			    काष्ठा tee_param *param)
अणु
	अगर (!ctx->teedev->desc->ops->खोलो_session)
		वापस -EINVAL;
	वापस ctx->teedev->desc->ops->खोलो_session(ctx, arg, param);
पूर्ण
EXPORT_SYMBOL_GPL(tee_client_खोलो_session);

पूर्णांक tee_client_बंद_session(काष्ठा tee_context *ctx, u32 session)
अणु
	अगर (!ctx->teedev->desc->ops->बंद_session)
		वापस -EINVAL;
	वापस ctx->teedev->desc->ops->बंद_session(ctx, session);
पूर्ण
EXPORT_SYMBOL_GPL(tee_client_बंद_session);

पूर्णांक tee_client_invoke_func(काष्ठा tee_context *ctx,
			   काष्ठा tee_ioctl_invoke_arg *arg,
			   काष्ठा tee_param *param)
अणु
	अगर (!ctx->teedev->desc->ops->invoke_func)
		वापस -EINVAL;
	वापस ctx->teedev->desc->ops->invoke_func(ctx, arg, param);
पूर्ण
EXPORT_SYMBOL_GPL(tee_client_invoke_func);

पूर्णांक tee_client_cancel_req(काष्ठा tee_context *ctx,
			  काष्ठा tee_ioctl_cancel_arg *arg)
अणु
	अगर (!ctx->teedev->desc->ops->cancel_req)
		वापस -EINVAL;
	वापस ctx->teedev->desc->ops->cancel_req(ctx, arg->cancel_id,
						  arg->session);
पूर्ण

अटल पूर्णांक tee_client_device_match(काष्ठा device *dev,
				   काष्ठा device_driver *drv)
अणु
	स्थिर काष्ठा tee_client_device_id *id_table;
	काष्ठा tee_client_device *tee_device;

	id_table = to_tee_client_driver(drv)->id_table;
	tee_device = to_tee_client_device(dev);

	जबतक (!uuid_is_null(&id_table->uuid)) अणु
		अगर (uuid_equal(&tee_device->id.uuid, &id_table->uuid))
			वापस 1;
		id_table++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tee_client_device_uevent(काष्ठा device *dev,
				    काष्ठा kobj_uevent_env *env)
अणु
	uuid_t *dev_id = &to_tee_client_device(dev)->id.uuid;

	वापस add_uevent_var(env, "MODALIAS=tee:%pUb", dev_id);
पूर्ण

काष्ठा bus_type tee_bus_type = अणु
	.name		= "tee",
	.match		= tee_client_device_match,
	.uevent		= tee_client_device_uevent,
पूर्ण;
EXPORT_SYMBOL_GPL(tee_bus_type);

अटल पूर्णांक __init tee_init(व्योम)
अणु
	पूर्णांक rc;

	tee_class = class_create(THIS_MODULE, "tee");
	अगर (IS_ERR(tee_class)) अणु
		pr_err("couldn't create class\n");
		वापस PTR_ERR(tee_class);
	पूर्ण

	rc = alloc_chrdev_region(&tee_devt, 0, TEE_NUM_DEVICES, "tee");
	अगर (rc) अणु
		pr_err("failed to allocate char dev region\n");
		जाओ out_unreg_class;
	पूर्ण

	rc = bus_रेजिस्टर(&tee_bus_type);
	अगर (rc) अणु
		pr_err("failed to register tee bus\n");
		जाओ out_unreg_chrdev;
	पूर्ण

	वापस 0;

out_unreg_chrdev:
	unरेजिस्टर_chrdev_region(tee_devt, TEE_NUM_DEVICES);
out_unreg_class:
	class_destroy(tee_class);
	tee_class = शून्य;

	वापस rc;
पूर्ण

अटल व्योम __निकास tee_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&tee_bus_type);
	unरेजिस्टर_chrdev_region(tee_devt, TEE_NUM_DEVICES);
	class_destroy(tee_class);
	tee_class = शून्य;
पूर्ण

subsys_initcall(tee_init);
module_निकास(tee_निकास);

MODULE_AUTHOR("Linaro");
MODULE_DESCRIPTION("TEE Driver");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL v2");
