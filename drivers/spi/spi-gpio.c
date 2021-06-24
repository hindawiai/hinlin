<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SPI master driver using generic bitbanged GPIO
 *
 * Copyright (C) 2006,2008 David Brownell
 * Copyright (C) 2017 Linus Walleij
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi_bitbang.h>
#समावेश <linux/spi/spi_gpपन.स>


/*
 * This bitbanging SPI master driver should help make प्रणालीs usable
 * when a native hardware SPI engine is not available, perhaps because
 * its driver isn't yet working or because the I/O pins it requires
 * are used क्रम other purposes.
 *
 * platक्रमm_device->driver_data ... poपूर्णांकs to spi_gpio
 *
 * spi->controller_state ... reserved क्रम bitbang framework code
 *
 * spi->master->dev.driver_data ... poपूर्णांकs to spi_gpio->bitbang
 */

काष्ठा spi_gpio अणु
	काष्ठा spi_bitbang		bitbang;
	काष्ठा gpio_desc		*sck;
	काष्ठा gpio_desc		*miso;
	काष्ठा gpio_desc		*mosi;
	काष्ठा gpio_desc		**cs_gpios;
पूर्ण;

/*----------------------------------------------------------------------*/

/*
 * Because the overhead of going through four GPIO procedure calls
 * per transferred bit can make perक्रमmance a problem, this code
 * is set up so that you can use it in either of two ways:
 *
 *   - The slow generic way:  set up platक्रमm_data to hold the GPIO
 *     numbers used क्रम MISO/MOSI/SCK, and issue procedure calls क्रम
 *     each of them.  This driver can handle several such busses.
 *
 *   - The quicker अंतरभूतd way:  only helps with platक्रमm GPIO code
 *     that अंतरभूतs operations क्रम स्थिरant GPIOs.  This can give
 *     you tight (fast!) inner loops, but each such bus needs a
 *     new driver.  You'll define a new C file, with Makefile and
 *     Kconfig support; the C code can be a total of six lines:
 *
 *		#घोषणा DRIVER_NAME	"myboard_spi2"
 *		#घोषणा	SPI_MISO_GPIO	119
 *		#घोषणा	SPI_MOSI_GPIO	120
 *		#घोषणा	SPI_SCK_GPIO	121
 *		#घोषणा	SPI_N_CHIPSEL	4
 *		#समावेश "spi-gpio.c"
 */

#अगर_अघोषित DRIVER_NAME
#घोषणा DRIVER_NAME	"spi_gpio"

#घोषणा GENERIC_BITBANG	/* vs tight अंतरभूतs */

#पूर्ण_अगर

/*----------------------------------------------------------------------*/

