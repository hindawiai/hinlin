<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * HD44780 Character LCD driver क्रम Linux
 *
 * Copyright (C) 2000-2008, Willy Tarreau <w@1wt.eu>
 * Copyright (C) 2016-2017 Glider bvba
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>

#समावेश "charlcd.h"
#समावेश "hd44780_common.h"

क्रमागत hd44780_pin अणु
	/* Order करोes matter due to writing to GPIO array subsets! */
	PIN_DATA0,	/* Optional */
	PIN_DATA1,	/* Optional */
	PIN_DATA2,	/* Optional */
	PIN_DATA3,	/* Optional */
	PIN_DATA4,
	PIN_DATA5,
	PIN_DATA6,
	PIN_DATA7,
	PIN_CTRL_RS,
	PIN_CTRL_RW,	/* Optional */
	PIN_CTRL_E,
	PIN_CTRL_BL,   /* Optional */
	PIN_NUM
पूर्ण;

काष्ठा hd44780 अणु
	काष्ठा gpio_desc *pins[PIN_NUM];
पूर्ण;

अटल व्योम hd44780_backlight(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_onoff on)
अणु
	काष्ठा hd44780_common *hdc = lcd->drvdata;
	काष्ठा hd44780 *hd = hdc->hd44780;

	अगर (hd->pins[PIN_CTRL_BL])
		gpiod_set_value_cansleep(hd->pins[PIN_CTRL_BL], on);
पूर्ण

अटल व्योम hd44780_strobe_gpio(काष्ठा hd44780 *hd)
अणु
	/* Maपूर्णांकain the data during 20 us beक्रमe the strobe */
	udelay(20);

	gpiod_set_value_cansleep(hd->pins[PIN_CTRL_E], 1);

	/* Maपूर्णांकain the strobe during 40 us */
	udelay(40);

	gpiod_set_value_cansleep(hd->pins[PIN_CTRL_E], 0);
पूर्ण

/* ग_लिखो to an LCD panel रेजिस्टर in 8 bit GPIO mode */
अटल व्योम hd44780_ग_लिखो_gpio8(काष्ठा hd44780 *hd, u8 val, अचिन्हित पूर्णांक rs)
अणु
	DECLARE_BITMAP(values, 10); /* क्रम DATA[0-7], RS, RW */
	अचिन्हित पूर्णांक n;

	values[0] = val;
	__assign_bit(8, values, rs);
	n = hd->pins[PIN_CTRL_RW] ? 10 : 9;

	/* Present the data to the port */
	gpiod_set_array_value_cansleep(n, &hd->pins[PIN_DATA0], शून्य, values);

	hd44780_strobe_gpio(hd);
पूर्ण

/* ग_लिखो to an LCD panel रेजिस्टर in 4 bit GPIO mode */
अटल व्योम hd44780_ग_लिखो_gpio4(काष्ठा hd44780 *hd, u8 val, अचिन्हित पूर्णांक rs)
अणु
	DECLARE_BITMAP(values, 6); /* क्रम DATA[4-7], RS, RW */
	अचिन्हित पूर्णांक n;

	/* High nibble + RS, RW */
	values[0] = val >> 4;
	__assign_bit(4, values, rs);
	n = hd->pins[PIN_CTRL_RW] ? 6 : 5;

	/* Present the data to the port */
	gpiod_set_array_value_cansleep(n, &hd->pins[PIN_DATA4], शून्य, values);

	hd44780_strobe_gpio(hd);

	/* Low nibble */
	values[0] &= ~0x0fUL;
	values[0] |= val & 0x0f;

	/* Present the data to the port */
	gpiod_set_array_value_cansleep(n, &hd->pins[PIN_DATA4], शून्य, values);

	hd44780_strobe_gpio(hd);
पूर्ण

/* Send a command to the LCD panel in 8 bit GPIO mode */
अटल व्योम hd44780_ग_लिखो_cmd_gpio8(काष्ठा hd44780_common *hdc, पूर्णांक cmd)
अणु
	काष्ठा hd44780 *hd = hdc->hd44780;

	hd44780_ग_लिखो_gpio8(hd, cmd, 0);

	/* The लघुest command takes at least 120 us */
	udelay(120);
पूर्ण

/* Send data to the LCD panel in 8 bit GPIO mode */
अटल व्योम hd44780_ग_लिखो_data_gpio8(काष्ठा hd44780_common *hdc, पूर्णांक data)
अणु
	काष्ठा hd44780 *hd = hdc->hd44780;

	hd44780_ग_लिखो_gpio8(hd, data, 1);

	/* The लघुest data takes at least 45 us */
	udelay(45);
