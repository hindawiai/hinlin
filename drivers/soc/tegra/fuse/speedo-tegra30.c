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

#घोषणा SOC_PROCESS_CORNERS	1
#घोषणा CPU_PROCESS_CORNERS	6

#घोषणा FUSE_SPEEDO_CALIB_0	0x14
#घोषणा FUSE_PACKAGE_INFO	0XFC
#घोषणा FUSE_TEST_PROG_VER	0X28

#घोषणा G_SPEEDO_BIT_MINUS1	58
#घोषणा G_SPEEDO_BIT_MINUS1_R	59
#घोषणा G_SPEEDO_BIT_MINUS2	60
#घोषणा G_SPEEDO_BIT_MINUS2_R	61
#घोषणा LP_SPEEDO_BIT_MINUS1	62
#घोषणा LP_SPEEDO_BIT_MINUS1_R	63
#घोषणा LP_SPEEDO_BIT_MINUS2	64
#घोषणा LP_SPEEDO_BIT_MINUS2_R	65

क्रमागत अणु
	THRESHOLD_INDEX_0,
	THRESHOLD_INDEX_1,
	THRESHOLD_INDEX_2,
	THRESHOLD_INDEX_3,
	THRESHOLD_INDEX_4,
	THRESHOLD_INDEX_5,
	THRESHOLD_INDEX_6,
	THRESHOLD_INDEX_7,
	THRESHOLD_INDEX_8,
	THRESHOLD_INDEX_9,
	THRESHOLD_INDEX_10,
	THRESHOLD_INDEX_11,
	THRESHOLD_INDEX_COUNT,
पूर्ण;

अटल स्थिर u32 __initस्थिर soc_process_speeकरोs[][SOC_PROCESS_CORNERS] = अणु
	अणु180पूर्ण,
	अणु170पूर्ण,
	अणु195पूर्ण,
	अणु180पूर्ण,
	अणु168पूर्ण,
	अणु192पूर्ण,
	अणु180पूर्ण,
	अणु170पूर्ण,
	अणु195पूर्ण,
	अणु180पूर्ण,
	अणु180पूर्ण,
	अणु180पूर्ण,
पूर्ण;

अटल स्थिर u32 __initस्थिर cpu_process_speeकरोs[][CPU_PROCESS_CORNERS] = अणु
	अणु306, 338, 360, 376, अच_पूर्णांक_उच्चपूर्ण,
	अणु295, 336, 358, 375, अच_पूर्णांक_उच्चपूर्ण,
	अणु325, 325, 358, 375, अच_पूर्णांक_उच्चपूर्ण,
	अणु325, 325, 358, 375, अच_पूर्णांक_उच्चपूर्ण,
	अणु292, 324, 348, 364, अच_पूर्णांक_उच्चपूर्ण,
	अणु324, 324, 348, 364, अच_पूर्णांक_उच्चपूर्ण,
	अणु324, 324, 348, 364, अच_पूर्णांक_उच्चपूर्ण,
	अणु295, 336, 358, 375, अच_पूर्णांक_उच्चपूर्ण,
	अणु358, 358, 358, 358, 397, अच_पूर्णांक_उच्चपूर्ण,
	अणु364, 364, 364, 364, 397, अच_पूर्णांक_उच्चपूर्ण,
	अणु295, 336, 358, 375, 391, अच_पूर्णांक_उच्चपूर्ण,
	अणु295, 336, 358, 375, 391, अच_पूर्णांक_उच्चपूर्ण,
पूर्ण;

अटल पूर्णांक threshold_index __initdata;

