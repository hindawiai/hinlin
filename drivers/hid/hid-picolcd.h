<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/***************************************************************************
 *   Copyright (C) 2010-2012 by Bruno Prथऊmont <bonbons@linux-vserver.org>  *
 *                                                                         *
 *   Based on Logitech G13 driver (v0.4)                                   *
 *     Copyright (C) 2009 by Rick L. Vinyard, Jr. <rvinyard@cs.nmsu.edu>   *
 *                                                                         *
 ***************************************************************************/

#घोषणा PICOLCD_NAME "PicoLCD (graphic)"

/* Report numbers */
#घोषणा REPORT_ERROR_CODE      0x10 /* LCD: IN[16]  */
#घोषणा   ERR_SUCCESS            0x00
#घोषणा   ERR_PARAMETER_MISSING  0x01
#घोषणा   ERR_DATA_MISSING       0x02
#घोषणा   ERR_BLOCK_READ_ONLY    0x03
#घोषणा   ERR_BLOCK_NOT_ERASABLE 0x04
#घोषणा   ERR_BLOCK_TOO_BIG      0x05
#घोषणा   ERR_SECTION_OVERFLOW   0x06
#घोषणा   ERR_INVALID_CMD_LEN    0x07
#घोषणा   ERR_INVALID_DATA_LEN   0x08
#घोषणा REPORT_KEY_STATE       0x11 /* LCD: IN[2]   */
#घोषणा REPORT_IR_DATA         0x21 /* LCD: IN[63]  */
#घोषणा REPORT_EE_DATA         0x32 /* LCD: IN[63]  */
#घोषणा REPORT_MEMORY          0x41 /* LCD: IN[63]  */
#घोषणा REPORT_LED_STATE       0x81 /* LCD: OUT[1]  */
#घोषणा REPORT_BRIGHTNESS      0x91 /* LCD: OUT[1]  */
#घोषणा REPORT_CONTRAST        0x92 /* LCD: OUT[1]  */
#घोषणा REPORT_RESET           0x93 /* LCD: OUT[2]  */
#घोषणा REPORT_LCD_CMD         0x94 /* LCD: OUT[63] */
#घोषणा REPORT_LCD_DATA        0x95 /* LCD: OUT[63] */
#घोषणा REPORT_LCD_CMD_DATA    0x96 /* LCD: OUT[63] */
#घोषणा	REPORT_EE_READ         0xa3 /* LCD: OUT[63] */
#घोषणा REPORT_EE_WRITE        0xa4 /* LCD: OUT[63] */
#घोषणा REPORT_ERASE_MEMORY    0xb2 /* LCD: OUT[2]  */
#घोषणा REPORT_READ_MEMORY     0xb3 /* LCD: OUT[3]  */
#घोषणा REPORT_WRITE_MEMORY    0xb4 /* LCD: OUT[63] */
#घोषणा REPORT_SPLASH_RESTART  0xc1 /* LCD: OUT[1]  */
#घोषणा REPORT_EXIT_KEYBOARD   0xef /* LCD: OUT[2]  */
#घोषणा REPORT_VERSION         0xf1 /* LCD: IN[2],OUT[1]    Bootloader: IN[2],OUT[1]   */
#घोषणा REPORT_BL_ERASE_MEMORY 0xf2 /*                      Bootloader: IN[36],OUT[4]  */
#घोषणा REPORT_BL_READ_MEMORY  0xf3 /*                      Bootloader: IN[36],OUT[4]  */
#घोषणा REPORT_BL_WRITE_MEMORY 0xf4 /*                      Bootloader: IN[36],OUT[36] */
#घोषणा REPORT_DEVID           0xf5 /* LCD: IN[5], OUT[1]   Bootloader: IN[5],OUT[1]   */
#घोषणा REPORT_SPLASH_SIZE     0xf6 /* LCD: IN[4], OUT[1]   */
#घोषणा REPORT_HOOK_VERSION    0xf7 /* LCD: IN[2], OUT[1]   */
#घोषणा REPORT_EXIT_FLASHER    0xff /*                      Bootloader: OUT[2]         */

/* Description of in-progress IO operation, used क्रम operations
 * that trigger response from device */
काष्ठा picolcd_pending अणु
	काष्ठा hid_report *out_report;
	काष्ठा hid_report *in_report;
	काष्ठा completion पढ़ोy;
	पूर्णांक raw_size;
	u8 raw_data[64];
पूर्ण;


#घोषणा PICOLCD_KEYS 17

/* Per device data काष्ठाure */
काष्ठा picolcd_data अणु
	काष्ठा hid_device *hdev;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debug_reset;
	काष्ठा dentry *debug_eeprom;
	काष्ठा dentry *debug_flash;
	काष्ठा mutex mutex_flash;
	पूर्णांक addr_sz;
