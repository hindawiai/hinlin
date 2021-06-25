<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI LP8788 MFD - core पूर्णांकerface
 *
 * Copyright 2012 Texas Instruments
 *
 * Author: Milo(Woogyom) Kim <milo.kim@ti.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/lp8788.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#घोषणा MAX_LP8788_REGISTERS		0xA2

#घोषणा MFD_DEV_SIMPLE(_name)					\
अणु								\
	.name = LP8788_DEV_##_name,				\
पूर्ण

#घोषणा MFD_DEV_WITH_ID(_name, _id)				\
अणु								\
	.name = LP8788_DEV_##_name,				\
	.id = _id,						\
पूर्ण

#घोषणा MFD_DEV_WITH_RESOURCE(_name, _resource, num_resource)	\
अणु								\
	.name = LP8788_DEV_##_name,				\
	.resources = _resource,					\
	.num_resources = num_resource,				\
पूर्ण

अटल स्थिर काष्ठा resource chg_irqs[] = अणु
	/* Charger Interrupts */
	अणु
		.start = LP8788_INT_CHG_INPUT_STATE,
		.end   = LP8788_INT_PRECHG_TIMEOUT,
		.name  = LP8788_CHG_IRQ,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	/* Power Routing Switch Interrupts */
	अणु
		.start = LP8788_INT_ENTER_SYS_SUPPORT,
		.end   = LP8788_INT_EXIT_SYS_SUPPORT,
		.name  = LP8788_PRSW_IRQ,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	/* Battery Interrupts */
	अणु
		.start = LP8788_INT_BATT_LOW,
		.end   = LP8788_INT_NO_BATT,
		.name  = LP8788_BATT_IRQ,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource rtc_irqs[] = अणु
	अणु
		.start = LP8788_INT_RTC_ALARM1,
		.end   = LP8788_INT_RTC_ALARM2,
		.name  = LP8788_ALM_IRQ,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell lp8788_devs[] = अणु
	/* 4 bucks */
	MFD_DEV_WITH_ID(BUCK, 1),
	MFD_DEV_WITH_ID(BUCK, 2),
	MFD_DEV_WITH_ID(BUCK, 3),
	MFD_DEV_WITH_ID(BUCK, 4),

	/* 12 digital lकरोs */
	MFD_DEV_WITH_ID(DLDO, 1),
	MFD_DEV_WITH_ID(DLDO, 2),
	MFD_DEV_WITH_ID(DLDO, 3),
	MFD_DEV_WITH_ID(DLDO, 4),
	MFD_DEV_WITH_ID(DLDO, 5),
	MFD_DEV_WITH_ID(DLDO, 6),
	MFD_DEV_WITH_ID(DLDO, 7),
	MFD_DEV_WITH_ID(DLDO, 8),
	MFD_DEV_WITH_ID(DLDO, 9),
	MFD_DEV_WITH_ID(DLDO, 10),
	MFD_DEV_WITH_ID(DLDO, 11),
	MFD_DEV_WITH_ID(DLDO, 12),

	/* 10 analog lकरोs */
	MFD_DEV_WITH_ID(ALDO, 1),
	MFD_DEV_WITH_ID(ALDO, 2),
	MFD_DEV_WITH_ID(ALDO, 3),
	MFD_DEV_WITH_ID(ALDO, 4),
	MFD_DEV_WITH_ID(ALDO, 5),
	MFD_DEV_WITH_ID(ALDO, 6),
	MFD_DEV_WITH_ID(ALDO, 7),
	MFD_DEV_WITH_ID(ALDO, 8),
	MFD_DEV_WITH_ID(ALDO, 9),
	MFD_DEV_WITH_ID(ALDO, 10),

	/* ADC */
	MFD_DEV_SIMPLE(ADC),

	/* battery अक्षरger */
	MFD_DEV_WITH_RESOURCE(CHARGER, chg_irqs, ARRAY_SIZE(chg_irqs)),

	/* rtc */
	MFD_DEV_WITH_RESOURCE(RTC, rtc_irqs, ARRAY_SIZE(rtc_irqs)),

	/* backlight */
	MFD_DEV_SIMPLE(BACKLIGHT),

	/* current sink क्रम vibrator */
	MFD_DEV_SIMPLE(VIBRATOR),

	/* current sink क्रम keypad LED */
	MFD_DEV_SIMPLE(KEYLED),
