<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014 - 2018, NVIDIA CORPORATION.  All rights reserved.
 *
 * Author:
 *	Mikko Perttunen <mperttunen@nvidia.com>
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

#समावेश <linux/debugfs.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/thermal.h>

#समावेश <dt-bindings/thermal/tegra124-soctherm.h>

#समावेश "../thermal_core.h"
#समावेश "soctherm.h"

#घोषणा SENSOR_CONFIG0				0
#घोषणा SENSOR_CONFIG0_STOP			BIT(0)
#घोषणा SENSOR_CONFIG0_CPTR_OVER		BIT(2)
#घोषणा SENSOR_CONFIG0_OVER			BIT(3)
#घोषणा SENSOR_CONFIG0_TCALC_OVER		BIT(4)
#घोषणा SENSOR_CONFIG0_TALL_MASK		(0xfffff << 8)
#घोषणा SENSOR_CONFIG0_TALL_SHIFT		8

#घोषणा SENSOR_CONFIG1				4
#घोषणा SENSOR_CONFIG1_TSAMPLE_MASK		0x3ff
#घोषणा SENSOR_CONFIG1_TSAMPLE_SHIFT		0
#घोषणा SENSOR_CONFIG1_TIDDQ_EN_MASK		(0x3f << 15)
#घोषणा SENSOR_CONFIG1_TIDDQ_EN_SHIFT		15
#घोषणा SENSOR_CONFIG1_TEN_COUNT_MASK		(0x3f << 24)
#घोषणा SENSOR_CONFIG1_TEN_COUNT_SHIFT		24
#घोषणा SENSOR_CONFIG1_TEMP_ENABLE		BIT(31)

/*
 * SENSOR_CONFIG2 is defined in soctherm.h
 * because, it will be used by tegra_soctherm_fuse.c
 */

#घोषणा SENSOR_STATUS0				0xc
#घोषणा SENSOR_STATUS0_VALID_MASK		BIT(31)
#घोषणा SENSOR_STATUS0_CAPTURE_MASK		0xffff

#घोषणा SENSOR_STATUS1				0x10
#घोषणा SENSOR_STATUS1_TEMP_VALID_MASK		BIT(31)
#घोषणा SENSOR_STATUS1_TEMP_MASK		0xffff

#घोषणा READBACK_VALUE_MASK			0xff00
#घोषणा READBACK_VALUE_SHIFT			8
#घोषणा READBACK_ADD_HALF			BIT(7)
#घोषणा READBACK_NEGATE				BIT(0)

/*
 * THERMCTL_LEVEL0_GROUP_CPU is defined in soctherm.h
 * because it will be used by tegraxxx_soctherm.c
 */
#घोषणा THERMCTL_LVL0_CPU0_EN_MASK		BIT(8)
#घोषणा THERMCTL_LVL0_CPU0_CPU_THROT_MASK	(0x3 << 5)
#घोषणा THERMCTL_LVL0_CPU0_CPU_THROT_LIGHT	0x1
#घोषणा THERMCTL_LVL0_CPU0_CPU_THROT_HEAVY	0x2
#घोषणा THERMCTL_LVL0_CPU0_GPU_THROT_MASK	(0x3 << 3)
#घोषणा THERMCTL_LVL0_CPU0_GPU_THROT_LIGHT	0x1
#घोषणा THERMCTL_LVL0_CPU0_GPU_THROT_HEAVY	0x2
#घोषणा THERMCTL_LVL0_CPU0_MEM_THROT_MASK	BIT(2)
#घोषणा THERMCTL_LVL0_CPU0_STATUS_MASK		0x3

#घोषणा THERMCTL_LVL0_UP_STATS			0x10
#घोषणा THERMCTL_LVL0_DN_STATS			0x14

#घोषणा THERMCTL_INTR_STATUS			0x84

#घोषणा TH_INTR_MD0_MASK			BIT(25)
#घोषणा TH_INTR_MU0_MASK			BIT(24)
#घोषणा TH_INTR_GD0_MASK			BIT(17)
#घोषणा TH_INTR_GU0_MASK			BIT(16)
#घोषणा TH_INTR_CD0_MASK			BIT(9)
#घोषणा TH_INTR_CU0_MASK			BIT(8)
#घोषणा TH_INTR_PD0_MASK			BIT(1)
#घोषणा TH_INTR_PU0_MASK			BIT(0)
#घोषणा TH_INTR_IGNORE_MASK			0xFCFCFCFC

#घोषणा THERMCTL_STATS_CTL			0x94
#घोषणा STATS_CTL_CLR_DN			0x8
#घोषणा STATS_CTL_EN_DN				0x4
#घोषणा STATS_CTL_CLR_UP			0x2
#घोषणा STATS_CTL_EN_UP				0x1

#घोषणा OC1_CFG					0x310
#घोषणा OC1_CFG_LONG_LATENCY_MASK		BIT(6)
#घोषणा OC1_CFG_HW_RESTORE_MASK			BIT(5)
#घोषणा OC1_CFG_PWR_GOOD_MASK_MASK		BIT(4)
#घोषणा OC1_CFG_THROTTLE_MODE_MASK		(0x3 << 2)
#घोषणा OC1_CFG_ALARM_POLARITY_MASK		BIT(1)
#घोषणा OC1_CFG_EN_THROTTLE_MASK		BIT(0)

#घोषणा OC1_CNT_THRESHOLD			0x314
#घोषणा OC1_THROTTLE_PERIOD			0x318
#घोषणा OC1_ALARM_COUNT				0x31c
#घोषणा OC1_FILTER				0x320
#घोषणा OC1_STATS				0x3a8

#घोषणा OC_INTR_STATUS				0x39c
#घोषणा OC_INTR_ENABLE				0x3a0
#घोषणा OC_INTR_DISABLE				0x3a4
#घोषणा OC_STATS_CTL				0x3c4
#घोषणा OC_STATS_CTL_CLR_ALL			0x2
#घोषणा OC_STATS_CTL_EN_ALL			0x1

#घोषणा OC_INTR_OC1_MASK			BIT(0)
#घोषणा OC_INTR_OC2_MASK			BIT(1)
#घोषणा OC_INTR_OC3_MASK			BIT(2)
#घोषणा OC_INTR_OC4_MASK			BIT(3)
#घोषणा OC_INTR_OC5_MASK			BIT(4)

#घोषणा THROT_GLOBAL_CFG			0x400
#घोषणा THROT_GLOBAL_ENB_MASK			BIT(0)

#घोषणा CPU_PSKIP_STATUS			0x418
#घोषणा XPU_PSKIP_STATUS_M_MASK			(0xff << 12)
#घोषणा XPU_PSKIP_STATUS_N_MASK			(0xff << 4)
#घोषणा XPU_PSKIP_STATUS_SW_OVERRIDE_MASK	BIT(1)
#घोषणा XPU_PSKIP_STATUS_ENABLED_MASK		BIT(0)

#घोषणा THROT_PRIORITY_LOCK			0x424
#घोषणा THROT_PRIORITY_LOCK_PRIORITY_MASK	0xff

#घोषणा THROT_STATUS				0x428
#घोषणा THROT_STATUS_BREACH_MASK		BIT(12)
#घोषणा THROT_STATUS_STATE_MASK			(0xff << 4)
#घोषणा THROT_STATUS_ENABLED_MASK		BIT(0)

#घोषणा THROT_PSKIP_CTRL_LITE_CPU		0x430
#घोषणा THROT_PSKIP_CTRL_ENABLE_MASK            BIT(31)
#घोषणा THROT_PSKIP_CTRL_DIVIDEND_MASK          (0xff << 8)
#घोषणा THROT_PSKIP_CTRL_DIVISOR_MASK           0xff
#घोषणा THROT_PSKIP_CTRL_VECT_GPU_MASK          (0x7 << 16)
#घोषणा THROT_PSKIP_CTRL_VECT_CPU_MASK          (0x7 << 8)
#घोषणा THROT_PSKIP_CTRL_VECT2_CPU_MASK         0x7

#घोषणा THROT_VECT_NONE				0x0 /* 3'b000 */
#घोषणा THROT_VECT_LOW				0x1 /* 3'b001 */
#घोषणा THROT_VECT_MED				0x3 /* 3'b011 */
#घोषणा THROT_VECT_HIGH				0x7 /* 3'b111 */

#घोषणा THROT_PSKIP_RAMP_LITE_CPU		0x434
#घोषणा THROT_PSKIP_RAMP_SEQ_BYPASS_MODE_MASK	BIT(31)
#घोषणा THROT_PSKIP_RAMP_DURATION_MASK		(0xffff << 8)
#घोषणा THROT_PSKIP_RAMP_STEP_MASK		0xff

#घोषणा THROT_PRIORITY_LITE			0x444
#घोषणा THROT_PRIORITY_LITE_PRIO_MASK		0xff

#घोषणा THROT_DELAY_LITE			0x448
#घोषणा THROT_DELAY_LITE_DELAY_MASK		0xff

/* car रेजिस्टर offsets needed क्रम enabling HW throttling */
#घोषणा CAR_SUPER_CCLKG_DIVIDER			0x36c
#घोषणा CDIVG_USE_THERM_CONTROLS_MASK		BIT(30)

/* ccroc रेजिस्टर offsets needed क्रम enabling HW throttling क्रम Tegra132 */
#घोषणा CCROC_SUPER_CCLKG_DIVIDER		0x024

#घोषणा CCROC_GLOBAL_CFG			0x148

#घोषणा CCROC_THROT_PSKIP_RAMP_CPU		0x150
#घोषणा CCROC_THROT_PSKIP_RAMP_SEQ_BYPASS_MODE_MASK	BIT(31)
#घोषणा CCROC_THROT_PSKIP_RAMP_DURATION_MASK	(0xffff << 8)
#घोषणा CCROC_THROT_PSKIP_RAMP_STEP_MASK	0xff

#घोषणा CCROC_THROT_PSKIP_CTRL_CPU		0x154
#घोषणा CCROC_THROT_PSKIP_CTRL_ENB_MASK		BIT(31)
#घोषणा CCROC_THROT_PSKIP_CTRL_DIVIDEND_MASK	(0xff << 8)
#घोषणा CCROC_THROT_PSKIP_CTRL_DIVISOR_MASK	0xff

/* get val from रेजिस्टर(r) mask bits(m) */
#घोषणा REG_GET_MASK(r, m)	(((r) & (m)) >> (ffs(m) - 1))
/* set val(v) to mask bits(m) of रेजिस्टर(r) */
#घोषणा REG_SET_MASK(r, m, v)	(((r) & ~(m)) | \
				 (((v) & (m >> (ffs(m) - 1))) << (ffs(m) - 1)))

/* get भागidend from the depth */
#घोषणा THROT_DEPTH_DIVIDEND(depth)	((256 * (100 - (depth)) / 100) - 1)

/* gk20a nv_therm पूर्णांकerface N:3 Mapping. Levels defined in tegra124-soctherm.h
 * level	vector
 * NONE		3'b000
 * LOW		3'b001
 * MED		3'b011
 * HIGH		3'b111
 */
#घोषणा THROT_LEVEL_TO_DEPTH(level)	((0x1 << (level)) - 1)

/* get THROT_PSKIP_xxx offset per LIGHT/HEAVY throt and CPU/GPU dev */
#घोषणा THROT_OFFSET			0x30
#घोषणा THROT_PSKIP_CTRL(throt, dev)	(THROT_PSKIP_CTRL_LITE_CPU + \
					(THROT_OFFSET * throt) + (8 * dev))
#घोषणा THROT_PSKIP_RAMP(throt, dev)	(THROT_PSKIP_RAMP_LITE_CPU + \
					(THROT_OFFSET * throt) + (8 * dev))

/* get THROT_xxx_CTRL offset per LIGHT/HEAVY throt */
#घोषणा THROT_PRIORITY_CTRL(throt)	(THROT_PRIORITY_LITE + \
					(THROT_OFFSET * throt))
#घोषणा THROT_DELAY_CTRL(throt)		(THROT_DELAY_LITE + \
					(THROT_OFFSET * throt))

#घोषणा ALARM_OFFSET			0x14
#घोषणा ALARM_CFG(throt)		(OC1_CFG + \
					(ALARM_OFFSET * (throt - THROTTLE_OC1)))

#घोषणा ALARM_CNT_THRESHOLD(throt)	(OC1_CNT_THRESHOLD + \
					(ALARM_OFFSET * (throt - THROTTLE_OC1)))

#घोषणा ALARM_THROTTLE_PERIOD(throt)	(OC1_THROTTLE_PERIOD + \
					(ALARM_OFFSET * (throt - THROTTLE_OC1)))

