<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Header File क्रम Altera SPI Driver.
 */
#अगर_अघोषित __LINUX_SPI_ALTERA_H
#घोषणा __LINUX_SPI_ALTERA_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/types.h>

#घोषणा ALTERA_SPI_MAX_CS		32

/**
 * काष्ठा altera_spi_platक्रमm_data - Platक्रमm data of the Altera SPI driver
 * @mode_bits:		Mode bits of SPI master.
 * @num_chipselect:	Number of chipselects.
 * @bits_per_word_mask:	biपंचांगask of supported bits_per_word क्रम transfers.
 * @num_devices:	Number of devices that shall be added when the driver
 *			is probed.
 * @devices:		The devices to add.
 */
काष्ठा altera_spi_platक्रमm_data अणु
	u16				mode_bits;
	u16				num_chipselect;
	u32				bits_per_word_mask;
	u16				num_devices;
	काष्ठा spi_board_info		*devices;
पूर्ण;

काष्ठा altera_spi अणु
	पूर्णांक irq;
	पूर्णांक len;
	पूर्णांक count;
	पूर्णांक bytes_per_word;
	u32 imr;

	/* data buffers */
	स्थिर अचिन्हित अक्षर *tx;
	अचिन्हित अक्षर *rx;

	काष्ठा regmap *regmap;
	u32 regoff;
	काष्ठा device *dev;
पूर्ण;

बाह्य irqवापस_t altera_spi_irq(पूर्णांक irq, व्योम *dev);
बाह्य व्योम altera_spi_init_master(काष्ठा spi_master *master);
#पूर्ण_अगर /* __LINUX_SPI_ALTERA_H */
