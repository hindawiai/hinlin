<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2020, Linaro Limited
 */

#अगर_अघोषित QCOM_GPI_DMA_H
#घोषणा QCOM_GPI_DMA_H

/**
 * क्रमागत spi_transfer_cmd - spi transfer commands
 */
क्रमागत spi_transfer_cmd अणु
	SPI_TX = 1,
	SPI_RX,
	SPI_DUPLEX,
पूर्ण;

/**
 * काष्ठा gpi_spi_config - spi config क्रम peripheral
 *
 * @loopback_en: spi loopback enable when set
 * @घड़ी_pol_high: घड़ी polarity
 * @data_pol_high: data polarity
 * @pack_en: process tx/rx buffers as packed
 * @word_len: spi word length
 * @clk_भाग: source घड़ी भागider
 * @clk_src: serial घड़ी
 * @cmd: spi cmd
 * @fragmentation: keep CS assserted at end of sequence
 * @cs: chip select toggle
 * @set_config: set peripheral config
 * @rx_len: receive length क्रम buffer
 */
काष्ठा gpi_spi_config अणु
	u8 set_config;
	u8 loopback_en;
	u8 घड़ी_pol_high;
	u8 data_pol_high;
	u8 pack_en;
	u8 word_len;
	u8 fragmentation;
	u8 cs;
	u32 clk_भाग;
	u32 clk_src;
	क्रमागत spi_transfer_cmd cmd;
	u32 rx_len;
पूर्ण;

क्रमागत i2c_op अणु
	I2C_WRITE = 1,
	I2C_READ,
पूर्ण;

/**
 * काष्ठा gpi_i2c_config - i2c config क्रम peripheral
 *
 * @pack_enable: process tx/rx buffers as packed
 * @cycle_count: घड़ी cycles to be sent
 * @high_count: high period of घड़ी
 * @low_count: low period of घड़ी
 * @clk_भाग: source घड़ी भागider
 * @addr: i2c bus address
 * @stretch: stretch the घड़ी at eot
 * @set_config: set peripheral config
 * @rx_len: receive length क्रम buffer
 * @op: i2c cmd
 * @muli-msg: is part of multi i2c r-w msgs
 */
काष्ठा gpi_i2c_config अणु
	u8 set_config;
	u8 pack_enable;
	u8 cycle_count;
	u8 high_count;
	u8 low_count;
	u8 addr;
	u8 stretch;
	u16 clk_भाग;
	u32 rx_len;
	क्रमागत i2c_op op;
	bool multi_msg;
पूर्ण;

#पूर्ण_अगर /* QCOM_GPI_DMA_H */
