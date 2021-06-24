<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Driver क्रम the MMC / SD / SDIO cell found in:
 *
 * TC6393XB TC6391XB TC6387XB T7L66XB ASIC3
 *
 * Copyright (C) 2015-19 Renesas Electronics Corporation
 * Copyright (C) 2016-19 Sang Engineering, Wolfram Sang
 * Copyright (C) 2016-17 Horms Solutions, Simon Horman
 * Copyright (C) 2007 Ian Molton
 * Copyright (C) 2004 Ian Molton
 */

#अगर_अघोषित TMIO_MMC_H
#घोषणा TMIO_MMC_H

#समावेश <linux/dmaengine.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/mutex.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>

#घोषणा CTL_SD_CMD 0x00
#घोषणा CTL_ARG_REG 0x04
#घोषणा CTL_STOP_INTERNAL_ACTION 0x08
#घोषणा CTL_XFER_BLK_COUNT 0xa
#घोषणा CTL_RESPONSE 0x0c
/* driver merges STATUS and following STATUS2 */
#घोषणा CTL_STATUS 0x1c
/* driver merges IRQ_MASK and following IRQ_MASK2 */
#घोषणा CTL_IRQ_MASK 0x20
#घोषणा CTL_SD_CARD_CLK_CTL 0x24
#घोषणा CTL_SD_XFER_LEN 0x26
#घोषणा CTL_SD_MEM_CARD_OPT 0x28
#घोषणा CTL_SD_ERROR_DETAIL_STATUS 0x2c
#घोषणा CTL_SD_DATA_PORT 0x30
#घोषणा CTL_TRANSACTION_CTL 0x34
#घोषणा CTL_SDIO_STATUS 0x36
#घोषणा CTL_SDIO_IRQ_MASK 0x38
#घोषणा CTL_DMA_ENABLE 0xd8
#घोषणा CTL_RESET_SD 0xe0
#घोषणा CTL_VERSION 0xe2

/* Definitions क्रम values the CTL_STOP_INTERNAL_ACTION रेजिस्टर can take */
#घोषणा TMIO_STOP_STP		BIT(0)
#घोषणा TMIO_STOP_SEC		BIT(8)

/* Definitions क्रम values the CTL_STATUS रेजिस्टर can take */
#घोषणा TMIO_STAT_CMDRESPEND    BIT(0)
#घोषणा TMIO_STAT_DATAEND       BIT(2)
#घोषणा TMIO_STAT_CARD_REMOVE   BIT(3)
#घोषणा TMIO_STAT_CARD_INSERT   BIT(4)
#घोषणा TMIO_STAT_SIGSTATE      BIT(5)
#घोषणा TMIO_STAT_WRPROTECT     BIT(7)
#घोषणा TMIO_STAT_CARD_REMOVE_A BIT(8)
#घोषणा TMIO_STAT_CARD_INSERT_A BIT(9)
#घोषणा TMIO_STAT_SIGSTATE_A    BIT(10)

/* These beदीर्घ technically to CTL_STATUS2, but the driver merges them */
#घोषणा TMIO_STAT_CMD_IDX_ERR   BIT(16)
#घोषणा TMIO_STAT_CRCFAIL       BIT(17)
#घोषणा TMIO_STAT_STOPBIT_ERR   BIT(18)
#घोषणा TMIO_STAT_DATATIMEOUT   BIT(19)
#घोषणा TMIO_STAT_RXOVERFLOW    BIT(20)
#घोषणा TMIO_STAT_TXUNDERRUN    BIT(21)
#घोषणा TMIO_STAT_CMDTIMEOUT    BIT(22)
#घोषणा TMIO_STAT_DAT0		BIT(23)	/* only known on R-Car so far */
#घोषणा TMIO_STAT_RXRDY         BIT(24)
#घोषणा TMIO_STAT_TXRQ          BIT(25)
#घोषणा TMIO_STAT_ALWAYS_SET_27	BIT(27) /* only known on R-Car 2+ so far */
#घोषणा TMIO_STAT_ILL_FUNC      BIT(29) /* only when !TMIO_MMC_HAS_IDLE_WAIT */
#घोषणा TMIO_STAT_SCLKDIVEN     BIT(29) /* only when TMIO_MMC_HAS_IDLE_WAIT */
#घोषणा TMIO_STAT_CMD_BUSY      BIT(30)
#घोषणा TMIO_STAT_ILL_ACCESS    BIT(31)

