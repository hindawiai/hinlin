<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2004 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Written by Ben Dooks, <ben@simtec.co.uk>
 */

/* s3c_pm_init
 *
 * called from board at initialisation समय to setup the घातer
 * management
*/

#समावेश "pm-common.h"

काष्ठा device;

#अगर_घोषित CONFIG_SAMSUNG_PM

बाह्य __init पूर्णांक s3c_pm_init(व्योम);
बाह्य __init पूर्णांक s3c64xx_pm_init(व्योम);

#अन्यथा

अटल अंतरभूत पूर्णांक s3c_pm_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक s3c64xx_pm_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* configuration क्रम the IRQ mask over sleep */
बाह्य अचिन्हित दीर्घ s3c_irqwake_पूर्णांकmask;
बाह्य अचिन्हित दीर्घ s3c_irqwake_eपूर्णांकmask;

/* per-cpu sleep functions */

बाह्य व्योम (*pm_cpu_prep)(व्योम);
बाह्य पूर्णांक (*pm_cpu_sleep)(अचिन्हित दीर्घ);

/* Flags क्रम PM Control */

बाह्य अचिन्हित दीर्घ s3c_pm_flags;

/* from sleep.S */

बाह्य पूर्णांक s3c2410_cpu_suspend(अचिन्हित दीर्घ);

#अगर_घोषित CONFIG_PM_SLEEP
बाह्य पूर्णांक s3c_irq_wake(काष्ठा irq_data *data, अचिन्हित पूर्णांक state);
बाह्य व्योम s3c_cpu_resume(व्योम);
#अन्यथा
#घोषणा s3c_irq_wake शून्य
#घोषणा s3c_cpu_resume शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_SAMSUNG_PM
बाह्य पूर्णांक s3c_irqext_wake(काष्ठा irq_data *data, अचिन्हित पूर्णांक state);
#अन्यथा
#घोषणा s3c_irqext_wake शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_S3C_PM_DEBUG_LED_SMDK
/**
 * s3c_pm_debug_smdkled() - Debug PM suspend/resume via SMDK Board LEDs
 * @set: set bits क्रम the state of the LEDs
 * @clear: clear bits क्रम the state of the LEDs.
 */
बाह्य व्योम s3c_pm_debug_smdkled(u32 set, u32 clear);

#अन्यथा
अटल अंतरभूत व्योम s3c_pm_debug_smdkled(u32 set, u32 clear) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_S3C_PM_DEBUG_LED_SMDK */

/**
 * s3c_pm_configure_extपूर्णांक() - ensure pins are correctly set क्रम IRQ
 *
 * Setup all the necessary GPIO pins क्रम waking the प्रणाली on बाह्यal
 * पूर्णांकerrupt.
 */
बाह्य व्योम s3c_pm_configure_extपूर्णांक(व्योम);

#अगर_घोषित CONFIG_GPIO_SAMSUNG
/**
 * samsung_pm_restore_gpios() - restore the state of the gpios after sleep.
 *
 * Restore the state of the GPIO pins after sleep, which may involve ensuring
 * that we करो not glitch the state of the pins from that the bootloader's
 * resume code has करोne.
*/
बाह्य व्योम samsung_pm_restore_gpios(व्योम);

/**
 * samsung_pm_save_gpios() - save the state of the GPIOs क्रम restoring after sleep.
 *
 * Save the GPIO states क्रम resotration on resume. See samsung_pm_restore_gpios().
 */
बाह्य व्योम samsung_pm_save_gpios(व्योम);
#अन्यथा
अटल अंतरभूत व्योम samsung_pm_restore_gpios(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम samsung_pm_save_gpios(व्योम) अणुपूर्ण
#पूर्ण_अगर

बाह्य व्योम s3c_pm_save_core(व्योम);
बाह्य व्योम s3c_pm_restore_core(व्योम);
