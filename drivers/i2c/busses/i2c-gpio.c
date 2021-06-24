<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Bitbanging I2C bus driver using the GPIO API
 *
 * Copyright (C) 2007 Aपंचांगel Corporation
 */
#समावेश <linux/completion.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_data/i2c-gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

काष्ठा i2c_gpio_निजी_data अणु
	काष्ठा gpio_desc *sda;
	काष्ठा gpio_desc *scl;
	काष्ठा i2c_adapter adap;
	काष्ठा i2c_algo_bit_data bit_data;
	काष्ठा i2c_gpio_platक्रमm_data pdata;
#अगर_घोषित CONFIG_I2C_GPIO_FAULT_INJECTOR
	काष्ठा dentry *debug_dir;
	/* these must be रक्षित by bus lock */
	काष्ठा completion scl_irq_completion;
	u64 scl_irq_data;
#पूर्ण_अगर
पूर्ण;

/*
 * Toggle SDA by changing the output value of the pin. This is only
 * valid क्रम pins configured as खोलो drain (i.e. setting the value
 * high effectively turns off the output driver.)
 */
अटल व्योम i2c_gpio_setsda_val(व्योम *data, पूर्णांक state)
अणु
	काष्ठा i2c_gpio_निजी_data *priv = data;

	gpiod_set_value_cansleep(priv->sda, state);
पूर्ण

/*
 * Toggle SCL by changing the output value of the pin. This is used
 * क्रम pins that are configured as खोलो drain and क्रम output-only
 * pins. The latter हाल will अवरोध the i2c protocol, but it will
 * often work in practice.
 */
अटल व्योम i2c_gpio_setscl_val(व्योम *data, पूर्णांक state)
अणु
	काष्ठा i2c_gpio_निजी_data *priv = data;

	gpiod_set_value_cansleep(priv->scl, state);
पूर्ण

अटल पूर्णांक i2c_gpio_माला_लोda(व्योम *data)
अणु
	काष्ठा i2c_gpio_निजी_data *priv = data;

	वापस gpiod_get_value_cansleep(priv->sda);
पूर्ण

अटल पूर्णांक i2c_gpio_माला_लोcl(व्योम *data)
अणु
	काष्ठा i2c_gpio_निजी_data *priv = data;

	वापस gpiod_get_value_cansleep(priv->scl);
पूर्ण

#अगर_घोषित CONFIG_I2C_GPIO_FAULT_INJECTOR
अटल काष्ठा dentry *i2c_gpio_debug_dir;

#घोषणा setsda(bd, val)	((bd)->setsda((bd)->data, val))
#घोषणा setscl(bd, val)	((bd)->setscl((bd)->data, val))
#घोषणा माला_लोda(bd)	((bd)->माला_लोda((bd)->data))
#घोषणा माला_लोcl(bd)	((bd)->माला_लोcl((bd)->data))

#घोषणा WIRE_ATTRIBUTE(wire) \
अटल पूर्णांक fops_##wire##_get(व्योम *data, u64 *val)		\
अणु								\
	काष्ठा i2c_gpio_निजी_data *priv = data;		\
								\
	i2c_lock_bus(&priv->adap, I2C_LOCK_ROOT_ADAPTER);	\
	*val = get##wire(&priv->bit_data);			\
	i2c_unlock_bus(&priv->adap, I2C_LOCK_ROOT_ADAPTER);	\
	वापस 0;						\
पूर्ण								\
अटल पूर्णांक fops_##wire##_set(व्योम *data, u64 val)		\
अणु								\
	काष्ठा i2c_gpio_निजी_data *priv = data;		\
								\
	i2c_lock_bus(&priv->adap, I2C_LOCK_ROOT_ADAPTER);	\
	set##wire(&priv->bit_data, val);			\
	i2c_unlock_bus(&priv->adap, I2C_LOCK_ROOT_ADAPTER);	\
	वापस 0;						\
