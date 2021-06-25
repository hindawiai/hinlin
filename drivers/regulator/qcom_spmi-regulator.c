<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2015, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/devm-helpers.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regmap.h>
#समावेश <linux/list.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/पन.स>

/* Pin control enable input pins. */
#घोषणा SPMI_REGULATOR_PIN_CTRL_ENABLE_NONE		0x00
#घोषणा SPMI_REGULATOR_PIN_CTRL_ENABLE_EN0		0x01
#घोषणा SPMI_REGULATOR_PIN_CTRL_ENABLE_EN1		0x02
#घोषणा SPMI_REGULATOR_PIN_CTRL_ENABLE_EN2		0x04
#घोषणा SPMI_REGULATOR_PIN_CTRL_ENABLE_EN3		0x08
#घोषणा SPMI_REGULATOR_PIN_CTRL_ENABLE_HW_DEFAULT	0x10

/* Pin control high घातer mode input pins. */
#घोषणा SPMI_REGULATOR_PIN_CTRL_HPM_NONE		0x00
#घोषणा SPMI_REGULATOR_PIN_CTRL_HPM_EN0			0x01
#घोषणा SPMI_REGULATOR_PIN_CTRL_HPM_EN1			0x02
#घोषणा SPMI_REGULATOR_PIN_CTRL_HPM_EN2			0x04
#घोषणा SPMI_REGULATOR_PIN_CTRL_HPM_EN3			0x08
#घोषणा SPMI_REGULATOR_PIN_CTRL_HPM_SLEEP_B		0x10
#घोषणा SPMI_REGULATOR_PIN_CTRL_HPM_HW_DEFAULT		0x20

/*
 * Used with enable parameters to specअगरy that hardware शेष रेजिस्टर values
 * should be left unaltered.
 */
#घोषणा SPMI_REGULATOR_USE_HW_DEFAULT			2

/* Soft start strength of a voltage चयन type regulator */
क्रमागत spmi_vs_soft_start_str अणु
	SPMI_VS_SOFT_START_STR_0P05_UA = 0,
	SPMI_VS_SOFT_START_STR_0P25_UA,
	SPMI_VS_SOFT_START_STR_0P55_UA,
	SPMI_VS_SOFT_START_STR_0P75_UA,
	SPMI_VS_SOFT_START_STR_HW_DEFAULT,
पूर्ण;

/**
 * काष्ठा spmi_regulator_init_data - spmi-regulator initialization data
 * @pin_ctrl_enable:        Bit mask specअगरying which hardware pins should be
 *				used to enable the regulator, अगर any
 *			    Value should be an ORing of
 *				SPMI_REGULATOR_PIN_CTRL_ENABLE_* स्थिरants.  If
 *				the bit specअगरied by
 *				SPMI_REGULATOR_PIN_CTRL_ENABLE_HW_DEFAULT is
 *				set, then pin control enable hardware रेजिस्टरs
 *				will not be modअगरied.
 * @pin_ctrl_hpm:           Bit mask specअगरying which hardware pins should be
 *				used to क्रमce the regulator पूर्णांकo high घातer
 *				mode, अगर any
 *			    Value should be an ORing of
 *				SPMI_REGULATOR_PIN_CTRL_HPM_* स्थिरants.  If
 *				the bit specअगरied by
 *				SPMI_REGULATOR_PIN_CTRL_HPM_HW_DEFAULT is
 *				set, then pin control mode hardware रेजिस्टरs
 *				will not be modअगरied.
 * @vs_soft_start_strength: This parameter sets the soft start strength क्रम
 *				voltage चयन type regulators.  Its value
 *				should be one of SPMI_VS_SOFT_START_STR_*.  If
 *				its value is SPMI_VS_SOFT_START_STR_HW_DEFAULT,
 *				then the soft start strength will be left at its
 *				शेष hardware value.
 */
काष्ठा spmi_regulator_init_data अणु
	अचिन्हित				pin_ctrl_enable;
	अचिन्हित				pin_ctrl_hpm;
	क्रमागत spmi_vs_soft_start_str		vs_soft_start_strength;
पूर्ण;

/* These types correspond to unique रेजिस्टर layouts. */
क्रमागत spmi_regulator_logical_type अणु
	SPMI_REGULATOR_LOGICAL_TYPE_SMPS,
	SPMI_REGULATOR_LOGICAL_TYPE_LDO,
	SPMI_REGULATOR_LOGICAL_TYPE_VS,
	SPMI_REGULATOR_LOGICAL_TYPE_BOOST,
	SPMI_REGULATOR_LOGICAL_TYPE_FTSMPS,
	SPMI_REGULATOR_LOGICAL_TYPE_BOOST_BYP,
	SPMI_REGULATOR_LOGICAL_TYPE_LN_LDO,
	SPMI_REGULATOR_LOGICAL_TYPE_ULT_LO_SMPS,
	SPMI_REGULATOR_LOGICAL_TYPE_ULT_HO_SMPS,
	SPMI_REGULATOR_LOGICAL_TYPE_ULT_LDO,
	SPMI_REGULATOR_LOGICAL_TYPE_FTSMPS426,
	SPMI_REGULATOR_LOGICAL_TYPE_HFS430,
पूर्ण;

क्रमागत spmi_regulator_type अणु
	SPMI_REGULATOR_TYPE_BUCK		= 0x03,
	SPMI_REGULATOR_TYPE_LDO			= 0x04,
	SPMI_REGULATOR_TYPE_VS			= 0x05,
	SPMI_REGULATOR_TYPE_BOOST		= 0x1b,
	SPMI_REGULATOR_TYPE_FTS			= 0x1c,
	SPMI_REGULATOR_TYPE_BOOST_BYP		= 0x1f,
	SPMI_REGULATOR_TYPE_ULT_LDO		= 0x21,
	SPMI_REGULATOR_TYPE_ULT_BUCK		= 0x22,
पूर्ण;

क्रमागत spmi_regulator_subtype अणु
	SPMI_REGULATOR_SUBTYPE_GP_CTL		= 0x08,
	SPMI_REGULATOR_SUBTYPE_RF_CTL		= 0x09,
	SPMI_REGULATOR_SUBTYPE_N50		= 0x01,
	SPMI_REGULATOR_SUBTYPE_N150		= 0x02,
	SPMI_REGULATOR_SUBTYPE_N300		= 0x03,
	SPMI_REGULATOR_SUBTYPE_N600		= 0x04,
	SPMI_REGULATOR_SUBTYPE_N1200		= 0x05,
	SPMI_REGULATOR_SUBTYPE_N600_ST		= 0x06,
	SPMI_REGULATOR_SUBTYPE_N1200_ST		= 0x07,
	SPMI_REGULATOR_SUBTYPE_N900_ST		= 0x14,
	SPMI_REGULATOR_SUBTYPE_N300_ST		= 0x15,
	SPMI_REGULATOR_SUBTYPE_P50		= 0x08,
	SPMI_REGULATOR_SUBTYPE_P150		= 0x09,
	SPMI_REGULATOR_SUBTYPE_P300		= 0x0a,
	SPMI_REGULATOR_SUBTYPE_P600		= 0x0b,
	SPMI_REGULATOR_SUBTYPE_P1200		= 0x0c,
	SPMI_REGULATOR_SUBTYPE_LN		= 0x10,
	SPMI_REGULATOR_SUBTYPE_LV_P50		= 0x28,
	SPMI_REGULATOR_SUBTYPE_LV_P150		= 0x29,
	SPMI_REGULATOR_SUBTYPE_LV_P300		= 0x2a,
	SPMI_REGULATOR_SUBTYPE_LV_P600		= 0x2b,
	SPMI_REGULATOR_SUBTYPE_LV_P1200		= 0x2c,
	SPMI_REGULATOR_SUBTYPE_LV_P450		= 0x2d,
	SPMI_REGULATOR_SUBTYPE_HT_N300_ST	= 0x30,
	SPMI_REGULATOR_SUBTYPE_HT_N600_ST	= 0x31,
	SPMI_REGULATOR_SUBTYPE_HT_N1200_ST	= 0x32,
	SPMI_REGULATOR_SUBTYPE_HT_LVP150	= 0x3b,
	SPMI_REGULATOR_SUBTYPE_HT_LVP300	= 0x3c,
	SPMI_REGULATOR_SUBTYPE_L660_N300_ST	= 0x42,
	SPMI_REGULATOR_SUBTYPE_L660_N600_ST	= 0x43,
	SPMI_REGULATOR_SUBTYPE_L660_P50		= 0x46,
	SPMI_REGULATOR_SUBTYPE_L660_P150	= 0x47,
	SPMI_REGULATOR_SUBTYPE_L660_P600	= 0x49,
	SPMI_REGULATOR_SUBTYPE_L660_LVP150	= 0x4d,
	SPMI_REGULATOR_SUBTYPE_L660_LVP600	= 0x4f,
	SPMI_REGULATOR_SUBTYPE_LV100		= 0x01,
	SPMI_REGULATOR_SUBTYPE_LV300		= 0x02,
	SPMI_REGULATOR_SUBTYPE_MV300		= 0x08,
	SPMI_REGULATOR_SUBTYPE_MV500		= 0x09,
	SPMI_REGULATOR_SUBTYPE_HDMI		= 0x10,
	SPMI_REGULATOR_SUBTYPE_OTG		= 0x11,
	SPMI_REGULATOR_SUBTYPE_5V_BOOST		= 0x01,
	SPMI_REGULATOR_SUBTYPE_FTS_CTL		= 0x08,
	SPMI_REGULATOR_SUBTYPE_FTS2p5_CTL	= 0x09,
	SPMI_REGULATOR_SUBTYPE_FTS426_CTL	= 0x0a,
	SPMI_REGULATOR_SUBTYPE_BB_2A		= 0x01,
	SPMI_REGULATOR_SUBTYPE_ULT_HF_CTL1	= 0x0d,
	SPMI_REGULATOR_SUBTYPE_ULT_HF_CTL2	= 0x0e,
	SPMI_REGULATOR_SUBTYPE_ULT_HF_CTL3	= 0x0f,
	SPMI_REGULATOR_SUBTYPE_ULT_HF_CTL4	= 0x10,
	SPMI_REGULATOR_SUBTYPE_HFS430		= 0x0a,
पूर्ण;

क्रमागत spmi_common_regulator_रेजिस्टरs अणु
	SPMI_COMMON_REG_DIG_MAJOR_REV		= 0x01,
	SPMI_COMMON_REG_TYPE			= 0x04,
	SPMI_COMMON_REG_SUBTYPE			= 0x05,
	SPMI_COMMON_REG_VOLTAGE_RANGE		= 0x40,
	SPMI_COMMON_REG_VOLTAGE_SET		= 0x41,
	SPMI_COMMON_REG_MODE			= 0x45,
	SPMI_COMMON_REG_ENABLE			= 0x46,
	SPMI_COMMON_REG_PULL_DOWN		= 0x48,
	SPMI_COMMON_REG_SOFT_START		= 0x4c,
	SPMI_COMMON_REG_STEP_CTRL		= 0x61,
पूर्ण;

/*
 * Second common रेजिस्टर layout used by newer devices starting with ftsmps426
 * Note that some of the रेजिस्टरs from the first common layout reमुख्य
 * unchanged and their definition is not duplicated.
 */
क्रमागत spmi_ftsmps426_regulator_रेजिस्टरs अणु
	SPMI_FTSMPS426_REG_VOLTAGE_LSB		= 0x40,
	SPMI_FTSMPS426_REG_VOLTAGE_MSB		= 0x41,
	SPMI_FTSMPS426_REG_VOLTAGE_ULS_LSB	= 0x68,
	SPMI_FTSMPS426_REG_VOLTAGE_ULS_MSB	= 0x69,
पूर्ण;

क्रमागत spmi_vs_रेजिस्टरs अणु
	SPMI_VS_REG_OCP				= 0x4a,
	SPMI_VS_REG_SOFT_START			= 0x4c,
पूर्ण;

क्रमागत spmi_boost_रेजिस्टरs अणु
	SPMI_BOOST_REG_CURRENT_LIMIT		= 0x4a,
पूर्ण;

क्रमागत spmi_boost_byp_रेजिस्टरs अणु
	SPMI_BOOST_BYP_REG_CURRENT_LIMIT	= 0x4b,
पूर्ण;

क्रमागत spmi_saw3_रेजिस्टरs अणु
	SAW3_SECURE				= 0x00,
	SAW3_ID					= 0x04,
	SAW3_SPM_STS				= 0x0C,
	SAW3_AVS_STS				= 0x10,
	SAW3_PMIC_STS				= 0x14,
	SAW3_RST				= 0x18,
	SAW3_VCTL				= 0x1C,
	SAW3_AVS_CTL				= 0x20,
	SAW3_AVS_LIMIT				= 0x24,
	SAW3_AVS_DLY				= 0x28,
	SAW3_AVS_HYSTERESIS			= 0x2C,
	SAW3_SPM_STS2				= 0x38,
	SAW3_SPM_PMIC_DATA_3			= 0x4C,
	SAW3_VERSION				= 0xFD0,
पूर्ण;

/* Used क्रम indexing पूर्णांकo ctrl_reg.  These are offets from 0x40 */
क्रमागत spmi_common_control_रेजिस्टर_index अणु
	SPMI_COMMON_IDX_VOLTAGE_RANGE		= 0,
	SPMI_COMMON_IDX_VOLTAGE_SET		= 1,
	SPMI_COMMON_IDX_MODE			= 5,
	SPMI_COMMON_IDX_ENABLE			= 6,
पूर्ण;

/* Common regulator control रेजिस्टर layout */
#घोषणा SPMI_COMMON_ENABLE_MASK			0x80
#घोषणा SPMI_COMMON_ENABLE			0x80
#घोषणा SPMI_COMMON_DISABLE			0x00
#घोषणा SPMI_COMMON_ENABLE_FOLLOW_HW_EN3_MASK	0x08
#घोषणा SPMI_COMMON_ENABLE_FOLLOW_HW_EN2_MASK	0x04
#घोषणा SPMI_COMMON_ENABLE_FOLLOW_HW_EN1_MASK	0x02
#घोषणा SPMI_COMMON_ENABLE_FOLLOW_HW_EN0_MASK	0x01
#घोषणा SPMI_COMMON_ENABLE_FOLLOW_ALL_MASK	0x0f

