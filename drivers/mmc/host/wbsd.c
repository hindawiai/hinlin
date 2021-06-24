<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  linux/drivers/mmc/host/wbsd.c - Winbond W83L51xD SD/MMC driver
 *
 *  Copyright (C) 2004-2007 Pierre Ossman, All Rights Reserved.
 *
 * Warning!
 *
 * Changes to the FIFO प्रणाली should be करोne with extreme care since
 * the hardware is full of bugs related to the FIFO. Known issues are:
 *
 * - FIFO size field in FSR is always zero.
 *
 * - FIFO पूर्णांकerrupts tend not to work as they should. Interrupts are
 *   triggered only क्रम full/empty events, not क्रम threshold values.
 *
 * - On APIC प्रणालीs the FIFO empty पूर्णांकerrupt is someबार lost.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/pnp.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/sd.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>

#समावेश "wbsd.h"

#घोषणा DRIVER_NAME "wbsd"

#घोषणा DBG(x...) \
	pr_debug(DRIVER_NAME ": " x)
#घोषणा DBGF(f, x...) \
	pr_debug(DRIVER_NAME " [%s()]: " f, __func__ , ##x)

/*
 * Device resources
 */

#अगर_घोषित CONFIG_PNP

अटल स्थिर काष्ठा pnp_device_id pnp_dev_table[] = अणु
	अणु "WEC0517", 0 पूर्ण,
	अणु "WEC0518", 0 पूर्ण,
	अणु "", 0 पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pnp, pnp_dev_table);

#पूर्ण_अगर /* CONFIG_PNP */

अटल स्थिर पूर्णांक config_ports[] = अणु 0x2E, 0x4E पूर्ण;
अटल स्थिर पूर्णांक unlock_codes[] = अणु 0x83, 0x87 पूर्ण;

अटल स्थिर पूर्णांक valid_ids[] = अणु
	0x7112,
पूर्ण;

#अगर_घोषित CONFIG_PNP
अटल अचिन्हित पूर्णांक param_nopnp = 0;
#अन्यथा
अटल स्थिर अचिन्हित पूर्णांक param_nopnp = 1;
#पूर्ण_अगर
अटल अचिन्हित पूर्णांक param_io = 0x248;
अटल अचिन्हित पूर्णांक param_irq = 6;
अटल पूर्णांक param_dma = 2;

/*
 * Basic functions
 */

अटल अंतरभूत व्योम wbsd_unlock_config(काष्ठा wbsd_host *host)
अणु
	BUG_ON(host->config == 0);

	outb(host->unlock_code, host->config);
	outb(host->unlock_code, host->config);
पूर्ण

अटल अंतरभूत व्योम wbsd_lock_config(काष्ठा wbsd_host *host)
अणु
	BUG_ON(host->config == 0);

	outb(LOCK_CODE, host->config);
पूर्ण

अटल अंतरभूत व्योम wbsd_ग_लिखो_config(काष्ठा wbsd_host *host, u8 reg, u8 value)
अणु
	BUG_ON(host->config == 0);

	outb(reg, host->config);
	outb(value, host->config + 1);
पूर्ण

अटल अंतरभूत u8 wbsd_पढ़ो_config(काष्ठा wbsd_host *host, u8 reg)
अणु
	BUG_ON(host->config == 0);

	outb(reg, host->config);
	वापस inb(host->config + 1);
पूर्ण

अटल अंतरभूत व्योम wbsd_ग_लिखो_index(काष्ठा wbsd_host *host, u8 index, u8 value)
अणु
	outb(index, host->base + WBSD_IDXR);
	outb(value, host->base + WBSD_DATAR);
पूर्ण

अटल अंतरभूत u8 wbsd_पढ़ो_index(काष्ठा wbsd_host *host, u8 index)
अणु
	outb(index, host->base + WBSD_IDXR);
	वापस inb(host->base + WBSD_DATAR);
पूर्ण

/*
 * Common routines
 */

अटल व्योम wbsd_init_device(काष्ठा wbsd_host *host)
अणु
	u8 setup, ier;

	/*
	 * Reset chip (SD/MMC part) and fअगरo.
	 */
	setup = wbsd_पढ़ो_index(host, WBSD_IDX_SETUP);
	setup |= WBSD_FIFO_RESET | WBSD_SOFT_RESET;
	wbsd_ग_लिखो_index(host, WBSD_IDX_SETUP, setup);

	/*
	 * Set DAT3 to input
	 */
	setup &= ~WBSD_DAT3_H;
	wbsd_ग_लिखो_index(host, WBSD_IDX_SETUP, setup);
	host->flags &= ~WBSD_FIGNORE_DETECT;

	/*
	 * Read back शेष घड़ी.
	 */
	host->clk = wbsd_पढ़ो_index(host, WBSD_IDX_CLK);

	/*
	 * Power करोwn port.
	 */
	outb(WBSD_POWER_N, host->base + WBSD_CSR);

	/*
	 * Set maximum समयout.
	 */
	wbsd_ग_लिखो_index(host, WBSD_IDX_TAAC, 0x7F);

	/*
	 * Test क्रम card presence
	 */
	अगर (inb(host->base + WBSD_CSR) & WBSD_CARDPRESENT)
		host->flags |= WBSD_FCARD_PRESENT;
	अन्यथा
		host->flags &= ~WBSD_FCARD_PRESENT;

	/*
	 * Enable पूर्णांकeresting पूर्णांकerrupts.
	 */
	ier = 0;
	ier |= WBSD_EINT_CARD;
	ier |= WBSD_EINT_FIFO_THRE;
	ier |= WBSD_EINT_CRC;
	ier |= WBSD_EINT_TIMEOUT;
	ier |= WBSD_EINT_TC;

	outb(ier, host->base + WBSD_EIR);

	/*
	 * Clear पूर्णांकerrupts.
	 */
	inb(host->base + WBSD_ISR);
पूर्ण

अटल व्योम wbsd_reset(काष्ठा wbsd_host *host)
अणु
	u8 setup;

	pr_err("%s: Resetting chip\n", mmc_hostname(host->mmc));

	/*
	 * Soft reset of chip (SD/MMC part).
	 */
	setup = wbsd_पढ़ो_index(host, WBSD_IDX_SETUP);
	setup |= WBSD_SOFT_RESET;
	wbsd_ग_लिखो_index(host, WBSD_IDX_SETUP, setup);
पूर्ण

अटल व्योम wbsd_request_end(काष्ठा wbsd_host *host, काष्ठा mmc_request *mrq)
अणु
	अचिन्हित दीर्घ dmaflags;

	अगर (host->dma >= 0) अणु
		/*
		 * Release ISA DMA controller.
		 */
		dmaflags = claim_dma_lock();
		disable_dma(host->dma);
		clear_dma_ff(host->dma);
		release_dma_lock(dmaflags);

		/*
		 * Disable DMA on host.
		 */
		wbsd_ग_लिखो_index(host, WBSD_IDX_DMA, 0);
	पूर्ण

	host->mrq = शून्य;

	/*
	 * MMC layer might call back पूर्णांकo the driver so first unlock.
	 */
	spin_unlock(&host->lock);
	mmc_request_करोne(host->mmc, mrq);
	spin_lock(&host->lock);
पूर्ण

/*
 * Scatter/gather functions
 */

अटल अंतरभूत व्योम wbsd_init_sg(काष्ठा wbsd_host *host, काष्ठा mmc_data *data)
अणु
	/*
	 * Get info. about SG list from data काष्ठाure.
	 */
	host->cur_sg = data->sg;
	host->num_sg = data->sg_len;

	host->offset = 0;
	host->reमुख्य = host->cur_sg->length;
