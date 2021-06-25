<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 MediaTek Inc.

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-subdev.h>

#घोषणा DW9768_NAME				"dw9768"
#घोषणा DW9768_MAX_FOCUS_POS			(1024 - 1)
/*
 * This sets the minimum granularity क्रम the focus positions.
 * A value of 1 gives maximum accuracy क्रम a desired focus position
 */
#घोषणा DW9768_FOCUS_STEPS			1

/*
 * Ring control and Power control रेजिस्टर
 * Bit[1] RING_EN
 * 0: Direct mode
 * 1: AAC mode (ringing control mode)
 * Bit[0] PD
 * 0: Normal operation mode
 * 1: Power करोwn mode
 * DW9768 requires रुकोing समय of Topr after PD reset takes place.
 */
#घोषणा DW9768_RING_PD_CONTROL_REG		0x02
#घोषणा DW9768_PD_MODE_OFF			0x00
#घोषणा DW9768_PD_MODE_EN			BIT(0)
#घोषणा DW9768_AAC_MODE_EN			BIT(1)

/*
 * DW9768 separates two रेजिस्टरs to control the VCM position.
 * One क्रम MSB value, another is LSB value.
 * DAC_MSB: D[9:8] (ADD: 0x03)
 * DAC_LSB: D[7:0] (ADD: 0x04)
 * D[9:0] DAC data input: positive output current = D[9:0] / 1023 * 100[mA]
 */
#घोषणा DW9768_MSB_ADDR				0x03
#घोषणा DW9768_LSB_ADDR				0x04
#घोषणा DW9768_STATUS_ADDR			0x05

/*
 * AAC mode control & prescale रेजिस्टर
 * Bit[7:5] Namely AC[2:0], decide the VCM mode and operation समय.
 * 001 AAC2 0.48 x Tvib
 * 010 AAC3 0.70 x Tvib
 * 011 AAC4 0.75 x Tvib
 * 101 AAC8 1.13 x Tvib
 * Bit[2:0] Namely PRESC[2:0], set the पूर्णांकernal घड़ी भागiding rate as follow.
 * 000 2
 * 001 1
 * 010 1/2
 * 011 1/4
 * 100 8
 * 101 4
 */
#घोषणा DW9768_AAC_PRESC_REG			0x06
#घोषणा DW9768_AAC_MODE_SEL_MASK		GENMASK(7, 5)
#घोषणा DW9768_CLOCK_PRE_SCALE_SEL_MASK		GENMASK(2, 0)

/*
 * VCM period of vibration रेजिस्टर
 * Bit[5:0] Defined as VCM rising periodic समय (Tvib) together with PRESC[2:0]
 * Tvib = (6.3ms + AACT[5:0] * 0.1ms) * Dividing Rate
 * Dividing Rate is the पूर्णांकernal घड़ी भागiding rate that is defined at
 * PRESCALE रेजिस्टर (ADD: 0x06)
 */
#घोषणा DW9768_AAC_TIME_REG			0x07

/*
 * DW9768 requires रुकोing समय (delay समय) of t_OPR after घातer-up,
 * or in the हाल of PD reset taking place.
 */
#घोषणा DW9768_T_OPR_US				1000
#घोषणा DW9768_TVIB_MS_BASE10			(64 - 1)
#घोषणा DW9768_AAC_MODE_DEFAULT			2
#घोषणा DW9768_AAC_TIME_DEFAULT			0x20
#घोषणा DW9768_CLOCK_PRE_SCALE_DEFAULT		1

/*
 * This acts as the minimum granularity of lens movement.
 * Keep this value घातer of 2, so the control steps can be
 * unअगरormly adjusted क्रम gradual lens movement, with desired
 * number of control steps.
 */
#घोषणा DW9768_MOVE_STEPS			16

अटल स्थिर अक्षर * स्थिर dw9768_supply_names[] = अणु
	"vin",	/* Digital I/O घातer */
	"vdd",	/* Digital core घातer */
पूर्ण;

/* dw9768 device काष्ठाure */
काष्ठा dw9768 अणु
	काष्ठा regulator_bulk_data supplies[ARRAY_SIZE(dw9768_supply_names)];
	काष्ठा v4l2_ctrl_handler ctrls;
	काष्ठा v4l2_ctrl *focus;
	काष्ठा v4l2_subdev sd;

	u32 aac_mode;
	u32 aac_timing;
	u32 घड़ी_presc;
	u32 move_delay_us;
पूर्ण;

अटल अंतरभूत काष्ठा dw9768 *sd_to_dw9768(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा dw9768, sd);
पूर्ण

काष्ठा regval_list अणु
	u8 reg_num;
	u8 value;
पूर्ण;

