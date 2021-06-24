<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2014, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/bug.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>

#समावेश <soc/tegra/fuse.h>

#समावेश "fuse.h"

#घोषणा CPU_SPEEDO_LSBIT		20
#घोषणा CPU_SPEEDO_MSBIT		29
#घोषणा CPU_SPEEDO_REDUND_LSBIT		30
#घोषणा CPU_SPEEDO_REDUND_MSBIT		39
#घोषणा CPU_SPEEDO_REDUND_OFFS	(CPU_SPEEDO_REDUND_MSBIT - CPU_SPEEDO_MSBIT)

#घोषणा SOC_SPEEDO_LSBIT		40
#घोषणा SOC_SPEEDO_MSBIT		47
#घोषणा SOC_SPEEDO_REDUND_LSBIT		48
#घोषणा SOC_SPEEDO_REDUND_MSBIT		55
#घोषणा SOC_SPEEDO_REDUND_OFFS	(SOC_SPEEDO_REDUND_MSBIT - SOC_SPEEDO_MSBIT)

#घोषणा SPEEDO_MULT			4

#घोषणा PROCESS_CORNERS_NUM		4

#घोषणा SPEEDO_ID_SELECT_0(rev)		((rev) <= 2)
#घोषणा SPEEDO_ID_SELECT_1(sku)		\
	(((sku) != 20) && ((sku) != 23) && ((sku) != 24) && \
	 ((sku) != 27) && ((sku) != 28))

क्रमागत अणु
	SPEEDO_ID_0,
	SPEEDO_ID_1,
	SPEEDO_ID_2,
	SPEEDO_ID_COUNT,
पूर्ण;

अटल स्थिर u32 __initस्थिर cpu_process_speeकरोs[][PROCESS_CORNERS_NUM] = अणु
	अणु315, 366, 420, अच_पूर्णांक_उच्चपूर्ण,
	अणु303, 368, 419, अच_पूर्णांक_उच्चपूर्ण,
	अणु316, 331, 383, अच_पूर्णांक_उच्चपूर्ण,
पूर्ण;

अटल स्थिर u32 __initस्थिर soc_process_speeकरोs[][PROCESS_CORNERS_NUM] = अणु
	अणु165, 195, 224, अच_पूर्णांक_उच्चपूर्ण,
	अणु165, 195, 224, अच_पूर्णांक_उच्चपूर्ण,
	अणु165, 195, 224, अच_पूर्णांक_उच्चपूर्ण,
पूर्ण;

व्योम __init tegra20_init_speeकरो_data(काष्ठा tegra_sku_info *sku_info)
अणु
	u32 reg;
	u32 val;
	पूर्णांक i;

	BUILD_BUG_ON(ARRAY_SIZE(cpu_process_speeकरोs) != SPEEDO_ID_COUNT);
	BUILD_BUG_ON(ARRAY_SIZE(soc_process_speeकरोs) != SPEEDO_ID_COUNT);

	अगर (SPEEDO_ID_SELECT_0(sku_info->revision))
		sku_info->soc_speeकरो_id = SPEEDO_ID_0;
	अन्यथा अगर (SPEEDO_ID_SELECT_1(sku_info->sku_id))
		sku_info->soc_speeकरो_id = SPEEDO_ID_1;
	अन्यथा
		sku_info->soc_speeकरो_id = SPEEDO_ID_2;

	val = 0;
	क्रम (i = CPU_SPEEDO_MSBIT; i >= CPU_SPEEDO_LSBIT; i--) अणु
		reg = tegra_fuse_पढ़ो_spare(i) |
			tegra_fuse_पढ़ो_spare(i + CPU_SPEEDO_REDUND_OFFS);
		val = (val << 1) | (reg & 0x1);
	पूर्ण
	val = val * SPEEDO_MULT;
	pr_debug("Tegra CPU speedo value %u\n", val);

	क्रम (i = 0; i < (PROCESS_CORNERS_NUM - 1); i++) अणु
		अगर (val <= cpu_process_speeकरोs[sku_info->soc_speeकरो_id][i])
			अवरोध;
	पूर्ण
	sku_info->cpu_process_id = i;

	val = 0;
	क्रम (i = SOC_SPEEDO_MSBIT; i >= SOC_SPEEDO_LSBIT; i--) अणु
		reg = tegra_fuse_पढ़ो_spare(i) |
			tegra_fuse_पढ़ो_spare(i + SOC_SPEEDO_REDUND_OFFS);
		val = (val << 1) | (reg & 0x1);
	पूर्ण
	val = val * SPEEDO_MULT;
	pr_debug("Core speedo value %u\n", val);

	क्रम (i = 0; i < (PROCESS_CORNERS_NUM - 1); i++) अणु
		अगर (val <= soc_process_speeकरोs[sku_info->soc_speeकरो_id][i])
			अवरोध;
	पूर्ण
	sku_info->soc_process_id = i;
पूर्ण
