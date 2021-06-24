<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * das6402.c
 * Comedi driver क्रम DAS6402 compatible boards
 * Copyright(c) 2014 H Hartley Sweeten <hsweeten@visionengravers.com>
 *
 * Reग_लिखो of an experimental driver by:
 * Copyright (C) 1999 Oystein Svendsen <svendsen@pvv.org>
 */

/*
 * Driver: das6402
 * Description: Keithley Metrabyte DAS6402 (& compatibles)
 * Devices: [Keithley Metrabyte] DAS6402-12 (das6402-12),
 *   DAS6402-16 (das6402-16)
 * Author: H Hartley Sweeten <hsweeten@visionengravers.com>
 * Updated: Fri, 14 Mar 2014 10:18:43 -0700
 * Status: unknown
 *
 * Configuration Options:
 *   [0] - I/O base address
 *   [1] - IRQ (optional, needed क्रम async command support)
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedidev.h"

#समावेश "comedi_8254.h"

/*
 * Register I/O map
 */
#घोषणा DAS6402_AI_DATA_REG		0x00
#घोषणा DAS6402_AI_MUX_REG		0x02
#घोषणा DAS6402_AI_MUX_LO(x)		(((x) & 0x3f) << 0)
#घोषणा DAS6402_AI_MUX_HI(x)		(((x) & 0x3f) << 8)
#घोषणा DAS6402_DI_DO_REG		0x03
#घोषणा DAS6402_AO_DATA_REG(x)		(0x04 + ((x) * 2))
#घोषणा DAS6402_AO_LSB_REG(x)		(0x04 + ((x) * 2))
#घोषणा DAS6402_AO_MSB_REG(x)		(0x05 + ((x) * 2))
#घोषणा DAS6402_STATUS_REG		0x08
#घोषणा DAS6402_STATUS_FFNE		BIT(0)
#घोषणा DAS6402_STATUS_FHALF		BIT(1)
#घोषणा DAS6402_STATUS_FFULL		BIT(2)
#घोषणा DAS6402_STATUS_XINT		BIT(3)
#घोषणा DAS6402_STATUS_INT		BIT(4)
#घोषणा DAS6402_STATUS_XTRIG		BIT(5)
#घोषणा DAS6402_STATUS_INDGT		BIT(6)
#घोषणा DAS6402_STATUS_10MHZ		BIT(7)
#घोषणा DAS6402_STATUS_W_CLRINT		BIT(0)
#घोषणा DAS6402_STATUS_W_CLRXTR		BIT(1)
#घोषणा DAS6402_STATUS_W_CLRXIN		BIT(2)
#घोषणा DAS6402_STATUS_W_EXTEND		BIT(4)
#घोषणा DAS6402_STATUS_W_ARMED		BIT(5)
#घोषणा DAS6402_STATUS_W_POSTMODE	BIT(6)
#घोषणा DAS6402_STATUS_W_10MHZ		BIT(7)
#घोषणा DAS6402_CTRL_REG		0x09
#घोषणा DAS6402_CTRL_TRIG(x)		((x) << 0)
#घोषणा DAS6402_CTRL_SOFT_TRIG		DAS6402_CTRL_TRIG(0)
#घोषणा DAS6402_CTRL_EXT_FALL_TRIG	DAS6402_CTRL_TRIG(1)
#घोषणा DAS6402_CTRL_EXT_RISE_TRIG	DAS6402_CTRL_TRIG(2)
#घोषणा DAS6402_CTRL_PACER_TRIG		DAS6402_CTRL_TRIG(3)
#घोषणा DAS6402_CTRL_BURSTEN		BIT(2)
#घोषणा DAS6402_CTRL_XINTE		BIT(3)
#घोषणा DAS6402_CTRL_IRQ(x)		((x) << 4)
#घोषणा DAS6402_CTRL_INTE		BIT(7)
#घोषणा DAS6402_TRIG_REG		0x0a
#घोषणा DAS6402_TRIG_TGEN		BIT(0)
#घोषणा DAS6402_TRIG_TGSEL		BIT(1)
#घोषणा DAS6402_TRIG_TGPOL		BIT(2)
#घोषणा DAS6402_TRIG_PRETRIG		BIT(3)
#घोषणा DAS6402_AO_RANGE(_chan, _range)	((_range) << ((_chan) ? 6 : 4))
#घोषणा DAS6402_AO_RANGE_MASK(_chan)	(3 << ((_chan) ? 6 : 4))
#घोषणा DAS6402_MODE_REG		0x0b
#घोषणा DAS6402_MODE_RANGE(x)		((x) << 2)
#घोषणा DAS6402_MODE_POLLED		DAS6402_MODE_RANGE(0)
#घोषणा DAS6402_MODE_FIFONEPTY		DAS6402_MODE_RANGE(1)
#घोषणा DAS6402_MODE_FIFOHFULL		DAS6402_MODE_RANGE(2)
#घोषणा DAS6402_MODE_EOB		DAS6402_MODE_RANGE(3)
#घोषणा DAS6402_MODE_ENHANCED		BIT(4)
#घोषणा DAS6402_MODE_SE			BIT(5)
#घोषणा DAS6402_MODE_UNI		BIT(6)
#घोषणा DAS6402_MODE_DMA(x)		((x) << 7)
#घोषणा DAS6402_MODE_DMA1		DAS6402_MODE_DMA(0)
#घोषणा DAS6402_MODE_DMA3		DAS6402_MODE_DMA(1)
#घोषणा DAS6402_TIMER_BASE		0x0c

