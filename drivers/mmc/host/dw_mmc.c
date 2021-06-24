<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Synopsys DesignWare Mulसमयdia Card Interface driver
 *  (Based on NXP driver क्रम lpc 31xx)
 *
 * Copyright (C) 2009 NXP Semiconductors
 * Copyright (C) 2009, 2010 Imagination Technologies Ltd.
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/clk.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/sd.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/bitops.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/mmc/slot-gpपन.स>

#समावेश "dw_mmc.h"

/* Common flag combinations */
#घोषणा DW_MCI_DATA_ERROR_FLAGS	(SDMMC_INT_DRTO | SDMMC_INT_DCRC | \
				 SDMMC_INT_HTO | SDMMC_INT_SBE  | \
				 SDMMC_INT_EBE | SDMMC_INT_HLE)
#घोषणा DW_MCI_CMD_ERROR_FLAGS	(SDMMC_INT_RTO | SDMMC_INT_RCRC | \
				 SDMMC_INT_RESP_ERR | SDMMC_INT_HLE)
#घोषणा DW_MCI_ERROR_FLAGS	(DW_MCI_DATA_ERROR_FLAGS | \
				 DW_MCI_CMD_ERROR_FLAGS)
#घोषणा DW_MCI_SEND_STATUS	1
#घोषणा DW_MCI_RECV_STATUS	2
#घोषणा DW_MCI_DMA_THRESHOLD	16

#घोषणा DW_MCI_FREQ_MAX	200000000	/* unit: HZ */
#घोषणा DW_MCI_FREQ_MIN	100000		/* unit: HZ */

#घोषणा IDMAC_INT_CLR		(SDMMC_IDMAC_INT_AI | SDMMC_IDMAC_INT_NI | \
				 SDMMC_IDMAC_INT_CES | SDMMC_IDMAC_INT_DU | \
				 SDMMC_IDMAC_INT_FBE | SDMMC_IDMAC_INT_RI | \
				 SDMMC_IDMAC_INT_TI)

#घोषणा DESC_RING_BUF_SZ	PAGE_SIZE

काष्ठा idmac_desc_64addr अणु
	u32		des0;	/* Control Descriptor */
#घोषणा IDMAC_OWN_CLR64(x) \
	!((x) & cpu_to_le32(IDMAC_DES0_OWN))

	u32		des1;	/* Reserved */

	u32		des2;	/*Buffer sizes */
#घोषणा IDMAC_64ADDR_SET_BUFFER1_SIZE(d, s) \
	((d)->des2 = ((d)->des2 & cpu_to_le32(0x03ffe000)) | \
	 ((cpu_to_le32(s)) & cpu_to_le32(0x1fff)))

	u32		des3;	/* Reserved */

	u32		des4;	/* Lower 32-bits of Buffer Address Poपूर्णांकer 1*/
	u32		des5;	/* Upper 32-bits of Buffer Address Poपूर्णांकer 1*/

	u32		des6;	/* Lower 32-bits of Next Descriptor Address */
	u32		des7;	/* Upper 32-bits of Next Descriptor Address */
पूर्ण;

काष्ठा idmac_desc अणु
	__le32		des0;	/* Control Descriptor */
#घोषणा IDMAC_DES0_DIC	BIT(1)
#घोषणा IDMAC_DES0_LD	BIT(2)
#घोषणा IDMAC_DES0_FD	BIT(3)
#घोषणा IDMAC_DES0_CH	BIT(4)
#घोषणा IDMAC_DES0_ER	BIT(5)
#घोषणा IDMAC_DES0_CES	BIT(30)
#घोषणा IDMAC_DES0_OWN	BIT(31)

	__le32		des1;	/* Buffer sizes */
#घोषणा IDMAC_SET_BUFFER1_SIZE(d, s) \
	((d)->des1 = ((d)->des1 & cpu_to_le32(0x03ffe000)) | (cpu_to_le32((s) & 0x1fff)))

	__le32		des2;	/* buffer 1 physical address */

	__le32		des3;	/* buffer 2 physical address */
पूर्ण;

/* Each descriptor can transfer up to 4KB of data in chained mode */
#घोषणा DW_MCI_DESC_DATA_LENGTH	0x1000

#अगर defined(CONFIG_DEBUG_FS)
अटल पूर्णांक dw_mci_req_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा dw_mci_slot *slot = s->निजी;
	काष्ठा mmc_request *mrq;
	काष्ठा mmc_command *cmd;
	काष्ठा mmc_command *stop;
	काष्ठा mmc_data	*data;

	/* Make sure we get a consistent snapshot */
	spin_lock_bh(&slot->host->lock);
	mrq = slot->mrq;

	अगर (mrq) अणु
		cmd = mrq->cmd;
		data = mrq->data;
		stop = mrq->stop;

		अगर (cmd)
			seq_म_लिखो(s,
				   "CMD%u(0x%x) flg %x rsp %x %x %x %x err %d\n",
				   cmd->opcode, cmd->arg, cmd->flags,
				   cmd->resp[0], cmd->resp[1], cmd->resp[2],
				   cmd->resp[2], cmd->error);
		अगर (data)
			seq_म_लिखो(s, "DATA %u / %u * %u flg %x err %d\n",
				   data->bytes_xfered, data->blocks,
				   data->blksz, data->flags, data->error);
		अगर (stop)
			seq_म_लिखो(s,
				   "CMD%u(0x%x) flg %x rsp %x %x %x %x err %d\n",
				   stop->opcode, stop->arg, stop->flags,
				   stop->resp[0], stop->resp[1], stop->resp[2],
				   stop->resp[2], stop->error);
	पूर्ण

	spin_unlock_bh(&slot->host->lock);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(dw_mci_req);

अटल पूर्णांक dw_mci_regs_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा dw_mci *host = s->निजी;

	pm_runसमय_get_sync(host->dev);

	seq_म_लिखो(s, "STATUS:\t0x%08x\n", mci_पढ़ोl(host, STATUS));
	seq_म_लिखो(s, "RINTSTS:\t0x%08x\n", mci_पढ़ोl(host, RINTSTS));
	seq_म_लिखो(s, "CMD:\t0x%08x\n", mci_पढ़ोl(host, CMD));
	seq_म_लिखो(s, "CTRL:\t0x%08x\n", mci_पढ़ोl(host, CTRL));
	seq_म_लिखो(s, "INTMASK:\t0x%08x\n", mci_पढ़ोl(host, INTMASK));
	seq_म_लिखो(s, "CLKENA:\t0x%08x\n", mci_पढ़ोl(host, CLKENA));

	pm_runसमय_put_स्वतःsuspend(host->dev);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(dw_mci_regs);

अटल व्योम dw_mci_init_debugfs(काष्ठा dw_mci_slot *slot)
अणु
	काष्ठा mmc_host	*mmc = slot->mmc;
	काष्ठा dw_mci *host = slot->host;
	काष्ठा dentry *root;

	root = mmc->debugfs_root;
	अगर (!root)
		वापस;

	debugfs_create_file("regs", S_IRUSR, root, host, &dw_mci_regs_fops);
	debugfs_create_file("req", S_IRUSR, root, slot, &dw_mci_req_fops);
	debugfs_create_u32("state", S_IRUSR, root, &host->state);
	debugfs_create_xul("pending_events", S_IRUSR, root,
			   &host->pending_events);
	debugfs_create_xul("completed_events", S_IRUSR, root,
			   &host->completed_events);
पूर्ण
#पूर्ण_अगर /* defined(CONFIG_DEBUG_FS) */

अटल bool dw_mci_ctrl_reset(काष्ठा dw_mci *host, u32 reset)
अणु
	u32 ctrl;

	ctrl = mci_पढ़ोl(host, CTRL);
	ctrl |= reset;
	mci_ग_लिखोl(host, CTRL, ctrl);

	/* रुको till resets clear */
	अगर (पढ़ोl_poll_समयout_atomic(host->regs + SDMMC_CTRL, ctrl,
				      !(ctrl & reset),
				      1, 500 * USEC_PER_MSEC)) अणु
		dev_err(host->dev,
			"Timeout resetting block (ctrl reset %#x)\n",
			ctrl & reset);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम dw_mci_रुको_जबतक_busy(काष्ठा dw_mci *host, u32 cmd_flags)
अणु
	u32 status;

	/*
	 * Databook says that beक्रमe issuing a new data transfer command
	 * we need to check to see अगर the card is busy.  Data transfer commands
	 * all have SDMMC_CMD_PRV_DAT_WAIT set, so we'll key off that.
	 *
	 * ...also allow sending क्रम SDMMC_CMD_VOLT_SWITCH where busy is
	 * expected.
	 */
	अगर ((cmd_flags & SDMMC_CMD_PRV_DAT_WAIT) &&
	    !(cmd_flags & SDMMC_CMD_VOLT_SWITCH)) अणु
		अगर (पढ़ोl_poll_समयout_atomic(host->regs + SDMMC_STATUS,
					      status,
					      !(status & SDMMC_STATUS_BUSY),
					      10, 500 * USEC_PER_MSEC))
			dev_err(host->dev, "Busy; trying anyway\n");
	पूर्ण
पूर्ण

अटल व्योम mci_send_cmd(काष्ठा dw_mci_slot *slot, u32 cmd, u32 arg)
अणु
	काष्ठा dw_mci *host = slot->host;
	अचिन्हित पूर्णांक cmd_status = 0;

	mci_ग_लिखोl(host, CMDARG, arg);
	wmb(); /* drain ग_लिखोbuffer */
	dw_mci_रुको_जबतक_busy(host, cmd);
	mci_ग_लिखोl(host, CMD, SDMMC_CMD_START | cmd);

	अगर (पढ़ोl_poll_समयout_atomic(host->regs + SDMMC_CMD, cmd_status,
				      !(cmd_status & SDMMC_CMD_START),
				      1, 500 * USEC_PER_MSEC))
		dev_err(&slot->mmc->class_dev,
			"Timeout sending command (cmd %#x arg %#x status %#x)\n",
			cmd, arg, cmd_status);
पूर्ण

अटल u32 dw_mci_prepare_command(काष्ठा mmc_host *mmc, काष्ठा mmc_command *cmd)
अणु
	काष्ठा dw_mci_slot *slot = mmc_priv(mmc);
	काष्ठा dw_mci *host = slot->host;
	u32 cmdr;

	cmd->error = -EINPROGRESS;
	cmdr = cmd->opcode;

	अगर (cmd->opcode == MMC_STOP_TRANSMISSION ||
	    cmd->opcode == MMC_GO_IDLE_STATE ||
	    cmd->opcode == MMC_GO_INACTIVE_STATE ||
	    (cmd->opcode == SD_IO_RW_सूचीECT &&
	     ((cmd->arg >> 9) & 0x1FFFF) == SDIO_CCCR_ABORT))
		cmdr |= SDMMC_CMD_STOP;
	अन्यथा अगर (cmd->opcode != MMC_SEND_STATUS && cmd->data)
		cmdr |= SDMMC_CMD_PRV_DAT_WAIT;

	अगर (cmd->opcode == SD_SWITCH_VOLTAGE) अणु
		u32 clk_en_a;

		/* Special bit makes CMD11 not die */
		cmdr |= SDMMC_CMD_VOLT_SWITCH;

		/* Change state to जारी to handle CMD11 weirdness */
		WARN_ON(slot->host->state != STATE_SENDING_CMD);
		slot->host->state = STATE_SENDING_CMD11;

		/*
		 * We need to disable low घातer mode (स्वतःmatic घड़ी stop)
		 * जबतक करोing voltage चयन so we करोn't confuse the card,
		 * since stopping the घड़ी is a specअगरic part of the UHS
		 * voltage change dance.
		 *
		 * Note that low घातer mode (SDMMC_CLKEN_LOW_PWR) will be
		 * unconditionally turned back on in dw_mci_setup_bus() अगर it's
		 * ever called with a non-zero घड़ी.  That shouldn't happen
		 * until the voltage change is all करोne.
		 */
		clk_en_a = mci_पढ़ोl(host, CLKENA);
		clk_en_a &= ~(SDMMC_CLKEN_LOW_PWR << slot->id);
		mci_ग_लिखोl(host, CLKENA, clk_en_a);
		mci_send_cmd(slot, SDMMC_CMD_UPD_CLK |
			     SDMMC_CMD_PRV_DAT_WAIT, 0);
	पूर्ण

	अगर (cmd->flags & MMC_RSP_PRESENT) अणु
		/* We expect a response, so set this bit */
		cmdr |= SDMMC_CMD_RESP_EXP;
		अगर (cmd->flags & MMC_RSP_136)
			cmdr |= SDMMC_CMD_RESP_LONG;
	पूर्ण

	अगर (cmd->flags & MMC_RSP_CRC)
		cmdr |= SDMMC_CMD_RESP_CRC;

	अगर (cmd->data) अणु
		cmdr |= SDMMC_CMD_DAT_EXP;
		अगर (cmd->data->flags & MMC_DATA_WRITE)
			cmdr |= SDMMC_CMD_DAT_WR;
	पूर्ण

	अगर (!test_bit(DW_MMC_CARD_NO_USE_HOLD, &slot->flags))
		cmdr |= SDMMC_CMD_USE_HOLD_REG;

	वापस cmdr;
पूर्ण

अटल u32 dw_mci_prep_stop_पात(काष्ठा dw_mci *host, काष्ठा mmc_command *cmd)
अणु
	काष्ठा mmc_command *stop;
	u32 cmdr;

	अगर (!cmd->data)
		वापस 0;

	stop = &host->stop_पात;
	cmdr = cmd->opcode;
	स_रखो(stop, 0, माप(काष्ठा mmc_command));

	अगर (cmdr == MMC_READ_SINGLE_BLOCK ||
	    cmdr == MMC_READ_MULTIPLE_BLOCK ||
	    cmdr == MMC_WRITE_BLOCK ||
	    cmdr == MMC_WRITE_MULTIPLE_BLOCK ||
	    cmdr == MMC_SEND_TUNING_BLOCK ||
	    cmdr == MMC_SEND_TUNING_BLOCK_HS200) अणु
		stop->opcode = MMC_STOP_TRANSMISSION;
		stop->arg = 0;
		stop->flags = MMC_RSP_R1B | MMC_CMD_AC;
	पूर्ण अन्यथा अगर (cmdr == SD_IO_RW_EXTENDED) अणु
		stop->opcode = SD_IO_RW_सूचीECT;
		stop->arg |= (1 << 31) | (0 << 28) | (SDIO_CCCR_ABORT << 9) |
			     ((cmd->arg >> 28) & 0x7);
		stop->flags = MMC_RSP_SPI_R5 | MMC_RSP_R5 | MMC_CMD_AC;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	cmdr = stop->opcode | SDMMC_CMD_STOP |
		SDMMC_CMD_RESP_CRC | SDMMC_CMD_RESP_EXP;

	अगर (!test_bit(DW_MMC_CARD_NO_USE_HOLD, &host->slot->flags))
		cmdr |= SDMMC_CMD_USE_HOLD_REG;

	वापस cmdr;
पूर्ण

अटल अंतरभूत व्योम dw_mci_set_cto(काष्ठा dw_mci *host)
अणु
	अचिन्हित पूर्णांक cto_clks;
	अचिन्हित पूर्णांक cto_भाग;
	अचिन्हित पूर्णांक cto_ms;
	अचिन्हित दीर्घ irqflags;

	cto_clks = mci_पढ़ोl(host, TMOUT) & 0xff;
	cto_भाग = (mci_पढ़ोl(host, CLKDIV) & 0xff) * 2;
	अगर (cto_भाग == 0)
		cto_भाग = 1;

	cto_ms = DIV_ROUND_UP_ULL((u64)MSEC_PER_SEC * cto_clks * cto_भाग,
				  host->bus_hz);

	/* add a bit spare समय */
	cto_ms += 10;

	/*
	 * The durations we're working with are fairly लघु so we have to be
	 * extra careful about synchronization here.  Specअगरically in hardware a
	 * command समयout is _at most_ 5.1 ms, so that means we expect an
	 * पूर्णांकerrupt (either command करोne or समयout) to come rather quickly
	 * after the mci_ग_लिखोl.  ...but just in हाल we have a दीर्घ पूर्णांकerrupt
	 * latency let's add a bit of paranoia.
	 *
	 * In general we'll assume that at least an पूर्णांकerrupt will be निश्चितed
	 * in hardware by the समय the cto_समयr runs.  ...and अगर it hasn't
	 * been निश्चितed in hardware by that समय then we'll assume it'll never
	 * come.
	 */
	spin_lock_irqsave(&host->irq_lock, irqflags);
	अगर (!test_bit(EVENT_CMD_COMPLETE, &host->pending_events))
		mod_समयr(&host->cto_समयr,
			jअगरfies + msecs_to_jअगरfies(cto_ms) + 1);
	spin_unlock_irqrestore(&host->irq_lock, irqflags);
पूर्ण

अटल व्योम dw_mci_start_command(काष्ठा dw_mci *host,
				 काष्ठा mmc_command *cmd, u32 cmd_flags)
