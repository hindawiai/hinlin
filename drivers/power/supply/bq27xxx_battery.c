<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * BQ27xxx battery driver
 *
 * Copyright (C) 2008 Roकरोlfo Giometti <giometti@linux.it>
 * Copyright (C) 2008 Eurotech S.p.A. <info@eurotech.it>
 * Copyright (C) 2010-2011 Lars-Peter Clausen <lars@metafoo.de>
 * Copyright (C) 2011 Pali Rohथँr <pali@kernel.org>
 * Copyright (C) 2017 Liam Breck <kernel@networkimprov.net>
 *
 * Based on a previous work by Copyright (C) 2008 Texas Instruments, Inc.
 *
 * Datasheets:
 * https://www.ti.com/product/bq27000
 * https://www.ti.com/product/bq27200
 * https://www.ti.com/product/bq27010
 * https://www.ti.com/product/bq27210
 * https://www.ti.com/product/bq27500
 * https://www.ti.com/product/bq27510-g1
 * https://www.ti.com/product/bq27510-g2
 * https://www.ti.com/product/bq27510-g3
 * https://www.ti.com/product/bq27520-g1
 * https://www.ti.com/product/bq27520-g2
 * https://www.ti.com/product/bq27520-g3
 * https://www.ti.com/product/bq27520-g4
 * https://www.ti.com/product/bq27530-g1
 * https://www.ti.com/product/bq27531-g1
 * https://www.ti.com/product/bq27541-g1
 * https://www.ti.com/product/bq27542-g1
 * https://www.ti.com/product/bq27546-g1
 * https://www.ti.com/product/bq27742-g1
 * https://www.ti.com/product/bq27545-g1
 * https://www.ti.com/product/bq27421-g1
 * https://www.ti.com/product/bq27425-g1
 * https://www.ti.com/product/bq27426
 * https://www.ti.com/product/bq27411-g1
 * https://www.ti.com/product/bq27441-g1
 * https://www.ti.com/product/bq27621-g1
 * https://www.ti.com/product/bq27z561
 * https://www.ti.com/product/bq28z610
 * https://www.ti.com/product/bq34z100-g1
 * https://www.ti.com/product/bq78z100
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/param.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>

#समावेश <linux/घातer/bq27xxx_battery.h>

#घोषणा BQ27XXX_MANUFACTURER	"Texas Instruments"

/* BQ27XXX Flags */
#घोषणा BQ27XXX_FLAG_DSC	BIT(0)
#घोषणा BQ27XXX_FLAG_SOCF	BIT(1) /* State-of-Charge threshold final */
#घोषणा BQ27XXX_FLAG_SOC1	BIT(2) /* State-of-Charge threshold 1 */
#घोषणा BQ27XXX_FLAG_CFGUP	BIT(4)
#घोषणा BQ27XXX_FLAG_FC		BIT(9)
#घोषणा BQ27XXX_FLAG_OTD	BIT(14)
#घोषणा BQ27XXX_FLAG_OTC	BIT(15)
#घोषणा BQ27XXX_FLAG_UT		BIT(14)
#घोषणा BQ27XXX_FLAG_OT		BIT(15)

/* BQ27000 has dअगरferent layout क्रम Flags रेजिस्टर */
#घोषणा BQ27000_FLAG_EDVF	BIT(0) /* Final End-of-Disअक्षरge-Voltage flag */
#घोषणा BQ27000_FLAG_EDV1	BIT(1) /* First End-of-Disअक्षरge-Voltage flag */
#घोषणा BQ27000_FLAG_CI		BIT(4) /* Capacity Inaccurate flag */
#घोषणा BQ27000_FLAG_FC		BIT(5)
#घोषणा BQ27000_FLAG_CHGS	BIT(7) /* Charge state flag */

/* BQ27Z561 has dअगरferent layout क्रम Flags रेजिस्टर */
#घोषणा BQ27Z561_FLAG_FDC	BIT(4) /* Battery fully disअक्षरged */
#घोषणा BQ27Z561_FLAG_FC	BIT(5) /* Battery fully अक्षरged */
#घोषणा BQ27Z561_FLAG_DIS_CH	BIT(6) /* Battery is disअक्षरging */

/* control रेजिस्टर params */
#घोषणा BQ27XXX_SEALED			0x20
#घोषणा BQ27XXX_SET_CFGUPDATE		0x13
#घोषणा BQ27XXX_SOFT_RESET		0x42
#घोषणा BQ27XXX_RESET			0x41

#घोषणा BQ27XXX_RS			(20) /* Resistor sense mOhm */
#घोषणा BQ27XXX_POWER_CONSTANT		(29200) /* 29.2 तगV^2 * 1000 */
#घोषणा BQ27XXX_CURRENT_CONSTANT	(3570) /* 3.57 तगV * 1000 */

#घोषणा INVALID_REG_ADDR	0xff

/*
 * bq27xxx_reg_index - Register names
 *
 * These are indexes पूर्णांकo a device's रेजिस्टर mapping array.
 */

क्रमागत bq27xxx_reg_index अणु
	BQ27XXX_REG_CTRL = 0,	/* Control */
	BQ27XXX_REG_TEMP,	/* Temperature */
	BQ27XXX_REG_INT_TEMP,	/* Internal Temperature */
	BQ27XXX_REG_VOLT,	/* Voltage */
	BQ27XXX_REG_AI,		/* Average Current */
	BQ27XXX_REG_FLAGS,	/* Flags */
	BQ27XXX_REG_TTE,	/* Time-to-Empty */
	BQ27XXX_REG_TTF,	/* Time-to-Full */
	BQ27XXX_REG_TTES,	/* Time-to-Empty Standby */
	BQ27XXX_REG_TTECP,	/* Time-to-Empty at Constant Power */
	BQ27XXX_REG_NAC,	/* Nominal Available Capacity */
	BQ27XXX_REG_RC,		/* Reमुख्यing Capacity */
	BQ27XXX_REG_FCC,	/* Full Charge Capacity */
	BQ27XXX_REG_CYCT,	/* Cycle Count */
	BQ27XXX_REG_AE,		/* Available Energy */
	BQ27XXX_REG_SOC,	/* State-of-Charge */
	BQ27XXX_REG_DCAP,	/* Design Capacity */
	BQ27XXX_REG_AP,		/* Average Power */
	BQ27XXX_DM_CTRL,	/* Block Data Control */
	BQ27XXX_DM_CLASS,	/* Data Class */
	BQ27XXX_DM_BLOCK,	/* Data Block */
	BQ27XXX_DM_DATA,	/* Block Data */
	BQ27XXX_DM_CKSUM,	/* Block Data Checksum */
	BQ27XXX_REG_MAX,	/* sentinel */
पूर्ण;

#घोषणा BQ27XXX_DM_REG_ROWS \
	[BQ27XXX_DM_CTRL] = 0x61,  \
	[BQ27XXX_DM_CLASS] = 0x3e, \
	[BQ27XXX_DM_BLOCK] = 0x3f, \
	[BQ27XXX_DM_DATA] = 0x40,  \
	[BQ27XXX_DM_CKSUM] = 0x60

/* Register mappings */
अटल u8
	bq27000_regs[BQ27XXX_REG_MAX] = अणु
		[BQ27XXX_REG_CTRL] = 0x00,
		[BQ27XXX_REG_TEMP] = 0x06,
		[BQ27XXX_REG_INT_TEMP] = INVALID_REG_ADDR,
		[BQ27XXX_REG_VOLT] = 0x08,
		[BQ27XXX_REG_AI] = 0x14,
		[BQ27XXX_REG_FLAGS] = 0x0a,
		[BQ27XXX_REG_TTE] = 0x16,
		[BQ27XXX_REG_TTF] = 0x18,
		[BQ27XXX_REG_TTES] = 0x1c,
		[BQ27XXX_REG_TTECP] = 0x26,
		[BQ27XXX_REG_NAC] = 0x0c,
		[BQ27XXX_REG_RC] = INVALID_REG_ADDR,
		[BQ27XXX_REG_FCC] = 0x12,
		[BQ27XXX_REG_CYCT] = 0x2a,
		[BQ27XXX_REG_AE] = 0x22,
		[BQ27XXX_REG_SOC] = 0x0b,
		[BQ27XXX_REG_DCAP] = 0x76,
		[BQ27XXX_REG_AP] = 0x24,
		[BQ27XXX_DM_CTRL] = INVALID_REG_ADDR,
		[BQ27XXX_DM_CLASS] = INVALID_REG_ADDR,
		[BQ27XXX_DM_BLOCK] = INVALID_REG_ADDR,
		[BQ27XXX_DM_DATA] = INVALID_REG_ADDR,
		[BQ27XXX_DM_CKSUM] = INVALID_REG_ADDR,
	पूर्ण,
	bq27010_regs[BQ27XXX_REG_MAX] = अणु
		[BQ27XXX_REG_CTRL] = 0x00,
		[BQ27XXX_REG_TEMP] = 0x06,
		[BQ27XXX_REG_INT_TEMP] = INVALID_REG_ADDR,
		[BQ27XXX_REG_VOLT] = 0x08,
		[BQ27XXX_REG_AI] = 0x14,
		[BQ27XXX_REG_FLAGS] = 0x0a,
		[BQ27XXX_REG_TTE] = 0x16,
		[BQ27XXX_REG_TTF] = 0x18,
		[BQ27XXX_REG_TTES] = 0x1c,
		[BQ27XXX_REG_TTECP] = 0x26,
		[BQ27XXX_REG_NAC] = 0x0c,
		[BQ27XXX_REG_RC] = INVALID_REG_ADDR,
		[BQ27XXX_REG_FCC] = 0x12,
		[BQ27XXX_REG_CYCT] = 0x2a,
		[BQ27XXX_REG_AE] = INVALID_REG_ADDR,
		[BQ27XXX_REG_SOC] = 0x0b,
		[BQ27XXX_REG_DCAP] = 0x76,
		[BQ27XXX_REG_AP] = INVALID_REG_ADDR,
		[BQ27XXX_DM_CTRL] = INVALID_REG_ADDR,
		[BQ27XXX_DM_CLASS] = INVALID_REG_ADDR,
		[BQ27XXX_DM_BLOCK] = INVALID_REG_ADDR,
		[BQ27XXX_DM_DATA] = INVALID_REG_ADDR,
		[BQ27XXX_DM_CKSUM] = INVALID_REG_ADDR,
	पूर्ण,
	bq2750x_regs[BQ27XXX_REG_MAX] = अणु
		[BQ27XXX_REG_CTRL] = 0x00,
		[BQ27XXX_REG_TEMP] = 0x06,
		[BQ27XXX_REG_INT_TEMP] = 0x28,
		[BQ27XXX_REG_VOLT] = 0x08,
		[BQ27XXX_REG_AI] = 0x14,
		[BQ27XXX_REG_FLAGS] = 0x0a,
		[BQ27XXX_REG_TTE] = 0x16,
		[BQ27XXX_REG_TTF] = INVALID_REG_ADDR,
		[BQ27XXX_REG_TTES] = 0x1a,
		[BQ27XXX_REG_TTECP] = INVALID_REG_ADDR,
		[BQ27XXX_REG_NAC] = 0x0c,
		[BQ27XXX_REG_RC] = 0x10,
		[BQ27XXX_REG_FCC] = 0x12,
		[BQ27XXX_REG_CYCT] = 0x2a,
		[BQ27XXX_REG_AE] = INVALID_REG_ADDR,
		[BQ27XXX_REG_SOC] = 0x2c,
		[BQ27XXX_REG_DCAP] = 0x3c,
		[BQ27XXX_REG_AP] = INVALID_REG_ADDR,
		BQ27XXX_DM_REG_ROWS,
	पूर्ण,
