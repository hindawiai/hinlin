<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SPI_H__
#घोषणा __ASM_SPI_H__

काष्ठा sh_spi_info;

काष्ठा sh_spi_info अणु
	पूर्णांक			 bus_num;
	पूर्णांक			 num_chipselect;

	व्योम (*chip_select)(काष्ठा sh_spi_info *spi, पूर्णांक cs, पूर्णांक state);
पूर्ण;

#पूर्ण_अगर /* __ASM_SPI_H__ */