अटल अंतरभूत काष्ठा spi_gpio *__pure
spi_to_spi_gpio(स्थिर काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_bitbang	*bang;
	काष्ठा spi_gpio			*spi_gpio;

	bang = spi_master_get_devdata(spi->master);
	spi_gpio = container_of(bang, काष्ठा spi_gpio, bitbang);
	वापस spi_gpio;
पूर्ण

/* These helpers are in turn called by the bitbang अंतरभूतs */
अटल अंतरभूत व्योम setsck(स्थिर काष्ठा spi_device *spi, पूर्णांक is_on)
अणु
	काष्ठा spi_gpio *spi_gpio = spi_to_spi_gpio(spi);

	gpiod_set_value_cansleep(spi_gpio->sck, is_on);
पूर्ण

अटल अंतरभूत व्योम seपंचांगosi(स्थिर काष्ठा spi_device *spi, पूर्णांक is_on)
अणु
	काष्ठा spi_gpio *spi_gpio = spi_to_spi_gpio(spi);

	gpiod_set_value_cansleep(spi_gpio->mosi, is_on);
पूर्ण

अटल अंतरभूत पूर्णांक geपंचांगiso(स्थिर काष्ठा spi_device *spi)
अणु
	काष्ठा spi_gpio *spi_gpio = spi_to_spi_gpio(spi);

	अगर (spi->mode & SPI_3WIRE)
		वापस !!gpiod_get_value_cansleep(spi_gpio->mosi);
	अन्यथा
		वापस !!gpiod_get_value_cansleep(spi_gpio->miso);
पूर्ण

/*
 * NOTE:  this घड़ीs "as fast as we can".  It "should" be a function of the
 * requested device घड़ी.  Software overhead means we usually have trouble
 * reaching even one Mbit/sec (except when we can अंतरभूत bitops), so क्रम now
 * we'll just assume we never need additional per-bit slowकरोwns.
 */
#घोषणा spidelay(nsecs)	करो अणुपूर्ण जबतक (0)

#समावेश "spi-bitbang-txrx.h"

/*
 * These functions can leverage अंतरभूत expansion of GPIO calls to shrink
 * costs क्रम a txrx bit, often by factors of around ten (by inकाष्ठाion
 * count).  That is particularly visible क्रम larger word sizes, but helps
 * even with शेष 8-bit words.
 *
 * REVISIT overheads calling these functions क्रम each word also have
 * signअगरicant perक्रमmance costs.  Having txrx_bufs() calls that अंतरभूत
 * the txrx_word() logic would help perक्रमmance, e.g. on larger blocks
 * used with flash storage or MMC/SD.  There should also be ways to make
 * GCC be less stupid about reloading रेजिस्टरs inside the I/O loops,
 * even without अंतरभूतd GPIO calls; __attribute__((hot)) on GCC 4.3?
 */

अटल u32 spi_gpio_txrx_word_mode0(काष्ठा spi_device *spi,
		अचिन्हित nsecs, u32 word, u8 bits, अचिन्हित flags)
अणु
	वापस bitbang_txrx_be_cpha0(spi, nsecs, 0, flags, word, bits);
पूर्ण

अटल u32 spi_gpio_txrx_word_mode1(काष्ठा spi_device *spi,
		अचिन्हित nsecs, u32 word, u8 bits, अचिन्हित flags)
अणु
	वापस bitbang_txrx_be_cpha1(spi, nsecs, 0, flags, word, bits);
पूर्ण

अटल u32 spi_gpio_txrx_word_mode2(काष्ठा spi_device *spi,
		अचिन्हित nsecs, u32 word, u8 bits, अचिन्हित flags)
अणु
	वापस bitbang_txrx_be_cpha0(spi, nsecs, 1, flags, word, bits);
पूर्ण

अटल u32 spi_gpio_txrx_word_mode3(काष्ठा spi_device *spi,
		अचिन्हित nsecs, u32 word, u8 bits, अचिन्हित flags)
अणु
	वापस bitbang_txrx_be_cpha1(spi, nsecs, 1, flags, word, bits);
पूर्ण

/*
 * These functions करो not call seपंचांगosi or geपंचांगiso अगर respective flag
 * (SPI_MASTER_NO_RX or SPI_MASTER_NO_TX) is set, so they are safe to
 * call when such pin is not present or defined in the controller.
 * A separate set of callbacks is defined to get highest possible
 * speed in the generic हाल (when both MISO and MOSI lines are
 * available), as optimiser will हटाओ the checks when argument is
 * स्थिरant.
 */

अटल u32 spi_gpio_spec_txrx_word_mode0(काष्ठा spi_device *spi,
		अचिन्हित nsecs, u32 word, u8 bits, अचिन्हित flags)
अणु
	flags = spi->master->flags;
	वापस bitbang_txrx_be_cpha0(spi, nsecs, 0, flags, word, bits);
पूर्ण

अटल u32 spi_gpio_spec_txrx_word_mode1(काष्ठा spi_device *spi,
		अचिन्हित nsecs, u32 word, u8 bits, अचिन्हित flags)
अणु
	flags = spi->master->flags;
	वापस bitbang_txrx_be_cpha1(spi, nsecs, 0, flags, word, bits);
पूर्ण

अटल u32 spi_gpio_spec_txrx_word_mode2(काष्ठा spi_device *spi,
		अचिन्हित nsecs, u32 word, u8 bits, अचिन्हित flags)
अणु
	flags = spi->master->flags;
	वापस bitbang_txrx_be_cpha0(spi, nsecs, 1, flags, word, bits);
पूर्ण

अटल u32 spi_gpio_spec_txrx_word_mode3(काष्ठा spi_device *spi,
		अचिन्हित nsecs, u32 word, u8 bits, अचिन्हित flags)
अणु
	flags = spi->master->flags;
	वापस bitbang_txrx_be_cpha1(spi, nsecs, 1, flags, word, bits);
पूर्ण

/*----------------------------------------------------------------------*/

अटल व्योम spi_gpio_chipselect(काष्ठा spi_device *spi, पूर्णांक is_active)
अणु
	काष्ठा spi_gpio *spi_gpio = spi_to_spi_gpio(spi);

	/* set initial घड़ी line level */
	अगर (is_active)
		gpiod_set_value_cansleep(spi_gpio->sck, spi->mode & SPI_CPOL);

	/* Drive chip select line, अगर we have one */
	अगर (spi_gpio->cs_gpios) अणु
		काष्ठा gpio_desc *cs = spi_gpio->cs_gpios[spi->chip_select];

		/* SPI chip selects are normally active-low */
		gpiod_set_value_cansleep(cs, (spi->mode & SPI_CS_HIGH) ? is_active : !is_active);
	पूर्ण
पूर्ण

अटल पूर्णांक spi_gpio_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा gpio_desc	*cs;
	पूर्णांक			status = 0;
	काष्ठा spi_gpio		*spi_gpio = spi_to_spi_gpio(spi);

	/*
	 * The CS GPIOs have alपढ़ोy been
	 * initialized from the descriptor lookup.
	 */
	अगर (spi_gpio->cs_gpios) अणु
		cs = spi_gpio->cs_gpios[spi->chip_select];
		अगर (!spi->controller_state && cs)
			status = gpiod_direction_output(cs,
						  !(spi->mode & SPI_CS_HIGH));
	पूर्ण

	अगर (!status)
		status = spi_bitbang_setup(spi);

	वापस status;
पूर्ण

अटल पूर्णांक spi_gpio_set_direction(काष्ठा spi_device *spi, bool output)
अणु
	काष्ठा spi_gpio *spi_gpio = spi_to_spi_gpio(spi);
	पूर्णांक ret;

	अगर (output)
		वापस gpiod_direction_output(spi_gpio->mosi, 1);

	ret = gpiod_direction_input(spi_gpio->mosi);
	अगर (ret)
		वापस ret;
	/*
	 * Send a turnaround high impedance cycle when चयनing
	 * from output to input. Theoretically there should be
	 * a घड़ी delay here, but as has been noted above, the
	 * nsec delay function क्रम bit-banged GPIO is simply
	 * अणुपूर्ण because bit-banging just करोesn't get fast enough
	 * anyway.
	 */
	अगर (spi->mode & SPI_3WIRE_HIZ) अणु
		gpiod_set_value_cansleep(spi_gpio->sck,
					 !(spi->mode & SPI_CPOL));
		gpiod_set_value_cansleep(spi_gpio->sck,
					 !!(spi->mode & SPI_CPOL));
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम spi_gpio_cleanup(काष्ठा spi_device *spi)
अणु
	spi_bitbang_cleanup(spi);
पूर्ण

/*
 * It can be convenient to use this driver with pins that have alternate
 * functions associated with a "native" SPI controller अगर a driver क्रम that
 * controller is not available, or is missing important functionality.
 *
 * On platक्रमms which can करो so, configure MISO with a weak pullup unless
 * there's an बाह्यal pullup on that संकेत.  That saves घातer by aव्योमing
 * भग्नing संकेतs.  (A weak pullकरोwn would save घातer too, but many
 * drivers expect to see all-ones data as the no slave "response".)
 */
अटल पूर्णांक spi_gpio_request(काष्ठा device *dev, काष्ठा spi_gpio *spi_gpio)
अणु
	spi_gpio->mosi = devm_gpiod_get_optional(dev, "mosi", GPIOD_OUT_LOW);
	अगर (IS_ERR(spi_gpio->mosi))
		वापस PTR_ERR(spi_gpio->mosi);

	spi_gpio->miso = devm_gpiod_get_optional(dev, "miso", GPIOD_IN);
	अगर (IS_ERR(spi_gpio->miso))
		वापस PTR_ERR(spi_gpio->miso);

	spi_gpio->sck = devm_gpiod_get(dev, "sck", GPIOD_OUT_LOW);
	वापस PTR_ERR_OR_ZERO(spi_gpio->sck);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id spi_gpio_dt_ids[] = अणु
	अणु .compatible = "spi-gpio" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, spi_gpio_dt_ids);

