<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/device.h>
#समावेश <linux/tee_drv.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/firmware.h>
#समावेश "amdtee_private.h"
#समावेश "../tee_private.h"
#समावेश <linux/psp-tee.h>

अटल काष्ठा amdtee_driver_data *drv_data;
अटल DEFINE_MUTEX(session_list_mutex);

अटल व्योम amdtee_get_version(काष्ठा tee_device *teedev,
			       काष्ठा tee_ioctl_version_data *vers)
अणु
	काष्ठा tee_ioctl_version_data v = अणु
		.impl_id = TEE_IMPL_ID_AMDTEE,
		.impl_caps = 0,
		.gen_caps = TEE_GEN_CAP_GP,
	पूर्ण;
	*vers = v;
पूर्ण

अटल पूर्णांक amdtee_खोलो(काष्ठा tee_context *ctx)
अणु
	काष्ठा amdtee_context_data *ctxdata;

	ctxdata = kzalloc(माप(*ctxdata), GFP_KERNEL);
	अगर (!ctxdata)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&ctxdata->sess_list);
	INIT_LIST_HEAD(&ctxdata->shm_list);
	mutex_init(&ctxdata->shm_mutex);

	ctx->data = ctxdata;
	वापस 0;
पूर्ण

अटल व्योम release_session(काष्ठा amdtee_session *sess)
अणु
	पूर्णांक i;

	/* Close any खोलो session */
	क्रम (i = 0; i < TEE_NUM_SESSIONS; ++i) अणु
		/* Check अगर session entry 'i' is valid */
		अगर (!test_bit(i, sess->sess_mask))
			जारी;

		handle_बंद_session(sess->ta_handle, sess->session_info[i]);
		handle_unload_ta(sess->ta_handle);
	पूर्ण

	kमुक्त(sess);
पूर्ण

अटल व्योम amdtee_release(काष्ठा tee_context *ctx)
अणु
	काष्ठा amdtee_context_data *ctxdata = ctx->data;

	अगर (!ctxdata)
		वापस;

	जबतक (true) अणु
		काष्ठा amdtee_session *sess;

		sess = list_first_entry_or_null(&ctxdata->sess_list,
						काष्ठा amdtee_session,
						list_node);

		अगर (!sess)
			अवरोध;

		list_del(&sess->list_node);
		release_session(sess);
	पूर्ण
	mutex_destroy(&ctxdata->shm_mutex);
	kमुक्त(ctxdata);

	ctx->data = शून्य;
पूर्ण

/**
 * alloc_session() - Allocate a session काष्ठाure
 * @ctxdata:    TEE Context data काष्ठाure
 * @session:    Session ID क्रम which 'struct amdtee_session' काष्ठाure is to be
 *              allocated.
 *
 * Scans the TEE context's session list to check अगर TA is alपढ़ोy loaded in to
 * TEE. If yes, वापसs the 'session' काष्ठाure क्रम that TA. Else allocates,
 * initializes a new 'session' structure and adds it to context's session list.
 *
 * The caller must hold a mutex.
 *
 * Returns:
 * 'struct amdtee_session *' on success and शून्य on failure.
 */
अटल काष्ठा amdtee_session *alloc_session(काष्ठा amdtee_context_data *ctxdata,
					    u32 session)
अणु
	काष्ठा amdtee_session *sess;
	u32 ta_handle = get_ta_handle(session);

	/* Scan session list to check अगर TA is alपढ़ोy loaded in to TEE */
	list_क्रम_each_entry(sess, &ctxdata->sess_list, list_node)
		अगर (sess->ta_handle == ta_handle) अणु
			kref_get(&sess->refcount);
			वापस sess;
		पूर्ण

	/* Allocate a new session and add to list */
	sess = kzalloc(माप(*sess), GFP_KERNEL);
	अगर (sess) अणु
		sess->ta_handle = ta_handle;
		kref_init(&sess->refcount);
		spin_lock_init(&sess->lock);
		list_add(&sess->list_node, &ctxdata->sess_list);
	पूर्ण

	वापस sess;
पूर्ण

/* Requires mutex to be held */
अटल काष्ठा amdtee_session *find_session(काष्ठा amdtee_context_data *ctxdata,
					   u32 session)
अणु
	u32 ta_handle = get_ta_handle(session);
	u32 index = get_session_index(session);
	काष्ठा amdtee_session *sess;

	अगर (index >= TEE_NUM_SESSIONS)
		वापस शून्य;

	list_क्रम_each_entry(sess, &ctxdata->sess_list, list_node)
		अगर (ta_handle == sess->ta_handle &&
		    test_bit(index, sess->sess_mask))
			वापस sess;

	वापस शून्य;
