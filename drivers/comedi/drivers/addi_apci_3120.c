<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * addi_apci_3120.c
 * Copyright (C) 2004,2005  ADDI-DATA GmbH क्रम the source code of this module.
 *
 *	ADDI-DATA GmbH
 *	Dieselstrasse 3
 *	D-77833 Ottersweier
 *	Tel: +19(0)7223/9493-0
 *	Fax: +49(0)7223/9493-92
 *	http://www.addi-data.com
 *	info@addi-data.com
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedi_pci.h"
#समावेश "amcc_s5933.h"

/*
 * PCI BAR 0 रेजिस्टर map (devpriv->amcc)
 * see amcc_s5933.h क्रम रेजिस्टर and bit defines
 */
#घोषणा APCI3120_FIFO_ADVANCE_ON_BYTE_2		BIT(29)

/*
 * PCI BAR 1 रेजिस्टर map (dev->iobase)
 */
#घोषणा APCI3120_AI_FIFO_REG			0x00
#घोषणा APCI3120_CTRL_REG			0x00
#घोषणा APCI3120_CTRL_EXT_TRIG			BIT(15)
#घोषणा APCI3120_CTRL_GATE(x)			BIT(12 + (x))
#घोषणा APCI3120_CTRL_PR(x)			(((x) & 0xf) << 8)
#घोषणा APCI3120_CTRL_PA(x)			(((x) & 0xf) << 0)
#घोषणा APCI3120_AI_SOFTTRIG_REG		0x02
#घोषणा APCI3120_STATUS_REG			0x02
#घोषणा APCI3120_STATUS_EOC_INT			BIT(15)
#घोषणा APCI3120_STATUS_AMCC_INT		BIT(14)
#घोषणा APCI3120_STATUS_EOS_INT			BIT(13)
#घोषणा APCI3120_STATUS_TIMER2_INT		BIT(12)
#घोषणा APCI3120_STATUS_INT_MASK		(0xf << 12)
#घोषणा APCI3120_STATUS_TO_DI_BITS(x)		(((x) >> 8) & 0xf)
#घोषणा APCI3120_STATUS_TO_VERSION(x)		(((x) >> 4) & 0xf)
#घोषणा APCI3120_STATUS_FIFO_FULL		BIT(2)
#घोषणा APCI3120_STATUS_FIFO_EMPTY		BIT(1)
#घोषणा APCI3120_STATUS_DA_READY		BIT(0)
#घोषणा APCI3120_TIMER_REG			0x04
#घोषणा APCI3120_CHANLIST_REG			0x06
#घोषणा APCI3120_CHANLIST_INDEX(x)		(((x) & 0xf) << 8)
#घोषणा APCI3120_CHANLIST_UNIPOLAR		BIT(7)
#घोषणा APCI3120_CHANLIST_GAIN(x)		(((x) & 0x3) << 4)
#घोषणा APCI3120_CHANLIST_MUX(x)		(((x) & 0xf) << 0)
#घोषणा APCI3120_AO_REG(x)			(0x08 + (((x) / 4) * 2))
#घोषणा APCI3120_AO_MUX(x)			(((x) & 0x3) << 14)
#घोषणा APCI3120_AO_DATA(x)			((x) << 0)
#घोषणा APCI3120_TIMER_MODE_REG			0x0c
#घोषणा APCI3120_TIMER_MODE(_t, _m)		((_m) << ((_t) * 2))
#घोषणा APCI3120_TIMER_MODE0			0  /* I8254_MODE0 */
#घोषणा APCI3120_TIMER_MODE2			1  /* I8254_MODE2 */
#घोषणा APCI3120_TIMER_MODE4			2  /* I8254_MODE4 */
#घोषणा APCI3120_TIMER_MODE5			3  /* I8254_MODE5 */
#घोषणा APCI3120_TIMER_MODE_MASK(_t)		(3 << ((_t) * 2))
#घोषणा APCI3120_CTR0_REG			0x0d
#घोषणा APCI3120_CTR0_DO_BITS(x)		((x) << 4)
#घोषणा APCI3120_CTR0_TIMER_SEL(x)		((x) << 0)
#घोषणा APCI3120_MODE_REG			0x0e
#घोषणा APCI3120_MODE_TIMER2_CLK(x)		(((x) & 0x3) << 6)
#घोषणा APCI3120_MODE_TIMER2_CLK_OSC		APCI3120_MODE_TIMER2_CLK(0)
#घोषणा APCI3120_MODE_TIMER2_CLK_OUT1		APCI3120_MODE_TIMER2_CLK(1)
#घोषणा APCI3120_MODE_TIMER2_CLK_EOC		APCI3120_MODE_TIMER2_CLK(2)
#घोषणा APCI3120_MODE_TIMER2_CLK_EOS		APCI3120_MODE_TIMER2_CLK(3)
#घोषणा APCI3120_MODE_TIMER2_CLK_MASK		APCI3120_MODE_TIMER2_CLK(3)
#घोषणा APCI3120_MODE_TIMER2_AS(x)		(((x) & 0x3) << 4)
#घोषणा APCI3120_MODE_TIMER2_AS_TIMER		APCI3120_MODE_TIMER2_AS(0)
#घोषणा APCI3120_MODE_TIMER2_AS_COUNTER		APCI3120_MODE_TIMER2_AS(1)
#घोषणा APCI3120_MODE_TIMER2_AS_WDOG		APCI3120_MODE_TIMER2_AS(2)
#घोषणा APCI3120_MODE_TIMER2_AS_MASK		APCI3120_MODE_TIMER2_AS(3)
#घोषणा APCI3120_MODE_SCAN_ENA			BIT(3)
#घोषणा APCI3120_MODE_TIMER2_IRQ_ENA		BIT(2)
#घोषणा APCI3120_MODE_EOS_IRQ_ENA		BIT(1)
#घोषणा APCI3120_MODE_EOC_IRQ_ENA		BIT(0)

