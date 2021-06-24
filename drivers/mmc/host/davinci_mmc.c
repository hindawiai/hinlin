<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * davinci_mmc.c - TI DaVinci MMC/SD/SDIO driver
 *
 * Copyright (C) 2006 Texas Instruments.
 *       Original author: Purushotam Kumar
 * Copyright (C) 2009 David Brownell
 */

#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/mmc/slot-gpपन.स>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/platक्रमm_data/mmc-davinci.h>

/*
 * Register Definitions
 */
#घोषणा DAVINCI_MMCCTL       0x00 /* Control Register                  */
#घोषणा DAVINCI_MMCCLK       0x04 /* Memory Clock Control Register     */
#घोषणा DAVINCI_MMCST0       0x08 /* Status Register 0                 */
#घोषणा DAVINCI_MMCST1       0x0C /* Status Register 1                 */
#घोषणा DAVINCI_MMCIM        0x10 /* Interrupt Mask Register           */
#घोषणा DAVINCI_MMCTOR       0x14 /* Response Time-Out Register        */
#घोषणा DAVINCI_MMCTOD       0x18 /* Data Read Time-Out Register       */
#घोषणा DAVINCI_MMCBLEN      0x1C /* Block Length Register             */
#घोषणा DAVINCI_MMCNBLK      0x20 /* Number of Blocks Register         */
#घोषणा DAVINCI_MMCNBLC      0x24 /* Number of Blocks Counter Register */
#घोषणा DAVINCI_MMCDRR       0x28 /* Data Receive Register             */
#घोषणा DAVINCI_MMCDXR       0x2C /* Data Transmit Register            */
#घोषणा DAVINCI_MMCCMD       0x30 /* Command Register                  */
#घोषणा DAVINCI_MMCARGHL     0x34 /* Argument Register                 */
#घोषणा DAVINCI_MMCRSP01     0x38 /* Response Register 0 and 1         */
#घोषणा DAVINCI_MMCRSP23     0x3C /* Response Register 0 and 1         */
#घोषणा DAVINCI_MMCRSP45     0x40 /* Response Register 0 and 1         */
#घोषणा DAVINCI_MMCRSP67     0x44 /* Response Register 0 and 1         */
#घोषणा DAVINCI_MMCDRSP      0x48 /* Data Response Register            */
#घोषणा DAVINCI_MMCETOK      0x4C
#घोषणा DAVINCI_MMCCIDX      0x50 /* Command Index Register            */
#घोषणा DAVINCI_MMCCKC       0x54
#घोषणा DAVINCI_MMCTORC      0x58
#घोषणा DAVINCI_MMCTODC      0x5C
#घोषणा DAVINCI_MMCBLNC      0x60
#घोषणा DAVINCI_SDIOCTL      0x64
#घोषणा DAVINCI_SDIOST0      0x68
#घोषणा DAVINCI_SDIOIEN      0x6C
#घोषणा DAVINCI_SDIOIST      0x70
#घोषणा DAVINCI_MMCFIFOCTL   0x74 /* FIFO Control Register             */

/* DAVINCI_MMCCTL definitions */
#घोषणा MMCCTL_DATRST         (1 << 0)
#घोषणा MMCCTL_CMDRST         (1 << 1)
#घोषणा MMCCTL_WIDTH_8_BIT    (1 << 8)
#घोषणा MMCCTL_WIDTH_4_BIT    (1 << 2)
#घोषणा MMCCTL_DATEG_DISABLED (0 << 6)
#घोषणा MMCCTL_DATEG_RISING   (1 << 6)
#घोषणा MMCCTL_DATEG_FALLING  (2 << 6)
#घोषणा MMCCTL_DATEG_BOTH     (3 << 6)
#घोषणा MMCCTL_PERMDR_LE      (0 << 9)
#घोषणा MMCCTL_PERMDR_BE      (1 << 9)
#घोषणा MMCCTL_PERMDX_LE      (0 << 10)
#घोषणा MMCCTL_PERMDX_BE      (1 << 10)

/* DAVINCI_MMCCLK definitions */
#घोषणा MMCCLK_CLKEN          (1 << 8)
#घोषणा MMCCLK_CLKRT_MASK     (0xFF << 0)

/* IRQ bit definitions, क्रम DAVINCI_MMCST0 and DAVINCI_MMCIM */
#घोषणा MMCST0_DATDNE         BIT(0)	/* data करोne */
#घोषणा MMCST0_BSYDNE         BIT(1)	/* busy करोne */
#घोषणा MMCST0_RSPDNE         BIT(2)	/* command करोne */
#घोषणा MMCST0_TOUTRD         BIT(3)	/* data पढ़ो समयout */
#घोषणा MMCST0_TOUTRS         BIT(4)	/* command response समयout */
#घोषणा MMCST0_CRCWR          BIT(5)	/* data ग_लिखो CRC error */
#घोषणा MMCST0_CRCRD          BIT(6)	/* data पढ़ो CRC error */
#घोषणा MMCST0_CRCRS          BIT(7)	/* command response CRC error */
#घोषणा MMCST0_DXRDY          BIT(9)	/* data transmit पढ़ोy (fअगरo empty) */
#घोषणा MMCST0_DRRDY          BIT(10)	/* data receive पढ़ोy (data in fअगरo)*/
#घोषणा MMCST0_DATED          BIT(11)	/* DAT3 edge detect */
#घोषणा MMCST0_TRNDNE         BIT(12)	/* transfer करोne */

/* DAVINCI_MMCST1 definitions */
#घोषणा MMCST1_BUSY           (1 << 0)

/* DAVINCI_MMCCMD definitions */
#घोषणा MMCCMD_CMD_MASK       (0x3F << 0)
#घोषणा MMCCMD_PPLEN          (1 << 7)
#घोषणा MMCCMD_BSYEXP         (1 << 8)
#घोषणा MMCCMD_RSPFMT_MASK    (3 << 9)
#घोषणा MMCCMD_RSPFMT_NONE    (0 << 9)
#घोषणा MMCCMD_RSPFMT_R1456   (1 << 9)
#घोषणा MMCCMD_RSPFMT_R2      (2 << 9)
#घोषणा MMCCMD_RSPFMT_R3      (3 << 9)
#घोषणा MMCCMD_DTRW           (1 << 11)
#घोषणा MMCCMD_STRMTP         (1 << 12)
#घोषणा MMCCMD_WDATX          (1 << 13)
#घोषणा MMCCMD_INITCK         (1 << 14)
#घोषणा MMCCMD_DCLR           (1 << 15)
#घोषणा MMCCMD_DMATRIG        (1 << 16)

/* DAVINCI_MMCFIFOCTL definitions */
#घोषणा MMCFIFOCTL_FIFORST    (1 << 0)
#घोषणा MMCFIFOCTL_FIFOसूची_WR (1 << 1)
#घोषणा MMCFIFOCTL_FIFOसूची_RD (0 << 1)
#घोषणा MMCFIFOCTL_FIFOLEV    (1 << 2) /* 0 = 128 bits, 1 = 256 bits */
#घोषणा MMCFIFOCTL_ACCWD_4    (0 << 3) /* access width of 4 bytes    */
#घोषणा MMCFIFOCTL_ACCWD_3    (1 << 3) /* access width of 3 bytes    */
#घोषणा MMCFIFOCTL_ACCWD_2    (2 << 3) /* access width of 2 bytes    */
#घोषणा MMCFIFOCTL_ACCWD_1    (3 << 3) /* access width of 1 byte     */

