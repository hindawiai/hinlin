<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 Linaro Ltd.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/tee_drv.h>
#समावेश <linux/uuid.h>
#समावेश "optee_private.h"

अटल पूर्णांक optee_ctx_match(काष्ठा tee_ioctl_version_data *ver, स्थिर व्योम *data)
अणु
	अगर (ver->impl_id == TEE_IMPL_ID_OPTEE)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक get_devices(काष्ठा tee_context *ctx, u32 session,
		       काष्ठा tee_shm *device_shm, u32 *shm_size,
		       u32 func)
अणु
	पूर्णांक ret = 0;
	काष्ठा tee_ioctl_invoke_arg inv_arg;
	काष्ठा tee_param param[4];

	स_रखो(&inv_arg, 0, माप(inv_arg));
	स_रखो(&param, 0, माप(param));

	inv_arg.func = func;
	inv_arg.session = session;
	inv_arg.num_params = 4;

	/* Fill invoke cmd params */
	param[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_OUTPUT;
	param[0].u.memref.shm = device_shm;
	param[0].u.memref.size = *shm_size;
	param[0].u.memref.shm_offs = 0;

	ret = tee_client_invoke_func(ctx, &inv_arg, param);
	अगर ((ret < 0) || ((inv_arg.ret != TEEC_SUCCESS) &&
			  (inv_arg.ret != TEEC_ERROR_SHORT_BUFFER))) अणु
		pr_err("PTA_CMD_GET_DEVICES invoke function err: %x\n",
		       inv_arg.ret);
		वापस -EINVAL;
	पूर्ण

	*shm_size = param[0].u.memref.size;

	वापस 0;
पूर्ण

अटल पूर्णांक optee_रेजिस्टर_device(स्थिर uuid_t *device_uuid)
अणु
	काष्ठा tee_client_device *optee_device = शून्य;
	पूर्णांक rc;

	optee_device = kzalloc(माप(*optee_device), GFP_KERNEL);
	अगर (!optee_device)
		वापस -ENOMEM;

	optee_device->dev.bus = &tee_bus_type;
	अगर (dev_set_name(&optee_device->dev, "optee-ta-%pUb", device_uuid)) अणु
		kमुक्त(optee_device);
		वापस -ENOMEM;
	पूर्ण
	uuid_copy(&optee_device->id.uuid, device_uuid);

	rc = device_रेजिस्टर(&optee_device->dev);
	अगर (rc) अणु
		pr_err("device registration failed, err: %d\n", rc);
		kमुक्त(optee_device);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक __optee_क्रमागतerate_devices(u32 func)
अणु
	स्थिर uuid_t pta_uuid =
		UUID_INIT(0x7011a688, 0xddde, 0x4053,
			  0xa5, 0xa9, 0x7b, 0x3c, 0x4d, 0xdf, 0x13, 0xb8);
	काष्ठा tee_ioctl_खोलो_session_arg sess_arg;
	काष्ठा tee_shm *device_shm = शून्य;
	स्थिर uuid_t *device_uuid = शून्य;
	काष्ठा tee_context *ctx = शून्य;
	u32 shm_size = 0, idx, num_devices = 0;
	पूर्णांक rc;

	स_रखो(&sess_arg, 0, माप(sess_arg));

	/* Open context with OP-TEE driver */
	ctx = tee_client_खोलो_context(शून्य, optee_ctx_match, शून्य, शून्य);
	अगर (IS_ERR(ctx))
		वापस -ENODEV;

	/* Open session with device क्रमागतeration pseuकरो TA */
	export_uuid(sess_arg.uuid, &pta_uuid);
	sess_arg.clnt_login = TEE_IOCTL_LOGIN_PUBLIC;
	sess_arg.num_params = 0;

	rc = tee_client_खोलो_session(ctx, &sess_arg, शून्य);
	अगर ((rc < 0) || (sess_arg.ret != TEEC_SUCCESS)) अणु
		/* Device क्रमागतeration pseuकरो TA not found */
		rc = 0;
		जाओ out_ctx;
	पूर्ण

	rc = get_devices(ctx, sess_arg.session, शून्य, &shm_size, func);
	अगर (rc < 0 || !shm_size)
		जाओ out_sess;

	device_shm = tee_shm_alloc(ctx, shm_size,
				   TEE_SHM_MAPPED | TEE_SHM_DMA_BUF);
	अगर (IS_ERR(device_shm)) अणु
		pr_err("tee_shm_alloc failed\n");
		rc = PTR_ERR(device_shm);
		जाओ out_sess;
	पूर्ण

	rc = get_devices(ctx, sess_arg.session, device_shm, &shm_size, func);
	अगर (rc < 0)
		जाओ out_shm;

	device_uuid = tee_shm_get_va(device_shm, 0);
	अगर (IS_ERR(device_uuid)) अणु
		pr_err("tee_shm_get_va failed\n");
		rc = PTR_ERR(device_uuid);
		जाओ out_shm;
	पूर्ण

	num_devices = shm_size / माप(uuid_t);

	क्रम (idx = 0; idx < num_devices; idx++) अणु
		rc = optee_रेजिस्टर_device(&device_uuid[idx]);
		अगर (rc)
			जाओ out_shm;
	पूर्ण

out_shm:
	tee_shm_मुक्त(device_shm);
out_sess:
	tee_client_बंद_session(ctx, sess_arg.session);
out_ctx:
	tee_client_बंद_context(ctx);

	वापस rc;
पूर्ण

पूर्णांक optee_क्रमागतerate_devices(u32 func)
अणु
	वापस  __optee_क्रमागतerate_devices(func);
पूर्ण
