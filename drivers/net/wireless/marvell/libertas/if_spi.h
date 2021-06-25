<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	linux/drivers/net/wireless/libertas/अगर_spi.c
 *
 *	Driver क्रम Marvell SPI WLAN cards.
 *
 *	Copyright 2008 Analog Devices Inc.
 *
 *	Authors:
 *	Andrey Yurovsky <andrey@cozybit.com>
 *	Colin McCabe <colin@cozybit.com>
 */

#अगर_अघोषित _LBS_IF_SPI_H_
#घोषणा _LBS_IF_SPI_H_

#घोषणा IPFIELD_ALIGN_OFFSET 2
#घोषणा IF_SPI_CMD_BUF_SIZE 2400

/***************** Firmware *****************/

#घोषणा IF_SPI_FW_NAME_MAX 30

#घोषणा MAX_MAIN_FW_LOAD_CRC_ERR 10

/* Chunk size when loading the helper firmware */
#घोषणा HELPER_FW_LOAD_CHUNK_SZ 64

/* Value to ग_लिखो to indicate end of helper firmware dnld */
#घोषणा FIRMWARE_DNLD_OK 0x0000

/* Value to check once the मुख्य firmware is करोwnloaded */
#घोषणा SUCCESSFUL_FW_DOWNLOAD_MAGIC 0x88888888

/***************** SPI Interface Unit *****************/
/* Masks used in SPI रेजिस्टर पढ़ो/ग_लिखो operations */
#घोषणा IF_SPI_READ_OPERATION_MASK 0x0
#घोषणा IF_SPI_WRITE_OPERATION_MASK 0x8000

/* SPI रेजिस्टर offsets. 4-byte aligned. */
#घोषणा IF_SPI_DEVICEID_CTRL_REG 0x00	/* DeviceID controller reg */
#घोषणा IF_SPI_IO_READBASE_REG 0x04 	/* Read I/O base reg */
#घोषणा IF_SPI_IO_WRITEBASE_REG 0x08	/* Write I/O base reg */
#घोषणा IF_SPI_IO_RDWRPORT_REG 0x0C	/* Read/Write I/O port reg */

#घोषणा IF_SPI_CMD_READBASE_REG 0x10	/* Read command base reg */
#घोषणा IF_SPI_CMD_WRITEBASE_REG 0x14	/* Write command base reg */
#घोषणा IF_SPI_CMD_RDWRPORT_REG 0x18	/* Read/Write command port reg */

#घोषणा IF_SPI_DATA_READBASE_REG 0x1C	/* Read data base reg */
#घोषणा IF_SPI_DATA_WRITEBASE_REG 0x20	/* Write data base reg */
#घोषणा IF_SPI_DATA_RDWRPORT_REG 0x24	/* Read/Write data port reg */

#घोषणा IF_SPI_SCRATCH_1_REG 0x28	/* Scratch reg 1 */
#घोषणा IF_SPI_SCRATCH_2_REG 0x2C	/* Scratch reg 2 */
#घोषणा IF_SPI_SCRATCH_3_REG 0x30	/* Scratch reg 3 */
#घोषणा IF_SPI_SCRATCH_4_REG 0x34	/* Scratch reg 4 */

#घोषणा IF_SPI_TX_FRAME_SEQ_NUM_REG 0x38 /* Tx frame sequence number reg */
#घोषणा IF_SPI_TX_FRAME_STATUS_REG 0x3C	/* Tx frame status reg */

#घोषणा IF_SPI_HOST_INT_CTRL_REG 0x40	/* Host पूर्णांकerrupt controller reg */

#घोषणा IF_SPI_CARD_INT_CAUSE_REG 0x44	/* Card पूर्णांकerrupt cause reg */
#घोषणा IF_SPI_CARD_INT_STATUS_REG 0x48 /* Card पूर्णांकerrupt status reg */
#घोषणा IF_SPI_CARD_INT_EVENT_MASK_REG 0x4C /* Card पूर्णांकerrupt event mask */
#घोषणा IF_SPI_CARD_INT_STATUS_MASK_REG	0x50 /* Card पूर्णांकerrupt status mask */

#घोषणा IF_SPI_CARD_INT_RESET_SELECT_REG 0x54 /* Card पूर्णांकerrupt reset select */

#घोषणा IF_SPI_HOST_INT_CAUSE_REG 0x58	/* Host पूर्णांकerrupt cause reg */
#घोषणा IF_SPI_HOST_INT_STATUS_REG 0x5C	/* Host पूर्णांकerrupt status reg */
#घोषणा IF_SPI_HOST_INT_EVENT_MASK_REG 0x60 /* Host पूर्णांकerrupt event mask */
#घोषणा IF_SPI_HOST_INT_STATUS_MASK_REG	0x64 /* Host पूर्णांकerrupt status mask */
#घोषणा IF_SPI_HOST_INT_RESET_SELECT_REG 0x68 /* Host पूर्णांकerrupt reset select */

#घोषणा IF_SPI_DELAY_READ_REG 0x6C	/* Delay पढ़ो reg */
#घोषणा IF_SPI_SPU_BUS_MODE_REG 0x70	/* SPU BUS mode reg */

