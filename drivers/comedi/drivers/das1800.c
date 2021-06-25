<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Comedi driver क्रम Keithley DAS-1700/DAS-1800 series boards
 * Copyright (C) 2000 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: das1800
 * Description: Keithley Metrabyte DAS1800 (& compatibles)
 * Author: Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 * Devices: [Keithley Metrabyte] DAS-1701ST (das-1701st),
 *   DAS-1701ST-DA (das-1701st-da), DAS-1701/AO (das-1701ao),
 *   DAS-1702ST (das-1702st), DAS-1702ST-DA (das-1702st-da),
 *   DAS-1702HR (das-1702hr), DAS-1702HR-DA (das-1702hr-da),
 *   DAS-1702/AO (das-1702ao), DAS-1801ST (das-1801st),
 *   DAS-1801ST-DA (das-1801st-da), DAS-1801HC (das-1801hc),
 *   DAS-1801AO (das-1801ao), DAS-1802ST (das-1802st),
 *   DAS-1802ST-DA (das-1802st-da), DAS-1802HR (das-1802hr),
 *   DAS-1802HR-DA (das-1802hr-da), DAS-1802HC (das-1802hc),
 *   DAS-1802AO (das-1802ao)
 * Status: works
 *
 * Configuration options:
 *   [0] - I/O port base address
 *   [1] - IRQ (optional, required क्रम analog input cmd support)
 *   [2] - DMA0 (optional, requires irq)
 *   [3] - DMA1 (optional, requires irq and dma0)
 *
 * analog input cmd triggers supported:
 *
 *   start_src		TRIG_NOW	command starts immediately
 *			TRIG_EXT	command starts on बाह्यal pin TGIN
 *
 *   scan_begin_src	TRIG_FOLLOW	paced/बाह्यal scans start immediately
 *			TRIG_TIMER	burst scans start periodically
 *			TRIG_EXT	burst scans start on बाह्यal pin XPCLK
 *
 *   scan_end_src	TRIG_COUNT	scan ends after last channel
 *
 *   convert_src	TRIG_TIMER	paced/burst conversions are समयd
 *			TRIG_EXT	conversions on बाह्यal pin XPCLK
 *					(requires scan_begin_src == TRIG_FOLLOW)
 *
 *   stop_src		TRIG_COUNT	command stops after stop_arg scans
 *			TRIG_EXT	command stops on बाह्यal pin TGIN
 *			TRIG_NONE	command runs until canceled
 *
 * If TRIG_EXT is used क्रम both the start_src and stop_src, the first TGIN
 * trigger starts the command, and the second trigger will stop it. If only
 * one is TRIG_EXT, the first trigger will either stop or start the command.
 * The बाह्यal pin TGIN is normally set क्रम negative edge triggering. It
 * can be set to positive edge with the CR_INVERT flag. If TRIG_EXT is used
 * क्रम both the start_src and stop_src they must have the same polarity.
 *
 * Minimum conversion speed is limited to 64 microseconds (convert_arg <= 64000)
 * क्रम 'burst' scans. This limitation does not apply for 'paced' scans. The
 * maximum conversion speed is limited by the board (convert_arg >= ai_speed).
 * Maximum conversion speeds are not always achievable depending on the
 * board setup (see user manual).
 *
 * NOTES:
 * Only the DAS-1801ST has been tested by me.
 * Unipolar and bipolar ranges cannot be mixed in the channel/gain list.
 *
 * The waveक्रमm analog output on the 'ao' cards is not supported.
 * If you need it, send me (Frank Hess) an email.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>

#समावेश "../comedidev.h"

#समावेश "comedi_isadma.h"
#समावेश "comedi_8254.h"

/* misc. defines */
#घोषणा DAS1800_SIZE           16	/* uses 16 io addresses */
#घोषणा FIFO_SIZE              1024	/*  1024 sample fअगरo */
#घोषणा DMA_BUF_SIZE           0x1ff00	/*  size in bytes of dma buffers */

/* Registers क्रम the das1800 */
#घोषणा DAS1800_FIFO            0x0
#घोषणा DAS1800_QRAM            0x0
#घोषणा DAS1800_DAC             0x0
#घोषणा DAS1800_SELECT          0x2
#घोषणा   ADC                     0x0
#घोषणा   QRAM                    0x1
#घोषणा   DAC(a)                  (0x2 + a)
#घोषणा DAS1800_DIGITAL         0x3
#घोषणा DAS1800_CONTROL_A       0x4
#घोषणा   FFEN                    0x1
#घोषणा   CGEN                    0x4
#घोषणा   CGSL                    0x8
#घोषणा   TGEN                    0x10
#घोषणा   TGSL                    0x20
#घोषणा   TGPL                    0x40
#घोषणा   ATEN                    0x80
#घोषणा DAS1800_CONTROL_B       0x5
#घोषणा   DMA_CH5                 0x1
#घोषणा   DMA_CH6                 0x2
#घोषणा   DMA_CH7                 0x3
#घोषणा   DMA_CH5_CH6             0x5
#घोषणा   DMA_CH6_CH7             0x6
#घोषणा   DMA_CH7_CH5             0x7
#घोषणा   DMA_ENABLED             0x3
#घोषणा   DMA_DUAL                0x4
#घोषणा   IRQ3                    0x8
#घोषणा   IRQ5                    0x10
#घोषणा   IRQ7                    0x18
#घोषणा   IRQ10                   0x28
#घोषणा   IRQ11                   0x30
#घोषणा   IRQ15                   0x38
#घोषणा   FIMD                    0x40
#घोषणा DAS1800_CONTROL_C       0X6
#घोषणा   IPCLK                   0x1
#घोषणा   XPCLK                   0x3
#घोषणा   BMDE                    0x4
#घोषणा   CMEN                    0x8
#घोषणा   UQEN                    0x10
#घोषणा   SD                      0x40
#घोषणा   UB                      0x80
#घोषणा DAS1800_STATUS          0x7
#घोषणा   INT                     0x1
#घोषणा   DMATC                   0x2
#घोषणा   CT0TC                   0x8
#घोषणा   OVF                     0x10
#घोषणा   FHF                     0x20
#घोषणा   FNE                     0x40
#घोषणा   CVEN                    0x80
#घोषणा   CVEN_MASK               0x40
#घोषणा   CLEAR_INTR_MASK         (CVEN_MASK | 0x1f)
#घोषणा DAS1800_BURST_LENGTH    0x8
#घोषणा DAS1800_BURST_RATE      0x9
#घोषणा DAS1800_QRAM_ADDRESS    0xa
#घोषणा DAS1800_COUNTER         0xc

