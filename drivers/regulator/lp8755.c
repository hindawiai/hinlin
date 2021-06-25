<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LP8755 High Perक्रमmance Power Management Unit : System Interface Driver
 * (based on rev. 0.26)
 * Copyright 2012 Texas Instruments
 *
 * Author: Daniel(Geon Si) Jeong <daniel.jeong@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/regmap.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/platक्रमm_data/lp8755.h>

#घोषणा LP8755_REG_BUCK0	0x00
#घोषणा LP8755_REG_BUCK1	0x03
#घोषणा LP8755_REG_BUCK2	0x04
#घोषणा LP8755_REG_BUCK3	0x01
#घोषणा LP8755_REG_BUCK4	0x05
#घोषणा LP8755_REG_BUCK5	0x02
#घोषणा LP8755_REG_MAX		0xFF

#घोषणा LP8755_BUCK_EN_M	BIT(7)
#घोषणा LP8755_BUCK_LINEAR_OUT_MAX	0x76
#घोषणा LP8755_BUCK_VOUT_M	0x7F

काष्ठा lp8755_mphase अणु
	पूर्णांक nreg;
	पूर्णांक buck_num[LP8755_BUCK_MAX];
पूर्ण;

काष्ठा lp8755_chip अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा lp8755_platक्रमm_data *pdata;

	पूर्णांक irq;
	अचिन्हित पूर्णांक irqmask;

	पूर्णांक mphase;
	काष्ठा regulator_dev *rdev[LP8755_BUCK_MAX];
पूर्ण;

