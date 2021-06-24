<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * arch/arm/mach-pxa/include/mach/pcm990_baseboard.h
 *
 * (c) 2003 Phytec Messtechnik GmbH <armlinux@phytec.de>
 * (c) 2007 Juergen Beisert <j.beisert@pengutronix.de>
 */

#समावेश "pcm027.h"
#समावेश <mach/irqs.h> /* PXA_GPIO_TO_IRQ */

/*
 * definitions relevant only when the PCM-990
 * development base board is in use
 */

/* CPLD's पूर्णांकerrupt controller is connected to PCM-027 GPIO 9 */
#घोषणा PCM990_CTRL_INT_IRQ_GPIO	9
#घोषणा PCM990_CTRL_INT_IRQ		PXA_GPIO_TO_IRQ(PCM990_CTRL_INT_IRQ_GPIO)
#घोषणा PCM990_CTRL_INT_IRQ_EDGE	IRQ_TYPE_EDGE_RISING
#घोषणा PCM990_CTRL_PHYS		PXA_CS1_PHYS	/* 16-Bit */
#घोषणा PCM990_CTRL_SIZE		(1*1024*1024)

#घोषणा PCM990_CTRL_PWR_IRQ_GPIO	14
#घोषणा PCM990_CTRL_PWR_IRQ		PXA_GPIO_TO_IRQ(PCM990_CTRL_PWR_IRQ_GPIO)
#घोषणा PCM990_CTRL_PWR_IRQ_EDGE	IRQ_TYPE_EDGE_RISING

/* visible CPLD (U7) रेजिस्टरs */
#घोषणा PCM990_CTRL_REG0	0x0000	/* RESET REGISTER */
#घोषणा PCM990_CTRL_SYSRES	0x0001	/* System RESET REGISTER */
#घोषणा PCM990_CTRL_RESOUT	0x0002	/* RESETOUT Enable REGISTER */
#घोषणा PCM990_CTRL_RESGPIO	0x0004	/* RESETGPIO Enable REGISTER */

#घोषणा PCM990_CTRL_REG1	0x0002	/* Power REGISTER */
#घोषणा PCM990_CTRL_5VOFF	0x0001	/* Disable  5V Regulators */
#घोषणा PCM990_CTRL_CANPWR	0x0004	/* Enable CANPWR ADUM */
#घोषणा PCM990_CTRL_PM_5V	0x0008	/* Read 5V OK */

#घोषणा PCM990_CTRL_REG2	0x0004	/* LED REGISTER */
#घोषणा PCM990_CTRL_LEDPWR	0x0001	/* POWER LED enable */
#घोषणा PCM990_CTRL_LEDBAS	0x0002	/* BASIS LED enable */
#घोषणा PCM990_CTRL_LEDUSR	0x0004	/* USER LED enable */

#घोषणा PCM990_CTRL_REG3	0x0006	/* LCD CTRL REGISTER 3 */
#घोषणा PCM990_CTRL_LCDPWR	0x0001	/* RW LCD Power on */
#घोषणा PCM990_CTRL_LCDON	0x0002	/* RW LCD Latch on */
#घोषणा PCM990_CTRL_LCDPOS1	0x0004	/* RW POS 1 */
#घोषणा PCM990_CTRL_LCDPOS2	0x0008	/* RW POS 2 */

#घोषणा PCM990_CTRL_REG4	0x0008	/* MMC1 CTRL REGISTER 4 */
#घोषणा PCM990_CTRL_MMC1PWR	0x0001 /* RW MMC1 Power on */

#घोषणा PCM990_CTRL_REG5	0x000A	/* MMC2 CTRL REGISTER 5 */
#घोषणा PCM990_CTRL_MMC2PWR	0x0001	/* RW MMC2 Power on */
#घोषणा PCM990_CTRL_MMC2LED	0x0002	/* RW MMC2 LED */
#घोषणा PCM990_CTRL_MMC2DE	0x0004	/* R MMC2 Card detect */
#घोषणा PCM990_CTRL_MMC2WP	0x0008	/* R MMC2 Card ग_लिखो protect */

#घोषणा PCM990_CTRL_INTSETCLR	0x000C	/* Interrupt Clear REGISTER */
#घोषणा PCM990_CTRL_INTC0	0x0001	/* Clear Reg BT Detect */
#घोषणा PCM990_CTRL_INTC1	0x0002	/* Clear Reg FR RI */
#घोषणा PCM990_CTRL_INTC2	0x0004	/* Clear Reg MMC1 Detect */
#घोषणा PCM990_CTRL_INTC3	0x0008	/* Clear Reg PM_5V off */

#घोषणा PCM990_CTRL_INTMSKENA	0x000E	/* Interrupt Enable REGISTER */
#घोषणा PCM990_CTRL_ENAINT0	0x0001	/* Enable Int BT Detect */
#घोषणा PCM990_CTRL_ENAINT1	0x0002	/* Enable Int FR RI */
#घोषणा PCM990_CTRL_ENAINT2	0x0004	/* Enable Int MMC1 Detect */
#घोषणा PCM990_CTRL_ENAINT3	0x0008	/* Enable Int PM_5V off */

