<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Intel CHT Whiskey Cove PMIC I2C Master driver
 * Copyright (C) 2017 Hans de Goede <hdegoede@redhat.com>
 *
 * Based on various non upstream patches to support the CHT Whiskey Cove PMIC:
 * Copyright (C) 2011 - 2014 Intel Corporation. All rights reserved.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer/bq24190_अक्षरger.h>
#समावेश <linux/slab.h>

#घोषणा CHT_WC_I2C_CTRL			0x5e24
#घोषणा CHT_WC_I2C_CTRL_WR		BIT(0)
#घोषणा CHT_WC_I2C_CTRL_RD		BIT(1)
#घोषणा CHT_WC_I2C_CLIENT_ADDR		0x5e25
#घोषणा CHT_WC_I2C_REG_OFFSET		0x5e26
#घोषणा CHT_WC_I2C_WRDATA		0x5e27
#घोषणा CHT_WC_I2C_RDDATA		0x5e28

#घोषणा CHT_WC_EXTCHGRIRQ		0x6e0a
#घोषणा CHT_WC_EXTCHGRIRQ_CLIENT_IRQ	BIT(0)
#घोषणा CHT_WC_EXTCHGRIRQ_WRITE_IRQ	BIT(1)
#घोषणा CHT_WC_EXTCHGRIRQ_READ_IRQ	BIT(2)
#घोषणा CHT_WC_EXTCHGRIRQ_NACK_IRQ	BIT(3)
#घोषणा CHT_WC_EXTCHGRIRQ_ADAP_IRQMASK	((u8)GENMASK(3, 1))
#घोषणा CHT_WC_EXTCHGRIRQ_MSK		0x6e17

काष्ठा cht_wc_i2c_adap अणु
	काष्ठा i2c_adapter adapter;
	रुको_queue_head_t रुको;
	काष्ठा irq_chip irqchip;
	काष्ठा mutex adap_lock;
	काष्ठा mutex irqchip_lock;
	काष्ठा regmap *regmap;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;
	काष्ठा i2c_client *client;
	पूर्णांक client_irq;
	u8 irq_mask;
	u8 old_irq_mask;
	पूर्णांक पढ़ो_data;
	bool io_error;
	bool करोne;
पूर्ण;

अटल irqवापस_t cht_wc_i2c_adap_thपढ़ो_handler(पूर्णांक id, व्योम *data)
अणु
	काष्ठा cht_wc_i2c_adap *adap = data;
	पूर्णांक ret, reg;

	mutex_lock(&adap->adap_lock);

	/* Read IRQs */
	ret = regmap_पढ़ो(adap->regmap, CHT_WC_EXTCHGRIRQ, &reg);
	अगर (ret) अणु
		dev_err(&adap->adapter.dev, "Error reading extchgrirq reg\n");
		mutex_unlock(&adap->adap_lock);
		वापस IRQ_NONE;
	पूर्ण

	reg &= ~adap->irq_mask;

	/* Reads must be acked after पढ़ोing the received data. */
	ret = regmap_पढ़ो(adap->regmap, CHT_WC_I2C_RDDATA, &adap->पढ़ो_data);
	अगर (ret)
		adap->io_error = true;

	/*
	 * Immediately ack IRQs, so that अगर new IRQs arrives जबतक we're
	 * handling the previous ones our irq will re-trigger when we're करोne.
	 */
	ret = regmap_ग_लिखो(adap->regmap, CHT_WC_EXTCHGRIRQ, reg);
	अगर (ret)
		dev_err(&adap->adapter.dev, "Error writing extchgrirq reg\n");

	अगर (reg & CHT_WC_EXTCHGRIRQ_ADAP_IRQMASK) अणु
		adap->io_error |= !!(reg & CHT_WC_EXTCHGRIRQ_NACK_IRQ);
		adap->करोne = true;
	पूर्ण

	mutex_unlock(&adap->adap_lock);

	अगर (reg & CHT_WC_EXTCHGRIRQ_ADAP_IRQMASK)
		wake_up(&adap->रुको);

	/*
	 * Do NOT use handle_nested_irq here, the client irq handler will
	 * likely want to करो i2c transfers and the i2c controller uses this
	 * पूर्णांकerrupt handler as well, so running the client irq handler from
	 * this thपढ़ो will cause things to lock up.
	 */
	अगर (reg & CHT_WC_EXTCHGRIRQ_CLIENT_IRQ) अणु
		/*
		 * generic_handle_irq expects local IRQs to be disabled
		 * as normally it is called from पूर्णांकerrupt context.
		 */
		local_irq_disable();
		generic_handle_irq(adap->client_irq);
		local_irq_enable();
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल u32 cht_wc_i2c_adap_master_func(काष्ठा i2c_adapter *adap)
अणु
	/* This i2c adapter only supports SMBUS byte transfers */
	वापस I2C_FUNC_SMBUS_BYTE_DATA;
