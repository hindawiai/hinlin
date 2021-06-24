<शैली गुरु>
/*
 * Retu/Tahvo MFD driver
 *
 * Copyright (C) 2004, 2005 Nokia Corporation
 *
 * Based on code written by Juha Yrjथघlथअ, David Weinehall and Mikko Ylinen.
 * Rewritten by Aaro Koskinen.
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file "COPYING" in the मुख्य directory of this
 * archive क्रम more details.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/retu.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/moduleparam.h>

/* Registers */
#घोषणा RETU_REG_ASICR		0x00		/* ASIC ID and revision */
#घोषणा RETU_REG_ASICR_VILMA	(1 << 7)	/* Bit indicating Vilma */
#घोषणा RETU_REG_IDR		0x01		/* Interrupt ID */
#घोषणा RETU_REG_IMR		0x02		/* Interrupt mask (Retu) */
#घोषणा TAHVO_REG_IMR		0x03		/* Interrupt mask (Tahvo) */

/* Interrupt sources */
#घोषणा RETU_INT_PWR		0		/* Power button */

काष्ठा retu_dev अणु
	काष्ठा regmap			*regmap;
	काष्ठा device			*dev;
	काष्ठा mutex			mutex;
	काष्ठा regmap_irq_chip_data	*irq_data;
पूर्ण;

अटल स्थिर काष्ठा resource retu_pwrbutton_res[] = अणु
	अणु
		.name	= "retu-pwrbutton",
		.start	= RETU_INT_PWR,
		.end	= RETU_INT_PWR,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell retu_devs[] = अणु
	अणु
		.name		= "retu-wdt"
	पूर्ण,
	अणु
		.name		= "retu-pwrbutton",
		.resources	= retu_pwrbutton_res,
		.num_resources	= ARRAY_SIZE(retu_pwrbutton_res),
	पूर्ण
पूर्ण;

अटल काष्ठा regmap_irq retu_irqs[] = अणु
	[RETU_INT_PWR] = अणु
		.mask = 1 << RETU_INT_PWR,
	पूर्ण
पूर्ण;

अटल काष्ठा regmap_irq_chip retu_irq_chip = अणु
	.name		= "RETU",
	.irqs		= retu_irqs,
	.num_irqs	= ARRAY_SIZE(retu_irqs),
	.num_regs	= 1,
	.status_base	= RETU_REG_IDR,
	.mask_base	= RETU_REG_IMR,
	.ack_base	= RETU_REG_IDR,
पूर्ण;

/* Retu device रेजिस्टरed क्रम the घातer off. */
अटल काष्ठा retu_dev *retu_pm_घातer_off;

अटल स्थिर काष्ठा resource tahvo_usb_res[] = अणु
	अणु
		.name	= "tahvo-usb",
		.start	= TAHVO_INT_VBUS,
		.end	= TAHVO_INT_VBUS,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell tahvo_devs[] = अणु
	अणु
		.name		= "tahvo-usb",
		.resources	= tahvo_usb_res,
		.num_resources	= ARRAY_SIZE(tahvo_usb_res),
	पूर्ण,
पूर्ण;

अटल काष्ठा regmap_irq tahvo_irqs[] = अणु
	[TAHVO_INT_VBUS] = अणु
		.mask = 1 << TAHVO_INT_VBUS,
	पूर्ण
पूर्ण;

अटल काष्ठा regmap_irq_chip tahvo_irq_chip = अणु
	.name		= "TAHVO",
	.irqs		= tahvo_irqs,
	.num_irqs	= ARRAY_SIZE(tahvo_irqs),
	.num_regs	= 1,
	.status_base	= RETU_REG_IDR,
	.mask_base	= TAHVO_REG_IMR,
	.ack_base	= RETU_REG_IDR,
पूर्ण;

