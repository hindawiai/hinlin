<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * GPIO driver क्रम the SMSC SCH311x Super-I/O chips
 *
 * Copyright (C) 2013 Bruno Ranकरोlf <br1@einfach.org>
 *
 * SuperIO functions and chip detection:
 * (c) Copyright 2008 Wim Van Sebroeck <wim@iguana.be>.
 */

#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>

#घोषणा DRV_NAME			"gpio-sch311x"

#घोषणा SCH311X_GPIO_CONF_सूची		BIT(0)
#घोषणा SCH311X_GPIO_CONF_INVERT	BIT(1)
#घोषणा SCH311X_GPIO_CONF_OPEN_DRAIN	BIT(7)

#घोषणा SIO_CONFIG_KEY_ENTER		0x55
#घोषणा SIO_CONFIG_KEY_EXIT		0xaa

#घोषणा GP1				0x4b

अटल पूर्णांक sch311x_ioports[] = अणु 0x2e, 0x4e, 0x162e, 0x164e पूर्ण;

अटल काष्ठा platक्रमm_device *sch311x_gpio_pdev;

काष्ठा sch311x_pdev_data अणु		/* platक्रमm device data */
	अचिन्हित लघु runसमय_reg;	/* runसमय रेजिस्टर base address */
पूर्ण;

काष्ठा sch311x_gpio_block अणु		/* one GPIO block runसमय data */
	काष्ठा gpio_chip chip;
	अचिन्हित लघु data_reg;	/* from definition below */
	अचिन्हित लघु *config_regs;	/* poपूर्णांकer to definition below */
	अचिन्हित लघु runसमय_reg;	/* runसमय रेजिस्टर */
	spinlock_t lock;		/* lock क्रम this GPIO block */
पूर्ण;

काष्ठा sch311x_gpio_priv अणु		/* driver निजी data */
	काष्ठा sch311x_gpio_block blocks[6];
पूर्ण;

काष्ठा sch311x_gpio_block_def अणु		/* रेजिस्टर address definitions */
	अचिन्हित लघु data_reg;
	अचिन्हित लघु config_regs[8];
	अचिन्हित लघु base;
पूर्ण;

/* Note: some GPIOs are not available, these are marked with 0x00 */

अटल काष्ठा sch311x_gpio_block_def sch311x_gpio_blocks[] = अणु
	अणु
		.data_reg = 0x4b,	/* GP1 */
		.config_regs = अणु0x23, 0x24, 0x25, 0x26, 0x27, 0x29, 0x2a, 0x2bपूर्ण,
		.base = 10,
	पूर्ण,
	अणु
		.data_reg = 0x4c,	/* GP2 */
		.config_regs = अणु0x00, 0x2c, 0x2d, 0x00, 0x00, 0x00, 0x00, 0x32पूर्ण,
		.base = 20,
	पूर्ण,
	अणु
		.data_reg = 0x4d,	/* GP3 */
		.config_regs = अणु0x33, 0x34, 0x35, 0x36, 0x37, 0x00, 0x39, 0x3aपूर्ण,
		.base = 30,
	पूर्ण,
	अणु
		.data_reg = 0x4e,	/* GP4 */
		.config_regs = अणु0x3b, 0x00, 0x3d, 0x00, 0x6e, 0x6f, 0x72, 0x73पूर्ण,
		.base = 40,
	पूर्ण,
	अणु
		.data_reg = 0x4f,	/* GP5 */
		.config_regs = अणु0x3f, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46पूर्ण,
		.base = 50,
	पूर्ण,
	अणु
		.data_reg = 0x50,	/* GP6 */
		.config_regs = अणु0x47, 0x48, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59पूर्ण,
		.base = 60,
	पूर्ण,
पूर्ण;

/*
 *	Super-IO functions
 */