अणु
	host->cmd = cmd;
	dev_vdbg(host->dev,
		 "start command: ARGR=0x%08x CMDR=0x%08x\n",
		 cmd->arg, cmd_flags);

	mci_ग_लिखोl(host, CMDARG, cmd->arg);
	wmb(); /* drain ग_लिखोbuffer */
	dw_mci_रुको_जबतक_busy(host, cmd_flags);

	mci_ग_लिखोl(host, CMD, cmd_flags | SDMMC_CMD_START);

	/* response expected command only */
	अगर (cmd_flags & SDMMC_CMD_RESP_EXP)
		dw_mci_set_cto(host);
पूर्ण

अटल अंतरभूत व्योम send_stop_पात(काष्ठा dw_mci *host, काष्ठा mmc_data *data)
अणु
	काष्ठा mmc_command *stop = &host->stop_पात;

	dw_mci_start_command(host, stop, host->stop_cmdr);
पूर्ण

/* DMA पूर्णांकerface functions */
अटल व्योम dw_mci_stop_dma(काष्ठा dw_mci *host)
अणु
	अगर (host->using_dma) अणु
		host->dma_ops->stop(host);
		host->dma_ops->cleanup(host);
	पूर्ण

	/* Data transfer was stopped by the पूर्णांकerrupt handler */
	set_bit(EVENT_XFER_COMPLETE, &host->pending_events);
पूर्ण

अटल व्योम dw_mci_dma_cleanup(काष्ठा dw_mci *host)
अणु
	काष्ठा mmc_data *data = host->data;

	अगर (data && data->host_cookie == COOKIE_MAPPED) अणु
		dma_unmap_sg(host->dev,
			     data->sg,
			     data->sg_len,
			     mmc_get_dma_dir(data));
		data->host_cookie = COOKIE_UNMAPPED;
	पूर्ण
पूर्ण

अटल व्योम dw_mci_idmac_reset(काष्ठा dw_mci *host)
अणु
	u32 bmod = mci_पढ़ोl(host, BMOD);
	/* Software reset of DMA */
	bmod |= SDMMC_IDMAC_SWRESET;
	mci_ग_लिखोl(host, BMOD, bmod);
पूर्ण

अटल व्योम dw_mci_idmac_stop_dma(काष्ठा dw_mci *host)
अणु
	u32 temp;

	/* Disable and reset the IDMAC पूर्णांकerface */
	temp = mci_पढ़ोl(host, CTRL);
	temp &= ~SDMMC_CTRL_USE_IDMAC;
	temp |= SDMMC_CTRL_DMA_RESET;
	mci_ग_लिखोl(host, CTRL, temp);

	/* Stop the IDMAC running */
	temp = mci_पढ़ोl(host, BMOD);
	temp &= ~(SDMMC_IDMAC_ENABLE | SDMMC_IDMAC_FB);
	temp |= SDMMC_IDMAC_SWRESET;
	mci_ग_लिखोl(host, BMOD, temp);
पूर्ण

अटल व्योम dw_mci_dmac_complete_dma(व्योम *arg)
अणु
	काष्ठा dw_mci *host = arg;
	काष्ठा mmc_data *data = host->data;

	dev_vdbg(host->dev, "DMA complete\n");

	अगर ((host->use_dma == TRANS_MODE_EDMAC) &&
	    data && (data->flags & MMC_DATA_READ))
		/* Invalidate cache after पढ़ो */
		dma_sync_sg_क्रम_cpu(mmc_dev(host->slot->mmc),
				    data->sg,
				    data->sg_len,
				    DMA_FROM_DEVICE);

	host->dma_ops->cleanup(host);

	/*
	 * If the card was हटाओd, data will be शून्य. No poपूर्णांक in trying to
	 * send the stop command or रुकोing क्रम NBUSY in this हाल.
	 */
	अगर (data) अणु
		set_bit(EVENT_XFER_COMPLETE, &host->pending_events);
		tasklet_schedule(&host->tasklet);
	पूर्ण
पूर्ण

अटल पूर्णांक dw_mci_idmac_init(काष्ठा dw_mci *host)
अणु
	पूर्णांक i;

	अगर (host->dma_64bit_address == 1) अणु
		काष्ठा idmac_desc_64addr *p;
		/* Number of descriptors in the ring buffer */
		host->ring_size =
			DESC_RING_BUF_SZ / माप(काष्ठा idmac_desc_64addr);

		/* Forward link the descriptor list */
		क्रम (i = 0, p = host->sg_cpu; i < host->ring_size - 1;
								i++, p++) अणु
			p->des6 = (host->sg_dma +
					(माप(काष्ठा idmac_desc_64addr) *
							(i + 1))) & 0xffffffff;

			p->des7 = (u64)(host->sg_dma +
					(माप(काष्ठा idmac_desc_64addr) *
							(i + 1))) >> 32;
			/* Initialize reserved and buffer size fields to "0" */
			p->des0 = 0;
			p->des1 = 0;
			p->des2 = 0;
			p->des3 = 0;
		पूर्ण

		/* Set the last descriptor as the end-of-ring descriptor */
		p->des6 = host->sg_dma & 0xffffffff;
		p->des7 = (u64)host->sg_dma >> 32;
		p->des0 = IDMAC_DES0_ER;

	पूर्ण अन्यथा अणु
		काष्ठा idmac_desc *p;
		/* Number of descriptors in the ring buffer */
		host->ring_size =
			DESC_RING_BUF_SZ / माप(काष्ठा idmac_desc);

		/* Forward link the descriptor list */
		क्रम (i = 0, p = host->sg_cpu;
		     i < host->ring_size - 1;
		     i++, p++) अणु
			p->des3 = cpu_to_le32(host->sg_dma +
					(माप(काष्ठा idmac_desc) * (i + 1)));
			p->des0 = 0;
			p->des1 = 0;
		पूर्ण

		/* Set the last descriptor as the end-of-ring descriptor */
		p->des3 = cpu_to_le32(host->sg_dma);
		p->des0 = cpu_to_le32(IDMAC_DES0_ER);
	पूर्ण

	dw_mci_idmac_reset(host);

	अगर (host->dma_64bit_address == 1) अणु
		/* Mask out पूर्णांकerrupts - get Tx & Rx complete only */
		mci_ग_लिखोl(host, IDSTS64, IDMAC_INT_CLR);
		mci_ग_लिखोl(host, IDINTEN64, SDMMC_IDMAC_INT_NI |
				SDMMC_IDMAC_INT_RI | SDMMC_IDMAC_INT_TI);

		/* Set the descriptor base address */
		mci_ग_लिखोl(host, DBADDRL, host->sg_dma & 0xffffffff);
		mci_ग_लिखोl(host, DBADDRU, (u64)host->sg_dma >> 32);

	पूर्ण अन्यथा अणु
		/* Mask out पूर्णांकerrupts - get Tx & Rx complete only */
		mci_ग_लिखोl(host, IDSTS, IDMAC_INT_CLR);
		mci_ग_लिखोl(host, IDINTEN, SDMMC_IDMAC_INT_NI |
				SDMMC_IDMAC_INT_RI | SDMMC_IDMAC_INT_TI);

		/* Set the descriptor base address */
		mci_ग_लिखोl(host, DBADDR, host->sg_dma);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dw_mci_prepare_desc64(काष्ठा dw_mci *host,
					 काष्ठा mmc_data *data,
					 अचिन्हित पूर्णांक sg_len)
अणु
	अचिन्हित पूर्णांक desc_len;
	काष्ठा idmac_desc_64addr *desc_first, *desc_last, *desc;
	u32 val;
	पूर्णांक i;

	desc_first = desc_last = desc = host->sg_cpu;

	क्रम (i = 0; i < sg_len; i++) अणु
		अचिन्हित पूर्णांक length = sg_dma_len(&data->sg[i]);

		u64 mem_addr = sg_dma_address(&data->sg[i]);

		क्रम ( ; length ; desc++) अणु
			desc_len = (length <= DW_MCI_DESC_DATA_LENGTH) ?
				   length : DW_MCI_DESC_DATA_LENGTH;

			length -= desc_len;

			/*
			 * Wait क्रम the क्रमmer clear OWN bit operation
			 * of IDMAC to make sure that this descriptor
			 * isn't still owned by IDMAC as IDMAC's ग_लिखो
			 * ops and CPU's पढ़ो ops are asynchronous.
			 */
			अगर (पढ़ोl_poll_समयout_atomic(&desc->des0, val,
						!(val & IDMAC_DES0_OWN),
						10, 100 * USEC_PER_MSEC))
				जाओ err_own_bit;

			/*
			 * Set the OWN bit and disable पूर्णांकerrupts
			 * क्रम this descriptor
			 */
			desc->des0 = IDMAC_DES0_OWN | IDMAC_DES0_DIC |
						IDMAC_DES0_CH;

			/* Buffer length */
			IDMAC_64ADDR_SET_BUFFER1_SIZE(desc, desc_len);

			/* Physical address to DMA to/from */
			desc->des4 = mem_addr & 0xffffffff;
			desc->des5 = mem_addr >> 32;

			/* Update physical address क्रम the next desc */
			mem_addr += desc_len;

			/* Save poपूर्णांकer to the last descriptor */
			desc_last = desc;
		पूर्ण
	पूर्ण

	/* Set first descriptor */
	desc_first->des0 |= IDMAC_DES0_FD;

	/* Set last descriptor */
	desc_last->des0 &= ~(IDMAC_DES0_CH | IDMAC_DES0_DIC);
	desc_last->des0 |= IDMAC_DES0_LD;

	वापस 0;
err_own_bit:
	/* restore the descriptor chain as it's polluted */
	dev_dbg(host->dev, "descriptor is still owned by IDMAC.\n");
	स_रखो(host->sg_cpu, 0, DESC_RING_BUF_SZ);
	dw_mci_idmac_init(host);
	वापस -EINVAL;
पूर्ण


अटल अंतरभूत पूर्णांक dw_mci_prepare_desc32(काष्ठा dw_mci *host,
					 काष्ठा mmc_data *data,
					 अचिन्हित पूर्णांक sg_len)
अणु
	अचिन्हित पूर्णांक desc_len;
	काष्ठा idmac_desc *desc_first, *desc_last, *desc;
	u32 val;
	पूर्णांक i;

	desc_first = desc_last = desc = host->sg_cpu;

	क्रम (i = 0; i < sg_len; i++) अणु
		अचिन्हित पूर्णांक length = sg_dma_len(&data->sg[i]);

		u32 mem_addr = sg_dma_address(&data->sg[i]);

		क्रम ( ; length ; desc++) अणु
			desc_len = (length <= DW_MCI_DESC_DATA_LENGTH) ?
				   length : DW_MCI_DESC_DATA_LENGTH;

			length -= desc_len;

			/*
			 * Wait क्रम the क्रमmer clear OWN bit operation
			 * of IDMAC to make sure that this descriptor
			 * isn't still owned by IDMAC as IDMAC's ग_लिखो
			 * ops and CPU's पढ़ो ops are asynchronous.
			 */
			अगर (पढ़ोl_poll_समयout_atomic(&desc->des0, val,
						      IDMAC_OWN_CLR64(val),
						      10,
						      100 * USEC_PER_MSEC))
				जाओ err_own_bit;

			/*
			 * Set the OWN bit and disable पूर्णांकerrupts
			 * क्रम this descriptor
			 */
			desc->des0 = cpu_to_le32(IDMAC_DES0_OWN |
						 IDMAC_DES0_DIC |
						 IDMAC_DES0_CH);

			/* Buffer length */
			IDMAC_SET_BUFFER1_SIZE(desc, desc_len);

			/* Physical address to DMA to/from */
			desc->des2 = cpu_to_le32(mem_addr);

			/* Update physical address क्रम the next desc */
			mem_addr += desc_len;

			/* Save poपूर्णांकer to the last descriptor */
			desc_last = desc;
		पूर्ण
	पूर्ण

	/* Set first descriptor */
	desc_first->des0 |= cpu_to_le32(IDMAC_DES0_FD);

	/* Set last descriptor */
	desc_last->des0 &= cpu_to_le32(~(IDMAC_DES0_CH |
				       IDMAC_DES0_DIC));
	desc_last->des0 |= cpu_to_le32(IDMAC_DES0_LD);

	वापस 0;
err_own_bit:
	/* restore the descriptor chain as it's polluted */
	dev_dbg(host->dev, "descriptor is still owned by IDMAC.\n");
	स_रखो(host->sg_cpu, 0, DESC_RING_BUF_SZ);
	dw_mci_idmac_init(host);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक dw_mci_idmac_start_dma(काष्ठा dw_mci *host, अचिन्हित पूर्णांक sg_len)
अणु
	u32 temp;
	पूर्णांक ret;

	अगर (host->dma_64bit_address == 1)
		ret = dw_mci_prepare_desc64(host, host->data, sg_len);
	अन्यथा
		ret = dw_mci_prepare_desc32(host, host->data, sg_len);

	अगर (ret)
		जाओ out;

	/* drain ग_लिखोbuffer */
	wmb();

	/* Make sure to reset DMA in हाल we did PIO beक्रमe this */
	dw_mci_ctrl_reset(host, SDMMC_CTRL_DMA_RESET);
	dw_mci_idmac_reset(host);

	/* Select IDMAC पूर्णांकerface */
	temp = mci_पढ़ोl(host, CTRL);
	temp |= SDMMC_CTRL_USE_IDMAC;
	mci_ग_लिखोl(host, CTRL, temp);

	/* drain ग_लिखोbuffer */
	wmb();

	/* Enable the IDMAC */
	temp = mci_पढ़ोl(host, BMOD);
	temp |= SDMMC_IDMAC_ENABLE | SDMMC_IDMAC_FB;
	mci_ग_लिखोl(host, BMOD, temp);

	/* Start it running */
	mci_ग_लिखोl(host, PLDMND, 1);

out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dw_mci_dma_ops dw_mci_idmac_ops = अणु
	.init = dw_mci_idmac_init,
	.start = dw_mci_idmac_start_dma,
	.stop = dw_mci_idmac_stop_dma,
	.complete = dw_mci_dmac_complete_dma,
	.cleanup = dw_mci_dma_cleanup,
पूर्ण;

अटल व्योम dw_mci_edmac_stop_dma(काष्ठा dw_mci *host)
अणु
	dmaengine_terminate_async(host->dms->ch);
पूर्ण

अटल पूर्णांक dw_mci_edmac_start_dma(काष्ठा dw_mci *host,
					    अचिन्हित पूर्णांक sg_len)
अणु
	काष्ठा dma_slave_config cfg;
	काष्ठा dma_async_tx_descriptor *desc = शून्य;
	काष्ठा scatterlist *sgl = host->data->sg;
	अटल स्थिर u32 mszs[] = अणु1, 4, 8, 16, 32, 64, 128, 256पूर्ण;
	u32 sg_elems = host->data->sg_len;
	u32 fअगरoth_val;
	u32 fअगरo_offset = host->fअगरo_reg - host->regs;
	पूर्णांक ret = 0;

	/* Set बाह्यal dma config: burst size, burst width */
	cfg.dst_addr = host->phy_regs + fअगरo_offset;
	cfg.src_addr = cfg.dst_addr;
	cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;

	/* Match burst msize with बाह्यal dma config */
	fअगरoth_val = mci_पढ़ोl(host, FIFOTH);
	cfg.dst_maxburst = mszs[(fअगरoth_val >> 28) & 0x7];
	cfg.src_maxburst = cfg.dst_maxburst;

	अगर (host->data->flags & MMC_DATA_WRITE)
		cfg.direction = DMA_MEM_TO_DEV;
	अन्यथा
		cfg.direction = DMA_DEV_TO_MEM;

	ret = dmaengine_slave_config(host->dms->ch, &cfg);
	अगर (ret) अणु
		dev_err(host->dev, "Failed to config edmac.\n");
		वापस -EBUSY;
	पूर्ण

	desc = dmaengine_prep_slave_sg(host->dms->ch, sgl,
				       sg_len, cfg.direction,
				       DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc) अणु
		dev_err(host->dev, "Can't prepare slave sg.\n");
		वापस -EBUSY;
	पूर्ण

	/* Set dw_mci_dmac_complete_dma as callback */
	desc->callback = dw_mci_dmac_complete_dma;
	desc->callback_param = (व्योम *)host;
	dmaengine_submit(desc);

	/* Flush cache beक्रमe ग_लिखो */
	अगर (host->data->flags & MMC_DATA_WRITE)
		dma_sync_sg_क्रम_device(mmc_dev(host->slot->mmc), sgl,
				       sg_elems, DMA_TO_DEVICE);

	dma_async_issue_pending(host->dms->ch);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_mci_edmac_init(काष्ठा dw_mci *host)