अटल व्योम __init fuse_speeकरो_calib(u32 *speeकरो_g, u32 *speeकरो_lp)
अणु
	u32 reg;
	पूर्णांक ate_ver;
	पूर्णांक bit_minus1;
	पूर्णांक bit_minus2;

	reg = tegra_fuse_पढ़ो_early(FUSE_SPEEDO_CALIB_0);

	*speeकरो_lp = (reg & 0xFFFF) * 4;
	*speeकरो_g = ((reg >> 16) & 0xFFFF) * 4;

	ate_ver = tegra_fuse_पढ़ो_early(FUSE_TEST_PROG_VER);
	pr_debug("Tegra ATE prog ver %d.%d\n", ate_ver/10, ate_ver%10);

	अगर (ate_ver >= 26) अणु
		bit_minus1 = tegra_fuse_पढ़ो_spare(LP_SPEEDO_BIT_MINUS1);
		bit_minus1 |= tegra_fuse_पढ़ो_spare(LP_SPEEDO_BIT_MINUS1_R);
		bit_minus2 = tegra_fuse_पढ़ो_spare(LP_SPEEDO_BIT_MINUS2);
		bit_minus2 |= tegra_fuse_पढ़ो_spare(LP_SPEEDO_BIT_MINUS2_R);
		*speeकरो_lp |= (bit_minus1 << 1) | bit_minus2;

		bit_minus1 = tegra_fuse_पढ़ो_spare(G_SPEEDO_BIT_MINUS1);
		bit_minus1 |= tegra_fuse_पढ़ो_spare(G_SPEEDO_BIT_MINUS1_R);
		bit_minus2 = tegra_fuse_पढ़ो_spare(G_SPEEDO_BIT_MINUS2);
		bit_minus2 |= tegra_fuse_पढ़ो_spare(G_SPEEDO_BIT_MINUS2_R);
		*speeकरो_g |= (bit_minus1 << 1) | bit_minus2;
	पूर्ण अन्यथा अणु
		*speeकरो_lp |= 0x3;
		*speeकरो_g |= 0x3;
	पूर्ण
पूर्ण

अटल व्योम __init rev_sku_to_speeकरो_ids(काष्ठा tegra_sku_info *sku_info)
अणु
	पूर्णांक package_id = tegra_fuse_पढ़ो_early(FUSE_PACKAGE_INFO) & 0x0F;

	चयन (sku_info->revision) अणु
	हाल TEGRA_REVISION_A01:
		sku_info->cpu_speeकरो_id = 0;
		sku_info->soc_speeकरो_id = 0;
		threshold_index = THRESHOLD_INDEX_0;
		अवरोध;
	हाल TEGRA_REVISION_A02:
	हाल TEGRA_REVISION_A03:
		चयन (sku_info->sku_id) अणु
		हाल 0x87:
		हाल 0x82:
			sku_info->cpu_speeकरो_id = 1;
			sku_info->soc_speeकरो_id = 1;
			threshold_index = THRESHOLD_INDEX_1;
			अवरोध;
		हाल 0x81:
			चयन (package_id) अणु
			हाल 1:
				sku_info->cpu_speeकरो_id = 2;
				sku_info->soc_speeकरो_id = 2;
				threshold_index = THRESHOLD_INDEX_2;
				अवरोध;
			हाल 2:
				sku_info->cpu_speeकरो_id = 4;
				sku_info->soc_speeकरो_id = 1;
				threshold_index = THRESHOLD_INDEX_7;
				अवरोध;
			शेष:
				pr_err("Tegra Unknown pkg %d\n", package_id);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 0x80:
			चयन (package_id) अणु
			हाल 1:
				sku_info->cpu_speeकरो_id = 5;
				sku_info->soc_speeकरो_id = 2;
				threshold_index = THRESHOLD_INDEX_8;
				अवरोध;
			हाल 2:
				sku_info->cpu_speeकरो_id = 6;
				sku_info->soc_speeकरो_id = 2;
				threshold_index = THRESHOLD_INDEX_9;
				अवरोध;
			शेष:
				pr_err("Tegra Unknown pkg %d\n", package_id);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 0x83:
			चयन (package_id) अणु
			हाल 1:
				sku_info->cpu_speeकरो_id = 7;
				sku_info->soc_speeकरो_id = 1;
				threshold_index = THRESHOLD_INDEX_10;
				अवरोध;
			हाल 2:
				sku_info->cpu_speeकरो_id = 3;
				sku_info->soc_speeकरो_id = 2;
				threshold_index = THRESHOLD_INDEX_3;
				अवरोध;
			शेष:
				pr_err("Tegra Unknown pkg %d\n", package_id);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 0x8F:
			sku_info->cpu_speeकरो_id = 8;
			sku_info->soc_speeकरो_id = 1;
			threshold_index = THRESHOLD_INDEX_11;
			अवरोध;
		हाल 0x08:
			sku_info->cpu_speeकरो_id = 1;
			sku_info->soc_speeकरो_id = 1;
			threshold_index = THRESHOLD_INDEX_4;
			अवरोध;
		हाल 0x02:
			sku_info->cpu_speeकरो_id = 2;
			sku_info->soc_speeकरो_id = 2;
			threshold_index = THRESHOLD_INDEX_5;
			अवरोध;
		हाल 0x04:
			sku_info->cpu_speeकरो_id = 3;
			sku_info->soc_speeकरो_id = 2;
			threshold_index = THRESHOLD_INDEX_6;
			अवरोध;
		हाल 0:
			चयन (package_id) अणु
			हाल 1:
				sku_info->cpu_speeकरो_id = 2;
				sku_info->soc_speeकरो_id = 2;
				threshold_index = THRESHOLD_INDEX_2;
				अवरोध;
			हाल 2:
				sku_info->cpu_speeकरो_id = 3;
				sku_info->soc_speeकरो_id = 2;
				threshold_index = THRESHOLD_INDEX_3;
				अवरोध;
			शेष:
				pr_err("Tegra Unknown pkg %d\n", package_id);
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			pr_warn("Tegra Unknown SKU %d\n", sku_info->sku_id);
			sku_info->cpu_speeकरो_id = 0;
			sku_info->soc_speeकरो_id = 0;
			threshold_index = THRESHOLD_INDEX_0;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		pr_warn("Tegra Unknown chip rev %d\n", sku_info->revision);
		sku_info->cpu_speeकरो_id = 0;
		sku_info->soc_speeकरो_id = 0;
		threshold_index = THRESHOLD_INDEX_0;
		अवरोध;
	पूर्ण