पूर्ण;

पूर्णांक lp8788_पढ़ो_byte(काष्ठा lp8788 *lp, u8 reg, u8 *data)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(lp->regmap, reg, &val);
	अगर (ret < 0) अणु
		dev_err(lp->dev, "failed to read 0x%.2x\n", reg);
		वापस ret;
	पूर्ण

	*data = (u8)val;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(lp8788_पढ़ो_byte);

पूर्णांक lp8788_पढ़ो_multi_bytes(काष्ठा lp8788 *lp, u8 reg, u8 *data, माप_प्रकार count)
अणु
	वापस regmap_bulk_पढ़ो(lp->regmap, reg, data, count);
पूर्ण
EXPORT_SYMBOL_GPL(lp8788_पढ़ो_multi_bytes);

पूर्णांक lp8788_ग_लिखो_byte(काष्ठा lp8788 *lp, u8 reg, u8 data)
अणु
	वापस regmap_ग_लिखो(lp->regmap, reg, data);
पूर्ण
EXPORT_SYMBOL_GPL(lp8788_ग_लिखो_byte);

पूर्णांक lp8788_update_bits(काष्ठा lp8788 *lp, u8 reg, u8 mask, u8 data)
अणु
	वापस regmap_update_bits(lp->regmap, reg, mask, data);
पूर्ण
EXPORT_SYMBOL_GPL(lp8788_update_bits);

अटल पूर्णांक lp8788_platक्रमm_init(काष्ठा lp8788 *lp)
अणु
	काष्ठा lp8788_platक्रमm_data *pdata = lp->pdata;

	वापस (pdata && pdata->init_func) ? pdata->init_func(lp) : 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config lp8788_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = MAX_LP8788_REGISTERS,
पूर्ण;

अटल पूर्णांक lp8788_probe(काष्ठा i2c_client *cl, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा lp8788 *lp;
	काष्ठा lp8788_platक्रमm_data *pdata = dev_get_platdata(&cl->dev);
	पूर्णांक ret;

	lp = devm_kzalloc(&cl->dev, माप(काष्ठा lp8788), GFP_KERNEL);
	अगर (!lp)
		वापस -ENOMEM;

	lp->regmap = devm_regmap_init_i2c(cl, &lp8788_regmap_config);
	अगर (IS_ERR(lp->regmap)) अणु
		ret = PTR_ERR(lp->regmap);
		dev_err(&cl->dev, "regmap init i2c err: %d\n", ret);
		वापस ret;
	पूर्ण

	lp->pdata = pdata;
	lp->dev = &cl->dev;
	i2c_set_clientdata(cl, lp);

	ret = lp8788_platक्रमm_init(lp);
	अगर (ret)
		वापस ret;

	ret = lp8788_irq_init(lp, cl->irq);
	अगर (ret)
		वापस ret;

	वापस mfd_add_devices(lp->dev, -1, lp8788_devs,
			       ARRAY_SIZE(lp8788_devs), शून्य, 0, शून्य);
पूर्ण

अटल पूर्णांक lp8788_हटाओ(काष्ठा i2c_client *cl)
अणु
	काष्ठा lp8788 *lp = i2c_get_clientdata(cl);

	mfd_हटाओ_devices(lp->dev);
	lp8788_irq_निकास(lp);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lp8788_ids[] = अणु
	अणु"lp8788", 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lp8788_ids);

अटल काष्ठा i2c_driver lp8788_driver = अणु
	.driver = अणु
		.name = "lp8788",
	पूर्ण,
	.probe = lp8788_probe,
	.हटाओ = lp8788_हटाओ,
	.id_table = lp8788_ids,
पूर्ण;

अटल पूर्णांक __init lp8788_init(व्योम)
अणु
	वापस i2c_add_driver(&lp8788_driver);
पूर्ण
subsys_initcall(lp8788_init);

अटल व्योम __निकास lp8788_निकास(व्योम)
अणु
	i2c_del_driver(&lp8788_driver);
पूर्ण
module_निकास(lp8788_निकास);

MODULE_DESCRIPTION("TI LP8788 MFD Driver");
MODULE_AUTHOR("Milo Kim");
MODULE_LICENSE("GPL");
