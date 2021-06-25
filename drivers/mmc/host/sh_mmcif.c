<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MMCIF eMMC driver.
 *
 * Copyright (C) 2010 Renesas Solutions Corp.
 * Yusuke Goda <yusuke.goda.sx@renesas.com>
 */

/*
 * The MMCIF driver is now processing MMC requests asynchronously, according
 * to the Linux MMC API requirement.
 *
 * The MMCIF driver processes MMC requests in up to 3 stages: command, optional
 * data, and optional stop. To achieve asynchronous processing each of these
 * stages is split पूर्णांकo two halves: a top and a bottom half. The top half
 * initialises the hardware, installs a समयout handler to handle completion
 * समयouts, and वापसs. In हाल of the command stage this immediately वापसs
 * control to the caller, leaving all further processing to run asynchronously.
 * All further request processing is perक्रमmed by the bottom halves.
 *
 * The bottom half further consists of a "hard" IRQ handler, an IRQ handler
 * thपढ़ो, a DMA completion callback, अगर DMA is used, a समयout work, and
 * request- and stage-specअगरic handler methods.
 *
 * Each bottom half run begins with either a hardware पूर्णांकerrupt, a DMA callback
 * invocation, or a समयout work run. In हाल of an error or a successful
 * processing completion, the MMC core is inक्रमmed and the request processing is
 * finished. In हाल processing has to जारी, i.e., अगर data has to be पढ़ो
 * from or written to the card, or अगर a stop command has to be sent, the next
 * top half is called, which perक्रमms the necessary hardware handling and
 * reschedules the समयout work. This वापसs the driver state machine पूर्णांकo the
 * bottom half रुकोing state.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/core.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/mmc/sh_mmcअगर.h>
#समावेश <linux/mmc/slot-gpपन.स>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sh_dma.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/module.h>

#घोषणा DRIVER_NAME	"sh_mmcif"

/* CE_CMD_SET */
#घोषणा CMD_MASK		0x3f000000
#घोषणा CMD_SET_RTYP_NO		((0 << 23) | (0 << 22))
#घोषणा CMD_SET_RTYP_6B		((0 << 23) | (1 << 22)) /* R1/R1b/R3/R4/R5 */
#घोषणा CMD_SET_RTYP_17B	((1 << 23) | (0 << 22)) /* R2 */
#घोषणा CMD_SET_RBSY		(1 << 21) /* R1b */
#घोषणा CMD_SET_CCSEN		(1 << 20)
#घोषणा CMD_SET_WDAT		(1 << 19) /* 1: on data, 0: no data */
#घोषणा CMD_SET_DWEN		(1 << 18) /* 1: ग_लिखो, 0: पढ़ो */
#घोषणा CMD_SET_CMLTE		(1 << 17) /* 1: multi block trans, 0: single */
#घोषणा CMD_SET_CMD12EN		(1 << 16) /* 1: CMD12 स्वतः issue */
#घोषणा CMD_SET_RIDXC_INDEX	((0 << 15) | (0 << 14)) /* index check */
#घोषणा CMD_SET_RIDXC_BITS	((0 << 15) | (1 << 14)) /* check bits check */
#घोषणा CMD_SET_RIDXC_NO	((1 << 15) | (0 << 14)) /* no check */
#घोषणा CMD_SET_CRC7C		((0 << 13) | (0 << 12)) /* CRC7 check*/
#घोषणा CMD_SET_CRC7C_BITS	((0 << 13) | (1 << 12)) /* check bits check*/
#घोषणा CMD_SET_CRC7C_INTERNAL	((1 << 13) | (0 << 12)) /* पूर्णांकernal CRC7 check*/
#घोषणा CMD_SET_CRC16C		(1 << 10) /* 0: CRC16 check*/
#घोषणा CMD_SET_CRCSTE		(1 << 8) /* 1: not receive CRC status */
#घोषणा CMD_SET_TBIT		(1 << 7) /* 1: tran mission bit "Low" */
#घोषणा CMD_SET_OPDM		(1 << 6) /* 1: खोलो/drain */
#घोषणा CMD_SET_CCSH		(1 << 5)
#घोषणा CMD_SET_DARS		(1 << 2) /* Dual Data Rate */
#घोषणा CMD_SET_DATW_1		((0 << 1) | (0 << 0)) /* 1bit */
#घोषणा CMD_SET_DATW_4		((0 << 1) | (1 << 0)) /* 4bit */
#घोषणा CMD_SET_DATW_8		((1 << 1) | (0 << 0)) /* 8bit */

/* CE_CMD_CTRL */
#घोषणा CMD_CTRL_BREAK		(1 << 0)

/* CE_BLOCK_SET */
#घोषणा BLOCK_SIZE_MASK		0x0000ffff

/* CE_INT */
#घोषणा INT_CCSDE		(1 << 29)
#घोषणा INT_CMD12DRE		(1 << 26)
#घोषणा INT_CMD12RBE		(1 << 25)
#घोषणा INT_CMD12CRE		(1 << 24)
#घोषणा INT_DTRANE		(1 << 23)
#घोषणा INT_BUFRE		(1 << 22)
#घोषणा INT_BUFWEN		(1 << 21)
#घोषणा INT_BUFREN		(1 << 20)
#घोषणा INT_CCSRCV		(1 << 19)
#घोषणा INT_RBSYE		(1 << 17)
#घोषणा INT_CRSPE		(1 << 16)
#घोषणा INT_CMDVIO		(1 << 15)
#घोषणा INT_BUFVIO		(1 << 14)
#घोषणा INT_WDATERR		(1 << 11)
#घोषणा INT_RDATERR		(1 << 10)
#घोषणा INT_RIDXERR		(1 << 9)
#घोषणा INT_RSPERR		(1 << 8)
#घोषणा INT_CCSTO		(1 << 5)
#घोषणा INT_CRCSTO		(1 << 4)
#घोषणा INT_WDATTO		(1 << 3)
#घोषणा INT_RDATTO		(1 << 2)
#घोषणा INT_RBSYTO		(1 << 1)
#घोषणा INT_RSPTO		(1 << 0)
#घोषणा INT_ERR_STS		(INT_CMDVIO | INT_BUFVIO | INT_WDATERR |  \
				 INT_RDATERR | INT_RIDXERR | INT_RSPERR | \
				 INT_CCSTO | INT_CRCSTO | INT_WDATTO |	  \
				 INT_RDATTO | INT_RBSYTO | INT_RSPTO)

#घोषणा INT_ALL			(INT_RBSYE | INT_CRSPE | INT_BUFREN |	 \
				 INT_BUFWEN | INT_CMD12DRE | INT_BUFRE | \
				 INT_DTRANE | INT_CMD12RBE | INT_CMD12CRE)

#घोषणा INT_CCS			(INT_CCSTO | INT_CCSRCV | INT_CCSDE)

/* CE_INT_MASK */
#घोषणा MASK_ALL		0x00000000
#घोषणा MASK_MCCSDE		(1 << 29)
#घोषणा MASK_MCMD12DRE		(1 << 26)
#घोषणा MASK_MCMD12RBE		(1 << 25)
#घोषणा MASK_MCMD12CRE		(1 << 24)
#घोषणा MASK_MDTRANE		(1 << 23)
#घोषणा MASK_MBUFRE		(1 << 22)
#घोषणा MASK_MBUFWEN		(1 << 21)
#घोषणा MASK_MBUFREN		(1 << 20)
#घोषणा MASK_MCCSRCV		(1 << 19)
#घोषणा MASK_MRBSYE		(1 << 17)
#घोषणा MASK_MCRSPE		(1 << 16)
#घोषणा MASK_MCMDVIO		(1 << 15)
#घोषणा MASK_MBUFVIO		(1 << 14)
#घोषणा MASK_MWDATERR		(1 << 11)
#घोषणा MASK_MRDATERR		(1 << 10)
#घोषणा MASK_MRIDXERR		(1 << 9)
#घोषणा MASK_MRSPERR		(1 << 8)
#घोषणा MASK_MCCSTO		(1 << 5)
#घोषणा MASK_MCRCSTO		(1 << 4)
#घोषणा MASK_MWDATTO		(1 << 3)
#घोषणा MASK_MRDATTO		(1 << 2)
#घोषणा MASK_MRBSYTO		(1 << 1)
#घोषणा MASK_MRSPTO		(1 << 0)

