<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * rk3328 ALSA SoC Audio driver
 *
 * Copyright (c) 2017, Fuzhou Rockchip Electronics Co., Ltd All rights reserved.
 */

#अगर_अघोषित _RK3328_CODEC_H
#घोषणा _RK3328_CODEC_H

#समावेश <linux/bitfield.h>

/* codec रेजिस्टर */
#घोषणा CODEC_RESET			(0x00 << 2)
#घोषणा DAC_INIT_CTRL1			(0x03 << 2)
#घोषणा DAC_INIT_CTRL2			(0x04 << 2)
#घोषणा DAC_INIT_CTRL3			(0x05 << 2)
#घोषणा DAC_PRECHARGE_CTRL		(0x22 << 2)
#घोषणा DAC_PWR_CTRL			(0x23 << 2)
#घोषणा DAC_CLK_CTRL			(0x24 << 2)
#घोषणा HPMIX_CTRL			(0x25 << 2)
#घोषणा DAC_SELECT			(0x26 << 2)
#घोषणा HPOUT_CTRL			(0x27 << 2)
#घोषणा HPOUTL_GAIN_CTRL		(0x28 << 2)
#घोषणा HPOUTR_GAIN_CTRL		(0x29 << 2)
#घोषणा HPOUT_POP_CTRL			(0x2a << 2)

/* REG00: CODEC_RESET */
#घोषणा PWR_RST_BYPASS_DIS		(0x0 << 6)
#घोषणा PWR_RST_BYPASS_EN		(0x1 << 6)
#घोषणा DIG_CORE_RST			(0x0 << 1)
#घोषणा DIG_CORE_WORK			(0x1 << 1)
#घोषणा SYS_RST				(0x0 << 0)
#घोषणा SYS_WORK			(0x1 << 0)

/* REG03: DAC_INIT_CTRL1 */
#घोषणा PIN_सूचीECTION_MASK		BIT(5)
#घोषणा PIN_सूचीECTION_IN		(0x0 << 5)
#घोषणा PIN_सूचीECTION_OUT		(0x1 << 5)
#घोषणा DAC_I2S_MODE_MASK		BIT(4)
#घोषणा DAC_I2S_MODE_SLAVE		(0x0 << 4)
#घोषणा DAC_I2S_MODE_MASTER		(0x1 << 4)

/* REG04: DAC_INIT_CTRL2 */
#घोषणा DAC_I2S_LRP_MASK		BIT(7)
#घोषणा DAC_I2S_LRP_NORMAL		(0x0 << 7)
#घोषणा DAC_I2S_LRP_REVERSAL		(0x1 << 7)
#घोषणा DAC_VDL_MASK			GENMASK(6, 5)
#घोषणा DAC_VDL_16BITS			(0x0 << 5)
#घोषणा DAC_VDL_20BITS			(0x1 << 5)
#घोषणा DAC_VDL_24BITS			(0x2 << 5)
#घोषणा DAC_VDL_32BITS			(0x3 << 5)
#घोषणा DAC_MODE_MASK			GENMASK(4, 3)
#घोषणा DAC_MODE_RJM			(0x0 << 3)
#घोषणा DAC_MODE_LJM			(0x1 << 3)
#घोषणा DAC_MODE_I2S			(0x2 << 3)
#घोषणा DAC_MODE_PCM			(0x3 << 3)
#घोषणा DAC_LR_SWAP_MASK		BIT(2)
#घोषणा DAC_LR_SWAP_DIS			(0x0 << 2)
#घोषणा DAC_LR_SWAP_EN			(0x1 << 2)

/* REG05: DAC_INIT_CTRL3 */
#घोषणा DAC_WL_MASK			GENMASK(3, 2)
#घोषणा DAC_WL_16BITS			(0x0 << 2)
#घोषणा DAC_WL_20BITS			(0x1 << 2)
#घोषणा DAC_WL_24BITS			(0x2 << 2)
#घोषणा DAC_WL_32BITS			(0x3 << 2)
#घोषणा DAC_RST_MASK			BIT(1)
#घोषणा DAC_RST_EN			(0x0 << 1)
#घोषणा DAC_RST_DIS			(0x1 << 1)
#घोषणा DAC_BCP_MASK			BIT(0)
#घोषणा DAC_BCP_NORMAL			(0x0 << 0)
#घोषणा DAC_BCP_REVERSAL		(0x1 << 0)

