<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * dt3000.c
 * Data Translation DT3000 series driver
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1999 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: dt3000
 * Description: Data Translation DT3000 series
 * Devices: [Data Translation] DT3001 (dt3000), DT3001-PGL, DT3002, DT3003,
 *   DT3003-PGL, DT3004, DT3005, DT3004-200
 * Author: ds
 * Updated: Mon, 14 Apr 2008 15:41:24 +0100
 * Status: works
 *
 * Configuration Options: not applicable, uses PCI स्वतः config
 *
 * There is code to support AI commands, but it may not work.
 *
 * AO commands are not supported.
 */

/*
 * The DT3000 series is Data Translation's attempt to make a PCI
 * data acquisition board.  The design of this series is very nice,
 * since each board has an on-board DSP (Texas Instruments TMS320C52).
 * However, a few details are a little annoying.  The boards lack
 * bus-mastering DMA, which eliminates them from serious work.
 * They also are not capable of स्वतःcalibration, which is a common
 * feature in modern hardware.  The शेष firmware is pretty bad,
 * making it nearly impossible to ग_लिखो an RT compatible driver.
 * It would make an पूर्णांकeresting project to ग_लिखो a decent firmware
 * क्रम these boards.
 *
 * Data Translation originally wanted an NDA क्रम the करोcumentation
 * क्रम the 3k series.  However, अगर you ask nicely, they might send
 * you the करोcs without one, also.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedi_pci.h"

/*
 * PCI BAR0 - dual-ported RAM location definitions (dev->mmio)
 */
#घोषणा DPR_DAC_BUFFER		(4 * 0x000)
#घोषणा DPR_ADC_BUFFER		(4 * 0x800)
#घोषणा DPR_COMMAND		(4 * 0xfd3)
#घोषणा DPR_SUBSYS		(4 * 0xfd3)
#घोषणा DPR_SUBSYS_AI		0
#घोषणा DPR_SUBSYS_AO		1
#घोषणा DPR_SUBSYS_DIN		2
#घोषणा DPR_SUBSYS_DOUT		3
#घोषणा DPR_SUBSYS_MEM		4
#घोषणा DPR_SUBSYS_CT		5
#घोषणा DPR_ENCODE		(4 * 0xfd4)
#घोषणा DPR_PARAMS(x)		(4 * (0xfd5 + (x)))
#घोषणा DPR_TICK_REG_LO		(4 * 0xff5)
#घोषणा DPR_TICK_REG_HI		(4 * 0xff6)
#घोषणा DPR_DA_BUF_FRONT	(4 * 0xff7)
#घोषणा DPR_DA_BUF_REAR		(4 * 0xff8)
#घोषणा DPR_AD_BUF_FRONT	(4 * 0xff9)
#घोषणा DPR_AD_BUF_REAR		(4 * 0xffa)
#घोषणा DPR_INT_MASK		(4 * 0xffb)
#घोषणा DPR_INTR_FLAG		(4 * 0xffc)
#घोषणा DPR_INTR_CMDONE		BIT(7)
#घोषणा DPR_INTR_CTDONE		BIT(6)
#घोषणा DPR_INTR_DAHWERR	BIT(5)
#घोषणा DPR_INTR_DASWERR	BIT(4)
#घोषणा DPR_INTR_DAEMPTY	BIT(3)
#घोषणा DPR_INTR_ADHWERR	BIT(2)
#घोषणा DPR_INTR_ADSWERR	BIT(1)
#घोषणा DPR_INTR_ADFULL		BIT(0)
#घोषणा DPR_RESPONSE_MBX	(4 * 0xffe)
#घोषणा DPR_CMD_MBX		(4 * 0xfff)
#घोषणा DPR_CMD_COMPLETION(x)	((x) << 8)
#घोषणा DPR_CMD_NOTPROCESSED	DPR_CMD_COMPLETION(0x00)
#घोषणा DPR_CMD_NOERROR		DPR_CMD_COMPLETION(0x55)
#घोषणा DPR_CMD_ERROR		DPR_CMD_COMPLETION(0xaa)
#घोषणा DPR_CMD_NOTSUPPORTED	DPR_CMD_COMPLETION(0xff)
#घोषणा DPR_CMD_COMPLETION_MASK	DPR_CMD_COMPLETION(0xff)
#घोषणा DPR_CMD(x)		((x) << 0)
#घोषणा DPR_CMD_GETBRDINFO	DPR_CMD(0)
#घोषणा DPR_CMD_CONFIG		DPR_CMD(1)
#घोषणा DPR_CMD_GETCONFIG	DPR_CMD(2)
#घोषणा DPR_CMD_START		DPR_CMD(3)
#घोषणा DPR_CMD_STOP		DPR_CMD(4)
#घोषणा DPR_CMD_READSINGLE	DPR_CMD(5)
#घोषणा DPR_CMD_WRITESINGLE	DPR_CMD(6)
#घोषणा DPR_CMD_CALCCLOCK	DPR_CMD(7)
#घोषणा DPR_CMD_READEVENTS	DPR_CMD(8)
#घोषणा DPR_CMD_WRITECTCTRL	DPR_CMD(16)
#घोषणा DPR_CMD_READCTCTRL	DPR_CMD(17)
#घोषणा DPR_CMD_WRITECT		DPR_CMD(18)
#घोषणा DPR_CMD_READCT		DPR_CMD(19)
#घोषणा DPR_CMD_WRITEDATA	DPR_CMD(32)
#घोषणा DPR_CMD_READDATA	DPR_CMD(33)
#घोषणा DPR_CMD_WRITEIO		DPR_CMD(34)
#घोषणा DPR_CMD_READIO		DPR_CMD(35)
#घोषणा DPR_CMD_WRITECODE	DPR_CMD(36)
#घोषणा DPR_CMD_READCODE	DPR_CMD(37)
#घोषणा DPR_CMD_EXECUTE		DPR_CMD(38)
#घोषणा DPR_CMD_HALT		DPR_CMD(48)
#घोषणा DPR_CMD_MASK		DPR_CMD(0xff)

