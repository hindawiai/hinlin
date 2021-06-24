<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/dyna_pci10xx.c
 * Copyright (C) 2011 Prashant Shah, pshah.mumbai@gmail.com
 */

/*
 * Driver: dyna_pci10xx
 * Description: Dynalog India PCI DAQ Cards, http://www.dynalogindia.com/
 * Devices: [Dynalog] PCI-1050 (dyna_pci1050)
 * Author: Prashant Shah <pshah.mumbai@gmail.com>
 * Status: Stable
 *
 * Developed at Automation Lअसल, Chemical Dept., IIT Bombay, India.
 * Prof. Kannan Moudgalya <kannan@iitb.ac.in>
 * http://www.iitb.ac.in
 *
 * Notes :
 * - Dynalog India Pvt. Ltd. करोes not have a रेजिस्टरed PCI Venकरोr ID and
 *   they are using the PLX Technlogies Venकरोr ID since that is the PCI Chip
 *   used in the card.
 * - Dynalog India Pvt. Ltd. has provided the पूर्णांकernal रेजिस्टर specअगरication
 *   क्रम their cards in their manuals.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>

#समावेश "../comedi_pci.h"

#घोषणा READ_TIMEOUT 50

अटल स्थिर काष्ठा comedi_lrange range_pci1050_ai = अणु
	3, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		UNI_RANGE(10)
	पूर्ण
पूर्ण;

अटल स्थिर अक्षर range_codes_pci1050_ai[] = अणु 0x00, 0x10, 0x30 पूर्ण;

काष्ठा dyna_pci10xx_निजी अणु
	काष्ठा mutex mutex;
	अचिन्हित दीर्घ BADR3;
पूर्ण;

अटल पूर्णांक dyna_pci10xx_ai_eoc(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inw_p(dev->iobase);
	अगर (status & BIT(15))
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक dyna_pci10xx_insn_पढ़ो_ai(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     काष्ठा comedi_insn *insn,
				     अचिन्हित पूर्णांक *data)
अणु
	काष्ठा dyna_pci10xx_निजी *devpriv = dev->निजी;
	पूर्णांक n;
	u16 d = 0;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक chan, range;

	/* get the channel number and range */
	chan = CR_CHAN(insn->chanspec);
	range = range_codes_pci1050_ai[CR_RANGE((insn->chanspec))];

	mutex_lock(&devpriv->mutex);
	/* convert n samples */
	क्रम (n = 0; n < insn->n; n++) अणु
		/* trigger conversion */
		smp_mb();
		outw_p(0x0000 + range + chan, dev->iobase + 2);
		usleep_range(10, 20);

		ret = comedi_समयout(dev, s, insn, dyna_pci10xx_ai_eoc, 0);
		अगर (ret)
			अवरोध;

		/* पढ़ो data */
		d = inw_p(dev->iobase);
		/* mask the first 4 bits - EOC bits */
		d &= 0x0FFF;
		data[n] = d;
	पूर्ण
	mutex_unlock(&devpriv->mutex);

	/* वापस the number of samples पढ़ो/written */
	वापस ret ? ret : n;
पूर्ण

/* analog output callback */
अटल पूर्णांक dyna_pci10xx_insn_ग_लिखो_ao(काष्ठा comedi_device *dev,
				      काष्ठा comedi_subdevice *s,
				      काष्ठा comedi_insn *insn,
				      अचिन्हित पूर्णांक *data)
अणु
	काष्ठा dyna_pci10xx_निजी *devpriv = dev->निजी;
	पूर्णांक n;

	mutex_lock(&devpriv->mutex);
	क्रम (n = 0; n < insn->n; n++) अणु
		smp_mb();
		/* trigger conversion and ग_लिखो data */
		outw_p(data[n], dev->iobase);
		usleep_range(10, 20);
	पूर्ण
	mutex_unlock(&devpriv->mutex);
	वापस n;
पूर्ण

/* digital input bit पूर्णांकerface */
अटल पूर्णांक dyna_pci10xx_di_insn_bits(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     काष्ठा comedi_insn *insn,
				     अचिन्हित पूर्णांक *data)
