<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * netup_unidvb_spi.c
 *
 * Internal SPI driver क्रम NetUP Universal Dual DVB-CI
 *
 * Copyright (C) 2014 NetUP Inc.
 * Copyright (C) 2014 Sergey Kozlov <serjk@netup.ru>
 * Copyright (C) 2014 Abylay Ospan <aospan@netup.ru>
 */

#समावेश "netup_unidvb.h"
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/flash.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <mtd/mtd-abi.h>

#घोषणा NETUP_SPI_CTRL_IRQ	0x1000
#घोषणा NETUP_SPI_CTRL_IMASK	0x2000
#घोषणा NETUP_SPI_CTRL_START	0x8000
#घोषणा NETUP_SPI_CTRL_LAST_CS	0x4000

#घोषणा NETUP_SPI_TIMEOUT	6000

क्रमागत netup_spi_state अणु
	SPI_STATE_START,
	SPI_STATE_DONE,
पूर्ण;

काष्ठा netup_spi_regs अणु
	__u8	data[1024];
	__le16	control_stat;
	__le16	घड़ी_भागider;
पूर्ण __packed __aligned(1);

काष्ठा netup_spi अणु
	काष्ठा device			*dev;
	काष्ठा spi_master		*master;
	काष्ठा netup_spi_regs __iomem	*regs;
	u8 __iomem			*mmio;
	spinlock_t			lock;
	रुको_queue_head_t		रुकोq;
	क्रमागत netup_spi_state		state;
पूर्ण;

अटल अक्षर netup_spi_name[64] = "fpga";

अटल काष्ठा mtd_partition netup_spi_flash_partitions = अणु
	.name = netup_spi_name,
	.size = 0x1000000, /* 16MB */
	.offset = 0,
	.mask_flags = MTD_CAP_ROM
पूर्ण;

अटल काष्ठा flash_platक्रमm_data spi_flash_data = अणु
	.name = "netup0_m25p128",
	.parts = &netup_spi_flash_partitions,
	.nr_parts = 1,
पूर्ण;

अटल काष्ठा spi_board_info netup_spi_board = अणु
	.modalias = "m25p128",
	.max_speed_hz = 11000000,
	.chip_select = 0,
	.mode = SPI_MODE_0,
	.platक्रमm_data = &spi_flash_data,
पूर्ण;

irqवापस_t netup_spi_पूर्णांकerrupt(काष्ठा netup_spi *spi)
अणु
	u16 reg;
	अचिन्हित दीर्घ flags;

	अगर (!spi)
		वापस IRQ_NONE;

	spin_lock_irqsave(&spi->lock, flags);
	reg = पढ़ोw(&spi->regs->control_stat);
	अगर (!(reg & NETUP_SPI_CTRL_IRQ)) अणु
		spin_unlock_irqrestore(&spi->lock, flags);
		dev_dbg(&spi->master->dev,
			"%s(): not mine interrupt\n", __func__);
		वापस IRQ_NONE;
	पूर्ण
	ग_लिखोw(reg | NETUP_SPI_CTRL_IRQ, &spi->regs->control_stat);
	reg = पढ़ोw(&spi->regs->control_stat);
	ग_लिखोw(reg & ~NETUP_SPI_CTRL_IMASK, &spi->regs->control_stat);
	spi->state = SPI_STATE_DONE;
	wake_up(&spi->रुकोq);
	spin_unlock_irqrestore(&spi->lock, flags);
	dev_dbg(&spi->master->dev,
		"%s(): SPI interrupt handled\n", __func__);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक netup_spi_transfer(काष्ठा spi_master *master,
			      काष्ठा spi_message *msg)