/* Definitions क्रम values the CTL_SD_CARD_CLK_CTL रेजिस्टर can take */
#घोषणा	CLK_CTL_DIV_MASK	0xff
#घोषणा	CLK_CTL_SCLKEN		BIT(8)

/* Definitions क्रम values the CTL_SD_MEM_CARD_OPT रेजिस्टर can take */
#घोषणा CARD_OPT_TOP_MASK	0xf0
#घोषणा CARD_OPT_TOP_SHIFT	4
#घोषणा CARD_OPT_EXTOP		BIT(9) /* first appeared on R-Car Gen3 SDHI */
#घोषणा CARD_OPT_WIDTH8		BIT(13)
#घोषणा CARD_OPT_ALWAYS1	BIT(14)
#घोषणा CARD_OPT_WIDTH		BIT(15)

/* Definitions क्रम values the CTL_SDIO_STATUS रेजिस्टर can take */
#घोषणा TMIO_SDIO_STAT_IOIRQ	0x0001
#घोषणा TMIO_SDIO_STAT_EXPUB52	0x4000
#घोषणा TMIO_SDIO_STAT_EXWT	0x8000
#घोषणा TMIO_SDIO_MASK_ALL	0xc007

#घोषणा TMIO_SDIO_SETBITS_MASK	0x0006

/* Definitions क्रम values the CTL_DMA_ENABLE रेजिस्टर can take */
#घोषणा DMA_ENABLE_DMASDRW	BIT(1)

/* Define some IRQ masks */
/* This is the mask used at reset by the chip */
#घोषणा TMIO_MASK_ALL           0x837f031d
#घोषणा TMIO_MASK_ALL_RCAR2	0x8b7f031d
#घोषणा TMIO_MASK_READOP  (TMIO_STAT_RXRDY | TMIO_STAT_DATAEND)
#घोषणा TMIO_MASK_WRITEOP (TMIO_STAT_TXRQ | TMIO_STAT_DATAEND)
#घोषणा TMIO_MASK_CMD     (TMIO_STAT_CMDRESPEND | TMIO_STAT_CMDTIMEOUT | \
		TMIO_STAT_CARD_REMOVE | TMIO_STAT_CARD_INSERT)
#घोषणा TMIO_MASK_IRQ     (TMIO_MASK_READOP | TMIO_MASK_WRITEOP | TMIO_MASK_CMD)

#घोषणा TMIO_MAX_BLK_SIZE 512

काष्ठा पंचांगio_mmc_data;
काष्ठा पंचांगio_mmc_host;

काष्ठा पंचांगio_mmc_dma_ops अणु
	व्योम (*start)(काष्ठा पंचांगio_mmc_host *host, काष्ठा mmc_data *data);
	व्योम (*enable)(काष्ठा पंचांगio_mmc_host *host, bool enable);
	व्योम (*request)(काष्ठा पंचांगio_mmc_host *host,
			काष्ठा पंचांगio_mmc_data *pdata);
	व्योम (*release)(काष्ठा पंचांगio_mmc_host *host);
	व्योम (*पात)(काष्ठा पंचांगio_mmc_host *host);
	व्योम (*dataend)(काष्ठा पंचांगio_mmc_host *host);

	/* optional */
	व्योम (*end)(काष्ठा पंचांगio_mmc_host *host);	/* held host->lock */
पूर्ण;

