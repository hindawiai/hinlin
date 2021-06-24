<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019-2021 Linaro Ltd.
 *
 * Author:
 * Sumit Garg <sumit.garg@linaro.org>
 */

#समावेश <linux/err.h>
#समावेश <linux/key-type.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/tee_drv.h>
#समावेश <linux/uuid.h>

#समावेश <keys/trusted_tee.h>

#घोषणा DRIVER_NAME "trusted-key-tee"

/*
 * Get अक्रमom data क्रम symmetric key
 *
 * [out]     memref[0]        Ranकरोm data
 */
#घोषणा TA_CMD_GET_RANDOM	0x0

/*
 * Seal trusted key using hardware unique key
 *
 * [in]      memref[0]        Plain key
 * [out]     memref[1]        Sealed key datablob
 */
#घोषणा TA_CMD_SEAL		0x1

/*
 * Unseal trusted key using hardware unique key
 *
 * [in]      memref[0]        Sealed key datablob
 * [out]     memref[1]        Plain key
 */
#घोषणा TA_CMD_UNSEAL		0x2

/**
 * काष्ठा trusted_key_tee_निजी - TEE Trusted key निजी data
 * @dev:		TEE based Trusted key device.
 * @ctx:		TEE context handler.
 * @session_id:		Trusted key TA session identअगरier.
 * @shm_pool:		Memory pool shared with TEE device.
 */
काष्ठा trusted_key_tee_निजी अणु
	काष्ठा device *dev;
	काष्ठा tee_context *ctx;
	u32 session_id;
	काष्ठा tee_shm *shm_pool;
पूर्ण;

अटल काष्ठा trusted_key_tee_निजी pvt_data;

/*
 * Have the TEE seal(encrypt) the symmetric key
 */
