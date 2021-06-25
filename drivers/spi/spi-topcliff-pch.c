<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SPI bus driver क्रम the Topclअगरf PCH used by Intel SoCs
 *
 * Copyright (C) 2011 LAPIS Semiconductor Co., Ltd.
 */

#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/रुको.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/spi/spidev.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/dmaengine.h>
#समावेश <linux/pch_dma.h>

/* Register offsets */
#घोषणा PCH_SPCR		0x00	/* SPI control रेजिस्टर */
#घोषणा PCH_SPBRR		0x04	/* SPI baud rate रेजिस्टर */
#घोषणा PCH_SPSR		0x08	/* SPI status रेजिस्टर */
#घोषणा PCH_SPDWR		0x0C	/* SPI ग_लिखो data रेजिस्टर */
#घोषणा PCH_SPDRR		0x10	/* SPI पढ़ो data रेजिस्टर */
#घोषणा PCH_SSNXCR		0x18	/* SSN Expand Control Register */
#घोषणा PCH_SRST		0x1C	/* SPI reset रेजिस्टर */
#घोषणा PCH_ADDRESS_SIZE	0x20

#घोषणा PCH_SPSR_TFD		0x000007C0
#घोषणा PCH_SPSR_RFD		0x0000F800

#घोषणा PCH_READABLE(x)		(((x) & PCH_SPSR_RFD)>>11)
#घोषणा PCH_WRITABLE(x)		(((x) & PCH_SPSR_TFD)>>6)

#घोषणा PCH_RX_THOLD		7
#घोषणा PCH_RX_THOLD_MAX	15

#घोषणा PCH_TX_THOLD		2

#घोषणा PCH_MAX_BAUDRATE	5000000
#घोषणा PCH_MAX_FIFO_DEPTH	16

#घोषणा STATUS_RUNNING		1
#घोषणा STATUS_EXITING		2
#घोषणा PCH_SLEEP_TIME		10

#घोषणा SSN_LOW			0x02U
#घोषणा SSN_HIGH		0x03U
#घोषणा SSN_NO_CONTROL		0x00U
#घोषणा PCH_MAX_CS		0xFF
#घोषणा PCI_DEVICE_ID_GE_SPI	0x8816

#घोषणा SPCR_SPE_BIT		(1 << 0)
#घोषणा SPCR_MSTR_BIT		(1 << 1)
#घोषणा SPCR_LSBF_BIT		(1 << 4)
#घोषणा SPCR_CPHA_BIT		(1 << 5)
#घोषणा SPCR_CPOL_BIT		(1 << 6)
#घोषणा SPCR_TFIE_BIT		(1 << 8)
#घोषणा SPCR_RFIE_BIT		(1 << 9)
#घोषणा SPCR_FIE_BIT		(1 << 10)
#घोषणा SPCR_ORIE_BIT		(1 << 11)
#घोषणा SPCR_MDFIE_BIT		(1 << 12)
#घोषणा SPCR_FICLR_BIT		(1 << 24)
#घोषणा SPSR_TFI_BIT		(1 << 0)
#घोषणा SPSR_RFI_BIT		(1 << 1)
#घोषणा SPSR_FI_BIT		(1 << 2)
#घोषणा SPSR_ORF_BIT		(1 << 3)
#घोषणा SPBRR_SIZE_BIT		(1 << 10)

#घोषणा PCH_ALL			(SPCR_TFIE_BIT|SPCR_RFIE_BIT|SPCR_FIE_BIT|\
				SPCR_ORIE_BIT|SPCR_MDFIE_BIT)

#घोषणा SPCR_RFIC_FIELD		20
#घोषणा SPCR_TFIC_FIELD		16

#घोषणा MASK_SPBRR_SPBR_BITS	((1 << 10) - 1)
#घोषणा MASK_RFIC_SPCR_BITS	(0xf << SPCR_RFIC_FIELD)
#घोषणा MASK_TFIC_SPCR_BITS	(0xf << SPCR_TFIC_FIELD)

#घोषणा PCH_CLOCK_HZ		50000000
#घोषणा PCH_MAX_SPBR		1023

/* Definition क्रम ML7213/ML7223/ML7831 by LAPIS Semiconductor */
#घोषणा PCI_DEVICE_ID_ML7213_SPI	0x802c
#घोषणा PCI_DEVICE_ID_ML7223_SPI	0x800F
#घोषणा PCI_DEVICE_ID_ML7831_SPI	0x8816

/*
 * Set the number of SPI instance max
 * Intel EG20T PCH :		1ch
 * LAPIS Semiconductor ML7213 IOH :	2ch
 * LAPIS Semiconductor ML7223 IOH :	1ch
 * LAPIS Semiconductor ML7831 IOH :	1ch
*/
#घोषणा PCH_SPI_MAX_DEV			2

#घोषणा PCH_BUF_SIZE		4096
#घोषणा PCH_DMA_TRANS_SIZE	12

अटल पूर्णांक use_dma = 1;

काष्ठा pch_spi_dma_ctrl अणु
	काष्ठा dma_async_tx_descriptor	*desc_tx;
	काष्ठा dma_async_tx_descriptor	*desc_rx;
	काष्ठा pch_dma_slave		param_tx;
	काष्ठा pch_dma_slave		param_rx;
	काष्ठा dma_chan		*chan_tx;
	काष्ठा dma_chan		*chan_rx;
	काष्ठा scatterlist		*sg_tx_p;
	काष्ठा scatterlist		*sg_rx_p;
	काष्ठा scatterlist		sg_tx;
	काष्ठा scatterlist		sg_rx;
	पूर्णांक				nent;
	व्योम				*tx_buf_virt;
	व्योम				*rx_buf_virt;
	dma_addr_t			tx_buf_dma;
	dma_addr_t			rx_buf_dma;
पूर्ण;
/**
 * काष्ठा pch_spi_data - Holds the SPI channel specअगरic details
 * @io_remap_addr:		The remapped PCI base address
 * @io_base_addr:		Base address
 * @master:			Poपूर्णांकer to the SPI master काष्ठाure
 * @work:			Reference to work queue handler
 * @रुको:			Wait queue क्रम waking up upon receiving an
 *				पूर्णांकerrupt.
 * @transfer_complete:		Status of SPI Transfer
 * @bcurrent_msg_processing:	Status flag क्रम message processing
 * @lock:			Lock क्रम protecting this काष्ठाure
 * @queue:			SPI Message queue
 * @status:			Status of the SPI driver
 * @bpw_len:			Length of data to be transferred in bits per
 *				word
 * @transfer_active:		Flag showing active transfer
 * @tx_index:			Transmit data count; क्रम bookkeeping during
 *				transfer
 * @rx_index:			Receive data count; क्रम bookkeeping during
 *				transfer
 * @pkt_tx_buff:		Buffer क्रम data to be transmitted
 * @pkt_rx_buff:		Buffer क्रम received data
 * @n_curnt_chip:		The chip number that this SPI driver currently
 *				operates on
 * @current_chip:		Reference to the current chip that this SPI
 *				driver currently operates on
 * @current_msg:		The current message that this SPI driver is
 *				handling
 * @cur_trans:			The current transfer that this SPI driver is
 *				handling
 * @board_dat:			Reference to the SPI device data काष्ठाure
 * @plat_dev:			platक्रमm_device काष्ठाure
 * @ch:				SPI channel number
 * @dma:			Local DMA inक्रमmation
 * @use_dma:			True अगर DMA is to be used
 * @irq_reg_sts:		Status of IRQ registration
 * @save_total_len:		Save length जबतक data is being transferred
 */
काष्ठा pch_spi_data अणु
	व्योम __iomem *io_remap_addr;
	अचिन्हित दीर्घ io_base_addr;
	काष्ठा spi_master *master;
	काष्ठा work_काष्ठा work;
	रुको_queue_head_t रुको;
	u8 transfer_complete;
	u8 bcurrent_msg_processing;
	spinlock_t lock;
	काष्ठा list_head queue;
	u8 status;
	u32 bpw_len;
	u8 transfer_active;
	u32 tx_index;
	u32 rx_index;
	u16 *pkt_tx_buff;
	u16 *pkt_rx_buff;
	u8 n_curnt_chip;
	काष्ठा spi_device *current_chip;
	काष्ठा spi_message *current_msg;
	काष्ठा spi_transfer *cur_trans;
	काष्ठा pch_spi_board_data *board_dat;
	काष्ठा platक्रमm_device	*plat_dev;
	पूर्णांक ch;
	काष्ठा pch_spi_dma_ctrl dma;
	पूर्णांक use_dma;
	u8 irq_reg_sts;
	पूर्णांक save_total_len;
पूर्ण;

/**
 * काष्ठा pch_spi_board_data - Holds the SPI device specअगरic details
 * @pdev:		Poपूर्णांकer to the PCI device
 * @suspend_sts:	Status of suspend
 * @num:		The number of SPI device instance
 */
