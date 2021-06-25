<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SVC Greybus driver.
 *
 * Copyright 2015 Google Inc.
 * Copyright 2015 Linaro Ltd.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/greybus.h>

#घोषणा SVC_INTF_EJECT_TIMEOUT		9000
#घोषणा SVC_INTF_ACTIVATE_TIMEOUT	6000
#घोषणा SVC_INTF_RESUME_TIMEOUT		3000

काष्ठा gb_svc_deferred_request अणु
	काष्ठा work_काष्ठा work;
	काष्ठा gb_operation *operation;
पूर्ण;

अटल पूर्णांक gb_svc_queue_deferred_request(काष्ठा gb_operation *operation);

अटल sमाप_प्रकार enकरो_id_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gb_svc *svc = to_gb_svc(dev);

	वापस प्र_लिखो(buf, "0x%04x\n", svc->enकरो_id);
पूर्ण
अटल DEVICE_ATTR_RO(enकरो_id);

अटल sमाप_प्रकार ap_पूर्णांकf_id_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gb_svc *svc = to_gb_svc(dev);

	वापस प्र_लिखो(buf, "%u\n", svc->ap_पूर्णांकf_id);
पूर्ण
अटल DEVICE_ATTR_RO(ap_पूर्णांकf_id);

// FIXME
// This is a hack, we need to करो this "right" and clean the पूर्णांकerface up
// properly, not just क्रमcibly yank the thing out of the प्रणाली and hope क्रम the
// best.  But क्रम now, people want their modules to come out without having to
// throw the thing to the ground or get out a screwdriver.
अटल sमाप_प्रकार पूर्णांकf_eject_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				माप_प्रकार len)
अणु
	काष्ठा gb_svc *svc = to_gb_svc(dev);
	अचिन्हित लघु पूर्णांकf_id;
	पूर्णांक ret;

	ret = kstrtou16(buf, 10, &पूर्णांकf_id);
	अगर (ret < 0)
		वापस ret;

	dev_warn(dev, "Forcibly trying to eject interface %d\n", पूर्णांकf_id);

	ret = gb_svc_पूर्णांकf_eject(svc, पूर्णांकf_id);
	अगर (ret < 0)
		वापस ret;

	वापस len;
पूर्ण
अटल DEVICE_ATTR_WO(पूर्णांकf_eject);

अटल sमाप_प्रकार watchकरोg_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा gb_svc *svc = to_gb_svc(dev);

	वापस प्र_लिखो(buf, "%s\n",
		       gb_svc_watchकरोg_enabled(svc) ? "enabled" : "disabled");
पूर्ण

अटल sमाप_प्रकार watchकरोg_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार len)
अणु
	काष्ठा gb_svc *svc = to_gb_svc(dev);
	पूर्णांक retval;
	bool user_request;

	retval = strtobool(buf, &user_request);
	अगर (retval)
		वापस retval;

	अगर (user_request)
		retval = gb_svc_watchकरोg_enable(svc);
	अन्यथा
		retval = gb_svc_watchकरोg_disable(svc);
	अगर (retval)
		वापस retval;
	वापस len;
पूर्ण
अटल DEVICE_ATTR_RW(watchकरोg);

अटल sमाप_प्रकार watchकरोg_action_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gb_svc *svc = to_gb_svc(dev);

	अगर (svc->action == GB_SVC_WATCHDOG_BITE_PANIC_KERNEL)
		वापस प्र_लिखो(buf, "panic\n");
	अन्यथा अगर (svc->action == GB_SVC_WATCHDOG_BITE_RESET_UNIPRO)
		वापस प्र_लिखो(buf, "reset\n");

	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार watchकरोg_action_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा gb_svc *svc = to_gb_svc(dev);

	अगर (sysfs_streq(buf, "panic"))
		svc->action = GB_SVC_WATCHDOG_BITE_PANIC_KERNEL;
	अन्यथा अगर (sysfs_streq(buf, "reset"))
		svc->action = GB_SVC_WATCHDOG_BITE_RESET_UNIPRO;
	अन्यथा
		वापस -EINVAL;

	वापस len;
पूर्ण
अटल DEVICE_ATTR_RW(watchकरोg_action);

अटल पूर्णांक gb_svc_pwrmon_rail_count_get(काष्ठा gb_svc *svc, u8 *value)
अणु
	काष्ठा gb_svc_pwrmon_rail_count_get_response response;
	पूर्णांक ret;

	ret = gb_operation_sync(svc->connection,
				GB_SVC_TYPE_PWRMON_RAIL_COUNT_GET, शून्य, 0,
				&response, माप(response));
	अगर (ret) अणु
		dev_err(&svc->dev, "failed to get rail count: %d\n", ret);
		वापस ret;
	पूर्ण

	*value = response.rail_count;

	वापस 0;
पूर्ण

अटल पूर्णांक gb_svc_pwrmon_rail_names_get(काष्ठा gb_svc *svc,
		काष्ठा gb_svc_pwrmon_rail_names_get_response *response,
		माप_प्रकार bufsize)
