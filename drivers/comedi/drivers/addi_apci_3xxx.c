<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * addi_apci_3xxx.c
 * Copyright (C) 2004,2005  ADDI-DATA GmbH क्रम the source code of this module.
 * Project manager: S. Weber
 *
 *	ADDI-DATA GmbH
 *	Dieselstrasse 3
 *	D-77833 Ottersweier
 *	Tel: +19(0)7223/9493-0
 *	Fax: +49(0)7223/9493-92
 *	http://www.addi-data.com
 *	info@addi-data.com
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedi_pci.h"

#घोषणा CONV_UNIT_NS		BIT(0)
#घोषणा CONV_UNIT_US		BIT(1)
#घोषणा CONV_UNIT_MS		BIT(2)

अटल स्थिर काष्ठा comedi_lrange apci3xxx_ai_range = अणु
	8, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2),
		BIP_RANGE(1),
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2),
		UNI_RANGE(1)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange apci3xxx_ao_range = अणु
	2, अणु
		BIP_RANGE(10),
		UNI_RANGE(10)
	पूर्ण
पूर्ण;

क्रमागत apci3xxx_boardid अणु
	BOARD_APCI3000_16,
	BOARD_APCI3000_8,
	BOARD_APCI3000_4,
	BOARD_APCI3006_16,
	BOARD_APCI3006_8,
	BOARD_APCI3006_4,
	BOARD_APCI3010_16,
	BOARD_APCI3010_8,
	BOARD_APCI3010_4,
	BOARD_APCI3016_16,
	BOARD_APCI3016_8,
	BOARD_APCI3016_4,
	BOARD_APCI3100_16_4,
	BOARD_APCI3100_8_4,
	BOARD_APCI3106_16_4,
	BOARD_APCI3106_8_4,
	BOARD_APCI3110_16_4,
	BOARD_APCI3110_8_4,
	BOARD_APCI3116_16_4,
	BOARD_APCI3116_8_4,
	BOARD_APCI3003,
	BOARD_APCI3002_16,
	BOARD_APCI3002_8,
	BOARD_APCI3002_4,
	BOARD_APCI3500,
पूर्ण;

काष्ठा apci3xxx_boardinfo अणु
	स्थिर अक्षर *name;
	पूर्णांक ai_subdev_flags;
	पूर्णांक ai_n_chan;
	अचिन्हित पूर्णांक ai_maxdata;
	अचिन्हित अक्षर ai_conv_units;
	अचिन्हित पूर्णांक ai_min_acq_ns;
	अचिन्हित पूर्णांक has_ao:1;
	अचिन्हित पूर्णांक has_dig_in:1;
	अचिन्हित पूर्णांक has_dig_out:1;
	अचिन्हित पूर्णांक has_ttl_io:1;
पूर्ण;

