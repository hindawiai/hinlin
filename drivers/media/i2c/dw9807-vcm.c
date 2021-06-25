<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Intel Corporation

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>

#घोषणा DW9807_MAX_FOCUS_POS	1023
/*
 * This sets the minimum granularity क्रम the focus positions.
 * A value of 1 gives maximum accuracy क्रम a desired focus position.
 */
#घोषणा DW9807_FOCUS_STEPS	1
/*
 * This acts as the minimum granularity of lens movement.
 * Keep this value घातer of 2, so the control steps can be
 * unअगरormly adjusted क्रम gradual lens movement, with desired
 * number of control steps.
 */
#घोषणा DW9807_CTRL_STEPS	16
#घोषणा DW9807_CTRL_DELAY_US	1000

#घोषणा DW9807_CTL_ADDR		0x02
/*
 * DW9807 separates two रेजिस्टरs to control the VCM position.
 * One क्रम MSB value, another is LSB value.
 */
#घोषणा DW9807_MSB_ADDR		0x03
#घोषणा DW9807_LSB_ADDR		0x04
#घोषणा DW9807_STATUS_ADDR	0x05
#घोषणा DW9807_MODE_ADDR	0x06
#घोषणा DW9807_RESOन_अंकCE_ADDR	0x07

#घोषणा MAX_RETRY		10

काष्ठा dw9807_device अणु
	काष्ठा v4l2_ctrl_handler ctrls_vcm;
	काष्ठा v4l2_subdev sd;
	u16 current_val;
पूर्ण;

अटल अंतरभूत काष्ठा dw9807_device *sd_to_dw9807_vcm(
					काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा dw9807_device, sd);
पूर्ण

