<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 Broadcom.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/tee_drv.h>
#समावेश <linux/uuid.h>

#समावेश <linux/firmware/broadcom/tee_bnxt_fw.h>

#घोषणा MAX_SHM_MEM_SZ	SZ_4M

#घोषणा MAX_TEE_PARAM_ARRY_MEMB		4

क्रमागत ta_cmd अणु
	/*
	 * TA_CMD_BNXT_FASTBOOT - boot bnxt device by copying f/w पूर्णांकo sram
	 *
	 *	param[0] unused
	 *	param[1] unused
	 *	param[2] unused
	 *	param[3] unused
	 *
	 * Result:
	 *	TEE_SUCCESS - Invoke command success
	 *	TEE_ERROR_ITEM_NOT_FOUND - Corrupt f/w image found on memory
	 */
	TA_CMD_BNXT_FASTBOOT = 0,

	/*
	 * TA_CMD_BNXT_COPY_COREDUMP - copy the core dump पूर्णांकo shm
	 *
	 *	param[0] (inout memref) - Coredump buffer memory reference
	 *	param[1] (in value) - value.a: offset, data to be copied from
	 *			      value.b: size of data to be copied
	 *	param[2] unused
	 *	param[3] unused
	 *
	 * Result:
	 *	TEE_SUCCESS - Invoke command success
	 *	TEE_ERROR_BAD_PARAMETERS - Incorrect input param
	 *	TEE_ERROR_ITEM_NOT_FOUND - Corrupt core dump
	 */
	TA_CMD_BNXT_COPY_COREDUMP = 3,
पूर्ण;

/**
 * काष्ठा tee_bnxt_fw_निजी - OP-TEE bnxt निजी data
 * @dev:		OP-TEE based bnxt device.
 * @ctx:		OP-TEE context handler.
 * @session_id:		TA session identअगरier.
 */
काष्ठा tee_bnxt_fw_निजी अणु
	काष्ठा device *dev;
	काष्ठा tee_context *ctx;
	u32 session_id;
	काष्ठा tee_shm *fw_shm_pool;
पूर्ण;

अटल काष्ठा tee_bnxt_fw_निजी pvt_data;

अटल व्योम prepare_args(पूर्णांक cmd,
			 काष्ठा tee_ioctl_invoke_arg *arg,
			 काष्ठा tee_param *param)
अणु
	स_रखो(arg, 0, माप(*arg));
	स_रखो(param, 0, MAX_TEE_PARAM_ARRY_MEMB * माप(*param));

	arg->func = cmd;
	arg->session = pvt_data.session_id;
	arg->num_params = MAX_TEE_PARAM_ARRY_MEMB;

	/* Fill invoke cmd params */
	चयन (cmd) अणु
	हाल TA_CMD_BNXT_COPY_COREDUMP:
		param[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT;
		param[0].u.memref.shm = pvt_data.fw_shm_pool;
		param[0].u.memref.size = MAX_SHM_MEM_SZ;
		param[0].u.memref.shm_offs = 0;
		param[1].attr = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INPUT;
		अवरोध;
	हाल TA_CMD_BNXT_FASTBOOT:
	शेष:
		/* Nothing to करो */
		अवरोध;
	पूर्ण
पूर्ण

/**
 * tee_bnxt_fw_load() - Load the bnxt firmware
 *		    Uses an OP-TEE call to start a secure
 *		    boot process.
 * Returns 0 on success, negative त्रुटि_सं otherwise.
 */
पूर्णांक tee_bnxt_fw_load(व्योम)
अणु
	पूर्णांक ret = 0;
	काष्ठा tee_ioctl_invoke_arg arg;
	काष्ठा tee_param param[MAX_TEE_PARAM_ARRY_MEMB];

	अगर (!pvt_data.ctx)
		वापस -ENODEV;

	prepare_args(TA_CMD_BNXT_FASTBOOT, &arg, param);

	ret = tee_client_invoke_func(pvt_data.ctx, &arg, param);
	अगर (ret < 0 || arg.ret != 0) अणु
		dev_err(pvt_data.dev,
			"TA_CMD_BNXT_FASTBOOT invoke failed TEE err: %x, ret:%x\n",
			arg.ret, ret);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tee_bnxt_fw_load);

/**
 * tee_bnxt_copy_coredump() - Copy coredump from the allocated memory
 *			    Uses an OP-TEE call to copy coredump
 * @buf:	destination buffer where core dump is copied पूर्णांकo
 * @offset:	offset from the base address of core dump area
 * @size:	size of the dump
 *
 * Returns 0 on success, negative त्रुटि_सं otherwise.
 */
