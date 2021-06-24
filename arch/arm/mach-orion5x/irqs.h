<शैली गुरु>
/*
 * IRQ definitions क्रम Orion SoC
 *
 *  Maपूर्णांकainer: Tzachi Perelstein <tzachi@marvell.com>
 *
 *  This file is licensed under the terms of the GNU General Public
 *  License version 2. This program is licensed "as is" without any
 *  warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __ASM_ARCH_IRQS_H
#घोषणा __ASM_ARCH_IRQS_H

/*
 * Orion Main Interrupt Controller
 */
#घोषणा IRQ_ORION5X_BRIDGE		(1 + 0)
#घोषणा IRQ_ORION5X_DOORBELL_H2C	(1 + 1)
#घोषणा IRQ_ORION5X_DOORBELL_C2H	(1 + 2)
#घोषणा IRQ_ORION5X_UART0		(1 + 3)
#घोषणा IRQ_ORION5X_UART1		(1 + 4)
#घोषणा IRQ_ORION5X_I2C			(1 + 5)
#घोषणा IRQ_ORION5X_GPIO_0_7		(1 + 6)
#घोषणा IRQ_ORION5X_GPIO_8_15		(1 + 7)
#घोषणा IRQ_ORION5X_GPIO_16_23		(1 + 8)
#घोषणा IRQ_ORION5X_GPIO_24_31		(1 + 9)
#घोषणा IRQ_ORION5X_PCIE0_ERR		(1 + 10)
#घोषणा IRQ_ORION5X_PCIE0_INT		(1 + 11)
#घोषणा IRQ_ORION5X_USB1_CTRL		(1 + 12)
#घोषणा IRQ_ORION5X_DEV_BUS_ERR		(1 + 14)
#घोषणा IRQ_ORION5X_PCI_ERR		(1 + 15)
#घोषणा IRQ_ORION5X_USB_BR_ERR		(1 + 16)
#घोषणा IRQ_ORION5X_USB0_CTRL		(1 + 17)
#घोषणा IRQ_ORION5X_ETH_RX		(1 + 18)
#घोषणा IRQ_ORION5X_ETH_TX		(1 + 19)
#घोषणा IRQ_ORION5X_ETH_MISC		(1 + 20)
#घोषणा IRQ_ORION5X_ETH_SUM		(1 + 21)
#घोषणा IRQ_ORION5X_ETH_ERR		(1 + 22)
#घोषणा IRQ_ORION5X_IDMA_ERR		(1 + 23)
#घोषणा IRQ_ORION5X_IDMA_0		(1 + 24)
#घोषणा IRQ_ORION5X_IDMA_1		(1 + 25)
#घोषणा IRQ_ORION5X_IDMA_2		(1 + 26)
#घोषणा IRQ_ORION5X_IDMA_3		(1 + 27)
#घोषणा IRQ_ORION5X_CESA		(1 + 28)
#घोषणा IRQ_ORION5X_SATA		(1 + 29)
#घोषणा IRQ_ORION5X_XOR0		(1 + 30)
#घोषणा IRQ_ORION5X_XOR1		(1 + 31)

/*
 * Orion General Purpose Pins
 */
#घोषणा IRQ_ORION5X_GPIO_START	33
#घोषणा NR_GPIO_IRQS		32

#घोषणा ORION5X_NR_IRQS		(IRQ_ORION5X_GPIO_START + NR_GPIO_IRQS)


#पूर्ण_अगर