/* REG22: DAC_PRECHARGE_CTRL */
#घोषणा DAC_CHARGE_XCHARGE_MASK		BIT(7)
#घोषणा DAC_CHARGE_DISCHARGE		(0x0 << 7)
#घोषणा DAC_CHARGE_PRECHARGE		(0x1 << 7)
#घोषणा DAC_CHARGE_CURRENT_64I_MASK	BIT(6)
#घोषणा DAC_CHARGE_CURRENT_64I		(0x1 << 6)
#घोषणा DAC_CHARGE_CURRENT_32I_MASK	BIT(5)
#घोषणा DAC_CHARGE_CURRENT_32I		(0x1 << 5)
#घोषणा DAC_CHARGE_CURRENT_16I_MASK	BIT(4)
#घोषणा DAC_CHARGE_CURRENT_16I		(0x1 << 4)
#घोषणा DAC_CHARGE_CURRENT_08I_MASK	BIT(3)
#घोषणा DAC_CHARGE_CURRENT_08I		(0x1 << 3)
#घोषणा DAC_CHARGE_CURRENT_04I_MASK	BIT(2)
#घोषणा DAC_CHARGE_CURRENT_04I		(0x1 << 2)
#घोषणा DAC_CHARGE_CURRENT_02I_MASK	BIT(1)
#घोषणा DAC_CHARGE_CURRENT_02I		(0x1 << 1)
#घोषणा DAC_CHARGE_CURRENT_I_MASK	BIT(0)
#घोषणा DAC_CHARGE_CURRENT_I		(0x1 << 0)
#घोषणा DAC_CHARGE_CURRENT_ALL_MASK	GENMASK(6, 0)
#घोषणा DAC_CHARGE_CURRENT_ALL_OFF	0x00
#घोषणा DAC_CHARGE_CURRENT_ALL_ON	0x7f

/* REG23: DAC_PWR_CTRL */
#घोषणा DAC_PWR_MASK			BIT(6)
#घोषणा DAC_PWR_OFF			(0x0 << 6)
#घोषणा DAC_PWR_ON			(0x1 << 6)
#घोषणा DACL_PATH_REFV_MASK		BIT(5)
#घोषणा DACL_PATH_REFV_OFF		(0x0 << 5)
#घोषणा DACL_PATH_REFV_ON		(0x1 << 5)
#घोषणा HPOUTL_ZERO_CROSSING_MASK	BIT(4)
#घोषणा HPOUTL_ZERO_CROSSING_OFF	(0x0 << 4)
#घोषणा HPOUTL_ZERO_CROSSING_ON		(0x1 << 4)
#घोषणा DACR_PATH_REFV_MASK		BIT(1)
#घोषणा DACR_PATH_REFV_OFF		(0x0 << 1)
#घोषणा DACR_PATH_REFV_ON		(0x1 << 1)
#घोषणा HPOUTR_ZERO_CROSSING_MASK	BIT(0)
#घोषणा HPOUTR_ZERO_CROSSING_OFF	(0x0 << 0)
#घोषणा HPOUTR_ZERO_CROSSING_ON		(0x1 << 0)

/* REG24: DAC_CLK_CTRL */
#घोषणा DACL_REFV_MASK			BIT(7)
#घोषणा DACL_REFV_OFF			(0x0 << 7)
#घोषणा DACL_REFV_ON			(0x1 << 7)
#घोषणा DACL_CLK_MASK			BIT(6)
#घोषणा DACL_CLK_OFF			(0x0 << 6)
#घोषणा DACL_CLK_ON			(0x1 << 6)
#घोषणा DACL_MASK			BIT(5)
#घोषणा DACL_OFF			(0x0 << 5)
#घोषणा DACL_ON				(0x1 << 5)
#घोषणा DACL_INIT_MASK			BIT(4)
#घोषणा DACL_INIT_OFF			(0x0 << 4)
#घोषणा DACL_INIT_ON			(0x1 << 4)
#घोषणा DACR_REFV_MASK			BIT(3)
#घोषणा DACR_REFV_OFF			(0x0 << 3)
#घोषणा DACR_REFV_ON			(0x1 << 3)
#घोषणा DACR_CLK_MASK			BIT(2)
#घोषणा DACR_CLK_OFF			(0x0 << 2)
#घोषणा DACR_CLK_ON			(0x1 << 2)
#घोषणा DACR_MASK			BIT(1)
#घोषणा DACR_OFF			(0x0 << 1)
#घोषणा DACR_ON				(0x1 << 1)
#घोषणा DACR_INIT_MASK			BIT(0)
#घोषणा DACR_INIT_OFF			(0x0 << 0)
#घोषणा DACR_INIT_ON			(0x1 << 0)

