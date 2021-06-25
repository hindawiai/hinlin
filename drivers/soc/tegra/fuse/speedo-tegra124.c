<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013-2014, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bug.h>

#समावेश <soc/tegra/fuse.h>

#समावेश "fuse.h"

#घोषणा CPU_PROCESS_CORNERS	2
#घोषणा GPU_PROCESS_CORNERS	2
#घोषणा SOC_PROCESS_CORNERS	2

#घोषणा FUSE_CPU_SPEEDO_0	0x14
#घोषणा FUSE_CPU_SPEEDO_1	0x2c
#घोषणा FUSE_CPU_SPEEDO_2	0x30
#घोषणा FUSE_SOC_SPEEDO_0	0x34
#घोषणा FUSE_SOC_SPEEDO_1	0x38
#घोषणा FUSE_SOC_SPEEDO_2	0x3c
#घोषणा FUSE_CPU_IDDQ		0x18
#घोषणा FUSE_SOC_IDDQ		0x40
#घोषणा FUSE_GPU_IDDQ		0x128
#घोषणा FUSE_FT_REV		0x28

क्रमागत अणु
	THRESHOLD_INDEX_0,
	THRESHOLD_INDEX_1,
	THRESHOLD_INDEX_COUNT,
पूर्ण;

अटल स्थिर u32 __initस्थिर cpu_process_speeकरोs[][CPU_PROCESS_CORNERS] = अणु
	अणु2190,	अच_पूर्णांक_उच्चपूर्ण,
	अणु0,	अच_पूर्णांक_उच्चपूर्ण,
पूर्ण;

अटल स्थिर u32 __initस्थिर gpu_process_speeकरोs[][GPU_PROCESS_CORNERS] = अणु
	अणु1965,	अच_पूर्णांक_उच्चपूर्ण,
	अणु0,	अच_पूर्णांक_उच्चपूर्ण,
पूर्ण;

अटल स्थिर u32 __initस्थिर soc_process_speeकरोs[][SOC_PROCESS_CORNERS] = अणु
	अणु2101,	अच_पूर्णांक_उच्चपूर्ण,
	अणु0,	अच_पूर्णांक_उच्चपूर्ण,
पूर्ण;

अटल व्योम __init rev_sku_to_speeकरो_ids(काष्ठा tegra_sku_info *sku_info,
					 पूर्णांक *threshold)
अणु
	पूर्णांक sku = sku_info->sku_id;

	/* Assign to शेष */
	sku_info->cpu_speeकरो_id = 0;
	sku_info->soc_speeकरो_id = 0;
	sku_info->gpu_speeकरो_id = 0;
	*threshold = THRESHOLD_INDEX_0;

	चयन (sku) अणु
	हाल 0x00: /* Eng sku */
	हाल 0x0F:
	हाल 0x23:
		/* Using the शेष */
		अवरोध;
	हाल 0x83:
		sku_info->cpu_speeकरो_id = 2;
		अवरोध;

	हाल 0x1F:
	हाल 0x87:
	हाल 0x27:
		sku_info->cpu_speeकरो_id = 2;
		sku_info->soc_speeकरो_id = 0;
		sku_info->gpu_speeकरो_id = 1;
		*threshold = THRESHOLD_INDEX_0;
		अवरोध;
	हाल 0x81:
	हाल 0x21:
	हाल 0x07:
		sku_info->cpu_speeकरो_id = 1;
		sku_info->soc_speeकरो_id = 1;
		sku_info->gpu_speeकरो_id = 1;
		*threshold = THRESHOLD_INDEX_1;
		अवरोध;
	हाल 0x49:
	हाल 0x4A:
	हाल 0x48:
		sku_info->cpu_speeकरो_id = 4;
		sku_info->soc_speeकरो_id = 2;
		sku_info->gpu_speeकरो_id = 3;
		*threshold = THRESHOLD_INDEX_1;
		अवरोध;
	शेष:
		pr_err("Tegra Unknown SKU %d\n", sku);
		/* Using the शेष क्रम the error हाल */
		अवरोध;
	पूर्ण
पूर्ण

व्योम __init tegra124_init_speeकरो_data(काष्ठा tegra_sku_info *sku_info)
अणु
	पूर्णांक i, threshold, soc_speeकरो_0_value;

	BUILD_BUG_ON(ARRAY_SIZE(cpu_process_speeकरोs) !=
			THRESHOLD_INDEX_COUNT);
	BUILD_BUG_ON(ARRAY_SIZE(gpu_process_speeकरोs) !=
			THRESHOLD_INDEX_COUNT);
	BUILD_BUG_ON(ARRAY_SIZE(soc_process_speeकरोs) !=
			THRESHOLD_INDEX_COUNT);

	sku_info->cpu_speeकरो_value = tegra_fuse_पढ़ो_early(FUSE_CPU_SPEEDO_0);
	अगर (sku_info->cpu_speeकरो_value == 0) अणु
		pr_warn("Tegra Warning: Speedo value not fused.\n");
		WARN_ON(1);
		वापस;
	पूर्ण

	/* GPU Speeकरो is stored in CPU_SPEEDO_2 */
	sku_info->gpu_speeकरो_value = tegra_fuse_पढ़ो_early(FUSE_CPU_SPEEDO_2);
	soc_speeकरो_0_value = tegra_fuse_पढ़ो_early(FUSE_SOC_SPEEDO_0);

	rev_sku_to_speeकरो_ids(sku_info, &threshold);

	sku_info->cpu_iddq_value = tegra_fuse_पढ़ो_early(FUSE_CPU_IDDQ);

	क्रम (i = 0; i < GPU_PROCESS_CORNERS; i++)
		अगर (sku_info->gpu_speeकरो_value <
			gpu_process_speeकरोs[threshold][i])
			अवरोध;
	sku_info->gpu_process_id = i;

	क्रम (i = 0; i < CPU_PROCESS_CORNERS; i++)
		अगर (sku_info->cpu_speeकरो_value <
			cpu_process_speeकरोs[threshold][i])
				अवरोध;
	sku_info->cpu_process_id = i;

	क्रम (i = 0; i < SOC_PROCESS_CORNERS; i++)
		अगर (soc_speeकरो_0_value <
			soc_process_speeकरोs[threshold][i])
			अवरोध;
	sku_info->soc_process_id = i;

	pr_debug("Tegra GPU Speedo ID=%d, Speedo Value=%d\n",
		 sku_info->gpu_speeकरो_id, sku_info->gpu_speeकरो_value);
पूर्ण
