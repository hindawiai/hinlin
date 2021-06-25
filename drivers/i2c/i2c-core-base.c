<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux I2C core
 *
 * Copyright (C) 1995-99 Simon G. Vogl
 *   With some changes from Kyथघsti Mथअlkki <kmalkki@cc.hut.fi>
 *   Mux support by Roकरोlfo Giometti <giometti@enneenne.com> and
 *   Michael Lawnick <michael.lawnick.ext@nsn.com>
 *
 * Copyright (C) 2013-2017 Wolfram Sang <wsa@kernel.org>
 */

#घोषणा pr_fmt(fmt) "i2c-core: " fmt

#समावेश <dt-bindings/i2c/i2c.h>
#समावेश <linux/acpi.h>
#समावेश <linux/clk/clk-conf.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-smbus.h>
#समावेश <linux/idr.h>
#समावेश <linux/init.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_wakeirq.h>
#समावेश <linux/property.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/slab.h>

#समावेश "i2c-core.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/i2c.h>

#घोषणा I2C_ADDR_OFFSET_TEN_BIT	0xa000
#घोषणा I2C_ADDR_OFFSET_SLAVE	0x1000

#घोषणा I2C_ADDR_7BITS_MAX	0x77
#घोषणा I2C_ADDR_7BITS_COUNT	(I2C_ADDR_7BITS_MAX + 1)

#घोषणा I2C_ADDR_DEVICE_ID	0x7c

/*
 * core_lock protects i2c_adapter_idr, and guarantees that device detection,
 * deletion of detected devices are serialized
 */
अटल DEFINE_MUTEX(core_lock);
अटल DEFINE_IDR(i2c_adapter_idr);

अटल पूर्णांक i2c_detect(काष्ठा i2c_adapter *adapter, काष्ठा i2c_driver *driver);

अटल DEFINE_STATIC_KEY_FALSE(i2c_trace_msg_key);
अटल bool is_रेजिस्टरed;

पूर्णांक i2c_transfer_trace_reg(व्योम)
अणु
	अटल_branch_inc(&i2c_trace_msg_key);
	वापस 0;
पूर्ण

व्योम i2c_transfer_trace_unreg(व्योम)
अणु
	अटल_branch_dec(&i2c_trace_msg_key);
पूर्ण

स्थिर अक्षर *i2c_freq_mode_string(u32 bus_freq_hz)
अणु
	चयन (bus_freq_hz) अणु
	हाल I2C_MAX_STANDARD_MODE_FREQ:
		वापस "Standard Mode (100 kHz)";
	हाल I2C_MAX_FAST_MODE_FREQ:
		वापस "Fast Mode (400 kHz)";
	हाल I2C_MAX_FAST_MODE_PLUS_FREQ:
		वापस "Fast Mode Plus (1.0 MHz)";
	हाल I2C_MAX_TURBO_MODE_FREQ:
		वापस "Turbo Mode (1.4 MHz)";
	हाल I2C_MAX_HIGH_SPEED_MODE_FREQ:
		वापस "High Speed Mode (3.4 MHz)";
	हाल I2C_MAX_ULTRA_FAST_MODE_FREQ:
		वापस "Ultra Fast Mode (5.0 MHz)";
	शेष:
		वापस "Unknown Mode";
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(i2c_freq_mode_string);

स्थिर काष्ठा i2c_device_id *i2c_match_id(स्थिर काष्ठा i2c_device_id *id,
						स्थिर काष्ठा i2c_client *client)
अणु
	अगर (!(id && client))
		वापस शून्य;

	जबतक (id->name[0]) अणु
		अगर (म_भेद(client->name, id->name) == 0)
			वापस id;
		id++;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_match_id);

अटल पूर्णांक i2c_device_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा i2c_client	*client = i2c_verअगरy_client(dev);
	काष्ठा i2c_driver	*driver;


	/* Attempt an OF style match */
	अगर (i2c_of_match_device(drv->of_match_table, client))
		वापस 1;

	/* Then ACPI style match */
	अगर (acpi_driver_match_device(dev, drv))
		वापस 1;

	driver = to_i2c_driver(drv);

	/* Finally an I2C match */
	अगर (i2c_match_id(driver->id_table, client))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_device_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक rc;

	rc = of_device_uevent_modalias(dev, env);
	अगर (rc != -ENODEV)
		वापस rc;

	rc = acpi_device_uevent_modalias(dev, env);
	अगर (rc != -ENODEV)
		वापस rc;

	वापस add_uevent_var(env, "MODALIAS=%s%s", I2C_MODULE_PREFIX, client->name);
पूर्ण

/* i2c bus recovery routines */
अटल पूर्णांक get_scl_gpio_value(काष्ठा i2c_adapter *adap)
अणु
	वापस gpiod_get_value_cansleep(adap->bus_recovery_info->scl_gpiod);
पूर्ण

अटल व्योम set_scl_gpio_value(काष्ठा i2c_adapter *adap, पूर्णांक val)
अणु
	gpiod_set_value_cansleep(adap->bus_recovery_info->scl_gpiod, val);
पूर्ण

अटल पूर्णांक get_sda_gpio_value(काष्ठा i2c_adapter *adap)
अणु
	वापस gpiod_get_value_cansleep(adap->bus_recovery_info->sda_gpiod);
पूर्ण

अटल व्योम set_sda_gpio_value(काष्ठा i2c_adapter *adap, पूर्णांक val)
अणु
	gpiod_set_value_cansleep(adap->bus_recovery_info->sda_gpiod, val);
पूर्ण

