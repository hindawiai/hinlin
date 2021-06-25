<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * adv_pci1710.c
 * Comedi driver क्रम Advantech PCI-1710 series boards
 * Author: Michal Dobes <करोbes@tesnet.cz>
 *
 * Thanks to ZhenGang Shang <ZhenGang.Shang@Advantech.com.cn>
 * क्रम testing and inक्रमmation.
 */

/*
 * Driver: adv_pci1710
 * Description: Comedi driver क्रम Advantech PCI-1710 series boards
 * Devices: [Advantech] PCI-1710 (adv_pci1710), PCI-1710HG, PCI-1711,
 *   PCI-1713, PCI-1731
 * Author: Michal Dobes <करोbes@tesnet.cz>
 * Updated: Fri, 29 Oct 2015 17:19:35 -0700
 * Status: works
 *
 * Configuration options: not applicable, uses PCI स्वतः config
 *
 * This driver supports AI, AO, DI and DO subdevices.
 * AI subdevice supports cmd and insn पूर्णांकerface,
 * other subdevices support only insn पूर्णांकerface.
 *
 * The PCI-1710 and PCI-1710HG have the same PCI device ID, so the
 * driver cannot distinguish between them, as would be normal क्रम a
 * PCI driver.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedi_pci.h"

#समावेश "comedi_8254.h"
#समावेश "amcc_s5933.h"

/*
 * PCI BAR2 Register map (dev->iobase)
 */
#घोषणा PCI171X_AD_DATA_REG	0x00	/* R:   A/D data */
#घोषणा PCI171X_SOFTTRG_REG	0x00	/* W:   soft trigger क्रम A/D */
#घोषणा PCI171X_RANGE_REG	0x02	/* W:   A/D gain/range रेजिस्टर */
#घोषणा PCI171X_RANGE_DIFF	BIT(5)
#घोषणा PCI171X_RANGE_UNI	BIT(4)
#घोषणा PCI171X_RANGE_GAIN(x)	(((x) & 0x7) << 0)
#घोषणा PCI171X_MUX_REG		0x04	/* W:   A/D multiplexor control */
#घोषणा PCI171X_MUX_CHANH(x)	(((x) & 0xff) << 8)
#घोषणा PCI171X_MUX_CHANL(x)	(((x) & 0xff) << 0)
#घोषणा PCI171X_MUX_CHAN(x)	(PCI171X_MUX_CHANH(x) | PCI171X_MUX_CHANL(x))
#घोषणा PCI171X_STATUS_REG	0x06	/* R:   status रेजिस्टर */
#घोषणा PCI171X_STATUS_IRQ	BIT(11)	/* 1=IRQ occurred */
#घोषणा PCI171X_STATUS_FF	BIT(10)	/* 1=FIFO is full, fatal error */
#घोषणा PCI171X_STATUS_FH	BIT(9)	/* 1=FIFO is half full */
#घोषणा PCI171X_STATUS_FE	BIT(8)	/* 1=FIFO is empty */
#घोषणा PCI171X_CTRL_REG	0x06	/* W:   control रेजिस्टर */
#घोषणा PCI171X_CTRL_CNT0	BIT(6)	/* 1=ext. clk, 0=पूर्णांक. 100kHz clk */
#घोषणा PCI171X_CTRL_ONEFH	BIT(5)	/* 1=on FIFO half full, 0=on sample */
#घोषणा PCI171X_CTRL_IRQEN	BIT(4)	/* 1=enable IRQ */
#घोषणा PCI171X_CTRL_GATE	BIT(3)	/* 1=enable ext. trigger GATE (8254?) */
#घोषणा PCI171X_CTRL_EXT	BIT(2)	/* 1=enable ext. trigger source */
#घोषणा PCI171X_CTRL_PACER	BIT(1)	/* 1=enable पूर्णांक. 8254 trigger source */
#घोषणा PCI171X_CTRL_SW		BIT(0)	/* 1=enable software trigger source */
#घोषणा PCI171X_CLRINT_REG	0x08	/* W:   clear पूर्णांकerrupts request */
#घोषणा PCI171X_CLRFIFO_REG	0x09	/* W:   clear FIFO */
#घोषणा PCI171X_DA_REG(x)	(0x0a + ((x) * 2)) /* W:   D/A रेजिस्टर */
#घोषणा PCI171X_DAREF_REG	0x0e	/* W:   D/A reference control */
#घोषणा PCI171X_DAREF(c, r)	(((r) & 0x3) << ((c) * 2))
#घोषणा PCI171X_DAREF_MASK(c)	PCI171X_DAREF((c), 0x3)
#घोषणा PCI171X_DI_REG		0x10	/* R:   digital inमाला_दो */
#घोषणा PCI171X_DO_REG		0x10	/* W:   digital outमाला_दो */
#घोषणा PCI171X_TIMER_BASE	0x18	/* R/W: 8254 समयr */