#घोषणा MASK_START_CMD		(MASK_MCMDVIO | MASK_MBUFVIO | MASK_MWDATERR | \
				 MASK_MRDATERR | MASK_MRIDXERR | MASK_MRSPERR | \
				 MASK_MCRCSTO | MASK_MWDATTO | \
				 MASK_MRDATTO | MASK_MRBSYTO | MASK_MRSPTO)

#घोषणा MASK_CLEAN		(INT_ERR_STS | MASK_MRBSYE | MASK_MCRSPE |	\
				 MASK_MBUFREN | MASK_MBUFWEN |			\
				 MASK_MCMD12DRE | MASK_MBUFRE | MASK_MDTRANE |	\
				 MASK_MCMD12RBE | MASK_MCMD12CRE)

/* CE_HOST_STS1 */
#घोषणा STS1_CMDSEQ		(1 << 31)

/* CE_HOST_STS2 */
#घोषणा STS2_CRCSTE		(1 << 31)
#घोषणा STS2_CRC16E		(1 << 30)
#घोषणा STS2_AC12CRCE		(1 << 29)
#घोषणा STS2_RSPCRC7E		(1 << 28)
#घोषणा STS2_CRCSTEBE		(1 << 27)
#घोषणा STS2_RDATEBE		(1 << 26)
#घोषणा STS2_AC12REBE		(1 << 25)
#घोषणा STS2_RSPEBE		(1 << 24)
#घोषणा STS2_AC12IDXE		(1 << 23)
#घोषणा STS2_RSPIDXE		(1 << 22)
#घोषणा STS2_CCSTO		(1 << 15)
#घोषणा STS2_RDATTO		(1 << 14)
#घोषणा STS2_DATBSYTO		(1 << 13)
#घोषणा STS2_CRCSTTO		(1 << 12)
#घोषणा STS2_AC12BSYTO		(1 << 11)
#घोषणा STS2_RSPBSYTO		(1 << 10)
#घोषणा STS2_AC12RSPTO		(1 << 9)
#घोषणा STS2_RSPTO		(1 << 8)
#घोषणा STS2_CRC_ERR		(STS2_CRCSTE | STS2_CRC16E |		\
				 STS2_AC12CRCE | STS2_RSPCRC7E | STS2_CRCSTEBE)
#घोषणा STS2_TIMEOUT_ERR	(STS2_CCSTO | STS2_RDATTO |		\
				 STS2_DATBSYTO | STS2_CRCSTTO |		\
				 STS2_AC12BSYTO | STS2_RSPBSYTO |	\
				 STS2_AC12RSPTO | STS2_RSPTO)

#घोषणा CLKDEV_EMMC_DATA	52000000 /* 52 MHz */
#घोषणा CLKDEV_MMC_DATA		20000000 /* 20 MHz */
#घोषणा CLKDEV_INIT		400000   /* 400 kHz */

क्रमागत sh_mmcअगर_state अणु
	STATE_IDLE,
	STATE_REQUEST,
	STATE_IOS,
	STATE_TIMEOUT,
पूर्ण;

क्रमागत sh_mmcअगर_रुको_क्रम अणु
	MMCIF_WAIT_FOR_REQUEST,
	MMCIF_WAIT_FOR_CMD,
	MMCIF_WAIT_FOR_MREAD,
	MMCIF_WAIT_FOR_MWRITE,
	MMCIF_WAIT_FOR_READ,
	MMCIF_WAIT_FOR_WRITE,
	MMCIF_WAIT_FOR_READ_END,
	MMCIF_WAIT_FOR_WRITE_END,
	MMCIF_WAIT_FOR_STOP,
पूर्ण;

/*
 * dअगरference क्रम each SoC
 */
काष्ठा sh_mmcअगर_host अणु
	काष्ठा mmc_host *mmc;
	काष्ठा mmc_request *mrq;
	काष्ठा platक्रमm_device *pd;
	काष्ठा clk *clk;
	पूर्णांक bus_width;
	अचिन्हित अक्षर timing;
	bool sd_error;
	bool dying;
	दीर्घ समयout;
	व्योम __iomem *addr;
	u32 *pio_ptr;
	spinlock_t lock;		/* protect sh_mmcअगर_host::state */
	क्रमागत sh_mmcअगर_state state;
	क्रमागत sh_mmcअगर_रुको_क्रम रुको_क्रम;
	काष्ठा delayed_work समयout_work;
	माप_प्रकार blocksize;
	पूर्णांक sg_idx;
	पूर्णांक sg_blkidx;
	bool घातer;
	bool ccs_enable;		/* Command Completion Signal support */
	bool clk_ctrl2_enable;
	काष्ठा mutex thपढ़ो_lock;
	u32 clkभाग_map;         /* see CE_CLK_CTRL::CLKDIV */

	/* DMA support */
	काष्ठा dma_chan		*chan_rx;
	काष्ठा dma_chan		*chan_tx;
	काष्ठा completion	dma_complete;
	bool			dma_active;
पूर्ण;

अटल स्थिर काष्ठा of_device_id sh_mmcअगर_of_match[] = अणु
	अणु .compatible = "renesas,sh-mmcif" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sh_mmcअगर_of_match);

#घोषणा sh_mmcअगर_host_to_dev(host) (&host->pd->dev)

अटल अंतरभूत व्योम sh_mmcअगर_bitset(काष्ठा sh_mmcअगर_host *host,
					अचिन्हित पूर्णांक reg, u32 val)
अणु
	ग_लिखोl(val | पढ़ोl(host->addr + reg), host->addr + reg);
पूर्ण

अटल अंतरभूत व्योम sh_mmcअगर_bitclr(काष्ठा sh_mmcअगर_host *host,
					अचिन्हित पूर्णांक reg, u32 val)
अणु
	ग_लिखोl(~val & पढ़ोl(host->addr + reg), host->addr + reg);
पूर्ण

अटल व्योम sh_mmcअगर_dma_complete(व्योम *arg)
अणु
	काष्ठा sh_mmcअगर_host *host = arg;
	काष्ठा mmc_request *mrq = host->mrq;
	काष्ठा device *dev = sh_mmcअगर_host_to_dev(host);

	dev_dbg(dev, "Command completed\n");

	अगर (WARN(!mrq || !mrq->data, "%s: NULL data in DMA completion!\n",
		 dev_name(dev)))
		वापस;

	complete(&host->dma_complete);
पूर्ण

