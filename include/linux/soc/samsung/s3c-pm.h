<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *	Tomasz Figa <t.figa@samsung.com>
 * Copyright (c) 2004 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Written by Ben Dooks, <ben@simtec.co.uk>
 */

#अगर_अघोषित __LINUX_SOC_SAMSUNG_S3C_PM_H
#घोषणा __LINUX_SOC_SAMSUNG_S3C_PM_H __खाता__

#समावेश <linux/types.h>

/* PM debug functions */

/**
 * काष्ठा pm_uart_save - save block क्रम core UART
 * @ulcon: Save value क्रम S3C2410_ULCON
 * @ucon: Save value क्रम S3C2410_UCON
 * @ufcon: Save value क्रम S3C2410_UFCON
 * @umcon: Save value क्रम S3C2410_UMCON
 * @ubrभाग: Save value क्रम S3C2410_UBRDIV
 *
 * Save block क्रम UART रेजिस्टरs to be held over sleep and restored अगर they
 * are needed (say by debug).
*/
काष्ठा pm_uart_save अणु
	u32	ulcon;
	u32	ucon;
	u32	ufcon;
	u32	umcon;
	u32	ubrभाग;
	u32	uभागslot;
पूर्ण;

#अगर_घोषित CONFIG_SAMSUNG_PM_DEBUG
/**
 * s3c_pm_dbg() - low level debug function क्रम use in suspend/resume.
 * @msg: The message to prपूर्णांक.
 *
 * This function is used मुख्यly to debug the resume process beक्रमe the प्रणाली
 * can rely on prपूर्णांकk/console output. It uses the low-level debugging output
 * routine prपूर्णांकascii() to करो its work.
 */
बाह्य व्योम s3c_pm_dbg(स्थिर अक्षर *msg, ...);

#घोषणा S3C_PMDBG(fmt...) s3c_pm_dbg(fmt)

बाह्य व्योम s3c_pm_save_uarts(bool is_s3c24xx);
बाह्य व्योम s3c_pm_restore_uarts(bool is_s3c24xx);

#अगर_घोषित CONFIG_ARCH_S3C64XX
बाह्य व्योम s3c_pm_arch_update_uart(व्योम __iomem *regs,
				    काष्ठा pm_uart_save *save);
#अन्यथा
अटल अंतरभूत व्योम
s3c_pm_arch_update_uart(व्योम __iomem *regs, काष्ठा pm_uart_save *save)
अणु
पूर्ण
#पूर्ण_अगर

#अन्यथा
#घोषणा S3C_PMDBG(fmt...) pr_debug(fmt)

अटल अंतरभूत व्योम s3c_pm_save_uarts(bool is_s3c24xx) अणु पूर्ण
अटल अंतरभूत व्योम s3c_pm_restore_uarts(bool is_s3c24xx) अणु पूर्ण
#पूर्ण_अगर

/* suspend memory checking */

#अगर_घोषित CONFIG_SAMSUNG_PM_CHECK
बाह्य व्योम s3c_pm_check_prepare(व्योम);
बाह्य व्योम s3c_pm_check_restore(व्योम);
बाह्य व्योम s3c_pm_check_cleanup(व्योम);
बाह्य व्योम s3c_pm_check_store(व्योम);
#अन्यथा
#घोषणा s3c_pm_check_prepare() करो अणु पूर्ण जबतक (0)
#घोषणा s3c_pm_check_restore() करो अणु पूर्ण जबतक (0)
#घोषणा s3c_pm_check_cleanup() करो अणु पूर्ण जबतक (0)
#घोषणा s3c_pm_check_store()   करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/* प्रणाली device subप्रणालीs */

बाह्य काष्ठा bus_type s3c2410_subsys;
बाह्य काष्ठा bus_type s3c2410a_subsys;
बाह्य काष्ठा bus_type s3c2412_subsys;
बाह्य काष्ठा bus_type s3c2416_subsys;
बाह्य काष्ठा bus_type s3c2440_subsys;
बाह्य काष्ठा bus_type s3c2442_subsys;
बाह्य काष्ठा bus_type s3c2443_subsys;

#पूर्ण_अगर