अटल स्थिर काष्ठा comedi_lrange das6402_ai_ranges = अणु
	8, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2.5),
		UNI_RANGE(1.25)
	पूर्ण
पूर्ण;

/*
 * Analog output ranges are programmable on the DAS6402/12.
 * For the DAS6402/16 the range bits have no function, the
 * DAC ranges are selected by चयनes on the board.
 */
अटल स्थिर काष्ठा comedi_lrange das6402_ao_ranges = अणु
	4, अणु
		BIP_RANGE(5),
		BIP_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(10)
	पूर्ण
पूर्ण;

काष्ठा das6402_boardinfo अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक maxdata;
पूर्ण;

अटल काष्ठा das6402_boardinfo das6402_boards[] = अणु
	अणु
		.name		= "das6402-12",
		.maxdata	= 0x0fff,
	पूर्ण, अणु
		.name		= "das6402-16",
		.maxdata	= 0xffff,
	पूर्ण,
पूर्ण;

काष्ठा das6402_निजी अणु
	अचिन्हित पूर्णांक irq;
	अचिन्हित पूर्णांक ao_range;
पूर्ण;

अटल व्योम das6402_set_mode(काष्ठा comedi_device *dev,
			     अचिन्हित पूर्णांक mode)
अणु
	outb(DAS6402_MODE_ENHANCED | mode, dev->iobase + DAS6402_MODE_REG);
पूर्ण

अटल व्योम das6402_set_extended(काष्ठा comedi_device *dev,
				 अचिन्हित पूर्णांक val)
अणु
	outb(DAS6402_STATUS_W_EXTEND, dev->iobase + DAS6402_STATUS_REG);
	outb(DAS6402_STATUS_W_EXTEND | val, dev->iobase + DAS6402_STATUS_REG);
	outb(val, dev->iobase + DAS6402_STATUS_REG);
पूर्ण

अटल व्योम das6402_clear_all_पूर्णांकerrupts(काष्ठा comedi_device *dev)
अणु
	outb(DAS6402_STATUS_W_CLRINT |
	     DAS6402_STATUS_W_CLRXTR |
	     DAS6402_STATUS_W_CLRXIN, dev->iobase + DAS6402_STATUS_REG);
पूर्ण

अटल व्योम das6402_ai_clear_eoc(काष्ठा comedi_device *dev)
अणु
	outb(DAS6402_STATUS_W_CLRINT, dev->iobase + DAS6402_STATUS_REG);
पूर्ण

