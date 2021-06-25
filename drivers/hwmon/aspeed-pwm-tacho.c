<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2016 Google, Inc
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/thermal.h>

/* ASPEED PWM & FAN Tach Register Definition */
#घोषणा ASPEED_PTCR_CTRL		0x00
#घोषणा ASPEED_PTCR_CLK_CTRL		0x04
#घोषणा ASPEED_PTCR_DUTY0_CTRL		0x08
#घोषणा ASPEED_PTCR_DUTY1_CTRL		0x0c
#घोषणा ASPEED_PTCR_TYPEM_CTRL		0x10
#घोषणा ASPEED_PTCR_TYPEM_CTRL1		0x14
#घोषणा ASPEED_PTCR_TYPEN_CTRL		0x18
#घोषणा ASPEED_PTCR_TYPEN_CTRL1		0x1c
#घोषणा ASPEED_PTCR_TACH_SOURCE		0x20
#घोषणा ASPEED_PTCR_TRIGGER		0x28
#घोषणा ASPEED_PTCR_RESULT		0x2c
#घोषणा ASPEED_PTCR_INTR_CTRL		0x30
#घोषणा ASPEED_PTCR_INTR_STS		0x34
#घोषणा ASPEED_PTCR_TYPEM_LIMIT		0x38
#घोषणा ASPEED_PTCR_TYPEN_LIMIT		0x3C
#घोषणा ASPEED_PTCR_CTRL_EXT		0x40
#घोषणा ASPEED_PTCR_CLK_CTRL_EXT	0x44
#घोषणा ASPEED_PTCR_DUTY2_CTRL		0x48
#घोषणा ASPEED_PTCR_DUTY3_CTRL		0x4c
#घोषणा ASPEED_PTCR_TYPEO_CTRL		0x50
#घोषणा ASPEED_PTCR_TYPEO_CTRL1		0x54
#घोषणा ASPEED_PTCR_TACH_SOURCE_EXT	0x60
#घोषणा ASPEED_PTCR_TYPEO_LIMIT		0x78

/* ASPEED_PTCR_CTRL : 0x00 - General Control Register */
#घोषणा ASPEED_PTCR_CTRL_SET_PWMD_TYPE_PART1	15
#घोषणा ASPEED_PTCR_CTRL_SET_PWMD_TYPE_PART2	6
#घोषणा ASPEED_PTCR_CTRL_SET_PWMD_TYPE_MASK	(BIT(7) | BIT(15))

#घोषणा ASPEED_PTCR_CTRL_SET_PWMC_TYPE_PART1	14
#घोषणा ASPEED_PTCR_CTRL_SET_PWMC_TYPE_PART2	5
#घोषणा ASPEED_PTCR_CTRL_SET_PWMC_TYPE_MASK	(BIT(6) | BIT(14))

#घोषणा ASPEED_PTCR_CTRL_SET_PWMB_TYPE_PART1	13
#घोषणा ASPEED_PTCR_CTRL_SET_PWMB_TYPE_PART2	4
#घोषणा ASPEED_PTCR_CTRL_SET_PWMB_TYPE_MASK	(BIT(5) | BIT(13))

#घोषणा ASPEED_PTCR_CTRL_SET_PWMA_TYPE_PART1	12
#घोषणा ASPEED_PTCR_CTRL_SET_PWMA_TYPE_PART2	3
#घोषणा ASPEED_PTCR_CTRL_SET_PWMA_TYPE_MASK	(BIT(4) | BIT(12))

#घोषणा	ASPEED_PTCR_CTRL_FAN_NUM_EN(x)	BIT(16 + (x))

#घोषणा	ASPEED_PTCR_CTRL_PWMD_EN	BIT(11)
#घोषणा	ASPEED_PTCR_CTRL_PWMC_EN	BIT(10)
#घोषणा	ASPEED_PTCR_CTRL_PWMB_EN	BIT(9)
#घोषणा	ASPEED_PTCR_CTRL_PWMA_EN	BIT(8)

#घोषणा	ASPEED_PTCR_CTRL_CLK_SRC	BIT(1)
#घोषणा	ASPEED_PTCR_CTRL_CLK_EN		BIT(0)

/* ASPEED_PTCR_CLK_CTRL : 0x04 - Clock Control Register */
/* TYPE N */
#घोषणा ASPEED_PTCR_CLK_CTRL_TYPEN_MASK		GENMASK(31, 16)
#घोषणा ASPEED_PTCR_CLK_CTRL_TYPEN_UNIT		24
#घोषणा ASPEED_PTCR_CLK_CTRL_TYPEN_H		20
#घोषणा ASPEED_PTCR_CLK_CTRL_TYPEN_L		16
/* TYPE M */
#घोषणा ASPEED_PTCR_CLK_CTRL_TYPEM_MASK         GENMASK(15, 0)
#घोषणा ASPEED_PTCR_CLK_CTRL_TYPEM_UNIT		8
#घोषणा ASPEED_PTCR_CLK_CTRL_TYPEM_H		4
#घोषणा ASPEED_PTCR_CLK_CTRL_TYPEM_L		0

/*
 * ASPEED_PTCR_DUTY_CTRL/1/2/3 : 0x08/0x0C/0x48/0x4C - PWM-FAN duty control
 * 0/1/2/3 रेजिस्टर
 */
#घोषणा DUTY_CTRL_PWM2_FALL_POINT	24
#घोषणा DUTY_CTRL_PWM2_RISE_POINT	16
#घोषणा DUTY_CTRL_PWM2_RISE_FALL_MASK	GENMASK(31, 16)
#घोषणा DUTY_CTRL_PWM1_FALL_POINT	8
#घोषणा DUTY_CTRL_PWM1_RISE_POINT	0
#घोषणा DUTY_CTRL_PWM1_RISE_FALL_MASK   GENMASK(15, 0)

