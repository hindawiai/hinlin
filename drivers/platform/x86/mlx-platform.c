<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*
 * Mellanox platक्रमm driver
 *
 * Copyright (C) 2016-2018 Mellanox Technologies
 * Copyright (C) 2016-2018 Vadim Pasternak <vadimp@mellanox.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/dmi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-mux.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/i2c-mux-reg.h>
#समावेश <linux/platक्रमm_data/mlxreg.h>
#समावेश <linux/regmap.h>

#घोषणा MLX_PLAT_DEVICE_NAME		"mlxplat"

/* LPC bus IO offsets */
#घोषणा MLXPLAT_CPLD_LPC_I2C_BASE_ADRR		0x2000
#घोषणा MLXPLAT_CPLD_LPC_REG_BASE_ADRR		0x2500
#घोषणा MLXPLAT_CPLD_LPC_REG_CPLD1_VER_OFFSET	0x00
#घोषणा MLXPLAT_CPLD_LPC_REG_CPLD2_VER_OFFSET	0x01
#घोषणा MLXPLAT_CPLD_LPC_REG_CPLD3_VER_OFFSET	0x02
#घोषणा MLXPLAT_CPLD_LPC_REG_CPLD4_VER_OFFSET	0x03
#घोषणा MLXPLAT_CPLD_LPC_REG_CPLD1_PN_OFFSET	0x04
#घोषणा MLXPLAT_CPLD_LPC_REG_CPLD2_PN_OFFSET	0x06
#घोषणा MLXPLAT_CPLD_LPC_REG_CPLD3_PN_OFFSET	0x08
#घोषणा MLXPLAT_CPLD_LPC_REG_CPLD4_PN_OFFSET	0x0a
#घोषणा MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET	0x1d
#घोषणा MLXPLAT_CPLD_LPC_REG_RST_CAUSE1_OFFSET	0x1e
#घोषणा MLXPLAT_CPLD_LPC_REG_RST_CAUSE2_OFFSET	0x1f
#घोषणा MLXPLAT_CPLD_LPC_REG_LED1_OFFSET	0x20
#घोषणा MLXPLAT_CPLD_LPC_REG_LED2_OFFSET	0x21
#घोषणा MLXPLAT_CPLD_LPC_REG_LED3_OFFSET	0x22
#घोषणा MLXPLAT_CPLD_LPC_REG_LED4_OFFSET	0x23
#घोषणा MLXPLAT_CPLD_LPC_REG_LED5_OFFSET	0x24
#घोषणा MLXPLAT_CPLD_LPC_REG_FAN_सूचीECTION	0x2a
#घोषणा MLXPLAT_CPLD_LPC_REG_GP0_RO_OFFSET	0x2b
#घोषणा MLXPLAT_CPLD_LPC_REG_GP0_OFFSET		0x2e
#घोषणा MLXPLAT_CPLD_LPC_REG_GP1_OFFSET		0x30
#घोषणा MLXPLAT_CPLD_LPC_REG_WP1_OFFSET		0x31
#घोषणा MLXPLAT_CPLD_LPC_REG_GP2_OFFSET		0x32
#घोषणा MLXPLAT_CPLD_LPC_REG_WP2_OFFSET		0x33
#घोषणा MLXPLAT_CPLD_LPC_REG_PWM_CONTROL_OFFSET	0x37
#घोषणा MLXPLAT_CPLD_LPC_REG_AGGR_OFFSET	0x3a
#घोषणा MLXPLAT_CPLD_LPC_REG_AGGR_MASK_OFFSET	0x3b
#घोषणा MLXPLAT_CPLD_LPC_REG_AGGRLO_OFFSET	0x40
#घोषणा MLXPLAT_CPLD_LPC_REG_AGGRLO_MASK_OFFSET	0x41
#घोषणा MLXPLAT_CPLD_LPC_REG_AGGRCO_OFFSET	0x42
#घोषणा MLXPLAT_CPLD_LPC_REG_AGGRCO_MASK_OFFSET	0x43
#घोषणा MLXPLAT_CPLD_LPC_REG_AGGRCX_OFFSET	0x44
#घोषणा MLXPLAT_CPLD_LPC_REG_AGGRCX_MASK_OFFSET 0x45
#घोषणा MLXPLAT_CPLD_LPC_REG_ASIC_HEALTH_OFFSET 0x50
#घोषणा MLXPLAT_CPLD_LPC_REG_ASIC_EVENT_OFFSET	0x51
#घोषणा MLXPLAT_CPLD_LPC_REG_ASIC_MASK_OFFSET	0x52
#घोषणा MLXPLAT_CPLD_LPC_REG_PSU_OFFSET		0x58
#घोषणा MLXPLAT_CPLD_LPC_REG_PSU_EVENT_OFFSET	0x59
#घोषणा MLXPLAT_CPLD_LPC_REG_PSU_MASK_OFFSET	0x5a
#घोषणा MLXPLAT_CPLD_LPC_REG_PWR_OFFSET		0x64
#घोषणा MLXPLAT_CPLD_LPC_REG_PWR_EVENT_OFFSET	0x65
#घोषणा MLXPLAT_CPLD_LPC_REG_PWR_MASK_OFFSET	0x66
#घोषणा MLXPLAT_CPLD_LPC_REG_FAN_OFFSET		0x88
#घोषणा MLXPLAT_CPLD_LPC_REG_FAN_EVENT_OFFSET	0x89
#घोषणा MLXPLAT_CPLD_LPC_REG_FAN_MASK_OFFSET	0x8a
#घोषणा MLXPLAT_CPLD_LPC_REG_WD_CLEAR_OFFSET	0xc7
#घोषणा MLXPLAT_CPLD_LPC_REG_WD_CLEAR_WP_OFFSET	0xc8
#घोषणा MLXPLAT_CPLD_LPC_REG_WD1_TMR_OFFSET	0xc9
#घोषणा MLXPLAT_CPLD_LPC_REG_WD1_ACT_OFFSET	0xcb
#घोषणा MLXPLAT_CPLD_LPC_REG_WD2_TMR_OFFSET	0xcd
#घोषणा MLXPLAT_CPLD_LPC_REG_WD2_TLEFT_OFFSET	0xce
#घोषणा MLXPLAT_CPLD_LPC_REG_WD2_ACT_OFFSET	0xcf
#घोषणा MLXPLAT_CPLD_LPC_REG_WD3_TMR_OFFSET	0xd1
#घोषणा MLXPLAT_CPLD_LPC_REG_WD3_TLEFT_OFFSET	0xd2
#घोषणा MLXPLAT_CPLD_LPC_REG_WD3_ACT_OFFSET	0xd3
#घोषणा MLXPLAT_CPLD_LPC_REG_CPLD1_MVER_OFFSET	0xde
#घोषणा MLXPLAT_CPLD_LPC_REG_CPLD2_MVER_OFFSET	0xdf
#घोषणा MLXPLAT_CPLD_LPC_REG_CPLD3_MVER_OFFSET	0xe0
#घोषणा MLXPLAT_CPLD_LPC_REG_CPLD4_MVER_OFFSET	0xe1
#घोषणा MLXPLAT_CPLD_LPC_REG_UFM_VERSION_OFFSET	0xe2
#घोषणा MLXPLAT_CPLD_LPC_REG_PWM1_OFFSET	0xe3
#घोषणा MLXPLAT_CPLD_LPC_REG_TACHO1_OFFSET	0xe4
#घोषणा MLXPLAT_CPLD_LPC_REG_TACHO2_OFFSET	0xe5
#घोषणा MLXPLAT_CPLD_LPC_REG_TACHO3_OFFSET	0xe6
#घोषणा MLXPLAT_CPLD_LPC_REG_TACHO4_OFFSET	0xe7
#घोषणा MLXPLAT_CPLD_LPC_REG_TACHO5_OFFSET	0xe8
#घोषणा MLXPLAT_CPLD_LPC_REG_TACHO6_OFFSET	0xe9
#घोषणा MLXPLAT_CPLD_LPC_REG_TACHO7_OFFSET	0xeb
#घोषणा MLXPLAT_CPLD_LPC_REG_TACHO8_OFFSET	0xec
#घोषणा MLXPLAT_CPLD_LPC_REG_TACHO9_OFFSET	0xed
#घोषणा MLXPLAT_CPLD_LPC_REG_TACHO10_OFFSET	0xee
#घोषणा MLXPLAT_CPLD_LPC_REG_TACHO11_OFFSET	0xef
#घोषणा MLXPLAT_CPLD_LPC_REG_TACHO12_OFFSET	0xf0
#घोषणा MLXPLAT_CPLD_LPC_REG_FAN_CAP1_OFFSET	0xf5
#घोषणा MLXPLAT_CPLD_LPC_REG_FAN_CAP2_OFFSET	0xf6
#घोषणा MLXPLAT_CPLD_LPC_REG_FAN_DRW_CAP_OFFSET	0xf7
#घोषणा MLXPLAT_CPLD_LPC_REG_TACHO_SPEED_OFFSET	0xf8
#घोषणा MLXPLAT_CPLD_LPC_REG_PSU_I2C_CAP_OFFSET 0xf9
#घोषणा MLXPLAT_CPLD_LPC_REG_CONFIG1_OFFSET	0xfb
#घोषणा MLXPLAT_CPLD_LPC_REG_CONFIG2_OFFSET	0xfc
#घोषणा MLXPLAT_CPLD_LPC_IO_RANGE		0x100
#घोषणा MLXPLAT_CPLD_LPC_I2C_CH1_OFF		0xdb
#घोषणा MLXPLAT_CPLD_LPC_I2C_CH2_OFF		0xda
#घोषणा MLXPLAT_CPLD_LPC_I2C_CH3_OFF		0xdc

#घोषणा MLXPLAT_CPLD_LPC_PIO_OFFSET		0x10000UL
#घोषणा MLXPLAT_CPLD_LPC_REG1	((MLXPLAT_CPLD_LPC_REG_BASE_ADRR + \
				  MLXPLAT_CPLD_LPC_I2C_CH1_OFF) | \
				  MLXPLAT_CPLD_LPC_PIO_OFFSET)
#घोषणा MLXPLAT_CPLD_LPC_REG2	((MLXPLAT_CPLD_LPC_REG_BASE_ADRR + \
				  MLXPLAT_CPLD_LPC_I2C_CH2_OFF) | \
				  MLXPLAT_CPLD_LPC_PIO_OFFSET)
#घोषणा MLXPLAT_CPLD_LPC_REG3	((MLXPLAT_CPLD_LPC_REG_BASE_ADRR + \
				  MLXPLAT_CPLD_LPC_I2C_CH3_OFF) | \
				  MLXPLAT_CPLD_LPC_PIO_OFFSET)

/* Masks क्रम aggregation, psu, pwr and fan event in CPLD related रेजिस्टरs. */
#घोषणा MLXPLAT_CPLD_AGGR_ASIC_MASK_DEF	0x04
#घोषणा MLXPLAT_CPLD_AGGR_PSU_MASK_DEF	0x08
#घोषणा MLXPLAT_CPLD_AGGR_PWR_MASK_DEF	0x08
#घोषणा MLXPLAT_CPLD_AGGR_FAN_MASK_DEF	0x40
#घोषणा MLXPLAT_CPLD_AGGR_MASK_DEF	(MLXPLAT_CPLD_AGGR_ASIC_MASK_DEF | \
					 MLXPLAT_CPLD_AGGR_PSU_MASK_DEF | \
					 MLXPLAT_CPLD_AGGR_FAN_MASK_DEF)
#घोषणा MLXPLAT_CPLD_AGGR_ASIC_MASK_NG	0x01
#घोषणा MLXPLAT_CPLD_AGGR_MASK_NG_DEF	0x04
#घोषणा MLXPLAT_CPLD_AGGR_MASK_COMEX	BIT(0)
#घोषणा MLXPLAT_CPLD_LOW_AGGR_MASK_LOW	0xc1
#घोषणा MLXPLAT_CPLD_LOW_AGGR_MASK_I2C	BIT(6)
#घोषणा MLXPLAT_CPLD_PSU_MASK		GENMASK(1, 0)
#घोषणा MLXPLAT_CPLD_PWR_MASK		GENMASK(1, 0)
#घोषणा MLXPLAT_CPLD_PSU_EXT_MASK	GENMASK(3, 0)
#घोषणा MLXPLAT_CPLD_PWR_EXT_MASK	GENMASK(3, 0)
#घोषणा MLXPLAT_CPLD_FAN_MASK		GENMASK(3, 0)
#घोषणा MLXPLAT_CPLD_ASIC_MASK		GENMASK(1, 0)
#घोषणा MLXPLAT_CPLD_FAN_NG_MASK	GENMASK(5, 0)
#घोषणा MLXPLAT_CPLD_LED_LO_NIBBLE_MASK	GENMASK(7, 4)
#घोषणा MLXPLAT_CPLD_LED_HI_NIBBLE_MASK	GENMASK(3, 0)
#घोषणा MLXPLAT_CPLD_VOLTREG_UPD_MASK	GENMASK(5, 4)
#घोषणा MLXPLAT_CPLD_I2C_CAP_BIT	0x04
#घोषणा MLXPLAT_CPLD_I2C_CAP_MASK	GENMASK(5, MLXPLAT_CPLD_I2C_CAP_BIT)

/* Masks क्रम aggregation क्रम comex carriers */
#घोषणा MLXPLAT_CPLD_AGGR_MASK_CARRIER	BIT(1)
#घोषणा MLXPLAT_CPLD_AGGR_MASK_CARR_DEF	(MLXPLAT_CPLD_AGGR_ASIC_MASK_DEF | \
					 MLXPLAT_CPLD_AGGR_MASK_CARRIER)
#घोषणा MLXPLAT_CPLD_LOW_AGGRCX_MASK	0xc1

/* Default I2C parent bus number */
#घोषणा MLXPLAT_CPLD_PHYS_ADAPTER_DEF_NR	1

/* Maximum number of possible physical buses equipped on प्रणाली */
#घोषणा MLXPLAT_CPLD_MAX_PHYS_ADAPTER_NUM	16
#घोषणा MLXPLAT_CPLD_MAX_PHYS_EXT_ADAPTER_NUM	24

/* Number of channels in group */
#घोषणा MLXPLAT_CPLD_GRP_CHNL_NUM		8

/* Start channel numbers */
#घोषणा MLXPLAT_CPLD_CH1			2
#घोषणा MLXPLAT_CPLD_CH2			10
#घोषणा MLXPLAT_CPLD_CH3			18

/* Number of LPC attached MUX platक्रमm devices */
#घोषणा MLXPLAT_CPLD_LPC_MUX_DEVS		3

/* Hotplug devices adapter numbers */
#घोषणा MLXPLAT_CPLD_NR_NONE			-1
#घोषणा MLXPLAT_CPLD_PSU_DEFAULT_NR		10
#घोषणा MLXPLAT_CPLD_PSU_MSNXXXX_NR		4
#घोषणा MLXPLAT_CPLD_FAN1_DEFAULT_NR		11
#घोषणा MLXPLAT_CPLD_FAN2_DEFAULT_NR		12
#घोषणा MLXPLAT_CPLD_FAN3_DEFAULT_NR		13
#घोषणा MLXPLAT_CPLD_FAN4_DEFAULT_NR		14

