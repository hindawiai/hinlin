<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ISHTP-HID glue driver.
 *
 * Copyright (c) 2012-2016, Intel Corporation.
 */

#समावेश <linux/hid.h>
#समावेश <linux/पूर्णांकel-ish-client-अगर.h>
#समावेश <uapi/linux/input.h>
#समावेश "ishtp-hid.h"

/**
 * ishtp_hid_parse() - hid-core .parse() callback
 * @hid:	hid device instance
 *
 * This function माला_लो called during call to hid_add_device
 *
 * Return: 0 on success and non zero on error
 */
अटल पूर्णांक ishtp_hid_parse(काष्ठा hid_device *hid)
अणु
	काष्ठा ishtp_hid_data *hid_data =  hid->driver_data;
	काष्ठा ishtp_cl_data *client_data = hid_data->client_data;
	पूर्णांक rv;

	rv = hid_parse_report(hid, client_data->report_descr[hid_data->index],
			      client_data->report_descr_size[hid_data->index]);
	अगर (rv)
		वापस	rv;

	वापस 0;
पूर्ण

/* Empty callbacks with success वापस code */
अटल पूर्णांक ishtp_hid_start(काष्ठा hid_device *hid)
अणु
	वापस 0;
पूर्ण

अटल व्योम ishtp_hid_stop(काष्ठा hid_device *hid)
अणु
पूर्ण

अटल पूर्णांक ishtp_hid_खोलो(काष्ठा hid_device *hid)
अणु
	वापस 0;
पूर्ण

अटल व्योम ishtp_hid_बंद(काष्ठा hid_device *hid)
अणु
पूर्ण

अटल पूर्णांक ishtp_raw_request(काष्ठा hid_device *hid, अचिन्हित अक्षर reportnum,
			     __u8 *buf, माप_प्रकार len, अचिन्हित अक्षर rtype,
			     पूर्णांक reqtype)
अणु
	काष्ठा ishtp_hid_data *hid_data =  hid->driver_data;
	अक्षर *ishtp_buf = शून्य;
	माप_प्रकार ishtp_buf_len;
	अचिन्हित पूर्णांक header_size = माप(काष्ठा hostअगर_msg);

	अगर (rtype == HID_OUTPUT_REPORT)
		वापस -EINVAL;

	hid_data->request_करोne = false;
	चयन (reqtype) अणु
	हाल HID_REQ_GET_REPORT:
		hid_data->raw_buf = buf;
		hid_data->raw_buf_size = len;
		hid_data->raw_get_req = true;

		hid_ishtp_get_report(hid, reportnum, rtype);
		अवरोध;
	हाल HID_REQ_SET_REPORT:
		/*
		 * Spare 7 bytes क्रम 64b accesses through
		 * get/put_unaligned_le64()
		 */
		ishtp_buf_len = len + header_size;
		ishtp_buf = kzalloc(ishtp_buf_len + 7, GFP_KERNEL);
		अगर (!ishtp_buf)
			वापस -ENOMEM;

		स_नकल(ishtp_buf + header_size, buf, len);
		hid_ishtp_set_feature(hid, ishtp_buf, ishtp_buf_len, reportnum);
		kमुक्त(ishtp_buf);
		अवरोध;
	पूर्ण

	hid_hw_रुको(hid);

	वापस len;
पूर्ण

/**
 * ishtp_hid_request() - hid-core .request() callback
 * @hid:	hid device instance
 * @rep:	poपूर्णांकer to hid_report
 * @reqtype:	type of req. [GET|SET]_REPORT
 *
 * This function is used to set/get feaure/input report.
 */
अटल व्योम ishtp_hid_request(काष्ठा hid_device *hid, काष्ठा hid_report *rep,
	पूर्णांक reqtype)
अणु
	काष्ठा ishtp_hid_data *hid_data =  hid->driver_data;
	/* the specअगरic report length, just HID part of it */
	अचिन्हित पूर्णांक len = ((rep->size - 1) >> 3) + 1 + (rep->id > 0);
	अक्षर *buf;
	अचिन्हित पूर्णांक header_size = माप(काष्ठा hostअगर_msg);

	len += header_size;

	hid_data->request_करोne = false;
	चयन (reqtype) अणु
	हाल HID_REQ_GET_REPORT:
		hid_data->raw_get_req = false;
		hid_ishtp_get_report(hid, rep->id, rep->type);
		अवरोध;
	हाल HID_REQ_SET_REPORT:
		/*
		 * Spare 7 bytes क्रम 64b accesses through
		 * get/put_unaligned_le64()
		 */
		buf = kzalloc(len + 7, GFP_KERNEL);
		अगर (!buf)
			वापस;

		hid_output_report(rep, buf + header_size);
		hid_ishtp_set_feature(hid, buf, len, rep->id);
		kमुक्त(buf);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ishtp_रुको_क्रम_response() - hid-core .रुको() callback
 * @hid:	hid device instance
 *
 * This function is used to रुको after get feaure/input report.
 *
 * Return: 0 on success and non zero on error
 */