अटल स्थिर काष्ठा retu_data अणु
	अक्षर			*chip_name;
	अक्षर			*companion_name;
	काष्ठा regmap_irq_chip	*irq_chip;
	स्थिर काष्ठा mfd_cell	*children;
	पूर्णांक			nchildren;
पूर्ण retu_data[] = अणु
	[0] = अणु
		.chip_name	= "Retu",
		.companion_name	= "Vilma",
		.irq_chip	= &retu_irq_chip,
		.children	= retu_devs,
		.nchildren	= ARRAY_SIZE(retu_devs),
	पूर्ण,
	[1] = अणु
		.chip_name	= "Tahvo",
		.companion_name	= "Betty",
		.irq_chip	= &tahvo_irq_chip,
		.children	= tahvo_devs,
		.nchildren	= ARRAY_SIZE(tahvo_devs),
	पूर्ण
पूर्ण;

पूर्णांक retu_पढ़ो(काष्ठा retu_dev *rdev, u8 reg)
अणु
	पूर्णांक ret;
	पूर्णांक value;

	mutex_lock(&rdev->mutex);
	ret = regmap_पढ़ो(rdev->regmap, reg, &value);
	mutex_unlock(&rdev->mutex);

	वापस ret ? ret : value;
पूर्ण
EXPORT_SYMBOL_GPL(retu_पढ़ो);

