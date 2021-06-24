<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * comedi/drivers/adv_pci_dio.c
 *
 * Author: Michal Dobes <करोbes@tesnet.cz>
 *
 *  Hardware driver क्रम Advantech PCI DIO cards.
 */

/*
 * Driver: adv_pci_dio
 * Description: Advantech Digital I/O Cards
 * Devices: [Advantech] PCI-1730 (adv_pci_dio), PCI-1733,
 *   PCI-1734, PCI-1735U, PCI-1736UP, PCI-1739U, PCI-1750,
 *   PCI-1751, PCI-1752, PCI-1753, PCI-1753+PCI-1753E,
 *   PCI-1754, PCI-1756, PCI-1761, PCI-1762
 * Author: Michal Dobes <करोbes@tesnet.cz>
 * Updated: Fri, 25 Aug 2017 07:23:06 +0300
 * Status: untested
 *
 * Configuration Options: not applicable, uses PCI स्वतः config
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>

#समावेश "../comedi_pci.h"

#समावेश "8255.h"
#समावेश "comedi_8254.h"

/*
 * Register offset definitions
 */

/* PCI-1730, PCI-1733, PCI-1736 पूर्णांकerrupt control रेजिस्टरs */
#घोषणा PCI173X_INT_EN_REG	0x0008	/* R/W: enable/disable */
#घोषणा PCI173X_INT_RF_REG	0x000c	/* R/W: falling/rising edge */
#घोषणा PCI173X_INT_FLAG_REG	0x0010	/* R: status */
#घोषणा PCI173X_INT_CLR_REG	0x0010	/* W: clear */

#घोषणा PCI173X_INT_IDI0 0x01  /* IDI0 edge occurred */
#घोषणा PCI173X_INT_IDI1 0x02  /* IDI1 edge occurred */
#घोषणा PCI173X_INT_DI0  0x04  /* DI0 edge occurred */
#घोषणा PCI173X_INT_DI1  0x08  /* DI1 edge occurred */

/* PCI-1739U, PCI-1750, PCI1751 पूर्णांकerrupt control रेजिस्टरs */
#घोषणा PCI1750_INT_REG		0x20	/* R/W: status/control */

/* PCI-1753, PCI-1753E पूर्णांकerrupt control रेजिस्टरs */
#घोषणा PCI1753_INT_REG(x)	(0x10 + (x)) /* R/W: control group 0 to 3 */
#घोषणा PCI1753E_INT_REG(x)	(0x30 + (x)) /* R/W: control group 0 to 3 */

/* PCI-1754, PCI-1756 पूर्णांकerrupt control रेजिस्टरs */
#घोषणा PCI1754_INT_REG(x)	(0x08 + (x) * 2) /* R/W: control group 0 to 3 */

/* PCI-1752, PCI-1756 special रेजिस्टरs */
#घोषणा PCI1752_CFC_REG		0x12	/* R/W: channel मुक्तze function */

/* PCI-1761 पूर्णांकerrupt control रेजिस्टरs */
#घोषणा PCI1761_INT_EN_REG	0x03	/* R/W: enable/disable पूर्णांकerrupts */
#घोषणा PCI1761_INT_RF_REG	0x04	/* R/W: falling/rising edge */
#घोषणा PCI1761_INT_CLR_REG	0x05	/* R/W: clear पूर्णांकerrupts */

/* PCI-1762 पूर्णांकerrupt control रेजिस्टरs */
#घोषणा PCI1762_INT_REG		0x06	/* R/W: status/control */

/* maximum number of subdevice descriptions in the boardinfo */
#घोषणा PCI_DIO_MAX_DI_SUBDEVS	2	/* 2 x 8/16/32 input channels max */
#घोषणा PCI_DIO_MAX_DO_SUBDEVS	2	/* 2 x 8/16/32 output channels max */
#घोषणा PCI_DIO_MAX_DIO_SUBDEVG	2	/* 2 x any number of 8255 devices max */
#घोषणा PCI_DIO_MAX_IRQ_SUBDEVS	4	/* 4 x 1 input IRQ channels max */

क्रमागत pci_dio_boardid अणु
	TYPE_PCI1730,
	TYPE_PCI1733,
	TYPE_PCI1734,
	TYPE_PCI1735,
	TYPE_PCI1736,
	TYPE_PCI1739,
	TYPE_PCI1750,
	TYPE_PCI1751,
	TYPE_PCI1752,
	TYPE_PCI1753,
	TYPE_PCI1753E,
	TYPE_PCI1754,
	TYPE_PCI1756,
	TYPE_PCI1761,
	TYPE_PCI1762
