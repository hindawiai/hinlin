<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/mmc/host/au1xmmc.c - AU1XX0 MMC driver
 *
 *  Copyright (c) 2005, Advanced Micro Devices, Inc.
 *
 *  Developed with help from the 2.4.30 MMC AU1XXX controller including
 *  the following copyright notices:
 *     Copyright (c) 2003-2004 Embedded Edge, LLC.
 *     Portions Copyright (C) 2002 Embedix, Inc
 *     Copyright 2002 Hewlett-Packard Company

 *  2.6 version of this driver inspired by:
 *     (drivers/mmc/wbsd.c) Copyright (C) 2004-2005 Pierre Ossman,
 *     All Rights Reserved.
 *     (drivers/mmc/pxa.c) Copyright (C) 2003 Russell King,
 *     All Rights Reserved.
 *

 */

/* Why करोn't we use the SD controllers' carddetect feature?
 *
 * From the AU1100 MMC application guide:
 * If the Au1100-based design is पूर्णांकended to support both MultiMediaCards
 * and 1- or 4-data bit SecureDigital cards, then the solution is to
 * connect a weak (560KOhm) pull-up resistor to connector pin 1.
 * In करोing so, a MMC card never enters SPI-mode communications,
 * but now the SecureDigital card-detect feature of CD/DAT3 is ineffective
 * (the low to high transition will not occur).
 */

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/leds.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mach-au1x00/au1000.h>
#समावेश <यंत्र/mach-au1x00/au1xxx_dbdma.h>
#समावेश <यंत्र/mach-au1x00/au1100_mmc.h>

#घोषणा DRIVER_NAME "au1xxx-mmc"

/* Set this to enable special debugging macros */
/* #घोषणा DEBUG */

#अगर_घोषित DEBUG
#घोषणा DBG(fmt, idx, args...)	\
	pr_debug("au1xmmc(%d): DEBUG: " fmt, idx, ##args)
#अन्यथा
#घोषणा DBG(fmt, idx, args...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/* Hardware definitions */
#घोषणा AU1XMMC_DESCRIPTOR_COUNT 1

/* max DMA seg size: 64KB on Au1100, 4MB on Au1200 */
#घोषणा AU1100_MMC_DESCRIPTOR_SIZE 0x0000ffff
#घोषणा AU1200_MMC_DESCRIPTOR_SIZE 0x003fffff

#घोषणा AU1XMMC_OCR (MMC_VDD_27_28 | MMC_VDD_28_29 | MMC_VDD_29_30 | \
		     MMC_VDD_30_31 | MMC_VDD_31_32 | MMC_VDD_32_33 | \
		     MMC_VDD_33_34 | MMC_VDD_34_35 | MMC_VDD_35_36)

/* This gives us a hard value क्रम the stop command that we can ग_लिखो directly
 * to the command रेजिस्टर.
 */
#घोषणा STOP_CMD	\
	(SD_CMD_RT_1B | SD_CMD_CT_7 | (0xC << SD_CMD_CI_SHIFT) | SD_CMD_GO)

/* This is the set of पूर्णांकerrupts that we configure by शेष. */
#घोषणा AU1XMMC_INTERRUPTS 				\
	(SD_CONFIG_SC | SD_CONFIG_DT | SD_CONFIG_RAT |	\
	 SD_CONFIG_CR | SD_CONFIG_I)

/* The poll event (looking क्रम insert/हटाओ events runs twice a second. */
#घोषणा AU1XMMC_DETECT_TIMEOUT (HZ/2)

काष्ठा au1xmmc_host अणु
	काष्ठा mmc_host *mmc;
	काष्ठा mmc_request *mrq;

	u32 flags;
	व्योम __iomem *iobase;
	u32 घड़ी;
	u32 bus_width;
	u32 घातer_mode;

	पूर्णांक status;

	काष्ठा अणु
		पूर्णांक len;
		पूर्णांक dir;
	पूर्ण dma;

	काष्ठा अणु
		पूर्णांक index;
		पूर्णांक offset;
		पूर्णांक len;
	पूर्ण pio;

	u32 tx_chan;
	u32 rx_chan;

	पूर्णांक irq;

	काष्ठा tasklet_काष्ठा finish_task;
	काष्ठा tasklet_काष्ठा data_task;
	काष्ठा au1xmmc_platक्रमm_data *platdata;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा resource *ioarea;
	काष्ठा clk *clk;
पूर्ण;

/* Status flags used by the host काष्ठाure */
#घोषणा HOST_F_XMIT	0x0001
#घोषणा HOST_F_RECV	0x0002
#घोषणा HOST_F_DMA	0x0010
#घोषणा HOST_F_DBDMA	0x0020
#घोषणा HOST_F_ACTIVE	0x0100
#घोषणा HOST_F_STOP	0x1000

#घोषणा HOST_S_IDLE	0x0001
#घोषणा HOST_S_CMD	0x0002
#घोषणा HOST_S_DATA	0x0003
#घोषणा HOST_S_STOP	0x0004

/* Easy access macros */
#घोषणा HOST_STATUS(h)	((h)->iobase + SD_STATUS)
#घोषणा HOST_CONFIG(h)	((h)->iobase + SD_CONFIG)
#घोषणा HOST_ENABLE(h)	((h)->iobase + SD_ENABLE)
#घोषणा HOST_TXPORT(h)	((h)->iobase + SD_TXPORT)
#घोषणा HOST_RXPORT(h)	((h)->iobase + SD_RXPORT)
#घोषणा HOST_CMDARG(h)	((h)->iobase + SD_CMDARG)
#घोषणा HOST_BLKSIZE(h)	((h)->iobase + SD_BLKSIZE)
#घोषणा HOST_CMD(h)	((h)->iobase + SD_CMD)
#घोषणा HOST_CONFIG2(h)	((h)->iobase + SD_CONFIG2)
#घोषणा HOST_TIMEOUT(h)	((h)->iobase + SD_TIMEOUT)
#घोषणा HOST_DEBUG(h)	((h)->iobase + SD_DEBUG)

