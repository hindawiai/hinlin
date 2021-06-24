<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/mmc/s3cmci.h - Samsung S3C MCI driver
 *
 *  Copyright (C) 2004-2006 मुख्यtech GmbH, Thomas Kleffel <tk@मुख्यtech.de>
 *
 * Current driver मुख्यtained by Ben Dooks and Simtec Electronics
 *  Copyright (C) 2008 Simtec Electronics <ben-linux@fluff.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/clk.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/mmc/slot-gpपन.स>
#समावेश <linux/platक्रमm_data/mmc-s3cmci.h>

#समावेश "s3cmci.h"

#घोषणा DRIVER_NAME "s3c-mci"

#घोषणा S3C2410_SDICON			(0x00)
#घोषणा S3C2410_SDIPRE			(0x04)
#घोषणा S3C2410_SDICMDARG		(0x08)
#घोषणा S3C2410_SDICMDCON		(0x0C)
#घोषणा S3C2410_SDICMDSTAT		(0x10)
#घोषणा S3C2410_SसूचीSP0			(0x14)
#घोषणा S3C2410_SसूचीSP1			(0x18)
#घोषणा S3C2410_SसूचीSP2			(0x1C)
#घोषणा S3C2410_SसूचीSP3			(0x20)
#घोषणा S3C2410_SDITIMER		(0x24)
#घोषणा S3C2410_SDIBSIZE		(0x28)
#घोषणा S3C2410_SDIDCON			(0x2C)
#घोषणा S3C2410_SDIDCNT			(0x30)
#घोषणा S3C2410_SDIDSTA			(0x34)
#घोषणा S3C2410_SDIFSTA			(0x38)

#घोषणा S3C2410_SDIDATA			(0x3C)
#घोषणा S3C2410_SDIIMSK			(0x40)

#घोषणा S3C2440_SDIDATA			(0x40)
#घोषणा S3C2440_SDIIMSK			(0x3C)

#घोषणा S3C2440_SDICON_SDRESET		(1 << 8)
#घोषणा S3C2410_SDICON_SDIOIRQ		(1 << 3)
#घोषणा S3C2410_SDICON_FIFORESET	(1 << 1)
#घोषणा S3C2410_SDICON_CLOCKTYPE	(1 << 0)

#घोषणा S3C2410_SDICMDCON_LONGRSP	(1 << 10)
#घोषणा S3C2410_SDICMDCON_WAITRSP	(1 << 9)
#घोषणा S3C2410_SDICMDCON_CMDSTART	(1 << 8)
#घोषणा S3C2410_SDICMDCON_SENDERHOST	(1 << 6)
#घोषणा S3C2410_SDICMDCON_INDEX		(0x3f)

#घोषणा S3C2410_SDICMDSTAT_CRCFAIL	(1 << 12)
#घोषणा S3C2410_SDICMDSTAT_CMDSENT	(1 << 11)
#घोषणा S3C2410_SDICMDSTAT_CMDTIMEOUT	(1 << 10)
#घोषणा S3C2410_SDICMDSTAT_RSPFIN	(1 << 9)

#घोषणा S3C2440_SDIDCON_DS_WORD		(2 << 22)
#घोषणा S3C2410_SDIDCON_TXAFTERRESP	(1 << 20)
#घोषणा S3C2410_SDIDCON_RXAFTERCMD	(1 << 19)
#घोषणा S3C2410_SDIDCON_BLOCKMODE	(1 << 17)
#घोषणा S3C2410_SDIDCON_WIDEBUS		(1 << 16)
#घोषणा S3C2410_SDIDCON_DMAEN		(1 << 15)
#घोषणा S3C2410_SDIDCON_STOP		(1 << 14)
#घोषणा S3C2440_SDIDCON_DATSTART	(1 << 14)

#घोषणा S3C2410_SDIDCON_XFER_RXSTART	(2 << 12)
#घोषणा S3C2410_SDIDCON_XFER_TXSTART	(3 << 12)

#घोषणा S3C2410_SDIDCON_BLKNUM_MASK	(0xFFF)

#घोषणा S3C2410_SDIDSTA_SDIOIRQDETECT	(1 << 9)
#घोषणा S3C2410_SDIDSTA_FIFOFAIL	(1 << 8)
#घोषणा S3C2410_SDIDSTA_CRCFAIL		(1 << 7)
#घोषणा S3C2410_SDIDSTA_RXCRCFAIL	(1 << 6)
#घोषणा S3C2410_SDIDSTA_DATATIMEOUT	(1 << 5)
#घोषणा S3C2410_SDIDSTA_XFERFINISH	(1 << 4)
#घोषणा S3C2410_SDIDSTA_TXDATAON	(1 << 1)
#घोषणा S3C2410_SDIDSTA_RXDATAON	(1 << 0)

#घोषणा S3C2440_SDIFSTA_FIFORESET	(1 << 16)
#घोषणा S3C2440_SDIFSTA_FIFOFAIL	(3 << 14)
#घोषणा S3C2410_SDIFSTA_TFDET		(1 << 13)
#घोषणा S3C2410_SDIFSTA_RFDET		(1 << 12)
#घोषणा S3C2410_SDIFSTA_COUNTMASK	(0x7f)

#घोषणा S3C2410_SDIIMSK_RESPONSECRC	(1 << 17)
#घोषणा S3C2410_SDIIMSK_CMDSENT		(1 << 16)
#घोषणा S3C2410_SDIIMSK_CMDTIMEOUT	(1 << 15)
#घोषणा S3C2410_SDIIMSK_RESPONSEND	(1 << 14)
#घोषणा S3C2410_SDIIMSK_SDIOIRQ		(1 << 12)
#घोषणा S3C2410_SDIIMSK_FIFOFAIL	(1 << 11)
#घोषणा S3C2410_SDIIMSK_CRCSTATUS	(1 << 10)
#घोषणा S3C2410_SDIIMSK_DATACRC		(1 << 9)
#घोषणा S3C2410_SDIIMSK_DATATIMEOUT	(1 << 8)
#घोषणा S3C2410_SDIIMSK_DATAFINISH	(1 << 7)
#घोषणा S3C2410_SDIIMSK_TXFIFOHALF	(1 << 4)
#घोषणा S3C2410_SDIIMSK_RXFIFOLAST	(1 << 2)
#घोषणा S3C2410_SDIIMSK_RXFIFOHALF	(1 << 0)

क्रमागत dbg_channels अणु
	dbg_err   = (1 << 0),
	dbg_debug = (1 << 1),
	dbg_info  = (1 << 2),
	dbg_irq   = (1 << 3),
	dbg_sg    = (1 << 4),
	dbg_dma   = (1 << 5),
	dbg_pio   = (1 << 6),
	dbg_fail  = (1 << 7),
	dbg_conf  = (1 << 8),
पूर्ण;

अटल स्थिर पूर्णांक dbgmap_err   = dbg_fail;
अटल स्थिर पूर्णांक dbgmap_info  = dbg_info | dbg_conf;
अटल स्थिर पूर्णांक dbgmap_debug = dbg_err | dbg_debug;

#घोषणा dbg(host, channels, args...)		  \
	करो अणु					  \
	अगर (dbgmap_err & channels) 		  \
		dev_err(&host->pdev->dev, args);  \
	अन्यथा अगर (dbgmap_info & channels)	  \
		dev_info(&host->pdev->dev, args); \
	अन्यथा अगर (dbgmap_debug & channels)	  \
		dev_dbg(&host->pdev->dev, args);  \
	पूर्ण जबतक (0)

अटल व्योम finalize_request(काष्ठा s3cmci_host *host);
अटल व्योम s3cmci_send_request(काष्ठा mmc_host *mmc);
अटल व्योम s3cmci_reset(काष्ठा s3cmci_host *host);

#अगर_घोषित CONFIG_MMC_DEBUG

