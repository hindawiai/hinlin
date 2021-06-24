<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014-2018, NVIDIA CORPORATION.  All rights reserved.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modअगरied under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <soc/tegra/fuse.h>

#समावेश <dt-bindings/thermal/tegra124-soctherm.h>

#समावेश "soctherm.h"

#घोषणा TEGRA210_THERMTRIP_ANY_EN_MASK		(0x1 << 31)
#घोषणा TEGRA210_THERMTRIP_MEM_EN_MASK		(0x1 << 30)
#घोषणा TEGRA210_THERMTRIP_GPU_EN_MASK		(0x1 << 29)
#घोषणा TEGRA210_THERMTRIP_CPU_EN_MASK		(0x1 << 28)
#घोषणा TEGRA210_THERMTRIP_TSENSE_EN_MASK	(0x1 << 27)
#घोषणा TEGRA210_THERMTRIP_GPUMEM_THRESH_MASK	(0x1ff << 18)
#घोषणा TEGRA210_THERMTRIP_CPU_THRESH_MASK	(0x1ff << 9)
#घोषणा TEGRA210_THERMTRIP_TSENSE_THRESH_MASK	0x1ff

#घोषणा TEGRA210_THERMCTL_LVL0_UP_THRESH_MASK	(0x1ff << 18)
#घोषणा TEGRA210_THERMCTL_LVL0_DN_THRESH_MASK	(0x1ff << 9)

#घोषणा TEGRA210_THRESH_GRAIN			500
#घोषणा TEGRA210_BPTT				9

अटल स्थिर काष्ठा tegra_tsensor_configuration tegra210_tsensor_config = अणु
	.tall = 16300,
	.tiddq_en = 1,
	.ten_count = 1,
	.tsample = 120,
	.tsample_ate = 480,
पूर्ण;

अटल स्थिर काष्ठा tegra_tsensor_group tegra210_tsensor_group_cpu = अणु
	.id = TEGRA124_SOCTHERM_SENSOR_CPU,
	.name = "cpu",
	.sensor_temp_offset = SENSOR_TEMP1,
	.sensor_temp_mask = SENSOR_TEMP1_CPU_TEMP_MASK,
	.pभाग = 8,
	.pभाग_ate = 8,
	.pभाग_mask = SENSOR_PDIV_CPU_MASK,
	.pllx_hotspot_dअगरf = 10,
	.pllx_hotspot_mask = SENSOR_HOTSPOT_CPU_MASK,
	.thermtrip_any_en_mask = TEGRA210_THERMTRIP_ANY_EN_MASK,
	.thermtrip_enable_mask = TEGRA210_THERMTRIP_CPU_EN_MASK,
	.thermtrip_threshold_mask = TEGRA210_THERMTRIP_CPU_THRESH_MASK,
	.thermctl_isr_mask = THERM_IRQ_CPU_MASK,
	.thermctl_lvl0_offset = THERMCTL_LEVEL0_GROUP_CPU,
	.thermctl_lvl0_up_thresh_mask = TEGRA210_THERMCTL_LVL0_UP_THRESH_MASK,
	.thermctl_lvl0_dn_thresh_mask = TEGRA210_THERMCTL_LVL0_DN_THRESH_MASK,
पूर्ण;

अटल स्थिर काष्ठा tegra_tsensor_group tegra210_tsensor_group_gpu = अणु
	.id = TEGRA124_SOCTHERM_SENSOR_GPU,
	.name = "gpu",
	.sensor_temp_offset = SENSOR_TEMP1,
	.sensor_temp_mask = SENSOR_TEMP1_GPU_TEMP_MASK,
	.pभाग = 8,
	.pभाग_ate = 8,
	.pभाग_mask = SENSOR_PDIV_GPU_MASK,
	.pllx_hotspot_dअगरf = 5,
	.pllx_hotspot_mask = SENSOR_HOTSPOT_GPU_MASK,
	.thermtrip_any_en_mask = TEGRA210_THERMTRIP_ANY_EN_MASK,
	.thermtrip_enable_mask = TEGRA210_THERMTRIP_GPU_EN_MASK,
	.thermtrip_threshold_mask = TEGRA210_THERMTRIP_GPUMEM_THRESH_MASK,
	.thermctl_isr_mask = THERM_IRQ_GPU_MASK,
	.thermctl_lvl0_offset = THERMCTL_LEVEL0_GROUP_GPU,
	.thermctl_lvl0_up_thresh_mask = TEGRA210_THERMCTL_LVL0_UP_THRESH_MASK,
	.thermctl_lvl0_dn_thresh_mask = TEGRA210_THERMCTL_LVL0_DN_THRESH_MASK,
