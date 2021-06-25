<शैली गुरु>
/*
 * spi_eeprom.c
 * Copyright (C) 2000-2001 Toshiba Corporation
 *
 * 2003-2005 (c) MontaVista Software, Inc. This file is licensed under the
 * terms of the GNU General Public License version 2. This program is
 * licensed "as is" without any warranty of any kind, whether express
 * or implied.
 *
 * Support क्रम TX4938 in 2.6 - Manish Lachwani (mlachwani@mvista.com)
 */
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/eeprom.h>
#समावेश <यंत्र/txx9/spi.h>

#घोषणा AT250X0_PAGE_SIZE	8

/* रेजिस्टर board inक्रमmation क्रम at25 driver */
पूर्णांक __init spi_eeprom_रेजिस्टर(पूर्णांक busid, पूर्णांक chipid, पूर्णांक size)
अणु
	काष्ठा spi_board_info info = अणु
		.modalias = "at25",
		.max_speed_hz = 1500000,	/* 1.5Mbps */
		.bus_num = busid,
		.chip_select = chipid,
		/* Mode 0: High-Active, Sample-Then-Shअगरt */
	पूर्ण;
	काष्ठा spi_eeprom *eeprom;
	eeprom = kzalloc(माप(*eeprom), GFP_KERNEL);
	अगर (!eeprom)
		वापस -ENOMEM;
	म_नकल(eeprom->name, "at250x0");
	eeprom->byte_len = size;
	eeprom->page_size = AT250X0_PAGE_SIZE;
	eeprom->flags = EE_ADDR1;
	info.platक्रमm_data = eeprom;
	वापस spi_रेजिस्टर_board_info(&info, 1);
पूर्ण

/* simple temporary spi driver to provide early access to seeprom. */

अटल काष्ठा पढ़ो_param अणु
	पूर्णांक busid;
	पूर्णांक chipid;
	पूर्णांक address;
	अचिन्हित अक्षर *buf;
	पूर्णांक len;
पूर्ण *पढ़ो_param;

अटल पूर्णांक __init early_seeprom_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक stat = 0;
	u8 cmd[2];
	पूर्णांक len = पढ़ो_param->len;
	अक्षर *buf = पढ़ो_param->buf;
	पूर्णांक address = पढ़ो_param->address;

	dev_info(&spi->dev, "spiclk %u KHz.\n",
		 (spi->max_speed_hz + 500) / 1000);
	अगर (पढ़ो_param->busid != spi->master->bus_num ||
	    पढ़ो_param->chipid != spi->chip_select)
		वापस -ENODEV;
	जबतक (len > 0) अणु
		/* spi_ग_लिखो_then_पढ़ो can only work with small chunk */
		पूर्णांक c = len < AT250X0_PAGE_SIZE ? len : AT250X0_PAGE_SIZE;
		cmd[0] = 0x03;	/* AT25_READ */
		cmd[1] = address;
		stat = spi_ग_लिखो_then_पढ़ो(spi, cmd, माप(cmd), buf, c);
		buf += c;
		len -= c;
		address += c;
	पूर्ण
	वापस stat;
पूर्ण

अटल काष्ठा spi_driver early_seeprom_driver __initdata = अणु
	.driver = अणु
		.name	= "at25",
	पूर्ण,
	.probe	= early_seeprom_probe,
पूर्ण;

पूर्णांक __init spi_eeprom_पढ़ो(पूर्णांक busid, पूर्णांक chipid, पूर्णांक address,
			   अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक ret;
	काष्ठा पढ़ो_param param = अणु
		.busid = busid,
		.chipid = chipid,
		.address = address,
		.buf = buf,
		.len = len
	पूर्ण;

	पढ़ो_param = &param;
	ret = spi_रेजिस्टर_driver(&early_seeprom_driver);
	अगर (!ret)
		spi_unरेजिस्टर_driver(&early_seeprom_driver);
	वापस ret;
पूर्ण