अटल व्योम dbg_dumpregs(काष्ठा s3cmci_host *host, अक्षर *prefix)
अणु
	u32 con, pre, cmdarg, cmdcon, cmdsta, r0, r1, r2, r3, समयr;
	u32 datcon, datcnt, datsta, fsta;

	con 	= पढ़ोl(host->base + S3C2410_SDICON);
	pre 	= पढ़ोl(host->base + S3C2410_SDIPRE);
	cmdarg 	= पढ़ोl(host->base + S3C2410_SDICMDARG);
	cmdcon 	= पढ़ोl(host->base + S3C2410_SDICMDCON);
	cmdsta 	= पढ़ोl(host->base + S3C2410_SDICMDSTAT);
	r0 	= पढ़ोl(host->base + S3C2410_SसूचीSP0);
	r1 	= पढ़ोl(host->base + S3C2410_SसूचीSP1);
	r2 	= पढ़ोl(host->base + S3C2410_SसूचीSP2);
	r3 	= पढ़ोl(host->base + S3C2410_SसूचीSP3);
	समयr 	= पढ़ोl(host->base + S3C2410_SDITIMER);
	datcon 	= पढ़ोl(host->base + S3C2410_SDIDCON);
	datcnt 	= पढ़ोl(host->base + S3C2410_SDIDCNT);
	datsta 	= पढ़ोl(host->base + S3C2410_SDIDSTA);
	fsta 	= पढ़ोl(host->base + S3C2410_SDIFSTA);

	dbg(host, dbg_debug, "%s  CON:[%08x]  PRE:[%08x]  TMR:[%08x]\n",
				prefix, con, pre, समयr);

	dbg(host, dbg_debug, "%s CCON:[%08x] CARG:[%08x] CSTA:[%08x]\n",
				prefix, cmdcon, cmdarg, cmdsta);

	dbg(host, dbg_debug, "%s DCON:[%08x] FSTA:[%08x]"
			       " DSTA:[%08x] DCNT:[%08x]\n",
				prefix, datcon, fsta, datsta, datcnt);

	dbg(host, dbg_debug, "%s   R0:[%08x]   R1:[%08x]"
			       "   R2:[%08x]   R3:[%08x]\n",
				prefix, r0, r1, r2, r3);
पूर्ण

अटल व्योम prepare_dbgmsg(काष्ठा s3cmci_host *host, काष्ठा mmc_command *cmd,
			   पूर्णांक stop)
अणु
	snम_लिखो(host->dbgmsg_cmd, 300,
		 "#%u%s op:%i arg:0x%08x flags:0x08%x retries:%u",
		 host->ccnt, (stop ? " (STOP)" : ""),
		 cmd->opcode, cmd->arg, cmd->flags, cmd->retries);

	अगर (cmd->data) अणु
		snम_लिखो(host->dbgmsg_dat, 300,
			 "#%u bsize:%u blocks:%u bytes:%u",
			 host->dcnt, cmd->data->blksz,
			 cmd->data->blocks,
			 cmd->data->blocks * cmd->data->blksz);
	पूर्ण अन्यथा अणु
		host->dbgmsg_dat[0] = '\0';
	पूर्ण
पूर्ण

अटल व्योम dbg_dumpcmd(काष्ठा s3cmci_host *host, काष्ठा mmc_command *cmd,
			पूर्णांक fail)
अणु
	अचिन्हित पूर्णांक dbglvl = fail ? dbg_fail : dbg_debug;

	अगर (!cmd)
		वापस;

	अगर (cmd->error == 0) अणु
		dbg(host, dbglvl, "CMD[OK] %s R0:0x%08x\n",
			host->dbgmsg_cmd, cmd->resp[0]);
	पूर्ण अन्यथा अणु
		dbg(host, dbglvl, "CMD[ERR %i] %s Status:%s\n",
			cmd->error, host->dbgmsg_cmd, host->status);
	पूर्ण

	अगर (!cmd->data)
		वापस;

	अगर (cmd->data->error == 0) अणु
		dbg(host, dbglvl, "DAT[OK] %s\n", host->dbgmsg_dat);
	पूर्ण अन्यथा अणु
		dbg(host, dbglvl, "DAT[ERR %i] %s DCNT:0x%08x\n",
			cmd->data->error, host->dbgmsg_dat,
			पढ़ोl(host->base + S3C2410_SDIDCNT));
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम dbg_dumpcmd(काष्ठा s3cmci_host *host,
			काष्ठा mmc_command *cmd, पूर्णांक fail) अणु पूर्ण

अटल व्योम prepare_dbgmsg(काष्ठा s3cmci_host *host, काष्ठा mmc_command *cmd,
			   पूर्णांक stop) अणु पूर्ण

अटल व्योम dbg_dumpregs(काष्ठा s3cmci_host *host, अक्षर *prefix) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_MMC_DEBUG */

/**
 * s3cmci_host_usedma - वापस whether the host is using dma or pio
 * @host: The host state
 *
 * Return true अगर the host is using DMA to transfer data, अन्यथा false
 * to use PIO mode. Will वापस अटल data depending on the driver
 * configuration.
 */
अटल अंतरभूत bool s3cmci_host_usedma(काष्ठा s3cmci_host *host)
अणु
#अगर_घोषित CONFIG_MMC_S3C_PIO
	वापस false;
#अन्यथा /* CONFIG_MMC_S3C_DMA */
	वापस true;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत u32 enable_imask(काष्ठा s3cmci_host *host, u32 imask)
अणु
	u32 newmask;

	newmask = पढ़ोl(host->base + host->sdiimsk);
	newmask |= imask;

	ग_लिखोl(newmask, host->base + host->sdiimsk);

	वापस newmask;
पूर्ण

अटल अंतरभूत u32 disable_imask(काष्ठा s3cmci_host *host, u32 imask)
अणु
	u32 newmask;

	newmask = पढ़ोl(host->base + host->sdiimsk);
	newmask &= ~imask;

	ग_लिखोl(newmask, host->base + host->sdiimsk);

	वापस newmask;
पूर्ण

अटल अंतरभूत व्योम clear_imask(काष्ठा s3cmci_host *host)
अणु
	u32 mask = पढ़ोl(host->base + host->sdiimsk);

	/* preserve the SDIO IRQ mask state */
	mask &= S3C2410_SDIIMSK_SDIOIRQ;
	ग_लिखोl(mask, host->base + host->sdiimsk);
पूर्ण

/**
 * s3cmci_check_sdio_irq - test whether the SDIO IRQ is being संकेतled
 * @host: The host to check.
 *
 * Test to see अगर the SDIO पूर्णांकerrupt is being संकेतled in हाल the
 * controller has failed to re-detect a card पूर्णांकerrupt. Read GPE8 and
 * see अगर it is low and अगर so, संकेत a SDIO पूर्णांकerrupt.
 *
 * This is currently called अगर a request is finished (we assume that the
 * bus is now idle) and when the SDIO IRQ is enabled in हाल the IRQ is
 * alपढ़ोy being indicated.
*/
अटल व्योम s3cmci_check_sdio_irq(काष्ठा s3cmci_host *host)
अणु
	अगर (host->sdio_irqen) अणु
		अगर (host->pdata->bus[3] &&
		    gpiod_get_value(host->pdata->bus[3]) == 0) अणु
			pr_debug("%s: signalling irq\n", __func__);
			mmc_संकेत_sdio_irq(host->mmc);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक get_data_buffer(काष्ठा s3cmci_host *host,
				  u32 *bytes, u32 **poपूर्णांकer)
अणु
	काष्ठा scatterlist *sg;

	अगर (host->pio_active == XFER_NONE)
		वापस -EINVAL;

	अगर ((!host->mrq) || (!host->mrq->data))
		वापस -EINVAL;

	अगर (host->pio_sgptr >= host->mrq->data->sg_len) अणु
		dbg(host, dbg_debug, "no more buffers (%i/%i)\n",
		      host->pio_sgptr, host->mrq->data->sg_len);
		वापस -EBUSY;
	पूर्ण
	sg = &host->mrq->data->sg[host->pio_sgptr];

	*bytes = sg->length;
	*poपूर्णांकer = sg_virt(sg);

	host->pio_sgptr++;

	dbg(host, dbg_sg, "new buffer (%i/%i)\n",
	    host->pio_sgptr, host->mrq->data->sg_len);

	वापस 0;
पूर्ण

अटल अंतरभूत u32 fअगरo_count(काष्ठा s3cmci_host *host)
अणु
	u32 fअगरostat = पढ़ोl(host->base + S3C2410_SDIFSTA);

	fअगरostat &= S3C2410_SDIFSTA_COUNTMASK;
	वापस fअगरostat;
पूर्ण

अटल अंतरभूत u32 fअगरo_मुक्त(काष्ठा s3cmci_host *host)
अणु
	u32 fअगरostat = पढ़ोl(host->base + S3C2410_SDIFSTA);

	fअगरostat &= S3C2410_SDIFSTA_COUNTMASK;
	वापस 63 - fअगरostat;
पूर्ण

