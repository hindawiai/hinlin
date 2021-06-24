<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 Google LLC
 *
 * Sysfs properties to view and modअगरy EC-controlled features on Wilco devices.
 * The entries will appear under /sys/bus/platक्रमm/devices/GOOG000C:00/
 *
 * See Documentation/ABI/testing/sysfs-platक्रमm-wilco-ec क्रम more inक्रमmation.
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_data/wilco-ec.h>
#समावेश <linux/माला.स>
#समावेश <linux/sysfs.h>
#समावेश <linux/types.h>

#घोषणा CMD_KB_CMOS			0x7C
#घोषणा SUB_CMD_KB_CMOS_AUTO_ON		0x03

काष्ठा boot_on_ac_request अणु
	u8 cmd;			/* Always CMD_KB_CMOS */
	u8 reserved1;
	u8 sub_cmd;		/* Always SUB_CMD_KB_CMOS_AUTO_ON */
	u8 reserved3to5[3];
	u8 val;			/* Either 0 or 1 */
	u8 reserved7;
पूर्ण __packed;

#घोषणा CMD_USB_CHARGE 0x39

क्रमागत usb_अक्षरge_op अणु
	USB_CHARGE_GET = 0,
	USB_CHARGE_SET = 1,
पूर्ण;

काष्ठा usb_अक्षरge_request अणु
	u8 cmd;		/* Always CMD_USB_CHARGE */
	u8 reserved;
	u8 op;		/* One of क्रमागत usb_अक्षरge_op */
	u8 val;		/* When setting, either 0 or 1 */
पूर्ण __packed;

काष्ठा usb_अक्षरge_response अणु
	u8 reserved;
	u8 status;	/* Set by EC to 0 on success, other value on failure */
	u8 val;		/* When getting, set by EC to either 0 or 1 */
पूर्ण __packed;

#घोषणा CMD_EC_INFO			0x38
क्रमागत get_ec_info_op अणु
	CMD_GET_EC_LABEL	= 0,
	CMD_GET_EC_REV		= 1,
	CMD_GET_EC_MODEL	= 2,
	CMD_GET_EC_BUILD_DATE	= 3,
पूर्ण;

काष्ठा get_ec_info_req अणु
	u8 cmd;			/* Always CMD_EC_INFO */
	u8 reserved;
	u8 op;			/* One of क्रमागत get_ec_info_op */
पूर्ण __packed;

काष्ठा get_ec_info_resp अणु
	u8 reserved[2];
	अक्षर value[9]; /* __nonstring: might not be null terminated */
पूर्ण __packed;

अटल sमाप_प्रकार boot_on_ac_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा wilco_ec_device *ec = dev_get_drvdata(dev);
	काष्ठा boot_on_ac_request rq;
	काष्ठा wilco_ec_message msg;
	पूर्णांक ret;
	u8 val;

	ret = kstrtou8(buf, 10, &val);
	अगर (ret < 0)
		वापस ret;
	अगर (val > 1)
		वापस -EINVAL;

	स_रखो(&rq, 0, माप(rq));
	rq.cmd = CMD_KB_CMOS;
	rq.sub_cmd = SUB_CMD_KB_CMOS_AUTO_ON;
	rq.val = val;

	स_रखो(&msg, 0, माप(msg));
	msg.type = WILCO_EC_MSG_LEGACY;
	msg.request_data = &rq;
	msg.request_size = माप(rq);
	ret = wilco_ec_mailbox(ec, &msg);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_WO(boot_on_ac);

अटल sमाप_प्रकार get_info(काष्ठा device *dev, अक्षर *buf, क्रमागत get_ec_info_op op)
अणु
	काष्ठा wilco_ec_device *ec = dev_get_drvdata(dev);
	काष्ठा get_ec_info_req req = अणु .cmd = CMD_EC_INFO, .op = op पूर्ण;
	काष्ठा get_ec_info_resp resp;
	पूर्णांक ret;

	काष्ठा wilco_ec_message msg = अणु
		.type = WILCO_EC_MSG_LEGACY,
		.request_data = &req,
		.request_size = माप(req),
		.response_data = &resp,
		.response_size = माप(resp),
	पूर्ण;

	ret = wilco_ec_mailbox(ec, &msg);
	अगर (ret < 0)
		वापस ret;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%.*s\n", (पूर्णांक)माप(resp.value),
			 (अक्षर *)&resp.value);