काष्ठा pch_spi_board_data अणु
	काष्ठा pci_dev *pdev;
	u8 suspend_sts;
	पूर्णांक num;
पूर्ण;

काष्ठा pch_pd_dev_save अणु
	पूर्णांक num;
	काष्ठा platक्रमm_device *pd_save[PCH_SPI_MAX_DEV];
	काष्ठा pch_spi_board_data *board_dat;
पूर्ण;

अटल स्थिर काष्ठा pci_device_id pch_spi_pcidev_id[] = अणु
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_GE_SPI),    1, पूर्ण,
	अणु PCI_VDEVICE(ROHM, PCI_DEVICE_ID_ML7213_SPI), 2, पूर्ण,
	अणु PCI_VDEVICE(ROHM, PCI_DEVICE_ID_ML7223_SPI), 1, पूर्ण,
	अणु PCI_VDEVICE(ROHM, PCI_DEVICE_ID_ML7831_SPI), 1, पूर्ण,
	अणु पूर्ण
पूर्ण;

/**
 * pch_spi_ग_लिखोreg() - Perक्रमms  रेजिस्टर ग_लिखोs
 * @master:	Poपूर्णांकer to काष्ठा spi_master.
 * @idx:	Register offset.
 * @val:	Value to be written to रेजिस्टर.
 */
अटल अंतरभूत व्योम pch_spi_ग_लिखोreg(काष्ठा spi_master *master, पूर्णांक idx, u32 val)
अणु
	काष्ठा pch_spi_data *data = spi_master_get_devdata(master);
	ioग_लिखो32(val, (data->io_remap_addr + idx));
पूर्ण

/**
 * pch_spi_पढ़ोreg() - Perक्रमms रेजिस्टर पढ़ोs
 * @master:	Poपूर्णांकer to काष्ठा spi_master.
 * @idx:	Register offset.
 */
अटल अंतरभूत u32 pch_spi_पढ़ोreg(काष्ठा spi_master *master, पूर्णांक idx)
अणु
	काष्ठा pch_spi_data *data = spi_master_get_devdata(master);
	वापस ioपढ़ो32(data->io_remap_addr + idx);
पूर्ण

अटल अंतरभूत व्योम pch_spi_setclr_reg(काष्ठा spi_master *master, पूर्णांक idx,
				      u32 set, u32 clr)
अणु
	u32 पंचांगp = pch_spi_पढ़ोreg(master, idx);
	पंचांगp = (पंचांगp & ~clr) | set;
	pch_spi_ग_लिखोreg(master, idx, पंचांगp);
पूर्ण

अटल व्योम pch_spi_set_master_mode(काष्ठा spi_master *master)
अणु
	pch_spi_setclr_reg(master, PCH_SPCR, SPCR_MSTR_BIT, 0);
पूर्ण

/**
 * pch_spi_clear_fअगरo() - Clears the Transmit and Receive FIFOs
 * @master:	Poपूर्णांकer to काष्ठा spi_master.
 */
अटल व्योम pch_spi_clear_fअगरo(काष्ठा spi_master *master)
अणु
	pch_spi_setclr_reg(master, PCH_SPCR, SPCR_FICLR_BIT, 0);
	pch_spi_setclr_reg(master, PCH_SPCR, 0, SPCR_FICLR_BIT);
पूर्ण

अटल व्योम pch_spi_handler_sub(काष्ठा pch_spi_data *data, u32 reg_spsr_val,
				व्योम __iomem *io_remap_addr)
अणु
	u32 n_पढ़ो, tx_index, rx_index, bpw_len;
	u16 *pkt_rx_buffer, *pkt_tx_buff;
	पूर्णांक पढ़ो_cnt;
	u32 reg_spcr_val;
	व्योम __iomem *spsr;
	व्योम __iomem *spdrr;
	व्योम __iomem *spdwr;

	spsr = io_remap_addr + PCH_SPSR;
	ioग_लिखो32(reg_spsr_val, spsr);

	अगर (data->transfer_active) अणु
		rx_index = data->rx_index;
		tx_index = data->tx_index;
		bpw_len = data->bpw_len;
		pkt_rx_buffer = data->pkt_rx_buff;
		pkt_tx_buff = data->pkt_tx_buff;

		spdrr = io_remap_addr + PCH_SPDRR;
		spdwr = io_remap_addr + PCH_SPDWR;

		n_पढ़ो = PCH_READABLE(reg_spsr_val);

		क्रम (पढ़ो_cnt = 0; (पढ़ो_cnt < n_पढ़ो); पढ़ो_cnt++) अणु
			pkt_rx_buffer[rx_index++] = ioपढ़ो32(spdrr);
			अगर (tx_index < bpw_len)
				ioग_लिखो32(pkt_tx_buff[tx_index++], spdwr);
		पूर्ण

		/* disable RFI अगर not needed */
		अगर ((bpw_len - rx_index) <= PCH_MAX_FIFO_DEPTH) अणु
			reg_spcr_val = ioपढ़ो32(io_remap_addr + PCH_SPCR);
			reg_spcr_val &= ~SPCR_RFIE_BIT; /* disable RFI */

			/* reset rx threshold */
			reg_spcr_val &= ~MASK_RFIC_SPCR_BITS;
			reg_spcr_val |= (PCH_RX_THOLD_MAX << SPCR_RFIC_FIELD);

			ioग_लिखो32(reg_spcr_val, (io_remap_addr + PCH_SPCR));
		पूर्ण

		/* update counts */
		data->tx_index = tx_index;
		data->rx_index = rx_index;

		/* अगर transfer complete पूर्णांकerrupt */
		अगर (reg_spsr_val & SPSR_FI_BIT) अणु
			अगर ((tx_index == bpw_len) && (rx_index == tx_index)) अणु
				/* disable पूर्णांकerrupts */
				pch_spi_setclr_reg(data->master, PCH_SPCR, 0,
						   PCH_ALL);

				/* transfer is completed;
				   inक्रमm pch_spi_process_messages */
				data->transfer_complete = true;
				data->transfer_active = false;
				wake_up(&data->रुको);
			पूर्ण अन्यथा अणु
				dev_vdbg(&data->master->dev,
					"%s : Transfer is not completed",
					__func__);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * pch_spi_handler() - Interrupt handler
 * @irq:	The पूर्णांकerrupt number.
 * @dev_id:	Poपूर्णांकer to काष्ठा pch_spi_board_data.
 */
अटल irqवापस_t pch_spi_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	u32 reg_spsr_val;
	व्योम __iomem *spsr;
	व्योम __iomem *io_remap_addr;
	irqवापस_t ret = IRQ_NONE;
	काष्ठा pch_spi_data *data = dev_id;
	काष्ठा pch_spi_board_data *board_dat = data->board_dat;

	अगर (board_dat->suspend_sts) अणु
		dev_dbg(&board_dat->pdev->dev,
			"%s returning due to suspend\n", __func__);
		वापस IRQ_NONE;
	पूर्ण

	io_remap_addr = data->io_remap_addr;
	spsr = io_remap_addr + PCH_SPSR;

	reg_spsr_val = ioपढ़ो32(spsr);

	अगर (reg_spsr_val & SPSR_ORF_BIT) अणु
		dev_err(&board_dat->pdev->dev, "%s Over run error\n", __func__);
		अगर (data->current_msg->complete) अणु
			data->transfer_complete = true;
			data->current_msg->status = -EIO;
			data->current_msg->complete(data->current_msg->context);
			data->bcurrent_msg_processing = false;
			data->current_msg = शून्य;
			data->cur_trans = शून्य;
		पूर्ण
	पूर्ण

	अगर (data->use_dma)
		वापस IRQ_NONE;

	/* Check अगर the पूर्णांकerrupt is क्रम SPI device */
	अगर (reg_spsr_val & (SPSR_FI_BIT | SPSR_RFI_BIT)) अणु
		pch_spi_handler_sub(data, reg_spsr_val, io_remap_addr);
		ret = IRQ_HANDLED;
	पूर्ण

	dev_dbg(&board_dat->pdev->dev, "%s EXIT return value=%d\n",
		__func__, ret);

	वापस ret;
पूर्ण

/**
 * pch_spi_set_baud_rate() - Sets SPBR field in SPBRR
 * @master:	Poपूर्णांकer to काष्ठा spi_master.
 * @speed_hz:	Baud rate.
 */
अटल व्योम pch_spi_set_baud_rate(काष्ठा spi_master *master, u32 speed_hz)
अणु
	u32 n_spbr = PCH_CLOCK_HZ / (speed_hz * 2);

	/* अगर baud rate is less than we can support limit it */
	अगर (n_spbr > PCH_MAX_SPBR)
		n_spbr = PCH_MAX_SPBR;

	pch_spi_setclr_reg(master, PCH_SPBRR, n_spbr, MASK_SPBRR_SPBR_BITS);