अटल व्योम sh_mmcअगर_start_dma_rx(काष्ठा sh_mmcअगर_host *host)
अणु
	काष्ठा mmc_data *data = host->mrq->data;
	काष्ठा scatterlist *sg = data->sg;
	काष्ठा dma_async_tx_descriptor *desc = शून्य;
	काष्ठा dma_chan *chan = host->chan_rx;
	काष्ठा device *dev = sh_mmcअगर_host_to_dev(host);
	dma_cookie_t cookie = -EINVAL;
	पूर्णांक ret;

	ret = dma_map_sg(chan->device->dev, sg, data->sg_len,
			 DMA_FROM_DEVICE);
	अगर (ret > 0) अणु
		host->dma_active = true;
		desc = dmaengine_prep_slave_sg(chan, sg, ret,
			DMA_DEV_TO_MEM, DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	पूर्ण

	अगर (desc) अणु
		desc->callback = sh_mmcअगर_dma_complete;
		desc->callback_param = host;
		cookie = dmaengine_submit(desc);
		sh_mmcअगर_bitset(host, MMCIF_CE_BUF_ACC, BUF_ACC_DMAREN);
		dma_async_issue_pending(chan);
	पूर्ण
	dev_dbg(dev, "%s(): mapped %d -> %d, cookie %d\n",
		__func__, data->sg_len, ret, cookie);

	अगर (!desc) अणु
		/* DMA failed, fall back to PIO */
		अगर (ret >= 0)
			ret = -EIO;
		host->chan_rx = शून्य;
		host->dma_active = false;
		dma_release_channel(chan);
		/* Free the Tx channel too */
		chan = host->chan_tx;
		अगर (chan) अणु
			host->chan_tx = शून्य;
			dma_release_channel(chan);
		पूर्ण
		dev_warn(dev,
			 "DMA failed: %d, falling back to PIO\n", ret);
		sh_mmcअगर_bitclr(host, MMCIF_CE_BUF_ACC, BUF_ACC_DMAREN | BUF_ACC_DMAWEN);
	पूर्ण

	dev_dbg(dev, "%s(): desc %p, cookie %d, sg[%d]\n", __func__,
		desc, cookie, data->sg_len);
पूर्ण

अटल व्योम sh_mmcअगर_start_dma_tx(काष्ठा sh_mmcअगर_host *host)
अणु
	काष्ठा mmc_data *data = host->mrq->data;
	काष्ठा scatterlist *sg = data->sg;
	काष्ठा dma_async_tx_descriptor *desc = शून्य;
	काष्ठा dma_chan *chan = host->chan_tx;
	काष्ठा device *dev = sh_mmcअगर_host_to_dev(host);
	dma_cookie_t cookie = -EINVAL;
	पूर्णांक ret;

	ret = dma_map_sg(chan->device->dev, sg, data->sg_len,
			 DMA_TO_DEVICE);
	अगर (ret > 0) अणु
		host->dma_active = true;
		desc = dmaengine_prep_slave_sg(chan, sg, ret,
			DMA_MEM_TO_DEV, DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	पूर्ण

	अगर (desc) अणु
		desc->callback = sh_mmcअगर_dma_complete;
		desc->callback_param = host;
		cookie = dmaengine_submit(desc);
		sh_mmcअगर_bitset(host, MMCIF_CE_BUF_ACC, BUF_ACC_DMAWEN);
		dma_async_issue_pending(chan);
	पूर्ण
	dev_dbg(dev, "%s(): mapped %d -> %d, cookie %d\n",
		__func__, data->sg_len, ret, cookie);

	अगर (!desc) अणु
		/* DMA failed, fall back to PIO */
		अगर (ret >= 0)
			ret = -EIO;
		host->chan_tx = शून्य;
		host->dma_active = false;
		dma_release_channel(chan);
		/* Free the Rx channel too */
		chan = host->chan_rx;
		अगर (chan) अणु
			host->chan_rx = शून्य;
			dma_release_channel(chan);
		पूर्ण
		dev_warn(dev,
			 "DMA failed: %d, falling back to PIO\n", ret);
		sh_mmcअगर_bitclr(host, MMCIF_CE_BUF_ACC, BUF_ACC_DMAREN | BUF_ACC_DMAWEN);
	पूर्ण

	dev_dbg(dev, "%s(): desc %p, cookie %d\n", __func__,
		desc, cookie);
पूर्ण

अटल काष्ठा dma_chan *
sh_mmcअगर_request_dma_pdata(काष्ठा sh_mmcअगर_host *host, uपूर्णांकptr_t slave_id)
अणु
	dma_cap_mask_t mask;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);
	अगर (slave_id <= 0)
		वापस शून्य;

	वापस dma_request_channel(mask, shdma_chan_filter, (व्योम *)slave_id);
पूर्ण

अटल पूर्णांक sh_mmcअगर_dma_slave_config(काष्ठा sh_mmcअगर_host *host,
				     काष्ठा dma_chan *chan,
				     क्रमागत dma_transfer_direction direction)
अणु
	काष्ठा resource *res;
	काष्ठा dma_slave_config cfg = अणु 0, पूर्ण;

	res = platक्रमm_get_resource(host->pd, IORESOURCE_MEM, 0);
	cfg.direction = direction;

	अगर (direction == DMA_DEV_TO_MEM) अणु
		cfg.src_addr = res->start + MMCIF_CE_DATA;
		cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	पूर्ण अन्यथा अणु
		cfg.dst_addr = res->start + MMCIF_CE_DATA;
		cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	पूर्ण

	वापस dmaengine_slave_config(chan, &cfg);
पूर्ण

अटल व्योम sh_mmcअगर_request_dma(काष्ठा sh_mmcअगर_host *host)
अणु
	काष्ठा device *dev = sh_mmcअगर_host_to_dev(host);
	host->dma_active = false;

	/* We can only either use DMA क्रम both Tx and Rx or not use it at all */
	अगर (IS_ENABLED(CONFIG_SUPERH) && dev->platक्रमm_data) अणु
		काष्ठा sh_mmcअगर_plat_data *pdata = dev->platक्रमm_data;

		host->chan_tx = sh_mmcअगर_request_dma_pdata(host,
							pdata->slave_id_tx);
		host->chan_rx = sh_mmcअगर_request_dma_pdata(host,
							pdata->slave_id_rx);
	पूर्ण अन्यथा अणु
		host->chan_tx = dma_request_chan(dev, "tx");
		अगर (IS_ERR(host->chan_tx))
			host->chan_tx = शून्य;
		host->chan_rx = dma_request_chan(dev, "rx");
		अगर (IS_ERR(host->chan_rx))
			host->chan_rx = शून्य;
	पूर्ण
	dev_dbg(dev, "%s: got channel TX %p RX %p\n", __func__, host->chan_tx,
		host->chan_rx);

	अगर (!host->chan_tx || !host->chan_rx ||
	    sh_mmcअगर_dma_slave_config(host, host->chan_tx, DMA_MEM_TO_DEV) ||
	    sh_mmcअगर_dma_slave_config(host, host->chan_rx, DMA_DEV_TO_MEM))
		जाओ error;

	वापस;

error:
	अगर (host->chan_tx)
		dma_release_channel(host->chan_tx);
	अगर (host->chan_rx)
		dma_release_channel(host->chan_rx);
	host->chan_tx = host->chan_rx = शून्य;
पूर्ण

अटल व्योम sh_mmcअगर_release_dma(काष्ठा sh_mmcअगर_host *host)
अणु
	sh_mmcअगर_bitclr(host, MMCIF_CE_BUF_ACC, BUF_ACC_DMAREN | BUF_ACC_DMAWEN);
	/* Descriptors are मुक्तd स्वतःmatically */
	अगर (host->chan_tx) अणु
		काष्ठा dma_chan *chan = host->chan_tx;
		host->chan_tx = शून्य;
		dma_release_channel(chan);
	पूर्ण
	अगर (host->chan_rx) अणु
		काष्ठा dma_chan *chan = host->chan_rx;
		host->chan_rx = शून्य;
		dma_release_channel(chan);
	पूर्ण

	host->dma_active = false;
पूर्ण

अटल व्योम sh_mmcअगर_घड़ी_control(काष्ठा sh_mmcअगर_host *host, अचिन्हित पूर्णांक clk)
अणु
	काष्ठा device *dev = sh_mmcअगर_host_to_dev(host);
	काष्ठा sh_mmcअगर_plat_data *p = dev->platक्रमm_data;
	bool sup_pclk = p ? p->sup_pclk : false;
	अचिन्हित पूर्णांक current_clk = clk_get_rate(host->clk);
	अचिन्हित पूर्णांक clkभाग;

	sh_mmcअगर_bitclr(host, MMCIF_CE_CLK_CTRL, CLK_ENABLE);
	sh_mmcअगर_bitclr(host, MMCIF_CE_CLK_CTRL, CLK_CLEAR);

	अगर (!clk)
		वापस;

	अगर (host->clkभाग_map) अणु
		अचिन्हित पूर्णांक freq, best_freq, myclk, भाग, dअगरf_min, dअगरf;
		पूर्णांक i;

		clkभाग = 0;
		dअगरf_min = ~0;
		best_freq = 0;
		क्रम (i = 31; i >= 0; i--) अणु
			अगर (!((1 << i) & host->clkभाग_map))
				जारी;

			/*
			 * clk = parent_freq / भाग
			 * -> parent_freq = clk x भाग
			 */

			भाग = 1 << (i + 1);
			freq = clk_round_rate(host->clk, clk * भाग);
			myclk = freq / भाग;
			dअगरf = (myclk > clk) ? myclk - clk : clk - myclk;

			अगर (dअगरf <= dअगरf_min) अणु
				best_freq = freq;
				clkभाग = i;
				dअगरf_min = dअगरf;
			पूर्ण
		पूर्ण

		dev_dbg(dev, "clk %u/%u (%u, 0x%x)\n",
			(best_freq / (1 << (clkभाग + 1))), clk,
			best_freq, clkभाग);

		clk_set_rate(host->clk, best_freq);
		clkभाग = clkभाग << 16;
	पूर्ण अन्यथा अगर (sup_pclk && clk == current_clk) अणु
		clkभाग = CLK_SUP_PCLK;
	पूर्ण अन्यथा अणु
		clkभाग = (fls(DIV_ROUND_UP(current_clk, clk) - 1) - 1) << 16;
	पूर्ण

	sh_mmcअगर_bitset(host, MMCIF_CE_CLK_CTRL, CLK_CLEAR & clkभाग);
	sh_mmcअगर_bitset(host, MMCIF_CE_CLK_CTRL, CLK_ENABLE);
पूर्ण

अटल व्योम sh_mmcअगर_sync_reset(काष्ठा sh_mmcअगर_host *host)
अणु
	u32 पंचांगp;

	पंचांगp = 0x010f0000 & sh_mmcअगर_पढ़ोl(host->addr, MMCIF_CE_CLK_CTRL);

	sh_mmcअगर_ग_लिखोl(host->addr, MMCIF_CE_VERSION, SOFT_RST_ON);
	sh_mmcअगर_ग_लिखोl(host->addr, MMCIF_CE_VERSION, SOFT_RST_OFF);
	अगर (host->ccs_enable)
		पंचांगp |= SCCSTO_29;
	अगर (host->clk_ctrl2_enable)
		sh_mmcअगर_ग_लिखोl(host->addr, MMCIF_CE_CLK_CTRL2, 0x0F0F0000);
	sh_mmcअगर_bitset(host, MMCIF_CE_CLK_CTRL, पंचांगp |
		SRSPTO_256 | SRBSYTO_29 | SRWDTO_29);
	/* byte swap on */
	sh_mmcअगर_bitset(host, MMCIF_CE_BUF_ACC, BUF_ACC_ATYP);
पूर्ण

अटल पूर्णांक sh_mmcअगर_error_manage(काष्ठा sh_mmcअगर_host *host)
अणु
	काष्ठा device *dev = sh_mmcअगर_host_to_dev(host);
	u32 state1, state2;
	पूर्णांक ret, समयout;

	host->sd_error = false;

	state1 = sh_mmcअगर_पढ़ोl(host->addr, MMCIF_CE_HOST_STS1);
	state2 = sh_mmcअगर_पढ़ोl(host->addr, MMCIF_CE_HOST_STS2);
	dev_dbg(dev, "ERR HOST_STS1 = %08x\n", state1);
	dev_dbg(dev, "ERR HOST_STS2 = %08x\n", state2);

	अगर (state1 & STS1_CMDSEQ) अणु
		sh_mmcअगर_bitset(host, MMCIF_CE_CMD_CTRL, CMD_CTRL_BREAK);
		sh_mmcअगर_bitset(host, MMCIF_CE_CMD_CTRL, ~CMD_CTRL_BREAK);
		क्रम (समयout = 10000; समयout; समयout--) अणु
			अगर (!(sh_mmcअगर_पढ़ोl(host->addr, MMCIF_CE_HOST_STS1)
			      & STS1_CMDSEQ))
				अवरोध;
			mdelay(1);
		पूर्ण
		अगर (!समयout) अणु
			dev_err(dev,
				"Forced end of command sequence timeout err\n");
			वापस -EIO;
		पूर्ण
		sh_mmcअगर_sync_reset(host);
		dev_dbg(dev, "Forced end of command sequence\n");
		वापस -EIO;
	पूर्ण

	अगर (state2 & STS2_CRC_ERR) अणु
		dev_err(dev, " CRC error: state %u, wait %u\n",
			host->state, host->रुको_क्रम);
		ret = -EIO;
	पूर्ण अन्यथा अगर (state2 & STS2_TIMEOUT_ERR) अणु
		dev_err(dev, " Timeout: state %u, wait %u\n",
			host->state, host->रुको_क्रम);
		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		dev_dbg(dev, " End/Index error: state %u, wait %u\n",
			host->state, host->रुको_क्रम);
		ret = -EIO;
	पूर्ण
	वापस ret;
पूर्ण

अटल bool sh_mmcअगर_next_block(काष्ठा sh_mmcअगर_host *host, u32 *p)
अणु
	काष्ठा mmc_data *data = host->mrq->data;

	host->sg_blkidx += host->blocksize;

	/* data->sg->length must be a multiple of host->blocksize? */
	BUG_ON(host->sg_blkidx > data->sg->length);

	अगर (host->sg_blkidx == data->sg->length) अणु
		host->sg_blkidx = 0;
		अगर (++host->sg_idx < data->sg_len)
			host->pio_ptr = sg_virt(++data->sg);
	पूर्ण अन्यथा अणु
		host->pio_ptr = p;
	पूर्ण

	वापस host->sg_idx != data->sg_len;
पूर्ण

अटल व्योम sh_mmcअगर_single_पढ़ो(काष्ठा sh_mmcअगर_host *host,
				 काष्ठा mmc_request *mrq)
अणु
	host->blocksize = (sh_mmcअगर_पढ़ोl(host->addr, MMCIF_CE_BLOCK_SET) &
			   BLOCK_SIZE_MASK) + 3;

	host->रुको_क्रम = MMCIF_WAIT_FOR_READ;

	/* buf पढ़ो enable */
	sh_mmcअगर_bitset(host, MMCIF_CE_INT_MASK, MASK_MBUFREN);
पूर्ण

अटल bool sh_mmcअगर_पढ़ो_block(काष्ठा sh_mmcअगर_host *host)
अणु
	काष्ठा device *dev = sh_mmcअगर_host_to_dev(host);
	काष्ठा mmc_data *data = host->mrq->data;
	u32 *p = sg_virt(data->sg);
	पूर्णांक i;

	अगर (host->sd_error) अणु
		data->error = sh_mmcअगर_error_manage(host);
		dev_dbg(dev, "%s(): %d\n", __func__, data->error);
		वापस false;
	पूर्ण

	क्रम (i = 0; i < host->blocksize / 4; i++)
		*p++ = sh_mmcअगर_पढ़ोl(host->addr, MMCIF_CE_DATA);

	/* buffer पढ़ो end */
	sh_mmcअगर_bitset(host, MMCIF_CE_INT_MASK, MASK_MBUFRE);
	host->रुको_क्रम = MMCIF_WAIT_FOR_READ_END;

	वापस true;
पूर्ण

अटल व्योम sh_mmcअगर_multi_पढ़ो(काष्ठा sh_mmcअगर_host *host,
				काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmc_data *data = mrq->data;

	अगर (!data->sg_len || !data->sg->length)
		वापस;

	host->blocksize = sh_mmcअगर_पढ़ोl(host->addr, MMCIF_CE_BLOCK_SET) &
		BLOCK_SIZE_MASK;

	host->रुको_क्रम = MMCIF_WAIT_FOR_MREAD;
	host->sg_idx = 0;
	host->sg_blkidx = 0;
	host->pio_ptr = sg_virt(data->sg);

	sh_mmcअगर_bitset(host, MMCIF_CE_INT_MASK, MASK_MBUFREN);
पूर्ण

अटल bool sh_mmcअगर_mपढ़ो_block(काष्ठा sh_mmcअगर_host *host)
अणु
	काष्ठा device *dev = sh_mmcअगर_host_to_dev(host);
	काष्ठा mmc_data *data = host->mrq->data;
	u32 *p = host->pio_ptr;
	पूर्णांक i;

	अगर (host->sd_error) अणु
		data->error = sh_mmcअगर_error_manage(host);
		dev_dbg(dev, "%s(): %d\n", __func__, data->error);
		वापस false;
	पूर्ण

	BUG_ON(!data->sg->length);

	क्रम (i = 0; i < host->blocksize / 4; i++)
		*p++ = sh_mmcअगर_पढ़ोl(host->addr, MMCIF_CE_DATA);

	अगर (!sh_mmcअगर_next_block(host, p))
		वापस false;

	sh_mmcअगर_bitset(host, MMCIF_CE_INT_MASK, MASK_MBUFREN);

	वापस true;
पूर्ण

अटल व्योम sh_mmcअगर_single_ग_लिखो(काष्ठा sh_mmcअगर_host *host,
					काष्ठा mmc_request *mrq)
अणु
	host->blocksize = (sh_mmcअगर_पढ़ोl(host->addr, MMCIF_CE_BLOCK_SET) &
			   BLOCK_SIZE_MASK) + 3;

	host->रुको_क्रम = MMCIF_WAIT_FOR_WRITE;

	/* buf ग_लिखो enable */
	sh_mmcअगर_bitset(host, MMCIF_CE_INT_MASK, MASK_MBUFWEN);
पूर्ण

अटल bool sh_mmcअगर_ग_लिखो_block(काष्ठा sh_mmcअगर_host *host)
अणु
	काष्ठा device *dev = sh_mmcअगर_host_to_dev(host);
	काष्ठा mmc_data *data = host->mrq->data;
	u32 *p = sg_virt(data->sg);
	पूर्णांक i;

	अगर (host->sd_error) अणु
		data->error = sh_mmcअगर_error_manage(host);
		dev_dbg(dev, "%s(): %d\n", __func__, data->error);
		वापस false;
	पूर्ण

	क्रम (i = 0; i < host->blocksize / 4; i++)
		sh_mmcअगर_ग_लिखोl(host->addr, MMCIF_CE_DATA, *p++);

	/* buffer ग_लिखो end */
	sh_mmcअगर_bitset(host, MMCIF_CE_INT_MASK, MASK_MDTRANE);
	host->रुको_क्रम = MMCIF_WAIT_FOR_WRITE_END;

	वापस true;
पूर्ण

अटल व्योम sh_mmcअगर_multi_ग_लिखो(काष्ठा sh_mmcअगर_host *host,
				काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmc_data *data = mrq->data;

	अगर (!data->sg_len || !data->sg->length)
		वापस;

	host->blocksize = sh_mmcअगर_पढ़ोl(host->addr, MMCIF_CE_BLOCK_SET) &
		BLOCK_SIZE_MASK;

	host->रुको_क्रम = MMCIF_WAIT_FOR_MWRITE;
	host->sg_idx = 0;
	host->sg_blkidx = 0;
	host->pio_ptr = sg_virt(data->sg);

	sh_mmcअगर_bitset(host, MMCIF_CE_INT_MASK, MASK_MBUFWEN);
पूर्ण

अटल bool sh_mmcअगर_mग_लिखो_block(काष्ठा sh_mmcअगर_host *host)
अणु
	काष्ठा device *dev = sh_mmcअगर_host_to_dev(host);
	काष्ठा mmc_data *data = host->mrq->data;
	u32 *p = host->pio_ptr;
	पूर्णांक i;

	अगर (host->sd_error) अणु
		data->error = sh_mmcअगर_error_manage(host);
		dev_dbg(dev, "%s(): %d\n", __func__, data->error);
		वापस false;
	पूर्ण

	BUG_ON(!data->sg->length);

	क्रम (i = 0; i < host->blocksize / 4; i++)
		sh_mmcअगर_ग_लिखोl(host->addr, MMCIF_CE_DATA, *p++);

	अगर (!sh_mmcअगर_next_block(host, p))
		वापस false;

	sh_mmcअगर_bitset(host, MMCIF_CE_INT_MASK, MASK_MBUFWEN);

	वापस true;
पूर्ण

अटल व्योम sh_mmcअगर_get_response(काष्ठा sh_mmcअगर_host *host,
						काष्ठा mmc_command *cmd)
अणु
	अगर (cmd->flags & MMC_RSP_136) अणु
		cmd->resp[0] = sh_mmcअगर_पढ़ोl(host->addr, MMCIF_CE_RESP3);
		cmd->resp[1] = sh_mmcअगर_पढ़ोl(host->addr, MMCIF_CE_RESP2);
		cmd->resp[2] = sh_mmcअगर_पढ़ोl(host->addr, MMCIF_CE_RESP1);
		cmd->resp[3] = sh_mmcअगर_पढ़ोl(host->addr, MMCIF_CE_RESP0);
	पूर्ण अन्यथा
		cmd->resp[0] = sh_mmcअगर_पढ़ोl(host->addr, MMCIF_CE_RESP0);
पूर्ण

अटल व्योम sh_mmcअगर_get_cmd12response(काष्ठा sh_mmcअगर_host *host,
						काष्ठा mmc_command *cmd)
अणु
	cmd->resp[0] = sh_mmcअगर_पढ़ोl(host->addr, MMCIF_CE_RESP_CMD12);
पूर्ण

अटल u32 sh_mmcअगर_set_cmd(काष्ठा sh_mmcअगर_host *host,
			    काष्ठा mmc_request *mrq)
अणु
	काष्ठा device *dev = sh_mmcअगर_host_to_dev(host);
	काष्ठा mmc_data *data = mrq->data;
	काष्ठा mmc_command *cmd = mrq->cmd;
	u32 opc = cmd->opcode;
	u32 पंचांगp = 0;

	/* Response Type check */
	चयन (mmc_resp_type(cmd)) अणु
	हाल MMC_RSP_NONE:
		पंचांगp |= CMD_SET_RTYP_NO;
		अवरोध;
	हाल MMC_RSP_R1:
	हाल MMC_RSP_R3:
		पंचांगp |= CMD_SET_RTYP_6B;
		अवरोध;
	हाल MMC_RSP_R1B:
		पंचांगp |= CMD_SET_RBSY | CMD_SET_RTYP_6B;
		अवरोध;
	हाल MMC_RSP_R2:
		पंचांगp |= CMD_SET_RTYP_17B;
		अवरोध;
	शेष:
		dev_err(dev, "Unsupported response type.\n");
		अवरोध;
	पूर्ण

	/* WDAT / DATW */
	अगर (data) अणु
		पंचांगp |= CMD_SET_WDAT;
		चयन (host->bus_width) अणु
		हाल MMC_BUS_WIDTH_1:
			पंचांगp |= CMD_SET_DATW_1;
			अवरोध;
		हाल MMC_BUS_WIDTH_4:
			पंचांगp |= CMD_SET_DATW_4;
			अवरोध;
		हाल MMC_BUS_WIDTH_8:
			पंचांगp |= CMD_SET_DATW_8;
			अवरोध;
		शेष:
			dev_err(dev, "Unsupported bus width.\n");
			अवरोध;
		पूर्ण
		चयन (host->timing) अणु
		हाल MMC_TIMING_MMC_DDR52:
			/*
			 * MMC core will only set this timing, अगर the host
			 * advertises the MMC_CAP_1_8V_DDR/MMC_CAP_1_2V_DDR
			 * capability. MMCIF implementations with this
			 * capability, e.g. sh73a0, will have to set it
			 * in their platक्रमm data.
			 */
			पंचांगp |= CMD_SET_DARS;
			अवरोध;
		पूर्ण
	पूर्ण
	/* DWEN */
	अगर (opc == MMC_WRITE_BLOCK || opc == MMC_WRITE_MULTIPLE_BLOCK)
		पंचांगp |= CMD_SET_DWEN;
	/* CMLTE/CMD12EN */
	अगर (opc == MMC_READ_MULTIPLE_BLOCK || opc == MMC_WRITE_MULTIPLE_BLOCK) अणु
		पंचांगp |= CMD_SET_CMLTE | CMD_SET_CMD12EN;
		sh_mmcअगर_bitset(host, MMCIF_CE_BLOCK_SET,
				data->blocks << 16);
	पूर्ण
	/* RIDXC[1:0] check bits */
	अगर (opc == MMC_SEND_OP_COND || opc == MMC_ALL_SEND_CID ||
	    opc == MMC_SEND_CSD || opc == MMC_SEND_CID)
		पंचांगp |= CMD_SET_RIDXC_BITS;
	/* RCRC7C[1:0] check bits */
	अगर (opc == MMC_SEND_OP_COND)
		पंचांगp |= CMD_SET_CRC7C_BITS;
	/* RCRC7C[1:0] पूर्णांकernal CRC7 */
	अगर (opc == MMC_ALL_SEND_CID ||
		opc == MMC_SEND_CSD || opc == MMC_SEND_CID)
		पंचांगp |= CMD_SET_CRC7C_INTERNAL;

	वापस (opc << 24) | पंचांगp;
पूर्ण

अटल पूर्णांक sh_mmcअगर_data_trans(काष्ठा sh_mmcअगर_host *host,
			       काष्ठा mmc_request *mrq, u32 opc)
अणु
	काष्ठा device *dev = sh_mmcअगर_host_to_dev(host);

	चयन (opc) अणु
	हाल MMC_READ_MULTIPLE_BLOCK:
		sh_mmcअगर_multi_पढ़ो(host, mrq);
		वापस 0;
	हाल MMC_WRITE_MULTIPLE_BLOCK:
		sh_mmcअगर_multi_ग_लिखो(host, mrq);
		वापस 0;
	हाल MMC_WRITE_BLOCK:
		sh_mmcअगर_single_ग_लिखो(host, mrq);
		वापस 0;
	हाल MMC_READ_SINGLE_BLOCK:
	हाल MMC_SEND_EXT_CSD:
		sh_mmcअगर_single_पढ़ो(host, mrq);
		वापस 0;
	शेष:
		dev_err(dev, "Unsupported CMD%d\n", opc);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम sh_mmcअगर_start_cmd(काष्ठा sh_mmcअगर_host *host,
			       काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmc_command *cmd = mrq->cmd;
	u32 opc;
	u32 mask = 0;
	अचिन्हित दीर्घ flags;

	अगर (cmd->flags & MMC_RSP_BUSY)
		mask = MASK_START_CMD | MASK_MRBSYE;
	अन्यथा
		mask = MASK_START_CMD | MASK_MCRSPE;

	अगर (host->ccs_enable)
		mask |= MASK_MCCSTO;

	अगर (mrq->data) अणु
		sh_mmcअगर_ग_लिखोl(host->addr, MMCIF_CE_BLOCK_SET, 0);
		sh_mmcअगर_ग_लिखोl(host->addr, MMCIF_CE_BLOCK_SET,
				mrq->data->blksz);
	पूर्ण
	opc = sh_mmcअगर_set_cmd(host, mrq);

	अगर (host->ccs_enable)
		sh_mmcअगर_ग_लिखोl(host->addr, MMCIF_CE_INT, 0xD80430C0);
	अन्यथा
		sh_mmcअगर_ग_लिखोl(host->addr, MMCIF_CE_INT, 0xD80430C0 | INT_CCS);
	sh_mmcअगर_ग_लिखोl(host->addr, MMCIF_CE_INT_MASK, mask);
	/* set arg */
	sh_mmcअगर_ग_लिखोl(host->addr, MMCIF_CE_ARG, cmd->arg);
	/* set cmd */
	spin_lock_irqsave(&host->lock, flags);
	sh_mmcअगर_ग_लिखोl(host->addr, MMCIF_CE_CMD_SET, opc);

	host->रुको_क्रम = MMCIF_WAIT_FOR_CMD;
	schedule_delayed_work(&host->समयout_work, host->समयout);
	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल व्योम sh_mmcअगर_stop_cmd(काष्ठा sh_mmcअगर_host *host,
			      काष्ठा mmc_request *mrq)
अणु
	काष्ठा device *dev = sh_mmcअगर_host_to_dev(host);

	चयन (mrq->cmd->opcode) अणु
	हाल MMC_READ_MULTIPLE_BLOCK:
		sh_mmcअगर_bitset(host, MMCIF_CE_INT_MASK, MASK_MCMD12DRE);
		अवरोध;
	हाल MMC_WRITE_MULTIPLE_BLOCK:
		sh_mmcअगर_bitset(host, MMCIF_CE_INT_MASK, MASK_MCMD12RBE);
		अवरोध;
	शेष:
		dev_err(dev, "unsupported stop cmd\n");
		mrq->stop->error = sh_mmcअगर_error_manage(host);
		वापस;
	पूर्ण

	host->रुको_क्रम = MMCIF_WAIT_FOR_STOP;
पूर्ण

अटल व्योम sh_mmcअगर_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा sh_mmcअगर_host *host = mmc_priv(mmc);
	काष्ठा device *dev = sh_mmcअगर_host_to_dev(host);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);
	अगर (host->state != STATE_IDLE) अणु
		dev_dbg(dev, "%s() rejected, state %u\n",
			__func__, host->state);
		spin_unlock_irqrestore(&host->lock, flags);
		mrq->cmd->error = -EAGAIN;
		mmc_request_करोne(mmc, mrq);
		वापस;
	पूर्ण

	host->state = STATE_REQUEST;
	spin_unlock_irqrestore(&host->lock, flags);

	host->mrq = mrq;

	sh_mmcअगर_start_cmd(host, mrq);
पूर्ण

अटल व्योम sh_mmcअगर_clk_setup(काष्ठा sh_mmcअगर_host *host)
अणु
	काष्ठा device *dev = sh_mmcअगर_host_to_dev(host);

	अगर (host->mmc->f_max) अणु
		अचिन्हित पूर्णांक f_max, f_min = 0, f_min_old;

		f_max = host->mmc->f_max;
		क्रम (f_min_old = f_max; f_min_old > 2;) अणु
			f_min = clk_round_rate(host->clk, f_min_old / 2);
			अगर (f_min == f_min_old)
				अवरोध;
			f_min_old = f_min;
		पूर्ण

		/*
		 * This driver assumes this SoC is R-Car Gen2 or later
		 */
		host->clkभाग_map = 0x3ff;

		host->mmc->f_max = f_max / (1 << ffs(host->clkभाग_map));
		host->mmc->f_min = f_min / (1 << fls(host->clkभाग_map));
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक clk = clk_get_rate(host->clk);

		host->mmc->f_max = clk / 2;
		host->mmc->f_min = clk / 512;
	पूर्ण

	dev_dbg(dev, "clk max/min = %d/%d\n",
		host->mmc->f_max, host->mmc->f_min);
पूर्ण

अटल व्योम sh_mmcअगर_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा sh_mmcअगर_host *host = mmc_priv(mmc);
	काष्ठा device *dev = sh_mmcअगर_host_to_dev(host);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);
	अगर (host->state != STATE_IDLE) अणु
		dev_dbg(dev, "%s() rejected, state %u\n",
			__func__, host->state);
		spin_unlock_irqrestore(&host->lock, flags);
		वापस;
	पूर्ण

	host->state = STATE_IOS;
	spin_unlock_irqrestore(&host->lock, flags);

	चयन (ios->घातer_mode) अणु
	हाल MMC_POWER_UP:
		अगर (!IS_ERR(mmc->supply.vmmc))
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, ios->vdd);
		अगर (!host->घातer) अणु
			clk_prepare_enable(host->clk);
			pm_runसमय_get_sync(dev);
			sh_mmcअगर_sync_reset(host);
			sh_mmcअगर_request_dma(host);
			host->घातer = true;
		पूर्ण
		अवरोध;
	हाल MMC_POWER_OFF:
		अगर (!IS_ERR(mmc->supply.vmmc))
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);
		अगर (host->घातer) अणु
			sh_mmcअगर_घड़ी_control(host, 0);
			sh_mmcअगर_release_dma(host);
			pm_runसमय_put(dev);
			clk_disable_unprepare(host->clk);
			host->घातer = false;
		पूर्ण
		अवरोध;
	हाल MMC_POWER_ON:
		sh_mmcअगर_घड़ी_control(host, ios->घड़ी);
		अवरोध;
	पूर्ण

	host->timing = ios->timing;
	host->bus_width = ios->bus_width;
	host->state = STATE_IDLE;
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops sh_mmcअगर_ops = अणु
	.request	= sh_mmcअगर_request,
	.set_ios	= sh_mmcअगर_set_ios,
	.get_cd		= mmc_gpio_get_cd,
