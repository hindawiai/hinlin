<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * cxd2880_devio_spi.h
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 * I/O पूर्णांकerface via SPI
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#अगर_अघोषित CXD2880_DEVIO_SPI_H
#घोषणा CXD2880_DEVIO_SPI_H

#समावेश "cxd2880_common.h"
#समावेश "cxd2880_io.h"
#समावेश "cxd2880_spi.h"

#समावेश "cxd2880_tnrdmd.h"

पूर्णांक cxd2880_io_spi_create(काष्ठा cxd2880_io *io,
			  काष्ठा cxd2880_spi *spi,
			  u8 slave_select);

#पूर्ण_अगर