अटल पूर्णांक spi_gpio_probe_dt(काष्ठा platक्रमm_device *pdev,
			     काष्ठा spi_master *master)
अणु
	master->dev.of_node = pdev->dev.of_node;
	master->use_gpio_descriptors = true;

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक spi_gpio_probe_dt(काष्ठा platक्रमm_device *pdev,
				    काष्ठा spi_master *master)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक spi_gpio_probe_pdata(काष्ठा platक्रमm_device *pdev,
				काष्ठा spi_master *master)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा spi_gpio_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा spi_gpio *spi_gpio = spi_master_get_devdata(master);
	पूर्णांक i;

#अगर_घोषित GENERIC_BITBANG
	अगर (!pdata || !pdata->num_chipselect)
		वापस -ENODEV;
#पूर्ण_अगर
	/*
	 * The master needs to think there is a chipselect even अगर not
	 * connected
	 */
	master->num_chipselect = pdata->num_chipselect ?: 1;

	spi_gpio->cs_gpios = devm_kसुस्मृति(dev, master->num_chipselect,
					  माप(*spi_gpio->cs_gpios),
					  GFP_KERNEL);
	अगर (!spi_gpio->cs_gpios)
		वापस -ENOMEM;

	क्रम (i = 0; i < master->num_chipselect; i++) अणु
		spi_gpio->cs_gpios[i] = devm_gpiod_get_index(dev, "cs", i,
							     GPIOD_OUT_HIGH);
		अगर (IS_ERR(spi_gpio->cs_gpios[i]))
			वापस PTR_ERR(spi_gpio->cs_gpios[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक spi_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक				status;
	काष्ठा spi_master		*master;
	काष्ठा spi_gpio			*spi_gpio;
	काष्ठा device			*dev = &pdev->dev;
	काष्ठा spi_bitbang		*bb;

	master = devm_spi_alloc_master(dev, माप(*spi_gpio));
	अगर (!master)
		वापस -ENOMEM;

	अगर (pdev->dev.of_node)
		status = spi_gpio_probe_dt(pdev, master);
	अन्यथा
		status = spi_gpio_probe_pdata(pdev, master);

	अगर (status)
		वापस status;

	spi_gpio = spi_master_get_devdata(master);

	status = spi_gpio_request(dev, spi_gpio);
	अगर (status)
		वापस status;

	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(1, 32);
	master->mode_bits = SPI_3WIRE | SPI_3WIRE_HIZ | SPI_CPHA | SPI_CPOL |
			    SPI_CS_HIGH;
	अगर (!spi_gpio->mosi) अणु
		/* HW configuration without MOSI pin
		 *
		 * No setting SPI_MASTER_NO_RX here - अगर there is only
		 * a MOSI pin connected the host can still करो RX by
		 * changing the direction of the line.
		 */
		master->flags = SPI_MASTER_NO_TX;
	पूर्ण

	master->bus_num = pdev->id;
	master->setup = spi_gpio_setup;
	master->cleanup = spi_gpio_cleanup;

	bb = &spi_gpio->bitbang;
	bb->master = master;
	/*
	 * There is some additional business, apart from driving the CS GPIO
	 * line, that we need to करो on selection. This makes the local
	 * callback क्रम chipselect always get called.
	 */
	master->flags |= SPI_MASTER_GPIO_SS;
	bb->chipselect = spi_gpio_chipselect;
	bb->set_line_direction = spi_gpio_set_direction;

	अगर (master->flags & SPI_MASTER_NO_TX) अणु
		bb->txrx_word[SPI_MODE_0] = spi_gpio_spec_txrx_word_mode0;
		bb->txrx_word[SPI_MODE_1] = spi_gpio_spec_txrx_word_mode1;
		bb->txrx_word[SPI_MODE_2] = spi_gpio_spec_txrx_word_mode2;
		bb->txrx_word[SPI_MODE_3] = spi_gpio_spec_txrx_word_mode3;
	पूर्ण अन्यथा अणु
		bb->txrx_word[SPI_MODE_0] = spi_gpio_txrx_word_mode0;
		bb->txrx_word[SPI_MODE_1] = spi_gpio_txrx_word_mode1;
		bb->txrx_word[SPI_MODE_2] = spi_gpio_txrx_word_mode2;
		bb->txrx_word[SPI_MODE_3] = spi_gpio_txrx_word_mode3;
	पूर्ण
	bb->setup_transfer = spi_bitbang_setup_transfer;

	status = spi_bitbang_init(&spi_gpio->bitbang);
	अगर (status)
		वापस status;

	वापस devm_spi_रेजिस्टर_master(&pdev->dev, master);
पूर्ण

MODULE_ALIAS("platform:" DRIVER_NAME);

अटल काष्ठा platक्रमm_driver spi_gpio_driver = अणु
	.driver = अणु
		.name	= DRIVER_NAME,
		.of_match_table = of_match_ptr(spi_gpio_dt_ids),
	पूर्ण,
	.probe		= spi_gpio_probe,
पूर्ण;
module_platक्रमm_driver(spi_gpio_driver);

MODULE_DESCRIPTION("SPI master driver using generic bitbanged GPIO ");
MODULE_AUTHOR("David Brownell");
MODULE_LICENSE("GPL");
