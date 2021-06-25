<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * comedi/drivers/pcl730.c
 * Driver क्रम Advantech PCL-730 and clones
 * Josथऊ Luis Sथँnchez
 */

/*
 * Driver: pcl730
 * Description: Advantech PCL-730 (& compatibles)
 * Devices: [Advantech] PCL-730 (pcl730), PCM-3730 (pcm3730), PCL-725 (pcl725),
 *   PCL-733 (pcl733), PCL-734 (pcl734),
 *   [ADLink] ACL-7130 (acl7130), ACL-7225b (acl7225b),
 *   [ICP] ISO-730 (iso730), P8R8-DIO (p8r8dio), P16R16-DIO (p16r16dio),
 *   [Diamond Systems] OPMM-1616-XT (opmm-1616-xt), PEARL-MM-P (pearl-mm-p),
 *   IR104-PBF (ir104-pbf),
 * Author: Josथऊ Luis Sथँnchez (jsanchezv@teleline.es)
 * Status: untested
 *
 * Configuration options:
 *   [0] - I/O port base
 *
 * Interrupts are not supported.
 * The ACL-7130 card has an 8254 समयr/counter not supported by this driver.
 */

#समावेश <linux/module.h>
#समावेश "../comedidev.h"

/*
 * Register map
 *
 * The रेजिस्टर map varies slightly depending on the board type but
 * all रेजिस्टरs are 8-bit.
 *
 * The boardinfo 'io_range' is used to allow comedi to request the
 * proper range required by the board.
 *
 * The comedi_subdevice 'private' data is used to pass the रेजिस्टर
 * offset to the (*insn_bits) functions to पढ़ो/ग_लिखो the correct
 * रेजिस्टरs.
 *
 * The basic रेजिस्टर mapping looks like this:
 *
 *     BASE+0  Isolated outमाला_दो 0-7 (ग_लिखो) / inमाला_दो 0-7 (पढ़ो)
 *     BASE+1  Isolated outमाला_दो 8-15 (ग_लिखो) / inमाला_दो 8-15 (पढ़ो)
 *     BASE+2  TTL outमाला_दो 0-7 (ग_लिखो) / inमाला_दो 0-7 (पढ़ो)
 *     BASE+3  TTL outमाला_दो 8-15 (ग_लिखो) / inमाला_दो 8-15 (पढ़ो)
 *
 * The pcm3730 board करोes not have रेजिस्टर BASE+1.
 *
 * The pcl725 and p8r8dio only have रेजिस्टरs BASE+0 and BASE+1:
 *
 *     BASE+0  Isolated outमाला_दो 0-7 (ग_लिखो) (पढ़ो back on p8r8dio)
 *     BASE+1  Isolated inमाला_दो 0-7 (पढ़ो)
 *
 * The acl7225b and p16r16dio boards have this रेजिस्टर mapping:
 *
 *     BASE+0  Isolated outमाला_दो 0-7 (ग_लिखो) (पढ़ो back)
 *     BASE+1  Isolated outमाला_दो 8-15 (ग_लिखो) (पढ़ो back)
 *     BASE+2  Isolated inमाला_दो 0-7 (पढ़ो)
 *     BASE+3  Isolated inमाला_दो 8-15 (पढ़ो)
 *
 * The pcl733 and pcl733 boards have this रेजिस्टर mapping:
 *
 *     BASE+0  Isolated outमाला_दो 0-7 (ग_लिखो) or inमाला_दो 0-7 (पढ़ो)
 *     BASE+1  Isolated outमाला_दो 8-15 (ग_लिखो) or inमाला_दो 8-15 (पढ़ो)
 *     BASE+2  Isolated outमाला_दो 16-23 (ग_लिखो) or inमाला_दो 16-23 (पढ़ो)
 *     BASE+3  Isolated outमाला_दो 24-31 (ग_लिखो) or inमाला_दो 24-31 (पढ़ो)
 *
 * The opmm-1616-xt board has this रेजिस्टर mapping:
 *
 *     BASE+0  Isolated outमाला_दो 0-7 (ग_लिखो) (पढ़ो back)
 *     BASE+1  Isolated outमाला_दो 8-15 (ग_लिखो) (पढ़ो back)
 *     BASE+2  Isolated inमाला_दो 0-7 (पढ़ो)
 *     BASE+3  Isolated inमाला_दो 8-15 (पढ़ो)
 *
 *     These रेजिस्टरs are not currently supported:
 *
 *     BASE+2  Relay select रेजिस्टर (ग_लिखो)
 *     BASE+3  Board reset control रेजिस्टर (ग_लिखो)
 *     BASE+4  Interrupt control रेजिस्टर (ग_लिखो)
 *     BASE+4  Change detect 7-0 status रेजिस्टर (पढ़ो)
 *     BASE+5  LED control रेजिस्टर (ग_लिखो)
 *     BASE+5  Change detect 15-8 status रेजिस्टर (पढ़ो)
 *
 * The pearl-mm-p board has this रेजिस्टर mapping:
 *
 *     BASE+0  Isolated outमाला_दो 0-7 (ग_लिखो)
 *     BASE+1  Isolated outमाला_दो 8-15 (ग_लिखो)
 *
 * The ir104-pbf board has this रेजिस्टर mapping:
 *
 *     BASE+0  Isolated outमाला_दो 0-7 (ग_लिखो) (पढ़ो back)
 *     BASE+1  Isolated outमाला_दो 8-15 (ग_लिखो) (पढ़ो back)
 *     BASE+2  Isolated outमाला_दो 16-19 (ग_लिखो) (पढ़ो back)
 *     BASE+4  Isolated inमाला_दो 0-7 (पढ़ो)
 *     BASE+5  Isolated inमाला_दो 8-15 (पढ़ो)
 *     BASE+6  Isolated inमाला_दो 16-19 (पढ़ो)
 */

