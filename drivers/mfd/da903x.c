<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Base driver क्रम Dialog Semiconductor DA9030/DA9034
 *
 * Copyright (C) 2008 Compulab, Ltd.
 *	Mike Rapoport <mike@compulab.co.il>
 *
 * Copyright (C) 2006-2008 Marvell International Ltd.
 *	Eric Miao <eric.miao@marvell.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/da903x.h>
#समावेश <linux/slab.h>

#घोषणा DA9030_CHIP_ID		0x00
#घोषणा DA9030_EVENT_A		0x01
#घोषणा DA9030_EVENT_B		0x02
#घोषणा DA9030_EVENT_C		0x03
#घोषणा DA9030_STATUS		0x04
#घोषणा DA9030_IRQ_MASK_A	0x05
#घोषणा DA9030_IRQ_MASK_B	0x06
#घोषणा DA9030_IRQ_MASK_C	0x07
#घोषणा DA9030_SYS_CTRL_A	0x08
#घोषणा DA9030_SYS_CTRL_B	0x09
#घोषणा DA9030_FAULT_LOG	0x0a

#घोषणा DA9034_CHIP_ID		0x00
#घोषणा DA9034_EVENT_A		0x01
#घोषणा DA9034_EVENT_B		0x02
#घोषणा DA9034_EVENT_C		0x03
#घोषणा DA9034_EVENT_D		0x04
#घोषणा DA9034_STATUS_A		0x05
#घोषणा DA9034_STATUS_B		0x06
#घोषणा DA9034_IRQ_MASK_A	0x07
#घोषणा DA9034_IRQ_MASK_B	0x08
#घोषणा DA9034_IRQ_MASK_C	0x09
#घोषणा DA9034_IRQ_MASK_D	0x0a
#घोषणा DA9034_SYS_CTRL_A	0x0b
#घोषणा DA9034_SYS_CTRL_B	0x0c
#घोषणा DA9034_FAULT_LOG	0x0d

काष्ठा da903x_chip;

काष्ठा da903x_chip_ops अणु
	पूर्णांक	(*init_chip)(काष्ठा da903x_chip *);
	पूर्णांक	(*unmask_events)(काष्ठा da903x_chip *, अचिन्हित पूर्णांक events);
	पूर्णांक	(*mask_events)(काष्ठा da903x_chip *, अचिन्हित पूर्णांक events);
	पूर्णांक	(*पढ़ो_events)(काष्ठा da903x_chip *, अचिन्हित पूर्णांक *events);
	पूर्णांक	(*पढ़ो_status)(काष्ठा da903x_chip *, अचिन्हित पूर्णांक *status);
पूर्ण;

काष्ठा da903x_chip अणु
	काष्ठा i2c_client	*client;
	काष्ठा device		*dev;
	स्थिर काष्ठा da903x_chip_ops *ops;

	पूर्णांक			type;
	uपूर्णांक32_t		events_mask;

	काष्ठा mutex		lock;
	काष्ठा work_काष्ठा	irq_work;

	काष्ठा blocking_notअगरier_head notअगरier_list;
पूर्ण;

अटल अंतरभूत पूर्णांक __da903x_पढ़ो(काष्ठा i2c_client *client,
				पूर्णांक reg, uपूर्णांक8_t *val)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, reg);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed reading at 0x%02x\n", reg);
		वापस ret;
	पूर्ण

	*val = (uपूर्णांक8_t)ret;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __da903x_पढ़ोs(काष्ठा i2c_client *client, पूर्णांक reg,
				 पूर्णांक len, uपूर्णांक8_t *val)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_i2c_block_data(client, reg, len, val);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed reading from 0x%02x\n", reg);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __da903x_ग_लिखो(काष्ठा i2c_client *client,
				 पूर्णांक reg, uपूर्णांक8_t val)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, reg, val);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed writing 0x%02x to 0x%02x\n",
				val, reg);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __da903x_ग_लिखोs(काष्ठा i2c_client *client, पूर्णांक reg,
				  पूर्णांक len, uपूर्णांक8_t *val)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_i2c_block_data(client, reg, len, val);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed writings to 0x%02x\n", reg);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक da903x_रेजिस्टर_notअगरier(काष्ठा device *dev, काष्ठा notअगरier_block *nb,
				अचिन्हित पूर्णांक events)
