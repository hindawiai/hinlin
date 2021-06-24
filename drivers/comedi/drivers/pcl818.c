<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * comedi/drivers/pcl818.c
 *
 * Driver: pcl818
 * Description: Advantech PCL-818 cards, PCL-718
 * Author: Michal Dobes <करोbes@tesnet.cz>
 * Devices: [Advantech] PCL-818L (pcl818l), PCL-818H (pcl818h),
 *   PCL-818HD (pcl818hd), PCL-818HG (pcl818hg), PCL-818 (pcl818),
 *   PCL-718 (pcl718)
 * Status: works
 *
 * All cards have 16 SE/8 DIFF ADCs, one or two DACs, 16 DI and 16 DO.
 * Dअगरferences are only at maximal sample speed, range list and FIFO
 * support.
 * The driver support AI mode 0, 1, 3 other subdevices (AO, DI, DO) support
 * only mode 0. If DMA/FIFO/INT are disabled then AI support only mode 0.
 * PCL-818HD and PCL-818HG support 1kword FIFO. Driver support this FIFO
 * but this code is untested.
 * A word or two about DMA. Driver support DMA operations at two ways:
 * 1) DMA uses two buffers and after one is filled then is generated
 *    INT and DMA restart with second buffer. With this mode I'm unable run
 *    more that 80Ksamples/secs without data dropouts on K6/233.
 * 2) DMA uses one buffer and run in स्वतःinit mode and the data are
 *    from DMA buffer moved on the fly with 2kHz पूर्णांकerrupts from RTC.
 *    This mode is used अगर the पूर्णांकerrupt 8 is available क्रम allocation.
 *    If not, then first DMA mode is used. With this I can run at
 *    full speed one card (100ksamples/secs) or two cards with
 *    60ksamples/secs each (more is problem on account of ISA limitations).
 *    To use this mode you must have compiled  kernel with disabled
 *    "Enhanced Real Time Clock Support".
 *    Maybe you can have problems अगर you use xntpd or similar.
 *    If you've data dropouts with DMA mode 2 then:
 *     a) disable IDE DMA
 *     b) चयन text mode console to fb.
 *
 *  Options क्रम PCL-818L:
 *  [0] - IO Base
 *  [1] - IRQ        (0=disable, 2, 3, 4, 5, 6, 7)
 *  [2] - DMA        (0=disable, 1, 3)
 *  [3] - 0, 10=10MHz घड़ी क्रम 8254
 *            1= 1MHz घड़ी क्रम 8254
 *  [4] - 0,  5=A/D input  -5V.. +5V
 *        1, 10=A/D input -10V..+10V
 *  [5] - 0,  5=D/A output 0-5V  (पूर्णांकernal reference -5V)
 *        1, 10=D/A output 0-10V (पूर्णांकernal reference -10V)
 *        2    =D/A output unknown (बाह्यal reference)
 *
 *  Options क्रम PCL-818, PCL-818H:
 *  [0] - IO Base
 *  [1] - IRQ        (0=disable, 2, 3, 4, 5, 6, 7)
 *  [2] - DMA        (0=disable, 1, 3)
 *  [3] - 0, 10=10MHz घड़ी क्रम 8254
 *            1= 1MHz घड़ी क्रम 8254
 *  [4] - 0,  5=D/A output 0-5V  (पूर्णांकernal reference -5V)
 *        1, 10=D/A output 0-10V (पूर्णांकernal reference -10V)
 *        2    =D/A output unknown (बाह्यal reference)
 *
 *  Options क्रम PCL-818HD, PCL-818HG:
 *  [0] - IO Base
 *  [1] - IRQ        (0=disable, 2, 3, 4, 5, 6, 7)
 *  [2] - DMA/FIFO  (-1=use FIFO, 0=disable both FIFO and DMA,
 *                    1=use DMA ch 1, 3=use DMA ch 3)
 *  [3] - 0, 10=10MHz घड़ी क्रम 8254
 *            1= 1MHz घड़ी क्रम 8254
 *  [4] - 0,  5=D/A output 0-5V  (पूर्णांकernal reference -5V)
 *        1, 10=D/A output 0-10V (पूर्णांकernal reference -10V)
 *        2    =D/A output unknown (बाह्यal reference)
 *
 *  Options क्रम PCL-718:
 *  [0] - IO Base
 *  [1] - IRQ        (0=disable, 2, 3, 4, 5, 6, 7)
 *  [2] - DMA        (0=disable, 1, 3)
 *  [3] - 0, 10=10MHz घड़ी क्रम 8254
 *            1= 1MHz घड़ी क्रम 8254
 *  [4] -     0=A/D Range is +/-10V
 *            1=             +/-5V
 *            2=             +/-2.5V
 *            3=             +/-1V
 *            4=             +/-0.5V
 *            5=             user defined bipolar
 *            6=             0-10V
 *            7=             0-5V
 *            8=             0-2V
 *            9=             0-1V
 *           10=             user defined unipolar
 *  [5] - 0,  5=D/A outमाला_दो 0-5V  (पूर्णांकernal reference -5V)
 *        1, 10=D/A outमाला_दो 0-10V (पूर्णांकernal reference -10V)
 *            2=D/A outमाला_दो unknown (बाह्यal reference)
 *  [6] - 0, 60=max  60kHz A/D sampling
 *        1,100=max 100kHz A/D sampling (PCL-718 with Option 001 installed)
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/gfp.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedidev.h"