#घोषणा DPR_PARAM5_AD_TRIG(x)		(((x) & 0x7) << 2)
#घोषणा DPR_PARAM5_AD_TRIG_INT		DPR_PARAM5_AD_TRIG(0)
#घोषणा DPR_PARAM5_AD_TRIG_EXT		DPR_PARAM5_AD_TRIG(1)
#घोषणा DPR_PARAM5_AD_TRIG_INT_RETRIG	DPR_PARAM5_AD_TRIG(2)
#घोषणा DPR_PARAM5_AD_TRIG_EXT_RETRIG	DPR_PARAM5_AD_TRIG(3)
#घोषणा DPR_PARAM5_AD_TRIG_INT_RETRIG2	DPR_PARAM5_AD_TRIG(4)

#घोषणा DPR_PARAM6_AD_DIFF		BIT(0)

#घोषणा DPR_AI_FIFO_DEPTH		2003
#घोषणा DPR_AO_FIFO_DEPTH		2048

#घोषणा DPR_EXTERNAL_CLOCK		1
#घोषणा DPR_RISING_EDGE			2

#घोषणा DPR_TMODE_MASK			0x1c

#घोषणा DPR_CMD_TIMEOUT			100

अटल स्थिर काष्ठा comedi_lrange range_dt3000_ai = अणु
	4, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_dt3000_ai_pgl = अणु
	4, अणु
		BIP_RANGE(10),
		BIP_RANGE(1),
		BIP_RANGE(0.1),
		BIP_RANGE(0.02)
	पूर्ण
पूर्ण;

क्रमागत dt3k_boardid अणु
	BOARD_DT3001,
	BOARD_DT3001_PGL,
	BOARD_DT3002,
	BOARD_DT3003,
	BOARD_DT3003_PGL,
	BOARD_DT3004,
	BOARD_DT3005,
पूर्ण;

काष्ठा dt3k_boardtype अणु
	स्थिर अक्षर *name;
	पूर्णांक adchan;
	पूर्णांक ai_speed;
	स्थिर काष्ठा comedi_lrange *adrange;
	अचिन्हित पूर्णांक ai_is_16bit:1;
	अचिन्हित पूर्णांक has_ao:1;
पूर्ण;

