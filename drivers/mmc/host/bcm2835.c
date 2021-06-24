<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * bcm2835 sdhost driver.
 *
 * The 2835 has two SD controllers: The Arasan sdhci controller
 * (supported by the iproc driver) and a custom sdhost controller
 * (supported by this driver).
 *
 * The sdhci controller supports both sdcard and sdio.  The sdhost
 * controller supports the sdcard only, but has better perक्रमmance.
 * Also note that the rpi3 has sdio wअगरi, so driving the sdcard with
 * the sdhost controller allows to use the sdhci controller क्रम wअगरi
 * support.
 *
 * The configuration is करोne by devicetree via pin muxing.  Both
 * SD controller are available on the same pins (2 pin groups = pin 22
 * to 27 + pin 48 to 53).  So it's possible to use both SD controllers
 * at the same समय with dअगरferent pin groups.
 *
 * Author:      Phil Elwell <phil@raspberrypi.org>
 *              Copyright (C) 2015-2016 Raspberry Pi (Trading) Ltd.
 *
 * Based on
 *  mmc-bcm2835.c by Gellert Weisz
 * which is, in turn, based on
 *  sdhci-bcm2708.c by Broadcom
 *  sdhci-bcm2835.c by Stephen Warren and Oleksandr Tymoshenko
 *  sdhci.c and sdhci-pci.c by Pierre Ossman
 */
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/समय.स>
#समावेश <linux/workqueue.h>

#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/sd.h>

#घोषणा SDCMD  0x00 /* Command to SD card              - 16 R/W */
#घोषणा SDARG  0x04 /* Argument to SD card             - 32 R/W */
#घोषणा SDTOUT 0x08 /* Start value क्रम समयout counter - 32 R/W */
#घोषणा SDCDIV 0x0c /* Start value क्रम घड़ी भागider   - 11 R/W */
#घोषणा SDRSP0 0x10 /* SD card response (31:0)         - 32 R   */
#घोषणा SDRSP1 0x14 /* SD card response (63:32)        - 32 R   */
#घोषणा SDRSP2 0x18 /* SD card response (95:64)        - 32 R   */
#घोषणा SDRSP3 0x1c /* SD card response (127:96)       - 32 R   */
#घोषणा SDHSTS 0x20 /* SD host status                  - 11 R/W */
#घोषणा SDVDD  0x30 /* SD card घातer control           -  1 R/W */
#घोषणा SDEDM  0x34 /* Emergency Debug Mode            - 13 R/W */
#घोषणा SDHCFG 0x38 /* Host configuration              -  2 R/W */
#घोषणा SDHBCT 0x3c /* Host byte count (debug)         - 32 R/W */
#घोषणा SDDATA 0x40 /* Data to/from SD card            - 32 R/W */
#घोषणा SDHBLC 0x50 /* Host block count (SDIO/SDHC)    -  9 R/W */

#घोषणा SDCMD_NEW_FLAG			0x8000
#घोषणा SDCMD_FAIL_FLAG			0x4000
#घोषणा SDCMD_BUSYWAIT			0x800
#घोषणा SDCMD_NO_RESPONSE		0x400
#घोषणा SDCMD_LONG_RESPONSE		0x200
#घोषणा SDCMD_WRITE_CMD			0x80
#घोषणा SDCMD_READ_CMD			0x40
#घोषणा SDCMD_CMD_MASK			0x3f

#घोषणा SDCDIV_MAX_CDIV			0x7ff

#घोषणा SDHSTS_BUSY_IRPT		0x400
#घोषणा SDHSTS_BLOCK_IRPT		0x200
#घोषणा SDHSTS_SDIO_IRPT		0x100
#घोषणा SDHSTS_REW_TIME_OUT		0x80
#घोषणा SDHSTS_CMD_TIME_OUT		0x40
#घोषणा SDHSTS_CRC16_ERROR		0x20
#घोषणा SDHSTS_CRC7_ERROR		0x10
#घोषणा SDHSTS_FIFO_ERROR		0x08
/* Reserved */
/* Reserved */
#घोषणा SDHSTS_DATA_FLAG		0x01

#घोषणा SDHSTS_TRANSFER_ERROR_MASK	(SDHSTS_CRC7_ERROR | \
					 SDHSTS_CRC16_ERROR | \
					 SDHSTS_REW_TIME_OUT | \
					 SDHSTS_FIFO_ERROR)

#घोषणा SDHSTS_ERROR_MASK		(SDHSTS_CMD_TIME_OUT | \
					 SDHSTS_TRANSFER_ERROR_MASK)

#घोषणा SDHCFG_BUSY_IRPT_EN	BIT(10)
#घोषणा SDHCFG_BLOCK_IRPT_EN	BIT(8)
#घोषणा SDHCFG_SDIO_IRPT_EN	BIT(5)
#घोषणा SDHCFG_DATA_IRPT_EN	BIT(4)
#घोषणा SDHCFG_SLOW_CARD	BIT(3)
#घोषणा SDHCFG_WIDE_EXT_BUS	BIT(2)
#घोषणा SDHCFG_WIDE_INT_BUS	BIT(1)
#घोषणा SDHCFG_REL_CMD_LINE	BIT(0)

#घोषणा SDVDD_POWER_OFF		0
#घोषणा SDVDD_POWER_ON		1

#घोषणा SDEDM_FORCE_DATA_MODE	BIT(19)
#घोषणा SDEDM_CLOCK_PULSE	BIT(20)
#घोषणा SDEDM_BYPASS		BIT(21)

#घोषणा SDEDM_WRITE_THRESHOLD_SHIFT	9
#घोषणा SDEDM_READ_THRESHOLD_SHIFT	14
#घोषणा SDEDM_THRESHOLD_MASK		0x1f

#घोषणा SDEDM_FSM_MASK		0xf
#घोषणा SDEDM_FSM_IDENTMODE	0x0
#घोषणा SDEDM_FSM_DATAMODE	0x1
#घोषणा SDEDM_FSM_READDATA	0x2
#घोषणा SDEDM_FSM_WRITEDATA	0x3
#घोषणा SDEDM_FSM_READWAIT	0x4
#घोषणा SDEDM_FSM_READCRC	0x5
#घोषणा SDEDM_FSM_WRITECRC	0x6
#घोषणा SDEDM_FSM_WRITEWAIT1	0x7
#घोषणा SDEDM_FSM_POWERDOWN	0x8
#घोषणा SDEDM_FSM_POWERUP	0x9
#घोषणा SDEDM_FSM_WRITESTART1	0xa
#घोषणा SDEDM_FSM_WRITESTART2	0xb
#घोषणा SDEDM_FSM_GENPULSES	0xc
#घोषणा SDEDM_FSM_WRITEWAIT2	0xd
#घोषणा SDEDM_FSM_STARTPOWDOWN	0xf

#घोषणा SDDATA_FIFO_WORDS	16

#घोषणा FIFO_READ_THRESHOLD	4
#घोषणा FIFO_WRITE_THRESHOLD	4
#घोषणा SDDATA_FIFO_PIO_BURST	8

#घोषणा PIO_THRESHOLD	1  /* Maximum block count क्रम PIO (0 = always DMA) */

