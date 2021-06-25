<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * board-specअगरic data क्रम the libertas_spi driver.
 *
 * Copyright 2008 Analog Devices Inc.
 */
#अगर_अघोषित _LIBERTAS_SPI_H_
#घोषणा _LIBERTAS_SPI_H_

काष्ठा spi_device;

काष्ठा libertas_spi_platक्रमm_data अणु
	/* There are two ways to पढ़ो data from the WLAN module's SPI
	 * पूर्णांकerface. Setting 0 or 1 here controls which one is used.
	 *
	 * Usually you want to set use_dummy_ग_लिखोs = 1.
	 * However, अगर that करोesn't work or अगर you are using a slow SPI घड़ी
	 * speed, you may want to use 0 here. */
	u16 use_dummy_ग_लिखोs;

	/* Board specअगरic setup/tearकरोwn */
	पूर्णांक (*setup)(काष्ठा spi_device *spi);
	पूर्णांक (*tearकरोwn)(काष्ठा spi_device *spi);
पूर्ण;
#पूर्ण_अगर