पूर्ण

अटल अंतरभूत पूर्णांक wbsd_next_sg(काष्ठा wbsd_host *host)
अणु
	/*
	 * Skip to next SG entry.
	 */
	host->cur_sg++;
	host->num_sg--;

	/*
	 * Any entries left?
	 */
	अगर (host->num_sg > 0) अणु
		host->offset = 0;
		host->reमुख्य = host->cur_sg->length;
	पूर्ण

	वापस host->num_sg;
पूर्ण

अटल अंतरभूत अक्षर *wbsd_map_sg(काष्ठा wbsd_host *host)
अणु
	वापस kmap_atomic(sg_page(host->cur_sg)) + host->cur_sg->offset;
पूर्ण

अटल अंतरभूत व्योम wbsd_sg_to_dma(काष्ठा wbsd_host *host, काष्ठा mmc_data *data)
अणु
	माप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < data->sg_len; i++)
		len += data->sg[i].length;
	sg_copy_to_buffer(data->sg, data->sg_len, host->dma_buffer, len);
पूर्ण

अटल अंतरभूत व्योम wbsd_dma_to_sg(काष्ठा wbsd_host *host, काष्ठा mmc_data *data)
अणु
	माप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < data->sg_len; i++)
		len += data->sg[i].length;
	sg_copy_from_buffer(data->sg, data->sg_len, host->dma_buffer, len);
पूर्ण

/*
 * Command handling
 */

अटल अंतरभूत व्योम wbsd_get_लघु_reply(काष्ठा wbsd_host *host,
					काष्ठा mmc_command *cmd)
अणु
	/*
	 * Correct response type?
	 */
	अगर (wbsd_पढ़ो_index(host, WBSD_IDX_RSPLEN) != WBSD_RSP_SHORT) अणु
		cmd->error = -EILSEQ;
		वापस;
	पूर्ण

	cmd->resp[0]  = wbsd_पढ़ो_index(host, WBSD_IDX_RESP12) << 24;
	cmd->resp[0] |= wbsd_पढ़ो_index(host, WBSD_IDX_RESP13) << 16;
	cmd->resp[0] |= wbsd_पढ़ो_index(host, WBSD_IDX_RESP14) << 8;
	cmd->resp[0] |= wbsd_पढ़ो_index(host, WBSD_IDX_RESP15) << 0;
	cmd->resp[1]  = wbsd_पढ़ो_index(host, WBSD_IDX_RESP16) << 24;
पूर्ण

अटल अंतरभूत व्योम wbsd_get_दीर्घ_reply(काष्ठा wbsd_host *host,
	काष्ठा mmc_command *cmd)
अणु
	पूर्णांक i;

	/*
	 * Correct response type?
	 */
	अगर (wbsd_पढ़ो_index(host, WBSD_IDX_RSPLEN) != WBSD_RSP_LONG) अणु
		cmd->error = -EILSEQ;
		वापस;
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		cmd->resp[i] =
			wbsd_पढ़ो_index(host, WBSD_IDX_RESP1 + i * 4) << 24;
		cmd->resp[i] |=
			wbsd_पढ़ो_index(host, WBSD_IDX_RESP2 + i * 4) << 16;
		cmd->resp[i] |=
			wbsd_पढ़ो_index(host, WBSD_IDX_RESP3 + i * 4) << 8;
		cmd->resp[i] |=
			wbsd_पढ़ो_index(host, WBSD_IDX_RESP4 + i * 4) << 0;
	पूर्ण
पूर्ण

अटल व्योम wbsd_send_command(काष्ठा wbsd_host *host, काष्ठा mmc_command *cmd)
अणु
	पूर्णांक i;
	u8 status, isr;

	/*
	 * Clear accumulated ISR. The पूर्णांकerrupt routine
	 * will fill this one with events that occur during
	 * transfer.
	 */
	host->isr = 0;

	/*
	 * Send the command (CRC calculated by host).
	 */
	outb(cmd->opcode, host->base + WBSD_CMDR);
	क्रम (i = 3; i >= 0; i--)
		outb((cmd->arg >> (i * 8)) & 0xff, host->base + WBSD_CMDR);

	cmd->error = 0;

	/*
	 * Wait क्रम the request to complete.
	 */
	करो अणु
		status = wbsd_पढ़ो_index(host, WBSD_IDX_STATUS);
	पूर्ण जबतक (status & WBSD_CARDTRAFFIC);

	/*
	 * Do we expect a reply?
	 */
	अगर (cmd->flags & MMC_RSP_PRESENT) अणु
		/*
		 * Read back status.
		 */
		isr = host->isr;

		/* Card हटाओd? */
		अगर (isr & WBSD_INT_CARD)
			cmd->error = -ENOMEDIUM;
		/* Timeout? */
		अन्यथा अगर (isr & WBSD_INT_TIMEOUT)
			cmd->error = -ETIMEDOUT;
		/* CRC? */
		अन्यथा अगर ((cmd->flags & MMC_RSP_CRC) && (isr & WBSD_INT_CRC))
			cmd->error = -EILSEQ;
		/* All ok */
		अन्यथा अणु
			अगर (cmd->flags & MMC_RSP_136)
				wbsd_get_दीर्घ_reply(host, cmd);
			अन्यथा
				wbsd_get_लघु_reply(host, cmd);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Data functions
 */

अटल व्योम wbsd_empty_fअगरo(काष्ठा wbsd_host *host)
अणु
	काष्ठा mmc_data *data = host->mrq->cmd->data;
	अक्षर *buffer;
	पूर्णांक i, idx, fsr, fअगरo;

	/*
	 * Handle excessive data.
	 */
	अगर (host->num_sg == 0)
		वापस;

	buffer = wbsd_map_sg(host) + host->offset;
	idx = 0;

	/*
	 * Drain the fअगरo. This has a tendency to loop दीर्घer
	 * than the FIFO length (usually one block).
	 */
	जबतक (!((fsr = inb(host->base + WBSD_FSR)) & WBSD_FIFO_EMPTY)) अणु
		/*
		 * The size field in the FSR is broken so we have to
		 * करो some guessing.
		 */
		अगर (fsr & WBSD_FIFO_FULL)
			fअगरo = 16;
		अन्यथा अगर (fsr & WBSD_FIFO_FUTHRE)
			fअगरo = 8;
		अन्यथा
			fअगरo = 1;

		क्रम (i = 0; i < fअगरo; i++) अणु
			buffer[idx++] = inb(host->base + WBSD_DFR);
			host->offset++;
			host->reमुख्य--;

			data->bytes_xfered++;

			/*
			 * End of scatter list entry?
			 */
			अगर (host->reमुख्य == 0) अणु
				kunmap_atomic(buffer);
				/*
				 * Get next entry. Check अगर last.
				 */
				अगर (!wbsd_next_sg(host))
					वापस;

				buffer = wbsd_map_sg(host);
				idx = 0;
			पूर्ण
		पूर्ण
	पूर्ण
	kunmap_atomic(buffer);

	/*
	 * This is a very dirty hack to solve a
	 * hardware problem. The chip करोesn't trigger
	 * FIFO threshold पूर्णांकerrupts properly.
	 */
	अगर ((data->blocks * data->blksz - data->bytes_xfered) < 16)
		tasklet_schedule(&host->fअगरo_tasklet);
पूर्ण

