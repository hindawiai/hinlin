<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#समावेश "charlcd.h"
#समावेश "hd44780_common.h"

/* LCD commands */
#घोषणा LCD_CMD_DISPLAY_CLEAR	0x01	/* Clear entire display */

#घोषणा LCD_CMD_ENTRY_MODE	0x04	/* Set entry mode */
#घोषणा LCD_CMD_CURSOR_INC	0x02	/* Increment cursor */

#घोषणा LCD_CMD_DISPLAY_CTRL	0x08	/* Display control */
#घोषणा LCD_CMD_DISPLAY_ON	0x04	/* Set display on */
#घोषणा LCD_CMD_CURSOR_ON	0x02	/* Set cursor on */
#घोषणा LCD_CMD_BLINK_ON	0x01	/* Set blink on */

#घोषणा LCD_CMD_SHIFT		0x10	/* Shअगरt cursor/display */
#घोषणा LCD_CMD_DISPLAY_SHIFT	0x08	/* Shअगरt display instead of cursor */
#घोषणा LCD_CMD_SHIFT_RIGHT	0x04	/* Shअगरt display/cursor to the right */

#घोषणा LCD_CMD_FUNCTION_SET	0x20	/* Set function */
#घोषणा LCD_CMD_DATA_LEN_8BITS	0x10	/* Set data length to 8 bits */
#घोषणा LCD_CMD_TWO_LINES	0x08	/* Set to two display lines */
#घोषणा LCD_CMD_FONT_5X10_DOTS	0x04	/* Set अक्षर font to 5x10 करोts */

#घोषणा LCD_CMD_SET_CGRAM_ADDR	0x40	/* Set अक्षर generator RAM address */

#घोषणा LCD_CMD_SET_DDRAM_ADDR	0x80	/* Set display data RAM address */

/* sleeps that many milliseconds with a reschedule */
अटल व्योम दीर्घ_sleep(पूर्णांक ms)
अणु
	schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(ms));
पूर्ण

पूर्णांक hd44780_common_prपूर्णांक(काष्ठा अक्षरlcd *lcd, पूर्णांक c)
अणु
	काष्ठा hd44780_common *hdc = lcd->drvdata;

	अगर (lcd->addr.x < hdc->bwidth) अणु
		hdc->ग_लिखो_data(hdc, c);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(hd44780_common_prपूर्णांक);

पूर्णांक hd44780_common_जाओxy(काष्ठा अक्षरlcd *lcd, अचिन्हित पूर्णांक x, अचिन्हित पूर्णांक y)
अणु
	काष्ठा hd44780_common *hdc = lcd->drvdata;
	अचिन्हित पूर्णांक addr;

	/*
	 * we क्रमce the cursor to stay at the end of the
	 * line अगर it wants to go farther
	 */
	addr = x < hdc->bwidth ? x & (hdc->hwidth - 1) : hdc->bwidth - 1;
	अगर (y & 1)
		addr += hdc->hwidth;
	अगर (y & 2)
		addr += hdc->bwidth;
	hdc->ग_लिखो_cmd(hdc, LCD_CMD_SET_DDRAM_ADDR | addr);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hd44780_common_जाओxy);

पूर्णांक hd44780_common_home(काष्ठा अक्षरlcd *lcd)
अणु
	वापस hd44780_common_जाओxy(lcd, 0, 0);
पूर्ण
EXPORT_SYMBOL_GPL(hd44780_common_home);

/* clears the display and resets X/Y */
पूर्णांक hd44780_common_clear_display(काष्ठा अक्षरlcd *lcd)
अणु
	काष्ठा hd44780_common *hdc = lcd->drvdata;

	hdc->ग_लिखो_cmd(hdc, LCD_CMD_DISPLAY_CLEAR);
	/* datasheet says to रुको 1,64 milliseconds */
	दीर्घ_sleep(2);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hd44780_common_clear_display);

