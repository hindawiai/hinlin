<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018-2019, Intel Corporation
 */

#समावेश <linux/arm-smccc.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/completion.h>
#समावेश <linux/kobject.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/firmware/पूर्णांकel/stratix10-svc-client.h>
#समावेश <linux/माला.स>
#समावेश <linux/sysfs.h>

#घोषणा RSU_STATE_MASK			GENMASK_ULL(31, 0)
#घोषणा RSU_VERSION_MASK		GENMASK_ULL(63, 32)
#घोषणा RSU_ERROR_LOCATION_MASK		GENMASK_ULL(31, 0)
#घोषणा RSU_ERROR_DETAIL_MASK		GENMASK_ULL(63, 32)
#घोषणा RSU_DCMF0_MASK			GENMASK_ULL(31, 0)
#घोषणा RSU_DCMF1_MASK			GENMASK_ULL(63, 32)
#घोषणा RSU_DCMF2_MASK			GENMASK_ULL(31, 0)
#घोषणा RSU_DCMF3_MASK			GENMASK_ULL(63, 32)

#घोषणा RSU_TIMEOUT	(msecs_to_jअगरfies(SVC_RSU_REQUEST_TIMEOUT_MS))

#घोषणा INVALID_RETRY_COUNTER		0xFF
#घोषणा INVALID_DCMF_VERSION		0xFF


प्रकार व्योम (*rsu_callback)(काष्ठा stratix10_svc_client *client,
			     काष्ठा stratix10_svc_cb_data *data);
/**
 * काष्ठा stratix10_rsu_priv - rsu data काष्ठाure
 * @chan: poपूर्णांकer to the allocated service channel
 * @client: active service client
 * @completion: state क्रम callback completion
 * @lock: a mutex to protect callback completion state
 * @status.current_image: address of image currently running in flash
 * @status.fail_image: address of failed image in flash
 * @status.version: the पूर्णांकerface version number of RSU firmware
 * @status.state: the state of RSU प्रणाली
 * @status.error_details: error code
 * @status.error_location: the error offset inside the image that failed
 * @dcmf_version.dcmf0: Quartus dcmf0 version
 * @dcmf_version.dcmf1: Quartus dcmf1 version
 * @dcmf_version.dcmf2: Quartus dcmf2 version
 * @dcmf_version.dcmf3: Quartus dcmf3 version
 * @retry_counter: the current image's retry counter
 * @max_retry: the preset max retry value
 */
काष्ठा stratix10_rsu_priv अणु
	काष्ठा stratix10_svc_chan *chan;
	काष्ठा stratix10_svc_client client;
	काष्ठा completion completion;
	काष्ठा mutex lock;
	काष्ठा अणु
		अचिन्हित दीर्घ current_image;
		अचिन्हित दीर्घ fail_image;
		अचिन्हित पूर्णांक version;
		अचिन्हित पूर्णांक state;
		अचिन्हित पूर्णांक error_details;
		अचिन्हित पूर्णांक error_location;
	पूर्ण status;

	काष्ठा अणु
		अचिन्हित पूर्णांक dcmf0;
		अचिन्हित पूर्णांक dcmf1;
		अचिन्हित पूर्णांक dcmf2;
		अचिन्हित पूर्णांक dcmf3;
	पूर्ण dcmf_version;

	अचिन्हित पूर्णांक retry_counter;
	अचिन्हित पूर्णांक max_retry;
पूर्ण;

/**
 * rsu_status_callback() - Status callback from Intel Service Layer
 * @client: poपूर्णांकer to service client
 * @data: poपूर्णांकer to callback data काष्ठाure
 *
 * Callback from Intel service layer क्रम RSU status request. Status is
 * only updated after a प्रणाली reboot, so a get updated status call is
 * made during driver probe.
 */
अटल व्योम rsu_status_callback(काष्ठा stratix10_svc_client *client,
				काष्ठा stratix10_svc_cb_data *data)