काष्ठा dw9768_aac_mode_ot_multi अणु
	u32 aac_mode_क्रमागत;
	u32 ot_multi_base100;
पूर्ण;

काष्ठा dw9768_clk_presc_भागiding_rate अणु
	u32 clk_presc_क्रमागत;
	u32 भागiding_rate_base100;
पूर्ण;

अटल स्थिर काष्ठा dw9768_aac_mode_ot_multi aac_mode_ot_multi[] = अणु
	अणु1,  48पूर्ण,
	अणु2,  70पूर्ण,
	अणु3,  75पूर्ण,
	अणु5, 113पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dw9768_clk_presc_भागiding_rate presc_भागiding_rate[] = अणु
	अणु0, 200पूर्ण,
	अणु1, 100पूर्ण,
	अणु2,  50पूर्ण,
	अणु3,  25पूर्ण,
	अणु4, 800पूर्ण,
	अणु5, 400पूर्ण,
पूर्ण;

अटल u32 dw9768_find_ot_multi(u32 aac_mode_param)
अणु
	u32 cur_ot_multi_base100 = 70;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(aac_mode_ot_multi); i++) अणु
		अगर (aac_mode_ot_multi[i].aac_mode_क्रमागत == aac_mode_param) अणु
			cur_ot_multi_base100 =
				aac_mode_ot_multi[i].ot_multi_base100;
		पूर्ण
	पूर्ण

	वापस cur_ot_multi_base100;
पूर्ण

अटल u32 dw9768_find_भागiding_rate(u32 presc_param)
अणु
	u32 cur_clk_भागiding_rate_base100 = 100;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(presc_भागiding_rate); i++) अणु
		अगर (presc_भागiding_rate[i].clk_presc_क्रमागत == presc_param) अणु
			cur_clk_भागiding_rate_base100 =
				presc_भागiding_rate[i].भागiding_rate_base100;
		पूर्ण
	पूर्ण

	वापस cur_clk_भागiding_rate_base100;
पूर्ण

/*
 * DW9768_AAC_PRESC_REG & DW9768_AAC_TIME_REG determine VCM operation समय.
 * For current VCM mode: AAC3, Operation Time would be 0.70 x Tvib.
 * Tvib = (6.3ms + AACT[5:0] * 0.1MS) * Dividing Rate.
 * Below is calculation of the operation delay क्रम each step.
 */
अटल अंतरभूत u32 dw9768_cal_move_delay(u32 aac_mode_param, u32 presc_param,
					u32 aac_timing_param)
अणु
	u32 Tvib_us;
	u32 ot_multi_base100;
	u32 clk_भागiding_rate_base100;

	ot_multi_base100 = dw9768_find_ot_multi(aac_mode_param);

	clk_भागiding_rate_base100 = dw9768_find_भागiding_rate(presc_param);

	Tvib_us = (DW9768_TVIB_MS_BASE10 + aac_timing_param) *
		  clk_भागiding_rate_base100;

	वापस Tvib_us * ot_multi_base100 / 100;
पूर्ण

अटल पूर्णांक dw9768_mod_reg(काष्ठा dw9768 *dw9768, u8 reg, u8 mask, u8 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&dw9768->sd);
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, reg);
	अगर (ret < 0)
		वापस ret;

	val = ((अचिन्हित अक्षर)ret & ~mask) | (val & mask);

	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, val);
पूर्ण

अटल पूर्णांक dw9768_set_dac(काष्ठा dw9768 *dw9768, u16 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&dw9768->sd);

	/* Write VCM position to रेजिस्टरs */
	वापस i2c_smbus_ग_लिखो_word_swapped(client, DW9768_MSB_ADDR, val);
पूर्ण

