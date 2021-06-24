<शैली गुरु>
/*
 * linux/mfd/tps65218.h
 *
 * Functions to access TPS65219 घातer management chip.
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - https://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether expressed or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 क्रम more details.
 */

#अगर_अघोषित __LINUX_MFD_TPS65218_H
#घोषणा __LINUX_MFD_TPS65218_H

#समावेश <linux/i2c.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/bitops.h>

/* TPS chip id list */
#घोषणा TPS65218			0xF0

/* I2C ID क्रम TPS65218 part */
#घोषणा TPS65218_I2C_ID			0x24

/* All रेजिस्टर addresses */
#घोषणा TPS65218_REG_CHIPID		0x00
#घोषणा TPS65218_REG_INT1		0x01
#घोषणा TPS65218_REG_INT2		0x02
#घोषणा TPS65218_REG_INT_MASK1		0x03
#घोषणा TPS65218_REG_INT_MASK2		0x04
#घोषणा TPS65218_REG_STATUS		0x05
#घोषणा TPS65218_REG_CONTROL		0x06
#घोषणा TPS65218_REG_FLAG		0x07

#घोषणा TPS65218_REG_PASSWORD		0x10
#घोषणा TPS65218_REG_ENABLE1		0x11
#घोषणा TPS65218_REG_ENABLE2		0x12
#घोषणा TPS65218_REG_CONFIG1		0x13
#घोषणा TPS65218_REG_CONFIG2		0x14
#घोषणा TPS65218_REG_CONFIG3		0x15
#घोषणा TPS65218_REG_CONTROL_DCDC1	0x16
#घोषणा TPS65218_REG_CONTROL_DCDC2	0x17
#घोषणा TPS65218_REG_CONTROL_DCDC3	0x18
#घोषणा TPS65218_REG_CONTROL_DCDC4	0x19
#घोषणा TPS65218_REG_CONTRL_SLEW_RATE	0x1A
#घोषणा TPS65218_REG_CONTROL_LDO1	0x1B
#घोषणा TPS65218_REG_SEQ1		0x20
#घोषणा TPS65218_REG_SEQ2		0x21
#घोषणा TPS65218_REG_SEQ3		0x22
#घोषणा TPS65218_REG_SEQ4		0x23
#घोषणा TPS65218_REG_SEQ5		0x24
#घोषणा TPS65218_REG_SEQ6		0x25
#घोषणा TPS65218_REG_SEQ7		0x26

/* Register field definitions */
#घोषणा TPS65218_CHIPID_CHIP_MASK	0xF8
#घोषणा TPS65218_CHIPID_REV_MASK	0x07

#घोषणा TPS65218_REV_1_0		0x0
#घोषणा TPS65218_REV_1_1		0x1
#घोषणा TPS65218_REV_2_0		0x2
#घोषणा TPS65218_REV_2_1		0x3

#घोषणा TPS65218_INT1_VPRG		BIT(5)
#घोषणा TPS65218_INT1_AC		BIT(4)
#घोषणा TPS65218_INT1_PB		BIT(3)
#घोषणा TPS65218_INT1_HOT		BIT(2)
#घोषणा TPS65218_INT1_CC_AQC		BIT(1)
#घोषणा TPS65218_INT1_PRGC		BIT(0)

#घोषणा TPS65218_INT2_LS3_F		BIT(5)
#घोषणा TPS65218_INT2_LS2_F		BIT(4)
#घोषणा TPS65218_INT2_LS1_F		BIT(3)
#घोषणा TPS65218_INT2_LS3_I		BIT(2)
#घोषणा TPS65218_INT2_LS2_I		BIT(1)
#घोषणा TPS65218_INT2_LS1_I		BIT(0)

#घोषणा TPS65218_INT_MASK1_VPRG		BIT(5)
#घोषणा TPS65218_INT_MASK1_AC		BIT(4)
#घोषणा TPS65218_INT_MASK1_PB		BIT(3)
#घोषणा TPS65218_INT_MASK1_HOT		BIT(2)
#घोषणा TPS65218_INT_MASK1_CC_AQC	BIT(1)
#घोषणा TPS65218_INT_MASK1_PRGC		BIT(0)

#घोषणा TPS65218_INT_MASK2_LS3_F	BIT(5)
#घोषणा TPS65218_INT_MASK2_LS2_F	BIT(4)
#घोषणा TPS65218_INT_MASK2_LS1_F	BIT(3)
#घोषणा TPS65218_INT_MASK2_LS3_I	BIT(2)
#घोषणा TPS65218_INT_MASK2_LS2_I	BIT(1)
#घोषणा TPS65218_INT_MASK2_LS1_I	BIT(0)

#घोषणा TPS65218_STATUS_FSEAL		BIT(7)
#घोषणा TPS65218_STATUS_EE		BIT(6)
#घोषणा TPS65218_STATUS_AC_STATE	BIT(5)
#घोषणा TPS65218_STATUS_PB_STATE	BIT(4)
#घोषणा TPS65218_STATUS_STATE_MASK	0xC
#घोषणा TPS65218_STATUS_CC_STAT		0x3