पूर्णांक retu_ग_लिखो(काष्ठा retu_dev *rdev, u8 reg, u16 data)
अणु
	पूर्णांक ret;

	mutex_lock(&rdev->mutex);
	ret = regmap_ग_लिखो(rdev->regmap, reg, data);
	mutex_unlock(&rdev->mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(retu_ग_लिखो);

अटल व्योम retu_घातer_off(व्योम)
अणु
	काष्ठा retu_dev *rdev = retu_pm_घातer_off;
	पूर्णांक reg;

	mutex_lock(&retu_pm_घातer_off->mutex);

	/* Ignore घातer button state */
	regmap_पढ़ो(rdev->regmap, RETU_REG_CC1, &reg);
	regmap_ग_लिखो(rdev->regmap, RETU_REG_CC1, reg | 2);

	/* Expire watchकरोg immediately */
	regmap_ग_लिखो(rdev->regmap, RETU_REG_WATCHDOG, 0);

	/* Wait क्रम घातeroff */
	क्रम (;;)
		cpu_relax();

	mutex_unlock(&retu_pm_घातer_off->mutex);
पूर्ण

अटल पूर्णांक retu_regmap_पढ़ो(व्योम *context, स्थिर व्योम *reg, माप_प्रकार reg_size,
			    व्योम *val, माप_प्रकार val_size)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = context;
	काष्ठा i2c_client *i2c = to_i2c_client(dev);

	BUG_ON(reg_size != 1 || val_size != 2);

	ret = i2c_smbus_पढ़ो_word_data(i2c, *(u8 स्थिर *)reg);
	अगर (ret < 0)
		वापस ret;

	*(u16 *)val = ret;
	वापस 0;
पूर्ण

अटल पूर्णांक retu_regmap_ग_लिखो(व्योम *context, स्थिर व्योम *data, माप_प्रकार count)
अणु
	u8 reg;
	u16 val;
	काष्ठा device *dev = context;
	काष्ठा i2c_client *i2c = to_i2c_client(dev);

	BUG_ON(count != माप(reg) + माप(val));
	स_नकल(&reg, data, माप(reg));
	स_नकल(&val, data + माप(reg), माप(val));
	वापस i2c_smbus_ग_लिखो_word_data(i2c, reg, val);
पूर्ण

अटल काष्ठा regmap_bus retu_bus = अणु
	.पढ़ो = retu_regmap_पढ़ो,
	.ग_लिखो = retu_regmap_ग_लिखो,
	.val_क्रमmat_endian_शेष = REGMAP_ENDIAN_NATIVE,
पूर्ण;

अटल स्थिर काष्ठा regmap_config retu_config = अणु
	.reg_bits = 8,
	.val_bits = 16,
पूर्ण;

अटल पूर्णांक retu_probe(काष्ठा i2c_client *i2c, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा retu_data स्थिर *rdat;
	काष्ठा retu_dev *rdev;
	पूर्णांक ret;

	अगर (i2c->addr > ARRAY_SIZE(retu_data))
		वापस -ENODEV;
	rdat = &retu_data[i2c->addr - 1];

	rdev = devm_kzalloc(&i2c->dev, माप(*rdev), GFP_KERNEL);
	अगर (rdev == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, rdev);
	rdev->dev = &i2c->dev;
	mutex_init(&rdev->mutex);
	rdev->regmap = devm_regmap_init(&i2c->dev, &retu_bus, &i2c->dev,
					&retu_config);
	अगर (IS_ERR(rdev->regmap))
		वापस PTR_ERR(rdev->regmap);

	ret = retu_पढ़ो(rdev, RETU_REG_ASICR);
	अगर (ret < 0) अणु
		dev_err(rdev->dev, "could not read %s revision: %d\n",
			rdat->chip_name, ret);
		वापस ret;
	पूर्ण

	dev_info(rdev->dev, "%s%s%s v%d.%d found\n", rdat->chip_name,
		 (ret & RETU_REG_ASICR_VILMA) ? " & " : "",
		 (ret & RETU_REG_ASICR_VILMA) ? rdat->companion_name : "",
		 (ret >> 4) & 0x7, ret & 0xf);

	/* Mask all पूर्णांकerrupts. */
	ret = retu_ग_लिखो(rdev, rdat->irq_chip->mask_base, 0xffff);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_add_irq_chip(rdev->regmap, i2c->irq, IRQF_ONESHOT, -1,
				  rdat->irq_chip, &rdev->irq_data);
	अगर (ret < 0)
		वापस ret;

	ret = mfd_add_devices(rdev->dev, -1, rdat->children, rdat->nchildren,
			      शून्य, regmap_irq_chip_get_base(rdev->irq_data),
			      शून्य);
	अगर (ret < 0) अणु
		regmap_del_irq_chip(i2c->irq, rdev->irq_data);
		वापस ret;
	पूर्ण

	अगर (i2c->addr == 1 && !pm_घातer_off) अणु
		retu_pm_घातer_off = rdev;
		pm_घातer_off	  = retu_घातer_off;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक retu_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा retu_dev *rdev = i2c_get_clientdata(i2c);

	अगर (retu_pm_घातer_off == rdev) अणु
		pm_घातer_off	  = शून्य;
		retu_pm_घातer_off = शून्य;
	पूर्ण
	mfd_हटाओ_devices(rdev->dev);
	regmap_del_irq_chip(i2c->irq, rdev->irq_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id retu_id[] = अणु
	अणु "retu", 0 पूर्ण,
	अणु "tahvo", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, retu_id);

अटल स्थिर काष्ठा of_device_id retu_of_match[] = अणु
	अणु .compatible = "nokia,retu" पूर्ण,
	अणु .compatible = "nokia,tahvo" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, retu_of_match);

अटल काष्ठा i2c_driver retu_driver = अणु
	.driver		= अणु
		.name = "retu-mfd",
		.of_match_table = retu_of_match,
	पूर्ण,
	.probe		= retu_probe,
	.हटाओ		= retu_हटाओ,
	.id_table	= retu_id,
पूर्ण;
module_i2c_driver(retu_driver);

MODULE_DESCRIPTION("Retu MFD driver");
MODULE_AUTHOR("Juha Yrjथघlथअ");
MODULE_AUTHOR("David Weinehall");
MODULE_AUTHOR("Mikko Ylinen");
MODULE_AUTHOR("Aaro Koskinen <aaro.koskinen@iki.fi>");
MODULE_LICENSE("GPL");
