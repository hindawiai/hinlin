<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/ni_labpc_common.c
 *
 * Common support code क्रम "ni_labpc", "ni_labpc_pci" and "ni_labpc_cs".
 *
 * Copyright (C) 2001-2003 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>

#समावेश "../comedidev.h"

#समावेश "comedi_8254.h"
#समावेश "8255.h"
#समावेश "ni_labpc.h"
#समावेश "ni_labpc_regs.h"
#समावेश "ni_labpc_isadma.h"

क्रमागत scan_mode अणु
	MODE_SINGLE_CHAN,
	MODE_SINGLE_CHAN_INTERVAL,
	MODE_MULT_CHAN_UP,
	MODE_MULT_CHAN_DOWN,
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_labpc_plus_ai = अणु
	16, अणु
		BIP_RANGE(5),
		BIP_RANGE(4),
		BIP_RANGE(2.5),
		BIP_RANGE(1),
		BIP_RANGE(0.5),
		BIP_RANGE(0.25),
		BIP_RANGE(0.1),
		BIP_RANGE(0.05),
		UNI_RANGE(10),
		UNI_RANGE(8),
		UNI_RANGE(5),
		UNI_RANGE(2),
		UNI_RANGE(1),
		UNI_RANGE(0.5),
		UNI_RANGE(0.2),
		UNI_RANGE(0.1)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_labpc_1200_ai = अणु
	14, अणु
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1),
		BIP_RANGE(0.5),
		BIP_RANGE(0.25),
		BIP_RANGE(0.1),
		BIP_RANGE(0.05),
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2),
		UNI_RANGE(1),
		UNI_RANGE(0.5),
		UNI_RANGE(0.2),
		UNI_RANGE(0.1)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_labpc_ao = अणु
	2, अणु
		BIP_RANGE(5),
		UNI_RANGE(10)
	पूर्ण
पूर्ण;

/*
 * functions that करो inb/outb and पढ़ोb/ग_लिखोb so we can use
 * function poपूर्णांकers to decide which to use
 */
अटल अचिन्हित पूर्णांक labpc_inb(काष्ठा comedi_device *dev, अचिन्हित दीर्घ reg)
अणु
	वापस inb(dev->iobase + reg);
पूर्ण

अटल व्योम labpc_outb(काष्ठा comedi_device *dev,
		       अचिन्हित पूर्णांक byte, अचिन्हित दीर्घ reg)
अणु
	outb(byte, dev->iobase + reg);
पूर्ण

अटल अचिन्हित पूर्णांक labpc_पढ़ोb(काष्ठा comedi_device *dev, अचिन्हित दीर्घ reg)
अणु
	वापस पढ़ोb(dev->mmio + reg);
पूर्ण

अटल व्योम labpc_ग_लिखोb(काष्ठा comedi_device *dev,
			 अचिन्हित पूर्णांक byte, अचिन्हित दीर्घ reg)
अणु
	ग_लिखोb(byte, dev->mmio + reg);
पूर्ण

