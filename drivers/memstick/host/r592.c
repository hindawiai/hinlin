<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 - Maxim Levitsky
 * driver क्रम Ricoh memstick पढ़ोers
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched.h>
#समावेश <linux/highस्मृति.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/swab.h>
#समावेश "r592.h"

अटल bool r592_enable_dma = 1;
अटल पूर्णांक debug;

अटल स्थिर अक्षर *tpc_names[] = अणु
	"MS_TPC_READ_MG_STATUS",
	"MS_TPC_READ_LONG_DATA",
	"MS_TPC_READ_SHORT_DATA",
	"MS_TPC_READ_REG",
	"MS_TPC_READ_QUAD_DATA",
	"INVALID",
	"MS_TPC_GET_INT",
	"MS_TPC_SET_RW_REG_ADRS",
	"MS_TPC_EX_SET_CMD",
	"MS_TPC_WRITE_QUAD_DATA",
	"MS_TPC_WRITE_REG",
	"MS_TPC_WRITE_SHORT_DATA",
	"MS_TPC_WRITE_LONG_DATA",
	"MS_TPC_SET_CMD",
पूर्ण;

/**
 * memstick_debug_get_tpc_name - debug helper that वापसs string क्रम
 * a TPC number
 */
स्थिर अक्षर *memstick_debug_get_tpc_name(पूर्णांक tpc)
अणु
	वापस tpc_names[tpc-1];
पूर्ण
EXPORT_SYMBOL(memstick_debug_get_tpc_name);


/* Read a रेजिस्टर*/
अटल अंतरभूत u32 r592_पढ़ो_reg(काष्ठा r592_device *dev, पूर्णांक address)
अणु
	u32 value = पढ़ोl(dev->mmio + address);
	dbg_reg("reg #%02d == 0x%08x", address, value);
	वापस value;
पूर्ण

/* Write a रेजिस्टर */
अटल अंतरभूत व्योम r592_ग_लिखो_reg(काष्ठा r592_device *dev,
							पूर्णांक address, u32 value)
अणु
	dbg_reg("reg #%02d <- 0x%08x", address, value);
	ग_लिखोl(value, dev->mmio + address);
पूर्ण

/* Reads a big endian DWORD रेजिस्टर */
अटल अंतरभूत u32 r592_पढ़ो_reg_raw_be(काष्ठा r592_device *dev, पूर्णांक address)
अणु
	u32 value = __raw_पढ़ोl(dev->mmio + address);
	dbg_reg("reg #%02d == 0x%08x", address, value);
	वापस be32_to_cpu(value);
पूर्ण

/* Writes a big endian DWORD रेजिस्टर */
अटल अंतरभूत व्योम r592_ग_लिखो_reg_raw_be(काष्ठा r592_device *dev,
							पूर्णांक address, u32 value)
अणु
	dbg_reg("reg #%02d <- 0x%08x", address, value);
	__raw_ग_लिखोl(cpu_to_be32(value), dev->mmio + address);
पूर्ण

/* Set specअगरic bits in a रेजिस्टर (little endian) */
अटल अंतरभूत व्योम r592_set_reg_mask(काष्ठा r592_device *dev,
							पूर्णांक address, u32 mask)
अणु
	u32 reg = पढ़ोl(dev->mmio + address);
	dbg_reg("reg #%02d |= 0x%08x (old =0x%08x)", address, mask, reg);
	ग_लिखोl(reg | mask , dev->mmio + address);
पूर्ण

/* Clear specअगरic bits in a रेजिस्टर (little endian) */
अटल अंतरभूत व्योम r592_clear_reg_mask(काष्ठा r592_device *dev,
						पूर्णांक address, u32 mask)
अणु
	u32 reg = पढ़ोl(dev->mmio + address);
	dbg_reg("reg #%02d &= 0x%08x (old = 0x%08x, mask = 0x%08x)",
						address, ~mask, reg, mask);
	ग_लिखोl(reg & ~mask, dev->mmio + address);
पूर्ण