अटल पूर्णांक lp8755_buck_enable_समय(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक regval;
	क्रमागत lp8755_bucks id = rdev_get_id(rdev);

	ret = regmap_पढ़ो(rdev->regmap, 0x12 + id, &regval);
	अगर (ret < 0) अणु
		dev_err(&rdev->dev, "i2c access error %s\n", __func__);
		वापस ret;
	पूर्ण
	वापस (regval & 0xff) * 100;
पूर्ण

अटल पूर्णांक lp8755_buck_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक regbval = 0x0;
	क्रमागत lp8755_bucks id = rdev_get_id(rdev);
	काष्ठा lp8755_chip *pchip = rdev_get_drvdata(rdev);

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		/* क्रमced pwm mode */
		regbval = (0x01 << id);
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		/* enable स्वतःmatic pwm/pfm mode */
		ret = regmap_update_bits(rdev->regmap, 0x08 + id, 0x20, 0x00);
		अगर (ret < 0)
			जाओ err_i2c;
		अवरोध;
	हाल REGULATOR_MODE_IDLE:
		/* enable स्वतःmatic pwm/pfm/lppfm mode */
		ret = regmap_update_bits(rdev->regmap, 0x08 + id, 0x20, 0x20);
		अगर (ret < 0)
			जाओ err_i2c;

		ret = regmap_update_bits(rdev->regmap, 0x10, 0x01, 0x01);
		अगर (ret < 0)
			जाओ err_i2c;
		अवरोध;
	शेष:
		dev_err(pchip->dev, "Not supported buck mode %s\n", __func__);
		/* क्रमced pwm mode */
		regbval = (0x01 << id);
	पूर्ण

	ret = regmap_update_bits(rdev->regmap, 0x06, 0x01 << id, regbval);
	अगर (ret < 0)
		जाओ err_i2c;
	वापस ret;
err_i2c:
	dev_err(&rdev->dev, "i2c access error %s\n", __func__);
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक lp8755_buck_get_mode(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक regval;
	क्रमागत lp8755_bucks id = rdev_get_id(rdev);

	ret = regmap_पढ़ो(rdev->regmap, 0x06, &regval);
	अगर (ret < 0)
		जाओ err_i2c;

	/* mode fast means क्रमced pwm mode */
	अगर (regval & (0x01 << id))
		वापस REGULATOR_MODE_FAST;

	ret = regmap_पढ़ो(rdev->regmap, 0x08 + id, &regval);
	अगर (ret < 0)
		जाओ err_i2c;

	/* mode idle means स्वतःmatic pwm/pfm/lppfm mode */
	अगर (regval & 0x20)
		वापस REGULATOR_MODE_IDLE;

	/* mode normal means स्वतःmatic pwm/pfm mode */
	वापस REGULATOR_MODE_NORMAL;

err_i2c:
	dev_err(&rdev->dev, "i2c access error %s\n", __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक lp8755_buck_set_ramp(काष्ठा regulator_dev *rdev, पूर्णांक ramp)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक regval = 0x00;
	क्रमागत lp8755_bucks id = rdev_get_id(rdev);

	/* uV/us */
	चयन (ramp) अणु
	हाल 0 ... 230:
		regval = 0x07;
		अवरोध;
	हाल 231 ... 470:
		regval = 0x06;
		अवरोध;
	हाल 471 ... 940:
		regval = 0x05;
		अवरोध;
	हाल 941 ... 1900:
		regval = 0x04;
		अवरोध;
	हाल 1901 ... 3800:
		regval = 0x03;
		अवरोध;
	हाल 3801 ... 7500:
		regval = 0x02;
		अवरोध;
	हाल 7501 ... 15000:
		regval = 0x01;
		अवरोध;
	हाल 15001 ... 30000:
		regval = 0x00;
		अवरोध;
	शेष:
		dev_err(&rdev->dev,
			"Not supported ramp value %d %s\n", ramp, __func__);
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(rdev->regmap, 0x07 + id, 0x07, regval);
	अगर (ret < 0)
		जाओ err_i2c;
	वापस ret;
err_i2c:
	dev_err(&rdev->dev, "i2c access error %s\n", __func__);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regulator_ops lp8755_buck_ops = अणु
	.map_voltage = regulator_map_voltage_linear,
	.list_voltage = regulator_list_voltage_linear,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.enable_समय = lp8755_buck_enable_समय,
	.set_mode = lp8755_buck_set_mode,
	.get_mode = lp8755_buck_get_mode,
	.set_ramp_delay = lp8755_buck_set_ramp,
पूर्ण;

#घोषणा lp8755_rail(_id) "lp8755_buck"#_id
#घोषणा lp8755_buck_init(_id)\
अणु\
	.स्थिरraपूर्णांकs = अणु\
		.name = lp8755_rail(_id),\
		.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE,\
		.min_uV = 500000,\
		.max_uV = 1675000,\
	पूर्ण,\
पूर्ण

अटल काष्ठा regulator_init_data lp8755_reg_शेष[LP8755_BUCK_MAX] = अणु
	[LP8755_BUCK0] = lp8755_buck_init(0),
	[LP8755_BUCK1] = lp8755_buck_init(1),
	[LP8755_BUCK2] = lp8755_buck_init(2),
	[LP8755_BUCK3] = lp8755_buck_init(3),
	[LP8755_BUCK4] = lp8755_buck_init(4),
	[LP8755_BUCK5] = lp8755_buck_init(5),
पूर्ण;

अटल स्थिर काष्ठा lp8755_mphase mphase_buck[MPHASE_CONF_MAX] = अणु
	अणु 3, अणु LP8755_BUCK0, LP8755_BUCK3, LP8755_BUCK5 पूर्ण पूर्ण,
	अणु 6, अणु LP8755_BUCK0, LP8755_BUCK1, LP8755_BUCK2, LP8755_BUCK3,
	       LP8755_BUCK4, LP8755_BUCK5 पूर्ण पूर्ण,
	अणु 5, अणु LP8755_BUCK0, LP8755_BUCK2, LP8755_BUCK3, LP8755_BUCK4,
	       LP8755_BUCK5पूर्ण पूर्ण,
	अणु 4, अणु LP8755_BUCK0, LP8755_BUCK3, LP8755_BUCK4, LP8755_BUCK5पूर्ण पूर्ण,
	अणु 3, अणु LP8755_BUCK0, LP8755_BUCK4, LP8755_BUCK5पूर्ण पूर्ण,
	अणु 2, अणु LP8755_BUCK0, LP8755_BUCK5पूर्ण पूर्ण,
	अणु 1, अणु LP8755_BUCK0पूर्ण पूर्ण,
	अणु 2, अणु LP8755_BUCK0, LP8755_BUCK3पूर्ण पूर्ण,
	अणु 4, अणु LP8755_BUCK0, LP8755_BUCK2, LP8755_BUCK3, LP8755_BUCK5पूर्ण पूर्ण,
पूर्ण;

अटल पूर्णांक lp8755_init_data(काष्ठा lp8755_chip *pchip)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret, icnt, buck_num;
	काष्ठा lp8755_platक्रमm_data *pdata = pchip->pdata;

	/* पढ़ो back  muti-phase configuration */
	ret = regmap_पढ़ो(pchip->regmap, 0x3D, &regval);
	अगर (ret < 0)
		जाओ out_i2c_error;
	pchip->mphase = regval & 0x0F;

	/* set शेष data based on multi-phase config */
	क्रम (icnt = 0; icnt < mphase_buck[pchip->mphase].nreg; icnt++) अणु
		buck_num = mphase_buck[pchip->mphase].buck_num[icnt];
		pdata->buck_data[buck_num] = &lp8755_reg_शेष[buck_num];
	पूर्ण
	वापस ret;

out_i2c_error:
	dev_err(pchip->dev, "i2c access error %s\n", __func__);
	वापस ret;
पूर्ण

#घोषणा lp8755_buck_desc(_id)\
अणु\
	.name = lp8755_rail(_id),\
	.id   = LP8755_BUCK##_id,\
	.ops  = &lp8755_buck_ops,\
	.n_voltages = LP8755_BUCK_LINEAR_OUT_MAX+1,\
	.uV_step = 10000,\
	.min_uV = 500000,\
	.type = REGULATOR_VOLTAGE,\
	.owner = THIS_MODULE,\
	.enable_reg = LP8755_REG_BUCK##_id,\
	.enable_mask = LP8755_BUCK_EN_M,\
	.vsel_reg = LP8755_REG_BUCK##_id,\
	.vsel_mask = LP8755_BUCK_VOUT_M,\
पूर्ण

अटल स्थिर काष्ठा regulator_desc lp8755_regulators[] = अणु
	lp8755_buck_desc(0),
	lp8755_buck_desc(1),
	lp8755_buck_desc(2),
	lp8755_buck_desc(3),
	lp8755_buck_desc(4),
	lp8755_buck_desc(5),
पूर्ण;

अटल पूर्णांक lp8755_regulator_init(काष्ठा lp8755_chip *pchip)
अणु
	पूर्णांक ret, icnt, buck_num;
	काष्ठा lp8755_platक्रमm_data *pdata = pchip->pdata;
	काष्ठा regulator_config rconfig = अणु पूर्ण;

	rconfig.regmap = pchip->regmap;
	rconfig.dev = pchip->dev;
	rconfig.driver_data = pchip;

	क्रम (icnt = 0; icnt < mphase_buck[pchip->mphase].nreg; icnt++) अणु
		buck_num = mphase_buck[pchip->mphase].buck_num[icnt];
		rconfig.init_data = pdata->buck_data[buck_num];
		rconfig.of_node = pchip->dev->of_node;
		pchip->rdev[buck_num] =
		    devm_regulator_रेजिस्टर(pchip->dev,
				    &lp8755_regulators[buck_num], &rconfig);
		अगर (IS_ERR(pchip->rdev[buck_num])) अणु
			ret = PTR_ERR(pchip->rdev[buck_num]);
			pchip->rdev[buck_num] = शून्य;
			dev_err(pchip->dev, "regulator init failed: buck %d\n",
				buck_num);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t lp8755_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	पूर्णांक ret, icnt;
	अचिन्हित पूर्णांक flag0, flag1;
	काष्ठा lp8755_chip *pchip = data;

	/* पढ़ो flag0 रेजिस्टर */
	ret = regmap_पढ़ो(pchip->regmap, 0x0D, &flag0);
	अगर (ret < 0)
		जाओ err_i2c;
	/* clear flag रेजिस्टर to pull up पूर्णांक. pin */
	ret = regmap_ग_लिखो(pchip->regmap, 0x0D, 0x00);
	अगर (ret < 0)
		जाओ err_i2c;

	/* sent घातer fault detection event to specअगरic regulator */
	क्रम (icnt = 0; icnt < LP8755_BUCK_MAX; icnt++)
		अगर ((flag0 & (0x4 << icnt))
		    && (pchip->irqmask & (0x04 << icnt))
		    && (pchip->rdev[icnt] != शून्य)) अणु
			regulator_notअगरier_call_chain(pchip->rdev[icnt],
						      LP8755_EVENT_PWR_FAULT,
						      शून्य);
		पूर्ण

	/* पढ़ो flag1 रेजिस्टर */
	ret = regmap_पढ़ो(pchip->regmap, 0x0E, &flag1);
	अगर (ret < 0)
		जाओ err_i2c;
	/* clear flag रेजिस्टर to pull up पूर्णांक. pin */
	ret = regmap_ग_लिखो(pchip->regmap, 0x0E, 0x00);
	अगर (ret < 0)
		जाओ err_i2c;

	/* send OCP event to all regulator devices */
	अगर ((flag1 & 0x01) && (pchip->irqmask & 0x01))
		क्रम (icnt = 0; icnt < LP8755_BUCK_MAX; icnt++)
			अगर (pchip->rdev[icnt] != शून्य) अणु
				regulator_notअगरier_call_chain(pchip->rdev[icnt],
							      LP8755_EVENT_OCP,
							      शून्य);
			पूर्ण

	/* send OVP event to all regulator devices */
	अगर ((flag1 & 0x02) && (pchip->irqmask & 0x02))
		क्रम (icnt = 0; icnt < LP8755_BUCK_MAX; icnt++)
			अगर (pchip->rdev[icnt] != शून्य) अणु
				regulator_notअगरier_call_chain(pchip->rdev[icnt],
							      LP8755_EVENT_OVP,
							      शून्य);
			पूर्ण
	वापस IRQ_HANDLED;

err_i2c:
	dev_err(pchip->dev, "i2c access error %s\n", __func__);
	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक lp8755_पूर्णांक_config(काष्ठा lp8755_chip *pchip)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक regval;

	अगर (pchip->irq == 0) अणु
		dev_warn(pchip->dev, "not use interrupt : %s\n", __func__);
		वापस 0;
	पूर्ण

	ret = regmap_पढ़ो(pchip->regmap, 0x0F, &regval);
	अगर (ret < 0) अणु
		dev_err(pchip->dev, "i2c access error %s\n", __func__);
		वापस ret;
	पूर्ण

	pchip->irqmask = regval;
	वापस devm_request_thपढ़ोed_irq(pchip->dev, pchip->irq, शून्य,
					 lp8755_irq_handler,
					 IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					 "lp8755-irq", pchip);
पूर्ण

अटल स्थिर काष्ठा regmap_config lp8755_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = LP8755_REG_MAX,
पूर्ण;

अटल पूर्णांक lp8755_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret, icnt;
	काष्ठा lp8755_chip *pchip;
	काष्ठा lp8755_platक्रमm_data *pdata = dev_get_platdata(&client->dev);

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev, "i2c functionality check fail.\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	pchip = devm_kzalloc(&client->dev,
			     माप(काष्ठा lp8755_chip), GFP_KERNEL);
	अगर (!pchip)
		वापस -ENOMEM;

	pchip->dev = &client->dev;
	pchip->regmap = devm_regmap_init_i2c(client, &lp8755_regmap);
	अगर (IS_ERR(pchip->regmap)) अणु
		ret = PTR_ERR(pchip->regmap);
		dev_err(&client->dev, "fail to allocate regmap %d\n", ret);
		वापस ret;
	पूर्ण
	i2c_set_clientdata(client, pchip);

	अगर (pdata != शून्य) अणु
		pchip->pdata = pdata;
		pchip->mphase = pdata->mphase;
	पूर्ण अन्यथा अणु
		pchip->pdata = devm_kzalloc(pchip->dev,
					    माप(काष्ठा lp8755_platक्रमm_data),
					    GFP_KERNEL);
		अगर (!pchip->pdata)
			वापस -ENOMEM;
		ret = lp8755_init_data(pchip);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "fail to initialize chip\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = lp8755_regulator_init(pchip);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "fail to initialize regulators\n");
		जाओ err;
	पूर्ण

	pchip->irq = client->irq;
	ret = lp8755_पूर्णांक_config(pchip);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "fail to irq config\n");
		जाओ err;
	पूर्ण

	वापस ret;

err:
	/* output disable */
	क्रम (icnt = 0; icnt < LP8755_BUCK_MAX; icnt++)
		regmap_ग_लिखो(pchip->regmap, icnt, 0x00);

	वापस ret;
पूर्ण

अटल पूर्णांक lp8755_हटाओ(काष्ठा i2c_client *client)
अणु
	पूर्णांक icnt;
	काष्ठा lp8755_chip *pchip = i2c_get_clientdata(client);

	क्रम (icnt = 0; icnt < LP8755_BUCK_MAX; icnt++)
		regmap_ग_लिखो(pchip->regmap, icnt, 0x00);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lp8755_id[] = अणु
	अणुLP8755_NAME, 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, lp8755_id);

अटल काष्ठा i2c_driver lp8755_i2c_driver = अणु
	.driver = अणु
		   .name = LP8755_NAME,
		   पूर्ण,
	.probe = lp8755_probe,
	.हटाओ = lp8755_हटाओ,
	.id_table = lp8755_id,
पूर्ण;

अटल पूर्णांक __init lp8755_init(व्योम)
अणु
	वापस i2c_add_driver(&lp8755_i2c_driver);
पूर्ण

subsys_initcall(lp8755_init);

अटल व्योम __निकास lp8755_निकास(व्योम)
अणु
	i2c_del_driver(&lp8755_i2c_driver);
पूर्ण

module_निकास(lp8755_निकास);

MODULE_DESCRIPTION("Texas Instruments lp8755 driver");
MODULE_AUTHOR("Daniel Jeong <daniel.jeong@ti.com>");
MODULE_LICENSE("GPL v2");
