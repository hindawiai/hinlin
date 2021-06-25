<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arch/arm/mach-footbridge/include/mach/irqs.h
 *
 * Copyright (C) 1998 Russell King
 * Copyright (C) 1998 Phil Blundell
 *
 * Changelog:
 *  20-Jan-1998	RMK	Started merge of EBSA286, CATS and NetWinder
 *  01-Feb-1999	PJB	ISA IRQs start at 0 not 16
 */
#समावेश <यंत्र/mach-types.h>

#घोषणा NR_IRQS			36
#घोषणा NR_DC21285_IRQS		16

#घोषणा _ISA_IRQ(x)		(0 + (x))
#घोषणा _ISA_INR(x)		((x) - 0)
#घोषणा _DC21285_IRQ(x)		(16 + (x))
#घोषणा _DC21285_INR(x)		((x) - 16)

/*
 * This is a list of all पूर्णांकerrupts that the 21285
 * can generate and we handle.
 */
#घोषणा IRQ_CONRX		_DC21285_IRQ(0)
#घोषणा IRQ_CONTX		_DC21285_IRQ(1)
#घोषणा IRQ_TIMER1		_DC21285_IRQ(2)
#घोषणा IRQ_TIMER2		_DC21285_IRQ(3)
#घोषणा IRQ_TIMER3		_DC21285_IRQ(4)
#घोषणा IRQ_IN0			_DC21285_IRQ(5)
#घोषणा IRQ_IN1			_DC21285_IRQ(6)
#घोषणा IRQ_IN2			_DC21285_IRQ(7)
#घोषणा IRQ_IN3			_DC21285_IRQ(8)
#घोषणा IRQ_DOORBELLHOST	_DC21285_IRQ(9)
#घोषणा IRQ_DMA1		_DC21285_IRQ(10)
#घोषणा IRQ_DMA2		_DC21285_IRQ(11)
#घोषणा IRQ_PCI			_DC21285_IRQ(12)
#घोषणा IRQ_SDRAMPARITY		_DC21285_IRQ(13)
#घोषणा IRQ_I2OINPOST		_DC21285_IRQ(14)
#घोषणा IRQ_PCI_ABORT		_DC21285_IRQ(15)
#घोषणा IRQ_PCI_SERR		_DC21285_IRQ(16)
#घोषणा IRQ_DISCARD_TIMER	_DC21285_IRQ(17)
#घोषणा IRQ_PCI_DPERR		_DC21285_IRQ(18)
#घोषणा IRQ_PCI_PERR		_DC21285_IRQ(19)

#घोषणा IRQ_ISA_TIMER		_ISA_IRQ(0)
#घोषणा IRQ_ISA_KEYBOARD	_ISA_IRQ(1)
#घोषणा IRQ_ISA_CASCADE		_ISA_IRQ(2)
#घोषणा IRQ_ISA_UART2		_ISA_IRQ(3)
#घोषणा IRQ_ISA_UART		_ISA_IRQ(4)
#घोषणा IRQ_ISA_FLOPPY		_ISA_IRQ(6)
#घोषणा IRQ_ISA_PRINTER		_ISA_IRQ(7)
#घोषणा IRQ_ISA_RTC_ALARM	_ISA_IRQ(8)
#घोषणा IRQ_ISA_2		_ISA_IRQ(9)
#घोषणा IRQ_ISA_PS2MOUSE	_ISA_IRQ(12)
#घोषणा IRQ_ISA_HARDDISK1	_ISA_IRQ(14)
#घोषणा IRQ_ISA_HARDDISK2	_ISA_IRQ(15)

#घोषणा IRQ_MASK_UART_RX	(1 << 2)
#घोषणा IRQ_MASK_UART_TX	(1 << 3)
#घोषणा IRQ_MASK_TIMER1		(1 << 4)
#घोषणा IRQ_MASK_TIMER2		(1 << 5)
#घोषणा IRQ_MASK_TIMER3		(1 << 6)
#घोषणा IRQ_MASK_IN0		(1 << 8)
#घोषणा IRQ_MASK_IN1		(1 << 9)
#घोषणा IRQ_MASK_IN2		(1 << 10)
#घोषणा IRQ_MASK_IN3		(1 << 11)
#घोषणा IRQ_MASK_DOORBELLHOST	(1 << 15)
#घोषणा IRQ_MASK_DMA1		(1 << 16)
#घोषणा IRQ_MASK_DMA2		(1 << 17)
#घोषणा IRQ_MASK_PCI		(1 << 18)
#घोषणा IRQ_MASK_SDRAMPARITY	(1 << 24)
#घोषणा IRQ_MASK_I2OINPOST	(1 << 25)
#घोषणा IRQ_MASK_PCI_ABORT	((1 << 29) | (1 << 30))
#घोषणा IRQ_MASK_PCI_SERR	(1 << 23)
#घोषणा IRQ_MASK_DISCARD_TIMER	(1 << 27)
#घोषणा IRQ_MASK_PCI_DPERR	(1 << 28)
#घोषणा IRQ_MASK_PCI_PERR	(1 << 31)

/*
 * Netwinder पूर्णांकerrupt allocations
 */
#घोषणा IRQ_NETWINDER_ETHER10	IRQ_IN0
#घोषणा IRQ_NETWINDER_ETHER100	IRQ_IN1
#घोषणा IRQ_NETWINDER_VIDCOMP	IRQ_IN2
#घोषणा IRQ_NETWINDER_PS2MOUSE	_ISA_IRQ(5)
#घोषणा IRQ_NETWINDER_IR	_ISA_IRQ(6)
#घोषणा IRQ_NETWINDER_BUTTON	_ISA_IRQ(10)
#घोषणा IRQ_NETWINDER_VGA	_ISA_IRQ(11)
#घोषणा IRQ_NETWINDER_SOUND	_ISA_IRQ(12)

#घोषणा I8042_KBD_IRQ	IRQ_ISA_KEYBOARD
#घोषणा I8042_AUX_IRQ	(machine_is_netwinder() ? IRQ_NETWINDER_PS2MOUSE : IRQ_ISA_PS2MOUSE)
#घोषणा IRQ_FLOPPYDISK	IRQ_ISA_FLOPPY

#घोषणा irq_canonicalize(_i)	(((_i) == IRQ_ISA_CASCADE) ? IRQ_ISA_2 : _i)