अणु
	काष्ठा netup_spi *spi = spi_master_get_devdata(master);
	काष्ठा spi_transfer *t;
	पूर्णांक result = 0;
	u32 tr_size;

	/* reset CS */
	ग_लिखोw(NETUP_SPI_CTRL_LAST_CS, &spi->regs->control_stat);
	ग_लिखोw(0, &spi->regs->control_stat);
	list_क्रम_each_entry(t, &msg->transfers, transfer_list) अणु
		tr_size = t->len;
		जबतक (tr_size) अणु
			u32 frag_offset = t->len - tr_size;
			u32 frag_size = (tr_size > माप(spi->regs->data)) ?
					माप(spi->regs->data) : tr_size;
			पूर्णांक frag_last = 0;

			अगर (list_is_last(&t->transfer_list,
					&msg->transfers) &&
					frag_offset + frag_size == t->len) अणु
				frag_last = 1;
			पूर्ण
			अगर (t->tx_buf) अणु
				स_नकल_toio(spi->regs->data,
					t->tx_buf + frag_offset,
					frag_size);
			पूर्ण अन्यथा अणु
				स_रखो_io(spi->regs->data,
					0, frag_size);
			पूर्ण
			spi->state = SPI_STATE_START;
			ग_लिखोw((frag_size & 0x3ff) |
				NETUP_SPI_CTRL_IMASK |
				NETUP_SPI_CTRL_START |
				(frag_last ? NETUP_SPI_CTRL_LAST_CS : 0),
				&spi->regs->control_stat);
			dev_dbg(&spi->master->dev,
				"%s(): control_stat 0x%04x\n",
				__func__, पढ़ोw(&spi->regs->control_stat));
			रुको_event_समयout(spi->रुकोq,
				spi->state != SPI_STATE_START,
				msecs_to_jअगरfies(NETUP_SPI_TIMEOUT));
			अगर (spi->state == SPI_STATE_DONE) अणु
				अगर (t->rx_buf) अणु
					स_नकल_fromio(t->rx_buf + frag_offset,
						spi->regs->data, frag_size);
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (spi->state == SPI_STATE_START) अणु
					dev_dbg(&spi->master->dev,
						"%s(): transfer timeout\n",
						__func__);
				पूर्ण अन्यथा अणु
					dev_dbg(&spi->master->dev,
						"%s(): invalid state %d\n",
						__func__, spi->state);
				पूर्ण
				result = -EIO;
				जाओ करोne;
			पूर्ण
			tr_size -= frag_size;
			msg->actual_length += frag_size;
		पूर्ण
	पूर्ण
करोne:
	msg->status = result;
	spi_finalize_current_message(master);
	वापस result;
पूर्ण

अटल पूर्णांक netup_spi_setup(काष्ठा spi_device *spi)
अणु
	वापस 0;
पूर्ण

पूर्णांक netup_spi_init(काष्ठा netup_unidvb_dev *ndev)
अणु
	काष्ठा spi_master *master;
	काष्ठा netup_spi *nspi;

	master = devm_spi_alloc_master(&ndev->pci_dev->dev,
		माप(काष्ठा netup_spi));
	अगर (!master) अणु
		dev_err(&ndev->pci_dev->dev,
			"%s(): unable to alloc SPI master\n", __func__);
		वापस -EINVAL;
	पूर्ण
	nspi = spi_master_get_devdata(master);
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_LSB_FIRST;
	master->bus_num = -1;
	master->num_chipselect = 1;
	master->transfer_one_message = netup_spi_transfer;
	master->setup = netup_spi_setup;
	spin_lock_init(&nspi->lock);
	init_रुकोqueue_head(&nspi->रुकोq);
	nspi->master = master;
	nspi->regs = (काष्ठा netup_spi_regs __iomem *)(ndev->bmmio0 + 0x4000);
	ग_लिखोw(2, &nspi->regs->घड़ी_भागider);
	ग_लिखोw(NETUP_UNIDVB_IRQ_SPI, ndev->bmmio0 + REG_IMASK_SET);
	ndev->spi = nspi;
	अगर (spi_रेजिस्टर_master(master)) अणु
		ndev->spi = शून्य;
		dev_err(&ndev->pci_dev->dev,
			"%s(): unable to register SPI bus\n", __func__);
		वापस -EINVAL;
	पूर्ण
	snम_लिखो(netup_spi_name,
		माप(netup_spi_name),
		"fpga_%02x:%02x.%01x",
		ndev->pci_bus,
		ndev->pci_slot,
		ndev->pci_func);
	अगर (!spi_new_device(master, &netup_spi_board)) अणु
		spi_unरेजिस्टर_master(master);
		ndev->spi = शून्य;
		dev_err(&ndev->pci_dev->dev,
			"%s(): unable to create SPI device\n", __func__);
		वापस -EINVAL;
	पूर्ण
	dev_dbg(&ndev->pci_dev->dev, "%s(): SPI init OK\n", __func__);
	वापस 0;
पूर्ण

व्योम netup_spi_release(काष्ठा netup_unidvb_dev *ndev)
अणु
	u16 reg;
	अचिन्हित दीर्घ flags;
	काष्ठा netup_spi *spi = ndev->spi;

	अगर (!spi)
		वापस;

	spi_unरेजिस्टर_master(spi->master);
	spin_lock_irqsave(&spi->lock, flags);
	reg = पढ़ोw(&spi->regs->control_stat);
	ग_लिखोw(reg | NETUP_SPI_CTRL_IRQ, &spi->regs->control_stat);
	reg = पढ़ोw(&spi->regs->control_stat);
	ग_लिखोw(reg & ~NETUP_SPI_CTRL_IMASK, &spi->regs->control_stat);
	spin_unlock_irqrestore(&spi->lock, flags);
	ndev->spi = शून्य;
पूर्ण