पूर्ण;

काष्ठा diosubd_data अणु
	पूर्णांक chans;		/*  num of chans or 8255 devices */
	अचिन्हित दीर्घ addr;	/*  PCI address offset */
पूर्ण;

काष्ठा dio_irq_subd_data अणु
	अचिन्हित लघु पूर्णांक_en;		/* पूर्णांकerrupt enable/status bit */
	अचिन्हित दीर्घ addr;		/* PCI address offset */
पूर्ण;

काष्ठा dio_boardtype अणु
	स्थिर अक्षर *name;	/*  board name */
	पूर्णांक nsubdevs;
	काष्ठा diosubd_data sdi[PCI_DIO_MAX_DI_SUBDEVS];
	काष्ठा diosubd_data sकरो[PCI_DIO_MAX_DO_SUBDEVS];
	काष्ठा diosubd_data sdio[PCI_DIO_MAX_DIO_SUBDEVG];
	काष्ठा dio_irq_subd_data sdirq[PCI_DIO_MAX_IRQ_SUBDEVS];
	अचिन्हित दीर्घ id_reg;
	अचिन्हित दीर्घ समयr_regbase;
	अचिन्हित पूर्णांक is_16bit:1;
पूर्ण;

अटल स्थिर काष्ठा dio_boardtype boardtypes[] = अणु
	[TYPE_PCI1730] = अणु
		.name		= "pci1730",
		/* DI, IDI, DO, IDO, ID, IRQ_DI0, IRQ_DI1, IRQ_IDI0, IRQ_IDI1 */
		.nsubdevs	= 9,
		.sdi[0]		= अणु 16, 0x02, पूर्ण,	/* DI 0-15 */
		.sdi[1]		= अणु 16, 0x00, पूर्ण,	/* ISO DI 0-15 */
		.sकरो[0]		= अणु 16, 0x02, पूर्ण,	/* DO 0-15 */
		.sकरो[1]		= अणु 16, 0x00, पूर्ण,	/* ISO DO 0-15 */
		.id_reg		= 0x04,
		.sdirq[0]	= अणु PCI173X_INT_DI0,  0x02, पूर्ण,	/* DI 0 */
		.sdirq[1]	= अणु PCI173X_INT_DI1,  0x02, पूर्ण,	/* DI 1 */
		.sdirq[2]	= अणु PCI173X_INT_IDI0, 0x00, पूर्ण,	/* ISO DI 0 */
		.sdirq[3]	= अणु PCI173X_INT_IDI1, 0x00, पूर्ण,	/* ISO DI 1 */
	पूर्ण,
	[TYPE_PCI1733] = अणु
		.name		= "pci1733",
		.nsubdevs	= 2,
		.sdi[1]		= अणु 32, 0x00, पूर्ण,	/* ISO DI 0-31 */
		.id_reg		= 0x04,
	पूर्ण,
	[TYPE_PCI1734] = अणु
		.name		= "pci1734",
		.nsubdevs	= 2,
		.sकरो[1]		= अणु 32, 0x00, पूर्ण,	/* ISO DO 0-31 */
		.id_reg		= 0x04,
	पूर्ण,
	[TYPE_PCI1735] = अणु
		.name		= "pci1735",
		.nsubdevs	= 4,
		.sdi[0]		= अणु 32, 0x00, पूर्ण,	/* DI 0-31 */
		.sकरो[0]		= अणु 32, 0x00, पूर्ण,	/* DO 0-31 */
		.id_reg		= 0x08,
		.समयr_regbase	= 0x04,
	पूर्ण,
	[TYPE_PCI1736] = अणु
		.name		= "pci1736",
		.nsubdevs	= 3,
		.sdi[1]		= अणु 16, 0x00, पूर्ण,	/* ISO DI 0-15 */
		.sकरो[1]		= अणु 16, 0x00, पूर्ण,	/* ISO DO 0-15 */
		.id_reg		= 0x04,
	पूर्ण,
	[TYPE_PCI1739] = अणु
		.name		= "pci1739",
		.nsubdevs	= 3,
		.sdio[0]	= अणु 2, 0x00, पूर्ण,		/* 8255 DIO */
		.id_reg		= 0x08,
	पूर्ण,
	[TYPE_PCI1750] = अणु
		.name		= "pci1750",
		.nsubdevs	= 2,
		.sdi[1]		= अणु 16, 0x00, पूर्ण,	/* ISO DI 0-15 */
		.sकरो[1]		= अणु 16, 0x00, पूर्ण,	/* ISO DO 0-15 */
	पूर्ण,
	[TYPE_PCI1751] = अणु
		.name		= "pci1751",
		.nsubdevs	= 3,
		.sdio[0]	= अणु 2, 0x00, पूर्ण,		/* 8255 DIO */
		.समयr_regbase	= 0x18,
	पूर्ण,
	[TYPE_PCI1752] = अणु
		.name		= "pci1752",
		.nsubdevs	= 3,
		.sकरो[0]		= अणु 32, 0x00, पूर्ण,	/* DO 0-31 */
		.sकरो[1]		= अणु 32, 0x04, पूर्ण,	/* DO 32-63 */
		.id_reg		= 0x10,
		.is_16bit	= 1,
	पूर्ण,
	[TYPE_PCI1753] = अणु
		.name		= "pci1753",
		.nsubdevs	= 4,
		.sdio[0]	= अणु 4, 0x00, पूर्ण,		/* 8255 DIO */
	पूर्ण,
	[TYPE_PCI1753E] = अणु
		.name		= "pci1753e",
		.nsubdevs	= 8,
		.sdio[0]	= अणु 4, 0x00, पूर्ण,		/* 8255 DIO */
		.sdio[1]	= अणु 4, 0x20, पूर्ण,		/* 8255 DIO */
	पूर्ण,
	[TYPE_PCI1754] = अणु
		.name		= "pci1754",
		.nsubdevs	= 3,
		.sdi[0]		= अणु 32, 0x00, पूर्ण,	/* DI 0-31 */
		.sdi[1]		= अणु 32, 0x04, पूर्ण,	/* DI 32-63 */
		.id_reg		= 0x10,
		.is_16bit	= 1,
	पूर्ण,
	[TYPE_PCI1756] = अणु
		.name		= "pci1756",
		.nsubdevs	= 3,
		.sdi[1]		= अणु 32, 0x00, पूर्ण,	/* DI 0-31 */
		.sकरो[1]		= अणु 32, 0x04, पूर्ण,	/* DO 0-31 */
		.id_reg		= 0x10,
		.is_16bit	= 1,
	पूर्ण,
	[TYPE_PCI1761] = अणु
		.name		= "pci1761",
		.nsubdevs	= 3,
		.sdi[1]		= अणु 8, 0x01 पूर्ण,		/* ISO DI 0-7 */
		.sकरो[1]		= अणु 8, 0x00 पूर्ण,		/* RELAY DO 0-7 */
		.id_reg		= 0x02,
	पूर्ण,
	[TYPE_PCI1762] = अणु
		.name		= "pci1762",
		.nsubdevs	= 3,
		.sdi[1]		= अणु 16, 0x02, पूर्ण,	/* ISO DI 0-15 */
		.sकरो[1]		= अणु 16, 0x00, पूर्ण,	/* ISO DO 0-15 */
		.id_reg		= 0x04,
		.is_16bit	= 1,
	पूर्ण,
