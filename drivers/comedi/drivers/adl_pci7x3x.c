<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * COMEDI driver क्रम the ADLINK PCI-723x/743x series boards.
 * Copyright (C) 2012 H Hartley Sweeten <hsweeten@visionengravers.com>
 *
 * Based on the adl_pci7230 driver written by:
 *	David Fernandez <dfcastelao@gmail.com>
 * and the adl_pci7432 driver written by:
 *	Michel Lachaine <mike@mikelachaine.ca>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: adl_pci7x3x
 * Description: 32/64-Channel Isolated Digital I/O Boards
 * Devices: [ADLink] PCI-7230 (adl_pci7230), PCI-7233 (adl_pci7233),
 *   PCI-7234 (adl_pci7234), PCI-7432 (adl_pci7432), PCI-7433 (adl_pci7433),
 *   PCI-7434 (adl_pci7434)
 * Author: H Hartley Sweeten <hsweeten@visionengravers.com>
 * Updated: Fri, 20 Nov 2020 14:49:36 +0000
 * Status: works (tested on PCI-7230)
 *
 * One or two subdevices are setup by this driver depending on
 * the number of digital inमाला_दो and/or outमाला_दो provided by the
 * board. Each subdevice has a maximum of 32 channels.
 *
 *	PCI-7230 - 4 subdevices: 0 - 16 input, 1 - 16 output,
 *	                         2 - IRQ_IDI0, 3 - IRQ_IDI1
 *	PCI-7233 - 1 subdevice: 0 - 32 input
 *	PCI-7234 - 1 subdevice: 0 - 32 output
 *	PCI-7432 - 2 subdevices: 0 - 32 input, 1 - 32 output
 *	PCI-7433 - 2 subdevices: 0 - 32 input, 1 - 32 input
 *	PCI-7434 - 2 subdevices: 0 - 32 output, 1 - 32 output
 *
 * The PCI-7230, PCI-7432 and PCI-7433 boards also support बाह्यal
 * पूर्णांकerrupt संकेतs on digital input channels 0 and 1. The PCI-7233
 * has dual-पूर्णांकerrupt sources क्रम change-of-state (COS) on any 16
 * digital input channels of LSB and क्रम COS on any 16 digital input
 * lines of MSB.
 *
 * Currently, this driver only supports पूर्णांकerrupts क्रम PCI-7230.
 *
 * Configuration Options: not applicable, uses comedi PCI स्वतः config
 */

#समावेश <linux/module.h>

#समावेश "../comedi_pci.h"

#समावेश "plx9052.h"

/*
 * Register I/O map (32-bit access only)
 */
#घोषणा PCI7X3X_DIO_REG		0x0000	/* in the DigIO Port area */
#घोषणा PCI743X_DIO_REG		0x0004

#घोषणा ADL_PT_CLRIRQ		0x0040	/* in the DigIO Port area */

#घोषणा LINTI1_EN_ACT_IDI0 (PLX9052_INTCSR_LI1ENAB | PLX9052_INTCSR_LI1STAT)
#घोषणा LINTI2_EN_ACT_IDI1 (PLX9052_INTCSR_LI2ENAB | PLX9052_INTCSR_LI2STAT)
#घोषणा EN_PCI_LINT2H_LINT1H	\
	(PLX9052_INTCSR_PCIENAB | PLX9052_INTCSR_LI2POL | PLX9052_INTCSR_LI1POL)

क्रमागत adl_pci7x3x_boardid अणु
	BOARD_PCI7230,
	BOARD_PCI7233,
	BOARD_PCI7234,
	BOARD_PCI7432,
	BOARD_PCI7433,
	BOARD_PCI7434,
पूर्ण;

काष्ठा adl_pci7x3x_boardinfo अणु
	स्थिर अक्षर *name;
	पूर्णांक nsubdevs;
	पूर्णांक di_nchan;
	पूर्णांक करो_nchan;
	पूर्णांक irq_nchan;
पूर्ण;

