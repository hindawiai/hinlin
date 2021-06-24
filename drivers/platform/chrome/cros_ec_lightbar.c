<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Expose the Chromebook Pixel lightbar to userspace
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
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>

#घोषणा DRV_NAME "cros-ec-lightbar"

/* Rate-limit the lightbar पूर्णांकerface to prevent DoS. */
अटल अचिन्हित दीर्घ lb_पूर्णांकerval_jअगरfies = 50 * HZ / 1000;

/*
 * Whether or not we have given userspace control of the lightbar.
 * If this is true, we won't करो anything during suspend/resume.
 */
अटल bool userspace_control;

अटल sमाप_प्रकार पूर्णांकerval_msec_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ msec = lb_पूर्णांकerval_jअगरfies * 1000 / HZ;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%lu\n", msec);
पूर्ण

अटल sमाप_प्रकार पूर्णांकerval_msec_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ msec;

	अगर (kम_से_अदीर्घ(buf, 0, &msec))
		वापस -EINVAL;

	lb_पूर्णांकerval_jअगरfies = msec * HZ / 1000;

	वापस count;
पूर्ण

अटल DEFINE_MUTEX(lb_mutex);
/* Return 0 अगर able to throttle correctly, error otherwise */
अटल पूर्णांक lb_throttle(व्योम)
अणु
	अटल अचिन्हित दीर्घ last_access;
	अचिन्हित दीर्घ now, next_बारlot;
	दीर्घ delay;
	पूर्णांक ret = 0;

	mutex_lock(&lb_mutex);

	now = jअगरfies;
	next_बारlot = last_access + lb_पूर्णांकerval_jअगरfies;

	अगर (समय_beक्रमe(now, next_बारlot)) अणु
		delay = (दीर्घ)(next_बारlot) - (दीर्घ)now;
		set_current_state(TASK_INTERRUPTIBLE);
		अगर (schedule_समयout(delay) > 0) अणु
			/* पूर्णांकerrupted - just पात */
			ret = -EINTR;
			जाओ out;
		पूर्ण
		now = jअगरfies;
	पूर्ण

	last_access = now;
out:
	mutex_unlock(&lb_mutex);

	वापस ret;
पूर्ण

अटल काष्ठा cros_ec_command *alloc_lightbar_cmd_msg(काष्ठा cros_ec_dev *ec)
अणु
	काष्ठा cros_ec_command *msg;
	पूर्णांक len;

	len = max(माप(काष्ठा ec_params_lightbar),
		  माप(काष्ठा ec_response_lightbar));

	msg = kदो_स्मृति(माप(*msg) + len, GFP_KERNEL);
	अगर (!msg)
		वापस शून्य;

	msg->version = 0;
	msg->command = EC_CMD_LIGHTBAR_CMD + ec->cmd_offset;
	msg->outsize = माप(काष्ठा ec_params_lightbar);
	msg->insize = माप(काष्ठा ec_response_lightbar);

	वापस msg;
पूर्ण

अटल पूर्णांक get_lightbar_version(काष्ठा cros_ec_dev *ec,
				uपूर्णांक32_t *ver_ptr, uपूर्णांक32_t *flg_ptr)
