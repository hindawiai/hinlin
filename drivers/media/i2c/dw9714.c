<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2015--2017 Intel Corporation.

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>

#घोषणा DW9714_NAME		"dw9714"
#घोषणा DW9714_MAX_FOCUS_POS	1023
/*
 * This sets the minimum granularity क्रम the focus positions.
 * A value of 1 gives maximum accuracy क्रम a desired focus position
 */
#घोषणा DW9714_FOCUS_STEPS	1
/*
 * This acts as the minimum granularity of lens movement.
 * Keep this value घातer of 2, so the control steps can be
 * unअगरormly adjusted क्रम gradual lens movement, with desired
 * number of control steps.
 */
#घोषणा DW9714_CTRL_STEPS	16
#घोषणा DW9714_CTRL_DELAY_US	1000
/*
 * S[3:2] = 0x00, codes per step क्रम "Linear Slope Control"
 * S[1:0] = 0x00, step period
 */
#घोषणा DW9714_DEFAULT_S 0x0
#घोषणा DW9714_VAL(data, s) ((data) << 4 | (s))

/* dw9714 device काष्ठाure */
काष्ठा dw9714_device अणु
	काष्ठा v4l2_ctrl_handler ctrls_vcm;
	काष्ठा v4l2_subdev sd;
	u16 current_val;
पूर्ण;

