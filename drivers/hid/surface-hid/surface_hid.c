<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Surface System Aggregator Module (SSAM) HID transport driver क्रम the
 * generic HID पूर्णांकerface (HID/TC=0x15 subप्रणाली). Provides support क्रम
 * पूर्णांकegrated HID devices on Surface Laptop 3, Book 3, and later.
 *
 * Copyright (C) 2019-2021 Blaधठ Hrastnik <blaz@mxxn.io>,
 *                         Maximilian Luz <luzmaximilian@gmail.com>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/hid.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>

#समावेश <linux/surface_aggregator/controller.h>
#समावेश <linux/surface_aggregator/device.h>

#समावेश "surface_hid_core.h"


/* -- SAM पूर्णांकerface. -------------------------------------------------------- */

काष्ठा surface_hid_buffer_slice अणु
	__u8 entry;
	__le32 offset;
	__le32 length;
	__u8 end;
	__u8 data[];
पूर्ण __packed;

अटल_निश्चित(माप(काष्ठा surface_hid_buffer_slice) == 10);

क्रमागत surface_hid_cid अणु
	SURFACE_HID_CID_OUTPUT_REPORT      = 0x01,
	SURFACE_HID_CID_GET_FEATURE_REPORT = 0x02,
	SURFACE_HID_CID_SET_FEATURE_REPORT = 0x03,
	SURFACE_HID_CID_GET_DESCRIPTOR     = 0x04,
पूर्ण;

अटल पूर्णांक ssam_hid_get_descriptor(काष्ठा surface_hid_device *shid, u8 entry, u8 *buf, माप_प्रकार len)
अणु
	u8 buffer[माप(काष्ठा surface_hid_buffer_slice) + 0x76];
	काष्ठा surface_hid_buffer_slice *slice;
	काष्ठा ssam_request rqst;
	काष्ठा ssam_response rsp;
	u32 buffer_len, offset, length;
	पूर्णांक status;

	/*
	 * Note: The 0x76 above has been chosen because that's what's used by
	 * the Winकरोws driver. Together with the header, this leads to a 128
	 * byte payload in total.
	 */

	buffer_len = ARRAY_SIZE(buffer) - माप(काष्ठा surface_hid_buffer_slice);

	rqst.target_category = shid->uid.category;
	rqst.target_id = shid->uid.target;
	rqst.command_id = SURFACE_HID_CID_GET_DESCRIPTOR;
	rqst.instance_id = shid->uid.instance;
	rqst.flags = SSAM_REQUEST_HAS_RESPONSE;
	rqst.length = माप(काष्ठा surface_hid_buffer_slice);
	rqst.payload = buffer;

	rsp.capacity = ARRAY_SIZE(buffer);
	rsp.poपूर्णांकer = buffer;

	slice = (काष्ठा surface_hid_buffer_slice *)buffer;
	slice->entry = entry;
	slice->end = 0;

	offset = 0;
	length = buffer_len;

	जबतक (!slice->end && offset < len) अणु
		put_unaligned_le32(offset, &slice->offset);
		put_unaligned_le32(length, &slice->length);

		rsp.length = 0;

		status = ssam_retry(ssam_request_sync_onstack, shid->ctrl, &rqst, &rsp,
				    माप(*slice));
		अगर (status)
			वापस status;

		offset = get_unaligned_le32(&slice->offset);
		length = get_unaligned_le32(&slice->length);

		/* Don't mess stuff up in हाल we receive garbage. */
		अगर (length > buffer_len || offset > len)
			वापस -EPROTO;

		अगर (offset + length > len)
			length = len - offset;

		स_नकल(buf + offset, &slice->data[0], length);

		offset += length;
		length = buffer_len;
	पूर्ण

	अगर (offset != len) अणु
		dev_err(shid->dev, "unexpected descriptor length: got %u, expected %zu\n",
			offset, len);
		वापस -EPROTO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ssam_hid_set_raw_report(काष्ठा surface_hid_device *shid, u8 rprt_id, bool feature,
				   u8 *buf, माप_प्रकार len)
अणु
	काष्ठा ssam_request rqst;
	u8 cid;

	अगर (feature)
		cid = SURFACE_HID_CID_SET_FEATURE_REPORT;
	अन्यथा
		cid = SURFACE_HID_CID_OUTPUT_REPORT;

	rqst.target_category = shid->uid.category;
	rqst.target_id = shid->uid.target;
	rqst.instance_id = shid->uid.instance;
	rqst.command_id = cid;
	rqst.flags = 0;
	rqst.length = len;
	rqst.payload = buf;

	buf[0] = rprt_id;

	वापस ssam_retry(ssam_request_sync, shid->ctrl, &rqst, शून्य);
पूर्ण