काष्ठा bcm2835_host अणु
	spinlock_t		lock;
	काष्ठा mutex		mutex;

	व्योम __iomem		*ioaddr;
	u32			phys_addr;

	काष्ठा platक्रमm_device	*pdev;

	पूर्णांक			घड़ी;		/* Current घड़ी speed */
	अचिन्हित पूर्णांक		max_clk;	/* Max possible freq */
	काष्ठा work_काष्ठा	dma_work;
	काष्ठा delayed_work	समयout_work;	/* Timer क्रम समयouts */
	काष्ठा sg_mapping_iter	sg_miter;	/* SG state क्रम PIO */
	अचिन्हित पूर्णांक		blocks;		/* reमुख्यing PIO blocks */
	पूर्णांक			irq;		/* Device IRQ */

	u32			ns_per_fअगरo_word;

	/* cached रेजिस्टरs */
	u32			hcfg;
	u32			cभाग;

	काष्ठा mmc_request	*mrq;		/* Current request */
	काष्ठा mmc_command	*cmd;		/* Current command */
	काष्ठा mmc_data		*data;		/* Current data request */
	bool			data_complete:1;/* Data finished beक्रमe cmd */
	bool			use_busy:1;	/* Wait क्रम busy पूर्णांकerrupt */
	bool			use_sbc:1;	/* Send CMD23 */

	/* क्रम thपढ़ोed irq handler */
	bool			irq_block;
	bool			irq_busy;
	bool			irq_data;

	/* DMA part */
	काष्ठा dma_chan		*dma_chan_rxtx;
	काष्ठा dma_chan		*dma_chan;
	काष्ठा dma_slave_config dma_cfg_rx;
	काष्ठा dma_slave_config dma_cfg_tx;
	काष्ठा dma_async_tx_descriptor	*dma_desc;
	u32			dma_dir;
	u32			drain_words;
	काष्ठा page		*drain_page;
	u32			drain_offset;
	bool			use_dma;
पूर्ण;

अटल व्योम bcm2835_dumpcmd(काष्ठा bcm2835_host *host, काष्ठा mmc_command *cmd,
			    स्थिर अक्षर *label)
अणु
	काष्ठा device *dev = &host->pdev->dev;

	अगर (!cmd)
		वापस;

	dev_dbg(dev, "%c%s op %d arg 0x%x flags 0x%x - resp %08x %08x %08x %08x, err %d\n",
		(cmd == host->cmd) ? '>' : ' ',
		label, cmd->opcode, cmd->arg, cmd->flags,
		cmd->resp[0], cmd->resp[1], cmd->resp[2], cmd->resp[3],
		cmd->error);
पूर्ण

अटल व्योम bcm2835_dumpregs(काष्ठा bcm2835_host *host)
अणु
	काष्ठा mmc_request *mrq = host->mrq;
	काष्ठा device *dev = &host->pdev->dev;

	अगर (mrq) अणु
		bcm2835_dumpcmd(host, mrq->sbc, "sbc");
		bcm2835_dumpcmd(host, mrq->cmd, "cmd");
		अगर (mrq->data) अणु
			dev_dbg(dev, "data blocks %x blksz %x - err %d\n",
				mrq->data->blocks,
				mrq->data->blksz,
				mrq->data->error);
		पूर्ण
		bcm2835_dumpcmd(host, mrq->stop, "stop");
	पूर्ण

	dev_dbg(dev, "=========== REGISTER DUMP ===========\n");
	dev_dbg(dev, "SDCMD  0x%08x\n", पढ़ोl(host->ioaddr + SDCMD));
	dev_dbg(dev, "SDARG  0x%08x\n", पढ़ोl(host->ioaddr + SDARG));
	dev_dbg(dev, "SDTOUT 0x%08x\n", पढ़ोl(host->ioaddr + SDTOUT));
	dev_dbg(dev, "SDCDIV 0x%08x\n", पढ़ोl(host->ioaddr + SDCDIV));
	dev_dbg(dev, "SDRSP0 0x%08x\n", पढ़ोl(host->ioaddr + SDRSP0));
	dev_dbg(dev, "SDRSP1 0x%08x\n", पढ़ोl(host->ioaddr + SDRSP1));
	dev_dbg(dev, "SDRSP2 0x%08x\n", पढ़ोl(host->ioaddr + SDRSP2));
	dev_dbg(dev, "SDRSP3 0x%08x\n", पढ़ोl(host->ioaddr + SDRSP3));
	dev_dbg(dev, "SDHSTS 0x%08x\n", पढ़ोl(host->ioaddr + SDHSTS));
	dev_dbg(dev, "SDVDD  0x%08x\n", पढ़ोl(host->ioaddr + SDVDD));
	dev_dbg(dev, "SDEDM  0x%08x\n", पढ़ोl(host->ioaddr + SDEDM));
	dev_dbg(dev, "SDHCFG 0x%08x\n", पढ़ोl(host->ioaddr + SDHCFG));
	dev_dbg(dev, "SDHBCT 0x%08x\n", पढ़ोl(host->ioaddr + SDHBCT));
	dev_dbg(dev, "SDHBLC 0x%08x\n", पढ़ोl(host->ioaddr + SDHBLC));
	dev_dbg(dev, "===========================================\n");
पूर्ण

अटल व्योम bcm2835_reset_पूर्णांकernal(काष्ठा bcm2835_host *host)
अणु
	u32 temp;

	ग_लिखोl(SDVDD_POWER_OFF, host->ioaddr + SDVDD);
	ग_लिखोl(0, host->ioaddr + SDCMD);
	ग_लिखोl(0, host->ioaddr + SDARG);
	ग_लिखोl(0xf00000, host->ioaddr + SDTOUT);
	ग_लिखोl(0, host->ioaddr + SDCDIV);
	ग_लिखोl(0x7f8, host->ioaddr + SDHSTS); /* Write 1s to clear */
	ग_लिखोl(0, host->ioaddr + SDHCFG);
	ग_लिखोl(0, host->ioaddr + SDHBCT);
	ग_लिखोl(0, host->ioaddr + SDHBLC);

	/* Limit fअगरo usage due to silicon bug */
	temp = पढ़ोl(host->ioaddr + SDEDM);
	temp &= ~((SDEDM_THRESHOLD_MASK << SDEDM_READ_THRESHOLD_SHIFT) |
		  (SDEDM_THRESHOLD_MASK << SDEDM_WRITE_THRESHOLD_SHIFT));
	temp |= (FIFO_READ_THRESHOLD << SDEDM_READ_THRESHOLD_SHIFT) |
		(FIFO_WRITE_THRESHOLD << SDEDM_WRITE_THRESHOLD_SHIFT);
	ग_लिखोl(temp, host->ioaddr + SDEDM);
	msleep(20);
	ग_लिखोl(SDVDD_POWER_ON, host->ioaddr + SDVDD);
	msleep(20);
	host->घड़ी = 0;
	ग_लिखोl(host->hcfg, host->ioaddr + SDHCFG);
	ग_लिखोl(host->cभाग, host->ioaddr + SDCDIV);
पूर्ण

अटल व्योम bcm2835_reset(काष्ठा mmc_host *mmc)
अणु
	काष्ठा bcm2835_host *host = mmc_priv(mmc);

	अगर (host->dma_chan)
		dmaengine_terminate_sync(host->dma_chan);
	host->dma_chan = शून्य;
	bcm2835_reset_पूर्णांकernal(host);
पूर्ण

अटल व्योम bcm2835_finish_command(काष्ठा bcm2835_host *host);