अणु
	पूर्णांक ret;

	ret = gb_operation_sync(svc->connection,
				GB_SVC_TYPE_PWRMON_RAIL_NAMES_GET, शून्य, 0,
				response, bufsize);
	अगर (ret) अणु
		dev_err(&svc->dev, "failed to get rail names: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (response->status != GB_SVC_OP_SUCCESS) अणु
		dev_err(&svc->dev,
			"SVC error while getting rail names: %u\n",
			response->status);
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gb_svc_pwrmon_sample_get(काष्ठा gb_svc *svc, u8 rail_id,
				    u8 measurement_type, u32 *value)
अणु
	काष्ठा gb_svc_pwrmon_sample_get_request request;
	काष्ठा gb_svc_pwrmon_sample_get_response response;
	पूर्णांक ret;

	request.rail_id = rail_id;
	request.measurement_type = measurement_type;

	ret = gb_operation_sync(svc->connection, GB_SVC_TYPE_PWRMON_SAMPLE_GET,
				&request, माप(request),
				&response, माप(response));
	अगर (ret) अणु
		dev_err(&svc->dev, "failed to get rail sample: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (response.result) अणु
		dev_err(&svc->dev,
			"UniPro error while getting rail power sample (%d %d): %d\n",
			rail_id, measurement_type, response.result);
		चयन (response.result) अणु
		हाल GB_SVC_PWRMON_GET_SAMPLE_INVAL:
			वापस -EINVAL;
		हाल GB_SVC_PWRMON_GET_SAMPLE_NOSUPP:
			वापस -ENOMSG;
		शेष:
			वापस -EREMOTEIO;
		पूर्ण
	पूर्ण

	*value = le32_to_cpu(response.measurement);

	वापस 0;
पूर्ण

पूर्णांक gb_svc_pwrmon_पूर्णांकf_sample_get(काष्ठा gb_svc *svc, u8 पूर्णांकf_id,
				  u8 measurement_type, u32 *value)
अणु
	काष्ठा gb_svc_pwrmon_पूर्णांकf_sample_get_request request;
	काष्ठा gb_svc_pwrmon_पूर्णांकf_sample_get_response response;
	पूर्णांक ret;

	request.पूर्णांकf_id = पूर्णांकf_id;
	request.measurement_type = measurement_type;

	ret = gb_operation_sync(svc->connection,
				GB_SVC_TYPE_PWRMON_INTF_SAMPLE_GET,
				&request, माप(request),
				&response, माप(response));
	अगर (ret) अणु
		dev_err(&svc->dev, "failed to get intf sample: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (response.result) अणु
		dev_err(&svc->dev,
			"UniPro error while getting intf power sample (%d %d): %d\n",
			पूर्णांकf_id, measurement_type, response.result);
		चयन (response.result) अणु
		हाल GB_SVC_PWRMON_GET_SAMPLE_INVAL:
			वापस -EINVAL;
		हाल GB_SVC_PWRMON_GET_SAMPLE_NOSUPP:
			वापस -ENOMSG;
		शेष:
			वापस -EREMOTEIO;
		पूर्ण
	पूर्ण

	*value = le32_to_cpu(response.measurement);

	वापस 0;
पूर्ण

अटल काष्ठा attribute *svc_attrs[] = अणु
	&dev_attr_enकरो_id.attr,
	&dev_attr_ap_पूर्णांकf_id.attr,
	&dev_attr_पूर्णांकf_eject.attr,
	&dev_attr_watchकरोg.attr,
	&dev_attr_watchकरोg_action.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(svc);

पूर्णांक gb_svc_पूर्णांकf_device_id(काष्ठा gb_svc *svc, u8 पूर्णांकf_id, u8 device_id)
अणु
	काष्ठा gb_svc_पूर्णांकf_device_id_request request;

	request.पूर्णांकf_id = पूर्णांकf_id;
	request.device_id = device_id;

	वापस gb_operation_sync(svc->connection, GB_SVC_TYPE_INTF_DEVICE_ID,
				 &request, माप(request), शून्य, 0);
पूर्ण

पूर्णांक gb_svc_पूर्णांकf_eject(काष्ठा gb_svc *svc, u8 पूर्णांकf_id)
अणु
	काष्ठा gb_svc_पूर्णांकf_eject_request request;
	पूर्णांक ret;

	request.पूर्णांकf_id = पूर्णांकf_id;

	/*
	 * The pulse width क्रम module release in svc is दीर्घ so we need to
	 * increase the समयout so the operation will not वापस to soon.
	 */
	ret = gb_operation_sync_समयout(svc->connection,
					GB_SVC_TYPE_INTF_EJECT, &request,
					माप(request), शून्य, 0,
					SVC_INTF_EJECT_TIMEOUT);
	अगर (ret) अणु
		dev_err(&svc->dev, "failed to eject interface %u\n", पूर्णांकf_id);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक gb_svc_पूर्णांकf_vsys_set(काष्ठा gb_svc *svc, u8 पूर्णांकf_id, bool enable)
अणु
	काष्ठा gb_svc_पूर्णांकf_vsys_request request;
	काष्ठा gb_svc_पूर्णांकf_vsys_response response;
	पूर्णांक type, ret;

	request.पूर्णांकf_id = पूर्णांकf_id;

	अगर (enable)
		type = GB_SVC_TYPE_INTF_VSYS_ENABLE;
	अन्यथा
		type = GB_SVC_TYPE_INTF_VSYS_DISABLE;

	ret = gb_operation_sync(svc->connection, type,
				&request, माप(request),
				&response, माप(response));
	अगर (ret < 0)
		वापस ret;
	अगर (response.result_code != GB_SVC_INTF_VSYS_OK)
		वापस -EREMOTEIO;
	वापस 0;
पूर्ण

पूर्णांक gb_svc_पूर्णांकf_refclk_set(काष्ठा gb_svc *svc, u8 पूर्णांकf_id, bool enable)
अणु
	काष्ठा gb_svc_पूर्णांकf_refclk_request request;
	काष्ठा gb_svc_पूर्णांकf_refclk_response response;
	पूर्णांक type, ret;

	request.पूर्णांकf_id = पूर्णांकf_id;

	अगर (enable)
		type = GB_SVC_TYPE_INTF_REFCLK_ENABLE;
	अन्यथा
		type = GB_SVC_TYPE_INTF_REFCLK_DISABLE;

	ret = gb_operation_sync(svc->connection, type,
				&request, माप(request),
				&response, माप(response));
	अगर (ret < 0)
		वापस ret;
	अगर (response.result_code != GB_SVC_INTF_REFCLK_OK)
		वापस -EREMOTEIO;
	वापस 0;
पूर्ण

पूर्णांक gb_svc_पूर्णांकf_unipro_set(काष्ठा gb_svc *svc, u8 पूर्णांकf_id, bool enable)
अणु
	काष्ठा gb_svc_पूर्णांकf_unipro_request request;
	काष्ठा gb_svc_पूर्णांकf_unipro_response response;
	पूर्णांक type, ret;

	request.पूर्णांकf_id = पूर्णांकf_id;

	अगर (enable)
		type = GB_SVC_TYPE_INTF_UNIPRO_ENABLE;
	अन्यथा
		type = GB_SVC_TYPE_INTF_UNIPRO_DISABLE;

	ret = gb_operation_sync(svc->connection, type,
				&request, माप(request),
				&response, माप(response));
	अगर (ret < 0)
		वापस ret;
	अगर (response.result_code != GB_SVC_INTF_UNIPRO_OK)
		वापस -EREMOTEIO;
	वापस 0;
पूर्ण

पूर्णांक gb_svc_पूर्णांकf_activate(काष्ठा gb_svc *svc, u8 पूर्णांकf_id, u8 *पूर्णांकf_type)
अणु
	काष्ठा gb_svc_पूर्णांकf_activate_request request;
	काष्ठा gb_svc_पूर्णांकf_activate_response response;
	पूर्णांक ret;

	request.पूर्णांकf_id = पूर्णांकf_id;

	ret = gb_operation_sync_समयout(svc->connection,
					GB_SVC_TYPE_INTF_ACTIVATE,
					&request, माप(request),
					&response, माप(response),
					SVC_INTF_ACTIVATE_TIMEOUT);
	अगर (ret < 0)
		वापस ret;
	अगर (response.status != GB_SVC_OP_SUCCESS) अणु
		dev_err(&svc->dev, "failed to activate interface %u: %u\n",
			पूर्णांकf_id, response.status);
		वापस -EREMOTEIO;
	पूर्ण

	*पूर्णांकf_type = response.पूर्णांकf_type;

	वापस 0;
पूर्ण

पूर्णांक gb_svc_पूर्णांकf_resume(काष्ठा gb_svc *svc, u8 पूर्णांकf_id)
अणु
	काष्ठा gb_svc_पूर्णांकf_resume_request request;
	काष्ठा gb_svc_पूर्णांकf_resume_response response;
	पूर्णांक ret;

	request.पूर्णांकf_id = पूर्णांकf_id;

	ret = gb_operation_sync_समयout(svc->connection,
					GB_SVC_TYPE_INTF_RESUME,
					&request, माप(request),
					&response, माप(response),
					SVC_INTF_RESUME_TIMEOUT);
	अगर (ret < 0) अणु
		dev_err(&svc->dev, "failed to send interface resume %u: %d\n",
			पूर्णांकf_id, ret);
		वापस ret;
	पूर्ण

	अगर (response.status != GB_SVC_OP_SUCCESS) अणु
		dev_err(&svc->dev, "failed to resume interface %u: %u\n",
			पूर्णांकf_id, response.status);
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक gb_svc_dme_peer_get(काष्ठा gb_svc *svc, u8 पूर्णांकf_id, u16 attr, u16 selector,
			u32 *value)
अणु
	काष्ठा gb_svc_dme_peer_get_request request;
	काष्ठा gb_svc_dme_peer_get_response response;
	u16 result;
	पूर्णांक ret;

	request.पूर्णांकf_id = पूर्णांकf_id;
	request.attr = cpu_to_le16(attr);
	request.selector = cpu_to_le16(selector);

	ret = gb_operation_sync(svc->connection, GB_SVC_TYPE_DME_PEER_GET,
				&request, माप(request),
				&response, माप(response));
	अगर (ret) अणु
		dev_err(&svc->dev, "failed to get DME attribute (%u 0x%04x %u): %d\n",
			पूर्णांकf_id, attr, selector, ret);
		वापस ret;
	पूर्ण

	result = le16_to_cpu(response.result_code);
	अगर (result) अणु
		dev_err(&svc->dev, "UniPro error while getting DME attribute (%u 0x%04x %u): %u\n",
			पूर्णांकf_id, attr, selector, result);
		वापस -EREMOTEIO;
	पूर्ण

	अगर (value)
		*value = le32_to_cpu(response.attr_value);

	वापस 0;
पूर्ण

पूर्णांक gb_svc_dme_peer_set(काष्ठा gb_svc *svc, u8 पूर्णांकf_id, u16 attr, u16 selector,
			u32 value)
अणु
	काष्ठा gb_svc_dme_peer_set_request request;
	काष्ठा gb_svc_dme_peer_set_response response;
	u16 result;
	पूर्णांक ret;

	request.पूर्णांकf_id = पूर्णांकf_id;
	request.attr = cpu_to_le16(attr);
	request.selector = cpu_to_le16(selector);
	request.value = cpu_to_le32(value);

	ret = gb_operation_sync(svc->connection, GB_SVC_TYPE_DME_PEER_SET,
				&request, माप(request),
				&response, माप(response));
	अगर (ret) अणु
		dev_err(&svc->dev, "failed to set DME attribute (%u 0x%04x %u %u): %d\n",
			पूर्णांकf_id, attr, selector, value, ret);
		वापस ret;
	पूर्ण

	result = le16_to_cpu(response.result_code);
	अगर (result) अणु
		dev_err(&svc->dev, "UniPro error while setting DME attribute (%u 0x%04x %u %u): %u\n",
			पूर्णांकf_id, attr, selector, value, result);
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक gb_svc_connection_create(काष्ठा gb_svc *svc,
			     u8 पूर्णांकf1_id, u16 cport1_id,
			     u8 पूर्णांकf2_id, u16 cport2_id,
			     u8 cport_flags)
अणु
	काष्ठा gb_svc_conn_create_request request;

	request.पूर्णांकf1_id = पूर्णांकf1_id;
	request.cport1_id = cpu_to_le16(cport1_id);
	request.पूर्णांकf2_id = पूर्णांकf2_id;
	request.cport2_id = cpu_to_le16(cport2_id);
	request.tc = 0;		/* TC0 */
	request.flags = cport_flags;

	वापस gb_operation_sync(svc->connection, GB_SVC_TYPE_CONN_CREATE,
				 &request, माप(request), शून्य, 0);
पूर्ण

व्योम gb_svc_connection_destroy(काष्ठा gb_svc *svc, u8 पूर्णांकf1_id, u16 cport1_id,
			       u8 पूर्णांकf2_id, u16 cport2_id)
अणु
	काष्ठा gb_svc_conn_destroy_request request;
	काष्ठा gb_connection *connection = svc->connection;
	पूर्णांक ret;

	request.पूर्णांकf1_id = पूर्णांकf1_id;
	request.cport1_id = cpu_to_le16(cport1_id);
	request.पूर्णांकf2_id = पूर्णांकf2_id;
	request.cport2_id = cpu_to_le16(cport2_id);

	ret = gb_operation_sync(connection, GB_SVC_TYPE_CONN_DESTROY,
				&request, माप(request), शून्य, 0);
	अगर (ret) अणु
		dev_err(&svc->dev, "failed to destroy connection (%u:%u %u:%u): %d\n",
			पूर्णांकf1_id, cport1_id, पूर्णांकf2_id, cport2_id, ret);
	पूर्ण
पूर्ण

/* Creates bi-directional routes between the devices */
पूर्णांक gb_svc_route_create(काष्ठा gb_svc *svc, u8 पूर्णांकf1_id, u8 dev1_id,
			u8 पूर्णांकf2_id, u8 dev2_id)
अणु
	काष्ठा gb_svc_route_create_request request;

	request.पूर्णांकf1_id = पूर्णांकf1_id;
	request.dev1_id = dev1_id;
	request.पूर्णांकf2_id = पूर्णांकf2_id;
	request.dev2_id = dev2_id;

	वापस gb_operation_sync(svc->connection, GB_SVC_TYPE_ROUTE_CREATE,
				 &request, माप(request), शून्य, 0);
पूर्ण

/* Destroys bi-directional routes between the devices */
व्योम gb_svc_route_destroy(काष्ठा gb_svc *svc, u8 पूर्णांकf1_id, u8 पूर्णांकf2_id)
अणु
	काष्ठा gb_svc_route_destroy_request request;
	पूर्णांक ret;

	request.पूर्णांकf1_id = पूर्णांकf1_id;
	request.पूर्णांकf2_id = पूर्णांकf2_id;

	ret = gb_operation_sync(svc->connection, GB_SVC_TYPE_ROUTE_DESTROY,
				&request, माप(request), शून्य, 0);
	अगर (ret) अणु
		dev_err(&svc->dev, "failed to destroy route (%u %u): %d\n",
			पूर्णांकf1_id, पूर्णांकf2_id, ret);
	पूर्ण
पूर्ण

पूर्णांक gb_svc_पूर्णांकf_set_घातer_mode(काष्ठा gb_svc *svc, u8 पूर्णांकf_id, u8 hs_series,
			       u8 tx_mode, u8 tx_gear, u8 tx_nlanes,
			       u8 tx_amplitude, u8 tx_hs_equalizer,
			       u8 rx_mode, u8 rx_gear, u8 rx_nlanes,
			       u8 flags, u32 quirks,
			       काष्ठा gb_svc_l2_समयr_cfg *local,
			       काष्ठा gb_svc_l2_समयr_cfg *remote)
अणु
	काष्ठा gb_svc_पूर्णांकf_set_pwrm_request request;
	काष्ठा gb_svc_पूर्णांकf_set_pwrm_response response;
	पूर्णांक ret;
	u16 result_code;

	स_रखो(&request, 0, माप(request));

	request.पूर्णांकf_id = पूर्णांकf_id;
	request.hs_series = hs_series;
	request.tx_mode = tx_mode;
	request.tx_gear = tx_gear;
	request.tx_nlanes = tx_nlanes;
	request.tx_amplitude = tx_amplitude;
	request.tx_hs_equalizer = tx_hs_equalizer;
	request.rx_mode = rx_mode;
	request.rx_gear = rx_gear;
	request.rx_nlanes = rx_nlanes;
	request.flags = flags;
	request.quirks = cpu_to_le32(quirks);
	अगर (local)
		request.local_l2समयrdata = *local;
	अगर (remote)
		request.remote_l2समयrdata = *remote;

	ret = gb_operation_sync(svc->connection, GB_SVC_TYPE_INTF_SET_PWRM,
				&request, माप(request),
				&response, माप(response));
	अगर (ret < 0)
		वापस ret;

	result_code = response.result_code;
	अगर (result_code != GB_SVC_SETPWRM_PWR_LOCAL) अणु
		dev_err(&svc->dev, "set power mode = %d\n", result_code);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gb_svc_पूर्णांकf_set_घातer_mode);

पूर्णांक gb_svc_पूर्णांकf_set_घातer_mode_hibernate(काष्ठा gb_svc *svc, u8 पूर्णांकf_id)
अणु
	काष्ठा gb_svc_पूर्णांकf_set_pwrm_request request;
	काष्ठा gb_svc_पूर्णांकf_set_pwrm_response response;
	पूर्णांक ret;
	u16 result_code;

	स_रखो(&request, 0, माप(request));

	request.पूर्णांकf_id = पूर्णांकf_id;
	request.hs_series = GB_SVC_UNIPRO_HS_SERIES_A;
	request.tx_mode = GB_SVC_UNIPRO_HIBERNATE_MODE;
	request.rx_mode = GB_SVC_UNIPRO_HIBERNATE_MODE;

	ret = gb_operation_sync(svc->connection, GB_SVC_TYPE_INTF_SET_PWRM,
				&request, माप(request),
				&response, माप(response));
	अगर (ret < 0) अणु
		dev_err(&svc->dev,
			"failed to send set power mode operation to interface %u: %d\n",
			पूर्णांकf_id, ret);
		वापस ret;
	पूर्ण

	result_code = response.result_code;
	अगर (result_code != GB_SVC_SETPWRM_PWR_OK) अणु
		dev_err(&svc->dev,
			"failed to hibernate the link for interface %u: %u\n",
			पूर्णांकf_id, result_code);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक gb_svc_ping(काष्ठा gb_svc *svc)
अणु
	वापस gb_operation_sync_समयout(svc->connection, GB_SVC_TYPE_PING,
					 शून्य, 0, शून्य, 0,
					 GB_OPERATION_TIMEOUT_DEFAULT * 2);
पूर्ण

अटल पूर्णांक gb_svc_version_request(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_connection *connection = op->connection;
	काष्ठा gb_svc *svc = gb_connection_get_data(connection);
	काष्ठा gb_svc_version_request *request;
	काष्ठा gb_svc_version_response *response;

	अगर (op->request->payload_size < माप(*request)) अणु
		dev_err(&svc->dev, "short version request (%zu < %zu)\n",
			op->request->payload_size,
			माप(*request));
		वापस -EINVAL;
	पूर्ण

	request = op->request->payload;

	अगर (request->major > GB_SVC_VERSION_MAJOR) अणु
		dev_warn(&svc->dev, "unsupported major version (%u > %u)\n",
			 request->major, GB_SVC_VERSION_MAJOR);
		वापस -ENOTSUPP;
	पूर्ण

	svc->protocol_major = request->major;
	svc->protocol_minor = request->minor;

	अगर (!gb_operation_response_alloc(op, माप(*response), GFP_KERNEL))
		वापस -ENOMEM;

	response = op->response->payload;
	response->major = svc->protocol_major;
	response->minor = svc->protocol_minor;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार pwr_debugfs_voltage_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
					माप_प्रकार len, loff_t *offset)
अणु
	काष्ठा svc_debugfs_pwrmon_rail *pwrmon_rails =
		file_inode(file)->i_निजी;
	काष्ठा gb_svc *svc = pwrmon_rails->svc;
	पूर्णांक ret, desc;
	u32 value;
	अक्षर buff[16];

	ret = gb_svc_pwrmon_sample_get(svc, pwrmon_rails->id,
				       GB_SVC_PWRMON_TYPE_VOL, &value);
	अगर (ret) अणु
		dev_err(&svc->dev,
			"failed to get voltage sample %u: %d\n",
			pwrmon_rails->id, ret);
		वापस ret;
	पूर्ण

	desc = scnम_लिखो(buff, माप(buff), "%u\n", value);

	वापस simple_पढ़ो_from_buffer(buf, len, offset, buff, desc);
पूर्ण

अटल sमाप_प्रकार pwr_debugfs_current_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
					माप_प्रकार len, loff_t *offset)
अणु
	काष्ठा svc_debugfs_pwrmon_rail *pwrmon_rails =
		file_inode(file)->i_निजी;
	काष्ठा gb_svc *svc = pwrmon_rails->svc;
	पूर्णांक ret, desc;
	u32 value;
	अक्षर buff[16];

	ret = gb_svc_pwrmon_sample_get(svc, pwrmon_rails->id,
				       GB_SVC_PWRMON_TYPE_CURR, &value);
	अगर (ret) अणु
		dev_err(&svc->dev,
			"failed to get current sample %u: %d\n",
			pwrmon_rails->id, ret);
		वापस ret;
	पूर्ण

	desc = scnम_लिखो(buff, माप(buff), "%u\n", value);

	वापस simple_पढ़ो_from_buffer(buf, len, offset, buff, desc);
पूर्ण

अटल sमाप_प्रकार pwr_debugfs_घातer_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				      माप_प्रकार len, loff_t *offset)
अणु
	काष्ठा svc_debugfs_pwrmon_rail *pwrmon_rails =
		file_inode(file)->i_निजी;
	काष्ठा gb_svc *svc = pwrmon_rails->svc;
	पूर्णांक ret, desc;
	u32 value;
	अक्षर buff[16];

	ret = gb_svc_pwrmon_sample_get(svc, pwrmon_rails->id,
				       GB_SVC_PWRMON_TYPE_PWR, &value);
	अगर (ret) अणु
		dev_err(&svc->dev, "failed to get power sample %u: %d\n",
			pwrmon_rails->id, ret);
		वापस ret;
	पूर्ण

	desc = scnम_लिखो(buff, माप(buff), "%u\n", value);

	वापस simple_पढ़ो_from_buffer(buf, len, offset, buff, desc);
