<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013-2014, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/device.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/अक्रमom.h>

#समावेश <soc/tegra/fuse.h>

#समावेश "fuse.h"

#घोषणा FUSE_BEGIN	0x100

/* Tegra30 and later */
#घोषणा FUSE_VENDOR_CODE	0x100
#घोषणा FUSE_FAB_CODE		0x104
#घोषणा FUSE_LOT_CODE_0		0x108
#घोषणा FUSE_LOT_CODE_1		0x10c
#घोषणा FUSE_WAFER_ID		0x110
#घोषणा FUSE_X_COORDINATE	0x114
#घोषणा FUSE_Y_COORDINATE	0x118

#घोषणा FUSE_HAS_REVISION_INFO	BIT(0)

#अगर defined(CONFIG_ARCH_TEGRA_3x_SOC) || \
    defined(CONFIG_ARCH_TEGRA_114_SOC) || \
    defined(CONFIG_ARCH_TEGRA_124_SOC) || \
    defined(CONFIG_ARCH_TEGRA_132_SOC) || \
    defined(CONFIG_ARCH_TEGRA_210_SOC) || \
    defined(CONFIG_ARCH_TEGRA_186_SOC) || \
    defined(CONFIG_ARCH_TEGRA_194_SOC)
अटल u32 tegra30_fuse_पढ़ो_early(काष्ठा tegra_fuse *fuse, अचिन्हित पूर्णांक offset)
अणु
	अगर (WARN_ON(!fuse->base))
		वापस 0;

	वापस पढ़ोl_relaxed(fuse->base + FUSE_BEGIN + offset);
पूर्ण

अटल u32 tegra30_fuse_पढ़ो(काष्ठा tegra_fuse *fuse, अचिन्हित पूर्णांक offset)
अणु
	u32 value;
	पूर्णांक err;

	err = clk_prepare_enable(fuse->clk);
	अगर (err < 0) अणु
		dev_err(fuse->dev, "failed to enable FUSE clock: %d\n", err);
		वापस 0;
	पूर्ण

	value = पढ़ोl_relaxed(fuse->base + FUSE_BEGIN + offset);

	clk_disable_unprepare(fuse->clk);

	वापस value;
पूर्ण

अटल व्योम __init tegra30_fuse_add_अक्रमomness(व्योम)
अणु
	u32 अक्रमomness[12];

	अक्रमomness[0] = tegra_sku_info.sku_id;
	अक्रमomness[1] = tegra_पढ़ो_straps();
	अक्रमomness[2] = tegra_पढ़ो_chipid();
	अक्रमomness[3] = tegra_sku_info.cpu_process_id << 16;
	अक्रमomness[3] |= tegra_sku_info.soc_process_id;
	अक्रमomness[4] = tegra_sku_info.cpu_speeकरो_id << 16;
	अक्रमomness[4] |= tegra_sku_info.soc_speeकरो_id;
	अक्रमomness[5] = tegra_fuse_पढ़ो_early(FUSE_VENDOR_CODE);
	अक्रमomness[6] = tegra_fuse_पढ़ो_early(FUSE_FAB_CODE);
	अक्रमomness[7] = tegra_fuse_पढ़ो_early(FUSE_LOT_CODE_0);
	अक्रमomness[8] = tegra_fuse_पढ़ो_early(FUSE_LOT_CODE_1);
	अक्रमomness[9] = tegra_fuse_पढ़ो_early(FUSE_WAFER_ID);
	अक्रमomness[10] = tegra_fuse_पढ़ो_early(FUSE_X_COORDINATE);
	अक्रमomness[11] = tegra_fuse_पढ़ो_early(FUSE_Y_COORDINATE);

	add_device_अक्रमomness(अक्रमomness, माप(अक्रमomness));
पूर्ण

अटल व्योम __init tegra30_fuse_init(काष्ठा tegra_fuse *fuse)
अणु
	fuse->पढ़ो_early = tegra30_fuse_पढ़ो_early;
	fuse->पढ़ो = tegra30_fuse_पढ़ो;

	tegra_init_revision();

	अगर (fuse->soc->speeकरो_init)
		fuse->soc->speeकरो_init(&tegra_sku_info);

	tegra30_fuse_add_अक्रमomness();
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_TEGRA_3x_SOC
अटल स्थिर काष्ठा tegra_fuse_info tegra30_fuse_info = अणु
	.पढ़ो = tegra30_fuse_पढ़ो,
	.size = 0x2a4,
	.spare = 0x144,