पूर्ण

अटल स्थिर काष्ठा अक्षरlcd_ops hd44780_ops_gpio8 = अणु
	.backlight	= hd44780_backlight,
	.prपूर्णांक		= hd44780_common_prपूर्णांक,
	.जाओxy		= hd44780_common_जाओxy,
	.home		= hd44780_common_home,
	.clear_display	= hd44780_common_clear_display,
	.init_display	= hd44780_common_init_display,
	.shअगरt_cursor	= hd44780_common_shअगरt_cursor,
	.shअगरt_display	= hd44780_common_shअगरt_display,
	.display	= hd44780_common_display,
	.cursor		= hd44780_common_cursor,
	.blink		= hd44780_common_blink,
	.fontsize	= hd44780_common_fontsize,
	.lines		= hd44780_common_lines,
	.redefine_अक्षर	= hd44780_common_redefine_अक्षर,
पूर्ण;

/* Send a command to the LCD panel in 4 bit GPIO mode */
अटल व्योम hd44780_ग_लिखो_cmd_gpio4(काष्ठा hd44780_common *hdc, पूर्णांक cmd)
अणु
	काष्ठा hd44780 *hd = hdc->hd44780;

	hd44780_ग_लिखो_gpio4(hd, cmd, 0);

	/* The लघुest command takes at least 120 us */
	udelay(120);
पूर्ण

/* Send 4-bits of a command to the LCD panel in raw 4 bit GPIO mode */
अटल व्योम hd44780_ग_लिखो_cmd_raw_gpio4(काष्ठा hd44780_common *hdc, पूर्णांक cmd)
अणु
	DECLARE_BITMAP(values, 6); /* क्रम DATA[4-7], RS, RW */
	काष्ठा hd44780 *hd = hdc->hd44780;
	अचिन्हित पूर्णांक n;

	/* Command nibble + RS, RW */
	values[0] = cmd & 0x0f;
	n = hd->pins[PIN_CTRL_RW] ? 6 : 5;

	/* Present the data to the port */
	gpiod_set_array_value_cansleep(n, &hd->pins[PIN_DATA4], शून्य, values);

	hd44780_strobe_gpio(hd);
पूर्ण

/* Send data to the LCD panel in 4 bit GPIO mode */
अटल व्योम hd44780_ग_लिखो_data_gpio4(काष्ठा hd44780_common *hdc, पूर्णांक data)
अणु
	काष्ठा hd44780 *hd = hdc->hd44780;

	hd44780_ग_लिखो_gpio4(hd, data, 1);

	/* The लघुest data takes at least 45 us */
	udelay(45);
पूर्ण

अटल स्थिर काष्ठा अक्षरlcd_ops hd44780_ops_gpio4 = अणु
	.backlight	= hd44780_backlight,
	.prपूर्णांक		= hd44780_common_prपूर्णांक,
	.जाओxy		= hd44780_common_जाओxy,
	.home		= hd44780_common_home,
	.clear_display	= hd44780_common_clear_display,
	.init_display	= hd44780_common_init_display,
	.shअगरt_cursor	= hd44780_common_shअगरt_cursor,
	.shअगरt_display	= hd44780_common_shअगरt_display,
	.display	= hd44780_common_display,
	.cursor		= hd44780_common_cursor,
	.blink		= hd44780_common_blink,
	.fontsize	= hd44780_common_fontsize,
	.lines		= hd44780_common_lines,
	.redefine_अक्षर	= hd44780_common_redefine_अक्षर,
पूर्ण;