पूर्ण;

काष्ठा pci_dio_dev_निजी_data अणु
	पूर्णांक boardtype;
	पूर्णांक irq_subd;
	अचिन्हित लघु पूर्णांक_ctrl;
	अचिन्हित लघु पूर्णांक_rf;
पूर्ण;

काष्ठा pci_dio_sd_निजी_data अणु
	spinlock_t subd_slock;		/* spin-lock क्रम cmd_running */
	अचिन्हित दीर्घ port_offset;
	लघु पूर्णांक cmd_running;
पूर्ण;

अटल व्योम process_irq(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक subdev,
			अचिन्हित अक्षर irqflags)
अणु
	काष्ठा comedi_subdevice *s = &dev->subdevices[subdev];
	काष्ठा pci_dio_sd_निजी_data *sd_priv = s->निजी;
	अचिन्हित दीर्घ reg = sd_priv->port_offset;
	काष्ठा comedi_async *async_p = s->async;

	अगर (async_p) अणु
		अचिन्हित लघु val = inw(dev->iobase + reg);

		spin_lock(&sd_priv->subd_slock);
		अगर (sd_priv->cmd_running)
			comedi_buf_ग_लिखो_samples(s, &val, 1);
		spin_unlock(&sd_priv->subd_slock);
		comedi_handle_events(dev, s);
	पूर्ण