#घोषणा bq2751x_regs bq27510g3_regs
#घोषणा bq2752x_regs bq27510g3_regs
	bq27500_regs[BQ27XXX_REG_MAX] = अणु
		[BQ27XXX_REG_CTRL] = 0x00,
		[BQ27XXX_REG_TEMP] = 0x06,
		[BQ27XXX_REG_INT_TEMP] = INVALID_REG_ADDR,
		[BQ27XXX_REG_VOLT] = 0x08,
		[BQ27XXX_REG_AI] = 0x14,
		[BQ27XXX_REG_FLAGS] = 0x0a,
		[BQ27XXX_REG_TTE] = 0x16,
		[BQ27XXX_REG_TTF] = 0x18,
		[BQ27XXX_REG_TTES] = 0x1c,
		[BQ27XXX_REG_TTECP] = 0x26,
		[BQ27XXX_REG_NAC] = 0x0c,
		[BQ27XXX_REG_RC] = 0x10,
		[BQ27XXX_REG_FCC] = 0x12,
		[BQ27XXX_REG_CYCT] = 0x2a,
		[BQ27XXX_REG_AE] = 0x22,
		[BQ27XXX_REG_SOC] = 0x2c,
		[BQ27XXX_REG_DCAP] = 0x3c,
		[BQ27XXX_REG_AP] = 0x24,
		BQ27XXX_DM_REG_ROWS,
	पूर्ण,
#घोषणा bq27510g1_regs bq27500_regs
#घोषणा bq27510g2_regs bq27500_regs
	bq27510g3_regs[BQ27XXX_REG_MAX] = अणु
		[BQ27XXX_REG_CTRL] = 0x00,
		[BQ27XXX_REG_TEMP] = 0x06,
		[BQ27XXX_REG_INT_TEMP] = 0x28,
		[BQ27XXX_REG_VOLT] = 0x08,
		[BQ27XXX_REG_AI] = 0x14,
		[BQ27XXX_REG_FLAGS] = 0x0a,
		[BQ27XXX_REG_TTE] = 0x16,
		[BQ27XXX_REG_TTF] = INVALID_REG_ADDR,
		[BQ27XXX_REG_TTES] = 0x1a,
		[BQ27XXX_REG_TTECP] = INVALID_REG_ADDR,
		[BQ27XXX_REG_NAC] = 0x0c,
		[BQ27XXX_REG_RC] = 0x10,
		[BQ27XXX_REG_FCC] = 0x12,
		[BQ27XXX_REG_CYCT] = 0x1e,
		[BQ27XXX_REG_AE] = INVALID_REG_ADDR,
		[BQ27XXX_REG_SOC] = 0x20,
		[BQ27XXX_REG_DCAP] = 0x2e,
		[BQ27XXX_REG_AP] = INVALID_REG_ADDR,
		BQ27XXX_DM_REG_ROWS,
	पूर्ण,
	bq27520g1_regs[BQ27XXX_REG_MAX] = अणु
		[BQ27XXX_REG_CTRL] = 0x00,
		[BQ27XXX_REG_TEMP] = 0x06,
		[BQ27XXX_REG_INT_TEMP] = INVALID_REG_ADDR,
		[BQ27XXX_REG_VOLT] = 0x08,
		[BQ27XXX_REG_AI] = 0x14,
		[BQ27XXX_REG_FLAGS] = 0x0a,
		[BQ27XXX_REG_TTE] = 0x16,
		[BQ27XXX_REG_TTF] = 0x18,
		[BQ27XXX_REG_TTES] = 0x1c,
		[BQ27XXX_REG_TTECP] = 0x26,
		[BQ27XXX_REG_NAC] = 0x0c,
		[BQ27XXX_REG_RC] = 0x10,
		[BQ27XXX_REG_FCC] = 0x12,
		[BQ27XXX_REG_CYCT] = INVALID_REG_ADDR,
		[BQ27XXX_REG_AE] = 0x22,
		[BQ27XXX_REG_SOC] = 0x2c,
		[BQ27XXX_REG_DCAP] = 0x3c,
		[BQ27XXX_REG_AP] = 0x24,
		BQ27XXX_DM_REG_ROWS,
	पूर्ण,
	bq27520g2_regs[BQ27XXX_REG_MAX] = अणु
		[BQ27XXX_REG_CTRL] = 0x00,
		[BQ27XXX_REG_TEMP] = 0x06,
		[BQ27XXX_REG_INT_TEMP] = 0x36,
		[BQ27XXX_REG_VOLT] = 0x08,
		[BQ27XXX_REG_AI] = 0x14,
		[BQ27XXX_REG_FLAGS] = 0x0a,
		[BQ27XXX_REG_TTE] = 0x16,
		[BQ27XXX_REG_TTF] = 0x18,
		[BQ27XXX_REG_TTES] = 0x1c,
		[BQ27XXX_REG_TTECP] = 0x26,
		[BQ27XXX_REG_NAC] = 0x0c,
		[BQ27XXX_REG_RC] = 0x10,
		[BQ27XXX_REG_FCC] = 0x12,
		[BQ27XXX_REG_CYCT] = 0x2a,
		[BQ27XXX_REG_AE] = 0x22,
		[BQ27XXX_REG_SOC] = 0x2c,
		[BQ27XXX_REG_DCAP] = 0x3c,
		[BQ27XXX_REG_AP] = 0x24,
		BQ27XXX_DM_REG_ROWS,
	पूर्ण,
	bq27520g3_regs[BQ27XXX_REG_MAX] = अणु
		[BQ27XXX_REG_CTRL] = 0x00,
		[BQ27XXX_REG_TEMP] = 0x06,
		[BQ27XXX_REG_INT_TEMP] = 0x36,
		[BQ27XXX_REG_VOLT] = 0x08,
		[BQ27XXX_REG_AI] = 0x14,
		[BQ27XXX_REG_FLAGS] = 0x0a,
		[BQ27XXX_REG_TTE] = 0x16,
		[BQ27XXX_REG_TTF] = INVALID_REG_ADDR,
		[BQ27XXX_REG_TTES] = 0x1c,
		[BQ27XXX_REG_TTECP] = 0x26,
		[BQ27XXX_REG_NAC] = 0x0c,
		[BQ27XXX_REG_RC] = 0x10,
		[BQ27XXX_REG_FCC] = 0x12,
		[BQ27XXX_REG_CYCT] = 0x2a,
		[BQ27XXX_REG_AE] = 0x22,
		[BQ27XXX_REG_SOC] = 0x2c,
		[BQ27XXX_REG_DCAP] = 0x3c,
		[BQ27XXX_REG_AP] = 0x24,
		BQ27XXX_DM_REG_ROWS,
	पूर्ण,
	bq27520g4_regs[BQ27XXX_REG_MAX] = अणु
		[BQ27XXX_REG_CTRL] = 0x00,
		[BQ27XXX_REG_TEMP] = 0x06,
		[BQ27XXX_REG_INT_TEMP] = 0x28,
		[BQ27XXX_REG_VOLT] = 0x08,
		[BQ27XXX_REG_AI] = 0x14,
		[BQ27XXX_REG_FLAGS] = 0x0a,
		[BQ27XXX_REG_TTE] = 0x16,
		[BQ27XXX_REG_TTF] = INVALID_REG_ADDR,
		[BQ27XXX_REG_TTES] = 0x1c,
		[BQ27XXX_REG_TTECP] = INVALID_REG_ADDR,
		[BQ27XXX_REG_NAC] = 0x0c,
		[BQ27XXX_REG_RC] = 0x10,
		[BQ27XXX_REG_FCC] = 0x12,
		[BQ27XXX_REG_CYCT] = 0x1e,
		[BQ27XXX_REG_AE] = INVALID_REG_ADDR,
		[BQ27XXX_REG_SOC] = 0x20,
		[BQ27XXX_REG_DCAP] = INVALID_REG_ADDR,
		[BQ27XXX_REG_AP] = INVALID_REG_ADDR,
		BQ27XXX_DM_REG_ROWS,
	पूर्ण,
	bq27521_regs[BQ27XXX_REG_MAX] = अणु
		[BQ27XXX_REG_CTRL] = 0x02,
		[BQ27XXX_REG_TEMP] = 0x0a,
		[BQ27XXX_REG_INT_TEMP] = INVALID_REG_ADDR,
		[BQ27XXX_REG_VOLT] = 0x0c,
		[BQ27XXX_REG_AI] = 0x0e,
		[BQ27XXX_REG_FLAGS] = 0x08,
		[BQ27XXX_REG_TTE] = INVALID_REG_ADDR,
		[BQ27XXX_REG_TTF] = INVALID_REG_ADDR,
		[BQ27XXX_REG_TTES] = INVALID_REG_ADDR,
		[BQ27XXX_REG_TTECP] = INVALID_REG_ADDR,
		[BQ27XXX_REG_NAC] = INVALID_REG_ADDR,
		[BQ27XXX_REG_RC] = INVALID_REG_ADDR,
		[BQ27XXX_REG_FCC] = INVALID_REG_ADDR,
		[BQ27XXX_REG_CYCT] = INVALID_REG_ADDR,
		[BQ27XXX_REG_AE] = INVALID_REG_ADDR,
		[BQ27XXX_REG_SOC] = INVALID_REG_ADDR,
		[BQ27XXX_REG_DCAP] = INVALID_REG_ADDR,
		[BQ27XXX_REG_AP] = INVALID_REG_ADDR,
		[BQ27XXX_DM_CTRL] = INVALID_REG_ADDR,
		[BQ27XXX_DM_CLASS] = INVALID_REG_ADDR,
		[BQ27XXX_DM_BLOCK] = INVALID_REG_ADDR,
		[BQ27XXX_DM_DATA] = INVALID_REG_ADDR,
		[BQ27XXX_DM_CKSUM] = INVALID_REG_ADDR,
	पूर्ण,
	bq27530_regs[BQ27XXX_REG_MAX] = अणु
		[BQ27XXX_REG_CTRL] = 0x00,
		[BQ27XXX_REG_TEMP] = 0x06,
		[BQ27XXX_REG_INT_TEMP] = 0x32,
		[BQ27XXX_REG_VOLT] = 0x08,
		[BQ27XXX_REG_AI] = 0x14,
		[BQ27XXX_REG_FLAGS] = 0x0a,
		[BQ27XXX_REG_TTE] = 0x16,
		[BQ27XXX_REG_TTF] = INVALID_REG_ADDR,
		[BQ27XXX_REG_TTES] = INVALID_REG_ADDR,
		[BQ27XXX_REG_TTECP] = INVALID_REG_ADDR,
		[BQ27XXX_REG_NAC] = 0x0c,
		[BQ27XXX_REG_RC] = 0x10,
		[BQ27XXX_REG_FCC] = 0x12,
		[BQ27XXX_REG_CYCT] = 0x2a,
		[BQ27XXX_REG_AE] = INVALID_REG_ADDR,
		[BQ27XXX_REG_SOC] = 0x2c,
		[BQ27XXX_REG_DCAP] = INVALID_REG_ADDR,
		[BQ27XXX_REG_AP] = 0x24,
		BQ27XXX_DM_REG_ROWS,
	पूर्ण,
