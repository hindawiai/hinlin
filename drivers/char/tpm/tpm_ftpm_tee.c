<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) Microsoft Corporation
 *
 * Implements a firmware TPM as described here:
 * https://www.microsoft.com/en-us/research/खुलाation/ftpm-software-implementation-tpm-chip/
 *
 * A reference implementation is available here:
 * https://github.com/microsoft/ms-tpm-20-ref/tree/master/Samples/ARM32-FirmwareTPM/optee_ta/fTPM
 */

#समावेश <linux/acpi.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/tee_drv.h>
#समावेश <linux/tpm.h>
#समावेश <linux/uuid.h>

#समावेश "tpm.h"
#समावेश "tpm_ftpm_tee.h"

/*
 * TA_FTPM_UUID: BC50D971-D4C9-42C4-82CB-343FB7F37896
 *
 * Ranकरोmly generated, and must correspond to the GUID on the TA side.
 * Defined here in the reference implementation:
 * https://github.com/microsoft/ms-tpm-20-ref/blob/master/Samples/ARM32-FirmwareTPM/optee_ta/fTPM/include/fTPM.h#L42
 */
अटल स्थिर uuid_t ftpm_ta_uuid =
	UUID_INIT(0xBC50D971, 0xD4C9, 0x42C4,
		  0x82, 0xCB, 0x34, 0x3F, 0xB7, 0xF3, 0x78, 0x96);

/**
 * ftpm_tee_tpm_op_recv() - retrieve fTPM response.
 * @chip:	the tpm_chip description as specअगरied in driver/अक्षर/tpm/tpm.h.
 * @buf:	the buffer to store data.
 * @count:	the number of bytes to पढ़ो.
 *
 * Return:
 *	In हाल of success the number of bytes received.
 *	On failure, -त्रुटि_सं.
 */
अटल पूर्णांक ftpm_tee_tpm_op_recv(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार count)
अणु
	काष्ठा ftpm_tee_निजी *pvt_data = dev_get_drvdata(chip->dev.parent);
	माप_प्रकार len;

	len = pvt_data->resp_len;
	अगर (count < len) अणु
		dev_err(&chip->dev,
			"%s: Invalid size in recv: count=%zd, resp_len=%zd\n",
			__func__, count, len);
		वापस -EIO;
	पूर्ण

	स_नकल(buf, pvt_data->resp_buf, len);
	pvt_data->resp_len = 0;

	वापस len;
पूर्ण

/**
 * ftpm_tee_tpm_op_send() - send TPM commands through the TEE shared memory.
 * @chip:	the tpm_chip description as specअगरied in driver/अक्षर/tpm/tpm.h
 * @buf:	the buffer to send.
 * @len:	the number of bytes to send.
 *
 * Return:
 *	In हाल of success, वापसs 0.
 *	On failure, -त्रुटि_सं
 */
