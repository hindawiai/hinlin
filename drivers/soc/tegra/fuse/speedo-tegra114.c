<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013-2014, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/bug.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>

#समावेश <soc/tegra/fuse.h>

#समावेश "fuse.h"

#घोषणा SOC_PROCESS_CORNERS	2
#घोषणा CPU_PROCESS_CORNERS	2

क्रमागत अणु
	THRESHOLD_INDEX_0,
	THRESHOLD_INDEX_1,
	THRESHOLD_INDEX_COUNT,
पूर्ण;

अटल स्थिर u32 __initस्थिर soc_process_speeकरोs[][SOC_PROCESS_CORNERS] = अणु
	अणु1123,     अच_पूर्णांक_उच्चपूर्ण,
	अणु0,        अच_पूर्णांक_उच्चपूर्ण,
पूर्ण;

अटल स्थिर u32 __initस्थिर cpu_process_speeकरोs[][CPU_PROCESS_CORNERS] = अणु
	अणु1695,     अच_पूर्णांक_उच्चपूर्ण,
	अणु0,        अच_पूर्णांक_उच्चपूर्ण,
पूर्ण;

अटल व्योम __init rev_sku_to_speeकरो_ids(काष्ठा tegra_sku_info *sku_info,
					 पूर्णांक *threshold)
अणु
	u32 पंचांगp;
	u32 sku = sku_info->sku_id;
	क्रमागत tegra_revision rev = sku_info->revision;

	चयन (sku) अणु
	हाल 0x00:
	हाल 0x10:
	हाल 0x05:
	हाल 0x06:
		sku_info->cpu_speeकरो_id = 1;
		sku_info->soc_speeकरो_id = 0;
		*threshold = THRESHOLD_INDEX_0;
		अवरोध;

	हाल 0x03:
	हाल 0x04:
		sku_info->cpu_speeकरो_id = 2;
		sku_info->soc_speeकरो_id = 1;
		*threshold = THRESHOLD_INDEX_1;
		अवरोध;

	शेष:
		pr_err("Tegra Unknown SKU %d\n", sku);
		sku_info->cpu_speeकरो_id = 0;
		sku_info->soc_speeकरो_id = 0;
		*threshold = THRESHOLD_INDEX_0;
		अवरोध;
	पूर्ण

	अगर (rev == TEGRA_REVISION_A01) अणु
		पंचांगp = tegra_fuse_पढ़ो_early(0x270) << 1;
		पंचांगp |= tegra_fuse_पढ़ो_early(0x26c);
		अगर (!पंचांगp)
			sku_info->cpu_speeकरो_id = 0;
	पूर्ण
पूर्ण

व्योम __init tegra114_init_speeकरो_data(काष्ठा tegra_sku_info *sku_info)
अणु
	u32 cpu_speeकरो_val;
	u32 soc_speeकरो_val;
	पूर्णांक threshold;
	पूर्णांक i;

	BUILD_BUG_ON(ARRAY_SIZE(cpu_process_speeकरोs) !=
			THRESHOLD_INDEX_COUNT);
	BUILD_BUG_ON(ARRAY_SIZE(soc_process_speeकरोs) !=
			THRESHOLD_INDEX_COUNT);

	rev_sku_to_speeकरो_ids(sku_info, &threshold);

	cpu_speeकरो_val = tegra_fuse_पढ़ो_early(0x12c) + 1024;
	soc_speeकरो_val = tegra_fuse_पढ़ो_early(0x134);

	क्रम (i = 0; i < CPU_PROCESS_CORNERS; i++)
		अगर (cpu_speeकरो_val < cpu_process_speeकरोs[threshold][i])
			अवरोध;
	sku_info->cpu_process_id = i;

	क्रम (i = 0; i < SOC_PROCESS_CORNERS; i++)
		अगर (soc_speeकरो_val < soc_process_speeकरोs[threshold][i])
			अवरोध;
	sku_info->soc_process_id = i;
पूर्ण