/* Wait क्रम status bits जबतक checking क्रम errors */
अटल पूर्णांक r592_रुको_status(काष्ठा r592_device *dev, u32 mask, u32 wanted_mask)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1000);
	u32 reg = r592_पढ़ो_reg(dev, R592_STATUS);

	अगर ((reg & mask) == wanted_mask)
		वापस 0;

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु

		reg = r592_पढ़ो_reg(dev, R592_STATUS);

		अगर ((reg & mask) == wanted_mask)
			वापस 0;

		अगर (reg & (R592_STATUS_SEND_ERR | R592_STATUS_RECV_ERR))
			वापस -EIO;

		cpu_relax();
	पूर्ण
	वापस -ETIME;
पूर्ण


/* Enable/disable device */
अटल पूर्णांक r592_enable_device(काष्ठा r592_device *dev, bool enable)
अणु
	dbg("%sabling the device", enable ? "en" : "dis");

	अगर (enable) अणु

		/* Power up the card */
		r592_ग_लिखो_reg(dev, R592_POWER, R592_POWER_0 | R592_POWER_1);

		/* Perक्रमm a reset */
		r592_set_reg_mask(dev, R592_IO, R592_IO_RESET);

		msleep(100);
	पूर्ण अन्यथा
		/* Power करोwn the card */
		r592_ग_लिखो_reg(dev, R592_POWER, 0);

	वापस 0;
पूर्ण

/* Set serial/parallel mode */
अटल पूर्णांक r592_set_mode(काष्ठा r592_device *dev, bool parallel_mode)
अणु
	अगर (!parallel_mode) अणु
		dbg("switching to serial mode");

		/* Set serial mode */
		r592_ग_लिखो_reg(dev, R592_IO_MODE, R592_IO_MODE_SERIAL);

		r592_clear_reg_mask(dev, R592_POWER, R592_POWER_20);

	पूर्ण अन्यथा अणु
		dbg("switching to parallel mode");

		/* This setting should be set _beक्रमe_ चयन TPC */
		r592_set_reg_mask(dev, R592_POWER, R592_POWER_20);

		r592_clear_reg_mask(dev, R592_IO,
			R592_IO_SERIAL1 | R592_IO_SERIAL2);

		/* Set the parallel mode now */
		r592_ग_लिखो_reg(dev, R592_IO_MODE, R592_IO_MODE_PARALLEL);
	पूर्ण

	dev->parallel_mode = parallel_mode;
	वापस 0;
पूर्ण

/* Perक्रमm a controller reset without घातering करोwn the card */
अटल व्योम r592_host_reset(काष्ठा r592_device *dev)
अणु
	r592_set_reg_mask(dev, R592_IO, R592_IO_RESET);
	msleep(100);
	r592_set_mode(dev, dev->parallel_mode);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/* Disable all hardware पूर्णांकerrupts */
अटल व्योम r592_clear_पूर्णांकerrupts(काष्ठा r592_device *dev)
अणु
	/* Disable & ACK all पूर्णांकerrupts */
	r592_clear_reg_mask(dev, R592_REG_MSC, IRQ_ALL_ACK_MASK);
	r592_clear_reg_mask(dev, R592_REG_MSC, IRQ_ALL_EN_MASK);
पूर्ण
#पूर्ण_अगर

/* Tests अगर there is an CRC error */
अटल पूर्णांक r592_test_io_error(काष्ठा r592_device *dev)
अणु
	अगर (!(r592_पढ़ो_reg(dev, R592_STATUS) &
		(R592_STATUS_SEND_ERR | R592_STATUS_RECV_ERR)))
		वापस 0;

	वापस -EIO;
पूर्ण

/* Ensure that FIFO is पढ़ोy क्रम use */
अटल पूर्णांक r592_test_fअगरo_empty(काष्ठा r592_device *dev)
अणु
	अगर (r592_पढ़ो_reg(dev, R592_REG_MSC) & R592_REG_MSC_FIFO_EMPTY)
		वापस 0;

	dbg("FIFO not ready, trying to reset the device");
	r592_host_reset(dev);

	अगर (r592_पढ़ो_reg(dev, R592_REG_MSC) & R592_REG_MSC_FIFO_EMPTY)
		वापस 0;

	message("FIFO still not ready, giving up");
	वापस -EIO;
पूर्ण

