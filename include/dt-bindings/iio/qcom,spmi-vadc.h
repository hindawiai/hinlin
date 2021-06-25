<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2012-2014,2018,2020 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DT_BINDINGS_QCOM_SPMI_VADC_H
#घोषणा _DT_BINDINGS_QCOM_SPMI_VADC_H

/* Voltage ADC channels */
#घोषणा VADC_USBIN				0x00
#घोषणा VADC_DCIN				0x01
#घोषणा VADC_VCHG_SNS				0x02
#घोषणा VADC_SPARE1_03				0x03
#घोषणा VADC_USB_ID_MV				0x04
#घोषणा VADC_VCOIN				0x05
#घोषणा VADC_VBAT_SNS				0x06
#घोषणा VADC_VSYS				0x07
#घोषणा VADC_DIE_TEMP				0x08
#घोषणा VADC_REF_625MV				0x09
#घोषणा VADC_REF_1250MV				0x0a
#घोषणा VADC_CHG_TEMP				0x0b
#घोषणा VADC_SPARE1				0x0c
#घोषणा VADC_SPARE2				0x0d
#घोषणा VADC_GND_REF				0x0e
#घोषणा VADC_VDD_VADC				0x0f

#घोषणा VADC_P_MUX1_1_1				0x10
#घोषणा VADC_P_MUX2_1_1				0x11
#घोषणा VADC_P_MUX3_1_1				0x12
#घोषणा VADC_P_MUX4_1_1				0x13
#घोषणा VADC_P_MUX5_1_1				0x14
#घोषणा VADC_P_MUX6_1_1				0x15
#घोषणा VADC_P_MUX7_1_1				0x16
#घोषणा VADC_P_MUX8_1_1				0x17
#घोषणा VADC_P_MUX9_1_1				0x18
#घोषणा VADC_P_MUX10_1_1			0x19
#घोषणा VADC_P_MUX11_1_1			0x1a
#घोषणा VADC_P_MUX12_1_1			0x1b
#घोषणा VADC_P_MUX13_1_1			0x1c
#घोषणा VADC_P_MUX14_1_1			0x1d
#घोषणा VADC_P_MUX15_1_1			0x1e
#घोषणा VADC_P_MUX16_1_1			0x1f

#घोषणा VADC_P_MUX1_1_3				0x20
#घोषणा VADC_P_MUX2_1_3				0x21
#घोषणा VADC_P_MUX3_1_3				0x22
#घोषणा VADC_P_MUX4_1_3				0x23
#घोषणा VADC_P_MUX5_1_3				0x24
#घोषणा VADC_P_MUX6_1_3				0x25
#घोषणा VADC_P_MUX7_1_3				0x26
#घोषणा VADC_P_MUX8_1_3				0x27
#घोषणा VADC_P_MUX9_1_3				0x28
#घोषणा VADC_P_MUX10_1_3			0x29
#घोषणा VADC_P_MUX11_1_3			0x2a
#घोषणा VADC_P_MUX12_1_3			0x2b
#घोषणा VADC_P_MUX13_1_3			0x2c
#घोषणा VADC_P_MUX14_1_3			0x2d
#घोषणा VADC_P_MUX15_1_3			0x2e
#घोषणा VADC_P_MUX16_1_3			0x2f

#घोषणा VADC_LR_MUX1_BAT_THERM			0x30
#घोषणा VADC_LR_MUX2_BAT_ID			0x31
#घोषणा VADC_LR_MUX3_XO_THERM			0x32
#घोषणा VADC_LR_MUX4_AMUX_THM1			0x33
#घोषणा VADC_LR_MUX5_AMUX_THM2			0x34
#घोषणा VADC_LR_MUX6_AMUX_THM3			0x35
#घोषणा VADC_LR_MUX7_HW_ID			0x36
#घोषणा VADC_LR_MUX8_AMUX_THM4			0x37
#घोषणा VADC_LR_MUX9_AMUX_THM5			0x38
#घोषणा VADC_LR_MUX10_USB_ID			0x39
#घोषणा VADC_AMUX_PU1				0x3a
#घोषणा VADC_AMUX_PU2				0x3b
#घोषणा VADC_LR_MUX3_BUF_XO_THERM		0x3c

