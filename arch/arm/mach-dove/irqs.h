<शैली गुरु>
/*
 * IRQ definitions क्रम Marvell Dove 88AP510 SoC
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __ASM_ARCH_IRQS_H
#घोषणा __ASM_ARCH_IRQS_H

/*
 * Dove Low Interrupt Controller
 */
#घोषणा IRQ_DOVE_BRIDGE		(1 + 0)
#घोषणा IRQ_DOVE_H2C		(1 + 1)
#घोषणा IRQ_DOVE_C2H		(1 + 2)
#घोषणा IRQ_DOVE_न_अंकD		(1 + 3)
#घोषणा IRQ_DOVE_PDMA		(1 + 4)
#घोषणा IRQ_DOVE_SPI1		(1 + 5)
#घोषणा IRQ_DOVE_SPI0		(1 + 6)
#घोषणा IRQ_DOVE_UART_0		(1 + 7)
#घोषणा IRQ_DOVE_UART_1		(1 + 8)
#घोषणा IRQ_DOVE_UART_2		(1 + 9)
#घोषणा IRQ_DOVE_UART_3		(1 + 10)
#घोषणा IRQ_DOVE_I2C		(1 + 11)
#घोषणा IRQ_DOVE_GPIO_0_7	(1 + 12)
#घोषणा IRQ_DOVE_GPIO_8_15	(1 + 13)
#घोषणा IRQ_DOVE_GPIO_16_23	(1 + 14)
#घोषणा IRQ_DOVE_PCIE0_ERR	(1 + 15)
#घोषणा IRQ_DOVE_PCIE0		(1 + 16)
#घोषणा IRQ_DOVE_PCIE1_ERR	(1 + 17)
#घोषणा IRQ_DOVE_PCIE1		(1 + 18)
#घोषणा IRQ_DOVE_I2S0		(1 + 19)
#घोषणा IRQ_DOVE_I2S0_ERR	(1 + 20)
#घोषणा IRQ_DOVE_I2S1		(1 + 21)
#घोषणा IRQ_DOVE_I2S1_ERR	(1 + 22)
#घोषणा IRQ_DOVE_USB_ERR	(1 + 23)
#घोषणा IRQ_DOVE_USB0		(1 + 24)
#घोषणा IRQ_DOVE_USB1		(1 + 25)
#घोषणा IRQ_DOVE_GE00_RX	(1 + 26)
#घोषणा IRQ_DOVE_GE00_TX	(1 + 27)
#घोषणा IRQ_DOVE_GE00_MISC	(1 + 28)
#घोषणा IRQ_DOVE_GE00_SUM	(1 + 29)
#घोषणा IRQ_DOVE_GE00_ERR	(1 + 30)
#घोषणा IRQ_DOVE_CRYPTO		(1 + 31)

/*
 * Dove High Interrupt Controller
 */
#घोषणा IRQ_DOVE_AC97		(1 + 32)
#घोषणा IRQ_DOVE_PMU		(1 + 33)
#घोषणा IRQ_DOVE_CAM		(1 + 34)
#घोषणा IRQ_DOVE_SDIO0		(1 + 35)
#घोषणा IRQ_DOVE_SDIO1		(1 + 36)
#घोषणा IRQ_DOVE_SDIO0_WAKEUP	(1 + 37)
#घोषणा IRQ_DOVE_SDIO1_WAKEUP	(1 + 38)
#घोषणा IRQ_DOVE_XOR_00		(1 + 39)
#घोषणा IRQ_DOVE_XOR_01		(1 + 40)
#घोषणा IRQ_DOVE_XOR0_ERR	(1 + 41)
#घोषणा IRQ_DOVE_XOR_10		(1 + 42)
#घोषणा IRQ_DOVE_XOR_11		(1 + 43)
#घोषणा IRQ_DOVE_XOR1_ERR	(1 + 44)
#घोषणा IRQ_DOVE_LCD_DCON	(1 + 45)
#घोषणा IRQ_DOVE_LCD1		(1 + 46)
#घोषणा IRQ_DOVE_LCD0		(1 + 47)
#घोषणा IRQ_DOVE_GPU		(1 + 48)
#घोषणा IRQ_DOVE_PERFORM_MNTR	(1 + 49)
#घोषणा IRQ_DOVE_VPRO_DMA1	(1 + 51)
#घोषणा IRQ_DOVE_SSP_TIMER	(1 + 54)
#घोषणा IRQ_DOVE_SSP		(1 + 55)
#घोषणा IRQ_DOVE_MC_L2_ERR	(1 + 56)
#घोषणा IRQ_DOVE_CRYPTO_ERR	(1 + 59)
#घोषणा IRQ_DOVE_GPIO_24_31	(1 + 60)
#घोषणा IRQ_DOVE_HIGH_GPIO	(1 + 61)
#घोषणा IRQ_DOVE_SATA		(1 + 62)

/*
 * DOVE General Purpose Pins
 */
#घोषणा IRQ_DOVE_GPIO_START	65
#घोषणा NR_GPIO_IRQS		64

/*
 * PMU पूर्णांकerrupts
 */
#घोषणा IRQ_DOVE_PMU_START	(IRQ_DOVE_GPIO_START + NR_GPIO_IRQS)
#घोषणा NR_PMU_IRQS		7
#घोषणा IRQ_DOVE_RTC		(IRQ_DOVE_PMU_START + 5)

#घोषणा DOVE_NR_IRQS		(IRQ_DOVE_PMU_START + NR_PMU_IRQS)


#पूर्ण_अगर
