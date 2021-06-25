<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Core support क्रम ATC260x PMICs
 *
 * Copyright (C) 2019 Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>
 * Copyright (C) 2020 Cristian Ciocaltea <cristian.ciocaltea@gmail.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/atc260x/core.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>

#घोषणा ATC260X_CHIP_REV_MAX	31

काष्ठा atc260x_init_regs अणु
	अचिन्हित पूर्णांक cmu_devrst;
	अचिन्हित पूर्णांक cmu_devrst_पूर्णांकs;
	अचिन्हित पूर्णांक पूर्णांकs_msk;
	अचिन्हित पूर्णांक pad_en;
	अचिन्हित पूर्णांक pad_en_extirq;
पूर्ण;

अटल व्योम regmap_lock_mutex(व्योम *__mutex)
अणु
	काष्ठा mutex *mutex = __mutex;

	/*
	 * Using regmap within an atomic context (e.g. accessing a PMIC when
	 * घातering प्रणाली करोwn) is normally allowed only अगर the regmap type
	 * is MMIO and the regcache type is either REGCACHE_NONE or
	 * REGCACHE_FLAT. For slow buses like I2C and SPI, the regmap is
	 * पूर्णांकernally रक्षित by a mutex which is acquired non-atomically.
	 *
	 * Let's improve this by using a customized locking scheme inspired
	 * from I2C atomic transfer. See i2c_in_atomic_xfer_mode() क्रम a
	 * starting poपूर्णांक.
	 */
	अगर (प्रणाली_state > SYSTEM_RUNNING && irqs_disabled())
		mutex_trylock(mutex);
	अन्यथा
		mutex_lock(mutex);
पूर्ण

अटल व्योम regmap_unlock_mutex(व्योम *__mutex)
अणु
	काष्ठा mutex *mutex = __mutex;

	mutex_unlock(mutex);
पूर्ण

अटल स्थिर काष्ठा regmap_config atc2603c_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.max_रेजिस्टर = ATC2603C_SADDR,
	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल स्थिर काष्ठा regmap_config atc2609a_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.max_रेजिस्टर = ATC2609A_SADDR,
	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq atc2603c_regmap_irqs[] = अणु
	REGMAP_IRQ_REG(ATC2603C_IRQ_AUDIO,	0, ATC2603C_INTS_MSK_AUDIO),
	REGMAP_IRQ_REG(ATC2603C_IRQ_OV,		0, ATC2603C_INTS_MSK_OV),
	REGMAP_IRQ_REG(ATC2603C_IRQ_OC,		0, ATC2603C_INTS_MSK_OC),
	REGMAP_IRQ_REG(ATC2603C_IRQ_OT,		0, ATC2603C_INTS_MSK_OT),
	REGMAP_IRQ_REG(ATC2603C_IRQ_UV,		0, ATC2603C_INTS_MSK_UV),
	REGMAP_IRQ_REG(ATC2603C_IRQ_ALARM,	0, ATC2603C_INTS_MSK_ALARM),
	REGMAP_IRQ_REG(ATC2603C_IRQ_ONOFF,	0, ATC2603C_INTS_MSK_ONOFF),
	REGMAP_IRQ_REG(ATC2603C_IRQ_SGPIO,	0, ATC2603C_INTS_MSK_SGPIO),
	REGMAP_IRQ_REG(ATC2603C_IRQ_IR,		0, ATC2603C_INTS_MSK_IR),
	REGMAP_IRQ_REG(ATC2603C_IRQ_REMCON,	0, ATC2603C_INTS_MSK_REMCON),
	REGMAP_IRQ_REG(ATC2603C_IRQ_POWER_IN,	0, ATC2603C_INTS_MSK_POWERIN),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq atc2609a_regmap_irqs[] = अणु
	REGMAP_IRQ_REG(ATC2609A_IRQ_AUDIO,	0, ATC2609A_INTS_MSK_AUDIO),
	REGMAP_IRQ_REG(ATC2609A_IRQ_OV,		0, ATC2609A_INTS_MSK_OV),
	REGMAP_IRQ_REG(ATC2609A_IRQ_OC,		0, ATC2609A_INTS_MSK_OC),
	REGMAP_IRQ_REG(ATC2609A_IRQ_OT,		0, ATC2609A_INTS_MSK_OT),
	REGMAP_IRQ_REG(ATC2609A_IRQ_UV,		0, ATC2609A_INTS_MSK_UV),
	REGMAP_IRQ_REG(ATC2609A_IRQ_ALARM,	0, ATC2609A_INTS_MSK_ALARM),
	REGMAP_IRQ_REG(ATC2609A_IRQ_ONOFF,	0, ATC2609A_INTS_MSK_ONOFF),
	REGMAP_IRQ_REG(ATC2609A_IRQ_WKUP,	0, ATC2609A_INTS_MSK_WKUP),
	REGMAP_IRQ_REG(ATC2609A_IRQ_IR,		0, ATC2609A_INTS_MSK_IR),
	REGMAP_IRQ_REG(ATC2609A_IRQ_REMCON,	0, ATC2609A_INTS_MSK_REMCON),
	REGMAP_IRQ_REG(ATC2609A_IRQ_POWER_IN,	0, ATC2609A_INTS_MSK_POWERIN),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip atc2603c_regmap_irq_chip = अणु
	.name = "atc2603c",
	.irqs = atc2603c_regmap_irqs,
	.num_irqs = ARRAY_SIZE(atc2603c_regmap_irqs),
	.num_regs = 1,
	.status_base = ATC2603C_INTS_PD,
	.mask_base = ATC2603C_INTS_MSK,
	.mask_invert = true,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip atc2609a_regmap_irq_chip = अणु
	.name = "atc2609a",
	.irqs = atc2609a_regmap_irqs,
	.num_irqs = ARRAY_SIZE(atc2609a_regmap_irqs),
	.num_regs = 1,
	.status_base = ATC2609A_INTS_PD,
	.mask_base = ATC2609A_INTS_MSK,
	.mask_invert = true,