पूर्ण;

अटल bool sh_mmcअगर_end_cmd(काष्ठा sh_mmcअगर_host *host)
अणु
	काष्ठा mmc_command *cmd = host->mrq->cmd;
	काष्ठा mmc_data *data = host->mrq->data;
	काष्ठा device *dev = sh_mmcअगर_host_to_dev(host);
	दीर्घ समय;

	अगर (host->sd_error) अणु
		चयन (cmd->opcode) अणु
		हाल MMC_ALL_SEND_CID:
		हाल MMC_SELECT_CARD:
		हाल MMC_APP_CMD:
			cmd->error = -ETIMEDOUT;
			अवरोध;
		शेष:
			cmd->error = sh_mmcअगर_error_manage(host);
			अवरोध;
		पूर्ण
		dev_dbg(dev, "CMD%d error %d\n",
			cmd->opcode, cmd->error);
		host->sd_error = false;
		वापस false;
	पूर्ण
	अगर (!(cmd->flags & MMC_RSP_PRESENT)) अणु
		cmd->error = 0;
		वापस false;
	पूर्ण

	sh_mmcअगर_get_response(host, cmd);

	अगर (!data)
		वापस false;

	/*
	 * Completion can be संकेतled from DMA callback and error, so, have to
	 * reset here, beक्रमe setting .dma_active
	 */
	init_completion(&host->dma_complete);

	अगर (data->flags & MMC_DATA_READ) अणु
		अगर (host->chan_rx)
			sh_mmcअगर_start_dma_rx(host);
	पूर्ण अन्यथा अणु
		अगर (host->chan_tx)
			sh_mmcअगर_start_dma_tx(host);
	पूर्ण

	अगर (!host->dma_active) अणु
		data->error = sh_mmcअगर_data_trans(host, host->mrq, cmd->opcode);
		वापस !data->error;
	पूर्ण

	/* Running in the IRQ thपढ़ो, can sleep */
	समय = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&host->dma_complete,
							 host->समयout);

	अगर (data->flags & MMC_DATA_READ)
		dma_unmap_sg(host->chan_rx->device->dev,
			     data->sg, data->sg_len,
			     DMA_FROM_DEVICE);
	अन्यथा
		dma_unmap_sg(host->chan_tx->device->dev,
			     data->sg, data->sg_len,
			     DMA_TO_DEVICE);

	अगर (host->sd_error) अणु
		dev_err(host->mmc->parent,
			"Error IRQ while waiting for DMA completion!\n");
		/* Woken up by an error IRQ: पात DMA */
		data->error = sh_mmcअगर_error_manage(host);
	पूर्ण अन्यथा अगर (!समय) अणु
		dev_err(host->mmc->parent, "DMA timeout!\n");
		data->error = -ETIMEDOUT;
	पूर्ण अन्यथा अगर (समय < 0) अणु
		dev_err(host->mmc->parent,
			"wait_for_completion_...() error %ld!\n", समय);
		data->error = समय;
	पूर्ण
	sh_mmcअगर_bitclr(host, MMCIF_CE_BUF_ACC,
			BUF_ACC_DMAREN | BUF_ACC_DMAWEN);
	host->dma_active = false;

	अगर (data->error) अणु
		data->bytes_xfered = 0;
		/* Abort DMA */
		अगर (data->flags & MMC_DATA_READ)
			dmaengine_terminate_all(host->chan_rx);
		अन्यथा
			dmaengine_terminate_all(host->chan_tx);
	पूर्ण

	वापस false;