पूर्ण;

अटल स्थिर काष्ठा tegra_tsensor_group tegra210_tsensor_group_pll = अणु
	.id = TEGRA124_SOCTHERM_SENSOR_PLLX,
	.name = "pll",
	.sensor_temp_offset = SENSOR_TEMP2,
	.sensor_temp_mask = SENSOR_TEMP2_PLLX_TEMP_MASK,
	.pभाग = 8,
	.pभाग_ate = 8,
	.pभाग_mask = SENSOR_PDIV_PLLX_MASK,
	.thermtrip_any_en_mask = TEGRA210_THERMTRIP_ANY_EN_MASK,
	.thermtrip_enable_mask = TEGRA210_THERMTRIP_TSENSE_EN_MASK,
	.thermtrip_threshold_mask = TEGRA210_THERMTRIP_TSENSE_THRESH_MASK,
	.thermctl_isr_mask = THERM_IRQ_TSENSE_MASK,
	.thermctl_lvl0_offset = THERMCTL_LEVEL0_GROUP_TSENSE,
	.thermctl_lvl0_up_thresh_mask = TEGRA210_THERMCTL_LVL0_UP_THRESH_MASK,
	.thermctl_lvl0_dn_thresh_mask = TEGRA210_THERMCTL_LVL0_DN_THRESH_MASK,
पूर्ण;

अटल स्थिर काष्ठा tegra_tsensor_group tegra210_tsensor_group_mem = अणु
	.id = TEGRA124_SOCTHERM_SENSOR_MEM,
	.name = "mem",
	.sensor_temp_offset = SENSOR_TEMP2,
	.sensor_temp_mask = SENSOR_TEMP2_MEM_TEMP_MASK,
	.pभाग = 8,
	.pभाग_ate = 8,
	.pभाग_mask = SENSOR_PDIV_MEM_MASK,
	.pllx_hotspot_dअगरf = 0,
	.pllx_hotspot_mask = SENSOR_HOTSPOT_MEM_MASK,
	.thermtrip_any_en_mask = TEGRA210_THERMTRIP_ANY_EN_MASK,
	.thermtrip_enable_mask = TEGRA210_THERMTRIP_MEM_EN_MASK,
	.thermtrip_threshold_mask = TEGRA210_THERMTRIP_GPUMEM_THRESH_MASK,
	.thermctl_isr_mask = THERM_IRQ_MEM_MASK,
	.thermctl_lvl0_offset = THERMCTL_LEVEL0_GROUP_MEM,
	.thermctl_lvl0_up_thresh_mask = TEGRA210_THERMCTL_LVL0_UP_THRESH_MASK,
	.thermctl_lvl0_dn_thresh_mask = TEGRA210_THERMCTL_LVL0_DN_THRESH_MASK,
पूर्ण;

अटल स्थिर काष्ठा tegra_tsensor_group *tegra210_tsensor_groups[] = अणु
	&tegra210_tsensor_group_cpu,
	&tegra210_tsensor_group_gpu,
	&tegra210_tsensor_group_pll,
	&tegra210_tsensor_group_mem,
पूर्ण;

