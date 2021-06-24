<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * pcm3724.c
 * Comedi driver क्रम Advantech PCM-3724 Digital I/O board
 *
 * Drew Csillag <drew_csillag@yahoo.com>
 */

/*
 * Driver: pcm3724
 * Description: Advantech PCM-3724
 * Devices: [Advantech] PCM-3724 (pcm3724)
 * Author: Drew Csillag <drew_csillag@yahoo.com>
 * Status: tested
 *
 * This is driver क्रम digital I/O boards PCM-3724 with 48 DIO.
 * It needs 8255.o क्रम operations and only immediate mode is supported.
 * See the source क्रम configuration details.
 *
 * Copy/pasted/hacked from pcm724.c
 *
 * Configuration Options:
 *   [0] - I/O port base address
 */

#समावेश <linux/module.h>
#समावेश "../comedidev.h"

#समावेश "8255.h"

/*
 * Register I/O Map
 *
 * This board has two standard 8255 devices that provide six 8-bit DIO ports
 * (48 channels total). Six 74HCT245 chips (one क्रम each port) buffer the
 * I/O lines to increase driving capability. Because the 74HCT245 is a
 * bidirectional, tri-state line buffer, two additional I/O ports are used
 * to control the direction of data and the enable of each port.
 */
#घोषणा PCM3724_8255_0_BASE		0x00
#घोषणा PCM3724_8255_1_BASE		0x04
#घोषणा PCM3724_DIO_सूची_REG		0x08
#घोषणा PCM3724_DIO_सूची_C0_OUT		BIT(0)
#घोषणा PCM3724_DIO_सूची_B0_OUT		BIT(1)
#घोषणा PCM3724_DIO_सूची_A0_OUT		BIT(2)
#घोषणा PCM3724_DIO_सूची_C1_OUT		BIT(3)
#घोषणा PCM3724_DIO_सूची_B1_OUT		BIT(4)
#घोषणा PCM3724_DIO_सूची_A1_OUT		BIT(5)
#घोषणा PCM3724_GATE_CTRL_REG		0x09
#घोषणा PCM3724_GATE_CTRL_C0_ENA	BIT(0)
#घोषणा PCM3724_GATE_CTRL_B0_ENA	BIT(1)
#घोषणा PCM3724_GATE_CTRL_A0_ENA	BIT(2)
#घोषणा PCM3724_GATE_CTRL_C1_ENA	BIT(3)
#घोषणा PCM3724_GATE_CTRL_B1_ENA	BIT(4)
#घोषणा PCM3724_GATE_CTRL_A1_ENA	BIT(5)

/* used to track configured dios */
काष्ठा priv_pcm3724 अणु
	पूर्णांक dio_1;
	पूर्णांक dio_2;
पूर्ण;

अटल पूर्णांक compute_buffer(पूर्णांक config, पूर्णांक devno, काष्ठा comedi_subdevice *s)
अणु
	/* 1 in io_bits indicates output */
	अगर (s->io_bits & 0x0000ff) अणु
		अगर (devno == 0)
			config |= PCM3724_DIO_सूची_A0_OUT;
		अन्यथा
			config |= PCM3724_DIO_सूची_A1_OUT;
	पूर्ण
	अगर (s->io_bits & 0x00ff00) अणु
		अगर (devno == 0)
			config |= PCM3724_DIO_सूची_B0_OUT;
		अन्यथा
			config |= PCM3724_DIO_सूची_B1_OUT;
	पूर्ण
	अगर (s->io_bits & 0xff0000) अणु
		अगर (devno == 0)
			config |= PCM3724_DIO_सूची_C0_OUT;
		अन्यथा
			config |= PCM3724_DIO_सूची_C1_OUT;
	पूर्ण
	वापस config;
पूर्ण