अणु
	काष्ठा ec_params_lightbar *param;
	काष्ठा ec_response_lightbar *resp;
	काष्ठा cros_ec_command *msg;
	पूर्णांक ret;

	msg = alloc_lightbar_cmd_msg(ec);
	अगर (!msg)
		वापस 0;

	param = (काष्ठा ec_params_lightbar *)msg->data;
	param->cmd = LIGHTBAR_CMD_VERSION;
	msg->outsize = माप(param->cmd);
	msg->result = माप(resp->version);
	ret = cros_ec_cmd_xfer_status(ec->ec_dev, msg);
	अगर (ret < 0 && ret != -EINVAL) अणु
		ret = 0;
		जाओ निकास;
	पूर्ण

	चयन (msg->result) अणु
	हाल EC_RES_INVALID_PARAM:
		/* Pixel had no version command. */
		अगर (ver_ptr)
			*ver_ptr = 0;
		अगर (flg_ptr)
			*flg_ptr = 0;
		ret = 1;
		जाओ निकास;

	हाल EC_RES_SUCCESS:
		resp = (काष्ठा ec_response_lightbar *)msg->data;

		/* Future devices w/lightbars should implement this command */
		अगर (ver_ptr)
			*ver_ptr = resp->version.num;
		अगर (flg_ptr)
			*flg_ptr = resp->version.flags;
		ret = 1;
		जाओ निकास;
	पूर्ण

	/* Anything अन्यथा (ie, EC_RES_INVALID_COMMAND) - no lightbar */
	ret = 0;
निकास:
	kमुक्त(msg);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार version_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	uपूर्णांक32_t version = 0, flags = 0;
	काष्ठा cros_ec_dev *ec = to_cros_ec_dev(dev);
	पूर्णांक ret;

	ret = lb_throttle();
	अगर (ret)
		वापस ret;

	/* This should always succeed, because we check during init. */
	अगर (!get_lightbar_version(ec, &version, &flags))
		वापस -EIO;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d %d\n", version, flags);
पूर्ण

अटल sमाप_प्रकार brightness_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ec_params_lightbar *param;
	काष्ठा cros_ec_command *msg;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;
	काष्ठा cros_ec_dev *ec = to_cros_ec_dev(dev);

	अगर (kstrtouपूर्णांक(buf, 0, &val))
		वापस -EINVAL;

	msg = alloc_lightbar_cmd_msg(ec);
	अगर (!msg)
		वापस -ENOMEM;

	param = (काष्ठा ec_params_lightbar *)msg->data;
	param->cmd = LIGHTBAR_CMD_SET_BRIGHTNESS;
	param->set_brightness.num = val;
	ret = lb_throttle();
	अगर (ret)
		जाओ निकास;

	ret = cros_ec_cmd_xfer_status(ec->ec_dev, msg);
	अगर (ret < 0)
		जाओ निकास;

	ret = count;
निकास:
	kमुक्त(msg);
	वापस ret;
पूर्ण


/*
 * We expect numbers, and we'll keep पढ़ोing until we find them, skipping over
 * any whitespace (sysfs guarantees that the input is null-terminated). Every
 * four numbers are sent to the lightbar as <LED,R,G,B>. We fail at the first
 * parsing error, अगर we करोn't parse any numbers, or अगर we have numbers left
 * over.
 */
अटल sमाप_प्रकार led_rgb_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ec_params_lightbar *param;
	काष्ठा cros_ec_command *msg;
	काष्ठा cros_ec_dev *ec = to_cros_ec_dev(dev);
	अचिन्हित पूर्णांक val[4];
	पूर्णांक ret, i = 0, j = 0, ok = 0;

	msg = alloc_lightbar_cmd_msg(ec);
	अगर (!msg)
		वापस -ENOMEM;

	करो अणु
		/* Skip any whitespace */
		जबतक (*buf && है_खाली(*buf))
			buf++;

		अगर (!*buf)
			अवरोध;

		ret = माला_पूछो(buf, "%i", &val[i++]);
		अगर (ret == 0)
			जाओ निकास;

		अगर (i == 4) अणु
			param = (काष्ठा ec_params_lightbar *)msg->data;
			param->cmd = LIGHTBAR_CMD_SET_RGB;
			param->set_rgb.led = val[0];
			param->set_rgb.red = val[1];
			param->set_rgb.green = val[2];
			param->set_rgb.blue = val[3];
			/*
			 * Throttle only the first of every four transactions,
			 * so that the user can update all four LEDs at once.
			 */
			अगर ((j++ % 4) == 0) अणु
				ret = lb_throttle();
				अगर (ret)
					जाओ निकास;
			पूर्ण

			ret = cros_ec_cmd_xfer_status(ec->ec_dev, msg);
			अगर (ret < 0)
				जाओ निकास;

			i = 0;
			ok = 1;
		पूर्ण

		/* Skip over the number we just पढ़ो */
		जबतक (*buf && !है_खाली(*buf))
			buf++;

	पूर्ण जबतक (*buf);

