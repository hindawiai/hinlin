<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * dmm32at.c
 * Diamond Systems Diamond-MM-32-AT Comedi driver
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: dmm32at
 * Description: Diamond Systems Diamond-MM-32-AT
 * Devices: [Diamond Systems] Diamond-MM-32-AT (dmm32at)
 * Author: Perry J. Piplani <perry.j.piplani@nasa.gov>
 * Updated: Fri Jun  4 09:13:24 CDT 2004
 * Status: experimental
 *
 * Configuration Options:
 *	comedi_config /dev/comedi0 dmm32at baseaddr,irq
 *
 * This driver is क्रम the Diamond Systems MM-32-AT board
 *	http://www.diamondप्रणालीs.com/products/diamondmm32at
 *
 * It is being used on several projects inside NASA, without
 * problems so far. For analog input commands, TRIG_EXT is not
 * yet supported.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश "../comedidev.h"

#समावेश "8255.h"

/* Board रेजिस्टर addresses */
#घोषणा DMM32AT_AI_START_CONV_REG	0x00
#घोषणा DMM32AT_AI_LSB_REG		0x00
#घोषणा DMM32AT_AUX_DOUT_REG		0x01
#घोषणा DMM32AT_AUX_DOUT2		BIT(2)  /* J3.42 - OUT2 (OUT2EN) */
#घोषणा DMM32AT_AUX_DOUT1		BIT(1)  /* J3.43 */
#घोषणा DMM32AT_AUX_DOUT0		BIT(0)  /* J3.44 - OUT0 (OUT0EN) */
#घोषणा DMM32AT_AI_MSB_REG		0x01
#घोषणा DMM32AT_AI_LO_CHAN_REG		0x02
#घोषणा DMM32AT_AI_HI_CHAN_REG		0x03
#घोषणा DMM32AT_AUX_DI_REG		0x04
#घोषणा DMM32AT_AUX_DI_DACBUSY		BIT(7)
#घोषणा DMM32AT_AUX_DI_CALBUSY		BIT(6)
#घोषणा DMM32AT_AUX_DI3			BIT(3)  /* J3.45 - ADCLK (CLKSEL) */
#घोषणा DMM32AT_AUX_DI2			BIT(2)  /* J3.46 - GATE12 (GT12EN) */
#घोषणा DMM32AT_AUX_DI1			BIT(1)  /* J3.47 - GATE0 (GT0EN) */
#घोषणा DMM32AT_AUX_DI0			BIT(0)  /* J3.48 - CLK0 (SRC0) */
#घोषणा DMM32AT_AO_LSB_REG		0x04
#घोषणा DMM32AT_AO_MSB_REG		0x05
#घोषणा DMM32AT_AO_MSB_DACH(x)		((x) << 6)
#घोषणा DMM32AT_FIFO_DEPTH_REG		0x06
#घोषणा DMM32AT_FIFO_CTRL_REG		0x07
#घोषणा DMM32AT_FIFO_CTRL_FIFOEN	BIT(3)
#घोषणा DMM32AT_FIFO_CTRL_SCANEN	BIT(2)
#घोषणा DMM32AT_FIFO_CTRL_FIFORST	BIT(1)
#घोषणा DMM32AT_FIFO_STATUS_REG		0x07
#घोषणा DMM32AT_FIFO_STATUS_EF		BIT(7)
#घोषणा DMM32AT_FIFO_STATUS_HF		BIT(6)
#घोषणा DMM32AT_FIFO_STATUS_FF		BIT(5)
#घोषणा DMM32AT_FIFO_STATUS_OVF		BIT(4)
#घोषणा DMM32AT_FIFO_STATUS_FIFOEN	BIT(3)
#घोषणा DMM32AT_FIFO_STATUS_SCANEN	BIT(2)
#घोषणा DMM32AT_FIFO_STATUS_PAGE_MASK	(3 << 0)
#घोषणा DMM32AT_CTRL_REG		0x08
#घोषणा DMM32AT_CTRL_RESETA		BIT(5)
#घोषणा DMM32AT_CTRL_RESETD		BIT(4)
#घोषणा DMM32AT_CTRL_INTRST		BIT(3)
#घोषणा DMM32AT_CTRL_PAGE(x)		((x) << 0)
#घोषणा DMM32AT_CTRL_PAGE_8254		DMM32AT_CTRL_PAGE(0)
#घोषणा DMM32AT_CTRL_PAGE_8255		DMM32AT_CTRL_PAGE(1)
#घोषणा DMM32AT_CTRL_PAGE_CALIB		DMM32AT_CTRL_PAGE(3)
#घोषणा DMM32AT_AI_STATUS_REG		0x08
#घोषणा DMM32AT_AI_STATUS_STS		BIT(7)
#घोषणा DMM32AT_AI_STATUS_SD1		BIT(6)
#घोषणा DMM32AT_AI_STATUS_SD0		BIT(5)
#घोषणा DMM32AT_AI_STATUS_ADCH_MASK	(0x1f << 0)
#घोषणा DMM32AT_INTCLK_REG		0x09
#घोषणा DMM32AT_INTCLK_ADINT		BIT(7)
#घोषणा DMM32AT_INTCLK_DINT		BIT(6)
#घोषणा DMM32AT_INTCLK_TINT		BIT(5)
#घोषणा DMM32AT_INTCLK_CLKEN		BIT(1)  /* 1=see below  0=software */
#घोषणा DMM32AT_INTCLK_CLKSEL		BIT(0)  /* 1=OUT2  0=EXTCLK */
#घोषणा DMM32AT_CTRDIO_CFG_REG		0x0a
#घोषणा DMM32AT_CTRDIO_CFG_FREQ12	BIT(7)  /* CLK12 1=100KHz 0=10MHz */
#घोषणा DMM32AT_CTRDIO_CFG_FREQ0	BIT(6)  /* CLK0  1=10KHz  0=10MHz */
#घोषणा DMM32AT_CTRDIO_CFG_OUT2EN	BIT(5)  /* J3.42 1=OUT2 is DOUT2 */
#घोषणा DMM32AT_CTRDIO_CFG_OUT0EN	BIT(4)  /* J3,44 1=OUT0 is DOUT0 */
#घोषणा DMM32AT_CTRDIO_CFG_GT0EN	BIT(2)  /* J3.47 1=DIN1 is GATE0 */
#घोषणा DMM32AT_CTRDIO_CFG_SRC0		BIT(1)  /* CLK0 is 0=FREQ0 1=J3.48 */
#घोषणा DMM32AT_CTRDIO_CFG_GT12EN	BIT(0)  /* J3.46 1=DIN2 is GATE12 */
#घोषणा DMM32AT_AI_CFG_REG		0x0b
#घोषणा DMM32AT_AI_CFG_SCINT(x)		((x) << 4)
#घोषणा DMM32AT_AI_CFG_SCINT_20US	DMM32AT_AI_CFG_SCINT(0)
#घोषणा DMM32AT_AI_CFG_SCINT_15US	DMM32AT_AI_CFG_SCINT(1)
#घोषणा DMM32AT_AI_CFG_SCINT_10US	DMM32AT_AI_CFG_SCINT(2)
#घोषणा DMM32AT_AI_CFG_SCINT_5US	DMM32AT_AI_CFG_SCINT(3)
#घोषणा DMM32AT_AI_CFG_RANGE		BIT(3)  /* 0=5V  1=10V */
#घोषणा DMM32AT_AI_CFG_ADBU		BIT(2)  /* 0=bipolar  1=unipolar */
#घोषणा DMM32AT_AI_CFG_GAIN(x)		((x) << 0)
#घोषणा DMM32AT_AI_READBACK_REG		0x0b
#घोषणा DMM32AT_AI_READBACK_WAIT	BIT(7)  /* DMM32AT_AI_STATUS_STS */
#घोषणा DMM32AT_AI_READBACK_RANGE	BIT(3)
#घोषणा DMM32AT_AI_READBACK_ADBU	BIT(2)
#घोषणा DMM32AT_AI_READBACK_GAIN_MASK	(3 << 0)