अणु
	काष्ठा da903x_chip *chip = dev_get_drvdata(dev);

	chip->ops->unmask_events(chip, events);
	वापस blocking_notअगरier_chain_रेजिस्टर(&chip->notअगरier_list, nb);
पूर्ण
EXPORT_SYMBOL_GPL(da903x_रेजिस्टर_notअगरier);

पूर्णांक da903x_unरेजिस्टर_notअगरier(काष्ठा device *dev, काष्ठा notअगरier_block *nb,
				अचिन्हित पूर्णांक events)
अणु
	काष्ठा da903x_chip *chip = dev_get_drvdata(dev);

	chip->ops->mask_events(chip, events);
	वापस blocking_notअगरier_chain_unरेजिस्टर(&chip->notअगरier_list, nb);
पूर्ण
EXPORT_SYMBOL_GPL(da903x_unरेजिस्टर_notअगरier);

पूर्णांक da903x_ग_लिखो(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t val)
अणु
	वापस __da903x_ग_लिखो(to_i2c_client(dev), reg, val);
पूर्ण
EXPORT_SYMBOL_GPL(da903x_ग_लिखो);

पूर्णांक da903x_ग_लिखोs(काष्ठा device *dev, पूर्णांक reg, पूर्णांक len, uपूर्णांक8_t *val)
अणु
	वापस __da903x_ग_लिखोs(to_i2c_client(dev), reg, len, val);
पूर्ण
EXPORT_SYMBOL_GPL(da903x_ग_लिखोs);

पूर्णांक da903x_पढ़ो(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t *val)
अणु
	वापस __da903x_पढ़ो(to_i2c_client(dev), reg, val);
पूर्ण
EXPORT_SYMBOL_GPL(da903x_पढ़ो);

पूर्णांक da903x_पढ़ोs(काष्ठा device *dev, पूर्णांक reg, पूर्णांक len, uपूर्णांक8_t *val)
अणु
	वापस __da903x_पढ़ोs(to_i2c_client(dev), reg, len, val);
पूर्ण
EXPORT_SYMBOL_GPL(da903x_पढ़ोs);

पूर्णांक da903x_set_bits(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t bit_mask)
अणु
	काष्ठा da903x_chip *chip = dev_get_drvdata(dev);
	uपूर्णांक8_t reg_val;
	पूर्णांक ret = 0;

	mutex_lock(&chip->lock);

	ret = __da903x_पढ़ो(chip->client, reg, &reg_val);
	अगर (ret)
		जाओ out;

	अगर ((reg_val & bit_mask) != bit_mask) अणु
		reg_val |= bit_mask;
		ret = __da903x_ग_लिखो(chip->client, reg, reg_val);
	पूर्ण
out:
	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(da903x_set_bits);

पूर्णांक da903x_clr_bits(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t bit_mask)
अणु
	काष्ठा da903x_chip *chip = dev_get_drvdata(dev);
	uपूर्णांक8_t reg_val;
	पूर्णांक ret = 0;

	mutex_lock(&chip->lock);

	ret = __da903x_पढ़ो(chip->client, reg, &reg_val);
	अगर (ret)
		जाओ out;

	अगर (reg_val & bit_mask) अणु
		reg_val &= ~bit_mask;
		ret = __da903x_ग_लिखो(chip->client, reg, reg_val);
	पूर्ण
out:
	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(da903x_clr_bits);

पूर्णांक da903x_update(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t val, uपूर्णांक8_t mask)
अणु
	काष्ठा da903x_chip *chip = dev_get_drvdata(dev);
	uपूर्णांक8_t reg_val;
	पूर्णांक ret = 0;

	mutex_lock(&chip->lock);

	ret = __da903x_पढ़ो(chip->client, reg, &reg_val);
	अगर (ret)
		जाओ out;

	अगर ((reg_val & mask) != val) अणु
		reg_val = (reg_val & ~mask) | val;
		ret = __da903x_ग_लिखो(chip->client, reg, reg_val);
	पूर्ण