/* Masks and शेष values क्रम watchकरोgs */
#घोषणा MLXPLAT_CPLD_WD1_CLEAR_MASK	GENMASK(7, 1)
#घोषणा MLXPLAT_CPLD_WD2_CLEAR_MASK	(GENMASK(7, 0) & ~BIT(1))

#घोषणा MLXPLAT_CPLD_WD_TYPE1_TO_MASK	GENMASK(7, 4)
#घोषणा MLXPLAT_CPLD_WD_TYPE2_TO_MASK	0
#घोषणा MLXPLAT_CPLD_WD_RESET_ACT_MASK	GENMASK(7, 1)
#घोषणा MLXPLAT_CPLD_WD_FAN_ACT_MASK	(GENMASK(7, 0) & ~BIT(4))
#घोषणा MLXPLAT_CPLD_WD_COUNT_ACT_MASK	(GENMASK(7, 0) & ~BIT(7))
#घोषणा MLXPLAT_CPLD_WD_CPBLTY_MASK	(GENMASK(7, 0) & ~BIT(6))
#घोषणा MLXPLAT_CPLD_WD_DFLT_TIMEOUT	30
#घोषणा MLXPLAT_CPLD_WD3_DFLT_TIMEOUT	600
#घोषणा MLXPLAT_CPLD_WD_MAX_DEVS	2

/* mlxplat_priv - platक्रमm निजी data
 * @pdev_i2c - i2c controller platक्रमm device
 * @pdev_mux - array of mux platक्रमm devices
 * @pdev_hotplug - hotplug platक्रमm devices
 * @pdev_led - led platक्रमm devices
 * @pdev_io_regs - रेजिस्टर access platक्रमm devices
 * @pdev_fan - FAN platक्रमm devices
 * @pdev_wd - array of watchकरोg platक्रमm devices
 * @regmap: device रेजिस्टर map
 */
काष्ठा mlxplat_priv अणु
	काष्ठा platक्रमm_device *pdev_i2c;
	काष्ठा platक्रमm_device *pdev_mux[MLXPLAT_CPLD_LPC_MUX_DEVS];
	काष्ठा platक्रमm_device *pdev_hotplug;
	काष्ठा platक्रमm_device *pdev_led;
	काष्ठा platक्रमm_device *pdev_io_regs;
	काष्ठा platक्रमm_device *pdev_fan;
	काष्ठा platक्रमm_device *pdev_wd[MLXPLAT_CPLD_WD_MAX_DEVS];
	व्योम *regmap;
पूर्ण;

/* Regions क्रम LPC I2C controller and LPC base रेजिस्टर space */
अटल स्थिर काष्ठा resource mlxplat_lpc_resources[] = अणु
	[0] = DEFINE_RES_NAMED(MLXPLAT_CPLD_LPC_I2C_BASE_ADRR,
			       MLXPLAT_CPLD_LPC_IO_RANGE,
			       "mlxplat_cpld_lpc_i2c_ctrl", IORESOURCE_IO),
	[1] = DEFINE_RES_NAMED(MLXPLAT_CPLD_LPC_REG_BASE_ADRR,
			       MLXPLAT_CPLD_LPC_IO_RANGE,
			       "mlxplat_cpld_lpc_regs",
			       IORESOURCE_IO),
पूर्ण;

/* Platक्रमm i2c next generation प्रणालीs data */
अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_i2c_ng_items_data[] = अणु
	अणु
		.reg = MLXPLAT_CPLD_LPC_REG_PSU_I2C_CAP_OFFSET,
		.mask = MLXPLAT_CPLD_I2C_CAP_MASK,
		.bit = MLXPLAT_CPLD_I2C_CAP_BIT,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_item mlxplat_mlxcpld_i2c_ng_items[] = अणु
	अणु
		.data = mlxplat_mlxcpld_i2c_ng_items_data,
	पूर्ण,
पूर्ण;

/* Platक्रमm next generation प्रणालीs i2c data */
अटल काष्ठा mlxreg_core_hotplug_platक्रमm_data mlxplat_mlxcpld_i2c_ng_data = अणु
	.items = mlxplat_mlxcpld_i2c_ng_items,
	.cell = MLXPLAT_CPLD_LPC_REG_AGGR_OFFSET,
	.mask = MLXPLAT_CPLD_AGGR_MASK_COMEX,
	.cell_low = MLXPLAT_CPLD_LPC_REG_AGGRCO_OFFSET,
	.mask_low = MLXPLAT_CPLD_LOW_AGGR_MASK_I2C,
पूर्ण;

/* Platक्रमm शेष channels */
अटल स्थिर पूर्णांक mlxplat_शेष_channels[][MLXPLAT_CPLD_GRP_CHNL_NUM] = अणु
	अणु
		MLXPLAT_CPLD_CH1, MLXPLAT_CPLD_CH1 + 1, MLXPLAT_CPLD_CH1 + 2,
		MLXPLAT_CPLD_CH1 + 3, MLXPLAT_CPLD_CH1 + 4, MLXPLAT_CPLD_CH1 +
		5, MLXPLAT_CPLD_CH1 + 6, MLXPLAT_CPLD_CH1 + 7
	पूर्ण,
	अणु
		MLXPLAT_CPLD_CH2, MLXPLAT_CPLD_CH2 + 1, MLXPLAT_CPLD_CH2 + 2,
		MLXPLAT_CPLD_CH2 + 3, MLXPLAT_CPLD_CH2 + 4, MLXPLAT_CPLD_CH2 +
		5, MLXPLAT_CPLD_CH2 + 6, MLXPLAT_CPLD_CH2 + 7
	पूर्ण,
पूर्ण;

/* Platक्रमm channels क्रम MSN21xx प्रणाली family */
अटल स्थिर पूर्णांक mlxplat_msn21xx_channels[] = अणु 1, 2, 3, 4, 5, 6, 7, 8 पूर्ण;

/* Platक्रमm mux data */
अटल काष्ठा i2c_mux_reg_platक्रमm_data mlxplat_शेष_mux_data[] = अणु
	अणु
		.parent = 1,
		.base_nr = MLXPLAT_CPLD_CH1,
		.ग_लिखो_only = 1,
		.reg = (व्योम __iomem *)MLXPLAT_CPLD_LPC_REG1,
		.reg_size = 1,
		.idle_in_use = 1,
	पूर्ण,
	अणु
		.parent = 1,
		.base_nr = MLXPLAT_CPLD_CH2,
		.ग_लिखो_only = 1,
		.reg = (व्योम __iomem *)MLXPLAT_CPLD_LPC_REG2,
		.reg_size = 1,
		.idle_in_use = 1,
	पूर्ण,

पूर्ण;

/* Platक्रमm mux configuration variables */
अटल पूर्णांक mlxplat_max_adap_num;
अटल पूर्णांक mlxplat_mux_num;
अटल काष्ठा i2c_mux_reg_platक्रमm_data *mlxplat_mux_data;

/* Platक्रमm extended mux data */
अटल काष्ठा i2c_mux_reg_platक्रमm_data mlxplat_extended_mux_data[] = अणु
	अणु
		.parent = 1,
		.base_nr = MLXPLAT_CPLD_CH1,
		.ग_लिखो_only = 1,
		.reg = (व्योम __iomem *)MLXPLAT_CPLD_LPC_REG1,
		.reg_size = 1,
		.idle_in_use = 1,
	पूर्ण,
	अणु
		.parent = 1,
		.base_nr = MLXPLAT_CPLD_CH2,
		.ग_लिखो_only = 1,
		.reg = (व्योम __iomem *)MLXPLAT_CPLD_LPC_REG3,
		.reg_size = 1,
		.idle_in_use = 1,
	पूर्ण,
	अणु
		.parent = 1,
		.base_nr = MLXPLAT_CPLD_CH3,
		.ग_लिखो_only = 1,
		.reg = (व्योम __iomem *)MLXPLAT_CPLD_LPC_REG2,
		.reg_size = 1,
		.idle_in_use = 1,
	पूर्ण,

पूर्ण;

/* Platक्रमm hotplug devices */
अटल काष्ठा i2c_board_info mlxplat_mlxcpld_pwr[] = अणु
	अणु
		I2C_BOARD_INFO("dps460", 0x59),
	पूर्ण,
	अणु
		I2C_BOARD_INFO("dps460", 0x58),
	पूर्ण,
पूर्ण;

अटल काष्ठा i2c_board_info mlxplat_mlxcpld_ext_pwr[] = अणु
	अणु
		I2C_BOARD_INFO("dps460", 0x5b),
	पूर्ण,
	अणु
		I2C_BOARD_INFO("dps460", 0x5a),
	पूर्ण,
पूर्ण;

अटल काष्ठा i2c_board_info mlxplat_mlxcpld_fan[] = अणु
	अणु
		I2C_BOARD_INFO("24c32", 0x50),
	पूर्ण,
	अणु
		I2C_BOARD_INFO("24c32", 0x50),
	पूर्ण,
	अणु
		I2C_BOARD_INFO("24c32", 0x50),
	पूर्ण,
	अणु
		I2C_BOARD_INFO("24c32", 0x50),
	पूर्ण,
पूर्ण;

/* Platक्रमm hotplug comex carrier प्रणाली family data */
अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_comex_psu_items_data[] = अणु
	अणु
		.label = "psu1",
		.reg = MLXPLAT_CPLD_LPC_REG_PSU_OFFSET,
		.mask = BIT(0),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
	अणु
		.label = "psu2",
		.reg = MLXPLAT_CPLD_LPC_REG_PSU_OFFSET,
		.mask = BIT(1),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
पूर्ण;

/* Platक्रमm hotplug शेष data */
अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_शेष_psu_items_data[] = अणु
	अणु
		.label = "psu1",
		.reg = MLXPLAT_CPLD_LPC_REG_PSU_OFFSET,
		.mask = BIT(0),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
	अणु
		.label = "psu2",
		.reg = MLXPLAT_CPLD_LPC_REG_PSU_OFFSET,
		.mask = BIT(1),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_शेष_pwr_items_data[] = अणु
	अणु
		.label = "pwr1",
		.reg = MLXPLAT_CPLD_LPC_REG_PWR_OFFSET,
		.mask = BIT(0),
		.hpdev.brdinfo = &mlxplat_mlxcpld_pwr[0],
		.hpdev.nr = MLXPLAT_CPLD_PSU_DEFAULT_NR,
	पूर्ण,
	अणु
		.label = "pwr2",
		.reg = MLXPLAT_CPLD_LPC_REG_PWR_OFFSET,
		.mask = BIT(1),
		.hpdev.brdinfo = &mlxplat_mlxcpld_pwr[1],
		.hpdev.nr = MLXPLAT_CPLD_PSU_DEFAULT_NR,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_शेष_fan_items_data[] = अणु
	अणु
		.label = "fan1",
		.reg = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
		.mask = BIT(0),
		.hpdev.brdinfo = &mlxplat_mlxcpld_fan[0],
		.hpdev.nr = MLXPLAT_CPLD_FAN1_DEFAULT_NR,
	पूर्ण,
	अणु
		.label = "fan2",
		.reg = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
		.mask = BIT(1),
		.hpdev.brdinfo = &mlxplat_mlxcpld_fan[1],
		.hpdev.nr = MLXPLAT_CPLD_FAN2_DEFAULT_NR,
	पूर्ण,
	अणु
		.label = "fan3",
		.reg = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
		.mask = BIT(2),
		.hpdev.brdinfo = &mlxplat_mlxcpld_fan[2],
		.hpdev.nr = MLXPLAT_CPLD_FAN3_DEFAULT_NR,
	पूर्ण,
	अणु
		.label = "fan4",
		.reg = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
		.mask = BIT(3),
		.hpdev.brdinfo = &mlxplat_mlxcpld_fan[3],
		.hpdev.nr = MLXPLAT_CPLD_FAN4_DEFAULT_NR,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_शेष_asic_items_data[] = अणु
	अणु
		.label = "asic1",
		.reg = MLXPLAT_CPLD_LPC_REG_ASIC_HEALTH_OFFSET,
		.mask = MLXPLAT_CPLD_ASIC_MASK,
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_item mlxplat_mlxcpld_शेष_items[] = अणु
	अणु
		.data = mlxplat_mlxcpld_शेष_psu_items_data,
		.aggr_mask = MLXPLAT_CPLD_AGGR_PSU_MASK_DEF,
		.reg = MLXPLAT_CPLD_LPC_REG_PSU_OFFSET,
		.mask = MLXPLAT_CPLD_PSU_MASK,
		.count = ARRAY_SIZE(mlxplat_mlxcpld_शेष_psu_items_data),
		.inversed = 1,
		.health = false,
	पूर्ण,
	अणु
		.data = mlxplat_mlxcpld_शेष_pwr_items_data,
		.aggr_mask = MLXPLAT_CPLD_AGGR_PWR_MASK_DEF,
		.reg = MLXPLAT_CPLD_LPC_REG_PWR_OFFSET,
		.mask = MLXPLAT_CPLD_PWR_MASK,
		.count = ARRAY_SIZE(mlxplat_mlxcpld_शेष_pwr_items_data),
		.inversed = 0,
		.health = false,
	पूर्ण,
	अणु
		.data = mlxplat_mlxcpld_शेष_fan_items_data,
		.aggr_mask = MLXPLAT_CPLD_AGGR_FAN_MASK_DEF,
		.reg = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
		.mask = MLXPLAT_CPLD_FAN_MASK,
		.count = ARRAY_SIZE(mlxplat_mlxcpld_शेष_fan_items_data),
		.inversed = 1,
		.health = false,
	पूर्ण,
	अणु
		.data = mlxplat_mlxcpld_शेष_asic_items_data,
		.aggr_mask = MLXPLAT_CPLD_AGGR_ASIC_MASK_DEF,
		.reg = MLXPLAT_CPLD_LPC_REG_ASIC_HEALTH_OFFSET,
		.mask = MLXPLAT_CPLD_ASIC_MASK,
		.count = ARRAY_SIZE(mlxplat_mlxcpld_शेष_asic_items_data),
		.inversed = 0,
		.health = true,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_item mlxplat_mlxcpld_comex_items[] = अणु
	अणु
		.data = mlxplat_mlxcpld_comex_psu_items_data,
		.aggr_mask = MLXPLAT_CPLD_AGGR_MASK_CARRIER,
		.reg = MLXPLAT_CPLD_LPC_REG_PSU_OFFSET,
		.mask = MLXPLAT_CPLD_PSU_MASK,
		.count = ARRAY_SIZE(mlxplat_mlxcpld_शेष_psu_items_data),
		.inversed = 1,
		.health = false,
	पूर्ण,
	अणु
		.data = mlxplat_mlxcpld_शेष_pwr_items_data,
		.aggr_mask = MLXPLAT_CPLD_AGGR_MASK_CARRIER,
		.reg = MLXPLAT_CPLD_LPC_REG_PWR_OFFSET,
		.mask = MLXPLAT_CPLD_PWR_MASK,
		.count = ARRAY_SIZE(mlxplat_mlxcpld_शेष_pwr_items_data),
		.inversed = 0,
		.health = false,
	पूर्ण,
	अणु
		.data = mlxplat_mlxcpld_शेष_fan_items_data,
		.aggr_mask = MLXPLAT_CPLD_AGGR_MASK_CARRIER,
		.reg = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
		.mask = MLXPLAT_CPLD_FAN_MASK,
		.count = ARRAY_SIZE(mlxplat_mlxcpld_शेष_fan_items_data),
		.inversed = 1,
		.health = false,
	पूर्ण,
	अणु
		.data = mlxplat_mlxcpld_शेष_asic_items_data,
		.aggr_mask = MLXPLAT_CPLD_AGGR_ASIC_MASK_DEF,
		.reg = MLXPLAT_CPLD_LPC_REG_ASIC_HEALTH_OFFSET,
		.mask = MLXPLAT_CPLD_ASIC_MASK,
		.count = ARRAY_SIZE(mlxplat_mlxcpld_शेष_asic_items_data),
		.inversed = 0,
		.health = true,
	पूर्ण,