/***************** IF_SPI_DEVICEID_CTRL_REG *****************/
#घोषणा IF_SPI_DEVICEID_CTRL_REG_TO_CARD_ID(dc) ((dc & 0xffff0000)>>16)
#घोषणा IF_SPI_DEVICEID_CTRL_REG_TO_CARD_REV(dc) (dc & 0x000000ff)

/***************** IF_SPI_HOST_INT_CTRL_REG *****************/
/* Host Interrupt Control bit : Wake up */
#घोषणा IF_SPI_HICT_WAKE_UP				(1<<0)
/* Host Interrupt Control bit : WLAN पढ़ोy */
#घोषणा IF_SPI_HICT_WLAN_READY				(1<<1)
/*#घोषणा IF_SPI_HICT_FIFO_FIRST_HALF_EMPTY		(1<<2) */
/*#घोषणा IF_SPI_HICT_FIFO_SECOND_HALF_EMPTY		(1<<3) */
/*#घोषणा IF_SPI_HICT_IRQSRC_WLAN			(1<<4) */
/* Host Interrupt Control bit : Tx स्वतः करोwnload */
#घोषणा IF_SPI_HICT_TX_DOWNLOAD_OVER_AUTO		(1<<5)
/* Host Interrupt Control bit : Rx स्वतः upload */
#घोषणा IF_SPI_HICT_RX_UPLOAD_OVER_AUTO			(1<<6)
/* Host Interrupt Control bit : Command स्वतः करोwnload */
#घोषणा IF_SPI_HICT_CMD_DOWNLOAD_OVER_AUTO		(1<<7)
/* Host Interrupt Control bit : Command स्वतः upload */
#घोषणा IF_SPI_HICT_CMD_UPLOAD_OVER_AUTO		(1<<8)

/***************** IF_SPI_CARD_INT_CAUSE_REG *****************/
/* Card Interrupt Case bit : Tx करोwnload over */
#घोषणा IF_SPI_CIC_TX_DOWNLOAD_OVER			(1<<0)
/* Card Interrupt Case bit : Rx upload over */
#घोषणा IF_SPI_CIC_RX_UPLOAD_OVER			(1<<1)
/* Card Interrupt Case bit : Command करोwnload over */
#घोषणा IF_SPI_CIC_CMD_DOWNLOAD_OVER			(1<<2)
/* Card Interrupt Case bit : Host event */
#घोषणा IF_SPI_CIC_HOST_EVENT				(1<<3)
/* Card Interrupt Case bit : Command upload over */
#घोषणा IF_SPI_CIC_CMD_UPLOAD_OVER			(1<<4)
/* Card Interrupt Case bit : Power करोwn */
#घोषणा IF_SPI_CIC_POWER_DOWN				(1<<5)

/***************** IF_SPI_CARD_INT_STATUS_REG *****************/
#घोषणा IF_SPI_CIS_TX_DOWNLOAD_OVER			(1<<0)
#घोषणा IF_SPI_CIS_RX_UPLOAD_OVER			(1<<1)
#घोषणा IF_SPI_CIS_CMD_DOWNLOAD_OVER			(1<<2)
#घोषणा IF_SPI_CIS_HOST_EVENT				(1<<3)
#घोषणा IF_SPI_CIS_CMD_UPLOAD_OVER			(1<<4)
#घोषणा IF_SPI_CIS_POWER_DOWN				(1<<5)

/***************** IF_SPI_HOST_INT_CAUSE_REG *****************/
#घोषणा IF_SPI_HICU_TX_DOWNLOAD_RDY			(1<<0)
#घोषणा IF_SPI_HICU_RX_UPLOAD_RDY			(1<<1)
#घोषणा IF_SPI_HICU_CMD_DOWNLOAD_RDY			(1<<2)
#घोषणा IF_SPI_HICU_CARD_EVENT				(1<<3)
#घोषणा IF_SPI_HICU_CMD_UPLOAD_RDY			(1<<4)
#घोषणा IF_SPI_HICU_IO_WR_FIFO_OVERFLOW			(1<<5)
#घोषणा IF_SPI_HICU_IO_RD_FIFO_UNDERFLOW		(1<<6)
#घोषणा IF_SPI_HICU_DATA_WR_FIFO_OVERFLOW		(1<<7)
#घोषणा IF_SPI_HICU_DATA_RD_FIFO_UNDERFLOW		(1<<8)
#घोषणा IF_SPI_HICU_CMD_WR_FIFO_OVERFLOW		(1<<9)
#घोषणा IF_SPI_HICU_CMD_RD_FIFO_UNDERFLOW		(1<<10)