अटल व्योम bcm2835_रुको_transfer_complete(काष्ठा bcm2835_host *host)
अणु
	पूर्णांक समयdअगरf;
	u32 alternate_idle;

	alternate_idle = (host->mrq->data->flags & MMC_DATA_READ) ?
		SDEDM_FSM_READWAIT : SDEDM_FSM_WRITESTART1;

	समयdअगरf = 0;

	जबतक (1) अणु
		u32 edm, fsm;

		edm = पढ़ोl(host->ioaddr + SDEDM);
		fsm = edm & SDEDM_FSM_MASK;

		अगर ((fsm == SDEDM_FSM_IDENTMODE) ||
		    (fsm == SDEDM_FSM_DATAMODE))
			अवरोध;
		अगर (fsm == alternate_idle) अणु
			ग_लिखोl(edm | SDEDM_FORCE_DATA_MODE,
			       host->ioaddr + SDEDM);
			अवरोध;
		पूर्ण

		समयdअगरf++;
		अगर (समयdअगरf == 100000) अणु
			dev_err(&host->pdev->dev,
				"wait_transfer_complete - still waiting after %d retries\n",
				समयdअगरf);
			bcm2835_dumpregs(host);
			host->mrq->data->error = -ETIMEDOUT;
			वापस;
		पूर्ण
		cpu_relax();
	पूर्ण
पूर्ण

अटल व्योम bcm2835_dma_complete(व्योम *param)
अणु
	काष्ठा bcm2835_host *host = param;

	schedule_work(&host->dma_work);
पूर्ण

अटल व्योम bcm2835_transfer_block_pio(काष्ठा bcm2835_host *host, bool is_पढ़ो)
अणु
	अचिन्हित दीर्घ flags;
	माप_प्रकार blksize;
	अचिन्हित दीर्घ रुको_max;

	blksize = host->data->blksz;

	रुको_max = jअगरfies + msecs_to_jअगरfies(500);

	local_irq_save(flags);

	जबतक (blksize) अणु
		पूर्णांक copy_words;
		u32 hsts = 0;
		माप_प्रकार len;
		u32 *buf;

		अगर (!sg_miter_next(&host->sg_miter)) अणु
			host->data->error = -EINVAL;
			अवरोध;
		पूर्ण

		len = min(host->sg_miter.length, blksize);
		अगर (len % 4) अणु
			host->data->error = -EINVAL;
			अवरोध;
		पूर्ण

		blksize -= len;
		host->sg_miter.consumed = len;

		buf = (u32 *)host->sg_miter.addr;

		copy_words = len / 4;

		जबतक (copy_words) अणु
			पूर्णांक burst_words, words;
			u32 edm;

			burst_words = min(SDDATA_FIFO_PIO_BURST, copy_words);
			edm = पढ़ोl(host->ioaddr + SDEDM);
			अगर (is_पढ़ो)
				words = ((edm >> 4) & 0x1f);
			अन्यथा
				words = SDDATA_FIFO_WORDS - ((edm >> 4) & 0x1f);

			अगर (words < burst_words) अणु
				पूर्णांक fsm_state = (edm & SDEDM_FSM_MASK);
				काष्ठा device *dev = &host->pdev->dev;

				अगर ((is_पढ़ो &&
				     (fsm_state != SDEDM_FSM_READDATA &&
				      fsm_state != SDEDM_FSM_READWAIT &&
				      fsm_state != SDEDM_FSM_READCRC)) ||
				    (!is_पढ़ो &&
				     (fsm_state != SDEDM_FSM_WRITEDATA &&
				      fsm_state != SDEDM_FSM_WRITESTART1 &&
				      fsm_state != SDEDM_FSM_WRITESTART2))) अणु
					hsts = पढ़ोl(host->ioaddr + SDHSTS);
					dev_err(dev, "fsm %x, hsts %08x\n",
						fsm_state, hsts);
					अगर (hsts & SDHSTS_ERROR_MASK)
						अवरोध;
				पूर्ण

				अगर (समय_after(jअगरfies, रुको_max)) अणु
					dev_err(dev, "PIO %s timeout - EDM %08x\n",
						is_पढ़ो ? "read" : "write",
						edm);
					hsts = SDHSTS_REW_TIME_OUT;
					अवरोध;
				पूर्ण
				ndelay((burst_words - words) *
				       host->ns_per_fअगरo_word);
				जारी;
			पूर्ण अन्यथा अगर (words > copy_words) अणु
				words = copy_words;
			पूर्ण

			copy_words -= words;

			जबतक (words) अणु
				अगर (is_पढ़ो)
					*(buf++) = पढ़ोl(host->ioaddr + SDDATA);
				अन्यथा
					ग_लिखोl(*(buf++), host->ioaddr + SDDATA);
				words--;
			पूर्ण
		पूर्ण

		अगर (hsts & SDHSTS_ERROR_MASK)
			अवरोध;
	पूर्ण

	sg_miter_stop(&host->sg_miter);

	local_irq_restore(flags);
पूर्ण

अटल व्योम bcm2835_transfer_pio(काष्ठा bcm2835_host *host)
अणु
	काष्ठा device *dev = &host->pdev->dev;
	u32 sdhsts;
	bool is_पढ़ो;

	is_पढ़ो = (host->data->flags & MMC_DATA_READ) != 0;
	bcm2835_transfer_block_pio(host, is_पढ़ो);

	sdhsts = पढ़ोl(host->ioaddr + SDHSTS);
	अगर (sdhsts & (SDHSTS_CRC16_ERROR |
		      SDHSTS_CRC7_ERROR |
		      SDHSTS_FIFO_ERROR)) अणु
		dev_err(dev, "%s transfer error - HSTS %08x\n",
			is_पढ़ो ? "read" : "write", sdhsts);
		host->data->error = -EILSEQ;
	पूर्ण अन्यथा अगर ((sdhsts & (SDHSTS_CMD_TIME_OUT |
			      SDHSTS_REW_TIME_OUT))) अणु
		dev_err(dev, "%s timeout error - HSTS %08x\n",
			is_पढ़ो ? "read" : "write", sdhsts);
		host->data->error = -ETIMEDOUT;
	पूर्ण
पूर्ण

