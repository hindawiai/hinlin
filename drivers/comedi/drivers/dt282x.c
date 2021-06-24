<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * dt282x.c
 * Comedi driver क्रम Data Translation DT2821 series
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1997-8 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: dt282x
 * Description: Data Translation DT2821 series (including DT-EZ)
 * Author: ds
 * Devices: [Data Translation] DT2821 (dt2821), DT2821-F-16SE (dt2821-f),
 *   DT2821-F-8DI (dt2821-f), DT2821-G-16SE (dt2821-g),
 *   DT2821-G-8DI (dt2821-g), DT2823 (dt2823), DT2824-PGH (dt2824-pgh),
 *   DT2824-PGL (dt2824-pgl), DT2825 (dt2825), DT2827 (dt2827),
 *   DT2828 (dt2828), DT2928 (dt2829), DT21-EZ (dt21-ez), DT23-EZ (dt23-ez),
 *   DT24-EZ (dt24-ez), DT24-EZ-PGL (dt24-ez-pgl)
 * Status: complete
 * Updated: Wed, 22 Aug 2001 17:11:34 -0700
 *
 * Configuration options:
 *   [0] - I/O port base address
 *   [1] - IRQ (optional, required क्रम async command support)
 *   [2] - DMA 1 (optional, required क्रम async command support)
 *   [3] - DMA 2 (optional, required क्रम async command support)
 *   [4] - AI jumpered क्रम 0=single ended, 1=dअगरferential
 *   [5] - AI jumpered क्रम 0=straight binary, 1=2's complement
 *   [6] - AO 0 data क्रमmat (deprecated, see below)
 *   [7] - AO 1 data क्रमmat (deprecated, see below)
 *   [8] - AI jumpered क्रम 0=[-10,10]V, 1=[0,10], 2=[-5,5], 3=[0,5]
 *   [9] - AO channel 0 range (deprecated, see below)
 *   [10]- AO channel 1 range (deprecated, see below)
 *
 * Notes:
 *   - AO commands might be broken.
 *   - If you try to run a command on both the AI and AO subdevices
 *     simultaneously, bad things will happen.  The driver needs to
 *     be fixed to check क्रम this situation and वापस an error.
 *   - AO range is not programmable. The AO subdevice has a range_table
 *     containing all the possible analog output ranges. Use the range
 *     that matches your board configuration to convert between data
 *     values and physical units. The क्रमmat of the data written to the
 *     board is handled स्वतःmatically based on the unipolar/bipolar
 *     range that is selected.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/gfp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>

#समावेश "../comedidev.h"

#समावेश "comedi_isadma.h"

/*
 * Register map
 */
#घोषणा DT2821_ADCSR_REG		0x00
#घोषणा DT2821_ADCSR_ADERR		BIT(15)
#घोषणा DT2821_ADCSR_ADCLK		BIT(9)
#घोषणा DT2821_ADCSR_MUXBUSY		BIT(8)
#घोषणा DT2821_ADCSR_ADDONE		BIT(7)
#घोषणा DT2821_ADCSR_IADDONE		BIT(6)
#घोषणा DT2821_ADCSR_GS(x)		(((x) & 0x3) << 4)
#घोषणा DT2821_ADCSR_CHAN(x)		(((x) & 0xf) << 0)
#घोषणा DT2821_CHANCSR_REG		0x02
#घोषणा DT2821_CHANCSR_LLE		BIT(15)
#घोषणा DT2821_CHANCSR_TO_PRESLA(x)	(((x) >> 8) & 0xf)
#घोषणा DT2821_CHANCSR_NUMB(x)		((((x) - 1) & 0xf) << 0)
#घोषणा DT2821_ADDAT_REG		0x04
#घोषणा DT2821_DACSR_REG		0x06
#घोषणा DT2821_DACSR_DAERR		BIT(15)
#घोषणा DT2821_DACSR_YSEL(x)		((x) << 9)
#घोषणा DT2821_DACSR_SSEL		BIT(8)
#घोषणा DT2821_DACSR_DACRDY		BIT(7)
#घोषणा DT2821_DACSR_IDARDY		BIT(6)
#घोषणा DT2821_DACSR_DACLK		BIT(5)
#घोषणा DT2821_DACSR_HBOE		BIT(1)
#घोषणा DT2821_DACSR_LBOE		BIT(0)
#घोषणा DT2821_DADAT_REG		0x08
#घोषणा DT2821_DIODAT_REG		0x0a
#घोषणा DT2821_SUPCSR_REG		0x0c
#घोषणा DT2821_SUPCSR_DMAD		BIT(15)
#घोषणा DT2821_SUPCSR_ERRINTEN		BIT(14)
#घोषणा DT2821_SUPCSR_CLRDMADNE		BIT(13)
#घोषणा DT2821_SUPCSR_DDMA		BIT(12)
#घोषणा DT2821_SUPCSR_DS(x)		(((x) & 0x3) << 10)
#घोषणा DT2821_SUPCSR_DS_PIO		DT2821_SUPCSR_DS(0)
#घोषणा DT2821_SUPCSR_DS_AD_CLK		DT2821_SUPCSR_DS(1)
#घोषणा DT2821_SUPCSR_DS_DA_CLK		DT2821_SUPCSR_DS(2)
#घोषणा DT2821_SUPCSR_DS_AD_TRIG	DT2821_SUPCSR_DS(3)
#घोषणा DT2821_SUPCSR_BUFFB		BIT(9)
#घोषणा DT2821_SUPCSR_SCDN		BIT(8)
#घोषणा DT2821_SUPCSR_DACON		BIT(7)
#घोषणा DT2821_SUPCSR_ADCINIT		BIT(6)
#घोषणा DT2821_SUPCSR_DACINIT		BIT(5)
#घोषणा DT2821_SUPCSR_PRLD		BIT(4)
#घोषणा DT2821_SUPCSR_STRIG		BIT(3)
#घोषणा DT2821_SUPCSR_XTRIG		BIT(2)
#घोषणा DT2821_SUPCSR_XCLK		BIT(1)
#घोषणा DT2821_SUPCSR_BDINIT		BIT(0)
#घोषणा DT2821_TMRCTR_REG		0x0e
#घोषणा DT2821_TMRCTR_PRESCALE(x)	(((x) & 0xf) << 8)
#घोषणा DT2821_TMRCTR_DIVIDER(x)	((255 - ((x) & 0xff)) << 0)

