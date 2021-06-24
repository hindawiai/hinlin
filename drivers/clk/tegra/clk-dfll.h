<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * clk-dfll.h - prototypes and macros क्रम the Tegra DFLL घड़ीsource driver
 * Copyright (C) 2013-2019 NVIDIA Corporation.  All rights reserved.
 *
 * Aleksandr Frid <afrid@nvidia.com>
 * Paul Walmsley <pwalmsley@nvidia.com>
 */

#अगर_अघोषित __DRIVERS_CLK_TEGRA_CLK_DFLL_H
#घोषणा __DRIVERS_CLK_TEGRA_CLK_DFLL_H

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/types.h>

#समावेश "cvb.h"

/**
 * काष्ठा tegra_dfll_soc_data - SoC-specअगरic hooks/पूर्णांकegration क्रम the DFLL driver
 * @dev: काष्ठा device * that holds the OPP table क्रम the DFLL
 * @max_freq: maximum frequency supported on this SoC
 * @cvb: CPU frequency table क्रम this SoC
 * @alignment: parameters of the regulator step and offset
 * @init_घड़ी_प्रकारrimmers: callback to initialize घड़ी trimmers
 * @set_घड़ी_प्रकारrimmers_high: callback to tune घड़ी trimmers क्रम high voltage
 * @set_घड़ी_प्रकारrimmers_low: callback to tune घड़ी trimmers क्रम low voltage
 */
काष्ठा tegra_dfll_soc_data अणु
	काष्ठा device *dev;
	अचिन्हित दीर्घ max_freq;
	स्थिर काष्ठा cvb_table *cvb;
	काष्ठा rail_alignment alignment;

	व्योम (*init_घड़ी_प्रकारrimmers)(व्योम);
	व्योम (*set_घड़ी_प्रकारrimmers_high)(व्योम);
	व्योम (*set_घड़ी_प्रकारrimmers_low)(व्योम);
पूर्ण;

पूर्णांक tegra_dfll_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
			काष्ठा tegra_dfll_soc_data *soc);
काष्ठा tegra_dfll_soc_data *tegra_dfll_unरेजिस्टर(काष्ठा platक्रमm_device *pdev);
पूर्णांक tegra_dfll_runसमय_suspend(काष्ठा device *dev);
पूर्णांक tegra_dfll_runसमय_resume(काष्ठा device *dev);
पूर्णांक tegra_dfll_suspend(काष्ठा device *dev);
पूर्णांक tegra_dfll_resume(काष्ठा device *dev);

#पूर्ण_अगर /* __DRIVERS_CLK_TEGRA_CLK_DFLL_H */
