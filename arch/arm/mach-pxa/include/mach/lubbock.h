<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/mach-pxa/include/mach/lubbock.h
 *
 *  Author:	Nicolas Pitre
 *  Created:	Jun 15, 2001
 *  Copyright:	MontaVista Software Inc.
 */

#समावेश <mach/irqs.h>

#घोषणा LUBBOCK_ETH_PHYS	PXA_CS3_PHYS

#घोषणा LUBBOCK_FPGA_PHYS	PXA_CS2_PHYS
#घोषणा LUBBOCK_FPGA_VIRT	(0xf0000000)
#घोषणा LUB_P2V(x)		((x) - LUBBOCK_FPGA_PHYS + LUBBOCK_FPGA_VIRT)
#घोषणा LUB_V2P(x)		((x) - LUBBOCK_FPGA_VIRT + LUBBOCK_FPGA_PHYS)

#अगर_अघोषित __ASSEMBLY__
#  define __LUB_REG(x)		(*((अस्थिर अचिन्हित दीर्घ *)LUB_P2V(x)))
#अन्यथा
#  define __LUB_REG(x)		LUB_P2V(x)
#पूर्ण_अगर

/* FPGA रेजिस्टर भव addresses */
#घोषणा LUB_WHOAMI		__LUB_REG(LUBBOCK_FPGA_PHYS + 0x000)
#घोषणा LUB_DISC_BLNK_LED	__LUB_REG(LUBBOCK_FPGA_PHYS + 0x040)
#घोषणा LUB_CONF_SWITCHES	__LUB_REG(LUBBOCK_FPGA_PHYS + 0x050)
#घोषणा LUB_USER_SWITCHES	__LUB_REG(LUBBOCK_FPGA_PHYS + 0x060)
#घोषणा LUB_MISC_WR		__LUB_REG(LUBBOCK_FPGA_PHYS + 0x080)
#घोषणा LUB_MISC_RD		__LUB_REG(LUBBOCK_FPGA_PHYS + 0x090)
#घोषणा LUB_IRQ_MASK_EN		__LUB_REG(LUBBOCK_FPGA_PHYS + 0x0c0)
#घोषणा LUB_IRQ_SET_CLR		__LUB_REG(LUBBOCK_FPGA_PHYS + 0x0d0)
#घोषणा LUB_GP			__LUB_REG(LUBBOCK_FPGA_PHYS + 0x100)

/* Board specअगरic IRQs */
#घोषणा LUBBOCK_NR_IRQS		IRQ_BOARD_START

#घोषणा LUBBOCK_IRQ(x)		(LUBBOCK_NR_IRQS + (x))
#घोषणा LUBBOCK_SD_IRQ		LUBBOCK_IRQ(0)
#घोषणा LUBBOCK_SA1111_IRQ	LUBBOCK_IRQ(1)
#घोषणा LUBBOCK_USB_IRQ		LUBBOCK_IRQ(2)  /* usb connect */
#घोषणा LUBBOCK_ETH_IRQ		LUBBOCK_IRQ(3)
#घोषणा LUBBOCK_UCB1400_IRQ	LUBBOCK_IRQ(4)
#घोषणा LUBBOCK_BB_IRQ		LUBBOCK_IRQ(5)
#घोषणा LUBBOCK_USB_DISC_IRQ	LUBBOCK_IRQ(6)  /* usb disconnect */
#घोषणा LUBBOCK_LAST_IRQ	LUBBOCK_IRQ(6)

#घोषणा LUBBOCK_SA1111_IRQ_BASE	(LUBBOCK_NR_IRQS + 32)