पूर्ण;

अटल
काष्ठा mlxreg_core_hotplug_platक्रमm_data mlxplat_mlxcpld_शेष_data = अणु
	.items = mlxplat_mlxcpld_शेष_items,
	.counter = ARRAY_SIZE(mlxplat_mlxcpld_शेष_items),
	.cell = MLXPLAT_CPLD_LPC_REG_AGGR_OFFSET,
	.mask = MLXPLAT_CPLD_AGGR_MASK_DEF,
	.cell_low = MLXPLAT_CPLD_LPC_REG_AGGRLO_OFFSET,
	.mask_low = MLXPLAT_CPLD_LOW_AGGR_MASK_LOW,
पूर्ण;

अटल
काष्ठा mlxreg_core_hotplug_platक्रमm_data mlxplat_mlxcpld_comex_data = अणु
	.items = mlxplat_mlxcpld_comex_items,
	.counter = ARRAY_SIZE(mlxplat_mlxcpld_comex_items),
	.cell = MLXPLAT_CPLD_LPC_REG_AGGR_OFFSET,
	.mask = MLXPLAT_CPLD_AGGR_MASK_CARR_DEF,
	.cell_low = MLXPLAT_CPLD_LPC_REG_AGGRCX_OFFSET,
	.mask_low = MLXPLAT_CPLD_LOW_AGGRCX_MASK,
पूर्ण;

अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_msn21xx_pwr_items_data[] = अणु
	अणु
		.label = "pwr1",
		.reg = MLXPLAT_CPLD_LPC_REG_PWR_OFFSET,
		.mask = BIT(0),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
	अणु
		.label = "pwr2",
		.reg = MLXPLAT_CPLD_LPC_REG_PWR_OFFSET,
		.mask = BIT(1),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
पूर्ण;

/* Platक्रमm hotplug MSN21xx प्रणाली family data */
अटल काष्ठा mlxreg_core_item mlxplat_mlxcpld_msn21xx_items[] = अणु
	अणु
		.data = mlxplat_mlxcpld_msn21xx_pwr_items_data,
		.aggr_mask = MLXPLAT_CPLD_AGGR_PWR_MASK_DEF,
		.reg = MLXPLAT_CPLD_LPC_REG_PWR_OFFSET,
		.mask = MLXPLAT_CPLD_PWR_MASK,
		.count = ARRAY_SIZE(mlxplat_mlxcpld_msn21xx_pwr_items_data),
		.inversed = 0,
		.health = false,
	पूर्ण,
	अणु
		.data = mlxplat_mlxcpld_शेष_asic_items_data,
		.aggr_mask = MLXPLAT_CPLD_AGGR_ASIC_MASK_DEF,
		.reg = MLXPLAT_CPLD_LPC_REG_ASIC_HEALTH_OFFSET,
		.mask = MLXPLAT_CPLD_ASIC_MASK,
		.count = ARRAY_SIZE(mlxplat_mlxcpld_शेष_asic_items_data),
		.inversed = 0,
		.health = true,
	पूर्ण,
पूर्ण;

अटल
काष्ठा mlxreg_core_hotplug_platक्रमm_data mlxplat_mlxcpld_msn21xx_data = अणु
	.items = mlxplat_mlxcpld_msn21xx_items,
	.counter = ARRAY_SIZE(mlxplat_mlxcpld_msn21xx_items),
	.cell = MLXPLAT_CPLD_LPC_REG_AGGR_OFFSET,
	.mask = MLXPLAT_CPLD_AGGR_MASK_DEF,
	.cell_low = MLXPLAT_CPLD_LPC_REG_AGGRLO_OFFSET,
	.mask_low = MLXPLAT_CPLD_LOW_AGGR_MASK_LOW,
पूर्ण;

/* Platक्रमm hotplug msn274x प्रणाली family data */
अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_msn274x_psu_items_data[] = अणु
	अणु
		.label = "psu1",
		.reg = MLXPLAT_CPLD_LPC_REG_PSU_OFFSET,
		.mask = BIT(0),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
	अणु
		.label = "psu2",
		.reg = MLXPLAT_CPLD_LPC_REG_PSU_OFFSET,
		.mask = BIT(1),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_शेष_ng_pwr_items_data[] = अणु
	अणु
		.label = "pwr1",
		.reg = MLXPLAT_CPLD_LPC_REG_PWR_OFFSET,
		.mask = BIT(0),
		.hpdev.brdinfo = &mlxplat_mlxcpld_pwr[0],
		.hpdev.nr = MLXPLAT_CPLD_PSU_MSNXXXX_NR,
	पूर्ण,
	अणु
		.label = "pwr2",
		.reg = MLXPLAT_CPLD_LPC_REG_PWR_OFFSET,
		.mask = BIT(1),
		.hpdev.brdinfo = &mlxplat_mlxcpld_pwr[1],
		.hpdev.nr = MLXPLAT_CPLD_PSU_MSNXXXX_NR,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_msn274x_fan_items_data[] = अणु
	अणु
		.label = "fan1",
		.reg = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
		.mask = BIT(0),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
	अणु
		.label = "fan2",
		.reg = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
		.mask = BIT(1),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
	अणु
		.label = "fan3",
		.reg = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
		.mask = BIT(2),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
	अणु
		.label = "fan4",
		.reg = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
		.mask = BIT(3),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_item mlxplat_mlxcpld_msn274x_items[] = अणु
	अणु
		.data = mlxplat_mlxcpld_msn274x_psu_items_data,
		.aggr_mask = MLXPLAT_CPLD_AGGR_MASK_NG_DEF,
		.reg = MLXPLAT_CPLD_LPC_REG_PSU_OFFSET,
		.mask = MLXPLAT_CPLD_PSU_MASK,
		.count = ARRAY_SIZE(mlxplat_mlxcpld_msn274x_psu_items_data),
		.inversed = 1,
		.health = false,
	पूर्ण,
	अणु
		.data = mlxplat_mlxcpld_शेष_ng_pwr_items_data,
		.aggr_mask = MLXPLAT_CPLD_AGGR_MASK_NG_DEF,
		.reg = MLXPLAT_CPLD_LPC_REG_PWR_OFFSET,
		.mask = MLXPLAT_CPLD_PWR_MASK,
		.count = ARRAY_SIZE(mlxplat_mlxcpld_शेष_ng_pwr_items_data),
		.inversed = 0,
		.health = false,
	पूर्ण,
	अणु
		.data = mlxplat_mlxcpld_msn274x_fan_items_data,
		.aggr_mask = MLXPLAT_CPLD_AGGR_MASK_NG_DEF,
		.reg = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
		.mask = MLXPLAT_CPLD_FAN_MASK,
		.count = ARRAY_SIZE(mlxplat_mlxcpld_msn274x_fan_items_data),
		.inversed = 1,
		.health = false,
	पूर्ण,
	अणु
		.data = mlxplat_mlxcpld_शेष_asic_items_data,
		.aggr_mask = MLXPLAT_CPLD_AGGR_MASK_NG_DEF,
		.reg = MLXPLAT_CPLD_LPC_REG_ASIC_HEALTH_OFFSET,
		.mask = MLXPLAT_CPLD_ASIC_MASK,
		.count = ARRAY_SIZE(mlxplat_mlxcpld_शेष_asic_items_data),
		.inversed = 0,
		.health = true,
	पूर्ण,
पूर्ण;

अटल
काष्ठा mlxreg_core_hotplug_platक्रमm_data mlxplat_mlxcpld_msn274x_data = अणु
	.items = mlxplat_mlxcpld_msn274x_items,
	.counter = ARRAY_SIZE(mlxplat_mlxcpld_msn274x_items),
	.cell = MLXPLAT_CPLD_LPC_REG_AGGR_OFFSET,
	.mask = MLXPLAT_CPLD_AGGR_MASK_NG_DEF,
	.cell_low = MLXPLAT_CPLD_LPC_REG_AGGRLO_OFFSET,
	.mask_low = MLXPLAT_CPLD_LOW_AGGR_MASK_LOW,
पूर्ण;

/* Platक्रमm hotplug MSN201x प्रणाली family data */
अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_msn201x_pwr_items_data[] = अणु
	अणु
		.label = "pwr1",
		.reg = MLXPLAT_CPLD_LPC_REG_PWR_OFFSET,
		.mask = BIT(0),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
	अणु
		.label = "pwr2",
		.reg = MLXPLAT_CPLD_LPC_REG_PWR_OFFSET,
		.mask = BIT(1),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_item mlxplat_mlxcpld_msn201x_items[] = अणु
	अणु
		.data = mlxplat_mlxcpld_msn201x_pwr_items_data,
		.aggr_mask = MLXPLAT_CPLD_AGGR_PWR_MASK_DEF,
		.reg = MLXPLAT_CPLD_LPC_REG_PWR_OFFSET,
		.mask = MLXPLAT_CPLD_PWR_MASK,
		.count = ARRAY_SIZE(mlxplat_mlxcpld_msn201x_pwr_items_data),
		.inversed = 0,
		.health = false,
	पूर्ण,
	अणु
		.data = mlxplat_mlxcpld_शेष_asic_items_data,
		.aggr_mask = MLXPLAT_CPLD_AGGR_ASIC_MASK_DEF,
		.reg = MLXPLAT_CPLD_LPC_REG_ASIC_HEALTH_OFFSET,
		.mask = MLXPLAT_CPLD_ASIC_MASK,
		.count = ARRAY_SIZE(mlxplat_mlxcpld_शेष_asic_items_data),
		.inversed = 0,
		.health = true,
	पूर्ण,
पूर्ण;

अटल
काष्ठा mlxreg_core_hotplug_platक्रमm_data mlxplat_mlxcpld_msn201x_data = अणु
	.items = mlxplat_mlxcpld_msn201x_items,
	.counter = ARRAY_SIZE(mlxplat_mlxcpld_msn201x_items),
	.cell = MLXPLAT_CPLD_LPC_REG_AGGR_OFFSET,
	.mask = MLXPLAT_CPLD_AGGR_MASK_DEF,
	.cell_low = MLXPLAT_CPLD_LPC_REG_AGGRLO_OFFSET,
	.mask_low = MLXPLAT_CPLD_LOW_AGGR_MASK_LOW,
पूर्ण;

/* Platक्रमm hotplug next generation प्रणाली family data */
अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_शेष_ng_psu_items_data[] = अणु
	अणु
		.label = "psu1",
		.reg = MLXPLAT_CPLD_LPC_REG_PSU_OFFSET,
		.mask = BIT(0),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
	अणु
		.label = "psu2",
		.reg = MLXPLAT_CPLD_LPC_REG_PSU_OFFSET,
		.mask = BIT(1),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_शेष_ng_fan_items_data[] = अणु
	अणु
		.label = "fan1",
		.reg = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
		.mask = BIT(0),
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_DRW_CAP_OFFSET,
		.bit = BIT(0),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
	अणु
		.label = "fan2",
		.reg = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
		.mask = BIT(1),
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_DRW_CAP_OFFSET,
		.bit = BIT(1),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
	अणु
		.label = "fan3",
		.reg = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
		.mask = BIT(2),
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_DRW_CAP_OFFSET,
		.bit = BIT(2),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
	अणु
		.label = "fan4",
		.reg = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
		.mask = BIT(3),
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_DRW_CAP_OFFSET,
		.bit = BIT(3),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
	अणु
		.label = "fan5",
		.reg = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
		.mask = BIT(4),
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_DRW_CAP_OFFSET,
		.bit = BIT(4),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
	अणु
		.label = "fan6",
		.reg = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
		.mask = BIT(5),
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_DRW_CAP_OFFSET,
		.bit = BIT(5),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_item mlxplat_mlxcpld_शेष_ng_items[] = अणु
	अणु
		.data = mlxplat_mlxcpld_शेष_ng_psu_items_data,
		.aggr_mask = MLXPLAT_CPLD_AGGR_MASK_NG_DEF,
		.reg = MLXPLAT_CPLD_LPC_REG_PSU_OFFSET,
		.mask = MLXPLAT_CPLD_PSU_MASK,
		.count = ARRAY_SIZE(mlxplat_mlxcpld_शेष_ng_psu_items_data),
		.inversed = 1,
		.health = false,
	पूर्ण,
	अणु
		.data = mlxplat_mlxcpld_शेष_ng_pwr_items_data,
		.aggr_mask = MLXPLAT_CPLD_AGGR_MASK_NG_DEF,
		.reg = MLXPLAT_CPLD_LPC_REG_PWR_OFFSET,
		.mask = MLXPLAT_CPLD_PWR_MASK,
		.count = ARRAY_SIZE(mlxplat_mlxcpld_शेष_ng_pwr_items_data),
		.inversed = 0,
		.health = false,
	पूर्ण,
	अणु
		.data = mlxplat_mlxcpld_शेष_ng_fan_items_data,
		.aggr_mask = MLXPLAT_CPLD_AGGR_MASK_NG_DEF,
		.reg = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
		.mask = MLXPLAT_CPLD_FAN_NG_MASK,
		.count = ARRAY_SIZE(mlxplat_mlxcpld_शेष_ng_fan_items_data),
		.inversed = 1,
		.health = false,
	पूर्ण,
	अणु
		.data = mlxplat_mlxcpld_शेष_asic_items_data,
		.aggr_mask = MLXPLAT_CPLD_AGGR_MASK_NG_DEF,
		.reg = MLXPLAT_CPLD_LPC_REG_ASIC_HEALTH_OFFSET,
		.mask = MLXPLAT_CPLD_ASIC_MASK,
		.count = ARRAY_SIZE(mlxplat_mlxcpld_शेष_asic_items_data),
		.inversed = 0,
		.health = true,
	पूर्ण,
पूर्ण;

अटल
काष्ठा mlxreg_core_hotplug_platक्रमm_data mlxplat_mlxcpld_शेष_ng_data = अणु
	.items = mlxplat_mlxcpld_शेष_ng_items,
	.counter = ARRAY_SIZE(mlxplat_mlxcpld_शेष_ng_items),
	.cell = MLXPLAT_CPLD_LPC_REG_AGGR_OFFSET,
	.mask = MLXPLAT_CPLD_AGGR_MASK_NG_DEF | MLXPLAT_CPLD_AGGR_MASK_COMEX,
	.cell_low = MLXPLAT_CPLD_LPC_REG_AGGRLO_OFFSET,
	.mask_low = MLXPLAT_CPLD_LOW_AGGR_MASK_LOW,
पूर्ण;