अटल पूर्णांक i2c_generic_bus_मुक्त(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा i2c_bus_recovery_info *bri = adap->bus_recovery_info;
	पूर्णांक ret = -EOPNOTSUPP;

	अगर (bri->get_bus_मुक्त)
		ret = bri->get_bus_मुक्त(adap);
	अन्यथा अगर (bri->get_sda)
		ret = bri->get_sda(adap);

	अगर (ret < 0)
		वापस ret;

	वापस ret ? 0 : -EBUSY;
पूर्ण

/*
 * We are generating घड़ी pulses. ndelay() determines durating of clk pulses.
 * We will generate घड़ी with rate 100 KHz and so duration of both घड़ी levels
 * is: delay in ns = (10^6 / 100) / 2
 */
#घोषणा RECOVERY_NDELAY		5000
#घोषणा RECOVERY_CLK_CNT	9

पूर्णांक i2c_generic_scl_recovery(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा i2c_bus_recovery_info *bri = adap->bus_recovery_info;
	पूर्णांक i = 0, scl = 1, ret = 0;

	अगर (bri->prepare_recovery)
		bri->prepare_recovery(adap);
	अगर (bri->pinctrl)
		pinctrl_select_state(bri->pinctrl, bri->pins_gpio);

	/*
	 * If we can set SDA, we will always create a STOP to ensure additional
	 * pulses will करो no harm. This is achieved by letting SDA follow SCL
	 * half a cycle later. Check the 'incomplete_write_byte' fault injector
	 * क्रम details. Note that we must honour tsu:sto, 4us, but lets use 5us
	 * here क्रम simplicity.
	 */
	bri->set_scl(adap, scl);
	ndelay(RECOVERY_NDELAY);
	अगर (bri->set_sda)
		bri->set_sda(adap, scl);
	ndelay(RECOVERY_NDELAY / 2);

	/*
	 * By this समय SCL is high, as we need to give 9 falling-rising edges
	 */
	जबतक (i++ < RECOVERY_CLK_CNT * 2) अणु
		अगर (scl) अणु
			/* SCL shouldn't be low here */
			अगर (!bri->get_scl(adap)) अणु
				dev_err(&adap->dev,
					"SCL is stuck low, exit recovery\n");
				ret = -EBUSY;
				अवरोध;
			पूर्ण
		पूर्ण

		scl = !scl;
		bri->set_scl(adap, scl);
		/* Creating STOP again, see above */
		अगर (scl)  अणु
			/* Honour minimum tsu:sto */
			ndelay(RECOVERY_NDELAY);
		पूर्ण अन्यथा अणु
			/* Honour minimum tf and thd:dat */
			ndelay(RECOVERY_NDELAY / 2);
		पूर्ण
		अगर (bri->set_sda)
			bri->set_sda(adap, scl);
		ndelay(RECOVERY_NDELAY / 2);

		अगर (scl) अणु
			ret = i2c_generic_bus_मुक्त(adap);
			अगर (ret == 0)
				अवरोध;
		पूर्ण
	पूर्ण

	/* If we can't check bus status, assume recovery worked */
	अगर (ret == -EOPNOTSUPP)
		ret = 0;

	अगर (bri->unprepare_recovery)
		bri->unprepare_recovery(adap);
	अगर (bri->pinctrl)
		pinctrl_select_state(bri->pinctrl, bri->pins_शेष);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_generic_scl_recovery);

पूर्णांक i2c_recover_bus(काष्ठा i2c_adapter *adap)
अणु
	अगर (!adap->bus_recovery_info)
		वापस -EBUSY;

	dev_dbg(&adap->dev, "Trying i2c bus recovery\n");
	वापस adap->bus_recovery_info->recover_bus(adap);
पूर्ण
EXPORT_SYMBOL_GPL(i2c_recover_bus);

अटल व्योम i2c_gpio_init_pinctrl_recovery(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा i2c_bus_recovery_info *bri = adap->bus_recovery_info;
	काष्ठा device *dev = &adap->dev;
	काष्ठा pinctrl *p = bri->pinctrl;

	/*
	 * we can't change states without pinctrl, so हटाओ the states अगर
	 * populated
	 */
	अगर (!p) अणु
		bri->pins_शेष = शून्य;
		bri->pins_gpio = शून्य;
		वापस;
	पूर्ण

	अगर (!bri->pins_शेष) अणु
		bri->pins_शेष = pinctrl_lookup_state(p,
							 PINCTRL_STATE_DEFAULT);
		अगर (IS_ERR(bri->pins_शेष)) अणु
			dev_dbg(dev, PINCTRL_STATE_DEFAULT " state not found for GPIO recovery\n");
			bri->pins_शेष = शून्य;
		पूर्ण
	पूर्ण
	अगर (!bri->pins_gpio) अणु
		bri->pins_gpio = pinctrl_lookup_state(p, "gpio");
		अगर (IS_ERR(bri->pins_gpio))
			bri->pins_gpio = pinctrl_lookup_state(p, "recovery");

		अगर (IS_ERR(bri->pins_gpio)) अणु
			dev_dbg(dev, "no gpio or recovery state found for GPIO recovery\n");
			bri->pins_gpio = शून्य;
		पूर्ण
	पूर्ण

	/* क्रम pinctrl state changes, we need all the inक्रमmation */
	अगर (bri->pins_शेष && bri->pins_gpio) अणु
		dev_info(dev, "using pinctrl states for GPIO recovery");
	पूर्ण अन्यथा अणु
		bri->pinctrl = शून्य;
		bri->pins_शेष = शून्य;
		bri->pins_gpio = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक i2c_gpio_init_generic_recovery(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा i2c_bus_recovery_info *bri = adap->bus_recovery_info;
	काष्ठा device *dev = &adap->dev;
	काष्ठा gpio_desc *gpiod;
	पूर्णांक ret = 0;

	/*
	 * करोn't touch the recovery inक्रमmation अगर the driver is not using
	 * generic SCL recovery
	 */
	अगर (bri->recover_bus && bri->recover_bus != i2c_generic_scl_recovery)
		वापस 0;

	/*
	 * pins might be taken as GPIO, so we should inक्रमm pinctrl about
	 * this and move the state to GPIO
	 */
	अगर (bri->pinctrl)
		pinctrl_select_state(bri->pinctrl, bri->pins_gpio);

	/*
	 * अगर there is incomplete or no recovery inक्रमmation, see अगर generic
	 * GPIO recovery is available
	 */
	अगर (!bri->scl_gpiod) अणु
		gpiod = devm_gpiod_get(dev, "scl", GPIOD_OUT_HIGH_OPEN_DRAIN);
		अगर (PTR_ERR(gpiod) == -EPROBE_DEFER) अणु
			ret  = -EPROBE_DEFER;
			जाओ cleanup_pinctrl_state;
		पूर्ण
		अगर (!IS_ERR(gpiod)) अणु
			bri->scl_gpiod = gpiod;
			bri->recover_bus = i2c_generic_scl_recovery;
			dev_info(dev, "using generic GPIOs for recovery\n");
		पूर्ण
	पूर्ण

	/* SDA GPIOD line is optional, so we care about DEFER only */
	अगर (!bri->sda_gpiod) अणु
		/*
		 * We have SCL. Pull SCL low and रुको a bit so that SDA glitches
		 * have no effect.
		 */
		gpiod_direction_output(bri->scl_gpiod, 0);
		udelay(10);
		gpiod = devm_gpiod_get(dev, "sda", GPIOD_IN);

		/* Wait a bit in हाल of a SDA glitch, and then release SCL. */
		udelay(10);
		gpiod_direction_output(bri->scl_gpiod, 1);

		अगर (PTR_ERR(gpiod) == -EPROBE_DEFER) अणु
			ret = -EPROBE_DEFER;
			जाओ cleanup_pinctrl_state;
		पूर्ण
		अगर (!IS_ERR(gpiod))
			bri->sda_gpiod = gpiod;
	पूर्ण

cleanup_pinctrl_state:
	/* change the state of the pins back to their शेष state */
	अगर (bri->pinctrl)
		pinctrl_select_state(bri->pinctrl, bri->pins_शेष);

	वापस ret;
पूर्ण

अटल पूर्णांक i2c_gpio_init_recovery(काष्ठा i2c_adapter *adap)
अणु
	i2c_gpio_init_pinctrl_recovery(adap);
	वापस i2c_gpio_init_generic_recovery(adap);
पूर्ण

अटल पूर्णांक i2c_init_recovery(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा i2c_bus_recovery_info *bri = adap->bus_recovery_info;
	अक्षर *err_str, *err_level = KERN_ERR;

	अगर (!bri)
		वापस 0;

	अगर (i2c_gpio_init_recovery(adap) == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	अगर (!bri->recover_bus) अणु
		err_str = "no suitable method provided";
		err_level = KERN_DEBUG;
		जाओ err;
	पूर्ण

	अगर (bri->scl_gpiod && bri->recover_bus == i2c_generic_scl_recovery) अणु
		bri->get_scl = get_scl_gpio_value;
		bri->set_scl = set_scl_gpio_value;
		अगर (bri->sda_gpiod) अणु
			bri->get_sda = get_sda_gpio_value;
			/* FIXME: add proper flag instead of '0' once available */
			अगर (gpiod_get_direction(bri->sda_gpiod) == 0)
				bri->set_sda = set_sda_gpio_value;
		पूर्ण
	पूर्ण अन्यथा अगर (bri->recover_bus == i2c_generic_scl_recovery) अणु
		/* Generic SCL recovery */
		अगर (!bri->set_scl || !bri->get_scl) अणु
			err_str = "no {get|set}_scl() found";
			जाओ err;
		पूर्ण
		अगर (!bri->set_sda && !bri->get_sda) अणु
			err_str = "either get_sda() or set_sda() needed";
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;
 err:
	dev_prपूर्णांकk(err_level, &adap->dev, "Not using recovery: %s\n", err_str);
	adap->bus_recovery_info = शून्य;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक i2c_smbus_host_notअगरy_to_irq(स्थिर काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_adapter *adap = client->adapter;
	अचिन्हित पूर्णांक irq;

	अगर (!adap->host_notअगरy_करोमुख्य)
		वापस -ENXIO;

	अगर (client->flags & I2C_CLIENT_TEN)
		वापस -EINVAL;

	irq = irq_create_mapping(adap->host_notअगरy_करोमुख्य, client->addr);

	वापस irq > 0 ? irq : -ENXIO;
पूर्ण

अटल पूर्णांक i2c_device_probe(काष्ठा device *dev)
अणु
	काष्ठा i2c_client	*client = i2c_verअगरy_client(dev);
	काष्ठा i2c_driver	*driver;
	पूर्णांक status;

	अगर (!client)
		वापस 0;

	client->irq = client->init_irq;

	अगर (!client->irq) अणु
		पूर्णांक irq = -ENOENT;

		अगर (client->flags & I2C_CLIENT_HOST_NOTIFY) अणु
			dev_dbg(dev, "Using Host Notify IRQ\n");
			/* Keep adapter active when Host Notअगरy is required */
			pm_runसमय_get_sync(&client->adapter->dev);
			irq = i2c_smbus_host_notअगरy_to_irq(client);
		पूर्ण अन्यथा अगर (dev->of_node) अणु
			irq = of_irq_get_byname(dev->of_node, "irq");
			अगर (irq == -EINVAL || irq == -ENODATA)
				irq = of_irq_get(dev->of_node, 0);
		पूर्ण अन्यथा अगर (ACPI_COMPANION(dev)) अणु
			irq = i2c_acpi_get_irq(client);
		पूर्ण
		अगर (irq == -EPROBE_DEFER) अणु
			status = irq;
			जाओ put_sync_adapter;
		पूर्ण

		अगर (irq < 0)
			irq = 0;

		client->irq = irq;
	पूर्ण

	driver = to_i2c_driver(dev->driver);

	/*
	 * An I2C ID table is not mandatory, अगर and only अगर, a suitable OF
	 * or ACPI ID table is supplied क्रम the probing device.
	 */
	अगर (!driver->id_table &&
	    !acpi_driver_match_device(dev, dev->driver) &&
	    !i2c_of_match_device(dev->driver->of_match_table, client)) अणु
		status = -ENODEV;
		जाओ put_sync_adapter;
	पूर्ण

	अगर (client->flags & I2C_CLIENT_WAKE) अणु
		पूर्णांक wakeirq;

		wakeirq = of_irq_get_byname(dev->of_node, "wakeup");
		अगर (wakeirq == -EPROBE_DEFER) अणु
			status = wakeirq;
			जाओ put_sync_adapter;
		पूर्ण

		device_init_wakeup(&client->dev, true);

		अगर (wakeirq > 0 && wakeirq != client->irq)
			status = dev_pm_set_dedicated_wake_irq(dev, wakeirq);
		अन्यथा अगर (client->irq > 0)
			status = dev_pm_set_wake_irq(dev, client->irq);
		अन्यथा
			status = 0;

		अगर (status)
			dev_warn(&client->dev, "failed to set up wakeup irq\n");
	पूर्ण

	dev_dbg(dev, "probe\n");

	status = of_clk_set_शेषs(dev->of_node, false);
	अगर (status < 0)
		जाओ err_clear_wakeup_irq;

	status = dev_pm_करोमुख्य_attach(&client->dev, true);
	अगर (status)
		जाओ err_clear_wakeup_irq;

	client->devres_group_id = devres_खोलो_group(&client->dev, शून्य,
						    GFP_KERNEL);
	अगर (!client->devres_group_id) अणु
		status = -ENOMEM;
		जाओ err_detach_pm_करोमुख्य;
	पूर्ण

	/*
	 * When there are no more users of probe(),
	 * नाम probe_new to probe.
	 */
	अगर (driver->probe_new)
		status = driver->probe_new(client);
	अन्यथा अगर (driver->probe)
		status = driver->probe(client,
				       i2c_match_id(driver->id_table, client));
	अन्यथा
		status = -EINVAL;

	/*
	 * Note that we are not closing the devres group खोलोed above so
	 * even resources that were attached to the device after probe is
	 * run are released when i2c_device_हटाओ() is executed. This is
	 * needed as some drivers would allocate additional resources,
	 * क्रम example when updating firmware.
	 */

	अगर (status)
		जाओ err_release_driver_resources;

	वापस 0;

err_release_driver_resources:
	devres_release_group(&client->dev, client->devres_group_id);
err_detach_pm_करोमुख्य:
	dev_pm_करोमुख्य_detach(&client->dev, true);
err_clear_wakeup_irq:
	dev_pm_clear_wake_irq(&client->dev);
	device_init_wakeup(&client->dev, false);
put_sync_adapter:
	अगर (client->flags & I2C_CLIENT_HOST_NOTIFY)
		pm_runसमय_put_sync(&client->adapter->dev);

	वापस status;
पूर्ण

अटल पूर्णांक i2c_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा i2c_client	*client = to_i2c_client(dev);
	काष्ठा i2c_driver	*driver;

	driver = to_i2c_driver(dev->driver);
	अगर (driver->हटाओ) अणु
		पूर्णांक status;

		dev_dbg(dev, "remove\n");

		status = driver->हटाओ(client);
		अगर (status)
			dev_warn(dev, "remove failed (%pe), will be ignored\n", ERR_PTR(status));
	पूर्ण

	devres_release_group(&client->dev, client->devres_group_id);

	dev_pm_करोमुख्य_detach(&client->dev, true);

	dev_pm_clear_wake_irq(&client->dev);
	device_init_wakeup(&client->dev, false);

	client->irq = 0;
	अगर (client->flags & I2C_CLIENT_HOST_NOTIFY)
		pm_runसमय_put(&client->adapter->dev);

	/* वापस always 0 because there is WIP to make हटाओ-functions व्योम */
	वापस 0;
पूर्ण

अटल व्योम i2c_device_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = i2c_verअगरy_client(dev);
	काष्ठा i2c_driver *driver;

	अगर (!client || !dev->driver)
		वापस;
	driver = to_i2c_driver(dev->driver);
	अगर (driver->shutकरोwn)
		driver->shutकरोwn(client);
पूर्ण

अटल व्योम i2c_client_dev_release(काष्ठा device *dev)
अणु
	kमुक्त(to_i2c_client(dev));
पूर्ण

अटल sमाप_प्रकार
name_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", dev->type == &i2c_client_type ?
		       to_i2c_client(dev)->name : to_i2c_adapter(dev)->name);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल sमाप_प्रकार
modalias_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक len;

	len = of_device_modalias(dev, buf, PAGE_SIZE);
	अगर (len != -ENODEV)
		वापस len;

	len = acpi_device_modalias(dev, buf, PAGE_SIZE - 1);
	अगर (len != -ENODEV)
		वापस len;

	वापस प्र_लिखो(buf, "%s%s\n", I2C_MODULE_PREFIX, client->name);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल काष्ठा attribute *i2c_dev_attrs[] = अणु
	&dev_attr_name.attr,
	/* modalias helps coldplug:  modprobe $(cat .../modalias) */
	&dev_attr_modalias.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(i2c_dev);

काष्ठा bus_type i2c_bus_type = अणु
	.name		= "i2c",
	.match		= i2c_device_match,
	.probe		= i2c_device_probe,
	.हटाओ		= i2c_device_हटाओ,
	.shutकरोwn	= i2c_device_shutकरोwn,
पूर्ण;
EXPORT_SYMBOL_GPL(i2c_bus_type);

काष्ठा device_type i2c_client_type = अणु
	.groups		= i2c_dev_groups,
	.uevent		= i2c_device_uevent,
	.release	= i2c_client_dev_release,
पूर्ण;
EXPORT_SYMBOL_GPL(i2c_client_type);


/**
 * i2c_verअगरy_client - वापस parameter as i2c_client, or शून्य
 * @dev: device, probably from some driver model iterator
 *
 * When traversing the driver model tree, perhaps using driver model
 * iterators like @device_क्रम_each_child(), you can't assume very much
 * about the nodes you find.  Use this function to aव्योम oopses caused
 * by wrongly treating some non-I2C device as an i2c_client.
 */
काष्ठा i2c_client *i2c_verअगरy_client(काष्ठा device *dev)
अणु
	वापस (dev->type == &i2c_client_type)
			? to_i2c_client(dev)
			: शून्य;
पूर्ण
EXPORT_SYMBOL(i2c_verअगरy_client);


/* Return a unique address which takes the flags of the client पूर्णांकo account */
अटल अचिन्हित लघु i2c_encode_flags_to_addr(काष्ठा i2c_client *client)
अणु
	अचिन्हित लघु addr = client->addr;

	/* For some client flags, add an arbitrary offset to aव्योम collisions */
	अगर (client->flags & I2C_CLIENT_TEN)
		addr |= I2C_ADDR_OFFSET_TEN_BIT;

	अगर (client->flags & I2C_CLIENT_SLAVE)
		addr |= I2C_ADDR_OFFSET_SLAVE;

	वापस addr;
पूर्ण

/* This is a permissive address validity check, I2C address map स्थिरraपूर्णांकs
 * are purposely not enक्रमced, except क्रम the general call address. */
अटल पूर्णांक i2c_check_addr_validity(अचिन्हित पूर्णांक addr, अचिन्हित लघु flags)
अणु
	अगर (flags & I2C_CLIENT_TEN) अणु
		/* 10-bit address, all values are valid */
		अगर (addr > 0x3ff)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* 7-bit address, reject the general call address */
		अगर (addr == 0x00 || addr > 0x7f)
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* And this is a strict address validity check, used when probing. If a
 * device uses a reserved address, then it shouldn't be probed. 7-bit
 * addressing is assumed, 10-bit address devices are rare and should be
 * explicitly क्रमागतerated. */
पूर्णांक i2c_check_7bit_addr_validity_strict(अचिन्हित लघु addr)
अणु
	/*
	 * Reserved addresses per I2C specअगरication:
	 *  0x00       General call address / START byte
	 *  0x01       CBUS address
	 *  0x02       Reserved क्रम dअगरferent bus क्रमmat
	 *  0x03       Reserved क्रम future purposes
	 *  0x04-0x07  Hs-mode master code
	 *  0x78-0x7b  10-bit slave addressing
	 *  0x7c-0x7f  Reserved क्रम future purposes
	 */
	अगर (addr < 0x08 || addr > 0x77)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक __i2c_check_addr_busy(काष्ठा device *dev, व्योम *addrp)
अणु
	काष्ठा i2c_client	*client = i2c_verअगरy_client(dev);
	पूर्णांक			addr = *(पूर्णांक *)addrp;

	अगर (client && i2c_encode_flags_to_addr(client) == addr)
		वापस -EBUSY;
	वापस 0;
पूर्ण

/* walk up mux tree */
अटल पूर्णांक i2c_check_mux_parents(काष्ठा i2c_adapter *adapter, पूर्णांक addr)
अणु
	काष्ठा i2c_adapter *parent = i2c_parent_is_i2c_adapter(adapter);
	पूर्णांक result;

	result = device_क्रम_each_child(&adapter->dev, &addr,
					__i2c_check_addr_busy);

	अगर (!result && parent)
		result = i2c_check_mux_parents(parent, addr);

	वापस result;
पूर्ण

/* recurse करोwn mux tree */
अटल पूर्णांक i2c_check_mux_children(काष्ठा device *dev, व्योम *addrp)
अणु
	पूर्णांक result;

	अगर (dev->type == &i2c_adapter_type)
		result = device_क्रम_each_child(dev, addrp,
						i2c_check_mux_children);
	अन्यथा
		result = __i2c_check_addr_busy(dev, addrp);

	वापस result;
पूर्ण

अटल पूर्णांक i2c_check_addr_busy(काष्ठा i2c_adapter *adapter, पूर्णांक addr)
अणु
	काष्ठा i2c_adapter *parent = i2c_parent_is_i2c_adapter(adapter);
	पूर्णांक result = 0;

	अगर (parent)
		result = i2c_check_mux_parents(parent, addr);

	अगर (!result)
		result = device_क्रम_each_child(&adapter->dev, &addr,
						i2c_check_mux_children);

	वापस result;
पूर्ण

/**
 * i2c_adapter_lock_bus - Get exclusive access to an I2C bus segment
 * @adapter: Target I2C bus segment
 * @flags: I2C_LOCK_ROOT_ADAPTER locks the root i2c adapter, I2C_LOCK_SEGMENT
 *	locks only this branch in the adapter tree
 */
अटल व्योम i2c_adapter_lock_bus(काष्ठा i2c_adapter *adapter,
				 अचिन्हित पूर्णांक flags)
अणु
	rt_mutex_lock_nested(&adapter->bus_lock, i2c_adapter_depth(adapter));
पूर्ण

/**
 * i2c_adapter_trylock_bus - Try to get exclusive access to an I2C bus segment
 * @adapter: Target I2C bus segment
 * @flags: I2C_LOCK_ROOT_ADAPTER trylocks the root i2c adapter, I2C_LOCK_SEGMENT
 *	trylocks only this branch in the adapter tree
 */
अटल पूर्णांक i2c_adapter_trylock_bus(काष्ठा i2c_adapter *adapter,
				   अचिन्हित पूर्णांक flags)
अणु
	वापस rt_mutex_trylock(&adapter->bus_lock);
पूर्ण

/**
 * i2c_adapter_unlock_bus - Release exclusive access to an I2C bus segment
 * @adapter: Target I2C bus segment
 * @flags: I2C_LOCK_ROOT_ADAPTER unlocks the root i2c adapter, I2C_LOCK_SEGMENT
 *	unlocks only this branch in the adapter tree
 */
अटल व्योम i2c_adapter_unlock_bus(काष्ठा i2c_adapter *adapter,
				   अचिन्हित पूर्णांक flags)
अणु
	rt_mutex_unlock(&adapter->bus_lock);
पूर्ण

अटल व्योम i2c_dev_set_name(काष्ठा i2c_adapter *adap,
			     काष्ठा i2c_client *client,
			     काष्ठा i2c_board_info स्थिर *info)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(&client->dev);

	अगर (info && info->dev_name) अणु
		dev_set_name(&client->dev, "i2c-%s", info->dev_name);
		वापस;
	पूर्ण

	अगर (adev) अणु
		dev_set_name(&client->dev, "i2c-%s", acpi_dev_name(adev));
		वापस;
	पूर्ण

	dev_set_name(&client->dev, "%d-%04x", i2c_adapter_id(adap),
		     i2c_encode_flags_to_addr(client));
पूर्ण

पूर्णांक i2c_dev_irq_from_resources(स्थिर काष्ठा resource *resources,
			       अचिन्हित पूर्णांक num_resources)
अणु
	काष्ठा irq_data *irqd;
	पूर्णांक i;

	क्रम (i = 0; i < num_resources; i++) अणु
		स्थिर काष्ठा resource *r = &resources[i];

		अगर (resource_type(r) != IORESOURCE_IRQ)
			जारी;

		अगर (r->flags & IORESOURCE_BITS) अणु
			irqd = irq_get_irq_data(r->start);
			अगर (!irqd)
				अवरोध;

			irqd_set_trigger_type(irqd, r->flags & IORESOURCE_BITS);
		पूर्ण

		वापस r->start;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i2c_new_client_device - instantiate an i2c device
 * @adap: the adapter managing the device
 * @info: describes one I2C device; bus_num is ignored
 * Context: can sleep
 *
 * Create an i2c device. Binding is handled through driver model
 * probe()/हटाओ() methods.  A driver may be bound to this device when we
 * वापस from this function, or any later moment (e.g. maybe hotplugging will
 * load the driver module).  This call is not appropriate क्रम use by मुख्यboard
 * initialization logic, which usually runs during an arch_initcall() दीर्घ
 * beक्रमe any i2c_adapter could exist.
 *
 * This वापसs the new i2c client, which may be saved क्रम later use with
 * i2c_unरेजिस्टर_device(); or an ERR_PTR to describe the error.
 */
काष्ठा i2c_client *
i2c_new_client_device(काष्ठा i2c_adapter *adap, काष्ठा i2c_board_info स्थिर *info)
अणु
	काष्ठा i2c_client	*client;
	पूर्णांक			status;

	client = kzalloc(माप *client, GFP_KERNEL);
	अगर (!client)
		वापस ERR_PTR(-ENOMEM);

	client->adapter = adap;

	client->dev.platक्रमm_data = info->platक्रमm_data;
	client->flags = info->flags;
	client->addr = info->addr;

	client->init_irq = info->irq;
	अगर (!client->init_irq)
		client->init_irq = i2c_dev_irq_from_resources(info->resources,
							 info->num_resources);

	strlcpy(client->name, info->type, माप(client->name));

	status = i2c_check_addr_validity(client->addr, client->flags);
	अगर (status) अणु
		dev_err(&adap->dev, "Invalid %d-bit I2C address 0x%02hx\n",
			client->flags & I2C_CLIENT_TEN ? 10 : 7, client->addr);
		जाओ out_err_silent;
	पूर्ण

	/* Check क्रम address business */
	status = i2c_check_addr_busy(adap, i2c_encode_flags_to_addr(client));
	अगर (status)
		जाओ out_err;

	client->dev.parent = &client->adapter->dev;
	client->dev.bus = &i2c_bus_type;
	client->dev.type = &i2c_client_type;
	client->dev.of_node = of_node_get(info->of_node);
	client->dev.fwnode = info->fwnode;

	i2c_dev_set_name(adap, client, info);

	अगर (info->swnode) अणु
		status = device_add_software_node(&client->dev, info->swnode);
		अगर (status) अणु
			dev_err(&adap->dev,
				"Failed to add software node to client %s: %d\n",
				client->name, status);
			जाओ out_err_put_of_node;
		पूर्ण
	पूर्ण

	status = device_रेजिस्टर(&client->dev);
	अगर (status)
		जाओ out_हटाओ_swnode;

	dev_dbg(&adap->dev, "client [%s] registered with bus id %s\n",
		client->name, dev_name(&client->dev));

	वापस client;

out_हटाओ_swnode:
	device_हटाओ_software_node(&client->dev);
out_err_put_of_node:
	of_node_put(info->of_node);
out_err:
	dev_err(&adap->dev,
		"Failed to register i2c client %s at 0x%02x (%d)\n",
		client->name, client->addr, status);
out_err_silent:
	kमुक्त(client);
	वापस ERR_PTR(status);
पूर्ण
EXPORT_SYMBOL_GPL(i2c_new_client_device);

/**
 * i2c_unरेजिस्टर_device - reverse effect of i2c_new_*_device()
 * @client: value वापसed from i2c_new_*_device()
 * Context: can sleep
 */
व्योम i2c_unरेजिस्टर_device(काष्ठा i2c_client *client)
अणु
	अगर (IS_ERR_OR_शून्य(client))
		वापस;

	अगर (client->dev.of_node) अणु
		of_node_clear_flag(client->dev.of_node, OF_POPULATED);
		of_node_put(client->dev.of_node);
	पूर्ण

	अगर (ACPI_COMPANION(&client->dev))
		acpi_device_clear_क्रमागतerated(ACPI_COMPANION(&client->dev));
	device_हटाओ_software_node(&client->dev);
	device_unरेजिस्टर(&client->dev);
पूर्ण
EXPORT_SYMBOL_GPL(i2c_unरेजिस्टर_device);


अटल स्थिर काष्ठा i2c_device_id dummy_id[] = अणु
	अणु "dummy", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक dummy_probe(काष्ठा i2c_client *client,
		       स्थिर काष्ठा i2c_device_id *id)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक dummy_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver dummy_driver = अणु
	.driver.name	= "dummy",
	.probe		= dummy_probe,
	.हटाओ		= dummy_हटाओ,
	.id_table	= dummy_id,
पूर्ण;

/**
 * i2c_new_dummy_device - वापस a new i2c device bound to a dummy driver
 * @adapter: the adapter managing the device
 * @address: seven bit address to be used
 * Context: can sleep
 *
 * This वापसs an I2C client bound to the "dummy" driver, पूर्णांकended क्रम use
 * with devices that consume multiple addresses.  Examples of such chips
 * include various EEPROMS (like 24c04 and 24c08 models).
 *
 * These dummy devices have two मुख्य uses.  First, most I2C and SMBus calls
 * except i2c_transfer() need a client handle; the dummy will be that handle.
 * And second, this prevents the specअगरied address from being bound to a
 * dअगरferent driver.
 *
 * This वापसs the new i2c client, which should be saved क्रम later use with
 * i2c_unरेजिस्टर_device(); or an ERR_PTR to describe the error.
 */
काष्ठा i2c_client *i2c_new_dummy_device(काष्ठा i2c_adapter *adapter, u16 address)
अणु
	काष्ठा i2c_board_info info = अणु
		I2C_BOARD_INFO("dummy", address),
	पूर्ण;

	वापस i2c_new_client_device(adapter, &info);
पूर्ण
EXPORT_SYMBOL_GPL(i2c_new_dummy_device);

अटल व्योम devm_i2c_release_dummy(व्योम *client)
अणु
	i2c_unरेजिस्टर_device(client);
पूर्ण

/**
 * devm_i2c_new_dummy_device - वापस a new i2c device bound to a dummy driver
 * @dev: device the managed resource is bound to
 * @adapter: the adapter managing the device
 * @address: seven bit address to be used
 * Context: can sleep
 *
 * This is the device-managed version of @i2c_new_dummy_device. It वापसs the
 * new i2c client or an ERR_PTR in हाल of an error.
 */
काष्ठा i2c_client *devm_i2c_new_dummy_device(काष्ठा device *dev,
					     काष्ठा i2c_adapter *adapter,
					     u16 address)
अणु
	काष्ठा i2c_client *client;
	पूर्णांक ret;

	client = i2c_new_dummy_device(adapter, address);
	अगर (IS_ERR(client))
		वापस client;

	ret = devm_add_action_or_reset(dev, devm_i2c_release_dummy, client);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस client;
पूर्ण
EXPORT_SYMBOL_GPL(devm_i2c_new_dummy_device);

/**
 * i2c_new_ancillary_device - Helper to get the instantiated secondary address
 * and create the associated device
 * @client: Handle to the primary client
 * @name: Handle to specअगरy which secondary address to get
 * @शेष_addr: Used as a fallback अगर no secondary address was specअगरied
 * Context: can sleep
 *
 * I2C clients can be composed of multiple I2C slaves bound together in a single
 * component. The I2C client driver then binds to the master I2C slave and needs
 * to create I2C dummy clients to communicate with all the other slaves.
 *
 * This function creates and वापसs an I2C dummy client whose I2C address is
 * retrieved from the platक्रमm firmware based on the given slave name. If no
 * address is specअगरied by the firmware शेष_addr is used.
 *
 * On DT-based platक्रमms the address is retrieved from the "reg" property entry
 * cell whose "reg-names" value matches the slave name.
 *
 * This वापसs the new i2c client, which should be saved क्रम later use with
 * i2c_unरेजिस्टर_device(); or an ERR_PTR to describe the error.
 */
काष्ठा i2c_client *i2c_new_ancillary_device(काष्ठा i2c_client *client,
						स्थिर अक्षर *name,
						u16 शेष_addr)
अणु
	काष्ठा device_node *np = client->dev.of_node;
	u32 addr = शेष_addr;
	पूर्णांक i;

	अगर (np) अणु
		i = of_property_match_string(np, "reg-names", name);
		अगर (i >= 0)
			of_property_पढ़ो_u32_index(np, "reg", i, &addr);
	पूर्ण

	dev_dbg(&client->adapter->dev, "Address for %s : 0x%x\n", name, addr);
	वापस i2c_new_dummy_device(client->adapter, addr);
पूर्ण
EXPORT_SYMBOL_GPL(i2c_new_ancillary_device);

/* ------------------------------------------------------------------------- */

/* I2C bus adapters -- one roots each I2C or SMBUS segment */

अटल व्योम i2c_adapter_dev_release(काष्ठा device *dev)
अणु
	काष्ठा i2c_adapter *adap = to_i2c_adapter(dev);
	complete(&adap->dev_released);
पूर्ण

अचिन्हित पूर्णांक i2c_adapter_depth(काष्ठा i2c_adapter *adapter)
अणु
	अचिन्हित पूर्णांक depth = 0;

	जबतक ((adapter = i2c_parent_is_i2c_adapter(adapter)))
		depth++;

	WARN_ONCE(depth >= MAX_LOCKDEP_SUBCLASSES,
		  "adapter depth exceeds lockdep subclass limit\n");

	वापस depth;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_adapter_depth);

/*
 * Let users instantiate I2C devices through sysfs. This can be used when
 * platक्रमm initialization code करोesn't contain the proper data क्रम
 * whatever reason. Also useful क्रम drivers that करो device detection and
 * detection fails, either because the device uses an unexpected address,
 * or this is a compatible device with dअगरferent ID रेजिस्टर values.
 *
 * Parameter checking may look overzealous, but we really करोn't want
 * the user to provide incorrect parameters.
 */
अटल sमाप_प्रकार
new_device_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_adapter *adap = to_i2c_adapter(dev);
	काष्ठा i2c_board_info info;
	काष्ठा i2c_client *client;
	अक्षर *blank, end;
	पूर्णांक res;

	स_रखो(&info, 0, माप(काष्ठा i2c_board_info));

	blank = म_अक्षर(buf, ' ');
	अगर (!blank) अणु
		dev_err(dev, "%s: Missing parameters\n", "new_device");
		वापस -EINVAL;
	पूर्ण
	अगर (blank - buf > I2C_NAME_SIZE - 1) अणु
		dev_err(dev, "%s: Invalid device name\n", "new_device");
		वापस -EINVAL;
	पूर्ण
	स_नकल(info.type, buf, blank - buf);

	/* Parse reमुख्यing parameters, reject extra parameters */
	res = माला_पूछो(++blank, "%hi%c", &info.addr, &end);
	अगर (res < 1) अणु
		dev_err(dev, "%s: Can't parse I2C address\n", "new_device");
		वापस -EINVAL;
	पूर्ण
	अगर (res > 1  && end != '\n') अणु
		dev_err(dev, "%s: Extra parameters\n", "new_device");
		वापस -EINVAL;
	पूर्ण

	अगर ((info.addr & I2C_ADDR_OFFSET_TEN_BIT) == I2C_ADDR_OFFSET_TEN_BIT) अणु
		info.addr &= ~I2C_ADDR_OFFSET_TEN_BIT;
		info.flags |= I2C_CLIENT_TEN;
	पूर्ण

	अगर (info.addr & I2C_ADDR_OFFSET_SLAVE) अणु
		info.addr &= ~I2C_ADDR_OFFSET_SLAVE;
		info.flags |= I2C_CLIENT_SLAVE;
	पूर्ण

	client = i2c_new_client_device(adap, &info);
	अगर (IS_ERR(client))
		वापस PTR_ERR(client);

	/* Keep track of the added device */
	mutex_lock(&adap->userspace_clients_lock);
	list_add_tail(&client->detected, &adap->userspace_clients);
	mutex_unlock(&adap->userspace_clients_lock);
	dev_info(dev, "%s: Instantiated device %s at 0x%02hx\n", "new_device",
		 info.type, info.addr);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(new_device);

/*
 * And of course let the users delete the devices they instantiated, अगर
 * they got it wrong. This पूर्णांकerface can only be used to delete devices
 * instantiated by i2c_sysfs_new_device above. This guarantees that we
 * करोn't delete devices to which some kernel code still has references.
 *
 * Parameter checking may look overzealous, but we really करोn't want
 * the user to delete the wrong device.
 */
अटल sमाप_प्रकार
delete_device_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_adapter *adap = to_i2c_adapter(dev);
	काष्ठा i2c_client *client, *next;
	अचिन्हित लघु addr;
	अक्षर end;
	पूर्णांक res;

	/* Parse parameters, reject extra parameters */
	res = माला_पूछो(buf, "%hi%c", &addr, &end);
	अगर (res < 1) अणु
		dev_err(dev, "%s: Can't parse I2C address\n", "delete_device");
		वापस -EINVAL;
	पूर्ण
	अगर (res > 1  && end != '\n') अणु
		dev_err(dev, "%s: Extra parameters\n", "delete_device");
		वापस -EINVAL;
	पूर्ण

	/* Make sure the device was added through sysfs */
	res = -ENOENT;
	mutex_lock_nested(&adap->userspace_clients_lock,
			  i2c_adapter_depth(adap));
	list_क्रम_each_entry_safe(client, next, &adap->userspace_clients,
				 detected) अणु
		अगर (i2c_encode_flags_to_addr(client) == addr) अणु
			dev_info(dev, "%s: Deleting device %s at 0x%02hx\n",
				 "delete_device", client->name, client->addr);

			list_del(&client->detected);
			i2c_unरेजिस्टर_device(client);
			res = count;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&adap->userspace_clients_lock);

	अगर (res < 0)
		dev_err(dev, "%s: Can't find device in list\n",
			"delete_device");
	वापस res;
पूर्ण
अटल DEVICE_ATTR_IGNORE_LOCKDEP(delete_device, S_IWUSR, शून्य,
				  delete_device_store);

अटल काष्ठा attribute *i2c_adapter_attrs[] = अणु
	&dev_attr_name.attr,
	&dev_attr_new_device.attr,
	&dev_attr_delete_device.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(i2c_adapter);

काष्ठा device_type i2c_adapter_type = अणु
	.groups		= i2c_adapter_groups,
	.release	= i2c_adapter_dev_release,
पूर्ण;
EXPORT_SYMBOL_GPL(i2c_adapter_type);

/**
 * i2c_verअगरy_adapter - वापस parameter as i2c_adapter or शून्य
 * @dev: device, probably from some driver model iterator
 *
 * When traversing the driver model tree, perhaps using driver model
 * iterators like @device_क्रम_each_child(), you can't assume very much
 * about the nodes you find.  Use this function to aव्योम oopses caused
 * by wrongly treating some non-I2C device as an i2c_adapter.
 */
काष्ठा i2c_adapter *i2c_verअगरy_adapter(काष्ठा device *dev)
अणु
	वापस (dev->type == &i2c_adapter_type)
			? to_i2c_adapter(dev)
			: शून्य;
पूर्ण
EXPORT_SYMBOL(i2c_verअगरy_adapter);

#अगर_घोषित CONFIG_I2C_COMPAT
अटल काष्ठा class_compat *i2c_adapter_compat_class;
#पूर्ण_अगर

अटल व्योम i2c_scan_अटल_board_info(काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा i2c_devinfo	*devinfo;

	करोwn_पढ़ो(&__i2c_board_lock);
	list_क्रम_each_entry(devinfo, &__i2c_board_list, list) अणु
		अगर (devinfo->busnum == adapter->nr &&
		    IS_ERR(i2c_new_client_device(adapter, &devinfo->board_info)))
			dev_err(&adapter->dev,
				"Can't create device at 0x%02x\n",
				devinfo->board_info.addr);
	पूर्ण
	up_पढ़ो(&__i2c_board_lock);
पूर्ण

अटल पूर्णांक i2c_करो_add_adapter(काष्ठा i2c_driver *driver,
			      काष्ठा i2c_adapter *adap)
अणु
	/* Detect supported devices on that bus, and instantiate them */
	i2c_detect(adap, driver);

	वापस 0;
पूर्ण

अटल पूर्णांक __process_new_adapter(काष्ठा device_driver *d, व्योम *data)
अणु
	वापस i2c_करो_add_adapter(to_i2c_driver(d), data);
पूर्ण

अटल स्थिर काष्ठा i2c_lock_operations i2c_adapter_lock_ops = अणु
	.lock_bus =    i2c_adapter_lock_bus,
	.trylock_bus = i2c_adapter_trylock_bus,
	.unlock_bus =  i2c_adapter_unlock_bus,
पूर्ण;

अटल व्योम i2c_host_notअगरy_irq_tearकरोwn(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य = adap->host_notअगरy_करोमुख्य;
	irq_hw_number_t hwirq;

	अगर (!करोमुख्य)
		वापस;

	क्रम (hwirq = 0 ; hwirq < I2C_ADDR_7BITS_COUNT ; hwirq++)
		irq_dispose_mapping(irq_find_mapping(करोमुख्य, hwirq));

	irq_करोमुख्य_हटाओ(करोमुख्य);
	adap->host_notअगरy_करोमुख्य = शून्य;
पूर्ण

अटल पूर्णांक i2c_host_notअगरy_irq_map(काष्ठा irq_करोमुख्य *h,
					  अचिन्हित पूर्णांक virq,
					  irq_hw_number_t hw_irq_num)
अणु
	irq_set_chip_and_handler(virq, &dummy_irq_chip, handle_simple_irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops i2c_host_notअगरy_irq_ops = अणु
	.map = i2c_host_notअगरy_irq_map,
पूर्ण;

अटल पूर्णांक i2c_setup_host_notअगरy_irq_करोमुख्य(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;

	अगर (!i2c_check_functionality(adap, I2C_FUNC_SMBUS_HOST_NOTIFY))
		वापस 0;

	करोमुख्य = irq_करोमुख्य_create_linear(adap->dev.parent->fwnode,
					  I2C_ADDR_7BITS_COUNT,
					  &i2c_host_notअगरy_irq_ops, adap);
	अगर (!करोमुख्य)
		वापस -ENOMEM;

	adap->host_notअगरy_करोमुख्य = करोमुख्य;

	वापस 0;
पूर्ण

/**
 * i2c_handle_smbus_host_notअगरy - Forward a Host Notअगरy event to the correct
 * I2C client.
 * @adap: the adapter
 * @addr: the I2C address of the notअगरying device
 * Context: can't sleep
 *
 * Helper function to be called from an I2C bus driver's पूर्णांकerrupt
 * handler. It will schedule the Host Notअगरy IRQ.
 */
पूर्णांक i2c_handle_smbus_host_notअगरy(काष्ठा i2c_adapter *adap, अचिन्हित लघु addr)
अणु
	पूर्णांक irq;

	अगर (!adap)
		वापस -EINVAL;

	irq = irq_find_mapping(adap->host_notअगरy_करोमुख्य, addr);
	अगर (irq <= 0)
		वापस -ENXIO;

	generic_handle_irq(irq);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_handle_smbus_host_notअगरy);

अटल पूर्णांक i2c_रेजिस्टर_adapter(काष्ठा i2c_adapter *adap)
अणु
	पूर्णांक res = -EINVAL;

	/* Can't रेजिस्टर until after driver model init */
	अगर (WARN_ON(!is_रेजिस्टरed)) अणु
		res = -EAGAIN;
		जाओ out_list;
	पूर्ण

	/* Sanity checks */
	अगर (WARN(!adap->name[0], "i2c adapter has no name"))
		जाओ out_list;

	अगर (!adap->algo) अणु
		pr_err("adapter '%s': no algo supplied!\n", adap->name);
		जाओ out_list;
	पूर्ण

	अगर (!adap->lock_ops)
		adap->lock_ops = &i2c_adapter_lock_ops;

	adap->locked_flags = 0;
	rt_mutex_init(&adap->bus_lock);
	rt_mutex_init(&adap->mux_lock);
	mutex_init(&adap->userspace_clients_lock);
	INIT_LIST_HEAD(&adap->userspace_clients);

	/* Set शेष समयout to 1 second अगर not alपढ़ोy set */
	अगर (adap->समयout == 0)
		adap->समयout = HZ;

	/* रेजिस्टर soft irqs क्रम Host Notअगरy */
	res = i2c_setup_host_notअगरy_irq_करोमुख्य(adap);
	अगर (res) अणु
		pr_err("adapter '%s': can't create Host Notify IRQs (%d)\n",
		       adap->name, res);
		जाओ out_list;
	पूर्ण

	dev_set_name(&adap->dev, "i2c-%d", adap->nr);
	adap->dev.bus = &i2c_bus_type;
	adap->dev.type = &i2c_adapter_type;
	res = device_रेजिस्टर(&adap->dev);
	अगर (res) अणु
		pr_err("adapter '%s': can't register device (%d)\n", adap->name, res);
		जाओ out_list;
	पूर्ण

	res = of_i2c_setup_smbus_alert(adap);
	अगर (res)
		जाओ out_reg;

	pm_runसमय_no_callbacks(&adap->dev);
	pm_suspend_ignore_children(&adap->dev, true);
	pm_runसमय_enable(&adap->dev);

	res = i2c_init_recovery(adap);
	अगर (res == -EPROBE_DEFER)
		जाओ out_reg;

	dev_dbg(&adap->dev, "adapter [%s] registered\n", adap->name);

#अगर_घोषित CONFIG_I2C_COMPAT
	res = class_compat_create_link(i2c_adapter_compat_class, &adap->dev,
				       adap->dev.parent);
	अगर (res)
		dev_warn(&adap->dev,
			 "Failed to create compatibility class link\n");
#पूर्ण_अगर

	/* create pre-declared device nodes */
	of_i2c_रेजिस्टर_devices(adap);
	i2c_acpi_install_space_handler(adap);
	i2c_acpi_रेजिस्टर_devices(adap);

	अगर (adap->nr < __i2c_first_dynamic_bus_num)
		i2c_scan_अटल_board_info(adap);

	/* Notअगरy drivers */
	mutex_lock(&core_lock);
	bus_क्रम_each_drv(&i2c_bus_type, शून्य, adap, __process_new_adapter);
	mutex_unlock(&core_lock);

	वापस 0;

out_reg:
	init_completion(&adap->dev_released);
	device_unरेजिस्टर(&adap->dev);
	रुको_क्रम_completion(&adap->dev_released);
out_list:
	mutex_lock(&core_lock);
	idr_हटाओ(&i2c_adapter_idr, adap->nr);
	mutex_unlock(&core_lock);
	वापस res;
पूर्ण

/**
 * __i2c_add_numbered_adapter - i2c_add_numbered_adapter where nr is never -1
 * @adap: the adapter to रेजिस्टर (with adap->nr initialized)
 * Context: can sleep
 *
 * See i2c_add_numbered_adapter() क्रम details.
 */
अटल पूर्णांक __i2c_add_numbered_adapter(काष्ठा i2c_adapter *adap)
अणु
	पूर्णांक id;

	mutex_lock(&core_lock);
	id = idr_alloc(&i2c_adapter_idr, adap, adap->nr, adap->nr + 1, GFP_KERNEL);
	mutex_unlock(&core_lock);
	अगर (WARN(id < 0, "couldn't get idr"))
		वापस id == -ENOSPC ? -EBUSY : id;

	वापस i2c_रेजिस्टर_adapter(adap);
पूर्ण

/**
 * i2c_add_adapter - declare i2c adapter, use dynamic bus number
 * @adapter: the adapter to add
 * Context: can sleep
 *
 * This routine is used to declare an I2C adapter when its bus number
 * करोesn't matter or when its bus number is specअगरied by an dt alias.
 * Examples of bases when the bus number करोesn't matter: I2C adapters
 * dynamically added by USB links or PCI plugin cards.
 *
 * When this वापसs zero, a new bus number was allocated and stored
 * in adap->nr, and the specअगरied adapter became available क्रम clients.
 * Otherwise, a negative त्रुटि_सं value is वापसed.
 */
पूर्णांक i2c_add_adapter(काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->dev;
	पूर्णांक id;

	अगर (dev->of_node) अणु
		id = of_alias_get_id(dev->of_node, "i2c");
		अगर (id >= 0) अणु
			adapter->nr = id;
			वापस __i2c_add_numbered_adapter(adapter);
		पूर्ण
	पूर्ण

	mutex_lock(&core_lock);
	id = idr_alloc(&i2c_adapter_idr, adapter,
		       __i2c_first_dynamic_bus_num, 0, GFP_KERNEL);
	mutex_unlock(&core_lock);
	अगर (WARN(id < 0, "couldn't get idr"))
		वापस id;

	adapter->nr = id;

	वापस i2c_रेजिस्टर_adapter(adapter);
पूर्ण
EXPORT_SYMBOL(i2c_add_adapter);

/**
 * i2c_add_numbered_adapter - declare i2c adapter, use अटल bus number
 * @adap: the adapter to रेजिस्टर (with adap->nr initialized)
 * Context: can sleep
 *
 * This routine is used to declare an I2C adapter when its bus number
 * matters.  For example, use it क्रम I2C adapters from प्रणाली-on-chip CPUs,
 * or otherwise built in to the प्रणाली's मुख्यboard, and where i2c_board_info
 * is used to properly configure I2C devices.
 *
 * If the requested bus number is set to -1, then this function will behave
 * identically to i2c_add_adapter, and will dynamically assign a bus number.
 *
 * If no devices have pre-been declared क्रम this bus, then be sure to
 * रेजिस्टर the adapter beक्रमe any dynamically allocated ones.  Otherwise
 * the required bus ID may not be available.
 *
 * When this वापसs zero, the specअगरied adapter became available क्रम
 * clients using the bus number provided in adap->nr.  Also, the table
 * of I2C devices pre-declared using i2c_रेजिस्टर_board_info() is scanned,
 * and the appropriate driver model device nodes are created.  Otherwise, a
 * negative त्रुटि_सं value is वापसed.
 */
पूर्णांक i2c_add_numbered_adapter(काष्ठा i2c_adapter *adap)
अणु
	अगर (adap->nr == -1) /* -1 means dynamically assign bus id */
		वापस i2c_add_adapter(adap);

	वापस __i2c_add_numbered_adapter(adap);
पूर्ण
EXPORT_SYMBOL_GPL(i2c_add_numbered_adapter);

अटल व्योम i2c_करो_del_adapter(काष्ठा i2c_driver *driver,
			      काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा i2c_client *client, *_n;

	/* Remove the devices we created ourselves as the result of hardware
	 * probing (using a driver's detect method) */
	list_क्रम_each_entry_safe(client, _n, &driver->clients, detected) अणु
		अगर (client->adapter == adapter) अणु
			dev_dbg(&adapter->dev, "Removing %s at 0x%x\n",
				client->name, client->addr);
			list_del(&client->detected);
			i2c_unरेजिस्टर_device(client);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __unरेजिस्टर_client(काष्ठा device *dev, व्योम *dummy)
अणु
	काष्ठा i2c_client *client = i2c_verअगरy_client(dev);
	अगर (client && म_भेद(client->name, "dummy"))
		i2c_unरेजिस्टर_device(client);
	वापस 0;
पूर्ण

अटल पूर्णांक __unरेजिस्टर_dummy(काष्ठा device *dev, व्योम *dummy)
अणु
	काष्ठा i2c_client *client = i2c_verअगरy_client(dev);
	i2c_unरेजिस्टर_device(client);
	वापस 0;
पूर्ण

अटल पूर्णांक __process_हटाओd_adapter(काष्ठा device_driver *d, व्योम *data)
अणु
	i2c_करो_del_adapter(to_i2c_driver(d), data);
	वापस 0;
पूर्ण

/**
 * i2c_del_adapter - unरेजिस्टर I2C adapter
 * @adap: the adapter being unरेजिस्टरed
 * Context: can sleep
 *
 * This unरेजिस्टरs an I2C adapter which was previously रेजिस्टरed
 * by @i2c_add_adapter or @i2c_add_numbered_adapter.
 */
व्योम i2c_del_adapter(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा i2c_adapter *found;
	काष्ठा i2c_client *client, *next;

	/* First make sure that this adapter was ever added */
	mutex_lock(&core_lock);
	found = idr_find(&i2c_adapter_idr, adap->nr);
	mutex_unlock(&core_lock);
	अगर (found != adap) अणु
		pr_debug("attempting to delete unregistered adapter [%s]\n", adap->name);
		वापस;
	पूर्ण

	i2c_acpi_हटाओ_space_handler(adap);
	/* Tell drivers about this removal */
	mutex_lock(&core_lock);
	bus_क्रम_each_drv(&i2c_bus_type, शून्य, adap,
			       __process_हटाओd_adapter);
	mutex_unlock(&core_lock);

	/* Remove devices instantiated from sysfs */
	mutex_lock_nested(&adap->userspace_clients_lock,
			  i2c_adapter_depth(adap));
	list_क्रम_each_entry_safe(client, next, &adap->userspace_clients,
				 detected) अणु
		dev_dbg(&adap->dev, "Removing %s at 0x%x\n", client->name,
			client->addr);
		list_del(&client->detected);
		i2c_unरेजिस्टर_device(client);
	पूर्ण
	mutex_unlock(&adap->userspace_clients_lock);

	/* Detach any active clients. This can't fail, thus we करो not
	 * check the वापसed value. This is a two-pass process, because
	 * we can't हटाओ the dummy devices during the first pass: they
	 * could have been instantiated by real devices wishing to clean
	 * them up properly, so we give them a chance to करो that first. */
	device_क्रम_each_child(&adap->dev, शून्य, __unरेजिस्टर_client);
	device_क्रम_each_child(&adap->dev, शून्य, __unरेजिस्टर_dummy);

#अगर_घोषित CONFIG_I2C_COMPAT
	class_compat_हटाओ_link(i2c_adapter_compat_class, &adap->dev,
				 adap->dev.parent);
#पूर्ण_अगर

	/* device name is gone after device_unरेजिस्टर */
	dev_dbg(&adap->dev, "adapter [%s] unregistered\n", adap->name);

	pm_runसमय_disable(&adap->dev);

	i2c_host_notअगरy_irq_tearकरोwn(adap);

	/* रुको until all references to the device are gone
	 *
	 * FIXME: This is old code and should ideally be replaced by an
	 * alternative which results in decoupling the lअगरeसमय of the काष्ठा
	 * device from the i2c_adapter, like spi or netdev करो. Any solution
	 * should be thoroughly tested with DEBUG_KOBJECT_RELEASE enabled!
	 */
	init_completion(&adap->dev_released);
	device_unरेजिस्टर(&adap->dev);
	रुको_क्रम_completion(&adap->dev_released);

	/* मुक्त bus id */
	mutex_lock(&core_lock);
	idr_हटाओ(&i2c_adapter_idr, adap->nr);
	mutex_unlock(&core_lock);

	/* Clear the device काष्ठाure in हाल this adapter is ever going to be
	   added again */
	स_रखो(&adap->dev, 0, माप(adap->dev));
पूर्ण
EXPORT_SYMBOL(i2c_del_adapter);

अटल व्योम devm_i2c_del_adapter(व्योम *adapter)
अणु
	i2c_del_adapter(adapter);
पूर्ण

/**
 * devm_i2c_add_adapter - device-managed variant of i2c_add_adapter()
 * @dev: managing device क्रम adding this I2C adapter
 * @adapter: the adapter to add
 * Context: can sleep
 *
 * Add adapter with dynamic bus number, same with i2c_add_adapter()
 * but the adapter will be स्वतः deleted on driver detach.
 */
पूर्णांक devm_i2c_add_adapter(काष्ठा device *dev, काष्ठा i2c_adapter *adapter)
अणु
	पूर्णांक ret;

	ret = i2c_add_adapter(adapter);
	अगर (ret)
		वापस ret;

	वापस devm_add_action_or_reset(dev, devm_i2c_del_adapter, adapter);
पूर्ण
EXPORT_SYMBOL_GPL(devm_i2c_add_adapter);

अटल व्योम i2c_parse_timing(काष्ठा device *dev, अक्षर *prop_name, u32 *cur_val_p,
			    u32 def_val, bool use_def)
अणु
	पूर्णांक ret;

	ret = device_property_पढ़ो_u32(dev, prop_name, cur_val_p);
	अगर (ret && use_def)
		*cur_val_p = def_val;

	dev_dbg(dev, "%s: %u\n", prop_name, *cur_val_p);
पूर्ण

/**
 * i2c_parse_fw_timings - get I2C related timing parameters from firmware
 * @dev: The device to scan क्रम I2C timing properties
 * @t: the i2c_timings काष्ठा to be filled with values
 * @use_शेषs: bool to use sane शेषs derived from the I2C specअगरication
 *		  when properties are not found, otherwise करोn't update
 *
 * Scan the device क्रम the generic I2C properties describing timing parameters
 * क्रम the संकेत and fill the given काष्ठा with the results. If a property was
 * not found and use_शेषs was true, then maximum timings are assumed which
 * are derived from the I2C specअगरication. If use_शेषs is not used, the
 * results will be as beक्रमe, so drivers can apply their own शेषs beक्रमe
 * calling this helper. The latter is मुख्यly पूर्णांकended क्रम aव्योमing regressions
 * of existing drivers which want to चयन to this function. New drivers
 * almost always should use the शेषs.
 */
व्योम i2c_parse_fw_timings(काष्ठा device *dev, काष्ठा i2c_timings *t, bool use_शेषs)
अणु
	bool u = use_शेषs;
	u32 d;

	i2c_parse_timing(dev, "clock-frequency", &t->bus_freq_hz,
			 I2C_MAX_STANDARD_MODE_FREQ, u);

	d = t->bus_freq_hz <= I2C_MAX_STANDARD_MODE_FREQ ? 1000 :
	    t->bus_freq_hz <= I2C_MAX_FAST_MODE_FREQ ? 300 : 120;
	i2c_parse_timing(dev, "i2c-scl-rising-time-ns", &t->scl_rise_ns, d, u);

	d = t->bus_freq_hz <= I2C_MAX_FAST_MODE_FREQ ? 300 : 120;
	i2c_parse_timing(dev, "i2c-scl-falling-time-ns", &t->scl_fall_ns, d, u);

	i2c_parse_timing(dev, "i2c-scl-internal-delay-ns",
			 &t->scl_पूर्णांक_delay_ns, 0, u);
	i2c_parse_timing(dev, "i2c-sda-falling-time-ns", &t->sda_fall_ns,
			 t->scl_fall_ns, u);
	i2c_parse_timing(dev, "i2c-sda-hold-time-ns", &t->sda_hold_ns, 0, u);
	i2c_parse_timing(dev, "i2c-digital-filter-width-ns",
			 &t->digital_filter_width_ns, 0, u);
	i2c_parse_timing(dev, "i2c-analog-filter-cutoff-frequency",
			 &t->analog_filter_cutoff_freq_hz, 0, u);
पूर्ण
EXPORT_SYMBOL_GPL(i2c_parse_fw_timings);

/* ------------------------------------------------------------------------- */

पूर्णांक i2c_क्रम_each_dev(व्योम *data, पूर्णांक (*fn)(काष्ठा device *dev, व्योम *data))
अणु
	पूर्णांक res;

	mutex_lock(&core_lock);
	res = bus_क्रम_each_dev(&i2c_bus_type, शून्य, data, fn);
	mutex_unlock(&core_lock);

	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_क्रम_each_dev);

अटल पूर्णांक __process_new_driver(काष्ठा device *dev, व्योम *data)
अणु
	अगर (dev->type != &i2c_adapter_type)
		वापस 0;
	वापस i2c_करो_add_adapter(data, to_i2c_adapter(dev));
पूर्ण

/*
 * An i2c_driver is used with one or more i2c_client (device) nodes to access
 * i2c slave chips, on a bus instance associated with some i2c_adapter.
 */

पूर्णांक i2c_रेजिस्टर_driver(काष्ठा module *owner, काष्ठा i2c_driver *driver)
अणु
	पूर्णांक res;

	/* Can't रेजिस्टर until after driver model init */
	अगर (WARN_ON(!is_रेजिस्टरed))
		वापस -EAGAIN;

	/* add the driver to the list of i2c drivers in the driver core */
	driver->driver.owner = owner;
	driver->driver.bus = &i2c_bus_type;
	INIT_LIST_HEAD(&driver->clients);

	/* When registration वापसs, the driver core
	 * will have called probe() क्रम all matching-but-unbound devices.
	 */
	res = driver_रेजिस्टर(&driver->driver);
	अगर (res)
		वापस res;

	pr_debug("driver [%s] registered\n", driver->driver.name);

	/* Walk the adapters that are alपढ़ोy present */
	i2c_क्रम_each_dev(driver, __process_new_driver);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(i2c_रेजिस्टर_driver);

अटल पूर्णांक __process_हटाओd_driver(काष्ठा device *dev, व्योम *data)
अणु
	अगर (dev->type == &i2c_adapter_type)
		i2c_करो_del_adapter(data, to_i2c_adapter(dev));
	वापस 0;
पूर्ण

/**
 * i2c_del_driver - unरेजिस्टर I2C driver
 * @driver: the driver being unरेजिस्टरed
 * Context: can sleep
 */
व्योम i2c_del_driver(काष्ठा i2c_driver *driver)
अणु
	i2c_क्रम_each_dev(driver, __process_हटाओd_driver);

	driver_unरेजिस्टर(&driver->driver);
	pr_debug("driver [%s] unregistered\n", driver->driver.name);
पूर्ण
EXPORT_SYMBOL(i2c_del_driver);

/* ------------------------------------------------------------------------- */

काष्ठा i2c_cmd_arg अणु
	अचिन्हित	cmd;
	व्योम		*arg;
पूर्ण;

अटल पूर्णांक i2c_cmd(काष्ठा device *dev, व्योम *_arg)
अणु
	काष्ठा i2c_client	*client = i2c_verअगरy_client(dev);
	काष्ठा i2c_cmd_arg	*arg = _arg;
	काष्ठा i2c_driver	*driver;

	अगर (!client || !client->dev.driver)
		वापस 0;

	driver = to_i2c_driver(client->dev.driver);
	अगर (driver->command)
		driver->command(client, arg->cmd, arg->arg);
	वापस 0;
पूर्ण

व्योम i2c_clients_command(काष्ठा i2c_adapter *adap, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा i2c_cmd_arg	cmd_arg;

	cmd_arg.cmd = cmd;
	cmd_arg.arg = arg;
	device_क्रम_each_child(&adap->dev, &cmd_arg, i2c_cmd);
पूर्ण
EXPORT_SYMBOL(i2c_clients_command);

अटल पूर्णांक __init i2c_init(व्योम)
अणु
	पूर्णांक retval;

	retval = of_alias_get_highest_id("i2c");

	करोwn_ग_लिखो(&__i2c_board_lock);
	अगर (retval >= __i2c_first_dynamic_bus_num)
		__i2c_first_dynamic_bus_num = retval + 1;
	up_ग_लिखो(&__i2c_board_lock);

	retval = bus_रेजिस्टर(&i2c_bus_type);
	अगर (retval)
		वापस retval;

	is_रेजिस्टरed = true;

#अगर_घोषित CONFIG_I2C_COMPAT
	i2c_adapter_compat_class = class_compat_रेजिस्टर("i2c-adapter");
	अगर (!i2c_adapter_compat_class) अणु
		retval = -ENOMEM;
		जाओ bus_err;
	पूर्ण
#पूर्ण_अगर
	retval = i2c_add_driver(&dummy_driver);
	अगर (retval)
		जाओ class_err;

	अगर (IS_ENABLED(CONFIG_OF_DYNAMIC))
		WARN_ON(of_reconfig_notअगरier_रेजिस्टर(&i2c_of_notअगरier));
	अगर (IS_ENABLED(CONFIG_ACPI))
		WARN_ON(acpi_reconfig_notअगरier_रेजिस्टर(&i2c_acpi_notअगरier));

	वापस 0;

class_err:
#अगर_घोषित CONFIG_I2C_COMPAT
	class_compat_unरेजिस्टर(i2c_adapter_compat_class);
bus_err:
#पूर्ण_अगर
	is_रेजिस्टरed = false;
	bus_unरेजिस्टर(&i2c_bus_type);
	वापस retval;
पूर्ण

अटल व्योम __निकास i2c_निकास(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_ACPI))
		WARN_ON(acpi_reconfig_notअगरier_unरेजिस्टर(&i2c_acpi_notअगरier));
	अगर (IS_ENABLED(CONFIG_OF_DYNAMIC))
		WARN_ON(of_reconfig_notअगरier_unरेजिस्टर(&i2c_of_notअगरier));
	i2c_del_driver(&dummy_driver);
#अगर_घोषित CONFIG_I2C_COMPAT
	class_compat_unरेजिस्टर(i2c_adapter_compat_class);
#पूर्ण_अगर
	bus_unरेजिस्टर(&i2c_bus_type);
	tracepoपूर्णांक_synchronize_unरेजिस्टर();
पूर्ण

/* We must initialize early, because some subप्रणालीs रेजिस्टर i2c drivers
 * in subsys_initcall() code, but are linked (and initialized) beक्रमe i2c.
 */
postcore_initcall(i2c_init);
module_निकास(i2c_निकास);

/* ----------------------------------------------------
 * the functional पूर्णांकerface to the i2c busses.
 * ----------------------------------------------------
 */

/* Check अगर val is exceeding the quirk IFF quirk is non 0 */
#घोषणा i2c_quirk_exceeded(val, quirk) ((quirk) && ((val) > (quirk)))

अटल पूर्णांक i2c_quirk_error(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msg, अक्षर *err_msg)
अणु
	dev_err_ratelimited(&adap->dev, "adapter quirk: %s (addr 0x%04x, size %u, %s)\n",
			    err_msg, msg->addr, msg->len,
			    msg->flags & I2C_M_RD ? "read" : "write");
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक i2c_check_क्रम_quirks(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	स्थिर काष्ठा i2c_adapter_quirks *q = adap->quirks;
	पूर्णांक max_num = q->max_num_msgs, i;
	bool करो_len_check = true;

	अगर (q->flags & I2C_AQ_COMB) अणु
		max_num = 2;

		/* special checks क्रम combined messages */
		अगर (num == 2) अणु
			अगर (q->flags & I2C_AQ_COMB_WRITE_FIRST && msgs[0].flags & I2C_M_RD)
				वापस i2c_quirk_error(adap, &msgs[0], "1st comb msg must be write");

			अगर (q->flags & I2C_AQ_COMB_READ_SECOND && !(msgs[1].flags & I2C_M_RD))
				वापस i2c_quirk_error(adap, &msgs[1], "2nd comb msg must be read");

			अगर (q->flags & I2C_AQ_COMB_SAME_ADDR && msgs[0].addr != msgs[1].addr)
				वापस i2c_quirk_error(adap, &msgs[0], "comb msg only to same addr");

			अगर (i2c_quirk_exceeded(msgs[0].len, q->max_comb_1st_msg_len))
				वापस i2c_quirk_error(adap, &msgs[0], "msg too long");

			अगर (i2c_quirk_exceeded(msgs[1].len, q->max_comb_2nd_msg_len))
				वापस i2c_quirk_error(adap, &msgs[1], "msg too long");

			करो_len_check = false;
		पूर्ण
	पूर्ण

	अगर (i2c_quirk_exceeded(num, max_num))
		वापस i2c_quirk_error(adap, &msgs[0], "too many messages");

	क्रम (i = 0; i < num; i++) अणु
		u16 len = msgs[i].len;

		अगर (msgs[i].flags & I2C_M_RD) अणु
			अगर (करो_len_check && i2c_quirk_exceeded(len, q->max_पढ़ो_len))
				वापस i2c_quirk_error(adap, &msgs[i], "msg too long");

			अगर (q->flags & I2C_AQ_NO_ZERO_LEN_READ && len == 0)
				वापस i2c_quirk_error(adap, &msgs[i], "no zero length");
		पूर्ण अन्यथा अणु
			अगर (करो_len_check && i2c_quirk_exceeded(len, q->max_ग_लिखो_len))
				वापस i2c_quirk_error(adap, &msgs[i], "msg too long");

			अगर (q->flags & I2C_AQ_NO_ZERO_LEN_WRITE && len == 0)
				वापस i2c_quirk_error(adap, &msgs[i], "no zero length");
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * __i2c_transfer - unlocked flavor of i2c_transfer
 * @adap: Handle to I2C bus
 * @msgs: One or more messages to execute beक्रमe STOP is issued to
 *	terminate the operation; each message begins with a START.
 * @num: Number of messages to be executed.
 *
 * Returns negative त्रुटि_सं, अन्यथा the number of messages executed.
 *
 * Adapter lock must be held when calling this function. No debug logging
 * takes place. adap->algo->master_xfer existence isn't checked.
 */
पूर्णांक __i2c_transfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	अचिन्हित दीर्घ orig_jअगरfies;
	पूर्णांक ret, try;

	अगर (WARN_ON(!msgs || num < 1))
		वापस -EINVAL;

	ret = __i2c_check_suspended(adap);
	अगर (ret)
		वापस ret;

	अगर (adap->quirks && i2c_check_क्रम_quirks(adap, msgs, num))
		वापस -EOPNOTSUPP;

	/*
	 * i2c_trace_msg_key माला_लो enabled when tracepoपूर्णांक i2c_transfer माला_लो
	 * enabled.  This is an efficient way of keeping the क्रम-loop from
	 * being executed when not needed.
	 */
	अगर (अटल_branch_unlikely(&i2c_trace_msg_key)) अणु
		पूर्णांक i;
		क्रम (i = 0; i < num; i++)
			अगर (msgs[i].flags & I2C_M_RD)
				trace_i2c_पढ़ो(adap, &msgs[i], i);
			अन्यथा
				trace_i2c_ग_लिखो(adap, &msgs[i], i);
	पूर्ण

	/* Retry स्वतःmatically on arbitration loss */
	orig_jअगरfies = jअगरfies;
	क्रम (ret = 0, try = 0; try <= adap->retries; try++) अणु
		अगर (i2c_in_atomic_xfer_mode() && adap->algo->master_xfer_atomic)
			ret = adap->algo->master_xfer_atomic(adap, msgs, num);
		अन्यथा
			ret = adap->algo->master_xfer(adap, msgs, num);

		अगर (ret != -EAGAIN)
			अवरोध;
		अगर (समय_after(jअगरfies, orig_jअगरfies + adap->समयout))
			अवरोध;
	पूर्ण

	अगर (अटल_branch_unlikely(&i2c_trace_msg_key)) अणु
		पूर्णांक i;
		क्रम (i = 0; i < ret; i++)
			अगर (msgs[i].flags & I2C_M_RD)
				trace_i2c_reply(adap, &msgs[i], i);
		trace_i2c_result(adap, num, ret);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(__i2c_transfer);

/**
 * i2c_transfer - execute a single or combined I2C message
 * @adap: Handle to I2C bus
 * @msgs: One or more messages to execute beक्रमe STOP is issued to
 *	terminate the operation; each message begins with a START.
 * @num: Number of messages to be executed.
 *
 * Returns negative त्रुटि_सं, अन्यथा the number of messages executed.
 *
 * Note that there is no requirement that each message be sent to
 * the same slave address, although that is the most common model.
 */
पूर्णांक i2c_transfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	पूर्णांक ret;

	अगर (!adap->algo->master_xfer) अणु
		dev_dbg(&adap->dev, "I2C level transfers not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* REVISIT the fault reporting model here is weak:
	 *
	 *  - When we get an error after receiving N bytes from a slave,
	 *    there is no way to report "N".
	 *
	 *  - When we get a NAK after transmitting N bytes to a slave,
	 *    there is no way to report "N" ... or to let the master
	 *    जारी executing the rest of this combined message, अगर
	 *    that's the appropriate response.
	 *
	 *  - When क्रम example "num" is two and we successfully complete
	 *    the first message but get an error part way through the
	 *    second, it's unclear whether that should be reported as
	 *    one (discarding status on the second message) or त्रुटि_सं
	 *    (discarding status on the first one).
	 */
	ret = __i2c_lock_bus_helper(adap);
	अगर (ret)
		वापस ret;

	ret = __i2c_transfer(adap, msgs, num);
	i2c_unlock_bus(adap, I2C_LOCK_SEGMENT);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(i2c_transfer);

/**
 * i2c_transfer_buffer_flags - issue a single I2C message transferring data
 *			       to/from a buffer
 * @client: Handle to slave device
 * @buf: Where the data is stored
 * @count: How many bytes to transfer, must be less than 64k since msg.len is u16
 * @flags: The flags to be used क्रम the message, e.g. I2C_M_RD क्रम पढ़ोs
 *
 * Returns negative त्रुटि_सं, or अन्यथा the number of bytes transferred.
 */
पूर्णांक i2c_transfer_buffer_flags(स्थिर काष्ठा i2c_client *client, अक्षर *buf,
			      पूर्णांक count, u16 flags)
अणु
	पूर्णांक ret;
	काष्ठा i2c_msg msg = अणु
		.addr = client->addr,
		.flags = flags | (client->flags & I2C_M_TEN),
		.len = count,
		.buf = buf,
	पूर्ण;

	ret = i2c_transfer(client->adapter, &msg, 1);

	/*
	 * If everything went ok (i.e. 1 msg transferred), वापस #bytes
	 * transferred, अन्यथा error code.
	 */
	वापस (ret == 1) ? count : ret;
पूर्ण
EXPORT_SYMBOL(i2c_transfer_buffer_flags);

/**
 * i2c_get_device_id - get manufacturer, part id and die revision of a device
 * @client: The device to query
 * @id: The queried inक्रमmation
 *
 * Returns negative त्रुटि_सं on error, zero on success.
 */
पूर्णांक i2c_get_device_id(स्थिर काष्ठा i2c_client *client,
		      काष्ठा i2c_device_identity *id)
अणु
	काष्ठा i2c_adapter *adap = client->adapter;
	जोड़ i2c_smbus_data raw_id;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(adap, I2C_FUNC_SMBUS_READ_I2C_BLOCK))
		वापस -EOPNOTSUPP;

	raw_id.block[0] = 3;
	ret = i2c_smbus_xfer(adap, I2C_ADDR_DEVICE_ID, 0,
			     I2C_SMBUS_READ, client->addr << 1,
			     I2C_SMBUS_I2C_BLOCK_DATA, &raw_id);
	अगर (ret)
		वापस ret;

	id->manufacturer_id = (raw_id.block[1] << 4) | (raw_id.block[2] >> 4);
	id->part_id = ((raw_id.block[2] & 0xf) << 5) | (raw_id.block[3] >> 3);
	id->die_revision = raw_id.block[3] & 0x7;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_get_device_id);

/* ----------------------------------------------------
 * the i2c address scanning function
 * Will not work क्रम 10-bit addresses!
 * ----------------------------------------------------
 */

/*
 * Legacy शेष probe function, mostly relevant क्रम SMBus. The शेष
 * probe method is a quick ग_लिखो, but it is known to corrupt the 24RF08
 * EEPROMs due to a state machine bug, and could also irreversibly
 * ग_लिखो-protect some EEPROMs, so क्रम address ranges 0x30-0x37 and 0x50-0x5f,
 * we use a लघु byte पढ़ो instead. Also, some bus drivers करोn't implement
 * quick ग_लिखो, so we fallback to a byte पढ़ो in that हाल too.
 * On x86, there is another special हाल क्रम FSC hardware monitoring chips,
 * which want regular byte पढ़ोs (address 0x73.) Fortunately, these are the
 * only known chips using this I2C address on PC hardware.
 * Returns 1 अगर probe succeeded, 0 अगर not.
 */
अटल पूर्णांक i2c_शेष_probe(काष्ठा i2c_adapter *adap, अचिन्हित लघु addr)
अणु
	पूर्णांक err;
	जोड़ i2c_smbus_data dummy;

#अगर_घोषित CONFIG_X86
	अगर (addr == 0x73 && (adap->class & I2C_CLASS_HWMON)
	 && i2c_check_functionality(adap, I2C_FUNC_SMBUS_READ_BYTE_DATA))
		err = i2c_smbus_xfer(adap, addr, 0, I2C_SMBUS_READ, 0,
				     I2C_SMBUS_BYTE_DATA, &dummy);
	अन्यथा
#पूर्ण_अगर
	अगर (!((addr & ~0x07) == 0x30 || (addr & ~0x0f) == 0x50)
	 && i2c_check_functionality(adap, I2C_FUNC_SMBUS_QUICK))
		err = i2c_smbus_xfer(adap, addr, 0, I2C_SMBUS_WRITE, 0,
				     I2C_SMBUS_QUICK, शून्य);
	अन्यथा अगर (i2c_check_functionality(adap, I2C_FUNC_SMBUS_READ_BYTE))
		err = i2c_smbus_xfer(adap, addr, 0, I2C_SMBUS_READ, 0,
				     I2C_SMBUS_BYTE, &dummy);
	अन्यथा अणु
		dev_warn(&adap->dev, "No suitable probing method supported for address 0x%02X\n",
			 addr);
		err = -EOPNOTSUPP;
	पूर्ण

	वापस err >= 0;
पूर्ण

अटल पूर्णांक i2c_detect_address(काष्ठा i2c_client *temp_client,
			      काष्ठा i2c_driver *driver)
अणु
	काष्ठा i2c_board_info info;
	काष्ठा i2c_adapter *adapter = temp_client->adapter;
	पूर्णांक addr = temp_client->addr;
	पूर्णांक err;

	/* Make sure the address is valid */
	err = i2c_check_7bit_addr_validity_strict(addr);
	अगर (err) अणु
		dev_warn(&adapter->dev, "Invalid probe address 0x%02x\n",
			 addr);
		वापस err;
	पूर्ण

	/* Skip अगर alपढ़ोy in use (7 bit, no need to encode flags) */
	अगर (i2c_check_addr_busy(adapter, addr))
		वापस 0;

	/* Make sure there is something at this address */
	अगर (!i2c_शेष_probe(adapter, addr))
		वापस 0;

	/* Finally call the custom detection function */
	स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
	info.addr = addr;
	err = driver->detect(temp_client, &info);
	अगर (err) अणु
		/* -ENODEV is वापसed अगर the detection fails. We catch it
		   here as this isn't an error. */
		वापस err == -ENODEV ? 0 : err;
	पूर्ण

	/* Consistency check */
	अगर (info.type[0] == '\0') अणु
		dev_err(&adapter->dev,
			"%s detection function provided no name for 0x%x\n",
			driver->driver.name, addr);
	पूर्ण अन्यथा अणु
		काष्ठा i2c_client *client;

		/* Detection succeeded, instantiate the device */
		अगर (adapter->class & I2C_CLASS_DEPRECATED)
			dev_warn(&adapter->dev,
				"This adapter will soon drop class based instantiation of devices. "
				"Please make sure client 0x%02x gets instantiated by other means. "
				"Check 'Documentation/i2c/instantiating-devices.rst' for details.\n",
				info.addr);

		dev_dbg(&adapter->dev, "Creating %s at 0x%02x\n",
			info.type, info.addr);
		client = i2c_new_client_device(adapter, &info);
		अगर (!IS_ERR(client))
			list_add_tail(&client->detected, &driver->clients);
		अन्यथा
			dev_err(&adapter->dev, "Failed creating %s at 0x%02x\n",
				info.type, info.addr);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक i2c_detect(काष्ठा i2c_adapter *adapter, काष्ठा i2c_driver *driver)
अणु
	स्थिर अचिन्हित लघु *address_list;
	काष्ठा i2c_client *temp_client;
	पूर्णांक i, err = 0;

	address_list = driver->address_list;
	अगर (!driver->detect || !address_list)
		वापस 0;

	/* Warn that the adapter lost class based instantiation */
	अगर (adapter->class == I2C_CLASS_DEPRECATED) अणु
		dev_dbg(&adapter->dev,
			"This adapter dropped support for I2C classes and won't auto-detect %s devices anymore. "
			"If you need it, check 'Documentation/i2c/instantiating-devices.rst' for alternatives.\n",
			driver->driver.name);
		वापस 0;
	पूर्ण

	/* Stop here अगर the classes करो not match */
	अगर (!(adapter->class & driver->class))
		वापस 0;

	/* Set up a temporary client to help detect callback */
	temp_client = kzalloc(माप(काष्ठा i2c_client), GFP_KERNEL);
	अगर (!temp_client)
		वापस -ENOMEM;
	temp_client->adapter = adapter;

	क्रम (i = 0; address_list[i] != I2C_CLIENT_END; i += 1) अणु
		dev_dbg(&adapter->dev,
			"found normal entry for adapter %d, addr 0x%02x\n",
			i2c_adapter_id(adapter), address_list[i]);
		temp_client->addr = address_list[i];
		err = i2c_detect_address(temp_client, driver);
		अगर (unlikely(err))
			अवरोध;
	पूर्ण

	kमुक्त(temp_client);
	वापस err;
पूर्ण

पूर्णांक i2c_probe_func_quick_पढ़ो(काष्ठा i2c_adapter *adap, अचिन्हित लघु addr)
अणु
	वापस i2c_smbus_xfer(adap, addr, 0, I2C_SMBUS_READ, 0,
			      I2C_SMBUS_QUICK, शून्य) >= 0;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_probe_func_quick_पढ़ो);

काष्ठा i2c_client *
i2c_new_scanned_device(काष्ठा i2c_adapter *adap,
		       काष्ठा i2c_board_info *info,
		       अचिन्हित लघु स्थिर *addr_list,
		       पूर्णांक (*probe)(काष्ठा i2c_adapter *adap, अचिन्हित लघु addr))
अणु
	पूर्णांक i;

	अगर (!probe)
		probe = i2c_शेष_probe;

	क्रम (i = 0; addr_list[i] != I2C_CLIENT_END; i++) अणु
		/* Check address validity */
		अगर (i2c_check_7bit_addr_validity_strict(addr_list[i]) < 0) अणु
			dev_warn(&adap->dev, "Invalid 7-bit address 0x%02x\n",
				 addr_list[i]);
			जारी;
		पूर्ण

		/* Check address availability (7 bit, no need to encode flags) */
		अगर (i2c_check_addr_busy(adap, addr_list[i])) अणु
			dev_dbg(&adap->dev,
				"Address 0x%02x already in use, not probing\n",
				addr_list[i]);
			जारी;
		पूर्ण

		/* Test address responsiveness */
		अगर (probe(adap, addr_list[i]))
			अवरोध;
	पूर्ण

	अगर (addr_list[i] == I2C_CLIENT_END) अणु
		dev_dbg(&adap->dev, "Probing failed, no device found\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	info->addr = addr_list[i];
	वापस i2c_new_client_device(adap, info);
पूर्ण
EXPORT_SYMBOL_GPL(i2c_new_scanned_device);

काष्ठा i2c_adapter *i2c_get_adapter(पूर्णांक nr)
अणु
	काष्ठा i2c_adapter *adapter;

	mutex_lock(&core_lock);
	adapter = idr_find(&i2c_adapter_idr, nr);
	अगर (!adapter)
		जाओ निकास;

	अगर (try_module_get(adapter->owner))
		get_device(&adapter->dev);
	अन्यथा
		adapter = शून्य;

 निकास:
	mutex_unlock(&core_lock);
	वापस adapter;
पूर्ण
EXPORT_SYMBOL(i2c_get_adapter);

व्योम i2c_put_adapter(काष्ठा i2c_adapter *adap)
अणु
	अगर (!adap)
		वापस;

	put_device(&adap->dev);
	module_put(adap->owner);
पूर्ण
EXPORT_SYMBOL(i2c_put_adapter);

/**
 * i2c_get_dma_safe_msg_buf() - get a DMA safe buffer क्रम the given i2c_msg
 * @msg: the message to be checked
 * @threshold: the minimum number of bytes क्रम which using DMA makes sense.
 *	       Should at least be 1.
 *
 * Return: शून्य अगर a DMA safe buffer was not obtained. Use msg->buf with PIO.
 *	   Or a valid poपूर्णांकer to be used with DMA. After use, release it by
 *	   calling i2c_put_dma_safe_msg_buf().
 *
 * This function must only be called from process context!
 */
u8 *i2c_get_dma_safe_msg_buf(काष्ठा i2c_msg *msg, अचिन्हित पूर्णांक threshold)
अणु
	/* also skip 0-length msgs क्रम bogus thresholds of 0 */
	अगर (!threshold)
		pr_debug("DMA buffer for addr=0x%02x with length 0 is bogus\n",
			 msg->addr);
	अगर (msg->len < threshold || msg->len == 0)
		वापस शून्य;

	अगर (msg->flags & I2C_M_DMA_SAFE)
		वापस msg->buf;

	pr_debug("using bounce buffer for addr=0x%02x, len=%d\n",
		 msg->addr, msg->len);

	अगर (msg->flags & I2C_M_RD)
		वापस kzalloc(msg->len, GFP_KERNEL);
	अन्यथा
		वापस kmemdup(msg->buf, msg->len, GFP_KERNEL);
पूर्ण
EXPORT_SYMBOL_GPL(i2c_get_dma_safe_msg_buf);

/**
 * i2c_put_dma_safe_msg_buf - release DMA safe buffer and sync with i2c_msg
 * @buf: the buffer obtained from i2c_get_dma_safe_msg_buf(). May be शून्य.
 * @msg: the message which the buffer corresponds to
 * @xferred: bool saying अगर the message was transferred
 */
व्योम i2c_put_dma_safe_msg_buf(u8 *buf, काष्ठा i2c_msg *msg, bool xferred)
अणु
	अगर (!buf || buf == msg->buf)
		वापस;

	अगर (xferred && msg->flags & I2C_M_RD)
		स_नकल(msg->buf, buf, msg->len);

	kमुक्त(buf);
पूर्ण
EXPORT_SYMBOL_GPL(i2c_put_dma_safe_msg_buf);

MODULE_AUTHOR("Simon G. Vogl <simon@tk.uni-linz.ac.at>");
MODULE_DESCRIPTION("I2C-Bus main module");
MODULE_LICENSE("GPL");