/* Common regulator mode रेजिस्टर layout */
#घोषणा SPMI_COMMON_MODE_HPM_MASK		0x80
#घोषणा SPMI_COMMON_MODE_AUTO_MASK		0x40
#घोषणा SPMI_COMMON_MODE_BYPASS_MASK		0x20
#घोषणा SPMI_COMMON_MODE_FOLLOW_AWAKE_MASK	0x10
#घोषणा SPMI_COMMON_MODE_FOLLOW_HW_EN3_MASK	0x08
#घोषणा SPMI_COMMON_MODE_FOLLOW_HW_EN2_MASK	0x04
#घोषणा SPMI_COMMON_MODE_FOLLOW_HW_EN1_MASK	0x02
#घोषणा SPMI_COMMON_MODE_FOLLOW_HW_EN0_MASK	0x01
#घोषणा SPMI_COMMON_MODE_FOLLOW_ALL_MASK	0x1f

#घोषणा SPMI_FTSMPS426_MODE_BYPASS_MASK		3
#घोषणा SPMI_FTSMPS426_MODE_RETENTION_MASK	4
#घोषणा SPMI_FTSMPS426_MODE_LPM_MASK		5
#घोषणा SPMI_FTSMPS426_MODE_AUTO_MASK		6
#घोषणा SPMI_FTSMPS426_MODE_HPM_MASK		7

#घोषणा SPMI_FTSMPS426_MODE_MASK		0x07

/* Common regulator pull करोwn control रेजिस्टर layout */
#घोषणा SPMI_COMMON_PULL_DOWN_ENABLE_MASK	0x80

/* LDO regulator current limit control रेजिस्टर layout */
#घोषणा SPMI_LDO_CURRENT_LIMIT_ENABLE_MASK	0x80

/* LDO regulator soft start control रेजिस्टर layout */
#घोषणा SPMI_LDO_SOFT_START_ENABLE_MASK		0x80

/* VS regulator over current protection control रेजिस्टर layout */
#घोषणा SPMI_VS_OCP_OVERRIDE			0x01
#घोषणा SPMI_VS_OCP_NO_OVERRIDE			0x00

/* VS regulator soft start control रेजिस्टर layout */
#घोषणा SPMI_VS_SOFT_START_ENABLE_MASK		0x80
#घोषणा SPMI_VS_SOFT_START_SEL_MASK		0x03

/* Boost regulator current limit control रेजिस्टर layout */
#घोषणा SPMI_BOOST_CURRENT_LIMIT_ENABLE_MASK	0x80
#घोषणा SPMI_BOOST_CURRENT_LIMIT_MASK		0x07

#घोषणा SPMI_VS_OCP_DEFAULT_MAX_RETRIES		10
#घोषणा SPMI_VS_OCP_DEFAULT_RETRY_DELAY_MS	30
#घोषणा SPMI_VS_OCP_FALL_DELAY_US		90
#घोषणा SPMI_VS_OCP_FAULT_DELAY_US		20000

#घोषणा SPMI_FTSMPS_STEP_CTRL_STEP_MASK		0x18
#घोषणा SPMI_FTSMPS_STEP_CTRL_STEP_SHIFT	3
#घोषणा SPMI_FTSMPS_STEP_CTRL_DELAY_MASK	0x07
#घोषणा SPMI_FTSMPS_STEP_CTRL_DELAY_SHIFT	0

/* Clock rate in kHz of the FTSMPS regulator reference घड़ी. */
#घोषणा SPMI_FTSMPS_CLOCK_RATE		19200

/* Minimum voltage stepper delay क्रम each step. */
#घोषणा SPMI_FTSMPS_STEP_DELAY		8
#घोषणा SPMI_DEFAULT_STEP_DELAY		20

/*
 * The ratio SPMI_FTSMPS_STEP_MARGIN_NUM/SPMI_FTSMPS_STEP_MARGIN_DEN is used to
 * adjust the step rate in order to account क्रम oscillator variance.
 */
#घोषणा SPMI_FTSMPS_STEP_MARGIN_NUM	4
#घोषणा SPMI_FTSMPS_STEP_MARGIN_DEN	5

#घोषणा SPMI_FTSMPS426_STEP_CTRL_DELAY_MASK	0x03
#घोषणा SPMI_FTSMPS426_STEP_CTRL_DELAY_SHIFT	0

/* Clock rate in kHz of the FTSMPS426 regulator reference घड़ी. */
#घोषणा SPMI_FTSMPS426_CLOCK_RATE		4800

#घोषणा SPMI_HFS430_CLOCK_RATE			1600

/* Minimum voltage stepper delay क्रम each step. */
#घोषणा SPMI_FTSMPS426_STEP_DELAY		2

/*
 * The ratio SPMI_FTSMPS426_STEP_MARGIN_NUM/SPMI_FTSMPS426_STEP_MARGIN_DEN is
 * used to adjust the step rate in order to account क्रम oscillator variance.
 */
#घोषणा SPMI_FTSMPS426_STEP_MARGIN_NUM	10
#घोषणा SPMI_FTSMPS426_STEP_MARGIN_DEN	11


/* VSET value to decide the range of ULT SMPS */
#घोषणा ULT_SMPS_RANGE_SPLIT 0x60

/**
 * काष्ठा spmi_voltage_range - regulator set poपूर्णांक voltage mapping description
 * @min_uV:		Minimum programmable output voltage resulting from
 *			set poपूर्णांक रेजिस्टर value 0x00
 * @max_uV:		Maximum programmable output voltage
 * @step_uV:		Output voltage increase resulting from the set poपूर्णांक
 *			रेजिस्टर value increasing by 1
 * @set_poपूर्णांक_min_uV:	Minimum allowed voltage
 * @set_poपूर्णांक_max_uV:	Maximum allowed voltage.  This may be tweaked in order
 *			to pick which range should be used in the हाल of
 *			overlapping set poपूर्णांकs.
 * @n_voltages:		Number of preferred voltage set poपूर्णांकs present in this
 *			range
 * @range_sel:		Voltage range रेजिस्टर value corresponding to this range
 *
 * The following relationships must be true क्रम the values used in this काष्ठा:
 * (max_uV - min_uV) % step_uV == 0
 * (set_poपूर्णांक_min_uV - min_uV) % step_uV == 0*
 * (set_poपूर्णांक_max_uV - min_uV) % step_uV == 0*
 * n_voltages = (set_poपूर्णांक_max_uV - set_poपूर्णांक_min_uV) / step_uV + 1
 *
 * *Note, set_poपूर्णांक_min_uV == set_poपूर्णांक_max_uV == 0 is allowed in order to
 * specअगरy that the voltage range has meaning, but is not preferred.
 */
काष्ठा spmi_voltage_range अणु
	पूर्णांक					min_uV;
	पूर्णांक					max_uV;
	पूर्णांक					step_uV;
	पूर्णांक					set_poपूर्णांक_min_uV;
	पूर्णांक					set_poपूर्णांक_max_uV;
	अचिन्हित				n_voltages;
	u8					range_sel;
पूर्ण;

/*
 * The ranges specअगरied in the spmi_voltage_set_poपूर्णांकs काष्ठा must be listed
 * so that range[i].set_poपूर्णांक_max_uV < range[i+1].set_poपूर्णांक_min_uV.
 */
काष्ठा spmi_voltage_set_poपूर्णांकs अणु
	काष्ठा spmi_voltage_range		*range;
	पूर्णांक					count;
	अचिन्हित				n_voltages;
पूर्ण;

काष्ठा spmi_regulator अणु
	काष्ठा regulator_desc			desc;
	काष्ठा device				*dev;
	काष्ठा delayed_work			ocp_work;
	काष्ठा regmap				*regmap;
	काष्ठा spmi_voltage_set_poपूर्णांकs		*set_poपूर्णांकs;
	क्रमागत spmi_regulator_logical_type	logical_type;
	पूर्णांक					ocp_irq;
	पूर्णांक					ocp_count;
	पूर्णांक					ocp_max_retries;
	पूर्णांक					ocp_retry_delay_ms;
	पूर्णांक					hpm_min_load;
	पूर्णांक					slew_rate;
	kसमय_प्रकार					vs_enable_समय;
	u16					base;
	काष्ठा list_head			node;
पूर्ण;

काष्ठा spmi_regulator_mapping अणु
	क्रमागत spmi_regulator_type		type;
	क्रमागत spmi_regulator_subtype		subtype;
	क्रमागत spmi_regulator_logical_type	logical_type;
	u32					revision_min;
	u32					revision_max;
	स्थिर काष्ठा regulator_ops		*ops;
	काष्ठा spmi_voltage_set_poपूर्णांकs		*set_poपूर्णांकs;
	पूर्णांक					hpm_min_load;
पूर्ण;

काष्ठा spmi_regulator_data अणु
	स्थिर अक्षर			*name;
	u16				base;
	स्थिर अक्षर			*supply;
	स्थिर अक्षर			*ocp;
	u16				क्रमce_type;
पूर्ण;

#घोषणा SPMI_VREG(_type, _subtype, _dig_major_min, _dig_major_max, \
		      _logical_type, _ops_val, _set_poपूर्णांकs_val, _hpm_min_load) \
	अणु \
		.type		= SPMI_REGULATOR_TYPE_##_type, \
		.subtype	= SPMI_REGULATOR_SUBTYPE_##_subtype, \
		.revision_min	= _dig_major_min, \
		.revision_max	= _dig_major_max, \
		.logical_type	= SPMI_REGULATOR_LOGICAL_TYPE_##_logical_type, \
		.ops		= &spmi_##_ops_val##_ops, \
		.set_poपूर्णांकs	= &_set_poपूर्णांकs_val##_set_poपूर्णांकs, \
		.hpm_min_load	= _hpm_min_load, \
	पूर्ण

#घोषणा SPMI_VREG_VS(_subtype, _dig_major_min, _dig_major_max) \
	अणु \
		.type		= SPMI_REGULATOR_TYPE_VS, \
		.subtype	= SPMI_REGULATOR_SUBTYPE_##_subtype, \
		.revision_min	= _dig_major_min, \
		.revision_max	= _dig_major_max, \
		.logical_type	= SPMI_REGULATOR_LOGICAL_TYPE_VS, \
		.ops		= &spmi_vs_ops, \
	पूर्ण

#घोषणा SPMI_VOLTAGE_RANGE(_range_sel, _min_uV, _set_poपूर्णांक_min_uV, \
			_set_poपूर्णांक_max_uV, _max_uV, _step_uV) \
	अणु \
		.min_uV			= _min_uV, \
		.max_uV			= _max_uV, \
		.set_poपूर्णांक_min_uV	= _set_poपूर्णांक_min_uV, \
		.set_poपूर्णांक_max_uV	= _set_poपूर्णांक_max_uV, \
		.step_uV		= _step_uV, \
		.range_sel		= _range_sel, \
	पूर्ण