#घोषणा DMM32AT_CLK1 0x0d
#घोषणा DMM32AT_CLK2 0x0e
#घोषणा DMM32AT_CLKCT 0x0f

#घोषणा DMM32AT_8255_IOBASE		0x0c  /* Page 1 रेजिस्टरs */

/* Board रेजिस्टर values. */

/* DMM32AT_AI_CFG_REG 0x0b */
#घोषणा DMM32AT_RANGE_U10 0x0c
#घोषणा DMM32AT_RANGE_U5 0x0d
#घोषणा DMM32AT_RANGE_B10 0x08
#घोषणा DMM32AT_RANGE_B5 0x00

/* DMM32AT_CLKCT 0x0f */
#घोषणा DMM32AT_CLKCT1 0x56	/* mode3 counter 1 - ग_लिखो low byte only */
#घोषणा DMM32AT_CLKCT2 0xb6	/*  mode3 counter 2 - ग_लिखो high and low byte */

/* board AI ranges in comedi काष्ठाure */
अटल स्थिर काष्ठा comedi_lrange dmm32at_airanges = अणु
	4, अणु
		UNI_RANGE(10),
		UNI_RANGE(5),
		BIP_RANGE(10),
		BIP_RANGE(5)
	पूर्ण
पूर्ण;

/* रेजिस्टर values क्रम above ranges */
अटल स्थिर अचिन्हित अक्षर dmm32at_rangebits[] = अणु
	DMM32AT_RANGE_U10,
	DMM32AT_RANGE_U5,
	DMM32AT_RANGE_B10,
	DMM32AT_RANGE_B5,