#घोषणा PCM990_CTRL_REG8	0x0014	/* Uart REGISTER */
#घोषणा PCM990_CTRL_FFSD	0x0001	/* BT Uart Enable */
#घोषणा PCM990_CTRL_BTSD	0x0002	/* FF Uart Enable */
#घोषणा PCM990_CTRL_FFRI	0x0004	/* FF Uart RI detect */
#घोषणा PCM990_CTRL_BTRX	0x0008	/* BT Uart Rx detect */

#घोषणा PCM990_CTRL_REG9	0x0010	/* AC97 Flash REGISTER */
#घोषणा PCM990_CTRL_FLWP	0x0001	/* pC Flash Write Protect */
#घोषणा PCM990_CTRL_FLDIS	0x0002	/* pC Flash Disable */
#घोषणा PCM990_CTRL_AC97ENA	0x0004	/* Enable AC97 Expansion */

#घोषणा PCM990_CTRL_REG10	0x0012	/* GPS-REGISTER */
#घोषणा PCM990_CTRL_GPSPWR	0x0004	/* GPS-Modul Power on */
#घोषणा PCM990_CTRL_GPSENA	0x0008	/* GPS-Modul Enable */

#घोषणा PCM990_CTRL_REG11	0x0014	/* Accu REGISTER */
#घोषणा PCM990_CTRL_ACENA	0x0001	/* Charge Enable */
#घोषणा PCM990_CTRL_ACSEL	0x0002	/* Charge Akku -> DC Enable */
#घोषणा PCM990_CTRL_ACPRES	0x0004	/* DC Present */
#घोषणा PCM990_CTRL_ACALARM	0x0008	/* Error Akku */

/*
 * IDE
 */
#घोषणा PCM990_IDE_IRQ_GPIO	13
#घोषणा PCM990_IDE_IRQ		PXA_GPIO_TO_IRQ(PCM990_IDE_IRQ_GPIO)
#घोषणा PCM990_IDE_IRQ_EDGE	IRQ_TYPE_EDGE_RISING
#घोषणा PCM990_IDE_PLD_PHYS	0x20000000	/* 16 bit wide */
#घोषणा PCM990_IDE_PLD_BASE	0xee000000
#घोषणा PCM990_IDE_PLD_SIZE	(1*1024*1024)

/* visible CPLD (U6) रेजिस्टरs */
#घोषणा PCM990_IDE_PLD_REG0	0x1000	/* OFFSET IDE REGISTER 0 */
#घोषणा PCM990_IDE_PM5V		0x0004	/* R System VCC_5V */
#घोषणा PCM990_IDE_STBY		0x0008	/* R System StandBy */

#घोषणा PCM990_IDE_PLD_REG1	0x1002	/* OFFSET IDE REGISTER 1 */
#घोषणा PCM990_IDE_IDEMODE	0x0001	/* R TrueIDE Mode */
#घोषणा PCM990_IDE_DMAENA	0x0004	/* RW DMA Enable */
#घोषणा PCM990_IDE_DMA1_0	0x0008	/* RW 1=DREQ1 0=DREQ0 */

#घोषणा PCM990_IDE_PLD_REG2	0x1004	/* OFFSET IDE REGISTER 2 */
#घोषणा PCM990_IDE_RESENA	0x0001	/* RW IDE Reset Bit enable */
#घोषणा PCM990_IDE_RES		0x0002	/* RW IDE Reset Bit */
#घोषणा PCM990_IDE_RDY		0x0008	/* RDY */

#घोषणा PCM990_IDE_PLD_REG3	0x1006	/* OFFSET IDE REGISTER 3 */
#घोषणा PCM990_IDE_IDEOE	0x0001	/* RW Latch on Databus */
#घोषणा PCM990_IDE_IDEON	0x0002	/* RW Latch on Control Address */
#घोषणा PCM990_IDE_IDEIN	0x0004	/* RW Latch on Interrupt usw. */

#घोषणा PCM990_IDE_PLD_REG4	0x1008	/* OFFSET IDE REGISTER 4 */
#घोषणा PCM990_IDE_PWRENA	0x0001	/* RW IDE Power enable */
#घोषणा PCM990_IDE_5V		0x0002	/* R IDE Power 5V */
#घोषणा PCM990_IDE_PWG		0x0008	/* R IDE Power is on */

#घोषणा PCM990_IDE_PLD_P2V(x) ((x) - PCM990_IDE_PLD_PHYS + PCM990_IDE_PLD_BASE)
#घोषणा PCM990_IDE_PLD_V2P(x) ((x) - PCM990_IDE_PLD_BASE + PCM990_IDE_PLD_PHYS)

/*
 * Compact Flash
 */