#घोषणा DEFINE_SPMI_SET_POINTS(name) \
काष्ठा spmi_voltage_set_poपूर्णांकs name##_set_poपूर्णांकs = अणु \
	.range	= name##_ranges, \
	.count	= ARRAY_SIZE(name##_ranges), \
पूर्ण

/*
 * These tables contain the physically available PMIC regulator voltage setpoपूर्णांक
 * ranges.  Where two ranges overlap in hardware, one of the ranges is trimmed
 * to ensure that the setpoपूर्णांकs available to software are monotonically
 * increasing and unique.  The set_voltage callback functions expect these
 * properties to hold.
 */
अटल काष्ठा spmi_voltage_range plकरो_ranges[] = अणु
	SPMI_VOLTAGE_RANGE(2,  750000,  750000, 1537500, 1537500, 12500),
	SPMI_VOLTAGE_RANGE(3, 1500000, 1550000, 3075000, 3075000, 25000),
	SPMI_VOLTAGE_RANGE(4, 1750000, 3100000, 4900000, 4900000, 50000),
पूर्ण;

अटल काष्ठा spmi_voltage_range nlकरो1_ranges[] = अणु
	SPMI_VOLTAGE_RANGE(2,  750000,  750000, 1537500, 1537500, 12500),
पूर्ण;

अटल काष्ठा spmi_voltage_range nlकरो2_ranges[] = अणु
	SPMI_VOLTAGE_RANGE(0,  375000,       0,       0, 1537500, 12500),
	SPMI_VOLTAGE_RANGE(1,  375000,  375000,  768750,  768750,  6250),
	SPMI_VOLTAGE_RANGE(2,  750000,  775000, 1537500, 1537500, 12500),
पूर्ण;

अटल काष्ठा spmi_voltage_range nlकरो3_ranges[] = अणु
	SPMI_VOLTAGE_RANGE(0,  375000,  375000, 1537500, 1537500, 12500),
	SPMI_VOLTAGE_RANGE(1,  375000,       0,       0, 1537500, 12500),
	SPMI_VOLTAGE_RANGE(2,  750000,       0,       0, 1537500, 12500),
पूर्ण;

अटल काष्ठा spmi_voltage_range ln_lकरो_ranges[] = अणु
	SPMI_VOLTAGE_RANGE(1,  690000,  690000, 1110000, 1110000, 60000),
	SPMI_VOLTAGE_RANGE(0, 1380000, 1380000, 2220000, 2220000, 120000),
पूर्ण;

अटल काष्ठा spmi_voltage_range smps_ranges[] = अणु
	SPMI_VOLTAGE_RANGE(0,  375000,  375000, 1562500, 1562500, 12500),
	SPMI_VOLTAGE_RANGE(1, 1550000, 1575000, 3125000, 3125000, 25000),
पूर्ण;

अटल काष्ठा spmi_voltage_range ftsmps_ranges[] = अणु
	SPMI_VOLTAGE_RANGE(0,       0,  350000, 1275000, 1275000,  5000),
	SPMI_VOLTAGE_RANGE(1,       0, 1280000, 2040000, 2040000, 10000),
पूर्ण;

अटल काष्ठा spmi_voltage_range ftsmps2p5_ranges[] = अणु
	SPMI_VOLTAGE_RANGE(0,   80000,  350000, 1355000, 1355000,  5000),
	SPMI_VOLTAGE_RANGE(1,  160000, 1360000, 2200000, 2200000, 10000),
पूर्ण;

अटल काष्ठा spmi_voltage_range ftsmps426_ranges[] = अणु
	SPMI_VOLTAGE_RANGE(0,       0,  320000, 1352000, 1352000,  4000),
पूर्ण;

अटल काष्ठा spmi_voltage_range boost_ranges[] = अणु
	SPMI_VOLTAGE_RANGE(0, 4000000, 4000000, 5550000, 5550000, 50000),
पूर्ण;

अटल काष्ठा spmi_voltage_range boost_byp_ranges[] = अणु
	SPMI_VOLTAGE_RANGE(0, 2500000, 2500000, 5200000, 5650000, 50000),
पूर्ण;

अटल काष्ठा spmi_voltage_range ult_lo_smps_ranges[] = अणु
	SPMI_VOLTAGE_RANGE(0,  375000,  375000, 1562500, 1562500, 12500),
	SPMI_VOLTAGE_RANGE(1,  750000,       0,       0, 1525000, 25000),
पूर्ण;

अटल काष्ठा spmi_voltage_range ult_ho_smps_ranges[] = अणु
	SPMI_VOLTAGE_RANGE(0, 1550000, 1550000, 2325000, 2325000, 25000),
पूर्ण;

अटल काष्ठा spmi_voltage_range ult_nlकरो_ranges[] = अणु
	SPMI_VOLTAGE_RANGE(0,  375000,  375000, 1537500, 1537500, 12500),
पूर्ण;

अटल काष्ठा spmi_voltage_range ult_plकरो_ranges[] = अणु
	SPMI_VOLTAGE_RANGE(0, 1750000, 1750000, 3337500, 3337500, 12500),
पूर्ण;

अटल काष्ठा spmi_voltage_range plकरो660_ranges[] = अणु
	SPMI_VOLTAGE_RANGE(0, 1504000, 1504000, 3544000, 3544000, 8000),
पूर्ण;

अटल काष्ठा spmi_voltage_range nlकरो660_ranges[] = अणु
	SPMI_VOLTAGE_RANGE(0,  320000,  320000, 1304000, 1304000, 8000),
पूर्ण;

अटल काष्ठा spmi_voltage_range ht_lvplकरो_ranges[] = अणु
	SPMI_VOLTAGE_RANGE(0, 1504000, 1504000, 2000000, 2000000, 8000),
पूर्ण;

अटल काष्ठा spmi_voltage_range ht_nlकरो_ranges[] = अणु
	SPMI_VOLTAGE_RANGE(0,  312000,  312000, 1304000, 1304000, 8000),
पूर्ण;

अटल काष्ठा spmi_voltage_range hfs430_ranges[] = अणु
	SPMI_VOLTAGE_RANGE(0, 320000, 320000, 2040000, 2040000, 8000),
पूर्ण;

अटल DEFINE_SPMI_SET_POINTS(plकरो);
अटल DEFINE_SPMI_SET_POINTS(nlकरो1);
अटल DEFINE_SPMI_SET_POINTS(nlकरो2);
अटल DEFINE_SPMI_SET_POINTS(nlकरो3);
अटल DEFINE_SPMI_SET_POINTS(ln_lकरो);
अटल DEFINE_SPMI_SET_POINTS(smps);
अटल DEFINE_SPMI_SET_POINTS(ftsmps);
अटल DEFINE_SPMI_SET_POINTS(ftsmps2p5);
अटल DEFINE_SPMI_SET_POINTS(ftsmps426);
अटल DEFINE_SPMI_SET_POINTS(boost);
अटल DEFINE_SPMI_SET_POINTS(boost_byp);
अटल DEFINE_SPMI_SET_POINTS(ult_lo_smps);
अटल DEFINE_SPMI_SET_POINTS(ult_ho_smps);
अटल DEFINE_SPMI_SET_POINTS(ult_nlकरो);
अटल DEFINE_SPMI_SET_POINTS(ult_plकरो);
अटल DEFINE_SPMI_SET_POINTS(plकरो660);
अटल DEFINE_SPMI_SET_POINTS(nlकरो660);
अटल DEFINE_SPMI_SET_POINTS(ht_lvplकरो);
अटल DEFINE_SPMI_SET_POINTS(ht_nlकरो);
अटल DEFINE_SPMI_SET_POINTS(hfs430);

अटल अंतरभूत पूर्णांक spmi_vreg_पढ़ो(काष्ठा spmi_regulator *vreg, u16 addr, u8 *buf,
				 पूर्णांक len)
अणु
	वापस regmap_bulk_पढ़ो(vreg->regmap, vreg->base + addr, buf, len);
पूर्ण

अटल अंतरभूत पूर्णांक spmi_vreg_ग_लिखो(काष्ठा spmi_regulator *vreg, u16 addr,
				u8 *buf, पूर्णांक len)
अणु
	वापस regmap_bulk_ग_लिखो(vreg->regmap, vreg->base + addr, buf, len);
पूर्ण

अटल पूर्णांक spmi_vreg_update_bits(काष्ठा spmi_regulator *vreg, u16 addr, u8 val,
		u8 mask)
अणु
	वापस regmap_update_bits(vreg->regmap, vreg->base + addr, mask, val);
पूर्ण

अटल पूर्णांक spmi_regulator_vs_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);

	अगर (vreg->ocp_irq) अणु
		vreg->ocp_count = 0;
		vreg->vs_enable_समय = kसमय_get();
	पूर्ण

	वापस regulator_enable_regmap(rdev);
पूर्ण

अटल पूर्णांक spmi_regulator_vs_ocp(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);
	u8 reg = SPMI_VS_OCP_OVERRIDE;

	वापस spmi_vreg_ग_लिखो(vreg, SPMI_VS_REG_OCP, &reg, 1);
पूर्ण

अटल पूर्णांक spmi_regulator_select_voltage(काष्ठा spmi_regulator *vreg,
					 पूर्णांक min_uV, पूर्णांक max_uV)
अणु
	स्थिर काष्ठा spmi_voltage_range *range;
	पूर्णांक uV = min_uV;
	पूर्णांक lim_min_uV, lim_max_uV, i, range_id, range_max_uV;
	पूर्णांक selector, voltage_sel;

	/* Check अगर request voltage is outside of physically settable range. */
	lim_min_uV = vreg->set_poपूर्णांकs->range[0].set_poपूर्णांक_min_uV;
	lim_max_uV =
	  vreg->set_poपूर्णांकs->range[vreg->set_poपूर्णांकs->count - 1].set_poपूर्णांक_max_uV;

	अगर (uV < lim_min_uV && max_uV >= lim_min_uV)
		uV = lim_min_uV;

	अगर (uV < lim_min_uV || uV > lim_max_uV) अणु
		dev_err(vreg->dev,
			"request v=[%d, %d] is outside possible v=[%d, %d]\n",
			 min_uV, max_uV, lim_min_uV, lim_max_uV);
		वापस -EINVAL;
	पूर्ण

	/* Find the range which uV is inside of. */
	क्रम (i = vreg->set_poपूर्णांकs->count - 1; i > 0; i--) अणु
		range_max_uV = vreg->set_poपूर्णांकs->range[i - 1].set_poपूर्णांक_max_uV;
		अगर (uV > range_max_uV && range_max_uV > 0)
			अवरोध;
	पूर्ण

	range_id = i;
	range = &vreg->set_poपूर्णांकs->range[range_id];

	/*
	 * Force uV to be an allowed set poपूर्णांक by applying a उच्चमानing function to
	 * the uV value.
	 */
	voltage_sel = DIV_ROUND_UP(uV - range->min_uV, range->step_uV);
	uV = voltage_sel * range->step_uV + range->min_uV;

	अगर (uV > max_uV) अणु
		dev_err(vreg->dev,
			"request v=[%d, %d] cannot be met by any set point; "
			"next set point: %d\n",
			min_uV, max_uV, uV);
		वापस -EINVAL;
	पूर्ण

	selector = 0;
	क्रम (i = 0; i < range_id; i++)
		selector += vreg->set_poपूर्णांकs->range[i].n_voltages;
	selector += (uV - range->set_poपूर्णांक_min_uV) / range->step_uV;

	वापस selector;
पूर्ण

अटल पूर्णांक spmi_sw_selector_to_hw(काष्ठा spmi_regulator *vreg,
				  अचिन्हित selector, u8 *range_sel,
				  u8 *voltage_sel)
अणु
	स्थिर काष्ठा spmi_voltage_range *range, *end;
	अचिन्हित offset;

	range = vreg->set_poपूर्णांकs->range;
	end = range + vreg->set_poपूर्णांकs->count;

	क्रम (; range < end; range++) अणु
		अगर (selector < range->n_voltages) अणु
			/*
			 * hardware selectors between set poपूर्णांक min and real
			 * min are invalid so we ignore them
			 */
			offset = range->set_poपूर्णांक_min_uV - range->min_uV;
			offset /= range->step_uV;
			*voltage_sel = selector + offset;
			*range_sel = range->range_sel;
			वापस 0;
		पूर्ण

		selector -= range->n_voltages;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक spmi_hw_selector_to_sw(काष्ठा spmi_regulator *vreg, u8 hw_sel,
				  स्थिर काष्ठा spmi_voltage_range *range)
अणु
	अचिन्हित sw_sel = 0;
	अचिन्हित offset, max_hw_sel;
	स्थिर काष्ठा spmi_voltage_range *r = vreg->set_poपूर्णांकs->range;
	स्थिर काष्ठा spmi_voltage_range *end = r + vreg->set_poपूर्णांकs->count;

	क्रम (; r < end; r++) अणु
		अगर (r == range && range->n_voltages) अणु
			/*
			 * hardware selectors between set poपूर्णांक min and real
			 * min and between set poपूर्णांक max and real max are
			 * invalid so we वापस an error अगर they're
			 * programmed पूर्णांकo the hardware
			 */
			offset = range->set_poपूर्णांक_min_uV - range->min_uV;
			offset /= range->step_uV;
			अगर (hw_sel < offset)
				वापस -EINVAL;

			max_hw_sel = range->set_poपूर्णांक_max_uV - range->min_uV;
			max_hw_sel /= range->step_uV;
			अगर (hw_sel > max_hw_sel)
				वापस -EINVAL;

			वापस sw_sel + hw_sel - offset;
		पूर्ण
		sw_sel += r->n_voltages;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा spmi_voltage_range *
spmi_regulator_find_range(काष्ठा spmi_regulator *vreg)
अणु
	u8 range_sel;
	स्थिर काष्ठा spmi_voltage_range *range, *end;

	range = vreg->set_poपूर्णांकs->range;
	end = range + vreg->set_poपूर्णांकs->count;

	spmi_vreg_पढ़ो(vreg, SPMI_COMMON_REG_VOLTAGE_RANGE, &range_sel, 1);

	क्रम (; range < end; range++)
		अगर (range->range_sel == range_sel)
			वापस range;

	वापस शून्य;
पूर्ण

अटल पूर्णांक spmi_regulator_select_voltage_same_range(काष्ठा spmi_regulator *vreg,
		पूर्णांक min_uV, पूर्णांक max_uV)
अणु
	स्थिर काष्ठा spmi_voltage_range *range;
	पूर्णांक uV = min_uV;
	पूर्णांक i, selector;

	range = spmi_regulator_find_range(vreg);
	अगर (!range)
		जाओ dअगरferent_range;

	अगर (uV < range->min_uV && max_uV >= range->min_uV)
		uV = range->min_uV;

	अगर (uV < range->min_uV || uV > range->max_uV) अणु
		/* Current range करोesn't support the requested voltage. */
		जाओ dअगरferent_range;
	पूर्ण

	/*
	 * Force uV to be an allowed set poपूर्णांक by applying a उच्चमानing function to
	 * the uV value.
	 */
	uV = DIV_ROUND_UP(uV - range->min_uV, range->step_uV);
	uV = uV * range->step_uV + range->min_uV;

	अगर (uV > max_uV) अणु
		/*
		 * No set poपूर्णांक in the current voltage range is within the
		 * requested min_uV to max_uV range.
		 */
		जाओ dअगरferent_range;
	पूर्ण

	selector = 0;
	क्रम (i = 0; i < vreg->set_poपूर्णांकs->count; i++) अणु
		अगर (uV >= vreg->set_poपूर्णांकs->range[i].set_poपूर्णांक_min_uV
		    && uV <= vreg->set_poपूर्णांकs->range[i].set_poपूर्णांक_max_uV) अणु
			selector +=
			    (uV - vreg->set_poपूर्णांकs->range[i].set_poपूर्णांक_min_uV)
				/ vreg->set_poपूर्णांकs->range[i].step_uV;
			अवरोध;
		पूर्ण

		selector += vreg->set_poपूर्णांकs->range[i].n_voltages;
	पूर्ण

	अगर (selector >= vreg->set_poपूर्णांकs->n_voltages)
		जाओ dअगरferent_range;

	वापस selector;

dअगरferent_range:
	वापस spmi_regulator_select_voltage(vreg, min_uV, max_uV);
पूर्ण

अटल पूर्णांक spmi_regulator_common_map_voltage(काष्ठा regulator_dev *rdev,
					     पूर्णांक min_uV, पूर्णांक max_uV)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);

	/*
	 * Favor staying in the current voltage range अगर possible.  This aव्योमs
	 * voltage spikes that occur when changing the voltage range.
	 */
	वापस spmi_regulator_select_voltage_same_range(vreg, min_uV, max_uV);
पूर्ण