/*
 * PCI BAR 2 रेजिस्टर map (devpriv->adकरोn)
 */
#घोषणा APCI3120_ADDON_ADDR_REG			0x00
#घोषणा APCI3120_ADDON_DATA_REG			0x02
#घोषणा APCI3120_ADDON_CTRL_REG			0x04
#घोषणा APCI3120_ADDON_CTRL_AMWEN_ENA		BIT(1)
#घोषणा APCI3120_ADDON_CTRL_A2P_FIFO_ENA	BIT(0)

/*
 * Board revisions
 */
#घोषणा APCI3120_REVA				0xa
#घोषणा APCI3120_REVB				0xb
#घोषणा APCI3120_REVA_OSC_BASE			70	/* 70ns = 14.29MHz */
#घोषणा APCI3120_REVB_OSC_BASE			50	/* 50ns = 20MHz */

अटल स्थिर काष्ठा comedi_lrange apci3120_ai_range = अणु
	8, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2),
		BIP_RANGE(1),
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2),
		UNI_RANGE(1)
	पूर्ण
पूर्ण;

क्रमागत apci3120_boardid अणु
	BOARD_APCI3120,
	BOARD_APCI3001,
पूर्ण;

काष्ठा apci3120_board अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक ai_is_16bit:1;
	अचिन्हित पूर्णांक has_ao:1;
पूर्ण;

अटल स्थिर काष्ठा apci3120_board apci3120_boardtypes[] = अणु
	[BOARD_APCI3120] = अणु
		.name		= "apci3120",
		.ai_is_16bit	= 1,
		.has_ao		= 1,
	पूर्ण,
	[BOARD_APCI3001] = अणु
		.name		= "apci3001",
	पूर्ण,
पूर्ण;

काष्ठा apci3120_dmabuf अणु
	अचिन्हित लघु *virt;
	dma_addr_t hw;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक use_size;
पूर्ण;

काष्ठा apci3120_निजी अणु
	अचिन्हित दीर्घ amcc;
	अचिन्हित दीर्घ adकरोn;
	अचिन्हित पूर्णांक osc_base;
	अचिन्हित पूर्णांक use_dma:1;
	अचिन्हित पूर्णांक use_द्विगुन_buffer:1;
	अचिन्हित पूर्णांक cur_dmabuf:1;
	काष्ठा apci3120_dmabuf dmabuf[2];
	अचिन्हित अक्षर करो_bits;
	अचिन्हित अक्षर समयr_mode;
	अचिन्हित अक्षर mode;
	अचिन्हित लघु ctrl;
पूर्ण;