#घोषणा PCM990_CF_IRQ_GPIO	11
#घोषणा PCM990_CF_IRQ		PXA_GPIO_TO_IRQ(PCM990_CF_IRQ_GPIO)
#घोषणा PCM990_CF_IRQ_EDGE	IRQ_TYPE_EDGE_RISING

#घोषणा PCM990_CF_CD_GPIO	12
#घोषणा PCM990_CF_CD		PXA_GPIO_TO_IRQ(PCM990_CF_CD_GPIO)
#घोषणा PCM990_CF_CD_EDGE	IRQ_TYPE_EDGE_RISING

#घोषणा PCM990_CF_PLD_PHYS	0x30000000	/* 16 bit wide */

/* visible CPLD (U6) रेजिस्टरs */
#घोषणा PCM990_CF_PLD_REG0	0x1000	/* OFFSET CF REGISTER 0 */
#घोषणा PCM990_CF_REG0_LED	0x0001	/* RW LED on */
#घोषणा PCM990_CF_REG0_BLK	0x0002	/* RW LED flash when access */
#घोषणा PCM990_CF_REG0_PM5V	0x0004	/* R System VCC_5V enable */
#घोषणा PCM990_CF_REG0_STBY	0x0008	/* R System StandBy */

#घोषणा PCM990_CF_PLD_REG1	0x1002	/* OFFSET CF REGISTER 1 */
#घोषणा PCM990_CF_REG1_IDEMODE	0x0001	/* RW CF card run as TrueIDE */
#घोषणा PCM990_CF_REG1_CF0	0x0002	/* RW CF card at ADDR 0x28000000 */

#घोषणा PCM990_CF_PLD_REG2	0x1004	/* OFFSET CF REGISTER 2 */
#घोषणा PCM990_CF_REG2_RES	0x0002	/* RW CF RESET BIT */
#घोषणा PCM990_CF_REG2_RDYENA	0x0004	/* RW Enable CF_RDY */
#घोषणा PCM990_CF_REG2_RDY	0x0008	/* R CF_RDY auf PWAIT */

#घोषणा PCM990_CF_PLD_REG3	0x1006	/* OFFSET CF REGISTER 3 */
#घोषणा PCM990_CF_REG3_CFOE	0x0001	/* RW Latch on Databus */
#घोषणा PCM990_CF_REG3_CFON	0x0002	/* RW Latch on Control Address */
#घोषणा PCM990_CF_REG3_CFIN	0x0004	/* RW Latch on Interrupt usw. */
#घोषणा PCM990_CF_REG3_CFCD	0x0008	/* RW Latch on CD1/2 VS1/2 usw */

#घोषणा PCM990_CF_PLD_REG4	0x1008	/* OFFSET CF REGISTER 4 */
#घोषणा PCM990_CF_REG4_PWRENA	0x0001	/* RW CF Power on (CD1/2 = "00") */
#घोषणा PCM990_CF_REG4_5_3V	0x0002	/* RW 1 = 5V CF_VCC 0 = 3 V CF_VCC */
#घोषणा PCM990_CF_REG4_3B	0x0004	/* RW 3.0V Backup from VCC (5_3V=0) */
#घोषणा PCM990_CF_REG4_PWG	0x0008	/* R CF-Power is on */

#घोषणा PCM990_CF_PLD_REG5	0x100A	/* OFFSET CF REGISTER 5 */
#घोषणा PCM990_CF_REG5_BVD1	0x0001	/* R CF /BVD1 */
#घोषणा PCM990_CF_REG5_BVD2	0x0002	/* R CF /BVD2 */
#घोषणा PCM990_CF_REG5_VS1	0x0004	/* R CF /VS1 */
#घोषणा PCM990_CF_REG5_VS2	0x0008	/* R CF /VS2 */

#घोषणा PCM990_CF_PLD_REG6	0x100C	/* OFFSET CF REGISTER 6 */
#घोषणा PCM990_CF_REG6_CD1	0x0001	/* R CF Card_Detect1 */
#घोषणा PCM990_CF_REG6_CD2	0x0002	/* R CF Card_Detect2 */

/*
 * Wolfson AC97 Touch
 */
#घोषणा PCM990_AC97_IRQ_GPIO	10
#घोषणा PCM990_AC97_IRQ		PXA_GPIO_TO_IRQ(PCM990_AC97_IRQ_GPIO)
#घोषणा PCM990_AC97_IRQ_EDGE	IRQ_TYPE_EDGE_RISING

/*
 * MMC phyCORE
 */
#घोषणा PCM990_MMC0_IRQ_GPIO	9
#घोषणा PCM990_MMC0_IRQ		PXA_GPIO_TO_IRQ(PCM990_MMC0_IRQ_GPIO)
#घोषणा PCM990_MMC0_IRQ_EDGE	IRQ_TYPE_EDGE_FALLING

/*
 * USB phyCore
 */
#घोषणा PCM990_USB_OVERCURRENT (88 | GPIO_ALT_FN_1_IN)
#घोषणा PCM990_USB_PWR_EN (89 | GPIO_ALT_FN_2_OUT)
