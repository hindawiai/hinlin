<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *	Tomasz Figa <t.figa@samsung.com>
 * Copyright (c) 2004 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Written by Ben Dooks, <ben@simtec.co.uk>
 */

#अगर_अघोषित __PLAT_SAMSUNG_PM_COMMON_H
#घोषणा __PLAT_SAMSUNG_PM_COMMON_H __खाता__

#समावेश <linux/irq.h>
#समावेश <linux/soc/samsung/s3c-pm.h>

/* sleep save info */

/**
 * काष्ठा sleep_save - save inक्रमmation क्रम shared peripherals.
 * @reg: Poपूर्णांकer to the रेजिस्टर to save.
 * @val: Holder क्रम the value saved from reg.
 *
 * This describes a list of रेजिस्टरs which is used by the pm core and
 * other subप्रणाली to save and restore रेजिस्टर values over suspend.
 */
काष्ठा sleep_save अणु
	व्योम __iomem	*reg;
	अचिन्हित दीर्घ	val;
पूर्ण;

#घोषणा SAVE_ITEM(x) \
	अणु .reg = (x) पूर्ण

/* helper functions to save/restore lists of रेजिस्टरs. */

बाह्य व्योम s3c_pm_करो_save(काष्ठा sleep_save *ptr, पूर्णांक count);
बाह्य व्योम s3c_pm_करो_restore(स्थिर काष्ठा sleep_save *ptr, पूर्णांक count);
बाह्य व्योम s3c_pm_करो_restore_core(स्थिर काष्ठा sleep_save *ptr, पूर्णांक count);

#पूर्ण_अगर
