<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/mmc/host/omap.c
 *
 *  Copyright (C) 2004 Nokia Corporation
 *  Written by Tuukka Tikkanen and Juha Yrjथघlथअ<juha.yrjola@nokia.com>
 *  Misc hacks here and there by Tony Lindgren <tony@atomide.com>
 *  Other hacks (DMA, SD, etc) by David Brownell
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>
#समावेश <linux/of.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/clk.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_data/mmc-omap.h>


#घोषणा	OMAP_MMC_REG_CMD	0x00
#घोषणा	OMAP_MMC_REG_ARGL	0x01
#घोषणा	OMAP_MMC_REG_ARGH	0x02
#घोषणा	OMAP_MMC_REG_CON	0x03
#घोषणा	OMAP_MMC_REG_STAT	0x04
#घोषणा	OMAP_MMC_REG_IE		0x05
#घोषणा	OMAP_MMC_REG_CTO	0x06
#घोषणा	OMAP_MMC_REG_DTO	0x07
#घोषणा	OMAP_MMC_REG_DATA	0x08
#घोषणा	OMAP_MMC_REG_BLEN	0x09
#घोषणा	OMAP_MMC_REG_NBLK	0x0a
#घोषणा	OMAP_MMC_REG_BUF	0x0b
#घोषणा	OMAP_MMC_REG_SDIO	0x0d
#घोषणा	OMAP_MMC_REG_REV	0x0f
#घोषणा	OMAP_MMC_REG_RSP0	0x10
#घोषणा	OMAP_MMC_REG_RSP1	0x11
#घोषणा	OMAP_MMC_REG_RSP2	0x12
#घोषणा	OMAP_MMC_REG_RSP3	0x13
#घोषणा	OMAP_MMC_REG_RSP4	0x14
#घोषणा	OMAP_MMC_REG_RSP5	0x15
#घोषणा	OMAP_MMC_REG_RSP6	0x16
#घोषणा	OMAP_MMC_REG_RSP7	0x17
#घोषणा	OMAP_MMC_REG_IOSR	0x18
#घोषणा	OMAP_MMC_REG_SYSC	0x19
#घोषणा	OMAP_MMC_REG_SYSS	0x1a

#घोषणा	OMAP_MMC_STAT_CARD_ERR		(1 << 14)
#घोषणा	OMAP_MMC_STAT_CARD_IRQ		(1 << 13)
#घोषणा	OMAP_MMC_STAT_OCR_BUSY		(1 << 12)
#घोषणा	OMAP_MMC_STAT_A_EMPTY		(1 << 11)
#घोषणा	OMAP_MMC_STAT_A_FULL		(1 << 10)
#घोषणा	OMAP_MMC_STAT_CMD_CRC		(1 <<  8)
#घोषणा	OMAP_MMC_STAT_CMD_TOUT		(1 <<  7)
#घोषणा	OMAP_MMC_STAT_DATA_CRC		(1 <<  6)
#घोषणा	OMAP_MMC_STAT_DATA_TOUT		(1 <<  5)
#घोषणा	OMAP_MMC_STAT_END_BUSY		(1 <<  4)
#घोषणा	OMAP_MMC_STAT_END_OF_DATA	(1 <<  3)
#घोषणा	OMAP_MMC_STAT_CARD_BUSY		(1 <<  2)
#घोषणा	OMAP_MMC_STAT_END_OF_CMD	(1 <<  0)

#घोषणा mmc_omap7xx()	(host->features & MMC_OMAP7XX)
#घोषणा mmc_omap15xx()	(host->features & MMC_OMAP15XX)
#घोषणा mmc_omap16xx()	(host->features & MMC_OMAP16XX)
#घोषणा MMC_OMAP1_MASK	(MMC_OMAP7XX | MMC_OMAP15XX | MMC_OMAP16XX)
#घोषणा mmc_omap1()	(host->features & MMC_OMAP1_MASK)
#घोषणा mmc_omap2()	(!mmc_omap1())

#घोषणा OMAP_MMC_REG(host, reg)		(OMAP_MMC_REG_##reg << (host)->reg_shअगरt)
#घोषणा OMAP_MMC_READ(host, reg)	__raw_पढ़ोw((host)->virt_base + OMAP_MMC_REG(host, reg))
#घोषणा OMAP_MMC_WRITE(host, reg, val)	__raw_ग_लिखोw((val), (host)->virt_base + OMAP_MMC_REG(host, reg))

/*
 * Command types
 */
#घोषणा OMAP_MMC_CMDTYPE_BC	0
#घोषणा OMAP_MMC_CMDTYPE_BCR	1
#घोषणा OMAP_MMC_CMDTYPE_AC	2
#घोषणा OMAP_MMC_CMDTYPE_ADTC	3

#घोषणा DRIVER_NAME "mmci-omap"

/* Specअगरies how often in millisecs to poll क्रम card status changes
 * when the cover चयन is खोलो */
#घोषणा OMAP_MMC_COVER_POLL_DELAY	500

काष्ठा mmc_omap_host;

काष्ठा mmc_omap_slot अणु
	पूर्णांक			id;
	अचिन्हित पूर्णांक		vdd;
	u16			saved_con;
	u16			bus_mode;
	u16			घातer_mode;
	अचिन्हित पूर्णांक		fclk_freq;

	काष्ठा tasklet_काष्ठा	cover_tasklet;
	काष्ठा समयr_list       cover_समयr;
	अचिन्हित		cover_खोलो;

	काष्ठा mmc_request      *mrq;
	काष्ठा mmc_omap_host    *host;
	काष्ठा mmc_host		*mmc;
	काष्ठा omap_mmc_slot_data *pdata;
पूर्ण;

काष्ठा mmc_omap_host अणु
	पूर्णांक			initialized;
	काष्ठा mmc_request *	mrq;
	काष्ठा mmc_command *	cmd;
	काष्ठा mmc_data *	data;
	काष्ठा mmc_host *	mmc;
	काष्ठा device *		dev;
	अचिन्हित अक्षर		id; /* 16xx chips have 2 MMC blocks */
	काष्ठा clk *		iclk;
	काष्ठा clk *		fclk;
	काष्ठा dma_chan		*dma_rx;
	u32			dma_rx_burst;
	काष्ठा dma_chan		*dma_tx;
	u32			dma_tx_burst;
	व्योम __iomem		*virt_base;
	अचिन्हित पूर्णांक		phys_base;
	पूर्णांक			irq;
	अचिन्हित अक्षर		bus_mode;
	अचिन्हित पूर्णांक		reg_shअगरt;

	काष्ठा work_काष्ठा	cmd_पात_work;
	अचिन्हित		पात:1;
	काष्ठा समयr_list	cmd_पात_समयr;

	काष्ठा work_काष्ठा      slot_release_work;
	काष्ठा mmc_omap_slot    *next_slot;
	काष्ठा work_काष्ठा      send_stop_work;
	काष्ठा mmc_data		*stop_data;

	अचिन्हित पूर्णांक		sg_len;
	पूर्णांक			sg_idx;
	u16 *			buffer;
	u32			buffer_bytes_left;
	u32			total_bytes_left;

	अचिन्हित		features;
	अचिन्हित		brs_received:1, dma_करोne:1;
	अचिन्हित		dma_in_use:1;
	spinlock_t		dma_lock;

	काष्ठा mmc_omap_slot    *slots[OMAP_MMC_MAX_SLOTS];
	काष्ठा mmc_omap_slot    *current_slot;
	spinlock_t              slot_lock;
	रुको_queue_head_t       slot_wq;
	पूर्णांक                     nr_slots;

	काष्ठा समयr_list       clk_समयr;
	spinlock_t		clk_lock;     /* क्रम changing enabled state */
	अचिन्हित पूर्णांक            fclk_enabled:1;
	काष्ठा workqueue_काष्ठा *mmc_omap_wq;

	काष्ठा omap_mmc_platक्रमm_data *pdata;