#घोषणा bq27531_regs bq27530_regs
	bq27541_regs[BQ27XXX_REG_MAX] = अणु
		[BQ27XXX_REG_CTRL] = 0x00,
		[BQ27XXX_REG_TEMP] = 0x06,
		[BQ27XXX_REG_INT_TEMP] = 0x28,
		[BQ27XXX_REG_VOLT] = 0x08,
		[BQ27XXX_REG_AI] = 0x14,
		[BQ27XXX_REG_FLAGS] = 0x0a,
		[BQ27XXX_REG_TTE] = 0x16,
		[BQ27XXX_REG_TTF] = INVALID_REG_ADDR,
		[BQ27XXX_REG_TTES] = INVALID_REG_ADDR,
		[BQ27XXX_REG_TTECP] = INVALID_REG_ADDR,
		[BQ27XXX_REG_NAC] = 0x0c,
		[BQ27XXX_REG_RC] = 0x10,
		[BQ27XXX_REG_FCC] = 0x12,
		[BQ27XXX_REG_CYCT] = 0x2a,
		[BQ27XXX_REG_AE] = INVALID_REG_ADDR,
		[BQ27XXX_REG_SOC] = 0x2c,
		[BQ27XXX_REG_DCAP] = 0x3c,
		[BQ27XXX_REG_AP] = 0x24,
		BQ27XXX_DM_REG_ROWS,
	पूर्ण,
#घोषणा bq27542_regs bq27541_regs
#घोषणा bq27546_regs bq27541_regs
#घोषणा bq27742_regs bq27541_regs
	bq27545_regs[BQ27XXX_REG_MAX] = अणु
		[BQ27XXX_REG_CTRL] = 0x00,
		[BQ27XXX_REG_TEMP] = 0x06,
		[BQ27XXX_REG_INT_TEMP] = 0x28,
		[BQ27XXX_REG_VOLT] = 0x08,
		[BQ27XXX_REG_AI] = 0x14,
		[BQ27XXX_REG_FLAGS] = 0x0a,
		[BQ27XXX_REG_TTE] = 0x16,
		[BQ27XXX_REG_TTF] = INVALID_REG_ADDR,
		[BQ27XXX_REG_TTES] = INVALID_REG_ADDR,
		[BQ27XXX_REG_TTECP] = INVALID_REG_ADDR,
		[BQ27XXX_REG_NAC] = 0x0c,
		[BQ27XXX_REG_RC] = 0x10,
		[BQ27XXX_REG_FCC] = 0x12,
		[BQ27XXX_REG_CYCT] = 0x2a,
		[BQ27XXX_REG_AE] = INVALID_REG_ADDR,
		[BQ27XXX_REG_SOC] = 0x2c,
		[BQ27XXX_REG_DCAP] = INVALID_REG_ADDR,
		[BQ27XXX_REG_AP] = 0x24,
		BQ27XXX_DM_REG_ROWS,
	पूर्ण,
	bq27421_regs[BQ27XXX_REG_MAX] = अणु
		[BQ27XXX_REG_CTRL] = 0x00,
		[BQ27XXX_REG_TEMP] = 0x02,
		[BQ27XXX_REG_INT_TEMP] = 0x1e,
		[BQ27XXX_REG_VOLT] = 0x04,
		[BQ27XXX_REG_AI] = 0x10,
		[BQ27XXX_REG_FLAGS] = 0x06,
		[BQ27XXX_REG_TTE] = INVALID_REG_ADDR,
		[BQ27XXX_REG_TTF] = INVALID_REG_ADDR,
		[BQ27XXX_REG_TTES] = INVALID_REG_ADDR,
		[BQ27XXX_REG_TTECP] = INVALID_REG_ADDR,
		[BQ27XXX_REG_NAC] = 0x08,
		[BQ27XXX_REG_RC] = 0x0c,
		[BQ27XXX_REG_FCC] = 0x0e,
		[BQ27XXX_REG_CYCT] = INVALID_REG_ADDR,
		[BQ27XXX_REG_AE] = INVALID_REG_ADDR,
		[BQ27XXX_REG_SOC] = 0x1c,
		[BQ27XXX_REG_DCAP] = 0x3c,
		[BQ27XXX_REG_AP] = 0x18,
		BQ27XXX_DM_REG_ROWS,
	पूर्ण,
#घोषणा bq27411_regs bq27421_regs
#घोषणा bq27425_regs bq27421_regs
#घोषणा bq27426_regs bq27421_regs
#घोषणा bq27441_regs bq27421_regs
#घोषणा bq27621_regs bq27421_regs
	bq27z561_regs[BQ27XXX_REG_MAX] = अणु
		[BQ27XXX_REG_CTRL] = 0x00,
		[BQ27XXX_REG_TEMP] = 0x06,
		[BQ27XXX_REG_INT_TEMP] = INVALID_REG_ADDR,
		[BQ27XXX_REG_VOLT] = 0x08,
		[BQ27XXX_REG_AI] = 0x14,
		[BQ27XXX_REG_FLAGS] = 0x0a,
		[BQ27XXX_REG_TTE] = 0x16,
		[BQ27XXX_REG_TTF] = 0x18,
		[BQ27XXX_REG_TTES] = INVALID_REG_ADDR,
		[BQ27XXX_REG_TTECP] = INVALID_REG_ADDR,
		[BQ27XXX_REG_NAC] = INVALID_REG_ADDR,
		[BQ27XXX_REG_RC] = 0x10,
		[BQ27XXX_REG_FCC] = 0x12,
		[BQ27XXX_REG_CYCT] = 0x2a,
		[BQ27XXX_REG_AE] = 0x22,
		[BQ27XXX_REG_SOC] = 0x2c,
		[BQ27XXX_REG_DCAP] = 0x3c,
		[BQ27XXX_REG_AP] = 0x22,
		BQ27XXX_DM_REG_ROWS,
	पूर्ण,
	bq28z610_regs[BQ27XXX_REG_MAX] = अणु
		[BQ27XXX_REG_CTRL] = 0x00,
		[BQ27XXX_REG_TEMP] = 0x06,
		[BQ27XXX_REG_INT_TEMP] = INVALID_REG_ADDR,
		[BQ27XXX_REG_VOLT] = 0x08,
		[BQ27XXX_REG_AI] = 0x14,
		[BQ27XXX_REG_FLAGS] = 0x0a,
		[BQ27XXX_REG_TTE] = 0x16,
		[BQ27XXX_REG_TTF] = 0x18,
		[BQ27XXX_REG_TTES] = INVALID_REG_ADDR,
		[BQ27XXX_REG_TTECP] = INVALID_REG_ADDR,
		[BQ27XXX_REG_NAC] = INVALID_REG_ADDR,
		[BQ27XXX_REG_RC] = 0x10,
		[BQ27XXX_REG_FCC] = 0x12,
		[BQ27XXX_REG_CYCT] = 0x2a,
		[BQ27XXX_REG_AE] = 0x22,
		[BQ27XXX_REG_SOC] = 0x2c,
		[BQ27XXX_REG_DCAP] = 0x3c,
		[BQ27XXX_REG_AP] = 0x22,
		BQ27XXX_DM_REG_ROWS,
	पूर्ण,
	bq34z100_regs[BQ27XXX_REG_MAX] = अणु
		[BQ27XXX_REG_CTRL] = 0x00,
		[BQ27XXX_REG_TEMP] = 0x0c,
		[BQ27XXX_REG_INT_TEMP] = 0x2a,
		[BQ27XXX_REG_VOLT] = 0x08,
		[BQ27XXX_REG_AI] = 0x0a,
		[BQ27XXX_REG_FLAGS] = 0x0e,
		[BQ27XXX_REG_TTE] = 0x18,
		[BQ27XXX_REG_TTF] = 0x1a,
		[BQ27XXX_REG_TTES] = 0x1e,
		[BQ27XXX_REG_TTECP] = INVALID_REG_ADDR,
		[BQ27XXX_REG_NAC] = INVALID_REG_ADDR,
		[BQ27XXX_REG_RC] = 0x04,
		[BQ27XXX_REG_FCC] = 0x06,
		[BQ27XXX_REG_CYCT] = 0x2c,
		[BQ27XXX_REG_AE] = 0x24,
		[BQ27XXX_REG_SOC] = 0x02,
		[BQ27XXX_REG_DCAP] = 0x3c,
		[BQ27XXX_REG_AP] = 0x22,
		BQ27XXX_DM_REG_ROWS,
	पूर्ण,
	bq78z100_regs[BQ27XXX_REG_MAX] = अणु
		[BQ27XXX_REG_CTRL] = 0x00,
		[BQ27XXX_REG_TEMP] = 0x06,
		[BQ27XXX_REG_INT_TEMP] = 0x28,
		[BQ27XXX_REG_VOLT] = 0x08,
		[BQ27XXX_REG_AI] = 0x14,
		[BQ27XXX_REG_FLAGS] = 0x0a,
		[BQ27XXX_REG_TTE] = 0x16,
		[BQ27XXX_REG_TTF] = 0x18,
		[BQ27XXX_REG_TTES] = 0x1c,
		[BQ27XXX_REG_TTECP] = INVALID_REG_ADDR,
		[BQ27XXX_REG_NAC] = INVALID_REG_ADDR,
		[BQ27XXX_REG_RC] = 0x10,
		[BQ27XXX_REG_FCC] = 0x12,
		[BQ27XXX_REG_CYCT] = 0x2a,
		[BQ27XXX_REG_AE] = INVALID_REG_ADDR,
		[BQ27XXX_REG_SOC] = 0x2c,
		[BQ27XXX_REG_DCAP] = 0x3c,
		[BQ27XXX_REG_AP] = 0x22,
		BQ27XXX_DM_REG_ROWS,
	पूर्ण;

अटल क्रमागत घातer_supply_property bq27000_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG,
	POWER_SUPPLY_PROP_TIME_TO_FULL_NOW,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CYCLE_COUNT,
	POWER_SUPPLY_PROP_ENERGY_NOW,
	POWER_SUPPLY_PROP_POWER_AVG,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_MANUFACTURER,
पूर्ण;

अटल क्रमागत घातer_supply_property bq27010_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG,
	POWER_SUPPLY_PROP_TIME_TO_FULL_NOW,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CYCLE_COUNT,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_MANUFACTURER,
पूर्ण;

#घोषणा bq2750x_props bq27510g3_props
#घोषणा bq2751x_props bq27510g3_props
#घोषणा bq2752x_props bq27510g3_props

अटल क्रमागत घातer_supply_property bq27500_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,
	POWER_SUPPLY_PROP_TIME_TO_FULL_NOW,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CYCLE_COUNT,
	POWER_SUPPLY_PROP_ENERGY_NOW,
	POWER_SUPPLY_PROP_POWER_AVG,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_MANUFACTURER,
पूर्ण;
#घोषणा bq27510g1_props bq27500_props
#घोषणा bq27510g2_props bq27500_props

अटल क्रमागत घातer_supply_property bq27510g3_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CYCLE_COUNT,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_MANUFACTURER,
पूर्ण;

अटल क्रमागत घातer_supply_property bq27520g1_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,
	POWER_SUPPLY_PROP_TIME_TO_FULL_NOW,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_ENERGY_NOW,
	POWER_SUPPLY_PROP_POWER_AVG,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_MANUFACTURER,
पूर्ण;

#घोषणा bq27520g2_props bq27500_props

अटल क्रमागत घातer_supply_property bq27520g3_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CYCLE_COUNT,
	POWER_SUPPLY_PROP_ENERGY_NOW,
	POWER_SUPPLY_PROP_POWER_AVG,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_MANUFACTURER,
पूर्ण;

अटल क्रमागत घातer_supply_property bq27520g4_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_CYCLE_COUNT,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_MANUFACTURER,
पूर्ण;

अटल क्रमागत घातer_supply_property bq27521_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TECHNOLOGY,
पूर्ण;

अटल क्रमागत घातer_supply_property bq27530_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_POWER_AVG,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_CYCLE_COUNT,
	POWER_SUPPLY_PROP_MANUFACTURER,
पूर्ण;
#घोषणा bq27531_props bq27530_props

