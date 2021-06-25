<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * das16.c
 * DAS16 driver
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 * Copyright (C) 2000 Chris R. Baugher <baugher@enteract.com>
 * Copyright (C) 2001,2002 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 */

/*
 * Driver: das16
 * Description: DAS16 compatible boards
 * Author: Sam Moore, Warren Jasper, ds, Chris Baugher, Frank Hess, Roman Fietze
 * Devices: [Keithley Metrabyte] DAS-16 (das-16), DAS-16G (das-16g),
 *   DAS-16F (das-16f), DAS-1201 (das-1201), DAS-1202 (das-1202),
 *   DAS-1401 (das-1401), DAS-1402 (das-1402), DAS-1601 (das-1601),
 *   DAS-1602 (das-1602),
 *   [ComputerBoards] PC104-DAS16/JR (pc104-das16jr),
 *   PC104-DAS16JR/16 (pc104-das16jr/16), CIO-DAS16 (cio-das16),
 *   CIO-DAS16F (cio-das16/f), CIO-DAS16/JR (cio-das16/jr),
 *   CIO-DAS16JR/16 (cio-das16jr/16), CIO-DAS1401/12 (cio-das1401/12),
 *   CIO-DAS1402/12 (cio-das1402/12), CIO-DAS1402/16 (cio-das1402/16),
 *   CIO-DAS1601/12 (cio-das1601/12), CIO-DAS1602/12 (cio-das1602/12),
 *   CIO-DAS1602/16 (cio-das1602/16), CIO-DAS16/330 (cio-das16/330)
 * Status: works
 * Updated: 2003-10-12
 *
 * A reग_लिखो of the das16 and das1600 drivers.
 *
 * Options:
 *	[0] - base io address
 *	[1] - irq (करोes nothing, irq is not used anymore)
 *	[2] - dma channel (optional, required क्रम comedi_command support)
 *	[3] - master घड़ी speed in MHz (optional, 1 or 10, ignored अगर
 *		board can probe घड़ी, शेषs to 1)
 *	[4] - analog input range lowest voltage in microvolts (optional,
 *		only useful अगर your board करोes not have software
 *		programmable gain)
 *	[5] - analog input range highest voltage in microvolts (optional,
 *		only useful अगर board करोes not have software programmable
 *		gain)
 *	[6] - analog output range lowest voltage in microvolts (optional)
 *	[7] - analog output range highest voltage in microvolts (optional)
 *
 * Passing a zero क्रम an option is the same as leaving it unspecअगरied.
 */

/*
 * Testing and debugging help provided by Daniel Koch.
 *
 * Keithley Manuals:
 *	2309.PDF (das16)
 *	4919.PDF (das1400, 1600)
 *	4922.PDF (das-1400)
 *	4923.PDF (das1200, 1400, 1600)
 *
 * Computer boards manuals also available from their website
 * www.measurementcomputing.com
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedidev.h"

#समावेश "comedi_isadma.h"
#समावेश "comedi_8254.h"
#समावेश "8255.h"

#घोषणा DAS16_DMA_SIZE 0xff00	/*  size in bytes of allocated dma buffer */

/*
 * Register I/O map
 */
#घोषणा DAS16_TRIG_REG			0x00
#घोषणा DAS16_AI_LSB_REG		0x00
#घोषणा DAS16_AI_MSB_REG		0x01
#घोषणा DAS16_MUX_REG			0x02
#घोषणा DAS16_DIO_REG			0x03
#घोषणा DAS16_AO_LSB_REG(x)		((x) ? 0x06 : 0x04)
#घोषणा DAS16_AO_MSB_REG(x)		((x) ? 0x07 : 0x05)
#घोषणा DAS16_STATUS_REG		0x08
#घोषणा DAS16_STATUS_BUSY		BIT(7)
#घोषणा DAS16_STATUS_UNIPOLAR		BIT(6)
#घोषणा DAS16_STATUS_MUXBIT		BIT(5)
#घोषणा DAS16_STATUS_INT		BIT(4)
#घोषणा DAS16_CTRL_REG			0x09
#घोषणा DAS16_CTRL_INTE			BIT(7)
#घोषणा DAS16_CTRL_IRQ(x)		(((x) & 0x7) << 4)
#घोषणा DAS16_CTRL_DMAE			BIT(2)
#घोषणा DAS16_CTRL_PACING_MASK		(3 << 0)
#घोषणा DAS16_CTRL_INT_PACER		(3 << 0)
#घोषणा DAS16_CTRL_EXT_PACER		(2 << 0)
#घोषणा DAS16_CTRL_SOFT_PACER		(0 << 0)
#घोषणा DAS16_PACER_REG			0x0a
#घोषणा DAS16_PACER_BURST_LEN(x)	(((x) & 0xf) << 4)
#घोषणा DAS16_PACER_CTR0		BIT(1)
#घोषणा DAS16_PACER_TRIG0		BIT(0)
#घोषणा DAS16_GAIN_REG			0x0b
#घोषणा DAS16_TIMER_BASE_REG		0x0c	/* to 0x0f */

