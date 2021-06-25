<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * I2C multiplexer
 *
 * Copyright (c) 2008-2009 Roकरोlfo Giometti <giometti@linux.it>
 * Copyright (c) 2008-2009 Eurotech S.p.A. <info@eurotech.it>
 *
 * This module supports the PCA954x and PCA984x series of I2C multiplexer/चयन
 * chips made by NXP Semiconductors.
 * This includes the:
 *	 PCA9540, PCA9542, PCA9543, PCA9544, PCA9545, PCA9546, PCA9547,
 *	 PCA9548, PCA9846, PCA9847, PCA9848 and PCA9849.
 *
 * These chips are all controlled via the I2C bus itself, and all have a
 * single 8-bit रेजिस्टर. The upstream "parent" bus fans out to two,
 * four, or eight करोwnstream busses or channels; which of these
 * are selected is determined by the chip type and रेजिस्टर contents. A
 * mux can select only one sub-bus at a समय; a चयन can select any
 * combination simultaneously.
 *
 * Based on:
 *	pca954x.c from Kumar Gala <galak@kernel.crashing.org>
 * Copyright (C) 2006
 *
 * Based on:
 *	pca954x.c from Ken Harrenstien
 * Copyright (C) 2004 Google, Inc. (Ken Harrenstien)
 *
 * Based on:
 *	i2c-भव_cb.c from Brian Kuschak <bkuschak@yahoo.com>
 * and
 *	pca9540.c from Jean Delvare <jdelvare@suse.de>.
 */

#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-mux.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/pm.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <dt-bindings/mux/mux.h>

#घोषणा PCA954X_MAX_NCHANS 8

#घोषणा PCA954X_IRQ_OFFSET 4

क्रमागत pca_type अणु
	pca_9540,
	pca_9542,
	pca_9543,
	pca_9544,
	pca_9545,
	pca_9546,
	pca_9547,
	pca_9548,
	pca_9846,
	pca_9847,
	pca_9848,
	pca_9849,
पूर्ण;

काष्ठा chip_desc अणु
	u8 nchans;
	u8 enable;	/* used क्रम muxes only */
	u8 has_irq;
	क्रमागत muxtype अणु
		pca954x_ismux = 0,
		pca954x_isswi
	पूर्ण muxtype;
	काष्ठा i2c_device_identity id;
पूर्ण;

काष्ठा pca954x अणु
	स्थिर काष्ठा chip_desc *chip;

	u8 last_chan;		/* last रेजिस्टर value */
	/* MUX_IDLE_AS_IS, MUX_IDLE_DISCONNECT or >= 0 क्रम channel */
	s32 idle_state;

	काष्ठा i2c_client *client;

	काष्ठा irq_करोमुख्य *irq;
	अचिन्हित पूर्णांक irq_mask;
	raw_spinlock_t lock;
पूर्ण;

