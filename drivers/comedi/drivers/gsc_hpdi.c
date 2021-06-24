<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * gsc_hpdi.c
 * Comedi driver the General Standards Corporation
 * High Speed Parallel Digital Interface rs485 boards.
 *
 * Author:  Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 * Copyright (C) 2003 Coherent Imaging Systems
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1997-8 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: gsc_hpdi
 * Description: General Standards Corporation High
 *    Speed Parallel Digital Interface rs485 boards
 * Author: Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 * Status: only receive mode works, transmit not supported
 * Updated: Thu, 01 Nov 2012 16:17:38 +0000
 * Devices: [General Standards Corporation] PCI-HPDI32 (gsc_hpdi),
 *   PMC-HPDI32
 *
 * Configuration options:
 *    None.
 *
 * Manual configuration of supported devices is not supported; they are
 * configured स्वतःmatically.
 *
 * There are some additional hpdi models available from GSC क्रम which
 * support could be added to this driver.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedi_pci.h"

#समावेश "plx9080.h"

/*
 * PCI BAR2 Register map (dev->mmio)
 */
#घोषणा FIRMWARE_REV_REG			0x00
#घोषणा FEATURES_REG_PRESENT_BIT		BIT(15)
#घोषणा BOARD_CONTROL_REG			0x04
#घोषणा BOARD_RESET_BIT				BIT(0)
#घोषणा TX_FIFO_RESET_BIT			BIT(1)
#घोषणा RX_FIFO_RESET_BIT			BIT(2)
#घोषणा TX_ENABLE_BIT				BIT(4)
#घोषणा RX_ENABLE_BIT				BIT(5)
#घोषणा DEMAND_DMA_सूचीECTION_TX_BIT		BIT(6)  /* ch 0 only */
#घोषणा LINE_VALID_ON_STATUS_VALID_BIT		BIT(7)
#घोषणा START_TX_BIT				BIT(8)
#घोषणा CABLE_THROTTLE_ENABLE_BIT		BIT(9)
#घोषणा TEST_MODE_ENABLE_BIT			BIT(31)
#घोषणा BOARD_STATUS_REG			0x08
#घोषणा COMMAND_LINE_STATUS_MASK		(0x7f << 0)
#घोषणा TX_IN_PROGRESS_BIT			BIT(7)
#घोषणा TX_NOT_EMPTY_BIT			BIT(8)
#घोषणा TX_NOT_ALMOST_EMPTY_BIT			BIT(9)
#घोषणा TX_NOT_ALMOST_FULL_BIT			BIT(10)
#घोषणा TX_NOT_FULL_BIT				BIT(11)
#घोषणा RX_NOT_EMPTY_BIT			BIT(12)
#घोषणा RX_NOT_ALMOST_EMPTY_BIT			BIT(13)
#घोषणा RX_NOT_ALMOST_FULL_BIT			BIT(14)
#घोषणा RX_NOT_FULL_BIT				BIT(15)
#घोषणा BOARD_JUMPER0_INSTALLED_BIT		BIT(16)
#घोषणा BOARD_JUMPER1_INSTALLED_BIT		BIT(17)
#घोषणा TX_OVERRUN_BIT				BIT(21)
#घोषणा RX_UNDERRUN_BIT				BIT(22)
#घोषणा RX_OVERRUN_BIT				BIT(23)
#घोषणा TX_PROG_ALMOST_REG			0x0c
#घोषणा RX_PROG_ALMOST_REG			0x10
#घोषणा ALMOST_EMPTY_BITS(x)			(((x) & 0xffff) << 0)
#घोषणा ALMOST_FULL_BITS(x)			(((x) & 0xff) << 16)
#घोषणा FEATURES_REG				0x14
#घोषणा FIFO_SIZE_PRESENT_BIT			BIT(0)
#घोषणा FIFO_WORDS_PRESENT_BIT			BIT(1)
#घोषणा LEVEL_EDGE_INTERRUPTS_PRESENT_BIT	BIT(2)
#घोषणा GPIO_SUPPORTED_BIT			BIT(3)
#घोषणा PLX_DMA_CH1_SUPPORTED_BIT		BIT(4)
#घोषणा OVERRUN_UNDERRUN_SUPPORTED_BIT		BIT(5)
#घोषणा FIFO_REG				0x18
#घोषणा TX_STATUS_COUNT_REG			0x1c
#घोषणा TX_LINE_VALID_COUNT_REG			0x20,
#घोषणा TX_LINE_INVALID_COUNT_REG		0x24
#घोषणा RX_STATUS_COUNT_REG			0x28
#घोषणा RX_LINE_COUNT_REG			0x2c
#घोषणा INTERRUPT_CONTROL_REG			0x30
#घोषणा FRAME_VALID_START_INTR			BIT(0)
#घोषणा FRAME_VALID_END_INTR			BIT(1)
#घोषणा TX_FIFO_EMPTY_INTR			BIT(8)
#घोषणा TX_FIFO_ALMOST_EMPTY_INTR		BIT(9)
#घोषणा TX_FIFO_ALMOST_FULL_INTR		BIT(10)
#घोषणा TX_FIFO_FULL_INTR			BIT(11)
#घोषणा RX_EMPTY_INTR				BIT(12)
#घोषणा RX_ALMOST_EMPTY_INTR			BIT(13)
#घोषणा RX_ALMOST_FULL_INTR			BIT(14)
#घोषणा RX_FULL_INTR				BIT(15)
#घोषणा INTERRUPT_STATUS_REG			0x34
#घोषणा TX_CLOCK_DIVIDER_REG			0x38
#घोषणा TX_FIFO_SIZE_REG			0x40
#घोषणा RX_FIFO_SIZE_REG			0x44
#घोषणा FIFO_SIZE_MASK				(0xfffff << 0)
#घोषणा TX_FIFO_WORDS_REG			0x48
#घोषणा RX_FIFO_WORDS_REG			0x4c
#घोषणा INTERRUPT_EDGE_LEVEL_REG		0x50
#घोषणा INTERRUPT_POLARITY_REG			0x54