#घोषणा DAS1600_CONV_REG		0x404
#घोषणा DAS1600_CONV_DISABLE		BIT(6)
#घोषणा DAS1600_BURST_REG		0x405
#घोषणा DAS1600_BURST_VAL		BIT(6)
#घोषणा DAS1600_ENABLE_REG		0x406
#घोषणा DAS1600_ENABLE_VAL		BIT(6)
#घोषणा DAS1600_STATUS_REG		0x407
#घोषणा DAS1600_STATUS_BME		BIT(6)
#घोषणा DAS1600_STATUS_ME		BIT(5)
#घोषणा DAS1600_STATUS_CD		BIT(4)
#घोषणा DAS1600_STATUS_WS		BIT(1)
#घोषणा DAS1600_STATUS_CLK_10MHZ	BIT(0)

अटल स्थिर काष्ठा comedi_lrange range_das1x01_bip = अणु
	4, अणु
		BIP_RANGE(10),
		BIP_RANGE(1),
		BIP_RANGE(0.1),
		BIP_RANGE(0.01)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_das1x01_unip = अणु
	4, अणु
		UNI_RANGE(10),
		UNI_RANGE(1),
		UNI_RANGE(0.1),
		UNI_RANGE(0.01)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_das1x02_bip = अणु
	4, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_das1x02_unip = अणु
	4, अणु
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2.5),
		UNI_RANGE(1.25)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_das16jr = अणु
	9, अणु
		BIP_RANGE(10),
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

अटल स्थिर काष्ठा comedi_lrange range_das16jr_16 = अणु
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

अटल स्थिर पूर्णांक das16jr_gainlist[] = अणु 8, 0, 1, 2, 3, 4, 5, 6, 7 पूर्ण;
अटल स्थिर पूर्णांक das16jr_16_gainlist[] = अणु 0, 1, 2, 3, 4, 5, 6, 7 पूर्ण;
अटल स्थिर पूर्णांक das1600_gainlist[] = अणु 0, 1, 2, 3 पूर्ण;

क्रमागत अणु
	das16_pg_none = 0,
	das16_pg_16jr,
	das16_pg_16jr_16,
	das16_pg_1601,
	das16_pg_1602,
पूर्ण;

अटल स्थिर पूर्णांक *स्थिर das16_gainlists[] = अणु
	शून्य,
	das16jr_gainlist,
	das16jr_16_gainlist,
	das1600_gainlist,
	das1600_gainlist,
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange *स्थिर das16_ai_uni_lranges[] = अणु
	&range_unknown,
	&range_das16jr,
	&range_das16jr_16,
	&range_das1x01_unip,
	&range_das1x02_unip,
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange *स्थिर das16_ai_bip_lranges[] = अणु
	&range_unknown,
	&range_das16jr,
	&range_das16jr_16,
	&range_das1x01_bip,
	&range_das1x02_bip,
पूर्ण;

काष्ठा das16_board अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक ai_maxdata;
	अचिन्हित पूर्णांक ai_speed;	/*  max conversion speed in nanosec */
	अचिन्हित पूर्णांक ai_pg;
	अचिन्हित पूर्णांक has_ao:1;
	अचिन्हित पूर्णांक has_8255:1;

	अचिन्हित पूर्णांक i8255_offset;

	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक id;
पूर्ण;

