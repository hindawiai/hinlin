<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ii_pci20kc.c
 * Driver क्रम Intelligent Instruments PCI-20001C carrier board and modules.
 *
 * Copyright (C) 2000 Markus Kempf <kempf@matsci.uni-sb.de>
 * with suggestions from David Schleef		16.06.2000
 */

/*
 * Driver: ii_pci20kc
 * Description: Intelligent Instruments PCI-20001C carrier board
 * Devices: [Intelligent Instrumentation] PCI-20001C (ii_pci20kc)
 * Author: Markus Kempf <kempf@matsci.uni-sb.de>
 * Status: works
 *
 * Supports the PCI-20001C-1a and PCI-20001C-2a carrier boards. The
 * -2a version has 32 on-board DIO channels. Three add-on modules
 * can be added to the carrier board क्रम additional functionality.
 *
 * Supported add-on modules:
 *	PCI-20006M-1   1 channel, 16-bit analog output module
 *	PCI-20006M-2   2 channel, 16-bit analog output module
 *	PCI-20341M-1A  4 channel, 16-bit analog input module
 *
 * Options:
 *   0   Board base address
 *   1   IRQ (not-used)
 */

#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश "../comedidev.h"

/*
 * Register I/O map
 */
#घोषणा II20K_SIZE			0x400
#घोषणा II20K_MOD_OFFSET		0x100
#घोषणा II20K_ID_REG			0x00
#घोषणा II20K_ID_MOD1_EMPTY		BIT(7)
#घोषणा II20K_ID_MOD2_EMPTY		BIT(6)
#घोषणा II20K_ID_MOD3_EMPTY		BIT(5)
#घोषणा II20K_ID_MASK			0x1f
#घोषणा II20K_ID_PCI20001C_1A		0x1b	/* no on-board DIO */
#घोषणा II20K_ID_PCI20001C_2A		0x1d	/* on-board DIO */
#घोषणा II20K_MOD_STATUS_REG		0x40
#घोषणा II20K_MOD_STATUS_IRQ_MOD1	BIT(7)
#घोषणा II20K_MOD_STATUS_IRQ_MOD2	BIT(6)
#घोषणा II20K_MOD_STATUS_IRQ_MOD3	BIT(5)
#घोषणा II20K_DIO0_REG			0x80
#घोषणा II20K_DIO1_REG			0x81
#घोषणा II20K_सूची_ENA_REG		0x82
#घोषणा II20K_सूची_DIO3_OUT		BIT(7)
#घोषणा II20K_सूची_DIO2_OUT		BIT(6)
#घोषणा II20K_BUF_DISAB_DIO3		BIT(5)
#घोषणा II20K_BUF_DISAB_DIO2		BIT(4)
#घोषणा II20K_सूची_DIO1_OUT		BIT(3)
#घोषणा II20K_सूची_DIO0_OUT		BIT(2)
#घोषणा II20K_BUF_DISAB_DIO1		BIT(1)
#घोषणा II20K_BUF_DISAB_DIO0		BIT(0)
#घोषणा II20K_CTRL01_REG		0x83
#घोषणा II20K_CTRL01_SET		BIT(7)
#घोषणा II20K_CTRL01_DIO0_IN		BIT(4)
#घोषणा II20K_CTRL01_DIO1_IN		BIT(1)
#घोषणा II20K_DIO2_REG			0xc0
#घोषणा II20K_DIO3_REG			0xc1
#घोषणा II20K_CTRL23_REG		0xc3
#घोषणा II20K_CTRL23_SET		BIT(7)
#घोषणा II20K_CTRL23_DIO2_IN		BIT(4)
#घोषणा II20K_CTRL23_DIO3_IN		BIT(1)

#घोषणा II20K_ID_PCI20006M_1		0xe2	/* 1 AO channels */
#घोषणा II20K_ID_PCI20006M_2		0xe3	/* 2 AO channels */
#घोषणा II20K_AO_STRB_REG(x)		(0x0b + ((x) * 0x08))
#घोषणा II20K_AO_LSB_REG(x)		(0x0d + ((x) * 0x08))
#घोषणा II20K_AO_MSB_REG(x)		(0x0e + ((x) * 0x08))
#घोषणा II20K_AO_STRB_BOTH_REG		0x1b