अटल पूर्णांक
spmi_regulator_common_set_voltage(काष्ठा regulator_dev *rdev, अचिन्हित selector)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);
	पूर्णांक ret;
	u8 buf[2];
	u8 range_sel, voltage_sel;

	ret = spmi_sw_selector_to_hw(vreg, selector, &range_sel, &voltage_sel);
	अगर (ret)
		वापस ret;

	buf[0] = range_sel;
	buf[1] = voltage_sel;
	वापस spmi_vreg_ग_लिखो(vreg, SPMI_COMMON_REG_VOLTAGE_RANGE, buf, 2);
पूर्ण

अटल पूर्णांक spmi_regulator_common_list_voltage(काष्ठा regulator_dev *rdev,
					      अचिन्हित selector);

अटल पूर्णांक spmi_regulator_ftsmps426_set_voltage(काष्ठा regulator_dev *rdev,
					      अचिन्हित selector)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);
	u8 buf[2];
	पूर्णांक mV;

	mV = spmi_regulator_common_list_voltage(rdev, selector) / 1000;

	buf[0] = mV & 0xff;
	buf[1] = mV >> 8;
	वापस spmi_vreg_ग_लिखो(vreg, SPMI_FTSMPS426_REG_VOLTAGE_LSB, buf, 2);
पूर्ण

अटल पूर्णांक spmi_regulator_set_voltage_समय_sel(काष्ठा regulator_dev *rdev,
		अचिन्हित पूर्णांक old_selector, अचिन्हित पूर्णांक new_selector)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);
	पूर्णांक dअगरf_uV;

	dअगरf_uV = असल(spmi_regulator_common_list_voltage(rdev, new_selector) -
		      spmi_regulator_common_list_voltage(rdev, old_selector));

	वापस DIV_ROUND_UP(dअगरf_uV, vreg->slew_rate);
पूर्ण

अटल पूर्णांक spmi_regulator_common_get_voltage(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);
	स्थिर काष्ठा spmi_voltage_range *range;
	u8 voltage_sel;

	spmi_vreg_पढ़ो(vreg, SPMI_COMMON_REG_VOLTAGE_SET, &voltage_sel, 1);

	range = spmi_regulator_find_range(vreg);
	अगर (!range)
		वापस -EINVAL;

	वापस spmi_hw_selector_to_sw(vreg, voltage_sel, range);
पूर्ण

अटल पूर्णांक spmi_regulator_ftsmps426_get_voltage(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);
	स्थिर काष्ठा spmi_voltage_range *range;
	u8 buf[2];
	पूर्णांक uV;

	spmi_vreg_पढ़ो(vreg, SPMI_FTSMPS426_REG_VOLTAGE_LSB, buf, 2);

	uV = (((अचिन्हित पूर्णांक)buf[1] << 8) | (अचिन्हित पूर्णांक)buf[0]) * 1000;
	range = vreg->set_poपूर्णांकs->range;

	वापस (uV - range->set_poपूर्णांक_min_uV) / range->step_uV;
पूर्ण

अटल पूर्णांक spmi_regulator_single_map_voltage(काष्ठा regulator_dev *rdev,
		पूर्णांक min_uV, पूर्णांक max_uV)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);

	वापस spmi_regulator_select_voltage(vreg, min_uV, max_uV);
पूर्ण

अटल पूर्णांक spmi_regulator_single_range_set_voltage(काष्ठा regulator_dev *rdev,
						   अचिन्हित selector)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);
	u8 sel = selector;

	/*
	 * Certain types of regulators करो not have a range select रेजिस्टर so
	 * only voltage set रेजिस्टर needs to be written.
	 */
	वापस spmi_vreg_ग_लिखो(vreg, SPMI_COMMON_REG_VOLTAGE_SET, &sel, 1);
पूर्ण

अटल पूर्णांक spmi_regulator_single_range_get_voltage(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);
	u8 selector;
	पूर्णांक ret;

	ret = spmi_vreg_पढ़ो(vreg, SPMI_COMMON_REG_VOLTAGE_SET, &selector, 1);
	अगर (ret)
		वापस ret;

	वापस selector;
पूर्ण

अटल पूर्णांक spmi_regulator_ult_lo_smps_set_voltage(काष्ठा regulator_dev *rdev,
						  अचिन्हित selector)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);
	पूर्णांक ret;
	u8 range_sel, voltage_sel;

	ret = spmi_sw_selector_to_hw(vreg, selector, &range_sel, &voltage_sel);
	अगर (ret)
		वापस ret;

	/*
	 * Calculate VSET based on range
	 * In हाल of range 0: voltage_sel is a 7 bit value, can be written
	 *			witout any modअगरication.
	 * In हाल of range 1: voltage_sel is a 5 bit value, bits[7-5] set to
	 *			[011].
	 */
	अगर (range_sel == 1)
		voltage_sel |= ULT_SMPS_RANGE_SPLIT;

	वापस spmi_vreg_update_bits(vreg, SPMI_COMMON_REG_VOLTAGE_SET,
				     voltage_sel, 0xff);
पूर्ण

अटल पूर्णांक spmi_regulator_ult_lo_smps_get_voltage(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);
	स्थिर काष्ठा spmi_voltage_range *range;
	u8 voltage_sel;

	spmi_vreg_पढ़ो(vreg, SPMI_COMMON_REG_VOLTAGE_SET, &voltage_sel, 1);

	range = spmi_regulator_find_range(vreg);
	अगर (!range)
		वापस -EINVAL;

	अगर (range->range_sel == 1)
		voltage_sel &= ~ULT_SMPS_RANGE_SPLIT;

	वापस spmi_hw_selector_to_sw(vreg, voltage_sel, range);
पूर्ण

अटल पूर्णांक spmi_regulator_common_list_voltage(काष्ठा regulator_dev *rdev,
			अचिन्हित selector)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);
	पूर्णांक uV = 0;
	पूर्णांक i;

	अगर (selector >= vreg->set_poपूर्णांकs->n_voltages)
		वापस 0;

	क्रम (i = 0; i < vreg->set_poपूर्णांकs->count; i++) अणु
		अगर (selector < vreg->set_poपूर्णांकs->range[i].n_voltages) अणु
			uV = selector * vreg->set_poपूर्णांकs->range[i].step_uV
				+ vreg->set_poपूर्णांकs->range[i].set_poपूर्णांक_min_uV;
			अवरोध;
		पूर्ण

		selector -= vreg->set_poपूर्णांकs->range[i].n_voltages;
	पूर्ण

	वापस uV;
पूर्ण

अटल पूर्णांक
spmi_regulator_common_set_bypass(काष्ठा regulator_dev *rdev, bool enable)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);
	u8 mask = SPMI_COMMON_MODE_BYPASS_MASK;
	u8 val = 0;

	अगर (enable)
		val = mask;

	वापस spmi_vreg_update_bits(vreg, SPMI_COMMON_REG_MODE, val, mask);
पूर्ण

अटल पूर्णांक
spmi_regulator_common_get_bypass(काष्ठा regulator_dev *rdev, bool *enable)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);
	u8 val;
	पूर्णांक ret;

	ret = spmi_vreg_पढ़ो(vreg, SPMI_COMMON_REG_MODE, &val, 1);
	*enable = val & SPMI_COMMON_MODE_BYPASS_MASK;

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक spmi_regulator_common_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);
	u8 reg;

	spmi_vreg_पढ़ो(vreg, SPMI_COMMON_REG_MODE, &reg, 1);

	reg &= SPMI_COMMON_MODE_HPM_MASK | SPMI_COMMON_MODE_AUTO_MASK;

	चयन (reg) अणु
	हाल SPMI_COMMON_MODE_HPM_MASK:
		वापस REGULATOR_MODE_NORMAL;
	हाल SPMI_COMMON_MODE_AUTO_MASK:
		वापस REGULATOR_MODE_FAST;
	शेष:
		वापस REGULATOR_MODE_IDLE;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक spmi_regulator_ftsmps426_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);
	u8 reg;

	spmi_vreg_पढ़ो(vreg, SPMI_COMMON_REG_MODE, &reg, 1);

	चयन (reg) अणु
	हाल SPMI_FTSMPS426_MODE_HPM_MASK:
		वापस REGULATOR_MODE_NORMAL;
	हाल SPMI_FTSMPS426_MODE_AUTO_MASK:
		वापस REGULATOR_MODE_FAST;
	शेष:
		वापस REGULATOR_MODE_IDLE;
	पूर्ण
पूर्ण

अटल पूर्णांक
spmi_regulator_common_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);
	u8 mask = SPMI_COMMON_MODE_HPM_MASK | SPMI_COMMON_MODE_AUTO_MASK;
	u8 val;

	चयन (mode) अणु
	हाल REGULATOR_MODE_NORMAL:
		val = SPMI_COMMON_MODE_HPM_MASK;
		अवरोध;
	हाल REGULATOR_MODE_FAST:
		val = SPMI_COMMON_MODE_AUTO_MASK;
		अवरोध;
	शेष:
		val = 0;
		अवरोध;
	पूर्ण

	वापस spmi_vreg_update_bits(vreg, SPMI_COMMON_REG_MODE, val, mask);
पूर्ण

अटल पूर्णांक
spmi_regulator_ftsmps426_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);
	u8 mask = SPMI_FTSMPS426_MODE_MASK;
	u8 val;

	चयन (mode) अणु
	हाल REGULATOR_MODE_NORMAL:
		val = SPMI_FTSMPS426_MODE_HPM_MASK;
		अवरोध;
	हाल REGULATOR_MODE_FAST:
		val = SPMI_FTSMPS426_MODE_AUTO_MASK;
		अवरोध;
	हाल REGULATOR_MODE_IDLE:
		val = SPMI_FTSMPS426_MODE_LPM_MASK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस spmi_vreg_update_bits(vreg, SPMI_COMMON_REG_MODE, val, mask);
पूर्ण

अटल पूर्णांक
spmi_regulator_common_set_load(काष्ठा regulator_dev *rdev, पूर्णांक load_uA)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक mode;

	अगर (load_uA >= vreg->hpm_min_load)
		mode = REGULATOR_MODE_NORMAL;
	अन्यथा
		mode = REGULATOR_MODE_IDLE;

	वापस spmi_regulator_common_set_mode(rdev, mode);
पूर्ण

