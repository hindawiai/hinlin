<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Marvell MMC/SD/SDIO driver
 *
 * Authors: Maen Suleiman, Nicolas Pitre
 * Copyright (C) 2008-2009 Marvell Ltd.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mbus.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/irq.h>
#समावेश <linux/clk.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/slot-gpपन.स>

#समावेश <linux/sizes.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "mvsdio.h"

#घोषणा DRIVER_NAME	"mvsdio"

अटल पूर्णांक maxfreq;
अटल पूर्णांक nodma;

काष्ठा mvsd_host अणु
	व्योम __iomem *base;
	काष्ठा mmc_request *mrq;
	spinlock_t lock;
	अचिन्हित पूर्णांक xfer_mode;
	अचिन्हित पूर्णांक पूर्णांकr_en;
	अचिन्हित पूर्णांक ctrl;
	अचिन्हित पूर्णांक pio_size;
	व्योम *pio_ptr;
	अचिन्हित पूर्णांक sg_frags;
	अचिन्हित पूर्णांक ns_per_clk;
	अचिन्हित पूर्णांक घड़ी;
	अचिन्हित पूर्णांक base_घड़ी;
	काष्ठा समयr_list समयr;
	काष्ठा mmc_host *mmc;
	काष्ठा device *dev;
	काष्ठा clk *clk;
पूर्ण;

#घोषणा mvsd_ग_लिखो(offs, val)	ग_लिखोl(val, iobase + (offs))
#घोषणा mvsd_पढ़ो(offs)		पढ़ोl(iobase + (offs))