/* ASPEED_PTCR_TYPEM_CTRL : 0x10/0x18/0x50 - Type M/N/O Ctrl 0 Register */
#घोषणा TYPE_CTRL_FAN_MASK		(GENMASK(5, 1) | GENMASK(31, 16))
#घोषणा TYPE_CTRL_FAN1_MASK		GENMASK(31, 0)
#घोषणा TYPE_CTRL_FAN_PERIOD		16
#घोषणा TYPE_CTRL_FAN_MODE		4
#घोषणा TYPE_CTRL_FAN_DIVISION		1
#घोषणा TYPE_CTRL_FAN_TYPE_EN		1

/* ASPEED_PTCR_TACH_SOURCE : 0x20/0x60 - Tach Source Register */
/* bit [0,1] at 0x20, bit [2] at 0x60 */
#घोषणा TACH_PWM_SOURCE_BIT01(x)	((x) * 2)
#घोषणा TACH_PWM_SOURCE_BIT2(x)		((x) * 2)
#घोषणा TACH_PWM_SOURCE_MASK_BIT01(x)	(0x3 << ((x) * 2))
#घोषणा TACH_PWM_SOURCE_MASK_BIT2(x)	BIT((x) * 2)

/* ASPEED_PTCR_RESULT : 0x2c - Result Register */
#घोषणा RESULT_STATUS_MASK		BIT(31)
#घोषणा RESULT_VALUE_MASK		0xfffff

/* ASPEED_PTCR_CTRL_EXT : 0x40 - General Control Extension #1 Register */
#घोषणा ASPEED_PTCR_CTRL_SET_PWMH_TYPE_PART1	15
#घोषणा ASPEED_PTCR_CTRL_SET_PWMH_TYPE_PART2	6
#घोषणा ASPEED_PTCR_CTRL_SET_PWMH_TYPE_MASK	(BIT(7) | BIT(15))

#घोषणा ASPEED_PTCR_CTRL_SET_PWMG_TYPE_PART1	14
#घोषणा ASPEED_PTCR_CTRL_SET_PWMG_TYPE_PART2	5
#घोषणा ASPEED_PTCR_CTRL_SET_PWMG_TYPE_MASK	(BIT(6) | BIT(14))

#घोषणा ASPEED_PTCR_CTRL_SET_PWMF_TYPE_PART1	13
#घोषणा ASPEED_PTCR_CTRL_SET_PWMF_TYPE_PART2	4
#घोषणा ASPEED_PTCR_CTRL_SET_PWMF_TYPE_MASK	(BIT(5) | BIT(13))

#घोषणा ASPEED_PTCR_CTRL_SET_PWME_TYPE_PART1	12
#घोषणा ASPEED_PTCR_CTRL_SET_PWME_TYPE_PART2	3
#घोषणा ASPEED_PTCR_CTRL_SET_PWME_TYPE_MASK	(BIT(4) | BIT(12))

#घोषणा	ASPEED_PTCR_CTRL_PWMH_EN	BIT(11)
#घोषणा	ASPEED_PTCR_CTRL_PWMG_EN	BIT(10)
#घोषणा	ASPEED_PTCR_CTRL_PWMF_EN	BIT(9)
#घोषणा	ASPEED_PTCR_CTRL_PWME_EN	BIT(8)

/* ASPEED_PTCR_CLK_EXT_CTRL : 0x44 - Clock Control Extension #1 Register */
/* TYPE O */
#घोषणा ASPEED_PTCR_CLK_CTRL_TYPEO_MASK         GENMASK(15, 0)
#घोषणा ASPEED_PTCR_CLK_CTRL_TYPEO_UNIT		8
#घोषणा ASPEED_PTCR_CLK_CTRL_TYPEO_H		4
#घोषणा ASPEED_PTCR_CLK_CTRL_TYPEO_L		0

#घोषणा PWM_MAX 255

#घोषणा BOTH_EDGES 0x02 /* 10b */

#घोषणा M_PWM_DIV_H 0x00
#घोषणा M_PWM_DIV_L 0x05
#घोषणा M_PWM_PERIOD 0x5F
#घोषणा M_TACH_CLK_DIV 0x00
/*
 * 5:4 Type N fan tach mode selection bit:
 * 00: falling
 * 01: rising
 * 10: both
 * 11: reserved.
 */
#घोषणा M_TACH_MODE 0x02 /* 10b */
#घोषणा M_TACH_UNIT 0x0210
#घोषणा INIT_FAN_CTRL 0xFF

/* How दीर्घ we sleep in us जबतक रुकोing क्रम an RPM result. */
#घोषणा ASPEED_RPM_STATUS_SLEEP_USEC	500

#घोषणा MAX_CDEV_NAME_LEN 16

काष्ठा aspeed_cooling_device अणु
	अक्षर name[16];
	काष्ठा aspeed_pwm_tacho_data *priv;
	काष्ठा thermal_cooling_device *tcdev;
	पूर्णांक pwm_port;
	u8 *cooling_levels;
	u8 max_state;
	u8 cur_state;
पूर्ण;

काष्ठा aspeed_pwm_tacho_data अणु
	काष्ठा regmap *regmap;
	काष्ठा reset_control *rst;
	अचिन्हित दीर्घ clk_freq;
	bool pwm_present[8];
	bool fan_tach_present[16];
	u8 type_pwm_घड़ी_unit[3];
	u8 type_pwm_घड़ी_भागision_h[3];
	u8 type_pwm_घड़ी_भागision_l[3];
	u8 type_fan_tach_घड़ी_भागision[3];
	u8 type_fan_tach_mode[3];
	u16 type_fan_tach_unit[3];
	u8 pwm_port_type[8];
	u8 pwm_port_fan_ctrl[8];
	u8 fan_tach_ch_source[16];
	काष्ठा aspeed_cooling_device *cdev[8];
	स्थिर काष्ठा attribute_group *groups[3];
पूर्ण;

क्रमागत type अणु TYPEM, TYPEN, TYPEO पूर्ण;

काष्ठा type_params अणु
	u32 l_value;
	u32 h_value;
	u32 unit_value;
	u32 clk_ctrl_mask;
	u32 clk_ctrl_reg;
	u32 ctrl_reg;
	u32 ctrl_reg1;
पूर्ण;