पूर्ण

u32 get_buffer_id(काष्ठा tee_shm *shm)
अणु
	काष्ठा amdtee_context_data *ctxdata = shm->ctx->data;
	काष्ठा amdtee_shm_data *shmdata;
	u32 buf_id = 0;

	mutex_lock(&ctxdata->shm_mutex);
	list_क्रम_each_entry(shmdata, &ctxdata->shm_list, shm_node)
		अगर (shmdata->kaddr == shm->kaddr) अणु
			buf_id = shmdata->buf_id;
			अवरोध;
		पूर्ण
	mutex_unlock(&ctxdata->shm_mutex);

	वापस buf_id;
पूर्ण

अटल DEFINE_MUTEX(drv_mutex);
अटल पूर्णांक copy_ta_binary(काष्ठा tee_context *ctx, व्योम *ptr, व्योम **ta,
			  माप_प्रकार *ta_size)
अणु
	स्थिर काष्ठा firmware *fw;
	अक्षर fw_name[TA_PATH_MAX];
	काष्ठा अणु
		u32 lo;
		u16 mid;
		u16 hi_ver;
		u8 seq_n[8];
	पूर्ण *uuid = ptr;
	पूर्णांक n, rc = 0;

	n = snम_लिखो(fw_name, TA_PATH_MAX,
		     "%s/%08x-%04x-%04x-%02x%02x%02x%02x%02x%02x%02x%02x.bin",
		     TA_LOAD_PATH, uuid->lo, uuid->mid, uuid->hi_ver,
		     uuid->seq_n[0], uuid->seq_n[1],
		     uuid->seq_n[2], uuid->seq_n[3],
		     uuid->seq_n[4], uuid->seq_n[5],
		     uuid->seq_n[6], uuid->seq_n[7]);
	अगर (n < 0 || n >= TA_PATH_MAX) अणु
		pr_err("failed to get firmware name\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&drv_mutex);
	n = request_firmware(&fw, fw_name, &ctx->teedev->dev);
	अगर (n) अणु
		pr_err("failed to load firmware %s\n", fw_name);
		rc = -ENOMEM;
		जाओ unlock;
	पूर्ण

	*ta_size = roundup(fw->size, PAGE_SIZE);
	*ta = (व्योम *)__get_मुक्त_pages(GFP_KERNEL, get_order(*ta_size));
	अगर (IS_ERR(*ta)) अणु
		pr_err("%s: get_free_pages failed 0x%llx\n", __func__,
		       (u64)*ta);
		rc = -ENOMEM;
		जाओ rel_fw;
	पूर्ण

	स_नकल(*ta, fw->data, fw->size);
rel_fw:
	release_firmware(fw);
unlock:
	mutex_unlock(&drv_mutex);
	वापस rc;
पूर्ण

अटल व्योम destroy_session(काष्ठा kref *ref)
अणु
	काष्ठा amdtee_session *sess = container_of(ref, काष्ठा amdtee_session,
						   refcount);

	mutex_lock(&session_list_mutex);
	list_del(&sess->list_node);
	mutex_unlock(&session_list_mutex);
	kमुक्त(sess);
पूर्ण

पूर्णांक amdtee_खोलो_session(काष्ठा tee_context *ctx,
			काष्ठा tee_ioctl_खोलो_session_arg *arg,
			काष्ठा tee_param *param)
अणु
	काष्ठा amdtee_context_data *ctxdata = ctx->data;
	काष्ठा amdtee_session *sess = शून्य;
	u32 session_info, ta_handle;
	माप_प्रकार ta_size;
	पूर्णांक rc, i;
	व्योम *ta;

	अगर (arg->clnt_login != TEE_IOCTL_LOGIN_PUBLIC) अणु
		pr_err("unsupported client login method\n");
		वापस -EINVAL;
	पूर्ण

	rc = copy_ta_binary(ctx, &arg->uuid[0], &ta, &ta_size);
	अगर (rc) अणु
		pr_err("failed to copy TA binary\n");
		वापस rc;
	पूर्ण

	/* Load the TA binary पूर्णांकo TEE environment */
	handle_load_ta(ta, ta_size, arg);
	अगर (arg->ret != TEEC_SUCCESS)
		जाओ out;

	ta_handle = get_ta_handle(arg->session);

	mutex_lock(&session_list_mutex);
	sess = alloc_session(ctxdata, arg->session);
	mutex_unlock(&session_list_mutex);

	अगर (!sess) अणु
		handle_unload_ta(ta_handle);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Find an empty session index क्रम the given TA */
	spin_lock(&sess->lock);
	i = find_first_zero_bit(sess->sess_mask, TEE_NUM_SESSIONS);
	अगर (i < TEE_NUM_SESSIONS)
		set_bit(i, sess->sess_mask);
	spin_unlock(&sess->lock);

	अगर (i >= TEE_NUM_SESSIONS) अणु
		pr_err("reached maximum session count %d\n", TEE_NUM_SESSIONS);
		handle_unload_ta(ta_handle);
		kref_put(&sess->refcount, destroy_session);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Open session with loaded TA */
	handle_खोलो_session(arg, &session_info, param);
	अगर (arg->ret != TEEC_SUCCESS) अणु
		pr_err("open_session failed %d\n", arg->ret);
		spin_lock(&sess->lock);
		clear_bit(i, sess->sess_mask);
		spin_unlock(&sess->lock);
		handle_unload_ta(ta_handle);
		kref_put(&sess->refcount, destroy_session);
		जाओ out;
	पूर्ण

	sess->session_info[i] = session_info;
	set_session_id(ta_handle, i, &arg->session);
out:
	मुक्त_pages((u64)ta, get_order(ta_size));
	वापस rc;
पूर्ण

पूर्णांक amdtee_बंद_session(काष्ठा tee_context *ctx, u32 session)
अणु
	काष्ठा amdtee_context_data *ctxdata = ctx->data;
	u32 i, ta_handle, session_info;
	काष्ठा amdtee_session *sess;

	pr_debug("%s: sid = 0x%x\n", __func__, session);

	/*
	 * Check that the session is valid and clear the session
	 * usage bit
	 */
	mutex_lock(&session_list_mutex);
	sess = find_session(ctxdata, session);
	अगर (sess) अणु
		ta_handle = get_ta_handle(session);
		i = get_session_index(session);
		session_info = sess->session_info[i];
		spin_lock(&sess->lock);
		clear_bit(i, sess->sess_mask);
		spin_unlock(&sess->lock);
	पूर्ण
	mutex_unlock(&session_list_mutex);

	अगर (!sess)
		वापस -EINVAL;

	/* Close the session */
	handle_बंद_session(ta_handle, session_info);
	handle_unload_ta(ta_handle);

	kref_put(&sess->refcount, destroy_session);

	वापस 0;
पूर्ण

पूर्णांक amdtee_map_shmem(काष्ठा tee_shm *shm)
अणु
	काष्ठा amdtee_context_data *ctxdata;
	काष्ठा amdtee_shm_data *shmnode;
	काष्ठा shmem_desc shmem;
	पूर्णांक rc, count;
	u32 buf_id;

	अगर (!shm)
		वापस -EINVAL;

	shmnode = kदो_स्मृति(माप(*shmnode), GFP_KERNEL);
	अगर (!shmnode)
		वापस -ENOMEM;

	count = 1;
	shmem.kaddr = shm->kaddr;
	shmem.size = shm->size;

	/*
	 * Send a MAP command to TEE and get the corresponding
	 * buffer Id
	 */
	rc = handle_map_shmem(count, &shmem, &buf_id);
	अगर (rc) अणु
		pr_err("map_shmem failed: ret = %d\n", rc);
		kमुक्त(shmnode);
		वापस rc;
	पूर्ण

	shmnode->kaddr = shm->kaddr;
	shmnode->buf_id = buf_id;
	ctxdata = shm->ctx->data;
	mutex_lock(&ctxdata->shm_mutex);
	list_add(&shmnode->shm_node, &ctxdata->shm_list);
	mutex_unlock(&ctxdata->shm_mutex);

	pr_debug("buf_id :[%x] kaddr[%p]\n", shmnode->buf_id, shmnode->kaddr);

	वापस 0;
पूर्ण

व्योम amdtee_unmap_shmem(काष्ठा tee_shm *shm)
अणु
	काष्ठा amdtee_context_data *ctxdata;
	काष्ठा amdtee_shm_data *shmnode;
	u32 buf_id;

	अगर (!shm)
		वापस;

	buf_id = get_buffer_id(shm);
	/* Unmap the shared memory from TEE */
	handle_unmap_shmem(buf_id);

	ctxdata = shm->ctx->data;
	mutex_lock(&ctxdata->shm_mutex);
	list_क्रम_each_entry(shmnode, &ctxdata->shm_list, shm_node)
		अगर (buf_id == shmnode->buf_id) अणु
			list_del(&shmnode->shm_node);
			kमुक्त(shmnode);
			अवरोध;
		पूर्ण
	mutex_unlock(&ctxdata->shm_mutex);
पूर्ण

पूर्णांक amdtee_invoke_func(काष्ठा tee_context *ctx,
		       काष्ठा tee_ioctl_invoke_arg *arg,
		       काष्ठा tee_param *param)
अणु
	काष्ठा amdtee_context_data *ctxdata = ctx->data;
	काष्ठा amdtee_session *sess;
	u32 i, session_info;

	/* Check that the session is valid */
	mutex_lock(&session_list_mutex);
	sess = find_session(ctxdata, arg->session);
	अगर (sess) अणु
		i = get_session_index(arg->session);
		session_info = sess->session_info[i];
	पूर्ण
	mutex_unlock(&session_list_mutex);

	अगर (!sess)
		वापस -EINVAL;

	handle_invoke_cmd(arg, session_info, param);

	वापस 0;
पूर्ण

पूर्णांक amdtee_cancel_req(काष्ठा tee_context *ctx, u32 cancel_id, u32 session)
अणु
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा tee_driver_ops amdtee_ops = अणु
	.get_version = amdtee_get_version,
	.खोलो = amdtee_खोलो,
	.release = amdtee_release,
	.खोलो_session = amdtee_खोलो_session,
	.बंद_session = amdtee_बंद_session,
	.invoke_func = amdtee_invoke_func,
	.cancel_req = amdtee_cancel_req,
पूर्ण;

अटल स्थिर काष्ठा tee_desc amdtee_desc = अणु
	.name = DRIVER_NAME "-clnt",
	.ops = &amdtee_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init amdtee_driver_init(व्योम)
अणु
	काष्ठा tee_device *teedev;
	काष्ठा tee_shm_pool *pool;
	काष्ठा amdtee *amdtee;
	पूर्णांक rc;

	rc = psp_check_tee_status();
	अगर (rc) अणु
		pr_err("amd-tee driver: tee not present\n");
		वापस rc;
	पूर्ण

	drv_data = kzalloc(माप(*drv_data), GFP_KERNEL);
	अगर (!drv_data)
		वापस -ENOMEM;

	amdtee = kzalloc(माप(*amdtee), GFP_KERNEL);
	अगर (!amdtee) अणु
		rc = -ENOMEM;
		जाओ err_kमुक्त_drv_data;
	पूर्ण

	pool = amdtee_config_shm();
	अगर (IS_ERR(pool)) अणु
		pr_err("shared pool configuration error\n");
		rc = PTR_ERR(pool);
		जाओ err_kमुक्त_amdtee;
	पूर्ण

	teedev = tee_device_alloc(&amdtee_desc, शून्य, pool, amdtee);
	अगर (IS_ERR(teedev)) अणु
		rc = PTR_ERR(teedev);
		जाओ err_मुक्त_pool;
	पूर्ण
	amdtee->teedev = teedev;

	rc = tee_device_रेजिस्टर(amdtee->teedev);
	अगर (rc)
		जाओ err_device_unरेजिस्टर;

	amdtee->pool = pool;

	drv_data->amdtee = amdtee;

	pr_info("amd-tee driver initialization successful\n");
	वापस 0;

err_device_unरेजिस्टर:
	tee_device_unरेजिस्टर(amdtee->teedev);

err_मुक्त_pool:
	tee_shm_pool_मुक्त(pool);

err_kमुक्त_amdtee:
	kमुक्त(amdtee);

err_kमुक्त_drv_data:
	kमुक्त(drv_data);
	drv_data = शून्य;

	pr_err("amd-tee driver initialization failed\n");
	वापस rc;
पूर्ण
module_init(amdtee_driver_init);

अटल व्योम __निकास amdtee_driver_निकास(व्योम)
अणु
	काष्ठा amdtee *amdtee;

	अगर (!drv_data || !drv_data->amdtee)
		वापस;

	amdtee = drv_data->amdtee;

	tee_device_unरेजिस्टर(amdtee->teedev);
	tee_shm_pool_मुक्त(amdtee->pool);
पूर्ण
module_निकास(amdtee_driver_निकास);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION("AMD-TEE driver");
MODULE_VERSION("1.0");
MODULE_LICENSE("Dual MIT/GPL");