अणु
	/* Request बाह्यal dma channel */
	host->dms = kzalloc(माप(काष्ठा dw_mci_dma_slave), GFP_KERNEL);
	अगर (!host->dms)
		वापस -ENOMEM;

	host->dms->ch = dma_request_chan(host->dev, "rx-tx");
	अगर (IS_ERR(host->dms->ch)) अणु
		पूर्णांक ret = PTR_ERR(host->dms->ch);

		dev_err(host->dev, "Failed to get external DMA channel.\n");
		kमुक्त(host->dms);
		host->dms = शून्य;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dw_mci_edmac_निकास(काष्ठा dw_mci *host)
अणु
	अगर (host->dms) अणु
		अगर (host->dms->ch) अणु
			dma_release_channel(host->dms->ch);
			host->dms->ch = शून्य;
		पूर्ण
		kमुक्त(host->dms);
		host->dms = शून्य;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा dw_mci_dma_ops dw_mci_edmac_ops = अणु
	.init = dw_mci_edmac_init,
	.निकास = dw_mci_edmac_निकास,
	.start = dw_mci_edmac_start_dma,
	.stop = dw_mci_edmac_stop_dma,
	.complete = dw_mci_dmac_complete_dma,
	.cleanup = dw_mci_dma_cleanup,
पूर्ण;

अटल पूर्णांक dw_mci_pre_dma_transfer(काष्ठा dw_mci *host,
				   काष्ठा mmc_data *data,
				   पूर्णांक cookie)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक i, sg_len;

	अगर (data->host_cookie == COOKIE_PRE_MAPPED)
		वापस data->sg_len;

	/*
	 * We करोn't करो DMA on "complex" transfers, i.e. with
	 * non-word-aligned buffers or lengths. Also, we करोn't bother
	 * with all the DMA setup overhead क्रम लघु transfers.
	 */
	अगर (data->blocks * data->blksz < DW_MCI_DMA_THRESHOLD)
		वापस -EINVAL;

	अगर (data->blksz & 3)
		वापस -EINVAL;

	क्रम_each_sg(data->sg, sg, data->sg_len, i) अणु
		अगर (sg->offset & 3 || sg->length & 3)
			वापस -EINVAL;
	पूर्ण

	sg_len = dma_map_sg(host->dev,
			    data->sg,
			    data->sg_len,
			    mmc_get_dma_dir(data));
	अगर (sg_len == 0)
		वापस -EINVAL;

	data->host_cookie = cookie;

	वापस sg_len;
पूर्ण

अटल व्योम dw_mci_pre_req(काष्ठा mmc_host *mmc,
			   काष्ठा mmc_request *mrq)
अणु
	काष्ठा dw_mci_slot *slot = mmc_priv(mmc);
	काष्ठा mmc_data *data = mrq->data;

	अगर (!slot->host->use_dma || !data)
		वापस;

	/* This data might be unmapped at this समय */
	data->host_cookie = COOKIE_UNMAPPED;

	अगर (dw_mci_pre_dma_transfer(slot->host, mrq->data,
				COOKIE_PRE_MAPPED) < 0)
		data->host_cookie = COOKIE_UNMAPPED;
पूर्ण

अटल व्योम dw_mci_post_req(काष्ठा mmc_host *mmc,
			    काष्ठा mmc_request *mrq,
			    पूर्णांक err)
अणु
	काष्ठा dw_mci_slot *slot = mmc_priv(mmc);
	काष्ठा mmc_data *data = mrq->data;

	अगर (!slot->host->use_dma || !data)
		वापस;

	अगर (data->host_cookie != COOKIE_UNMAPPED)
		dma_unmap_sg(slot->host->dev,
			     data->sg,
			     data->sg_len,
			     mmc_get_dma_dir(data));
	data->host_cookie = COOKIE_UNMAPPED;
पूर्ण

अटल पूर्णांक dw_mci_get_cd(काष्ठा mmc_host *mmc)
अणु
	पूर्णांक present;
	काष्ठा dw_mci_slot *slot = mmc_priv(mmc);
	काष्ठा dw_mci *host = slot->host;
	पूर्णांक gpio_cd = mmc_gpio_get_cd(mmc);

	/* Use platक्रमm get_cd function, अन्यथा try onboard card detect */
	अगर (((mmc->caps & MMC_CAP_NEEDS_POLL)
				|| !mmc_card_is_removable(mmc))) अणु
		present = 1;

		अगर (!test_bit(DW_MMC_CARD_PRESENT, &slot->flags)) अणु
			अगर (mmc->caps & MMC_CAP_NEEDS_POLL) अणु
				dev_info(&mmc->class_dev,
					"card is polling.\n");
			पूर्ण अन्यथा अणु
				dev_info(&mmc->class_dev,
					"card is non-removable.\n");
			पूर्ण
			set_bit(DW_MMC_CARD_PRESENT, &slot->flags);
		पूर्ण

		वापस present;
	पूर्ण अन्यथा अगर (gpio_cd >= 0)
		present = gpio_cd;
	अन्यथा
		present = (mci_पढ़ोl(slot->host, CDETECT) & (1 << slot->id))
			== 0 ? 1 : 0;

	spin_lock_bh(&host->lock);
	अगर (present && !test_and_set_bit(DW_MMC_CARD_PRESENT, &slot->flags))
		dev_dbg(&mmc->class_dev, "card is present\n");
	अन्यथा अगर (!present &&
			!test_and_clear_bit(DW_MMC_CARD_PRESENT, &slot->flags))
		dev_dbg(&mmc->class_dev, "card is not present\n");
	spin_unlock_bh(&host->lock);

	वापस present;
पूर्ण

अटल व्योम dw_mci_adjust_fअगरoth(काष्ठा dw_mci *host, काष्ठा mmc_data *data)
अणु
	अचिन्हित पूर्णांक blksz = data->blksz;
	अटल स्थिर u32 mszs[] = अणु1, 4, 8, 16, 32, 64, 128, 256पूर्ण;
	u32 fअगरo_width = 1 << host->data_shअगरt;
	u32 blksz_depth = blksz / fअगरo_width, fअगरoth_val;
	u32 msize = 0, rx_wmark = 1, tx_wmark, tx_wmark_invers;
	पूर्णांक idx = ARRAY_SIZE(mszs) - 1;

	/* pio should ship this scenario */
	अगर (!host->use_dma)
		वापस;

	tx_wmark = (host->fअगरo_depth) / 2;
	tx_wmark_invers = host->fअगरo_depth - tx_wmark;

	/*
	 * MSIZE is '1',
	 * अगर blksz is not a multiple of the FIFO width
	 */
	अगर (blksz % fअगरo_width)
		जाओ करोne;

	करो अणु
		अगर (!((blksz_depth % mszs[idx]) ||
		     (tx_wmark_invers % mszs[idx]))) अणु
			msize = idx;
			rx_wmark = mszs[idx] - 1;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (--idx > 0);
	/*
	 * If idx is '0', it won't be tried
	 * Thus, initial values are uesed
	 */
करोne:
	fअगरoth_val = SDMMC_SET_FIFOTH(msize, rx_wmark, tx_wmark);
	mci_ग_लिखोl(host, FIFOTH, fअगरoth_val);
पूर्ण

अटल व्योम dw_mci_ctrl_thld(काष्ठा dw_mci *host, काष्ठा mmc_data *data)
अणु
	अचिन्हित पूर्णांक blksz = data->blksz;
	u32 blksz_depth, fअगरo_depth;
	u16 thld_size;
	u8 enable;

	/*
	 * CDTHRCTL करोesn't exist prior to 240A (in fact that रेजिस्टर offset is
	 * in the FIFO region, so we really shouldn't access it).
	 */
	अगर (host->verid < DW_MMC_240A ||
		(host->verid < DW_MMC_280A && data->flags & MMC_DATA_WRITE))
		वापस;

	/*
	 * Card ग_लिखो Threshold is पूर्णांकroduced since 2.80a
	 * It's used when HS400 mode is enabled.
	 */
	अगर (data->flags & MMC_DATA_WRITE &&
		host->timing != MMC_TIMING_MMC_HS400)
		जाओ disable;

	अगर (data->flags & MMC_DATA_WRITE)
		enable = SDMMC_CARD_WR_THR_EN;
	अन्यथा
		enable = SDMMC_CARD_RD_THR_EN;

	अगर (host->timing != MMC_TIMING_MMC_HS200 &&
	    host->timing != MMC_TIMING_UHS_SDR104 &&
	    host->timing != MMC_TIMING_MMC_HS400)
		जाओ disable;

	blksz_depth = blksz / (1 << host->data_shअगरt);
	fअगरo_depth = host->fअगरo_depth;

	अगर (blksz_depth > fअगरo_depth)
		जाओ disable;

	/*
	 * If (blksz_depth) >= (fअगरo_depth >> 1), should be 'thld_size <= blksz'
	 * If (blksz_depth) <  (fअगरo_depth >> 1), should be thld_size = blksz
	 * Currently just choose blksz.
	 */
	thld_size = blksz;
	mci_ग_लिखोl(host, CDTHRCTL, SDMMC_SET_THLD(thld_size, enable));
	वापस;

disable:
	mci_ग_लिखोl(host, CDTHRCTL, 0);
पूर्ण

अटल पूर्णांक dw_mci_submit_data_dma(काष्ठा dw_mci *host, काष्ठा mmc_data *data)
अणु
	अचिन्हित दीर्घ irqflags;
	पूर्णांक sg_len;
	u32 temp;

	host->using_dma = 0;

	/* If we करोn't have a channel, we can't करो DMA */
	अगर (!host->use_dma)
		वापस -ENODEV;

	sg_len = dw_mci_pre_dma_transfer(host, data, COOKIE_MAPPED);
	अगर (sg_len < 0) अणु
		host->dma_ops->stop(host);
		वापस sg_len;
	पूर्ण

	host->using_dma = 1;

	अगर (host->use_dma == TRANS_MODE_IDMAC)
		dev_vdbg(host->dev,
			 "sd sg_cpu: %#lx sg_dma: %#lx sg_len: %d\n",
			 (अचिन्हित दीर्घ)host->sg_cpu,
			 (अचिन्हित दीर्घ)host->sg_dma,
			 sg_len);

	/*
	 * Decide the MSIZE and RX/TX Watermark.
	 * If current block size is same with previous size,
	 * no need to update fअगरoth.
	 */
	अगर (host->prev_blksz != data->blksz)
		dw_mci_adjust_fअगरoth(host, data);

	/* Enable the DMA पूर्णांकerface */
	temp = mci_पढ़ोl(host, CTRL);
	temp |= SDMMC_CTRL_DMA_ENABLE;
	mci_ग_लिखोl(host, CTRL, temp);

	/* Disable RX/TX IRQs, let DMA handle it */
	spin_lock_irqsave(&host->irq_lock, irqflags);
	temp = mci_पढ़ोl(host, INTMASK);
	temp  &= ~(SDMMC_INT_RXDR | SDMMC_INT_TXDR);
	mci_ग_लिखोl(host, INTMASK, temp);
	spin_unlock_irqrestore(&host->irq_lock, irqflags);

	अगर (host->dma_ops->start(host, sg_len)) अणु
		host->dma_ops->stop(host);
		/* We can't करो DMA, try PIO क्रम this one */
		dev_dbg(host->dev,
			"%s: fall back to PIO mode for current transfer\n",
			__func__);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dw_mci_submit_data(काष्ठा dw_mci *host, काष्ठा mmc_data *data)
अणु
	अचिन्हित दीर्घ irqflags;
	पूर्णांक flags = SG_MITER_ATOMIC;
	u32 temp;

	data->error = -EINPROGRESS;

	WARN_ON(host->data);
	host->sg = शून्य;
	host->data = data;

	अगर (data->flags & MMC_DATA_READ)
		host->dir_status = DW_MCI_RECV_STATUS;
	अन्यथा
		host->dir_status = DW_MCI_SEND_STATUS;

	dw_mci_ctrl_thld(host, data);

	अगर (dw_mci_submit_data_dma(host, data)) अणु
		अगर (host->data->flags & MMC_DATA_READ)
			flags |= SG_MITER_TO_SG;
		अन्यथा
			flags |= SG_MITER_FROM_SG;

		sg_miter_start(&host->sg_miter, data->sg, data->sg_len, flags);
		host->sg = data->sg;
		host->part_buf_start = 0;
		host->part_buf_count = 0;

		mci_ग_लिखोl(host, RINTSTS, SDMMC_INT_TXDR | SDMMC_INT_RXDR);

		spin_lock_irqsave(&host->irq_lock, irqflags);
		temp = mci_पढ़ोl(host, INTMASK);
		temp |= SDMMC_INT_TXDR | SDMMC_INT_RXDR;
		mci_ग_लिखोl(host, INTMASK, temp);
		spin_unlock_irqrestore(&host->irq_lock, irqflags);

		temp = mci_पढ़ोl(host, CTRL);
		temp &= ~SDMMC_CTRL_DMA_ENABLE;
		mci_ग_लिखोl(host, CTRL, temp);

		/*
		 * Use the initial fअगरoth_val क्रम PIO mode. If wm_algined
		 * is set, we set watermark same as data size.
		 * If next issued data may be transfered by DMA mode,
		 * prev_blksz should be invalidated.
		 */
		अगर (host->wm_aligned)
			dw_mci_adjust_fअगरoth(host, data);
		अन्यथा
			mci_ग_लिखोl(host, FIFOTH, host->fअगरoth_val);
		host->prev_blksz = 0;
	पूर्ण अन्यथा अणु
		/*
		 * Keep the current block size.
		 * It will be used to decide whether to update
		 * fअगरoth रेजिस्टर next समय.
		 */
		host->prev_blksz = data->blksz;
	पूर्ण
पूर्ण

अटल व्योम dw_mci_setup_bus(काष्ठा dw_mci_slot *slot, bool क्रमce_clkinit)
अणु
	काष्ठा dw_mci *host = slot->host;
	अचिन्हित पूर्णांक घड़ी = slot->घड़ी;
	u32 भाग;
	u32 clk_en_a;
	u32 sdmmc_cmd_bits = SDMMC_CMD_UPD_CLK | SDMMC_CMD_PRV_DAT_WAIT;

	/* We must जारी to set bit 28 in CMD until the change is complete */
	अगर (host->state == STATE_WAITING_CMD11_DONE)
		sdmmc_cmd_bits |= SDMMC_CMD_VOLT_SWITCH;

	slot->mmc->actual_घड़ी = 0;

	अगर (!घड़ी) अणु
		mci_ग_लिखोl(host, CLKENA, 0);
		mci_send_cmd(slot, sdmmc_cmd_bits, 0);
	पूर्ण अन्यथा अगर (घड़ी != host->current_speed || क्रमce_clkinit) अणु
		भाग = host->bus_hz / घड़ी;
		अगर (host->bus_hz % घड़ी && host->bus_hz > घड़ी)
			/*
			 * move the + 1 after the भागide to prevent
			 * over-घड़ीing the card.
			 */
			भाग += 1;

		भाग = (host->bus_hz != घड़ी) ? DIV_ROUND_UP(भाग, 2) : 0;

		अगर ((घड़ी != slot->__clk_old &&
			!test_bit(DW_MMC_CARD_NEEDS_POLL, &slot->flags)) ||
			क्रमce_clkinit) अणु
			/* Silent the verbose log अगर calling from PM context */
			अगर (!क्रमce_clkinit)
				dev_info(&slot->mmc->class_dev,
					 "Bus speed (slot %d) = %dHz (slot req %dHz, actual %dHZ div = %d)\n",
					 slot->id, host->bus_hz, घड़ी,
					 भाग ? ((host->bus_hz / भाग) >> 1) :
					 host->bus_hz, भाग);

			/*
			 * If card is polling, display the message only
			 * one समय at boot समय.
			 */
			अगर (slot->mmc->caps & MMC_CAP_NEEDS_POLL &&
					slot->mmc->f_min == घड़ी)
				set_bit(DW_MMC_CARD_NEEDS_POLL, &slot->flags);
		पूर्ण

		/* disable घड़ी */
		mci_ग_लिखोl(host, CLKENA, 0);
		mci_ग_लिखोl(host, CLKSRC, 0);

		/* inक्रमm CIU */
		mci_send_cmd(slot, sdmmc_cmd_bits, 0);

		/* set घड़ी to desired speed */
		mci_ग_लिखोl(host, CLKDIV, भाग);

		/* inक्रमm CIU */
		mci_send_cmd(slot, sdmmc_cmd_bits, 0);

		/* enable घड़ी; only low घातer अगर no SDIO */
		clk_en_a = SDMMC_CLKEN_ENABLE << slot->id;
		अगर (!test_bit(DW_MMC_CARD_NO_LOW_PWR, &slot->flags))
			clk_en_a |= SDMMC_CLKEN_LOW_PWR << slot->id;
		mci_ग_लिखोl(host, CLKENA, clk_en_a);

		/* inक्रमm CIU */
		mci_send_cmd(slot, sdmmc_cmd_bits, 0);

		/* keep the last घड़ी value that was requested from core */
		slot->__clk_old = घड़ी;
		slot->mmc->actual_घड़ी = भाग ? ((host->bus_hz / भाग) >> 1) :
					  host->bus_hz;
	पूर्ण

	host->current_speed = घड़ी;

	/* Set the current slot bus width */
	mci_ग_लिखोl(host, CTYPE, (slot->ctype << slot->id));