अटल स्थिर काष्ठा adl_pci7x3x_boardinfo adl_pci7x3x_boards[] = अणु
	[BOARD_PCI7230] = अणु
		.name		= "adl_pci7230",
		.nsubdevs	= 4,  /* IDI, IDO, IRQ_IDI0, IRQ_IDI1 */
		.di_nchan	= 16,
		.करो_nchan	= 16,
		.irq_nchan	= 2,
	पूर्ण,
	[BOARD_PCI7233] = अणु
		.name		= "adl_pci7233",
		.nsubdevs	= 1,
		.di_nchan	= 32,
	पूर्ण,
	[BOARD_PCI7234] = अणु
		.name		= "adl_pci7234",
		.nsubdevs	= 1,
		.करो_nchan	= 32,
	पूर्ण,
	[BOARD_PCI7432] = अणु
		.name		= "adl_pci7432",
		.nsubdevs	= 2,
		.di_nchan	= 32,
		.करो_nchan	= 32,
	पूर्ण,
	[BOARD_PCI7433] = अणु
		.name		= "adl_pci7433",
		.nsubdevs	= 2,
		.di_nchan	= 64,
	पूर्ण,
	[BOARD_PCI7434] = अणु
		.name		= "adl_pci7434",
		.nsubdevs	= 2,
		.करो_nchan	= 64,
	पूर्ण
पूर्ण;

काष्ठा adl_pci7x3x_dev_निजी_data अणु
	अचिन्हित दीर्घ lcr_io_base;
	अचिन्हित पूर्णांक पूर्णांक_ctrl;
पूर्ण;

काष्ठा adl_pci7x3x_sd_निजी_data अणु
	spinlock_t subd_slock;		/* spin-lock क्रम cmd_running */
	अचिन्हित दीर्घ port_offset;
	लघु पूर्णांक cmd_running;
पूर्ण;

अटल व्योम process_irq(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक subdev,
			अचिन्हित लघु पूर्णांकcsr)
अणु
	काष्ठा comedi_subdevice *s = &dev->subdevices[subdev];
	काष्ठा adl_pci7x3x_sd_निजी_data *sd_priv = s->निजी;
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

अटल irqवापस_t adl_pci7x3x_पूर्णांकerrupt(पूर्णांक irq, व्योम *p_device)
अणु
	काष्ठा comedi_device *dev = p_device;
	काष्ठा adl_pci7x3x_dev_निजी_data *dev_निजी = dev->निजी;
	अचिन्हित दीर्घ cpu_flags;
	अचिन्हित पूर्णांक पूर्णांकcsr;
	bool li1stat, li2stat;

	अगर (!dev->attached) अणु
		/* Ignore पूर्णांकerrupt beक्रमe device fully attached. */
		/* Might not even have allocated subdevices yet! */
		वापस IRQ_NONE;
	पूर्ण

	/* Check अगर we are source of पूर्णांकerrupt */
	spin_lock_irqsave(&dev->spinlock, cpu_flags);
	पूर्णांकcsr = inl(dev_निजी->lcr_io_base + PLX9052_INTCSR);
	li1stat = (पूर्णांकcsr & LINTI1_EN_ACT_IDI0) == LINTI1_EN_ACT_IDI0;
	li2stat = (पूर्णांकcsr & LINTI2_EN_ACT_IDI1) == LINTI2_EN_ACT_IDI1;
	अगर (li1stat || li2stat) अणु
		/* clear all current पूर्णांकerrupt flags */
		/* Fixme: Reset all 2 Int Flags */
		outb(0x00, dev->iobase + ADL_PT_CLRIRQ);
	पूर्ण
	spin_unlock_irqrestore(&dev->spinlock, cpu_flags);

	/* SubDev 2, 3 = Isolated DigIn , on "SCSI2" jack!*/

	अगर (li1stat)	/* 0x0005 LINTi1 is Enabled && IDI0 is 1 */
		process_irq(dev, 2, पूर्णांकcsr);

	अगर (li2stat)	/* 0x0028 LINTi2 is Enabled && IDI1 is 1 */
		process_irq(dev, 3, पूर्णांकcsr);

	वापस IRQ_RETVAL(li1stat || li2stat);
पूर्ण

अटल पूर्णांक adl_pci7x3x_asy_cmdtest(काष्ठा comedi_device *dev,
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
	err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);
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