अटल व्योम wbsd_fill_fअगरo(काष्ठा wbsd_host *host)
अणु
	काष्ठा mmc_data *data = host->mrq->cmd->data;
	अक्षर *buffer;
	पूर्णांक i, idx, fsr, fअगरo;

	/*
	 * Check that we aren't being called after the
	 * entire buffer has been transferred.
	 */
	अगर (host->num_sg == 0)
		वापस;

	buffer = wbsd_map_sg(host) + host->offset;
	idx = 0;

	/*
	 * Fill the fअगरo. This has a tendency to loop दीर्घer
	 * than the FIFO length (usually one block).
	 */
	जबतक (!((fsr = inb(host->base + WBSD_FSR)) & WBSD_FIFO_FULL)) अणु
		/*
		 * The size field in the FSR is broken so we have to
		 * करो some guessing.
		 */
		अगर (fsr & WBSD_FIFO_EMPTY)
			fअगरo = 0;
		अन्यथा अगर (fsr & WBSD_FIFO_EMTHRE)
			fअगरo = 8;
		अन्यथा
			fअगरo = 15;

		क्रम (i = 16; i > fअगरo; i--) अणु
			outb(buffer[idx], host->base + WBSD_DFR);
			host->offset++;
			host->reमुख्य--;

			data->bytes_xfered++;

			/*
			 * End of scatter list entry?
			 */
			अगर (host->reमुख्य == 0) अणु
				kunmap_atomic(buffer);
				/*
				 * Get next entry. Check अगर last.
				 */
				अगर (!wbsd_next_sg(host))
					वापस;

				buffer = wbsd_map_sg(host);
				idx = 0;
			पूर्ण
		पूर्ण
	पूर्ण
	kunmap_atomic(buffer);

	/*
	 * The controller stops sending पूर्णांकerrupts क्रम
	 * 'FIFO empty' under certain conditions. So we
	 * need to be a bit more pro-active.
	 */
	tasklet_schedule(&host->fअगरo_tasklet);
पूर्ण

अटल व्योम wbsd_prepare_data(काष्ठा wbsd_host *host, काष्ठा mmc_data *data)
अणु
	u16 blksize;
	u8 setup;
	अचिन्हित दीर्घ dmaflags;
	अचिन्हित पूर्णांक size;

	/*
	 * Calculate size.
	 */
	size = data->blocks * data->blksz;

	/*
	 * Check समयout values क्रम overflow.
	 * (Yes, some cards cause this value to overflow).
	 */
	अगर (data->समयout_ns > 127000000)
		wbsd_ग_लिखो_index(host, WBSD_IDX_TAAC, 127);
	अन्यथा अणु
		wbsd_ग_लिखो_index(host, WBSD_IDX_TAAC,
			data->समयout_ns / 1000000);
	पूर्ण

	अगर (data->समयout_clks > 255)
		wbsd_ग_लिखो_index(host, WBSD_IDX_NSAC, 255);
	अन्यथा
		wbsd_ग_लिखो_index(host, WBSD_IDX_NSAC, data->समयout_clks);

	/*
	 * Inक्रमm the chip of how large blocks will be
	 * sent. It needs this to determine when to
	 * calculate CRC.
	 *
	 * Space क्रम CRC must be included in the size.
	 * Two bytes are needed क्रम each data line.
	 */
	अगर (host->bus_width == MMC_BUS_WIDTH_1) अणु
		blksize = data->blksz + 2;

		wbsd_ग_लिखो_index(host, WBSD_IDX_PBSMSB, (blksize >> 4) & 0xF0);
		wbsd_ग_लिखो_index(host, WBSD_IDX_PBSLSB, blksize & 0xFF);
	पूर्ण अन्यथा अगर (host->bus_width == MMC_BUS_WIDTH_4) अणु
		blksize = data->blksz + 2 * 4;

		wbsd_ग_लिखो_index(host, WBSD_IDX_PBSMSB,
			((blksize >> 4) & 0xF0) | WBSD_DATA_WIDTH);
		wbsd_ग_लिखो_index(host, WBSD_IDX_PBSLSB, blksize & 0xFF);
	पूर्ण अन्यथा अणु
		data->error = -EINVAL;
		वापस;
	पूर्ण

	/*
	 * Clear the FIFO. This is needed even क्रम DMA
	 * transfers since the chip still uses the FIFO
	 * पूर्णांकernally.
	 */
	setup = wbsd_पढ़ो_index(host, WBSD_IDX_SETUP);
	setup |= WBSD_FIFO_RESET;
	wbsd_ग_लिखो_index(host, WBSD_IDX_SETUP, setup);

	/*
	 * DMA transfer?
	 */
	अगर (host->dma >= 0) अणु
		/*
		 * The buffer क्रम DMA is only 64 kB.
		 */
		BUG_ON(size > 0x10000);
		अगर (size > 0x10000) अणु
			data->error = -EINVAL;
			वापस;
		पूर्ण

		/*
		 * Transfer data from the SG list to
		 * the DMA buffer.
		 */
		अगर (data->flags & MMC_DATA_WRITE)
			wbsd_sg_to_dma(host, data);

		/*
		 * Initialise the ISA DMA controller.
		 */
		dmaflags = claim_dma_lock();
		disable_dma(host->dma);
		clear_dma_ff(host->dma);
		अगर (data->flags & MMC_DATA_READ)
			set_dma_mode(host->dma, DMA_MODE_READ & ~0x40);
		अन्यथा
			set_dma_mode(host->dma, DMA_MODE_WRITE & ~0x40);
		set_dma_addr(host->dma, host->dma_addr);
		set_dma_count(host->dma, size);

		enable_dma(host->dma);
		release_dma_lock(dmaflags);

		/*
		 * Enable DMA on the host.
		 */
		wbsd_ग_लिखो_index(host, WBSD_IDX_DMA, WBSD_DMA_ENABLE);
	पूर्ण अन्यथा अणु
		/*
		 * This flag is used to keep prपूर्णांकk
		 * output to a minimum.
		 */
		host->firsterr = 1;

		/*
		 * Initialise the SG list.
		 */
		wbsd_init_sg(host, data);

		/*
		 * Turn off DMA.
		 */
		wbsd_ग_लिखो_index(host, WBSD_IDX_DMA, 0);

		/*
		 * Set up FIFO threshold levels (and fill
		 * buffer अगर करोing a ग_लिखो).
		 */
		अगर (data->flags & MMC_DATA_READ) अणु
			wbsd_ग_लिखो_index(host, WBSD_IDX_FIFOEN,
				WBSD_FIFOEN_FULL | 8);
		पूर्ण अन्यथा अणु
			wbsd_ग_लिखो_index(host, WBSD_IDX_FIFOEN,
				WBSD_FIFOEN_EMPTY | 8);
			wbsd_fill_fअगरo(host);
		पूर्ण
	पूर्ण

	data->error = 0;
पूर्ण