अटल स्थिर काष्ठा das16_board das16_boards[] = अणु
	अणु
		.name		= "das-16",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 15000,
		.ai_pg		= das16_pg_none,
		.has_ao		= 1,
		.has_8255	= 1,
		.i8255_offset	= 0x10,
		.size		= 0x14,
		.id		= 0x00,
	पूर्ण, अणु
		.name		= "das-16g",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 15000,
		.ai_pg		= das16_pg_none,
		.has_ao		= 1,
		.has_8255	= 1,
		.i8255_offset	= 0x10,
		.size		= 0x14,
		.id		= 0x00,
	पूर्ण, अणु
		.name		= "das-16f",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 8500,
		.ai_pg		= das16_pg_none,
		.has_ao		= 1,
		.has_8255	= 1,
		.i8255_offset	= 0x10,
		.size		= 0x14,
		.id		= 0x00,
	पूर्ण, अणु
		.name		= "cio-das16",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 20000,
		.ai_pg		= das16_pg_none,
		.has_ao		= 1,
		.has_8255	= 1,
		.i8255_offset	= 0x10,
		.size		= 0x14,
		.id		= 0x80,
	पूर्ण, अणु
		.name		= "cio-das16/f",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 10000,
		.ai_pg		= das16_pg_none,
		.has_ao		= 1,
		.has_8255	= 1,
		.i8255_offset	= 0x10,
		.size		= 0x14,
		.id		= 0x80,
	पूर्ण, अणु
		.name		= "cio-das16/jr",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 7692,
		.ai_pg		= das16_pg_16jr,
		.size		= 0x10,
		.id		= 0x00,
	पूर्ण, अणु
		.name		= "pc104-das16jr",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 3300,
		.ai_pg		= das16_pg_16jr,
		.size		= 0x10,
		.id		= 0x00,
	पूर्ण, अणु
		.name		= "cio-das16jr/16",
		.ai_maxdata	= 0xffff,
		.ai_speed	= 10000,
		.ai_pg		= das16_pg_16jr_16,
		.size		= 0x10,
		.id		= 0x00,
	पूर्ण, अणु
		.name		= "pc104-das16jr/16",
		.ai_maxdata	= 0xffff,
		.ai_speed	= 10000,
		.ai_pg		= das16_pg_16jr_16,
		.size		= 0x10,
		.id		= 0x00,
	पूर्ण, अणु
		.name		= "das-1201",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 20000,
		.ai_pg		= das16_pg_none,
		.has_8255	= 1,
		.i8255_offset	= 0x400,
		.size		= 0x408,
		.id		= 0x20,
	पूर्ण, अणु
		.name		= "das-1202",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 10000,
		.ai_pg		= das16_pg_none,
		.has_8255	= 1,
		.i8255_offset	= 0x400,
		.size		= 0x408,
		.id		= 0x20,
	पूर्ण, अणु
		.name		= "das-1401",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 10000,
		.ai_pg		= das16_pg_1601,
		.size		= 0x408,
		.id		= 0xc0,
	पूर्ण, अणु
		.name		= "das-1402",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 10000,
		.ai_pg		= das16_pg_1602,
		.size		= 0x408,
		.id		= 0xc0,
	पूर्ण, अणु
		.name		= "das-1601",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 10000,
		.ai_pg		= das16_pg_1601,
		.has_ao		= 1,
		.has_8255	= 1,
		.i8255_offset	= 0x400,
		.size		= 0x408,
		.id		= 0xc0,
	पूर्ण, अणु
		.name		= "das-1602",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 10000,
		.ai_pg		= das16_pg_1602,
		.has_ao		= 1,
		.has_8255	= 1,
		.i8255_offset	= 0x400,
		.size		= 0x408,
		.id		= 0xc0,
	पूर्ण, अणु
		.name		= "cio-das1401/12",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 6250,
		.ai_pg		= das16_pg_1601,
		.size		= 0x408,
		.id		= 0xc0,
	पूर्ण, अणु
		.name		= "cio-das1402/12",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 6250,
		.ai_pg		= das16_pg_1602,
		.size		= 0x408,
		.id		= 0xc0,
	पूर्ण, अणु
		.name		= "cio-das1402/16",
		.ai_maxdata	= 0xffff,
		.ai_speed	= 10000,
		.ai_pg		= das16_pg_1602,
		.size		= 0x408,
		.id		= 0xc0,
	पूर्ण, अणु
		.name		= "cio-das1601/12",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 6250,
		.ai_pg		= das16_pg_1601,
		.has_ao		= 1,
		.has_8255	= 1,
		.i8255_offset	= 0x400,
		.size		= 0x408,
		.id		= 0xc0,
	पूर्ण, अणु
		.name		= "cio-das1602/12",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 10000,
		.ai_pg		= das16_pg_1602,
		.has_ao		= 1,
		.has_8255	= 1,
		.i8255_offset	= 0x400,
		.size		= 0x408,
		.id		= 0xc0,
	पूर्ण, अणु
		.name		= "cio-das1602/16",
		.ai_maxdata	= 0xffff,
		.ai_speed	= 10000,
		.ai_pg		= das16_pg_1602,
		.has_ao		= 1,
		.has_8255	= 1,
		.i8255_offset	= 0x400,
		.size		= 0x408,
		.id		= 0xc0,
	पूर्ण, अणु
		.name		= "cio-das16/330",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 3030,
		.ai_pg		= das16_pg_16jr,
		.size		= 0x14,
		.id		= 0xf0,
	पूर्ण,
पूर्ण;

/*
 * Period क्रम समयr पूर्णांकerrupt in jअगरfies.  It's a function
 * to deal with possibility of dynamic HZ patches
 */