अटल स्थिर काष्ठा dt3k_boardtype dt3k_boardtypes[] = अणु
	[BOARD_DT3001] = अणु
		.name		= "dt3001",
		.adchan		= 16,
		.adrange	= &range_dt3000_ai,
		.ai_speed	= 3000,
		.has_ao		= 1,
	पूर्ण,
	[BOARD_DT3001_PGL] = अणु
		.name		= "dt3001-pgl",
		.adchan		= 16,
		.adrange	= &range_dt3000_ai_pgl,
		.ai_speed	= 3000,
		.has_ao		= 1,
	पूर्ण,
	[BOARD_DT3002] = अणु
		.name		= "dt3002",
		.adchan		= 32,
		.adrange	= &range_dt3000_ai,
		.ai_speed	= 3000,
	पूर्ण,
	[BOARD_DT3003] = अणु
		.name		= "dt3003",
		.adchan		= 64,
		.adrange	= &range_dt3000_ai,
		.ai_speed	= 3000,
		.has_ao		= 1,
	पूर्ण,
	[BOARD_DT3003_PGL] = अणु
		.name		= "dt3003-pgl",
		.adchan		= 64,
		.adrange	= &range_dt3000_ai_pgl,
		.ai_speed	= 3000,
		.has_ao		= 1,
	पूर्ण,
	[BOARD_DT3004] = अणु
		.name		= "dt3004",
		.adchan		= 16,
		.adrange	= &range_dt3000_ai,
		.ai_speed	= 10000,
		.ai_is_16bit	= 1,
		.has_ao		= 1,
	पूर्ण,
	[BOARD_DT3005] = अणु
		.name		= "dt3005",	/* a.k.a. 3004-200 */
		.adchan		= 16,
		.adrange	= &range_dt3000_ai,
		.ai_speed	= 5000,
		.ai_is_16bit	= 1,
		.has_ao		= 1,
	पूर्ण,
पूर्ण;

काष्ठा dt3k_निजी अणु
	अचिन्हित पूर्णांक lock;
	अचिन्हित पूर्णांक ai_front;
	अचिन्हित पूर्णांक ai_rear;
पूर्ण;

अटल व्योम dt3k_send_cmd(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक cmd)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक status = 0;

	ग_लिखोw(cmd, dev->mmio + DPR_CMD_MBX);

	क्रम (i = 0; i < DPR_CMD_TIMEOUT; i++) अणु
		status = पढ़ोw(dev->mmio + DPR_CMD_MBX);
		status &= DPR_CMD_COMPLETION_MASK;
		अगर (status != DPR_CMD_NOTPROCESSED)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (status != DPR_CMD_NOERROR)
		dev_dbg(dev->class_dev, "%s: timeout/error status=0x%04x\n",
			__func__, status);
पूर्ण

अटल अचिन्हित पूर्णांक dt3k_पढ़ोsingle(काष्ठा comedi_device *dev,
				    अचिन्हित पूर्णांक subsys, अचिन्हित पूर्णांक chan,
				    अचिन्हित पूर्णांक gain)
अणु
	ग_लिखोw(subsys, dev->mmio + DPR_SUBSYS);

	ग_लिखोw(chan, dev->mmio + DPR_PARAMS(0));
	ग_लिखोw(gain, dev->mmio + DPR_PARAMS(1));

	dt3k_send_cmd(dev, DPR_CMD_READSINGLE);

	वापस पढ़ोw(dev->mmio + DPR_PARAMS(2));
पूर्ण

अटल व्योम dt3k_ग_लिखोsingle(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक subsys,
			     अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक data)
अणु
	ग_लिखोw(subsys, dev->mmio + DPR_SUBSYS);

	ग_लिखोw(chan, dev->mmio + DPR_PARAMS(0));
	ग_लिखोw(0, dev->mmio + DPR_PARAMS(1));
	ग_लिखोw(data, dev->mmio + DPR_PARAMS(2));

	dt3k_send_cmd(dev, DPR_CMD_WRITESINGLE);
पूर्ण

अटल व्योम dt3k_ai_empty_fअगरo(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s)
अणु
	काष्ठा dt3k_निजी *devpriv = dev->निजी;
	पूर्णांक front;
	पूर्णांक rear;
	पूर्णांक count;
	पूर्णांक i;
	अचिन्हित लघु data;

	front = पढ़ोw(dev->mmio + DPR_AD_BUF_FRONT);
	count = front - devpriv->ai_front;
	अगर (count < 0)
		count += DPR_AI_FIFO_DEPTH;

	rear = devpriv->ai_rear;

	क्रम (i = 0; i < count; i++) अणु
		data = पढ़ोw(dev->mmio + DPR_ADC_BUFFER + rear);
		comedi_buf_ग_लिखो_samples(s, &data, 1);
		rear++;
		अगर (rear >= DPR_AI_FIFO_DEPTH)
			rear = 0;
	पूर्ण

	devpriv->ai_rear = rear;
	ग_लिखोw(rear, dev->mmio + DPR_AD_BUF_REAR);
