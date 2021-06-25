<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * rt5514-spi.h  --  RT5514 driver
 *
 * Copyright 2015 Realtek Semiconductor Corp.
 * Author: Oder Chiou <oder_chiou@realtek.com>
 */

#अगर_अघोषित __RT5514_SPI_H__
#घोषणा __RT5514_SPI_H__

/**
 * RT5514_SPI_BUF_LEN is the buffer size of SPI master controller.
*/
#घोषणा RT5514_SPI_BUF_LEN		240

#घोषणा RT5514_BUFFER_VOICE_BASE	0x18000200
#घोषणा RT5514_BUFFER_VOICE_LIMIT	0x18000204
#घोषणा RT5514_BUFFER_VOICE_WP		0x1800020c
#घोषणा RT5514_IRQ_CTRL			0x18002094

#घोषणा RT5514_IRQ_STATUS_BIT		(0x1 << 5)

/* SPI Command */
क्रमागत अणु
	RT5514_SPI_CMD_16_READ = 0,
	RT5514_SPI_CMD_16_WRITE,
	RT5514_SPI_CMD_32_READ,
	RT5514_SPI_CMD_32_WRITE,
	RT5514_SPI_CMD_BURST_READ,
	RT5514_SPI_CMD_BURST_WRITE,
पूर्ण;

पूर्णांक rt5514_spi_burst_पढ़ो(अचिन्हित पूर्णांक addr, u8 *rxbuf, माप_प्रकार len);
पूर्णांक rt5514_spi_burst_ग_लिखो(u32 addr, स्थिर u8 *txbuf, माप_प्रकार len);

#पूर्ण_अगर /* __RT5514_SPI_H__ */