पूर्ण;

अटल स्थिर काष्ठा resource atc2603c_onkey_resources[] = अणु
	DEFINE_RES_IRQ(ATC2603C_IRQ_ONOFF),
पूर्ण;

अटल स्थिर काष्ठा resource atc2609a_onkey_resources[] = अणु
	DEFINE_RES_IRQ(ATC2609A_IRQ_ONOFF),
पूर्ण;

अटल स्थिर काष्ठा mfd_cell atc2603c_mfd_cells[] = अणु
	अणु .name = "atc260x-regulator" पूर्ण,
	अणु .name = "atc260x-pwrc" पूर्ण,
	अणु
		.name = "atc260x-onkey",
		.num_resources = ARRAY_SIZE(atc2603c_onkey_resources),
		.resources = atc2603c_onkey_resources,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell atc2609a_mfd_cells[] = अणु
	अणु .name = "atc260x-regulator" पूर्ण,
	अणु .name = "atc260x-pwrc" पूर्ण,
	अणु
		.name = "atc260x-onkey",
		.num_resources = ARRAY_SIZE(atc2609a_onkey_resources),
		.resources = atc2609a_onkey_resources,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा atc260x_init_regs atc2603c_init_regs = अणु
	.cmu_devrst = ATC2603C_CMU_DEVRST,
	.cmu_devrst_पूर्णांकs = ATC2603C_CMU_DEVRST_INTS,
	.पूर्णांकs_msk = ATC2603C_INTS_MSK,
	.pad_en = ATC2603C_PAD_EN,
	.pad_en_extirq = ATC2603C_PAD_EN_EXTIRQ,
पूर्ण;

अटल स्थिर काष्ठा atc260x_init_regs atc2609a_init_regs = अणु
	.cmu_devrst = ATC2609A_CMU_DEVRST,
	.cmu_devrst_पूर्णांकs = ATC2609A_CMU_DEVRST_INTS,
	.पूर्णांकs_msk = ATC2609A_INTS_MSK,
	.pad_en = ATC2609A_PAD_EN,
	.pad_en_extirq = ATC2609A_PAD_EN_EXTIRQ,
पूर्ण;

अटल व्योम atc260x_cmu_reset(काष्ठा atc260x *atc260x)
अणु
	स्थिर काष्ठा atc260x_init_regs *regs = atc260x->init_regs;

	/* Assert reset */
	regmap_update_bits(atc260x->regmap, regs->cmu_devrst,
			   regs->cmu_devrst_पूर्णांकs, ~regs->cmu_devrst_पूर्णांकs);

	/* De-निश्चित reset */
	regmap_update_bits(atc260x->regmap, regs->cmu_devrst,
			   regs->cmu_devrst_पूर्णांकs, regs->cmu_devrst_पूर्णांकs);
पूर्ण

अटल व्योम atc260x_dev_init(काष्ठा atc260x *atc260x)
अणु
	स्थिर काष्ठा atc260x_init_regs *regs = atc260x->init_regs;

	/* Initialize पूर्णांकerrupt block */
	atc260x_cmu_reset(atc260x);

	/* Disable all पूर्णांकerrupt sources */
	regmap_ग_लिखो(atc260x->regmap, regs->पूर्णांकs_msk, 0);

	/* Enable EXTIRQ pad */
	regmap_update_bits(atc260x->regmap, regs->pad_en,
			   regs->pad_en_extirq, regs->pad_en_extirq);
पूर्ण

/**
 * atc260x_match_device(): Setup ATC260x variant related fields
 *
 * @atc260x: ATC260x device to setup (.dev field must be set)
 * @regmap_cfg: regmap config associated with this ATC260x device
 *
 * This lets the ATC260x core configure the MFD cells and रेजिस्टर maps
 * क्रम later use.
 */