out:
	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(da903x_update);

पूर्णांक da903x_query_status(काष्ठा device *dev, अचिन्हित पूर्णांक sbits)
अणु
	काष्ठा da903x_chip *chip = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक status = 0;

	chip->ops->पढ़ो_status(chip, &status);
	वापस ((status & sbits) == sbits);
पूर्ण
EXPORT_SYMBOL(da903x_query_status);

अटल पूर्णांक da9030_init_chip(काष्ठा da903x_chip *chip)
अणु
	uपूर्णांक8_t chip_id;
	पूर्णांक err;

	err = __da903x_पढ़ो(chip->client, DA9030_CHIP_ID, &chip_id);
	अगर (err)
		वापस err;

	err = __da903x_ग_लिखो(chip->client, DA9030_SYS_CTRL_A, 0xE8);
	अगर (err)
		वापस err;

	dev_info(chip->dev, "DA9030 (CHIP ID: 0x%02x) detected\n", chip_id);
	वापस 0;
पूर्ण

अटल पूर्णांक da9030_unmask_events(काष्ठा da903x_chip *chip, अचिन्हित पूर्णांक events)
अणु
	uपूर्णांक8_t v[3];

	chip->events_mask &= ~events;

	v[0] = (chip->events_mask & 0xff);
	v[1] = (chip->events_mask >> 8) & 0xff;
	v[2] = (chip->events_mask >> 16) & 0xff;

	वापस __da903x_ग_लिखोs(chip->client, DA9030_IRQ_MASK_A, 3, v);
पूर्ण

अटल पूर्णांक da9030_mask_events(काष्ठा da903x_chip *chip, अचिन्हित पूर्णांक events)
अणु
	uपूर्णांक8_t v[3];

	chip->events_mask |= events;

	v[0] = (chip->events_mask & 0xff);
	v[1] = (chip->events_mask >> 8) & 0xff;
	v[2] = (chip->events_mask >> 16) & 0xff;

	वापस __da903x_ग_लिखोs(chip->client, DA9030_IRQ_MASK_A, 3, v);
पूर्ण

अटल पूर्णांक da9030_पढ़ो_events(काष्ठा da903x_chip *chip, अचिन्हित पूर्णांक *events)
अणु
	uपूर्णांक8_t v[3] = अणु0, 0, 0पूर्ण;
	पूर्णांक ret;

	ret = __da903x_पढ़ोs(chip->client, DA9030_EVENT_A, 3, v);
	अगर (ret < 0)
		वापस ret;

	*events = (v[2] << 16) | (v[1] << 8) | v[0];
	वापस 0;
पूर्ण

अटल पूर्णांक da9030_पढ़ो_status(काष्ठा da903x_chip *chip, अचिन्हित पूर्णांक *status)
अणु
	वापस __da903x_पढ़ो(chip->client, DA9030_STATUS, (uपूर्णांक8_t *)status);
पूर्ण

अटल पूर्णांक da9034_init_chip(काष्ठा da903x_chip *chip)
अणु
	uपूर्णांक8_t chip_id;
	पूर्णांक err;

	err = __da903x_पढ़ो(chip->client, DA9034_CHIP_ID, &chip_id);
	अगर (err)
		वापस err;

	err = __da903x_ग_लिखो(chip->client, DA9034_SYS_CTRL_A, 0xE8);
	अगर (err)
		वापस err;

	/* aव्योम SRAM घातer off during sleep*/
	__da903x_ग_लिखो(chip->client, 0x10, 0x07);
	__da903x_ग_लिखो(chip->client, 0x11, 0xff);
	__da903x_ग_लिखो(chip->client, 0x12, 0xff);

	/* Enable the ONKEY घातer करोwn functionality */
	__da903x_ग_लिखो(chip->client, DA9034_SYS_CTRL_B, 0x20);
	__da903x_ग_लिखो(chip->client, DA9034_SYS_CTRL_A, 0x60);

	/* workaround to make LEDs work */
	__da903x_ग_लिखो(chip->client, 0x90, 0x01);
	__da903x_ग_लिखो(chip->client, 0xB0, 0x08);

	/* make ADTV1 and SDTV1 effective */
	__da903x_ग_लिखो(chip->client, 0x20, 0x00);

	dev_info(chip->dev, "DA9034 (CHIP ID: 0x%02x) detected\n", chip_id);
	वापस 0;
