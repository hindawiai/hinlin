<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * au1550_spi.h - Au1550 PSC SPI controller driver - platक्रमm data काष्ठाure
 */

#अगर_अघोषित _AU1550_SPI_H_
#घोषणा _AU1550_SPI_H_

काष्ठा au1550_spi_info अणु
	u32 मुख्यclk_hz;		/* मुख्य input घड़ी frequency of PSC */
	u16 num_chipselect;	/* number of chipselects supported */
	व्योम (*activate_cs)(काष्ठा au1550_spi_info *spi, पूर्णांक cs, पूर्णांक polarity);
	व्योम (*deactivate_cs)(काष्ठा au1550_spi_info *spi, पूर्णांक cs, पूर्णांक polarity);
पूर्ण;

#पूर्ण_अगर