#घोषणा DMA_CHANNEL(h)	\
	(((h)->flags & HOST_F_XMIT) ? (h)->tx_chan : (h)->rx_chan)

अटल अंतरभूत पूर्णांक has_dbdma(व्योम)
अणु
	चयन (alchemy_get_cputype()) अणु
	हाल ALCHEMY_CPU_AU1200:
	हाल ALCHEMY_CPU_AU1300:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम IRQ_ON(काष्ठा au1xmmc_host *host, u32 mask)
अणु
	u32 val = __raw_पढ़ोl(HOST_CONFIG(host));
	val |= mask;
	__raw_ग_लिखोl(val, HOST_CONFIG(host));
	wmb(); /* drain ग_लिखोbuffer */
पूर्ण

अटल अंतरभूत व्योम FLUSH_FIFO(काष्ठा au1xmmc_host *host)
अणु
	u32 val = __raw_पढ़ोl(HOST_CONFIG2(host));

	__raw_ग_लिखोl(val | SD_CONFIG2_FF, HOST_CONFIG2(host));
	wmb(); /* drain ग_लिखोbuffer */
	mdelay(1);

	/* SEND_STOP will turn off घड़ी control - this re-enables it */
	val &= ~SD_CONFIG2_DF;

	__raw_ग_लिखोl(val, HOST_CONFIG2(host));
	wmb(); /* drain ग_लिखोbuffer */
पूर्ण

अटल अंतरभूत व्योम IRQ_OFF(काष्ठा au1xmmc_host *host, u32 mask)
अणु
	u32 val = __raw_पढ़ोl(HOST_CONFIG(host));
	val &= ~mask;
	__raw_ग_लिखोl(val, HOST_CONFIG(host));
	wmb(); /* drain ग_लिखोbuffer */
पूर्ण

अटल अंतरभूत व्योम SEND_STOP(काष्ठा au1xmmc_host *host)
अणु
	u32 config2;

	WARN_ON(host->status != HOST_S_DATA);
	host->status = HOST_S_STOP;

	config2 = __raw_पढ़ोl(HOST_CONFIG2(host));
	__raw_ग_लिखोl(config2 | SD_CONFIG2_DF, HOST_CONFIG2(host));
	wmb(); /* drain ग_लिखोbuffer */

	/* Send the stop command */
	__raw_ग_लिखोl(STOP_CMD, HOST_CMD(host));
	wmb(); /* drain ग_लिखोbuffer */
पूर्ण

अटल व्योम au1xmmc_set_घातer(काष्ठा au1xmmc_host *host, पूर्णांक state)
अणु
	अगर (host->platdata && host->platdata->set_घातer)
		host->platdata->set_घातer(host->mmc, state);
पूर्ण

अटल पूर्णांक au1xmmc_card_inserted(काष्ठा mmc_host *mmc)
अणु
	काष्ठा au1xmmc_host *host = mmc_priv(mmc);

	अगर (host->platdata && host->platdata->card_inserted)
		वापस !!host->platdata->card_inserted(host->mmc);

	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक au1xmmc_card_पढ़ोonly(काष्ठा mmc_host *mmc)
अणु
	काष्ठा au1xmmc_host *host = mmc_priv(mmc);

	अगर (host->platdata && host->platdata->card_पढ़ोonly)
		वापस !!host->platdata->card_पढ़ोonly(mmc);

	वापस -ENOSYS;
पूर्ण

अटल व्योम au1xmmc_finish_request(काष्ठा au1xmmc_host *host)
अणु
	काष्ठा mmc_request *mrq = host->mrq;

	host->mrq = शून्य;
	host->flags &= HOST_F_ACTIVE | HOST_F_DMA;

	host->dma.len = 0;
	host->dma.dir = 0;

	host->pio.index  = 0;
	host->pio.offset = 0;
	host->pio.len = 0;

	host->status = HOST_S_IDLE;

	mmc_request_करोne(host->mmc, mrq);
पूर्ण

