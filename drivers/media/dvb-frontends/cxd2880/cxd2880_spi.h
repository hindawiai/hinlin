<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * cxd2880_spi.h
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 * SPI access definitions
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#अगर_अघोषित CXD2880_SPI_H
#घोषणा CXD2880_SPI_H

#समावेश "cxd2880_common.h"

क्रमागत cxd2880_spi_mode अणु
	CXD2880_SPI_MODE_0,
	CXD2880_SPI_MODE_1,
	CXD2880_SPI_MODE_2,
	CXD2880_SPI_MODE_3
पूर्ण;

काष्ठा cxd2880_spi अणु
	पूर्णांक (*पढ़ो)(काष्ठा cxd2880_spi *spi, u8 *data,
		    u32 size);
	पूर्णांक (*ग_लिखो)(काष्ठा cxd2880_spi *spi, स्थिर u8 *data,
		     u32 size);
	पूर्णांक (*ग_लिखो_पढ़ो)(काष्ठा cxd2880_spi *spi,
			  स्थिर u8 *tx_data, u32 tx_size,
			  u8 *rx_data, u32 rx_size);
	u32 flags;
	व्योम *user;
पूर्ण;

#पूर्ण_अगर
