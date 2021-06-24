<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * comparator.h  --  Comparator Aux ADC क्रम Wolfson WM8350 PMIC
 *
 * Copyright 2007 Wolfson Microelectronics PLC
 */

#अगर_अघोषित __LINUX_MFD_WM8350_COMPARATOR_H_
#घोषणा __LINUX_MFD_WM8350_COMPARATOR_H_

/*
 * Registers
 */

#घोषणा WM8350_DIGITISER_CONTROL_1              0x90
#घोषणा WM8350_DIGITISER_CONTROL_2              0x91
#घोषणा WM8350_AUX1_READBACK                    0x98
#घोषणा WM8350_AUX2_READBACK                    0x99
#घोषणा WM8350_AUX3_READBACK                    0x9A
#घोषणा WM8350_AUX4_READBACK                    0x9B
#घोषणा WM8350_CHIP_TEMP_READBACK               0x9F
#घोषणा WM8350_GENERIC_COMPARATOR_CONTROL       0xA3
#घोषणा WM8350_GENERIC_COMPARATOR_1             0xA4
#घोषणा WM8350_GENERIC_COMPARATOR_2             0xA5
#घोषणा WM8350_GENERIC_COMPARATOR_3             0xA6
#घोषणा WM8350_GENERIC_COMPARATOR_4             0xA7

/*
 * R144 (0x90) - Digitiser Control (1)
 */
#घोषणा WM8350_AUXADC_CTC                       0x4000
#घोषणा WM8350_AUXADC_POLL                      0x2000
#घोषणा WM8350_AUXADC_HIB_MODE                  0x1000
#घोषणा WM8350_AUXADC_SEL8                      0x0080
#घोषणा WM8350_AUXADC_SEL7                      0x0040
#घोषणा WM8350_AUXADC_SEL6                      0x0020
#घोषणा WM8350_AUXADC_SEL5                      0x0010
#घोषणा WM8350_AUXADC_SEL4                      0x0008
#घोषणा WM8350_AUXADC_SEL3                      0x0004
#घोषणा WM8350_AUXADC_SEL2                      0x0002
#घोषणा WM8350_AUXADC_SEL1                      0x0001

/*
 * R145 (0x91) - Digitiser Control (2)
 */
#घोषणा WM8350_AUXADC_MASKMODE_MASK             0x3000
#घोषणा WM8350_AUXADC_CRATE_MASK                0x0700
#घोषणा WM8350_AUXADC_CAL                       0x0004
#घोषणा WM8350_AUX_RBMODE                       0x0002
#घोषणा WM8350_AUXADC_WAIT                      0x0001

/*
 * R152 (0x98) - AUX1 Readback
 */
#घोषणा WM8350_AUXADC_SCALE1_MASK               0x6000
#घोषणा WM8350_AUXADC_REF1                      0x1000
#घोषणा WM8350_AUXADC_DATA1_MASK                0x0FFF

/*
 * R153 (0x99) - AUX2 Readback
 */
#घोषणा WM8350_AUXADC_SCALE2_MASK               0x6000
#घोषणा WM8350_AUXADC_REF2                      0x1000
#घोषणा WM8350_AUXADC_DATA2_MASK                0x0FFF

/*
 * R154 (0x9A) - AUX3 Readback
 */
#घोषणा WM8350_AUXADC_SCALE3_MASK               0x6000
#घोषणा WM8350_AUXADC_REF3                      0x1000
#घोषणा WM8350_AUXADC_DATA3_MASK                0x0FFF

/*
 * R155 (0x9B) - AUX4 Readback
 */
#घोषणा WM8350_AUXADC_SCALE4_MASK               0x6000
#घोषणा WM8350_AUXADC_REF4                      0x1000
#घोषणा WM8350_AUXADC_DATA4_MASK                0x0FFF

/*
 * R156 (0x9C) - USB Voltage Readback
 */
#घोषणा WM8350_AUXADC_DATA_USB_MASK             0x0FFF

/*
 * R157 (0x9D) - LINE Voltage Readback
 */
#घोषणा WM8350_AUXADC_DATA_LINE_MASK            0x0FFF

/*
 * R158 (0x9E) - BATT Voltage Readback
 */
#घोषणा WM8350_AUXADC_DATA_BATT_MASK            0x0FFF

/*
 * R159 (0x9F) - Chip Temp Readback
 */
#घोषणा WM8350_AUXADC_DATA_CHIPTEMP_MASK        0x0FFF

/*
 * R163 (0xA3) - Generic Comparator Control
 */
#घोषणा WM8350_DCMP4_ENA                        0x0008
#घोषणा WM8350_DCMP3_ENA                        0x0004
#घोषणा WM8350_DCMP2_ENA                        0x0002
#घोषणा WM8350_DCMP1_ENA                        0x0001

/*
 * R164 (0xA4) - Generic comparator 1
 */
#घोषणा WM8350_DCMP1_SRCSEL_MASK                0xE000
#घोषणा WM8350_DCMP1_GT                         0x1000
#घोषणा WM8350_DCMP1_THR_MASK                   0x0FFF

/*
 * R165 (0xA5) - Generic comparator 2
 */
#घोषणा WM8350_DCMP2_SRCSEL_MASK                0xE000
#घोषणा WM8350_DCMP2_GT                         0x1000
#घोषणा WM8350_DCMP2_THR_MASK                   0x0FFF

/*
 * R166 (0xA6) - Generic comparator 3
 */
#घोषणा WM8350_DCMP3_SRCSEL_MASK                0xE000
#घोषणा WM8350_DCMP3_GT                         0x1000
#घोषणा WM8350_DCMP3_THR_MASK                   0x0FFF

/*
 * R167 (0xA7) - Generic comparator 4
 */
#घोषणा WM8350_DCMP4_SRCSEL_MASK                0xE000
#घोषणा WM8350_DCMP4_GT                         0x1000
#घोषणा WM8350_DCMP4_THR_MASK                   0x0FFF

/*
 * Interrupts.
 */
#घोषणा WM8350_IRQ_AUXADC_DATARDY		16
#घोषणा WM8350_IRQ_AUXADC_DCOMP4		17
#घोषणा WM8350_IRQ_AUXADC_DCOMP3		18
#घोषणा WM8350_IRQ_AUXADC_DCOMP2		19
#घोषणा WM8350_IRQ_AUXADC_DCOMP1		20
#घोषणा WM8350_IRQ_SYS_HYST_COMP_FAIL		21
#घोषणा WM8350_IRQ_SYS_CHIP_GT115		22
#घोषणा WM8350_IRQ_SYS_CHIP_GT140		23

/*
 * USB/2, LINE & BATT = ((VRTC * 2) / 4095)) * 10e6 uV
 * Where VRTC = 2.7 V
 */
#घोषणा WM8350_AUX_COEFF			1319

#घोषणा WM8350_AUXADC_AUX1			0
#घोषणा WM8350_AUXADC_AUX2			1
#घोषणा WM8350_AUXADC_AUX3			2
#घोषणा WM8350_AUXADC_AUX4			3
#घोषणा WM8350_AUXADC_USB			4
#घोषणा WM8350_AUXADC_LINE			5
#घोषणा WM8350_AUXADC_BATT			6
#घोषणा WM8350_AUXADC_TEMP			7

काष्ठा wm8350;

/*
 * AUX ADC Readback
 */
पूर्णांक wm8350_पढ़ो_auxadc(काष्ठा wm8350 *wm8350, पूर्णांक channel, पूर्णांक scale,
		       पूर्णांक vref);

#पूर्ण_अगर