/* Pacer Clock */
#घोषणा DT2821_OSC_BASE		250	/* 4 MHz (in nanoseconds) */
#घोषणा DT2821_PRESCALE(x)	BIT(x)
#घोषणा DT2821_PRESCALE_MAX	15
#घोषणा DT2821_DIVIDER_MAX	255
#घोषणा DT2821_OSC_MAX		(DT2821_OSC_BASE *			\
				 DT2821_PRESCALE(DT2821_PRESCALE_MAX) *	\
				 DT2821_DIVIDER_MAX)

अटल स्थिर काष्ठा comedi_lrange range_dt282x_ai_lo_bipolar = अणु
	4, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_dt282x_ai_lo_unipolar = अणु
	4, अणु
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2.5),
		UNI_RANGE(1.25)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_dt282x_ai_5_bipolar = अणु
	4, अणु
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
		BIP_RANGE(0.625)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_dt282x_ai_5_unipolar = अणु
	4, अणु
		UNI_RANGE(5),
		UNI_RANGE(2.5),
		UNI_RANGE(1.25),
		UNI_RANGE(0.625)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_dt282x_ai_hi_bipolar = अणु
	4, अणु
		BIP_RANGE(10),
		BIP_RANGE(1),
		BIP_RANGE(0.1),
		BIP_RANGE(0.02)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_dt282x_ai_hi_unipolar = अणु
	4, अणु
		UNI_RANGE(10),
		UNI_RANGE(1),
		UNI_RANGE(0.1),
		UNI_RANGE(0.02)
	पूर्ण
पूर्ण;

/*
 * The Analog Output range is set per-channel using jumpers on the board.
 * All of these ranges may not be available on some DT2821 series boards.
 * The शेष jumper setting has both channels set क्रम +/-10V output.
 */
अटल स्थिर काष्ठा comedi_lrange dt282x_ao_range = अणु
	5, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		UNI_RANGE(10),
		UNI_RANGE(5),
	पूर्ण
पूर्ण;

काष्ठा dt282x_board अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक ai_maxdata;
	पूर्णांक adchan_se;
	पूर्णांक adchan_di;
	पूर्णांक ai_speed;
	पूर्णांक ispgl;
	पूर्णांक dachan;
	अचिन्हित पूर्णांक ao_maxdata;
पूर्ण;