पूर्ण

/**
 * pch_spi_set_bits_per_word() - Sets SIZE field in SPBRR
 * @master:		Poपूर्णांकer to काष्ठा spi_master.
 * @bits_per_word:	Bits per word क्रम SPI transfer.
 */
अटल व्योम pch_spi_set_bits_per_word(काष्ठा spi_master *master,
				      u8 bits_per_word)
अणु
	अगर (bits_per_word == 8)
		pch_spi_setclr_reg(master, PCH_SPBRR, 0, SPBRR_SIZE_BIT);
	अन्यथा
		pch_spi_setclr_reg(master, PCH_SPBRR, SPBRR_SIZE_BIT, 0);
पूर्ण

/**
 * pch_spi_setup_transfer() - Configures the PCH SPI hardware क्रम transfer
 * @spi:	Poपूर्णांकer to काष्ठा spi_device.
 */
अटल व्योम pch_spi_setup_transfer(काष्ठा spi_device *spi)
अणु
	u32 flags = 0;

	dev_dbg(&spi->dev, "%s SPBRR content =%x setting baud rate=%d\n",
		__func__, pch_spi_पढ़ोreg(spi->master, PCH_SPBRR),
		spi->max_speed_hz);
	pch_spi_set_baud_rate(spi->master, spi->max_speed_hz);

	/* set bits per word */
	pch_spi_set_bits_per_word(spi->master, spi->bits_per_word);

	अगर (!(spi->mode & SPI_LSB_FIRST))
		flags |= SPCR_LSBF_BIT;
	अगर (spi->mode & SPI_CPOL)
		flags |= SPCR_CPOL_BIT;
	अगर (spi->mode & SPI_CPHA)
		flags |= SPCR_CPHA_BIT;
	pch_spi_setclr_reg(spi->master, PCH_SPCR, flags,
			   (SPCR_LSBF_BIT | SPCR_CPOL_BIT | SPCR_CPHA_BIT));

	/* Clear the FIFO by toggling  FICLR to 1 and back to 0 */
	pch_spi_clear_fअगरo(spi->master);
पूर्ण

/**
 * pch_spi_reset() - Clears SPI रेजिस्टरs
 * @master:	Poपूर्णांकer to काष्ठा spi_master.
 */
अटल व्योम pch_spi_reset(काष्ठा spi_master *master)
अणु
	/* ग_लिखो 1 to reset SPI */
	pch_spi_ग_लिखोreg(master, PCH_SRST, 0x1);

	/* clear reset */
	pch_spi_ग_लिखोreg(master, PCH_SRST, 0x0);
पूर्ण

अटल पूर्णांक pch_spi_transfer(काष्ठा spi_device *pspi, काष्ठा spi_message *pmsg)
अणु

	काष्ठा spi_transfer *transfer;
	काष्ठा pch_spi_data *data = spi_master_get_devdata(pspi->master);
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&data->lock, flags);
	/* validate Tx/Rx buffers and Transfer length */
	list_क्रम_each_entry(transfer, &pmsg->transfers, transfer_list) अणु
		अगर (!transfer->tx_buf && !transfer->rx_buf) अणु
			dev_err(&pspi->dev,
				"%s Tx and Rx buffer NULL\n", __func__);
			retval = -EINVAL;
			जाओ err_वापस_spinlock;
		पूर्ण

		अगर (!transfer->len) अणु
			dev_err(&pspi->dev, "%s Transfer length invalid\n",
				__func__);
			retval = -EINVAL;
			जाओ err_वापस_spinlock;
		पूर्ण

		dev_dbg(&pspi->dev,
			"%s Tx/Rx buffer valid. Transfer length valid\n",
			__func__);
	पूर्ण
	spin_unlock_irqrestore(&data->lock, flags);

	/* We won't process any messages अगर we have been asked to terminate */
	अगर (data->status == STATUS_EXITING) अणु
		dev_err(&pspi->dev, "%s status = STATUS_EXITING.\n", __func__);
		retval = -ESHUTDOWN;
		जाओ err_out;
	पूर्ण

	/* If suspended ,वापस -EINVAL */
	अगर (data->board_dat->suspend_sts) अणु
		dev_err(&pspi->dev, "%s suspend; returning EINVAL\n", __func__);
		retval = -EINVAL;
		जाओ err_out;
	पूर्ण

	/* set status of message */
	pmsg->actual_length = 0;
	dev_dbg(&pspi->dev, "%s - pmsg->status =%d\n", __func__, pmsg->status);

	pmsg->status = -EINPROGRESS;
	spin_lock_irqsave(&data->lock, flags);
	/* add message to queue */
	list_add_tail(&pmsg->queue, &data->queue);
	spin_unlock_irqrestore(&data->lock, flags);

	dev_dbg(&pspi->dev, "%s - Invoked list_add_tail\n", __func__);

	schedule_work(&data->work);
	dev_dbg(&pspi->dev, "%s - Invoked queue work\n", __func__);

	retval = 0;

err_out:
	dev_dbg(&pspi->dev, "%s RETURN=%d\n", __func__, retval);
	वापस retval;
err_वापस_spinlock:
	dev_dbg(&pspi->dev, "%s RETURN=%d\n", __func__, retval);
	spin_unlock_irqrestore(&data->lock, flags);
	वापस retval;
पूर्ण

अटल अंतरभूत व्योम pch_spi_select_chip(काष्ठा pch_spi_data *data,
				       काष्ठा spi_device *pspi)
अणु
	अगर (data->current_chip != शून्य) अणु
		अगर (pspi->chip_select != data->n_curnt_chip) अणु
			dev_dbg(&pspi->dev, "%s : different slave\n", __func__);
			data->current_chip = शून्य;
		पूर्ण
	पूर्ण

	data->current_chip = pspi;

	data->n_curnt_chip = data->current_chip->chip_select;

	dev_dbg(&pspi->dev, "%s :Invoking pch_spi_setup_transfer\n", __func__);
	pch_spi_setup_transfer(pspi);
पूर्ण

अटल व्योम pch_spi_set_tx(काष्ठा pch_spi_data *data, पूर्णांक *bpw)
अणु
	पूर्णांक size;
	u32 n_ग_लिखोs;
	पूर्णांक j;
	काष्ठा spi_message *pmsg, *पंचांगp;
	स्थिर u8 *tx_buf;
	स्थिर u16 *tx_sbuf;

	/* set baud rate अगर needed */
	अगर (data->cur_trans->speed_hz) अणु
		dev_dbg(&data->master->dev, "%s:setting baud rate\n", __func__);
		pch_spi_set_baud_rate(data->master, data->cur_trans->speed_hz);
	पूर्ण

	/* set bits per word अगर needed */
	अगर (data->cur_trans->bits_per_word &&
	    (data->current_msg->spi->bits_per_word != data->cur_trans->bits_per_word)) अणु
		dev_dbg(&data->master->dev, "%s:set bits per word\n", __func__);
		pch_spi_set_bits_per_word(data->master,
					  data->cur_trans->bits_per_word);
		*bpw = data->cur_trans->bits_per_word;
	पूर्ण अन्यथा अणु
		*bpw = data->current_msg->spi->bits_per_word;
	पूर्ण

	/* reset Tx/Rx index */
	data->tx_index = 0;
	data->rx_index = 0;

	data->bpw_len = data->cur_trans->len / (*bpw / 8);

	/* find alloc size */
	size = data->cur_trans->len * माप(*data->pkt_tx_buff);

	/* allocate memory क्रम pkt_tx_buff & pkt_rx_buffer */
	data->pkt_tx_buff = kzalloc(size, GFP_KERNEL);
	अगर (data->pkt_tx_buff != शून्य) अणु
		data->pkt_rx_buff = kzalloc(size, GFP_KERNEL);
		अगर (!data->pkt_rx_buff)
			kमुक्त(data->pkt_tx_buff);
	पूर्ण

	अगर (!data->pkt_rx_buff) अणु
		/* flush queue and set status of all transfers to -ENOMEM */
		list_क्रम_each_entry_safe(pmsg, पंचांगp, data->queue.next, queue) अणु
			pmsg->status = -ENOMEM;

			अगर (pmsg->complete)
				pmsg->complete(pmsg->context);

			/* delete from queue */
			list_del_init(&pmsg->queue);
		पूर्ण
		वापस;
	पूर्ण

	/* copy Tx Data */
	अगर (data->cur_trans->tx_buf != शून्य) अणु
		अगर (*bpw == 8) अणु
			tx_buf = data->cur_trans->tx_buf;
			क्रम (j = 0; j < data->bpw_len; j++)
				data->pkt_tx_buff[j] = *tx_buf++;
		पूर्ण अन्यथा अणु
			tx_sbuf = data->cur_trans->tx_buf;
			क्रम (j = 0; j < data->bpw_len; j++)
				data->pkt_tx_buff[j] = *tx_sbuf++;
		पूर्ण
	पूर्ण

	/* अगर len greater than PCH_MAX_FIFO_DEPTH, ग_लिखो 16,अन्यथा len bytes */
	n_ग_लिखोs = data->bpw_len;
	अगर (n_ग_लिखोs > PCH_MAX_FIFO_DEPTH)
		n_ग_लिखोs = PCH_MAX_FIFO_DEPTH;

	dev_dbg(&data->master->dev,
		"\n%s:Pulling down SSN low - writing 0x2 to SSNXCR\n",
		__func__);
	pch_spi_ग_लिखोreg(data->master, PCH_SSNXCR, SSN_LOW);

	क्रम (j = 0; j < n_ग_लिखोs; j++)
		pch_spi_ग_लिखोreg(data->master, PCH_SPDWR, data->pkt_tx_buff[j]);

	/* update tx_index */
	data->tx_index = j;

	/* reset transfer complete flag */
	data->transfer_complete = false;
	data->transfer_active = true;
