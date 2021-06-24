<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  comedi/drivers/adl_pci9118.c
 *
 *  hardware driver क्रम ADLink cards:
 *   card:   PCI-9118DG, PCI-9118HG, PCI-9118HR
 *   driver: pci9118dg,  pci9118hg,  pci9118hr
 *
 * Author: Michal Dobes <करोbes@tesnet.cz>
 *
 */

/*
 * Driver: adl_pci9118
 * Description: Adlink PCI-9118DG, PCI-9118HG, PCI-9118HR
 * Author: Michal Dobes <करोbes@tesnet.cz>
 * Devices: [ADLink] PCI-9118DG (pci9118dg), PCI-9118HG (pci9118hg),
 * PCI-9118HR (pci9118hr)
 * Status: works
 *
 * This driver supports AI, AO, DI and DO subdevices.
 * AI subdevice supports cmd and insn पूर्णांकerface,
 * other subdevices support only insn पूर्णांकerface.
 * For AI:
 * - If cmd->scan_begin_src=TRIG_EXT then trigger input is TGIN (pin 46).
 * - If cmd->convert_src=TRIG_EXT then trigger input is EXTTRG (pin 44).
 * - If cmd->start_src/stop_src=TRIG_EXT then trigger input is TGIN (pin 46).
 * - It is not necessary to have cmd.scan_end_arg=cmd.chanlist_len but
 * cmd.scan_end_arg modulo cmd.chanlist_len must by 0.
 * - If वापस value of cmdtest is 5 then you've bad channel list
 * (it isn't possible mixture S.E. and DIFF inमाला_दो or bipolar and unipolar
 * ranges).
 *
 * There are some hardware limitations:
 * a) You cann't use mixture of unipolar/bipoar ranges or dअगरferencial/single
 *  ended inमाला_दो.
 * b) DMA transfers must have the length aligned to two samples (32 bit),
 *  so there is some problems अगर cmd->chanlist_len is odd. This driver tries
 *  bypass this with adding one sample to the end of the every scan and discard
 *  it on output but this can't be used अगर cmd->scan_begin_src=TRIG_FOLLOW
 *  and is used flag CMDF_WAKE_EOS, then driver चयन to पूर्णांकerrupt driven mode
 *  with पूर्णांकerrupt after every sample.
 * c) If isn't used DMA then you can use only mode where
 *  cmd->scan_begin_src=TRIG_FOLLOW.
 *
 * Configuration options:
 * [0] - PCI bus of device (optional)
 * [1] - PCI slot of device (optional)
 *	 If bus/slot is not specअगरied, then first available PCI
 *	 card will be used.
 * [2] - 0= standard 8 DIFF/16 SE channels configuration
 *	 n = बाह्यal multiplexer connected, 1 <= n <= 256
 * [3] - ignored
 * [4] - sample&hold संकेत - card can generate संकेत क्रम बाह्यal S&H board
 *	 0 = use SSHO(pin 45) संकेत is generated in onboard hardware S&H logic
 *	 0 != use ADCHN7(pin 23) संकेत is generated from driver, number say how
 *		दीर्घ delay is requested in ns and sign polarity of the hold
 *		(in this हाल बाह्यal multiplexor can serve only 128 channels)
 * [5] - ignored
 */

/*
 * FIXME
 *
 * All the supported boards have the same PCI venकरोr and device IDs, so
 * स्वतः-attachment of PCI devices will always find the first board type.
 *
 * Perhaps the boards have dअगरferent subdevice IDs that we could use to
 * distinguish them?
 *
 * Need some device attributes so the board type can be corrected after
 * attachment अगर necessary, and possibly to set other options supported by
 * manual attachment.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/gfp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>

#समावेश "../comedi_pci.h"

#समावेश "amcc_s5933.h"
#समावेश "comedi_8254.h"

/*
 * PCI BAR2 Register map (dev->iobase)
 */
#घोषणा PCI9118_TIMER_BASE		0x00
#घोषणा PCI9118_AI_FIFO_REG		0x10
#घोषणा PCI9118_AO_REG(x)		(0x10 + ((x) * 4))
#घोषणा PCI9118_AI_STATUS_REG		0x18
#घोषणा PCI9118_AI_STATUS_NFULL		BIT(8)	/* 0=FIFO full (fatal) */
#घोषणा PCI9118_AI_STATUS_NHFULL	BIT(7)	/* 0=FIFO half full */
#घोषणा PCI9118_AI_STATUS_NEPTY		BIT(6)	/* 0=FIFO empty */
#घोषणा PCI9118_AI_STATUS_ACMP		BIT(5)	/* 1=about trigger complete */
#घोषणा PCI9118_AI_STATUS_DTH		BIT(4)	/* 1=ext. digital trigger */
#घोषणा PCI9118_AI_STATUS_BOVER		BIT(3)	/* 1=burst overrun (fatal) */
#घोषणा PCI9118_AI_STATUS_ADOS		BIT(2)	/* 1=A/D over speed (warn) */
#घोषणा PCI9118_AI_STATUS_ADOR		BIT(1)	/* 1=A/D overrun (fatal) */
#घोषणा PCI9118_AI_STATUS_ADRDY		BIT(0)	/* 1=A/D पढ़ोy */
#घोषणा PCI9118_AI_CTRL_REG		0x18
#घोषणा PCI9118_AI_CTRL_UNIP		BIT(7)	/* 1=unipolar */
#घोषणा PCI9118_AI_CTRL_DIFF		BIT(6)	/* 1=dअगरferential inमाला_दो */
#घोषणा PCI9118_AI_CTRL_SOFTG		BIT(5)	/* 1=8254 software gate */
#घोषणा PCI9118_AI_CTRL_EXTG		BIT(4)	/* 1=8254 TGIN(pin 46) gate */
#घोषणा PCI9118_AI_CTRL_EXTM		BIT(3)	/* 1=ext. trigger (pin 44) */
#घोषणा PCI9118_AI_CTRL_TMRTR		BIT(2)	/* 1=8254 is trigger source */
#घोषणा PCI9118_AI_CTRL_INT		BIT(1)	/* 1=enable पूर्णांकerrupt */
#घोषणा PCI9118_AI_CTRL_DMA		BIT(0)	/* 1=enable DMA */
#घोषणा PCI9118_DIO_REG			0x1c
#घोषणा PCI9118_SOFTTRG_REG		0x20
#घोषणा PCI9118_AI_CHANLIST_REG		0x24
#घोषणा PCI9118_AI_CHANLIST_RANGE(x)	(((x) & 0x3) << 8)
#घोषणा PCI9118_AI_CHANLIST_CHAN(x)	((x) << 0)
#घोषणा PCI9118_AI_BURST_NUM_REG	0x28
#घोषणा PCI9118_AI_AUTOSCAN_MODE_REG	0x2c
#घोषणा PCI9118_AI_CFG_REG		0x30
#घोषणा PCI9118_AI_CFG_PDTRG		BIT(7)	/* 1=positive trigger */
#घोषणा PCI9118_AI_CFG_PETRG		BIT(6)	/* 1=positive ext. trigger */
#घोषणा PCI9118_AI_CFG_BSSH		BIT(5)	/* 1=with sample & hold */
#घोषणा PCI9118_AI_CFG_BM		BIT(4)	/* 1=burst mode */
#घोषणा PCI9118_AI_CFG_BS		BIT(3)	/* 1=burst mode start */
#घोषणा PCI9118_AI_CFG_PM		BIT(2)	/* 1=post trigger */
#घोषणा PCI9118_AI_CFG_AM		BIT(1)	/* 1=about trigger */
#घोषणा PCI9118_AI_CFG_START		BIT(0)	/* 1=trigger start */
#घोषणा PCI9118_FIFO_RESET_REG		0x34
#घोषणा PCI9118_INT_CTRL_REG		0x38
#घोषणा PCI9118_INT_CTRL_TIMER		BIT(3)	/* समयr पूर्णांकerrupt */
#घोषणा PCI9118_INT_CTRL_ABOUT		BIT(2)	/* about trigger complete */
#घोषणा PCI9118_INT_CTRL_HFULL		BIT(1)	/* A/D FIFO half full */
#घोषणा PCI9118_INT_CTRL_DTRG		BIT(0)	/* ext. digital trigger */

#घोषणा START_AI_EXT	0x01	/* start measure on बाह्यal trigger */
#घोषणा STOP_AI_EXT	0x02	/* stop measure on बाह्यal trigger */
#घोषणा STOP_AI_INT	0x08	/* stop measure on पूर्णांकernal trigger */

