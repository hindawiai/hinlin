<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2020 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DT_BINDINGS_QCOM_SPMI_VADC_PMR735A_H
#घोषणा _DT_BINDINGS_QCOM_SPMI_VADC_PMR735A_H

#अगर_अघोषित PMR735A_SID
#घोषणा PMR735A_SID					4
#पूर्ण_अगर

/* ADC channels क्रम PMR735A_ADC क्रम PMIC7 */
#घोषणा PMR735A_ADC7_REF_GND			(PMR735A_SID << 8 | 0x0)
#घोषणा PMR735A_ADC7_1P25VREF			(PMR735A_SID << 8 | 0x01)
#घोषणा PMR735A_ADC7_VREF_VADC			(PMR735A_SID << 8 | 0x02)
#घोषणा PMR735A_ADC7_DIE_TEMP			(PMR735A_SID << 8 | 0x03)

#घोषणा PMR735A_ADC7_GPIO1			(PMR735A_SID << 8 | 0x0a)
#घोषणा PMR735A_ADC7_GPIO2			(PMR735A_SID << 8 | 0x0b)
#घोषणा PMR735A_ADC7_GPIO3			(PMR735A_SID << 8 | 0x0c)

/* 100k pull-up2 */
#घोषणा PMR735A_ADC7_GPIO1_100K_PU		(PMR735A_SID << 8 | 0x4a)
#घोषणा PMR735A_ADC7_GPIO2_100K_PU		(PMR735A_SID << 8 | 0x4b)
#घोषणा PMR735A_ADC7_GPIO3_100K_PU		(PMR735A_SID << 8 | 0x4c)

#पूर्ण_अगर /* _DT_BINDINGS_QCOM_SPMI_VADC_PMR735A_H */
