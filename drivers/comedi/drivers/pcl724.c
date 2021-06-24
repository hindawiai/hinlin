<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * pcl724.c
 * Comedi driver क्रम 8255 based ISA and PC/104 DIO boards
 *
 * Michal Dobes <करोbes@tesnet.cz>
 */

/*
 * Driver: pcl724
 * Description: Comedi driver क्रम 8255 based ISA DIO boards
 * Devices: [Advantech] PCL-724 (pcl724), PCL-722 (pcl722), PCL-731 (pcl731),
 *  [ADLink] ACL-7122 (acl7122), ACL-7124 (acl7124), PET-48DIO (pet48dio),
 *  [WinSystems] PCM-IO48 (pcmio48),
 *  [Diamond Systems] ONYX-MM-DIO (onyx-mm-dio)
 * Author: Michal Dobes <करोbes@tesnet.cz>
 * Status: untested
 *
 * Configuration options:
 *   [0] - IO Base
 *   [1] - IRQ (not supported)
 *   [2] - number of DIO (pcl722 and acl7122 boards)
 *	   0, 144: 144 DIO configuration
 *	   1,  96:  96 DIO configuration
 */

#समावेश <linux/module.h>
#समावेश "../comedidev.h"

#समावेश "8255.h"

काष्ठा pcl724_board अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक io_range;
	अचिन्हित पूर्णांक can_have96:1;
	अचिन्हित पूर्णांक is_pet48:1;
	पूर्णांक numofports;
पूर्ण;

अटल स्थिर काष्ठा pcl724_board boardtypes[] = अणु
	अणु
		.name		= "pcl724",
		.io_range	= 0x04,
		.numofports	= 1,	/* 24 DIO channels */
	पूर्ण, अणु
		.name		= "pcl722",
		.io_range	= 0x20,
		.can_have96	= 1,
		.numofports	= 6,	/* 144 (or 96) DIO channels */
	पूर्ण, अणु
		.name		= "pcl731",
		.io_range	= 0x08,
		.numofports	= 2,	/* 48 DIO channels */
	पूर्ण, अणु
		.name		= "acl7122",
		.io_range	= 0x20,
		.can_have96	= 1,
		.numofports	= 6,	/* 144 (or 96) DIO channels */
	पूर्ण, अणु
		.name		= "acl7124",
		.io_range	= 0x04,
		.numofports	= 1,	/* 24 DIO channels */
	पूर्ण, अणु
		.name		= "pet48dio",
		.io_range	= 0x02,
		.is_pet48	= 1,
		.numofports	= 2,	/* 48 DIO channels */
	पूर्ण, अणु
		.name		= "pcmio48",
		.io_range	= 0x08,
		.numofports	= 2,	/* 48 DIO channels */
	पूर्ण, अणु
		.name		= "onyx-mm-dio",
		.io_range	= 0x10,
		.numofports	= 2,	/* 48 DIO channels */
	पूर्ण,
पूर्ण;

अटल पूर्णांक pcl724_8255mapped_io(काष्ठा comedi_device *dev,
				पूर्णांक dir, पूर्णांक port, पूर्णांक data,
				अचिन्हित दीर्घ iobase)
अणु
	पूर्णांक movport = I8255_SIZE * (iobase >> 12);

	iobase &= 0x0fff;

	outb(port + movport, iobase);
	अगर (dir) अणु
		outb(data, iobase + 1);
		वापस 0;
	पूर्ण
	वापस inb(iobase + 1);
पूर्ण

अटल पूर्णांक pcl724_attach(काष्ठा comedi_device *dev,
			 काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा pcl724_board *board = dev->board_ptr;
	काष्ठा comedi_subdevice *s;
	अचिन्हित दीर्घ iobase;
	अचिन्हित पूर्णांक iorange;
	पूर्णांक n_subdevices;
	पूर्णांक ret;
	पूर्णांक i;

	iorange = board->io_range;
	n_subdevices = board->numofports;

	/* Handle PCL-724 in 96 DIO configuration */
	अगर (board->can_have96 &&
	    (it->options[2] == 1 || it->options[2] == 96)) अणु
		iorange = 0x10;
		n_subdevices = 4;
	पूर्ण

	ret = comedi_request_region(dev, it->options[0], iorange);
	अगर (ret)
		वापस ret;

	ret = comedi_alloc_subdevices(dev, n_subdevices);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < dev->n_subdevices; i++) अणु
		s = &dev->subdevices[i];
		अगर (board->is_pet48) अणु
			iobase = dev->iobase + (i * 0x1000);
			ret = subdev_8255_init(dev, s, pcl724_8255mapped_io,
					       iobase);
		पूर्ण अन्यथा अणु
			ret = subdev_8255_init(dev, s, शून्य, i * I8255_SIZE);
		पूर्ण
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver pcl724_driver = अणु
	.driver_name	= "pcl724",
	.module		= THIS_MODULE,
	.attach		= pcl724_attach,
	.detach		= comedi_legacy_detach,
	.board_name	= &boardtypes[0].name,
	.num_names	= ARRAY_SIZE(boardtypes),
	.offset		= माप(काष्ठा pcl724_board),
पूर्ण;
module_comedi_driver(pcl724_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for 8255 based ISA and PC/104 DIO boards");
MODULE_LICENSE("GPL");