पूर्ण

अटल व्योम pch_spi_nomore_transfer(काष्ठा pch_spi_data *data)
अणु
	काष्ठा spi_message *pmsg, *पंचांगp;
	dev_dbg(&data->master->dev, "%s called\n", __func__);
	/* Invoke complete callback
	 * [To the spi core..indicating end of transfer] */
	data->current_msg->status = 0;

	अगर (data->current_msg->complete) अणु
		dev_dbg(&data->master->dev,
			"%s:Invoking callback of SPI core\n", __func__);
		data->current_msg->complete(data->current_msg->context);
	पूर्ण

	/* update status in global variable */
	data->bcurrent_msg_processing = false;

	dev_dbg(&data->master->dev,
		"%s:data->bcurrent_msg_processing = false\n", __func__);

	data->current_msg = शून्य;
	data->cur_trans = शून्य;

	/* check अगर we have items in list and not suspending
	 * वापस 1 अगर list empty */
	अगर ((list_empty(&data->queue) == 0) &&
	    (!data->board_dat->suspend_sts) &&
	    (data->status != STATUS_EXITING)) अणु
		/* We have some more work to करो (either there is more tranपूर्णांक
		 * bpw;sfer requests in the current message or there are
		 *more messages)
		 */
		dev_dbg(&data->master->dev, "%s:Invoke queue_work\n", __func__);
		schedule_work(&data->work);
	पूर्ण अन्यथा अगर (data->board_dat->suspend_sts ||
		   data->status == STATUS_EXITING) अणु
		dev_dbg(&data->master->dev,
			"%s suspend/remove initiated, flushing queue\n",
			__func__);
		list_क्रम_each_entry_safe(pmsg, पंचांगp, data->queue.next, queue) अणु
			pmsg->status = -EIO;

			अगर (pmsg->complete)
				pmsg->complete(pmsg->context);

			/* delete from queue */
			list_del_init(&pmsg->queue);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pch_spi_set_ir(काष्ठा pch_spi_data *data)
अणु
	/* enable पूर्णांकerrupts, set threshold, enable SPI */
	अगर ((data->bpw_len) > PCH_MAX_FIFO_DEPTH)
		/* set receive threshold to PCH_RX_THOLD */
		pch_spi_setclr_reg(data->master, PCH_SPCR,
				   PCH_RX_THOLD << SPCR_RFIC_FIELD |
				   SPCR_FIE_BIT | SPCR_RFIE_BIT |
				   SPCR_ORIE_BIT | SPCR_SPE_BIT,
				   MASK_RFIC_SPCR_BITS | PCH_ALL);
	अन्यथा
		/* set receive threshold to maximum */
		pch_spi_setclr_reg(data->master, PCH_SPCR,
				   PCH_RX_THOLD_MAX << SPCR_RFIC_FIELD |
				   SPCR_FIE_BIT | SPCR_ORIE_BIT |
				   SPCR_SPE_BIT,
				   MASK_RFIC_SPCR_BITS | PCH_ALL);

	/* Wait until the transfer completes; go to sleep after
				 initiating the transfer. */
	dev_dbg(&data->master->dev,
		"%s:waiting for transfer to get over\n", __func__);

	रुको_event_पूर्णांकerruptible(data->रुको, data->transfer_complete);

	/* clear all पूर्णांकerrupts */
	pch_spi_ग_लिखोreg(data->master, PCH_SPSR,
			 pch_spi_पढ़ोreg(data->master, PCH_SPSR));
	/* Disable पूर्णांकerrupts and SPI transfer */
	pch_spi_setclr_reg(data->master, PCH_SPCR, 0, PCH_ALL | SPCR_SPE_BIT);
	/* clear FIFO */
	pch_spi_clear_fअगरo(data->master);
पूर्ण

अटल व्योम pch_spi_copy_rx_data(काष्ठा pch_spi_data *data, पूर्णांक bpw)
अणु
	पूर्णांक j;
	u8 *rx_buf;
	u16 *rx_sbuf;

	/* copy Rx Data */
	अगर (!data->cur_trans->rx_buf)
		वापस;

	अगर (bpw == 8) अणु
		rx_buf = data->cur_trans->rx_buf;
		क्रम (j = 0; j < data->bpw_len; j++)
			*rx_buf++ = data->pkt_rx_buff[j] & 0xFF;
	पूर्ण अन्यथा अणु
		rx_sbuf = data->cur_trans->rx_buf;
		क्रम (j = 0; j < data->bpw_len; j++)
			*rx_sbuf++ = data->pkt_rx_buff[j];
	पूर्ण
पूर्ण

अटल व्योम pch_spi_copy_rx_data_क्रम_dma(काष्ठा pch_spi_data *data, पूर्णांक bpw)
अणु
	पूर्णांक j;
	u8 *rx_buf;
	u16 *rx_sbuf;
	स्थिर u8 *rx_dma_buf;
	स्थिर u16 *rx_dma_sbuf;

	/* copy Rx Data */
	अगर (!data->cur_trans->rx_buf)
		वापस;

	अगर (bpw == 8) अणु
		rx_buf = data->cur_trans->rx_buf;
		rx_dma_buf = data->dma.rx_buf_virt;
		क्रम (j = 0; j < data->bpw_len; j++)
			*rx_buf++ = *rx_dma_buf++ & 0xFF;
		data->cur_trans->rx_buf = rx_buf;
	पूर्ण अन्यथा अणु
		rx_sbuf = data->cur_trans->rx_buf;
		rx_dma_sbuf = data->dma.rx_buf_virt;
		क्रम (j = 0; j < data->bpw_len; j++)
			*rx_sbuf++ = *rx_dma_sbuf++;
		data->cur_trans->rx_buf = rx_sbuf;
	पूर्ण
पूर्ण

अटल पूर्णांक pch_spi_start_transfer(काष्ठा pch_spi_data *data)
अणु
	काष्ठा pch_spi_dma_ctrl *dma;
	अचिन्हित दीर्घ flags;
	पूर्णांक rtn;

	dma = &data->dma;

	spin_lock_irqsave(&data->lock, flags);

	/* disable पूर्णांकerrupts, SPI set enable */
	pch_spi_setclr_reg(data->master, PCH_SPCR, SPCR_SPE_BIT, PCH_ALL);

	spin_unlock_irqrestore(&data->lock, flags);

	/* Wait until the transfer completes; go to sleep after
				 initiating the transfer. */
	dev_dbg(&data->master->dev,
		"%s:waiting for transfer to get over\n", __func__);
	rtn = रुको_event_पूर्णांकerruptible_समयout(data->रुको,
					       data->transfer_complete,
					       msecs_to_jअगरfies(2 * HZ));
	अगर (!rtn)
		dev_err(&data->master->dev,
			"%s wait-event timeout\n", __func__);

	dma_sync_sg_क्रम_cpu(&data->master->dev, dma->sg_rx_p, dma->nent,
			    DMA_FROM_DEVICE);

	dma_sync_sg_क्रम_cpu(&data->master->dev, dma->sg_tx_p, dma->nent,
			    DMA_FROM_DEVICE);
	स_रखो(data->dma.tx_buf_virt, 0, PAGE_SIZE);

	async_tx_ack(dma->desc_rx);
	async_tx_ack(dma->desc_tx);
	kमुक्त(dma->sg_tx_p);
	kमुक्त(dma->sg_rx_p);

	spin_lock_irqsave(&data->lock, flags);

	/* clear fअगरo threshold, disable पूर्णांकerrupts, disable SPI transfer */
	pch_spi_setclr_reg(data->master, PCH_SPCR, 0,
			   MASK_RFIC_SPCR_BITS | MASK_TFIC_SPCR_BITS | PCH_ALL |
			   SPCR_SPE_BIT);
	/* clear all पूर्णांकerrupts */
	pch_spi_ग_लिखोreg(data->master, PCH_SPSR,
			 pch_spi_पढ़ोreg(data->master, PCH_SPSR));
	/* clear FIFO */
	pch_spi_clear_fअगरo(data->master);

	spin_unlock_irqrestore(&data->lock, flags);

	वापस rtn;
