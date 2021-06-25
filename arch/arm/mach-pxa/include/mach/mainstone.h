<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/mach-pxa/include/mach/मुख्यstone.h
 *
 *  Author:	Nicolas Pitre
 *  Created:	Nov 14, 2002
 *  Copyright:	MontaVista Software Inc.
 */

#अगर_अघोषित ASM_ARCH_MAINSTONE_H
#घोषणा ASM_ARCH_MAINSTONE_H

#समावेश <mach/irqs.h>

#घोषणा MST_ETH_PHYS		PXA_CS4_PHYS

#घोषणा MST_FPGA_PHYS		PXA_CS2_PHYS
#घोषणा MST_FPGA_VIRT		(0xf0000000)
#घोषणा MST_P2V(x)		((x) - MST_FPGA_PHYS + MST_FPGA_VIRT)
#घोषणा MST_V2P(x)		((x) - MST_FPGA_VIRT + MST_FPGA_PHYS)

#अगर_अघोषित __ASSEMBLY__
# define __MST_REG(x)		(*((अस्थिर अचिन्हित दीर्घ *)MST_P2V(x)))
#अन्यथा
# define __MST_REG(x)		MST_P2V(x)
#पूर्ण_अगर

/* board level रेजिस्टरs in the FPGA */

#घोषणा MST_LEDDAT1		__MST_REG(0x08000010)
#घोषणा MST_LEDDAT2		__MST_REG(0x08000014)
#घोषणा MST_LEDCTRL		__MST_REG(0x08000040)
#घोषणा MST_GPSWR		__MST_REG(0x08000060)
#घोषणा MST_MSCWR1		__MST_REG(0x08000080)
#घोषणा MST_MSCWR2		__MST_REG(0x08000084)
#घोषणा MST_MSCWR3		__MST_REG(0x08000088)
#घोषणा MST_MSCRD		__MST_REG(0x08000090)
#घोषणा MST_INTMSKENA		__MST_REG(0x080000c0)
#घोषणा MST_INTSETCLR		__MST_REG(0x080000d0)
#घोषणा MST_PCMCIA0		__MST_REG(0x080000e0)
#घोषणा MST_PCMCIA1		__MST_REG(0x080000e4)

#घोषणा MST_MSCWR1_CAMERA_ON	(1 << 15)  /* Camera पूर्णांकerface घातer control */
#घोषणा MST_MSCWR1_CAMERA_SEL	(1 << 14)  /* Camera पूर्णांकerface mux control */
#घोषणा MST_MSCWR1_LCD_CTL	(1 << 13)  /* General-purpose LCD control */
#घोषणा MST_MSCWR1_MS_ON	(1 << 12)  /* Memory Stick घातer control */
#घोषणा MST_MSCWR1_MMC_ON	(1 << 11)  /* MultiMediaCard* घातer control */
#घोषणा MST_MSCWR1_MS_SEL	(1 << 10)  /* SD/MS multiplexer control */
#घोषणा MST_MSCWR1_BB_SEL	(1 << 9)   /* PCMCIA/Baseband multiplexer */
#घोषणा MST_MSCWR1_BT_ON	(1 << 8)   /* Bluetooth UART transceiver */
#घोषणा MST_MSCWR1_BTDTR	(1 << 7)   /* Bluetooth UART DTR */

#घोषणा MST_MSCWR1_IRDA_MASK	(3 << 5)   /* IrDA transceiver mode */
#घोषणा MST_MSCWR1_IRDA_FULL	(0 << 5)   /* full distance घातer */
#घोषणा MST_MSCWR1_IRDA_OFF	(1 << 5)   /* shutकरोwn */
#घोषणा MST_MSCWR1_IRDA_MED	(2 << 5)   /* 2/3 distance घातer */
#घोषणा MST_MSCWR1_IRDA_LOW	(3 << 5)   /* 1/3 distance घातer */