अटल स्थिर काष्ठा type_params type_params[] = अणु
	[TYPEM] = अणु
		.l_value = ASPEED_PTCR_CLK_CTRL_TYPEM_L,
		.h_value = ASPEED_PTCR_CLK_CTRL_TYPEM_H,
		.unit_value = ASPEED_PTCR_CLK_CTRL_TYPEM_UNIT,
		.clk_ctrl_mask = ASPEED_PTCR_CLK_CTRL_TYPEM_MASK,
		.clk_ctrl_reg = ASPEED_PTCR_CLK_CTRL,
		.ctrl_reg = ASPEED_PTCR_TYPEM_CTRL,
		.ctrl_reg1 = ASPEED_PTCR_TYPEM_CTRL1,
	पूर्ण,
	[TYPEN] = अणु
		.l_value = ASPEED_PTCR_CLK_CTRL_TYPEN_L,
		.h_value = ASPEED_PTCR_CLK_CTRL_TYPEN_H,
		.unit_value = ASPEED_PTCR_CLK_CTRL_TYPEN_UNIT,
		.clk_ctrl_mask = ASPEED_PTCR_CLK_CTRL_TYPEN_MASK,
		.clk_ctrl_reg = ASPEED_PTCR_CLK_CTRL,
		.ctrl_reg = ASPEED_PTCR_TYPEN_CTRL,
		.ctrl_reg1 = ASPEED_PTCR_TYPEN_CTRL1,
	पूर्ण,
	[TYPEO] = अणु
		.l_value = ASPEED_PTCR_CLK_CTRL_TYPEO_L,
		.h_value = ASPEED_PTCR_CLK_CTRL_TYPEO_H,
		.unit_value = ASPEED_PTCR_CLK_CTRL_TYPEO_UNIT,
		.clk_ctrl_mask = ASPEED_PTCR_CLK_CTRL_TYPEO_MASK,
		.clk_ctrl_reg = ASPEED_PTCR_CLK_CTRL_EXT,
		.ctrl_reg = ASPEED_PTCR_TYPEO_CTRL,
		.ctrl_reg1 = ASPEED_PTCR_TYPEO_CTRL1,
	पूर्ण
पूर्ण;

क्रमागत pwm_port अणु PWMA, PWMB, PWMC, PWMD, PWME, PWMF, PWMG, PWMH पूर्ण;

काष्ठा pwm_port_params अणु
	u32 pwm_en;
	u32 ctrl_reg;
	u32 type_part1;
	u32 type_part2;
	u32 type_mask;
	u32 duty_ctrl_rise_poपूर्णांक;
	u32 duty_ctrl_fall_poपूर्णांक;
	u32 duty_ctrl_reg;
	u32 duty_ctrl_rise_fall_mask;
पूर्ण;