अटल पूर्णांक labpc_cancel(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा labpc_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->spinlock, flags);
	devpriv->cmd2 &= ~(CMD2_SWTRIG | CMD2_HWTRIG | CMD2_PRETRIG);
	devpriv->ग_लिखो_byte(dev, devpriv->cmd2, CMD2_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	devpriv->cmd3 = 0;
	devpriv->ग_लिखो_byte(dev, devpriv->cmd3, CMD3_REG);

	वापस 0;
पूर्ण

अटल व्योम labpc_ai_set_chan_and_gain(काष्ठा comedi_device *dev,
				       क्रमागत scan_mode mode,
				       अचिन्हित पूर्णांक chan,
				       अचिन्हित पूर्णांक range,
				       अचिन्हित पूर्णांक aref)
अणु
	स्थिर काष्ठा labpc_boardinfo *board = dev->board_ptr;
	काष्ठा labpc_निजी *devpriv = dev->निजी;

	अगर (board->is_labpc1200) अणु
		/*
		 * The LabPC-1200 boards करो not have a gain
		 * of '0x10'. Skip the range values that would
		 * result in this gain.
		 */
		range += (range > 0) + (range > 7);
	पूर्ण

	/* munge channel bits क्रम dअगरferential/scan disabled mode */
	अगर ((mode == MODE_SINGLE_CHAN || mode == MODE_SINGLE_CHAN_INTERVAL) &&
	    aref == AREF_DIFF)
		chan *= 2;
	devpriv->cmd1 = CMD1_MA(chan);
	devpriv->cmd1 |= CMD1_GAIN(range);

	devpriv->ग_लिखो_byte(dev, devpriv->cmd1, CMD1_REG);
पूर्ण

अटल व्योम labpc_setup_cmd6_reg(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 क्रमागत scan_mode mode,
				 क्रमागत transfer_type xfer,
				 अचिन्हित पूर्णांक range,
				 अचिन्हित पूर्णांक aref,
				 bool ena_पूर्णांकr)
अणु
	स्थिर काष्ठा labpc_boardinfo *board = dev->board_ptr;
	काष्ठा labpc_निजी *devpriv = dev->निजी;

	अगर (!board->is_labpc1200)
		वापस;

	/* reference inमाला_दो to ground or common? */
	अगर (aref != AREF_GROUND)
		devpriv->cmd6 |= CMD6_NRSE;
	अन्यथा
		devpriv->cmd6 &= ~CMD6_NRSE;

	/* bipolar or unipolar range? */
	अगर (comedi_range_is_unipolar(s, range))
		devpriv->cmd6 |= CMD6_ADCUNI;
	अन्यथा
		devpriv->cmd6 &= ~CMD6_ADCUNI;

	/*  पूर्णांकerrupt on fअगरo half full? */
	अगर (xfer == fअगरo_half_full_transfer)
		devpriv->cmd6 |= CMD6_HFINTEN;
	अन्यथा
		devpriv->cmd6 &= ~CMD6_HFINTEN;

	/* enable पूर्णांकerrupt on counter a1 terminal count? */
	अगर (ena_पूर्णांकr)
		devpriv->cmd6 |= CMD6_DQINTEN;
	अन्यथा
		devpriv->cmd6 &= ~CMD6_DQINTEN;

	/* are we scanning up or करोwn through channels? */
	अगर (mode == MODE_MULT_CHAN_UP)
		devpriv->cmd6 |= CMD6_SCANUP;
	अन्यथा
		devpriv->cmd6 &= ~CMD6_SCANUP;

	devpriv->ग_लिखो_byte(dev, devpriv->cmd6, CMD6_REG);
पूर्ण

अटल अचिन्हित पूर्णांक labpc_पढ़ो_adc_fअगरo(काष्ठा comedi_device *dev)
अणु
	काष्ठा labpc_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक lsb = devpriv->पढ़ो_byte(dev, ADC_FIFO_REG);
	अचिन्हित पूर्णांक msb = devpriv->पढ़ो_byte(dev, ADC_FIFO_REG);

	वापस (msb << 8) | lsb;
पूर्ण

अटल व्योम labpc_clear_adc_fअगरo(काष्ठा comedi_device *dev)
अणु
	काष्ठा labpc_निजी *devpriv = dev->निजी;

	devpriv->ग_लिखो_byte(dev, 0x1, ADC_FIFO_CLEAR_REG);
	labpc_पढ़ो_adc_fअगरo(dev);
पूर्ण

अटल पूर्णांक labpc_ai_eoc(काष्ठा comedi_device *dev,
			काष्ठा comedi_subdevice *s,
			काष्ठा comedi_insn *insn,
			अचिन्हित दीर्घ context)
अणु
	काष्ठा labpc_निजी *devpriv = dev->निजी;

	devpriv->stat1 = devpriv->पढ़ो_byte(dev, STAT1_REG);
	अगर (devpriv->stat1 & STAT1_DAVAIL)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक labpc_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	काष्ठा labpc_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक aref = CR_AREF(insn->chanspec);
	पूर्णांक ret;
	पूर्णांक i;

	/* disable समयd conversions, पूर्णांकerrupt generation and dma */
	labpc_cancel(dev, s);

	labpc_ai_set_chan_and_gain(dev, MODE_SINGLE_CHAN, chan, range, aref);

	labpc_setup_cmd6_reg(dev, s, MODE_SINGLE_CHAN, fअगरo_not_empty_transfer,
			     range, aref, false);

	/* setup cmd4 रेजिस्टर */
	devpriv->cmd4 = 0;
	devpriv->cmd4 |= CMD4_ECLKRCV;
	/* single-ended/dअगरferential */
	अगर (aref == AREF_DIFF)
		devpriv->cmd4 |= CMD4_SEDIFF;
	devpriv->ग_लिखो_byte(dev, devpriv->cmd4, CMD4_REG);

	/* initialize pacer counter to prevent any problems */
	comedi_8254_set_mode(devpriv->counter, 0, I8254_MODE2 | I8254_BINARY);

	labpc_clear_adc_fअगरo(dev);

	क्रम (i = 0; i < insn->n; i++) अणु
		/* trigger conversion */
		devpriv->ग_लिखो_byte(dev, 0x1, ADC_START_CONVERT_REG);

		ret = comedi_समयout(dev, s, insn, labpc_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		data[i] = labpc_पढ़ो_adc_fअगरo(dev);
	पूर्ण

	वापस insn->n;
पूर्ण

अटल bool labpc_use_continuous_mode(स्थिर काष्ठा comedi_cmd *cmd,
				      क्रमागत scan_mode mode)
अणु
	अगर (mode == MODE_SINGLE_CHAN || cmd->scan_begin_src == TRIG_FOLLOW)
		वापस true;

	वापस false;
पूर्ण

अटल अचिन्हित पूर्णांक labpc_ai_convert_period(स्थिर काष्ठा comedi_cmd *cmd,
					    क्रमागत scan_mode mode)
अणु
	अगर (cmd->convert_src != TRIG_TIMER)
		वापस 0;

	अगर (mode == MODE_SINGLE_CHAN && cmd->scan_begin_src == TRIG_TIMER)
		वापस cmd->scan_begin_arg;

	वापस cmd->convert_arg;
पूर्ण

अटल व्योम labpc_set_ai_convert_period(काष्ठा comedi_cmd *cmd,
					क्रमागत scan_mode mode, अचिन्हित पूर्णांक ns)
अणु
	अगर (cmd->convert_src != TRIG_TIMER)
		वापस;

	अगर (mode == MODE_SINGLE_CHAN &&
	    cmd->scan_begin_src == TRIG_TIMER) अणु
		cmd->scan_begin_arg = ns;
		अगर (cmd->convert_arg > cmd->scan_begin_arg)
			cmd->convert_arg = cmd->scan_begin_arg;
	पूर्ण अन्यथा अणु
		cmd->convert_arg = ns;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक labpc_ai_scan_period(स्थिर काष्ठा comedi_cmd *cmd,
					 क्रमागत scan_mode mode)
अणु
	अगर (cmd->scan_begin_src != TRIG_TIMER)
		वापस 0;

	अगर (mode == MODE_SINGLE_CHAN && cmd->convert_src == TRIG_TIMER)
		वापस 0;

	वापस cmd->scan_begin_arg;
पूर्ण

अटल व्योम labpc_set_ai_scan_period(काष्ठा comedi_cmd *cmd,
				     क्रमागत scan_mode mode, अचिन्हित पूर्णांक ns)
अणु
	अगर (cmd->scan_begin_src != TRIG_TIMER)
		वापस;

	अगर (mode == MODE_SINGLE_CHAN && cmd->convert_src == TRIG_TIMER)
		वापस;

	cmd->scan_begin_arg = ns;
पूर्ण

/* figures out what counter values to use based on command */
अटल व्योम labpc_adc_timing(काष्ठा comedi_device *dev, काष्ठा comedi_cmd *cmd,
			     क्रमागत scan_mode mode)
अणु
	काष्ठा comedi_8254 *pacer = dev->pacer;
	अचिन्हित पूर्णांक convert_period = labpc_ai_convert_period(cmd, mode);
	अचिन्हित पूर्णांक scan_period = labpc_ai_scan_period(cmd, mode);
	अचिन्हित पूर्णांक base_period;

	/*
	 * If both convert and scan triggers are TRIG_TIMER, then they
	 * both rely on counter b0. If only one TRIG_TIMER is used, we
	 * can use the generic cascaded timing functions.
	 */
	अगर (convert_period && scan_period) अणु
		/*
		 * pick the lowest भागisor value we can (क्रम maximum input
		 * घड़ी speed on convert and scan counters)
		 */
		pacer->next_भाग1 = (scan_period - 1) /
				   (pacer->osc_base * I8254_MAX_COUNT) + 1;

		comedi_check_trigger_arg_min(&pacer->next_भाग1, 2);
		comedi_check_trigger_arg_max(&pacer->next_भाग1,
					     I8254_MAX_COUNT);

		base_period = pacer->osc_base * pacer->next_भाग1;

		/*  set a0 क्रम conversion frequency and b1 क्रम scan frequency */
		चयन (cmd->flags & CMDF_ROUND_MASK) अणु
		शेष:
		हाल CMDF_ROUND_NEAREST:
			pacer->next_भाग = DIV_ROUND_CLOSEST(convert_period,
							    base_period);
			pacer->next_भाग2 = DIV_ROUND_CLOSEST(scan_period,
							     base_period);
			अवरोध;
		हाल CMDF_ROUND_UP:
			pacer->next_भाग = DIV_ROUND_UP(convert_period,
						       base_period);
			pacer->next_भाग2 = DIV_ROUND_UP(scan_period,
							base_period);
			अवरोध;
		हाल CMDF_ROUND_DOWN:
			pacer->next_भाग = convert_period / base_period;
			pacer->next_भाग2 = scan_period / base_period;
			अवरोध;
		पूर्ण
		/*  make sure a0 and b1 values are acceptable */
		comedi_check_trigger_arg_min(&pacer->next_भाग, 2);
		comedi_check_trigger_arg_max(&pacer->next_भाग, I8254_MAX_COUNT);
		comedi_check_trigger_arg_min(&pacer->next_भाग2, 2);
		comedi_check_trigger_arg_max(&pacer->next_भाग2,
					     I8254_MAX_COUNT);

		/*  ग_लिखो corrected timings to command */
		labpc_set_ai_convert_period(cmd, mode,
					    base_period * pacer->next_भाग);
		labpc_set_ai_scan_period(cmd, mode,
					 base_period * pacer->next_भाग2);
	पूर्ण अन्यथा अगर (scan_period) अणु
		/*
		 * calculate cascaded counter values
		 * that give desired scan timing
		 * (pacer->next_भाग2 / pacer->next_भाग1)
		 */
		comedi_8254_cascade_ns_to_समयr(pacer, &scan_period,
						cmd->flags);
		labpc_set_ai_scan_period(cmd, mode, scan_period);
	पूर्ण अन्यथा अगर (convert_period) अणु
		/*
		 * calculate cascaded counter values
		 * that give desired conversion timing
		 * (pacer->next_भाग / pacer->next_भाग1)
		 */
		comedi_8254_cascade_ns_to_समयr(pacer, &convert_period,
						cmd->flags);
		/* transfer भाग2 value so correct समयr माला_लो updated */
		pacer->next_भाग = pacer->next_भाग2;
		labpc_set_ai_convert_period(cmd, mode, convert_period);
	पूर्ण
पूर्ण

अटल क्रमागत scan_mode labpc_ai_scan_mode(स्थिर काष्ठा comedi_cmd *cmd)
अणु
	अचिन्हित पूर्णांक chan0;
	अचिन्हित पूर्णांक chan1;

	अगर (cmd->chanlist_len == 1)
		वापस MODE_SINGLE_CHAN;

	/* chanlist may be शून्य during cmdtest */
	अगर (!cmd->chanlist)
		वापस MODE_MULT_CHAN_UP;

	chan0 = CR_CHAN(cmd->chanlist[0]);
	chan1 = CR_CHAN(cmd->chanlist[1]);

	अगर (chan0 < chan1)
		वापस MODE_MULT_CHAN_UP;

	अगर (chan0 > chan1)
		वापस MODE_MULT_CHAN_DOWN;

	वापस MODE_SINGLE_CHAN_INTERVAL;
पूर्ण

अटल पूर्णांक labpc_ai_check_chanlist(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_cmd *cmd)
अणु
	क्रमागत scan_mode mode = labpc_ai_scan_mode(cmd);
	अचिन्हित पूर्णांक chan0 = CR_CHAN(cmd->chanlist[0]);
	अचिन्हित पूर्णांक range0 = CR_RANGE(cmd->chanlist[0]);
	अचिन्हित पूर्णांक aref0 = CR_AREF(cmd->chanlist[0]);
	पूर्णांक i;

	क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);
		अचिन्हित पूर्णांक range = CR_RANGE(cmd->chanlist[i]);
		अचिन्हित पूर्णांक aref = CR_AREF(cmd->chanlist[i]);

		चयन (mode) अणु
		हाल MODE_SINGLE_CHAN:
			अवरोध;
		हाल MODE_SINGLE_CHAN_INTERVAL:
			अगर (chan != chan0) अणु
				dev_dbg(dev->class_dev,
					"channel scanning order specified in chanlist is not supported by hardware\n");
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल MODE_MULT_CHAN_UP:
			अगर (chan != i) अणु
				dev_dbg(dev->class_dev,
					"channel scanning order specified in chanlist is not supported by hardware\n");
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल MODE_MULT_CHAN_DOWN:
			अगर (chan != (cmd->chanlist_len - i - 1)) अणु
				dev_dbg(dev->class_dev,
					"channel scanning order specified in chanlist is not supported by hardware\n");
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (range != range0) अणु
			dev_dbg(dev->class_dev,
				"entries in chanlist must all have the same range\n");
			वापस -EINVAL;
		पूर्ण

		अगर (aref != aref0) अणु
			dev_dbg(dev->class_dev,
				"entries in chanlist must all have the same reference\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक labpc_ai_cmdtest(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s, काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा labpc_boardinfo *board = dev->board_ptr;
	पूर्णांक err = 0;
	पूर्णांक पंचांगp, पंचांगp2;
	अचिन्हित पूर्णांक stop_mask;
	क्रमागत scan_mode mode;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_TIMER | TRIG_FOLLOW | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src,
					TRIG_TIMER | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);

	stop_mask = TRIG_COUNT | TRIG_NONE;
	अगर (board->is_labpc1200)
		stop_mask |= TRIG_EXT;
	err |= comedi_check_trigger_src(&cmd->stop_src, stop_mask);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->convert_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	/* can't have बाह्यal stop and start triggers at once */
	अगर (cmd->start_src == TRIG_EXT && cmd->stop_src == TRIG_EXT)
		err++;

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	चयन (cmd->start_src) अणु
	हाल TRIG_NOW:
		err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
		अवरोध;
	हाल TRIG_EXT:
		/* start_arg value is ignored */
		अवरोध;
	पूर्ण

	अगर (!cmd->chanlist_len)
		err |= -EINVAL;
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
						    board->ai_speed);
	पूर्ण

	/* make sure scan timing is not too fast */
	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		अगर (cmd->convert_src == TRIG_TIMER) अणु
			err |= comedi_check_trigger_arg_min(
					&cmd->scan_begin_arg,
					cmd->convert_arg * cmd->chanlist_len);
		पूर्ण
		err |= comedi_check_trigger_arg_min(
					&cmd->scan_begin_arg,
					board->ai_speed * cmd->chanlist_len);
	पूर्ण

	चयन (cmd->stop_src) अणु
	हाल TRIG_COUNT:
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
		अवरोध;
	हाल TRIG_NONE:
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);
		अवरोध;
		/*
		 * TRIG_EXT करोesn't care since it doesn't
		 * trigger off a numbered channel
		 */
	शेष:
		अवरोध;
	पूर्ण

	अगर (err)
		वापस 3;

	/* step 4: fix up any arguments */

	पंचांगp = cmd->convert_arg;
	पंचांगp2 = cmd->scan_begin_arg;
	mode = labpc_ai_scan_mode(cmd);
	labpc_adc_timing(dev, cmd, mode);
	अगर (पंचांगp != cmd->convert_arg || पंचांगp2 != cmd->scan_begin_arg)
		err++;

	अगर (err)
		वापस 4;

	/* Step 5: check channel list अगर it exists */
	अगर (cmd->chanlist && cmd->chanlist_len > 0)
		err |= labpc_ai_check_chanlist(dev, s, cmd);

	अगर (err)
		वापस 5;

	वापस 0;
