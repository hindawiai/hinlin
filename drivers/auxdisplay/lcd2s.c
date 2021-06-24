<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  console driver क्रम LCD2S 4x20 अक्षरacter displays connected through i2c.
 *  The display also has a spi पूर्णांकerface, but the driver करोes not support
 *  this yet.
 *
 *  This is a driver allowing you to use a LCD2S 4x20 from modtronix
 *  engineering as auxdisplay अक्षरacter device.
 *
 *  (C) 2019 by Lemonage Software GmbH
 *  Author: Lars Pथघschel <poeschel@lemonage.de>
 *  All rights reserved.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>

#समावेश "charlcd.h"

#घोषणा LCD2S_CMD_CUR_MOVES_FWD		0x09
#घोषणा LCD2S_CMD_CUR_BLINK_OFF		0x10
#घोषणा LCD2S_CMD_CUR_UL_OFF		0x11
#घोषणा LCD2S_CMD_DISPLAY_OFF		0x12
#घोषणा LCD2S_CMD_CUR_BLINK_ON		0x18
#घोषणा LCD2S_CMD_CUR_UL_ON		0x19
#घोषणा LCD2S_CMD_DISPLAY_ON		0x1a
#घोषणा LCD2S_CMD_BACKLIGHT_OFF		0x20
#घोषणा LCD2S_CMD_BACKLIGHT_ON		0x28
#घोषणा LCD2S_CMD_WRITE			0x80
#घोषणा LCD2S_CMD_MOV_CUR_RIGHT		0x83
#घोषणा LCD2S_CMD_MOV_CUR_LEFT		0x84
#घोषणा LCD2S_CMD_SHIFT_RIGHT		0x85
#घोषणा LCD2S_CMD_SHIFT_LEFT		0x86
#घोषणा LCD2S_CMD_SHIFT_UP		0x87
#घोषणा LCD2S_CMD_SHIFT_DOWN		0x88
#घोषणा LCD2S_CMD_CUR_ADDR		0x89
#घोषणा LCD2S_CMD_CUR_POS		0x8a
#घोषणा LCD2S_CMD_CUR_RESET		0x8b
#घोषणा LCD2S_CMD_CLEAR			0x8c
#घोषणा LCD2S_CMD_DEF_CUSTOM_CHAR	0x92
#घोषणा LCD2S_CMD_READ_STATUS		0xd0

#घोषणा LCD2S_CHARACTER_SIZE		8

#घोषणा LCD2S_STATUS_BUF_MASK		0x7f

काष्ठा lcd2s_data अणु
	काष्ठा i2c_client *i2c;
	काष्ठा अक्षरlcd *अक्षरlcd;
पूर्ण;

अटल s32 lcd2s_रुको_buf_मुक्त(स्थिर काष्ठा i2c_client *client, पूर्णांक count)
अणु
	s32 status;

	status = i2c_smbus_पढ़ो_byte_data(client, LCD2S_CMD_READ_STATUS);
	अगर (status < 0)
		वापस status;

	जबतक ((status & LCD2S_STATUS_BUF_MASK) < count) अणु
		mdelay(1);
		status = i2c_smbus_पढ़ो_byte_data(client,
						  LCD2S_CMD_READ_STATUS);
		अगर (status < 0)
			वापस status;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lcd2s_i2c_master_send(स्थिर काष्ठा i2c_client *client,
				 स्थिर अक्षर *buf, पूर्णांक count)
अणु
	s32 status;

	status = lcd2s_रुको_buf_मुक्त(client, count);
	अगर (status < 0)
		वापस status;

	वापस i2c_master_send(client, buf, count);
पूर्ण

अटल पूर्णांक lcd2s_i2c_smbus_ग_लिखो_byte(स्थिर काष्ठा i2c_client *client, u8 value)
अणु
	s32 status;

	status = lcd2s_रुको_buf_मुक्त(client, 1);
	अगर (status < 0)
		वापस status;

	वापस i2c_smbus_ग_लिखो_byte(client, value);
पूर्ण