/* Activates the DMA transfer from to FIFO */
अटल व्योम r592_start_dma(काष्ठा r592_device *dev, bool is_ग_लिखो)
अणु
	अचिन्हित दीर्घ flags;
	u32 reg;
	spin_lock_irqsave(&dev->irq_lock, flags);

	/* Ack पूर्णांकerrupts (just in हाल) + enable them */
	r592_clear_reg_mask(dev, R592_REG_MSC, DMA_IRQ_ACK_MASK);
	r592_set_reg_mask(dev, R592_REG_MSC, DMA_IRQ_EN_MASK);

	/* Set DMA address */
	r592_ग_लिखो_reg(dev, R592_FIFO_DMA, sg_dma_address(&dev->req->sg));

	/* Enable the DMA */
	reg = r592_पढ़ो_reg(dev, R592_FIFO_DMA_SETTINGS);
	reg |= R592_FIFO_DMA_SETTINGS_EN;

	अगर (!is_ग_लिखो)
		reg |= R592_FIFO_DMA_SETTINGS_सूची;
	अन्यथा
		reg &= ~R592_FIFO_DMA_SETTINGS_सूची;
	r592_ग_लिखो_reg(dev, R592_FIFO_DMA_SETTINGS, reg);

	spin_unlock_irqrestore(&dev->irq_lock, flags);
पूर्ण

/* Cleanups DMA related settings */
अटल व्योम r592_stop_dma(काष्ठा r592_device *dev, पूर्णांक error)
अणु
	r592_clear_reg_mask(dev, R592_FIFO_DMA_SETTINGS,
		R592_FIFO_DMA_SETTINGS_EN);

	/* This is only a precation */
	r592_ग_लिखो_reg(dev, R592_FIFO_DMA,
			dev->dummy_dma_page_physical_address);

	r592_clear_reg_mask(dev, R592_REG_MSC, DMA_IRQ_EN_MASK);
	r592_clear_reg_mask(dev, R592_REG_MSC, DMA_IRQ_ACK_MASK);
	dev->dma_error = error;
पूर्ण

/* Test अगर hardware supports DMA */
अटल व्योम r592_check_dma(काष्ठा r592_device *dev)
अणु
	dev->dma_capable = r592_enable_dma &&
		(r592_पढ़ो_reg(dev, R592_FIFO_DMA_SETTINGS) &
			R592_FIFO_DMA_SETTINGS_CAP);
पूर्ण

/* Transfers fअगरo contents in/out using DMA */
अटल पूर्णांक r592_transfer_fअगरo_dma(काष्ठा r592_device *dev)
अणु
	पूर्णांक len, sg_count;
	bool is_ग_लिखो;

	अगर (!dev->dma_capable || !dev->req->दीर्घ_data)
		वापस -EINVAL;

	len = dev->req->sg.length;
	is_ग_लिखो = dev->req->data_dir == WRITE;

	अगर (len != R592_LFIFO_SIZE)
		वापस -EINVAL;

	dbg_verbose("doing dma transfer");

	dev->dma_error = 0;
	reinit_completion(&dev->dma_करोne);

	/* TODO: hidden assumption about nenth beeing always 1 */
	sg_count = dma_map_sg(&dev->pci_dev->dev, &dev->req->sg, 1, is_ग_लिखो ?
		PCI_DMA_TODEVICE : PCI_DMA_FROMDEVICE);

	अगर (sg_count != 1 || sg_dma_len(&dev->req->sg) < R592_LFIFO_SIZE) अणु
		message("problem in dma_map_sg");
		वापस -EIO;
	पूर्ण

	r592_start_dma(dev, is_ग_लिखो);

	/* Wait क्रम DMA completion */
	अगर (!रुको_क्रम_completion_समयout(
			&dev->dma_करोne, msecs_to_jअगरfies(1000))) अणु
		message("DMA timeout");
		r592_stop_dma(dev, -ETIMEDOUT);
	पूर्ण

	dma_unmap_sg(&dev->pci_dev->dev, &dev->req->sg, 1, is_ग_लिखो ?
		PCI_DMA_TODEVICE : PCI_DMA_FROMDEVICE);


	वापस dev->dma_error;
पूर्ण

/*
 * Writes the FIFO in 4 byte chunks.
 * If length isn't 4 byte aligned, rest of the data अगर put to a fअगरo
 * to be written later
 * Use r592_flush_fअगरo_ग_लिखो to flush that fअगरo when writing क्रम the
 * last समय
 */