पूर्ण;

स्थिर काष्ठा tegra_fuse_soc tegra30_fuse_soc = अणु
	.init = tegra30_fuse_init,
	.speeकरो_init = tegra30_init_speeकरो_data,
	.info = &tegra30_fuse_info,
	.soc_attr_group = &tegra_soc_attr_group,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_TEGRA_114_SOC
अटल स्थिर काष्ठा tegra_fuse_info tegra114_fuse_info = अणु
	.पढ़ो = tegra30_fuse_पढ़ो,
	.size = 0x2a0,
	.spare = 0x180,
पूर्ण;

स्थिर काष्ठा tegra_fuse_soc tegra114_fuse_soc = अणु
	.init = tegra30_fuse_init,
	.speeकरो_init = tegra114_init_speeकरो_data,
	.info = &tegra114_fuse_info,
	.soc_attr_group = &tegra_soc_attr_group,
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_TEGRA_124_SOC) || defined(CONFIG_ARCH_TEGRA_132_SOC)
अटल स्थिर काष्ठा nvmem_cell_lookup tegra124_fuse_lookups[] = अणु
	अणु
		.nvmem_name = "fuse",
		.cell_name = "xusb-pad-calibration",
		.dev_id = "7009f000.padctl",
		.con_id = "calibration",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "sata-calibration",
		.dev_id = "70020000.sata",
		.con_id = "calibration",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "tsensor-common",
		.dev_id = "700e2000.thermal-sensor",
		.con_id = "common",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "tsensor-realignment",
		.dev_id = "700e2000.thermal-sensor",
		.con_id = "realignment",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "tsensor-cpu0",
		.dev_id = "700e2000.thermal-sensor",
		.con_id = "cpu0",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "tsensor-cpu1",
		.dev_id = "700e2000.thermal-sensor",
		.con_id = "cpu1",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "tsensor-cpu2",
		.dev_id = "700e2000.thermal-sensor",
		.con_id = "cpu2",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "tsensor-cpu3",
		.dev_id = "700e2000.thermal-sensor",
		.con_id = "cpu3",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "tsensor-mem0",
		.dev_id = "700e2000.thermal-sensor",
		.con_id = "mem0",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "tsensor-mem1",
		.dev_id = "700e2000.thermal-sensor",
		.con_id = "mem1",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "tsensor-gpu",
		.dev_id = "700e2000.thermal-sensor",
		.con_id = "gpu",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "tsensor-pllx",
		.dev_id = "700e2000.thermal-sensor",
		.con_id = "pllx",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_fuse_info tegra124_fuse_info = अणु
	.पढ़ो = tegra30_fuse_पढ़ो,
	.size = 0x300,
	.spare = 0x200,
पूर्ण;

स्थिर काष्ठा tegra_fuse_soc tegra124_fuse_soc = अणु
	.init = tegra30_fuse_init,
	.speeकरो_init = tegra124_init_speeकरो_data,
	.info = &tegra124_fuse_info,
	.lookups = tegra124_fuse_lookups,
	.num_lookups = ARRAY_SIZE(tegra124_fuse_lookups),
	.soc_attr_group = &tegra_soc_attr_group,
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_TEGRA_210_SOC)
अटल स्थिर काष्ठा nvmem_cell_lookup tegra210_fuse_lookups[] = अणु
	अणु
		.nvmem_name = "fuse",
		.cell_name = "tsensor-cpu1",
		.dev_id = "700e2000.thermal-sensor",
		.con_id = "cpu1",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "tsensor-cpu2",
		.dev_id = "700e2000.thermal-sensor",
		.con_id = "cpu2",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "tsensor-cpu0",
		.dev_id = "700e2000.thermal-sensor",
		.con_id = "cpu0",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "xusb-pad-calibration",
		.dev_id = "7009f000.padctl",
		.con_id = "calibration",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "tsensor-cpu3",
		.dev_id = "700e2000.thermal-sensor",
		.con_id = "cpu3",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "sata-calibration",
		.dev_id = "70020000.sata",
		.con_id = "calibration",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "tsensor-gpu",
		.dev_id = "700e2000.thermal-sensor",
		.con_id = "gpu",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "tsensor-mem0",
		.dev_id = "700e2000.thermal-sensor",
		.con_id = "mem0",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "tsensor-mem1",
		.dev_id = "700e2000.thermal-sensor",
		.con_id = "mem1",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "tsensor-pllx",
		.dev_id = "700e2000.thermal-sensor",
		.con_id = "pllx",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "tsensor-common",
		.dev_id = "700e2000.thermal-sensor",
		.con_id = "common",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "gpu-calibration",
		.dev_id = "57000000.gpu",
		.con_id = "calibration",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "xusb-pad-calibration-ext",
		.dev_id = "7009f000.padctl",
		.con_id = "calibration-ext",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_fuse_info tegra210_fuse_info = अणु
	.पढ़ो = tegra30_fuse_पढ़ो,
	.size = 0x300,
	.spare = 0x280,