अटल पूर्णांक adl_pci7x3x_asy_cmd(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s)
अणु
	काष्ठा adl_pci7x3x_dev_निजी_data *dev_निजी = dev->निजी;
	काष्ठा adl_pci7x3x_sd_निजी_data *sd_priv = s->निजी;
	अचिन्हित दीर्घ cpu_flags;
	अचिन्हित पूर्णांक पूर्णांक_enab;

	अगर (s->index == 2) अणु
		/* enable LINTi1 == IDI sdi[0] Ch 0 IRQ ActHigh */
		पूर्णांक_enab = PLX9052_INTCSR_LI1ENAB;
	पूर्ण अन्यथा अणु
		/* enable LINTi2 == IDI sdi[0] Ch 1 IRQ ActHigh */
		पूर्णांक_enab = PLX9052_INTCSR_LI2ENAB;
	पूर्ण

	spin_lock_irqsave(&dev->spinlock, cpu_flags);
	dev_निजी->पूर्णांक_ctrl |= पूर्णांक_enab;
	outl(dev_निजी->पूर्णांक_ctrl, dev_निजी->lcr_io_base + PLX9052_INTCSR);
	spin_unlock_irqrestore(&dev->spinlock, cpu_flags);

	spin_lock_irqsave(&sd_priv->subd_slock, cpu_flags);
	sd_priv->cmd_running = 1;
	spin_unlock_irqrestore(&sd_priv->subd_slock, cpu_flags);

	वापस 0;
पूर्ण

अटल पूर्णांक adl_pci7x3x_asy_cancel(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s)
अणु
	काष्ठा adl_pci7x3x_dev_निजी_data *dev_निजी = dev->निजी;
	काष्ठा adl_pci7x3x_sd_निजी_data *sd_priv = s->निजी;
	अचिन्हित दीर्घ cpu_flags;
	अचिन्हित पूर्णांक पूर्णांक_enab;

	spin_lock_irqsave(&sd_priv->subd_slock, cpu_flags);
	sd_priv->cmd_running = 0;
	spin_unlock_irqrestore(&sd_priv->subd_slock, cpu_flags);
	/* disable Interrupts */
	अगर (s->index == 2)
		पूर्णांक_enab = PLX9052_INTCSR_LI1ENAB;
	अन्यथा
		पूर्णांक_enab = PLX9052_INTCSR_LI2ENAB;
	spin_lock_irqsave(&dev->spinlock, cpu_flags);
	dev_निजी->पूर्णांक_ctrl &= ~पूर्णांक_enab;
	outl(dev_निजी->पूर्णांक_ctrl, dev_निजी->lcr_io_base + PLX9052_INTCSR);
	spin_unlock_irqrestore(&dev->spinlock, cpu_flags);

	वापस 0;
पूर्ण

/* same as _di_insn_bits because the IRQ-pins are the DI-ports  */
अटल पूर्णांक adl_pci7x3x_dirq_insn_bits(काष्ठा comedi_device *dev,
				      काष्ठा comedi_subdevice *s,
				      काष्ठा comedi_insn *insn,
				      अचिन्हित पूर्णांक *data)
अणु
	काष्ठा adl_pci7x3x_sd_निजी_data *sd_priv = s->निजी;
	अचिन्हित दीर्घ reg = (अचिन्हित दीर्घ)sd_priv->port_offset;

	data[1] = inl(dev->iobase + reg);

	वापस insn->n;
पूर्ण