अटल स्थिर काष्ठा tegra_tsensor tegra210_tsensors[] = अणु
	अणु
		.name = "cpu0",
		.base = 0xc0,
		.config = &tegra210_tsensor_config,
		.calib_fuse_offset = 0x098,
		.fuse_corr_alpha = 1085000,
		.fuse_corr_beta = 3244200,
		.group = &tegra210_tsensor_group_cpu,
	पूर्ण, अणु
		.name = "cpu1",
		.base = 0xe0,
		.config = &tegra210_tsensor_config,
		.calib_fuse_offset = 0x084,
		.fuse_corr_alpha = 1126200,
		.fuse_corr_beta = -67500,
		.group = &tegra210_tsensor_group_cpu,
	पूर्ण, अणु
		.name = "cpu2",
		.base = 0x100,
		.config = &tegra210_tsensor_config,
		.calib_fuse_offset = 0x088,
		.fuse_corr_alpha = 1098400,
		.fuse_corr_beta = 2251100,
		.group = &tegra210_tsensor_group_cpu,
	पूर्ण, अणु
		.name = "cpu3",
		.base = 0x120,
		.config = &tegra210_tsensor_config,
		.calib_fuse_offset = 0x12c,
		.fuse_corr_alpha = 1108000,
		.fuse_corr_beta = 602700,
		.group = &tegra210_tsensor_group_cpu,
	पूर्ण, अणु
		.name = "mem0",
		.base = 0x140,
		.config = &tegra210_tsensor_config,
		.calib_fuse_offset = 0x158,
		.fuse_corr_alpha = 1069200,
		.fuse_corr_beta = 3549900,
		.group = &tegra210_tsensor_group_mem,
	पूर्ण, अणु
		.name = "mem1",
		.base = 0x160,
		.config = &tegra210_tsensor_config,
		.calib_fuse_offset = 0x15c,
		.fuse_corr_alpha = 1173700,
		.fuse_corr_beta = -6263600,
		.group = &tegra210_tsensor_group_mem,
	पूर्ण, अणु
		.name = "gpu",
		.base = 0x180,
		.config = &tegra210_tsensor_config,
		.calib_fuse_offset = 0x154,
		.fuse_corr_alpha = 1074300,
		.fuse_corr_beta = 2734900,
		.group = &tegra210_tsensor_group_gpu,
	पूर्ण, अणु
		.name = "pllx",
		.base = 0x1a0,
		.config = &tegra210_tsensor_config,
		.calib_fuse_offset = 0x160,
		.fuse_corr_alpha = 1039700,
		.fuse_corr_beta = 6829100,
		.group = &tegra210_tsensor_group_pll,
	पूर्ण,
पूर्ण;

/*
 * Mask/shअगरt bits in FUSE_TSENSOR_COMMON and
 * FUSE_TSENSOR_COMMON, which are described in
 * tegra_soctherm_fuse.c
 */
अटल स्थिर काष्ठा tegra_soctherm_fuse tegra210_soctherm_fuse = अणु
	.fuse_base_cp_mask = 0x3ff << 11,
	.fuse_base_cp_shअगरt = 11,
	.fuse_base_ft_mask = 0x7ff << 21,
	.fuse_base_ft_shअगरt = 21,
	.fuse_shअगरt_ft_mask = 0x1f << 6,
	.fuse_shअगरt_ft_shअगरt = 6,
	.fuse_spare_realignment = 0,
पूर्ण;

अटल काष्ठा tsensor_group_thermtrips tegra210_tsensor_thermtrips[] = अणु
	अणु.id = TEGRA124_SOCTHERM_SENSOR_NUMपूर्ण,
	अणु.id = TEGRA124_SOCTHERM_SENSOR_NUMपूर्ण,
	अणु.id = TEGRA124_SOCTHERM_SENSOR_NUMपूर्ण,
	अणु.id = TEGRA124_SOCTHERM_SENSOR_NUMपूर्ण,
पूर्ण;

स्थिर काष्ठा tegra_soctherm_soc tegra210_soctherm = अणु
	.tsensors = tegra210_tsensors,
	.num_tsensors = ARRAY_SIZE(tegra210_tsensors),
	.ttgs = tegra210_tsensor_groups,
	.num_ttgs = ARRAY_SIZE(tegra210_tsensor_groups),
	.tfuse = &tegra210_soctherm_fuse,
	.thresh_grain = TEGRA210_THRESH_GRAIN,
	.bptt = TEGRA210_BPTT,
	.use_ccroc = false,
	.thermtrips = tegra210_tsensor_thermtrips,
पूर्ण;