#घोषणा II20K_ID_PCI20341M_1		0x77	/* 4 AI channels */
#घोषणा II20K_AI_STATUS_CMD_REG		0x01
#घोषणा II20K_AI_STATUS_CMD_BUSY	BIT(7)
#घोषणा II20K_AI_STATUS_CMD_HW_ENA	BIT(1)
#घोषणा II20K_AI_STATUS_CMD_EXT_START	BIT(0)
#घोषणा II20K_AI_LSB_REG		0x02
#घोषणा II20K_AI_MSB_REG		0x03
#घोषणा II20K_AI_PACER_RESET_REG	0x04
#घोषणा II20K_AI_16BIT_DATA_REG		0x06
#घोषणा II20K_AI_CONF_REG		0x10
#घोषणा II20K_AI_CONF_ENA		BIT(2)
#घोषणा II20K_AI_OPT_REG		0x11
#घोषणा II20K_AI_OPT_TRIG_ENA		BIT(5)
#घोषणा II20K_AI_OPT_TRIG_INV		BIT(4)
#घोषणा II20K_AI_OPT_TIMEBASE(x)	(((x) & 0x3) << 1)
#घोषणा II20K_AI_OPT_BURST_MODE		BIT(0)
#घोषणा II20K_AI_STATUS_REG		0x12
#घोषणा II20K_AI_STATUS_INT		BIT(7)
#घोषणा II20K_AI_STATUS_TRIG		BIT(6)
#घोषणा II20K_AI_STATUS_TRIG_ENA	BIT(5)
#घोषणा II20K_AI_STATUS_PACER_ERR	BIT(2)
#घोषणा II20K_AI_STATUS_DATA_ERR	BIT(1)
#घोषणा II20K_AI_STATUS_SET_TIME_ERR	BIT(0)
#घोषणा II20K_AI_LAST_CHAN_ADDR_REG	0x13
#घोषणा II20K_AI_CUR_ADDR_REG		0x14
#घोषणा II20K_AI_SET_TIME_REG		0x15
#घोषणा II20K_AI_DELAY_LSB_REG		0x16
#घोषणा II20K_AI_DELAY_MSB_REG		0x17
#घोषणा II20K_AI_CHAN_ADV_REG		0x18
#घोषणा II20K_AI_CHAN_RESET_REG		0x19
#घोषणा II20K_AI_START_TRIG_REG		0x1a
#घोषणा II20K_AI_COUNT_RESET_REG	0x1b
#घोषणा II20K_AI_CHANLIST_REG		0x80
#घोषणा II20K_AI_CHANLIST_ONBOARD_ONLY	BIT(5)
#घोषणा II20K_AI_CHANLIST_GAIN(x)	(((x) & 0x3) << 3)
#घोषणा II20K_AI_CHANLIST_MUX_ENA	BIT(2)
#घोषणा II20K_AI_CHANLIST_CHAN(x)	(((x) & 0x3) << 0)
#घोषणा II20K_AI_CHANLIST_LEN		0x80

/* the AO range is set by jumpers on the 20006M module */
अटल स्थिर काष्ठा comedi_lrange ii20k_ao_ranges = अणु
	3, अणु
		BIP_RANGE(5),	/* Chan 0 - W1/W3 in   Chan 1 - W2/W4 in  */
		UNI_RANGE(10),	/* Chan 0 - W1/W3 out  Chan 1 - W2/W4 in  */
		BIP_RANGE(10)	/* Chan 0 - W1/W3 in   Chan 1 - W2/W4 out */
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange ii20k_ai_ranges = अणु
	4, अणु
		BIP_RANGE(5),		/* gain 1 */
		BIP_RANGE(0.5),		/* gain 10 */
		BIP_RANGE(0.05),	/* gain 100 */
		BIP_RANGE(0.025)	/* gain 200 */
	पूर्ण,
पूर्ण;

अटल व्योम __iomem *ii20k_module_iobase(काष्ठा comedi_device *dev,
					 काष्ठा comedi_subdevice *s)
अणु
	वापस dev->mmio + (s->index + 1) * II20K_MOD_OFFSET;
पूर्ण