पूर्ण

अटल व्योम __dw_mci_start_request(काष्ठा dw_mci *host,
				   काष्ठा dw_mci_slot *slot,
				   काष्ठा mmc_command *cmd)
अणु
	काष्ठा mmc_request *mrq;
	काष्ठा mmc_data	*data;
	u32 cmdflags;

	mrq = slot->mrq;

	host->mrq = mrq;

	host->pending_events = 0;
	host->completed_events = 0;
	host->cmd_status = 0;
	host->data_status = 0;
	host->dir_status = 0;

	data = cmd->data;
	अगर (data) अणु
		mci_ग_लिखोl(host, TMOUT, 0xFFFFFFFF);
		mci_ग_लिखोl(host, BYTCNT, data->blksz*data->blocks);
		mci_ग_लिखोl(host, BLKSIZ, data->blksz);
	पूर्ण

	cmdflags = dw_mci_prepare_command(slot->mmc, cmd);

	/* this is the first command, send the initialization घड़ी */
	अगर (test_and_clear_bit(DW_MMC_CARD_NEED_INIT, &slot->flags))
		cmdflags |= SDMMC_CMD_INIT;

	अगर (data) अणु
		dw_mci_submit_data(host, data);
		wmb(); /* drain ग_लिखोbuffer */
	पूर्ण

	dw_mci_start_command(host, cmd, cmdflags);

	अगर (cmd->opcode == SD_SWITCH_VOLTAGE) अणु
		अचिन्हित दीर्घ irqflags;

		/*
		 * Databook says to fail after 2ms w/ no response, but evidence
		 * shows that someबार the cmd11 पूर्णांकerrupt takes over 130ms.
		 * We'll set to 500ms, plus an extra jअगरfy just in हाल jअगरfies
		 * is just about to roll over.
		 *
		 * We करो this whole thing under spinlock and only अगर the
		 * command hasn't alपढ़ोy completed (indicating the the irq
		 * alपढ़ोy ran so we करोn't want the समयout).
		 */
		spin_lock_irqsave(&host->irq_lock, irqflags);
		अगर (!test_bit(EVENT_CMD_COMPLETE, &host->pending_events))
			mod_समयr(&host->cmd11_समयr,
				jअगरfies + msecs_to_jअगरfies(500) + 1);
		spin_unlock_irqrestore(&host->irq_lock, irqflags);
	पूर्ण

	host->stop_cmdr = dw_mci_prep_stop_पात(host, cmd);
पूर्ण

अटल व्योम dw_mci_start_request(काष्ठा dw_mci *host,
				 काष्ठा dw_mci_slot *slot)
अणु
	काष्ठा mmc_request *mrq = slot->mrq;
	काष्ठा mmc_command *cmd;

	cmd = mrq->sbc ? mrq->sbc : mrq->cmd;
	__dw_mci_start_request(host, slot, cmd);
पूर्ण

/* must be called with host->lock held */
अटल व्योम dw_mci_queue_request(काष्ठा dw_mci *host, काष्ठा dw_mci_slot *slot,
				 काष्ठा mmc_request *mrq)
अणु
	dev_vdbg(&slot->mmc->class_dev, "queue request: state=%d\n",
		 host->state);

	slot->mrq = mrq;

	अगर (host->state == STATE_WAITING_CMD11_DONE) अणु
		dev_warn(&slot->mmc->class_dev,
			 "Voltage change didn't complete\n");
		/*
		 * this हाल isn't expected to happen, so we can
		 * either crash here or just try to जारी on
		 * in the बंदst possible state
		 */
		host->state = STATE_IDLE;
	पूर्ण

	अगर (host->state == STATE_IDLE) अणु
		host->state = STATE_SENDING_CMD;
		dw_mci_start_request(host, slot);
	पूर्ण अन्यथा अणु
		list_add_tail(&slot->queue_node, &host->queue);
	पूर्ण
पूर्ण

अटल व्योम dw_mci_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा dw_mci_slot *slot = mmc_priv(mmc);
	काष्ठा dw_mci *host = slot->host;

	WARN_ON(slot->mrq);

	/*
	 * The check क्रम card presence and queueing of the request must be
	 * atomic, otherwise the card could be हटाओd in between and the
	 * request wouldn't fail until another card was inserted.
	 */

	अगर (!dw_mci_get_cd(mmc)) अणु
		mrq->cmd->error = -ENOMEDIUM;
		mmc_request_करोne(mmc, mrq);
		वापस;
	पूर्ण

	spin_lock_bh(&host->lock);

	dw_mci_queue_request(host, slot, mrq);

	spin_unlock_bh(&host->lock);
पूर्ण

अटल व्योम dw_mci_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा dw_mci_slot *slot = mmc_priv(mmc);
	स्थिर काष्ठा dw_mci_drv_data *drv_data = slot->host->drv_data;
	u32 regs;
	पूर्णांक ret;

	चयन (ios->bus_width) अणु
	हाल MMC_BUS_WIDTH_4:
		slot->ctype = SDMMC_CTYPE_4BIT;
		अवरोध;
	हाल MMC_BUS_WIDTH_8:
		slot->ctype = SDMMC_CTYPE_8BIT;
		अवरोध;
	शेष:
		/* set शेष 1 bit mode */
		slot->ctype = SDMMC_CTYPE_1BIT;
	पूर्ण

	regs = mci_पढ़ोl(slot->host, UHS_REG);

	/* DDR mode set */
	अगर (ios->timing == MMC_TIMING_MMC_DDR52 ||
	    ios->timing == MMC_TIMING_UHS_DDR50 ||
	    ios->timing == MMC_TIMING_MMC_HS400)
		regs |= ((0x1 << slot->id) << 16);
	अन्यथा
		regs &= ~((0x1 << slot->id) << 16);

	mci_ग_लिखोl(slot->host, UHS_REG, regs);
	slot->host->timing = ios->timing;

	/*
	 * Use mirror of ios->घड़ी to prevent race with mmc
	 * core ios update when finding the minimum.
	 */
	slot->घड़ी = ios->घड़ी;

	अगर (drv_data && drv_data->set_ios)
		drv_data->set_ios(slot->host, ios);

	चयन (ios->घातer_mode) अणु
	हाल MMC_POWER_UP:
		अगर (!IS_ERR(mmc->supply.vmmc)) अणु
			ret = mmc_regulator_set_ocr(mmc, mmc->supply.vmmc,
					ios->vdd);
			अगर (ret) अणु
				dev_err(slot->host->dev,
					"failed to enable vmmc regulator\n");
				/*वापस, अगर failed turn on vmmc*/
				वापस;
			पूर्ण
		पूर्ण
		set_bit(DW_MMC_CARD_NEED_INIT, &slot->flags);
		regs = mci_पढ़ोl(slot->host, PWREN);
		regs |= (1 << slot->id);
		mci_ग_लिखोl(slot->host, PWREN, regs);
		अवरोध;
	हाल MMC_POWER_ON:
		अगर (!slot->host->vqmmc_enabled) अणु
			अगर (!IS_ERR(mmc->supply.vqmmc)) अणु
				ret = regulator_enable(mmc->supply.vqmmc);
				अगर (ret < 0)
					dev_err(slot->host->dev,
						"failed to enable vqmmc\n");
				अन्यथा
					slot->host->vqmmc_enabled = true;

			पूर्ण अन्यथा अणु
				/* Keep track so we करोn't reset again */
				slot->host->vqmmc_enabled = true;
			पूर्ण

			/* Reset our state machine after घातering on */
			dw_mci_ctrl_reset(slot->host,
					  SDMMC_CTRL_ALL_RESET_FLAGS);
		पूर्ण

		/* Adjust घड़ी / bus width after घातer is up */
		dw_mci_setup_bus(slot, false);

		अवरोध;
	हाल MMC_POWER_OFF:
		/* Turn घड़ी off beक्रमe घातer goes करोwn */
		dw_mci_setup_bus(slot, false);

		अगर (!IS_ERR(mmc->supply.vmmc))
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);

		अगर (!IS_ERR(mmc->supply.vqmmc) && slot->host->vqmmc_enabled)
			regulator_disable(mmc->supply.vqmmc);
		slot->host->vqmmc_enabled = false;

		regs = mci_पढ़ोl(slot->host, PWREN);
		regs &= ~(1 << slot->id);
		mci_ग_लिखोl(slot->host, PWREN, regs);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (slot->host->state == STATE_WAITING_CMD11_DONE && ios->घड़ी != 0)
		slot->host->state = STATE_IDLE;
पूर्ण

अटल पूर्णांक dw_mci_card_busy(काष्ठा mmc_host *mmc)
अणु
	काष्ठा dw_mci_slot *slot = mmc_priv(mmc);
	u32 status;

	/*
	 * Check the busy bit which is low when DAT[3:0]
	 * (the data lines) are 0000
	 */
	status = mci_पढ़ोl(slot->host, STATUS);

	वापस !!(status & SDMMC_STATUS_BUSY);
पूर्ण