/* Platक्रमm hotplug extended प्रणाली family data */
अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_ext_psu_items_data[] = अणु
	अणु
		.label = "psu1",
		.reg = MLXPLAT_CPLD_LPC_REG_PSU_OFFSET,
		.mask = BIT(0),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
	अणु
		.label = "psu2",
		.reg = MLXPLAT_CPLD_LPC_REG_PSU_OFFSET,
		.mask = BIT(1),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
	अणु
		.label = "psu3",
		.reg = MLXPLAT_CPLD_LPC_REG_PSU_OFFSET,
		.mask = BIT(2),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
	अणु
		.label = "psu4",
		.reg = MLXPLAT_CPLD_LPC_REG_PSU_OFFSET,
		.mask = BIT(3),
		.hpdev.nr = MLXPLAT_CPLD_NR_NONE,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_ext_pwr_items_data[] = अणु
	अणु
		.label = "pwr1",
		.reg = MLXPLAT_CPLD_LPC_REG_PWR_OFFSET,
		.mask = BIT(0),
		.hpdev.brdinfo = &mlxplat_mlxcpld_pwr[0],
		.hpdev.nr = MLXPLAT_CPLD_PSU_MSNXXXX_NR,
	पूर्ण,
	अणु
		.label = "pwr2",
		.reg = MLXPLAT_CPLD_LPC_REG_PWR_OFFSET,
		.mask = BIT(1),
		.hpdev.brdinfo = &mlxplat_mlxcpld_pwr[1],
		.hpdev.nr = MLXPLAT_CPLD_PSU_MSNXXXX_NR,
	पूर्ण,
	अणु
		.label = "pwr3",
		.reg = MLXPLAT_CPLD_LPC_REG_PWR_OFFSET,
		.mask = BIT(2),
		.hpdev.brdinfo = &mlxplat_mlxcpld_ext_pwr[0],
		.hpdev.nr = MLXPLAT_CPLD_PSU_MSNXXXX_NR,
	पूर्ण,
	अणु
		.label = "pwr4",
		.reg = MLXPLAT_CPLD_LPC_REG_PWR_OFFSET,
		.mask = BIT(3),
		.hpdev.brdinfo = &mlxplat_mlxcpld_ext_pwr[1],
		.hpdev.nr = MLXPLAT_CPLD_PSU_MSNXXXX_NR,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_item mlxplat_mlxcpld_ext_items[] = अणु
	अणु
		.data = mlxplat_mlxcpld_ext_psu_items_data,
		.aggr_mask = MLXPLAT_CPLD_AGGR_MASK_NG_DEF,
		.reg = MLXPLAT_CPLD_LPC_REG_PSU_OFFSET,
		.mask = MLXPLAT_CPLD_PSU_EXT_MASK,
		.capability = MLXPLAT_CPLD_LPC_REG_PSU_I2C_CAP_OFFSET,
		.count = ARRAY_SIZE(mlxplat_mlxcpld_ext_psu_items_data),
		.inversed = 1,
		.health = false,
	पूर्ण,
	अणु
		.data = mlxplat_mlxcpld_ext_pwr_items_data,
		.aggr_mask = MLXPLAT_CPLD_AGGR_MASK_NG_DEF,
		.reg = MLXPLAT_CPLD_LPC_REG_PWR_OFFSET,
		.mask = MLXPLAT_CPLD_PWR_EXT_MASK,
		.capability = MLXPLAT_CPLD_LPC_REG_PSU_I2C_CAP_OFFSET,
		.count = ARRAY_SIZE(mlxplat_mlxcpld_ext_pwr_items_data),
		.inversed = 0,
		.health = false,
	पूर्ण,
	अणु
		.data = mlxplat_mlxcpld_शेष_ng_fan_items_data,
		.aggr_mask = MLXPLAT_CPLD_AGGR_MASK_NG_DEF,
		.reg = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
		.mask = MLXPLAT_CPLD_FAN_NG_MASK,
		.count = ARRAY_SIZE(mlxplat_mlxcpld_शेष_ng_fan_items_data),
		.inversed = 1,
		.health = false,
	पूर्ण,
	अणु
		.data = mlxplat_mlxcpld_शेष_asic_items_data,
		.aggr_mask = MLXPLAT_CPLD_AGGR_MASK_NG_DEF,
		.reg = MLXPLAT_CPLD_LPC_REG_ASIC_HEALTH_OFFSET,
		.mask = MLXPLAT_CPLD_ASIC_MASK,
		.count = ARRAY_SIZE(mlxplat_mlxcpld_शेष_asic_items_data),
		.inversed = 0,
		.health = true,
	पूर्ण,
पूर्ण;

अटल
काष्ठा mlxreg_core_hotplug_platक्रमm_data mlxplat_mlxcpld_ext_data = अणु
	.items = mlxplat_mlxcpld_ext_items,
	.counter = ARRAY_SIZE(mlxplat_mlxcpld_ext_items),
	.cell = MLXPLAT_CPLD_LPC_REG_AGGR_OFFSET,
	.mask = MLXPLAT_CPLD_AGGR_MASK_NG_DEF | MLXPLAT_CPLD_AGGR_MASK_COMEX,
	.cell_low = MLXPLAT_CPLD_LPC_REG_AGGRLO_OFFSET,
	.mask_low = MLXPLAT_CPLD_LOW_AGGR_MASK_LOW,
पूर्ण;

/* Platक्रमm led शेष data */
अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_शेष_led_data[] = अणु
	अणु
		.label = "status:green",
		.reg = MLXPLAT_CPLD_LPC_REG_LED1_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "status:red",
		.reg = MLXPLAT_CPLD_LPC_REG_LED1_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK
	पूर्ण,
	अणु
		.label = "psu:green",
		.reg = MLXPLAT_CPLD_LPC_REG_LED1_OFFSET,
		.mask = MLXPLAT_CPLD_LED_HI_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "psu:red",
		.reg = MLXPLAT_CPLD_LPC_REG_LED1_OFFSET,
		.mask = MLXPLAT_CPLD_LED_HI_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "fan1:green",
		.reg = MLXPLAT_CPLD_LPC_REG_LED2_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "fan1:red",
		.reg = MLXPLAT_CPLD_LPC_REG_LED2_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "fan2:green",
		.reg = MLXPLAT_CPLD_LPC_REG_LED2_OFFSET,
		.mask = MLXPLAT_CPLD_LED_HI_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "fan2:red",
		.reg = MLXPLAT_CPLD_LPC_REG_LED2_OFFSET,
		.mask = MLXPLAT_CPLD_LED_HI_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "fan3:green",
		.reg = MLXPLAT_CPLD_LPC_REG_LED3_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "fan3:red",
		.reg = MLXPLAT_CPLD_LPC_REG_LED3_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "fan4:green",
		.reg = MLXPLAT_CPLD_LPC_REG_LED3_OFFSET,
		.mask = MLXPLAT_CPLD_LED_HI_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "fan4:red",
		.reg = MLXPLAT_CPLD_LPC_REG_LED3_OFFSET,
		.mask = MLXPLAT_CPLD_LED_HI_NIBBLE_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_platक्रमm_data mlxplat_शेष_led_data = अणु
		.data = mlxplat_mlxcpld_शेष_led_data,
		.counter = ARRAY_SIZE(mlxplat_mlxcpld_शेष_led_data),
पूर्ण;

/* Platक्रमm led MSN21xx प्रणाली family data */
अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_msn21xx_led_data[] = अणु
	अणु
		.label = "status:green",
		.reg = MLXPLAT_CPLD_LPC_REG_LED1_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "status:red",
		.reg = MLXPLAT_CPLD_LPC_REG_LED1_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK
	पूर्ण,
	अणु
		.label = "fan:green",
		.reg = MLXPLAT_CPLD_LPC_REG_LED2_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "fan:red",
		.reg = MLXPLAT_CPLD_LPC_REG_LED2_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "psu1:green",
		.reg = MLXPLAT_CPLD_LPC_REG_LED4_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "psu1:red",
		.reg = MLXPLAT_CPLD_LPC_REG_LED4_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "psu2:green",
		.reg = MLXPLAT_CPLD_LPC_REG_LED4_OFFSET,
		.mask = MLXPLAT_CPLD_LED_HI_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "psu2:red",
		.reg = MLXPLAT_CPLD_LPC_REG_LED4_OFFSET,
		.mask = MLXPLAT_CPLD_LED_HI_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "uid:blue",
		.reg = MLXPLAT_CPLD_LPC_REG_LED5_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_platक्रमm_data mlxplat_msn21xx_led_data = अणु
		.data = mlxplat_mlxcpld_msn21xx_led_data,
		.counter = ARRAY_SIZE(mlxplat_mlxcpld_msn21xx_led_data),
पूर्ण;

/* Platक्रमm led क्रम शेष data क्रम 200GbE प्रणालीs */
अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_शेष_ng_led_data[] = अणु
	अणु
		.label = "status:green",
		.reg = MLXPLAT_CPLD_LPC_REG_LED1_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "status:orange",
		.reg = MLXPLAT_CPLD_LPC_REG_LED1_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK
	पूर्ण,
	अणु
		.label = "psu:green",
		.reg = MLXPLAT_CPLD_LPC_REG_LED1_OFFSET,
		.mask = MLXPLAT_CPLD_LED_HI_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "psu:orange",
		.reg = MLXPLAT_CPLD_LPC_REG_LED1_OFFSET,
		.mask = MLXPLAT_CPLD_LED_HI_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "fan1:green",
		.reg = MLXPLAT_CPLD_LPC_REG_LED2_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_DRW_CAP_OFFSET,
		.bit = BIT(0),
	पूर्ण,
	अणु
		.label = "fan1:orange",
		.reg = MLXPLAT_CPLD_LPC_REG_LED2_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_DRW_CAP_OFFSET,
		.bit = BIT(0),
	पूर्ण,
	अणु
		.label = "fan2:green",
		.reg = MLXPLAT_CPLD_LPC_REG_LED2_OFFSET,
		.mask = MLXPLAT_CPLD_LED_HI_NIBBLE_MASK,
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_DRW_CAP_OFFSET,
		.bit = BIT(1),
	पूर्ण,
	अणु
		.label = "fan2:orange",
		.reg = MLXPLAT_CPLD_LPC_REG_LED2_OFFSET,
		.mask = MLXPLAT_CPLD_LED_HI_NIBBLE_MASK,
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_DRW_CAP_OFFSET,
		.bit = BIT(1),
	पूर्ण,
	अणु
		.label = "fan3:green",
		.reg = MLXPLAT_CPLD_LPC_REG_LED3_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_DRW_CAP_OFFSET,
		.bit = BIT(2),
	पूर्ण,
	अणु
		.label = "fan3:orange",
		.reg = MLXPLAT_CPLD_LPC_REG_LED3_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_DRW_CAP_OFFSET,
		.bit = BIT(2),
	पूर्ण,
	अणु
		.label = "fan4:green",
		.reg = MLXPLAT_CPLD_LPC_REG_LED3_OFFSET,
		.mask = MLXPLAT_CPLD_LED_HI_NIBBLE_MASK,
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_DRW_CAP_OFFSET,
		.bit = BIT(3),
	पूर्ण,
	अणु
		.label = "fan4:orange",
		.reg = MLXPLAT_CPLD_LPC_REG_LED3_OFFSET,
		.mask = MLXPLAT_CPLD_LED_HI_NIBBLE_MASK,
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_DRW_CAP_OFFSET,
		.bit = BIT(3),
	पूर्ण,
	अणु
		.label = "fan5:green",
		.reg = MLXPLAT_CPLD_LPC_REG_LED4_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_DRW_CAP_OFFSET,
		.bit = BIT(4),
	पूर्ण,
	अणु
		.label = "fan5:orange",
		.reg = MLXPLAT_CPLD_LPC_REG_LED4_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_DRW_CAP_OFFSET,
		.bit = BIT(4),
	पूर्ण,
	अणु
		.label = "fan6:green",
		.reg = MLXPLAT_CPLD_LPC_REG_LED4_OFFSET,
		.mask = MLXPLAT_CPLD_LED_HI_NIBBLE_MASK,
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_DRW_CAP_OFFSET,
		.bit = BIT(5),
	पूर्ण,
	अणु
		.label = "fan6:orange",
		.reg = MLXPLAT_CPLD_LPC_REG_LED4_OFFSET,
		.mask = MLXPLAT_CPLD_LED_HI_NIBBLE_MASK,
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_DRW_CAP_OFFSET,
		.bit = BIT(5),
	पूर्ण,
	अणु
		.label = "uid:blue",
		.reg = MLXPLAT_CPLD_LPC_REG_LED5_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_platक्रमm_data mlxplat_शेष_ng_led_data = अणु
		.data = mlxplat_mlxcpld_शेष_ng_led_data,
		.counter = ARRAY_SIZE(mlxplat_mlxcpld_शेष_ng_led_data),
पूर्ण;

/* Platक्रमm led क्रम Comex based 100GbE प्रणालीs */
अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_comex_100G_led_data[] = अणु
	अणु
		.label = "status:green",
		.reg = MLXPLAT_CPLD_LPC_REG_LED1_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "status:red",
		.reg = MLXPLAT_CPLD_LPC_REG_LED1_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK
	पूर्ण,
	अणु
		.label = "psu:green",
		.reg = MLXPLAT_CPLD_LPC_REG_LED1_OFFSET,
		.mask = MLXPLAT_CPLD_LED_HI_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "psu:red",
		.reg = MLXPLAT_CPLD_LPC_REG_LED1_OFFSET,
		.mask = MLXPLAT_CPLD_LED_HI_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "fan1:green",
		.reg = MLXPLAT_CPLD_LPC_REG_LED2_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "fan1:red",
		.reg = MLXPLAT_CPLD_LPC_REG_LED2_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "fan2:green",
		.reg = MLXPLAT_CPLD_LPC_REG_LED2_OFFSET,
		.mask = MLXPLAT_CPLD_LED_HI_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "fan2:red",
		.reg = MLXPLAT_CPLD_LPC_REG_LED2_OFFSET,
		.mask = MLXPLAT_CPLD_LED_HI_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "fan3:green",
		.reg = MLXPLAT_CPLD_LPC_REG_LED3_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "fan3:red",
		.reg = MLXPLAT_CPLD_LPC_REG_LED3_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "fan4:green",
		.reg = MLXPLAT_CPLD_LPC_REG_LED3_OFFSET,
		.mask = MLXPLAT_CPLD_LED_HI_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "fan4:red",
		.reg = MLXPLAT_CPLD_LPC_REG_LED3_OFFSET,
		.mask = MLXPLAT_CPLD_LED_HI_NIBBLE_MASK,
	पूर्ण,
	अणु
		.label = "uid:blue",
		.reg = MLXPLAT_CPLD_LPC_REG_LED5_OFFSET,
		.mask = MLXPLAT_CPLD_LED_LO_NIBBLE_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_platक्रमm_data mlxplat_comex_100G_led_data = अणु
		.data = mlxplat_mlxcpld_comex_100G_led_data,
		.counter = ARRAY_SIZE(mlxplat_mlxcpld_comex_100G_led_data),
पूर्ण;