निकास:
	kमुक्त(msg);
	वापस (ok && i == 0) ? count : -EINVAL;
पूर्ण

अटल अक्षर स्थिर *seqname[] = अणु
	"ERROR", "S5", "S3", "S0", "S5S3", "S3S0",
	"S0S3", "S3S5", "STOP", "RUN", "KONAMI",
	"TAP", "PROGRAM",
पूर्ण;

अटल sमाप_प्रकार sequence_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ec_params_lightbar *param;
	काष्ठा ec_response_lightbar *resp;
	काष्ठा cros_ec_command *msg;
	पूर्णांक ret;
	काष्ठा cros_ec_dev *ec = to_cros_ec_dev(dev);

	msg = alloc_lightbar_cmd_msg(ec);
	अगर (!msg)
		वापस -ENOMEM;

	param = (काष्ठा ec_params_lightbar *)msg->data;
	param->cmd = LIGHTBAR_CMD_GET_SEQ;
	ret = lb_throttle();
	अगर (ret)
		जाओ निकास;

	ret = cros_ec_cmd_xfer_status(ec->ec_dev, msg);
	अगर (ret < 0) अणु
		ret = scnम_लिखो(buf, PAGE_SIZE, "XFER / EC ERROR %d / %d\n",
				ret, msg->result);
		जाओ निकास;
	पूर्ण

	resp = (काष्ठा ec_response_lightbar *)msg->data;
	अगर (resp->get_seq.num >= ARRAY_SIZE(seqname))
		ret = scnम_लिखो(buf, PAGE_SIZE, "%d\n", resp->get_seq.num);
	अन्यथा
		ret = scnम_लिखो(buf, PAGE_SIZE, "%s\n",
				seqname[resp->get_seq.num]);

निकास:
	kमुक्त(msg);
	वापस ret;
पूर्ण

अटल पूर्णांक lb_send_empty_cmd(काष्ठा cros_ec_dev *ec, uपूर्णांक8_t cmd)
अणु
	काष्ठा ec_params_lightbar *param;
	काष्ठा cros_ec_command *msg;
	पूर्णांक ret;

	msg = alloc_lightbar_cmd_msg(ec);
	अगर (!msg)
		वापस -ENOMEM;

	param = (काष्ठा ec_params_lightbar *)msg->data;
	param->cmd = cmd;

	ret = lb_throttle();
	अगर (ret)
		जाओ error;

	ret = cros_ec_cmd_xfer_status(ec->ec_dev, msg);
	अगर (ret < 0)
		जाओ error;

	ret = 0;
error:
	kमुक्त(msg);

	वापस ret;
पूर्ण

अटल पूर्णांक lb_manual_suspend_ctrl(काष्ठा cros_ec_dev *ec, uपूर्णांक8_t enable)
अणु
	काष्ठा ec_params_lightbar *param;
	काष्ठा cros_ec_command *msg;
	पूर्णांक ret;

	msg = alloc_lightbar_cmd_msg(ec);
	अगर (!msg)
		वापस -ENOMEM;

	param = (काष्ठा ec_params_lightbar *)msg->data;

	param->cmd = LIGHTBAR_CMD_MANUAL_SUSPEND_CTRL;
	param->manual_suspend_ctrl.enable = enable;

	ret = lb_throttle();
	अगर (ret)
		जाओ error;

	ret = cros_ec_cmd_xfer_status(ec->ec_dev, msg);
	अगर (ret < 0)
		जाओ error;

	ret = 0;
