<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi_8255.c
 * Generic 8255 digital I/O support
 *
 * Split from the Comedi "8255" driver module.
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1998 David A. Schleef <ds@schleef.org>
 */

/*
 * Module: comedi_8255
 * Description: Generic 8255 support
 * Author: ds
 * Updated: Fri, 22 May 2015 12:14:17 +0000
 * Status: works
 *
 * This module is not used directly by end-users.  Rather, it is used by
 * other drivers to provide support क्रम an 8255 "Programmable Peripheral
 * Interface" (PPI) chip.
 *
 * The classic in digital I/O.  The 8255 appears in Comedi as a single
 * digital I/O subdevice with 24 channels.  The channel 0 corresponds to
 * the 8255's port A, bit 0; channel 23 corresponds to port C, bit 7.
 * Direction configuration is करोne in blocks, with channels 0-7, 8-15,
 * 16-19, and 20-23 making up the 4 blocks.  The only 8255 mode
 * supported is mode 0.
 */

#समावेश <linux/module.h>
#समावेश "../comedidev.h"

#समावेश "8255.h"

काष्ठा subdev_8255_निजी अणु
	अचिन्हित दीर्घ regbase;
	पूर्णांक (*io)(काष्ठा comedi_device *dev, पूर्णांक dir, पूर्णांक port, पूर्णांक data,
		  अचिन्हित दीर्घ regbase);
पूर्ण;

अटल पूर्णांक subdev_8255_io(काष्ठा comedi_device *dev,
			  पूर्णांक dir, पूर्णांक port, पूर्णांक data, अचिन्हित दीर्घ regbase)
अणु
	अगर (dir) अणु
		outb(data, dev->iobase + regbase + port);
		वापस 0;
	पूर्ण
	वापस inb(dev->iobase + regbase + port);
पूर्ण

अटल पूर्णांक subdev_8255_mmio(काष्ठा comedi_device *dev,
			    पूर्णांक dir, पूर्णांक port, पूर्णांक data, अचिन्हित दीर्घ regbase)
अणु
	अगर (dir) अणु
		ग_लिखोb(data, dev->mmio + regbase + port);
		वापस 0;
	पूर्ण
	वापस पढ़ोb(dev->mmio + regbase + port);
पूर्ण

अटल पूर्णांक subdev_8255_insn(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s,
			    काष्ठा comedi_insn *insn,
			    अचिन्हित पूर्णांक *data)
अणु
	काष्ठा subdev_8255_निजी *spriv = s->निजी;
	अचिन्हित दीर्घ regbase = spriv->regbase;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक v;

	mask = comedi_dio_update_state(s, data);
	अगर (mask) अणु
		अगर (mask & 0xff)
			spriv->io(dev, 1, I8255_DATA_A_REG,
				  s->state & 0xff, regbase);
		अगर (mask & 0xff00)
			spriv->io(dev, 1, I8255_DATA_B_REG,
				  (s->state >> 8) & 0xff, regbase);
		अगर (mask & 0xff0000)
			spriv->io(dev, 1, I8255_DATA_C_REG,
				  (s->state >> 16) & 0xff, regbase);
	पूर्ण

	v = spriv->io(dev, 0, I8255_DATA_A_REG, 0, regbase);
	v |= (spriv->io(dev, 0, I8255_DATA_B_REG, 0, regbase) << 8);
	v |= (spriv->io(dev, 0, I8255_DATA_C_REG, 0, regbase) << 16);

	data[1] = v;

	वापस insn->n;
पूर्ण

अटल व्योम subdev_8255_करो_config(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s)
अणु
	काष्ठा subdev_8255_निजी *spriv = s->निजी;
	अचिन्हित दीर्घ regbase = spriv->regbase;
	पूर्णांक config;

	config = I8255_CTRL_CW;
	/* 1 in io_bits indicates output, 1 in config indicates input */
	अगर (!(s->io_bits & 0x0000ff))
		config |= I8255_CTRL_A_IO;
	अगर (!(s->io_bits & 0x00ff00))
		config |= I8255_CTRL_B_IO;
	अगर (!(s->io_bits & 0x0f0000))
		config |= I8255_CTRL_C_LO_IO;
	अगर (!(s->io_bits & 0xf00000))
		config |= I8255_CTRL_C_HI_IO;

	spriv->io(dev, 1, I8255_CTRL_REG, config, regbase);
पूर्ण