पूर्ण

अटल पूर्णांक da9034_unmask_events(काष्ठा da903x_chip *chip, अचिन्हित पूर्णांक events)
अणु
	uपूर्णांक8_t v[4];

	chip->events_mask &= ~events;

	v[0] = (chip->events_mask & 0xff);
	v[1] = (chip->events_mask >> 8) & 0xff;
	v[2] = (chip->events_mask >> 16) & 0xff;
	v[3] = (chip->events_mask >> 24) & 0xff;

	वापस __da903x_ग_लिखोs(chip->client, DA9034_IRQ_MASK_A, 4, v);
पूर्ण

अटल पूर्णांक da9034_mask_events(काष्ठा da903x_chip *chip, अचिन्हित पूर्णांक events)
अणु
	uपूर्णांक8_t v[4];

	chip->events_mask |= events;

	v[0] = (chip->events_mask & 0xff);
	v[1] = (chip->events_mask >> 8) & 0xff;
	v[2] = (chip->events_mask >> 16) & 0xff;
	v[3] = (chip->events_mask >> 24) & 0xff;

	वापस __da903x_ग_लिखोs(chip->client, DA9034_IRQ_MASK_A, 4, v);
पूर्ण

अटल पूर्णांक da9034_पढ़ो_events(काष्ठा da903x_chip *chip, अचिन्हित पूर्णांक *events)
अणु
	uपूर्णांक8_t v[4] = अणु0, 0, 0, 0पूर्ण;
	पूर्णांक ret;

	ret = __da903x_पढ़ोs(chip->client, DA9034_EVENT_A, 4, v);
	अगर (ret < 0)
		वापस ret;

	*events = (v[3] << 24) | (v[2] << 16) | (v[1] << 8) | v[0];
	वापस 0;
पूर्ण

अटल पूर्णांक da9034_पढ़ो_status(काष्ठा da903x_chip *chip, अचिन्हित पूर्णांक *status)
अणु
	uपूर्णांक8_t v[2] = अणु0, 0पूर्ण;
	पूर्णांक ret = 0;

	ret = __da903x_पढ़ोs(chip->client, DA9034_STATUS_A, 2, v);
	अगर (ret)
		वापस ret;

	*status = (v[1] << 8) | v[0];
	वापस 0;
पूर्ण

अटल व्योम da903x_irq_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा da903x_chip *chip =
		container_of(work, काष्ठा da903x_chip, irq_work);
	अचिन्हित पूर्णांक events = 0;

	जबतक (1) अणु
		अगर (chip->ops->पढ़ो_events(chip, &events))
			अवरोध;

		events &= ~chip->events_mask;
		अगर (events == 0)
			अवरोध;

		blocking_notअगरier_call_chain(
				&chip->notअगरier_list, events, शून्य);
	पूर्ण
	enable_irq(chip->client->irq);
पूर्ण

अटल irqवापस_t da903x_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da903x_chip *chip = data;

	disable_irq_nosync(irq);
	(व्योम)schedule_work(&chip->irq_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा da903x_chip_ops da903x_ops[] = अणु
	[0] = अणु
		.init_chip	= da9030_init_chip,
		.unmask_events	= da9030_unmask_events,
		.mask_events	= da9030_mask_events,
		.पढ़ो_events	= da9030_पढ़ो_events,
		.पढ़ो_status	= da9030_पढ़ो_status,
	पूर्ण,
	[1] = अणु
		.init_chip	= da9034_init_chip,
		.unmask_events	= da9034_unmask_events,
		.mask_events	= da9034_mask_events,
		.पढ़ो_events	= da9034_पढ़ो_events,
		.पढ़ो_status	= da9034_पढ़ो_status,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id da903x_id_table[] = अणु
	अणु "da9030", 0 पूर्ण,
	अणु "da9034", 1 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, da903x_id_table);