पूर्ण

अटल व्योम pch_dma_rx_complete(व्योम *arg)
अणु
	काष्ठा pch_spi_data *data = arg;

	/* transfer is completed;inक्रमm pch_spi_process_messages_dma */
	data->transfer_complete = true;
	wake_up_पूर्णांकerruptible(&data->रुको);
पूर्ण

अटल bool pch_spi_filter(काष्ठा dma_chan *chan, व्योम *slave)
अणु
	काष्ठा pch_dma_slave *param = slave;

	अगर ((chan->chan_id == param->chan_id) &&
	    (param->dma_dev == chan->device->dev)) अणु
		chan->निजी = param;
		वापस true;
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम pch_spi_request_dma(काष्ठा pch_spi_data *data, पूर्णांक bpw)
अणु
	dma_cap_mask_t mask;
	काष्ठा dma_chan *chan;
	काष्ठा pci_dev *dma_dev;
	काष्ठा pch_dma_slave *param;
	काष्ठा pch_spi_dma_ctrl *dma;
	अचिन्हित पूर्णांक width;

	अगर (bpw == 8)
		width = PCH_DMA_WIDTH_1_BYTE;
	अन्यथा
		width = PCH_DMA_WIDTH_2_BYTES;

	dma = &data->dma;
	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	/* Get DMA's dev inक्रमmation */
	dma_dev = pci_get_slot(data->board_dat->pdev->bus,
			PCI_DEVFN(PCI_SLOT(data->board_dat->pdev->devfn), 0));

	/* Set Tx DMA */
	param = &dma->param_tx;
	param->dma_dev = &dma_dev->dev;
	param->chan_id = data->ch * 2; /* Tx = 0, 2 */
	param->tx_reg = data->io_base_addr + PCH_SPDWR;
	param->width = width;
	chan = dma_request_channel(mask, pch_spi_filter, param);
	अगर (!chan) अणु
		dev_err(&data->master->dev,
			"ERROR: dma_request_channel FAILS(Tx)\n");
		data->use_dma = 0;
		वापस;
	पूर्ण
	dma->chan_tx = chan;

	/* Set Rx DMA */
	param = &dma->param_rx;
	param->dma_dev = &dma_dev->dev;
	param->chan_id = data->ch * 2 + 1; /* Rx = Tx + 1 */
	param->rx_reg = data->io_base_addr + PCH_SPDRR;
	param->width = width;
	chan = dma_request_channel(mask, pch_spi_filter, param);
	अगर (!chan) अणु
		dev_err(&data->master->dev,
			"ERROR: dma_request_channel FAILS(Rx)\n");
		dma_release_channel(dma->chan_tx);
		dma->chan_tx = शून्य;
		data->use_dma = 0;
		वापस;
	पूर्ण
	dma->chan_rx = chan;
पूर्ण

अटल व्योम pch_spi_release_dma(काष्ठा pch_spi_data *data)
अणु
	काष्ठा pch_spi_dma_ctrl *dma;

	dma = &data->dma;
	अगर (dma->chan_tx) अणु
		dma_release_channel(dma->chan_tx);
		dma->chan_tx = शून्य;
	पूर्ण
	अगर (dma->chan_rx) अणु
		dma_release_channel(dma->chan_rx);
		dma->chan_rx = शून्य;
	पूर्ण
पूर्ण

अटल व्योम pch_spi_handle_dma(काष्ठा pch_spi_data *data, पूर्णांक *bpw)
अणु
	स्थिर u8 *tx_buf;
	स्थिर u16 *tx_sbuf;
	u8 *tx_dma_buf;
	u16 *tx_dma_sbuf;
	काष्ठा scatterlist *sg;
	काष्ठा dma_async_tx_descriptor *desc_tx;
	काष्ठा dma_async_tx_descriptor *desc_rx;
	पूर्णांक num;
	पूर्णांक i;
	पूर्णांक size;
	पूर्णांक rem;
	पूर्णांक head;
	अचिन्हित दीर्घ flags;
	काष्ठा pch_spi_dma_ctrl *dma;

	dma = &data->dma;

	/* set baud rate अगर needed */
	अगर (data->cur_trans->speed_hz) अणु
		dev_dbg(&data->master->dev, "%s:setting baud rate\n", __func__);
		spin_lock_irqsave(&data->lock, flags);
		pch_spi_set_baud_rate(data->master, data->cur_trans->speed_hz);
		spin_unlock_irqrestore(&data->lock, flags);
	पूर्ण

	/* set bits per word अगर needed */
	अगर (data->cur_trans->bits_per_word &&
	    (data->current_msg->spi->bits_per_word !=
	     data->cur_trans->bits_per_word)) अणु
		dev_dbg(&data->master->dev, "%s:set bits per word\n", __func__);
		spin_lock_irqsave(&data->lock, flags);
		pch_spi_set_bits_per_word(data->master,
					  data->cur_trans->bits_per_word);
		spin_unlock_irqrestore(&data->lock, flags);
		*bpw = data->cur_trans->bits_per_word;
	पूर्ण अन्यथा अणु
		*bpw = data->current_msg->spi->bits_per_word;
	पूर्ण
	data->bpw_len = data->cur_trans->len / (*bpw / 8);

	अगर (data->bpw_len > PCH_BUF_SIZE) अणु
		data->bpw_len = PCH_BUF_SIZE;
		data->cur_trans->len -= PCH_BUF_SIZE;
	पूर्ण

	/* copy Tx Data */
	अगर (data->cur_trans->tx_buf != शून्य) अणु
		अगर (*bpw == 8) अणु
			tx_buf = data->cur_trans->tx_buf;
			tx_dma_buf = dma->tx_buf_virt;
			क्रम (i = 0; i < data->bpw_len; i++)
				*tx_dma_buf++ = *tx_buf++;
		पूर्ण अन्यथा अणु
			tx_sbuf = data->cur_trans->tx_buf;
			tx_dma_sbuf = dma->tx_buf_virt;
			क्रम (i = 0; i < data->bpw_len; i++)
				*tx_dma_sbuf++ = *tx_sbuf++;
		पूर्ण
	पूर्ण

	/* Calculate Rx parameter क्रम DMA transmitting */
	अगर (data->bpw_len > PCH_DMA_TRANS_SIZE) अणु
		अगर (data->bpw_len % PCH_DMA_TRANS_SIZE) अणु
			num = data->bpw_len / PCH_DMA_TRANS_SIZE + 1;
			rem = data->bpw_len % PCH_DMA_TRANS_SIZE;
		पूर्ण अन्यथा अणु
			num = data->bpw_len / PCH_DMA_TRANS_SIZE;
			rem = PCH_DMA_TRANS_SIZE;
		पूर्ण
		size = PCH_DMA_TRANS_SIZE;
	पूर्ण अन्यथा अणु
		num = 1;
		size = data->bpw_len;
		rem = data->bpw_len;
	पूर्ण
	dev_dbg(&data->master->dev, "%s num=%d size=%d rem=%d\n",
		__func__, num, size, rem);
	spin_lock_irqsave(&data->lock, flags);

	/* set receive fअगरo threshold and transmit fअगरo threshold */
	pch_spi_setclr_reg(data->master, PCH_SPCR,
			   ((size - 1) << SPCR_RFIC_FIELD) |
			   (PCH_TX_THOLD << SPCR_TFIC_FIELD),
			   MASK_RFIC_SPCR_BITS | MASK_TFIC_SPCR_BITS);

	spin_unlock_irqrestore(&data->lock, flags);

	/* RX */
	dma->sg_rx_p = kदो_स्मृति_array(num, माप(*dma->sg_rx_p), GFP_ATOMIC);
	अगर (!dma->sg_rx_p)
		वापस;

	sg_init_table(dma->sg_rx_p, num); /* Initialize SG table */
	/* offset, length setting */
	sg = dma->sg_rx_p;
	क्रम (i = 0; i < num; i++, sg++) अणु
		अगर (i == (num - 2)) अणु
			sg->offset = size * i;
			sg->offset = sg->offset * (*bpw / 8);
			sg_set_page(sg, virt_to_page(dma->rx_buf_virt), rem,
				    sg->offset);
			sg_dma_len(sg) = rem;
		पूर्ण अन्यथा अगर (i == (num - 1)) अणु
			sg->offset = size * (i - 1) + rem;
			sg->offset = sg->offset * (*bpw / 8);
			sg_set_page(sg, virt_to_page(dma->rx_buf_virt), size,
				    sg->offset);
			sg_dma_len(sg) = size;
		पूर्ण अन्यथा अणु
			sg->offset = size * i;
			sg->offset = sg->offset * (*bpw / 8);
			sg_set_page(sg, virt_to_page(dma->rx_buf_virt), size,
				    sg->offset);
			sg_dma_len(sg) = size;
		पूर्ण
		sg_dma_address(sg) = dma->rx_buf_dma + sg->offset;
	पूर्ण
	sg = dma->sg_rx_p;
	desc_rx = dmaengine_prep_slave_sg(dma->chan_rx, sg,
					num, DMA_DEV_TO_MEM,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc_rx) अणु
		dev_err(&data->master->dev,
			"%s:dmaengine_prep_slave_sg Failed\n", __func__);
		वापस;
	पूर्ण
	dma_sync_sg_क्रम_device(&data->master->dev, sg, num, DMA_FROM_DEVICE);
	desc_rx->callback = pch_dma_rx_complete;
	desc_rx->callback_param = data;
	dma->nent = num;
	dma->desc_rx = desc_rx;

	/* Calculate Tx parameter क्रम DMA transmitting */
	अगर (data->bpw_len > PCH_MAX_FIFO_DEPTH) अणु
		head = PCH_MAX_FIFO_DEPTH - PCH_DMA_TRANS_SIZE;
		अगर (data->bpw_len % PCH_DMA_TRANS_SIZE > 4) अणु
			num = data->bpw_len / PCH_DMA_TRANS_SIZE + 1;
			rem = data->bpw_len % PCH_DMA_TRANS_SIZE - head;
		पूर्ण अन्यथा अणु
			num = data->bpw_len / PCH_DMA_TRANS_SIZE;
			rem = data->bpw_len % PCH_DMA_TRANS_SIZE +
			      PCH_DMA_TRANS_SIZE - head;
		पूर्ण
		size = PCH_DMA_TRANS_SIZE;
	पूर्ण अन्यथा अणु
		num = 1;
		size = data->bpw_len;
		rem = data->bpw_len;
		head = 0;
	पूर्ण

	dma->sg_tx_p = kदो_स्मृति_array(num, माप(*dma->sg_tx_p), GFP_ATOMIC);
	अगर (!dma->sg_tx_p)
		वापस;

	sg_init_table(dma->sg_tx_p, num); /* Initialize SG table */
	/* offset, length setting */
	sg = dma->sg_tx_p;
	क्रम (i = 0; i < num; i++, sg++) अणु
		अगर (i == 0) अणु
			sg->offset = 0;
			sg_set_page(sg, virt_to_page(dma->tx_buf_virt), size + head,
				    sg->offset);
			sg_dma_len(sg) = size + head;
		पूर्ण अन्यथा अगर (i == (num - 1)) अणु
			sg->offset = head + size * i;
			sg->offset = sg->offset * (*bpw / 8);
			sg_set_page(sg, virt_to_page(dma->tx_buf_virt), rem,
				    sg->offset);
			sg_dma_len(sg) = rem;
		पूर्ण अन्यथा अणु
			sg->offset = head + size * i;
			sg->offset = sg->offset * (*bpw / 8);
			sg_set_page(sg, virt_to_page(dma->tx_buf_virt), size,
				    sg->offset);
			sg_dma_len(sg) = size;
		पूर्ण
		sg_dma_address(sg) = dma->tx_buf_dma + sg->offset;
	पूर्ण
	sg = dma->sg_tx_p;
	desc_tx = dmaengine_prep_slave_sg(dma->chan_tx,
					sg, num, DMA_MEM_TO_DEV,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc_tx) अणु
		dev_err(&data->master->dev,
			"%s:dmaengine_prep_slave_sg Failed\n", __func__);
		वापस;
	पूर्ण
	dma_sync_sg_क्रम_device(&data->master->dev, sg, num, DMA_TO_DEVICE);
	desc_tx->callback = शून्य;
	desc_tx->callback_param = data;
	dma->nent = num;
	dma->desc_tx = desc_tx;

	dev_dbg(&data->master->dev, "%s:Pulling down SSN low - writing 0x2 to SSNXCR\n", __func__);

	spin_lock_irqsave(&data->lock, flags);
	pch_spi_ग_लिखोreg(data->master, PCH_SSNXCR, SSN_LOW);
	desc_rx->tx_submit(desc_rx);
	desc_tx->tx_submit(desc_tx);
	spin_unlock_irqrestore(&data->lock, flags);

	/* reset transfer complete flag */
	data->transfer_complete = false;
