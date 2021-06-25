<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm8350-regmap.c  --  Wolfson Microelectronics WM8350 रेजिस्टर map
 *
 * This file splits out the tables describing the शेषs and access
 * status of the WM8350 रेजिस्टरs since they are rather large.
 *
 * Copyright 2007, 2008 Wolfson Microelectronics PLC.
 */

#समावेश <linux/mfd/wm8350/core.h>

/*
 * Access masks.
 */

अटल स्थिर काष्ठा wm8350_reg_access अणु
	u16 पढ़ोable;		/* Mask of पढ़ोable bits */
	u16 writable;		/* Mask of writable bits */
	u16 vol;		/* Mask of अस्थिर bits */
पूर्ण wm8350_reg_io_map[] = अणु
	/*  पढ़ो    ग_लिखो अस्थिर */
	अणु 0xFFFF, 0xFFFF, 0x0000 पूर्ण, /* R0   - Reset/ID */
	अणु 0x7CFF, 0x0C00, 0x0000 पूर्ण, /* R1   - ID */
	अणु 0x007F, 0x0000, 0x0000 पूर्ण, /* R2   - ROM Mask ID */
	अणु 0xBE3B, 0xBE3B, 0x8000 पूर्ण, /* R3   - System Control 1 */
	अणु 0xFEF7, 0xFEF7, 0xF800 पूर्ण, /* R4   - System Control 2 */
	अणु 0x80FF, 0x80FF, 0x8000 पूर्ण, /* R5   - System Hibernate */
	अणु 0xFB0E, 0xFB0E, 0x0000 पूर्ण, /* R6   - Interface Control */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R7 */
	अणु 0xE537, 0xE537, 0xFFFF पूर्ण, /* R8   - Power mgmt (1) */
	अणु 0x0FF3, 0x0FF3, 0xFFFF पूर्ण, /* R9   - Power mgmt (2) */
	अणु 0x008F, 0x008F, 0xFFFF पूर्ण, /* R10  - Power mgmt (3) */
	अणु 0x6D3C, 0x6D3C, 0xFFFF पूर्ण, /* R11  - Power mgmt (4) */
	अणु 0x1F8F, 0x1F8F, 0xFFFF पूर्ण, /* R12  - Power mgmt (5) */
	अणु 0x8F3F, 0x8F3F, 0xFFFF पूर्ण, /* R13  - Power mgmt (6) */
	अणु 0x0003, 0x0003, 0xFFFF पूर्ण, /* R14  - Power mgmt (7) */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R15 */
	अणु 0x7F7F, 0x7F7F, 0xFFFF पूर्ण, /* R16  - RTC Seconds/Minutes */
	अणु 0x073F, 0x073F, 0xFFFF पूर्ण, /* R17  - RTC Hours/Day */
	अणु 0x1F3F, 0x1F3F, 0xFFFF पूर्ण, /* R18  - RTC Date/Month */
	अणु 0x3FFF, 0x00FF, 0xFFFF पूर्ण, /* R19  - RTC Year */
	अणु 0x7F7F, 0x7F7F, 0x0000 पूर्ण, /* R20  - Alarm Seconds/Minutes */
	अणु 0x0F3F, 0x0F3F, 0x0000 पूर्ण, /* R21  - Alarm Hours/Day */
	अणु 0x1F3F, 0x1F3F, 0x0000 पूर्ण, /* R22  - Alarm Date/Month */
	अणु 0xEF7F, 0xEA7F, 0xFFFF पूर्ण, /* R23  - RTC Time Control */
	अणु 0x3BFF, 0x0000, 0xFFFF पूर्ण, /* R24  - System Interrupts */
	अणु 0xFEE7, 0x0000, 0xFFFF पूर्ण, /* R25  - Interrupt Status 1 */
	अणु 0x35FF, 0x0000, 0xFFFF पूर्ण, /* R26  - Interrupt Status 2 */
	अणु 0x0F3F, 0x0000, 0xFFFF पूर्ण, /* R27  - Power Up Interrupt Status */
	अणु 0x0F3F, 0x0000, 0xFFFF पूर्ण, /* R28  - Under Voltage Interrupt status */
	अणु 0x8000, 0x0000, 0xFFFF पूर्ण, /* R29  - Over Current Interrupt status */
	अणु 0x1FFF, 0x0000, 0xFFFF पूर्ण, /* R30  - GPIO Interrupt Status */
	अणु 0xEF7F, 0x0000, 0xFFFF पूर्ण, /* R31  - Comparator Interrupt Status */
	अणु 0x3FFF, 0x3FFF, 0x0000 पूर्ण, /* R32  - System Interrupts Mask */
	अणु 0xFEE7, 0xFEE7, 0x0000 पूर्ण, /* R33  - Interrupt Status 1 Mask */
	अणु 0xF5FF, 0xF5FF, 0x0000 पूर्ण, /* R34  - Interrupt Status 2 Mask */
	अणु 0x0F3F, 0x0F3F, 0x0000 पूर्ण, /* R35  - Power Up Interrupt Status Mask */
	अणु 0x0F3F, 0x0F3F, 0x0000 पूर्ण, /* R36  - Under Voltage Int status Mask */
	अणु 0x8000, 0x8000, 0x0000 पूर्ण, /* R37  - Over Current Int status Mask */
	अणु 0x1FFF, 0x1FFF, 0x0000 पूर्ण, /* R38  - GPIO Interrupt Status Mask */
	अणु 0xEF7F, 0xEF7F, 0x0000 पूर्ण, /* R39  - Comparator IntStatus Mask */
	अणु 0xC9F7, 0xC9F7, 0xFFFF पूर्ण, /* R40  - Clock Control 1 */
	अणु 0x8001, 0x8001, 0x0000 पूर्ण, /* R41  - Clock Control 2 */
	अणु 0xFFF7, 0xFFF7, 0xFFFF पूर्ण, /* R42  - FLL Control 1 */
	अणु 0xFBFF, 0xFBFF, 0x0000 पूर्ण, /* R43  - FLL Control 2 */
	अणु 0xFFFF, 0xFFFF, 0x0000 पूर्ण, /* R44  - FLL Control 3 */
	अणु 0x0033, 0x0033, 0x0000 पूर्ण, /* R45  - FLL Control 4 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R46 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R47 */
	अणु 0x3033, 0x3033, 0x0000 पूर्ण, /* R48  - DAC Control */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R49 */
	अणु 0x81FF, 0x81FF, 0xFFFF पूर्ण, /* R50  - DAC Digital Volume L */
	अणु 0x81FF, 0x81FF, 0xFFFF पूर्ण, /* R51  - DAC Digital Volume R */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R52 */
	अणु 0x0FFF, 0x0FFF, 0xFFFF पूर्ण, /* R53  - DAC LR Rate */
	अणु 0x0017, 0x0017, 0x0000 पूर्ण, /* R54  - DAC Clock Control */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R55 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R56 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R57 */
	अणु 0x4000, 0x4000, 0x0000 पूर्ण, /* R58  - DAC Mute */
	अणु 0x7000, 0x7000, 0x0000 पूर्ण, /* R59  - DAC Mute Volume */
	अणु 0x3C00, 0x3C00, 0x0000 पूर्ण, /* R60  - DAC Side */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R61 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R62 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R63 */
	अणु 0x8303, 0x8303, 0xFFFF पूर्ण, /* R64  - ADC Control */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R65 */
	अणु 0x81FF, 0x81FF, 0xFFFF पूर्ण, /* R66  - ADC Digital Volume L */
	अणु 0x81FF, 0x81FF, 0xFFFF पूर्ण, /* R67  - ADC Digital Volume R */
	अणु 0x0FFF, 0x0FFF, 0x0000 पूर्ण, /* R68  - ADC Divider */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R69 */
	अणु 0x0FFF, 0x0FFF, 0xFFFF पूर्ण, /* R70  - ADC LR Rate */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R71 */
	अणु 0x0707, 0x0707, 0xFFFF पूर्ण, /* R72  - Input Control */
	अणु 0xC0C0, 0xC0C0, 0xFFFF पूर्ण, /* R73  - IN3 Input Control */
	अणु 0xC09F, 0xC09F, 0xFFFF पूर्ण, /* R74  - Mic Bias Control */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R75 */
	अणु 0x0F15, 0x0F15, 0xFFFF पूर्ण, /* R76  - Output Control */
	अणु 0xC000, 0xC000, 0xFFFF पूर्ण, /* R77  - Jack Detect */
	अणु 0x03FF, 0x03FF, 0x0000 पूर्ण, /* R78  - Anti Pop Control */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R79 */
	अणु 0xE1FC, 0xE1FC, 0x8000 पूर्ण, /* R80  - Left Input Volume */
	अणु 0xE1FC, 0xE1FC, 0x8000 पूर्ण, /* R81  - Right Input Volume */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R82 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R83 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R84 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R85 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R86 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R87 */
	अणु 0x9807, 0x9807, 0xFFFF पूर्ण, /* R88  - Left Mixer Control */
	अणु 0x980B, 0x980B, 0xFFFF पूर्ण, /* R89  - Right Mixer Control */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R90 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R91 */
	अणु 0x8909, 0x8909, 0xFFFF पूर्ण, /* R92  - OUT3 Mixer Control */
	अणु 0x9E07, 0x9E07, 0xFFFF पूर्ण, /* R93  - OUT4 Mixer Control */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R94 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R95 */
	अणु 0x0EEE, 0x0EEE, 0x0000 पूर्ण, /* R96  - Output Left Mixer Volume */
	अणु 0xE0EE, 0xE0EE, 0x0000 पूर्ण, /* R97  - Output Right Mixer Volume */
	अणु 0x0E0F, 0x0E0F, 0x0000 पूर्ण, /* R98  - Input Mixer Volume L */
	अणु 0xE0E1, 0xE0E1, 0x0000 पूर्ण, /* R99  - Input Mixer Volume R */
	अणु 0x800E, 0x800E, 0x0000 पूर्ण, /* R100 - Input Mixer Volume */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R101 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R102 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R103 */
	अणु 0xE1FC, 0xE1FC, 0xFFFF पूर्ण, /* R104 - LOUT1 Volume */
	अणु 0xE1FC, 0xE1FC, 0xFFFF पूर्ण, /* R105 - ROUT1 Volume */
	अणु 0xE1FC, 0xE1FC, 0xFFFF पूर्ण, /* R106 - LOUT2 Volume */
	अणु 0xE7FC, 0xE7FC, 0xFFFF पूर्ण, /* R107 - ROUT2 Volume */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R108 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R109 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R110 */
	अणु 0x80E0, 0x80E0, 0xFFFF पूर्ण, /* R111 - BEEP Volume */
	अणु 0xBF00, 0xBF00, 0x0000 पूर्ण, /* R112 - AI Formating */
	अणु 0x00F1, 0x00F1, 0x0000 पूर्ण, /* R113 - ADC DAC COMP */
	अणु 0x00F8, 0x00F8, 0x0000 पूर्ण, /* R114 - AI ADC Control */
	अणु 0x40FB, 0x40FB, 0x0000 पूर्ण, /* R115 - AI DAC Control */
	अणु 0x7C30, 0x7C30, 0x0000 पूर्ण, /* R116 - AIF Test */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R117 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R118 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R119 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R120 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R121 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R122 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R123 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R124 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R125 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R126 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R127 */
	अणु 0x1FFF, 0x1FFF, 0x0000 पूर्ण, /* R128 - GPIO Debounce */
	अणु 0x1FFF, 0x1FFF, 0x0000 पूर्ण, /* R129 - GPIO Pin pull up Control */
	अणु 0x1FFF, 0x1FFF, 0x0000 पूर्ण, /* R130 - GPIO Pull करोwn Control */
	अणु 0x1FFF, 0x1FFF, 0x0000 पूर्ण, /* R131 - GPIO Interrupt Mode */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R132 */
	अणु 0x00C0, 0x00C0, 0x0000 पूर्ण, /* R133 - GPIO Control */
	अणु 0x1FFF, 0x1FFF, 0x0000 पूर्ण, /* R134 - GPIO Configuration (i/o) */
	अणु 0x1FFF, 0x1FFF, 0x0000 पूर्ण, /* R135 - GPIO Pin Polarity / Type */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R136 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R137 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R138 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R139 */
	अणु 0xFFFF, 0xFFFF, 0x0000 पूर्ण, /* R140 - GPIO Function Select 1 */
	अणु 0xFFFF, 0xFFFF, 0x0000 पूर्ण, /* R141 - GPIO Function Select 2 */
	अणु 0xFFFF, 0xFFFF, 0x0000 पूर्ण, /* R142 - GPIO Function Select 3 */
	अणु 0x000F, 0x000F, 0x0000 पूर्ण, /* R143 - GPIO Function Select 4 */
	अणु 0xF0FF, 0xF0FF, 0xA000 पूर्ण, /* R144 - Digitiser Control (1) */
	अणु 0x3707, 0x3707, 0x0000 पूर्ण, /* R145 - Digitiser Control (2) */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R146 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R147 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R148 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R149 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R150 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R151 */
	अणु 0x7FFF, 0x7000, 0xFFFF पूर्ण, /* R152 - AUX1 Readback */
	अणु 0x7FFF, 0x7000, 0xFFFF पूर्ण, /* R153 - AUX2 Readback */
	अणु 0x7FFF, 0x7000, 0xFFFF पूर्ण, /* R154 - AUX3 Readback */
	अणु 0x7FFF, 0x7000, 0xFFFF पूर्ण, /* R155 - AUX4 Readback */
	अणु 0x0FFF, 0x0000, 0xFFFF पूर्ण, /* R156 - USB Voltage Readback */
	अणु 0x0FFF, 0x0000, 0xFFFF पूर्ण, /* R157 - LINE Voltage Readback */
	अणु 0x0FFF, 0x0000, 0xFFFF पूर्ण, /* R158 - BATT Voltage Readback */
	अणु 0x0FFF, 0x0000, 0xFFFF पूर्ण, /* R159 - Chip Temp Readback */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R160 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R161 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R162 */
	अणु 0x000F, 0x000F, 0x0000 पूर्ण, /* R163 - Generic Comparator Control */
	अणु 0xFFFF, 0xFFFF, 0x0000 पूर्ण, /* R164 - Generic comparator 1 */
	अणु 0xFFFF, 0xFFFF, 0x0000 पूर्ण, /* R165 - Generic comparator 2 */
	अणु 0xFFFF, 0xFFFF, 0x0000 पूर्ण, /* R166 - Generic comparator 3 */
	अणु 0xFFFF, 0xFFFF, 0x0000 पूर्ण, /* R167 - Generic comparator 4 */
	अणु 0xBFFF, 0xBFFF, 0x8000 पूर्ण, /* R168 - Battery Charger Control 1 */
	अणु 0xFFFF, 0x4FFF, 0xB000 पूर्ण, /* R169 - Battery Charger Control 2 */
	अणु 0x007F, 0x007F, 0x0000 पूर्ण, /* R170 - Battery Charger Control 3 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R171 */
	अणु 0x903F, 0x903F, 0xFFFF पूर्ण, /* R172 - Current Sink Driver A */
	अणु 0xE333, 0xE333, 0xFFFF पूर्ण, /* R173 - CSA Flash control */
	अणु 0x903F, 0x903F, 0xFFFF पूर्ण, /* R174 - Current Sink Driver B */
	अणु 0xE333, 0xE333, 0xFFFF पूर्ण, /* R175 - CSB Flash control */
	अणु 0x8F3F, 0x8F3F, 0xFFFF पूर्ण, /* R176 - DCDC/LDO requested */
	अणु 0x332D, 0x332D, 0x0000 पूर्ण, /* R177 - DCDC Active options */
	अणु 0x002D, 0x002D, 0x0000 पूर्ण, /* R178 - DCDC Sleep options */
	अणु 0x5177, 0x5177, 0x8000 पूर्ण, /* R179 - Power-check comparator */
	अणु 0x047F, 0x047F, 0x0000 पूर्ण, /* R180 - DCDC1 Control */
	अणु 0xFFC0, 0xFFC0, 0x0000 पूर्ण, /* R181 - DCDC1 Timeouts */
	अणु 0x737F, 0x737F, 0x0000 पूर्ण, /* R182 - DCDC1 Low Power */
	अणु 0x535B, 0x535B, 0x0000 पूर्ण, /* R183 - DCDC2 Control */
	अणु 0xFFC0, 0xFFC0, 0x0000 पूर्ण, /* R184 - DCDC2 Timeouts */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R185 */
	अणु 0x047F, 0x047F, 0x0000 पूर्ण, /* R186 - DCDC3 Control */
	अणु 0xFFC0, 0xFFC0, 0x0000 पूर्ण, /* R187 - DCDC3 Timeouts */
	अणु 0x737F, 0x737F, 0x0000 पूर्ण, /* R188 - DCDC3 Low Power */
	अणु 0x047F, 0x047F, 0x0000 पूर्ण, /* R189 - DCDC4 Control */
	अणु 0xFFC0, 0xFFC0, 0x0000 पूर्ण, /* R190 - DCDC4 Timeouts */
	अणु 0x737F, 0x737F, 0x0000 पूर्ण, /* R191 - DCDC4 Low Power */
	अणु 0x535B, 0x535B, 0x0000 पूर्ण, /* R192 - DCDC5 Control */
	अणु 0xFFC0, 0xFFC0, 0x0000 पूर्ण, /* R193 - DCDC5 Timeouts */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R194 */
	अणु 0x047F, 0x047F, 0x0000 पूर्ण, /* R195 - DCDC6 Control */
	अणु 0xFFC0, 0xFFC0, 0x0000 पूर्ण, /* R196 - DCDC6 Timeouts */
	अणु 0x737F, 0x737F, 0x0000 पूर्ण, /* R197 - DCDC6 Low Power */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R198 */
	अणु 0xFFD3, 0xFFD3, 0x0000 पूर्ण, /* R199 - Limit Switch Control */
	अणु 0x441F, 0x441F, 0x0000 पूर्ण, /* R200 - LDO1 Control */
	अणु 0xFFC0, 0xFFC0, 0x0000 पूर्ण, /* R201 - LDO1 Timeouts */
	अणु 0x331F, 0x331F, 0x0000 पूर्ण, /* R202 - LDO1 Low Power */
	अणु 0x441F, 0x441F, 0x0000 पूर्ण, /* R203 - LDO2 Control */
	अणु 0xFFC0, 0xFFC0, 0x0000 पूर्ण, /* R204 - LDO2 Timeouts */
	अणु 0x331F, 0x331F, 0x0000 पूर्ण, /* R205 - LDO2 Low Power */
	अणु 0x441F, 0x441F, 0x0000 पूर्ण, /* R206 - LDO3 Control */
	अणु 0xFFC0, 0xFFC0, 0x0000 पूर्ण, /* R207 - LDO3 Timeouts */
	अणु 0x331F, 0x331F, 0x0000 पूर्ण, /* R208 - LDO3 Low Power */
	अणु 0x441F, 0x441F, 0x0000 पूर्ण, /* R209 - LDO4 Control */
	अणु 0xFFC0, 0xFFC0, 0x0000 पूर्ण, /* R210 - LDO4 Timeouts */
	अणु 0x331F, 0x331F, 0x0000 पूर्ण, /* R211 - LDO4 Low Power */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R212 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R213 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R214 */
	अणु 0x8F3F, 0x8F3F, 0x0000 पूर्ण, /* R215 - VCC_FAULT Masks */
	अणु 0xFF3F, 0xE03F, 0x0000 पूर्ण, /* R216 - Main Bandgap Control */
	अणु 0xEF2F, 0xE02F, 0x0000 पूर्ण, /* R217 - OSC Control */
	अणु 0xF3FF, 0xB3FF, 0xc000 पूर्ण, /* R218 - RTC Tick Control */
	अणु 0xFFFF, 0xFFFF, 0x0000 पूर्ण, /* R219 - Security */
	अणु 0x09FF, 0x01FF, 0x0000 पूर्ण, /* R220 - RAM BIST 1 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R221 */
	अणु 0xFFFF, 0xFFFF, 0xFFFF पूर्ण, /* R222 */
	अणु 0xFFFF, 0xFFFF, 0xFFFF पूर्ण, /* R223 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R224 */
	अणु 0x8F3F, 0x0000, 0xFFFF पूर्ण, /* R225 - DCDC/LDO status */
	अणु 0x0000, 0x0000, 0xFFFF पूर्ण, /* R226 - Charger status */
	अणु 0x34FE, 0x0000, 0xFFFF पूर्ण, /* R227 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R228 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R229 */
	अणु 0xFFFF, 0x1FFF, 0xFFFF पूर्ण, /* R230 - GPIO Pin Status */
	अणु 0xFFFF, 0x1FFF, 0xFFFF पूर्ण, /* R231 */
	अणु 0xFFFF, 0x1FFF, 0xFFFF पूर्ण, /* R232 */
	अणु 0xFFFF, 0x1FFF, 0xFFFF पूर्ण, /* R233 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R234 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R235 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R236 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R237 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R238 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R239 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R240 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R241 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R242 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R243 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R244 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R245 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R246 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R247 */
	अणु 0xFFFF, 0x0010, 0xFFFF पूर्ण, /* R248 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R249 */
	अणु 0xFFFF, 0x0010, 0xFFFF पूर्ण, /* R250 */
	अणु 0xFFFF, 0x0010, 0xFFFF पूर्ण, /* R251 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R252 */
	अणु 0xFFFF, 0x0010, 0xFFFF पूर्ण, /* R253 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R254 */
	अणु 0x0000, 0x0000, 0x0000 पूर्ण, /* R255 */