#घोषणा IOBASE2                   0x400

अटल स्थिर काष्ठा comedi_lrange das1801_ai_range = अणु
	8, अणु
		BIP_RANGE(5),		/* bipolar gain = 1 */
		BIP_RANGE(1),		/* bipolar gain = 10 */
		BIP_RANGE(0.1),		/* bipolar gain = 50 */
		BIP_RANGE(0.02),	/* bipolar gain = 250 */
		UNI_RANGE(5),		/* unipolar gain = 1 */
		UNI_RANGE(1),		/* unipolar gain = 10 */
		UNI_RANGE(0.1),		/* unipolar gain = 50 */
		UNI_RANGE(0.02)		/* unipolar gain = 250 */
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange das1802_ai_range = अणु
	8, अणु
		BIP_RANGE(10),		/* bipolar gain = 1 */
		BIP_RANGE(5),		/* bipolar gain = 2 */
		BIP_RANGE(2.5),		/* bipolar gain = 4 */
		BIP_RANGE(1.25),	/* bipolar gain = 8 */
		UNI_RANGE(10),		/* unipolar gain = 1 */
		UNI_RANGE(5),		/* unipolar gain = 2 */
		UNI_RANGE(2.5),		/* unipolar gain = 4 */
		UNI_RANGE(1.25)		/* unipolar gain = 8 */
	पूर्ण
पूर्ण;

/*
 * The waveक्रमm analog outमाला_दो on the 'ao' boards are not currently
 * supported. They have a comedi_lrange of:
 * अणु 2, अणु BIP_RANGE(10), BIP_RANGE(5) पूर्ण पूर्ण
 */

क्रमागत das1800_boardid अणु
	BOARD_DAS1701ST,
	BOARD_DAS1701ST_DA,
	BOARD_DAS1702ST,
	BOARD_DAS1702ST_DA,
	BOARD_DAS1702HR,
	BOARD_DAS1702HR_DA,
	BOARD_DAS1701AO,
	BOARD_DAS1702AO,
	BOARD_DAS1801ST,
	BOARD_DAS1801ST_DA,
	BOARD_DAS1802ST,
	BOARD_DAS1802ST_DA,
	BOARD_DAS1802HR,
	BOARD_DAS1802HR_DA,
	BOARD_DAS1801HC,
	BOARD_DAS1802HC,
	BOARD_DAS1801AO,
	BOARD_DAS1802AO
पूर्ण;

/* board probe id values (hi byte of the digital input रेजिस्टर) */
#घोषणा DAS1800_ID_ST_DA		0x3
#घोषणा DAS1800_ID_HR_DA		0x4
#घोषणा DAS1800_ID_AO			0x5
#घोषणा DAS1800_ID_HR			0x6
#घोषणा DAS1800_ID_ST			0x7
#घोषणा DAS1800_ID_HC			0x8

काष्ठा das1800_board अणु
	स्थिर अक्षर *name;
	अचिन्हित अक्षर id;
	अचिन्हित पूर्णांक ai_speed;
	अचिन्हित पूर्णांक is_01_series:1;
पूर्ण;

अटल स्थिर काष्ठा das1800_board das1800_boards[] = अणु
	[BOARD_DAS1701ST] = अणु
		.name		= "das-1701st",
		.id		= DAS1800_ID_ST,
		.ai_speed	= 6250,
		.is_01_series	= 1,
	पूर्ण,
	[BOARD_DAS1701ST_DA] = अणु
		.name		= "das-1701st-da",
		.id		= DAS1800_ID_ST_DA,
		.ai_speed	= 6250,
		.is_01_series	= 1,
	पूर्ण,
	[BOARD_DAS1702ST] = अणु
		.name		= "das-1702st",
		.id		= DAS1800_ID_ST,
		.ai_speed	= 6250,
	पूर्ण,
	[BOARD_DAS1702ST_DA] = अणु
		.name		= "das-1702st-da",
		.id		= DAS1800_ID_ST_DA,
		.ai_speed	= 6250,
	पूर्ण,
	[BOARD_DAS1702HR] = अणु
		.name		= "das-1702hr",
		.id		= DAS1800_ID_HR,
		.ai_speed	= 20000,
	पूर्ण,
	[BOARD_DAS1702HR_DA] = अणु
		.name		= "das-1702hr-da",
		.id		= DAS1800_ID_HR_DA,
		.ai_speed	= 20000,
	पूर्ण,
	[BOARD_DAS1701AO] = अणु
		.name		= "das-1701ao",
		.id		= DAS1800_ID_AO,
		.ai_speed	= 6250,
		.is_01_series	= 1,
	पूर्ण,
	[BOARD_DAS1702AO] = अणु
		.name		= "das-1702ao",
		.id		= DAS1800_ID_AO,
		.ai_speed	= 6250,
	पूर्ण,
	[BOARD_DAS1801ST] = अणु
		.name		= "das-1801st",
		.id		= DAS1800_ID_ST,
		.ai_speed	= 3000,
		.is_01_series	= 1,
	पूर्ण,
	[BOARD_DAS1801ST_DA] = अणु
		.name		= "das-1801st-da",
		.id		= DAS1800_ID_ST_DA,
		.ai_speed	= 3000,
		.is_01_series	= 1,
	पूर्ण,
	[BOARD_DAS1802ST] = अणु
		.name		= "das-1802st",
		.id		= DAS1800_ID_ST,
		.ai_speed	= 3000,
	पूर्ण,
	[BOARD_DAS1802ST_DA] = अणु
		.name		= "das-1802st-da",
		.id		= DAS1800_ID_ST_DA,
		.ai_speed	= 3000,
	पूर्ण,
	[BOARD_DAS1802HR] = अणु
		.name		= "das-1802hr",
		.id		= DAS1800_ID_HR,
		.ai_speed	= 10000,
	पूर्ण,
	[BOARD_DAS1802HR_DA] = अणु
		.name		= "das-1802hr-da",
		.id		= DAS1800_ID_HR_DA,
		.ai_speed	= 10000,
	पूर्ण,
	[BOARD_DAS1801HC] = अणु
		.name		= "das-1801hc",
		.id		= DAS1800_ID_HC,
		.ai_speed	= 3000,
		.is_01_series	= 1,
	पूर्ण,
	[BOARD_DAS1802HC] = अणु
		.name		= "das-1802hc",
		.id		= DAS1800_ID_HC,
		.ai_speed	= 3000,
	पूर्ण,
	[BOARD_DAS1801AO] = अणु
		.name		= "das-1801ao",
		.id		= DAS1800_ID_AO,
		.ai_speed	= 3000,
		.is_01_series	= 1,
	पूर्ण,
	[BOARD_DAS1802AO] = अणु
		.name		= "das-1802ao",
		.id		= DAS1800_ID_AO,
		.ai_speed	= 3000,
	पूर्ण,