अटल व्योम apci3120_adकरोn_ग_लिखो(काष्ठा comedi_device *dev,
				 अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा apci3120_निजी *devpriv = dev->निजी;

	/* 16-bit पूर्णांकerface क्रम AMCC add-on रेजिस्टरs */

	outw(reg, devpriv->adकरोn + APCI3120_ADDON_ADDR_REG);
	outw(val & 0xffff, devpriv->adकरोn + APCI3120_ADDON_DATA_REG);

	outw(reg + 2, devpriv->adकरोn + APCI3120_ADDON_ADDR_REG);
	outw((val >> 16) & 0xffff, devpriv->adकरोn + APCI3120_ADDON_DATA_REG);
पूर्ण

अटल व्योम apci3120_init_dma(काष्ठा comedi_device *dev,
			      काष्ठा apci3120_dmabuf *dmabuf)
अणु
	काष्ठा apci3120_निजी *devpriv = dev->निजी;

	/* AMCC - enable transfer count and reset A2P FIFO */
	outl(AGCSTS_TC_ENABLE | AGCSTS_RESET_A2P_FIFO,
	     devpriv->amcc + AMCC_OP_REG_AGCSTS);

	/* Add-On - enable transfer count and reset A2P FIFO */
	apci3120_adकरोn_ग_लिखो(dev, AGCSTS_TC_ENABLE | AGCSTS_RESET_A2P_FIFO,
			     AMCC_OP_REG_AGCSTS);

	/* AMCC - enable transfers and reset A2P flags */
	outl(RESET_A2P_FLAGS | EN_A2P_TRANSFERS,
	     devpriv->amcc + AMCC_OP_REG_MCSR);

	/* Add-On - DMA start address */
	apci3120_adकरोn_ग_लिखो(dev, dmabuf->hw, AMCC_OP_REG_AMWAR);

	/* Add-On - Number of acquisitions */
	apci3120_adकरोn_ग_लिखो(dev, dmabuf->use_size, AMCC_OP_REG_AMWTC);

	/* AMCC - enable ग_लिखो complete (DMA) and set FIFO advance */
	outl(APCI3120_FIFO_ADVANCE_ON_BYTE_2 | AINT_WRITE_COMPL,
	     devpriv->amcc + AMCC_OP_REG_INTCSR);

	/* Add-On - enable DMA */
	outw(APCI3120_ADDON_CTRL_AMWEN_ENA | APCI3120_ADDON_CTRL_A2P_FIFO_ENA,
	     devpriv->adकरोn + APCI3120_ADDON_CTRL_REG);
पूर्ण

अटल व्योम apci3120_setup_dma(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s)
अणु
	काष्ठा apci3120_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	काष्ठा apci3120_dmabuf *dmabuf0 = &devpriv->dmabuf[0];
	काष्ठा apci3120_dmabuf *dmabuf1 = &devpriv->dmabuf[1];
	अचिन्हित पूर्णांक dmalen0 = dmabuf0->size;
	अचिन्हित पूर्णांक dmalen1 = dmabuf1->size;
	अचिन्हित पूर्णांक scan_bytes;

	scan_bytes = comedi_samples_to_bytes(s, cmd->scan_end_arg);

	अगर (cmd->stop_src == TRIG_COUNT) अणु
		/*
		 * Must we fill full first buffer? And must we fill
		 * full second buffer when first is once filled?
		 */
		अगर (dmalen0 > (cmd->stop_arg * scan_bytes))
			dmalen0 = cmd->stop_arg * scan_bytes;
		अन्यथा अगर (dmalen1 > (cmd->stop_arg * scan_bytes - dmalen0))
			dmalen1 = cmd->stop_arg * scan_bytes - dmalen0;
	पूर्ण

	अगर (cmd->flags & CMDF_WAKE_EOS) अणु
		/* करोn't we want wake up every scan? */
		अगर (dmalen0 > scan_bytes) अणु
			dmalen0 = scan_bytes;
			अगर (cmd->scan_end_arg & 1)
				dmalen0 += 2;
		पूर्ण
		अगर (dmalen1 > scan_bytes) अणु
			dmalen1 = scan_bytes;
			अगर (cmd->scan_end_arg & 1)
				dmalen1 -= 2;
			अगर (dmalen1 < 4)
				dmalen1 = 4;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* isn't output buff smaller that our DMA buff? */
		अगर (dmalen0 > s->async->pपुनः_स्मृति_bufsz)
			dmalen0 = s->async->pपुनः_स्मृति_bufsz;
		अगर (dmalen1 > s->async->pपुनः_स्मृति_bufsz)
			dmalen1 = s->async->pपुनः_स्मृति_bufsz;
	पूर्ण
	dmabuf0->use_size = dmalen0;
	dmabuf1->use_size = dmalen1;

	apci3120_init_dma(dev, dmabuf0);
पूर्ण

/*
 * There are three समयrs on the board. They all use the same base
 * घड़ी with a fixed prescaler क्रम each समयr. The base घड़ी used
 * depends on the board version and type.
 *
 * APCI-3120 Rev A boards OSC = 14.29MHz base घड़ी (~70ns)
 * APCI-3120 Rev B boards OSC = 20MHz base घड़ी (50ns)
 * APCI-3001 boards OSC = 20MHz base घड़ी (50ns)
 *
 * The prescalers क्रम each समयr are:
 * Timer 0 CLK = OSC/10
 * Timer 1 CLK = OSC/1000
 * Timer 2 CLK = OSC/1000
 */
अटल अचिन्हित पूर्णांक apci3120_ns_to_समयr(काष्ठा comedi_device *dev,
					 अचिन्हित पूर्णांक समयr,
					 अचिन्हित पूर्णांक ns,
					 अचिन्हित पूर्णांक flags)
अणु
	काष्ठा apci3120_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक prescale = (समयr == 0) ? 10 : 1000;
	अचिन्हित पूर्णांक समयr_base = devpriv->osc_base * prescale;
	अचिन्हित पूर्णांक भागisor;

	चयन (flags & CMDF_ROUND_MASK) अणु
	हाल CMDF_ROUND_UP:
		भागisor = DIV_ROUND_UP(ns, समयr_base);
		अवरोध;
	हाल CMDF_ROUND_DOWN:
		भागisor = ns / समयr_base;
		अवरोध;
	हाल CMDF_ROUND_NEAREST:
	शेष:
		भागisor = DIV_ROUND_CLOSEST(ns, समयr_base);
		अवरोध;
	पूर्ण

	अगर (समयr == 2) अणु
		/* समयr 2 is 24-bits */
		अगर (भागisor > 0x00ffffff)
			भागisor = 0x00ffffff;
	पूर्ण अन्यथा अणु
		/* समयrs 0 and 1 are 16-bits */
		अगर (भागisor > 0xffff)
			भागisor = 0xffff;
	पूर्ण
	/* the समयrs require a minimum भागisor of 2 */
	अगर (भागisor < 2)
		भागisor = 2;

	वापस भागisor;
पूर्ण

अटल व्योम apci3120_clr_समयr2_पूर्णांकerrupt(काष्ठा comedi_device *dev)
अणु
	/* a dummy पढ़ो of APCI3120_CTR0_REG clears the समयr 2 पूर्णांकerrupt */
	inb(dev->iobase + APCI3120_CTR0_REG);
पूर्ण

अटल व्योम apci3120_समयr_ग_लिखो(काष्ठा comedi_device *dev,
				 अचिन्हित पूर्णांक समयr, अचिन्हित पूर्णांक val)
अणु
	काष्ठा apci3120_निजी *devpriv = dev->निजी;

	/* ग_लिखो 16-bit value to समयr (lower 16-bits of समयr 2) */
	outb(APCI3120_CTR0_DO_BITS(devpriv->करो_bits) |
	     APCI3120_CTR0_TIMER_SEL(समयr),
	     dev->iobase + APCI3120_CTR0_REG);
	outw(val & 0xffff, dev->iobase + APCI3120_TIMER_REG);

	अगर (समयr == 2) अणु
		/* ग_लिखो upper 16-bits to समयr 2 */
		outb(APCI3120_CTR0_DO_BITS(devpriv->करो_bits) |
		     APCI3120_CTR0_TIMER_SEL(समयr + 1),
		     dev->iobase + APCI3120_CTR0_REG);
		outw((val >> 16) & 0xffff, dev->iobase + APCI3120_TIMER_REG);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक apci3120_समयr_पढ़ो(काष्ठा comedi_device *dev,
					अचिन्हित पूर्णांक समयr)
अणु
	काष्ठा apci3120_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक val;

	/* पढ़ो 16-bit value from समयr (lower 16-bits of समयr 2) */
	outb(APCI3120_CTR0_DO_BITS(devpriv->करो_bits) |
	     APCI3120_CTR0_TIMER_SEL(समयr),
	     dev->iobase + APCI3120_CTR0_REG);
	val = inw(dev->iobase + APCI3120_TIMER_REG);

	अगर (समयr == 2) अणु
		/* पढ़ो upper 16-bits from समयr 2 */
		outb(APCI3120_CTR0_DO_BITS(devpriv->करो_bits) |
		     APCI3120_CTR0_TIMER_SEL(समयr + 1),
		     dev->iobase + APCI3120_CTR0_REG);
		val |= (inw(dev->iobase + APCI3120_TIMER_REG) << 16);
	पूर्ण

	वापस val;
पूर्ण

अटल व्योम apci3120_समयr_set_mode(काष्ठा comedi_device *dev,
				    अचिन्हित पूर्णांक समयr, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा apci3120_निजी *devpriv = dev->निजी;

	devpriv->समयr_mode &= ~APCI3120_TIMER_MODE_MASK(समयr);
	devpriv->समयr_mode |= APCI3120_TIMER_MODE(समयr, mode);
	outb(devpriv->समयr_mode, dev->iobase + APCI3120_TIMER_MODE_REG);
पूर्ण

अटल व्योम apci3120_समयr_enable(काष्ठा comedi_device *dev,
				  अचिन्हित पूर्णांक समयr, bool enable)
अणु
	काष्ठा apci3120_निजी *devpriv = dev->निजी;

	अगर (enable)
		devpriv->ctrl |= APCI3120_CTRL_GATE(समयr);
	अन्यथा
		devpriv->ctrl &= ~APCI3120_CTRL_GATE(समयr);
	outw(devpriv->ctrl, dev->iobase + APCI3120_CTRL_REG);
पूर्ण

अटल व्योम apci3120_exttrig_enable(काष्ठा comedi_device *dev, bool enable)
अणु
	काष्ठा apci3120_निजी *devpriv = dev->निजी;

	अगर (enable)
		devpriv->ctrl |= APCI3120_CTRL_EXT_TRIG;
	अन्यथा
		devpriv->ctrl &= ~APCI3120_CTRL_EXT_TRIG;
	outw(devpriv->ctrl, dev->iobase + APCI3120_CTRL_REG);
पूर्ण

अटल व्योम apci3120_set_chanlist(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  पूर्णांक n_chan, अचिन्हित पूर्णांक *chanlist)
अणु
	काष्ठा apci3120_निजी *devpriv = dev->निजी;
	पूर्णांक i;

	/* set chanlist क्रम scan */
	क्रम (i = 0; i < n_chan; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(chanlist[i]);
		अचिन्हित पूर्णांक range = CR_RANGE(chanlist[i]);
		अचिन्हित पूर्णांक val;

		val = APCI3120_CHANLIST_MUX(chan) |
		      APCI3120_CHANLIST_GAIN(range) |
		      APCI3120_CHANLIST_INDEX(i);

		अगर (comedi_range_is_unipolar(s, range))
			val |= APCI3120_CHANLIST_UNIPOLAR;

		outw(val, dev->iobase + APCI3120_CHANLIST_REG);
	पूर्ण

	/* a dummy पढ़ो of APCI3120_TIMER_MODE_REG resets the ai FIFO */
	inw(dev->iobase + APCI3120_TIMER_MODE_REG);

	/* set scan length (PR) and scan start (PA) */
	devpriv->ctrl = APCI3120_CTRL_PR(n_chan - 1) | APCI3120_CTRL_PA(0);
	outw(devpriv->ctrl, dev->iobase + APCI3120_CTRL_REG);

	/* enable chanlist scanning अगर necessary */
	अगर (n_chan > 1)
		devpriv->mode |= APCI3120_MODE_SCAN_ENA;
पूर्ण

अटल व्योम apci3120_पूर्णांकerrupt_dma(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s)
अणु
	काष्ठा apci3120_निजी *devpriv = dev->निजी;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	काष्ठा apci3120_dmabuf *dmabuf;
	अचिन्हित पूर्णांक nbytes;
	अचिन्हित पूर्णांक nsamples;

	dmabuf = &devpriv->dmabuf[devpriv->cur_dmabuf];

	nbytes = dmabuf->use_size - inl(devpriv->amcc + AMCC_OP_REG_MWTC);

	अगर (nbytes < dmabuf->use_size)
		dev_err(dev->class_dev, "Interrupted DMA transfer!\n");
	अगर (nbytes & 1) अणु
		dev_err(dev->class_dev, "Odd count of bytes in DMA ring!\n");
		async->events |= COMEDI_CB_ERROR;
		वापस;
	पूर्ण

	nsamples = comedi_bytes_to_samples(s, nbytes);
	अगर (nsamples) अणु
		comedi_buf_ग_लिखो_samples(s, dmabuf->virt, nsamples);

		अगर (!(cmd->flags & CMDF_WAKE_EOS))
			async->events |= COMEDI_CB_EOS;
	पूर्ण

	अगर ((async->events & COMEDI_CB_CANCEL_MASK) ||
	    (cmd->stop_src == TRIG_COUNT && async->scans_करोne >= cmd->stop_arg))
		वापस;

	अगर (devpriv->use_द्विगुन_buffer) अणु
		/* चयन DMA buffers क्रम next पूर्णांकerrupt */
		devpriv->cur_dmabuf = !devpriv->cur_dmabuf;
		dmabuf = &devpriv->dmabuf[devpriv->cur_dmabuf];
		apci3120_init_dma(dev, dmabuf);
	पूर्ण अन्यथा अणु
		/* restart DMA अगर not using द्विगुन buffering */
		apci3120_init_dma(dev, dmabuf);
	पूर्ण
पूर्ण

अटल irqवापस_t apci3120_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा apci3120_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक पूर्णांक_amcc;

	status = inw(dev->iobase + APCI3120_STATUS_REG);
	पूर्णांक_amcc = inl(devpriv->amcc + AMCC_OP_REG_INTCSR);

	अगर (!(status & APCI3120_STATUS_INT_MASK) &&
	    !(पूर्णांक_amcc & ANY_S593X_INT)) अणु
		dev_err(dev->class_dev, "IRQ from unknown source\n");
		वापस IRQ_NONE;
	पूर्ण

	outl(पूर्णांक_amcc | AINT_INT_MASK, devpriv->amcc + AMCC_OP_REG_INTCSR);

	अगर (devpriv->ctrl & APCI3120_CTRL_EXT_TRIG)
		apci3120_exttrig_enable(dev, false);

	अगर (पूर्णांक_amcc & MASTER_ABORT_INT)
		dev_err(dev->class_dev, "AMCC IRQ - MASTER DMA ABORT!\n");
	अगर (पूर्णांक_amcc & TARGET_ABORT_INT)
		dev_err(dev->class_dev, "AMCC IRQ - TARGET DMA ABORT!\n");

	अगर ((status & APCI3120_STATUS_EOS_INT) &&
	    (devpriv->mode & APCI3120_MODE_EOS_IRQ_ENA)) अणु
		अचिन्हित लघु val;
		पूर्णांक i;

		क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
			val = inw(dev->iobase + APCI3120_AI_FIFO_REG);
			comedi_buf_ग_लिखो_samples(s, &val, 1);
		पूर्ण

		devpriv->mode |= APCI3120_MODE_EOS_IRQ_ENA;
		outb(devpriv->mode, dev->iobase + APCI3120_MODE_REG);
	पूर्ण

	अगर (status & APCI3120_STATUS_TIMER2_INT) अणु
		/*
		 * क्रम safety...
		 * समयr2 पूर्णांकerrupts are not enabled in the driver
		 */
		apci3120_clr_समयr2_पूर्णांकerrupt(dev);
	पूर्ण

	अगर (status & APCI3120_STATUS_AMCC_INT) अणु
		/* AMCC- Clear ग_लिखो complete पूर्णांकerrupt (DMA) */
		outl(AINT_WT_COMPLETE, devpriv->amcc + AMCC_OP_REG_INTCSR);

		/* करो some data transfer */
		apci3120_पूर्णांकerrupt_dma(dev, s);
	पूर्ण

	अगर (cmd->stop_src == TRIG_COUNT && async->scans_करोne >= cmd->stop_arg)
		async->events |= COMEDI_CB_EOA;

	comedi_handle_events(dev, s);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक apci3120_ai_cmd(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s)
अणु
	काष्ठा apci3120_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक भागisor;

	/* set शेष mode bits */
	devpriv->mode = APCI3120_MODE_TIMER2_CLK_OSC |
			APCI3120_MODE_TIMER2_AS_TIMER;

	/* AMCC- Clear ग_लिखो complete पूर्णांकerrupt (DMA) */
	outl(AINT_WT_COMPLETE, devpriv->amcc + AMCC_OP_REG_INTCSR);

	devpriv->cur_dmabuf = 0;

	/* load chanlist क्रम command scan */
	apci3120_set_chanlist(dev, s, cmd->chanlist_len, cmd->chanlist);

	अगर (cmd->start_src == TRIG_EXT)
		apci3120_exttrig_enable(dev, true);

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		/*
		 * Timer 1 is used in MODE2 (rate generator) to set the
		 * start समय क्रम each scan.
		 */
		भागisor = apci3120_ns_to_समयr(dev, 1, cmd->scan_begin_arg,
					       cmd->flags);
		apci3120_समयr_set_mode(dev, 1, APCI3120_TIMER_MODE2);
		apci3120_समयr_ग_लिखो(dev, 1, भागisor);
	पूर्ण

	/*
	 * Timer 0 is used in MODE2 (rate generator) to set the conversion
	 * समय क्रम each acquisition.
	 */
	भागisor = apci3120_ns_to_समयr(dev, 0, cmd->convert_arg, cmd->flags);
	apci3120_समयr_set_mode(dev, 0, APCI3120_TIMER_MODE2);
	apci3120_समयr_ग_लिखो(dev, 0, भागisor);

	अगर (devpriv->use_dma)
		apci3120_setup_dma(dev, s);
	अन्यथा
		devpriv->mode |= APCI3120_MODE_EOS_IRQ_ENA;

	/* set mode to enable acquisition */
	outb(devpriv->mode, dev->iobase + APCI3120_MODE_REG);

	अगर (cmd->scan_begin_src == TRIG_TIMER)
		apci3120_समयr_enable(dev, 1, true);
	apci3120_समयr_enable(dev, 0, true);

	वापस 0;
पूर्ण

अटल पूर्णांक apci3120_ai_cmdtest(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_cmd *cmd)
अणु
	अचिन्हित पूर्णांक arg;
	पूर्णांक err = 0;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_TIMER | TRIG_FOLLOW);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_TIMER);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु	/* Test Delay timing */
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
						    100000);
	पूर्ण

	/* minimum conversion समय per sample is 10us */
	err |= comedi_check_trigger_arg_min(&cmd->convert_arg, 10000);

	err |= comedi_check_trigger_arg_min(&cmd->chanlist_len, 1);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/*  TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* Step 4: fix up any arguments */

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		/* scan begin must be larger than the scan समय */
		arg = cmd->convert_arg * cmd->scan_end_arg;
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg, arg);
	पूर्ण

	अगर (err)
		वापस 4;

	/* Step 5: check channel list अगर it exists */

	वापस 0;