अटल पूर्णांक dw9768_init(काष्ठा dw9768 *dw9768)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&dw9768->sd);
	पूर्णांक ret, val;

	/* Reset DW9768_RING_PD_CONTROL_REG to शेष status 0x00 */
	ret = i2c_smbus_ग_लिखो_byte_data(client, DW9768_RING_PD_CONTROL_REG,
					DW9768_PD_MODE_OFF);
	अगर (ret < 0)
		वापस ret;

	/*
	 * DW9769 requires रुकोing delay समय of t_OPR
	 * after PD reset takes place.
	 */
	usleep_range(DW9768_T_OPR_US, DW9768_T_OPR_US + 100);

	/* Set DW9768_RING_PD_CONTROL_REG to DW9768_AAC_MODE_EN(0x01) */
	ret = i2c_smbus_ग_लिखो_byte_data(client, DW9768_RING_PD_CONTROL_REG,
					DW9768_AAC_MODE_EN);
	अगर (ret < 0)
		वापस ret;

	/* Set AAC mode */
	ret = dw9768_mod_reg(dw9768, DW9768_AAC_PRESC_REG,
			     DW9768_AAC_MODE_SEL_MASK,
			     dw9768->aac_mode << 5);
	अगर (ret < 0)
		वापस ret;

	/* Set घड़ी presc */
	अगर (dw9768->घड़ी_presc != DW9768_CLOCK_PRE_SCALE_DEFAULT) अणु
		ret = dw9768_mod_reg(dw9768, DW9768_AAC_PRESC_REG,
				     DW9768_CLOCK_PRE_SCALE_SEL_MASK,
				     dw9768->घड़ी_presc);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Set AAC Timing */
	अगर (dw9768->aac_timing != DW9768_AAC_TIME_DEFAULT) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(client, DW9768_AAC_TIME_REG,
						dw9768->aac_timing);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	क्रम (val = dw9768->focus->val % DW9768_MOVE_STEPS;
	     val <= dw9768->focus->val;
	     val += DW9768_MOVE_STEPS) अणु
		ret = dw9768_set_dac(dw9768, val);
		अगर (ret) अणु
			dev_err(&client->dev, "I2C failure: %d", ret);
			वापस ret;
		पूर्ण
		usleep_range(dw9768->move_delay_us,
			     dw9768->move_delay_us + 1000);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dw9768_release(काष्ठा dw9768 *dw9768)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&dw9768->sd);
	पूर्णांक ret, val;

	val = round_करोwn(dw9768->focus->val, DW9768_MOVE_STEPS);
	क्रम ( ; val >= 0; val -= DW9768_MOVE_STEPS) अणु
		ret = dw9768_set_dac(dw9768, val);
		अगर (ret) अणु
			dev_err(&client->dev, "I2C write fail: %d", ret);
			वापस ret;
		पूर्ण
		usleep_range(dw9768->move_delay_us,
			     dw9768->move_delay_us + 1000);
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte_data(client, DW9768_RING_PD_CONTROL_REG,
					DW9768_PD_MODE_EN);
	अगर (ret < 0)
		वापस ret;

	/*
	 * DW9769 requires रुकोing delay समय of t_OPR
	 * after PD reset takes place.
	 */
	usleep_range(DW9768_T_OPR_US, DW9768_T_OPR_US + 100);

	वापस 0;
पूर्ण

अटल पूर्णांक dw9768_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा dw9768 *dw9768 = sd_to_dw9768(sd);

	dw9768_release(dw9768);
	regulator_bulk_disable(ARRAY_SIZE(dw9768_supply_names),
			       dw9768->supplies);

	वापस 0;
पूर्ण

अटल पूर्णांक dw9768_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा dw9768 *dw9768 = sd_to_dw9768(sd);
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(dw9768_supply_names),
				    dw9768->supplies);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to enable regulators\n");
		वापस ret;
	पूर्ण

	/*
	 * The datasheet refers to t_OPR that needs to be रुकोed beक्रमe sending
	 * I2C commands after घातer-up.
	 */
	usleep_range(DW9768_T_OPR_US, DW9768_T_OPR_US + 100);

	ret = dw9768_init(dw9768);
	अगर (ret < 0)
		जाओ disable_regulator;

	वापस 0;

disable_regulator:
	regulator_bulk_disable(ARRAY_SIZE(dw9768_supply_names),
			       dw9768->supplies);

	वापस ret;
पूर्ण