अटल स्थिर काष्ठा apci3xxx_boardinfo apci3xxx_boardtypes[] = अणु
	[BOARD_APCI3000_16] = अणु
		.name			= "apci3000-16",
		.ai_subdev_flags	= SDF_COMMON | SDF_GROUND | SDF_DIFF,
		.ai_n_chan		= 16,
		.ai_maxdata		= 0x0fff,
		.ai_conv_units		= CONV_UNIT_MS | CONV_UNIT_US,
		.ai_min_acq_ns		= 10000,
		.has_ttl_io		= 1,
	पूर्ण,
	[BOARD_APCI3000_8] = अणु
		.name			= "apci3000-8",
		.ai_subdev_flags	= SDF_COMMON | SDF_GROUND | SDF_DIFF,
		.ai_n_chan		= 8,
		.ai_maxdata		= 0x0fff,
		.ai_conv_units		= CONV_UNIT_MS | CONV_UNIT_US,
		.ai_min_acq_ns		= 10000,
		.has_ttl_io		= 1,
	पूर्ण,
	[BOARD_APCI3000_4] = अणु
		.name			= "apci3000-4",
		.ai_subdev_flags	= SDF_COMMON | SDF_GROUND | SDF_DIFF,
		.ai_n_chan		= 4,
		.ai_maxdata		= 0x0fff,
		.ai_conv_units		= CONV_UNIT_MS | CONV_UNIT_US,
		.ai_min_acq_ns		= 10000,
		.has_ttl_io		= 1,
	पूर्ण,
	[BOARD_APCI3006_16] = अणु
		.name			= "apci3006-16",
		.ai_subdev_flags	= SDF_COMMON | SDF_GROUND | SDF_DIFF,
		.ai_n_chan		= 16,
		.ai_maxdata		= 0xffff,
		.ai_conv_units		= CONV_UNIT_MS | CONV_UNIT_US,
		.ai_min_acq_ns		= 10000,
		.has_ttl_io		= 1,
	पूर्ण,
	[BOARD_APCI3006_8] = अणु
		.name			= "apci3006-8",
		.ai_subdev_flags	= SDF_COMMON | SDF_GROUND | SDF_DIFF,
		.ai_n_chan		= 8,
		.ai_maxdata		= 0xffff,
		.ai_conv_units		= CONV_UNIT_MS | CONV_UNIT_US,
		.ai_min_acq_ns		= 10000,
		.has_ttl_io		= 1,
	पूर्ण,
	[BOARD_APCI3006_4] = अणु
		.name			= "apci3006-4",
		.ai_subdev_flags	= SDF_COMMON | SDF_GROUND | SDF_DIFF,
		.ai_n_chan		= 4,
		.ai_maxdata		= 0xffff,
		.ai_conv_units		= CONV_UNIT_MS | CONV_UNIT_US,
		.ai_min_acq_ns		= 10000,
		.has_ttl_io		= 1,
	पूर्ण,
	[BOARD_APCI3010_16] = अणु
		.name			= "apci3010-16",
		.ai_subdev_flags	= SDF_COMMON | SDF_GROUND | SDF_DIFF,
		.ai_n_chan		= 16,
		.ai_maxdata		= 0x0fff,
		.ai_conv_units		= CONV_UNIT_MS | CONV_UNIT_US,
		.ai_min_acq_ns		= 5000,
		.has_dig_in		= 1,
		.has_dig_out		= 1,
		.has_ttl_io		= 1,
	पूर्ण,
	[BOARD_APCI3010_8] = अणु
		.name			= "apci3010-8",
		.ai_subdev_flags	= SDF_COMMON | SDF_GROUND | SDF_DIFF,
		.ai_n_chan		= 8,
		.ai_maxdata		= 0x0fff,
		.ai_conv_units		= CONV_UNIT_MS | CONV_UNIT_US,
		.ai_min_acq_ns		= 5000,
		.has_dig_in		= 1,
		.has_dig_out		= 1,
		.has_ttl_io		= 1,
	पूर्ण,
	[BOARD_APCI3010_4] = अणु
		.name			= "apci3010-4",
		.ai_subdev_flags	= SDF_COMMON | SDF_GROUND | SDF_DIFF,
		.ai_n_chan		= 4,
		.ai_maxdata		= 0x0fff,
		.ai_conv_units		= CONV_UNIT_MS | CONV_UNIT_US,
		.ai_min_acq_ns		= 5000,
		.has_dig_in		= 1,
		.has_dig_out		= 1,
		.has_ttl_io		= 1,
	पूर्ण,
	[BOARD_APCI3016_16] = अणु
		.name			= "apci3016-16",
		.ai_subdev_flags	= SDF_COMMON | SDF_GROUND | SDF_DIFF,
		.ai_n_chan		= 16,
		.ai_maxdata		= 0xffff,
		.ai_conv_units		= CONV_UNIT_MS | CONV_UNIT_US,
		.ai_min_acq_ns		= 5000,
		.has_dig_in		= 1,
		.has_dig_out		= 1,
		.has_ttl_io		= 1,
	पूर्ण,
	[BOARD_APCI3016_8] = अणु
		.name			= "apci3016-8",
		.ai_subdev_flags	= SDF_COMMON | SDF_GROUND | SDF_DIFF,
		.ai_n_chan		= 8,
		.ai_maxdata		= 0xffff,
		.ai_conv_units		= CONV_UNIT_MS | CONV_UNIT_US,
		.ai_min_acq_ns		= 5000,
		.has_dig_in		= 1,
		.has_dig_out		= 1,
		.has_ttl_io		= 1,
	पूर्ण,
	[BOARD_APCI3016_4] = अणु
		.name			= "apci3016-4",
		.ai_subdev_flags	= SDF_COMMON | SDF_GROUND | SDF_DIFF,
		.ai_n_chan		= 4,
		.ai_maxdata		= 0xffff,
		.ai_conv_units		= CONV_UNIT_MS | CONV_UNIT_US,
		.ai_min_acq_ns		= 5000,
		.has_dig_in		= 1,
		.has_dig_out		= 1,
		.has_ttl_io		= 1,
	पूर्ण,
	[BOARD_APCI3100_16_4] = अणु
		.name			= "apci3100-16-4",
		.ai_subdev_flags	= SDF_COMMON | SDF_GROUND | SDF_DIFF,
		.ai_n_chan		= 16,
		.ai_maxdata		= 0x0fff,
		.ai_conv_units		= CONV_UNIT_MS | CONV_UNIT_US,
		.ai_min_acq_ns		= 10000,
		.has_ao			= 1,
		.has_ttl_io		= 1,
	पूर्ण,
	[BOARD_APCI3100_8_4] = अणु
		.name			= "apci3100-8-4",
		.ai_subdev_flags	= SDF_COMMON | SDF_GROUND | SDF_DIFF,
		.ai_n_chan		= 8,
		.ai_maxdata		= 0x0fff,
		.ai_conv_units		= CONV_UNIT_MS | CONV_UNIT_US,
		.ai_min_acq_ns		= 10000,
		.has_ao			= 1,
		.has_ttl_io		= 1,
	पूर्ण,
	[BOARD_APCI3106_16_4] = अणु
		.name			= "apci3106-16-4",
		.ai_subdev_flags	= SDF_COMMON | SDF_GROUND | SDF_DIFF,
		.ai_n_chan		= 16,
		.ai_maxdata		= 0xffff,
		.ai_conv_units		= CONV_UNIT_MS | CONV_UNIT_US,
		.ai_min_acq_ns		= 10000,
		.has_ao			= 1,
		.has_ttl_io		= 1,
	पूर्ण,
	[BOARD_APCI3106_8_4] = अणु
		.name			= "apci3106-8-4",
		.ai_subdev_flags	= SDF_COMMON | SDF_GROUND | SDF_DIFF,
		.ai_n_chan		= 8,
		.ai_maxdata		= 0xffff,
		.ai_conv_units		= CONV_UNIT_MS | CONV_UNIT_US,
		.ai_min_acq_ns		= 10000,
		.has_ao			= 1,
		.has_ttl_io		= 1,
	पूर्ण,
	[BOARD_APCI3110_16_4] = अणु
		.name			= "apci3110-16-4",
		.ai_subdev_flags	= SDF_COMMON | SDF_GROUND | SDF_DIFF,
		.ai_n_chan		= 16,
		.ai_maxdata		= 0x0fff,
		.ai_conv_units		= CONV_UNIT_MS | CONV_UNIT_US,
		.ai_min_acq_ns		= 5000,
		.has_ao			= 1,
		.has_dig_in		= 1,
		.has_dig_out		= 1,
		.has_ttl_io		= 1,
	पूर्ण,
	[BOARD_APCI3110_8_4] = अणु
		.name			= "apci3110-8-4",
		.ai_subdev_flags	= SDF_COMMON | SDF_GROUND | SDF_DIFF,
		.ai_n_chan		= 8,
		.ai_maxdata		= 0x0fff,
		.ai_conv_units		= CONV_UNIT_MS | CONV_UNIT_US,
		.ai_min_acq_ns		= 5000,
		.has_ao			= 1,
		.has_dig_in		= 1,
		.has_dig_out		= 1,
		.has_ttl_io		= 1,
	पूर्ण,
	[BOARD_APCI3116_16_4] = अणु
		.name			= "apci3116-16-4",
		.ai_subdev_flags	= SDF_COMMON | SDF_GROUND | SDF_DIFF,
		.ai_n_chan		= 16,
		.ai_maxdata		= 0xffff,
		.ai_conv_units		= CONV_UNIT_MS | CONV_UNIT_US,
		.ai_min_acq_ns		= 5000,
		.has_ao			= 1,
		.has_dig_in		= 1,
		.has_dig_out		= 1,
		.has_ttl_io		= 1,
	पूर्ण,
	[BOARD_APCI3116_8_4] = अणु
		.name			= "apci3116-8-4",
		.ai_subdev_flags	= SDF_COMMON | SDF_GROUND | SDF_DIFF,
		.ai_n_chan		= 8,
		.ai_maxdata		= 0xffff,
		.ai_conv_units		= CONV_UNIT_MS | CONV_UNIT_US,
		.ai_min_acq_ns		= 5000,
		.has_ao			= 1,
		.has_dig_in		= 1,
		.has_dig_out		= 1,
		.has_ttl_io		= 1,
	पूर्ण,
	[BOARD_APCI3003] = अणु
		.name			= "apci3003",
		.ai_subdev_flags	= SDF_DIFF,
		.ai_n_chan		= 4,
		.ai_maxdata		= 0xffff,
		.ai_conv_units		= CONV_UNIT_MS | CONV_UNIT_US |
					  CONV_UNIT_NS,
		.ai_min_acq_ns		= 2500,
		.has_dig_in		= 1,
		.has_dig_out		= 1,
	पूर्ण,
	[BOARD_APCI3002_16] = अणु
		.name			= "apci3002-16",
		.ai_subdev_flags	= SDF_DIFF,
		.ai_n_chan		= 16,
		.ai_maxdata		= 0xffff,
		.ai_conv_units		= CONV_UNIT_MS | CONV_UNIT_US,
		.ai_min_acq_ns		= 5000,
		.has_dig_in		= 1,
		.has_dig_out		= 1,
	पूर्ण,
	[BOARD_APCI3002_8] = अणु
		.name			= "apci3002-8",
		.ai_subdev_flags	= SDF_DIFF,
		.ai_n_chan		= 8,
		.ai_maxdata		= 0xffff,
		.ai_conv_units		= CONV_UNIT_MS | CONV_UNIT_US,
		.ai_min_acq_ns		= 5000,
		.has_dig_in		= 1,
		.has_dig_out		= 1,
	पूर्ण,
	[BOARD_APCI3002_4] = अणु
		.name			= "apci3002-4",
		.ai_subdev_flags	= SDF_DIFF,
		.ai_n_chan		= 4,
		.ai_maxdata		= 0xffff,
		.ai_conv_units		= CONV_UNIT_MS | CONV_UNIT_US,
		.ai_min_acq_ns		= 5000,
		.has_dig_in		= 1,
		.has_dig_out		= 1,
	पूर्ण,
	[BOARD_APCI3500] = अणु
		.name			= "apci3500",
		.has_ao			= 1,
		.has_ttl_io		= 1,
	पूर्ण,
