<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * pv88060-regulator.h - Regulator definitions क्रम PV88060
 * Copyright (C) 2015 Powerventure Semiconductor Ltd.
 */

#अगर_अघोषित __PV88060_REGISTERS_H__
#घोषणा __PV88060_REGISTERS_H__

/* System Control and Event Registers */
#घोषणा	PV88060_REG_EVENT_A			0x04
#घोषणा	PV88060_REG_MASK_A			0x08
#घोषणा	PV88060_REG_MASK_B			0x09
#घोषणा	PV88060_REG_MASK_C			0x0A

/* Regulator Registers */
#घोषणा	PV88060_REG_BUCK1_CONF0			0x1B
#घोषणा	PV88060_REG_BUCK1_CONF1			0x1C
#घोषणा	PV88060_REG_LDO1_CONF			0x1D
#घोषणा	PV88060_REG_LDO2_CONF			0x1E
#घोषणा	PV88060_REG_LDO3_CONF			0x1F
#घोषणा	PV88060_REG_LDO4_CONF			0x20
#घोषणा	PV88060_REG_LDO5_CONF			0x21
#घोषणा	PV88060_REG_LDO6_CONF			0x22
#घोषणा	PV88060_REG_LDO7_CONF			0x23

#घोषणा	PV88060_REG_SW1_CONF			0x3B
#घोषणा	PV88060_REG_SW2_CONF			0x3C
#घोषणा	PV88060_REG_SW3_CONF			0x3D
#घोषणा	PV88060_REG_SW4_CONF			0x3E
#घोषणा	PV88060_REG_SW5_CONF			0x3F
#घोषणा	PV88060_REG_SW6_CONF			0x40

/* PV88060_REG_EVENT_A (addr=0x04) */
#घोषणा	PV88060_E_VDD_FLT			0x01
#घोषणा	PV88060_E_OVER_TEMP			0x02

/* PV88060_REG_MASK_A (addr=0x08) */
#घोषणा	PV88060_M_VDD_FLT			0x01
#घोषणा	PV88060_M_OVER_TEMP			0x02

/* PV88060_REG_BUCK1_CONF0 (addr=0x1B) */
#घोषणा	PV88060_BUCK_EN			0x80
#घोषणा PV88060_VBUCK_MASK			0x7F
/* PV88060_REG_LDO1/2/3/4/5/6/7_CONT */
#घोषणा	PV88060_LDO_EN			0x40
#घोषणा PV88060_VLDO_MASK			0x3F
/* PV88060_REG_SW1/2/3/4/5_CONF */
#घोषणा	PV88060_SW_EN			0x80

/* PV88060_REG_BUCK1_CONF1 (addr=0x1C) */
#घोषणा	PV88060_BUCK_ILIM_SHIFT			2
#घोषणा	PV88060_BUCK_ILIM_MASK			0x0C
#घोषणा	PV88060_BUCK_MODE_SHIFT			0
#घोषणा	PV88060_BUCK_MODE_MASK			0x03
#घोषणा	PV88060_BUCK_MODE_SLEEP			0x00
#घोषणा	PV88060_BUCK_MODE_AUTO			0x01
#घोषणा	PV88060_BUCK_MODE_SYNC			0x02

#पूर्ण_अगर	/* __PV88060_REGISTERS_H__ */