/* REG25: HPMIX_CTRL*/
#घोषणा HPMIXL_MASK			BIT(6)
#घोषणा HPMIXL_DIS			(0x0 << 6)
#घोषणा HPMIXL_EN			(0x1 << 6)
#घोषणा HPMIXL_INIT_MASK		BIT(5)
#घोषणा HPMIXL_INIT_DIS			(0x0 << 5)
#घोषणा HPMIXL_INIT_EN			(0x1 << 5)
#घोषणा HPMIXL_INIT2_MASK		BIT(4)
#घोषणा HPMIXL_INIT2_DIS		(0x0 << 4)
#घोषणा HPMIXL_INIT2_EN			(0x1 << 4)
#घोषणा HPMIXR_MASK			BIT(2)
#घोषणा HPMIXR_DIS			(0x0 << 2)
#घोषणा HPMIXR_EN			(0x1 << 2)
#घोषणा HPMIXR_INIT_MASK		BIT(1)
#घोषणा HPMIXR_INIT_DIS			(0x0 << 1)
#घोषणा HPMIXR_INIT_EN			(0x1 << 1)
#घोषणा HPMIXR_INIT2_MASK		BIT(0)
#घोषणा HPMIXR_INIT2_DIS		(0x0 << 0)
#घोषणा HPMIXR_INIT2_EN			(0x1 << 0)

/* REG26: DAC_SELECT */
#घोषणा DACL_SELECT_MASK		BIT(4)
#घोषणा DACL_UNSELECT			(0x0 << 4)
#घोषणा DACL_SELECT			(0x1 << 4)
#घोषणा DACR_SELECT_MASK		BIT(0)
#घोषणा DACR_UNSELECT			(0x0 << 0)
#घोषणा DACR_SELECT			(0x1 << 0)

/* REG27: HPOUT_CTRL */
#घोषणा HPOUTL_MASK			BIT(7)
#घोषणा HPOUTL_DIS			(0x0 << 7)
#घोषणा HPOUTL_EN			(0x1 << 7)
#घोषणा HPOUTL_INIT_MASK		BIT(6)
#घोषणा HPOUTL_INIT_DIS			(0x0 << 6)
#घोषणा HPOUTL_INIT_EN			(0x1 << 6)
#घोषणा HPOUTL_MUTE_MASK		BIT(5)
#घोषणा HPOUTL_MUTE			(0x0 << 5)
#घोषणा HPOUTL_UNMUTE			(0x1 << 5)
#घोषणा HPOUTR_MASK			BIT(4)
#घोषणा HPOUTR_DIS			(0x0 << 4)
#घोषणा HPOUTR_EN			(0x1 << 4)
#घोषणा HPOUTR_INIT_MASK		BIT(3)
#घोषणा HPOUTR_INIT_DIS			(0x0 << 3)
#घोषणा HPOUTR_INIT_EN			(0x1 << 3)
#घोषणा HPOUTR_MUTE_MASK		BIT(2)
#घोषणा HPOUTR_MUTE			(0x0 << 2)
#घोषणा HPOUTR_UNMUTE			(0x1 << 2)

/* REG28: HPOUTL_GAIN_CTRL */
#घोषणा HPOUTL_GAIN_MASK		GENMASK(4, 0)

/* REG29: HPOUTR_GAIN_CTRL */
#घोषणा HPOUTR_GAIN_MASK		GENMASK(4, 0)

/* REG2a: HPOUT_POP_CTRL */
#घोषणा HPOUTR_POP_MASK			GENMASK(5, 4)
#घोषणा HPOUTR_POP_XCHARGE		(0x1 << 4)
#घोषणा HPOUTR_POP_WORK			(0x2 << 4)
#घोषणा HPOUTL_POP_MASK			GENMASK(1, 0)
#घोषणा HPOUTL_POP_XCHARGE		(0x1 << 0)
#घोषणा HPOUTL_POP_WORK			(0x2 << 0)

#घोषणा RK3328_HIFI			0

काष्ठा rk3328_reg_msk_val अणु
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक msk;
	अचिन्हित पूर्णांक val;
पूर्ण;

#पूर्ण_अगर