पूर्ण;

/* only one of these ranges is valid, as set by a jumper on the
 * board. The application should only use the range set by the jumper
 */
अटल स्थिर काष्ठा comedi_lrange dmm32at_aoranges = अणु
	4, अणु
		UNI_RANGE(10),
		UNI_RANGE(5),
		BIP_RANGE(10),
		BIP_RANGE(5)
	पूर्ण
पूर्ण;

अटल व्योम dmm32at_ai_set_chanspec(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    अचिन्हित पूर्णांक chanspec, पूर्णांक nchan)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(chanspec);
	अचिन्हित पूर्णांक last_chan = (chan + nchan - 1) % s->n_chan;

	outb(DMM32AT_FIFO_CTRL_FIFORST, dev->iobase + DMM32AT_FIFO_CTRL_REG);

	अगर (nchan > 1)
		outb(DMM32AT_FIFO_CTRL_SCANEN,
		     dev->iobase + DMM32AT_FIFO_CTRL_REG);

	outb(chan, dev->iobase + DMM32AT_AI_LO_CHAN_REG);
	outb(last_chan, dev->iobase + DMM32AT_AI_HI_CHAN_REG);
	outb(dmm32at_rangebits[range], dev->iobase + DMM32AT_AI_CFG_REG);
पूर्ण