काष्ठा pcl730_board अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक io_range;
	अचिन्हित is_pcl725:1;
	अचिन्हित is_acl7225b:1;
	अचिन्हित is_ir104:1;
	अचिन्हित has_पढ़ोback:1;
	अचिन्हित has_ttl_io:1;
	पूर्णांक n_subdevs;
	पूर्णांक n_iso_out_chan;
	पूर्णांक n_iso_in_chan;
	पूर्णांक n_ttl_chan;
पूर्ण;

अटल स्थिर काष्ठा pcl730_board pcl730_boards[] = अणु
	अणु
		.name		= "pcl730",
		.io_range	= 0x04,
		.has_ttl_io	= 1,
		.n_subdevs	= 4,
		.n_iso_out_chan	= 16,
		.n_iso_in_chan	= 16,
		.n_ttl_chan	= 16,
	पूर्ण, अणु
		.name		= "iso730",
		.io_range	= 0x04,
		.n_subdevs	= 4,
		.n_iso_out_chan	= 16,
		.n_iso_in_chan	= 16,
		.n_ttl_chan	= 16,
	पूर्ण, अणु
		.name		= "acl7130",
		.io_range	= 0x08,
		.has_ttl_io	= 1,
		.n_subdevs	= 4,
		.n_iso_out_chan	= 16,
		.n_iso_in_chan	= 16,
		.n_ttl_chan	= 16,
	पूर्ण, अणु
		.name		= "pcm3730",
		.io_range	= 0x04,
		.has_ttl_io	= 1,
		.n_subdevs	= 4,
		.n_iso_out_chan	= 8,
		.n_iso_in_chan	= 8,
		.n_ttl_chan	= 16,
	पूर्ण, अणु
		.name		= "pcl725",
		.io_range	= 0x02,
		.is_pcl725	= 1,
		.n_subdevs	= 2,
		.n_iso_out_chan	= 8,
		.n_iso_in_chan	= 8,
	पूर्ण, अणु
		.name		= "p8r8dio",
		.io_range	= 0x02,
		.is_pcl725	= 1,
		.has_पढ़ोback	= 1,
		.n_subdevs	= 2,
		.n_iso_out_chan	= 8,
		.n_iso_in_chan	= 8,
	पूर्ण, अणु
		.name		= "acl7225b",
		.io_range	= 0x08,		/* only 4 are used */
		.is_acl7225b	= 1,
		.has_पढ़ोback	= 1,
		.n_subdevs	= 2,
		.n_iso_out_chan	= 16,
		.n_iso_in_chan	= 16,
	पूर्ण, अणु
		.name		= "p16r16dio",
		.io_range	= 0x04,
		.is_acl7225b	= 1,
		.has_पढ़ोback	= 1,
		.n_subdevs	= 2,
		.n_iso_out_chan	= 16,
		.n_iso_in_chan	= 16,
	पूर्ण, अणु
		.name		= "pcl733",
		.io_range	= 0x04,
		.n_subdevs	= 1,
		.n_iso_in_chan	= 32,
	पूर्ण, अणु
		.name		= "pcl734",
		.io_range	= 0x04,
		.n_subdevs	= 1,
		.n_iso_out_chan	= 32,
	पूर्ण, अणु
		.name		= "opmm-1616-xt",
		.io_range	= 0x10,
		.is_acl7225b	= 1,
		.has_पढ़ोback	= 1,
		.n_subdevs	= 2,
		.n_iso_out_chan	= 16,
		.n_iso_in_chan	= 16,
	पूर्ण, अणु
		.name		= "pearl-mm-p",
		.io_range	= 0x02,
		.n_subdevs	= 1,
		.n_iso_out_chan	= 16,
	पूर्ण, अणु
		.name		= "ir104-pbf",
		.io_range	= 0x08,
		.is_ir104	= 1,
		.has_पढ़ोback	= 1,
		.n_iso_out_chan	= 20,
		.n_iso_in_chan	= 20,
	पूर्ण,
