<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * arch/arm/mach-pxa/include/mach/pcm027.h
 *
 * (c) 2003 Phytec Messtechnik GmbH <armlinux@phytec.de>
 * (c) 2007 Juergen Beisert <j.beisert@pengutronix.de>
 */

/*
 * Definitions of CPU card resources only
 */

#समावेश <mach/irqs.h> /* PXA_GPIO_TO_IRQ */

/* phyCORE-PXA270 (PCM027) Interrupts */
#घोषणा PCM027_IRQ(x)          (IRQ_BOARD_START + (x))
#घोषणा PCM027_BTDET_IRQ       PCM027_IRQ(0)
#घोषणा PCM027_FF_RI_IRQ       PCM027_IRQ(1)
#घोषणा PCM027_MMCDET_IRQ      PCM027_IRQ(2)
#घोषणा PCM027_PM_5V_IRQ       PCM027_IRQ(3)

#घोषणा PCM027_NR_IRQS		(IRQ_BOARD_START + 32)

/* I2C RTC */
#घोषणा PCM027_RTC_IRQ_GPIO	0
#घोषणा PCM027_RTC_IRQ		PXA_GPIO_TO_IRQ(PCM027_RTC_IRQ_GPIO)
#घोषणा PCM027_RTC_IRQ_EDGE	IRQ_TYPE_EDGE_FALLING
#घोषणा ADR_PCM027_RTC		0x51	/* I2C address */

/* I2C EEPROM */
#घोषणा ADR_PCM027_EEPROM	0x54	/* I2C address */

/* Ethernet chip (SMSC91C111) */
#घोषणा PCM027_ETH_IRQ_GPIO	52
#घोषणा PCM027_ETH_IRQ		PXA_GPIO_TO_IRQ(PCM027_ETH_IRQ_GPIO)
#घोषणा PCM027_ETH_IRQ_EDGE	IRQ_TYPE_EDGE_RISING
#घोषणा PCM027_ETH_PHYS		PXA_CS5_PHYS
#घोषणा PCM027_ETH_SIZE		(1*1024*1024)

/* CAN controller SJA1000 (unsupported yet) */
#घोषणा PCM027_CAN_IRQ_GPIO	114
#घोषणा PCM027_CAN_IRQ		PXA_GPIO_TO_IRQ(PCM027_CAN_IRQ_GPIO)
#घोषणा PCM027_CAN_IRQ_EDGE	IRQ_TYPE_EDGE_FALLING
#घोषणा PCM027_CAN_PHYS		0x22000000
#घोषणा PCM027_CAN_SIZE		0x100

/* SPI GPIO expander (unsupported yet) */
#घोषणा PCM027_EGPIO_IRQ_GPIO	27
#घोषणा PCM027_EGPIO_IRQ	PXA_GPIO_TO_IRQ(PCM027_EGPIO_IRQ_GPIO)
#घोषणा PCM027_EGPIO_IRQ_EDGE	IRQ_TYPE_EDGE_FALLING
#घोषणा PCM027_EGPIO_CS		24
/*
 * TODO: Switch this pin from dedicated usage to GPIO अगर
 * more than the MAX7301 device is connected to this SPI bus
 */
#घोषणा PCM027_EGPIO_CS_MODE	GPIO24_SFRM_MD

/* Flash memory */
#घोषणा PCM027_FLASH_PHYS	0x00000000
#घोषणा PCM027_FLASH_SIZE	0x02000000

/* onboard LEDs connected to GPIO */
#घोषणा PCM027_LED_CPU		90
#घोषणा PCM027_LED_HEARD_BEAT	91

/*
 * This CPU module needs a baseboard to work. After basic initializing
 * its own devices, it calls baseboard's init function.
 * TODO: Add your own basebaord init function and call it from
 * inside pcm027_init(). This example here is क्रम the developmen board.
 * Refer pcm990-baseboard.c
 */
बाह्य व्योम pcm990_baseboard_init(व्योम);