#घोषणा ALARM_ALARM_COUNT(throt)	(OC1_ALARM_COUNT + \
					(ALARM_OFFSET * (throt - THROTTLE_OC1)))

#घोषणा ALARM_FILTER(throt)		(OC1_FILTER + \
					(ALARM_OFFSET * (throt - THROTTLE_OC1)))

#घोषणा ALARM_STATS(throt)		(OC1_STATS + \
					(4 * (throt - THROTTLE_OC1)))

/* get CCROC_THROT_PSKIP_xxx offset per HIGH/MED/LOW vect*/
#घोषणा CCROC_THROT_OFFSET			0x0c
#घोषणा CCROC_THROT_PSKIP_CTRL_CPU_REG(vect)    (CCROC_THROT_PSKIP_CTRL_CPU + \
						(CCROC_THROT_OFFSET * vect))
#घोषणा CCROC_THROT_PSKIP_RAMP_CPU_REG(vect)    (CCROC_THROT_PSKIP_RAMP_CPU + \
						(CCROC_THROT_OFFSET * vect))

/* get THERMCTL_LEVELx offset per CPU/GPU/MEM/TSENSE rg and LEVEL0~3 lv */
#घोषणा THERMCTL_LVL_REGS_SIZE		0x20
#घोषणा THERMCTL_LVL_REG(rg, lv)	((rg) + ((lv) * THERMCTL_LVL_REGS_SIZE))

#घोषणा OC_THROTTLE_MODE_DISABLED	0
#घोषणा OC_THROTTLE_MODE_BRIEF		2

अटल स्थिर पूर्णांक min_low_temp = -127000;
अटल स्थिर पूर्णांक max_high_temp = 127000;

क्रमागत soctherm_throttle_id अणु
	THROTTLE_LIGHT = 0,
	THROTTLE_HEAVY,
	THROTTLE_OC1,
	THROTTLE_OC2,
	THROTTLE_OC3,
	THROTTLE_OC4,
	THROTTLE_OC5, /* OC5 is reserved */
	THROTTLE_SIZE,
पूर्ण;

क्रमागत soctherm_oc_irq_id अणु
	TEGRA_SOC_OC_IRQ_1,
	TEGRA_SOC_OC_IRQ_2,
	TEGRA_SOC_OC_IRQ_3,
	TEGRA_SOC_OC_IRQ_4,
	TEGRA_SOC_OC_IRQ_5,
	TEGRA_SOC_OC_IRQ_MAX,
पूर्ण;

क्रमागत soctherm_throttle_dev_id अणु
	THROTTLE_DEV_CPU = 0,
	THROTTLE_DEV_GPU,
	THROTTLE_DEV_SIZE,
पूर्ण;

अटल स्थिर अक्षर *स्थिर throt_names[] = अणु
	[THROTTLE_LIGHT] = "light",
	[THROTTLE_HEAVY] = "heavy",
	[THROTTLE_OC1]   = "oc1",
	[THROTTLE_OC2]   = "oc2",
	[THROTTLE_OC3]   = "oc3",
	[THROTTLE_OC4]   = "oc4",
	[THROTTLE_OC5]   = "oc5",
पूर्ण;

काष्ठा tegra_soctherm;
काष्ठा tegra_thermctl_zone अणु
	व्योम __iomem *reg;
	काष्ठा device *dev;
	काष्ठा tegra_soctherm *ts;
	काष्ठा thermal_zone_device *tz;
	स्थिर काष्ठा tegra_tsensor_group *sg;
पूर्ण;

काष्ठा soctherm_oc_cfg अणु
	u32 active_low;
	u32 throt_period;
	u32 alarm_cnt_thresh;
	u32 alarm_filter;
	u32 mode;
	bool पूर्णांकr_en;
पूर्ण;

काष्ठा soctherm_throt_cfg अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक id;
	u8 priority;
	u8 cpu_throt_level;
	u32 cpu_throt_depth;
	u32 gpu_throt_level;
	काष्ठा soctherm_oc_cfg oc_cfg;
	काष्ठा thermal_cooling_device *cdev;
	bool init;
पूर्ण;

काष्ठा tegra_soctherm अणु
	काष्ठा reset_control *reset;
	काष्ठा clk *घड़ी_प्रकारsensor;
	काष्ठा clk *घड़ी_soctherm;
	व्योम __iomem *regs;
	व्योम __iomem *clk_regs;
	व्योम __iomem *ccroc_regs;

	पूर्णांक thermal_irq;
	पूर्णांक edp_irq;

	u32 *calib;
	काष्ठा thermal_zone_device **thermctl_tzs;
	काष्ठा tegra_soctherm_soc *soc;

	काष्ठा soctherm_throt_cfg throt_cfgs[THROTTLE_SIZE];

	काष्ठा dentry *debugfs_dir;

	काष्ठा mutex thermctl_lock;
पूर्ण;

काष्ठा soctherm_oc_irq_chip_data अणु
	काष्ठा mutex		irq_lock; /* serialize OC IRQs */
	काष्ठा irq_chip		irq_chip;
	काष्ठा irq_करोमुख्य	*करोमुख्य;
	पूर्णांक			irq_enable;
पूर्ण;

अटल काष्ठा soctherm_oc_irq_chip_data soc_irq_cdata;

/**
 * ccroc_ग_लिखोl() - ग_लिखोs a value to a CCROC रेजिस्टर
 * @ts: poपूर्णांकer to a काष्ठा tegra_soctherm
 * @value: the value to ग_लिखो
 * @reg: the रेजिस्टर offset
 *
 * Writes @v to @reg.  No वापस value.
 */
अटल अंतरभूत व्योम ccroc_ग_लिखोl(काष्ठा tegra_soctherm *ts, u32 value, u32 reg)
अणु
	ग_लिखोl(value, (ts->ccroc_regs + reg));
पूर्ण

/**
 * ccroc_पढ़ोl() - पढ़ोs specअगरied रेजिस्टर from CCROC IP block
 * @ts: poपूर्णांकer to a काष्ठा tegra_soctherm
 * @reg: रेजिस्टर address to be पढ़ो
 *
 * Return: the value of the रेजिस्टर
 */
अटल अंतरभूत u32 ccroc_पढ़ोl(काष्ठा tegra_soctherm *ts, u32 reg)
अणु
	वापस पढ़ोl(ts->ccroc_regs + reg);
पूर्ण

अटल व्योम enable_tsensor(काष्ठा tegra_soctherm *tegra, अचिन्हित पूर्णांक i)
अणु
	स्थिर काष्ठा tegra_tsensor *sensor = &tegra->soc->tsensors[i];
	व्योम __iomem *base = tegra->regs + sensor->base;
	अचिन्हित पूर्णांक val;

	val = sensor->config->tall << SENSOR_CONFIG0_TALL_SHIFT;
	ग_लिखोl(val, base + SENSOR_CONFIG0);

	val  = (sensor->config->tsample - 1) << SENSOR_CONFIG1_TSAMPLE_SHIFT;
	val |= sensor->config->tiddq_en << SENSOR_CONFIG1_TIDDQ_EN_SHIFT;
	val |= sensor->config->ten_count << SENSOR_CONFIG1_TEN_COUNT_SHIFT;
	val |= SENSOR_CONFIG1_TEMP_ENABLE;
	ग_लिखोl(val, base + SENSOR_CONFIG1);

	ग_लिखोl(tegra->calib[i], base + SENSOR_CONFIG2);
पूर्ण

/*
 * Translate from soctherm पढ़ोback क्रमmat to millicelsius.
 * The soctherm पढ़ोback क्रमmat in bits is as follows:
 *   TTTTTTTT H______N
 * where T's contain the temperature in Celsius,
 * H denotes an addition of 0.5 Celsius and N denotes negation
 * of the final value.
 */
अटल पूर्णांक translate_temp(u16 val)
अणु
	पूर्णांक t;

	t = ((val & READBACK_VALUE_MASK) >> READBACK_VALUE_SHIFT) * 1000;
	अगर (val & READBACK_ADD_HALF)
		t += 500;
	अगर (val & READBACK_NEGATE)
		t *= -1;

	वापस t;
पूर्ण

अटल पूर्णांक tegra_thermctl_get_temp(व्योम *data, पूर्णांक *out_temp)
अणु
	काष्ठा tegra_thermctl_zone *zone = data;
	u32 val;

	val = पढ़ोl(zone->reg);
	val = REG_GET_MASK(val, zone->sg->sensor_temp_mask);
	*out_temp = translate_temp(val);

	वापस 0;
पूर्ण

/**
 * enक्रमce_temp_range() - check and enक्रमce temperature range [min, max]
 * @dev: काष्ठा device * of the SOC_THERM instance
 * @trip_temp: the trip temperature to check
 *
 * Checks and enक्रमces the permitted temperature range that SOC_THERM
 * HW can support This is
 * करोne जबतक taking care of precision.
 *
 * Return: The precision adjusted capped temperature in millicelsius.
 */
अटल पूर्णांक enक्रमce_temp_range(काष्ठा device *dev, पूर्णांक trip_temp)
अणु
	पूर्णांक temp;

	temp = clamp_val(trip_temp, min_low_temp, max_high_temp);
	अगर (temp != trip_temp)
		dev_info(dev, "soctherm: trip temperature %d forced to %d\n",
			 trip_temp, temp);
	वापस temp;
पूर्ण

/**
 * thermtrip_program() - Configures the hardware to shut करोwn the
 * प्रणाली अगर a given sensor group reaches a given temperature
 * @dev: ptr to the काष्ठा device क्रम the SOC_THERM IP block
 * @sg: poपूर्णांकer to the sensor group to set the thermtrip temperature क्रम
 * @trip_temp: the temperature in millicelsius to trigger the thermal trip at
 *
 * Sets the thermal trip threshold of the given sensor group to be the
 * @trip_temp.  If this threshold is crossed, the hardware will shut
 * करोwn.
 *
 * Note that, although @trip_temp is specअगरied in millicelsius, the
 * hardware is programmed in degrees Celsius.
 *
 * Return: 0 upon success, or %-EINVAL upon failure.
 */
अटल पूर्णांक thermtrip_program(काष्ठा device *dev,
			     स्थिर काष्ठा tegra_tsensor_group *sg,
			     पूर्णांक trip_temp)
अणु
	काष्ठा tegra_soctherm *ts = dev_get_drvdata(dev);
	पूर्णांक temp;
	u32 r;

	अगर (!sg || !sg->thermtrip_threshold_mask)
		वापस -EINVAL;

	temp = enक्रमce_temp_range(dev, trip_temp) / ts->soc->thresh_grain;

	r = पढ़ोl(ts->regs + THERMCTL_THERMTRIP_CTL);
	r = REG_SET_MASK(r, sg->thermtrip_threshold_mask, temp);
	r = REG_SET_MASK(r, sg->thermtrip_enable_mask, 1);
	r = REG_SET_MASK(r, sg->thermtrip_any_en_mask, 0);
	ग_लिखोl(r, ts->regs + THERMCTL_THERMTRIP_CTL);

	वापस 0;
पूर्ण

/**
 * throttrip_program() - Configures the hardware to throttle the
 * pulse अगर a given sensor group reaches a given temperature
 * @dev: ptr to the काष्ठा device क्रम the SOC_THERM IP block
 * @sg: poपूर्णांकer to the sensor group to set the thermtrip temperature क्रम
 * @stc: poपूर्णांकer to the throttle need to be triggered
 * @trip_temp: the temperature in millicelsius to trigger the thermal trip at
 *
 * Sets the thermal trip threshold and throttle event of the given sensor
 * group. If this threshold is crossed, the hardware will trigger the
 * throttle.
 *
 * Note that, although @trip_temp is specअगरied in millicelsius, the
 * hardware is programmed in degrees Celsius.
 *
 * Return: 0 upon success, or %-EINVAL upon failure.
 */
अटल पूर्णांक throttrip_program(काष्ठा device *dev,
			     स्थिर काष्ठा tegra_tsensor_group *sg,
			     काष्ठा soctherm_throt_cfg *stc,
			     पूर्णांक trip_temp)
