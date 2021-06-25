<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * timberdale.h timberdale FPGA MFD driver defines
 * Copyright (c) 2009 Intel Corporation
 */

/* Supports:
 * Timberdale FPGA
 */

#अगर_अघोषित MFD_TIMBERDALE_H
#घोषणा MFD_TIMBERDALE_H

#घोषणा DRV_VERSION		"0.3"

/* This driver only support versions >= 3.8 and < 4.0  */
#घोषणा TIMB_SUPPORTED_MAJOR	3

/* This driver only support minor >= 8 */
#घोषणा TIMB_REQUIRED_MINOR	8

/* Registers of the control area */
#घोषणा TIMB_REV_MAJOR	0x00
#घोषणा TIMB_REV_MINOR	0x04
#घोषणा TIMB_HW_CONFIG	0x08
#घोषणा TIMB_SW_RST	0x40

/* bits in the TIMB_HW_CONFIG रेजिस्टर */
#घोषणा TIMB_HW_CONFIG_SPI_8BIT	0x80

#घोषणा TIMB_HW_VER_MASK	0x0f
#घोषणा TIMB_HW_VER0		0x00
#घोषणा TIMB_HW_VER1		0x01
#घोषणा TIMB_HW_VER2		0x02
#घोषणा TIMB_HW_VER3		0x03

#घोषणा OCORESOFFSET	0x0
#घोषणा OCORESEND	0x1f

#घोषणा SPIOFFSET	0x80
#घोषणा SPIEND		0xff

#घोषणा UARTLITखातापूर्णFSET	0x100
#घोषणा UARTLITEEND	0x10f

#घोषणा RDSOFFSET	0x180
#घोषणा RDSEND		0x183

#घोषणा ETHOFFSET	0x300
#घोषणा ETHEND		0x3ff

#घोषणा GPIOOFFSET	0x400
#घोषणा GPIOEND		0x7ff

#घोषणा CHIPCTLOFFSET	0x800
#घोषणा CHIPCTLEND	0x8ff
#घोषणा CHIPCTLSIZE	(CHIPCTLEND - CHIPCTLOFFSET + 1)

#घोषणा INTCOFFSET	0xc00
#घोषणा INTCEND		0xfff
#घोषणा INTCSIZE	(INTCEND - INTCOFFSET)

#घोषणा MOSTOFFSET	0x1000
#घोषणा MOSTEND		0x13ff

#घोषणा UARTOFFSET	0x1400
#घोषणा UARTEND		0x17ff

#घोषणा XIICOFFSET	0x1800
#घोषणा XIICEND		0x19ff

#घोषणा I2SOFFSET	0x1C00
#घोषणा I2SEND		0x1fff

#घोषणा LOGIWOFFSET	0x30000
#घोषणा LOGIWEND	0x37fff

#घोषणा MLCORखातापूर्णFSET	0x40000
#घोषणा MLCOREEND	0x43fff

#घोषणा DMAOFFSET	0x01000000
#घोषणा DMAEND		0x013fffff

/* SDHC0 is placed in PCI bar 1 */
#घोषणा SDHC0OFFSET	0x00
#घोषणा SDHC0END	0xff

/* SDHC1 is placed in PCI bar 2 */
#घोषणा SDHC1OFFSET	0x00
#घोषणा SDHC1END	0xff

#घोषणा PCI_VENDOR_ID_TIMB	0x10ee
#घोषणा PCI_DEVICE_ID_TIMB	0xa123

#घोषणा IRQ_TIMBERDALE_INIC		0
#घोषणा IRQ_TIMBERDALE_MLB		1
#घोषणा IRQ_TIMBERDALE_GPIO		2
#घोषणा IRQ_TIMBERDALE_I2C		3
#घोषणा IRQ_TIMBERDALE_UART		4
#घोषणा IRQ_TIMBERDALE_DMA		5
#घोषणा IRQ_TIMBERDALE_I2S		6
#घोषणा IRQ_TIMBERDALE_TSC_INT		7
#घोषणा IRQ_TIMBERDALE_SDHC		8
#घोषणा IRQ_TIMBERDALE_ADV7180		9
#घोषणा IRQ_TIMBERDALE_ETHSW_IF		10
#घोषणा IRQ_TIMBERDALE_SPI		11
#घोषणा IRQ_TIMBERDALE_UARTLITE		12
#घोषणा IRQ_TIMBERDALE_MLCORE		13
#घोषणा IRQ_TIMBERDALE_MLCORE_BUF	14
#घोषणा IRQ_TIMBERDALE_RDS		15
#घोषणा TIMBERDALE_NR_IRQS		16

#घोषणा GPIO_PIN_ASCB		8
#घोषणा GPIO_PIN_INIC_RST	14
#घोषणा GPIO_PIN_BT_RST		15
#घोषणा GPIO_NR_PINS		16

/* DMA Channels */
#घोषणा DMA_UART_RX         0
#घोषणा DMA_UART_TX         1
#घोषणा DMA_MLB_RX          2
#घोषणा DMA_MLB_TX          3
#घोषणा DMA_VIDEO_RX        4
#घोषणा DMA_VIDEO_DROP      5
#घोषणा DMA_SDHCI_RX        6
#घोषणा DMA_SDHCI_TX        7
#घोषणा DMA_ETH_RX          8
#घोषणा DMA_ETH_TX          9

#पूर्ण_अगर
