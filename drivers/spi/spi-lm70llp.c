<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम LM70EVAL-LLP board क्रम the LM70 sensor
 *
 * Copyright (C) 2006 Kaiwan N Billimoria <kaiwan@designergraphix.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/parport.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi_bitbang.h>

/*
 * The LM70 communicates with a host processor using a 3-wire variant of
 * the SPI/Microwire bus पूर्णांकerface. This driver specअगरically supports an
 * NS LM70 LLP Evaluation Board, पूर्णांकerfacing to a PC using its parallel
 * port to bitbang an SPI-parport bridge.  Accordingly, this is an SPI
 * master controller driver.  The hwmon/lm70 driver is a "SPI protocol
 * driver", layered on top of this one and usable without the lm70llp.
 *
 * Datasheet and Schematic:
 * The LM70 is a temperature sensor chip from National Semiconductor; its
 * datasheet is available at http://www.national.com/pf/LM/LM70.hपंचांगl
 * The schematic क्रम this particular board (the LM70EVAL-LLP) is
 * available (on page 4) here:
 *  http://www.national.com/appinfo/tempsensors/files/LM70LLPEVALmanual.pdf
 *
 * Also see Documentation/spi/spi-lm70llp.rst.  The SPI<->parport code here is
 * (heavily) based on spi-butterfly by David Brownell.
 *
 * The LM70 LLP connects to the PC parallel port in the following manner:
 *
 *   Parallel                 LM70 LLP
 *     Port      Direction   JP2 Header
 *  -----------  ---------  ------------
 *      D0    2      -         -
 *      D1    3     -->      V+   5
 *      D2    4     -->      V+   5
 *      D3    5     -->      V+   5
 *      D4    6     -->      V+   5
 *      D5    7     -->      nCS  8
 *      D6    8     -->      SCLK 3
 *      D7    9     -->      SI/O 5
 *     GND   25      -       GND  7
 *    Select 13     <--      SI/O 1
 *
 * Note that parport pin 13 actually माला_लो inverted by the transistor
 * arrangement which lets either the parport or the LM70 drive the
 * SI/SO संकेत (see the schematic क्रम details).
 */

#घोषणा DRVNAME		"spi-lm70llp"

#घोषणा lm70_INIT	0xBE
#घोषणा SIO		0x10
#घोषणा nCS		0x20
#घोषणा SCLK		0x40

/*-------------------------------------------------------------------------*/

काष्ठा spi_lm70llp अणु
	काष्ठा spi_bitbang	bitbang;
	काष्ठा parport		*port;
	काष्ठा pardevice	*pd;
	काष्ठा spi_device	*spidev_lm70;
	काष्ठा spi_board_info	info;
	//काष्ठा device		*dev;
पूर्ण;

/* REVISIT : ugly global ; provides "exclusive open" facility */
अटल काष्ठा spi_lm70llp *lm70llp;

/*-------------------------------------------------------------------*/

अटल अंतरभूत काष्ठा spi_lm70llp *spidev_to_pp(काष्ठा spi_device *spi)
अणु
	वापस spi->controller_data;
पूर्ण

/*---------------------- LM70 LLP eval board-specअगरic अंतरभूतs follow */

/* NOTE:  we करोn't actually need to reread the output values, since they'll
 * still be what we wrote beक्रमe.  Plus, going through parport builds in
 * a ~1ms/operation delay; these SPI transfers could easily be faster.
 */

अटल अंतरभूत व्योम deनिश्चितCS(काष्ठा spi_lm70llp *pp)
अणु
	u8 data = parport_पढ़ो_data(pp->port);

	data &= ~0x80;		/* pull D7/SI-out low जबतक de-निश्चितed */
	parport_ग_लिखो_data(pp->port, data | nCS);
पूर्ण

अटल अंतरभूत व्योम निश्चितCS(काष्ठा spi_lm70llp *pp)
अणु
	u8 data = parport_पढ़ो_data(pp->port);

	data |= 0x80;		/* pull D7/SI-out high so lm70 drives SO-in */
	parport_ग_लिखो_data(pp->port, data & ~nCS);