अटल पूर्णांक adl_pci7x3x_करो_insn_bits(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_insn *insn,
				    अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित दीर्घ reg = (अचिन्हित दीर्घ)s->निजी;

	अगर (comedi_dio_update_state(s, data)) अणु
		अचिन्हित पूर्णांक val = s->state;

		अगर (s->n_chan == 16) अणु
			/*
			 * It seems the PCI-7230 needs the 16-bit DO state
			 * to be shअगरted left by 16 bits beक्रमe being written
			 * to the 32-bit रेजिस्टर.  Set the value in both
			 * halves of the रेजिस्टर to be sure.
			 */
			val |= val << 16;
		पूर्ण
		outl(val, dev->iobase + reg);
	पूर्ण

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक adl_pci7x3x_di_insn_bits(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_insn *insn,
				    अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित दीर्घ reg = (अचिन्हित दीर्घ)s->निजी;

	data[1] = inl(dev->iobase + reg);

	वापस insn->n;
पूर्ण

अटल पूर्णांक adl_pci7x3x_reset(काष्ठा comedi_device *dev)
अणु
	काष्ठा adl_pci7x3x_dev_निजी_data *dev_निजी = dev->निजी;

	/* disable Interrupts */
	dev_निजी->पूर्णांक_ctrl = 0x00;  /* Disable PCI + LINTi2 + LINTi1 */
	outl(dev_निजी->पूर्णांक_ctrl, dev_निजी->lcr_io_base + PLX9052_INTCSR);

	वापस 0;
पूर्ण

अटल पूर्णांक adl_pci7x3x_स्वतः_attach(काष्ठा comedi_device *dev,
				   अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा adl_pci7x3x_boardinfo *board = शून्य;
	काष्ठा comedi_subdevice *s;
	काष्ठा adl_pci7x3x_dev_निजी_data *dev_निजी;
	पूर्णांक subdev;
	पूर्णांक nchan;
	पूर्णांक ret;
	पूर्णांक ic;

	अगर (context < ARRAY_SIZE(adl_pci7x3x_boards))
		board = &adl_pci7x3x_boards[context];
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
	dev->iobase = pci_resource_start(pcidev, 2);
	dev_निजी->lcr_io_base = pci_resource_start(pcidev, 1);

	adl_pci7x3x_reset(dev);

	अगर (board->irq_nchan) अणु
		/* discard all evtl. old IRQs */
		outb(0x00, dev->iobase + ADL_PT_CLRIRQ);

		अगर (pcidev->irq) अणु
			ret = request_irq(pcidev->irq, adl_pci7x3x_पूर्णांकerrupt,
					  IRQF_SHARED, dev->board_name, dev);
			अगर (ret == 0) अणु
				dev->irq = pcidev->irq;
				/* 0x52 PCI + IDI Ch 1 Ch 0 IRQ Off ActHigh */
				dev_निजी->पूर्णांक_ctrl = EN_PCI_LINT2H_LINT1H;
				outl(dev_निजी->पूर्णांक_ctrl,
				     dev_निजी->lcr_io_base + PLX9052_INTCSR);
			पूर्ण
		पूर्ण
	पूर्ण

	ret = comedi_alloc_subdevices(dev, board->nsubdevs);
	अगर (ret)
		वापस ret;

	subdev = 0;

	अगर (board->di_nchan) अणु
		nchan = min(board->di_nchan, 32);

		s = &dev->subdevices[subdev];
		/* Isolated digital inमाला_दो 0 to 15/31 */
		s->type		= COMEDI_SUBD_DI;
		s->subdev_flags	= SDF_READABLE;
		s->n_chan	= nchan;
		s->maxdata	= 1;
		s->insn_bits	= adl_pci7x3x_di_insn_bits;
		s->range_table	= &range_digital;

		s->निजी	= (व्योम *)PCI7X3X_DIO_REG;

		subdev++;

		nchan = board->di_nchan - nchan;
		अगर (nchan) अणु
			s = &dev->subdevices[subdev];
			/* Isolated digital inमाला_दो 32 to 63 */
			s->type		= COMEDI_SUBD_DI;
			s->subdev_flags	= SDF_READABLE;
			s->n_chan	= nchan;
			s->maxdata	= 1;
			s->insn_bits	= adl_pci7x3x_di_insn_bits;
			s->range_table	= &range_digital;

			s->निजी	= (व्योम *)PCI743X_DIO_REG;

			subdev++;
		पूर्ण
	पूर्ण

	अगर (board->करो_nchan) अणु
		nchan = min(board->करो_nchan, 32);

		s = &dev->subdevices[subdev];
		/* Isolated digital outमाला_दो 0 to 15/31 */
		s->type		= COMEDI_SUBD_DO;
		s->subdev_flags	= SDF_WRITABLE;
		s->n_chan	= nchan;
		s->maxdata	= 1;
		s->insn_bits	= adl_pci7x3x_करो_insn_bits;
		s->range_table	= &range_digital;

		s->निजी	= (व्योम *)PCI7X3X_DIO_REG;

		subdev++;

		nchan = board->करो_nchan - nchan;
		अगर (nchan) अणु
			s = &dev->subdevices[subdev];
			/* Isolated digital outमाला_दो 32 to 63 */
			s->type		= COMEDI_SUBD_DO;
			s->subdev_flags	= SDF_WRITABLE;
			s->n_chan	= nchan;
			s->maxdata	= 1;
			s->insn_bits	= adl_pci7x3x_करो_insn_bits;
			s->range_table	= &range_digital;

			s->निजी	= (व्योम *)PCI743X_DIO_REG;

			subdev++;
		पूर्ण
	पूर्ण

	क्रम (ic = 0; ic < board->irq_nchan; ++ic) अणु
		काष्ठा adl_pci7x3x_sd_निजी_data *sd_priv;

		nchan = 1;

		s = &dev->subdevices[subdev];
		/* Isolated digital inमाला_दो 0 or 1 */
		s->type		= COMEDI_SUBD_DI;
		s->subdev_flags	= SDF_READABLE;
		s->n_chan	= nchan;
		s->maxdata	= 1;
		s->insn_bits	= adl_pci7x3x_dirq_insn_bits;
		s->range_table	= &range_digital;

		sd_priv = comedi_alloc_spriv(s, माप(*sd_priv));
		अगर (!sd_priv)
			वापस -ENOMEM;

		spin_lock_init(&sd_priv->subd_slock);
		sd_priv->port_offset = PCI7X3X_DIO_REG;
		sd_priv->cmd_running = 0;

		अगर (dev->irq) अणु
			dev->पढ़ो_subdev = s;
			s->type		= COMEDI_SUBD_DI;
			s->subdev_flags	= SDF_READABLE | SDF_CMD_READ;
			s->len_chanlist	= 1;
			s->करो_cmdtest	= adl_pci7x3x_asy_cmdtest;
			s->करो_cmd	= adl_pci7x3x_asy_cmd;
			s->cancel	= adl_pci7x3x_asy_cancel;
		पूर्ण

		subdev++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम adl_pci7x3x_detach(काष्ठा comedi_device *dev)
अणु
	अगर (dev->iobase)
		adl_pci7x3x_reset(dev);
	comedi_pci_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver adl_pci7x3x_driver = अणु
	.driver_name	= "adl_pci7x3x",
	.module		= THIS_MODULE,
	.स्वतः_attach	= adl_pci7x3x_स्वतः_attach,
	.detach		= adl_pci7x3x_detach,
पूर्ण;

अटल पूर्णांक adl_pci7x3x_pci_probe(काष्ठा pci_dev *dev,
				 स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &adl_pci7x3x_driver,
				      id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id adl_pci7x3x_pci_table[] = अणु
	अणु PCI_VDEVICE(ADLINK, 0x7230), BOARD_PCI7230 पूर्ण,
	अणु PCI_VDEVICE(ADLINK, 0x7233), BOARD_PCI7233 पूर्ण,
	अणु PCI_VDEVICE(ADLINK, 0x7234), BOARD_PCI7234 पूर्ण,
	अणु PCI_VDEVICE(ADLINK, 0x7432), BOARD_PCI7432 पूर्ण,
	अणु PCI_VDEVICE(ADLINK, 0x7433), BOARD_PCI7433 पूर्ण,
	अणु PCI_VDEVICE(ADLINK, 0x7434), BOARD_PCI7434 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, adl_pci7x3x_pci_table);

अटल काष्ठा pci_driver adl_pci7x3x_pci_driver = अणु
	.name		= "adl_pci7x3x",
	.id_table	= adl_pci7x3x_pci_table,
	.probe		= adl_pci7x3x_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(adl_pci7x3x_driver, adl_pci7x3x_pci_driver);

MODULE_DESCRIPTION("ADLINK PCI-723x/743x Isolated Digital I/O boards");
MODULE_AUTHOR("H Hartley Sweeten <hsweeten@visionengravers.com>");
MODULE_LICENSE("GPL");
