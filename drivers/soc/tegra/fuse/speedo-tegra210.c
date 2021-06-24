<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013-2015, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bug.h>

#समावेश <soc/tegra/fuse.h>

#समावेश "fuse.h"

#घोषणा CPU_PROCESS_CORNERS	2
#घोषणा GPU_PROCESS_CORNERS	2
#घोषणा SOC_PROCESS_CORNERS	3

#घोषणा FUSE_CPU_SPEEDO_0	0x014
#घोषणा FUSE_CPU_SPEEDO_1	0x02c
#घोषणा FUSE_CPU_SPEEDO_2	0x030
#घोषणा FUSE_SOC_SPEEDO_0	0x034
#घोषणा FUSE_SOC_SPEEDO_1	0x038
#घोषणा FUSE_SOC_SPEEDO_2	0x03c
#घोषणा FUSE_CPU_IDDQ		0x018
#घोषणा FUSE_SOC_IDDQ		0x040
#घोषणा FUSE_GPU_IDDQ		0x128
#घोषणा FUSE_FT_REV		0x028

क्रमागत अणु
	THRESHOLD_INDEX_0,
	THRESHOLD_INDEX_1,
	THRESHOLD_INDEX_COUNT,
पूर्ण;

अटल स्थिर u32 __initस्थिर cpu_process_speeकरोs[][CPU_PROCESS_CORNERS] = अणु
	अणु 2119, अच_पूर्णांक_उच्च पूर्ण,
	अणु 2119, अच_पूर्णांक_उच्च पूर्ण,
पूर्ण;

अटल स्थिर u32 __initस्थिर gpu_process_speeकरोs[][GPU_PROCESS_CORNERS] = अणु
	अणु अच_पूर्णांक_उच्च, अच_पूर्णांक_उच्च पूर्ण,
	अणु अच_पूर्णांक_उच्च, अच_पूर्णांक_उच्च पूर्ण,
पूर्ण;

अटल स्थिर u32 __initस्थिर soc_process_speeकरोs[][SOC_PROCESS_CORNERS] = अणु
	अणु 1950, 2100, अच_पूर्णांक_उच्च पूर्ण,
	अणु 1950, 2100, अच_पूर्णांक_उच्च पूर्ण,
पूर्ण;

अटल u8 __init get_speeकरो_revision(व्योम)
अणु
	वापस tegra_fuse_पढ़ो_spare(4) << 2 |
	       tegra_fuse_पढ़ो_spare(3) << 1 |
	       tegra_fuse_पढ़ो_spare(2) << 0;
पूर्ण

अटल व्योम __init rev_sku_to_speeकरो_ids(काष्ठा tegra_sku_info *sku_info,
					 u8 speeकरो_rev, पूर्णांक *threshold)
अणु
	पूर्णांक sku = sku_info->sku_id;

	/* Assign to शेष */
	sku_info->cpu_speeकरो_id = 0;
	sku_info->soc_speeकरो_id = 0;
	sku_info->gpu_speeकरो_id = 0;
	*threshold = THRESHOLD_INDEX_0;

	चयन (sku) अणु
	हाल 0x00: /* Engineering SKU */
	हाल 0x01: /* Engineering SKU */
	हाल 0x07:
	हाल 0x17:
	हाल 0x27:
		अगर (speeकरो_rev >= 2)
			sku_info->gpu_speeकरो_id = 1;
		अवरोध;

	हाल 0x13:
		अगर (speeकरो_rev >= 2)
			sku_info->gpu_speeकरो_id = 1;

		sku_info->cpu_speeकरो_id = 1;
		अवरोध;

	शेष:
		pr_err("Tegra210: unknown SKU %#04x\n", sku);
		/* Using the शेष क्रम the error हाल */
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक get_process_id(पूर्णांक value, स्थिर u32 *speeकरोs, अचिन्हित पूर्णांक num)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num; i++)
		अगर (value < speeकरोs[i])
			वापस i;

	वापस -EINVAL;
पूर्ण