अटल अंतरभूत पूर्णांक sch311x_sio_enter(पूर्णांक sio_config_port)
अणु
	/* Don't step on other drivers' I/O space by accident. */
	अगर (!request_muxed_region(sio_config_port, 2, DRV_NAME)) अणु
		pr_err(DRV_NAME "I/O address 0x%04x already in use\n",
		       sio_config_port);
		वापस -EBUSY;
	पूर्ण

	outb(SIO_CONFIG_KEY_ENTER, sio_config_port);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sch311x_sio_निकास(पूर्णांक sio_config_port)
अणु
	outb(SIO_CONFIG_KEY_EXIT, sio_config_port);
	release_region(sio_config_port, 2);
पूर्ण

अटल अंतरभूत पूर्णांक sch311x_sio_inb(पूर्णांक sio_config_port, पूर्णांक reg)
अणु
	outb(reg, sio_config_port);
	वापस inb(sio_config_port + 1);
पूर्ण

अटल अंतरभूत व्योम sch311x_sio_outb(पूर्णांक sio_config_port, पूर्णांक reg, पूर्णांक val)
अणु
	outb(reg, sio_config_port);
	outb(val, sio_config_port + 1);
पूर्ण


/*
 *	GPIO functions
 */

अटल पूर्णांक sch311x_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा sch311x_gpio_block *block = gpiochip_get_data(chip);

	अगर (block->config_regs[offset] == 0) /* GPIO is not available */
		वापस -ENODEV;

	अगर (!request_region(block->runसमय_reg + block->config_regs[offset],
			    1, DRV_NAME)) अणु
		dev_err(chip->parent, "Failed to request region 0x%04x.\n",
			block->runसमय_reg + block->config_regs[offset]);
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम sch311x_gpio_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा sch311x_gpio_block *block = gpiochip_get_data(chip);

	अगर (block->config_regs[offset] == 0) /* GPIO is not available */
		वापस;

	release_region(block->runसमय_reg + block->config_regs[offset], 1);
पूर्ण

अटल पूर्णांक sch311x_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा sch311x_gpio_block *block = gpiochip_get_data(chip);
	u8 data;

	spin_lock(&block->lock);
	data = inb(block->runसमय_reg + block->data_reg);
	spin_unlock(&block->lock);

	वापस !!(data & BIT(offset));
पूर्ण

अटल व्योम __sch311x_gpio_set(काष्ठा sch311x_gpio_block *block,
			       अचिन्हित offset, पूर्णांक value)
अणु
	u8 data = inb(block->runसमय_reg + block->data_reg);
	अगर (value)
		data |= BIT(offset);
	अन्यथा
		data &= ~BIT(offset);
	outb(data, block->runसमय_reg + block->data_reg);
पूर्ण

अटल व्योम sch311x_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset,
			     पूर्णांक value)
अणु
	काष्ठा sch311x_gpio_block *block = gpiochip_get_data(chip);

	spin_lock(&block->lock);
	__sch311x_gpio_set(block, offset, value);
	spin_unlock(&block->lock);
पूर्ण