अटल पूर्णांक spmi_regulator_common_set_pull_करोwn(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक mask = SPMI_COMMON_PULL_DOWN_ENABLE_MASK;

	वापस spmi_vreg_update_bits(vreg, SPMI_COMMON_REG_PULL_DOWN,
				     mask, mask);
पूर्ण

अटल पूर्णांक spmi_regulator_common_set_soft_start(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक mask = SPMI_LDO_SOFT_START_ENABLE_MASK;

	वापस spmi_vreg_update_bits(vreg, SPMI_COMMON_REG_SOFT_START,
				     mask, mask);
पूर्ण

अटल पूर्णांक spmi_regulator_set_ilim(काष्ठा regulator_dev *rdev, पूर्णांक ilim_uA)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);
	क्रमागत spmi_regulator_logical_type type = vreg->logical_type;
	अचिन्हित पूर्णांक current_reg;
	u8 reg;
	u8 mask = SPMI_BOOST_CURRENT_LIMIT_MASK |
		  SPMI_BOOST_CURRENT_LIMIT_ENABLE_MASK;
	पूर्णांक max = (SPMI_BOOST_CURRENT_LIMIT_MASK + 1) * 500;

	अगर (type == SPMI_REGULATOR_LOGICAL_TYPE_BOOST)
		current_reg = SPMI_BOOST_REG_CURRENT_LIMIT;
	अन्यथा
		current_reg = SPMI_BOOST_BYP_REG_CURRENT_LIMIT;

	अगर (ilim_uA > max || ilim_uA <= 0)
		वापस -EINVAL;

	reg = (ilim_uA - 1) / 500;
	reg |= SPMI_BOOST_CURRENT_LIMIT_ENABLE_MASK;

	वापस spmi_vreg_update_bits(vreg, current_reg, reg, mask);
पूर्ण

अटल पूर्णांक spmi_regulator_vs_clear_ocp(काष्ठा spmi_regulator *vreg)
अणु
	पूर्णांक ret;

	ret = spmi_vreg_update_bits(vreg, SPMI_COMMON_REG_ENABLE,
		SPMI_COMMON_DISABLE, SPMI_COMMON_ENABLE_MASK);

	vreg->vs_enable_समय = kसमय_get();

	ret = spmi_vreg_update_bits(vreg, SPMI_COMMON_REG_ENABLE,
		SPMI_COMMON_ENABLE, SPMI_COMMON_ENABLE_MASK);

	वापस ret;
पूर्ण

अटल व्योम spmi_regulator_vs_ocp_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा spmi_regulator *vreg
		= container_of(dwork, काष्ठा spmi_regulator, ocp_work);

	spmi_regulator_vs_clear_ocp(vreg);
पूर्ण

अटल irqवापस_t spmi_regulator_vs_ocp_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा spmi_regulator *vreg = data;
	kसमय_प्रकार ocp_irq_समय;
	s64 ocp_trigger_delay_us;

	ocp_irq_समय = kसमय_get();
	ocp_trigger_delay_us = kसमय_us_delta(ocp_irq_समय,
						vreg->vs_enable_समय);

	/*
	 * Reset the OCP count अगर there is a large delay between चयन enable
	 * and when OCP triggers.  This is indicative of a hotplug event as
	 * opposed to a fault.
	 */
	अगर (ocp_trigger_delay_us > SPMI_VS_OCP_FAULT_DELAY_US)
		vreg->ocp_count = 0;

	/* Wait क्रम चयन output to settle back to 0 V after OCP triggered. */
	udelay(SPMI_VS_OCP_FALL_DELAY_US);

	vreg->ocp_count++;

	अगर (vreg->ocp_count == 1) अणु
		/* Immediately clear the over current condition. */
		spmi_regulator_vs_clear_ocp(vreg);
	पूर्ण अन्यथा अगर (vreg->ocp_count <= vreg->ocp_max_retries) अणु
		/* Schedule the over current clear task to run later. */
		schedule_delayed_work(&vreg->ocp_work,
			msecs_to_jअगरfies(vreg->ocp_retry_delay_ms) + 1);
	पूर्ण अन्यथा अणु
		dev_err(vreg->dev,
			"OCP triggered %d times; no further retries\n",
			vreg->ocp_count);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा SAW3_VCTL_DATA_MASK	0xFF
#घोषणा SAW3_VCTL_CLEAR_MASK	0x700FF
#घोषणा SAW3_AVS_CTL_EN_MASK	0x1
#घोषणा SAW3_AVS_CTL_TGGL_MASK	0x8000000
#घोषणा SAW3_AVS_CTL_CLEAR_MASK	0x7efc00

अटल काष्ठा regmap *saw_regmap;

अटल व्योम spmi_saw_set_vdd(व्योम *data)
अणु
	u32 vctl, data3, avs_ctl, pmic_sts;
	bool avs_enabled = false;
	अचिन्हित दीर्घ समयout;
	u8 voltage_sel = *(u8 *)data;

	regmap_पढ़ो(saw_regmap, SAW3_AVS_CTL, &avs_ctl);
	regmap_पढ़ो(saw_regmap, SAW3_VCTL, &vctl);
	regmap_पढ़ो(saw_regmap, SAW3_SPM_PMIC_DATA_3, &data3);

	/* select the band */
	vctl &= ~SAW3_VCTL_CLEAR_MASK;
	vctl |= (u32)voltage_sel;

	data3 &= ~SAW3_VCTL_CLEAR_MASK;
	data3 |= (u32)voltage_sel;

	/* If AVS is enabled, चयन it off during the voltage change */
	avs_enabled = SAW3_AVS_CTL_EN_MASK & avs_ctl;
	अगर (avs_enabled) अणु
		avs_ctl &= ~SAW3_AVS_CTL_TGGL_MASK;
		regmap_ग_लिखो(saw_regmap, SAW3_AVS_CTL, avs_ctl);
	पूर्ण

	regmap_ग_लिखो(saw_regmap, SAW3_RST, 1);
	regmap_ग_लिखो(saw_regmap, SAW3_VCTL, vctl);
	regmap_ग_लिखो(saw_regmap, SAW3_SPM_PMIC_DATA_3, data3);

	समयout = jअगरfies + usecs_to_jअगरfies(100);
	करो अणु
		regmap_पढ़ो(saw_regmap, SAW3_PMIC_STS, &pmic_sts);
		pmic_sts &= SAW3_VCTL_DATA_MASK;
		अगर (pmic_sts == (u32)voltage_sel)
			अवरोध;

		cpu_relax();

	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	/* After successful voltage change, चयन the AVS back on */
	अगर (avs_enabled) अणु
		pmic_sts &= 0x3f;
		avs_ctl &= ~SAW3_AVS_CTL_CLEAR_MASK;
		avs_ctl |= ((pmic_sts - 4) << 10);
		avs_ctl |= (pmic_sts << 17);
		avs_ctl |= SAW3_AVS_CTL_TGGL_MASK;
		regmap_ग_लिखो(saw_regmap, SAW3_AVS_CTL, avs_ctl);
	पूर्ण
पूर्ण

अटल पूर्णांक
spmi_regulator_saw_set_voltage(काष्ठा regulator_dev *rdev, अचिन्हित selector)
अणु
	काष्ठा spmi_regulator *vreg = rdev_get_drvdata(rdev);
	पूर्णांक ret;
	u8 range_sel, voltage_sel;

	ret = spmi_sw_selector_to_hw(vreg, selector, &range_sel, &voltage_sel);
	अगर (ret)
		वापस ret;

	अगर (0 != range_sel) अणु
		dev_dbg(&rdev->dev, "range_sel = %02X voltage_sel = %02X", \
			range_sel, voltage_sel);
		वापस -EINVAL;
	पूर्ण

	/* Always करो the SAW रेजिस्टर ग_लिखोs on the first CPU */
	वापस smp_call_function_single(0, spmi_saw_set_vdd, \
					&voltage_sel, true);
पूर्ण

अटल काष्ठा regulator_ops spmi_saw_ops = अणुपूर्ण;

अटल स्थिर काष्ठा regulator_ops spmi_smps_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.set_voltage_sel	= spmi_regulator_common_set_voltage,
	.set_voltage_समय_sel	= spmi_regulator_set_voltage_समय_sel,
	.get_voltage_sel	= spmi_regulator_common_get_voltage,
	.map_voltage		= spmi_regulator_common_map_voltage,
	.list_voltage		= spmi_regulator_common_list_voltage,
	.set_mode		= spmi_regulator_common_set_mode,
	.get_mode		= spmi_regulator_common_get_mode,
	.set_load		= spmi_regulator_common_set_load,
	.set_pull_करोwn		= spmi_regulator_common_set_pull_करोwn,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops spmi_lकरो_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.set_voltage_sel	= spmi_regulator_common_set_voltage,
	.get_voltage_sel	= spmi_regulator_common_get_voltage,
	.map_voltage		= spmi_regulator_common_map_voltage,
	.list_voltage		= spmi_regulator_common_list_voltage,
	.set_mode		= spmi_regulator_common_set_mode,
	.get_mode		= spmi_regulator_common_get_mode,
	.set_load		= spmi_regulator_common_set_load,
	.set_bypass		= spmi_regulator_common_set_bypass,
	.get_bypass		= spmi_regulator_common_get_bypass,
	.set_pull_करोwn		= spmi_regulator_common_set_pull_करोwn,
	.set_soft_start		= spmi_regulator_common_set_soft_start,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops spmi_ln_lकरो_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.set_voltage_sel	= spmi_regulator_common_set_voltage,
	.get_voltage_sel	= spmi_regulator_common_get_voltage,
	.map_voltage		= spmi_regulator_common_map_voltage,
	.list_voltage		= spmi_regulator_common_list_voltage,
	.set_bypass		= spmi_regulator_common_set_bypass,
	.get_bypass		= spmi_regulator_common_get_bypass,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops spmi_vs_ops = अणु
	.enable			= spmi_regulator_vs_enable,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.set_pull_करोwn		= spmi_regulator_common_set_pull_करोwn,
	.set_soft_start		= spmi_regulator_common_set_soft_start,
	.set_over_current_protection = spmi_regulator_vs_ocp,
	.set_mode		= spmi_regulator_common_set_mode,
	.get_mode		= spmi_regulator_common_get_mode,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops spmi_boost_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.set_voltage_sel	= spmi_regulator_single_range_set_voltage,
	.get_voltage_sel	= spmi_regulator_single_range_get_voltage,
	.map_voltage		= spmi_regulator_single_map_voltage,
	.list_voltage		= spmi_regulator_common_list_voltage,
	.set_input_current_limit = spmi_regulator_set_ilim,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops spmi_ftsmps_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.set_voltage_sel	= spmi_regulator_common_set_voltage,
	.set_voltage_समय_sel	= spmi_regulator_set_voltage_समय_sel,
	.get_voltage_sel	= spmi_regulator_common_get_voltage,
	.map_voltage		= spmi_regulator_common_map_voltage,
	.list_voltage		= spmi_regulator_common_list_voltage,
	.set_mode		= spmi_regulator_common_set_mode,
	.get_mode		= spmi_regulator_common_get_mode,
	.set_load		= spmi_regulator_common_set_load,
	.set_pull_करोwn		= spmi_regulator_common_set_pull_करोwn,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops spmi_ult_lo_smps_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.set_voltage_sel	= spmi_regulator_ult_lo_smps_set_voltage,
	.set_voltage_समय_sel	= spmi_regulator_set_voltage_समय_sel,
	.get_voltage_sel	= spmi_regulator_ult_lo_smps_get_voltage,
	.list_voltage		= spmi_regulator_common_list_voltage,
	.set_mode		= spmi_regulator_common_set_mode,
	.get_mode		= spmi_regulator_common_get_mode,
	.set_load		= spmi_regulator_common_set_load,
	.set_pull_करोwn		= spmi_regulator_common_set_pull_करोwn,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops spmi_ult_ho_smps_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.set_voltage_sel	= spmi_regulator_single_range_set_voltage,
	.set_voltage_समय_sel	= spmi_regulator_set_voltage_समय_sel,
	.get_voltage_sel	= spmi_regulator_single_range_get_voltage,
	.map_voltage		= spmi_regulator_single_map_voltage,
	.list_voltage		= spmi_regulator_common_list_voltage,
	.set_mode		= spmi_regulator_common_set_mode,
	.get_mode		= spmi_regulator_common_get_mode,
	.set_load		= spmi_regulator_common_set_load,
	.set_pull_करोwn		= spmi_regulator_common_set_pull_करोwn,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops spmi_ult_lकरो_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.set_voltage_sel	= spmi_regulator_single_range_set_voltage,
	.get_voltage_sel	= spmi_regulator_single_range_get_voltage,
	.map_voltage		= spmi_regulator_single_map_voltage,
	.list_voltage		= spmi_regulator_common_list_voltage,
	.set_mode		= spmi_regulator_common_set_mode,
	.get_mode		= spmi_regulator_common_get_mode,
	.set_load		= spmi_regulator_common_set_load,
	.set_bypass		= spmi_regulator_common_set_bypass,
	.get_bypass		= spmi_regulator_common_get_bypass,
	.set_pull_करोwn		= spmi_regulator_common_set_pull_करोwn,
	.set_soft_start		= spmi_regulator_common_set_soft_start,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops spmi_ftsmps426_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.set_voltage_sel	= spmi_regulator_ftsmps426_set_voltage,
	.set_voltage_समय_sel	= spmi_regulator_set_voltage_समय_sel,
	.get_voltage_sel	= spmi_regulator_ftsmps426_get_voltage,
	.map_voltage		= spmi_regulator_single_map_voltage,
	.list_voltage		= spmi_regulator_common_list_voltage,
	.set_mode		= spmi_regulator_ftsmps426_set_mode,
	.get_mode		= spmi_regulator_ftsmps426_get_mode,
	.set_load		= spmi_regulator_common_set_load,
	.set_pull_करोwn		= spmi_regulator_common_set_pull_करोwn,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops spmi_hfs430_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.set_voltage_sel	= spmi_regulator_ftsmps426_set_voltage,
	.set_voltage_समय_sel	= spmi_regulator_set_voltage_समय_sel,
	.get_voltage_sel	= spmi_regulator_ftsmps426_get_voltage,
	.map_voltage		= spmi_regulator_single_map_voltage,
	.list_voltage		= spmi_regulator_common_list_voltage,
	.set_mode		= spmi_regulator_ftsmps426_set_mode,
	.get_mode		= spmi_regulator_ftsmps426_get_mode,
पूर्ण;

/* Maximum possible digital major revision value */
#घोषणा INF 0xFF

अटल स्थिर काष्ठा spmi_regulator_mapping supported_regulators[] = अणु
	/*           type subtype dig_min dig_max ltype ops setpoपूर्णांकs hpm_min */
	SPMI_VREG(BUCK,  GP_CTL,   0, INF, SMPS,   smps,   smps,   100000),
	SPMI_VREG(BUCK,  HFS430,   0, INF, HFS430, hfs430, hfs430,  10000),
	SPMI_VREG(LDO,   N300,     0, INF, LDO,    lकरो,    nlकरो1,   10000),
	SPMI_VREG(LDO,   N600,     0,   0, LDO,    lकरो,    nlकरो2,   10000),
	SPMI_VREG(LDO,   N1200,    0,   0, LDO,    lकरो,    nlकरो2,   10000),
	SPMI_VREG(LDO,   N600,     1, INF, LDO,    lकरो,    nlकरो3,   10000),
	SPMI_VREG(LDO,   N1200,    1, INF, LDO,    lकरो,    nlकरो3,   10000),
	SPMI_VREG(LDO,   N600_ST,  0,   0, LDO,    lकरो,    nlकरो2,   10000),
	SPMI_VREG(LDO,   N1200_ST, 0,   0, LDO,    lकरो,    nlकरो2,   10000),
	SPMI_VREG(LDO,   N600_ST,  1, INF, LDO,    lकरो,    nlकरो3,   10000),
	SPMI_VREG(LDO,   N1200_ST, 1, INF, LDO,    lकरो,    nlकरो3,   10000),
	SPMI_VREG(LDO,   P50,      0, INF, LDO,    lकरो,    plकरो,     5000),
	SPMI_VREG(LDO,   P150,     0, INF, LDO,    lकरो,    plकरो,    10000),
	SPMI_VREG(LDO,   P300,     0, INF, LDO,    lकरो,    plकरो,    10000),
	SPMI_VREG(LDO,   P600,     0, INF, LDO,    lकरो,    plकरो,    10000),
	SPMI_VREG(LDO,   P1200,    0, INF, LDO,    lकरो,    plकरो,    10000),
	SPMI_VREG(LDO,   LN,       0, INF, LN_LDO, ln_lकरो, ln_lकरो,      0),
	SPMI_VREG(LDO,   LV_P50,   0, INF, LDO,    lकरो,    plकरो,     5000),
	SPMI_VREG(LDO,   LV_P150,  0, INF, LDO,    lकरो,    plकरो,    10000),
	SPMI_VREG(LDO,   LV_P300,  0, INF, LDO,    lकरो,    plकरो,    10000),
	SPMI_VREG(LDO,   LV_P600,  0, INF, LDO,    lकरो,    plकरो,    10000),
	SPMI_VREG(LDO,   LV_P1200, 0, INF, LDO,    lकरो,    plकरो,    10000),
	SPMI_VREG(LDO, HT_N300_ST,   0, INF, FTSMPS426, ftsmps426,
							ht_nlकरो,   30000),
	SPMI_VREG(LDO, HT_N600_ST,   0, INF, FTSMPS426, ftsmps426,
							ht_nlकरो,   30000),
	SPMI_VREG(LDO, HT_N1200_ST,  0, INF, FTSMPS426, ftsmps426,
							ht_nlकरो,   30000),
	SPMI_VREG(LDO, HT_LVP150,    0, INF, FTSMPS426, ftsmps426,
							ht_lvplकरो, 10000),
	SPMI_VREG(LDO, HT_LVP300,    0, INF, FTSMPS426, ftsmps426,
							ht_lvplकरो, 10000),
	SPMI_VREG(LDO, L660_N300_ST, 0, INF, FTSMPS426, ftsmps426,
							nlकरो660,   10000),
	SPMI_VREG(LDO, L660_N600_ST, 0, INF, FTSMPS426, ftsmps426,
							nlकरो660,   10000),
	SPMI_VREG(LDO, L660_P50,     0, INF, FTSMPS426, ftsmps426,
							plकरो660,   10000),
	SPMI_VREG(LDO, L660_P150,    0, INF, FTSMPS426, ftsmps426,
							plकरो660,   10000),
	SPMI_VREG(LDO, L660_P600,    0, INF, FTSMPS426, ftsmps426,
							plकरो660,   10000),
	SPMI_VREG(LDO, L660_LVP150,  0, INF, FTSMPS426, ftsmps426,
							ht_lvplकरो, 10000),
	SPMI_VREG(LDO, L660_LVP600,  0, INF, FTSMPS426, ftsmps426,
							ht_lvplकरो, 10000),
	SPMI_VREG_VS(LV100,        0, INF),
	SPMI_VREG_VS(LV300,        0, INF),
	SPMI_VREG_VS(MV300,        0, INF),
	SPMI_VREG_VS(MV500,        0, INF),
	SPMI_VREG_VS(HDMI,         0, INF),
	SPMI_VREG_VS(OTG,          0, INF),
	SPMI_VREG(BOOST, 5V_BOOST, 0, INF, BOOST,  boost,  boost,       0),
	SPMI_VREG(FTS,   FTS_CTL,  0, INF, FTSMPS, ftsmps, ftsmps, 100000),
	SPMI_VREG(FTS, FTS2p5_CTL, 0, INF, FTSMPS, ftsmps, ftsmps2p5, 100000),
	SPMI_VREG(FTS, FTS426_CTL, 0, INF, FTSMPS426, ftsmps426, ftsmps426, 100000),
	SPMI_VREG(BOOST_BYP, BB_2A, 0, INF, BOOST_BYP, boost, boost_byp, 0),
	SPMI_VREG(ULT_BUCK, ULT_HF_CTL1, 0, INF, ULT_LO_SMPS, ult_lo_smps,
						ult_lo_smps,   100000),
	SPMI_VREG(ULT_BUCK, ULT_HF_CTL2, 0, INF, ULT_LO_SMPS, ult_lo_smps,
						ult_lo_smps,   100000),
	SPMI_VREG(ULT_BUCK, ULT_HF_CTL3, 0, INF, ULT_LO_SMPS, ult_lo_smps,
						ult_lo_smps,   100000),
	SPMI_VREG(ULT_BUCK, ULT_HF_CTL4, 0, INF, ULT_HO_SMPS, ult_ho_smps,
						ult_ho_smps,   100000),
	SPMI_VREG(ULT_LDO, N300_ST, 0, INF, ULT_LDO, ult_lकरो, ult_nlकरो, 10000),
	SPMI_VREG(ULT_LDO, N600_ST, 0, INF, ULT_LDO, ult_lकरो, ult_nlकरो, 10000),
	SPMI_VREG(ULT_LDO, N900_ST, 0, INF, ULT_LDO, ult_lकरो, ult_nlकरो, 10000),
	SPMI_VREG(ULT_LDO, N1200_ST, 0, INF, ULT_LDO, ult_lकरो, ult_nlकरो, 10000),
	SPMI_VREG(ULT_LDO, LV_P50,   0, INF, ULT_LDO, ult_lकरो, ult_plकरो, 10000),
	SPMI_VREG(ULT_LDO, LV_P150,  0, INF, ULT_LDO, ult_lकरो, ult_plकरो, 10000),
	SPMI_VREG(ULT_LDO, LV_P300,  0, INF, ULT_LDO, ult_lकरो, ult_plकरो, 10000),
	SPMI_VREG(ULT_LDO, LV_P450,  0, INF, ULT_LDO, ult_lकरो, ult_plकरो, 10000),
	SPMI_VREG(ULT_LDO, P600,     0, INF, ULT_LDO, ult_lकरो, ult_plकरो, 10000),
	SPMI_VREG(ULT_LDO, P300,     0, INF, ULT_LDO, ult_lकरो, ult_plकरो, 10000),
	SPMI_VREG(ULT_LDO, P150,     0, INF, ULT_LDO, ult_lकरो, ult_plकरो, 10000),
	SPMI_VREG(ULT_LDO, P50,     0, INF, ULT_LDO, ult_lकरो, ult_plकरो, 5000),
पूर्ण;

अटल व्योम spmi_calculate_num_voltages(काष्ठा spmi_voltage_set_poपूर्णांकs *poपूर्णांकs)
अणु
	अचिन्हित पूर्णांक n;
	काष्ठा spmi_voltage_range *range = poपूर्णांकs->range;

	क्रम (; range < poपूर्णांकs->range + poपूर्णांकs->count; range++) अणु
		n = 0;
		अगर (range->set_poपूर्णांक_max_uV) अणु
			n = range->set_poपूर्णांक_max_uV - range->set_poपूर्णांक_min_uV;
			n = (n / range->step_uV) + 1;
		पूर्ण
		range->n_voltages = n;
		poपूर्णांकs->n_voltages += n;
	पूर्ण
पूर्ण

अटल पूर्णांक spmi_regulator_match(काष्ठा spmi_regulator *vreg, u16 क्रमce_type)
अणु
	स्थिर काष्ठा spmi_regulator_mapping *mapping;
	पूर्णांक ret, i;
	u32 dig_major_rev;
	u8 version[SPMI_COMMON_REG_SUBTYPE - SPMI_COMMON_REG_DIG_MAJOR_REV + 1];
	u8 type, subtype;

	ret = spmi_vreg_पढ़ो(vreg, SPMI_COMMON_REG_DIG_MAJOR_REV, version,
		ARRAY_SIZE(version));
	अगर (ret) अणु
		dev_dbg(vreg->dev, "could not read version registers\n");
		वापस ret;
	पूर्ण
	dig_major_rev	= version[SPMI_COMMON_REG_DIG_MAJOR_REV
					- SPMI_COMMON_REG_DIG_MAJOR_REV];

	अगर (!क्रमce_type) अणु
		type		= version[SPMI_COMMON_REG_TYPE -
					  SPMI_COMMON_REG_DIG_MAJOR_REV];
		subtype		= version[SPMI_COMMON_REG_SUBTYPE -
					  SPMI_COMMON_REG_DIG_MAJOR_REV];
	पूर्ण अन्यथा अणु
		type = क्रमce_type >> 8;
		subtype = क्रमce_type;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(supported_regulators); i++) अणु
		mapping = &supported_regulators[i];
		अगर (mapping->type == type && mapping->subtype == subtype
		    && mapping->revision_min <= dig_major_rev
		    && mapping->revision_max >= dig_major_rev)
			जाओ found;
	पूर्ण

	dev_err(vreg->dev,
		"unsupported regulator: name=%s type=0x%02X, subtype=0x%02X, dig major rev=0x%02X\n",
		vreg->desc.name, type, subtype, dig_major_rev);

	वापस -ENODEV;

