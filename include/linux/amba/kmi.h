<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  linux/include/यंत्र-arm/hardware/amba_kmi.h
 *
 *  Internal header file क्रम AMBA KMI ports
 *
 *  Copyright (C) 2000 Deep Blue Solutions Ltd.
 *
 * ---------------------------------------------------------------------------
 *  From ARM PrimeCell(पंचांग) PS2 Keyboard/Mouse Interface (PL050) Technical
 *  Reference Manual - ARM DDI 0143B - see http://www.arm.com/
 * ---------------------------------------------------------------------------
 */
#अगर_अघोषित ASM_ARM_HARDWARE_AMBA_KMI_H
#घोषणा ASM_ARM_HARDWARE_AMBA_KMI_H

/*
 * KMI control रेजिस्टर:
 *  KMICR_TYPE       0 = PS2/AT mode, 1 = No line control bit mode
 *  KMICR_RXINTREN   1 = enable RX पूर्णांकerrupts
 *  KMICR_TXINTREN   1 = enable TX पूर्णांकerrupts
 *  KMICR_EN         1 = enable KMI
 *  KMICR_FD         1 = क्रमce KMI data low
 *  KMICR_FC         1 = क्रमce KMI घड़ी low
 */
#घोषणा KMICR		(KMI_BASE + 0x00)
#घोषणा KMICR_TYPE		(1 << 5)
#घोषणा KMICR_RXINTREN		(1 << 4)
#घोषणा KMICR_TXINTREN		(1 << 3)
#घोषणा KMICR_EN		(1 << 2)
#घोषणा KMICR_FD		(1 << 1)
#घोषणा KMICR_FC		(1 << 0)

/*
 * KMI status रेजिस्टर:
 *  KMISTAT_TXEMPTY  1 = transmitter रेजिस्टर empty
 *  KMISTAT_TXBUSY   1 = currently sending data
 *  KMISTAT_RXFULL   1 = receiver रेजिस्टर पढ़ोy to be पढ़ो
 *  KMISTAT_RXBUSY   1 = currently receiving data
 *  KMISTAT_RXPARITY parity of last databyte received
 *  KMISTAT_IC       current level of KMI घड़ी input
 *  KMISTAT_ID       current level of KMI data input
 */
#घोषणा KMISTAT		(KMI_BASE + 0x04)
#घोषणा KMISTAT_TXEMPTY		(1 << 6)
#घोषणा KMISTAT_TXBUSY		(1 << 5)
#घोषणा KMISTAT_RXFULL		(1 << 4)
#घोषणा KMISTAT_RXBUSY		(1 << 3)
#घोषणा KMISTAT_RXPARITY	(1 << 2)
#घोषणा KMISTAT_IC		(1 << 1)
#घोषणा KMISTAT_ID		(1 << 0)

/*
 * KMI data रेजिस्टर
 */
#घोषणा KMIDATA		(KMI_BASE + 0x08)

/*
 * KMI घड़ी भागisor: to generate 8MHz पूर्णांकernal घड़ी
 *  भाग = (ref / 8MHz) - 1; 0 <= भाग <= 15
 */
#घोषणा KMICLKDIV	(KMI_BASE + 0x0c)

/*
 * KMI पूर्णांकerrupt रेजिस्टर:
 *  KMIIR_TXINTR     1 = transmit पूर्णांकerrupt निश्चितed
 *  KMIIR_RXINTR     1 = receive पूर्णांकerrupt निश्चितed
 */
#घोषणा KMIIR		(KMI_BASE + 0x10)
#घोषणा KMIIR_TXINTR		(1 << 1)
#घोषणा KMIIR_RXINTR		(1 << 0)

/*
 * The size of the KMI primecell
 */
#घोषणा KMI_SIZE	(0x100)

#पूर्ण_अगर
