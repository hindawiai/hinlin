<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2005 Ivan Kokshaysky
 * Copyright (C) SAN People
 *
 * Parallel I/O Controller (PIO) - System peripherals रेजिस्टरs.
 */

#अगर_अघोषित __PINCTRL_AT91_H
#घोषणा __PINCTRL_AT91_H

#घोषणा PIO_PER		0x00	/* Enable Register */
#घोषणा PIO_PDR		0x04	/* Disable Register */
#घोषणा PIO_PSR		0x08	/* Status Register */
#घोषणा PIO_OER		0x10	/* Output Enable Register */
#घोषणा PIO_ODR		0x14	/* Output Disable Register */
#घोषणा PIO_OSR		0x18	/* Output Status Register */
#घोषणा PIO_IFER	0x20	/* Glitch Input Filter Enable */
#घोषणा PIO_IFDR	0x24	/* Glitch Input Filter Disable */
#घोषणा PIO_IFSR	0x28	/* Glitch Input Filter Status */
#घोषणा PIO_SODR	0x30	/* Set Output Data Register */
#घोषणा PIO_CODR	0x34	/* Clear Output Data Register */
#घोषणा PIO_ODSR	0x38	/* Output Data Status Register */
#घोषणा PIO_PDSR	0x3c	/* Pin Data Status Register */
#घोषणा PIO_IER		0x40	/* Interrupt Enable Register */
#घोषणा PIO_IDR		0x44	/* Interrupt Disable Register */
#घोषणा PIO_IMR		0x48	/* Interrupt Mask Register */
#घोषणा PIO_ISR		0x4c	/* Interrupt Status Register */
#घोषणा PIO_MDER	0x50	/* Multi-driver Enable Register */
#घोषणा PIO_MDDR	0x54	/* Multi-driver Disable Register */
#घोषणा PIO_MDSR	0x58	/* Multi-driver Status Register */
#घोषणा PIO_PUDR	0x60	/* Pull-up Disable Register */
#घोषणा PIO_PUER	0x64	/* Pull-up Enable Register */
#घोषणा PIO_PUSR	0x68	/* Pull-up Status Register */
#घोषणा PIO_ASR		0x70	/* Peripheral A Select Register */
#घोषणा PIO_ABCDSR1	0x70	/* Peripheral ABCD Select Register 1 [some sam9 only] */
#घोषणा PIO_BSR		0x74	/* Peripheral B Select Register */
#घोषणा PIO_ABCDSR2	0x74	/* Peripheral ABCD Select Register 2 [some sam9 only] */
#घोषणा PIO_ABSR	0x78	/* AB Status Register */
#घोषणा PIO_IFSCDR	0x80	/* Input Filter Slow Clock Disable Register */
#घोषणा PIO_IFSCER	0x84	/* Input Filter Slow Clock Enable Register */
#घोषणा PIO_IFSCSR	0x88	/* Input Filter Slow Clock Status Register */
#घोषणा PIO_SCDR	0x8c	/* Slow Clock Divider Debouncing Register */
#घोषणा		PIO_SCDR_DIV	(0x3fff <<  0)		/* Slow Clock Divider Mask */
#घोषणा PIO_PPDDR	0x90	/* Pad Pull-करोwn Disable Register */
#घोषणा PIO_PPDER	0x94	/* Pad Pull-करोwn Enable Register */
#घोषणा PIO_PPDSR	0x98	/* Pad Pull-करोwn Status Register */
#घोषणा PIO_OWER	0xa0	/* Output Write Enable Register */
#घोषणा PIO_OWDR	0xa4	/* Output Write Disable Register */
#घोषणा PIO_OWSR	0xa8	/* Output Write Status Register */
#घोषणा PIO_AIMER	0xb0	/* Additional Interrupt Modes Enable Register */
#घोषणा PIO_AIMDR	0xb4	/* Additional Interrupt Modes Disable Register */
#घोषणा PIO_AIMMR	0xb8	/* Additional Interrupt Modes Mask Register */
#घोषणा PIO_ESR		0xc0	/* Edge Select Register */
#घोषणा PIO_LSR		0xc4	/* Level Select Register */
#घोषणा PIO_ELSR	0xc8	/* Edge/Level Status Register */
#घोषणा PIO_FELLSR	0xd0	/* Falling Edge/Low Level Select Register */
#घोषणा PIO_REHLSR	0xd4	/* Rising Edge/ High Level Select Register */
#घोषणा PIO_FRLHSR	0xd8	/* Fall/Rise - Low/High Status Register */
#घोषणा PIO_SCHMITT	0x100	/* Schmitt Trigger Register */

#घोषणा SAMA5D3_PIO_DRIVER1		0x118  /*PIO Driver 1 रेजिस्टर offset*/
#घोषणा SAMA5D3_PIO_DRIVER2		0x11C  /*PIO Driver 2 रेजिस्टर offset*/

#घोषणा AT91SAM9X5_PIO_DRIVER1	0x114  /*PIO Driver 1 रेजिस्टर offset*/
#घोषणा AT91SAM9X5_PIO_DRIVER2	0x118  /*PIO Driver 2 रेजिस्टर offset*/

#घोषणा SAM9X60_PIO_SLEWR	0x110	/* PIO Slew Rate Control Register */
#घोषणा SAM9X60_PIO_DRIVER1	0x118	/* PIO Driver 1 रेजिस्टर offset */

#पूर्ण_अगर