अटल पूर्णांक hd44780_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	अचिन्हित पूर्णांक i, base;
	काष्ठा अक्षरlcd *lcd;
	काष्ठा hd44780_common *hdc;
	काष्ठा hd44780 *hd;
	पूर्णांक अगरwidth, ret = -ENOMEM;

	/* Required pins */
	अगरwidth = gpiod_count(dev, "data");
	अगर (अगरwidth < 0)
		वापस अगरwidth;

	चयन (अगरwidth) अणु
	हाल 4:
		base = PIN_DATA4;
		अवरोध;
	हाल 8:
		base = PIN_DATA0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	hdc = hd44780_common_alloc();
	अगर (!hdc)
		वापस -ENOMEM;

	lcd = अक्षरlcd_alloc();
	अगर (!lcd)
		जाओ fail1;

	hd = kzalloc(माप(काष्ठा hd44780), GFP_KERNEL);
	अगर (!hd)
		जाओ fail2;

	hdc->hd44780 = hd;
	lcd->drvdata = hdc;
	क्रम (i = 0; i < अगरwidth; i++) अणु
		hd->pins[base + i] = devm_gpiod_get_index(dev, "data", i,
							  GPIOD_OUT_LOW);
		अगर (IS_ERR(hd->pins[base + i])) अणु
			ret = PTR_ERR(hd->pins[base + i]);
			जाओ fail3;
		पूर्ण
	पूर्ण

	hd->pins[PIN_CTRL_E] = devm_gpiod_get(dev, "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(hd->pins[PIN_CTRL_E])) अणु
		ret = PTR_ERR(hd->pins[PIN_CTRL_E]);
		जाओ fail3;
	पूर्ण

	hd->pins[PIN_CTRL_RS] = devm_gpiod_get(dev, "rs", GPIOD_OUT_HIGH);
	अगर (IS_ERR(hd->pins[PIN_CTRL_RS])) अणु
		ret = PTR_ERR(hd->pins[PIN_CTRL_RS]);
		जाओ fail3;
	पूर्ण

	/* Optional pins */
	hd->pins[PIN_CTRL_RW] = devm_gpiod_get_optional(dev, "rw",
							GPIOD_OUT_LOW);
	अगर (IS_ERR(hd->pins[PIN_CTRL_RW])) अणु
		ret = PTR_ERR(hd->pins[PIN_CTRL_RW]);
		जाओ fail3;
	पूर्ण

	hd->pins[PIN_CTRL_BL] = devm_gpiod_get_optional(dev, "backlight",
							GPIOD_OUT_LOW);
	अगर (IS_ERR(hd->pins[PIN_CTRL_BL])) अणु
		ret = PTR_ERR(hd->pins[PIN_CTRL_BL]);
		जाओ fail3;
	पूर्ण

	/* Required properties */
	ret = device_property_पढ़ो_u32(dev, "display-height-chars",
				       &lcd->height);
	अगर (ret)
		जाओ fail3;
	ret = device_property_पढ़ो_u32(dev, "display-width-chars", &lcd->width);
	अगर (ret)
		जाओ fail3;

	/*
	 * On displays with more than two rows, the पूर्णांकernal buffer width is
	 * usually equal to the display width
	 */
	अगर (lcd->height > 2)
		hdc->bwidth = lcd->width;

	/* Optional properties */
	device_property_पढ़ो_u32(dev, "internal-buffer-width", &hdc->bwidth);

	hdc->अगरwidth = अगरwidth;
	अगर (अगरwidth == 8) अणु
		lcd->ops = &hd44780_ops_gpio8;
		hdc->ग_लिखो_data = hd44780_ग_लिखो_data_gpio8;
		hdc->ग_लिखो_cmd = hd44780_ग_लिखो_cmd_gpio8;
	पूर्ण अन्यथा अणु
		lcd->ops = &hd44780_ops_gpio4;
		hdc->ग_लिखो_data = hd44780_ग_लिखो_data_gpio4;
		hdc->ग_लिखो_cmd = hd44780_ग_लिखो_cmd_gpio4;
		hdc->ग_लिखो_cmd_raw4 = hd44780_ग_लिखो_cmd_raw_gpio4;
	पूर्ण

	ret = अक्षरlcd_रेजिस्टर(lcd);
	अगर (ret)
		जाओ fail3;

	platक्रमm_set_drvdata(pdev, lcd);
	वापस 0;

fail3:
	kमुक्त(hd);
fail2:
	kमुक्त(lcd);
fail1:
	kमुक्त(hdc);
	वापस ret;
पूर्ण

अटल पूर्णांक hd44780_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा अक्षरlcd *lcd = platक्रमm_get_drvdata(pdev);

	kमुक्त(lcd->drvdata);
	अक्षरlcd_unरेजिस्टर(lcd);

	kमुक्त(lcd);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id hd44780_of_match[] = अणु
	अणु .compatible = "hit,hd44780" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, hd44780_of_match);

अटल काष्ठा platक्रमm_driver hd44780_driver = अणु
	.probe = hd44780_probe,
	.हटाओ = hd44780_हटाओ,
	.driver		= अणु
		.name	= "hd44780",
		.of_match_table = hd44780_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(hd44780_driver);
MODULE_DESCRIPTION("HD44780 Character LCD driver");
MODULE_AUTHOR("Geert Uytterhoeven <geert@linux-m68k.org>");
MODULE_LICENSE("GPL");