अणु
	काष्ठा tegra_soctherm *ts = dev_get_drvdata(dev);
	पूर्णांक temp, cpu_throt, gpu_throt;
	अचिन्हित पूर्णांक throt;
	u32 r, reg_off;

	अगर (!sg || !stc || !stc->init)
		वापस -EINVAL;

	temp = enक्रमce_temp_range(dev, trip_temp) / ts->soc->thresh_grain;

	/* Hardcode LIGHT on LEVEL1 and HEAVY on LEVEL2 */
	throt = stc->id;
	reg_off = THERMCTL_LVL_REG(sg->thermctl_lvl0_offset, throt + 1);

	अगर (throt == THROTTLE_LIGHT) अणु
		cpu_throt = THERMCTL_LVL0_CPU0_CPU_THROT_LIGHT;
		gpu_throt = THERMCTL_LVL0_CPU0_GPU_THROT_LIGHT;
	पूर्ण अन्यथा अणु
		cpu_throt = THERMCTL_LVL0_CPU0_CPU_THROT_HEAVY;
		gpu_throt = THERMCTL_LVL0_CPU0_GPU_THROT_HEAVY;
		अगर (throt != THROTTLE_HEAVY)
			dev_warn(dev,
				 "invalid throt id %d - assuming HEAVY",
				 throt);
	पूर्ण

	r = पढ़ोl(ts->regs + reg_off);
	r = REG_SET_MASK(r, sg->thermctl_lvl0_up_thresh_mask, temp);
	r = REG_SET_MASK(r, sg->thermctl_lvl0_dn_thresh_mask, temp);
	r = REG_SET_MASK(r, THERMCTL_LVL0_CPU0_CPU_THROT_MASK, cpu_throt);
	r = REG_SET_MASK(r, THERMCTL_LVL0_CPU0_GPU_THROT_MASK, gpu_throt);
	r = REG_SET_MASK(r, THERMCTL_LVL0_CPU0_EN_MASK, 1);
	ग_लिखोl(r, ts->regs + reg_off);

	वापस 0;
पूर्ण

अटल काष्ठा soctherm_throt_cfg *
find_throttle_cfg_by_name(काष्ठा tegra_soctherm *ts, स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; ts->throt_cfgs[i].name; i++)
		अगर (!म_भेद(ts->throt_cfgs[i].name, name))
			वापस &ts->throt_cfgs[i];

	वापस शून्य;
पूर्ण

अटल पूर्णांक tsensor_group_thermtrip_get(काष्ठा tegra_soctherm *ts, पूर्णांक id)
अणु
	पूर्णांक i, temp = min_low_temp;
	काष्ठा tsensor_group_thermtrips *tt = ts->soc->thermtrips;

	अगर (id >= TEGRA124_SOCTHERM_SENSOR_NUM)
		वापस temp;

	अगर (tt) अणु
		क्रम (i = 0; i < ts->soc->num_ttgs; i++) अणु
			अगर (tt[i].id == id)
				वापस tt[i].temp;
		पूर्ण
	पूर्ण

	वापस temp;
पूर्ण

अटल पूर्णांक tegra_thermctl_set_trip_temp(व्योम *data, पूर्णांक trip, पूर्णांक temp)
अणु
	काष्ठा tegra_thermctl_zone *zone = data;
	काष्ठा thermal_zone_device *tz = zone->tz;
	काष्ठा tegra_soctherm *ts = zone->ts;
	स्थिर काष्ठा tegra_tsensor_group *sg = zone->sg;
	काष्ठा device *dev = zone->dev;
	क्रमागत thermal_trip_type type;
	पूर्णांक ret;

	अगर (!tz)
		वापस -EINVAL;

	ret = tz->ops->get_trip_type(tz, trip, &type);
	अगर (ret)
		वापस ret;

	अगर (type == THERMAL_TRIP_CRITICAL) अणु
		/*
		 * If thermtrips property is set in DT,
		 * करोesn't need to program critical type trip to HW,
		 * अगर not, program critical trip to HW.
		 */
		अगर (min_low_temp == tsensor_group_thermtrip_get(ts, sg->id))
			वापस thermtrip_program(dev, sg, temp);
		अन्यथा
			वापस 0;

	पूर्ण अन्यथा अगर (type == THERMAL_TRIP_HOT) अणु
		पूर्णांक i;

		क्रम (i = 0; i < THROTTLE_SIZE; i++) अणु
			काष्ठा thermal_cooling_device *cdev;
			काष्ठा soctherm_throt_cfg *stc;

			अगर (!ts->throt_cfgs[i].init)
				जारी;

			cdev = ts->throt_cfgs[i].cdev;
			अगर (get_thermal_instance(tz, cdev, trip))
				stc = find_throttle_cfg_by_name(ts, cdev->type);
			अन्यथा
				जारी;

			वापस throttrip_program(dev, sg, stc, temp);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_thermctl_get_trend(व्योम *data, पूर्णांक trip,
				    क्रमागत thermal_trend *trend)
अणु
	काष्ठा tegra_thermctl_zone *zone = data;
	काष्ठा thermal_zone_device *tz = zone->tz;
	पूर्णांक trip_temp, temp, last_temp, ret;

	अगर (!tz)
		वापस -EINVAL;

	ret = tz->ops->get_trip_temp(zone->tz, trip, &trip_temp);
	अगर (ret)
		वापस ret;

	temp = READ_ONCE(tz->temperature);
	last_temp = READ_ONCE(tz->last_temperature);

	अगर (temp > trip_temp) अणु
		अगर (temp >= last_temp)
			*trend = THERMAL_TREND_RAISING;
		अन्यथा
			*trend = THERMAL_TREND_STABLE;
	पूर्ण अन्यथा अगर (temp < trip_temp) अणु
		*trend = THERMAL_TREND_DROPPING;
	पूर्ण अन्यथा अणु
		*trend = THERMAL_TREND_STABLE;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम thermal_irq_enable(काष्ठा tegra_thermctl_zone *zn)
अणु
	u32 r;

	/* multiple zones could be handling and setting trips at once */
	mutex_lock(&zn->ts->thermctl_lock);
	r = पढ़ोl(zn->ts->regs + THERMCTL_INTR_ENABLE);
	r = REG_SET_MASK(r, zn->sg->thermctl_isr_mask, TH_INTR_UP_DN_EN);
	ग_लिखोl(r, zn->ts->regs + THERMCTL_INTR_ENABLE);
	mutex_unlock(&zn->ts->thermctl_lock);
पूर्ण

अटल व्योम thermal_irq_disable(काष्ठा tegra_thermctl_zone *zn)
अणु
	u32 r;

	/* multiple zones could be handling and setting trips at once */
	mutex_lock(&zn->ts->thermctl_lock);
	r = पढ़ोl(zn->ts->regs + THERMCTL_INTR_DISABLE);
	r = REG_SET_MASK(r, zn->sg->thermctl_isr_mask, 0);
	ग_लिखोl(r, zn->ts->regs + THERMCTL_INTR_DISABLE);
	mutex_unlock(&zn->ts->thermctl_lock);
पूर्ण

अटल पूर्णांक tegra_thermctl_set_trips(व्योम *data, पूर्णांक lo, पूर्णांक hi)
अणु
	काष्ठा tegra_thermctl_zone *zone = data;
	u32 r;

	thermal_irq_disable(zone);

	r = पढ़ोl(zone->ts->regs + zone->sg->thermctl_lvl0_offset);
	r = REG_SET_MASK(r, THERMCTL_LVL0_CPU0_EN_MASK, 0);
	ग_लिखोl(r, zone->ts->regs + zone->sg->thermctl_lvl0_offset);

	lo = enक्रमce_temp_range(zone->dev, lo) / zone->ts->soc->thresh_grain;
	hi = enक्रमce_temp_range(zone->dev, hi) / zone->ts->soc->thresh_grain;
	dev_dbg(zone->dev, "%s hi:%d, lo:%d\n", __func__, hi, lo);

	r = REG_SET_MASK(r, zone->sg->thermctl_lvl0_up_thresh_mask, hi);
	r = REG_SET_MASK(r, zone->sg->thermctl_lvl0_dn_thresh_mask, lo);
	r = REG_SET_MASK(r, THERMCTL_LVL0_CPU0_EN_MASK, 1);
	ग_लिखोl(r, zone->ts->regs + zone->sg->thermctl_lvl0_offset);

	thermal_irq_enable(zone);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops tegra_of_thermal_ops = अणु
	.get_temp = tegra_thermctl_get_temp,
	.set_trip_temp = tegra_thermctl_set_trip_temp,
	.get_trend = tegra_thermctl_get_trend,
	.set_trips = tegra_thermctl_set_trips,
पूर्ण;

अटल पूर्णांक get_hot_temp(काष्ठा thermal_zone_device *tz, पूर्णांक *trip, पूर्णांक *temp)
अणु
	पूर्णांक ntrips, i, ret;
	क्रमागत thermal_trip_type type;

	ntrips = of_thermal_get_ntrips(tz);
	अगर (ntrips <= 0)
		वापस -EINVAL;

	क्रम (i = 0; i < ntrips; i++) अणु
		ret = tz->ops->get_trip_type(tz, i, &type);
		अगर (ret)
			वापस -EINVAL;
		अगर (type == THERMAL_TRIP_HOT) अणु
			ret = tz->ops->get_trip_temp(tz, i, temp);
			अगर (!ret)
				*trip = i;

			वापस ret;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * tegra_soctherm_set_hwtrips() - set HW trip poपूर्णांक from DT data
 * @dev: काष्ठा device * of the SOC_THERM instance
 * @sg: poपूर्णांकer to the sensor group to set the thermtrip temperature क्रम
 * @tz: काष्ठा thermal_zone_device *
 *
 * Configure the SOC_THERM HW trip poपूर्णांकs, setting "THERMTRIP"
 * "THROTTLE" trip poपूर्णांकs , using "thermtrips", "critical" or "hot"
 * type trip_temp
 * from thermal zone.
 * After they have been configured, THERMTRIP or THROTTLE will take
 * action when the configured SoC thermal sensor group reaches a
 * certain temperature.
 *
 * Return: 0 upon success, or a negative error code on failure.
 * "Success" करोes not mean that trips was enabled; it could also
 * mean that no node was found in DT.
 * THERMTRIP has been enabled successfully when a message similar to
 * this one appears on the serial console:
 * "thermtrip: will shut down when sensor group XXX reaches YYYYYY mC"
 * THROTTLE has been enabled successfully when a message similar to
 * this one appears on the serial console:
 * ""throttrip: will throttle when sensor group XXX reaches YYYYYY mC"
 */
अटल पूर्णांक tegra_soctherm_set_hwtrips(काष्ठा device *dev,
				      स्थिर काष्ठा tegra_tsensor_group *sg,
				      काष्ठा thermal_zone_device *tz)
अणु
	काष्ठा tegra_soctherm *ts = dev_get_drvdata(dev);
	काष्ठा soctherm_throt_cfg *stc;
	पूर्णांक i, trip, temperature, ret;

	/* Get thermtrips. If missing, try to get critical trips. */
	temperature = tsensor_group_thermtrip_get(ts, sg->id);
	अगर (min_low_temp == temperature)
		अगर (tz->ops->get_crit_temp(tz, &temperature))
			temperature = max_high_temp;

	ret = thermtrip_program(dev, sg, temperature);
	अगर (ret) अणु
		dev_err(dev, "thermtrip: %s: error during enable\n", sg->name);
		वापस ret;
	पूर्ण

	dev_info(dev, "thermtrip: will shut down when %s reaches %d mC\n",
		 sg->name, temperature);

	ret = get_hot_temp(tz, &trip, &temperature);
	अगर (ret) अणु
		dev_info(dev, "throttrip: %s: missing hot temperature\n",
			 sg->name);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < THROTTLE_OC1; i++) अणु
		काष्ठा thermal_cooling_device *cdev;

		अगर (!ts->throt_cfgs[i].init)
			जारी;

		cdev = ts->throt_cfgs[i].cdev;
		अगर (get_thermal_instance(tz, cdev, trip))
			stc = find_throttle_cfg_by_name(ts, cdev->type);
		अन्यथा
			जारी;

		ret = throttrip_program(dev, sg, stc, temperature);
		अगर (ret) अणु
			dev_err(dev, "throttrip: %s: error during enable\n",
				sg->name);
			वापस ret;
		पूर्ण

		dev_info(dev,
			 "throttrip: will throttle when %s reaches %d mC\n",
			 sg->name, temperature);
		अवरोध;
	पूर्ण

	अगर (i == THROTTLE_SIZE)
		dev_info(dev, "throttrip: %s: missing throttle cdev\n",
			 sg->name);

	वापस 0;
पूर्ण

अटल irqवापस_t soctherm_thermal_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा tegra_soctherm *ts = dev_id;
	u32 r;

	/* Case क्रम no lock:
	 * Although पूर्णांकerrupts are enabled in set_trips, there is still no need
	 * to lock here because the पूर्णांकerrupts are disabled beक्रमe programming
	 * new trip poपूर्णांकs. Hence there cant be a पूर्णांकerrupt on the same sensor.
	 * An पूर्णांकerrupt can however occur on a sensor जबतक trips are being
	 * programmed on a dअगरferent one. This beign a LEVEL पूर्णांकerrupt won't
	 * cause a new पूर्णांकerrupt but this is taken care of by the re-पढ़ोing of
	 * the STATUS रेजिस्टर in the thपढ़ो function.
	 */
	r = पढ़ोl(ts->regs + THERMCTL_INTR_STATUS);
	ग_लिखोl(r, ts->regs + THERMCTL_INTR_DISABLE);

	वापस IRQ_WAKE_THREAD;
