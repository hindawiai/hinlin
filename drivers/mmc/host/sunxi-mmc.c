<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम sunxi SD/MMC host controllers
 * (C) Copyright 2007-2011 Reuuimlla Technology Co., Ltd.
 * (C) Copyright 2007-2011 Aaron Maoye <leafy.myeh@reuuimllatech.com>
 * (C) Copyright 2013-2014 O2S GmbH <www.o2s.ch>
 * (C) Copyright 2013-2014 David Lanzendथघrfer <david.lanzenकरोerfer@o2s.ch>
 * (C) Copyright 2013-2014 Hans de Goede <hdegoede@redhat.com>
 * (C) Copyright 2017 Sootech SA
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk/sunxi-ng.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/core.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/sd.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/mmc/slot-gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

/* रेजिस्टर offset definitions */
#घोषणा SDXC_REG_GCTRL	(0x00) /* SMC Global Control Register */
#घोषणा SDXC_REG_CLKCR	(0x04) /* SMC Clock Control Register */
#घोषणा SDXC_REG_TMOUT	(0x08) /* SMC Time Out Register */
#घोषणा SDXC_REG_WIDTH	(0x0C) /* SMC Bus Width Register */
#घोषणा SDXC_REG_BLKSZ	(0x10) /* SMC Block Size Register */
#घोषणा SDXC_REG_BCNTR	(0x14) /* SMC Byte Count Register */
#घोषणा SDXC_REG_CMDR	(0x18) /* SMC Command Register */
#घोषणा SDXC_REG_CARG	(0x1C) /* SMC Argument Register */
#घोषणा SDXC_REG_RESP0	(0x20) /* SMC Response Register 0 */
#घोषणा SDXC_REG_RESP1	(0x24) /* SMC Response Register 1 */
#घोषणा SDXC_REG_RESP2	(0x28) /* SMC Response Register 2 */
#घोषणा SDXC_REG_RESP3	(0x2C) /* SMC Response Register 3 */
#घोषणा SDXC_REG_IMASK	(0x30) /* SMC Interrupt Mask Register */
#घोषणा SDXC_REG_MISTA	(0x34) /* SMC Masked Interrupt Status Register */
#घोषणा SDXC_REG_RINTR	(0x38) /* SMC Raw Interrupt Status Register */
#घोषणा SDXC_REG_STAS	(0x3C) /* SMC Status Register */
#घोषणा SDXC_REG_FTRGL	(0x40) /* SMC FIFO Threshold Watermark Registe */
#घोषणा SDXC_REG_FUNS	(0x44) /* SMC Function Select Register */
#घोषणा SDXC_REG_CBCR	(0x48) /* SMC CIU Byte Count Register */
#घोषणा SDXC_REG_BBCR	(0x4C) /* SMC BIU Byte Count Register */
#घोषणा SDXC_REG_DBGC	(0x50) /* SMC Debug Enable Register */
#घोषणा SDXC_REG_HWRST	(0x78) /* SMC Card Hardware Reset क्रम Register */
#घोषणा SDXC_REG_DMAC	(0x80) /* SMC IDMAC Control Register */
#घोषणा SDXC_REG_DLBA	(0x84) /* SMC IDMAC Descriptor List Base Addre */
#घोषणा SDXC_REG_IDST	(0x88) /* SMC IDMAC Status Register */
#घोषणा SDXC_REG_IDIE	(0x8C) /* SMC IDMAC Interrupt Enable Register */
#घोषणा SDXC_REG_CHDA	(0x90)
#घोषणा SDXC_REG_CBDA	(0x94)

/* New रेजिस्टरs पूर्णांकroduced in A64 */
#घोषणा SDXC_REG_A12A		0x058 /* SMC Auto Command 12 Register */
#घोषणा SDXC_REG_SD_NTSR	0x05C /* SMC New Timing Set Register */
#घोषणा SDXC_REG_DRV_DL		0x140 /* Drive Delay Control Register */
#घोषणा SDXC_REG_SAMP_DL_REG	0x144 /* SMC sample delay control */
#घोषणा SDXC_REG_DS_DL_REG	0x148 /* SMC data strobe delay control */