पूर्ण

अटल पूर्णांक dt3k_ai_cancel(काष्ठा comedi_device *dev,
			  काष्ठा comedi_subdevice *s)
अणु
	ग_लिखोw(DPR_SUBSYS_AI, dev->mmio + DPR_SUBSYS);
	dt3k_send_cmd(dev, DPR_CMD_STOP);

	ग_लिखोw(0, dev->mmio + DPR_INT_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक debug_n_पूर्णांकs;

/* FIXME! Assumes shared पूर्णांकerrupt is क्रम this card. */
/* What's this debug_n_पूर्णांकs stuff? Obviously needs some work... */
अटल irqवापस_t dt3k_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	अचिन्हित पूर्णांक status;

	अगर (!dev->attached)
		वापस IRQ_NONE;

	status = पढ़ोw(dev->mmio + DPR_INTR_FLAG);

	अगर (status & DPR_INTR_ADFULL)
		dt3k_ai_empty_fअगरo(dev, s);

	अगर (status & (DPR_INTR_ADSWERR | DPR_INTR_ADHWERR))
		s->async->events |= COMEDI_CB_ERROR;

	debug_n_पूर्णांकs++;
	अगर (debug_n_पूर्णांकs >= 10)
		s->async->events |= COMEDI_CB_EOA;

	comedi_handle_events(dev, s);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dt3k_ns_to_समयr(अचिन्हित पूर्णांक समयr_base, अचिन्हित पूर्णांक *nanosec,
			    अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक भागider, base, prescale;

	/* This function needs improvement */
	/* Don't know अगर भागider==0 works. */

	क्रम (prescale = 0; prescale < 16; prescale++) अणु
		base = समयr_base * (prescale + 1);
		चयन (flags & CMDF_ROUND_MASK) अणु
		हाल CMDF_ROUND_NEAREST:
		शेष:
			भागider = DIV_ROUND_CLOSEST(*nanosec, base);
			अवरोध;
		हाल CMDF_ROUND_DOWN:
			भागider = (*nanosec) / base;
			अवरोध;
		हाल CMDF_ROUND_UP:
			भागider = DIV_ROUND_UP(*nanosec, base);
			अवरोध;
		पूर्ण
		अगर (भागider < 65536) अणु
			*nanosec = भागider * base;
			वापस (prescale << 16) | (भागider);
		पूर्ण
	पूर्ण

	prescale = 15;
	base = समयr_base * (prescale + 1);
	भागider = 65535;
	*nanosec = भागider * base;
	वापस (prescale << 16) | (भागider);
पूर्ण

अटल पूर्णांक dt3k_ai_cmdtest(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s, काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा dt3k_boardtype *board = dev->board_ptr;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक arg;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_TIMER);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_TIMER);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */
	/* Step 2b : and mutually compatible */

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
						    board->ai_speed);
		err |= comedi_check_trigger_arg_max(&cmd->scan_begin_arg,
						    100 * 16 * 65535);
	पूर्ण

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
						    board->ai_speed);
		err |= comedi_check_trigger_arg_max(&cmd->convert_arg,
						    50 * 16 * 65535);
	पूर्ण

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_max(&cmd->stop_arg, 0x00ffffff);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* step 4: fix up any arguments */

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		arg = cmd->scan_begin_arg;
		dt3k_ns_to_समयr(100, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);
	पूर्ण

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		arg = cmd->convert_arg;
		dt3k_ns_to_समयr(50, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg);

		अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
			arg = cmd->convert_arg * cmd->scan_end_arg;
			err |= comedi_check_trigger_arg_min(
				&cmd->scan_begin_arg, arg);
		पूर्ण
	पूर्ण

	अगर (err)
		वापस 4;

	वापस 0;
पूर्ण