काष्ठा पंचांगio_mmc_host अणु
	व्योम __iomem *ctl;
	काष्ठा mmc_command      *cmd;
	काष्ठा mmc_request      *mrq;
	काष्ठा mmc_data         *data;
	काष्ठा mmc_host         *mmc;
	काष्ठा mmc_host_ops     ops;

	/* Callbacks क्रम घड़ी / घातer control */
	व्योम (*set_pwr)(काष्ठा platक्रमm_device *host, पूर्णांक state);

	/* pio related stuff */
	काष्ठा scatterlist      *sg_ptr;
	काष्ठा scatterlist      *sg_orig;
	अचिन्हित पूर्णांक            sg_len;
	अचिन्हित पूर्णांक            sg_off;
	अचिन्हित पूर्णांक		bus_shअगरt;

	काष्ठा platक्रमm_device *pdev;
	काष्ठा पंचांगio_mmc_data *pdata;

	/* DMA support */
	bool			dma_on;
	काष्ठा dma_chan		*chan_rx;
	काष्ठा dma_chan		*chan_tx;
	काष्ठा tasklet_काष्ठा	dma_issue;
	काष्ठा scatterlist	bounce_sg;
	u8			*bounce_buf;

	/* Track lost पूर्णांकerrupts */
	काष्ठा delayed_work	delayed_reset_work;
	काष्ठा work_काष्ठा	करोne;

	/* Cache */
	u32			sdcard_irq_mask;
	u32			sdio_irq_mask;
	अचिन्हित पूर्णांक		clk_cache;
	u32			sdcard_irq_setbit_mask;
	u32			sdcard_irq_mask_all;

	spinlock_t		lock;		/* protect host निजी data */
	अचिन्हित दीर्घ		last_req_ts;
	काष्ठा mutex		ios_lock;	/* protect set_ios() context */
	bool			native_hotplug;
	bool			sdio_irq_enabled;

	/* Mandatory callback */
	पूर्णांक (*clk_enable)(काष्ठा पंचांगio_mmc_host *host);
	व्योम (*set_घड़ी)(काष्ठा पंचांगio_mmc_host *host, अचिन्हित पूर्णांक घड़ी);

	/* Optional callbacks */
	व्योम (*clk_disable)(काष्ठा पंचांगio_mmc_host *host);
	पूर्णांक (*multi_io_quirk)(काष्ठा mmc_card *card,
			      अचिन्हित पूर्णांक direction, पूर्णांक blk_size);
	पूर्णांक (*ग_लिखो16_hook)(काष्ठा पंचांगio_mmc_host *host, पूर्णांक addr);
	व्योम (*reset)(काष्ठा पंचांगio_mmc_host *host);
	bool (*check_retune)(काष्ठा पंचांगio_mmc_host *host, काष्ठा mmc_request *mrq);
	व्योम (*fixup_request)(काष्ठा पंचांगio_mmc_host *host, काष्ठा mmc_request *mrq);
	अचिन्हित पूर्णांक (*get_समयout_cycles)(काष्ठा पंचांगio_mmc_host *host);

	व्योम (*prepare_hs400_tuning)(काष्ठा पंचांगio_mmc_host *host);
	व्योम (*hs400_करोwngrade)(काष्ठा पंचांगio_mmc_host *host);
	व्योम (*hs400_complete)(काष्ठा पंचांगio_mmc_host *host);

	स्थिर काष्ठा पंचांगio_mmc_dma_ops *dma_ops;
पूर्ण;

काष्ठा पंचांगio_mmc_host *पंचांगio_mmc_host_alloc(काष्ठा platक्रमm_device *pdev,
					  काष्ठा पंचांगio_mmc_data *pdata);
व्योम पंचांगio_mmc_host_मुक्त(काष्ठा पंचांगio_mmc_host *host);
पूर्णांक पंचांगio_mmc_host_probe(काष्ठा पंचांगio_mmc_host *host);
व्योम पंचांगio_mmc_host_हटाओ(काष्ठा पंचांगio_mmc_host *host);
व्योम पंचांगio_mmc_करो_data_irq(काष्ठा पंचांगio_mmc_host *host);

व्योम पंचांगio_mmc_enable_mmc_irqs(काष्ठा पंचांगio_mmc_host *host, u32 i);
व्योम पंचांगio_mmc_disable_mmc_irqs(काष्ठा पंचांगio_mmc_host *host, u32 i);
irqवापस_t पंचांगio_mmc_irq(पूर्णांक irq, व्योम *devid);

अटल अंतरभूत अक्षर *पंचांगio_mmc_kmap_atomic(काष्ठा scatterlist *sg,
					 अचिन्हित दीर्घ *flags)