पूर्ण;

काष्ठा das1800_निजी अणु
	काष्ठा comedi_isadma *dma;
	पूर्णांक irq_dma_bits;
	पूर्णांक dma_bits;
	अचिन्हित लघु *fअगरo_buf;
	अचिन्हित दीर्घ iobase2;
	bool ai_is_unipolar;
पूर्ण;

अटल व्योम das1800_ai_munge(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     व्योम *data, अचिन्हित पूर्णांक num_bytes,
			     अचिन्हित पूर्णांक start_chan_index)
अणु
	काष्ठा das1800_निजी *devpriv = dev->निजी;
	अचिन्हित लघु *array = data;
	अचिन्हित पूर्णांक num_samples = comedi_bytes_to_samples(s, num_bytes);
	अचिन्हित पूर्णांक i;

	अगर (devpriv->ai_is_unipolar)
		वापस;

	क्रम (i = 0; i < num_samples; i++)
		array[i] = comedi_offset_munge(s, array[i]);
पूर्ण

अटल व्योम das1800_handle_fअगरo_half_full(काष्ठा comedi_device *dev,
					  काष्ठा comedi_subdevice *s)
अणु
	काष्ठा das1800_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक nsamples = comedi_nsamples_left(s, FIFO_SIZE / 2);

	insw(dev->iobase + DAS1800_FIFO, devpriv->fअगरo_buf, nsamples);
	comedi_buf_ग_लिखो_samples(s, devpriv->fअगरo_buf, nsamples);
पूर्ण

