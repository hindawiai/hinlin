<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_SPI_GPIO_H
#घोषणा __LINUX_SPI_GPIO_H

/*
 * For each bitbanged SPI bus, set up a platक्रमm_device node with:
 *   - name "spi_gpio"
 *   - id the same as the SPI bus number it implements
 *   - dev.platक्रमm data poपूर्णांकing to a काष्ठा spi_gpio_platक्रमm_data
 *
 * Use spi_board_info with these busses in the usual way.
 *
 * If the bitbanged bus is later चयनed to a "native" controller,
 * that platक्रमm_device and controller_data should be हटाओd.
 */

/**
 * काष्ठा spi_gpio_platक्रमm_data - parameter क्रम bitbanged SPI master
 * @num_chipselect: how many slaves to allow
 */
काष्ठा spi_gpio_platक्रमm_data अणु
	u16		num_chipselect;
पूर्ण;

#पूर्ण_अगर /* __LINUX_SPI_GPIO_H */
