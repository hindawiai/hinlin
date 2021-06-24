<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * parport-to-butterfly adapter
 *
 * Copyright (C) 2005 David Brownell
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/parport.h>

#समावेश <linux/sched.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi_bitbang.h>
#समावेश <linux/spi/flash.h>

#समावेश <linux/mtd/partitions.h>

/*
 * This uses SPI to talk with an "AVR Butterfly", which is a $US20 card
 * with a battery घातered AVR microcontroller and lots of goodies.  You
 * can use GCC to develop firmware क्रम this.
 *
 * See Documentation/spi/butterfly.rst क्रम inक्रमmation about how to build
 * and use this custom parallel port cable.
 */

/* DATA output bits (pins 2..9 == D0..D7) */
#घोषणा	butterfly_nreset (1 << 1)		/* pin 3 */

#घोषणा	spi_sck_bit	(1 << 0)		/* pin 2 */
#घोषणा	spi_mosi_bit	(1 << 7)		/* pin 9 */

#घोषणा	vcc_bits	((1 << 6) | (1 << 5))	/* pins 7, 8 */

/* STATUS input bits */
#घोषणा	spi_miso_bit	PARPORT_STATUS_BUSY	/* pin 11 */

/* CONTROL output bits */
#घोषणा	spi_cs_bit	PARPORT_CONTROL_SELECT	/* pin 17 */

अटल अंतरभूत काष्ठा butterfly *spidev_to_pp(काष्ठा spi_device *spi)
अणु
	वापस spi->controller_data;
पूर्ण

काष्ठा butterfly अणु
	/* REVISIT ... क्रम now, this must be first */
	काष्ठा spi_bitbang	bitbang;

	काष्ठा parport		*port;
	काष्ठा pardevice	*pd;

	u8			lastbyte;

	काष्ठा spi_device	*dataflash;
	काष्ठा spi_device	*butterfly;
	काष्ठा spi_board_info	info[2];

पूर्ण;

/*----------------------------------------------------------------------*/

अटल अंतरभूत व्योम
setsck(काष्ठा spi_device *spi, पूर्णांक is_on)
अणु
	काष्ठा butterfly	*pp = spidev_to_pp(spi);
	u8			bit, byte = pp->lastbyte;

	bit = spi_sck_bit;

	अगर (is_on)
		byte |= bit;
	अन्यथा
		byte &= ~bit;
	parport_ग_लिखो_data(pp->port, byte);
	pp->lastbyte = byte;
पूर्ण

अटल अंतरभूत व्योम
seपंचांगosi(काष्ठा spi_device *spi, पूर्णांक is_on)
अणु
	काष्ठा butterfly	*pp = spidev_to_pp(spi);
	u8			bit, byte = pp->lastbyte;

	bit = spi_mosi_bit;

	अगर (is_on)
		byte |= bit;
	अन्यथा
		byte &= ~bit;
	parport_ग_लिखो_data(pp->port, byte);
	pp->lastbyte = byte;
पूर्ण

अटल अंतरभूत पूर्णांक geपंचांगiso(काष्ठा spi_device *spi)
अणु
	काष्ठा butterfly	*pp = spidev_to_pp(spi);
	पूर्णांक			value;
	u8			bit;

	bit = spi_miso_bit;

	/* only STATUS_BUSY is NOT negated */
	value = !(parport_पढ़ो_status(pp->port) & bit);
	वापस (bit == PARPORT_STATUS_BUSY) ? value : !value;
पूर्ण

अटल व्योम butterfly_chipselect(काष्ठा spi_device *spi, पूर्णांक value)
अणु
	काष्ठा butterfly	*pp = spidev_to_pp(spi);

	/* set शेष घड़ी polarity */
	अगर (value != BITBANG_CS_INACTIVE)
		setsck(spi, spi->mode & SPI_CPOL);

	/* here, value == "activate or not";
	 * most PARPORT_CONTROL_* bits are negated, so we must
	 * morph it to value == "bit value to write in control register"
	 */
	अगर (spi_cs_bit == PARPORT_CONTROL_INIT)
		value = !value;

	parport_frob_control(pp->port, spi_cs_bit, value ? spi_cs_bit : 0);
पूर्ण

/* we only needed to implement one mode here, and choose SPI_MODE_0 */

#घोषणा spidelay(X)	करो अणु पूर्ण जबतक (0)
/* #घोषणा spidelay	ndelay */

#समावेश "spi-bitbang-txrx.h"

अटल u32
butterfly_txrx_word_mode0(काष्ठा spi_device *spi, अचिन्हित nsecs, u32 word,
			  u8 bits, अचिन्हित flags)
अणु
	वापस bitbang_txrx_be_cpha0(spi, nsecs, 0, flags, word, bits);
पूर्ण

/*----------------------------------------------------------------------*/

/* override शेष partitioning with cmdlinepart */
अटल काष्ठा mtd_partition partitions[] = अणु अणु
	/* JFFS2 wants partitions of 4*N blocks क्रम this device,
	 * so sectors 0 and 1 can't be partitions by themselves.
	 */

	/* sector 0 = 8 pages * 264 bytes/page (1 block)
	 * sector 1 = 248 pages * 264 bytes/page
	 */
	.name		= "bookkeeping",	/* 66 KB */
	.offset		= 0,
	.size		= (8 + 248) * 264,
	/* .mask_flags	= MTD_WRITEABLE, */
पूर्ण, अणु
	/* sector 2 = 256 pages * 264 bytes/page
	 * sectors 3-5 = 512 pages * 264 bytes/page
	 */
	.name		= "filesystem",		/* 462 KB */
	.offset		= MTDPART_OFS_APPEND,
	.size		= MTDPART_SIZ_FULL,
