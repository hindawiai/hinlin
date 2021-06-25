<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/amplc_dio200_common.c
 *
 * Common support code क्रम "amplc_dio200" and "amplc_dio200_pci".
 *
 * Copyright (C) 2005-2013 MEV Ltd. <https://www.mev.co.uk/>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1998,2000 David A. Schleef <ds@schleef.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedidev.h"

#समावेश "amplc_dio200.h"
#समावेश "comedi_8254.h"
#समावेश "8255.h"		/* only क्रम रेजिस्टर defines */

/* 200 series रेजिस्टरs */
#घोषणा DIO200_IO_SIZE		0x20
#घोषणा DIO200_PCIE_IO_SIZE	0x4000
#घोषणा DIO200_CLK_SCE(x)	(0x18 + (x))	/* Group X/Y/Z घड़ी sel reg */
#घोषणा DIO200_GAT_SCE(x)	(0x1b + (x))	/* Group X/Y/Z gate sel reg */
#घोषणा DIO200_INT_SCE		0x1e	/* Interrupt enable/status रेजिस्टर */
/* Extra रेजिस्टरs क्रम new PCIe boards */
#घोषणा DIO200_ENHANCE		0x20	/* 1 to enable enhanced features */
#घोषणा DIO200_VERSION		0x24	/* Hardware version रेजिस्टर */
#घोषणा DIO200_TS_CONFIG	0x600	/* Timestamp समयr config रेजिस्टर */
#घोषणा DIO200_TS_COUNT		0x602	/* Timestamp समयr count रेजिस्टर */

/*
 * Functions क्रम स्थिरructing value क्रम DIO_200_?CLK_SCE and
 * DIO_200_?GAT_SCE रेजिस्टरs:
 *
 * 'which' is: 0 क्रम CTR-X1, CTR-Y1, CTR-Z1; 1 क्रम CTR-X2, CTR-Y2 or CTR-Z2.
 * 'chan' is the channel: 0, 1 or 2.
 * 'source' is the संकेत source: 0 to 7, or 0 to 31 क्रम "enhanced" boards.
 */
अटल अचिन्हित अक्षर clk_gat_sce(अचिन्हित पूर्णांक which, अचिन्हित पूर्णांक chan,
				 अचिन्हित पूर्णांक source)
अणु
	वापस (which << 5) | (chan << 3) |
	       ((source & 030) << 3) | (source & 007);
पूर्ण

/*
 * Periods of the पूर्णांकernal घड़ी sources in nanoseconds.
 */
अटल स्थिर अचिन्हित पूर्णांक घड़ी_period[32] = अणु
	[1] = 100,		/* 10 MHz */
	[2] = 1000,		/* 1 MHz */
	[3] = 10000,		/* 100 kHz */
	[4] = 100000,		/* 10 kHz */
	[5] = 1000000,		/* 1 kHz */
	[11] = 50,		/* 20 MHz (enhanced boards) */
	/* घड़ी sources 12 and later reserved क्रम enhanced boards */
पूर्ण;

/*
 * Timestamp समयr configuration रेजिस्टर (क्रम new PCIe boards).
 */
#घोषणा TS_CONFIG_RESET		0x100	/* Reset counter to zero. */
#घोषणा TS_CONFIG_CLK_SRC_MASK	0x0FF	/* Clock source. */
#घोषणा TS_CONFIG_MAX_CLK_SRC	2	/* Maximum घड़ी source value. */

/*
 * Periods of the बारtamp समयr घड़ी sources in nanoseconds.
 */
अटल स्थिर अचिन्हित पूर्णांक ts_घड़ी_period[TS_CONFIG_MAX_CLK_SRC + 1] = अणु
	1,			/* 1 nanosecond (but with 20 ns granularity). */
	1000,			/* 1 microsecond. */
	1000000,		/* 1 millisecond. */
पूर्ण;

काष्ठा dio200_subdev_8255 अणु
	अचिन्हित पूर्णांक ofs;		/* DIO base offset */
पूर्ण;

काष्ठा dio200_subdev_पूर्णांकr अणु
	spinlock_t spinlock;	/* protects the 'active' flag */
	अचिन्हित पूर्णांक ofs;
	अचिन्हित पूर्णांक valid_isns;
	अचिन्हित पूर्णांक enabled_isns;
	अचिन्हित पूर्णांक active:1;
पूर्ण;