/**
 * s3cmci_enable_irq - enable IRQ, after having disabled it.
 * @host: The device state.
 * @more: True अगर more IRQs are expected from transfer.
 *
 * Enable the मुख्य IRQ अगर needed after it has been disabled.
 *
 * The IRQ can be one of the following states:
 *	- disabled during IDLE
 *	- disabled whilst processing data
 *	- enabled during transfer
 *	- enabled whilst aरुकोing SDIO पूर्णांकerrupt detection
 */
अटल व्योम s3cmci_enable_irq(काष्ठा s3cmci_host *host, bool more)
अणु
	अचिन्हित दीर्घ flags;
	bool enable = false;

	local_irq_save(flags);

	host->irq_enabled = more;
	host->irq_disabled = false;

	enable = more | host->sdio_irqen;

	अगर (host->irq_state != enable) अणु
		host->irq_state = enable;

		अगर (enable)
			enable_irq(host->irq);
		अन्यथा
			disable_irq(host->irq);
	पूर्ण

	local_irq_restore(flags);
पूर्ण

अटल व्योम s3cmci_disable_irq(काष्ठा s3cmci_host *host, bool transfer)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	/* pr_debug("%s: transfer %d\n", __func__, transfer); */

	host->irq_disabled = transfer;

	अगर (transfer && host->irq_state) अणु
		host->irq_state = false;
		disable_irq(host->irq);
	पूर्ण

	local_irq_restore(flags);
पूर्ण

अटल व्योम करो_pio_पढ़ो(काष्ठा s3cmci_host *host)
अणु
	पूर्णांक res;
	u32 fअगरo;
	u32 *ptr;
	u32 fअगरo_words;
	व्योम __iomem *from_ptr;

	/* ग_लिखो real prescaler to host, it might be set slow to fix */
	ग_लिखोl(host->prescaler, host->base + S3C2410_SDIPRE);

	from_ptr = host->base + host->sdidata;

	जबतक ((fअगरo = fअगरo_count(host))) अणु
		अगर (!host->pio_bytes) अणु
			res = get_data_buffer(host, &host->pio_bytes,
					      &host->pio_ptr);
			अगर (res) अणु
				host->pio_active = XFER_NONE;
				host->complete_what = COMPLETION_FINALIZE;

				dbg(host, dbg_pio, "pio_read(): "
				    "complete (no more data).\n");
				वापस;
			पूर्ण

			dbg(host, dbg_pio,
			    "pio_read(): new target: [%i]@[%p]\n",
			    host->pio_bytes, host->pio_ptr);
		पूर्ण

		dbg(host, dbg_pio,
		    "pio_read(): fifo:[%02i] buffer:[%03i] dcnt:[%08X]\n",
		    fअगरo, host->pio_bytes,
		    पढ़ोl(host->base + S3C2410_SDIDCNT));

		/* If we have reached the end of the block, we can
		 * पढ़ो a word and get 1 to 3 bytes.  If we in the
		 * middle of the block, we have to पढ़ो full words,
		 * otherwise we will ग_लिखो garbage, so round करोwn to
		 * an even multiple of 4. */
		अगर (fअगरo >= host->pio_bytes)
			fअगरo = host->pio_bytes;
		अन्यथा
			fअगरo -= fअगरo & 3;

		host->pio_bytes -= fअगरo;
		host->pio_count += fअगरo;

		fअगरo_words = fअगरo >> 2;
		ptr = host->pio_ptr;
		जबतक (fअगरo_words--)
			*ptr++ = पढ़ोl(from_ptr);
		host->pio_ptr = ptr;

		अगर (fअगरo & 3) अणु
			u32 n = fअगरo & 3;
			u32 data = पढ़ोl(from_ptr);
			u8 *p = (u8 *)host->pio_ptr;

			जबतक (n--) अणु
				*p++ = data;
				data >>= 8;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!host->pio_bytes) अणु
		res = get_data_buffer(host, &host->pio_bytes, &host->pio_ptr);
		अगर (res) अणु
			dbg(host, dbg_pio,
			    "pio_read(): complete (no more buffers).\n");
			host->pio_active = XFER_NONE;
			host->complete_what = COMPLETION_FINALIZE;

			वापस;
		पूर्ण
	पूर्ण

	enable_imask(host,
		     S3C2410_SDIIMSK_RXFIFOHALF | S3C2410_SDIIMSK_RXFIFOLAST);
पूर्ण

अटल व्योम करो_pio_ग_लिखो(काष्ठा s3cmci_host *host)
अणु
	व्योम __iomem *to_ptr;
	पूर्णांक res;
	u32 fअगरo;
	u32 *ptr;

	to_ptr = host->base + host->sdidata;

	जबतक ((fअगरo = fअगरo_मुक्त(host)) > 3) अणु
		अगर (!host->pio_bytes) अणु
			res = get_data_buffer(host, &host->pio_bytes,
							&host->pio_ptr);
			अगर (res) अणु
				dbg(host, dbg_pio,
				    "pio_write(): complete (no more data).\n");
				host->pio_active = XFER_NONE;

				वापस;
			पूर्ण

			dbg(host, dbg_pio,
			    "pio_write(): new source: [%i]@[%p]\n",
			    host->pio_bytes, host->pio_ptr);

		पूर्ण

		/* If we have reached the end of the block, we have to
		 * ग_लिखो exactly the reमुख्यing number of bytes.  If we
		 * in the middle of the block, we have to ग_लिखो full
		 * words, so round करोwn to an even multiple of 4. */
		अगर (fअगरo >= host->pio_bytes)
			fअगरo = host->pio_bytes;
		अन्यथा
			fअगरo -= fअगरo & 3;

		host->pio_bytes -= fअगरo;
		host->pio_count += fअगरo;

		fअगरo = (fअगरo + 3) >> 2;
		ptr = host->pio_ptr;
		जबतक (fअगरo--)
			ग_लिखोl(*ptr++, to_ptr);
		host->pio_ptr = ptr;
	पूर्ण

	enable_imask(host, S3C2410_SDIIMSK_TXFIFOHALF);
पूर्ण

अटल व्योम pio_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा s3cmci_host *host = from_tasklet(host, t, pio_tasklet);

	s3cmci_disable_irq(host, true);

	अगर (host->pio_active == XFER_WRITE)
		करो_pio_ग_लिखो(host);

	अगर (host->pio_active == XFER_READ)
		करो_pio_पढ़ो(host);

	अगर (host->complete_what == COMPLETION_FINALIZE) अणु
		clear_imask(host);
		अगर (host->pio_active != XFER_NONE) अणु
			dbg(host, dbg_err, "unfinished %s "
			    "- pio_count:[%u] pio_bytes:[%u]\n",
			    (host->pio_active == XFER_READ) ? "read" : "write",
			    host->pio_count, host->pio_bytes);

			अगर (host->mrq->data)
				host->mrq->data->error = -EINVAL;
		पूर्ण

		s3cmci_enable_irq(host, false);
		finalize_request(host);
	पूर्ण अन्यथा
		s3cmci_enable_irq(host, true);
पूर्ण

/*
 * ISR क्रम SDI Interface IRQ
 * Communication between driver and ISR works as follows:
 *   host->mrq 			poपूर्णांकs to current request
 *   host->complete_what	Indicates when the request is considered करोne
 *     COMPLETION_CMDSENT	  when the command was sent
 *     COMPLETION_RSPFIN          when a response was received
 *     COMPLETION_XFERFINISH	  when the data transfer is finished
 *     COMPLETION_XFERFINISH_RSPFIN both of the above.
 *   host->complete_request	is the completion-object the driver रुकोs क्रम
 *
 * 1) Driver sets up host->mrq and host->complete_what
 * 2) Driver prepares the transfer
 * 3) Driver enables पूर्णांकerrupts
 * 4) Driver starts transfer
 * 5) Driver रुकोs क्रम host->complete_rquest
 * 6) ISR checks क्रम request status (errors and success)
 * 6) ISR sets host->mrq->cmd->error and host->mrq->data->error
 * 7) ISR completes host->complete_request
 * 8) ISR disables पूर्णांकerrupts
 * 9) Driver wakes up and takes care of the request
 *
 * Note: "->error"-fields are expected to be set to 0 beक्रमe the request
 *       was issued by mmc.c - thereक्रमe they are only set, when an error
 *       contition comes up
 */