अटल पूर्णांक dw9768_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा dw9768 *dw9768 = container_of(ctrl->handler,
					     काष्ठा dw9768, ctrls);

	अगर (ctrl->id == V4L2_CID_FOCUS_ABSOLUTE)
		वापस dw9768_set_dac(dw9768, ctrl->val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops dw9768_ctrl_ops = अणु
	.s_ctrl = dw9768_set_ctrl,
पूर्ण;

अटल पूर्णांक dw9768_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(sd->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(sd->dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dw9768_बंद(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	pm_runसमय_put(sd->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops dw9768_पूर्णांक_ops = अणु
	.खोलो = dw9768_खोलो,
	.बंद = dw9768_बंद,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops dw9768_ops = अणु पूर्ण;

अटल पूर्णांक dw9768_init_controls(काष्ठा dw9768 *dw9768)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &dw9768->ctrls;
	स्थिर काष्ठा v4l2_ctrl_ops *ops = &dw9768_ctrl_ops;

	v4l2_ctrl_handler_init(hdl, 1);

	dw9768->focus = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_FOCUS_ABSOLUTE, 0,
					  DW9768_MAX_FOCUS_POS,
					  DW9768_FOCUS_STEPS, 0);

	अगर (hdl->error)
		वापस hdl->error;

	dw9768->sd.ctrl_handler = hdl;

	वापस 0;
पूर्ण

अटल पूर्णांक dw9768_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा dw9768 *dw9768;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	dw9768 = devm_kzalloc(dev, माप(*dw9768), GFP_KERNEL);
	अगर (!dw9768)
		वापस -ENOMEM;

	/* Initialize subdev */
	v4l2_i2c_subdev_init(&dw9768->sd, client, &dw9768_ops);

	dw9768->aac_mode = DW9768_AAC_MODE_DEFAULT;
	dw9768->aac_timing = DW9768_AAC_TIME_DEFAULT;
	dw9768->घड़ी_presc = DW9768_CLOCK_PRE_SCALE_DEFAULT;

	/* Optional indication of AAC mode select */
	fwnode_property_पढ़ो_u32(dev_fwnode(dev), "dongwoon,aac-mode",
				 &dw9768->aac_mode);

	/* Optional indication of घड़ी pre-scale select */
	fwnode_property_पढ़ो_u32(dev_fwnode(dev), "dongwoon,clock-presc",
				 &dw9768->घड़ी_presc);

	/* Optional indication of AAC Timing */
	fwnode_property_पढ़ो_u32(dev_fwnode(dev), "dongwoon,aac-timing",
				 &dw9768->aac_timing);

	dw9768->move_delay_us = dw9768_cal_move_delay(dw9768->aac_mode,
						      dw9768->घड़ी_presc,
						      dw9768->aac_timing);

	क्रम (i = 0; i < ARRAY_SIZE(dw9768_supply_names); i++)
		dw9768->supplies[i].supply = dw9768_supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(dw9768_supply_names),
				      dw9768->supplies);
	अगर (ret) अणु
		dev_err(dev, "failed to get regulators\n");
		वापस ret;
	पूर्ण

	/* Initialize controls */
	ret = dw9768_init_controls(dw9768);
	अगर (ret)
		जाओ err_मुक्त_handler;

	/* Initialize subdev */
	dw9768->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	dw9768->sd.पूर्णांकernal_ops = &dw9768_पूर्णांक_ops;

	ret = media_entity_pads_init(&dw9768->sd.entity, 0, शून्य);
	अगर (ret < 0)
		जाओ err_मुक्त_handler;

	dw9768->sd.entity.function = MEDIA_ENT_F_LENS;

	pm_runसमय_enable(dev);
	अगर (!pm_runसमय_enabled(dev)) अणु
		ret = dw9768_runसमय_resume(dev);
		अगर (ret < 0) अणु
			dev_err(dev, "failed to power on: %d\n", ret);
			जाओ err_clean_entity;
		पूर्ण
	पूर्ण

	ret = v4l2_async_रेजिस्टर_subdev(&dw9768->sd);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to register V4L2 subdev: %d", ret);
		जाओ err_घातer_off;
	पूर्ण

	वापस 0;

err_घातer_off:
	अगर (pm_runसमय_enabled(dev))
		pm_runसमय_disable(dev);
	अन्यथा
		dw9768_runसमय_suspend(dev);
err_clean_entity:
	media_entity_cleanup(&dw9768->sd.entity);
err_मुक्त_handler:
	v4l2_ctrl_handler_मुक्त(&dw9768->ctrls);

	वापस ret;
पूर्ण

अटल पूर्णांक dw9768_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा dw9768 *dw9768 = sd_to_dw9768(sd);

	v4l2_async_unरेजिस्टर_subdev(&dw9768->sd);
	v4l2_ctrl_handler_मुक्त(&dw9768->ctrls);
	media_entity_cleanup(&dw9768->sd.entity);
	pm_runसमय_disable(&client->dev);
	अगर (!pm_runसमय_status_suspended(&client->dev))
		dw9768_runसमय_suspend(&client->dev);
	pm_runसमय_set_suspended(&client->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dw9768_of_table[] = अणु
	अणु .compatible = "dongwoon,dw9768" पूर्ण,
	अणु .compatible = "giantec,gt9769" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dw9768_of_table);

अटल स्थिर काष्ठा dev_pm_ops dw9768_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(dw9768_runसमय_suspend, dw9768_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा i2c_driver dw9768_i2c_driver = अणु
	.driver = अणु
		.name = DW9768_NAME,
		.pm = &dw9768_pm_ops,
		.of_match_table = dw9768_of_table,
	पूर्ण,
	.probe_new  = dw9768_probe,
	.हटाओ = dw9768_हटाओ,
पूर्ण;
module_i2c_driver(dw9768_i2c_driver);

MODULE_AUTHOR("Dongchun Zhu <dongchun.zhu@mediatek.com>");
MODULE_DESCRIPTION("DW9768 VCM driver");
MODULE_LICENSE("GPL v2");