पूर्ण पूर्ण;

अटल काष्ठा flash_platक्रमm_data flash = अणु
	.name		= "butterflash",
	.parts		= partitions,
	.nr_parts	= ARRAY_SIZE(partitions),
पूर्ण;

/* REVISIT हटाओ this ugly global and its "only one" limitation */
अटल काष्ठा butterfly *butterfly;

अटल व्योम butterfly_attach(काष्ठा parport *p)
अणु
	काष्ठा pardevice	*pd;
	पूर्णांक			status;
	काष्ठा butterfly	*pp;
	काष्ठा spi_master	*master;
	काष्ठा device		*dev = p->physport->dev;
	काष्ठा pardev_cb	butterfly_cb;

	अगर (butterfly || !dev)
		वापस;

	/* REVISIT:  this just _assumes_ a butterfly is there ... no probe,
	 * and no way to be selective about what it binds to.
	 */

	master = spi_alloc_master(dev, माप(*pp));
	अगर (!master) अणु
		status = -ENOMEM;
		जाओ करोne;
	पूर्ण
	pp = spi_master_get_devdata(master);

	/*
	 * SPI and bitbang hookup
	 *
	 * use शेष setup(), cleanup(), and transfer() methods; and
	 * only bother implementing mode 0.  Start it later.
	 */
	master->bus_num = 42;
	master->num_chipselect = 2;

	pp->bitbang.master = master;
	pp->bitbang.chipselect = butterfly_chipselect;
	pp->bitbang.txrx_word[SPI_MODE_0] = butterfly_txrx_word_mode0;

	/*
	 * parport hookup
	 */
	pp->port = p;
	स_रखो(&butterfly_cb, 0, माप(butterfly_cb));
	butterfly_cb.निजी = pp;
	pd = parport_रेजिस्टर_dev_model(p, "spi_butterfly", &butterfly_cb, 0);
	अगर (!pd) अणु
		status = -ENOMEM;
		जाओ clean0;
	पूर्ण
	pp->pd = pd;

	status = parport_claim(pd);
	अगर (status < 0)
		जाओ clean1;

	/*
	 * Butterfly reset, घातerup, run firmware
	 */
	pr_debug("%s: powerup/reset Butterfly\n", p->name);

	/* nCS क्रम dataflash (this bit is inverted on output) */
	parport_frob_control(pp->port, spi_cs_bit, 0);

	/* stabilize घातer with chip in reset (nRESET), and
	 * spi_sck_bit clear (CPOL=0)
	 */
	pp->lastbyte |= vcc_bits;
	parport_ग_लिखो_data(pp->port, pp->lastbyte);
	msleep(5);

	/* take it out of reset; assume दीर्घ reset delay */
	pp->lastbyte |= butterfly_nreset;
	parport_ग_लिखो_data(pp->port, pp->lastbyte);
	msleep(100);

	/*
	 * Start SPI ... क्रम now, hide that we're two physical busses.
	 */
	status = spi_bitbang_start(&pp->bitbang);
	अगर (status < 0)
		जाओ clean2;

	/* Bus 1 lets us talk to at45db041b (firmware disables AVR SPI), AVR
	 * (firmware resets at45, acts as spi slave) or neither (we ignore
	 * both, AVR uses AT45).  Here we expect firmware क्रम the first option.
	 */

	pp->info[0].max_speed_hz = 15 * 1000 * 1000;
	म_नकल(pp->info[0].modalias, "mtd_dataflash");
	pp->info[0].platक्रमm_data = &flash;
	pp->info[0].chip_select = 1;
	pp->info[0].controller_data = pp;
	pp->dataflash = spi_new_device(pp->bitbang.master, &pp->info[0]);
	अगर (pp->dataflash)
		pr_debug("%s: dataflash at %s\n", p->name,
			 dev_name(&pp->dataflash->dev));

	pr_info("%s: AVR Butterfly\n", p->name);
	butterfly = pp;
	वापस;

clean2:
	/* turn off VCC */
	parport_ग_लिखो_data(pp->port, 0);

	parport_release(pp->pd);
clean1:
	parport_unरेजिस्टर_device(pd);
clean0:
	spi_master_put(pp->bitbang.master);
करोne:
	pr_debug("%s: butterfly probe, fail %d\n", p->name, status);
पूर्ण

अटल व्योम butterfly_detach(काष्ठा parport *p)
अणु
	काष्ठा butterfly	*pp;

	/* FIXME this global is ugly ... but, how to quickly get from
	 * the parport to the "struct butterfly" associated with it?
	 * "old school" driver-पूर्णांकernal device lists?
	 */
	अगर (!butterfly || butterfly->port != p)
		वापस;
	pp = butterfly;
	butterfly = शून्य;

	/* stop() unरेजिस्टरs child devices too */
	spi_bitbang_stop(&pp->bitbang);

	/* turn off VCC */
	parport_ग_लिखो_data(pp->port, 0);
	msleep(10);

	parport_release(pp->pd);
	parport_unरेजिस्टर_device(pp->pd);

	spi_master_put(pp->bitbang.master);
पूर्ण

अटल काष्ठा parport_driver butterfly_driver = अणु
	.name =		"spi_butterfly",
	.match_port =	butterfly_attach,
	.detach =	butterfly_detach,
	.devmodel = true,
पूर्ण;
module_parport_driver(butterfly_driver);

MODULE_DESCRIPTION("Parport Adapter driver for AVR Butterfly");
MODULE_LICENSE("GPL");