अटल अचिन्हित पूर्णांक dmm32at_ai_get_sample(काष्ठा comedi_device *dev,
					  काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित पूर्णांक val;

	val = inb(dev->iobase + DMM32AT_AI_LSB_REG);
	val |= (inb(dev->iobase + DMM32AT_AI_MSB_REG) << 8);

	/* munge two's complement value to offset binary */
	वापस comedi_offset_munge(s, val);
पूर्ण

अटल पूर्णांक dmm32at_ai_status(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_insn *insn,
			     अचिन्हित दीर्घ context)
अणु
	अचिन्हित अक्षर status;

	status = inb(dev->iobase + context);
	अगर ((status & DMM32AT_AI_STATUS_STS) == 0)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक dmm32at_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	dmm32at_ai_set_chanspec(dev, s, insn->chanspec, 1);

	/* रुको क्रम circuit to settle */
	ret = comedi_समयout(dev, s, insn, dmm32at_ai_status,
			     DMM32AT_AI_READBACK_REG);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < insn->n; i++) अणु
		outb(0xff, dev->iobase + DMM32AT_AI_START_CONV_REG);

		ret = comedi_समयout(dev, s, insn, dmm32at_ai_status,
				     DMM32AT_AI_STATUS_REG);
		अगर (ret)
			वापस ret;

		data[i] = dmm32at_ai_get_sample(dev, s);
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक dmm32at_ai_check_chanlist(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     काष्ठा comedi_cmd *cmd)
अणु
	अचिन्हित पूर्णांक chan0 = CR_CHAN(cmd->chanlist[0]);
	अचिन्हित पूर्णांक range0 = CR_RANGE(cmd->chanlist[0]);
	पूर्णांक i;

	क्रम (i = 1; i < cmd->chanlist_len; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);
		अचिन्हित पूर्णांक range = CR_RANGE(cmd->chanlist[i]);

		अगर (chan != (chan0 + i) % s->n_chan) अणु
			dev_dbg(dev->class_dev,
				"entries in chanlist must be consecutive channels, counting upwards\n");
			वापस -EINVAL;
		पूर्ण
		अगर (range != range0) अणु
			dev_dbg(dev->class_dev,
				"entries in chanlist must all have the same gain\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dmm32at_ai_cmdtest(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक arg;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_TIMER);
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

	err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg, 1000000);
	err |= comedi_check_trigger_arg_max(&cmd->scan_begin_arg, 1000000000);

	अगर (cmd->convert_arg >= 17500)
		cmd->convert_arg = 20000;
	अन्यथा अगर (cmd->convert_arg >= 12500)
		cmd->convert_arg = 15000;
	अन्यथा अगर (cmd->convert_arg >= 7500)
		cmd->convert_arg = 10000;
	अन्यथा
		cmd->convert_arg = 5000;

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा /* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* Step 4: fix up any arguments */

	arg = cmd->convert_arg * cmd->scan_end_arg;
	err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg, arg);

	अगर (err)
		वापस 4;

	/* Step 5: check channel list अगर it exists */
	अगर (cmd->chanlist && cmd->chanlist_len > 0)
		err |= dmm32at_ai_check_chanlist(dev, s, cmd);

	अगर (err)
		वापस 5;

	वापस 0;
पूर्ण

अटल व्योम dmm32at_setaiसमयr(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक nansec)
अणु
	अचिन्हित अक्षर lo1, lo2, hi2;
	अचिन्हित लघु both2;

	/* based on 10mhz घड़ी */
	lo1 = 200;
	both2 = nansec / 20000;
	hi2 = (both2 & 0xff00) >> 8;
	lo2 = both2 & 0x00ff;

	/* set counter घड़ीs to 10MHz, disable all aux dio */
	outb(0, dev->iobase + DMM32AT_CTRDIO_CFG_REG);

	/* get access to the घड़ी regs */
	outb(DMM32AT_CTRL_PAGE_8254, dev->iobase + DMM32AT_CTRL_REG);

	/* ग_लिखो the counter 1 control word and low byte to counter */
	outb(DMM32AT_CLKCT1, dev->iobase + DMM32AT_CLKCT);
	outb(lo1, dev->iobase + DMM32AT_CLK1);

	/* ग_लिखो the counter 2 control word and low byte then to counter */
	outb(DMM32AT_CLKCT2, dev->iobase + DMM32AT_CLKCT);
	outb(lo2, dev->iobase + DMM32AT_CLK2);
	outb(hi2, dev->iobase + DMM32AT_CLK2);

	/* enable the ai conversion पूर्णांकerrupt and the घड़ी to start scans */
	outb(DMM32AT_INTCLK_ADINT |
	     DMM32AT_INTCLK_CLKEN | DMM32AT_INTCLK_CLKSEL,
	     dev->iobase + DMM32AT_INTCLK_REG);
पूर्ण

