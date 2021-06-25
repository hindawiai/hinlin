<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2010 Samsung Electronics Co., Ltd.
 *	Pawel Osciak <p.osciak@samsung.com>
 *
 * Samsung framebuffer driver core functions
 */
#अगर_अघोषित __ASM_PLAT_FB_CORE_S3C24XX_H
#घोषणा __ASM_PLAT_FB_CORE_S3C24XX_H __खाता__

/*
 * These functions are only क्रम use with the core support code, such as
 * the CPU-specअगरic initialization code.
 */

/* Re-define device name depending on support. */
अटल अंतरभूत व्योम s3c_fb_setname(अक्षर *name)
अणु
#अगर_घोषित CONFIG_S3C_DEV_FB
	s3c_device_fb.name = name;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* __ASM_PLAT_FB_CORE_S3C24XX_H */