पूर्ण;

स्थिर काष्ठा tegra_fuse_soc tegra210_fuse_soc = अणु
	.init = tegra30_fuse_init,
	.speeकरो_init = tegra210_init_speeकरो_data,
	.info = &tegra210_fuse_info,
	.lookups = tegra210_fuse_lookups,
	.num_lookups = ARRAY_SIZE(tegra210_fuse_lookups),
	.soc_attr_group = &tegra_soc_attr_group,
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_TEGRA_186_SOC)
अटल स्थिर काष्ठा nvmem_cell_lookup tegra186_fuse_lookups[] = अणु
	अणु
		.nvmem_name = "fuse",
		.cell_name = "xusb-pad-calibration",
		.dev_id = "3520000.padctl",
		.con_id = "calibration",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "xusb-pad-calibration-ext",
		.dev_id = "3520000.padctl",
		.con_id = "calibration-ext",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_fuse_info tegra186_fuse_info = अणु
	.पढ़ो = tegra30_fuse_पढ़ो,
	.size = 0x300,
	.spare = 0x280,
पूर्ण;

स्थिर काष्ठा tegra_fuse_soc tegra186_fuse_soc = अणु
	.init = tegra30_fuse_init,
	.info = &tegra186_fuse_info,
	.lookups = tegra186_fuse_lookups,
	.num_lookups = ARRAY_SIZE(tegra186_fuse_lookups),
	.soc_attr_group = &tegra_soc_attr_group,
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_TEGRA_194_SOC)
अटल स्थिर काष्ठा nvmem_cell_lookup tegra194_fuse_lookups[] = अणु
	अणु
		.nvmem_name = "fuse",
		.cell_name = "xusb-pad-calibration",
		.dev_id = "3520000.padctl",
		.con_id = "calibration",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "xusb-pad-calibration-ext",
		.dev_id = "3520000.padctl",
		.con_id = "calibration-ext",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_fuse_info tegra194_fuse_info = अणु
	.पढ़ो = tegra30_fuse_पढ़ो,
	.size = 0x300,
	.spare = 0x280,
पूर्ण;

स्थिर काष्ठा tegra_fuse_soc tegra194_fuse_soc = अणु
	.init = tegra30_fuse_init,
	.info = &tegra194_fuse_info,
	.lookups = tegra194_fuse_lookups,
	.num_lookups = ARRAY_SIZE(tegra194_fuse_lookups),
	.soc_attr_group = &tegra194_soc_attr_group,
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_TEGRA_234_SOC)
अटल स्थिर काष्ठा nvmem_cell_lookup tegra234_fuse_lookups[] = अणु
	अणु
		.nvmem_name = "fuse",
		.cell_name = "xusb-pad-calibration",
		.dev_id = "3520000.padctl",
		.con_id = "calibration",
	पूर्ण, अणु
		.nvmem_name = "fuse",
		.cell_name = "xusb-pad-calibration-ext",
		.dev_id = "3520000.padctl",
		.con_id = "calibration-ext",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_fuse_info tegra234_fuse_info = अणु
	.पढ़ो = tegra30_fuse_पढ़ो,
	.size = 0x300,
	.spare = 0x280,
पूर्ण;

स्थिर काष्ठा tegra_fuse_soc tegra234_fuse_soc = अणु
	.init = tegra30_fuse_init,
	.info = &tegra234_fuse_info,
	.lookups = tegra234_fuse_lookups,
	.num_lookups = ARRAY_SIZE(tegra234_fuse_lookups),
	.soc_attr_group = &tegra194_soc_attr_group,
पूर्ण;
#पूर्ण_अगर