#घोषणा VADC_LR_MUX1_PU1_BAT_THERM		0x70
#घोषणा VADC_LR_MUX2_PU1_BAT_ID			0x71
#घोषणा VADC_LR_MUX3_PU1_XO_THERM		0x72
#घोषणा VADC_LR_MUX4_PU1_AMUX_THM1		0x73
#घोषणा VADC_LR_MUX5_PU1_AMUX_THM2		0x74
#घोषणा VADC_LR_MUX6_PU1_AMUX_THM3		0x75
#घोषणा VADC_LR_MUX7_PU1_AMUX_HW_ID		0x76
#घोषणा VADC_LR_MUX8_PU1_AMUX_THM4		0x77
#घोषणा VADC_LR_MUX9_PU1_AMUX_THM5		0x78
#घोषणा VADC_LR_MUX10_PU1_AMUX_USB_ID		0x79
#घोषणा VADC_LR_MUX3_BUF_PU1_XO_THERM		0x7c

#घोषणा VADC_LR_MUX1_PU2_BAT_THERM		0xb0
#घोषणा VADC_LR_MUX2_PU2_BAT_ID			0xb1
#घोषणा VADC_LR_MUX3_PU2_XO_THERM		0xb2
#घोषणा VADC_LR_MUX4_PU2_AMUX_THM1		0xb3
#घोषणा VADC_LR_MUX5_PU2_AMUX_THM2		0xb4
#घोषणा VADC_LR_MUX6_PU2_AMUX_THM3		0xb5
#घोषणा VADC_LR_MUX7_PU2_AMUX_HW_ID		0xb6
#घोषणा VADC_LR_MUX8_PU2_AMUX_THM4		0xb7
#घोषणा VADC_LR_MUX9_PU2_AMUX_THM5		0xb8
#घोषणा VADC_LR_MUX10_PU2_AMUX_USB_ID		0xb9
#घोषणा VADC_LR_MUX3_BUF_PU2_XO_THERM		0xbc

#घोषणा VADC_LR_MUX1_PU1_PU2_BAT_THERM		0xf0
#घोषणा VADC_LR_MUX2_PU1_PU2_BAT_ID		0xf1
#घोषणा VADC_LR_MUX3_PU1_PU2_XO_THERM		0xf2
#घोषणा VADC_LR_MUX4_PU1_PU2_AMUX_THM1		0xf3
#घोषणा VADC_LR_MUX5_PU1_PU2_AMUX_THM2		0xf4
#घोषणा VADC_LR_MUX6_PU1_PU2_AMUX_THM3		0xf5
#घोषणा VADC_LR_MUX7_PU1_PU2_AMUX_HW_ID		0xf6
#घोषणा VADC_LR_MUX8_PU1_PU2_AMUX_THM4		0xf7
#घोषणा VADC_LR_MUX9_PU1_PU2_AMUX_THM5		0xf8
#घोषणा VADC_LR_MUX10_PU1_PU2_AMUX_USB_ID	0xf9
#घोषणा VADC_LR_MUX3_BUF_PU1_PU2_XO_THERM	0xfc

/* ADC channels क्रम SPMI PMIC5 */

#घोषणा ADC5_REF_GND				0x00
#घोषणा ADC5_1P25VREF				0x01
#घोषणा ADC5_VREF_VADC				0x02
#घोषणा ADC5_VREF_VADC5_DIV_3			0x82
#घोषणा ADC5_VPH_PWR				0x83
#घोषणा ADC5_VBAT_SNS				0x84
#घोषणा ADC5_VCOIN				0x85
#घोषणा ADC5_DIE_TEMP				0x06
#घोषणा ADC5_USB_IN_I				0x07
#घोषणा ADC5_USB_IN_V_16			0x08
#घोषणा ADC5_CHG_TEMP				0x09
#घोषणा ADC5_BAT_THERM				0x0a
#घोषणा ADC5_BAT_ID				0x0b
#घोषणा ADC5_XO_THERM				0x0c
#घोषणा ADC5_AMUX_THM1				0x0d
#घोषणा ADC5_AMUX_THM2				0x0e
#घोषणा ADC5_AMUX_THM3				0x0f
#घोषणा ADC5_AMUX_THM4				0x10
#घोषणा ADC5_AMUX_THM5				0x11
#घोषणा ADC5_GPIO1				0x12
#घोषणा ADC5_GPIO2				0x13
#घोषणा ADC5_GPIO3				0x14
#घोषणा ADC5_GPIO4				0x15
#घोषणा ADC5_GPIO5				0x16
#घोषणा ADC5_GPIO6				0x17
#घोषणा ADC5_GPIO7				0x18
#घोषणा ADC5_SBUx				0x99
#घोषणा ADC5_MID_CHG_DIV6			0x1e
#घोषणा ADC5_OFF				0xff

