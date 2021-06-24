<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Comedi driver क्रम National Instruments AT-A2150 boards
 * Copyright (C) 2001, 2002 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: ni_at_a2150
 * Description: National Instruments AT-A2150
 * Author: Frank Mori Hess
 * Status: works
 * Devices: [National Instruments] AT-A2150C (at_a2150c), AT-2150S (at_a2150s)
 *
 * Configuration options:
 *   [0] - I/O port base address
 *   [1] - IRQ (optional, required क्रम समयd conversions)
 *   [2] - DMA (optional, required क्रम समयd conversions)
 *
 * Yet another driver क्रम obsolete hardware brought to you by Frank Hess.
 * Testing and debugging help provided by Dave Andruczyk.
 *
 * If you want to ac couple the board's inमाला_दो, use AREF_OTHER.
 *
 * The only dअगरference in the boards is their master घड़ी frequencies.
 *
 * References (from ftp://ftp.natinst.com/support/manuals):
 *   320360.pdf  AT-A2150 User Manual
 *
 * TODO:
 * - analog level triggering
 * - TRIG_WAKE_EOS
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>

#समावेश "../comedidev.h"

#समावेश "comedi_isadma.h"
#समावेश "comedi_8254.h"

#घोषणा A2150_DMA_BUFFER_SIZE	0xff00	/*  size in bytes of dma buffer */

/* Registers and bits */
#घोषणा CONFIG_REG		0x0
#घोषणा   CHANNEL_BITS(x)	((x) & 0x7)
#घोषणा   CHANNEL_MASK		0x7
#घोषणा   CLOCK_SELECT_BITS(x)	(((x) & 0x3) << 3)
#घोषणा   CLOCK_DIVISOR_BITS(x)	(((x) & 0x3) << 5)
#घोषणा   CLOCK_MASK		(0xf << 3)
/* enable (करोn't पूर्णांकernally ground) channels 0 and 1 */
#घोषणा   ENABLE0_BIT		0x80
/* enable (करोn't पूर्णांकernally ground) channels 2 and 3 */
#घोषणा   ENABLE1_BIT		0x100
#घोषणा   AC0_BIT		0x200	/* ac couple channels 0,1 */
#घोषणा   AC1_BIT		0x400	/* ac couple channels 2,3 */
#घोषणा   APD_BIT		0x800	/* analog घातer करोwn */
#घोषणा   DPD_BIT		0x1000	/* digital घातer करोwn */
#घोषणा TRIGGER_REG		0x2	/* trigger config रेजिस्टर */
#घोषणा   POST_TRIGGER_BITS	0x2
#घोषणा   DELAY_TRIGGER_BITS	0x3
#घोषणा   HW_TRIG_EN		0x10	/* enable hardware trigger */
#घोषणा FIFO_START_REG		0x6	/* software start aquistion trigger */
#घोषणा FIFO_RESET_REG		0x8	/* clears fअगरo + fअगरo flags */
#घोषणा FIFO_DATA_REG		0xa	/* पढ़ो data */
#घोषणा DMA_TC_CLEAR_REG	0xe	/* clear dma terminal count पूर्णांकerrupt */
#घोषणा STATUS_REG		0x12	/* पढ़ो only */
#घोषणा   FNE_BIT		0x1	/* fअगरo not empty */
#घोषणा   OVFL_BIT		0x8	/* fअगरo overflow */
#घोषणा   EDAQ_BIT		0x10	/* end of acquisition पूर्णांकerrupt */
#घोषणा   DCAL_BIT		0x20	/* offset calibration in progress */
#घोषणा   INTR_BIT		0x40	/* पूर्णांकerrupt has occurred */
/* dma terminal count पूर्णांकerrupt has occurred */
#घोषणा   DMA_TC_BIT		0x80
#घोषणा   ID_BITS(x)		(((x) >> 8) & 0x3)
#घोषणा IRQ_DMA_CNTRL_REG	0x12			/* ग_लिखो only */
#घोषणा   DMA_CHAN_BITS(x)	((x) & 0x7)		/* sets dma channel */
#घोषणा   DMA_EN_BIT		0x8			/* enables dma */
#घोषणा   IRQ_LVL_BITS(x)	(((x) & 0xf) << 4)	/* sets irq level */
#घोषणा   FIFO_INTR_EN_BIT	0x100	/* enable fअगरo पूर्णांकerrupts */
#घोषणा   FIFO_INTR_FHF_BIT	0x200	/* पूर्णांकerrupt fअगरo half full */
/* enable पूर्णांकerrupt on dma terminal count */
#घोषणा   DMA_INTR_EN_BIT	0x800
#घोषणा   DMA_DEM_EN_BIT	0x1000	/* enables demand mode dma */
#घोषणा I8253_BASE_REG		0x14

काष्ठा a2150_board अणु
	स्थिर अक्षर *name;
	पूर्णांक घड़ी[4];		/* master घड़ी periods, in nanoseconds */
	पूर्णांक num_घड़ीs;		/* number of available master घड़ी speeds */
	पूर्णांक ai_speed;		/* maximum conversion rate in nanoseconds */
पूर्ण;

/* analog input range */
अटल स्थिर काष्ठा comedi_lrange range_a2150 = अणु
	1, अणु
		BIP_RANGE(2.828)
	पूर्ण
पूर्ण;

/* क्रमागत must match board indices */
क्रमागत अणु a2150_c, a2150_s पूर्ण;
अटल स्थिर काष्ठा a2150_board a2150_boards[] = अणु
	अणु
	 .name = "at-a2150c",
	 .घड़ी = अणु31250, 22676, 20833, 19531पूर्ण,
	 .num_घड़ीs = 4,
	 .ai_speed = 19531,
	 पूर्ण,
	अणु
	 .name = "at-a2150s",
	 .घड़ी = अणु62500, 50000, 41667, 0पूर्ण,
	 .num_घड़ीs = 3,
	 .ai_speed = 41667,
	 पूर्ण,
पूर्ण;

काष्ठा a2150_निजी अणु
	काष्ठा comedi_isadma *dma;
	अचिन्हित पूर्णांक count;	/* number of data poपूर्णांकs left to be taken */
	पूर्णांक irq_dma_bits;	/* irq/dma रेजिस्टर bits */
	पूर्णांक config_bits;	/* config रेजिस्टर bits */
पूर्ण;

/* पूर्णांकerrupt service routine */
अटल irqवापस_t a2150_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा a2150_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_isadma_desc *desc = &dma->desc[0];
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित लघु *buf = desc->virt_addr;
	अचिन्हित पूर्णांक max_poपूर्णांकs, num_poपूर्णांकs, residue, leftover;
	अचिन्हित लघु dpnt;
	पूर्णांक status;
	पूर्णांक i;

	अगर (!dev->attached)
		वापस IRQ_HANDLED;

	status = inw(dev->iobase + STATUS_REG);
	अगर ((status & INTR_BIT) == 0)
		वापस IRQ_NONE;

	अगर (status & OVFL_BIT) अणु
		async->events |= COMEDI_CB_ERROR;
		comedi_handle_events(dev, s);
	पूर्ण

	अगर ((status & DMA_TC_BIT) == 0) अणु
		async->events |= COMEDI_CB_ERROR;
		comedi_handle_events(dev, s);
		वापस IRQ_HANDLED;
	पूर्ण

	/*
	 * residue is the number of bytes left to be करोne on the dma
	 * transfer.  It should always be zero at this poपूर्णांक unless
	 * the stop_src is set to बाह्यal triggering.
	 */
	residue = comedi_isadma_disable(desc->chan);

	/* figure out how many poपूर्णांकs to पढ़ो */
	max_poपूर्णांकs = comedi_bytes_to_samples(s, desc->size);
	num_poपूर्णांकs = max_poपूर्णांकs - comedi_bytes_to_samples(s, residue);
	अगर (devpriv->count < num_poपूर्णांकs && cmd->stop_src == TRIG_COUNT)
		num_poपूर्णांकs = devpriv->count;

	/* figure out how many poपूर्णांकs will be stored next समय */
	leftover = 0;
	अगर (cmd->stop_src == TRIG_NONE) अणु
		leftover = comedi_bytes_to_samples(s, desc->size);
	पूर्ण अन्यथा अगर (devpriv->count > max_poपूर्णांकs) अणु
		leftover = devpriv->count - max_poपूर्णांकs;
		अगर (leftover > max_poपूर्णांकs)
			leftover = max_poपूर्णांकs;
	पूर्ण
	/*
	 * There should only be a residue अगर collection was stopped by having
	 * the stop_src set to an बाह्यal trigger, in which हाल there
	 * will be no more data
	 */
	अगर (residue)
		leftover = 0;

	क्रम (i = 0; i < num_poपूर्णांकs; i++) अणु
		/* ग_लिखो data poपूर्णांक to comedi buffer */
		dpnt = buf[i];
		/* convert from 2's complement to अचिन्हित coding */
		dpnt ^= 0x8000;
		comedi_buf_ग_लिखो_samples(s, &dpnt, 1);
		अगर (cmd->stop_src == TRIG_COUNT) अणु
			अगर (--devpriv->count == 0) अणु	/* end of acquisition */
				async->events |= COMEDI_CB_EOA;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	/* re-enable dma */
	अगर (leftover) अणु
		desc->size = comedi_samples_to_bytes(s, leftover);
		comedi_isadma_program(desc);
	पूर्ण

	comedi_handle_events(dev, s);

	/* clear पूर्णांकerrupt */
	outw(0x00, dev->iobase + DMA_TC_CLEAR_REG);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक a2150_cancel(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा a2150_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_isadma_desc *desc = &dma->desc[0];

	/* disable dma on card */
	devpriv->irq_dma_bits &= ~DMA_INTR_EN_BIT & ~DMA_EN_BIT;
	outw(devpriv->irq_dma_bits, dev->iobase + IRQ_DMA_CNTRL_REG);

	/* disable computer's dma */
	comedi_isadma_disable(desc->chan);

	/* clear fअगरo and reset triggering circuitry */
	outw(0, dev->iobase + FIFO_RESET_REG);

	वापस 0;
पूर्ण

/*
 * sets bits in devpriv->घड़ी_bits to nearest approximation of requested
 * period, adjusts requested period to actual timing.
 */
अटल पूर्णांक a2150_get_timing(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक *period,
			    अचिन्हित पूर्णांक flags)
अणु
	स्थिर काष्ठा a2150_board *board = dev->board_ptr;
	काष्ठा a2150_निजी *devpriv = dev->निजी;
	पूर्णांक lub, glb, temp;
	पूर्णांक lub_भागisor_shअगरt, lub_index, glb_भागisor_shअगरt, glb_index;
	पूर्णांक i, j;

	/* initialize greatest lower and least upper bounds */
	lub_भागisor_shअगरt = 3;
	lub_index = 0;
	lub = board->घड़ी[lub_index] * (1 << lub_भागisor_shअगरt);
	glb_भागisor_shअगरt = 0;
	glb_index = board->num_घड़ीs - 1;
	glb = board->घड़ी[glb_index] * (1 << glb_भागisor_shअगरt);

	/* make sure period is in available range */
	अगर (*period < glb)
		*period = glb;
	अगर (*period > lub)
		*period = lub;

	/* we can multiply period by 1, 2, 4, or 8, using (1 << i) */
	क्रम (i = 0; i < 4; i++) अणु
		/* there are a maximum of 4 master घड़ीs */
		क्रम (j = 0; j < board->num_घड़ीs; j++) अणु
			/* temp is the period in nanosec we are evaluating */
			temp = board->घड़ी[j] * (1 << i);
			/* अगर it is the best match yet */
			अगर (temp < lub && temp >= *period) अणु
				lub_भागisor_shअगरt = i;
				lub_index = j;
				lub = temp;
			पूर्ण
			अगर (temp > glb && temp <= *period) अणु
				glb_भागisor_shअगरt = i;
				glb_index = j;
				glb = temp;
			पूर्ण
		पूर्ण
	पूर्ण
	चयन (flags & CMDF_ROUND_MASK) अणु
	हाल CMDF_ROUND_NEAREST:
	शेष:
		/* अगर least upper bound is better approximation */
		अगर (lub - *period < *period - glb)
			*period = lub;
		अन्यथा
			*period = glb;
		अवरोध;
	हाल CMDF_ROUND_UP:
		*period = lub;
		अवरोध;
	हाल CMDF_ROUND_DOWN:
		*period = glb;
		अवरोध;
	पूर्ण

	/* set घड़ी bits क्रम config रेजिस्टर appropriately */
	devpriv->config_bits &= ~CLOCK_MASK;
	अगर (*period == lub) अणु
		devpriv->config_bits |=
		    CLOCK_SELECT_BITS(lub_index) |
		    CLOCK_DIVISOR_BITS(lub_भागisor_shअगरt);
	पूर्ण अन्यथा अणु
		devpriv->config_bits |=
		    CLOCK_SELECT_BITS(glb_index) |
		    CLOCK_DIVISOR_BITS(glb_भागisor_shअगरt);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक a2150_set_chanlist(काष्ठा comedi_device *dev,
			      अचिन्हित पूर्णांक start_channel,
			      अचिन्हित पूर्णांक num_channels)
अणु
	काष्ठा a2150_निजी *devpriv = dev->निजी;

	अगर (start_channel + num_channels > 4)
		वापस -1;

	devpriv->config_bits &= ~CHANNEL_MASK;

	चयन (num_channels) अणु
	हाल 1:
		devpriv->config_bits |= CHANNEL_BITS(0x4 | start_channel);
		अवरोध;
	हाल 2:
		अगर (start_channel == 0)
			devpriv->config_bits |= CHANNEL_BITS(0x2);
		अन्यथा अगर (start_channel == 2)
			devpriv->config_bits |= CHANNEL_BITS(0x3);
		अन्यथा
			वापस -1;
		अवरोध;
	हाल 4:
		devpriv->config_bits |= CHANNEL_BITS(0x1);
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक a2150_ai_check_chanlist(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_cmd *cmd)
अणु
	अचिन्हित पूर्णांक chan0 = CR_CHAN(cmd->chanlist[0]);
	अचिन्हित पूर्णांक aref0 = CR_AREF(cmd->chanlist[0]);
	पूर्णांक i;

	अगर (cmd->chanlist_len == 2 && (chan0 == 1 || chan0 == 3)) अणु
		dev_dbg(dev->class_dev,
			"length 2 chanlist must be channels 0,1 or channels 2,3\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cmd->chanlist_len == 3) अणु
		dev_dbg(dev->class_dev,
			"chanlist must have 1,2 or 4 channels\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 1; i < cmd->chanlist_len; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);
		अचिन्हित पूर्णांक aref = CR_AREF(cmd->chanlist[i]);

		अगर (chan != (chan0 + i)) अणु
			dev_dbg(dev->class_dev,
				"entries in chanlist must be consecutive channels, counting upwards\n");
			वापस -EINVAL;
		पूर्ण

		अगर (chan == 2)
			aref0 = aref;
		अगर (aref != aref0) अणु
			dev_dbg(dev->class_dev,
				"channels 0/1 and 2/3 must have the same analog reference\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक a2150_ai_cmdtest(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s, काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा a2150_board *board = dev->board_ptr;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक arg;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_TIMER);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
						    board->ai_speed);
	पूर्ण

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

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		arg = cmd->scan_begin_arg;
		a2150_get_timing(dev, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);
	पूर्ण

	अगर (err)
		वापस 4;

	/* Step 5: check channel list अगर it exists */
	अगर (cmd->chanlist && cmd->chanlist_len > 0)
		err |= a2150_ai_check_chanlist(dev, s, cmd);

	अगर (err)
		वापस 5;

	वापस 0;
पूर्ण

अटल पूर्णांक a2150_ai_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा a2150_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_isadma_desc *desc = &dma->desc[0];
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित पूर्णांक old_config_bits = devpriv->config_bits;
	अचिन्हित पूर्णांक trigger_bits;

	अगर (cmd->flags & CMDF_PRIORITY) अणु
		dev_err(dev->class_dev,
			"dma incompatible with hard real-time interrupt (CMDF_PRIORITY), aborting\n");
		वापस -1;
	पूर्ण
	/* clear fअगरo and reset triggering circuitry */
	outw(0, dev->iobase + FIFO_RESET_REG);

	/* setup chanlist */
	अगर (a2150_set_chanlist(dev, CR_CHAN(cmd->chanlist[0]),
			       cmd->chanlist_len) < 0)
		वापस -1;

	/* setup ac/dc coupling */
	अगर (CR_AREF(cmd->chanlist[0]) == AREF_OTHER)
		devpriv->config_bits |= AC0_BIT;
	अन्यथा
		devpriv->config_bits &= ~AC0_BIT;
	अगर (CR_AREF(cmd->chanlist[2]) == AREF_OTHER)
		devpriv->config_bits |= AC1_BIT;
	अन्यथा
		devpriv->config_bits &= ~AC1_BIT;

	/* setup timing */
	a2150_get_timing(dev, &cmd->scan_begin_arg, cmd->flags);

	/* send timing, channel, config bits */
	outw(devpriv->config_bits, dev->iobase + CONFIG_REG);

	/* initialize number of samples reमुख्यing */
	devpriv->count = cmd->stop_arg * cmd->chanlist_len;

	comedi_isadma_disable(desc->chan);

	/* set size of transfer to fill in 1/3 second */
#घोषणा ONE_THIRD_SECOND 333333333
	desc->size = comedi_bytes_per_sample(s) * cmd->chanlist_len *
		    ONE_THIRD_SECOND / cmd->scan_begin_arg;
	अगर (desc->size > desc->maxsize)
		desc->size = desc->maxsize;
	अगर (desc->size < comedi_bytes_per_sample(s))
		desc->size = comedi_bytes_per_sample(s);
	desc->size -= desc->size % comedi_bytes_per_sample(s);

	comedi_isadma_program(desc);

	/*
	 * Clear dma पूर्णांकerrupt beक्रमe enabling it, to try and get rid of
	 * that one spurious पूर्णांकerrupt that has been happening.
	 */
	outw(0x00, dev->iobase + DMA_TC_CLEAR_REG);

	/* enable dma on card */
	devpriv->irq_dma_bits |= DMA_INTR_EN_BIT | DMA_EN_BIT;
	outw(devpriv->irq_dma_bits, dev->iobase + IRQ_DMA_CNTRL_REG);

	/* may need to रुको 72 sampling periods अगर timing was changed */
	comedi_8254_load(dev->pacer, 2, 72, I8254_MODE0 | I8254_BINARY);

	/* setup start triggering */
	trigger_bits = 0;
	/* decide अगर we need to रुको 72 periods क्रम valid data */
	अगर (cmd->start_src == TRIG_NOW &&
	    (old_config_bits & CLOCK_MASK) !=
	    (devpriv->config_bits & CLOCK_MASK)) अणु
		/* set trigger source to delay trigger */
		trigger_bits |= DELAY_TRIGGER_BITS;
	पूर्ण अन्यथा अणु
		/* otherwise no delay */
		trigger_bits |= POST_TRIGGER_BITS;
	पूर्ण
	/* enable बाह्यal hardware trigger */
	अगर (cmd->start_src == TRIG_EXT) अणु
		trigger_bits |= HW_TRIG_EN;
	पूर्ण अन्यथा अगर (cmd->start_src == TRIG_OTHER) अणु
		/*
		 * XXX add support क्रम level/slope start trigger
		 * using TRIG_OTHER
		 */
		dev_err(dev->class_dev, "you shouldn't see this?\n");
	पूर्ण
	/* send trigger config bits */
	outw(trigger_bits, dev->iobase + TRIGGER_REG);

	/* start acquisition क्रम soft trigger */
	अगर (cmd->start_src == TRIG_NOW)
		outw(0, dev->iobase + FIFO_START_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक a2150_ai_eoc(काष्ठा comedi_device *dev,
			काष्ठा comedi_subdevice *s,
			काष्ठा comedi_insn *insn,
			अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inw(dev->iobase + STATUS_REG);
	अगर (status & FNE_BIT)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक a2150_ai_rinsn(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
			  काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	काष्ठा a2150_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक n;
	पूर्णांक ret;

	/* clear fअगरo and reset triggering circuitry */
	outw(0, dev->iobase + FIFO_RESET_REG);

	/* setup chanlist */
	अगर (a2150_set_chanlist(dev, CR_CHAN(insn->chanspec), 1) < 0)
		वापस -1;

	/* set dc coupling */
	devpriv->config_bits &= ~AC0_BIT;
	devpriv->config_bits &= ~AC1_BIT;

	/* send timing, channel, config bits */
	outw(devpriv->config_bits, dev->iobase + CONFIG_REG);

	/* disable dma on card */
	devpriv->irq_dma_bits &= ~DMA_INTR_EN_BIT & ~DMA_EN_BIT;
	outw(devpriv->irq_dma_bits, dev->iobase + IRQ_DMA_CNTRL_REG);

	/* setup start triggering */
	outw(0, dev->iobase + TRIGGER_REG);

	/* start acquisition क्रम soft trigger */
	outw(0, dev->iobase + FIFO_START_REG);

	/*
	 * there is a 35.6 sample delay क्रम data to get through the
	 * antialias filter
	 */
	क्रम (n = 0; n < 36; n++) अणु
		ret = comedi_समयout(dev, s, insn, a2150_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		inw(dev->iobase + FIFO_DATA_REG);
	पूर्ण

	/* पढ़ो data */
	क्रम (n = 0; n < insn->n; n++) अणु
		ret = comedi_समयout(dev, s, insn, a2150_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		data[n] = inw(dev->iobase + FIFO_DATA_REG);
		data[n] ^= 0x8000;
	पूर्ण

	/* clear fअगरo and reset triggering circuitry */
	outw(0, dev->iobase + FIFO_RESET_REG);

	वापस n;
पूर्ण

अटल व्योम a2150_alloc_irq_and_dma(काष्ठा comedi_device *dev,
				    काष्ठा comedi_devconfig *it)
अणु
	काष्ठा a2150_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक irq_num = it->options[1];
	अचिन्हित पूर्णांक dma_chan = it->options[2];

	/*
	 * Only IRQs 15, 14, 12-9, and 7-3 are valid.
	 * Only DMA channels 7-5 and 3-0 are valid.
	 */
	अगर (irq_num > 15 || dma_chan > 7 ||
	    !((1 << irq_num) & 0xdef8) || !((1 << dma_chan) & 0xef))
		वापस;

	अगर (request_irq(irq_num, a2150_पूर्णांकerrupt, 0, dev->board_name, dev))
		वापस;

	/* DMA uses 1 buffer */
	devpriv->dma = comedi_isadma_alloc(dev, 1, dma_chan, dma_chan,
					   A2150_DMA_BUFFER_SIZE,
					   COMEDI_ISADMA_READ);
	अगर (!devpriv->dma) अणु
		मुक्त_irq(irq_num, dev);
	पूर्ण अन्यथा अणु
		dev->irq = irq_num;
		devpriv->irq_dma_bits = IRQ_LVL_BITS(irq_num) |
					DMA_CHAN_BITS(dma_chan);
	पूर्ण
पूर्ण

अटल व्योम a2150_मुक्त_dma(काष्ठा comedi_device *dev)
अणु
	काष्ठा a2150_निजी *devpriv = dev->निजी;

	अगर (devpriv)
		comedi_isadma_मुक्त(devpriv->dma);
पूर्ण

अटल स्थिर काष्ठा a2150_board *a2150_probe(काष्ठा comedi_device *dev)
अणु
	पूर्णांक id = ID_BITS(inw(dev->iobase + STATUS_REG));

	अगर (id >= ARRAY_SIZE(a2150_boards))
		वापस शून्य;

	वापस &a2150_boards[id];
पूर्ण

अटल पूर्णांक a2150_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा a2150_board *board;
	काष्ठा a2150_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	अटल स्थिर पूर्णांक समयout = 2000;
	पूर्णांक i;
	पूर्णांक ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_request_region(dev, it->options[0], 0x1c);
	अगर (ret)
		वापस ret;

	board = a2150_probe(dev);
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	/* an IRQ and DMA are required to support async commands */
	a2150_alloc_irq_and_dma(dev, it);

	dev->pacer = comedi_8254_init(dev->iobase + I8253_BASE_REG,
				      0, I8254_IO8, 0);
	अगर (!dev->pacer)
		वापस -ENOMEM;

	ret = comedi_alloc_subdevices(dev, 1);
	अगर (ret)
		वापस ret;

	/* analog input subdevice */
	s = &dev->subdevices[0];
	s->type = COMEDI_SUBD_AI;
	s->subdev_flags = SDF_READABLE | SDF_GROUND | SDF_OTHER;
	s->n_chan = 4;
	s->maxdata = 0xffff;
	s->range_table = &range_a2150;
	s->insn_पढ़ो = a2150_ai_rinsn;
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags |= SDF_CMD_READ;
		s->len_chanlist = s->n_chan;
		s->करो_cmd = a2150_ai_cmd;
		s->करो_cmdtest = a2150_ai_cmdtest;
		s->cancel = a2150_cancel;
	पूर्ण

	/* set card's irq and dma levels */
	outw(devpriv->irq_dma_bits, dev->iobase + IRQ_DMA_CNTRL_REG);

	/* reset and sync adc घड़ी circuitry */
	outw_p(DPD_BIT | APD_BIT, dev->iobase + CONFIG_REG);
	outw_p(DPD_BIT, dev->iobase + CONFIG_REG);
	/* initialize configuration रेजिस्टर */
	devpriv->config_bits = 0;
	outw(devpriv->config_bits, dev->iobase + CONFIG_REG);
	/* रुको until offset calibration is करोne, then enable analog inमाला_दो */
	क्रम (i = 0; i < समयout; i++) अणु
		अगर ((DCAL_BIT & inw(dev->iobase + STATUS_REG)) == 0)
			अवरोध;
		usleep_range(1000, 3000);
	पूर्ण
	अगर (i == समयout) अणु
		dev_err(dev->class_dev,
			"timed out waiting for offset calibration to complete\n");
		वापस -ETIME;
	पूर्ण
	devpriv->config_bits |= ENABLE0_BIT | ENABLE1_BIT;
	outw(devpriv->config_bits, dev->iobase + CONFIG_REG);

	वापस 0;
पूर्ण;

अटल व्योम a2150_detach(काष्ठा comedi_device *dev)
अणु
	अगर (dev->iobase)
		outw(APD_BIT | DPD_BIT, dev->iobase + CONFIG_REG);
	a2150_मुक्त_dma(dev);
	comedi_legacy_detach(dev);
पूर्ण;

अटल काष्ठा comedi_driver ni_at_a2150_driver = अणु
	.driver_name	= "ni_at_a2150",
	.module		= THIS_MODULE,
	.attach		= a2150_attach,
	.detach		= a2150_detach,
पूर्ण;
module_comedi_driver(ni_at_a2150_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