अणु
	काष्ठा stratix10_rsu_priv *priv = client->priv;
	काष्ठा arm_smccc_res *res = (काष्ठा arm_smccc_res *)data->kaddr1;

	अगर (data->status == BIT(SVC_STATUS_OK)) अणु
		priv->status.version = FIELD_GET(RSU_VERSION_MASK,
						 res->a2);
		priv->status.state = FIELD_GET(RSU_STATE_MASK, res->a2);
		priv->status.fail_image = res->a1;
		priv->status.current_image = res->a0;
		priv->status.error_location =
			FIELD_GET(RSU_ERROR_LOCATION_MASK, res->a3);
		priv->status.error_details =
			FIELD_GET(RSU_ERROR_DETAIL_MASK, res->a3);
	पूर्ण अन्यथा अणु
		dev_err(client->dev, "COMMAND_RSU_STATUS returned 0x%lX\n",
			res->a0);
		priv->status.version = 0;
		priv->status.state = 0;
		priv->status.fail_image = 0;
		priv->status.current_image = 0;
		priv->status.error_location = 0;
		priv->status.error_details = 0;
	पूर्ण

	complete(&priv->completion);
पूर्ण

/**
 * rsu_command_callback() - Update callback from Intel Service Layer
 * @client: poपूर्णांकer to client
 * @data: poपूर्णांकer to callback data काष्ठाure
 *
 * Callback from Intel service layer क्रम RSU commands.
 */
अटल व्योम rsu_command_callback(काष्ठा stratix10_svc_client *client,
				 काष्ठा stratix10_svc_cb_data *data)
अणु
	काष्ठा stratix10_rsu_priv *priv = client->priv;

	अगर (data->status == BIT(SVC_STATUS_NO_SUPPORT))
		dev_warn(client->dev, "FW doesn't support notify\n");
	अन्यथा अगर (data->status == BIT(SVC_STATUS_ERROR))
		dev_err(client->dev, "Failure, returned status is %lu\n",
			BIT(data->status));

	complete(&priv->completion);
पूर्ण

/**
 * rsu_retry_callback() - Callback from Intel service layer क्रम getting
 * the current image's retry counter from the firmware
 * @client: poपूर्णांकer to client
 * @data: poपूर्णांकer to callback data काष्ठाure
 *
 * Callback from Intel service layer क्रम retry counter, which is used by
 * user to know how many बार the images is still allowed to reload
 * itself beक्रमe giving up and starting RSU fail-over flow.
 */
अटल व्योम rsu_retry_callback(काष्ठा stratix10_svc_client *client,
			       काष्ठा stratix10_svc_cb_data *data)
अणु
	काष्ठा stratix10_rsu_priv *priv = client->priv;
	अचिन्हित पूर्णांक *counter = (अचिन्हित पूर्णांक *)data->kaddr1;

	अगर (data->status == BIT(SVC_STATUS_OK))
		priv->retry_counter = *counter;
	अन्यथा अगर (data->status == BIT(SVC_STATUS_NO_SUPPORT))
		dev_warn(client->dev, "FW doesn't support retry\n");
	अन्यथा
		dev_err(client->dev, "Failed to get retry counter %lu\n",
			BIT(data->status));

	complete(&priv->completion);
पूर्ण

/**
 * rsu_max_retry_callback() - Callback from Intel service layer क्रम getting
 * the max retry value from the firmware
 * @client: poपूर्णांकer to client
 * @data: poपूर्णांकer to callback data काष्ठाure
 *
 * Callback from Intel service layer क्रम max retry.
 */
अटल व्योम rsu_max_retry_callback(काष्ठा stratix10_svc_client *client,
				   काष्ठा stratix10_svc_cb_data *data)
अणु
	काष्ठा stratix10_rsu_priv *priv = client->priv;
	अचिन्हित पूर्णांक *max_retry = (अचिन्हित पूर्णांक *)data->kaddr1;

	अगर (data->status == BIT(SVC_STATUS_OK))
		priv->max_retry = *max_retry;
	अन्यथा अगर (data->status == BIT(SVC_STATUS_NO_SUPPORT))
		dev_warn(client->dev, "FW doesn't support max retry\n");
	अन्यथा
		dev_err(client->dev, "Failed to get max retry %lu\n",
			BIT(data->status));

	complete(&priv->completion);
पूर्ण