अटल irqवापस_t s3cmci_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा s3cmci_host *host = dev_id;
	काष्ठा mmc_command *cmd;
	u32 mci_csta, mci_dsta, mci_fsta, mci_dcnt, mci_imsk;
	u32 mci_cclear = 0, mci_dclear;
	अचिन्हित दीर्घ अगरlags;

	mci_dsta = पढ़ोl(host->base + S3C2410_SDIDSTA);
	mci_imsk = पढ़ोl(host->base + host->sdiimsk);

	अगर (mci_dsta & S3C2410_SDIDSTA_SDIOIRQDETECT) अणु
		अगर (mci_imsk & S3C2410_SDIIMSK_SDIOIRQ) अणु
			mci_dclear = S3C2410_SDIDSTA_SDIOIRQDETECT;
			ग_लिखोl(mci_dclear, host->base + S3C2410_SDIDSTA);

			mmc_संकेत_sdio_irq(host->mmc);
			वापस IRQ_HANDLED;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&host->complete_lock, अगरlags);

	mci_csta = पढ़ोl(host->base + S3C2410_SDICMDSTAT);
	mci_dcnt = पढ़ोl(host->base + S3C2410_SDIDCNT);
	mci_fsta = पढ़ोl(host->base + S3C2410_SDIFSTA);
	mci_dclear = 0;

	अगर ((host->complete_what == COMPLETION_NONE) ||
	    (host->complete_what == COMPLETION_FINALIZE)) अणु
		host->status = "nothing to complete";
		clear_imask(host);
		जाओ irq_out;
	पूर्ण

	अगर (!host->mrq) अणु
		host->status = "no active mrq";
		clear_imask(host);
		जाओ irq_out;
	पूर्ण

	cmd = host->cmd_is_stop ? host->mrq->stop : host->mrq->cmd;

	अगर (!cmd) अणु
		host->status = "no active cmd";
		clear_imask(host);
		जाओ irq_out;
	पूर्ण

	अगर (!s3cmci_host_usedma(host)) अणु
		अगर ((host->pio_active == XFER_WRITE) &&
		    (mci_fsta & S3C2410_SDIFSTA_TFDET)) अणु

			disable_imask(host, S3C2410_SDIIMSK_TXFIFOHALF);
			tasklet_schedule(&host->pio_tasklet);
			host->status = "pio tx";
		पूर्ण

		अगर ((host->pio_active == XFER_READ) &&
		    (mci_fsta & S3C2410_SDIFSTA_RFDET)) अणु

			disable_imask(host,
				      S3C2410_SDIIMSK_RXFIFOHALF |
				      S3C2410_SDIIMSK_RXFIFOLAST);

			tasklet_schedule(&host->pio_tasklet);
			host->status = "pio rx";
		पूर्ण
	पूर्ण

	अगर (mci_csta & S3C2410_SDICMDSTAT_CMDTIMEOUT) अणु
		dbg(host, dbg_err, "CMDSTAT: error CMDTIMEOUT\n");
		cmd->error = -ETIMEDOUT;
		host->status = "error: command timeout";
		जाओ fail_transfer;
	पूर्ण

	अगर (mci_csta & S3C2410_SDICMDSTAT_CMDSENT) अणु
		अगर (host->complete_what == COMPLETION_CMDSENT) अणु
			host->status = "ok: command sent";
			जाओ बंद_transfer;
		पूर्ण

		mci_cclear |= S3C2410_SDICMDSTAT_CMDSENT;
	पूर्ण

	अगर (mci_csta & S3C2410_SDICMDSTAT_CRCFAIL) अणु
		अगर (cmd->flags & MMC_RSP_CRC) अणु
			अगर (host->mrq->cmd->flags & MMC_RSP_136) अणु
				dbg(host, dbg_irq,
				    "fixup: ignore CRC fail with long rsp\n");
			पूर्ण अन्यथा अणु
				/* note, we used to fail the transfer
				 * here, but it seems that this is just
				 * the hardware getting it wrong.
				 *
				 * cmd->error = -EILSEQ;
				 * host->status = "error: bad command crc";
				 * जाओ fail_transfer;
				*/
			पूर्ण
		पूर्ण

		mci_cclear |= S3C2410_SDICMDSTAT_CRCFAIL;
	पूर्ण

	अगर (mci_csta & S3C2410_SDICMDSTAT_RSPFIN) अणु
		अगर (host->complete_what == COMPLETION_RSPFIN) अणु
			host->status = "ok: command response received";
			जाओ बंद_transfer;
		पूर्ण

		अगर (host->complete_what == COMPLETION_XFERFINISH_RSPFIN)
			host->complete_what = COMPLETION_XFERFINISH;

		mci_cclear |= S3C2410_SDICMDSTAT_RSPFIN;
	पूर्ण

	/* errors handled after this poपूर्णांक are only relevant
	   when a data transfer is in progress */

	अगर (!cmd->data)
		जाओ clear_status_bits;

	/* Check क्रम FIFO failure */
	अगर (host->is2440) अणु
		अगर (mci_fsta & S3C2440_SDIFSTA_FIFOFAIL) अणु
			dbg(host, dbg_err, "FIFO failure\n");
			host->mrq->data->error = -EILSEQ;
			host->status = "error: 2440 fifo failure";
			जाओ fail_transfer;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (mci_dsta & S3C2410_SDIDSTA_FIFOFAIL) अणु
			dbg(host, dbg_err, "FIFO failure\n");
			cmd->data->error = -EILSEQ;
			host->status = "error:  fifo failure";
			जाओ fail_transfer;
		पूर्ण
	पूर्ण

	अगर (mci_dsta & S3C2410_SDIDSTA_RXCRCFAIL) अणु
		dbg(host, dbg_err, "bad data crc (outgoing)\n");
		cmd->data->error = -EILSEQ;
		host->status = "error: bad data crc (outgoing)";
		जाओ fail_transfer;
	पूर्ण

	अगर (mci_dsta & S3C2410_SDIDSTA_CRCFAIL) अणु
		dbg(host, dbg_err, "bad data crc (incoming)\n");
		cmd->data->error = -EILSEQ;
		host->status = "error: bad data crc (incoming)";
		जाओ fail_transfer;
	पूर्ण

	अगर (mci_dsta & S3C2410_SDIDSTA_DATATIMEOUT) अणु
		dbg(host, dbg_err, "data timeout\n");
		cmd->data->error = -ETIMEDOUT;
		host->status = "error: data timeout";
		जाओ fail_transfer;
	पूर्ण

	अगर (mci_dsta & S3C2410_SDIDSTA_XFERFINISH) अणु
		अगर (host->complete_what == COMPLETION_XFERFINISH) अणु
			host->status = "ok: data transfer completed";
			जाओ बंद_transfer;
		पूर्ण

		अगर (host->complete_what == COMPLETION_XFERFINISH_RSPFIN)
			host->complete_what = COMPLETION_RSPFIN;

		mci_dclear |= S3C2410_SDIDSTA_XFERFINISH;
	पूर्ण

clear_status_bits:
	ग_लिखोl(mci_cclear, host->base + S3C2410_SDICMDSTAT);
	ग_लिखोl(mci_dclear, host->base + S3C2410_SDIDSTA);

	जाओ irq_out;

fail_transfer:
	host->pio_active = XFER_NONE;

बंद_transfer:
	host->complete_what = COMPLETION_FINALIZE;

	clear_imask(host);
	tasklet_schedule(&host->pio_tasklet);

	जाओ irq_out;

irq_out:
	dbg(host, dbg_irq,
	    "csta:0x%08x dsta:0x%08x fsta:0x%08x dcnt:0x%08x status:%s.\n",
	    mci_csta, mci_dsta, mci_fsta, mci_dcnt, host->status);

	spin_unlock_irqrestore(&host->complete_lock, अगरlags);
	वापस IRQ_HANDLED;

पूर्ण

अटल व्योम s3cmci_dma_करोne_callback(व्योम *arg)
अणु
	काष्ठा s3cmci_host *host = arg;
	अचिन्हित दीर्घ अगरlags;

	BUG_ON(!host->mrq);
	BUG_ON(!host->mrq->data);

	spin_lock_irqsave(&host->complete_lock, अगरlags);

	dbg(host, dbg_dma, "DMA FINISHED\n");

	host->dma_complete = 1;
	host->complete_what = COMPLETION_FINALIZE;

	tasklet_schedule(&host->pio_tasklet);
	spin_unlock_irqrestore(&host->complete_lock, अगरlags);

पूर्ण