पूर्ण

अटल व्योम pch_spi_process_messages(काष्ठा work_काष्ठा *pwork)
अणु
	काष्ठा spi_message *pmsg, *पंचांगp;
	काष्ठा pch_spi_data *data;
	पूर्णांक bpw;

	data = container_of(pwork, काष्ठा pch_spi_data, work);
	dev_dbg(&data->master->dev, "%s data initialized\n", __func__);

	spin_lock(&data->lock);
	/* check अगर suspend has been initiated;अगर yes flush queue */
	अगर (data->board_dat->suspend_sts || (data->status == STATUS_EXITING)) अणु
		dev_dbg(&data->master->dev,
			"%s suspend/remove initiated, flushing queue\n", __func__);
		list_क्रम_each_entry_safe(pmsg, पंचांगp, data->queue.next, queue) अणु
			pmsg->status = -EIO;

			अगर (pmsg->complete) अणु
				spin_unlock(&data->lock);
				pmsg->complete(pmsg->context);
				spin_lock(&data->lock);
			पूर्ण

			/* delete from queue */
			list_del_init(&pmsg->queue);
		पूर्ण

		spin_unlock(&data->lock);
		वापस;
	पूर्ण

	data->bcurrent_msg_processing = true;
	dev_dbg(&data->master->dev,
		"%s Set data->bcurrent_msg_processing= true\n", __func__);

	/* Get the message from the queue and delete it from there. */
	data->current_msg = list_entry(data->queue.next, काष्ठा spi_message,
					queue);

	list_del_init(&data->current_msg->queue);

	data->current_msg->status = 0;

	pch_spi_select_chip(data, data->current_msg->spi);

	spin_unlock(&data->lock);

	अगर (data->use_dma)
		pch_spi_request_dma(data,
				    data->current_msg->spi->bits_per_word);
	pch_spi_ग_लिखोreg(data->master, PCH_SSNXCR, SSN_NO_CONTROL);
	करो अणु
		पूर्णांक cnt;
		/* If we are alपढ़ोy processing a message get the next
		transfer काष्ठाure from the message otherwise retrieve
		the 1st transfer request from the message. */
		spin_lock(&data->lock);
		अगर (data->cur_trans == शून्य) अणु
			data->cur_trans =
				list_entry(data->current_msg->transfers.next,
					   काष्ठा spi_transfer, transfer_list);
			dev_dbg(&data->master->dev,
				"%s :Getting 1st transfer message\n",
				__func__);
		पूर्ण अन्यथा अणु
			data->cur_trans =
				list_entry(data->cur_trans->transfer_list.next,
					   काष्ठा spi_transfer, transfer_list);
			dev_dbg(&data->master->dev,
				"%s :Getting next transfer message\n",
				__func__);
		पूर्ण
		spin_unlock(&data->lock);

		अगर (!data->cur_trans->len)
			जाओ out;
		cnt = (data->cur_trans->len - 1) / PCH_BUF_SIZE + 1;
		data->save_total_len = data->cur_trans->len;
		अगर (data->use_dma) अणु
			पूर्णांक i;
			अक्षर *save_rx_buf = data->cur_trans->rx_buf;

			क्रम (i = 0; i < cnt; i++) अणु
				pch_spi_handle_dma(data, &bpw);
				अगर (!pch_spi_start_transfer(data)) अणु
					data->transfer_complete = true;
					data->current_msg->status = -EIO;
					data->current_msg->complete
						   (data->current_msg->context);
					data->bcurrent_msg_processing = false;
					data->current_msg = शून्य;
					data->cur_trans = शून्य;
					जाओ out;
				पूर्ण
				pch_spi_copy_rx_data_क्रम_dma(data, bpw);
			पूर्ण
			data->cur_trans->rx_buf = save_rx_buf;
		पूर्ण अन्यथा अणु
			pch_spi_set_tx(data, &bpw);
			pch_spi_set_ir(data);
			pch_spi_copy_rx_data(data, bpw);
			kमुक्त(data->pkt_rx_buff);
			data->pkt_rx_buff = शून्य;
			kमुक्त(data->pkt_tx_buff);
			data->pkt_tx_buff = शून्य;
		पूर्ण
		/* increment message count */
		data->cur_trans->len = data->save_total_len;
		data->current_msg->actual_length += data->cur_trans->len;

		dev_dbg(&data->master->dev,
			"%s:data->current_msg->actual_length=%d\n",
			__func__, data->current_msg->actual_length);

		spi_transfer_delay_exec(data->cur_trans);

		spin_lock(&data->lock);

		/* No more transfer in this message. */
		अगर ((data->cur_trans->transfer_list.next) ==
		    &(data->current_msg->transfers)) अणु
			pch_spi_nomore_transfer(data);
		पूर्ण

		spin_unlock(&data->lock);

	पूर्ण जबतक (data->cur_trans != शून्य);

