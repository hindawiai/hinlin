<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *	http://armlinux.simtec.co.uk/
 *
 * Common Header क्रम S3C64XX machines
 */

#अगर_अघोषित __ARCH_ARM_MACH_S3C64XX_COMMON_H
#घोषणा __ARCH_ARM_MACH_S3C64XX_COMMON_H

#समावेश <linux/reboot.h>

व्योम s3c64xx_init_irq(u32 vic0, u32 vic1);
व्योम s3c64xx_init_io(काष्ठा map_desc *mach_desc, पूर्णांक size);

काष्ठा device_node;
व्योम s3c64xx_set_xtal_freq(अचिन्हित दीर्घ freq);
व्योम s3c64xx_set_xusbxti_freq(अचिन्हित दीर्घ freq);

#अगर_घोषित CONFIG_CPU_S3C6400

बाह्य  पूर्णांक s3c6400_init(व्योम);
बाह्य व्योम s3c6400_init_irq(व्योम);
बाह्य व्योम s3c6400_map_io(व्योम);

#अन्यथा
#घोषणा s3c6400_map_io शून्य
#घोषणा s3c6400_init शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_S3C6410

बाह्य  पूर्णांक s3c6410_init(व्योम);
बाह्य व्योम s3c6410_init_irq(व्योम);
बाह्य व्योम s3c6410_map_io(व्योम);

#अन्यथा
#घोषणा s3c6410_map_io शून्य
#घोषणा s3c6410_init शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_S3C64XX_PL080
बाह्य काष्ठा pl08x_platक्रमm_data s3c64xx_dma0_plat_data;
बाह्य काष्ठा pl08x_platक्रमm_data s3c64xx_dma1_plat_data;
#पूर्ण_अगर

/* Samsung HR-Timer Clock mode */
क्रमागत s3c64xx_समयr_mode अणु
	S3C64XX_PWM0,
	S3C64XX_PWM1,
	S3C64XX_PWM2,
	S3C64XX_PWM3,
	S3C64XX_PWM4,
पूर्ण;

बाह्य व्योम __init s3c64xx_set_समयr_source(क्रमागत s3c64xx_समयr_mode event,
					    क्रमागत s3c64xx_समयr_mode source);
बाह्य व्योम __init s3c64xx_समयr_init(व्योम);

#पूर्ण_अगर /* __ARCH_ARM_MACH_S3C64XX_COMMON_H */