अटल पूर्णांक dt3k_ai_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	पूर्णांक i;
	अचिन्हित पूर्णांक chan, range, aref;
	अचिन्हित पूर्णांक भागider;
	अचिन्हित पूर्णांक tscanभाग;

	क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
		chan = CR_CHAN(cmd->chanlist[i]);
		range = CR_RANGE(cmd->chanlist[i]);

		ग_लिखोw((range << 6) | chan, dev->mmio + DPR_ADC_BUFFER + i);
	पूर्ण
	aref = CR_AREF(cmd->chanlist[0]);

	ग_लिखोw(cmd->scan_end_arg, dev->mmio + DPR_PARAMS(0));

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		भागider = dt3k_ns_to_समयr(50, &cmd->convert_arg, cmd->flags);
		ग_लिखोw((भागider >> 16), dev->mmio + DPR_PARAMS(1));
		ग_लिखोw((भागider & 0xffff), dev->mmio + DPR_PARAMS(2));
	पूर्ण

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		tscanभाग = dt3k_ns_to_समयr(100, &cmd->scan_begin_arg,
					    cmd->flags);
		ग_लिखोw((tscanभाग >> 16), dev->mmio + DPR_PARAMS(3));
		ग_लिखोw((tscanभाग & 0xffff), dev->mmio + DPR_PARAMS(4));
	पूर्ण

	ग_लिखोw(DPR_PARAM5_AD_TRIG_INT_RETRIG, dev->mmio + DPR_PARAMS(5));
	ग_लिखोw((aref == AREF_DIFF) ? DPR_PARAM6_AD_DIFF : 0,
	       dev->mmio + DPR_PARAMS(6));

	ग_लिखोw(DPR_AI_FIFO_DEPTH / 2, dev->mmio + DPR_PARAMS(7));

	ग_लिखोw(DPR_SUBSYS_AI, dev->mmio + DPR_SUBSYS);
	dt3k_send_cmd(dev, DPR_CMD_CONFIG);

	ग_लिखोw(DPR_INTR_ADFULL | DPR_INTR_ADSWERR | DPR_INTR_ADHWERR,
	       dev->mmio + DPR_INT_MASK);

	debug_n_पूर्णांकs = 0;

	ग_लिखोw(DPR_SUBSYS_AI, dev->mmio + DPR_SUBSYS);
	dt3k_send_cmd(dev, DPR_CMD_START);

	वापस 0;
पूर्ण

अटल पूर्णांक dt3k_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_insn *insn,
			     अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक chan, gain;

	chan = CR_CHAN(insn->chanspec);
	gain = CR_RANGE(insn->chanspec);
	/* XXX करोcs करोn't explain how to select aref */

	क्रम (i = 0; i < insn->n; i++)
		data[i] = dt3k_पढ़ोsingle(dev, DPR_SUBSYS_AI, chan, gain);

	वापस i;
पूर्ण

अटल पूर्णांक dt3k_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];
		dt3k_ग_लिखोsingle(dev, DPR_SUBSYS_AO, chan, val);
	पूर्ण
	s->पढ़ोback[chan] = val;

	वापस insn->n;
पूर्ण

अटल व्योम dt3k_dio_config(काष्ठा comedi_device *dev, पूर्णांक bits)
अणु
	/* XXX */
	ग_लिखोw(DPR_SUBSYS_DOUT, dev->mmio + DPR_SUBSYS);

	ग_लिखोw(bits, dev->mmio + DPR_PARAMS(0));

	/* XXX ग_लिखो 0 to DPR_PARAMS(1) and DPR_PARAMS(2) ? */

	dt3k_send_cmd(dev, DPR_CMD_CONFIG);
पूर्ण