अटल व्योम finalize_request(काष्ठा s3cmci_host *host)
अणु
	काष्ठा mmc_request *mrq = host->mrq;
	काष्ठा mmc_command *cmd;
	पूर्णांक debug_as_failure = 0;

	अगर (host->complete_what != COMPLETION_FINALIZE)
		वापस;

	अगर (!mrq)
		वापस;
	cmd = host->cmd_is_stop ? mrq->stop : mrq->cmd;

	अगर (cmd->data && (cmd->error == 0) &&
	    (cmd->data->error == 0)) अणु
		अगर (s3cmci_host_usedma(host) && (!host->dma_complete)) अणु
			dbg(host, dbg_dma, "DMA Missing (%d)!\n",
			    host->dma_complete);
			वापस;
		पूर्ण
	पूर्ण

	/* Read response from controller. */
	cmd->resp[0] = पढ़ोl(host->base + S3C2410_SसूचीSP0);
	cmd->resp[1] = पढ़ोl(host->base + S3C2410_SसूचीSP1);
	cmd->resp[2] = पढ़ोl(host->base + S3C2410_SसूचीSP2);
	cmd->resp[3] = पढ़ोl(host->base + S3C2410_SसूचीSP3);

	ग_लिखोl(host->prescaler, host->base + S3C2410_SDIPRE);

	अगर (cmd->error)
		debug_as_failure = 1;

	अगर (cmd->data && cmd->data->error)
		debug_as_failure = 1;

	dbg_dumpcmd(host, cmd, debug_as_failure);

	/* Cleanup controller */
	ग_लिखोl(0, host->base + S3C2410_SDICMDARG);
	ग_लिखोl(S3C2410_SDIDCON_STOP, host->base + S3C2410_SDIDCON);
	ग_लिखोl(0, host->base + S3C2410_SDICMDCON);
	clear_imask(host);

	अगर (cmd->data && cmd->error)
		cmd->data->error = cmd->error;

	अगर (cmd->data && cmd->data->stop && (!host->cmd_is_stop)) अणु
		host->cmd_is_stop = 1;
		s3cmci_send_request(host->mmc);
		वापस;
	पूर्ण

	/* If we have no data transfer we are finished here */
	अगर (!mrq->data)
		जाओ request_करोne;

	/* Calculate the amout of bytes transfer अगर there was no error */
	अगर (mrq->data->error == 0) अणु
		mrq->data->bytes_xfered =
			(mrq->data->blocks * mrq->data->blksz);
	पूर्ण अन्यथा अणु
		mrq->data->bytes_xfered = 0;
	पूर्ण

	/* If we had an error जबतक transferring data we flush the
	 * DMA channel and the fअगरo to clear out any garbage. */
	अगर (mrq->data->error != 0) अणु
		अगर (s3cmci_host_usedma(host))
			dmaengine_terminate_all(host->dma);

		अगर (host->is2440) अणु
			/* Clear failure रेजिस्टर and reset fअगरo. */
			ग_लिखोl(S3C2440_SDIFSTA_FIFORESET |
			       S3C2440_SDIFSTA_FIFOFAIL,
			       host->base + S3C2410_SDIFSTA);
		पूर्ण अन्यथा अणु
			u32 mci_con;

			/* reset fअगरo */
			mci_con = पढ़ोl(host->base + S3C2410_SDICON);
			mci_con |= S3C2410_SDICON_FIFORESET;

			ग_लिखोl(mci_con, host->base + S3C2410_SDICON);
		पूर्ण
	पूर्ण

request_करोne:
	host->complete_what = COMPLETION_NONE;
	host->mrq = शून्य;

	s3cmci_check_sdio_irq(host);
	mmc_request_करोne(host->mmc, mrq);
पूर्ण

अटल व्योम s3cmci_send_command(काष्ठा s3cmci_host *host,
					काष्ठा mmc_command *cmd)
अणु
	u32 ccon, imsk;

	imsk  = S3C2410_SDIIMSK_CRCSTATUS | S3C2410_SDIIMSK_CMDTIMEOUT |
		S3C2410_SDIIMSK_RESPONSEND | S3C2410_SDIIMSK_CMDSENT |
		S3C2410_SDIIMSK_RESPONSECRC;

	enable_imask(host, imsk);

	अगर (cmd->data)
		host->complete_what = COMPLETION_XFERFINISH_RSPFIN;
	अन्यथा अगर (cmd->flags & MMC_RSP_PRESENT)
		host->complete_what = COMPLETION_RSPFIN;
	अन्यथा
		host->complete_what = COMPLETION_CMDSENT;

	ग_लिखोl(cmd->arg, host->base + S3C2410_SDICMDARG);

	ccon  = cmd->opcode & S3C2410_SDICMDCON_INDEX;
	ccon |= S3C2410_SDICMDCON_SENDERHOST | S3C2410_SDICMDCON_CMDSTART;

	अगर (cmd->flags & MMC_RSP_PRESENT)
		ccon |= S3C2410_SDICMDCON_WAITRSP;

	अगर (cmd->flags & MMC_RSP_136)
		ccon |= S3C2410_SDICMDCON_LONGRSP;

	ग_लिखोl(ccon, host->base + S3C2410_SDICMDCON);
पूर्ण

अटल पूर्णांक s3cmci_setup_data(काष्ठा s3cmci_host *host, काष्ठा mmc_data *data)
अणु
	u32 dcon, imsk, stoptries = 3;

	अगर ((data->blksz & 3) != 0) अणु
		/* We cannot deal with unaligned blocks with more than
		 * one block being transferred. */

		अगर (data->blocks > 1) अणु
			pr_warn("%s: can't do non-word sized block transfers (blksz %d)\n",
				__func__, data->blksz);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	जबतक (पढ़ोl(host->base + S3C2410_SDIDSTA) &
	       (S3C2410_SDIDSTA_TXDATAON | S3C2410_SDIDSTA_RXDATAON)) अणु

		dbg(host, dbg_err,
		    "mci_setup_data() transfer stillin progress.\n");

		ग_लिखोl(S3C2410_SDIDCON_STOP, host->base + S3C2410_SDIDCON);
		s3cmci_reset(host);

		अगर ((stoptries--) == 0) अणु
			dbg_dumpregs(host, "DRF");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	dcon  = data->blocks & S3C2410_SDIDCON_BLKNUM_MASK;

	अगर (s3cmci_host_usedma(host))
		dcon |= S3C2410_SDIDCON_DMAEN;

	अगर (host->bus_width == MMC_BUS_WIDTH_4)
		dcon |= S3C2410_SDIDCON_WIDEBUS;

	dcon |= S3C2410_SDIDCON_BLOCKMODE;

	अगर (data->flags & MMC_DATA_WRITE) अणु
		dcon |= S3C2410_SDIDCON_TXAFTERRESP;
		dcon |= S3C2410_SDIDCON_XFER_TXSTART;
	पूर्ण

	अगर (data->flags & MMC_DATA_READ) अणु
		dcon |= S3C2410_SDIDCON_RXAFTERCMD;
		dcon |= S3C2410_SDIDCON_XFER_RXSTART;
	पूर्ण

	अगर (host->is2440) अणु
		dcon |= S3C2440_SDIDCON_DS_WORD;
		dcon |= S3C2440_SDIDCON_DATSTART;
	पूर्ण

	ग_लिखोl(dcon, host->base + S3C2410_SDIDCON);

	/* ग_लिखो BSIZE रेजिस्टर */

	ग_लिखोl(data->blksz, host->base + S3C2410_SDIBSIZE);

	/* add to IMASK रेजिस्टर */
	imsk = S3C2410_SDIIMSK_FIFOFAIL | S3C2410_SDIIMSK_DATACRC |
	       S3C2410_SDIIMSK_DATATIMEOUT | S3C2410_SDIIMSK_DATAFINISH;

	enable_imask(host, imsk);

	/* ग_लिखो TIMER रेजिस्टर */

	अगर (host->is2440) अणु
		ग_लिखोl(0x007FFFFF, host->base + S3C2410_SDITIMER);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0x0000FFFF, host->base + S3C2410_SDITIMER);

		/* FIX: set slow घड़ी to prevent समयouts on पढ़ो */
		अगर (data->flags & MMC_DATA_READ)
			ग_लिखोl(0xFF, host->base + S3C2410_SDIPRE);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा BOTH_सूची (MMC_DATA_WRITE | MMC_DATA_READ)

अटल पूर्णांक s3cmci_prepare_pio(काष्ठा s3cmci_host *host, काष्ठा mmc_data *data)
अणु
	पूर्णांक rw = (data->flags & MMC_DATA_WRITE) ? 1 : 0;

	BUG_ON((data->flags & BOTH_सूची) == BOTH_सूची);

	host->pio_sgptr = 0;
	host->pio_bytes = 0;
	host->pio_count = 0;
	host->pio_active = rw ? XFER_WRITE : XFER_READ;

	अगर (rw) अणु
		करो_pio_ग_लिखो(host);
		enable_imask(host, S3C2410_SDIIMSK_TXFIFOHALF);
	पूर्ण अन्यथा अणु
		enable_imask(host, S3C2410_SDIIMSK_RXFIFOHALF
			     | S3C2410_SDIIMSK_RXFIFOLAST);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s3cmci_prepare_dma(काष्ठा s3cmci_host *host, काष्ठा mmc_data *data)
