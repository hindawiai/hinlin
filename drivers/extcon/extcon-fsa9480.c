<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * extcon-fsa9480.c - Fairchild Semiconductor FSA9480 extcon driver
 *
 * Copyright (c) 2019 Tomasz Figa <tomasz.figa@gmail.com>
 *
 * Loosely based on old fsa9480 misc-device driver.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kobject.h>
#समावेश <linux/extcon-provider.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/regmap.h>

/* FSA9480 I2C रेजिस्टरs */
#घोषणा FSA9480_REG_DEVID               0x01
#घोषणा FSA9480_REG_CTRL                0x02
#घोषणा FSA9480_REG_INT1                0x03
#घोषणा FSA9480_REG_INT2                0x04
#घोषणा FSA9480_REG_INT1_MASK           0x05
#घोषणा FSA9480_REG_INT2_MASK           0x06
#घोषणा FSA9480_REG_ADC                 0x07
#घोषणा FSA9480_REG_TIMING1             0x08
#घोषणा FSA9480_REG_TIMING2             0x09
#घोषणा FSA9480_REG_DEV_T1              0x0a
#घोषणा FSA9480_REG_DEV_T2              0x0b
#घोषणा FSA9480_REG_BTN1                0x0c
#घोषणा FSA9480_REG_BTN2                0x0d
#घोषणा FSA9480_REG_CK                  0x0e
#घोषणा FSA9480_REG_CK_INT1             0x0f
#घोषणा FSA9480_REG_CK_INT2             0x10
#घोषणा FSA9480_REG_CK_INTMASK1         0x11
#घोषणा FSA9480_REG_CK_INTMASK2         0x12
#घोषणा FSA9480_REG_MANSW1              0x13
#घोषणा FSA9480_REG_MANSW2              0x14
#घोषणा FSA9480_REG_END                 0x15

/* Control */
#घोषणा CON_SWITCH_OPEN         (1 << 4)
#घोषणा CON_RAW_DATA            (1 << 3)
#घोषणा CON_MANUAL_SW           (1 << 2)
#घोषणा CON_WAIT                (1 << 1)
#घोषणा CON_INT_MASK            (1 << 0)
#घोषणा CON_MASK                (CON_SWITCH_OPEN | CON_RAW_DATA | \
				 CON_MANUAL_SW | CON_WAIT)

/* Device Type 1 */
#घोषणा DEV_USB_OTG             7
#घोषणा DEV_DEDICATED_CHG       6
#घोषणा DEV_USB_CHG             5
#घोषणा DEV_CAR_KIT             4
#घोषणा DEV_UART                3
#घोषणा DEV_USB                 2
#घोषणा DEV_AUDIO_2             1
#घोषणा DEV_AUDIO_1             0

#घोषणा DEV_T1_USB_MASK         (DEV_USB_OTG | DEV_USB)
#घोषणा DEV_T1_UART_MASK        (DEV_UART)
#घोषणा DEV_T1_CHARGER_MASK     (DEV_DEDICATED_CHG | DEV_USB_CHG)

/* Device Type 2 */
#घोषणा DEV_AV                  14
#घोषणा DEV_TTY                 13
#घोषणा DEV_PPD                 12
#घोषणा DEV_JIG_UART_OFF        11
#घोषणा DEV_JIG_UART_ON         10
#घोषणा DEV_JIG_USB_OFF         9
#घोषणा DEV_JIG_USB_ON          8

#घोषणा DEV_T2_USB_MASK         (DEV_JIG_USB_OFF | DEV_JIG_USB_ON)
#घोषणा DEV_T2_UART_MASK        (DEV_JIG_UART_OFF | DEV_JIG_UART_ON)
#घोषणा DEV_T2_JIG_MASK         (DEV_JIG_USB_OFF | DEV_JIG_USB_ON | \
				 DEV_JIG_UART_OFF | DEV_JIG_UART_ON)

/*
 * Manual Switch
 * D- [7:5] / D+ [4:2]
 * 000: Open all / 001: USB / 010: AUDIO / 011: UART / 100: V_AUDIO
 */
#घोषणा SW_VAUDIO               ((4 << 5) | (4 << 2))
#घोषणा SW_UART                 ((3 << 5) | (3 << 2))
#घोषणा SW_AUDIO                ((2 << 5) | (2 << 2))
#घोषणा SW_DHOST                ((1 << 5) | (1 << 2))
#घोषणा SW_AUTO                 ((0 << 5) | (0 << 2))

/* Interrupt 1 */
#घोषणा INT1_MASK               (0xff << 0)
#घोषणा INT_DETACH              (1 << 1)
#घोषणा INT_ATTACH              (1 << 0)

/* Interrupt 2 mask */
#घोषणा INT2_MASK               (0x1f << 0)

/* Timing Set 1 */
#घोषणा TIMING1_ADC_500MS       (0x6 << 0)

काष्ठा fsa9480_usbsw अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा extcon_dev *edev;
	u16 cable;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक fsa9480_extcon_cable[] = अणु
	EXTCON_USB_HOST,
	EXTCON_USB,
	EXTCON_CHG_USB_DCP,
	EXTCON_CHG_USB_SDP,
	EXTCON_CHG_USB_ACA,
	EXTCON_JACK_LINE_OUT,
	EXTCON_JACK_VIDEO_OUT,
	EXTCON_JIG,

	EXTCON_NONE,
पूर्ण;

अटल स्थिर u64 cable_types[] = अणु
	[DEV_USB_OTG] = BIT_ULL(EXTCON_USB_HOST),
	[DEV_DEDICATED_CHG] = BIT_ULL(EXTCON_USB) | BIT_ULL(EXTCON_CHG_USB_DCP),
	[DEV_USB_CHG] = BIT_ULL(EXTCON_USB) | BIT_ULL(EXTCON_CHG_USB_SDP),
	[DEV_CAR_KIT] = BIT_ULL(EXTCON_USB) | BIT_ULL(EXTCON_CHG_USB_SDP)
			| BIT_ULL(EXTCON_JACK_LINE_OUT),
	[DEV_UART] = BIT_ULL(EXTCON_JIG),
	[DEV_USB] = BIT_ULL(EXTCON_USB) | BIT_ULL(EXTCON_CHG_USB_SDP),
	[DEV_AUDIO_2] = BIT_ULL(EXTCON_JACK_LINE_OUT),
	[DEV_AUDIO_1] = BIT_ULL(EXTCON_JACK_LINE_OUT),
	[DEV_AV] = BIT_ULL(EXTCON_JACK_LINE_OUT)
		   | BIT_ULL(EXTCON_JACK_VIDEO_OUT),
	[DEV_TTY] = BIT_ULL(EXTCON_JIG),
	[DEV_PPD] = BIT_ULL(EXTCON_JACK_LINE_OUT) | BIT_ULL(EXTCON_CHG_USB_ACA),
	[DEV_JIG_UART_OFF] = BIT_ULL(EXTCON_JIG),
	[DEV_JIG_UART_ON] = BIT_ULL(EXTCON_JIG),
	[DEV_JIG_USB_OFF] = BIT_ULL(EXTCON_USB) | BIT_ULL(EXTCON_JIG),
	[DEV_JIG_USB_ON] = BIT_ULL(EXTCON_USB) | BIT_ULL(EXTCON_JIG),
पूर्ण;

/* Define regmap configuration of FSA9480 क्रम I2C communication  */
अटल bool fsa9480_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल FSA9480_REG_INT1_MASK:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config fsa9480_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.अस्थिर_reg	= fsa9480_अस्थिर_reg,
	.max_रेजिस्टर	= FSA9480_REG_END,
पूर्ण;

अटल पूर्णांक fsa9480_ग_लिखो_reg(काष्ठा fsa9480_usbsw *usbsw, पूर्णांक reg, पूर्णांक value)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(usbsw->regmap, reg, value);
	अगर (ret < 0)
		dev_err(usbsw->dev, "%s: err %d\n", __func__, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक fsa9480_पढ़ो_reg(काष्ठा fsa9480_usbsw *usbsw, पूर्णांक reg)
अणु
	पूर्णांक ret, val;

	ret = regmap_पढ़ो(usbsw->regmap, reg, &val);
	अगर (ret < 0) अणु
		dev_err(usbsw->dev, "%s: err %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक fsa9480_पढ़ो_irq(काष्ठा fsa9480_usbsw *usbsw, पूर्णांक *value)
अणु
	u8 regs[2];
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(usbsw->regmap, FSA9480_REG_INT1, regs, 2);
	अगर (ret < 0)
		dev_err(usbsw->dev, "%s: err %d\n", __func__, ret);

	*value = regs[1] << 8 | regs[0];
	वापस ret;
पूर्ण

अटल व्योम fsa9480_handle_change(काष्ठा fsa9480_usbsw *usbsw,
				  u16 mask, bool attached)
अणु
	जबतक (mask) अणु
		पूर्णांक dev = fls64(mask) - 1;
		u64 cables = cable_types[dev];

		जबतक (cables) अणु
			पूर्णांक cable = fls64(cables) - 1;

			extcon_set_state_sync(usbsw->edev, cable, attached);
			cables &= ~BIT_ULL(cable);
		पूर्ण

		mask &= ~BIT_ULL(dev);
	पूर्ण
पूर्ण

अटल व्योम fsa9480_detect_dev(काष्ठा fsa9480_usbsw *usbsw)
अणु
	पूर्णांक val1, val2;
	u16 val;

	val1 = fsa9480_पढ़ो_reg(usbsw, FSA9480_REG_DEV_T1);
	val2 = fsa9480_पढ़ो_reg(usbsw, FSA9480_REG_DEV_T2);
	अगर (val1 < 0 || val2 < 0) अणु
		dev_err(usbsw->dev, "%s: failed to read registers", __func__);
		वापस;
	पूर्ण
	val = val2 << 8 | val1;

	dev_info(usbsw->dev, "dev1: 0x%x, dev2: 0x%x\n", val1, val2);

	/* handle detached cables first */
	fsa9480_handle_change(usbsw, usbsw->cable & ~val, false);

	/* then handle attached ones */
	fsa9480_handle_change(usbsw, val & ~usbsw->cable, true);

	usbsw->cable = val;
पूर्ण

अटल irqवापस_t fsa9480_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा fsa9480_usbsw *usbsw = data;
	पूर्णांक पूर्णांकr = 0;

	/* clear पूर्णांकerrupt */
	fsa9480_पढ़ो_irq(usbsw, &पूर्णांकr);
	अगर (!पूर्णांकr)
		वापस IRQ_NONE;

	/* device detection */
	fsa9480_detect_dev(usbsw);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक fsa9480_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा fsa9480_usbsw *info;
	पूर्णांक ret;

	अगर (!client->irq) अणु
		dev_err(&client->dev, "no interrupt provided\n");
		वापस -EINVAL;
	पूर्ण

	info = devm_kzalloc(&client->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;
	info->dev = &client->dev;

	i2c_set_clientdata(client, info);

	/* External connector */
	info->edev = devm_extcon_dev_allocate(info->dev,
					      fsa9480_extcon_cable);
	अगर (IS_ERR(info->edev)) अणु
		dev_err(info->dev, "failed to allocate memory for extcon\n");
		ret = -ENOMEM;
		वापस ret;
	पूर्ण

	ret = devm_extcon_dev_रेजिस्टर(info->dev, info->edev);
	अगर (ret) अणु
		dev_err(info->dev, "failed to register extcon device\n");
		वापस ret;
	पूर्ण

	info->regmap = devm_regmap_init_i2c(client, &fsa9480_regmap_config);
	अगर (IS_ERR(info->regmap)) अणु
		ret = PTR_ERR(info->regmap);
		dev_err(info->dev, "failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	/* ADC Detect Time: 500ms */
	fsa9480_ग_लिखो_reg(info, FSA9480_REG_TIMING1, TIMING1_ADC_500MS);

	/* configure स्वतःmatic चयनing */
	fsa9480_ग_लिखो_reg(info, FSA9480_REG_CTRL, CON_MASK);

	/* unmask पूर्णांकerrupt (attach/detach only) */
	fsa9480_ग_लिखो_reg(info, FSA9480_REG_INT1_MASK,
			  INT1_MASK & ~(INT_ATTACH | INT_DETACH));
	fsa9480_ग_लिखो_reg(info, FSA9480_REG_INT2_MASK, INT2_MASK);

	ret = devm_request_thपढ़ोed_irq(info->dev, client->irq, शून्य,
					fsa9480_irq_handler,
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					"fsa9480", info);
	अगर (ret) अणु
		dev_err(info->dev, "failed to request IRQ\n");
		वापस ret;
	पूर्ण

	device_init_wakeup(info->dev, true);
	fsa9480_detect_dev(info);

	वापस 0;
पूर्ण

अटल पूर्णांक fsa9480_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक fsa9480_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	अगर (device_may_wakeup(&client->dev) && client->irq)
		enable_irq_wake(client->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक fsa9480_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	अगर (device_may_wakeup(&client->dev) && client->irq)
		disable_irq_wake(client->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops fsa9480_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(fsa9480_suspend, fsa9480_resume)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id fsa9480_id[] = अणु
	अणु "fsa9480", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, fsa9480_id);

अटल स्थिर काष्ठा of_device_id fsa9480_of_match[] = अणु
	अणु .compatible = "fcs,fsa9480", पूर्ण,
	अणु .compatible = "fcs,fsa880", पूर्ण,
	अणु .compatible = "ti,tsu6111", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, fsa9480_of_match);

अटल काष्ठा i2c_driver fsa9480_i2c_driver = अणु
	.driver			= अणु
		.name		= "fsa9480",
		.pm		= &fsa9480_pm_ops,
		.of_match_table = fsa9480_of_match,
	पूर्ण,
	.probe			= fsa9480_probe,
	.हटाओ			= fsa9480_हटाओ,
	.id_table		= fsa9480_id,
पूर्ण;

अटल पूर्णांक __init fsa9480_module_init(व्योम)
अणु
	वापस i2c_add_driver(&fsa9480_i2c_driver);
पूर्ण
subsys_initcall(fsa9480_module_init);

अटल व्योम __निकास fsa9480_module_निकास(व्योम)
अणु
	i2c_del_driver(&fsa9480_i2c_driver);
पूर्ण
module_निकास(fsa9480_module_निकास);

MODULE_DESCRIPTION("Fairchild Semiconductor FSA9480 extcon driver");
MODULE_AUTHOR("Tomasz Figa <tomasz.figa@gmail.com>");
MODULE_LICENSE("GPL");