पूर्ण

अटल अंतरभूत व्योम clkHigh(काष्ठा spi_lm70llp *pp)
अणु
	u8 data = parport_पढ़ो_data(pp->port);

	parport_ग_लिखो_data(pp->port, data | SCLK);
पूर्ण

अटल अंतरभूत व्योम clkLow(काष्ठा spi_lm70llp *pp)
अणु
	u8 data = parport_पढ़ो_data(pp->port);

	parport_ग_लिखो_data(pp->port, data & ~SCLK);
पूर्ण

/*------------------------- SPI-LM70-specअगरic अंतरभूतs ----------------------*/

अटल अंतरभूत व्योम spidelay(अचिन्हित d)
अणु
	udelay(d);
पूर्ण

अटल अंतरभूत व्योम setsck(काष्ठा spi_device *s, पूर्णांक is_on)
अणु
	काष्ठा spi_lm70llp *pp = spidev_to_pp(s);

	अगर (is_on)
		clkHigh(pp);
	अन्यथा
		clkLow(pp);
पूर्ण

अटल अंतरभूत व्योम seपंचांगosi(काष्ठा spi_device *s, पूर्णांक is_on)
अणु
	/* FIXME update D7 ... this way we can put the chip
	 * पूर्णांकo shutकरोwn mode and पढ़ो the manufacturer ID,
	 * but we can't put it back पूर्णांकo operational mode.
	 */
पूर्ण

/*
 * geपंचांगiso:
 * Why करो we वापस 0 when the SIO line is high and vice-versa?
 * The fact is, the lm70 eval board from NS (which this driver drives),
 * is wired in just such a way : when the lm70's SIO goes high, a transistor
 * चयनes it to low reflecting this on the parport (pin 13), and vice-versa.
 */
अटल अंतरभूत पूर्णांक geपंचांगiso(काष्ठा spi_device *s)
अणु
	काष्ठा spi_lm70llp *pp = spidev_to_pp(s);

	वापस ((SIO == (parport_पढ़ो_status(pp->port) & SIO)) ? 0 : 1);
पूर्ण

/*--------------------------------------------------------------------*/

#समावेश "spi-bitbang-txrx.h"

अटल व्योम lm70_chipselect(काष्ठा spi_device *spi, पूर्णांक value)
अणु
	काष्ठा spi_lm70llp *pp = spidev_to_pp(spi);

	अगर (value)
		निश्चितCS(pp);
	अन्यथा
		deनिश्चितCS(pp);
पूर्ण

/*
 * Our actual bitbanger routine.
 */
अटल u32 lm70_txrx(काष्ठा spi_device *spi, अचिन्हित nsecs, u32 word, u8 bits,
		     अचिन्हित flags)
अणु
	वापस bitbang_txrx_be_cpha0(spi, nsecs, 0, flags, word, bits);
पूर्ण