अटल पूर्णांक mvsd_setup_data(काष्ठा mvsd_host *host, काष्ठा mmc_data *data)
अणु
	व्योम __iomem *iobase = host->base;
	अचिन्हित पूर्णांक पंचांगout;
	पूर्णांक पंचांगout_index;

	/*
	 * Hardware weirdness.  The FIFO_EMPTY bit of the HW_STATE
	 * रेजिस्टर is someबार not set beक्रमe a जबतक when some
	 * "unusual" data block sizes are used (such as with the SWITCH
	 * command), even despite the fact that the XFER_DONE पूर्णांकerrupt
	 * was उठाओd.  And अगर another data transfer starts beक्रमe
	 * this bit comes to good sense (which eventually happens by
	 * itself) then the new transfer simply fails with a समयout.
	 */
	अगर (!(mvsd_पढ़ो(MVSD_HW_STATE) & (1 << 13))) अणु
		अचिन्हित दीर्घ t = jअगरfies + HZ;
		अचिन्हित पूर्णांक hw_state,  count = 0;
		करो अणु
			hw_state = mvsd_पढ़ो(MVSD_HW_STATE);
			अगर (समय_after(jअगरfies, t)) अणु
				dev_warn(host->dev, "FIFO_EMPTY bit missing\n");
				अवरोध;
			पूर्ण
			count++;
		पूर्ण जबतक (!(hw_state & (1 << 13)));
		dev_dbg(host->dev, "*** wait for FIFO_EMPTY bit "
				   "(hw=0x%04x, count=%d, jiffies=%ld)\n",
				   hw_state, count, jअगरfies - (t - HZ));
	पूर्ण

	/* If समयout=0 then maximum समयout index is used. */
	पंचांगout = DIV_ROUND_UP(data->समयout_ns, host->ns_per_clk);
	पंचांगout += data->समयout_clks;
	पंचांगout_index = fls(पंचांगout - 1) - 12;
	अगर (पंचांगout_index < 0)
		पंचांगout_index = 0;
	अगर (पंचांगout_index > MVSD_HOST_CTRL_TMOUT_MAX)
		पंचांगout_index = MVSD_HOST_CTRL_TMOUT_MAX;

	dev_dbg(host->dev, "data %s at 0x%08x: blocks=%d blksz=%d tmout=%u (%d)\n",
		(data->flags & MMC_DATA_READ) ? "read" : "write",
		(u32)sg_virt(data->sg), data->blocks, data->blksz,
		पंचांगout, पंचांगout_index);

	host->ctrl &= ~MVSD_HOST_CTRL_TMOUT_MASK;
	host->ctrl |= MVSD_HOST_CTRL_TMOUT(पंचांगout_index);
	mvsd_ग_लिखो(MVSD_HOST_CTRL, host->ctrl);
	mvsd_ग_लिखो(MVSD_BLK_COUNT, data->blocks);
	mvsd_ग_लिखो(MVSD_BLK_SIZE, data->blksz);

	अगर (nodma || (data->blksz | data->sg->offset) & 3 ||
	    ((!(data->flags & MMC_DATA_READ) && data->sg->offset & 0x3f))) अणु
		/*
		 * We cannot करो DMA on a buffer which offset or size
		 * is not aligned on a 4-byte boundary.
		 *
		 * It also appears the host to card DMA can corrupt
		 * data when the buffer is not aligned on a 64 byte
		 * boundary.
		 */
		host->pio_size = data->blocks * data->blksz;
		host->pio_ptr = sg_virt(data->sg);
		अगर (!nodma)
			dev_dbg(host->dev, "fallback to PIO for data at 0x%p size %d\n",
				host->pio_ptr, host->pio_size);
		वापस 1;
	पूर्ण अन्यथा अणु
		dma_addr_t phys_addr;

		host->sg_frags = dma_map_sg(mmc_dev(host->mmc),
					    data->sg, data->sg_len,
					    mmc_get_dma_dir(data));
		phys_addr = sg_dma_address(data->sg);
		mvsd_ग_लिखो(MVSD_SYS_ADDR_LOW, (u32)phys_addr & 0xffff);
		mvsd_ग_लिखो(MVSD_SYS_ADDR_HI,  (u32)phys_addr >> 16);
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम mvsd_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा mvsd_host *host = mmc_priv(mmc);
	व्योम __iomem *iobase = host->base;
	काष्ठा mmc_command *cmd = mrq->cmd;
	u32 cmdreg = 0, xfer = 0, पूर्णांकr = 0;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक समयout;

	BUG_ON(host->mrq != शून्य);
	host->mrq = mrq;

	dev_dbg(host->dev, "cmd %d (hw state 0x%04x)\n",
		cmd->opcode, mvsd_पढ़ो(MVSD_HW_STATE));

	cmdreg = MVSD_CMD_INDEX(cmd->opcode);

	अगर (cmd->flags & MMC_RSP_BUSY)
		cmdreg |= MVSD_CMD_RSP_48BUSY;
	अन्यथा अगर (cmd->flags & MMC_RSP_136)
		cmdreg |= MVSD_CMD_RSP_136;
	अन्यथा अगर (cmd->flags & MMC_RSP_PRESENT)
		cmdreg |= MVSD_CMD_RSP_48;
	अन्यथा
		cmdreg |= MVSD_CMD_RSP_NONE;

	अगर (cmd->flags & MMC_RSP_CRC)
		cmdreg |= MVSD_CMD_CHECK_CMDCRC;

	अगर (cmd->flags & MMC_RSP_OPCODE)
		cmdreg |= MVSD_CMD_INDX_CHECK;

	अगर (cmd->flags & MMC_RSP_PRESENT) अणु
		cmdreg |= MVSD_UNEXPECTED_RESP;
		पूर्णांकr |= MVSD_NOR_UNEXP_RSP;
	पूर्ण

	अगर (mrq->data) अणु
		काष्ठा mmc_data *data = mrq->data;
		पूर्णांक pio;

		cmdreg |= MVSD_CMD_DATA_PRESENT | MVSD_CMD_CHECK_DATACRC16;
		xfer |= MVSD_XFER_MODE_HW_WR_DATA_EN;
		अगर (data->flags & MMC_DATA_READ)
			xfer |= MVSD_XFER_MODE_TO_HOST;

		pio = mvsd_setup_data(host, data);
		अगर (pio) अणु
			xfer |= MVSD_XFER_MODE_PIO;
			/* PIO section of mvsd_irq has comments on those bits */
			अगर (data->flags & MMC_DATA_WRITE)
				पूर्णांकr |= MVSD_NOR_TX_AVAIL;
			अन्यथा अगर (host->pio_size > 32)
				पूर्णांकr |= MVSD_NOR_RX_FIFO_8W;
			अन्यथा
				पूर्णांकr |= MVSD_NOR_RX_READY;
		पूर्ण

		अगर (data->stop) अणु
			काष्ठा mmc_command *stop = data->stop;
			u32 cmd12reg = 0;

			mvsd_ग_लिखो(MVSD_AUTOCMD12_ARG_LOW, stop->arg & 0xffff);
			mvsd_ग_लिखो(MVSD_AUTOCMD12_ARG_HI,  stop->arg >> 16);

			अगर (stop->flags & MMC_RSP_BUSY)
				cmd12reg |= MVSD_AUTOCMD12_BUSY;
			अगर (stop->flags & MMC_RSP_OPCODE)
				cmd12reg |= MVSD_AUTOCMD12_INDX_CHECK;
			cmd12reg |= MVSD_AUTOCMD12_INDEX(stop->opcode);
			mvsd_ग_लिखो(MVSD_AUTOCMD12_CMD, cmd12reg);

			xfer |= MVSD_XFER_MODE_AUTO_CMD12;
			पूर्णांकr |= MVSD_NOR_AUTOCMD12_DONE;
		पूर्ण अन्यथा अणु
			पूर्णांकr |= MVSD_NOR_XFER_DONE;
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांकr |= MVSD_NOR_CMD_DONE;
	पूर्ण

	mvsd_ग_लिखो(MVSD_ARG_LOW, cmd->arg & 0xffff);
	mvsd_ग_लिखो(MVSD_ARG_HI,  cmd->arg >> 16);

	spin_lock_irqsave(&host->lock, flags);

	host->xfer_mode &= MVSD_XFER_MODE_INT_CHK_EN;
	host->xfer_mode |= xfer;
	mvsd_ग_लिखो(MVSD_XFER_MODE, host->xfer_mode);

	mvsd_ग_लिखो(MVSD_NOR_INTR_STATUS, ~MVSD_NOR_CARD_INT);
	mvsd_ग_लिखो(MVSD_ERR_INTR_STATUS, 0xffff);
	mvsd_ग_लिखो(MVSD_CMD, cmdreg);

	host->पूर्णांकr_en &= MVSD_NOR_CARD_INT;
	host->पूर्णांकr_en |= पूर्णांकr | MVSD_NOR_ERROR;
	mvsd_ग_लिखो(MVSD_NOR_INTR_EN, host->पूर्णांकr_en);
	mvsd_ग_लिखो(MVSD_ERR_INTR_EN, 0xffff);

	समयout = cmd->busy_समयout ? cmd->busy_समयout : 5000;
	mod_समयr(&host->समयr, jअगरfies + msecs_to_jअगरfies(समयout));

	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल u32 mvsd_finish_cmd(काष्ठा mvsd_host *host, काष्ठा mmc_command *cmd,
			   u32 err_status)