पूर्ण;

काष्ठा apci3xxx_निजी अणु
	अचिन्हित पूर्णांक ai_समयr;
	अचिन्हित अक्षर ai_समय_base;
पूर्ण;

अटल irqवापस_t apci3xxx_irq_handler(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक val;

	/* Test अगर पूर्णांकerrupt occur */
	status = पढ़ोl(dev->mmio + 16);
	अगर ((status & 0x2) == 0x2) अणु
		/* Reset the पूर्णांकerrupt */
		ग_लिखोl(status, dev->mmio + 16);

		val = पढ़ोl(dev->mmio + 28);
		comedi_buf_ग_लिखो_samples(s, &val, 1);

		s->async->events |= COMEDI_CB_EOA;
		comedi_handle_events(dev, s);

		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक apci3xxx_ai_started(काष्ठा comedi_device *dev)
अणु
	अगर ((पढ़ोl(dev->mmio + 8) & 0x80000) == 0x80000)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक apci3xxx_ai_setup(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक chanspec)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(chanspec);
	अचिन्हित पूर्णांक aref = CR_AREF(chanspec);
	अचिन्हित पूर्णांक delay_mode;
	अचिन्हित पूर्णांक val;

	अगर (apci3xxx_ai_started(dev))
		वापस -EBUSY;

	/* Clear the FIFO */
	ग_लिखोl(0x10000, dev->mmio + 12);

	/* Get and save the delay mode */
	delay_mode = पढ़ोl(dev->mmio + 4);
	delay_mode &= 0xfffffef0;

	/* Channel configuration selection */
	ग_लिखोl(delay_mode, dev->mmio + 4);

	/* Make the configuration */
	val = (range & 3) | ((range >> 2) << 6) |
	      ((aref == AREF_DIFF) << 7);
	ग_लिखोl(val, dev->mmio + 0);

	/* Channel selection */
	ग_लिखोl(delay_mode | 0x100, dev->mmio + 4);
	ग_लिखोl(chan, dev->mmio + 0);

	/* Restore delay mode */
	ग_लिखोl(delay_mode, dev->mmio + 4);

	/* Set the number of sequence to 1 */
	ग_लिखोl(1, dev->mmio + 48);

	वापस 0;
पूर्ण

अटल पूर्णांक apci3xxx_ai_eoc(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s,
			   काष्ठा comedi_insn *insn,
			   अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = पढ़ोl(dev->mmio + 20);
	अगर (status & 0x1)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक apci3xxx_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	ret = apci3xxx_ai_setup(dev, insn->chanspec);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < insn->n; i++) अणु
		/* Start the conversion */
		ग_लिखोl(0x80000, dev->mmio + 8);

		/* Wait the EOS */
		ret = comedi_समयout(dev, s, insn, apci3xxx_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		/* Read the analog value */
		data[i] = पढ़ोl(dev->mmio + 28);
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci3xxx_ai_ns_to_समयr(काष्ठा comedi_device *dev,
				   अचिन्हित पूर्णांक *ns, अचिन्हित पूर्णांक flags)
अणु
	स्थिर काष्ठा apci3xxx_boardinfo *board = dev->board_ptr;
	काष्ठा apci3xxx_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक base;
	अचिन्हित पूर्णांक समयr;
	पूर्णांक समय_base;

	/* समय_base: 0 = ns, 1 = us, 2 = ms */
	क्रम (समय_base = 0; समय_base < 3; समय_base++) अणु
		/* skip unsupported समय bases */
		अगर (!(board->ai_conv_units & (1 << समय_base)))
			जारी;

		चयन (समय_base) अणु
		हाल 0:
			base = 1;
			अवरोध;
		हाल 1:
			base = 1000;
			अवरोध;
		हाल 2:
			base = 1000000;
			अवरोध;
		पूर्ण

		चयन (flags & CMDF_ROUND_MASK) अणु
		हाल CMDF_ROUND_NEAREST:
		शेष:
			समयr = DIV_ROUND_CLOSEST(*ns, base);
			अवरोध;
		हाल CMDF_ROUND_DOWN:
			समयr = *ns / base;
			अवरोध;
		हाल CMDF_ROUND_UP:
			समयr = DIV_ROUND_UP(*ns, base);
			अवरोध;
		पूर्ण

		अगर (समयr < 0x10000) अणु
			devpriv->ai_समय_base = समय_base;
			devpriv->ai_समयr = समयr;
			*ns = समयr * समय_base;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक apci3xxx_ai_cmdtest(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा apci3xxx_boardinfo *board = dev->board_ptr;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक arg;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_FOLLOW);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_TIMER);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);
	err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
					    board->ai_min_acq_ns);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* step 4: fix up any arguments */

	arg = cmd->convert_arg;
	err |= apci3xxx_ai_ns_to_समयr(dev, &arg, cmd->flags);
	err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg);

	अगर (err)
		वापस 4;

	वापस 0;