अटल क्रमागत घातer_supply_property bq27541_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CYCLE_COUNT,
	POWER_SUPPLY_PROP_POWER_AVG,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_MANUFACTURER,
पूर्ण;
#घोषणा bq27542_props bq27541_props
#घोषणा bq27546_props bq27541_props
#घोषणा bq27742_props bq27541_props

अटल क्रमागत घातer_supply_property bq27545_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_CYCLE_COUNT,
	POWER_SUPPLY_PROP_POWER_AVG,
	POWER_SUPPLY_PROP_MANUFACTURER,
पूर्ण;

अटल क्रमागत घातer_supply_property bq27421_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_MANUFACTURER,
पूर्ण;
#घोषणा bq27411_props bq27421_props
#घोषणा bq27425_props bq27421_props
#घोषणा bq27426_props bq27421_props
#घोषणा bq27441_props bq27421_props
#घोषणा bq27621_props bq27421_props

अटल क्रमागत घातer_supply_property bq27z561_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,
	POWER_SUPPLY_PROP_TIME_TO_FULL_NOW,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CYCLE_COUNT,
	POWER_SUPPLY_PROP_POWER_AVG,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_MANUFACTURER,
पूर्ण;

अटल क्रमागत घातer_supply_property bq28z610_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,
	POWER_SUPPLY_PROP_TIME_TO_FULL_NOW,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CYCLE_COUNT,
	POWER_SUPPLY_PROP_POWER_AVG,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_MANUFACTURER,
पूर्ण;

अटल क्रमागत घातer_supply_property bq34z100_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG,
	POWER_SUPPLY_PROP_TIME_TO_FULL_NOW,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CYCLE_COUNT,
	POWER_SUPPLY_PROP_ENERGY_NOW,
	POWER_SUPPLY_PROP_POWER_AVG,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_MANUFACTURER,
पूर्ण;

अटल क्रमागत घातer_supply_property bq78z100_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,
	POWER_SUPPLY_PROP_TIME_TO_FULL_NOW,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CYCLE_COUNT,
	POWER_SUPPLY_PROP_POWER_AVG,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_MANUFACTURER,
पूर्ण;

काष्ठा bq27xxx_dm_reg अणु
	u8 subclass_id;
	u8 offset;
	u8 bytes;
	u16 min, max;
पूर्ण;

क्रमागत bq27xxx_dm_reg_id अणु
	BQ27XXX_DM_DESIGN_CAPACITY = 0,
	BQ27XXX_DM_DESIGN_ENERGY,
	BQ27XXX_DM_TERMINATE_VOLTAGE,
पूर्ण;

#घोषणा bq27000_dm_regs 0
#घोषणा bq27010_dm_regs 0
#घोषणा bq2750x_dm_regs 0
#घोषणा bq2751x_dm_regs 0
#घोषणा bq2752x_dm_regs 0

#अगर 0 /* not yet tested */
अटल काष्ठा bq27xxx_dm_reg bq27500_dm_regs[] = अणु
	[BQ27XXX_DM_DESIGN_CAPACITY]   = अणु 48, 10, 2,    0, 65535 पूर्ण,
	[BQ27XXX_DM_DESIGN_ENERGY]     = अणु पूर्ण, /* missing on chip */
	[BQ27XXX_DM_TERMINATE_VOLTAGE] = अणु 80, 48, 2, 1000, 32767 पूर्ण,
पूर्ण;
#अन्यथा
#घोषणा bq27500_dm_regs 0
#पूर्ण_अगर

/* toकरो create data memory definitions from datasheets and test on chips */
#घोषणा bq27510g1_dm_regs 0
#घोषणा bq27510g2_dm_regs 0
#घोषणा bq27510g3_dm_regs 0
#घोषणा bq27520g1_dm_regs 0
#घोषणा bq27520g2_dm_regs 0
#घोषणा bq27520g3_dm_regs 0
#घोषणा bq27520g4_dm_regs 0
#घोषणा bq27521_dm_regs 0
#घोषणा bq27530_dm_regs 0
#घोषणा bq27531_dm_regs 0
#घोषणा bq27541_dm_regs 0
#घोषणा bq27542_dm_regs 0
#घोषणा bq27546_dm_regs 0
#घोषणा bq27742_dm_regs 0

#अगर 0 /* not yet tested */
अटल काष्ठा bq27xxx_dm_reg bq27545_dm_regs[] = अणु
	[BQ27XXX_DM_DESIGN_CAPACITY]   = अणु 48, 23, 2,    0, 32767 पूर्ण,
	[BQ27XXX_DM_DESIGN_ENERGY]     = अणु 48, 25, 2,    0, 32767 पूर्ण,
	[BQ27XXX_DM_TERMINATE_VOLTAGE] = अणु 80, 67, 2, 2800,  3700 पूर्ण,
पूर्ण;
#अन्यथा
#घोषणा bq27545_dm_regs 0
#पूर्ण_अगर

अटल काष्ठा bq27xxx_dm_reg bq27411_dm_regs[] = अणु
	[BQ27XXX_DM_DESIGN_CAPACITY]   = अणु 82, 10, 2,    0, 32767 पूर्ण,
	[BQ27XXX_DM_DESIGN_ENERGY]     = अणु 82, 12, 2,    0, 32767 पूर्ण,
	[BQ27XXX_DM_TERMINATE_VOLTAGE] = अणु 82, 16, 2, 2800,  3700 पूर्ण,
पूर्ण;

अटल काष्ठा bq27xxx_dm_reg bq27421_dm_regs[] = अणु
	[BQ27XXX_DM_DESIGN_CAPACITY]   = अणु 82, 10, 2,    0,  8000 पूर्ण,
	[BQ27XXX_DM_DESIGN_ENERGY]     = अणु 82, 12, 2,    0, 32767 पूर्ण,
	[BQ27XXX_DM_TERMINATE_VOLTAGE] = अणु 82, 16, 2, 2500,  3700 पूर्ण,
पूर्ण;

अटल काष्ठा bq27xxx_dm_reg bq27425_dm_regs[] = अणु
	[BQ27XXX_DM_DESIGN_CAPACITY]   = अणु 82, 12, 2,    0, 32767 पूर्ण,
	[BQ27XXX_DM_DESIGN_ENERGY]     = अणु 82, 14, 2,    0, 32767 पूर्ण,
	[BQ27XXX_DM_TERMINATE_VOLTAGE] = अणु 82, 18, 2, 2800,  3700 पूर्ण,
पूर्ण;

अटल काष्ठा bq27xxx_dm_reg bq27426_dm_regs[] = अणु
	[BQ27XXX_DM_DESIGN_CAPACITY]   = अणु 82,  6, 2,    0,  8000 पूर्ण,
	[BQ27XXX_DM_DESIGN_ENERGY]     = अणु 82,  8, 2,    0, 32767 पूर्ण,
	[BQ27XXX_DM_TERMINATE_VOLTAGE] = अणु 82, 10, 2, 2500,  3700 पूर्ण,
पूर्ण;

#अगर 0 /* not yet tested */
#घोषणा bq27441_dm_regs bq27421_dm_regs
#अन्यथा
#घोषणा bq27441_dm_regs 0
#पूर्ण_अगर

#अगर 0 /* not yet tested */
अटल काष्ठा bq27xxx_dm_reg bq27621_dm_regs[] = अणु
	[BQ27XXX_DM_DESIGN_CAPACITY]   = अणु 82, 3, 2,    0,  8000 पूर्ण,
	[BQ27XXX_DM_DESIGN_ENERGY]     = अणु 82, 5, 2,    0, 32767 पूर्ण,
	[BQ27XXX_DM_TERMINATE_VOLTAGE] = अणु 82, 9, 2, 2500,  3700 पूर्ण,
पूर्ण;
#अन्यथा
#घोषणा bq27621_dm_regs 0
#पूर्ण_अगर

#घोषणा bq27z561_dm_regs 0
#घोषणा bq28z610_dm_regs 0
#घोषणा bq34z100_dm_regs 0
#घोषणा bq78z100_dm_regs 0

#घोषणा BQ27XXX_O_ZERO		BIT(0)
#घोषणा BQ27XXX_O_OTDC		BIT(1) /* has OTC/OTD overtemperature flags */
#घोषणा BQ27XXX_O_UTOT		BIT(2) /* has OT overtemperature flag */
#घोषणा BQ27XXX_O_CFGUP		BIT(3)
#घोषणा BQ27XXX_O_RAM		BIT(4)
#घोषणा BQ27Z561_O_BITS		BIT(5)
#घोषणा BQ27XXX_O_SOC_SI	BIT(6) /* SoC is single रेजिस्टर */
#घोषणा BQ27XXX_O_HAS_CI	BIT(7) /* has Capacity Inaccurate flag */
#घोषणा BQ27XXX_O_MUL_CHEM	BIT(8) /* multiple chemistries supported */

