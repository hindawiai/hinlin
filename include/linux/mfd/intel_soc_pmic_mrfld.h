<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Header file क्रम Intel Merrअगरield Basin Cove PMIC
 *
 * Copyright (C) 2019 Intel Corporation. All rights reserved.
 */

#अगर_अघोषित __INTEL_SOC_PMIC_MRFLD_H__
#घोषणा __INTEL_SOC_PMIC_MRFLD_H__

#समावेश <linux/bits.h>

#घोषणा BCOVE_ID		0x00

#घोषणा BCOVE_ID_MINREV0	GENMASK(2, 0)
#घोषणा BCOVE_ID_MAJREV0	GENMASK(5, 3)
#घोषणा BCOVE_ID_VENDID0	GENMASK(7, 6)

#घोषणा BCOVE_MINOR(x)		(अचिन्हित पूर्णांक)(((x) & BCOVE_ID_MINREV0) >> 0)
#घोषणा BCOVE_MAJOR(x)		(अचिन्हित पूर्णांक)(((x) & BCOVE_ID_MAJREV0) >> 3)
#घोषणा BCOVE_VENDOR(x)		(अचिन्हित पूर्णांक)(((x) & BCOVE_ID_VENDID0) >> 6)

#घोषणा BCOVE_IRQLVL1		0x01

#घोषणा BCOVE_PBIRQ		0x02
#घोषणा BCOVE_TMUIRQ		0x03
#घोषणा BCOVE_THRMIRQ		0x04
#घोषणा BCOVE_BCUIRQ		0x05
#घोषणा BCOVE_ADCIRQ		0x06
#घोषणा BCOVE_CHGRIRQ0		0x07
#घोषणा BCOVE_CHGRIRQ1		0x08
#घोषणा BCOVE_GPIOIRQ		0x09
#घोषणा BCOVE_CRITIRQ		0x0B

#घोषणा BCOVE_MIRQLVL1		0x0C

#घोषणा BCOVE_MPBIRQ		0x0D
#घोषणा BCOVE_MTMUIRQ		0x0E
#घोषणा BCOVE_MTHRMIRQ		0x0F
#घोषणा BCOVE_MBCUIRQ		0x10
#घोषणा BCOVE_MADCIRQ		0x11
#घोषणा BCOVE_MCHGRIRQ0		0x12
#घोषणा BCOVE_MCHGRIRQ1		0x13
#घोषणा BCOVE_MGPIOIRQ		0x14
#घोषणा BCOVE_MCRITIRQ		0x16

#घोषणा BCOVE_SCHGRIRQ0		0x4E
#घोषणा BCOVE_SCHGRIRQ1		0x4F

/* Level 1 IRQs */
#घोषणा BCOVE_LVL1_PWRBTN	BIT(0)	/* घातer button */
#घोषणा BCOVE_LVL1_TMU		BIT(1)	/* समय management unit */
#घोषणा BCOVE_LVL1_THRM		BIT(2)	/* thermal */
#घोषणा BCOVE_LVL1_BCU		BIT(3)	/* burst control unit */
#घोषणा BCOVE_LVL1_ADC		BIT(4)	/* ADC */
#घोषणा BCOVE_LVL1_CHGR		BIT(5)	/* अक्षरger */
#घोषणा BCOVE_LVL1_GPIO		BIT(6)	/* GPIO */
#घोषणा BCOVE_LVL1_CRIT		BIT(7)	/* critical event */

/* Level 2 IRQs: घातer button */
#घोषणा BCOVE_PBIRQ_PBTN	BIT(0)
#घोषणा BCOVE_PBIRQ_UBTN	BIT(1)

/* Level 2 IRQs: ADC */
#घोषणा BCOVE_ADCIRQ_BATTEMP	BIT(2)
#घोषणा BCOVE_ADCIRQ_SYSTEMP	BIT(3)
#घोषणा BCOVE_ADCIRQ_BATTID	BIT(4)
#घोषणा BCOVE_ADCIRQ_VIBATT	BIT(5)
#घोषणा BCOVE_ADCIRQ_CCTICK	BIT(7)

/* Level 2 IRQs: अक्षरger */
#घोषणा BCOVE_CHGRIRQ_BAT0ALRT	BIT(4)
#घोषणा BCOVE_CHGRIRQ_BAT1ALRT	BIT(5)
#घोषणा BCOVE_CHGRIRQ_BATCRIT	BIT(6)

#घोषणा BCOVE_CHGRIRQ_VBUSDET	BIT(0)
#घोषणा BCOVE_CHGRIRQ_DCDET	BIT(1)
#घोषणा BCOVE_CHGRIRQ_BATTDET	BIT(2)
#घोषणा BCOVE_CHGRIRQ_USBIDDET	BIT(3)

#पूर्ण_अगर	/* __INTEL_SOC_PMIC_MRFLD_H__ */