अणु
	व्योम __iomem *iobase = host->base;

	अगर (cmd->flags & MMC_RSP_136) अणु
		अचिन्हित पूर्णांक response[8], i;
		क्रम (i = 0; i < 8; i++)
			response[i] = mvsd_पढ़ो(MVSD_RSP(i));
		cmd->resp[0] =		((response[0] & 0x03ff) << 22) |
					((response[1] & 0xffff) << 6) |
					((response[2] & 0xfc00) >> 10);
		cmd->resp[1] =		((response[2] & 0x03ff) << 22) |
					((response[3] & 0xffff) << 6) |
					((response[4] & 0xfc00) >> 10);
		cmd->resp[2] =		((response[4] & 0x03ff) << 22) |
					((response[5] & 0xffff) << 6) |
					((response[6] & 0xfc00) >> 10);
		cmd->resp[3] =		((response[6] & 0x03ff) << 22) |
					((response[7] & 0x3fff) << 8);
	पूर्ण अन्यथा अगर (cmd->flags & MMC_RSP_PRESENT) अणु
		अचिन्हित पूर्णांक response[3], i;
		क्रम (i = 0; i < 3; i++)
			response[i] = mvsd_पढ़ो(MVSD_RSP(i));
		cmd->resp[0] =		((response[2] & 0x003f) << (8 - 8)) |
					((response[1] & 0xffff) << (14 - 8)) |
					((response[0] & 0x03ff) << (30 - 8));
		cmd->resp[1] =		((response[0] & 0xfc00) >> 10);
		cmd->resp[2] = 0;
		cmd->resp[3] = 0;
	पूर्ण

	अगर (err_status & MVSD_ERR_CMD_TIMEOUT) अणु
		cmd->error = -ETIMEDOUT;
	पूर्ण अन्यथा अगर (err_status & (MVSD_ERR_CMD_CRC | MVSD_ERR_CMD_ENDBIT |
				 MVSD_ERR_CMD_INDEX | MVSD_ERR_CMD_STARTBIT)) अणु
		cmd->error = -EILSEQ;
	पूर्ण
	err_status &= ~(MVSD_ERR_CMD_TIMEOUT | MVSD_ERR_CMD_CRC |
			MVSD_ERR_CMD_ENDBIT | MVSD_ERR_CMD_INDEX |
			MVSD_ERR_CMD_STARTBIT);

	वापस err_status;
पूर्ण

अटल u32 mvsd_finish_data(काष्ठा mvsd_host *host, काष्ठा mmc_data *data,
			    u32 err_status)