पूर्ण;


अटल व्योम mmc_omap_fclk_offdelay(काष्ठा mmc_omap_slot *slot)
अणु
	अचिन्हित दीर्घ tick_ns;

	अगर (slot != शून्य && slot->host->fclk_enabled && slot->fclk_freq > 0) अणु
		tick_ns = DIV_ROUND_UP(NSEC_PER_SEC, slot->fclk_freq);
		ndelay(8 * tick_ns);
	पूर्ण
पूर्ण

अटल व्योम mmc_omap_fclk_enable(काष्ठा mmc_omap_host *host, अचिन्हित पूर्णांक enable)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->clk_lock, flags);
	अगर (host->fclk_enabled != enable) अणु
		host->fclk_enabled = enable;
		अगर (enable)
			clk_enable(host->fclk);
		अन्यथा
			clk_disable(host->fclk);
	पूर्ण
	spin_unlock_irqrestore(&host->clk_lock, flags);
पूर्ण

अटल व्योम mmc_omap_select_slot(काष्ठा mmc_omap_slot *slot, पूर्णांक claimed)
अणु
	काष्ठा mmc_omap_host *host = slot->host;
	अचिन्हित दीर्घ flags;

	अगर (claimed)
		जाओ no_claim;
	spin_lock_irqsave(&host->slot_lock, flags);
	जबतक (host->mmc != शून्य) अणु
		spin_unlock_irqrestore(&host->slot_lock, flags);
		रुको_event(host->slot_wq, host->mmc == शून्य);
		spin_lock_irqsave(&host->slot_lock, flags);
	पूर्ण
	host->mmc = slot->mmc;
	spin_unlock_irqrestore(&host->slot_lock, flags);
no_claim:
	del_समयr(&host->clk_समयr);
	अगर (host->current_slot != slot || !claimed)
		mmc_omap_fclk_offdelay(host->current_slot);

	अगर (host->current_slot != slot) अणु
		OMAP_MMC_WRITE(host, CON, slot->saved_con & 0xFC00);
		अगर (host->pdata->चयन_slot != शून्य)
			host->pdata->चयन_slot(mmc_dev(slot->mmc), slot->id);
		host->current_slot = slot;
	पूर्ण

	अगर (claimed) अणु
		mmc_omap_fclk_enable(host, 1);

		/* Doing the dummy पढ़ो here seems to work around some bug
		 * at least in OMAP24xx silicon where the command would not
		 * start after writing the CMD रेजिस्टर. Sigh. */
		OMAP_MMC_READ(host, CON);

		OMAP_MMC_WRITE(host, CON, slot->saved_con);
	पूर्ण अन्यथा
		mmc_omap_fclk_enable(host, 0);
पूर्ण

अटल व्योम mmc_omap_start_request(काष्ठा mmc_omap_host *host,
				   काष्ठा mmc_request *req);

अटल व्योम mmc_omap_slot_release_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mmc_omap_host *host = container_of(work, काष्ठा mmc_omap_host,
						  slot_release_work);
	काष्ठा mmc_omap_slot *next_slot = host->next_slot;
	काष्ठा mmc_request *rq;

	host->next_slot = शून्य;
	mmc_omap_select_slot(next_slot, 1);

	rq = next_slot->mrq;
	next_slot->mrq = शून्य;
	mmc_omap_start_request(host, rq);
पूर्ण

अटल व्योम mmc_omap_release_slot(काष्ठा mmc_omap_slot *slot, पूर्णांक clk_enabled)
अणु
	काष्ठा mmc_omap_host *host = slot->host;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	BUG_ON(slot == शून्य || host->mmc == शून्य);

	अगर (clk_enabled)
		/* Keeps घड़ी running क्रम at least 8 cycles on valid freq */
		mod_समयr(&host->clk_समयr, jअगरfies  + HZ/10);
	अन्यथा अणु
		del_समयr(&host->clk_समयr);
		mmc_omap_fclk_offdelay(slot);
		mmc_omap_fclk_enable(host, 0);
	पूर्ण

	spin_lock_irqsave(&host->slot_lock, flags);
	/* Check क्रम any pending requests */
	क्रम (i = 0; i < host->nr_slots; i++) अणु
		काष्ठा mmc_omap_slot *new_slot;

		अगर (host->slots[i] == शून्य || host->slots[i]->mrq == शून्य)
			जारी;

		BUG_ON(host->next_slot != शून्य);
		new_slot = host->slots[i];
		/* The current slot should not have a request in queue */
		BUG_ON(new_slot == host->current_slot);

		host->next_slot = new_slot;
		host->mmc = new_slot->mmc;
		spin_unlock_irqrestore(&host->slot_lock, flags);
		queue_work(host->mmc_omap_wq, &host->slot_release_work);
		वापस;
	पूर्ण

	host->mmc = शून्य;
	wake_up(&host->slot_wq);
	spin_unlock_irqrestore(&host->slot_lock, flags);
पूर्ण

अटल अंतरभूत
पूर्णांक mmc_omap_cover_is_खोलो(काष्ठा mmc_omap_slot *slot)
अणु
	अगर (slot->pdata->get_cover_state)
		वापस slot->pdata->get_cover_state(mmc_dev(slot->mmc),
						    slot->id);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार
mmc_omap_show_cover_चयन(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा mmc_host *mmc = container_of(dev, काष्ठा mmc_host, class_dev);
	काष्ठा mmc_omap_slot *slot = mmc_priv(mmc);

	वापस प्र_लिखो(buf, "%s\n", mmc_omap_cover_is_खोलो(slot) ? "open" :
		       "closed");
पूर्ण

अटल DEVICE_ATTR(cover_चयन, S_IRUGO, mmc_omap_show_cover_चयन, शून्य);

अटल sमाप_प्रकार
mmc_omap_show_slot_name(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा mmc_host *mmc = container_of(dev, काष्ठा mmc_host, class_dev);
	काष्ठा mmc_omap_slot *slot = mmc_priv(mmc);

	वापस प्र_लिखो(buf, "%s\n", slot->pdata->name);
पूर्ण

अटल DEVICE_ATTR(slot_name, S_IRUGO, mmc_omap_show_slot_name, शून्य);

अटल व्योम
mmc_omap_start_command(काष्ठा mmc_omap_host *host, काष्ठा mmc_command *cmd)
अणु
	u32 cmdreg;
	u32 resptype;
	u32 cmdtype;
	u16 irq_mask;

	host->cmd = cmd;

	resptype = 0;
	cmdtype = 0;

	/* Our hardware needs to know exact type */
	चयन (mmc_resp_type(cmd)) अणु
	हाल MMC_RSP_NONE:
		अवरोध;
	हाल MMC_RSP_R1:
	हाल MMC_RSP_R1B:
		/* resp 1, 1b, 6, 7 */
		resptype = 1;
		अवरोध;
	हाल MMC_RSP_R2:
		resptype = 2;
		अवरोध;
	हाल MMC_RSP_R3:
		resptype = 3;
		अवरोध;
	शेष:
		dev_err(mmc_dev(host->mmc), "Invalid response type: %04x\n", mmc_resp_type(cmd));
		अवरोध;
	पूर्ण

	अगर (mmc_cmd_type(cmd) == MMC_CMD_ADTC) अणु
		cmdtype = OMAP_MMC_CMDTYPE_ADTC;
	पूर्ण अन्यथा अगर (mmc_cmd_type(cmd) == MMC_CMD_BC) अणु
		cmdtype = OMAP_MMC_CMDTYPE_BC;
	पूर्ण अन्यथा अगर (mmc_cmd_type(cmd) == MMC_CMD_BCR) अणु
		cmdtype = OMAP_MMC_CMDTYPE_BCR;
	पूर्ण अन्यथा अणु
		cmdtype = OMAP_MMC_CMDTYPE_AC;
	पूर्ण

	cmdreg = cmd->opcode | (resptype << 8) | (cmdtype << 12);

	अगर (host->current_slot->bus_mode == MMC_BUSMODE_OPENDRAIN)
		cmdreg |= 1 << 6;

	अगर (cmd->flags & MMC_RSP_BUSY)
		cmdreg |= 1 << 11;

	अगर (host->data && !(host->data->flags & MMC_DATA_WRITE))
		cmdreg |= 1 << 15;

	mod_समयr(&host->cmd_पात_समयr, jअगरfies + HZ/2);

	OMAP_MMC_WRITE(host, CTO, 200);
	OMAP_MMC_WRITE(host, ARGL, cmd->arg & 0xffff);
	OMAP_MMC_WRITE(host, ARGH, cmd->arg >> 16);
	irq_mask = OMAP_MMC_STAT_A_EMPTY    | OMAP_MMC_STAT_A_FULL    |
		   OMAP_MMC_STAT_CMD_CRC    | OMAP_MMC_STAT_CMD_TOUT  |
		   OMAP_MMC_STAT_DATA_CRC   | OMAP_MMC_STAT_DATA_TOUT |
		   OMAP_MMC_STAT_END_OF_CMD | OMAP_MMC_STAT_CARD_ERR  |
		   OMAP_MMC_STAT_END_OF_DATA;
	अगर (cmd->opcode == MMC_ERASE)
		irq_mask &= ~OMAP_MMC_STAT_DATA_TOUT;
	OMAP_MMC_WRITE(host, IE, irq_mask);
	OMAP_MMC_WRITE(host, CMD, cmdreg);
पूर्ण

अटल व्योम
mmc_omap_release_dma(काष्ठा mmc_omap_host *host, काष्ठा mmc_data *data,
		     पूर्णांक पात)
अणु
	क्रमागत dma_data_direction dma_data_dir;
	काष्ठा device *dev = mmc_dev(host->mmc);
	काष्ठा dma_chan *c;

	अगर (data->flags & MMC_DATA_WRITE) अणु
		dma_data_dir = DMA_TO_DEVICE;
		c = host->dma_tx;
	पूर्ण अन्यथा अणु
		dma_data_dir = DMA_FROM_DEVICE;
		c = host->dma_rx;
	पूर्ण
	अगर (c) अणु
		अगर (data->error) अणु
			dmaengine_terminate_all(c);
			/* Claim nothing transferred on error... */
			data->bytes_xfered = 0;
		पूर्ण
		dev = c->device->dev;
	पूर्ण
	dma_unmap_sg(dev, data->sg, host->sg_len, dma_data_dir);
पूर्ण

अटल व्योम mmc_omap_send_stop_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mmc_omap_host *host = container_of(work, काष्ठा mmc_omap_host,
						  send_stop_work);
	काष्ठा mmc_omap_slot *slot = host->current_slot;
	काष्ठा mmc_data *data = host->stop_data;
	अचिन्हित दीर्घ tick_ns;

	tick_ns = DIV_ROUND_UP(NSEC_PER_SEC, slot->fclk_freq);
	ndelay(8*tick_ns);

	mmc_omap_start_command(host, data->stop);
पूर्ण

अटल व्योम
mmc_omap_xfer_करोne(काष्ठा mmc_omap_host *host, काष्ठा mmc_data *data)
अणु
	अगर (host->dma_in_use)
		mmc_omap_release_dma(host, data, data->error);

	host->data = शून्य;
	host->sg_len = 0;

	/* NOTE:  MMC layer will someबार poll-रुको CMD13 next, issuing
	 * करोzens of requests until the card finishes writing data.
	 * It'd be cheaper to just रुको till an खातापूर्णB पूर्णांकerrupt arrives...
	 */

	अगर (!data->stop) अणु
		काष्ठा mmc_host *mmc;

		host->mrq = शून्य;
		mmc = host->mmc;
		mmc_omap_release_slot(host->current_slot, 1);
		mmc_request_करोne(mmc, data->mrq);
		वापस;
	पूर्ण

	host->stop_data = data;
	queue_work(host->mmc_omap_wq, &host->send_stop_work);
पूर्ण

अटल व्योम
mmc_omap_send_पात(काष्ठा mmc_omap_host *host, पूर्णांक maxloops)
अणु
	काष्ठा mmc_omap_slot *slot = host->current_slot;
	अचिन्हित पूर्णांक restarts, passes, समयout;
	u16 stat = 0;

	/* Sending पात takes 80 घड़ीs. Have some extra and round up */
	समयout = DIV_ROUND_UP(120 * USEC_PER_SEC, slot->fclk_freq);
	restarts = 0;
	जबतक (restarts < maxloops) अणु
		OMAP_MMC_WRITE(host, STAT, 0xFFFF);
		OMAP_MMC_WRITE(host, CMD, (3 << 12) | (1 << 7));

		passes = 0;
		जबतक (passes < समयout) अणु
			stat = OMAP_MMC_READ(host, STAT);
			अगर (stat & OMAP_MMC_STAT_END_OF_CMD)
				जाओ out;
			udelay(1);
			passes++;
		पूर्ण

		restarts++;
	पूर्ण
out:
	OMAP_MMC_WRITE(host, STAT, stat);
पूर्ण

अटल व्योम
mmc_omap_पात_xfer(काष्ठा mmc_omap_host *host, काष्ठा mmc_data *data)
अणु
	अगर (host->dma_in_use)
		mmc_omap_release_dma(host, data, 1);

	host->data = शून्य;
	host->sg_len = 0;

	mmc_omap_send_पात(host, 10000);
पूर्ण

अटल व्योम
mmc_omap_end_of_data(काष्ठा mmc_omap_host *host, काष्ठा mmc_data *data)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक करोne;

	अगर (!host->dma_in_use) अणु
		mmc_omap_xfer_करोne(host, data);
		वापस;
	पूर्ण
	करोne = 0;
	spin_lock_irqsave(&host->dma_lock, flags);
	अगर (host->dma_करोne)
		करोne = 1;
	अन्यथा
		host->brs_received = 1;
	spin_unlock_irqrestore(&host->dma_lock, flags);
	अगर (करोne)
		mmc_omap_xfer_करोne(host, data);
पूर्ण

अटल व्योम
mmc_omap_dma_करोne(काष्ठा mmc_omap_host *host, काष्ठा mmc_data *data)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक करोne;

	करोne = 0;
	spin_lock_irqsave(&host->dma_lock, flags);
	अगर (host->brs_received)
		करोne = 1;
	अन्यथा
		host->dma_करोne = 1;
	spin_unlock_irqrestore(&host->dma_lock, flags);
	अगर (करोne)
		mmc_omap_xfer_करोne(host, data);
पूर्ण

अटल व्योम
mmc_omap_cmd_करोne(काष्ठा mmc_omap_host *host, काष्ठा mmc_command *cmd)
अणु
	host->cmd = शून्य;

	del_समयr(&host->cmd_पात_समयr);

	अगर (cmd->flags & MMC_RSP_PRESENT) अणु
		अगर (cmd->flags & MMC_RSP_136) अणु
			/* response type 2 */
			cmd->resp[3] =
				OMAP_MMC_READ(host, RSP0) |
				(OMAP_MMC_READ(host, RSP1) << 16);
			cmd->resp[2] =
				OMAP_MMC_READ(host, RSP2) |
				(OMAP_MMC_READ(host, RSP3) << 16);
			cmd->resp[1] =
				OMAP_MMC_READ(host, RSP4) |
				(OMAP_MMC_READ(host, RSP5) << 16);
			cmd->resp[0] =
				OMAP_MMC_READ(host, RSP6) |
				(OMAP_MMC_READ(host, RSP7) << 16);
		पूर्ण अन्यथा अणु
			/* response types 1, 1b, 3, 4, 5, 6 */
			cmd->resp[0] =
				OMAP_MMC_READ(host, RSP6) |
				(OMAP_MMC_READ(host, RSP7) << 16);
		पूर्ण
	पूर्ण

	अगर (host->data == शून्य || cmd->error) अणु
		काष्ठा mmc_host *mmc;

		अगर (host->data != शून्य)
			mmc_omap_पात_xfer(host, host->data);
		host->mrq = शून्य;
		mmc = host->mmc;
		mmc_omap_release_slot(host->current_slot, 1);
		mmc_request_करोne(mmc, cmd->mrq);
	पूर्ण
पूर्ण

/*
 * Abort stuck command. Can occur when card is हटाओd जबतक it is being
 * पढ़ो.
 */
अटल व्योम mmc_omap_पात_command(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mmc_omap_host *host = container_of(work, काष्ठा mmc_omap_host,
						  cmd_पात_work);
	BUG_ON(!host->cmd);

	dev_dbg(mmc_dev(host->mmc), "Aborting stuck command CMD%d\n",
		host->cmd->opcode);

	अगर (host->cmd->error == 0)
		host->cmd->error = -ETIMEDOUT;

	अगर (host->data == शून्य) अणु
		काष्ठा mmc_command *cmd;
		काष्ठा mmc_host    *mmc;

		cmd = host->cmd;
		host->cmd = शून्य;
		mmc_omap_send_पात(host, 10000);

		host->mrq = शून्य;
		mmc = host->mmc;
		mmc_omap_release_slot(host->current_slot, 1);
		mmc_request_करोne(mmc, cmd->mrq);
	पूर्ण अन्यथा
		mmc_omap_cmd_करोne(host, host->cmd);

	host->पात = 0;
	enable_irq(host->irq);
पूर्ण

अटल व्योम
mmc_omap_cmd_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा mmc_omap_host *host = from_समयr(host, t, cmd_पात_समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->slot_lock, flags);
	अगर (host->cmd != शून्य && !host->पात) अणु
		OMAP_MMC_WRITE(host, IE, 0);
		disable_irq(host->irq);
		host->पात = 1;
		queue_work(host->mmc_omap_wq, &host->cmd_पात_work);
	पूर्ण
	spin_unlock_irqrestore(&host->slot_lock, flags);
पूर्ण

/* PIO only */
अटल व्योम
mmc_omap_sg_to_buf(काष्ठा mmc_omap_host *host)
अणु
	काष्ठा scatterlist *sg;

	sg = host->data->sg + host->sg_idx;
	host->buffer_bytes_left = sg->length;
	host->buffer = sg_virt(sg);
	अगर (host->buffer_bytes_left > host->total_bytes_left)
		host->buffer_bytes_left = host->total_bytes_left;
पूर्ण

अटल व्योम
mmc_omap_clk_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा mmc_omap_host *host = from_समयr(host, t, clk_समयr);

	mmc_omap_fclk_enable(host, 0);
पूर्ण

/* PIO only */
अटल व्योम
mmc_omap_xfer_data(काष्ठा mmc_omap_host *host, पूर्णांक ग_लिखो)
अणु
	पूर्णांक n, nwords;

	अगर (host->buffer_bytes_left == 0) अणु
		host->sg_idx++;
		BUG_ON(host->sg_idx == host->sg_len);
		mmc_omap_sg_to_buf(host);
	पूर्ण
	n = 64;
	अगर (n > host->buffer_bytes_left)
		n = host->buffer_bytes_left;

	/* Round up to handle odd number of bytes to transfer */
	nwords = DIV_ROUND_UP(n, 2);

	host->buffer_bytes_left -= n;
	host->total_bytes_left -= n;
	host->data->bytes_xfered += n;

	अगर (ग_लिखो) अणु
		__raw_ग_लिखोsw(host->virt_base + OMAP_MMC_REG(host, DATA),
			      host->buffer, nwords);
	पूर्ण अन्यथा अणु
		__raw_पढ़ोsw(host->virt_base + OMAP_MMC_REG(host, DATA),
			     host->buffer, nwords);
	पूर्ण

	host->buffer += nwords;
पूर्ण

#अगर_घोषित CONFIG_MMC_DEBUG
अटल व्योम mmc_omap_report_irq(काष्ठा mmc_omap_host *host, u16 status)
अणु
	अटल स्थिर अक्षर *mmc_omap_status_bits[] = अणु
		"EOC", "CD", "CB", "BRS", "EOFB", "DTO", "DCRC", "CTO",
		"CCRC", "CRW", "AF", "AE", "OCRB", "CIRQ", "CERR"
	पूर्ण;
	पूर्णांक i;
	अक्षर res[64], *buf = res;

	buf += प्र_लिखो(buf, "MMC IRQ 0x%x:", status);

	क्रम (i = 0; i < ARRAY_SIZE(mmc_omap_status_bits); i++)
		अगर (status & (1 << i))
			buf += प्र_लिखो(buf, " %s", mmc_omap_status_bits[i]);
	dev_vdbg(mmc_dev(host->mmc), "%s\n", res);
पूर्ण
#अन्यथा
अटल व्योम mmc_omap_report_irq(काष्ठा mmc_omap_host *host, u16 status)
अणु
पूर्ण
#पूर्ण_अगर


अटल irqवापस_t mmc_omap_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mmc_omap_host * host = (काष्ठा mmc_omap_host *)dev_id;
	u16 status;
	पूर्णांक end_command;
	पूर्णांक end_transfer;
	पूर्णांक transfer_error, cmd_error;

	अगर (host->cmd == शून्य && host->data == शून्य) अणु
		status = OMAP_MMC_READ(host, STAT);
		dev_info(mmc_dev(host->slots[0]->mmc),
			 "Spurious IRQ 0x%04x\n", status);
		अगर (status != 0) अणु
			OMAP_MMC_WRITE(host, STAT, status);
			OMAP_MMC_WRITE(host, IE, 0);
		पूर्ण
		वापस IRQ_HANDLED;
	पूर्ण

	end_command = 0;
	end_transfer = 0;
	transfer_error = 0;
	cmd_error = 0;

	जबतक ((status = OMAP_MMC_READ(host, STAT)) != 0) अणु
		पूर्णांक cmd;

		OMAP_MMC_WRITE(host, STAT, status);
		अगर (host->cmd != शून्य)
			cmd = host->cmd->opcode;
		अन्यथा
			cmd = -1;
		dev_dbg(mmc_dev(host->mmc), "MMC IRQ %04x (CMD %d): ",
			status, cmd);
		mmc_omap_report_irq(host, status);

		अगर (host->total_bytes_left) अणु
			अगर ((status & OMAP_MMC_STAT_A_FULL) ||
			    (status & OMAP_MMC_STAT_END_OF_DATA))
				mmc_omap_xfer_data(host, 0);
			अगर (status & OMAP_MMC_STAT_A_EMPTY)
				mmc_omap_xfer_data(host, 1);
		पूर्ण

		अगर (status & OMAP_MMC_STAT_END_OF_DATA)
			end_transfer = 1;

		अगर (status & OMAP_MMC_STAT_DATA_TOUT) अणु
			dev_dbg(mmc_dev(host->mmc), "data timeout (CMD%d)\n",
				cmd);
			अगर (host->data) अणु
				host->data->error = -ETIMEDOUT;
				transfer_error = 1;
			पूर्ण
		पूर्ण

		अगर (status & OMAP_MMC_STAT_DATA_CRC) अणु
			अगर (host->data) अणु
				host->data->error = -EILSEQ;
				dev_dbg(mmc_dev(host->mmc),
					 "data CRC error, bytes left %d\n",
					host->total_bytes_left);
				transfer_error = 1;
			पूर्ण अन्यथा अणु
				dev_dbg(mmc_dev(host->mmc), "data CRC error\n");
			पूर्ण
		पूर्ण

		अगर (status & OMAP_MMC_STAT_CMD_TOUT) अणु
			/* Timeouts are routine with some commands */
			अगर (host->cmd) अणु
				काष्ठा mmc_omap_slot *slot =
					host->current_slot;
				अगर (slot == शून्य ||
				    !mmc_omap_cover_is_खोलो(slot))
					dev_err(mmc_dev(host->mmc),
						"command timeout (CMD%d)\n",
						cmd);
				host->cmd->error = -ETIMEDOUT;
				end_command = 1;
				cmd_error = 1;
			पूर्ण
		पूर्ण

		अगर (status & OMAP_MMC_STAT_CMD_CRC) अणु
			अगर (host->cmd) अणु
				dev_err(mmc_dev(host->mmc),
					"command CRC error (CMD%d, arg 0x%08x)\n",
					cmd, host->cmd->arg);
				host->cmd->error = -EILSEQ;
				end_command = 1;
				cmd_error = 1;
			पूर्ण अन्यथा
				dev_err(mmc_dev(host->mmc),
					"command CRC error without cmd?\n");
		पूर्ण

		अगर (status & OMAP_MMC_STAT_CARD_ERR) अणु
			dev_dbg(mmc_dev(host->mmc),
				"ignoring card status error (CMD%d)\n",
				cmd);
			end_command = 1;
		पूर्ण

		/*
		 * NOTE: On 1610 the END_OF_CMD may come too early when
		 * starting a ग_लिखो
		 */
		अगर ((status & OMAP_MMC_STAT_END_OF_CMD) &&
		    (!(status & OMAP_MMC_STAT_A_EMPTY))) अणु
			end_command = 1;
		पूर्ण
	पूर्ण

	अगर (cmd_error && host->data) अणु
		del_समयr(&host->cmd_पात_समयr);
		host->पात = 1;
		OMAP_MMC_WRITE(host, IE, 0);
		disable_irq_nosync(host->irq);
		queue_work(host->mmc_omap_wq, &host->cmd_पात_work);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (end_command && host->cmd)
		mmc_omap_cmd_करोne(host, host->cmd);
	अगर (host->data != शून्य) अणु
		अगर (transfer_error)
			mmc_omap_xfer_करोne(host, host->data);
		अन्यथा अगर (end_transfer)
			mmc_omap_end_of_data(host, host->data);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

व्योम omap_mmc_notअगरy_cover_event(काष्ठा device *dev, पूर्णांक num, पूर्णांक is_बंदd)
अणु
	पूर्णांक cover_खोलो;
	काष्ठा mmc_omap_host *host = dev_get_drvdata(dev);
	काष्ठा mmc_omap_slot *slot = host->slots[num];

	BUG_ON(num >= host->nr_slots);

	/* Other subप्रणालीs can call in here beक्रमe we're initialised. */
	अगर (host->nr_slots == 0 || !host->slots[num])
		वापस;

	cover_खोलो = mmc_omap_cover_is_खोलो(slot);
	अगर (cover_खोलो != slot->cover_खोलो) अणु
		slot->cover_खोलो = cover_खोलो;
		sysfs_notअगरy(&slot->mmc->class_dev.kobj, शून्य, "cover_switch");
	पूर्ण

	tasklet_hi_schedule(&slot->cover_tasklet);
पूर्ण

अटल व्योम mmc_omap_cover_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा mmc_omap_slot *slot = from_समयr(slot, t, cover_समयr);
	tasklet_schedule(&slot->cover_tasklet);
पूर्ण

अटल व्योम mmc_omap_cover_handler(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा mmc_omap_slot *slot = from_tasklet(slot, t, cover_tasklet);
	पूर्णांक cover_खोलो = mmc_omap_cover_is_खोलो(slot);

	mmc_detect_change(slot->mmc, 0);
	अगर (!cover_खोलो)
		वापस;

	/*
	 * If no card is inserted, we postpone polling until
	 * the cover has been बंदd.
	 */
	अगर (slot->mmc->card == शून्य)
		वापस;

	mod_समयr(&slot->cover_समयr,
		  jअगरfies + msecs_to_jअगरfies(OMAP_MMC_COVER_POLL_DELAY));
पूर्ण

अटल व्योम mmc_omap_dma_callback(व्योम *priv)
अणु
	काष्ठा mmc_omap_host *host = priv;
	काष्ठा mmc_data *data = host->data;

	/* If we got to the end of DMA, assume everything went well */
	data->bytes_xfered += data->blocks * data->blksz;

	mmc_omap_dma_करोne(host, data);
पूर्ण

अटल अंतरभूत व्योम set_cmd_समयout(काष्ठा mmc_omap_host *host, काष्ठा mmc_request *req)
अणु
	u16 reg;

	reg = OMAP_MMC_READ(host, SDIO);
	reg &= ~(1 << 5);
	OMAP_MMC_WRITE(host, SDIO, reg);
	/* Set maximum समयout */
	OMAP_MMC_WRITE(host, CTO, 0xfd);
पूर्ण

अटल अंतरभूत व्योम set_data_समयout(काष्ठा mmc_omap_host *host, काष्ठा mmc_request *req)
अणु
	अचिन्हित पूर्णांक समयout, cycle_ns;
	u16 reg;

	cycle_ns = 1000000000 / host->current_slot->fclk_freq;
	समयout = req->data->समयout_ns / cycle_ns;
	समयout += req->data->समयout_clks;

	/* Check अगर we need to use समयout multiplier रेजिस्टर */
	reg = OMAP_MMC_READ(host, SDIO);
	अगर (समयout > 0xffff) अणु
		reg |= (1 << 5);
		समयout /= 1024;
	पूर्ण अन्यथा
		reg &= ~(1 << 5);
	OMAP_MMC_WRITE(host, SDIO, reg);
	OMAP_MMC_WRITE(host, DTO, समयout);
पूर्ण

अटल व्योम
mmc_omap_prepare_data(काष्ठा mmc_omap_host *host, काष्ठा mmc_request *req)
अणु
	काष्ठा mmc_data *data = req->data;
	पूर्णांक i, use_dma = 1, block_size;
	काष्ठा scatterlist *sg;
	अचिन्हित sg_len;

	host->data = data;
	अगर (data == शून्य) अणु
		OMAP_MMC_WRITE(host, BLEN, 0);
		OMAP_MMC_WRITE(host, NBLK, 0);
		OMAP_MMC_WRITE(host, BUF, 0);
		host->dma_in_use = 0;
		set_cmd_समयout(host, req);
		वापस;
	पूर्ण

	block_size = data->blksz;

	OMAP_MMC_WRITE(host, NBLK, data->blocks - 1);
	OMAP_MMC_WRITE(host, BLEN, block_size - 1);
	set_data_समयout(host, req);

	/* cope with calling layer confusion; it issues "single
	 * block" ग_लिखोs using multi-block scatterlists.
	 */
	sg_len = (data->blocks == 1) ? 1 : data->sg_len;

	/* Only करो DMA क्रम entire blocks */
	क्रम_each_sg(data->sg, sg, sg_len, i) अणु
		अगर ((sg->length % block_size) != 0) अणु
			use_dma = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	host->sg_idx = 0;
	अगर (use_dma) अणु
		क्रमागत dma_data_direction dma_data_dir;
		काष्ठा dma_async_tx_descriptor *tx;
		काष्ठा dma_chan *c;
		u32 burst, *bp;
		u16 buf;

		/*
		 * FIFO is 16x2 bytes on 15xx, and 32x2 bytes on 16xx
		 * and 24xx. Use 16 or 32 word frames when the
		 * blocksize is at least that large. Blocksize is
		 * usually 512 bytes; but not क्रम some SD पढ़ोs.
		 */
		burst = mmc_omap15xx() ? 32 : 64;
		अगर (burst > data->blksz)
			burst = data->blksz;

		burst >>= 1;

		अगर (data->flags & MMC_DATA_WRITE) अणु
			c = host->dma_tx;
			bp = &host->dma_tx_burst;
			buf = 0x0f80 | (burst - 1) << 0;
			dma_data_dir = DMA_TO_DEVICE;
		पूर्ण अन्यथा अणु
			c = host->dma_rx;
			bp = &host->dma_rx_burst;
			buf = 0x800f | (burst - 1) << 8;
			dma_data_dir = DMA_FROM_DEVICE;
		पूर्ण

		अगर (!c)
			जाओ use_pio;

		/* Only reconfigure अगर we have a dअगरferent burst size */
		अगर (*bp != burst) अणु
			काष्ठा dma_slave_config cfg = अणु
				.src_addr = host->phys_base +
					    OMAP_MMC_REG(host, DATA),
				.dst_addr = host->phys_base +
					    OMAP_MMC_REG(host, DATA),
				.src_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES,
				.dst_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES,
				.src_maxburst = burst,
				.dst_maxburst = burst,
			पूर्ण;

			अगर (dmaengine_slave_config(c, &cfg))
				जाओ use_pio;

			*bp = burst;
		पूर्ण

		host->sg_len = dma_map_sg(c->device->dev, data->sg, sg_len,
					  dma_data_dir);
		अगर (host->sg_len == 0)
			जाओ use_pio;

		tx = dmaengine_prep_slave_sg(c, data->sg, host->sg_len,
			data->flags & MMC_DATA_WRITE ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM,
			DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
		अगर (!tx)
			जाओ use_pio;

		OMAP_MMC_WRITE(host, BUF, buf);

		tx->callback = mmc_omap_dma_callback;
		tx->callback_param = host;
		dmaengine_submit(tx);
		host->brs_received = 0;
		host->dma_करोne = 0;
		host->dma_in_use = 1;
		वापस;
	पूर्ण
 use_pio:

	/* Revert to PIO? */
	OMAP_MMC_WRITE(host, BUF, 0x1f1f);
	host->total_bytes_left = data->blocks * block_size;
	host->sg_len = sg_len;
	mmc_omap_sg_to_buf(host);
	host->dma_in_use = 0;
पूर्ण

अटल व्योम mmc_omap_start_request(काष्ठा mmc_omap_host *host,
				   काष्ठा mmc_request *req)
अणु
	BUG_ON(host->mrq != शून्य);

	host->mrq = req;

	/* only touch fअगरo AFTER the controller पढ़ोies it */
	mmc_omap_prepare_data(host, req);
	mmc_omap_start_command(host, req->cmd);
	अगर (host->dma_in_use) अणु
		काष्ठा dma_chan *c = host->data->flags & MMC_DATA_WRITE ?
				host->dma_tx : host->dma_rx;

		dma_async_issue_pending(c);
	पूर्ण
पूर्ण

अटल व्योम mmc_omap_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *req)
अणु
	काष्ठा mmc_omap_slot *slot = mmc_priv(mmc);
	काष्ठा mmc_omap_host *host = slot->host;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->slot_lock, flags);
	अगर (host->mmc != शून्य) अणु
		BUG_ON(slot->mrq != शून्य);
		slot->mrq = req;
		spin_unlock_irqrestore(&host->slot_lock, flags);
		वापस;
	पूर्ण अन्यथा
		host->mmc = mmc;
	spin_unlock_irqrestore(&host->slot_lock, flags);
	mmc_omap_select_slot(slot, 1);
	mmc_omap_start_request(host, req);
पूर्ण

अटल व्योम mmc_omap_set_घातer(काष्ठा mmc_omap_slot *slot, पूर्णांक घातer_on,
				पूर्णांक vdd)
अणु
	काष्ठा mmc_omap_host *host;

	host = slot->host;

	अगर (slot->pdata->set_घातer != शून्य)
		slot->pdata->set_घातer(mmc_dev(slot->mmc), slot->id, घातer_on,
					vdd);
	अगर (mmc_omap2()) अणु
		u16 w;

		अगर (घातer_on) अणु
			w = OMAP_MMC_READ(host, CON);
			OMAP_MMC_WRITE(host, CON, w | (1 << 11));
		पूर्ण अन्यथा अणु
			w = OMAP_MMC_READ(host, CON);
			OMAP_MMC_WRITE(host, CON, w & ~(1 << 11));
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mmc_omap_calc_भागisor(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा mmc_omap_slot *slot = mmc_priv(mmc);
	काष्ठा mmc_omap_host *host = slot->host;
	पूर्णांक func_clk_rate = clk_get_rate(host->fclk);
	पूर्णांक dsor;

	अगर (ios->घड़ी == 0)
		वापस 0;

	dsor = func_clk_rate / ios->घड़ी;
	अगर (dsor < 1)
		dsor = 1;

	अगर (func_clk_rate / dsor > ios->घड़ी)
		dsor++;

	अगर (dsor > 250)
		dsor = 250;

	slot->fclk_freq = func_clk_rate / dsor;

	अगर (ios->bus_width == MMC_BUS_WIDTH_4)
		dsor |= 1 << 15;

	वापस dsor;
पूर्ण

अटल व्योम mmc_omap_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा mmc_omap_slot *slot = mmc_priv(mmc);
	काष्ठा mmc_omap_host *host = slot->host;
	पूर्णांक i, dsor;
	पूर्णांक clk_enabled, init_stream;

	mmc_omap_select_slot(slot, 0);

	dsor = mmc_omap_calc_भागisor(mmc, ios);

	अगर (ios->vdd != slot->vdd)
		slot->vdd = ios->vdd;

	clk_enabled = 0;
	init_stream = 0;
	चयन (ios->घातer_mode) अणु
	हाल MMC_POWER_OFF:
		mmc_omap_set_घातer(slot, 0, ios->vdd);
		अवरोध;
	हाल MMC_POWER_UP:
		/* Cannot touch dsor yet, just घातer up MMC */
		mmc_omap_set_घातer(slot, 1, ios->vdd);
		slot->घातer_mode = ios->घातer_mode;
		जाओ निकास;
	हाल MMC_POWER_ON:
		mmc_omap_fclk_enable(host, 1);
		clk_enabled = 1;
		dsor |= 1 << 11;
		अगर (slot->घातer_mode != MMC_POWER_ON)
			init_stream = 1;
		अवरोध;
	पूर्ण
	slot->घातer_mode = ios->घातer_mode;

	अगर (slot->bus_mode != ios->bus_mode) अणु
		अगर (slot->pdata->set_bus_mode != शून्य)
			slot->pdata->set_bus_mode(mmc_dev(mmc), slot->id,
						  ios->bus_mode);
		slot->bus_mode = ios->bus_mode;
	पूर्ण

	/* On insanely high arm_per frequencies something someबार
	 * goes somehow out of sync, and the POW bit is not being set,
	 * which results in the जबतक loop below getting stuck.
	 * Writing to the CON रेजिस्टर twice seems to करो the trick. */
	क्रम (i = 0; i < 2; i++)
		OMAP_MMC_WRITE(host, CON, dsor);
	slot->saved_con = dsor;
	अगर (init_stream) अणु
		/* worst हाल at 400kHz, 80 cycles makes 200 microsecs */
		पूर्णांक usecs = 250;

		/* Send घड़ी cycles, poll completion */
		OMAP_MMC_WRITE(host, IE, 0);
		OMAP_MMC_WRITE(host, STAT, 0xffff);
		OMAP_MMC_WRITE(host, CMD, 1 << 7);
		जबतक (usecs > 0 && (OMAP_MMC_READ(host, STAT) & 1) == 0) अणु
			udelay(1);
			usecs--;
		पूर्ण
		OMAP_MMC_WRITE(host, STAT, 1);
	पूर्ण

निकास:
	mmc_omap_release_slot(slot, clk_enabled);
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops mmc_omap_ops = अणु
	.request	= mmc_omap_request,
	.set_ios	= mmc_omap_set_ios,
पूर्ण;

अटल पूर्णांक mmc_omap_new_slot(काष्ठा mmc_omap_host *host, पूर्णांक id)
अणु
	काष्ठा mmc_omap_slot *slot = शून्य;
	काष्ठा mmc_host *mmc;
	पूर्णांक r;

	mmc = mmc_alloc_host(माप(काष्ठा mmc_omap_slot), host->dev);
	अगर (mmc == शून्य)
		वापस -ENOMEM;

	slot = mmc_priv(mmc);
	slot->host = host;
	slot->mmc = mmc;
	slot->id = id;
	slot->घातer_mode = MMC_POWER_UNDEFINED;
	slot->pdata = &host->pdata->slots[id];

	host->slots[id] = slot;

	mmc->caps = 0;
	अगर (host->pdata->slots[id].wires >= 4)
		mmc->caps |= MMC_CAP_4_BIT_DATA;

	mmc->ops = &mmc_omap_ops;
	mmc->f_min = 400000;

	अगर (mmc_omap2())
		mmc->f_max = 48000000;
	अन्यथा
		mmc->f_max = 24000000;
	अगर (host->pdata->max_freq)
		mmc->f_max = min(host->pdata->max_freq, mmc->f_max);
	mmc->ocr_avail = slot->pdata->ocr_mask;

	/* Use scatterlist DMA to reduce per-transfer costs.
	 * NOTE max_seg_size assumption that small blocks aren't
	 * normally used (except e.g. क्रम पढ़ोing SD रेजिस्टरs).
	 */
	mmc->max_segs = 32;
	mmc->max_blk_size = 2048;	/* BLEN is 11 bits (+1) */
	mmc->max_blk_count = 2048;	/* NBLK is 11 bits (+1) */
	mmc->max_req_size = mmc->max_blk_size * mmc->max_blk_count;
	mmc->max_seg_size = mmc->max_req_size;

	अगर (slot->pdata->get_cover_state != शून्य) अणु
		समयr_setup(&slot->cover_समयr, mmc_omap_cover_समयr, 0);
		tasklet_setup(&slot->cover_tasklet, mmc_omap_cover_handler);
	पूर्ण

	r = mmc_add_host(mmc);
	अगर (r < 0)
		जाओ err_हटाओ_host;

	अगर (slot->pdata->name != शून्य) अणु
		r = device_create_file(&mmc->class_dev,
					&dev_attr_slot_name);
		अगर (r < 0)
			जाओ err_हटाओ_host;
	पूर्ण

	अगर (slot->pdata->get_cover_state != शून्य) अणु
		r = device_create_file(&mmc->class_dev,
					&dev_attr_cover_चयन);
		अगर (r < 0)
			जाओ err_हटाओ_slot_name;
		tasklet_schedule(&slot->cover_tasklet);
	पूर्ण

	वापस 0;

err_हटाओ_slot_name:
	अगर (slot->pdata->name != शून्य)
		device_हटाओ_file(&mmc->class_dev, &dev_attr_slot_name);
err_हटाओ_host:
	mmc_हटाओ_host(mmc);
	mmc_मुक्त_host(mmc);
	वापस r;
पूर्ण

अटल व्योम mmc_omap_हटाओ_slot(काष्ठा mmc_omap_slot *slot)
अणु
	काष्ठा mmc_host *mmc = slot->mmc;

	अगर (slot->pdata->name != शून्य)
		device_हटाओ_file(&mmc->class_dev, &dev_attr_slot_name);
	अगर (slot->pdata->get_cover_state != शून्य)
		device_हटाओ_file(&mmc->class_dev, &dev_attr_cover_चयन);

	tasklet_समाप्त(&slot->cover_tasklet);
	del_समयr_sync(&slot->cover_समयr);
	flush_workqueue(slot->host->mmc_omap_wq);

	mmc_हटाओ_host(mmc);
	mmc_मुक्त_host(mmc);
पूर्ण

अटल पूर्णांक mmc_omap_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_mmc_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा mmc_omap_host *host = शून्य;
	काष्ठा resource *res;
	पूर्णांक i, ret = 0;
	पूर्णांक irq;

	अगर (pdata == शून्य) अणु
		dev_err(&pdev->dev, "platform data missing\n");
		वापस -ENXIO;
	पूर्ण
	अगर (pdata->nr_slots == 0) अणु
		dev_err(&pdev->dev, "no slots\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	host = devm_kzalloc(&pdev->dev, माप(काष्ठा mmc_omap_host),
			    GFP_KERNEL);
	अगर (host == शून्य)
		वापस -ENOMEM;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -ENXIO;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	host->virt_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(host->virt_base))
		वापस PTR_ERR(host->virt_base);

	INIT_WORK(&host->slot_release_work, mmc_omap_slot_release_work);
	INIT_WORK(&host->send_stop_work, mmc_omap_send_stop_work);

	INIT_WORK(&host->cmd_पात_work, mmc_omap_पात_command);
	समयr_setup(&host->cmd_पात_समयr, mmc_omap_cmd_समयr, 0);

	spin_lock_init(&host->clk_lock);
	समयr_setup(&host->clk_समयr, mmc_omap_clk_समयr, 0);

	spin_lock_init(&host->dma_lock);
	spin_lock_init(&host->slot_lock);
	init_रुकोqueue_head(&host->slot_wq);

	host->pdata = pdata;
	host->features = host->pdata->slots[0].features;
	host->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, host);

	host->id = pdev->id;
	host->irq = irq;
	host->phys_base = res->start;
	host->iclk = clk_get(&pdev->dev, "ick");
	अगर (IS_ERR(host->iclk))
		वापस PTR_ERR(host->iclk);
	clk_enable(host->iclk);

	host->fclk = clk_get(&pdev->dev, "fck");
	अगर (IS_ERR(host->fclk)) अणु
		ret = PTR_ERR(host->fclk);
		जाओ err_मुक्त_iclk;
	पूर्ण

	host->dma_tx_burst = -1;
	host->dma_rx_burst = -1;

	host->dma_tx = dma_request_chan(&pdev->dev, "tx");
	अगर (IS_ERR(host->dma_tx)) अणु
		ret = PTR_ERR(host->dma_tx);
		अगर (ret == -EPROBE_DEFER) अणु
			clk_put(host->fclk);
			जाओ err_मुक्त_iclk;
		पूर्ण

		host->dma_tx = शून्य;
		dev_warn(host->dev, "TX DMA channel request failed\n");
	पूर्ण

	host->dma_rx = dma_request_chan(&pdev->dev, "rx");
	अगर (IS_ERR(host->dma_rx)) अणु
		ret = PTR_ERR(host->dma_rx);
		अगर (ret == -EPROBE_DEFER) अणु
			अगर (host->dma_tx)
				dma_release_channel(host->dma_tx);
			clk_put(host->fclk);
			जाओ err_मुक्त_iclk;
		पूर्ण

		host->dma_rx = शून्य;
		dev_warn(host->dev, "RX DMA channel request failed\n");
	पूर्ण

	ret = request_irq(host->irq, mmc_omap_irq, 0, DRIVER_NAME, host);
	अगर (ret)
		जाओ err_मुक्त_dma;

	अगर (pdata->init != शून्य) अणु
		ret = pdata->init(&pdev->dev);
		अगर (ret < 0)
			जाओ err_मुक्त_irq;
	पूर्ण

	host->nr_slots = pdata->nr_slots;
	host->reg_shअगरt = (mmc_omap7xx() ? 1 : 2);

	host->mmc_omap_wq = alloc_workqueue("mmc_omap", 0, 0);
	अगर (!host->mmc_omap_wq) अणु
		ret = -ENOMEM;
		जाओ err_plat_cleanup;
	पूर्ण

	क्रम (i = 0; i < pdata->nr_slots; i++) अणु
		ret = mmc_omap_new_slot(host, i);
		अगर (ret < 0) अणु
			जबतक (--i >= 0)
				mmc_omap_हटाओ_slot(host->slots[i]);

			जाओ err_destroy_wq;
		पूर्ण
	पूर्ण

	वापस 0;

err_destroy_wq:
	destroy_workqueue(host->mmc_omap_wq);
err_plat_cleanup:
	अगर (pdata->cleanup)
		pdata->cleanup(&pdev->dev);
err_मुक्त_irq:
	मुक्त_irq(host->irq, host);
err_मुक्त_dma:
	अगर (host->dma_tx)
		dma_release_channel(host->dma_tx);
	अगर (host->dma_rx)
		dma_release_channel(host->dma_rx);
	clk_put(host->fclk);
err_मुक्त_iclk:
	clk_disable(host->iclk);
	clk_put(host->iclk);
	वापस ret;
पूर्ण

अटल पूर्णांक mmc_omap_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_omap_host *host = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	BUG_ON(host == शून्य);

	क्रम (i = 0; i < host->nr_slots; i++)
		mmc_omap_हटाओ_slot(host->slots[i]);

	अगर (host->pdata->cleanup)
		host->pdata->cleanup(&pdev->dev);

	mmc_omap_fclk_enable(host, 0);
	मुक्त_irq(host->irq, host);
	clk_put(host->fclk);
	clk_disable(host->iclk);
	clk_put(host->iclk);

	अगर (host->dma_tx)
		dma_release_channel(host->dma_tx);
	अगर (host->dma_rx)
		dma_release_channel(host->dma_rx);

	destroy_workqueue(host->mmc_omap_wq);

	वापस 0;
पूर्ण

#अगर IS_BUILTIN(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id mmc_omap_match[] = अणु
	अणु .compatible = "ti,omap2420-mmc", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mmc_omap_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver mmc_omap_driver = अणु
	.probe		= mmc_omap_probe,
	.हटाओ		= mmc_omap_हटाओ,
	.driver		= अणु
		.name	= DRIVER_NAME,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = of_match_ptr(mmc_omap_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mmc_omap_driver);
MODULE_DESCRIPTION("OMAP Multimedia Card driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRIVER_NAME);
MODULE_AUTHOR("Juha Yrjथघlथअ");