#घोषणा TPS65218_CONTROL_OFFNPFO	BIT(1)
#घोषणा TPS65218_CONTROL_CC_AQ	BIT(0)

#घोषणा TPS65218_FLAG_GPO3_FLG		BIT(7)
#घोषणा TPS65218_FLAG_GPO2_FLG		BIT(6)
#घोषणा TPS65218_FLAG_GPO1_FLG		BIT(5)
#घोषणा TPS65218_FLAG_LDO1_FLG		BIT(4)
#घोषणा TPS65218_FLAG_DC4_FLG		BIT(3)
#घोषणा TPS65218_FLAG_DC3_FLG		BIT(2)
#घोषणा TPS65218_FLAG_DC2_FLG		BIT(1)
#घोषणा TPS65218_FLAG_DC1_FLG		BIT(0)

#घोषणा TPS65218_ENABLE1_DC6_EN		BIT(5)
#घोषणा TPS65218_ENABLE1_DC5_EN		BIT(4)
#घोषणा TPS65218_ENABLE1_DC4_EN		BIT(3)
#घोषणा TPS65218_ENABLE1_DC3_EN		BIT(2)
#घोषणा TPS65218_ENABLE1_DC2_EN		BIT(1)
#घोषणा TPS65218_ENABLE1_DC1_EN		BIT(0)

#घोषणा TPS65218_ENABLE2_GPIO3		BIT(6)
#घोषणा TPS65218_ENABLE2_GPIO2		BIT(5)
#घोषणा TPS65218_ENABLE2_GPIO1		BIT(4)
#घोषणा TPS65218_ENABLE2_LS3_EN		BIT(3)
#घोषणा TPS65218_ENABLE2_LS2_EN		BIT(2)
#घोषणा TPS65218_ENABLE2_LS1_EN		BIT(1)
#घोषणा TPS65218_ENABLE2_LDO1_EN	BIT(0)


#घोषणा TPS65218_CONFIG1_TRST		BIT(7)
#घोषणा TPS65218_CONFIG1_GPO2_BUF	BIT(6)
#घोषणा TPS65218_CONFIG1_IO1_SEL	BIT(5)
#घोषणा TPS65218_CONFIG1_PGDLY_MASK	0x18
#घोषणा TPS65218_CONFIG1_STRICT		BIT(2)
#घोषणा TPS65218_CONFIG1_UVLO_MASK	0x3
#घोषणा TPS65218_CONFIG1_UVLO_2750000	0x0
#घोषणा TPS65218_CONFIG1_UVLO_2950000	0x1
#घोषणा TPS65218_CONFIG1_UVLO_3250000	0x2
#घोषणा TPS65218_CONFIG1_UVLO_3350000	0x3

#घोषणा TPS65218_CONFIG2_DC12_RST	BIT(7)
#घोषणा TPS65218_CONFIG2_UVLOHYS	BIT(6)
#घोषणा TPS65218_CONFIG2_LS3ILIM_MASK	0xC
#घोषणा TPS65218_CONFIG2_LS2ILIM_MASK	0x3

#घोषणा TPS65218_CONFIG3_LS3NPFO	BIT(5)
#घोषणा TPS65218_CONFIG3_LS2NPFO	BIT(4)
#घोषणा TPS65218_CONFIG3_LS1NPFO	BIT(3)
#घोषणा TPS65218_CONFIG3_LS3DCHRG	BIT(2)
#घोषणा TPS65218_CONFIG3_LS2DCHRG	BIT(1)
#घोषणा TPS65218_CONFIG3_LS1DCHRG	BIT(0)

#घोषणा TPS65218_CONTROL_DCDC1_PFM	BIT(7)
#घोषणा TPS65218_CONTROL_DCDC1_MASK	0x7F

#घोषणा TPS65218_CONTROL_DCDC2_PFM	BIT(7)
#घोषणा TPS65218_CONTROL_DCDC2_MASK	0x3F

#घोषणा TPS65218_CONTROL_DCDC3_PFM	BIT(7)
#घोषणा TPS65218_CONTROL_DCDC3_MASK	0x3F

#घोषणा TPS65218_CONTROL_DCDC4_PFM	BIT(7)
#घोषणा TPS65218_CONTROL_DCDC4_MASK	0x3F

#घोषणा TPS65218_SLEW_RATE_GO		BIT(7)
#घोषणा TPS65218_SLEW_RATE_GODSBL	BIT(6)
#घोषणा TPS65218_SLEW_RATE_SLEW_MASK	0x7

#घोषणा TPS65218_CONTROL_LDO1_MASK	0x3F

