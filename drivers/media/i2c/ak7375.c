<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Intel Corporation

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>

#घोषणा AK7375_MAX_FOCUS_POS	4095
/*
 * This sets the minimum granularity क्रम the focus positions.
 * A value of 1 gives maximum accuracy क्रम a desired focus position
 */
#घोषणा AK7375_FOCUS_STEPS	1
/*
 * This acts as the minimum granularity of lens movement.
 * Keep this value घातer of 2, so the control steps can be
 * unअगरormly adjusted क्रम gradual lens movement, with desired
 * number of control steps.
 */
#घोषणा AK7375_CTRL_STEPS	64
#घोषणा AK7375_CTRL_DELAY_US	1000

#घोषणा AK7375_REG_POSITION	0x0
#घोषणा AK7375_REG_CONT		0x2
#घोषणा AK7375_MODE_ACTIVE	0x0
#घोषणा AK7375_MODE_STANDBY	0x40

/* ak7375 device काष्ठाure */
काष्ठा ak7375_device अणु
	काष्ठा v4l2_ctrl_handler ctrls_vcm;
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl *focus;
	/* active or standby mode */
	bool active;
पूर्ण;

अटल अंतरभूत काष्ठा ak7375_device *to_ak7375_vcm(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस container_of(ctrl->handler, काष्ठा ak7375_device, ctrls_vcm);
पूर्ण

अटल अंतरभूत काष्ठा ak7375_device *sd_to_ak7375_vcm(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा ak7375_device, sd);
पूर्ण

अटल पूर्णांक ak7375_i2c_ग_लिखो(काष्ठा ak7375_device *ak7375,
	u8 addr, u16 data, u8 size)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ak7375->sd);
	u8 buf[3];
	पूर्णांक ret;

	अगर (size != 1 && size != 2)
		वापस -EINVAL;
	buf[0] = addr;
	buf[size] = data & 0xff;
	अगर (size == 2)
		buf[1] = (data >> 8) & 0xff;
	ret = i2c_master_send(client, (स्थिर अक्षर *)buf, size + 1);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != size + 1)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक ak7375_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ak7375_device *dev_vcm = to_ak7375_vcm(ctrl);

	अगर (ctrl->id == V4L2_CID_FOCUS_ABSOLUTE)
		वापस ak7375_i2c_ग_लिखो(dev_vcm, AK7375_REG_POSITION,
					ctrl->val << 4, 2);

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ak7375_vcm_ctrl_ops = अणु
	.s_ctrl = ak7375_set_ctrl,
पूर्ण;