/**
 * rsu_dcmf_version_callback() - Callback from Intel service layer क्रम getting
 * the DCMF version
 * @client: poपूर्णांकer to client
 * @data: poपूर्णांकer to callback data काष्ठाure
 *
 * Callback from Intel service layer क्रम DCMF version number
 */
अटल व्योम rsu_dcmf_version_callback(काष्ठा stratix10_svc_client *client,
				      काष्ठा stratix10_svc_cb_data *data)
अणु
	काष्ठा stratix10_rsu_priv *priv = client->priv;
	अचिन्हित दीर्घ दीर्घ *value1 = (अचिन्हित दीर्घ दीर्घ *)data->kaddr1;
	अचिन्हित दीर्घ दीर्घ *value2 = (अचिन्हित दीर्घ दीर्घ *)data->kaddr2;

	अगर (data->status == BIT(SVC_STATUS_OK)) अणु
		priv->dcmf_version.dcmf0 = FIELD_GET(RSU_DCMF0_MASK, *value1);
		priv->dcmf_version.dcmf1 = FIELD_GET(RSU_DCMF1_MASK, *value1);
		priv->dcmf_version.dcmf2 = FIELD_GET(RSU_DCMF2_MASK, *value2);
		priv->dcmf_version.dcmf3 = FIELD_GET(RSU_DCMF3_MASK, *value2);
	पूर्ण अन्यथा
		dev_err(client->dev, "failed to get DCMF version\n");

	complete(&priv->completion);
पूर्ण

/**
 * rsu_send_msg() - send a message to Intel service layer
 * @priv: poपूर्णांकer to rsu निजी data
 * @command: RSU status or update command
 * @arg: the request argument, the bitstream address or notअगरy status
 * @callback: function poपूर्णांकer क्रम the callback (status or update)
 *
 * Start an Intel service layer transaction to perक्रमm the SMC call that
 * is necessary to get RSU boot log or set the address of bitstream to
 * boot after reboot.
 *
 * Returns 0 on success or -ETIMEDOUT on error.
 */
अटल पूर्णांक rsu_send_msg(काष्ठा stratix10_rsu_priv *priv,
			क्रमागत stratix10_svc_command_code command,
			अचिन्हित दीर्घ arg,
			rsu_callback callback)
अणु
	काष्ठा stratix10_svc_client_msg msg;
	पूर्णांक ret;

	mutex_lock(&priv->lock);
	reinit_completion(&priv->completion);
	priv->client.receive_cb = callback;

	msg.command = command;
	अगर (arg)
		msg.arg[0] = arg;

	ret = stratix10_svc_send(priv->chan, &msg);
	अगर (ret < 0)
		जाओ status_करोne;

	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&priv->completion,
							RSU_TIMEOUT);
	अगर (!ret) अणु
		dev_err(priv->client.dev,
			"timeout waiting for SMC call\n");
		ret = -ETIMEDOUT;
		जाओ status_करोne;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		dev_err(priv->client.dev,
			"error %d waiting for SMC call\n", ret);
		जाओ status_करोne;
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

status_करोne:
	stratix10_svc_करोne(priv->chan);
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

/*
 * This driver exposes some optional features of the Intel Stratix 10 SoC FPGA.
 * The sysfs पूर्णांकerfaces exposed here are FPGA Remote System Update (RSU)
 * related. They allow user space software to query the configuration प्रणाली
 * status and to request optional reboot behavior specअगरic to Intel FPGAs.
 */

अटल sमाप_प्रकार current_image_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा stratix10_rsu_priv *priv = dev_get_drvdata(dev);

	अगर (!priv)
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "0x%08lx\n", priv->status.current_image);
पूर्ण

अटल sमाप_प्रकार fail_image_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा stratix10_rsu_priv *priv = dev_get_drvdata(dev);

	अगर (!priv)
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "0x%08lx\n", priv->status.fail_image);
पूर्ण

अटल sमाप_प्रकार version_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा stratix10_rsu_priv *priv = dev_get_drvdata(dev);

	अगर (!priv)
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "0x%08x\n", priv->status.version);
पूर्ण

अटल sमाप_प्रकार state_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा stratix10_rsu_priv *priv = dev_get_drvdata(dev);

	अगर (!priv)
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "0x%08x\n", priv->status.state);
पूर्ण