/* 30k pull-up1 */
#घोषणा ADC5_BAT_THERM_30K_PU			0x2a
#घोषणा ADC5_BAT_ID_30K_PU			0x2b
#घोषणा ADC5_XO_THERM_30K_PU			0x2c
#घोषणा ADC5_AMUX_THM1_30K_PU			0x2d
#घोषणा ADC5_AMUX_THM2_30K_PU			0x2e
#घोषणा ADC5_AMUX_THM3_30K_PU			0x2f
#घोषणा ADC5_AMUX_THM4_30K_PU			0x30
#घोषणा ADC5_AMUX_THM5_30K_PU			0x31
#घोषणा ADC5_GPIO1_30K_PU			0x32
#घोषणा ADC5_GPIO2_30K_PU			0x33
#घोषणा ADC5_GPIO3_30K_PU			0x34
#घोषणा ADC5_GPIO4_30K_PU			0x35
#घोषणा ADC5_GPIO5_30K_PU			0x36
#घोषणा ADC5_GPIO6_30K_PU			0x37
#घोषणा ADC5_GPIO7_30K_PU			0x38
#घोषणा ADC5_SBUx_30K_PU			0x39

/* 100k pull-up2 */
#घोषणा ADC5_BAT_THERM_100K_PU			0x4a
#घोषणा ADC5_BAT_ID_100K_PU			0x4b
#घोषणा ADC5_XO_THERM_100K_PU			0x4c
#घोषणा ADC5_AMUX_THM1_100K_PU			0x4d
#घोषणा ADC5_AMUX_THM2_100K_PU			0x4e
#घोषणा ADC5_AMUX_THM3_100K_PU			0x4f
#घोषणा ADC5_AMUX_THM4_100K_PU			0x50
#घोषणा ADC5_AMUX_THM5_100K_PU			0x51
#घोषणा ADC5_GPIO1_100K_PU			0x52
#घोषणा ADC5_GPIO2_100K_PU			0x53
#घोषणा ADC5_GPIO3_100K_PU			0x54
#घोषणा ADC5_GPIO4_100K_PU			0x55
#घोषणा ADC5_GPIO5_100K_PU			0x56
#घोषणा ADC5_GPIO6_100K_PU			0x57
#घोषणा ADC5_GPIO7_100K_PU			0x58
#घोषणा ADC5_SBUx_100K_PU			0x59

/* 400k pull-up3 */
#घोषणा ADC5_BAT_THERM_400K_PU			0x6a
#घोषणा ADC5_BAT_ID_400K_PU			0x6b
#घोषणा ADC5_XO_THERM_400K_PU			0x6c
#घोषणा ADC5_AMUX_THM1_400K_PU			0x6d
#घोषणा ADC5_AMUX_THM2_400K_PU			0x6e
#घोषणा ADC5_AMUX_THM3_400K_PU			0x6f
#घोषणा ADC5_AMUX_THM4_400K_PU			0x70
#घोषणा ADC5_AMUX_THM5_400K_PU			0x71
#घोषणा ADC5_GPIO1_400K_PU			0x72
#घोषणा ADC5_GPIO2_400K_PU			0x73
#घोषणा ADC5_GPIO3_400K_PU			0x74
#घोषणा ADC5_GPIO4_400K_PU			0x75
#घोषणा ADC5_GPIO5_400K_PU			0x76
#घोषणा ADC5_GPIO6_400K_PU			0x77
#घोषणा ADC5_GPIO7_400K_PU			0x78
#घोषणा ADC5_SBUx_400K_PU			0x79

/* 1/3 Divider */
#घोषणा ADC5_GPIO1_DIV3				0x92
#घोषणा ADC5_GPIO2_DIV3				0x93
#घोषणा ADC5_GPIO3_DIV3				0x94
#घोषणा ADC5_GPIO4_DIV3				0x95
#घोषणा ADC5_GPIO5_DIV3				0x96
#घोषणा ADC5_GPIO6_DIV3				0x97
#घोषणा ADC5_GPIO7_DIV3				0x98
#घोषणा ADC5_SBUx_DIV3				0x99

/* Current and combined current/voltage channels */
#घोषणा ADC5_INT_EXT_ISENSE			0xa1
#घोषणा ADC5_PARALLEL_ISENSE			0xa5
#घोषणा ADC5_CUR_REPLICA_VDS			0xa7
#घोषणा ADC5_CUR_SENS_BATFET_VDS_OFFSET		0xa9
#घोषणा ADC5_CUR_SENS_REPLICA_VDS_OFFSET	0xab
#घोषणा ADC5_EXT_SENS_OFFSET			0xad

#घोषणा ADC5_INT_EXT_ISENSE_VBAT_VDATA		0xb0
#घोषणा ADC5_INT_EXT_ISENSE_VBAT_IDATA		0xb1
#घोषणा ADC5_EXT_ISENSE_VBAT_VDATA		0xb2
#घोषणा ADC5_EXT_ISENSE_VBAT_IDATA		0xb3
#घोषणा ADC5_PARALLEL_ISENSE_VBAT_VDATA		0xb4
#घोषणा ADC5_PARALLEL_ISENSE_VBAT_IDATA		0xb5