पूर्ण

अटल पूर्णांक apci3xxx_ai_cmd(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s)
अणु
	काष्ठा apci3xxx_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	पूर्णांक ret;

	ret = apci3xxx_ai_setup(dev, cmd->chanlist[0]);
	अगर (ret)
		वापस ret;

	/* Set the convert timing unit */
	ग_लिखोl(devpriv->ai_समय_base, dev->mmio + 36);

	/* Set the convert timing */
	ग_लिखोl(devpriv->ai_समयr, dev->mmio + 32);

	/* Start the conversion */
	ग_लिखोl(0x180000, dev->mmio + 8);

	वापस 0;
पूर्ण

अटल पूर्णांक apci3xxx_ai_cancel(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक apci3xxx_ao_eoc(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s,
			   काष्ठा comedi_insn *insn,
			   अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = पढ़ोl(dev->mmio + 96);
	अगर (status & 0x100)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक apci3xxx_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val = data[i];

		/* Set the range selection */
		ग_लिखोl(range, dev->mmio + 96);

		/* Write the analog value to the selected channel */
		ग_लिखोl((val << 8) | chan, dev->mmio + 100);

		/* Wait the end of transfer */
		ret = comedi_समयout(dev, s, insn, apci3xxx_ao_eoc, 0);
		अगर (ret)
			वापस ret;

		s->पढ़ोback[chan] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci3xxx_di_insn_bits(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	data[1] = inl(dev->iobase + 32) & 0xf;

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci3xxx_करो_insn_bits(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	s->state = inl(dev->iobase + 48) & 0xf;

	अगर (comedi_dio_update_state(s, data))
		outl(s->state, dev->iobase + 48);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci3xxx_dio_insn_config(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_insn *insn,
				    अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक mask = 0;
	पूर्णांक ret;

	/*
	 * Port 0 (channels 0-7) are always inमाला_दो
	 * Port 1 (channels 8-15) are always outमाला_दो
	 * Port 2 (channels 16-23) are programmable i/o
	 */
	अगर (data[0] != INSN_CONFIG_DIO_QUERY) अणु
		/* ignore all other inकाष्ठाions क्रम ports 0 and 1 */
		अगर (chan < 16)
			वापस -EINVAL;

		/* changing any channel in port 2 changes the entire port */
		mask = 0xff0000;
	पूर्ण

	ret = comedi_dio_insn_config(dev, s, insn, data, mask);
	अगर (ret)
		वापस ret;

	/* update port 2 configuration */
	outl((s->io_bits >> 24) & 0xff, dev->iobase + 224);

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci3xxx_dio_insn_bits(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक val;

	mask = comedi_dio_update_state(s, data);
	अगर (mask) अणु
		अगर (mask & 0xff)
			outl(s->state & 0xff, dev->iobase + 80);
		अगर (mask & 0xff0000)
			outl((s->state >> 16) & 0xff, dev->iobase + 112);
	पूर्ण

	val = inl(dev->iobase + 80);
	val |= (inl(dev->iobase + 64) << 8);
	अगर (s->io_bits & 0xff0000)
		val |= (inl(dev->iobase + 112) << 16);
	अन्यथा
		val |= (inl(dev->iobase + 96) << 16);

	data[1] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci3xxx_reset(काष्ठा comedi_device *dev)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	/* Disable the पूर्णांकerrupt */
	disable_irq(dev->irq);

	/* Clear the start command */
	ग_लिखोl(0, dev->mmio + 8);

	/* Reset the पूर्णांकerrupt flags */
	val = पढ़ोl(dev->mmio + 16);
	ग_लिखोl(val, dev->mmio + 16);

	/* clear the EOS */
	पढ़ोl(dev->mmio + 20);

	/* Clear the FIFO */
	क्रम (i = 0; i < 16; i++)
		val = पढ़ोl(dev->mmio + 28);

	/* Enable the पूर्णांकerrupt */
	enable_irq(dev->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक apci3xxx_स्वतः_attach(काष्ठा comedi_device *dev,
				अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा apci3xxx_boardinfo *board = शून्य;
	काष्ठा apci3xxx_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक n_subdevices;
	पूर्णांक subdev;
	पूर्णांक ret;

	अगर (context < ARRAY_SIZE(apci3xxx_boardtypes))
		board = &apci3xxx_boardtypes[context];
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	dev->iobase = pci_resource_start(pcidev, 2);
	dev->mmio = pci_ioremap_bar(pcidev, 3);
	अगर (!dev->mmio)
		वापस -ENOMEM;

	अगर (pcidev->irq > 0) अणु
		ret = request_irq(pcidev->irq, apci3xxx_irq_handler,
				  IRQF_SHARED, dev->board_name, dev);
		अगर (ret == 0)
			dev->irq = pcidev->irq;
	पूर्ण

	n_subdevices = (board->ai_n_chan ? 0 : 1) + board->has_ao +
		       board->has_dig_in + board->has_dig_out +
		       board->has_ttl_io;
	ret = comedi_alloc_subdevices(dev, n_subdevices);
	अगर (ret)
		वापस ret;

	subdev = 0;

	/* Analog Input subdevice */
	अगर (board->ai_n_chan) अणु
		s = &dev->subdevices[subdev];
		s->type		= COMEDI_SUBD_AI;
		s->subdev_flags	= SDF_READABLE | board->ai_subdev_flags;
		s->n_chan	= board->ai_n_chan;
		s->maxdata	= board->ai_maxdata;
		s->range_table	= &apci3xxx_ai_range;
		s->insn_पढ़ो	= apci3xxx_ai_insn_पढ़ो;
		अगर (dev->irq) अणु
			/*
			 * FIXME: The hardware supports multiple scan modes
			 * but the original addi-data driver only supported
			 * पढ़ोing a single channel with पूर्णांकerrupts. Need a
			 * proper datasheet to fix this.
			 *
			 * The following scan modes are supported by the
			 * hardware:
			 *   1) Single software scan
			 *   2) Single hardware triggered scan
			 *   3) Continuous software scan
			 *   4) Continuous software scan with समयr delay
			 *   5) Continuous hardware triggered scan
			 *   6) Continuous hardware triggered scan with समयr
			 *      delay
			 *
			 * For now, limit the chanlist to a single channel.
			 */
			dev->पढ़ो_subdev = s;
			s->subdev_flags	|= SDF_CMD_READ;
			s->len_chanlist	= 1;
			s->करो_cmdtest	= apci3xxx_ai_cmdtest;
			s->करो_cmd	= apci3xxx_ai_cmd;
			s->cancel	= apci3xxx_ai_cancel;
		पूर्ण

		subdev++;
	पूर्ण

	/* Analog Output subdevice */
	अगर (board->has_ao) अणु
		s = &dev->subdevices[subdev];
		s->type		= COMEDI_SUBD_AO;
		s->subdev_flags	= SDF_WRITABLE | SDF_GROUND | SDF_COMMON;
		s->n_chan	= 4;
		s->maxdata	= 0x0fff;
		s->range_table	= &apci3xxx_ao_range;
		s->insn_ग_लिखो	= apci3xxx_ao_insn_ग_लिखो;

		ret = comedi_alloc_subdev_पढ़ोback(s);
		अगर (ret)
			वापस ret;

		subdev++;
	पूर्ण

	/* Digital Input subdevice */
	अगर (board->has_dig_in) अणु
		s = &dev->subdevices[subdev];
		s->type		= COMEDI_SUBD_DI;
		s->subdev_flags	= SDF_READABLE;
		s->n_chan	= 4;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_bits	= apci3xxx_di_insn_bits;

		subdev++;
	पूर्ण

	/* Digital Output subdevice */
	अगर (board->has_dig_out) अणु
		s = &dev->subdevices[subdev];
		s->type		= COMEDI_SUBD_DO;
		s->subdev_flags	= SDF_WRITABLE;
		s->n_chan	= 4;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_bits	= apci3xxx_करो_insn_bits;

		subdev++;
	पूर्ण

	/* TTL Digital I/O subdevice */
	अगर (board->has_ttl_io) अणु
		s = &dev->subdevices[subdev];
		s->type		= COMEDI_SUBD_DIO;
		s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
		s->n_chan	= 24;
		s->maxdata	= 1;
		s->io_bits	= 0xff;	/* channels 0-7 are always outमाला_दो */
		s->range_table	= &range_digital;
		s->insn_config	= apci3xxx_dio_insn_config;
		s->insn_bits	= apci3xxx_dio_insn_bits;

		subdev++;
	पूर्ण

	apci3xxx_reset(dev);
	वापस 0;
पूर्ण

अटल व्योम apci3xxx_detach(काष्ठा comedi_device *dev)
अणु
	अगर (dev->iobase)
		apci3xxx_reset(dev);
	comedi_pci_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver apci3xxx_driver = अणु
	.driver_name	= "addi_apci_3xxx",
	.module		= THIS_MODULE,
	.स्वतः_attach	= apci3xxx_स्वतः_attach,
	.detach		= apci3xxx_detach,
पूर्ण;

अटल पूर्णांक apci3xxx_pci_probe(काष्ठा pci_dev *dev,
			      स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &apci3xxx_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id apci3xxx_pci_table[] = अणु
	अणु PCI_VDEVICE(ADDIDATA, 0x3010), BOARD_APCI3000_16 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x300f), BOARD_APCI3000_8 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x300e), BOARD_APCI3000_4 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x3013), BOARD_APCI3006_16 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x3014), BOARD_APCI3006_8 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x3015), BOARD_APCI3006_4 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x3016), BOARD_APCI3010_16 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x3017), BOARD_APCI3010_8 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x3018), BOARD_APCI3010_4 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x3019), BOARD_APCI3016_16 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x301a), BOARD_APCI3016_8 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x301b), BOARD_APCI3016_4 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x301c), BOARD_APCI3100_16_4 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x301d), BOARD_APCI3100_8_4 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x301e), BOARD_APCI3106_16_4 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x301f), BOARD_APCI3106_8_4 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x3020), BOARD_APCI3110_16_4 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x3021), BOARD_APCI3110_8_4 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x3022), BOARD_APCI3116_16_4 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x3023), BOARD_APCI3116_8_4 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x300B), BOARD_APCI3003 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x3002), BOARD_APCI3002_16 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x3003), BOARD_APCI3002_8 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x3004), BOARD_APCI3002_4 पूर्ण,
	अणु PCI_VDEVICE(ADDIDATA, 0x3024), BOARD_APCI3500 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, apci3xxx_pci_table);

अटल काष्ठा pci_driver apci3xxx_pci_driver = अणु
	.name		= "addi_apci_3xxx",
	.id_table	= apci3xxx_pci_table,
	.probe		= apci3xxx_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(apci3xxx_driver, apci3xxx_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