/***************** IF_SPI_HOST_INT_STATUS_REG *****************/
/* Host Interrupt Status bit : Tx करोwnload पढ़ोy */
#घोषणा IF_SPI_HIST_TX_DOWNLOAD_RDY			(1<<0)
/* Host Interrupt Status bit : Rx upload पढ़ोy */
#घोषणा IF_SPI_HIST_RX_UPLOAD_RDY			(1<<1)
/* Host Interrupt Status bit : Command करोwnload पढ़ोy */
#घोषणा IF_SPI_HIST_CMD_DOWNLOAD_RDY			(1<<2)
/* Host Interrupt Status bit : Card event */
#घोषणा IF_SPI_HIST_CARD_EVENT				(1<<3)
/* Host Interrupt Status bit : Command upload पढ़ोy */
#घोषणा IF_SPI_HIST_CMD_UPLOAD_RDY			(1<<4)
/* Host Interrupt Status bit : I/O ग_लिखो FIFO overflow */
#घोषणा IF_SPI_HIST_IO_WR_FIFO_OVERFLOW			(1<<5)
/* Host Interrupt Status bit : I/O पढ़ो FIFO underflow */
#घोषणा IF_SPI_HIST_IO_RD_FIFO_UNDRFLOW			(1<<6)
/* Host Interrupt Status bit : Data ग_लिखो FIFO overflow */
#घोषणा IF_SPI_HIST_DATA_WR_FIFO_OVERFLOW		(1<<7)
/* Host Interrupt Status bit : Data पढ़ो FIFO underflow */
#घोषणा IF_SPI_HIST_DATA_RD_FIFO_UNDERFLOW		(1<<8)
/* Host Interrupt Status bit : Command ग_लिखो FIFO overflow */
#घोषणा IF_SPI_HIST_CMD_WR_FIFO_OVERFLOW		(1<<9)
/* Host Interrupt Status bit : Command पढ़ो FIFO underflow */
#घोषणा IF_SPI_HIST_CMD_RD_FIFO_UNDERFLOW		(1<<10)

/***************** IF_SPI_HOST_INT_STATUS_MASK_REG *****************/
/* Host Interrupt Status Mask bit : Tx करोwnload पढ़ोy */
#घोषणा IF_SPI_HISM_TX_DOWNLOAD_RDY			(1<<0)
/* Host Interrupt Status Mask bit : Rx upload पढ़ोy */
#घोषणा IF_SPI_HISM_RX_UPLOAD_RDY			(1<<1)
/* Host Interrupt Status Mask bit : Command करोwnload पढ़ोy */
#घोषणा IF_SPI_HISM_CMD_DOWNLOAD_RDY			(1<<2)
/* Host Interrupt Status Mask bit : Card event */
#घोषणा IF_SPI_HISM_CARDEVENT				(1<<3)
/* Host Interrupt Status Mask bit : Command upload पढ़ोy */
#घोषणा IF_SPI_HISM_CMD_UPLOAD_RDY			(1<<4)
/* Host Interrupt Status Mask bit : I/O ग_लिखो FIFO overflow */
#घोषणा IF_SPI_HISM_IO_WR_FIFO_OVERFLOW			(1<<5)
/* Host Interrupt Status Mask bit : I/O पढ़ो FIFO underflow */
#घोषणा IF_SPI_HISM_IO_RD_FIFO_UNDERFLOW		(1<<6)
/* Host Interrupt Status Mask bit : Data ग_लिखो FIFO overflow */
#घोषणा IF_SPI_HISM_DATA_WR_FIFO_OVERFLOW		(1<<7)
/* Host Interrupt Status Mask bit : Data ग_लिखो FIFO underflow */
#घोषणा IF_SPI_HISM_DATA_RD_FIFO_UNDERFLOW		(1<<8)
/* Host Interrupt Status Mask bit : Command ग_लिखो FIFO overflow */
#घोषणा IF_SPI_HISM_CMD_WR_FIFO_OVERFLOW		(1<<9)
/* Host Interrupt Status Mask bit : Command ग_लिखो FIFO underflow */
#घोषणा IF_SPI_HISM_CMD_RD_FIFO_UNDERFLOW		(1<<10)

/***************** IF_SPI_SPU_BUS_MODE_REG *****************/
/* SCK edge on which the WLAN module outमाला_दो data on MISO */
#घोषणा IF_SPI_BUS_MODE_SPI_CLOCK_PHASE_FALLING 0x8
#घोषणा IF_SPI_BUS_MODE_SPI_CLOCK_PHASE_RISING 0x0

/* In a SPU पढ़ो operation, there is a delay between writing the SPU
 * रेजिस्टर name and getting back data from the WLAN module.
 * This can be specअगरied in terms of nanoseconds or in terms of dummy
 * घड़ी cycles which the master must output beक्रमe receiving a response. */
#घोषणा IF_SPI_BUS_MODE_DELAY_METHOD_DUMMY_CLOCK 0x4
#घोषणा IF_SPI_BUS_MODE_DELAY_METHOD_TIMED 0x0

/* Some dअगरferent modes of SPI operation */
#घोषणा IF_SPI_BUS_MODE_8_BIT_ADDRESS_16_BIT_DATA 0x00
#घोषणा IF_SPI_BUS_MODE_8_BIT_ADDRESS_32_BIT_DATA 0x01
#घोषणा IF_SPI_BUS_MODE_16_BIT_ADDRESS_16_BIT_DATA 0x02
#घोषणा IF_SPI_BUS_MODE_16_BIT_ADDRESS_32_BIT_DATA 0x03

#पूर्ण_अगर