अटल पूर्णांक lcd2s_prपूर्णांक(काष्ठा अक्षरlcd *lcd, पूर्णांक c)
अणु
	काष्ठा lcd2s_data *lcd2s = lcd->drvdata;
	u8 buf[2] = अणु LCD2S_CMD_WRITE, c पूर्ण;

	lcd2s_i2c_master_send(lcd2s->i2c, buf, माप(buf));
	वापस 0;
पूर्ण

अटल पूर्णांक lcd2s_जाओxy(काष्ठा अक्षरlcd *lcd, अचिन्हित पूर्णांक x, अचिन्हित पूर्णांक y)
अणु
	काष्ठा lcd2s_data *lcd2s = lcd->drvdata;
	u8 buf[] = अणु LCD2S_CMD_CUR_POS, y + 1, x + 1पूर्ण;

	lcd2s_i2c_master_send(lcd2s->i2c, buf, माप(buf));

	वापस 0;
पूर्ण

अटल पूर्णांक lcd2s_home(काष्ठा अक्षरlcd *lcd)
अणु
	काष्ठा lcd2s_data *lcd2s = lcd->drvdata;

	lcd2s_i2c_smbus_ग_लिखो_byte(lcd2s->i2c, LCD2S_CMD_CUR_RESET);
	वापस 0;
पूर्ण

अटल पूर्णांक lcd2s_init_display(काष्ठा अक्षरlcd *lcd)
अणु
	काष्ठा lcd2s_data *lcd2s = lcd->drvdata;

	/* turn everything off, but display on */
	lcd2s_i2c_smbus_ग_लिखो_byte(lcd2s->i2c, LCD2S_CMD_DISPLAY_ON);
	lcd2s_i2c_smbus_ग_लिखो_byte(lcd2s->i2c, LCD2S_CMD_BACKLIGHT_OFF);
	lcd2s_i2c_smbus_ग_लिखो_byte(lcd2s->i2c, LCD2S_CMD_CUR_MOVES_FWD);
	lcd2s_i2c_smbus_ग_लिखो_byte(lcd2s->i2c, LCD2S_CMD_CUR_BLINK_OFF);
	lcd2s_i2c_smbus_ग_लिखो_byte(lcd2s->i2c, LCD2S_CMD_CUR_UL_OFF);
	lcd2s_i2c_smbus_ग_लिखो_byte(lcd2s->i2c, LCD2S_CMD_CLEAR);

	वापस 0;
पूर्ण

अटल पूर्णांक lcd2s_shअगरt_cursor(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_shअगरt_dir dir)
अणु
	काष्ठा lcd2s_data *lcd2s = lcd->drvdata;

	अगर (dir == CHARLCD_SHIFT_LEFT)
		lcd2s_i2c_smbus_ग_लिखो_byte(lcd2s->i2c, LCD2S_CMD_MOV_CUR_LEFT);
	अन्यथा
		lcd2s_i2c_smbus_ग_लिखो_byte(lcd2s->i2c, LCD2S_CMD_MOV_CUR_RIGHT);

	वापस 0;
पूर्ण

अटल पूर्णांक lcd2s_shअगरt_display(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_shअगरt_dir dir)
अणु
	काष्ठा lcd2s_data *lcd2s = lcd->drvdata;

	अगर (dir == CHARLCD_SHIFT_LEFT)
		lcd2s_i2c_smbus_ग_लिखो_byte(lcd2s->i2c, LCD2S_CMD_SHIFT_LEFT);
	अन्यथा
		lcd2s_i2c_smbus_ग_लिखो_byte(lcd2s->i2c, LCD2S_CMD_SHIFT_RIGHT);

	वापस 0;
पूर्ण

अटल व्योम lcd2s_backlight(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_onoff on)
अणु
	काष्ठा lcd2s_data *lcd2s = lcd->drvdata;

	अगर (on)
		lcd2s_i2c_smbus_ग_लिखो_byte(lcd2s->i2c, LCD2S_CMD_BACKLIGHT_ON);
	अन्यथा
		lcd2s_i2c_smbus_ग_लिखो_byte(lcd2s->i2c, LCD2S_CMD_BACKLIGHT_OFF);