#घोषणा MST_MSCWR1_IRDA_FIR	(1 << 4)   /* IrDA transceiver SIR/FIR */
#घोषणा MST_MSCWR1_GREENLED	(1 << 3)   /* LED D1 control */
#घोषणा MST_MSCWR1_PDC_CTL	(1 << 2)   /* reserved */
#घोषणा MST_MSCWR1_MTR_ON	(1 << 1)   /* Silent alert motor */
#घोषणा MST_MSCWR1_SYSRESET	(1 << 0)   /* System reset */

#घोषणा MST_MSCWR2_USB_OTG_RST	(1 << 6)   /* USB On The Go reset */
#घोषणा MST_MSCWR2_USB_OTG_SEL	(1 << 5)   /* USB On The Go control */
#घोषणा MST_MSCWR2_nUSBC_SC	(1 << 4)   /* USB client soft connect control */
#घोषणा MST_MSCWR2_I2S_SPKROFF	(1 << 3)   /* I2S CODEC amplअगरier control */
#घोषणा MST_MSCWR2_AC97_SPKROFF	(1 << 2)   /* AC97 CODEC amplअगरier control */
#घोषणा MST_MSCWR2_RADIO_PWR	(1 << 1)   /* Radio module घातer control */
#घोषणा MST_MSCWR2_RADIO_WAKE	(1 << 0)   /* Radio module wake-up संकेत */

#घोषणा MST_MSCWR3_GPIO_RESET_EN	(1 << 2) /* Enable GPIO Reset */
#घोषणा MST_MSCWR3_GPIO_RESET		(1 << 1) /* Initiate a GPIO Reset */
#घोषणा MST_MSCWR3_COMMS_SW_RESET	(1 << 0) /* Communications Processor Reset Control */

#घोषणा MST_MSCRD_nPENIRQ	(1 << 9)   /* ADI7873* nPENIRQ संकेत */
#घोषणा MST_MSCRD_nMEMSTK_CD	(1 << 8)   /* Memory Stick detection संकेत */
#घोषणा MST_MSCRD_nMMC_CD	(1 << 7)   /* SD/MMC card detection संकेत */
#घोषणा MST_MSCRD_nUSIM_CD	(1 << 6)   /* USIM card detection संकेत */
#घोषणा MST_MSCRD_USB_CBL	(1 << 5)   /* USB client cable status */
#घोषणा MST_MSCRD_TS_BUSY	(1 << 4)   /* ADI7873 busy */
#घोषणा MST_MSCRD_BTDSR		(1 << 3)   /* Bluetooth UART DSR */
#घोषणा MST_MSCRD_BTRI		(1 << 2)   /* Bluetooth UART Ring Indicator */
#घोषणा MST_MSCRD_BTDCD		(1 << 1)   /* Bluetooth UART DCD */
#घोषणा MST_MSCRD_nMMC_WP	(1 << 0)   /* SD/MMC ग_लिखो-protect status */

#घोषणा MST_INT_S1_IRQ		(1 << 15)  /* PCMCIA socket 1 IRQ */
#घोषणा MST_INT_S1_STSCHG	(1 << 14)  /* PCMCIA socket 1 status changed */
#घोषणा MST_INT_S1_CD		(1 << 13)  /* PCMCIA socket 1 card detection */
#घोषणा MST_INT_S0_IRQ		(1 << 11)  /* PCMCIA socket 0 IRQ */
#घोषणा MST_INT_S0_STSCHG	(1 << 10)  /* PCMCIA socket 0 status changed */
#घोषणा MST_INT_S0_CD		(1 << 9)   /* PCMCIA socket 0 card detection */
#घोषणा MST_INT_nEXBRD_INT	(1 << 7)   /* Expansion board IRQ */
#घोषणा MST_INT_MSINS		(1 << 6)   /* Memory Stick* detection */
#घोषणा MST_INT_PENIRQ		(1 << 5)   /* ADI7873* touch-screen IRQ */
#घोषणा MST_INT_AC97		(1 << 4)   /* AC'97 CODEC IRQ */
#घोषणा MST_INT_ETHERNET	(1 << 3)   /* Ethernet controller IRQ */
#घोषणा MST_INT_USBC		(1 << 2)   /* USB client cable detection IRQ */
#घोषणा MST_INT_USIM		(1 << 1)   /* USIM card detection IRQ */
#घोषणा MST_INT_MMC		(1 << 0)   /* MMC/SD card detection IRQ */