अटल अचिन्हित अक्षर dio200_पढ़ो8(काष्ठा comedi_device *dev,
				  अचिन्हित पूर्णांक offset)
अणु
	स्थिर काष्ठा dio200_board *board = dev->board_ptr;

	अगर (board->is_pcie)
		offset <<= 3;

	अगर (dev->mmio)
		वापस पढ़ोb(dev->mmio + offset);
	वापस inb(dev->iobase + offset);
पूर्ण

अटल व्योम dio200_ग_लिखो8(काष्ठा comedi_device *dev,
			  अचिन्हित पूर्णांक offset, अचिन्हित अक्षर val)
अणु
	स्थिर काष्ठा dio200_board *board = dev->board_ptr;

	अगर (board->is_pcie)
		offset <<= 3;

	अगर (dev->mmio)
		ग_लिखोb(val, dev->mmio + offset);
	अन्यथा
		outb(val, dev->iobase + offset);
पूर्ण

अटल अचिन्हित पूर्णांक dio200_पढ़ो32(काष्ठा comedi_device *dev,
				  अचिन्हित पूर्णांक offset)
अणु
	स्थिर काष्ठा dio200_board *board = dev->board_ptr;

	अगर (board->is_pcie)
		offset <<= 3;

	अगर (dev->mmio)
		वापस पढ़ोl(dev->mmio + offset);
	वापस inl(dev->iobase + offset);
पूर्ण

अटल व्योम dio200_ग_लिखो32(काष्ठा comedi_device *dev,
			   अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक val)
अणु
	स्थिर काष्ठा dio200_board *board = dev->board_ptr;

	अगर (board->is_pcie)
		offset <<= 3;

	अगर (dev->mmio)
		ग_लिखोl(val, dev->mmio + offset);
	अन्यथा
		outl(val, dev->iobase + offset);
पूर्ण

अटल अचिन्हित पूर्णांक dio200_subdev_8254_offset(काष्ठा comedi_device *dev,
					      काष्ठा comedi_subdevice *s)
अणु
	स्थिर काष्ठा dio200_board *board = dev->board_ptr;
	काष्ठा comedi_8254 *i8254 = s->निजी;
	अचिन्हित पूर्णांक offset;

	/* get the offset that was passed to comedi_8254_*_init() */
	अगर (dev->mmio)
		offset = i8254->mmio - dev->mmio;
	अन्यथा
		offset = i8254->iobase - dev->iobase;

	/* हटाओ the shअगरt that was added क्रम PCIe boards */
	अगर (board->is_pcie)
		offset >>= 3;

	/* this offset now works क्रम the dio200_अणुपढ़ो,ग_लिखोपूर्ण helpers */
	वापस offset;
पूर्ण

अटल पूर्णांक dio200_subdev_पूर्णांकr_insn_bits(काष्ठा comedi_device *dev,
					काष्ठा comedi_subdevice *s,
					काष्ठा comedi_insn *insn,
					अचिन्हित पूर्णांक *data)
अणु
	स्थिर काष्ठा dio200_board *board = dev->board_ptr;
	काष्ठा dio200_subdev_पूर्णांकr *subpriv = s->निजी;

	अगर (board->has_पूर्णांक_sce) अणु
		/* Just पढ़ो the पूर्णांकerrupt status रेजिस्टर.  */
		data[1] = dio200_पढ़ो8(dev, subpriv->ofs) & subpriv->valid_isns;
	पूर्ण अन्यथा अणु
		/* No पूर्णांकerrupt status रेजिस्टर. */
		data[0] = 0;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल व्योम dio200_stop_पूर्णांकr(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s)
अणु
	स्थिर काष्ठा dio200_board *board = dev->board_ptr;
	काष्ठा dio200_subdev_पूर्णांकr *subpriv = s->निजी;

	subpriv->active = false;
	subpriv->enabled_isns = 0;
	अगर (board->has_पूर्णांक_sce)
		dio200_ग_लिखो8(dev, subpriv->ofs, 0);
पूर्ण