अटल स्थिर काष्ठा comedi_lrange pci1710_ai_range = अणु
	9, अणु
		BIP_RANGE(5),		/* gain 1   (0x00) */
		BIP_RANGE(2.5),		/* gain 2   (0x01) */
		BIP_RANGE(1.25),	/* gain 4   (0x02) */
		BIP_RANGE(0.625),	/* gain 8   (0x03) */
		BIP_RANGE(10),		/* gain 0.5 (0x04) */
		UNI_RANGE(10),		/* gain 1   (0x00 | UNI) */
		UNI_RANGE(5),		/* gain 2   (0x01 | UNI) */
		UNI_RANGE(2.5),		/* gain 4   (0x02 | UNI) */
		UNI_RANGE(1.25)		/* gain 8   (0x03 | UNI) */
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange pci1710hg_ai_range = अणु
	12, अणु
		BIP_RANGE(5),		/* gain 1    (0x00) */
		BIP_RANGE(0.5),		/* gain 10   (0x01) */
		BIP_RANGE(0.05),	/* gain 100  (0x02) */
		BIP_RANGE(0.005),	/* gain 1000 (0x03) */
		BIP_RANGE(10),		/* gain 0.5  (0x04) */
		BIP_RANGE(1),		/* gain 5    (0x05) */
		BIP_RANGE(0.1),		/* gain 50   (0x06) */
		BIP_RANGE(0.01),	/* gain 500  (0x07) */
		UNI_RANGE(10),		/* gain 1    (0x00 | UNI) */
		UNI_RANGE(1),		/* gain 10   (0x01 | UNI) */
		UNI_RANGE(0.1),		/* gain 100  (0x02 | UNI) */
		UNI_RANGE(0.01)		/* gain 1000 (0x03 | UNI) */
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange pci1711_ai_range = अणु
	5, अणु
		BIP_RANGE(10),		/* gain 1  (0x00) */
		BIP_RANGE(5),		/* gain 2  (0x01) */
		BIP_RANGE(2.5),		/* gain 4  (0x02) */
		BIP_RANGE(1.25),	/* gain 8  (0x03) */
		BIP_RANGE(0.625)	/* gain 16 (0x04) */
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange pci171x_ao_range = अणु
	3, अणु
		UNI_RANGE(5),		/* पूर्णांकernal -5V ref */
		UNI_RANGE(10),		/* पूर्णांकernal -10V ref */
		RANGE_ext(0, 1)		/* बाह्यal -Vref (+/-10V max) */
	पूर्ण
पूर्ण;

क्रमागत pci1710_boardid अणु
	BOARD_PCI1710,
	BOARD_PCI1710HG,
	BOARD_PCI1711,
	BOARD_PCI1713,
	BOARD_PCI1731,
पूर्ण;

काष्ठा boardtype अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा comedi_lrange *ai_range;
	अचिन्हित पूर्णांक is_pci1711:1;
	अचिन्हित पूर्णांक is_pci1713:1;
	अचिन्हित पूर्णांक has_ao:1;
पूर्ण;

अटल स्थिर काष्ठा boardtype boardtypes[] = अणु
	[BOARD_PCI1710] = अणु
		.name		= "pci1710",
		.ai_range	= &pci1710_ai_range,
		.has_ao		= 1,
	पूर्ण,
	[BOARD_PCI1710HG] = अणु
		.name		= "pci1710hg",
		.ai_range	= &pci1710hg_ai_range,
		.has_ao		= 1,
	पूर्ण,
	[BOARD_PCI1711] = अणु
		.name		= "pci1711",
		.ai_range	= &pci1711_ai_range,
		.is_pci1711	= 1,
		.has_ao		= 1,
	पूर्ण,
	[BOARD_PCI1713] = अणु
		.name		= "pci1713",
		.ai_range	= &pci1710_ai_range,
		.is_pci1713	= 1,
	पूर्ण,
	[BOARD_PCI1731] = अणु
		.name		= "pci1731",
		.ai_range	= &pci1711_ai_range,
		.is_pci1711	= 1,
	पूर्ण,