पूर्ण

/**
 * soctherm_thermal_isr_thपढ़ो() - Handles a thermal पूर्णांकerrupt request
 * @irq:       The पूर्णांकerrupt number being requested; not used
 * @dev_id:    Opaque poपूर्णांकer to tegra_soctherm;
 *
 * Clears the पूर्णांकerrupt status रेजिस्टर अगर there are expected
 * पूर्णांकerrupt bits set.
 * The पूर्णांकerrupt(s) are then handled by updating the corresponding
 * thermal zones.
 *
 * An error is logged अगर any unexpected पूर्णांकerrupt bits are set.
 *
 * Disabled पूर्णांकerrupts are re-enabled.
 *
 * Return: %IRQ_HANDLED. Interrupt was handled and no further processing
 * is needed.
 */
अटल irqवापस_t soctherm_thermal_isr_thपढ़ो(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा tegra_soctherm *ts = dev_id;
	काष्ठा thermal_zone_device *tz;
	u32 st, ex = 0, cp = 0, gp = 0, pl = 0, me = 0;

	st = पढ़ोl(ts->regs + THERMCTL_INTR_STATUS);

	/* deliberately clear expected पूर्णांकerrupts handled in SW */
	cp |= st & TH_INTR_CD0_MASK;
	cp |= st & TH_INTR_CU0_MASK;

	gp |= st & TH_INTR_GD0_MASK;
	gp |= st & TH_INTR_GU0_MASK;

	pl |= st & TH_INTR_PD0_MASK;
	pl |= st & TH_INTR_PU0_MASK;

	me |= st & TH_INTR_MD0_MASK;
	me |= st & TH_INTR_MU0_MASK;

	ex |= cp | gp | pl | me;
	अगर (ex) अणु
		ग_लिखोl(ex, ts->regs + THERMCTL_INTR_STATUS);
		st &= ~ex;

		अगर (cp) अणु
			tz = ts->thermctl_tzs[TEGRA124_SOCTHERM_SENSOR_CPU];
			thermal_zone_device_update(tz,
						   THERMAL_EVENT_UNSPECIFIED);
		पूर्ण

		अगर (gp) अणु
			tz = ts->thermctl_tzs[TEGRA124_SOCTHERM_SENSOR_GPU];
			thermal_zone_device_update(tz,
						   THERMAL_EVENT_UNSPECIFIED);
		पूर्ण

		अगर (pl) अणु
			tz = ts->thermctl_tzs[TEGRA124_SOCTHERM_SENSOR_PLLX];
			thermal_zone_device_update(tz,
						   THERMAL_EVENT_UNSPECIFIED);
		पूर्ण

		अगर (me) अणु
			tz = ts->thermctl_tzs[TEGRA124_SOCTHERM_SENSOR_MEM];
			thermal_zone_device_update(tz,
						   THERMAL_EVENT_UNSPECIFIED);
		पूर्ण
	पूर्ण

	/* deliberately ignore expected पूर्णांकerrupts NOT handled in SW */
	ex |= TH_INTR_IGNORE_MASK;
	st &= ~ex;

	अगर (st) अणु
		/* Whine about any other unexpected INTR bits still set */
		pr_err("soctherm: Ignored unexpected INTRs 0x%08x\n", st);
		ग_लिखोl(st, ts->regs + THERMCTL_INTR_STATUS);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/**
 * soctherm_oc_पूर्णांकr_enable() - Enables the soctherm over-current पूर्णांकerrupt
 * @ts:		poपूर्णांकer to a काष्ठा tegra_soctherm
 * @alarm:		The soctherm throttle id
 * @enable:		Flag indicating enable the soctherm over-current
 *			पूर्णांकerrupt or disable it
 *
 * Enables a specअगरic over-current pins @alarm to उठाओ an पूर्णांकerrupt अगर the flag
 * is set and the alarm corresponds to OC1, OC2, OC3, or OC4.
 */
अटल व्योम soctherm_oc_पूर्णांकr_enable(काष्ठा tegra_soctherm *ts,
				    क्रमागत soctherm_throttle_id alarm,
				    bool enable)
अणु
	u32 r;

	अगर (!enable)
		वापस;

	r = पढ़ोl(ts->regs + OC_INTR_ENABLE);
	चयन (alarm) अणु
	हाल THROTTLE_OC1:
		r = REG_SET_MASK(r, OC_INTR_OC1_MASK, 1);
		अवरोध;
	हाल THROTTLE_OC2:
		r = REG_SET_MASK(r, OC_INTR_OC2_MASK, 1);
		अवरोध;
	हाल THROTTLE_OC3:
		r = REG_SET_MASK(r, OC_INTR_OC3_MASK, 1);
		अवरोध;
	हाल THROTTLE_OC4:
		r = REG_SET_MASK(r, OC_INTR_OC4_MASK, 1);
		अवरोध;
	शेष:
		r = 0;
		अवरोध;
	पूर्ण
	ग_लिखोl(r, ts->regs + OC_INTR_ENABLE);
पूर्ण

/**
 * soctherm_handle_alarm() - Handles soctherm alarms
 * @alarm:		The soctherm throttle id
 *
 * "Handles" over-current alarms (OC1, OC2, OC3, and OC4) by prपूर्णांकing
 * a warning or inक्रमmative message.
 *
 * Return: -EINVAL क्रम @alarm = THROTTLE_OC3, otherwise 0 (success).
 */
अटल पूर्णांक soctherm_handle_alarm(क्रमागत soctherm_throttle_id alarm)
अणु
	पूर्णांक rv = -EINVAL;

	चयन (alarm) अणु
	हाल THROTTLE_OC1:
		pr_debug("soctherm: Successfully handled OC1 alarm\n");
		rv = 0;
		अवरोध;

	हाल THROTTLE_OC2:
		pr_debug("soctherm: Successfully handled OC2 alarm\n");
		rv = 0;
		अवरोध;

	हाल THROTTLE_OC3:
		pr_debug("soctherm: Successfully handled OC3 alarm\n");
		rv = 0;
		अवरोध;

	हाल THROTTLE_OC4:
		pr_debug("soctherm: Successfully handled OC4 alarm\n");
		rv = 0;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (rv)
		pr_err("soctherm: ERROR in handling %s alarm\n",
		       throt_names[alarm]);

	वापस rv;
पूर्ण

/**
 * soctherm_edp_isr_thपढ़ो() - log an over-current पूर्णांकerrupt request
 * @irq:	OC irq number. Currently not being used. See description
 * @arg:	a व्योम poपूर्णांकer क्रम callback, currently not being used
 *
 * Over-current events are handled in hardware. This function is called to log
 * and handle any OC events that happened. Additionally, it checks every
 * over-current पूर्णांकerrupt रेजिस्टरs क्रम रेजिस्टरs are set but
 * was not expected (i.e. any discrepancy in पूर्णांकerrupt status) by the function,
 * the discrepancy will logged.
 *
 * Return: %IRQ_HANDLED
 */
अटल irqवापस_t soctherm_edp_isr_thपढ़ो(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा tegra_soctherm *ts = arg;
	u32 st, ex, oc1, oc2, oc3, oc4;

	st = पढ़ोl(ts->regs + OC_INTR_STATUS);

	/* deliberately clear expected पूर्णांकerrupts handled in SW */
	oc1 = st & OC_INTR_OC1_MASK;
	oc2 = st & OC_INTR_OC2_MASK;
	oc3 = st & OC_INTR_OC3_MASK;
	oc4 = st & OC_INTR_OC4_MASK;
	ex = oc1 | oc2 | oc3 | oc4;

	pr_err("soctherm: OC ALARM 0x%08x\n", ex);
	अगर (ex) अणु
		ग_लिखोl(st, ts->regs + OC_INTR_STATUS);
		st &= ~ex;

		अगर (oc1 && !soctherm_handle_alarm(THROTTLE_OC1))
			soctherm_oc_पूर्णांकr_enable(ts, THROTTLE_OC1, true);

		अगर (oc2 && !soctherm_handle_alarm(THROTTLE_OC2))
			soctherm_oc_पूर्णांकr_enable(ts, THROTTLE_OC2, true);

		अगर (oc3 && !soctherm_handle_alarm(THROTTLE_OC3))
			soctherm_oc_पूर्णांकr_enable(ts, THROTTLE_OC3, true);

		अगर (oc4 && !soctherm_handle_alarm(THROTTLE_OC4))
			soctherm_oc_पूर्णांकr_enable(ts, THROTTLE_OC4, true);

		अगर (oc1 && soc_irq_cdata.irq_enable & BIT(0))
			handle_nested_irq(
				irq_find_mapping(soc_irq_cdata.करोमुख्य, 0));

		अगर (oc2 && soc_irq_cdata.irq_enable & BIT(1))
			handle_nested_irq(
				irq_find_mapping(soc_irq_cdata.करोमुख्य, 1));

		अगर (oc3 && soc_irq_cdata.irq_enable & BIT(2))
			handle_nested_irq(
				irq_find_mapping(soc_irq_cdata.करोमुख्य, 2));

		अगर (oc4 && soc_irq_cdata.irq_enable & BIT(3))
			handle_nested_irq(
				irq_find_mapping(soc_irq_cdata.करोमुख्य, 3));
	पूर्ण

	अगर (st) अणु
		pr_err("soctherm: Ignored unexpected OC ALARM 0x%08x\n", st);
		ग_लिखोl(st, ts->regs + OC_INTR_STATUS);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/**
 * soctherm_edp_isr() - Disables any active पूर्णांकerrupts
 * @irq:	The पूर्णांकerrupt request number
 * @arg:	Opaque poपूर्णांकer to an argument
 *
 * Writes to the OC_INTR_DISABLE रेजिस्टर the over current पूर्णांकerrupt status,
 * masking any निश्चितed पूर्णांकerrupts. Doing this prevents the same पूर्णांकerrupts
 * from triggering this isr repeatedly. The thपढ़ो woken by this isr will
 * handle निश्चितed पूर्णांकerrupts and subsequently unmask/re-enable them.
 *
 * The OC_INTR_DISABLE रेजिस्टर indicates which OC पूर्णांकerrupts
 * have been disabled.
 *
 * Return: %IRQ_WAKE_THREAD, handler requests to wake the handler thपढ़ो
 */
अटल irqवापस_t soctherm_edp_isr(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा tegra_soctherm *ts = arg;
	u32 r;

	अगर (!ts)
		वापस IRQ_NONE;

	r = पढ़ोl(ts->regs + OC_INTR_STATUS);
	ग_लिखोl(r, ts->regs + OC_INTR_DISABLE);

	वापस IRQ_WAKE_THREAD;
पूर्ण

/**
 * soctherm_oc_irq_lock() - locks the over-current पूर्णांकerrupt request
 * @data:	Interrupt request data
 *
 * Looks up the chip data from @data and locks the mutex associated with
 * a particular over-current पूर्णांकerrupt request.
 */
अटल व्योम soctherm_oc_irq_lock(काष्ठा irq_data *data)
अणु
	काष्ठा soctherm_oc_irq_chip_data *d = irq_data_get_irq_chip_data(data);

	mutex_lock(&d->irq_lock);
पूर्ण

/**
 * soctherm_oc_irq_sync_unlock() - Unlocks the OC पूर्णांकerrupt request
 * @data:		Interrupt request data
 *
 * Looks up the पूर्णांकerrupt request data @data and unlocks the mutex associated
 * with a particular over-current पूर्णांकerrupt request.
 */
अटल व्योम soctherm_oc_irq_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा soctherm_oc_irq_chip_data *d = irq_data_get_irq_chip_data(data);

	mutex_unlock(&d->irq_lock);
पूर्ण

/**
 * soctherm_oc_irq_enable() - Enables the SOC_THERM over-current पूर्णांकerrupt queue
 * @data:       irq_data काष्ठाure of the chip
 *
 * Sets the irq_enable bit of SOC_THERM allowing SOC_THERM
 * to respond to over-current पूर्णांकerrupts.
 *
 */
अटल व्योम soctherm_oc_irq_enable(काष्ठा irq_data *data)
अणु
	काष्ठा soctherm_oc_irq_chip_data *d = irq_data_get_irq_chip_data(data);

	d->irq_enable |= BIT(data->hwirq);
पूर्ण

/**
 * soctherm_oc_irq_disable() - Disables overcurrent पूर्णांकerrupt requests
 * @data:	The पूर्णांकerrupt request inक्रमmation
 *
 * Clears the पूर्णांकerrupt request enable bit of the overcurrent
 * पूर्णांकerrupt request chip data.
 *
 * Return: Nothing is वापसed (व्योम)
 */
अटल व्योम soctherm_oc_irq_disable(काष्ठा irq_data *data)
अणु
	काष्ठा soctherm_oc_irq_chip_data *d = irq_data_get_irq_chip_data(data);

	d->irq_enable &= ~BIT(data->hwirq);
पूर्ण

अटल पूर्णांक soctherm_oc_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	वापस 0;
पूर्ण

/**
 * soctherm_oc_irq_map() - SOC_THERM पूर्णांकerrupt request करोमुख्य mapper
 * @h:		Interrupt request करोमुख्य
 * @virq:	Virtual पूर्णांकerrupt request number
 * @hw:		Hardware पूर्णांकerrupt request number
 *
 * Mapping callback function क्रम SOC_THERM's irq_करोमुख्य. When a SOC_THERM
 * पूर्णांकerrupt request is called, the irq_करोमुख्य takes the request's भव
 * request number (much like a भव memory address) and maps it to a
 * physical hardware request number.
 *
 * When a mapping करोesn't alपढ़ोy exist क्रम a भव request number, the
 * irq_करोमुख्य calls this function to associate the भव request number with
 * a hardware request number.
 *
 * Return: 0
 */
अटल पूर्णांक soctherm_oc_irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
		irq_hw_number_t hw)
अणु
	काष्ठा soctherm_oc_irq_chip_data *data = h->host_data;

	irq_set_chip_data(virq, data);
	irq_set_chip(virq, &data->irq_chip);
	irq_set_nested_thपढ़ो(virq, 1);
	वापस 0;
पूर्ण

/**
 * soctherm_irq_करोमुख्य_xlate_twocell() - xlate क्रम soctherm पूर्णांकerrupts
 * @d:      Interrupt request करोमुख्य
 * @ctrlr:      Controller device tree node
 * @पूर्णांकspec:    Array of u32s from DTs "interrupt" property
 * @पूर्णांकsize:    Number of values inside the पूर्णांकspec array
 * @out_hwirq:  HW IRQ value associated with this पूर्णांकerrupt
 * @out_type:   The IRQ SENSE type क्रम this पूर्णांकerrupt.
 *
 * This Device Tree IRQ specअगरier translation function will translate a
 * specअगरic "interrupt" as defined by 2 DT values where the cell values map
 * the hwirq number + 1 and linux irq flags. Since the output is the hwirq
 * number, this function will subtract 1 from the value listed in DT.
 *
 * Return: 0
 */
अटल पूर्णांक soctherm_irq_करोमुख्य_xlate_twocell(काष्ठा irq_करोमुख्य *d,
	काष्ठा device_node *ctrlr, स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
	irq_hw_number_t *out_hwirq, अचिन्हित पूर्णांक *out_type)
अणु
	अगर (WARN_ON(पूर्णांकsize < 2))
		वापस -EINVAL;

	/*
	 * The HW value is 1 index less than the DT IRQ values.
	 * i.e. OC4 goes to HW index 3.
	 */
	*out_hwirq = पूर्णांकspec[0] - 1;
	*out_type = पूर्णांकspec[1] & IRQ_TYPE_SENSE_MASK;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops soctherm_oc_करोमुख्य_ops = अणु
	.map	= soctherm_oc_irq_map,
	.xlate	= soctherm_irq_करोमुख्य_xlate_twocell,
पूर्ण;

/**
 * soctherm_oc_पूर्णांक_init() - Initial enabling of the over
 * current पूर्णांकerrupts
 * @np:	The devicetree node क्रम soctherm
 * @num_irqs:	The number of new पूर्णांकerrupt requests
 *
 * Sets the over current पूर्णांकerrupt request chip data
 *
 * Return: 0 on success or अगर overcurrent पूर्णांकerrupts are not enabled,
 * -ENOMEM (out of memory), or irq_base अगर the function failed to
 * allocate the irqs
 */
अटल पूर्णांक soctherm_oc_पूर्णांक_init(काष्ठा device_node *np, पूर्णांक num_irqs)
अणु
	अगर (!num_irqs) अणु
		pr_info("%s(): OC interrupts are not enabled\n", __func__);
		वापस 0;
	पूर्ण

	mutex_init(&soc_irq_cdata.irq_lock);
	soc_irq_cdata.irq_enable = 0;

	soc_irq_cdata.irq_chip.name = "soc_therm_oc";
	soc_irq_cdata.irq_chip.irq_bus_lock = soctherm_oc_irq_lock;
	soc_irq_cdata.irq_chip.irq_bus_sync_unlock =
		soctherm_oc_irq_sync_unlock;
	soc_irq_cdata.irq_chip.irq_disable = soctherm_oc_irq_disable;
	soc_irq_cdata.irq_chip.irq_enable = soctherm_oc_irq_enable;
	soc_irq_cdata.irq_chip.irq_set_type = soctherm_oc_irq_set_type;
	soc_irq_cdata.irq_chip.irq_set_wake = शून्य;

	soc_irq_cdata.करोमुख्य = irq_करोमुख्य_add_linear(np, num_irqs,
						     &soctherm_oc_करोमुख्य_ops,
						     &soc_irq_cdata);

	अगर (!soc_irq_cdata.करोमुख्य) अणु
		pr_err("%s: Failed to create IRQ domain\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	pr_debug("%s(): OC interrupts enabled successful\n", __func__);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक regs_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = s->निजी;
	काष्ठा tegra_soctherm *ts = platक्रमm_get_drvdata(pdev);
	स्थिर काष्ठा tegra_tsensor *tsensors = ts->soc->tsensors;
	स्थिर काष्ठा tegra_tsensor_group **ttgs = ts->soc->ttgs;
	u32 r, state;
	पूर्णांक i, level;

	seq_माला_दो(s, "-----TSENSE (convert HW)-----\n");

	क्रम (i = 0; i < ts->soc->num_tsensors; i++) अणु
		r = पढ़ोl(ts->regs + tsensors[i].base + SENSOR_CONFIG1);
		state = REG_GET_MASK(r, SENSOR_CONFIG1_TEMP_ENABLE);

		seq_म_लिखो(s, "%s: ", tsensors[i].name);
		seq_म_लिखो(s, "En(%d) ", state);

		अगर (!state) अणु
			seq_माला_दो(s, "\n");
			जारी;
		पूर्ण

		state = REG_GET_MASK(r, SENSOR_CONFIG1_TIDDQ_EN_MASK);
		seq_म_लिखो(s, "tiddq(%d) ", state);
		state = REG_GET_MASK(r, SENSOR_CONFIG1_TEN_COUNT_MASK);
		seq_म_लिखो(s, "ten_count(%d) ", state);
		state = REG_GET_MASK(r, SENSOR_CONFIG1_TSAMPLE_MASK);
		seq_म_लिखो(s, "tsample(%d) ", state + 1);

		r = पढ़ोl(ts->regs + tsensors[i].base + SENSOR_STATUS1);
		state = REG_GET_MASK(r, SENSOR_STATUS1_TEMP_VALID_MASK);
		seq_म_लिखो(s, "Temp(%d/", state);
		state = REG_GET_MASK(r, SENSOR_STATUS1_TEMP_MASK);
		seq_म_लिखो(s, "%d) ", translate_temp(state));

		r = पढ़ोl(ts->regs + tsensors[i].base + SENSOR_STATUS0);
		state = REG_GET_MASK(r, SENSOR_STATUS0_VALID_MASK);
		seq_म_लिखो(s, "Capture(%d/", state);
		state = REG_GET_MASK(r, SENSOR_STATUS0_CAPTURE_MASK);
		seq_म_लिखो(s, "%d) ", state);

		r = पढ़ोl(ts->regs + tsensors[i].base + SENSOR_CONFIG0);
		state = REG_GET_MASK(r, SENSOR_CONFIG0_STOP);
		seq_म_लिखो(s, "Stop(%d) ", state);
		state = REG_GET_MASK(r, SENSOR_CONFIG0_TALL_MASK);
		seq_म_लिखो(s, "Tall(%d) ", state);
		state = REG_GET_MASK(r, SENSOR_CONFIG0_TCALC_OVER);
		seq_म_लिखो(s, "Over(%d/", state);
		state = REG_GET_MASK(r, SENSOR_CONFIG0_OVER);
		seq_म_लिखो(s, "%d/", state);
		state = REG_GET_MASK(r, SENSOR_CONFIG0_CPTR_OVER);
		seq_म_लिखो(s, "%d) ", state);

		r = पढ़ोl(ts->regs + tsensors[i].base + SENSOR_CONFIG2);
		state = REG_GET_MASK(r, SENSOR_CONFIG2_THERMA_MASK);
		seq_म_लिखो(s, "Therm_A/B(%d/", state);
		state = REG_GET_MASK(r, SENSOR_CONFIG2_THERMB_MASK);
		seq_म_लिखो(s, "%d)\n", (s16)state);
	पूर्ण

	r = पढ़ोl(ts->regs + SENSOR_PDIV);
	seq_म_लिखो(s, "PDIV: 0x%x\n", r);

	r = पढ़ोl(ts->regs + SENSOR_HOTSPOT_OFF);
	seq_म_लिखो(s, "HOTSPOT: 0x%x\n", r);

	seq_माला_दो(s, "\n");
	seq_माला_दो(s, "-----SOC_THERM-----\n");

	r = पढ़ोl(ts->regs + SENSOR_TEMP1);
	state = REG_GET_MASK(r, SENSOR_TEMP1_CPU_TEMP_MASK);
	seq_म_लिखो(s, "Temperatures: CPU(%d) ", translate_temp(state));
	state = REG_GET_MASK(r, SENSOR_TEMP1_GPU_TEMP_MASK);
	seq_म_लिखो(s, " GPU(%d) ", translate_temp(state));
	r = पढ़ोl(ts->regs + SENSOR_TEMP2);
	state = REG_GET_MASK(r, SENSOR_TEMP2_PLLX_TEMP_MASK);
	seq_म_लिखो(s, " PLLX(%d) ", translate_temp(state));
	state = REG_GET_MASK(r, SENSOR_TEMP2_MEM_TEMP_MASK);
	seq_म_लिखो(s, " MEM(%d)\n", translate_temp(state));

	क्रम (i = 0; i < ts->soc->num_ttgs; i++) अणु
		seq_म_लिखो(s, "%s:\n", ttgs[i]->name);
		क्रम (level = 0; level < 4; level++) अणु
			s32 v;
			u32 mask;
			u16 off = ttgs[i]->thermctl_lvl0_offset;

			r = पढ़ोl(ts->regs + THERMCTL_LVL_REG(off, level));

			mask = ttgs[i]->thermctl_lvl0_up_thresh_mask;
			state = REG_GET_MASK(r, mask);
			v = sign_extend32(state, ts->soc->bptt - 1);
			v *= ts->soc->thresh_grain;
			seq_म_लिखो(s, "   %d: Up/Dn(%d /", level, v);

			mask = ttgs[i]->thermctl_lvl0_dn_thresh_mask;
			state = REG_GET_MASK(r, mask);
			v = sign_extend32(state, ts->soc->bptt - 1);
			v *= ts->soc->thresh_grain;
			seq_म_लिखो(s, "%d ) ", v);

			mask = THERMCTL_LVL0_CPU0_EN_MASK;
			state = REG_GET_MASK(r, mask);
			seq_म_लिखो(s, "En(%d) ", state);

			mask = THERMCTL_LVL0_CPU0_CPU_THROT_MASK;
			state = REG_GET_MASK(r, mask);
			seq_माला_दो(s, "CPU Throt");
			अगर (!state)
				seq_म_लिखो(s, "(%s) ", "none");
			अन्यथा अगर (state == THERMCTL_LVL0_CPU0_CPU_THROT_LIGHT)
				seq_म_लिखो(s, "(%s) ", "L");
			अन्यथा अगर (state == THERMCTL_LVL0_CPU0_CPU_THROT_HEAVY)
				seq_म_लिखो(s, "(%s) ", "H");
			अन्यथा
				seq_म_लिखो(s, "(%s) ", "H+L");

			mask = THERMCTL_LVL0_CPU0_GPU_THROT_MASK;
			state = REG_GET_MASK(r, mask);
			seq_माला_दो(s, "GPU Throt");
			अगर (!state)
				seq_म_लिखो(s, "(%s) ", "none");
			अन्यथा अगर (state == THERMCTL_LVL0_CPU0_GPU_THROT_LIGHT)
				seq_म_लिखो(s, "(%s) ", "L");
			अन्यथा अगर (state == THERMCTL_LVL0_CPU0_GPU_THROT_HEAVY)
				seq_म_लिखो(s, "(%s) ", "H");
			अन्यथा
				seq_म_लिखो(s, "(%s) ", "H+L");

			mask = THERMCTL_LVL0_CPU0_STATUS_MASK;
			state = REG_GET_MASK(r, mask);
			seq_म_लिखो(s, "Status(%s)\n",
				   state == 0 ? "LO" :
				   state == 1 ? "In" :
				   state == 2 ? "Res" : "HI");
		पूर्ण
	पूर्ण

	r = पढ़ोl(ts->regs + THERMCTL_STATS_CTL);
	seq_म_लिखो(s, "STATS: Up(%s) Dn(%s)\n",
		   r & STATS_CTL_EN_UP ? "En" : "--",
		   r & STATS_CTL_EN_DN ? "En" : "--");

	क्रम (level = 0; level < 4; level++) अणु
		u16 off;

		off = THERMCTL_LVL0_UP_STATS;
		r = पढ़ोl(ts->regs + THERMCTL_LVL_REG(off, level));
		seq_म_लिखो(s, "  Level_%d Up(%d) ", level, r);

		off = THERMCTL_LVL0_DN_STATS;
		r = पढ़ोl(ts->regs + THERMCTL_LVL_REG(off, level));
		seq_म_लिखो(s, "Dn(%d)\n", r);
	पूर्ण

	r = पढ़ोl(ts->regs + THERMCTL_THERMTRIP_CTL);
	state = REG_GET_MASK(r, ttgs[0]->thermtrip_any_en_mask);
	seq_म_लिखो(s, "Thermtrip Any En(%d)\n", state);
	क्रम (i = 0; i < ts->soc->num_ttgs; i++) अणु
		state = REG_GET_MASK(r, ttgs[i]->thermtrip_enable_mask);
		seq_म_लिखो(s, "     %s En(%d) ", ttgs[i]->name, state);
		state = REG_GET_MASK(r, ttgs[i]->thermtrip_threshold_mask);
		state *= ts->soc->thresh_grain;
		seq_म_लिखो(s, "Thresh(%d)\n", state);
	पूर्ण

	r = पढ़ोl(ts->regs + THROT_GLOBAL_CFG);
	seq_माला_दो(s, "\n");
	seq_म_लिखो(s, "GLOBAL THROTTLE CONFIG: 0x%08x\n", r);

	seq_माला_दो(s, "---------------------------------------------------\n");
	r = पढ़ोl(ts->regs + THROT_STATUS);
	state = REG_GET_MASK(r, THROT_STATUS_BREACH_MASK);
	seq_म_लिखो(s, "THROT STATUS: breach(%d) ", state);
	state = REG_GET_MASK(r, THROT_STATUS_STATE_MASK);
	seq_म_लिखो(s, "state(%d) ", state);
	state = REG_GET_MASK(r, THROT_STATUS_ENABLED_MASK);
	seq_म_लिखो(s, "enabled(%d)\n", state);

	r = पढ़ोl(ts->regs + CPU_PSKIP_STATUS);
	अगर (ts->soc->use_ccroc) अणु
		state = REG_GET_MASK(r, XPU_PSKIP_STATUS_ENABLED_MASK);
		seq_म_लिखो(s, "CPU PSKIP STATUS: enabled(%d)\n", state);
	पूर्ण अन्यथा अणु
		state = REG_GET_MASK(r, XPU_PSKIP_STATUS_M_MASK);
		seq_म_लिखो(s, "CPU PSKIP STATUS: M(%d) ", state);
		state = REG_GET_MASK(r, XPU_PSKIP_STATUS_N_MASK);
		seq_म_लिखो(s, "N(%d) ", state);
		state = REG_GET_MASK(r, XPU_PSKIP_STATUS_ENABLED_MASK);
		seq_म_लिखो(s, "enabled(%d)\n", state);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(regs);

अटल व्योम soctherm_debug_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_soctherm *tegra = platक्रमm_get_drvdata(pdev);
	काष्ठा dentry *root;

	root = debugfs_create_dir("soctherm", शून्य);

	tegra->debugfs_dir = root;

	debugfs_create_file("reg_contents", 0644, root, pdev, &regs_fops);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम soctherm_debug_init(काष्ठा platक्रमm_device *pdev) अणुपूर्ण
#पूर्ण_अगर

अटल पूर्णांक soctherm_clk_enable(काष्ठा platक्रमm_device *pdev, bool enable)
अणु
	काष्ठा tegra_soctherm *tegra = platक्रमm_get_drvdata(pdev);
	पूर्णांक err;

	अगर (!tegra->घड़ी_soctherm || !tegra->घड़ी_प्रकारsensor)
		वापस -EINVAL;

	reset_control_निश्चित(tegra->reset);

	अगर (enable) अणु
		err = clk_prepare_enable(tegra->घड़ी_soctherm);
		अगर (err) अणु
			reset_control_deनिश्चित(tegra->reset);
			वापस err;
		पूर्ण

		err = clk_prepare_enable(tegra->घड़ी_प्रकारsensor);
		अगर (err) अणु
			clk_disable_unprepare(tegra->घड़ी_soctherm);
			reset_control_deनिश्चित(tegra->reset);
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		clk_disable_unprepare(tegra->घड़ी_प्रकारsensor);
		clk_disable_unprepare(tegra->घड़ी_soctherm);
	पूर्ण

	reset_control_deनिश्चित(tegra->reset);

	वापस 0;
पूर्ण

अटल पूर्णांक throt_get_cdev_max_state(काष्ठा thermal_cooling_device *cdev,
				    अचिन्हित दीर्घ *max_state)
अणु
	*max_state = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक throt_get_cdev_cur_state(काष्ठा thermal_cooling_device *cdev,
				    अचिन्हित दीर्घ *cur_state)
अणु
	काष्ठा tegra_soctherm *ts = cdev->devdata;
	u32 r;

	r = पढ़ोl(ts->regs + THROT_STATUS);
	अगर (REG_GET_MASK(r, THROT_STATUS_STATE_MASK))
		*cur_state = 1;
	अन्यथा
		*cur_state = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक throt_set_cdev_state(काष्ठा thermal_cooling_device *cdev,
				अचिन्हित दीर्घ cur_state)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_cooling_device_ops throt_cooling_ops = अणु
	.get_max_state = throt_get_cdev_max_state,
	.get_cur_state = throt_get_cdev_cur_state,
	.set_cur_state = throt_set_cdev_state,
पूर्ण;

अटल पूर्णांक soctherm_thermtrips_parse(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा tegra_soctherm *ts = dev_get_drvdata(dev);
	काष्ठा tsensor_group_thermtrips *tt = ts->soc->thermtrips;
	स्थिर पूर्णांक max_num_prop = ts->soc->num_ttgs * 2;
	u32 *tlb;
	पूर्णांक i, j, n, ret;

	अगर (!tt)
		वापस -ENOMEM;

	n = of_property_count_u32_elems(dev->of_node, "nvidia,thermtrips");
	अगर (n <= 0) अणु
		dev_info(dev,
			 "missing thermtrips, will use critical trips as shut down temp\n");
		वापस n;
	पूर्ण

	n = min(max_num_prop, n);

	tlb = devm_kसुस्मृति(&pdev->dev, max_num_prop, माप(u32), GFP_KERNEL);
	अगर (!tlb)
		वापस -ENOMEM;
	ret = of_property_पढ़ो_u32_array(dev->of_node, "nvidia,thermtrips",
					 tlb, n);
	अगर (ret) अणु
		dev_err(dev, "invalid num ele: thermtrips:%d\n", ret);
		वापस ret;
	पूर्ण

	i = 0;
	क्रम (j = 0; j < n; j = j + 2) अणु
		अगर (tlb[j] >= TEGRA124_SOCTHERM_SENSOR_NUM)
			जारी;

		tt[i].id = tlb[j];
		tt[i].temp = tlb[j + 1];
		i++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम soctherm_oc_cfg_parse(काष्ठा device *dev,
				काष्ठा device_node *np_oc,
				काष्ठा soctherm_throt_cfg *stc)
अणु
	u32 val;

	अगर (of_property_पढ़ो_bool(np_oc, "nvidia,polarity-active-low"))
		stc->oc_cfg.active_low = 1;
	अन्यथा
		stc->oc_cfg.active_low = 0;

	अगर (!of_property_पढ़ो_u32(np_oc, "nvidia,count-threshold", &val)) अणु
		stc->oc_cfg.पूर्णांकr_en = 1;
		stc->oc_cfg.alarm_cnt_thresh = val;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(np_oc, "nvidia,throttle-period-us", &val))
		stc->oc_cfg.throt_period = val;

	अगर (!of_property_पढ़ो_u32(np_oc, "nvidia,alarm-filter", &val))
		stc->oc_cfg.alarm_filter = val;

	/* BRIEF throttling by शेष, करो not support STICKY */
	stc->oc_cfg.mode = OC_THROTTLE_MODE_BRIEF;
पूर्ण

अटल पूर्णांक soctherm_throt_cfg_parse(काष्ठा device *dev,
				    काष्ठा device_node *np,
				    काष्ठा soctherm_throt_cfg *stc)
अणु
	काष्ठा tegra_soctherm *ts = dev_get_drvdata(dev);
	पूर्णांक ret;
	u32 val;

	ret = of_property_पढ़ो_u32(np, "nvidia,priority", &val);
	अगर (ret) अणु
		dev_err(dev, "throttle-cfg: %s: invalid priority\n", stc->name);
		वापस -EINVAL;
	पूर्ण
	stc->priority = val;

	ret = of_property_पढ़ो_u32(np, ts->soc->use_ccroc ?
				   "nvidia,cpu-throt-level" :
				   "nvidia,cpu-throt-percent", &val);
	अगर (!ret) अणु
		अगर (ts->soc->use_ccroc &&
		    val <= TEGRA_SOCTHERM_THROT_LEVEL_HIGH)
			stc->cpu_throt_level = val;
		अन्यथा अगर (!ts->soc->use_ccroc && val <= 100)
			stc->cpu_throt_depth = val;
		अन्यथा
			जाओ err;
	पूर्ण अन्यथा अणु
		जाओ err;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "nvidia,gpu-throt-level", &val);
	अगर (!ret && val <= TEGRA_SOCTHERM_THROT_LEVEL_HIGH)
		stc->gpu_throt_level = val;
	अन्यथा
		जाओ err;

	वापस 0;

err:
	dev_err(dev, "throttle-cfg: %s: no throt prop or invalid prop\n",
		stc->name);
	वापस -EINVAL;
पूर्ण

/**
 * soctherm_init_hw_throt_cdev() - Parse the HW throttle configurations
 * and रेजिस्टर them as cooling devices.
 * @pdev: Poपूर्णांकer to platक्रमm_device काष्ठा
 */
अटल व्योम soctherm_init_hw_throt_cdev(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा tegra_soctherm *ts = dev_get_drvdata(dev);
	काष्ठा device_node *np_stc, *np_stcc;
	स्थिर अक्षर *name;
	पूर्णांक i;

	क्रम (i = 0; i < THROTTLE_SIZE; i++) अणु
		ts->throt_cfgs[i].name = throt_names[i];
		ts->throt_cfgs[i].id = i;
		ts->throt_cfgs[i].init = false;
	पूर्ण

	np_stc = of_get_child_by_name(dev->of_node, "throttle-cfgs");
	अगर (!np_stc) अणु
		dev_info(dev,
			 "throttle-cfg: no throttle-cfgs - not enabling\n");
		वापस;
	पूर्ण

	क्रम_each_child_of_node(np_stc, np_stcc) अणु
		काष्ठा soctherm_throt_cfg *stc;
		काष्ठा thermal_cooling_device *tcd;
		पूर्णांक err;

		name = np_stcc->name;
		stc = find_throttle_cfg_by_name(ts, name);
		अगर (!stc) अणु
			dev_err(dev,
				"throttle-cfg: could not find %s\n", name);
			जारी;
		पूर्ण

		अगर (stc->init) अणु
			dev_err(dev, "throttle-cfg: %s: redefined!\n", name);
			of_node_put(np_stcc);
			अवरोध;
		पूर्ण

		err = soctherm_throt_cfg_parse(dev, np_stcc, stc);
		अगर (err)
			जारी;

		अगर (stc->id >= THROTTLE_OC1) अणु
			soctherm_oc_cfg_parse(dev, np_stcc, stc);
			stc->init = true;
		पूर्ण अन्यथा अणु

			tcd = thermal_of_cooling_device_रेजिस्टर(np_stcc,
							 (अक्षर *)name, ts,
							 &throt_cooling_ops);
			अगर (IS_ERR_OR_शून्य(tcd)) अणु
				dev_err(dev,
					"throttle-cfg: %s: failed to register cooling device\n",
					name);
				जारी;
			पूर्ण
			stc->cdev = tcd;
			stc->init = true;
		पूर्ण

	पूर्ण

	of_node_put(np_stc);
पूर्ण

/**
 * throttlectl_cpu_level_cfg() - programs CCROC NV_THERM level config
 * @ts: poपूर्णांकer to a काष्ठा tegra_soctherm
 * @level: describing the level LOW/MED/HIGH of throttling
 *
 * It's necessary to set up the CPU-local CCROC NV_THERM instance with
 * the M/N values desired क्रम each level. This function करोes this.
 *
 * This function pre-programs the CCROC NV_THERM levels in terms of
 * pre-configured "Low", "Medium" or "Heavy" throttle levels which are
 * mapped to THROT_LEVEL_LOW, THROT_LEVEL_MED and THROT_LEVEL_HVY.
 */
अटल व्योम throttlectl_cpu_level_cfg(काष्ठा tegra_soctherm *ts, पूर्णांक level)
अणु
	u8 depth, भागidend;
	u32 r;

	चयन (level) अणु
	हाल TEGRA_SOCTHERM_THROT_LEVEL_LOW:
		depth = 50;
		अवरोध;
	हाल TEGRA_SOCTHERM_THROT_LEVEL_MED:
		depth = 75;
		अवरोध;
	हाल TEGRA_SOCTHERM_THROT_LEVEL_HIGH:
		depth = 80;
		अवरोध;
	हाल TEGRA_SOCTHERM_THROT_LEVEL_NONE:
		वापस;
	शेष:
		वापस;
	पूर्ण

	भागidend = THROT_DEPTH_DIVIDEND(depth);

	/* setup PSKIP in ccroc nv_therm रेजिस्टरs */
	r = ccroc_पढ़ोl(ts, CCROC_THROT_PSKIP_RAMP_CPU_REG(level));
	r = REG_SET_MASK(r, CCROC_THROT_PSKIP_RAMP_DURATION_MASK, 0xff);
	r = REG_SET_MASK(r, CCROC_THROT_PSKIP_RAMP_STEP_MASK, 0xf);
	ccroc_ग_लिखोl(ts, r, CCROC_THROT_PSKIP_RAMP_CPU_REG(level));

	r = ccroc_पढ़ोl(ts, CCROC_THROT_PSKIP_CTRL_CPU_REG(level));
	r = REG_SET_MASK(r, CCROC_THROT_PSKIP_CTRL_ENB_MASK, 1);
	r = REG_SET_MASK(r, CCROC_THROT_PSKIP_CTRL_DIVIDEND_MASK, भागidend);
	r = REG_SET_MASK(r, CCROC_THROT_PSKIP_CTRL_DIVISOR_MASK, 0xff);
	ccroc_ग_लिखोl(ts, r, CCROC_THROT_PSKIP_CTRL_CPU_REG(level));
पूर्ण

/**
 * throttlectl_cpu_level_select() - program CPU pulse skipper config
 * @ts: poपूर्णांकer to a काष्ठा tegra_soctherm
 * @throt: the LIGHT/HEAVY of throttle event id
 *
 * Pulse skippers are used to throttle घड़ी frequencies.  This
 * function programs the pulse skippers based on @throt and platक्रमm
 * data.  This function is used on SoCs which have CPU-local pulse
 * skipper control, such as T13x. It programs soctherm's पूर्णांकerface to
 * Denver:CCROC NV_THERM in terms of Low, Medium and HIGH throttling
 * vectors. PSKIP_BYPASS mode is set as required per HW spec.
 */
अटल व्योम throttlectl_cpu_level_select(काष्ठा tegra_soctherm *ts,
					 क्रमागत soctherm_throttle_id throt)
अणु
	u32 r, throt_vect;

	/* Denver:CCROC NV_THERM पूर्णांकerface N:3 Mapping */
	चयन (ts->throt_cfgs[throt].cpu_throt_level) अणु
	हाल TEGRA_SOCTHERM_THROT_LEVEL_LOW:
		throt_vect = THROT_VECT_LOW;
		अवरोध;
	हाल TEGRA_SOCTHERM_THROT_LEVEL_MED:
		throt_vect = THROT_VECT_MED;
		अवरोध;
	हाल TEGRA_SOCTHERM_THROT_LEVEL_HIGH:
		throt_vect = THROT_VECT_HIGH;
		अवरोध;
	शेष:
		throt_vect = THROT_VECT_NONE;
		अवरोध;
	पूर्ण

	r = पढ़ोl(ts->regs + THROT_PSKIP_CTRL(throt, THROTTLE_DEV_CPU));
	r = REG_SET_MASK(r, THROT_PSKIP_CTRL_ENABLE_MASK, 1);
	r = REG_SET_MASK(r, THROT_PSKIP_CTRL_VECT_CPU_MASK, throt_vect);
	r = REG_SET_MASK(r, THROT_PSKIP_CTRL_VECT2_CPU_MASK, throt_vect);
	ग_लिखोl(r, ts->regs + THROT_PSKIP_CTRL(throt, THROTTLE_DEV_CPU));

	/* bypass sequencer in soc_therm as it is programmed in ccroc */
	r = REG_SET_MASK(0, THROT_PSKIP_RAMP_SEQ_BYPASS_MODE_MASK, 1);
	ग_लिखोl(r, ts->regs + THROT_PSKIP_RAMP(throt, THROTTLE_DEV_CPU));
पूर्ण

/**
 * throttlectl_cpu_mn() - program CPU pulse skipper configuration
 * @ts: poपूर्णांकer to a काष्ठा tegra_soctherm
 * @throt: the LIGHT/HEAVY of throttle event id
 *
 * Pulse skippers are used to throttle घड़ी frequencies.  This
 * function programs the pulse skippers based on @throt and platक्रमm
 * data.  This function is used क्रम CPUs that have "remote" pulse
 * skipper control, e.g., the CPU pulse skipper is controlled by the
 * SOC_THERM IP block.  (SOC_THERM is located outside the CPU
 * complex.)
 */
अटल व्योम throttlectl_cpu_mn(काष्ठा tegra_soctherm *ts,
			       क्रमागत soctherm_throttle_id throt)
अणु
	u32 r;
	पूर्णांक depth;
	u8 भागidend;

	depth = ts->throt_cfgs[throt].cpu_throt_depth;
	भागidend = THROT_DEPTH_DIVIDEND(depth);

	r = पढ़ोl(ts->regs + THROT_PSKIP_CTRL(throt, THROTTLE_DEV_CPU));
	r = REG_SET_MASK(r, THROT_PSKIP_CTRL_ENABLE_MASK, 1);
	r = REG_SET_MASK(r, THROT_PSKIP_CTRL_DIVIDEND_MASK, भागidend);
	r = REG_SET_MASK(r, THROT_PSKIP_CTRL_DIVISOR_MASK, 0xff);
	ग_लिखोl(r, ts->regs + THROT_PSKIP_CTRL(throt, THROTTLE_DEV_CPU));

	r = पढ़ोl(ts->regs + THROT_PSKIP_RAMP(throt, THROTTLE_DEV_CPU));
	r = REG_SET_MASK(r, THROT_PSKIP_RAMP_DURATION_MASK, 0xff);
	r = REG_SET_MASK(r, THROT_PSKIP_RAMP_STEP_MASK, 0xf);
	ग_लिखोl(r, ts->regs + THROT_PSKIP_RAMP(throt, THROTTLE_DEV_CPU));
पूर्ण

/**
 * throttlectl_gpu_level_select() - selects throttling level क्रम GPU
 * @ts: poपूर्णांकer to a काष्ठा tegra_soctherm
 * @throt: the LIGHT/HEAVY of throttle event id
 *
 * This function programs soctherm's पूर्णांकerface to GK20a NV_THERM to select
 * pre-configured "Low", "Medium" or "Heavy" throttle levels.
 *
 * Return: boolean true अगर HW was programmed
 */
अटल व्योम throttlectl_gpu_level_select(काष्ठा tegra_soctherm *ts,
					 क्रमागत soctherm_throttle_id throt)
अणु
	u32 r, level, throt_vect;

	level = ts->throt_cfgs[throt].gpu_throt_level;
	throt_vect = THROT_LEVEL_TO_DEPTH(level);
	r = पढ़ोl(ts->regs + THROT_PSKIP_CTRL(throt, THROTTLE_DEV_GPU));
	r = REG_SET_MASK(r, THROT_PSKIP_CTRL_ENABLE_MASK, 1);
	r = REG_SET_MASK(r, THROT_PSKIP_CTRL_VECT_GPU_MASK, throt_vect);
	ग_लिखोl(r, ts->regs + THROT_PSKIP_CTRL(throt, THROTTLE_DEV_GPU));
पूर्ण

अटल पूर्णांक soctherm_oc_cfg_program(काष्ठा tegra_soctherm *ts,
				      क्रमागत soctherm_throttle_id throt)
अणु
	u32 r;
	काष्ठा soctherm_oc_cfg *oc = &ts->throt_cfgs[throt].oc_cfg;

	अगर (oc->mode == OC_THROTTLE_MODE_DISABLED)
		वापस -EINVAL;

	r = REG_SET_MASK(0, OC1_CFG_HW_RESTORE_MASK, 1);
	r = REG_SET_MASK(r, OC1_CFG_THROTTLE_MODE_MASK, oc->mode);
	r = REG_SET_MASK(r, OC1_CFG_ALARM_POLARITY_MASK, oc->active_low);
	r = REG_SET_MASK(r, OC1_CFG_EN_THROTTLE_MASK, 1);
	ग_लिखोl(r, ts->regs + ALARM_CFG(throt));
	ग_लिखोl(oc->throt_period, ts->regs + ALARM_THROTTLE_PERIOD(throt));
	ग_लिखोl(oc->alarm_cnt_thresh, ts->regs + ALARM_CNT_THRESHOLD(throt));
	ग_लिखोl(oc->alarm_filter, ts->regs + ALARM_FILTER(throt));
	soctherm_oc_पूर्णांकr_enable(ts, throt, oc->पूर्णांकr_en);

	वापस 0;
पूर्ण

/**
 * soctherm_throttle_program() - programs pulse skippers' configuration
 * @ts: poपूर्णांकer to a काष्ठा tegra_soctherm
 * @throt: the LIGHT/HEAVY of the throttle event id.
 *
 * Pulse skippers are used to throttle घड़ी frequencies.
 * This function programs the pulse skippers.
 */
अटल व्योम soctherm_throttle_program(काष्ठा tegra_soctherm *ts,
				      क्रमागत soctherm_throttle_id throt)
अणु
	u32 r;
	काष्ठा soctherm_throt_cfg stc = ts->throt_cfgs[throt];

	अगर (!stc.init)
		वापस;

	अगर ((throt >= THROTTLE_OC1) && (soctherm_oc_cfg_program(ts, throt)))
		वापस;

	/* Setup PSKIP parameters */
	अगर (ts->soc->use_ccroc)
		throttlectl_cpu_level_select(ts, throt);
	अन्यथा
		throttlectl_cpu_mn(ts, throt);

	throttlectl_gpu_level_select(ts, throt);

	r = REG_SET_MASK(0, THROT_PRIORITY_LITE_PRIO_MASK, stc.priority);
	ग_लिखोl(r, ts->regs + THROT_PRIORITY_CTRL(throt));

	r = REG_SET_MASK(0, THROT_DELAY_LITE_DELAY_MASK, 0);
	ग_लिखोl(r, ts->regs + THROT_DELAY_CTRL(throt));

	r = पढ़ोl(ts->regs + THROT_PRIORITY_LOCK);
	r = REG_GET_MASK(r, THROT_PRIORITY_LOCK_PRIORITY_MASK);
	अगर (r >= stc.priority)
		वापस;
	r = REG_SET_MASK(0, THROT_PRIORITY_LOCK_PRIORITY_MASK,
			 stc.priority);
	ग_लिखोl(r, ts->regs + THROT_PRIORITY_LOCK);
पूर्ण

अटल व्योम tegra_soctherm_throttle(काष्ठा device *dev)
अणु
	काष्ठा tegra_soctherm *ts = dev_get_drvdata(dev);
	u32 v;
	पूर्णांक i;

	/* configure LOW, MED and HIGH levels क्रम CCROC NV_THERM */
	अगर (ts->soc->use_ccroc) अणु
		throttlectl_cpu_level_cfg(ts, TEGRA_SOCTHERM_THROT_LEVEL_LOW);
		throttlectl_cpu_level_cfg(ts, TEGRA_SOCTHERM_THROT_LEVEL_MED);
		throttlectl_cpu_level_cfg(ts, TEGRA_SOCTHERM_THROT_LEVEL_HIGH);
	पूर्ण

	/* Thermal HW throttle programming */
	क्रम (i = 0; i < THROTTLE_SIZE; i++)
		soctherm_throttle_program(ts, i);

	v = REG_SET_MASK(0, THROT_GLOBAL_ENB_MASK, 1);
	अगर (ts->soc->use_ccroc) अणु
		ccroc_ग_लिखोl(ts, v, CCROC_GLOBAL_CFG);

		v = ccroc_पढ़ोl(ts, CCROC_SUPER_CCLKG_DIVIDER);
		v = REG_SET_MASK(v, CDIVG_USE_THERM_CONTROLS_MASK, 1);
		ccroc_ग_लिखोl(ts, v, CCROC_SUPER_CCLKG_DIVIDER);
	पूर्ण अन्यथा अणु
		ग_लिखोl(v, ts->regs + THROT_GLOBAL_CFG);

		v = पढ़ोl(ts->clk_regs + CAR_SUPER_CCLKG_DIVIDER);
		v = REG_SET_MASK(v, CDIVG_USE_THERM_CONTROLS_MASK, 1);
		ग_लिखोl(v, ts->clk_regs + CAR_SUPER_CCLKG_DIVIDER);
	पूर्ण

	/* initialize stats collection */
	v = STATS_CTL_CLR_DN | STATS_CTL_EN_DN |
	    STATS_CTL_CLR_UP | STATS_CTL_EN_UP;
	ग_लिखोl(v, ts->regs + THERMCTL_STATS_CTL);
पूर्ण

अटल पूर्णांक soctherm_पूर्णांकerrupts_init(काष्ठा platक्रमm_device *pdev,
				    काष्ठा tegra_soctherm *tegra)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक ret;

	ret = soctherm_oc_पूर्णांक_init(np, TEGRA_SOC_OC_IRQ_MAX);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "soctherm_oc_int_init failed\n");
		वापस ret;
	पूर्ण

	tegra->thermal_irq = platक्रमm_get_irq(pdev, 0);
	अगर (tegra->thermal_irq < 0) अणु
		dev_dbg(&pdev->dev, "get 'thermal_irq' failed.\n");
		वापस 0;
	पूर्ण

	tegra->edp_irq = platक्रमm_get_irq(pdev, 1);
	अगर (tegra->edp_irq < 0) अणु
		dev_dbg(&pdev->dev, "get 'edp_irq' failed.\n");
		वापस 0;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev,
					tegra->thermal_irq,
					soctherm_thermal_isr,
					soctherm_thermal_isr_thपढ़ो,
					IRQF_ONESHOT,
					dev_name(&pdev->dev),
					tegra);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "request_irq 'thermal_irq' failed.\n");
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev,
					tegra->edp_irq,
					soctherm_edp_isr,
					soctherm_edp_isr_thपढ़ो,
					IRQF_ONESHOT,
					"soctherm_edp",
					tegra);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "request_irq 'edp_irq' failed.\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम soctherm_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_soctherm *tegra = platक्रमm_get_drvdata(pdev);
	स्थिर काष्ठा tegra_tsensor_group **ttgs = tegra->soc->ttgs;
	पूर्णांक i;
	u32 pभाग, hotspot;

	/* Initialize raw sensors */
	क्रम (i = 0; i < tegra->soc->num_tsensors; ++i)
		enable_tsensor(tegra, i);

	/* program pभाग and hotspot offsets per THERM */
	pभाग = पढ़ोl(tegra->regs + SENSOR_PDIV);
	hotspot = पढ़ोl(tegra->regs + SENSOR_HOTSPOT_OFF);
	क्रम (i = 0; i < tegra->soc->num_ttgs; ++i) अणु
		pभाग = REG_SET_MASK(pभाग, ttgs[i]->pभाग_mask,
				    ttgs[i]->pभाग);
		/* hotspot offset from PLLX, करोesn't need to configure PLLX */
		अगर (ttgs[i]->id == TEGRA124_SOCTHERM_SENSOR_PLLX)
			जारी;
		hotspot =  REG_SET_MASK(hotspot,
					ttgs[i]->pllx_hotspot_mask,
					ttgs[i]->pllx_hotspot_dअगरf);
	पूर्ण
	ग_लिखोl(pभाग, tegra->regs + SENSOR_PDIV);
	ग_लिखोl(hotspot, tegra->regs + SENSOR_HOTSPOT_OFF);

	/* Configure hw throttle */
	tegra_soctherm_throttle(&pdev->dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra_soctherm_of_match[] = अणु
#अगर_घोषित CONFIG_ARCH_TEGRA_124_SOC
	अणु
		.compatible = "nvidia,tegra124-soctherm",
		.data = &tegra124_soctherm,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_TEGRA_132_SOC
	अणु
		.compatible = "nvidia,tegra132-soctherm",
		.data = &tegra132_soctherm,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_TEGRA_210_SOC
	अणु
		.compatible = "nvidia,tegra210-soctherm",
		.data = &tegra210_soctherm,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_soctherm_of_match);

