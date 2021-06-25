<शैली गुरु>
/*
 * platक्रमm/hardware.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 Tensilica Inc.
 */

/*
 * This file contains the hardware configuration of the XT2000 board.
 */

#अगर_अघोषित _XTENSA_XT2000_HARDWARE_H
#घोषणा _XTENSA_XT2000_HARDWARE_H

#समावेश <यंत्र/core.h>

/*
 * On-board components.
 */

#घोषणा SONIC83934_INTNUM	XCHAL_EXTINT3_NUM
#घोषणा SONIC83934_ADDR		IOADDR(0x0d030000)

/*
 * V3-PCI
 */

/* The XT2000 uses the V3 as a cascaded पूर्णांकerrupt controller क्रम the PCI bus */

#घोषणा IRQ_PCI_A		(XCHAL_NUM_INTERRUPTS + 0)
#घोषणा IRQ_PCI_B		(XCHAL_NUM_INTERRUPTS + 1)
#घोषणा IRQ_PCI_C		(XCHAL_NUM_INTERRUPTS + 2)

/*
 * Various other components.
 */

#घोषणा XT2000_LED_ADDR		IOADDR(0x0d040000)

#पूर्ण_अगर /* _XTENSA_XT2000_HARDWARE_H */
