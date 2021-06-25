<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * polling/bitbanging SPI master controller driver utilities
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi_bitbang.h>

#घोषणा SPI_BITBANG_CS_DELAY	100


/*----------------------------------------------------------------------*/

/*
 * FIRST PART (OPTIONAL):  word-at-a-समय spi_transfer support.
 * Use this क्रम GPIO or shअगरt-रेजिस्टर level hardware APIs.
 *
 * spi_bitbang_cs is in spi_device->controller_state, which is unavailable
 * to glue code.  These bitbang setup() and cleanup() routines are always
 * used, though maybe they're called from controller-aware code.
 *
 * chipselect() and मित्रs may use spi_device->controller_data and
 * controller रेजिस्टरs as appropriate.
 *
 *
 * NOTE:  SPI controller pins can often be used as GPIO pins instead,
 * which means you could use a bitbang driver either to get hardware
 * working quickly, or testing क्रम dअगरferences that aren't speed related.
 */

काष्ठा spi_bitbang_cs अणु
	अचिन्हित	nsecs;	/* (घड़ी cycle समय)/2 */
	u32		(*txrx_word)(काष्ठा spi_device *spi, अचिन्हित nsecs,
					u32 word, u8 bits, अचिन्हित flags);
	अचिन्हित	(*txrx_bufs)(काष्ठा spi_device *,
					u32 (*txrx_word)(
						काष्ठा spi_device *spi,
						अचिन्हित nsecs,
						u32 word, u8 bits,
						अचिन्हित flags),
					अचिन्हित, काष्ठा spi_transfer *,
					अचिन्हित);
पूर्ण;

अटल अचिन्हित bitbang_txrx_8(
	काष्ठा spi_device	*spi,
	u32			(*txrx_word)(काष्ठा spi_device *spi,
					अचिन्हित nsecs,
					u32 word, u8 bits,
					अचिन्हित flags),
	अचिन्हित		ns,
	काष्ठा spi_transfer	*t,
	अचिन्हित flags
)
अणु
	अचिन्हित		bits = t->bits_per_word;
	अचिन्हित		count = t->len;
	स्थिर u8		*tx = t->tx_buf;
	u8			*rx = t->rx_buf;

	जबतक (likely(count > 0)) अणु
		u8		word = 0;

		अगर (tx)
			word = *tx++;
		word = txrx_word(spi, ns, word, bits, flags);
		अगर (rx)
			*rx++ = word;
		count -= 1;
	पूर्ण
	वापस t->len - count;
पूर्ण

अटल अचिन्हित bitbang_txrx_16(
	काष्ठा spi_device	*spi,
	u32			(*txrx_word)(काष्ठा spi_device *spi,
					अचिन्हित nsecs,
					u32 word, u8 bits,
					अचिन्हित flags),
	अचिन्हित		ns,
	काष्ठा spi_transfer	*t,
	अचिन्हित flags
)
अणु
	अचिन्हित		bits = t->bits_per_word;
	अचिन्हित		count = t->len;
	स्थिर u16		*tx = t->tx_buf;
	u16			*rx = t->rx_buf;

	जबतक (likely(count > 1)) अणु
		u16		word = 0;

		अगर (tx)
			word = *tx++;
		word = txrx_word(spi, ns, word, bits, flags);
		अगर (rx)
			*rx++ = word;
		count -= 2;
	पूर्ण
	वापस t->len - count;
पूर्ण

अटल अचिन्हित bitbang_txrx_32(
	काष्ठा spi_device	*spi,
	u32			(*txrx_word)(काष्ठा spi_device *spi,
					अचिन्हित nsecs,
					u32 word, u8 bits,
					अचिन्हित flags),
	अचिन्हित		ns,
	काष्ठा spi_transfer	*t,
	अचिन्हित flags
)
अणु
	अचिन्हित		bits = t->bits_per_word;
	अचिन्हित		count = t->len;
	स्थिर u32		*tx = t->tx_buf;
	u32			*rx = t->rx_buf;

	जबतक (likely(count > 3)) अणु
		u32		word = 0;

		अगर (tx)
			word = *tx++;
		word = txrx_word(spi, ns, word, bits, flags);
		अगर (rx)
			*rx++ = word;
		count -= 4;
	पूर्ण
	वापस t->len - count;
पूर्ण

पूर्णांक spi_bitbang_setup_transfer(काष्ठा spi_device *spi, काष्ठा spi_transfer *t)
अणु
	काष्ठा spi_bitbang_cs	*cs = spi->controller_state;
	u8			bits_per_word;
	u32			hz;

	अगर (t) अणु
		bits_per_word = t->bits_per_word;
		hz = t->speed_hz;
	पूर्ण अन्यथा अणु
		bits_per_word = 0;
		hz = 0;
	पूर्ण

	/* spi_transfer level calls that work per-word */
	अगर (!bits_per_word)
		bits_per_word = spi->bits_per_word;
	अगर (bits_per_word <= 8)
		cs->txrx_bufs = bitbang_txrx_8;
	अन्यथा अगर (bits_per_word <= 16)
		cs->txrx_bufs = bitbang_txrx_16;
	अन्यथा अगर (bits_per_word <= 32)
		cs->txrx_bufs = bitbang_txrx_32;
	अन्यथा
		वापस -EINVAL;

	/* nsecs = (घड़ी period)/2 */
	अगर (!hz)
		hz = spi->max_speed_hz;
	अगर (hz) अणु
		cs->nsecs = (1000000000/2) / hz;
		अगर (cs->nsecs > (MAX_UDELAY_MS * 1000 * 1000))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(spi_bitbang_setup_transfer);