अटल पूर्णांक tegra_soctherm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा tegra_soctherm *tegra;
	काष्ठा thermal_zone_device *z;
	काष्ठा tsensor_shared_calib shared_calib;
	काष्ठा tegra_soctherm_soc *soc;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	match = of_match_node(tegra_soctherm_of_match, pdev->dev.of_node);
	अगर (!match)
		वापस -ENODEV;

	soc = (काष्ठा tegra_soctherm_soc *)match->data;
	अगर (soc->num_ttgs > TEGRA124_SOCTHERM_SENSOR_NUM)
		वापस -EINVAL;

	tegra = devm_kzalloc(&pdev->dev, माप(*tegra), GFP_KERNEL);
	अगर (!tegra)
		वापस -ENOMEM;

	mutex_init(&tegra->thermctl_lock);
	dev_set_drvdata(&pdev->dev, tegra);

	tegra->soc = soc;

	tegra->regs = devm_platक्रमm_ioremap_resource_byname(pdev, "soctherm-reg");
	अगर (IS_ERR(tegra->regs)) अणु
		dev_err(&pdev->dev, "can't get soctherm registers");
		वापस PTR_ERR(tegra->regs);
	पूर्ण

	अगर (!tegra->soc->use_ccroc) अणु
		tegra->clk_regs = devm_platक्रमm_ioremap_resource_byname(pdev, "car-reg");
		अगर (IS_ERR(tegra->clk_regs)) अणु
			dev_err(&pdev->dev, "can't get car clk registers");
			वापस PTR_ERR(tegra->clk_regs);
		पूर्ण
	पूर्ण अन्यथा अणु
		tegra->ccroc_regs = devm_platक्रमm_ioremap_resource_byname(pdev, "ccroc-reg");
		अगर (IS_ERR(tegra->ccroc_regs)) अणु
			dev_err(&pdev->dev, "can't get ccroc registers");
			वापस PTR_ERR(tegra->ccroc_regs);
		पूर्ण
	पूर्ण

	tegra->reset = devm_reset_control_get(&pdev->dev, "soctherm");
	अगर (IS_ERR(tegra->reset)) अणु
		dev_err(&pdev->dev, "can't get soctherm reset\n");
		वापस PTR_ERR(tegra->reset);
	पूर्ण

	tegra->घड़ी_प्रकारsensor = devm_clk_get(&pdev->dev, "tsensor");
	अगर (IS_ERR(tegra->घड़ी_प्रकारsensor)) अणु
		dev_err(&pdev->dev, "can't get tsensor clock\n");
		वापस PTR_ERR(tegra->घड़ी_प्रकारsensor);
	पूर्ण

	tegra->घड़ी_soctherm = devm_clk_get(&pdev->dev, "soctherm");
	अगर (IS_ERR(tegra->घड़ी_soctherm)) अणु
		dev_err(&pdev->dev, "can't get soctherm clock\n");
		वापस PTR_ERR(tegra->घड़ी_soctherm);
	पूर्ण

	tegra->calib = devm_kसुस्मृति(&pdev->dev,
				    soc->num_tsensors, माप(u32),
				    GFP_KERNEL);
	अगर (!tegra->calib)
		वापस -ENOMEM;

	/* calculate shared calibration data */
	err = tegra_calc_shared_calib(soc->tfuse, &shared_calib);
	अगर (err)
		वापस err;

	/* calculate tsensor calibration data */
	क्रम (i = 0; i < soc->num_tsensors; ++i) अणु
		err = tegra_calc_tsensor_calib(&soc->tsensors[i],
					       &shared_calib,
					       &tegra->calib[i]);
		अगर (err)
			वापस err;
	पूर्ण

	tegra->thermctl_tzs = devm_kसुस्मृति(&pdev->dev,
					   soc->num_ttgs, माप(z),
					   GFP_KERNEL);
	अगर (!tegra->thermctl_tzs)
		वापस -ENOMEM;

	err = soctherm_clk_enable(pdev, true);
	अगर (err)
		वापस err;

	soctherm_thermtrips_parse(pdev);

	soctherm_init_hw_throt_cdev(pdev);

	soctherm_init(pdev);

	क्रम (i = 0; i < soc->num_ttgs; ++i) अणु
		काष्ठा tegra_thermctl_zone *zone =
			devm_kzalloc(&pdev->dev, माप(*zone), GFP_KERNEL);
		अगर (!zone) अणु
			err = -ENOMEM;
			जाओ disable_घड़ीs;
		पूर्ण

		zone->reg = tegra->regs + soc->ttgs[i]->sensor_temp_offset;
		zone->dev = &pdev->dev;
		zone->sg = soc->ttgs[i];
		zone->ts = tegra;

		z = devm_thermal_zone_of_sensor_रेजिस्टर(&pdev->dev,
							 soc->ttgs[i]->id, zone,
							 &tegra_of_thermal_ops);
		अगर (IS_ERR(z)) अणु
			err = PTR_ERR(z);
			dev_err(&pdev->dev, "failed to register sensor: %d\n",
				err);
			जाओ disable_घड़ीs;
		पूर्ण

		zone->tz = z;
		tegra->thermctl_tzs[soc->ttgs[i]->id] = z;

		/* Configure hw trip poपूर्णांकs */
		err = tegra_soctherm_set_hwtrips(&pdev->dev, soc->ttgs[i], z);
		अगर (err)
			जाओ disable_घड़ीs;
	पूर्ण

	err = soctherm_पूर्णांकerrupts_init(pdev, tegra);

	soctherm_debug_init(pdev);

	वापस 0;

