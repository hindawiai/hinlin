<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Expose the ChromeOS EC through sysfs
//
// Copyright (C) 2014 Google, Inc.

#समावेश <linux/प्रकार.स>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/kobject.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>

#घोषणा DRV_NAME "cros-ec-sysfs"

/* Accessor functions */

अटल sमाप_प्रकार reboot_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक count = 0;

	count += scnम_लिखो(buf + count, PAGE_SIZE - count,
			   "ro|rw|cancel|cold|disable-jump|hibernate|cold-ap-off");
	count += scnम_लिखो(buf + count, PAGE_SIZE - count,
			   " [at-shutdown]\n");
	वापस count;
पूर्ण

अटल sमाप_प्रकार reboot_store(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अटल स्थिर काष्ठा अणु
		स्थिर अक्षर * स्थिर str;
		uपूर्णांक8_t cmd;
		uपूर्णांक8_t flags;
	पूर्ण words[] = अणु
		अणु"cancel",       EC_REBOOT_CANCEL, 0पूर्ण,
		अणु"ro",           EC_REBOOT_JUMP_RO, 0पूर्ण,
		अणु"rw",           EC_REBOOT_JUMP_RW, 0पूर्ण,
		अणु"cold-ap-off",  EC_REBOOT_COLD_AP_OFF, 0पूर्ण,
		अणु"cold",         EC_REBOOT_COLD, 0पूर्ण,
		अणु"disable-jump", EC_REBOOT_DISABLE_JUMP, 0पूर्ण,
		अणु"hibernate",    EC_REBOOT_HIBERNATE, 0पूर्ण,
		अणु"at-shutdown",  -1, EC_REBOOT_FLAG_ON_AP_SHUTDOWNपूर्ण,
	पूर्ण;
	काष्ठा cros_ec_command *msg;
	काष्ठा ec_params_reboot_ec *param;
	पूर्णांक got_cmd = 0, offset = 0;
	पूर्णांक i;
	पूर्णांक ret;
	काष्ठा cros_ec_dev *ec = to_cros_ec_dev(dev);

	msg = kदो_स्मृति(माप(*msg) + माप(*param), GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	param = (काष्ठा ec_params_reboot_ec *)msg->data;

	param->flags = 0;
	जबतक (1) अणु
		/* Find word to start scanning */
		जबतक (buf[offset] && है_खाली(buf[offset]))
			offset++;
		अगर (!buf[offset])
			अवरोध;

		क्रम (i = 0; i < ARRAY_SIZE(words); i++) अणु
			अगर (!strnहालcmp(words[i].str, buf+offset,
					 म_माप(words[i].str))) अणु
				अगर (words[i].flags) अणु
					param->flags |= words[i].flags;
				पूर्ण अन्यथा अणु
					param->cmd = words[i].cmd;
					got_cmd = 1;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण

		/* On to the next word, अगर any */
		जबतक (buf[offset] && !है_खाली(buf[offset]))
			offset++;
	पूर्ण

	अगर (!got_cmd) अणु
		count = -EINVAL;
		जाओ निकास;
	पूर्ण

	msg->version = 0;
	msg->command = EC_CMD_REBOOT_EC + ec->cmd_offset;
	msg->outsize = माप(*param);
	msg->insize = 0;
	ret = cros_ec_cmd_xfer_status(ec->ec_dev, msg);
	अगर (ret < 0)
		count = ret;
निकास:
	kमुक्त(msg);
	वापस count;
पूर्ण

अटल sमाप_प्रकार version_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अटल स्थिर अक्षर * स्थिर image_names[] = अणु"unknown", "RO", "RW"पूर्ण;
	काष्ठा ec_response_get_version *r_ver;
	काष्ठा ec_response_get_chip_info *r_chip;
	काष्ठा ec_response_board_version *r_board;
	काष्ठा cros_ec_command *msg;
	पूर्णांक ret;
	पूर्णांक count = 0;
	काष्ठा cros_ec_dev *ec = to_cros_ec_dev(dev);

	msg = kदो_स्मृति(माप(*msg) + EC_HOST_PARAM_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	/* Get versions. RW may change. */
	msg->version = 0;
	msg->command = EC_CMD_GET_VERSION + ec->cmd_offset;
	msg->insize = माप(*r_ver);
	msg->outsize = 0;
	ret = cros_ec_cmd_xfer_status(ec->ec_dev, msg);
	अगर (ret < 0) अणु
		count = ret;
		जाओ निकास;
	पूर्ण
	r_ver = (काष्ठा ec_response_get_version *)msg->data;
	/* Strings should be null-terminated, but let's be sure. */
	r_ver->version_string_ro[माप(r_ver->version_string_ro) - 1] = '\0';
	r_ver->version_string_rw[माप(r_ver->version_string_rw) - 1] = '\0';
	count += scnम_लिखो(buf + count, PAGE_SIZE - count,
			   "RO version:    %s\n", r_ver->version_string_ro);
	count += scnम_लिखो(buf + count, PAGE_SIZE - count,
			   "RW version:    %s\n", r_ver->version_string_rw);
	count += scnम_लिखो(buf + count, PAGE_SIZE - count,
			   "Firmware copy: %s\n",
			   (r_ver->current_image < ARRAY_SIZE(image_names) ?
			    image_names[r_ver->current_image] : "?"));

	/* Get build info. */
	msg->command = EC_CMD_GET_BUILD_INFO + ec->cmd_offset;
	msg->insize = EC_HOST_PARAM_SIZE;
	ret = cros_ec_cmd_xfer_status(ec->ec_dev, msg);
	अगर (ret < 0) अणु
		count += scnम_लिखो(buf + count, PAGE_SIZE - count,
				   "Build info:    XFER / EC ERROR %d / %d\n",
				   ret, msg->result);
	पूर्ण अन्यथा अणु
		msg->data[EC_HOST_PARAM_SIZE - 1] = '\0';
		count += scnम_लिखो(buf + count, PAGE_SIZE - count,
				   "Build info:    %s\n", msg->data);
	पूर्ण

	/* Get chip info. */
	msg->command = EC_CMD_GET_CHIP_INFO + ec->cmd_offset;
	msg->insize = माप(*r_chip);
	ret = cros_ec_cmd_xfer_status(ec->ec_dev, msg);
	अगर (ret < 0) अणु
		count += scnम_लिखो(buf + count, PAGE_SIZE - count,
				   "Chip info:     XFER / EC ERROR %d / %d\n",
				   ret, msg->result);
	पूर्ण अन्यथा अणु
		r_chip = (काष्ठा ec_response_get_chip_info *)msg->data;

		r_chip->venकरोr[माप(r_chip->venकरोr) - 1] = '\0';
		r_chip->name[माप(r_chip->name) - 1] = '\0';
		r_chip->revision[माप(r_chip->revision) - 1] = '\0';
		count += scnम_लिखो(buf + count, PAGE_SIZE - count,
				   "Chip vendor:   %s\n", r_chip->venकरोr);
		count += scnम_लिखो(buf + count, PAGE_SIZE - count,
				   "Chip name:     %s\n", r_chip->name);
		count += scnम_लिखो(buf + count, PAGE_SIZE - count,
				   "Chip revision: %s\n", r_chip->revision);
	पूर्ण

	/* Get board version */
	msg->command = EC_CMD_GET_BOARD_VERSION + ec->cmd_offset;
	msg->insize = माप(*r_board);
	ret = cros_ec_cmd_xfer_status(ec->ec_dev, msg);
	अगर (ret < 0) अणु
		count += scnम_लिखो(buf + count, PAGE_SIZE - count,
				   "Board version: XFER / EC ERROR %d / %d\n",
				   ret, msg->result);
	पूर्ण अन्यथा अणु
		r_board = (काष्ठा ec_response_board_version *)msg->data;

		count += scnम_लिखो(buf + count, PAGE_SIZE - count,
				   "Board version: %d\n",
				   r_board->board_version);
	पूर्ण

निकास:
	kमुक्त(msg);
	वापस count;
पूर्ण

अटल sमाप_प्रकार flashinfo_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ec_response_flash_info *resp;
	काष्ठा cros_ec_command *msg;
	पूर्णांक ret;
	काष्ठा cros_ec_dev *ec = to_cros_ec_dev(dev);

	msg = kदो_स्मृति(माप(*msg) + माप(*resp), GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	/* The flash info shouldn't ever change, but ask each समय anyway. */
	msg->version = 0;
	msg->command = EC_CMD_FLASH_INFO + ec->cmd_offset;
	msg->insize = माप(*resp);
	msg->outsize = 0;
	ret = cros_ec_cmd_xfer_status(ec->ec_dev, msg);
	अगर (ret < 0)
		जाओ निकास;

	resp = (काष्ठा ec_response_flash_info *)msg->data;

	ret = scnम_लिखो(buf, PAGE_SIZE,
			"FlashSize %d\nWriteSize %d\n"
			"EraseSize %d\nProtectSize %d\n",
			resp->flash_size, resp->ग_लिखो_block_size,
			resp->erase_block_size, resp->protect_block_size);
निकास:
	kमुक्त(msg);
	वापस ret;
पूर्ण

/* Keyboard wake angle control */
अटल sमाप_प्रकार kb_wake_angle_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cros_ec_dev *ec = to_cros_ec_dev(dev);
	काष्ठा ec_response_motion_sense *resp;
	काष्ठा ec_params_motion_sense *param;
	काष्ठा cros_ec_command *msg;
	पूर्णांक ret;

	msg = kदो_स्मृति(माप(*msg) + EC_HOST_PARAM_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	param = (काष्ठा ec_params_motion_sense *)msg->data;
	msg->command = EC_CMD_MOTION_SENSE_CMD + ec->cmd_offset;
	msg->version = 2;
	param->cmd = MOTIONSENSE_CMD_KB_WAKE_ANGLE;
	param->kb_wake_angle.data = EC_MOTION_SENSE_NO_VALUE;
	msg->outsize = माप(*param);
	msg->insize = माप(*resp);

	ret = cros_ec_cmd_xfer_status(ec->ec_dev, msg);
	अगर (ret < 0)
		जाओ निकास;

	resp = (काष्ठा ec_response_motion_sense *)msg->data;
	ret = scnम_लिखो(buf, PAGE_SIZE, "%d\n", resp->kb_wake_angle.ret);
निकास:
	kमुक्त(msg);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार kb_wake_angle_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cros_ec_dev *ec = to_cros_ec_dev(dev);
	काष्ठा ec_params_motion_sense *param;
	काष्ठा cros_ec_command *msg;
	u16 angle;
	पूर्णांक ret;

	ret = kstrtou16(buf, 0, &angle);
	अगर (ret)
		वापस ret;

	msg = kदो_स्मृति(माप(*msg) + EC_HOST_PARAM_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	param = (काष्ठा ec_params_motion_sense *)msg->data;
	msg->command = EC_CMD_MOTION_SENSE_CMD + ec->cmd_offset;
	msg->version = 2;
	param->cmd = MOTIONSENSE_CMD_KB_WAKE_ANGLE;
	param->kb_wake_angle.data = angle;
	msg->outsize = माप(*param);
	msg->insize = माप(काष्ठा ec_response_motion_sense);

	ret = cros_ec_cmd_xfer_status(ec->ec_dev, msg);
	kमुक्त(msg);
	अगर (ret < 0)
		वापस ret;
	वापस count;
पूर्ण

/* Module initialization */

अटल DEVICE_ATTR_RW(reboot);
अटल DEVICE_ATTR_RO(version);
अटल DEVICE_ATTR_RO(flashinfo);
अटल DEVICE_ATTR_RW(kb_wake_angle);

अटल काष्ठा attribute *__ec_attrs[] = अणु
	&dev_attr_kb_wake_angle.attr,
	&dev_attr_reboot.attr,
	&dev_attr_version.attr,
	&dev_attr_flashinfo.attr,
	शून्य,
पूर्ण;

अटल umode_t cros_ec_ctrl_visible(काष्ठा kobject *kobj,
				    काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा cros_ec_dev *ec = to_cros_ec_dev(dev);

	अगर (a == &dev_attr_kb_wake_angle.attr && !ec->has_kb_wake_angle)
		वापस 0;

	वापस a->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group cros_ec_attr_group = अणु
	.attrs = __ec_attrs,
	.is_visible = cros_ec_ctrl_visible,
पूर्ण;

अटल पूर्णांक cros_ec_sysfs_probe(काष्ठा platक्रमm_device *pd)
अणु
	काष्ठा cros_ec_dev *ec_dev = dev_get_drvdata(pd->dev.parent);
	काष्ठा device *dev = &pd->dev;
	पूर्णांक ret;

	ret = sysfs_create_group(&ec_dev->class_dev.kobj, &cros_ec_attr_group);
	अगर (ret < 0)
		dev_err(dev, "failed to create attributes. err=%d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक cros_ec_sysfs_हटाओ(काष्ठा platक्रमm_device *pd)
अणु
	काष्ठा cros_ec_dev *ec_dev = dev_get_drvdata(pd->dev.parent);

	sysfs_हटाओ_group(&ec_dev->class_dev.kobj, &cros_ec_attr_group);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cros_ec_sysfs_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
	पूर्ण,
	.probe = cros_ec_sysfs_probe,
	.हटाओ = cros_ec_sysfs_हटाओ,
पूर्ण;

module_platक्रमm_driver(cros_ec_sysfs_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Expose the ChromeOS EC through sysfs");
MODULE_ALIAS("platform:" DRV_NAME);
