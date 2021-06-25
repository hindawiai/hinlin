<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018-2019 Linaro Ltd.
 */

#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/tee_drv.h>
#समावेश <linux/uuid.h>

#घोषणा DRIVER_NAME "optee-rng"

#घोषणा TEE_ERROR_HEALTH_TEST_FAIL	0x00000001

/*
 * TA_CMD_GET_ENTROPY - Get Entropy from RNG
 *
 * param[0] (inout memref) - Entropy buffer memory reference
 * param[1] unused
 * param[2] unused
 * param[3] unused
 *
 * Result:
 * TEE_SUCCESS - Invoke command success
 * TEE_ERROR_BAD_PARAMETERS - Incorrect input param
 * TEE_ERROR_NOT_SUPPORTED - Requested entropy size greater than size of pool
 * TEE_ERROR_HEALTH_TEST_FAIL - Continuous health testing failed
 */
#घोषणा TA_CMD_GET_ENTROPY		0x0

/*
 * TA_CMD_GET_RNG_INFO - Get RNG inक्रमmation
 *
 * param[0] (out value) - value.a: RNG data-rate in bytes per second
 *                        value.b: Quality/Entropy per 1024 bit of data
 * param[1] unused
 * param[2] unused
 * param[3] unused
 *
 * Result:
 * TEE_SUCCESS - Invoke command success
 * TEE_ERROR_BAD_PARAMETERS - Incorrect input param
 */
#घोषणा TA_CMD_GET_RNG_INFO		0x1

#घोषणा MAX_ENTROPY_REQ_SZ		(4 * 1024)

/**
 * काष्ठा optee_rng_निजी - OP-TEE Ranकरोm Number Generator निजी data
 * @dev:		OP-TEE based RNG device.
 * @ctx:		OP-TEE context handler.
 * @session_id:		RNG TA session identअगरier.
 * @data_rate:		RNG data rate.
 * @entropy_shm_pool:	Memory pool shared with RNG device.
 * @optee_rng:		OP-TEE RNG driver काष्ठाure.
 */
काष्ठा optee_rng_निजी अणु
	काष्ठा device *dev;
	काष्ठा tee_context *ctx;
	u32 session_id;
	u32 data_rate;
	काष्ठा tee_shm *entropy_shm_pool;
	काष्ठा hwrng optee_rng;
पूर्ण;

#घोषणा to_optee_rng_निजी(r) \
		container_of(r, काष्ठा optee_rng_निजी, optee_rng)

अटल माप_प्रकार get_optee_rng_data(काष्ठा optee_rng_निजी *pvt_data,
				 व्योम *buf, माप_प्रकार req_size)
