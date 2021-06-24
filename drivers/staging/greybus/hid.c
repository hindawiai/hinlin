<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * HID class driver क्रम the Greybus.
 *
 * Copyright 2014 Google Inc.
 * Copyright 2014 Linaro Ltd.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/hid.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/greybus.h>

/* Greybus HID device's काष्ठाure */
काष्ठा gb_hid अणु
	काष्ठा gb_bundle *bundle;
	काष्ठा gb_connection		*connection;

	काष्ठा hid_device		*hid;
	काष्ठा gb_hid_desc_response	hdesc;

	अचिन्हित दीर्घ			flags;
#घोषणा GB_HID_STARTED			0x01
#घोषणा GB_HID_READ_PENDING		0x04

	अचिन्हित पूर्णांक			bufsize;
	अक्षर				*inbuf;
पूर्ण;

/* Routines to get controller's inक्रमmation over greybus */

/* Operations perक्रमmed on greybus */
अटल पूर्णांक gb_hid_get_desc(काष्ठा gb_hid *ghid)
अणु
	वापस gb_operation_sync(ghid->connection, GB_HID_TYPE_GET_DESC, शून्य,
				 0, &ghid->hdesc, माप(ghid->hdesc));
पूर्ण

अटल पूर्णांक gb_hid_get_report_desc(काष्ठा gb_hid *ghid, अक्षर *rdesc)
अणु
	पूर्णांक ret;

	ret = gb_pm_runसमय_get_sync(ghid->bundle);
	अगर (ret)
		वापस ret;

	ret = gb_operation_sync(ghid->connection, GB_HID_TYPE_GET_REPORT_DESC,
				शून्य, 0, rdesc,
				le16_to_cpu(ghid->hdesc.wReportDescLength));

	gb_pm_runसमय_put_स्वतःsuspend(ghid->bundle);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_hid_set_घातer(काष्ठा gb_hid *ghid, पूर्णांक type)