पूर्ण;

अटल bool wm8350_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस wm8350_reg_io_map[reg].पढ़ोable;
पूर्ण

अटल bool wm8350_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा wm8350 *wm8350 = dev_get_drvdata(dev);

	अगर (!wm8350->unlocked) अणु
		अगर ((reg >= WM8350_GPIO_FUNCTION_SELECT_1 &&
		     reg <= WM8350_GPIO_FUNCTION_SELECT_4) ||
		    (reg >= WM8350_BATTERY_CHARGER_CONTROL_1 &&
		     reg <= WM8350_BATTERY_CHARGER_CONTROL_3))
			वापस false;
	पूर्ण

	वापस wm8350_reg_io_map[reg].writable;
पूर्ण

अटल bool wm8350_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस wm8350_reg_io_map[reg].vol;
पूर्ण

अटल bool wm8350_precious(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8350_SYSTEM_INTERRUPTS:
	हाल WM8350_INT_STATUS_1:
	हाल WM8350_INT_STATUS_2:
	हाल WM8350_POWER_UP_INT_STATUS:
	हाल WM8350_UNDER_VOLTAGE_INT_STATUS:
	हाल WM8350_OVER_CURRENT_INT_STATUS:
	हाल WM8350_GPIO_INT_STATUS:
	हाल WM8350_COMPARATOR_INT_STATUS:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

स्थिर काष्ठा regmap_config wm8350_regmap = अणु
	.reg_bits = 8,
	.val_bits = 16,

	.cache_type = REGCACHE_RBTREE,

	.max_रेजिस्टर = WM8350_MAX_REGISTER,
	.पढ़ोable_reg = wm8350_पढ़ोable,
	.ग_लिखोable_reg = wm8350_ग_लिखोable,
	.अस्थिर_reg = wm8350_अस्थिर,
	.precious_reg = wm8350_precious,
पूर्ण;