पूर्ण

अटल irqवापस_t sh_mmcअगर_irqt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sh_mmcअगर_host *host = dev_id;
	काष्ठा mmc_request *mrq;
	काष्ठा device *dev = sh_mmcअगर_host_to_dev(host);
	bool रुको = false;
	अचिन्हित दीर्घ flags;
	पूर्णांक रुको_work;

	spin_lock_irqsave(&host->lock, flags);
	रुको_work = host->रुको_क्रम;
	spin_unlock_irqrestore(&host->lock, flags);

	cancel_delayed_work_sync(&host->समयout_work);

	mutex_lock(&host->thपढ़ो_lock);

	mrq = host->mrq;
	अगर (!mrq) अणु
		dev_dbg(dev, "IRQ thread state %u, wait %u: NULL mrq!\n",
			host->state, host->रुको_क्रम);
		mutex_unlock(&host->thपढ़ो_lock);
		वापस IRQ_HANDLED;
	पूर्ण

	/*
	 * All handlers वापस true, अगर processing जारीs, and false, अगर the
	 * request has to be completed - successfully or not
	 */
	चयन (रुको_work) अणु
	हाल MMCIF_WAIT_FOR_REQUEST:
		/* We're too late, the समयout has alपढ़ोy kicked in */
		mutex_unlock(&host->thपढ़ो_lock);
		वापस IRQ_HANDLED;
	हाल MMCIF_WAIT_FOR_CMD:
		/* Wait क्रम data? */
		रुको = sh_mmcअगर_end_cmd(host);
		अवरोध;
	हाल MMCIF_WAIT_FOR_MREAD:
		/* Wait क्रम more data? */
		रुको = sh_mmcअगर_mपढ़ो_block(host);
		अवरोध;
	हाल MMCIF_WAIT_FOR_READ:
		/* Wait क्रम data end? */
		रुको = sh_mmcअगर_पढ़ो_block(host);
		अवरोध;
	हाल MMCIF_WAIT_FOR_MWRITE:
		/* Wait data to ग_लिखो? */
		रुको = sh_mmcअगर_mग_लिखो_block(host);
		अवरोध;
	हाल MMCIF_WAIT_FOR_WRITE:
		/* Wait क्रम data end? */
		रुको = sh_mmcअगर_ग_लिखो_block(host);
		अवरोध;
	हाल MMCIF_WAIT_FOR_STOP:
		अगर (host->sd_error) अणु
			mrq->stop->error = sh_mmcअगर_error_manage(host);
			dev_dbg(dev, "%s(): %d\n", __func__, mrq->stop->error);
			अवरोध;
		पूर्ण
		sh_mmcअगर_get_cmd12response(host, mrq->stop);
		mrq->stop->error = 0;
		अवरोध;
	हाल MMCIF_WAIT_FOR_READ_END:
	हाल MMCIF_WAIT_FOR_WRITE_END:
		अगर (host->sd_error) अणु
			mrq->data->error = sh_mmcअगर_error_manage(host);
			dev_dbg(dev, "%s(): %d\n", __func__, mrq->data->error);
		पूर्ण
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	अगर (रुको) अणु
		schedule_delayed_work(&host->समयout_work, host->समयout);
		/* Wait क्रम more data */
		mutex_unlock(&host->thपढ़ो_lock);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (host->रुको_क्रम != MMCIF_WAIT_FOR_STOP) अणु
		काष्ठा mmc_data *data = mrq->data;
		अगर (!mrq->cmd->error && data && !data->error)
			data->bytes_xfered =
				data->blocks * data->blksz;

		अगर (mrq->stop && !mrq->cmd->error && (!data || !data->error)) अणु
			sh_mmcअगर_stop_cmd(host, mrq);
			अगर (!mrq->stop->error) अणु
				schedule_delayed_work(&host->समयout_work, host->समयout);
				mutex_unlock(&host->thपढ़ो_lock);
				वापस IRQ_HANDLED;
			पूर्ण
		पूर्ण
	पूर्ण

	host->रुको_क्रम = MMCIF_WAIT_FOR_REQUEST;
	host->state = STATE_IDLE;
	host->mrq = शून्य;
	mmc_request_करोne(host->mmc, mrq);

	mutex_unlock(&host->thपढ़ो_lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sh_mmcअगर_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sh_mmcअगर_host *host = dev_id;
	काष्ठा device *dev = sh_mmcअगर_host_to_dev(host);
	u32 state, mask;

	state = sh_mmcअगर_पढ़ोl(host->addr, MMCIF_CE_INT);
	mask = sh_mmcअगर_पढ़ोl(host->addr, MMCIF_CE_INT_MASK);
	अगर (host->ccs_enable)
		sh_mmcअगर_ग_लिखोl(host->addr, MMCIF_CE_INT, ~(state & mask));
	अन्यथा
		sh_mmcअगर_ग_लिखोl(host->addr, MMCIF_CE_INT, INT_CCS | ~(state & mask));
	sh_mmcअगर_bitclr(host, MMCIF_CE_INT_MASK, state & MASK_CLEAN);

	अगर (state & ~MASK_CLEAN)
		dev_dbg(dev, "IRQ state = 0x%08x incompletely cleared\n",
			state);

	अगर (state & INT_ERR_STS || state & ~INT_ALL) अणु
		host->sd_error = true;
		dev_dbg(dev, "int err state = 0x%08x\n", state);
	पूर्ण
	अगर (state & ~(INT_CMD12RBE | INT_CMD12CRE)) अणु
		अगर (!host->mrq)
			dev_dbg(dev, "NULL IRQ state = 0x%08x\n", state);
		अगर (!host->dma_active)
			वापस IRQ_WAKE_THREAD;
		अन्यथा अगर (host->sd_error)
			sh_mmcअगर_dma_complete(host);
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "Unexpected IRQ 0x%x\n", state);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sh_mmcअगर_समयout_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *d = to_delayed_work(work);
	काष्ठा sh_mmcअगर_host *host = container_of(d, काष्ठा sh_mmcअगर_host, समयout_work);
	काष्ठा mmc_request *mrq = host->mrq;
	काष्ठा device *dev = sh_mmcअगर_host_to_dev(host);
	अचिन्हित दीर्घ flags;

	अगर (host->dying)
		/* Don't run after mmc_हटाओ_host() */
		वापस;

	spin_lock_irqsave(&host->lock, flags);
	अगर (host->state == STATE_IDLE) अणु
		spin_unlock_irqrestore(&host->lock, flags);
		वापस;
	पूर्ण

	dev_err(dev, "Timeout waiting for %u on CMD%u\n",
		host->रुको_क्रम, mrq->cmd->opcode);

	host->state = STATE_TIMEOUT;
	spin_unlock_irqrestore(&host->lock, flags);

	/*
	 * Handle races with cancel_delayed_work(), unless
	 * cancel_delayed_work_sync() is used
	 */
	चयन (host->रुको_क्रम) अणु
	हाल MMCIF_WAIT_FOR_CMD:
		mrq->cmd->error = sh_mmcअगर_error_manage(host);
		अवरोध;
	हाल MMCIF_WAIT_FOR_STOP:
		mrq->stop->error = sh_mmcअगर_error_manage(host);
		अवरोध;
	हाल MMCIF_WAIT_FOR_MREAD:
	हाल MMCIF_WAIT_FOR_MWRITE:
	हाल MMCIF_WAIT_FOR_READ:
	हाल MMCIF_WAIT_FOR_WRITE:
	हाल MMCIF_WAIT_FOR_READ_END:
	हाल MMCIF_WAIT_FOR_WRITE_END:
		mrq->data->error = sh_mmcअगर_error_manage(host);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	host->state = STATE_IDLE;
	host->रुको_क्रम = MMCIF_WAIT_FOR_REQUEST;
	host->mrq = शून्य;
	mmc_request_करोne(host->mmc, mrq);