अणु
	व्योम __iomem *iobase = host->base;

	अगर (host->pio_ptr) अणु
		host->pio_ptr = शून्य;
		host->pio_size = 0;
	पूर्ण अन्यथा अणु
		dma_unmap_sg(mmc_dev(host->mmc), data->sg, host->sg_frags,
			     mmc_get_dma_dir(data));
	पूर्ण

	अगर (err_status & MVSD_ERR_DATA_TIMEOUT)
		data->error = -ETIMEDOUT;
	अन्यथा अगर (err_status & (MVSD_ERR_DATA_CRC | MVSD_ERR_DATA_ENDBIT))
		data->error = -EILSEQ;
	अन्यथा अगर (err_status & MVSD_ERR_XFER_SIZE)
		data->error = -EBADE;
	err_status &= ~(MVSD_ERR_DATA_TIMEOUT | MVSD_ERR_DATA_CRC |
			MVSD_ERR_DATA_ENDBIT | MVSD_ERR_XFER_SIZE);

	dev_dbg(host->dev, "data done: blocks_left=%d, bytes_left=%d\n",
		mvsd_पढ़ो(MVSD_CURR_BLK_LEFT), mvsd_पढ़ो(MVSD_CURR_BYTE_LEFT));
	data->bytes_xfered =
		(data->blocks - mvsd_पढ़ो(MVSD_CURR_BLK_LEFT)) * data->blksz;
	/* We can't be sure about the last block when errors are detected */
	अगर (data->bytes_xfered && data->error)
		data->bytes_xfered -= data->blksz;

	/* Handle Auto cmd 12 response */
	अगर (data->stop) अणु
		अचिन्हित पूर्णांक response[3], i;
		क्रम (i = 0; i < 3; i++)
			response[i] = mvsd_पढ़ो(MVSD_AUTO_RSP(i));
		data->stop->resp[0] =	((response[2] & 0x003f) << (8 - 8)) |
					((response[1] & 0xffff) << (14 - 8)) |
					((response[0] & 0x03ff) << (30 - 8));
		data->stop->resp[1] =	((response[0] & 0xfc00) >> 10);
		data->stop->resp[2] = 0;
		data->stop->resp[3] = 0;

		अगर (err_status & MVSD_ERR_AUTOCMD12) अणु
			u32 err_cmd12 = mvsd_पढ़ो(MVSD_AUTOCMD12_ERR_STATUS);
			dev_dbg(host->dev, "c12err 0x%04x\n", err_cmd12);
			अगर (err_cmd12 & MVSD_AUTOCMD12_ERR_NOTEXE)
				data->stop->error = -ENOEXEC;
			अन्यथा अगर (err_cmd12 & MVSD_AUTOCMD12_ERR_TIMEOUT)
				data->stop->error = -ETIMEDOUT;
			अन्यथा अगर (err_cmd12)
				data->stop->error = -EILSEQ;
			err_status &= ~MVSD_ERR_AUTOCMD12;
		पूर्ण
	पूर्ण

	वापस err_status;
पूर्ण