अटल स्थिर काष्ठा dt282x_board boardtypes[] = अणु
	अणु
		.name		= "dt2821",
		.ai_maxdata	= 0x0fff,
		.adchan_se	= 16,
		.adchan_di	= 8,
		.ai_speed	= 20000,
		.dachan		= 2,
		.ao_maxdata	= 0x0fff,
	पूर्ण, अणु
		.name		= "dt2821-f",
		.ai_maxdata	= 0x0fff,
		.adchan_se	= 16,
		.adchan_di	= 8,
		.ai_speed	= 6500,
		.dachan		= 2,
		.ao_maxdata	= 0x0fff,
	पूर्ण, अणु
		.name		= "dt2821-g",
		.ai_maxdata	= 0x0fff,
		.adchan_se	= 16,
		.adchan_di	= 8,
		.ai_speed	= 4000,
		.dachan		= 2,
		.ao_maxdata	= 0x0fff,
	पूर्ण, अणु
		.name		= "dt2823",
		.ai_maxdata	= 0xffff,
		.adchan_di	= 4,
		.ai_speed	= 10000,
		.dachan		= 2,
		.ao_maxdata	= 0xffff,
	पूर्ण, अणु
		.name		= "dt2824-pgh",
		.ai_maxdata	= 0x0fff,
		.adchan_se	= 16,
		.adchan_di	= 8,
		.ai_speed	= 20000,
	पूर्ण, अणु
		.name		= "dt2824-pgl",
		.ai_maxdata	= 0x0fff,
		.adchan_se	= 16,
		.adchan_di	= 8,
		.ai_speed	= 20000,
		.ispgl		= 1,
	पूर्ण, अणु
		.name		= "dt2825",
		.ai_maxdata	= 0x0fff,
		.adchan_se	= 16,
		.adchan_di	= 8,
		.ai_speed	= 20000,
		.ispgl		= 1,
		.dachan		= 2,
		.ao_maxdata	= 0x0fff,
	पूर्ण, अणु
		.name		= "dt2827",
		.ai_maxdata	= 0xffff,
		.adchan_di	= 4,
		.ai_speed	= 10000,
		.dachan		= 2,
		.ao_maxdata	= 0x0fff,
	पूर्ण, अणु
		.name		= "dt2828",
		.ai_maxdata	= 0x0fff,
		.adchan_se	= 4,
		.ai_speed	= 10000,
		.dachan		= 2,
		.ao_maxdata	= 0x0fff,
	पूर्ण, अणु
		.name		= "dt2829",
		.ai_maxdata	= 0xffff,
		.adchan_se	= 8,
		.ai_speed	= 33250,
		.dachan		= 2,
		.ao_maxdata	= 0xffff,
	पूर्ण, अणु
		.name		= "dt21-ez",
		.ai_maxdata	= 0x0fff,
		.adchan_se	= 16,
		.adchan_di	= 8,
		.ai_speed	= 10000,
		.dachan		= 2,
		.ao_maxdata	= 0x0fff,
	पूर्ण, अणु
		.name		= "dt23-ez",
		.ai_maxdata	= 0xffff,
		.adchan_se	= 16,
		.adchan_di	= 8,
		.ai_speed	= 10000,
	पूर्ण, अणु
		.name		= "dt24-ez",
		.ai_maxdata	= 0x0fff,
		.adchan_se	= 16,
		.adchan_di	= 8,
		.ai_speed	= 10000,
	पूर्ण, अणु
		.name		= "dt24-ez-pgl",
		.ai_maxdata	= 0x0fff,
		.adchan_se	= 16,
		.adchan_di	= 8,
		.ai_speed	= 10000,
		.ispgl		= 1,
	पूर्ण,
पूर्ण;

काष्ठा dt282x_निजी अणु
	काष्ठा comedi_isadma *dma;
	अचिन्हित पूर्णांक ad_2scomp:1;
	अचिन्हित पूर्णांक भागisor;
	पूर्णांक dacsr;	/* software copies of रेजिस्टरs */
	पूर्णांक adcsr;
	पूर्णांक supcsr;
	पूर्णांक ntrig;
	पूर्णांक nपढ़ो;
	पूर्णांक dma_dir;
पूर्ण;

अटल पूर्णांक dt282x_prep_ai_dma(काष्ठा comedi_device *dev, पूर्णांक dma_index, पूर्णांक n)
अणु
	काष्ठा dt282x_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_isadma_desc *desc = &dma->desc[dma_index];

	अगर (!devpriv->ntrig)
		वापस 0;

	अगर (n == 0)
		n = desc->maxsize;
	अगर (n > devpriv->ntrig * 2)
		n = devpriv->ntrig * 2;
	devpriv->ntrig -= n / 2;

	desc->size = n;
	comedi_isadma_set_mode(desc, devpriv->dma_dir);

	comedi_isadma_program(desc);

	वापस n;
पूर्ण

अटल पूर्णांक dt282x_prep_ao_dma(काष्ठा comedi_device *dev, पूर्णांक dma_index, पूर्णांक n)
अणु
	काष्ठा dt282x_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_isadma_desc *desc = &dma->desc[dma_index];

	desc->size = n;
	comedi_isadma_set_mode(desc, devpriv->dma_dir);

	comedi_isadma_program(desc);

	वापस n;
पूर्ण