पूर्ण

अटल पूर्णांक lcd2s_display(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_onoff on)
अणु
	काष्ठा lcd2s_data *lcd2s = lcd->drvdata;

	अगर (on)
		lcd2s_i2c_smbus_ग_लिखो_byte(lcd2s->i2c, LCD2S_CMD_DISPLAY_ON);
	अन्यथा
		lcd2s_i2c_smbus_ग_लिखो_byte(lcd2s->i2c, LCD2S_CMD_DISPLAY_OFF);

	वापस 0;
पूर्ण

अटल पूर्णांक lcd2s_cursor(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_onoff on)
अणु
	काष्ठा lcd2s_data *lcd2s = lcd->drvdata;

	अगर (on)
		lcd2s_i2c_smbus_ग_लिखो_byte(lcd2s->i2c, LCD2S_CMD_CUR_UL_ON);
	अन्यथा
		lcd2s_i2c_smbus_ग_लिखो_byte(lcd2s->i2c, LCD2S_CMD_CUR_UL_OFF);

	वापस 0;
पूर्ण

अटल पूर्णांक lcd2s_blink(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_onoff on)
अणु
	काष्ठा lcd2s_data *lcd2s = lcd->drvdata;

	अगर (on)
		lcd2s_i2c_smbus_ग_लिखो_byte(lcd2s->i2c, LCD2S_CMD_CUR_BLINK_ON);
	अन्यथा
		lcd2s_i2c_smbus_ग_लिखो_byte(lcd2s->i2c, LCD2S_CMD_CUR_BLINK_OFF);

	वापस 0;
पूर्ण

अटल पूर्णांक lcd2s_fontsize(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_fontsize size)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक lcd2s_lines(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_lines lines)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक lcd2s_redefine_अक्षर(काष्ठा अक्षरlcd *lcd, अक्षर *esc)
अणु
	/* Generator : LGcxxxxx...xx; must have <c> between '0'
	 * and '7', representing the numerical ASCII code of the
	 * redefined अक्षरacter, and <xx...xx> a sequence of 16
	 * hex digits representing 8 bytes क्रम each अक्षरacter.
	 * Most LCDs will only use 5 lower bits of the 7 first
	 * bytes.
	 */

	काष्ठा lcd2s_data *lcd2s = lcd->drvdata;
	u8 buf[LCD2S_CHARACTER_SIZE + 2] = अणु LCD2S_CMD_DEF_CUSTOM_CHAR पूर्ण;
	u8 value;
	पूर्णांक shअगरt, i;

	अगर (!म_अक्षर(esc, ';'))
		वापस 0;

	esc++;

	buf[1] = *(esc++) - '0';
	अगर (buf[1] > 7)
		वापस 1;

	i = 0;
	shअगरt = 0;
	value = 0;
	जबतक (*esc && i < LCD2S_CHARACTER_SIZE + 2) अणु
		पूर्णांक half;

		shअगरt ^= 4;
		half = hex_to_bin(*esc++);
		अगर (half < 0)
			जारी;

		value |= half << shअगरt;
		अगर (shअगरt == 0) अणु
			buf[i++] = value;
			value = 0;
		पूर्ण
	पूर्ण

	lcd2s_i2c_master_send(lcd2s->i2c, buf, माप(buf));
	वापस 1;
पूर्ण

अटल पूर्णांक lcd2s_clear_display(काष्ठा अक्षरlcd *lcd)
अणु
	काष्ठा lcd2s_data *lcd2s = lcd->drvdata;

	/* This implicitly sets cursor to first row and column */
	lcd2s_i2c_smbus_ग_लिखो_byte(lcd2s->i2c, LCD2S_CMD_CLEAR);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा अक्षरlcd_ops lcd2s_ops = अणु
	.prपूर्णांक		= lcd2s_prपूर्णांक,
	.backlight	= lcd2s_backlight,
	.जाओxy		= lcd2s_जाओxy,
	.home		= lcd2s_home,
	.clear_display	= lcd2s_clear_display,
	.init_display	= lcd2s_init_display,
	.shअगरt_cursor	= lcd2s_shअगरt_cursor,
	.shअगरt_display	= lcd2s_shअगरt_display,
	.display	= lcd2s_display,
	.cursor		= lcd2s_cursor,
	.blink		= lcd2s_blink,
	.fontsize	= lcd2s_fontsize,
	.lines		= lcd2s_lines,
	.redefine_अक्षर	= lcd2s_redefine_अक्षर,