पूर्ण

अटल स्थिर काष्ठा file_operations pwrmon_debugfs_voltage_fops = अणु
	.पढ़ो		= pwr_debugfs_voltage_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा file_operations pwrmon_debugfs_current_fops = अणु
	.पढ़ो		= pwr_debugfs_current_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा file_operations pwrmon_debugfs_घातer_fops = अणु
	.पढ़ो		= pwr_debugfs_घातer_पढ़ो,
पूर्ण;

अटल व्योम gb_svc_pwrmon_debugfs_init(काष्ठा gb_svc *svc)
अणु
	पूर्णांक i;
	माप_प्रकार bufsize;
	काष्ठा dentry *dent;
	काष्ठा gb_svc_pwrmon_rail_names_get_response *rail_names;
	u8 rail_count;

	dent = debugfs_create_dir("pwrmon", svc->debugfs_dentry);
	अगर (IS_ERR_OR_शून्य(dent))
		वापस;

	अगर (gb_svc_pwrmon_rail_count_get(svc, &rail_count))
		जाओ err_pwrmon_debugfs;

	अगर (!rail_count || rail_count > GB_SVC_PWRMON_MAX_RAIL_COUNT)
		जाओ err_pwrmon_debugfs;

	bufsize = माप(*rail_names) +
		GB_SVC_PWRMON_RAIL_NAME_बफ_मानE * rail_count;

	rail_names = kzalloc(bufsize, GFP_KERNEL);
	अगर (!rail_names)
		जाओ err_pwrmon_debugfs;

	svc->pwrmon_rails = kसुस्मृति(rail_count, माप(*svc->pwrmon_rails),
				    GFP_KERNEL);
	अगर (!svc->pwrmon_rails)
		जाओ err_pwrmon_debugfs_मुक्त;

	अगर (gb_svc_pwrmon_rail_names_get(svc, rail_names, bufsize))
		जाओ err_pwrmon_debugfs_मुक्त;

	क्रम (i = 0; i < rail_count; i++) अणु
		काष्ठा dentry *dir;
		काष्ठा svc_debugfs_pwrmon_rail *rail = &svc->pwrmon_rails[i];
		अक्षर fname[GB_SVC_PWRMON_RAIL_NAME_बफ_मानE];

		snम_लिखो(fname, माप(fname), "%s",
			 (अक्षर *)&rail_names->name[i]);

		rail->id = i;
		rail->svc = svc;

		dir = debugfs_create_dir(fname, dent);
		debugfs_create_file("voltage_now", 0444, dir, rail,
				    &pwrmon_debugfs_voltage_fops);
		debugfs_create_file("current_now", 0444, dir, rail,
				    &pwrmon_debugfs_current_fops);
		debugfs_create_file("power_now", 0444, dir, rail,
				    &pwrmon_debugfs_घातer_fops);
	पूर्ण

	kमुक्त(rail_names);
	वापस;