/*
 * spi_bitbang_setup - शेष setup क्रम per-word I/O loops
 */
पूर्णांक spi_bitbang_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_bitbang_cs	*cs = spi->controller_state;
	काष्ठा spi_bitbang	*bitbang;
	bool			initial_setup = false;
	पूर्णांक			retval;

	bitbang = spi_master_get_devdata(spi->master);

	अगर (!cs) अणु
		cs = kzalloc(माप(*cs), GFP_KERNEL);
		अगर (!cs)
			वापस -ENOMEM;
		spi->controller_state = cs;
		initial_setup = true;
	पूर्ण

	/* per-word shअगरt रेजिस्टर access, in hardware or bitbanging */
	cs->txrx_word = bitbang->txrx_word[spi->mode & (SPI_CPOL|SPI_CPHA)];
	अगर (!cs->txrx_word) अणु
		retval = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण

	अगर (bitbang->setup_transfer) अणु
		retval = bitbang->setup_transfer(spi, शून्य);
		अगर (retval < 0)
			जाओ err_मुक्त;
	पूर्ण

	dev_dbg(&spi->dev, "%s, %u nsec/bit\n", __func__, 2 * cs->nsecs);

	वापस 0;

err_मुक्त:
	अगर (initial_setup)
		kमुक्त(cs);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(spi_bitbang_setup);

/*
 * spi_bitbang_cleanup - शेष cleanup क्रम per-word I/O loops
 */
व्योम spi_bitbang_cleanup(काष्ठा spi_device *spi)
अणु
	kमुक्त(spi->controller_state);
पूर्ण
EXPORT_SYMBOL_GPL(spi_bitbang_cleanup);

अटल पूर्णांक spi_bitbang_bufs(काष्ठा spi_device *spi, काष्ठा spi_transfer *t)
अणु
	काष्ठा spi_bitbang_cs	*cs = spi->controller_state;
	अचिन्हित		nsecs = cs->nsecs;
	काष्ठा spi_bitbang	*bitbang;

	bitbang = spi_master_get_devdata(spi->master);
	अगर (bitbang->set_line_direction) अणु
		पूर्णांक err;

		err = bitbang->set_line_direction(spi, !!(t->tx_buf));
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (spi->mode & SPI_3WIRE) अणु
		अचिन्हित flags;

		flags = t->tx_buf ? SPI_MASTER_NO_RX : SPI_MASTER_NO_TX;
		वापस cs->txrx_bufs(spi, cs->txrx_word, nsecs, t, flags);
	पूर्ण
	वापस cs->txrx_bufs(spi, cs->txrx_word, nsecs, t, 0);
पूर्ण

/*----------------------------------------------------------------------*/

/*
 * SECOND PART ... simple transfer queue runner.
 *
 * This costs a task context per controller, running the queue by
 * perक्रमming each transfer in sequence.  Smarter hardware can queue
 * several DMA transfers at once, and process several controller queues
 * in parallel; this driver करोesn't match such hardware very well.
 *
 * Drivers can provide word-at-a-समय i/o primitives, or provide
 * transfer-at-a-समय ones to leverage dma or fअगरo hardware.
 */