पूर्णांक hd44780_common_init_display(काष्ठा अक्षरlcd *lcd)
अणु
	काष्ठा hd44780_common *hdc = lcd->drvdata;

	व्योम (*ग_लिखो_cmd_raw)(काष्ठा hd44780_common *hdc, पूर्णांक cmd);
	u8 init;

	अगर (hdc->अगरwidth != 4 && hdc->अगरwidth != 8)
		वापस -EINVAL;

	hdc->hd44780_common_flags = ((lcd->height > 1) ? LCD_FLAG_N : 0) |
		LCD_FLAG_D | LCD_FLAG_C | LCD_FLAG_B;

	दीर्घ_sleep(20);		/* रुको 20 ms after घातer-up क्रम the paranoid */

	/*
	 * 8-bit mode, 1 line, small fonts; let's करो it 3 बार, to make sure
	 * the LCD is in 8-bit mode afterwards
	 */
	init = LCD_CMD_FUNCTION_SET | LCD_CMD_DATA_LEN_8BITS;
	अगर (hdc->अगरwidth == 4) अणु
		init >>= 4;
		ग_लिखो_cmd_raw = hdc->ग_लिखो_cmd_raw4;
	पूर्ण अन्यथा अणु
		ग_लिखो_cmd_raw = hdc->ग_लिखो_cmd;
	पूर्ण
	ग_लिखो_cmd_raw(hdc, init);
	दीर्घ_sleep(10);
	ग_लिखो_cmd_raw(hdc, init);
	दीर्घ_sleep(10);
	ग_लिखो_cmd_raw(hdc, init);
	दीर्घ_sleep(10);

	अगर (hdc->अगरwidth == 4) अणु
		/* Switch to 4-bit mode, 1 line, small fonts */
		hdc->ग_लिखो_cmd_raw4(hdc, LCD_CMD_FUNCTION_SET >> 4);
		दीर्घ_sleep(10);
	पूर्ण

	/* set font height and lines number */
	hdc->ग_लिखो_cmd(hdc,
		LCD_CMD_FUNCTION_SET |
		((hdc->अगरwidth == 8) ? LCD_CMD_DATA_LEN_8BITS : 0) |
		((hdc->hd44780_common_flags & LCD_FLAG_F) ?
			LCD_CMD_FONT_5X10_DOTS : 0) |
		((hdc->hd44780_common_flags & LCD_FLAG_N) ?
			LCD_CMD_TWO_LINES : 0));
	दीर्घ_sleep(10);

	/* display off, cursor off, blink off */
	hdc->ग_लिखो_cmd(hdc, LCD_CMD_DISPLAY_CTRL);
	दीर्घ_sleep(10);

	hdc->ग_लिखो_cmd(hdc,
		LCD_CMD_DISPLAY_CTRL |	/* set display mode */
		((hdc->hd44780_common_flags & LCD_FLAG_D) ?
			LCD_CMD_DISPLAY_ON : 0) |
		((hdc->hd44780_common_flags & LCD_FLAG_C) ?
			LCD_CMD_CURSOR_ON : 0) |
		((hdc->hd44780_common_flags & LCD_FLAG_B) ?
			LCD_CMD_BLINK_ON : 0));

	अक्षरlcd_backlight(lcd,
			(hdc->hd44780_common_flags & LCD_FLAG_L) ? 1 : 0);

	दीर्घ_sleep(10);

	/* entry mode set : increment, cursor shअगरting */
	hdc->ग_लिखो_cmd(hdc, LCD_CMD_ENTRY_MODE | LCD_CMD_CURSOR_INC);

	hd44780_common_clear_display(lcd);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hd44780_common_init_display);

पूर्णांक hd44780_common_shअगरt_cursor(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_shअगरt_dir dir)
अणु
	काष्ठा hd44780_common *hdc = lcd->drvdata;

	अगर (dir == CHARLCD_SHIFT_LEFT) अणु
		/* back one अक्षर अगर not at end of line */
		अगर (lcd->addr.x < hdc->bwidth)
			hdc->ग_लिखो_cmd(hdc, LCD_CMD_SHIFT);
	पूर्ण अन्यथा अगर (dir == CHARLCD_SHIFT_RIGHT) अणु
		/* allow the cursor to pass the end of the line */
		अगर (lcd->addr.x < (hdc->bwidth - 1))
			hdc->ग_लिखो_cmd(hdc,
					LCD_CMD_SHIFT | LCD_CMD_SHIFT_RIGHT);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hd44780_common_shअगरt_cursor);

पूर्णांक hd44780_common_shअगरt_display(काष्ठा अक्षरlcd *lcd,
		क्रमागत अक्षरlcd_shअगरt_dir dir)
अणु
	काष्ठा hd44780_common *hdc = lcd->drvdata;

	अगर (dir == CHARLCD_SHIFT_LEFT)
		hdc->ग_लिखो_cmd(hdc, LCD_CMD_SHIFT | LCD_CMD_DISPLAY_SHIFT);
	अन्यथा अगर (dir == CHARLCD_SHIFT_RIGHT)
		hdc->ग_लिखो_cmd(hdc, LCD_CMD_SHIFT | LCD_CMD_DISPLAY_SHIFT |
			LCD_CMD_SHIFT_RIGHT);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hd44780_common_shअगरt_display);

अटल व्योम hd44780_common_set_mode(काष्ठा hd44780_common *hdc)
अणु
	hdc->ग_लिखो_cmd(hdc,
		LCD_CMD_DISPLAY_CTRL |
		((hdc->hd44780_common_flags & LCD_FLAG_D) ?
			LCD_CMD_DISPLAY_ON : 0) |
		((hdc->hd44780_common_flags & LCD_FLAG_C) ?
			LCD_CMD_CURSOR_ON : 0) |
		((hdc->hd44780_common_flags & LCD_FLAG_B) ?
			LCD_CMD_BLINK_ON : 0));
पूर्ण

पूर्णांक hd44780_common_display(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_onoff on)
अणु
	काष्ठा hd44780_common *hdc = lcd->drvdata;

	अगर (on == CHARLCD_ON)
		hdc->hd44780_common_flags |= LCD_FLAG_D;
	अन्यथा
		hdc->hd44780_common_flags &= ~LCD_FLAG_D;

	hd44780_common_set_mode(hdc);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hd44780_common_display);