अटल अंतरभूत काष्ठा dw9714_device *to_dw9714_vcm(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस container_of(ctrl->handler, काष्ठा dw9714_device, ctrls_vcm);
पूर्ण

अटल अंतरभूत काष्ठा dw9714_device *sd_to_dw9714_vcm(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा dw9714_device, sd);
पूर्ण

अटल पूर्णांक dw9714_i2c_ग_लिखो(काष्ठा i2c_client *client, u16 data)
अणु
	पूर्णांक ret;
	__be16 val = cpu_to_be16(data);

	ret = i2c_master_send(client, (स्थिर अक्षर *)&val, माप(val));
	अगर (ret != माप(val)) अणु
		dev_err(&client->dev, "I2C write fail\n");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dw9714_t_focus_vcm(काष्ठा dw9714_device *dw9714_dev, u16 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&dw9714_dev->sd);

	dw9714_dev->current_val = val;

	वापस dw9714_i2c_ग_लिखो(client, DW9714_VAL(val, DW9714_DEFAULT_S));
पूर्ण

अटल पूर्णांक dw9714_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा dw9714_device *dev_vcm = to_dw9714_vcm(ctrl);

	अगर (ctrl->id == V4L2_CID_FOCUS_ABSOLUTE)
		वापस dw9714_t_focus_vcm(dev_vcm, ctrl->val);

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops dw9714_vcm_ctrl_ops = अणु
	.s_ctrl = dw9714_set_ctrl,
पूर्ण;

अटल पूर्णांक dw9714_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	पूर्णांक rval;

	rval = pm_runसमय_get_sync(sd->dev);
	अगर (rval < 0) अणु
		pm_runसमय_put_noidle(sd->dev);
		वापस rval;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dw9714_बंद(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	pm_runसमय_put(sd->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops dw9714_पूर्णांक_ops = अणु
	.खोलो = dw9714_खोलो,
	.बंद = dw9714_बंद,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops dw9714_ops = अणु पूर्ण;

अटल व्योम dw9714_subdev_cleanup(काष्ठा dw9714_device *dw9714_dev)
अणु
	v4l2_async_unरेजिस्टर_subdev(&dw9714_dev->sd);
	v4l2_ctrl_handler_मुक्त(&dw9714_dev->ctrls_vcm);
	media_entity_cleanup(&dw9714_dev->sd.entity);
पूर्ण

अटल पूर्णांक dw9714_init_controls(काष्ठा dw9714_device *dev_vcm)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &dev_vcm->ctrls_vcm;
	स्थिर काष्ठा v4l2_ctrl_ops *ops = &dw9714_vcm_ctrl_ops;

	v4l2_ctrl_handler_init(hdl, 1);

	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_FOCUS_ABSOLUTE,
			  0, DW9714_MAX_FOCUS_POS, DW9714_FOCUS_STEPS, 0);

	अगर (hdl->error)
		dev_err(dev_vcm->sd.dev, "%s fail error: 0x%x\n",
			__func__, hdl->error);
	dev_vcm->sd.ctrl_handler = hdl;
	वापस hdl->error;
पूर्ण

अटल पूर्णांक dw9714_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा dw9714_device *dw9714_dev;
	पूर्णांक rval;

	dw9714_dev = devm_kzalloc(&client->dev, माप(*dw9714_dev),
				  GFP_KERNEL);
	अगर (dw9714_dev == शून्य)
		वापस -ENOMEM;

	v4l2_i2c_subdev_init(&dw9714_dev->sd, client, &dw9714_ops);
	dw9714_dev->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	dw9714_dev->sd.पूर्णांकernal_ops = &dw9714_पूर्णांक_ops;

	rval = dw9714_init_controls(dw9714_dev);
	अगर (rval)
		जाओ err_cleanup;

	rval = media_entity_pads_init(&dw9714_dev->sd.entity, 0, शून्य);
	अगर (rval < 0)
		जाओ err_cleanup;

	dw9714_dev->sd.entity.function = MEDIA_ENT_F_LENS;

	rval = v4l2_async_रेजिस्टर_subdev(&dw9714_dev->sd);
	अगर (rval < 0)
		जाओ err_cleanup;

	pm_runसमय_set_active(&client->dev);
	pm_runसमय_enable(&client->dev);
	pm_runसमय_idle(&client->dev);

	वापस 0;

err_cleanup:
	v4l2_ctrl_handler_मुक्त(&dw9714_dev->ctrls_vcm);
	media_entity_cleanup(&dw9714_dev->sd.entity);

	वापस rval;
पूर्ण

अटल पूर्णांक dw9714_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा dw9714_device *dw9714_dev = sd_to_dw9714_vcm(sd);

	pm_runसमय_disable(&client->dev);
	dw9714_subdev_cleanup(dw9714_dev);

	वापस 0;
पूर्ण

/*
 * This function sets the vcm position, so it consumes least current
 * The lens position is gradually moved in units of DW9714_CTRL_STEPS,
 * to make the movements smoothly.
 */
अटल पूर्णांक __maybe_unused dw9714_vcm_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा dw9714_device *dw9714_dev = sd_to_dw9714_vcm(sd);
	पूर्णांक ret, val;

	क्रम (val = dw9714_dev->current_val & ~(DW9714_CTRL_STEPS - 1);
	     val >= 0; val -= DW9714_CTRL_STEPS) अणु
		ret = dw9714_i2c_ग_लिखो(client,
				       DW9714_VAL(val, DW9714_DEFAULT_S));
		अगर (ret)
			dev_err_once(dev, "%s I2C failure: %d", __func__, ret);
		usleep_range(DW9714_CTRL_DELAY_US, DW9714_CTRL_DELAY_US + 10);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This function sets the vcm position to the value set by the user
 * through v4l2_ctrl_ops s_ctrl handler
 * The lens position is gradually moved in units of DW9714_CTRL_STEPS,
 * to make the movements smoothly.
 */
अटल पूर्णांक  __maybe_unused dw9714_vcm_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा dw9714_device *dw9714_dev = sd_to_dw9714_vcm(sd);
	पूर्णांक ret, val;

	क्रम (val = dw9714_dev->current_val % DW9714_CTRL_STEPS;
	     val < dw9714_dev->current_val + DW9714_CTRL_STEPS - 1;
	     val += DW9714_CTRL_STEPS) अणु
		ret = dw9714_i2c_ग_लिखो(client,
				       DW9714_VAL(val, DW9714_DEFAULT_S));
		अगर (ret)
			dev_err_ratelimited(dev, "%s I2C failure: %d",
						__func__, ret);
		usleep_range(DW9714_CTRL_DELAY_US, DW9714_CTRL_DELAY_US + 10);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id dw9714_id_table[] = अणु
	अणु DW9714_NAME, 0 पूर्ण,
	अणु अणु 0 पूर्ण पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, dw9714_id_table);

अटल स्थिर काष्ठा of_device_id dw9714_of_table[] = अणु
	अणु .compatible = "dongwoon,dw9714" पूर्ण,
	अणु अणु 0 पूर्ण पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dw9714_of_table);

अटल स्थिर काष्ठा dev_pm_ops dw9714_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(dw9714_vcm_suspend, dw9714_vcm_resume)
	SET_RUNTIME_PM_OPS(dw9714_vcm_suspend, dw9714_vcm_resume, शून्य)
पूर्ण;

अटल काष्ठा i2c_driver dw9714_i2c_driver = अणु
	.driver = अणु
		.name = DW9714_NAME,
		.pm = &dw9714_pm_ops,
		.of_match_table = dw9714_of_table,
	पूर्ण,
	.probe_new = dw9714_probe,
	.हटाओ = dw9714_हटाओ,
	.id_table = dw9714_id_table,
पूर्ण;

module_i2c_driver(dw9714_i2c_driver);

MODULE_AUTHOR("Tianshu Qiu <tian.shu.qiu@intel.com>");
MODULE_AUTHOR("Jian Xu Zheng");
MODULE_AUTHOR("Yuning Pu <yuning.pu@intel.com>");
MODULE_AUTHOR("Jouni Ukkonen <jouni.ukkonen@intel.com>");
MODULE_AUTHOR("Tommi Franttila <tommi.franttila@intel.com>");
MODULE_DESCRIPTION("DW9714 VCM driver");
MODULE_LICENSE("GPL v2");