अटल स्थिर काष्ठा pwm_port_params pwm_port_params[] = अणु
	[PWMA] = अणु
		.pwm_en = ASPEED_PTCR_CTRL_PWMA_EN,
		.ctrl_reg = ASPEED_PTCR_CTRL,
		.type_part1 = ASPEED_PTCR_CTRL_SET_PWMA_TYPE_PART1,
		.type_part2 = ASPEED_PTCR_CTRL_SET_PWMA_TYPE_PART2,
		.type_mask = ASPEED_PTCR_CTRL_SET_PWMA_TYPE_MASK,
		.duty_ctrl_rise_poपूर्णांक = DUTY_CTRL_PWM1_RISE_POINT,
		.duty_ctrl_fall_poपूर्णांक = DUTY_CTRL_PWM1_FALL_POINT,
		.duty_ctrl_reg = ASPEED_PTCR_DUTY0_CTRL,
		.duty_ctrl_rise_fall_mask = DUTY_CTRL_PWM1_RISE_FALL_MASK,
	पूर्ण,
	[PWMB] = अणु
		.pwm_en = ASPEED_PTCR_CTRL_PWMB_EN,
		.ctrl_reg = ASPEED_PTCR_CTRL,
		.type_part1 = ASPEED_PTCR_CTRL_SET_PWMB_TYPE_PART1,
		.type_part2 = ASPEED_PTCR_CTRL_SET_PWMB_TYPE_PART2,
		.type_mask = ASPEED_PTCR_CTRL_SET_PWMB_TYPE_MASK,
		.duty_ctrl_rise_poपूर्णांक = DUTY_CTRL_PWM2_RISE_POINT,
		.duty_ctrl_fall_poपूर्णांक = DUTY_CTRL_PWM2_FALL_POINT,
		.duty_ctrl_reg = ASPEED_PTCR_DUTY0_CTRL,
		.duty_ctrl_rise_fall_mask = DUTY_CTRL_PWM2_RISE_FALL_MASK,
	पूर्ण,
	[PWMC] = अणु
		.pwm_en = ASPEED_PTCR_CTRL_PWMC_EN,
		.ctrl_reg = ASPEED_PTCR_CTRL,
		.type_part1 = ASPEED_PTCR_CTRL_SET_PWMC_TYPE_PART1,
		.type_part2 = ASPEED_PTCR_CTRL_SET_PWMC_TYPE_PART2,
		.type_mask = ASPEED_PTCR_CTRL_SET_PWMC_TYPE_MASK,
		.duty_ctrl_rise_poपूर्णांक = DUTY_CTRL_PWM1_RISE_POINT,
		.duty_ctrl_fall_poपूर्णांक = DUTY_CTRL_PWM1_FALL_POINT,
		.duty_ctrl_reg = ASPEED_PTCR_DUTY1_CTRL,
		.duty_ctrl_rise_fall_mask = DUTY_CTRL_PWM1_RISE_FALL_MASK,
	पूर्ण,
	[PWMD] = अणु
		.pwm_en = ASPEED_PTCR_CTRL_PWMD_EN,
		.ctrl_reg = ASPEED_PTCR_CTRL,
		.type_part1 = ASPEED_PTCR_CTRL_SET_PWMD_TYPE_PART1,
		.type_part2 = ASPEED_PTCR_CTRL_SET_PWMD_TYPE_PART2,
		.type_mask = ASPEED_PTCR_CTRL_SET_PWMD_TYPE_MASK,
		.duty_ctrl_rise_poपूर्णांक = DUTY_CTRL_PWM2_RISE_POINT,
		.duty_ctrl_fall_poपूर्णांक = DUTY_CTRL_PWM2_FALL_POINT,
		.duty_ctrl_reg = ASPEED_PTCR_DUTY1_CTRL,
		.duty_ctrl_rise_fall_mask = DUTY_CTRL_PWM2_RISE_FALL_MASK,
	पूर्ण,
	[PWME] = अणु
		.pwm_en = ASPEED_PTCR_CTRL_PWME_EN,
		.ctrl_reg = ASPEED_PTCR_CTRL_EXT,
		.type_part1 = ASPEED_PTCR_CTRL_SET_PWME_TYPE_PART1,
		.type_part2 = ASPEED_PTCR_CTRL_SET_PWME_TYPE_PART2,
		.type_mask = ASPEED_PTCR_CTRL_SET_PWME_TYPE_MASK,
		.duty_ctrl_rise_poपूर्णांक = DUTY_CTRL_PWM1_RISE_POINT,
		.duty_ctrl_fall_poपूर्णांक = DUTY_CTRL_PWM1_FALL_POINT,
		.duty_ctrl_reg = ASPEED_PTCR_DUTY2_CTRL,
		.duty_ctrl_rise_fall_mask = DUTY_CTRL_PWM1_RISE_FALL_MASK,
	पूर्ण,
	[PWMF] = अणु
		.pwm_en = ASPEED_PTCR_CTRL_PWMF_EN,
		.ctrl_reg = ASPEED_PTCR_CTRL_EXT,
		.type_part1 = ASPEED_PTCR_CTRL_SET_PWMF_TYPE_PART1,
		.type_part2 = ASPEED_PTCR_CTRL_SET_PWMF_TYPE_PART2,
		.type_mask = ASPEED_PTCR_CTRL_SET_PWMF_TYPE_MASK,
		.duty_ctrl_rise_poपूर्णांक = DUTY_CTRL_PWM2_RISE_POINT,
		.duty_ctrl_fall_poपूर्णांक = DUTY_CTRL_PWM2_FALL_POINT,
		.duty_ctrl_reg = ASPEED_PTCR_DUTY2_CTRL,
		.duty_ctrl_rise_fall_mask = DUTY_CTRL_PWM2_RISE_FALL_MASK,
	पूर्ण,
	[PWMG] = अणु
		.pwm_en = ASPEED_PTCR_CTRL_PWMG_EN,
		.ctrl_reg = ASPEED_PTCR_CTRL_EXT,
		.type_part1 = ASPEED_PTCR_CTRL_SET_PWMG_TYPE_PART1,
		.type_part2 = ASPEED_PTCR_CTRL_SET_PWMG_TYPE_PART2,
		.type_mask = ASPEED_PTCR_CTRL_SET_PWMG_TYPE_MASK,
		.duty_ctrl_rise_poपूर्णांक = DUTY_CTRL_PWM1_RISE_POINT,
		.duty_ctrl_fall_poपूर्णांक = DUTY_CTRL_PWM1_FALL_POINT,
		.duty_ctrl_reg = ASPEED_PTCR_DUTY3_CTRL,
		.duty_ctrl_rise_fall_mask = DUTY_CTRL_PWM1_RISE_FALL_MASK,
	पूर्ण,
	[PWMH] = अणु
		.pwm_en = ASPEED_PTCR_CTRL_PWMH_EN,
		.ctrl_reg = ASPEED_PTCR_CTRL_EXT,
		.type_part1 = ASPEED_PTCR_CTRL_SET_PWMH_TYPE_PART1,
		.type_part2 = ASPEED_PTCR_CTRL_SET_PWMH_TYPE_PART2,
		.type_mask = ASPEED_PTCR_CTRL_SET_PWMH_TYPE_MASK,
		.duty_ctrl_rise_poपूर्णांक = DUTY_CTRL_PWM2_RISE_POINT,
		.duty_ctrl_fall_poपूर्णांक = DUTY_CTRL_PWM2_FALL_POINT,
		.duty_ctrl_reg = ASPEED_PTCR_DUTY3_CTRL,
		.duty_ctrl_rise_fall_mask = DUTY_CTRL_PWM2_RISE_FALL_MASK,
	पूर्ण
पूर्ण;

अटल पूर्णांक regmap_aspeed_pwm_tacho_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
					     अचिन्हित पूर्णांक val)
अणु
	व्योम __iomem *regs = (व्योम __iomem *)context;

	ग_लिखोl(val, regs + reg);
	वापस 0;
पूर्ण

अटल पूर्णांक regmap_aspeed_pwm_tacho_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
					    अचिन्हित पूर्णांक *val)
अणु
	व्योम __iomem *regs = (व्योम __iomem *)context;

	*val = पढ़ोl(regs + reg);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config aspeed_pwm_tacho_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = ASPEED_PTCR_TYPEO_LIMIT,
	.reg_ग_लिखो = regmap_aspeed_pwm_tacho_reg_ग_लिखो,
	.reg_पढ़ो = regmap_aspeed_pwm_tacho_reg_पढ़ो,
	.fast_io = true,
पूर्ण;

अटल व्योम aspeed_set_घड़ी_enable(काष्ठा regmap *regmap, bool val)
अणु
	regmap_update_bits(regmap, ASPEED_PTCR_CTRL,
			   ASPEED_PTCR_CTRL_CLK_EN,
			   val ? ASPEED_PTCR_CTRL_CLK_EN : 0);
पूर्ण

अटल व्योम aspeed_set_घड़ी_source(काष्ठा regmap *regmap, पूर्णांक val)
अणु
	regmap_update_bits(regmap, ASPEED_PTCR_CTRL,
			   ASPEED_PTCR_CTRL_CLK_SRC,
			   val ? ASPEED_PTCR_CTRL_CLK_SRC : 0);
पूर्ण

अटल व्योम aspeed_set_pwm_घड़ी_values(काष्ठा regmap *regmap, u8 type,
					u8 भाग_high, u8 भाग_low, u8 unit)