अटल पूर्णांक ii20k_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	व्योम __iomem *iobase = ii20k_module_iobase(dev, s);
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val = data[i];

		s->पढ़ोback[chan] = val;

		/* munge the offset binary data to 2's complement */
		val = comedi_offset_munge(s, val);

		ग_लिखोb(val & 0xff, iobase + II20K_AO_LSB_REG(chan));
		ग_लिखोb((val >> 8) & 0xff, iobase + II20K_AO_MSB_REG(chan));
		ग_लिखोb(0x00, iobase + II20K_AO_STRB_REG(chan));
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक ii20k_ai_eoc(काष्ठा comedi_device *dev,
			काष्ठा comedi_subdevice *s,
			काष्ठा comedi_insn *insn,
			अचिन्हित दीर्घ context)
अणु
	व्योम __iomem *iobase = ii20k_module_iobase(dev, s);
	अचिन्हित अक्षर status;

	status = पढ़ोb(iobase + II20K_AI_STATUS_REG);
	अगर ((status & II20K_AI_STATUS_INT) == 0)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल व्योम ii20k_ai_setup(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s,
			   अचिन्हित पूर्णांक chanspec)
अणु
	व्योम __iomem *iobase = ii20k_module_iobase(dev, s);
	अचिन्हित पूर्णांक chan = CR_CHAN(chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(chanspec);
	अचिन्हित अक्षर val;

	/* initialize module */
	ग_लिखोb(II20K_AI_CONF_ENA, iobase + II20K_AI_CONF_REG);

	/* software conversion */
	ग_लिखोb(0, iobase + II20K_AI_STATUS_CMD_REG);

	/* set the समय base क्रम the settling समय counter based on the gain */
	val = (range < 3) ? II20K_AI_OPT_TIMEBASE(0) : II20K_AI_OPT_TIMEBASE(2);
	ग_लिखोb(val, iobase + II20K_AI_OPT_REG);

	/* set the settling समय counter based on the gain */
	val = (range < 2) ? 0x58 : (range < 3) ? 0x93 : 0x99;
	ग_लिखोb(val, iobase + II20K_AI_SET_TIME_REG);

	/* set number of input channels */
	ग_लिखोb(1, iobase + II20K_AI_LAST_CHAN_ADDR_REG);

	/* set the channel list byte */
	val = II20K_AI_CHANLIST_ONBOARD_ONLY |
	      II20K_AI_CHANLIST_MUX_ENA |
	      II20K_AI_CHANLIST_GAIN(range) |
	      II20K_AI_CHANLIST_CHAN(chan);
	ग_लिखोb(val, iobase + II20K_AI_CHANLIST_REG);

	/* reset settling समय counter and trigger delay counter */
	ग_लिखोb(0, iobase + II20K_AI_COUNT_RESET_REG);

	/* reset channel scanner */
	ग_लिखोb(0, iobase + II20K_AI_CHAN_RESET_REG);
पूर्ण

अटल पूर्णांक ii20k_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	व्योम __iomem *iobase = ii20k_module_iobase(dev, s);
	पूर्णांक ret;
	पूर्णांक i;

	ii20k_ai_setup(dev, s, insn->chanspec);

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val;

		/* generate a software start convert संकेत */
		पढ़ोb(iobase + II20K_AI_PACER_RESET_REG);

		ret = comedi_समयout(dev, s, insn, ii20k_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		val = पढ़ोb(iobase + II20K_AI_LSB_REG);
		val |= (पढ़ोb(iobase + II20K_AI_MSB_REG) << 8);

		/* munge the 2's complement data to offset binary */
		data[i] = comedi_offset_munge(s, val);
	पूर्ण

	वापस insn->n;
पूर्ण

अटल व्योम ii20k_dio_config(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित अक्षर ctrl01 = 0;
	अचिन्हित अक्षर ctrl23 = 0;
	अचिन्हित अक्षर dir_ena = 0;

	/* port 0 - channels 0-7 */
	अगर (s->io_bits & 0x000000ff) अणु
		/* output port */
		ctrl01 &= ~II20K_CTRL01_DIO0_IN;
		dir_ena &= ~II20K_BUF_DISAB_DIO0;
		dir_ena |= II20K_सूची_DIO0_OUT;
	पूर्ण अन्यथा अणु
		/* input port */
		ctrl01 |= II20K_CTRL01_DIO0_IN;
		dir_ena &= ~II20K_सूची_DIO0_OUT;
	पूर्ण

	/* port 1 - channels 8-15 */
	अगर (s->io_bits & 0x0000ff00) अणु
		/* output port */
		ctrl01 &= ~II20K_CTRL01_DIO1_IN;
		dir_ena &= ~II20K_BUF_DISAB_DIO1;
		dir_ena |= II20K_सूची_DIO1_OUT;
	पूर्ण अन्यथा अणु
		/* input port */
		ctrl01 |= II20K_CTRL01_DIO1_IN;
		dir_ena &= ~II20K_सूची_DIO1_OUT;
	पूर्ण

	/* port 2 - channels 16-23 */
	अगर (s->io_bits & 0x00ff0000) अणु
		/* output port */
		ctrl23 &= ~II20K_CTRL23_DIO2_IN;
		dir_ena &= ~II20K_BUF_DISAB_DIO2;
		dir_ena |= II20K_सूची_DIO2_OUT;
	पूर्ण अन्यथा अणु
		/* input port */
		ctrl23 |= II20K_CTRL23_DIO2_IN;
		dir_ena &= ~II20K_सूची_DIO2_OUT;
	पूर्ण

	/* port 3 - channels 24-31 */
	अगर (s->io_bits & 0xff000000) अणु
		/* output port */
		ctrl23 &= ~II20K_CTRL23_DIO3_IN;
		dir_ena &= ~II20K_BUF_DISAB_DIO3;
		dir_ena |= II20K_सूची_DIO3_OUT;
	पूर्ण अन्यथा अणु
		/* input port */
		ctrl23 |= II20K_CTRL23_DIO3_IN;
		dir_ena &= ~II20K_सूची_DIO3_OUT;
	पूर्ण

	ctrl23 |= II20K_CTRL01_SET;
	ctrl23 |= II20K_CTRL23_SET;

	/* order is important */
	ग_लिखोb(ctrl01, dev->mmio + II20K_CTRL01_REG);
	ग_लिखोb(ctrl23, dev->mmio + II20K_CTRL23_REG);
	ग_लिखोb(dir_ena, dev->mmio + II20K_सूची_ENA_REG);
पूर्ण

अटल पूर्णांक ii20k_dio_insn_config(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक mask;
	पूर्णांक ret;

	अगर (chan < 8)
		mask = 0x000000ff;
	अन्यथा अगर (chan < 16)
		mask = 0x0000ff00;
	अन्यथा अगर (chan < 24)
		mask = 0x00ff0000;
	अन्यथा
		mask = 0xff000000;

	ret = comedi_dio_insn_config(dev, s, insn, data, mask);
	अगर (ret)
		वापस ret;

	ii20k_dio_config(dev, s);

	वापस insn->n;
पूर्ण

अटल पूर्णांक ii20k_dio_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक mask;

	mask = comedi_dio_update_state(s, data);
	अगर (mask) अणु
		अगर (mask & 0x000000ff)
			ग_लिखोb((s->state >> 0) & 0xff,
			       dev->mmio + II20K_DIO0_REG);
		अगर (mask & 0x0000ff00)
			ग_लिखोb((s->state >> 8) & 0xff,
			       dev->mmio + II20K_DIO1_REG);
		अगर (mask & 0x00ff0000)
			ग_लिखोb((s->state >> 16) & 0xff,
			       dev->mmio + II20K_DIO2_REG);
		अगर (mask & 0xff000000)
			ग_लिखोb((s->state >> 24) & 0xff,
			       dev->mmio + II20K_DIO3_REG);
	पूर्ण

	data[1] = पढ़ोb(dev->mmio + II20K_DIO0_REG);
	data[1] |= पढ़ोb(dev->mmio + II20K_DIO1_REG) << 8;
	data[1] |= पढ़ोb(dev->mmio + II20K_DIO2_REG) << 16;
	data[1] |= पढ़ोb(dev->mmio + II20K_DIO3_REG) << 24;

	वापस insn->n;
पूर्ण

अटल पूर्णांक ii20k_init_module(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s)
अणु
	व्योम __iomem *iobase = ii20k_module_iobase(dev, s);
	अचिन्हित अक्षर id;
	पूर्णांक ret;

	id = पढ़ोb(iobase + II20K_ID_REG);
	चयन (id) अणु
	हाल II20K_ID_PCI20006M_1:
	हाल II20K_ID_PCI20006M_2:
		/* Analog Output subdevice */
		s->type		= COMEDI_SUBD_AO;
		s->subdev_flags	= SDF_WRITABLE;
		s->n_chan	= (id == II20K_ID_PCI20006M_2) ? 2 : 1;
		s->maxdata	= 0xffff;
		s->range_table	= &ii20k_ao_ranges;
		s->insn_ग_लिखो	= ii20k_ao_insn_ग_लिखो;

		ret = comedi_alloc_subdev_पढ़ोback(s);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल II20K_ID_PCI20341M_1:
		/* Analog Input subdevice */
		s->type		= COMEDI_SUBD_AI;
		s->subdev_flags	= SDF_READABLE | SDF_DIFF;
		s->n_chan	= 4;
		s->maxdata	= 0xffff;
		s->range_table	= &ii20k_ai_ranges;
		s->insn_पढ़ो	= ii20k_ai_insn_पढ़ो;
		अवरोध;
	शेष:
		s->type = COMEDI_SUBD_UNUSED;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ii20k_attach(काष्ठा comedi_device *dev,
			काष्ठा comedi_devconfig *it)
अणु
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक membase;
	अचिन्हित अक्षर id;
	bool has_dio;
	पूर्णांक ret;

	membase = it->options[0];
	अगर (!membase || (membase & ~(0x100000 - II20K_SIZE))) अणु
		dev_warn(dev->class_dev,
			 "%s: invalid memory address specified\n",
			 dev->board_name);
		वापस -EINVAL;
	पूर्ण

	अगर (!request_mem_region(membase, II20K_SIZE, dev->board_name)) अणु
		dev_warn(dev->class_dev, "%s: I/O mem conflict (%#x,%u)\n",
			 dev->board_name, membase, II20K_SIZE);
		वापस -EIO;
	पूर्ण
	dev->iobase = membase;	/* actually, a memory address */

	dev->mmio = ioremap(membase, II20K_SIZE);
	अगर (!dev->mmio)
		वापस -ENOMEM;

	id = पढ़ोb(dev->mmio + II20K_ID_REG);
	चयन (id & II20K_ID_MASK) अणु
	हाल II20K_ID_PCI20001C_1A:
		has_dio = false;
		अवरोध;
	हाल II20K_ID_PCI20001C_2A:
		has_dio = true;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	अगर (id & II20K_ID_MOD1_EMPTY) अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण अन्यथा अणु
		ret = ii20k_init_module(dev, s);
		अगर (ret)
			वापस ret;
	पूर्ण

	s = &dev->subdevices[1];
	अगर (id & II20K_ID_MOD2_EMPTY) अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण अन्यथा अणु
		ret = ii20k_init_module(dev, s);
		अगर (ret)
			वापस ret;
	पूर्ण

	s = &dev->subdevices[2];
	अगर (id & II20K_ID_MOD3_EMPTY) अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण अन्यथा अणु
		ret = ii20k_init_module(dev, s);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Digital I/O subdevice */
	s = &dev->subdevices[3];
	अगर (has_dio) अणु
		s->type		= COMEDI_SUBD_DIO;
		s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
		s->n_chan	= 32;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_bits	= ii20k_dio_insn_bits;
		s->insn_config	= ii20k_dio_insn_config;

		/* शेष all channels to input */
		ii20k_dio_config(dev, s);
	पूर्ण अन्यथा अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ii20k_detach(काष्ठा comedi_device *dev)
अणु
	अगर (dev->mmio)
		iounmap(dev->mmio);
	अगर (dev->iobase)	/* actually, a memory address */
		release_mem_region(dev->iobase, II20K_SIZE);
पूर्ण

अटल काष्ठा comedi_driver ii20k_driver = अणु
	.driver_name	= "ii_pci20kc",
	.module		= THIS_MODULE,
	.attach		= ii20k_attach,
	.detach		= ii20k_detach,
पूर्ण;
module_comedi_driver(ii20k_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for Intelligent Instruments PCI-20001C");
MODULE_LICENSE("GPL");
