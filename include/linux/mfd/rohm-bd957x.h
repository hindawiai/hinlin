<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Copyright (C) 2021 ROHM Semiconductors */

#अगर_अघोषित __LINUX_MFD_BD957X_H__
#घोषणा __LINUX_MFD_BD957X_H__

क्रमागत अणु
	BD957X_VD50,
	BD957X_VD18,
	BD957X_VDDDR,
	BD957X_VD10,
	BD957X_VOUTL1,
	BD957X_VOUTS1,
पूर्ण;

/*
 * The BD9576 has own IRQ 'blocks' क्रम:
 *  - I2C/thermal,
 *  - Over voltage protection
 *  - Short-circuit protection
 *  - Over current protection
 *  - Over voltage detection
 *  - Under voltage detection
 *  - Under voltage protection
 *  - 'system interrupt'.
 *
 * Each of the blocks have a status रेजिस्टर giving more accurate IRQ source
 * inक्रमmation - क्रम example which of the regulators have over-voltage.
 *
 * On top of this, there is "main IRQ" status रेजिस्टर where each bit indicates
 * which of sub-blocks have active IRQs. Fine. That would fit regmap-irq मुख्य
 * status handling. Except that:
 *  - Only some sub-IRQs can be masked.
 *  - The IRQ inक्रमms us about fault-condition, not when fault state changes.
 *    The IRQ line it is kept निश्चितed until the detected condition is acked
 *    AND cleared in HW. This is annoying क्रम IRQs like the one inक्रमming high
 *    temperature because अगर IRQ is not disabled it keeps the CPU in IRQ
 *    handling loop.
 *
 * For now we करो just use the मुख्य-IRQ रेजिस्टर as source क्रम our IRQ
 * inक्रमmation and bind the regmap-irq to this. We leave fine-grained sub-IRQ
 * रेजिस्टर handling to handlers in sub-devices. The regulator driver shall
 * पढ़ो which regulators are source क्रम problem - or अगर the detected error is
 * regulator temperature error. The sub-drivers करो also handle masking of "sub-
 * IRQs" अगर this is supported/needed.
 *
 * To overcome the problem with HW keeping IRQ निश्चितed we करो call
 * disable_irq_nosync() from sub-device handler and add a delayed work to
 * re-enable IRQ roughly 1 second later. This should keep our CPU out of
 * busy-loop.
 */
#घोषणा IRQS_SILENT_MS			1000

क्रमागत अणु
	BD9576_INT_THERM,
	BD9576_INT_OVP,
	BD9576_INT_SCP,
	BD9576_INT_OCP,
	BD9576_INT_OVD,
	BD9576_INT_UVD,
	BD9576_INT_UVP,
	BD9576_INT_SYS,
पूर्ण;

#घोषणा BD957X_REG_SMRB_ASSERT		0x15
#घोषणा BD957X_REG_PMIC_INTERNAL_STAT	0x20
#घोषणा BD957X_REG_INT_THERM_STAT	0x23
#घोषणा BD957X_REG_INT_THERM_MASK	0x24
#घोषणा BD957X_REG_INT_OVP_STAT		0x25
#घोषणा BD957X_REG_INT_SCP_STAT		0x26
#घोषणा BD957X_REG_INT_OCP_STAT		0x27
#घोषणा BD957X_REG_INT_OVD_STAT		0x28
#घोषणा BD957X_REG_INT_UVD_STAT		0x29
#घोषणा BD957X_REG_INT_UVP_STAT		0x2a
#घोषणा BD957X_REG_INT_SYS_STAT		0x2b
#घोषणा BD957X_REG_INT_SYS_MASK		0x2c
#घोषणा BD957X_REG_INT_MAIN_STAT	0x30
#घोषणा BD957X_REG_INT_MAIN_MASK	0x31

#घोषणा UVD_IRQ_VALID_MASK		0x6F
#घोषणा OVD_IRQ_VALID_MASK		0x2F

#घोषणा BD957X_MASK_INT_MAIN_THERM	BIT(0)
#घोषणा BD957X_MASK_INT_MAIN_OVP	BIT(1)
#घोषणा BD957X_MASK_INT_MAIN_SCP	BIT(2)
#घोषणा BD957X_MASK_INT_MAIN_OCP	BIT(3)
#घोषणा BD957X_MASK_INT_MAIN_OVD	BIT(4)
#घोषणा BD957X_MASK_INT_MAIN_UVD	BIT(5)
#घोषणा BD957X_MASK_INT_MAIN_UVP	BIT(6)
#घोषणा BD957X_MASK_INT_MAIN_SYS	BIT(7)
#घोषणा BD957X_MASK_INT_ALL		0xff

#घोषणा BD957X_REG_WDT_CONF		0x16

#घोषणा BD957X_REG_POW_TRIGGER1		0x41
#घोषणा BD957X_REG_POW_TRIGGER2		0x42
#घोषणा BD957X_REG_POW_TRIGGER3		0x43
#घोषणा BD957X_REG_POW_TRIGGER4		0x44
#घोषणा BD957X_REG_POW_TRIGGERL1	0x45
#घोषणा BD957X_REG_POW_TRIGGERS1	0x46

#घोषणा BD957X_REGULATOR_EN_MASK	0xff
#घोषणा BD957X_REGULATOR_DIS_VAL	0xff

#घोषणा BD957X_VSEL_REG_MASK		0xff

#घोषणा BD957X_MASK_VOUT1_TUNE		0x87
#घोषणा BD957X_MASK_VOUT2_TUNE		0x87
#घोषणा BD957X_MASK_VOUT3_TUNE		0x1f
#घोषणा BD957X_MASK_VOUT4_TUNE		0x1f
#घोषणा BD957X_MASK_VOUTL1_TUNE		0x87

#घोषणा BD957X_REG_VOUT1_TUNE		0x50
#घोषणा BD957X_REG_VOUT2_TUNE		0x53
#घोषणा BD957X_REG_VOUT3_TUNE		0x56
#घोषणा BD957X_REG_VOUT4_TUNE		0x59
#घोषणा BD957X_REG_VOUTL1_TUNE		0x5c

#घोषणा BD9576_REG_VOUT1_OVD		0x51
#घोषणा BD9576_REG_VOUT1_UVD		0x52
#घोषणा BD9576_REG_VOUT2_OVD		0x54
#घोषणा BD9576_REG_VOUT2_UVD		0x55
#घोषणा BD9576_REG_VOUT3_OVD		0x57
#घोषणा BD9576_REG_VOUT3_UVD		0x58
#घोषणा BD9576_REG_VOUT4_OVD		0x5a
#घोषणा BD9576_REG_VOUT4_UVD		0x5b
#घोषणा BD9576_REG_VOUTL1_OVD		0x5d
#घोषणा BD9576_REG_VOUTL1_UVD		0x5e

#घोषणा BD9576_MASK_XVD			0x7f

#घोषणा BD9576_REG_VOUT1S_OCW		0x5f
#घोषणा BD9576_REG_VOUT1S_OCP		0x60

#घोषणा BD9576_MASK_VOUT1S_OCW		0x3f
#घोषणा BD9576_MASK_VOUT1S_OCP		0x3f

#घोषणा BD957X_MAX_REGISTER		0x61

#पूर्ण_अगर
