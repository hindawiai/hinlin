<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* linux/include/linux/scx200.h

   Copyright (c) 2001,2002 Christer Weinigel <wingel@nano-प्रणाली.com>

   Defines क्रम the National Semiconductor SCx200 Processors
*/

/* Interesting stuff क्रम the National Semiconductor SCx200 CPU */

बाह्य अचिन्हित scx200_cb_base;

#घोषणा scx200_cb_present() (scx200_cb_base!=0)

/* F0 PCI Header/Bridge Configuration Registers */
#घोषणा SCx200_DOCCS_BASE 0x78	/* DOCCS Base Address Register */
#घोषणा SCx200_DOCCS_CTRL 0x7c	/* DOCCS Control Register */

/* GPIO Register Block */
#घोषणा SCx200_GPIO_SIZE 0x2c	/* Size of GPIO रेजिस्टर block */

/* General Configuration Block */
#घोषणा SCx200_CB_BASE_FIXED 0x9000	/* Base fixed at 0x9000 according to errata? */

/* Watchकरोg Timer */
#घोषणा SCx200_WDT_OFFSET 0x00	/* offset within configuration block */
#घोषणा SCx200_WDT_SIZE 0x05	/* size */

#घोषणा SCx200_WDT_WDTO 0x00	/* Time-Out Register */
#घोषणा SCx200_WDT_WDCNFG 0x02	/* Configuration Register */
#घोषणा SCx200_WDT_WDSTS 0x04	/* Status Register */
#घोषणा SCx200_WDT_WDSTS_WDOVF (1<<0) /* Overflow bit */

/* High Resolution Timer */
#घोषणा SCx200_TIMER_OFFSET 0x08
#घोषणा SCx200_TIMER_SIZE 0x06

/* Clock Generators */
#घोषणा SCx200_CLOCKGEN_OFFSET 0x10
#घोषणा SCx200_CLOCKGEN_SIZE 0x10

/* Pin Multiplexing and Miscellaneous Configuration Registers */
#घोषणा SCx200_MISC_OFFSET 0x30
#घोषणा SCx200_MISC_SIZE 0x10

#घोषणा SCx200_PMR 0x30		/* Pin Multiplexing Register */
#घोषणा SCx200_MCR 0x34		/* Miscellaneous Configuration Register */
#घोषणा SCx200_INTSEL 0x38	/* Interrupt Selection Register */
#घोषणा SCx200_IID 0x3c		/* IA On a Chip Identअगरication Number Reg */
#घोषणा SCx200_REV 0x3d		/* Revision Register */
#घोषणा SCx200_CBA 0x3e		/* Configuration Base Address Register */
#घोषणा SCx200_CBA_SCRATCH 0x64	/* Configuration Base Address Scratchpad */