अटल पूर्णांक dw_mci_चयन_voltage(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा dw_mci_slot *slot = mmc_priv(mmc);
	काष्ठा dw_mci *host = slot->host;
	स्थिर काष्ठा dw_mci_drv_data *drv_data = host->drv_data;
	u32 uhs;
	u32 v18 = SDMMC_UHS_18V << slot->id;
	पूर्णांक ret;

	अगर (drv_data && drv_data->चयन_voltage)
		वापस drv_data->चयन_voltage(mmc, ios);

	/*
	 * Program the voltage.  Note that some instances of dw_mmc may use
	 * the UHS_REG क्रम this.  For other instances (like exynos) the UHS_REG
	 * करोes no harm but you need to set the regulator directly.  Try both.
	 */
	uhs = mci_पढ़ोl(host, UHS_REG);
	अगर (ios->संकेत_voltage == MMC_SIGNAL_VOLTAGE_330)
		uhs &= ~v18;
	अन्यथा
		uhs |= v18;

	अगर (!IS_ERR(mmc->supply.vqmmc)) अणु
		ret = mmc_regulator_set_vqmmc(mmc, ios);
		अगर (ret < 0) अणु
			dev_dbg(&mmc->class_dev,
					 "Regulator set error %d - %s V\n",
					 ret, uhs & v18 ? "1.8" : "3.3");
			वापस ret;
		पूर्ण
	पूर्ण
	mci_ग_लिखोl(host, UHS_REG, uhs);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_mci_get_ro(काष्ठा mmc_host *mmc)
अणु
	पूर्णांक पढ़ो_only;
	काष्ठा dw_mci_slot *slot = mmc_priv(mmc);
	पूर्णांक gpio_ro = mmc_gpio_get_ro(mmc);

	/* Use platक्रमm get_ro function, अन्यथा try on board ग_लिखो protect */
	अगर (gpio_ro >= 0)
		पढ़ो_only = gpio_ro;
	अन्यथा
		पढ़ो_only =
			mci_पढ़ोl(slot->host, WRTPRT) & (1 << slot->id) ? 1 : 0;

	dev_dbg(&mmc->class_dev, "card is %s\n",
		पढ़ो_only ? "read-only" : "read-write");

	वापस पढ़ो_only;
पूर्ण

अटल व्योम dw_mci_hw_reset(काष्ठा mmc_host *mmc)
अणु
	काष्ठा dw_mci_slot *slot = mmc_priv(mmc);
	काष्ठा dw_mci *host = slot->host;
	पूर्णांक reset;

	अगर (host->use_dma == TRANS_MODE_IDMAC)
		dw_mci_idmac_reset(host);

	अगर (!dw_mci_ctrl_reset(host, SDMMC_CTRL_DMA_RESET |
				     SDMMC_CTRL_FIFO_RESET))
		वापस;

	/*
	 * According to eMMC spec, card reset procedure:
	 * tRstW >= 1us:   RST_n pulse width
	 * tRSCA >= 200us: RST_n to Command समय
	 * tRSTH >= 1us:   RST_n high period
	 */
	reset = mci_पढ़ोl(host, RST_N);
	reset &= ~(SDMMC_RST_HWACTIVE << slot->id);
	mci_ग_लिखोl(host, RST_N, reset);
	usleep_range(1, 2);
	reset |= SDMMC_RST_HWACTIVE << slot->id;
	mci_ग_लिखोl(host, RST_N, reset);
	usleep_range(200, 300);
पूर्ण

अटल व्योम dw_mci_init_card(काष्ठा mmc_host *mmc, काष्ठा mmc_card *card)
अणु
	काष्ठा dw_mci_slot *slot = mmc_priv(mmc);
	काष्ठा dw_mci *host = slot->host;

	/*
	 * Low घातer mode will stop the card घड़ी when idle.  According to the
	 * description of the CLKENA रेजिस्टर we should disable low घातer mode
	 * क्रम SDIO cards अगर we need SDIO पूर्णांकerrupts to work.
	 */
	अगर (mmc->caps & MMC_CAP_SDIO_IRQ) अणु
		स्थिर u32 clken_low_pwr = SDMMC_CLKEN_LOW_PWR << slot->id;
		u32 clk_en_a_old;
		u32 clk_en_a;

		clk_en_a_old = mci_पढ़ोl(host, CLKENA);

		अगर (card->type == MMC_TYPE_SDIO ||
		    card->type == MMC_TYPE_SD_COMBO) अणु
			set_bit(DW_MMC_CARD_NO_LOW_PWR, &slot->flags);
			clk_en_a = clk_en_a_old & ~clken_low_pwr;
		पूर्ण अन्यथा अणु
			clear_bit(DW_MMC_CARD_NO_LOW_PWR, &slot->flags);
			clk_en_a = clk_en_a_old | clken_low_pwr;
		पूर्ण

		अगर (clk_en_a != clk_en_a_old) अणु
			mci_ग_लिखोl(host, CLKENA, clk_en_a);
			mci_send_cmd(slot, SDMMC_CMD_UPD_CLK |
				     SDMMC_CMD_PRV_DAT_WAIT, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __dw_mci_enable_sdio_irq(काष्ठा dw_mci_slot *slot, पूर्णांक enb)
अणु
	काष्ठा dw_mci *host = slot->host;
	अचिन्हित दीर्घ irqflags;
	u32 पूर्णांक_mask;

	spin_lock_irqsave(&host->irq_lock, irqflags);

	/* Enable/disable Slot Specअगरic SDIO पूर्णांकerrupt */
	पूर्णांक_mask = mci_पढ़ोl(host, INTMASK);
	अगर (enb)
		पूर्णांक_mask |= SDMMC_INT_SDIO(slot->sdio_id);
	अन्यथा
		पूर्णांक_mask &= ~SDMMC_INT_SDIO(slot->sdio_id);
	mci_ग_लिखोl(host, INTMASK, पूर्णांक_mask);

	spin_unlock_irqrestore(&host->irq_lock, irqflags);
पूर्ण

अटल व्योम dw_mci_enable_sdio_irq(काष्ठा mmc_host *mmc, पूर्णांक enb)
अणु
	काष्ठा dw_mci_slot *slot = mmc_priv(mmc);
	काष्ठा dw_mci *host = slot->host;

	__dw_mci_enable_sdio_irq(slot, enb);

	/* Aव्योम runसमय suspending the device when SDIO IRQ is enabled */
	अगर (enb)
		pm_runसमय_get_noresume(host->dev);
	अन्यथा
		pm_runसमय_put_noidle(host->dev);
पूर्ण

अटल व्योम dw_mci_ack_sdio_irq(काष्ठा mmc_host *mmc)
अणु
	काष्ठा dw_mci_slot *slot = mmc_priv(mmc);

	__dw_mci_enable_sdio_irq(slot, 1);
पूर्ण

अटल पूर्णांक dw_mci_execute_tuning(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	काष्ठा dw_mci_slot *slot = mmc_priv(mmc);
	काष्ठा dw_mci *host = slot->host;
	स्थिर काष्ठा dw_mci_drv_data *drv_data = host->drv_data;
	पूर्णांक err = -EINVAL;

	अगर (drv_data && drv_data->execute_tuning)
		err = drv_data->execute_tuning(slot, opcode);
	वापस err;
पूर्ण

अटल पूर्णांक dw_mci_prepare_hs400_tuning(काष्ठा mmc_host *mmc,
				       काष्ठा mmc_ios *ios)
अणु
	काष्ठा dw_mci_slot *slot = mmc_priv(mmc);
	काष्ठा dw_mci *host = slot->host;
	स्थिर काष्ठा dw_mci_drv_data *drv_data = host->drv_data;

	अगर (drv_data && drv_data->prepare_hs400_tuning)
		वापस drv_data->prepare_hs400_tuning(host, ios);

	वापस 0;
पूर्ण

अटल bool dw_mci_reset(काष्ठा dw_mci *host)
अणु
	u32 flags = SDMMC_CTRL_RESET | SDMMC_CTRL_FIFO_RESET;
	bool ret = false;
	u32 status = 0;

	/*
	 * Resetting generates a block पूर्णांकerrupt, hence setting
	 * the scatter-gather poपूर्णांकer to शून्य.
	 */
	अगर (host->sg) अणु
		sg_miter_stop(&host->sg_miter);
		host->sg = शून्य;
	पूर्ण

	अगर (host->use_dma)
		flags |= SDMMC_CTRL_DMA_RESET;

	अगर (dw_mci_ctrl_reset(host, flags)) अणु
		/*
		 * In all हालs we clear the RAWINTS
		 * रेजिस्टर to clear any पूर्णांकerrupts.
		 */
		mci_ग_लिखोl(host, RINTSTS, 0xFFFFFFFF);

		अगर (!host->use_dma) अणु
			ret = true;
			जाओ ciu_out;
		पूर्ण

		/* Wait क्रम dma_req to be cleared */
		अगर (पढ़ोl_poll_समयout_atomic(host->regs + SDMMC_STATUS,
					      status,
					      !(status & SDMMC_STATUS_DMA_REQ),
					      1, 500 * USEC_PER_MSEC)) अणु
			dev_err(host->dev,
				"%s: Timeout waiting for dma_req to be cleared\n",
				__func__);
			जाओ ciu_out;
		पूर्ण

		/* when using DMA next we reset the fअगरo again */
		अगर (!dw_mci_ctrl_reset(host, SDMMC_CTRL_FIFO_RESET))
			जाओ ciu_out;
	पूर्ण अन्यथा अणु
		/* अगर the controller reset bit did clear, then set घड़ी regs */
		अगर (!(mci_पढ़ोl(host, CTRL) & SDMMC_CTRL_RESET)) अणु
			dev_err(host->dev,
				"%s: fifo/dma reset bits didn't clear but ciu was reset, doing clock update\n",
				__func__);
			जाओ ciu_out;
		पूर्ण
	पूर्ण

	अगर (host->use_dma == TRANS_MODE_IDMAC)
		/* It is also required that we reinit idmac */
		dw_mci_idmac_init(host);

	ret = true;

ciu_out:
	/* After a CTRL reset we need to have CIU set घड़ी रेजिस्टरs  */
	mci_send_cmd(host->slot, SDMMC_CMD_UPD_CLK, 0);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops dw_mci_ops = अणु
	.request		= dw_mci_request,
	.pre_req		= dw_mci_pre_req,
	.post_req		= dw_mci_post_req,
	.set_ios		= dw_mci_set_ios,
	.get_ro			= dw_mci_get_ro,
	.get_cd			= dw_mci_get_cd,
	.hw_reset               = dw_mci_hw_reset,
	.enable_sdio_irq	= dw_mci_enable_sdio_irq,
	.ack_sdio_irq		= dw_mci_ack_sdio_irq,
	.execute_tuning		= dw_mci_execute_tuning,
	.card_busy		= dw_mci_card_busy,
	.start_संकेत_voltage_चयन = dw_mci_चयन_voltage,
	.init_card		= dw_mci_init_card,
	.prepare_hs400_tuning	= dw_mci_prepare_hs400_tuning,
पूर्ण;

अटल व्योम dw_mci_request_end(काष्ठा dw_mci *host, काष्ठा mmc_request *mrq)
	__releases(&host->lock)
	__acquires(&host->lock)
अणु
	काष्ठा dw_mci_slot *slot;
	काष्ठा mmc_host	*prev_mmc = host->slot->mmc;

	WARN_ON(host->cmd || host->data);

	host->slot->mrq = शून्य;
	host->mrq = शून्य;
	अगर (!list_empty(&host->queue)) अणु
		slot = list_entry(host->queue.next,
				  काष्ठा dw_mci_slot, queue_node);
		list_del(&slot->queue_node);
		dev_vdbg(host->dev, "list not empty: %s is next\n",
			 mmc_hostname(slot->mmc));
		host->state = STATE_SENDING_CMD;
		dw_mci_start_request(host, slot);
	पूर्ण अन्यथा अणु
		dev_vdbg(host->dev, "list empty\n");

		अगर (host->state == STATE_SENDING_CMD11)
			host->state = STATE_WAITING_CMD11_DONE;
		अन्यथा
			host->state = STATE_IDLE;
	पूर्ण

	spin_unlock(&host->lock);
	mmc_request_करोne(prev_mmc, mrq);
	spin_lock(&host->lock);
पूर्ण

अटल पूर्णांक dw_mci_command_complete(काष्ठा dw_mci *host, काष्ठा mmc_command *cmd)
अणु
	u32 status = host->cmd_status;

	host->cmd_status = 0;

	/* Read the response from the card (up to 16 bytes) */
	अगर (cmd->flags & MMC_RSP_PRESENT) अणु
		अगर (cmd->flags & MMC_RSP_136) अणु
			cmd->resp[3] = mci_पढ़ोl(host, RESP0);
			cmd->resp[2] = mci_पढ़ोl(host, RESP1);
			cmd->resp[1] = mci_पढ़ोl(host, RESP2);
			cmd->resp[0] = mci_पढ़ोl(host, RESP3);
		पूर्ण अन्यथा अणु
			cmd->resp[0] = mci_पढ़ोl(host, RESP0);
			cmd->resp[1] = 0;
			cmd->resp[2] = 0;
			cmd->resp[3] = 0;
		पूर्ण
	पूर्ण

	अगर (status & SDMMC_INT_RTO)
		cmd->error = -ETIMEDOUT;
	अन्यथा अगर ((cmd->flags & MMC_RSP_CRC) && (status & SDMMC_INT_RCRC))
		cmd->error = -EILSEQ;
	अन्यथा अगर (status & SDMMC_INT_RESP_ERR)
		cmd->error = -EIO;
	अन्यथा
		cmd->error = 0;

	वापस cmd->error;
पूर्ण

अटल पूर्णांक dw_mci_data_complete(काष्ठा dw_mci *host, काष्ठा mmc_data *data)
अणु
	u32 status = host->data_status;

	अगर (status & DW_MCI_DATA_ERROR_FLAGS) अणु
		अगर (status & SDMMC_INT_DRTO) अणु
			data->error = -ETIMEDOUT;
		पूर्ण अन्यथा अगर (status & SDMMC_INT_DCRC) अणु
			data->error = -EILSEQ;
		पूर्ण अन्यथा अगर (status & SDMMC_INT_EBE) अणु
			अगर (host->dir_status ==
				DW_MCI_SEND_STATUS) अणु
				/*
				 * No data CRC status was वापसed.
				 * The number of bytes transferred
				 * will be exaggerated in PIO mode.
				 */
				data->bytes_xfered = 0;
				data->error = -ETIMEDOUT;
			पूर्ण अन्यथा अगर (host->dir_status ==
					DW_MCI_RECV_STATUS) अणु
				data->error = -EILSEQ;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* SDMMC_INT_SBE is included */
			data->error = -EILSEQ;
		पूर्ण

		dev_dbg(host->dev, "data error, status 0x%08x\n", status);

		/*
		 * After an error, there may be data lingering
		 * in the FIFO
		 */
		dw_mci_reset(host);
	पूर्ण अन्यथा अणु
		data->bytes_xfered = data->blocks * data->blksz;
		data->error = 0;
	पूर्ण

	वापस data->error;
पूर्ण

अटल व्योम dw_mci_set_drto(काष्ठा dw_mci *host)
अणु
	अचिन्हित पूर्णांक drto_clks;
	अचिन्हित पूर्णांक drto_भाग;
	अचिन्हित पूर्णांक drto_ms;
	अचिन्हित दीर्घ irqflags;

	drto_clks = mci_पढ़ोl(host, TMOUT) >> 8;
	drto_भाग = (mci_पढ़ोl(host, CLKDIV) & 0xff) * 2;
	अगर (drto_भाग == 0)
		drto_भाग = 1;

	drto_ms = DIV_ROUND_UP_ULL((u64)MSEC_PER_SEC * drto_clks * drto_भाग,
				   host->bus_hz);

	/* add a bit spare समय */
	drto_ms += 10;

	spin_lock_irqsave(&host->irq_lock, irqflags);
	अगर (!test_bit(EVENT_DATA_COMPLETE, &host->pending_events))
		mod_समयr(&host->dto_समयr,
			  jअगरfies + msecs_to_jअगरfies(drto_ms));
	spin_unlock_irqrestore(&host->irq_lock, irqflags);
पूर्ण

अटल bool dw_mci_clear_pending_cmd_complete(काष्ठा dw_mci *host)
अणु
	अगर (!test_bit(EVENT_CMD_COMPLETE, &host->pending_events))
		वापस false;

	/*
	 * Really be certain that the समयr has stopped.  This is a bit of
	 * paranoia and could only really happen अगर we had really bad
	 * पूर्णांकerrupt latency and the पूर्णांकerrupt routine and समयout were
	 * running concurrently so that the del_समयr() in the पूर्णांकerrupt
	 * handler couldn't run.
	 */
	WARN_ON(del_समयr_sync(&host->cto_समयr));
	clear_bit(EVENT_CMD_COMPLETE, &host->pending_events);

	वापस true;
पूर्ण

अटल bool dw_mci_clear_pending_data_complete(काष्ठा dw_mci *host)
अणु
	अगर (!test_bit(EVENT_DATA_COMPLETE, &host->pending_events))
		वापस false;

	/* Extra paranoia just like dw_mci_clear_pending_cmd_complete() */
	WARN_ON(del_समयr_sync(&host->dto_समयr));
	clear_bit(EVENT_DATA_COMPLETE, &host->pending_events);

	वापस true;
पूर्ण

अटल व्योम dw_mci_tasklet_func(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा dw_mci *host = from_tasklet(host, t, tasklet);
	काष्ठा mmc_data	*data;
	काष्ठा mmc_command *cmd;
	काष्ठा mmc_request *mrq;
	क्रमागत dw_mci_state state;
	क्रमागत dw_mci_state prev_state;
	अचिन्हित पूर्णांक err;

	spin_lock(&host->lock);

	state = host->state;
	data = host->data;
	mrq = host->mrq;

	करो अणु
		prev_state = state;

		चयन (state) अणु
		हाल STATE_IDLE:
		हाल STATE_WAITING_CMD11_DONE:
			अवरोध;

		हाल STATE_SENDING_CMD11:
		हाल STATE_SENDING_CMD:
			अगर (!dw_mci_clear_pending_cmd_complete(host))
				अवरोध;

			cmd = host->cmd;
			host->cmd = शून्य;
			set_bit(EVENT_CMD_COMPLETE, &host->completed_events);
			err = dw_mci_command_complete(host, cmd);
			अगर (cmd == mrq->sbc && !err) अणु
				__dw_mci_start_request(host, host->slot,
						       mrq->cmd);
				जाओ unlock;
			पूर्ण

			अगर (cmd->data && err) अणु
				/*
				 * During UHS tuning sequence, sending the stop
				 * command after the response CRC error would
				 * throw the प्रणाली पूर्णांकo a confused state
				 * causing all future tuning phases to report
				 * failure.
				 *
				 * In such हाल controller will move पूर्णांकo a data
				 * transfer state after a response error or
				 * response CRC error. Let's let that finish
				 * beक्रमe trying to send a stop, so we'll go to
				 * STATE_SENDING_DATA.
				 *
				 * Although letting the data transfer take place
				 * will waste a bit of समय (we alपढ़ोy know
				 * the command was bad), it can't cause any
				 * errors since it's possible it would have
				 * taken place anyway अगर this tasklet got
				 * delayed. Allowing the transfer to take place
				 * aव्योमs races and keeps things simple.
				 */
				अगर (err != -ETIMEDOUT) अणु
					state = STATE_SENDING_DATA;
					जारी;
				पूर्ण

				dw_mci_stop_dma(host);
				send_stop_पात(host, data);
				state = STATE_SENDING_STOP;
				अवरोध;
			पूर्ण

			अगर (!cmd->data || err) अणु
				dw_mci_request_end(host, mrq);
				जाओ unlock;
			पूर्ण

			prev_state = state = STATE_SENDING_DATA;
			fallthrough;

		हाल STATE_SENDING_DATA:
			/*
			 * We could get a data error and never a transfer
			 * complete so we'd better check क्रम it here.
			 *
			 * Note that we करोn't really care अगर we also got a
			 * transfer complete; stopping the DMA and sending an
			 * पात won't hurt.
			 */
			अगर (test_and_clear_bit(EVENT_DATA_ERROR,
					       &host->pending_events)) अणु
				dw_mci_stop_dma(host);
				अगर (!(host->data_status & (SDMMC_INT_DRTO |
							   SDMMC_INT_EBE)))
					send_stop_पात(host, data);
				state = STATE_DATA_ERROR;
				अवरोध;
			पूर्ण

			अगर (!test_and_clear_bit(EVENT_XFER_COMPLETE,
						&host->pending_events)) अणु
				/*
				 * If all data-related पूर्णांकerrupts करोn't come
				 * within the given समय in पढ़ोing data state.
				 */
				अगर (host->dir_status == DW_MCI_RECV_STATUS)
					dw_mci_set_drto(host);
				अवरोध;
			पूर्ण

			set_bit(EVENT_XFER_COMPLETE, &host->completed_events);

			/*
			 * Handle an EVENT_DATA_ERROR that might have shown up
			 * beक्रमe the transfer completed.  This might not have
			 * been caught by the check above because the पूर्णांकerrupt
			 * could have gone off between the previous check and
			 * the check क्रम transfer complete.
			 *
			 * Technically this ought not be needed assuming we
			 * get a DATA_COMPLETE eventually (we'll notice the
			 * error and end the request), but it shouldn't hurt.
			 *
			 * This has the advantage of sending the stop command.
			 */
			अगर (test_and_clear_bit(EVENT_DATA_ERROR,
					       &host->pending_events)) अणु
				dw_mci_stop_dma(host);
				अगर (!(host->data_status & (SDMMC_INT_DRTO |
							   SDMMC_INT_EBE)))
					send_stop_पात(host, data);
				state = STATE_DATA_ERROR;
				अवरोध;
			पूर्ण
			prev_state = state = STATE_DATA_BUSY;

			fallthrough;

		हाल STATE_DATA_BUSY:
			अगर (!dw_mci_clear_pending_data_complete(host)) अणु
				/*
				 * If data error पूर्णांकerrupt comes but data over
				 * पूर्णांकerrupt करोesn't come within the given समय.
				 * in पढ़ोing data state.
				 */
				अगर (host->dir_status == DW_MCI_RECV_STATUS)
					dw_mci_set_drto(host);
				अवरोध;
			पूर्ण

			host->data = शून्य;
			set_bit(EVENT_DATA_COMPLETE, &host->completed_events);
			err = dw_mci_data_complete(host, data);

			अगर (!err) अणु
				अगर (!data->stop || mrq->sbc) अणु
					अगर (mrq->sbc && data->stop)
						data->stop->error = 0;
					dw_mci_request_end(host, mrq);
					जाओ unlock;
				पूर्ण

				/* stop command क्रम खोलो-ended transfer*/
				अगर (data->stop)
					send_stop_पात(host, data);
			पूर्ण अन्यथा अणु
				/*
				 * If we करोn't have a command complete now we'll
				 * never get one since we just reset everything;
				 * better end the request.
				 *
				 * If we करो have a command complete we'll fall
				 * through to the SENDING_STOP command and
				 * everything will be peachy keen.
				 */
				अगर (!test_bit(EVENT_CMD_COMPLETE,
					      &host->pending_events)) अणु
					host->cmd = शून्य;
					dw_mci_request_end(host, mrq);
					जाओ unlock;
				पूर्ण
			पूर्ण

			/*
			 * If err has non-zero,
			 * stop-पात command has been alपढ़ोy issued.
			 */
			prev_state = state = STATE_SENDING_STOP;

			fallthrough;

		हाल STATE_SENDING_STOP:
			अगर (!dw_mci_clear_pending_cmd_complete(host))
				अवरोध;

			/* CMD error in data command */
			अगर (mrq->cmd->error && mrq->data)
				dw_mci_reset(host);

			host->cmd = शून्य;
			host->data = शून्य;

			अगर (!mrq->sbc && mrq->stop)
				dw_mci_command_complete(host, mrq->stop);
			अन्यथा
				host->cmd_status = 0;

			dw_mci_request_end(host, mrq);
			जाओ unlock;

		हाल STATE_DATA_ERROR:
			अगर (!test_and_clear_bit(EVENT_XFER_COMPLETE,
						&host->pending_events))
				अवरोध;

			state = STATE_DATA_BUSY;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (state != prev_state);

	host->state = state;
unlock:
	spin_unlock(&host->lock);

पूर्ण

/* push final bytes to part_buf, only use during push */
अटल व्योम dw_mci_set_part_bytes(काष्ठा dw_mci *host, व्योम *buf, पूर्णांक cnt)
अणु
	स_नकल((व्योम *)&host->part_buf, buf, cnt);
	host->part_buf_count = cnt;
पूर्ण

/* append bytes to part_buf, only use during push */
अटल पूर्णांक dw_mci_push_part_bytes(काष्ठा dw_mci *host, व्योम *buf, पूर्णांक cnt)
अणु
	cnt = min(cnt, (1 << host->data_shअगरt) - host->part_buf_count);
	स_नकल((व्योम *)&host->part_buf + host->part_buf_count, buf, cnt);
	host->part_buf_count += cnt;
	वापस cnt;
पूर्ण

/* pull first bytes from part_buf, only use during pull */
अटल पूर्णांक dw_mci_pull_part_bytes(काष्ठा dw_mci *host, व्योम *buf, पूर्णांक cnt)
अणु
	cnt = min_t(पूर्णांक, cnt, host->part_buf_count);
	अगर (cnt) अणु
		स_नकल(buf, (व्योम *)&host->part_buf + host->part_buf_start,
		       cnt);
		host->part_buf_count -= cnt;
		host->part_buf_start += cnt;
	पूर्ण
	वापस cnt;
पूर्ण

/* pull final bytes from the part_buf, assuming it's just been filled */
अटल व्योम dw_mci_pull_final_bytes(काष्ठा dw_mci *host, व्योम *buf, पूर्णांक cnt)
अणु
	स_नकल(buf, &host->part_buf, cnt);
	host->part_buf_start = cnt;
	host->part_buf_count = (1 << host->data_shअगरt) - cnt;
पूर्ण

अटल व्योम dw_mci_push_data16(काष्ठा dw_mci *host, व्योम *buf, पूर्णांक cnt)
अणु
	काष्ठा mmc_data *data = host->data;
	पूर्णांक init_cnt = cnt;

	/* try and push anything in the part_buf */
	अगर (unlikely(host->part_buf_count)) अणु
		पूर्णांक len = dw_mci_push_part_bytes(host, buf, cnt);

		buf += len;
		cnt -= len;
		अगर (host->part_buf_count == 2) अणु
			mci_fअगरo_ग_लिखोw(host->fअगरo_reg, host->part_buf16);
			host->part_buf_count = 0;
		पूर्ण
	पूर्ण
#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	अगर (unlikely((अचिन्हित दीर्घ)buf & 0x1)) अणु
		जबतक (cnt >= 2) अणु
			u16 aligned_buf[64];
			पूर्णांक len = min(cnt & -2, (पूर्णांक)माप(aligned_buf));
			पूर्णांक items = len >> 1;
			पूर्णांक i;
			/* स_नकल from input buffer पूर्णांकo aligned buffer */
			स_नकल(aligned_buf, buf, len);
			buf += len;
			cnt -= len;
			/* push data from aligned buffer पूर्णांकo fअगरo */
			क्रम (i = 0; i < items; ++i)
				mci_fअगरo_ग_लिखोw(host->fअगरo_reg, aligned_buf[i]);
		पूर्ण
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		u16 *pdata = buf;

		क्रम (; cnt >= 2; cnt -= 2)
			mci_fअगरo_ग_लिखोw(host->fअगरo_reg, *pdata++);
		buf = pdata;
	पूर्ण
	/* put anything reमुख्यing in the part_buf */
	अगर (cnt) अणु
		dw_mci_set_part_bytes(host, buf, cnt);
		 /* Push data अगर we have reached the expected data length */
		अगर ((data->bytes_xfered + init_cnt) ==
		    (data->blksz * data->blocks))
			mci_fअगरo_ग_लिखोw(host->fअगरo_reg, host->part_buf16);
	पूर्ण
पूर्ण

अटल व्योम dw_mci_pull_data16(काष्ठा dw_mci *host, व्योम *buf, पूर्णांक cnt)
अणु
#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	अगर (unlikely((अचिन्हित दीर्घ)buf & 0x1)) अणु
		जबतक (cnt >= 2) अणु
			/* pull data from fअगरo पूर्णांकo aligned buffer */
			u16 aligned_buf[64];
			पूर्णांक len = min(cnt & -2, (पूर्णांक)माप(aligned_buf));
			पूर्णांक items = len >> 1;
			पूर्णांक i;

			क्रम (i = 0; i < items; ++i)
				aligned_buf[i] = mci_fअगरo_पढ़ोw(host->fअगरo_reg);
			/* स_नकल from aligned buffer पूर्णांकo output buffer */
			स_नकल(buf, aligned_buf, len);
			buf += len;
			cnt -= len;
		पूर्ण
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		u16 *pdata = buf;

		क्रम (; cnt >= 2; cnt -= 2)
			*pdata++ = mci_fअगरo_पढ़ोw(host->fअगरo_reg);
		buf = pdata;
	पूर्ण
	अगर (cnt) अणु
		host->part_buf16 = mci_fअगरo_पढ़ोw(host->fअगरo_reg);
		dw_mci_pull_final_bytes(host, buf, cnt);
	पूर्ण
पूर्ण

अटल व्योम dw_mci_push_data32(काष्ठा dw_mci *host, व्योम *buf, पूर्णांक cnt)
अणु
	काष्ठा mmc_data *data = host->data;
	पूर्णांक init_cnt = cnt;

	/* try and push anything in the part_buf */
	अगर (unlikely(host->part_buf_count)) अणु
		पूर्णांक len = dw_mci_push_part_bytes(host, buf, cnt);

		buf += len;
		cnt -= len;
		अगर (host->part_buf_count == 4) अणु
			mci_fअगरo_ग_लिखोl(host->fअगरo_reg,	host->part_buf32);
			host->part_buf_count = 0;
		पूर्ण
	पूर्ण
#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	अगर (unlikely((अचिन्हित दीर्घ)buf & 0x3)) अणु
		जबतक (cnt >= 4) अणु
			u32 aligned_buf[32];
			पूर्णांक len = min(cnt & -4, (पूर्णांक)माप(aligned_buf));
			पूर्णांक items = len >> 2;
			पूर्णांक i;
			/* स_नकल from input buffer पूर्णांकo aligned buffer */
			स_नकल(aligned_buf, buf, len);
			buf += len;
			cnt -= len;
			/* push data from aligned buffer पूर्णांकo fअगरo */
			क्रम (i = 0; i < items; ++i)
				mci_fअगरo_ग_लिखोl(host->fअगरo_reg,	aligned_buf[i]);
		पूर्ण
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		u32 *pdata = buf;

		क्रम (; cnt >= 4; cnt -= 4)
			mci_fअगरo_ग_लिखोl(host->fअगरo_reg, *pdata++);
		buf = pdata;
	पूर्ण
	/* put anything reमुख्यing in the part_buf */
	अगर (cnt) अणु
		dw_mci_set_part_bytes(host, buf, cnt);
		 /* Push data अगर we have reached the expected data length */
		अगर ((data->bytes_xfered + init_cnt) ==
		    (data->blksz * data->blocks))
			mci_fअगरo_ग_लिखोl(host->fअगरo_reg, host->part_buf32);
	पूर्ण
पूर्ण

अटल व्योम dw_mci_pull_data32(काष्ठा dw_mci *host, व्योम *buf, पूर्णांक cnt)
अणु
#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	अगर (unlikely((अचिन्हित दीर्घ)buf & 0x3)) अणु
		जबतक (cnt >= 4) अणु
			/* pull data from fअगरo पूर्णांकo aligned buffer */
			u32 aligned_buf[32];
			पूर्णांक len = min(cnt & -4, (पूर्णांक)माप(aligned_buf));
			पूर्णांक items = len >> 2;
			पूर्णांक i;

			क्रम (i = 0; i < items; ++i)
				aligned_buf[i] = mci_fअगरo_पढ़ोl(host->fअगरo_reg);
			/* स_नकल from aligned buffer पूर्णांकo output buffer */
			स_नकल(buf, aligned_buf, len);
			buf += len;
			cnt -= len;
		पूर्ण
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		u32 *pdata = buf;

		क्रम (; cnt >= 4; cnt -= 4)
			*pdata++ = mci_fअगरo_पढ़ोl(host->fअगरo_reg);
		buf = pdata;
	पूर्ण
	अगर (cnt) अणु
		host->part_buf32 = mci_fअगरo_पढ़ोl(host->fअगरo_reg);
		dw_mci_pull_final_bytes(host, buf, cnt);
	पूर्ण
पूर्ण

अटल व्योम dw_mci_push_data64(काष्ठा dw_mci *host, व्योम *buf, पूर्णांक cnt)
अणु
	काष्ठा mmc_data *data = host->data;
	पूर्णांक init_cnt = cnt;

	/* try and push anything in the part_buf */
	अगर (unlikely(host->part_buf_count)) अणु
		पूर्णांक len = dw_mci_push_part_bytes(host, buf, cnt);

		buf += len;
		cnt -= len;

		अगर (host->part_buf_count == 8) अणु
			mci_fअगरo_ग_लिखोq(host->fअगरo_reg,	host->part_buf);
			host->part_buf_count = 0;
		पूर्ण
	पूर्ण
#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	अगर (unlikely((अचिन्हित दीर्घ)buf & 0x7)) अणु
		जबतक (cnt >= 8) अणु
			u64 aligned_buf[16];
			पूर्णांक len = min(cnt & -8, (पूर्णांक)माप(aligned_buf));
			पूर्णांक items = len >> 3;
			पूर्णांक i;
			/* स_नकल from input buffer पूर्णांकo aligned buffer */
			स_नकल(aligned_buf, buf, len);
			buf += len;
			cnt -= len;
			/* push data from aligned buffer पूर्णांकo fअगरo */
			क्रम (i = 0; i < items; ++i)
				mci_fअगरo_ग_लिखोq(host->fअगरo_reg,	aligned_buf[i]);
		पूर्ण
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		u64 *pdata = buf;

		क्रम (; cnt >= 8; cnt -= 8)
			mci_fअगरo_ग_लिखोq(host->fअगरo_reg, *pdata++);
		buf = pdata;
	पूर्ण
	/* put anything reमुख्यing in the part_buf */
	अगर (cnt) अणु
		dw_mci_set_part_bytes(host, buf, cnt);
		/* Push data अगर we have reached the expected data length */
		अगर ((data->bytes_xfered + init_cnt) ==
		    (data->blksz * data->blocks))
			mci_fअगरo_ग_लिखोq(host->fअगरo_reg, host->part_buf);
	पूर्ण
पूर्ण

अटल व्योम dw_mci_pull_data64(काष्ठा dw_mci *host, व्योम *buf, पूर्णांक cnt)
अणु
#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	अगर (unlikely((अचिन्हित दीर्घ)buf & 0x7)) अणु
		जबतक (cnt >= 8) अणु
			/* pull data from fअगरo पूर्णांकo aligned buffer */
			u64 aligned_buf[16];
			पूर्णांक len = min(cnt & -8, (पूर्णांक)माप(aligned_buf));
			पूर्णांक items = len >> 3;
			पूर्णांक i;

			क्रम (i = 0; i < items; ++i)
				aligned_buf[i] = mci_fअगरo_पढ़ोq(host->fअगरo_reg);

			/* स_नकल from aligned buffer पूर्णांकo output buffer */
			स_नकल(buf, aligned_buf, len);
			buf += len;
			cnt -= len;
		पूर्ण
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		u64 *pdata = buf;

		क्रम (; cnt >= 8; cnt -= 8)
			*pdata++ = mci_fअगरo_पढ़ोq(host->fअगरo_reg);
		buf = pdata;
	पूर्ण
	अगर (cnt) अणु
		host->part_buf = mci_fअगरo_पढ़ोq(host->fअगरo_reg);
		dw_mci_pull_final_bytes(host, buf, cnt);
	पूर्ण
पूर्ण

अटल व्योम dw_mci_pull_data(काष्ठा dw_mci *host, व्योम *buf, पूर्णांक cnt)
अणु
	पूर्णांक len;

	/* get reमुख्यing partial bytes */
	len = dw_mci_pull_part_bytes(host, buf, cnt);
	अगर (unlikely(len == cnt))
		वापस;
	buf += len;
	cnt -= len;

	/* get the rest of the data */
	host->pull_data(host, buf, cnt);
पूर्ण

अटल व्योम dw_mci_पढ़ो_data_pio(काष्ठा dw_mci *host, bool dto)
अणु
	काष्ठा sg_mapping_iter *sg_miter = &host->sg_miter;
	व्योम *buf;
	अचिन्हित पूर्णांक offset;
	काष्ठा mmc_data	*data = host->data;
	पूर्णांक shअगरt = host->data_shअगरt;
	u32 status;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक reमुख्य, fcnt;

	करो अणु
		अगर (!sg_miter_next(sg_miter))
			जाओ करोne;

		host->sg = sg_miter->piter.sg;
		buf = sg_miter->addr;
		reमुख्य = sg_miter->length;
		offset = 0;

		करो अणु
			fcnt = (SDMMC_GET_FCNT(mci_पढ़ोl(host, STATUS))
					<< shअगरt) + host->part_buf_count;
			len = min(reमुख्य, fcnt);
			अगर (!len)
				अवरोध;
			dw_mci_pull_data(host, (व्योम *)(buf + offset), len);
			data->bytes_xfered += len;
			offset += len;
			reमुख्य -= len;
		पूर्ण जबतक (reमुख्य);

		sg_miter->consumed = offset;
		status = mci_पढ़ोl(host, MINTSTS);
		mci_ग_लिखोl(host, RINTSTS, SDMMC_INT_RXDR);
	/* अगर the RXDR is पढ़ोy पढ़ो again */
	पूर्ण जबतक ((status & SDMMC_INT_RXDR) ||
		 (dto && SDMMC_GET_FCNT(mci_पढ़ोl(host, STATUS))));

	अगर (!reमुख्य) अणु
		अगर (!sg_miter_next(sg_miter))
			जाओ करोne;
		sg_miter->consumed = 0;
	पूर्ण
	sg_miter_stop(sg_miter);
	वापस;

करोne:
	sg_miter_stop(sg_miter);
	host->sg = शून्य;
	smp_wmb(); /* drain ग_लिखोbuffer */
	set_bit(EVENT_XFER_COMPLETE, &host->pending_events);
पूर्ण

अटल व्योम dw_mci_ग_लिखो_data_pio(काष्ठा dw_mci *host)
अणु
	काष्ठा sg_mapping_iter *sg_miter = &host->sg_miter;
	व्योम *buf;
	अचिन्हित पूर्णांक offset;
	काष्ठा mmc_data	*data = host->data;
	पूर्णांक shअगरt = host->data_shअगरt;
	u32 status;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक fअगरo_depth = host->fअगरo_depth;
	अचिन्हित पूर्णांक reमुख्य, fcnt;

	करो अणु
		अगर (!sg_miter_next(sg_miter))
			जाओ करोne;

		host->sg = sg_miter->piter.sg;
		buf = sg_miter->addr;
		reमुख्य = sg_miter->length;
		offset = 0;

		करो अणु
			fcnt = ((fअगरo_depth -
				 SDMMC_GET_FCNT(mci_पढ़ोl(host, STATUS)))
					<< shअगरt) - host->part_buf_count;
			len = min(reमुख्य, fcnt);
			अगर (!len)
				अवरोध;
			host->push_data(host, (व्योम *)(buf + offset), len);
			data->bytes_xfered += len;
			offset += len;
			reमुख्य -= len;
		पूर्ण जबतक (reमुख्य);

		sg_miter->consumed = offset;
		status = mci_पढ़ोl(host, MINTSTS);
		mci_ग_लिखोl(host, RINTSTS, SDMMC_INT_TXDR);
	पूर्ण जबतक (status & SDMMC_INT_TXDR); /* अगर TXDR ग_लिखो again */

	अगर (!reमुख्य) अणु
		अगर (!sg_miter_next(sg_miter))
			जाओ करोne;
		sg_miter->consumed = 0;
	पूर्ण
	sg_miter_stop(sg_miter);
	वापस;

करोne:
	sg_miter_stop(sg_miter);
	host->sg = शून्य;
	smp_wmb(); /* drain ग_लिखोbuffer */
	set_bit(EVENT_XFER_COMPLETE, &host->pending_events);
पूर्ण

अटल व्योम dw_mci_cmd_पूर्णांकerrupt(काष्ठा dw_mci *host, u32 status)
अणु
	del_समयr(&host->cto_समयr);

	अगर (!host->cmd_status)
		host->cmd_status = status;

	smp_wmb(); /* drain ग_लिखोbuffer */

	set_bit(EVENT_CMD_COMPLETE, &host->pending_events);
	tasklet_schedule(&host->tasklet);
पूर्ण

अटल व्योम dw_mci_handle_cd(काष्ठा dw_mci *host)
अणु
	काष्ठा dw_mci_slot *slot = host->slot;

	mmc_detect_change(slot->mmc,
		msecs_to_jअगरfies(host->pdata->detect_delay_ms));
पूर्ण

अटल irqवापस_t dw_mci_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा dw_mci *host = dev_id;
	u32 pending;
	काष्ठा dw_mci_slot *slot = host->slot;

	pending = mci_पढ़ोl(host, MINTSTS); /* पढ़ो-only mask reg */

	अगर (pending) अणु
		/* Check volt चयन first, since it can look like an error */
		अगर ((host->state == STATE_SENDING_CMD11) &&
		    (pending & SDMMC_INT_VOLT_SWITCH)) अणु
			mci_ग_लिखोl(host, RINTSTS, SDMMC_INT_VOLT_SWITCH);
			pending &= ~SDMMC_INT_VOLT_SWITCH;

			/*
			 * Hold the lock; we know cmd11_समयr can't be kicked
			 * off after the lock is released, so safe to delete.
			 */
			spin_lock(&host->irq_lock);
			dw_mci_cmd_पूर्णांकerrupt(host, pending);
			spin_unlock(&host->irq_lock);

			del_समयr(&host->cmd11_समयr);
		पूर्ण

		अगर (pending & DW_MCI_CMD_ERROR_FLAGS) अणु
			spin_lock(&host->irq_lock);

			del_समयr(&host->cto_समयr);
			mci_ग_लिखोl(host, RINTSTS, DW_MCI_CMD_ERROR_FLAGS);
			host->cmd_status = pending;
			smp_wmb(); /* drain ग_लिखोbuffer */
			set_bit(EVENT_CMD_COMPLETE, &host->pending_events);

			spin_unlock(&host->irq_lock);
		पूर्ण

		अगर (pending & DW_MCI_DATA_ERROR_FLAGS) अणु
			/* अगर there is an error report DATA_ERROR */
			mci_ग_लिखोl(host, RINTSTS, DW_MCI_DATA_ERROR_FLAGS);
			host->data_status = pending;
			smp_wmb(); /* drain ग_लिखोbuffer */
			set_bit(EVENT_DATA_ERROR, &host->pending_events);
			tasklet_schedule(&host->tasklet);
		पूर्ण

		अगर (pending & SDMMC_INT_DATA_OVER) अणु
			spin_lock(&host->irq_lock);

			del_समयr(&host->dto_समयr);

			mci_ग_लिखोl(host, RINTSTS, SDMMC_INT_DATA_OVER);
			अगर (!host->data_status)
				host->data_status = pending;
			smp_wmb(); /* drain ग_लिखोbuffer */
			अगर (host->dir_status == DW_MCI_RECV_STATUS) अणु
				अगर (host->sg != शून्य)
					dw_mci_पढ़ो_data_pio(host, true);
			पूर्ण
			set_bit(EVENT_DATA_COMPLETE, &host->pending_events);
			tasklet_schedule(&host->tasklet);

			spin_unlock(&host->irq_lock);
		पूर्ण

		अगर (pending & SDMMC_INT_RXDR) अणु
			mci_ग_लिखोl(host, RINTSTS, SDMMC_INT_RXDR);
			अगर (host->dir_status == DW_MCI_RECV_STATUS && host->sg)
				dw_mci_पढ़ो_data_pio(host, false);
		पूर्ण

		अगर (pending & SDMMC_INT_TXDR) अणु
			mci_ग_लिखोl(host, RINTSTS, SDMMC_INT_TXDR);
			अगर (host->dir_status == DW_MCI_SEND_STATUS && host->sg)
				dw_mci_ग_लिखो_data_pio(host);
		पूर्ण

		अगर (pending & SDMMC_INT_CMD_DONE) अणु
			spin_lock(&host->irq_lock);

			mci_ग_लिखोl(host, RINTSTS, SDMMC_INT_CMD_DONE);
			dw_mci_cmd_पूर्णांकerrupt(host, pending);

			spin_unlock(&host->irq_lock);
		पूर्ण

		अगर (pending & SDMMC_INT_CD) अणु
			mci_ग_लिखोl(host, RINTSTS, SDMMC_INT_CD);
			dw_mci_handle_cd(host);
		पूर्ण

		अगर (pending & SDMMC_INT_SDIO(slot->sdio_id)) अणु
			mci_ग_लिखोl(host, RINTSTS,
				   SDMMC_INT_SDIO(slot->sdio_id));
			__dw_mci_enable_sdio_irq(slot, 0);
			sdio_संकेत_irq(slot->mmc);
		पूर्ण

	पूर्ण

	अगर (host->use_dma != TRANS_MODE_IDMAC)
		वापस IRQ_HANDLED;

	/* Handle IDMA पूर्णांकerrupts */
	अगर (host->dma_64bit_address == 1) अणु
		pending = mci_पढ़ोl(host, IDSTS64);
		अगर (pending & (SDMMC_IDMAC_INT_TI | SDMMC_IDMAC_INT_RI)) अणु
			mci_ग_लिखोl(host, IDSTS64, SDMMC_IDMAC_INT_TI |
							SDMMC_IDMAC_INT_RI);
			mci_ग_लिखोl(host, IDSTS64, SDMMC_IDMAC_INT_NI);
			अगर (!test_bit(EVENT_DATA_ERROR, &host->pending_events))
				host->dma_ops->complete((व्योम *)host);
		पूर्ण
	पूर्ण अन्यथा अणु
		pending = mci_पढ़ोl(host, IDSTS);
		अगर (pending & (SDMMC_IDMAC_INT_TI | SDMMC_IDMAC_INT_RI)) अणु
			mci_ग_लिखोl(host, IDSTS, SDMMC_IDMAC_INT_TI |
							SDMMC_IDMAC_INT_RI);
			mci_ग_लिखोl(host, IDSTS, SDMMC_IDMAC_INT_NI);
			अगर (!test_bit(EVENT_DATA_ERROR, &host->pending_events))
				host->dma_ops->complete((व्योम *)host);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dw_mci_init_slot_caps(काष्ठा dw_mci_slot *slot)
अणु
	काष्ठा dw_mci *host = slot->host;
	स्थिर काष्ठा dw_mci_drv_data *drv_data = host->drv_data;
	काष्ठा mmc_host *mmc = slot->mmc;
	पूर्णांक ctrl_id;

	अगर (host->pdata->caps)
		mmc->caps = host->pdata->caps;

	अगर (host->pdata->pm_caps)
		mmc->pm_caps = host->pdata->pm_caps;

	अगर (host->dev->of_node) अणु
		ctrl_id = of_alias_get_id(host->dev->of_node, "mshc");
		अगर (ctrl_id < 0)
			ctrl_id = 0;
	पूर्ण अन्यथा अणु
		ctrl_id = to_platक्रमm_device(host->dev)->id;
	पूर्ण

	अगर (drv_data && drv_data->caps) अणु
		अगर (ctrl_id >= drv_data->num_caps) अणु
			dev_err(host->dev, "invalid controller id %d\n",
				ctrl_id);
			वापस -EINVAL;
		पूर्ण
		mmc->caps |= drv_data->caps[ctrl_id];
	पूर्ण

	अगर (host->pdata->caps2)
		mmc->caps2 = host->pdata->caps2;

	mmc->f_min = DW_MCI_FREQ_MIN;
	अगर (!mmc->f_max)
		mmc->f_max = DW_MCI_FREQ_MAX;

	/* Process SDIO IRQs through the sdio_irq_work. */
	अगर (mmc->caps & MMC_CAP_SDIO_IRQ)
		mmc->caps2 |= MMC_CAP2_SDIO_IRQ_NOTHREAD;

	वापस 0;
पूर्ण

अटल पूर्णांक dw_mci_init_slot(काष्ठा dw_mci *host)
अणु
	काष्ठा mmc_host *mmc;
	काष्ठा dw_mci_slot *slot;
	पूर्णांक ret;

	mmc = mmc_alloc_host(माप(काष्ठा dw_mci_slot), host->dev);
	अगर (!mmc)
		वापस -ENOMEM;

	slot = mmc_priv(mmc);
	slot->id = 0;
	slot->sdio_id = host->sdio_id0 + slot->id;
	slot->mmc = mmc;
	slot->host = host;
	host->slot = slot;

	mmc->ops = &dw_mci_ops;

	/*अगर there are बाह्यal regulators, get them*/
	ret = mmc_regulator_get_supply(mmc);
	अगर (ret)
		जाओ err_host_allocated;

	अगर (!mmc->ocr_avail)
		mmc->ocr_avail = MMC_VDD_32_33 | MMC_VDD_33_34;

	ret = mmc_of_parse(mmc);
	अगर (ret)
		जाओ err_host_allocated;

	ret = dw_mci_init_slot_caps(slot);
	अगर (ret)
		जाओ err_host_allocated;

	/* Useful शेषs अगर platक्रमm data is unset. */
	अगर (host->use_dma == TRANS_MODE_IDMAC) अणु
		mmc->max_segs = host->ring_size;
		mmc->max_blk_size = 65535;
		mmc->max_seg_size = 0x1000;
		mmc->max_req_size = mmc->max_seg_size * host->ring_size;
		mmc->max_blk_count = mmc->max_req_size / 512;
	पूर्ण अन्यथा अगर (host->use_dma == TRANS_MODE_EDMAC) अणु
		mmc->max_segs = 64;
		mmc->max_blk_size = 65535;
		mmc->max_blk_count = 65535;
		mmc->max_req_size =
				mmc->max_blk_size * mmc->max_blk_count;
		mmc->max_seg_size = mmc->max_req_size;
	पूर्ण अन्यथा अणु
		/* TRANS_MODE_PIO */
		mmc->max_segs = 64;
		mmc->max_blk_size = 65535; /* BLKSIZ is 16 bits */
		mmc->max_blk_count = 512;
		mmc->max_req_size = mmc->max_blk_size *
				    mmc->max_blk_count;
		mmc->max_seg_size = mmc->max_req_size;
	पूर्ण

	dw_mci_get_cd(mmc);

	ret = mmc_add_host(mmc);
	अगर (ret)
		जाओ err_host_allocated;

#अगर defined(CONFIG_DEBUG_FS)
	dw_mci_init_debugfs(slot);
#पूर्ण_अगर

	वापस 0;

err_host_allocated:
	mmc_मुक्त_host(mmc);
	वापस ret;
पूर्ण

अटल व्योम dw_mci_cleanup_slot(काष्ठा dw_mci_slot *slot)
अणु
	/* Debugfs stuff is cleaned up by mmc core */
	mmc_हटाओ_host(slot->mmc);
	slot->host->slot = शून्य;
	mmc_मुक्त_host(slot->mmc);
पूर्ण

अटल व्योम dw_mci_init_dma(काष्ठा dw_mci *host)
अणु
	पूर्णांक addr_config;
	काष्ठा device *dev = host->dev;

	/*
	* Check tansfer mode from HCON[17:16]
	* Clear the ambiguous description of dw_mmc databook:
	* 2b'00: No DMA Interface -> Actually means using Internal DMA block
	* 2b'01: DesignWare DMA Interface -> Synopsys DW-DMA block
	* 2b'10: Generic DMA Interface -> non-Synopsys generic DMA block
	* 2b'11: Non DW DMA Interface -> pio only
	* Compared to DesignWare DMA Interface, Generic DMA Interface has a
	* simpler request/acknowledge handshake mechanism and both of them
	* are regarded as बाह्यal dma master क्रम dw_mmc.
	*/
	host->use_dma = SDMMC_GET_TRANS_MODE(mci_पढ़ोl(host, HCON));
	अगर (host->use_dma == DMA_INTERFACE_IDMA) अणु
		host->use_dma = TRANS_MODE_IDMAC;
	पूर्ण अन्यथा अगर (host->use_dma == DMA_INTERFACE_DWDMA ||
		   host->use_dma == DMA_INTERFACE_GDMA) अणु
		host->use_dma = TRANS_MODE_EDMAC;
	पूर्ण अन्यथा अणु
		जाओ no_dma;
	पूर्ण

	/* Determine which DMA पूर्णांकerface to use */
	अगर (host->use_dma == TRANS_MODE_IDMAC) अणु
		/*
		* Check ADDR_CONFIG bit in HCON to find
		* IDMAC address bus width
		*/
		addr_config = SDMMC_GET_ADDR_CONFIG(mci_पढ़ोl(host, HCON));

		अगर (addr_config == 1) अणु
			/* host supports IDMAC in 64-bit address mode */
			host->dma_64bit_address = 1;
			dev_info(host->dev,
				 "IDMAC supports 64-bit address mode.\n");
			अगर (!dma_set_mask(host->dev, DMA_BIT_MASK(64)))
				dma_set_coherent_mask(host->dev,
						      DMA_BIT_MASK(64));
		पूर्ण अन्यथा अणु
			/* host supports IDMAC in 32-bit address mode */
			host->dma_64bit_address = 0;
			dev_info(host->dev,
				 "IDMAC supports 32-bit address mode.\n");
		पूर्ण

		/* Alloc memory क्रम sg translation */
		host->sg_cpu = dmam_alloc_coherent(host->dev,
						   DESC_RING_BUF_SZ,
						   &host->sg_dma, GFP_KERNEL);
		अगर (!host->sg_cpu) अणु
			dev_err(host->dev,
				"%s: could not alloc DMA memory\n",
				__func__);
			जाओ no_dma;
		पूर्ण

		host->dma_ops = &dw_mci_idmac_ops;
		dev_info(host->dev, "Using internal DMA controller.\n");
	पूर्ण अन्यथा अणु
		/* TRANS_MODE_EDMAC: check dma bindings again */
		अगर ((device_property_पढ़ो_string_array(dev, "dma-names",
						       शून्य, 0) < 0) ||
		    !device_property_present(dev, "dmas")) अणु
			जाओ no_dma;
		पूर्ण
		host->dma_ops = &dw_mci_edmac_ops;
		dev_info(host->dev, "Using external DMA controller.\n");
	पूर्ण

	अगर (host->dma_ops->init && host->dma_ops->start &&
	    host->dma_ops->stop && host->dma_ops->cleanup) अणु
		अगर (host->dma_ops->init(host)) अणु
			dev_err(host->dev, "%s: Unable to initialize DMA Controller.\n",
				__func__);
			जाओ no_dma;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(host->dev, "DMA initialization not found.\n");
		जाओ no_dma;
	पूर्ण

	वापस;

no_dma:
	dev_info(host->dev, "Using PIO mode.\n");
	host->use_dma = TRANS_MODE_PIO;
पूर्ण

अटल व्योम dw_mci_cmd11_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा dw_mci *host = from_समयr(host, t, cmd11_समयr);

	अगर (host->state != STATE_SENDING_CMD11) अणु
		dev_warn(host->dev, "Unexpected CMD11 timeout\n");
		वापस;
	पूर्ण

	host->cmd_status = SDMMC_INT_RTO;
	set_bit(EVENT_CMD_COMPLETE, &host->pending_events);
	tasklet_schedule(&host->tasklet);
पूर्ण

अटल व्योम dw_mci_cto_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा dw_mci *host = from_समयr(host, t, cto_समयr);
	अचिन्हित दीर्घ irqflags;
	u32 pending;

	spin_lock_irqsave(&host->irq_lock, irqflags);

	/*
	 * If somehow we have very bad पूर्णांकerrupt latency it's remotely possible
	 * that the समयr could fire जबतक the पूर्णांकerrupt is still pending or
	 * जबतक the पूर्णांकerrupt is midway through running.  Let's be paranoid
	 * and detect those two हालs.  Note that this is paranoia is somewhat
	 * justअगरied because in this function we करोn't actually cancel the
	 * pending command in the controller--we just assume it will never come.
	 */
	pending = mci_पढ़ोl(host, MINTSTS); /* पढ़ो-only mask reg */
	अगर (pending & (DW_MCI_CMD_ERROR_FLAGS | SDMMC_INT_CMD_DONE)) अणु
		/* The पूर्णांकerrupt should fire; no need to act but we can warn */
		dev_warn(host->dev, "Unexpected interrupt latency\n");
		जाओ निकास;
	पूर्ण
	अगर (test_bit(EVENT_CMD_COMPLETE, &host->pending_events)) अणु
		/* Presumably पूर्णांकerrupt handler couldn't delete the समयr */
		dev_warn(host->dev, "CTO timeout when already completed\n");
		जाओ निकास;
	पूर्ण

	/*
	 * Continued paranoia to make sure we're in the state we expect.
	 * This paranoia isn't really justअगरied but it seems good to be safe.
	 */
	चयन (host->state) अणु
	हाल STATE_SENDING_CMD11:
	हाल STATE_SENDING_CMD:
	हाल STATE_SENDING_STOP:
		/*
		 * If CMD_DONE पूर्णांकerrupt करोes NOT come in sending command
		 * state, we should notअगरy the driver to terminate current
		 * transfer and report a command समयout to the core.
		 */
		host->cmd_status = SDMMC_INT_RTO;
		set_bit(EVENT_CMD_COMPLETE, &host->pending_events);
		tasklet_schedule(&host->tasklet);
		अवरोध;
	शेष:
		dev_warn(host->dev, "Unexpected command timeout, state %d\n",
			 host->state);
		अवरोध;
	पूर्ण

निकास:
	spin_unlock_irqrestore(&host->irq_lock, irqflags);
पूर्ण

अटल व्योम dw_mci_dto_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा dw_mci *host = from_समयr(host, t, dto_समयr);
	अचिन्हित दीर्घ irqflags;
	u32 pending;

	spin_lock_irqsave(&host->irq_lock, irqflags);

	/*
	 * The DTO समयr is much दीर्घer than the CTO समयr, so it's even less
	 * likely that we'll these हालs, but it pays to be paranoid.
	 */
	pending = mci_पढ़ोl(host, MINTSTS); /* पढ़ो-only mask reg */
	अगर (pending & SDMMC_INT_DATA_OVER) अणु
		/* The पूर्णांकerrupt should fire; no need to act but we can warn */
		dev_warn(host->dev, "Unexpected data interrupt latency\n");
		जाओ निकास;
	पूर्ण
	अगर (test_bit(EVENT_DATA_COMPLETE, &host->pending_events)) अणु
		/* Presumably पूर्णांकerrupt handler couldn't delete the समयr */
		dev_warn(host->dev, "DTO timeout when already completed\n");
		जाओ निकास;
	पूर्ण

	/*
	 * Continued paranoia to make sure we're in the state we expect.
	 * This paranoia isn't really justअगरied but it seems good to be safe.
	 */
	चयन (host->state) अणु
	हाल STATE_SENDING_DATA:
	हाल STATE_DATA_BUSY:
		/*
		 * If DTO पूर्णांकerrupt करोes NOT come in sending data state,
		 * we should notअगरy the driver to terminate current transfer
		 * and report a data समयout to the core.
		 */
		host->data_status = SDMMC_INT_DRTO;
		set_bit(EVENT_DATA_ERROR, &host->pending_events);
		set_bit(EVENT_DATA_COMPLETE, &host->pending_events);
		tasklet_schedule(&host->tasklet);
		अवरोध;
	शेष:
		dev_warn(host->dev, "Unexpected data timeout, state %d\n",
			 host->state);
		अवरोध;
	पूर्ण

निकास:
	spin_unlock_irqrestore(&host->irq_lock, irqflags);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल काष्ठा dw_mci_board *dw_mci_parse_dt(काष्ठा dw_mci *host)
अणु
	काष्ठा dw_mci_board *pdata;
	काष्ठा device *dev = host->dev;
	स्थिर काष्ठा dw_mci_drv_data *drv_data = host->drv_data;
	पूर्णांक ret;
	u32 घड़ी_frequency;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	/* find reset controller when exist */
	pdata->rstc = devm_reset_control_get_optional_exclusive(dev, "reset");
	अगर (IS_ERR(pdata->rstc))
		वापस ERR_CAST(pdata->rstc);

	अगर (device_property_पढ़ो_u32(dev, "fifo-depth", &pdata->fअगरo_depth))
		dev_info(dev,
			 "fifo-depth property not found, using value of FIFOTH register as default\n");

	device_property_पढ़ो_u32(dev, "card-detect-delay",
				 &pdata->detect_delay_ms);

	device_property_पढ़ो_u32(dev, "data-addr", &host->data_addr_override);

	अगर (device_property_present(dev, "fifo-watermark-aligned"))
		host->wm_aligned = true;

	अगर (!device_property_पढ़ो_u32(dev, "clock-frequency", &घड़ी_frequency))
		pdata->bus_hz = घड़ी_frequency;

	अगर (drv_data && drv_data->parse_dt) अणु
		ret = drv_data->parse_dt(host);
		अगर (ret)
			वापस ERR_PTR(ret);
	पूर्ण

	वापस pdata;
पूर्ण

#अन्यथा /* CONFIG_OF */
अटल काष्ठा dw_mci_board *dw_mci_parse_dt(काष्ठा dw_mci *host)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

अटल व्योम dw_mci_enable_cd(काष्ठा dw_mci *host)
अणु
	अचिन्हित दीर्घ irqflags;
	u32 temp;

	/*
	 * No need क्रम CD अगर all slots have a non-error GPIO
	 * as well as broken card detection is found.
	 */
	अगर (host->slot->mmc->caps & MMC_CAP_NEEDS_POLL)
		वापस;

	अगर (mmc_gpio_get_cd(host->slot->mmc) < 0) अणु
		spin_lock_irqsave(&host->irq_lock, irqflags);
		temp = mci_पढ़ोl(host, INTMASK);
		temp  |= SDMMC_INT_CD;
		mci_ग_लिखोl(host, INTMASK, temp);
		spin_unlock_irqrestore(&host->irq_lock, irqflags);
	पूर्ण
पूर्ण

पूर्णांक dw_mci_probe(काष्ठा dw_mci *host)
अणु
	स्थिर काष्ठा dw_mci_drv_data *drv_data = host->drv_data;
	पूर्णांक width, i, ret = 0;
	u32 fअगरo_size;

	अगर (!host->pdata) अणु
		host->pdata = dw_mci_parse_dt(host);
		अगर (IS_ERR(host->pdata))
			वापस dev_err_probe(host->dev, PTR_ERR(host->pdata),
					     "platform data not available\n");
	पूर्ण

	host->biu_clk = devm_clk_get(host->dev, "biu");
	अगर (IS_ERR(host->biu_clk)) अणु
		dev_dbg(host->dev, "biu clock not available\n");
	पूर्ण अन्यथा अणु
		ret = clk_prepare_enable(host->biu_clk);
		अगर (ret) अणु
			dev_err(host->dev, "failed to enable biu clock\n");
			वापस ret;
		पूर्ण
	पूर्ण

	host->ciu_clk = devm_clk_get(host->dev, "ciu");
	अगर (IS_ERR(host->ciu_clk)) अणु
		dev_dbg(host->dev, "ciu clock not available\n");
		host->bus_hz = host->pdata->bus_hz;
	पूर्ण अन्यथा अणु
		ret = clk_prepare_enable(host->ciu_clk);
		अगर (ret) अणु
			dev_err(host->dev, "failed to enable ciu clock\n");
			जाओ err_clk_biu;
		पूर्ण

		अगर (host->pdata->bus_hz) अणु
			ret = clk_set_rate(host->ciu_clk, host->pdata->bus_hz);
			अगर (ret)
				dev_warn(host->dev,
					 "Unable to set bus rate to %uHz\n",
					 host->pdata->bus_hz);
		पूर्ण
		host->bus_hz = clk_get_rate(host->ciu_clk);
	पूर्ण

	अगर (!host->bus_hz) अणु
		dev_err(host->dev,
			"Platform data must supply bus speed\n");
		ret = -ENODEV;
		जाओ err_clk_ciu;
	पूर्ण

	अगर (host->pdata->rstc) अणु
		reset_control_निश्चित(host->pdata->rstc);
		usleep_range(10, 50);
		reset_control_deनिश्चित(host->pdata->rstc);
	पूर्ण

	अगर (drv_data && drv_data->init) अणु
		ret = drv_data->init(host);
		अगर (ret) अणु
			dev_err(host->dev,
				"implementation specific init failed\n");
			जाओ err_clk_ciu;
		पूर्ण
	पूर्ण

	समयr_setup(&host->cmd11_समयr, dw_mci_cmd11_समयr, 0);
	समयr_setup(&host->cto_समयr, dw_mci_cto_समयr, 0);
	समयr_setup(&host->dto_समयr, dw_mci_dto_समयr, 0);

	spin_lock_init(&host->lock);
	spin_lock_init(&host->irq_lock);
	INIT_LIST_HEAD(&host->queue);

	/*
	 * Get the host data width - this assumes that HCON has been set with
	 * the correct values.
	 */
	i = SDMMC_GET_HDATA_WIDTH(mci_पढ़ोl(host, HCON));
	अगर (!i) अणु
		host->push_data = dw_mci_push_data16;
		host->pull_data = dw_mci_pull_data16;
		width = 16;
		host->data_shअगरt = 1;
	पूर्ण अन्यथा अगर (i == 2) अणु
		host->push_data = dw_mci_push_data64;
		host->pull_data = dw_mci_pull_data64;
		width = 64;
		host->data_shअगरt = 3;
	पूर्ण अन्यथा अणु
		/* Check क्रम a reserved value, and warn अगर it is */
		WARN((i != 1),
		     "HCON reports a reserved host data width!\n"
		     "Defaulting to 32-bit access.\n");
		host->push_data = dw_mci_push_data32;
		host->pull_data = dw_mci_pull_data32;
		width = 32;
		host->data_shअगरt = 2;
	पूर्ण

	/* Reset all blocks */
	अगर (!dw_mci_ctrl_reset(host, SDMMC_CTRL_ALL_RESET_FLAGS)) अणु
		ret = -ENODEV;
		जाओ err_clk_ciu;
	पूर्ण

	host->dma_ops = host->pdata->dma_ops;
	dw_mci_init_dma(host);

	/* Clear the पूर्णांकerrupts क्रम the host controller */
	mci_ग_लिखोl(host, RINTSTS, 0xFFFFFFFF);
	mci_ग_लिखोl(host, INTMASK, 0); /* disable all mmc पूर्णांकerrupt first */

	/* Put in max समयout */
	mci_ग_लिखोl(host, TMOUT, 0xFFFFFFFF);

	/*
	 * FIFO threshold settings  RxMark  = fअगरo_size / 2 - 1,
	 *                          Tx Mark = fअगरo_size / 2 DMA Size = 8
	 */
	अगर (!host->pdata->fअगरo_depth) अणु
		/*
		 * Power-on value of RX_WMark is FIFO_DEPTH-1, but this may
		 * have been overwritten by the bootloader, just like we're
		 * about to करो, so अगर you know the value क्रम your hardware, you
		 * should put it in the platक्रमm data.
		 */
		fअगरo_size = mci_पढ़ोl(host, FIFOTH);
		fअगरo_size = 1 + ((fअगरo_size >> 16) & 0xfff);
	पूर्ण अन्यथा अणु
		fअगरo_size = host->pdata->fअगरo_depth;
	पूर्ण
	host->fअगरo_depth = fअगरo_size;
	host->fअगरoth_val =
		SDMMC_SET_FIFOTH(0x2, fअगरo_size / 2 - 1, fअगरo_size / 2);
	mci_ग_लिखोl(host, FIFOTH, host->fअगरoth_val);

	/* disable घड़ी to CIU */
	mci_ग_लिखोl(host, CLKENA, 0);
	mci_ग_लिखोl(host, CLKSRC, 0);

	/*
	 * In 2.40a spec, Data offset is changed.
	 * Need to check the version-id and set data-offset क्रम DATA रेजिस्टर.
	 */
	host->verid = SDMMC_GET_VERID(mci_पढ़ोl(host, VERID));
	dev_info(host->dev, "Version ID is %04x\n", host->verid);

	अगर (host->data_addr_override)
		host->fअगरo_reg = host->regs + host->data_addr_override;
	अन्यथा अगर (host->verid < DW_MMC_240A)
		host->fअगरo_reg = host->regs + DATA_OFFSET;
	अन्यथा
		host->fअगरo_reg = host->regs + DATA_240A_OFFSET;

	tasklet_setup(&host->tasklet, dw_mci_tasklet_func);
	ret = devm_request_irq(host->dev, host->irq, dw_mci_पूर्णांकerrupt,
			       host->irq_flags, "dw-mci", host);
	अगर (ret)
		जाओ err_dmaunmap;

	/*
	 * Enable पूर्णांकerrupts क्रम command करोne, data over, data empty,
	 * receive पढ़ोy and error such as transmit, receive समयout, crc error
	 */
	mci_ग_लिखोl(host, INTMASK, SDMMC_INT_CMD_DONE | SDMMC_INT_DATA_OVER |
		   SDMMC_INT_TXDR | SDMMC_INT_RXDR |
		   DW_MCI_ERROR_FLAGS);
	/* Enable mci पूर्णांकerrupt */
	mci_ग_लिखोl(host, CTRL, SDMMC_CTRL_INT_ENABLE);

	dev_info(host->dev,
		 "DW MMC controller at irq %d,%d bit host data width,%u deep fifo\n",
		 host->irq, width, fअगरo_size);

	/* We need at least one slot to succeed */
	ret = dw_mci_init_slot(host);
	अगर (ret) अणु
		dev_dbg(host->dev, "slot %d init failed\n", i);
		जाओ err_dmaunmap;
	पूर्ण

	/* Now that slots are all setup, we can enable card detect */
	dw_mci_enable_cd(host);

	वापस 0;

err_dmaunmap:
	अगर (host->use_dma && host->dma_ops->निकास)
		host->dma_ops->निकास(host);

	reset_control_निश्चित(host->pdata->rstc);

err_clk_ciu:
	clk_disable_unprepare(host->ciu_clk);

err_clk_biu:
	clk_disable_unprepare(host->biu_clk);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(dw_mci_probe);

व्योम dw_mci_हटाओ(काष्ठा dw_mci *host)
अणु
	dev_dbg(host->dev, "remove slot\n");
	अगर (host->slot)
		dw_mci_cleanup_slot(host->slot);

	mci_ग_लिखोl(host, RINTSTS, 0xFFFFFFFF);
	mci_ग_लिखोl(host, INTMASK, 0); /* disable all mmc पूर्णांकerrupt first */

	/* disable घड़ी to CIU */
	mci_ग_लिखोl(host, CLKENA, 0);
	mci_ग_लिखोl(host, CLKSRC, 0);

	अगर (host->use_dma && host->dma_ops->निकास)
		host->dma_ops->निकास(host);

	reset_control_निश्चित(host->pdata->rstc);

	clk_disable_unprepare(host->ciu_clk);
	clk_disable_unprepare(host->biu_clk);
पूर्ण
EXPORT_SYMBOL(dw_mci_हटाओ);



#अगर_घोषित CONFIG_PM
पूर्णांक dw_mci_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा dw_mci *host = dev_get_drvdata(dev);

	अगर (host->use_dma && host->dma_ops->निकास)
		host->dma_ops->निकास(host);

	clk_disable_unprepare(host->ciu_clk);

	अगर (host->slot &&
	    (mmc_can_gpio_cd(host->slot->mmc) ||
	     !mmc_card_is_removable(host->slot->mmc)))
		clk_disable_unprepare(host->biu_clk);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(dw_mci_runसमय_suspend);

पूर्णांक dw_mci_runसमय_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret = 0;
	काष्ठा dw_mci *host = dev_get_drvdata(dev);

	अगर (host->slot &&
	    (mmc_can_gpio_cd(host->slot->mmc) ||
	     !mmc_card_is_removable(host->slot->mmc))) अणु
		ret = clk_prepare_enable(host->biu_clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = clk_prepare_enable(host->ciu_clk);
	अगर (ret)
		जाओ err;

	अगर (!dw_mci_ctrl_reset(host, SDMMC_CTRL_ALL_RESET_FLAGS)) अणु
		clk_disable_unprepare(host->ciu_clk);
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	अगर (host->use_dma && host->dma_ops->init)
		host->dma_ops->init(host);

	/*
	 * Restore the initial value at FIFOTH रेजिस्टर
	 * And Invalidate the prev_blksz with zero
	 */
	mci_ग_लिखोl(host, FIFOTH, host->fअगरoth_val);
	host->prev_blksz = 0;

	/* Put in max समयout */
	mci_ग_लिखोl(host, TMOUT, 0xFFFFFFFF);

	mci_ग_लिखोl(host, RINTSTS, 0xFFFFFFFF);
	mci_ग_लिखोl(host, INTMASK, SDMMC_INT_CMD_DONE | SDMMC_INT_DATA_OVER |
		   SDMMC_INT_TXDR | SDMMC_INT_RXDR |
		   DW_MCI_ERROR_FLAGS);
	mci_ग_लिखोl(host, CTRL, SDMMC_CTRL_INT_ENABLE);


	अगर (host->slot->mmc->pm_flags & MMC_PM_KEEP_POWER)
		dw_mci_set_ios(host->slot->mmc, &host->slot->mmc->ios);

	/* Force setup bus to guarantee available घड़ी output */
	dw_mci_setup_bus(host->slot, true);

	/* Re-enable SDIO पूर्णांकerrupts. */
	अगर (sdio_irq_claimed(host->slot->mmc))
		__dw_mci_enable_sdio_irq(host->slot, 1);

	/* Now that slots are all setup, we can enable card detect */
	dw_mci_enable_cd(host);

	वापस 0;

err:
	अगर (host->slot &&
	    (mmc_can_gpio_cd(host->slot->mmc) ||
	     !mmc_card_is_removable(host->slot->mmc)))
		clk_disable_unprepare(host->biu_clk);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(dw_mci_runसमय_resume);
#पूर्ण_अगर /* CONFIG_PM */

अटल पूर्णांक __init dw_mci_init(व्योम)
अणु
	pr_info("Synopsys Designware Multimedia Card Interface Driver\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास dw_mci_निकास(व्योम)
अणु
पूर्ण

module_init(dw_mci_init);
module_निकास(dw_mci_निकास);

MODULE_DESCRIPTION("DW Multimedia Card Interface driver");
MODULE_AUTHOR("NXP Semiconductor VietNam");
MODULE_AUTHOR("Imagination Technologies Ltd");
MODULE_LICENSE("GPL v2");