अटल व्योम dio200_start_पूर्णांकr(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s)
अणु
	स्थिर काष्ठा dio200_board *board = dev->board_ptr;
	काष्ठा dio200_subdev_पूर्णांकr *subpriv = s->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक n;
	अचिन्हित पूर्णांक isn_bits;

	/* Determine पूर्णांकerrupt sources to enable. */
	isn_bits = 0;
	अगर (cmd->chanlist) अणु
		क्रम (n = 0; n < cmd->chanlist_len; n++)
			isn_bits |= (1U << CR_CHAN(cmd->chanlist[n]));
	पूर्ण
	isn_bits &= subpriv->valid_isns;
	/* Enable पूर्णांकerrupt sources. */
	subpriv->enabled_isns = isn_bits;
	अगर (board->has_पूर्णांक_sce)
		dio200_ग_लिखो8(dev, subpriv->ofs, isn_bits);
पूर्ण

अटल पूर्णांक dio200_पूर्णांकtrig_start_पूर्णांकr(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा dio200_subdev_पूर्णांकr *subpriv = s->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित दीर्घ flags;

	अगर (trig_num != cmd->start_arg)
		वापस -EINVAL;

	spin_lock_irqsave(&subpriv->spinlock, flags);
	s->async->पूर्णांकtrig = शून्य;
	अगर (subpriv->active)
		dio200_start_पूर्णांकr(dev, s);

	spin_unlock_irqrestore(&subpriv->spinlock, flags);

	वापस 1;
पूर्ण

अटल व्योम dio200_पढ़ो_scan_पूर्णांकr(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  अचिन्हित पूर्णांक triggered)
अणु
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित लघु val;
	अचिन्हित पूर्णांक n, ch;

	val = 0;
	क्रम (n = 0; n < cmd->chanlist_len; n++) अणु
		ch = CR_CHAN(cmd->chanlist[n]);
		अगर (triggered & (1U << ch))
			val |= (1U << n);
	पूर्ण

	comedi_buf_ग_लिखो_samples(s, &val, 1);

	अगर (cmd->stop_src == TRIG_COUNT &&
	    s->async->scans_करोne >= cmd->stop_arg)
		s->async->events |= COMEDI_CB_EOA;
पूर्ण

अटल पूर्णांक dio200_handle_पढ़ो_पूर्णांकr(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s)
अणु
	स्थिर काष्ठा dio200_board *board = dev->board_ptr;
	काष्ठा dio200_subdev_पूर्णांकr *subpriv = s->निजी;
	अचिन्हित पूर्णांक triggered;
	अचिन्हित पूर्णांक पूर्णांकstat;
	अचिन्हित पूर्णांक cur_enabled;
	अचिन्हित दीर्घ flags;

	triggered = 0;

	spin_lock_irqsave(&subpriv->spinlock, flags);
	अगर (board->has_पूर्णांक_sce) अणु
		/*
		 * Collect पूर्णांकerrupt sources that have triggered and disable
		 * them temporarily.  Loop around until no extra पूर्णांकerrupt
		 * sources have triggered, at which poपूर्णांक, the valid part of
		 * the पूर्णांकerrupt status रेजिस्टर will पढ़ो zero, clearing the
		 * cause of the पूर्णांकerrupt.
		 *
		 * Mask off पूर्णांकerrupt sources alपढ़ोy seen to aव्योम infinite
		 * loop in हाल of misconfiguration.
		 */
		cur_enabled = subpriv->enabled_isns;
		जबतक ((पूर्णांकstat = (dio200_पढ़ो8(dev, subpriv->ofs) &
				   subpriv->valid_isns & ~triggered)) != 0) अणु
			triggered |= पूर्णांकstat;
			cur_enabled &= ~triggered;
			dio200_ग_लिखो8(dev, subpriv->ofs, cur_enabled);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * No पूर्णांकerrupt status रेजिस्टर.  Assume the single पूर्णांकerrupt
		 * source has triggered.
		 */
		triggered = subpriv->enabled_isns;
	पूर्ण

	अगर (triggered) अणु
		/*
		 * Some पूर्णांकerrupt sources have triggered and have been
		 * temporarily disabled to clear the cause of the पूर्णांकerrupt.
		 *
		 * Reenable them NOW to minimize the समय they are disabled.
		 */
		cur_enabled = subpriv->enabled_isns;
		अगर (board->has_पूर्णांक_sce)
			dio200_ग_लिखो8(dev, subpriv->ofs, cur_enabled);

		अगर (subpriv->active) अणु
			/*
			 * The command is still active.
			 *
			 * Ignore पूर्णांकerrupt sources that the command isn't
			 * पूर्णांकerested in (just in हाल there's a race
			 * condition).
			 */
			अगर (triggered & subpriv->enabled_isns) अणु
				/* Collect scan data. */
				dio200_पढ़ो_scan_पूर्णांकr(dev, s, triggered);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&subpriv->spinlock, flags);

	comedi_handle_events(dev, s);

	वापस (triggered != 0);