पूर्णांक hd44780_common_cursor(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_onoff on)
अणु
	काष्ठा hd44780_common *hdc = lcd->drvdata;

	अगर (on == CHARLCD_ON)
		hdc->hd44780_common_flags |= LCD_FLAG_C;
	अन्यथा
		hdc->hd44780_common_flags &= ~LCD_FLAG_C;

	hd44780_common_set_mode(hdc);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hd44780_common_cursor);

पूर्णांक hd44780_common_blink(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_onoff on)
अणु
	काष्ठा hd44780_common *hdc = lcd->drvdata;

	अगर (on == CHARLCD_ON)
		hdc->hd44780_common_flags |= LCD_FLAG_B;
	अन्यथा
		hdc->hd44780_common_flags &= ~LCD_FLAG_B;

	hd44780_common_set_mode(hdc);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hd44780_common_blink);

अटल व्योम hd44780_common_set_function(काष्ठा hd44780_common *hdc)
अणु
	hdc->ग_लिखो_cmd(hdc,
		LCD_CMD_FUNCTION_SET |
		((hdc->अगरwidth == 8) ? LCD_CMD_DATA_LEN_8BITS : 0) |
		((hdc->hd44780_common_flags & LCD_FLAG_F) ?
			LCD_CMD_FONT_5X10_DOTS : 0) |
		((hdc->hd44780_common_flags & LCD_FLAG_N) ?
			LCD_CMD_TWO_LINES : 0));
पूर्ण

पूर्णांक hd44780_common_fontsize(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_fontsize size)
अणु
	काष्ठा hd44780_common *hdc = lcd->drvdata;

	अगर (size == CHARLCD_FONTSIZE_LARGE)
		hdc->hd44780_common_flags |= LCD_FLAG_F;
	अन्यथा
		hdc->hd44780_common_flags &= ~LCD_FLAG_F;

	hd44780_common_set_function(hdc);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hd44780_common_fontsize);

पूर्णांक hd44780_common_lines(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_lines lines)
अणु
	काष्ठा hd44780_common *hdc = lcd->drvdata;

	अगर (lines == CHARLCD_LINES_2)
		hdc->hd44780_common_flags |= LCD_FLAG_N;
	अन्यथा
		hdc->hd44780_common_flags &= ~LCD_FLAG_N;

	hd44780_common_set_function(hdc);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hd44780_common_lines);

पूर्णांक hd44780_common_redefine_अक्षर(काष्ठा अक्षरlcd *lcd, अक्षर *esc)
अणु
	/* Generator : LGcxxxxx...xx; must have <c> between '0'
	 * and '7', representing the numerical ASCII code of the
	 * redefined अक्षरacter, and <xx...xx> a sequence of 16
	 * hex digits representing 8 bytes क्रम each अक्षरacter.
	 * Most LCDs will only use 5 lower bits of the 7 first
	 * bytes.
	 */

	काष्ठा hd44780_common *hdc = lcd->drvdata;
	अचिन्हित अक्षर cgbytes[8];
	अचिन्हित अक्षर cgaddr;
	पूर्णांक cgoffset;
	पूर्णांक shअगरt;
	अक्षर value;
	पूर्णांक addr;

	अगर (!म_अक्षर(esc, ';'))
		वापस 0;

	esc++;

	cgaddr = *(esc++) - '0';
	अगर (cgaddr > 7)
		वापस 1;

	cgoffset = 0;
	shअगरt = 0;
	value = 0;
	जबतक (*esc && cgoffset < 8) अणु
		पूर्णांक half;

		shअगरt ^= 4;
		half = hex_to_bin(*esc++);
		अगर (half < 0)
			जारी;

		value |= half << shअगरt;
		अगर (shअगरt == 0) अणु
			cgbytes[cgoffset++] = value;
			value = 0;
		पूर्ण
	पूर्ण

	hdc->ग_लिखो_cmd(hdc, LCD_CMD_SET_CGRAM_ADDR | (cgaddr * 8));
	क्रम (addr = 0; addr < cgoffset; addr++)
		hdc->ग_लिखो_data(hdc, cgbytes[addr]);

	/* ensures that we stop writing to CGRAM */
	lcd->ops->जाओxy(lcd, lcd->addr.x, lcd->addr.y);
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(hd44780_common_redefine_अक्षर);

काष्ठा hd44780_common *hd44780_common_alloc(व्योम)
अणु
	काष्ठा hd44780_common *hd;

	hd = kzalloc(माप(*hd), GFP_KERNEL);
	अगर (!hd)
		वापस शून्य;

	hd->अगरwidth = 8;
	hd->bwidth = DEFAULT_LCD_BWIDTH;
	hd->hwidth = DEFAULT_LCD_HWIDTH;
	वापस hd;
पूर्ण
EXPORT_SYMBOL_GPL(hd44780_common_alloc);

MODULE_LICENSE("GPL");
