<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Expose the vboot context nvram to userspace
//
// Copyright (C) 2012 Google, Inc.
// Copyright (C) 2015 Collabora Ltd.

#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/slab.h>

#घोषणा DRV_NAME "cros-ec-vbc"

अटल sमाप_प्रकार vboot_context_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
				  काष्ठा bin_attribute *att, अक्षर *buf,
				  loff_t pos, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा cros_ec_dev *ec = to_cros_ec_dev(dev);
	काष्ठा cros_ec_device *ecdev = ec->ec_dev;
	काष्ठा ec_params_vbnvcontext *params;
	काष्ठा cros_ec_command *msg;
	पूर्णांक err;
	स्थिर माप_प्रकार para_sz = माप(params->op);
	स्थिर माप_प्रकार resp_sz = माप(काष्ठा ec_response_vbnvcontext);
	स्थिर माप_प्रकार payload = max(para_sz, resp_sz);

	msg = kदो_स्मृति(माप(*msg) + payload, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	/* NB: we only kदो_स्मृति()ated enough space क्रम the op field */
	params = (काष्ठा ec_params_vbnvcontext *)msg->data;
	params->op = EC_VBNV_CONTEXT_OP_READ;

	msg->version = EC_VER_VBNV_CONTEXT;
	msg->command = EC_CMD_VBNV_CONTEXT;
	msg->outsize = para_sz;
	msg->insize = resp_sz;

	err = cros_ec_cmd_xfer_status(ecdev, msg);
	अगर (err < 0) अणु
		dev_err(dev, "Error sending read request: %d\n", err);
		kमुक्त(msg);
		वापस err;
	पूर्ण

	स_नकल(buf, msg->data, resp_sz);

	kमुक्त(msg);
	वापस resp_sz;
पूर्ण

अटल sमाप_प्रकार vboot_context_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
				   काष्ठा bin_attribute *attr, अक्षर *buf,
				   loff_t pos, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा cros_ec_dev *ec = to_cros_ec_dev(dev);
	काष्ठा cros_ec_device *ecdev = ec->ec_dev;
	काष्ठा ec_params_vbnvcontext *params;
	काष्ठा cros_ec_command *msg;
	पूर्णांक err;
	स्थिर माप_प्रकार para_sz = माप(*params);
	स्थिर माप_प्रकार data_sz = माप(params->block);

	/* Only ग_लिखो full values */
	अगर (count != data_sz)
		वापस -EINVAL;

	msg = kदो_स्मृति(माप(*msg) + para_sz, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	params = (काष्ठा ec_params_vbnvcontext *)msg->data;
	params->op = EC_VBNV_CONTEXT_OP_WRITE;
	स_नकल(params->block, buf, data_sz);

	msg->version = EC_VER_VBNV_CONTEXT;
	msg->command = EC_CMD_VBNV_CONTEXT;
	msg->outsize = para_sz;
	msg->insize = 0;

	err = cros_ec_cmd_xfer_status(ecdev, msg);
	अगर (err < 0) अणु
		dev_err(dev, "Error sending write request: %d\n", err);
		kमुक्त(msg);
		वापस err;
	पूर्ण

	kमुक्त(msg);
	वापस data_sz;
पूर्ण

अटल BIN_ATTR_RW(vboot_context, 16);

अटल काष्ठा bin_attribute *cros_ec_vbc_bin_attrs[] = अणु
	&bin_attr_vboot_context,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group cros_ec_vbc_attr_group = अणु
	.name = "vbc",
	.bin_attrs = cros_ec_vbc_bin_attrs,
पूर्ण;

अटल पूर्णांक cros_ec_vbc_probe(काष्ठा platक्रमm_device *pd)
अणु
	काष्ठा cros_ec_dev *ec_dev = dev_get_drvdata(pd->dev.parent);
	काष्ठा device *dev = &pd->dev;
	पूर्णांक ret;

	ret = sysfs_create_group(&ec_dev->class_dev.kobj,
				 &cros_ec_vbc_attr_group);
	अगर (ret < 0)
		dev_err(dev, "failed to create %s attributes. err=%d\n",
			cros_ec_vbc_attr_group.name, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक cros_ec_vbc_हटाओ(काष्ठा platक्रमm_device *pd)
अणु
	काष्ठा cros_ec_dev *ec_dev = dev_get_drvdata(pd->dev.parent);

	sysfs_हटाओ_group(&ec_dev->class_dev.kobj,
			   &cros_ec_vbc_attr_group);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cros_ec_vbc_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
	पूर्ण,
	.probe = cros_ec_vbc_probe,
	.हटाओ = cros_ec_vbc_हटाओ,
पूर्ण;

module_platक्रमm_driver(cros_ec_vbc_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Expose the vboot context nvram to userspace");
MODULE_ALIAS("platform:" DRV_NAME);