#समावेश "comedi_isadma.h"
#समावेश "comedi_8254.h"

/*
 * Register I/O map
 */
#घोषणा PCL818_AI_LSB_REG			0x00
#घोषणा PCL818_AI_MSB_REG			0x01
#घोषणा PCL818_RANGE_REG			0x01
#घोषणा PCL818_MUX_REG				0x02
#घोषणा PCL818_MUX_SCAN(_first, _last)		(((_last) << 4) | (_first))
#घोषणा PCL818_DO_DI_LSB_REG			0x03
#घोषणा PCL818_AO_LSB_REG(x)			(0x04 + ((x) * 2))
#घोषणा PCL818_AO_MSB_REG(x)			(0x05 + ((x) * 2))
#घोषणा PCL818_STATUS_REG			0x08
#घोषणा PCL818_STATUS_NEXT_CHAN_MASK		(0xf << 0)
#घोषणा PCL818_STATUS_INT			BIT(4)
#घोषणा PCL818_STATUS_MUX			BIT(5)
#घोषणा PCL818_STATUS_UNI			BIT(6)
#घोषणा PCL818_STATUS_EOC			BIT(7)
#घोषणा PCL818_CTRL_REG				0x09
#घोषणा PCL818_CTRL_TRIG(x)			(((x) & 0x3) << 0)
#घोषणा PCL818_CTRL_DISABLE_TRIG		PCL818_CTRL_TRIG(0)
#घोषणा PCL818_CTRL_SOFT_TRIG			PCL818_CTRL_TRIG(1)
#घोषणा PCL818_CTRL_EXT_TRIG			PCL818_CTRL_TRIG(2)
#घोषणा PCL818_CTRL_PACER_TRIG			PCL818_CTRL_TRIG(3)
#घोषणा PCL818_CTRL_DMAE			BIT(2)
#घोषणा PCL818_CTRL_IRQ(x)			((x) << 4)
#घोषणा PCL818_CTRL_INTE			BIT(7)
#घोषणा PCL818_CNTENABLE_REG			0x0a
#घोषणा PCL818_CNTENABLE_PACER_TRIG0		BIT(0)
#घोषणा PCL818_CNTENABLE_CNT0_INT_CLK		BIT(1)	/* 0=ext clk */
#घोषणा PCL818_DO_DI_MSB_REG			0x0b
#घोषणा PCL818_TIMER_BASE			0x0c

/* W: fअगरo enable/disable */
#घोषणा PCL818_FI_ENABLE 6
/* W: fअगरo पूर्णांकerrupt clear */
#घोषणा PCL818_FI_INTCLR 20
/* W: fअगरo पूर्णांकerrupt clear */
#घोषणा PCL818_FI_FLUSH 25
/* R: fअगरo status */
#घोषणा PCL818_FI_STATUS 25
/* R: one record from FIFO */
#घोषणा PCL818_FI_DATALO 23
#घोषणा PCL818_FI_DATAHI 24

#घोषणा MAGIC_DMA_WORD 0x5a5a

अटल स्थिर काष्ठा comedi_lrange range_pcl818h_ai = अणु
	9, अणु
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
		BIP_RANGE(0.625),
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2.5),
		UNI_RANGE(1.25),
		BIP_RANGE(10)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_pcl818hg_ai = अणु
	10, अणु
		BIP_RANGE(5),
		BIP_RANGE(0.5),
		BIP_RANGE(0.05),
		BIP_RANGE(0.005),
		UNI_RANGE(10),
		UNI_RANGE(1),
		UNI_RANGE(0.1),
		UNI_RANGE(0.01),
		BIP_RANGE(10),
		BIP_RANGE(1),
		BIP_RANGE(0.1),
		BIP_RANGE(0.01)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_pcl818l_l_ai = अणु
	4, अणु
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
		BIP_RANGE(0.625)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_pcl818l_h_ai = अणु
	4, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range718_bipolar1 = अणु
	1, अणु
		BIP_RANGE(1)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range718_bipolar0_5 = अणु
	1, अणु
		BIP_RANGE(0.5)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range718_unipolar2 = अणु
	1, अणु
		UNI_RANGE(2)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range718_unipolar1 = अणु
	1, अणु
		BIP_RANGE(1)
	पूर्ण
