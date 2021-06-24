<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Samsung CF-ATA Controller core functions
 */

#अगर_अघोषित __ASM_PLAT_ATA_CORE_S3C64XX_H
#घोषणा __ASM_PLAT_ATA_CORE_S3C64XX_H __खाता__

/* These functions are only क्रम use with the core support code, such as
 * the cpu specअगरic initialisation code
*/

/* re-define device name depending on support. */
अटल अंतरभूत व्योम s3c_cfcon_setname(अक्षर *name)
अणु
#अगर_घोषित CONFIG_SAMSUNG_DEV_IDE
	s3c_device_cfcon.name = name;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* __ASM_PLAT_ATA_CORE_S3C64XX_H */