#घोषणा TIMER_BASE				50	/* 20MHz master घड़ी */
#घोषणा DMA_BUFFER_SIZE				0x10000
#घोषणा NUM_DMA_BUFFERS				4
#घोषणा NUM_DMA_DESCRIPTORS			256

काष्ठा hpdi_निजी अणु
	व्योम __iomem *plx9080_mmio;
	u32 *dio_buffer[NUM_DMA_BUFFERS];	/* dma buffers */
	/* physical addresses of dma buffers */
	dma_addr_t dio_buffer_phys_addr[NUM_DMA_BUFFERS];
	/*
	 * array of dma descriptors पढ़ो by plx9080, allocated to get proper
	 * alignment
	 */
	काष्ठा plx_dma_desc *dma_desc;
	/* physical address of dma descriptor array */
	dma_addr_t dma_desc_phys_addr;
	अचिन्हित पूर्णांक num_dma_descriptors;
	/* poपूर्णांकer to start of buffers indexed by descriptor */
	u32 *desc_dio_buffer[NUM_DMA_DESCRIPTORS];
	/* index of the dma descriptor that is currently being used */
	अचिन्हित पूर्णांक dma_desc_index;
	अचिन्हित पूर्णांक tx_fअगरo_size;
	अचिन्हित पूर्णांक rx_fअगरo_size;
	अचिन्हित दीर्घ dio_count;
	/* number of bytes at which to generate COMEDI_CB_BLOCK events */
	अचिन्हित पूर्णांक block_size;
पूर्ण;

