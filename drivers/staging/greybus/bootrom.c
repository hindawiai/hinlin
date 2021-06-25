<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * BOOTROM Greybus driver.
 *
 * Copyright 2016 Google Inc.
 * Copyright 2016 Linaro Ltd.
 */

#समावेश <linux/firmware.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/greybus.h>

#समावेश "firmware.h"

/* Timeout, in jअगरfies, within which the next request must be received */
#घोषणा NEXT_REQ_TIMEOUT_MS	1000

/*
 * FIXME: Reduce this समयout once svc core handles parallel processing of
 * events from the SVC, which are handled sequentially today.
 */
#घोषणा MODE_SWITCH_TIMEOUT_MS	10000

क्रमागत next_request_type अणु
	NEXT_REQ_FIRMWARE_SIZE,
	NEXT_REQ_GET_FIRMWARE,
	NEXT_REQ_READY_TO_BOOT,
	NEXT_REQ_MODE_SWITCH,
पूर्ण;

काष्ठा gb_bootrom अणु
	काष्ठा gb_connection	*connection;
	स्थिर काष्ठा firmware	*fw;
	u8			protocol_major;
	u8			protocol_minor;
	क्रमागत next_request_type	next_request;
	काष्ठा delayed_work	dwork;
	काष्ठा mutex		mutex; /* Protects bootrom->fw */
पूर्ण;

अटल व्योम मुक्त_firmware(काष्ठा gb_bootrom *bootrom)
अणु
	अगर (!bootrom->fw)
		वापस;

	release_firmware(bootrom->fw);
	bootrom->fw = शून्य;
पूर्ण