#घोषणा mmc_पढ़ोl(host, reg) \
	पढ़ोl((host)->reg_base + SDXC_##reg)
#घोषणा mmc_ग_लिखोl(host, reg, value) \
	ग_लिखोl((value), (host)->reg_base + SDXC_##reg)

/* global control रेजिस्टर bits */
#घोषणा SDXC_SOFT_RESET			BIT(0)
#घोषणा SDXC_FIFO_RESET			BIT(1)
#घोषणा SDXC_DMA_RESET			BIT(2)
#घोषणा SDXC_INTERRUPT_ENABLE_BIT	BIT(4)
#घोषणा SDXC_DMA_ENABLE_BIT		BIT(5)
#घोषणा SDXC_DEBOUNCE_ENABLE_BIT	BIT(8)
#घोषणा SDXC_POSEDGE_LATCH_DATA		BIT(9)
#घोषणा SDXC_DDR_MODE			BIT(10)
#घोषणा SDXC_MEMORY_ACCESS_DONE		BIT(29)
#घोषणा SDXC_ACCESS_DONE_सूचीECT		BIT(30)
#घोषणा SDXC_ACCESS_BY_AHB		BIT(31)
#घोषणा SDXC_ACCESS_BY_DMA		(0 << 31)
#घोषणा SDXC_HARDWARE_RESET \
	(SDXC_SOFT_RESET | SDXC_FIFO_RESET | SDXC_DMA_RESET)

/* घड़ी control bits */
#घोषणा SDXC_MASK_DATA0			BIT(31)
#घोषणा SDXC_CARD_CLOCK_ON		BIT(16)
#घोषणा SDXC_LOW_POWER_ON		BIT(17)

/* bus width */
#घोषणा SDXC_WIDTH1			0
#घोषणा SDXC_WIDTH4			1
#घोषणा SDXC_WIDTH8			2

/* smc command bits */
#घोषणा SDXC_RESP_EXPIRE		BIT(6)
#घोषणा SDXC_LONG_RESPONSE		BIT(7)
#घोषणा SDXC_CHECK_RESPONSE_CRC		BIT(8)
#घोषणा SDXC_DATA_EXPIRE		BIT(9)
#घोषणा SDXC_WRITE			BIT(10)
#घोषणा SDXC_SEQUENCE_MODE		BIT(11)
#घोषणा SDXC_SEND_AUTO_STOP		BIT(12)
#घोषणा SDXC_WAIT_PRE_OVER		BIT(13)
#घोषणा SDXC_STOP_ABORT_CMD		BIT(14)
#घोषणा SDXC_SEND_INIT_SEQUENCE		BIT(15)
#घोषणा SDXC_UPCLK_ONLY			BIT(21)
#घोषणा SDXC_READ_CEATA_DEV		BIT(22)
#घोषणा SDXC_CCS_EXPIRE			BIT(23)
#घोषणा SDXC_ENABLE_BIT_BOOT		BIT(24)
#घोषणा SDXC_ALT_BOOT_OPTIONS		BIT(25)
#घोषणा SDXC_BOOT_ACK_EXPIRE		BIT(26)
#घोषणा SDXC_BOOT_ABORT			BIT(27)
#घोषणा SDXC_VOLTAGE_SWITCH	        BIT(28)
#घोषणा SDXC_USE_HOLD_REGISTER	        BIT(29)
#घोषणा SDXC_START			BIT(31)

/* पूर्णांकerrupt bits */
#घोषणा SDXC_RESP_ERROR			BIT(1)
#घोषणा SDXC_COMMAND_DONE		BIT(2)
#घोषणा SDXC_DATA_OVER			BIT(3)
#घोषणा SDXC_TX_DATA_REQUEST		BIT(4)
#घोषणा SDXC_RX_DATA_REQUEST		BIT(5)
#घोषणा SDXC_RESP_CRC_ERROR		BIT(6)
#घोषणा SDXC_DATA_CRC_ERROR		BIT(7)
#घोषणा SDXC_RESP_TIMEOUT		BIT(8)
#घोषणा SDXC_DATA_TIMEOUT		BIT(9)
#घोषणा SDXC_VOLTAGE_CHANGE_DONE	BIT(10)
#घोषणा SDXC_FIFO_RUN_ERROR		BIT(11)
#घोषणा SDXC_HARD_WARE_LOCKED		BIT(12)
#घोषणा SDXC_START_BIT_ERROR		BIT(13)
#घोषणा SDXC_AUTO_COMMAND_DONE		BIT(14)
#घोषणा SDXC_END_BIT_ERROR		BIT(15)
#घोषणा SDXC_SDIO_INTERRUPT		BIT(16)
#घोषणा SDXC_CARD_INSERT		BIT(30)
#घोषणा SDXC_CARD_REMOVE		BIT(31)
#घोषणा SDXC_INTERRUPT_ERROR_BIT \
	(SDXC_RESP_ERROR | SDXC_RESP_CRC_ERROR | SDXC_DATA_CRC_ERROR | \
	 SDXC_RESP_TIMEOUT | SDXC_DATA_TIMEOUT | SDXC_FIFO_RUN_ERROR | \
	 SDXC_HARD_WARE_LOCKED | SDXC_START_BIT_ERROR | SDXC_END_BIT_ERROR)
#घोषणा SDXC_INTERRUPT_DONE_BIT \
	(SDXC_AUTO_COMMAND_DONE | SDXC_DATA_OVER | \
	 SDXC_COMMAND_DONE | SDXC_VOLTAGE_CHANGE_DONE)

/* status */
#घोषणा SDXC_RXWL_FLAG			BIT(0)
#घोषणा SDXC_TXWL_FLAG			BIT(1)
#घोषणा SDXC_FIFO_EMPTY			BIT(2)
#घोषणा SDXC_FIFO_FULL			BIT(3)
#घोषणा SDXC_CARD_PRESENT		BIT(8)
#घोषणा SDXC_CARD_DATA_BUSY		BIT(9)
#घोषणा SDXC_DATA_FSM_BUSY		BIT(10)
#घोषणा SDXC_DMA_REQUEST		BIT(31)
#घोषणा SDXC_FIFO_SIZE			16

/* Function select */
#घोषणा SDXC_CEATA_ON			(0xceaa << 16)
#घोषणा SDXC_SEND_IRQ_RESPONSE		BIT(0)
#घोषणा SDXC_SDIO_READ_WAIT		BIT(1)
#घोषणा SDXC_ABORT_READ_DATA		BIT(2)
#घोषणा SDXC_SEND_CCSD			BIT(8)
#घोषणा SDXC_SEND_AUTO_STOPCCSD		BIT(9)
#घोषणा SDXC_CEATA_DEV_IRQ_ENABLE	BIT(10)

/* IDMA controller bus mod bit field */
#घोषणा SDXC_IDMAC_SOFT_RESET		BIT(0)
#घोषणा SDXC_IDMAC_FIX_BURST		BIT(1)
#घोषणा SDXC_IDMAC_IDMA_ON		BIT(7)
#घोषणा SDXC_IDMAC_REFETCH_DES		BIT(31)

/* IDMA status bit field */
#घोषणा SDXC_IDMAC_TRANSMIT_INTERRUPT		BIT(0)
#घोषणा SDXC_IDMAC_RECEIVE_INTERRUPT		BIT(1)
#घोषणा SDXC_IDMAC_FATAL_BUS_ERROR		BIT(2)
#घोषणा SDXC_IDMAC_DESTINATION_INVALID		BIT(4)
#घोषणा SDXC_IDMAC_CARD_ERROR_SUM		BIT(5)
#घोषणा SDXC_IDMAC_NORMAL_INTERRUPT_SUM		BIT(8)
#घोषणा SDXC_IDMAC_ABNORMAL_INTERRUPT_SUM	BIT(9)
#घोषणा SDXC_IDMAC_HOST_ABORT_INTERRUPT		BIT(10)
#घोषणा SDXC_IDMAC_IDLE				(0 << 13)
#घोषणा SDXC_IDMAC_SUSPEND			(1 << 13)
#घोषणा SDXC_IDMAC_DESC_READ			(2 << 13)
#घोषणा SDXC_IDMAC_DESC_CHECK			(3 << 13)
#घोषणा SDXC_IDMAC_READ_REQUEST_WAIT		(4 << 13)
#घोषणा SDXC_IDMAC_WRITE_REQUEST_WAIT		(5 << 13)
#घोषणा SDXC_IDMAC_READ				(6 << 13)
#घोषणा SDXC_IDMAC_WRITE			(7 << 13)
#घोषणा SDXC_IDMAC_DESC_CLOSE			(8 << 13)

/*
* If the idma-des-size-bits of property is ie 13, bufsize bits are:
*  Bits  0-12: buf1 size
*  Bits 13-25: buf2 size
*  Bits 26-31: not used
* Since we only ever set buf1 size, we can simply store it directly.
*/
#घोषणा SDXC_IDMAC_DES0_DIC	BIT(1)  /* disable पूर्णांकerrupt on completion */
#घोषणा SDXC_IDMAC_DES0_LD	BIT(2)  /* last descriptor */
#घोषणा SDXC_IDMAC_DES0_FD	BIT(3)  /* first descriptor */
#घोषणा SDXC_IDMAC_DES0_CH	BIT(4)  /* chain mode */
#घोषणा SDXC_IDMAC_DES0_ER	BIT(5)  /* end of ring */
#घोषणा SDXC_IDMAC_DES0_CES	BIT(30) /* card error summary */
#घोषणा SDXC_IDMAC_DES0_OWN	BIT(31) /* 1-idma owns it, 0-host owns it */

#घोषणा SDXC_CLK_400K		0
#घोषणा SDXC_CLK_25M		1
#घोषणा SDXC_CLK_50M		2
#घोषणा SDXC_CLK_50M_DDR	3
#घोषणा SDXC_CLK_50M_DDR_8BIT	4

#घोषणा SDXC_2X_TIMING_MODE	BIT(31)

#घोषणा SDXC_CAL_START		BIT(15)
#घोषणा SDXC_CAL_DONE		BIT(14)
#घोषणा SDXC_CAL_DL_SHIFT	8
#घोषणा SDXC_CAL_DL_SW_EN	BIT(7)
#घोषणा SDXC_CAL_DL_SW_SHIFT	0
#घोषणा SDXC_CAL_DL_MASK	0x3f

#घोषणा SDXC_CAL_TIMEOUT	3	/* in seconds, 3s is enough*/

काष्ठा sunxi_mmc_clk_delay अणु
	u32 output;
	u32 sample;
पूर्ण;

काष्ठा sunxi_idma_des अणु
	__le32 config;
	__le32 buf_size;
	__le32 buf_addr_ptr1;
	__le32 buf_addr_ptr2;
पूर्ण;

काष्ठा sunxi_mmc_cfg अणु
	u32 idma_des_size_bits;
	u32 idma_des_shअगरt;
	स्थिर काष्ठा sunxi_mmc_clk_delay *clk_delays;

	/* करोes the IP block support स्वतःcalibration? */
	bool can_calibrate;

	/* Does DATA0 needs to be masked जबतक the घड़ी is updated */
	bool mask_data0;

	/*
	 * hardware only supports new timing mode, either due to lack of
	 * a mode चयन in the घड़ी controller, or the mmc controller
	 * is permanently configured in the new timing mode, without the
	 * NTSR mode चयन.
	 */
	bool needs_new_timings;

	/* घड़ी hardware can चयन between old and new timing modes */
	bool ccu_has_timings_चयन;
पूर्ण;

काष्ठा sunxi_mmc_host अणु
	काष्ठा device *dev;
	काष्ठा mmc_host	*mmc;
	काष्ठा reset_control *reset;
	स्थिर काष्ठा sunxi_mmc_cfg *cfg;

	/* IO mapping base */
	व्योम __iomem	*reg_base;

	/* घड़ी management */
	काष्ठा clk	*clk_ahb;
	काष्ठा clk	*clk_mmc;
	काष्ठा clk	*clk_sample;
	काष्ठा clk	*clk_output;

	/* irq */
	spinlock_t	lock;
	पूर्णांक		irq;
	u32		पूर्णांक_sum;
	u32		sdio_imask;

	/* dma */
	dma_addr_t	sg_dma;
	व्योम		*sg_cpu;
	bool		रुको_dma;

	काष्ठा mmc_request *mrq;
	काष्ठा mmc_request *manual_stop_mrq;
	पूर्णांक		ख_त्रुटि;

	/* vqmmc */
	bool		vqmmc_enabled;

	/* timings */
	bool		use_new_timings;
पूर्ण;

अटल पूर्णांक sunxi_mmc_reset_host(काष्ठा sunxi_mmc_host *host)
अणु
	अचिन्हित दीर्घ expire = jअगरfies + msecs_to_jअगरfies(250);
	u32 rval;

	mmc_ग_लिखोl(host, REG_GCTRL, SDXC_HARDWARE_RESET);
	करो अणु
		rval = mmc_पढ़ोl(host, REG_GCTRL);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, expire) && (rval & SDXC_HARDWARE_RESET));

	अगर (rval & SDXC_HARDWARE_RESET) अणु
		dev_err(mmc_dev(host->mmc), "fatal err reset timeout\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_mmc_init_host(काष्ठा sunxi_mmc_host *host)
अणु
	u32 rval;

	अगर (sunxi_mmc_reset_host(host))
		वापस -EIO;

	/*
	 * Burst 8 transfers, RX trigger level: 7, TX trigger level: 8
	 *
	 * TODO: sun9i has a larger FIFO and supports higher trigger values
	 */
	mmc_ग_लिखोl(host, REG_FTRGL, 0x20070008);
	/* Maximum समयout value */
	mmc_ग_लिखोl(host, REG_TMOUT, 0xffffffff);
	/* Unmask SDIO पूर्णांकerrupt अगर needed */
	mmc_ग_लिखोl(host, REG_IMASK, host->sdio_imask);
	/* Clear all pending पूर्णांकerrupts */
	mmc_ग_लिखोl(host, REG_RINTR, 0xffffffff);
	/* Debug रेजिस्टर? unकरोcumented */
	mmc_ग_लिखोl(host, REG_DBGC, 0xdeb);
	/* Enable CEATA support */
	mmc_ग_लिखोl(host, REG_FUNS, SDXC_CEATA_ON);
	/* Set DMA descriptor list base address */
	mmc_ग_लिखोl(host, REG_DLBA, host->sg_dma >> host->cfg->idma_des_shअगरt);

	rval = mmc_पढ़ोl(host, REG_GCTRL);
	rval |= SDXC_INTERRUPT_ENABLE_BIT;
	/* Unकरोcumented, but found in Allwinner code */
	rval &= ~SDXC_ACCESS_DONE_सूचीECT;
	mmc_ग_लिखोl(host, REG_GCTRL, rval);

	वापस 0;
पूर्ण

अटल व्योम sunxi_mmc_init_idma_des(काष्ठा sunxi_mmc_host *host,
				    काष्ठा mmc_data *data)
अणु
	काष्ठा sunxi_idma_des *pdes = (काष्ठा sunxi_idma_des *)host->sg_cpu;
	dma_addr_t next_desc = host->sg_dma;
	पूर्णांक i, max_len = (1 << host->cfg->idma_des_size_bits);

	क्रम (i = 0; i < data->sg_len; i++) अणु
		pdes[i].config = cpu_to_le32(SDXC_IDMAC_DES0_CH |
					     SDXC_IDMAC_DES0_OWN |
					     SDXC_IDMAC_DES0_DIC);

		अगर (data->sg[i].length == max_len)
			pdes[i].buf_size = 0; /* 0 == max_len */
		अन्यथा
			pdes[i].buf_size = cpu_to_le32(data->sg[i].length);

		next_desc += माप(काष्ठा sunxi_idma_des);
		pdes[i].buf_addr_ptr1 =
			cpu_to_le32(sg_dma_address(&data->sg[i]) >>
				    host->cfg->idma_des_shअगरt);
		pdes[i].buf_addr_ptr2 = cpu_to_le32((u32)next_desc >>
						    host->cfg->idma_des_shअगरt);
	पूर्ण

	pdes[0].config |= cpu_to_le32(SDXC_IDMAC_DES0_FD);
	pdes[i - 1].config |= cpu_to_le32(SDXC_IDMAC_DES0_LD |
					  SDXC_IDMAC_DES0_ER);
	pdes[i - 1].config &= cpu_to_le32(~SDXC_IDMAC_DES0_DIC);
	pdes[i - 1].buf_addr_ptr2 = 0;

	/*
	 * Aव्योम the io-store starting the idmac hitting io-mem beक्रमe the
	 * descriptors hit the मुख्य-mem.
	 */
	wmb();
पूर्ण

अटल पूर्णांक sunxi_mmc_map_dma(काष्ठा sunxi_mmc_host *host,
			     काष्ठा mmc_data *data)
अणु
	u32 i, dma_len;
	काष्ठा scatterlist *sg;

	dma_len = dma_map_sg(mmc_dev(host->mmc), data->sg, data->sg_len,
			     mmc_get_dma_dir(data));
	अगर (dma_len == 0) अणु
		dev_err(mmc_dev(host->mmc), "dma_map_sg failed\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम_each_sg(data->sg, sg, data->sg_len, i) अणु
		अगर (sg->offset & 3 || sg->length & 3) अणु
			dev_err(mmc_dev(host->mmc),
				"unaligned scatterlist: os %x length %d\n",
				sg->offset, sg->length);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sunxi_mmc_start_dma(काष्ठा sunxi_mmc_host *host,
				काष्ठा mmc_data *data)
अणु
	u32 rval;

	sunxi_mmc_init_idma_des(host, data);

	rval = mmc_पढ़ोl(host, REG_GCTRL);
	rval |= SDXC_DMA_ENABLE_BIT;
	mmc_ग_लिखोl(host, REG_GCTRL, rval);
	rval |= SDXC_DMA_RESET;
	mmc_ग_लिखोl(host, REG_GCTRL, rval);

	mmc_ग_लिखोl(host, REG_DMAC, SDXC_IDMAC_SOFT_RESET);

	अगर (!(data->flags & MMC_DATA_WRITE))
		mmc_ग_लिखोl(host, REG_IDIE, SDXC_IDMAC_RECEIVE_INTERRUPT);

	mmc_ग_लिखोl(host, REG_DMAC,
		   SDXC_IDMAC_FIX_BURST | SDXC_IDMAC_IDMA_ON);
पूर्ण

अटल व्योम sunxi_mmc_send_manual_stop(काष्ठा sunxi_mmc_host *host,
				       काष्ठा mmc_request *req)
अणु
	u32 arg, cmd_val, ri;
	अचिन्हित दीर्घ expire = jअगरfies + msecs_to_jअगरfies(1000);

	cmd_val = SDXC_START | SDXC_RESP_EXPIRE |
		  SDXC_STOP_ABORT_CMD | SDXC_CHECK_RESPONSE_CRC;

	अगर (req->cmd->opcode == SD_IO_RW_EXTENDED) अणु
		cmd_val |= SD_IO_RW_सूचीECT;
		arg = (1 << 31) | (0 << 28) | (SDIO_CCCR_ABORT << 9) |
		      ((req->cmd->arg >> 28) & 0x7);
	पूर्ण अन्यथा अणु
		cmd_val |= MMC_STOP_TRANSMISSION;
		arg = 0;
	पूर्ण

	mmc_ग_लिखोl(host, REG_CARG, arg);
	mmc_ग_लिखोl(host, REG_CMDR, cmd_val);

	करो अणु
		ri = mmc_पढ़ोl(host, REG_RINTR);
	पूर्ण जबतक (!(ri & (SDXC_COMMAND_DONE | SDXC_INTERRUPT_ERROR_BIT)) &&
		 समय_beक्रमe(jअगरfies, expire));

	अगर (!(ri & SDXC_COMMAND_DONE) || (ri & SDXC_INTERRUPT_ERROR_BIT)) अणु
		dev_err(mmc_dev(host->mmc), "send stop command failed\n");
		अगर (req->stop)
			req->stop->resp[0] = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		अगर (req->stop)
			req->stop->resp[0] = mmc_पढ़ोl(host, REG_RESP0);
	पूर्ण

	mmc_ग_लिखोl(host, REG_RINTR, 0xffff);
पूर्ण

अटल व्योम sunxi_mmc_dump_errinfo(काष्ठा sunxi_mmc_host *host)
अणु
	काष्ठा mmc_command *cmd = host->mrq->cmd;
	काष्ठा mmc_data *data = host->mrq->data;

	/* For some cmds समयout is normal with sd/mmc cards */
	अगर ((host->पूर्णांक_sum & SDXC_INTERRUPT_ERROR_BIT) ==
		SDXC_RESP_TIMEOUT && (cmd->opcode == SD_IO_SEND_OP_COND ||
				      cmd->opcode == SD_IO_RW_सूचीECT))
		वापस;

	dev_dbg(mmc_dev(host->mmc),
		"smc %d err, cmd %d,%s%s%s%s%s%s%s%s%s%s !!\n",
		host->mmc->index, cmd->opcode,
		data ? (data->flags & MMC_DATA_WRITE ? " WR" : " RD") : "",
		host->पूर्णांक_sum & SDXC_RESP_ERROR     ? " RE"     : "",
		host->पूर्णांक_sum & SDXC_RESP_CRC_ERROR  ? " RCE"    : "",
		host->पूर्णांक_sum & SDXC_DATA_CRC_ERROR  ? " DCE"    : "",
		host->पूर्णांक_sum & SDXC_RESP_TIMEOUT ? " RTO"    : "",
		host->पूर्णांक_sum & SDXC_DATA_TIMEOUT ? " DTO"    : "",
		host->पूर्णांक_sum & SDXC_FIFO_RUN_ERROR  ? " FE"     : "",
		host->पूर्णांक_sum & SDXC_HARD_WARE_LOCKED ? " HL"     : "",
		host->पूर्णांक_sum & SDXC_START_BIT_ERROR ? " SBE"    : "",
		host->पूर्णांक_sum & SDXC_END_BIT_ERROR   ? " EBE"    : ""
		);
पूर्ण

/* Called in पूर्णांकerrupt context! */
अटल irqवापस_t sunxi_mmc_finalize_request(काष्ठा sunxi_mmc_host *host)
अणु
	काष्ठा mmc_request *mrq = host->mrq;
	काष्ठा mmc_data *data = mrq->data;
	u32 rval;

	mmc_ग_लिखोl(host, REG_IMASK, host->sdio_imask);
	mmc_ग_लिखोl(host, REG_IDIE, 0);

	अगर (host->पूर्णांक_sum & SDXC_INTERRUPT_ERROR_BIT) अणु
		sunxi_mmc_dump_errinfo(host);
		mrq->cmd->error = -ETIMEDOUT;

		अगर (data) अणु
			data->error = -ETIMEDOUT;
			host->manual_stop_mrq = mrq;
		पूर्ण

		अगर (mrq->stop)
			mrq->stop->error = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		अगर (mrq->cmd->flags & MMC_RSP_136) अणु
			mrq->cmd->resp[0] = mmc_पढ़ोl(host, REG_RESP3);
			mrq->cmd->resp[1] = mmc_पढ़ोl(host, REG_RESP2);
			mrq->cmd->resp[2] = mmc_पढ़ोl(host, REG_RESP1);
			mrq->cmd->resp[3] = mmc_पढ़ोl(host, REG_RESP0);
		पूर्ण अन्यथा अणु
			mrq->cmd->resp[0] = mmc_पढ़ोl(host, REG_RESP0);
		पूर्ण

		अगर (data)
			data->bytes_xfered = data->blocks * data->blksz;
	पूर्ण

	अगर (data) अणु
		mmc_ग_लिखोl(host, REG_IDST, 0x337);
		mmc_ग_लिखोl(host, REG_DMAC, 0);
		rval = mmc_पढ़ोl(host, REG_GCTRL);
		rval |= SDXC_DMA_RESET;
		mmc_ग_लिखोl(host, REG_GCTRL, rval);
		rval &= ~SDXC_DMA_ENABLE_BIT;
		mmc_ग_लिखोl(host, REG_GCTRL, rval);
		rval |= SDXC_FIFO_RESET;
		mmc_ग_लिखोl(host, REG_GCTRL, rval);
		dma_unmap_sg(mmc_dev(host->mmc), data->sg, data->sg_len,
			     mmc_get_dma_dir(data));
	पूर्ण

	mmc_ग_लिखोl(host, REG_RINTR, 0xffff);

	host->mrq = शून्य;
	host->पूर्णांक_sum = 0;
	host->रुको_dma = false;

	वापस host->manual_stop_mrq ? IRQ_WAKE_THREAD : IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sunxi_mmc_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sunxi_mmc_host *host = dev_id;
	काष्ठा mmc_request *mrq;
	u32 msk_पूर्णांक, idma_पूर्णांक;
	bool finalize = false;
	bool sdio_पूर्णांक = false;
	irqवापस_t ret = IRQ_HANDLED;

	spin_lock(&host->lock);

	idma_पूर्णांक  = mmc_पढ़ोl(host, REG_IDST);
	msk_पूर्णांक   = mmc_पढ़ोl(host, REG_MISTA);

	dev_dbg(mmc_dev(host->mmc), "irq: rq %p mi %08x idi %08x\n",
		host->mrq, msk_पूर्णांक, idma_पूर्णांक);

	mrq = host->mrq;
	अगर (mrq) अणु
		अगर (idma_पूर्णांक & SDXC_IDMAC_RECEIVE_INTERRUPT)
			host->रुको_dma = false;

		host->पूर्णांक_sum |= msk_पूर्णांक;

		/* Wait क्रम COMMAND_DONE on RESPONSE_TIMEOUT beक्रमe finalize */
		अगर ((host->पूर्णांक_sum & SDXC_RESP_TIMEOUT) &&
				!(host->पूर्णांक_sum & SDXC_COMMAND_DONE))
			mmc_ग_लिखोl(host, REG_IMASK,
				   host->sdio_imask | SDXC_COMMAND_DONE);
		/* Don't रुको क्रम dma on error */
		अन्यथा अगर (host->पूर्णांक_sum & SDXC_INTERRUPT_ERROR_BIT)
			finalize = true;
		अन्यथा अगर ((host->पूर्णांक_sum & SDXC_INTERRUPT_DONE_BIT) &&
				!host->रुको_dma)
			finalize = true;
	पूर्ण

	अगर (msk_पूर्णांक & SDXC_SDIO_INTERRUPT)
		sdio_पूर्णांक = true;

	mmc_ग_लिखोl(host, REG_RINTR, msk_पूर्णांक);
	mmc_ग_लिखोl(host, REG_IDST, idma_पूर्णांक);

	अगर (finalize)
		ret = sunxi_mmc_finalize_request(host);

	spin_unlock(&host->lock);

	अगर (finalize && ret == IRQ_HANDLED)
		mmc_request_करोne(host->mmc, mrq);

	अगर (sdio_पूर्णांक)
		mmc_संकेत_sdio_irq(host->mmc);

	वापस ret;
पूर्ण

अटल irqवापस_t sunxi_mmc_handle_manual_stop(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sunxi_mmc_host *host = dev_id;
	काष्ठा mmc_request *mrq;
	अचिन्हित दीर्घ अगरlags;

	spin_lock_irqsave(&host->lock, अगरlags);
	mrq = host->manual_stop_mrq;
	spin_unlock_irqrestore(&host->lock, अगरlags);

	अगर (!mrq) अणु
		dev_err(mmc_dev(host->mmc), "no request for manual stop\n");
		वापस IRQ_HANDLED;
	पूर्ण

	dev_err(mmc_dev(host->mmc), "data error, sending stop command\n");

	/*
	 * We will never have more than one outstanding request,
	 * and we करो not complete the request until after
	 * we've cleared host->manual_stop_mrq so we करो not need to
	 * spin lock this function.
	 * Additionally we have रुको states within this function
	 * so having it in a lock is a very bad idea.
	 */
	sunxi_mmc_send_manual_stop(host, mrq);

	spin_lock_irqsave(&host->lock, अगरlags);
	host->manual_stop_mrq = शून्य;
	spin_unlock_irqrestore(&host->lock, अगरlags);

	mmc_request_करोne(host->mmc, mrq);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sunxi_mmc_oclk_onoff(काष्ठा sunxi_mmc_host *host, u32 oclk_en)
अणु
	अचिन्हित दीर्घ expire = jअगरfies + msecs_to_jअगरfies(750);
	u32 rval;

	dev_dbg(mmc_dev(host->mmc), "%sabling the clock\n",
		oclk_en ? "en" : "dis");

	rval = mmc_पढ़ोl(host, REG_CLKCR);
	rval &= ~(SDXC_CARD_CLOCK_ON | SDXC_LOW_POWER_ON | SDXC_MASK_DATA0);

	अगर (oclk_en)
		rval |= SDXC_CARD_CLOCK_ON;
	अगर (host->cfg->mask_data0)
		rval |= SDXC_MASK_DATA0;

	mmc_ग_लिखोl(host, REG_CLKCR, rval);

	rval = SDXC_START | SDXC_UPCLK_ONLY | SDXC_WAIT_PRE_OVER;
	mmc_ग_लिखोl(host, REG_CMDR, rval);

	करो अणु
		rval = mmc_पढ़ोl(host, REG_CMDR);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, expire) && (rval & SDXC_START));

	/* clear irq status bits set by the command */
	mmc_ग_लिखोl(host, REG_RINTR,
		   mmc_पढ़ोl(host, REG_RINTR) & ~SDXC_SDIO_INTERRUPT);

	अगर (rval & SDXC_START) अणु
		dev_err(mmc_dev(host->mmc), "fatal err update clk timeout\n");
		वापस -EIO;
	पूर्ण

	अगर (host->cfg->mask_data0) अणु
		rval = mmc_पढ़ोl(host, REG_CLKCR);
		mmc_ग_लिखोl(host, REG_CLKCR, rval & ~SDXC_MASK_DATA0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_mmc_calibrate(काष्ठा sunxi_mmc_host *host, पूर्णांक reg_off)
अणु
	अगर (!host->cfg->can_calibrate)
		वापस 0;

	/*
	 * FIXME:
	 * This is not clear how the calibration is supposed to work
	 * yet. The best rate have been obtained by simply setting the
	 * delay to 0, as Allwinner करोes in its BSP.
	 *
	 * The only mode that करोesn't have such a delay is HS400, that
	 * is in itself a TODO.
	 */
	ग_लिखोl(SDXC_CAL_DL_SW_EN, host->reg_base + reg_off);

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_mmc_clk_set_phase(काष्ठा sunxi_mmc_host *host,
				   काष्ठा mmc_ios *ios, u32 rate)
अणु
	पूर्णांक index;

	/* clk controller delays not used under new timings mode */
	अगर (host->use_new_timings)
		वापस 0;

	/* some old controllers करोn't support delays */
	अगर (!host->cfg->clk_delays)
		वापस 0;

	/* determine delays */
	अगर (rate <= 400000) अणु
		index = SDXC_CLK_400K;
	पूर्ण अन्यथा अगर (rate <= 25000000) अणु
		index = SDXC_CLK_25M;
	पूर्ण अन्यथा अगर (rate <= 52000000) अणु
		अगर (ios->timing != MMC_TIMING_UHS_DDR50 &&
		    ios->timing != MMC_TIMING_MMC_DDR52) अणु
			index = SDXC_CLK_50M;
		पूर्ण अन्यथा अगर (ios->bus_width == MMC_BUS_WIDTH_8) अणु
			index = SDXC_CLK_50M_DDR_8BIT;
		पूर्ण अन्यथा अणु
			index = SDXC_CLK_50M_DDR;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(mmc_dev(host->mmc), "Invalid clock... returning\n");
		वापस -EINVAL;
	पूर्ण

	clk_set_phase(host->clk_sample, host->cfg->clk_delays[index].sample);
	clk_set_phase(host->clk_output, host->cfg->clk_delays[index].output);

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_mmc_clk_set_rate(काष्ठा sunxi_mmc_host *host,
				  काष्ठा mmc_ios *ios)
अणु
	काष्ठा mmc_host *mmc = host->mmc;
	दीर्घ rate;
	u32 rval, घड़ी = ios->घड़ी, भाग = 1;
	पूर्णांक ret;

	ret = sunxi_mmc_oclk_onoff(host, 0);
	अगर (ret)
		वापस ret;

	/* Our घड़ी is gated now */
	mmc->actual_घड़ी = 0;

	अगर (!ios->घड़ी)
		वापस 0;

	/*
	 * Under the old timing mode, 8 bit DDR requires the module
	 * घड़ी to be द्विगुन the card घड़ी. Under the new timing
	 * mode, all DDR modes require a द्विगुनd module घड़ी.
	 *
	 * We currently only support the standard MMC DDR52 mode.
	 * This block should be updated once support क्रम other DDR
	 * modes is added.
	 */
	अगर (ios->timing == MMC_TIMING_MMC_DDR52 &&
	    (host->use_new_timings ||
	     ios->bus_width == MMC_BUS_WIDTH_8)) अणु
		भाग = 2;
		घड़ी <<= 1;
	पूर्ण

	अगर (host->use_new_timings && host->cfg->ccu_has_timings_चयन) अणु
		ret = sunxi_ccu_set_mmc_timing_mode(host->clk_mmc, true);
		अगर (ret) अणु
			dev_err(mmc_dev(mmc),
				"error setting new timing mode\n");
			वापस ret;
		पूर्ण
	पूर्ण

	rate = clk_round_rate(host->clk_mmc, घड़ी);
	अगर (rate < 0) अणु
		dev_err(mmc_dev(mmc), "error rounding clk to %d: %ld\n",
			घड़ी, rate);
		वापस rate;
	पूर्ण
	dev_dbg(mmc_dev(mmc), "setting clk to %d, rounded %ld\n",
		घड़ी, rate);

	/* setting घड़ी rate */
	ret = clk_set_rate(host->clk_mmc, rate);
	अगर (ret) अणु
		dev_err(mmc_dev(mmc), "error setting clk to %ld: %d\n",
			rate, ret);
		वापस ret;
	पूर्ण

	/* set पूर्णांकernal भागider */
	rval = mmc_पढ़ोl(host, REG_CLKCR);
	rval &= ~0xff;
	rval |= भाग - 1;
	mmc_ग_लिखोl(host, REG_CLKCR, rval);

	/* update card घड़ी rate to account क्रम पूर्णांकernal भागider */
	rate /= भाग;

	/*
	 * Configure the controller to use the new timing mode अगर needed.
	 * On controllers that only support the new timing mode, such as
	 * the eMMC controller on the A64, this रेजिस्टर करोes not exist,
	 * and any ग_लिखोs to it are ignored.
	 */
	अगर (host->use_new_timings) अणु
		/* Don't touch the delay bits */
		rval = mmc_पढ़ोl(host, REG_SD_NTSR);
		rval |= SDXC_2X_TIMING_MODE;
		mmc_ग_लिखोl(host, REG_SD_NTSR, rval);
	पूर्ण

	/* sunxi_mmc_clk_set_phase expects the actual card घड़ी rate */
	ret = sunxi_mmc_clk_set_phase(host, ios, rate);
	अगर (ret)
		वापस ret;

	ret = sunxi_mmc_calibrate(host, SDXC_REG_SAMP_DL_REG);
	अगर (ret)
		वापस ret;

	/*
	 * FIXME:
	 *
	 * In HS400 we'll also need to calibrate the data strobe
	 * संकेत. This should only happen on the MMC2 controller (at
	 * least on the A64).
	 */

	ret = sunxi_mmc_oclk_onoff(host, 1);
	अगर (ret)
		वापस ret;

	/* And we just enabled our घड़ी back */
	mmc->actual_घड़ी = rate;

	वापस 0;
पूर्ण

अटल व्योम sunxi_mmc_set_bus_width(काष्ठा sunxi_mmc_host *host,
				   अचिन्हित अक्षर width)
अणु
	चयन (width) अणु
	हाल MMC_BUS_WIDTH_1:
		mmc_ग_लिखोl(host, REG_WIDTH, SDXC_WIDTH1);
		अवरोध;
	हाल MMC_BUS_WIDTH_4:
		mmc_ग_लिखोl(host, REG_WIDTH, SDXC_WIDTH4);
		अवरोध;
	हाल MMC_BUS_WIDTH_8:
		mmc_ग_लिखोl(host, REG_WIDTH, SDXC_WIDTH8);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम sunxi_mmc_set_clk(काष्ठा sunxi_mmc_host *host, काष्ठा mmc_ios *ios)
अणु
	u32 rval;

	/* set ddr mode */
	rval = mmc_पढ़ोl(host, REG_GCTRL);
	अगर (ios->timing == MMC_TIMING_UHS_DDR50 ||
	    ios->timing == MMC_TIMING_MMC_DDR52)
		rval |= SDXC_DDR_MODE;
	अन्यथा
		rval &= ~SDXC_DDR_MODE;
	mmc_ग_लिखोl(host, REG_GCTRL, rval);

	host->ख_त्रुटि = sunxi_mmc_clk_set_rate(host, ios);
	/* Android code had a usleep_range(50000, 55000); here */
पूर्ण

अटल व्योम sunxi_mmc_card_घातer(काष्ठा sunxi_mmc_host *host,
				 काष्ठा mmc_ios *ios)
अणु
	काष्ठा mmc_host *mmc = host->mmc;

	चयन (ios->घातer_mode) अणु
	हाल MMC_POWER_UP:
		dev_dbg(mmc_dev(mmc), "Powering card up\n");

		अगर (!IS_ERR(mmc->supply.vmmc)) अणु
			host->ख_त्रुटि = mmc_regulator_set_ocr(mmc,
							     mmc->supply.vmmc,
							     ios->vdd);
			अगर (host->ख_त्रुटि)
				वापस;
		पूर्ण

		अगर (!IS_ERR(mmc->supply.vqmmc)) अणु
			host->ख_त्रुटि = regulator_enable(mmc->supply.vqmmc);
			अगर (host->ख_त्रुटि) अणु
				dev_err(mmc_dev(mmc),
					"failed to enable vqmmc\n");
				वापस;
			पूर्ण
			host->vqmmc_enabled = true;
		पूर्ण
		अवरोध;

	हाल MMC_POWER_OFF:
		dev_dbg(mmc_dev(mmc), "Powering card off\n");

		अगर (!IS_ERR(mmc->supply.vmmc))
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);

		अगर (!IS_ERR(mmc->supply.vqmmc) && host->vqmmc_enabled)
			regulator_disable(mmc->supply.vqmmc);

		host->vqmmc_enabled = false;
		अवरोध;

	शेष:
		dev_dbg(mmc_dev(mmc), "Ignoring unknown card power state\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम sunxi_mmc_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा sunxi_mmc_host *host = mmc_priv(mmc);

	sunxi_mmc_card_घातer(host, ios);
	sunxi_mmc_set_bus_width(host, ios->bus_width);
	sunxi_mmc_set_clk(host, ios);
पूर्ण

अटल पूर्णांक sunxi_mmc_volt_चयन(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	पूर्णांक ret;

	/* vqmmc regulator is available */
	अगर (!IS_ERR(mmc->supply.vqmmc)) अणु
		ret = mmc_regulator_set_vqmmc(mmc, ios);
		वापस ret < 0 ? ret : 0;
	पूर्ण

	/* no vqmmc regulator, assume fixed regulator at 3/3.3V */
	अगर (mmc->ios.संकेत_voltage == MMC_SIGNAL_VOLTAGE_330)
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल व्योम sunxi_mmc_enable_sdio_irq(काष्ठा mmc_host *mmc, पूर्णांक enable)
अणु
	काष्ठा sunxi_mmc_host *host = mmc_priv(mmc);
	अचिन्हित दीर्घ flags;
	u32 imask;

	अगर (enable)
		pm_runसमय_get_noresume(host->dev);

	spin_lock_irqsave(&host->lock, flags);

	imask = mmc_पढ़ोl(host, REG_IMASK);
	अगर (enable) अणु
		host->sdio_imask = SDXC_SDIO_INTERRUPT;
		imask |= SDXC_SDIO_INTERRUPT;
	पूर्ण अन्यथा अणु
		host->sdio_imask = 0;
		imask &= ~SDXC_SDIO_INTERRUPT;
	पूर्ण
	mmc_ग_लिखोl(host, REG_IMASK, imask);
	spin_unlock_irqrestore(&host->lock, flags);

	अगर (!enable)
		pm_runसमय_put_noidle(host->mmc->parent);
पूर्ण

अटल व्योम sunxi_mmc_hw_reset(काष्ठा mmc_host *mmc)
अणु
	काष्ठा sunxi_mmc_host *host = mmc_priv(mmc);
	mmc_ग_लिखोl(host, REG_HWRST, 0);
	udelay(10);
	mmc_ग_लिखोl(host, REG_HWRST, 1);
	udelay(300);
पूर्ण

अटल व्योम sunxi_mmc_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा sunxi_mmc_host *host = mmc_priv(mmc);
	काष्ठा mmc_command *cmd = mrq->cmd;
	काष्ठा mmc_data *data = mrq->data;
	अचिन्हित दीर्घ अगरlags;
	u32 imask = SDXC_INTERRUPT_ERROR_BIT;
	u32 cmd_val = SDXC_START | (cmd->opcode & 0x3f);
	bool रुको_dma = host->रुको_dma;
	पूर्णांक ret;

	/* Check क्रम set_ios errors (should never happen) */
	अगर (host->ख_त्रुटि) अणु
		mrq->cmd->error = host->ख_त्रुटि;
		mmc_request_करोne(mmc, mrq);
		वापस;
	पूर्ण

	अगर (data) अणु
		ret = sunxi_mmc_map_dma(host, data);
		अगर (ret < 0) अणु
			dev_err(mmc_dev(mmc), "map DMA failed\n");
			cmd->error = ret;
			data->error = ret;
			mmc_request_करोne(mmc, mrq);
			वापस;
		पूर्ण
	पूर्ण

	अगर (cmd->opcode == MMC_GO_IDLE_STATE) अणु
		cmd_val |= SDXC_SEND_INIT_SEQUENCE;
		imask |= SDXC_COMMAND_DONE;
	पूर्ण

	अगर (cmd->flags & MMC_RSP_PRESENT) अणु
		cmd_val |= SDXC_RESP_EXPIRE;
		अगर (cmd->flags & MMC_RSP_136)
			cmd_val |= SDXC_LONG_RESPONSE;
		अगर (cmd->flags & MMC_RSP_CRC)
			cmd_val |= SDXC_CHECK_RESPONSE_CRC;

		अगर ((cmd->flags & MMC_CMD_MASK) == MMC_CMD_ADTC) अणु
			cmd_val |= SDXC_DATA_EXPIRE | SDXC_WAIT_PRE_OVER;

			अगर (cmd->data->stop) अणु
				imask |= SDXC_AUTO_COMMAND_DONE;
				cmd_val |= SDXC_SEND_AUTO_STOP;
			पूर्ण अन्यथा अणु
				imask |= SDXC_DATA_OVER;
			पूर्ण

			अगर (cmd->data->flags & MMC_DATA_WRITE)
				cmd_val |= SDXC_WRITE;
			अन्यथा
				रुको_dma = true;
		पूर्ण अन्यथा अणु
			imask |= SDXC_COMMAND_DONE;
		पूर्ण
	पूर्ण अन्यथा अणु
		imask |= SDXC_COMMAND_DONE;
	पूर्ण

	dev_dbg(mmc_dev(mmc), "cmd %d(%08x) arg %x ie 0x%08x len %d\n",
		cmd_val & 0x3f, cmd_val, cmd->arg, imask,
		mrq->data ? mrq->data->blksz * mrq->data->blocks : 0);

	spin_lock_irqsave(&host->lock, अगरlags);

	अगर (host->mrq || host->manual_stop_mrq) अणु
		spin_unlock_irqrestore(&host->lock, अगरlags);

		अगर (data)
			dma_unmap_sg(mmc_dev(mmc), data->sg, data->sg_len,
				     mmc_get_dma_dir(data));

		dev_err(mmc_dev(mmc), "request already pending\n");
		mrq->cmd->error = -EBUSY;
		mmc_request_करोne(mmc, mrq);
		वापस;
	पूर्ण

	अगर (data) अणु
		mmc_ग_लिखोl(host, REG_BLKSZ, data->blksz);
		mmc_ग_लिखोl(host, REG_BCNTR, data->blksz * data->blocks);
		sunxi_mmc_start_dma(host, data);
	पूर्ण

	host->mrq = mrq;
	host->रुको_dma = रुको_dma;
	mmc_ग_लिखोl(host, REG_IMASK, host->sdio_imask | imask);
	mmc_ग_लिखोl(host, REG_CARG, cmd->arg);
	mmc_ग_लिखोl(host, REG_CMDR, cmd_val);

	spin_unlock_irqrestore(&host->lock, अगरlags);
पूर्ण

अटल पूर्णांक sunxi_mmc_card_busy(काष्ठा mmc_host *mmc)
अणु
	काष्ठा sunxi_mmc_host *host = mmc_priv(mmc);

	वापस !!(mmc_पढ़ोl(host, REG_STAS) & SDXC_CARD_DATA_BUSY);
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops sunxi_mmc_ops = अणु
	.request	 = sunxi_mmc_request,
	.set_ios	 = sunxi_mmc_set_ios,
	.get_ro		 = mmc_gpio_get_ro,
	.get_cd		 = mmc_gpio_get_cd,
	.enable_sdio_irq = sunxi_mmc_enable_sdio_irq,
	.start_संकेत_voltage_चयन = sunxi_mmc_volt_चयन,
	.hw_reset	 = sunxi_mmc_hw_reset,
	.card_busy	 = sunxi_mmc_card_busy,
पूर्ण;

अटल स्थिर काष्ठा sunxi_mmc_clk_delay sunxi_mmc_clk_delays[] = अणु
	[SDXC_CLK_400K]		= अणु .output = 180, .sample = 180 पूर्ण,
	[SDXC_CLK_25M]		= अणु .output = 180, .sample =  75 पूर्ण,
	[SDXC_CLK_50M]		= अणु .output =  90, .sample = 120 पूर्ण,
	[SDXC_CLK_50M_DDR]	= अणु .output =  60, .sample = 120 पूर्ण,
	/* Value from A83T "new timing mode". Works but might not be right. */
	[SDXC_CLK_50M_DDR_8BIT]	= अणु .output =  90, .sample = 180 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sunxi_mmc_clk_delay sun9i_mmc_clk_delays[] = अणु
	[SDXC_CLK_400K]		= अणु .output = 180, .sample = 180 पूर्ण,
	[SDXC_CLK_25M]		= अणु .output = 180, .sample =  75 पूर्ण,
	[SDXC_CLK_50M]		= अणु .output = 150, .sample = 120 पूर्ण,
	[SDXC_CLK_50M_DDR]	= अणु .output =  54, .sample =  36 पूर्ण,
	[SDXC_CLK_50M_DDR_8BIT]	= अणु .output =  72, .sample =  72 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sunxi_mmc_cfg sun4i_a10_cfg = अणु
	.idma_des_size_bits = 13,
	.clk_delays = शून्य,
	.can_calibrate = false,
पूर्ण;

अटल स्थिर काष्ठा sunxi_mmc_cfg sun5i_a13_cfg = अणु
	.idma_des_size_bits = 16,
	.clk_delays = शून्य,
	.can_calibrate = false,
पूर्ण;

अटल स्थिर काष्ठा sunxi_mmc_cfg sun7i_a20_cfg = अणु
	.idma_des_size_bits = 16,
	.clk_delays = sunxi_mmc_clk_delays,
	.can_calibrate = false,
पूर्ण;

अटल स्थिर काष्ठा sunxi_mmc_cfg sun8i_a83t_emmc_cfg = अणु
	.idma_des_size_bits = 16,
	.clk_delays = sunxi_mmc_clk_delays,
	.can_calibrate = false,
	.ccu_has_timings_चयन = true,
पूर्ण;

अटल स्थिर काष्ठा sunxi_mmc_cfg sun9i_a80_cfg = अणु
	.idma_des_size_bits = 16,
	.clk_delays = sun9i_mmc_clk_delays,
	.can_calibrate = false,
पूर्ण;

अटल स्थिर काष्ठा sunxi_mmc_cfg sun50i_a64_cfg = अणु
	.idma_des_size_bits = 16,
	.clk_delays = शून्य,
	.can_calibrate = true,
	.mask_data0 = true,
	.needs_new_timings = true,
पूर्ण;

अटल स्थिर काष्ठा sunxi_mmc_cfg sun50i_a64_emmc_cfg = अणु
	.idma_des_size_bits = 13,
	.clk_delays = शून्य,
	.can_calibrate = true,
	.needs_new_timings = true,
पूर्ण;

अटल स्थिर काष्ठा sunxi_mmc_cfg sun50i_a100_cfg = अणु
	.idma_des_size_bits = 16,
	.idma_des_shअगरt = 2,
	.clk_delays = शून्य,
	.can_calibrate = true,
	.mask_data0 = true,
	.needs_new_timings = true,
पूर्ण;

अटल स्थिर काष्ठा sunxi_mmc_cfg sun50i_a100_emmc_cfg = अणु
	.idma_des_size_bits = 13,
	.idma_des_shअगरt = 2,
	.clk_delays = शून्य,
	.can_calibrate = true,
	.needs_new_timings = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sunxi_mmc_of_match[] = अणु
	अणु .compatible = "allwinner,sun4i-a10-mmc", .data = &sun4i_a10_cfg पूर्ण,
	अणु .compatible = "allwinner,sun5i-a13-mmc", .data = &sun5i_a13_cfg पूर्ण,
	अणु .compatible = "allwinner,sun7i-a20-mmc", .data = &sun7i_a20_cfg पूर्ण,
	अणु .compatible = "allwinner,sun8i-a83t-emmc", .data = &sun8i_a83t_emmc_cfg पूर्ण,
	अणु .compatible = "allwinner,sun9i-a80-mmc", .data = &sun9i_a80_cfg पूर्ण,
	अणु .compatible = "allwinner,sun50i-a64-mmc", .data = &sun50i_a64_cfg पूर्ण,
	अणु .compatible = "allwinner,sun50i-a64-emmc", .data = &sun50i_a64_emmc_cfg पूर्ण,
	अणु .compatible = "allwinner,sun50i-a100-mmc", .data = &sun50i_a100_cfg पूर्ण,
	अणु .compatible = "allwinner,sun50i-a100-emmc", .data = &sun50i_a100_emmc_cfg पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sunxi_mmc_of_match);

अटल पूर्णांक sunxi_mmc_enable(काष्ठा sunxi_mmc_host *host)
अणु
	पूर्णांक ret;

	अगर (!IS_ERR(host->reset)) अणु
		ret = reset_control_reset(host->reset);
		अगर (ret) अणु
			dev_err(host->dev, "Couldn't reset the MMC controller (%d)\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = clk_prepare_enable(host->clk_ahb);
	अगर (ret) अणु
		dev_err(host->dev, "Couldn't enable the bus clocks (%d)\n", ret);
		जाओ error_निश्चित_reset;
	पूर्ण

	ret = clk_prepare_enable(host->clk_mmc);
	अगर (ret) अणु
		dev_err(host->dev, "Enable mmc clk err %d\n", ret);
		जाओ error_disable_clk_ahb;
	पूर्ण

	ret = clk_prepare_enable(host->clk_output);
	अगर (ret) अणु
		dev_err(host->dev, "Enable output clk err %d\n", ret);
		जाओ error_disable_clk_mmc;
	पूर्ण

	ret = clk_prepare_enable(host->clk_sample);
	अगर (ret) अणु
		dev_err(host->dev, "Enable sample clk err %d\n", ret);
		जाओ error_disable_clk_output;
	पूर्ण

	/*
	 * Someबार the controller निश्चितs the irq on boot क्रम some reason,
	 * make sure the controller is in a sane state beक्रमe enabling irqs.
	 */
	ret = sunxi_mmc_reset_host(host);
	अगर (ret)
		जाओ error_disable_clk_sample;

	वापस 0;

error_disable_clk_sample:
	clk_disable_unprepare(host->clk_sample);
error_disable_clk_output:
	clk_disable_unprepare(host->clk_output);
error_disable_clk_mmc:
	clk_disable_unprepare(host->clk_mmc);
error_disable_clk_ahb:
	clk_disable_unprepare(host->clk_ahb);
error_निश्चित_reset:
	अगर (!IS_ERR(host->reset))
		reset_control_निश्चित(host->reset);
	वापस ret;
पूर्ण

अटल व्योम sunxi_mmc_disable(काष्ठा sunxi_mmc_host *host)
अणु
	sunxi_mmc_reset_host(host);

	clk_disable_unprepare(host->clk_sample);
	clk_disable_unprepare(host->clk_output);
	clk_disable_unprepare(host->clk_mmc);
	clk_disable_unprepare(host->clk_ahb);

	अगर (!IS_ERR(host->reset))
		reset_control_निश्चित(host->reset);
पूर्ण

अटल पूर्णांक sunxi_mmc_resource_request(काष्ठा sunxi_mmc_host *host,
				      काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	host->cfg = of_device_get_match_data(&pdev->dev);
	अगर (!host->cfg)
		वापस -EINVAL;

	ret = mmc_regulator_get_supply(host->mmc);
	अगर (ret)
		वापस ret;

	host->reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(host->reg_base))
		वापस PTR_ERR(host->reg_base);

	host->clk_ahb = devm_clk_get(&pdev->dev, "ahb");
	अगर (IS_ERR(host->clk_ahb)) अणु
		dev_err(&pdev->dev, "Could not get ahb clock\n");
		वापस PTR_ERR(host->clk_ahb);
	पूर्ण

	host->clk_mmc = devm_clk_get(&pdev->dev, "mmc");
	अगर (IS_ERR(host->clk_mmc)) अणु
		dev_err(&pdev->dev, "Could not get mmc clock\n");
		वापस PTR_ERR(host->clk_mmc);
	पूर्ण

	अगर (host->cfg->clk_delays) अणु
		host->clk_output = devm_clk_get(&pdev->dev, "output");
		अगर (IS_ERR(host->clk_output)) अणु
			dev_err(&pdev->dev, "Could not get output clock\n");
			वापस PTR_ERR(host->clk_output);
		पूर्ण

		host->clk_sample = devm_clk_get(&pdev->dev, "sample");
		अगर (IS_ERR(host->clk_sample)) अणु
			dev_err(&pdev->dev, "Could not get sample clock\n");
			वापस PTR_ERR(host->clk_sample);
		पूर्ण
	पूर्ण

	host->reset = devm_reset_control_get_optional_exclusive(&pdev->dev,
								"ahb");
	अगर (PTR_ERR(host->reset) == -EPROBE_DEFER)
		वापस PTR_ERR(host->reset);

	ret = sunxi_mmc_enable(host);
	अगर (ret)
		वापस ret;

	host->irq = platक्रमm_get_irq(pdev, 0);
	अगर (host->irq <= 0) अणु
		ret = -EINVAL;
		जाओ error_disable_mmc;
	पूर्ण

	वापस devm_request_thपढ़ोed_irq(&pdev->dev, host->irq, sunxi_mmc_irq,
			sunxi_mmc_handle_manual_stop, 0, "sunxi-mmc", host);

error_disable_mmc:
	sunxi_mmc_disable(host);
	वापस ret;
पूर्ण

अटल पूर्णांक sunxi_mmc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sunxi_mmc_host *host;
	काष्ठा mmc_host *mmc;
	पूर्णांक ret;

	mmc = mmc_alloc_host(माप(काष्ठा sunxi_mmc_host), &pdev->dev);
	अगर (!mmc) अणु
		dev_err(&pdev->dev, "mmc alloc host failed\n");
		वापस -ENOMEM;
	पूर्ण
	platक्रमm_set_drvdata(pdev, mmc);

	host = mmc_priv(mmc);
	host->dev = &pdev->dev;
	host->mmc = mmc;
	spin_lock_init(&host->lock);

	ret = sunxi_mmc_resource_request(host, pdev);
	अगर (ret)
		जाओ error_मुक्त_host;

	host->sg_cpu = dma_alloc_coherent(&pdev->dev, PAGE_SIZE,
					  &host->sg_dma, GFP_KERNEL);
	अगर (!host->sg_cpu) अणु
		dev_err(&pdev->dev, "Failed to allocate DMA descriptor mem\n");
		ret = -ENOMEM;
		जाओ error_मुक्त_host;
	पूर्ण

	अगर (host->cfg->ccu_has_timings_चयन) अणु
		/*
		 * Supports both old and new timing modes.
		 * Try setting the clk to new timing mode.
		 */
		sunxi_ccu_set_mmc_timing_mode(host->clk_mmc, true);

		/* And check the result */
		ret = sunxi_ccu_get_mmc_timing_mode(host->clk_mmc);
		अगर (ret < 0) अणु
			/*
			 * For whatever reason we were not able to get
			 * the current active mode. Default to old mode.
			 */
			dev_warn(&pdev->dev, "MMC clk timing mode unknown\n");
			host->use_new_timings = false;
		पूर्ण अन्यथा अणु
			host->use_new_timings = !!ret;
		पूर्ण
	पूर्ण अन्यथा अगर (host->cfg->needs_new_timings) अणु
		/* Supports new timing mode only */
		host->use_new_timings = true;
	पूर्ण

	mmc->ops		= &sunxi_mmc_ops;
	mmc->max_blk_count	= 8192;
	mmc->max_blk_size	= 4096;
	mmc->max_segs		= PAGE_SIZE / माप(काष्ठा sunxi_idma_des);
	mmc->max_seg_size	= (1 << host->cfg->idma_des_size_bits);
	mmc->max_req_size	= mmc->max_seg_size * mmc->max_segs;
	/* 400kHz ~ 52MHz */
	mmc->f_min		=   400000;
	mmc->f_max		= 52000000;
	mmc->caps	       |= MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED |
				  MMC_CAP_SDIO_IRQ;

	/*
	 * Some H5 devices करो not have संकेत traces precise enough to
	 * use HS DDR mode क्रम their eMMC chips.
	 *
	 * We still enable HS DDR modes क्रम all the other controller
	 * variants that support them.
	 */
	अगर ((host->cfg->clk_delays || host->use_new_timings) &&
	    !of_device_is_compatible(pdev->dev.of_node,
				     "allwinner,sun50i-h5-emmc"))
		mmc->caps      |= MMC_CAP_1_8V_DDR | MMC_CAP_3_3V_DDR;

	ret = mmc_of_parse(mmc);
	अगर (ret)
		जाओ error_मुक्त_dma;

	/*
	 * If we करोn't support delay chains in the SoC, we can't use any
	 * of the higher speed modes. Mask them out in हाल the device
	 * tree specअगरies the properties क्रम them, which माला_लो added to
	 * the caps by mmc_of_parse() above.
	 */
	अगर (!(host->cfg->clk_delays || host->use_new_timings)) अणु
		mmc->caps &= ~(MMC_CAP_3_3V_DDR | MMC_CAP_1_8V_DDR |
			       MMC_CAP_1_2V_DDR | MMC_CAP_UHS);
		mmc->caps2 &= ~MMC_CAP2_HS200;
	पूर्ण

	/* TODO: This driver करोesn't support HS400 mode yet */
	mmc->caps2 &= ~MMC_CAP2_HS400;

	ret = sunxi_mmc_init_host(host);
	अगर (ret)
		जाओ error_मुक्त_dma;

	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 50);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	ret = mmc_add_host(mmc);
	अगर (ret)
		जाओ error_मुक्त_dma;

	dev_info(&pdev->dev, "initialized, max. request size: %u KB%s\n",
		 mmc->max_req_size >> 10,
		 host->use_new_timings ? ", uses new timings mode" : "");

	वापस 0;

error_मुक्त_dma:
	dma_मुक्त_coherent(&pdev->dev, PAGE_SIZE, host->sg_cpu, host->sg_dma);
error_मुक्त_host:
	mmc_मुक्त_host(mmc);
	वापस ret;
पूर्ण

अटल पूर्णांक sunxi_mmc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_host	*mmc = platक्रमm_get_drvdata(pdev);
	काष्ठा sunxi_mmc_host *host = mmc_priv(mmc);

	mmc_हटाओ_host(mmc);
	pm_runसमय_क्रमce_suspend(&pdev->dev);
	disable_irq(host->irq);
	sunxi_mmc_disable(host);
	dma_मुक्त_coherent(&pdev->dev, PAGE_SIZE, host->sg_cpu, host->sg_dma);
	mmc_मुक्त_host(mmc);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक sunxi_mmc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा mmc_host	*mmc = dev_get_drvdata(dev);
	काष्ठा sunxi_mmc_host *host = mmc_priv(mmc);
	पूर्णांक ret;

	ret = sunxi_mmc_enable(host);
	अगर (ret)
		वापस ret;

	sunxi_mmc_init_host(host);
	sunxi_mmc_set_bus_width(host, mmc->ios.bus_width);
	sunxi_mmc_set_clk(host, &mmc->ios);
	enable_irq(host->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_mmc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा mmc_host	*mmc = dev_get_drvdata(dev);
	काष्ठा sunxi_mmc_host *host = mmc_priv(mmc);

	/*
	 * When घड़ीs are off, it's possible receiving
	 * fake पूर्णांकerrupts, which will stall the प्रणाली.
	 * Disabling the irq  will prevent this.
	 */
	disable_irq(host->irq);
	sunxi_mmc_reset_host(host);
	sunxi_mmc_disable(host);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops sunxi_mmc_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(sunxi_mmc_runसमय_suspend,
			   sunxi_mmc_runसमय_resume,
			   शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver sunxi_mmc_driver = अणु
	.driver = अणु
		.name	= "sunxi-mmc",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = sunxi_mmc_of_match,
		.pm = &sunxi_mmc_pm_ops,
	पूर्ण,
	.probe		= sunxi_mmc_probe,
	.हटाओ		= sunxi_mmc_हटाओ,
पूर्ण;
module_platक्रमm_driver(sunxi_mmc_driver);

MODULE_DESCRIPTION("Allwinner's SD/MMC Card Controller Driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("David Lanzendथघrfer <david.lanzendoerfer@o2s.ch>");
MODULE_ALIAS("platform:sunxi-mmc");