अणु
	u32 reg_value = ((भाग_high << type_params[type].h_value) |
			 (भाग_low << type_params[type].l_value) |
			 (unit << type_params[type].unit_value));

	regmap_update_bits(regmap, type_params[type].clk_ctrl_reg,
			   type_params[type].clk_ctrl_mask, reg_value);
पूर्ण

अटल व्योम aspeed_set_pwm_port_enable(काष्ठा regmap *regmap, u8 pwm_port,
				       bool enable)
अणु
	regmap_update_bits(regmap, pwm_port_params[pwm_port].ctrl_reg,
			   pwm_port_params[pwm_port].pwm_en,
			   enable ? pwm_port_params[pwm_port].pwm_en : 0);
पूर्ण

अटल व्योम aspeed_set_pwm_port_type(काष्ठा regmap *regmap,
				     u8 pwm_port, u8 type)
अणु
	u32 reg_value = (type & 0x1) << pwm_port_params[pwm_port].type_part1;

	reg_value |= (type & 0x2) << pwm_port_params[pwm_port].type_part2;

	regmap_update_bits(regmap, pwm_port_params[pwm_port].ctrl_reg,
			   pwm_port_params[pwm_port].type_mask, reg_value);
पूर्ण

अटल व्योम aspeed_set_pwm_port_duty_rising_falling(काष्ठा regmap *regmap,
						    u8 pwm_port, u8 rising,
						    u8 falling)
अणु
	u32 reg_value = (rising <<
			 pwm_port_params[pwm_port].duty_ctrl_rise_poपूर्णांक);
	reg_value |= (falling <<
		      pwm_port_params[pwm_port].duty_ctrl_fall_poपूर्णांक);

	regmap_update_bits(regmap, pwm_port_params[pwm_port].duty_ctrl_reg,
			   pwm_port_params[pwm_port].duty_ctrl_rise_fall_mask,
			   reg_value);
पूर्ण

अटल व्योम aspeed_set_tacho_type_enable(काष्ठा regmap *regmap, u8 type,
					 bool enable)
अणु
	regmap_update_bits(regmap, type_params[type].ctrl_reg,
			   TYPE_CTRL_FAN_TYPE_EN,
			   enable ? TYPE_CTRL_FAN_TYPE_EN : 0);
पूर्ण

अटल व्योम aspeed_set_tacho_type_values(काष्ठा regmap *regmap, u8 type,
					 u8 mode, u16 unit, u8 भागision)
अणु
	u32 reg_value = ((mode << TYPE_CTRL_FAN_MODE) |
			 (unit << TYPE_CTRL_FAN_PERIOD) |
			 (भागision << TYPE_CTRL_FAN_DIVISION));

	regmap_update_bits(regmap, type_params[type].ctrl_reg,
			   TYPE_CTRL_FAN_MASK, reg_value);
	regmap_update_bits(regmap, type_params[type].ctrl_reg1,
			   TYPE_CTRL_FAN1_MASK, unit << 16);
पूर्ण

अटल व्योम aspeed_set_fan_tach_ch_enable(काष्ठा regmap *regmap, u8 fan_tach_ch,
					  bool enable)
अणु
	regmap_update_bits(regmap, ASPEED_PTCR_CTRL,
			   ASPEED_PTCR_CTRL_FAN_NUM_EN(fan_tach_ch),
			   enable ?
			   ASPEED_PTCR_CTRL_FAN_NUM_EN(fan_tach_ch) : 0);
पूर्ण

अटल व्योम aspeed_set_fan_tach_ch_source(काष्ठा regmap *regmap, u8 fan_tach_ch,
					  u8 fan_tach_ch_source)
अणु
	u32 reg_value1 = ((fan_tach_ch_source & 0x3) <<
			  TACH_PWM_SOURCE_BIT01(fan_tach_ch));
	u32 reg_value2 = (((fan_tach_ch_source & 0x4) >> 2) <<
			  TACH_PWM_SOURCE_BIT2(fan_tach_ch));

	regmap_update_bits(regmap, ASPEED_PTCR_TACH_SOURCE,
			   TACH_PWM_SOURCE_MASK_BIT01(fan_tach_ch),
			   reg_value1);

	regmap_update_bits(regmap, ASPEED_PTCR_TACH_SOURCE_EXT,
			   TACH_PWM_SOURCE_MASK_BIT2(fan_tach_ch),
			   reg_value2);
पूर्ण

अटल व्योम aspeed_set_pwm_port_fan_ctrl(काष्ठा aspeed_pwm_tacho_data *priv,
					 u8 index, u8 fan_ctrl)
अणु
	u16 period, dc_समय_on;

	period = priv->type_pwm_घड़ी_unit[priv->pwm_port_type[index]];
	period += 1;
	dc_समय_on = (fan_ctrl * period) / PWM_MAX;

	अगर (dc_समय_on == 0) अणु
		aspeed_set_pwm_port_enable(priv->regmap, index, false);
	पूर्ण अन्यथा अणु
		अगर (dc_समय_on == period)
			dc_समय_on = 0;

		aspeed_set_pwm_port_duty_rising_falling(priv->regmap, index, 0,
							dc_समय_on);
		aspeed_set_pwm_port_enable(priv->regmap, index, true);
	पूर्ण
पूर्ण

अटल u32 aspeed_get_fan_tach_ch_measure_period(काष्ठा aspeed_pwm_tacho_data
						 *priv, u8 type)
अणु
	u32 clk;
	u16 tacho_unit;
	u8 clk_unit, भाग_h, भाग_l, tacho_भाग;

	clk = priv->clk_freq;
	clk_unit = priv->type_pwm_घड़ी_unit[type];
	भाग_h = priv->type_pwm_घड़ी_भागision_h[type];
	भाग_h = 0x1 << भाग_h;
	भाग_l = priv->type_pwm_घड़ी_भागision_l[type];
	अगर (भाग_l == 0)
		भाग_l = 1;
	अन्यथा
		भाग_l = भाग_l * 2;

	tacho_unit = priv->type_fan_tach_unit[type];
	tacho_भाग = priv->type_fan_tach_घड़ी_भागision[type];

	tacho_भाग = 0x4 << (tacho_भाग * 2);
	वापस clk / (clk_unit * भाग_h * भाग_l * tacho_भाग * tacho_unit);