पूर्ण

अटल पूर्णांक labpc_ai_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	स्थिर काष्ठा labpc_boardinfo *board = dev->board_ptr;
	काष्ठा labpc_निजी *devpriv = dev->निजी;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	क्रमागत scan_mode mode = labpc_ai_scan_mode(cmd);
	अचिन्हित पूर्णांक chanspec = (mode == MODE_MULT_CHAN_UP) ?
				cmd->chanlist[cmd->chanlist_len - 1] :
				cmd->chanlist[0];
	अचिन्हित पूर्णांक chan = CR_CHAN(chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(chanspec);
	अचिन्हित पूर्णांक aref = CR_AREF(chanspec);
	क्रमागत transfer_type xfer;
	अचिन्हित दीर्घ flags;

	/* make sure board is disabled beक्रमe setting up acquisition */
	labpc_cancel(dev, s);

	/*  initialize software conversion count */
	अगर (cmd->stop_src == TRIG_COUNT)
		devpriv->count = cmd->stop_arg * cmd->chanlist_len;

	/*  setup hardware conversion counter */
	अगर (cmd->stop_src == TRIG_EXT) अणु
		/*
		 * load counter a1 with count of 3
		 * (pc+ manual says this is minimum allowed) using mode 0
		 */
		comedi_8254_load(devpriv->counter, 1,
				 3, I8254_MODE0 | I8254_BINARY);
	पूर्ण अन्यथा	अणु
		/* just put counter a1 in mode 0 to set its output low */
		comedi_8254_set_mode(devpriv->counter, 1,
				     I8254_MODE0 | I8254_BINARY);
	पूर्ण

	/* figure out what method we will use to transfer data */
	अगर (devpriv->dma &&
	    (cmd->flags & (CMDF_WAKE_EOS | CMDF_PRIORITY)) == 0) अणु
		/*
		 * dma unsafe at RT priority,
		 * and too much setup समय क्रम CMDF_WAKE_EOS
		 */
		xfer = isa_dma_transfer;
	पूर्ण अन्यथा अगर (board->is_labpc1200 &&
		   (cmd->flags & CMDF_WAKE_EOS) == 0 &&
		   (cmd->stop_src != TRIG_COUNT || devpriv->count > 256)) अणु
		/*
		 * pc-plus has no fअगरo-half full पूर्णांकerrupt
		 * wake-end-of-scan should पूर्णांकerrupt on fअगरo not empty
		 * make sure we are taking more than just a few poपूर्णांकs
		 */
		xfer = fअगरo_half_full_transfer;
	पूर्ण अन्यथा अणु
		xfer = fअगरo_not_empty_transfer;
	पूर्ण
	devpriv->current_transfer = xfer;

	labpc_ai_set_chan_and_gain(dev, mode, chan, range, aref);

	labpc_setup_cmd6_reg(dev, s, mode, xfer, range, aref,
			     (cmd->stop_src == TRIG_EXT));

	/* manual says to set scan enable bit on second pass */
	अगर (mode == MODE_MULT_CHAN_UP || mode == MODE_MULT_CHAN_DOWN) अणु
		devpriv->cmd1 |= CMD1_SCANEN;
		/*
		 * Need a brief delay beक्रमe enabling scan, or scan
		 * list will get screwed when you चयन between
		 * scan up to scan करोwn mode - dunno why.
		 */
		udelay(1);
		devpriv->ग_लिखो_byte(dev, devpriv->cmd1, CMD1_REG);
	पूर्ण

	devpriv->ग_लिखो_byte(dev, cmd->chanlist_len, INTERVAL_COUNT_REG);
	/*  load count */
	devpriv->ग_लिखो_byte(dev, 0x1, INTERVAL_STROBE_REG);

	अगर (cmd->convert_src == TRIG_TIMER ||
	    cmd->scan_begin_src == TRIG_TIMER) अणु
		काष्ठा comedi_8254 *pacer = dev->pacer;
		काष्ठा comedi_8254 *counter = devpriv->counter;

		comedi_8254_update_भागisors(pacer);

		/* set up pacing */
		comedi_8254_load(pacer, 0, pacer->भागisor1,
				 I8254_MODE3 | I8254_BINARY);

		/* set up conversion pacing */
		comedi_8254_set_mode(counter, 0, I8254_MODE2 | I8254_BINARY);
		अगर (labpc_ai_convert_period(cmd, mode))
			comedi_8254_ग_लिखो(counter, 0, pacer->भागisor);

		/* set up scan pacing */
		अगर (labpc_ai_scan_period(cmd, mode))
			comedi_8254_load(pacer, 1, pacer->भागisor2,
					 I8254_MODE2 | I8254_BINARY);
	पूर्ण

	labpc_clear_adc_fअगरo(dev);

	अगर (xfer == isa_dma_transfer)
		labpc_setup_dma(dev, s);

	/*  enable error पूर्णांकerrupts */
	devpriv->cmd3 |= CMD3_ERRINTEN;
	/*  enable fअगरo not empty पूर्णांकerrupt? */
	अगर (xfer == fअगरo_not_empty_transfer)
		devpriv->cmd3 |= CMD3_FIFOINTEN;
	devpriv->ग_लिखो_byte(dev, devpriv->cmd3, CMD3_REG);

	/*  setup any बाह्यal triggering/pacing (cmd4 रेजिस्टर) */
	devpriv->cmd4 = 0;
	अगर (cmd->convert_src != TRIG_EXT)
		devpriv->cmd4 |= CMD4_ECLKRCV;
	/*
	 * XXX should discard first scan when using पूर्णांकerval scanning
	 * since manual says it is not synced with scan घड़ी.
	 */
	अगर (!labpc_use_continuous_mode(cmd, mode)) अणु
		devpriv->cmd4 |= CMD4_INTSCAN;
		अगर (cmd->scan_begin_src == TRIG_EXT)
			devpriv->cmd4 |= CMD4_EOIRCV;
	पूर्ण
	/*  single-ended/dअगरferential */
	अगर (aref == AREF_DIFF)
		devpriv->cmd4 |= CMD4_SEDIFF;
	devpriv->ग_लिखो_byte(dev, devpriv->cmd4, CMD4_REG);

	/*  startup acquisition */

	spin_lock_irqsave(&dev->spinlock, flags);

	/* use 2 cascaded counters क्रम pacing */
	devpriv->cmd2 |= CMD2_TBSEL;

	devpriv->cmd2 &= ~(CMD2_SWTRIG | CMD2_HWTRIG | CMD2_PRETRIG);
	अगर (cmd->start_src == TRIG_EXT)
		devpriv->cmd2 |= CMD2_HWTRIG;
	अन्यथा
		devpriv->cmd2 |= CMD2_SWTRIG;
	अगर (cmd->stop_src == TRIG_EXT)
		devpriv->cmd2 |= (CMD2_HWTRIG | CMD2_PRETRIG);

	devpriv->ग_लिखो_byte(dev, devpriv->cmd2, CMD2_REG);

	spin_unlock_irqrestore(&dev->spinlock, flags);

	वापस 0;
पूर्ण

/* पढ़ो all available samples from ai fअगरo */
अटल पूर्णांक labpc_drain_fअगरo(काष्ठा comedi_device *dev)
अणु
	काष्ठा labpc_निजी *devpriv = dev->निजी;
	काष्ठा comedi_async *async = dev->पढ़ो_subdev->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित लघु data;
	स्थिर पूर्णांक समयout = 10000;
	अचिन्हित पूर्णांक i;

	devpriv->stat1 = devpriv->पढ़ो_byte(dev, STAT1_REG);

	क्रम (i = 0; (devpriv->stat1 & STAT1_DAVAIL) && i < समयout;
	     i++) अणु
		/*  quit अगर we have all the data we want */
		अगर (cmd->stop_src == TRIG_COUNT) अणु
			अगर (devpriv->count == 0)
				अवरोध;
			devpriv->count--;
		पूर्ण
		data = labpc_पढ़ो_adc_fअगरo(dev);
		comedi_buf_ग_लिखो_samples(dev->पढ़ो_subdev, &data, 1);
		devpriv->stat1 = devpriv->पढ़ो_byte(dev, STAT1_REG);
	पूर्ण
	अगर (i == समयout) अणु
		dev_err(dev->class_dev, "ai timeout, fifo never empties\n");
		async->events |= COMEDI_CB_ERROR;
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Makes sure all data acquired by board is transferred to comedi (used
 * when acquisition is terminated by stop_src == TRIG_EXT).
 */
अटल व्योम labpc_drain_dregs(काष्ठा comedi_device *dev)
अणु
	काष्ठा labpc_निजी *devpriv = dev->निजी;

	अगर (devpriv->current_transfer == isa_dma_transfer)
		labpc_drain_dma(dev);

	labpc_drain_fअगरo(dev);
पूर्ण

/* पूर्णांकerrupt service routine */
अटल irqवापस_t labpc_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	स्थिर काष्ठा labpc_boardinfo *board = dev->board_ptr;
	काष्ठा labpc_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_async *async;
	काष्ठा comedi_cmd *cmd;

	अगर (!dev->attached) अणु
		dev_err(dev->class_dev, "premature interrupt\n");
		वापस IRQ_HANDLED;
	पूर्ण

	async = s->async;
	cmd = &async->cmd;

	/* पढ़ो board status */
	devpriv->stat1 = devpriv->पढ़ो_byte(dev, STAT1_REG);
	अगर (board->is_labpc1200)
		devpriv->stat2 = devpriv->पढ़ो_byte(dev, STAT2_REG);

	अगर ((devpriv->stat1 & (STAT1_GATA0 | STAT1_CNTINT | STAT1_OVERFLOW |
			       STAT1_OVERRUN | STAT1_DAVAIL)) == 0 &&
	    (devpriv->stat2 & STAT2_OUTA1) == 0 &&
	    (devpriv->stat2 & STAT2_FIFONHF)) अणु
		वापस IRQ_NONE;
	पूर्ण

	अगर (devpriv->stat1 & STAT1_OVERRUN) अणु
		/* clear error पूर्णांकerrupt */
		devpriv->ग_लिखो_byte(dev, 0x1, ADC_FIFO_CLEAR_REG);
		async->events |= COMEDI_CB_ERROR;
		comedi_handle_events(dev, s);
		dev_err(dev->class_dev, "overrun\n");
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (devpriv->current_transfer == isa_dma_transfer)
		labpc_handle_dma_status(dev);
	अन्यथा
		labpc_drain_fअगरo(dev);

	अगर (devpriv->stat1 & STAT1_CNTINT) अणु
		dev_err(dev->class_dev, "handled timer interrupt?\n");
		/*  clear it */
		devpriv->ग_लिखो_byte(dev, 0x1, TIMER_CLEAR_REG);
	पूर्ण

	अगर (devpriv->stat1 & STAT1_OVERFLOW) अणु
		/*  clear error पूर्णांकerrupt */
		devpriv->ग_लिखो_byte(dev, 0x1, ADC_FIFO_CLEAR_REG);
		async->events |= COMEDI_CB_ERROR;
		comedi_handle_events(dev, s);
		dev_err(dev->class_dev, "overflow\n");
		वापस IRQ_HANDLED;
	पूर्ण
	/*  handle बाह्यal stop trigger */
	अगर (cmd->stop_src == TRIG_EXT) अणु
		अगर (devpriv->stat2 & STAT2_OUTA1) अणु
			labpc_drain_dregs(dev);
			async->events |= COMEDI_CB_EOA;
		पूर्ण
	पूर्ण

	/* TRIG_COUNT end of acquisition */
	अगर (cmd->stop_src == TRIG_COUNT) अणु
		अगर (devpriv->count == 0)
			async->events |= COMEDI_CB_EOA;
	पूर्ण

	comedi_handle_events(dev, s);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम labpc_ao_ग_लिखो(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s,
			   अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक val)
अणु
	काष्ठा labpc_निजी *devpriv = dev->निजी;

	devpriv->ग_लिखो_byte(dev, val & 0xff, DAC_LSB_REG(chan));
	devpriv->ग_लिखो_byte(dev, (val >> 8) & 0xff, DAC_MSB_REG(chan));

	s->पढ़ोback[chan] = val;
पूर्ण

अटल पूर्णांक labpc_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	स्थिर काष्ठा labpc_boardinfo *board = dev->board_ptr;
	काष्ठा labpc_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक channel;
	अचिन्हित पूर्णांक range;
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;

	channel = CR_CHAN(insn->chanspec);

	/*
	 * Turn off pacing of analog output channel.
	 * NOTE: hardware bug in daqcard-1200 means pacing cannot
	 * be independently enabled/disabled क्रम its the two channels.
	 */
	spin_lock_irqsave(&dev->spinlock, flags);
	devpriv->cmd2 &= ~CMD2_LDAC(channel);
	devpriv->ग_लिखो_byte(dev, devpriv->cmd2, CMD2_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	/* set range */
	अगर (board->is_labpc1200) अणु
		range = CR_RANGE(insn->chanspec);
		अगर (comedi_range_is_unipolar(s, range))
			devpriv->cmd6 |= CMD6_DACUNI(channel);
		अन्यथा
			devpriv->cmd6 &= ~CMD6_DACUNI(channel);
		/*  ग_लिखो to रेजिस्टर */
		devpriv->ग_लिखो_byte(dev, devpriv->cmd6, CMD6_REG);
	पूर्ण
	/* send data */
	क्रम (i = 0; i < insn->n; i++)
		labpc_ao_ग_लिखो(dev, s, channel, data[i]);

	वापस insn->n;
पूर्ण

/* lowlevel ग_लिखो to eeprom/dac */
अटल व्योम labpc_serial_out(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक value,
			     अचिन्हित पूर्णांक value_width)
अणु
	काष्ठा labpc_निजी *devpriv = dev->निजी;
	पूर्णांक i;

	क्रम (i = 1; i <= value_width; i++) अणु
		/*  clear serial घड़ी */
		devpriv->cmd5 &= ~CMD5_SCLK;
		/*  send bits most signअगरicant bit first */
		अगर (value & (1 << (value_width - i)))
			devpriv->cmd5 |= CMD5_SDATA;
		अन्यथा
			devpriv->cmd5 &= ~CMD5_SDATA;
		udelay(1);
		devpriv->ग_लिखो_byte(dev, devpriv->cmd5, CMD5_REG);
		/*  set घड़ी to load bit */
		devpriv->cmd5 |= CMD5_SCLK;
		udelay(1);
		devpriv->ग_लिखो_byte(dev, devpriv->cmd5, CMD5_REG);
	पूर्ण
पूर्ण

/* lowlevel पढ़ो from eeprom */
अटल अचिन्हित पूर्णांक labpc_serial_in(काष्ठा comedi_device *dev)
अणु
	काष्ठा labpc_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक value = 0;
	पूर्णांक i;
	स्थिर पूर्णांक value_width = 8;	/*  number of bits wide values are */

	क्रम (i = 1; i <= value_width; i++) अणु
		/*  set serial घड़ी */
		devpriv->cmd5 |= CMD5_SCLK;
		udelay(1);
		devpriv->ग_लिखो_byte(dev, devpriv->cmd5, CMD5_REG);
		/*  clear घड़ी bit */
		devpriv->cmd5 &= ~CMD5_SCLK;
		udelay(1);
		devpriv->ग_लिखो_byte(dev, devpriv->cmd5, CMD5_REG);
		/*  पढ़ो bits most signअगरicant bit first */
		udelay(1);
		devpriv->stat2 = devpriv->पढ़ो_byte(dev, STAT2_REG);
		अगर (devpriv->stat2 & STAT2_PROMOUT)
			value |= 1 << (value_width - i);
	पूर्ण

	वापस value;
पूर्ण

अटल अचिन्हित पूर्णांक labpc_eeprom_पढ़ो(काष्ठा comedi_device *dev,
				      अचिन्हित पूर्णांक address)
अणु
	काष्ठा labpc_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक value;
	/*  bits to tell eeprom to expect a पढ़ो */
	स्थिर पूर्णांक पढ़ो_inकाष्ठाion = 0x3;
	/*  8 bit ग_लिखो lengths to eeprom */
	स्थिर पूर्णांक ग_लिखो_length = 8;

	/*  enable पढ़ो/ग_लिखो to eeprom */
	devpriv->cmd5 &= ~CMD5_EEPROMCS;
	udelay(1);
	devpriv->ग_लिखो_byte(dev, devpriv->cmd5, CMD5_REG);
	devpriv->cmd5 |= (CMD5_EEPROMCS | CMD5_WRTPRT);
	udelay(1);
	devpriv->ग_लिखो_byte(dev, devpriv->cmd5, CMD5_REG);

	/*  send पढ़ो inकाष्ठाion */
	labpc_serial_out(dev, पढ़ो_inकाष्ठाion, ग_लिखो_length);
	/*  send 8 bit address to पढ़ो from */
	labpc_serial_out(dev, address, ग_लिखो_length);
	/*  पढ़ो result */
	value = labpc_serial_in(dev);

	/*  disable पढ़ो/ग_लिखो to eeprom */
	devpriv->cmd5 &= ~(CMD5_EEPROMCS | CMD5_WRTPRT);
	udelay(1);
	devpriv->ग_लिखो_byte(dev, devpriv->cmd5, CMD5_REG);

	वापस value;
पूर्ण

अटल अचिन्हित पूर्णांक labpc_eeprom_पढ़ो_status(काष्ठा comedi_device *dev)
अणु
	काष्ठा labpc_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक value;
	स्थिर पूर्णांक पढ़ो_status_inकाष्ठाion = 0x5;
	स्थिर पूर्णांक ग_लिखो_length = 8;	/*  8 bit ग_लिखो lengths to eeprom */

	/*  enable पढ़ो/ग_लिखो to eeprom */
	devpriv->cmd5 &= ~CMD5_EEPROMCS;
	udelay(1);
	devpriv->ग_लिखो_byte(dev, devpriv->cmd5, CMD5_REG);
	devpriv->cmd5 |= (CMD5_EEPROMCS | CMD5_WRTPRT);
	udelay(1);
	devpriv->ग_लिखो_byte(dev, devpriv->cmd5, CMD5_REG);

	/*  send पढ़ो status inकाष्ठाion */
	labpc_serial_out(dev, पढ़ो_status_inकाष्ठाion, ग_लिखो_length);
	/*  पढ़ो result */
	value = labpc_serial_in(dev);

	/*  disable पढ़ो/ग_लिखो to eeprom */
	devpriv->cmd5 &= ~(CMD5_EEPROMCS | CMD5_WRTPRT);
	udelay(1);
	devpriv->ग_लिखो_byte(dev, devpriv->cmd5, CMD5_REG);

	वापस value;
पूर्ण

अटल व्योम labpc_eeprom_ग_लिखो(काष्ठा comedi_device *dev,
			       अचिन्हित पूर्णांक address, अचिन्हित पूर्णांक value)
अणु
	काष्ठा labpc_निजी *devpriv = dev->निजी;
	स्थिर पूर्णांक ग_लिखो_enable_inकाष्ठाion = 0x6;
	स्थिर पूर्णांक ग_लिखो_inकाष्ठाion = 0x2;
	स्थिर पूर्णांक ग_लिखो_length = 8;	/*  8 bit ग_लिखो lengths to eeprom */

	/*  enable पढ़ो/ग_लिखो to eeprom */
	devpriv->cmd5 &= ~CMD5_EEPROMCS;
	udelay(1);
	devpriv->ग_लिखो_byte(dev, devpriv->cmd5, CMD5_REG);
	devpriv->cmd5 |= (CMD5_EEPROMCS | CMD5_WRTPRT);
	udelay(1);
	devpriv->ग_लिखो_byte(dev, devpriv->cmd5, CMD5_REG);

	/*  send ग_लिखो_enable inकाष्ठाion */
	labpc_serial_out(dev, ग_लिखो_enable_inकाष्ठाion, ग_लिखो_length);
	devpriv->cmd5 &= ~CMD5_EEPROMCS;
	udelay(1);
	devpriv->ग_लिखो_byte(dev, devpriv->cmd5, CMD5_REG);

	/*  send ग_लिखो inकाष्ठाion */
	devpriv->cmd5 |= CMD5_EEPROMCS;
	udelay(1);
	devpriv->ग_लिखो_byte(dev, devpriv->cmd5, CMD5_REG);
	labpc_serial_out(dev, ग_लिखो_inकाष्ठाion, ग_लिखो_length);
	/*  send 8 bit address to ग_लिखो to */
	labpc_serial_out(dev, address, ग_लिखो_length);
	/*  ग_लिखो value */
	labpc_serial_out(dev, value, ग_लिखो_length);
	devpriv->cmd5 &= ~CMD5_EEPROMCS;
	udelay(1);
	devpriv->ग_लिखो_byte(dev, devpriv->cmd5, CMD5_REG);

	/*  disable पढ़ो/ग_लिखो to eeprom */
	devpriv->cmd5 &= ~(CMD5_EEPROMCS | CMD5_WRTPRT);
	udelay(1);
	devpriv->ग_लिखो_byte(dev, devpriv->cmd5, CMD5_REG);
पूर्ण

/* ग_लिखोs to 8 bit calibration dacs */
अटल व्योम ग_लिखो_caldac(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक channel,
			 अचिन्हित पूर्णांक value)
अणु
	काष्ठा labpc_निजी *devpriv = dev->निजी;

	/*  clear caldac load bit and make sure we करोn't ग_लिखो to eeprom */
	devpriv->cmd5 &= ~(CMD5_CALDACLD | CMD5_EEPROMCS | CMD5_WRTPRT);
	udelay(1);
	devpriv->ग_लिखो_byte(dev, devpriv->cmd5, CMD5_REG);

	/*  ग_लिखो 4 bit channel */
	labpc_serial_out(dev, channel, 4);
	/*  ग_लिखो 8 bit caldac value */
	labpc_serial_out(dev, value, 8);

	/*  set and clear caldac bit to load caldac value */
	devpriv->cmd5 |= CMD5_CALDACLD;
	udelay(1);
	devpriv->ग_लिखो_byte(dev, devpriv->cmd5, CMD5_REG);
	devpriv->cmd5 &= ~CMD5_CALDACLD;
	udelay(1);
	devpriv->ग_लिखो_byte(dev, devpriv->cmd5, CMD5_REG);
पूर्ण

अटल पूर्णांक labpc_calib_insn_ग_लिखो(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);

	/*
	 * Only ग_लिखो the last data value to the caldac. Preceding
	 * data would be overwritten anyway.
	 */
	अगर (insn->n > 0) अणु
		अचिन्हित पूर्णांक val = data[insn->n - 1];

		अगर (s->पढ़ोback[chan] != val) अणु
			ग_लिखो_caldac(dev, chan, val);
			s->पढ़ोback[chan] = val;
		पूर्ण
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक labpc_eeprom_पढ़ोy(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	/* make sure there isn't alपढ़ोy a ग_लिखो in progress */
	status = labpc_eeprom_पढ़ो_status(dev);
	अगर ((status & 0x1) == 0)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक labpc_eeprom_insn_ग_लिखो(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक ret;

	/* only allow ग_लिखोs to user area of eeprom */
	अगर (chan < 16 || chan > 127)
		वापस -EINVAL;

	/*
	 * Only ग_लिखो the last data value to the eeprom. Preceding
	 * data would be overwritten anyway.
	 */
	अगर (insn->n > 0) अणु
		अचिन्हित पूर्णांक val = data[insn->n - 1];

		ret = comedi_समयout(dev, s, insn, labpc_eeprom_पढ़ोy, 0);
		अगर (ret)
			वापस ret;

		labpc_eeprom_ग_लिखो(dev, chan, val);
		s->पढ़ोback[chan] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

पूर्णांक labpc_common_attach(काष्ठा comedi_device *dev,
			अचिन्हित पूर्णांक irq, अचिन्हित दीर्घ isr_flags)
अणु
	स्थिर काष्ठा labpc_boardinfo *board = dev->board_ptr;
	काष्ठा labpc_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;
	पूर्णांक i;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	अगर (dev->mmio) अणु
		devpriv->पढ़ो_byte = labpc_पढ़ोb;
		devpriv->ग_लिखो_byte = labpc_ग_लिखोb;
	पूर्ण अन्यथा अणु
		devpriv->पढ़ो_byte = labpc_inb;
		devpriv->ग_लिखो_byte = labpc_outb;
	पूर्ण

	/* initialize board's command रेजिस्टरs */
	devpriv->ग_लिखो_byte(dev, devpriv->cmd1, CMD1_REG);
	devpriv->ग_लिखो_byte(dev, devpriv->cmd2, CMD2_REG);
	devpriv->ग_लिखो_byte(dev, devpriv->cmd3, CMD3_REG);
	devpriv->ग_लिखो_byte(dev, devpriv->cmd4, CMD4_REG);
	अगर (board->is_labpc1200) अणु
		devpriv->ग_लिखो_byte(dev, devpriv->cmd5, CMD5_REG);
		devpriv->ग_लिखो_byte(dev, devpriv->cmd6, CMD6_REG);
	पूर्ण

	अगर (irq) अणु
		ret = request_irq(irq, labpc_पूर्णांकerrupt, isr_flags,
				  dev->board_name, dev);
		अगर (ret == 0)
			dev->irq = irq;
	पूर्ण

	अगर (dev->mmio) अणु
		dev->pacer = comedi_8254_mm_init(dev->mmio + COUNTER_B_BASE_REG,
						 I8254_OSC_BASE_2MHZ,
						 I8254_IO8, 0);
		devpriv->counter = comedi_8254_mm_init(dev->mmio +
						       COUNTER_A_BASE_REG,
						       I8254_OSC_BASE_2MHZ,
						       I8254_IO8, 0);
	पूर्ण अन्यथा अणु
		dev->pacer = comedi_8254_init(dev->iobase + COUNTER_B_BASE_REG,
					      I8254_OSC_BASE_2MHZ,
					      I8254_IO8, 0);
		devpriv->counter = comedi_8254_init(dev->iobase +
						    COUNTER_A_BASE_REG,
						    I8254_OSC_BASE_2MHZ,
						    I8254_IO8, 0);
	पूर्ण
	अगर (!dev->pacer || !devpriv->counter)
		वापस -ENOMEM;

	ret = comedi_alloc_subdevices(dev, 5);
	अगर (ret)
		वापस ret;

	/* analog input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_GROUND | SDF_COMMON | SDF_DIFF;
	s->n_chan	= 8;
	s->len_chanlist	= 8;
	s->maxdata	= 0x0fff;
	s->range_table	= board->is_labpc1200 ?
			  &range_labpc_1200_ai : &range_labpc_plus_ai;
	s->insn_पढ़ो	= labpc_ai_insn_पढ़ो;
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->करो_cmd	= labpc_ai_cmd;
		s->करो_cmdtest	= labpc_ai_cmdtest;
		s->cancel	= labpc_cancel;
	पूर्ण

	/* analog output */
	s = &dev->subdevices[1];
	अगर (board->has_ao) अणु
		s->type		= COMEDI_SUBD_AO;
		s->subdev_flags	= SDF_READABLE | SDF_WRITABLE | SDF_GROUND;
		s->n_chan	= 2;
		s->maxdata	= 0x0fff;
		s->range_table	= &range_labpc_ao;
		s->insn_ग_लिखो	= labpc_ao_insn_ग_लिखो;

		ret = comedi_alloc_subdev_पढ़ोback(s);
		अगर (ret)
			वापस ret;

		/* initialize analog outमाला_दो to a known value */
		क्रम (i = 0; i < s->n_chan; i++)
			labpc_ao_ग_लिखो(dev, s, i, s->maxdata / 2);
	पूर्ण अन्यथा अणु
		s->type		= COMEDI_SUBD_UNUSED;
	पूर्ण

	/* 8255 dio */
	s = &dev->subdevices[2];
	अगर (dev->mmio)
		ret = subdev_8255_mm_init(dev, s, शून्य, DIO_BASE_REG);
	अन्यथा
		ret = subdev_8255_init(dev, s, शून्य, DIO_BASE_REG);
	अगर (ret)
		वापस ret;

	/*  calibration subdevices क्रम boards that have one */
	s = &dev->subdevices[3];
	अगर (board->is_labpc1200) अणु
		s->type		= COMEDI_SUBD_CALIB;
		s->subdev_flags	= SDF_READABLE | SDF_WRITABLE | SDF_INTERNAL;
		s->n_chan	= 16;
		s->maxdata	= 0xff;
		s->insn_ग_लिखो	= labpc_calib_insn_ग_लिखो;

		ret = comedi_alloc_subdev_पढ़ोback(s);
		अगर (ret)
			वापस ret;

		क्रम (i = 0; i < s->n_chan; i++) अणु
			ग_लिखो_caldac(dev, i, s->maxdata / 2);
			s->पढ़ोback[i] = s->maxdata / 2;
		पूर्ण
	पूर्ण अन्यथा अणु
		s->type		= COMEDI_SUBD_UNUSED;
	पूर्ण

	/* EEPROM (256 bytes) */
	s = &dev->subdevices[4];
	अगर (board->is_labpc1200) अणु
		s->type		= COMEDI_SUBD_MEMORY;
		s->subdev_flags	= SDF_READABLE | SDF_WRITABLE | SDF_INTERNAL;
		s->n_chan	= 256;
		s->maxdata	= 0xff;
		s->insn_ग_लिखो	= labpc_eeprom_insn_ग_लिखो;

		ret = comedi_alloc_subdev_पढ़ोback(s);
		अगर (ret)
			वापस ret;

		क्रम (i = 0; i < s->n_chan; i++)
			s->पढ़ोback[i] = labpc_eeprom_पढ़ो(dev, i);
	पूर्ण अन्यथा अणु
		s->type		= COMEDI_SUBD_UNUSED;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(labpc_common_attach);

व्योम labpc_common_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा labpc_निजी *devpriv = dev->निजी;

	अगर (devpriv)
		kमुक्त(devpriv->counter);
पूर्ण
EXPORT_SYMBOL_GPL(labpc_common_detach);

अटल पूर्णांक __init labpc_common_init(व्योम)
अणु
	वापस 0;
पूर्ण
module_init(labpc_common_init);

अटल व्योम __निकास labpc_common_निकास(व्योम)
अणु
पूर्ण
module_निकास(labpc_common_निकास);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi helper for ni_labpc, ni_labpc_pci, ni_labpc_cs");
MODULE_LICENSE("GPL");