अटल पूर्णांक dt3k_dio_insn_config(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक mask;
	पूर्णांक ret;

	अगर (chan < 4)
		mask = 0x0f;
	अन्यथा
		mask = 0xf0;

	ret = comedi_dio_insn_config(dev, s, insn, data, mask);
	अगर (ret)
		वापस ret;

	dt3k_dio_config(dev, (s->io_bits & 0x01) | ((s->io_bits & 0x10) >> 3));

	वापस insn->n;
पूर्ण

अटल पूर्णांक dt3k_dio_insn_bits(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		dt3k_ग_लिखोsingle(dev, DPR_SUBSYS_DOUT, 0, s->state);

	data[1] = dt3k_पढ़ोsingle(dev, DPR_SUBSYS_DIN, 0, 0);

	वापस insn->n;
पूर्ण

अटल पूर्णांक dt3k_mem_insn_पढ़ो(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक addr = CR_CHAN(insn->chanspec);
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		ग_लिखोw(DPR_SUBSYS_MEM, dev->mmio + DPR_SUBSYS);
		ग_लिखोw(addr, dev->mmio + DPR_PARAMS(0));
		ग_लिखोw(1, dev->mmio + DPR_PARAMS(1));

		dt3k_send_cmd(dev, DPR_CMD_READCODE);

		data[i] = पढ़ोw(dev->mmio + DPR_PARAMS(2));
	पूर्ण

	वापस i;
पूर्ण

अटल पूर्णांक dt3000_स्वतः_attach(काष्ठा comedi_device *dev,
			      अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा dt3k_boardtype *board = शून्य;
	काष्ठा dt3k_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret = 0;

	अगर (context < ARRAY_SIZE(dt3k_boardtypes))
		board = &dt3k_boardtypes[context];
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_pci_enable(dev);
	अगर (ret < 0)
		वापस ret;

	dev->mmio = pci_ioremap_bar(pcidev, 0);
	अगर (!dev->mmio)
		वापस -ENOMEM;

	अगर (pcidev->irq) अणु
		ret = request_irq(pcidev->irq, dt3k_पूर्णांकerrupt, IRQF_SHARED,
				  dev->board_name, dev);
		अगर (ret == 0)
			dev->irq = pcidev->irq;
	पूर्ण

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_GROUND | SDF_DIFF;
	s->n_chan	= board->adchan;
	s->maxdata	= board->ai_is_16bit ? 0xffff : 0x0fff;
	s->range_table	= &range_dt3000_ai;	/* XXX */
	s->insn_पढ़ो	= dt3k_ai_insn_पढ़ो;
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->len_chanlist	= 512;
		s->करो_cmd	= dt3k_ai_cmd;
		s->करो_cmdtest	= dt3k_ai_cmdtest;
		s->cancel	= dt3k_ai_cancel;
	पूर्ण

	/* Analog Output subdevice */
	s = &dev->subdevices[1];
	अगर (board->has_ao) अणु
		s->type		= COMEDI_SUBD_AO;
		s->subdev_flags	= SDF_WRITABLE;
		s->n_chan	= 2;
		s->maxdata	= 0x0fff;
		s->range_table	= &range_bipolar10;
		s->insn_ग_लिखो	= dt3k_ao_insn_ग_लिखो;

		ret = comedi_alloc_subdev_पढ़ोback(s);
		अगर (ret)
			वापस ret;

	पूर्ण अन्यथा अणु
		s->type		= COMEDI_SUBD_UNUSED;
	पूर्ण

	/* Digital I/O subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_config	= dt3k_dio_insn_config;
	s->insn_bits	= dt3k_dio_insn_bits;

	/* Memory subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_MEMORY;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 0x1000;
	s->maxdata	= 0xff;
	s->range_table	= &range_unknown;
	s->insn_पढ़ो	= dt3k_mem_insn_पढ़ो;

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver dt3000_driver = अणु
	.driver_name	= "dt3000",
	.module		= THIS_MODULE,
	.स्वतः_attach	= dt3000_स्वतः_attach,
	.detach		= comedi_pci_detach,
पूर्ण;

अटल पूर्णांक dt3000_pci_probe(काष्ठा pci_dev *dev,
			    स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &dt3000_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id dt3000_pci_table[] = अणु
	अणु PCI_VDEVICE(DT, 0x0022), BOARD_DT3001 पूर्ण,
	अणु PCI_VDEVICE(DT, 0x0023), BOARD_DT3002 पूर्ण,
	अणु PCI_VDEVICE(DT, 0x0024), BOARD_DT3003 पूर्ण,
	अणु PCI_VDEVICE(DT, 0x0025), BOARD_DT3004 पूर्ण,
	अणु PCI_VDEVICE(DT, 0x0026), BOARD_DT3005 पूर्ण,
	अणु PCI_VDEVICE(DT, 0x0027), BOARD_DT3001_PGL पूर्ण,
	अणु PCI_VDEVICE(DT, 0x0028), BOARD_DT3003_PGL पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, dt3000_pci_table);

अटल काष्ठा pci_driver dt3000_pci_driver = अणु
	.name		= "dt3000",
	.id_table	= dt3000_pci_table,
	.probe		= dt3000_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(dt3000_driver, dt3000_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for Data Translation DT3000 series boards");
MODULE_LICENSE("GPL");