#घोषणा TPS65218_SEQ1_DLY8		BIT(7)
#घोषणा TPS65218_SEQ1_DLY7		BIT(6)
#घोषणा TPS65218_SEQ1_DLY6		BIT(5)
#घोषणा TPS65218_SEQ1_DLY5		BIT(4)
#घोषणा TPS65218_SEQ1_DLY4		BIT(3)
#घोषणा TPS65218_SEQ1_DLY3		BIT(2)
#घोषणा TPS65218_SEQ1_DLY2		BIT(1)
#घोषणा TPS65218_SEQ1_DLY1		BIT(0)

#घोषणा TPS65218_SEQ2_DLYFCTR		BIT(7)
#घोषणा TPS65218_SEQ2_DLY9		BIT(0)

#घोषणा TPS65218_SEQ3_DC2_SEQ_MASK	0xF0
#घोषणा TPS65218_SEQ3_DC1_SEQ_MASK	0xF

#घोषणा TPS65218_SEQ4_DC4_SEQ_MASK	0xF0
#घोषणा TPS65218_SEQ4_DC3_SEQ_MASK	0xF

#घोषणा TPS65218_SEQ5_DC6_SEQ_MASK	0xF0
#घोषणा TPS65218_SEQ5_DC5_SEQ_MASK	0xF

#घोषणा TPS65218_SEQ6_LS1_SEQ_MASK	0xF0
#घोषणा TPS65218_SEQ6_LDO1_SEQ_MASK	0xF

#घोषणा TPS65218_SEQ7_GPO3_SEQ_MASK	0xF0
#घोषणा TPS65218_SEQ7_GPO1_SEQ_MASK	0xF
#घोषणा TPS65218_PROTECT_NONE		0
#घोषणा TPS65218_PROTECT_L1		1

क्रमागत tps65218_regulator_id अणु
	/* DCDC's */
	TPS65218_DCDC_1,
	TPS65218_DCDC_2,
	TPS65218_DCDC_3,
	TPS65218_DCDC_4,
	TPS65218_DCDC_5,
	TPS65218_DCDC_6,
	/* LDOs */
	TPS65218_LDO_1,
	/* LS's */
	TPS65218_LS_2,
	TPS65218_LS_3,
पूर्ण;

#घोषणा TPS65218_MAX_REG_ID		TPS65218_LDO_1

/* Number of step-करोwn converters available */
#घोषणा TPS65218_NUM_DCDC		6
/* Number of LDO voltage regulators available */
#घोषणा TPS65218_NUM_LDO		1
/* Number of total LS current regulators available */
#घोषणा TPS65218_NUM_LS			2
/* Number of total regulators available */
#घोषणा TPS65218_NUM_REGULATOR		(TPS65218_NUM_DCDC + TPS65218_NUM_LDO \
					 + TPS65218_NUM_LS)

/* Define the TPS65218 IRQ numbers */
क्रमागत tps65218_irqs अणु
	/* INT1 रेजिस्टरs */
	TPS65218_PRGC_IRQ,
	TPS65218_CC_AQC_IRQ,
	TPS65218_HOT_IRQ,
	TPS65218_PB_IRQ,
	TPS65218_AC_IRQ,
	TPS65218_VPRG_IRQ,
	TPS65218_INVALID1_IRQ,
	TPS65218_INVALID2_IRQ,
	/* INT2 रेजिस्टरs */
	TPS65218_LS1_I_IRQ,
	TPS65218_LS2_I_IRQ,
	TPS65218_LS3_I_IRQ,
	TPS65218_LS1_F_IRQ,
	TPS65218_LS2_F_IRQ,
	TPS65218_LS3_F_IRQ,
	TPS65218_INVALID3_IRQ,
	TPS65218_INVALID4_IRQ,
पूर्ण;

/**
 * काष्ठा tps65218 - tps65218 sub-driver chip access routines
 *
 * Device data may be used to access the TPS65218 chip
 */

काष्ठा tps65218 अणु
	काष्ठा device *dev;
	अचिन्हित पूर्णांक id;
	u8 rev;

	काष्ठा mutex tps_lock;		/* lock guarding the data काष्ठाure */
	/* IRQ Data */
	पूर्णांक irq;
	u32 irq_mask;
	काष्ठा regmap_irq_chip_data *irq_data;
	काष्ठा regulator_desc desc[TPS65218_NUM_REGULATOR];
	काष्ठा regmap *regmap;
	u8 *strobes;
पूर्ण;

पूर्णांक tps65218_reg_ग_लिखो(काष्ठा tps65218 *tps, अचिन्हित पूर्णांक reg,
			अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक level);
पूर्णांक tps65218_set_bits(काष्ठा tps65218 *tps, अचिन्हित पूर्णांक reg,
		अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक level);
पूर्णांक tps65218_clear_bits(काष्ठा tps65218 *tps, अचिन्हित पूर्णांक reg,
		अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक level);

#पूर्ण_अगर /*  __LINUX_MFD_TPS65218_H */
