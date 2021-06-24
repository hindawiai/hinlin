<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Common/core components क्रम the Surface System Aggregator Module (SSAM) HID
 * transport driver. Provides support क्रम पूर्णांकegrated HID devices on Microsoft
 * Surface models.
 *
 * Copyright (C) 2019-2021 Maximilian Luz <luzmaximilian@gmail.com>
 */

#अगर_अघोषित SURFACE_HID_CORE_H
#घोषणा SURFACE_HID_CORE_H

#समावेश <linux/hid.h>
#समावेश <linux/pm.h>
#समावेश <linux/types.h>

#समावेश <linux/surface_aggregator/controller.h>
#समावेश <linux/surface_aggregator/device.h>

क्रमागत surface_hid_descriptor_entry अणु
	SURFACE_HID_DESC_HID    = 0,
	SURFACE_HID_DESC_REPORT = 1,
	SURFACE_HID_DESC_ATTRS  = 2,
पूर्ण;

काष्ठा surface_hid_descriptor अणु
	__u8 desc_len;			/* = 9 */
	__u8 desc_type;			/* = HID_DT_HID */
	__le16 hid_version;
	__u8 country_code;
	__u8 num_descriptors;		/* = 1 */

	__u8 report_desc_type;		/* = HID_DT_REPORT */
	__le16 report_desc_len;
पूर्ण __packed;

अटल_निश्चित(माप(काष्ठा surface_hid_descriptor) == 9);

काष्ठा surface_hid_attributes अणु
	__le32 length;
	__le16 venकरोr;
	__le16 product;
	__le16 version;
	__u8 _unknown[22];
पूर्ण __packed;

अटल_निश्चित(माप(काष्ठा surface_hid_attributes) == 32);

काष्ठा surface_hid_device;

काष्ठा surface_hid_device_ops अणु
	पूर्णांक (*get_descriptor)(काष्ठा surface_hid_device *shid, u8 entry, u8 *buf, माप_प्रकार len);
	पूर्णांक (*output_report)(काष्ठा surface_hid_device *shid, u8 rprt_id, u8 *buf, माप_प्रकार len);
	पूर्णांक (*get_feature_report)(काष्ठा surface_hid_device *shid, u8 rprt_id, u8 *buf, माप_प्रकार len);
	पूर्णांक (*set_feature_report)(काष्ठा surface_hid_device *shid, u8 rprt_id, u8 *buf, माप_प्रकार len);
पूर्ण;

काष्ठा surface_hid_device अणु
	काष्ठा device *dev;
	काष्ठा ssam_controller *ctrl;
	काष्ठा ssam_device_uid uid;

	काष्ठा surface_hid_descriptor hid_desc;
	काष्ठा surface_hid_attributes attrs;

	काष्ठा ssam_event_notअगरier notअगर;
	काष्ठा hid_device *hid;

	काष्ठा surface_hid_device_ops ops;
पूर्ण;

पूर्णांक surface_hid_device_add(काष्ठा surface_hid_device *shid);
व्योम surface_hid_device_destroy(काष्ठा surface_hid_device *shid);

बाह्य स्थिर काष्ठा dev_pm_ops surface_hid_pm_ops;

#पूर्ण_अगर /* SURFACE_HID_CORE_H */