अटल अंतरभूत पूर्णांक समयr_period(व्योम)
अणु
	वापस HZ / 20;
पूर्ण

काष्ठा das16_निजी_काष्ठा अणु
	काष्ठा comedi_isadma	*dma;
	काष्ठा comedi_device	*dev;
	अचिन्हित पूर्णांक		घड़ीbase;
	अचिन्हित पूर्णांक		ctrl_reg;
	अचिन्हित पूर्णांक		भागisor1;
	अचिन्हित पूर्णांक		भागisor2;
	काष्ठा समयr_list	समयr;
	अचिन्हित दीर्घ		extra_iobase;
	अचिन्हित पूर्णांक		can_burst:1;
	अचिन्हित पूर्णांक		समयr_running:1;
पूर्ण;

अटल व्योम das16_ai_setup_dma(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       अचिन्हित पूर्णांक unपढ़ो_samples)
अणु
	काष्ठा das16_निजी_काष्ठा *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_isadma_desc *desc = &dma->desc[dma->cur_dma];
	अचिन्हित पूर्णांक max_samples = comedi_bytes_to_samples(s, desc->maxsize);
	अचिन्हित पूर्णांक nsamples;

	/*
	 * Determine dma size based on the buffer size plus the number of
	 * unपढ़ो samples and the number of samples reमुख्यing in the command.
	 */
	nsamples = comedi_nsamples_left(s, max_samples + unपढ़ो_samples);
	अगर (nsamples > unपढ़ो_samples) अणु
		nsamples -= unपढ़ो_samples;
		desc->size = comedi_samples_to_bytes(s, nsamples);
		comedi_isadma_program(desc);
	पूर्ण
पूर्ण

अटल व्योम das16_पूर्णांकerrupt(काष्ठा comedi_device *dev)
अणु
	काष्ठा das16_निजी_काष्ठा *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_isadma_desc *desc = &dma->desc[dma->cur_dma];
	अचिन्हित दीर्घ spin_flags;
	अचिन्हित पूर्णांक residue;
	अचिन्हित पूर्णांक nbytes;
	अचिन्हित पूर्णांक nsamples;

	spin_lock_irqsave(&dev->spinlock, spin_flags);
	अगर (!(devpriv->ctrl_reg & DAS16_CTRL_DMAE)) अणु
		spin_unlock_irqrestore(&dev->spinlock, spin_flags);
		वापस;
	पूर्ण

	/*
	 * The pc104-das16jr (at least) has problems अगर the dma
	 * transfer is पूर्णांकerrupted in the middle of transferring
	 * a 16 bit sample.
	 */
	residue = comedi_isadma_disable_on_sample(desc->chan,
						  comedi_bytes_per_sample(s));

	/* figure out how many samples to पढ़ो */
	अगर (residue > desc->size) अणु
		dev_err(dev->class_dev, "residue > transfer size!\n");
		async->events |= COMEDI_CB_ERROR;
		nbytes = 0;
	पूर्ण अन्यथा अणु
		nbytes = desc->size - residue;
	पूर्ण
	nsamples = comedi_bytes_to_samples(s, nbytes);

	/* restart DMA अगर more samples are needed */
	अगर (nsamples) अणु
		dma->cur_dma = 1 - dma->cur_dma;
		das16_ai_setup_dma(dev, s, nsamples);
	पूर्ण

	spin_unlock_irqrestore(&dev->spinlock, spin_flags);

	comedi_buf_ग_लिखो_samples(s, desc->virt_addr, nsamples);

	अगर (cmd->stop_src == TRIG_COUNT && async->scans_करोne >= cmd->stop_arg)
		async->events |= COMEDI_CB_EOA;

	comedi_handle_events(dev, s);
पूर्ण

अटल व्योम das16_समयr_पूर्णांकerrupt(काष्ठा समयr_list *t)
अणु
	काष्ठा das16_निजी_काष्ठा *devpriv = from_समयr(devpriv, t, समयr);
	काष्ठा comedi_device *dev = devpriv->dev;
	अचिन्हित दीर्घ flags;

	das16_पूर्णांकerrupt(dev);

	spin_lock_irqsave(&dev->spinlock, flags);
	अगर (devpriv->समयr_running)
		mod_समयr(&devpriv->समयr, jअगरfies + समयr_period());
	spin_unlock_irqrestore(&dev->spinlock, flags);
पूर्ण

अटल व्योम das16_ai_set_mux_range(काष्ठा comedi_device *dev,
				   अचिन्हित पूर्णांक first_chan,
				   अचिन्हित पूर्णांक last_chan,
				   अचिन्हित पूर्णांक range)
