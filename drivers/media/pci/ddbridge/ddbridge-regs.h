<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ddbridge-regs.h: Digital Devices PCIe bridge driver
 *
 * Copyright (C) 2010-2017 Digital Devices GmbH
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2 only, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित __DDBRIDGE_REGS_H__
#घोषणा __DDBRIDGE_REGS_H__

/* ------------------------------------------------------------------------- */
/* SPI Controller */

#घोषणा SPI_CONTROL     0x10
#घोषणा SPI_DATA        0x14

/* ------------------------------------------------------------------------- */
/* GPIO */

#घोषणा GPIO_OUTPUT      0x20
#घोषणा GPIO_INPUT       0x24
#घोषणा GPIO_सूचीECTION   0x28

/* ------------------------------------------------------------------------- */

#घोषणा BOARD_CONTROL    0x30

/* ------------------------------------------------------------------------- */

/* Interrupt controller
 * How many MSI's are available depends on HW (Min 2 max 8)
 * How many are usable also depends on Host platक्रमm
 */

#घोषणा INTERRUPT_BASE   (0x40)

#घोषणा INTERRUPT_ENABLE (INTERRUPT_BASE + 0x00)
#घोषणा MSI1_ENABLE      (INTERRUPT_BASE + 0x04)
#घोषणा MSI2_ENABLE      (INTERRUPT_BASE + 0x08)
#घोषणा MSI3_ENABLE      (INTERRUPT_BASE + 0x0C)
#घोषणा MSI4_ENABLE      (INTERRUPT_BASE + 0x10)
#घोषणा MSI5_ENABLE      (INTERRUPT_BASE + 0x14)
#घोषणा MSI6_ENABLE      (INTERRUPT_BASE + 0x18)
#घोषणा MSI7_ENABLE      (INTERRUPT_BASE + 0x1C)

#घोषणा INTERRUPT_STATUS (INTERRUPT_BASE + 0x20)
#घोषणा INTERRUPT_ACK    (INTERRUPT_BASE + 0x20)

/* Temperature Monitor ( 2x LM75A @ 0x90,0x92 I2c ) */
#घोषणा TEMPMON_BASE			(0x1c0)
#घोषणा TEMPMON_CONTROL			(TEMPMON_BASE + 0x00)

#घोषणा TEMPMON_CONTROL_AUTOSCAN	(0x00000002)
#घोषणा TEMPMON_CONTROL_INTENABLE	(0x00000004)
#घोषणा TEMPMON_CONTROL_OVERTEMP	(0x00008000)

/* SHORT Temperature in Celsius x 256 */
#घोषणा TEMPMON_SENSOR0			(TEMPMON_BASE + 0x04)
#घोषणा TEMPMON_SENSOR1			(TEMPMON_BASE + 0x08)

#घोषणा TEMPMON_FANCONTROL		(TEMPMON_BASE + 0x10)

/* ------------------------------------------------------------------------- */
/* I2C Master Controller */

#घोषणा I2C_COMMAND     (0x00)
#घोषणा I2C_TIMING      (0x04)
#घोषणा I2C_TASKLENGTH  (0x08)     /* High पढ़ो, low ग_लिखो */
#घोषणा I2C_TASKADDRESS (0x0C)     /* High पढ़ो, low ग_लिखो */
#घोषणा I2C_MONITOR     (0x1C)

#घोषणा I2C_SPEED_400   (0x04030404)
#घोषणा I2C_SPEED_100   (0x13121313)

/* ------------------------------------------------------------------------- */
/* DMA  Controller */

#घोषणा DMA_BASE_WRITE        (0x100)
#घोषणा DMA_BASE_READ         (0x140)

#घोषणा TS_CONTROL(_io)         ((_io)->regs + 0x00)
#घोषणा TS_CONTROL2(_io)        ((_io)->regs + 0x04)

/* ------------------------------------------------------------------------- */
/* DMA  Buffer */

#घोषणा DMA_BUFFER_CONTROL(_dma)       ((_dma)->regs + 0x00)
#घोषणा DMA_BUFFER_ACK(_dma)           ((_dma)->regs + 0x04)
#घोषणा DMA_BUFFER_CURRENT(_dma)       ((_dma)->regs + 0x08)
#घोषणा DMA_BUFFER_SIZE(_dma)          ((_dma)->regs + 0x0c)

/* ------------------------------------------------------------------------- */
/* CI Interface (only CI-Bridge) */

#घोषणा CI_BASE                         (0x400)
#घोषणा CI_CONTROL(i)                   (CI_BASE + (i) * 32 + 0x00)

#घोषणा CI_DO_ATTRIBUTE_RW(i)           (CI_BASE + (i) * 32 + 0x04)
#घोषणा CI_DO_IO_RW(i)                  (CI_BASE + (i) * 32 + 0x08)
#घोषणा CI_READDATA(i)                  (CI_BASE + (i) * 32 + 0x0c)
#घोषणा CI_DO_READ_ATTRIBUTES(i)        (CI_BASE + (i) * 32 + 0x10)

#घोषणा CI_RESET_CAM                    (0x00000001)
#घोषणा CI_POWER_ON                     (0x00000002)
#घोषणा CI_ENABLE                       (0x00000004)
#घोषणा CI_BYPASS_DISABLE               (0x00000010)

#घोषणा CI_CAM_READY                    (0x00010000)
#घोषणा CI_CAM_DETECT                   (0x00020000)
#घोषणा CI_READY                        (0x80000000)

#घोषणा CI_READ_CMD                     (0x40000000)
#घोषणा CI_WRITE_CMD                    (0x80000000)

#घोषणा CI_BUFFER_BASE                  (0x3000)
#घोषणा CI_BUFFER_SIZE                  (0x0800)

#घोषणा CI_BUFFER(i)                    (CI_BUFFER_BASE + (i) * CI_BUFFER_SIZE)

/* ------------------------------------------------------------------------- */
/* LNB commands (mxl5xx / Max S8) */

#घोषणा LNB_BASE			(0x400)
#घोषणा LNB_CONTROL(i)			(LNB_BASE + (i) * 0x20 + 0x00)

#घोषणा LNB_CMD				(7ULL << 0)
#घोषणा LNB_CMD_NOP			0
#घोषणा LNB_CMD_INIT			1
#घोषणा LNB_CMD_LOW			3
#घोषणा LNB_CMD_HIGH			4
#घोषणा LNB_CMD_OFF			5
#घोषणा LNB_CMD_DISEQC			6

#घोषणा LNB_BUSY			BIT_ULL(4)
#घोषणा LNB_TONE			BIT_ULL(15)

#घोषणा LNB_BUF_LEVEL(i)		(LNB_BASE + (i) * 0x20 + 0x10)
#घोषणा LNB_BUF_WRITE(i)		(LNB_BASE + (i) * 0x20 + 0x14)

#पूर्ण_अगर /* __DDBRIDGE_REGS_H__ */
