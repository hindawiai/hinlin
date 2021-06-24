<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_IODATA_LANDISK_H
#घोषणा __ASM_SH_IODATA_LANDISK_H

/*
 * arch/sh/include/mach-landisk/mach/iodata_landisk.h
 *
 * Copyright (C) 2000  Atom Create Engineering Co., Ltd.
 *
 * IO-DATA LANDISK support
 */
#समावेश <linux/sh_पूर्णांकc.h>

/* Box specअगरic addresses.  */

#घोषणा PA_USB		0xa4000000	/* USB Controller M66590 */

#घोषणा PA_ATARST	0xb0000000	/* ATA/FATA Access Control Register */
#घोषणा PA_LED		0xb0000001	/* LED Control Register */
#घोषणा PA_STATUS	0xb0000002	/* Switch Status Register */
#घोषणा PA_SHUTDOWN	0xb0000003	/* Shutकरोwn Control Register */
#घोषणा PA_PCIPME	0xb0000004	/* PCI PME Status Register */
#घोषणा PA_IMASK	0xb0000005	/* Interrupt Mask Register */
/* 2003.10.31 I-O DATA NSD NWG	add.	क्रम shutकरोwn port clear */
#घोषणा PA_PWRINT_CLR	0xb0000006	/* Shutकरोwn Interrupt clear Register */

#घोषणा PA_PIDE_OFFSET	0x40		/* CF IDE Offset */
#घोषणा PA_SIDE_OFFSET	0x40		/* HDD IDE Offset */

#घोषणा IRQ_PCIINTA	evt2irq(0x2a0)	/* PCI INTA IRQ */
#घोषणा IRQ_PCIINTB	evt2irq(0x2c0)	/* PCI INTB IRQ */
#घोषणा IRQ_PCIINTC	evt2irq(0x2e0)	/* PCI INTC IRQ */
#घोषणा IRQ_PCIINTD	evt2irq(0x300)	/* PCI INTD IRQ */
#घोषणा IRQ_ATA		evt2irq(0x320)	/* ATA IRQ */
#घोषणा IRQ_FATA	evt2irq(0x340)	/* FATA IRQ */
#घोषणा IRQ_POWER	evt2irq(0x360)	/* Power Switch IRQ */
#घोषणा IRQ_BUTTON	evt2irq(0x380)	/* USL-5P Button IRQ */
#घोषणा IRQ_FAULT	evt2irq(0x3a0)	/* USL-5P Fault  IRQ */

व्योम init_landisk_IRQ(व्योम);

#घोषणा __IO_PREFIX landisk
#समावेश <यंत्र/io_generic.h>

#पूर्ण_अगर  /* __ASM_SH_IODATA_LANDISK_H */

