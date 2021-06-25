<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Intel LPSS core support.
 *
 * Copyright (C) 2015, Intel Corporation
 *
 * Authors: Andy Shevchenko <andriy.shevchenko@linux.पूर्णांकel.com>
 *          Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#अगर_अघोषित __MFD_INTEL_LPSS_H
#घोषणा __MFD_INTEL_LPSS_H

#समावेश <linux/pm.h>

काष्ठा device;
काष्ठा resource;
काष्ठा software_node;

काष्ठा पूर्णांकel_lpss_platक्रमm_info अणु
	काष्ठा resource *mem;
	पूर्णांक irq;
	अचिन्हित दीर्घ clk_rate;
	स्थिर अक्षर *clk_con_id;
	स्थिर काष्ठा software_node *swnode;
पूर्ण;

पूर्णांक पूर्णांकel_lpss_probe(काष्ठा device *dev,
		     स्थिर काष्ठा पूर्णांकel_lpss_platक्रमm_info *info);
व्योम पूर्णांकel_lpss_हटाओ(काष्ठा device *dev);

#अगर_घोषित CONFIG_PM
पूर्णांक पूर्णांकel_lpss_prepare(काष्ठा device *dev);
पूर्णांक पूर्णांकel_lpss_suspend(काष्ठा device *dev);
पूर्णांक पूर्णांकel_lpss_resume(काष्ठा device *dev);

#अगर_घोषित CONFIG_PM_SLEEP
#घोषणा INTEL_LPSS_SLEEP_PM_OPS			\
	.prepare = पूर्णांकel_lpss_prepare,		\
	SET_LATE_SYSTEM_SLEEP_PM_OPS(पूर्णांकel_lpss_suspend, पूर्णांकel_lpss_resume)
#अन्यथा
#घोषणा INTEL_LPSS_SLEEP_PM_OPS
#पूर्ण_अगर

#घोषणा INTEL_LPSS_RUNTIME_PM_OPS		\
	.runसमय_suspend = पूर्णांकel_lpss_suspend,	\
	.runसमय_resume = पूर्णांकel_lpss_resume,

#अन्यथा /* !CONFIG_PM */
#घोषणा INTEL_LPSS_SLEEP_PM_OPS
#घोषणा INTEL_LPSS_RUNTIME_PM_OPS
#पूर्ण_अगर /* CONFIG_PM */

#घोषणा INTEL_LPSS_PM_OPS(name)			\
स्थिर काष्ठा dev_pm_ops name = अणु		\
	INTEL_LPSS_SLEEP_PM_OPS			\
	INTEL_LPSS_RUNTIME_PM_OPS		\
पूर्ण

#पूर्ण_अगर /* __MFD_INTEL_LPSS_H */