अटल व्योम dt282x_disable_dma(काष्ठा comedi_device *dev)
अणु
	काष्ठा dt282x_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_isadma_desc *desc;
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		desc = &dma->desc[i];
		comedi_isadma_disable(desc->chan);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक dt282x_ns_to_समयr(अचिन्हित पूर्णांक *ns, अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक prescale, base, भागider;

	क्रम (prescale = 0; prescale <= DT2821_PRESCALE_MAX; prescale++) अणु
		अगर (prescale == 1)	/* 0 and 1 are both भागide by 1 */
			जारी;
		base = DT2821_OSC_BASE * DT2821_PRESCALE(prescale);
		चयन (flags & CMDF_ROUND_MASK) अणु
		हाल CMDF_ROUND_NEAREST:
		शेष:
			भागider = DIV_ROUND_CLOSEST(*ns, base);
			अवरोध;
		हाल CMDF_ROUND_DOWN:
			भागider = (*ns) / base;
			अवरोध;
		हाल CMDF_ROUND_UP:
			भागider = DIV_ROUND_UP(*ns, base);
			अवरोध;
		पूर्ण
		अगर (भागider <= DT2821_DIVIDER_MAX)
			अवरोध;
	पूर्ण
	अगर (भागider > DT2821_DIVIDER_MAX) अणु
		prescale = DT2821_PRESCALE_MAX;
		भागider = DT2821_DIVIDER_MAX;
		base = DT2821_OSC_BASE * DT2821_PRESCALE(prescale);
	पूर्ण
	*ns = भागider * base;
	वापस DT2821_TMRCTR_PRESCALE(prescale) |
	       DT2821_TMRCTR_DIVIDER(भागider);
पूर्ण

अटल व्योम dt282x_munge(काष्ठा comedi_device *dev,
			 काष्ठा comedi_subdevice *s,
			 अचिन्हित लघु *buf,
			 अचिन्हित पूर्णांक nbytes)
अणु
	काष्ठा dt282x_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	अगर (nbytes % 2)
		dev_err(dev->class_dev,
			"bug! odd number of bytes from dma xfer\n");

	क्रम (i = 0; i < nbytes / 2; i++) अणु
		val = buf[i];
		val &= s->maxdata;
		अगर (devpriv->ad_2scomp)
			val = comedi_offset_munge(s, val);

		buf[i] = val;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक dt282x_ao_setup_dma(काष्ठा comedi_device *dev,
					काष्ठा comedi_subdevice *s,
					पूर्णांक cur_dma)
अणु
	काष्ठा dt282x_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_isadma_desc *desc = &dma->desc[cur_dma];
	अचिन्हित पूर्णांक nsamples = comedi_bytes_to_samples(s, desc->maxsize);
	अचिन्हित पूर्णांक nbytes;

	nbytes = comedi_buf_पढ़ो_samples(s, desc->virt_addr, nsamples);
	अगर (nbytes)
		dt282x_prep_ao_dma(dev, cur_dma, nbytes);
	अन्यथा
		dev_err(dev->class_dev, "AO underrun\n");

	वापस nbytes;
पूर्ण

अटल व्योम dt282x_ao_dma_पूर्णांकerrupt(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s)
अणु
	काष्ठा dt282x_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_isadma_desc *desc = &dma->desc[dma->cur_dma];

	outw(devpriv->supcsr | DT2821_SUPCSR_CLRDMADNE,
	     dev->iobase + DT2821_SUPCSR_REG);

	comedi_isadma_disable(desc->chan);

	अगर (!dt282x_ao_setup_dma(dev, s, dma->cur_dma))
		s->async->events |= COMEDI_CB_OVERFLOW;

	dma->cur_dma = 1 - dma->cur_dma;
पूर्ण

अटल व्योम dt282x_ai_dma_पूर्णांकerrupt(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s)
अणु
	काष्ठा dt282x_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_isadma_desc *desc = &dma->desc[dma->cur_dma];
	अचिन्हित पूर्णांक nsamples = comedi_bytes_to_samples(s, desc->size);
	पूर्णांक ret;

	outw(devpriv->supcsr | DT2821_SUPCSR_CLRDMADNE,
	     dev->iobase + DT2821_SUPCSR_REG);

	comedi_isadma_disable(desc->chan);

	dt282x_munge(dev, s, desc->virt_addr, desc->size);
	ret = comedi_buf_ग_लिखो_samples(s, desc->virt_addr, nsamples);
	अगर (ret != desc->size)
		वापस;

	devpriv->nपढ़ो -= nsamples;
	अगर (devpriv->nपढ़ो < 0) अणु
		dev_info(dev->class_dev, "nread off by one\n");
		devpriv->nपढ़ो = 0;
	पूर्ण
	अगर (!devpriv->nपढ़ो) अणु
		s->async->events |= COMEDI_CB_EOA;
		वापस;
	पूर्ण

	/* restart the channel */
	dt282x_prep_ai_dma(dev, dma->cur_dma, 0);

	dma->cur_dma = 1 - dma->cur_dma;
पूर्ण

अटल irqवापस_t dt282x_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा dt282x_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_subdevice *s_ao = dev->ग_लिखो_subdev;
	अचिन्हित पूर्णांक supcsr, adcsr, dacsr;
	पूर्णांक handled = 0;

	अगर (!dev->attached) अणु
		dev_err(dev->class_dev, "spurious interrupt\n");
		वापस IRQ_HANDLED;
	पूर्ण

	adcsr = inw(dev->iobase + DT2821_ADCSR_REG);
	dacsr = inw(dev->iobase + DT2821_DACSR_REG);
	supcsr = inw(dev->iobase + DT2821_SUPCSR_REG);
	अगर (supcsr & DT2821_SUPCSR_DMAD) अणु
		अगर (devpriv->dma_dir == COMEDI_ISADMA_READ)
			dt282x_ai_dma_पूर्णांकerrupt(dev, s);
		अन्यथा
			dt282x_ao_dma_पूर्णांकerrupt(dev, s_ao);
		handled = 1;
	पूर्ण
	अगर (adcsr & DT2821_ADCSR_ADERR) अणु
		अगर (devpriv->nपढ़ो != 0) अणु
			dev_err(dev->class_dev, "A/D error\n");
			s->async->events |= COMEDI_CB_ERROR;
		पूर्ण
		handled = 1;
	पूर्ण
	अगर (dacsr & DT2821_DACSR_DAERR) अणु
		dev_err(dev->class_dev, "D/A error\n");
		s_ao->async->events |= COMEDI_CB_ERROR;
		handled = 1;
	पूर्ण

	comedi_handle_events(dev, s);
	अगर (s_ao)
		comedi_handle_events(dev, s_ao);

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम dt282x_load_changain(काष्ठा comedi_device *dev, पूर्णांक n,
				 अचिन्हित पूर्णांक *chanlist)
अणु
	काष्ठा dt282x_निजी *devpriv = dev->निजी;
	पूर्णांक i;

	outw(DT2821_CHANCSR_LLE | DT2821_CHANCSR_NUMB(n),
	     dev->iobase + DT2821_CHANCSR_REG);
	क्रम (i = 0; i < n; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(chanlist[i]);
		अचिन्हित पूर्णांक range = CR_RANGE(chanlist[i]);

		outw(devpriv->adcsr |
		     DT2821_ADCSR_GS(range) |
		     DT2821_ADCSR_CHAN(chan),
		     dev->iobase + DT2821_ADCSR_REG);
	पूर्ण
	outw(DT2821_CHANCSR_NUMB(n), dev->iobase + DT2821_CHANCSR_REG);
पूर्ण

अटल पूर्णांक dt282x_ai_समयout(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_insn *insn,
			     अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inw(dev->iobase + DT2821_ADCSR_REG);
	चयन (context) अणु
	हाल DT2821_ADCSR_MUXBUSY:
		अगर ((status & DT2821_ADCSR_MUXBUSY) == 0)
			वापस 0;
		अवरोध;
	हाल DT2821_ADCSR_ADDONE:
		अगर (status & DT2821_ADCSR_ADDONE)
			वापस 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस -EBUSY;
पूर्ण

/*
 *    Perक्रमms a single A/D conversion.
 *      - Put channel/gain पूर्णांकo channel-gain list
 *      - preload multiplexer
 *      - trigger conversion and रुको क्रम it to finish
 */
अटल पूर्णांक dt282x_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	काष्ठा dt282x_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;
	पूर्णांक i;

	/* XXX should we really be enabling the ad घड़ी here? */
	devpriv->adcsr = DT2821_ADCSR_ADCLK;
	outw(devpriv->adcsr, dev->iobase + DT2821_ADCSR_REG);

	dt282x_load_changain(dev, 1, &insn->chanspec);

	outw(devpriv->supcsr | DT2821_SUPCSR_PRLD,
	     dev->iobase + DT2821_SUPCSR_REG);
	ret = comedi_समयout(dev, s, insn,
			     dt282x_ai_समयout, DT2821_ADCSR_MUXBUSY);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < insn->n; i++) अणु
		outw(devpriv->supcsr | DT2821_SUPCSR_STRIG,
		     dev->iobase + DT2821_SUPCSR_REG);

		ret = comedi_समयout(dev, s, insn,
				     dt282x_ai_समयout, DT2821_ADCSR_ADDONE);
		अगर (ret)
			वापस ret;

		val = inw(dev->iobase + DT2821_ADDAT_REG);
		val &= s->maxdata;
		अगर (devpriv->ad_2scomp)
			val = comedi_offset_munge(s, val);

		data[i] = val;
	पूर्ण

	वापस i;
पूर्ण

अटल पूर्णांक dt282x_ai_cmdtest(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा dt282x_board *board = dev->board_ptr;
	काष्ठा dt282x_निजी *devpriv = dev->निजी;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक arg;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_FOLLOW | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_TIMER);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);
	err |= comedi_check_trigger_arg_max(&cmd->convert_arg, DT2821_OSC_MAX);
	err |= comedi_check_trigger_arg_min(&cmd->convert_arg, board->ai_speed);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_EXT | TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* step 4: fix up any arguments */

	arg = cmd->convert_arg;
	devpriv->भागisor = dt282x_ns_to_समयr(&arg, cmd->flags);
	err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg);

	अगर (err)
		वापस 4;

	वापस 0;