अटल irqवापस_t mvsd_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा mvsd_host *host = dev;
	व्योम __iomem *iobase = host->base;
	u32 पूर्णांकr_status, पूर्णांकr_करोne_mask;
	पूर्णांक irq_handled = 0;

	पूर्णांकr_status = mvsd_पढ़ो(MVSD_NOR_INTR_STATUS);
	dev_dbg(host->dev, "intr 0x%04x intr_en 0x%04x hw_state 0x%04x\n",
		पूर्णांकr_status, mvsd_पढ़ो(MVSD_NOR_INTR_EN),
		mvsd_पढ़ो(MVSD_HW_STATE));

	/*
	 * It looks like, SDIO IP can issue one late, spurious irq
	 * although all irqs should be disabled. To work around this,
	 * bail out early, अगर we didn't expect any irqs to occur.
	 */
	अगर (!mvsd_पढ़ो(MVSD_NOR_INTR_EN) && !mvsd_पढ़ो(MVSD_ERR_INTR_EN)) अणु
		dev_dbg(host->dev, "spurious irq detected intr 0x%04x intr_en 0x%04x erri 0x%04x erri_en 0x%04x\n",
			mvsd_पढ़ो(MVSD_NOR_INTR_STATUS),
			mvsd_पढ़ो(MVSD_NOR_INTR_EN),
			mvsd_पढ़ो(MVSD_ERR_INTR_STATUS),
			mvsd_पढ़ो(MVSD_ERR_INTR_EN));
		वापस IRQ_HANDLED;
	पूर्ण

	spin_lock(&host->lock);

	/* PIO handling, अगर needed. Messy business... */
	अगर (host->pio_size &&
	    (पूर्णांकr_status & host->पूर्णांकr_en &
	     (MVSD_NOR_RX_READY | MVSD_NOR_RX_FIFO_8W))) अणु
		u16 *p = host->pio_ptr;
		पूर्णांक s = host->pio_size;
		जबतक (s >= 32 && (पूर्णांकr_status & MVSD_NOR_RX_FIFO_8W)) अणु
			पढ़ोsw(iobase + MVSD_FIFO, p, 16);
			p += 16;
			s -= 32;
			पूर्णांकr_status = mvsd_पढ़ो(MVSD_NOR_INTR_STATUS);
		पूर्ण
		/*
		 * Normally we'd use < 32 here, but the RX_FIFO_8W bit
		 * करोesn't appear to निश्चित when there is exactly 32 bytes
		 * (8 words) left to fetch in a transfer.
		 */
		अगर (s <= 32) अणु
			जबतक (s >= 4 && (पूर्णांकr_status & MVSD_NOR_RX_READY)) अणु
				put_unaligned(mvsd_पढ़ो(MVSD_FIFO), p++);
				put_unaligned(mvsd_पढ़ो(MVSD_FIFO), p++);
				s -= 4;
				पूर्णांकr_status = mvsd_पढ़ो(MVSD_NOR_INTR_STATUS);
			पूर्ण
			अगर (s && s < 4 && (पूर्णांकr_status & MVSD_NOR_RX_READY)) अणु
				u16 val[2] = अणु0, 0पूर्ण;
				val[0] = mvsd_पढ़ो(MVSD_FIFO);
				val[1] = mvsd_पढ़ो(MVSD_FIFO);
				स_नकल(p, ((व्योम *)&val) + 4 - s, s);
				s = 0;
				पूर्णांकr_status = mvsd_पढ़ो(MVSD_NOR_INTR_STATUS);
			पूर्ण
			अगर (s == 0) अणु
				host->पूर्णांकr_en &=
				     ~(MVSD_NOR_RX_READY | MVSD_NOR_RX_FIFO_8W);
				mvsd_ग_लिखो(MVSD_NOR_INTR_EN, host->पूर्णांकr_en);
			पूर्ण अन्यथा अगर (host->पूर्णांकr_en & MVSD_NOR_RX_FIFO_8W) अणु
				host->पूर्णांकr_en &= ~MVSD_NOR_RX_FIFO_8W;
				host->पूर्णांकr_en |= MVSD_NOR_RX_READY;
				mvsd_ग_लिखो(MVSD_NOR_INTR_EN, host->पूर्णांकr_en);
			पूर्ण
		पूर्ण
		dev_dbg(host->dev, "pio %d intr 0x%04x hw_state 0x%04x\n",
			s, पूर्णांकr_status, mvsd_पढ़ो(MVSD_HW_STATE));
		host->pio_ptr = p;
		host->pio_size = s;
		irq_handled = 1;
	पूर्ण अन्यथा अगर (host->pio_size &&
		   (पूर्णांकr_status & host->पूर्णांकr_en &
		    (MVSD_NOR_TX_AVAIL | MVSD_NOR_TX_FIFO_8W))) अणु
		u16 *p = host->pio_ptr;
		पूर्णांक s = host->pio_size;
		/*
		 * The TX_FIFO_8W bit is unreliable. When set, bursting
		 * 16 halfwords all at once in the FIFO drops data. Actually
		 * TX_AVAIL करोes go off after only one word is pushed even अगर
		 * TX_FIFO_8W reमुख्यs set.
		 */
		जबतक (s >= 4 && (पूर्णांकr_status & MVSD_NOR_TX_AVAIL)) अणु
			mvsd_ग_लिखो(MVSD_FIFO, get_unaligned(p++));
			mvsd_ग_लिखो(MVSD_FIFO, get_unaligned(p++));
			s -= 4;
			पूर्णांकr_status = mvsd_पढ़ो(MVSD_NOR_INTR_STATUS);
		पूर्ण
		अगर (s < 4) अणु
			अगर (s && (पूर्णांकr_status & MVSD_NOR_TX_AVAIL)) अणु
				u16 val[2] = अणु0, 0पूर्ण;
				स_नकल(((व्योम *)&val) + 4 - s, p, s);
				mvsd_ग_लिखो(MVSD_FIFO, val[0]);
				mvsd_ग_लिखो(MVSD_FIFO, val[1]);
				s = 0;
				पूर्णांकr_status = mvsd_पढ़ो(MVSD_NOR_INTR_STATUS);
			पूर्ण
			अगर (s == 0) अणु
				host->पूर्णांकr_en &=
				     ~(MVSD_NOR_TX_AVAIL | MVSD_NOR_TX_FIFO_8W);
				mvsd_ग_लिखो(MVSD_NOR_INTR_EN, host->पूर्णांकr_en);
			पूर्ण
		पूर्ण
		dev_dbg(host->dev, "pio %d intr 0x%04x hw_state 0x%04x\n",
			s, पूर्णांकr_status, mvsd_पढ़ो(MVSD_HW_STATE));
		host->pio_ptr = p;
		host->pio_size = s;
		irq_handled = 1;
	पूर्ण

	mvsd_ग_लिखो(MVSD_NOR_INTR_STATUS, पूर्णांकr_status);

	पूर्णांकr_करोne_mask = MVSD_NOR_CARD_INT | MVSD_NOR_RX_READY |
			 MVSD_NOR_RX_FIFO_8W | MVSD_NOR_TX_FIFO_8W;
	अगर (पूर्णांकr_status & host->पूर्णांकr_en & ~पूर्णांकr_करोne_mask) अणु
		काष्ठा mmc_request *mrq = host->mrq;
		काष्ठा mmc_command *cmd = mrq->cmd;
		u32 err_status = 0;

		del_समयr(&host->समयr);
		host->mrq = शून्य;

		host->पूर्णांकr_en &= MVSD_NOR_CARD_INT;
		mvsd_ग_लिखो(MVSD_NOR_INTR_EN, host->पूर्णांकr_en);
		mvsd_ग_लिखो(MVSD_ERR_INTR_EN, 0);

		spin_unlock(&host->lock);

		अगर (पूर्णांकr_status & MVSD_NOR_UNEXP_RSP) अणु
			cmd->error = -EPROTO;
		पूर्ण अन्यथा अगर (पूर्णांकr_status & MVSD_NOR_ERROR) अणु
			err_status = mvsd_पढ़ो(MVSD_ERR_INTR_STATUS);
			dev_dbg(host->dev, "err 0x%04x\n", err_status);
		पूर्ण

		err_status = mvsd_finish_cmd(host, cmd, err_status);
		अगर (mrq->data)
			err_status = mvsd_finish_data(host, mrq->data, err_status);
		अगर (err_status) अणु
			dev_err(host->dev, "unhandled error status %#04x\n",
				err_status);
			cmd->error = -ENOMSG;
		पूर्ण

		mmc_request_करोne(host->mmc, mrq);
		irq_handled = 1;
	पूर्ण अन्यथा
		spin_unlock(&host->lock);

	अगर (पूर्णांकr_status & MVSD_NOR_CARD_INT) अणु
		mmc_संकेत_sdio_irq(host->mmc);
		irq_handled = 1;
	पूर्ण

	अगर (irq_handled)
		वापस IRQ_HANDLED;

	dev_err(host->dev, "unhandled interrupt status=0x%04x en=0x%04x pio=%d\n",
		पूर्णांकr_status, host->पूर्णांकr_en, host->pio_size);
	वापस IRQ_NONE;
