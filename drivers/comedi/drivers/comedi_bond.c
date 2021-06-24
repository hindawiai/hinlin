<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi_bond.c
 * A Comedi driver to 'bond' or merge multiple drivers and devices as one.
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 * Copyright (C) 2005 Calin A. Culianu <calin@ajvar.org>
 */

/*
 * Driver: comedi_bond
 * Description: A driver to 'bond' (merge) multiple subdevices from multiple
 * devices together as one.
 * Devices:
 * Author: ds
 * Updated: Mon, 10 Oct 00:18:25 -0500
 * Status: works
 *
 * This driver allows you to 'bond' (merge) multiple comedi subdevices
 * (coming from possibly dअगरference boards and/or drivers) together.  For
 * example, अगर you had a board with 2 dअगरferent DIO subdevices, and
 * another with 1 DIO subdevice, you could 'bond' them with this driver
 * so that they look like one big fat DIO subdevice.  This makes writing
 * applications slightly easier as you करोn't have to worry about managing
 * dअगरferent subdevices in the application -- you just worry about
 * indexing one linear array of channel id's.
 *
 * Right now only DIO subdevices are supported as that's the personal itch
 * I am scratching with this driver.  If you want to add support क्रम AI and AO
 * subdevs, go right on ahead and करो so!
 *
 * Commands aren't supported -- although it would be cool अगर they were.
 *
 * Configuration Options:
 *   List of comedi-minors to bond.  All subdevices of the same type
 *   within each minor will be concatenated together in the order given here.
 */

#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश "../comedi.h"
#समावेश "../comedilib.h"
#समावेश "../comedidev.h"

काष्ठा bonded_device अणु
	काष्ठा comedi_device *dev;
	अचिन्हित पूर्णांक minor;
	अचिन्हित पूर्णांक subdev;
	अचिन्हित पूर्णांक nchans;
पूर्ण;

काष्ठा comedi_bond_निजी अणु
	अक्षर name[256];
	काष्ठा bonded_device **devs;
	अचिन्हित पूर्णांक ndevs;
	अचिन्हित पूर्णांक nchans;
पूर्ण;