#पूर्ण_अगर
	u8 version[2];
	अचिन्हित लघु opmode_delay;
	/* input stuff */
	u8 pressed_keys[2];
	काष्ठा input_dev *input_keys;
#अगर_घोषित CONFIG_HID_PICOLCD_CIR
	काष्ठा rc_dev *rc_dev;
#पूर्ण_अगर
	अचिन्हित लघु keycode[PICOLCD_KEYS];

#अगर_घोषित CONFIG_HID_PICOLCD_FB
	/* Framebuffer stuff */
	काष्ठा fb_info *fb_info;
#पूर्ण_अगर /* CONFIG_HID_PICOLCD_FB */
#अगर_घोषित CONFIG_HID_PICOLCD_LCD
	काष्ठा lcd_device *lcd;
	u8 lcd_contrast;
#पूर्ण_अगर /* CONFIG_HID_PICOLCD_LCD */
#अगर_घोषित CONFIG_HID_PICOLCD_BACKLIGHT
	काष्ठा backlight_device *backlight;
	u8 lcd_brightness;
	u8 lcd_घातer;
#पूर्ण_अगर /* CONFIG_HID_PICOLCD_BACKLIGHT */
#अगर_घोषित CONFIG_HID_PICOLCD_LEDS
	/* LED stuff */
	u8 led_state;
	काष्ठा led_classdev *led[8];
#पूर्ण_अगर /* CONFIG_HID_PICOLCD_LEDS */

	/* Housekeeping stuff */
	spinlock_t lock;
	काष्ठा mutex mutex;
	काष्ठा picolcd_pending *pending;
	पूर्णांक status;
#घोषणा PICOLCD_BOOTLOADER 1
#घोषणा PICOLCD_FAILED 2
#घोषणा PICOLCD_CIR_SHUN 4
पूर्ण;

#अगर_घोषित CONFIG_HID_PICOLCD_FB
काष्ठा picolcd_fb_data अणु
	/* Framebuffer stuff */
	spinlock_t lock;
	काष्ठा picolcd_data *picolcd;
	u8 update_rate;
	u8 bpp;
	u8 क्रमce;
	u8 पढ़ोy;
	u8 *vbiपंचांगap;		/* local copy of what was sent to PicoLCD */
	u8 *biपंचांगap;		/* framebuffer */
पूर्ण;
#पूर्ण_अगर /* CONFIG_HID_PICOLCD_FB */

/* Find a given report */
#घोषणा picolcd_in_report(id, dev) picolcd_report(id, dev, HID_INPUT_REPORT)
#घोषणा picolcd_out_report(id, dev) picolcd_report(id, dev, HID_OUTPUT_REPORT)

काष्ठा hid_report *picolcd_report(पूर्णांक id, काष्ठा hid_device *hdev, पूर्णांक dir);

#अगर_घोषित CONFIG_DEBUG_FS
व्योम picolcd_debug_out_report(काष्ठा picolcd_data *data,
		काष्ठा hid_device *hdev, काष्ठा hid_report *report);
#घोषणा hid_hw_request(a, b, c) \
	करो अणु \
		picolcd_debug_out_report(hid_get_drvdata(a), a, b); \
		hid_hw_request(a, b, c); \
	पूर्ण जबतक (0)

व्योम picolcd_debug_raw_event(काष्ठा picolcd_data *data,
		काष्ठा hid_device *hdev, काष्ठा hid_report *report,
		u8 *raw_data, पूर्णांक size);

व्योम picolcd_init_devfs(काष्ठा picolcd_data *data,
		काष्ठा hid_report *eeprom_r, काष्ठा hid_report *eeprom_w,
		काष्ठा hid_report *flash_r, काष्ठा hid_report *flash_w,
		काष्ठा hid_report *reset);

व्योम picolcd_निकास_devfs(काष्ठा picolcd_data *data);
#अन्यथा
अटल अंतरभूत व्योम picolcd_debug_out_report(काष्ठा picolcd_data *data,
		काष्ठा hid_device *hdev, काष्ठा hid_report *report)
अणु
पूर्ण
अटल अंतरभूत व्योम picolcd_debug_raw_event(काष्ठा picolcd_data *data,
		काष्ठा hid_device *hdev, काष्ठा hid_report *report,
		u8 *raw_data, पूर्णांक size)
अणु
पूर्ण
अटल अंतरभूत व्योम picolcd_init_devfs(काष्ठा picolcd_data *data,
		काष्ठा hid_report *eeprom_r, काष्ठा hid_report *eeprom_w,
		काष्ठा hid_report *flash_r, काष्ठा hid_report *flash_w,
		काष्ठा hid_report *reset)
अणु
पूर्ण
अटल अंतरभूत व्योम picolcd_निकास_devfs(काष्ठा picolcd_data *data)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */


#अगर_घोषित CONFIG_HID_PICOLCD_FB
पूर्णांक picolcd_fb_reset(काष्ठा picolcd_data *data, पूर्णांक clear);

पूर्णांक picolcd_init_framebuffer(काष्ठा picolcd_data *data);

व्योम picolcd_निकास_framebuffer(काष्ठा picolcd_data *data);

व्योम picolcd_fb_refresh(काष्ठा picolcd_data *data);
#घोषणा picolcd_fbinfo(d) ((d)->fb_info)
#अन्यथा
अटल अंतरभूत पूर्णांक picolcd_fb_reset(काष्ठा picolcd_data *data, पूर्णांक clear)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक picolcd_init_framebuffer(काष्ठा picolcd_data *data)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम picolcd_निकास_framebuffer(काष्ठा picolcd_data *data)
अणु
पूर्ण
अटल अंतरभूत व्योम picolcd_fb_refresh(काष्ठा picolcd_data *data)
अणु
पूर्ण
#घोषणा picolcd_fbinfo(d) शून्य
#पूर्ण_अगर /* CONFIG_HID_PICOLCD_FB */


#अगर_घोषित CONFIG_HID_PICOLCD_BACKLIGHT
पूर्णांक picolcd_init_backlight(काष्ठा picolcd_data *data,
		काष्ठा hid_report *report);

व्योम picolcd_निकास_backlight(काष्ठा picolcd_data *data);

पूर्णांक picolcd_resume_backlight(काष्ठा picolcd_data *data);

व्योम picolcd_suspend_backlight(काष्ठा picolcd_data *data);
#अन्यथा
अटल अंतरभूत पूर्णांक picolcd_init_backlight(काष्ठा picolcd_data *data,
		काष्ठा hid_report *report)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम picolcd_निकास_backlight(काष्ठा picolcd_data *data)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक picolcd_resume_backlight(काष्ठा picolcd_data *data)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम picolcd_suspend_backlight(काष्ठा picolcd_data *data)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_HID_PICOLCD_BACKLIGHT */


#अगर_घोषित CONFIG_HID_PICOLCD_LCD
पूर्णांक picolcd_init_lcd(काष्ठा picolcd_data *data,
		काष्ठा hid_report *report);

व्योम picolcd_निकास_lcd(काष्ठा picolcd_data *data);

पूर्णांक picolcd_resume_lcd(काष्ठा picolcd_data *data);
#अन्यथा
अटल अंतरभूत पूर्णांक picolcd_init_lcd(काष्ठा picolcd_data *data,
		काष्ठा hid_report *report)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम picolcd_निकास_lcd(काष्ठा picolcd_data *data)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक picolcd_resume_lcd(काष्ठा picolcd_data *data)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_HID_PICOLCD_LCD */


#अगर_घोषित CONFIG_HID_PICOLCD_LEDS
पूर्णांक picolcd_init_leds(काष्ठा picolcd_data *data,
		काष्ठा hid_report *report);

व्योम picolcd_निकास_leds(काष्ठा picolcd_data *data);

व्योम picolcd_leds_set(काष्ठा picolcd_data *data);
#अन्यथा
अटल अंतरभूत पूर्णांक picolcd_init_leds(काष्ठा picolcd_data *data,
		काष्ठा hid_report *report)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम picolcd_निकास_leds(काष्ठा picolcd_data *data)
अणु
पूर्ण
अटल अंतरभूत व्योम picolcd_leds_set(काष्ठा picolcd_data *data)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_HID_PICOLCD_LEDS */


#अगर_घोषित CONFIG_HID_PICOLCD_CIR
पूर्णांक picolcd_raw_cir(काष्ठा picolcd_data *data,
		काष्ठा hid_report *report, u8 *raw_data, पूर्णांक size);

पूर्णांक picolcd_init_cir(काष्ठा picolcd_data *data, काष्ठा hid_report *report);

व्योम picolcd_निकास_cir(काष्ठा picolcd_data *data);
#अन्यथा
अटल अंतरभूत पूर्णांक picolcd_raw_cir(काष्ठा picolcd_data *data,
		काष्ठा hid_report *report, u8 *raw_data, पूर्णांक size)
अणु
	वापस 1;
पूर्ण
अटल अंतरभूत पूर्णांक picolcd_init_cir(काष्ठा picolcd_data *data, काष्ठा hid_report *report)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम picolcd_निकास_cir(काष्ठा picolcd_data *data)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_HID_PICOLCD_CIR */

पूर्णांक picolcd_reset(काष्ठा hid_device *hdev);
काष्ठा picolcd_pending *picolcd_send_and_रुको(काष्ठा hid_device *hdev,
			पूर्णांक report_id, स्थिर u8 *raw_data, पूर्णांक size);