पूर्ण

अटल व्योम mvsd_समयout_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा mvsd_host *host = from_समयr(host, t, समयr);
	व्योम __iomem *iobase = host->base;
	काष्ठा mmc_request *mrq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);
	mrq = host->mrq;
	अगर (mrq) अणु
		dev_err(host->dev, "Timeout waiting for hardware interrupt.\n");
		dev_err(host->dev, "hw_state=0x%04x, intr_status=0x%04x intr_en=0x%04x\n",
			mvsd_पढ़ो(MVSD_HW_STATE),
			mvsd_पढ़ो(MVSD_NOR_INTR_STATUS),
			mvsd_पढ़ो(MVSD_NOR_INTR_EN));

		host->mrq = शून्य;

		mvsd_ग_लिखो(MVSD_SW_RESET, MVSD_SW_RESET_NOW);

		host->xfer_mode &= MVSD_XFER_MODE_INT_CHK_EN;
		mvsd_ग_लिखो(MVSD_XFER_MODE, host->xfer_mode);

		host->पूर्णांकr_en &= MVSD_NOR_CARD_INT;
		mvsd_ग_लिखो(MVSD_NOR_INTR_EN, host->पूर्णांकr_en);
		mvsd_ग_लिखो(MVSD_ERR_INTR_EN, 0);
		mvsd_ग_लिखो(MVSD_ERR_INTR_STATUS, 0xffff);

		mrq->cmd->error = -ETIMEDOUT;
		mvsd_finish_cmd(host, mrq->cmd, 0);
		अगर (mrq->data) अणु
			mrq->data->error = -ETIMEDOUT;
			mvsd_finish_data(host, mrq->data, 0);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&host->lock, flags);

	अगर (mrq)
		mmc_request_करोne(host->mmc, mrq);
पूर्ण

अटल व्योम mvsd_enable_sdio_irq(काष्ठा mmc_host *mmc, पूर्णांक enable)
अणु
	काष्ठा mvsd_host *host = mmc_priv(mmc);
	व्योम __iomem *iobase = host->base;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);
	अगर (enable) अणु
		host->xfer_mode |= MVSD_XFER_MODE_INT_CHK_EN;
		host->पूर्णांकr_en |= MVSD_NOR_CARD_INT;
	पूर्ण अन्यथा अणु
		host->xfer_mode &= ~MVSD_XFER_MODE_INT_CHK_EN;
		host->पूर्णांकr_en &= ~MVSD_NOR_CARD_INT;
	पूर्ण
	mvsd_ग_लिखो(MVSD_XFER_MODE, host->xfer_mode);
	mvsd_ग_लिखो(MVSD_NOR_INTR_EN, host->पूर्णांकr_en);
	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल व्योम mvsd_घातer_up(काष्ठा mvsd_host *host)
अणु
	व्योम __iomem *iobase = host->base;
	dev_dbg(host->dev, "power up\n");
	mvsd_ग_लिखो(MVSD_NOR_INTR_EN, 0);
	mvsd_ग_लिखो(MVSD_ERR_INTR_EN, 0);
	mvsd_ग_लिखो(MVSD_SW_RESET, MVSD_SW_RESET_NOW);
	mvsd_ग_लिखो(MVSD_XFER_MODE, 0);
	mvsd_ग_लिखो(MVSD_NOR_STATUS_EN, 0xffff);
	mvsd_ग_लिखो(MVSD_ERR_STATUS_EN, 0xffff);
	mvsd_ग_लिखो(MVSD_NOR_INTR_STATUS, 0xffff);
	mvsd_ग_लिखो(MVSD_ERR_INTR_STATUS, 0xffff);
पूर्ण