व्योम __init tegra210_init_speeकरो_data(काष्ठा tegra_sku_info *sku_info)
अणु
	पूर्णांक cpu_speeकरो[3], soc_speeकरो[3];
	अचिन्हित पूर्णांक index;
	u8 speeकरो_revision;

	BUILD_BUG_ON(ARRAY_SIZE(cpu_process_speeकरोs) !=
			THRESHOLD_INDEX_COUNT);
	BUILD_BUG_ON(ARRAY_SIZE(gpu_process_speeकरोs) !=
			THRESHOLD_INDEX_COUNT);
	BUILD_BUG_ON(ARRAY_SIZE(soc_process_speeकरोs) !=
			THRESHOLD_INDEX_COUNT);

	/* Read speeकरो/IDDQ fuses */
	cpu_speeकरो[0] = tegra_fuse_पढ़ो_early(FUSE_CPU_SPEEDO_0);
	cpu_speeकरो[1] = tegra_fuse_पढ़ो_early(FUSE_CPU_SPEEDO_1);
	cpu_speeकरो[2] = tegra_fuse_पढ़ो_early(FUSE_CPU_SPEEDO_2);

	soc_speeकरो[0] = tegra_fuse_पढ़ो_early(FUSE_SOC_SPEEDO_0);
	soc_speeकरो[1] = tegra_fuse_पढ़ो_early(FUSE_SOC_SPEEDO_1);
	soc_speeकरो[2] = tegra_fuse_पढ़ो_early(FUSE_SOC_SPEEDO_2);

	/*
	 * Determine CPU, GPU and SoC speeकरो values depending on speeकरो fusing
	 * revision. Note that GPU speeकरो value is fused in CPU_SPEEDO_2.
	 */
	speeकरो_revision = get_speeकरो_revision();
	pr_info("Speedo Revision %u\n", speeकरो_revision);

	अगर (speeकरो_revision >= 3) अणु
		sku_info->cpu_speeकरो_value = cpu_speeकरो[0];
		sku_info->gpu_speeकरो_value = cpu_speeकरो[2];
		sku_info->soc_speeकरो_value = soc_speeकरो[0];
	पूर्ण अन्यथा अगर (speeकरो_revision == 2) अणु
		sku_info->cpu_speeकरो_value = (-1938 + (1095 * cpu_speeकरो[0] / 100)) / 10;
		sku_info->gpu_speeकरो_value = (-1662 + (1082 * cpu_speeकरो[2] / 100)) / 10;
		sku_info->soc_speeकरो_value = ( -705 + (1037 * soc_speeकरो[0] / 100)) / 10;
	पूर्ण अन्यथा अणु
		sku_info->cpu_speeकरो_value = 2100;
		sku_info->gpu_speeकरो_value = cpu_speeकरो[2] - 75;
		sku_info->soc_speeकरो_value = 1900;
	पूर्ण

	अगर ((sku_info->cpu_speeकरो_value <= 0) ||
	    (sku_info->gpu_speeकरो_value <= 0) ||
	    (sku_info->soc_speeकरो_value <= 0)) अणु
		WARN(1, "speedo value not fused\n");
		वापस;
	पूर्ण

	rev_sku_to_speeकरो_ids(sku_info, speeकरो_revision, &index);

	sku_info->gpu_process_id = get_process_id(sku_info->gpu_speeकरो_value,
						  gpu_process_speeकरोs[index],
						  GPU_PROCESS_CORNERS);

	sku_info->cpu_process_id = get_process_id(sku_info->cpu_speeकरो_value,
						  cpu_process_speeकरोs[index],
						  CPU_PROCESS_CORNERS);

	sku_info->soc_process_id = get_process_id(sku_info->soc_speeकरो_value,
						  soc_process_speeकरोs[index],
						  SOC_PROCESS_CORNERS);

	pr_debug("Tegra GPU Speedo ID=%d, Speedo Value=%d\n",
		 sku_info->gpu_speeकरो_id, sku_info->gpu_speeकरो_value);
पूर्ण
