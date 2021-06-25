<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Character LCD driver क्रम Linux
 *
 * Copyright (C) 2000-2008, Willy Tarreau <w@1wt.eu>
 * Copyright (C) 2016-2017 Glider bvba
 */

#अगर_अघोषित _CHARLCD_H
#घोषणा _CHARLCD_H

#घोषणा LCD_FLAG_B		0x0004	/* Blink on */
#घोषणा LCD_FLAG_C		0x0008	/* Cursor on */
#घोषणा LCD_FLAG_D		0x0010	/* Display on */
#घोषणा LCD_FLAG_F		0x0020	/* Large font mode */
#घोषणा LCD_FLAG_N		0x0040	/* 2-rows mode */
#घोषणा LCD_FLAG_L		0x0080	/* Backlight enabled */

क्रमागत अक्षरlcd_onoff अणु
	CHARLCD_OFF = 0,
	CHARLCD_ON,
पूर्ण;

क्रमागत अक्षरlcd_shअगरt_dir अणु
	CHARLCD_SHIFT_LEFT,
	CHARLCD_SHIFT_RIGHT,
पूर्ण;

क्रमागत अक्षरlcd_fontsize अणु
	CHARLCD_FONTSIZE_SMALL,
	CHARLCD_FONTSIZE_LARGE,
पूर्ण;

क्रमागत अक्षरlcd_lines अणु
	CHARLCD_LINES_1,
	CHARLCD_LINES_2,
पूर्ण;

काष्ठा अक्षरlcd अणु
	स्थिर काष्ठा अक्षरlcd_ops *ops;
	स्थिर अचिन्हित अक्षर *अक्षर_conv;	/* Optional */

	पूर्णांक height;
	पूर्णांक width;

	/* Contains the LCD X and Y offset */
	काष्ठा अणु
		अचिन्हित दीर्घ x;
		अचिन्हित दीर्घ y;
	पूर्ण addr;

	व्योम *drvdata;
पूर्ण;

/**
 * काष्ठा अक्षरlcd_ops - Functions used by अक्षरlcd. Drivers have to implement
 * these.
 * @backlight: Turn backlight on or off. Optional.
 * @prपूर्णांक: Prपूर्णांक one अक्षरacter to the display at current cursor position.
 * The buffered cursor position is advanced by अक्षरlcd. The cursor should not
 * wrap to the next line at the end of a line.
 * @जाओxy: Set cursor to x, y. The x and y values to set the cursor to are
 * previously set in addr.x and addr.y by अक्षरlcd.
 * @home: Set cursor to 0, 0. The values in addr.x and addr.y are set to 0, 0 by
 * अक्षरlcd prior to calling this function.
 * @clear_display: Clear the whole display and set the cursor to 0, 0. The
 * values in addr.x and addr.y are set to 0, 0 by अक्षरlcd after to calling this
 * function.
 * @init_display: Initialize the display.
 * @shअगरt_cursor: Shअगरt cursor left or right one position.
 * @shअगरt_display: Shअगरt whole display content left or right.
 * @display: Turn display on or off.
 * @cursor: Turn cursor on or off.
 * @blink: Turn cursor blink on or off.
 * @lines: One or two lines.
 * @redefine_अक्षर: Redefine the actual pixel matrix of अक्षरacter.
 */
काष्ठा अक्षरlcd_ops अणु
	व्योम (*backlight)(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_onoff on);
	पूर्णांक (*prपूर्णांक)(काष्ठा अक्षरlcd *lcd, पूर्णांक c);
	पूर्णांक (*जाओxy)(काष्ठा अक्षरlcd *lcd, अचिन्हित पूर्णांक x, अचिन्हित पूर्णांक y);
	पूर्णांक (*home)(काष्ठा अक्षरlcd *lcd);
	पूर्णांक (*clear_display)(काष्ठा अक्षरlcd *lcd);
	पूर्णांक (*init_display)(काष्ठा अक्षरlcd *lcd);
	पूर्णांक (*shअगरt_cursor)(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_shअगरt_dir dir);
	पूर्णांक (*shअगरt_display)(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_shअगरt_dir dir);
	पूर्णांक (*display)(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_onoff on);
	पूर्णांक (*cursor)(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_onoff on);
	पूर्णांक (*blink)(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_onoff on);
	पूर्णांक (*fontsize)(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_fontsize size);
	पूर्णांक (*lines)(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_lines lines);
	पूर्णांक (*redefine_अक्षर)(काष्ठा अक्षरlcd *lcd, अक्षर *esc);
पूर्ण;

व्योम अक्षरlcd_backlight(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_onoff on);
काष्ठा अक्षरlcd *अक्षरlcd_alloc(व्योम);
व्योम अक्षरlcd_मुक्त(काष्ठा अक्षरlcd *lcd);

पूर्णांक अक्षरlcd_रेजिस्टर(काष्ठा अक्षरlcd *lcd);
पूर्णांक अक्षरlcd_unरेजिस्टर(काष्ठा अक्षरlcd *lcd);

व्योम अक्षरlcd_poke(काष्ठा अक्षरlcd *lcd);

#पूर्ण_अगर /* CHARLCD_H */