अणु
	local_irq_save(*flags);
	वापस kmap_atomic(sg_page(sg)) + sg->offset;
पूर्ण

अटल अंतरभूत व्योम पंचांगio_mmc_kunmap_atomic(काष्ठा scatterlist *sg,
					  अचिन्हित दीर्घ *flags, व्योम *virt)
अणु
	kunmap_atomic(virt - sg->offset);
	local_irq_restore(*flags);
पूर्ण

#अगर_घोषित CONFIG_PM
पूर्णांक पंचांगio_mmc_host_runसमय_suspend(काष्ठा device *dev);
पूर्णांक पंचांगio_mmc_host_runसमय_resume(काष्ठा device *dev);
#पूर्ण_अगर

अटल अंतरभूत u16 sd_ctrl_पढ़ो16(काष्ठा पंचांगio_mmc_host *host, पूर्णांक addr)
अणु
	वापस ioपढ़ो16(host->ctl + (addr << host->bus_shअगरt));
पूर्ण

अटल अंतरभूत व्योम sd_ctrl_पढ़ो16_rep(काष्ठा पंचांगio_mmc_host *host, पूर्णांक addr,
				      u16 *buf, पूर्णांक count)
अणु
	ioपढ़ो16_rep(host->ctl + (addr << host->bus_shअगरt), buf, count);
पूर्ण

अटल अंतरभूत u32 sd_ctrl_पढ़ो16_and_16_as_32(काष्ठा पंचांगio_mmc_host *host,
					      पूर्णांक addr)
अणु
	वापस ioपढ़ो16(host->ctl + (addr << host->bus_shअगरt)) |
	       ioपढ़ो16(host->ctl + ((addr + 2) << host->bus_shअगरt)) << 16;
पूर्ण

अटल अंतरभूत व्योम sd_ctrl_पढ़ो32_rep(काष्ठा पंचांगio_mmc_host *host, पूर्णांक addr,
				      u32 *buf, पूर्णांक count)
अणु
	ioपढ़ो32_rep(host->ctl + (addr << host->bus_shअगरt), buf, count);
पूर्ण

अटल अंतरभूत व्योम sd_ctrl_ग_लिखो16(काष्ठा पंचांगio_mmc_host *host, पूर्णांक addr,
				   u16 val)
अणु
	/* If there is a hook and it वापसs non-zero then there
	 * is an error and the ग_लिखो should be skipped
	 */
	अगर (host->ग_लिखो16_hook && host->ग_लिखो16_hook(host, addr))
		वापस;
	ioग_लिखो16(val, host->ctl + (addr << host->bus_shअगरt));
पूर्ण

अटल अंतरभूत व्योम sd_ctrl_ग_लिखो16_rep(काष्ठा पंचांगio_mmc_host *host, पूर्णांक addr,
				       u16 *buf, पूर्णांक count)
अणु
	ioग_लिखो16_rep(host->ctl + (addr << host->bus_shअगरt), buf, count);
पूर्ण

अटल अंतरभूत व्योम sd_ctrl_ग_लिखो32_as_16_and_16(काष्ठा पंचांगio_mmc_host *host,
						पूर्णांक addr, u32 val)
अणु
	अगर (addr == CTL_IRQ_MASK || addr == CTL_STATUS)
		val |= host->sdcard_irq_setbit_mask;

	ioग_लिखो16(val & 0xffff, host->ctl + (addr << host->bus_shअगरt));
	ioग_लिखो16(val >> 16, host->ctl + ((addr + 2) << host->bus_shअगरt));
पूर्ण

अटल अंतरभूत व्योम sd_ctrl_ग_लिखो32(काष्ठा पंचांगio_mmc_host *host, पूर्णांक addr, u32 val)
अणु
	ioग_लिखो32(val, host->ctl + (addr << host->bus_shअगरt));
पूर्ण

अटल अंतरभूत व्योम sd_ctrl_ग_लिखो32_rep(काष्ठा पंचांगio_mmc_host *host, पूर्णांक addr,
				       स्थिर u32 *buf, पूर्णांक count)
अणु
	ioग_लिखो32_rep(host->ctl + (addr << host->bus_shअगरt), buf, count);
पूर्ण

#पूर्ण_अगर