अटल व्योम r592_ग_लिखो_fअगरo_pio(काष्ठा r592_device *dev,
					अचिन्हित अक्षर *buffer, पूर्णांक len)
अणु
	/* flush spill from क्रमmer ग_लिखो */
	अगर (!kfअगरo_is_empty(&dev->pio_fअगरo)) अणु

		u8 पंचांगp[4] = अणु0पूर्ण;
		पूर्णांक copy_len = kfअगरo_in(&dev->pio_fअगरo, buffer, len);

		अगर (!kfअगरo_is_full(&dev->pio_fअगरo))
			वापस;
		len -= copy_len;
		buffer += copy_len;

		copy_len = kfअगरo_out(&dev->pio_fअगरo, पंचांगp, 4);
		WARN_ON(copy_len != 4);
		r592_ग_लिखो_reg_raw_be(dev, R592_FIFO_PIO, *(u32 *)पंचांगp);
	पूर्ण

	WARN_ON(!kfअगरo_is_empty(&dev->pio_fअगरo));

	/* ग_लिखो full dwords */
	जबतक (len >= 4) अणु
		r592_ग_लिखो_reg_raw_be(dev, R592_FIFO_PIO, *(u32 *)buffer);
		buffer += 4;
		len -= 4;
	पूर्ण

	/* put reमुख्यing bytes to the spill */
	अगर (len)
		kfअगरo_in(&dev->pio_fअगरo, buffer, len);
पूर्ण

/* Flushes the temporary FIFO used to make aligned DWORD ग_लिखोs */
अटल व्योम r592_flush_fअगरo_ग_लिखो(काष्ठा r592_device *dev)
अणु
	पूर्णांक ret;
	u8 buffer[4] = अणु 0 पूर्ण;

	अगर (kfअगरo_is_empty(&dev->pio_fअगरo))
		वापस;

	ret = kfअगरo_out(&dev->pio_fअगरo, buffer, 4);
	/* पूर्णांकentionally ignore __must_check वापस code */
	(व्योम)ret;
	r592_ग_लिखो_reg_raw_be(dev, R592_FIFO_PIO, *(u32 *)buffer);
पूर्ण

/*
 * Read a fअगरo in 4 bytes chunks.
 * If input करोesn't fit the buffer, it places bytes of last dword in spill
 * buffer, so that they करोn't get lost on last पढ़ो, just throw these away.
 */
अटल व्योम r592_पढ़ो_fअगरo_pio(काष्ठा r592_device *dev,
						अचिन्हित अक्षर *buffer, पूर्णांक len)
अणु
	u8 पंचांगp[4];

	/* Read from last spill */
	अगर (!kfअगरo_is_empty(&dev->pio_fअगरo)) अणु
		पूर्णांक bytes_copied =
			kfअगरo_out(&dev->pio_fअगरo, buffer, min(4, len));
		buffer += bytes_copied;
		len -= bytes_copied;

		अगर (!kfअगरo_is_empty(&dev->pio_fअगरo))
			वापस;
	पूर्ण

	/* Reads dwords from FIFO */
	जबतक (len >= 4) अणु
		*(u32 *)buffer = r592_पढ़ो_reg_raw_be(dev, R592_FIFO_PIO);
		buffer += 4;
		len -= 4;
	पूर्ण

	अगर (len) अणु
		*(u32 *)पंचांगp = r592_पढ़ो_reg_raw_be(dev, R592_FIFO_PIO);
		kfअगरo_in(&dev->pio_fअगरo, पंचांगp, 4);
		len -= kfअगरo_out(&dev->pio_fअगरo, buffer, len);
	पूर्ण

	WARN_ON(len);
	वापस;
पूर्ण