#घोषणा MST_PCMCIA_nIRQ		(1 << 10)  /* IRQ / पढ़ोy संकेत */
#घोषणा MST_PCMCIA_nSPKR_BVD2	(1 << 9)   /* VDD sense / digital speaker */
#घोषणा MST_PCMCIA_nSTSCHG_BVD1	(1 << 8)   /* VDD sense / card status changed */
#घोषणा MST_PCMCIA_nVS2		(1 << 7)   /* VSS voltage sense */
#घोषणा MST_PCMCIA_nVS1		(1 << 6)   /* VSS voltage sense */
#घोषणा MST_PCMCIA_nCD		(1 << 5)   /* Card detection संकेत */
#घोषणा MST_PCMCIA_RESET	(1 << 4)   /* Card reset संकेत */
#घोषणा MST_PCMCIA_PWR_MASK	(0x000f)   /* MAX1602 घातer-supply controls */

#घोषणा MST_PCMCIA_PWR_VPP_0    0x0	   /* voltage VPP = 0V */
#घोषणा MST_PCMCIA_PWR_VPP_120  0x2 	   /* voltage VPP = 12V*/
#घोषणा MST_PCMCIA_PWR_VPP_VCC  0x1	   /* voltage VPP = VCC */
#घोषणा MST_PCMCIA_PWR_VCC_0    0x0	   /* voltage VCC = 0V */
#घोषणा MST_PCMCIA_PWR_VCC_33   0x8	   /* voltage VCC = 3.3V */
#घोषणा MST_PCMCIA_PWR_VCC_50   0x4	   /* voltage VCC = 5.0V */

#घोषणा MST_PCMCIA_INPUTS \
	(MST_PCMCIA_nIRQ | MST_PCMCIA_nSPKR_BVD2 | MST_PCMCIA_nSTSCHG_BVD1 | \
	 MST_PCMCIA_nVS2 | MST_PCMCIA_nVS1 | MST_PCMCIA_nCD)

/* board specअगरic IRQs */
#घोषणा MAINSTONE_NR_IRQS	IRQ_BOARD_START

#घोषणा MAINSTONE_IRQ(x)	(MAINSTONE_NR_IRQS + (x))
#घोषणा MAINSTONE_MMC_IRQ	MAINSTONE_IRQ(0)
#घोषणा MAINSTONE_USIM_IRQ	MAINSTONE_IRQ(1)
#घोषणा MAINSTONE_USBC_IRQ	MAINSTONE_IRQ(2)
#घोषणा MAINSTONE_ETHERNET_IRQ	MAINSTONE_IRQ(3)
#घोषणा MAINSTONE_AC97_IRQ	MAINSTONE_IRQ(4)
#घोषणा MAINSTONE_PEN_IRQ	MAINSTONE_IRQ(5)
#घोषणा MAINSTONE_MSINS_IRQ	MAINSTONE_IRQ(6)
#घोषणा MAINSTONE_EXBRD_IRQ	MAINSTONE_IRQ(7)
#घोषणा MAINSTONE_S0_CD_IRQ	MAINSTONE_IRQ(9)
#घोषणा MAINSTONE_S0_STSCHG_IRQ	MAINSTONE_IRQ(10)
#घोषणा MAINSTONE_S0_IRQ	MAINSTONE_IRQ(11)
#घोषणा MAINSTONE_S1_CD_IRQ	MAINSTONE_IRQ(13)
#घोषणा MAINSTONE_S1_STSCHG_IRQ	MAINSTONE_IRQ(14)
#घोषणा MAINSTONE_S1_IRQ	MAINSTONE_IRQ(15)

#पूर्ण_अगर