अटल पूर्णांक dw9807_i2c_check(काष्ठा i2c_client *client)
अणु
	स्थिर अक्षर status_addr = DW9807_STATUS_ADDR;
	अक्षर status_result;
	पूर्णांक ret;

	ret = i2c_master_send(client, &status_addr, माप(status_addr));
	अगर (ret < 0) अणु
		dev_err(&client->dev, "I2C write STATUS address fail ret = %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = i2c_master_recv(client, &status_result, माप(status_result));
	अगर (ret < 0) अणु
		dev_err(&client->dev, "I2C read STATUS value fail ret = %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस status_result;
पूर्ण

अटल पूर्णांक dw9807_set_dac(काष्ठा i2c_client *client, u16 data)
अणु
	स्थिर अक्षर tx_data[3] = अणु
		DW9807_MSB_ADDR, ((data >> 8) & 0x03), (data & 0xff)
	पूर्ण;
	पूर्णांक val, ret;

	/*
	 * According to the datasheet, need to check the bus status beक्रमe we
	 * ग_लिखो VCM position. This ensure that we really ग_लिखो the value
	 * पूर्णांकo the रेजिस्टर
	 */
	ret = पढ़ोx_poll_समयout(dw9807_i2c_check, client, val, val <= 0,
			DW9807_CTRL_DELAY_US, MAX_RETRY * DW9807_CTRL_DELAY_US);

	अगर (ret || val < 0) अणु
		अगर (ret) अणु
			dev_warn(&client->dev,
				"Cannot do the write operation because VCM is busy\n");
		पूर्ण

		वापस ret ? -EBUSY : val;
	पूर्ण

	/* Write VCM position to रेजिस्टरs */
	ret = i2c_master_send(client, tx_data, माप(tx_data));
	अगर (ret < 0) अणु
		dev_err(&client->dev,
			"I2C write MSB fail ret=%d\n", ret);

		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dw9807_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा dw9807_device *dev_vcm = container_of(ctrl->handler,
		काष्ठा dw9807_device, ctrls_vcm);

	अगर (ctrl->id == V4L2_CID_FOCUS_ABSOLUTE) अणु
		काष्ठा i2c_client *client = v4l2_get_subdevdata(&dev_vcm->sd);

		dev_vcm->current_val = ctrl->val;
		वापस dw9807_set_dac(client, ctrl->val);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops dw9807_vcm_ctrl_ops = अणु
	.s_ctrl = dw9807_set_ctrl,
पूर्ण;

अटल पूर्णांक dw9807_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	पूर्णांक rval;

	rval = pm_runसमय_get_sync(sd->dev);
	अगर (rval < 0) अणु
		pm_runसमय_put_noidle(sd->dev);
		वापस rval;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dw9807_बंद(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	pm_runसमय_put(sd->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops dw9807_पूर्णांक_ops = अणु
	.खोलो = dw9807_खोलो,
	.बंद = dw9807_बंद,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops dw9807_ops = अणु पूर्ण;

अटल व्योम dw9807_subdev_cleanup(काष्ठा dw9807_device *dw9807_dev)
अणु
	v4l2_async_unरेजिस्टर_subdev(&dw9807_dev->sd);
	v4l2_ctrl_handler_मुक्त(&dw9807_dev->ctrls_vcm);
	media_entity_cleanup(&dw9807_dev->sd.entity);
पूर्ण

अटल पूर्णांक dw9807_init_controls(काष्ठा dw9807_device *dev_vcm)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &dev_vcm->ctrls_vcm;
	स्थिर काष्ठा v4l2_ctrl_ops *ops = &dw9807_vcm_ctrl_ops;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&dev_vcm->sd);

	v4l2_ctrl_handler_init(hdl, 1);

	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_FOCUS_ABSOLUTE,
			  0, DW9807_MAX_FOCUS_POS, DW9807_FOCUS_STEPS, 0);

	dev_vcm->sd.ctrl_handler = hdl;
	अगर (hdl->error) अणु
		dev_err(&client->dev, "%s fail error: 0x%x\n",
			__func__, hdl->error);
		वापस hdl->error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dw9807_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा dw9807_device *dw9807_dev;
	पूर्णांक rval;

	dw9807_dev = devm_kzalloc(&client->dev, माप(*dw9807_dev),
				  GFP_KERNEL);
	अगर (dw9807_dev == शून्य)
		वापस -ENOMEM;

	v4l2_i2c_subdev_init(&dw9807_dev->sd, client, &dw9807_ops);
	dw9807_dev->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	dw9807_dev->sd.पूर्णांकernal_ops = &dw9807_पूर्णांक_ops;

	rval = dw9807_init_controls(dw9807_dev);
	अगर (rval)
		जाओ err_cleanup;

	rval = media_entity_pads_init(&dw9807_dev->sd.entity, 0, शून्य);
	अगर (rval < 0)
		जाओ err_cleanup;

	dw9807_dev->sd.entity.function = MEDIA_ENT_F_LENS;

	rval = v4l2_async_रेजिस्टर_subdev(&dw9807_dev->sd);
	अगर (rval < 0)
		जाओ err_cleanup;

	pm_runसमय_set_active(&client->dev);
	pm_runसमय_enable(&client->dev);
	pm_runसमय_idle(&client->dev);

	वापस 0;

err_cleanup:
	v4l2_ctrl_handler_मुक्त(&dw9807_dev->ctrls_vcm);
	media_entity_cleanup(&dw9807_dev->sd.entity);

	वापस rval;
पूर्ण

अटल पूर्णांक dw9807_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा dw9807_device *dw9807_dev = sd_to_dw9807_vcm(sd);

	pm_runसमय_disable(&client->dev);

	dw9807_subdev_cleanup(dw9807_dev);

	वापस 0;
पूर्ण

/*
 * This function sets the vcm position, so it consumes least current
 * The lens position is gradually moved in units of DW9807_CTRL_STEPS,
 * to make the movements smoothly.
 */
अटल पूर्णांक __maybe_unused dw9807_vcm_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा dw9807_device *dw9807_dev = sd_to_dw9807_vcm(sd);
	स्थिर अक्षर tx_data[2] = अणु DW9807_CTL_ADDR, 0x01 पूर्ण;
	पूर्णांक ret, val;

	क्रम (val = dw9807_dev->current_val & ~(DW9807_CTRL_STEPS - 1);
	     val >= 0; val -= DW9807_CTRL_STEPS) अणु
		ret = dw9807_set_dac(client, val);
		अगर (ret)
			dev_err_once(dev, "%s I2C failure: %d", __func__, ret);
		usleep_range(DW9807_CTRL_DELAY_US, DW9807_CTRL_DELAY_US + 10);
	पूर्ण

	/* Power करोwn */
	ret = i2c_master_send(client, tx_data, माप(tx_data));
	अगर (ret < 0) अणु
		dev_err(&client->dev, "I2C write CTL fail ret = %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function sets the vcm position to the value set by the user
 * through v4l2_ctrl_ops s_ctrl handler
 * The lens position is gradually moved in units of DW9807_CTRL_STEPS,
 * to make the movements smoothly.
 */
अटल पूर्णांक  __maybe_unused dw9807_vcm_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा dw9807_device *dw9807_dev = sd_to_dw9807_vcm(sd);
	स्थिर अक्षर tx_data[2] = अणु DW9807_CTL_ADDR, 0x00 पूर्ण;
	पूर्णांक ret, val;

	/* Power on */
	ret = i2c_master_send(client, tx_data, माप(tx_data));
	अगर (ret < 0) अणु
		dev_err(&client->dev, "I2C write CTL fail ret = %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (val = dw9807_dev->current_val % DW9807_CTRL_STEPS;
	     val < dw9807_dev->current_val + DW9807_CTRL_STEPS - 1;
	     val += DW9807_CTRL_STEPS) अणु
		ret = dw9807_set_dac(client, val);
		अगर (ret)
			dev_err_ratelimited(dev, "%s I2C failure: %d",
						__func__, ret);
		usleep_range(DW9807_CTRL_DELAY_US, DW9807_CTRL_DELAY_US + 10);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dw9807_of_table[] = अणु
	अणु .compatible = "dongwoon,dw9807-vcm" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dw9807_of_table);

अटल स्थिर काष्ठा dev_pm_ops dw9807_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(dw9807_vcm_suspend, dw9807_vcm_resume)
	SET_RUNTIME_PM_OPS(dw9807_vcm_suspend, dw9807_vcm_resume, शून्य)
पूर्ण;

अटल काष्ठा i2c_driver dw9807_i2c_driver = अणु
	.driver = अणु
		.name = "dw9807",
		.pm = &dw9807_pm_ops,
		.of_match_table = dw9807_of_table,
	पूर्ण,
	.probe_new = dw9807_probe,
	.हटाओ = dw9807_हटाओ,
पूर्ण;

module_i2c_driver(dw9807_i2c_driver);

MODULE_AUTHOR("Chiang, Alan");
MODULE_DESCRIPTION("DW9807 VCM driver");
MODULE_LICENSE("GPL v2");