पूर्ण

अटल पूर्णांक cht_wc_i2c_adap_smbus_xfer(काष्ठा i2c_adapter *_adap, u16 addr,
				      अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
				      u8 command, पूर्णांक size,
				      जोड़ i2c_smbus_data *data)
अणु
	काष्ठा cht_wc_i2c_adap *adap = i2c_get_adapdata(_adap);
	पूर्णांक ret;

	mutex_lock(&adap->adap_lock);
	adap->io_error = false;
	adap->करोne = false;
	mutex_unlock(&adap->adap_lock);

	ret = regmap_ग_लिखो(adap->regmap, CHT_WC_I2C_CLIENT_ADDR, addr);
	अगर (ret)
		वापस ret;

	अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
		ret = regmap_ग_लिखो(adap->regmap, CHT_WC_I2C_WRDATA, data->byte);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(adap->regmap, CHT_WC_I2C_REG_OFFSET, command);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(adap->regmap, CHT_WC_I2C_CTRL,
			   (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) ?
			   CHT_WC_I2C_CTRL_WR : CHT_WC_I2C_CTRL_RD);
	अगर (ret)
		वापस ret;

	ret = रुको_event_समयout(adap->रुको, adap->करोne, msecs_to_jअगरfies(30));
	अगर (ret == 0) अणु
		/*
		 * The CHT GPIO controller serializes all IRQs, someबार
		 * causing signअगरicant delays, check status manually.
		 */
		cht_wc_i2c_adap_thपढ़ो_handler(0, adap);
		अगर (!adap->करोne)
			वापस -ETIMEDOUT;
	पूर्ण

	ret = 0;
	mutex_lock(&adap->adap_lock);
	अगर (adap->io_error)
		ret = -EIO;
	अन्यथा अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ)
		data->byte = adap->पढ़ो_data;
	mutex_unlock(&adap->adap_lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm cht_wc_i2c_adap_algo = अणु
	.functionality = cht_wc_i2c_adap_master_func,
	.smbus_xfer = cht_wc_i2c_adap_smbus_xfer,
पूर्ण;

/*
 * We are an i2c-adapter which itself is part of an i2c-client. This means that
 * transfers करोne through us take adapter->bus_lock twice, once क्रम our parent
 * i2c-adapter and once to take our own bus_lock. Lockdep करोes not like this
 * nested locking, to make lockdep happy in the हाल of busses with muxes, the
 * i2c-core's i2c_adapter_lock_bus function calls:
 * rt_mutex_lock_nested(&adapter->bus_lock, i2c_adapter_depth(adapter));
 *
 * But i2c_adapter_depth only works when the direct parent of the adapter is
 * another adapter, as it is only meant क्रम muxes. In our हाल there is an
 * i2c-client and MFD instantiated platक्रमm_device in the parent->child chain
 * between the 2 devices.
 *
 * So we override the शेष i2c_lock_operations and pass a hardcoded
 * depth of 1 to rt_mutex_lock_nested, to make lockdep happy.
 *
 * Note that अगर there were to be a mux attached to our adapter, this would
 * अवरोध things again since the i2c-mux code expects the root-adapter to have
 * a locking depth of 0. But we always have only 1 client directly attached
 * in the क्रमm of the Charger IC paired with the CHT Whiskey Cove PMIC.
 */
अटल व्योम cht_wc_i2c_adap_lock_bus(काष्ठा i2c_adapter *adapter,
				 अचिन्हित पूर्णांक flags)
अणु
	rt_mutex_lock_nested(&adapter->bus_lock, 1);
पूर्ण

अटल पूर्णांक cht_wc_i2c_adap_trylock_bus(काष्ठा i2c_adapter *adapter,
				   अचिन्हित पूर्णांक flags)
अणु
	वापस rt_mutex_trylock(&adapter->bus_lock);
पूर्ण

अटल व्योम cht_wc_i2c_adap_unlock_bus(काष्ठा i2c_adapter *adapter,
				   अचिन्हित पूर्णांक flags)
अणु
	rt_mutex_unlock(&adapter->bus_lock);
पूर्ण

अटल स्थिर काष्ठा i2c_lock_operations cht_wc_i2c_adap_lock_ops = अणु
	.lock_bus =    cht_wc_i2c_adap_lock_bus,
	.trylock_bus = cht_wc_i2c_adap_trylock_bus,
	.unlock_bus =  cht_wc_i2c_adap_unlock_bus,
पूर्ण;

/**** irqchip क्रम the client connected to the extchgr i2c adapter ****/
अटल व्योम cht_wc_i2c_irq_lock(काष्ठा irq_data *data)
अणु
	काष्ठा cht_wc_i2c_adap *adap = irq_data_get_irq_chip_data(data);

	mutex_lock(&adap->irqchip_lock);
पूर्ण

अटल व्योम cht_wc_i2c_irq_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा cht_wc_i2c_adap *adap = irq_data_get_irq_chip_data(data);
	पूर्णांक ret;

	अगर (adap->irq_mask != adap->old_irq_mask) अणु
		ret = regmap_ग_लिखो(adap->regmap, CHT_WC_EXTCHGRIRQ_MSK,
				   adap->irq_mask);
		अगर (ret == 0)
			adap->old_irq_mask = adap->irq_mask;
		अन्यथा
			dev_err(&adap->adapter.dev, "Error writing EXTCHGRIRQ_MSK\n");
	पूर्ण

	mutex_unlock(&adap->irqchip_lock);
पूर्ण

अटल व्योम cht_wc_i2c_irq_enable(काष्ठा irq_data *data)
अणु
	काष्ठा cht_wc_i2c_adap *adap = irq_data_get_irq_chip_data(data);

	adap->irq_mask &= ~CHT_WC_EXTCHGRIRQ_CLIENT_IRQ;
पूर्ण

अटल व्योम cht_wc_i2c_irq_disable(काष्ठा irq_data *data)
अणु
	काष्ठा cht_wc_i2c_adap *adap = irq_data_get_irq_chip_data(data);

	adap->irq_mask |= CHT_WC_EXTCHGRIRQ_CLIENT_IRQ;
पूर्ण

अटल स्थिर काष्ठा irq_chip cht_wc_i2c_irq_chip = अणु
	.irq_bus_lock		= cht_wc_i2c_irq_lock,
	.irq_bus_sync_unlock	= cht_wc_i2c_irq_sync_unlock,
	.irq_disable		= cht_wc_i2c_irq_disable,
	.irq_enable		= cht_wc_i2c_irq_enable,
	.name			= "cht_wc_ext_chrg_irq_chip",
पूर्ण;

अटल स्थिर अक्षर * स्थिर bq24190_suppliers[] = अणु
	"tcpm-source-psy-i2c-fusb302" पूर्ण;

अटल स्थिर काष्ठा property_entry bq24190_props[] = अणु
	PROPERTY_ENTRY_STRING_ARRAY("supplied-from", bq24190_suppliers),
	PROPERTY_ENTRY_BOOL("omit-battery-class"),
	PROPERTY_ENTRY_BOOL("disable-reset"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा software_node bq24190_node = अणु
	.properties = bq24190_props,
पूर्ण;

अटल काष्ठा regulator_consumer_supply fusb302_consumer = अणु
	.supply = "vbus",
	/* Must match fusb302 dev_name in पूर्णांकel_cht_पूर्णांक33fe.c */
	.dev_name = "i2c-fusb302",
पूर्ण;

अटल स्थिर काष्ठा regulator_init_data bq24190_vbus_init_data = अणु
	.स्थिरraपूर्णांकs = अणु
		/* The name is used in पूर्णांकel_cht_पूर्णांक33fe.c करो not change. */
		.name = "cht_wc_usb_typec_vbus",
		.valid_ops_mask = REGULATOR_CHANGE_STATUS,
	पूर्ण,
	.consumer_supplies = &fusb302_consumer,
	.num_consumer_supplies = 1,
पूर्ण;

अटल काष्ठा bq24190_platक्रमm_data bq24190_pdata = अणु
	.regulator_init_data = &bq24190_vbus_init_data,
पूर्ण;

अटल पूर्णांक cht_wc_i2c_adap_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(pdev->dev.parent);
	काष्ठा cht_wc_i2c_adap *adap;
	काष्ठा i2c_board_info board_info = अणु
		.type = "bq24190",
		.addr = 0x6b,
		.dev_name = "bq24190",
		.swnode = &bq24190_node,
		.platक्रमm_data = &bq24190_pdata,
	पूर्ण;
	पूर्णांक ret, reg, irq;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	adap = devm_kzalloc(&pdev->dev, माप(*adap), GFP_KERNEL);
	अगर (!adap)
		वापस -ENOMEM;

	init_रुकोqueue_head(&adap->रुको);
	mutex_init(&adap->adap_lock);
	mutex_init(&adap->irqchip_lock);
	adap->irqchip = cht_wc_i2c_irq_chip;
	adap->regmap = pmic->regmap;
	adap->adapter.owner = THIS_MODULE;
	adap->adapter.class = I2C_CLASS_HWMON;
	adap->adapter.algo = &cht_wc_i2c_adap_algo;
	adap->adapter.lock_ops = &cht_wc_i2c_adap_lock_ops;
	strlcpy(adap->adapter.name, "PMIC I2C Adapter",
		माप(adap->adapter.name));
	adap->adapter.dev.parent = &pdev->dev;

	/* Clear and activate i2c-adapter पूर्णांकerrupts, disable client IRQ */
	adap->old_irq_mask = adap->irq_mask = ~CHT_WC_EXTCHGRIRQ_ADAP_IRQMASK;

	ret = regmap_पढ़ो(adap->regmap, CHT_WC_I2C_RDDATA, &reg);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(adap->regmap, CHT_WC_EXTCHGRIRQ, ~adap->irq_mask);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(adap->regmap, CHT_WC_EXTCHGRIRQ_MSK, adap->irq_mask);
	अगर (ret)
		वापस ret;

	/* Alloc and रेजिस्टर client IRQ */
	adap->irq_करोमुख्य = irq_करोमुख्य_add_linear(pdev->dev.of_node, 1,
						 &irq_करोमुख्य_simple_ops, शून्य);
	अगर (!adap->irq_करोमुख्य)
		वापस -ENOMEM;

	adap->client_irq = irq_create_mapping(adap->irq_करोमुख्य, 0);
	अगर (!adap->client_irq) अणु
		ret = -ENOMEM;
		जाओ हटाओ_irq_करोमुख्य;
	पूर्ण

	irq_set_chip_data(adap->client_irq, adap);
	irq_set_chip_and_handler(adap->client_irq, &adap->irqchip,
				 handle_simple_irq);

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
					cht_wc_i2c_adap_thपढ़ो_handler,
					IRQF_ONESHOT, "PMIC I2C Adapter", adap);
	अगर (ret)
		जाओ हटाओ_irq_करोमुख्य;

	i2c_set_adapdata(&adap->adapter, adap);
	ret = i2c_add_adapter(&adap->adapter);
	अगर (ret)
		जाओ हटाओ_irq_करोमुख्य;

	/*
	 * Normally the Whiskey Cove PMIC is paired with a TI bq24292i अक्षरger,
	 * connected to this i2c bus, and a max17047 fuel-gauge and a fusb302
	 * USB Type-C controller connected to another i2c bus. In this setup
	 * the max17047 and fusb302 devices are क्रमागतerated through an INT33FE
	 * ACPI device. If this device is present रेजिस्टर an i2c-client क्रम
	 * the TI bq24292i अक्षरger.
	 */
	अगर (acpi_dev_present("INT33FE", शून्य, -1)) अणु
		board_info.irq = adap->client_irq;
		adap->client = i2c_new_client_device(&adap->adapter, &board_info);
		अगर (IS_ERR(adap->client)) अणु
			ret = PTR_ERR(adap->client);
			जाओ del_adapter;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, adap);
	वापस 0;