अणु
	पूर्णांक rw = data->flags & MMC_DATA_WRITE;
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा dma_slave_config conf = अणु
		.src_addr = host->mem->start + host->sdidata,
		.dst_addr = host->mem->start + host->sdidata,
		.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES,
		.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES,
	पूर्ण;

	BUG_ON((data->flags & BOTH_सूची) == BOTH_सूची);

	/* Restore prescaler value */
	ग_लिखोl(host->prescaler, host->base + S3C2410_SDIPRE);

	अगर (!rw)
		conf.direction = DMA_DEV_TO_MEM;
	अन्यथा
		conf.direction = DMA_MEM_TO_DEV;

	dma_map_sg(mmc_dev(host->mmc), data->sg, data->sg_len,
		   mmc_get_dma_dir(data));

	dmaengine_slave_config(host->dma, &conf);
	desc = dmaengine_prep_slave_sg(host->dma, data->sg, data->sg_len,
		conf.direction,
		DMA_CTRL_ACK | DMA_PREP_INTERRUPT);
	अगर (!desc)
		जाओ unmap_निकास;
	desc->callback = s3cmci_dma_करोne_callback;
	desc->callback_param = host;
	dmaengine_submit(desc);
	dma_async_issue_pending(host->dma);

	वापस 0;

unmap_निकास:
	dma_unmap_sg(mmc_dev(host->mmc), data->sg, data->sg_len,
		     mmc_get_dma_dir(data));
	वापस -ENOMEM;
पूर्ण

अटल व्योम s3cmci_send_request(काष्ठा mmc_host *mmc)
अणु
	काष्ठा s3cmci_host *host = mmc_priv(mmc);
	काष्ठा mmc_request *mrq = host->mrq;
	काष्ठा mmc_command *cmd = host->cmd_is_stop ? mrq->stop : mrq->cmd;

	host->ccnt++;
	prepare_dbgmsg(host, cmd, host->cmd_is_stop);

	/* Clear command, data and fअगरo status रेजिस्टरs
	   Fअगरo clear only necessary on 2440, but करोesn't hurt on 2410
	*/
	ग_लिखोl(0xFFFFFFFF, host->base + S3C2410_SDICMDSTAT);
	ग_लिखोl(0xFFFFFFFF, host->base + S3C2410_SDIDSTA);
	ग_लिखोl(0xFFFFFFFF, host->base + S3C2410_SDIFSTA);

	अगर (cmd->data) अणु
		पूर्णांक res = s3cmci_setup_data(host, cmd->data);

		host->dcnt++;

		अगर (res) अणु
			dbg(host, dbg_err, "setup data error %d\n", res);
			cmd->error = res;
			cmd->data->error = res;

			mmc_request_करोne(mmc, mrq);
			वापस;
		पूर्ण

		अगर (s3cmci_host_usedma(host))
			res = s3cmci_prepare_dma(host, cmd->data);
		अन्यथा
			res = s3cmci_prepare_pio(host, cmd->data);

		अगर (res) अणु
			dbg(host, dbg_err, "data prepare error %d\n", res);
			cmd->error = res;
			cmd->data->error = res;

			mmc_request_करोne(mmc, mrq);
			वापस;
		पूर्ण
	पूर्ण

	/* Send command */
	s3cmci_send_command(host, cmd);

	/* Enable Interrupt */
	s3cmci_enable_irq(host, true);
पूर्ण

अटल व्योम s3cmci_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा s3cmci_host *host = mmc_priv(mmc);

	host->status = "mmc request";
	host->cmd_is_stop = 0;
	host->mrq = mrq;

	अगर (mmc_gpio_get_cd(mmc) == 0) अणु
		dbg(host, dbg_err, "%s: no medium present\n", __func__);
		host->mrq->cmd->error = -ENOMEDIUM;
		mmc_request_करोne(mmc, mrq);
	पूर्ण अन्यथा
		s3cmci_send_request(mmc);
पूर्ण

अटल व्योम s3cmci_set_clk(काष्ठा s3cmci_host *host, काष्ठा mmc_ios *ios)
अणु
	u32 mci_psc;

	/* Set घड़ी */
	क्रम (mci_psc = 0; mci_psc < 255; mci_psc++) अणु
		host->real_rate = host->clk_rate / (host->clk_भाग*(mci_psc+1));

		अगर (host->real_rate <= ios->घड़ी)
			अवरोध;
	पूर्ण

	अगर (mci_psc > 255)
		mci_psc = 255;

	host->prescaler = mci_psc;
	ग_लिखोl(host->prescaler, host->base + S3C2410_SDIPRE);

	/* If requested घड़ी is 0, real_rate will be 0, too */
	अगर (ios->घड़ी == 0)
		host->real_rate = 0;
पूर्ण

अटल व्योम s3cmci_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा s3cmci_host *host = mmc_priv(mmc);
	u32 mci_con;

	/* Set the घातer state */

	mci_con = पढ़ोl(host->base + S3C2410_SDICON);

	चयन (ios->घातer_mode) अणु
	हाल MMC_POWER_ON:
	हाल MMC_POWER_UP:
		अगर (!host->is2440)
			mci_con |= S3C2410_SDICON_FIFORESET;
		अवरोध;

	हाल MMC_POWER_OFF:
	शेष:
		अगर (host->is2440)
			mci_con |= S3C2440_SDICON_SDRESET;
		अवरोध;
	पूर्ण

	अगर (host->pdata->set_घातer)
		host->pdata->set_घातer(ios->घातer_mode, ios->vdd);

	s3cmci_set_clk(host, ios);

	/* Set CLOCK_ENABLE */
	अगर (ios->घड़ी)
		mci_con |= S3C2410_SDICON_CLOCKTYPE;
	अन्यथा
		mci_con &= ~S3C2410_SDICON_CLOCKTYPE;

	ग_लिखोl(mci_con, host->base + S3C2410_SDICON);

	अगर ((ios->घातer_mode == MMC_POWER_ON) ||
	    (ios->घातer_mode == MMC_POWER_UP)) अणु
		dbg(host, dbg_conf, "running at %lukHz (requested: %ukHz).\n",
			host->real_rate/1000, ios->घड़ी/1000);
	पूर्ण अन्यथा अणु
		dbg(host, dbg_conf, "powered down.\n");
	पूर्ण

	host->bus_width = ios->bus_width;
पूर्ण

अटल व्योम s3cmci_reset(काष्ठा s3cmci_host *host)
अणु
	u32 con = पढ़ोl(host->base + S3C2410_SDICON);

	con |= S3C2440_SDICON_SDRESET;
	ग_लिखोl(con, host->base + S3C2410_SDICON);
पूर्ण

अटल व्योम s3cmci_enable_sdio_irq(काष्ठा mmc_host *mmc, पूर्णांक enable)
अणु
	काष्ठा s3cmci_host *host = mmc_priv(mmc);
	अचिन्हित दीर्घ flags;
	u32 con;

	local_irq_save(flags);

	con = पढ़ोl(host->base + S3C2410_SDICON);
	host->sdio_irqen = enable;

	अगर (enable == host->sdio_irqen)
		जाओ same_state;

	अगर (enable) अणु
		con |= S3C2410_SDICON_SDIOIRQ;
		enable_imask(host, S3C2410_SDIIMSK_SDIOIRQ);

		अगर (!host->irq_state && !host->irq_disabled) अणु
			host->irq_state = true;
			enable_irq(host->irq);
		पूर्ण
	पूर्ण अन्यथा अणु
		disable_imask(host, S3C2410_SDIIMSK_SDIOIRQ);
		con &= ~S3C2410_SDICON_SDIOIRQ;

		अगर (!host->irq_enabled && host->irq_state) अणु
			disable_irq_nosync(host->irq);
			host->irq_state = false;
		पूर्ण
	पूर्ण

	ग_लिखोl(con, host->base + S3C2410_SDICON);

 same_state:
	local_irq_restore(flags);

	s3cmci_check_sdio_irq(host);
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops s3cmci_ops = अणु
	.request	= s3cmci_request,
	.set_ios	= s3cmci_set_ios,
	.get_ro		= mmc_gpio_get_ro,
	.get_cd		= mmc_gpio_get_cd,
	.enable_sdio_irq = s3cmci_enable_sdio_irq,