अटल पूर्णांक dmm32at_ai_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	पूर्णांक ret;

	dmm32at_ai_set_chanspec(dev, s, cmd->chanlist[0], cmd->chanlist_len);

	/* reset the पूर्णांकerrupt just in हाल */
	outb(DMM32AT_CTRL_INTRST, dev->iobase + DMM32AT_CTRL_REG);

	/*
	 * रुको क्रम circuit to settle
	 * we करोn't have the 'insn' here but it's not needed
	 */
	ret = comedi_समयout(dev, s, शून्य, dmm32at_ai_status,
			     DMM32AT_AI_READBACK_REG);
	अगर (ret)
		वापस ret;

	अगर (cmd->stop_src == TRIG_NONE || cmd->stop_arg > 1) अणु
		/* start the घड़ी and enable the पूर्णांकerrupts */
		dmm32at_setaiसमयr(dev, cmd->scan_begin_arg);
	पूर्ण अन्यथा अणु
		/* start the पूर्णांकerrupts and initiate a single scan */
		outb(DMM32AT_INTCLK_ADINT, dev->iobase + DMM32AT_INTCLK_REG);
		outb(0xff, dev->iobase + DMM32AT_AI_START_CONV_REG);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dmm32at_ai_cancel(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s)
अणु
	/* disable further पूर्णांकerrupts and घड़ीs */
	outb(0x0, dev->iobase + DMM32AT_INTCLK_REG);
	वापस 0;
पूर्ण

