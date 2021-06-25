<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  das08_isa.c
 *  comedi driver क्रम DAS08 ISA/PC-104 boards
 *
 *  COMEDI - Linux Control and Measurement Device Interface
 *  Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 *  Copyright (C) 2001,2002,2003 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 *  Copyright (C) 2004 Salvaकरोr E. Tropea <set@users.sf.net> <set@ieee.org>
 */

/*
 * Driver: das08_isa
 * Description: DAS-08 ISA/PC-104 compatible boards
 * Devices: [Keithley Metrabyte] DAS08 (isa-das08),
 *   [ComputerBoards] DAS08 (isa-das08), DAS08-PGM (das08-pgm),
 *   DAS08-PGH (das08-pgh), DAS08-PGL (das08-pgl), DAS08-AOH (das08-aoh),
 *   DAS08-AOL (das08-aol), DAS08-AOM (das08-aom), DAS08/JR-AO (das08/jr-ao),
 *   DAS08/JR-16-AO (das08jr-16-ao), PC104-DAS08 (pc104-das08),
 *   DAS08/JR/16 (das08jr/16)
 * Author: Warren Jasper, ds, Frank Hess
 * Updated: Fri, 31 Aug 2012 19:19:06 +0100
 * Status: works
 *
 * This is the ISA/PC-104-specअगरic support split off from the das08 driver.
 *
 * Configuration Options:
 *	[0] - base io address
 */

#समावेश <linux/module.h>
#समावेश "../comedidev.h"

#समावेश "das08.h"

अटल स्थिर काष्ठा das08_board_काष्ठा das08_isa_boards[] = अणु
	अणु
		/* cio-das08.pdf */
		.name		= "isa-das08",
		.ai_nbits	= 12,
		.ai_pg		= das08_pg_none,
		.ai_encoding	= das08_encode12,
		.di_nchan	= 3,
		.करो_nchan	= 4,
		.i8255_offset	= 8,
		.i8254_offset	= 4,
		.iosize		= 16,		/* unchecked */
	पूर्ण, अणु
		/* cio-das08pgx.pdf */
		.name		= "das08-pgm",
		.ai_nbits	= 12,
		.ai_pg		= das08_pgm,
		.ai_encoding	= das08_encode12,
		.di_nchan	= 3,
		.करो_nchan	= 4,
		.i8255_offset	= 0,
		.i8254_offset	= 0x04,
		.iosize		= 16,		/* unchecked */
	पूर्ण, अणु
		/* cio-das08pgx.pdf */
		.name		= "das08-pgh",
		.ai_nbits	= 12,
		.ai_pg		= das08_pgh,
		.ai_encoding	= das08_encode12,
		.di_nchan	= 3,
		.करो_nchan	= 4,
		.i8254_offset	= 0x04,
		.iosize		= 16,		/* unchecked */
	पूर्ण, अणु
		/* cio-das08pgx.pdf */
		.name		= "das08-pgl",
		.ai_nbits	= 12,
		.ai_pg		= das08_pgl,
		.ai_encoding	= das08_encode12,
		.di_nchan	= 3,
		.करो_nchan	= 4,
		.i8254_offset	= 0x04,
		.iosize		= 16,		/* unchecked */
	पूर्ण, अणु
		/* cio-das08_aox.pdf */
		.name		= "das08-aoh",
		.ai_nbits	= 12,
		.ai_pg		= das08_pgh,
		.ai_encoding	= das08_encode12,
		.ao_nbits	= 12,
		.di_nchan	= 3,
		.करो_nchan	= 4,
		.i8255_offset	= 0x0c,
		.i8254_offset	= 0x04,
		.iosize		= 16,		/* unchecked */
	पूर्ण, अणु
		/* cio-das08_aox.pdf */
		.name		= "das08-aol",
		.ai_nbits	= 12,
		.ai_pg		= das08_pgl,
		.ai_encoding	= das08_encode12,
		.ao_nbits	= 12,
		.di_nchan	= 3,
		.करो_nchan	= 4,
		.i8255_offset	= 0x0c,
		.i8254_offset	= 0x04,
		.iosize		= 16,		/* unchecked */
	पूर्ण, अणु
		/* cio-das08_aox.pdf */
		.name		= "das08-aom",
		.ai_nbits	= 12,
		.ai_pg		= das08_pgm,
		.ai_encoding	= das08_encode12,
		.ao_nbits	= 12,
		.di_nchan	= 3,
		.करो_nchan	= 4,
		.i8255_offset	= 0x0c,
		.i8254_offset	= 0x04,
		.iosize		= 16,		/* unchecked */
	पूर्ण, अणु
		/* cio-das08-jr-ao.pdf */
		.name		= "das08/jr-ao",
		.is_jr		= true,
		.ai_nbits	= 12,
		.ai_pg		= das08_pg_none,
		.ai_encoding	= das08_encode12,
		.ao_nbits	= 12,
		.di_nchan	= 8,
		.करो_nchan	= 8,
		.iosize		= 16,		/* unchecked */
	पूर्ण, अणु
		/* cio-das08jr-16-ao.pdf */
		.name		= "das08jr-16-ao",
		.is_jr		= true,
		.ai_nbits	= 16,
		.ai_pg		= das08_pg_none,
		.ai_encoding	= das08_encode16,
		.ao_nbits	= 16,
		.di_nchan	= 8,
		.करो_nchan	= 8,
		.i8254_offset	= 0x04,
		.iosize		= 16,		/* unchecked */
	पूर्ण, अणु
		.name		= "pc104-das08",
		.ai_nbits	= 12,
		.ai_pg		= das08_pg_none,
		.ai_encoding	= das08_encode12,
		.di_nchan	= 3,
		.करो_nchan	= 4,
		.i8254_offset	= 4,
		.iosize		= 16,		/* unchecked */
	पूर्ण, अणु
		.name		= "das08jr/16",
		.is_jr		= true,
		.ai_nbits	= 16,
		.ai_pg		= das08_pg_none,
		.ai_encoding	= das08_encode16,
		.di_nchan	= 8,
		.करो_nchan	= 8,
		.iosize		= 16,		/* unchecked */
	पूर्ण,
पूर्ण;

अटल पूर्णांक das08_isa_attach(काष्ठा comedi_device *dev,
			    काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा das08_board_काष्ठा *board = dev->board_ptr;
	काष्ठा das08_निजी_काष्ठा *devpriv;
	पूर्णांक ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_request_region(dev, it->options[0], board->iosize);
	अगर (ret)
		वापस ret;

	वापस das08_common_attach(dev, dev->iobase);
पूर्ण

अटल काष्ठा comedi_driver das08_isa_driver = अणु
	.driver_name	= "isa-das08",
	.module		= THIS_MODULE,
	.attach		= das08_isa_attach,
	.detach		= comedi_legacy_detach,
	.board_name	= &das08_isa_boards[0].name,
	.num_names	= ARRAY_SIZE(das08_isa_boards),
	.offset		= माप(das08_isa_boards[0]),
पूर्ण;
module_comedi_driver(das08_isa_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