पूर्ण

अटल व्योम sh_mmcअगर_init_ocr(काष्ठा sh_mmcअगर_host *host)
अणु
	काष्ठा device *dev = sh_mmcअगर_host_to_dev(host);
	काष्ठा sh_mmcअगर_plat_data *pd = dev->platक्रमm_data;
	काष्ठा mmc_host *mmc = host->mmc;

	mmc_regulator_get_supply(mmc);

	अगर (!pd)
		वापस;

	अगर (!mmc->ocr_avail)
		mmc->ocr_avail = pd->ocr;
	अन्यथा अगर (pd->ocr)
		dev_warn(mmc_dev(mmc), "Platform OCR mask is ignored\n");
पूर्ण

अटल पूर्णांक sh_mmcअगर_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0, irq[2];
	काष्ठा mmc_host *mmc;
	काष्ठा sh_mmcअगर_host *host;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sh_mmcअगर_plat_data *pd = dev->platक्रमm_data;
	व्योम __iomem *reg;
	स्थिर अक्षर *name;

	irq[0] = platक्रमm_get_irq(pdev, 0);
	irq[1] = platक्रमm_get_irq_optional(pdev, 1);
	अगर (irq[0] < 0)
		वापस -ENXIO;

	reg = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(reg))
		वापस PTR_ERR(reg);

	mmc = mmc_alloc_host(माप(काष्ठा sh_mmcअगर_host), dev);
	अगर (!mmc)
		वापस -ENOMEM;

	ret = mmc_of_parse(mmc);
	अगर (ret < 0)
		जाओ err_host;

	host		= mmc_priv(mmc);
	host->mmc	= mmc;
	host->addr	= reg;
	host->समयout	= msecs_to_jअगरfies(10000);
	host->ccs_enable = true;
	host->clk_ctrl2_enable = false;

	host->pd = pdev;

	spin_lock_init(&host->lock);

	mmc->ops = &sh_mmcअगर_ops;
	sh_mmcअगर_init_ocr(host);

	mmc->caps |= MMC_CAP_MMC_HIGHSPEED | MMC_CAP_WAIT_WHILE_BUSY;
	mmc->caps2 |= MMC_CAP2_NO_SD | MMC_CAP2_NO_SDIO;
	mmc->max_busy_समयout = 10000;

	अगर (pd && pd->caps)
		mmc->caps |= pd->caps;
	mmc->max_segs = 32;
	mmc->max_blk_size = 512;
	mmc->max_req_size = PAGE_SIZE * mmc->max_segs;
	mmc->max_blk_count = mmc->max_req_size / mmc->max_blk_size;
	mmc->max_seg_size = mmc->max_req_size;

	platक्रमm_set_drvdata(pdev, host);

	host->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(host->clk)) अणु
		ret = PTR_ERR(host->clk);
		dev_err(dev, "cannot get clock: %d\n", ret);
		जाओ err_host;
	पूर्ण

	ret = clk_prepare_enable(host->clk);
	अगर (ret < 0)
		जाओ err_host;

	sh_mmcअगर_clk_setup(host);

	pm_runसमय_enable(dev);
	host->घातer = false;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0)
		जाओ err_clk;

	INIT_DELAYED_WORK(&host->समयout_work, sh_mmcअगर_समयout_work);

	sh_mmcअगर_sync_reset(host);
	sh_mmcअगर_ग_लिखोl(host->addr, MMCIF_CE_INT_MASK, MASK_ALL);

	name = irq[1] < 0 ? dev_name(dev) : "sh_mmc:error";
	ret = devm_request_thपढ़ोed_irq(dev, irq[0], sh_mmcअगर_पूर्णांकr,
					sh_mmcअगर_irqt, 0, name, host);
	अगर (ret) अणु
		dev_err(dev, "request_irq error (%s)\n", name);
		जाओ err_clk;
	पूर्ण
	अगर (irq[1] >= 0) अणु
		ret = devm_request_thपढ़ोed_irq(dev, irq[1],
						sh_mmcअगर_पूर्णांकr, sh_mmcअगर_irqt,
						0, "sh_mmc:int", host);
		अगर (ret) अणु
			dev_err(dev, "request_irq error (sh_mmc:int)\n");
			जाओ err_clk;
		पूर्ण
	पूर्ण

	mutex_init(&host->thपढ़ो_lock);

	ret = mmc_add_host(mmc);
	अगर (ret < 0)
		जाओ err_clk;

	dev_pm_qos_expose_latency_limit(dev, 100);

	dev_info(dev, "Chip version 0x%04x, clock rate %luMHz\n",
		 sh_mmcअगर_पढ़ोl(host->addr, MMCIF_CE_VERSION) & 0xffff,
		 clk_get_rate(host->clk) / 1000000UL);

	pm_runसमय_put(dev);
	clk_disable_unprepare(host->clk);
	वापस ret;

