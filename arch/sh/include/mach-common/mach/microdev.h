<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * linux/include/यंत्र-sh/microdev.h
 *
 * Copyright (C) 2003 Sean McGoogan (Sean.McGoogan@superh.com)
 *
 * Definitions क्रम the SuperH SH4-202 MicroDev board.
 */
#अगर_अघोषित __ASM_SH_MICRODEV_H
#घोषणा __ASM_SH_MICRODEV_H

बाह्य व्योम init_microdev_irq(व्योम);
बाह्य व्योम microdev_prपूर्णांक_fpga_पूर्णांकc_status(व्योम);

/*
 * The following are useful macros क्रम manipulating the पूर्णांकerrupt
 * controller (INTC) on the CPU-board FPGA.  should be noted that there
 * is an INTC on the FPGA, and a separate INTC on the SH4-202 core -
 * these are two dअगरferent things, both of which need to be prorammed to
 * correctly route - unक्रमtunately, they have the same name and
 * abbreviations!
 */
#घोषणा	MICRODEV_FPGA_INTC_BASE		0xa6110000ul				/* INTC base address on CPU-board FPGA */
#घोषणा	MICRODEV_FPGA_INTENB_REG	(MICRODEV_FPGA_INTC_BASE+0ul)		/* Interrupt Enable Register on INTC on CPU-board FPGA */
#घोषणा	MICRODEV_FPGA_INTDSB_REG	(MICRODEV_FPGA_INTC_BASE+8ul)		/* Interrupt Disable Register on INTC on CPU-board FPGA */
#घोषणा	MICRODEV_FPGA_INTC_MASK(n)	(1ul<<(n))				/* Interrupt mask to enable/disable INTC in CPU-board FPGA */
#घोषणा	MICRODEV_FPGA_INTPRI_REG(n)	(MICRODEV_FPGA_INTC_BASE+0x10+((n)/8)*8)/* Interrupt Priority Register on INTC on CPU-board FPGA */
#घोषणा	MICRODEV_FPGA_INTPRI_LEVEL(n,x)	((x)<<(((n)%8)*4))			/* MICRODEV_FPGA_INTPRI_LEVEL(पूर्णांक_number, पूर्णांक_level) */
#घोषणा	MICRODEV_FPGA_INTPRI_MASK(n)	(MICRODEV_FPGA_INTPRI_LEVEL((n),0xful))	/* Interrupt Priority Mask on INTC on CPU-board FPGA */
#घोषणा	MICRODEV_FPGA_INTSRC_REG	(MICRODEV_FPGA_INTC_BASE+0x30ul)	/* Interrupt Source Register on INTC on CPU-board FPGA */
#घोषणा	MICRODEV_FPGA_INTREQ_REG	(MICRODEV_FPGA_INTC_BASE+0x38ul)	/* Interrupt Request Register on INTC on CPU-board FPGA */


/*
 * The following are the IRQ numbers क्रम the Linux Kernel क्रम बाह्यal
 * पूर्णांकerrupts.  i.e. the numbers seen by 'cat /proc/interrupt'.
 */
#घोषणा MICRODEV_LINUX_IRQ_KEYBOARD	 1	/* SuperIO Keyboard */
#घोषणा MICRODEV_LINUX_IRQ_SERIAL1	 2	/* SuperIO Serial #1 */
#घोषणा MICRODEV_LINUX_IRQ_ETHERNET	 3	/* on-board Ethnernet */
#घोषणा MICRODEV_LINUX_IRQ_SERIAL2	 4	/* SuperIO Serial #2 */
#घोषणा MICRODEV_LINUX_IRQ_USB_HC	 7	/* on-board USB HC */
#घोषणा MICRODEV_LINUX_IRQ_MOUSE	12	/* SuperIO PS/2 Mouse */
#घोषणा MICRODEV_LINUX_IRQ_IDE2		13	/* SuperIO IDE #2 */
#घोषणा MICRODEV_LINUX_IRQ_IDE1		14	/* SuperIO IDE #1 */

/*
 * The following are the IRQ numbers क्रम the INTC on the FPGA क्रम
 * बाह्यal पूर्णांकerrupts.  i.e. the bits in the INTC रेजिस्टरs in the
 * FPGA.
 */
#घोषणा MICRODEV_FPGA_IRQ_KEYBOARD	 1	/* SuperIO Keyboard */
#घोषणा MICRODEV_FPGA_IRQ_SERIAL1	 3	/* SuperIO Serial #1 */
#घोषणा MICRODEV_FPGA_IRQ_SERIAL2	 4	/* SuperIO Serial #2 */
#घोषणा MICRODEV_FPGA_IRQ_MOUSE		12	/* SuperIO PS/2 Mouse */
#घोषणा MICRODEV_FPGA_IRQ_IDE1		14	/* SuperIO IDE #1 */
#घोषणा MICRODEV_FPGA_IRQ_IDE2		15	/* SuperIO IDE #2 */
#घोषणा MICRODEV_FPGA_IRQ_USB_HC	16	/* on-board USB HC */
#घोषणा MICRODEV_FPGA_IRQ_ETHERNET	18	/* on-board Ethnernet */

#घोषणा MICRODEV_IRQ_PCI_INTA		 8
#घोषणा MICRODEV_IRQ_PCI_INTB		 9
#घोषणा MICRODEV_IRQ_PCI_INTC		10
#घोषणा MICRODEV_IRQ_PCI_INTD		11

#घोषणा __IO_PREFIX microdev
#समावेश <यंत्र/io_generic.h>

#पूर्ण_अगर /* __ASM_SH_MICRODEV_H */
