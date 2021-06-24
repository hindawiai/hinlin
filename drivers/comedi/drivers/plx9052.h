<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Definitions क्रम the PLX-9052 PCI पूर्णांकerface chip
 *
 * Copyright (C) 2002 MEV Ltd. <https://www.mev.co.uk/>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

#अगर_अघोषित _PLX9052_H_
#घोषणा _PLX9052_H_

/*
 * INTCSR - Interrupt Control/Status रेजिस्टर
 */
#घोषणा PLX9052_INTCSR			0x4c
#घोषणा PLX9052_INTCSR_LI1ENAB		BIT(0)	/* LI1 enabled */
#घोषणा PLX9052_INTCSR_LI1POL		BIT(1)	/* LI1 active high */
#घोषणा PLX9052_INTCSR_LI1STAT		BIT(2)	/* LI1 active */
#घोषणा PLX9052_INTCSR_LI2ENAB		BIT(3)	/* LI2 enabled */
#घोषणा PLX9052_INTCSR_LI2POL		BIT(4)	/* LI2 active high */
#घोषणा PLX9052_INTCSR_LI2STAT		BIT(5)	/* LI2 active */
#घोषणा PLX9052_INTCSR_PCIENAB		BIT(6)	/* PCIINT enabled */
#घोषणा PLX9052_INTCSR_SOFTINT		BIT(7)	/* generate soft पूर्णांक */
#घोषणा PLX9052_INTCSR_LI1SEL		BIT(8)	/* LI1 edge */
#घोषणा PLX9052_INTCSR_LI2SEL		BIT(9)	/* LI2 edge */
#घोषणा PLX9052_INTCSR_LI1CLRINT	BIT(10)	/* LI1 clear पूर्णांक */
#घोषणा PLX9052_INTCSR_LI2CLRINT	BIT(11)	/* LI2 clear पूर्णांक */
#घोषणा PLX9052_INTCSR_ISAMODE		BIT(12)	/* ISA पूर्णांकerface mode */

/*
 * CNTRL - User I/O, Direct Slave Response, Serial EEPROM, and
 * Initialization Control रेजिस्टर
 */
#घोषणा PLX9052_CNTRL			0x50
#घोषणा PLX9052_CNTRL_WAITO		BIT(0)	/* UIO0 or WAITO# select */
#घोषणा PLX9052_CNTRL_UIO0_सूची		BIT(1)	/* UIO0 direction */
#घोषणा PLX9052_CNTRL_UIO0_DATA		BIT(2)	/* UIO0 data */
#घोषणा PLX9052_CNTRL_LLOCKO		BIT(3)	/* UIO1 or LLOCKo# select */
#घोषणा PLX9052_CNTRL_UIO1_सूची		BIT(4)	/* UIO1 direction */
#घोषणा PLX9052_CNTRL_UIO1_DATA		BIT(5)	/* UIO1 data */
#घोषणा PLX9052_CNTRL_CS2		BIT(6)	/* UIO2 or CS2# select */
#घोषणा PLX9052_CNTRL_UIO2_सूची		BIT(7)	/* UIO2 direction */
#घोषणा PLX9052_CNTRL_UIO2_DATA		BIT(8)	/* UIO2 data */
#घोषणा PLX9052_CNTRL_CS3		BIT(9)	/* UIO3 or CS3# select */
#घोषणा PLX9052_CNTRL_UIO3_सूची		BIT(10)	/* UIO3 direction */
#घोषणा PLX9052_CNTRL_UIO3_DATA		BIT(11)	/* UIO3 data */
#घोषणा PLX9052_CNTRL_PCIBAR(x)		(((x) & 0x3) << 12)
#घोषणा PLX9052_CNTRL_PCIBAR01		PLX9052_CNTRL_PCIBAR(0)	/* mem and IO */
#घोषणा PLX9052_CNTRL_PCIBAR0		PLX9052_CNTRL_PCIBAR(1)	/* mem only */
#घोषणा PLX9052_CNTRL_PCIBAR1		PLX9052_CNTRL_PCIBAR(2)	/* IO only */
#घोषणा PLX9052_CNTRL_PCI2_1_FEATURES	BIT(14)	/* PCI v2.1 features enabled */
#घोषणा PLX9052_CNTRL_PCI_R_W_FLUSH	BIT(15)	/* पढ़ो w/ग_लिखो flush mode */
#घोषणा PLX9052_CNTRL_PCI_R_NO_FLUSH	BIT(16)	/* पढ़ो no flush mode */
#घोषणा PLX9052_CNTRL_PCI_R_NO_WRITE	BIT(17)	/* पढ़ो no ग_लिखो mode */
#घोषणा PLX9052_CNTRL_PCI_W_RELEASE	BIT(18)	/* ग_लिखो release bus mode */
#घोषणा PLX9052_CNTRL_RETRY_CLKS(x)	(((x) & 0xf) << 19) /* retry clks */
#घोषणा PLX9052_CNTRL_LOCK_ENAB		BIT(23)	/* slave LOCK# enable */
#घोषणा PLX9052_CNTRL_EEPROM_MASK	(0x1f << 24) /* EEPROM bits */
#घोषणा PLX9052_CNTRL_EEPROM_CLK	BIT(24)	/* EEPROM घड़ी */
#घोषणा PLX9052_CNTRL_EEPROM_CS		BIT(25)	/* EEPROM chip select */
#घोषणा PLX9052_CNTRL_EEPROM_DOUT	BIT(26)	/* EEPROM ग_लिखो bit */
#घोषणा PLX9052_CNTRL_EEPROM_DIN	BIT(27)	/* EEPROM पढ़ो bit */
#घोषणा PLX9052_CNTRL_EEPROM_PRESENT	BIT(28)	/* EEPROM present */
#घोषणा PLX9052_CNTRL_RELOAD_CFG	BIT(29)	/* reload configuration */
#घोषणा PLX9052_CNTRL_PCI_RESET		BIT(30)	/* PCI adapter reset */
#घोषणा PLX9052_CNTRL_MASK_REV		BIT(31)	/* mask revision */

#पूर्ण_अगर /* _PLX9052_H_ */
