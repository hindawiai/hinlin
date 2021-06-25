<शैली गुरु>
/*
 * Hardware definitions common to all DaVinci family processors
 *
 * Author: Kevin Hilman, Deep Root Systems, LLC
 *
 * 2007 (c) Deep Root Systems, LLC. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
#अगर_अघोषित __ASM_ARCH_HARDWARE_H
#घोषणा __ASM_ARCH_HARDWARE_H

/*
 * Beक्रमe you add anything to ths file:
 *
 * This header is क्रम defines common to ALL DaVinci family chips.
 * Anything that is chip specअगरic should go in <chipname>.h,
 * and the chip/board init code should then explicitly include
 * <chipname>.h
 */
/*
 * I/O mapping
 */
#घोषणा IO_PHYS				UL(0x01c00000)
#घोषणा IO_OFFSET			0xfd000000 /* Virtual IO = 0xfec00000 */
#घोषणा IO_SIZE				0x00400000
#घोषणा IO_VIRT				(IO_PHYS + IO_OFFSET)
#घोषणा io_v2p(va)			((va) - IO_OFFSET)
#घोषणा __IO_ADDRESS(x)			((x) + IO_OFFSET)
#घोषणा IO_ADDRESS(pa)			IOMEM(__IO_ADDRESS(pa))

#पूर्ण_अगर /* __ASM_ARCH_HARDWARE_H */
