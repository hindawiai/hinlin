<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/dt2815.c
 * Hardware driver क्रम Data Translation DT2815
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1999 Anders Blomdell <anders.blomdell@control.lth.se>
 */
/*
 * Driver: dt2815
 * Description: Data Translation DT2815
 * Author: ds
 * Status: mostly complete, untested
 * Devices: [Data Translation] DT2815 (dt2815)
 *
 * I'm not sure anyone has ever tested this board.  If you have inक्रमmation
 * contrary, please update.
 *
 * Configuration options:
 * [0] - I/O port base base address
 * [1] - IRQ (unused)
 * [2] - Voltage unipolar/bipolar configuration
 *	0 == unipolar 5V  (0V -- +5V)
 *	1 == bipolar 5V  (-5V -- +5V)
 * [3] - Current offset configuration
 *	0 == disabled  (0mA -- +32mAV)
 *	1 == enabled  (+4mA -- +20mAV)
 * [4] - Firmware program configuration
 *	0 == program 1 (see manual table 5-4)
 *	1 == program 2 (see manual table 5-4)
 *	2 == program 3 (see manual table 5-4)
 *	3 == program 4 (see manual table 5-4)
 * [5] - Analog output 0 range configuration
 *	0 == voltage
 *	1 == current
 * [6] - Analog output 1 range configuration (same options)
 * [7] - Analog output 2 range configuration (same options)
 * [8] - Analog output 3 range configuration (same options)
 * [9] - Analog output 4 range configuration (same options)
 * [10] - Analog output 5 range configuration (same options)
 * [11] - Analog output 6 range configuration (same options)
 * [12] - Analog output 7 range configuration (same options)
 */

#समावेश <linux/module.h>
#समावेश "../comedidev.h"

#समावेश <linux/delay.h>

#घोषणा DT2815_DATA 0
#घोषणा DT2815_STATUS 1

काष्ठा dt2815_निजी अणु
	स्थिर काष्ठा comedi_lrange *range_type_list[8];
	अचिन्हित पूर्णांक ao_पढ़ोback[8];
पूर्ण;

अटल पूर्णांक dt2815_ao_status(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s,
			    काष्ठा comedi_insn *insn,
			    अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inb(dev->iobase + DT2815_STATUS);
	अगर (status == context)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक dt2815_ao_insn_पढ़ो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	काष्ठा dt2815_निजी *devpriv = dev->निजी;
	पूर्णांक i;
	पूर्णांक chan = CR_CHAN(insn->chanspec);

	क्रम (i = 0; i < insn->n; i++)
		data[i] = devpriv->ao_पढ़ोback[chan];

	वापस i;
पूर्ण

अटल पूर्णांक dt2815_ao_insn(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
			  काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	काष्ठा dt2815_निजी *devpriv = dev->निजी;
	पूर्णांक i;
	पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक lo, hi;
	पूर्णांक ret;

	क्रम (i = 0; i < insn->n; i++) अणु
		/* FIXME: lo bit 0 chooses voltage output or current output */
		lo = ((data[i] & 0x0f) << 4) | (chan << 1) | 0x01;
		hi = (data[i] & 0xff0) >> 4;

		ret = comedi_समयout(dev, s, insn, dt2815_ao_status, 0x00);
		अगर (ret)
			वापस ret;

		outb(lo, dev->iobase + DT2815_DATA);

		ret = comedi_समयout(dev, s, insn, dt2815_ao_status, 0x10);
		अगर (ret)
			वापस ret;

		outb(hi, dev->iobase + DT2815_DATA);

		devpriv->ao_पढ़ोback[chan] = data[i];
	पूर्ण
	वापस i;
पूर्ण

/*
 * options[0]   Board base address
 * options[1]   IRQ (not applicable)
 * options[2]   Voltage unipolar/bipolar configuration
 *		0 == unipolar 5V  (0V -- +5V)
 *		1 == bipolar 5V  (-5V -- +5V)
 * options[3]   Current offset configuration
 *		0 == disabled  (0mA -- +32mAV)
 *		1 == enabled  (+4mA -- +20mAV)
 * options[4]   Firmware program configuration
 *		0 == program 1 (see manual table 5-4)
 *		1 == program 2 (see manual table 5-4)
 *		2 == program 3 (see manual table 5-4)
 *		3 == program 4 (see manual table 5-4)
 * options[5]   Analog output 0 range configuration
 *		0 == voltage
 *		1 == current
 * options[6]   Analog output 1 range configuration
 * ...
 * options[12]   Analog output 7 range configuration
 *		0 == voltage
 *		1 == current
 */

अटल पूर्णांक dt2815_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	काष्ठा dt2815_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक i;
	स्थिर काष्ठा comedi_lrange *current_range_type, *voltage_range_type;
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], 0x2);
	अगर (ret)
		वापस ret;

	ret = comedi_alloc_subdevices(dev, 1);
	अगर (ret)
		वापस ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	s = &dev->subdevices[0];
	/* ao subdevice */
	s->type = COMEDI_SUBD_AO;
	s->subdev_flags = SDF_WRITABLE;
	s->maxdata = 0xfff;
	s->n_chan = 8;
	s->insn_ग_लिखो = dt2815_ao_insn;
	s->insn_पढ़ो = dt2815_ao_insn_पढ़ो;
	s->range_table_list = devpriv->range_type_list;

	current_range_type = (it->options[3])
	    ? &range_4_20mA : &range_0_32mA;
	voltage_range_type = (it->options[2])
	    ? &range_bipolar5 : &range_unipolar5;
	क्रम (i = 0; i < 8; i++) अणु
		devpriv->range_type_list[i] = (it->options[5 + i])
		    ? current_range_type : voltage_range_type;
	पूर्ण

	/* Init the 2815 */
	outb(0x00, dev->iobase + DT2815_STATUS);
	क्रम (i = 0; i < 100; i++) अणु
		/* This is incredibly slow (approx 20 ms) */
		अचिन्हित पूर्णांक status;

		usleep_range(1000, 3000);
		status = inb(dev->iobase + DT2815_STATUS);
		अगर (status == 4) अणु
			अचिन्हित पूर्णांक program;

			program = (it->options[4] & 0x3) << 3 | 0x7;
			outb(program, dev->iobase + DT2815_DATA);
			dev_dbg(dev->class_dev, "program: 0x%x (@t=%d)\n",
				program, i);
			अवरोध;
		पूर्ण अन्यथा अगर (status != 0x00) अणु
			dev_dbg(dev->class_dev,
				"unexpected status 0x%x (@t=%d)\n",
				status, i);
			अगर (status & 0x60)
				outb(0x00, dev->iobase + DT2815_STATUS);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver dt2815_driver = अणु
	.driver_name	= "dt2815",
	.module		= THIS_MODULE,
	.attach		= dt2815_attach,
	.detach		= comedi_legacy_detach,
पूर्ण;
module_comedi_driver(dt2815_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
