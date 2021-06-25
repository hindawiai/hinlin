<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित	__SPI_BITBANG_H
#घोषणा	__SPI_BITBANG_H

#समावेश <linux/workqueue.h>

काष्ठा spi_bitbang अणु
	काष्ठा mutex		lock;
	u8			busy;
	u8			use_dma;
	u16			flags;		/* extra spi->mode support */

	काष्ठा spi_master	*master;

	/* setup_transfer() changes घड़ी and/or wordsize to match settings
	 * क्रम this transfer; zeroes restore शेषs from spi_device.
	 */
	पूर्णांक	(*setup_transfer)(काष्ठा spi_device *spi,
			काष्ठा spi_transfer *t);

	व्योम	(*chipselect)(काष्ठा spi_device *spi, पूर्णांक is_on);
#घोषणा	BITBANG_CS_ACTIVE	1	/* normally nCS, active low */
#घोषणा	BITBANG_CS_INACTIVE	0

	/* txrx_bufs() may handle dma mapping क्रम transfers that करोn't
	 * alपढ़ोy have one (transfer.अणुtx,rxपूर्ण_dma is zero), or use PIO
	 */
	पूर्णांक	(*txrx_bufs)(काष्ठा spi_device *spi, काष्ठा spi_transfer *t);

	/* txrx_word[SPI_MODE_*]() just looks like a shअगरt रेजिस्टर */
	u32	(*txrx_word[4])(काष्ठा spi_device *spi,
			अचिन्हित nsecs,
			u32 word, u8 bits, अचिन्हित flags);
	पूर्णांक	(*set_line_direction)(काष्ठा spi_device *spi, bool output);
पूर्ण;

/* you can call these शेष bitbang->master methods from your custom
 * methods, अगर you like.
 */
बाह्य पूर्णांक spi_bitbang_setup(काष्ठा spi_device *spi);
बाह्य व्योम spi_bitbang_cleanup(काष्ठा spi_device *spi);
बाह्य पूर्णांक spi_bitbang_setup_transfer(काष्ठा spi_device *spi,
				      काष्ठा spi_transfer *t);

/* start or stop queue processing */
बाह्य पूर्णांक spi_bitbang_start(काष्ठा spi_bitbang *spi);
बाह्य पूर्णांक spi_bitbang_init(काष्ठा spi_bitbang *spi);
बाह्य व्योम spi_bitbang_stop(काष्ठा spi_bitbang *spi);

#पूर्ण_अगर	/* __SPI_BITBANG_H */