अटल पूर्णांक ssam_hid_get_raw_report(काष्ठा surface_hid_device *shid, u8 rprt_id, u8 *buf, माप_प्रकार len)
अणु
	काष्ठा ssam_request rqst;
	काष्ठा ssam_response rsp;

	rqst.target_category = shid->uid.category;
	rqst.target_id = shid->uid.target;
	rqst.instance_id = shid->uid.instance;
	rqst.command_id = SURFACE_HID_CID_GET_FEATURE_REPORT;
	rqst.flags = 0;
	rqst.length = माप(rprt_id);
	rqst.payload = &rprt_id;

	rsp.capacity = len;
	rsp.length = 0;
	rsp.poपूर्णांकer = buf;

	वापस ssam_retry(ssam_request_sync_onstack, shid->ctrl, &rqst, &rsp, माप(rprt_id));
पूर्ण

अटल u32 ssam_hid_event_fn(काष्ठा ssam_event_notअगरier *nf, स्थिर काष्ठा ssam_event *event)
अणु
	काष्ठा surface_hid_device *shid = container_of(nf, काष्ठा surface_hid_device, notअगर);

	अगर (event->command_id != 0x00)
		वापस 0;

	hid_input_report(shid->hid, HID_INPUT_REPORT, (u8 *)&event->data[0], event->length, 0);
	वापस SSAM_NOTIF_HANDLED;
पूर्ण


/* -- Transport driver. ----------------------------------------------------- */

अटल पूर्णांक shid_output_report(काष्ठा surface_hid_device *shid, u8 rprt_id, u8 *buf, माप_प्रकार len)
अणु
	पूर्णांक status;

	status = ssam_hid_set_raw_report(shid, rprt_id, false, buf, len);
	वापस status >= 0 ? len : status;
पूर्ण

अटल पूर्णांक shid_get_feature_report(काष्ठा surface_hid_device *shid, u8 rprt_id, u8 *buf, माप_प्रकार len)
अणु
	पूर्णांक status;

	status = ssam_hid_get_raw_report(shid, rprt_id, buf, len);
	वापस status >= 0 ? len : status;
पूर्ण

अटल पूर्णांक shid_set_feature_report(काष्ठा surface_hid_device *shid, u8 rprt_id, u8 *buf, माप_प्रकार len)
अणु
	पूर्णांक status;

	status = ssam_hid_set_raw_report(shid, rprt_id, true, buf, len);
	वापस status >= 0 ? len : status;
पूर्ण


/* -- Driver setup. --------------------------------------------------------- */

अटल पूर्णांक surface_hid_probe(काष्ठा ssam_device *sdev)
अणु
	काष्ठा surface_hid_device *shid;

	shid = devm_kzalloc(&sdev->dev, माप(*shid), GFP_KERNEL);
	अगर (!shid)
		वापस -ENOMEM;

	shid->dev = &sdev->dev;
	shid->ctrl = sdev->ctrl;
	shid->uid = sdev->uid;

	shid->notअगर.base.priority = 1;
	shid->notअगर.base.fn = ssam_hid_event_fn;
	shid->notअगर.event.reg = SSAM_EVENT_REGISTRY_REG;
	shid->notअगर.event.id.target_category = sdev->uid.category;
	shid->notअगर.event.id.instance = sdev->uid.instance;
	shid->notअगर.event.mask = SSAM_EVENT_MASK_STRICT;
	shid->notअगर.event.flags = 0;

	shid->ops.get_descriptor = ssam_hid_get_descriptor;
	shid->ops.output_report = shid_output_report;
	shid->ops.get_feature_report = shid_get_feature_report;
	shid->ops.set_feature_report = shid_set_feature_report;

	ssam_device_set_drvdata(sdev, shid);
	वापस surface_hid_device_add(shid);
पूर्ण

अटल व्योम surface_hid_हटाओ(काष्ठा ssam_device *sdev)
अणु
	surface_hid_device_destroy(ssam_device_get_drvdata(sdev));
पूर्ण

अटल स्थिर काष्ठा ssam_device_id surface_hid_match[] = अणु
	अणु SSAM_SDEV(HID, 0x02, SSAM_ANY_IID, 0x00) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(ssam, surface_hid_match);

अटल काष्ठा ssam_device_driver surface_hid_driver = अणु
	.probe = surface_hid_probe,
	.हटाओ = surface_hid_हटाओ,
	.match_table = surface_hid_match,
	.driver = अणु
		.name = "surface_hid",
		.pm = &surface_hid_pm_ops,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;
module_ssam_device_driver(surface_hid_driver);

MODULE_AUTHOR("Blaधठ Hrastnik <blaz@mxxn.io>");
MODULE_AUTHOR("Maximilian Luz <luzmaximilian@gmail.com>");
MODULE_DESCRIPTION("HID transport driver for Surface System Aggregator Module");
MODULE_LICENSE("GPL");