अटल व्योम wbsd_finish_data(काष्ठा wbsd_host *host, काष्ठा mmc_data *data)
अणु
	अचिन्हित दीर्घ dmaflags;
	पूर्णांक count;
	u8 status;

	WARN_ON(host->mrq == शून्य);

	/*
	 * Send a stop command अगर needed.
	 */
	अगर (data->stop)
		wbsd_send_command(host, data->stop);

	/*
	 * Wait क्रम the controller to leave data
	 * transfer state.
	 */
	करो अणु
		status = wbsd_पढ़ो_index(host, WBSD_IDX_STATUS);
	पूर्ण जबतक (status & (WBSD_BLOCK_READ | WBSD_BLOCK_WRITE));

	/*
	 * DMA transfer?
	 */
	अगर (host->dma >= 0) अणु
		/*
		 * Disable DMA on the host.
		 */
		wbsd_ग_लिखो_index(host, WBSD_IDX_DMA, 0);

		/*
		 * Turn of ISA DMA controller.
		 */
		dmaflags = claim_dma_lock();
		disable_dma(host->dma);
		clear_dma_ff(host->dma);
		count = get_dma_residue(host->dma);
		release_dma_lock(dmaflags);

		data->bytes_xfered = host->mrq->data->blocks *
			host->mrq->data->blksz - count;
		data->bytes_xfered -= data->bytes_xfered % data->blksz;

		/*
		 * Any leftover data?
		 */
		अगर (count) अणु
			pr_err("%s: Incomplete DMA transfer. "
				"%d bytes left.\n",
				mmc_hostname(host->mmc), count);

			अगर (!data->error)
				data->error = -EIO;
		पूर्ण अन्यथा अणु
			/*
			 * Transfer data from DMA buffer to
			 * SG list.
			 */
			अगर (data->flags & MMC_DATA_READ)
				wbsd_dma_to_sg(host, data);
		पूर्ण

		अगर (data->error) अणु
			अगर (data->bytes_xfered)
				data->bytes_xfered -= data->blksz;
		पूर्ण
	पूर्ण

	wbsd_request_end(host, host->mrq);
पूर्ण

/*****************************************************************************\
 *                                                                           *
 * MMC layer callbacks                                                       *
 *                                                                           *
\*****************************************************************************/

अटल व्योम wbsd_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा wbsd_host *host = mmc_priv(mmc);
	काष्ठा mmc_command *cmd;

	/*
	 * Disable tasklets to aव्योम a deadlock.
	 */
	spin_lock_bh(&host->lock);

	BUG_ON(host->mrq != शून्य);

	cmd = mrq->cmd;

	host->mrq = mrq;

	/*
	 * Check that there is actually a card in the slot.
	 */
	अगर (!(host->flags & WBSD_FCARD_PRESENT)) अणु
		cmd->error = -ENOMEDIUM;
		जाओ करोne;
	पूर्ण

	अगर (cmd->data) अणु
		/*
		 * The hardware is so delightfully stupid that it has a list
		 * of "data" commands. If a command isn't on this list, it'll
		 * just go back to the idle state and won't send any data
		 * पूर्णांकerrupts.
		 */
		चयन (cmd->opcode) अणु
		हाल SD_SWITCH_VOLTAGE:
		हाल MMC_READ_SINGLE_BLOCK:
		हाल MMC_READ_MULTIPLE_BLOCK:
		हाल MMC_WRITE_DAT_UNTIL_STOP:
		हाल MMC_WRITE_BLOCK:
		हाल MMC_WRITE_MULTIPLE_BLOCK:
		हाल MMC_PROGRAM_CID:
		हाल MMC_PROGRAM_CSD:
		हाल MMC_SEND_WRITE_PROT:
		हाल MMC_LOCK_UNLOCK:
		हाल MMC_GEN_CMD:
			अवरोध;

		/* ACMDs. We करोn't keep track of state, so we just treat them
		 * like any other command. */
		हाल SD_APP_SEND_SCR:
			अवरोध;

		शेष:
			pr_warn("%s: Data command %d is not supported by this controller\n",
				mmc_hostname(host->mmc), cmd->opcode);
			cmd->error = -EINVAL;

			जाओ करोne;
		पूर्ण
	पूर्ण

	/*
	 * Does the request include data?
	 */
	अगर (cmd->data) अणु
		wbsd_prepare_data(host, cmd->data);

		अगर (cmd->data->error)
			जाओ करोne;
	पूर्ण

	wbsd_send_command(host, cmd);

	/*
	 * If this is a data transfer the request
	 * will be finished after the data has
	 * transferred.
	 */
	अगर (cmd->data && !cmd->error) अणु
		/*
		 * Dirty fix क्रम hardware bug.
		 */
		अगर (host->dma == -1)
			tasklet_schedule(&host->fअगरo_tasklet);

		spin_unlock_bh(&host->lock);

		वापस;
	पूर्ण

करोne:
	wbsd_request_end(host, mrq);

	spin_unlock_bh(&host->lock);
पूर्ण

अटल व्योम wbsd_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा wbsd_host *host = mmc_priv(mmc);
	u8 clk, setup, pwr;

	spin_lock_bh(&host->lock);

	/*
	 * Reset the chip on each घातer off.
	 * Should clear out any weird states.
	 */
	अगर (ios->घातer_mode == MMC_POWER_OFF)
		wbsd_init_device(host);

	अगर (ios->घड़ी >= 24000000)
		clk = WBSD_CLK_24M;
	अन्यथा अगर (ios->घड़ी >= 16000000)
		clk = WBSD_CLK_16M;
	अन्यथा अगर (ios->घड़ी >= 12000000)
		clk = WBSD_CLK_12M;
	अन्यथा
		clk = WBSD_CLK_375K;

	/*
	 * Only ग_लिखो to the घड़ी रेजिस्टर when
	 * there is an actual change.
	 */
	अगर (clk != host->clk) अणु
		wbsd_ग_लिखो_index(host, WBSD_IDX_CLK, clk);
		host->clk = clk;
	पूर्ण

	/*
	 * Power up card.
	 */
	अगर (ios->घातer_mode != MMC_POWER_OFF) अणु
		pwr = inb(host->base + WBSD_CSR);
		pwr &= ~WBSD_POWER_N;
		outb(pwr, host->base + WBSD_CSR);
	पूर्ण

	/*
	 * MMC cards need to have pin 1 high during init.
	 * It wreaks havoc with the card detection though so
	 * that needs to be disabled.
	 */
	setup = wbsd_पढ़ो_index(host, WBSD_IDX_SETUP);
	अगर (ios->chip_select == MMC_CS_HIGH) अणु
		BUG_ON(ios->bus_width != MMC_BUS_WIDTH_1);
		setup |= WBSD_DAT3_H;
		host->flags |= WBSD_FIGNORE_DETECT;
	पूर्ण अन्यथा अणु
		अगर (setup & WBSD_DAT3_H) अणु
			setup &= ~WBSD_DAT3_H;

			/*
			 * We cannot resume card detection immediately
			 * because of capacitance and delays in the chip.
			 */
			mod_समयr(&host->ignore_समयr, jअगरfies + HZ / 100);
		पूर्ण
	पूर्ण
	wbsd_ग_लिखो_index(host, WBSD_IDX_SETUP, setup);

	/*
	 * Store bus width क्रम later. Will be used when
	 * setting up the data transfer.
	 */
	host->bus_width = ios->bus_width;

	spin_unlock_bh(&host->lock);
पूर्ण

अटल पूर्णांक wbsd_get_ro(काष्ठा mmc_host *mmc)
अणु
	काष्ठा wbsd_host *host = mmc_priv(mmc);
	u8 csr;

	spin_lock_bh(&host->lock);

	csr = inb(host->base + WBSD_CSR);
	csr |= WBSD_MSLED;
	outb(csr, host->base + WBSD_CSR);

	mdelay(1);

	csr = inb(host->base + WBSD_CSR);
	csr &= ~WBSD_MSLED;
	outb(csr, host->base + WBSD_CSR);

	spin_unlock_bh(&host->lock);

	वापस !!(csr & WBSD_WRPT);
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops wbsd_ops = अणु
	.request	= wbsd_request,
	.set_ios	= wbsd_set_ios,
	.get_ro		= wbsd_get_ro,
पूर्ण;

/*****************************************************************************\
 *                                                                           *
 * Interrupt handling                                                        *
 *                                                                           *
\*****************************************************************************/

/*
 * Helper function to reset detection ignore
 */