पूर्ण;

अटल पूर्णांक pcl730_करो_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित दीर्घ reg = (अचिन्हित दीर्घ)s->निजी;
	अचिन्हित पूर्णांक mask;

	mask = comedi_dio_update_state(s, data);
	अगर (mask) अणु
		अगर (mask & 0x00ff)
			outb(s->state & 0xff, dev->iobase + reg);
		अगर ((mask & 0xff00) && (s->n_chan > 8))
			outb((s->state >> 8) & 0xff, dev->iobase + reg + 1);
		अगर ((mask & 0xff0000) && (s->n_chan > 16))
			outb((s->state >> 16) & 0xff, dev->iobase + reg + 2);
		अगर ((mask & 0xff000000) && (s->n_chan > 24))
			outb((s->state >> 24) & 0xff, dev->iobase + reg + 3);
	पूर्ण

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल अचिन्हित पूर्णांक pcl730_get_bits(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित दीर्घ reg = (अचिन्हित दीर्घ)s->निजी;
	अचिन्हित पूर्णांक val;

	val = inb(dev->iobase + reg);
	अगर (s->n_chan > 8)
		val |= (inb(dev->iobase + reg + 1) << 8);
	अगर (s->n_chan > 16)
		val |= (inb(dev->iobase + reg + 2) << 16);
	अगर (s->n_chan > 24)
		val |= (inb(dev->iobase + reg + 3) << 24);

	वापस val;
पूर्ण

अटल पूर्णांक pcl730_di_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	data[1] = pcl730_get_bits(dev, s);

	वापस insn->n;
पूर्ण

अटल पूर्णांक pcl730_attach(काष्ठा comedi_device *dev,
			 काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा pcl730_board *board = dev->board_ptr;
	काष्ठा comedi_subdevice *s;
	पूर्णांक subdev;
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], board->io_range);
	अगर (ret)
		वापस ret;

	ret = comedi_alloc_subdevices(dev, board->n_subdevs);
	अगर (ret)
		वापस ret;

	subdev = 0;

	अगर (board->n_iso_out_chan) अणु
		/* Isolated Digital Outमाला_दो */
		s = &dev->subdevices[subdev++];
		s->type		= COMEDI_SUBD_DO;
		s->subdev_flags	= SDF_WRITABLE;
		s->n_chan	= board->n_iso_out_chan;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_bits	= pcl730_करो_insn_bits;
		s->निजी	= (व्योम *)0;

		/* get the initial state अगर supported */
		अगर (board->has_पढ़ोback)
			s->state = pcl730_get_bits(dev, s);
	पूर्ण

	अगर (board->n_iso_in_chan) अणु
		/* Isolated Digital Inमाला_दो */
		s = &dev->subdevices[subdev++];
		s->type		= COMEDI_SUBD_DI;
		s->subdev_flags	= SDF_READABLE;
		s->n_chan	= board->n_iso_in_chan;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_bits	= pcl730_di_insn_bits;
		s->निजी	= board->is_ir104 ? (व्योम *)4 :
				  board->is_acl7225b ? (व्योम *)2 :
				  board->is_pcl725 ? (व्योम *)1 : (व्योम *)0;
	पूर्ण

	अगर (board->has_ttl_io) अणु
		/* TTL Digital Outमाला_दो */
		s = &dev->subdevices[subdev++];
		s->type		= COMEDI_SUBD_DO;
		s->subdev_flags	= SDF_WRITABLE;
		s->n_chan	= board->n_ttl_chan;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_bits	= pcl730_करो_insn_bits;
		s->निजी	= (व्योम *)2;

		/* TTL Digital Inमाला_दो */
		s = &dev->subdevices[subdev++];
		s->type		= COMEDI_SUBD_DI;
		s->subdev_flags	= SDF_READABLE;
		s->n_chan	= board->n_ttl_chan;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_bits	= pcl730_di_insn_bits;
		s->निजी	= (व्योम *)2;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver pcl730_driver = अणु
	.driver_name	= "pcl730",
	.module		= THIS_MODULE,
	.attach		= pcl730_attach,
	.detach		= comedi_legacy_detach,
	.board_name	= &pcl730_boards[0].name,
	.num_names	= ARRAY_SIZE(pcl730_boards),
	.offset		= माप(काष्ठा pcl730_board),
पूर्ण;
module_comedi_driver(pcl730_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
