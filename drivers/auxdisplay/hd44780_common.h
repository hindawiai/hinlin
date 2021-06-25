<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */

#घोषणा DEFAULT_LCD_BWIDTH      40
#घोषणा DEFAULT_LCD_HWIDTH      64

काष्ठा hd44780_common अणु
	पूर्णांक अगरwidth;			/* 4-bit or 8-bit (शेष) */
	पूर्णांक bwidth;			/* Default set by hd44780_alloc() */
	पूर्णांक hwidth;			/* Default set by hd44780_alloc() */
	अचिन्हित दीर्घ hd44780_common_flags;
	व्योम (*ग_लिखो_data)(काष्ठा hd44780_common *hdc, पूर्णांक data);
	व्योम (*ग_लिखो_cmd)(काष्ठा hd44780_common *hdc, पूर्णांक cmd);
	/* ग_लिखो_cmd_raw4 is क्रम 4-bit connected displays only */
	व्योम (*ग_लिखो_cmd_raw4)(काष्ठा hd44780_common *hdc, पूर्णांक cmd);
	व्योम *hd44780;
पूर्ण;

पूर्णांक hd44780_common_prपूर्णांक(काष्ठा अक्षरlcd *lcd, पूर्णांक c);
पूर्णांक hd44780_common_जाओxy(काष्ठा अक्षरlcd *lcd, अचिन्हित पूर्णांक x, अचिन्हित पूर्णांक y);
पूर्णांक hd44780_common_home(काष्ठा अक्षरlcd *lcd);
पूर्णांक hd44780_common_clear_display(काष्ठा अक्षरlcd *lcd);
पूर्णांक hd44780_common_init_display(काष्ठा अक्षरlcd *lcd);
पूर्णांक hd44780_common_shअगरt_cursor(काष्ठा अक्षरlcd *lcd,
		क्रमागत अक्षरlcd_shअगरt_dir dir);
पूर्णांक hd44780_common_shअगरt_display(काष्ठा अक्षरlcd *lcd,
		क्रमागत अक्षरlcd_shअगरt_dir dir);
पूर्णांक hd44780_common_display(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_onoff on);
पूर्णांक hd44780_common_cursor(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_onoff on);
पूर्णांक hd44780_common_blink(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_onoff on);
पूर्णांक hd44780_common_fontsize(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_fontsize size);
पूर्णांक hd44780_common_lines(काष्ठा अक्षरlcd *lcd, क्रमागत अक्षरlcd_lines lines);
पूर्णांक hd44780_common_redefine_अक्षर(काष्ठा अक्षरlcd *lcd, अक्षर *esc);
काष्ठा hd44780_common *hd44780_common_alloc(व्योम);
