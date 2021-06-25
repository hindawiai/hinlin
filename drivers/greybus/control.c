<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus CPort control protocol.
 *
 * Copyright 2015 Google Inc.
 * Copyright 2015 Linaro Ltd.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/greybus.h>

/* Highest control-protocol version supported */
#घोषणा GB_CONTROL_VERSION_MAJOR	0
#घोषणा GB_CONTROL_VERSION_MINOR	1

अटल पूर्णांक gb_control_get_version(काष्ठा gb_control *control)
अणु
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = control->connection->पूर्णांकf;
	काष्ठा gb_control_version_request request;
	काष्ठा gb_control_version_response response;
	पूर्णांक ret;

	request.major = GB_CONTROL_VERSION_MAJOR;
	request.minor = GB_CONTROL_VERSION_MINOR;

	ret = gb_operation_sync(control->connection,
				GB_CONTROL_TYPE_VERSION,
				&request, माप(request), &response,
				माप(response));
	अगर (ret) अणु
		dev_err(&पूर्णांकf->dev,
			"failed to get control-protocol version: %d\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (response.major > request.major) अणु
		dev_err(&पूर्णांकf->dev,
			"unsupported major control-protocol version (%u > %u)\n",
			response.major, request.major);
		वापस -ENOTSUPP;
	पूर्ण

	control->protocol_major = response.major;
	control->protocol_minor = response.minor;

	dev_dbg(&पूर्णांकf->dev, "%s - %u.%u\n", __func__, response.major,
		response.minor);

	वापस 0;
पूर्ण

अटल पूर्णांक gb_control_get_bundle_version(काष्ठा gb_control *control,
					 काष्ठा gb_bundle *bundle)
अणु
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = control->connection->पूर्णांकf;
	काष्ठा gb_control_bundle_version_request request;
	काष्ठा gb_control_bundle_version_response response;
	पूर्णांक ret;

	request.bundle_id = bundle->id;

	ret = gb_operation_sync(control->connection,
				GB_CONTROL_TYPE_BUNDLE_VERSION,
				&request, माप(request),
				&response, माप(response));
	अगर (ret) अणु
		dev_err(&पूर्णांकf->dev,
			"failed to get bundle %u class version: %d\n",
			bundle->id, ret);
		वापस ret;
	पूर्ण

	bundle->class_major = response.major;
	bundle->class_minor = response.minor;

	dev_dbg(&पूर्णांकf->dev, "%s - %u: %u.%u\n", __func__, bundle->id,
		response.major, response.minor);

	वापस 0;
पूर्ण

पूर्णांक gb_control_get_bundle_versions(काष्ठा gb_control *control)
अणु
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = control->connection->पूर्णांकf;
	काष्ठा gb_bundle *bundle;
	पूर्णांक ret;

	अगर (!control->has_bundle_version)
		वापस 0;

	list_क्रम_each_entry(bundle, &पूर्णांकf->bundles, links) अणु
		ret = gb_control_get_bundle_version(control, bundle);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* Get Manअगरest's size from the पूर्णांकerface */
पूर्णांक gb_control_get_manअगरest_size_operation(काष्ठा gb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा gb_control_get_manअगरest_size_response response;
	काष्ठा gb_connection *connection = पूर्णांकf->control->connection;
	पूर्णांक ret;

	ret = gb_operation_sync(connection, GB_CONTROL_TYPE_GET_MANIFEST_SIZE,
				शून्य, 0, &response, माप(response));
	अगर (ret) अणु
		dev_err(&connection->पूर्णांकf->dev,
			"failed to get manifest size: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस le16_to_cpu(response.size);
पूर्ण

/* Reads Manअगरest from the पूर्णांकerface */
पूर्णांक gb_control_get_manअगरest_operation(काष्ठा gb_पूर्णांकerface *पूर्णांकf, व्योम *manअगरest,
				      माप_प्रकार size)
अणु
	काष्ठा gb_connection *connection = पूर्णांकf->control->connection;

	वापस gb_operation_sync(connection, GB_CONTROL_TYPE_GET_MANIFEST,
				शून्य, 0, manअगरest, size);
पूर्ण

पूर्णांक gb_control_connected_operation(काष्ठा gb_control *control, u16 cport_id)
अणु
	काष्ठा gb_control_connected_request request;

	request.cport_id = cpu_to_le16(cport_id);
	वापस gb_operation_sync(control->connection, GB_CONTROL_TYPE_CONNECTED,
				 &request, माप(request), शून्य, 0);
पूर्ण

पूर्णांक gb_control_disconnected_operation(काष्ठा gb_control *control, u16 cport_id)
अणु
	काष्ठा gb_control_disconnected_request request;

	request.cport_id = cpu_to_le16(cport_id);
	वापस gb_operation_sync(control->connection,
				 GB_CONTROL_TYPE_DISCONNECTED, &request,
				 माप(request), शून्य, 0);
पूर्ण

पूर्णांक gb_control_disconnecting_operation(काष्ठा gb_control *control,
				       u16 cport_id)
अणु
	काष्ठा gb_control_disconnecting_request *request;
	काष्ठा gb_operation *operation;
	पूर्णांक ret;

	operation = gb_operation_create_core(control->connection,
					     GB_CONTROL_TYPE_DISCONNECTING,
					     माप(*request), 0, 0,
					     GFP_KERNEL);
	अगर (!operation)
		वापस -ENOMEM;

	request = operation->request->payload;
	request->cport_id = cpu_to_le16(cport_id);

	ret = gb_operation_request_send_sync(operation);
	अगर (ret) अणु
		dev_err(&control->dev, "failed to send disconnecting: %d\n",
			ret);
	पूर्ण

	gb_operation_put(operation);

	वापस ret;
पूर्ण

पूर्णांक gb_control_mode_चयन_operation(काष्ठा gb_control *control)
अणु
	काष्ठा gb_operation *operation;
	पूर्णांक ret;

	operation = gb_operation_create_core(control->connection,
					     GB_CONTROL_TYPE_MODE_SWITCH,
					     0, 0,
					     GB_OPERATION_FLAG_UNIसूचीECTIONAL,
					     GFP_KERNEL);
	अगर (!operation)
		वापस -ENOMEM;

	ret = gb_operation_request_send_sync(operation);
	अगर (ret)
		dev_err(&control->dev, "failed to send mode switch: %d\n", ret);

	gb_operation_put(operation);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_control_bundle_pm_status_map(u8 status)
अणु
	चयन (status) अणु
	हाल GB_CONTROL_BUNDLE_PM_INVAL:
		वापस -EINVAL;
	हाल GB_CONTROL_BUNDLE_PM_BUSY:
		वापस -EBUSY;
	हाल GB_CONTROL_BUNDLE_PM_NA:
		वापस -ENOMSG;
	हाल GB_CONTROL_BUNDLE_PM_FAIL:
	शेष:
		वापस -EREMOTEIO;
	पूर्ण
पूर्ण

पूर्णांक gb_control_bundle_suspend(काष्ठा gb_control *control, u8 bundle_id)
अणु
	काष्ठा gb_control_bundle_pm_request request;
	काष्ठा gb_control_bundle_pm_response response;
	पूर्णांक ret;

	request.bundle_id = bundle_id;
	ret = gb_operation_sync(control->connection,
				GB_CONTROL_TYPE_BUNDLE_SUSPEND, &request,
				माप(request), &response, माप(response));
	अगर (ret) अणु
		dev_err(&control->dev, "failed to send bundle %u suspend: %d\n",
			bundle_id, ret);
		वापस ret;
	पूर्ण

	अगर (response.status != GB_CONTROL_BUNDLE_PM_OK) अणु
		dev_err(&control->dev, "failed to suspend bundle %u: %d\n",
			bundle_id, response.status);
		वापस gb_control_bundle_pm_status_map(response.status);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक gb_control_bundle_resume(काष्ठा gb_control *control, u8 bundle_id)
अणु
	काष्ठा gb_control_bundle_pm_request request;
	काष्ठा gb_control_bundle_pm_response response;
	पूर्णांक ret;

	request.bundle_id = bundle_id;
	ret = gb_operation_sync(control->connection,
				GB_CONTROL_TYPE_BUNDLE_RESUME, &request,
				माप(request), &response, माप(response));
	अगर (ret) अणु
		dev_err(&control->dev, "failed to send bundle %u resume: %d\n",
			bundle_id, ret);
		वापस ret;
	पूर्ण

	अगर (response.status != GB_CONTROL_BUNDLE_PM_OK) अणु
		dev_err(&control->dev, "failed to resume bundle %u: %d\n",
			bundle_id, response.status);
		वापस gb_control_bundle_pm_status_map(response.status);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक gb_control_bundle_deactivate(काष्ठा gb_control *control, u8 bundle_id)
अणु
	काष्ठा gb_control_bundle_pm_request request;
	काष्ठा gb_control_bundle_pm_response response;
	पूर्णांक ret;

	request.bundle_id = bundle_id;
	ret = gb_operation_sync(control->connection,
				GB_CONTROL_TYPE_BUNDLE_DEACTIVATE, &request,
				माप(request), &response, माप(response));
	अगर (ret) अणु
		dev_err(&control->dev,
			"failed to send bundle %u deactivate: %d\n", bundle_id,
			ret);
		वापस ret;
	पूर्ण

	अगर (response.status != GB_CONTROL_BUNDLE_PM_OK) अणु
		dev_err(&control->dev, "failed to deactivate bundle %u: %d\n",
			bundle_id, response.status);
		वापस gb_control_bundle_pm_status_map(response.status);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक gb_control_bundle_activate(काष्ठा gb_control *control, u8 bundle_id)
अणु
	काष्ठा gb_control_bundle_pm_request request;
	काष्ठा gb_control_bundle_pm_response response;
	पूर्णांक ret;

	अगर (!control->has_bundle_activate)
		वापस 0;

	request.bundle_id = bundle_id;
	ret = gb_operation_sync(control->connection,
				GB_CONTROL_TYPE_BUNDLE_ACTIVATE, &request,
				माप(request), &response, माप(response));
	अगर (ret) अणु
		dev_err(&control->dev,
			"failed to send bundle %u activate: %d\n", bundle_id,
			ret);
		वापस ret;
	पूर्ण

	अगर (response.status != GB_CONTROL_BUNDLE_PM_OK) अणु
		dev_err(&control->dev, "failed to activate bundle %u: %d\n",
			bundle_id, response.status);
		वापस gb_control_bundle_pm_status_map(response.status);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gb_control_पूर्णांकerface_pm_status_map(u8 status)
अणु
	चयन (status) अणु
	हाल GB_CONTROL_INTF_PM_BUSY:
		वापस -EBUSY;
	हाल GB_CONTROL_INTF_PM_NA:
		वापस -ENOMSG;
	शेष:
		वापस -EREMOTEIO;
	पूर्ण
पूर्ण

पूर्णांक gb_control_पूर्णांकerface_suspend_prepare(काष्ठा gb_control *control)
अणु
	काष्ठा gb_control_पूर्णांकf_pm_response response;
	पूर्णांक ret;

	ret = gb_operation_sync(control->connection,
				GB_CONTROL_TYPE_INTF_SUSPEND_PREPARE, शून्य, 0,
				&response, माप(response));
	अगर (ret) अणु
		dev_err(&control->dev,
			"failed to send interface suspend prepare: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (response.status != GB_CONTROL_INTF_PM_OK) अणु
		dev_err(&control->dev, "interface error while preparing suspend: %d\n",
			response.status);
		वापस gb_control_पूर्णांकerface_pm_status_map(response.status);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक gb_control_पूर्णांकerface_deactivate_prepare(काष्ठा gb_control *control)
अणु
	काष्ठा gb_control_पूर्णांकf_pm_response response;
	पूर्णांक ret;

	ret = gb_operation_sync(control->connection,
				GB_CONTROL_TYPE_INTF_DEACTIVATE_PREPARE, शून्य,
				0, &response, माप(response));
	अगर (ret) अणु
		dev_err(&control->dev, "failed to send interface deactivate prepare: %d\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (response.status != GB_CONTROL_INTF_PM_OK) अणु
		dev_err(&control->dev, "interface error while preparing deactivate: %d\n",
			response.status);
		वापस gb_control_पूर्णांकerface_pm_status_map(response.status);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक gb_control_पूर्णांकerface_hibernate_पात(काष्ठा gb_control *control)
अणु
	काष्ठा gb_control_पूर्णांकf_pm_response response;
	पूर्णांक ret;

	ret = gb_operation_sync(control->connection,
				GB_CONTROL_TYPE_INTF_HIBERNATE_ABORT, शून्य, 0,
				&response, माप(response));
	अगर (ret) अणु
		dev_err(&control->dev,
			"failed to send interface aborting hibernate: %d\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (response.status != GB_CONTROL_INTF_PM_OK) अणु
		dev_err(&control->dev, "interface error while aborting hibernate: %d\n",
			response.status);
		वापस gb_control_पूर्णांकerface_pm_status_map(response.status);
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार venकरोr_string_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gb_control *control = to_gb_control(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", control->venकरोr_string);
पूर्ण
अटल DEVICE_ATTR_RO(venकरोr_string);

अटल sमाप_प्रकार product_string_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gb_control *control = to_gb_control(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", control->product_string);
पूर्ण
अटल DEVICE_ATTR_RO(product_string);

अटल काष्ठा attribute *control_attrs[] = अणु
	&dev_attr_venकरोr_string.attr,
	&dev_attr_product_string.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(control);

अटल व्योम gb_control_release(काष्ठा device *dev)
अणु
	काष्ठा gb_control *control = to_gb_control(dev);

	gb_connection_destroy(control->connection);

	kमुक्त(control->venकरोr_string);
	kमुक्त(control->product_string);

	kमुक्त(control);
पूर्ण

काष्ठा device_type greybus_control_type = अणु
	.name =		"greybus_control",
	.release =	gb_control_release,
पूर्ण;

काष्ठा gb_control *gb_control_create(काष्ठा gb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा gb_connection *connection;
	काष्ठा gb_control *control;

	control = kzalloc(माप(*control), GFP_KERNEL);
	अगर (!control)
		वापस ERR_PTR(-ENOMEM);

	control->पूर्णांकf = पूर्णांकf;

	connection = gb_connection_create_control(पूर्णांकf);
	अगर (IS_ERR(connection)) अणु
		dev_err(&पूर्णांकf->dev,
			"failed to create control connection: %ld\n",
			PTR_ERR(connection));
		kमुक्त(control);
		वापस ERR_CAST(connection);
	पूर्ण

	control->connection = connection;

	control->dev.parent = &पूर्णांकf->dev;
	control->dev.bus = &greybus_bus_type;
	control->dev.type = &greybus_control_type;
	control->dev.groups = control_groups;
	control->dev.dma_mask = पूर्णांकf->dev.dma_mask;
	device_initialize(&control->dev);
	dev_set_name(&control->dev, "%s.ctrl", dev_name(&पूर्णांकf->dev));

	gb_connection_set_data(control->connection, control);

	वापस control;
पूर्ण

पूर्णांक gb_control_enable(काष्ठा gb_control *control)
अणु
	पूर्णांक ret;

	dev_dbg(&control->connection->पूर्णांकf->dev, "%s\n", __func__);

	ret = gb_connection_enable_tx(control->connection);
	अगर (ret) अणु
		dev_err(&control->connection->पूर्णांकf->dev,
			"failed to enable control connection: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = gb_control_get_version(control);
	अगर (ret)
		जाओ err_disable_connection;

	अगर (control->protocol_major > 0 || control->protocol_minor > 1)
		control->has_bundle_version = true;

	/* FIXME: use protocol version instead */
	अगर (!(control->पूर्णांकf->quirks & GB_INTERFACE_QUIRK_NO_BUNDLE_ACTIVATE))
		control->has_bundle_activate = true;

	वापस 0;

err_disable_connection:
	gb_connection_disable(control->connection);

	वापस ret;
पूर्ण

व्योम gb_control_disable(काष्ठा gb_control *control)
अणु
	dev_dbg(&control->connection->पूर्णांकf->dev, "%s\n", __func__);

	अगर (control->पूर्णांकf->disconnected)
		gb_connection_disable_क्रमced(control->connection);
	अन्यथा
		gb_connection_disable(control->connection);
पूर्ण

पूर्णांक gb_control_suspend(काष्ठा gb_control *control)
अणु
	gb_connection_disable(control->connection);

	वापस 0;
पूर्ण

पूर्णांक gb_control_resume(काष्ठा gb_control *control)
अणु
	पूर्णांक ret;

	ret = gb_connection_enable_tx(control->connection);
	अगर (ret) अणु
		dev_err(&control->connection->पूर्णांकf->dev,
			"failed to enable control connection: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक gb_control_add(काष्ठा gb_control *control)
अणु
	पूर्णांक ret;

	ret = device_add(&control->dev);
	अगर (ret) अणु
		dev_err(&control->dev,
			"failed to register control device: %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम gb_control_del(काष्ठा gb_control *control)
अणु
	अगर (device_is_रेजिस्टरed(&control->dev))
		device_del(&control->dev);
पूर्ण

काष्ठा gb_control *gb_control_get(काष्ठा gb_control *control)
अणु
	get_device(&control->dev);

	वापस control;
पूर्ण

व्योम gb_control_put(काष्ठा gb_control *control)
अणु
	put_device(&control->dev);
पूर्ण

व्योम gb_control_mode_चयन_prepare(काष्ठा gb_control *control)
अणु
	gb_connection_mode_चयन_prepare(control->connection);
पूर्ण

व्योम gb_control_mode_चयन_complete(काष्ठा gb_control *control)
अणु
	gb_connection_mode_चयन_complete(control->connection);
पूर्ण