/* Transfers actual data using PIO. */
अटल पूर्णांक r592_transfer_fअगरo_pio(काष्ठा r592_device *dev)
अणु
	अचिन्हित दीर्घ flags;

	bool is_ग_लिखो = dev->req->tpc >= MS_TPC_SET_RW_REG_ADRS;
	काष्ठा sg_mapping_iter miter;

	kfअगरo_reset(&dev->pio_fअगरo);

	अगर (!dev->req->दीर्घ_data) अणु
		अगर (is_ग_लिखो) अणु
			r592_ग_लिखो_fअगरo_pio(dev, dev->req->data,
							dev->req->data_len);
			r592_flush_fअगरo_ग_लिखो(dev);
		पूर्ण अन्यथा
			r592_पढ़ो_fअगरo_pio(dev, dev->req->data,
							dev->req->data_len);
		वापस 0;
	पूर्ण

	local_irq_save(flags);
	sg_miter_start(&miter, &dev->req->sg, 1, SG_MITER_ATOMIC |
		(is_ग_लिखो ? SG_MITER_FROM_SG : SG_MITER_TO_SG));

	/* Do the transfer fअगरo<->memory*/
	जबतक (sg_miter_next(&miter))
		अगर (is_ग_लिखो)
			r592_ग_लिखो_fअगरo_pio(dev, miter.addr, miter.length);
		अन्यथा
			r592_पढ़ो_fअगरo_pio(dev, miter.addr, miter.length);


	/* Write last few non aligned bytes*/
	अगर (is_ग_लिखो)
		r592_flush_fअगरo_ग_लिखो(dev);

	sg_miter_stop(&miter);
	local_irq_restore(flags);
	वापस 0;
पूर्ण

/* Executes one TPC (data is पढ़ो/written from small or large fअगरo) */
अटल व्योम r592_execute_tpc(काष्ठा r592_device *dev)
अणु
	bool is_ग_लिखो;
	पूर्णांक len, error;
	u32 status, reg;

	अगर (!dev->req) अणु
		message("BUG: tpc execution without request!");
		वापस;
	पूर्ण

	is_ग_लिखो = dev->req->tpc >= MS_TPC_SET_RW_REG_ADRS;
	len = dev->req->दीर्घ_data ?
		dev->req->sg.length : dev->req->data_len;

	/* Ensure that FIFO can hold the input data */
	अगर (len > R592_LFIFO_SIZE) अणु
		message("IO: hardware doesn't support TPCs longer that 512");
		error = -ENOSYS;
		जाओ out;
	पूर्ण

	अगर (!(r592_पढ़ो_reg(dev, R592_REG_MSC) & R592_REG_MSC_PRSNT)) अणु
		dbg("IO: refusing to send TPC because card is absent");
		error = -ENODEV;
		जाओ out;
	पूर्ण

	dbg("IO: executing %s LEN=%d",
			memstick_debug_get_tpc_name(dev->req->tpc), len);

	/* Set IO direction */
	अगर (is_ग_लिखो)
		r592_set_reg_mask(dev, R592_IO, R592_IO_सूचीECTION);
	अन्यथा
		r592_clear_reg_mask(dev, R592_IO, R592_IO_सूचीECTION);


	error = r592_test_fअगरo_empty(dev);
	अगर (error)
		जाओ out;

	/* Transfer ग_लिखो data */
	अगर (is_ग_लिखो) अणु
		error = r592_transfer_fअगरo_dma(dev);
		अगर (error == -EINVAL)
			error = r592_transfer_fअगरo_pio(dev);
	पूर्ण

	अगर (error)
		जाओ out;

	/* Trigger the TPC */
	reg = (len << R592_TPC_EXEC_LEN_SHIFT) |
		(dev->req->tpc << R592_TPC_EXEC_TPC_SHIFT) |
			R592_TPC_EXEC_BIG_FIFO;

	r592_ग_लिखो_reg(dev, R592_TPC_EXEC, reg);

	/* Wait क्रम TPC completion */
	status = R592_STATUS_RDY;
	अगर (dev->req->need_card_पूर्णांक)
		status |= R592_STATUS_CED;

	error = r592_रुको_status(dev, status, status);
	अगर (error) अणु
		message("card didn't respond");
		जाओ out;
	पूर्ण

	/* Test IO errors */
	error = r592_test_io_error(dev);
	अगर (error) अणु
		dbg("IO error");
		जाओ out;
	पूर्ण

	/* Read data from FIFO */
	अगर (!is_ग_लिखो) अणु
		error = r592_transfer_fअगरo_dma(dev);
		अगर (error == -EINVAL)
			error = r592_transfer_fअगरo_pio(dev);
	पूर्ण

	/* पढ़ो INT reg. This can be लघुened with shअगरts, but that way
		its more पढ़ोable */
	अगर (dev->parallel_mode && dev->req->need_card_पूर्णांक) अणु

		dev->req->पूर्णांक_reg = 0;
		status = r592_पढ़ो_reg(dev, R592_STATUS);

		अगर (status & R592_STATUS_P_CMDNACK)
			dev->req->पूर्णांक_reg |= MEMSTICK_INT_CMDNAK;
		अगर (status & R592_STATUS_P_BREQ)
			dev->req->पूर्णांक_reg |= MEMSTICK_INT_BREQ;
		अगर (status & R592_STATUS_P_INTERR)
			dev->req->पूर्णांक_reg |= MEMSTICK_INT_ERR;
		अगर (status & R592_STATUS_P_CED)
			dev->req->पूर्णांक_reg |= MEMSTICK_INT_CED;
	पूर्ण

	अगर (error)
		dbg("FIFO read error");