अटल
व्योम bcm2835_prepare_dma(काष्ठा bcm2835_host *host, काष्ठा mmc_data *data)
अणु
	पूर्णांक sg_len, dir_data, dir_slave;
	काष्ठा dma_async_tx_descriptor *desc = शून्य;
	काष्ठा dma_chan *dma_chan;

	dma_chan = host->dma_chan_rxtx;
	अगर (data->flags & MMC_DATA_READ) अणु
		dir_data = DMA_FROM_DEVICE;
		dir_slave = DMA_DEV_TO_MEM;
	पूर्ण अन्यथा अणु
		dir_data = DMA_TO_DEVICE;
		dir_slave = DMA_MEM_TO_DEV;
	पूर्ण

	/* The block करोesn't manage the FIFO DREQs properly क्रम
	 * multi-block transfers, so करोn't attempt to DMA the final
	 * few words.  Unक्रमtunately this requires the final sg entry
	 * to be trimmed.  N.B. This code demands that the overspill
	 * is contained in a single sg entry.
	 */

	host->drain_words = 0;
	अगर ((data->blocks > 1) && (dir_data == DMA_FROM_DEVICE)) अणु
		काष्ठा scatterlist *sg;
		u32 len;
		पूर्णांक i;

		len = min((u32)(FIFO_READ_THRESHOLD - 1) * 4,
			  (u32)data->blocks * data->blksz);

		क्रम_each_sg(data->sg, sg, data->sg_len, i) अणु
			अगर (sg_is_last(sg)) अणु
				WARN_ON(sg->length < len);
				sg->length -= len;
				host->drain_page = sg_page(sg);
				host->drain_offset = sg->offset + sg->length;
			पूर्ण
		पूर्ण
		host->drain_words = len / 4;
	पूर्ण

	/* The parameters have alपढ़ोy been validated, so this will not fail */
	(व्योम)dmaengine_slave_config(dma_chan,
				     (dir_data == DMA_FROM_DEVICE) ?
				     &host->dma_cfg_rx :
				     &host->dma_cfg_tx);

	sg_len = dma_map_sg(dma_chan->device->dev, data->sg, data->sg_len,
			    dir_data);
	अगर (!sg_len)
		वापस;

	desc = dmaengine_prep_slave_sg(dma_chan, data->sg, sg_len, dir_slave,
				       DMA_PREP_INTERRUPT | DMA_CTRL_ACK);

	अगर (!desc) अणु
		dma_unmap_sg(dma_chan->device->dev, data->sg, sg_len, dir_data);
		वापस;
	पूर्ण

	desc->callback = bcm2835_dma_complete;
	desc->callback_param = host;
	host->dma_desc = desc;
	host->dma_chan = dma_chan;
	host->dma_dir = dir_data;
पूर्ण

अटल व्योम bcm2835_start_dma(काष्ठा bcm2835_host *host)
अणु
	dmaengine_submit(host->dma_desc);
	dma_async_issue_pending(host->dma_chan);
पूर्ण

अटल व्योम bcm2835_set_transfer_irqs(काष्ठा bcm2835_host *host)
अणु
	u32 all_irqs = SDHCFG_DATA_IRPT_EN | SDHCFG_BLOCK_IRPT_EN |
		SDHCFG_BUSY_IRPT_EN;

	अगर (host->dma_desc) अणु
		host->hcfg = (host->hcfg & ~all_irqs) |
			SDHCFG_BUSY_IRPT_EN;
	पूर्ण अन्यथा अणु
		host->hcfg = (host->hcfg & ~all_irqs) |
			SDHCFG_DATA_IRPT_EN |
			SDHCFG_BUSY_IRPT_EN;
	पूर्ण

	ग_लिखोl(host->hcfg, host->ioaddr + SDHCFG);
पूर्ण

अटल
व्योम bcm2835_prepare_data(काष्ठा bcm2835_host *host, काष्ठा mmc_command *cmd)
अणु
	काष्ठा mmc_data *data = cmd->data;

	WARN_ON(host->data);

	host->data = data;
	अगर (!data)
		वापस;

	host->data_complete = false;
	host->data->bytes_xfered = 0;

	अगर (!host->dma_desc) अणु
		/* Use PIO */
		पूर्णांक flags = SG_MITER_ATOMIC;

		अगर (data->flags & MMC_DATA_READ)
			flags |= SG_MITER_TO_SG;
		अन्यथा
			flags |= SG_MITER_FROM_SG;
		sg_miter_start(&host->sg_miter, data->sg, data->sg_len, flags);
		host->blocks = data->blocks;
	पूर्ण

	bcm2835_set_transfer_irqs(host);

	ग_लिखोl(data->blksz, host->ioaddr + SDHBCT);
	ग_लिखोl(data->blocks, host->ioaddr + SDHBLC);
पूर्ण

अटल u32 bcm2835_पढ़ो_रुको_sdcmd(काष्ठा bcm2835_host *host, u32 max_ms)
अणु
	काष्ठा device *dev = &host->pdev->dev;
	u32 value;
	पूर्णांक ret;

	ret = पढ़ोl_poll_समयout(host->ioaddr + SDCMD, value,
				 !(value & SDCMD_NEW_FLAG), 1, 10);
	अगर (ret == -ETIMEDOUT)
		/* अगर it takes a जबतक make poll पूर्णांकerval bigger */
		ret = पढ़ोl_poll_समयout(host->ioaddr + SDCMD, value,
					 !(value & SDCMD_NEW_FLAG),
					 10, max_ms * 1000);
	अगर (ret == -ETIMEDOUT)
		dev_err(dev, "%s: timeout (%d ms)\n", __func__, max_ms);

	वापस value;
पूर्ण

अटल व्योम bcm2835_finish_request(काष्ठा bcm2835_host *host)
अणु
	काष्ठा dma_chan *terminate_chan = शून्य;
	काष्ठा mmc_request *mrq;

	cancel_delayed_work(&host->समयout_work);

	mrq = host->mrq;

	host->mrq = शून्य;
	host->cmd = शून्य;
	host->data = शून्य;

	host->dma_desc = शून्य;
	terminate_chan = host->dma_chan;
	host->dma_chan = शून्य;

	अगर (terminate_chan) अणु
		पूर्णांक err = dmaengine_terminate_all(terminate_chan);

		अगर (err)
			dev_err(&host->pdev->dev,
				"failed to terminate DMA (%d)\n", err);
	पूर्ण

	mmc_request_करोne(mmc_from_priv(host), mrq);
पूर्ण

अटल
bool bcm2835_send_command(काष्ठा bcm2835_host *host, काष्ठा mmc_command *cmd)
अणु
	काष्ठा device *dev = &host->pdev->dev;
	u32 sdcmd, sdhsts;
	अचिन्हित दीर्घ समयout;

	WARN_ON(host->cmd);

	sdcmd = bcm2835_पढ़ो_रुको_sdcmd(host, 100);
	अगर (sdcmd & SDCMD_NEW_FLAG) अणु
		dev_err(dev, "previous command never completed.\n");
		bcm2835_dumpregs(host);
		cmd->error = -EILSEQ;
		bcm2835_finish_request(host);
		वापस false;
	पूर्ण

	अगर (!cmd->data && cmd->busy_समयout > 9000)
		समयout = DIV_ROUND_UP(cmd->busy_समयout, 1000) * HZ + HZ;
	अन्यथा
		समयout = 10 * HZ;
	schedule_delayed_work(&host->समयout_work, समयout);

	host->cmd = cmd;

	/* Clear any error flags */
	sdhsts = पढ़ोl(host->ioaddr + SDHSTS);
	अगर (sdhsts & SDHSTS_ERROR_MASK)
		ग_लिखोl(sdhsts, host->ioaddr + SDHSTS);

	अगर ((cmd->flags & MMC_RSP_136) && (cmd->flags & MMC_RSP_BUSY)) अणु
		dev_err(dev, "unsupported response type!\n");
		cmd->error = -EINVAL;
		bcm2835_finish_request(host);
		वापस false;
	पूर्ण

	bcm2835_prepare_data(host, cmd);

	ग_लिखोl(cmd->arg, host->ioaddr + SDARG);

	sdcmd = cmd->opcode & SDCMD_CMD_MASK;

	host->use_busy = false;
	अगर (!(cmd->flags & MMC_RSP_PRESENT)) अणु
		sdcmd |= SDCMD_NO_RESPONSE;
	पूर्ण अन्यथा अणु
		अगर (cmd->flags & MMC_RSP_136)
			sdcmd |= SDCMD_LONG_RESPONSE;
		अगर (cmd->flags & MMC_RSP_BUSY) अणु
			sdcmd |= SDCMD_BUSYWAIT;
			host->use_busy = true;
		पूर्ण
	पूर्ण

	अगर (cmd->data) अणु
		अगर (cmd->data->flags & MMC_DATA_WRITE)
			sdcmd |= SDCMD_WRITE_CMD;
		अगर (cmd->data->flags & MMC_DATA_READ)
			sdcmd |= SDCMD_READ_CMD;
	पूर्ण

	ग_लिखोl(sdcmd | SDCMD_NEW_FLAG, host->ioaddr + SDCMD);

	वापस true;