/* Platक्रमm रेजिस्टर access शेष */
अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_शेष_regs_io_data[] = अणु
	अणु
		.label = "cpld1_version",
		.reg = MLXPLAT_CPLD_LPC_REG_CPLD1_VER_OFFSET,
		.bit = GENMASK(7, 0),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "cpld2_version",
		.reg = MLXPLAT_CPLD_LPC_REG_CPLD2_VER_OFFSET,
		.bit = GENMASK(7, 0),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "cpld1_pn",
		.reg = MLXPLAT_CPLD_LPC_REG_CPLD1_PN_OFFSET,
		.bit = GENMASK(15, 0),
		.mode = 0444,
		.regnum = 2,
	पूर्ण,
	अणु
		.label = "cpld2_pn",
		.reg = MLXPLAT_CPLD_LPC_REG_CPLD2_PN_OFFSET,
		.bit = GENMASK(15, 0),
		.mode = 0444,
		.regnum = 2,
	पूर्ण,
	अणु
		.label = "cpld1_version_min",
		.reg = MLXPLAT_CPLD_LPC_REG_CPLD1_MVER_OFFSET,
		.bit = GENMASK(7, 0),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "cpld2_version_min",
		.reg = MLXPLAT_CPLD_LPC_REG_CPLD2_MVER_OFFSET,
		.bit = GENMASK(7, 0),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_long_pb",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(0),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_short_pb",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(1),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_aux_pwr_or_ref",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(2),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_main_pwr_fail",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(3),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_sw_reset",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(4),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_fw_reset",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(5),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_hotswap_or_wd",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(6),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_asic_thermal",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(7),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "psu1_on",
		.reg = MLXPLAT_CPLD_LPC_REG_GP1_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(0),
		.mode = 0200,
	पूर्ण,
	अणु
		.label = "psu2_on",
		.reg = MLXPLAT_CPLD_LPC_REG_GP1_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(1),
		.mode = 0200,
	पूर्ण,
	अणु
		.label = "pwr_cycle",
		.reg = MLXPLAT_CPLD_LPC_REG_GP1_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(2),
		.mode = 0200,
	पूर्ण,
	अणु
		.label = "pwr_down",
		.reg = MLXPLAT_CPLD_LPC_REG_GP1_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(3),
		.mode = 0200,
	पूर्ण,
	अणु
		.label = "select_iio",
		.reg = MLXPLAT_CPLD_LPC_REG_GP2_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(6),
		.mode = 0644,
	पूर्ण,
	अणु
		.label = "asic_health",
		.reg = MLXPLAT_CPLD_LPC_REG_ASIC_HEALTH_OFFSET,
		.mask = MLXPLAT_CPLD_ASIC_MASK,
		.bit = 1,
		.mode = 0444,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_platक्रमm_data mlxplat_शेष_regs_io_data = अणु
		.data = mlxplat_mlxcpld_शेष_regs_io_data,
		.counter = ARRAY_SIZE(mlxplat_mlxcpld_शेष_regs_io_data),
पूर्ण;

/* Platक्रमm रेजिस्टर access MSN21xx, MSN201x, MSN274x प्रणालीs families data */
अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_msn21xx_regs_io_data[] = अणु
	अणु
		.label = "cpld1_version",
		.reg = MLXPLAT_CPLD_LPC_REG_CPLD1_VER_OFFSET,
		.bit = GENMASK(7, 0),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "cpld2_version",
		.reg = MLXPLAT_CPLD_LPC_REG_CPLD2_VER_OFFSET,
		.bit = GENMASK(7, 0),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "cpld1_pn",
		.reg = MLXPLAT_CPLD_LPC_REG_CPLD1_PN_OFFSET,
		.bit = GENMASK(15, 0),
		.mode = 0444,
		.regnum = 2,
	पूर्ण,
	अणु
		.label = "cpld2_pn",
		.reg = MLXPLAT_CPLD_LPC_REG_CPLD2_PN_OFFSET,
		.bit = GENMASK(15, 0),
		.mode = 0444,
		.regnum = 2,
	पूर्ण,
	अणु
		.label = "cpld1_version_min",
		.reg = MLXPLAT_CPLD_LPC_REG_CPLD1_MVER_OFFSET,
		.bit = GENMASK(7, 0),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "cpld2_version_min",
		.reg = MLXPLAT_CPLD_LPC_REG_CPLD2_MVER_OFFSET,
		.bit = GENMASK(7, 0),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_long_pb",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(0),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_short_pb",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(1),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_aux_pwr_or_ref",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(2),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_sw_reset",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(3),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_main_pwr_fail",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(4),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_asic_thermal",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(5),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_hotswap_or_halt",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(6),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_sff_wd",
		.reg = MLXPLAT_CPLD_LPC_REG_RST_CAUSE1_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(6),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "psu1_on",
		.reg = MLXPLAT_CPLD_LPC_REG_GP1_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(0),
		.mode = 0200,
	पूर्ण,
	अणु
		.label = "psu2_on",
		.reg = MLXPLAT_CPLD_LPC_REG_GP1_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(1),
		.mode = 0200,
	पूर्ण,
	अणु
		.label = "pwr_cycle",
		.reg = MLXPLAT_CPLD_LPC_REG_GP1_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(2),
		.mode = 0200,
	पूर्ण,
	अणु
		.label = "pwr_down",
		.reg = MLXPLAT_CPLD_LPC_REG_GP1_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(3),
		.mode = 0200,
	पूर्ण,
	अणु
		.label = "select_iio",
		.reg = MLXPLAT_CPLD_LPC_REG_GP2_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(6),
		.mode = 0644,
	पूर्ण,
	अणु
		.label = "asic_health",
		.reg = MLXPLAT_CPLD_LPC_REG_ASIC_HEALTH_OFFSET,
		.mask = MLXPLAT_CPLD_ASIC_MASK,
		.bit = 1,
		.mode = 0444,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_platक्रमm_data mlxplat_msn21xx_regs_io_data = अणु
		.data = mlxplat_mlxcpld_msn21xx_regs_io_data,
		.counter = ARRAY_SIZE(mlxplat_mlxcpld_msn21xx_regs_io_data),
पूर्ण;

/* Platक्रमm रेजिस्टर access क्रम next generation प्रणालीs families data */
अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_शेष_ng_regs_io_data[] = अणु
	अणु
		.label = "cpld1_version",
		.reg = MLXPLAT_CPLD_LPC_REG_CPLD1_VER_OFFSET,
		.bit = GENMASK(7, 0),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "cpld2_version",
		.reg = MLXPLAT_CPLD_LPC_REG_CPLD2_VER_OFFSET,
		.bit = GENMASK(7, 0),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "cpld3_version",
		.reg = MLXPLAT_CPLD_LPC_REG_CPLD3_VER_OFFSET,
		.bit = GENMASK(7, 0),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "cpld4_version",
		.reg = MLXPLAT_CPLD_LPC_REG_CPLD4_VER_OFFSET,
		.bit = GENMASK(7, 0),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "cpld1_pn",
		.reg = MLXPLAT_CPLD_LPC_REG_CPLD1_PN_OFFSET,
		.bit = GENMASK(15, 0),
		.mode = 0444,
		.regnum = 2,
	पूर्ण,
	अणु
		.label = "cpld2_pn",
		.reg = MLXPLAT_CPLD_LPC_REG_CPLD2_PN_OFFSET,
		.bit = GENMASK(15, 0),
		.mode = 0444,
		.regnum = 2,
	पूर्ण,
	अणु
		.label = "cpld3_pn",
		.reg = MLXPLAT_CPLD_LPC_REG_CPLD3_PN_OFFSET,
		.bit = GENMASK(15, 0),
		.mode = 0444,
		.regnum = 2,
	पूर्ण,
	अणु
		.label = "cpld4_pn",
		.reg = MLXPLAT_CPLD_LPC_REG_CPLD4_PN_OFFSET,
		.bit = GENMASK(15, 0),
		.mode = 0444,
		.regnum = 2,
	पूर्ण,
	अणु
		.label = "cpld1_version_min",
		.reg = MLXPLAT_CPLD_LPC_REG_CPLD1_MVER_OFFSET,
		.bit = GENMASK(7, 0),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "cpld2_version_min",
		.reg = MLXPLAT_CPLD_LPC_REG_CPLD2_MVER_OFFSET,
		.bit = GENMASK(7, 0),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "cpld3_version_min",
		.reg = MLXPLAT_CPLD_LPC_REG_CPLD3_MVER_OFFSET,
		.bit = GENMASK(7, 0),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "cpld4_version_min",
		.reg = MLXPLAT_CPLD_LPC_REG_CPLD4_MVER_OFFSET,
		.bit = GENMASK(7, 0),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_long_pb",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(0),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_short_pb",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(1),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_aux_pwr_or_ref",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(2),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_from_comex",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(4),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_from_asic",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(5),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_swb_wd",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(6),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_asic_thermal",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(7),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_comex_pwr_fail",
		.reg = MLXPLAT_CPLD_LPC_REG_RST_CAUSE1_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(3),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_platform",
		.reg = MLXPLAT_CPLD_LPC_REG_RST_CAUSE1_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(4),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_soc",
		.reg = MLXPLAT_CPLD_LPC_REG_RST_CAUSE1_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(5),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_comex_wd",
		.reg = MLXPLAT_CPLD_LPC_REG_RST_CAUSE1_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(6),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_voltmon_upgrade_fail",
		.reg = MLXPLAT_CPLD_LPC_REG_RST_CAUSE2_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(0),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_system",
		.reg = MLXPLAT_CPLD_LPC_REG_RST_CAUSE2_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(1),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_sw_pwr_off",
		.reg = MLXPLAT_CPLD_LPC_REG_RST_CAUSE2_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(2),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_comex_thermal",
		.reg = MLXPLAT_CPLD_LPC_REG_RST_CAUSE2_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(3),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_reload_bios",
		.reg = MLXPLAT_CPLD_LPC_REG_RST_CAUSE2_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(5),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "reset_ac_pwr_fail",
		.reg = MLXPLAT_CPLD_LPC_REG_RST_CAUSE2_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(6),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "psu1_on",
		.reg = MLXPLAT_CPLD_LPC_REG_GP1_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(0),
		.mode = 0200,
	पूर्ण,
	अणु
		.label = "psu2_on",
		.reg = MLXPLAT_CPLD_LPC_REG_GP1_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(1),
		.mode = 0200,
	पूर्ण,
	अणु
		.label = "pwr_cycle",
		.reg = MLXPLAT_CPLD_LPC_REG_GP1_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(2),
		.mode = 0200,
	पूर्ण,
	अणु
		.label = "pwr_down",
		.reg = MLXPLAT_CPLD_LPC_REG_GP1_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(3),
		.mode = 0200,
	पूर्ण,
	अणु
		.label = "jtag_enable",
		.reg = MLXPLAT_CPLD_LPC_REG_GP2_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(4),
		.mode = 0644,
	पूर्ण,
	अणु
		.label = "asic_health",
		.reg = MLXPLAT_CPLD_LPC_REG_ASIC_HEALTH_OFFSET,
		.mask = MLXPLAT_CPLD_ASIC_MASK,
		.bit = 1,
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "fan_dir",
		.reg = MLXPLAT_CPLD_LPC_REG_FAN_सूचीECTION,
		.bit = GENMASK(7, 0),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "voltreg_update_status",
		.reg = MLXPLAT_CPLD_LPC_REG_GP0_RO_OFFSET,
		.mask = MLXPLAT_CPLD_VOLTREG_UPD_MASK,
		.bit = 5,
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "vpd_wp",
		.reg = MLXPLAT_CPLD_LPC_REG_GP0_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(3),
		.mode = 0644,
	पूर्ण,
	अणु
		.label = "pcie_asic_reset_dis",
		.reg = MLXPLAT_CPLD_LPC_REG_GP0_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(4),
		.mode = 0644,
	पूर्ण,
	अणु
		.label = "config1",
		.reg = MLXPLAT_CPLD_LPC_REG_CONFIG1_OFFSET,
		.bit = GENMASK(7, 0),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "config2",
		.reg = MLXPLAT_CPLD_LPC_REG_CONFIG2_OFFSET,
		.bit = GENMASK(7, 0),
		.mode = 0444,
	पूर्ण,
	अणु
		.label = "ufm_version",
		.reg = MLXPLAT_CPLD_LPC_REG_UFM_VERSION_OFFSET,
		.bit = GENMASK(7, 0),
		.mode = 0444,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_platक्रमm_data mlxplat_शेष_ng_regs_io_data = अणु
		.data = mlxplat_mlxcpld_शेष_ng_regs_io_data,
		.counter = ARRAY_SIZE(mlxplat_mlxcpld_शेष_ng_regs_io_data),
पूर्ण;

/* Platक्रमm FAN शेष */
अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_शेष_fan_data[] = अणु
	अणु
		.label = "pwm1",
		.reg = MLXPLAT_CPLD_LPC_REG_PWM1_OFFSET,
	पूर्ण,
	अणु
		.label = "tacho1",
		.reg = MLXPLAT_CPLD_LPC_REG_TACHO1_OFFSET,
		.mask = GENMASK(7, 0),
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_CAP1_OFFSET,
		.bit = BIT(0),
		.reg_prsnt = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,

	पूर्ण,
	अणु
		.label = "tacho2",
		.reg = MLXPLAT_CPLD_LPC_REG_TACHO2_OFFSET,
		.mask = GENMASK(7, 0),
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_CAP1_OFFSET,
		.bit = BIT(1),
		.reg_prsnt = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
	पूर्ण,
	अणु
		.label = "tacho3",
		.reg = MLXPLAT_CPLD_LPC_REG_TACHO3_OFFSET,
		.mask = GENMASK(7, 0),
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_CAP1_OFFSET,
		.bit = BIT(2),
		.reg_prsnt = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
	पूर्ण,
	अणु
		.label = "tacho4",
		.reg = MLXPLAT_CPLD_LPC_REG_TACHO4_OFFSET,
		.mask = GENMASK(7, 0),
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_CAP1_OFFSET,
		.bit = BIT(3),
		.reg_prsnt = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
	पूर्ण,
	अणु
		.label = "tacho5",
		.reg = MLXPLAT_CPLD_LPC_REG_TACHO5_OFFSET,
		.mask = GENMASK(7, 0),
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_CAP1_OFFSET,
		.bit = BIT(4),
		.reg_prsnt = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
	पूर्ण,
	अणु
		.label = "tacho6",
		.reg = MLXPLAT_CPLD_LPC_REG_TACHO6_OFFSET,
		.mask = GENMASK(7, 0),
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_CAP1_OFFSET,
		.bit = BIT(5),
		.reg_prsnt = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
	पूर्ण,
	अणु
		.label = "tacho7",
		.reg = MLXPLAT_CPLD_LPC_REG_TACHO7_OFFSET,
		.mask = GENMASK(7, 0),
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_CAP1_OFFSET,
		.bit = BIT(6),
		.reg_prsnt = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
	पूर्ण,
	अणु
		.label = "tacho8",
		.reg = MLXPLAT_CPLD_LPC_REG_TACHO8_OFFSET,
		.mask = GENMASK(7, 0),
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_CAP1_OFFSET,
		.bit = BIT(7),
		.reg_prsnt = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
	पूर्ण,
	अणु
		.label = "tacho9",
		.reg = MLXPLAT_CPLD_LPC_REG_TACHO9_OFFSET,
		.mask = GENMASK(7, 0),
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_CAP2_OFFSET,
		.bit = BIT(0),
		.reg_prsnt = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
	पूर्ण,
	अणु
		.label = "tacho10",
		.reg = MLXPLAT_CPLD_LPC_REG_TACHO10_OFFSET,
		.mask = GENMASK(7, 0),
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_CAP2_OFFSET,
		.bit = BIT(1),
		.reg_prsnt = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
	पूर्ण,
	अणु
		.label = "tacho11",
		.reg = MLXPLAT_CPLD_LPC_REG_TACHO11_OFFSET,
		.mask = GENMASK(7, 0),
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_CAP2_OFFSET,
		.bit = BIT(2),
		.reg_prsnt = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
	पूर्ण,
	अणु
		.label = "tacho12",
		.reg = MLXPLAT_CPLD_LPC_REG_TACHO12_OFFSET,
		.mask = GENMASK(7, 0),
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_CAP2_OFFSET,
		.bit = BIT(3),
		.reg_prsnt = MLXPLAT_CPLD_LPC_REG_FAN_OFFSET,
	पूर्ण,
	अणु
		.label = "conf",
		.capability = MLXPLAT_CPLD_LPC_REG_TACHO_SPEED_OFFSET,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_platक्रमm_data mlxplat_शेष_fan_data = अणु
		.data = mlxplat_mlxcpld_शेष_fan_data,
		.counter = ARRAY_SIZE(mlxplat_mlxcpld_शेष_fan_data),
		.capability = MLXPLAT_CPLD_LPC_REG_FAN_DRW_CAP_OFFSET,