अटल पूर्णांक ak7375_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(sd->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(sd->dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ak7375_बंद(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	pm_runसमय_put(sd->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops ak7375_पूर्णांक_ops = अणु
	.खोलो = ak7375_खोलो,
	.बंद = ak7375_बंद,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ak7375_ops = अणु पूर्ण;

अटल व्योम ak7375_subdev_cleanup(काष्ठा ak7375_device *ak7375_dev)
अणु
	v4l2_async_unरेजिस्टर_subdev(&ak7375_dev->sd);
	v4l2_ctrl_handler_मुक्त(&ak7375_dev->ctrls_vcm);
	media_entity_cleanup(&ak7375_dev->sd.entity);
पूर्ण

अटल पूर्णांक ak7375_init_controls(काष्ठा ak7375_device *dev_vcm)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &dev_vcm->ctrls_vcm;
	स्थिर काष्ठा v4l2_ctrl_ops *ops = &ak7375_vcm_ctrl_ops;

	v4l2_ctrl_handler_init(hdl, 1);

	dev_vcm->focus = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_FOCUS_ABSOLUTE,
		0, AK7375_MAX_FOCUS_POS, AK7375_FOCUS_STEPS, 0);

	अगर (hdl->error)
		dev_err(dev_vcm->sd.dev, "%s fail error: 0x%x\n",
			__func__, hdl->error);
	dev_vcm->sd.ctrl_handler = hdl;

	वापस hdl->error;
पूर्ण

अटल पूर्णांक ak7375_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा ak7375_device *ak7375_dev;
	पूर्णांक ret;

	ak7375_dev = devm_kzalloc(&client->dev, माप(*ak7375_dev),
				  GFP_KERNEL);
	अगर (!ak7375_dev)
		वापस -ENOMEM;

	v4l2_i2c_subdev_init(&ak7375_dev->sd, client, &ak7375_ops);
	ak7375_dev->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	ak7375_dev->sd.पूर्णांकernal_ops = &ak7375_पूर्णांक_ops;
	ak7375_dev->sd.entity.function = MEDIA_ENT_F_LENS;

	ret = ak7375_init_controls(ak7375_dev);
	अगर (ret)
		जाओ err_cleanup;

	ret = media_entity_pads_init(&ak7375_dev->sd.entity, 0, शून्य);
	अगर (ret < 0)
		जाओ err_cleanup;

	ret = v4l2_async_रेजिस्टर_subdev(&ak7375_dev->sd);
	अगर (ret < 0)
		जाओ err_cleanup;

	pm_runसमय_set_active(&client->dev);
	pm_runसमय_enable(&client->dev);
	pm_runसमय_idle(&client->dev);

	वापस 0;

err_cleanup:
	v4l2_ctrl_handler_मुक्त(&ak7375_dev->ctrls_vcm);
	media_entity_cleanup(&ak7375_dev->sd.entity);

	वापस ret;
पूर्ण

अटल पूर्णांक ak7375_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ak7375_device *ak7375_dev = sd_to_ak7375_vcm(sd);

	ak7375_subdev_cleanup(ak7375_dev);
	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);

	वापस 0;
पूर्ण

/*
 * This function sets the vcm position, so it consumes least current
 * The lens position is gradually moved in units of AK7375_CTRL_STEPS,
 * to make the movements smoothly.
 */
अटल पूर्णांक __maybe_unused ak7375_vcm_suspend(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा ak7375_device *ak7375_dev = sd_to_ak7375_vcm(sd);
	पूर्णांक ret, val;

	अगर (!ak7375_dev->active)
		वापस 0;

	क्रम (val = ak7375_dev->focus->val & ~(AK7375_CTRL_STEPS - 1);
	     val >= 0; val -= AK7375_CTRL_STEPS) अणु
		ret = ak7375_i2c_ग_लिखो(ak7375_dev, AK7375_REG_POSITION,
				       val << 4, 2);
		अगर (ret)
			dev_err_once(dev, "%s I2C failure: %d\n",
				     __func__, ret);
		usleep_range(AK7375_CTRL_DELAY_US, AK7375_CTRL_DELAY_US + 10);
	पूर्ण

	ret = ak7375_i2c_ग_लिखो(ak7375_dev, AK7375_REG_CONT,
			       AK7375_MODE_STANDBY, 1);
	अगर (ret)
		dev_err(dev, "%s I2C failure: %d\n", __func__, ret);

	ak7375_dev->active = false;

	वापस 0;
पूर्ण

/*
 * This function sets the vcm position to the value set by the user
 * through v4l2_ctrl_ops s_ctrl handler
 * The lens position is gradually moved in units of AK7375_CTRL_STEPS,
 * to make the movements smoothly.
 */
अटल पूर्णांक __maybe_unused ak7375_vcm_resume(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा ak7375_device *ak7375_dev = sd_to_ak7375_vcm(sd);
	पूर्णांक ret, val;

	अगर (ak7375_dev->active)
		वापस 0;

	ret = ak7375_i2c_ग_लिखो(ak7375_dev, AK7375_REG_CONT,
		AK7375_MODE_ACTIVE, 1);
	अगर (ret) अणु
		dev_err(dev, "%s I2C failure: %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	क्रम (val = ak7375_dev->focus->val % AK7375_CTRL_STEPS;
	     val <= ak7375_dev->focus->val;
	     val += AK7375_CTRL_STEPS) अणु
		ret = ak7375_i2c_ग_लिखो(ak7375_dev, AK7375_REG_POSITION,
				       val << 4, 2);
		अगर (ret)
			dev_err_ratelimited(dev, "%s I2C failure: %d\n",
						__func__, ret);
		usleep_range(AK7375_CTRL_DELAY_US, AK7375_CTRL_DELAY_US + 10);
	पूर्ण

	ak7375_dev->active = true;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ak7375_of_table[] = अणु
	अणु .compatible = "asahi-kasei,ak7375" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ak7375_of_table);

अटल स्थिर काष्ठा dev_pm_ops ak7375_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(ak7375_vcm_suspend, ak7375_vcm_resume)
	SET_RUNTIME_PM_OPS(ak7375_vcm_suspend, ak7375_vcm_resume, शून्य)
पूर्ण;

अटल काष्ठा i2c_driver ak7375_i2c_driver = अणु
	.driver = अणु
		.name = "ak7375",
		.pm = &ak7375_pm_ops,
		.of_match_table = ak7375_of_table,
	पूर्ण,
	.probe_new = ak7375_probe,
	.हटाओ = ak7375_हटाओ,
पूर्ण;
module_i2c_driver(ak7375_i2c_driver);

MODULE_AUTHOR("Tianshu Qiu <tian.shu.qiu@intel.com>");
MODULE_AUTHOR("Bingbu Cao <bingbu.cao@intel.com>");
MODULE_DESCRIPTION("AK7375 VCM driver");
MODULE_LICENSE("GPL v2");
