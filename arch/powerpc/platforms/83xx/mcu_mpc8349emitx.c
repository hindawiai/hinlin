<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Power Management and GPIO expander driver क्रम MPC8349E-mITX-compatible MCU
 *
 * Copyright (c) 2008  MontaVista Software, Inc.
 *
 * Author: Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/reboot.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>

/*
 * I करोn't have specअगरications क्रम the MCU firmware, I found this रेजिस्टर
 * and bits positions by the trial&error method.
 */
#घोषणा MCU_REG_CTRL	0x20
#घोषणा MCU_CTRL_POFF	0x40
#घोषणा MCU_CTRL_BTN	0x80

#घोषणा MCU_NUM_GPIO	2

काष्ठा mcu अणु
	काष्ठा mutex lock;
	काष्ठा i2c_client *client;
	काष्ठा gpio_chip gc;
	u8 reg_ctrl;
पूर्ण;

अटल काष्ठा mcu *glob_mcu;

काष्ठा task_काष्ठा *shutकरोwn_thपढ़ो;
अटल पूर्णांक shutकरोwn_thपढ़ो_fn(व्योम *data)
अणु
	पूर्णांक ret;
	काष्ठा mcu *mcu = glob_mcu;

	जबतक (!kthपढ़ो_should_stop()) अणु
		ret = i2c_smbus_पढ़ो_byte_data(mcu->client, MCU_REG_CTRL);
		अगर (ret < 0)
			pr_err("MCU status reg read failed.\n");
		mcu->reg_ctrl = ret;


		अगर (mcu->reg_ctrl & MCU_CTRL_BTN) अणु
			i2c_smbus_ग_लिखो_byte_data(mcu->client, MCU_REG_CTRL,
						  mcu->reg_ctrl & ~MCU_CTRL_BTN);

			ctrl_alt_del();
		पूर्ण

		set_current_state(TASK_INTERRUPTIBLE);
		schedule_समयout(HZ);
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार show_status(काष्ठा device *d,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक ret;
	काष्ठा mcu *mcu = glob_mcu;

	ret = i2c_smbus_पढ़ो_byte_data(mcu->client, MCU_REG_CTRL);
	अगर (ret < 0)
		वापस -ENODEV;
	mcu->reg_ctrl = ret;

	वापस प्र_लिखो(buf, "%02x\n", ret);
पूर्ण
अटल DEVICE_ATTR(status, 0444, show_status, शून्य);

अटल व्योम mcu_घातer_off(व्योम)
अणु
	काष्ठा mcu *mcu = glob_mcu;

	pr_info("Sending power-off request to the MCU...\n");
	mutex_lock(&mcu->lock);
	i2c_smbus_ग_लिखो_byte_data(mcu->client, MCU_REG_CTRL,
				  mcu->reg_ctrl | MCU_CTRL_POFF);
	mutex_unlock(&mcu->lock);
पूर्ण

अटल व्योम mcu_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	काष्ठा mcu *mcu = gpiochip_get_data(gc);
	u8 bit = 1 << (4 + gpio);

	mutex_lock(&mcu->lock);
	अगर (val)
		mcu->reg_ctrl &= ~bit;
	अन्यथा
		mcu->reg_ctrl |= bit;

	i2c_smbus_ग_लिखो_byte_data(mcu->client, MCU_REG_CTRL, mcu->reg_ctrl);
	mutex_unlock(&mcu->lock);
पूर्ण

अटल पूर्णांक mcu_gpio_dir_out(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	mcu_gpio_set(gc, gpio, val);
	वापस 0;
पूर्ण

अटल पूर्णांक mcu_gpiochip_add(काष्ठा mcu *mcu)
अणु
	काष्ठा device_node *np;
	काष्ठा gpio_chip *gc = &mcu->gc;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,mcu-mpc8349emitx");
	अगर (!np)
		वापस -ENODEV;

	gc->owner = THIS_MODULE;
	gc->label = kaप्र_लिखो(GFP_KERNEL, "%pOF", np);
	gc->can_sleep = 1;
	gc->ngpio = MCU_NUM_GPIO;
	gc->base = -1;
	gc->set = mcu_gpio_set;
	gc->direction_output = mcu_gpio_dir_out;
	gc->of_node = np;

	वापस gpiochip_add_data(gc, mcu);
पूर्ण

अटल पूर्णांक mcu_gpiochip_हटाओ(काष्ठा mcu *mcu)
अणु
	kमुक्त(mcu->gc.label);
	gpiochip_हटाओ(&mcu->gc);
	वापस 0;
पूर्ण

अटल पूर्णांक mcu_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा mcu *mcu;
	पूर्णांक ret;

	mcu = kzalloc(माप(*mcu), GFP_KERNEL);
	अगर (!mcu)
		वापस -ENOMEM;

	mutex_init(&mcu->lock);
	mcu->client = client;
	i2c_set_clientdata(client, mcu);

	ret = i2c_smbus_पढ़ो_byte_data(mcu->client, MCU_REG_CTRL);
	अगर (ret < 0)
		जाओ err;
	mcu->reg_ctrl = ret;

	ret = mcu_gpiochip_add(mcu);
	अगर (ret)
		जाओ err;

	/* XXX: this is potentially racy, but there is no lock क्रम pm_घातer_off */
	अगर (!pm_घातer_off) अणु
		glob_mcu = mcu;
		pm_घातer_off = mcu_घातer_off;
		dev_info(&client->dev, "will provide power-off service\n");
	पूर्ण

	अगर (device_create_file(&client->dev, &dev_attr_status))
		dev_err(&client->dev,
			"couldn't create device file for status\n");

	shutकरोwn_thपढ़ो = kthपढ़ो_run(shutकरोwn_thपढ़ो_fn, शून्य,
				      "mcu-i2c-shdn");

	वापस 0;
err:
	kमुक्त(mcu);
	वापस ret;
पूर्ण

अटल पूर्णांक mcu_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा mcu *mcu = i2c_get_clientdata(client);
	पूर्णांक ret;

	kthपढ़ो_stop(shutकरोwn_thपढ़ो);

	device_हटाओ_file(&client->dev, &dev_attr_status);

	अगर (glob_mcu == mcu) अणु
		pm_घातer_off = शून्य;
		glob_mcu = शून्य;
	पूर्ण

	ret = mcu_gpiochip_हटाओ(mcu);
	अगर (ret)
		वापस ret;
	kमुक्त(mcu);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id mcu_ids[] = अणु
	अणु "mcu-mpc8349emitx", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mcu_ids);

अटल स्थिर काष्ठा of_device_id mcu_of_match_table[] = अणु
	अणु .compatible = "fsl,mcu-mpc8349emitx", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा i2c_driver mcu_driver = अणु
	.driver = अणु
		.name = "mcu-mpc8349emitx",
		.of_match_table = mcu_of_match_table,
	पूर्ण,
	.probe_new = mcu_probe,
	.हटाओ	= mcu_हटाओ,
	.id_table = mcu_ids,
पूर्ण;

module_i2c_driver(mcu_driver);

MODULE_DESCRIPTION("Power Management and GPIO expander driver for "
		   "MPC8349E-mITX-compatible MCU");
MODULE_AUTHOR("Anton Vorontsov <avorontsov@ru.mvista.com>");
MODULE_LICENSE("GPL");