पूर्ण;

#अगर_घोषित CONFIG_ARM_S3C24XX_CPUFREQ

अटल पूर्णांक s3cmci_cpufreq_transition(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा s3cmci_host *host;
	काष्ठा mmc_host *mmc;
	अचिन्हित दीर्घ newclk;
	अचिन्हित दीर्घ flags;

	host = container_of(nb, काष्ठा s3cmci_host, freq_transition);
	newclk = clk_get_rate(host->clk);
	mmc = host->mmc;

	अगर ((val == CPUFREQ_PRECHANGE && newclk > host->clk_rate) ||
	    (val == CPUFREQ_POSTCHANGE && newclk < host->clk_rate)) अणु
		spin_lock_irqsave(&mmc->lock, flags);

		host->clk_rate = newclk;

		अगर (mmc->ios.घातer_mode != MMC_POWER_OFF &&
		    mmc->ios.घड़ी != 0)
			s3cmci_set_clk(host, &mmc->ios);

		spin_unlock_irqrestore(&mmc->lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक s3cmci_cpufreq_रेजिस्टर(काष्ठा s3cmci_host *host)
अणु
	host->freq_transition.notअगरier_call = s3cmci_cpufreq_transition;

	वापस cpufreq_रेजिस्टर_notअगरier(&host->freq_transition,
					 CPUFREQ_TRANSITION_NOTIFIER);
पूर्ण

अटल अंतरभूत व्योम s3cmci_cpufreq_deरेजिस्टर(काष्ठा s3cmci_host *host)
अणु
	cpufreq_unरेजिस्टर_notअगरier(&host->freq_transition,
				    CPUFREQ_TRANSITION_NOTIFIER);
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक s3cmci_cpufreq_रेजिस्टर(काष्ठा s3cmci_host *host)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम s3cmci_cpufreq_deरेजिस्टर(काष्ठा s3cmci_host *host)
अणु
पूर्ण
#पूर्ण_अगर


#अगर_घोषित CONFIG_DEBUG_FS

अटल पूर्णांक s3cmci_state_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा s3cmci_host *host = seq->निजी;

	seq_म_लिखो(seq, "Register base = 0x%p\n", host->base);
	seq_म_लिखो(seq, "Clock rate = %ld\n", host->clk_rate);
	seq_म_लिखो(seq, "Prescale = %d\n", host->prescaler);
	seq_म_लिखो(seq, "is2440 = %d\n", host->is2440);
	seq_म_लिखो(seq, "IRQ = %d\n", host->irq);
	seq_म_लिखो(seq, "IRQ enabled = %d\n", host->irq_enabled);
	seq_म_लिखो(seq, "IRQ disabled = %d\n", host->irq_disabled);
	seq_म_लिखो(seq, "IRQ state = %d\n", host->irq_state);
	seq_म_लिखो(seq, "CD IRQ = %d\n", host->irq_cd);
	seq_म_लिखो(seq, "Do DMA = %d\n", s3cmci_host_usedma(host));
	seq_म_लिखो(seq, "SDIIMSK at %d\n", host->sdiimsk);
	seq_म_लिखो(seq, "SDIDATA at %d\n", host->sdidata);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(s3cmci_state);

#घोषणा DBG_REG(_r) अणु .addr = S3C2410_SDI##_r, .name = #_r पूर्ण

काष्ठा s3cmci_reg अणु
	अचिन्हित लघु	addr;
	अचिन्हित अक्षर	*name;
पूर्ण;

अटल स्थिर काष्ठा s3cmci_reg debug_regs[] = अणु
	DBG_REG(CON),
	DBG_REG(PRE),
	DBG_REG(CMDARG),
	DBG_REG(CMDCON),
	DBG_REG(CMDSTAT),
	DBG_REG(RSP0),
	DBG_REG(RSP1),
	DBG_REG(RSP2),
	DBG_REG(RSP3),
	DBG_REG(TIMER),
	DBG_REG(BSIZE),
	DBG_REG(DCON),
	DBG_REG(DCNT),
	DBG_REG(DSTA),
	DBG_REG(FSTA),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक s3cmci_regs_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा s3cmci_host *host = seq->निजी;
	स्थिर काष्ठा s3cmci_reg *rptr = debug_regs;

	क्रम (; rptr->name; rptr++)
		seq_म_लिखो(seq, "SDI%s\t=0x%08x\n", rptr->name,
			   पढ़ोl(host->base + rptr->addr));

	seq_म_लिखो(seq, "SDIIMSK\t=0x%08x\n", पढ़ोl(host->base + host->sdiimsk));

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(s3cmci_regs);

अटल व्योम s3cmci_debugfs_attach(काष्ठा s3cmci_host *host)
अणु
	काष्ठा device *dev = &host->pdev->dev;
	काष्ठा dentry *root;

	root = debugfs_create_dir(dev_name(dev), शून्य);
	host->debug_root = root;

	debugfs_create_file("state", 0444, root, host, &s3cmci_state_fops);
	debugfs_create_file("regs", 0444, root, host, &s3cmci_regs_fops);
पूर्ण

अटल व्योम s3cmci_debugfs_हटाओ(काष्ठा s3cmci_host *host)
अणु
	debugfs_हटाओ_recursive(host->debug_root);
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम s3cmci_debugfs_attach(काष्ठा s3cmci_host *host) अणु पूर्ण
अटल अंतरभूत व्योम s3cmci_debugfs_हटाओ(काष्ठा s3cmci_host *host) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_DEBUG_FS */

अटल पूर्णांक s3cmci_probe_pdata(काष्ठा s3cmci_host *host)
अणु
	काष्ठा platक्रमm_device *pdev = host->pdev;
	काष्ठा mmc_host *mmc = host->mmc;
	काष्ठा s3c24xx_mci_pdata *pdata;
	पूर्णांक i, ret;

	host->is2440 = platक्रमm_get_device_id(pdev)->driver_data;
	pdata = pdev->dev.platक्रमm_data;
	अगर (!pdata) अणु
		dev_err(&pdev->dev, "need platform data");
		वापस -ENXIO;
	पूर्ण

	क्रम (i = 0; i < 6; i++) अणु
		pdata->bus[i] = devm_gpiod_get_index(&pdev->dev, "bus", i,
						     GPIOD_OUT_LOW);
		अगर (IS_ERR(pdata->bus[i])) अणु
			dev_err(&pdev->dev, "failed to get gpio %d\n", i);
			वापस PTR_ERR(pdata->bus[i]);
		पूर्ण
	पूर्ण

	अगर (pdata->no_wprotect)
		mmc->caps2 |= MMC_CAP2_NO_WRITE_PROTECT;

	अगर (pdata->no_detect)
		mmc->caps |= MMC_CAP_NEEDS_POLL;

	अगर (pdata->wprotect_invert)
		mmc->caps2 |= MMC_CAP2_RO_ACTIVE_HIGH;

	/* If we get -ENOENT we have no card detect GPIO line */
	ret = mmc_gpiod_request_cd(mmc, "cd", 0, false, 0);
	अगर (ret != -ENOENT) अणु
		dev_err(&pdev->dev, "error requesting GPIO for CD %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = mmc_gpiod_request_ro(host->mmc, "wp", 0, 0);
	अगर (ret != -ENOENT) अणु
		dev_err(&pdev->dev, "error requesting GPIO for WP %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s3cmci_probe_dt(काष्ठा s3cmci_host *host)
अणु
	काष्ठा platक्रमm_device *pdev = host->pdev;
	काष्ठा s3c24xx_mci_pdata *pdata;
	काष्ठा mmc_host *mmc = host->mmc;
	पूर्णांक ret;

	host->is2440 = (दीर्घ) of_device_get_match_data(&pdev->dev);

	ret = mmc_of_parse(mmc);
	अगर (ret)
		वापस ret;

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	pdev->dev.platक्रमm_data = pdata;

	वापस 0;
पूर्ण

अटल पूर्णांक s3cmci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s3cmci_host *host;
	काष्ठा mmc_host	*mmc;
	पूर्णांक ret;

	mmc = mmc_alloc_host(माप(काष्ठा s3cmci_host), &pdev->dev);
	अगर (!mmc) अणु
		ret = -ENOMEM;
		जाओ probe_out;
	पूर्ण

	host = mmc_priv(mmc);
	host->mmc 	= mmc;
	host->pdev	= pdev;

	अगर (pdev->dev.of_node)
		ret = s3cmci_probe_dt(host);
	अन्यथा
		ret = s3cmci_probe_pdata(host);

	अगर (ret)
		जाओ probe_मुक्त_host;

	host->pdata = pdev->dev.platक्रमm_data;

	spin_lock_init(&host->complete_lock);
	tasklet_setup(&host->pio_tasklet, pio_tasklet);

	अगर (host->is2440) अणु
		host->sdiimsk	= S3C2440_SDIIMSK;
		host->sdidata	= S3C2440_SDIDATA;
		host->clk_भाग	= 1;
	पूर्ण अन्यथा अणु
		host->sdiimsk	= S3C2410_SDIIMSK;
		host->sdidata	= S3C2410_SDIDATA;
		host->clk_भाग	= 2;
	पूर्ण

	host->complete_what 	= COMPLETION_NONE;
	host->pio_active 	= XFER_NONE;

	host->mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!host->mem) अणु
		dev_err(&pdev->dev,
			"failed to get io memory region resource.\n");

		ret = -ENOENT;
		जाओ probe_मुक्त_host;
	पूर्ण

	host->mem = request_mem_region(host->mem->start,
				       resource_size(host->mem), pdev->name);

	अगर (!host->mem) अणु
		dev_err(&pdev->dev, "failed to request io memory region.\n");
		ret = -ENOENT;
		जाओ probe_मुक्त_host;
	पूर्ण

	host->base = ioremap(host->mem->start, resource_size(host->mem));
	अगर (!host->base) अणु
		dev_err(&pdev->dev, "failed to ioremap() io memory region.\n");
		ret = -EINVAL;
		जाओ probe_मुक्त_mem_region;
	पूर्ण

	host->irq = platक्रमm_get_irq(pdev, 0);
	अगर (host->irq <= 0) अणु
		ret = -EINVAL;
		जाओ probe_iounmap;
	पूर्ण

	अगर (request_irq(host->irq, s3cmci_irq, 0, DRIVER_NAME, host)) अणु
		dev_err(&pdev->dev, "failed to request mci interrupt.\n");
		ret = -ENOENT;
		जाओ probe_iounmap;
	पूर्ण

	/* We get spurious पूर्णांकerrupts even when we have set the IMSK
	 * रेजिस्टर to ignore everything, so use disable_irq() to make
	 * ensure we करोn't lock the प्रणाली with un-serviceable requests. */

	disable_irq(host->irq);
	host->irq_state = false;

	/* Depending on the dma state, get a DMA channel to use. */

	अगर (s3cmci_host_usedma(host)) अणु
		host->dma = dma_request_chan(&pdev->dev, "rx-tx");
		ret = PTR_ERR_OR_ZERO(host->dma);
		अगर (ret) अणु
			dev_err(&pdev->dev, "cannot get DMA channel.\n");
			जाओ probe_मुक्त_irq;
		पूर्ण
	पूर्ण

	host->clk = clk_get(&pdev->dev, "sdi");
	अगर (IS_ERR(host->clk)) अणु
		dev_err(&pdev->dev, "failed to find clock source.\n");
		ret = PTR_ERR(host->clk);
		host->clk = शून्य;
		जाओ probe_मुक्त_dma;
	पूर्ण

	ret = clk_prepare_enable(host->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to enable clock source.\n");
		जाओ clk_मुक्त;
	पूर्ण

	host->clk_rate = clk_get_rate(host->clk);

	mmc->ops 	= &s3cmci_ops;
	mmc->ocr_avail	= MMC_VDD_32_33 | MMC_VDD_33_34;
#अगर_घोषित CONFIG_MMC_S3C_HW_SDIO_IRQ
	mmc->caps	= MMC_CAP_4_BIT_DATA | MMC_CAP_SDIO_IRQ;
#अन्यथा
	mmc->caps	= MMC_CAP_4_BIT_DATA;
#पूर्ण_अगर
	mmc->f_min 	= host->clk_rate / (host->clk_भाग * 256);
	mmc->f_max 	= host->clk_rate / host->clk_भाग;

	अगर (host->pdata->ocr_avail)
		mmc->ocr_avail = host->pdata->ocr_avail;

	mmc->max_blk_count	= 4095;
	mmc->max_blk_size	= 4095;
	mmc->max_req_size	= 4095 * 512;
	mmc->max_seg_size	= mmc->max_req_size;

	mmc->max_segs		= 128;

	dbg(host, dbg_debug,
	    "probe: mode:%s mapped mci_base:%p irq:%u irq_cd:%u dma:%p.\n",
	    (host->is2440?"2440":""),
	    host->base, host->irq, host->irq_cd, host->dma);

	ret = s3cmci_cpufreq_रेजिस्टर(host);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register cpufreq\n");
		जाओ मुक्त_dmabuf;
	पूर्ण

	ret = mmc_add_host(mmc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to add mmc host.\n");
		जाओ मुक्त_cpufreq;
	पूर्ण

	s3cmci_debugfs_attach(host);

	platक्रमm_set_drvdata(pdev, mmc);
	dev_info(&pdev->dev, "%s - using %s, %s SDIO IRQ\n", mmc_hostname(mmc),
		 s3cmci_host_usedma(host) ? "dma" : "pio",
		 mmc->caps & MMC_CAP_SDIO_IRQ ? "hw" : "sw");

	वापस 0;

 मुक्त_cpufreq:
	s3cmci_cpufreq_deरेजिस्टर(host);

 मुक्त_dmabuf:
	clk_disable_unprepare(host->clk);

 clk_मुक्त:
	clk_put(host->clk);

 probe_मुक्त_dma:
	अगर (s3cmci_host_usedma(host))
		dma_release_channel(host->dma);

 probe_मुक्त_irq:
	मुक्त_irq(host->irq, host);

 probe_iounmap:
	iounmap(host->base);

 probe_मुक्त_mem_region:
	release_mem_region(host->mem->start, resource_size(host->mem));

 probe_मुक्त_host:
	mmc_मुक्त_host(mmc);

 probe_out:
	वापस ret;
पूर्ण

अटल व्योम s3cmci_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_host	*mmc = platक्रमm_get_drvdata(pdev);
	काष्ठा s3cmci_host *host = mmc_priv(mmc);

	अगर (host->irq_cd >= 0)
		मुक्त_irq(host->irq_cd, host);

	s3cmci_debugfs_हटाओ(host);
	s3cmci_cpufreq_deरेजिस्टर(host);
	mmc_हटाओ_host(mmc);
	clk_disable_unprepare(host->clk);
पूर्ण

अटल पूर्णांक s3cmci_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_host		*mmc  = platक्रमm_get_drvdata(pdev);
	काष्ठा s3cmci_host	*host = mmc_priv(mmc);

	s3cmci_shutकरोwn(pdev);

	clk_put(host->clk);

	tasklet_disable(&host->pio_tasklet);

	अगर (s3cmci_host_usedma(host))
		dma_release_channel(host->dma);

	मुक्त_irq(host->irq, host);

	iounmap(host->base);
	release_mem_region(host->mem->start, resource_size(host->mem));

	mmc_मुक्त_host(mmc);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id s3cmci_dt_match[] = अणु
	अणु
		.compatible = "samsung,s3c2410-sdi",
		.data = (व्योम *)0,
	पूर्ण,
	अणु
		.compatible = "samsung,s3c2412-sdi",
		.data = (व्योम *)1,
	पूर्ण,
	अणु
		.compatible = "samsung,s3c2440-sdi",
		.data = (व्योम *)1,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, s3cmci_dt_match);

अटल स्थिर काष्ठा platक्रमm_device_id s3cmci_driver_ids[] = अणु
	अणु
		.name	= "s3c2410-sdi",
		.driver_data	= 0,
	पूर्ण, अणु
		.name	= "s3c2412-sdi",
		.driver_data	= 1,
	पूर्ण, अणु
		.name	= "s3c2440-sdi",
		.driver_data	= 1,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(platक्रमm, s3cmci_driver_ids);

अटल काष्ठा platक्रमm_driver s3cmci_driver = अणु
	.driver	= अणु
		.name	= "s3c-sdi",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = s3cmci_dt_match,
	पूर्ण,
	.id_table	= s3cmci_driver_ids,
	.probe		= s3cmci_probe,
	.हटाओ		= s3cmci_हटाओ,
	.shutकरोwn	= s3cmci_shutकरोwn,
पूर्ण;

module_platक्रमm_driver(s3cmci_driver);

MODULE_DESCRIPTION("Samsung S3C MMC/SD Card Interface driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Thomas Kleffel <tk@maintech.de>, Ben Dooks <ben-linux@fluff.org>");