अटल स्थिर काष्ठा comedi_lrange pci9118_ai_range = अणु
	8, अणु
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
		BIP_RANGE(0.625),
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2.5),
		UNI_RANGE(1.25)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange pci9118hg_ai_range = अणु
	8, अणु
		BIP_RANGE(5),
		BIP_RANGE(0.5),
		BIP_RANGE(0.05),
		BIP_RANGE(0.005),
		UNI_RANGE(10),
		UNI_RANGE(1),
		UNI_RANGE(0.1),
		UNI_RANGE(0.01)
	पूर्ण
पूर्ण;

क्रमागत pci9118_boardid अणु
	BOARD_PCI9118DG,
	BOARD_PCI9118HG,
	BOARD_PCI9118HR,
पूर्ण;

काष्ठा pci9118_boardinfo अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक ai_is_16bit:1;
	अचिन्हित पूर्णांक is_hg:1;
पूर्ण;

अटल स्थिर काष्ठा pci9118_boardinfo pci9118_boards[] = अणु
	[BOARD_PCI9118DG] = अणु
		.name		= "pci9118dg",
	पूर्ण,
	[BOARD_PCI9118HG] = अणु
		.name		= "pci9118hg",
		.is_hg		= 1,
	पूर्ण,
	[BOARD_PCI9118HR] = अणु
		.name		= "pci9118hr",
		.ai_is_16bit	= 1,
	पूर्ण,
पूर्ण;

काष्ठा pci9118_dmabuf अणु
	अचिन्हित लघु *virt;	/* भव address of buffer */
	dma_addr_t hw;		/* hardware (bus) address of buffer */
	अचिन्हित पूर्णांक size;	/* size of dma buffer in bytes */
	अचिन्हित पूर्णांक use_size;	/* which size we may now use क्रम transfer */
पूर्ण;

काष्ठा pci9118_निजी अणु
	अचिन्हित दीर्घ iobase_a;	/* base+size क्रम AMCC chip */
	अचिन्हित पूर्णांक master:1;
	अचिन्हित पूर्णांक dma_द्विगुनbuf:1;
	अचिन्हित पूर्णांक ai_neverending:1;
	अचिन्हित पूर्णांक usedma:1;
	अचिन्हित पूर्णांक usemux:1;
	अचिन्हित अक्षर ai_ctrl;
	अचिन्हित अक्षर पूर्णांक_ctrl;
	अचिन्हित अक्षर ai_cfg;
	अचिन्हित पूर्णांक ai_करो;		/* what करो AI? 0=nothing, 1 to 4 mode */
	अचिन्हित पूर्णांक ai_n_realscanlen;	/*
					 * what we must transfer क्रम one
					 * outgoing scan include front/back adds
					 */
	अचिन्हित पूर्णांक ai_act_dmapos;	/* position in actual real stream */
	अचिन्हित पूर्णांक ai_add_front;	/*
					 * how many channels we must add
					 * beक्रमe scan to satisfy S&H?
					 */
	अचिन्हित पूर्णांक ai_add_back;	/*
					 * how many channels we must add
					 * beक्रमe scan to satisfy DMA?
					 */
	अचिन्हित पूर्णांक ai_flags;
	अक्षर ai12_startstop;		/*
					 * measure can start/stop
					 * on बाह्यal trigger
					 */
	अचिन्हित पूर्णांक dma_actbuf;		/* which buffer is used now */
	काष्ठा pci9118_dmabuf dmabuf[2];
	पूर्णांक softsshdelay;		/*
					 * >0 use software S&H,
					 * numer is requested delay in ns
					 */
	अचिन्हित अक्षर softsshsample;	/*
					 * polarity of S&H संकेत
					 * in sample state
					 */
	अचिन्हित अक्षर softsshhold;	/*
					 * polarity of S&H संकेत
					 * in hold state
					 */
	अचिन्हित पूर्णांक ai_ns_min;
पूर्ण;

अटल व्योम pci9118_amcc_setup_dma(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक buf)
अणु
	काष्ठा pci9118_निजी *devpriv = dev->निजी;
	काष्ठा pci9118_dmabuf *dmabuf = &devpriv->dmabuf[buf];

	/* set the master ग_लिखो address and transfer count */
	outl(dmabuf->hw, devpriv->iobase_a + AMCC_OP_REG_MWAR);
	outl(dmabuf->use_size, devpriv->iobase_a + AMCC_OP_REG_MWTC);
पूर्ण

अटल व्योम pci9118_amcc_dma_ena(काष्ठा comedi_device *dev, bool enable)
अणु
	काष्ठा pci9118_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक mcsr;

	mcsr = inl(devpriv->iobase_a + AMCC_OP_REG_MCSR);
	अगर (enable)
		mcsr |= RESET_A2P_FLAGS | A2P_HI_PRIORITY | EN_A2P_TRANSFERS;
	अन्यथा
		mcsr &= ~EN_A2P_TRANSFERS;
	outl(mcsr, devpriv->iobase_a + AMCC_OP_REG_MCSR);
पूर्ण

अटल व्योम pci9118_amcc_पूर्णांक_ena(काष्ठा comedi_device *dev, bool enable)
अणु
	काष्ठा pci9118_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक पूर्णांकcsr;

	/* enable/disable पूर्णांकerrupt क्रम AMCC Incoming Mailbox 4 (32-bit) */
	पूर्णांकcsr = inl(devpriv->iobase_a + AMCC_OP_REG_INTCSR);
	अगर (enable)
		पूर्णांकcsr |= 0x1f00;
	अन्यथा
		पूर्णांकcsr &= ~0x1f00;
	outl(पूर्णांकcsr, devpriv->iobase_a + AMCC_OP_REG_INTCSR);
पूर्ण

अटल व्योम pci9118_ai_reset_fअगरo(काष्ठा comedi_device *dev)
अणु
	/* writing any value resets the A/D FIFO */
	outl(0, dev->iobase + PCI9118_FIFO_RESET_REG);
पूर्ण