error:
	kमुक्त(msg);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार sequence_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ec_params_lightbar *param;
	काष्ठा cros_ec_command *msg;
	अचिन्हित पूर्णांक num;
	पूर्णांक ret, len;
	काष्ठा cros_ec_dev *ec = to_cros_ec_dev(dev);

	क्रम (len = 0; len < count; len++)
		अगर (!है_अक्षर_अंक(buf[len]))
			अवरोध;

	क्रम (num = 0; num < ARRAY_SIZE(seqname); num++)
		अगर (!strnहालcmp(seqname[num], buf, len))
			अवरोध;

	अगर (num >= ARRAY_SIZE(seqname)) अणु
		ret = kstrtouपूर्णांक(buf, 0, &num);
		अगर (ret)
			वापस ret;
	पूर्ण

	msg = alloc_lightbar_cmd_msg(ec);
	अगर (!msg)
		वापस -ENOMEM;

	param = (काष्ठा ec_params_lightbar *)msg->data;
	param->cmd = LIGHTBAR_CMD_SEQ;
	param->seq.num = num;
	ret = lb_throttle();
	अगर (ret)
		जाओ निकास;

	ret = cros_ec_cmd_xfer_status(ec->ec_dev, msg);
	अगर (ret < 0)
		जाओ निकास;

	ret = count;
निकास:
	kमुक्त(msg);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार program_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक extra_bytes, max_size, ret;
	काष्ठा ec_params_lightbar *param;
	काष्ठा cros_ec_command *msg;
	काष्ठा cros_ec_dev *ec = to_cros_ec_dev(dev);

	/*
	 * We might need to reject the program क्रम size reasons. The EC
	 * enक्रमces a maximum program size, but we also करोn't want to try
	 * and send a program that is too big क्रम the protocol. In order
	 * to ensure the latter, we also need to ensure we have extra bytes
	 * to represent the rest of the packet.
	 */
	extra_bytes = माप(*param) - माप(param->set_program.data);
	max_size = min(EC_LB_PROG_LEN, ec->ec_dev->max_request - extra_bytes);
	अगर (count > max_size) अणु
		dev_err(dev, "Program is %u bytes, too long to send (max: %u)",
			(अचिन्हित पूर्णांक)count, max_size);

		वापस -EINVAL;
	पूर्ण

	msg = alloc_lightbar_cmd_msg(ec);
	अगर (!msg)
		वापस -ENOMEM;

	ret = lb_throttle();
	अगर (ret)
		जाओ निकास;

	dev_info(dev, "Copying %zu byte program to EC", count);

	param = (काष्ठा ec_params_lightbar *)msg->data;
	param->cmd = LIGHTBAR_CMD_SET_PROGRAM;

	param->set_program.size = count;
	स_नकल(param->set_program.data, buf, count);

	/*
	 * We need to set the message size manually or अन्यथा it will use
	 * EC_LB_PROG_LEN. This might be too दीर्घ, and the program
	 * is unlikely to use all of the space.
	 */
	msg->outsize = count + extra_bytes;

	ret = cros_ec_cmd_xfer_status(ec->ec_dev, msg);
	अगर (ret < 0)
		जाओ निकास;

	ret = count;
निकास:
	kमुक्त(msg);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार userspace_control_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", userspace_control);
पूर्ण

अटल sमाप_प्रकार userspace_control_store(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf,
				       माप_प्रकार count)
अणु
	bool enable;
	पूर्णांक ret;

	ret = strtobool(buf, &enable);
	अगर (ret < 0)
		वापस ret;

	userspace_control = enable;

	वापस count;
पूर्ण

/* Module initialization */