err_clk:
	clk_disable_unprepare(host->clk);
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);
err_host:
	mmc_मुक्त_host(mmc);
	वापस ret;
पूर्ण

अटल पूर्णांक sh_mmcअगर_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sh_mmcअगर_host *host = platक्रमm_get_drvdata(pdev);

	host->dying = true;
	clk_prepare_enable(host->clk);
	pm_runसमय_get_sync(&pdev->dev);

	dev_pm_qos_hide_latency_limit(&pdev->dev);

	mmc_हटाओ_host(host->mmc);
	sh_mmcअगर_ग_लिखोl(host->addr, MMCIF_CE_INT_MASK, MASK_ALL);

	/*
	 * FIXME: cancel_delayed_work(_sync)() and मुक्त_irq() race with the
	 * mmc_हटाओ_host() call above. But swapping order करोesn't help either
	 * (a query on the linux-mmc mailing list didn't bring any replies).
	 */
	cancel_delayed_work_sync(&host->समयout_work);

	clk_disable_unprepare(host->clk);
	mmc_मुक्त_host(host->mmc);
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sh_mmcअगर_suspend(काष्ठा device *dev)
अणु
	काष्ठा sh_mmcअगर_host *host = dev_get_drvdata(dev);

	pm_runसमय_get_sync(dev);
	sh_mmcअगर_ग_लिखोl(host->addr, MMCIF_CE_INT_MASK, MASK_ALL);
	pm_runसमय_put(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_mmcअगर_resume(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops sh_mmcअगर_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sh_mmcअगर_suspend, sh_mmcअगर_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver sh_mmcअगर_driver = अणु
	.probe		= sh_mmcअगर_probe,
	.हटाओ		= sh_mmcअगर_हटाओ,
	.driver		= अणु
		.name	= DRIVER_NAME,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.pm	= &sh_mmcअगर_dev_pm_ops,
		.of_match_table = sh_mmcअगर_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sh_mmcअगर_driver);

MODULE_DESCRIPTION("SuperH on-chip MMC/eMMC interface driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRIVER_NAME);
MODULE_AUTHOR("Yusuke Goda <yusuke.goda.sx@renesas.com>");