अटल sमाप_प्रकार error_location_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा stratix10_rsu_priv *priv = dev_get_drvdata(dev);

	अगर (!priv)
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "0x%08x\n", priv->status.error_location);
पूर्ण

अटल sमाप_प्रकार error_details_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा stratix10_rsu_priv *priv = dev_get_drvdata(dev);

	अगर (!priv)
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "0x%08x\n", priv->status.error_details);
पूर्ण

अटल sमाप_प्रकार retry_counter_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा stratix10_rsu_priv *priv = dev_get_drvdata(dev);

	अगर (!priv)
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "0x%08x\n", priv->retry_counter);
पूर्ण

अटल sमाप_प्रकार max_retry_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा stratix10_rsu_priv *priv = dev_get_drvdata(dev);

	अगर (!priv)
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "0x%08x\n", priv->max_retry);
पूर्ण

अटल sमाप_प्रकार dcmf0_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा stratix10_rsu_priv *priv = dev_get_drvdata(dev);

	अगर (!priv)
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "0x%08x\n", priv->dcmf_version.dcmf0);
पूर्ण

अटल sमाप_प्रकार dcmf1_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा stratix10_rsu_priv *priv = dev_get_drvdata(dev);

	अगर (!priv)
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "0x%08x\n", priv->dcmf_version.dcmf1);
पूर्ण

अटल sमाप_प्रकार dcmf2_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा stratix10_rsu_priv *priv = dev_get_drvdata(dev);

	अगर (!priv)
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "0x%08x\n", priv->dcmf_version.dcmf2);
पूर्ण

अटल sमाप_प्रकार dcmf3_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा stratix10_rsu_priv *priv = dev_get_drvdata(dev);

	अगर (!priv)
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "0x%08x\n", priv->dcmf_version.dcmf3);
पूर्ण