अणु
	स्थिर काष्ठा das16_board *board = dev->board_ptr;

	/* set multiplexer */
	outb(first_chan | (last_chan << 4), dev->iobase + DAS16_MUX_REG);

	/* some boards करो not have programmable gain */
	अगर (board->ai_pg == das16_pg_none)
		वापस;

	/*
	 * Set gain (this is also burst rate रेजिस्टर but according to
	 * computer boards manual, burst rate करोes nothing, even on
	 * keithley cards).
	 */
	outb((das16_gainlists[board->ai_pg])[range],
	     dev->iobase + DAS16_GAIN_REG);
पूर्ण

अटल पूर्णांक das16_ai_check_chanlist(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_cmd *cmd)
अणु
	अचिन्हित पूर्णांक chan0 = CR_CHAN(cmd->chanlist[0]);
	अचिन्हित पूर्णांक range0 = CR_RANGE(cmd->chanlist[0]);
	पूर्णांक i;

	क्रम (i = 1; i < cmd->chanlist_len; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);
		अचिन्हित पूर्णांक range = CR_RANGE(cmd->chanlist[i]);

		अगर (chan != ((chan0 + i) % s->n_chan)) अणु
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

अटल पूर्णांक das16_cmd_test(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
			  काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा das16_board *board = dev->board_ptr;
	काष्ठा das16_निजी_काष्ठा *devpriv = dev->निजी;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक trig_mask;
	अचिन्हित पूर्णांक arg;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);

	trig_mask = TRIG_FOLLOW;
	अगर (devpriv->can_burst)
		trig_mask |= TRIG_TIMER | TRIG_EXT;
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, trig_mask);

	trig_mask = TRIG_TIMER | TRIG_EXT;
	अगर (devpriv->can_burst)
		trig_mask |= TRIG_NOW;
	err |= comedi_check_trigger_src(&cmd->convert_src, trig_mask);

	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->convert_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	/*  make sure scan_begin_src and convert_src करोn't conflict */
	अगर (cmd->scan_begin_src == TRIG_FOLLOW && cmd->convert_src == TRIG_NOW)
		err |= -EINVAL;
	अगर (cmd->scan_begin_src != TRIG_FOLLOW && cmd->convert_src != TRIG_NOW)
		err |= -EINVAL;

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

	अगर (cmd->scan_begin_src == TRIG_FOLLOW)	/* पूर्णांकernal trigger */
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	/* check against maximum frequency */
	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
						    board->ai_speed *
						    cmd->chanlist_len);
	पूर्ण

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
						    board->ai_speed);
	पूर्ण

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/*  step 4: fix up arguments */
	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		arg = cmd->scan_begin_arg;
		comedi_8254_cascade_ns_to_समयr(dev->pacer, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);
	पूर्ण
	अगर (cmd->convert_src == TRIG_TIMER) अणु
		arg = cmd->convert_arg;
		comedi_8254_cascade_ns_to_समयr(dev->pacer, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg);
	पूर्ण
	अगर (err)
		वापस 4;

	/* Step 5: check channel list अगर it exists */
	अगर (cmd->chanlist && cmd->chanlist_len > 0)
		err |= das16_ai_check_chanlist(dev, s, cmd);

	अगर (err)
		वापस 5;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक das16_set_pacer(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक ns,
				    अचिन्हित पूर्णांक flags)
अणु
	comedi_8254_cascade_ns_to_समयr(dev->pacer, &ns, flags);
	comedi_8254_update_भागisors(dev->pacer);
	comedi_8254_pacer_enable(dev->pacer, 1, 2, true);

	वापस ns;
पूर्ण