पूर्ण

अटल irqवापस_t pci_dio_पूर्णांकerrupt(पूर्णांक irq, व्योम *p_device)
अणु
	काष्ठा comedi_device *dev = p_device;
	काष्ठा pci_dio_dev_निजी_data *dev_निजी = dev->निजी;
	स्थिर काष्ठा dio_boardtype *board = dev->board_ptr;
	अचिन्हित दीर्घ cpu_flags;
	अचिन्हित अक्षर irqflags;
	पूर्णांक i;

	अगर (!dev->attached) अणु
		/* Ignore पूर्णांकerrupt beक्रमe device fully attached. */
		/* Might not even have allocated subdevices yet! */
		वापस IRQ_NONE;
	पूर्ण

	/* Check अगर we are source of पूर्णांकerrupt */
	spin_lock_irqsave(&dev->spinlock, cpu_flags);
	irqflags = inb(dev->iobase + PCI173X_INT_FLAG_REG);
	अगर (!(irqflags & 0x0F)) अणु
		spin_unlock_irqrestore(&dev->spinlock, cpu_flags);
		वापस IRQ_NONE;
	पूर्ण

	/* clear all current पूर्णांकerrupt flags */
	outb(irqflags, dev->iobase + PCI173X_INT_CLR_REG);
	spin_unlock_irqrestore(&dev->spinlock, cpu_flags);

	/* check irq subdevice triggers */
	क्रम (i = 0; i < PCI_DIO_MAX_IRQ_SUBDEVS; i++) अणु
		अगर (irqflags & board->sdirq[i].पूर्णांक_en)
			process_irq(dev, dev_निजी->irq_subd + i, irqflags);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pci_dio_asy_cmdtest(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_FOLLOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */
	/* Step 2b : and mutually compatible */

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
	/*
	 * For scan_begin_arg, the trigger number must be 0 and the only
	 * allowed flags are CR_EDGE and CR_INVERT.  CR_EDGE is ignored,
	 * CR_INVERT sets the trigger to falling edge.
	 */
	अगर (cmd->scan_begin_arg & ~(CR_EDGE | CR_INVERT)) अणु
		cmd->scan_begin_arg &= (CR_EDGE | CR_INVERT);
		err |= -EINVAL;
	पूर्ण
	err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);
	err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* Step 4: fix up any arguments */

	/* Step 5: check channel list अगर it exists */

	वापस 0;
पूर्ण

