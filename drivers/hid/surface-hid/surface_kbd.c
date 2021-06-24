<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Surface System Aggregator Module (SSAM) HID transport driver क्रम the legacy
 * keyboard पूर्णांकerface (KBD/TC=0x08 subप्रणाली). Provides support क्रम the
 * पूर्णांकegrated HID keyboard on Surface Laptops 1 and 2.
 *
 * Copyright (C) 2019-2021 Maximilian Luz <luzmaximilian@gmail.com>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/hid.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>

#समावेश <linux/surface_aggregator/controller.h>

#समावेश "surface_hid_core.h"


/* -- SAM पूर्णांकerface (KBD). -------------------------------------------------- */

#घोषणा KBD_FEATURE_REPORT_SIZE			7  /* 6 + report ID */

क्रमागत surface_kbd_cid अणु
	SURFACE_KBD_CID_GET_DESCRIPTOR		= 0x00,
	SURFACE_KBD_CID_SET_CAPSLOCK_LED	= 0x01,
	SURFACE_KBD_CID_EVT_INPUT_GENERIC	= 0x03,
	SURFACE_KBD_CID_EVT_INPUT_HOTKEYS	= 0x04,
	SURFACE_KBD_CID_GET_FEATURE_REPORT	= 0x0b,
पूर्ण;

अटल पूर्णांक ssam_kbd_get_descriptor(काष्ठा surface_hid_device *shid, u8 entry, u8 *buf, माप_प्रकार len)
अणु
	काष्ठा ssam_request rqst;
	काष्ठा ssam_response rsp;
	पूर्णांक status;

	rqst.target_category = shid->uid.category;
	rqst.target_id = shid->uid.target;
	rqst.command_id = SURFACE_KBD_CID_GET_DESCRIPTOR;
	rqst.instance_id = shid->uid.instance;
	rqst.flags = SSAM_REQUEST_HAS_RESPONSE;
	rqst.length = माप(entry);
	rqst.payload = &entry;

	rsp.capacity = len;
	rsp.length = 0;
	rsp.poपूर्णांकer = buf;

	status = ssam_retry(ssam_request_sync_onstack, shid->ctrl, &rqst, &rsp, माप(entry));
	अगर (status)
		वापस status;

	अगर (rsp.length != len) अणु
		dev_err(shid->dev, "invalid descriptor length: got %zu, expected, %zu\n",
			rsp.length, len);
		वापस -EPROTO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ssam_kbd_set_caps_led(काष्ठा surface_hid_device *shid, bool value)
अणु
	काष्ठा ssam_request rqst;
	u8 value_u8 = value;

	rqst.target_category = shid->uid.category;
	rqst.target_id = shid->uid.target;
	rqst.command_id = SURFACE_KBD_CID_SET_CAPSLOCK_LED;
	rqst.instance_id = shid->uid.instance;
	rqst.flags = 0;
	rqst.length = माप(value_u8);
	rqst.payload = &value_u8;

	वापस ssam_retry(ssam_request_sync_onstack, shid->ctrl, &rqst, शून्य, माप(value_u8));
पूर्ण

अटल पूर्णांक ssam_kbd_get_feature_report(काष्ठा surface_hid_device *shid, u8 *buf, माप_प्रकार len)
अणु
	काष्ठा ssam_request rqst;
	काष्ठा ssam_response rsp;
	u8 payload = 0;
	पूर्णांक status;

	rqst.target_category = shid->uid.category;
	rqst.target_id = shid->uid.target;
	rqst.command_id = SURFACE_KBD_CID_GET_FEATURE_REPORT;
	rqst.instance_id = shid->uid.instance;
	rqst.flags = SSAM_REQUEST_HAS_RESPONSE;
	rqst.length = माप(payload);
	rqst.payload = &payload;

	rsp.capacity = len;
	rsp.length = 0;
	rsp.poपूर्णांकer = buf;

	status = ssam_retry(ssam_request_sync_onstack, shid->ctrl, &rqst, &rsp, माप(payload));
	अगर (status)
		वापस status;

	अगर (rsp.length != len) अणु
		dev_err(shid->dev, "invalid feature report length: got %zu, expected, %zu\n",
			rsp.length, len);
		वापस -EPROTO;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool ssam_kbd_is_input_event(स्थिर काष्ठा ssam_event *event)
अणु
	अगर (event->command_id == SURFACE_KBD_CID_EVT_INPUT_GENERIC)
		वापस true;

	अगर (event->command_id == SURFACE_KBD_CID_EVT_INPUT_HOTKEYS)
		वापस true;

	वापस false;
पूर्ण

अटल u32 ssam_kbd_event_fn(काष्ठा ssam_event_notअगरier *nf, स्थिर काष्ठा ssam_event *event)
अणु
	काष्ठा surface_hid_device *shid = container_of(nf, काष्ठा surface_hid_device, notअगर);

	/*
	 * Check against device UID manually, as registry and device target
	 * category करोesn't line up.
	 */

	अगर (shid->uid.category != event->target_category)
		वापस 0;

	अगर (shid->uid.target != event->target_id)
		वापस 0;

	अगर (shid->uid.instance != event->instance_id)
		वापस 0;

	अगर (!ssam_kbd_is_input_event(event))
		वापस 0;

	hid_input_report(shid->hid, HID_INPUT_REPORT, (u8 *)&event->data[0], event->length, 0);
	वापस SSAM_NOTIF_HANDLED;
पूर्ण


