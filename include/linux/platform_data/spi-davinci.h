<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2009 Texas Instruments.
 */

#अगर_अघोषित __ARCH_ARM_DAVINCI_SPI_H
#घोषणा __ARCH_ARM_DAVINCI_SPI_H

#समावेश <linux/platक्रमm_data/edma.h>

#घोषणा SPI_INTERN_CS	0xFF

क्रमागत अणु
	SPI_VERSION_1, /* For DM355/DM365/DM6467 */
	SPI_VERSION_2, /* For DA8xx */
पूर्ण;

/**
 * davinci_spi_platक्रमm_data - Platक्रमm data क्रम SPI master device on DaVinci
 *
 * @version:	version of the SPI IP. Dअगरferent DaVinci devices have slightly
 *		varying versions of the same IP.
 * @num_chipselect: number of chipselects supported by this SPI master
 * @पूर्णांकr_line:	पूर्णांकerrupt line used to connect the SPI IP to the ARM पूर्णांकerrupt
 *		controller withn the SoC. Possible values are 0 and 1.
 * @cshold_bug:	set this to true अगर the SPI controller on your chip requires
 *		a ग_लिखो to CSHOLD bit in between transfers (like in DM355).
 * @dma_event_q: DMA event queue to use अगर SPI_IO_TYPE_DMA is used क्रम any
 *		device on the bus.
 */
काष्ठा davinci_spi_platक्रमm_data अणु
	u8			version;
	u8			num_chipselect;
	u8			पूर्णांकr_line;
	u8			prescaler_limit;
	bool			cshold_bug;
	क्रमागत dma_event_q	dma_event_q;
पूर्ण;

/**
 * davinci_spi_config - Per-chip-select configuration क्रम SPI slave devices
 *
 * @wdelay:	amount of delay between transmissions. Measured in number of
 *		SPI module घड़ीs.
 * @odd_parity:	polarity of parity flag at the end of transmit data stream.
 *		0 - odd parity, 1 - even parity.
 * @parity_enable: enable transmission of parity at end of each transmit
 *		data stream.
 * @io_type:	type of IO transfer. Choose between polled, पूर्णांकerrupt and DMA.
 * @समयr_disable: disable chip-select समयrs (setup and hold)
 * @c2tdelay:	chip-select setup समय. Measured in number of SPI module घड़ीs.
 * @t2cdelay:	chip-select hold समय. Measured in number of SPI module घड़ीs.
 * @t2edelay:	transmit data finished to SPI ENAn pin inactive समय. Measured
 *		in number of SPI घड़ीs.
 * @c2edelay:	chip-select active to SPI ENAn संकेत active समय. Measured in
 *		number of SPI घड़ीs.
 */
काष्ठा davinci_spi_config अणु
	u8	wdelay;
	u8	odd_parity;
	u8	parity_enable;
#घोषणा SPI_IO_TYPE_INTR	0
#घोषणा SPI_IO_TYPE_POLL	1
#घोषणा SPI_IO_TYPE_DMA		2
	u8	io_type;
	u8	समयr_disable;
	u8	c2tdelay;
	u8	t2cdelay;
	u8	t2edelay;
	u8	c2edelay;
पूर्ण;

#पूर्ण_अगर	/* __ARCH_ARM_DAVINCI_SPI_H */