/* Provide specs क्रम the PCA954x types we know about */
अटल स्थिर काष्ठा chip_desc chips[] = अणु
	[pca_9540] = अणु
		.nchans = 2,
		.enable = 0x4,
		.muxtype = pca954x_ismux,
		.id = अणु .manufacturer_id = I2C_DEVICE_ID_NONE पूर्ण,
	पूर्ण,
	[pca_9542] = अणु
		.nchans = 2,
		.enable = 0x4,
		.has_irq = 1,
		.muxtype = pca954x_ismux,
		.id = अणु .manufacturer_id = I2C_DEVICE_ID_NONE पूर्ण,
	पूर्ण,
	[pca_9543] = अणु
		.nchans = 2,
		.has_irq = 1,
		.muxtype = pca954x_isswi,
		.id = अणु .manufacturer_id = I2C_DEVICE_ID_NONE पूर्ण,
	पूर्ण,
	[pca_9544] = अणु
		.nchans = 4,
		.enable = 0x4,
		.has_irq = 1,
		.muxtype = pca954x_ismux,
		.id = अणु .manufacturer_id = I2C_DEVICE_ID_NONE पूर्ण,
	पूर्ण,
	[pca_9545] = अणु
		.nchans = 4,
		.has_irq = 1,
		.muxtype = pca954x_isswi,
		.id = अणु .manufacturer_id = I2C_DEVICE_ID_NONE पूर्ण,
	पूर्ण,
	[pca_9546] = अणु
		.nchans = 4,
		.muxtype = pca954x_isswi,
		.id = अणु .manufacturer_id = I2C_DEVICE_ID_NONE पूर्ण,
	पूर्ण,
	[pca_9547] = अणु
		.nchans = 8,
		.enable = 0x8,
		.muxtype = pca954x_ismux,
		.id = अणु .manufacturer_id = I2C_DEVICE_ID_NONE पूर्ण,
	पूर्ण,
	[pca_9548] = अणु
		.nchans = 8,
		.muxtype = pca954x_isswi,
		.id = अणु .manufacturer_id = I2C_DEVICE_ID_NONE पूर्ण,
	पूर्ण,
	[pca_9846] = अणु
		.nchans = 4,
		.muxtype = pca954x_isswi,
		.id = अणु
			.manufacturer_id = I2C_DEVICE_ID_NXP_SEMICONDUCTORS,
			.part_id = 0x10b,
		पूर्ण,
	पूर्ण,
	[pca_9847] = अणु
		.nchans = 8,
		.enable = 0x8,
		.muxtype = pca954x_ismux,
		.id = अणु
			.manufacturer_id = I2C_DEVICE_ID_NXP_SEMICONDUCTORS,
			.part_id = 0x108,
		पूर्ण,
	पूर्ण,
	[pca_9848] = अणु
		.nchans = 8,
		.muxtype = pca954x_isswi,
		.id = अणु
			.manufacturer_id = I2C_DEVICE_ID_NXP_SEMICONDUCTORS,
			.part_id = 0x10a,
		पूर्ण,
	पूर्ण,
	[pca_9849] = अणु
		.nchans = 4,
		.enable = 0x4,
		.muxtype = pca954x_ismux,
		.id = अणु
			.manufacturer_id = I2C_DEVICE_ID_NXP_SEMICONDUCTORS,
			.part_id = 0x109,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id pca954x_id[] = अणु
	अणु "pca9540", pca_9540 पूर्ण,
	अणु "pca9542", pca_9542 पूर्ण,
	अणु "pca9543", pca_9543 पूर्ण,
	अणु "pca9544", pca_9544 पूर्ण,
	अणु "pca9545", pca_9545 पूर्ण,
	अणु "pca9546", pca_9546 पूर्ण,
	अणु "pca9547", pca_9547 पूर्ण,
	अणु "pca9548", pca_9548 पूर्ण,
	अणु "pca9846", pca_9846 पूर्ण,
	अणु "pca9847", pca_9847 पूर्ण,
	अणु "pca9848", pca_9848 पूर्ण,
	अणु "pca9849", pca_9849 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pca954x_id);

अटल स्थिर काष्ठा of_device_id pca954x_of_match[] = अणु
	अणु .compatible = "nxp,pca9540", .data = &chips[pca_9540] पूर्ण,
	अणु .compatible = "nxp,pca9542", .data = &chips[pca_9542] पूर्ण,
	अणु .compatible = "nxp,pca9543", .data = &chips[pca_9543] पूर्ण,
	अणु .compatible = "nxp,pca9544", .data = &chips[pca_9544] पूर्ण,
	अणु .compatible = "nxp,pca9545", .data = &chips[pca_9545] पूर्ण,
	अणु .compatible = "nxp,pca9546", .data = &chips[pca_9546] पूर्ण,
	अणु .compatible = "nxp,pca9547", .data = &chips[pca_9547] पूर्ण,
	अणु .compatible = "nxp,pca9548", .data = &chips[pca_9548] पूर्ण,
	अणु .compatible = "nxp,pca9846", .data = &chips[pca_9846] पूर्ण,
	अणु .compatible = "nxp,pca9847", .data = &chips[pca_9847] पूर्ण,
	अणु .compatible = "nxp,pca9848", .data = &chips[pca_9848] पूर्ण,
	अणु .compatible = "nxp,pca9849", .data = &chips[pca_9849] पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pca954x_of_match);