पूर्ण;

काष्ठा pcl818_board अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक ns_min;
	पूर्णांक n_aochan;
	स्थिर काष्ठा comedi_lrange *ai_range_type;
	अचिन्हित पूर्णांक has_dma:1;
	अचिन्हित पूर्णांक has_fअगरo:1;
	अचिन्हित पूर्णांक is_818:1;
पूर्ण;

अटल स्थिर काष्ठा pcl818_board boardtypes[] = अणु
	अणु
		.name		= "pcl818l",
		.ns_min		= 25000,
		.n_aochan	= 1,
		.ai_range_type	= &range_pcl818l_l_ai,
		.has_dma	= 1,
		.is_818		= 1,
	पूर्ण, अणु
		.name		= "pcl818h",
		.ns_min		= 10000,
		.n_aochan	= 1,
		.ai_range_type	= &range_pcl818h_ai,
		.has_dma	= 1,
		.is_818		= 1,
	पूर्ण, अणु
		.name		= "pcl818hd",
		.ns_min		= 10000,
		.n_aochan	= 1,
		.ai_range_type	= &range_pcl818h_ai,
		.has_dma	= 1,
		.has_fअगरo	= 1,
		.is_818		= 1,
	पूर्ण, अणु
		.name		= "pcl818hg",
		.ns_min		= 10000,
		.n_aochan	= 1,
		.ai_range_type	= &range_pcl818hg_ai,
		.has_dma	= 1,
		.has_fअगरo	= 1,
		.is_818		= 1,
	पूर्ण, अणु
		.name		= "pcl818",
		.ns_min		= 10000,
		.n_aochan	= 2,
		.ai_range_type	= &range_pcl818h_ai,
		.has_dma	= 1,
		.is_818		= 1,
	पूर्ण, अणु
		.name		= "pcl718",
		.ns_min		= 16000,
		.n_aochan	= 2,
		.ai_range_type	= &range_unipolar5,
		.has_dma	= 1,
	पूर्ण, अणु
		.name		= "pcm3718",
		.ns_min		= 10000,
		.ai_range_type	= &range_pcl818h_ai,
		.has_dma	= 1,
		.is_818		= 1,
	पूर्ण,
पूर्ण;

काष्ठा pcl818_निजी अणु
	काष्ठा comedi_isadma *dma;
	/*  manimal allowed delay between samples (in us) क्रम actual card */
	अचिन्हित पूर्णांक ns_min;
	/*  MUX setting क्रम actual AI operations */
	अचिन्हित पूर्णांक act_chanlist[16];
	अचिन्हित पूर्णांक act_chanlist_len;	/*  how दीर्घ is actual MUX list */
	अचिन्हित पूर्णांक act_chanlist_pos;	/*  actual position in MUX list */
	अचिन्हित पूर्णांक usefअगरo:1;
	अचिन्हित पूर्णांक ai_cmd_running:1;
	अचिन्हित पूर्णांक ai_cmd_canceled:1;
पूर्ण;

अटल व्योम pcl818_ai_setup_dma(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				अचिन्हित पूर्णांक unपढ़ो_samples)
अणु
	काष्ठा pcl818_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_isadma_desc *desc = &dma->desc[dma->cur_dma];
	अचिन्हित पूर्णांक max_samples = comedi_bytes_to_samples(s, desc->maxsize);
	अचिन्हित पूर्णांक nsamples;

	comedi_isadma_disable(dma->chan);

	/*
	 * Determine dma size based on the buffer maxsize plus the number of
	 * unपढ़ो samples and the number of samples reमुख्यing in the command.
	 */
	nsamples = comedi_nsamples_left(s, max_samples + unपढ़ो_samples);
	अगर (nsamples > unपढ़ो_samples) अणु
		nsamples -= unपढ़ो_samples;
		desc->size = comedi_samples_to_bytes(s, nsamples);
		comedi_isadma_program(desc);
	पूर्ण
पूर्ण

अटल व्योम pcl818_ai_set_chan_range(काष्ठा comedi_device *dev,
				     अचिन्हित पूर्णांक chan,
				     अचिन्हित पूर्णांक range)
अणु
	outb(chan, dev->iobase + PCL818_MUX_REG);
	outb(range, dev->iobase + PCL818_RANGE_REG);
पूर्ण

अटल व्योम pcl818_ai_set_chan_scan(काष्ठा comedi_device *dev,
				    अचिन्हित पूर्णांक first_chan,
				    अचिन्हित पूर्णांक last_chan)
