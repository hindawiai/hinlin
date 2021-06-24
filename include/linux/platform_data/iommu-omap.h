<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * omap iommu: मुख्य काष्ठाures
 *
 * Copyright (C) 2008-2009 Nokia Corporation
 *
 * Written by Hiroshi DOYU <Hiroshi.DOYU@nokia.com>
 */

#समावेश <linux/platक्रमm_device.h>

काष्ठा iommu_platक्रमm_data अणु
	स्थिर अक्षर *reset_name;
	पूर्णांक (*निश्चित_reset)(काष्ठा platक्रमm_device *pdev, स्थिर अक्षर *name);
	पूर्णांक (*deनिश्चित_reset)(काष्ठा platक्रमm_device *pdev, स्थिर अक्षर *name);
	पूर्णांक (*device_enable)(काष्ठा platक्रमm_device *pdev);
	पूर्णांक (*device_idle)(काष्ठा platक्रमm_device *pdev);
	पूर्णांक (*set_pwrdm_स्थिरraपूर्णांक)(काष्ठा platक्रमm_device *pdev, bool request,
				    u8 *pwrst);
पूर्ण;