out:
	dev->req->error = error;
	r592_clear_reg_mask(dev, R592_REG_MSC, R592_REG_MSC_LED);
	वापस;
पूर्ण

/* Main request processing thपढ़ो */
अटल पूर्णांक r592_process_thपढ़ो(व्योम *data)
अणु
	पूर्णांक error;
	काष्ठा r592_device *dev = (काष्ठा r592_device *)data;
	अचिन्हित दीर्घ flags;

	जबतक (!kthपढ़ो_should_stop()) अणु
		spin_lock_irqsave(&dev->io_thपढ़ो_lock, flags);
		set_current_state(TASK_INTERRUPTIBLE);
		error = memstick_next_req(dev->host, &dev->req);
		spin_unlock_irqrestore(&dev->io_thपढ़ो_lock, flags);

		अगर (error) अणु
			अगर (error == -ENXIO || error == -EAGAIN) अणु
				dbg_verbose("IO: done IO, sleeping");
			पूर्ण अन्यथा अणु
				dbg("IO: unknown error from "
					"memstick_next_req %d", error);
			पूर्ण

			अगर (kthपढ़ो_should_stop())
				set_current_state(TASK_RUNNING);

			schedule();
		पूर्ण अन्यथा अणु
			set_current_state(TASK_RUNNING);
			r592_execute_tpc(dev);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Reprogram chip to detect change in card state */
/* eg, अगर card is detected, arm it to detect removal, and vice versa */
अटल व्योम r592_update_card_detect(काष्ठा r592_device *dev)
अणु
	u32 reg = r592_पढ़ो_reg(dev, R592_REG_MSC);
	bool card_detected = reg & R592_REG_MSC_PRSNT;

	dbg("update card detect. card state: %s", card_detected ?
		"present" : "absent");

	reg &= ~((R592_REG_MSC_IRQ_REMOVE | R592_REG_MSC_IRQ_INSERT) << 16);

	अगर (card_detected)
		reg |= (R592_REG_MSC_IRQ_REMOVE << 16);
	अन्यथा
		reg |= (R592_REG_MSC_IRQ_INSERT << 16);

	r592_ग_लिखो_reg(dev, R592_REG_MSC, reg);
पूर्ण

/* Timer routine that fires 1 second after last card detection event, */
अटल व्योम r592_detect_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा r592_device *dev = from_समयr(dev, t, detect_समयr);
	r592_update_card_detect(dev);
	memstick_detect_change(dev->host);
पूर्ण