अटल व्योम das1800_handle_fअगरo_not_empty(काष्ठा comedi_device *dev,
					  काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित लघु dpnt;

	जबतक (inb(dev->iobase + DAS1800_STATUS) & FNE) अणु
		dpnt = inw(dev->iobase + DAS1800_FIFO);
		comedi_buf_ग_लिखो_samples(s, &dpnt, 1);

		अगर (cmd->stop_src == TRIG_COUNT &&
		    s->async->scans_करोne >= cmd->stop_arg)
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम das1800_flush_dma_channel(काष्ठा comedi_device *dev,
				      काष्ठा comedi_subdevice *s,
				      काष्ठा comedi_isadma_desc *desc)
अणु
	अचिन्हित पूर्णांक residue = comedi_isadma_disable(desc->chan);
	अचिन्हित पूर्णांक nbytes = desc->size - residue;
	अचिन्हित पूर्णांक nsamples;

	/*  figure out how many poपूर्णांकs to पढ़ो */
	nsamples = comedi_bytes_to_samples(s, nbytes);
	nsamples = comedi_nsamples_left(s, nsamples);

	comedi_buf_ग_लिखो_samples(s, desc->virt_addr, nsamples);
पूर्ण

अटल व्योम das1800_flush_dma(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s)
अणु
	काष्ठा das1800_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_isadma_desc *desc = &dma->desc[dma->cur_dma];
	स्थिर पूर्णांक dual_dma = devpriv->irq_dma_bits & DMA_DUAL;

	das1800_flush_dma_channel(dev, s, desc);

	अगर (dual_dma) अणु
		/*  चयन to other channel and flush it */
		dma->cur_dma = 1 - dma->cur_dma;
		desc = &dma->desc[dma->cur_dma];
		das1800_flush_dma_channel(dev, s, desc);
	पूर्ण

	/*  get any reमुख्यing samples in fअगरo */
	das1800_handle_fअगरo_not_empty(dev, s);
पूर्ण

अटल व्योम das1800_handle_dma(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s, अचिन्हित पूर्णांक status)
अणु
	काष्ठा das1800_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_isadma_desc *desc = &dma->desc[dma->cur_dma];
	स्थिर पूर्णांक dual_dma = devpriv->irq_dma_bits & DMA_DUAL;

	das1800_flush_dma_channel(dev, s, desc);

	/* re-enable dma channel */
	comedi_isadma_program(desc);

	अगर (status & DMATC) अणु
		/*  clear DMATC पूर्णांकerrupt bit */
		outb(CLEAR_INTR_MASK & ~DMATC, dev->iobase + DAS1800_STATUS);
		/*  चयन dma channels क्रम next समय, अगर appropriate */
		अगर (dual_dma)
			dma->cur_dma = 1 - dma->cur_dma;
	पूर्ण
पूर्ण

अटल पूर्णांक das1800_ai_cancel(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s)
अणु
	काष्ठा das1800_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_isadma_desc *desc;
	पूर्णांक i;

	/* disable and stop conversions */
	outb(0x0, dev->iobase + DAS1800_STATUS);
	outb(0x0, dev->iobase + DAS1800_CONTROL_B);
	outb(0x0, dev->iobase + DAS1800_CONTROL_A);

	अगर (dma) अणु
		क्रम (i = 0; i < 2; i++) अणु
			desc = &dma->desc[i];
			अगर (desc->chan)
				comedi_isadma_disable(desc->chan);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम das1800_ai_handler(काष्ठा comedi_device *dev)
अणु
	काष्ठा das1800_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित पूर्णांक status = inb(dev->iobase + DAS1800_STATUS);

	/* select adc रेजिस्टर (spinlock is alपढ़ोy held) */
	outb(ADC, dev->iobase + DAS1800_SELECT);

	/* get samples with dma, fअगरo, or polled as necessary */
	अगर (devpriv->irq_dma_bits & DMA_ENABLED)
		das1800_handle_dma(dev, s, status);
	अन्यथा अगर (status & FHF)
		das1800_handle_fअगरo_half_full(dev, s);
	अन्यथा अगर (status & FNE)
		das1800_handle_fअगरo_not_empty(dev, s);

	/* अगर the card's fअगरo has overflowed */
	अगर (status & OVF) अणु
		/*  clear OVF पूर्णांकerrupt bit */
		outb(CLEAR_INTR_MASK & ~OVF, dev->iobase + DAS1800_STATUS);
		dev_err(dev->class_dev, "FIFO overflow\n");
		async->events |= COMEDI_CB_ERROR;
		comedi_handle_events(dev, s);
		वापस;
	पूर्ण
	/*  stop taking data अगर appropriate */
	/* stop_src TRIG_EXT */
	अगर (status & CT0TC) अणु
		/*  clear CT0TC पूर्णांकerrupt bit */
		outb(CLEAR_INTR_MASK & ~CT0TC, dev->iobase + DAS1800_STATUS);
		/* get all reमुख्यing samples beक्रमe quitting */
		अगर (devpriv->irq_dma_bits & DMA_ENABLED)
			das1800_flush_dma(dev, s);
		अन्यथा
			das1800_handle_fअगरo_not_empty(dev, s);
		async->events |= COMEDI_CB_EOA;
	पूर्ण अन्यथा अगर (cmd->stop_src == TRIG_COUNT &&
		   async->scans_करोne >= cmd->stop_arg) अणु
		async->events |= COMEDI_CB_EOA;
	पूर्ण

	comedi_handle_events(dev, s);
पूर्ण

अटल पूर्णांक das1800_ai_poll(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * Protects the indirect addressing selected by DAS1800_SELECT
	 * in das1800_ai_handler() also prevents race with das1800_पूर्णांकerrupt().
	 */
	spin_lock_irqsave(&dev->spinlock, flags);

	das1800_ai_handler(dev);

	spin_unlock_irqrestore(&dev->spinlock, flags);

	वापस comedi_buf_n_bytes_पढ़ोy(s);
पूर्ण

अटल irqवापस_t das1800_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	अचिन्हित पूर्णांक status;

	अगर (!dev->attached) अणु
		dev_err(dev->class_dev, "premature interrupt\n");
		वापस IRQ_HANDLED;
	पूर्ण

	/*
	 * Protects the indirect addressing selected by DAS1800_SELECT
	 * in das1800_ai_handler() also prevents race with das1800_ai_poll().
	 */
	spin_lock(&dev->spinlock);

	status = inb(dev->iobase + DAS1800_STATUS);

	/* अगर पूर्णांकerrupt was not caused by das-1800 */
	अगर (!(status & INT)) अणु
		spin_unlock(&dev->spinlock);
		वापस IRQ_NONE;
	पूर्ण
	/* clear the पूर्णांकerrupt status bit INT */
	outb(CLEAR_INTR_MASK & ~INT, dev->iobase + DAS1800_STATUS);
	/*  handle पूर्णांकerrupt */
	das1800_ai_handler(dev);

	spin_unlock(&dev->spinlock);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक das1800_ai_fixup_paced_timing(काष्ठा comedi_device *dev,
					 काष्ठा comedi_cmd *cmd)
अणु
	अचिन्हित पूर्णांक arg = cmd->convert_arg;

	/*
	 * Paced mode:
	 *	scan_begin_src is TRIG_FOLLOW
	 *	convert_src is TRIG_TIMER
	 *
	 * The convert_arg sets the pacer sample acquisition समय.
	 * The max acquisition speed is limited to the boards
	 * 'ai_speed' (this was alपढ़ोy verअगरied). The min speed is
	 * limited by the cascaded 8254 समयr.
	 */
	comedi_8254_cascade_ns_to_समयr(dev->pacer, &arg, cmd->flags);
	वापस comedi_check_trigger_arg_is(&cmd->convert_arg, arg);
पूर्ण

अटल पूर्णांक das1800_ai_fixup_burst_timing(काष्ठा comedi_device *dev,
					 काष्ठा comedi_cmd *cmd)
अणु
	अचिन्हित पूर्णांक arg = cmd->convert_arg;
	पूर्णांक err = 0;

	/*
	 * Burst mode:
	 *	scan_begin_src is TRIG_TIMER or TRIG_EXT
	 *	convert_src is TRIG_TIMER
	 *
	 * The convert_arg sets burst sample acquisition समय.
	 * The max acquisition speed is limited to the boards
	 * 'ai_speed' (this was alपढ़ोy verअगरied). The min speed is
	 * limiited to 64 microseconds,
	 */
	err |= comedi_check_trigger_arg_max(&arg, 64000);

	/* round to microseconds then verअगरy */
	चयन (cmd->flags & CMDF_ROUND_MASK) अणु
	हाल CMDF_ROUND_NEAREST:
	शेष:
		arg = DIV_ROUND_CLOSEST(arg, 1000);
		अवरोध;
	हाल CMDF_ROUND_DOWN:
		arg = arg / 1000;
		अवरोध;
	हाल CMDF_ROUND_UP:
		arg = DIV_ROUND_UP(arg, 1000);
		अवरोध;
	पूर्ण
	err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg * 1000);

	/*
	 * The pacer can be used to set the scan sample rate. The max scan
	 * speed is limited by the conversion speed and the number of channels
	 * to convert. The min speed is limited by the cascaded 8254 समयr.
	 */
	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		arg = cmd->convert_arg * cmd->chanlist_len;
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg, arg);

		arg = cmd->scan_begin_arg;
		comedi_8254_cascade_ns_to_समयr(dev->pacer, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक das1800_ai_check_chanlist(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     काष्ठा comedi_cmd *cmd)
अणु
	अचिन्हित पूर्णांक range = CR_RANGE(cmd->chanlist[0]);
	bool unipolar0 = comedi_range_is_unipolar(s, range);
	पूर्णांक i;

	क्रम (i = 1; i < cmd->chanlist_len; i++) अणु
		range = CR_RANGE(cmd->chanlist[i]);

		अगर (unipolar0 != comedi_range_is_unipolar(s, range)) अणु
			dev_dbg(dev->class_dev,
				"unipolar and bipolar ranges cannot be mixed in the chanlist\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक das1800_ai_cmdtest(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा das1800_board *board = dev->board_ptr;
	पूर्णांक err = 0;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_FOLLOW | TRIG_TIMER | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src,
					TRIG_TIMER | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src,
					TRIG_COUNT | TRIG_EXT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->convert_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	/* burst scans must use समयd conversions */
	अगर (cmd->scan_begin_src != TRIG_FOLLOW &&
	    cmd->convert_src != TRIG_TIMER)
		err |= -EINVAL;

	/* the बाह्यal pin TGIN must use the same polarity */
	अगर (cmd->start_src == TRIG_EXT && cmd->stop_src == TRIG_EXT)
		err |= comedi_check_trigger_arg_is(&cmd->start_arg,
						   cmd->stop_arg);

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	अगर (cmd->start_arg == TRIG_NOW)
		err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
						    board->ai_speed);
	पूर्ण

	err |= comedi_check_trigger_arg_min(&cmd->chanlist_len, 1);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	चयन (cmd->stop_src) अणु
	हाल TRIG_COUNT:
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
		अवरोध;
	हाल TRIG_NONE:
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (err)
		वापस 3;

	/* Step 4: fix up any arguments */

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		अगर (cmd->scan_begin_src == TRIG_FOLLOW)
			err |= das1800_ai_fixup_paced_timing(dev, cmd);
		अन्यथा /* TRIG_TIMER or TRIG_EXT */
			err |= das1800_ai_fixup_burst_timing(dev, cmd);
	पूर्ण

	अगर (err)
		वापस 4;

	/* Step 5: check channel list अगर it exists */
	अगर (cmd->chanlist && cmd->chanlist_len > 0)
		err |= das1800_ai_check_chanlist(dev, s, cmd);

	अगर (err)
		वापस 5;

	वापस 0;
पूर्ण

अटल अचिन्हित अक्षर das1800_ai_chanspec_bits(काष्ठा comedi_subdevice *s,
					      अचिन्हित पूर्णांक chanspec)
अणु
	अचिन्हित पूर्णांक range = CR_RANGE(chanspec);
	अचिन्हित पूर्णांक aref = CR_AREF(chanspec);
	अचिन्हित अक्षर bits;

	bits = UQEN;
	अगर (aref != AREF_DIFF)
		bits |= SD;
	अगर (aref == AREF_COMMON)
		bits |= CMEN;
	अगर (comedi_range_is_unipolar(s, range))
		bits |= UB;

	वापस bits;
पूर्ण

अटल अचिन्हित पूर्णांक das1800_ai_transfer_size(काष्ठा comedi_device *dev,
					     काष्ठा comedi_subdevice *s,
					     अचिन्हित पूर्णांक maxbytes,
					     अचिन्हित पूर्णांक ns)
अणु
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक max_samples = comedi_bytes_to_samples(s, maxbytes);
	अचिन्हित पूर्णांक samples;

	samples = max_samples;

	/* क्रम समयd modes, make dma buffer fill in 'ns' समय */
	चयन (cmd->scan_begin_src) अणु
	हाल TRIG_FOLLOW:	/* not in burst mode */
		अगर (cmd->convert_src == TRIG_TIMER)
			samples = ns / cmd->convert_arg;
		अवरोध;
	हाल TRIG_TIMER:
		samples = ns / (cmd->scan_begin_arg * cmd->chanlist_len);
		अवरोध;
	पूर्ण

	/* limit samples to what is reमुख्यing in the command */
	samples = comedi_nsamples_left(s, samples);

	अगर (samples > max_samples)
		samples = max_samples;
	अगर (samples < 1)
		samples = 1;

	वापस comedi_samples_to_bytes(s, samples);
पूर्ण

अटल व्योम das1800_ai_setup_dma(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s)
अणु
	काष्ठा das1800_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_isadma_desc *desc;
	अचिन्हित पूर्णांक bytes;

	अगर ((devpriv->irq_dma_bits & DMA_ENABLED) == 0)
		वापस;

	dma->cur_dma = 0;
	desc = &dma->desc[0];

	/* determine a dma transfer size to fill buffer in 0.3 sec */
	bytes = das1800_ai_transfer_size(dev, s, desc->maxsize, 300000000);

	desc->size = bytes;
	comedi_isadma_program(desc);

	/* set up dual dma अगर appropriate */
	अगर (devpriv->irq_dma_bits & DMA_DUAL) अणु
		desc = &dma->desc[1];
		desc->size = bytes;
		comedi_isadma_program(desc);
	पूर्ण
पूर्ण

अटल व्योम das1800_ai_set_chanlist(काष्ठा comedi_device *dev,
				    अचिन्हित पूर्णांक *chanlist, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	/* protects the indirect addressing selected by DAS1800_SELECT */
	spin_lock_irqsave(&dev->spinlock, flags);

	/* select QRAM रेजिस्टर and set start address */
	outb(QRAM, dev->iobase + DAS1800_SELECT);
	outb(len - 1, dev->iobase + DAS1800_QRAM_ADDRESS);

	/* make channel / gain list */
	क्रम (i = 0; i < len; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(chanlist[i]);
		अचिन्हित पूर्णांक range = CR_RANGE(chanlist[i]);
		अचिन्हित लघु val;

		val = chan | ((range & 0x3) << 8);
		outw(val, dev->iobase + DAS1800_QRAM);
	पूर्ण

	/* finish ग_लिखो to QRAM */
	outb(len - 1, dev->iobase + DAS1800_QRAM_ADDRESS);

	spin_unlock_irqrestore(&dev->spinlock, flags);
पूर्ण

अटल पूर्णांक das1800_ai_cmd(काष्ठा comedi_device *dev,
			  काष्ठा comedi_subdevice *s)
अणु
	काष्ठा das1800_निजी *devpriv = dev->निजी;
	पूर्णांक control_a, control_c;
	काष्ठा comedi_async *async = s->async;
	स्थिर काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित पूर्णांक range0 = CR_RANGE(cmd->chanlist[0]);

	/*
	 * Disable dma on CMDF_WAKE_EOS, or CMDF_PRIORITY (because dma in
	 * handler is unsafe at hard real-समय priority).
	 */
	अगर (cmd->flags & (CMDF_WAKE_EOS | CMDF_PRIORITY))
		devpriv->irq_dma_bits &= ~DMA_ENABLED;
	अन्यथा
		devpriv->irq_dma_bits |= devpriv->dma_bits;
	/*  पूर्णांकerrupt on end of conversion क्रम CMDF_WAKE_EOS */
	अगर (cmd->flags & CMDF_WAKE_EOS) अणु
		/*  पूर्णांकerrupt fअगरo not empty */
		devpriv->irq_dma_bits &= ~FIMD;
	पूर्ण अन्यथा अणु
		/*  पूर्णांकerrupt fअगरo half full */
		devpriv->irq_dma_bits |= FIMD;
	पूर्ण

	das1800_ai_cancel(dev, s);

	devpriv->ai_is_unipolar = comedi_range_is_unipolar(s, range0);

	control_a = FFEN;
	अगर (cmd->stop_src == TRIG_EXT)
		control_a |= ATEN;
	अगर (cmd->start_src == TRIG_EXT)
		control_a |= TGEN | CGSL;
	अन्यथा /* TRIG_NOW */
		control_a |= CGEN;
	अगर (control_a & (ATEN | TGEN)) अणु
		अगर ((cmd->start_arg & CR_INVERT) || (cmd->stop_arg & CR_INVERT))
			control_a |= TGPL;
	पूर्ण

	control_c = das1800_ai_chanspec_bits(s, cmd->chanlist[0]);
	/* set घड़ी source to पूर्णांकernal or बाह्यal */
	अगर (cmd->scan_begin_src == TRIG_FOLLOW) अणु
		/* not in burst mode */
		अगर (cmd->convert_src == TRIG_TIMER) अणु
			/* trig on cascaded counters */
			control_c |= IPCLK;
		पूर्ण अन्यथा अणु /* TRIG_EXT */
			/* trig on falling edge of बाह्यal trigger */
			control_c |= XPCLK;
		पूर्ण
	पूर्ण अन्यथा अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		/* burst mode with पूर्णांकernal pacer घड़ी */
		control_c |= BMDE | IPCLK;
	पूर्ण अन्यथा अणु /* TRIG_EXT */
		/* burst mode with बाह्यal trigger */
		control_c |= BMDE | XPCLK;
	पूर्ण

	das1800_ai_set_chanlist(dev, cmd->chanlist, cmd->chanlist_len);

	/* setup cascaded counters क्रम conversion/scan frequency */
	अगर ((cmd->scan_begin_src == TRIG_FOLLOW ||
	     cmd->scan_begin_src == TRIG_TIMER) &&
	    cmd->convert_src == TRIG_TIMER) अणु
		comedi_8254_update_भागisors(dev->pacer);
		comedi_8254_pacer_enable(dev->pacer, 1, 2, true);
	पूर्ण

	/* setup counter 0 क्रम 'about triggering' */
	अगर (cmd->stop_src == TRIG_EXT)
		comedi_8254_load(dev->pacer, 0, 1, I8254_MODE0 | I8254_BINARY);

	das1800_ai_setup_dma(dev, s);
	outb(control_c, dev->iobase + DAS1800_CONTROL_C);
	/*  set conversion rate and length क्रम burst mode */
	अगर (control_c & BMDE) अणु
		outb(cmd->convert_arg / 1000 - 1,	/* microseconds - 1 */
		     dev->iobase + DAS1800_BURST_RATE);
		outb(cmd->chanlist_len - 1, dev->iobase + DAS1800_BURST_LENGTH);
	पूर्ण

	/* enable and start conversions */
	outb(devpriv->irq_dma_bits, dev->iobase + DAS1800_CONTROL_B);
	outb(control_a, dev->iobase + DAS1800_CONTROL_A);
	outb(CVEN, dev->iobase + DAS1800_STATUS);

	वापस 0;
पूर्ण

अटल पूर्णांक das1800_ai_eoc(काष्ठा comedi_device *dev,
			  काष्ठा comedi_subdevice *s,
			  काष्ठा comedi_insn *insn,
			  अचिन्हित दीर्घ context)
अणु
	अचिन्हित अक्षर status;

	status = inb(dev->iobase + DAS1800_STATUS);
	अगर (status & FNE)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक das1800_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	bool is_unipolar = comedi_range_is_unipolar(s, range);
	पूर्णांक ret = 0;
	पूर्णांक n;
	अचिन्हित लघु dpnt;
	अचिन्हित दीर्घ flags;

	outb(das1800_ai_chanspec_bits(s, insn->chanspec),
	     dev->iobase + DAS1800_CONTROL_C);		/* software pacer */
	outb(CVEN, dev->iobase + DAS1800_STATUS);	/* enable conversions */
	outb(0x0, dev->iobase + DAS1800_CONTROL_A);	/* reset fअगरo */
	outb(FFEN, dev->iobase + DAS1800_CONTROL_A);

	das1800_ai_set_chanlist(dev, &insn->chanspec, 1);

	/* protects the indirect addressing selected by DAS1800_SELECT */
	spin_lock_irqsave(&dev->spinlock, flags);

	/* select ai fअगरo रेजिस्टर */
	outb(ADC, dev->iobase + DAS1800_SELECT);

	क्रम (n = 0; n < insn->n; n++) अणु
		/* trigger conversion */
		outb(0, dev->iobase + DAS1800_FIFO);

		ret = comedi_समयout(dev, s, insn, das1800_ai_eoc, 0);
		अगर (ret)
			अवरोध;

		dpnt = inw(dev->iobase + DAS1800_FIFO);
		अगर (!is_unipolar)
			dpnt = comedi_offset_munge(s, dpnt);
		data[n] = dpnt;
	पूर्ण
	spin_unlock_irqrestore(&dev->spinlock, flags);

	वापस ret ? ret : insn->n;
पूर्ण

अटल पूर्णांक das1800_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक update_chan = s->n_chan - 1;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	/* protects the indirect addressing selected by DAS1800_SELECT */
	spin_lock_irqsave(&dev->spinlock, flags);

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val = data[i];

		s->पढ़ोback[chan] = val;

		val = comedi_offset_munge(s, val);

		/* load this channel (and update अगर it's the last channel) */
		outb(DAC(chan), dev->iobase + DAS1800_SELECT);
		outw(val, dev->iobase + DAS1800_DAC);

		/* update all channels */
		अगर (chan != update_chan) अणु
			val = comedi_offset_munge(s, s->पढ़ोback[update_chan]);

			outb(DAC(update_chan), dev->iobase + DAS1800_SELECT);
			outw(val, dev->iobase + DAS1800_DAC);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dev->spinlock, flags);

	वापस insn->n;
पूर्ण

अटल पूर्णांक das1800_di_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	data[1] = inb(dev->iobase + DAS1800_DIGITAL) & 0xf;
	data[0] = 0;

	वापस insn->n;
पूर्ण

अटल पूर्णांक das1800_करो_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		outb(s->state, dev->iobase + DAS1800_DIGITAL);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल व्योम das1800_init_dma(काष्ठा comedi_device *dev,
			     काष्ठा comedi_devconfig *it)
अणु
	काष्ठा das1800_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक *dma_chan;

	/*
	 * it->options[2] is DMA channel 0
	 * it->options[3] is DMA channel 1
	 *
	 * Encode the DMA channels पूर्णांकo 2 digit hexadecimal क्रम चयन.
	 */
	dma_chan = &it->options[2];

	चयन ((dma_chan[0] & 0x7) | (dma_chan[1] << 4)) अणु
	हाल 0x5:	/*  dma0 == 5 */
		devpriv->dma_bits = DMA_CH5;
		अवरोध;
	हाल 0x6:	/*  dma0 == 6 */
		devpriv->dma_bits = DMA_CH6;
		अवरोध;
	हाल 0x7:	/*  dma0 == 7 */
		devpriv->dma_bits = DMA_CH7;
		अवरोध;
	हाल 0x65:	/*  dma0 == 5, dma1 == 6 */
		devpriv->dma_bits = DMA_CH5_CH6;
		अवरोध;
	हाल 0x76:	/*  dma0 == 6, dma1 == 7 */
		devpriv->dma_bits = DMA_CH6_CH7;
		अवरोध;
	हाल 0x57:	/*  dma0 == 7, dma1 == 5 */
		devpriv->dma_bits = DMA_CH7_CH5;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	/* DMA can use 1 or 2 buffers, each with a separate channel */
	devpriv->dma = comedi_isadma_alloc(dev, dma_chan[1] ? 2 : 1,
					   dma_chan[0], dma_chan[1],
					   DMA_BUF_SIZE, COMEDI_ISADMA_READ);
	अगर (!devpriv->dma)
		devpriv->dma_bits = 0;
पूर्ण

अटल व्योम das1800_मुक्त_dma(काष्ठा comedi_device *dev)
अणु
	काष्ठा das1800_निजी *devpriv = dev->निजी;

	अगर (devpriv)
		comedi_isadma_मुक्त(devpriv->dma);
पूर्ण

अटल पूर्णांक das1800_probe(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा das1800_board *board = dev->board_ptr;
	अचिन्हित अक्षर id;

	id = (inb(dev->iobase + DAS1800_DIGITAL) >> 4) & 0xf;

	/*
	 * The dev->board_ptr will be set by comedi_device_attach() अगर the
	 * board name provided by the user matches a board->name in this
	 * driver. If so, this function sanity checks the id to verअगरy that
	 * the board is correct.
	 */
	अगर (board) अणु
		अगर (board->id == id)
			वापस 0;
		dev_err(dev->class_dev,
			"probed id does not match board id (0x%x != 0x%x)\n",
			id, board->id);
		वापस -ENODEV;
	पूर्ण

	 /*
	  * If the dev->board_ptr is not set, the user is trying to attach
	  * an unspecअगरied board to this driver. In this हाल the id is used
	  * to 'probe' क्रम the dev->board_ptr.
	  */
	चयन (id) अणु
	हाल DAS1800_ID_ST_DA:
		/* das-1701st-da, das-1702st-da, das-1801st-da, das-1802st-da */
		board = &das1800_boards[BOARD_DAS1801ST_DA];
		अवरोध;
	हाल DAS1800_ID_HR_DA:
		/* das-1702hr-da, das-1802hr-da */
		board = &das1800_boards[BOARD_DAS1802HR_DA];
		अवरोध;
	हाल DAS1800_ID_AO:
		/* das-1701ao, das-1702ao, das-1801ao, das-1802ao */
		board = &das1800_boards[BOARD_DAS1801AO];
		अवरोध;
	हाल DAS1800_ID_HR:
		/*  das-1702hr, das-1802hr */
		board = &das1800_boards[BOARD_DAS1802HR];
		अवरोध;
	हाल DAS1800_ID_ST:
		/* das-1701st, das-1702st, das-1801st, das-1802st */
		board = &das1800_boards[BOARD_DAS1801ST];
		अवरोध;
	हाल DAS1800_ID_HC:
		/* das-1801hc, das-1802hc */
		board = &das1800_boards[BOARD_DAS1801HC];
		अवरोध;
	शेष:
		dev_err(dev->class_dev, "invalid probe id 0x%x\n", id);
		वापस -ENODEV;
	पूर्ण
	dev->board_ptr = board;
	dev->board_name = board->name;
	dev_warn(dev->class_dev,
		 "probed id 0x%0x: %s series (not recommended)\n",
		 id, board->name);
	वापस 0;
पूर्ण

अटल पूर्णांक das1800_attach(काष्ठा comedi_device *dev,
			  काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा das1800_board *board;
	काष्ठा das1800_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक irq = it->options[1];
	bool is_16bit;
	पूर्णांक ret;
	पूर्णांक i;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_request_region(dev, it->options[0], DAS1800_SIZE);
	अगर (ret)
		वापस ret;

	ret = das1800_probe(dev);
	अगर (ret)
		वापस ret;
	board = dev->board_ptr;

	is_16bit = board->id == DAS1800_ID_HR || board->id == DAS1800_ID_HR_DA;

	/* waveक्रमm 'ao' boards have additional io ports */
	अगर (board->id == DAS1800_ID_AO) अणु
		अचिन्हित दीर्घ iobase2 = dev->iobase + IOBASE2;

		ret = __comedi_request_region(dev, iobase2, DAS1800_SIZE);
		अगर (ret)
			वापस ret;
		devpriv->iobase2 = iobase2;
	पूर्ण

	अगर (irq == 3 || irq == 5 || irq == 7 || irq == 10 || irq == 11 ||
	    irq == 15) अणु
		ret = request_irq(irq, das1800_पूर्णांकerrupt, 0,
				  dev->board_name, dev);
		अगर (ret == 0) अणु
			dev->irq = irq;

			चयन (irq) अणु
			हाल 3:
				devpriv->irq_dma_bits |= 0x8;
				अवरोध;
			हाल 5:
				devpriv->irq_dma_bits |= 0x10;
				अवरोध;
			हाल 7:
				devpriv->irq_dma_bits |= 0x18;
				अवरोध;
			हाल 10:
				devpriv->irq_dma_bits |= 0x28;
				अवरोध;
			हाल 11:
				devpriv->irq_dma_bits |= 0x30;
				अवरोध;
			हाल 15:
				devpriv->irq_dma_bits |= 0x38;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* an irq and one dma channel is required to use dma */
	अगर (dev->irq & it->options[2])
		das1800_init_dma(dev, it);

	devpriv->fअगरo_buf = kदो_स्मृति_array(FIFO_SIZE,
					  माप(*devpriv->fअगरo_buf),
					  GFP_KERNEL);
	अगर (!devpriv->fअगरo_buf)
		वापस -ENOMEM;

	dev->pacer = comedi_8254_init(dev->iobase + DAS1800_COUNTER,
				      I8254_OSC_BASE_5MHZ, I8254_IO8, 0);
	अगर (!dev->pacer)
		वापस -ENOMEM;

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	/*
	 * Analog Input subdevice
	 *
	 * The "hc" type boards have 64 analog input channels and a 64
	 * entry QRAM fअगरo.
	 *
	 * All the other board types have 16 on-board channels. Each channel
	 * can be expanded to 16 channels with the addition of an EXP-1800
	 * expansion board क्रम a total of 256 channels. The QRAM fअगरo on
	 * these boards has 256 entries.
	 *
	 * From the datasheets it's not clear what the comedi channel to
	 * actual physical channel mapping is when EXP-1800 boards are used.
	 */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_DIFF | SDF_GROUND;
	अगर (board->id != DAS1800_ID_HC)
		s->subdev_flags	|= SDF_COMMON;
	s->n_chan	= (board->id == DAS1800_ID_HC) ? 64 : 256;
	s->maxdata	= is_16bit ? 0xffff : 0x0fff;
	s->range_table	= board->is_01_series ? &das1801_ai_range
					      : &das1802_ai_range;
	s->insn_पढ़ो	= das1800_ai_insn_पढ़ो;
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->len_chanlist	= s->n_chan;
		s->करो_cmd	= das1800_ai_cmd;
		s->करो_cmdtest	= das1800_ai_cmdtest;
		s->poll		= das1800_ai_poll;
		s->cancel	= das1800_ai_cancel;
		s->munge	= das1800_ai_munge;
	पूर्ण

	/* Analog Output subdevice */
	s = &dev->subdevices[1];
	अगर (board->id == DAS1800_ID_ST_DA || board->id == DAS1800_ID_HR_DA) अणु
		s->type		= COMEDI_SUBD_AO;
		s->subdev_flags	= SDF_WRITABLE;
		s->n_chan	= (board->id == DAS1800_ID_ST_DA) ? 4 : 2;
		s->maxdata	= is_16bit ? 0xffff : 0x0fff;
		s->range_table	= &range_bipolar10;
		s->insn_ग_लिखो	= das1800_ao_insn_ग_लिखो;

		ret = comedi_alloc_subdev_पढ़ोback(s);
		अगर (ret)
			वापस ret;

		/* initialize all channels to 0V */
		क्रम (i = 0; i < s->n_chan; i++) अणु
			/* spinlock is not necessary during the attach */
			outb(DAC(i), dev->iobase + DAS1800_SELECT);
			outw(0, dev->iobase + DAS1800_DAC);
		पूर्ण
	पूर्ण अन्यथा अगर (board->id == DAS1800_ID_AO) अणु
		/*
		 * 'ao' boards have waveक्रमm analog outमाला_दो that are not
		 * currently supported.
		 */
		s->type		= COMEDI_SUBD_UNUSED;
	पूर्ण अन्यथा अणु
		s->type		= COMEDI_SUBD_UNUSED;
	पूर्ण

	/* Digital Input subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= das1800_di_insn_bits;

	/* Digital Output subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= (board->id == DAS1800_ID_HC) ? 8 : 4;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= das1800_करो_insn_bits;

	das1800_ai_cancel(dev, dev->पढ़ो_subdev);

	/*  initialize digital out channels */
	outb(0, dev->iobase + DAS1800_DIGITAL);

	वापस 0;
पूर्ण;

अटल व्योम das1800_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा das1800_निजी *devpriv = dev->निजी;

	das1800_मुक्त_dma(dev);
	अगर (devpriv) अणु
		kमुक्त(devpriv->fअगरo_buf);
		अगर (devpriv->iobase2)
			release_region(devpriv->iobase2, DAS1800_SIZE);
	पूर्ण
	comedi_legacy_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver das1800_driver = अणु
	.driver_name	= "das1800",
	.module		= THIS_MODULE,
	.attach		= das1800_attach,
	.detach		= das1800_detach,
	.num_names	= ARRAY_SIZE(das1800_boards),
	.board_name	= &das1800_boards[0].name,
	.offset		= माप(काष्ठा das1800_board),
पूर्ण;
module_comedi_driver(das1800_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for DAS1800 compatible ISA boards");
MODULE_LICENSE("GPL");