अटल DEVICE_ATTR_RW(पूर्णांकerval_msec);
अटल DEVICE_ATTR_RO(version);
अटल DEVICE_ATTR_WO(brightness);
अटल DEVICE_ATTR_WO(led_rgb);
अटल DEVICE_ATTR_RW(sequence);
अटल DEVICE_ATTR_WO(program);
अटल DEVICE_ATTR_RW(userspace_control);

अटल काष्ठा attribute *__lb_cmds_attrs[] = अणु
	&dev_attr_पूर्णांकerval_msec.attr,
	&dev_attr_version.attr,
	&dev_attr_brightness.attr,
	&dev_attr_led_rgb.attr,
	&dev_attr_sequence.attr,
	&dev_attr_program.attr,
	&dev_attr_userspace_control.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group cros_ec_lightbar_attr_group = अणु
	.name = "lightbar",
	.attrs = __lb_cmds_attrs,
पूर्ण;

अटल पूर्णांक cros_ec_lightbar_probe(काष्ठा platक्रमm_device *pd)
अणु
	काष्ठा cros_ec_dev *ec_dev = dev_get_drvdata(pd->dev.parent);
	काष्ठा cros_ec_platक्रमm *pdata = dev_get_platdata(ec_dev->dev);
	काष्ठा device *dev = &pd->dev;
	पूर्णांक ret;

	/*
	 * Only instantiate the lightbar अगर the EC name is 'cros_ec'. Other EC
	 * devices like 'cros_pd' doesn't have a lightbar.
	 */
	अगर (म_भेद(pdata->ec_name, CROS_EC_DEV_NAME) != 0)
		वापस -ENODEV;

	/*
	 * Ask then क्रम the lightbar version, अगर it's 0 then the 'cros_ec'
	 * करोesn't have a lightbar.
	 */
	अगर (!get_lightbar_version(ec_dev, शून्य, शून्य))
		वापस -ENODEV;

	/* Take control of the lightbar from the EC. */
	lb_manual_suspend_ctrl(ec_dev, 1);

	ret = sysfs_create_group(&ec_dev->class_dev.kobj,
				 &cros_ec_lightbar_attr_group);
	अगर (ret < 0)
		dev_err(dev, "failed to create %s attributes. err=%d\n",
			cros_ec_lightbar_attr_group.name, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक cros_ec_lightbar_हटाओ(काष्ठा platक्रमm_device *pd)
अणु
	काष्ठा cros_ec_dev *ec_dev = dev_get_drvdata(pd->dev.parent);

	sysfs_हटाओ_group(&ec_dev->class_dev.kobj,
			   &cros_ec_lightbar_attr_group);

	/* Let the EC take over the lightbar again. */
	lb_manual_suspend_ctrl(ec_dev, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cros_ec_lightbar_resume(काष्ठा device *dev)
अणु
	काष्ठा cros_ec_dev *ec_dev = dev_get_drvdata(dev->parent);

	अगर (userspace_control)
		वापस 0;

	वापस lb_send_empty_cmd(ec_dev, LIGHTBAR_CMD_RESUME);
पूर्ण

अटल पूर्णांक __maybe_unused cros_ec_lightbar_suspend(काष्ठा device *dev)
अणु
	काष्ठा cros_ec_dev *ec_dev = dev_get_drvdata(dev->parent);

	अगर (userspace_control)
		वापस 0;

	वापस lb_send_empty_cmd(ec_dev, LIGHTBAR_CMD_SUSPEND);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(cros_ec_lightbar_pm_ops,
			 cros_ec_lightbar_suspend, cros_ec_lightbar_resume);

अटल काष्ठा platक्रमm_driver cros_ec_lightbar_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.pm = &cros_ec_lightbar_pm_ops,
	पूर्ण,
	.probe = cros_ec_lightbar_probe,
	.हटाओ = cros_ec_lightbar_हटाओ,
पूर्ण;

module_platक्रमm_driver(cros_ec_lightbar_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Expose the Chromebook Pixel's lightbar to userspace");
MODULE_ALIAS("platform:" DRV_NAME);