अटल व्योम gb_bootrom_समयकरोut(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा gb_bootrom *bootrom = container_of(dwork,
						  काष्ठा gb_bootrom, dwork);
	काष्ठा device *dev = &bootrom->connection->bundle->dev;
	स्थिर अक्षर *reason;

	चयन (bootrom->next_request) अणु
	हाल NEXT_REQ_FIRMWARE_SIZE:
		reason = "Firmware Size Request";
		अवरोध;
	हाल NEXT_REQ_GET_FIRMWARE:
		reason = "Get Firmware Request";
		अवरोध;
	हाल NEXT_REQ_READY_TO_BOOT:
		reason = "Ready to Boot Request";
		अवरोध;
	हाल NEXT_REQ_MODE_SWITCH:
		reason = "Interface Mode Switch";
		अवरोध;
	शेष:
		reason = शून्य;
		dev_err(dev, "Invalid next-request: %u", bootrom->next_request);
		अवरोध;
	पूर्ण

	dev_err(dev, "Timed out waiting for %s from the Module\n", reason);

	mutex_lock(&bootrom->mutex);
	मुक्त_firmware(bootrom);
	mutex_unlock(&bootrom->mutex);

	/* TODO: Power-off Module ? */
पूर्ण

अटल व्योम gb_bootrom_set_समयout(काष्ठा gb_bootrom *bootrom,
				   क्रमागत next_request_type next,
				   अचिन्हित दीर्घ समयout)
अणु
	bootrom->next_request = next;
	schedule_delayed_work(&bootrom->dwork, msecs_to_jअगरfies(समयout));
पूर्ण

अटल व्योम gb_bootrom_cancel_समयout(काष्ठा gb_bootrom *bootrom)
अणु
	cancel_delayed_work_sync(&bootrom->dwork);
पूर्ण

/*
 * The es2 chip करोesn't have VID/PID programmed पूर्णांकo the hardware and we need to
 * hack that up to distinguish dअगरferent modules and their firmware blobs.
 *
 * This fetches VID/PID (over bootrom protocol) क्रम es2 chip only, when VID/PID
 * alपढ़ोy sent during hotplug are 0.
 *
 * Otherwise, we keep पूर्णांकf->venकरोr_id/product_id same as what's passed
 * during hotplug.
 */
अटल व्योम bootrom_es2_fixup_vid_pid(काष्ठा gb_bootrom *bootrom)
अणु
	काष्ठा gb_bootrom_get_vid_pid_response response;
	काष्ठा gb_connection *connection = bootrom->connection;
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = connection->bundle->पूर्णांकf;
	पूर्णांक ret;

	अगर (!(पूर्णांकf->quirks & GB_INTERFACE_QUIRK_NO_GMP_IDS))
		वापस;

	ret = gb_operation_sync(connection, GB_BOOTROM_TYPE_GET_VID_PID,
				शून्य, 0, &response, माप(response));
	अगर (ret) अणु
		dev_err(&connection->bundle->dev,
			"Bootrom get vid/pid operation failed (%d)\n", ret);
		वापस;
	पूर्ण

	/*
	 * NOTE: This is hacked, so that the same values of VID/PID can be used
	 * by next firmware level as well. The uevent क्रम bootrom will still
	 * have VID/PID as 0, though after this poपूर्णांक the sysfs files will start
	 * showing the updated values. But yeah, that's a bit racy as the same
	 * sysfs files would be showing 0 beक्रमe this poपूर्णांक.
	 */
	पूर्णांकf->venकरोr_id = le32_to_cpu(response.venकरोr_id);
	पूर्णांकf->product_id = le32_to_cpu(response.product_id);

	dev_dbg(&connection->bundle->dev, "Bootrom got vid (0x%x)/pid (0x%x)\n",
		पूर्णांकf->venकरोr_id, पूर्णांकf->product_id);
पूर्ण

/* This वापसs path of the firmware blob on the disk */
अटल पूर्णांक find_firmware(काष्ठा gb_bootrom *bootrom, u8 stage)
अणु
	काष्ठा gb_connection *connection = bootrom->connection;
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = connection->bundle->पूर्णांकf;
	अक्षर firmware_name[49];
	पूर्णांक rc;

	/* Alपढ़ोy have a firmware, मुक्त it */
	मुक्त_firmware(bootrom);

	/* Bootrom protocol is only supported क्रम loading Stage 2 firmware */
	अगर (stage != 2) अणु
		dev_err(&connection->bundle->dev, "Invalid boot stage: %u\n",
			stage);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Create firmware name
	 *
	 * XXX Name it properly..
	 */
	snम_लिखो(firmware_name, माप(firmware_name),
		 FW_NAME_PREFIX "%08x_%08x_%08x_%08x_s2l.tftf",
		 पूर्णांकf->ddbl1_manufacturer_id, पूर्णांकf->ddbl1_product_id,
		 पूर्णांकf->venकरोr_id, पूर्णांकf->product_id);

	// FIXME:
	// Turn to dev_dbg later after everyone has valid bootloaders with good
	// ids, but leave this as dev_info क्रम now to make it easier to track
	// करोwn "empty" vid/pid modules.
	dev_info(&connection->bundle->dev, "Firmware file '%s' requested\n",
		 firmware_name);

	rc = request_firmware(&bootrom->fw, firmware_name,
			      &connection->bundle->dev);
	अगर (rc) अणु
		dev_err(&connection->bundle->dev,
			"failed to find %s firmware (%d)\n", firmware_name, rc);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक gb_bootrom_firmware_size_request(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_bootrom *bootrom = gb_connection_get_data(op->connection);
	काष्ठा gb_bootrom_firmware_size_request *size_request =
		op->request->payload;
	काष्ठा gb_bootrom_firmware_size_response *size_response;
	काष्ठा device *dev = &op->connection->bundle->dev;
	पूर्णांक ret;

	/* Disable समयouts */
	gb_bootrom_cancel_समयout(bootrom);

	अगर (op->request->payload_size != माप(*size_request)) अणु
		dev_err(dev, "%s: illegal size of firmware size request (%zu != %zu)\n",
			__func__, op->request->payload_size,
			माप(*size_request));
		ret = -EINVAL;
		जाओ queue_work;
	पूर्ण

	mutex_lock(&bootrom->mutex);

	ret = find_firmware(bootrom, size_request->stage);
	अगर (ret)
		जाओ unlock;

	अगर (!gb_operation_response_alloc(op, माप(*size_response),
					 GFP_KERNEL)) अणु
		dev_err(dev, "%s: error allocating response\n", __func__);
		मुक्त_firmware(bootrom);
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण

	size_response = op->response->payload;
	size_response->size = cpu_to_le32(bootrom->fw->size);

	dev_dbg(dev, "%s: firmware size %d bytes\n",
		__func__, size_response->size);

unlock:
	mutex_unlock(&bootrom->mutex);

queue_work:
	अगर (!ret) अणु
		/* Refresh समयout */
		gb_bootrom_set_समयout(bootrom, NEXT_REQ_GET_FIRMWARE,
				       NEXT_REQ_TIMEOUT_MS);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक gb_bootrom_get_firmware(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_bootrom *bootrom = gb_connection_get_data(op->connection);
	स्थिर काष्ठा firmware *fw;
	काष्ठा gb_bootrom_get_firmware_request *firmware_request;
	काष्ठा gb_bootrom_get_firmware_response *firmware_response;
	काष्ठा device *dev = &op->connection->bundle->dev;
	अचिन्हित पूर्णांक offset, size;
	क्रमागत next_request_type next_request;
	पूर्णांक ret = 0;

	/* Disable समयouts */
	gb_bootrom_cancel_समयout(bootrom);

	अगर (op->request->payload_size != माप(*firmware_request)) अणु
		dev_err(dev, "%s: Illegal size of get firmware request (%zu %zu)\n",
			__func__, op->request->payload_size,
			माप(*firmware_request));
		ret = -EINVAL;
		जाओ queue_work;
	पूर्ण

	mutex_lock(&bootrom->mutex);

	fw = bootrom->fw;
	अगर (!fw) अणु
		dev_err(dev, "%s: firmware not available\n", __func__);
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	firmware_request = op->request->payload;
	offset = le32_to_cpu(firmware_request->offset);
	size = le32_to_cpu(firmware_request->size);

	अगर (offset >= fw->size || size > fw->size - offset) अणु
		dev_warn(dev, "bad firmware request (offs = %u, size = %u)\n",
			 offset, size);
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	अगर (!gb_operation_response_alloc(op, माप(*firmware_response) + size,
					 GFP_KERNEL)) अणु
		dev_err(dev, "%s: error allocating response\n", __func__);
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण

	firmware_response = op->response->payload;
	स_नकल(firmware_response->data, fw->data + offset, size);

	dev_dbg(dev, "responding with firmware (offs = %u, size = %u)\n",
		offset, size);

unlock:
	mutex_unlock(&bootrom->mutex);

queue_work:
	/* Refresh समयout */
	अगर (!ret && (offset + size == fw->size))
		next_request = NEXT_REQ_READY_TO_BOOT;
	अन्यथा
		next_request = NEXT_REQ_GET_FIRMWARE;

	gb_bootrom_set_समयout(bootrom, next_request, NEXT_REQ_TIMEOUT_MS);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_bootrom_पढ़ोy_to_boot(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_connection *connection = op->connection;
	काष्ठा gb_bootrom *bootrom = gb_connection_get_data(connection);
	काष्ठा gb_bootrom_पढ़ोy_to_boot_request *rtb_request;
	काष्ठा device *dev = &connection->bundle->dev;
	u8 status;
	पूर्णांक ret = 0;

	/* Disable समयouts */
	gb_bootrom_cancel_समयout(bootrom);

	अगर (op->request->payload_size != माप(*rtb_request)) अणु
		dev_err(dev, "%s: Illegal size of ready to boot request (%zu %zu)\n",
			__func__, op->request->payload_size,
			माप(*rtb_request));
		ret = -EINVAL;
		जाओ queue_work;
	पूर्ण

	rtb_request = op->request->payload;
	status = rtb_request->status;

	/* Return error अगर the blob was invalid */
	अगर (status == GB_BOOTROM_BOOT_STATUS_INVALID) अणु
		ret = -EINVAL;
		जाओ queue_work;
	पूर्ण

	/*
	 * XXX Should we वापस error क्रम insecure firmware?
	 */
	dev_dbg(dev, "ready to boot: 0x%x, 0\n", status);

queue_work:
	/*
	 * Refresh समयout, the Interface shall load the new personality and
	 * send a new hotplug request, which shall get rid of the bootrom
	 * connection. As that can take some समय, increase the समयout a bit.
	 */
	gb_bootrom_set_समयout(bootrom, NEXT_REQ_MODE_SWITCH,
			       MODE_SWITCH_TIMEOUT_MS);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_bootrom_request_handler(काष्ठा gb_operation *op)
अणु
	u8 type = op->type;

	चयन (type) अणु
	हाल GB_BOOTROM_TYPE_FIRMWARE_SIZE:
		वापस gb_bootrom_firmware_size_request(op);
	हाल GB_BOOTROM_TYPE_GET_FIRMWARE:
		वापस gb_bootrom_get_firmware(op);
	हाल GB_BOOTROM_TYPE_READY_TO_BOOT:
		वापस gb_bootrom_पढ़ोy_to_boot(op);
	शेष:
		dev_err(&op->connection->bundle->dev,
			"unsupported request: %u\n", type);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक gb_bootrom_get_version(काष्ठा gb_bootrom *bootrom)
अणु
	काष्ठा gb_bundle *bundle = bootrom->connection->bundle;
	काष्ठा gb_bootrom_version_request request;
	काष्ठा gb_bootrom_version_response response;
	पूर्णांक ret;

	request.major = GB_BOOTROM_VERSION_MAJOR;
	request.minor = GB_BOOTROM_VERSION_MINOR;

	ret = gb_operation_sync(bootrom->connection,
				GB_BOOTROM_TYPE_VERSION,
				&request, माप(request), &response,
				माप(response));
	अगर (ret) अणु
		dev_err(&bundle->dev,
			"failed to get protocol version: %d\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (response.major > request.major) अणु
		dev_err(&bundle->dev,
			"unsupported major protocol version (%u > %u)\n",
			response.major, request.major);
		वापस -ENOTSUPP;
	पूर्ण

	bootrom->protocol_major = response.major;
	bootrom->protocol_minor = response.minor;

	dev_dbg(&bundle->dev, "%s - %u.%u\n", __func__, response.major,
		response.minor);

	वापस 0;
पूर्ण

अटल पूर्णांक gb_bootrom_probe(काष्ठा gb_bundle *bundle,
			    स्थिर काष्ठा greybus_bundle_id *id)
अणु
	काष्ठा greybus_descriptor_cport *cport_desc;
	काष्ठा gb_connection *connection;
	काष्ठा gb_bootrom *bootrom;
	पूर्णांक ret;

	अगर (bundle->num_cports != 1)
		वापस -ENODEV;

	cport_desc = &bundle->cport_desc[0];
	अगर (cport_desc->protocol_id != GREYBUS_PROTOCOL_BOOTROM)
		वापस -ENODEV;

	bootrom = kzalloc(माप(*bootrom), GFP_KERNEL);
	अगर (!bootrom)
		वापस -ENOMEM;

	connection = gb_connection_create(bundle,
					  le16_to_cpu(cport_desc->id),
					  gb_bootrom_request_handler);
	अगर (IS_ERR(connection)) अणु
		ret = PTR_ERR(connection);
		जाओ err_मुक्त_bootrom;
	पूर्ण

	gb_connection_set_data(connection, bootrom);

	bootrom->connection = connection;

	mutex_init(&bootrom->mutex);
	INIT_DELAYED_WORK(&bootrom->dwork, gb_bootrom_समयकरोut);
	greybus_set_drvdata(bundle, bootrom);

	ret = gb_connection_enable_tx(connection);
	अगर (ret)
		जाओ err_connection_destroy;

	ret = gb_bootrom_get_version(bootrom);
	अगर (ret)
		जाओ err_connection_disable;

	bootrom_es2_fixup_vid_pid(bootrom);

	ret = gb_connection_enable(connection);
	अगर (ret)
		जाओ err_connection_disable;

	/* Refresh समयout */
	gb_bootrom_set_समयout(bootrom, NEXT_REQ_FIRMWARE_SIZE,
			       NEXT_REQ_TIMEOUT_MS);

	/* Tell bootrom we're पढ़ोy. */
	ret = gb_operation_sync(connection, GB_BOOTROM_TYPE_AP_READY, शून्य, 0,
				शून्य, 0);
	अगर (ret) अणु
		dev_err(&connection->bundle->dev,
			"failed to send AP READY: %d\n", ret);
		जाओ err_cancel_समयout;
	पूर्ण

	dev_dbg(&bundle->dev, "AP_READY sent\n");

	वापस 0;

err_cancel_समयout:
	gb_bootrom_cancel_समयout(bootrom);
err_connection_disable:
	gb_connection_disable(connection);
err_connection_destroy:
	gb_connection_destroy(connection);
err_मुक्त_bootrom:
	kमुक्त(bootrom);

	वापस ret;
पूर्ण

अटल व्योम gb_bootrom_disconnect(काष्ठा gb_bundle *bundle)
अणु
	काष्ठा gb_bootrom *bootrom = greybus_get_drvdata(bundle);

	dev_dbg(&bundle->dev, "%s\n", __func__);

	gb_connection_disable(bootrom->connection);

	/* Disable समयouts */
	gb_bootrom_cancel_समयout(bootrom);

	/*
	 * Release firmware:
	 *
	 * As the connection and the delayed work are alपढ़ोy disabled, we करोn't
	 * need to lock access to bootrom->fw here.
	 */
	मुक्त_firmware(bootrom);

	gb_connection_destroy(bootrom->connection);
	kमुक्त(bootrom);
पूर्ण

अटल स्थिर काष्ठा greybus_bundle_id gb_bootrom_id_table[] = अणु
	अणु GREYBUS_DEVICE_CLASS(GREYBUS_CLASS_BOOTROM) पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा greybus_driver gb_bootrom_driver = अणु
	.name		= "bootrom",
	.probe		= gb_bootrom_probe,
	.disconnect	= gb_bootrom_disconnect,
	.id_table	= gb_bootrom_id_table,
पूर्ण;

module_greybus_driver(gb_bootrom_driver);

MODULE_LICENSE("GPL v2");