अटल व्योम gsc_hpdi_drain_dma(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक channel)
अणु
	काष्ठा hpdi_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक idx;
	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक desc;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक next;

	next = पढ़ोl(devpriv->plx9080_mmio + PLX_REG_DMAPADR(channel));

	idx = devpriv->dma_desc_index;
	start = le32_to_cpu(devpriv->dma_desc[idx].pci_start_addr);
	/* loop until we have पढ़ो all the full buffers */
	क्रम (desc = 0; (next < start || next >= start + devpriv->block_size) &&
	     desc < devpriv->num_dma_descriptors; desc++) अणु
		/* transfer data from dma buffer to comedi buffer */
		size = devpriv->block_size / माप(u32);
		अगर (cmd->stop_src == TRIG_COUNT) अणु
			अगर (size > devpriv->dio_count)
				size = devpriv->dio_count;
			devpriv->dio_count -= size;
		पूर्ण
		comedi_buf_ग_लिखो_samples(s, devpriv->desc_dio_buffer[idx],
					 size);
		idx++;
		idx %= devpriv->num_dma_descriptors;
		start = le32_to_cpu(devpriv->dma_desc[idx].pci_start_addr);

		devpriv->dma_desc_index = idx;
	पूर्ण
	/* XXX check क्रम buffer overrun somehow */
पूर्ण

अटल irqवापस_t gsc_hpdi_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा hpdi_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_async *async = s->async;
	u32 hpdi_पूर्णांकr_status, hpdi_board_status;
	u32 plx_status;
	u32 plx_bits;
	u8 dma0_status, dma1_status;
	अचिन्हित दीर्घ flags;

	अगर (!dev->attached)
		वापस IRQ_NONE;

	plx_status = पढ़ोl(devpriv->plx9080_mmio + PLX_REG_INTCSR);
	अगर ((plx_status &
	     (PLX_INTCSR_DMA0IA | PLX_INTCSR_DMA1IA | PLX_INTCSR_PLIA)) == 0)
		वापस IRQ_NONE;

	hpdi_पूर्णांकr_status = पढ़ोl(dev->mmio + INTERRUPT_STATUS_REG);
	hpdi_board_status = पढ़ोl(dev->mmio + BOARD_STATUS_REG);

	अगर (hpdi_पूर्णांकr_status)
		ग_लिखोl(hpdi_पूर्णांकr_status, dev->mmio + INTERRUPT_STATUS_REG);

	/* spin lock makes sure no one अन्यथा changes plx dma control reg */
	spin_lock_irqsave(&dev->spinlock, flags);
	dma0_status = पढ़ोb(devpriv->plx9080_mmio + PLX_REG_DMACSR0);
	अगर (plx_status & PLX_INTCSR_DMA0IA) अणु
		/* dma chan 0 पूर्णांकerrupt */
		ग_लिखोb((dma0_status & PLX_DMACSR_ENABLE) | PLX_DMACSR_CLEARINTR,
		       devpriv->plx9080_mmio + PLX_REG_DMACSR0);

		अगर (dma0_status & PLX_DMACSR_ENABLE)
			gsc_hpdi_drain_dma(dev, 0);
	पूर्ण
	spin_unlock_irqrestore(&dev->spinlock, flags);

	/* spin lock makes sure no one अन्यथा changes plx dma control reg */
	spin_lock_irqsave(&dev->spinlock, flags);
	dma1_status = पढ़ोb(devpriv->plx9080_mmio + PLX_REG_DMACSR1);
	अगर (plx_status & PLX_INTCSR_DMA1IA) अणु
		/* XXX */ /* dma chan 1 पूर्णांकerrupt */
		ग_लिखोb((dma1_status & PLX_DMACSR_ENABLE) | PLX_DMACSR_CLEARINTR,
		       devpriv->plx9080_mmio + PLX_REG_DMACSR1);
	पूर्ण
	spin_unlock_irqrestore(&dev->spinlock, flags);

	/* clear possible plx9080 पूर्णांकerrupt sources */
	अगर (plx_status & PLX_INTCSR_LDBIA) अणु
		/* clear local करोorbell पूर्णांकerrupt */
		plx_bits = पढ़ोl(devpriv->plx9080_mmio + PLX_REG_L2PDBELL);
		ग_लिखोl(plx_bits, devpriv->plx9080_mmio + PLX_REG_L2PDBELL);
	पूर्ण

	अगर (hpdi_board_status & RX_OVERRUN_BIT) अणु
		dev_err(dev->class_dev, "rx fifo overrun\n");
		async->events |= COMEDI_CB_ERROR;
	पूर्ण

	अगर (hpdi_board_status & RX_UNDERRUN_BIT) अणु
		dev_err(dev->class_dev, "rx fifo underrun\n");
		async->events |= COMEDI_CB_ERROR;
	पूर्ण

	अगर (devpriv->dio_count == 0)
		async->events |= COMEDI_CB_EOA;

	comedi_handle_events(dev, s);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम gsc_hpdi_पात_dma(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक channel)