पूर्ण

अटल पूर्णांक dt282x_ai_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा dt282x_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	पूर्णांक ret;

	dt282x_disable_dma(dev);

	outw(devpriv->भागisor, dev->iobase + DT2821_TMRCTR_REG);

	devpriv->supcsr = DT2821_SUPCSR_ERRINTEN;
	अगर (cmd->scan_begin_src == TRIG_FOLLOW)
		devpriv->supcsr = DT2821_SUPCSR_DS_AD_CLK;
	अन्यथा
		devpriv->supcsr = DT2821_SUPCSR_DS_AD_TRIG;
	outw(devpriv->supcsr |
	     DT2821_SUPCSR_CLRDMADNE |
	     DT2821_SUPCSR_BUFFB |
	     DT2821_SUPCSR_ADCINIT,
	     dev->iobase + DT2821_SUPCSR_REG);

	devpriv->ntrig = cmd->stop_arg * cmd->scan_end_arg;
	devpriv->nपढ़ो = devpriv->ntrig;

	devpriv->dma_dir = COMEDI_ISADMA_READ;
	dma->cur_dma = 0;
	dt282x_prep_ai_dma(dev, 0, 0);
	अगर (devpriv->ntrig) अणु
		dt282x_prep_ai_dma(dev, 1, 0);
		devpriv->supcsr |= DT2821_SUPCSR_DDMA;
		outw(devpriv->supcsr, dev->iobase + DT2821_SUPCSR_REG);
	पूर्ण

	devpriv->adcsr = 0;

	dt282x_load_changain(dev, cmd->chanlist_len, cmd->chanlist);

	devpriv->adcsr = DT2821_ADCSR_ADCLK | DT2821_ADCSR_IADDONE;
	outw(devpriv->adcsr, dev->iobase + DT2821_ADCSR_REG);

	outw(devpriv->supcsr | DT2821_SUPCSR_PRLD,
	     dev->iobase + DT2821_SUPCSR_REG);
	ret = comedi_समयout(dev, s, शून्य,
			     dt282x_ai_समयout, DT2821_ADCSR_MUXBUSY);
	अगर (ret)
		वापस ret;

	अगर (cmd->scan_begin_src == TRIG_FOLLOW) अणु
		outw(devpriv->supcsr | DT2821_SUPCSR_STRIG,
		     dev->iobase + DT2821_SUPCSR_REG);
	पूर्ण अन्यथा अणु
		devpriv->supcsr |= DT2821_SUPCSR_XTRIG;
		outw(devpriv->supcsr, dev->iobase + DT2821_SUPCSR_REG);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dt282x_ai_cancel(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	काष्ठा dt282x_निजी *devpriv = dev->निजी;

	dt282x_disable_dma(dev);

	devpriv->adcsr = 0;
	outw(devpriv->adcsr, dev->iobase + DT2821_ADCSR_REG);

	devpriv->supcsr = 0;
	outw(devpriv->supcsr | DT2821_SUPCSR_ADCINIT,
	     dev->iobase + DT2821_SUPCSR_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक dt282x_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	काष्ठा dt282x_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	पूर्णांक i;

	devpriv->dacsr |= DT2821_DACSR_SSEL | DT2821_DACSR_YSEL(chan);

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val = data[i];

		s->पढ़ोback[chan] = val;

		अगर (comedi_range_is_bipolar(s, range))
			val = comedi_offset_munge(s, val);

		outw(devpriv->dacsr, dev->iobase + DT2821_DACSR_REG);

		outw(val, dev->iobase + DT2821_DADAT_REG);

		outw(devpriv->supcsr | DT2821_SUPCSR_DACON,
		     dev->iobase + DT2821_SUPCSR_REG);
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक dt282x_ao_cmdtest(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा dt282x_निजी *devpriv = dev->निजी;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक arg;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_INT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_TIMER);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_NOW);
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
	err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg, 5000);
	err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_EXT | TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* step 4: fix up any arguments */

	arg = cmd->scan_begin_arg;
	devpriv->भागisor = dt282x_ns_to_समयr(&arg, cmd->flags);
	err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);

	अगर (err)
		वापस 4;

	वापस 0;