पूर्ण;

काष्ठा pci1710_निजी अणु
	अचिन्हित पूर्णांक max_samples;
	अचिन्हित पूर्णांक ctrl;	/* control रेजिस्टर value */
	अचिन्हित पूर्णांक ctrl_ext;	/* used to चयन from TRIG_EXT to TRIG_xxx */
	अचिन्हित पूर्णांक mux_scan;	/* used to set the channel पूर्णांकerval to scan */
	अचिन्हित अक्षर ai_et;
	अचिन्हित पूर्णांक act_chanlist[32];	/*  list of scanned channel */
	अचिन्हित अक्षर saved_seglen;	/* len of the non-repeating chanlist */
	अचिन्हित अक्षर da_ranges;	/*  copy of D/A outpit range रेजिस्टर */
	अचिन्हित अक्षर unipolar_gain;	/* adjust क्रम unipolar gain codes */
पूर्ण;

अटल पूर्णांक pci1710_ai_check_chanlist(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा pci1710_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan0 = CR_CHAN(cmd->chanlist[0]);
	अचिन्हित पूर्णांक last_aref = CR_AREF(cmd->chanlist[0]);
	अचिन्हित पूर्णांक next_chan = (chan0 + 1) % s->n_chan;
	अचिन्हित पूर्णांक chansegment[32];
	अचिन्हित पूर्णांक seglen;
	पूर्णांक i;

	अगर (cmd->chanlist_len == 1) अणु
		devpriv->saved_seglen = cmd->chanlist_len;
		वापस 0;
	पूर्ण

	/* first channel is always ok */
	chansegment[0] = cmd->chanlist[0];

	क्रम (i = 1; i < cmd->chanlist_len; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);
		अचिन्हित पूर्णांक aref = CR_AREF(cmd->chanlist[i]);

		अगर (cmd->chanlist[0] == cmd->chanlist[i])
			अवरोध;	/*  we detected a loop, stop */

		अगर (aref == AREF_DIFF && (chan & 1)) अणु
			dev_err(dev->class_dev,
				"Odd channel cannot be differential input!\n");
			वापस -EINVAL;
		पूर्ण

		अगर (last_aref == AREF_DIFF)
			next_chan = (next_chan + 1) % s->n_chan;
		अगर (chan != next_chan) अणु
			dev_err(dev->class_dev,
				"channel list must be continuous! chanlist[%i]=%d but must be %d or %d!\n",
				i, chan, next_chan, chan0);
			वापस -EINVAL;
		पूर्ण

		/* next correct channel in list */
		chansegment[i] = cmd->chanlist[i];
		last_aref = aref;
	पूर्ण
	seglen = i;

	क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
		अगर (cmd->chanlist[i] != chansegment[i % seglen]) अणु
			dev_err(dev->class_dev,
				"bad channel, reference or range number! chanlist[%i]=%d,%d,%d and not %d,%d,%d!\n",
				i, CR_CHAN(chansegment[i]),
				CR_RANGE(chansegment[i]),
				CR_AREF(chansegment[i]),
				CR_CHAN(cmd->chanlist[i % seglen]),
				CR_RANGE(cmd->chanlist[i % seglen]),
				CR_AREF(chansegment[i % seglen]));
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	devpriv->saved_seglen = seglen;

	वापस 0;
पूर्ण

अटल व्योम pci1710_ai_setup_chanlist(काष्ठा comedi_device *dev,
				      काष्ठा comedi_subdevice *s,
				      अचिन्हित पूर्णांक *chanlist,
				      अचिन्हित पूर्णांक n_chan,
				      अचिन्हित पूर्णांक seglen)
अणु
	काष्ठा pci1710_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक first_chan = CR_CHAN(chanlist[0]);
	अचिन्हित पूर्णांक last_chan = CR_CHAN(chanlist[seglen - 1]);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < seglen; i++) अणु	/*  store range list to card */
		अचिन्हित पूर्णांक chan = CR_CHAN(chanlist[i]);
		अचिन्हित पूर्णांक range = CR_RANGE(chanlist[i]);
		अचिन्हित पूर्णांक aref = CR_AREF(chanlist[i]);
		अचिन्हित पूर्णांक rangeval = 0;

		अगर (aref == AREF_DIFF)
			rangeval |= PCI171X_RANGE_DIFF;
		अगर (comedi_range_is_unipolar(s, range)) अणु
			rangeval |= PCI171X_RANGE_UNI;
			range -= devpriv->unipolar_gain;
		पूर्ण
		rangeval |= PCI171X_RANGE_GAIN(range);

		/* select channel and set range */
		outw(PCI171X_MUX_CHAN(chan), dev->iobase + PCI171X_MUX_REG);
		outw(rangeval, dev->iobase + PCI171X_RANGE_REG);

		devpriv->act_chanlist[i] = chan;
	पूर्ण
	क्रम ( ; i < n_chan; i++)	/* store reमुख्यder of channel list */
		devpriv->act_chanlist[i] = CR_CHAN(chanlist[i]);

	/* select channel पूर्णांकerval to scan */
	devpriv->mux_scan = PCI171X_MUX_CHANL(first_chan) |
			    PCI171X_MUX_CHANH(last_chan);
	outw(devpriv->mux_scan, dev->iobase + PCI171X_MUX_REG);