अणु
	काष्ठा hpdi_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;

	/* spinlock क्रम plx dma control/status reg */
	spin_lock_irqsave(&dev->spinlock, flags);

	plx9080_पात_dma(devpriv->plx9080_mmio, channel);

	spin_unlock_irqrestore(&dev->spinlock, flags);
पूर्ण

अटल पूर्णांक gsc_hpdi_cancel(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s)
अणु
	ग_लिखोl(0, dev->mmio + BOARD_CONTROL_REG);
	ग_लिखोl(0, dev->mmio + INTERRUPT_CONTROL_REG);

	gsc_hpdi_पात_dma(dev, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक gsc_hpdi_cmd(काष्ठा comedi_device *dev,
			काष्ठा comedi_subdevice *s)
अणु
	काष्ठा hpdi_निजी *devpriv = dev->निजी;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित दीर्घ flags;
	u32 bits;

	अगर (s->io_bits)
		वापस -EINVAL;

	ग_लिखोl(RX_FIFO_RESET_BIT, dev->mmio + BOARD_CONTROL_REG);

	gsc_hpdi_पात_dma(dev, 0);

	devpriv->dma_desc_index = 0;

	/*
	 * These रेजिस्टर are supposedly unused during chained dma,
	 * but I have found that left over values from last operation
	 * occasionally cause problems with transfer of first dma
	 * block.  Initializing them to zero seems to fix the problem.
	 */
	ग_लिखोl(0, devpriv->plx9080_mmio + PLX_REG_DMASIZ0);
	ग_लिखोl(0, devpriv->plx9080_mmio + PLX_REG_DMAPADR0);
	ग_लिखोl(0, devpriv->plx9080_mmio + PLX_REG_DMALADR0);

	/* give location of first dma descriptor */
	bits = devpriv->dma_desc_phys_addr | PLX_DMADPR_DESCPCI |
	       PLX_DMADPR_TCINTR | PLX_DMADPR_XFERL2P;
	ग_लिखोl(bits, devpriv->plx9080_mmio + PLX_REG_DMADPR0);

	/* enable dma transfer */
	spin_lock_irqsave(&dev->spinlock, flags);
	ग_लिखोb(PLX_DMACSR_ENABLE | PLX_DMACSR_START | PLX_DMACSR_CLEARINTR,
	       devpriv->plx9080_mmio + PLX_REG_DMACSR0);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	अगर (cmd->stop_src == TRIG_COUNT)
		devpriv->dio_count = cmd->stop_arg;
	अन्यथा
		devpriv->dio_count = 1;

	/* clear over/under run status flags */
	ग_लिखोl(RX_UNDERRUN_BIT | RX_OVERRUN_BIT, dev->mmio + BOARD_STATUS_REG);

	/* enable पूर्णांकerrupts */
	ग_लिखोl(RX_FULL_INTR, dev->mmio + INTERRUPT_CONTROL_REG);

	ग_लिखोl(RX_ENABLE_BIT, dev->mmio + BOARD_CONTROL_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक gsc_hpdi_check_chanlist(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);

		अगर (chan != i) अणु
			dev_dbg(dev->class_dev,
				"chanlist must be ch 0 to 31 in order\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gsc_hpdi_cmd_test(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;

	अगर (s->io_bits)
		वापस -EINVAL;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_EXT);
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

	अगर (!cmd->chanlist_len || !cmd->chanlist) अणु
		cmd->chanlist_len = 32;
		err |= -EINVAL;
	पूर्ण
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* Step 4: fix up any arguments */

	/* Step 5: check channel list अगर it exists */

	अगर (cmd->chanlist && cmd->chanlist_len > 0)
		err |= gsc_hpdi_check_chanlist(dev, s, cmd);

	अगर (err)
		वापस 5;

	वापस 0;
पूर्ण

/* setup dma descriptors so a link completes every 'len' bytes */
अटल पूर्णांक gsc_hpdi_setup_dma_descriptors(काष्ठा comedi_device *dev,
					  अचिन्हित पूर्णांक len)
अणु
	काष्ठा hpdi_निजी *devpriv = dev->निजी;
	dma_addr_t phys_addr = devpriv->dma_desc_phys_addr;
	u32 next_bits = PLX_DMADPR_DESCPCI | PLX_DMADPR_TCINTR |
			PLX_DMADPR_XFERL2P;
	अचिन्हित पूर्णांक offset = 0;
	अचिन्हित पूर्णांक idx = 0;
	अचिन्हित पूर्णांक i;

	अगर (len > DMA_BUFFER_SIZE)
		len = DMA_BUFFER_SIZE;
	len -= len % माप(u32);
	अगर (len == 0)
		वापस -EINVAL;

	क्रम (i = 0; i < NUM_DMA_DESCRIPTORS && idx < NUM_DMA_BUFFERS; i++) अणु
		devpriv->dma_desc[i].pci_start_addr =
		    cpu_to_le32(devpriv->dio_buffer_phys_addr[idx] + offset);
		devpriv->dma_desc[i].local_start_addr = cpu_to_le32(FIFO_REG);
		devpriv->dma_desc[i].transfer_size = cpu_to_le32(len);
		devpriv->dma_desc[i].next = cpu_to_le32((phys_addr +
			(i + 1) * माप(devpriv->dma_desc[0])) | next_bits);

		devpriv->desc_dio_buffer[i] = devpriv->dio_buffer[idx] +
					      (offset / माप(u32));

		offset += len;
		अगर (len + offset > DMA_BUFFER_SIZE) अणु
			offset = 0;
			idx++;
		पूर्ण
	पूर्ण
	devpriv->num_dma_descriptors = i;
	/* fix last descriptor to poपूर्णांक back to first */
	devpriv->dma_desc[i - 1].next = cpu_to_le32(phys_addr | next_bits);

	devpriv->block_size = len;

	वापस len;
पूर्ण

अटल पूर्णांक gsc_hpdi_dio_insn_config(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_insn *insn,
				    अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक ret;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_BLOCK_SIZE:
		ret = gsc_hpdi_setup_dma_descriptors(dev, data[1]);
		अगर (ret)
			वापस ret;

		data[1] = ret;
		अवरोध;
	शेष:
		ret = comedi_dio_insn_config(dev, s, insn, data, 0xffffffff);
		अगर (ret)
			वापस ret;
		अवरोध;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल व्योम gsc_hpdi_मुक्त_dma(काष्ठा comedi_device *dev)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा hpdi_निजी *devpriv = dev->निजी;
	पूर्णांक i;

	अगर (!devpriv)
		वापस;

	/* मुक्त pci dma buffers */
	क्रम (i = 0; i < NUM_DMA_BUFFERS; i++) अणु
		अगर (devpriv->dio_buffer[i])
			dma_मुक्त_coherent(&pcidev->dev,
					  DMA_BUFFER_SIZE,
					  devpriv->dio_buffer[i],
					  devpriv->dio_buffer_phys_addr[i]);
	पूर्ण
	/* मुक्त dma descriptors */
	अगर (devpriv->dma_desc)
		dma_मुक्त_coherent(&pcidev->dev,
				  माप(काष्ठा plx_dma_desc) *
				  NUM_DMA_DESCRIPTORS,
				  devpriv->dma_desc,
				  devpriv->dma_desc_phys_addr);
पूर्ण

अटल पूर्णांक gsc_hpdi_init(काष्ठा comedi_device *dev)
अणु
	काष्ठा hpdi_निजी *devpriv = dev->निजी;
	u32 plx_पूर्णांकcsr_bits;

	/* रुको 10usec after reset beक्रमe accessing fअगरos */
	ग_लिखोl(BOARD_RESET_BIT, dev->mmio + BOARD_CONTROL_REG);
	usleep_range(10, 1000);

	ग_लिखोl(ALMOST_EMPTY_BITS(32) | ALMOST_FULL_BITS(32),
	       dev->mmio + RX_PROG_ALMOST_REG);
	ग_लिखोl(ALMOST_EMPTY_BITS(32) | ALMOST_FULL_BITS(32),
	       dev->mmio + TX_PROG_ALMOST_REG);

	devpriv->tx_fअगरo_size = पढ़ोl(dev->mmio + TX_FIFO_SIZE_REG) &
				FIFO_SIZE_MASK;
	devpriv->rx_fअगरo_size = पढ़ोl(dev->mmio + RX_FIFO_SIZE_REG) &
				FIFO_SIZE_MASK;

	ग_लिखोl(0, dev->mmio + INTERRUPT_CONTROL_REG);

	/* enable पूर्णांकerrupts */
	plx_पूर्णांकcsr_bits =
	    PLX_INTCSR_LSEABORTEN | PLX_INTCSR_LSEPARITYEN | PLX_INTCSR_PIEN |
	    PLX_INTCSR_PLIEN | PLX_INTCSR_PABORTIEN | PLX_INTCSR_LIOEN |
	    PLX_INTCSR_DMA0IEN;
	ग_लिखोl(plx_पूर्णांकcsr_bits, devpriv->plx9080_mmio + PLX_REG_INTCSR);

	वापस 0;
पूर्ण

अटल व्योम gsc_hpdi_init_plx9080(काष्ठा comedi_device *dev)
अणु
	काष्ठा hpdi_निजी *devpriv = dev->निजी;
	u32 bits;
	व्योम __iomem *plx_iobase = devpriv->plx9080_mmio;

#अगर_घोषित __BIG_ENDIAN
	bits = PLX_BIGEND_DMA0 | PLX_BIGEND_DMA1;
#अन्यथा
	bits = 0;
#पूर्ण_अगर
	ग_लिखोl(bits, devpriv->plx9080_mmio + PLX_REG_BIGEND);

	ग_लिखोl(0, devpriv->plx9080_mmio + PLX_REG_INTCSR);

	gsc_hpdi_पात_dma(dev, 0);
	gsc_hpdi_पात_dma(dev, 1);

	/* configure dma0 mode */
	bits = 0;
	/* enable पढ़ोy input */
	bits |= PLX_DMAMODE_READYIEN;
	/* enable dma chaining */
	bits |= PLX_DMAMODE_CHAINEN;
	/*
	 * enable पूर्णांकerrupt on dma करोne
	 * (probably करोn't need this, since chain never finishes)
	 */
	bits |= PLX_DMAMODE_DONEIEN;
	/*
	 * करोn't increment local address during transfers
	 * (we are transferring from a fixed fअगरo रेजिस्टर)
	 */
	bits |= PLX_DMAMODE_LACONST;
	/* route dma पूर्णांकerrupt to pci bus */
	bits |= PLX_DMAMODE_INTRPCI;
	/* enable demand mode */
	bits |= PLX_DMAMODE_DEMAND;
	/* enable local burst mode */
	bits |= PLX_DMAMODE_BURSTEN;
	bits |= PLX_DMAMODE_WIDTH_32;
	ग_लिखोl(bits, plx_iobase + PLX_REG_DMAMODE0);
पूर्ण

अटल पूर्णांक gsc_hpdi_स्वतः_attach(काष्ठा comedi_device *dev,
				अचिन्हित दीर्घ context_unused)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा hpdi_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक i;
	पूर्णांक retval;

	dev->board_name = "pci-hpdi32";

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	retval = comedi_pci_enable(dev);
	अगर (retval)
		वापस retval;
	pci_set_master(pcidev);

	devpriv->plx9080_mmio = pci_ioremap_bar(pcidev, 0);
	dev->mmio = pci_ioremap_bar(pcidev, 2);
	अगर (!devpriv->plx9080_mmio || !dev->mmio) अणु
		dev_warn(dev->class_dev, "failed to remap io memory\n");
		वापस -ENOMEM;
	पूर्ण

	gsc_hpdi_init_plx9080(dev);

	/* get irq */
	अगर (request_irq(pcidev->irq, gsc_hpdi_पूर्णांकerrupt, IRQF_SHARED,
			dev->board_name, dev)) अणु
		dev_warn(dev->class_dev,
			 "unable to allocate irq %u\n", pcidev->irq);
		वापस -EINVAL;
	पूर्ण
	dev->irq = pcidev->irq;

	dev_dbg(dev->class_dev, " irq %u\n", dev->irq);

	/* allocate pci dma buffers */
	क्रम (i = 0; i < NUM_DMA_BUFFERS; i++) अणु
		devpriv->dio_buffer[i] =
		    dma_alloc_coherent(&pcidev->dev, DMA_BUFFER_SIZE,
				       &devpriv->dio_buffer_phys_addr[i],
				       GFP_KERNEL);
		अगर (!devpriv->dio_buffer[i]) अणु
			dev_warn(dev->class_dev,
				 "failed to allocate DMA buffer\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	/* allocate dma descriptors */
	devpriv->dma_desc = dma_alloc_coherent(&pcidev->dev,
					       माप(काष्ठा plx_dma_desc) *
					       NUM_DMA_DESCRIPTORS,
					       &devpriv->dma_desc_phys_addr,
					       GFP_KERNEL);
	अगर (!devpriv->dma_desc) अणु
		dev_warn(dev->class_dev,
			 "failed to allocate DMA descriptors\n");
		वापस -ENOMEM;
	पूर्ण
	अगर (devpriv->dma_desc_phys_addr & 0xf) अणु
		dev_warn(dev->class_dev,
			 " dma descriptors not quad-word aligned (bug)\n");
		वापस -EIO;
	पूर्ण

	retval = gsc_hpdi_setup_dma_descriptors(dev, 0x1000);
	अगर (retval < 0)
		वापस retval;

	retval = comedi_alloc_subdevices(dev, 1);
	अगर (retval)
		वापस retval;

	/* Digital I/O subdevice */
	s = &dev->subdevices[0];
	dev->पढ़ो_subdev = s;
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE | SDF_LSAMPL |
			  SDF_CMD_READ;
	s->n_chan	= 32;
	s->len_chanlist	= 32;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_config	= gsc_hpdi_dio_insn_config;
	s->करो_cmd	= gsc_hpdi_cmd;
	s->करो_cmdtest	= gsc_hpdi_cmd_test;
	s->cancel	= gsc_hpdi_cancel;

	वापस gsc_hpdi_init(dev);
पूर्ण

अटल व्योम gsc_hpdi_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा hpdi_निजी *devpriv = dev->निजी;

	अगर (dev->irq)
		मुक्त_irq(dev->irq, dev);
	अगर (devpriv) अणु
		अगर (devpriv->plx9080_mmio) अणु
			ग_लिखोl(0, devpriv->plx9080_mmio + PLX_REG_INTCSR);
			iounmap(devpriv->plx9080_mmio);
		पूर्ण
		अगर (dev->mmio)
			iounmap(dev->mmio);
	पूर्ण
	comedi_pci_disable(dev);
	gsc_hpdi_मुक्त_dma(dev);
पूर्ण

अटल काष्ठा comedi_driver gsc_hpdi_driver = अणु
	.driver_name	= "gsc_hpdi",
	.module		= THIS_MODULE,
	.स्वतः_attach	= gsc_hpdi_स्वतः_attach,
	.detach		= gsc_hpdi_detach,
पूर्ण;

अटल पूर्णांक gsc_hpdi_pci_probe(काष्ठा pci_dev *dev,
			      स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &gsc_hpdi_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id gsc_hpdi_pci_table[] = अणु
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9080,
			 PCI_VENDOR_ID_PLX, 0x2400) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, gsc_hpdi_pci_table);

अटल काष्ठा pci_driver gsc_hpdi_pci_driver = अणु
	.name		= "gsc_hpdi",
	.id_table	= gsc_hpdi_pci_table,
	.probe		= gsc_hpdi_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(gsc_hpdi_driver, gsc_hpdi_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for General Standards PCI-HPDI32/PMC-HPDI32");
MODULE_LICENSE("GPL");