/* Interrupt handler */
अटल irqवापस_t r592_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा r592_device *dev = (काष्ठा r592_device *)data;
	irqवापस_t ret = IRQ_NONE;
	u32 reg;
	u16 irq_enable, irq_status;
	अचिन्हित दीर्घ flags;
	पूर्णांक error;

	spin_lock_irqsave(&dev->irq_lock, flags);

	reg = r592_पढ़ो_reg(dev, R592_REG_MSC);
	irq_enable = reg >> 16;
	irq_status = reg & 0xFFFF;

	/* Ack the पूर्णांकerrupts */
	reg &= ~irq_status;
	r592_ग_लिखो_reg(dev, R592_REG_MSC, reg);

	/* Get the IRQ status minus bits that aren't enabled */
	irq_status &= (irq_enable);

	/* Due to limitation of memstick core, we करोn't look at bits that
		indicate that card was हटाओd/inserted and/or present */
	अगर (irq_status & (R592_REG_MSC_IRQ_INSERT | R592_REG_MSC_IRQ_REMOVE)) अणु

		bool card_was_added = irq_status & R592_REG_MSC_IRQ_INSERT;
		ret = IRQ_HANDLED;

		message("IRQ: card %s", card_was_added ? "added" : "removed");

		mod_समयr(&dev->detect_समयr,
			jअगरfies + msecs_to_jअगरfies(card_was_added ? 500 : 50));
	पूर्ण

	अगर (irq_status &
		(R592_REG_MSC_FIFO_DMA_DONE | R592_REG_MSC_FIFO_DMA_ERR)) अणु
		ret = IRQ_HANDLED;

		अगर (irq_status & R592_REG_MSC_FIFO_DMA_ERR) अणु
			message("IRQ: DMA error");
			error = -EIO;
		पूर्ण अन्यथा अणु
			dbg_verbose("IRQ: dma done");
			error = 0;
		पूर्ण

		r592_stop_dma(dev, error);
		complete(&dev->dma_करोne);
	पूर्ण

	spin_unlock_irqrestore(&dev->irq_lock, flags);
	वापस ret;
पूर्ण

/* External पूर्णांकeface: set settings */
अटल पूर्णांक r592_set_param(काष्ठा memstick_host *host,
			क्रमागत memstick_param param, पूर्णांक value)
अणु
	काष्ठा r592_device *dev = memstick_priv(host);

	चयन (param) अणु
	हाल MEMSTICK_POWER:
		चयन (value) अणु
		हाल MEMSTICK_POWER_ON:
			वापस r592_enable_device(dev, true);
		हाल MEMSTICK_POWER_OFF:
			वापस r592_enable_device(dev, false);
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल MEMSTICK_INTERFACE:
		चयन (value) अणु
		हाल MEMSTICK_SERIAL:
			वापस r592_set_mode(dev, 0);
		हाल MEMSTICK_PAR4:
			वापस r592_set_mode(dev, 1);
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* External पूर्णांकerface: submit requests */
अटल व्योम r592_submit_req(काष्ठा memstick_host *host)
अणु
	काष्ठा r592_device *dev = memstick_priv(host);
	अचिन्हित दीर्घ flags;

	अगर (dev->req)
		वापस;

	spin_lock_irqsave(&dev->io_thपढ़ो_lock, flags);
	अगर (wake_up_process(dev->io_thपढ़ो))
		dbg_verbose("IO thread woken to process requests");
	spin_unlock_irqrestore(&dev->io_thपढ़ो_lock, flags);
पूर्ण

अटल स्थिर काष्ठा pci_device_id r592_pci_id_tbl[] = अणु

	अणु PCI_VDEVICE(RICOH, 0x0592), पूर्ण,
	अणु पूर्ण,
पूर्ण;