out:
	pch_spi_ग_लिखोreg(data->master, PCH_SSNXCR, SSN_HIGH);
	अगर (data->use_dma)
		pch_spi_release_dma(data);
पूर्ण

अटल व्योम pch_spi_मुक्त_resources(काष्ठा pch_spi_board_data *board_dat,
				   काष्ठा pch_spi_data *data)
अणु
	dev_dbg(&board_dat->pdev->dev, "%s ENTRY\n", __func__);

	flush_work(&data->work);
पूर्ण

अटल पूर्णांक pch_spi_get_resources(काष्ठा pch_spi_board_data *board_dat,
				 काष्ठा pch_spi_data *data)
अणु
	dev_dbg(&board_dat->pdev->dev, "%s ENTRY\n", __func__);

	/* reset PCH SPI h/w */
	pch_spi_reset(data->master);
	dev_dbg(&board_dat->pdev->dev,
		"%s pch_spi_reset invoked successfully\n", __func__);

	dev_dbg(&board_dat->pdev->dev, "%s data->irq_reg_sts=true\n", __func__);

	वापस 0;
पूर्ण

अटल व्योम pch_मुक्त_dma_buf(काष्ठा pch_spi_board_data *board_dat,
			     काष्ठा pch_spi_data *data)
अणु
	काष्ठा pch_spi_dma_ctrl *dma;

	dma = &data->dma;
	अगर (dma->tx_buf_dma)
		dma_मुक्त_coherent(&board_dat->pdev->dev, PCH_BUF_SIZE,
				  dma->tx_buf_virt, dma->tx_buf_dma);
	अगर (dma->rx_buf_dma)
		dma_मुक्त_coherent(&board_dat->pdev->dev, PCH_BUF_SIZE,
				  dma->rx_buf_virt, dma->rx_buf_dma);
पूर्ण

अटल पूर्णांक pch_alloc_dma_buf(काष्ठा pch_spi_board_data *board_dat,
			      काष्ठा pch_spi_data *data)
अणु
	काष्ठा pch_spi_dma_ctrl *dma;
	पूर्णांक ret;

	dma = &data->dma;
	ret = 0;
	/* Get Consistent memory क्रम Tx DMA */
	dma->tx_buf_virt = dma_alloc_coherent(&board_dat->pdev->dev,
				PCH_BUF_SIZE, &dma->tx_buf_dma, GFP_KERNEL);
	अगर (!dma->tx_buf_virt)
		ret = -ENOMEM;

	/* Get Consistent memory क्रम Rx DMA */
	dma->rx_buf_virt = dma_alloc_coherent(&board_dat->pdev->dev,
				PCH_BUF_SIZE, &dma->rx_buf_dma, GFP_KERNEL);
	अगर (!dma->rx_buf_virt)
		ret = -ENOMEM;

	वापस ret;
पूर्ण

अटल पूर्णांक pch_spi_pd_probe(काष्ठा platक्रमm_device *plat_dev)
अणु
	पूर्णांक ret;
	काष्ठा spi_master *master;
	काष्ठा pch_spi_board_data *board_dat = dev_get_platdata(&plat_dev->dev);
	काष्ठा pch_spi_data *data;

	dev_dbg(&plat_dev->dev, "%s:debug\n", __func__);

	master = spi_alloc_master(&board_dat->pdev->dev,
				  माप(काष्ठा pch_spi_data));
	अगर (!master) अणु
		dev_err(&plat_dev->dev, "spi_alloc_master[%d] failed.\n",
			plat_dev->id);
		वापस -ENOMEM;
	पूर्ण

	data = spi_master_get_devdata(master);
	data->master = master;

	platक्रमm_set_drvdata(plat_dev, data);

	/* baseaddress + address offset) */
	data->io_base_addr = pci_resource_start(board_dat->pdev, 1) +
					 PCH_ADDRESS_SIZE * plat_dev->id;
	data->io_remap_addr = pci_iomap(board_dat->pdev, 1, 0);
	अगर (!data->io_remap_addr) अणु
		dev_err(&plat_dev->dev, "%s pci_iomap failed\n", __func__);
		ret = -ENOMEM;
		जाओ err_pci_iomap;
	पूर्ण
	data->io_remap_addr += PCH_ADDRESS_SIZE * plat_dev->id;

	dev_dbg(&plat_dev->dev, "[ch%d] remap_addr=%p\n",
		plat_dev->id, data->io_remap_addr);

	/* initialize members of SPI master */
	master->num_chipselect = PCH_MAX_CS;
	master->transfer = pch_spi_transfer;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_LSB_FIRST;
	master->bits_per_word_mask = SPI_BPW_MASK(8) | SPI_BPW_MASK(16);
	master->max_speed_hz = PCH_MAX_BAUDRATE;

	data->board_dat = board_dat;
	data->plat_dev = plat_dev;
	data->n_curnt_chip = 255;
	data->status = STATUS_RUNNING;
	data->ch = plat_dev->id;
	data->use_dma = use_dma;

	INIT_LIST_HEAD(&data->queue);
	spin_lock_init(&data->lock);
	INIT_WORK(&data->work, pch_spi_process_messages);
	init_रुकोqueue_head(&data->रुको);

	ret = pch_spi_get_resources(board_dat, data);
	अगर (ret) अणु
		dev_err(&plat_dev->dev, "%s fail(retval=%d)\n", __func__, ret);
		जाओ err_spi_get_resources;
	पूर्ण

	ret = request_irq(board_dat->pdev->irq, pch_spi_handler,
			  IRQF_SHARED, KBUILD_MODNAME, data);
	अगर (ret) अणु
		dev_err(&plat_dev->dev,
			"%s request_irq failed\n", __func__);
		जाओ err_request_irq;
	पूर्ण
	data->irq_reg_sts = true;

	pch_spi_set_master_mode(master);

	अगर (use_dma) अणु
		dev_info(&plat_dev->dev, "Use DMA for data transfers\n");
		ret = pch_alloc_dma_buf(board_dat, data);
		अगर (ret)
			जाओ err_spi_रेजिस्टर_master;
	पूर्ण

	ret = spi_रेजिस्टर_master(master);
	अगर (ret != 0) अणु
		dev_err(&plat_dev->dev,
			"%s spi_register_master FAILED\n", __func__);
		जाओ err_spi_रेजिस्टर_master;
	पूर्ण

	वापस 0;

err_spi_रेजिस्टर_master:
	pch_मुक्त_dma_buf(board_dat, data);
	मुक्त_irq(board_dat->pdev->irq, data);
err_request_irq:
	pch_spi_मुक्त_resources(board_dat, data);
err_spi_get_resources:
	pci_iounmap(board_dat->pdev, data->io_remap_addr);
err_pci_iomap:
	spi_master_put(master);

	वापस ret;
पूर्ण

अटल पूर्णांक pch_spi_pd_हटाओ(काष्ठा platक्रमm_device *plat_dev)
अणु
	काष्ठा pch_spi_board_data *board_dat = dev_get_platdata(&plat_dev->dev);
	काष्ठा pch_spi_data *data = platक्रमm_get_drvdata(plat_dev);
	पूर्णांक count;
	अचिन्हित दीर्घ flags;

	dev_dbg(&plat_dev->dev, "%s:[ch%d] irq=%d\n",
		__func__, plat_dev->id, board_dat->pdev->irq);

	अगर (use_dma)
		pch_मुक्त_dma_buf(board_dat, data);

	/* check क्रम any pending messages; no action is taken अगर the queue
	 * is still full; but at least we tried.  Unload anyway */
	count = 500;
	spin_lock_irqsave(&data->lock, flags);
	data->status = STATUS_EXITING;
	जबतक ((list_empty(&data->queue) == 0) && --count) अणु
		dev_dbg(&board_dat->pdev->dev, "%s :queue not empty\n",
			__func__);
		spin_unlock_irqrestore(&data->lock, flags);
		msleep(PCH_SLEEP_TIME);
		spin_lock_irqsave(&data->lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&data->lock, flags);

	pch_spi_मुक्त_resources(board_dat, data);
	/* disable पूर्णांकerrupts & मुक्त IRQ */
	अगर (data->irq_reg_sts) अणु
		/* disable पूर्णांकerrupts */
		pch_spi_setclr_reg(data->master, PCH_SPCR, 0, PCH_ALL);
		data->irq_reg_sts = false;
		मुक्त_irq(board_dat->pdev->irq, data);
	पूर्ण

	pci_iounmap(board_dat->pdev, data->io_remap_addr);
	spi_unरेजिस्टर_master(data->master);

	वापस 0;
