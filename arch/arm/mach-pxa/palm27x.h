<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Common functions क्रम Palm LD, T5, TX, Z72
 *
 * Copyright (C) 2010
 * Marek Vasut <marek.vasut@gmail.com>
 */
#अगर_अघोषित	__INCLUDE_MACH_PALM27X__
#घोषणा	__INCLUDE_MACH_PALM27X__

#समावेश <linux/gpio/machine.h>

#अगर defined(CONFIG_MMC_PXA) || defined(CONFIG_MMC_PXA_MODULE)
बाह्य व्योम __init palm27x_mmc_init(काष्ठा gpiod_lookup_table *gtable);
#अन्यथा
अटल अंतरभूत व्योम palm27x_mmc_init(काष्ठा gpiod_lookup_table *gtable)
अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_SUSPEND)
बाह्य व्योम __init palm27x_pm_init(अचिन्हित दीर्घ str_base);
#अन्यथा
अटल अंतरभूत व्योम palm27x_pm_init(अचिन्हित दीर्घ str_base) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_FB_PXA) || defined(CONFIG_FB_PXA_MODULE)
बाह्य काष्ठा pxafb_mode_info palm_320x480_lcd_mode;
बाह्य काष्ठा pxafb_mode_info palm_320x320_lcd_mode;
बाह्य काष्ठा pxafb_mode_info palm_320x320_new_lcd_mode;
बाह्य व्योम __init palm27x_lcd_init(पूर्णांक घातer,
					काष्ठा pxafb_mode_info *mode);
#अन्यथा
#घोषणा palm27x_lcd_init(घातer, mode)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#अगर	defined(CONFIG_USB_PXA27X) || \
	defined(CONFIG_USB_PXA27X_MODULE)
बाह्य व्योम __init palm27x_udc_init(पूर्णांक vbus, पूर्णांक pullup,
					पूर्णांक vbus_inverted);
#अन्यथा
अटल अंतरभूत व्योम palm27x_udc_init(पूर्णांक vbus, पूर्णांक pullup, पूर्णांक vbus_inverted) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_IRDA) || defined(CONFIG_IRDA_MODULE)
बाह्य व्योम __init palm27x_irda_init(पूर्णांक pwdn);
#अन्यथा
अटल अंतरभूत व्योम palm27x_irda_init(पूर्णांक pwdn) अणुपूर्ण
#पूर्ण_अगर

#अगर	defined(CONFIG_TOUCHSCREEN_WM97XX) || \
	defined(CONFIG_TOUCHSCREEN_WM97XX_MODULE)
बाह्य व्योम __init palm27x_ac97_init(पूर्णांक minv, पूर्णांक maxv, पूर्णांक jack,
					पूर्णांक reset);
#अन्यथा
अटल अंतरभूत व्योम palm27x_ac97_init(पूर्णांक minv, पूर्णांक maxv, पूर्णांक jack, पूर्णांक reset) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_BACKLIGHT_PWM) || defined(CONFIG_BACKLIGHT_PWM_MODULE)
बाह्य व्योम __init palm27x_pwm_init(पूर्णांक bl, पूर्णांक lcd);
#अन्यथा
अटल अंतरभूत व्योम palm27x_pwm_init(पूर्णांक bl, पूर्णांक lcd) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PDA_POWER) || defined(CONFIG_PDA_POWER_MODULE)
बाह्य व्योम __init palm27x_घातer_init(पूर्णांक ac, पूर्णांक usb);
#अन्यथा
अटल अंतरभूत व्योम palm27x_घातer_init(पूर्णांक ac, पूर्णांक usb) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_REGULATOR_MAX1586) || \
    defined(CONFIG_REGULATOR_MAX1586_MODULE)
बाह्य व्योम __init palm27x_pmic_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम palm27x_pmic_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* __INCLUDE_MACH_PALM27X__ */
