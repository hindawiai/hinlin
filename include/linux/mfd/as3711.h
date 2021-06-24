<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AS3711 PMIC MFC driver header
 *
 * Copyright (C) 2012 Renesas Electronics Corporation
 * Author: Guennadi Liakhovetski, <g.liakhovetski@gmx.de>
 */

#अगर_अघोषित MFD_AS3711_H
#घोषणा MFD_AS3711_H

/*
 * Client data
 */

/* Register addresses */
#घोषणा AS3711_SD_1_VOLTAGE		0	/* Digital Step-Down */
#घोषणा AS3711_SD_2_VOLTAGE		1
#घोषणा AS3711_SD_3_VOLTAGE		2
#घोषणा AS3711_SD_4_VOLTAGE		3
#घोषणा AS3711_LDO_1_VOLTAGE		4	/* Analog LDO */
#घोषणा AS3711_LDO_2_VOLTAGE		5
#घोषणा AS3711_LDO_3_VOLTAGE		6	/* Digital LDO */
#घोषणा AS3711_LDO_4_VOLTAGE		7
#घोषणा AS3711_LDO_5_VOLTAGE		8
#घोषणा AS3711_LDO_6_VOLTAGE		9
#घोषणा AS3711_LDO_7_VOLTAGE		0xa
#घोषणा AS3711_LDO_8_VOLTAGE		0xb
#घोषणा AS3711_SD_CONTROL		0x10
#घोषणा AS3711_GPIO_SIGNAL_OUT		0x20
#घोषणा AS3711_GPIO_SIGNAL_IN		0x21
#घोषणा AS3711_SD_CONTROL_1		0x30
#घोषणा AS3711_SD_CONTROL_2		0x31
#घोषणा AS3711_CURR_CONTROL		0x40
#घोषणा AS3711_CURR1_VALUE		0x43
#घोषणा AS3711_CURR2_VALUE		0x44
#घोषणा AS3711_CURR3_VALUE		0x45
#घोषणा AS3711_STEPUP_CONTROL_1		0x50
#घोषणा AS3711_STEPUP_CONTROL_2		0x51
#घोषणा AS3711_STEPUP_CONTROL_4		0x53
#घोषणा AS3711_STEPUP_CONTROL_5		0x54
#घोषणा AS3711_REG_STATUS		0x73
#घोषणा AS3711_INTERRUPT_STATUS_1	0x77
#घोषणा AS3711_INTERRUPT_STATUS_2	0x78
#घोषणा AS3711_INTERRUPT_STATUS_3	0x79
#घोषणा AS3711_CHARGER_STATUS_1		0x86
#घोषणा AS3711_CHARGER_STATUS_2		0x87
#घोषणा AS3711_ASIC_ID_1		0x90
#घोषणा AS3711_ASIC_ID_2		0x91

#घोषणा AS3711_MAX_REG		AS3711_ASIC_ID_2
#घोषणा AS3711_NUM_REGS		(AS3711_MAX_REG + 1)

/* Regulators */
क्रमागत अणु
	AS3711_REGULATOR_SD_1,
	AS3711_REGULATOR_SD_2,
	AS3711_REGULATOR_SD_3,
	AS3711_REGULATOR_SD_4,
	AS3711_REGULATOR_LDO_1,
	AS3711_REGULATOR_LDO_2,
	AS3711_REGULATOR_LDO_3,
	AS3711_REGULATOR_LDO_4,
	AS3711_REGULATOR_LDO_5,
	AS3711_REGULATOR_LDO_6,
	AS3711_REGULATOR_LDO_7,
	AS3711_REGULATOR_LDO_8,

	AS3711_REGULATOR_MAX,
पूर्ण;

काष्ठा device;
काष्ठा regmap;

काष्ठा as3711 अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
पूर्ण;

#घोषणा AS3711_MAX_STEPDOWN 4
#घोषणा AS3711_MAX_STEPUP 2
#घोषणा AS3711_MAX_LDO 8

क्रमागत as3711_su2_feedback अणु
	AS3711_SU2_VOLTAGE,
	AS3711_SU2_CURR1,
	AS3711_SU2_CURR2,
	AS3711_SU2_CURR3,
	AS3711_SU2_CURR_AUTO,
पूर्ण;

क्रमागत as3711_su2_fbprot अणु
	AS3711_SU2_LX_SD4,
	AS3711_SU2_GPIO2,
	AS3711_SU2_GPIO3,
	AS3711_SU2_GPIO4,
पूर्ण;

/*
 * Platक्रमm data
 */

काष्ठा as3711_regulator_pdata अणु
	काष्ठा regulator_init_data *init_data[AS3711_REGULATOR_MAX];
पूर्ण;

काष्ठा as3711_bl_pdata अणु
	bool su1_fb;
	पूर्णांक su1_max_uA;
	bool su2_fb;
	पूर्णांक su2_max_uA;
	क्रमागत as3711_su2_feedback su2_feedback;
	क्रमागत as3711_su2_fbprot su2_fbprot;
	bool su2_स्वतः_curr1;
	bool su2_स्वतः_curr2;
	bool su2_स्वतः_curr3;
पूर्ण;

काष्ठा as3711_platक्रमm_data अणु
	काष्ठा as3711_regulator_pdata regulator;
	काष्ठा as3711_bl_pdata backlight;
पूर्ण;

#पूर्ण_अगर