अटल पूर्णांक __हटाओ_subdev(काष्ठा device *dev, व्योम *unused)
अणु
	platक्रमm_device_unरेजिस्टर(to_platक्रमm_device(dev));
	वापस 0;
पूर्ण

अटल पूर्णांक da903x_हटाओ_subdevs(काष्ठा da903x_chip *chip)
अणु
	वापस device_क्रम_each_child(chip->dev, शून्य, __हटाओ_subdev);
पूर्ण

अटल पूर्णांक da903x_add_subdevs(काष्ठा da903x_chip *chip,
					काष्ठा da903x_platक्रमm_data *pdata)
अणु
	काष्ठा da903x_subdev_info *subdev;
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < pdata->num_subdevs; i++) अणु
		subdev = &pdata->subdevs[i];

		pdev = platक्रमm_device_alloc(subdev->name, subdev->id);
		अगर (!pdev) अणु
			ret = -ENOMEM;
			जाओ failed;
		पूर्ण

		pdev->dev.parent = chip->dev;
		pdev->dev.platक्रमm_data = subdev->platक्रमm_data;

		ret = platक्रमm_device_add(pdev);
		अगर (ret) अणु
			platक्रमm_device_put(pdev);
			जाओ failed;
		पूर्ण
	पूर्ण
	वापस 0;

failed:
	da903x_हटाओ_subdevs(chip);
	वापस ret;
पूर्ण

अटल पूर्णांक da903x_probe(काष्ठा i2c_client *client,
				  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा da903x_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा da903x_chip *chip;
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक ret;

	chip = devm_kzalloc(&client->dev, माप(काष्ठा da903x_chip),
				GFP_KERNEL);
	अगर (chip == शून्य)
		वापस -ENOMEM;

	chip->client = client;
	chip->dev = &client->dev;
	chip->ops = &da903x_ops[id->driver_data];

	mutex_init(&chip->lock);
	INIT_WORK(&chip->irq_work, da903x_irq_work);
	BLOCKING_INIT_NOTIFIER_HEAD(&chip->notअगरier_list);

	i2c_set_clientdata(client, chip);

	ret = chip->ops->init_chip(chip);
	अगर (ret)
		वापस ret;

	/* mask and clear all IRQs */
	chip->events_mask = 0xffffffff;
	chip->ops->mask_events(chip, chip->events_mask);
	chip->ops->पढ़ो_events(chip, &पंचांगp);

	ret = devm_request_irq(&client->dev, client->irq, da903x_irq_handler,
			IRQF_TRIGGER_FALLING,
			"da903x", chip);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to request irq %d\n",
				client->irq);
		वापस ret;
	पूर्ण

	वापस da903x_add_subdevs(chip, pdata);
पूर्ण

अटल पूर्णांक da903x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा da903x_chip *chip = i2c_get_clientdata(client);

	da903x_हटाओ_subdevs(chip);
	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver da903x_driver = अणु
	.driver	= अणु
		.name	= "da903x",
	पूर्ण,
	.probe		= da903x_probe,
	.हटाओ		= da903x_हटाओ,
	.id_table	= da903x_id_table,
पूर्ण;

अटल पूर्णांक __init da903x_init(व्योम)
अणु
	वापस i2c_add_driver(&da903x_driver);
पूर्ण
subsys_initcall(da903x_init);

अटल व्योम __निकास da903x_निकास(व्योम)
अणु
	i2c_del_driver(&da903x_driver);
पूर्ण
module_निकास(da903x_निकास);

MODULE_DESCRIPTION("PMIC Driver for Dialog Semiconductor DA9034");
MODULE_AUTHOR("Eric Miao <eric.miao@marvell.com>");
MODULE_AUTHOR("Mike Rapoport <mike@compulab.co.il>");
MODULE_LICENSE("GPL v2");