अणु
	पूर्णांक ret;

	ret = gb_pm_runसमय_get_sync(ghid->bundle);
	अगर (ret)
		वापस ret;

	ret = gb_operation_sync(ghid->connection, type, शून्य, 0, शून्य, 0);

	gb_pm_runसमय_put_स्वतःsuspend(ghid->bundle);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_hid_get_report(काष्ठा gb_hid *ghid, u8 report_type, u8 report_id,
			     अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा gb_hid_get_report_request request;
	पूर्णांक ret;

	ret = gb_pm_runसमय_get_sync(ghid->bundle);
	अगर (ret)
		वापस ret;

	request.report_type = report_type;
	request.report_id = report_id;

	ret = gb_operation_sync(ghid->connection, GB_HID_TYPE_GET_REPORT,
				&request, माप(request), buf, len);

	gb_pm_runसमय_put_स्वतःsuspend(ghid->bundle);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_hid_set_report(काष्ठा gb_hid *ghid, u8 report_type, u8 report_id,
			     अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा gb_hid_set_report_request *request;
	काष्ठा gb_operation *operation;
	पूर्णांक ret, size = माप(*request) + len - 1;

	ret = gb_pm_runसमय_get_sync(ghid->bundle);
	अगर (ret)
		वापस ret;

	operation = gb_operation_create(ghid->connection,
					GB_HID_TYPE_SET_REPORT, size, 0,
					GFP_KERNEL);
	अगर (!operation) अणु
		gb_pm_runसमय_put_स्वतःsuspend(ghid->bundle);
		वापस -ENOMEM;
	पूर्ण

	request = operation->request->payload;
	request->report_type = report_type;
	request->report_id = report_id;
	स_नकल(request->report, buf, len);

	ret = gb_operation_request_send_sync(operation);
	अगर (ret) अणु
		dev_err(&operation->connection->bundle->dev,
			"failed to set report: %d\n", ret);
	पूर्ण अन्यथा अणु
		ret = len;
	पूर्ण

	gb_operation_put(operation);
	gb_pm_runसमय_put_स्वतःsuspend(ghid->bundle);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_hid_request_handler(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_connection *connection = op->connection;
	काष्ठा gb_hid *ghid = gb_connection_get_data(connection);
	काष्ठा gb_hid_input_report_request *request = op->request->payload;

	अगर (op->type != GB_HID_TYPE_IRQ_EVENT) अणु
		dev_err(&connection->bundle->dev,
			"unsupported unsolicited request\n");
		वापस -EINVAL;
	पूर्ण

	अगर (test_bit(GB_HID_STARTED, &ghid->flags))
		hid_input_report(ghid->hid, HID_INPUT_REPORT,
				 request->report, op->request->payload_size, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक gb_hid_report_len(काष्ठा hid_report *report)
अणु
	वापस ((report->size - 1) >> 3) + 1 +
		report->device->report_क्रमागत[report->type].numbered;
पूर्ण

अटल व्योम gb_hid_find_max_report(काष्ठा hid_device *hid, अचिन्हित पूर्णांक type,
				   अचिन्हित पूर्णांक *max)
अणु
	काष्ठा hid_report *report;
	अचिन्हित पूर्णांक size;

	list_क्रम_each_entry(report, &hid->report_क्रमागत[type].report_list, list) अणु
		size = gb_hid_report_len(report);
		अगर (*max < size)
			*max = size;
	पूर्ण
पूर्ण

अटल व्योम gb_hid_मुक्त_buffers(काष्ठा gb_hid *ghid)
अणु
	kमुक्त(ghid->inbuf);
	ghid->inbuf = शून्य;
	ghid->bufsize = 0;
पूर्ण

अटल पूर्णांक gb_hid_alloc_buffers(काष्ठा gb_hid *ghid, माप_प्रकार bufsize)
अणु
	ghid->inbuf = kzalloc(bufsize, GFP_KERNEL);
	अगर (!ghid->inbuf)
		वापस -ENOMEM;

	ghid->bufsize = bufsize;

	वापस 0;
पूर्ण

/* Routines dealing with reports */
अटल व्योम gb_hid_init_report(काष्ठा gb_hid *ghid, काष्ठा hid_report *report)
अणु
	अचिन्हित पूर्णांक size;

	size = gb_hid_report_len(report);
	अगर (gb_hid_get_report(ghid, report->type, report->id, ghid->inbuf,
			      size))
		वापस;

	/*
	 * hid->driver_lock is held as we are in probe function,
	 * we just need to setup the input fields, so using
	 * hid_report_raw_event is safe.
	 */
	hid_report_raw_event(ghid->hid, report->type, ghid->inbuf, size, 1);
पूर्ण

अटल व्योम gb_hid_init_reports(काष्ठा gb_hid *ghid)
अणु
	काष्ठा hid_device *hid = ghid->hid;
	काष्ठा hid_report *report;

	list_क्रम_each_entry(report,
			    &hid->report_क्रमागत[HID_INPUT_REPORT].report_list,
			    list)
		gb_hid_init_report(ghid, report);

	list_क्रम_each_entry(report,
			    &hid->report_क्रमागत[HID_FEATURE_REPORT].report_list,
			    list)
		gb_hid_init_report(ghid, report);
पूर्ण

अटल पूर्णांक __gb_hid_get_raw_report(काष्ठा hid_device *hid,
				   अचिन्हित अक्षर report_number, __u8 *buf, माप_प्रकार count,
				   अचिन्हित अक्षर report_type)
अणु
	काष्ठा gb_hid *ghid = hid->driver_data;
	पूर्णांक ret;

	अगर (report_type == HID_OUTPUT_REPORT)
		वापस -EINVAL;

	ret = gb_hid_get_report(ghid, report_type, report_number, buf, count);
	अगर (!ret)
		ret = count;

	वापस ret;
पूर्ण

अटल पूर्णांक __gb_hid_output_raw_report(काष्ठा hid_device *hid, __u8 *buf,
				      माप_प्रकार len, अचिन्हित अक्षर report_type)
अणु
	काष्ठा gb_hid *ghid = hid->driver_data;
	पूर्णांक report_id = buf[0];
	पूर्णांक ret;

	अगर (report_type == HID_INPUT_REPORT)
		वापस -EINVAL;

	अगर (report_id) अणु
		buf++;
		len--;
	पूर्ण

	ret = gb_hid_set_report(ghid, report_type, report_id, buf, len);
	अगर (report_id && ret >= 0)
		ret++; /* add report_id to the number of transferred bytes */

	वापस 0;
पूर्ण

अटल पूर्णांक gb_hid_raw_request(काष्ठा hid_device *hid, अचिन्हित अक्षर reportnum,
			      __u8 *buf, माप_प्रकार len, अचिन्हित अक्षर rtype,
			      पूर्णांक reqtype)
अणु
	चयन (reqtype) अणु
	हाल HID_REQ_GET_REPORT:
		वापस __gb_hid_get_raw_report(hid, reportnum, buf, len, rtype);
	हाल HID_REQ_SET_REPORT:
		अगर (buf[0] != reportnum)
			वापस -EINVAL;
		वापस __gb_hid_output_raw_report(hid, buf, len, rtype);
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

/* HID Callbacks */
अटल पूर्णांक gb_hid_parse(काष्ठा hid_device *hid)
अणु
	काष्ठा gb_hid *ghid = hid->driver_data;
	अचिन्हित पूर्णांक rsize;
	अक्षर *rdesc;
	पूर्णांक ret;

	rsize = le16_to_cpu(ghid->hdesc.wReportDescLength);
	अगर (!rsize || rsize > HID_MAX_DESCRIPTOR_SIZE) अणु
		dbg_hid("weird size of report descriptor (%u)\n", rsize);
		वापस -EINVAL;
	पूर्ण

	rdesc = kzalloc(rsize, GFP_KERNEL);
	अगर (!rdesc)
		वापस -ENOMEM;

	ret = gb_hid_get_report_desc(ghid, rdesc);
	अगर (ret) अणु
		hid_err(hid, "reading report descriptor failed\n");
		जाओ मुक्त_rdesc;
	पूर्ण

	ret = hid_parse_report(hid, rdesc, rsize);
	अगर (ret)
		dbg_hid("parsing report descriptor failed\n");

मुक्त_rdesc:
	kमुक्त(rdesc);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_hid_start(काष्ठा hid_device *hid)
अणु
	काष्ठा gb_hid *ghid = hid->driver_data;
	अचिन्हित पूर्णांक bufsize = HID_MIN_BUFFER_SIZE;
	पूर्णांक ret;

	gb_hid_find_max_report(hid, HID_INPUT_REPORT, &bufsize);
	gb_hid_find_max_report(hid, HID_OUTPUT_REPORT, &bufsize);
	gb_hid_find_max_report(hid, HID_FEATURE_REPORT, &bufsize);

	अगर (bufsize > HID_MAX_BUFFER_SIZE)
		bufsize = HID_MAX_BUFFER_SIZE;

	ret = gb_hid_alloc_buffers(ghid, bufsize);
	अगर (ret)
		वापस ret;

	अगर (!(hid->quirks & HID_QUIRK_NO_INIT_REPORTS))
		gb_hid_init_reports(ghid);

	वापस 0;
पूर्ण

अटल व्योम gb_hid_stop(काष्ठा hid_device *hid)
अणु
	काष्ठा gb_hid *ghid = hid->driver_data;

	gb_hid_मुक्त_buffers(ghid);
पूर्ण

अटल पूर्णांक gb_hid_खोलो(काष्ठा hid_device *hid)
अणु
	काष्ठा gb_hid *ghid = hid->driver_data;
	पूर्णांक ret;

	ret = gb_hid_set_घातer(ghid, GB_HID_TYPE_PWR_ON);
	अगर (ret < 0)
		वापस ret;

	set_bit(GB_HID_STARTED, &ghid->flags);
	वापस 0;
पूर्ण

अटल व्योम gb_hid_बंद(काष्ठा hid_device *hid)
अणु
	काष्ठा gb_hid *ghid = hid->driver_data;
	पूर्णांक ret;

	clear_bit(GB_HID_STARTED, &ghid->flags);

	/* Save some घातer */
	ret = gb_hid_set_घातer(ghid, GB_HID_TYPE_PWR_OFF);
	अगर (ret)
		dev_err(&ghid->connection->bundle->dev,
			"failed to power off (%d)\n", ret);
पूर्ण

अटल पूर्णांक gb_hid_घातer(काष्ठा hid_device *hid, पूर्णांक lvl)
अणु
	काष्ठा gb_hid *ghid = hid->driver_data;

	चयन (lvl) अणु
	हाल PM_HINT_FULLON:
		वापस gb_hid_set_घातer(ghid, GB_HID_TYPE_PWR_ON);
	हाल PM_HINT_NORMAL:
		वापस gb_hid_set_घातer(ghid, GB_HID_TYPE_PWR_OFF);
	पूर्ण

	वापस 0;
पूर्ण

/* HID काष्ठाure to pass callbacks */
अटल काष्ठा hid_ll_driver gb_hid_ll_driver = अणु
	.parse = gb_hid_parse,
	.start = gb_hid_start,
	.stop = gb_hid_stop,
	.खोलो = gb_hid_खोलो,
	.बंद = gb_hid_बंद,
	.घातer = gb_hid_घातer,
	.raw_request = gb_hid_raw_request,
पूर्ण;

अटल पूर्णांक gb_hid_init(काष्ठा gb_hid *ghid)
अणु
	काष्ठा hid_device *hid = ghid->hid;
	पूर्णांक ret;

	ret = gb_hid_get_desc(ghid);
	अगर (ret)
		वापस ret;

	hid->version = le16_to_cpu(ghid->hdesc.bcdHID);
	hid->venकरोr = le16_to_cpu(ghid->hdesc.wVenकरोrID);
	hid->product = le16_to_cpu(ghid->hdesc.wProductID);
	hid->country = ghid->hdesc.bCountryCode;

	hid->driver_data = ghid;
	hid->ll_driver = &gb_hid_ll_driver;
	hid->dev.parent = &ghid->connection->bundle->dev;
//	hid->bus = BUS_GREYBUS; /* Need a bustype क्रम GREYBUS in <linux/input.h> */

	/* Set HID device's name */
	snम_लिखो(hid->name, माप(hid->name), "%s %04X:%04X",
		 dev_name(&ghid->connection->bundle->dev),
		 hid->venकरोr, hid->product);

	वापस 0;
पूर्ण

अटल पूर्णांक gb_hid_probe(काष्ठा gb_bundle *bundle,
			स्थिर काष्ठा greybus_bundle_id *id)
अणु
	काष्ठा greybus_descriptor_cport *cport_desc;
	काष्ठा gb_connection *connection;
	काष्ठा hid_device *hid;
	काष्ठा gb_hid *ghid;
	पूर्णांक ret;

	अगर (bundle->num_cports != 1)
		वापस -ENODEV;

	cport_desc = &bundle->cport_desc[0];
	अगर (cport_desc->protocol_id != GREYBUS_PROTOCOL_HID)
		वापस -ENODEV;

	ghid = kzalloc(माप(*ghid), GFP_KERNEL);
	अगर (!ghid)
		वापस -ENOMEM;

	connection = gb_connection_create(bundle, le16_to_cpu(cport_desc->id),
					  gb_hid_request_handler);
	अगर (IS_ERR(connection)) अणु
		ret = PTR_ERR(connection);
		जाओ err_मुक्त_ghid;
	पूर्ण

	gb_connection_set_data(connection, ghid);
	ghid->connection = connection;

	hid = hid_allocate_device();
	अगर (IS_ERR(hid)) अणु
		ret = PTR_ERR(hid);
		जाओ err_connection_destroy;
	पूर्ण

	ghid->hid = hid;
	ghid->bundle = bundle;

	greybus_set_drvdata(bundle, ghid);

	ret = gb_connection_enable(connection);
	अगर (ret)
		जाओ err_destroy_hid;

	ret = gb_hid_init(ghid);
	अगर (ret)
		जाओ err_connection_disable;

	ret = hid_add_device(hid);
	अगर (ret) अणु
		hid_err(hid, "can't add hid device: %d\n", ret);
		जाओ err_connection_disable;
	पूर्ण

	gb_pm_runसमय_put_स्वतःsuspend(bundle);

	वापस 0;

err_connection_disable:
	gb_connection_disable(connection);
err_destroy_hid:
	hid_destroy_device(hid);
err_connection_destroy:
	gb_connection_destroy(connection);
err_मुक्त_ghid:
	kमुक्त(ghid);

	वापस ret;
पूर्ण

अटल व्योम gb_hid_disconnect(काष्ठा gb_bundle *bundle)
अणु
	काष्ठा gb_hid *ghid = greybus_get_drvdata(bundle);

	अगर (gb_pm_runसमय_get_sync(bundle))
		gb_pm_runसमय_get_noresume(bundle);

	hid_destroy_device(ghid->hid);
	gb_connection_disable(ghid->connection);
	gb_connection_destroy(ghid->connection);
	kमुक्त(ghid);
पूर्ण

अटल स्थिर काष्ठा greybus_bundle_id gb_hid_id_table[] = अणु
	अणु GREYBUS_DEVICE_CLASS(GREYBUS_CLASS_HID) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(greybus, gb_hid_id_table);

अटल काष्ठा greybus_driver gb_hid_driver = अणु
	.name		= "hid",
	.probe		= gb_hid_probe,
	.disconnect	= gb_hid_disconnect,
	.id_table	= gb_hid_id_table,
पूर्ण;
module_greybus_driver(gb_hid_driver);

MODULE_LICENSE("GPL v2");