पूर्ण

अटल व्योम bcm2835_transfer_complete(काष्ठा bcm2835_host *host)
अणु
	काष्ठा mmc_data *data;

	WARN_ON(!host->data_complete);

	data = host->data;
	host->data = शून्य;

	/* Need to send CMD12 अगर -
	 * a) खोलो-ended multiblock transfer (no CMD23)
	 * b) error in multiblock transfer
	 */
	अगर (host->mrq->stop && (data->error || !host->use_sbc)) अणु
		अगर (bcm2835_send_command(host, host->mrq->stop)) अणु
			/* No busy, so poll क्रम completion */
			अगर (!host->use_busy)
				bcm2835_finish_command(host);
		पूर्ण
	पूर्ण अन्यथा अणु
		bcm2835_रुको_transfer_complete(host);
		bcm2835_finish_request(host);
	पूर्ण
पूर्ण

अटल व्योम bcm2835_finish_data(काष्ठा bcm2835_host *host)
अणु
	काष्ठा device *dev = &host->pdev->dev;
	काष्ठा mmc_data *data;

	data = host->data;

	host->hcfg &= ~(SDHCFG_DATA_IRPT_EN | SDHCFG_BLOCK_IRPT_EN);
	ग_लिखोl(host->hcfg, host->ioaddr + SDHCFG);

	data->bytes_xfered = data->error ? 0 : (data->blksz * data->blocks);

	host->data_complete = true;

	अगर (host->cmd) अणु
		/* Data managed to finish beक्रमe the
		 * command completed. Make sure we करो
		 * things in the proper order.
		 */
		dev_dbg(dev, "Finished early - HSTS %08x\n",
			पढ़ोl(host->ioaddr + SDHSTS));
	पूर्ण अन्यथा अणु
		bcm2835_transfer_complete(host);
	पूर्ण
पूर्ण

अटल व्योम bcm2835_finish_command(काष्ठा bcm2835_host *host)
अणु
	काष्ठा device *dev = &host->pdev->dev;
	काष्ठा mmc_command *cmd = host->cmd;
	u32 sdcmd;

	sdcmd = bcm2835_पढ़ो_रुको_sdcmd(host, 100);

	/* Check क्रम errors */
	अगर (sdcmd & SDCMD_NEW_FLAG) अणु
		dev_err(dev, "command never completed.\n");
		bcm2835_dumpregs(host);
		host->cmd->error = -EIO;
		bcm2835_finish_request(host);
		वापस;
	पूर्ण अन्यथा अगर (sdcmd & SDCMD_FAIL_FLAG) अणु
		u32 sdhsts = पढ़ोl(host->ioaddr + SDHSTS);

		/* Clear the errors */
		ग_लिखोl(SDHSTS_ERROR_MASK, host->ioaddr + SDHSTS);

		अगर (!(sdhsts & SDHSTS_CRC7_ERROR) ||
		    (host->cmd->opcode != MMC_SEND_OP_COND)) अणु
			u32 edm, fsm;

			अगर (sdhsts & SDHSTS_CMD_TIME_OUT) अणु
				host->cmd->error = -ETIMEDOUT;
			पूर्ण अन्यथा अणु
				dev_err(dev, "unexpected command %d error\n",
					host->cmd->opcode);
				bcm2835_dumpregs(host);
				host->cmd->error = -EILSEQ;
			पूर्ण
			edm = पढ़ोl(host->ioaddr + SDEDM);
			fsm = edm & SDEDM_FSM_MASK;
			अगर (fsm == SDEDM_FSM_READWAIT ||
			    fsm == SDEDM_FSM_WRITESTART1)
				/* Kick the FSM out of its रुको */
				ग_लिखोl(edm | SDEDM_FORCE_DATA_MODE,
				       host->ioaddr + SDEDM);
			bcm2835_finish_request(host);
			वापस;
		पूर्ण
	पूर्ण

	अगर (cmd->flags & MMC_RSP_PRESENT) अणु
		अगर (cmd->flags & MMC_RSP_136) अणु
			पूर्णांक i;

			क्रम (i = 0; i < 4; i++) अणु
				cmd->resp[3 - i] =
					पढ़ोl(host->ioaddr + SDRSP0 + i * 4);
			पूर्ण
		पूर्ण अन्यथा अणु
			cmd->resp[0] = पढ़ोl(host->ioaddr + SDRSP0);
		पूर्ण
	पूर्ण

	अगर (cmd == host->mrq->sbc) अणु
		/* Finished CMD23, now send actual command. */
		host->cmd = शून्य;
		अगर (bcm2835_send_command(host, host->mrq->cmd)) अणु
			अगर (host->data && host->dma_desc)
				/* DMA transfer starts now, PIO starts
				 * after irq
				 */
				bcm2835_start_dma(host);

			अगर (!host->use_busy)
				bcm2835_finish_command(host);
		पूर्ण
	पूर्ण अन्यथा अगर (cmd == host->mrq->stop) अणु
		/* Finished CMD12 */
		bcm2835_finish_request(host);
	पूर्ण अन्यथा अणु
		/* Processed actual command. */
		host->cmd = शून्य;
		अगर (!host->data)
			bcm2835_finish_request(host);
		अन्यथा अगर (host->data_complete)
			bcm2835_transfer_complete(host);
	पूर्ण
पूर्ण

अटल व्योम bcm2835_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *d = to_delayed_work(work);
	काष्ठा bcm2835_host *host =
		container_of(d, काष्ठा bcm2835_host, समयout_work);
	काष्ठा device *dev = &host->pdev->dev;

	mutex_lock(&host->mutex);

	अगर (host->mrq) अणु
		dev_err(dev, "timeout waiting for hardware interrupt.\n");
		bcm2835_dumpregs(host);

		bcm2835_reset(mmc_from_priv(host));

		अगर (host->data) अणु
			host->data->error = -ETIMEDOUT;
			bcm2835_finish_data(host);
		पूर्ण अन्यथा अणु
			अगर (host->cmd)
				host->cmd->error = -ETIMEDOUT;
			अन्यथा
				host->mrq->cmd->error = -ETIMEDOUT;

			bcm2835_finish_request(host);
		पूर्ण
	पूर्ण

	mutex_unlock(&host->mutex);
पूर्ण