err_pwrmon_debugfs_मुक्त:
	kमुक्त(rail_names);
	kमुक्त(svc->pwrmon_rails);
	svc->pwrmon_rails = शून्य;

err_pwrmon_debugfs:
	debugfs_हटाओ(dent);
पूर्ण

अटल व्योम gb_svc_debugfs_init(काष्ठा gb_svc *svc)
अणु
	svc->debugfs_dentry = debugfs_create_dir(dev_name(&svc->dev),
						 gb_debugfs_get());
	gb_svc_pwrmon_debugfs_init(svc);
पूर्ण

अटल व्योम gb_svc_debugfs_निकास(काष्ठा gb_svc *svc)
अणु
	debugfs_हटाओ_recursive(svc->debugfs_dentry);
	kमुक्त(svc->pwrmon_rails);
	svc->pwrmon_rails = शून्य;
पूर्ण

अटल पूर्णांक gb_svc_hello(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_connection *connection = op->connection;
	काष्ठा gb_svc *svc = gb_connection_get_data(connection);
	काष्ठा gb_svc_hello_request *hello_request;
	पूर्णांक ret;

	अगर (op->request->payload_size < माप(*hello_request)) अणु
		dev_warn(&svc->dev, "short hello request (%zu < %zu)\n",
			 op->request->payload_size,
			 माप(*hello_request));
		वापस -EINVAL;
	पूर्ण

	hello_request = op->request->payload;
	svc->enकरो_id = le16_to_cpu(hello_request->enकरो_id);
	svc->ap_पूर्णांकf_id = hello_request->पूर्णांकerface_id;

	ret = device_add(&svc->dev);
	अगर (ret) अणु
		dev_err(&svc->dev, "failed to register svc device: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = gb_svc_watchकरोg_create(svc);
	अगर (ret) अणु
		dev_err(&svc->dev, "failed to create watchdog: %d\n", ret);
		जाओ err_unरेजिस्टर_device;
	पूर्ण

	gb_svc_debugfs_init(svc);

	वापस gb_svc_queue_deferred_request(op);

err_unरेजिस्टर_device:
	gb_svc_watchकरोg_destroy(svc);
	device_del(&svc->dev);
	वापस ret;
पूर्ण

अटल काष्ठा gb_पूर्णांकerface *gb_svc_पूर्णांकerface_lookup(काष्ठा gb_svc *svc,
						    u8 पूर्णांकf_id)
अणु
	काष्ठा gb_host_device *hd = svc->hd;
	काष्ठा gb_module *module;
	माप_प्रकार num_पूर्णांकerfaces;
	u8 module_id;

	list_क्रम_each_entry(module, &hd->modules, hd_node) अणु
		module_id = module->module_id;
		num_पूर्णांकerfaces = module->num_पूर्णांकerfaces;

		अगर (पूर्णांकf_id >= module_id &&
		    पूर्णांकf_id < module_id + num_पूर्णांकerfaces) अणु
			वापस module->पूर्णांकerfaces[पूर्णांकf_id - module_id];
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा gb_module *gb_svc_module_lookup(काष्ठा gb_svc *svc, u8 module_id)
अणु
	काष्ठा gb_host_device *hd = svc->hd;
	काष्ठा gb_module *module;

	list_क्रम_each_entry(module, &hd->modules, hd_node) अणु
		अगर (module->module_id == module_id)
			वापस module;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम gb_svc_process_hello_deferred(काष्ठा gb_operation *operation)
अणु
	काष्ठा gb_connection *connection = operation->connection;
	काष्ठा gb_svc *svc = gb_connection_get_data(connection);
	पूर्णांक ret;

	/*
	 * XXX This is a hack/work-around to reconfigure the APBridgeA-Switch
	 * link to PWM G2, 1 Lane, Slow Auto, so that it has sufficient
	 * bandwidth क्रम 3 audio streams plus boot-over-UniPro of a hot-plugged
	 * module.
	 *
	 * The code should be हटाओd once SW-2217, Heuristic क्रम UniPro
	 * Power Mode Changes is resolved.
	 */
	ret = gb_svc_पूर्णांकf_set_घातer_mode(svc, svc->ap_पूर्णांकf_id,
					 GB_SVC_UNIPRO_HS_SERIES_A,
					 GB_SVC_UNIPRO_SLOW_AUTO_MODE,
					 2, 1,
					 GB_SVC_SMALL_AMPLITUDE,
					 GB_SVC_NO_DE_EMPHASIS,
					 GB_SVC_UNIPRO_SLOW_AUTO_MODE,
					 2, 1,
					 0, 0,
					 शून्य, शून्य);

	अगर (ret)
		dev_warn(&svc->dev,
			 "power mode change failed on AP to switch link: %d\n",
			 ret);
पूर्ण

अटल व्योम gb_svc_process_module_inserted(काष्ठा gb_operation *operation)
अणु
	काष्ठा gb_svc_module_inserted_request *request;
	काष्ठा gb_connection *connection = operation->connection;
	काष्ठा gb_svc *svc = gb_connection_get_data(connection);
	काष्ठा gb_host_device *hd = svc->hd;
	काष्ठा gb_module *module;
	माप_प्रकार num_पूर्णांकerfaces;
	u8 module_id;
	u16 flags;
	पूर्णांक ret;

	/* The request message size has alपढ़ोy been verअगरied. */
	request = operation->request->payload;
	module_id = request->primary_पूर्णांकf_id;
	num_पूर्णांकerfaces = request->पूर्णांकf_count;
	flags = le16_to_cpu(request->flags);

	dev_dbg(&svc->dev, "%s - id = %u, num_interfaces = %zu, flags = 0x%04x\n",
		__func__, module_id, num_पूर्णांकerfaces, flags);

	अगर (flags & GB_SVC_MODULE_INSERTED_FLAG_NO_PRIMARY) अणु
		dev_warn(&svc->dev, "no primary interface detected on module %u\n",
			 module_id);
	पूर्ण

	module = gb_svc_module_lookup(svc, module_id);
	अगर (module) अणु
		dev_warn(&svc->dev, "unexpected module-inserted event %u\n",
			 module_id);
		वापस;
	पूर्ण

	module = gb_module_create(hd, module_id, num_पूर्णांकerfaces);
	अगर (!module) अणु
		dev_err(&svc->dev, "failed to create module\n");
		वापस;
	पूर्ण

	ret = gb_module_add(module);
	अगर (ret) अणु
		gb_module_put(module);
		वापस;
	पूर्ण

	list_add(&module->hd_node, &hd->modules);
पूर्ण

अटल व्योम gb_svc_process_module_हटाओd(काष्ठा gb_operation *operation)
अणु
	काष्ठा gb_svc_module_हटाओd_request *request;
	काष्ठा gb_connection *connection = operation->connection;
	काष्ठा gb_svc *svc = gb_connection_get_data(connection);
	काष्ठा gb_module *module;
	u8 module_id;

	/* The request message size has alपढ़ोy been verअगरied. */
	request = operation->request->payload;
	module_id = request->primary_पूर्णांकf_id;

	dev_dbg(&svc->dev, "%s - id = %u\n", __func__, module_id);

	module = gb_svc_module_lookup(svc, module_id);
	अगर (!module) अणु
		dev_warn(&svc->dev, "unexpected module-removed event %u\n",
			 module_id);
		वापस;
	पूर्ण

	module->disconnected = true;

	gb_module_del(module);
	list_del(&module->hd_node);
	gb_module_put(module);
पूर्ण

अटल व्योम gb_svc_process_पूर्णांकf_oops(काष्ठा gb_operation *operation)
अणु
	काष्ठा gb_svc_पूर्णांकf_oops_request *request;
	काष्ठा gb_connection *connection = operation->connection;
	काष्ठा gb_svc *svc = gb_connection_get_data(connection);
	काष्ठा gb_पूर्णांकerface *पूर्णांकf;
	u8 पूर्णांकf_id;
	u8 reason;

	/* The request message size has alपढ़ोy been verअगरied. */
	request = operation->request->payload;
	पूर्णांकf_id = request->पूर्णांकf_id;
	reason = request->reason;

	पूर्णांकf = gb_svc_पूर्णांकerface_lookup(svc, पूर्णांकf_id);
	अगर (!पूर्णांकf) अणु
		dev_warn(&svc->dev, "unexpected interface-oops event %u\n",
			 पूर्णांकf_id);
		वापस;
	पूर्ण

	dev_info(&svc->dev, "Deactivating interface %u, interface oops reason = %u\n",
		 पूर्णांकf_id, reason);

	mutex_lock(&पूर्णांकf->mutex);
	पूर्णांकf->disconnected = true;
	gb_पूर्णांकerface_disable(पूर्णांकf);
	gb_पूर्णांकerface_deactivate(पूर्णांकf);
	mutex_unlock(&पूर्णांकf->mutex);
पूर्ण

अटल व्योम gb_svc_process_पूर्णांकf_mailbox_event(काष्ठा gb_operation *operation)
अणु
	काष्ठा gb_svc_पूर्णांकf_mailbox_event_request *request;
	काष्ठा gb_connection *connection = operation->connection;
	काष्ठा gb_svc *svc = gb_connection_get_data(connection);
	काष्ठा gb_पूर्णांकerface *पूर्णांकf;
	u8 पूर्णांकf_id;
	u16 result_code;
	u32 mailbox;

	/* The request message size has alपढ़ोy been verअगरied. */
	request = operation->request->payload;
	पूर्णांकf_id = request->पूर्णांकf_id;
	result_code = le16_to_cpu(request->result_code);
	mailbox = le32_to_cpu(request->mailbox);

	dev_dbg(&svc->dev, "%s - id = %u, result = 0x%04x, mailbox = 0x%08x\n",
		__func__, पूर्णांकf_id, result_code, mailbox);

	पूर्णांकf = gb_svc_पूर्णांकerface_lookup(svc, पूर्णांकf_id);
	अगर (!पूर्णांकf) अणु
		dev_warn(&svc->dev, "unexpected mailbox event %u\n", पूर्णांकf_id);
		वापस;
	पूर्ण

	gb_पूर्णांकerface_mailbox_event(पूर्णांकf, result_code, mailbox);
पूर्ण

अटल व्योम gb_svc_process_deferred_request(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gb_svc_deferred_request *dr;
	काष्ठा gb_operation *operation;
	काष्ठा gb_svc *svc;
	u8 type;

	dr = container_of(work, काष्ठा gb_svc_deferred_request, work);
	operation = dr->operation;
	svc = gb_connection_get_data(operation->connection);
	type = operation->request->header->type;

	चयन (type) अणु
	हाल GB_SVC_TYPE_SVC_HELLO:
		gb_svc_process_hello_deferred(operation);
		अवरोध;
	हाल GB_SVC_TYPE_MODULE_INSERTED:
		gb_svc_process_module_inserted(operation);
		अवरोध;
	हाल GB_SVC_TYPE_MODULE_REMOVED:
		gb_svc_process_module_हटाओd(operation);
		अवरोध;
	हाल GB_SVC_TYPE_INTF_MAILBOX_EVENT:
		gb_svc_process_पूर्णांकf_mailbox_event(operation);
		अवरोध;
	हाल GB_SVC_TYPE_INTF_OOPS:
		gb_svc_process_पूर्णांकf_oops(operation);
		अवरोध;
	शेष:
		dev_err(&svc->dev, "bad deferred request type: 0x%02x\n", type);
	पूर्ण

	gb_operation_put(operation);
	kमुक्त(dr);
पूर्ण

अटल पूर्णांक gb_svc_queue_deferred_request(काष्ठा gb_operation *operation)
अणु
	काष्ठा gb_svc *svc = gb_connection_get_data(operation->connection);
	काष्ठा gb_svc_deferred_request *dr;

	dr = kदो_स्मृति(माप(*dr), GFP_KERNEL);
	अगर (!dr)
		वापस -ENOMEM;

	gb_operation_get(operation);

	dr->operation = operation;
	INIT_WORK(&dr->work, gb_svc_process_deferred_request);

	queue_work(svc->wq, &dr->work);

	वापस 0;
पूर्ण

अटल पूर्णांक gb_svc_पूर्णांकf_reset_recv(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_svc *svc = gb_connection_get_data(op->connection);
	काष्ठा gb_message *request = op->request;
	काष्ठा gb_svc_पूर्णांकf_reset_request *reset;

	अगर (request->payload_size < माप(*reset)) अणु
		dev_warn(&svc->dev, "short reset request received (%zu < %zu)\n",
			 request->payload_size, माप(*reset));
		वापस -EINVAL;
	पूर्ण
	reset = request->payload;

	/* FIXME Reset the पूर्णांकerface here */

	वापस 0;
पूर्ण

अटल पूर्णांक gb_svc_module_inserted_recv(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_svc *svc = gb_connection_get_data(op->connection);
	काष्ठा gb_svc_module_inserted_request *request;

	अगर (op->request->payload_size < माप(*request)) अणु
		dev_warn(&svc->dev, "short module-inserted request received (%zu < %zu)\n",
			 op->request->payload_size, माप(*request));
		वापस -EINVAL;
	पूर्ण

	request = op->request->payload;

	dev_dbg(&svc->dev, "%s - id = %u\n", __func__,
		request->primary_पूर्णांकf_id);

	वापस gb_svc_queue_deferred_request(op);
पूर्ण

अटल पूर्णांक gb_svc_module_हटाओd_recv(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_svc *svc = gb_connection_get_data(op->connection);
	काष्ठा gb_svc_module_हटाओd_request *request;

	अगर (op->request->payload_size < माप(*request)) अणु
		dev_warn(&svc->dev, "short module-removed request received (%zu < %zu)\n",
			 op->request->payload_size, माप(*request));
		वापस -EINVAL;
	पूर्ण

	request = op->request->payload;

	dev_dbg(&svc->dev, "%s - id = %u\n", __func__,
		request->primary_पूर्णांकf_id);

	वापस gb_svc_queue_deferred_request(op);
पूर्ण

अटल पूर्णांक gb_svc_पूर्णांकf_oops_recv(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_svc *svc = gb_connection_get_data(op->connection);
	काष्ठा gb_svc_पूर्णांकf_oops_request *request;

	अगर (op->request->payload_size < माप(*request)) अणु
		dev_warn(&svc->dev, "short intf-oops request received (%zu < %zu)\n",
			 op->request->payload_size, माप(*request));
		वापस -EINVAL;
	पूर्ण

	वापस gb_svc_queue_deferred_request(op);
पूर्ण

अटल पूर्णांक gb_svc_पूर्णांकf_mailbox_event_recv(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_svc *svc = gb_connection_get_data(op->connection);
	काष्ठा gb_svc_पूर्णांकf_mailbox_event_request *request;

	अगर (op->request->payload_size < माप(*request)) अणु
		dev_warn(&svc->dev, "short mailbox request received (%zu < %zu)\n",
			 op->request->payload_size, माप(*request));
		वापस -EINVAL;
	पूर्ण

	request = op->request->payload;

	dev_dbg(&svc->dev, "%s - id = %u\n", __func__, request->पूर्णांकf_id);

	वापस gb_svc_queue_deferred_request(op);
पूर्ण

अटल पूर्णांक gb_svc_request_handler(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_connection *connection = op->connection;
	काष्ठा gb_svc *svc = gb_connection_get_data(connection);
	u8 type = op->type;
	पूर्णांक ret = 0;

	/*
	 * SVC requests need to follow a specअगरic order (at least initially) and
	 * below code takes care of enक्रमcing that. The expected order is:
	 * - PROTOCOL_VERSION
	 * - SVC_HELLO
	 * - Any other request, but the earlier two.
	 *
	 * Incoming requests are guaranteed to be serialized and so we करोn't
	 * need to protect 'state' क्रम any races.
	 */
	चयन (type) अणु
	हाल GB_SVC_TYPE_PROTOCOL_VERSION:
		अगर (svc->state != GB_SVC_STATE_RESET)
			ret = -EINVAL;
		अवरोध;
	हाल GB_SVC_TYPE_SVC_HELLO:
		अगर (svc->state != GB_SVC_STATE_PROTOCOL_VERSION)
			ret = -EINVAL;
		अवरोध;
	शेष:
		अगर (svc->state != GB_SVC_STATE_SVC_HELLO)
			ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (ret) अणु
		dev_warn(&svc->dev, "unexpected request 0x%02x received (state %u)\n",
			 type, svc->state);
		वापस ret;
	पूर्ण

	चयन (type) अणु
	हाल GB_SVC_TYPE_PROTOCOL_VERSION:
		ret = gb_svc_version_request(op);
		अगर (!ret)
			svc->state = GB_SVC_STATE_PROTOCOL_VERSION;
		वापस ret;
	हाल GB_SVC_TYPE_SVC_HELLO:
		ret = gb_svc_hello(op);
		अगर (!ret)
			svc->state = GB_SVC_STATE_SVC_HELLO;
		वापस ret;
	हाल GB_SVC_TYPE_INTF_RESET:
		वापस gb_svc_पूर्णांकf_reset_recv(op);
	हाल GB_SVC_TYPE_MODULE_INSERTED:
		वापस gb_svc_module_inserted_recv(op);
	हाल GB_SVC_TYPE_MODULE_REMOVED:
		वापस gb_svc_module_हटाओd_recv(op);
	हाल GB_SVC_TYPE_INTF_MAILBOX_EVENT:
		वापस gb_svc_पूर्णांकf_mailbox_event_recv(op);
	हाल GB_SVC_TYPE_INTF_OOPS:
		वापस gb_svc_पूर्णांकf_oops_recv(op);
	शेष:
		dev_warn(&svc->dev, "unsupported request 0x%02x\n", type);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम gb_svc_release(काष्ठा device *dev)
अणु
	काष्ठा gb_svc *svc = to_gb_svc(dev);

	अगर (svc->connection)
		gb_connection_destroy(svc->connection);
	ida_destroy(&svc->device_id_map);
	destroy_workqueue(svc->wq);
	kमुक्त(svc);
पूर्ण

काष्ठा device_type greybus_svc_type = अणु
	.name		= "greybus_svc",
	.release	= gb_svc_release,
पूर्ण;

काष्ठा gb_svc *gb_svc_create(काष्ठा gb_host_device *hd)
अणु
	काष्ठा gb_svc *svc;

	svc = kzalloc(माप(*svc), GFP_KERNEL);
	अगर (!svc)
		वापस शून्य;

	svc->wq = alloc_workqueue("%s:svc", WQ_UNBOUND, 1, dev_name(&hd->dev));
	अगर (!svc->wq) अणु
		kमुक्त(svc);
		वापस शून्य;
	पूर्ण

	svc->dev.parent = &hd->dev;
	svc->dev.bus = &greybus_bus_type;
	svc->dev.type = &greybus_svc_type;
	svc->dev.groups = svc_groups;
	svc->dev.dma_mask = svc->dev.parent->dma_mask;
	device_initialize(&svc->dev);

	dev_set_name(&svc->dev, "%d-svc", hd->bus_id);

	ida_init(&svc->device_id_map);
	svc->state = GB_SVC_STATE_RESET;
	svc->hd = hd;

	svc->connection = gb_connection_create_अटल(hd, GB_SVC_CPORT_ID,
						      gb_svc_request_handler);
	अगर (IS_ERR(svc->connection)) अणु
		dev_err(&svc->dev, "failed to create connection: %ld\n",
			PTR_ERR(svc->connection));
		जाओ err_put_device;
	पूर्ण

	gb_connection_set_data(svc->connection, svc);

	वापस svc;

err_put_device:
	put_device(&svc->dev);
	वापस शून्य;
पूर्ण

पूर्णांक gb_svc_add(काष्ठा gb_svc *svc)
अणु
	पूर्णांक ret;

	/*
	 * The SVC protocol is currently driven by the SVC, so the SVC device
	 * is added from the connection request handler when enough
	 * inक्रमmation has been received.
	 */
	ret = gb_connection_enable(svc->connection);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम gb_svc_हटाओ_modules(काष्ठा gb_svc *svc)
अणु
	काष्ठा gb_host_device *hd = svc->hd;
	काष्ठा gb_module *module, *पंचांगp;

	list_क्रम_each_entry_safe(module, पंचांगp, &hd->modules, hd_node) अणु
		gb_module_del(module);
		list_del(&module->hd_node);
		gb_module_put(module);
	पूर्ण
पूर्ण

व्योम gb_svc_del(काष्ठा gb_svc *svc)
अणु
	gb_connection_disable_rx(svc->connection);

	/*
	 * The SVC device may have been रेजिस्टरed from the request handler.
	 */
	अगर (device_is_रेजिस्टरed(&svc->dev)) अणु
		gb_svc_debugfs_निकास(svc);
		gb_svc_watchकरोg_destroy(svc);
		device_del(&svc->dev);
	पूर्ण

	flush_workqueue(svc->wq);

	gb_svc_हटाओ_modules(svc);

	gb_connection_disable(svc->connection);
पूर्ण

व्योम gb_svc_put(काष्ठा gb_svc *svc)
अणु
	put_device(&svc->dev);
पूर्ण
