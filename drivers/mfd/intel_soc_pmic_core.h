<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Intel SoC PMIC MFD Driver
 *
 * Copyright (C) 2012-2014 Intel Corporation. All rights reserved.
 *
 * Author: Yang, Bin <bin.yang@पूर्णांकel.com>
 * Author: Zhu, Lejun <lejun.zhu@linux.पूर्णांकel.com>
 */

#अगर_अघोषित __INTEL_SOC_PMIC_CORE_H__
#घोषणा __INTEL_SOC_PMIC_CORE_H__

काष्ठा पूर्णांकel_soc_pmic_config अणु
	अचिन्हित दीर्घ irq_flags;
	काष्ठा mfd_cell *cell_dev;
	पूर्णांक n_cell_devs;
	स्थिर काष्ठा regmap_config *regmap_config;
	स्थिर काष्ठा regmap_irq_chip *irq_chip;
पूर्ण;

बाह्य काष्ठा पूर्णांकel_soc_pmic_config पूर्णांकel_soc_pmic_config_byt_crc;
बाह्य काष्ठा पूर्णांकel_soc_pmic_config पूर्णांकel_soc_pmic_config_cht_crc;

#पूर्ण_अगर	/* __INTEL_SOC_PMIC_CORE_H__ */