अटल bool bcm2835_check_cmd_error(काष्ठा bcm2835_host *host, u32 पूर्णांकmask)
अणु
	काष्ठा device *dev = &host->pdev->dev;

	अगर (!(पूर्णांकmask & SDHSTS_ERROR_MASK))
		वापस false;

	अगर (!host->cmd)
		वापस true;

	dev_err(dev, "sdhost_busy_irq: intmask %08x\n", पूर्णांकmask);
	अगर (पूर्णांकmask & SDHSTS_CRC7_ERROR) अणु
		host->cmd->error = -EILSEQ;
	पूर्ण अन्यथा अगर (पूर्णांकmask & (SDHSTS_CRC16_ERROR |
			      SDHSTS_FIFO_ERROR)) अणु
		अगर (host->mrq->data)
			host->mrq->data->error = -EILSEQ;
		अन्यथा
			host->cmd->error = -EILSEQ;
	पूर्ण अन्यथा अगर (पूर्णांकmask & SDHSTS_REW_TIME_OUT) अणु
		अगर (host->mrq->data)
			host->mrq->data->error = -ETIMEDOUT;
		अन्यथा
			host->cmd->error = -ETIMEDOUT;
	पूर्ण अन्यथा अगर (पूर्णांकmask & SDHSTS_CMD_TIME_OUT) अणु
		host->cmd->error = -ETIMEDOUT;
	पूर्ण
	bcm2835_dumpregs(host);
	वापस true;
पूर्ण

अटल व्योम bcm2835_check_data_error(काष्ठा bcm2835_host *host, u32 पूर्णांकmask)
अणु
	अगर (!host->data)
		वापस;
	अगर (पूर्णांकmask & (SDHSTS_CRC16_ERROR | SDHSTS_FIFO_ERROR))
		host->data->error = -EILSEQ;
	अगर (पूर्णांकmask & SDHSTS_REW_TIME_OUT)
		host->data->error = -ETIMEDOUT;
पूर्ण

अटल व्योम bcm2835_busy_irq(काष्ठा bcm2835_host *host)
अणु
	अगर (WARN_ON(!host->cmd)) अणु
		bcm2835_dumpregs(host);
		वापस;
	पूर्ण

	अगर (WARN_ON(!host->use_busy)) अणु
		bcm2835_dumpregs(host);
		वापस;
	पूर्ण
	host->use_busy = false;

	bcm2835_finish_command(host);
पूर्ण

अटल व्योम bcm2835_data_irq(काष्ठा bcm2835_host *host, u32 पूर्णांकmask)
अणु
	/* There are no dedicated data/space available पूर्णांकerrupt
	 * status bits, so it is necessary to use the single shared
	 * data/space available FIFO status bits. It is thereक्रमe not
	 * an error to get here when there is no data transfer in
	 * progress.
	 */
	अगर (!host->data)
		वापस;

	bcm2835_check_data_error(host, पूर्णांकmask);
	अगर (host->data->error)
		जाओ finished;

	अगर (host->data->flags & MMC_DATA_WRITE) अणु
		/* Use the block पूर्णांकerrupt क्रम ग_लिखोs after the first block */
		host->hcfg &= ~(SDHCFG_DATA_IRPT_EN);
		host->hcfg |= SDHCFG_BLOCK_IRPT_EN;
		ग_लिखोl(host->hcfg, host->ioaddr + SDHCFG);
		bcm2835_transfer_pio(host);
	पूर्ण अन्यथा अणु
		bcm2835_transfer_pio(host);
		host->blocks--;
		अगर ((host->blocks == 0) || host->data->error)
			जाओ finished;
	पूर्ण
	वापस;

finished:
	host->hcfg &= ~(SDHCFG_DATA_IRPT_EN | SDHCFG_BLOCK_IRPT_EN);
	ग_लिखोl(host->hcfg, host->ioaddr + SDHCFG);
पूर्ण

अटल व्योम bcm2835_data_thपढ़ोed_irq(काष्ठा bcm2835_host *host)
अणु
	अगर (!host->data)
		वापस;
	अगर ((host->blocks == 0) || host->data->error)
		bcm2835_finish_data(host);
पूर्ण

अटल व्योम bcm2835_block_irq(काष्ठा bcm2835_host *host)
अणु
	अगर (WARN_ON(!host->data)) अणु
		bcm2835_dumpregs(host);
		वापस;
	पूर्ण

	अगर (!host->dma_desc) अणु
		WARN_ON(!host->blocks);
		अगर (host->data->error || (--host->blocks == 0))
			bcm2835_finish_data(host);
		अन्यथा
			bcm2835_transfer_pio(host);
	पूर्ण अन्यथा अगर (host->data->flags & MMC_DATA_WRITE) अणु
		bcm2835_finish_data(host);
	पूर्ण
पूर्ण

अटल irqवापस_t bcm2835_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	irqवापस_t result = IRQ_NONE;
	काष्ठा bcm2835_host *host = dev_id;
	u32 पूर्णांकmask;

	spin_lock(&host->lock);

	पूर्णांकmask = पढ़ोl(host->ioaddr + SDHSTS);

	ग_लिखोl(SDHSTS_BUSY_IRPT |
	       SDHSTS_BLOCK_IRPT |
	       SDHSTS_SDIO_IRPT |
	       SDHSTS_DATA_FLAG,
	       host->ioaddr + SDHSTS);

	अगर (पूर्णांकmask & SDHSTS_BLOCK_IRPT) अणु
		bcm2835_check_data_error(host, पूर्णांकmask);
		host->irq_block = true;
		result = IRQ_WAKE_THREAD;
	पूर्ण

	अगर (पूर्णांकmask & SDHSTS_BUSY_IRPT) अणु
		अगर (!bcm2835_check_cmd_error(host, पूर्णांकmask)) अणु
			host->irq_busy = true;
			result = IRQ_WAKE_THREAD;
		पूर्ण अन्यथा अणु
			result = IRQ_HANDLED;
		पूर्ण
	पूर्ण

	/* There is no true data पूर्णांकerrupt status bit, so it is
	 * necessary to qualअगरy the data flag with the पूर्णांकerrupt
	 * enable bit.
	 */
	अगर ((पूर्णांकmask & SDHSTS_DATA_FLAG) &&
	    (host->hcfg & SDHCFG_DATA_IRPT_EN)) अणु
		bcm2835_data_irq(host, पूर्णांकmask);
		host->irq_data = true;
		result = IRQ_WAKE_THREAD;
	पूर्ण

	spin_unlock(&host->lock);

	वापस result;
पूर्ण

अटल irqवापस_t bcm2835_thपढ़ोed_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा bcm2835_host *host = dev_id;
	अचिन्हित दीर्घ flags;
	bool block, busy, data;

	spin_lock_irqsave(&host->lock, flags);

	block = host->irq_block;
	busy  = host->irq_busy;
	data  = host->irq_data;
	host->irq_block = false;
	host->irq_busy  = false;
	host->irq_data  = false;

	spin_unlock_irqrestore(&host->lock, flags);

	mutex_lock(&host->mutex);

	अगर (block)
		bcm2835_block_irq(host);
	अगर (busy)
		bcm2835_busy_irq(host);
	अगर (data)
		bcm2835_data_thपढ़ोed_irq(host);

	mutex_unlock(&host->mutex);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम bcm2835_dma_complete_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bcm2835_host *host =
		container_of(work, काष्ठा bcm2835_host, dma_work);
	काष्ठा mmc_data *data;

	mutex_lock(&host->mutex);

	data = host->data;

	अगर (host->dma_chan) अणु
		dma_unmap_sg(host->dma_chan->device->dev,
			     data->sg, data->sg_len,
			     host->dma_dir);

		host->dma_chan = शून्य;
	पूर्ण

	अगर (host->drain_words) अणु
		अचिन्हित दीर्घ flags;
		व्योम *page;
		u32 *buf;

		अगर (host->drain_offset & PAGE_MASK) अणु
			host->drain_page += host->drain_offset >> PAGE_SHIFT;
			host->drain_offset &= ~PAGE_MASK;
		पूर्ण
		local_irq_save(flags);
		page = kmap_atomic(host->drain_page);
		buf = page + host->drain_offset;

		जबतक (host->drain_words) अणु
			u32 edm = पढ़ोl(host->ioaddr + SDEDM);

			अगर ((edm >> 4) & 0x1f)
				*(buf++) = पढ़ोl(host->ioaddr + SDDATA);
			host->drain_words--;
		पूर्ण

		kunmap_atomic(page);
		local_irq_restore(flags);
	पूर्ण

	bcm2835_finish_data(host);

	mutex_unlock(&host->mutex);
