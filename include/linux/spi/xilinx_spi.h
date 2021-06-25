<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_SPI_XILINX_SPI_H
#घोषणा __LINUX_SPI_XILINX_SPI_H

/**
 * काष्ठा xspi_platक्रमm_data - Platक्रमm data of the Xilinx SPI driver
 * @num_chipselect:	Number of chip select by the IP.
 * @little_endian:	If रेजिस्टरs should be accessed little endian or not.
 * @bits_per_word:	Number of bits per word.
 * @devices:		Devices to add when the driver is probed.
 * @num_devices:	Number of devices in the devices array.
 */
काष्ठा xspi_platक्रमm_data अणु
	u16 num_chipselect;
	u8 bits_per_word;
	काष्ठा spi_board_info *devices;
	u8 num_devices;
पूर्ण;

#पूर्ण_अगर /* __LINUX_SPI_XILINX_SPI_H */