पूर्ण

अटल पूर्णांक dio200_subdev_पूर्णांकr_cancel(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s)
अणु
	काष्ठा dio200_subdev_पूर्णांकr *subpriv = s->निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&subpriv->spinlock, flags);
	अगर (subpriv->active)
		dio200_stop_पूर्णांकr(dev, s);

	spin_unlock_irqrestore(&subpriv->spinlock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक dio200_subdev_पूर्णांकr_cmdtest(काष्ठा comedi_device *dev,
				      काष्ठा comedi_subdevice *s,
				      काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW | TRIG_INT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_EXT);
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
	err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* step 4: fix up any arguments */

	/* अगर (err) वापस 4; */

	वापस 0;
पूर्ण

अटल पूर्णांक dio200_subdev_पूर्णांकr_cmd(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	काष्ठा dio200_subdev_पूर्णांकr *subpriv = s->निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&subpriv->spinlock, flags);

	subpriv->active = true;

	अगर (cmd->start_src == TRIG_INT)
		s->async->पूर्णांकtrig = dio200_पूर्णांकtrig_start_पूर्णांकr;
	अन्यथा	/* TRIG_NOW */
		dio200_start_पूर्णांकr(dev, s);

	spin_unlock_irqrestore(&subpriv->spinlock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक dio200_subdev_पूर्णांकr_init(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   अचिन्हित पूर्णांक offset,
				   अचिन्हित पूर्णांक valid_isns)
अणु
	स्थिर काष्ठा dio200_board *board = dev->board_ptr;
	काष्ठा dio200_subdev_पूर्णांकr *subpriv;

	subpriv = comedi_alloc_spriv(s, माप(*subpriv));
	अगर (!subpriv)
		वापस -ENOMEM;

	subpriv->ofs = offset;
	subpriv->valid_isns = valid_isns;
	spin_lock_init(&subpriv->spinlock);

	अगर (board->has_पूर्णांक_sce)
		/* Disable पूर्णांकerrupt sources. */
		dio200_ग_लिखो8(dev, subpriv->ofs, 0);

	s->type = COMEDI_SUBD_DI;
	s->subdev_flags = SDF_READABLE | SDF_CMD_READ | SDF_PACKED;
	अगर (board->has_पूर्णांक_sce) अणु
		s->n_chan = DIO200_MAX_ISNS;
		s->len_chanlist = DIO200_MAX_ISNS;
	पूर्ण अन्यथा अणु
		/* No पूर्णांकerrupt source रेजिस्टर.  Support single channel. */
		s->n_chan = 1;
		s->len_chanlist = 1;
	पूर्ण
	s->range_table = &range_digital;
	s->maxdata = 1;
	s->insn_bits = dio200_subdev_पूर्णांकr_insn_bits;
	s->करो_cmdtest = dio200_subdev_पूर्णांकr_cmdtest;
	s->करो_cmd = dio200_subdev_पूर्णांकr_cmd;
	s->cancel = dio200_subdev_पूर्णांकr_cancel;

	वापस 0;
पूर्ण

अटल irqवापस_t dio200_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	पूर्णांक handled;

	अगर (!dev->attached)
		वापस IRQ_NONE;

	handled = dio200_handle_पढ़ो_पूर्णांकr(dev, s);

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम dio200_subdev_8254_set_gate_src(काष्ठा comedi_device *dev,
					    काष्ठा comedi_subdevice *s,
					    अचिन्हित पूर्णांक chan,
					    अचिन्हित पूर्णांक src)
अणु
	अचिन्हित पूर्णांक offset = dio200_subdev_8254_offset(dev, s);

	dio200_ग_लिखो8(dev, DIO200_GAT_SCE(offset >> 3),
		      clk_gat_sce((offset >> 2) & 1, chan, src));
पूर्ण

अटल व्योम dio200_subdev_8254_set_घड़ी_src(काष्ठा comedi_device *dev,
					     काष्ठा comedi_subdevice *s,
					     अचिन्हित पूर्णांक chan,
					     अचिन्हित पूर्णांक src)
अणु
	अचिन्हित पूर्णांक offset = dio200_subdev_8254_offset(dev, s);

	dio200_ग_लिखो8(dev, DIO200_CLK_SCE(offset >> 3),
		      clk_gat_sce((offset >> 2) & 1, chan, src));
पूर्ण

अटल पूर्णांक dio200_subdev_8254_config(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     काष्ठा comedi_insn *insn,
				     अचिन्हित पूर्णांक *data)
अणु
	स्थिर काष्ठा dio200_board *board = dev->board_ptr;
	काष्ठा comedi_8254 *i8254 = s->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक max_src = board->is_pcie ? 31 : 7;
	अचिन्हित पूर्णांक src;

	अगर (!board->has_clk_gat_sce)
		वापस -EINVAL;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_SET_GATE_SRC:
		src = data[2];
		अगर (src > max_src)
			वापस -EINVAL;

		dio200_subdev_8254_set_gate_src(dev, s, chan, src);
		i8254->gate_src[chan] = src;
		अवरोध;
	हाल INSN_CONFIG_GET_GATE_SRC:
		data[2] = i8254->gate_src[chan];
		अवरोध;
	हाल INSN_CONFIG_SET_CLOCK_SRC:
		src = data[1];
		अगर (src > max_src)
			वापस -EINVAL;

		dio200_subdev_8254_set_घड़ी_src(dev, s, chan, src);
		i8254->घड़ी_src[chan] = src;
		अवरोध;
	हाल INSN_CONFIG_GET_CLOCK_SRC:
		data[1] = i8254->घड़ी_src[chan];
		data[2] = घड़ी_period[i8254->घड़ी_src[chan]];
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक dio200_subdev_8254_init(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   अचिन्हित पूर्णांक offset)
अणु
	स्थिर काष्ठा dio200_board *board = dev->board_ptr;
	काष्ठा comedi_8254 *i8254;
	अचिन्हित पूर्णांक regshअगरt;
	पूर्णांक chan;

	/*
	 * PCIe boards need the offset shअगरted in order to get the
	 * correct base address of the समयr.
	 */
	अगर (board->is_pcie) अणु
		offset <<= 3;
		regshअगरt = 3;
	पूर्ण अन्यथा अणु
		regshअगरt = 0;
	पूर्ण

	अगर (dev->mmio) अणु
		i8254 = comedi_8254_mm_init(dev->mmio + offset,
					    0, I8254_IO8, regshअगरt);
	पूर्ण अन्यथा अणु
		i8254 = comedi_8254_init(dev->iobase + offset,
					 0, I8254_IO8, regshअगरt);
	पूर्ण
	अगर (!i8254)
		वापस -ENOMEM;

	comedi_8254_subdevice_init(s, i8254);

	i8254->insn_config = dio200_subdev_8254_config;

	/*
	 * There could be multiple समयrs so this driver करोes not
	 * use dev->pacer to save the i8254 poपूर्णांकer. Instead,
	 * comedi_8254_subdevice_init() saved the i8254 poपूर्णांकer in
	 * s->निजी.  Mark the subdevice as having निजी data
	 * to be स्वतःmatically मुक्तd when the device is detached.
	 */
	comedi_set_spriv_स्वतः_मुक्त(s);

	/* Initialize channels. */
	अगर (board->has_clk_gat_sce) अणु
		क्रम (chan = 0; chan < 3; chan++) अणु
			/* Gate source 0 is VCC (logic 1). */
			dio200_subdev_8254_set_gate_src(dev, s, chan, 0);
			/* Clock source 0 is the dedicated घड़ी input. */
			dio200_subdev_8254_set_घड़ी_src(dev, s, chan, 0);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dio200_subdev_8255_set_dir(काष्ठा comedi_device *dev,
				       काष्ठा comedi_subdevice *s)
अणु
	काष्ठा dio200_subdev_8255 *subpriv = s->निजी;
	पूर्णांक config;

	config = I8255_CTRL_CW;
	/* 1 in io_bits indicates output, 1 in config indicates input */
	अगर (!(s->io_bits & 0x0000ff))
		config |= I8255_CTRL_A_IO;
	अगर (!(s->io_bits & 0x00ff00))
		config |= I8255_CTRL_B_IO;
	अगर (!(s->io_bits & 0x0f0000))
		config |= I8255_CTRL_C_LO_IO;
	अगर (!(s->io_bits & 0xf00000))
		config |= I8255_CTRL_C_HI_IO;
	dio200_ग_लिखो8(dev, subpriv->ofs + I8255_CTRL_REG, config);
पूर्ण

अटल पूर्णांक dio200_subdev_8255_bits(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	काष्ठा dio200_subdev_8255 *subpriv = s->निजी;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक val;

	mask = comedi_dio_update_state(s, data);
	अगर (mask) अणु
		अगर (mask & 0xff) अणु
			dio200_ग_लिखो8(dev, subpriv->ofs + I8255_DATA_A_REG,
				      s->state & 0xff);
		पूर्ण
		अगर (mask & 0xff00) अणु
			dio200_ग_लिखो8(dev, subpriv->ofs + I8255_DATA_B_REG,
				      (s->state >> 8) & 0xff);
		पूर्ण
		अगर (mask & 0xff0000) अणु
			dio200_ग_लिखो8(dev, subpriv->ofs + I8255_DATA_C_REG,
				      (s->state >> 16) & 0xff);
		पूर्ण
	पूर्ण

	val = dio200_पढ़ो8(dev, subpriv->ofs + I8255_DATA_A_REG);
	val |= dio200_पढ़ो8(dev, subpriv->ofs + I8255_DATA_B_REG) << 8;
	val |= dio200_पढ़ो8(dev, subpriv->ofs + I8255_DATA_C_REG) << 16;

	data[1] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक dio200_subdev_8255_config(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     काष्ठा comedi_insn *insn,
				     अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक mask;
	पूर्णांक ret;

	अगर (chan < 8)
		mask = 0x0000ff;
	अन्यथा अगर (chan < 16)
		mask = 0x00ff00;
	अन्यथा अगर (chan < 20)
		mask = 0x0f0000;
	अन्यथा
		mask = 0xf00000;

	ret = comedi_dio_insn_config(dev, s, insn, data, mask);
	अगर (ret)
		वापस ret;

	dio200_subdev_8255_set_dir(dev, s);

	वापस insn->n;
पूर्ण

अटल पूर्णांक dio200_subdev_8255_init(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   अचिन्हित पूर्णांक offset)
अणु
	काष्ठा dio200_subdev_8255 *subpriv;

	subpriv = comedi_alloc_spriv(s, माप(*subpriv));
	अगर (!subpriv)
		वापस -ENOMEM;

	subpriv->ofs = offset;

	s->type = COMEDI_SUBD_DIO;
	s->subdev_flags = SDF_READABLE | SDF_WRITABLE;
	s->n_chan = 24;
	s->range_table = &range_digital;
	s->maxdata = 1;
	s->insn_bits = dio200_subdev_8255_bits;
	s->insn_config = dio200_subdev_8255_config;
	dio200_subdev_8255_set_dir(dev, s);
	वापस 0;
पूर्ण

अटल पूर्णांक dio200_subdev_समयr_पढ़ो(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_insn *insn,
				    अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक n;

	क्रम (n = 0; n < insn->n; n++)
		data[n] = dio200_पढ़ो32(dev, DIO200_TS_COUNT);
	वापस n;
पूर्ण

अटल व्योम dio200_subdev_समयr_reset(काष्ठा comedi_device *dev,
				      काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित पूर्णांक घड़ी;

	घड़ी = dio200_पढ़ो32(dev, DIO200_TS_CONFIG) & TS_CONFIG_CLK_SRC_MASK;
	dio200_ग_लिखो32(dev, DIO200_TS_CONFIG, घड़ी | TS_CONFIG_RESET);
	dio200_ग_लिखो32(dev, DIO200_TS_CONFIG, घड़ी);
पूर्ण

अटल व्योम dio200_subdev_समयr_get_घड़ी_src(काष्ठा comedi_device *dev,
					      काष्ठा comedi_subdevice *s,
					      अचिन्हित पूर्णांक *src,
					      अचिन्हित पूर्णांक *period)
अणु
	अचिन्हित पूर्णांक clk;

	clk = dio200_पढ़ो32(dev, DIO200_TS_CONFIG) & TS_CONFIG_CLK_SRC_MASK;
	*src = clk;
	*period = (clk < ARRAY_SIZE(ts_घड़ी_period)) ?
		  ts_घड़ी_period[clk] : 0;
पूर्ण

अटल पूर्णांक dio200_subdev_समयr_set_घड़ी_src(काष्ठा comedi_device *dev,
					     काष्ठा comedi_subdevice *s,
					     अचिन्हित पूर्णांक src)
अणु
	अगर (src > TS_CONFIG_MAX_CLK_SRC)
		वापस -EINVAL;
	dio200_ग_लिखो32(dev, DIO200_TS_CONFIG, src);
	वापस 0;
पूर्ण

अटल पूर्णांक dio200_subdev_समयr_config(काष्ठा comedi_device *dev,
				      काष्ठा comedi_subdevice *s,
				      काष्ठा comedi_insn *insn,
				      अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक ret = 0;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_RESET:
		dio200_subdev_समयr_reset(dev, s);
		अवरोध;
	हाल INSN_CONFIG_SET_CLOCK_SRC:
		ret = dio200_subdev_समयr_set_घड़ी_src(dev, s, data[1]);
		अगर (ret < 0)
			ret = -EINVAL;
		अवरोध;
	हाल INSN_CONFIG_GET_CLOCK_SRC:
		dio200_subdev_समयr_get_घड़ी_src(dev, s, &data[1], &data[2]);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret < 0 ? ret : insn->n;
पूर्ण

व्योम amplc_dio200_set_enhance(काष्ठा comedi_device *dev, अचिन्हित अक्षर val)
अणु
	dio200_ग_लिखो8(dev, DIO200_ENHANCE, val);
पूर्ण
EXPORT_SYMBOL_GPL(amplc_dio200_set_enhance);

पूर्णांक amplc_dio200_common_attach(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक irq,
			       अचिन्हित दीर्घ req_irq_flags)
अणु
	स्थिर काष्ठा dio200_board *board = dev->board_ptr;
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक n;
	पूर्णांक ret;

	ret = comedi_alloc_subdevices(dev, board->n_subdevs);
	अगर (ret)
		वापस ret;

	क्रम (n = 0; n < dev->n_subdevices; n++) अणु
		s = &dev->subdevices[n];
		चयन (board->sdtype[n]) अणु
		हाल sd_8254:
			/* counter subdevice (8254) */
			ret = dio200_subdev_8254_init(dev, s,
						      board->sdinfo[n]);
			अगर (ret < 0)
				वापस ret;
			अवरोध;
		हाल sd_8255:
			/* digital i/o subdevice (8255) */
			ret = dio200_subdev_8255_init(dev, s,
						      board->sdinfo[n]);
			अगर (ret < 0)
				वापस ret;
			अवरोध;
		हाल sd_पूर्णांकr:
			/* 'INTERRUPT' subdevice */
			अगर (irq && !dev->पढ़ो_subdev) अणु
				ret = dio200_subdev_पूर्णांकr_init(dev, s,
							      DIO200_INT_SCE,
							      board->sdinfo[n]);
				अगर (ret < 0)
					वापस ret;
				dev->पढ़ो_subdev = s;
			पूर्ण अन्यथा अणु
				s->type = COMEDI_SUBD_UNUSED;
			पूर्ण
			अवरोध;
		हाल sd_समयr:
			s->type		= COMEDI_SUBD_TIMER;
			s->subdev_flags	= SDF_READABLE | SDF_LSAMPL;
			s->n_chan	= 1;
			s->maxdata	= 0xffffffff;
			s->insn_पढ़ो	= dio200_subdev_समयr_पढ़ो;
			s->insn_config	= dio200_subdev_समयr_config;
			अवरोध;
		शेष:
			s->type = COMEDI_SUBD_UNUSED;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (irq && dev->पढ़ो_subdev) अणु
		अगर (request_irq(irq, dio200_पूर्णांकerrupt, req_irq_flags,
				dev->board_name, dev) >= 0) अणु
			dev->irq = irq;
		पूर्ण अन्यथा अणु
			dev_warn(dev->class_dev,
				 "warning! irq %u unavailable!\n", irq);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(amplc_dio200_common_attach);

अटल पूर्णांक __init amplc_dio200_common_init(व्योम)
अणु
	वापस 0;
पूर्ण
module_init(amplc_dio200_common_init);

अटल व्योम __निकास amplc_dio200_common_निकास(व्योम)
अणु
पूर्ण
module_निकास(amplc_dio200_common_निकास);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi helper for amplc_dio200 and amplc_dio200_pci");
MODULE_LICENSE("GPL");