अटल पूर्णांक trusted_tee_seal(काष्ठा trusted_key_payload *p, अक्षर *datablob)
अणु
	पूर्णांक ret;
	काष्ठा tee_ioctl_invoke_arg inv_arg;
	काष्ठा tee_param param[4];
	काष्ठा tee_shm *reg_shm_in = शून्य, *reg_shm_out = शून्य;

	स_रखो(&inv_arg, 0, माप(inv_arg));
	स_रखो(&param, 0, माप(param));

	reg_shm_in = tee_shm_रेजिस्टर(pvt_data.ctx, (अचिन्हित दीर्घ)p->key,
				      p->key_len, TEE_SHM_DMA_BUF |
				      TEE_SHM_KERNEL_MAPPED);
	अगर (IS_ERR(reg_shm_in)) अणु
		dev_err(pvt_data.dev, "key shm register failed\n");
		वापस PTR_ERR(reg_shm_in);
	पूर्ण

	reg_shm_out = tee_shm_रेजिस्टर(pvt_data.ctx, (अचिन्हित दीर्घ)p->blob,
				       माप(p->blob), TEE_SHM_DMA_BUF |
				       TEE_SHM_KERNEL_MAPPED);
	अगर (IS_ERR(reg_shm_out)) अणु
		dev_err(pvt_data.dev, "blob shm register failed\n");
		ret = PTR_ERR(reg_shm_out);
		जाओ out;
	पूर्ण

	inv_arg.func = TA_CMD_SEAL;
	inv_arg.session = pvt_data.session_id;
	inv_arg.num_params = 4;

	param[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INPUT;
	param[0].u.memref.shm = reg_shm_in;
	param[0].u.memref.size = p->key_len;
	param[0].u.memref.shm_offs = 0;
	param[1].attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_OUTPUT;
	param[1].u.memref.shm = reg_shm_out;
	param[1].u.memref.size = माप(p->blob);
	param[1].u.memref.shm_offs = 0;

	ret = tee_client_invoke_func(pvt_data.ctx, &inv_arg, param);
	अगर ((ret < 0) || (inv_arg.ret != 0)) अणु
		dev_err(pvt_data.dev, "TA_CMD_SEAL invoke err: %x\n",
			inv_arg.ret);
		ret = -EFAULT;
	पूर्ण अन्यथा अणु
		p->blob_len = param[1].u.memref.size;
	पूर्ण

out:
	अगर (reg_shm_out)
		tee_shm_मुक्त(reg_shm_out);
	अगर (reg_shm_in)
		tee_shm_मुक्त(reg_shm_in);

	वापस ret;
पूर्ण

/*
 * Have the TEE unseal(decrypt) the symmetric key
 */
अटल पूर्णांक trusted_tee_unseal(काष्ठा trusted_key_payload *p, अक्षर *datablob)
अणु
	पूर्णांक ret;
	काष्ठा tee_ioctl_invoke_arg inv_arg;
	काष्ठा tee_param param[4];
	काष्ठा tee_shm *reg_shm_in = शून्य, *reg_shm_out = शून्य;

	स_रखो(&inv_arg, 0, माप(inv_arg));
	स_रखो(&param, 0, माप(param));

	reg_shm_in = tee_shm_रेजिस्टर(pvt_data.ctx, (अचिन्हित दीर्घ)p->blob,
				      p->blob_len, TEE_SHM_DMA_BUF |
				      TEE_SHM_KERNEL_MAPPED);
	अगर (IS_ERR(reg_shm_in)) अणु
		dev_err(pvt_data.dev, "blob shm register failed\n");
		वापस PTR_ERR(reg_shm_in);
	पूर्ण

	reg_shm_out = tee_shm_रेजिस्टर(pvt_data.ctx, (अचिन्हित दीर्घ)p->key,
				       माप(p->key), TEE_SHM_DMA_BUF |
				       TEE_SHM_KERNEL_MAPPED);
	अगर (IS_ERR(reg_shm_out)) अणु
		dev_err(pvt_data.dev, "key shm register failed\n");
		ret = PTR_ERR(reg_shm_out);
		जाओ out;
	पूर्ण

	inv_arg.func = TA_CMD_UNSEAL;
	inv_arg.session = pvt_data.session_id;
	inv_arg.num_params = 4;

	param[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INPUT;
	param[0].u.memref.shm = reg_shm_in;
	param[0].u.memref.size = p->blob_len;
	param[0].u.memref.shm_offs = 0;
	param[1].attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_OUTPUT;
	param[1].u.memref.shm = reg_shm_out;
	param[1].u.memref.size = माप(p->key);
	param[1].u.memref.shm_offs = 0;

	ret = tee_client_invoke_func(pvt_data.ctx, &inv_arg, param);
	अगर ((ret < 0) || (inv_arg.ret != 0)) अणु
		dev_err(pvt_data.dev, "TA_CMD_UNSEAL invoke err: %x\n",
			inv_arg.ret);
		ret = -EFAULT;
	पूर्ण अन्यथा अणु
		p->key_len = param[1].u.memref.size;
	पूर्ण

out:
	अगर (reg_shm_out)
		tee_shm_मुक्त(reg_shm_out);
	अगर (reg_shm_in)
		tee_shm_मुक्त(reg_shm_in);

	वापस ret;
पूर्ण

/*
 * Have the TEE generate अक्रमom symmetric key
 */
अटल पूर्णांक trusted_tee_get_अक्रमom(अचिन्हित अक्षर *key, माप_प्रकार key_len)
अणु
	पूर्णांक ret;
	काष्ठा tee_ioctl_invoke_arg inv_arg;
	काष्ठा tee_param param[4];
	काष्ठा tee_shm *reg_shm = शून्य;

	स_रखो(&inv_arg, 0, माप(inv_arg));
	स_रखो(&param, 0, माप(param));

	reg_shm = tee_shm_रेजिस्टर(pvt_data.ctx, (अचिन्हित दीर्घ)key, key_len,
				   TEE_SHM_DMA_BUF | TEE_SHM_KERNEL_MAPPED);
	अगर (IS_ERR(reg_shm)) अणु
		dev_err(pvt_data.dev, "key shm register failed\n");
		वापस PTR_ERR(reg_shm);
	पूर्ण

	inv_arg.func = TA_CMD_GET_RANDOM;
	inv_arg.session = pvt_data.session_id;
	inv_arg.num_params = 4;

	param[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_OUTPUT;
	param[0].u.memref.shm = reg_shm;
	param[0].u.memref.size = key_len;
	param[0].u.memref.shm_offs = 0;

	ret = tee_client_invoke_func(pvt_data.ctx, &inv_arg, param);
	अगर ((ret < 0) || (inv_arg.ret != 0)) अणु
		dev_err(pvt_data.dev, "TA_CMD_GET_RANDOM invoke err: %x\n",
			inv_arg.ret);
		ret = -EFAULT;
	पूर्ण अन्यथा अणु
		ret = param[0].u.memref.size;
	पूर्ण

	tee_shm_मुक्त(reg_shm);

	वापस ret;
पूर्ण

अटल पूर्णांक optee_ctx_match(काष्ठा tee_ioctl_version_data *ver, स्थिर व्योम *data)
अणु
	अगर (ver->impl_id == TEE_IMPL_ID_OPTEE)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक trusted_key_probe(काष्ठा device *dev)
अणु
	काष्ठा tee_client_device *rng_device = to_tee_client_device(dev);
	पूर्णांक ret;
	काष्ठा tee_ioctl_खोलो_session_arg sess_arg;

	स_रखो(&sess_arg, 0, माप(sess_arg));

	pvt_data.ctx = tee_client_खोलो_context(शून्य, optee_ctx_match, शून्य,
					       शून्य);
	अगर (IS_ERR(pvt_data.ctx))
		वापस -ENODEV;

	स_नकल(sess_arg.uuid, rng_device->id.uuid.b, TEE_IOCTL_UUID_LEN);
	sess_arg.clnt_login = TEE_IOCTL_LOGIN_REE_KERNEL;
	sess_arg.num_params = 0;

	ret = tee_client_खोलो_session(pvt_data.ctx, &sess_arg, शून्य);
	अगर ((ret < 0) || (sess_arg.ret != 0)) अणु
		dev_err(dev, "tee_client_open_session failed, err: %x\n",
			sess_arg.ret);
		ret = -EINVAL;
		जाओ out_ctx;
	पूर्ण
	pvt_data.session_id = sess_arg.session;

	ret = रेजिस्टर_key_type(&key_type_trusted);
	अगर (ret < 0)
		जाओ out_sess;

	pvt_data.dev = dev;

	वापस 0;

out_sess:
	tee_client_बंद_session(pvt_data.ctx, pvt_data.session_id);
out_ctx:
	tee_client_बंद_context(pvt_data.ctx);

	वापस ret;
पूर्ण

अटल पूर्णांक trusted_key_हटाओ(काष्ठा device *dev)
अणु
	unरेजिस्टर_key_type(&key_type_trusted);
	tee_client_बंद_session(pvt_data.ctx, pvt_data.session_id);
	tee_client_बंद_context(pvt_data.ctx);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tee_client_device_id trusted_key_id_table[] = अणु
	अणुUUID_INIT(0xf04a0fe7, 0x1f5d, 0x4b9b,
		   0xab, 0xf7, 0x61, 0x9b, 0x85, 0xb4, 0xce, 0x8c)पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(tee, trusted_key_id_table);

अटल काष्ठा tee_client_driver trusted_key_driver = अणु
	.id_table	= trusted_key_id_table,
	.driver		= अणु
		.name		= DRIVER_NAME,
		.bus		= &tee_bus_type,
		.probe		= trusted_key_probe,
		.हटाओ		= trusted_key_हटाओ,
	पूर्ण,
पूर्ण;

अटल पूर्णांक trusted_tee_init(व्योम)
अणु
	वापस driver_रेजिस्टर(&trusted_key_driver.driver);
पूर्ण

अटल व्योम trusted_tee_निकास(व्योम)
अणु
	driver_unरेजिस्टर(&trusted_key_driver.driver);
पूर्ण

काष्ठा trusted_key_ops trusted_key_tee_ops = अणु
	.migratable = 0, /* non-migratable */
	.init = trusted_tee_init,
	.seal = trusted_tee_seal,
	.unseal = trusted_tee_unseal,
	.get_अक्रमom = trusted_tee_get_अक्रमom,
	.निकास = trusted_tee_निकास,
पूर्ण;