पूर्ण

अटल पूर्णांक aspeed_get_fan_tach_ch_rpm(काष्ठा aspeed_pwm_tacho_data *priv,
				      u8 fan_tach_ch)
अणु
	u32 raw_data, tach_भाग, clk_source, msec, usec, val;
	u8 fan_tach_ch_source, type, mode, both;
	पूर्णांक ret;

	regmap_ग_लिखो(priv->regmap, ASPEED_PTCR_TRIGGER, 0);
	regmap_ग_लिखो(priv->regmap, ASPEED_PTCR_TRIGGER, 0x1 << fan_tach_ch);

	fan_tach_ch_source = priv->fan_tach_ch_source[fan_tach_ch];
	type = priv->pwm_port_type[fan_tach_ch_source];

	msec = (1000 / aspeed_get_fan_tach_ch_measure_period(priv, type));
	usec = msec * 1000;

	ret = regmap_पढ़ो_poll_समयout(
		priv->regmap,
		ASPEED_PTCR_RESULT,
		val,
		(val & RESULT_STATUS_MASK),
		ASPEED_RPM_STATUS_SLEEP_USEC,
		usec);

	/* वापस -ETIMEDOUT अगर we didn't get an answer. */
	अगर (ret)
		वापस ret;

	raw_data = val & RESULT_VALUE_MASK;
	tach_भाग = priv->type_fan_tach_घड़ी_भागision[type];
	/*
	 * We need the mode to determine अगर the raw_data is द्विगुन (from
	 * counting both edges).
	 */
	mode = priv->type_fan_tach_mode[type];
	both = (mode & BOTH_EDGES) ? 1 : 0;

	tach_भाग = (0x4 << both) << (tach_भाग * 2);
	clk_source = priv->clk_freq;

	अगर (raw_data == 0)
		वापस 0;

	वापस (clk_source * 60) / (2 * raw_data * tach_भाग);
पूर्ण

अटल sमाप_प्रकार pwm_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक index = sensor_attr->index;
	पूर्णांक ret;
	काष्ठा aspeed_pwm_tacho_data *priv = dev_get_drvdata(dev);
	दीर्घ fan_ctrl;

	ret = kम_से_दीर्घ(buf, 10, &fan_ctrl);
	अगर (ret != 0)
		वापस ret;

	अगर (fan_ctrl < 0 || fan_ctrl > PWM_MAX)
		वापस -EINVAL;

	अगर (priv->pwm_port_fan_ctrl[index] == fan_ctrl)
		वापस count;

	priv->pwm_port_fan_ctrl[index] = fan_ctrl;
	aspeed_set_pwm_port_fan_ctrl(priv, index, fan_ctrl);

	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक index = sensor_attr->index;
	काष्ठा aspeed_pwm_tacho_data *priv = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", priv->pwm_port_fan_ctrl[index]);
पूर्ण

अटल sमाप_प्रकार rpm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक index = sensor_attr->index;
	पूर्णांक rpm;
	काष्ठा aspeed_pwm_tacho_data *priv = dev_get_drvdata(dev);

	rpm = aspeed_get_fan_tach_ch_rpm(priv, index);
	अगर (rpm < 0)
		वापस rpm;

	वापस प्र_लिखो(buf, "%d\n", rpm);
पूर्ण