पूर्ण;

/* Watchकरोg type1: hardware implementation version1
 * (MSN2700, MSN2410, MSN2740, MSN2100 and MSN2140 प्रणालीs).
 */
अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_wd_मुख्य_regs_type1[] = अणु
	अणु
		.label = "action",
		.reg = MLXPLAT_CPLD_LPC_REG_WD1_ACT_OFFSET,
		.mask = MLXPLAT_CPLD_WD_RESET_ACT_MASK,
		.bit = 0,
	पूर्ण,
	अणु
		.label = "timeout",
		.reg = MLXPLAT_CPLD_LPC_REG_WD1_TMR_OFFSET,
		.mask = MLXPLAT_CPLD_WD_TYPE1_TO_MASK,
		.health_cntr = MLXPLAT_CPLD_WD_DFLT_TIMEOUT,
	पूर्ण,
	अणु
		.label = "ping",
		.reg = MLXPLAT_CPLD_LPC_REG_WD_CLEAR_OFFSET,
		.mask = MLXPLAT_CPLD_WD1_CLEAR_MASK,
		.bit = 0,
	पूर्ण,
	अणु
		.label = "reset",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(6),
		.bit = 6,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_wd_aux_regs_type1[] = अणु
	अणु
		.label = "action",
		.reg = MLXPLAT_CPLD_LPC_REG_WD2_ACT_OFFSET,
		.mask = MLXPLAT_CPLD_WD_FAN_ACT_MASK,
		.bit = 4,
	पूर्ण,
	अणु
		.label = "timeout",
		.reg = MLXPLAT_CPLD_LPC_REG_WD2_TMR_OFFSET,
		.mask = MLXPLAT_CPLD_WD_TYPE1_TO_MASK,
		.health_cntr = MLXPLAT_CPLD_WD_DFLT_TIMEOUT,
	पूर्ण,
	अणु
		.label = "ping",
		.reg = MLXPLAT_CPLD_LPC_REG_WD_CLEAR_OFFSET,
		.mask = MLXPLAT_CPLD_WD1_CLEAR_MASK,
		.bit = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_platक्रमm_data mlxplat_mlxcpld_wd_set_type1[] = अणु
	अणु
		.data = mlxplat_mlxcpld_wd_मुख्य_regs_type1,
		.counter = ARRAY_SIZE(mlxplat_mlxcpld_wd_मुख्य_regs_type1),
		.version = MLX_WDT_TYPE1,
		.identity = "mlx-wdt-main",
	पूर्ण,
	अणु
		.data = mlxplat_mlxcpld_wd_aux_regs_type1,
		.counter = ARRAY_SIZE(mlxplat_mlxcpld_wd_aux_regs_type1),
		.version = MLX_WDT_TYPE1,
		.identity = "mlx-wdt-aux",
	पूर्ण,
पूर्ण;

/* Watchकरोg type2: hardware implementation version 2
 * (all प्रणालीs except (MSN2700, MSN2410, MSN2740, MSN2100 and MSN2140).
 */
अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_wd_मुख्य_regs_type2[] = अणु
	अणु
		.label = "action",
		.reg = MLXPLAT_CPLD_LPC_REG_WD2_ACT_OFFSET,
		.mask = MLXPLAT_CPLD_WD_RESET_ACT_MASK,
		.bit = 0,
	पूर्ण,
	अणु
		.label = "timeout",
		.reg = MLXPLAT_CPLD_LPC_REG_WD2_TMR_OFFSET,
		.mask = MLXPLAT_CPLD_WD_TYPE2_TO_MASK,
		.health_cntr = MLXPLAT_CPLD_WD_DFLT_TIMEOUT,
	पूर्ण,
	अणु
		.label = "timeleft",
		.reg = MLXPLAT_CPLD_LPC_REG_WD2_TLEFT_OFFSET,
		.mask = MLXPLAT_CPLD_WD_TYPE2_TO_MASK,
	पूर्ण,
	अणु
		.label = "ping",
		.reg = MLXPLAT_CPLD_LPC_REG_WD2_ACT_OFFSET,
		.mask = MLXPLAT_CPLD_WD_RESET_ACT_MASK,
		.bit = 0,
	पूर्ण,
	अणु
		.label = "reset",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(6),
		.bit = 6,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_wd_aux_regs_type2[] = अणु
	अणु
		.label = "action",
		.reg = MLXPLAT_CPLD_LPC_REG_WD3_ACT_OFFSET,
		.mask = MLXPLAT_CPLD_WD_FAN_ACT_MASK,
		.bit = 4,
	पूर्ण,
	अणु
		.label = "timeout",
		.reg = MLXPLAT_CPLD_LPC_REG_WD3_TMR_OFFSET,
		.mask = MLXPLAT_CPLD_WD_TYPE2_TO_MASK,
		.health_cntr = MLXPLAT_CPLD_WD_DFLT_TIMEOUT,
	पूर्ण,
	अणु
		.label = "timeleft",
		.reg = MLXPLAT_CPLD_LPC_REG_WD3_TLEFT_OFFSET,
		.mask = MLXPLAT_CPLD_WD_TYPE2_TO_MASK,
	पूर्ण,
	अणु
		.label = "ping",
		.reg = MLXPLAT_CPLD_LPC_REG_WD3_ACT_OFFSET,
		.mask = MLXPLAT_CPLD_WD_FAN_ACT_MASK,
		.bit = 4,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_platक्रमm_data mlxplat_mlxcpld_wd_set_type2[] = अणु
	अणु
		.data = mlxplat_mlxcpld_wd_मुख्य_regs_type2,
		.counter = ARRAY_SIZE(mlxplat_mlxcpld_wd_मुख्य_regs_type2),
		.version = MLX_WDT_TYPE2,
		.identity = "mlx-wdt-main",
	पूर्ण,
	अणु
		.data = mlxplat_mlxcpld_wd_aux_regs_type2,
		.counter = ARRAY_SIZE(mlxplat_mlxcpld_wd_aux_regs_type2),
		.version = MLX_WDT_TYPE2,
		.identity = "mlx-wdt-aux",
	पूर्ण,
पूर्ण;

/* Watchकरोg type3: hardware implementation version 3
 * Can be on all प्रणालीs. It's dअगरferentiated by WD capability bit.
 * Old प्रणालीs (MSN2700, MSN2410, MSN2740, MSN2100 and MSN2140)
 * still have only one मुख्य watchकरोg.
 */
अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_wd_मुख्य_regs_type3[] = अणु
	अणु
		.label = "action",
		.reg = MLXPLAT_CPLD_LPC_REG_WD2_ACT_OFFSET,
		.mask = MLXPLAT_CPLD_WD_RESET_ACT_MASK,
		.bit = 0,
	पूर्ण,
	अणु
		.label = "timeout",
		.reg = MLXPLAT_CPLD_LPC_REG_WD2_TMR_OFFSET,
		.mask = MLXPLAT_CPLD_WD_TYPE2_TO_MASK,
		.health_cntr = MLXPLAT_CPLD_WD3_DFLT_TIMEOUT,
	पूर्ण,
	अणु
		.label = "timeleft",
		.reg = MLXPLAT_CPLD_LPC_REG_WD2_TMR_OFFSET,
		.mask = MLXPLAT_CPLD_WD_TYPE2_TO_MASK,
	पूर्ण,
	अणु
		.label = "ping",
		.reg = MLXPLAT_CPLD_LPC_REG_WD2_ACT_OFFSET,
		.mask = MLXPLAT_CPLD_WD_RESET_ACT_MASK,
		.bit = 0,
	पूर्ण,
	अणु
		.label = "reset",
		.reg = MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET,
		.mask = GENMASK(7, 0) & ~BIT(6),
		.bit = 6,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_data mlxplat_mlxcpld_wd_aux_regs_type3[] = अणु
	अणु
		.label = "action",
		.reg = MLXPLAT_CPLD_LPC_REG_WD3_ACT_OFFSET,
		.mask = MLXPLAT_CPLD_WD_FAN_ACT_MASK,
		.bit = 4,
	पूर्ण,
	अणु
		.label = "timeout",
		.reg = MLXPLAT_CPLD_LPC_REG_WD3_TMR_OFFSET,
		.mask = MLXPLAT_CPLD_WD_TYPE2_TO_MASK,
		.health_cntr = MLXPLAT_CPLD_WD3_DFLT_TIMEOUT,
	पूर्ण,
	अणु
		.label = "timeleft",
		.reg = MLXPLAT_CPLD_LPC_REG_WD3_TMR_OFFSET,
		.mask = MLXPLAT_CPLD_WD_TYPE2_TO_MASK,
	पूर्ण,
	अणु
		.label = "ping",
		.reg = MLXPLAT_CPLD_LPC_REG_WD3_ACT_OFFSET,
		.mask = MLXPLAT_CPLD_WD_FAN_ACT_MASK,
		.bit = 4,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlxreg_core_platक्रमm_data mlxplat_mlxcpld_wd_set_type3[] = अणु
	अणु
		.data = mlxplat_mlxcpld_wd_मुख्य_regs_type3,
		.counter = ARRAY_SIZE(mlxplat_mlxcpld_wd_मुख्य_regs_type3),
		.version = MLX_WDT_TYPE3,
		.identity = "mlx-wdt-main",
	पूर्ण,
	अणु
		.data = mlxplat_mlxcpld_wd_aux_regs_type3,
		.counter = ARRAY_SIZE(mlxplat_mlxcpld_wd_aux_regs_type3),
		.version = MLX_WDT_TYPE3,
		.identity = "mlx-wdt-aux",
	पूर्ण,
पूर्ण;

अटल bool mlxplat_mlxcpld_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MLXPLAT_CPLD_LPC_REG_LED1_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_LED2_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_LED3_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_LED4_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_LED5_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_GP0_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_GP1_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WP1_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_GP2_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WP2_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_AGGR_MASK_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_AGGRLO_MASK_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_AGGRCO_MASK_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_AGGRCX_MASK_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_ASIC_EVENT_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_ASIC_MASK_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_PSU_EVENT_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_PSU_MASK_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_PWR_EVENT_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_PWR_MASK_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_FAN_EVENT_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_FAN_MASK_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WD_CLEAR_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WD_CLEAR_WP_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WD1_TMR_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WD1_ACT_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WD2_TMR_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WD2_TLEFT_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WD2_ACT_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WD3_TMR_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WD3_TLEFT_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WD3_ACT_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_PWM1_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_PWM_CONTROL_OFFSET:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool mlxplat_mlxcpld_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MLXPLAT_CPLD_LPC_REG_CPLD1_VER_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CPLD2_VER_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CPLD3_VER_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CPLD4_VER_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CPLD1_PN_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CPLD2_PN_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CPLD3_PN_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CPLD4_PN_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_RST_CAUSE1_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_RST_CAUSE2_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_LED1_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_LED2_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_LED3_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_LED4_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_LED5_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_FAN_सूचीECTION:
	हाल MLXPLAT_CPLD_LPC_REG_GP0_RO_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_GP0_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_GP1_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WP1_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_GP2_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WP2_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_AGGR_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_AGGR_MASK_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_AGGRLO_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_AGGRLO_MASK_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_AGGRCO_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_AGGRCO_MASK_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_AGGRCX_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_AGGRCX_MASK_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_ASIC_HEALTH_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_ASIC_EVENT_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_ASIC_MASK_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_PSU_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_PSU_EVENT_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_PSU_MASK_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_PWR_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_PWR_EVENT_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_PWR_MASK_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_FAN_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_FAN_EVENT_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_FAN_MASK_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WD_CLEAR_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WD_CLEAR_WP_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WD1_TMR_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WD1_ACT_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WD2_TMR_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WD2_TLEFT_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WD2_ACT_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WD3_TMR_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WD3_TLEFT_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WD3_ACT_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CPLD1_MVER_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CPLD2_MVER_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CPLD3_MVER_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CPLD4_MVER_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_PWM1_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO1_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO2_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO3_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO4_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO5_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO6_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO7_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO8_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO9_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO10_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO11_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO12_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_PWM_CONTROL_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_FAN_CAP1_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_FAN_CAP2_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_FAN_DRW_CAP_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO_SPEED_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_PSU_I2C_CAP_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CONFIG1_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CONFIG2_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_UFM_VERSION_OFFSET:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool mlxplat_mlxcpld_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MLXPLAT_CPLD_LPC_REG_CPLD1_VER_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CPLD2_VER_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CPLD3_VER_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CPLD4_VER_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CPLD1_PN_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CPLD2_PN_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CPLD3_PN_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CPLD4_PN_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_RESET_CAUSE_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_RST_CAUSE1_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_RST_CAUSE2_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_LED1_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_LED2_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_LED3_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_LED4_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_LED5_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_FAN_सूचीECTION:
	हाल MLXPLAT_CPLD_LPC_REG_GP0_RO_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_GP0_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_GP1_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_GP2_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_AGGR_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_AGGR_MASK_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_AGGRLO_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_AGGRLO_MASK_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_AGGRCO_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_AGGRCO_MASK_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_AGGRCX_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_AGGRCX_MASK_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_ASIC_HEALTH_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_ASIC_EVENT_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_ASIC_MASK_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_PSU_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_PSU_EVENT_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_PSU_MASK_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_PWR_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_PWR_EVENT_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_PWR_MASK_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_FAN_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_FAN_EVENT_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_FAN_MASK_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WD2_TMR_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WD2_TLEFT_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WD3_TMR_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_WD3_TLEFT_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CPLD1_MVER_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CPLD2_MVER_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CPLD3_MVER_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CPLD4_MVER_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_PWM1_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO1_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO2_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO3_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO4_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO5_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO6_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO7_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO8_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO9_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO10_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO11_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO12_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_PWM_CONTROL_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_FAN_CAP1_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_FAN_CAP2_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_FAN_DRW_CAP_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_TACHO_SPEED_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_PSU_I2C_CAP_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CONFIG1_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_CONFIG2_OFFSET:
	हाल MLXPLAT_CPLD_LPC_REG_UFM_VERSION_OFFSET:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल स्थिर काष्ठा reg_शेष mlxplat_mlxcpld_regmap_शेष[] = अणु
	अणु MLXPLAT_CPLD_LPC_REG_WP1_OFFSET, 0x00 पूर्ण,
	अणु MLXPLAT_CPLD_LPC_REG_WP2_OFFSET, 0x00 पूर्ण,
	अणु MLXPLAT_CPLD_LPC_REG_PWM_CONTROL_OFFSET, 0x00 पूर्ण,
	अणु MLXPLAT_CPLD_LPC_REG_WD_CLEAR_WP_OFFSET, 0x00 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष mlxplat_mlxcpld_regmap_ng[] = अणु
	अणु MLXPLAT_CPLD_LPC_REG_PWM_CONTROL_OFFSET, 0x00 पूर्ण,
	अणु MLXPLAT_CPLD_LPC_REG_WD_CLEAR_WP_OFFSET, 0x00 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष mlxplat_mlxcpld_regmap_comex_शेष[] = अणु
	अणु MLXPLAT_CPLD_LPC_REG_AGGRCX_MASK_OFFSET,
	  MLXPLAT_CPLD_LOW_AGGRCX_MASK पूर्ण,
	अणु MLXPLAT_CPLD_LPC_REG_PWM_CONTROL_OFFSET, 0x00 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष mlxplat_mlxcpld_regmap_ng400[] = अणु
	अणु MLXPLAT_CPLD_LPC_REG_PWM_CONTROL_OFFSET, 0x00 पूर्ण,
	अणु MLXPLAT_CPLD_LPC_REG_WD1_ACT_OFFSET, 0x00 पूर्ण,
	अणु MLXPLAT_CPLD_LPC_REG_WD2_ACT_OFFSET, 0x00 पूर्ण,
	अणु MLXPLAT_CPLD_LPC_REG_WD3_ACT_OFFSET, 0x00 पूर्ण,