पूर्ण

अटल पूर्णांक pci1710_ai_eoc(काष्ठा comedi_device *dev,
			  काष्ठा comedi_subdevice *s,
			  काष्ठा comedi_insn *insn,
			  अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inw(dev->iobase + PCI171X_STATUS_REG);
	अगर ((status & PCI171X_STATUS_FE) == 0)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक pci1710_ai_पढ़ो_sample(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  अचिन्हित पूर्णांक cur_chan,
				  अचिन्हित लघु *val)
अणु
	स्थिर काष्ठा boardtype *board = dev->board_ptr;
	काष्ठा pci1710_निजी *devpriv = dev->निजी;
	अचिन्हित लघु sample;
	अचिन्हित पूर्णांक chan;

	sample = inw(dev->iobase + PCI171X_AD_DATA_REG);
	अगर (!board->is_pci1713) अणु
		/*
		 * The upper 4 bits of the 16-bit sample are the channel number
		 * that the sample was acquired from. Verअगरy that this channel
		 * number matches the expected channel number.
		 */
		chan = sample >> 12;
		अगर (chan != devpriv->act_chanlist[cur_chan]) अणु
			dev_err(dev->class_dev,
				"A/D data dropout: received from channel %d, expected %d\n",
				chan, devpriv->act_chanlist[cur_chan]);
			वापस -ENODATA;
		पूर्ण
	पूर्ण
	*val = sample & s->maxdata;
	वापस 0;
पूर्ण

अटल पूर्णांक pci1710_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	काष्ठा pci1710_निजी *devpriv = dev->निजी;
	पूर्णांक ret = 0;
	पूर्णांक i;

	/* enable software trigger */
	devpriv->ctrl |= PCI171X_CTRL_SW;
	outw(devpriv->ctrl, dev->iobase + PCI171X_CTRL_REG);

	outb(0, dev->iobase + PCI171X_CLRFIFO_REG);
	outb(0, dev->iobase + PCI171X_CLRINT_REG);

	pci1710_ai_setup_chanlist(dev, s, &insn->chanspec, 1, 1);

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित लघु val;

		/* start conversion */
		outw(0, dev->iobase + PCI171X_SOFTTRG_REG);

		ret = comedi_समयout(dev, s, insn, pci1710_ai_eoc, 0);
		अगर (ret)
			अवरोध;

		ret = pci1710_ai_पढ़ो_sample(dev, s, 0, &val);
		अगर (ret)
			अवरोध;

		data[i] = val;
	पूर्ण

	/* disable software trigger */
	devpriv->ctrl &= ~PCI171X_CTRL_SW;
	outw(devpriv->ctrl, dev->iobase + PCI171X_CTRL_REG);

	outb(0, dev->iobase + PCI171X_CLRFIFO_REG);
	outb(0, dev->iobase + PCI171X_CLRINT_REG);

	वापस ret ? ret : insn->n;
पूर्ण

अटल पूर्णांक pci1710_ai_cancel(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci1710_निजी *devpriv = dev->निजी;

	/* disable A/D triggers and पूर्णांकerrupt sources */
	devpriv->ctrl &= PCI171X_CTRL_CNT0;	/* preserve counter 0 clk src */
	outw(devpriv->ctrl, dev->iobase + PCI171X_CTRL_REG);

	/* disable pacer */
	comedi_8254_pacer_enable(dev->pacer, 1, 2, false);

	/* clear A/D FIFO and any pending पूर्णांकerrutps */
	outb(0, dev->iobase + PCI171X_CLRFIFO_REG);
	outb(0, dev->iobase + PCI171X_CLRINT_REG);

	वापस 0;
पूर्ण

अटल व्योम pci1710_handle_every_sample(काष्ठा comedi_device *dev,
					काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक status;
	अचिन्हित लघु val;
	पूर्णांक ret;

	status = inw(dev->iobase + PCI171X_STATUS_REG);
	अगर (status & PCI171X_STATUS_FE) अणु
		dev_dbg(dev->class_dev, "A/D FIFO empty (%4x)\n", status);
		s->async->events |= COMEDI_CB_ERROR;
		वापस;
	पूर्ण
	अगर (status & PCI171X_STATUS_FF) अणु
		dev_dbg(dev->class_dev,
			"A/D FIFO Full status (Fatal Error!) (%4x)\n", status);
		s->async->events |= COMEDI_CB_ERROR;
		वापस;
	पूर्ण

	outb(0, dev->iobase + PCI171X_CLRINT_REG);

	क्रम (; !(inw(dev->iobase + PCI171X_STATUS_REG) & PCI171X_STATUS_FE);) अणु
		ret = pci1710_ai_पढ़ो_sample(dev, s, s->async->cur_chan, &val);
		अगर (ret) अणु
			s->async->events |= COMEDI_CB_ERROR;
			अवरोध;
		पूर्ण

		comedi_buf_ग_लिखो_samples(s, &val, 1);

		अगर (cmd->stop_src == TRIG_COUNT &&
		    s->async->scans_करोne >= cmd->stop_arg) अणु
			s->async->events |= COMEDI_CB_EOA;
			अवरोध;
		पूर्ण
	पूर्ण

	outb(0, dev->iobase + PCI171X_CLRINT_REG);
पूर्ण

अटल व्योम pci1710_handle_fअगरo(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci1710_निजी *devpriv = dev->निजी;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित पूर्णांक status;
	पूर्णांक i;

	status = inw(dev->iobase + PCI171X_STATUS_REG);
	अगर (!(status & PCI171X_STATUS_FH)) अणु
		dev_dbg(dev->class_dev, "A/D FIFO not half full!\n");
		async->events |= COMEDI_CB_ERROR;
		वापस;
	पूर्ण
	अगर (status & PCI171X_STATUS_FF) अणु
		dev_dbg(dev->class_dev,
			"A/D FIFO Full status (Fatal Error!)\n");
		async->events |= COMEDI_CB_ERROR;
		वापस;
	पूर्ण

	क्रम (i = 0; i < devpriv->max_samples; i++) अणु
		अचिन्हित लघु val;
		पूर्णांक ret;

		ret = pci1710_ai_पढ़ो_sample(dev, s, s->async->cur_chan, &val);
		अगर (ret) अणु
			s->async->events |= COMEDI_CB_ERROR;
			अवरोध;
		पूर्ण

		अगर (!comedi_buf_ग_लिखो_samples(s, &val, 1))
			अवरोध;

		अगर (cmd->stop_src == TRIG_COUNT &&
		    async->scans_करोne >= cmd->stop_arg) अणु
			async->events |= COMEDI_CB_EOA;
			अवरोध;
		पूर्ण
	पूर्ण

	outb(0, dev->iobase + PCI171X_CLRINT_REG);
पूर्ण

अटल irqवापस_t pci1710_irq_handler(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा pci1710_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s;
	काष्ठा comedi_cmd *cmd;

	अगर (!dev->attached)	/*  is device attached? */
		वापस IRQ_NONE;	/*  no, निकास */

	s = dev->पढ़ो_subdev;
	cmd = &s->async->cmd;

	/*  is this पूर्णांकerrupt from our board? */
	अगर (!(inw(dev->iobase + PCI171X_STATUS_REG) & PCI171X_STATUS_IRQ))
		वापस IRQ_NONE;	/*  no, निकास */

	अगर (devpriv->ai_et) अणु	/*  Switch from initial TRIG_EXT to TRIG_xxx. */
		devpriv->ai_et = 0;
		devpriv->ctrl &= PCI171X_CTRL_CNT0;
		devpriv->ctrl |= PCI171X_CTRL_SW; /* set software trigger */
		outw(devpriv->ctrl, dev->iobase + PCI171X_CTRL_REG);
		devpriv->ctrl = devpriv->ctrl_ext;
		outb(0, dev->iobase + PCI171X_CLRFIFO_REG);
		outb(0, dev->iobase + PCI171X_CLRINT_REG);
		/* no sample on this पूर्णांकerrupt; reset the channel पूर्णांकerval */
		outw(devpriv->mux_scan, dev->iobase + PCI171X_MUX_REG);
		outw(devpriv->ctrl, dev->iobase + PCI171X_CTRL_REG);
		comedi_8254_pacer_enable(dev->pacer, 1, 2, true);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (cmd->flags & CMDF_WAKE_EOS)
		pci1710_handle_every_sample(dev, s);
	अन्यथा
		pci1710_handle_fअगरo(dev, s);

	comedi_handle_events(dev, s);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pci1710_ai_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci1710_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;

	pci1710_ai_setup_chanlist(dev, s, cmd->chanlist, cmd->chanlist_len,
				  devpriv->saved_seglen);

	outb(0, dev->iobase + PCI171X_CLRFIFO_REG);
	outb(0, dev->iobase + PCI171X_CLRINT_REG);

	devpriv->ctrl &= PCI171X_CTRL_CNT0;
	अगर ((cmd->flags & CMDF_WAKE_EOS) == 0)
		devpriv->ctrl |= PCI171X_CTRL_ONEFH;

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		comedi_8254_update_भागisors(dev->pacer);

		devpriv->ctrl |= PCI171X_CTRL_PACER | PCI171X_CTRL_IRQEN;
		अगर (cmd->start_src == TRIG_EXT) अणु
			devpriv->ctrl_ext = devpriv->ctrl;
			devpriv->ctrl &= ~(PCI171X_CTRL_PACER |
					   PCI171X_CTRL_ONEFH |
					   PCI171X_CTRL_GATE);
			devpriv->ctrl |= PCI171X_CTRL_EXT;
			devpriv->ai_et = 1;
		पूर्ण अन्यथा अणु	/* TRIG_NOW */
			devpriv->ai_et = 0;
		पूर्ण
		outw(devpriv->ctrl, dev->iobase + PCI171X_CTRL_REG);

		अगर (cmd->start_src == TRIG_NOW)
			comedi_8254_pacer_enable(dev->pacer, 1, 2, true);
	पूर्ण अन्यथा अणु	/* TRIG_EXT */
		devpriv->ctrl |= PCI171X_CTRL_EXT | PCI171X_CTRL_IRQEN;
		outw(devpriv->ctrl, dev->iobase + PCI171X_CTRL_REG);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pci1710_ai_cmdtest(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_FOLLOW);
	err |= comedi_check_trigger_src(&cmd->convert_src,
					TRIG_TIMER | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* step 2a: make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->convert_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* step 2b: and mutually compatible */

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);

	अगर (cmd->convert_src == TRIG_TIMER)
		err |= comedi_check_trigger_arg_min(&cmd->convert_arg, 10000);
	अन्यथा	/* TRIG_FOLLOW */
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

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		अचिन्हित पूर्णांक arg = cmd->convert_arg;

		comedi_8254_cascade_ns_to_समयr(dev->pacer, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg);
	पूर्ण

	अगर (err)
		वापस 4;

	/* Step 5: check channel list */

	err |= pci1710_ai_check_chanlist(dev, s, cmd);

	अगर (err)
		वापस 5;

	वापस 0;
पूर्ण

अटल पूर्णांक pci1710_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	काष्ठा pci1710_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	पूर्णांक i;

	devpriv->da_ranges &= ~PCI171X_DAREF_MASK(chan);
	devpriv->da_ranges |= PCI171X_DAREF(chan, range);
	outw(devpriv->da_ranges, dev->iobase + PCI171X_DAREF_REG);

	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];
		outw(val, dev->iobase + PCI171X_DA_REG(chan));
	पूर्ण

	s->पढ़ोback[chan] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci1710_di_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	data[1] = inw(dev->iobase + PCI171X_DI_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci1710_करो_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		outw(s->state, dev->iobase + PCI171X_DO_REG);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci1710_counter_insn_config(काष्ठा comedi_device *dev,
				       काष्ठा comedi_subdevice *s,
				       काष्ठा comedi_insn *insn,
				       अचिन्हित पूर्णांक *data)
अणु
	काष्ठा pci1710_निजी *devpriv = dev->निजी;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_SET_CLOCK_SRC:
		चयन (data[1]) अणु
		हाल 0:	/* पूर्णांकernal */
			devpriv->ctrl_ext &= ~PCI171X_CTRL_CNT0;
			अवरोध;
		हाल 1:	/* बाह्यal */
			devpriv->ctrl_ext |= PCI171X_CTRL_CNT0;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		outw(devpriv->ctrl_ext, dev->iobase + PCI171X_CTRL_REG);
		अवरोध;
	हाल INSN_CONFIG_GET_CLOCK_SRC:
		अगर (devpriv->ctrl_ext & PCI171X_CTRL_CNT0) अणु
			data[1] = 1;
			data[2] = 0;
		पूर्ण अन्यथा अणु
			data[1] = 0;
			data[2] = I8254_OSC_BASE_1MHZ;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल व्योम pci1710_reset(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा boardtype *board = dev->board_ptr;

	/*
	 * Disable A/D triggers and पूर्णांकerrupt sources, set counter 0
	 * to use पूर्णांकernal 1 MHz घड़ी.
	 */
	outw(0, dev->iobase + PCI171X_CTRL_REG);

	/* clear A/D FIFO and any pending पूर्णांकerrutps */
	outb(0, dev->iobase + PCI171X_CLRFIFO_REG);
	outb(0, dev->iobase + PCI171X_CLRINT_REG);

	अगर (board->has_ao) अणु
		/* set DACs to 0..5V and outमाला_दो to 0V */
		outb(0, dev->iobase + PCI171X_DAREF_REG);
		outw(0, dev->iobase + PCI171X_DA_REG(0));
		outw(0, dev->iobase + PCI171X_DA_REG(1));
	पूर्ण

	/* set digital outमाला_दो to 0 */
	outw(0, dev->iobase + PCI171X_DO_REG);
पूर्ण

अटल पूर्णांक pci1710_स्वतः_attach(काष्ठा comedi_device *dev,
			       अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा boardtype *board = शून्य;
	काष्ठा pci1710_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret, subdev, n_subdevices;
	पूर्णांक i;

	अगर (context < ARRAY_SIZE(boardtypes))
		board = &boardtypes[context];
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

	dev->pacer = comedi_8254_init(dev->iobase + PCI171X_TIMER_BASE,
				      I8254_OSC_BASE_10MHZ, I8254_IO16, 0);
	अगर (!dev->pacer)
		वापस -ENOMEM;

	n_subdevices = 1;	/* all boards have analog inमाला_दो */
	अगर (board->has_ao)
		n_subdevices++;
	अगर (!board->is_pci1713) अणु
		/*
		 * All other boards have digital inमाला_दो and outमाला_दो as
		 * well as a user counter.
		 */
		n_subdevices += 3;
	पूर्ण

	ret = comedi_alloc_subdevices(dev, n_subdevices);
	अगर (ret)
		वापस ret;

	pci1710_reset(dev);

	अगर (pcidev->irq) अणु
		ret = request_irq(pcidev->irq, pci1710_irq_handler,
				  IRQF_SHARED, dev->board_name, dev);
		अगर (ret == 0)
			dev->irq = pcidev->irq;
	पूर्ण

	subdev = 0;

	/* Analog Input subdevice */
	s = &dev->subdevices[subdev++];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_GROUND;
	अगर (!board->is_pci1711)
		s->subdev_flags	|= SDF_DIFF;
	s->n_chan	= board->is_pci1713 ? 32 : 16;
	s->maxdata	= 0x0fff;
	s->range_table	= board->ai_range;
	s->insn_पढ़ो	= pci1710_ai_insn_पढ़ो;
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->len_chanlist	= s->n_chan;
		s->करो_cmdtest	= pci1710_ai_cmdtest;
		s->करो_cmd	= pci1710_ai_cmd;
		s->cancel	= pci1710_ai_cancel;
	पूर्ण

	/* find the value needed to adjust क्रम unipolar gain codes */
	क्रम (i = 0; i < s->range_table->length; i++) अणु
		अगर (comedi_range_is_unipolar(s, i)) अणु
			devpriv->unipolar_gain = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (board->has_ao) अणु
		/* Analog Output subdevice */
		s = &dev->subdevices[subdev++];
		s->type		= COMEDI_SUBD_AO;
		s->subdev_flags	= SDF_WRITABLE | SDF_GROUND;
		s->n_chan	= 2;
		s->maxdata	= 0x0fff;
		s->range_table	= &pci171x_ao_range;
		s->insn_ग_लिखो	= pci1710_ao_insn_ग_लिखो;

		ret = comedi_alloc_subdev_पढ़ोback(s);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!board->is_pci1713) अणु
		/* Digital Input subdevice */
		s = &dev->subdevices[subdev++];
		s->type		= COMEDI_SUBD_DI;
		s->subdev_flags	= SDF_READABLE;
		s->n_chan	= 16;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_bits	= pci1710_di_insn_bits;

		/* Digital Output subdevice */
		s = &dev->subdevices[subdev++];
		s->type		= COMEDI_SUBD_DO;
		s->subdev_flags	= SDF_WRITABLE;
		s->n_chan	= 16;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_bits	= pci1710_करो_insn_bits;

		/* Counter subdevice (8254) */
		s = &dev->subdevices[subdev++];
		comedi_8254_subdevice_init(s, dev->pacer);

		dev->pacer->insn_config = pci1710_counter_insn_config;

		/* counters 1 and 2 are used पूर्णांकernally क्रम the pacer */
		comedi_8254_set_busy(dev->pacer, 1, true);
		comedi_8254_set_busy(dev->pacer, 2, true);
	पूर्ण

	/* max_samples is half the FIFO size (2 bytes/sample) */
	devpriv->max_samples = (board->is_pci1711) ? 512 : 2048;

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver adv_pci1710_driver = अणु
	.driver_name	= "adv_pci1710",
	.module		= THIS_MODULE,
	.स्वतः_attach	= pci1710_स्वतः_attach,
	.detach		= comedi_pci_detach,
पूर्ण;

अटल पूर्णांक adv_pci1710_pci_probe(काष्ठा pci_dev *dev,
				 स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &adv_pci1710_driver,
				      id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id adv_pci1710_pci_table[] = अणु
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADVANTECH, 0x1710,
			       PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9050),
		.driver_data = BOARD_PCI1710,
	पूर्ण, अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADVANTECH, 0x1710,
			       PCI_VENDOR_ID_ADVANTECH, 0x0000),
		.driver_data = BOARD_PCI1710,
	पूर्ण, अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADVANTECH, 0x1710,
			       PCI_VENDOR_ID_ADVANTECH, 0xb100),
		.driver_data = BOARD_PCI1710,
	पूर्ण, अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADVANTECH, 0x1710,
			       PCI_VENDOR_ID_ADVANTECH, 0xb200),
		.driver_data = BOARD_PCI1710,
	पूर्ण, अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADVANTECH, 0x1710,
			       PCI_VENDOR_ID_ADVANTECH, 0xc100),
		.driver_data = BOARD_PCI1710,
	पूर्ण, अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADVANTECH, 0x1710,
			       PCI_VENDOR_ID_ADVANTECH, 0xc200),
		.driver_data = BOARD_PCI1710,
	पूर्ण, अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADVANTECH, 0x1710, 0x1000, 0xd100),
		.driver_data = BOARD_PCI1710,
	पूर्ण, अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADVANTECH, 0x1710,
			       PCI_VENDOR_ID_ADVANTECH, 0x0002),
		.driver_data = BOARD_PCI1710HG,
	पूर्ण, अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADVANTECH, 0x1710,
			       PCI_VENDOR_ID_ADVANTECH, 0xb102),
		.driver_data = BOARD_PCI1710HG,
	पूर्ण, अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADVANTECH, 0x1710,
			       PCI_VENDOR_ID_ADVANTECH, 0xb202),
		.driver_data = BOARD_PCI1710HG,
	पूर्ण, अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADVANTECH, 0x1710,
			       PCI_VENDOR_ID_ADVANTECH, 0xc102),
		.driver_data = BOARD_PCI1710HG,
	पूर्ण, अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADVANTECH, 0x1710,
			       PCI_VENDOR_ID_ADVANTECH, 0xc202),
		.driver_data = BOARD_PCI1710HG,
	पूर्ण, अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_ADVANTECH, 0x1710, 0x1000, 0xd102),
		.driver_data = BOARD_PCI1710HG,
	पूर्ण,
	अणु PCI_VDEVICE(ADVANTECH, 0x1711), BOARD_PCI1711 पूर्ण,
	अणु PCI_VDEVICE(ADVANTECH, 0x1713), BOARD_PCI1713 पूर्ण,
	अणु PCI_VDEVICE(ADVANTECH, 0x1731), BOARD_PCI1731 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, adv_pci1710_pci_table);

अटल काष्ठा pci_driver adv_pci1710_pci_driver = अणु
	.name		= "adv_pci1710",
	.id_table	= adv_pci1710_pci_table,
	.probe		= adv_pci1710_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(adv_pci1710_driver, adv_pci1710_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi: Advantech PCI-1710 Series Multifunction DAS Cards");
MODULE_LICENSE("GPL");