अटल पूर्णांक spi_bitbang_prepare_hardware(काष्ठा spi_master *spi)
अणु
	काष्ठा spi_bitbang	*bitbang;

	bitbang = spi_master_get_devdata(spi);

	mutex_lock(&bitbang->lock);
	bitbang->busy = 1;
	mutex_unlock(&bitbang->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक spi_bitbang_transfer_one(काष्ठा spi_master *master,
				    काष्ठा spi_device *spi,
				    काष्ठा spi_transfer *transfer)
अणु
	काष्ठा spi_bitbang *bitbang = spi_master_get_devdata(master);
	पूर्णांक status = 0;

	अगर (bitbang->setup_transfer) अणु
		status = bitbang->setup_transfer(spi, transfer);
		अगर (status < 0)
			जाओ out;
	पूर्ण

	अगर (transfer->len)
		status = bitbang->txrx_bufs(spi, transfer);

	अगर (status == transfer->len)
		status = 0;
	अन्यथा अगर (status >= 0)
		status = -EREMOTEIO;

out:
	spi_finalize_current_transfer(master);

	वापस status;
पूर्ण

अटल पूर्णांक spi_bitbang_unprepare_hardware(काष्ठा spi_master *spi)
अणु
	काष्ठा spi_bitbang	*bitbang;

	bitbang = spi_master_get_devdata(spi);

	mutex_lock(&bitbang->lock);
	bitbang->busy = 0;
	mutex_unlock(&bitbang->lock);

	वापस 0;
पूर्ण

अटल व्योम spi_bitbang_set_cs(काष्ठा spi_device *spi, bool enable)
अणु
	काष्ठा spi_bitbang *bitbang = spi_master_get_devdata(spi->master);

	/* SPI core provides CS high / low, but bitbang driver
	 * expects CS active
	 * spi device driver takes care of handling SPI_CS_HIGH
	 */
	enable = (!!(spi->mode & SPI_CS_HIGH) == enable);

	ndelay(SPI_BITBANG_CS_DELAY);
	bitbang->chipselect(spi, enable ? BITBANG_CS_ACTIVE :
			    BITBANG_CS_INACTIVE);
	ndelay(SPI_BITBANG_CS_DELAY);
पूर्ण

/*----------------------------------------------------------------------*/

पूर्णांक spi_bitbang_init(काष्ठा spi_bitbang *bitbang)
अणु
	काष्ठा spi_master *master = bitbang->master;
	bool custom_cs;

	अगर (!master)
		वापस -EINVAL;
	/*
	 * We only need the chipselect callback अगर we are actually using it.
	 * If we just use GPIO descriptors, it is surplus. If the
	 * SPI_MASTER_GPIO_SS flag is set, we always need to call the
	 * driver-specअगरic chipselect routine.
	 */
	custom_cs = (!master->use_gpio_descriptors ||
		     (master->flags & SPI_MASTER_GPIO_SS));

	अगर (custom_cs && !bitbang->chipselect)
		वापस -EINVAL;

	mutex_init(&bitbang->lock);

	अगर (!master->mode_bits)
		master->mode_bits = SPI_CPOL | SPI_CPHA | bitbang->flags;

	अगर (master->transfer || master->transfer_one_message)
		वापस -EINVAL;

	master->prepare_transfer_hardware = spi_bitbang_prepare_hardware;
	master->unprepare_transfer_hardware = spi_bitbang_unprepare_hardware;
	master->transfer_one = spi_bitbang_transfer_one;
	/*
	 * When using GPIO descriptors, the ->set_cs() callback करोesn't even
	 * get called unless SPI_MASTER_GPIO_SS is set.
	 */
	अगर (custom_cs)
		master->set_cs = spi_bitbang_set_cs;

	अगर (!bitbang->txrx_bufs) अणु
		bitbang->use_dma = 0;
		bitbang->txrx_bufs = spi_bitbang_bufs;
		अगर (!master->setup) अणु
			अगर (!bitbang->setup_transfer)
				bitbang->setup_transfer =
					 spi_bitbang_setup_transfer;
			master->setup = spi_bitbang_setup;
			master->cleanup = spi_bitbang_cleanup;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(spi_bitbang_init);

/**
 * spi_bitbang_start - start up a polled/bitbanging SPI master driver
 * @bitbang: driver handle
 *
 * Caller should have zero-initialized all parts of the काष्ठाure, and then
 * provided callbacks क्रम chip selection and I/O loops.  If the master has
 * a transfer method, its final step should call spi_bitbang_transfer; or,
 * that's the शेष अगर the transfer routine is not initialized.  It should
 * also set up the bus number and number of chipselects.
 *
 * For i/o loops, provide callbacks either per-word (क्रम bitbanging, or क्रम
 * hardware that basically exposes a shअगरt रेजिस्टर) or per-spi_transfer
 * (which takes better advantage of hardware like fअगरos or DMA engines).
 *
 * Drivers using per-word I/O loops should use (or call) spi_bitbang_setup,
 * spi_bitbang_cleanup and spi_bitbang_setup_transfer to handle those spi
 * master methods.  Those methods are the शेषs अगर the bitbang->txrx_bufs
 * routine isn't initialized.
 *
 * This routine रेजिस्टरs the spi_master, which will process requests in a
 * dedicated task, keeping IRQs unblocked most of the समय.  To stop
 * processing those requests, call spi_bitbang_stop().
 *
 * On success, this routine will take a reference to master. The caller is
 * responsible क्रम calling spi_bitbang_stop() to decrement the reference and
 * spi_master_put() as counterpart of spi_alloc_master() to prevent a memory
 * leak.
 */
पूर्णांक spi_bitbang_start(काष्ठा spi_bitbang *bitbang)
अणु
	काष्ठा spi_master *master = bitbang->master;
	पूर्णांक ret;

	ret = spi_bitbang_init(bitbang);
	अगर (ret)
		वापस ret;

	/* driver may get busy beक्रमe रेजिस्टर() वापसs, especially
	 * अगर someone रेजिस्टरed boardinfo क्रम devices
	 */
	ret = spi_रेजिस्टर_master(spi_master_get(master));
	अगर (ret)
		spi_master_put(master);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(spi_bitbang_start);

/*
 * spi_bitbang_stop - stops the task providing spi communication
 */
व्योम spi_bitbang_stop(काष्ठा spi_bitbang *bitbang)
अणु
	spi_unरेजिस्टर_master(bitbang->master);
पूर्ण
EXPORT_SYMBOL_GPL(spi_bitbang_stop);

MODULE_LICENSE("GPL");

