<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Common Header क्रम S3C24XX SoCs
 */

#अगर_अघोषित __ARCH_ARM_MACH_S3C24XX_COMMON_H
#घोषणा __ARCH_ARM_MACH_S3C24XX_COMMON_H __खाता__

#समावेश <linux/reboot.h>
#समावेश <mach/irqs.h>

काष्ठा s3c2410_uartcfg;

#अगर_घोषित CONFIG_CPU_S3C2410
बाह्य  पूर्णांक s3c2410_init(व्योम);
बाह्य  पूर्णांक s3c2410a_init(व्योम);
बाह्य व्योम s3c2410_map_io(व्योम);
बाह्य व्योम s3c2410_init_uarts(काष्ठा s3c2410_uartcfg *cfg, पूर्णांक no);
बाह्य व्योम s3c2410_init_घड़ीs(पूर्णांक xtal);
बाह्य व्योम s3c2410_init_irq(व्योम);
#अन्यथा
#घोषणा s3c2410_init_घड़ीs शून्य
#घोषणा s3c2410_init_uarts शून्य
#घोषणा s3c2410_map_io शून्य
#घोषणा s3c2410_init शून्य
#घोषणा s3c2410a_init शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_S3C2412
बाह्य  पूर्णांक s3c2412_init(व्योम);
बाह्य व्योम s3c2412_map_io(व्योम);
बाह्य व्योम s3c2412_init_uarts(काष्ठा s3c2410_uartcfg *cfg, पूर्णांक no);
बाह्य व्योम s3c2412_init_घड़ीs(पूर्णांक xtal);
बाह्य  पूर्णांक s3c2412_baseclk_add(व्योम);
बाह्य व्योम s3c2412_init_irq(व्योम);
#अन्यथा
#घोषणा s3c2412_init_घड़ीs शून्य
#घोषणा s3c2412_init_uarts शून्य
#घोषणा s3c2412_map_io शून्य
#घोषणा s3c2412_init शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_S3C2416
बाह्य  पूर्णांक s3c2416_init(व्योम);
बाह्य व्योम s3c2416_map_io(व्योम);
बाह्य व्योम s3c2416_init_uarts(काष्ठा s3c2410_uartcfg *cfg, पूर्णांक no);
बाह्य व्योम s3c2416_init_घड़ीs(पूर्णांक xtal);
बाह्य  पूर्णांक s3c2416_baseclk_add(व्योम);
बाह्य व्योम s3c2416_init_irq(व्योम);

बाह्य काष्ठा syscore_ops s3c2416_irq_syscore_ops;
#अन्यथा
#घोषणा s3c2416_init_घड़ीs शून्य
#घोषणा s3c2416_init_uarts शून्य
#घोषणा s3c2416_map_io शून्य
#घोषणा s3c2416_init शून्य
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_S3C2440) || defined(CONFIG_CPU_S3C2442)
बाह्य व्योम s3c244x_map_io(व्योम);
बाह्य व्योम s3c244x_init_uarts(काष्ठा s3c2410_uartcfg *cfg, पूर्णांक no);
#अन्यथा
#घोषणा s3c244x_init_uarts शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_S3C2440
बाह्य  पूर्णांक s3c2440_init(व्योम);
बाह्य व्योम s3c2440_map_io(व्योम);
बाह्य व्योम s3c2440_init_घड़ीs(पूर्णांक xtal);
बाह्य व्योम s3c2440_init_irq(व्योम);
#अन्यथा
#घोषणा s3c2440_init शून्य
#घोषणा s3c2440_map_io शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_S3C2442
बाह्य  पूर्णांक s3c2442_init(व्योम);
बाह्य व्योम s3c2442_map_io(व्योम);
बाह्य व्योम s3c2442_init_घड़ीs(पूर्णांक xtal);
बाह्य व्योम s3c2442_init_irq(व्योम);
#अन्यथा
#घोषणा s3c2442_init शून्य
#घोषणा s3c2442_map_io शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_S3C2443
बाह्य  पूर्णांक s3c2443_init(व्योम);
बाह्य व्योम s3c2443_map_io(व्योम);
बाह्य व्योम s3c2443_init_uarts(काष्ठा s3c2410_uartcfg *cfg, पूर्णांक no);
बाह्य व्योम s3c2443_init_घड़ीs(पूर्णांक xtal);
बाह्य  पूर्णांक s3c2443_baseclk_add(व्योम);
बाह्य व्योम s3c2443_init_irq(व्योम);
#अन्यथा
#घोषणा s3c2443_init_घड़ीs शून्य
#घोषणा s3c2443_init_uarts शून्य
#घोषणा s3c2443_map_io शून्य
#घोषणा s3c2443_init शून्य
#पूर्ण_अगर

बाह्य काष्ठा syscore_ops s3c24xx_irq_syscore_ops;

बाह्य काष्ठा platक्रमm_device s3c2410_device_dma;
बाह्य काष्ठा platक्रमm_device s3c2412_device_dma;
बाह्य काष्ठा platक्रमm_device s3c2440_device_dma;
बाह्य काष्ठा platक्रमm_device s3c2443_device_dma;

बाह्य काष्ठा platक्रमm_device s3c2410_device_dclk;

क्रमागत s3c24xx_समयr_mode अणु
	S3C24XX_PWM0,
	S3C24XX_PWM1,
	S3C24XX_PWM2,
	S3C24XX_PWM3,
	S3C24XX_PWM4,
पूर्ण;

बाह्य व्योम __init s3c24xx_set_समयr_source(क्रमागत s3c24xx_समयr_mode event,
					    क्रमागत s3c24xx_समयr_mode source);
बाह्य व्योम __init s3c24xx_समयr_init(व्योम);

#पूर्ण_अगर /* __ARCH_ARM_MACH_S3C24XX_COMMON_H */