अटल पूर्णांक ftpm_tee_tpm_op_send(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार len)
अणु
	काष्ठा ftpm_tee_निजी *pvt_data = dev_get_drvdata(chip->dev.parent);
	माप_प्रकार resp_len;
	पूर्णांक rc;
	u8 *temp_buf;
	काष्ठा tpm_header *resp_header;
	काष्ठा tee_ioctl_invoke_arg transceive_args;
	काष्ठा tee_param command_params[4];
	काष्ठा tee_shm *shm = pvt_data->shm;

	अगर (len > MAX_COMMAND_SIZE) अणु
		dev_err(&chip->dev,
			"%s: len=%zd exceeds MAX_COMMAND_SIZE supported by fTPM TA\n",
			__func__, len);
		वापस -EIO;
	पूर्ण

	स_रखो(&transceive_args, 0, माप(transceive_args));
	स_रखो(command_params, 0, माप(command_params));
	pvt_data->resp_len = 0;

	/* Invoke FTPM_OPTEE_TA_SUBMIT_COMMAND function of fTPM TA */
	transceive_args = (काष्ठा tee_ioctl_invoke_arg) अणु
		.func = FTPM_OPTEE_TA_SUBMIT_COMMAND,
		.session = pvt_data->session,
		.num_params = 4,
	पूर्ण;

	/* Fill FTPM_OPTEE_TA_SUBMIT_COMMAND parameters */
	command_params[0] = (काष्ठा tee_param) अणु
		.attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INPUT,
		.u.memref = अणु
			.shm = shm,
			.size = len,
			.shm_offs = 0,
		पूर्ण,
	पूर्ण;

	temp_buf = tee_shm_get_va(shm, 0);
	अगर (IS_ERR(temp_buf)) अणु
		dev_err(&chip->dev, "%s: tee_shm_get_va failed for transmit\n",
			__func__);
		वापस PTR_ERR(temp_buf);
	पूर्ण
	स_रखो(temp_buf, 0, (MAX_COMMAND_SIZE + MAX_RESPONSE_SIZE));
	स_नकल(temp_buf, buf, len);

	command_params[1] = (काष्ठा tee_param) अणु
		.attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT,
		.u.memref = अणु
			.shm = shm,
			.size = MAX_RESPONSE_SIZE,
			.shm_offs = MAX_COMMAND_SIZE,
		पूर्ण,
	पूर्ण;

	rc = tee_client_invoke_func(pvt_data->ctx, &transceive_args,
				    command_params);
	अगर ((rc < 0) || (transceive_args.ret != 0)) अणु
		dev_err(&chip->dev, "%s: SUBMIT_COMMAND invoke error: 0x%x\n",
			__func__, transceive_args.ret);
		वापस (rc < 0) ? rc : transceive_args.ret;
	पूर्ण

	temp_buf = tee_shm_get_va(shm, command_params[1].u.memref.shm_offs);
	अगर (IS_ERR(temp_buf)) अणु
		dev_err(&chip->dev, "%s: tee_shm_get_va failed for receive\n",
			__func__);
		वापस PTR_ERR(temp_buf);
	पूर्ण

	resp_header = (काष्ठा tpm_header *)temp_buf;
	resp_len = be32_to_cpu(resp_header->length);

	/* sanity check resp_len */
	अगर (resp_len < TPM_HEADER_SIZE) अणु
		dev_err(&chip->dev, "%s: tpm response header too small\n",
			__func__);
		वापस -EIO;
	पूर्ण
	अगर (resp_len > MAX_RESPONSE_SIZE) अणु
		dev_err(&chip->dev,
			"%s: resp_len=%zd exceeds MAX_RESPONSE_SIZE\n",
			__func__, resp_len);
		वापस -EIO;
	पूर्ण

	/* sanity checks look good, cache the response */
	स_नकल(pvt_data->resp_buf, temp_buf, resp_len);
	pvt_data->resp_len = resp_len;

	वापस 0;
पूर्ण

अटल व्योम ftpm_tee_tpm_op_cancel(काष्ठा tpm_chip *chip)
अणु
	/* not supported */
पूर्ण

अटल u8 ftpm_tee_tpm_op_status(काष्ठा tpm_chip *chip)
अणु
	वापस 0;
पूर्ण

अटल bool ftpm_tee_tpm_req_canceled(काष्ठा tpm_chip *chip, u8 status)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tpm_class_ops ftpm_tee_tpm_ops = अणु
	.flags = TPM_OPS_AUTO_STARTUP,
	.recv = ftpm_tee_tpm_op_recv,
	.send = ftpm_tee_tpm_op_send,
	.cancel = ftpm_tee_tpm_op_cancel,
	.status = ftpm_tee_tpm_op_status,
	.req_complete_mask = 0,
	.req_complete_val = 0,
	.req_canceled = ftpm_tee_tpm_req_canceled,
पूर्ण;

/*
 * Check whether this driver supports the fTPM TA in the TEE instance
 * represented by the params (ver/data) to this function.
 */