अटल व्योम wbsd_reset_ignore(काष्ठा समयr_list *t)
अणु
	काष्ठा wbsd_host *host = from_समयr(host, t, ignore_समयr);

	BUG_ON(host == शून्य);

	DBG("Resetting card detection ignore\n");

	spin_lock_bh(&host->lock);

	host->flags &= ~WBSD_FIGNORE_DETECT;

	/*
	 * Card status might have changed during the
	 * blackout.
	 */
	tasklet_schedule(&host->card_tasklet);

	spin_unlock_bh(&host->lock);
पूर्ण

/*
 * Tasklets
 */

अटल अंतरभूत काष्ठा mmc_data *wbsd_get_data(काष्ठा wbsd_host *host)
अणु
	WARN_ON(!host->mrq);
	अगर (!host->mrq)
		वापस शून्य;

	WARN_ON(!host->mrq->cmd);
	अगर (!host->mrq->cmd)
		वापस शून्य;

	WARN_ON(!host->mrq->cmd->data);
	अगर (!host->mrq->cmd->data)
		वापस शून्य;

	वापस host->mrq->cmd->data;
पूर्ण

अटल व्योम wbsd_tasklet_card(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा wbsd_host *host = from_tasklet(host, t, card_tasklet);
	u8 csr;
	पूर्णांक delay = -1;

	spin_lock(&host->lock);

	अगर (host->flags & WBSD_FIGNORE_DETECT) अणु
		spin_unlock(&host->lock);
		वापस;
	पूर्ण

	csr = inb(host->base + WBSD_CSR);
	WARN_ON(csr == 0xff);

	अगर (csr & WBSD_CARDPRESENT) अणु
		अगर (!(host->flags & WBSD_FCARD_PRESENT)) अणु
			DBG("Card inserted\n");
			host->flags |= WBSD_FCARD_PRESENT;

			delay = 500;
		पूर्ण
	पूर्ण अन्यथा अगर (host->flags & WBSD_FCARD_PRESENT) अणु
		DBG("Card removed\n");
		host->flags &= ~WBSD_FCARD_PRESENT;

		अगर (host->mrq) अणु
			pr_err("%s: Card removed during transfer!\n",
				mmc_hostname(host->mmc));
			wbsd_reset(host);

			host->mrq->cmd->error = -ENOMEDIUM;
			tasklet_schedule(&host->finish_tasklet);
		पूर्ण

		delay = 0;
	पूर्ण

	/*
	 * Unlock first since we might get a call back.
	 */

	spin_unlock(&host->lock);

	अगर (delay != -1)
		mmc_detect_change(host->mmc, msecs_to_jअगरfies(delay));
पूर्ण

अटल व्योम wbsd_tasklet_fअगरo(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा wbsd_host *host = from_tasklet(host, t, fअगरo_tasklet);
	काष्ठा mmc_data *data;

	spin_lock(&host->lock);

	अगर (!host->mrq)
		जाओ end;

	data = wbsd_get_data(host);
	अगर (!data)
		जाओ end;

	अगर (data->flags & MMC_DATA_WRITE)
		wbsd_fill_fअगरo(host);
	अन्यथा
		wbsd_empty_fअगरo(host);

	/*
	 * Done?
	 */
	अगर (host->num_sg == 0) अणु
		wbsd_ग_लिखो_index(host, WBSD_IDX_FIFOEN, 0);
		tasklet_schedule(&host->finish_tasklet);
	पूर्ण

end:
	spin_unlock(&host->lock);
पूर्ण

अटल व्योम wbsd_tasklet_crc(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा wbsd_host *host = from_tasklet(host, t, crc_tasklet);
	काष्ठा mmc_data *data;

	spin_lock(&host->lock);

	अगर (!host->mrq)
		जाओ end;

	data = wbsd_get_data(host);
	अगर (!data)
		जाओ end;

	DBGF("CRC error\n");

	data->error = -EILSEQ;

	tasklet_schedule(&host->finish_tasklet);

end:
	spin_unlock(&host->lock);
पूर्ण

अटल व्योम wbsd_tasklet_समयout(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा wbsd_host *host = from_tasklet(host, t, समयout_tasklet);
	काष्ठा mmc_data *data;

	spin_lock(&host->lock);

	अगर (!host->mrq)
		जाओ end;

	data = wbsd_get_data(host);
	अगर (!data)
		जाओ end;

	DBGF("Timeout\n");

	data->error = -ETIMEDOUT;

	tasklet_schedule(&host->finish_tasklet);

end:
	spin_unlock(&host->lock);
पूर्ण

अटल व्योम wbsd_tasklet_finish(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा wbsd_host *host = from_tasklet(host, t, finish_tasklet);
	काष्ठा mmc_data *data;

	spin_lock(&host->lock);

	WARN_ON(!host->mrq);
	अगर (!host->mrq)
		जाओ end;

	data = wbsd_get_data(host);
	अगर (!data)
		जाओ end;

	wbsd_finish_data(host, data);

end:
	spin_unlock(&host->lock);
पूर्ण

/*
 * Interrupt handling
 */

अटल irqवापस_t wbsd_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा wbsd_host *host = dev_id;
	पूर्णांक isr;

	isr = inb(host->base + WBSD_ISR);

	/*
	 * Was it actually our hardware that caused the पूर्णांकerrupt?
	 */
	अगर (isr == 0xff || isr == 0x00)
		वापस IRQ_NONE;

	host->isr |= isr;

	/*
	 * Schedule tasklets as needed.
	 */
	अगर (isr & WBSD_INT_CARD)
		tasklet_schedule(&host->card_tasklet);
	अगर (isr & WBSD_INT_FIFO_THRE)
		tasklet_schedule(&host->fअगरo_tasklet);
	अगर (isr & WBSD_INT_CRC)
		tasklet_hi_schedule(&host->crc_tasklet);
	अगर (isr & WBSD_INT_TIMEOUT)
		tasklet_hi_schedule(&host->समयout_tasklet);
	अगर (isr & WBSD_INT_TC)
		tasklet_schedule(&host->finish_tasklet);

	वापस IRQ_HANDLED;
पूर्ण

/*****************************************************************************\
 *                                                                           *
 * Device initialisation and shutकरोwn                                        *
 *                                                                           *
\*****************************************************************************/

/*
 * Allocate/मुक्त MMC काष्ठाure.
 */

अटल पूर्णांक wbsd_alloc_mmc(काष्ठा device *dev)
अणु
	काष्ठा mmc_host *mmc;
	काष्ठा wbsd_host *host;

	/*
	 * Allocate MMC काष्ठाure.
	 */
	mmc = mmc_alloc_host(माप(काष्ठा wbsd_host), dev);
	अगर (!mmc)
		वापस -ENOMEM;

	host = mmc_priv(mmc);
	host->mmc = mmc;

	host->dma = -1;

	/*
	 * Set host parameters.
	 */
	mmc->ops = &wbsd_ops;
	mmc->f_min = 375000;
	mmc->f_max = 24000000;
	mmc->ocr_avail = MMC_VDD_32_33 | MMC_VDD_33_34;
	mmc->caps = MMC_CAP_4_BIT_DATA;

	spin_lock_init(&host->lock);

	/*
	 * Set up समयrs
	 */
	समयr_setup(&host->ignore_समयr, wbsd_reset_ignore, 0);

	/*
	 * Maximum number of segments. Worst हाल is one sector per segment
	 * so this will be 64kB/512.
	 */
	mmc->max_segs = 128;

	/*
	 * Maximum request size. Also limited by 64KiB buffer.
	 */
	mmc->max_req_size = 65536;

	/*
	 * Maximum segment size. Could be one segment with the maximum number
	 * of bytes.
	 */
	mmc->max_seg_size = mmc->max_req_size;

	/*
	 * Maximum block size. We have 12 bits (= 4095) but have to subtract
	 * space क्रम CRC. So the maximum is 4095 - 4*2 = 4087.
	 */
	mmc->max_blk_size = 4087;

	/*
	 * Maximum block count. There is no real limit so the maximum
	 * request size will be the only restriction.
	 */
	mmc->max_blk_count = mmc->max_req_size;

	dev_set_drvdata(dev, mmc);

	वापस 0;
पूर्ण

अटल व्योम wbsd_मुक्त_mmc(काष्ठा device *dev)
अणु
	काष्ठा mmc_host *mmc;
	काष्ठा wbsd_host *host;

	mmc = dev_get_drvdata(dev);
	अगर (!mmc)
		वापस;

	host = mmc_priv(mmc);
	BUG_ON(host == शून्य);

	del_समयr_sync(&host->ignore_समयr);

	mmc_मुक्त_host(mmc);

	dev_set_drvdata(dev, शून्य);
पूर्ण

/*
 * Scan क्रम known chip id:s
 */

अटल पूर्णांक wbsd_scan(काष्ठा wbsd_host *host)
अणु
	पूर्णांक i, j, k;
	पूर्णांक id;

	/*
	 * Iterate through all ports, all codes to
	 * find hardware that is in our known list.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(config_ports); i++) अणु
		अगर (!request_region(config_ports[i], 2, DRIVER_NAME))
			जारी;

		क्रम (j = 0; j < ARRAY_SIZE(unlock_codes); j++) अणु
			id = 0xFFFF;

			host->config = config_ports[i];
			host->unlock_code = unlock_codes[j];

			wbsd_unlock_config(host);

			outb(WBSD_CONF_ID_HI, config_ports[i]);
			id = inb(config_ports[i] + 1) << 8;

			outb(WBSD_CONF_ID_LO, config_ports[i]);
			id |= inb(config_ports[i] + 1);

			wbsd_lock_config(host);

			क्रम (k = 0; k < ARRAY_SIZE(valid_ids); k++) अणु
				अगर (id == valid_ids[k]) अणु
					host->chip_id = id;

					वापस 0;
				पूर्ण
			पूर्ण

			अगर (id != 0xFFFF) अणु
				DBG("Unknown hardware (id %x) found at %x\n",
					id, config_ports[i]);
			पूर्ण
		पूर्ण

		release_region(config_ports[i], 2);
	पूर्ण

	host->config = 0;
	host->unlock_code = 0;

	वापस -ENODEV;
पूर्ण

/*
 * Allocate/मुक्त io port ranges
 */

अटल पूर्णांक wbsd_request_region(काष्ठा wbsd_host *host, पूर्णांक base)
अणु
	अगर (base & 0x7)
		वापस -EINVAL;

	अगर (!request_region(base, 8, DRIVER_NAME))
		वापस -EIO;

	host->base = base;

	वापस 0;
पूर्ण

अटल व्योम wbsd_release_regions(काष्ठा wbsd_host *host)
अणु
	अगर (host->base)
		release_region(host->base, 8);

	host->base = 0;

	अगर (host->config)
		release_region(host->config, 2);

	host->config = 0;
पूर्ण

/*
 * Allocate/मुक्त DMA port and buffer
 */

अटल व्योम wbsd_request_dma(काष्ठा wbsd_host *host, पूर्णांक dma)
अणु
	अगर (dma < 0)
		वापस;

	अगर (request_dma(dma, DRIVER_NAME))
		जाओ err;

	/*
	 * We need to allocate a special buffer in
	 * order क्रम ISA to be able to DMA to it.
	 */
	host->dma_buffer = kदो_स्मृति(WBSD_DMA_SIZE,
		GFP_NOIO | GFP_DMA | __GFP_RETRY_MAYFAIL | __GFP_NOWARN);
	अगर (!host->dma_buffer)
		जाओ मुक्त;

	/*
	 * Translate the address to a physical address.
	 */
	host->dma_addr = dma_map_single(mmc_dev(host->mmc), host->dma_buffer,
		WBSD_DMA_SIZE, DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(mmc_dev(host->mmc), host->dma_addr))
		जाओ kमुक्त;

	/*
	 * ISA DMA must be aligned on a 64k basis.
	 */
	अगर ((host->dma_addr & 0xffff) != 0)
		जाओ unmap;
	/*
	 * ISA cannot access memory above 16 MB.
	 */
	अन्यथा अगर (host->dma_addr >= 0x1000000)
		जाओ unmap;

	host->dma = dma;

	वापस;

unmap:
	/*
	 * If we've gotten here then there is some kind of alignment bug
	 */
	BUG_ON(1);

	dma_unmap_single(mmc_dev(host->mmc), host->dma_addr,
		WBSD_DMA_SIZE, DMA_BIसूचीECTIONAL);
	host->dma_addr = 0;

kमुक्त:
	kमुक्त(host->dma_buffer);
	host->dma_buffer = शून्य;

मुक्त:
	मुक्त_dma(dma);

err:
	pr_warn(DRIVER_NAME ": Unable to allocate DMA %d - falling back on FIFO\n",
		dma);
पूर्ण

अटल व्योम wbsd_release_dma(काष्ठा wbsd_host *host)
अणु
	/*
	 * host->dma_addr is valid here अगरf host->dma_buffer is not शून्य.
	 */
	अगर (host->dma_buffer) अणु
		dma_unmap_single(mmc_dev(host->mmc), host->dma_addr,
			WBSD_DMA_SIZE, DMA_BIसूचीECTIONAL);
		kमुक्त(host->dma_buffer);
	पूर्ण
	अगर (host->dma >= 0)
		मुक्त_dma(host->dma);

	host->dma = -1;
	host->dma_buffer = शून्य;
	host->dma_addr = 0;
पूर्ण

/*
 * Allocate/मुक्त IRQ.
 */

अटल पूर्णांक wbsd_request_irq(काष्ठा wbsd_host *host, पूर्णांक irq)
अणु
	पूर्णांक ret;

	/*
	 * Set up tasklets. Must be करोne beक्रमe requesting पूर्णांकerrupt.
	 */
	tasklet_setup(&host->card_tasklet, wbsd_tasklet_card);
	tasklet_setup(&host->fअगरo_tasklet, wbsd_tasklet_fअगरo);
	tasklet_setup(&host->crc_tasklet, wbsd_tasklet_crc);
	tasklet_setup(&host->समयout_tasklet, wbsd_tasklet_समयout);
	tasklet_setup(&host->finish_tasklet, wbsd_tasklet_finish);

	/*
	 * Allocate पूर्णांकerrupt.
	 */
	ret = request_irq(irq, wbsd_irq, IRQF_SHARED, DRIVER_NAME, host);
	अगर (ret)
		वापस ret;

	host->irq = irq;

	वापस 0;
पूर्ण

अटल व्योम  wbsd_release_irq(काष्ठा wbsd_host *host)
अणु
	अगर (!host->irq)
		वापस;

	मुक्त_irq(host->irq, host);

	host->irq = 0;

	tasklet_समाप्त(&host->card_tasklet);
	tasklet_समाप्त(&host->fअगरo_tasklet);
	tasklet_समाप्त(&host->crc_tasklet);
	tasklet_समाप्त(&host->समयout_tasklet);
	tasklet_समाप्त(&host->finish_tasklet);
पूर्ण

/*
 * Allocate all resources क्रम the host.
 */

अटल पूर्णांक wbsd_request_resources(काष्ठा wbsd_host *host,
	पूर्णांक base, पूर्णांक irq, पूर्णांक dma)
अणु
	पूर्णांक ret;

	/*
	 * Allocate I/O ports.
	 */
	ret = wbsd_request_region(host, base);
	अगर (ret)
		वापस ret;

	/*
	 * Allocate पूर्णांकerrupt.
	 */
	ret = wbsd_request_irq(host, irq);
	अगर (ret)
		वापस ret;

	/*
	 * Allocate DMA.
	 */
	wbsd_request_dma(host, dma);

	वापस 0;
पूर्ण

/*
 * Release all resources क्रम the host.
 */

अटल व्योम wbsd_release_resources(काष्ठा wbsd_host *host)
अणु
	wbsd_release_dma(host);
	wbsd_release_irq(host);
	wbsd_release_regions(host);
पूर्ण

/*
 * Configure the resources the chip should use.
 */

अटल व्योम wbsd_chip_config(काष्ठा wbsd_host *host)
अणु
	wbsd_unlock_config(host);

	/*
	 * Reset the chip.
	 */
	wbsd_ग_लिखो_config(host, WBSD_CONF_SWRST, 1);
	wbsd_ग_लिखो_config(host, WBSD_CONF_SWRST, 0);

	/*
	 * Select SD/MMC function.
	 */
	wbsd_ग_लिखो_config(host, WBSD_CONF_DEVICE, DEVICE_SD);

	/*
	 * Set up card detection.
	 */
	wbsd_ग_लिखो_config(host, WBSD_CONF_PINS, WBSD_PINS_DETECT_GP11);

	/*
	 * Configure chip
	 */
	wbsd_ग_लिखो_config(host, WBSD_CONF_PORT_HI, host->base >> 8);
	wbsd_ग_लिखो_config(host, WBSD_CONF_PORT_LO, host->base & 0xff);

	wbsd_ग_लिखो_config(host, WBSD_CONF_IRQ, host->irq);

	अगर (host->dma >= 0)
		wbsd_ग_लिखो_config(host, WBSD_CONF_DRQ, host->dma);

	/*
	 * Enable and घातer up chip.
	 */
	wbsd_ग_लिखो_config(host, WBSD_CONF_ENABLE, 1);
	wbsd_ग_लिखो_config(host, WBSD_CONF_POWER, 0x20);

	wbsd_lock_config(host);
पूर्ण

/*
 * Check that configured resources are correct.
 */

अटल पूर्णांक wbsd_chip_validate(काष्ठा wbsd_host *host)
अणु
	पूर्णांक base, irq, dma;

	wbsd_unlock_config(host);

	/*
	 * Select SD/MMC function.
	 */
	wbsd_ग_लिखो_config(host, WBSD_CONF_DEVICE, DEVICE_SD);

	/*
	 * Read configuration.
	 */
	base = wbsd_पढ़ो_config(host, WBSD_CONF_PORT_HI) << 8;
	base |= wbsd_पढ़ो_config(host, WBSD_CONF_PORT_LO);

	irq = wbsd_पढ़ो_config(host, WBSD_CONF_IRQ);

	dma = wbsd_पढ़ो_config(host, WBSD_CONF_DRQ);

	wbsd_lock_config(host);

	/*
	 * Validate against given configuration.
	 */
	अगर (base != host->base)
		वापस 0;
	अगर (irq != host->irq)
		वापस 0;
	अगर ((dma != host->dma) && (host->dma != -1))
		वापस 0;

	वापस 1;
पूर्ण

/*
 * Powers करोwn the SD function
 */

अटल व्योम wbsd_chip_घातeroff(काष्ठा wbsd_host *host)
अणु
	wbsd_unlock_config(host);

	wbsd_ग_लिखो_config(host, WBSD_CONF_DEVICE, DEVICE_SD);
	wbsd_ग_लिखो_config(host, WBSD_CONF_ENABLE, 0);

	wbsd_lock_config(host);
पूर्ण

/*****************************************************************************\
 *                                                                           *
 * Devices setup and shutकरोwn                                                *
 *                                                                           *
\*****************************************************************************/

अटल पूर्णांक wbsd_init(काष्ठा device *dev, पूर्णांक base, पूर्णांक irq, पूर्णांक dma,
	पूर्णांक pnp)
अणु
	काष्ठा wbsd_host *host = शून्य;
	काष्ठा mmc_host *mmc = शून्य;
	पूर्णांक ret;

	ret = wbsd_alloc_mmc(dev);
	अगर (ret)
		वापस ret;

	mmc = dev_get_drvdata(dev);
	host = mmc_priv(mmc);

	/*
	 * Scan क्रम hardware.
	 */
	ret = wbsd_scan(host);
	अगर (ret) अणु
		अगर (pnp && (ret == -ENODEV)) अणु
			pr_warn(DRIVER_NAME ": Unable to confirm device presence - you may experience lock-ups\n");
		पूर्ण अन्यथा अणु
			wbsd_मुक्त_mmc(dev);
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * Request resources.
	 */
	ret = wbsd_request_resources(host, base, irq, dma);
	अगर (ret) अणु
		wbsd_release_resources(host);
		wbsd_मुक्त_mmc(dev);
		वापस ret;
	पूर्ण

	/*
	 * See अगर chip needs to be configured.
	 */
	अगर (pnp) अणु
		अगर ((host->config != 0) && !wbsd_chip_validate(host)) अणु
			pr_warn(DRIVER_NAME ": PnP active but chip not configured! You probably have a buggy BIOS. Configuring chip manually.\n");
			wbsd_chip_config(host);
		पूर्ण
	पूर्ण अन्यथा
		wbsd_chip_config(host);

	/*
	 * Power Management stuff. No idea how this works.
	 * Not tested.
	 */
#अगर_घोषित CONFIG_PM
	अगर (host->config) अणु
		wbsd_unlock_config(host);
		wbsd_ग_लिखो_config(host, WBSD_CONF_PME, 0xA0);
		wbsd_lock_config(host);
	पूर्ण
#पूर्ण_अगर
	/*
	 * Allow device to initialise itself properly.
	 */
	mdelay(5);

	/*
	 * Reset the chip पूर्णांकo a known state.
	 */
	wbsd_init_device(host);

	mmc_add_host(mmc);

	pr_info("%s: W83L51xD", mmc_hostname(mmc));
	अगर (host->chip_id != 0)
		prपूर्णांकk(" id %x", (पूर्णांक)host->chip_id);
	prपूर्णांकk(" at 0x%x irq %d", (पूर्णांक)host->base, (पूर्णांक)host->irq);
	अगर (host->dma >= 0)
		prपूर्णांकk(" dma %d", (पूर्णांक)host->dma);
	अन्यथा
		prपूर्णांकk(" FIFO");
	अगर (pnp)
		prपूर्णांकk(" PnP");
	prपूर्णांकk("\n");

	वापस 0;
पूर्ण

अटल व्योम wbsd_shutकरोwn(काष्ठा device *dev, पूर्णांक pnp)
अणु
	काष्ठा mmc_host *mmc = dev_get_drvdata(dev);
	काष्ठा wbsd_host *host;

	अगर (!mmc)
		वापस;

	host = mmc_priv(mmc);

	mmc_हटाओ_host(mmc);

	/*
	 * Power करोwn the SD/MMC function.
	 */
	अगर (!pnp)
		wbsd_chip_घातeroff(host);

	wbsd_release_resources(host);

	wbsd_मुक्त_mmc(dev);
पूर्ण

/*
 * Non-PnP
 */

अटल पूर्णांक wbsd_probe(काष्ठा platक्रमm_device *dev)
अणु
	/* Use the module parameters क्रम resources */
	वापस wbsd_init(&dev->dev, param_io, param_irq, param_dma, 0);
पूर्ण

अटल पूर्णांक wbsd_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	wbsd_shutकरोwn(&dev->dev, 0);

	वापस 0;
पूर्ण

/*
 * PnP
 */

#अगर_घोषित CONFIG_PNP

अटल पूर्णांक
wbsd_pnp_probe(काष्ठा pnp_dev *pnpdev, स्थिर काष्ठा pnp_device_id *dev_id)
अणु
	पूर्णांक io, irq, dma;

	/*
	 * Get resources from PnP layer.
	 */
	io = pnp_port_start(pnpdev, 0);
	irq = pnp_irq(pnpdev, 0);
	अगर (pnp_dma_valid(pnpdev, 0))
		dma = pnp_dma(pnpdev, 0);
	अन्यथा
		dma = -1;

	DBGF("PnP resources: port %3x irq %d dma %d\n", io, irq, dma);

	वापस wbsd_init(&pnpdev->dev, io, irq, dma, 1);
पूर्ण

अटल व्योम wbsd_pnp_हटाओ(काष्ठा pnp_dev *dev)
अणु
	wbsd_shutकरोwn(&dev->dev, 1);
पूर्ण

#पूर्ण_अगर /* CONFIG_PNP */

/*
 * Power management
 */

#अगर_घोषित CONFIG_PM

अटल पूर्णांक wbsd_platक्रमm_suspend(काष्ठा platक्रमm_device *dev,
				 pm_message_t state)
अणु
	काष्ठा mmc_host *mmc = platक्रमm_get_drvdata(dev);
	काष्ठा wbsd_host *host;

	अगर (mmc == शून्य)
		वापस 0;

	DBGF("Suspending...\n");

	host = mmc_priv(mmc);

	wbsd_chip_घातeroff(host);
	वापस 0;
पूर्ण

अटल पूर्णांक wbsd_platक्रमm_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा mmc_host *mmc = platक्रमm_get_drvdata(dev);
	काष्ठा wbsd_host *host;

	अगर (mmc == शून्य)
		वापस 0;

	DBGF("Resuming...\n");

	host = mmc_priv(mmc);

	wbsd_chip_config(host);

	/*
	 * Allow device to initialise itself properly.
	 */
	mdelay(5);

	wbsd_init_device(host);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PNP

अटल पूर्णांक wbsd_pnp_suspend(काष्ठा pnp_dev *pnp_dev, pm_message_t state)
अणु
	काष्ठा mmc_host *mmc = dev_get_drvdata(&pnp_dev->dev);

	अगर (mmc == शून्य)
		वापस 0;

	DBGF("Suspending...\n");
	वापस 0;
पूर्ण

अटल पूर्णांक wbsd_pnp_resume(काष्ठा pnp_dev *pnp_dev)
अणु
	काष्ठा mmc_host *mmc = dev_get_drvdata(&pnp_dev->dev);
	काष्ठा wbsd_host *host;

	अगर (mmc == शून्य)
		वापस 0;

	DBGF("Resuming...\n");

	host = mmc_priv(mmc);

	/*
	 * See अगर chip needs to be configured.
	 */
	अगर (host->config != 0) अणु
		अगर (!wbsd_chip_validate(host)) अणु
			pr_warn(DRIVER_NAME ": PnP active but chip not configured! You probably have a buggy BIOS. Configuring chip manually.\n");
			wbsd_chip_config(host);
		पूर्ण
	पूर्ण

	/*
	 * Allow device to initialise itself properly.
	 */
	mdelay(5);

	wbsd_init_device(host);
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PNP */

#अन्यथा /* CONFIG_PM */

#घोषणा wbsd_platक्रमm_suspend शून्य
#घोषणा wbsd_platक्रमm_resume शून्य

#घोषणा wbsd_pnp_suspend शून्य
#घोषणा wbsd_pnp_resume शून्य

#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा platक्रमm_device *wbsd_device;

अटल काष्ठा platक्रमm_driver wbsd_driver = अणु
	.probe		= wbsd_probe,
	.हटाओ		= wbsd_हटाओ,

	.suspend	= wbsd_platक्रमm_suspend,
	.resume		= wbsd_platक्रमm_resume,
	.driver		= अणु
		.name	= DRIVER_NAME,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_PNP

अटल काष्ठा pnp_driver wbsd_pnp_driver = अणु
	.name		= DRIVER_NAME,
	.id_table	= pnp_dev_table,
	.probe		= wbsd_pnp_probe,
	.हटाओ		= wbsd_pnp_हटाओ,

	.suspend	= wbsd_pnp_suspend,
	.resume		= wbsd_pnp_resume,
पूर्ण;

#पूर्ण_अगर /* CONFIG_PNP */

/*
 * Module loading/unloading
 */

अटल पूर्णांक __init wbsd_drv_init(व्योम)
अणु
	पूर्णांक result;

	pr_info(DRIVER_NAME
		": Winbond W83L51xD SD/MMC card interface driver\n");
	pr_info(DRIVER_NAME ": Copyright(c) Pierre Ossman\n");

#अगर_घोषित CONFIG_PNP

	अगर (!param_nopnp) अणु
		result = pnp_रेजिस्टर_driver(&wbsd_pnp_driver);
		अगर (result < 0)
			वापस result;
	पूर्ण
#पूर्ण_अगर /* CONFIG_PNP */

	अगर (param_nopnp) अणु
		result = platक्रमm_driver_रेजिस्टर(&wbsd_driver);
		अगर (result < 0)
			वापस result;

		wbsd_device = platक्रमm_device_alloc(DRIVER_NAME, -1);
		अगर (!wbsd_device) अणु
			platक्रमm_driver_unरेजिस्टर(&wbsd_driver);
			वापस -ENOMEM;
		पूर्ण

		result = platक्रमm_device_add(wbsd_device);
		अगर (result) अणु
			platक्रमm_device_put(wbsd_device);
			platक्रमm_driver_unरेजिस्टर(&wbsd_driver);
			वापस result;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास wbsd_drv_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_PNP

	अगर (!param_nopnp)
		pnp_unरेजिस्टर_driver(&wbsd_pnp_driver);

#पूर्ण_अगर /* CONFIG_PNP */

	अगर (param_nopnp) अणु
		platक्रमm_device_unरेजिस्टर(wbsd_device);

		platक्रमm_driver_unरेजिस्टर(&wbsd_driver);
	पूर्ण

	DBG("unloaded\n");
पूर्ण

module_init(wbsd_drv_init);
module_निकास(wbsd_drv_निकास);
#अगर_घोषित CONFIG_PNP
module_param_hw_named(nopnp, param_nopnp, uपूर्णांक, other, 0444);
#पूर्ण_अगर
module_param_hw_named(io, param_io, uपूर्णांक, ioport, 0444);
module_param_hw_named(irq, param_irq, uपूर्णांक, irq, 0444);
module_param_hw_named(dma, param_dma, पूर्णांक, dma, 0444);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pierre Ossman <pierre@ossman.eu>");
MODULE_DESCRIPTION("Winbond W83L51xD SD/MMC card interface driver");

#अगर_घोषित CONFIG_PNP
MODULE_PARM_DESC(nopnp, "Scan for device instead of relying on PNP. (default 0)");
#पूर्ण_अगर
MODULE_PARM_DESC(io, "I/O base to allocate. Must be 8 byte aligned. (default 0x248)");
MODULE_PARM_DESC(irq, "IRQ to allocate. (default 6)");
MODULE_PARM_DESC(dma, "DMA channel to allocate. -1 for no DMA. (default 2)");