disable_घड़ीs:
	soctherm_clk_enable(pdev, false);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_soctherm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_soctherm *tegra = platक्रमm_get_drvdata(pdev);

	debugfs_हटाओ_recursive(tegra->debugfs_dir);

	soctherm_clk_enable(pdev, false);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused soctherm_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	soctherm_clk_enable(pdev, false);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused soctherm_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा tegra_soctherm *tegra = platक्रमm_get_drvdata(pdev);
	काष्ठा tegra_soctherm_soc *soc = tegra->soc;
	पूर्णांक err, i;

	err = soctherm_clk_enable(pdev, true);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"Resume failed: enable clocks failed\n");
		वापस err;
	पूर्ण

	soctherm_init(pdev);

	क्रम (i = 0; i < soc->num_ttgs; ++i) अणु
		काष्ठा thermal_zone_device *tz;

		tz = tegra->thermctl_tzs[soc->ttgs[i]->id];
		err = tegra_soctherm_set_hwtrips(dev, soc->ttgs[i], tz);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"Resume failed: set hwtrips failed\n");
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(tegra_soctherm_pm, soctherm_suspend, soctherm_resume);

अटल काष्ठा platक्रमm_driver tegra_soctherm_driver = अणु
	.probe = tegra_soctherm_probe,
	.हटाओ = tegra_soctherm_हटाओ,
	.driver = अणु
		.name = "tegra_soctherm",
		.pm = &tegra_soctherm_pm,
		.of_match_table = tegra_soctherm_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tegra_soctherm_driver);

MODULE_AUTHOR("Mikko Perttunen <mperttunen@nvidia.com>");
MODULE_DESCRIPTION("NVIDIA Tegra SOCTHERM thermal management driver");
MODULE_LICENSE("GPL v2");