अटल sमाप_प्रकार reboot_image_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा stratix10_rsu_priv *priv = dev_get_drvdata(dev);
	अचिन्हित दीर्घ address;
	पूर्णांक ret;

	अगर (!priv)
		वापस -ENODEV;

	ret = kम_से_अदीर्घ(buf, 0, &address);
	अगर (ret)
		वापस ret;

	ret = rsu_send_msg(priv, COMMAND_RSU_UPDATE,
			   address, rsu_command_callback);
	अगर (ret) अणु
		dev_err(dev, "Error, RSU update returned %i\n", ret);
		वापस ret;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार notअगरy_store(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा stratix10_rsu_priv *priv = dev_get_drvdata(dev);
	अचिन्हित दीर्घ status;
	पूर्णांक ret;

	अगर (!priv)
		वापस -ENODEV;

	ret = kम_से_अदीर्घ(buf, 0, &status);
	अगर (ret)
		वापस ret;

	ret = rsu_send_msg(priv, COMMAND_RSU_NOTIFY,
			   status, rsu_command_callback);
	अगर (ret) अणु
		dev_err(dev, "Error, RSU notify returned %i\n", ret);
		वापस ret;
	पूर्ण

	/* to get the updated state */
	ret = rsu_send_msg(priv, COMMAND_RSU_STATUS,
			   0, rsu_status_callback);
	अगर (ret) अणु
		dev_err(dev, "Error, getting RSU status %i\n", ret);
		वापस ret;
	पूर्ण

	ret = rsu_send_msg(priv, COMMAND_RSU_RETRY, 0, rsu_retry_callback);
	अगर (ret) अणु
		dev_err(dev, "Error, getting RSU retry %i\n", ret);
		वापस ret;
	पूर्ण

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RO(current_image);
अटल DEVICE_ATTR_RO(fail_image);
अटल DEVICE_ATTR_RO(state);
अटल DEVICE_ATTR_RO(version);
अटल DEVICE_ATTR_RO(error_location);
अटल DEVICE_ATTR_RO(error_details);
अटल DEVICE_ATTR_RO(retry_counter);
अटल DEVICE_ATTR_RO(max_retry);
अटल DEVICE_ATTR_RO(dcmf0);
अटल DEVICE_ATTR_RO(dcmf1);
अटल DEVICE_ATTR_RO(dcmf2);
अटल DEVICE_ATTR_RO(dcmf3);
अटल DEVICE_ATTR_WO(reboot_image);
अटल DEVICE_ATTR_WO(notअगरy);

अटल काष्ठा attribute *rsu_attrs[] = अणु
	&dev_attr_current_image.attr,
	&dev_attr_fail_image.attr,
	&dev_attr_state.attr,
	&dev_attr_version.attr,
	&dev_attr_error_location.attr,
	&dev_attr_error_details.attr,
	&dev_attr_retry_counter.attr,
	&dev_attr_max_retry.attr,
	&dev_attr_dcmf0.attr,
	&dev_attr_dcmf1.attr,
	&dev_attr_dcmf2.attr,
	&dev_attr_dcmf3.attr,
	&dev_attr_reboot_image.attr,
	&dev_attr_notअगरy.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(rsu);

अटल पूर्णांक stratix10_rsu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा stratix10_rsu_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->client.dev = dev;
	priv->client.receive_cb = शून्य;
	priv->client.priv = priv;
	priv->status.current_image = 0;
	priv->status.fail_image = 0;
	priv->status.error_location = 0;
	priv->status.error_details = 0;
	priv->status.version = 0;
	priv->status.state = 0;
	priv->retry_counter = INVALID_RETRY_COUNTER;
	priv->dcmf_version.dcmf0 = INVALID_DCMF_VERSION;
	priv->dcmf_version.dcmf1 = INVALID_DCMF_VERSION;
	priv->dcmf_version.dcmf2 = INVALID_DCMF_VERSION;
	priv->dcmf_version.dcmf3 = INVALID_DCMF_VERSION;
	priv->max_retry = INVALID_RETRY_COUNTER;

	mutex_init(&priv->lock);
	priv->chan = stratix10_svc_request_channel_byname(&priv->client,
							  SVC_CLIENT_RSU);
	अगर (IS_ERR(priv->chan)) अणु
		dev_err(dev, "couldn't get service channel %s\n",
			SVC_CLIENT_RSU);
		वापस PTR_ERR(priv->chan);
	पूर्ण

	init_completion(&priv->completion);
	platक्रमm_set_drvdata(pdev, priv);

	/* get the initial state from firmware */
	ret = rsu_send_msg(priv, COMMAND_RSU_STATUS,
			   0, rsu_status_callback);
	अगर (ret) अणु
		dev_err(dev, "Error, getting RSU status %i\n", ret);
		stratix10_svc_मुक्त_channel(priv->chan);
	पूर्ण

	/* get DCMF version from firmware */
	ret = rsu_send_msg(priv, COMMAND_RSU_DCMF_VERSION,
			   0, rsu_dcmf_version_callback);
	अगर (ret) अणु
		dev_err(dev, "Error, getting DCMF version %i\n", ret);
		stratix10_svc_मुक्त_channel(priv->chan);
	पूर्ण

	ret = rsu_send_msg(priv, COMMAND_RSU_RETRY, 0, rsu_retry_callback);
	अगर (ret) अणु
		dev_err(dev, "Error, getting RSU retry %i\n", ret);
		stratix10_svc_मुक्त_channel(priv->chan);
	पूर्ण

	ret = rsu_send_msg(priv, COMMAND_RSU_MAX_RETRY, 0,
			   rsu_max_retry_callback);
	अगर (ret) अणु
		dev_err(dev, "Error, getting RSU max retry %i\n", ret);
		stratix10_svc_मुक्त_channel(priv->chan);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक stratix10_rsu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा stratix10_rsu_priv *priv = platक्रमm_get_drvdata(pdev);

	stratix10_svc_मुक्त_channel(priv->chan);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver stratix10_rsu_driver = अणु
	.probe = stratix10_rsu_probe,
	.हटाओ = stratix10_rsu_हटाओ,
	.driver = अणु
		.name = "stratix10-rsu",
		.dev_groups = rsu_groups,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(stratix10_rsu_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel Remote System Update Driver");
MODULE_AUTHOR("Richard Gong <richard.gong@intel.com>");