पूर्ण;

अटल पूर्णांक lcd2s_i2c_probe(काष्ठा i2c_client *i2c,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा अक्षरlcd *lcd;
	काष्ठा lcd2s_data *lcd2s;
	पूर्णांक err;

	अगर (!i2c_check_functionality(i2c->adapter,
			I2C_FUNC_SMBUS_WRITE_BYTE_DATA |
			I2C_FUNC_SMBUS_WRITE_BLOCK_DATA))
		वापस -EIO;

	/* Test, अगर the display is responding */
	err = lcd2s_i2c_smbus_ग_लिखो_byte(i2c, LCD2S_CMD_DISPLAY_OFF);
	अगर (err < 0)
		वापस err;

	lcd = अक्षरlcd_alloc();
	अगर (!lcd)
		वापस -ENOMEM;

	lcd2s = kzalloc(माप(काष्ठा lcd2s_data), GFP_KERNEL);
	अगर (!lcd2s) अणु
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	lcd->drvdata = lcd2s;
	lcd2s->i2c = i2c;
	lcd2s->अक्षरlcd = lcd;

	/* Required properties */
	err = device_property_पढ़ो_u32(&i2c->dev, "display-height-chars",
			&lcd->height);
	अगर (err)
		जाओ fail2;

	err = device_property_पढ़ो_u32(&i2c->dev, "display-width-chars",
			&lcd->width);
	अगर (err)
		जाओ fail2;

	lcd->ops = &lcd2s_ops;

	err = अक्षरlcd_रेजिस्टर(lcd2s->अक्षरlcd);
	अगर (err)
		जाओ fail2;

	i2c_set_clientdata(i2c, lcd2s);
	वापस 0;

fail2:
	kमुक्त(lcd2s);
fail1:
	kमुक्त(lcd);
	वापस err;
पूर्ण

अटल पूर्णांक lcd2s_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा lcd2s_data *lcd2s = i2c_get_clientdata(i2c);

	अक्षरlcd_unरेजिस्टर(lcd2s->अक्षरlcd);
	kमुक्त(lcd2s->अक्षरlcd);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lcd2s_i2c_id[] = अणु
	अणु "lcd2s", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lcd2s_i2c_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id lcd2s_of_table[] = अणु
	अणु .compatible = "modtronix,lcd2s" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lcd2s_of_table);
#पूर्ण_अगर

अटल काष्ठा i2c_driver lcd2s_i2c_driver = अणु
	.driver = अणु
		.name = "lcd2s",
#अगर_घोषित CONFIG_OF
		.of_match_table = of_match_ptr(lcd2s_of_table),
#पूर्ण_अगर
	पूर्ण,
	.probe = lcd2s_i2c_probe,
	.हटाओ = lcd2s_i2c_हटाओ,
	.id_table = lcd2s_i2c_id,
पूर्ण;

अटल पूर्णांक __init lcd2s_modinit(व्योम)
अणु
	पूर्णांक ret = 0;

	ret = i2c_add_driver(&lcd2s_i2c_driver);
	अगर (ret != 0)
		pr_err("Failed to register lcd2s driver\n");

	वापस ret;
पूर्ण
module_init(lcd2s_modinit)

अटल व्योम __निकास lcd2s_निकास(व्योम)
अणु
	i2c_del_driver(&lcd2s_i2c_driver);
पूर्ण
module_निकास(lcd2s_निकास)

MODULE_DESCRIPTION("LCD2S character display driver");
MODULE_AUTHOR("Lars Poeschel");
MODULE_LICENSE("GPL");
