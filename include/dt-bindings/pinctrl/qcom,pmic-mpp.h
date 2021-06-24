<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This header provides स्थिरants क्रम the Qualcomm PMIC's
 * Multi-Purpose Pin binding.
 */

#अगर_अघोषित _DT_BINDINGS_PINCTRL_QCOM_PMIC_MPP_H
#घोषणा _DT_BINDINGS_PINCTRL_QCOM_PMIC_MPP_H

/* घातer-source */

/* Digital Input/Output: level [PM8058] */
#घोषणा PM8058_MPP_VPH			0
#घोषणा PM8058_MPP_S3			1
#घोषणा PM8058_MPP_L2			2
#घोषणा PM8058_MPP_L3			3

/* Digital Input/Output: level [PM8901] */
#घोषणा PM8901_MPP_MSMIO		0
#घोषणा PM8901_MPP_DIG			1
#घोषणा PM8901_MPP_L5			2
#घोषणा PM8901_MPP_S4			3
#घोषणा PM8901_MPP_VPH			4

/* Digital Input/Output: level [PM8921] */
#घोषणा PM8921_MPP_S4			1
#घोषणा PM8921_MPP_L15			3
#घोषणा PM8921_MPP_L17			4
#घोषणा PM8921_MPP_VPH			7

/* Digital Input/Output: level [PM8821] */
#घोषणा PM8821_MPP_1P8			0
#घोषणा PM8821_MPP_VPH			7

/* Digital Input/Output: level [PM8018] */
#घोषणा PM8018_MPP_L4			0
#घोषणा PM8018_MPP_L14			1
#घोषणा PM8018_MPP_S3			2
#घोषणा PM8018_MPP_L6			3
#घोषणा PM8018_MPP_L2			4
#घोषणा PM8018_MPP_L5			5
#घोषणा PM8018_MPP_VPH			7

/* Digital Input/Output: level [PM8038] */
#घोषणा PM8038_MPP_L20			0
#घोषणा PM8038_MPP_L11			1
#घोषणा PM8038_MPP_L5			2
#घोषणा PM8038_MPP_L15			3
#घोषणा PM8038_MPP_L17			4
#घोषणा PM8038_MPP_VPH			7

#घोषणा PM8841_MPP_VPH			0
#घोषणा PM8841_MPP_S3			2

#घोषणा PM8916_MPP_VPH			0
#घोषणा PM8916_MPP_L2			2
#घोषणा PM8916_MPP_L5			3

#घोषणा PM8941_MPP_VPH			0
#घोषणा PM8941_MPP_L1			1
#घोषणा PM8941_MPP_S3			2
#घोषणा PM8941_MPP_L6			3

#घोषणा PMA8084_MPP_VPH			0
#घोषणा PMA8084_MPP_L1			1
#घोषणा PMA8084_MPP_S4			2
#घोषणा PMA8084_MPP_L6			3

#घोषणा PM8994_MPP_VPH			0
/* Only supported क्रम MPP_05-MPP_08 */
#घोषणा PM8994_MPP_L19			1
#घोषणा PM8994_MPP_S4			2
#घोषणा PM8994_MPP_L12			3

/*
 * Analog Input - Set the source क्रम analog input.
 * To be used with "qcom,amux-route" property
 */
#घोषणा PMIC_MPP_AMUX_ROUTE_CH5		0
#घोषणा PMIC_MPP_AMUX_ROUTE_CH6		1
#घोषणा PMIC_MPP_AMUX_ROUTE_CH7		2
#घोषणा PMIC_MPP_AMUX_ROUTE_CH8		3
#घोषणा PMIC_MPP_AMUX_ROUTE_ABUS1	4
#घोषणा PMIC_MPP_AMUX_ROUTE_ABUS2	5
#घोषणा PMIC_MPP_AMUX_ROUTE_ABUS3	6
#घोषणा PMIC_MPP_AMUX_ROUTE_ABUS4	7

/* Analog Output: level */
#घोषणा PMIC_MPP_AOUT_LVL_1V25		0
#घोषणा PMIC_MPP_AOUT_LVL_1V25_2	1
#घोषणा PMIC_MPP_AOUT_LVL_0V625		2
#घोषणा PMIC_MPP_AOUT_LVL_0V3125	3
#घोषणा PMIC_MPP_AOUT_LVL_MPP		4
#घोषणा PMIC_MPP_AOUT_LVL_ABUS1		5
#घोषणा PMIC_MPP_AOUT_LVL_ABUS2		6
#घोषणा PMIC_MPP_AOUT_LVL_ABUS3		7

/* To be used with "function" */
#घोषणा PMIC_MPP_FUNC_NORMAL		"normal"
#घोषणा PMIC_MPP_FUNC_PAIRED		"paired"
#घोषणा PMIC_MPP_FUNC_DTEST1		"dtest1"
#घोषणा PMIC_MPP_FUNC_DTEST2		"dtest2"
#घोषणा PMIC_MPP_FUNC_DTEST3		"dtest3"
#घोषणा PMIC_MPP_FUNC_DTEST4		"dtest4"

#पूर्ण_अगर