अटल पूर्णांक subdev_8255_insn_config(काष्ठा comedi_device *dev,
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

	subdev_8255_करो_config(dev, s);

	वापस insn->n;
पूर्ण

अटल पूर्णांक __subdev_8255_init(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      पूर्णांक (*io)(काष्ठा comedi_device *dev,
					पूर्णांक dir, पूर्णांक port, पूर्णांक data,
					अचिन्हित दीर्घ regbase),
			      अचिन्हित दीर्घ regbase,
			      bool is_mmio)
अणु
	काष्ठा subdev_8255_निजी *spriv;

	spriv = comedi_alloc_spriv(s, माप(*spriv));
	अगर (!spriv)
		वापस -ENOMEM;

	अगर (io)
		spriv->io = io;
	अन्यथा अगर (is_mmio)
		spriv->io = subdev_8255_mmio;
	अन्यथा
		spriv->io = subdev_8255_io;
	spriv->regbase	= regbase;

	s->type		= COMEDI_SUBD_DIO;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= 24;
	s->range_table	= &range_digital;
	s->maxdata	= 1;
	s->insn_bits	= subdev_8255_insn;
	s->insn_config	= subdev_8255_insn_config;

	subdev_8255_करो_config(dev, s);

	वापस 0;
पूर्ण

/**
 * subdev_8255_init - initialize DIO subdevice क्रम driving I/O mapped 8255
 * @dev: comedi device owning subdevice
 * @s: comedi subdevice to initialize
 * @io: (optional) रेजिस्टर I/O call-back function
 * @regbase: offset of 8255 रेजिस्टरs from dev->iobase, or call-back context
 *
 * Initializes a comedi subdevice as a DIO subdevice driving an 8255 chip.
 *
 * If the optional I/O call-back function is provided, its prototype is of
 * the following क्रमm:
 *
 *   पूर्णांक my_8255_callback(काष्ठा comedi_device *dev, पूर्णांक dir, पूर्णांक port,
 *                        पूर्णांक data, अचिन्हित दीर्घ regbase);
 *
 * where 'dev', and 'regbase' match the values passed to this function,
 * 'port' is the 8255 port number 0 to 3 (including the control port), 'dir'
 * is the direction (0 क्रम पढ़ो, 1 क्रम ग_लिखो) and 'data' is the value to be
 * written.  It should वापस 0 अगर writing or the value पढ़ो अगर पढ़ोing.
 *
 * If the optional I/O call-back function is not provided, an पूर्णांकernal
 * call-back function is used which uses consecutive I/O port addresses
 * starting at dev->iobase + regbase.
 *
 * Return: -ENOMEM अगर failed to allocate memory, zero on success.
 */
पूर्णांक subdev_8255_init(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
		     पूर्णांक (*io)(काष्ठा comedi_device *dev, पूर्णांक dir, पूर्णांक port,
			       पूर्णांक data, अचिन्हित दीर्घ regbase),
		     अचिन्हित दीर्घ regbase)
अणु
	वापस __subdev_8255_init(dev, s, io, regbase, false);
पूर्ण
EXPORT_SYMBOL_GPL(subdev_8255_init);

/**
 * subdev_8255_mm_init - initialize DIO subdevice क्रम driving mmio-mapped 8255
 * @dev: comedi device owning subdevice
 * @s: comedi subdevice to initialize
 * @io: (optional) रेजिस्टर I/O call-back function
 * @regbase: offset of 8255 रेजिस्टरs from dev->mmio, or call-back context
 *
 * Initializes a comedi subdevice as a DIO subdevice driving an 8255 chip.
 *
 * If the optional I/O call-back function is provided, its prototype is of
 * the following क्रमm:
 *
 *   पूर्णांक my_8255_callback(काष्ठा comedi_device *dev, पूर्णांक dir, पूर्णांक port,
 *                        पूर्णांक data, अचिन्हित दीर्घ regbase);
 *
 * where 'dev', and 'regbase' match the values passed to this function,
 * 'port' is the 8255 port number 0 to 3 (including the control port), 'dir'
 * is the direction (0 क्रम पढ़ो, 1 क्रम ग_लिखो) and 'data' is the value to be
 * written.  It should वापस 0 अगर writing or the value पढ़ो अगर पढ़ोing.
 *
 * If the optional I/O call-back function is not provided, an पूर्णांकernal
 * call-back function is used which uses consecutive MMIO भव addresses
 * starting at dev->mmio + regbase.
 *
 * Return: -ENOMEM अगर failed to allocate memory, zero on success.
 */
पूर्णांक subdev_8255_mm_init(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
			पूर्णांक (*io)(काष्ठा comedi_device *dev, पूर्णांक dir, पूर्णांक port,
				  पूर्णांक data, अचिन्हित दीर्घ regbase),
			अचिन्हित दीर्घ regbase)
अणु
	वापस __subdev_8255_init(dev, s, io, regbase, true);
पूर्ण
EXPORT_SYMBOL_GPL(subdev_8255_mm_init);

/**
 * subdev_8255_regbase - get offset of 8255 रेजिस्टरs or call-back context
 * @s: comedi subdevice
 *
 * Returns the 'regbase' parameter that was previously passed to
 * subdev_8255_init() or subdev_8255_mm_init() to set up the subdevice.
 * Only valid अगर the subdevice was set up successfully.
 */
अचिन्हित दीर्घ subdev_8255_regbase(काष्ठा comedi_subdevice *s)
अणु
	काष्ठा subdev_8255_निजी *spriv = s->निजी;

	वापस spriv->regbase;
पूर्ण
EXPORT_SYMBOL_GPL(subdev_8255_regbase);

अटल पूर्णांक __init comedi_8255_module_init(व्योम)
अणु
	वापस 0;
पूर्ण
module_init(comedi_8255_module_init);

अटल व्योम __निकास comedi_8255_module_निकास(व्योम)
अणु
पूर्ण
module_निकास(comedi_8255_module_निकास);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi: Generic 8255 digital I/O support");
MODULE_LICENSE("GPL");
