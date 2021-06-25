<शैली गुरु>
/*
 * Driver क्रम the LCD display on the Tensilica XTFPGA board family.
 * http://www.mytechcorp.com/cfdata/productFile/File1/MOC-16216B-B-A0A04.pdf
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001, 2006 Tensilica Inc.
 * Copyright (C) 2015 Cadence Design Systems Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>

#समावेश <platक्रमm/hardware.h>
#समावेश <platक्रमm/lcd.h>

/* LCD inकाष्ठाion and data addresses. */
#घोषणा LCD_INSTR_ADDR		((अक्षर *)IOADDR(CONFIG_XTFPGA_LCD_BASE_ADDR))
#घोषणा LCD_DATA_ADDR		(LCD_INSTR_ADDR + 4)

#घोषणा LCD_CLEAR		0x1
#घोषणा LCD_DISPLAY_ON		0xc

/* 8bit and 2 lines display */
#घोषणा LCD_DISPLAY_MODE8BIT	0x38
#घोषणा LCD_DISPLAY_MODE4BIT	0x28
#घोषणा LCD_DISPLAY_POS		0x80
#घोषणा LCD_SHIFT_LEFT		0x18
#घोषणा LCD_SHIFT_RIGHT		0x1c

अटल व्योम lcd_put_byte(u8 *addr, u8 data)
अणु
#अगर_घोषित CONFIG_XTFPGA_LCD_8BIT_ACCESS
	WRITE_ONCE(*addr, data);
#अन्यथा
	WRITE_ONCE(*addr, data & 0xf0);
	WRITE_ONCE(*addr, (data << 4) & 0xf0);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __init lcd_init(व्योम)
अणु
	WRITE_ONCE(*LCD_INSTR_ADDR, LCD_DISPLAY_MODE8BIT);
	mdelay(5);
	WRITE_ONCE(*LCD_INSTR_ADDR, LCD_DISPLAY_MODE8BIT);
	udelay(200);
	WRITE_ONCE(*LCD_INSTR_ADDR, LCD_DISPLAY_MODE8BIT);
	udelay(50);
#अगर_अघोषित CONFIG_XTFPGA_LCD_8BIT_ACCESS
	WRITE_ONCE(*LCD_INSTR_ADDR, LCD_DISPLAY_MODE4BIT);
	udelay(50);
	lcd_put_byte(LCD_INSTR_ADDR, LCD_DISPLAY_MODE4BIT);
	udelay(50);
#पूर्ण_अगर
	lcd_put_byte(LCD_INSTR_ADDR, LCD_DISPLAY_ON);
	udelay(50);
	lcd_put_byte(LCD_INSTR_ADDR, LCD_CLEAR);
	mdelay(10);
	lcd_disp_at_pos("XTENSA LINUX", 0);
	वापस 0;
पूर्ण

व्योम lcd_disp_at_pos(अक्षर *str, अचिन्हित अक्षर pos)
अणु
	lcd_put_byte(LCD_INSTR_ADDR, LCD_DISPLAY_POS | pos);
	udelay(100);
	जबतक (*str != 0) अणु
		lcd_put_byte(LCD_DATA_ADDR, *str);
		udelay(200);
		str++;
	पूर्ण
पूर्ण

व्योम lcd_shअगरtleft(व्योम)
अणु
	lcd_put_byte(LCD_INSTR_ADDR, LCD_SHIFT_LEFT);
	udelay(50);
पूर्ण

व्योम lcd_shअगरtright(व्योम)
अणु
	lcd_put_byte(LCD_INSTR_ADDR, LCD_SHIFT_RIGHT);
	udelay(50);
पूर्ण

arch_initcall(lcd_init);
