<शैली गुरु>
/*
 * IRQ definitions क्रम Marvell MV78xx0 SoCs
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __ASM_ARCH_IRQS_H
#घोषणा __ASM_ARCH_IRQS_H

/*
 * MV78xx0 Low Interrupt Controller
 */
#घोषणा IRQ_MV78XX0_ERR		0
#घोषणा IRQ_MV78XX0_SPI		1
#घोषणा IRQ_MV78XX0_I2C_0	2
#घोषणा IRQ_MV78XX0_I2C_1	3
#घोषणा IRQ_MV78XX0_IDMA_0	4
#घोषणा IRQ_MV78XX0_IDMA_1	5
#घोषणा IRQ_MV78XX0_IDMA_2	6
#घोषणा IRQ_MV78XX0_IDMA_3	7
#घोषणा IRQ_MV78XX0_TIMER_0	8
#घोषणा IRQ_MV78XX0_TIMER_1	9
#घोषणा IRQ_MV78XX0_TIMER_2	10
#घोषणा IRQ_MV78XX0_TIMER_3	11
#घोषणा IRQ_MV78XX0_UART_0	12
#घोषणा IRQ_MV78XX0_UART_1	13
#घोषणा IRQ_MV78XX0_UART_2	14
#घोषणा IRQ_MV78XX0_UART_3	15
#घोषणा IRQ_MV78XX0_USB_0	16
#घोषणा IRQ_MV78XX0_USB_1	17
#घोषणा IRQ_MV78XX0_USB_2	18
#घोषणा IRQ_MV78XX0_CRYPTO	19
#घोषणा IRQ_MV78XX0_SDIO_0	20
#घोषणा IRQ_MV78XX0_SDIO_1	21
#घोषणा IRQ_MV78XX0_XOR_0	22
#घोषणा IRQ_MV78XX0_XOR_1	23
#घोषणा IRQ_MV78XX0_I2S_0	24
#घोषणा IRQ_MV78XX0_I2S_1	25
#घोषणा IRQ_MV78XX0_SATA	26
#घोषणा IRQ_MV78XX0_TDMI	27

/*
 * MV78xx0 High Interrupt Controller
 */
#घोषणा IRQ_MV78XX0_PCIE_00	32
#घोषणा IRQ_MV78XX0_PCIE_01	33
#घोषणा IRQ_MV78XX0_PCIE_02	34
#घोषणा IRQ_MV78XX0_PCIE_03	35
#घोषणा IRQ_MV78XX0_PCIE_10	36
#घोषणा IRQ_MV78XX0_PCIE_11	37
#घोषणा IRQ_MV78XX0_PCIE_12	38
#घोषणा IRQ_MV78XX0_PCIE_13	39
#घोषणा IRQ_MV78XX0_GE00_SUM	40
#घोषणा IRQ_MV78XX0_GE00_RX	41
#घोषणा IRQ_MV78XX0_GE00_TX	42
#घोषणा IRQ_MV78XX0_GE00_MISC	43
#घोषणा IRQ_MV78XX0_GE01_SUM	44
#घोषणा IRQ_MV78XX0_GE01_RX	45
#घोषणा IRQ_MV78XX0_GE01_TX	46
#घोषणा IRQ_MV78XX0_GE01_MISC	47
#घोषणा IRQ_MV78XX0_GE10_SUM	48
#घोषणा IRQ_MV78XX0_GE10_RX	49
#घोषणा IRQ_MV78XX0_GE10_TX	50
#घोषणा IRQ_MV78XX0_GE10_MISC	51
#घोषणा IRQ_MV78XX0_GE11_SUM	52
#घोषणा IRQ_MV78XX0_GE11_RX	53
#घोषणा IRQ_MV78XX0_GE11_TX	54
#घोषणा IRQ_MV78XX0_GE11_MISC	55
#घोषणा IRQ_MV78XX0_GPIO_0_7	56
#घोषणा IRQ_MV78XX0_GPIO_8_15	57
#घोषणा IRQ_MV78XX0_GPIO_16_23	58
#घोषणा IRQ_MV78XX0_GPIO_24_31	59
#घोषणा IRQ_MV78XX0_DB_IN	60
#घोषणा IRQ_MV78XX0_DB_OUT	61

/*
 * MV78xx0 Error Interrupt Controller
 */
#घोषणा IRQ_MV78XX0_GE_ERR	70

/*
 * MV78XX0 General Purpose Pins
 */
#घोषणा IRQ_MV78XX0_GPIO_START	96
#घोषणा NR_GPIO_IRQS		32

#घोषणा MV78XX0_NR_IRQS		(IRQ_MV78XX0_GPIO_START + NR_GPIO_IRQS)


#पूर्ण_अगर
