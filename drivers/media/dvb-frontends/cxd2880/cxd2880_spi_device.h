<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * cxd2880_spi_device.h
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 * SPI access पूर्णांकerface
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#अगर_अघोषित CXD2880_SPI_DEVICE_H
#घोषणा CXD2880_SPI_DEVICE_H

#समावेश "cxd2880_spi.h"

काष्ठा cxd2880_spi_device अणु
	काष्ठा spi_device *spi;
पूर्ण;

पूर्णांक cxd2880_spi_device_initialize(काष्ठा cxd2880_spi_device *spi_device,
				  क्रमागत cxd2880_spi_mode mode,
				  u32 speedHz);

पूर्णांक cxd2880_spi_device_create_spi(काष्ठा cxd2880_spi *spi,
				  काष्ठा cxd2880_spi_device *spi_device);

#पूर्ण_अगर /* CXD2880_SPI_DEVICE_H */