#घोषणा BQ27XXX_DATA(ref, key, opt) अणु		\
	.opts = (opt),				\
	.unseal_key = key,			\
	.regs  = ref##_regs,			\
	.dm_regs = ref##_dm_regs,		\
	.props = ref##_props,			\
	.props_size = ARRAY_SIZE(ref##_props) पूर्ण

अटल काष्ठा अणु
	u32 opts;
	u32 unseal_key;
	u8 *regs;
	काष्ठा bq27xxx_dm_reg *dm_regs;
	क्रमागत घातer_supply_property *props;
	माप_प्रकार props_size;
पूर्ण bq27xxx_chip_data[] = अणु
	[BQ27000]   = BQ27XXX_DATA(bq27000,   0         , BQ27XXX_O_ZERO | BQ27XXX_O_SOC_SI | BQ27XXX_O_HAS_CI),
	[BQ27010]   = BQ27XXX_DATA(bq27010,   0         , BQ27XXX_O_ZERO | BQ27XXX_O_SOC_SI | BQ27XXX_O_HAS_CI),
	[BQ2750X]   = BQ27XXX_DATA(bq2750x,   0         , BQ27XXX_O_OTDC),
	[BQ2751X]   = BQ27XXX_DATA(bq2751x,   0         , BQ27XXX_O_OTDC),
	[BQ2752X]   = BQ27XXX_DATA(bq2752x,   0         , BQ27XXX_O_OTDC),
	[BQ27500]   = BQ27XXX_DATA(bq27500,   0x04143672, BQ27XXX_O_OTDC),
	[BQ27510G1] = BQ27XXX_DATA(bq27510g1, 0         , BQ27XXX_O_OTDC),
	[BQ27510G2] = BQ27XXX_DATA(bq27510g2, 0         , BQ27XXX_O_OTDC),
	[BQ27510G3] = BQ27XXX_DATA(bq27510g3, 0         , BQ27XXX_O_OTDC),
	[BQ27520G1] = BQ27XXX_DATA(bq27520g1, 0         , BQ27XXX_O_OTDC),
	[BQ27520G2] = BQ27XXX_DATA(bq27520g2, 0         , BQ27XXX_O_OTDC),
	[BQ27520G3] = BQ27XXX_DATA(bq27520g3, 0         , BQ27XXX_O_OTDC),
	[BQ27520G4] = BQ27XXX_DATA(bq27520g4, 0         , BQ27XXX_O_OTDC),
	[BQ27521]   = BQ27XXX_DATA(bq27521,   0         , 0),
	[BQ27530]   = BQ27XXX_DATA(bq27530,   0         , BQ27XXX_O_UTOT),
	[BQ27531]   = BQ27XXX_DATA(bq27531,   0         , BQ27XXX_O_UTOT),
	[BQ27541]   = BQ27XXX_DATA(bq27541,   0         , BQ27XXX_O_OTDC),
	[BQ27542]   = BQ27XXX_DATA(bq27542,   0         , BQ27XXX_O_OTDC),
	[BQ27546]   = BQ27XXX_DATA(bq27546,   0         , BQ27XXX_O_OTDC),
	[BQ27742]   = BQ27XXX_DATA(bq27742,   0         , BQ27XXX_O_OTDC),
	[BQ27545]   = BQ27XXX_DATA(bq27545,   0x04143672, BQ27XXX_O_OTDC),
	[BQ27411]   = BQ27XXX_DATA(bq27411,   0x80008000, BQ27XXX_O_UTOT | BQ27XXX_O_CFGUP | BQ27XXX_O_RAM),
	[BQ27421]   = BQ27XXX_DATA(bq27421,   0x80008000, BQ27XXX_O_UTOT | BQ27XXX_O_CFGUP | BQ27XXX_O_RAM),
	[BQ27425]   = BQ27XXX_DATA(bq27425,   0x04143672, BQ27XXX_O_UTOT | BQ27XXX_O_CFGUP),
	[BQ27426]   = BQ27XXX_DATA(bq27426,   0x80008000, BQ27XXX_O_UTOT | BQ27XXX_O_CFGUP | BQ27XXX_O_RAM),
	[BQ27441]   = BQ27XXX_DATA(bq27441,   0x80008000, BQ27XXX_O_UTOT | BQ27XXX_O_CFGUP | BQ27XXX_O_RAM),
	[BQ27621]   = BQ27XXX_DATA(bq27621,   0x80008000, BQ27XXX_O_UTOT | BQ27XXX_O_CFGUP | BQ27XXX_O_RAM),
	[BQ27Z561]  = BQ27XXX_DATA(bq27z561,  0         , BQ27Z561_O_BITS),
	[BQ28Z610]  = BQ27XXX_DATA(bq28z610,  0         , BQ27Z561_O_BITS),
	[BQ34Z100]  = BQ27XXX_DATA(bq34z100,  0         , BQ27XXX_O_OTDC | BQ27XXX_O_SOC_SI | \
							  BQ27XXX_O_HAS_CI | BQ27XXX_O_MUL_CHEM),
	[BQ78Z100]  = BQ27XXX_DATA(bq78z100,  0         , BQ27Z561_O_BITS),
पूर्ण;

अटल DEFINE_MUTEX(bq27xxx_list_lock);
अटल LIST_HEAD(bq27xxx_battery_devices);

#घोषणा BQ27XXX_MSLEEP(i) usleep_range((i)*1000, (i)*1000+500)

#घोषणा BQ27XXX_DM_SZ	32

/**
 * काष्ठा bq27xxx_dm_buf - chip data memory buffer
 * @class: data memory subclass_id
 * @block: data memory block number
 * @data: data from/क्रम the block
 * @has_data: true अगर data has been filled by पढ़ो
 * @dirty: true अगर data has changed since last पढ़ो/ग_लिखो
 *
 * Encapsulates info required to manage chip data memory blocks.
 */
काष्ठा bq27xxx_dm_buf अणु
	u8 class;
	u8 block;
	u8 data[BQ27XXX_DM_SZ];
	bool has_data, dirty;
पूर्ण;

#घोषणा BQ27XXX_DM_BUF(di, i) अणु \
	.class = (di)->dm_regs[i].subclass_id, \
	.block = (di)->dm_regs[i].offset / BQ27XXX_DM_SZ, \
पूर्ण

अटल अंतरभूत u16 *bq27xxx_dm_reg_ptr(काष्ठा bq27xxx_dm_buf *buf,
				      काष्ठा bq27xxx_dm_reg *reg)
अणु
	अगर (buf->class == reg->subclass_id &&
	    buf->block == reg->offset / BQ27XXX_DM_SZ)
		वापस (u16 *) (buf->data + reg->offset % BQ27XXX_DM_SZ);

	वापस शून्य;
पूर्ण

अटल स्थिर अक्षर * स्थिर bq27xxx_dm_reg_name[] = अणु
	[BQ27XXX_DM_DESIGN_CAPACITY] = "design-capacity",
	[BQ27XXX_DM_DESIGN_ENERGY] = "design-energy",
	[BQ27XXX_DM_TERMINATE_VOLTAGE] = "terminate-voltage",
पूर्ण;


अटल bool bq27xxx_dt_to_nvm = true;
module_param_named(dt_monitored_battery_updates_nvm, bq27xxx_dt_to_nvm, bool, 0444);
MODULE_PARM_DESC(dt_monitored_battery_updates_nvm,
	"Devicetree monitored-battery config updates data memory on NVM/flash chips.\n"
	"Users must set this =0 when installing a different type of battery!\n"
	"Default is =1."
#अगर_अघोषित CONFIG_BATTERY_BQ27XXX_DT_UPDATES_NVM
	"\nSetting this affects future kernel updates, not the current configuration."
#पूर्ण_अगर
);

अटल पूर्णांक poll_पूर्णांकerval_param_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	काष्ठा bq27xxx_device_info *di;
	अचिन्हित पूर्णांक prev_val = *(अचिन्हित पूर्णांक *) kp->arg;
	पूर्णांक ret;

	ret = param_set_uपूर्णांक(val, kp);
	अगर (ret < 0 || prev_val == *(अचिन्हित पूर्णांक *) kp->arg)
		वापस ret;

	mutex_lock(&bq27xxx_list_lock);
	list_क्रम_each_entry(di, &bq27xxx_battery_devices, list) अणु
		cancel_delayed_work_sync(&di->work);
		schedule_delayed_work(&di->work, 0);
	पूर्ण
	mutex_unlock(&bq27xxx_list_lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops param_ops_poll_पूर्णांकerval = अणु
	.get = param_get_uपूर्णांक,
	.set = poll_पूर्णांकerval_param_set,
पूर्ण;

अटल अचिन्हित पूर्णांक poll_पूर्णांकerval = 360;
module_param_cb(poll_पूर्णांकerval, &param_ops_poll_पूर्णांकerval, &poll_पूर्णांकerval, 0644);
MODULE_PARM_DESC(poll_पूर्णांकerval,
		 "battery poll interval in seconds - 0 disables polling");

/*
 * Common code क्रम BQ27xxx devices
 */

अटल अंतरभूत पूर्णांक bq27xxx_पढ़ो(काष्ठा bq27xxx_device_info *di, पूर्णांक reg_index,
			       bool single)
अणु
	पूर्णांक ret;

	अगर (!di || di->regs[reg_index] == INVALID_REG_ADDR)
		वापस -EINVAL;

	ret = di->bus.पढ़ो(di, di->regs[reg_index], single);
	अगर (ret < 0)
		dev_dbg(di->dev, "failed to read register 0x%02x (index %d)\n",
			di->regs[reg_index], reg_index);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक bq27xxx_ग_लिखो(काष्ठा bq27xxx_device_info *di, पूर्णांक reg_index,
				u16 value, bool single)
अणु
	पूर्णांक ret;

	अगर (!di || di->regs[reg_index] == INVALID_REG_ADDR)
		वापस -EINVAL;

	अगर (!di->bus.ग_लिखो)
		वापस -EPERM;

	ret = di->bus.ग_लिखो(di, di->regs[reg_index], value, single);
	अगर (ret < 0)
		dev_dbg(di->dev, "failed to write register 0x%02x (index %d)\n",
			di->regs[reg_index], reg_index);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक bq27xxx_पढ़ो_block(काष्ठा bq27xxx_device_info *di, पूर्णांक reg_index,
				     u8 *data, पूर्णांक len)
अणु
	पूर्णांक ret;

	अगर (!di || di->regs[reg_index] == INVALID_REG_ADDR)
		वापस -EINVAL;

	अगर (!di->bus.पढ़ो_bulk)
		वापस -EPERM;

	ret = di->bus.पढ़ो_bulk(di, di->regs[reg_index], data, len);
	अगर (ret < 0)
		dev_dbg(di->dev, "failed to read_bulk register 0x%02x (index %d)\n",
			di->regs[reg_index], reg_index);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक bq27xxx_ग_लिखो_block(काष्ठा bq27xxx_device_info *di, पूर्णांक reg_index,
				      u8 *data, पूर्णांक len)
अणु
	पूर्णांक ret;

	अगर (!di || di->regs[reg_index] == INVALID_REG_ADDR)
		वापस -EINVAL;

	अगर (!di->bus.ग_लिखो_bulk)
		वापस -EPERM;

	ret = di->bus.ग_लिखो_bulk(di, di->regs[reg_index], data, len);
	अगर (ret < 0)
		dev_dbg(di->dev, "failed to write_bulk register 0x%02x (index %d)\n",
			di->regs[reg_index], reg_index);

	वापस ret;
पूर्ण

अटल पूर्णांक bq27xxx_battery_seal(काष्ठा bq27xxx_device_info *di)
अणु
	पूर्णांक ret;

	ret = bq27xxx_ग_लिखो(di, BQ27XXX_REG_CTRL, BQ27XXX_SEALED, false);
	अगर (ret < 0) अणु
		dev_err(di->dev, "bus error on seal: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bq27xxx_battery_unseal(काष्ठा bq27xxx_device_info *di)
अणु
	पूर्णांक ret;

	अगर (di->unseal_key == 0) अणु
		dev_err(di->dev, "unseal failed due to missing key\n");
		वापस -EINVAL;
	पूर्ण

	ret = bq27xxx_ग_लिखो(di, BQ27XXX_REG_CTRL, (u16)(di->unseal_key >> 16), false);
	अगर (ret < 0)
		जाओ out;

	ret = bq27xxx_ग_लिखो(di, BQ27XXX_REG_CTRL, (u16)di->unseal_key, false);
	अगर (ret < 0)
		जाओ out;

	वापस 0;

out:
	dev_err(di->dev, "bus error on unseal: %d\n", ret);
	वापस ret;
पूर्ण

अटल u8 bq27xxx_battery_checksum_dm_block(काष्ठा bq27xxx_dm_buf *buf)
अणु
	u16 sum = 0;
	पूर्णांक i;

	क्रम (i = 0; i < BQ27XXX_DM_SZ; i++)
		sum += buf->data[i];
	sum &= 0xff;

	वापस 0xff - sum;
पूर्ण

अटल पूर्णांक bq27xxx_battery_पढ़ो_dm_block(काष्ठा bq27xxx_device_info *di,
					 काष्ठा bq27xxx_dm_buf *buf)
अणु
	पूर्णांक ret;

	buf->has_data = false;

	ret = bq27xxx_ग_लिखो(di, BQ27XXX_DM_CLASS, buf->class, true);
	अगर (ret < 0)
		जाओ out;

	ret = bq27xxx_ग_लिखो(di, BQ27XXX_DM_BLOCK, buf->block, true);
	अगर (ret < 0)
		जाओ out;

	BQ27XXX_MSLEEP(1);

	ret = bq27xxx_पढ़ो_block(di, BQ27XXX_DM_DATA, buf->data, BQ27XXX_DM_SZ);
	अगर (ret < 0)
		जाओ out;

	ret = bq27xxx_पढ़ो(di, BQ27XXX_DM_CKSUM, true);
	अगर (ret < 0)
		जाओ out;

	अगर ((u8)ret != bq27xxx_battery_checksum_dm_block(buf)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	buf->has_data = true;
	buf->dirty = false;

	वापस 0;

out:
	dev_err(di->dev, "bus error reading chip memory: %d\n", ret);
	वापस ret;
पूर्ण

अटल व्योम bq27xxx_battery_update_dm_block(काष्ठा bq27xxx_device_info *di,
					    काष्ठा bq27xxx_dm_buf *buf,
					    क्रमागत bq27xxx_dm_reg_id reg_id,
					    अचिन्हित पूर्णांक val)
अणु
	काष्ठा bq27xxx_dm_reg *reg = &di->dm_regs[reg_id];
	स्थिर अक्षर *str = bq27xxx_dm_reg_name[reg_id];
	u16 *prev = bq27xxx_dm_reg_ptr(buf, reg);

	अगर (prev == शून्य) अणु
		dev_warn(di->dev, "buffer does not match %s dm spec\n", str);
		वापस;
	पूर्ण

	अगर (reg->bytes != 2) अणु
		dev_warn(di->dev, "%s dm spec has unsupported byte size\n", str);
		वापस;
	पूर्ण

	अगर (!buf->has_data)
		वापस;

	अगर (be16_to_cpup(prev) == val) अणु
		dev_info(di->dev, "%s has %u\n", str, val);
		वापस;
	पूर्ण

#अगर_घोषित CONFIG_BATTERY_BQ27XXX_DT_UPDATES_NVM
	अगर (!(di->opts & BQ27XXX_O_RAM) && !bq27xxx_dt_to_nvm) अणु
#अन्यथा
	अगर (!(di->opts & BQ27XXX_O_RAM)) अणु
#पूर्ण_अगर
		/* devicetree and NVM dअगरfer; defer to NVM */
		dev_warn(di->dev, "%s has %u; update to %u disallowed "
#अगर_घोषित CONFIG_BATTERY_BQ27XXX_DT_UPDATES_NVM
			 "by dt_monitored_battery_updates_nvm=0"
#अन्यथा
			 "for flash/NVM data memory"
#पूर्ण_अगर
			 "\n", str, be16_to_cpup(prev), val);
		वापस;
	पूर्ण

	dev_info(di->dev, "update %s to %u\n", str, val);

	*prev = cpu_to_be16(val);
	buf->dirty = true;
पूर्ण

अटल पूर्णांक bq27xxx_battery_cfgupdate_priv(काष्ठा bq27xxx_device_info *di, bool active)
अणु
	स्थिर पूर्णांक limit = 100;
	u16 cmd = active ? BQ27XXX_SET_CFGUPDATE : BQ27XXX_SOFT_RESET;
	पूर्णांक ret, try = limit;

	ret = bq27xxx_ग_लिखो(di, BQ27XXX_REG_CTRL, cmd, false);
	अगर (ret < 0)
		वापस ret;

	करो अणु
		BQ27XXX_MSLEEP(25);
		ret = bq27xxx_पढ़ो(di, BQ27XXX_REG_FLAGS, false);
		अगर (ret < 0)
			वापस ret;
	पूर्ण जबतक (!!(ret & BQ27XXX_FLAG_CFGUP) != active && --try);

	अगर (!try && di->chip != BQ27425) अणु // 425 has a bug
		dev_err(di->dev, "timed out waiting for cfgupdate flag %d\n", active);
		वापस -EINVAL;
	पूर्ण

	अगर (limit - try > 3)
		dev_warn(di->dev, "cfgupdate %d, retries %d\n", active, limit - try);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक bq27xxx_battery_set_cfgupdate(काष्ठा bq27xxx_device_info *di)
अणु
	पूर्णांक ret = bq27xxx_battery_cfgupdate_priv(di, true);
	अगर (ret < 0 && ret != -EINVAL)
		dev_err(di->dev, "bus error on set_cfgupdate: %d\n", ret);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक bq27xxx_battery_soft_reset(काष्ठा bq27xxx_device_info *di)
अणु
	पूर्णांक ret = bq27xxx_battery_cfgupdate_priv(di, false);
	अगर (ret < 0 && ret != -EINVAL)
		dev_err(di->dev, "bus error on soft_reset: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक bq27xxx_battery_ग_लिखो_dm_block(काष्ठा bq27xxx_device_info *di,
					  काष्ठा bq27xxx_dm_buf *buf)
अणु
	bool cfgup = di->opts & BQ27XXX_O_CFGUP;
	पूर्णांक ret;

	अगर (!buf->dirty)
		वापस 0;

	अगर (cfgup) अणु
		ret = bq27xxx_battery_set_cfgupdate(di);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = bq27xxx_ग_लिखो(di, BQ27XXX_DM_CTRL, 0, true);
	अगर (ret < 0)
		जाओ out;

	ret = bq27xxx_ग_लिखो(di, BQ27XXX_DM_CLASS, buf->class, true);
	अगर (ret < 0)
		जाओ out;

	ret = bq27xxx_ग_लिखो(di, BQ27XXX_DM_BLOCK, buf->block, true);
	अगर (ret < 0)
		जाओ out;

	BQ27XXX_MSLEEP(1);

	ret = bq27xxx_ग_लिखो_block(di, BQ27XXX_DM_DATA, buf->data, BQ27XXX_DM_SZ);
	अगर (ret < 0)
		जाओ out;

	ret = bq27xxx_ग_लिखो(di, BQ27XXX_DM_CKSUM,
			    bq27xxx_battery_checksum_dm_block(buf), true);
	अगर (ret < 0)
		जाओ out;

	/* DO NOT पढ़ो BQ27XXX_DM_CKSUM here to verअगरy it! That may cause NVM
	 * corruption on the '425 chip (and perhaps others), which can damage
	 * the chip.
	 */

	अगर (cfgup) अणु
		BQ27XXX_MSLEEP(1);
		ret = bq27xxx_battery_soft_reset(di);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		BQ27XXX_MSLEEP(100); /* flash DM updates in <100ms */
	पूर्ण

	buf->dirty = false;

	वापस 0;

out:
	अगर (cfgup)
		bq27xxx_battery_soft_reset(di);

	dev_err(di->dev, "bus error writing chip memory: %d\n", ret);
	वापस ret;
पूर्ण

अटल व्योम bq27xxx_battery_set_config(काष्ठा bq27xxx_device_info *di,
				       काष्ठा घातer_supply_battery_info *info)
अणु
	काष्ठा bq27xxx_dm_buf bd = BQ27XXX_DM_BUF(di, BQ27XXX_DM_DESIGN_CAPACITY);
	काष्ठा bq27xxx_dm_buf bt = BQ27XXX_DM_BUF(di, BQ27XXX_DM_TERMINATE_VOLTAGE);
	bool updated;

	अगर (bq27xxx_battery_unseal(di) < 0)
		वापस;

	अगर (info->अक्षरge_full_design_uah != -EINVAL &&
	    info->energy_full_design_uwh != -EINVAL) अणु
		bq27xxx_battery_पढ़ो_dm_block(di, &bd);
		/* assume design energy & capacity are in same block */
		bq27xxx_battery_update_dm_block(di, &bd,
					BQ27XXX_DM_DESIGN_CAPACITY,
					info->अक्षरge_full_design_uah / 1000);
		bq27xxx_battery_update_dm_block(di, &bd,
					BQ27XXX_DM_DESIGN_ENERGY,
					info->energy_full_design_uwh / 1000);
	पूर्ण

	अगर (info->voltage_min_design_uv != -EINVAL) अणु
		bool same = bd.class == bt.class && bd.block == bt.block;
		अगर (!same)
			bq27xxx_battery_पढ़ो_dm_block(di, &bt);
		bq27xxx_battery_update_dm_block(di, same ? &bd : &bt,
					BQ27XXX_DM_TERMINATE_VOLTAGE,
					info->voltage_min_design_uv / 1000);
	पूर्ण

	updated = bd.dirty || bt.dirty;

	bq27xxx_battery_ग_लिखो_dm_block(di, &bd);
	bq27xxx_battery_ग_लिखो_dm_block(di, &bt);

	bq27xxx_battery_seal(di);

	अगर (updated && !(di->opts & BQ27XXX_O_CFGUP)) अणु
		bq27xxx_ग_लिखो(di, BQ27XXX_REG_CTRL, BQ27XXX_RESET, false);
		BQ27XXX_MSLEEP(300); /* reset समय is not करोcumented */
	पूर्ण
	/* assume bq27xxx_battery_update() is called hereafter */
पूर्ण

अटल व्योम bq27xxx_battery_settings(काष्ठा bq27xxx_device_info *di)
अणु
	काष्ठा घातer_supply_battery_info info = अणुपूर्ण;
	अचिन्हित पूर्णांक min, max;

	अगर (घातer_supply_get_battery_info(di->bat, &info) < 0)
		वापस;

	अगर (!di->dm_regs) अणु
		dev_warn(di->dev, "data memory update not supported for chip\n");
		वापस;
	पूर्ण

	अगर (info.energy_full_design_uwh != info.अक्षरge_full_design_uah) अणु
		अगर (info.energy_full_design_uwh == -EINVAL)
			dev_warn(di->dev, "missing battery:energy-full-design-microwatt-hours\n");
		अन्यथा अगर (info.अक्षरge_full_design_uah == -EINVAL)
			dev_warn(di->dev, "missing battery:charge-full-design-microamp-hours\n");
	पूर्ण

	/* assume min == 0 */
	max = di->dm_regs[BQ27XXX_DM_DESIGN_ENERGY].max;
	अगर (info.energy_full_design_uwh > max * 1000) अणु
		dev_err(di->dev, "invalid battery:energy-full-design-microwatt-hours %d\n",
			info.energy_full_design_uwh);
		info.energy_full_design_uwh = -EINVAL;
	पूर्ण

	/* assume min == 0 */
	max = di->dm_regs[BQ27XXX_DM_DESIGN_CAPACITY].max;
	अगर (info.अक्षरge_full_design_uah > max * 1000) अणु
		dev_err(di->dev, "invalid battery:charge-full-design-microamp-hours %d\n",
			info.अक्षरge_full_design_uah);
		info.अक्षरge_full_design_uah = -EINVAL;
	पूर्ण

	min = di->dm_regs[BQ27XXX_DM_TERMINATE_VOLTAGE].min;
	max = di->dm_regs[BQ27XXX_DM_TERMINATE_VOLTAGE].max;
	अगर ((info.voltage_min_design_uv < min * 1000 ||
	     info.voltage_min_design_uv > max * 1000) &&
	     info.voltage_min_design_uv != -EINVAL) अणु
		dev_err(di->dev, "invalid battery:voltage-min-design-microvolt %d\n",
			info.voltage_min_design_uv);
		info.voltage_min_design_uv = -EINVAL;
	पूर्ण

	अगर ((info.energy_full_design_uwh != -EINVAL &&
	     info.अक्षरge_full_design_uah != -EINVAL) ||
	     info.voltage_min_design_uv  != -EINVAL)
		bq27xxx_battery_set_config(di, &info);
पूर्ण

/*
 * Return the battery State-of-Charge
 * Or < 0 अगर something fails.
 */
अटल पूर्णांक bq27xxx_battery_पढ़ो_soc(काष्ठा bq27xxx_device_info *di)
अणु
	पूर्णांक soc;

	अगर (di->opts & BQ27XXX_O_SOC_SI)
		soc = bq27xxx_पढ़ो(di, BQ27XXX_REG_SOC, true);
	अन्यथा
		soc = bq27xxx_पढ़ो(di, BQ27XXX_REG_SOC, false);

	अगर (soc < 0)
		dev_dbg(di->dev, "error reading State-of-Charge\n");

	वापस soc;
पूर्ण

/*
 * Return a battery अक्षरge value in तगAh
 * Or < 0 अगर something fails.
 */
अटल पूर्णांक bq27xxx_battery_पढ़ो_अक्षरge(काष्ठा bq27xxx_device_info *di, u8 reg)
अणु
	पूर्णांक अक्षरge;

	अक्षरge = bq27xxx_पढ़ो(di, reg, false);
	अगर (अक्षरge < 0) अणु
		dev_dbg(di->dev, "error reading charge register %02x: %d\n",
			reg, अक्षरge);
		वापस अक्षरge;
	पूर्ण

	अगर (di->opts & BQ27XXX_O_ZERO)
		अक्षरge *= BQ27XXX_CURRENT_CONSTANT / BQ27XXX_RS;
	अन्यथा
		अक्षरge *= 1000;

	वापस अक्षरge;
पूर्ण

/*
 * Return the battery Nominal available capacity in तगAh
 * Or < 0 अगर something fails.
 */
अटल अंतरभूत पूर्णांक bq27xxx_battery_पढ़ो_nac(काष्ठा bq27xxx_device_info *di)
अणु
	पूर्णांक flags;

	अगर (di->opts & BQ27XXX_O_ZERO) अणु
		flags = bq27xxx_पढ़ो(di, BQ27XXX_REG_FLAGS, true);
		अगर (flags >= 0 && (flags & BQ27000_FLAG_CI))
			वापस -ENODATA;
	पूर्ण

	वापस bq27xxx_battery_पढ़ो_अक्षरge(di, BQ27XXX_REG_NAC);
पूर्ण

/*
 * Return the battery Reमुख्यing Capacity in तगAh
 * Or < 0 अगर something fails.
 */
अटल अंतरभूत पूर्णांक bq27xxx_battery_पढ़ो_rc(काष्ठा bq27xxx_device_info *di)
अणु
	वापस bq27xxx_battery_पढ़ो_अक्षरge(di, BQ27XXX_REG_RC);
पूर्ण

/*
 * Return the battery Full Charge Capacity in तगAh
 * Or < 0 अगर something fails.
 */
अटल अंतरभूत पूर्णांक bq27xxx_battery_पढ़ो_fcc(काष्ठा bq27xxx_device_info *di)
अणु
	वापस bq27xxx_battery_पढ़ो_अक्षरge(di, BQ27XXX_REG_FCC);
पूर्ण

/*
 * Return the Design Capacity in तगAh
 * Or < 0 अगर something fails.
 */
अटल पूर्णांक bq27xxx_battery_पढ़ो_dcap(काष्ठा bq27xxx_device_info *di)
अणु
	पूर्णांक dcap;

	अगर (di->opts & BQ27XXX_O_ZERO)
		dcap = bq27xxx_पढ़ो(di, BQ27XXX_REG_DCAP, true);
	अन्यथा
		dcap = bq27xxx_पढ़ो(di, BQ27XXX_REG_DCAP, false);

	अगर (dcap < 0) अणु
		dev_dbg(di->dev, "error reading initial last measured discharge\n");
		वापस dcap;
	पूर्ण

	अगर (di->opts & BQ27XXX_O_ZERO)
		dcap = (dcap << 8) * BQ27XXX_CURRENT_CONSTANT / BQ27XXX_RS;
	अन्यथा
		dcap *= 1000;

	वापस dcap;
पूर्ण

/*
 * Return the battery Available energy in तगWh
 * Or < 0 अगर something fails.
 */
अटल पूर्णांक bq27xxx_battery_पढ़ो_energy(काष्ठा bq27xxx_device_info *di)
अणु
	पूर्णांक ae;

	ae = bq27xxx_पढ़ो(di, BQ27XXX_REG_AE, false);
	अगर (ae < 0) अणु
		dev_dbg(di->dev, "error reading available energy\n");
		वापस ae;
	पूर्ण

	अगर (di->opts & BQ27XXX_O_ZERO)
		ae *= BQ27XXX_POWER_CONSTANT / BQ27XXX_RS;
	अन्यथा
		ae *= 1000;

	वापस ae;
पूर्ण

/*
 * Return the battery temperature in tenths of degree Kelvin
 * Or < 0 अगर something fails.
 */
अटल पूर्णांक bq27xxx_battery_पढ़ो_temperature(काष्ठा bq27xxx_device_info *di)
अणु
	पूर्णांक temp;

	temp = bq27xxx_पढ़ो(di, BQ27XXX_REG_TEMP, false);
	अगर (temp < 0) अणु
		dev_err(di->dev, "error reading temperature\n");
		वापस temp;
	पूर्ण

	अगर (di->opts & BQ27XXX_O_ZERO)
		temp = 5 * temp / 2;

	वापस temp;
पूर्ण

/*
 * Return the battery Cycle count total
 * Or < 0 अगर something fails.
 */
अटल पूर्णांक bq27xxx_battery_पढ़ो_cyct(काष्ठा bq27xxx_device_info *di)
अणु
	पूर्णांक cyct;

	cyct = bq27xxx_पढ़ो(di, BQ27XXX_REG_CYCT, false);
	अगर (cyct < 0)
		dev_err(di->dev, "error reading cycle count total\n");

	वापस cyct;
पूर्ण

/*
 * Read a समय रेजिस्टर.
 * Return < 0 अगर something fails.
 */
अटल पूर्णांक bq27xxx_battery_पढ़ो_समय(काष्ठा bq27xxx_device_info *di, u8 reg)
अणु
	पूर्णांक tval;

	tval = bq27xxx_पढ़ो(di, reg, false);
	अगर (tval < 0) अणु
		dev_dbg(di->dev, "error reading time register %02x: %d\n",
			reg, tval);
		वापस tval;
	पूर्ण

	अगर (tval == 65535)
		वापस -ENODATA;

	वापस tval * 60;
पूर्ण

/*
 * Returns true अगर a battery over temperature condition is detected
 */
अटल bool bq27xxx_battery_overtemp(काष्ठा bq27xxx_device_info *di, u16 flags)
अणु
	अगर (di->opts & BQ27XXX_O_OTDC)
		वापस flags & (BQ27XXX_FLAG_OTC | BQ27XXX_FLAG_OTD);
        अगर (di->opts & BQ27XXX_O_UTOT)
		वापस flags & BQ27XXX_FLAG_OT;

	वापस false;
पूर्ण

/*
 * Returns true अगर a battery under temperature condition is detected
 */
अटल bool bq27xxx_battery_undertemp(काष्ठा bq27xxx_device_info *di, u16 flags)
अणु
	अगर (di->opts & BQ27XXX_O_UTOT)
		वापस flags & BQ27XXX_FLAG_UT;

	वापस false;
पूर्ण

/*
 * Returns true अगर a low state of अक्षरge condition is detected
 */
अटल bool bq27xxx_battery_dead(काष्ठा bq27xxx_device_info *di, u16 flags)
अणु
	अगर (di->opts & BQ27XXX_O_ZERO)
		वापस flags & (BQ27000_FLAG_EDV1 | BQ27000_FLAG_EDVF);
	अन्यथा अगर (di->opts & BQ27Z561_O_BITS)
		वापस flags & BQ27Z561_FLAG_FDC;
	अन्यथा
		वापस flags & (BQ27XXX_FLAG_SOC1 | BQ27XXX_FLAG_SOCF);
पूर्ण

अटल पूर्णांक bq27xxx_battery_पढ़ो_health(काष्ठा bq27xxx_device_info *di)
अणु
	/* Unlikely but important to वापस first */
	अगर (unlikely(bq27xxx_battery_overtemp(di, di->cache.flags)))
		वापस POWER_SUPPLY_HEALTH_OVERHEAT;
	अगर (unlikely(bq27xxx_battery_undertemp(di, di->cache.flags)))
		वापस POWER_SUPPLY_HEALTH_COLD;
	अगर (unlikely(bq27xxx_battery_dead(di, di->cache.flags)))
		वापस POWER_SUPPLY_HEALTH_DEAD;

	वापस POWER_SUPPLY_HEALTH_GOOD;
पूर्ण

व्योम bq27xxx_battery_update(काष्ठा bq27xxx_device_info *di)
अणु
	काष्ठा bq27xxx_reg_cache cache = अणु0, पूर्ण;
	bool has_ci_flag = di->opts & BQ27XXX_O_HAS_CI;
	bool has_singe_flag = di->opts & BQ27XXX_O_ZERO;

	cache.flags = bq27xxx_पढ़ो(di, BQ27XXX_REG_FLAGS, has_singe_flag);
	अगर ((cache.flags & 0xff) == 0xff)
		cache.flags = -1; /* पढ़ो error */
	अगर (cache.flags >= 0) अणु
		cache.temperature = bq27xxx_battery_पढ़ो_temperature(di);
		अगर (has_ci_flag && (cache.flags & BQ27000_FLAG_CI)) अणु
			dev_info_once(di->dev, "battery is not calibrated! ignoring capacity values\n");
			cache.capacity = -ENODATA;
			cache.energy = -ENODATA;
			cache.समय_प्रकारo_empty = -ENODATA;
			cache.समय_प्रकारo_empty_avg = -ENODATA;
			cache.समय_प्रकारo_full = -ENODATA;
			cache.अक्षरge_full = -ENODATA;
			cache.health = -ENODATA;
		पूर्ण अन्यथा अणु
			अगर (di->regs[BQ27XXX_REG_TTE] != INVALID_REG_ADDR)
				cache.समय_प्रकारo_empty = bq27xxx_battery_पढ़ो_समय(di, BQ27XXX_REG_TTE);
			अगर (di->regs[BQ27XXX_REG_TTECP] != INVALID_REG_ADDR)
				cache.समय_प्रकारo_empty_avg = bq27xxx_battery_पढ़ो_समय(di, BQ27XXX_REG_TTECP);
			अगर (di->regs[BQ27XXX_REG_TTF] != INVALID_REG_ADDR)
				cache.समय_प्रकारo_full = bq27xxx_battery_पढ़ो_समय(di, BQ27XXX_REG_TTF);

			cache.अक्षरge_full = bq27xxx_battery_पढ़ो_fcc(di);
			cache.capacity = bq27xxx_battery_पढ़ो_soc(di);
			अगर (di->regs[BQ27XXX_REG_AE] != INVALID_REG_ADDR)
				cache.energy = bq27xxx_battery_पढ़ो_energy(di);
			di->cache.flags = cache.flags;
			cache.health = bq27xxx_battery_पढ़ो_health(di);
		पूर्ण
		अगर (di->regs[BQ27XXX_REG_CYCT] != INVALID_REG_ADDR)
			cache.cycle_count = bq27xxx_battery_पढ़ो_cyct(di);

		/* We only have to पढ़ो अक्षरge design full once */
		अगर (di->अक्षरge_design_full <= 0)
			di->अक्षरge_design_full = bq27xxx_battery_पढ़ो_dcap(di);
	पूर्ण

	अगर ((di->cache.capacity != cache.capacity) ||
	    (di->cache.flags != cache.flags))
		घातer_supply_changed(di->bat);

	अगर (स_भेद(&di->cache, &cache, माप(cache)) != 0)
		di->cache = cache;

	di->last_update = jअगरfies;
पूर्ण
EXPORT_SYMBOL_GPL(bq27xxx_battery_update);

अटल व्योम bq27xxx_battery_poll(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bq27xxx_device_info *di =
			container_of(work, काष्ठा bq27xxx_device_info,
				     work.work);

	bq27xxx_battery_update(di);

	अगर (poll_पूर्णांकerval > 0)
		schedule_delayed_work(&di->work, poll_पूर्णांकerval * HZ);
पूर्ण

अटल bool bq27xxx_battery_is_full(काष्ठा bq27xxx_device_info *di, पूर्णांक flags)
अणु
	अगर (di->opts & BQ27XXX_O_ZERO)
		वापस (flags & BQ27000_FLAG_FC);
	अन्यथा अगर (di->opts & BQ27Z561_O_BITS)
		वापस (flags & BQ27Z561_FLAG_FC);
	अन्यथा
		वापस (flags & BQ27XXX_FLAG_FC);
पूर्ण

/*
 * Return the battery average current in तगA and the status
 * Note that current can be negative चिन्हित as well
 * Or 0 अगर something fails.
 */
अटल पूर्णांक bq27xxx_battery_current_and_status(
	काष्ठा bq27xxx_device_info *di,
	जोड़ घातer_supply_propval *val_curr,
	जोड़ घातer_supply_propval *val_status)
अणु
	bool single_flags = (di->opts & BQ27XXX_O_ZERO);
	पूर्णांक curr;
	पूर्णांक flags;

	curr = bq27xxx_पढ़ो(di, BQ27XXX_REG_AI, false);
	अगर (curr < 0) अणु
		dev_err(di->dev, "error reading current\n");
		वापस curr;
	पूर्ण

	flags = bq27xxx_पढ़ो(di, BQ27XXX_REG_FLAGS, single_flags);
	अगर (flags < 0) अणु
		dev_err(di->dev, "error reading flags\n");
		वापस flags;
	पूर्ण

	अगर (di->opts & BQ27XXX_O_ZERO) अणु
		अगर (!(flags & BQ27000_FLAG_CHGS)) अणु
			dev_dbg(di->dev, "negative current!\n");
			curr = -curr;
		पूर्ण

		curr = curr * BQ27XXX_CURRENT_CONSTANT / BQ27XXX_RS;
	पूर्ण अन्यथा अणु
		/* Other gauges वापस चिन्हित value */
		curr = (पूर्णांक)((s16)curr) * 1000;
	पूर्ण

	अगर (val_curr)
		val_curr->पूर्णांकval = curr;

	अगर (val_status) अणु
		अगर (curr > 0) अणु
			val_status->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		पूर्ण अन्यथा अगर (curr < 0) अणु
			val_status->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		पूर्ण अन्यथा अणु
			अगर (bq27xxx_battery_is_full(di, flags))
				val_status->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
			अन्यथा
				val_status->पूर्णांकval =
					POWER_SUPPLY_STATUS_NOT_CHARGING;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Get the average घातer in तगW
 * Return < 0 अगर something fails.
 */
अटल पूर्णांक bq27xxx_battery_pwr_avg(काष्ठा bq27xxx_device_info *di,
				   जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक घातer;

	घातer = bq27xxx_पढ़ो(di, BQ27XXX_REG_AP, false);
	अगर (घातer < 0) अणु
		dev_err(di->dev,
			"error reading average power register %02x: %d\n",
			BQ27XXX_REG_AP, घातer);
		वापस घातer;
	पूर्ण

	अगर (di->opts & BQ27XXX_O_ZERO)
		val->पूर्णांकval = (घातer * BQ27XXX_POWER_CONSTANT) / BQ27XXX_RS;
	अन्यथा
		/* Other gauges वापस a चिन्हित value in units of 10mW */
		val->पूर्णांकval = (पूर्णांक)((s16)घातer) * 10000;

	वापस 0;
पूर्ण

अटल पूर्णांक bq27xxx_battery_capacity_level(काष्ठा bq27xxx_device_info *di,
					  जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक level;

	अगर (di->opts & BQ27XXX_O_ZERO) अणु
		अगर (di->cache.flags & BQ27000_FLAG_FC)
			level = POWER_SUPPLY_CAPACITY_LEVEL_FULL;
		अन्यथा अगर (di->cache.flags & BQ27000_FLAG_EDV1)
			level = POWER_SUPPLY_CAPACITY_LEVEL_LOW;
		अन्यथा अगर (di->cache.flags & BQ27000_FLAG_EDVF)
			level = POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL;
		अन्यथा
			level = POWER_SUPPLY_CAPACITY_LEVEL_NORMAL;
	पूर्ण अन्यथा अगर (di->opts & BQ27Z561_O_BITS) अणु
		अगर (di->cache.flags & BQ27Z561_FLAG_FC)
			level = POWER_SUPPLY_CAPACITY_LEVEL_FULL;
		अन्यथा अगर (di->cache.flags & BQ27Z561_FLAG_FDC)
			level = POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL;
		अन्यथा
			level = POWER_SUPPLY_CAPACITY_LEVEL_NORMAL;
	पूर्ण अन्यथा अणु
		अगर (di->cache.flags & BQ27XXX_FLAG_FC)
			level = POWER_SUPPLY_CAPACITY_LEVEL_FULL;
		अन्यथा अगर (di->cache.flags & BQ27XXX_FLAG_SOC1)
			level = POWER_SUPPLY_CAPACITY_LEVEL_LOW;
		अन्यथा अगर (di->cache.flags & BQ27XXX_FLAG_SOCF)
			level = POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL;
		अन्यथा
			level = POWER_SUPPLY_CAPACITY_LEVEL_NORMAL;
	पूर्ण

	val->पूर्णांकval = level;

	वापस 0;
पूर्ण

/*
 * Return the battery Voltage in millivolts
 * Or < 0 अगर something fails.
 */
अटल पूर्णांक bq27xxx_battery_voltage(काष्ठा bq27xxx_device_info *di,
				   जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक volt;

	volt = bq27xxx_पढ़ो(di, BQ27XXX_REG_VOLT, false);
	अगर (volt < 0) अणु
		dev_err(di->dev, "error reading voltage\n");
		वापस volt;
	पूर्ण

	val->पूर्णांकval = volt * 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक bq27xxx_simple_value(पूर्णांक value,
				जोड़ घातer_supply_propval *val)
अणु
	अगर (value < 0)
		वापस value;

	val->पूर्णांकval = value;

	वापस 0;
पूर्ण

अटल पूर्णांक bq27xxx_battery_get_property(काष्ठा घातer_supply *psy,
					क्रमागत घातer_supply_property psp,
					जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक ret = 0;
	काष्ठा bq27xxx_device_info *di = घातer_supply_get_drvdata(psy);

	mutex_lock(&di->lock);
	अगर (समय_is_beक्रमe_jअगरfies(di->last_update + 5 * HZ)) अणु
		cancel_delayed_work_sync(&di->work);
		bq27xxx_battery_poll(&di->work.work);
	पूर्ण
	mutex_unlock(&di->lock);

	अगर (psp != POWER_SUPPLY_PROP_PRESENT && di->cache.flags < 0)
		वापस -ENODEV;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		ret = bq27xxx_battery_current_and_status(di, शून्य, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = bq27xxx_battery_voltage(di, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = di->cache.flags < 0 ? 0 : 1;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = bq27xxx_battery_current_and_status(di, val, शून्य);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY:
		ret = bq27xxx_simple_value(di->cache.capacity, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY_LEVEL:
		ret = bq27xxx_battery_capacity_level(di, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP:
		ret = bq27xxx_simple_value(di->cache.temperature, val);
		अगर (ret == 0)
			val->पूर्णांकval -= 2731; /* convert decidegree k to c */
		अवरोध;
	हाल POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW:
		ret = bq27xxx_simple_value(di->cache.समय_प्रकारo_empty, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG:
		ret = bq27xxx_simple_value(di->cache.समय_प्रकारo_empty_avg, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TIME_TO_FULL_NOW:
		ret = bq27xxx_simple_value(di->cache.समय_प्रकारo_full, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		अगर (di->opts & BQ27XXX_O_MUL_CHEM)
			val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_UNKNOWN;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_LION;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
		अगर (di->regs[BQ27XXX_REG_NAC] != INVALID_REG_ADDR)
			ret = bq27xxx_simple_value(bq27xxx_battery_पढ़ो_nac(di), val);
		अन्यथा
			ret = bq27xxx_simple_value(bq27xxx_battery_पढ़ो_rc(di), val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
		ret = bq27xxx_simple_value(di->cache.अक्षरge_full, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		ret = bq27xxx_simple_value(di->अक्षरge_design_full, val);
		अवरोध;
	/*
	 * TODO: Implement these to make रेजिस्टरs set from
	 * घातer_supply_battery_info visible in sysfs.
	 */
	हाल POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN:
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		वापस -EINVAL;
	हाल POWER_SUPPLY_PROP_CYCLE_COUNT:
		ret = bq27xxx_simple_value(di->cache.cycle_count, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_ENERGY_NOW:
		ret = bq27xxx_simple_value(di->cache.energy, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_POWER_AVG:
		ret = bq27xxx_battery_pwr_avg(di, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_HEALTH:
		ret = bq27xxx_simple_value(di->cache.health, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = BQ27XXX_MANUFACTURER;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम bq27xxx_बाह्यal_घातer_changed(काष्ठा घातer_supply *psy)
अणु
	काष्ठा bq27xxx_device_info *di = घातer_supply_get_drvdata(psy);

	cancel_delayed_work_sync(&di->work);
	schedule_delayed_work(&di->work, 0);
पूर्ण

पूर्णांक bq27xxx_battery_setup(काष्ठा bq27xxx_device_info *di)
अणु
	काष्ठा घातer_supply_desc *psy_desc;
	काष्ठा घातer_supply_config psy_cfg = अणु
		.of_node = di->dev->of_node,
		.drv_data = di,
	पूर्ण;

	INIT_DELAYED_WORK(&di->work, bq27xxx_battery_poll);
	mutex_init(&di->lock);

	di->regs       = bq27xxx_chip_data[di->chip].regs;
	di->unseal_key = bq27xxx_chip_data[di->chip].unseal_key;
	di->dm_regs    = bq27xxx_chip_data[di->chip].dm_regs;
	di->opts       = bq27xxx_chip_data[di->chip].opts;

	psy_desc = devm_kzalloc(di->dev, माप(*psy_desc), GFP_KERNEL);
	अगर (!psy_desc)
		वापस -ENOMEM;

	psy_desc->name = di->name;
	psy_desc->type = POWER_SUPPLY_TYPE_BATTERY;
	psy_desc->properties = bq27xxx_chip_data[di->chip].props;
	psy_desc->num_properties = bq27xxx_chip_data[di->chip].props_size;
	psy_desc->get_property = bq27xxx_battery_get_property;
	psy_desc->बाह्यal_घातer_changed = bq27xxx_बाह्यal_घातer_changed;

	di->bat = घातer_supply_रेजिस्टर_no_ws(di->dev, psy_desc, &psy_cfg);
	अगर (IS_ERR(di->bat))
		वापस dev_err_probe(di->dev, PTR_ERR(di->bat),
				     "failed to register battery\n");

	bq27xxx_battery_settings(di);
	bq27xxx_battery_update(di);

	mutex_lock(&bq27xxx_list_lock);
	list_add(&di->list, &bq27xxx_battery_devices);
	mutex_unlock(&bq27xxx_list_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bq27xxx_battery_setup);

व्योम bq27xxx_battery_tearकरोwn(काष्ठा bq27xxx_device_info *di)
अणु
	/*
	 * घातer_supply_unरेजिस्टर call bq27xxx_battery_get_property which
	 * call bq27xxx_battery_poll.
	 * Make sure that bq27xxx_battery_poll will not call
	 * schedule_delayed_work again after unरेजिस्टर (which cause OOPS).
	 */
	poll_पूर्णांकerval = 0;

	cancel_delayed_work_sync(&di->work);

	घातer_supply_unरेजिस्टर(di->bat);

	mutex_lock(&bq27xxx_list_lock);
	list_del(&di->list);
	mutex_unlock(&bq27xxx_list_lock);

	mutex_destroy(&di->lock);
पूर्ण
EXPORT_SYMBOL_GPL(bq27xxx_battery_tearकरोwn);

MODULE_AUTHOR("Rodolfo Giometti <giometti@linux.it>");
MODULE_DESCRIPTION("BQ27xxx battery monitor driver");
MODULE_LICENSE("GPL");
