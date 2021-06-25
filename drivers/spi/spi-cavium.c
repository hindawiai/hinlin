<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2011, 2012 Cavium, Inc.
 */

#समावेश <linux/spi/spi.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>

#समावेश "spi-cavium.h"

अटल व्योम octeon_spi_रुको_पढ़ोy(काष्ठा octeon_spi *p)
अणु
	जोड़ cvmx_mpi_sts mpi_sts;
	अचिन्हित पूर्णांक loops = 0;

	करो अणु
		अगर (loops++)
			__delay(500);
		mpi_sts.u64 = पढ़ोq(p->रेजिस्टर_base + OCTEON_SPI_STS(p));
	पूर्ण जबतक (mpi_sts.s.busy);
पूर्ण

अटल पूर्णांक octeon_spi_करो_transfer(काष्ठा octeon_spi *p,
				  काष्ठा spi_message *msg,
				  काष्ठा spi_transfer *xfer,
				  bool last_xfer)
अणु
	काष्ठा spi_device *spi = msg->spi;
	जोड़ cvmx_mpi_cfg mpi_cfg;
	जोड़ cvmx_mpi_tx mpi_tx;
	अचिन्हित पूर्णांक clkभाग;
	पूर्णांक mode;
	bool cpha, cpol;
	स्थिर u8 *tx_buf;
	u8 *rx_buf;
	पूर्णांक len;
	पूर्णांक i;

	mode = spi->mode;
	cpha = mode & SPI_CPHA;
	cpol = mode & SPI_CPOL;

	clkभाग = p->sys_freq / (2 * xfer->speed_hz);

	mpi_cfg.u64 = 0;

	mpi_cfg.s.clkभाग = clkभाग;
	mpi_cfg.s.cshi = (mode & SPI_CS_HIGH) ? 1 : 0;
	mpi_cfg.s.lsbfirst = (mode & SPI_LSB_FIRST) ? 1 : 0;
	mpi_cfg.s.wireor = (mode & SPI_3WIRE) ? 1 : 0;
	mpi_cfg.s.idlelo = cpha != cpol;
	mpi_cfg.s.cslate = cpha ? 1 : 0;
	mpi_cfg.s.enable = 1;

	अगर (spi->chip_select < 4)
		p->cs_enax |= 1ull << (12 + spi->chip_select);
	mpi_cfg.u64 |= p->cs_enax;

	अगर (mpi_cfg.u64 != p->last_cfg) अणु
		p->last_cfg = mpi_cfg.u64;
		ग_लिखोq(mpi_cfg.u64, p->रेजिस्टर_base + OCTEON_SPI_CFG(p));
	पूर्ण
	tx_buf = xfer->tx_buf;
	rx_buf = xfer->rx_buf;
	len = xfer->len;
	जबतक (len > OCTEON_SPI_MAX_BYTES) अणु
		क्रम (i = 0; i < OCTEON_SPI_MAX_BYTES; i++) अणु
			u8 d;
			अगर (tx_buf)
				d = *tx_buf++;
			अन्यथा
				d = 0;
			ग_लिखोq(d, p->रेजिस्टर_base + OCTEON_SPI_DAT0(p) + (8 * i));
		पूर्ण
		mpi_tx.u64 = 0;
		mpi_tx.s.csid = spi->chip_select;
		mpi_tx.s.leavecs = 1;
		mpi_tx.s.txnum = tx_buf ? OCTEON_SPI_MAX_BYTES : 0;
		mpi_tx.s.totnum = OCTEON_SPI_MAX_BYTES;
		ग_लिखोq(mpi_tx.u64, p->रेजिस्टर_base + OCTEON_SPI_TX(p));

		octeon_spi_रुको_पढ़ोy(p);
		अगर (rx_buf)
			क्रम (i = 0; i < OCTEON_SPI_MAX_BYTES; i++) अणु
				u64 v = पढ़ोq(p->रेजिस्टर_base + OCTEON_SPI_DAT0(p) + (8 * i));
				*rx_buf++ = (u8)v;
			पूर्ण
		len -= OCTEON_SPI_MAX_BYTES;
	पूर्ण

	क्रम (i = 0; i < len; i++) अणु
		u8 d;
		अगर (tx_buf)
			d = *tx_buf++;
		अन्यथा
			d = 0;
		ग_लिखोq(d, p->रेजिस्टर_base + OCTEON_SPI_DAT0(p) + (8 * i));
	पूर्ण

	mpi_tx.u64 = 0;
	mpi_tx.s.csid = spi->chip_select;
	अगर (last_xfer)
		mpi_tx.s.leavecs = xfer->cs_change;
	अन्यथा
		mpi_tx.s.leavecs = !xfer->cs_change;
	mpi_tx.s.txnum = tx_buf ? len : 0;
	mpi_tx.s.totnum = len;
	ग_लिखोq(mpi_tx.u64, p->रेजिस्टर_base + OCTEON_SPI_TX(p));

	octeon_spi_रुको_पढ़ोy(p);
	अगर (rx_buf)
		क्रम (i = 0; i < len; i++) अणु
			u64 v = पढ़ोq(p->रेजिस्टर_base + OCTEON_SPI_DAT0(p) + (8 * i));
			*rx_buf++ = (u8)v;
		पूर्ण

	spi_transfer_delay_exec(xfer);

	वापस xfer->len;
पूर्ण

पूर्णांक octeon_spi_transfer_one_message(काष्ठा spi_master *master,
				    काष्ठा spi_message *msg)
अणु
	काष्ठा octeon_spi *p = spi_master_get_devdata(master);
	अचिन्हित पूर्णांक total_len = 0;
	पूर्णांक status = 0;
	काष्ठा spi_transfer *xfer;

	list_क्रम_each_entry(xfer, &msg->transfers, transfer_list) अणु
		bool last_xfer = list_is_last(&xfer->transfer_list,
					      &msg->transfers);
		पूर्णांक r = octeon_spi_करो_transfer(p, msg, xfer, last_xfer);
		अगर (r < 0) अणु
			status = r;
			जाओ err;
		पूर्ण
		total_len += r;
	पूर्ण
err:
	msg->status = status;
	msg->actual_length = total_len;
	spi_finalize_current_message(master);
	वापस status;
पूर्ण