पूर्ण
#अगर_घोषित CONFIG_PM
अटल पूर्णांक pch_spi_pd_suspend(काष्ठा platक्रमm_device *pd_dev,
			      pm_message_t state)
अणु
	u8 count;
	काष्ठा pch_spi_board_data *board_dat = dev_get_platdata(&pd_dev->dev);
	काष्ठा pch_spi_data *data = platक्रमm_get_drvdata(pd_dev);

	dev_dbg(&pd_dev->dev, "%s ENTRY\n", __func__);

	अगर (!board_dat) अणु
		dev_err(&pd_dev->dev,
			"%s pci_get_drvdata returned NULL\n", __func__);
		वापस -EFAULT;
	पूर्ण

	/* check अगर the current message is processed:
	   Only after thats करोne the transfer will be suspended */
	count = 255;
	जबतक ((--count) > 0) अणु
		अगर (!(data->bcurrent_msg_processing))
			अवरोध;
		msleep(PCH_SLEEP_TIME);
	पूर्ण

	/* Free IRQ */
	अगर (data->irq_reg_sts) अणु
		/* disable all पूर्णांकerrupts */
		pch_spi_setclr_reg(data->master, PCH_SPCR, 0, PCH_ALL);
		pch_spi_reset(data->master);
		मुक्त_irq(board_dat->pdev->irq, data);

		data->irq_reg_sts = false;
		dev_dbg(&pd_dev->dev,
			"%s free_irq invoked successfully.\n", __func__);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pch_spi_pd_resume(काष्ठा platक्रमm_device *pd_dev)
अणु
	काष्ठा pch_spi_board_data *board_dat = dev_get_platdata(&pd_dev->dev);
	काष्ठा pch_spi_data *data = platक्रमm_get_drvdata(pd_dev);
	पूर्णांक retval;

	अगर (!board_dat) अणु
		dev_err(&pd_dev->dev,
			"%s pci_get_drvdata returned NULL\n", __func__);
		वापस -EFAULT;
	पूर्ण

	अगर (!data->irq_reg_sts) अणु
		/* रेजिस्टर IRQ */
		retval = request_irq(board_dat->pdev->irq, pch_spi_handler,
				     IRQF_SHARED, KBUILD_MODNAME, data);
		अगर (retval < 0) अणु
			dev_err(&pd_dev->dev,
				"%s request_irq failed\n", __func__);
			वापस retval;
		पूर्ण

		/* reset PCH SPI h/w */
		pch_spi_reset(data->master);
		pch_spi_set_master_mode(data->master);
		data->irq_reg_sts = true;
	पूर्ण
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा pch_spi_pd_suspend शून्य
#घोषणा pch_spi_pd_resume शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver pch_spi_pd_driver = अणु
	.driver = अणु
		.name = "pch-spi",
	पूर्ण,
	.probe = pch_spi_pd_probe,
	.हटाओ = pch_spi_pd_हटाओ,
	.suspend = pch_spi_pd_suspend,
	.resume = pch_spi_pd_resume
पूर्ण;

अटल पूर्णांक pch_spi_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा pch_spi_board_data *board_dat;
	काष्ठा platक्रमm_device *pd_dev = शून्य;
	पूर्णांक retval;
	पूर्णांक i;
	काष्ठा pch_pd_dev_save *pd_dev_save;

	pd_dev_save = kzalloc(माप(*pd_dev_save), GFP_KERNEL);
	अगर (!pd_dev_save)
		वापस -ENOMEM;

	board_dat = kzalloc(माप(*board_dat), GFP_KERNEL);
	अगर (!board_dat) अणु
		retval = -ENOMEM;
		जाओ err_no_mem;
	पूर्ण

	retval = pci_request_regions(pdev, KBUILD_MODNAME);
	अगर (retval) अणु
		dev_err(&pdev->dev, "%s request_region failed\n", __func__);
		जाओ pci_request_regions;
	पूर्ण

	board_dat->pdev = pdev;
	board_dat->num = id->driver_data;
	pd_dev_save->num = id->driver_data;
	pd_dev_save->board_dat = board_dat;

	retval = pci_enable_device(pdev);
	अगर (retval) अणु
		dev_err(&pdev->dev, "%s pci_enable_device failed\n", __func__);
		जाओ pci_enable_device;
	पूर्ण

	क्रम (i = 0; i < board_dat->num; i++) अणु
		pd_dev = platक्रमm_device_alloc("pch-spi", i);
		अगर (!pd_dev) अणु
			dev_err(&pdev->dev, "platform_device_alloc failed\n");
			retval = -ENOMEM;
			जाओ err_platक्रमm_device;
		पूर्ण
		pd_dev_save->pd_save[i] = pd_dev;
		pd_dev->dev.parent = &pdev->dev;

		retval = platक्रमm_device_add_data(pd_dev, board_dat,
						  माप(*board_dat));
		अगर (retval) अणु
			dev_err(&pdev->dev,
				"platform_device_add_data failed\n");
			platक्रमm_device_put(pd_dev);
			जाओ err_platक्रमm_device;
		पूर्ण

		retval = platक्रमm_device_add(pd_dev);
		अगर (retval) अणु
			dev_err(&pdev->dev, "platform_device_add failed\n");
			platक्रमm_device_put(pd_dev);
			जाओ err_platक्रमm_device;
		पूर्ण
	पूर्ण

	pci_set_drvdata(pdev, pd_dev_save);

	वापस 0;

err_platक्रमm_device:
	जबतक (--i >= 0)
		platक्रमm_device_unरेजिस्टर(pd_dev_save->pd_save[i]);
	pci_disable_device(pdev);
pci_enable_device:
	pci_release_regions(pdev);
pci_request_regions:
	kमुक्त(board_dat);
err_no_mem:
	kमुक्त(pd_dev_save);

	वापस retval;
पूर्ण

अटल व्योम pch_spi_हटाओ(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;
	काष्ठा pch_pd_dev_save *pd_dev_save = pci_get_drvdata(pdev);

	dev_dbg(&pdev->dev, "%s ENTRY:pdev=%p\n", __func__, pdev);

	क्रम (i = 0; i < pd_dev_save->num; i++)
		platक्रमm_device_unरेजिस्टर(pd_dev_save->pd_save[i]);

	pci_disable_device(pdev);
	pci_release_regions(pdev);
	kमुक्त(pd_dev_save->board_dat);
	kमुक्त(pd_dev_save);
पूर्ण

अटल पूर्णांक __maybe_unused pch_spi_suspend(काष्ठा device *dev)
अणु
	काष्ठा pch_pd_dev_save *pd_dev_save = dev_get_drvdata(dev);

	dev_dbg(dev, "%s ENTRY\n", __func__);

	pd_dev_save->board_dat->suspend_sts = true;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pch_spi_resume(काष्ठा device *dev)
अणु
	काष्ठा pch_pd_dev_save *pd_dev_save = dev_get_drvdata(dev);

	dev_dbg(dev, "%s ENTRY\n", __func__);

	/* set suspend status to false */
	pd_dev_save->board_dat->suspend_sts = false;

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(pch_spi_pm_ops, pch_spi_suspend, pch_spi_resume);

अटल काष्ठा pci_driver pch_spi_pcidev_driver = अणु
	.name = "pch_spi",
	.id_table = pch_spi_pcidev_id,
	.probe = pch_spi_probe,
	.हटाओ = pch_spi_हटाओ,
	.driver.pm = &pch_spi_pm_ops,
पूर्ण;

अटल पूर्णांक __init pch_spi_init(व्योम)
अणु
	पूर्णांक ret;
	ret = platक्रमm_driver_रेजिस्टर(&pch_spi_pd_driver);
	अगर (ret)
		वापस ret;

	ret = pci_रेजिस्टर_driver(&pch_spi_pcidev_driver);
	अगर (ret) अणु
		platक्रमm_driver_unरेजिस्टर(&pch_spi_pd_driver);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
module_init(pch_spi_init);

अटल व्योम __निकास pch_spi_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&pch_spi_pcidev_driver);
	platक्रमm_driver_unरेजिस्टर(&pch_spi_pd_driver);
पूर्ण
module_निकास(pch_spi_निकास);

module_param(use_dma, पूर्णांक, 0644);
MODULE_PARM_DESC(use_dma,
		 "to use DMA for data transfers pass 1 else 0; default 1");

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Intel EG20T PCH/LAPIS Semiconductor ML7xxx IOH SPI Driver");
MODULE_DEVICE_TABLE(pci, pch_spi_pcidev_id);