पूर्ण

व्योम __init tegra30_init_speeकरो_data(काष्ठा tegra_sku_info *sku_info)
अणु
	u32 cpu_speeकरो_val;
	u32 soc_speeकरो_val;
	पूर्णांक i;

	BUILD_BUG_ON(ARRAY_SIZE(cpu_process_speeकरोs) !=
			THRESHOLD_INDEX_COUNT);
	BUILD_BUG_ON(ARRAY_SIZE(soc_process_speeकरोs) !=
			THRESHOLD_INDEX_COUNT);


	rev_sku_to_speeकरो_ids(sku_info);
	fuse_speeकरो_calib(&cpu_speeकरो_val, &soc_speeकरो_val);
	pr_debug("Tegra CPU speedo value %u\n", cpu_speeकरो_val);
	pr_debug("Tegra Core speedo value %u\n", soc_speeकरो_val);

	क्रम (i = 0; i < CPU_PROCESS_CORNERS; i++) अणु
		अगर (cpu_speeकरो_val < cpu_process_speeकरोs[threshold_index][i])
			अवरोध;
	पूर्ण
	sku_info->cpu_process_id = i - 1;

	अगर (sku_info->cpu_process_id == -1) अणु
		pr_warn("Tegra CPU speedo value %3d out of range",
			 cpu_speeकरो_val);
		sku_info->cpu_process_id = 0;
		sku_info->cpu_speeकरो_id = 1;
	पूर्ण

	क्रम (i = 0; i < SOC_PROCESS_CORNERS; i++) अणु
		अगर (soc_speeकरो_val < soc_process_speeकरोs[threshold_index][i])
			अवरोध;
	पूर्ण
	sku_info->soc_process_id = i - 1;

	अगर (sku_info->soc_process_id == -1) अणु
		pr_warn("Tegra SoC speedo value %3d out of range",
			soc_speeकरो_val);
		sku_info->soc_process_id = 0;
		sku_info->soc_speeकरो_id = 1;
	पूर्ण
पूर्ण
