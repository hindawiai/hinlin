<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Mix this utility code with some glue code to get one of several types of
 * simple SPI master driver.  Two करो polled word-at-a-समय I/O:
 *
 *   -	GPIO/parport bitbangers.  Provide chipselect() and txrx_word[](),
 *	expanding the per-word routines from the अंतरभूत ढाँचाs below.
 *
 *   -	Drivers क्रम controllers resembling bare shअगरt रेजिस्टरs.  Provide
 *	chipselect() and txrx_word[](), with custom setup()/cleanup() methods
 *	that use your controller's घड़ी and chipselect रेजिस्टरs.
 *
 * Some hardware works well with requests at spi_transfer scope:
 *
 *   -	Drivers leveraging smarter hardware, with fअगरos or DMA; or क्रम half
 *	duplex (MicroWire) controllers.  Provide chipselect() and txrx_bufs(),
 *	and custom setup()/cleanup() methods.
 */

/*
 * The code that knows what GPIO pins करो what should have declared four
 * functions, ideally as अंतरभूतs, beक्रमe including this header:
 *
 *  व्योम setsck(काष्ठा spi_device *, पूर्णांक is_on);
 *  व्योम seपंचांगosi(काष्ठा spi_device *, पूर्णांक is_on);
 *  पूर्णांक geपंचांगiso(काष्ठा spi_device *);
 *  व्योम spidelay(अचिन्हित);
 *
 * setsck()'s is_on parameter is a zero/nonzero boolean.
 *
 * seपंचांगosi()'s is_on parameter is a zero/nonzero boolean.
 *
 * geपंचांगiso() is required to वापस 0 or 1 only. Any other value is invalid
 * and will result in improper operation.
 *
 * A non-अंतरभूतd routine would call bitbang_txrx_*() routines.  The
 * मुख्य loop could easily compile करोwn to a handful of inकाष्ठाions,
 * especially अगर the delay is a NOP (to run at peak speed).
 *
 * Since this is software, the timings may not be exactly what your board's
 * chips need ... there may be several reasons you'd need to tweak timings
 * in these routines, not just to make it faster or slower to match a
 * particular CPU घड़ी rate.
 */

अटल अंतरभूत u32
bitbang_txrx_be_cpha0(काष्ठा spi_device *spi,
		अचिन्हित nsecs, अचिन्हित cpol, अचिन्हित flags,
		u32 word, u8 bits)
अणु
	/* अगर (cpol == 0) this is SPI_MODE_0; अन्यथा this is SPI_MODE_2 */

	u32 oldbit = (!(word & (1<<(bits-1)))) << 31;
	/* घड़ी starts at inactive polarity */
	क्रम (word <<= (32 - bits); likely(bits); bits--) अणु

		/* setup MSB (to slave) on trailing edge */
		अगर ((flags & SPI_MASTER_NO_TX) == 0) अणु
			अगर ((word & (1 << 31)) != oldbit) अणु
				seपंचांगosi(spi, word & (1 << 31));
				oldbit = word & (1 << 31);
			पूर्ण
		पूर्ण
		spidelay(nsecs);	/* T(setup) */

		setsck(spi, !cpol);
		spidelay(nsecs);

		/* sample MSB (from slave) on leading edge */
		word <<= 1;
		अगर ((flags & SPI_MASTER_NO_RX) == 0)
			word |= geपंचांगiso(spi);
		setsck(spi, cpol);
	पूर्ण
	वापस word;
पूर्ण

अटल अंतरभूत u32
bitbang_txrx_be_cpha1(काष्ठा spi_device *spi,
		अचिन्हित nsecs, अचिन्हित cpol, अचिन्हित flags,
		u32 word, u8 bits)
अणु
	/* अगर (cpol == 0) this is SPI_MODE_1; अन्यथा this is SPI_MODE_3 */

	u32 oldbit = (!(word & (1<<(bits-1)))) << 31;
	/* घड़ी starts at inactive polarity */
	क्रम (word <<= (32 - bits); likely(bits); bits--) अणु

		/* setup MSB (to slave) on leading edge */
		setsck(spi, !cpol);
		अगर ((flags & SPI_MASTER_NO_TX) == 0) अणु
			अगर ((word & (1 << 31)) != oldbit) अणु
				seपंचांगosi(spi, word & (1 << 31));
				oldbit = word & (1 << 31);
			पूर्ण
		पूर्ण
		spidelay(nsecs); /* T(setup) */

		setsck(spi, cpol);
		spidelay(nsecs);

		/* sample MSB (from slave) on trailing edge */
		word <<= 1;
		अगर ((flags & SPI_MASTER_NO_RX) == 0)
			word |= geपंचांगiso(spi);
	पूर्ण
	वापस word;
पूर्ण