पूर्णांक atc260x_match_device(काष्ठा atc260x *atc260x, काष्ठा regmap_config *regmap_cfg)
अणु
	काष्ठा device *dev = atc260x->dev;
	स्थिर व्योम *of_data;

	of_data = of_device_get_match_data(dev);
	अगर (!of_data)
		वापस -ENODEV;

	atc260x->ic_type = (अचिन्हित दीर्घ)of_data;

	चयन (atc260x->ic_type) अणु
	हाल ATC2603C:
		*regmap_cfg = atc2603c_regmap_config;
		atc260x->regmap_irq_chip = &atc2603c_regmap_irq_chip;
		atc260x->cells = atc2603c_mfd_cells;
		atc260x->nr_cells = ARRAY_SIZE(atc2603c_mfd_cells);
		atc260x->type_name = "atc2603c";
		atc260x->rev_reg = ATC2603C_CHIP_VER;
		atc260x->init_regs = &atc2603c_init_regs;
		अवरोध;
	हाल ATC2609A:
		*regmap_cfg = atc2609a_regmap_config;
		atc260x->regmap_irq_chip = &atc2609a_regmap_irq_chip;
		atc260x->cells = atc2609a_mfd_cells;
		atc260x->nr_cells = ARRAY_SIZE(atc2609a_mfd_cells);
		atc260x->type_name = "atc2609a";
		atc260x->rev_reg = ATC2609A_CHIP_VER;
		atc260x->init_regs = &atc2609a_init_regs;
		अवरोध;
	शेष:
		dev_err(dev, "Unsupported ATC260x device type: %u\n",
			atc260x->ic_type);
		वापस -EINVAL;
	पूर्ण

	atc260x->regmap_mutex = devm_kzalloc(dev, माप(*atc260x->regmap_mutex),
					     GFP_KERNEL);
	अगर (!atc260x->regmap_mutex)
		वापस -ENOMEM;

	mutex_init(atc260x->regmap_mutex);

	regmap_cfg->lock = regmap_lock_mutex,
	regmap_cfg->unlock = regmap_unlock_mutex,
	regmap_cfg->lock_arg = atc260x->regmap_mutex;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(atc260x_match_device);

/**
 * atc260x_device_probe(): Probe a configured ATC260x device
 *
 * @atc260x: ATC260x device to probe (must be configured)
 *
 * This function lets the ATC260x core रेजिस्टर the ATC260x MFD devices
 * and IRQCHIP. The ATC260x device passed in must be fully configured
 * with atc260x_match_device, its IRQ set, and regmap created.
 */
पूर्णांक atc260x_device_probe(काष्ठा atc260x *atc260x)
अणु
	काष्ठा device *dev = atc260x->dev;
	अचिन्हित पूर्णांक chip_rev;
	पूर्णांक ret;

	अगर (!atc260x->irq) अणु
		dev_err(dev, "No interrupt support\n");
		वापस -EINVAL;
	पूर्ण

	/* Initialize the hardware */
	atc260x_dev_init(atc260x);

	ret = regmap_पढ़ो(atc260x->regmap, atc260x->rev_reg, &chip_rev);
	अगर (ret) अणु
		dev_err(dev, "Failed to get chip revision\n");
		वापस ret;
	पूर्ण

	अगर (chip_rev > ATC260X_CHIP_REV_MAX) अणु
		dev_err(dev, "Unknown chip revision: %u\n", chip_rev);
		वापस -EINVAL;
	पूर्ण

	atc260x->ic_ver = __ffs(chip_rev + 1U);

	dev_info(dev, "Detected chip type %s rev.%c\n",
		 atc260x->type_name, 'A' + atc260x->ic_ver);

	ret = devm_regmap_add_irq_chip(dev, atc260x->regmap, atc260x->irq, IRQF_ONESHOT,
				       -1, atc260x->regmap_irq_chip, &atc260x->irq_data);
	अगर (ret) अणु
		dev_err(dev, "Failed to add IRQ chip: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_mfd_add_devices(dev, PLATFORM_DEVID_NONE,
				   atc260x->cells, atc260x->nr_cells, शून्य, 0,
				   regmap_irq_get_करोमुख्य(atc260x->irq_data));
	अगर (ret) अणु
		dev_err(dev, "Failed to add child devices: %d\n", ret);
		regmap_del_irq_chip(atc260x->irq, atc260x->irq_data);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(atc260x_device_probe);

MODULE_DESCRIPTION("ATC260x PMICs Core support");
MODULE_AUTHOR("Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>");
MODULE_AUTHOR("Cristian Ciocaltea <cristian.ciocaltea@gmail.com>");
MODULE_LICENSE("GPL");
