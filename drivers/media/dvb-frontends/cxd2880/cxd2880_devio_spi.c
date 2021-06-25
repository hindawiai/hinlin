<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cxd2880_devio_spi.c
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 * I/O पूर्णांकerface via SPI
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#समावेश "cxd2880_devio_spi.h"

#घोषणा BURST_WRITE_MAX 128

अटल पूर्णांक cxd2880_io_spi_पढ़ो_reg(काष्ठा cxd2880_io *io,
				   क्रमागत cxd2880_io_tgt tgt,
				   u8 sub_address, u8 *data,
				   u32 size)
अणु
	पूर्णांक ret = 0;
	काष्ठा cxd2880_spi *spi = शून्य;
	u8 send_data[6];
	u8 *पढ़ो_data_top = data;

	अगर (!io || !io->अगर_object || !data)
		वापस -EINVAL;

	अगर (sub_address + size > 0x100)
		वापस -EINVAL;

	spi = io->अगर_object;

	अगर (tgt == CXD2880_IO_TGT_SYS)
		send_data[0] = 0x0b;
	अन्यथा
		send_data[0] = 0x0a;

	send_data[3] = 0;
	send_data[4] = 0;
	send_data[5] = 0;

	जबतक (size > 0) अणु
		send_data[1] = sub_address;
		अगर (size > 255)
			send_data[2] = 255;
		अन्यथा
			send_data[2] = size;

		ret =
		    spi->ग_लिखो_पढ़ो(spi, send_data, माप(send_data),
				    पढ़ो_data_top, send_data[2]);
		अगर (ret)
			वापस ret;

		sub_address += send_data[2];
		पढ़ो_data_top += send_data[2];
		size -= send_data[2];
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cxd2880_io_spi_ग_लिखो_reg(काष्ठा cxd2880_io *io,
				    क्रमागत cxd2880_io_tgt tgt,
				    u8 sub_address,
				    स्थिर u8 *data, u32 size)
अणु
	पूर्णांक ret = 0;
	काष्ठा cxd2880_spi *spi = शून्य;
	u8 send_data[BURST_WRITE_MAX + 4];
	स्थिर u8 *ग_लिखो_data_top = data;

	अगर (!io || !io->अगर_object || !data)
		वापस -EINVAL;

	अगर (size > BURST_WRITE_MAX)
		वापस -EINVAL;

	अगर (sub_address + size > 0x100)
		वापस -EINVAL;

	spi = io->अगर_object;

	अगर (tgt == CXD2880_IO_TGT_SYS)
		send_data[0] = 0x0f;
	अन्यथा
		send_data[0] = 0x0e;

	जबतक (size > 0) अणु
		send_data[1] = sub_address;
		अगर (size > 255)
			send_data[2] = 255;
		अन्यथा
			send_data[2] = size;

		स_नकल(&send_data[3], ग_लिखो_data_top, send_data[2]);

		अगर (tgt == CXD2880_IO_TGT_SYS) अणु
			send_data[3 + send_data[2]] = 0x00;
			ret = spi->ग_लिखो(spi, send_data, send_data[2] + 4);
		पूर्ण अन्यथा अणु
			ret = spi->ग_लिखो(spi, send_data, send_data[2] + 3);
		पूर्ण
		अगर (ret)
			वापस ret;

		sub_address += send_data[2];
		ग_लिखो_data_top += send_data[2];
		size -= send_data[2];
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक cxd2880_io_spi_create(काष्ठा cxd2880_io *io,
			  काष्ठा cxd2880_spi *spi, u8 slave_select)
अणु
	अगर (!io || !spi)
		वापस -EINVAL;

	io->पढ़ो_regs = cxd2880_io_spi_पढ़ो_reg;
	io->ग_लिखो_regs = cxd2880_io_spi_ग_लिखो_reg;
	io->ग_लिखो_reg = cxd2880_io_common_ग_लिखो_one_reg;
	io->अगर_object = spi;
	io->i2c_address_sys = 0;
	io->i2c_address_demod = 0;
	io->slave_select = slave_select;

	वापस 0;
पूर्ण