अटल व्योम करो_3724_config(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s, पूर्णांक chanspec)
अणु
	काष्ठा comedi_subdevice *s_dio1 = &dev->subdevices[0];
	काष्ठा comedi_subdevice *s_dio2 = &dev->subdevices[1];
	पूर्णांक config;
	पूर्णांक buffer_config;
	अचिन्हित दीर्घ port_8255_cfg;

	config = I8255_CTRL_CW;
	buffer_config = 0;

	/* 1 in io_bits indicates output, 1 in config indicates input */
	अगर (!(s->io_bits & 0x0000ff))
		config |= I8255_CTRL_A_IO;

	अगर (!(s->io_bits & 0x00ff00))
		config |= I8255_CTRL_B_IO;

	अगर (!(s->io_bits & 0xff0000))
		config |= I8255_CTRL_C_HI_IO | I8255_CTRL_C_LO_IO;

	buffer_config = compute_buffer(0, 0, s_dio1);
	buffer_config = compute_buffer(buffer_config, 1, s_dio2);

	अगर (s == s_dio1)
		port_8255_cfg = dev->iobase + I8255_CTRL_REG;
	अन्यथा
		port_8255_cfg = dev->iobase + I8255_SIZE + I8255_CTRL_REG;

	outb(buffer_config, dev->iobase + PCM3724_DIO_सूची_REG);

	outb(config, port_8255_cfg);
पूर्ण

अटल व्योम enable_chan(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
			पूर्णांक chanspec)
अणु
	काष्ठा priv_pcm3724 *priv = dev->निजी;
	काष्ठा comedi_subdevice *s_dio1 = &dev->subdevices[0];
	अचिन्हित पूर्णांक mask;
	पूर्णांक gatecfg;

	gatecfg = 0;

	mask = 1 << CR_CHAN(chanspec);
	अगर (s == s_dio1)
		priv->dio_1 |= mask;
	अन्यथा
		priv->dio_2 |= mask;

	अगर (priv->dio_1 & 0xff0000)
		gatecfg |= PCM3724_GATE_CTRL_C0_ENA;

	अगर (priv->dio_1 & 0xff00)
		gatecfg |= PCM3724_GATE_CTRL_B0_ENA;

	अगर (priv->dio_1 & 0xff)
		gatecfg |= PCM3724_GATE_CTRL_A0_ENA;

	अगर (priv->dio_2 & 0xff0000)
		gatecfg |= PCM3724_GATE_CTRL_C1_ENA;

	अगर (priv->dio_2 & 0xff00)
		gatecfg |= PCM3724_GATE_CTRL_B1_ENA;

	अगर (priv->dio_2 & 0xff)
		gatecfg |= PCM3724_GATE_CTRL_A1_ENA;

	outb(gatecfg, dev->iobase + PCM3724_GATE_CTRL_REG);
पूर्ण

/* overriding the 8255 insn config */
अटल पूर्णांक subdev_3724_insn_config(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक mask;
	पूर्णांक ret;

	अगर (chan < 8)
		mask = 0x0000ff;
	अन्यथा अगर (chan < 16)
		mask = 0x00ff00;
	अन्यथा अगर (chan < 20)
		mask = 0x0f0000;
	अन्यथा
		mask = 0xf00000;

	ret = comedi_dio_insn_config(dev, s, insn, data, mask);
	अगर (ret)
		वापस ret;

	करो_3724_config(dev, s, insn->chanspec);
	enable_chan(dev, s, insn->chanspec);

	वापस insn->n;
पूर्ण

अटल पूर्णांक pcm3724_attach(काष्ठा comedi_device *dev,
			  काष्ठा comedi_devconfig *it)
अणु
	काष्ठा priv_pcm3724 *priv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret, i;

	priv = comedi_alloc_devpriv(dev, माप(*priv));
	अगर (!priv)
		वापस -ENOMEM;

	ret = comedi_request_region(dev, it->options[0], 0x10);
	अगर (ret)
		वापस ret;

	ret = comedi_alloc_subdevices(dev, 2);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < dev->n_subdevices; i++) अणु
		s = &dev->subdevices[i];
		ret = subdev_8255_init(dev, s, शून्य, i * I8255_SIZE);
		अगर (ret)
			वापस ret;
		s->insn_config = subdev_3724_insn_config;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver pcm3724_driver = अणु
	.driver_name	= "pcm3724",
	.module		= THIS_MODULE,
	.attach		= pcm3724_attach,
	.detach		= comedi_legacy_detach,
पूर्ण;
module_comedi_driver(pcm3724_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for Advantech PCM-3724 Digital I/O board");
MODULE_LICENSE("GPL");