पूर्ण

अटल व्योम bcm2835_set_घड़ी(काष्ठा bcm2835_host *host, अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा mmc_host *mmc = mmc_from_priv(host);
	पूर्णांक भाग;

	/* The SDCDIV रेजिस्टर has 11 bits, and holds (भाग - 2).  But
	 * in data mode the max is 50MHz wihout a minimum, and only
	 * the bottom 3 bits are used. Since the चयन over is
	 * स्वतःmatic (unless we have marked the card as slow...),
	 * chosen values have to make sense in both modes.  Ident mode
	 * must be 100-400KHz, so can range check the requested
	 * घड़ी. CMD15 must be used to वापस to data mode, so this
	 * can be monitored.
	 *
	 * घड़ी 250MHz -> 0->125MHz, 1->83.3MHz, 2->62.5MHz, 3->50.0MHz
	 *                 4->41.7MHz, 5->35.7MHz, 6->31.3MHz, 7->27.8MHz
	 *
	 *		 623->400KHz/27.8MHz
	 *		 reset value (507)->491159/50MHz
	 *
	 * BUT, the 3-bit घड़ी भागisor in data mode is too small अगर
	 * the core घड़ी is higher than 250MHz, so instead use the
	 * SLOW_CARD configuration bit to क्रमce the use of the ident
	 * घड़ी भागisor at all बार.
	 */

	अगर (घड़ी < 100000) अणु
		/* Can't stop the घड़ी, but make it as slow as possible
		 * to show willing
		 */
		host->cभाग = SDCDIV_MAX_CDIV;
		ग_लिखोl(host->cभाग, host->ioaddr + SDCDIV);
		वापस;
	पूर्ण

	भाग = host->max_clk / घड़ी;
	अगर (भाग < 2)
		भाग = 2;
	अगर ((host->max_clk / भाग) > घड़ी)
		भाग++;
	भाग -= 2;

	अगर (भाग > SDCDIV_MAX_CDIV)
		भाग = SDCDIV_MAX_CDIV;

	घड़ी = host->max_clk / (भाग + 2);
	mmc->actual_घड़ी = घड़ी;

	/* Calibrate some delays */

	host->ns_per_fअगरo_word = (1000000000 / घड़ी) *
		((mmc->caps & MMC_CAP_4_BIT_DATA) ? 8 : 32);

	host->cभाग = भाग;
	ग_लिखोl(host->cभाग, host->ioaddr + SDCDIV);

	/* Set the समयout to 500ms */
	ग_लिखोl(mmc->actual_घड़ी / 2, host->ioaddr + SDTOUT);
पूर्ण

अटल व्योम bcm2835_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा bcm2835_host *host = mmc_priv(mmc);
	काष्ठा device *dev = &host->pdev->dev;
	u32 edm, fsm;

	/* Reset the error statuses in हाल this is a retry */
	अगर (mrq->sbc)
		mrq->sbc->error = 0;
	अगर (mrq->cmd)
		mrq->cmd->error = 0;
	अगर (mrq->data)
		mrq->data->error = 0;
	अगर (mrq->stop)
		mrq->stop->error = 0;

	अगर (mrq->data && !is_घातer_of_2(mrq->data->blksz)) अणु
		dev_err(dev, "unsupported block size (%d bytes)\n",
			mrq->data->blksz);

		अगर (mrq->cmd)
			mrq->cmd->error = -EINVAL;

		mmc_request_करोne(mmc, mrq);
		वापस;
	पूर्ण

	mutex_lock(&host->mutex);

	WARN_ON(host->mrq);
	host->mrq = mrq;

	edm = पढ़ोl(host->ioaddr + SDEDM);
	fsm = edm & SDEDM_FSM_MASK;

	अगर ((fsm != SDEDM_FSM_IDENTMODE) &&
	    (fsm != SDEDM_FSM_DATAMODE)) अणु
		dev_err(dev, "previous command (%d) not complete (EDM %08x)\n",
			पढ़ोl(host->ioaddr + SDCMD) & SDCMD_CMD_MASK,
			edm);
		bcm2835_dumpregs(host);

		अगर (mrq->cmd)
			mrq->cmd->error = -EILSEQ;

		bcm2835_finish_request(host);
		mutex_unlock(&host->mutex);
		वापस;
	पूर्ण

	अगर (host->use_dma && mrq->data && (mrq->data->blocks > PIO_THRESHOLD))
		bcm2835_prepare_dma(host, mrq->data);

	host->use_sbc = !!mrq->sbc && host->mrq->data &&
			(host->mrq->data->flags & MMC_DATA_READ);
	अगर (host->use_sbc) अणु
		अगर (bcm2835_send_command(host, mrq->sbc)) अणु
			अगर (!host->use_busy)
				bcm2835_finish_command(host);
		पूर्ण
	पूर्ण अन्यथा अगर (mrq->cmd && bcm2835_send_command(host, mrq->cmd)) अणु
		अगर (host->data && host->dma_desc) अणु
			/* DMA transfer starts now, PIO starts after irq */
			bcm2835_start_dma(host);
		पूर्ण

		अगर (!host->use_busy)
			bcm2835_finish_command(host);
	पूर्ण

	mutex_unlock(&host->mutex);
पूर्ण

अटल व्योम bcm2835_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा bcm2835_host *host = mmc_priv(mmc);

	mutex_lock(&host->mutex);

	अगर (!ios->घड़ी || ios->घड़ी != host->घड़ी) अणु
		bcm2835_set_घड़ी(host, ios->घड़ी);
		host->घड़ी = ios->घड़ी;
	पूर्ण

	/* set bus width */
	host->hcfg &= ~SDHCFG_WIDE_EXT_BUS;
	अगर (ios->bus_width == MMC_BUS_WIDTH_4)
		host->hcfg |= SDHCFG_WIDE_EXT_BUS;

	host->hcfg |= SDHCFG_WIDE_INT_BUS;

	/* Disable clever घड़ी चयनing, to cope with fast core घड़ीs */
	host->hcfg |= SDHCFG_SLOW_CARD;

	ग_लिखोl(host->hcfg, host->ioaddr + SDHCFG);

	mutex_unlock(&host->mutex);
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops bcm2835_ops = अणु
	.request = bcm2835_request,
	.set_ios = bcm2835_set_ios,
	.hw_reset = bcm2835_reset,
पूर्ण;

अटल पूर्णांक bcm2835_add_host(काष्ठा bcm2835_host *host)
अणु
	काष्ठा mmc_host *mmc = mmc_from_priv(host);
	काष्ठा device *dev = &host->pdev->dev;
	अक्षर pio_limit_string[20];
	पूर्णांक ret;

	अगर (!mmc->f_max || mmc->f_max > host->max_clk)
		mmc->f_max = host->max_clk;
	mmc->f_min = host->max_clk / SDCDIV_MAX_CDIV;

	mmc->max_busy_समयout = ~0 / (mmc->f_max / 1000);

	dev_dbg(dev, "f_max %d, f_min %d, max_busy_timeout %d\n",
		mmc->f_max, mmc->f_min, mmc->max_busy_समयout);

	/* host controller capabilities */
	mmc->caps |= MMC_CAP_SD_HIGHSPEED | MMC_CAP_MMC_HIGHSPEED |
		     MMC_CAP_NEEDS_POLL | MMC_CAP_HW_RESET | MMC_CAP_CMD23;

	spin_lock_init(&host->lock);
	mutex_init(&host->mutex);

	अगर (!host->dma_chan_rxtx) अणु
		dev_warn(dev, "unable to initialise DMA channel. Falling back to PIO\n");
		host->use_dma = false;
	पूर्ण अन्यथा अणु
		host->use_dma = true;

		host->dma_cfg_tx.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		host->dma_cfg_tx.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		host->dma_cfg_tx.slave_id = 13;		/* DREQ channel */
		host->dma_cfg_tx.direction = DMA_MEM_TO_DEV;
		host->dma_cfg_tx.src_addr = 0;
		host->dma_cfg_tx.dst_addr = host->phys_addr + SDDATA;

		host->dma_cfg_rx.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		host->dma_cfg_rx.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		host->dma_cfg_rx.slave_id = 13;		/* DREQ channel */
		host->dma_cfg_rx.direction = DMA_DEV_TO_MEM;
		host->dma_cfg_rx.src_addr = host->phys_addr + SDDATA;
		host->dma_cfg_rx.dst_addr = 0;

		अगर (dmaengine_slave_config(host->dma_chan_rxtx,
					   &host->dma_cfg_tx) != 0 ||
		    dmaengine_slave_config(host->dma_chan_rxtx,
					   &host->dma_cfg_rx) != 0)
			host->use_dma = false;
	पूर्ण

	mmc->max_segs = 128;
	mmc->max_req_size = min_t(माप_प्रकार, 524288, dma_max_mapping_size(dev));
	mmc->max_seg_size = mmc->max_req_size;
	mmc->max_blk_size = 1024;
	mmc->max_blk_count =  65535;

	/* report supported voltage ranges */
	mmc->ocr_avail = MMC_VDD_32_33 | MMC_VDD_33_34;

	INIT_WORK(&host->dma_work, bcm2835_dma_complete_work);
	INIT_DELAYED_WORK(&host->समयout_work, bcm2835_समयout);

	/* Set पूर्णांकerrupt enables */
	host->hcfg = SDHCFG_BUSY_IRPT_EN;

	bcm2835_reset_पूर्णांकernal(host);

	ret = request_thपढ़ोed_irq(host->irq, bcm2835_irq,
				   bcm2835_thपढ़ोed_irq,
				   0, mmc_hostname(mmc), host);
	अगर (ret) अणु
		dev_err(dev, "failed to request IRQ %d: %d\n", host->irq, ret);
		वापस ret;
	पूर्ण

	ret = mmc_add_host(mmc);
	अगर (ret) अणु
		मुक्त_irq(host->irq, host);
		वापस ret;
	पूर्ण

	pio_limit_string[0] = '\0';
	अगर (host->use_dma && (PIO_THRESHOLD > 0))
		प्र_लिखो(pio_limit_string, " (>%d)", PIO_THRESHOLD);
	dev_info(dev, "loaded - DMA %s%s\n",
		 host->use_dma ? "enabled" : "disabled", pio_limit_string);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा clk *clk;
	काष्ठा bcm2835_host *host;
	काष्ठा mmc_host *mmc;
	स्थिर __be32 *regaddr_p;
	पूर्णांक ret;

	dev_dbg(dev, "%s\n", __func__);
	mmc = mmc_alloc_host(माप(*host), dev);
	अगर (!mmc)
		वापस -ENOMEM;

	mmc->ops = &bcm2835_ops;
	host = mmc_priv(mmc);
	host->pdev = pdev;
	spin_lock_init(&host->lock);

	host->ioaddr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(host->ioaddr)) अणु
		ret = PTR_ERR(host->ioaddr);
		जाओ err;
	पूर्ण

	/* Parse OF address directly to get the physical address क्रम
	 * DMA to our रेजिस्टरs.
	 */
	regaddr_p = of_get_address(pdev->dev.of_node, 0, शून्य, शून्य);
	अगर (!regaddr_p) अणु
		dev_err(dev, "Can't get phys address\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	host->phys_addr = be32_to_cpup(regaddr_p);

	host->dma_chan = शून्य;
	host->dma_desc = शून्य;

	host->dma_chan_rxtx = dma_request_chan(dev, "rx-tx");
	अगर (IS_ERR(host->dma_chan_rxtx)) अणु
		ret = PTR_ERR(host->dma_chan_rxtx);
		host->dma_chan_rxtx = शून्य;

		अगर (ret == -EPROBE_DEFER)
			जाओ err;

		/* Ignore errors to fall back to PIO mode */
	पूर्ण


	clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		ret = dev_err_probe(dev, PTR_ERR(clk), "could not get clk\n");
		जाओ err;
	पूर्ण

	host->max_clk = clk_get_rate(clk);

	host->irq = platक्रमm_get_irq(pdev, 0);
	अगर (host->irq <= 0) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = mmc_of_parse(mmc);
	अगर (ret)
		जाओ err;

	ret = bcm2835_add_host(host);
	अगर (ret)
		जाओ err;

	platक्रमm_set_drvdata(pdev, host);

	dev_dbg(dev, "%s -> OK\n", __func__);

	वापस 0;

err:
	dev_dbg(dev, "%s -> err %d\n", __func__, ret);
	अगर (host->dma_chan_rxtx)
		dma_release_channel(host->dma_chan_rxtx);
	mmc_मुक्त_host(mmc);

	वापस ret;
पूर्ण

अटल पूर्णांक bcm2835_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm2835_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा mmc_host *mmc = mmc_from_priv(host);

	mmc_हटाओ_host(mmc);

	ग_लिखोl(SDVDD_POWER_OFF, host->ioaddr + SDVDD);

	मुक्त_irq(host->irq, host);

	cancel_work_sync(&host->dma_work);
	cancel_delayed_work_sync(&host->समयout_work);

	अगर (host->dma_chan_rxtx)
		dma_release_channel(host->dma_chan_rxtx);

	mmc_मुक्त_host(mmc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm2835_match[] = अणु
	अणु .compatible = "brcm,bcm2835-sdhost" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm2835_match);

अटल काष्ठा platक्रमm_driver bcm2835_driver = अणु
	.probe      = bcm2835_probe,
	.हटाओ     = bcm2835_हटाओ,
	.driver     = अणु
		.name		= "sdhost-bcm2835",
		.probe_type	= PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table	= bcm2835_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(bcm2835_driver);

MODULE_ALIAS("platform:sdhost-bcm2835");
MODULE_DESCRIPTION("BCM2835 SDHost driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Phil Elwell");