अटल व्योम spi_lm70llp_attach(काष्ठा parport *p)
अणु
	काष्ठा pardevice	*pd;
	काष्ठा spi_lm70llp	*pp;
	काष्ठा spi_master	*master;
	पूर्णांक			status;
	काष्ठा pardev_cb	lm70llp_cb;

	अगर (lm70llp) अणु
		pr_warn("spi_lm70llp instance already loaded. Aborting.\n");
		वापस;
	पूर्ण

	/* TODO:  this just _assumes_ a lm70 is there ... no probe;
	 * the lm70 driver could verअगरy it, पढ़ोing the manf ID.
	 */

	master = spi_alloc_master(p->physport->dev, माप *pp);
	अगर (!master) अणु
		status = -ENOMEM;
		जाओ out_fail;
	पूर्ण
	pp = spi_master_get_devdata(master);

	/*
	 * SPI and bitbang hookup.
	 */
	pp->bitbang.master = master;
	pp->bitbang.chipselect = lm70_chipselect;
	pp->bitbang.txrx_word[SPI_MODE_0] = lm70_txrx;
	pp->bitbang.flags = SPI_3WIRE;

	/*
	 * Parport hookup
	 */
	pp->port = p;
	स_रखो(&lm70llp_cb, 0, माप(lm70llp_cb));
	lm70llp_cb.निजी = pp;
	lm70llp_cb.flags = PARPORT_FLAG_EXCL;
	pd = parport_रेजिस्टर_dev_model(p, DRVNAME, &lm70llp_cb, 0);

	अगर (!pd) अणु
		status = -ENOMEM;
		जाओ out_मुक्त_master;
	पूर्ण
	pp->pd = pd;

	status = parport_claim(pd);
	अगर (status < 0)
		जाओ out_parport_unreg;

	/*
	 * Start SPI ...
	 */
	status = spi_bitbang_start(&pp->bitbang);
	अगर (status < 0) अणु
		dev_warn(&pd->dev, "spi_bitbang_start failed with status %d\n",
			 status);
		जाओ out_off_and_release;
	पूर्ण

	/*
	 * The modalias name MUST match the device_driver name
	 * क्रम the bus glue code to match and subsequently bind them.
	 * We are binding to the generic drivers/hwmon/lm70.c device
	 * driver.
	 */
	म_नकल(pp->info.modalias, "lm70");
	pp->info.max_speed_hz = 6 * 1000 * 1000;
	pp->info.chip_select = 0;
	pp->info.mode = SPI_3WIRE | SPI_MODE_0;

	/* घातer up the chip, and let the LM70 control SI/SO */
	parport_ग_लिखो_data(pp->port, lm70_INIT);

	/* Enable access to our primary data काष्ठाure via
	 * the board info's (व्योम *)controller_data.
	 */
	pp->info.controller_data = pp;
	pp->spidev_lm70 = spi_new_device(pp->bitbang.master, &pp->info);
	अगर (pp->spidev_lm70)
		dev_dbg(&pp->spidev_lm70->dev, "spidev_lm70 at %s\n",
			dev_name(&pp->spidev_lm70->dev));
	अन्यथा अणु
		dev_warn(&pd->dev, "spi_new_device failed\n");
		status = -ENODEV;
		जाओ out_bitbang_stop;
	पूर्ण
	pp->spidev_lm70->bits_per_word = 8;

	lm70llp = pp;
	वापस;

out_bitbang_stop:
	spi_bitbang_stop(&pp->bitbang);
out_off_and_release:
	/* घातer करोwn */
	parport_ग_लिखो_data(pp->port, 0);
	mdelay(10);
	parport_release(pp->pd);
out_parport_unreg:
	parport_unरेजिस्टर_device(pd);
out_मुक्त_master:
	spi_master_put(master);
out_fail:
	pr_info("spi_lm70llp probe fail, status %d\n", status);
पूर्ण

अटल व्योम spi_lm70llp_detach(काष्ठा parport *p)
अणु
	काष्ठा spi_lm70llp		*pp;

	अगर (!lm70llp || lm70llp->port != p)
		वापस;

	pp = lm70llp;
	spi_bitbang_stop(&pp->bitbang);

	/* घातer करोwn */
	parport_ग_लिखो_data(pp->port, 0);

	parport_release(pp->pd);
	parport_unरेजिस्टर_device(pp->pd);

	spi_master_put(pp->bitbang.master);

	lm70llp = शून्य;
पूर्ण

अटल काष्ठा parport_driver spi_lm70llp_drv = अणु
	.name =		DRVNAME,
	.match_port =	spi_lm70llp_attach,
	.detach =	spi_lm70llp_detach,
	.devmodel =	true,
पूर्ण;
module_parport_driver(spi_lm70llp_drv);

MODULE_AUTHOR("Kaiwan N Billimoria <kaiwan@designergraphix.com>");
MODULE_DESCRIPTION(
	"Parport adapter for the National Semiconductor LM70 LLP eval board");
MODULE_LICENSE("GPL");