अणु
	outb(PCL818_MUX_SCAN(first_chan, last_chan),
	     dev->iobase + PCL818_MUX_REG);
पूर्ण

अटल व्योम pcl818_ai_setup_chanlist(काष्ठा comedi_device *dev,
				     अचिन्हित पूर्णांक *chanlist,
				     अचिन्हित पूर्णांक seglen)
अणु
	काष्ठा pcl818_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक first_chan = CR_CHAN(chanlist[0]);
	अचिन्हित पूर्णांक last_chan;
	अचिन्हित पूर्णांक range;
	पूर्णांक i;

	devpriv->act_chanlist_len = seglen;
	devpriv->act_chanlist_pos = 0;

	/* store range list to card */
	क्रम (i = 0; i < seglen; i++) अणु
		last_chan = CR_CHAN(chanlist[i]);
		range = CR_RANGE(chanlist[i]);

		devpriv->act_chanlist[i] = last_chan;

		pcl818_ai_set_chan_range(dev, last_chan, range);
	पूर्ण

	udelay(1);

	pcl818_ai_set_chan_scan(dev, first_chan, last_chan);
पूर्ण

अटल व्योम pcl818_ai_clear_eoc(काष्ठा comedi_device *dev)
अणु
	/* writing any value clears the पूर्णांकerrupt request */
	outb(0, dev->iobase + PCL818_STATUS_REG);
पूर्ण

अटल व्योम pcl818_ai_soft_trig(काष्ठा comedi_device *dev)
अणु
	/* writing any value triggers a software conversion */
	outb(0, dev->iobase + PCL818_AI_LSB_REG);
पूर्ण

अटल अचिन्हित पूर्णांक pcl818_ai_get_fअगरo_sample(काष्ठा comedi_device *dev,
					      काष्ठा comedi_subdevice *s,
					      अचिन्हित पूर्णांक *chan)
अणु
	अचिन्हित पूर्णांक val;

	val = inb(dev->iobase + PCL818_FI_DATALO);
	val |= (inb(dev->iobase + PCL818_FI_DATAHI) << 8);

	अगर (chan)
		*chan = val & 0xf;

	वापस (val >> 4) & s->maxdata;
पूर्ण

अटल अचिन्हित पूर्णांक pcl818_ai_get_sample(काष्ठा comedi_device *dev,
					 काष्ठा comedi_subdevice *s,
					 अचिन्हित पूर्णांक *chan)
अणु
	अचिन्हित पूर्णांक val;

	val = inb(dev->iobase + PCL818_AI_MSB_REG) << 8;
	val |= inb(dev->iobase + PCL818_AI_LSB_REG);

	अगर (chan)
		*chan = val & 0xf;

	वापस (val >> 4) & s->maxdata;
पूर्ण