#घोषणा ADC5_MAX_CHANNEL			0xc0

/* ADC channels क्रम ADC क्रम PMIC7 */

#घोषणा ADC7_REF_GND				0x00
#घोषणा ADC7_1P25VREF				0x01
#घोषणा ADC7_VREF_VADC				0x02
#घोषणा ADC7_DIE_TEMP				0x03

#घोषणा ADC7_AMUX_THM1				0x04
#घोषणा ADC7_AMUX_THM2				0x05
#घोषणा ADC7_AMUX_THM3				0x06
#घोषणा ADC7_AMUX_THM4				0x07
#घोषणा ADC7_AMUX_THM5				0x08
#घोषणा ADC7_AMUX_THM6				0x09
#घोषणा ADC7_GPIO1				0x0a
#घोषणा ADC7_GPIO2				0x0b
#घोषणा ADC7_GPIO3				0x0c
#घोषणा ADC7_GPIO4				0x0d

#घोषणा ADC7_CHG_TEMP				0x10
#घोषणा ADC7_USB_IN_V_16			0x11
#घोषणा ADC7_VDC_16				0x12
#घोषणा ADC7_CC1_ID				0x13
#घोषणा ADC7_VREF_BAT_THERM			0x15
#घोषणा ADC7_IIN_FB				0x17

/* 30k pull-up1 */
#घोषणा ADC7_AMUX_THM1_30K_PU			0x24
#घोषणा ADC7_AMUX_THM2_30K_PU			0x25
#घोषणा ADC7_AMUX_THM3_30K_PU			0x26
#घोषणा ADC7_AMUX_THM4_30K_PU			0x27
#घोषणा ADC7_AMUX_THM5_30K_PU			0x28
#घोषणा ADC7_AMUX_THM6_30K_PU			0x29
#घोषणा ADC7_GPIO1_30K_PU			0x2a
#घोषणा ADC7_GPIO2_30K_PU			0x2b
#घोषणा ADC7_GPIO3_30K_PU			0x2c
#घोषणा ADC7_GPIO4_30K_PU			0x2d
#घोषणा ADC7_CC1_ID_30K_PU			0x33

/* 100k pull-up2 */
#घोषणा ADC7_AMUX_THM1_100K_PU			0x44
#घोषणा ADC7_AMUX_THM2_100K_PU			0x45
#घोषणा ADC7_AMUX_THM3_100K_PU			0x46
#घोषणा ADC7_AMUX_THM4_100K_PU			0x47
#घोषणा ADC7_AMUX_THM5_100K_PU			0x48
#घोषणा ADC7_AMUX_THM6_100K_PU			0x49
#घोषणा ADC7_GPIO1_100K_PU			0x4a
#घोषणा ADC7_GPIO2_100K_PU			0x4b
#घोषणा ADC7_GPIO3_100K_PU			0x4c
#घोषणा ADC7_GPIO4_100K_PU			0x4d
#घोषणा ADC7_CC1_ID_100K_PU			0x53

/* 400k pull-up3 */
#घोषणा ADC7_AMUX_THM1_400K_PU			0x64
#घोषणा ADC7_AMUX_THM2_400K_PU			0x65
#घोषणा ADC7_AMUX_THM3_400K_PU			0x66
#घोषणा ADC7_AMUX_THM4_400K_PU			0x67
#घोषणा ADC7_AMUX_THM5_400K_PU			0x68
#घोषणा ADC7_AMUX_THM6_400K_PU			0x69
#घोषणा ADC7_GPIO1_400K_PU			0x6a
#घोषणा ADC7_GPIO2_400K_PU			0x6b
#घोषणा ADC7_GPIO3_400K_PU			0x6c
#घोषणा ADC7_GPIO4_400K_PU			0x6d
#घोषणा ADC7_CC1_ID_400K_PU			0x73

/* 1/3 Divider */
#घोषणा ADC7_GPIO1_DIV3				0x8a
#घोषणा ADC7_GPIO2_DIV3				0x8b
#घोषणा ADC7_GPIO3_DIV3				0x8c
#घोषणा ADC7_GPIO4_DIV3				0x8d

#घोषणा ADC7_VPH_PWR				0x8e
#घोषणा ADC7_VBAT_SNS				0x8f

#घोषणा ADC7_SBUx				0x94
#घोषणा ADC7_VBAT_2S_MID			0x96

#पूर्ण_अगर /* _DT_BINDINGS_QCOM_SPMI_VADC_H */