अटल पूर्णांक ftpm_tee_match(काष्ठा tee_ioctl_version_data *ver, स्थिर व्योम *data)
अणु
	/*
	 * Currently this driver only support GP Complaपूर्णांक OPTEE based fTPM TA
	 */
	अगर ((ver->impl_id == TEE_IMPL_ID_OPTEE) &&
		(ver->gen_caps & TEE_GEN_CAP_GP))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/**
 * ftpm_tee_probe() - initialize the fTPM
 * @pdev: the platक्रमm_device description.
 *
 * Return:
 *	On success, 0. On failure, -त्रुटि_सं.
 */
अटल पूर्णांक ftpm_tee_probe(काष्ठा device *dev)
अणु
	पूर्णांक rc;
	काष्ठा tpm_chip *chip;
	काष्ठा ftpm_tee_निजी *pvt_data = शून्य;
	काष्ठा tee_ioctl_खोलो_session_arg sess_arg;

	pvt_data = devm_kzalloc(dev, माप(काष्ठा ftpm_tee_निजी),
				GFP_KERNEL);
	अगर (!pvt_data)
		वापस -ENOMEM;

	dev_set_drvdata(dev, pvt_data);

	/* Open context with TEE driver */
	pvt_data->ctx = tee_client_खोलो_context(शून्य, ftpm_tee_match, शून्य,
						शून्य);
	अगर (IS_ERR(pvt_data->ctx)) अणु
		अगर (PTR_ERR(pvt_data->ctx) == -ENOENT)
			वापस -EPROBE_DEFER;
		dev_err(dev, "%s: tee_client_open_context failed\n", __func__);
		वापस PTR_ERR(pvt_data->ctx);
	पूर्ण

	/* Open a session with fTPM TA */
	स_रखो(&sess_arg, 0, माप(sess_arg));
	export_uuid(sess_arg.uuid, &ftpm_ta_uuid);
	sess_arg.clnt_login = TEE_IOCTL_LOGIN_PUBLIC;
	sess_arg.num_params = 0;

	rc = tee_client_खोलो_session(pvt_data->ctx, &sess_arg, शून्य);
	अगर ((rc < 0) || (sess_arg.ret != 0)) अणु
		dev_err(dev, "%s: tee_client_open_session failed, err=%x\n",
			__func__, sess_arg.ret);
		rc = -EINVAL;
		जाओ out_tee_session;
	पूर्ण
	pvt_data->session = sess_arg.session;

	/* Allocate dynamic shared memory with fTPM TA */
	pvt_data->shm = tee_shm_alloc(pvt_data->ctx,
				      MAX_COMMAND_SIZE + MAX_RESPONSE_SIZE,
				      TEE_SHM_MAPPED | TEE_SHM_DMA_BUF);
	अगर (IS_ERR(pvt_data->shm)) अणु
		dev_err(dev, "%s: tee_shm_alloc failed\n", __func__);
		rc = -ENOMEM;
		जाओ out_shm_alloc;
	पूर्ण

	/* Allocate new काष्ठा tpm_chip instance */
	chip = tpm_chip_alloc(dev, &ftpm_tee_tpm_ops);
	अगर (IS_ERR(chip)) अणु
		dev_err(dev, "%s: tpm_chip_alloc failed\n", __func__);
		rc = PTR_ERR(chip);
		जाओ out_chip_alloc;
	पूर्ण

	pvt_data->chip = chip;
	pvt_data->chip->flags |= TPM_CHIP_FLAG_TPM2;

	/* Create a अक्षरacter device क्रम the fTPM */
	rc = tpm_chip_रेजिस्टर(pvt_data->chip);
	अगर (rc) अणु
		dev_err(dev, "%s: tpm_chip_register failed with rc=%d\n",
			__func__, rc);
		जाओ out_chip;
	पूर्ण

	वापस 0;

out_chip:
	put_device(&pvt_data->chip->dev);
out_chip_alloc:
	tee_shm_मुक्त(pvt_data->shm);
out_shm_alloc:
	tee_client_बंद_session(pvt_data->ctx, pvt_data->session);