पूर्ण

अटल sमाप_प्रकार version_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	वापस get_info(dev, buf, CMD_GET_EC_LABEL);
पूर्ण

अटल DEVICE_ATTR_RO(version);

अटल sमाप_प्रकार build_revision_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस get_info(dev, buf, CMD_GET_EC_REV);
पूर्ण

अटल DEVICE_ATTR_RO(build_revision);

अटल sमाप_प्रकार build_date_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस get_info(dev, buf, CMD_GET_EC_BUILD_DATE);
पूर्ण

अटल DEVICE_ATTR_RO(build_date);

अटल sमाप_प्रकार model_number_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस get_info(dev, buf, CMD_GET_EC_MODEL);
पूर्ण

अटल DEVICE_ATTR_RO(model_number);

अटल पूर्णांक send_usb_अक्षरge(काष्ठा wilco_ec_device *ec,
				काष्ठा usb_अक्षरge_request *rq,
				काष्ठा usb_अक्षरge_response *rs)
अणु
	काष्ठा wilco_ec_message msg;
	पूर्णांक ret;

	स_रखो(&msg, 0, माप(msg));
	msg.type = WILCO_EC_MSG_LEGACY;
	msg.request_data = rq;
	msg.request_size = माप(*rq);
	msg.response_data = rs;
	msg.response_size = माप(*rs);
	ret = wilco_ec_mailbox(ec, &msg);
	अगर (ret < 0)
		वापस ret;
	अगर (rs->status)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार usb_अक्षरge_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा wilco_ec_device *ec = dev_get_drvdata(dev);
	काष्ठा usb_अक्षरge_request rq;
	काष्ठा usb_अक्षरge_response rs;
	पूर्णांक ret;

	स_रखो(&rq, 0, माप(rq));
	rq.cmd = CMD_USB_CHARGE;
	rq.op = USB_CHARGE_GET;

	ret = send_usb_अक्षरge(ec, &rq, &rs);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", rs.val);
पूर्ण

अटल sमाप_प्रकार usb_अक्षरge_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा wilco_ec_device *ec = dev_get_drvdata(dev);
	काष्ठा usb_अक्षरge_request rq;
	काष्ठा usb_अक्षरge_response rs;
	पूर्णांक ret;
	u8 val;

	ret = kstrtou8(buf, 10, &val);
	अगर (ret < 0)
		वापस ret;
	अगर (val > 1)
		वापस -EINVAL;

	स_रखो(&rq, 0, माप(rq));
	rq.cmd = CMD_USB_CHARGE;
	rq.op = USB_CHARGE_SET;
	rq.val = val;

	ret = send_usb_अक्षरge(ec, &rq, &rs);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(usb_अक्षरge);

अटल काष्ठा attribute *wilco_dev_attrs[] = अणु
	&dev_attr_boot_on_ac.attr,
	&dev_attr_build_date.attr,
	&dev_attr_build_revision.attr,
	&dev_attr_model_number.attr,
	&dev_attr_usb_अक्षरge.attr,
	&dev_attr_version.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group wilco_dev_attr_group = अणु
	.attrs = wilco_dev_attrs,
पूर्ण;

पूर्णांक wilco_ec_add_sysfs(काष्ठा wilco_ec_device *ec)
अणु
	वापस sysfs_create_group(&ec->dev->kobj, &wilco_dev_attr_group);
पूर्ण

व्योम wilco_ec_हटाओ_sysfs(काष्ठा wilco_ec_device *ec)
अणु
	sysfs_हटाओ_group(&ec->dev->kobj, &wilco_dev_attr_group);
पूर्ण