अटल पूर्णांक pci9118_ai_check_chanlist(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा pci9118_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक range0 = CR_RANGE(cmd->chanlist[0]);
	अचिन्हित पूर्णांक aref0 = CR_AREF(cmd->chanlist[0]);
	पूर्णांक i;

	/* single channel scans are always ok */
	अगर (cmd->chanlist_len == 1)
		वापस 0;

	क्रम (i = 1; i < cmd->chanlist_len; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);
		अचिन्हित पूर्णांक range = CR_RANGE(cmd->chanlist[i]);
		अचिन्हित पूर्णांक aref = CR_AREF(cmd->chanlist[i]);

		अगर (aref != aref0) अणु
			dev_err(dev->class_dev,
				"Differential and single ended inputs can't be mixed!\n");
			वापस -EINVAL;
		पूर्ण
		अगर (comedi_range_is_bipolar(s, range) !=
		    comedi_range_is_bipolar(s, range0)) अणु
			dev_err(dev->class_dev,
				"Bipolar and unipolar ranges can't be mixed!\n");
			वापस -EINVAL;
		पूर्ण
		अगर (!devpriv->usemux && aref == AREF_DIFF &&
		    (chan >= (s->n_chan / 2))) अणु
			dev_err(dev->class_dev,
				"AREF_DIFF is only available for the first 8 channels!\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pci9118_set_chanlist(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 पूर्णांक n_chan, अचिन्हित पूर्णांक *chanlist,
				 पूर्णांक frontadd, पूर्णांक backadd)
अणु
	काष्ठा pci9118_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan0 = CR_CHAN(chanlist[0]);
	अचिन्हित पूर्णांक range0 = CR_RANGE(chanlist[0]);
	अचिन्हित पूर्णांक aref0 = CR_AREF(chanlist[0]);
	अचिन्हित पूर्णांक ssh = 0x00;
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	/*
	 * Configure analog input based on the first chanlist entry.
	 * All entries are either unipolar or bipolar and single-ended
	 * or dअगरferential.
	 */
	devpriv->ai_ctrl = 0;
	अगर (comedi_range_is_unipolar(s, range0))
		devpriv->ai_ctrl |= PCI9118_AI_CTRL_UNIP;
	अगर (aref0 == AREF_DIFF)
		devpriv->ai_ctrl |= PCI9118_AI_CTRL_DIFF;
	outl(devpriv->ai_ctrl, dev->iobase + PCI9118_AI_CTRL_REG);

	/* gods know why this sequence! */
	outl(2, dev->iobase + PCI9118_AI_AUTOSCAN_MODE_REG);
	outl(0, dev->iobase + PCI9118_AI_AUTOSCAN_MODE_REG);
	outl(1, dev->iobase + PCI9118_AI_AUTOSCAN_MODE_REG);

	/* insert channels क्रम S&H */
	अगर (frontadd) अणु
		val = PCI9118_AI_CHANLIST_CHAN(chan0) |
		      PCI9118_AI_CHANLIST_RANGE(range0);
		ssh = devpriv->softsshsample;
		क्रम (i = 0; i < frontadd; i++) अणु
			outl(val | ssh, dev->iobase + PCI9118_AI_CHANLIST_REG);
			ssh = devpriv->softsshhold;
		पूर्ण
	पूर्ण

	/* store chanlist */
	क्रम (i = 0; i < n_chan; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(chanlist[i]);
		अचिन्हित पूर्णांक range = CR_RANGE(chanlist[i]);

		val = PCI9118_AI_CHANLIST_CHAN(chan) |
		      PCI9118_AI_CHANLIST_RANGE(range);
		outl(val | ssh, dev->iobase + PCI9118_AI_CHANLIST_REG);
	पूर्ण

	/* insert channels to fit onto 32bit DMA */
	अगर (backadd) अणु
		val = PCI9118_AI_CHANLIST_CHAN(chan0) |
		      PCI9118_AI_CHANLIST_RANGE(range0);
		क्रम (i = 0; i < backadd; i++)
			outl(val | ssh, dev->iobase + PCI9118_AI_CHANLIST_REG);
	पूर्ण
	/* बंद scan queue */
	outl(0, dev->iobase + PCI9118_AI_AUTOSCAN_MODE_REG);
	/* udelay(100); important delay, or first sample will be crippled */
पूर्ण

अटल व्योम pci9118_ai_mode4_चयन(काष्ठा comedi_device *dev,
				    अचिन्हित पूर्णांक next_buf)
अणु
	काष्ठा pci9118_निजी *devpriv = dev->निजी;
	काष्ठा pci9118_dmabuf *dmabuf = &devpriv->dmabuf[next_buf];

	devpriv->ai_cfg = PCI9118_AI_CFG_PDTRG | PCI9118_AI_CFG_PETRG |
			  PCI9118_AI_CFG_AM;
	outl(devpriv->ai_cfg, dev->iobase + PCI9118_AI_CFG_REG);
	comedi_8254_load(dev->pacer, 0, dmabuf->hw >> 1,
			 I8254_MODE0 | I8254_BINARY);
	devpriv->ai_cfg |= PCI9118_AI_CFG_START;
	outl(devpriv->ai_cfg, dev->iobase + PCI9118_AI_CFG_REG);
पूर्ण

अटल अचिन्हित पूर्णांक pci9118_ai_samples_पढ़ोy(काष्ठा comedi_device *dev,
					     काष्ठा comedi_subdevice *s,
					     अचिन्हित पूर्णांक n_raw_samples)
अणु
	काष्ठा pci9118_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक start_pos = devpriv->ai_add_front;
	अचिन्हित पूर्णांक stop_pos = start_pos + cmd->chanlist_len;
	अचिन्हित पूर्णांक span_len = stop_pos + devpriv->ai_add_back;
	अचिन्हित पूर्णांक dma_pos = devpriv->ai_act_dmapos;
	अचिन्हित पूर्णांक whole_spans, n_samples, x;

	अगर (span_len == cmd->chanlist_len)
		वापस n_raw_samples;	/* use all samples */

	/*
	 * Not all samples are to be used.  Buffer contents consist of a
	 * possibly non-whole number of spans and a region of each span
	 * is to be used.
	 *
	 * Account क्रम samples in whole number of spans.
	 */
	whole_spans = n_raw_samples / span_len;
	n_samples = whole_spans * cmd->chanlist_len;
	n_raw_samples -= whole_spans * span_len;

	/*
	 * Deal with reमुख्यing samples which could overlap up to two spans.
	 */
	जबतक (n_raw_samples) अणु
		अगर (dma_pos < start_pos) अणु
			/* Skip samples beक्रमe start position. */
			x = start_pos - dma_pos;
			अगर (x > n_raw_samples)
				x = n_raw_samples;
			dma_pos += x;
			n_raw_samples -= x;
			अगर (!n_raw_samples)
				अवरोध;
		पूर्ण
		अगर (dma_pos < stop_pos) अणु
			/* Include samples beक्रमe stop position. */
			x = stop_pos - dma_pos;
			अगर (x > n_raw_samples)
				x = n_raw_samples;
			n_samples += x;
			dma_pos += x;
			n_raw_samples -= x;
		पूर्ण
		/* Advance to next span. */
		start_pos += span_len;
		stop_pos += span_len;
	पूर्ण
	वापस n_samples;
पूर्ण

अटल व्योम pci9118_ai_dma_xfer(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				अचिन्हित लघु *dma_buffer,
				अचिन्हित पूर्णांक n_raw_samples)
अणु
	काष्ठा pci9118_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक start_pos = devpriv->ai_add_front;
	अचिन्हित पूर्णांक stop_pos = start_pos + cmd->chanlist_len;
	अचिन्हित पूर्णांक span_len = stop_pos + devpriv->ai_add_back;
	अचिन्हित पूर्णांक dma_pos = devpriv->ai_act_dmapos;
	अचिन्हित पूर्णांक x;

	अगर (span_len == cmd->chanlist_len) अणु
		/* All samples are to be copied. */
		comedi_buf_ग_लिखो_samples(s, dma_buffer, n_raw_samples);
		dma_pos += n_raw_samples;
	पूर्ण अन्यथा अणु
		/*
		 * Not all samples are to be copied.  Buffer contents consist
		 * of a possibly non-whole number of spans and a region of
		 * each span is to be copied.
		 */
		जबतक (n_raw_samples) अणु
			अगर (dma_pos < start_pos) अणु
				/* Skip samples beक्रमe start position. */
				x = start_pos - dma_pos;
				अगर (x > n_raw_samples)
					x = n_raw_samples;
				dma_pos += x;
				n_raw_samples -= x;
				अगर (!n_raw_samples)
					अवरोध;
			पूर्ण
			अगर (dma_pos < stop_pos) अणु
				/* Copy samples beक्रमe stop position. */
				x = stop_pos - dma_pos;
				अगर (x > n_raw_samples)
					x = n_raw_samples;
				comedi_buf_ग_लिखो_samples(s, dma_buffer, x);
				dma_pos += x;
				n_raw_samples -= x;
			पूर्ण
			/* Advance to next span. */
			start_pos += span_len;
			stop_pos += span_len;
		पूर्ण
	पूर्ण
	/* Update position in span क्रम next समय. */
	devpriv->ai_act_dmapos = dma_pos % span_len;
पूर्ण

अटल व्योम pci9118_exttrg_enable(काष्ठा comedi_device *dev, bool enable)
अणु
	काष्ठा pci9118_निजी *devpriv = dev->निजी;

	अगर (enable)
		devpriv->पूर्णांक_ctrl |= PCI9118_INT_CTRL_DTRG;
	अन्यथा
		devpriv->पूर्णांक_ctrl &= ~PCI9118_INT_CTRL_DTRG;
	outl(devpriv->पूर्णांक_ctrl, dev->iobase + PCI9118_INT_CTRL_REG);

	अगर (devpriv->पूर्णांक_ctrl)
		pci9118_amcc_पूर्णांक_ena(dev, true);
	अन्यथा
		pci9118_amcc_पूर्णांक_ena(dev, false);
पूर्ण

अटल व्योम pci9118_calc_भागisors(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  अचिन्हित पूर्णांक *tim1, अचिन्हित पूर्णांक *tim2,
				  अचिन्हित पूर्णांक flags, पूर्णांक chans,
				  अचिन्हित पूर्णांक *भाग1, अचिन्हित पूर्णांक *भाग2,
				  अचिन्हित पूर्णांक chnsshfront)
अणु
	काष्ठा comedi_8254 *pacer = dev->pacer;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;

	*भाग1 = *tim2 / pacer->osc_base;	/* convert समयr (burst) */
	*भाग2 = *tim1 / pacer->osc_base;	/* scan समयr */
	*भाग2 = *भाग2 / *भाग1;			/* major समयr is c1*c2 */
	अगर (*भाग2 < chans)
		*भाग2 = chans;

	*tim2 = *भाग1 * pacer->osc_base;	/* real convert समयr */

	अगर (cmd->convert_src == TRIG_NOW && !chnsshfront) अणु
		/* use BSSH संकेत */
		अगर (*भाग2 < (chans + 2))
			*भाग2 = chans + 2;
	पूर्ण

	*tim1 = *भाग1 * *भाग2 * pacer->osc_base;
पूर्ण

अटल व्योम pci9118_start_pacer(काष्ठा comedi_device *dev, पूर्णांक mode)
अणु
	अगर (mode == 1 || mode == 2 || mode == 4)
		comedi_8254_pacer_enable(dev->pacer, 1, 2, true);
पूर्ण

अटल पूर्णांक pci9118_ai_cancel(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci9118_निजी *devpriv = dev->निजी;

	अगर (devpriv->usedma)
		pci9118_amcc_dma_ena(dev, false);
	pci9118_exttrg_enable(dev, false);
	comedi_8254_pacer_enable(dev->pacer, 1, 2, false);
	/* set शेष config (disable burst and triggers) */
	devpriv->ai_cfg = PCI9118_AI_CFG_PDTRG | PCI9118_AI_CFG_PETRG;
	outl(devpriv->ai_cfg, dev->iobase + PCI9118_AI_CFG_REG);
	/* reset acquisition control */
	devpriv->ai_ctrl = 0;
	outl(devpriv->ai_ctrl, dev->iobase + PCI9118_AI_CTRL_REG);
	outl(0, dev->iobase + PCI9118_AI_BURST_NUM_REG);
	/* reset scan queue */
	outl(1, dev->iobase + PCI9118_AI_AUTOSCAN_MODE_REG);
	outl(2, dev->iobase + PCI9118_AI_AUTOSCAN_MODE_REG);
	pci9118_ai_reset_fअगरo(dev);

	devpriv->पूर्णांक_ctrl = 0;
	outl(devpriv->पूर्णांक_ctrl, dev->iobase + PCI9118_INT_CTRL_REG);
	pci9118_amcc_पूर्णांक_ena(dev, false);

	devpriv->ai_करो = 0;
	devpriv->usedma = 0;

	devpriv->ai_act_dmapos = 0;
	s->async->पूर्णांकtrig = शून्य;
	devpriv->ai_neverending = 0;
	devpriv->dma_actbuf = 0;

	वापस 0;
पूर्ण

अटल व्योम pci9118_ai_munge(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s, व्योम *data,
			     अचिन्हित पूर्णांक num_bytes,
			     अचिन्हित पूर्णांक start_chan_index)
अणु
	काष्ठा pci9118_निजी *devpriv = dev->निजी;
	अचिन्हित लघु *array = data;
	अचिन्हित पूर्णांक num_samples = comedi_bytes_to_samples(s, num_bytes);
	अचिन्हित पूर्णांक i;
	__be16 *barray = data;

	क्रम (i = 0; i < num_samples; i++) अणु
		अगर (devpriv->usedma)
			array[i] = be16_to_cpu(barray[i]);
		अगर (s->maxdata == 0xffff)
			array[i] ^= 0x8000;
		अन्यथा
			array[i] = (array[i] >> 4) & 0x0fff;
	पूर्ण
पूर्ण

अटल व्योम pci9118_ai_get_onesample(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci9118_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित लघु sampl;

	sampl = inl(dev->iobase + PCI9118_AI_FIFO_REG);

	comedi_buf_ग_लिखो_samples(s, &sampl, 1);

	अगर (!devpriv->ai_neverending) अणु
		अगर (s->async->scans_करोne >= cmd->stop_arg)
			s->async->events |= COMEDI_CB_EOA;
	पूर्ण
पूर्ण

अटल व्योम pci9118_ai_get_dma(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci9118_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	काष्ठा pci9118_dmabuf *dmabuf = &devpriv->dmabuf[devpriv->dma_actbuf];
	अचिन्हित पूर्णांक n_all = comedi_bytes_to_samples(s, dmabuf->use_size);
	अचिन्हित पूर्णांक n_valid;
	bool more_dma;

	/* determine whether more DMA buffers to करो after this one */
	n_valid = pci9118_ai_samples_पढ़ोy(dev, s, n_all);
	more_dma = n_valid < comedi_nsamples_left(s, n_valid + 1);

	/* चयन DMA buffers and restart DMA अगर द्विगुन buffering */
	अगर (more_dma && devpriv->dma_द्विगुनbuf) अणु
		devpriv->dma_actbuf = 1 - devpriv->dma_actbuf;
		pci9118_amcc_setup_dma(dev, devpriv->dma_actbuf);
		अगर (devpriv->ai_करो == 4)
			pci9118_ai_mode4_चयन(dev, devpriv->dma_actbuf);
	पूर्ण

	अगर (n_all)
		pci9118_ai_dma_xfer(dev, s, dmabuf->virt, n_all);

	अगर (!devpriv->ai_neverending) अणु
		अगर (s->async->scans_करोne >= cmd->stop_arg)
			s->async->events |= COMEDI_CB_EOA;
	पूर्ण

	अगर (s->async->events & COMEDI_CB_CANCEL_MASK)
		more_dma = false;

	/* restart DMA अगर not द्विगुन buffering */
	अगर (more_dma && !devpriv->dma_द्विगुनbuf) अणु
		pci9118_amcc_setup_dma(dev, 0);
		अगर (devpriv->ai_करो == 4)
			pci9118_ai_mode4_चयन(dev, 0);
	पूर्ण
पूर्ण

अटल irqवापस_t pci9118_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा pci9118_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक पूर्णांकsrc;	/* IRQ reasons from card */
	अचिन्हित पूर्णांक पूर्णांकcsr;	/* INT रेजिस्टर from AMCC chip */
	अचिन्हित पूर्णांक adstat;	/* STATUS रेजिस्टर */

	अगर (!dev->attached)
		वापस IRQ_NONE;

	पूर्णांकsrc = inl(dev->iobase + PCI9118_INT_CTRL_REG) & 0xf;
	पूर्णांकcsr = inl(devpriv->iobase_a + AMCC_OP_REG_INTCSR);

	अगर (!पूर्णांकsrc && !(पूर्णांकcsr & ANY_S593X_INT))
		वापस IRQ_NONE;

	outl(पूर्णांकcsr | 0x00ff0000, devpriv->iobase_a + AMCC_OP_REG_INTCSR);

	अगर (पूर्णांकcsr & MASTER_ABORT_INT) अणु
		dev_err(dev->class_dev, "AMCC IRQ - MASTER DMA ABORT!\n");
		s->async->events |= COMEDI_CB_ERROR;
		जाओ पूर्णांकerrupt_निकास;
	पूर्ण

	अगर (पूर्णांकcsr & TARGET_ABORT_INT) अणु
		dev_err(dev->class_dev, "AMCC IRQ - TARGET DMA ABORT!\n");
		s->async->events |= COMEDI_CB_ERROR;
		जाओ पूर्णांकerrupt_निकास;
	पूर्ण

	adstat = inl(dev->iobase + PCI9118_AI_STATUS_REG);
	अगर ((adstat & PCI9118_AI_STATUS_NFULL) == 0) अणु
		dev_err(dev->class_dev,
			"A/D FIFO Full status (Fatal Error!)\n");
		s->async->events |= COMEDI_CB_ERROR | COMEDI_CB_OVERFLOW;
		जाओ पूर्णांकerrupt_निकास;
	पूर्ण
	अगर (adstat & PCI9118_AI_STATUS_BOVER) अणु
		dev_err(dev->class_dev,
			"A/D Burst Mode Overrun Status (Fatal Error!)\n");
		s->async->events |= COMEDI_CB_ERROR | COMEDI_CB_OVERFLOW;
		जाओ पूर्णांकerrupt_निकास;
	पूर्ण
	अगर (adstat & PCI9118_AI_STATUS_ADOS) अणु
		dev_err(dev->class_dev, "A/D Over Speed Status (Warning!)\n");
		s->async->events |= COMEDI_CB_ERROR;
		जाओ पूर्णांकerrupt_निकास;
	पूर्ण
	अगर (adstat & PCI9118_AI_STATUS_ADOR) अणु
		dev_err(dev->class_dev, "A/D Overrun Status (Fatal Error!)\n");
		s->async->events |= COMEDI_CB_ERROR | COMEDI_CB_OVERFLOW;
		जाओ पूर्णांकerrupt_निकास;
	पूर्ण

	अगर (!devpriv->ai_करो)
		वापस IRQ_HANDLED;

	अगर (devpriv->ai12_startstop) अणु
		अगर ((adstat & PCI9118_AI_STATUS_DTH) &&
		    (पूर्णांकsrc & PCI9118_INT_CTRL_DTRG)) अणु
			/* start/stop of measure */
			अगर (devpriv->ai12_startstop & START_AI_EXT) अणु
				/* deactivate EXT trigger */
				devpriv->ai12_startstop &= ~START_AI_EXT;
				अगर (!(devpriv->ai12_startstop & STOP_AI_EXT))
					pci9118_exttrg_enable(dev, false);

				/* start pacer */
				pci9118_start_pacer(dev, devpriv->ai_करो);
				outl(devpriv->ai_ctrl,
				     dev->iobase + PCI9118_AI_CTRL_REG);
			पूर्ण अन्यथा अगर (devpriv->ai12_startstop & STOP_AI_EXT) अणु
				/* deactivate EXT trigger */
				devpriv->ai12_startstop &= ~STOP_AI_EXT;
				pci9118_exttrg_enable(dev, false);

				/* on next पूर्णांकerrupt measure will stop */
				devpriv->ai_neverending = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (devpriv->usedma)
		pci9118_ai_get_dma(dev, s);
	अन्यथा
		pci9118_ai_get_onesample(dev, s);

पूर्णांकerrupt_निकास:
	comedi_handle_events(dev, s);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम pci9118_ai_cmd_start(काष्ठा comedi_device *dev)
अणु
	काष्ठा pci9118_निजी *devpriv = dev->निजी;

	outl(devpriv->पूर्णांक_ctrl, dev->iobase + PCI9118_INT_CTRL_REG);
	outl(devpriv->ai_cfg, dev->iobase + PCI9118_AI_CFG_REG);
	अगर (devpriv->ai_करो != 3) अणु
		pci9118_start_pacer(dev, devpriv->ai_करो);
		devpriv->ai_ctrl |= PCI9118_AI_CTRL_SOFTG;
	पूर्ण
	outl(devpriv->ai_ctrl, dev->iobase + PCI9118_AI_CTRL_REG);
पूर्ण

अटल पूर्णांक pci9118_ai_पूर्णांकtrig(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा comedi_cmd *cmd = &s->async->cmd;

	अगर (trig_num != cmd->start_arg)
		वापस -EINVAL;

	s->async->पूर्णांकtrig = शून्य;
	pci9118_ai_cmd_start(dev);

	वापस 1;
पूर्ण

अटल पूर्णांक pci9118_ai_setup_dma(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci9118_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	काष्ठा pci9118_dmabuf *dmabuf0 = &devpriv->dmabuf[0];
	काष्ठा pci9118_dmabuf *dmabuf1 = &devpriv->dmabuf[1];
	अचिन्हित पूर्णांक dmalen0 = dmabuf0->size;
	अचिन्हित पूर्णांक dmalen1 = dmabuf1->size;
	अचिन्हित पूर्णांक scan_bytes = devpriv->ai_n_realscanlen *
				  comedi_bytes_per_sample(s);

	/* isn't output buff smaller that our DMA buff? */
	अगर (dmalen0 > s->async->pपुनः_स्मृति_bufsz) अणु
		/* align to 32bit करोwn */
		dmalen0 = s->async->pपुनः_स्मृति_bufsz & ~3L;
	पूर्ण
	अगर (dmalen1 > s->async->pपुनः_स्मृति_bufsz) अणु
		/* align to 32bit करोwn */
		dmalen1 = s->async->pपुनः_स्मृति_bufsz & ~3L;
	पूर्ण

	/* we want wake up every scan? */
	अगर (devpriv->ai_flags & CMDF_WAKE_EOS) अणु
		अगर (dmalen0 < scan_bytes) अणु
			/* uff, too लघु DMA buffer, disable EOS support! */
			devpriv->ai_flags &= (~CMDF_WAKE_EOS);
			dev_info(dev->class_dev,
				 "WAR: DMA0 buf too short, can't support CMDF_WAKE_EOS (%d<%d)\n",
				  dmalen0, scan_bytes);
		पूर्ण अन्यथा अणु
			/* लघु first DMA buffer to one scan */
			dmalen0 = scan_bytes;
			अगर (dmalen0 < 4) अणु
				dev_info(dev->class_dev,
					 "ERR: DMA0 buf len bug? (%d<4)\n",
					 dmalen0);
				dmalen0 = 4;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (devpriv->ai_flags & CMDF_WAKE_EOS) अणु
		अगर (dmalen1 < scan_bytes) अणु
			/* uff, too लघु DMA buffer, disable EOS support! */
			devpriv->ai_flags &= (~CMDF_WAKE_EOS);
			dev_info(dev->class_dev,
				 "WAR: DMA1 buf too short, can't support CMDF_WAKE_EOS (%d<%d)\n",
				 dmalen1, scan_bytes);
		पूर्ण अन्यथा अणु
			/* लघु second DMA buffer to one scan */
			dmalen1 = scan_bytes;
			अगर (dmalen1 < 4) अणु
				dev_info(dev->class_dev,
					 "ERR: DMA1 buf len bug? (%d<4)\n",
					 dmalen1);
				dmalen1 = 4;
			पूर्ण
		पूर्ण
	पूर्ण

	/* transfer without CMDF_WAKE_EOS */
	अगर (!(devpriv->ai_flags & CMDF_WAKE_EOS)) अणु
		अचिन्हित पूर्णांक पंचांगp;

		/* अगर it's possible then align DMA buffers to length of scan */
		पंचांगp = dmalen0;
		dmalen0 = (dmalen0 / scan_bytes) * scan_bytes;
		dmalen0 &= ~3L;
		अगर (!dmalen0)
			dmalen0 = पंचांगp;	/* uff. very दीर्घ scan? */
		पंचांगp = dmalen1;
		dmalen1 = (dmalen1 / scan_bytes) * scan_bytes;
		dmalen1 &= ~3L;
		अगर (!dmalen1)
			dmalen1 = पंचांगp;	/* uff. very दीर्घ scan? */
		/*
		 * अगर measure isn't neverending then test, अगर it fits whole
		 * पूर्णांकo one or two DMA buffers
		 */
		अगर (!devpriv->ai_neverending) अणु
			अचिन्हित दीर्घ दीर्घ scanlen;

			scanlen = (अचिन्हित दीर्घ दीर्घ)scan_bytes *
				  cmd->stop_arg;

			/* fits whole measure पूर्णांकo one DMA buffer? */
			अगर (dmalen0 > scanlen) अणु
				dmalen0 = scanlen;
				dmalen0 &= ~3L;
			पूर्ण अन्यथा अणु
				/* fits whole measure पूर्णांकo two DMA buffer? */
				अगर (dmalen1 > (scanlen - dmalen0)) अणु
					dmalen1 = scanlen - dmalen0;
					dmalen1 &= ~3L;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* these DMA buffer size will be used */
	devpriv->dma_actbuf = 0;
	dmabuf0->use_size = dmalen0;
	dmabuf1->use_size = dmalen1;

	pci9118_amcc_dma_ena(dev, false);
	pci9118_amcc_setup_dma(dev, 0);
	/* init DMA transfer */
	outl(0x00000000 | AINT_WRITE_COMPL,
	     devpriv->iobase_a + AMCC_OP_REG_INTCSR);
/* outl(0x02000000|AINT_WRITE_COMPL, devpriv->iobase_a+AMCC_OP_REG_INTCSR); */
	pci9118_amcc_dma_ena(dev, true);
	outl(inl(devpriv->iobase_a + AMCC_OP_REG_INTCSR) | EN_A2P_TRANSFERS,
	     devpriv->iobase_a + AMCC_OP_REG_INTCSR);
						/* allow bus mastering */

	वापस 0;
पूर्ण

अटल पूर्णांक pci9118_ai_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci9118_निजी *devpriv = dev->निजी;
	काष्ठा comedi_8254 *pacer = dev->pacer;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक addchans = 0;
	अचिन्हित पूर्णांक scanlen;

	devpriv->ai12_startstop = 0;
	devpriv->ai_flags = cmd->flags;
	devpriv->ai_add_front = 0;
	devpriv->ai_add_back = 0;

	/* prepare क्रम start/stop conditions */
	अगर (cmd->start_src == TRIG_EXT)
		devpriv->ai12_startstop |= START_AI_EXT;
	अगर (cmd->stop_src == TRIG_EXT) अणु
		devpriv->ai_neverending = 1;
		devpriv->ai12_startstop |= STOP_AI_EXT;
	पूर्ण
	अगर (cmd->stop_src == TRIG_NONE)
		devpriv->ai_neverending = 1;
	अगर (cmd->stop_src == TRIG_COUNT)
		devpriv->ai_neverending = 0;

	/*
	 * use additional sample at end of every scan
	 * to satisty DMA 32 bit transfer?
	 */
	devpriv->ai_add_front = 0;
	devpriv->ai_add_back = 0;
	अगर (devpriv->master) अणु
		devpriv->usedma = 1;
		अगर ((cmd->flags & CMDF_WAKE_EOS) &&
		    (cmd->scan_end_arg == 1)) अणु
			अगर (cmd->convert_src == TRIG_NOW)
				devpriv->ai_add_back = 1;
			अगर (cmd->convert_src == TRIG_TIMER) अणु
				devpriv->usedma = 0;
					/*
					 * use INT transfer अगर scanlist
					 * have only one channel
					 */
			पूर्ण
		पूर्ण
		अगर ((cmd->flags & CMDF_WAKE_EOS) &&
		    (cmd->scan_end_arg & 1) &&
		    (cmd->scan_end_arg > 1)) अणु
			अगर (cmd->scan_begin_src == TRIG_FOLLOW) अणु
				devpriv->usedma = 0;
				/*
				 * XXX maybe can be corrected to use 16 bit DMA
				 */
			पूर्ण अन्यथा अणु	/*
					 * well, we must insert one sample
					 * to end of EOS to meet 32 bit transfer
					 */
				devpriv->ai_add_back = 1;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु	/* पूर्णांकerrupt transfer करोn't need any correction */
		devpriv->usedma = 0;
	पूर्ण

	/*
	 * we need software S&H संकेत?
	 * It adds two samples beक्रमe every scan as minimum
	 */
	अगर (cmd->convert_src == TRIG_NOW && devpriv->softsshdelay) अणु
		devpriv->ai_add_front = 2;
		अगर ((devpriv->usedma == 1) && (devpriv->ai_add_back == 1)) अणु
							/* move it to front */
			devpriv->ai_add_front++;
			devpriv->ai_add_back = 0;
		पूर्ण
		अगर (cmd->convert_arg < devpriv->ai_ns_min)
			cmd->convert_arg = devpriv->ai_ns_min;
		addchans = devpriv->softsshdelay / cmd->convert_arg;
		अगर (devpriv->softsshdelay % cmd->convert_arg)
			addchans++;
		अगर (addchans > (devpriv->ai_add_front - 1)) अणु
							/* uff, still लघु */
			devpriv->ai_add_front = addchans + 1;
			अगर (devpriv->usedma == 1)
				अगर ((devpriv->ai_add_front +
				     cmd->chanlist_len +
				     devpriv->ai_add_back) & 1)
					devpriv->ai_add_front++;
							/* round up to 32 bit */
		पूर्ण
	पूर्ण
	/* well, we now know what must be all added */
	scanlen = devpriv->ai_add_front + cmd->chanlist_len +
		  devpriv->ai_add_back;
	/*
	 * what we must take from card in real to have cmd->scan_end_arg
	 * on output?
	 */
	devpriv->ai_n_realscanlen = scanlen *
				    (cmd->scan_end_arg / cmd->chanlist_len);

	अगर (scanlen > s->len_chanlist) अणु
		dev_err(dev->class_dev,
			"range/channel list is too long for actual configuration!\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Configure analog input and load the chanlist.
	 * The acquisition control bits are enabled later.
	 */
	pci9118_set_chanlist(dev, s, cmd->chanlist_len, cmd->chanlist,
			     devpriv->ai_add_front, devpriv->ai_add_back);

	/* Determine acquisition mode and calculate timing */
	devpriv->ai_करो = 0;
	अगर (cmd->scan_begin_src != TRIG_TIMER &&
	    cmd->convert_src == TRIG_TIMER) अणु
		/* cascaded समयrs 1 and 2 are used क्रम convert timing */
		अगर (cmd->scan_begin_src == TRIG_EXT)
			devpriv->ai_करो = 4;
		अन्यथा
			devpriv->ai_करो = 1;

		comedi_8254_cascade_ns_to_समयr(pacer, &cmd->convert_arg,
						devpriv->ai_flags &
						CMDF_ROUND_NEAREST);
		comedi_8254_update_भागisors(pacer);

		devpriv->ai_ctrl |= PCI9118_AI_CTRL_TMRTR;

		अगर (!devpriv->usedma) अणु
			devpriv->ai_ctrl |= PCI9118_AI_CTRL_INT;
			devpriv->पूर्णांक_ctrl |= PCI9118_INT_CTRL_TIMER;
		पूर्ण

		अगर (cmd->scan_begin_src == TRIG_EXT) अणु
			काष्ठा pci9118_dmabuf *dmabuf = &devpriv->dmabuf[0];

			devpriv->ai_cfg |= PCI9118_AI_CFG_AM;
			outl(devpriv->ai_cfg, dev->iobase + PCI9118_AI_CFG_REG);
			comedi_8254_load(pacer, 0, dmabuf->hw >> 1,
					 I8254_MODE0 | I8254_BINARY);
			devpriv->ai_cfg |= PCI9118_AI_CFG_START;
		पूर्ण
	पूर्ण

	अगर (cmd->scan_begin_src == TRIG_TIMER &&
	    cmd->convert_src != TRIG_EXT) अणु
		अगर (!devpriv->usedma) अणु
			dev_err(dev->class_dev,
				"cmd->scan_begin_src=TRIG_TIMER works only with bus mastering!\n");
			वापस -EIO;
		पूर्ण

		/* द्विगुन समयd action */
		devpriv->ai_करो = 2;

		pci9118_calc_भागisors(dev, s,
				      &cmd->scan_begin_arg, &cmd->convert_arg,
				      devpriv->ai_flags,
				      devpriv->ai_n_realscanlen,
				      &pacer->भागisor1,
				      &pacer->भागisor2,
				      devpriv->ai_add_front);

		devpriv->ai_ctrl |= PCI9118_AI_CTRL_TMRTR;
		devpriv->ai_cfg |= PCI9118_AI_CFG_BM | PCI9118_AI_CFG_BS;
		अगर (cmd->convert_src == TRIG_NOW && !devpriv->softsshdelay)
			devpriv->ai_cfg |= PCI9118_AI_CFG_BSSH;
		outl(devpriv->ai_n_realscanlen,
		     dev->iobase + PCI9118_AI_BURST_NUM_REG);
	पूर्ण

	अगर (cmd->scan_begin_src == TRIG_FOLLOW &&
	    cmd->convert_src == TRIG_EXT) अणु
		/* बाह्यal trigger conversion */
		devpriv->ai_करो = 3;

		devpriv->ai_ctrl |= PCI9118_AI_CTRL_EXTM;
	पूर्ण

	अगर (devpriv->ai_करो == 0) अणु
		dev_err(dev->class_dev,
			"Unable to determine acquisition mode! BUG in (*do_cmdtest)?\n");
		वापस -EINVAL;
	पूर्ण

	अगर (devpriv->usedma)
		devpriv->ai_ctrl |= PCI9118_AI_CTRL_DMA;

	/* set शेष config (disable burst and triggers) */
	devpriv->ai_cfg = PCI9118_AI_CFG_PDTRG | PCI9118_AI_CFG_PETRG;
	outl(devpriv->ai_cfg, dev->iobase + PCI9118_AI_CFG_REG);
	udelay(1);
	pci9118_ai_reset_fअगरo(dev);

	/* clear A/D and INT status रेजिस्टरs */
	inl(dev->iobase + PCI9118_AI_STATUS_REG);
	inl(dev->iobase + PCI9118_INT_CTRL_REG);

	devpriv->ai_act_dmapos = 0;

	अगर (devpriv->usedma) अणु
		pci9118_ai_setup_dma(dev, s);

		outl(0x02000000 | AINT_WRITE_COMPL,
		     devpriv->iobase_a + AMCC_OP_REG_INTCSR);
	पूर्ण अन्यथा अणु
		pci9118_amcc_पूर्णांक_ena(dev, true);
	पूर्ण

	/* start async command now or रुको क्रम पूर्णांकernal trigger */
	अगर (cmd->start_src == TRIG_NOW)
		pci9118_ai_cmd_start(dev);
	अन्यथा अगर (cmd->start_src == TRIG_INT)
		s->async->पूर्णांकtrig = pci9118_ai_पूर्णांकtrig;

	/* enable बाह्यal trigger क्रम command start/stop */
	अगर (cmd->start_src == TRIG_EXT || cmd->stop_src == TRIG_EXT)
		pci9118_exttrg_enable(dev, true);

	वापस 0;
पूर्ण

अटल पूर्णांक pci9118_ai_cmdtest(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा pci9118_निजी *devpriv = dev->निजी;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक arg;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src,
					TRIG_NOW | TRIG_EXT | TRIG_INT);

	flags = TRIG_FOLLOW;
	अगर (devpriv->master)
		flags |= TRIG_TIMER | TRIG_EXT;
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, flags);

	flags = TRIG_TIMER | TRIG_EXT;
	अगर (devpriv->master)
		flags |= TRIG_NOW;
	err |= comedi_check_trigger_src(&cmd->convert_src, flags);

	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src,
					TRIG_COUNT | TRIG_NONE | TRIG_EXT);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->convert_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (cmd->start_src == TRIG_EXT && cmd->scan_begin_src == TRIG_EXT)
		err |= -EINVAL;

	अगर ((cmd->scan_begin_src & (TRIG_TIMER | TRIG_EXT)) &&
	    (!(cmd->convert_src & (TRIG_TIMER | TRIG_NOW))))
		err |= -EINVAL;

	अगर ((cmd->scan_begin_src == TRIG_FOLLOW) &&
	    (!(cmd->convert_src & (TRIG_TIMER | TRIG_EXT))))
		err |= -EINVAL;

	अगर (cmd->stop_src == TRIG_EXT && cmd->scan_begin_src == TRIG_EXT)
		err |= -EINVAL;

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	चयन (cmd->start_src) अणु
	हाल TRIG_NOW:
	हाल TRIG_EXT:
		err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
		अवरोध;
	हाल TRIG_INT:
		/* start_arg is the पूर्णांकernal trigger (any value) */
		अवरोध;
	पूर्ण

	अगर (cmd->scan_begin_src & (TRIG_FOLLOW | TRIG_EXT))
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);

	अगर ((cmd->scan_begin_src == TRIG_TIMER) &&
	    (cmd->convert_src == TRIG_TIMER) && (cmd->scan_end_arg == 1)) अणु
		cmd->scan_begin_src = TRIG_FOLLOW;
		cmd->convert_arg = cmd->scan_begin_arg;
		cmd->scan_begin_arg = 0;
	पूर्ण

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
						    devpriv->ai_ns_min);
	पूर्ण

	अगर (cmd->scan_begin_src == TRIG_EXT) अणु
		अगर (cmd->scan_begin_arg) अणु
			cmd->scan_begin_arg = 0;
			err |= -EINVAL;
			err |= comedi_check_trigger_arg_max(&cmd->scan_end_arg,
							    65535);
		पूर्ण
	पूर्ण

	अगर (cmd->convert_src & (TRIG_TIMER | TRIG_NOW)) अणु
		err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
						    devpriv->ai_ns_min);
	पूर्ण

	अगर (cmd->convert_src == TRIG_EXT)
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	err |= comedi_check_trigger_arg_min(&cmd->chanlist_len, 1);

	err |= comedi_check_trigger_arg_min(&cmd->scan_end_arg,
					    cmd->chanlist_len);

	अगर ((cmd->scan_end_arg % cmd->chanlist_len)) अणु
		cmd->scan_end_arg =
		    cmd->chanlist_len * (cmd->scan_end_arg / cmd->chanlist_len);
		err |= -EINVAL;
	पूर्ण

	अगर (err)
		वापस 3;

	/* step 4: fix up any arguments */

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		arg = cmd->scan_begin_arg;
		comedi_8254_cascade_ns_to_समयr(dev->pacer, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);
	पूर्ण

	अगर (cmd->convert_src & (TRIG_TIMER | TRIG_NOW)) अणु
		arg = cmd->convert_arg;
		comedi_8254_cascade_ns_to_समयr(dev->pacer, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg);

		अगर (cmd->scan_begin_src == TRIG_TIMER &&
		    cmd->convert_src == TRIG_NOW) अणु
			अगर (cmd->convert_arg == 0) अणु
				arg = devpriv->ai_ns_min *
				      (cmd->scan_end_arg + 2);
			पूर्ण अन्यथा अणु
				arg = cmd->convert_arg * cmd->chanlist_len;
			पूर्ण
			err |= comedi_check_trigger_arg_min(
				&cmd->scan_begin_arg, arg);
		पूर्ण
	पूर्ण

	अगर (err)
		वापस 4;

	/* Step 5: check channel list अगर it exists */

	अगर (cmd->chanlist)
		err |= pci9118_ai_check_chanlist(dev, s, cmd);

	अगर (err)
		वापस 5;

	वापस 0;
पूर्ण

अटल पूर्णांक pci9118_ai_eoc(काष्ठा comedi_device *dev,
			  काष्ठा comedi_subdevice *s,
			  काष्ठा comedi_insn *insn,
			  अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inl(dev->iobase + PCI9118_AI_STATUS_REG);
	अगर (status & PCI9118_AI_STATUS_ADRDY)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल व्योम pci9118_ai_start_conv(काष्ठा comedi_device *dev)
अणु
	/* writing any value triggers an A/D conversion */
	outl(0, dev->iobase + PCI9118_SOFTTRG_REG);
पूर्ण

अटल पूर्णांक pci9118_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	काष्ठा pci9118_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;
	पूर्णांक i;

       /*
	* Configure analog input based on the chanspec.
	* Acqusition is software controlled without पूर्णांकerrupts.
	*/
	pci9118_set_chanlist(dev, s, 1, &insn->chanspec, 0, 0);

	/* set शेष config (disable burst and triggers) */
	devpriv->ai_cfg = PCI9118_AI_CFG_PDTRG | PCI9118_AI_CFG_PETRG;
	outl(devpriv->ai_cfg, dev->iobase + PCI9118_AI_CFG_REG);

	pci9118_ai_reset_fअगरo(dev);

	क्रम (i = 0; i < insn->n; i++) अणु
		pci9118_ai_start_conv(dev);

		ret = comedi_समयout(dev, s, insn, pci9118_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		val = inl(dev->iobase + PCI9118_AI_FIFO_REG);
		अगर (s->maxdata == 0xffff)
			data[i] = (val & 0xffff) ^ 0x8000;
		अन्यथा
			data[i] = (val >> 4) & 0xfff;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci9118_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];
		outl(val, dev->iobase + PCI9118_AO_REG(chan));
	पूर्ण
	s->पढ़ोback[chan] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci9118_di_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	/*
	 * The digital inमाला_दो and outमाला_दो share the पढ़ो रेजिस्टर.
	 * bits [7:4] are the digital outमाला_दो
	 * bits [3:0] are the digital inमाला_दो
	 */
	data[1] = inl(dev->iobase + PCI9118_DIO_REG) & 0xf;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci9118_करो_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	/*
	 * The digital outमाला_दो are set with the same रेजिस्टर that
	 * the digital inमाला_दो and outमाला_दो are पढ़ो from. But the
	 * outमाला_दो are set with bits [3:0] so we can simply ग_लिखो
	 * the s->state to set them.
	 */
	अगर (comedi_dio_update_state(s, data))
		outl(s->state, dev->iobase + PCI9118_DIO_REG);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल व्योम pci9118_reset(काष्ठा comedi_device *dev)
अणु
	/* reset analog input subप्रणाली */
	outl(0, dev->iobase + PCI9118_INT_CTRL_REG);
	outl(0, dev->iobase + PCI9118_AI_CTRL_REG);
	outl(0, dev->iobase + PCI9118_AI_CFG_REG);
	pci9118_ai_reset_fअगरo(dev);

	/* clear any pending पूर्णांकerrupts and status */
	inl(dev->iobase + PCI9118_INT_CTRL_REG);
	inl(dev->iobase + PCI9118_AI_STATUS_REG);

	/* reset DMA and scan queue */
	outl(0, dev->iobase + PCI9118_AI_BURST_NUM_REG);
	outl(1, dev->iobase + PCI9118_AI_AUTOSCAN_MODE_REG);
	outl(2, dev->iobase + PCI9118_AI_AUTOSCAN_MODE_REG);

	/* reset analog outमाला_दो to 0V */
	outl(2047, dev->iobase + PCI9118_AO_REG(0));
	outl(2047, dev->iobase + PCI9118_AO_REG(1));
पूर्ण

अटल काष्ठा pci_dev *pci9118_find_pci(काष्ठा comedi_device *dev,
					काष्ठा comedi_devconfig *it)
अणु
	काष्ठा pci_dev *pcidev = शून्य;
	पूर्णांक bus = it->options[0];
	पूर्णांक slot = it->options[1];

	क्रम_each_pci_dev(pcidev) अणु
		अगर (pcidev->venकरोr != PCI_VENDOR_ID_AMCC)
			जारी;
		अगर (pcidev->device != 0x80d9)
			जारी;
		अगर (bus || slot) अणु
			/* requested particular bus/slot */
			अगर (pcidev->bus->number != bus ||
			    PCI_SLOT(pcidev->devfn) != slot)
				जारी;
		पूर्ण
		वापस pcidev;
	पूर्ण
	dev_err(dev->class_dev,
		"no supported board found! (req. bus/slot : %d/%d)\n",
		bus, slot);
	वापस शून्य;
पूर्ण

अटल व्योम pci9118_alloc_dma(काष्ठा comedi_device *dev)
अणु
	काष्ठा pci9118_निजी *devpriv = dev->निजी;
	काष्ठा pci9118_dmabuf *dmabuf;
	पूर्णांक order;
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		dmabuf = &devpriv->dmabuf[i];
		क्रम (order = 2; order >= 0; order--) अणु
			dmabuf->virt =
			    dma_alloc_coherent(dev->hw_dev, PAGE_SIZE << order,
					       &dmabuf->hw, GFP_KERNEL);
			अगर (dmabuf->virt)
				अवरोध;
		पूर्ण
		अगर (!dmabuf->virt)
			अवरोध;
		dmabuf->size = PAGE_SIZE << order;

		अगर (i == 0)
			devpriv->master = 1;
		अगर (i == 1)
			devpriv->dma_द्विगुनbuf = 1;
	पूर्ण
पूर्ण

अटल व्योम pci9118_मुक्त_dma(काष्ठा comedi_device *dev)
अणु
	काष्ठा pci9118_निजी *devpriv = dev->निजी;
	काष्ठा pci9118_dmabuf *dmabuf;
	पूर्णांक i;

	अगर (!devpriv)
		वापस;

	क्रम (i = 0; i < 2; i++) अणु
		dmabuf = &devpriv->dmabuf[i];
		अगर (dmabuf->virt) अणु
			dma_मुक्त_coherent(dev->hw_dev, dmabuf->size,
					  dmabuf->virt, dmabuf->hw);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक pci9118_common_attach(काष्ठा comedi_device *dev,
				 पूर्णांक ext_mux, पूर्णांक softsshdelay)
अणु
	स्थिर काष्ठा pci9118_boardinfo *board = dev->board_ptr;
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा pci9118_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;
	पूर्णांक i;
	u16 u16w;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;
	pci_set_master(pcidev);

	devpriv->iobase_a = pci_resource_start(pcidev, 0);
	dev->iobase = pci_resource_start(pcidev, 2);

	dev->pacer = comedi_8254_init(dev->iobase + PCI9118_TIMER_BASE,
				      I8254_OSC_BASE_4MHZ, I8254_IO32, 0);
	अगर (!dev->pacer)
		वापस -ENOMEM;

	pci9118_reset(dev);

	अगर (pcidev->irq) अणु
		ret = request_irq(pcidev->irq, pci9118_पूर्णांकerrupt, IRQF_SHARED,
				  dev->board_name, dev);
		अगर (ret == 0) अणु
			dev->irq = pcidev->irq;

			pci9118_alloc_dma(dev);
		पूर्ण
	पूर्ण

	अगर (ext_mux > 0) अणु
		अगर (ext_mux > 256)
			ext_mux = 256;	/* max 256 channels! */
		अगर (softsshdelay > 0)
			अगर (ext_mux > 128)
				ext_mux = 128;
		devpriv->usemux = 1;
	पूर्ण अन्यथा अणु
		devpriv->usemux = 0;
	पूर्ण

	अगर (softsshdelay < 0) अणु
		/* select sample&hold संकेत polarity */
		devpriv->softsshdelay = -softsshdelay;
		devpriv->softsshsample = 0x80;
		devpriv->softsshhold = 0x00;
	पूर्ण अन्यथा अणु
		devpriv->softsshdelay = softsshdelay;
		devpriv->softsshsample = 0x00;
		devpriv->softsshhold = 0x80;
	पूर्ण

	pci_पढ़ो_config_word(pcidev, PCI_COMMAND, &u16w);
	pci_ग_लिखो_config_word(pcidev, PCI_COMMAND, u16w | 64);
				/* Enable parity check क्रम parity error */

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_COMMON | SDF_GROUND | SDF_DIFF;
	s->n_chan	= (devpriv->usemux) ? ext_mux : 16;
	s->maxdata	= board->ai_is_16bit ? 0xffff : 0x0fff;
	s->range_table	= board->is_hg ? &pci9118hg_ai_range
				       : &pci9118_ai_range;
	s->insn_पढ़ो	= pci9118_ai_insn_पढ़ो;
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->len_chanlist	= 255;
		s->करो_cmdtest	= pci9118_ai_cmdtest;
		s->करो_cmd	= pci9118_ai_cmd;
		s->cancel	= pci9118_ai_cancel;
		s->munge	= pci9118_ai_munge;
	पूर्ण

	अगर (s->maxdata == 0xffff) अणु
		/*
		 * 16-bit samples are from an ADS7805 A/D converter.
		 * Minimum sampling rate is 10us.
		 */
		devpriv->ai_ns_min = 10000;
	पूर्ण अन्यथा अणु
		/*
		 * 12-bit samples are from an ADS7800 A/D converter.
		 * Minimum sampling rate is 3us.
		 */
		devpriv->ai_ns_min = 3000;
	पूर्ण

	/* Analog Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE | SDF_GROUND | SDF_COMMON;
	s->n_chan	= 2;
	s->maxdata	= 0x0fff;
	s->range_table	= &range_bipolar10;
	s->insn_ग_लिखो	= pci9118_ao_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	/* the analog outमाला_दो were reset to 0V, make the पढ़ोback match */
	क्रम (i = 0; i < s->n_chan; i++)
		s->पढ़ोback[i] = 2047;

	/* Digital Input subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pci9118_di_insn_bits;

	/* Digital Output subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pci9118_करो_insn_bits;

	/* get the current state of the digital outमाला_दो */
	s->state = inl(dev->iobase + PCI9118_DIO_REG) >> 4;

	वापस 0;
पूर्ण

अटल पूर्णांक pci9118_attach(काष्ठा comedi_device *dev,
			  काष्ठा comedi_devconfig *it)
अणु
	काष्ठा pci_dev *pcidev;
	पूर्णांक ext_mux, softsshdelay;

	ext_mux = it->options[2];
	softsshdelay = it->options[4];

	pcidev = pci9118_find_pci(dev, it);
	अगर (!pcidev)
		वापस -EIO;
	comedi_set_hw_dev(dev, &pcidev->dev);

	वापस pci9118_common_attach(dev, ext_mux, softsshdelay);
पूर्ण

अटल पूर्णांक pci9118_स्वतः_attach(काष्ठा comedi_device *dev,
			       अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा pci9118_boardinfo *board = शून्य;

	अगर (context < ARRAY_SIZE(pci9118_boards))
		board = &pci9118_boards[context];
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	/*
	 * Need to 'get' the PCI device to match the 'put' in pci9118_detach().
	 * (The 'put' also matches the implicit 'get' by pci9118_find_pci().)
	 */
	pci_dev_get(pcidev);
	/* no बाह्यal mux, no sample-hold delay */
	वापस pci9118_common_attach(dev, 0, 0);
पूर्ण

अटल व्योम pci9118_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);

	अगर (dev->iobase)
		pci9118_reset(dev);
	comedi_pci_detach(dev);
	pci9118_मुक्त_dma(dev);
	pci_dev_put(pcidev);
पूर्ण

अटल काष्ठा comedi_driver adl_pci9118_driver = अणु
	.driver_name	= "adl_pci9118",
	.module		= THIS_MODULE,
	.attach		= pci9118_attach,
	.स्वतः_attach	= pci9118_स्वतः_attach,
	.detach		= pci9118_detach,
	.num_names	= ARRAY_SIZE(pci9118_boards),
	.board_name	= &pci9118_boards[0].name,
	.offset		= माप(काष्ठा pci9118_boardinfo),
पूर्ण;

अटल पूर्णांक adl_pci9118_pci_probe(काष्ठा pci_dev *dev,
				 स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &adl_pci9118_driver,
				      id->driver_data);
पूर्ण

/* FIXME: All the supported board types have the same device ID! */
अटल स्थिर काष्ठा pci_device_id adl_pci9118_pci_table[] = अणु
	अणु PCI_VDEVICE(AMCC, 0x80d9), BOARD_PCI9118DG पूर्ण,
/*	अणु PCI_VDEVICE(AMCC, 0x80d9), BOARD_PCI9118HG पूर्ण, */
/*	अणु PCI_VDEVICE(AMCC, 0x80d9), BOARD_PCI9118HR पूर्ण, */
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, adl_pci9118_pci_table);

अटल काष्ठा pci_driver adl_pci9118_pci_driver = अणु
	.name		= "adl_pci9118",
	.id_table	= adl_pci9118_pci_table,
	.probe		= adl_pci9118_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(adl_pci9118_driver, adl_pci9118_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