अणु
	काष्ठा dyna_pci10xx_निजी *devpriv = dev->निजी;
	u16 d = 0;

	mutex_lock(&devpriv->mutex);
	smp_mb();
	d = inw_p(devpriv->BADR3);
	usleep_range(10, 100);

	/* on वापस the data[0] contains output and data[1] contains input */
	data[1] = d;
	data[0] = s->state;
	mutex_unlock(&devpriv->mutex);
	वापस insn->n;
पूर्ण

अटल पूर्णांक dyna_pci10xx_करो_insn_bits(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     काष्ठा comedi_insn *insn,
				     अचिन्हित पूर्णांक *data)
अणु
	काष्ठा dyna_pci10xx_निजी *devpriv = dev->निजी;

	mutex_lock(&devpriv->mutex);
	अगर (comedi_dio_update_state(s, data)) अणु
		smp_mb();
		outw_p(s->state, devpriv->BADR3);
		usleep_range(10, 100);
	पूर्ण

	data[1] = s->state;
	mutex_unlock(&devpriv->mutex);

	वापस insn->n;
पूर्ण

अटल पूर्णांक dyna_pci10xx_स्वतः_attach(काष्ठा comedi_device *dev,
				    अचिन्हित दीर्घ context_unused)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा dyna_pci10xx_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;
	dev->iobase = pci_resource_start(pcidev, 2);
	devpriv->BADR3 = pci_resource_start(pcidev, 3);

	mutex_init(&devpriv->mutex);

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	/* analog input */
	s = &dev->subdevices[0];
	s->type = COMEDI_SUBD_AI;
	s->subdev_flags = SDF_READABLE | SDF_GROUND | SDF_DIFF;
	s->n_chan = 16;
	s->maxdata = 0x0FFF;
	s->range_table = &range_pci1050_ai;
	s->insn_पढ़ो = dyna_pci10xx_insn_पढ़ो_ai;

	/* analog output */
	s = &dev->subdevices[1];
	s->type = COMEDI_SUBD_AO;
	s->subdev_flags = SDF_WRITABLE;
	s->n_chan = 1;
	s->maxdata = 0x0FFF;
	s->range_table = &range_unipolar10;
	s->insn_ग_लिखो = dyna_pci10xx_insn_ग_लिखो_ao;

	/* digital input */
	s = &dev->subdevices[2];
	s->type = COMEDI_SUBD_DI;
	s->subdev_flags = SDF_READABLE;
	s->n_chan = 16;
	s->maxdata = 1;
	s->range_table = &range_digital;
	s->insn_bits = dyna_pci10xx_di_insn_bits;

	/* digital output */
	s = &dev->subdevices[3];
	s->type = COMEDI_SUBD_DO;
	s->subdev_flags = SDF_WRITABLE;
	s->n_chan = 16;
	s->maxdata = 1;
	s->range_table = &range_digital;
	s->state = 0;
	s->insn_bits = dyna_pci10xx_करो_insn_bits;

	वापस 0;
पूर्ण

अटल व्योम dyna_pci10xx_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा dyna_pci10xx_निजी *devpriv = dev->निजी;

	comedi_pci_detach(dev);
	अगर (devpriv)
		mutex_destroy(&devpriv->mutex);
पूर्ण

अटल काष्ठा comedi_driver dyna_pci10xx_driver = अणु
	.driver_name	= "dyna_pci10xx",
	.module		= THIS_MODULE,
	.स्वतः_attach	= dyna_pci10xx_स्वतः_attach,
	.detach		= dyna_pci10xx_detach,
पूर्ण;

अटल पूर्णांक dyna_pci10xx_pci_probe(काष्ठा pci_dev *dev,
				  स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &dyna_pci10xx_driver,
				      id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id dyna_pci10xx_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_PLX, 0x1050) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, dyna_pci10xx_pci_table);

अटल काष्ठा pci_driver dyna_pci10xx_pci_driver = अणु
	.name		= "dyna_pci10xx",
	.id_table	= dyna_pci10xx_pci_table,
	.probe		= dyna_pci10xx_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(dyna_pci10xx_driver, dyna_pci10xx_pci_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Prashant Shah <pshah.mumbai@gmail.com>");
MODULE_DESCRIPTION("Comedi based drivers for Dynalog PCI DAQ cards");