out_tee_session:
	tee_client_बंद_context(pvt_data->ctx);

	वापस rc;
पूर्ण

अटल पूर्णांक ftpm_plat_tee_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;

	वापस ftpm_tee_probe(dev);
पूर्ण

/**
 * ftpm_tee_हटाओ() - हटाओ the TPM device
 * @pdev: the platक्रमm_device description.
 *
 * Return:
 *	0 always.
 */
अटल पूर्णांक ftpm_tee_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा ftpm_tee_निजी *pvt_data = dev_get_drvdata(dev);

	/* Release the chip */
	tpm_chip_unरेजिस्टर(pvt_data->chip);

	/* मुक्तs chip */
	put_device(&pvt_data->chip->dev);

	/* Free the shared memory pool */
	tee_shm_मुक्त(pvt_data->shm);

	/* बंद the existing session with fTPM TA*/
	tee_client_बंद_session(pvt_data->ctx, pvt_data->session);

	/* बंद the context with TEE driver */
	tee_client_बंद_context(pvt_data->ctx);

	/* memory allocated with devm_kzalloc() is मुक्तd स्वतःmatically */

	वापस 0;
पूर्ण

अटल पूर्णांक ftpm_plat_tee_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;

	वापस ftpm_tee_हटाओ(dev);
पूर्ण

/**
 * ftpm_tee_shutकरोwn() - shutकरोwn the TPM device
 * @pdev: the platक्रमm_device description.
 */
अटल व्योम ftpm_plat_tee_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ftpm_tee_निजी *pvt_data = dev_get_drvdata(&pdev->dev);

	tee_shm_मुक्त(pvt_data->shm);
	tee_client_बंद_session(pvt_data->ctx, pvt_data->session);
	tee_client_बंद_context(pvt_data->ctx);
पूर्ण

अटल स्थिर काष्ठा of_device_id of_ftpm_tee_ids[] = अणु
	अणु .compatible = "microsoft,ftpm" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_ftpm_tee_ids);

अटल काष्ठा platक्रमm_driver ftpm_tee_plat_driver = अणु
	.driver = अणु
		.name = "ftpm-tee",
		.of_match_table = of_match_ptr(of_ftpm_tee_ids),
	पूर्ण,
	.shutकरोwn = ftpm_plat_tee_shutकरोwn,
	.probe = ftpm_plat_tee_probe,
	.हटाओ = ftpm_plat_tee_हटाओ,
पूर्ण;

/* UUID of the fTPM TA */
अटल स्थिर काष्ठा tee_client_device_id optee_ftpm_id_table[] = अणु
	अणुUUID_INIT(0xbc50d971, 0xd4c9, 0x42c4,
		   0x82, 0xcb, 0x34, 0x3f, 0xb7, 0xf3, 0x78, 0x96)पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(tee, optee_ftpm_id_table);

अटल काष्ठा tee_client_driver ftpm_tee_driver = अणु
	.id_table	= optee_ftpm_id_table,
	.driver		= अणु
		.name		= "optee-ftpm",
		.bus		= &tee_bus_type,
		.probe		= ftpm_tee_probe,
		.हटाओ		= ftpm_tee_हटाओ,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ftpm_mod_init(व्योम)
अणु
	पूर्णांक rc;

	rc = platक्रमm_driver_रेजिस्टर(&ftpm_tee_plat_driver);
	अगर (rc)
		वापस rc;

	वापस driver_रेजिस्टर(&ftpm_tee_driver.driver);
पूर्ण

अटल व्योम __निकास ftpm_mod_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ftpm_tee_plat_driver);
	driver_unरेजिस्टर(&ftpm_tee_driver.driver);
पूर्ण

module_init(ftpm_mod_init);
module_निकास(ftpm_mod_निकास);

MODULE_AUTHOR("Thirupathaiah Annapureddy <thiruan@microsoft.com>");
MODULE_DESCRIPTION("TPM Driver for fTPM TA in TEE");
MODULE_LICENSE("GPL v2");