अणु
	पूर्णांक ret = 0;
	u8 *rng_data = शून्य;
	माप_प्रकार rng_size = 0;
	काष्ठा tee_ioctl_invoke_arg inv_arg;
	काष्ठा tee_param param[4];

	स_रखो(&inv_arg, 0, माप(inv_arg));
	स_रखो(&param, 0, माप(param));

	/* Invoke TA_CMD_GET_ENTROPY function of Trusted App */
	inv_arg.func = TA_CMD_GET_ENTROPY;
	inv_arg.session = pvt_data->session_id;
	inv_arg.num_params = 4;

	/* Fill invoke cmd params */
	param[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT;
	param[0].u.memref.shm = pvt_data->entropy_shm_pool;
	param[0].u.memref.size = req_size;
	param[0].u.memref.shm_offs = 0;

	ret = tee_client_invoke_func(pvt_data->ctx, &inv_arg, param);
	अगर ((ret < 0) || (inv_arg.ret != 0)) अणु
		dev_err(pvt_data->dev, "TA_CMD_GET_ENTROPY invoke err: %x\n",
			inv_arg.ret);
		वापस 0;
	पूर्ण

	rng_data = tee_shm_get_va(pvt_data->entropy_shm_pool, 0);
	अगर (IS_ERR(rng_data)) अणु
		dev_err(pvt_data->dev, "tee_shm_get_va failed\n");
		वापस 0;
	पूर्ण

	rng_size = param[0].u.memref.size;
	स_नकल(buf, rng_data, rng_size);

	वापस rng_size;
पूर्ण

अटल पूर्णांक optee_rng_पढ़ो(काष्ठा hwrng *rng, व्योम *buf, माप_प्रकार max, bool रुको)
अणु
	काष्ठा optee_rng_निजी *pvt_data = to_optee_rng_निजी(rng);
	माप_प्रकार पढ़ो = 0, rng_size = 0;
	पूर्णांक समयout = 1;
	u8 *data = buf;

	अगर (max > MAX_ENTROPY_REQ_SZ)
		max = MAX_ENTROPY_REQ_SZ;

	जबतक (पढ़ो < max) अणु
		rng_size = get_optee_rng_data(pvt_data, data, (max - पढ़ो));

		data += rng_size;
		पढ़ो += rng_size;

		अगर (रुको && pvt_data->data_rate) अणु
			अगर ((समयout-- == 0) || (पढ़ो == max))
				वापस पढ़ो;
			msleep((1000 * (max - पढ़ो)) / pvt_data->data_rate);
		पूर्ण अन्यथा अणु
			वापस पढ़ो;
		पूर्ण
	पूर्ण

	वापस पढ़ो;
पूर्ण

अटल पूर्णांक optee_rng_init(काष्ठा hwrng *rng)
अणु
	काष्ठा optee_rng_निजी *pvt_data = to_optee_rng_निजी(rng);
	काष्ठा tee_shm *entropy_shm_pool = शून्य;

	entropy_shm_pool = tee_shm_alloc(pvt_data->ctx, MAX_ENTROPY_REQ_SZ,
					 TEE_SHM_MAPPED | TEE_SHM_DMA_BUF);
	अगर (IS_ERR(entropy_shm_pool)) अणु
		dev_err(pvt_data->dev, "tee_shm_alloc failed\n");
		वापस PTR_ERR(entropy_shm_pool);
	पूर्ण

	pvt_data->entropy_shm_pool = entropy_shm_pool;

	वापस 0;
पूर्ण

अटल व्योम optee_rng_cleanup(काष्ठा hwrng *rng)
अणु
	काष्ठा optee_rng_निजी *pvt_data = to_optee_rng_निजी(rng);

	tee_shm_मुक्त(pvt_data->entropy_shm_pool);
पूर्ण

अटल काष्ठा optee_rng_निजी pvt_data = अणु
	.optee_rng = अणु
		.name		= DRIVER_NAME,
		.init		= optee_rng_init,
		.cleanup	= optee_rng_cleanup,
		.पढ़ो		= optee_rng_पढ़ो,
	पूर्ण
पूर्ण;

अटल पूर्णांक get_optee_rng_info(काष्ठा device *dev)
अणु
	पूर्णांक ret = 0;
	काष्ठा tee_ioctl_invoke_arg inv_arg;
	काष्ठा tee_param param[4];

	स_रखो(&inv_arg, 0, माप(inv_arg));
	स_रखो(&param, 0, माप(param));

	/* Invoke TA_CMD_GET_RNG_INFO function of Trusted App */
	inv_arg.func = TA_CMD_GET_RNG_INFO;
	inv_arg.session = pvt_data.session_id;
	inv_arg.num_params = 4;

	/* Fill invoke cmd params */
	param[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_OUTPUT;

	ret = tee_client_invoke_func(pvt_data.ctx, &inv_arg, param);
	अगर ((ret < 0) || (inv_arg.ret != 0)) अणु
		dev_err(dev, "TA_CMD_GET_RNG_INFO invoke err: %x\n",
			inv_arg.ret);
		वापस -EINVAL;
	पूर्ण

	pvt_data.data_rate = param[0].u.value.a;
	pvt_data.optee_rng.quality = param[0].u.value.b;

	वापस 0;
पूर्ण

अटल पूर्णांक optee_ctx_match(काष्ठा tee_ioctl_version_data *ver, स्थिर व्योम *data)
अणु
	अगर (ver->impl_id == TEE_IMPL_ID_OPTEE)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक optee_rng_probe(काष्ठा device *dev)
अणु
	काष्ठा tee_client_device *rng_device = to_tee_client_device(dev);
	पूर्णांक ret = 0, err = -ENODEV;
	काष्ठा tee_ioctl_खोलो_session_arg sess_arg;

	स_रखो(&sess_arg, 0, माप(sess_arg));

	/* Open context with TEE driver */
	pvt_data.ctx = tee_client_खोलो_context(शून्य, optee_ctx_match, शून्य,
					       शून्य);
	अगर (IS_ERR(pvt_data.ctx))
		वापस -ENODEV;

	/* Open session with hwrng Trusted App */
	export_uuid(sess_arg.uuid, &rng_device->id.uuid);
	sess_arg.clnt_login = TEE_IOCTL_LOGIN_PUBLIC;
	sess_arg.num_params = 0;

	ret = tee_client_खोलो_session(pvt_data.ctx, &sess_arg, शून्य);
	अगर ((ret < 0) || (sess_arg.ret != 0)) अणु
		dev_err(dev, "tee_client_open_session failed, err: %x\n",
			sess_arg.ret);
		err = -EINVAL;
		जाओ out_ctx;
	पूर्ण
	pvt_data.session_id = sess_arg.session;

	err = get_optee_rng_info(dev);
	अगर (err)
		जाओ out_sess;

	err = devm_hwrng_रेजिस्टर(dev, &pvt_data.optee_rng);
	अगर (err) अणु
		dev_err(dev, "hwrng registration failed (%d)\n", err);
		जाओ out_sess;
	पूर्ण

	pvt_data.dev = dev;

	वापस 0;

out_sess:
	tee_client_बंद_session(pvt_data.ctx, pvt_data.session_id);
out_ctx:
	tee_client_बंद_context(pvt_data.ctx);

	वापस err;
पूर्ण

अटल पूर्णांक optee_rng_हटाओ(काष्ठा device *dev)
अणु
	tee_client_बंद_session(pvt_data.ctx, pvt_data.session_id);
	tee_client_बंद_context(pvt_data.ctx);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tee_client_device_id optee_rng_id_table[] = अणु
	अणुUUID_INIT(0xab7a617c, 0xb8e7, 0x4d8f,
		   0x83, 0x01, 0xd0, 0x9b, 0x61, 0x03, 0x6b, 0x64)पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(tee, optee_rng_id_table);

अटल काष्ठा tee_client_driver optee_rng_driver = अणु
	.id_table	= optee_rng_id_table,
	.driver		= अणु
		.name		= DRIVER_NAME,
		.bus		= &tee_bus_type,
		.probe		= optee_rng_probe,
		.हटाओ		= optee_rng_हटाओ,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init optee_rng_mod_init(व्योम)
अणु
	वापस driver_रेजिस्टर(&optee_rng_driver.driver);
पूर्ण

अटल व्योम __निकास optee_rng_mod_निकास(व्योम)
अणु
	driver_unरेजिस्टर(&optee_rng_driver.driver);
पूर्ण

module_init(optee_rng_mod_init);
module_निकास(optee_rng_mod_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Sumit Garg <sumit.garg@linaro.org>");
MODULE_DESCRIPTION("OP-TEE based random number generator driver");