अटल irqवापस_t dmm32at_isr(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	अचिन्हित अक्षर पूर्णांकstat;
	अचिन्हित लघु val;
	पूर्णांक i;

	अगर (!dev->attached) अणु
		dev_err(dev->class_dev, "spurious interrupt\n");
		वापस IRQ_HANDLED;
	पूर्ण

	पूर्णांकstat = inb(dev->iobase + DMM32AT_INTCLK_REG);

	अगर (पूर्णांकstat & DMM32AT_INTCLK_ADINT) अणु
		काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
		काष्ठा comedi_cmd *cmd = &s->async->cmd;

		क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
			val = dmm32at_ai_get_sample(dev, s);
			comedi_buf_ग_लिखो_samples(s, &val, 1);
		पूर्ण

		अगर (cmd->stop_src == TRIG_COUNT &&
		    s->async->scans_करोne >= cmd->stop_arg)
			s->async->events |= COMEDI_CB_EOA;

		comedi_handle_events(dev, s);
	पूर्ण

	/* reset the पूर्णांकerrupt */
	outb(DMM32AT_CTRL_INTRST, dev->iobase + DMM32AT_CTRL_REG);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dmm32at_ao_eoc(काष्ठा comedi_device *dev,
			  काष्ठा comedi_subdevice *s,
			  काष्ठा comedi_insn *insn,
			  अचिन्हित दीर्घ context)
अणु
	अचिन्हित अक्षर status;

	status = inb(dev->iobase + DMM32AT_AUX_DI_REG);
	अगर ((status & DMM32AT_AUX_DI_DACBUSY) == 0)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक dmm32at_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val = data[i];
		पूर्णांक ret;

		/* ग_लिखो LSB then MSB + chan to load DAC */
		outb(val & 0xff, dev->iobase + DMM32AT_AO_LSB_REG);
		outb((val >> 8) | DMM32AT_AO_MSB_DACH(chan),
		     dev->iobase + DMM32AT_AO_MSB_REG);

		/* रुको क्रम circuit to settle */
		ret = comedi_समयout(dev, s, insn, dmm32at_ao_eoc, 0);
		अगर (ret)
			वापस ret;

		/* dummy पढ़ो to update DAC */
		inb(dev->iobase + DMM32AT_AO_MSB_REG);

		s->पढ़ोback[chan] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक dmm32at_8255_io(काष्ठा comedi_device *dev,
			   पूर्णांक dir, पूर्णांक port, पूर्णांक data, अचिन्हित दीर्घ regbase)
अणु
	/* get access to the DIO regs */
	outb(DMM32AT_CTRL_PAGE_8255, dev->iobase + DMM32AT_CTRL_REG);

	अगर (dir) अणु
		outb(data, dev->iobase + regbase + port);
		वापस 0;
	पूर्ण
	वापस inb(dev->iobase + regbase + port);
पूर्ण

/* Make sure the board is there and put it to a known state */
अटल पूर्णांक dmm32at_reset(काष्ठा comedi_device *dev)
अणु
	अचिन्हित अक्षर aihi, ailo, fअगरostat, aistat, पूर्णांकstat, airback;

	/* reset the board */
	outb(DMM32AT_CTRL_RESETA, dev->iobase + DMM32AT_CTRL_REG);

	/* allow a millisecond to reset */
	usleep_range(1000, 3000);

	/* zero scan and fअगरo control */
	outb(0x0, dev->iobase + DMM32AT_FIFO_CTRL_REG);

	/* zero पूर्णांकerrupt and घड़ी control */
	outb(0x0, dev->iobase + DMM32AT_INTCLK_REG);

	/* ग_लिखो a test channel range, the high 3 bits should drop */
	outb(0x80, dev->iobase + DMM32AT_AI_LO_CHAN_REG);
	outb(0xff, dev->iobase + DMM32AT_AI_HI_CHAN_REG);

	/* set the range at 10v unipolar */
	outb(DMM32AT_RANGE_U10, dev->iobase + DMM32AT_AI_CFG_REG);

	/* should take 10 us to settle, here's a hundred */
	usleep_range(100, 200);

	/* पढ़ो back the values */
	ailo = inb(dev->iobase + DMM32AT_AI_LO_CHAN_REG);
	aihi = inb(dev->iobase + DMM32AT_AI_HI_CHAN_REG);
	fअगरostat = inb(dev->iobase + DMM32AT_FIFO_STATUS_REG);
	aistat = inb(dev->iobase + DMM32AT_AI_STATUS_REG);
	पूर्णांकstat = inb(dev->iobase + DMM32AT_INTCLK_REG);
	airback = inb(dev->iobase + DMM32AT_AI_READBACK_REG);

	/*
	 * NOTE: The (DMM32AT_AI_STATUS_SD1 | DMM32AT_AI_STATUS_SD0)
	 * test makes this driver only work अगर the board is configured
	 * with all A/D channels set क्रम single-ended operation.
	 */
	अगर (ailo != 0x00 || aihi != 0x1f ||
	    fअगरostat != DMM32AT_FIFO_STATUS_EF ||
	    aistat != (DMM32AT_AI_STATUS_SD1 | DMM32AT_AI_STATUS_SD0) ||
	    पूर्णांकstat != 0x00 || airback != 0x0c)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक dmm32at_attach(काष्ठा comedi_device *dev,
			  काष्ठा comedi_devconfig *it)
अणु
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], 0x10);
	अगर (ret)
		वापस ret;

	ret = dmm32at_reset(dev);
	अगर (ret) अणु
		dev_err(dev->class_dev, "board detection failed\n");
		वापस ret;
	पूर्ण

	अगर (it->options[1]) अणु
		ret = request_irq(it->options[1], dmm32at_isr, 0,
				  dev->board_name, dev);
		अगर (ret == 0)
			dev->irq = it->options[1];
	पूर्ण

	ret = comedi_alloc_subdevices(dev, 3);
	अगर (ret)
		वापस ret;

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_GROUND | SDF_DIFF;
	s->n_chan	= 32;
	s->maxdata	= 0xffff;
	s->range_table	= &dmm32at_airanges;
	s->insn_पढ़ो	= dmm32at_ai_insn_पढ़ो;
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->len_chanlist	= s->n_chan;
		s->करो_cmd	= dmm32at_ai_cmd;
		s->करो_cmdtest	= dmm32at_ai_cmdtest;
		s->cancel	= dmm32at_ai_cancel;
	पूर्ण

	/* Analog Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 4;
	s->maxdata	= 0x0fff;
	s->range_table	= &dmm32at_aoranges;
	s->insn_ग_लिखो	= dmm32at_ao_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	/* Digital I/O subdevice */
	s = &dev->subdevices[2];
	वापस subdev_8255_init(dev, s, dmm32at_8255_io, DMM32AT_8255_IOBASE);
पूर्ण

अटल काष्ठा comedi_driver dmm32at_driver = अणु
	.driver_name	= "dmm32at",
	.module		= THIS_MODULE,
	.attach		= dmm32at_attach,
	.detach		= comedi_legacy_detach,
पूर्ण;
module_comedi_driver(dmm32at_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi: Diamond Systems Diamond-MM-32-AT");
MODULE_LICENSE("GPL");