पूर्ण;

काष्ठा mlxplat_mlxcpld_regmap_context अणु
	व्योम __iomem *base;
पूर्ण;

अटल काष्ठा mlxplat_mlxcpld_regmap_context mlxplat_mlxcpld_regmap_ctx;

अटल पूर्णांक
mlxplat_mlxcpld_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा mlxplat_mlxcpld_regmap_context *ctx = context;

	*val = ioपढ़ो8(ctx->base + reg);
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxplat_mlxcpld_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा mlxplat_mlxcpld_regmap_context *ctx = context;

	ioग_लिखो8(val, ctx->base + reg);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config mlxplat_mlxcpld_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 255,
	.cache_type = REGCACHE_FLAT,
	.ग_लिखोable_reg = mlxplat_mlxcpld_ग_लिखोable_reg,
	.पढ़ोable_reg = mlxplat_mlxcpld_पढ़ोable_reg,
	.अस्थिर_reg = mlxplat_mlxcpld_अस्थिर_reg,
	.reg_शेषs = mlxplat_mlxcpld_regmap_शेष,
	.num_reg_शेषs = ARRAY_SIZE(mlxplat_mlxcpld_regmap_शेष),
	.reg_पढ़ो = mlxplat_mlxcpld_reg_पढ़ो,
	.reg_ग_लिखो = mlxplat_mlxcpld_reg_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा regmap_config mlxplat_mlxcpld_regmap_config_ng = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 255,
	.cache_type = REGCACHE_FLAT,
	.ग_लिखोable_reg = mlxplat_mlxcpld_ग_लिखोable_reg,
	.पढ़ोable_reg = mlxplat_mlxcpld_पढ़ोable_reg,
	.अस्थिर_reg = mlxplat_mlxcpld_अस्थिर_reg,
	.reg_शेषs = mlxplat_mlxcpld_regmap_ng,
	.num_reg_शेषs = ARRAY_SIZE(mlxplat_mlxcpld_regmap_ng),
	.reg_पढ़ो = mlxplat_mlxcpld_reg_पढ़ो,
	.reg_ग_लिखो = mlxplat_mlxcpld_reg_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा regmap_config mlxplat_mlxcpld_regmap_config_comex = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 255,
	.cache_type = REGCACHE_FLAT,
	.ग_लिखोable_reg = mlxplat_mlxcpld_ग_लिखोable_reg,
	.पढ़ोable_reg = mlxplat_mlxcpld_पढ़ोable_reg,
	.अस्थिर_reg = mlxplat_mlxcpld_अस्थिर_reg,
	.reg_शेषs = mlxplat_mlxcpld_regmap_comex_शेष,
	.num_reg_शेषs = ARRAY_SIZE(mlxplat_mlxcpld_regmap_comex_शेष),
	.reg_पढ़ो = mlxplat_mlxcpld_reg_पढ़ो,
	.reg_ग_लिखो = mlxplat_mlxcpld_reg_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा regmap_config mlxplat_mlxcpld_regmap_config_ng400 = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 255,
	.cache_type = REGCACHE_FLAT,
	.ग_लिखोable_reg = mlxplat_mlxcpld_ग_लिखोable_reg,
	.पढ़ोable_reg = mlxplat_mlxcpld_पढ़ोable_reg,
	.अस्थिर_reg = mlxplat_mlxcpld_अस्थिर_reg,
	.reg_शेषs = mlxplat_mlxcpld_regmap_ng400,
	.num_reg_शेषs = ARRAY_SIZE(mlxplat_mlxcpld_regmap_ng400),
	.reg_पढ़ो = mlxplat_mlxcpld_reg_पढ़ो,
	.reg_ग_लिखो = mlxplat_mlxcpld_reg_ग_लिखो,
पूर्ण;

अटल काष्ठा resource mlxplat_mlxcpld_resources[] = अणु
	[0] = DEFINE_RES_IRQ_NAMED(17, "mlxreg-hotplug"),
पूर्ण;

अटल काष्ठा platक्रमm_device *mlxplat_dev;
अटल काष्ठा mlxreg_core_hotplug_platक्रमm_data *mlxplat_i2c;
अटल काष्ठा mlxreg_core_hotplug_platक्रमm_data *mlxplat_hotplug;
अटल काष्ठा mlxreg_core_platक्रमm_data *mlxplat_led;
अटल काष्ठा mlxreg_core_platक्रमm_data *mlxplat_regs_io;
अटल काष्ठा mlxreg_core_platक्रमm_data *mlxplat_fan;
अटल काष्ठा mlxreg_core_platक्रमm_data
	*mlxplat_wd_data[MLXPLAT_CPLD_WD_MAX_DEVS];
अटल स्थिर काष्ठा regmap_config *mlxplat_regmap_config;

अटल पूर्णांक __init mlxplat_dmi_शेष_matched(स्थिर काष्ठा dmi_प्रणाली_id *dmi)
अणु
	पूर्णांक i;

	mlxplat_max_adap_num = MLXPLAT_CPLD_MAX_PHYS_ADAPTER_NUM;
	mlxplat_mux_num = ARRAY_SIZE(mlxplat_शेष_mux_data);
	mlxplat_mux_data = mlxplat_शेष_mux_data;
	क्रम (i = 0; i < mlxplat_mux_num; i++) अणु
		mlxplat_mux_data[i].values = mlxplat_शेष_channels[i];
		mlxplat_mux_data[i].n_values =
				ARRAY_SIZE(mlxplat_शेष_channels[i]);
	पूर्ण
	mlxplat_hotplug = &mlxplat_mlxcpld_शेष_data;
	mlxplat_hotplug->deferred_nr =
		mlxplat_शेष_channels[i - 1][MLXPLAT_CPLD_GRP_CHNL_NUM - 1];
	mlxplat_led = &mlxplat_शेष_led_data;
	mlxplat_regs_io = &mlxplat_शेष_regs_io_data;
	mlxplat_wd_data[0] = &mlxplat_mlxcpld_wd_set_type1[0];

	वापस 1;
पूर्ण

अटल पूर्णांक __init mlxplat_dmi_msn21xx_matched(स्थिर काष्ठा dmi_प्रणाली_id *dmi)
अणु
	पूर्णांक i;

	mlxplat_max_adap_num = MLXPLAT_CPLD_MAX_PHYS_ADAPTER_NUM;
	mlxplat_mux_num = ARRAY_SIZE(mlxplat_शेष_mux_data);
	mlxplat_mux_data = mlxplat_शेष_mux_data;
	क्रम (i = 0; i < mlxplat_mux_num; i++) अणु
		mlxplat_mux_data[i].values = mlxplat_msn21xx_channels;
		mlxplat_mux_data[i].n_values =
				ARRAY_SIZE(mlxplat_msn21xx_channels);
	पूर्ण
	mlxplat_hotplug = &mlxplat_mlxcpld_msn21xx_data;
	mlxplat_hotplug->deferred_nr =
		mlxplat_msn21xx_channels[MLXPLAT_CPLD_GRP_CHNL_NUM - 1];
	mlxplat_led = &mlxplat_msn21xx_led_data;
	mlxplat_regs_io = &mlxplat_msn21xx_regs_io_data;
	mlxplat_wd_data[0] = &mlxplat_mlxcpld_wd_set_type1[0];

	वापस 1;
पूर्ण

अटल पूर्णांक __init mlxplat_dmi_msn274x_matched(स्थिर काष्ठा dmi_प्रणाली_id *dmi)
अणु
	पूर्णांक i;

	mlxplat_max_adap_num = MLXPLAT_CPLD_MAX_PHYS_ADAPTER_NUM;
	mlxplat_mux_num = ARRAY_SIZE(mlxplat_शेष_mux_data);
	mlxplat_mux_data = mlxplat_शेष_mux_data;
	क्रम (i = 0; i < mlxplat_mux_num; i++) अणु
		mlxplat_mux_data[i].values = mlxplat_msn21xx_channels;
		mlxplat_mux_data[i].n_values =
				ARRAY_SIZE(mlxplat_msn21xx_channels);
	पूर्ण
	mlxplat_hotplug = &mlxplat_mlxcpld_msn274x_data;
	mlxplat_hotplug->deferred_nr =
		mlxplat_msn21xx_channels[MLXPLAT_CPLD_GRP_CHNL_NUM - 1];
	mlxplat_led = &mlxplat_शेष_led_data;
	mlxplat_regs_io = &mlxplat_msn21xx_regs_io_data;
	mlxplat_wd_data[0] = &mlxplat_mlxcpld_wd_set_type1[0];

	वापस 1;
पूर्ण

अटल पूर्णांक __init mlxplat_dmi_msn201x_matched(स्थिर काष्ठा dmi_प्रणाली_id *dmi)
अणु
	पूर्णांक i;

	mlxplat_max_adap_num = MLXPLAT_CPLD_MAX_PHYS_ADAPTER_NUM;
	mlxplat_mux_num = ARRAY_SIZE(mlxplat_शेष_mux_data);
	mlxplat_mux_data = mlxplat_शेष_mux_data;
	क्रम (i = 0; i < mlxplat_mux_num; i++) अणु
		mlxplat_mux_data[i].values = mlxplat_msn21xx_channels;
		mlxplat_mux_data[i].n_values =
				ARRAY_SIZE(mlxplat_msn21xx_channels);
	पूर्ण
	mlxplat_hotplug = &mlxplat_mlxcpld_msn201x_data;
	mlxplat_hotplug->deferred_nr =
		mlxplat_शेष_channels[i - 1][MLXPLAT_CPLD_GRP_CHNL_NUM - 1];
	mlxplat_led = &mlxplat_msn21xx_led_data;
	mlxplat_regs_io = &mlxplat_msn21xx_regs_io_data;
	mlxplat_wd_data[0] = &mlxplat_mlxcpld_wd_set_type1[0];

	वापस 1;
पूर्ण

अटल पूर्णांक __init mlxplat_dmi_qmb7xx_matched(स्थिर काष्ठा dmi_प्रणाली_id *dmi)
अणु
	पूर्णांक i;

	mlxplat_max_adap_num = MLXPLAT_CPLD_MAX_PHYS_ADAPTER_NUM;
	mlxplat_mux_num = ARRAY_SIZE(mlxplat_शेष_mux_data);
	mlxplat_mux_data = mlxplat_शेष_mux_data;
	क्रम (i = 0; i < mlxplat_mux_num; i++) अणु
		mlxplat_mux_data[i].values = mlxplat_msn21xx_channels;
		mlxplat_mux_data[i].n_values =
				ARRAY_SIZE(mlxplat_msn21xx_channels);
	पूर्ण
	mlxplat_hotplug = &mlxplat_mlxcpld_शेष_ng_data;
	mlxplat_hotplug->deferred_nr =
		mlxplat_msn21xx_channels[MLXPLAT_CPLD_GRP_CHNL_NUM - 1];
	mlxplat_led = &mlxplat_शेष_ng_led_data;
	mlxplat_regs_io = &mlxplat_शेष_ng_regs_io_data;
	mlxplat_fan = &mlxplat_शेष_fan_data;
	क्रम (i = 0; i < ARRAY_SIZE(mlxplat_mlxcpld_wd_set_type2); i++)
		mlxplat_wd_data[i] = &mlxplat_mlxcpld_wd_set_type2[i];
	mlxplat_i2c = &mlxplat_mlxcpld_i2c_ng_data;
	mlxplat_regmap_config = &mlxplat_mlxcpld_regmap_config_ng;

	वापस 1;
पूर्ण

अटल पूर्णांक __init mlxplat_dmi_comex_matched(स्थिर काष्ठा dmi_प्रणाली_id *dmi)
अणु
	पूर्णांक i;

	mlxplat_max_adap_num = MLXPLAT_CPLD_MAX_PHYS_EXT_ADAPTER_NUM;
	mlxplat_mux_num = ARRAY_SIZE(mlxplat_extended_mux_data);
	mlxplat_mux_data = mlxplat_extended_mux_data;
	क्रम (i = 0; i < mlxplat_mux_num; i++) अणु
		mlxplat_mux_data[i].values = mlxplat_msn21xx_channels;
		mlxplat_mux_data[i].n_values =
				ARRAY_SIZE(mlxplat_msn21xx_channels);
	पूर्ण
	mlxplat_hotplug = &mlxplat_mlxcpld_comex_data;
	mlxplat_hotplug->deferred_nr = MLXPLAT_CPLD_MAX_PHYS_EXT_ADAPTER_NUM;
	mlxplat_led = &mlxplat_comex_100G_led_data;
	mlxplat_regs_io = &mlxplat_शेष_ng_regs_io_data;
	mlxplat_fan = &mlxplat_शेष_fan_data;
	क्रम (i = 0; i < ARRAY_SIZE(mlxplat_mlxcpld_wd_set_type2); i++)
		mlxplat_wd_data[i] = &mlxplat_mlxcpld_wd_set_type2[i];
	mlxplat_regmap_config = &mlxplat_mlxcpld_regmap_config_comex;

	वापस 1;
पूर्ण