अटल व्योम au1xmmc_tasklet_finish(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा au1xmmc_host *host = from_tasklet(host, t, finish_task);
	au1xmmc_finish_request(host);
पूर्ण

अटल पूर्णांक au1xmmc_send_command(काष्ठा au1xmmc_host *host,
				काष्ठा mmc_command *cmd, काष्ठा mmc_data *data)
अणु
	u32 mmccmd = (cmd->opcode << SD_CMD_CI_SHIFT);

	चयन (mmc_resp_type(cmd)) अणु
	हाल MMC_RSP_NONE:
		अवरोध;
	हाल MMC_RSP_R1:
		mmccmd |= SD_CMD_RT_1;
		अवरोध;
	हाल MMC_RSP_R1B:
		mmccmd |= SD_CMD_RT_1B;
		अवरोध;
	हाल MMC_RSP_R2:
		mmccmd |= SD_CMD_RT_2;
		अवरोध;
	हाल MMC_RSP_R3:
		mmccmd |= SD_CMD_RT_3;
		अवरोध;
	शेष:
		pr_info("au1xmmc: unhandled response type %02x\n",
			mmc_resp_type(cmd));
		वापस -EINVAL;
	पूर्ण

	अगर (data) अणु
		अगर (data->flags & MMC_DATA_READ) अणु
			अगर (data->blocks > 1)
				mmccmd |= SD_CMD_CT_4;
			अन्यथा
				mmccmd |= SD_CMD_CT_2;
		पूर्ण अन्यथा अगर (data->flags & MMC_DATA_WRITE) अणु
			अगर (data->blocks > 1)
				mmccmd |= SD_CMD_CT_3;
			अन्यथा
				mmccmd |= SD_CMD_CT_1;
		पूर्ण
	पूर्ण

	__raw_ग_लिखोl(cmd->arg, HOST_CMDARG(host));
	wmb(); /* drain ग_लिखोbuffer */

	__raw_ग_लिखोl((mmccmd | SD_CMD_GO), HOST_CMD(host));
	wmb(); /* drain ग_लिखोbuffer */

	/* Wait क्रम the command to go on the line */
	जबतक (__raw_पढ़ोl(HOST_CMD(host)) & SD_CMD_GO)
		/* nop */;

	वापस 0;
पूर्ण

अटल व्योम au1xmmc_data_complete(काष्ठा au1xmmc_host *host, u32 status)
अणु
	काष्ठा mmc_request *mrq = host->mrq;
	काष्ठा mmc_data *data;
	u32 crc;

	WARN_ON((host->status != HOST_S_DATA) && (host->status != HOST_S_STOP));

	अगर (host->mrq == शून्य)
		वापस;

	data = mrq->cmd->data;

	अगर (status == 0)
		status = __raw_पढ़ोl(HOST_STATUS(host));

	/* The transaction is really over when the SD_STATUS_DB bit is clear */
	जबतक ((host->flags & HOST_F_XMIT) && (status & SD_STATUS_DB))
		status = __raw_पढ़ोl(HOST_STATUS(host));

	data->error = 0;
	dma_unmap_sg(mmc_dev(host->mmc), data->sg, data->sg_len, host->dma.dir);

        /* Process any errors */
	crc = (status & (SD_STATUS_WC | SD_STATUS_RC));
	अगर (host->flags & HOST_F_XMIT)
		crc |= ((status & 0x07) == 0x02) ? 0 : 1;

	अगर (crc)
		data->error = -EILSEQ;

	/* Clear the CRC bits */
	__raw_ग_लिखोl(SD_STATUS_WC | SD_STATUS_RC, HOST_STATUS(host));

	data->bytes_xfered = 0;

	अगर (!data->error) अणु
		अगर (host->flags & (HOST_F_DMA | HOST_F_DBDMA)) अणु
			u32 chan = DMA_CHANNEL(host);

			chan_tab_t *c = *((chan_tab_t **)chan);
			au1x_dma_chan_t *cp = c->chan_ptr;
			data->bytes_xfered = cp->ddma_bytecnt;
		पूर्ण अन्यथा
			data->bytes_xfered =
				(data->blocks * data->blksz) - host->pio.len;
	पूर्ण

	au1xmmc_finish_request(host);
पूर्ण

अटल व्योम au1xmmc_tasklet_data(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा au1xmmc_host *host = from_tasklet(host, t, data_task);

	u32 status = __raw_पढ़ोl(HOST_STATUS(host));
	au1xmmc_data_complete(host, status);
पूर्ण

#घोषणा AU1XMMC_MAX_TRANSFER 8

अटल व्योम au1xmmc_send_pio(काष्ठा au1xmmc_host *host)
अणु
	काष्ठा mmc_data *data;
	पूर्णांक sg_len, max, count;
	अचिन्हित अक्षर *sg_ptr, val;
	u32 status;
	काष्ठा scatterlist *sg;

	data = host->mrq->data;

	अगर (!(host->flags & HOST_F_XMIT))
		वापस;

	/* This is the poपूर्णांकer to the data buffer */
	sg = &data->sg[host->pio.index];
	sg_ptr = kmap_atomic(sg_page(sg)) + sg->offset + host->pio.offset;

	/* This is the space left inside the buffer */
	sg_len = data->sg[host->pio.index].length - host->pio.offset;

	/* Check अगर we need less than the size of the sg_buffer */
	max = (sg_len > host->pio.len) ? host->pio.len : sg_len;
	अगर (max > AU1XMMC_MAX_TRANSFER)
		max = AU1XMMC_MAX_TRANSFER;

	क्रम (count = 0; count < max; count++) अणु
		status = __raw_पढ़ोl(HOST_STATUS(host));

		अगर (!(status & SD_STATUS_TH))
			अवरोध;

		val = sg_ptr[count];

		__raw_ग_लिखोl((अचिन्हित दीर्घ)val, HOST_TXPORT(host));
		wmb(); /* drain ग_लिखोbuffer */
	पूर्ण
	kunmap_atomic(sg_ptr);

	host->pio.len -= count;
	host->pio.offset += count;

	अगर (count == sg_len) अणु
		host->pio.index++;
		host->pio.offset = 0;
	पूर्ण

	अगर (host->pio.len == 0) अणु
		IRQ_OFF(host, SD_CONFIG_TH);

		अगर (host->flags & HOST_F_STOP)
			SEND_STOP(host);

		tasklet_schedule(&host->data_task);
	पूर्ण
पूर्ण

अटल व्योम au1xmmc_receive_pio(काष्ठा au1xmmc_host *host)
अणु
	काष्ठा mmc_data *data;
	पूर्णांक max, count, sg_len = 0;
	अचिन्हित अक्षर *sg_ptr = शून्य;
	u32 status, val;
	काष्ठा scatterlist *sg;

	data = host->mrq->data;

	अगर (!(host->flags & HOST_F_RECV))
		वापस;

	max = host->pio.len;

	अगर (host->pio.index < host->dma.len) अणु
		sg = &data->sg[host->pio.index];
		sg_ptr = kmap_atomic(sg_page(sg)) + sg->offset + host->pio.offset;

		/* This is the space left inside the buffer */
		sg_len = sg_dma_len(&data->sg[host->pio.index]) - host->pio.offset;

		/* Check अगर we need less than the size of the sg_buffer */
		अगर (sg_len < max)
			max = sg_len;
	पूर्ण

	अगर (max > AU1XMMC_MAX_TRANSFER)
		max = AU1XMMC_MAX_TRANSFER;

	क्रम (count = 0; count < max; count++) अणु
		status = __raw_पढ़ोl(HOST_STATUS(host));

		अगर (!(status & SD_STATUS_NE))
			अवरोध;

		अगर (status & SD_STATUS_RC) अणु
			DBG("RX CRC Error [%d + %d].\n", host->pdev->id,
					host->pio.len, count);
			अवरोध;
		पूर्ण

		अगर (status & SD_STATUS_RO) अणु
			DBG("RX Overrun [%d + %d]\n", host->pdev->id,
					host->pio.len, count);
			अवरोध;
		पूर्ण
		अन्यथा अगर (status & SD_STATUS_RU) अणु
			DBG("RX Underrun [%d + %d]\n", host->pdev->id,
					host->pio.len,	count);
			अवरोध;
		पूर्ण

		val = __raw_पढ़ोl(HOST_RXPORT(host));

		अगर (sg_ptr)
			sg_ptr[count] = (अचिन्हित अक्षर)(val & 0xFF);
	पूर्ण
	अगर (sg_ptr)
		kunmap_atomic(sg_ptr);

	host->pio.len -= count;
	host->pio.offset += count;

	अगर (sg_len && count == sg_len) अणु
		host->pio.index++;
		host->pio.offset = 0;
	पूर्ण

	अगर (host->pio.len == 0) अणु
		/* IRQ_OFF(host, SD_CONFIG_RA | SD_CONFIG_RF); */
		IRQ_OFF(host, SD_CONFIG_NE);

		अगर (host->flags & HOST_F_STOP)
			SEND_STOP(host);

		tasklet_schedule(&host->data_task);
	पूर्ण
पूर्ण

/* This is called when a command has been completed - grab the response
 * and check क्रम errors.  Then start the data transfer अगर it is indicated.
 */
अटल व्योम au1xmmc_cmd_complete(काष्ठा au1xmmc_host *host, u32 status)
अणु
	काष्ठा mmc_request *mrq = host->mrq;
	काष्ठा mmc_command *cmd;
	u32 r[4];
	पूर्णांक i, trans;

	अगर (!host->mrq)
		वापस;

	cmd = mrq->cmd;
	cmd->error = 0;

	अगर (cmd->flags & MMC_RSP_PRESENT) अणु
		अगर (cmd->flags & MMC_RSP_136) अणु
			r[0] = __raw_पढ़ोl(host->iobase + SD_RESP3);
			r[1] = __raw_पढ़ोl(host->iobase + SD_RESP2);
			r[2] = __raw_पढ़ोl(host->iobase + SD_RESP1);
			r[3] = __raw_पढ़ोl(host->iobase + SD_RESP0);

			/* The CRC is omitted from the response, so really
			 * we only got 120 bytes, but the engine expects
			 * 128 bits, so we have to shअगरt things up.
			 */
			क्रम (i = 0; i < 4; i++) अणु
				cmd->resp[i] = (r[i] & 0x00FFFFFF) << 8;
				अगर (i != 3)
					cmd->resp[i] |= (r[i + 1] & 0xFF000000) >> 24;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Techincally, we should be getting all 48 bits of
			 * the response (SD_RESP1 + SD_RESP2), but because
			 * our response omits the CRC, our data ends up
			 * being shअगरted 8 bits to the right.  In this हाल,
			 * that means that the OSR data starts at bit 31,
			 * so we can just पढ़ो RESP0 and वापस that.
			 */
			cmd->resp[0] = __raw_पढ़ोl(host->iobase + SD_RESP0);
		पूर्ण
	पूर्ण

        /* Figure out errors */
	अगर (status & (SD_STATUS_SC | SD_STATUS_WC | SD_STATUS_RC))
		cmd->error = -EILSEQ;

	trans = host->flags & (HOST_F_XMIT | HOST_F_RECV);

	अगर (!trans || cmd->error) अणु
		IRQ_OFF(host, SD_CONFIG_TH | SD_CONFIG_RA | SD_CONFIG_RF);
		tasklet_schedule(&host->finish_task);
		वापस;
	पूर्ण

	host->status = HOST_S_DATA;

	अगर ((host->flags & (HOST_F_DMA | HOST_F_DBDMA))) अणु
		u32 channel = DMA_CHANNEL(host);

		/* Start the DBDMA as soon as the buffer माला_लो something in it */

		अगर (host->flags & HOST_F_RECV) अणु
			u32 mask = SD_STATUS_DB | SD_STATUS_NE;

			जबतक((status & mask) != mask)
				status = __raw_पढ़ोl(HOST_STATUS(host));
		पूर्ण

		au1xxx_dbdma_start(channel);
	पूर्ण
पूर्ण

अटल व्योम au1xmmc_set_घड़ी(काष्ठा au1xmmc_host *host, पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक pbus = clk_get_rate(host->clk);
	अचिन्हित पूर्णांक भागisor = ((pbus / rate) / 2) - 1;
	u32 config;

	config = __raw_पढ़ोl(HOST_CONFIG(host));

	config &= ~(SD_CONFIG_DIV);
	config |= (भागisor & SD_CONFIG_DIV) | SD_CONFIG_DE;

	__raw_ग_लिखोl(config, HOST_CONFIG(host));
	wmb(); /* drain ग_लिखोbuffer */
पूर्ण

अटल पूर्णांक au1xmmc_prepare_data(काष्ठा au1xmmc_host *host,
				काष्ठा mmc_data *data)
अणु
	पूर्णांक datalen = data->blocks * data->blksz;

	अगर (data->flags & MMC_DATA_READ)
		host->flags |= HOST_F_RECV;
	अन्यथा
		host->flags |= HOST_F_XMIT;

	अगर (host->mrq->stop)
		host->flags |= HOST_F_STOP;

	host->dma.dir = DMA_BIसूचीECTIONAL;

	host->dma.len = dma_map_sg(mmc_dev(host->mmc), data->sg,
				   data->sg_len, host->dma.dir);

	अगर (host->dma.len == 0)
		वापस -ETIMEDOUT;

	__raw_ग_लिखोl(data->blksz - 1, HOST_BLKSIZE(host));

	अगर (host->flags & (HOST_F_DMA | HOST_F_DBDMA)) अणु
		पूर्णांक i;
		u32 channel = DMA_CHANNEL(host);

		au1xxx_dbdma_stop(channel);

		क्रम (i = 0; i < host->dma.len; i++) अणु
			u32 ret = 0, flags = DDMA_FLAGS_NOIE;
			काष्ठा scatterlist *sg = &data->sg[i];
			पूर्णांक sg_len = sg->length;

			पूर्णांक len = (datalen > sg_len) ? sg_len : datalen;

			अगर (i == host->dma.len - 1)
				flags = DDMA_FLAGS_IE;

			अगर (host->flags & HOST_F_XMIT) अणु
				ret = au1xxx_dbdma_put_source(channel,
					sg_phys(sg), len, flags);
			पूर्ण अन्यथा अणु
				ret = au1xxx_dbdma_put_dest(channel,
					sg_phys(sg), len, flags);
			पूर्ण

			अगर (!ret)
				जाओ dataerr;

			datalen -= len;
		पूर्ण
	पूर्ण अन्यथा अणु
		host->pio.index = 0;
		host->pio.offset = 0;
		host->pio.len = datalen;

		अगर (host->flags & HOST_F_XMIT)
			IRQ_ON(host, SD_CONFIG_TH);
		अन्यथा
			IRQ_ON(host, SD_CONFIG_NE);
			/* IRQ_ON(host, SD_CONFIG_RA | SD_CONFIG_RF); */
	पूर्ण

	वापस 0;

dataerr:
	dma_unmap_sg(mmc_dev(host->mmc), data->sg, data->sg_len,
			host->dma.dir);
	वापस -ETIMEDOUT;
पूर्ण

/* This actually starts a command or data transaction */
अटल व्योम au1xmmc_request(काष्ठा mmc_host* mmc, काष्ठा mmc_request* mrq)
अणु
	काष्ठा au1xmmc_host *host = mmc_priv(mmc);
	पूर्णांक ret = 0;

	WARN_ON(irqs_disabled());
	WARN_ON(host->status != HOST_S_IDLE);

	host->mrq = mrq;
	host->status = HOST_S_CMD;

	/* fail request immediately अगर no card is present */
	अगर (0 == au1xmmc_card_inserted(mmc)) अणु
		mrq->cmd->error = -ENOMEDIUM;
		au1xmmc_finish_request(host);
		वापस;
	पूर्ण

	अगर (mrq->data) अणु
		FLUSH_FIFO(host);
		ret = au1xmmc_prepare_data(host, mrq->data);
	पूर्ण

	अगर (!ret)
		ret = au1xmmc_send_command(host, mrq->cmd, mrq->data);

	अगर (ret) अणु
		mrq->cmd->error = ret;
		au1xmmc_finish_request(host);
	पूर्ण
पूर्ण

अटल व्योम au1xmmc_reset_controller(काष्ठा au1xmmc_host *host)
अणु
	/* Apply the घड़ी */
	__raw_ग_लिखोl(SD_ENABLE_CE, HOST_ENABLE(host));
	wmb(); /* drain ग_लिखोbuffer */
	mdelay(1);

	__raw_ग_लिखोl(SD_ENABLE_R | SD_ENABLE_CE, HOST_ENABLE(host));
	wmb(); /* drain ग_लिखोbuffer */
	mdelay(5);

	__raw_ग_लिखोl(~0, HOST_STATUS(host));
	wmb(); /* drain ग_लिखोbuffer */

	__raw_ग_लिखोl(0, HOST_BLKSIZE(host));
	__raw_ग_लिखोl(0x001fffff, HOST_TIMEOUT(host));
	wmb(); /* drain ग_लिखोbuffer */

	__raw_ग_लिखोl(SD_CONFIG2_EN, HOST_CONFIG2(host));
	wmb(); /* drain ग_लिखोbuffer */

	__raw_ग_लिखोl(SD_CONFIG2_EN | SD_CONFIG2_FF, HOST_CONFIG2(host));
	wmb(); /* drain ग_लिखोbuffer */
	mdelay(1);

	__raw_ग_लिखोl(SD_CONFIG2_EN, HOST_CONFIG2(host));
	wmb(); /* drain ग_लिखोbuffer */

	/* Configure पूर्णांकerrupts */
	__raw_ग_लिखोl(AU1XMMC_INTERRUPTS, HOST_CONFIG(host));
	wmb(); /* drain ग_लिखोbuffer */
पूर्ण


अटल व्योम au1xmmc_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा au1xmmc_host *host = mmc_priv(mmc);
	u32 config2;

	अगर (ios->घातer_mode == MMC_POWER_OFF)
		au1xmmc_set_घातer(host, 0);
	अन्यथा अगर (ios->घातer_mode == MMC_POWER_ON) अणु
		au1xmmc_set_घातer(host, 1);
	पूर्ण

	अगर (ios->घड़ी && ios->घड़ी != host->घड़ी) अणु
		au1xmmc_set_घड़ी(host, ios->घड़ी);
		host->घड़ी = ios->घड़ी;
	पूर्ण

	config2 = __raw_पढ़ोl(HOST_CONFIG2(host));
	चयन (ios->bus_width) अणु
	हाल MMC_BUS_WIDTH_8:
		config2 |= SD_CONFIG2_BB;
		अवरोध;
	हाल MMC_BUS_WIDTH_4:
		config2 &= ~SD_CONFIG2_BB;
		config2 |= SD_CONFIG2_WB;
		अवरोध;
	हाल MMC_BUS_WIDTH_1:
		config2 &= ~(SD_CONFIG2_WB | SD_CONFIG2_BB);
		अवरोध;
	पूर्ण
	__raw_ग_लिखोl(config2, HOST_CONFIG2(host));
	wmb(); /* drain ग_लिखोbuffer */
पूर्ण

#घोषणा STATUS_TIMEOUT (SD_STATUS_RAT | SD_STATUS_DT)
#घोषणा STATUS_DATA_IN  (SD_STATUS_NE)
#घोषणा STATUS_DATA_OUT (SD_STATUS_TH)

अटल irqवापस_t au1xmmc_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा au1xmmc_host *host = dev_id;
	u32 status;

	status = __raw_पढ़ोl(HOST_STATUS(host));

	अगर (!(status & SD_STATUS_I))
		वापस IRQ_NONE;	/* not ours */

	अगर (status & SD_STATUS_SI)	/* SDIO */
		mmc_संकेत_sdio_irq(host->mmc);

	अगर (host->mrq && (status & STATUS_TIMEOUT)) अणु
		अगर (status & SD_STATUS_RAT)
			host->mrq->cmd->error = -ETIMEDOUT;
		अन्यथा अगर (status & SD_STATUS_DT)
			host->mrq->data->error = -ETIMEDOUT;

		/* In PIO mode, पूर्णांकerrupts might still be enabled */
		IRQ_OFF(host, SD_CONFIG_NE | SD_CONFIG_TH);

		/* IRQ_OFF(host, SD_CONFIG_TH | SD_CONFIG_RA | SD_CONFIG_RF); */
		tasklet_schedule(&host->finish_task);
	पूर्ण
#अगर 0
	अन्यथा अगर (status & SD_STATUS_DD) अणु
		/* Someबार we get a DD beक्रमe a NE in PIO mode */
		अगर (!(host->flags & HOST_F_DMA) && (status & SD_STATUS_NE))
			au1xmmc_receive_pio(host);
		अन्यथा अणु
			au1xmmc_data_complete(host, status);
			/* tasklet_schedule(&host->data_task); */
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	अन्यथा अगर (status & SD_STATUS_CR) अणु
		अगर (host->status == HOST_S_CMD)
			au1xmmc_cmd_complete(host, status);

	पूर्ण अन्यथा अगर (!(host->flags & HOST_F_DMA)) अणु
		अगर ((host->flags & HOST_F_XMIT) && (status & STATUS_DATA_OUT))
			au1xmmc_send_pio(host);
		अन्यथा अगर ((host->flags & HOST_F_RECV) && (status & STATUS_DATA_IN))
			au1xmmc_receive_pio(host);

	पूर्ण अन्यथा अगर (status & 0x203F3C70) अणु
			DBG("Unhandled status %8.8x\n", host->pdev->id,
				status);
	पूर्ण

	__raw_ग_लिखोl(status, HOST_STATUS(host));
	wmb(); /* drain ग_लिखोbuffer */

	वापस IRQ_HANDLED;
पूर्ण

/* 8bit memory DMA device */
अटल dbdev_tab_t au1xmmc_mem_dbdev = अणु
	.dev_id		= DSCR_CMD0_ALWAYS,
	.dev_flags	= DEV_FLAGS_ANYUSE,
	.dev_tsize	= 0,
	.dev_devwidth	= 8,
	.dev_physaddr	= 0x00000000,
	.dev_पूर्णांकlevel	= 0,
	.dev_पूर्णांकpolarity = 0,
पूर्ण;
अटल पूर्णांक memid;

अटल व्योम au1xmmc_dbdma_callback(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा au1xmmc_host *host = (काष्ठा au1xmmc_host *)dev_id;

	/* Aव्योम spurious पूर्णांकerrupts */
	अगर (!host->mrq)
		वापस;

	अगर (host->flags & HOST_F_STOP)
		SEND_STOP(host);

	tasklet_schedule(&host->data_task);
पूर्ण

अटल पूर्णांक au1xmmc_dbdma_init(काष्ठा au1xmmc_host *host)
अणु
	काष्ठा resource *res;
	पूर्णांक txid, rxid;

	res = platक्रमm_get_resource(host->pdev, IORESOURCE_DMA, 0);
	अगर (!res)
		वापस -ENODEV;
	txid = res->start;

	res = platक्रमm_get_resource(host->pdev, IORESOURCE_DMA, 1);
	अगर (!res)
		वापस -ENODEV;
	rxid = res->start;

	अगर (!memid)
		वापस -ENODEV;

	host->tx_chan = au1xxx_dbdma_chan_alloc(memid, txid,
				au1xmmc_dbdma_callback, (व्योम *)host);
	अगर (!host->tx_chan) अणु
		dev_err(&host->pdev->dev, "cannot allocate TX DMA\n");
		वापस -ENODEV;
	पूर्ण

	host->rx_chan = au1xxx_dbdma_chan_alloc(rxid, memid,
				au1xmmc_dbdma_callback, (व्योम *)host);
	अगर (!host->rx_chan) अणु
		dev_err(&host->pdev->dev, "cannot allocate RX DMA\n");
		au1xxx_dbdma_chan_मुक्त(host->tx_chan);
		वापस -ENODEV;
	पूर्ण

	au1xxx_dbdma_set_devwidth(host->tx_chan, 8);
	au1xxx_dbdma_set_devwidth(host->rx_chan, 8);

	au1xxx_dbdma_ring_alloc(host->tx_chan, AU1XMMC_DESCRIPTOR_COUNT);
	au1xxx_dbdma_ring_alloc(host->rx_chan, AU1XMMC_DESCRIPTOR_COUNT);

	/* DBDMA is good to go */
	host->flags |= HOST_F_DMA | HOST_F_DBDMA;

	वापस 0;
पूर्ण

अटल व्योम au1xmmc_dbdma_shutकरोwn(काष्ठा au1xmmc_host *host)
अणु
	अगर (host->flags & HOST_F_DMA) अणु
		host->flags &= ~HOST_F_DMA;
		au1xxx_dbdma_chan_मुक्त(host->tx_chan);
		au1xxx_dbdma_chan_मुक्त(host->rx_chan);
	पूर्ण
पूर्ण

अटल व्योम au1xmmc_enable_sdio_irq(काष्ठा mmc_host *mmc, पूर्णांक en)
अणु
	काष्ठा au1xmmc_host *host = mmc_priv(mmc);

	अगर (en)
		IRQ_ON(host, SD_CONFIG_SI);
	अन्यथा
		IRQ_OFF(host, SD_CONFIG_SI);
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops au1xmmc_ops = अणु
	.request	= au1xmmc_request,
	.set_ios	= au1xmmc_set_ios,
	.get_ro		= au1xmmc_card_पढ़ोonly,
	.get_cd		= au1xmmc_card_inserted,
	.enable_sdio_irq = au1xmmc_enable_sdio_irq,
पूर्ण;

अटल पूर्णांक au1xmmc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_host *mmc;
	काष्ठा au1xmmc_host *host;
	काष्ठा resource *r;
	पूर्णांक ret, अगरlag;

	mmc = mmc_alloc_host(माप(काष्ठा au1xmmc_host), &pdev->dev);
	अगर (!mmc) अणु
		dev_err(&pdev->dev, "no memory for mmc_host\n");
		ret = -ENOMEM;
		जाओ out0;
	पूर्ण

	host = mmc_priv(mmc);
	host->mmc = mmc;
	host->platdata = pdev->dev.platक्रमm_data;
	host->pdev = pdev;

	ret = -ENODEV;
	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r) अणु
		dev_err(&pdev->dev, "no mmio defined\n");
		जाओ out1;
	पूर्ण

	host->ioarea = request_mem_region(r->start, resource_size(r),
					   pdev->name);
	अगर (!host->ioarea) अणु
		dev_err(&pdev->dev, "mmio already in use\n");
		जाओ out1;
	पूर्ण

	host->iobase = ioremap(r->start, 0x3c);
	अगर (!host->iobase) अणु
		dev_err(&pdev->dev, "cannot remap mmio\n");
		जाओ out2;
	पूर्ण

	host->irq = platक्रमm_get_irq(pdev, 0);
	अगर (host->irq < 0)
		जाओ out3;

	mmc->ops = &au1xmmc_ops;

	mmc->f_min =   450000;
	mmc->f_max = 24000000;

	mmc->max_blk_size = 2048;
	mmc->max_blk_count = 512;

	mmc->ocr_avail = AU1XMMC_OCR;
	mmc->caps = MMC_CAP_4_BIT_DATA | MMC_CAP_SDIO_IRQ;
	mmc->max_segs = AU1XMMC_DESCRIPTOR_COUNT;

	अगरlag = IRQF_SHARED;	/* Au1100/Au1200: one पूर्णांक क्रम both ctrls */

	चयन (alchemy_get_cputype()) अणु
	हाल ALCHEMY_CPU_AU1100:
		mmc->max_seg_size = AU1100_MMC_DESCRIPTOR_SIZE;
		अवरोध;
	हाल ALCHEMY_CPU_AU1200:
		mmc->max_seg_size = AU1200_MMC_DESCRIPTOR_SIZE;
		अवरोध;
	हाल ALCHEMY_CPU_AU1300:
		अगरlag = 0;	/* nothing is shared */
		mmc->max_seg_size = AU1200_MMC_DESCRIPTOR_SIZE;
		mmc->f_max = 52000000;
		अगर (host->ioarea->start == AU1100_SD0_PHYS_ADDR)
			mmc->caps |= MMC_CAP_8_BIT_DATA;
		अवरोध;
	पूर्ण

	ret = request_irq(host->irq, au1xmmc_irq, अगरlag, DRIVER_NAME, host);
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot grab IRQ\n");
		जाओ out3;
	पूर्ण

	host->clk = clk_get(&pdev->dev, ALCHEMY_PERIPH_CLK);
	अगर (IS_ERR(host->clk)) अणु
		dev_err(&pdev->dev, "cannot find clock\n");
		ret = PTR_ERR(host->clk);
		जाओ out_irq;
	पूर्ण

	ret = clk_prepare_enable(host->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot enable clock\n");
		जाओ out_clk;
	पूर्ण

	host->status = HOST_S_IDLE;

	/* board-specअगरic carddetect setup, अगर any */
	अगर (host->platdata && host->platdata->cd_setup) अणु
		ret = host->platdata->cd_setup(mmc, 1);
		अगर (ret) अणु
			dev_warn(&pdev->dev, "board CD setup failed\n");
			mmc->caps |= MMC_CAP_NEEDS_POLL;
		पूर्ण
	पूर्ण अन्यथा
		mmc->caps |= MMC_CAP_NEEDS_POLL;

	/* platक्रमm may not be able to use all advertised caps */
	अगर (host->platdata)
		mmc->caps &= ~(host->platdata->mask_host_caps);

	tasklet_setup(&host->data_task, au1xmmc_tasklet_data);

	tasklet_setup(&host->finish_task, au1xmmc_tasklet_finish);

	अगर (has_dbdma()) अणु
		ret = au1xmmc_dbdma_init(host);
		अगर (ret)
			pr_info(DRIVER_NAME ": DBDMA init failed; using PIO\n");
	पूर्ण

#अगर_घोषित CONFIG_LEDS_CLASS
	अगर (host->platdata && host->platdata->led) अणु
		काष्ठा led_classdev *led = host->platdata->led;
		led->name = mmc_hostname(mmc);
		led->brightness = LED_OFF;
		led->शेष_trigger = mmc_hostname(mmc);
		ret = led_classdev_रेजिस्टर(mmc_dev(mmc), led);
		अगर (ret)
			जाओ out5;
	पूर्ण
#पूर्ण_अगर

	au1xmmc_reset_controller(host);

	ret = mmc_add_host(mmc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot add mmc host\n");
		जाओ out6;
	पूर्ण

	platक्रमm_set_drvdata(pdev, host);

	pr_info(DRIVER_NAME ": MMC Controller %d set up at %p"
		" (mode=%s)\n", pdev->id, host->iobase,
		host->flags & HOST_F_DMA ? "dma" : "pio");

	वापस 0;	/* all ok */

out6:
#अगर_घोषित CONFIG_LEDS_CLASS
	अगर (host->platdata && host->platdata->led)
		led_classdev_unरेजिस्टर(host->platdata->led);
out5:
#पूर्ण_अगर
	__raw_ग_लिखोl(0, HOST_ENABLE(host));
	__raw_ग_लिखोl(0, HOST_CONFIG(host));
	__raw_ग_लिखोl(0, HOST_CONFIG2(host));
	wmb(); /* drain ग_लिखोbuffer */

	अगर (host->flags & HOST_F_DBDMA)
		au1xmmc_dbdma_shutकरोwn(host);

	tasklet_समाप्त(&host->data_task);
	tasklet_समाप्त(&host->finish_task);

	अगर (host->platdata && host->platdata->cd_setup &&
	    !(mmc->caps & MMC_CAP_NEEDS_POLL))
		host->platdata->cd_setup(mmc, 0);
out_clk:
	clk_disable_unprepare(host->clk);
	clk_put(host->clk);
out_irq:
	मुक्त_irq(host->irq, host);
out3:
	iounmap((व्योम *)host->iobase);
out2:
	release_resource(host->ioarea);
	kमुक्त(host->ioarea);
out1:
	mmc_मुक्त_host(mmc);
out0:
	वापस ret;
पूर्ण

अटल पूर्णांक au1xmmc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा au1xmmc_host *host = platक्रमm_get_drvdata(pdev);

	अगर (host) अणु
		mmc_हटाओ_host(host->mmc);

#अगर_घोषित CONFIG_LEDS_CLASS
		अगर (host->platdata && host->platdata->led)
			led_classdev_unरेजिस्टर(host->platdata->led);
#पूर्ण_अगर

		अगर (host->platdata && host->platdata->cd_setup &&
		    !(host->mmc->caps & MMC_CAP_NEEDS_POLL))
			host->platdata->cd_setup(host->mmc, 0);

		__raw_ग_लिखोl(0, HOST_ENABLE(host));
		__raw_ग_लिखोl(0, HOST_CONFIG(host));
		__raw_ग_लिखोl(0, HOST_CONFIG2(host));
		wmb(); /* drain ग_लिखोbuffer */

		tasklet_समाप्त(&host->data_task);
		tasklet_समाप्त(&host->finish_task);

		अगर (host->flags & HOST_F_DBDMA)
			au1xmmc_dbdma_shutकरोwn(host);

		au1xmmc_set_घातer(host, 0);

		clk_disable_unprepare(host->clk);
		clk_put(host->clk);

		मुक्त_irq(host->irq, host);
		iounmap((व्योम *)host->iobase);
		release_resource(host->ioarea);
		kमुक्त(host->ioarea);

		mmc_मुक्त_host(host->mmc);
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक au1xmmc_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा au1xmmc_host *host = platक्रमm_get_drvdata(pdev);

	__raw_ग_लिखोl(0, HOST_CONFIG2(host));
	__raw_ग_लिखोl(0, HOST_CONFIG(host));
	__raw_ग_लिखोl(0xffffffff, HOST_STATUS(host));
	__raw_ग_लिखोl(0, HOST_ENABLE(host));
	wmb(); /* drain ग_लिखोbuffer */

	वापस 0;
पूर्ण

अटल पूर्णांक au1xmmc_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा au1xmmc_host *host = platक्रमm_get_drvdata(pdev);

	au1xmmc_reset_controller(host);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा au1xmmc_suspend शून्य
#घोषणा au1xmmc_resume शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver au1xmmc_driver = अणु
	.probe         = au1xmmc_probe,
	.हटाओ        = au1xmmc_हटाओ,
	.suspend       = au1xmmc_suspend,
	.resume        = au1xmmc_resume,
	.driver        = अणु
		.name  = DRIVER_NAME,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init au1xmmc_init(व्योम)
अणु
	अगर (has_dbdma()) अणु
		/* DSCR_CMD0_ALWAYS has a stride of 32 bits, we need a stride
		* of 8 bits.  And since devices are shared, we need to create
		* our own to aव्योम freaking out other devices.
		*/
		memid = au1xxx_ddma_add_device(&au1xmmc_mem_dbdev);
		अगर (!memid)
			pr_err("au1xmmc: cannot add memory dbdma\n");
	पूर्ण
	वापस platक्रमm_driver_रेजिस्टर(&au1xmmc_driver);
पूर्ण

अटल व्योम __निकास au1xmmc_निकास(व्योम)
अणु
	अगर (has_dbdma() && memid)
		au1xxx_ddma_del_device(memid);

	platक्रमm_driver_unरेजिस्टर(&au1xmmc_driver);
पूर्ण

module_init(au1xmmc_init);
module_निकास(au1xmmc_निकास);

MODULE_AUTHOR("Advanced Micro Devices, Inc");
MODULE_DESCRIPTION("MMC/SD driver for the Alchemy Au1XXX");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:au1xxx-mmc");