अटल पूर्णांक pcl818_ai_eoc(काष्ठा comedi_device *dev,
			 काष्ठा comedi_subdevice *s,
			 काष्ठा comedi_insn *insn,
			 अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inb(dev->iobase + PCL818_STATUS_REG);
	अगर (status & PCL818_STATUS_INT)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल bool pcl818_ai_ग_लिखो_sample(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   अचिन्हित पूर्णांक chan, अचिन्हित लघु val)
अणु
	काष्ठा pcl818_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक expected_chan;

	expected_chan = devpriv->act_chanlist[devpriv->act_chanlist_pos];
	अगर (chan != expected_chan) अणु
		dev_dbg(dev->class_dev,
			"A/D mode1/3 %s - channel dropout %d!=%d !\n",
			(devpriv->dma) ? "DMA" :
			(devpriv->usefअगरo) ? "FIFO" : "IRQ",
			chan, expected_chan);
		s->async->events |= COMEDI_CB_ERROR;
		वापस false;
	पूर्ण

	comedi_buf_ग_लिखो_samples(s, &val, 1);

	devpriv->act_chanlist_pos++;
	अगर (devpriv->act_chanlist_pos >= devpriv->act_chanlist_len)
		devpriv->act_chanlist_pos = 0;

	अगर (cmd->stop_src == TRIG_COUNT &&
	    s->async->scans_करोne >= cmd->stop_arg) अणु
		s->async->events |= COMEDI_CB_EOA;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम pcl818_handle_eoc(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित पूर्णांक chan;
	अचिन्हित पूर्णांक val;

	अगर (pcl818_ai_eoc(dev, s, शून्य, 0)) अणु
		dev_err(dev->class_dev, "A/D mode1/3 IRQ without DRDY!\n");
		s->async->events |= COMEDI_CB_ERROR;
		वापस;
	पूर्ण

	val = pcl818_ai_get_sample(dev, s, &chan);
	pcl818_ai_ग_लिखो_sample(dev, s, chan, val);
पूर्ण

अटल व्योम pcl818_handle_dma(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pcl818_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_isadma_desc *desc = &dma->desc[dma->cur_dma];
	अचिन्हित लघु *ptr = desc->virt_addr;
	अचिन्हित पूर्णांक nsamples = comedi_bytes_to_samples(s, desc->size);
	अचिन्हित पूर्णांक chan;
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	/* restart dma with the next buffer */
	dma->cur_dma = 1 - dma->cur_dma;
	pcl818_ai_setup_dma(dev, s, nsamples);

	क्रम (i = 0; i < nsamples; i++) अणु
		val = ptr[i];
		chan = val & 0xf;
		val = (val >> 4) & s->maxdata;
		अगर (!pcl818_ai_ग_लिखो_sample(dev, s, chan, val))
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम pcl818_handle_fअगरo(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक chan;
	अचिन्हित पूर्णांक val;
	पूर्णांक i, len;

	status = inb(dev->iobase + PCL818_FI_STATUS);

	अगर (status & 4) अणु
		dev_err(dev->class_dev, "A/D mode1/3 FIFO overflow!\n");
		s->async->events |= COMEDI_CB_ERROR;
		वापस;
	पूर्ण

	अगर (status & 1) अणु
		dev_err(dev->class_dev,
			"A/D mode1/3 FIFO interrupt without data!\n");
		s->async->events |= COMEDI_CB_ERROR;
		वापस;
	पूर्ण

	अगर (status & 2)
		len = 512;
	अन्यथा
		len = 0;

	क्रम (i = 0; i < len; i++) अणु
		val = pcl818_ai_get_fअगरo_sample(dev, s, &chan);
		अगर (!pcl818_ai_ग_लिखो_sample(dev, s, chan, val))
			अवरोध;
	पूर्ण
पूर्ण

अटल irqवापस_t pcl818_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा pcl818_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;

	अगर (!dev->attached || !devpriv->ai_cmd_running) अणु
		pcl818_ai_clear_eoc(dev);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (devpriv->ai_cmd_canceled) अणु
		/*
		 * The cleanup from ai_cancel() has been delayed
		 * until now because the card करोesn't seem to like
		 * being reprogrammed जबतक a DMA transfer is in
		 * progress.
		 */
		s->async->scans_करोne = cmd->stop_arg;
		s->cancel(dev, s);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (devpriv->dma)
		pcl818_handle_dma(dev, s);
	अन्यथा अगर (devpriv->usefअगरo)
		pcl818_handle_fअगरo(dev, s);
	अन्यथा
		pcl818_handle_eoc(dev, s);

	pcl818_ai_clear_eoc(dev);

	comedi_handle_events(dev, s);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक check_channel_list(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      अचिन्हित पूर्णांक *chanlist, अचिन्हित पूर्णांक n_chan)
अणु
	अचिन्हित पूर्णांक chansegment[16];
	अचिन्हित पूर्णांक i, nowmustbechan, seglen;

	/* correct channel and range number check itself comedi/range.c */
	अगर (n_chan < 1) अणु
		dev_err(dev->class_dev, "range/channel list is empty!\n");
		वापस 0;
	पूर्ण

	अगर (n_chan > 1) अणु
		/*  first channel is every समय ok */
		chansegment[0] = chanlist[0];
		/*  build part of chanlist */
		क्रम (i = 1, seglen = 1; i < n_chan; i++, seglen++) अणु
			/* we detect loop, this must by finish */

			अगर (chanlist[0] == chanlist[i])
				अवरोध;
			nowmustbechan =
			    (CR_CHAN(chansegment[i - 1]) + 1) % s->n_chan;
			अगर (nowmustbechan != CR_CHAN(chanlist[i])) अणु
				/*  channel list isn't continuous :-( */
				dev_dbg(dev->class_dev,
					"channel list must be continuous! chanlist[%i]=%d but must be %d or %d!\n",
					i, CR_CHAN(chanlist[i]), nowmustbechan,
					CR_CHAN(chanlist[0]));
				वापस 0;
			पूर्ण
			/*  well, this is next correct channel in list */
			chansegment[i] = chanlist[i];
		पूर्ण

		/*  check whole chanlist */
		क्रम (i = 0; i < n_chan; i++) अणु
			अगर (chanlist[i] != chansegment[i % seglen]) अणु
				dev_dbg(dev->class_dev,
					"bad channel or range number! chanlist[%i]=%d,%d,%d and not %d,%d,%d!\n",
					i, CR_CHAN(chansegment[i]),
					CR_RANGE(chansegment[i]),
					CR_AREF(chansegment[i]),
					CR_CHAN(chanlist[i % seglen]),
					CR_RANGE(chanlist[i % seglen]),
					CR_AREF(chansegment[i % seglen]));
				वापस 0;	/*  chan/gain list is strange */
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		seglen = 1;
	पूर्ण
	वापस seglen;
पूर्ण

अटल पूर्णांक check_single_ended(अचिन्हित पूर्णांक port)
अणु
	अगर (inb(port + PCL818_STATUS_REG) & PCL818_STATUS_MUX)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक ai_cmdtest(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
		      काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा pcl818_board *board = dev->board_ptr;
	पूर्णांक err = 0;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_FOLLOW);
	err |= comedi_check_trigger_src(&cmd->convert_src,
					TRIG_TIMER | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->convert_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
						    board->ns_min);
	पूर्ण अन्यथा अणु	/* TRIG_EXT */
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	पूर्ण

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

	/* step 5: complain about special chanlist considerations */

	अगर (cmd->chanlist) अणु
		अगर (!check_channel_list(dev, s, cmd->chanlist,
					cmd->chanlist_len))
			वापस 5;	/*  incorrect channels list */
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcl818_ai_cmd(काष्ठा comedi_device *dev,
			 काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pcl818_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक ctrl = 0;
	अचिन्हित पूर्णांक seglen;

	अगर (devpriv->ai_cmd_running)
		वापस -EBUSY;

	seglen = check_channel_list(dev, s, cmd->chanlist, cmd->chanlist_len);
	अगर (seglen < 1)
		वापस -EINVAL;
	pcl818_ai_setup_chanlist(dev, cmd->chanlist, seglen);

	devpriv->ai_cmd_running = 1;
	devpriv->ai_cmd_canceled = 0;
	devpriv->act_chanlist_pos = 0;

	अगर (cmd->convert_src == TRIG_TIMER)
		ctrl |= PCL818_CTRL_PACER_TRIG;
	अन्यथा
		ctrl |= PCL818_CTRL_EXT_TRIG;

	outb(0, dev->iobase + PCL818_CNTENABLE_REG);

	अगर (dma) अणु
		/* setup and enable dma क्रम the first buffer */
		dma->cur_dma = 0;
		pcl818_ai_setup_dma(dev, s, 0);

		ctrl |= PCL818_CTRL_INTE | PCL818_CTRL_IRQ(dev->irq) |
			PCL818_CTRL_DMAE;
	पूर्ण अन्यथा अगर (devpriv->usefअगरo) अणु
		/* enable FIFO */
		outb(1, dev->iobase + PCL818_FI_ENABLE);
	पूर्ण अन्यथा अणु
		ctrl |= PCL818_CTRL_INTE | PCL818_CTRL_IRQ(dev->irq);
	पूर्ण
	outb(ctrl, dev->iobase + PCL818_CTRL_REG);

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		comedi_8254_update_भागisors(dev->pacer);
		comedi_8254_pacer_enable(dev->pacer, 1, 2, true);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcl818_ai_cancel(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pcl818_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;

	अगर (!devpriv->ai_cmd_running)
		वापस 0;

	अगर (dma) अणु
		अगर (cmd->stop_src == TRIG_NONE ||
		    (cmd->stop_src == TRIG_COUNT &&
		     s->async->scans_करोne < cmd->stop_arg)) अणु
			अगर (!devpriv->ai_cmd_canceled) अणु
				/*
				 * Wait क्रम running dma transfer to end,
				 * करो cleanup in पूर्णांकerrupt.
				 */
				devpriv->ai_cmd_canceled = 1;
				वापस 0;
			पूर्ण
		पूर्ण
		comedi_isadma_disable(dma->chan);
	पूर्ण

	outb(PCL818_CTRL_DISABLE_TRIG, dev->iobase + PCL818_CTRL_REG);
	comedi_8254_pacer_enable(dev->pacer, 1, 2, false);
	pcl818_ai_clear_eoc(dev);

	अगर (devpriv->usefअगरo) अणु	/*  FIFO shutकरोwn */
		outb(0, dev->iobase + PCL818_FI_INTCLR);
		outb(0, dev->iobase + PCL818_FI_FLUSH);
		outb(0, dev->iobase + PCL818_FI_ENABLE);
	पूर्ण
	devpriv->ai_cmd_running = 0;
	devpriv->ai_cmd_canceled = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक pcl818_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	पूर्णांक ret = 0;
	पूर्णांक i;

	outb(PCL818_CTRL_SOFT_TRIG, dev->iobase + PCL818_CTRL_REG);

	pcl818_ai_set_chan_range(dev, chan, range);
	pcl818_ai_set_chan_scan(dev, chan, chan);

	क्रम (i = 0; i < insn->n; i++) अणु
		pcl818_ai_clear_eoc(dev);
		pcl818_ai_soft_trig(dev);

		ret = comedi_समयout(dev, s, insn, pcl818_ai_eoc, 0);
		अगर (ret)
			अवरोध;

		data[i] = pcl818_ai_get_sample(dev, s, शून्य);
	पूर्ण
	pcl818_ai_clear_eoc(dev);

	वापस ret ? ret : insn->n;
पूर्ण

अटल पूर्णांक pcl818_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];
		outb((val & 0x000f) << 4,
		     dev->iobase + PCL818_AO_LSB_REG(chan));
		outb((val & 0x0ff0) >> 4,
		     dev->iobase + PCL818_AO_MSB_REG(chan));
	पूर्ण
	s->पढ़ोback[chan] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pcl818_di_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	data[1] = inb(dev->iobase + PCL818_DO_DI_LSB_REG) |
		  (inb(dev->iobase + PCL818_DO_DI_MSB_REG) << 8);

	वापस insn->n;
पूर्ण

अटल पूर्णांक pcl818_करो_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data)) अणु
		outb(s->state & 0xff, dev->iobase + PCL818_DO_DI_LSB_REG);
		outb((s->state >> 8), dev->iobase + PCL818_DO_DI_MSB_REG);
	पूर्ण

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल व्योम pcl818_reset(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा pcl818_board *board = dev->board_ptr;
	अचिन्हित पूर्णांक chan;

	/* flush and disable the FIFO */
	अगर (board->has_fअगरo) अणु
		outb(0, dev->iobase + PCL818_FI_INTCLR);
		outb(0, dev->iobase + PCL818_FI_FLUSH);
		outb(0, dev->iobase + PCL818_FI_ENABLE);
	पूर्ण

	/* disable analog input trigger */
	outb(PCL818_CTRL_DISABLE_TRIG, dev->iobase + PCL818_CTRL_REG);
	pcl818_ai_clear_eoc(dev);

	pcl818_ai_set_chan_range(dev, 0, 0);

	/* stop pacer */
	outb(0, dev->iobase + PCL818_CNTENABLE_REG);

	/* set analog output channels to 0V */
	क्रम (chan = 0; chan < board->n_aochan; chan++) अणु
		outb(0, dev->iobase + PCL818_AO_LSB_REG(chan));
		outb(0, dev->iobase + PCL818_AO_MSB_REG(chan));
	पूर्ण

	/* set all digital outमाला_दो low */
	outb(0, dev->iobase + PCL818_DO_DI_MSB_REG);
	outb(0, dev->iobase + PCL818_DO_DI_LSB_REG);
पूर्ण

अटल व्योम pcl818_set_ai_range_table(काष्ठा comedi_device *dev,
				      काष्ठा comedi_subdevice *s,
				      काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा pcl818_board *board = dev->board_ptr;

	/* शेष to the range table from the boardinfo */
	s->range_table = board->ai_range_type;

	/* now check the user config option based on the boardtype */
	अगर (board->is_818) अणु
		अगर (it->options[4] == 1 || it->options[4] == 10) अणु
			/* secondary range list jumper selectable */
			s->range_table = &range_pcl818l_h_ai;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (it->options[4]) अणु
		हाल 0:
			s->range_table = &range_bipolar10;
			अवरोध;
		हाल 1:
			s->range_table = &range_bipolar5;
			अवरोध;
		हाल 2:
			s->range_table = &range_bipolar2_5;
			अवरोध;
		हाल 3:
			s->range_table = &range718_bipolar1;
			अवरोध;
		हाल 4:
			s->range_table = &range718_bipolar0_5;
			अवरोध;
		हाल 6:
			s->range_table = &range_unipolar10;
			अवरोध;
		हाल 7:
			s->range_table = &range_unipolar5;
			अवरोध;
		हाल 8:
			s->range_table = &range718_unipolar2;
			अवरोध;
		हाल 9:
			s->range_table = &range718_unipolar1;
			अवरोध;
		शेष:
			s->range_table = &range_unknown;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pcl818_alloc_dma(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक dma_chan)
अणु
	काष्ठा pcl818_निजी *devpriv = dev->निजी;

	/* only DMA channels 3 and 1 are valid */
	अगर (!(dma_chan == 3 || dma_chan == 1))
		वापस;

	/* DMA uses two 16K buffers */
	devpriv->dma = comedi_isadma_alloc(dev, 2, dma_chan, dma_chan,
					   PAGE_SIZE * 4, COMEDI_ISADMA_READ);
पूर्ण

अटल व्योम pcl818_मुक्त_dma(काष्ठा comedi_device *dev)
अणु
	काष्ठा pcl818_निजी *devpriv = dev->निजी;

	अगर (devpriv)
		comedi_isadma_मुक्त(devpriv->dma);
पूर्ण

अटल पूर्णांक pcl818_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा pcl818_board *board = dev->board_ptr;
	काष्ठा pcl818_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक osc_base;
	पूर्णांक ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_request_region(dev, it->options[0],
				    board->has_fअगरo ? 0x20 : 0x10);
	अगर (ret)
		वापस ret;

	/* we can use IRQ 2-7 क्रम async command support */
	अगर (it->options[1] >= 2 && it->options[1] <= 7) अणु
		ret = request_irq(it->options[1], pcl818_पूर्णांकerrupt, 0,
				  dev->board_name, dev);
		अगर (ret == 0)
			dev->irq = it->options[1];
	पूर्ण

	/* should we use the FIFO? */
	अगर (dev->irq && board->has_fअगरo && it->options[2] == -1)
		devpriv->usefअगरo = 1;

	/* we need an IRQ to करो DMA on channel 3 or 1 */
	अगर (dev->irq && board->has_dma)
		pcl818_alloc_dma(dev, it->options[2]);

	/* use 1MHz or 10MHz oscilator */
	अगर ((it->options[3] == 0) || (it->options[3] == 10))
		osc_base = I8254_OSC_BASE_10MHZ;
	अन्यथा
		osc_base = I8254_OSC_BASE_1MHZ;

	dev->pacer = comedi_8254_init(dev->iobase + PCL818_TIMER_BASE,
				      osc_base, I8254_IO8, 0);
	अगर (!dev->pacer)
		वापस -ENOMEM;

	/* max sampling speed */
	devpriv->ns_min = board->ns_min;
	अगर (!board->is_818) अणु
		/* extended PCL718 to 100kHz DAC */
		अगर ((it->options[6] == 1) || (it->options[6] == 100))
			devpriv->ns_min = 10000;
	पूर्ण

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE;
	अगर (check_single_ended(dev->iobase)) अणु
		s->n_chan	= 16;
		s->subdev_flags	|= SDF_COMMON | SDF_GROUND;
	पूर्ण अन्यथा अणु
		s->n_chan	= 8;
		s->subdev_flags	|= SDF_DIFF;
	पूर्ण
	s->maxdata	= 0x0fff;

	pcl818_set_ai_range_table(dev, s, it);

	s->insn_पढ़ो	= pcl818_ai_insn_पढ़ो;
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->len_chanlist	= s->n_chan;
		s->करो_cmdtest	= ai_cmdtest;
		s->करो_cmd	= pcl818_ai_cmd;
		s->cancel	= pcl818_ai_cancel;
	पूर्ण

	/* Analog Output subdevice */
	s = &dev->subdevices[1];
	अगर (board->n_aochan) अणु
		s->type		= COMEDI_SUBD_AO;
		s->subdev_flags	= SDF_WRITABLE | SDF_GROUND;
		s->n_chan	= board->n_aochan;
		s->maxdata	= 0x0fff;
		s->range_table	= &range_unipolar5;
		अगर (board->is_818) अणु
			अगर ((it->options[4] == 1) || (it->options[4] == 10))
				s->range_table = &range_unipolar10;
			अगर (it->options[4] == 2)
				s->range_table = &range_unknown;
		पूर्ण अन्यथा अणु
			अगर ((it->options[5] == 1) || (it->options[5] == 10))
				s->range_table = &range_unipolar10;
			अगर (it->options[5] == 2)
				s->range_table = &range_unknown;
		पूर्ण
		s->insn_ग_लिखो	= pcl818_ao_insn_ग_लिखो;

		ret = comedi_alloc_subdev_पढ़ोback(s);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		s->type		= COMEDI_SUBD_UNUSED;
	पूर्ण

	/* Digital Input subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pcl818_di_insn_bits;

	/* Digital Output subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pcl818_करो_insn_bits;

	pcl818_reset(dev);

	वापस 0;
पूर्ण

अटल व्योम pcl818_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा pcl818_निजी *devpriv = dev->निजी;

	अगर (devpriv) अणु
		pcl818_ai_cancel(dev, dev->पढ़ो_subdev);
		pcl818_reset(dev);
	पूर्ण
	pcl818_मुक्त_dma(dev);
	comedi_legacy_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver pcl818_driver = अणु
	.driver_name	= "pcl818",
	.module		= THIS_MODULE,
	.attach		= pcl818_attach,
	.detach		= pcl818_detach,
	.board_name	= &boardtypes[0].name,
	.num_names	= ARRAY_SIZE(boardtypes),
	.offset		= माप(काष्ठा pcl818_board),
पूर्ण;
module_comedi_driver(pcl818_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