पूर्णांक tee_bnxt_copy_coredump(व्योम *buf, u32 offset, u32 size)
अणु
	काष्ठा tee_ioctl_invoke_arg arg;
	काष्ठा tee_param param[MAX_TEE_PARAM_ARRY_MEMB];
	व्योम *core_data;
	u32 rbytes = size;
	u32 nbytes = 0;
	पूर्णांक ret = 0;

	अगर (!pvt_data.ctx)
		वापस -ENODEV;

	prepare_args(TA_CMD_BNXT_COPY_COREDUMP, &arg, param);

	जबतक (rbytes)  अणु
		nbytes = rbytes;

		nbytes = min_t(u32, rbytes, param[0].u.memref.size);

		/* Fill additional invoke cmd params */
		param[1].u.value.a = offset;
		param[1].u.value.b = nbytes;

		ret = tee_client_invoke_func(pvt_data.ctx, &arg, param);
		अगर (ret < 0 || arg.ret != 0) अणु
			dev_err(pvt_data.dev,
				"TA_CMD_BNXT_COPY_COREDUMP invoke failed TEE err: %x, ret:%x\n",
				arg.ret, ret);
			वापस -EINVAL;
		पूर्ण

		core_data = tee_shm_get_va(pvt_data.fw_shm_pool, 0);
		अगर (IS_ERR(core_data)) अणु
			dev_err(pvt_data.dev, "tee_shm_get_va failed\n");
			वापस PTR_ERR(core_data);
		पूर्ण

		स_नकल(buf, core_data, nbytes);

		rbytes -= nbytes;
		buf += nbytes;
		offset += nbytes;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tee_bnxt_copy_coredump);

अटल पूर्णांक optee_ctx_match(काष्ठा tee_ioctl_version_data *ver, स्थिर व्योम *data)
अणु
	वापस (ver->impl_id == TEE_IMPL_ID_OPTEE);
पूर्ण

अटल पूर्णांक tee_bnxt_fw_probe(काष्ठा device *dev)
अणु
	काष्ठा tee_client_device *bnxt_device = to_tee_client_device(dev);
	पूर्णांक ret, err = -ENODEV;
	काष्ठा tee_ioctl_खोलो_session_arg sess_arg;
	काष्ठा tee_shm *fw_shm_pool;

	स_रखो(&sess_arg, 0, माप(sess_arg));

	/* Open context with TEE driver */
	pvt_data.ctx = tee_client_खोलो_context(शून्य, optee_ctx_match, शून्य,
					       शून्य);
	अगर (IS_ERR(pvt_data.ctx))
		वापस -ENODEV;

	/* Open session with Bnxt load Trusted App */
	स_नकल(sess_arg.uuid, bnxt_device->id.uuid.b, TEE_IOCTL_UUID_LEN);
	sess_arg.clnt_login = TEE_IOCTL_LOGIN_PUBLIC;
	sess_arg.num_params = 0;

	ret = tee_client_खोलो_session(pvt_data.ctx, &sess_arg, शून्य);
	अगर (ret < 0 || sess_arg.ret != 0) अणु
		dev_err(dev, "tee_client_open_session failed, err: %x\n",
			sess_arg.ret);
		err = -EINVAL;
		जाओ out_ctx;
	पूर्ण
	pvt_data.session_id = sess_arg.session;

	pvt_data.dev = dev;

	fw_shm_pool = tee_shm_alloc(pvt_data.ctx, MAX_SHM_MEM_SZ,
				    TEE_SHM_MAPPED | TEE_SHM_DMA_BUF);
	अगर (IS_ERR(fw_shm_pool)) अणु
		dev_err(pvt_data.dev, "tee_shm_alloc failed\n");
		err = PTR_ERR(fw_shm_pool);
		जाओ out_sess;
	पूर्ण

	pvt_data.fw_shm_pool = fw_shm_pool;

	वापस 0;

out_sess:
	tee_client_बंद_session(pvt_data.ctx, pvt_data.session_id);
out_ctx:
	tee_client_बंद_context(pvt_data.ctx);

	वापस err;
पूर्ण

अटल पूर्णांक tee_bnxt_fw_हटाओ(काष्ठा device *dev)
अणु
	tee_shm_मुक्त(pvt_data.fw_shm_pool);
	tee_client_बंद_session(pvt_data.ctx, pvt_data.session_id);
	tee_client_बंद_context(pvt_data.ctx);
	pvt_data.ctx = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tee_client_device_id tee_bnxt_fw_id_table[] = अणु
	अणुUUID_INIT(0x6272636D, 0x2019, 0x0716,
		    0x42, 0x43, 0x4D, 0x5F, 0x53, 0x43, 0x48, 0x49)पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(tee, tee_bnxt_fw_id_table);

अटल काष्ठा tee_client_driver tee_bnxt_fw_driver = अणु
	.id_table	= tee_bnxt_fw_id_table,
	.driver		= अणु
		.name		= KBUILD_MODNAME,
		.bus		= &tee_bus_type,
		.probe		= tee_bnxt_fw_probe,
		.हटाओ		= tee_bnxt_fw_हटाओ,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init tee_bnxt_fw_mod_init(व्योम)
अणु
	वापस driver_रेजिस्टर(&tee_bnxt_fw_driver.driver);
पूर्ण

अटल व्योम __निकास tee_bnxt_fw_mod_निकास(व्योम)
अणु
	driver_unरेजिस्टर(&tee_bnxt_fw_driver.driver);
पूर्ण

module_init(tee_bnxt_fw_mod_init);
module_निकास(tee_bnxt_fw_mod_निकास);

MODULE_AUTHOR("Vikas Gupta <vikas.gupta@broadcom.com>");
MODULE_DESCRIPTION("Broadcom bnxt firmware manager");
MODULE_LICENSE("GPL v2");