/* Main entry */
अटल पूर्णांक r592_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक error = -ENOMEM;
	काष्ठा memstick_host *host;
	काष्ठा r592_device *dev;

	/* Allocate memory */
	host = memstick_alloc_host(माप(काष्ठा r592_device), &pdev->dev);
	अगर (!host)
		जाओ error1;

	dev = memstick_priv(host);
	dev->host = host;
	dev->pci_dev = pdev;
	pci_set_drvdata(pdev, dev);

	/* pci initialization */
	error = pci_enable_device(pdev);
	अगर (error)
		जाओ error2;

	pci_set_master(pdev);
	error = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (error)
		जाओ error3;

	error = pci_request_regions(pdev, DRV_NAME);
	अगर (error)
		जाओ error3;

	dev->mmio = pci_ioremap_bar(pdev, 0);
	अगर (!dev->mmio) अणु
		error = -ENOMEM;
		जाओ error4;
	पूर्ण

	dev->irq = pdev->irq;
	spin_lock_init(&dev->irq_lock);
	spin_lock_init(&dev->io_thपढ़ो_lock);
	init_completion(&dev->dma_करोne);
	INIT_KFIFO(dev->pio_fअगरo);
	समयr_setup(&dev->detect_समयr, r592_detect_समयr, 0);

	/* Host initialization */
	host->caps = MEMSTICK_CAP_PAR4;
	host->request = r592_submit_req;
	host->set_param = r592_set_param;
	r592_check_dma(dev);

	dev->io_thपढ़ो = kthपढ़ो_run(r592_process_thपढ़ो, dev, "r592_io");
	अगर (IS_ERR(dev->io_thपढ़ो)) अणु
		error = PTR_ERR(dev->io_thपढ़ो);
		जाओ error5;
	पूर्ण

	/* This is just a precation, so करोn't fail */
	dev->dummy_dma_page = dma_alloc_coherent(&pdev->dev, PAGE_SIZE,
		&dev->dummy_dma_page_physical_address, GFP_KERNEL);
	r592_stop_dma(dev , 0);

	error = request_irq(dev->irq, &r592_irq, IRQF_SHARED,
			  DRV_NAME, dev);
	अगर (error)
		जाओ error6;

	r592_update_card_detect(dev);
	error = memstick_add_host(host);
	अगर (error)
		जाओ error7;

	message("driver successfully loaded");
	वापस 0;
error7:
	मुक्त_irq(dev->irq, dev);
error6:
	अगर (dev->dummy_dma_page)
		dma_मुक्त_coherent(&pdev->dev, PAGE_SIZE, dev->dummy_dma_page,
			dev->dummy_dma_page_physical_address);

	kthपढ़ो_stop(dev->io_thपढ़ो);
error5:
	iounmap(dev->mmio);
error4:
	pci_release_regions(pdev);
error3:
	pci_disable_device(pdev);
error2:
	memstick_मुक्त_host(host);
error1:
	वापस error;
पूर्ण

अटल व्योम r592_हटाओ(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक error = 0;
	काष्ठा r592_device *dev = pci_get_drvdata(pdev);

	/* Stop the processing thपढ़ो.
	That ensures that we won't take any more requests */
	kthपढ़ो_stop(dev->io_thपढ़ो);

	r592_enable_device(dev, false);

	जबतक (!error && dev->req) अणु
		dev->req->error = -ETIME;
		error = memstick_next_req(dev->host, &dev->req);
	पूर्ण
	memstick_हटाओ_host(dev->host);

	मुक्त_irq(dev->irq, dev);
	iounmap(dev->mmio);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	memstick_मुक्त_host(dev->host);

	अगर (dev->dummy_dma_page)
		dma_मुक्त_coherent(&pdev->dev, PAGE_SIZE, dev->dummy_dma_page,
			dev->dummy_dma_page_physical_address);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक r592_suspend(काष्ठा device *core_dev)
अणु
	काष्ठा r592_device *dev = dev_get_drvdata(core_dev);

	r592_clear_पूर्णांकerrupts(dev);
	memstick_suspend_host(dev->host);
	del_समयr_sync(&dev->detect_समयr);
	वापस 0;
पूर्ण

अटल पूर्णांक r592_resume(काष्ठा device *core_dev)
अणु
	काष्ठा r592_device *dev = dev_get_drvdata(core_dev);

	r592_clear_पूर्णांकerrupts(dev);
	r592_enable_device(dev, false);
	memstick_resume_host(dev->host);
	r592_update_card_detect(dev);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(r592_pm_ops, r592_suspend, r592_resume);

MODULE_DEVICE_TABLE(pci, r592_pci_id_tbl);

अटल काष्ठा pci_driver r852_pci_driver = अणु
	.name		= DRV_NAME,
	.id_table	= r592_pci_id_tbl,
	.probe		= r592_probe,
	.हटाओ		= r592_हटाओ,
	.driver.pm	= &r592_pm_ops,
पूर्ण;

module_pci_driver(r852_pci_driver);

module_param_named(enable_dma, r592_enable_dma, bool, S_IRUGO);
MODULE_PARM_DESC(enable_dma, "Enable usage of the DMA (default)");
module_param(debug, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "Debug level (0-3)");

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Maxim Levitsky <maximlevitsky@gmail.com>");
MODULE_DESCRIPTION("Ricoh R5C592 Memstick/Memstick PRO card reader driver");
