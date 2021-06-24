<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright (c) 2010 Samsung Electronics
 *  Kyungmin Park <kyungmin.park@samsung.com>
 *  Marek Szyprowski <m.szyprowski@samsung.com>
 *
 * Samsung OneNAD Controller core functions
 */

#अगर_अघोषित __ASM_ARCH_ONEन_अंकD_CORE_S3C64XX_H
#घोषणा __ASM_ARCH_ONEन_अंकD_CORE_S3C64XX_H __खाता__

/* These functions are only क्रम use with the core support code, such as
 * the cpu specअगरic initialisation code
 */

/* re-define device name depending on support. */
अटल अंतरभूत व्योम s3c_onenand_setname(अक्षर *name)
अणु
#अगर_घोषित CONFIG_S3C_DEV_ONEन_अंकD
	s3c_device_onenand.name = name;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम s3c64xx_onenand1_setname(अक्षर *name)
अणु
#अगर_घोषित CONFIG_S3C64XX_DEV_ONEन_अंकD1
	s3c64xx_device_onenand1.name = name;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* __ASM_ARCH_ONEन_अंकD_CORE_S3C64XX_H */