अटल पूर्णांक ishtp_रुको_क्रम_response(काष्ठा hid_device *hid)
अणु
	काष्ठा ishtp_hid_data *hid_data =  hid->driver_data;
	पूर्णांक rv;

	hid_ishtp_trace(client_data,  "%s hid %p\n", __func__, hid);

	rv = ishtp_hid_link_पढ़ोy_रुको(hid_data->client_data);
	अगर (rv)
		वापस rv;

	अगर (!hid_data->request_करोne)
		रुको_event_पूर्णांकerruptible_समयout(hid_data->hid_रुको,
					hid_data->request_करोne, 3 * HZ);

	अगर (!hid_data->request_करोne) अणु
		hid_err(hid,
			"timeout waiting for response from ISHTP device\n");
		वापस -ETIMEDOUT;
	पूर्ण
	hid_ishtp_trace(client_data,  "%s hid %p done\n", __func__, hid);

	hid_data->request_करोne = false;

	वापस 0;
पूर्ण

/**
 * ishtp_hid_wakeup() - Wakeup caller
 * @hid:	hid device instance
 *
 * This function will wakeup caller रुकोing क्रम Get/Set feature report
 */
व्योम ishtp_hid_wakeup(काष्ठा hid_device *hid)
अणु
	काष्ठा ishtp_hid_data *hid_data = hid->driver_data;

	hid_data->request_करोne = true;
	wake_up_पूर्णांकerruptible(&hid_data->hid_रुको);
पूर्ण

अटल काष्ठा hid_ll_driver ishtp_hid_ll_driver = अणु
	.parse = ishtp_hid_parse,
	.start = ishtp_hid_start,
	.stop = ishtp_hid_stop,
	.खोलो = ishtp_hid_खोलो,
	.बंद = ishtp_hid_बंद,
	.request = ishtp_hid_request,
	.रुको = ishtp_रुको_क्रम_response,
	.raw_request = ishtp_raw_request
पूर्ण;

/**
 * ishtp_hid_probe() - hid रेजिस्टर ll driver
 * @cur_hid_dev:	Index of hid device calling to रेजिस्टर
 * @client_data:	Client data poपूर्णांकer
 *
 * This function is used to allocate and add HID device.
 *
 * Return: 0 on success, non zero on error
 */
पूर्णांक ishtp_hid_probe(अचिन्हित पूर्णांक cur_hid_dev,
		    काष्ठा ishtp_cl_data *client_data)
अणु
	पूर्णांक rv;
	काष्ठा hid_device *hid;
	काष्ठा ishtp_hid_data *hid_data;

	hid = hid_allocate_device();
	अगर (IS_ERR(hid))
		वापस PTR_ERR(hid);

	hid_data = kzalloc(माप(*hid_data), GFP_KERNEL);
	अगर (!hid_data) अणु
		rv = -ENOMEM;
		जाओ err_hid_data;
	पूर्ण

	hid_data->index = cur_hid_dev;
	hid_data->client_data = client_data;
	init_रुकोqueue_head(&hid_data->hid_रुको);

	hid->driver_data = hid_data;

	client_data->hid_sensor_hubs[cur_hid_dev] = hid;

	hid->ll_driver = &ishtp_hid_ll_driver;
	hid->bus = BUS_INTEL_ISHTP;
	hid->dev.parent = ishtp_device(client_data->cl_device);

	hid->version = le16_to_cpu(ISH_HID_VERSION);
	hid->venकरोr = le16_to_cpu(client_data->hid_devices[cur_hid_dev].vid);
	hid->product = le16_to_cpu(client_data->hid_devices[cur_hid_dev].pid);
	snम_लिखो(hid->name, माप(hid->name), "%s %04X:%04X", "hid-ishtp",
		hid->venकरोr, hid->product);

	rv = hid_add_device(hid);
	अगर (rv)
		जाओ err_hid_device;

	hid_ishtp_trace(client_data,  "%s allocated hid %p\n", __func__, hid);

	वापस 0;

err_hid_device:
	kमुक्त(hid_data);
err_hid_data:
	hid_destroy_device(hid);
	वापस rv;
पूर्ण

/**
 * ishtp_hid_probe() - Remove रेजिस्टरed hid device
 * @client_data:	client data poपूर्णांकer
 *
 * This function is used to destroy allocatd HID device.
 */
व्योम ishtp_hid_हटाओ(काष्ठा ishtp_cl_data *client_data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < client_data->num_hid_devices; ++i) अणु
		अगर (client_data->hid_sensor_hubs[i]) अणु
			kमुक्त(client_data->hid_sensor_hubs[i]->driver_data);
			hid_destroy_device(client_data->hid_sensor_hubs[i]);
			client_data->hid_sensor_hubs[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण
