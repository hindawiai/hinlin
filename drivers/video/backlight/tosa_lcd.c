<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  LCD / Backlight control code क्रम Sharp SL-6000x (tosa)
 *
 *  Copyright (c) 2005		Dirk Opfer
 *  Copyright (c) 2007,2008	Dmitry Baryshkov
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/delay.h>
#समावेश <linux/lcd.h>
#समावेश <linux/fb.h>

#समावेश <यंत्र/mach/sharpsl_param.h>

#समावेश "tosa_bl.h"

#घोषणा POWER_IS_ON(pwr)	((pwr) <= FB_BLANK_NORMAL)

#घोषणा TG_REG0_VQV	0x0001
#घोषणा TG_REG0_COLOR	0x0002
#घोषणा TG_REG0_UD	0x0004
#घोषणा TG_REG0_LR	0x0008

/*
 * Timing Generator
 */
#घोषणा TG_PNLCTL 	0x00
#घोषणा TG_TPOSCTL 	0x01
#घोषणा TG_DUTYCTL 	0x02
#घोषणा TG_GPOSR 	0x03
#घोषणा TG_GPODR1 	0x04
#घोषणा TG_GPODR2 	0x05
#घोषणा TG_PINICTL 	0x06
#घोषणा TG_HPOSCTL 	0x07


#घोषणा	DAC_BASE	0x4e

काष्ठा tosa_lcd_data अणु
	काष्ठा spi_device *spi;
	काष्ठा lcd_device *lcd;
	काष्ठा i2c_client *i2c;
	काष्ठा gpio_desc *gpiod_tg;

	पूर्णांक lcd_घातer;
	bool is_vga;
पूर्ण;

अटल पूर्णांक tosa_tg_send(काष्ठा spi_device *spi, पूर्णांक adrs, uपूर्णांक8_t data)
अणु
	u8 buf[1];
	काष्ठा spi_message msg;
	काष्ठा spi_transfer xfer = अणु
		.len		= 1,
		.cs_change	= 0,
		.tx_buf		= buf,
	पूर्ण;

	buf[0] = ((adrs & 0x07) << 5) | (data & 0x1f);
	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);

	वापस spi_sync(spi, &msg);
पूर्ण

पूर्णांक tosa_bl_enable(काष्ठा spi_device *spi, पूर्णांक enable)
अणु
	/* bl_enable GP04=1 otherwise GP04=0*/
	वापस tosa_tg_send(spi, TG_GPODR2, enable ? 0x01 : 0x00);
पूर्ण
EXPORT_SYMBOL(tosa_bl_enable);

अटल व्योम tosa_lcd_tg_init(काष्ठा tosa_lcd_data *data)
अणु
	/* TG on */
	gpiod_set_value(data->gpiod_tg, 0);

	mdelay(60);

	/* delayed 0clk TCTL संकेत क्रम VGA */
	tosa_tg_send(data->spi, TG_TPOSCTL, 0x00);
	/* GPOS0=घातercontrol, GPOS1=GPIO, GPOS2=TCTL */
	tosa_tg_send(data->spi, TG_GPOSR, 0x02);
पूर्ण

अटल व्योम tosa_lcd_tg_on(काष्ठा tosa_lcd_data *data)
अणु
	काष्ठा spi_device *spi = data->spi;
	पूर्णांक value = TG_REG0_COLOR | TG_REG0_UD | TG_REG0_LR;

	अगर (data->is_vga)
		value |= TG_REG0_VQV;

	tosa_tg_send(spi, TG_PNLCTL, value);

	/* TG LCD pannel घातer up */
	tosa_tg_send(spi, TG_PINICTL, 0x4);
	mdelay(50);

	/* TG LCD GVSS */
	tosa_tg_send(spi, TG_PINICTL, 0x0);

	अगर (IS_ERR_OR_शून्य(data->i2c)) अणु
		/*
		 * after the pannel is घातered up the first समय,
		 * we can access the i2c bus so probe क्रम the DAC
		 */
		काष्ठा i2c_adapter *adap = i2c_get_adapter(0);
		काष्ठा i2c_board_info info = अणु
			.dev_name = "tosa-bl",
			.type	= "tosa-bl",
			.addr	= DAC_BASE,
			.platक्रमm_data = data->spi,
		पूर्ण;
		data->i2c = i2c_new_client_device(adap, &info);
	पूर्ण
पूर्ण

अटल व्योम tosa_lcd_tg_off(काष्ठा tosa_lcd_data *data)
अणु
	काष्ठा spi_device *spi = data->spi;

	/* TG LCD VHSA off */
	tosa_tg_send(spi, TG_PINICTL, 0x4);
	mdelay(50);

	/* TG LCD संकेत off */
	tosa_tg_send(spi, TG_PINICTL, 0x6);
	mdelay(50);

	/* TG Off */
	gpiod_set_value(data->gpiod_tg, 1);
	mdelay(100);
पूर्ण

पूर्णांक tosa_lcd_set_घातer(काष्ठा lcd_device *lcd, पूर्णांक घातer)
अणु
	काष्ठा tosa_lcd_data *data = lcd_get_data(lcd);

	अगर (POWER_IS_ON(घातer) && !POWER_IS_ON(data->lcd_घातer))
		tosa_lcd_tg_on(data);

	अगर (!POWER_IS_ON(घातer) && POWER_IS_ON(data->lcd_घातer))
		tosa_lcd_tg_off(data);

	data->lcd_घातer = घातer;
	वापस 0;
पूर्ण

अटल पूर्णांक tosa_lcd_get_घातer(काष्ठा lcd_device *lcd)
अणु
	काष्ठा tosa_lcd_data *data = lcd_get_data(lcd);

	वापस data->lcd_घातer;
पूर्ण

अटल पूर्णांक tosa_lcd_set_mode(काष्ठा lcd_device *lcd, काष्ठा fb_videomode *mode)
अणु
	काष्ठा tosa_lcd_data *data = lcd_get_data(lcd);

	अगर (mode->xres == 320 || mode->yres == 320)
		data->is_vga = false;
	अन्यथा
		data->is_vga = true;

	अगर (POWER_IS_ON(data->lcd_घातer))
		tosa_lcd_tg_on(data);

	वापस 0;
पूर्ण

अटल काष्ठा lcd_ops tosa_lcd_ops = अणु
	.set_घातer = tosa_lcd_set_घातer,
	.get_घातer = tosa_lcd_get_घातer,
	.set_mode = tosa_lcd_set_mode,
पूर्ण;

अटल पूर्णांक tosa_lcd_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;
	काष्ठा tosa_lcd_data *data;

	data = devm_kzalloc(&spi->dev, माप(काष्ठा tosa_lcd_data),
				GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->is_vga = true; /* शेष to VGA mode */

	/*
	 * bits_per_word cannot be configured in platक्रमm data
	 */
	spi->bits_per_word = 8;

	ret = spi_setup(spi);
	अगर (ret < 0)
		वापस ret;

	data->spi = spi;
	spi_set_drvdata(spi, data);

	data->gpiod_tg = devm_gpiod_get(&spi->dev, "tg #pwr", GPIOD_OUT_LOW);
	अगर (IS_ERR(data->gpiod_tg))
		वापस PTR_ERR(data->gpiod_tg);

	mdelay(60);

	tosa_lcd_tg_init(data);

	tosa_lcd_tg_on(data);

	data->lcd = devm_lcd_device_रेजिस्टर(&spi->dev, "tosa-lcd", &spi->dev,
					data, &tosa_lcd_ops);

	अगर (IS_ERR(data->lcd)) अणु
		ret = PTR_ERR(data->lcd);
		data->lcd = शून्य;
		जाओ err_रेजिस्टर;
	पूर्ण

	वापस 0;

err_रेजिस्टर:
	tosa_lcd_tg_off(data);
	वापस ret;
पूर्ण

अटल पूर्णांक tosa_lcd_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा tosa_lcd_data *data = spi_get_drvdata(spi);

	i2c_unरेजिस्टर_device(data->i2c);

	tosa_lcd_tg_off(data);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tosa_lcd_suspend(काष्ठा device *dev)
अणु
	काष्ठा tosa_lcd_data *data = dev_get_drvdata(dev);

	tosa_lcd_tg_off(data);

	वापस 0;
पूर्ण

अटल पूर्णांक tosa_lcd_resume(काष्ठा device *dev)
अणु
	काष्ठा tosa_lcd_data *data = dev_get_drvdata(dev);

	tosa_lcd_tg_init(data);
	अगर (POWER_IS_ON(data->lcd_घातer))
		tosa_lcd_tg_on(data);
	अन्यथा
		tosa_lcd_tg_off(data);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(tosa_lcd_pm_ops, tosa_lcd_suspend, tosa_lcd_resume);

अटल काष्ठा spi_driver tosa_lcd_driver = अणु
	.driver = अणु
		.name		= "tosa-lcd",
		.pm		= &tosa_lcd_pm_ops,
	पूर्ण,
	.probe		= tosa_lcd_probe,
	.हटाओ		= tosa_lcd_हटाओ,
पूर्ण;

module_spi_driver(tosa_lcd_driver);

MODULE_AUTHOR("Dmitry Baryshkov");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("LCD/Backlight control for Sharp SL-6000 PDA");
MODULE_ALIAS("spi:tosa-lcd");