अटल umode_t pwm_is_visible(काष्ठा kobject *kobj,
			      काष्ठा attribute *a, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा aspeed_pwm_tacho_data *priv = dev_get_drvdata(dev);

	अगर (!priv->pwm_present[index])
		वापस 0;
	वापस a->mode;
पूर्ण

अटल umode_t fan_dev_is_visible(काष्ठा kobject *kobj,
				  काष्ठा attribute *a, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा aspeed_pwm_tacho_data *priv = dev_get_drvdata(dev);

	अगर (!priv->fan_tach_present[index])
		वापस 0;
	वापस a->mode;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(pwm1, pwm, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2, pwm, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm3, pwm, 2);
अटल SENSOR_DEVICE_ATTR_RW(pwm4, pwm, 3);
अटल SENSOR_DEVICE_ATTR_RW(pwm5, pwm, 4);
अटल SENSOR_DEVICE_ATTR_RW(pwm6, pwm, 5);
अटल SENSOR_DEVICE_ATTR_RW(pwm7, pwm, 6);
अटल SENSOR_DEVICE_ATTR_RW(pwm8, pwm, 7);
अटल काष्ठा attribute *pwm_dev_attrs[] = अणु
	&sensor_dev_attr_pwm1.dev_attr.attr,
	&sensor_dev_attr_pwm2.dev_attr.attr,
	&sensor_dev_attr_pwm3.dev_attr.attr,
	&sensor_dev_attr_pwm4.dev_attr.attr,
	&sensor_dev_attr_pwm5.dev_attr.attr,
	&sensor_dev_attr_pwm6.dev_attr.attr,
	&sensor_dev_attr_pwm7.dev_attr.attr,
	&sensor_dev_attr_pwm8.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group pwm_dev_group = अणु
	.attrs = pwm_dev_attrs,
	.is_visible = pwm_is_visible,
पूर्ण;

अटल SENSOR_DEVICE_ATTR_RO(fan1_input, rpm, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_input, rpm, 1);
अटल SENSOR_DEVICE_ATTR_RO(fan3_input, rpm, 2);
अटल SENSOR_DEVICE_ATTR_RO(fan4_input, rpm, 3);
अटल SENSOR_DEVICE_ATTR_RO(fan5_input, rpm, 4);
अटल SENSOR_DEVICE_ATTR_RO(fan6_input, rpm, 5);
अटल SENSOR_DEVICE_ATTR_RO(fan7_input, rpm, 6);
अटल SENSOR_DEVICE_ATTR_RO(fan8_input, rpm, 7);
अटल SENSOR_DEVICE_ATTR_RO(fan9_input, rpm, 8);
अटल SENSOR_DEVICE_ATTR_RO(fan10_input, rpm, 9);
अटल SENSOR_DEVICE_ATTR_RO(fan11_input, rpm, 10);
अटल SENSOR_DEVICE_ATTR_RO(fan12_input, rpm, 11);
अटल SENSOR_DEVICE_ATTR_RO(fan13_input, rpm, 12);
अटल SENSOR_DEVICE_ATTR_RO(fan14_input, rpm, 13);
अटल SENSOR_DEVICE_ATTR_RO(fan15_input, rpm, 14);
अटल SENSOR_DEVICE_ATTR_RO(fan16_input, rpm, 15);
अटल काष्ठा attribute *fan_dev_attrs[] = अणु
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan3_input.dev_attr.attr,
	&sensor_dev_attr_fan4_input.dev_attr.attr,
	&sensor_dev_attr_fan5_input.dev_attr.attr,
	&sensor_dev_attr_fan6_input.dev_attr.attr,
	&sensor_dev_attr_fan7_input.dev_attr.attr,
	&sensor_dev_attr_fan8_input.dev_attr.attr,
	&sensor_dev_attr_fan9_input.dev_attr.attr,
	&sensor_dev_attr_fan10_input.dev_attr.attr,
	&sensor_dev_attr_fan11_input.dev_attr.attr,
	&sensor_dev_attr_fan12_input.dev_attr.attr,
	&sensor_dev_attr_fan13_input.dev_attr.attr,
	&sensor_dev_attr_fan14_input.dev_attr.attr,
	&sensor_dev_attr_fan15_input.dev_attr.attr,
	&sensor_dev_attr_fan16_input.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group fan_dev_group = अणु
	.attrs = fan_dev_attrs,
	.is_visible = fan_dev_is_visible,
पूर्ण;

/*
 * The घड़ी type is type M :
 * The PWM frequency = 24MHz / (type M घड़ी भागision L bit *
 * type M घड़ी भागision H bit * (type M PWM period bit + 1))
 */
अटल व्योम aspeed_create_type(काष्ठा aspeed_pwm_tacho_data *priv)
अणु
	priv->type_pwm_घड़ी_भागision_h[TYPEM] = M_PWM_DIV_H;
	priv->type_pwm_घड़ी_भागision_l[TYPEM] = M_PWM_DIV_L;
	priv->type_pwm_घड़ी_unit[TYPEM] = M_PWM_PERIOD;
	aspeed_set_pwm_घड़ी_values(priv->regmap, TYPEM, M_PWM_DIV_H,
				    M_PWM_DIV_L, M_PWM_PERIOD);
	aspeed_set_tacho_type_enable(priv->regmap, TYPEM, true);
	priv->type_fan_tach_घड़ी_भागision[TYPEM] = M_TACH_CLK_DIV;
	priv->type_fan_tach_unit[TYPEM] = M_TACH_UNIT;
	priv->type_fan_tach_mode[TYPEM] = M_TACH_MODE;
	aspeed_set_tacho_type_values(priv->regmap, TYPEM, M_TACH_MODE,
				     M_TACH_UNIT, M_TACH_CLK_DIV);
पूर्ण

अटल व्योम aspeed_create_pwm_port(काष्ठा aspeed_pwm_tacho_data *priv,
				   u8 pwm_port)
अणु
	aspeed_set_pwm_port_enable(priv->regmap, pwm_port, true);
	priv->pwm_present[pwm_port] = true;

	priv->pwm_port_type[pwm_port] = TYPEM;
	aspeed_set_pwm_port_type(priv->regmap, pwm_port, TYPEM);

	priv->pwm_port_fan_ctrl[pwm_port] = INIT_FAN_CTRL;
	aspeed_set_pwm_port_fan_ctrl(priv, pwm_port, INIT_FAN_CTRL);
पूर्ण

अटल व्योम aspeed_create_fan_tach_channel(काष्ठा aspeed_pwm_tacho_data *priv,
					   u8 *fan_tach_ch,
					   पूर्णांक count,
					   u8 pwm_source)
अणु
	u8 val, index;

	क्रम (val = 0; val < count; val++) अणु
		index = fan_tach_ch[val];
		aspeed_set_fan_tach_ch_enable(priv->regmap, index, true);
		priv->fan_tach_present[index] = true;
		priv->fan_tach_ch_source[index] = pwm_source;
		aspeed_set_fan_tach_ch_source(priv->regmap, index, pwm_source);
	पूर्ण
पूर्ण

अटल पूर्णांक
aspeed_pwm_cz_get_max_state(काष्ठा thermal_cooling_device *tcdev,
			    अचिन्हित दीर्घ *state)
अणु
	काष्ठा aspeed_cooling_device *cdev = tcdev->devdata;

	*state = cdev->max_state;

	वापस 0;
पूर्ण

अटल पूर्णांक
aspeed_pwm_cz_get_cur_state(काष्ठा thermal_cooling_device *tcdev,
			    अचिन्हित दीर्घ *state)
अणु
	काष्ठा aspeed_cooling_device *cdev = tcdev->devdata;

	*state = cdev->cur_state;

	वापस 0;
पूर्ण

अटल पूर्णांक
aspeed_pwm_cz_set_cur_state(काष्ठा thermal_cooling_device *tcdev,
			    अचिन्हित दीर्घ state)
अणु
	काष्ठा aspeed_cooling_device *cdev = tcdev->devdata;

	अगर (state > cdev->max_state)
		वापस -EINVAL;

	cdev->cur_state = state;
	cdev->priv->pwm_port_fan_ctrl[cdev->pwm_port] =
					cdev->cooling_levels[cdev->cur_state];
	aspeed_set_pwm_port_fan_ctrl(cdev->priv, cdev->pwm_port,
				     cdev->cooling_levels[cdev->cur_state]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_cooling_device_ops aspeed_pwm_cool_ops = अणु
	.get_max_state = aspeed_pwm_cz_get_max_state,
	.get_cur_state = aspeed_pwm_cz_get_cur_state,
	.set_cur_state = aspeed_pwm_cz_set_cur_state,
पूर्ण;

अटल पूर्णांक aspeed_create_pwm_cooling(काष्ठा device *dev,
				     काष्ठा device_node *child,
				     काष्ठा aspeed_pwm_tacho_data *priv,
				     u32 pwm_port, u8 num_levels)
अणु
	पूर्णांक ret;
	काष्ठा aspeed_cooling_device *cdev;

	cdev = devm_kzalloc(dev, माप(*cdev), GFP_KERNEL);

	अगर (!cdev)
		वापस -ENOMEM;

	cdev->cooling_levels = devm_kzalloc(dev, num_levels, GFP_KERNEL);
	अगर (!cdev->cooling_levels)
		वापस -ENOMEM;

	cdev->max_state = num_levels - 1;
	ret = of_property_पढ़ो_u8_array(child, "cooling-levels",
					cdev->cooling_levels,
					num_levels);
	अगर (ret) अणु
		dev_err(dev, "Property 'cooling-levels' cannot be read.\n");
		वापस ret;
	पूर्ण
	snम_लिखो(cdev->name, MAX_CDEV_NAME_LEN, "%pOFn%d", child, pwm_port);

	cdev->tcdev = devm_thermal_of_cooling_device_रेजिस्टर(dev, child,
					cdev->name, cdev, &aspeed_pwm_cool_ops);
	अगर (IS_ERR(cdev->tcdev))
		वापस PTR_ERR(cdev->tcdev);

	cdev->priv = priv;
	cdev->pwm_port = pwm_port;

	priv->cdev[pwm_port] = cdev;

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_create_fan(काष्ठा device *dev,
			     काष्ठा device_node *child,
			     काष्ठा aspeed_pwm_tacho_data *priv)
अणु
	u8 *fan_tach_ch;
	u32 pwm_port;
	पूर्णांक ret, count;

	ret = of_property_पढ़ो_u32(child, "reg", &pwm_port);
	अगर (ret)
		वापस ret;
	अगर (pwm_port >= ARRAY_SIZE(pwm_port_params))
		वापस -EINVAL;
	aspeed_create_pwm_port(priv, (u8)pwm_port);

	ret = of_property_count_u8_elems(child, "cooling-levels");

	अगर (ret > 0) अणु
		ret = aspeed_create_pwm_cooling(dev, child, priv, pwm_port,
						ret);
		अगर (ret)
			वापस ret;
	पूर्ण

	count = of_property_count_u8_elems(child, "aspeed,fan-tach-ch");
	अगर (count < 1)
		वापस -EINVAL;
	fan_tach_ch = devm_kसुस्मृति(dev, count, माप(*fan_tach_ch),
				   GFP_KERNEL);
	अगर (!fan_tach_ch)
		वापस -ENOMEM;
	ret = of_property_पढ़ो_u8_array(child, "aspeed,fan-tach-ch",
					fan_tach_ch, count);
	अगर (ret)
		वापस ret;
	aspeed_create_fan_tach_channel(priv, fan_tach_ch, count, pwm_port);

	वापस 0;
पूर्ण

अटल व्योम aspeed_pwm_tacho_हटाओ(व्योम *data)
अणु
	काष्ठा aspeed_pwm_tacho_data *priv = data;

	reset_control_निश्चित(priv->rst);
पूर्ण

अटल पूर्णांक aspeed_pwm_tacho_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np, *child;
	काष्ठा aspeed_pwm_tacho_data *priv;
	व्योम __iomem *regs;
	काष्ठा device *hwmon;
	काष्ठा clk *clk;
	पूर्णांक ret;

	np = dev->of_node;
	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);
	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	priv->regmap = devm_regmap_init(dev, शून्य, (__क्रमce व्योम *)regs,
			&aspeed_pwm_tacho_regmap_config);
	अगर (IS_ERR(priv->regmap))
		वापस PTR_ERR(priv->regmap);

	priv->rst = devm_reset_control_get_exclusive(dev, शून्य);
	अगर (IS_ERR(priv->rst)) अणु
		dev_err(dev,
			"missing or invalid reset controller device tree entry");
		वापस PTR_ERR(priv->rst);
	पूर्ण
	reset_control_deनिश्चित(priv->rst);

	ret = devm_add_action_or_reset(dev, aspeed_pwm_tacho_हटाओ, priv);
	अगर (ret)
		वापस ret;

	regmap_ग_लिखो(priv->regmap, ASPEED_PTCR_TACH_SOURCE, 0);
	regmap_ग_लिखो(priv->regmap, ASPEED_PTCR_TACH_SOURCE_EXT, 0);

	clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(clk))
		वापस -ENODEV;
	priv->clk_freq = clk_get_rate(clk);
	aspeed_set_घड़ी_enable(priv->regmap, true);
	aspeed_set_घड़ी_source(priv->regmap, 0);

	aspeed_create_type(priv);

	क्रम_each_child_of_node(np, child) अणु
		ret = aspeed_create_fan(dev, child, priv);
		अगर (ret) अणु
			of_node_put(child);
			वापस ret;
		पूर्ण
	पूर्ण

	priv->groups[0] = &pwm_dev_group;
	priv->groups[1] = &fan_dev_group;
	priv->groups[2] = शून्य;
	hwmon = devm_hwmon_device_रेजिस्टर_with_groups(dev,
						       "aspeed_pwm_tacho",
						       priv, priv->groups);
	वापस PTR_ERR_OR_ZERO(hwmon);
पूर्ण

अटल स्थिर काष्ठा of_device_id of_pwm_tacho_match_table[] = अणु
	अणु .compatible = "aspeed,ast2400-pwm-tacho", पूर्ण,
	अणु .compatible = "aspeed,ast2500-pwm-tacho", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_pwm_tacho_match_table);

अटल काष्ठा platक्रमm_driver aspeed_pwm_tacho_driver = अणु
	.probe		= aspeed_pwm_tacho_probe,
	.driver		= अणु
		.name	= "aspeed_pwm_tacho",
		.of_match_table = of_pwm_tacho_match_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(aspeed_pwm_tacho_driver);

MODULE_AUTHOR("Jaghathiswari Rankappagounder Natarajan <jaghu@google.com>");
MODULE_DESCRIPTION("ASPEED PWM and Fan Tacho device driver");
MODULE_LICENSE("GPL");