अटल पूर्णांक das16_cmd_exec(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा das16_निजी_काष्ठा *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित पूर्णांक first_chan = CR_CHAN(cmd->chanlist[0]);
	अचिन्हित पूर्णांक last_chan = CR_CHAN(cmd->chanlist[cmd->chanlist_len - 1]);
	अचिन्हित पूर्णांक range = CR_RANGE(cmd->chanlist[0]);
	अचिन्हित पूर्णांक byte;
	अचिन्हित दीर्घ flags;

	अगर (cmd->flags & CMDF_PRIORITY) अणु
		dev_err(dev->class_dev,
			"isa dma transfers cannot be performed with CMDF_PRIORITY, aborting\n");
		वापस -1;
	पूर्ण

	अगर (devpriv->can_burst)
		outb(DAS1600_CONV_DISABLE, dev->iobase + DAS1600_CONV_REG);

	/* set mux and range क्रम chanlist scan */
	das16_ai_set_mux_range(dev, first_chan, last_chan, range);

	/* set counter mode and counts */
	cmd->convert_arg = das16_set_pacer(dev, cmd->convert_arg, cmd->flags);

	/* enable counters */
	byte = 0;
	अगर (devpriv->can_burst) अणु
		अगर (cmd->convert_src == TRIG_NOW) अणु
			outb(DAS1600_BURST_VAL,
			     dev->iobase + DAS1600_BURST_REG);
			/*  set burst length */
			byte |= DAS16_PACER_BURST_LEN(cmd->chanlist_len - 1);
		पूर्ण अन्यथा अणु
			outb(0, dev->iobase + DAS1600_BURST_REG);
		पूर्ण
	पूर्ण
	outb(byte, dev->iobase + DAS16_PACER_REG);

	/* set up dma transfer */
	dma->cur_dma = 0;
	das16_ai_setup_dma(dev, s, 0);

	/*  set up समयr */
	spin_lock_irqsave(&dev->spinlock, flags);
	devpriv->समयr_running = 1;
	devpriv->समयr.expires = jअगरfies + समयr_period();
	add_समयr(&devpriv->समयr);

	/* enable DMA पूर्णांकerrupt with बाह्यal or पूर्णांकernal pacing */
	devpriv->ctrl_reg &= ~(DAS16_CTRL_INTE | DAS16_CTRL_PACING_MASK);
	devpriv->ctrl_reg |= DAS16_CTRL_DMAE;
	अगर (cmd->convert_src == TRIG_EXT)
		devpriv->ctrl_reg |= DAS16_CTRL_EXT_PACER;
	अन्यथा
		devpriv->ctrl_reg |= DAS16_CTRL_INT_PACER;
	outb(devpriv->ctrl_reg, dev->iobase + DAS16_CTRL_REG);

	अगर (devpriv->can_burst)
		outb(0, dev->iobase + DAS1600_CONV_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक das16_cancel(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा das16_निजी_काष्ठा *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->spinlock, flags);

	/* disable पूर्णांकerrupts, dma and pacer घड़ीed conversions */
	devpriv->ctrl_reg &= ~(DAS16_CTRL_INTE | DAS16_CTRL_DMAE |
			       DAS16_CTRL_PACING_MASK);
	outb(devpriv->ctrl_reg, dev->iobase + DAS16_CTRL_REG);

	comedi_isadma_disable(dma->chan);

	/*  disable SW समयr */
	अगर (devpriv->समयr_running) अणु
		devpriv->समयr_running = 0;
		del_समयr(&devpriv->समयr);
	पूर्ण

	अगर (devpriv->can_burst)
		outb(0, dev->iobase + DAS1600_BURST_REG);

	spin_unlock_irqrestore(&dev->spinlock, flags);

	वापस 0;
पूर्ण

अटल व्योम das16_ai_munge(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s, व्योम *array,
			   अचिन्हित पूर्णांक num_bytes,
			   अचिन्हित पूर्णांक start_chan_index)
अणु
	अचिन्हित लघु *data = array;
	अचिन्हित पूर्णांक num_samples = comedi_bytes_to_samples(s, num_bytes);
	अचिन्हित पूर्णांक i;
	__le16 *buf = array;

	क्रम (i = 0; i < num_samples; i++) अणु
		data[i] = le16_to_cpu(buf[i]);
		अगर (s->maxdata == 0x0fff)
			data[i] >>= 4;
		data[i] &= s->maxdata;
	पूर्ण
पूर्ण

अटल पूर्णांक das16_ai_eoc(काष्ठा comedi_device *dev,
			काष्ठा comedi_subdevice *s,
			काष्ठा comedi_insn *insn,
			अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inb(dev->iobase + DAS16_STATUS_REG);
	अगर ((status & DAS16_STATUS_BUSY) == 0)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक das16_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;
	पूर्णांक i;

	/* set mux and range क्रम single channel */
	das16_ai_set_mux_range(dev, chan, chan, range);

	क्रम (i = 0; i < insn->n; i++) अणु
		/* trigger conversion */
		outb_p(0, dev->iobase + DAS16_TRIG_REG);

		ret = comedi_समयout(dev, s, insn, das16_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		val = inb(dev->iobase + DAS16_AI_MSB_REG) << 8;
		val |= inb(dev->iobase + DAS16_AI_LSB_REG);
		अगर (s->maxdata == 0x0fff)
			val >>= 4;
		val &= s->maxdata;

		data[i] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक das16_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val = data[i];

		s->पढ़ोback[chan] = val;

		val <<= 4;

		outb(val & 0xff, dev->iobase + DAS16_AO_LSB_REG(chan));
		outb((val >> 8) & 0xff, dev->iobase + DAS16_AO_MSB_REG(chan));
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक das16_di_insn_bits(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	data[1] = inb(dev->iobase + DAS16_DIO_REG) & 0xf;

	वापस insn->n;
पूर्ण

अटल पूर्णांक das16_करो_insn_bits(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		outb(s->state, dev->iobase + DAS16_DIO_REG);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक das16_probe(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा das16_board *board = dev->board_ptr;
	पूर्णांक diobits;

	/* diobits indicates boards */
	diobits = inb(dev->iobase + DAS16_DIO_REG) & 0xf0;
	अगर (board->id != diobits) अणु
		dev_err(dev->class_dev,
			"requested board's id bits are incorrect (0x%x != 0x%x)\n",
			board->id, diobits);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम das16_reset(काष्ठा comedi_device *dev)
अणु
	outb(0, dev->iobase + DAS16_STATUS_REG);
	outb(0, dev->iobase + DAS16_CTRL_REG);
	outb(0, dev->iobase + DAS16_PACER_REG);
पूर्ण

अटल व्योम das16_alloc_dma(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक dma_chan)
अणु
	काष्ठा das16_निजी_काष्ठा *devpriv = dev->निजी;

	समयr_setup(&devpriv->समयr, das16_समयr_पूर्णांकerrupt, 0);

	/* only DMA channels 3 and 1 are valid */
	अगर (!(dma_chan == 1 || dma_chan == 3))
		वापस;

	/* DMA uses two buffers */
	devpriv->dma = comedi_isadma_alloc(dev, 2, dma_chan, dma_chan,
					   DAS16_DMA_SIZE, COMEDI_ISADMA_READ);
पूर्ण

अटल व्योम das16_मुक्त_dma(काष्ठा comedi_device *dev)
अणु
	काष्ठा das16_निजी_काष्ठा *devpriv = dev->निजी;

	अगर (devpriv) अणु
		del_समयr_sync(&devpriv->समयr);
		comedi_isadma_मुक्त(devpriv->dma);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा comedi_lrange *das16_ai_range(काष्ठा comedi_device *dev,
						  काष्ठा comedi_subdevice *s,
						  काष्ठा comedi_devconfig *it,
						  अचिन्हित पूर्णांक pg_type,
						  अचिन्हित पूर्णांक status)
अणु
	अचिन्हित पूर्णांक min = it->options[4];
	अचिन्हित पूर्णांक max = it->options[5];

	/* get any user-defined input range */
	अगर (pg_type == das16_pg_none && (min || max)) अणु
		काष्ठा comedi_lrange *lrange;
		काष्ठा comedi_krange *krange;

		/* allocate single-range range table */
		lrange = comedi_alloc_spriv(s,
					    माप(*lrange) + माप(*krange));
		अगर (!lrange)
			वापस &range_unknown;

		/* initialize ai range */
		lrange->length = 1;
		krange = lrange->range;
		krange->min = min;
		krange->max = max;
		krange->flags = UNIT_volt;

		वापस lrange;
	पूर्ण

	/* use software programmable range */
	अगर (status & DAS16_STATUS_UNIPOLAR)
		वापस das16_ai_uni_lranges[pg_type];
	वापस das16_ai_bip_lranges[pg_type];
पूर्ण

अटल स्थिर काष्ठा comedi_lrange *das16_ao_range(काष्ठा comedi_device *dev,
						  काष्ठा comedi_subdevice *s,
						  काष्ठा comedi_devconfig *it)
अणु
	अचिन्हित पूर्णांक min = it->options[6];
	अचिन्हित पूर्णांक max = it->options[7];

	/* get any user-defined output range */
	अगर (min || max) अणु
		काष्ठा comedi_lrange *lrange;
		काष्ठा comedi_krange *krange;

		/* allocate single-range range table */
		lrange = comedi_alloc_spriv(s,
					    माप(*lrange) + माप(*krange));
		अगर (!lrange)
			वापस &range_unknown;

		/* initialize ao range */
		lrange->length = 1;
		krange = lrange->range;
		krange->min = min;
		krange->max = max;
		krange->flags = UNIT_volt;

		वापस lrange;
	पूर्ण

	वापस &range_unknown;
पूर्ण

अटल पूर्णांक das16_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा das16_board *board = dev->board_ptr;
	काष्ठा das16_निजी_काष्ठा *devpriv;
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक osc_base;
	अचिन्हित पूर्णांक status;
	पूर्णांक ret;

	/*  check that घड़ी setting is valid */
	अगर (it->options[3]) अणु
		अगर (it->options[3] != 1 && it->options[3] != 10) अणु
			dev_err(dev->class_dev,
				"Invalid option. Master clock must be set to 1 or 10 (MHz)\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;
	devpriv->dev = dev;

	अगर (board->size < 0x400) अणु
		ret = comedi_request_region(dev, it->options[0], board->size);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = comedi_request_region(dev, it->options[0], 0x10);
		अगर (ret)
			वापस ret;
		/* Request an additional region क्रम the 8255 */
		ret = __comedi_request_region(dev, dev->iobase + 0x400,
					      board->size & 0x3ff);
		अगर (ret)
			वापस ret;
		devpriv->extra_iobase = dev->iobase + 0x400;
		devpriv->can_burst = 1;
	पूर्ण

	/*  probe id bits to make sure they are consistent */
	अगर (das16_probe(dev, it))
		वापस -EINVAL;

	/*  get master घड़ी speed */
	osc_base = I8254_OSC_BASE_1MHZ;
	अगर (devpriv->can_burst) अणु
		status = inb(dev->iobase + DAS1600_STATUS_REG);
		अगर (status & DAS1600_STATUS_CLK_10MHZ)
			osc_base = I8254_OSC_BASE_10MHZ;
	पूर्ण अन्यथा अणु
		अगर (it->options[3])
			osc_base = I8254_OSC_BASE_1MHZ / it->options[3];
	पूर्ण

	dev->pacer = comedi_8254_init(dev->iobase + DAS16_TIMER_BASE_REG,
				      osc_base, I8254_IO8, 0);
	अगर (!dev->pacer)
		वापस -ENOMEM;

	das16_alloc_dma(dev, it->options[2]);

	ret = comedi_alloc_subdevices(dev, 4 + board->has_8255);
	अगर (ret)
		वापस ret;

	status = inb(dev->iobase + DAS16_STATUS_REG);

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE;
	अगर (status & DAS16_STATUS_MUXBIT) अणु
		s->subdev_flags	|= SDF_GROUND;
		s->n_chan	= 16;
	पूर्ण अन्यथा अणु
		s->subdev_flags	|= SDF_DIFF;
		s->n_chan	= 8;
	पूर्ण
	s->len_chanlist	= s->n_chan;
	s->maxdata	= board->ai_maxdata;
	s->range_table	= das16_ai_range(dev, s, it, board->ai_pg, status);
	s->insn_पढ़ो	= das16_ai_insn_पढ़ो;
	अगर (devpriv->dma) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->करो_cmdtest	= das16_cmd_test;
		s->करो_cmd	= das16_cmd_exec;
		s->cancel	= das16_cancel;
		s->munge	= das16_ai_munge;
	पूर्ण

	/* Analog Output subdevice */
	s = &dev->subdevices[1];
	अगर (board->has_ao) अणु
		s->type		= COMEDI_SUBD_AO;
		s->subdev_flags	= SDF_WRITABLE;
		s->n_chan	= 2;
		s->maxdata	= 0x0fff;
		s->range_table	= das16_ao_range(dev, s, it);
		s->insn_ग_लिखो	= das16_ao_insn_ग_लिखो;

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
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= das16_di_insn_bits;

	/* Digital Output subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= das16_करो_insn_bits;

	/* initialize digital output lines */
	outb(s->state, dev->iobase + DAS16_DIO_REG);

	/* 8255 Digital I/O subdevice */
	अगर (board->has_8255) अणु
		s = &dev->subdevices[4];
		ret = subdev_8255_init(dev, s, शून्य, board->i8255_offset);
		अगर (ret)
			वापस ret;
	पूर्ण

	das16_reset(dev);
	/* set the पूर्णांकerrupt level */
	devpriv->ctrl_reg = DAS16_CTRL_IRQ(dev->irq);
	outb(devpriv->ctrl_reg, dev->iobase + DAS16_CTRL_REG);

	अगर (devpriv->can_burst) अणु
		outb(DAS1600_ENABLE_VAL, dev->iobase + DAS1600_ENABLE_REG);
		outb(0, dev->iobase + DAS1600_CONV_REG);
		outb(0, dev->iobase + DAS1600_BURST_REG);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम das16_detach(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा das16_board *board = dev->board_ptr;
	काष्ठा das16_निजी_काष्ठा *devpriv = dev->निजी;

	अगर (devpriv) अणु
		अगर (dev->iobase)
			das16_reset(dev);
		das16_मुक्त_dma(dev);

		अगर (devpriv->extra_iobase)
			release_region(devpriv->extra_iobase,
				       board->size & 0x3ff);
	पूर्ण

	comedi_legacy_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver das16_driver = अणु
	.driver_name	= "das16",
	.module		= THIS_MODULE,
	.attach		= das16_attach,
	.detach		= das16_detach,
	.board_name	= &das16_boards[0].name,
	.num_names	= ARRAY_SIZE(das16_boards),
	.offset		= माप(das16_boards[0]),
पूर्ण;
module_comedi_driver(das16_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for DAS16 compatible boards");
MODULE_LICENSE("GPL");
