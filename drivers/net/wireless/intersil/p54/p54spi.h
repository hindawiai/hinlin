<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2008 Christian Lamparter <chunkeey@web.de>
 *
 * This driver is a port from stlc45xx:
 *	Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
 */

#अगर_अघोषित P54SPI_H
#घोषणा P54SPI_H

#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <net/mac80211.h>

#समावेश "p54.h"

/* Bit 15 is पढ़ो/ग_लिखो bit; ON = READ, OFF = WRITE */
#घोषणा SPI_ADRS_READ_BIT_15		0x8000

#घोषणा SPI_ADRS_ARM_INTERRUPTS		0x00
#घोषणा SPI_ADRS_ARM_INT_EN		0x04

#घोषणा SPI_ADRS_HOST_INTERRUPTS	0x08
#घोषणा SPI_ADRS_HOST_INT_EN		0x0c
#घोषणा SPI_ADRS_HOST_INT_ACK		0x10

#घोषणा SPI_ADRS_GEN_PURP_1		0x14
#घोषणा SPI_ADRS_GEN_PURP_2		0x18

#घोषणा SPI_ADRS_DEV_CTRL_STAT		0x26    /* high word */

#घोषणा SPI_ADRS_DMA_DATA		0x28

#घोषणा SPI_ADRS_DMA_WRITE_CTRL		0x2c
#घोषणा SPI_ADRS_DMA_WRITE_LEN		0x2e
#घोषणा SPI_ADRS_DMA_WRITE_BASE		0x30

#घोषणा SPI_ADRS_DMA_READ_CTRL		0x34
#घोषणा SPI_ADRS_DMA_READ_LEN		0x36
#घोषणा SPI_ADRS_DMA_READ_BASE		0x38

#घोषणा SPI_CTRL_STAT_HOST_OVERRIDE	0x8000
#घोषणा SPI_CTRL_STAT_START_HALTED	0x4000
#घोषणा SPI_CTRL_STAT_RAM_BOOT		0x2000
#घोषणा SPI_CTRL_STAT_HOST_RESET	0x1000
#घोषणा SPI_CTRL_STAT_HOST_CPU_EN	0x0800

#घोषणा SPI_DMA_WRITE_CTRL_ENABLE	0x0001
#घोषणा SPI_DMA_READ_CTRL_ENABLE	0x0001
#घोषणा HOST_ALLOWED			(1 << 7)

#घोषणा SPI_TIMEOUT			100         /* msec */

#घोषणा SPI_MAX_TX_PACKETS		32

#घोषणा SPI_MAX_PACKET_SIZE		32767

#घोषणा SPI_TARGET_INT_WAKEUP		0x00000001
#घोषणा SPI_TARGET_INT_SLEEP		0x00000002
#घोषणा SPI_TARGET_INT_RDDONE		0x00000004

#घोषणा SPI_TARGET_INT_CTS		0x00004000
#घोषणा SPI_TARGET_INT_DR		0x00008000

#घोषणा SPI_HOST_INT_READY		0x00000001
#घोषणा SPI_HOST_INT_WR_READY		0x00000002
#घोषणा SPI_HOST_INT_SW_UPDATE		0x00000004
#घोषणा SPI_HOST_INT_UPDATE		0x10000000

/* clear to send */
#घोषणा SPI_HOST_INT_CR			0x00004000

/* data पढ़ोy */
#घोषणा SPI_HOST_INT_DR			0x00008000

#घोषणा SPI_HOST_INTS_DEFAULT 						    \
	(SPI_HOST_INT_READY | SPI_HOST_INT_UPDATE | SPI_HOST_INT_SW_UPDATE)

#घोषणा TARGET_BOOT_SLEEP 50

काष्ठा p54s_dma_regs अणु
	__le16 cmd;
	__le16 len;
	__le32 addr;
पूर्ण __packed;

काष्ठा p54s_tx_info अणु
	काष्ठा list_head tx_list;
पूर्ण;

काष्ठा p54s_priv अणु
	/* p54_common has to be the first entry */
	काष्ठा p54_common common;
	काष्ठा ieee80211_hw *hw;
	काष्ठा spi_device *spi;

	काष्ठा work_काष्ठा work;

	काष्ठा mutex mutex;
	काष्ठा completion fw_comp;

	spinlock_t tx_lock;

	/* रक्षित by tx_lock */
	काष्ठा list_head tx_pending;

	क्रमागत fw_state fw_state;
	स्थिर काष्ठा firmware *firmware;
पूर्ण;

#पूर्ण_अगर /* P54SPI_H */