अटल पूर्णांक sch311x_gpio_direction_in(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा sch311x_gpio_block *block = gpiochip_get_data(chip);
	u8 data;

	spin_lock(&block->lock);
	data = inb(block->runसमय_reg + block->config_regs[offset]);
	data |= SCH311X_GPIO_CONF_सूची;
	outb(data, block->runसमय_reg + block->config_regs[offset]);
	spin_unlock(&block->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक sch311x_gpio_direction_out(काष्ठा gpio_chip *chip, अचिन्हित offset,
				      पूर्णांक value)
अणु
	काष्ठा sch311x_gpio_block *block = gpiochip_get_data(chip);
	u8 data;

	spin_lock(&block->lock);

	data = inb(block->runसमय_reg + block->config_regs[offset]);
	data &= ~SCH311X_GPIO_CONF_सूची;
	outb(data, block->runसमय_reg + block->config_regs[offset]);
	__sch311x_gpio_set(block, offset, value);

	spin_unlock(&block->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक sch311x_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा sch311x_gpio_block *block = gpiochip_get_data(chip);
	u8 data;

	spin_lock(&block->lock);
	data = inb(block->runसमय_reg + block->config_regs[offset]);
	spin_unlock(&block->lock);

	अगर (data & SCH311X_GPIO_CONF_सूची)
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक sch311x_gpio_set_config(काष्ठा gpio_chip *chip, अचिन्हित offset,
				   अचिन्हित दीर्घ config)
अणु
	काष्ठा sch311x_gpio_block *block = gpiochip_get_data(chip);
	क्रमागत pin_config_param param = pinconf_to_config_param(config);
	u8 data;

	चयन (param) अणु
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		spin_lock(&block->lock);
		data = inb(block->runसमय_reg + block->config_regs[offset]);
		data |= SCH311X_GPIO_CONF_OPEN_DRAIN;
		outb(data, block->runसमय_reg + block->config_regs[offset]);
		spin_unlock(&block->lock);
		वापस 0;
	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		spin_lock(&block->lock);
		data = inb(block->runसमय_reg + block->config_regs[offset]);
		data &= ~SCH311X_GPIO_CONF_OPEN_DRAIN;
		outb(data, block->runसमय_reg + block->config_regs[offset]);
		spin_unlock(&block->lock);
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक sch311x_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sch311x_pdev_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा sch311x_gpio_priv *priv;
	काष्ठा sch311x_gpio_block *block;
	पूर्णांक err, i;

	/* we can रेजिस्टर all GPIO data रेजिस्टरs at once */
	अगर (!devm_request_region(&pdev->dev, pdata->runसमय_reg + GP1, 6,
		DRV_NAME)) अणु
		dev_err(&pdev->dev, "Failed to request region 0x%04x-0x%04x.\n",
			pdata->runसमय_reg + GP1, pdata->runसमय_reg + GP1 + 5);
		वापस -EBUSY;
	पूर्ण

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);

	क्रम (i = 0; i < ARRAY_SIZE(priv->blocks); i++) अणु
		block = &priv->blocks[i];

		spin_lock_init(&block->lock);

		block->chip.label = DRV_NAME;
		block->chip.owner = THIS_MODULE;
		block->chip.request = sch311x_gpio_request;
		block->chip.मुक्त = sch311x_gpio_मुक्त;
		block->chip.direction_input = sch311x_gpio_direction_in;
		block->chip.direction_output = sch311x_gpio_direction_out;
		block->chip.get_direction = sch311x_gpio_get_direction;
		block->chip.set_config = sch311x_gpio_set_config;
		block->chip.get = sch311x_gpio_get;
		block->chip.set = sch311x_gpio_set;
		block->chip.ngpio = 8;
		block->chip.parent = &pdev->dev;
		block->chip.base = sch311x_gpio_blocks[i].base;
		block->config_regs = sch311x_gpio_blocks[i].config_regs;
		block->data_reg = sch311x_gpio_blocks[i].data_reg;
		block->runसमय_reg = pdata->runसमय_reg;

		err = gpiochip_add_data(&block->chip, block);
		अगर (err < 0) अणु
			dev_err(&pdev->dev,
				"Could not register gpiochip, %d\n", err);
			जाओ निकास_err;
		पूर्ण
		dev_info(&pdev->dev,
			 "SMSC SCH311x GPIO block %d registered.\n", i);
	पूर्ण

	वापस 0;

निकास_err:
	/* release alपढ़ोy रेजिस्टरed chips */
	क्रम (--i; i >= 0; i--)
		gpiochip_हटाओ(&priv->blocks[i].chip);
	वापस err;
पूर्ण

अटल पूर्णांक sch311x_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sch311x_gpio_priv *priv = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(priv->blocks); i++) अणु
		gpiochip_हटाओ(&priv->blocks[i].chip);
		dev_info(&pdev->dev,
			 "SMSC SCH311x GPIO block %d unregistered.\n", i);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sch311x_gpio_driver = अणु
	.driver.name	= DRV_NAME,
	.probe		= sch311x_gpio_probe,
	.हटाओ		= sch311x_gpio_हटाओ,
पूर्ण;


/*
 *	Init & निकास routines
 */

अटल पूर्णांक __init sch311x_detect(पूर्णांक sio_config_port, अचिन्हित लघु *addr)
अणु
	पूर्णांक err = 0, reg;
	अचिन्हित लघु base_addr;
	u8 dev_id;

	err = sch311x_sio_enter(sio_config_port);
	अगर (err)
		वापस err;

	/* Check device ID. */
	reg = sch311x_sio_inb(sio_config_port, 0x20);
	चयन (reg) अणु
	हाल 0x7c: /* SCH3112 */
		dev_id = 2;
		अवरोध;
	हाल 0x7d: /* SCH3114 */
		dev_id = 4;
		अवरोध;
	हाल 0x7f: /* SCH3116 */
		dev_id = 6;
		अवरोध;
	शेष:
		err = -ENODEV;
		जाओ निकास;
	पूर्ण

	/* Select logical device A (runसमय रेजिस्टरs) */
	sch311x_sio_outb(sio_config_port, 0x07, 0x0a);

	/* Check अगर Logical Device Register is currently active */
	अगर ((sch311x_sio_inb(sio_config_port, 0x30) & 0x01) == 0)
		pr_info("Seems that LDN 0x0a is not active...\n");

	/* Get the base address of the runसमय रेजिस्टरs */
	base_addr = (sch311x_sio_inb(sio_config_port, 0x60) << 8) |
			   sch311x_sio_inb(sio_config_port, 0x61);
	अगर (!base_addr) अणु
		pr_err("Base address not set\n");
		err = -ENODEV;
		जाओ निकास;
	पूर्ण
	*addr = base_addr;

	pr_info("Found an SMSC SCH311%d chip at 0x%04x\n", dev_id, base_addr);

निकास:
	sch311x_sio_निकास(sio_config_port);
	वापस err;
पूर्ण

अटल पूर्णांक __init sch311x_gpio_pdev_add(स्थिर अचिन्हित लघु addr)
अणु
	काष्ठा sch311x_pdev_data pdata;
	पूर्णांक err;

	pdata.runसमय_reg = addr;

	sch311x_gpio_pdev = platक्रमm_device_alloc(DRV_NAME, -1);
	अगर (!sch311x_gpio_pdev)
		वापस -ENOMEM;

	err = platक्रमm_device_add_data(sch311x_gpio_pdev,
				       &pdata, माप(pdata));
	अगर (err) अणु
		pr_err(DRV_NAME "Platform data allocation failed\n");
		जाओ err;
	पूर्ण

	err = platक्रमm_device_add(sch311x_gpio_pdev);
	अगर (err) अणु
		pr_err(DRV_NAME "Device addition failed\n");
		जाओ err;
	पूर्ण
	वापस 0;

err:
	platक्रमm_device_put(sch311x_gpio_pdev);
	वापस err;
पूर्ण

अटल पूर्णांक __init sch311x_gpio_init(व्योम)
अणु
	पूर्णांक err, i;
	अचिन्हित लघु addr = 0;

	क्रम (i = 0; i < ARRAY_SIZE(sch311x_ioports); i++)
		अगर (sch311x_detect(sch311x_ioports[i], &addr) == 0)
			अवरोध;

	अगर (!addr)
		वापस -ENODEV;

	err = platक्रमm_driver_रेजिस्टर(&sch311x_gpio_driver);
	अगर (err)
		वापस err;

	err = sch311x_gpio_pdev_add(addr);
	अगर (err)
		जाओ unreg_platक्रमm_driver;

	वापस 0;

unreg_platक्रमm_driver:
	platक्रमm_driver_unरेजिस्टर(&sch311x_gpio_driver);
	वापस err;
पूर्ण

अटल व्योम __निकास sch311x_gpio_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(sch311x_gpio_pdev);
	platक्रमm_driver_unरेजिस्टर(&sch311x_gpio_driver);
पूर्ण

module_init(sch311x_gpio_init);
module_निकास(sch311x_gpio_निकास);

MODULE_AUTHOR("Bruno Randolf <br1@einfach.org>");
MODULE_DESCRIPTION("SMSC SCH311x GPIO Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:gpio-sch311x");