del_adapter:
	i2c_del_adapter(&adap->adapter);
हटाओ_irq_करोमुख्य:
	irq_करोमुख्य_हटाओ(adap->irq_करोमुख्य);
	वापस ret;
पूर्ण

अटल पूर्णांक cht_wc_i2c_adap_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cht_wc_i2c_adap *adap = platक्रमm_get_drvdata(pdev);

	i2c_unरेजिस्टर_device(adap->client);
	i2c_del_adapter(&adap->adapter);
	irq_करोमुख्य_हटाओ(adap->irq_करोमुख्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id cht_wc_i2c_adap_id_table[] = अणु
	अणु .name = "cht_wcove_ext_chgr" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, cht_wc_i2c_adap_id_table);

अटल काष्ठा platक्रमm_driver cht_wc_i2c_adap_driver = अणु
	.probe = cht_wc_i2c_adap_i2c_probe,
	.हटाओ = cht_wc_i2c_adap_i2c_हटाओ,
	.driver = अणु
		.name = "cht_wcove_ext_chgr",
	पूर्ण,
	.id_table = cht_wc_i2c_adap_id_table,
पूर्ण;
module_platक्रमm_driver(cht_wc_i2c_adap_driver);

MODULE_DESCRIPTION("Intel CHT Whiskey Cove PMIC I2C Master driver");
MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_LICENSE("GPL");