पूर्ण

अटल पूर्णांक dt282x_ao_पूर्णांकtrig(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा dt282x_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;

	अगर (trig_num != cmd->start_src)
		वापस -EINVAL;

	अगर (!dt282x_ao_setup_dma(dev, s, 0))
		वापस -EPIPE;

	अगर (!dt282x_ao_setup_dma(dev, s, 1))
		वापस -EPIPE;

	outw(devpriv->supcsr | DT2821_SUPCSR_STRIG,
	     dev->iobase + DT2821_SUPCSR_REG);
	s->async->पूर्णांकtrig = शून्य;

	वापस 1;
पूर्ण

अटल पूर्णांक dt282x_ao_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा dt282x_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma *dma = devpriv->dma;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;

	dt282x_disable_dma(dev);

	devpriv->supcsr = DT2821_SUPCSR_ERRINTEN |
			  DT2821_SUPCSR_DS_DA_CLK |
			  DT2821_SUPCSR_DDMA;
	outw(devpriv->supcsr |
	     DT2821_SUPCSR_CLRDMADNE |
	     DT2821_SUPCSR_BUFFB |
	     DT2821_SUPCSR_DACINIT,
	     dev->iobase + DT2821_SUPCSR_REG);

	devpriv->ntrig = cmd->stop_arg * cmd->chanlist_len;
	devpriv->nपढ़ो = devpriv->ntrig;

	devpriv->dma_dir = COMEDI_ISADMA_WRITE;
	dma->cur_dma = 0;

	outw(devpriv->भागisor, dev->iobase + DT2821_TMRCTR_REG);

	/* clear all bits but the DIO direction bits */
	devpriv->dacsr &= (DT2821_DACSR_LBOE | DT2821_DACSR_HBOE);

	devpriv->dacsr |= (DT2821_DACSR_SSEL |
			   DT2821_DACSR_DACLK |
			   DT2821_DACSR_IDARDY);
	outw(devpriv->dacsr, dev->iobase + DT2821_DACSR_REG);

	s->async->पूर्णांकtrig = dt282x_ao_पूर्णांकtrig;

	वापस 0;
पूर्ण

अटल पूर्णांक dt282x_ao_cancel(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	काष्ठा dt282x_निजी *devpriv = dev->निजी;

	dt282x_disable_dma(dev);

	/* clear all bits but the DIO direction bits */
	devpriv->dacsr &= (DT2821_DACSR_LBOE | DT2821_DACSR_HBOE);

	outw(devpriv->dacsr, dev->iobase + DT2821_DACSR_REG);

	devpriv->supcsr = 0;
	outw(devpriv->supcsr | DT2821_SUPCSR_DACINIT,
	     dev->iobase + DT2821_SUPCSR_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक dt282x_dio_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		outw(s->state, dev->iobase + DT2821_DIODAT_REG);

	data[1] = inw(dev->iobase + DT2821_DIODAT_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक dt282x_dio_insn_config(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	काष्ठा dt282x_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक mask;
	पूर्णांक ret;

	अगर (chan < 8)
		mask = 0x00ff;
	अन्यथा
		mask = 0xff00;

	ret = comedi_dio_insn_config(dev, s, insn, data, mask);
	अगर (ret)
		वापस ret;

	devpriv->dacsr &= ~(DT2821_DACSR_LBOE | DT2821_DACSR_HBOE);
	अगर (s->io_bits & 0x00ff)
		devpriv->dacsr |= DT2821_DACSR_LBOE;
	अगर (s->io_bits & 0xff00)
		devpriv->dacsr |= DT2821_DACSR_HBOE;

	outw(devpriv->dacsr, dev->iobase + DT2821_DACSR_REG);

	वापस insn->n;
पूर्ण

अटल स्थिर काष्ठा comedi_lrange *स्थिर ai_range_table[] = अणु
	&range_dt282x_ai_lo_bipolar,
	&range_dt282x_ai_lo_unipolar,
	&range_dt282x_ai_5_bipolar,
	&range_dt282x_ai_5_unipolar
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange *स्थिर ai_range_pgl_table[] = अणु
	&range_dt282x_ai_hi_bipolar,
	&range_dt282x_ai_hi_unipolar
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange *opt_ai_range_lkup(पूर्णांक ispgl, पूर्णांक x)
अणु
	अगर (ispgl) अणु
		अगर (x < 0 || x >= 2)
			x = 0;
		वापस ai_range_pgl_table[x];
	पूर्ण

	अगर (x < 0 || x >= 4)
		x = 0;
	वापस ai_range_table[x];
पूर्ण

अटल व्योम dt282x_alloc_dma(काष्ठा comedi_device *dev,
			     काष्ठा comedi_devconfig *it)
अणु
	काष्ठा dt282x_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक irq_num = it->options[1];
	अचिन्हित पूर्णांक dma_chan[2];

	अगर (it->options[2] < it->options[3]) अणु
		dma_chan[0] = it->options[2];
		dma_chan[1] = it->options[3];
	पूर्ण अन्यथा अणु
		dma_chan[0] = it->options[3];
		dma_chan[1] = it->options[2];
	पूर्ण

	अगर (!irq_num || dma_chan[0] == dma_chan[1] ||
	    dma_chan[0] < 5 || dma_chan[0] > 7 ||
	    dma_chan[1] < 5 || dma_chan[1] > 7)
		वापस;

	अगर (request_irq(irq_num, dt282x_पूर्णांकerrupt, 0, dev->board_name, dev))
		वापस;

	/* DMA uses two 4K buffers with separate DMA channels */
	devpriv->dma = comedi_isadma_alloc(dev, 2, dma_chan[0], dma_chan[1],
					   PAGE_SIZE, 0);
	अगर (!devpriv->dma)
		मुक्त_irq(irq_num, dev);
	अन्यथा
		dev->irq = irq_num;
पूर्ण

अटल व्योम dt282x_मुक्त_dma(काष्ठा comedi_device *dev)
अणु
	काष्ठा dt282x_निजी *devpriv = dev->निजी;

	अगर (devpriv)
		comedi_isadma_मुक्त(devpriv->dma);
पूर्ण

अटल पूर्णांक dt282x_initialize(काष्ठा comedi_device *dev)
अणु
	/* Initialize board */
	outw(DT2821_SUPCSR_BDINIT, dev->iobase + DT2821_SUPCSR_REG);
	inw(dev->iobase + DT2821_ADCSR_REG);

	/*
	 * At घातer up, some रेजिस्टरs are in a well-known state.
	 * Check them to see अगर a DT2821 series board is present.
	 */
	अगर (((inw(dev->iobase + DT2821_ADCSR_REG) & 0xfff0) != 0x7c00) ||
	    ((inw(dev->iobase + DT2821_CHANCSR_REG) & 0xf0f0) != 0x70f0) ||
	    ((inw(dev->iobase + DT2821_DACSR_REG) & 0x7c93) != 0x7c90) ||
	    ((inw(dev->iobase + DT2821_SUPCSR_REG) & 0xf8ff) != 0x0000) ||
	    ((inw(dev->iobase + DT2821_TMRCTR_REG) & 0xff00) != 0xf000)) अणु
		dev_err(dev->class_dev, "board not found\n");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dt282x_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा dt282x_board *board = dev->board_ptr;
	काष्ठा dt282x_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], 0x10);
	अगर (ret)
		वापस ret;

	ret = dt282x_initialize(dev);
	अगर (ret)
		वापस ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	/* an IRQ and 2 DMA channels are required क्रम async command support */
	dt282x_alloc_dma(dev, it);

	ret = comedi_alloc_subdevices(dev, 3);
	अगर (ret)
		वापस ret;

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE;
	अगर ((it->options[4] && board->adchan_di) || board->adchan_se == 0) अणु
		s->subdev_flags	|= SDF_DIFF;
		s->n_chan	= board->adchan_di;
	पूर्ण अन्यथा अणु
		s->subdev_flags	|= SDF_COMMON;
		s->n_chan	= board->adchan_se;
	पूर्ण
	s->maxdata	= board->ai_maxdata;

	s->range_table = opt_ai_range_lkup(board->ispgl, it->options[8]);
	devpriv->ad_2scomp = it->options[5] ? 1 : 0;

	s->insn_पढ़ो	= dt282x_ai_insn_पढ़ो;
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->len_chanlist	= s->n_chan;
		s->करो_cmdtest	= dt282x_ai_cmdtest;
		s->करो_cmd	= dt282x_ai_cmd;
		s->cancel	= dt282x_ai_cancel;
	पूर्ण

	/* Analog Output subdevice */
	s = &dev->subdevices[1];
	अगर (board->dachan) अणु
		s->type		= COMEDI_SUBD_AO;
		s->subdev_flags	= SDF_WRITABLE;
		s->n_chan	= board->dachan;
		s->maxdata	= board->ao_maxdata;
		/* ranges are per-channel, set by jumpers on the board */
		s->range_table	= &dt282x_ao_range;
		s->insn_ग_लिखो	= dt282x_ao_insn_ग_लिखो;
		अगर (dev->irq) अणु
			dev->ग_लिखो_subdev = s;
			s->subdev_flags	|= SDF_CMD_WRITE;
			s->len_chanlist	= s->n_chan;
			s->करो_cmdtest	= dt282x_ao_cmdtest;
			s->करो_cmd	= dt282x_ao_cmd;
			s->cancel	= dt282x_ao_cancel;
		पूर्ण

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
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= dt282x_dio_insn_bits;
	s->insn_config	= dt282x_dio_insn_config;

	वापस 0;
पूर्ण

अटल व्योम dt282x_detach(काष्ठा comedi_device *dev)
अणु
	dt282x_मुक्त_dma(dev);
	comedi_legacy_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver dt282x_driver = अणु
	.driver_name	= "dt282x",
	.module		= THIS_MODULE,
	.attach		= dt282x_attach,
	.detach		= dt282x_detach,
	.board_name	= &boardtypes[0].name,
	.num_names	= ARRAY_SIZE(boardtypes),
	.offset		= माप(काष्ठा dt282x_board),
पूर्ण;
module_comedi_driver(dt282x_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for Data Translation DT2821 series");
MODULE_LICENSE("GPL");