found:
	vreg->logical_type	= mapping->logical_type;
	vreg->set_poपूर्णांकs	= mapping->set_poपूर्णांकs;
	vreg->hpm_min_load	= mapping->hpm_min_load;
	vreg->desc.ops		= mapping->ops;

	अगर (mapping->set_poपूर्णांकs) अणु
		अगर (!mapping->set_poपूर्णांकs->n_voltages)
			spmi_calculate_num_voltages(mapping->set_poपूर्णांकs);
		vreg->desc.n_voltages = mapping->set_poपूर्णांकs->n_voltages;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक spmi_regulator_init_slew_rate(काष्ठा spmi_regulator *vreg)
अणु
	पूर्णांक ret;
	u8 reg = 0;
	पूर्णांक step, delay, slew_rate, step_delay;
	स्थिर काष्ठा spmi_voltage_range *range;

	ret = spmi_vreg_पढ़ो(vreg, SPMI_COMMON_REG_STEP_CTRL, &reg, 1);
	अगर (ret) अणु
		dev_err(vreg->dev, "spmi read failed, ret=%d\n", ret);
		वापस ret;
	पूर्ण

	range = spmi_regulator_find_range(vreg);
	अगर (!range)
		वापस -EINVAL;

	चयन (vreg->logical_type) अणु
	हाल SPMI_REGULATOR_LOGICAL_TYPE_FTSMPS:
		step_delay = SPMI_FTSMPS_STEP_DELAY;
		अवरोध;
	शेष:
		step_delay = SPMI_DEFAULT_STEP_DELAY;
		अवरोध;
	पूर्ण

	step = reg & SPMI_FTSMPS_STEP_CTRL_STEP_MASK;
	step >>= SPMI_FTSMPS_STEP_CTRL_STEP_SHIFT;

	delay = reg & SPMI_FTSMPS_STEP_CTRL_DELAY_MASK;
	delay >>= SPMI_FTSMPS_STEP_CTRL_DELAY_SHIFT;

	/* slew_rate has units of uV/us */
	slew_rate = SPMI_FTSMPS_CLOCK_RATE * range->step_uV * (1 << step);
	slew_rate /= 1000 * (step_delay << delay);
	slew_rate *= SPMI_FTSMPS_STEP_MARGIN_NUM;
	slew_rate /= SPMI_FTSMPS_STEP_MARGIN_DEN;

	/* Ensure that the slew rate is greater than 0 */
	vreg->slew_rate = max(slew_rate, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक spmi_regulator_init_slew_rate_ftsmps426(काष्ठा spmi_regulator *vreg,
						   पूर्णांक घड़ी_rate)
अणु
	पूर्णांक ret;
	u8 reg = 0;
	पूर्णांक delay, slew_rate;
	स्थिर काष्ठा spmi_voltage_range *range = &vreg->set_poपूर्णांकs->range[0];

	ret = spmi_vreg_पढ़ो(vreg, SPMI_COMMON_REG_STEP_CTRL, &reg, 1);
	अगर (ret) अणु
		dev_err(vreg->dev, "spmi read failed, ret=%d\n", ret);
		वापस ret;
	पूर्ण

	delay = reg & SPMI_FTSMPS426_STEP_CTRL_DELAY_MASK;
	delay >>= SPMI_FTSMPS426_STEP_CTRL_DELAY_SHIFT;

	/* slew_rate has units of uV/us */
	slew_rate = घड़ी_rate * range->step_uV;
	slew_rate /= 1000 * (SPMI_FTSMPS426_STEP_DELAY << delay);
	slew_rate *= SPMI_FTSMPS426_STEP_MARGIN_NUM;
	slew_rate /= SPMI_FTSMPS426_STEP_MARGIN_DEN;

	/* Ensure that the slew rate is greater than 0 */
	vreg->slew_rate = max(slew_rate, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक spmi_regulator_init_रेजिस्टरs(काष्ठा spmi_regulator *vreg,
				स्थिर काष्ठा spmi_regulator_init_data *data)
अणु
	पूर्णांक ret;
	क्रमागत spmi_regulator_logical_type type;
	u8 ctrl_reg[8], reg, mask;

	type = vreg->logical_type;

	ret = spmi_vreg_पढ़ो(vreg, SPMI_COMMON_REG_VOLTAGE_RANGE, ctrl_reg, 8);
	अगर (ret)
		वापस ret;

	/* Set up enable pin control. */
	अगर (!(data->pin_ctrl_enable & SPMI_REGULATOR_PIN_CTRL_ENABLE_HW_DEFAULT)) अणु
		चयन (type) अणु
		हाल SPMI_REGULATOR_LOGICAL_TYPE_SMPS:
		हाल SPMI_REGULATOR_LOGICAL_TYPE_LDO:
		हाल SPMI_REGULATOR_LOGICAL_TYPE_VS:
			ctrl_reg[SPMI_COMMON_IDX_ENABLE] &=
				~SPMI_COMMON_ENABLE_FOLLOW_ALL_MASK;
			ctrl_reg[SPMI_COMMON_IDX_ENABLE] |=
				data->pin_ctrl_enable & SPMI_COMMON_ENABLE_FOLLOW_ALL_MASK;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/* Set up mode pin control. */
	अगर (!(data->pin_ctrl_hpm & SPMI_REGULATOR_PIN_CTRL_HPM_HW_DEFAULT)) अणु
		चयन (type) अणु
		हाल SPMI_REGULATOR_LOGICAL_TYPE_SMPS:
		हाल SPMI_REGULATOR_LOGICAL_TYPE_LDO:
			ctrl_reg[SPMI_COMMON_IDX_MODE] &=
				~SPMI_COMMON_MODE_FOLLOW_ALL_MASK;
			ctrl_reg[SPMI_COMMON_IDX_MODE] |=
				data->pin_ctrl_hpm & SPMI_COMMON_MODE_FOLLOW_ALL_MASK;
			अवरोध;
		हाल SPMI_REGULATOR_LOGICAL_TYPE_VS:
		हाल SPMI_REGULATOR_LOGICAL_TYPE_ULT_LO_SMPS:
		हाल SPMI_REGULATOR_LOGICAL_TYPE_ULT_HO_SMPS:
		हाल SPMI_REGULATOR_LOGICAL_TYPE_ULT_LDO:
			ctrl_reg[SPMI_COMMON_IDX_MODE] &=
				~SPMI_COMMON_MODE_FOLLOW_AWAKE_MASK;
			ctrl_reg[SPMI_COMMON_IDX_MODE] |=
				data->pin_ctrl_hpm & SPMI_COMMON_MODE_FOLLOW_AWAKE_MASK;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/* Write back any control रेजिस्टर values that were modअगरied. */
	ret = spmi_vreg_ग_लिखो(vreg, SPMI_COMMON_REG_VOLTAGE_RANGE, ctrl_reg, 8);
	अगर (ret)
		वापस ret;

	/* Set soft start strength and over current protection क्रम VS. */
	अगर (type == SPMI_REGULATOR_LOGICAL_TYPE_VS) अणु
		अगर (data->vs_soft_start_strength
				!= SPMI_VS_SOFT_START_STR_HW_DEFAULT) अणु
			reg = data->vs_soft_start_strength
				& SPMI_VS_SOFT_START_SEL_MASK;
			mask = SPMI_VS_SOFT_START_SEL_MASK;
			वापस spmi_vreg_update_bits(vreg,
						     SPMI_VS_REG_SOFT_START,
						     reg, mask);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम spmi_regulator_get_dt_config(काष्ठा spmi_regulator *vreg,
		काष्ठा device_node *node, काष्ठा spmi_regulator_init_data *data)
अणु
	/*
	 * Initialize configuration parameters to use hardware शेष in हाल
	 * no value is specअगरied via device tree.
	 */
	data->pin_ctrl_enable	    = SPMI_REGULATOR_PIN_CTRL_ENABLE_HW_DEFAULT;
	data->pin_ctrl_hpm	    = SPMI_REGULATOR_PIN_CTRL_HPM_HW_DEFAULT;
	data->vs_soft_start_strength	= SPMI_VS_SOFT_START_STR_HW_DEFAULT;

	/* These bindings are optional, so it is okay अगर they aren't found. */
	of_property_पढ़ो_u32(node, "qcom,ocp-max-retries",
		&vreg->ocp_max_retries);
	of_property_पढ़ो_u32(node, "qcom,ocp-retry-delay",
		&vreg->ocp_retry_delay_ms);
	of_property_पढ़ो_u32(node, "qcom,pin-ctrl-enable",
		&data->pin_ctrl_enable);
	of_property_पढ़ो_u32(node, "qcom,pin-ctrl-hpm", &data->pin_ctrl_hpm);
	of_property_पढ़ो_u32(node, "qcom,vs-soft-start-strength",
		&data->vs_soft_start_strength);
पूर्ण

अटल अचिन्हित पूर्णांक spmi_regulator_of_map_mode(अचिन्हित पूर्णांक mode)
अणु
	अगर (mode == 1)
		वापस REGULATOR_MODE_NORMAL;
	अगर (mode == 2)
		वापस REGULATOR_MODE_FAST;

	वापस REGULATOR_MODE_IDLE;
पूर्ण

अटल पूर्णांक spmi_regulator_of_parse(काष्ठा device_node *node,
			    स्थिर काष्ठा regulator_desc *desc,
			    काष्ठा regulator_config *config)
अणु
	काष्ठा spmi_regulator_init_data data = अणु पूर्ण;
	काष्ठा spmi_regulator *vreg = config->driver_data;
	काष्ठा device *dev = config->dev;
	पूर्णांक ret;

	spmi_regulator_get_dt_config(vreg, node, &data);

	अगर (!vreg->ocp_max_retries)
		vreg->ocp_max_retries = SPMI_VS_OCP_DEFAULT_MAX_RETRIES;
	अगर (!vreg->ocp_retry_delay_ms)
		vreg->ocp_retry_delay_ms = SPMI_VS_OCP_DEFAULT_RETRY_DELAY_MS;

	ret = spmi_regulator_init_रेजिस्टरs(vreg, &data);
	अगर (ret) अणु
		dev_err(dev, "common initialization failed, ret=%d\n", ret);
		वापस ret;
	पूर्ण

	चयन (vreg->logical_type) अणु
	हाल SPMI_REGULATOR_LOGICAL_TYPE_FTSMPS:
	हाल SPMI_REGULATOR_LOGICAL_TYPE_ULT_LO_SMPS:
	हाल SPMI_REGULATOR_LOGICAL_TYPE_ULT_HO_SMPS:
	हाल SPMI_REGULATOR_LOGICAL_TYPE_SMPS:
		ret = spmi_regulator_init_slew_rate(vreg);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल SPMI_REGULATOR_LOGICAL_TYPE_FTSMPS426:
		ret = spmi_regulator_init_slew_rate_ftsmps426(vreg,
						SPMI_FTSMPS426_CLOCK_RATE);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल SPMI_REGULATOR_LOGICAL_TYPE_HFS430:
		ret = spmi_regulator_init_slew_rate_ftsmps426(vreg,
							SPMI_HFS430_CLOCK_RATE);
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (vreg->logical_type != SPMI_REGULATOR_LOGICAL_TYPE_VS)
		vreg->ocp_irq = 0;

	अगर (vreg->ocp_irq) अणु
		ret = devm_request_irq(dev, vreg->ocp_irq,
			spmi_regulator_vs_ocp_isr, IRQF_TRIGGER_RISING, "ocp",
			vreg);
		अगर (ret < 0) अणु
			dev_err(dev, "failed to request irq %d, ret=%d\n",
				vreg->ocp_irq, ret);
			वापस ret;
		पूर्ण

		ret = devm_delayed_work_स्वतःcancel(dev, &vreg->ocp_work,
						   spmi_regulator_vs_ocp_work);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spmi_regulator_data pm8941_regulators[] = अणु
	अणु "s1", 0x1400, "vdd_s1", पूर्ण,
	अणु "s2", 0x1700, "vdd_s2", पूर्ण,
	अणु "s3", 0x1a00, "vdd_s3", पूर्ण,
	अणु "s4", 0xa000, पूर्ण,
	अणु "l1", 0x4000, "vdd_l1_l3", पूर्ण,
	अणु "l2", 0x4100, "vdd_l2_lvs_1_2_3", पूर्ण,
	अणु "l3", 0x4200, "vdd_l1_l3", पूर्ण,
	अणु "l4", 0x4300, "vdd_l4_l11", पूर्ण,
	अणु "l5", 0x4400, "vdd_l5_l7", शून्य, 0x0410 पूर्ण,
	अणु "l6", 0x4500, "vdd_l6_l12_l14_l15", पूर्ण,
	अणु "l7", 0x4600, "vdd_l5_l7", शून्य, 0x0410 पूर्ण,
	अणु "l8", 0x4700, "vdd_l8_l16_l18_19", पूर्ण,
	अणु "l9", 0x4800, "vdd_l9_l10_l17_l22", पूर्ण,
	अणु "l10", 0x4900, "vdd_l9_l10_l17_l22", पूर्ण,
	अणु "l11", 0x4a00, "vdd_l4_l11", पूर्ण,
	अणु "l12", 0x4b00, "vdd_l6_l12_l14_l15", पूर्ण,
	अणु "l13", 0x4c00, "vdd_l13_l20_l23_l24", पूर्ण,
	अणु "l14", 0x4d00, "vdd_l6_l12_l14_l15", पूर्ण,
	अणु "l15", 0x4e00, "vdd_l6_l12_l14_l15", पूर्ण,
	अणु "l16", 0x4f00, "vdd_l8_l16_l18_19", पूर्ण,
	अणु "l17", 0x5000, "vdd_l9_l10_l17_l22", पूर्ण,
	अणु "l18", 0x5100, "vdd_l8_l16_l18_19", पूर्ण,
	अणु "l19", 0x5200, "vdd_l8_l16_l18_19", पूर्ण,
	अणु "l20", 0x5300, "vdd_l13_l20_l23_l24", पूर्ण,
	अणु "l21", 0x5400, "vdd_l21", पूर्ण,
	अणु "l22", 0x5500, "vdd_l9_l10_l17_l22", पूर्ण,
	अणु "l23", 0x5600, "vdd_l13_l20_l23_l24", पूर्ण,
	अणु "l24", 0x5700, "vdd_l13_l20_l23_l24", पूर्ण,
	अणु "lvs1", 0x8000, "vdd_l2_lvs_1_2_3", पूर्ण,
	अणु "lvs2", 0x8100, "vdd_l2_lvs_1_2_3", पूर्ण,
	अणु "lvs3", 0x8200, "vdd_l2_lvs_1_2_3", पूर्ण,
	अणु "5vs1", 0x8300, "vin_5vs", "ocp-5vs1", पूर्ण,
	अणु "5vs2", 0x8400, "vin_5vs", "ocp-5vs2", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा spmi_regulator_data pm8841_regulators[] = अणु
	अणु "s1", 0x1400, "vdd_s1", पूर्ण,
	अणु "s2", 0x1700, "vdd_s2", शून्य, 0x1c08 पूर्ण,
	अणु "s3", 0x1a00, "vdd_s3", पूर्ण,
	अणु "s4", 0x1d00, "vdd_s4", शून्य, 0x1c08 पूर्ण,
	अणु "s5", 0x2000, "vdd_s5", शून्य, 0x1c08 पूर्ण,
	अणु "s6", 0x2300, "vdd_s6", शून्य, 0x1c08 पूर्ण,
	अणु "s7", 0x2600, "vdd_s7", शून्य, 0x1c08 पूर्ण,
	अणु "s8", 0x2900, "vdd_s8", शून्य, 0x1c08 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा spmi_regulator_data pm8916_regulators[] = अणु
	अणु "s1", 0x1400, "vdd_s1", पूर्ण,
	अणु "s2", 0x1700, "vdd_s2", पूर्ण,
	अणु "s3", 0x1a00, "vdd_s3", पूर्ण,
	अणु "s4", 0x1d00, "vdd_s4", पूर्ण,
	अणु "l1", 0x4000, "vdd_l1_l3", पूर्ण,
	अणु "l2", 0x4100, "vdd_l2", पूर्ण,
	अणु "l3", 0x4200, "vdd_l1_l3", पूर्ण,
	अणु "l4", 0x4300, "vdd_l4_l5_l6", पूर्ण,
	अणु "l5", 0x4400, "vdd_l4_l5_l6", पूर्ण,
	अणु "l6", 0x4500, "vdd_l4_l5_l6", पूर्ण,
	अणु "l7", 0x4600, "vdd_l7", पूर्ण,
	अणु "l8", 0x4700, "vdd_l8_l11_l14_l15_l16", पूर्ण,
	अणु "l9", 0x4800, "vdd_l9_l10_l12_l13_l17_l18", पूर्ण,
	अणु "l10", 0x4900, "vdd_l9_l10_l12_l13_l17_l18", पूर्ण,
	अणु "l11", 0x4a00, "vdd_l8_l11_l14_l15_l16", पूर्ण,
	अणु "l12", 0x4b00, "vdd_l9_l10_l12_l13_l17_l18", पूर्ण,
	अणु "l13", 0x4c00, "vdd_l9_l10_l12_l13_l17_l18", पूर्ण,
	अणु "l14", 0x4d00, "vdd_l8_l11_l14_l15_l16", पूर्ण,
	अणु "l15", 0x4e00, "vdd_l8_l11_l14_l15_l16", पूर्ण,
	अणु "l16", 0x4f00, "vdd_l8_l11_l14_l15_l16", पूर्ण,
	अणु "l17", 0x5000, "vdd_l9_l10_l12_l13_l17_l18", पूर्ण,
	अणु "l18", 0x5100, "vdd_l9_l10_l12_l13_l17_l18", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा spmi_regulator_data pm8950_regulators[] = अणु
	अणु "s1", 0x1400, "vdd_s1", पूर्ण,
	अणु "s2", 0x1700, "vdd_s2", पूर्ण,
	अणु "s3", 0x1a00, "vdd_s3", पूर्ण,
	अणु "s4", 0x1d00, "vdd_s4", पूर्ण,
	अणु "s5", 0x2000, "vdd_s5", पूर्ण,
	अणु "s6", 0x2300, "vdd_s6", पूर्ण,
	अणु "l1", 0x4000, "vdd_l1_l19", पूर्ण,
	अणु "l2", 0x4100, "vdd_l2_l23", पूर्ण,
	अणु "l3", 0x4200, "vdd_l3", पूर्ण,
	अणु "l4", 0x4300, "vdd_l4_l5_l6_l7_l16", पूर्ण,
	अणु "l5", 0x4400, "vdd_l4_l5_l6_l7_l16", पूर्ण,
	अणु "l6", 0x4500, "vdd_l4_l5_l6_l7_l16", पूर्ण,
	अणु "l7", 0x4600, "vdd_l4_l5_l6_l7_l16", पूर्ण,
	अणु "l8", 0x4700, "vdd_l8_l11_l12_l17_l22", पूर्ण,
	अणु "l9", 0x4800, "vdd_l9_l10_l13_l14_l15_l18", पूर्ण,
	अणु "l10", 0x4900, "vdd_l9_l10_l13_l14_l15_l18", पूर्ण,
	अणु "l11", 0x4a00, "vdd_l8_l11_l12_l17_l22", पूर्ण,
	अणु "l12", 0x4b00, "vdd_l8_l11_l12_l17_l22", पूर्ण,
	अणु "l13", 0x4c00, "vdd_l9_l10_l13_l14_l15_l18", पूर्ण,
	अणु "l14", 0x4d00, "vdd_l9_l10_l13_l14_l15_l18", पूर्ण,
	अणु "l15", 0x4e00, "vdd_l9_l10_l13_l14_l15_l18", पूर्ण,
	अणु "l16", 0x4f00, "vdd_l4_l5_l6_l7_l16", पूर्ण,
	अणु "l17", 0x5000, "vdd_l8_l11_l12_l17_l22", पूर्ण,
	अणु "l18", 0x5100, "vdd_l9_l10_l13_l14_l15_l18", पूर्ण,
	अणु "l19", 0x5200, "vdd_l1_l19", पूर्ण,
	अणु "l20", 0x5300, "vdd_l20", पूर्ण,
	अणु "l21", 0x5400, "vdd_l21", पूर्ण,
	अणु "l22", 0x5500, "vdd_l8_l11_l12_l17_l22", पूर्ण,
	अणु "l23", 0x5600, "vdd_l2_l23", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा spmi_regulator_data pm8994_regulators[] = अणु
	अणु "s1", 0x1400, "vdd_s1", पूर्ण,
	अणु "s2", 0x1700, "vdd_s2", पूर्ण,
	अणु "s3", 0x1a00, "vdd_s3", पूर्ण,
	अणु "s4", 0x1d00, "vdd_s4", पूर्ण,
	अणु "s5", 0x2000, "vdd_s5", पूर्ण,
	अणु "s6", 0x2300, "vdd_s6", पूर्ण,
	अणु "s7", 0x2600, "vdd_s7", पूर्ण,
	अणु "s8", 0x2900, "vdd_s8", पूर्ण,
	अणु "s9", 0x2c00, "vdd_s9", पूर्ण,
	अणु "s10", 0x2f00, "vdd_s10", पूर्ण,
	अणु "s11", 0x3200, "vdd_s11", पूर्ण,
	अणु "s12", 0x3500, "vdd_s12", पूर्ण,
	अणु "l1", 0x4000, "vdd_l1", पूर्ण,
	अणु "l2", 0x4100, "vdd_l2_l26_l28", पूर्ण,
	अणु "l3", 0x4200, "vdd_l3_l11", पूर्ण,
	अणु "l4", 0x4300, "vdd_l4_l27_l31", पूर्ण,
	अणु "l5", 0x4400, "vdd_l5_l7", पूर्ण,
	अणु "l6", 0x4500, "vdd_l6_l12_l32", पूर्ण,
	अणु "l7", 0x4600, "vdd_l5_l7", पूर्ण,
	अणु "l8", 0x4700, "vdd_l8_l16_l30", पूर्ण,
	अणु "l9", 0x4800, "vdd_l9_l10_l18_l22", पूर्ण,
	अणु "l10", 0x4900, "vdd_l9_l10_l18_l22", पूर्ण,
	अणु "l11", 0x4a00, "vdd_l3_l11", पूर्ण,
	अणु "l12", 0x4b00, "vdd_l6_l12_l32", पूर्ण,
	अणु "l13", 0x4c00, "vdd_l13_l19_l23_l24", पूर्ण,
	अणु "l14", 0x4d00, "vdd_l14_l15", पूर्ण,
	अणु "l15", 0x4e00, "vdd_l14_l15", पूर्ण,
	अणु "l16", 0x4f00, "vdd_l8_l16_l30", पूर्ण,
	अणु "l17", 0x5000, "vdd_l17_l29", पूर्ण,
	अणु "l18", 0x5100, "vdd_l9_l10_l18_l22", पूर्ण,
	अणु "l19", 0x5200, "vdd_l13_l19_l23_l24", पूर्ण,
	अणु "l20", 0x5300, "vdd_l20_l21", पूर्ण,
	अणु "l21", 0x5400, "vdd_l20_l21", पूर्ण,
	अणु "l22", 0x5500, "vdd_l9_l10_l18_l22", पूर्ण,
	अणु "l23", 0x5600, "vdd_l13_l19_l23_l24", पूर्ण,
	अणु "l24", 0x5700, "vdd_l13_l19_l23_l24", पूर्ण,
	अणु "l25", 0x5800, "vdd_l25", पूर्ण,
	अणु "l26", 0x5900, "vdd_l2_l26_l28", पूर्ण,
	अणु "l27", 0x5a00, "vdd_l4_l27_l31", पूर्ण,
	अणु "l28", 0x5b00, "vdd_l2_l26_l28", पूर्ण,
	अणु "l29", 0x5c00, "vdd_l17_l29", पूर्ण,
	अणु "l30", 0x5d00, "vdd_l8_l16_l30", पूर्ण,
	अणु "l31", 0x5e00, "vdd_l4_l27_l31", पूर्ण,
	अणु "l32", 0x5f00, "vdd_l6_l12_l32", पूर्ण,
	अणु "lvs1", 0x8000, "vdd_lvs_1_2", पूर्ण,
	अणु "lvs2", 0x8100, "vdd_lvs_1_2", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा spmi_regulator_data pmi8994_regulators[] = अणु
	अणु "s1", 0x1400, "vdd_s1", पूर्ण,
	अणु "s2", 0x1700, "vdd_s2", पूर्ण,
	अणु "s3", 0x1a00, "vdd_s3", पूर्ण,
	अणु "l1", 0x4000, "vdd_l1", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा spmi_regulator_data pm660_regulators[] = अणु
	अणु "s1", 0x1400, "vdd_s1", पूर्ण,
	अणु "s2", 0x1700, "vdd_s2", पूर्ण,
	अणु "s3", 0x1a00, "vdd_s3", पूर्ण,
	अणु "s4", 0x1d00, "vdd_s3", पूर्ण,
	अणु "s5", 0x2000, "vdd_s5", पूर्ण,
	अणु "s6", 0x2300, "vdd_s6", पूर्ण,
	अणु "l1", 0x4000, "vdd_l1_l6_l7", पूर्ण,
	अणु "l2", 0x4100, "vdd_l2_l3", पूर्ण,
	अणु "l3", 0x4200, "vdd_l2_l3", पूर्ण,
	/* l4 is unaccessible on PM660 */
	अणु "l5", 0x4400, "vdd_l5", पूर्ण,
	अणु "l6", 0x4500, "vdd_l1_l6_l7", पूर्ण,
	अणु "l7", 0x4600, "vdd_l1_l6_l7", पूर्ण,
	अणु "l8", 0x4700, "vdd_l8_l9_l10_l11_l12_l13_l14", पूर्ण,
	अणु "l9", 0x4800, "vdd_l8_l9_l10_l11_l12_l13_l14", पूर्ण,
	अणु "l10", 0x4900, "vdd_l8_l9_l10_l11_l12_l13_l14", पूर्ण,
	अणु "l11", 0x4a00, "vdd_l8_l9_l10_l11_l12_l13_l14", पूर्ण,
	अणु "l12", 0x4b00, "vdd_l8_l9_l10_l11_l12_l13_l14", पूर्ण,
	अणु "l13", 0x4c00, "vdd_l8_l9_l10_l11_l12_l13_l14", पूर्ण,
	अणु "l14", 0x4d00, "vdd_l8_l9_l10_l11_l12_l13_l14", पूर्ण,
	अणु "l15", 0x4e00, "vdd_l15_l16_l17_l18_l19", पूर्ण,
	अणु "l16", 0x4f00, "vdd_l15_l16_l17_l18_l19", पूर्ण,
	अणु "l17", 0x5000, "vdd_l15_l16_l17_l18_l19", पूर्ण,
	अणु "l18", 0x5100, "vdd_l15_l16_l17_l18_l19", पूर्ण,
	अणु "l19", 0x5200, "vdd_l15_l16_l17_l18_l19", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा spmi_regulator_data pm660l_regulators[] = अणु
	अणु "s1", 0x1400, "vdd_s1", पूर्ण,
	अणु "s2", 0x1700, "vdd_s2", पूर्ण,
	अणु "s3", 0x1a00, "vdd_s3", पूर्ण,
	अणु "s4", 0x1d00, "vdd_s4", पूर्ण,
	अणु "s5", 0x2000, "vdd_s5", पूर्ण,
	अणु "l1", 0x4000, "vdd_l1_l9_l10", पूर्ण,
	अणु "l2", 0x4100, "vdd_l2", पूर्ण,
	अणु "l3", 0x4200, "vdd_l3_l5_l7_l8", पूर्ण,
	अणु "l4", 0x4300, "vdd_l4_l6", पूर्ण,
	अणु "l5", 0x4400, "vdd_l3_l5_l7_l8", पूर्ण,
	अणु "l6", 0x4500, "vdd_l4_l6", पूर्ण,
	अणु "l7", 0x4600, "vdd_l3_l5_l7_l8", पूर्ण,
	अणु "l8", 0x4700, "vdd_l3_l5_l7_l8", पूर्ण,
	अणु "l9", 0x4800, "vdd_l1_l9_l10", पूर्ण,
	अणु "l10", 0x4900, "vdd_l1_l9_l10", पूर्ण,
	अणु पूर्ण
पूर्ण;


अटल स्थिर काष्ठा spmi_regulator_data pm8004_regulators[] = अणु
	अणु "s2", 0x1700, "vdd_s2", पूर्ण,
	अणु "s5", 0x2000, "vdd_s5", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा spmi_regulator_data pm8005_regulators[] = अणु
	अणु "s1", 0x1400, "vdd_s1", पूर्ण,
	अणु "s2", 0x1700, "vdd_s2", पूर्ण,
	अणु "s3", 0x1a00, "vdd_s3", पूर्ण,
	अणु "s4", 0x1d00, "vdd_s4", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा spmi_regulator_data pms405_regulators[] = अणु
	अणु "s3", 0x1a00, "vdd_s3"पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id qcom_spmi_regulator_match[] = अणु
	अणु .compatible = "qcom,pm8004-regulators", .data = &pm8004_regulators पूर्ण,
	अणु .compatible = "qcom,pm8005-regulators", .data = &pm8005_regulators पूर्ण,
	अणु .compatible = "qcom,pm8841-regulators", .data = &pm8841_regulators पूर्ण,
	अणु .compatible = "qcom,pm8916-regulators", .data = &pm8916_regulators पूर्ण,
	अणु .compatible = "qcom,pm8941-regulators", .data = &pm8941_regulators पूर्ण,
	अणु .compatible = "qcom,pm8950-regulators", .data = &pm8950_regulators पूर्ण,
	अणु .compatible = "qcom,pm8994-regulators", .data = &pm8994_regulators पूर्ण,
	अणु .compatible = "qcom,pmi8994-regulators", .data = &pmi8994_regulators पूर्ण,
	अणु .compatible = "qcom,pm660-regulators", .data = &pm660_regulators पूर्ण,
	अणु .compatible = "qcom,pm660l-regulators", .data = &pm660l_regulators पूर्ण,
	अणु .compatible = "qcom,pms405-regulators", .data = &pms405_regulators पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_spmi_regulator_match);

अटल पूर्णांक qcom_spmi_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा spmi_regulator_data *reg;
	स्थिर काष्ठा spmi_voltage_range *range;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	काष्ठा spmi_regulator *vreg;
	काष्ठा regmap *regmap;
	स्थिर अक्षर *name;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device_node *syscon, *reg_node;
	काष्ठा property *reg_prop;
	पूर्णांक ret, lenp;
	काष्ठा list_head *vreg_list;

	vreg_list = devm_kzalloc(dev, माप(*vreg_list), GFP_KERNEL);
	अगर (!vreg_list)
		वापस -ENOMEM;
	INIT_LIST_HEAD(vreg_list);
	platक्रमm_set_drvdata(pdev, vreg_list);

	regmap = dev_get_regmap(dev->parent, शून्य);
	अगर (!regmap)
		वापस -ENODEV;

	match = of_match_device(qcom_spmi_regulator_match, &pdev->dev);
	अगर (!match)
		वापस -ENODEV;

	अगर (of_find_property(node, "qcom,saw-reg", &lenp)) अणु
		syscon = of_parse_phandle(node, "qcom,saw-reg", 0);
		saw_regmap = syscon_node_to_regmap(syscon);
		of_node_put(syscon);
		अगर (IS_ERR(saw_regmap))
			dev_err(dev, "ERROR reading SAW regmap\n");
	पूर्ण

	क्रम (reg = match->data; reg->name; reg++) अणु

		अगर (saw_regmap) अणु
			reg_node = of_get_child_by_name(node, reg->name);
			reg_prop = of_find_property(reg_node, "qcom,saw-slave",
						    &lenp);
			of_node_put(reg_node);
			अगर (reg_prop)
				जारी;
		पूर्ण

		vreg = devm_kzalloc(dev, माप(*vreg), GFP_KERNEL);
		अगर (!vreg)
			वापस -ENOMEM;

		vreg->dev = dev;
		vreg->base = reg->base;
		vreg->regmap = regmap;
		अगर (reg->ocp) अणु
			vreg->ocp_irq = platक्रमm_get_irq_byname(pdev, reg->ocp);
			अगर (vreg->ocp_irq < 0)
				वापस vreg->ocp_irq;
		पूर्ण
		vreg->desc.id = -1;
		vreg->desc.owner = THIS_MODULE;
		vreg->desc.type = REGULATOR_VOLTAGE;
		vreg->desc.enable_reg = reg->base + SPMI_COMMON_REG_ENABLE;
		vreg->desc.enable_mask = SPMI_COMMON_ENABLE_MASK;
		vreg->desc.enable_val = SPMI_COMMON_ENABLE;
		vreg->desc.name = name = reg->name;
		vreg->desc.supply_name = reg->supply;
		vreg->desc.of_match = reg->name;
		vreg->desc.of_parse_cb = spmi_regulator_of_parse;
		vreg->desc.of_map_mode = spmi_regulator_of_map_mode;

		ret = spmi_regulator_match(vreg, reg->क्रमce_type);
		अगर (ret)
			जारी;

		अगर (saw_regmap) अणु
			reg_node = of_get_child_by_name(node, reg->name);
			reg_prop = of_find_property(reg_node, "qcom,saw-leader",
						    &lenp);
			of_node_put(reg_node);
			अगर (reg_prop) अणु
				spmi_saw_ops = *(vreg->desc.ops);
				spmi_saw_ops.set_voltage_sel =
					spmi_regulator_saw_set_voltage;
				vreg->desc.ops = &spmi_saw_ops;
			पूर्ण
		पूर्ण

		अगर (vreg->set_poपूर्णांकs && vreg->set_poपूर्णांकs->count == 1) अणु
			/* since there is only one range */
			range = vreg->set_poपूर्णांकs->range;
			vreg->desc.uV_step = range->step_uV;
		पूर्ण

		config.dev = dev;
		config.driver_data = vreg;
		config.regmap = regmap;
		rdev = devm_regulator_रेजिस्टर(dev, &vreg->desc, &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(dev, "failed to register %s\n", name);
			वापस PTR_ERR(rdev);
		पूर्ण

		INIT_LIST_HEAD(&vreg->node);
		list_add(&vreg->node, vreg_list);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver qcom_spmi_regulator_driver = अणु
	.driver		= अणु
		.name	= "qcom-spmi-regulator",
		.of_match_table = qcom_spmi_regulator_match,
	पूर्ण,
	.probe		= qcom_spmi_regulator_probe,
पूर्ण;
module_platक्रमm_driver(qcom_spmi_regulator_driver);

MODULE_DESCRIPTION("Qualcomm SPMI PMIC regulator driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:qcom-spmi-regulator");