/* DAVINCI_SDIOST0 definitions */
#घोषणा SDIOST0_DAT1_HI       BIT(0)

/* DAVINCI_SDIOIEN definitions */
#घोषणा SDIOIEN_IOINTEN       BIT(0)

/* DAVINCI_SDIOIST definitions */
#घोषणा SDIOIST_IOINT         BIT(0)

/* MMCSD Init घड़ी in Hz in खोलोdrain mode */
#घोषणा MMCSD_INIT_CLOCK		200000

/*
 * One scatterlist dma "segment" is at most MAX_CCNT rw_threshold units,
 * and we handle up to MAX_NR_SG segments.  MMC_BLOCK_BOUNCE kicks in only
 * क्रम drivers with max_segs == 1, making the segments bigger (64KB)
 * than the page or two that's otherwise typical. nr_sg (passed from
 * platक्रमm data) == 16 gives at least the same throughput boost, using
 * EDMA transfer linkage instead of spending CPU समय copying pages.
 */
#घोषणा MAX_CCNT	((1 << 16) - 1)

#घोषणा MAX_NR_SG	16

अटल अचिन्हित rw_threshold = 32;
module_param(rw_threshold, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(rw_threshold,
		"Read/Write threshold. Default = 32");

अटल अचिन्हित poll_threshold = 128;
module_param(poll_threshold, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(poll_threshold,
		 "Polling transaction size threshold. Default = 128");

अटल अचिन्हित poll_loopcount = 32;
module_param(poll_loopcount, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(poll_loopcount,
		 "Maximum polling loop count. Default = 32");

अटल अचिन्हित use_dma = 1;
module_param(use_dma, uपूर्णांक, 0);
MODULE_PARM_DESC(use_dma, "Whether to use DMA or not. Default = 1");

काष्ठा mmc_davinci_host अणु
	काष्ठा mmc_command *cmd;
	काष्ठा mmc_data *data;
	काष्ठा mmc_host *mmc;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक mmc_input_clk;
	व्योम __iomem *base;
	काष्ठा resource *mem_res;
	पूर्णांक mmc_irq, sdio_irq;
	अचिन्हित अक्षर bus_mode;

#घोषणा DAVINCI_MMC_DATAसूची_NONE	0
#घोषणा DAVINCI_MMC_DATAसूची_READ	1
#घोषणा DAVINCI_MMC_DATAसूची_WRITE	2
	अचिन्हित अक्षर data_dir;

	/* buffer is used during PIO of one scatterlist segment, and
	 * is updated aदीर्घ with buffer_bytes_left.  bytes_left applies
	 * to all N blocks of the PIO transfer.
	 */
	u8 *buffer;
	u32 buffer_bytes_left;
	u32 bytes_left;

	काष्ठा dma_chan *dma_tx;
	काष्ठा dma_chan *dma_rx;
	bool use_dma;
	bool करो_dma;
	bool sdio_पूर्णांक;
	bool active_request;

	/* For PIO we walk scatterlists one segment at a समय. */
	अचिन्हित पूर्णांक		sg_len;
	काष्ठा scatterlist *sg;

	/* Version of the MMC/SD controller */
	u8 version;
	/* क्रम ns in one cycle calculation */
	अचिन्हित ns_in_one_cycle;
	/* Number of sg segments */
	u8 nr_sg;
#अगर_घोषित CONFIG_CPU_FREQ
	काष्ठा notअगरier_block	freq_transition;
#पूर्ण_अगर
पूर्ण;

अटल irqवापस_t mmc_davinci_irq(पूर्णांक irq, व्योम *dev_id);

/* PIO only */
अटल व्योम mmc_davinci_sg_to_buf(काष्ठा mmc_davinci_host *host)
अणु
	host->buffer_bytes_left = sg_dma_len(host->sg);
	host->buffer = sg_virt(host->sg);
	अगर (host->buffer_bytes_left > host->bytes_left)
		host->buffer_bytes_left = host->bytes_left;
पूर्ण

अटल व्योम davinci_fअगरo_data_trans(काष्ठा mmc_davinci_host *host,
					अचिन्हित पूर्णांक n)
अणु
	u8 *p;
	अचिन्हित पूर्णांक i;

	अगर (host->buffer_bytes_left == 0) अणु
		host->sg = sg_next(host->data->sg);
		mmc_davinci_sg_to_buf(host);
	पूर्ण

	p = host->buffer;
	अगर (n > host->buffer_bytes_left)
		n = host->buffer_bytes_left;
	host->buffer_bytes_left -= n;
	host->bytes_left -= n;

	/* NOTE:  we never transfer more than rw_threshold bytes
	 * to/from the fअगरo here; there's no I/O overlap.
	 * This also assumes that access width( i.e. ACCWD) is 4 bytes
	 */
	अगर (host->data_dir == DAVINCI_MMC_DATAसूची_WRITE) अणु
		क्रम (i = 0; i < (n >> 2); i++) अणु
			ग_लिखोl(*((u32 *)p), host->base + DAVINCI_MMCDXR);
			p = p + 4;
		पूर्ण
		अगर (n & 3) अणु
			ioग_लिखो8_rep(host->base + DAVINCI_MMCDXR, p, (n & 3));
			p = p + (n & 3);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < (n >> 2); i++) अणु
			*((u32 *)p) = पढ़ोl(host->base + DAVINCI_MMCDRR);
			p  = p + 4;
		पूर्ण
		अगर (n & 3) अणु
			ioपढ़ो8_rep(host->base + DAVINCI_MMCDRR, p, (n & 3));
			p = p + (n & 3);
		पूर्ण
	पूर्ण
	host->buffer = p;
पूर्ण

अटल व्योम mmc_davinci_start_command(काष्ठा mmc_davinci_host *host,
		काष्ठा mmc_command *cmd)
अणु
	u32 cmd_reg = 0;
	u32 im_val;

	dev_dbg(mmc_dev(host->mmc), "CMD%d, arg 0x%08x%s\n",
		cmd->opcode, cmd->arg,
		(अणु अक्षर *s;
		चयन (mmc_resp_type(cmd)) अणु
		हाल MMC_RSP_R1:
			s = ", R1/R5/R6/R7 response";
			अवरोध;
		हाल MMC_RSP_R1B:
			s = ", R1b response";
			अवरोध;
		हाल MMC_RSP_R2:
			s = ", R2 response";
			अवरोध;
		हाल MMC_RSP_R3:
			s = ", R3/R4 response";
			अवरोध;
		शेष:
			s = ", (R? response)";
			अवरोध;
		पूर्ण s; पूर्ण));
	host->cmd = cmd;

	चयन (mmc_resp_type(cmd)) अणु
	हाल MMC_RSP_R1B:
		/* There's some spec confusion about when R1B is
		 * allowed, but अगर the card करोesn't issue a BUSY
		 * then it's harmless क्रम us to allow it.
		 */
		cmd_reg |= MMCCMD_BSYEXP;
		fallthrough;
	हाल MMC_RSP_R1:		/* 48 bits, CRC */
		cmd_reg |= MMCCMD_RSPFMT_R1456;
		अवरोध;
	हाल MMC_RSP_R2:		/* 136 bits, CRC */
		cmd_reg |= MMCCMD_RSPFMT_R2;
		अवरोध;
	हाल MMC_RSP_R3:		/* 48 bits, no CRC */
		cmd_reg |= MMCCMD_RSPFMT_R3;
		अवरोध;
	शेष:
		cmd_reg |= MMCCMD_RSPFMT_NONE;
		dev_dbg(mmc_dev(host->mmc), "unknown resp_type %04x\n",
			mmc_resp_type(cmd));
		अवरोध;
	पूर्ण

	/* Set command index */
	cmd_reg |= cmd->opcode;

	/* Enable EDMA transfer triggers */
	अगर (host->करो_dma)
		cmd_reg |= MMCCMD_DMATRIG;

	अगर (host->version == MMC_CTLR_VERSION_2 && host->data != शून्य &&
			host->data_dir == DAVINCI_MMC_DATAसूची_READ)
		cmd_reg |= MMCCMD_DMATRIG;

	/* Setting whether command involves data transfer or not */
	अगर (cmd->data)
		cmd_reg |= MMCCMD_WDATX;

	/* Setting whether data पढ़ो or ग_लिखो */
	अगर (host->data_dir == DAVINCI_MMC_DATAसूची_WRITE)
		cmd_reg |= MMCCMD_DTRW;

	अगर (host->bus_mode == MMC_BUSMODE_PUSHPULL)
		cmd_reg |= MMCCMD_PPLEN;

	/* set Command समयout */
	ग_लिखोl(0x1FFF, host->base + DAVINCI_MMCTOR);

	/* Enable पूर्णांकerrupt (calculate here, defer until FIFO is stuffed). */
	im_val =  MMCST0_RSPDNE | MMCST0_CRCRS | MMCST0_TOUTRS;
	अगर (host->data_dir == DAVINCI_MMC_DATAसूची_WRITE) अणु
		im_val |= MMCST0_DATDNE | MMCST0_CRCWR;

		अगर (!host->करो_dma)
			im_val |= MMCST0_DXRDY;
	पूर्ण अन्यथा अगर (host->data_dir == DAVINCI_MMC_DATAसूची_READ) अणु
		im_val |= MMCST0_DATDNE | MMCST0_CRCRD | MMCST0_TOUTRD;

		अगर (!host->करो_dma)
			im_val |= MMCST0_DRRDY;
	पूर्ण

	/*
	 * Beक्रमe non-DMA WRITE commands the controller needs priming:
	 * FIFO should be populated with 32 bytes i.e. whatever is the FIFO size
	 */
	अगर (!host->करो_dma && (host->data_dir == DAVINCI_MMC_DATAसूची_WRITE))
		davinci_fअगरo_data_trans(host, rw_threshold);

	ग_लिखोl(cmd->arg, host->base + DAVINCI_MMCARGHL);
	ग_लिखोl(cmd_reg,  host->base + DAVINCI_MMCCMD);

	host->active_request = true;

	अगर (!host->करो_dma && host->bytes_left <= poll_threshold) अणु
		u32 count = poll_loopcount;

		जबतक (host->active_request && count--) अणु
			mmc_davinci_irq(0, host);
			cpu_relax();
		पूर्ण
	पूर्ण

	अगर (host->active_request)
		ग_लिखोl(im_val, host->base + DAVINCI_MMCIM);
पूर्ण

/*----------------------------------------------------------------------*/

/* DMA infraकाष्ठाure */

अटल व्योम davinci_पात_dma(काष्ठा mmc_davinci_host *host)
अणु
	काष्ठा dma_chan *sync_dev;

	अगर (host->data_dir == DAVINCI_MMC_DATAसूची_READ)
		sync_dev = host->dma_rx;
	अन्यथा
		sync_dev = host->dma_tx;

	dmaengine_terminate_all(sync_dev);
पूर्ण

अटल पूर्णांक mmc_davinci_send_dma_request(काष्ठा mmc_davinci_host *host,
		काष्ठा mmc_data *data)
अणु
	काष्ठा dma_chan *chan;
	काष्ठा dma_async_tx_descriptor *desc;
	पूर्णांक ret = 0;

	अगर (host->data_dir == DAVINCI_MMC_DATAसूची_WRITE) अणु
		काष्ठा dma_slave_config dma_tx_conf = अणु
			.direction = DMA_MEM_TO_DEV,
			.dst_addr = host->mem_res->start + DAVINCI_MMCDXR,
			.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES,
			.dst_maxburst =
				rw_threshold / DMA_SLAVE_BUSWIDTH_4_BYTES,
		पूर्ण;
		chan = host->dma_tx;
		dmaengine_slave_config(host->dma_tx, &dma_tx_conf);

		desc = dmaengine_prep_slave_sg(host->dma_tx,
				data->sg,
				host->sg_len,
				DMA_MEM_TO_DEV,
				DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
		अगर (!desc) अणु
			dev_dbg(mmc_dev(host->mmc),
				"failed to allocate DMA TX descriptor");
			ret = -1;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा dma_slave_config dma_rx_conf = अणु
			.direction = DMA_DEV_TO_MEM,
			.src_addr = host->mem_res->start + DAVINCI_MMCDRR,
			.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES,
			.src_maxburst =
				rw_threshold / DMA_SLAVE_BUSWIDTH_4_BYTES,
		पूर्ण;
		chan = host->dma_rx;
		dmaengine_slave_config(host->dma_rx, &dma_rx_conf);

		desc = dmaengine_prep_slave_sg(host->dma_rx,
				data->sg,
				host->sg_len,
				DMA_DEV_TO_MEM,
				DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
		अगर (!desc) अणु
			dev_dbg(mmc_dev(host->mmc),
				"failed to allocate DMA RX descriptor");
			ret = -1;
			जाओ out;
		पूर्ण
	पूर्ण

	dmaengine_submit(desc);
	dma_async_issue_pending(chan);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक mmc_davinci_start_dma_transfer(काष्ठा mmc_davinci_host *host,
		काष्ठा mmc_data *data)
अणु
	पूर्णांक i;
	पूर्णांक mask = rw_threshold - 1;
	पूर्णांक ret = 0;

	host->sg_len = dma_map_sg(mmc_dev(host->mmc), data->sg, data->sg_len,
				  mmc_get_dma_dir(data));

	/* no inभागidual DMA segment should need a partial FIFO */
	क्रम (i = 0; i < host->sg_len; i++) अणु
		अगर (sg_dma_len(data->sg + i) & mask) अणु
			dma_unmap_sg(mmc_dev(host->mmc),
				     data->sg, data->sg_len,
				     mmc_get_dma_dir(data));
			वापस -1;
		पूर्ण
	पूर्ण

	host->करो_dma = 1;
	ret = mmc_davinci_send_dma_request(host, data);

	वापस ret;
पूर्ण

अटल व्योम davinci_release_dma_channels(काष्ठा mmc_davinci_host *host)
अणु
	अगर (!host->use_dma)
		वापस;

	dma_release_channel(host->dma_tx);
	dma_release_channel(host->dma_rx);
पूर्ण

अटल पूर्णांक davinci_acquire_dma_channels(काष्ठा mmc_davinci_host *host)
अणु
	host->dma_tx = dma_request_chan(mmc_dev(host->mmc), "tx");
	अगर (IS_ERR(host->dma_tx)) अणु
		dev_err(mmc_dev(host->mmc), "Can't get dma_tx channel\n");
		वापस PTR_ERR(host->dma_tx);
	पूर्ण

	host->dma_rx = dma_request_chan(mmc_dev(host->mmc), "rx");
	अगर (IS_ERR(host->dma_rx)) अणु
		dev_err(mmc_dev(host->mmc), "Can't get dma_rx channel\n");
		dma_release_channel(host->dma_tx);
		वापस PTR_ERR(host->dma_rx);
	पूर्ण

	वापस 0;
पूर्ण

/*----------------------------------------------------------------------*/

अटल व्योम
mmc_davinci_prepare_data(काष्ठा mmc_davinci_host *host, काष्ठा mmc_request *req)
अणु
	पूर्णांक fअगरo_lev = (rw_threshold == 32) ? MMCFIFOCTL_FIFOLEV : 0;
	पूर्णांक समयout;
	काष्ठा mmc_data *data = req->data;

	अगर (host->version == MMC_CTLR_VERSION_2)
		fअगरo_lev = (rw_threshold == 64) ? MMCFIFOCTL_FIFOLEV : 0;

	host->data = data;
	अगर (data == शून्य) अणु
		host->data_dir = DAVINCI_MMC_DATAसूची_NONE;
		ग_लिखोl(0, host->base + DAVINCI_MMCBLEN);
		ग_लिखोl(0, host->base + DAVINCI_MMCNBLK);
		वापस;
	पूर्ण

	dev_dbg(mmc_dev(host->mmc), "%s, %d blocks of %d bytes\n",
		(data->flags & MMC_DATA_WRITE) ? "write" : "read",
		data->blocks, data->blksz);
	dev_dbg(mmc_dev(host->mmc), "  DTO %d cycles + %d ns\n",
		data->समयout_clks, data->समयout_ns);
	समयout = data->समयout_clks +
		(data->समयout_ns / host->ns_in_one_cycle);
	अगर (समयout > 0xffff)
		समयout = 0xffff;

	ग_लिखोl(समयout, host->base + DAVINCI_MMCTOD);
	ग_लिखोl(data->blocks, host->base + DAVINCI_MMCNBLK);
	ग_लिखोl(data->blksz, host->base + DAVINCI_MMCBLEN);

	/* Configure the FIFO */
	अगर (data->flags & MMC_DATA_WRITE) अणु
		host->data_dir = DAVINCI_MMC_DATAसूची_WRITE;
		ग_लिखोl(fअगरo_lev | MMCFIFOCTL_FIFOसूची_WR | MMCFIFOCTL_FIFORST,
			host->base + DAVINCI_MMCFIFOCTL);
		ग_लिखोl(fअगरo_lev | MMCFIFOCTL_FIFOसूची_WR,
			host->base + DAVINCI_MMCFIFOCTL);
	पूर्ण अन्यथा अणु
		host->data_dir = DAVINCI_MMC_DATAसूची_READ;
		ग_लिखोl(fअगरo_lev | MMCFIFOCTL_FIFOसूची_RD | MMCFIFOCTL_FIFORST,
			host->base + DAVINCI_MMCFIFOCTL);
		ग_लिखोl(fअगरo_lev | MMCFIFOCTL_FIFOसूची_RD,
			host->base + DAVINCI_MMCFIFOCTL);
	पूर्ण

	host->buffer = शून्य;
	host->bytes_left = data->blocks * data->blksz;

	/* For now we try to use DMA whenever we won't need partial FIFO
	 * पढ़ोs or ग_लिखोs, either क्रम the whole transfer (as tested here)
	 * or क्रम any inभागidual scatterlist segment (tested when we call
	 * start_dma_transfer).
	 *
	 * While we *could* change that, unusual block sizes are rarely
	 * used.  The occasional fallback to PIO should't hurt.
	 */
	अगर (host->use_dma && (host->bytes_left & (rw_threshold - 1)) == 0
			&& mmc_davinci_start_dma_transfer(host, data) == 0) अणु
		/* zero this to ensure we take no PIO paths */
		host->bytes_left = 0;
	पूर्ण अन्यथा अणु
		/* Revert to CPU Copy */
		host->sg_len = data->sg_len;
		host->sg = host->data->sg;
		mmc_davinci_sg_to_buf(host);
	पूर्ण
पूर्ण

अटल व्योम mmc_davinci_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *req)
अणु
	काष्ठा mmc_davinci_host *host = mmc_priv(mmc);
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(900);
	u32 mmcst1 = 0;

	/* Card may still be sending BUSY after a previous operation,
	 * typically some kind of ग_लिखो.  If so, we can't proceed yet.
	 */
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		mmcst1  = पढ़ोl(host->base + DAVINCI_MMCST1);
		अगर (!(mmcst1 & MMCST1_BUSY))
			अवरोध;
		cpu_relax();
	पूर्ण
	अगर (mmcst1 & MMCST1_BUSY) अणु
		dev_err(mmc_dev(host->mmc), "still BUSY? bad ... \n");
		req->cmd->error = -ETIMEDOUT;
		mmc_request_करोne(mmc, req);
		वापस;
	पूर्ण

	host->करो_dma = 0;
	mmc_davinci_prepare_data(host, req);
	mmc_davinci_start_command(host, req->cmd);
पूर्ण

अटल अचिन्हित पूर्णांक calculate_freq_क्रम_card(काष्ठा mmc_davinci_host *host,
	अचिन्हित पूर्णांक mmc_req_freq)
अणु
	अचिन्हित पूर्णांक mmc_freq = 0, mmc_pclk = 0, mmc_push_pull_भागisor = 0;

	mmc_pclk = host->mmc_input_clk;
	अगर (mmc_req_freq && mmc_pclk > (2 * mmc_req_freq))
		mmc_push_pull_भागisor = ((अचिन्हित पूर्णांक)mmc_pclk
				/ (2 * mmc_req_freq)) - 1;
	अन्यथा
		mmc_push_pull_भागisor = 0;

	mmc_freq = (अचिन्हित पूर्णांक)mmc_pclk
		/ (2 * (mmc_push_pull_भागisor + 1));

	अगर (mmc_freq > mmc_req_freq)
		mmc_push_pull_भागisor = mmc_push_pull_भागisor + 1;
	/* Convert ns to घड़ी cycles */
	अगर (mmc_req_freq <= 400000)
		host->ns_in_one_cycle = (1000000) / (((mmc_pclk
				/ (2 * (mmc_push_pull_भागisor + 1)))/1000));
	अन्यथा
		host->ns_in_one_cycle = (1000000) / (((mmc_pclk
				/ (2 * (mmc_push_pull_भागisor + 1)))/1000000));

	वापस mmc_push_pull_भागisor;
पूर्ण

अटल व्योम calculate_clk_भागider(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	अचिन्हित पूर्णांक खोलो_drain_freq = 0, mmc_pclk = 0;
	अचिन्हित पूर्णांक mmc_push_pull_freq = 0;
	काष्ठा mmc_davinci_host *host = mmc_priv(mmc);

	अगर (ios->bus_mode == MMC_BUSMODE_OPENDRAIN) अणु
		u32 temp;

		/* Ignoring the init घड़ी value passed क्रम fixing the पूर्णांकer
		 * operability with dअगरferent cards.
		 */
		खोलो_drain_freq = ((अचिन्हित पूर्णांक)mmc_pclk
				/ (2 * MMCSD_INIT_CLOCK)) - 1;

		अगर (खोलो_drain_freq > 0xFF)
			खोलो_drain_freq = 0xFF;

		temp = पढ़ोl(host->base + DAVINCI_MMCCLK) & ~MMCCLK_CLKRT_MASK;
		temp |= खोलो_drain_freq;
		ग_लिखोl(temp, host->base + DAVINCI_MMCCLK);

		/* Convert ns to घड़ी cycles */
		host->ns_in_one_cycle = (1000000) / (MMCSD_INIT_CLOCK/1000);
	पूर्ण अन्यथा अणु
		u32 temp;
		mmc_push_pull_freq = calculate_freq_क्रम_card(host, ios->घड़ी);

		अगर (mmc_push_pull_freq > 0xFF)
			mmc_push_pull_freq = 0xFF;

		temp = पढ़ोl(host->base + DAVINCI_MMCCLK) & ~MMCCLK_CLKEN;
		ग_लिखोl(temp, host->base + DAVINCI_MMCCLK);

		udelay(10);

		temp = पढ़ोl(host->base + DAVINCI_MMCCLK) & ~MMCCLK_CLKRT_MASK;
		temp |= mmc_push_pull_freq;
		ग_लिखोl(temp, host->base + DAVINCI_MMCCLK);

		ग_लिखोl(temp | MMCCLK_CLKEN, host->base + DAVINCI_MMCCLK);

		udelay(10);
	पूर्ण
पूर्ण

अटल व्योम mmc_davinci_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा mmc_davinci_host *host = mmc_priv(mmc);
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(mmc->parent);
	काष्ठा davinci_mmc_config *config = pdev->dev.platक्रमm_data;

	dev_dbg(mmc_dev(host->mmc),
		"clock %dHz busmode %d powermode %d Vdd %04x\n",
		ios->घड़ी, ios->bus_mode, ios->घातer_mode,
		ios->vdd);

	चयन (ios->घातer_mode) अणु
	हाल MMC_POWER_OFF:
		अगर (config && config->set_घातer)
			config->set_घातer(pdev->id, false);
		अवरोध;
	हाल MMC_POWER_UP:
		अगर (config && config->set_घातer)
			config->set_घातer(pdev->id, true);
		अवरोध;
	पूर्ण

	चयन (ios->bus_width) अणु
	हाल MMC_BUS_WIDTH_8:
		dev_dbg(mmc_dev(host->mmc), "Enabling 8 bit mode\n");
		ग_लिखोl((पढ़ोl(host->base + DAVINCI_MMCCTL) &
			~MMCCTL_WIDTH_4_BIT) | MMCCTL_WIDTH_8_BIT,
			host->base + DAVINCI_MMCCTL);
		अवरोध;
	हाल MMC_BUS_WIDTH_4:
		dev_dbg(mmc_dev(host->mmc), "Enabling 4 bit mode\n");
		अगर (host->version == MMC_CTLR_VERSION_2)
			ग_लिखोl((पढ़ोl(host->base + DAVINCI_MMCCTL) &
				~MMCCTL_WIDTH_8_BIT) | MMCCTL_WIDTH_4_BIT,
				host->base + DAVINCI_MMCCTL);
		अन्यथा
			ग_लिखोl(पढ़ोl(host->base + DAVINCI_MMCCTL) |
				MMCCTL_WIDTH_4_BIT,
				host->base + DAVINCI_MMCCTL);
		अवरोध;
	हाल MMC_BUS_WIDTH_1:
		dev_dbg(mmc_dev(host->mmc), "Enabling 1 bit mode\n");
		अगर (host->version == MMC_CTLR_VERSION_2)
			ग_लिखोl(पढ़ोl(host->base + DAVINCI_MMCCTL) &
				~(MMCCTL_WIDTH_8_BIT | MMCCTL_WIDTH_4_BIT),
				host->base + DAVINCI_MMCCTL);
		अन्यथा
			ग_लिखोl(पढ़ोl(host->base + DAVINCI_MMCCTL) &
				~MMCCTL_WIDTH_4_BIT,
				host->base + DAVINCI_MMCCTL);
		अवरोध;
	पूर्ण

	calculate_clk_भागider(mmc, ios);

	host->bus_mode = ios->bus_mode;
	अगर (ios->घातer_mode == MMC_POWER_UP) अणु
		अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(50);
		bool lose = true;

		/* Send घड़ी cycles, poll completion */
		ग_लिखोl(0, host->base + DAVINCI_MMCARGHL);
		ग_लिखोl(MMCCMD_INITCK, host->base + DAVINCI_MMCCMD);
		जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
			u32 पंचांगp = पढ़ोl(host->base + DAVINCI_MMCST0);

			अगर (पंचांगp & MMCST0_RSPDNE) अणु
				lose = false;
				अवरोध;
			पूर्ण
			cpu_relax();
		पूर्ण
		अगर (lose)
			dev_warn(mmc_dev(host->mmc), "powerup timeout\n");
	पूर्ण

	/* FIXME on घातer OFF, reset things ... */
पूर्ण

अटल व्योम
mmc_davinci_xfer_करोne(काष्ठा mmc_davinci_host *host, काष्ठा mmc_data *data)
अणु
	host->data = शून्य;

	अगर (host->mmc->caps & MMC_CAP_SDIO_IRQ) अणु
		/*
		 * SDIO Interrupt Detection work-around as suggested by
		 * Davinci Errata (TMS320DM355 Silicon Revision 1.1 Errata
		 * 2.1.6): Signal SDIO पूर्णांकerrupt only अगर it is enabled by core
		 */
		अगर (host->sdio_पूर्णांक && !(पढ़ोl(host->base + DAVINCI_SDIOST0) &
					SDIOST0_DAT1_HI)) अणु
			ग_लिखोl(SDIOIST_IOINT, host->base + DAVINCI_SDIOIST);
			mmc_संकेत_sdio_irq(host->mmc);
		पूर्ण
	पूर्ण

	अगर (host->करो_dma) अणु
		davinci_पात_dma(host);

		dma_unmap_sg(mmc_dev(host->mmc), data->sg, data->sg_len,
			     mmc_get_dma_dir(data));
		host->करो_dma = false;
	पूर्ण
	host->data_dir = DAVINCI_MMC_DATAसूची_NONE;

	अगर (!data->stop || (host->cmd && host->cmd->error)) अणु
		mmc_request_करोne(host->mmc, data->mrq);
		ग_लिखोl(0, host->base + DAVINCI_MMCIM);
		host->active_request = false;
	पूर्ण अन्यथा
		mmc_davinci_start_command(host, data->stop);
पूर्ण

अटल व्योम mmc_davinci_cmd_करोne(काष्ठा mmc_davinci_host *host,
				 काष्ठा mmc_command *cmd)
अणु
	host->cmd = शून्य;

	अगर (cmd->flags & MMC_RSP_PRESENT) अणु
		अगर (cmd->flags & MMC_RSP_136) अणु
			/* response type 2 */
			cmd->resp[3] = पढ़ोl(host->base + DAVINCI_MMCRSP01);
			cmd->resp[2] = पढ़ोl(host->base + DAVINCI_MMCRSP23);
			cmd->resp[1] = पढ़ोl(host->base + DAVINCI_MMCRSP45);
			cmd->resp[0] = पढ़ोl(host->base + DAVINCI_MMCRSP67);
		पूर्ण अन्यथा अणु
			/* response types 1, 1b, 3, 4, 5, 6 */
			cmd->resp[0] = पढ़ोl(host->base + DAVINCI_MMCRSP67);
		पूर्ण
	पूर्ण

	अगर (host->data == शून्य || cmd->error) अणु
		अगर (cmd->error == -ETIMEDOUT)
			cmd->mrq->cmd->retries = 0;
		mmc_request_करोne(host->mmc, cmd->mrq);
		ग_लिखोl(0, host->base + DAVINCI_MMCIM);
		host->active_request = false;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम mmc_davinci_reset_ctrl(काष्ठा mmc_davinci_host *host,
								पूर्णांक val)
अणु
	u32 temp;

	temp = पढ़ोl(host->base + DAVINCI_MMCCTL);
	अगर (val)	/* reset */
		temp |= MMCCTL_CMDRST | MMCCTL_DATRST;
	अन्यथा		/* enable */
		temp &= ~(MMCCTL_CMDRST | MMCCTL_DATRST);

	ग_लिखोl(temp, host->base + DAVINCI_MMCCTL);
	udelay(10);
पूर्ण

अटल व्योम
davinci_पात_data(काष्ठा mmc_davinci_host *host, काष्ठा mmc_data *data)
अणु
	mmc_davinci_reset_ctrl(host, 1);
	mmc_davinci_reset_ctrl(host, 0);
पूर्ण

अटल irqवापस_t mmc_davinci_sdio_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mmc_davinci_host *host = dev_id;
	अचिन्हित पूर्णांक status;

	status = पढ़ोl(host->base + DAVINCI_SDIOIST);
	अगर (status & SDIOIST_IOINT) अणु
		dev_dbg(mmc_dev(host->mmc),
			"SDIO interrupt status %x\n", status);
		ग_लिखोl(status | SDIOIST_IOINT, host->base + DAVINCI_SDIOIST);
		mmc_संकेत_sdio_irq(host->mmc);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mmc_davinci_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mmc_davinci_host *host = (काष्ठा mmc_davinci_host *)dev_id;
	अचिन्हित पूर्णांक status, qstatus;
	पूर्णांक end_command = 0;
	पूर्णांक end_transfer = 0;
	काष्ठा mmc_data *data = host->data;

	अगर (host->cmd == शून्य && host->data == शून्य) अणु
		status = पढ़ोl(host->base + DAVINCI_MMCST0);
		dev_dbg(mmc_dev(host->mmc),
			"Spurious interrupt 0x%04x\n", status);
		/* Disable the पूर्णांकerrupt from mmcsd */
		ग_लिखोl(0, host->base + DAVINCI_MMCIM);
		वापस IRQ_NONE;
	पूर्ण

	status = पढ़ोl(host->base + DAVINCI_MMCST0);
	qstatus = status;

	/* handle FIFO first when using PIO क्रम data.
	 * bytes_left will decrease to zero as I/O progress and status will
	 * पढ़ो zero over iteration because this controller status
	 * रेजिस्टर(MMCST0) reports any status only once and it is cleared
	 * by पढ़ो. So, it is not unbouned loop even in the हाल of
	 * non-dma.
	 */
	अगर (host->bytes_left && (status & (MMCST0_DXRDY | MMCST0_DRRDY))) अणु
		अचिन्हित दीर्घ im_val;

		/*
		 * If पूर्णांकerrupts fire during the following loop, they will be
		 * handled by the handler, but the PIC will still buffer these.
		 * As a result, the handler will be called again to serve these
		 * needlessly. In order to aव्योम these spurious पूर्णांकerrupts,
		 * keep पूर्णांकerrupts masked during the loop.
		 */
		im_val = पढ़ोl(host->base + DAVINCI_MMCIM);
		ग_लिखोl(0, host->base + DAVINCI_MMCIM);

		करो अणु
			davinci_fअगरo_data_trans(host, rw_threshold);
			status = पढ़ोl(host->base + DAVINCI_MMCST0);
			qstatus |= status;
		पूर्ण जबतक (host->bytes_left &&
			 (status & (MMCST0_DXRDY | MMCST0_DRRDY)));

		/*
		 * If an पूर्णांकerrupt is pending, it is assumed it will fire when
		 * it is unmasked. This assumption is also taken when the MMCIM
		 * is first set. Otherwise, writing to MMCIM after पढ़ोing the
		 * status is race-prone.
		 */
		ग_लिखोl(im_val, host->base + DAVINCI_MMCIM);
	पूर्ण

	अगर (qstatus & MMCST0_DATDNE) अणु
		/* All blocks sent/received, and CRC checks passed */
		अगर (data != शून्य) अणु
			अगर ((host->करो_dma == 0) && (host->bytes_left > 0)) अणु
				/* अगर datasize < rw_threshold
				 * no RX पूर्णांकs are generated
				 */
				davinci_fअगरo_data_trans(host, host->bytes_left);
			पूर्ण
			end_transfer = 1;
			data->bytes_xfered = data->blocks * data->blksz;
		पूर्ण अन्यथा अणु
			dev_err(mmc_dev(host->mmc),
					"DATDNE with no host->data\n");
		पूर्ण
	पूर्ण

	अगर (qstatus & MMCST0_TOUTRD) अणु
		/* Read data समयout */
		data->error = -ETIMEDOUT;
		end_transfer = 1;

		dev_dbg(mmc_dev(host->mmc),
			"read data timeout, status %x\n",
			qstatus);

		davinci_पात_data(host, data);
	पूर्ण

	अगर (qstatus & (MMCST0_CRCWR | MMCST0_CRCRD)) अणु
		/* Data CRC error */
		data->error = -EILSEQ;
		end_transfer = 1;

		/* NOTE:  this controller uses CRCWR to report both CRC
		 * errors and समयouts (on ग_लिखोs).  MMCDRSP values are
		 * only weakly करोcumented, but 0x9f was clearly a समयout
		 * हाल and the two three-bit patterns in various SD specs
		 * (101, 010) aren't part of it ...
		 */
		अगर (qstatus & MMCST0_CRCWR) अणु
			u32 temp = पढ़ोb(host->base + DAVINCI_MMCDRSP);

			अगर (temp == 0x9f)
				data->error = -ETIMEDOUT;
		पूर्ण
		dev_dbg(mmc_dev(host->mmc), "data %s %s error\n",
			(qstatus & MMCST0_CRCWR) ? "write" : "read",
			(data->error == -ETIMEDOUT) ? "timeout" : "CRC");

		davinci_पात_data(host, data);
	पूर्ण

	अगर (qstatus & MMCST0_TOUTRS) अणु
		/* Command समयout */
		अगर (host->cmd) अणु
			dev_dbg(mmc_dev(host->mmc),
				"CMD%d timeout, status %x\n",
				host->cmd->opcode, qstatus);
			host->cmd->error = -ETIMEDOUT;
			अगर (data) अणु
				end_transfer = 1;
				davinci_पात_data(host, data);
			पूर्ण अन्यथा
				end_command = 1;
		पूर्ण
	पूर्ण

	अगर (qstatus & MMCST0_CRCRS) अणु
		/* Command CRC error */
		dev_dbg(mmc_dev(host->mmc), "Command CRC error\n");
		अगर (host->cmd) अणु
			host->cmd->error = -EILSEQ;
			end_command = 1;
		पूर्ण
	पूर्ण

	अगर (qstatus & MMCST0_RSPDNE) अणु
		/* End of command phase */
		end_command = host->cmd ? 1 : 0;
	पूर्ण

	अगर (end_command)
		mmc_davinci_cmd_करोne(host, host->cmd);
	अगर (end_transfer)
		mmc_davinci_xfer_करोne(host, data);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mmc_davinci_get_cd(काष्ठा mmc_host *mmc)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(mmc->parent);
	काष्ठा davinci_mmc_config *config = pdev->dev.platक्रमm_data;

	अगर (config && config->get_cd)
		वापस config->get_cd(pdev->id);

	वापस mmc_gpio_get_cd(mmc);
पूर्ण

अटल पूर्णांक mmc_davinci_get_ro(काष्ठा mmc_host *mmc)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(mmc->parent);
	काष्ठा davinci_mmc_config *config = pdev->dev.platक्रमm_data;

	अगर (config && config->get_ro)
		वापस config->get_ro(pdev->id);

	वापस mmc_gpio_get_ro(mmc);
पूर्ण

अटल व्योम mmc_davinci_enable_sdio_irq(काष्ठा mmc_host *mmc, पूर्णांक enable)
अणु
	काष्ठा mmc_davinci_host *host = mmc_priv(mmc);

	अगर (enable) अणु
		अगर (!(पढ़ोl(host->base + DAVINCI_SDIOST0) & SDIOST0_DAT1_HI)) अणु
			ग_लिखोl(SDIOIST_IOINT, host->base + DAVINCI_SDIOIST);
			mmc_संकेत_sdio_irq(host->mmc);
		पूर्ण अन्यथा अणु
			host->sdio_पूर्णांक = true;
			ग_लिखोl(पढ़ोl(host->base + DAVINCI_SDIOIEN) |
			       SDIOIEN_IOINTEN, host->base + DAVINCI_SDIOIEN);
		पूर्ण
	पूर्ण अन्यथा अणु
		host->sdio_पूर्णांक = false;
		ग_लिखोl(पढ़ोl(host->base + DAVINCI_SDIOIEN) & ~SDIOIEN_IOINTEN,
		       host->base + DAVINCI_SDIOIEN);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops mmc_davinci_ops = अणु
	.request	= mmc_davinci_request,
	.set_ios	= mmc_davinci_set_ios,
	.get_cd		= mmc_davinci_get_cd,
	.get_ro		= mmc_davinci_get_ro,
	.enable_sdio_irq = mmc_davinci_enable_sdio_irq,
पूर्ण;

/*----------------------------------------------------------------------*/

#अगर_घोषित CONFIG_CPU_FREQ
अटल पूर्णांक mmc_davinci_cpufreq_transition(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा mmc_davinci_host *host;
	अचिन्हित पूर्णांक mmc_pclk;
	काष्ठा mmc_host *mmc;
	अचिन्हित दीर्घ flags;

	host = container_of(nb, काष्ठा mmc_davinci_host, freq_transition);
	mmc = host->mmc;
	mmc_pclk = clk_get_rate(host->clk);

	अगर (val == CPUFREQ_POSTCHANGE) अणु
		spin_lock_irqsave(&mmc->lock, flags);
		host->mmc_input_clk = mmc_pclk;
		calculate_clk_भागider(mmc, &mmc->ios);
		spin_unlock_irqrestore(&mmc->lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक mmc_davinci_cpufreq_रेजिस्टर(काष्ठा mmc_davinci_host *host)
अणु
	host->freq_transition.notअगरier_call = mmc_davinci_cpufreq_transition;

	वापस cpufreq_रेजिस्टर_notअगरier(&host->freq_transition,
					 CPUFREQ_TRANSITION_NOTIFIER);
पूर्ण

अटल अंतरभूत व्योम mmc_davinci_cpufreq_deरेजिस्टर(काष्ठा mmc_davinci_host *host)
अणु
	cpufreq_unरेजिस्टर_notअगरier(&host->freq_transition,
				    CPUFREQ_TRANSITION_NOTIFIER);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक mmc_davinci_cpufreq_रेजिस्टर(काष्ठा mmc_davinci_host *host)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mmc_davinci_cpufreq_deरेजिस्टर(काष्ठा mmc_davinci_host *host)
अणु
पूर्ण
#पूर्ण_अगर
अटल व्योम init_mmcsd_host(काष्ठा mmc_davinci_host *host)
अणु

	mmc_davinci_reset_ctrl(host, 1);

	ग_लिखोl(0, host->base + DAVINCI_MMCCLK);
	ग_लिखोl(MMCCLK_CLKEN, host->base + DAVINCI_MMCCLK);

	ग_लिखोl(0x1FFF, host->base + DAVINCI_MMCTOR);
	ग_लिखोl(0xFFFF, host->base + DAVINCI_MMCTOD);

	mmc_davinci_reset_ctrl(host, 0);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id davinci_mmc_devtype[] = अणु
	अणु
		.name	= "dm6441-mmc",
		.driver_data = MMC_CTLR_VERSION_1,
	पूर्ण, अणु
		.name	= "da830-mmc",
		.driver_data = MMC_CTLR_VERSION_2,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, davinci_mmc_devtype);

अटल स्थिर काष्ठा of_device_id davinci_mmc_dt_ids[] = अणु
	अणु
		.compatible = "ti,dm6441-mmc",
		.data = &davinci_mmc_devtype[MMC_CTLR_VERSION_1],
	पूर्ण,
	अणु
		.compatible = "ti,da830-mmc",
		.data = &davinci_mmc_devtype[MMC_CTLR_VERSION_2],
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, davinci_mmc_dt_ids);

अटल पूर्णांक mmc_davinci_parse_pdata(काष्ठा mmc_host *mmc)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(mmc->parent);
	काष्ठा davinci_mmc_config *pdata = pdev->dev.platक्रमm_data;
	काष्ठा mmc_davinci_host *host;
	पूर्णांक ret;

	अगर (!pdata)
		वापस -EINVAL;

	host = mmc_priv(mmc);
	अगर (!host)
		वापस -EINVAL;

	अगर (pdata && pdata->nr_sg)
		host->nr_sg = pdata->nr_sg - 1;

	अगर (pdata && (pdata->wires == 4 || pdata->wires == 0))
		mmc->caps |= MMC_CAP_4_BIT_DATA;

	अगर (pdata && (pdata->wires == 8))
		mmc->caps |= (MMC_CAP_4_BIT_DATA | MMC_CAP_8_BIT_DATA);

	mmc->f_min = 312500;
	mmc->f_max = 25000000;
	अगर (pdata && pdata->max_freq)
		mmc->f_max = pdata->max_freq;
	अगर (pdata && pdata->caps)
		mmc->caps |= pdata->caps;

	/* Register a cd gpio, अगर there is not one, enable polling */
	ret = mmc_gpiod_request_cd(mmc, "cd", 0, false, 0);
	अगर (ret == -EPROBE_DEFER)
		वापस ret;
	अन्यथा अगर (ret)
		mmc->caps |= MMC_CAP_NEEDS_POLL;

	ret = mmc_gpiod_request_ro(mmc, "wp", 0, 0);
	अगर (ret == -EPROBE_DEFER)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_mmcsd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा mmc_davinci_host *host = शून्य;
	काष्ठा mmc_host *mmc = शून्य;
	काष्ठा resource *r, *mem = शून्य;
	पूर्णांक ret, irq;
	माप_प्रकार mem_size;
	स्थिर काष्ठा platक्रमm_device_id *id_entry;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r)
		वापस -ENODEV;
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	mem_size = resource_size(r);
	mem = devm_request_mem_region(&pdev->dev, r->start, mem_size,
				      pdev->name);
	अगर (!mem)
		वापस -EBUSY;

	mmc = mmc_alloc_host(माप(काष्ठा mmc_davinci_host), &pdev->dev);
	अगर (!mmc)
		वापस -ENOMEM;

	host = mmc_priv(mmc);
	host->mmc = mmc;	/* Important */

	host->mem_res = mem;
	host->base = devm_ioremap(&pdev->dev, mem->start, mem_size);
	अगर (!host->base) अणु
		ret = -ENOMEM;
		जाओ ioremap_fail;
	पूर्ण

	host->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(host->clk)) अणु
		ret = PTR_ERR(host->clk);
		जाओ clk_get_fail;
	पूर्ण
	ret = clk_prepare_enable(host->clk);
	अगर (ret)
		जाओ clk_prepare_enable_fail;

	host->mmc_input_clk = clk_get_rate(host->clk);

	match = of_match_device(davinci_mmc_dt_ids, &pdev->dev);
	अगर (match) अणु
		pdev->id_entry = match->data;
		ret = mmc_of_parse(mmc);
		अगर (ret) अणु
			dev_err_probe(&pdev->dev, ret,
				      "could not parse of data\n");
			जाओ parse_fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = mmc_davinci_parse_pdata(mmc);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"could not parse platform data: %d\n", ret);
			जाओ parse_fail;
	पूर्ण	पूर्ण

	अगर (host->nr_sg > MAX_NR_SG || !host->nr_sg)
		host->nr_sg = MAX_NR_SG;

	init_mmcsd_host(host);

	host->use_dma = use_dma;
	host->mmc_irq = irq;
	host->sdio_irq = platक्रमm_get_irq(pdev, 1);

	अगर (host->use_dma) अणु
		ret = davinci_acquire_dma_channels(host);
		अगर (ret == -EPROBE_DEFER)
			जाओ dma_probe_defer;
		अन्यथा अगर (ret)
			host->use_dma = 0;
	पूर्ण

	mmc->caps |= MMC_CAP_WAIT_WHILE_BUSY;

	id_entry = platक्रमm_get_device_id(pdev);
	अगर (id_entry)
		host->version = id_entry->driver_data;

	mmc->ops = &mmc_davinci_ops;
	mmc->ocr_avail = MMC_VDD_32_33 | MMC_VDD_33_34;

	/* With no iommu coalescing pages, each phys_seg is a hw_seg.
	 * Each hw_seg uses one EDMA parameter RAM slot, always one
	 * channel and then usually some linked slots.
	 */
	mmc->max_segs		= MAX_NR_SG;

	/* EDMA limit per hw segment (one or two MBytes) */
	mmc->max_seg_size	= MAX_CCNT * rw_threshold;

	/* MMC/SD controller limits क्रम multiblock requests */
	mmc->max_blk_size	= 4095;  /* BLEN is 12 bits */
	mmc->max_blk_count	= 65535; /* NBLK is 16 bits */
	mmc->max_req_size	= mmc->max_blk_size * mmc->max_blk_count;

	dev_dbg(mmc_dev(host->mmc), "max_segs=%d\n", mmc->max_segs);
	dev_dbg(mmc_dev(host->mmc), "max_blk_size=%d\n", mmc->max_blk_size);
	dev_dbg(mmc_dev(host->mmc), "max_req_size=%d\n", mmc->max_req_size);
	dev_dbg(mmc_dev(host->mmc), "max_seg_size=%d\n", mmc->max_seg_size);

	platक्रमm_set_drvdata(pdev, host);

	ret = mmc_davinci_cpufreq_रेजिस्टर(host);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register cpufreq\n");
		जाओ cpu_freq_fail;
	पूर्ण

	ret = mmc_add_host(mmc);
	अगर (ret < 0)
		जाओ mmc_add_host_fail;

	ret = devm_request_irq(&pdev->dev, irq, mmc_davinci_irq, 0,
			       mmc_hostname(mmc), host);
	अगर (ret)
		जाओ request_irq_fail;

	अगर (host->sdio_irq >= 0) अणु
		ret = devm_request_irq(&pdev->dev, host->sdio_irq,
				       mmc_davinci_sdio_irq, 0,
				       mmc_hostname(mmc), host);
		अगर (!ret)
			mmc->caps |= MMC_CAP_SDIO_IRQ;
	पूर्ण

	नाम_region(mem, mmc_hostname(mmc));

	dev_info(mmc_dev(host->mmc), "Using %s, %d-bit mode\n",
		host->use_dma ? "DMA" : "PIO",
		(mmc->caps & MMC_CAP_4_BIT_DATA) ? 4 : 1);

	वापस 0;

request_irq_fail:
	mmc_हटाओ_host(mmc);
mmc_add_host_fail:
	mmc_davinci_cpufreq_deरेजिस्टर(host);
cpu_freq_fail:
	davinci_release_dma_channels(host);
parse_fail:
dma_probe_defer:
	clk_disable_unprepare(host->clk);
clk_prepare_enable_fail:
clk_get_fail:
ioremap_fail:
	mmc_मुक्त_host(mmc);

	वापस ret;
पूर्ण

अटल पूर्णांक __निकास davinci_mmcsd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_davinci_host *host = platक्रमm_get_drvdata(pdev);

	mmc_हटाओ_host(host->mmc);
	mmc_davinci_cpufreq_deरेजिस्टर(host);
	davinci_release_dma_channels(host);
	clk_disable_unprepare(host->clk);
	mmc_मुक्त_host(host->mmc);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक davinci_mmcsd_suspend(काष्ठा device *dev)
अणु
	काष्ठा mmc_davinci_host *host = dev_get_drvdata(dev);

	ग_लिखोl(0, host->base + DAVINCI_MMCIM);
	mmc_davinci_reset_ctrl(host, 1);
	clk_disable(host->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_mmcsd_resume(काष्ठा device *dev)
अणु
	काष्ठा mmc_davinci_host *host = dev_get_drvdata(dev);

	clk_enable(host->clk);
	mmc_davinci_reset_ctrl(host, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops davinci_mmcsd_pm = अणु
	.suspend        = davinci_mmcsd_suspend,
	.resume         = davinci_mmcsd_resume,
पूर्ण;

#घोषणा davinci_mmcsd_pm_ops (&davinci_mmcsd_pm)
#अन्यथा
#घोषणा davinci_mmcsd_pm_ops शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver davinci_mmcsd_driver = अणु
	.driver		= अणु
		.name	= "davinci_mmc",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.pm	= davinci_mmcsd_pm_ops,
		.of_match_table = davinci_mmc_dt_ids,
	पूर्ण,
	.probe		= davinci_mmcsd_probe,
	.हटाओ		= __निकास_p(davinci_mmcsd_हटाओ),
	.id_table	= davinci_mmc_devtype,
पूर्ण;

module_platक्रमm_driver(davinci_mmcsd_driver);

MODULE_AUTHOR("Texas Instruments India");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MMC/SD driver for Davinci MMC controller");
MODULE_ALIAS("platform:davinci_mmc");