अटल व्योम mvsd_घातer_करोwn(काष्ठा mvsd_host *host)
अणु
	व्योम __iomem *iobase = host->base;
	dev_dbg(host->dev, "power down\n");
	mvsd_ग_लिखो(MVSD_NOR_INTR_EN, 0);
	mvsd_ग_लिखो(MVSD_ERR_INTR_EN, 0);
	mvsd_ग_लिखो(MVSD_SW_RESET, MVSD_SW_RESET_NOW);
	mvsd_ग_लिखो(MVSD_XFER_MODE, MVSD_XFER_MODE_STOP_CLK);
	mvsd_ग_लिखो(MVSD_NOR_STATUS_EN, 0);
	mvsd_ग_लिखो(MVSD_ERR_STATUS_EN, 0);
	mvsd_ग_लिखो(MVSD_NOR_INTR_STATUS, 0xffff);
	mvsd_ग_लिखो(MVSD_ERR_INTR_STATUS, 0xffff);
पूर्ण

अटल व्योम mvsd_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा mvsd_host *host = mmc_priv(mmc);
	व्योम __iomem *iobase = host->base;
	u32 ctrl_reg = 0;

	अगर (ios->घातer_mode == MMC_POWER_UP)
		mvsd_घातer_up(host);

	अगर (ios->घड़ी == 0) अणु
		mvsd_ग_लिखो(MVSD_XFER_MODE, MVSD_XFER_MODE_STOP_CLK);
		mvsd_ग_लिखो(MVSD_CLK_DIV, MVSD_BASE_DIV_MAX);
		host->घड़ी = 0;
		dev_dbg(host->dev, "clock off\n");
	पूर्ण अन्यथा अगर (ios->घड़ी != host->घड़ी) अणु
		u32 m = DIV_ROUND_UP(host->base_घड़ी, ios->घड़ी) - 1;
		अगर (m > MVSD_BASE_DIV_MAX)
			m = MVSD_BASE_DIV_MAX;
		mvsd_ग_लिखो(MVSD_CLK_DIV, m);
		host->घड़ी = ios->घड़ी;
		host->ns_per_clk = 1000000000 / (host->base_घड़ी / (m+1));
		dev_dbg(host->dev, "clock=%d (%d), div=0x%04x\n",
			ios->घड़ी, host->base_घड़ी / (m+1), m);
	पूर्ण

	/* शेष transfer mode */
	ctrl_reg |= MVSD_HOST_CTRL_BIG_ENDIAN;
	ctrl_reg &= ~MVSD_HOST_CTRL_LSB_FIRST;

	/* शेष to maximum समयout */
	ctrl_reg |= MVSD_HOST_CTRL_TMOUT_MASK;
	ctrl_reg |= MVSD_HOST_CTRL_TMOUT_EN;

	अगर (ios->bus_mode == MMC_BUSMODE_PUSHPULL)
		ctrl_reg |= MVSD_HOST_CTRL_PUSH_PULL_EN;

	अगर (ios->bus_width == MMC_BUS_WIDTH_4)
		ctrl_reg |= MVSD_HOST_CTRL_DATA_WIDTH_4_BITS;

	/*
	 * The HI_SPEED_EN bit is causing trouble with many (but not all)
	 * high speed SD, SDHC and SDIO cards.  Not enabling that bit
	 * makes all cards work.  So let's just ignore that bit क्रम now
	 * and revisit this issue अगर problems क्रम not enabling this bit
	 * are ever reported.
	 */
#अगर 0
	अगर (ios->timing == MMC_TIMING_MMC_HS ||
	    ios->timing == MMC_TIMING_SD_HS)
		ctrl_reg |= MVSD_HOST_CTRL_HI_SPEED_EN;
#पूर्ण_अगर

	host->ctrl = ctrl_reg;
	mvsd_ग_लिखो(MVSD_HOST_CTRL, ctrl_reg);
	dev_dbg(host->dev, "ctrl 0x%04x: %s %s %s\n", ctrl_reg,
		(ctrl_reg & MVSD_HOST_CTRL_PUSH_PULL_EN) ?
			"push-pull" : "open-drain",
		(ctrl_reg & MVSD_HOST_CTRL_DATA_WIDTH_4_BITS) ?
			"4bit-width" : "1bit-width",
		(ctrl_reg & MVSD_HOST_CTRL_HI_SPEED_EN) ?
			"high-speed" : "");

	अगर (ios->घातer_mode == MMC_POWER_OFF)
		mvsd_घातer_करोwn(host);
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops mvsd_ops = अणु
	.request		= mvsd_request,
	.get_ro			= mmc_gpio_get_ro,
	.set_ios		= mvsd_set_ios,
	.enable_sdio_irq	= mvsd_enable_sdio_irq,
पूर्ण;

अटल व्योम
mv_conf_mbus_winकरोws(काष्ठा mvsd_host *host,
		     स्थिर काष्ठा mbus_dram_target_info *dram)