पूर्ण								\
DEFINE_DEBUGFS_ATTRIBUTE(fops_##wire, fops_##wire##_get, fops_##wire##_set, "%llu\n")

WIRE_ATTRIBUTE(scl);
WIRE_ATTRIBUTE(sda);

अटल व्योम i2c_gpio_incomplete_transfer(काष्ठा i2c_gpio_निजी_data *priv,
					u32 pattern, u8 pattern_size)
अणु
	काष्ठा i2c_algo_bit_data *bit_data = &priv->bit_data;
	पूर्णांक i;

	i2c_lock_bus(&priv->adap, I2C_LOCK_ROOT_ADAPTER);

	/* START condition */
	setsda(bit_data, 0);
	udelay(bit_data->udelay);

	/* Send pattern, request ACK, करोn't send STOP */
	क्रम (i = pattern_size - 1; i >= 0; i--) अणु
		setscl(bit_data, 0);
		udelay(bit_data->udelay / 2);
		setsda(bit_data, (pattern >> i) & 1);
		udelay((bit_data->udelay + 1) / 2);
		setscl(bit_data, 1);
		udelay(bit_data->udelay);
	पूर्ण

	i2c_unlock_bus(&priv->adap, I2C_LOCK_ROOT_ADAPTER);
पूर्ण

अटल पूर्णांक fops_incomplete_addr_phase_set(व्योम *data, u64 addr)
अणु
	काष्ठा i2c_gpio_निजी_data *priv = data;
	u32 pattern;

	अगर (addr > 0x7f)
		वापस -EINVAL;

	/* ADDR (7 bit) + RD (1 bit) + Client ACK, keep SDA hi (1 bit) */
	pattern = (addr << 2) | 3;

	i2c_gpio_incomplete_transfer(priv, pattern, 9);

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(fops_incomplete_addr_phase, शून्य, fops_incomplete_addr_phase_set, "%llu\n");

अटल पूर्णांक fops_incomplete_ग_लिखो_byte_set(व्योम *data, u64 addr)
अणु
	काष्ठा i2c_gpio_निजी_data *priv = data;
	u32 pattern;

	अगर (addr > 0x7f)
		वापस -EINVAL;

	/* ADDR (7 bit) + WR (1 bit) + Client ACK (1 bit) */
	pattern = (addr << 2) | 1;
	/* 0x00 (8 bit) + Client ACK, keep SDA hi (1 bit) */
	pattern = (pattern << 9) | 1;

	i2c_gpio_incomplete_transfer(priv, pattern, 18);

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(fops_incomplete_ग_लिखो_byte, शून्य, fops_incomplete_ग_लिखो_byte_set, "%llu\n");

अटल पूर्णांक i2c_gpio_fi_act_on_scl_irq(काष्ठा i2c_gpio_निजी_data *priv,
				       irqवापस_t handler(पूर्णांक, व्योम*))
अणु
	पूर्णांक ret, irq = gpiod_to_irq(priv->scl);

	अगर (irq < 0)
		वापस irq;

	i2c_lock_bus(&priv->adap, I2C_LOCK_ROOT_ADAPTER);

	ret = gpiod_direction_input(priv->scl);
	अगर (ret)
		जाओ unlock;

	reinit_completion(&priv->scl_irq_completion);

	ret = request_irq(irq, handler, IRQF_TRIGGER_FALLING,
			  "i2c_gpio_fault_injector_scl_irq", priv);
	अगर (ret)
		जाओ output;

	रुको_क्रम_completion_पूर्णांकerruptible(&priv->scl_irq_completion);

	मुक्त_irq(irq, priv);
 output:
	ret = gpiod_direction_output(priv->scl, 1) ?: ret;
 unlock:
	i2c_unlock_bus(&priv->adap, I2C_LOCK_ROOT_ADAPTER);

	वापस ret;
पूर्ण

अटल irqवापस_t lose_arbitration_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा i2c_gpio_निजी_data *priv = dev_id;

	setsda(&priv->bit_data, 0);
	udelay(priv->scl_irq_data);
	setsda(&priv->bit_data, 1);

	complete(&priv->scl_irq_completion);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक fops_lose_arbitration_set(व्योम *data, u64 duration)
अणु
	काष्ठा i2c_gpio_निजी_data *priv = data;

	अगर (duration > 100 * 1000)
		वापस -EINVAL;

	priv->scl_irq_data = duration;
	/*
	 * Interrupt on falling SCL. This ensures that the master under test has
	 * really started the transfer. Interrupt on falling SDA did only
	 * exercise 'bus busy' detection on some HW but not 'arbitration lost'.
	 * Note that the पूर्णांकerrupt latency may cause the first bits to be
	 * transmitted correctly.
	 */
	वापस i2c_gpio_fi_act_on_scl_irq(priv, lose_arbitration_irq);
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(fops_lose_arbitration, शून्य, fops_lose_arbitration_set, "%llu\n");

अटल irqवापस_t inject_panic_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा i2c_gpio_निजी_data *priv = dev_id;

	udelay(priv->scl_irq_data);
	panic("I2C fault injector induced panic");

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक fops_inject_panic_set(व्योम *data, u64 duration)
अणु
	काष्ठा i2c_gpio_निजी_data *priv = data;

	अगर (duration > 100 * 1000)
		वापस -EINVAL;

	priv->scl_irq_data = duration;
	/*
	 * Interrupt on falling SCL. This ensures that the master under test has
	 * really started the transfer.
	 */
	वापस i2c_gpio_fi_act_on_scl_irq(priv, inject_panic_irq);
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(fops_inject_panic, शून्य, fops_inject_panic_set, "%llu\n");

अटल व्योम i2c_gpio_fault_injector_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_gpio_निजी_data *priv = platक्रमm_get_drvdata(pdev);

	/*
	 * If there will be a debugfs-dir per i2c adapter somewhen, put the
	 * 'fault-injector' dir there. Until then, we have a global dir with
	 * all adapters as subdirs.
	 */
	अगर (!i2c_gpio_debug_dir) अणु
		i2c_gpio_debug_dir = debugfs_create_dir("i2c-fault-injector", शून्य);
		अगर (!i2c_gpio_debug_dir)
			वापस;
	पूर्ण

	priv->debug_dir = debugfs_create_dir(pdev->name, i2c_gpio_debug_dir);
	अगर (!priv->debug_dir)
		वापस;

	init_completion(&priv->scl_irq_completion);

	debugfs_create_file_unsafe("incomplete_address_phase", 0200, priv->debug_dir,
				   priv, &fops_incomplete_addr_phase);
	debugfs_create_file_unsafe("incomplete_write_byte", 0200, priv->debug_dir,
				   priv, &fops_incomplete_ग_लिखो_byte);
	अगर (priv->bit_data.माला_लोcl) अणु
		debugfs_create_file_unsafe("inject_panic", 0200, priv->debug_dir,
					   priv, &fops_inject_panic);
		debugfs_create_file_unsafe("lose_arbitration", 0200, priv->debug_dir,
					   priv, &fops_lose_arbitration);
	पूर्ण
	debugfs_create_file_unsafe("scl", 0600, priv->debug_dir, priv, &fops_scl);
	debugfs_create_file_unsafe("sda", 0600, priv->debug_dir, priv, &fops_sda);
पूर्ण

अटल व्योम i2c_gpio_fault_injector_निकास(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_gpio_निजी_data *priv = platक्रमm_get_drvdata(pdev);

	debugfs_हटाओ_recursive(priv->debug_dir);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम i2c_gpio_fault_injector_init(काष्ठा platक्रमm_device *pdev) अणुपूर्ण
अटल अंतरभूत व्योम i2c_gpio_fault_injector_निकास(काष्ठा platक्रमm_device *pdev) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_I2C_GPIO_FAULT_INJECTOR*/

अटल व्योम of_i2c_gpio_get_props(काष्ठा device_node *np,
				  काष्ठा i2c_gpio_platक्रमm_data *pdata)
अणु
	u32 reg;

	of_property_पढ़ो_u32(np, "i2c-gpio,delay-us", &pdata->udelay);

	अगर (!of_property_पढ़ो_u32(np, "i2c-gpio,timeout-ms", &reg))
		pdata->समयout = msecs_to_jअगरfies(reg);

	pdata->sda_is_खोलो_drain =
		of_property_पढ़ो_bool(np, "i2c-gpio,sda-open-drain");
	pdata->scl_is_खोलो_drain =
		of_property_पढ़ो_bool(np, "i2c-gpio,scl-open-drain");
	pdata->scl_is_output_only =
		of_property_पढ़ो_bool(np, "i2c-gpio,scl-output-only");
पूर्ण

अटल काष्ठा gpio_desc *i2c_gpio_get_desc(काष्ठा device *dev,
					   स्थिर अक्षर *con_id,
					   अचिन्हित पूर्णांक index,
					   क्रमागत gpiod_flags gflags)
अणु
	काष्ठा gpio_desc *retdesc;
	पूर्णांक ret;

	retdesc = devm_gpiod_get(dev, con_id, gflags);
	अगर (!IS_ERR(retdesc)) अणु
		dev_dbg(dev, "got GPIO from name %s\n", con_id);
		वापस retdesc;
	पूर्ण

	retdesc = devm_gpiod_get_index(dev, शून्य, index, gflags);
	अगर (!IS_ERR(retdesc)) अणु
		dev_dbg(dev, "got GPIO from index %u\n", index);
		वापस retdesc;
	पूर्ण

	ret = PTR_ERR(retdesc);

	/* FIXME: hack in the old code, is this really necessary? */
	अगर (ret == -EINVAL)
		retdesc = ERR_PTR(-EPROBE_DEFER);

	/* This happens अगर the GPIO driver is not yet probed, let's defer */
	अगर (ret == -ENOENT)
		retdesc = ERR_PTR(-EPROBE_DEFER);

	अगर (PTR_ERR(retdesc) != -EPROBE_DEFER)
		dev_err(dev, "error trying to get descriptor: %d\n", ret);

	वापस retdesc;
पूर्ण

अटल पूर्णांक i2c_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_gpio_निजी_data *priv;
	काष्ठा i2c_gpio_platक्रमm_data *pdata;
	काष्ठा i2c_algo_bit_data *bit_data;
	काष्ठा i2c_adapter *adap;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	क्रमागत gpiod_flags gflags;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	adap = &priv->adap;
	bit_data = &priv->bit_data;
	pdata = &priv->pdata;

	अगर (np) अणु
		of_i2c_gpio_get_props(np, pdata);
	पूर्ण अन्यथा अणु
		/*
		 * If all platक्रमm data settings are zero it is OK
		 * to not provide any platक्रमm data from the board.
		 */
		अगर (dev_get_platdata(dev))
			स_नकल(pdata, dev_get_platdata(dev), माप(*pdata));
	पूर्ण

	/*
	 * First get the GPIO pins; अगर it fails, we'll defer the probe.
	 * If the SCL/SDA lines are marked "open drain" by platक्रमm data or
	 * device tree then this means that something outside of our control is
	 * marking these lines to be handled as खोलो drain, and we should just
	 * handle them as we handle any other output. Else we enक्रमce खोलो
	 * drain as this is required क्रम an I2C bus.
	 */
	अगर (pdata->sda_is_खोलो_drain)
		gflags = GPIOD_OUT_HIGH;
	अन्यथा
		gflags = GPIOD_OUT_HIGH_OPEN_DRAIN;
	priv->sda = i2c_gpio_get_desc(dev, "sda", 0, gflags);
	अगर (IS_ERR(priv->sda))
		वापस PTR_ERR(priv->sda);

	अगर (pdata->scl_is_खोलो_drain)
		gflags = GPIOD_OUT_HIGH;
	अन्यथा
		gflags = GPIOD_OUT_HIGH_OPEN_DRAIN;
	priv->scl = i2c_gpio_get_desc(dev, "scl", 1, gflags);
	अगर (IS_ERR(priv->scl))
		वापस PTR_ERR(priv->scl);

	अगर (gpiod_cansleep(priv->sda) || gpiod_cansleep(priv->scl))
		dev_warn(dev, "Slow GPIO pins might wreak havoc into I2C/SMBus bus timing");
	अन्यथा
		bit_data->can_करो_atomic = true;

	bit_data->setsda = i2c_gpio_setsda_val;
	bit_data->setscl = i2c_gpio_setscl_val;

	अगर (!pdata->scl_is_output_only)
		bit_data->माला_लोcl = i2c_gpio_माला_लोcl;
	bit_data->माला_लोda = i2c_gpio_माला_लोda;

	अगर (pdata->udelay)
		bit_data->udelay = pdata->udelay;
	अन्यथा अगर (pdata->scl_is_output_only)
		bit_data->udelay = 50;			/* 10 kHz */
	अन्यथा
		bit_data->udelay = 5;			/* 100 kHz */

	अगर (pdata->समयout)
		bit_data->समयout = pdata->समयout;
	अन्यथा
		bit_data->समयout = HZ / 10;		/* 100 ms */

	bit_data->data = priv;

	adap->owner = THIS_MODULE;
	अगर (np)
		strlcpy(adap->name, dev_name(dev), माप(adap->name));
	अन्यथा
		snम_लिखो(adap->name, माप(adap->name), "i2c-gpio%d", pdev->id);

	adap->algo_data = bit_data;
	adap->class = I2C_CLASS_HWMON | I2C_CLASS_SPD;
	adap->dev.parent = dev;
	adap->dev.of_node = np;

	adap->nr = pdev->id;
	ret = i2c_bit_add_numbered_bus(adap);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, priv);

	/*
	 * FIXME: using global GPIO numbers is not helpful. If/when we
	 * get accessors to get the actual name of the GPIO line,
	 * from the descriptor, then provide that instead.
	 */
	dev_info(dev, "using lines %u (SDA) and %u (SCL%s)\n",
		 desc_to_gpio(priv->sda), desc_to_gpio(priv->scl),
		 pdata->scl_is_output_only
		 ? ", no clock stretching" : "");

	i2c_gpio_fault_injector_init(pdev);

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_gpio_निजी_data *priv;
	काष्ठा i2c_adapter *adap;

	i2c_gpio_fault_injector_निकास(pdev);

	priv = platक्रमm_get_drvdata(pdev);
	adap = &priv->adap;

	i2c_del_adapter(adap);

	वापस 0;
पूर्ण

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id i2c_gpio_dt_ids[] = अणु
	अणु .compatible = "i2c-gpio", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, i2c_gpio_dt_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver i2c_gpio_driver = अणु
	.driver		= अणु
		.name	= "i2c-gpio",
		.of_match_table	= of_match_ptr(i2c_gpio_dt_ids),
	पूर्ण,
	.probe		= i2c_gpio_probe,
	.हटाओ		= i2c_gpio_हटाओ,
पूर्ण;

अटल पूर्णांक __init i2c_gpio_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&i2c_gpio_driver);
	अगर (ret)
		prपूर्णांकk(KERN_ERR "i2c-gpio: probe failed: %d\n", ret);

	वापस ret;
पूर्ण
subsys_initcall(i2c_gpio_init);

अटल व्योम __निकास i2c_gpio_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&i2c_gpio_driver);
पूर्ण
module_निकास(i2c_gpio_निकास);

MODULE_AUTHOR("Haavard Skinnemoen (Atmel)");
MODULE_DESCRIPTION("Platform-independent bitbanging I2C driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:i2c-gpio");