अटल पूर्णांक bonding_dio_insn_bits(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	काष्ठा comedi_bond_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक n_left, n_करोne, base_chan;
	अचिन्हित पूर्णांक ग_लिखो_mask, data_bits;
	काष्ठा bonded_device **devs;

	ग_लिखो_mask = data[0];
	data_bits = data[1];
	base_chan = CR_CHAN(insn->chanspec);
	/* करो a maximum of 32 channels, starting from base_chan. */
	n_left = devpriv->nchans - base_chan;
	अगर (n_left > 32)
		n_left = 32;

	n_करोne = 0;
	devs = devpriv->devs;
	करो अणु
		काष्ठा bonded_device *bdev = *devs++;

		अगर (base_chan < bdev->nchans) अणु
			/* base channel falls within bonded device */
			अचिन्हित पूर्णांक b_chans, b_mask, b_ग_लिखो_mask, b_data_bits;
			पूर्णांक ret;

			/*
			 * Get num channels to करो क्रम bonded device and set
			 * up mask and data bits क्रम bonded device.
			 */
			b_chans = bdev->nchans - base_chan;
			अगर (b_chans > n_left)
				b_chans = n_left;
			b_mask = (b_chans < 32) ? ((1 << b_chans) - 1)
						: 0xffffffff;
			b_ग_लिखो_mask = (ग_लिखो_mask >> n_करोne) & b_mask;
			b_data_bits = (data_bits >> n_करोne) & b_mask;
			/* Read/Write the new digital lines. */
			ret = comedi_dio_bitfield2(bdev->dev, bdev->subdev,
						   b_ग_लिखो_mask, &b_data_bits,
						   base_chan);
			अगर (ret < 0)
				वापस ret;
			/* Place पढ़ो bits पूर्णांकo data[1]. */
			data[1] &= ~(b_mask << n_करोne);
			data[1] |= (b_data_bits & b_mask) << n_करोne;
			/*
			 * Set up क्रम following bonded device (अगर still have
			 * channels to पढ़ो/ग_लिखो).
			 */
			base_chan = 0;
			n_करोne += b_chans;
			n_left -= b_chans;
		पूर्ण अन्यथा अणु
			/* Skip bonded devices beक्रमe base channel. */
			base_chan -= bdev->nchans;
		पूर्ण
	पूर्ण जबतक (n_left);

	वापस insn->n;
पूर्ण

अटल पूर्णांक bonding_dio_insn_config(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	काष्ठा comedi_bond_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक ret;
	काष्ठा bonded_device *bdev;
	काष्ठा bonded_device **devs;

	/*
	 * Locate bonded subdevice and adjust channel.
	 */
	devs = devpriv->devs;
	क्रम (bdev = *devs++; chan >= bdev->nchans; bdev = *devs++)
		chan -= bdev->nchans;

	/*
	 * The input or output configuration of each digital line is
	 * configured by a special insn_config inकाष्ठाion.  chanspec
	 * contains the channel to be changed, and data[0] contains the
	 * configuration inकाष्ठाion INSN_CONFIG_DIO_OUTPUT,
	 * INSN_CONFIG_DIO_INPUT or INSN_CONFIG_DIO_QUERY.
	 *
	 * Note that INSN_CONFIG_DIO_OUTPUT == COMEDI_OUTPUT,
	 * and INSN_CONFIG_DIO_INPUT == COMEDI_INPUT.  This is deliberate ;)
	 */
	चयन (data[0]) अणु
	हाल INSN_CONFIG_DIO_OUTPUT:
	हाल INSN_CONFIG_DIO_INPUT:
		ret = comedi_dio_config(bdev->dev, bdev->subdev, chan, data[0]);
		अवरोध;
	हाल INSN_CONFIG_DIO_QUERY:
		ret = comedi_dio_get_config(bdev->dev, bdev->subdev, chan,
					    &data[1]);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	अगर (ret >= 0)
		ret = insn->n;
	वापस ret;
पूर्ण

अटल पूर्णांक करो_dev_config(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	काष्ठा comedi_bond_निजी *devpriv = dev->निजी;
	DECLARE_BITMAP(devs_खोलोed, COMEDI_NUM_BOARD_MINORS);
	पूर्णांक i;

	स_रखो(&devs_खोलोed, 0, माप(devs_खोलोed));
	devpriv->name[0] = 0;
	/*
	 * Loop through all comedi devices specअगरied on the command-line,
	 * building our device list.
	 */
	क्रम (i = 0; i < COMEDI_NDEVCONFOPTS && (!i || it->options[i]); ++i) अणु
		अक्षर file[माप("/dev/comediXXXXXX")];
		पूर्णांक minor = it->options[i];
		काष्ठा comedi_device *d;
		पूर्णांक sdev = -1, nchans;
		काष्ठा bonded_device *bdev;
		काष्ठा bonded_device **devs;

		अगर (minor < 0 || minor >= COMEDI_NUM_BOARD_MINORS) अणु
			dev_err(dev->class_dev,
				"Minor %d is invalid!\n", minor);
			वापस -EINVAL;
		पूर्ण
		अगर (minor == dev->minor) अणु
			dev_err(dev->class_dev,
				"Cannot bond this driver to itself!\n");
			वापस -EINVAL;
		पूर्ण
		अगर (test_and_set_bit(minor, devs_खोलोed)) अणु
			dev_err(dev->class_dev,
				"Minor %d specified more than once!\n", minor);
			वापस -EINVAL;
		पूर्ण

		snम_लिखो(file, माप(file), "/dev/comedi%d", minor);
		file[माप(file) - 1] = 0;

		d = comedi_खोलो(file);

		अगर (!d) अणु
			dev_err(dev->class_dev,
				"Minor %u could not be opened\n", minor);
			वापस -ENODEV;
		पूर्ण

		/* Do DIO, as that's all we support now.. */
		जबतक ((sdev = comedi_find_subdevice_by_type(d, COMEDI_SUBD_DIO,
							     sdev + 1)) > -1) अणु
			nchans = comedi_get_n_channels(d, sdev);
			अगर (nchans <= 0) अणु
				dev_err(dev->class_dev,
					"comedi_get_n_channels() returned %d on minor %u subdev %d!\n",
					nchans, minor, sdev);
				वापस -EINVAL;
			पूर्ण
			bdev = kदो_स्मृति(माप(*bdev), GFP_KERNEL);
			अगर (!bdev)
				वापस -ENOMEM;

			bdev->dev = d;
			bdev->minor = minor;
			bdev->subdev = sdev;
			bdev->nchans = nchans;
			devpriv->nchans += nchans;

			/*
			 * Now put bdev poपूर्णांकer at end of devpriv->devs array
			 * list..
			 */

			/* ergh.. ugly.. we need to पुनः_स्मृति :(  */
			devs = kपुनः_स्मृति(devpriv->devs,
					(devpriv->ndevs + 1) * माप(*devs),
					GFP_KERNEL);
			अगर (!devs) अणु
				dev_err(dev->class_dev,
					"Could not allocate memory. Out of memory?\n");
				kमुक्त(bdev);
				वापस -ENOMEM;
			पूर्ण
			devpriv->devs = devs;
			devpriv->devs[devpriv->ndevs++] = bdev;
			अणु
				/* Append dev:subdev to devpriv->name */
				अक्षर buf[20];

				snम_लिखो(buf, माप(buf), "%u:%u ",
					 bdev->minor, bdev->subdev);
				strlcat(devpriv->name, buf,
					माप(devpriv->name));
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!devpriv->nchans) अणु
		dev_err(dev->class_dev, "No channels found!\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bonding_attach(काष्ठा comedi_device *dev,
			  काष्ठा comedi_devconfig *it)
अणु
	काष्ठा comedi_bond_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	/*
	 * Setup our bonding from config params.. sets up our निजी काष्ठा..
	 */
	ret = करो_dev_config(dev, it);
	अगर (ret)
		वापस ret;

	dev->board_name = devpriv->name;

	ret = comedi_alloc_subdevices(dev, 1);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	s->type = COMEDI_SUBD_DIO;
	s->subdev_flags = SDF_READABLE | SDF_WRITABLE;
	s->n_chan = devpriv->nchans;
	s->maxdata = 1;
	s->range_table = &range_digital;
	s->insn_bits = bonding_dio_insn_bits;
	s->insn_config = bonding_dio_insn_config;

	dev_info(dev->class_dev,
		 "%s: %s attached, %u channels from %u devices\n",
		 dev->driver->driver_name, dev->board_name,
		 devpriv->nchans, devpriv->ndevs);

	वापस 0;
पूर्ण

अटल व्योम bonding_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा comedi_bond_निजी *devpriv = dev->निजी;

	अगर (devpriv && devpriv->devs) अणु
		DECLARE_BITMAP(devs_बंदd, COMEDI_NUM_BOARD_MINORS);

		स_रखो(&devs_बंदd, 0, माप(devs_बंदd));
		जबतक (devpriv->ndevs--) अणु
			काष्ठा bonded_device *bdev;

			bdev = devpriv->devs[devpriv->ndevs];
			अगर (!bdev)
				जारी;
			अगर (!test_and_set_bit(bdev->minor, devs_बंदd))
				comedi_बंद(bdev->dev);
			kमुक्त(bdev);
		पूर्ण
		kमुक्त(devpriv->devs);
		devpriv->devs = शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा comedi_driver bonding_driver = अणु
	.driver_name	= "comedi_bond",
	.module		= THIS_MODULE,
	.attach		= bonding_attach,
	.detach		= bonding_detach,
पूर्ण;
module_comedi_driver(bonding_driver);

MODULE_AUTHOR("Calin A. Culianu");
MODULE_DESCRIPTION("comedi_bond: A driver for COMEDI to bond multiple COMEDI devices together as one.");
MODULE_LICENSE("GPL");