अणु
	व्योम __iomem *iobase = host->base;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		ग_लिखोl(0, iobase + MVSD_WINDOW_CTRL(i));
		ग_लिखोl(0, iobase + MVSD_WINDOW_BASE(i));
	पूर्ण

	क्रम (i = 0; i < dram->num_cs; i++) अणु
		स्थिर काष्ठा mbus_dram_winकरोw *cs = dram->cs + i;
		ग_लिखोl(((cs->size - 1) & 0xffff0000) |
		       (cs->mbus_attr << 8) |
		       (dram->mbus_dram_target_id << 4) | 1,
		       iobase + MVSD_WINDOW_CTRL(i));
		ग_लिखोl(cs->base, iobase + MVSD_WINDOW_BASE(i));
	पूर्ण
पूर्ण

अटल पूर्णांक mvsd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा mmc_host *mmc = शून्य;
	काष्ठा mvsd_host *host = शून्य;
	स्थिर काष्ठा mbus_dram_target_info *dram;
	पूर्णांक ret, irq;

	अगर (!np) अणु
		dev_err(&pdev->dev, "no DT node\n");
		वापस -ENODEV;
	पूर्ण
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -ENXIO;

	mmc = mmc_alloc_host(माप(काष्ठा mvsd_host), &pdev->dev);
	अगर (!mmc) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	host = mmc_priv(mmc);
	host->mmc = mmc;
	host->dev = &pdev->dev;

	/*
	 * Some non-DT platक्रमms करो not pass a घड़ी, and the घड़ी
	 * frequency is passed through platक्रमm_data. On DT platक्रमms,
	 * a घड़ी must always be passed, even अगर there is no gatable
	 * घड़ी associated to the SDIO पूर्णांकerface (it can simply be a
	 * fixed rate घड़ी).
	 */
	host->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(host->clk)) अणु
		dev_err(&pdev->dev, "no clock associated\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	clk_prepare_enable(host->clk);

	mmc->ops = &mvsd_ops;

	mmc->ocr_avail = MMC_VDD_32_33 | MMC_VDD_33_34;

	mmc->f_min = DIV_ROUND_UP(host->base_घड़ी, MVSD_BASE_DIV_MAX);
	mmc->f_max = MVSD_CLOCKRATE_MAX;

	mmc->max_blk_size = 2048;
	mmc->max_blk_count = 65535;

	mmc->max_segs = 1;
	mmc->max_seg_size = mmc->max_blk_size * mmc->max_blk_count;
	mmc->max_req_size = mmc->max_blk_size * mmc->max_blk_count;

	host->base_घड़ी = clk_get_rate(host->clk) / 2;
	ret = mmc_of_parse(mmc);
	अगर (ret < 0)
		जाओ out;
	अगर (maxfreq)
		mmc->f_max = maxfreq;

	spin_lock_init(&host->lock);

	host->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(host->base)) अणु
		ret = PTR_ERR(host->base);
		जाओ out;
	पूर्ण

	/* (Re-)program MBUS remapping winकरोws अगर we are asked to. */
	dram = mv_mbus_dram_info();
	अगर (dram)
		mv_conf_mbus_winकरोws(host, dram);

	mvsd_घातer_करोwn(host);

	ret = devm_request_irq(&pdev->dev, irq, mvsd_irq, 0, DRIVER_NAME, host);
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot assign irq %d\n", irq);
		जाओ out;
	पूर्ण

	समयr_setup(&host->समयr, mvsd_समयout_समयr, 0);
	platक्रमm_set_drvdata(pdev, mmc);
	ret = mmc_add_host(mmc);
	अगर (ret)
		जाओ out;

	अगर (!(mmc->caps & MMC_CAP_NEEDS_POLL))
		dev_dbg(&pdev->dev, "using GPIO for card detection\n");
	अन्यथा
		dev_dbg(&pdev->dev, "lacking card detect (fall back to polling)\n");

	वापस 0;

out:
	अगर (mmc) अणु
		अगर (!IS_ERR(host->clk))
			clk_disable_unprepare(host->clk);
		mmc_मुक्त_host(mmc);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mvsd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_host *mmc = platक्रमm_get_drvdata(pdev);

	काष्ठा mvsd_host *host = mmc_priv(mmc);

	mmc_हटाओ_host(mmc);
	del_समयr_sync(&host->समयr);
	mvsd_घातer_करोwn(host);

	अगर (!IS_ERR(host->clk))
		clk_disable_unprepare(host->clk);
	mmc_मुक्त_host(mmc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mvsdio_dt_ids[] = अणु
	अणु .compatible = "marvell,orion-sdio" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mvsdio_dt_ids);

अटल काष्ठा platक्रमm_driver mvsd_driver = अणु
	.probe		= mvsd_probe,
	.हटाओ		= mvsd_हटाओ,
	.driver		= अणु
		.name	= DRIVER_NAME,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = mvsdio_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mvsd_driver);

/* maximum card घड़ी frequency (शेष 50MHz) */
module_param(maxfreq, पूर्णांक, 0);

/* क्रमce PIO transfers all the समय */
module_param(nodma, पूर्णांक, 0);

MODULE_AUTHOR("Maen Suleiman, Nicolas Pitre");
MODULE_DESCRIPTION("Marvell MMC,SD,SDIO Host Controller driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:mvsdio");