/* Write to mux रेजिस्टर. Don't use i2c_transfer()/i2c_smbus_xfer()
   क्रम this as they will try to lock adapter a second समय */
अटल पूर्णांक pca954x_reg_ग_लिखो(काष्ठा i2c_adapter *adap,
			     काष्ठा i2c_client *client, u8 val)
अणु
	जोड़ i2c_smbus_data dummy;

	वापस __i2c_smbus_xfer(adap, client->addr, client->flags,
				I2C_SMBUS_WRITE, val,
				I2C_SMBUS_BYTE, &dummy);
पूर्ण

अटल u8 pca954x_regval(काष्ठा pca954x *data, u8 chan)
अणु
	/* We make चयनes look like muxes, not sure how to be smarter. */
	अगर (data->chip->muxtype == pca954x_ismux)
		वापस chan | data->chip->enable;
	अन्यथा
		वापस 1 << chan;
पूर्ण

अटल पूर्णांक pca954x_select_chan(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	काष्ठा pca954x *data = i2c_mux_priv(muxc);
	काष्ठा i2c_client *client = data->client;
	u8 regval;
	पूर्णांक ret = 0;

	regval = pca954x_regval(data, chan);
	/* Only select the channel अगर its dअगरferent from the last channel */
	अगर (data->last_chan != regval) अणु
		ret = pca954x_reg_ग_लिखो(muxc->parent, client, regval);
		data->last_chan = ret < 0 ? 0 : regval;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pca954x_deselect_mux(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	काष्ठा pca954x *data = i2c_mux_priv(muxc);
	काष्ठा i2c_client *client = data->client;
	s32 idle_state;

	idle_state = READ_ONCE(data->idle_state);
	अगर (idle_state >= 0)
		/* Set the mux back to a predetermined channel */
		वापस pca954x_select_chan(muxc, idle_state);

	अगर (idle_state == MUX_IDLE_DISCONNECT) अणु
		/* Deselect active channel */
		data->last_chan = 0;
		वापस pca954x_reg_ग_लिखो(muxc->parent, client,
					 data->last_chan);
	पूर्ण

	/* otherwise leave as-is */

	वापस 0;
पूर्ण

अटल sमाप_प्रकार idle_state_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा i2c_mux_core *muxc = i2c_get_clientdata(client);
	काष्ठा pca954x *data = i2c_mux_priv(muxc);

	वापस प्र_लिखो(buf, "%d\n", READ_ONCE(data->idle_state));
पूर्ण

अटल sमाप_प्रकार idle_state_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा i2c_mux_core *muxc = i2c_get_clientdata(client);
	काष्ठा pca954x *data = i2c_mux_priv(muxc);
	पूर्णांक val;
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(buf, 0, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (val != MUX_IDLE_AS_IS && val != MUX_IDLE_DISCONNECT &&
	    (val < 0 || val >= data->chip->nchans))
		वापस -EINVAL;

	i2c_lock_bus(muxc->parent, I2C_LOCK_SEGMENT);

	WRITE_ONCE(data->idle_state, val);
	/*
	 * Set the mux पूर्णांकo a state consistent with the new
	 * idle_state.
	 */
	अगर (data->last_chan || val != MUX_IDLE_DISCONNECT)
		ret = pca954x_deselect_mux(muxc, 0);

	i2c_unlock_bus(muxc->parent, I2C_LOCK_SEGMENT);

	वापस ret < 0 ? ret : count;
पूर्ण

अटल DEVICE_ATTR_RW(idle_state);

अटल irqवापस_t pca954x_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pca954x *data = dev_id;
	अचिन्हित दीर्घ pending;
	पूर्णांक ret, i;

	ret = i2c_smbus_पढ़ो_byte(data->client);
	अगर (ret < 0)
		वापस IRQ_NONE;

	pending = (ret >> PCA954X_IRQ_OFFSET) & (BIT(data->chip->nchans) - 1);
	क्रम_each_set_bit(i, &pending, data->chip->nchans)
		handle_nested_irq(irq_linear_revmap(data->irq, i));

	वापस IRQ_RETVAL(pending);
पूर्ण

अटल पूर्णांक pca954x_irq_set_type(काष्ठा irq_data *idata, अचिन्हित पूर्णांक type)
अणु
	अगर ((type & IRQ_TYPE_SENSE_MASK) != IRQ_TYPE_LEVEL_LOW)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल काष्ठा irq_chip pca954x_irq_chip = अणु
	.name = "i2c-mux-pca954x",
	.irq_set_type = pca954x_irq_set_type,
पूर्ण;

अटल पूर्णांक pca954x_irq_setup(काष्ठा i2c_mux_core *muxc)
अणु
	काष्ठा pca954x *data = i2c_mux_priv(muxc);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक c, irq;

	अगर (!data->chip->has_irq || client->irq <= 0)
		वापस 0;

	raw_spin_lock_init(&data->lock);

	data->irq = irq_करोमुख्य_add_linear(client->dev.of_node,
					  data->chip->nchans,
					  &irq_करोमुख्य_simple_ops, data);
	अगर (!data->irq)
		वापस -ENODEV;

	क्रम (c = 0; c < data->chip->nchans; c++) अणु
		irq = irq_create_mapping(data->irq, c);
		अगर (!irq) अणु
			dev_err(&client->dev, "failed irq create map\n");
			वापस -EINVAL;
		पूर्ण
		irq_set_chip_data(irq, data);
		irq_set_chip_and_handler(irq, &pca954x_irq_chip,
			handle_simple_irq);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pca954x_cleanup(काष्ठा i2c_mux_core *muxc)
अणु
	काष्ठा pca954x *data = i2c_mux_priv(muxc);
	पूर्णांक c, irq;

	अगर (data->irq) अणु
		क्रम (c = 0; c < data->chip->nchans; c++) अणु
			irq = irq_find_mapping(data->irq, c);
			irq_dispose_mapping(irq);
		पूर्ण
		irq_करोमुख्य_हटाओ(data->irq);
	पूर्ण
	i2c_mux_del_adapters(muxc);
पूर्ण

अटल पूर्णांक pca954x_init(काष्ठा i2c_client *client, काष्ठा pca954x *data)
अणु
	पूर्णांक ret;

	अगर (data->idle_state >= 0)
		data->last_chan = pca954x_regval(data, data->idle_state);
	अन्यथा
		data->last_chan = 0; /* Disconnect multiplexer */

	ret = i2c_smbus_ग_लिखो_byte(client, data->last_chan);
	अगर (ret < 0)
		data->last_chan = 0;

	वापस ret;
पूर्ण

/*
 * I2C init/probing/निकास functions
 */
अटल पूर्णांक pca954x_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adap = client->adapter;
	काष्ठा device *dev = &client->dev;
	काष्ठा gpio_desc *gpio;
	काष्ठा i2c_mux_core *muxc;
	काष्ठा pca954x *data;
	पूर्णांक num;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(adap, I2C_FUNC_SMBUS_BYTE))
		वापस -ENODEV;

	muxc = i2c_mux_alloc(adap, dev, PCA954X_MAX_NCHANS, माप(*data), 0,
			     pca954x_select_chan, pca954x_deselect_mux);
	अगर (!muxc)
		वापस -ENOMEM;
	data = i2c_mux_priv(muxc);

	i2c_set_clientdata(client, muxc);
	data->client = client;

	/* Reset the mux अगर a reset GPIO is specअगरied. */
	gpio = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(gpio))
		वापस PTR_ERR(gpio);
	अगर (gpio) अणु
		udelay(1);
		gpiod_set_value_cansleep(gpio, 0);
		/* Give the chip some समय to recover. */
		udelay(1);
	पूर्ण

	data->chip = device_get_match_data(dev);
	अगर (!data->chip)
		data->chip = &chips[id->driver_data];

	अगर (data->chip->id.manufacturer_id != I2C_DEVICE_ID_NONE) अणु
		काष्ठा i2c_device_identity id;

		ret = i2c_get_device_id(client, &id);
		अगर (ret && ret != -EOPNOTSUPP)
			वापस ret;

		अगर (!ret &&
		    (id.manufacturer_id != data->chip->id.manufacturer_id ||
		     id.part_id != data->chip->id.part_id)) अणु
			dev_warn(dev, "unexpected device id %03x-%03x-%x\n",
				 id.manufacturer_id, id.part_id,
				 id.die_revision);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	data->idle_state = MUX_IDLE_AS_IS;
	अगर (device_property_पढ़ो_u32(dev, "idle-state", &data->idle_state)) अणु
		अगर (device_property_पढ़ो_bool(dev, "i2c-mux-idle-disconnect"))
			data->idle_state = MUX_IDLE_DISCONNECT;
	पूर्ण

	/*
	 * Write the mux रेजिस्टर at addr to verअगरy
	 * that the mux is in fact present. This also
	 * initializes the mux to a channel
	 * or disconnected state.
	 */
	ret = pca954x_init(client, data);
	अगर (ret < 0) अणु
		dev_warn(dev, "probe failed\n");
		वापस -ENODEV;
	पूर्ण

	ret = pca954x_irq_setup(muxc);
	अगर (ret)
		जाओ fail_cleanup;

	/* Now create an adapter क्रम each channel */
	क्रम (num = 0; num < data->chip->nchans; num++) अणु
		ret = i2c_mux_add_adapter(muxc, 0, num, 0);
		अगर (ret)
			जाओ fail_cleanup;
	पूर्ण

	अगर (data->irq) अणु
		ret = devm_request_thपढ़ोed_irq(dev, data->client->irq,
						शून्य, pca954x_irq_handler,
						IRQF_ONESHOT | IRQF_SHARED,
						"pca954x", data);
		अगर (ret)
			जाओ fail_cleanup;
	पूर्ण

	/*
	 * The attr probably isn't going to be needed in most हालs,
	 * so करोn't fail completely on error.
	 */
	device_create_file(dev, &dev_attr_idle_state);

	dev_info(dev, "registered %d multiplexed busses for I2C %s %s\n",
		 num, data->chip->muxtype == pca954x_ismux
				? "mux" : "switch", client->name);

	वापस 0;

fail_cleanup:
	pca954x_cleanup(muxc);
	वापस ret;
पूर्ण

अटल पूर्णांक pca954x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_mux_core *muxc = i2c_get_clientdata(client);

	device_हटाओ_file(&client->dev, &dev_attr_idle_state);

	pca954x_cleanup(muxc);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pca954x_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा i2c_mux_core *muxc = i2c_get_clientdata(client);
	काष्ठा pca954x *data = i2c_mux_priv(muxc);
	पूर्णांक ret;

	ret = pca954x_init(client, data);
	अगर (ret < 0)
		dev_err(&client->dev, "failed to verify mux presence\n");

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(pca954x_pm, शून्य, pca954x_resume);

अटल काष्ठा i2c_driver pca954x_driver = अणु
	.driver		= अणु
		.name	= "pca954x",
		.pm	= &pca954x_pm,
		.of_match_table = pca954x_of_match,
	पूर्ण,
	.probe		= pca954x_probe,
	.हटाओ		= pca954x_हटाओ,
	.id_table	= pca954x_id,
पूर्ण;

module_i2c_driver(pca954x_driver);

MODULE_AUTHOR("Rodolfo Giometti <giometti@linux.it>");
MODULE_DESCRIPTION("PCA954x I2C mux/switch driver");
MODULE_LICENSE("GPL v2");
