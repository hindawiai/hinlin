<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2014-2016, NVIDIA CORPORATION.  All rights reserved.
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

#अगर_अघोषित __DRIVERS_THERMAL_TEGRA_SOCTHERM_H
#घोषणा __DRIVERS_THERMAL_TEGRA_SOCTHERM_H

#घोषणा THERMCTL_LEVEL0_GROUP_CPU               0x0
#घोषणा THERMCTL_LEVEL0_GROUP_GPU		0x4
#घोषणा THERMCTL_LEVEL0_GROUP_MEM		0x8
#घोषणा THERMCTL_LEVEL0_GROUP_TSENSE		0xc

#घोषणा SENSOR_CONFIG2                          8
#घोषणा SENSOR_CONFIG2_THERMA_MASK		(0xffff << 16)
#घोषणा SENSOR_CONFIG2_THERMA_SHIFT		16
#घोषणा SENSOR_CONFIG2_THERMB_MASK		0xffff
#घोषणा SENSOR_CONFIG2_THERMB_SHIFT		0

#घोषणा THERMCTL_THERMTRIP_CTL			0x80
/* BITs are defined in device file */

#घोषणा THERMCTL_INTR_ENABLE			0x88
#घोषणा THERMCTL_INTR_DISABLE			0x8c
#घोषणा TH_INTR_UP_DN_EN			0x3
#घोषणा THERM_IRQ_MEM_MASK			(TH_INTR_UP_DN_EN << 24)
#घोषणा THERM_IRQ_GPU_MASK			(TH_INTR_UP_DN_EN << 16)
#घोषणा THERM_IRQ_CPU_MASK			(TH_INTR_UP_DN_EN << 8)
#घोषणा THERM_IRQ_TSENSE_MASK			(TH_INTR_UP_DN_EN << 0)

#घोषणा SENSOR_PDIV				0x1c0
#घोषणा SENSOR_PDIV_CPU_MASK			(0xf << 12)
#घोषणा SENSOR_PDIV_GPU_MASK			(0xf << 8)
#घोषणा SENSOR_PDIV_MEM_MASK			(0xf << 4)
#घोषणा SENSOR_PDIV_PLLX_MASK			(0xf << 0)

#घोषणा SENSOR_HOTSPOT_OFF			0x1c4
#घोषणा SENSOR_HOTSPOT_CPU_MASK			(0xff << 16)
#घोषणा SENSOR_HOTSPOT_GPU_MASK			(0xff << 8)
#घोषणा SENSOR_HOTSPOT_MEM_MASK			(0xff << 0)

#घोषणा SENSOR_TEMP1				0x1c8
#घोषणा SENSOR_TEMP1_CPU_TEMP_MASK		(0xffff << 16)
#घोषणा SENSOR_TEMP1_GPU_TEMP_MASK		0xffff
#घोषणा SENSOR_TEMP2				0x1cc
#घोषणा SENSOR_TEMP2_MEM_TEMP_MASK		(0xffff << 16)
#घोषणा SENSOR_TEMP2_PLLX_TEMP_MASK		0xffff

/**
 * काष्ठा tegra_tsensor_group - SOC_THERM sensor group data
 * @name: लघु name of the temperature sensor group
 * @id: numeric ID of the temperature sensor group
 * @sensor_temp_offset: offset of the SENSOR_TEMP* रेजिस्टर
 * @sensor_temp_mask: bit mask क्रम this sensor group in SENSOR_TEMP* रेजिस्टर
 * @pभाग: the sensor count post-भागider to use during runसमय
 * @pभाग_ate: the sensor count post-भागider used during स्वतःmated test
 * @pभाग_mask: रेजिस्टर bitfield mask क्रम the PDIV field क्रम this sensor
 * @pllx_hotspot_dअगरf: hotspot offset from the PLLX sensor, must be 0 क्रम
    PLLX sensor group
 * @pllx_hotspot_mask: रेजिस्टर bitfield mask क्रम the HOTSPOT field
 */
काष्ठा tegra_tsensor_group अणु
	स्थिर अक्षर *name;
	u8 id;
	u16 sensor_temp_offset;
	u32 sensor_temp_mask;
	u32 pभाग, pभाग_ate, pभाग_mask;
	u32 pllx_hotspot_dअगरf, pllx_hotspot_mask;
	u32 thermtrip_enable_mask;
	u32 thermtrip_any_en_mask;
	u32 thermtrip_threshold_mask;
	u32 thermctl_isr_mask;
	u16 thermctl_lvl0_offset;
	u32 thermctl_lvl0_up_thresh_mask;
	u32 thermctl_lvl0_dn_thresh_mask;
पूर्ण;

काष्ठा tegra_tsensor_configuration अणु
	u32 tall, tiddq_en, ten_count, pभाग, pभाग_ate, tsample, tsample_ate;
पूर्ण;

काष्ठा tegra_tsensor अणु
	स्थिर अक्षर *name;
	स्थिर u32 base;
	स्थिर काष्ठा tegra_tsensor_configuration *config;
	स्थिर u32 calib_fuse_offset;
	/*
	 * Correction values used to modअगरy values पढ़ो from
	 * calibration fuses
	 */
	स्थिर s32 fuse_corr_alpha, fuse_corr_beta;
	स्थिर काष्ठा tegra_tsensor_group *group;
पूर्ण;

काष्ठा tsensor_group_thermtrips अणु
	u8 id;
	u32 temp;
पूर्ण;

काष्ठा tegra_soctherm_fuse अणु
	u32 fuse_base_cp_mask, fuse_base_cp_shअगरt;
	u32 fuse_base_ft_mask, fuse_base_ft_shअगरt;
	u32 fuse_shअगरt_ft_mask, fuse_shअगरt_ft_shअगरt;
	u32 fuse_spare_realignment;
पूर्ण;

काष्ठा tsensor_shared_calib अणु
	u32 base_cp, base_ft;
	u32 actual_temp_cp, actual_temp_ft;
पूर्ण;

काष्ठा tegra_soctherm_soc अणु
	स्थिर काष्ठा tegra_tsensor *tsensors;
	स्थिर अचिन्हित पूर्णांक num_tsensors;
	स्थिर काष्ठा tegra_tsensor_group **ttgs;
	स्थिर अचिन्हित पूर्णांक num_ttgs;
	स्थिर काष्ठा tegra_soctherm_fuse *tfuse;
	स्थिर पूर्णांक thresh_grain;
	स्थिर अचिन्हित पूर्णांक bptt;
	स्थिर bool use_ccroc;
	काष्ठा tsensor_group_thermtrips *thermtrips;
पूर्ण;

पूर्णांक tegra_calc_shared_calib(स्थिर काष्ठा tegra_soctherm_fuse *tfuse,
			    काष्ठा tsensor_shared_calib *shared);
पूर्णांक tegra_calc_tsensor_calib(स्थिर काष्ठा tegra_tsensor *sensor,
			     स्थिर काष्ठा tsensor_shared_calib *shared,
			     u32 *calib);

#अगर_घोषित CONFIG_ARCH_TEGRA_124_SOC
बाह्य स्थिर काष्ठा tegra_soctherm_soc tegra124_soctherm;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_TEGRA_132_SOC
बाह्य स्थिर काष्ठा tegra_soctherm_soc tegra132_soctherm;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_TEGRA_210_SOC
बाह्य स्थिर काष्ठा tegra_soctherm_soc tegra210_soctherm;
#पूर्ण_अगर

#पूर्ण_अगर