अटल पूर्णांक pci_dio_asy_cmd(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci_dio_dev_निजी_data *dev_निजी = dev->निजी;
	काष्ठा pci_dio_sd_निजी_data *sd_priv = s->निजी;
	स्थिर काष्ठा dio_boardtype *board = dev->board_ptr;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित दीर्घ cpu_flags;
	अचिन्हित लघु पूर्णांक_en;

	पूर्णांक_en = board->sdirq[s->index - dev_निजी->irq_subd].पूर्णांक_en;

	spin_lock_irqsave(&dev->spinlock, cpu_flags);
	अगर (cmd->scan_begin_arg & CR_INVERT)
		dev_निजी->पूर्णांक_rf |= पूर्णांक_en;	/* falling edge */
	अन्यथा
		dev_निजी->पूर्णांक_rf &= ~पूर्णांक_en;	/* rising edge */
	outb(dev_निजी->पूर्णांक_rf, dev->iobase + PCI173X_INT_RF_REG);
	dev_निजी->पूर्णांक_ctrl |= पूर्णांक_en;	/* enable पूर्णांकerrupt source */
	outb(dev_निजी->पूर्णांक_ctrl, dev->iobase + PCI173X_INT_EN_REG);
	spin_unlock_irqrestore(&dev->spinlock, cpu_flags);

	spin_lock_irqsave(&sd_priv->subd_slock, cpu_flags);
	sd_priv->cmd_running = 1;
	spin_unlock_irqrestore(&sd_priv->subd_slock, cpu_flags);

	वापस 0;
पूर्ण

अटल पूर्णांक pci_dio_asy_cancel(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci_dio_dev_निजी_data *dev_निजी = dev->निजी;
	काष्ठा pci_dio_sd_निजी_data *sd_priv = s->निजी;
	स्थिर काष्ठा dio_boardtype *board = dev->board_ptr;
	अचिन्हित दीर्घ cpu_flags;
	अचिन्हित लघु पूर्णांक_en;

	spin_lock_irqsave(&sd_priv->subd_slock, cpu_flags);
	sd_priv->cmd_running = 0;
	spin_unlock_irqrestore(&sd_priv->subd_slock, cpu_flags);

	पूर्णांक_en = board->sdirq[s->index - dev_निजी->irq_subd].पूर्णांक_en;

	spin_lock_irqsave(&dev->spinlock, cpu_flags);
	dev_निजी->पूर्णांक_ctrl &= ~पूर्णांक_en;
	outb(dev_निजी->पूर्णांक_ctrl, dev->iobase + PCI173X_INT_EN_REG);
	spin_unlock_irqrestore(&dev->spinlock, cpu_flags);

	वापस 0;
पूर्ण

/* same as _insn_bits_di_ because the IRQ-pins are the DI-ports  */
अटल पूर्णांक pci_dio_insn_bits_dirq_b(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_insn *insn,
				    अचिन्हित पूर्णांक *data)
अणु
	काष्ठा pci_dio_sd_निजी_data *sd_priv = s->निजी;
	अचिन्हित दीर्घ reg = (अचिन्हित दीर्घ)sd_priv->port_offset;
	अचिन्हित दीर्घ iobase = dev->iobase + reg;

	data[1] = inb(iobase);

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci_dio_insn_bits_di_b(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित दीर्घ reg = (अचिन्हित दीर्घ)s->निजी;
	अचिन्हित दीर्घ iobase = dev->iobase + reg;

	data[1] = inb(iobase);
	अगर (s->n_chan > 8)
		data[1] |= (inb(iobase + 1) << 8);
	अगर (s->n_chan > 16)
		data[1] |= (inb(iobase + 2) << 16);
	अगर (s->n_chan > 24)
		data[1] |= (inb(iobase + 3) << 24);

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci_dio_insn_bits_di_w(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित दीर्घ reg = (अचिन्हित दीर्घ)s->निजी;
	अचिन्हित दीर्घ iobase = dev->iobase + reg;

	data[1] = inw(iobase);
	अगर (s->n_chan > 16)
		data[1] |= (inw(iobase + 2) << 16);

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci_dio_insn_bits_करो_b(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित दीर्घ reg = (अचिन्हित दीर्घ)s->निजी;
	अचिन्हित दीर्घ iobase = dev->iobase + reg;

	अगर (comedi_dio_update_state(s, data)) अणु
		outb(s->state & 0xff, iobase);
		अगर (s->n_chan > 8)
			outb((s->state >> 8) & 0xff, iobase + 1);
		अगर (s->n_chan > 16)
			outb((s->state >> 16) & 0xff, iobase + 2);
		अगर (s->n_chan > 24)
			outb((s->state >> 24) & 0xff, iobase + 3);
	पूर्ण

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci_dio_insn_bits_करो_w(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित दीर्घ reg = (अचिन्हित दीर्घ)s->निजी;
	अचिन्हित दीर्घ iobase = dev->iobase + reg;

	अगर (comedi_dio_update_state(s, data)) अणु
		outw(s->state & 0xffff, iobase);
		अगर (s->n_chan > 16)
			outw((s->state >> 16) & 0xffff, iobase + 2);
	पूर्ण

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci_dio_reset(काष्ठा comedi_device *dev, अचिन्हित दीर्घ cardtype)
अणु
	काष्ठा pci_dio_dev_निजी_data *dev_निजी = dev->निजी;
	/* disable channel मुक्तze function on the PCI-1752/1756 boards */
	अगर (cardtype == TYPE_PCI1752 || cardtype == TYPE_PCI1756)
		outw(0, dev->iobase + PCI1752_CFC_REG);

	/* disable and clear पूर्णांकerrupts */
	चयन (cardtype) अणु
	हाल TYPE_PCI1730:
	हाल TYPE_PCI1733:
	हाल TYPE_PCI1736:
		dev_निजी->पूर्णांक_ctrl = 0x00;
		outb(dev_निजी->पूर्णांक_ctrl, dev->iobase + PCI173X_INT_EN_REG);
		/* Reset all 4 Int Flags */
		outb(0x0f, dev->iobase + PCI173X_INT_CLR_REG);
		/* Rising Edge => IRQ . On all 4 Pins */
		dev_निजी->पूर्णांक_rf = 0x00;
		outb(dev_निजी->पूर्णांक_rf, dev->iobase + PCI173X_INT_RF_REG);
		अवरोध;
	हाल TYPE_PCI1739:
	हाल TYPE_PCI1750:
	हाल TYPE_PCI1751:
		outb(0x88, dev->iobase + PCI1750_INT_REG);
		अवरोध;
	हाल TYPE_PCI1753:
	हाल TYPE_PCI1753E:
		outb(0x88, dev->iobase + PCI1753_INT_REG(0));
		outb(0x80, dev->iobase + PCI1753_INT_REG(1));
		outb(0x80, dev->iobase + PCI1753_INT_REG(2));
		outb(0x80, dev->iobase + PCI1753_INT_REG(3));
		अगर (cardtype == TYPE_PCI1753E) अणु
			outb(0x88, dev->iobase + PCI1753E_INT_REG(0));
			outb(0x80, dev->iobase + PCI1753E_INT_REG(1));
			outb(0x80, dev->iobase + PCI1753E_INT_REG(2));
			outb(0x80, dev->iobase + PCI1753E_INT_REG(3));
		पूर्ण
		अवरोध;
	हाल TYPE_PCI1754:
	हाल TYPE_PCI1756:
		outw(0x08, dev->iobase + PCI1754_INT_REG(0));
		outw(0x08, dev->iobase + PCI1754_INT_REG(1));
		अगर (cardtype == TYPE_PCI1754) अणु
			outw(0x08, dev->iobase + PCI1754_INT_REG(2));
			outw(0x08, dev->iobase + PCI1754_INT_REG(3));
		पूर्ण
		अवरोध;
	हाल TYPE_PCI1761:
		/* disable पूर्णांकerrupts */
		outb(0, dev->iobase + PCI1761_INT_EN_REG);
		/* clear पूर्णांकerrupts */
		outb(0xff, dev->iobase + PCI1761_INT_CLR_REG);
		/* set rising edge trigger */
		outb(0, dev->iobase + PCI1761_INT_RF_REG);
		अवरोध;
	हाल TYPE_PCI1762:
		outw(0x0101, dev->iobase + PCI1762_INT_REG);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pci_dio_स्वतः_attach(काष्ठा comedi_device *dev,
			       अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा dio_boardtype *board = शून्य;
	काष्ठा comedi_subdevice *s;
	काष्ठा pci_dio_dev_निजी_data *dev_निजी;
	पूर्णांक ret, subdev, i, j;

	अगर (context < ARRAY_SIZE(boardtypes))
		board = &boardtypes[context];
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	dev_निजी = comedi_alloc_devpriv(dev, माप(*dev_निजी));
	अगर (!dev_निजी)
		वापस -ENOMEM;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;
	अगर (context == TYPE_PCI1736)
		dev->iobase = pci_resource_start(pcidev, 0);
	अन्यथा
		dev->iobase = pci_resource_start(pcidev, 2);

	dev_निजी->boardtype = context;
	pci_dio_reset(dev, context);

	/* request IRQ अगर device has irq subdevices */
	अगर (board->sdirq[0].पूर्णांक_en && pcidev->irq) अणु
		ret = request_irq(pcidev->irq, pci_dio_पूर्णांकerrupt, IRQF_SHARED,
				  dev->board_name, dev);
		अगर (ret == 0)
			dev->irq = pcidev->irq;
	पूर्ण

	ret = comedi_alloc_subdevices(dev, board->nsubdevs);
	अगर (ret)
		वापस ret;

	subdev = 0;
	क्रम (i = 0; i < PCI_DIO_MAX_DI_SUBDEVS; i++) अणु
		स्थिर काष्ठा diosubd_data *d = &board->sdi[i];

		अगर (d->chans) अणु
			s = &dev->subdevices[subdev++];
			s->type		= COMEDI_SUBD_DI;
			s->subdev_flags	= SDF_READABLE;
			s->n_chan	= d->chans;
			s->maxdata	= 1;
			s->range_table	= &range_digital;
			s->insn_bits	= board->is_16bit
						? pci_dio_insn_bits_di_w
						: pci_dio_insn_bits_di_b;
			s->निजी	= (व्योम *)d->addr;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < PCI_DIO_MAX_DO_SUBDEVS; i++) अणु
		स्थिर काष्ठा diosubd_data *d = &board->sकरो[i];

		अगर (d->chans) अणु
			s = &dev->subdevices[subdev++];
			s->type		= COMEDI_SUBD_DO;
			s->subdev_flags	= SDF_WRITABLE;
			s->n_chan	= d->chans;
			s->maxdata	= 1;
			s->range_table	= &range_digital;
			s->insn_bits	= board->is_16bit
						? pci_dio_insn_bits_करो_w
						: pci_dio_insn_bits_करो_b;
			s->निजी	= (व्योम *)d->addr;

			/* reset all outमाला_दो to 0 */
			अगर (board->is_16bit) अणु
				outw(0, dev->iobase + d->addr);
				अगर (s->n_chan > 16)
					outw(0, dev->iobase + d->addr + 2);
			पूर्ण अन्यथा अणु
				outb(0, dev->iobase + d->addr);
				अगर (s->n_chan > 8)
					outb(0, dev->iobase + d->addr + 1);
				अगर (s->n_chan > 16)
					outb(0, dev->iobase + d->addr + 2);
				अगर (s->n_chan > 24)
					outb(0, dev->iobase + d->addr + 3);
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < PCI_DIO_MAX_DIO_SUBDEVG; i++) अणु
		स्थिर काष्ठा diosubd_data *d = &board->sdio[i];

		क्रम (j = 0; j < d->chans; j++) अणु
			s = &dev->subdevices[subdev++];
			ret = subdev_8255_init(dev, s, शून्य,
					       d->addr + j * I8255_SIZE);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	अगर (board->id_reg) अणु
		s = &dev->subdevices[subdev++];
		s->type		= COMEDI_SUBD_DI;
		s->subdev_flags	= SDF_READABLE | SDF_INTERNAL;
		s->n_chan	= 4;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_bits	= board->is_16bit ? pci_dio_insn_bits_di_w
						  : pci_dio_insn_bits_di_b;
		s->निजी	= (व्योम *)board->id_reg;
	पूर्ण

	अगर (board->समयr_regbase) अणु
		s = &dev->subdevices[subdev++];

		dev->pacer = comedi_8254_init(dev->iobase +
					      board->समयr_regbase,
					      0, I8254_IO8, 0);
		अगर (!dev->pacer)
			वापस -ENOMEM;

		comedi_8254_subdevice_init(s, dev->pacer);
	पूर्ण

	dev_निजी->irq_subd = subdev; /* first पूर्णांकerrupt subdevice index */
	क्रम (i = 0; i < PCI_DIO_MAX_IRQ_SUBDEVS; ++i) अणु
		काष्ठा pci_dio_sd_निजी_data *sd_priv = शून्य;
		स्थिर काष्ठा dio_irq_subd_data *d = &board->sdirq[i];

		अगर (d->पूर्णांक_en) अणु
			s = &dev->subdevices[subdev++];
			s->type		= COMEDI_SUBD_DI;
			s->subdev_flags	= SDF_READABLE;
			s->n_chan	= 1;
			s->maxdata	= 1;
			s->range_table	= &range_digital;
			s->insn_bits	= pci_dio_insn_bits_dirq_b;
			sd_priv = comedi_alloc_spriv(s, माप(*sd_priv));
			अगर (!sd_priv)
				वापस -ENOMEM;

			spin_lock_init(&sd_priv->subd_slock);
			sd_priv->port_offset = d->addr;
			sd_priv->cmd_running = 0;

			अगर (dev->irq) अणु
				dev->पढ़ो_subdev = s;
				s->type		= COMEDI_SUBD_DI;
				s->subdev_flags	= SDF_READABLE | SDF_CMD_READ;
				s->len_chanlist	= 1;
				s->करो_cmdtest	= pci_dio_asy_cmdtest;
				s->करो_cmd	= pci_dio_asy_cmd;
				s->cancel	= pci_dio_asy_cancel;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pci_dio_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा pci_dio_dev_निजी_data *dev_निजी = dev->निजी;
	पूर्णांक boardtype = dev_निजी->boardtype;

	अगर (dev->iobase)
		pci_dio_reset(dev, boardtype);
	comedi_pci_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver adv_pci_dio_driver = अणु
	.driver_name	= "adv_pci_dio",
	.module		= THIS_MODULE,
	.स्वतः_attach	= pci_dio_स्वतः_attach,
	.detach		= pci_dio_detach,
पूर्ण;

अटल अचिन्हित दीर्घ pci_dio_override_cardtype(काष्ठा pci_dev *pcidev,
					       अचिन्हित दीर्घ cardtype)
अणु
	/*
	 * Change cardtype from TYPE_PCI1753 to TYPE_PCI1753E अगर expansion
	 * board available.  Need to enable PCI device and request the मुख्य
	 * रेजिस्टरs PCI BAR temporarily to perक्रमm the test.
	 */
	अगर (cardtype != TYPE_PCI1753)
		वापस cardtype;
	अगर (pci_enable_device(pcidev) < 0)
		वापस cardtype;
	अगर (pci_request_region(pcidev, 2, "adv_pci_dio") == 0) अणु
		/*
		 * This test is based on Advantech's "advdaq" driver source
		 * (which declares its module licence as "GPL" although the
		 * driver source करोes not include a "COPYING" file).
		 */
		अचिन्हित दीर्घ reg = pci_resource_start(pcidev, 2) + 53;

		outb(0x05, reg);
		अगर ((inb(reg) & 0x07) == 0x02) अणु
			outb(0x02, reg);
			अगर ((inb(reg) & 0x07) == 0x05)
				cardtype = TYPE_PCI1753E;
		पूर्ण
		pci_release_region(pcidev, 2);
	पूर्ण
	pci_disable_device(pcidev);
	वापस cardtype;
पूर्ण

अटल पूर्णांक adv_pci_dio_pci_probe(काष्ठा pci_dev *dev,
				 स्थिर काष्ठा pci_device_id *id)
अणु
	अचिन्हित दीर्घ cardtype;

	cardtype = pci_dio_override_cardtype(dev, id->driver_data);
	वापस comedi_pci_स्वतः_config(dev, &adv_pci_dio_driver, cardtype);
पूर्ण

अटल स्थिर काष्ठा pci_device_id adv_pci_dio_pci_table[] = अणु
	अणु PCI_VDEVICE(ADVANTECH, 0x1730), TYPE_PCI1730 पूर्ण,
	अणु PCI_VDEVICE(ADVANTECH, 0x1733), TYPE_PCI1733 पूर्ण,
	अणु PCI_VDEVICE(ADVANTECH, 0x1734), TYPE_PCI1734 पूर्ण,
	अणु PCI_VDEVICE(ADVANTECH, 0x1735), TYPE_PCI1735 पूर्ण,
	अणु PCI_VDEVICE(ADVANTECH, 0x1736), TYPE_PCI1736 पूर्ण,
	अणु PCI_VDEVICE(ADVANTECH, 0x1739), TYPE_PCI1739 पूर्ण,
	अणु PCI_VDEVICE(ADVANTECH, 0x1750), TYPE_PCI1750 पूर्ण,
	अणु PCI_VDEVICE(ADVANTECH, 0x1751), TYPE_PCI1751 पूर्ण,
	अणु PCI_VDEVICE(ADVANTECH, 0x1752), TYPE_PCI1752 पूर्ण,
	अणु PCI_VDEVICE(ADVANTECH, 0x1753), TYPE_PCI1753 पूर्ण,
	अणु PCI_VDEVICE(ADVANTECH, 0x1754), TYPE_PCI1754 पूर्ण,
	अणु PCI_VDEVICE(ADVANTECH, 0x1756), TYPE_PCI1756 पूर्ण,
	अणु PCI_VDEVICE(ADVANTECH, 0x1761), TYPE_PCI1761 पूर्ण,
	अणु PCI_VDEVICE(ADVANTECH, 0x1762), TYPE_PCI1762 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, adv_pci_dio_pci_table);

अटल काष्ठा pci_driver adv_pci_dio_pci_driver = अणु
	.name		= "adv_pci_dio",
	.id_table	= adv_pci_dio_pci_table,
	.probe		= adv_pci_dio_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(adv_pci_dio_driver, adv_pci_dio_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for Advantech Digital I/O Cards");
MODULE_LICENSE("GPL");