अटल अचिन्हित पूर्णांक das6402_ai_पढ़ो_sample(काष्ठा comedi_device *dev,
					   काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित पूर्णांक val;

	val = inw(dev->iobase + DAS6402_AI_DATA_REG);
	अगर (s->maxdata == 0x0fff)
		val >>= 4;
	वापस val;
पूर्ण

अटल irqवापस_t das6402_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित पूर्णांक status;

	status = inb(dev->iobase + DAS6402_STATUS_REG);
	अगर ((status & DAS6402_STATUS_INT) == 0)
		वापस IRQ_NONE;

	अगर (status & DAS6402_STATUS_FFULL) अणु
		async->events |= COMEDI_CB_OVERFLOW;
	पूर्ण अन्यथा अगर (status & DAS6402_STATUS_FFNE) अणु
		अचिन्हित लघु val;

		val = das6402_ai_पढ़ो_sample(dev, s);
		comedi_buf_ग_लिखो_samples(s, &val, 1);

		अगर (cmd->stop_src == TRIG_COUNT &&
		    async->scans_करोne >= cmd->stop_arg)
			async->events |= COMEDI_CB_EOA;
	पूर्ण

	das6402_clear_all_पूर्णांकerrupts(dev);

	comedi_handle_events(dev, s);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम das6402_ai_set_mode(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				अचिन्हित पूर्णांक chanspec,
				अचिन्हित पूर्णांक mode)
अणु
	अचिन्हित पूर्णांक range = CR_RANGE(chanspec);
	अचिन्हित पूर्णांक aref = CR_AREF(chanspec);

	mode |= DAS6402_MODE_RANGE(range);
	अगर (aref == AREF_GROUND)
		mode |= DAS6402_MODE_SE;
	अगर (comedi_range_is_unipolar(s, range))
		mode |= DAS6402_MODE_UNI;

	das6402_set_mode(dev, mode);
पूर्ण

अटल पूर्णांक das6402_ai_cmd(काष्ठा comedi_device *dev,
			  काष्ठा comedi_subdevice *s)
अणु
	काष्ठा das6402_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक chan_lo = CR_CHAN(cmd->chanlist[0]);
	अचिन्हित पूर्णांक chan_hi = CR_CHAN(cmd->chanlist[cmd->chanlist_len - 1]);

	das6402_ai_set_mode(dev, s, cmd->chanlist[0], DAS6402_MODE_FIFONEPTY);

	/* load the mux क्रम chanlist conversion */
	outw(DAS6402_AI_MUX_HI(chan_hi) | DAS6402_AI_MUX_LO(chan_lo),
	     dev->iobase + DAS6402_AI_MUX_REG);

	comedi_8254_update_भागisors(dev->pacer);
	comedi_8254_pacer_enable(dev->pacer, 1, 2, true);

	/* enable पूर्णांकerrupt and pacer trigger */
	outb(DAS6402_CTRL_INTE |
	     DAS6402_CTRL_IRQ(devpriv->irq) |
	     DAS6402_CTRL_PACER_TRIG, dev->iobase + DAS6402_CTRL_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक das6402_ai_check_chanlist(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     काष्ठा comedi_cmd *cmd)
अणु
	अचिन्हित पूर्णांक chan0 = CR_CHAN(cmd->chanlist[0]);
	अचिन्हित पूर्णांक range0 = CR_RANGE(cmd->chanlist[0]);
	अचिन्हित पूर्णांक aref0 = CR_AREF(cmd->chanlist[0]);
	पूर्णांक i;

	क्रम (i = 1; i < cmd->chanlist_len; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);
		अचिन्हित पूर्णांक range = CR_RANGE(cmd->chanlist[i]);
		अचिन्हित पूर्णांक aref = CR_AREF(cmd->chanlist[i]);

		अगर (chan != chan0 + i) अणु
			dev_dbg(dev->class_dev,
				"chanlist must be consecutive\n");
			वापस -EINVAL;
		पूर्ण

		अगर (range != range0) अणु
			dev_dbg(dev->class_dev,
				"chanlist must have the same range\n");
			वापस -EINVAL;
		पूर्ण

		अगर (aref != aref0) अणु
			dev_dbg(dev->class_dev,
				"chanlist must have the same reference\n");
			वापस -EINVAL;
		पूर्ण

		अगर (aref0 == AREF_DIFF && chan > (s->n_chan / 2)) अणु
			dev_dbg(dev->class_dev,
				"chanlist differential channel too large\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक das6402_ai_cmdtest(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_cmd *cmd)
अणु
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
	err |= comedi_check_trigger_arg_min(&cmd->convert_arg, 10000);
	err |= comedi_check_trigger_arg_min(&cmd->chanlist_len, 1);
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
	comedi_8254_cascade_ns_to_समयr(dev->pacer, &arg, cmd->flags);
	err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg);

	अगर (err)
		वापस 4;

	/* Step 5: check channel list अगर it exists */
	अगर (cmd->chanlist && cmd->chanlist_len > 0)
		err |= das6402_ai_check_chanlist(dev, s, cmd);

	अगर (err)
		वापस 5;

	वापस 0;
पूर्ण

अटल पूर्णांक das6402_ai_cancel(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s)
अणु
	outb(DAS6402_CTRL_SOFT_TRIG, dev->iobase + DAS6402_CTRL_REG);

	वापस 0;
पूर्ण

अटल व्योम das6402_ai_soft_trig(काष्ठा comedi_device *dev)
अणु
	outw(0, dev->iobase + DAS6402_AI_DATA_REG);
पूर्ण

अटल पूर्णांक das6402_ai_eoc(काष्ठा comedi_device *dev,
			  काष्ठा comedi_subdevice *s,
			  काष्ठा comedi_insn *insn,
			  अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inb(dev->iobase + DAS6402_STATUS_REG);
	अगर (status & DAS6402_STATUS_FFNE)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक das6402_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक aref = CR_AREF(insn->chanspec);
	पूर्णांक ret;
	पूर्णांक i;

	अगर (aref == AREF_DIFF && chan > (s->n_chan / 2))
		वापस -EINVAL;

	/* enable software conversion trigger */
	outb(DAS6402_CTRL_SOFT_TRIG, dev->iobase + DAS6402_CTRL_REG);

	das6402_ai_set_mode(dev, s, insn->chanspec, DAS6402_MODE_POLLED);

	/* load the mux क्रम single channel conversion */
	outw(DAS6402_AI_MUX_HI(chan) | DAS6402_AI_MUX_LO(chan),
	     dev->iobase + DAS6402_AI_MUX_REG);

	क्रम (i = 0; i < insn->n; i++) अणु
		das6402_ai_clear_eoc(dev);
		das6402_ai_soft_trig(dev);

		ret = comedi_समयout(dev, s, insn, das6402_ai_eoc, 0);
		अगर (ret)
			अवरोध;

		data[i] = das6402_ai_पढ़ो_sample(dev, s);
	पूर्ण

	das6402_ai_clear_eoc(dev);

	वापस insn->n;
पूर्ण

अटल पूर्णांक das6402_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	काष्ठा das6402_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	/* set the range क्रम this channel */
	val = devpriv->ao_range;
	val &= ~DAS6402_AO_RANGE_MASK(chan);
	val |= DAS6402_AO_RANGE(chan, range);
	अगर (val != devpriv->ao_range) अणु
		devpriv->ao_range = val;
		outb(val, dev->iobase + DAS6402_TRIG_REG);
	पूर्ण

	/*
	 * The DAS6402/16 has a jumper to select either inभागidual
	 * update (UPDATE) or simultaneous updating (XFER) of both
	 * DAC's. In UPDATE mode, when the MSB is written, that DAC
	 * is updated. In XFER mode, after both DAC's are loaded,
	 * a पढ़ो cycle of any DAC रेजिस्टर will update both DAC's
	 * simultaneously.
	 *
	 * If you have XFER mode enabled a (*insn_पढ़ो) will need
	 * to be perक्रमmed in order to update the DAC's with the
	 * last value written.
	 */
	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];

		s->पढ़ोback[chan] = val;

		अगर (s->maxdata == 0x0fff) अणु
			/*
			 * DAS6402/12 has the two 8-bit DAC रेजिस्टरs, left
			 * justअगरied (the 4 LSB bits are करोn't care). Data
			 * can be written as one word.
			 */
			val <<= 4;
			outw(val, dev->iobase + DAS6402_AO_DATA_REG(chan));
		पूर्ण अन्यथा अणु
			/*
			 * DAS6402/16 uses both 8-bit DAC रेजिस्टरs and needs
			 * to be written LSB then MSB.
			 */
			outb(val & 0xff,
			     dev->iobase + DAS6402_AO_LSB_REG(chan));
			outb((val >> 8) & 0xff,
			     dev->iobase + DAS6402_AO_LSB_REG(chan));
		पूर्ण
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक das6402_ao_insn_पढ़ो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);

	/*
	 * If XFER mode is enabled, पढ़ोing any DAC रेजिस्टर
	 * will update both DAC's simultaneously.
	 */
	inw(dev->iobase + DAS6402_AO_LSB_REG(chan));

	वापस comedi_पढ़ोback_insn_पढ़ो(dev, s, insn, data);
पूर्ण

अटल पूर्णांक das6402_di_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	data[1] = inb(dev->iobase + DAS6402_DI_DO_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक das6402_करो_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		outb(s->state, dev->iobase + DAS6402_DI_DO_REG);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल व्योम das6402_reset(काष्ठा comedi_device *dev)
अणु
	काष्ठा das6402_निजी *devpriv = dev->निजी;

	/* enable "Enhanced" mode */
	outb(DAS6402_MODE_ENHANCED, dev->iobase + DAS6402_MODE_REG);

	/* enable 10MHz pacer घड़ी */
	das6402_set_extended(dev, DAS6402_STATUS_W_10MHZ);

	/* enable software conversion trigger */
	outb(DAS6402_CTRL_SOFT_TRIG, dev->iobase + DAS6402_CTRL_REG);

	/* शेष ADC to single-ended unipolar 10V inमाला_दो */
	das6402_set_mode(dev, DAS6402_MODE_RANGE(0) |
			      DAS6402_MODE_POLLED |
			      DAS6402_MODE_SE |
			      DAS6402_MODE_UNI);

	/* शेष mux क्रम single channel conversion (channel 0) */
	outw(DAS6402_AI_MUX_HI(0) | DAS6402_AI_MUX_LO(0),
	     dev->iobase + DAS6402_AI_MUX_REG);

	/* set both DAC's क्रम unipolar 5V output range */
	devpriv->ao_range = DAS6402_AO_RANGE(0, 2) | DAS6402_AO_RANGE(1, 2);
	outb(devpriv->ao_range, dev->iobase + DAS6402_TRIG_REG);

	/* set both DAC's to 0V */
	outw(0, dev->iobase + DAS6402_AO_DATA_REG(0));
	outw(0, dev->iobase + DAS6402_AO_DATA_REG(0));
	inw(dev->iobase + DAS6402_AO_LSB_REG(0));

	/* set all digital outमाला_दो low */
	outb(0, dev->iobase + DAS6402_DI_DO_REG);

	das6402_clear_all_पूर्णांकerrupts(dev);
पूर्ण

अटल पूर्णांक das6402_attach(काष्ठा comedi_device *dev,
			  काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा das6402_boardinfo *board = dev->board_ptr;
	काष्ठा das6402_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_request_region(dev, it->options[0], 0x10);
	अगर (ret)
		वापस ret;

	das6402_reset(dev);

	/* IRQs 2,3,5,6,7, 10,11,15 are valid क्रम "enhanced" mode */
	अगर ((1 << it->options[1]) & 0x8cec) अणु
		ret = request_irq(it->options[1], das6402_पूर्णांकerrupt, 0,
				  dev->board_name, dev);
		अगर (ret == 0) अणु
			dev->irq = it->options[1];

			चयन (dev->irq) अणु
			हाल 10:
				devpriv->irq = 4;
				अवरोध;
			हाल 11:
				devpriv->irq = 1;
				अवरोध;
			हाल 15:
				devpriv->irq = 6;
				अवरोध;
			शेष:
				devpriv->irq = dev->irq;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	dev->pacer = comedi_8254_init(dev->iobase + DAS6402_TIMER_BASE,
				      I8254_OSC_BASE_10MHZ, I8254_IO8, 0);
	अगर (!dev->pacer)
		वापस -ENOMEM;

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_GROUND | SDF_DIFF;
	s->n_chan	= 64;
	s->maxdata	= board->maxdata;
	s->range_table	= &das6402_ai_ranges;
	s->insn_पढ़ो	= das6402_ai_insn_पढ़ो;
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->len_chanlist	= s->n_chan;
		s->करो_cmdtest	= das6402_ai_cmdtest;
		s->करो_cmd	= das6402_ai_cmd;
		s->cancel	= das6402_ai_cancel;
	पूर्ण

	/* Analog Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 2;
	s->maxdata	= board->maxdata;
	s->range_table	= &das6402_ao_ranges;
	s->insn_ग_लिखो	= das6402_ao_insn_ग_लिखो;
	s->insn_पढ़ो	= das6402_ao_insn_पढ़ो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	/* Digital Input subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= das6402_di_insn_bits;

	/* Digital Input subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= das6402_करो_insn_bits;

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver das6402_driver = अणु
	.driver_name	= "das6402",
	.module		= THIS_MODULE,
	.attach		= das6402_attach,
	.detach		= comedi_legacy_detach,
	.board_name	= &das6402_boards[0].name,
	.num_names	= ARRAY_SIZE(das6402_boards),
	.offset		= माप(काष्ठा das6402_boardinfo),
पूर्ण;
module_comedi_driver(das6402_driver)

MODULE_AUTHOR("H Hartley Sweeten <hsweeten@visionengravers.com>");
MODULE_DESCRIPTION("Comedi driver for DAS6402 compatible boards");
MODULE_LICENSE("GPL");