अटल पूर्णांक __init mlxplat_dmi_ng400_matched(स्थिर काष्ठा dmi_प्रणाली_id *dmi)
अणु
	पूर्णांक i;

	mlxplat_max_adap_num = MLXPLAT_CPLD_MAX_PHYS_ADAPTER_NUM;
	mlxplat_mux_num = ARRAY_SIZE(mlxplat_शेष_mux_data);
	mlxplat_mux_data = mlxplat_शेष_mux_data;
	क्रम (i = 0; i < mlxplat_mux_num; i++) अणु
		mlxplat_mux_data[i].values = mlxplat_msn21xx_channels;
		mlxplat_mux_data[i].n_values =
				ARRAY_SIZE(mlxplat_msn21xx_channels);
	पूर्ण
	mlxplat_hotplug = &mlxplat_mlxcpld_ext_data;
	mlxplat_hotplug->deferred_nr =
		mlxplat_msn21xx_channels[MLXPLAT_CPLD_GRP_CHNL_NUM - 1];
	mlxplat_led = &mlxplat_शेष_ng_led_data;
	mlxplat_regs_io = &mlxplat_शेष_ng_regs_io_data;
	mlxplat_fan = &mlxplat_शेष_fan_data;
	क्रम (i = 0; i < ARRAY_SIZE(mlxplat_mlxcpld_wd_set_type2); i++)
		mlxplat_wd_data[i] = &mlxplat_mlxcpld_wd_set_type2[i];
	mlxplat_i2c = &mlxplat_mlxcpld_i2c_ng_data;
	mlxplat_regmap_config = &mlxplat_mlxcpld_regmap_config_ng400;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id mlxplat_dmi_table[] __initस्थिर = अणु
	अणु
		.callback = mlxplat_dmi_शेष_matched,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "VMOD0001"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = mlxplat_dmi_msn21xx_matched,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "VMOD0002"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = mlxplat_dmi_msn274x_matched,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "VMOD0003"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = mlxplat_dmi_msn201x_matched,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "VMOD0004"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = mlxplat_dmi_qmb7xx_matched,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "VMOD0005"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = mlxplat_dmi_qmb7xx_matched,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "VMOD0007"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = mlxplat_dmi_comex_matched,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "VMOD0009"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = mlxplat_dmi_ng400_matched,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "VMOD0010"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = mlxplat_dmi_msn274x_matched,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Mellanox Technologies"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MSN274"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = mlxplat_dmi_शेष_matched,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Mellanox Technologies"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MSN24"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = mlxplat_dmi_शेष_matched,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Mellanox Technologies"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MSN27"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = mlxplat_dmi_शेष_matched,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Mellanox Technologies"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MSB"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = mlxplat_dmi_शेष_matched,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Mellanox Technologies"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MSX"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = mlxplat_dmi_msn21xx_matched,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Mellanox Technologies"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MSN21"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = mlxplat_dmi_msn201x_matched,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Mellanox Technologies"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MSN201"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = mlxplat_dmi_qmb7xx_matched,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Mellanox Technologies"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MQM87"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = mlxplat_dmi_qmb7xx_matched,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Mellanox Technologies"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MSN37"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = mlxplat_dmi_qmb7xx_matched,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Mellanox Technologies"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MSN34"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = mlxplat_dmi_qmb7xx_matched,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Mellanox Technologies"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MSN38"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(dmi, mlxplat_dmi_table);

अटल पूर्णांक mlxplat_mlxcpld_verअगरy_bus_topology(पूर्णांक *nr)
अणु
	काष्ठा i2c_adapter *search_adap;
	पूर्णांक shअगरt, i;

	/* Scan adapters from expected id to verअगरy it is मुक्त. */
	*nr = MLXPLAT_CPLD_PHYS_ADAPTER_DEF_NR;
	क्रम (i = MLXPLAT_CPLD_PHYS_ADAPTER_DEF_NR; i <
	     mlxplat_max_adap_num; i++) अणु
		search_adap = i2c_get_adapter(i);
		अगर (search_adap) अणु
			i2c_put_adapter(search_adap);
			जारी;
		पूर्ण

		/* Return अगर expected parent adapter is मुक्त. */
		अगर (i == MLXPLAT_CPLD_PHYS_ADAPTER_DEF_NR)
			वापस 0;
		अवरोध;
	पूर्ण

	/* Return with error अगर मुक्त id क्रम adapter is not found. */
	अगर (i == mlxplat_max_adap_num)
		वापस -ENODEV;

	/* Shअगरt adapter ids, since expected parent adapter is not मुक्त. */
	*nr = i;
	क्रम (i = 0; i < mlxplat_mux_num; i++) अणु
		shअगरt = *nr - mlxplat_mux_data[i].parent;
		mlxplat_mux_data[i].parent = *nr;
		mlxplat_mux_data[i].base_nr += shअगरt;
		अगर (shअगरt > 0)
			mlxplat_hotplug->shअगरt_nr = shअगरt;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxplat_mlxcpld_check_wd_capability(व्योम *regmap)
अणु
	u32 regval;
	पूर्णांक i, rc;

	rc = regmap_पढ़ो(regmap, MLXPLAT_CPLD_LPC_REG_PSU_I2C_CAP_OFFSET,
			 &regval);
	अगर (rc)
		वापस rc;

	अगर (!(regval & ~MLXPLAT_CPLD_WD_CPBLTY_MASK)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(mlxplat_mlxcpld_wd_set_type3); i++) अणु
			अगर (mlxplat_wd_data[i])
				mlxplat_wd_data[i] =
					&mlxplat_mlxcpld_wd_set_type3[i];
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init mlxplat_init(व्योम)
अणु
	काष्ठा mlxplat_priv *priv;
	पूर्णांक i, j, nr, err;

	अगर (!dmi_check_प्रणाली(mlxplat_dmi_table))
		वापस -ENODEV;

	mlxplat_dev = platक्रमm_device_रेजिस्टर_simple(MLX_PLAT_DEVICE_NAME, -1,
					mlxplat_lpc_resources,
					ARRAY_SIZE(mlxplat_lpc_resources));

	अगर (IS_ERR(mlxplat_dev))
		वापस PTR_ERR(mlxplat_dev);

	priv = devm_kzalloc(&mlxplat_dev->dev, माप(काष्ठा mlxplat_priv),
			    GFP_KERNEL);
	अगर (!priv) अणु
		err = -ENOMEM;
		जाओ fail_alloc;
	पूर्ण
	platक्रमm_set_drvdata(mlxplat_dev, priv);

	mlxplat_mlxcpld_regmap_ctx.base = devm_ioport_map(&mlxplat_dev->dev,
			       mlxplat_lpc_resources[1].start, 1);
	अगर (!mlxplat_mlxcpld_regmap_ctx.base) अणु
		err = -ENOMEM;
		जाओ fail_alloc;
	पूर्ण

	अगर (!mlxplat_regmap_config)
		mlxplat_regmap_config = &mlxplat_mlxcpld_regmap_config;

	priv->regmap = devm_regmap_init(&mlxplat_dev->dev, शून्य,
					&mlxplat_mlxcpld_regmap_ctx,
					mlxplat_regmap_config);
	अगर (IS_ERR(priv->regmap)) अणु
		err = PTR_ERR(priv->regmap);
		जाओ fail_alloc;
	पूर्ण

	err = mlxplat_mlxcpld_verअगरy_bus_topology(&nr);
	अगर (nr < 0)
		जाओ fail_alloc;

	nr = (nr == mlxplat_max_adap_num) ? -1 : nr;
	अगर (mlxplat_i2c)
		mlxplat_i2c->regmap = priv->regmap;
	priv->pdev_i2c = platक्रमm_device_रेजिस्टर_resndata(
					&mlxplat_dev->dev, "i2c_mlxcpld",
					nr, mlxplat_mlxcpld_resources,
					ARRAY_SIZE(mlxplat_mlxcpld_resources),
					mlxplat_i2c, माप(*mlxplat_i2c));
	अगर (IS_ERR(priv->pdev_i2c)) अणु
		err = PTR_ERR(priv->pdev_i2c);
		जाओ fail_alloc;
	पूर्ण

	क्रम (i = 0; i < mlxplat_mux_num; i++) अणु
		priv->pdev_mux[i] = platक्रमm_device_रेजिस्टर_resndata(
						&priv->pdev_i2c->dev,
						"i2c-mux-reg", i, शून्य,
						0, &mlxplat_mux_data[i],
						माप(mlxplat_mux_data[i]));
		अगर (IS_ERR(priv->pdev_mux[i])) अणु
			err = PTR_ERR(priv->pdev_mux[i]);
			जाओ fail_platक्रमm_mux_रेजिस्टर;
		पूर्ण
	पूर्ण

	/* Add hotplug driver */
	mlxplat_hotplug->regmap = priv->regmap;
	priv->pdev_hotplug = platक्रमm_device_रेजिस्टर_resndata(
				&mlxplat_dev->dev, "mlxreg-hotplug",
				PLATFORM_DEVID_NONE,
				mlxplat_mlxcpld_resources,
				ARRAY_SIZE(mlxplat_mlxcpld_resources),
				mlxplat_hotplug, माप(*mlxplat_hotplug));
	अगर (IS_ERR(priv->pdev_hotplug)) अणु
		err = PTR_ERR(priv->pdev_hotplug);
		जाओ fail_platक्रमm_mux_रेजिस्टर;
	पूर्ण

	/* Set शेष रेजिस्टरs. */
	क्रम (j = 0; j <  mlxplat_regmap_config->num_reg_शेषs; j++) अणु
		err = regmap_ग_लिखो(priv->regmap,
				   mlxplat_regmap_config->reg_शेषs[j].reg,
				   mlxplat_regmap_config->reg_शेषs[j].def);
		अगर (err)
			जाओ fail_platक्रमm_mux_रेजिस्टर;
	पूर्ण

	/* Add LED driver. */
	mlxplat_led->regmap = priv->regmap;
	priv->pdev_led = platक्रमm_device_रेजिस्टर_resndata(
				&mlxplat_dev->dev, "leds-mlxreg",
				PLATFORM_DEVID_NONE, शून्य, 0,
				mlxplat_led, माप(*mlxplat_led));
	अगर (IS_ERR(priv->pdev_led)) अणु
		err = PTR_ERR(priv->pdev_led);
		जाओ fail_platक्रमm_hotplug_रेजिस्टर;
	पूर्ण

	/* Add रेजिस्टरs io access driver. */
	अगर (mlxplat_regs_io) अणु
		mlxplat_regs_io->regmap = priv->regmap;
		priv->pdev_io_regs = platक्रमm_device_रेजिस्टर_resndata(
					&mlxplat_dev->dev, "mlxreg-io",
					PLATFORM_DEVID_NONE, शून्य, 0,
					mlxplat_regs_io,
					माप(*mlxplat_regs_io));
		अगर (IS_ERR(priv->pdev_io_regs)) अणु
			err = PTR_ERR(priv->pdev_io_regs);
			जाओ fail_platक्रमm_led_रेजिस्टर;
		पूर्ण
	पूर्ण

	/* Add FAN driver. */
	अगर (mlxplat_fan) अणु
		mlxplat_fan->regmap = priv->regmap;
		priv->pdev_fan = platक्रमm_device_रेजिस्टर_resndata(
					&mlxplat_dev->dev, "mlxreg-fan",
					PLATFORM_DEVID_NONE, शून्य, 0,
					mlxplat_fan,
					माप(*mlxplat_fan));
		अगर (IS_ERR(priv->pdev_fan)) अणु
			err = PTR_ERR(priv->pdev_fan);
			जाओ fail_platक्रमm_io_regs_रेजिस्टर;
		पूर्ण
	पूर्ण

	/* Add WD drivers. */
	err = mlxplat_mlxcpld_check_wd_capability(priv->regmap);
	अगर (err)
		जाओ fail_platक्रमm_wd_रेजिस्टर;
	क्रम (j = 0; j < MLXPLAT_CPLD_WD_MAX_DEVS; j++) अणु
		अगर (mlxplat_wd_data[j]) अणु
			mlxplat_wd_data[j]->regmap = priv->regmap;
			priv->pdev_wd[j] = platक्रमm_device_रेजिस्टर_resndata(
						&mlxplat_dev->dev, "mlx-wdt",
						j, शून्य, 0,
						mlxplat_wd_data[j],
						माप(*mlxplat_wd_data[j]));
			अगर (IS_ERR(priv->pdev_wd[j])) अणु
				err = PTR_ERR(priv->pdev_wd[j]);
				जाओ fail_platक्रमm_wd_रेजिस्टर;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Sync रेजिस्टरs with hardware. */
	regcache_mark_dirty(priv->regmap);
	err = regcache_sync(priv->regmap);
	अगर (err)
		जाओ fail_platक्रमm_wd_रेजिस्टर;

	वापस 0;

fail_platक्रमm_wd_रेजिस्टर:
	जबतक (--j >= 0)
		platक्रमm_device_unरेजिस्टर(priv->pdev_wd[j]);
	अगर (mlxplat_fan)
		platक्रमm_device_unरेजिस्टर(priv->pdev_fan);
fail_platक्रमm_io_regs_रेजिस्टर:
	अगर (mlxplat_regs_io)
		platक्रमm_device_unरेजिस्टर(priv->pdev_io_regs);
fail_platक्रमm_led_रेजिस्टर:
	platक्रमm_device_unरेजिस्टर(priv->pdev_led);
fail_platक्रमm_hotplug_रेजिस्टर:
	platक्रमm_device_unरेजिस्टर(priv->pdev_hotplug);
fail_platक्रमm_mux_रेजिस्टर:
	जबतक (--i >= 0)
		platक्रमm_device_unरेजिस्टर(priv->pdev_mux[i]);
	platक्रमm_device_unरेजिस्टर(priv->pdev_i2c);
fail_alloc:
	platक्रमm_device_unरेजिस्टर(mlxplat_dev);

	वापस err;
पूर्ण
module_init(mlxplat_init);

अटल व्योम __निकास mlxplat_निकास(व्योम)
अणु
	काष्ठा mlxplat_priv *priv = platक्रमm_get_drvdata(mlxplat_dev);
	पूर्णांक i;

	क्रम (i = MLXPLAT_CPLD_WD_MAX_DEVS - 1; i >= 0 ; i--)
		platक्रमm_device_unरेजिस्टर(priv->pdev_wd[i]);
	अगर (priv->pdev_fan)
		platक्रमm_device_unरेजिस्टर(priv->pdev_fan);
	अगर (priv->pdev_io_regs)
		platक्रमm_device_unरेजिस्टर(priv->pdev_io_regs);
	platक्रमm_device_unरेजिस्टर(priv->pdev_led);
	platक्रमm_device_unरेजिस्टर(priv->pdev_hotplug);

	क्रम (i = mlxplat_mux_num - 1; i >= 0 ; i--)
		platक्रमm_device_unरेजिस्टर(priv->pdev_mux[i]);

	platक्रमm_device_unरेजिस्टर(priv->pdev_i2c);
	platक्रमm_device_unरेजिस्टर(mlxplat_dev);
पूर्ण
module_निकास(mlxplat_निकास);

MODULE_AUTHOR("Vadim Pasternak (vadimp@mellanox.com)");
MODULE_DESCRIPTION("Mellanox platform driver");
MODULE_LICENSE("Dual BSD/GPL");