/* -- Transport driver (KBD). ----------------------------------------------- */

अटल पूर्णांक skbd_get_caps_led_value(काष्ठा hid_device *hid, u8 rprt_id, u8 *buf, माप_प्रकार len)
अणु
	काष्ठा hid_field *field;
	अचिन्हित पूर्णांक offset, size;
	पूर्णांक i;

	/* Get LED field. */
	field = hidinput_get_led_field(hid);
	अगर (!field)
		वापस -ENOENT;

	/* Check अगर we got the correct report. */
	अगर (len != hid_report_len(field->report))
		वापस -ENOENT;

	अगर (rprt_id != field->report->id)
		वापस -ENOENT;

	/* Get caps lock LED index. */
	क्रम (i = 0; i < field->report_count; i++)
		अगर ((field->usage[i].hid & 0xffff) == 0x02)
			अवरोध;

	अगर (i == field->report_count)
		वापस -ENOENT;

	/* Extract value. */
	size = field->report_size;
	offset = field->report_offset + i * size;
	वापस !!hid_field_extract(hid, buf + 1, size, offset);
पूर्ण

अटल पूर्णांक skbd_output_report(काष्ठा surface_hid_device *shid, u8 rprt_id, u8 *buf, माप_प्रकार len)
अणु
	पूर्णांक caps_led;
	पूर्णांक status;

	caps_led = skbd_get_caps_led_value(shid->hid, rprt_id, buf, len);
	अगर (caps_led < 0)
		वापस -EIO;  /* Only caps LED output reports are supported. */

	status = ssam_kbd_set_caps_led(shid, caps_led);
	अगर (status < 0)
		वापस status;

	वापस len;
पूर्ण

अटल पूर्णांक skbd_get_feature_report(काष्ठा surface_hid_device *shid, u8 rprt_id, u8 *buf, माप_प्रकार len)
अणु
	u8 report[KBD_FEATURE_REPORT_SIZE];
	पूर्णांक status;

	/*
	 * The keyboard only has a single hard-coded पढ़ो-only feature report
	 * of size KBD_FEATURE_REPORT_SIZE. Try to load it and compare its
	 * report ID against the requested one.
	 */

	अगर (len < ARRAY_SIZE(report))
		वापस -ENOSPC;

	status = ssam_kbd_get_feature_report(shid, report, ARRAY_SIZE(report));
	अगर (status < 0)
		वापस status;

	अगर (rprt_id != report[0])
		वापस -ENOENT;

	स_नकल(buf, report, ARRAY_SIZE(report));
	वापस len;
पूर्ण

अटल पूर्णांक skbd_set_feature_report(काष्ठा surface_hid_device *shid, u8 rprt_id, u8 *buf, माप_प्रकार len)
अणु
	/* Not supported. See skbd_get_feature_report() क्रम details. */
	वापस -EIO;
पूर्ण


/* -- Driver setup. --------------------------------------------------------- */

अटल पूर्णांक surface_kbd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ssam_controller *ctrl;
	काष्ठा surface_hid_device *shid;

	/* Add device link to EC. */
	ctrl = ssam_client_bind(&pdev->dev);
	अगर (IS_ERR(ctrl))
		वापस PTR_ERR(ctrl) == -ENODEV ? -EPROBE_DEFER : PTR_ERR(ctrl);

	shid = devm_kzalloc(&pdev->dev, माप(*shid), GFP_KERNEL);
	अगर (!shid)
		वापस -ENOMEM;

	shid->dev = &pdev->dev;
	shid->ctrl = ctrl;

	shid->uid.करोमुख्य = SSAM_DOMAIN_SERIALHUB;
	shid->uid.category = SSAM_SSH_TC_KBD;
	shid->uid.target = 2;
	shid->uid.instance = 0;
	shid->uid.function = 0;

	shid->notअगर.base.priority = 1;
	shid->notअगर.base.fn = ssam_kbd_event_fn;
	shid->notअगर.event.reg = SSAM_EVENT_REGISTRY_SAM;
	shid->notअगर.event.id.target_category = shid->uid.category;
	shid->notअगर.event.id.instance = shid->uid.instance;
	shid->notअगर.event.mask = SSAM_EVENT_MASK_NONE;
	shid->notअगर.event.flags = 0;

	shid->ops.get_descriptor = ssam_kbd_get_descriptor;
	shid->ops.output_report = skbd_output_report;
	shid->ops.get_feature_report = skbd_get_feature_report;
	shid->ops.set_feature_report = skbd_set_feature_report;

	platक्रमm_set_drvdata(pdev, shid);
	वापस surface_hid_device_add(shid);
पूर्ण

अटल पूर्णांक surface_kbd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	surface_hid_device_destroy(platक्रमm_get_drvdata(pdev));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id surface_kbd_match[] = अणु
	अणु "MSHW0096" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, surface_kbd_match);

अटल काष्ठा platक्रमm_driver surface_kbd_driver = अणु
	.probe = surface_kbd_probe,
	.हटाओ = surface_kbd_हटाओ,
	.driver = अणु
		.name = "surface_keyboard",
		.acpi_match_table = surface_kbd_match,
		.pm = &surface_hid_pm_ops,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(surface_kbd_driver);

MODULE_AUTHOR("Maximilian Luz <luzmaximilian@gmail.com>");
MODULE_DESCRIPTION("HID legacy transport driver for Surface System Aggregator Module");
MODULE_LICENSE("GPL");