पूर्ण

अटल पूर्णांक apci3120_cancel(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s)
अणु
	काष्ठा apci3120_निजी *devpriv = dev->निजी;

	/* Add-On - disable DMA */
	outw(0, devpriv->adकरोn + 4);

	/* Add-On - disable bus master */
	apci3120_adकरोn_ग_लिखो(dev, 0, AMCC_OP_REG_AGCSTS);

	/* AMCC - disable bus master */
	outl(0, devpriv->amcc + AMCC_OP_REG_MCSR);

	/* disable all counters, ext trigger, and reset scan */
	devpriv->ctrl = 0;
	outw(devpriv->ctrl, dev->iobase + APCI3120_CTRL_REG);

	/* DISABLE_ALL_INTERRUPT */
	devpriv->mode = 0;
	outb(devpriv->mode, dev->iobase + APCI3120_MODE_REG);

	inw(dev->iobase + APCI3120_STATUS_REG);
	devpriv->cur_dmabuf = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक apci3120_ai_eoc(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s,
			   काष्ठा comedi_insn *insn,
			   अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inw(dev->iobase + APCI3120_STATUS_REG);
	अगर ((status & APCI3120_STATUS_EOC_INT) == 0)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक apci3120_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	काष्ठा apci3120_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक भागisor;
	पूर्णांक ret;
	पूर्णांक i;

	/* set mode क्रम A/D conversions by software trigger with समयr 0 */
	devpriv->mode = APCI3120_MODE_TIMER2_CLK_OSC |
			APCI3120_MODE_TIMER2_AS_TIMER;
	outb(devpriv->mode, dev->iobase + APCI3120_MODE_REG);

	/* load chanlist क्रम single channel scan */
	apci3120_set_chanlist(dev, s, 1, &insn->chanspec);

	/*
	 * Timer 0 is used in MODE4 (software triggered strobe) to set the
	 * conversion समय क्रम each acquisition. Each conversion is triggered
	 * when the भागisor is written to the समयr, The conversion is करोne
	 * when the EOC bit in the status रेजिस्टर is '0'.
	 */
	apci3120_समयr_set_mode(dev, 0, APCI3120_TIMER_MODE4);
	apci3120_समयr_enable(dev, 0, true);

	/* fixed conversion समय of 10 us */
	भागisor = apci3120_ns_to_समयr(dev, 0, 10000, CMDF_ROUND_NEAREST);

	क्रम (i = 0; i < insn->n; i++) अणु
		/* trigger conversion */
		apci3120_समयr_ग_लिखो(dev, 0, भागisor);

		ret = comedi_समयout(dev, s, insn, apci3120_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		data[i] = inw(dev->iobase + APCI3120_AI_FIFO_REG);
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci3120_ao_पढ़ोy(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_insn *insn,
			     अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inw(dev->iobase + APCI3120_STATUS_REG);
	अगर (status & APCI3120_STATUS_DA_READY)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक apci3120_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val = data[i];
		पूर्णांक ret;

		ret = comedi_समयout(dev, s, insn, apci3120_ao_पढ़ोy, 0);
		अगर (ret)
			वापस ret;

		outw(APCI3120_AO_MUX(chan) | APCI3120_AO_DATA(val),
		     dev->iobase + APCI3120_AO_REG(chan));

		s->पढ़ोback[chan] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci3120_di_insn_bits(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक status;

	status = inw(dev->iobase + APCI3120_STATUS_REG);
	data[1] = APCI3120_STATUS_TO_DI_BITS(status);

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci3120_करो_insn_bits(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	काष्ठा apci3120_निजी *devpriv = dev->निजी;

	अगर (comedi_dio_update_state(s, data)) अणु
		devpriv->करो_bits = s->state;
		outb(APCI3120_CTR0_DO_BITS(devpriv->करो_bits),
		     dev->iobase + APCI3120_CTR0_REG);
	पूर्ण

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci3120_समयr_insn_config(काष्ठा comedi_device *dev,
				      काष्ठा comedi_subdevice *s,
				      काष्ठा comedi_insn *insn,
				      अचिन्हित पूर्णांक *data)
अणु
	काष्ठा apci3120_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक भागisor;
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक समयr_mode;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_ARM:
		apci3120_clr_समयr2_पूर्णांकerrupt(dev);
		भागisor = apci3120_ns_to_समयr(dev, 2, data[1],
					       CMDF_ROUND_DOWN);
		apci3120_समयr_ग_लिखो(dev, 2, भागisor);
		apci3120_समयr_enable(dev, 2, true);
		अवरोध;

	हाल INSN_CONFIG_DISARM:
		apci3120_समयr_enable(dev, 2, false);
		apci3120_clr_समयr2_पूर्णांकerrupt(dev);
		अवरोध;

	हाल INSN_CONFIG_GET_COUNTER_STATUS:
		data[1] = 0;
		data[2] = COMEDI_COUNTER_ARMED | COMEDI_COUNTER_COUNTING |
			  COMEDI_COUNTER_TERMINAL_COUNT;

		अगर (devpriv->ctrl & APCI3120_CTRL_GATE(2)) अणु
			data[1] |= COMEDI_COUNTER_ARMED;
			data[1] |= COMEDI_COUNTER_COUNTING;
		पूर्ण
		status = inw(dev->iobase + APCI3120_STATUS_REG);
		अगर (status & APCI3120_STATUS_TIMER2_INT) अणु
			data[1] &= ~COMEDI_COUNTER_COUNTING;
			data[1] |= COMEDI_COUNTER_TERMINAL_COUNT;
		पूर्ण
		अवरोध;

	हाल INSN_CONFIG_SET_COUNTER_MODE:
		चयन (data[1]) अणु
		हाल I8254_MODE0:
			mode = APCI3120_MODE_TIMER2_AS_COUNTER;
			समयr_mode = APCI3120_TIMER_MODE0;
			अवरोध;
		हाल I8254_MODE2:
			mode = APCI3120_MODE_TIMER2_AS_TIMER;
			समयr_mode = APCI3120_TIMER_MODE2;
			अवरोध;
		हाल I8254_MODE4:
			mode = APCI3120_MODE_TIMER2_AS_TIMER;
			समयr_mode = APCI3120_TIMER_MODE4;
			अवरोध;
		हाल I8254_MODE5:
			mode = APCI3120_MODE_TIMER2_AS_WDOG;
			समयr_mode = APCI3120_TIMER_MODE5;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		apci3120_समयr_enable(dev, 2, false);
		apci3120_clr_समयr2_पूर्णांकerrupt(dev);
		apci3120_समयr_set_mode(dev, 2, समयr_mode);
		devpriv->mode &= ~APCI3120_MODE_TIMER2_AS_MASK;
		devpriv->mode |= mode;
		outb(devpriv->mode, dev->iobase + APCI3120_MODE_REG);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci3120_समयr_insn_पढ़ो(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_insn *insn,
				    अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++)
		data[i] = apci3120_समयr_पढ़ो(dev, 2);

	वापस insn->n;
पूर्ण

अटल व्योम apci3120_dma_alloc(काष्ठा comedi_device *dev)
अणु
	काष्ठा apci3120_निजी *devpriv = dev->निजी;
	काष्ठा apci3120_dmabuf *dmabuf;
	पूर्णांक order;
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		dmabuf = &devpriv->dmabuf[i];
		क्रम (order = 2; order >= 0; order--) अणु
			dmabuf->virt = dma_alloc_coherent(dev->hw_dev,
							  PAGE_SIZE << order,
							  &dmabuf->hw,
							  GFP_KERNEL);
			अगर (dmabuf->virt)
				अवरोध;
		पूर्ण
		अगर (!dmabuf->virt)
			अवरोध;
		dmabuf->size = PAGE_SIZE << order;

		अगर (i == 0)
			devpriv->use_dma = 1;
		अगर (i == 1)
			devpriv->use_द्विगुन_buffer = 1;
	पूर्ण
पूर्ण

अटल व्योम apci3120_dma_मुक्त(काष्ठा comedi_device *dev)
अणु
	काष्ठा apci3120_निजी *devpriv = dev->निजी;
	काष्ठा apci3120_dmabuf *dmabuf;
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

अटल व्योम apci3120_reset(काष्ठा comedi_device *dev)
अणु
	/* disable all पूर्णांकerrupt sources */
	outb(0, dev->iobase + APCI3120_MODE_REG);

	/* disable all counters, ext trigger, and reset scan */
	outw(0, dev->iobase + APCI3120_CTRL_REG);

	/* clear पूर्णांकerrupt status */
	inw(dev->iobase + APCI3120_STATUS_REG);
पूर्ण

अटल पूर्णांक apci3120_स्वतः_attach(काष्ठा comedi_device *dev,
				अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा apci3120_board *board = शून्य;
	काष्ठा apci3120_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक status;
	पूर्णांक ret;

	अगर (context < ARRAY_SIZE(apci3120_boardtypes))
		board = &apci3120_boardtypes[context];
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
	pci_set_master(pcidev);

	dev->iobase = pci_resource_start(pcidev, 1);
	devpriv->amcc = pci_resource_start(pcidev, 0);
	devpriv->adकरोn = pci_resource_start(pcidev, 2);

	apci3120_reset(dev);

	अगर (pcidev->irq > 0) अणु
		ret = request_irq(pcidev->irq, apci3120_पूर्णांकerrupt, IRQF_SHARED,
				  dev->board_name, dev);
		अगर (ret == 0) अणु
			dev->irq = pcidev->irq;

			apci3120_dma_alloc(dev);
		पूर्ण
	पूर्ण

	status = inw(dev->iobase + APCI3120_STATUS_REG);
	अगर (APCI3120_STATUS_TO_VERSION(status) == APCI3120_REVB ||
	    context == BOARD_APCI3001)
		devpriv->osc_base = APCI3120_REVB_OSC_BASE;
	अन्यथा
		devpriv->osc_base = APCI3120_REVA_OSC_BASE;

	ret = comedi_alloc_subdevices(dev, 5);
	अगर (ret)
		वापस ret;

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_COMMON | SDF_GROUND | SDF_DIFF;
	s->n_chan	= 16;
	s->maxdata	= board->ai_is_16bit ? 0xffff : 0x0fff;
	s->range_table	= &apci3120_ai_range;
	s->insn_पढ़ो	= apci3120_ai_insn_पढ़ो;
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->len_chanlist	= s->n_chan;
		s->करो_cmdtest	= apci3120_ai_cmdtest;
		s->करो_cmd	= apci3120_ai_cmd;
		s->cancel	= apci3120_cancel;
	पूर्ण

	/* Analog Output subdevice */
	s = &dev->subdevices[1];
	अगर (board->has_ao) अणु
		s->type		= COMEDI_SUBD_AO;
		s->subdev_flags	= SDF_WRITABLE | SDF_GROUND | SDF_COMMON;
		s->n_chan	= 8;
		s->maxdata	= 0x3fff;
		s->range_table	= &range_bipolar10;
		s->insn_ग_लिखो	= apci3120_ao_insn_ग_लिखो;

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
	s->insn_bits	= apci3120_di_insn_bits;

	/* Digital Output subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= apci3120_करो_insn_bits;

	/* Timer subdevice */
	s = &dev->subdevices[4];
	s->type		= COMEDI_SUBD_TIMER;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 1;
	s->maxdata	= 0x00ffffff;
	s->insn_config	= apci3120_समयr_insn_config;
	s->insn_पढ़ो	= apci3120_समयr_insn_पढ़ो;

	वापस 0;
पूर्ण

अटल व्योम apci3120_detach(काष्ठा comedi_device *dev)
अणु
	comedi_pci_detach(dev);
	apci3120_dma_मुक्त(dev);
पूर्ण

अटल काष्ठा comedi_driver apci3120_driver = अणु
	.driver_name	= "addi_apci_3120",
	.module		= THIS_MODULE,
	.स्वतः_attach	= apci3120_स्वतः_attach,
	.detach		= apci3120_detach,
पूर्ण;

अटल पूर्णांक apci3120_pci_probe(काष्ठा pci_dev *dev,
			      स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &apci3120_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id apci3120_pci_table[] = अणु
	अणु PCI_VDEVICE(AMCC, 0x818d), BOARD_APCI3120 पूर्ण,
	अणु PCI_VDEVICE(AMCC, 0x828d), BOARD_APCI3001 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, apci3120_pci_table);

अटल काष्ठा pci_driver apci3120_pci_driver = अणु
	.name		= "addi_apci_3120",
	.id_table	= apci3120_pci_table,
	.probe		= apci3120_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(apci3120_driver, apci3120_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("ADDI-DATA APCI-3120, Analog input board");
MODULE_LICENSE("GPL");
