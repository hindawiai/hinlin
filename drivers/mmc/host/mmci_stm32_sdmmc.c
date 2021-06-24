<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics 2018 - All Rights Reserved
 * Author: Luकरोvic.barre@st.com क्रम STMicroelectronics.
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/of_address.h>
#समावेश <linux/reset.h>
#समावेश <linux/scatterlist.h>
#समावेश "mmci.h"

#घोषणा SDMMC_LLI_BUF_LEN	PAGE_SIZE
#घोषणा SDMMC_IDMA_BURST	BIT(MMCI_STM32_IDMABNDT_SHIFT)

#घोषणा DLYB_CR			0x0
#घोषणा DLYB_CR_DEN		BIT(0)
#घोषणा DLYB_CR_SEN		BIT(1)

#घोषणा DLYB_CFGR		0x4
#घोषणा DLYB_CFGR_SEL_MASK	GENMASK(3, 0)
#घोषणा DLYB_CFGR_UNIT_MASK	GENMASK(14, 8)
#घोषणा DLYB_CFGR_LNG_MASK	GENMASK(27, 16)
#घोषणा DLYB_CFGR_LNGF		BIT(31)

#घोषणा DLYB_NB_DELAY		11
#घोषणा DLYB_CFGR_SEL_MAX	(DLYB_NB_DELAY + 1)
#घोषणा DLYB_CFGR_UNIT_MAX	127

#घोषणा DLYB_LNG_TIMEOUT_US	1000
#घोषणा SDMMC_VSWEND_TIMEOUT_US 10000

काष्ठा sdmmc_lli_desc अणु
	u32 idmalar;
	u32 idmabase;
	u32 idmasize;
पूर्ण;

काष्ठा sdmmc_idma अणु
	dma_addr_t sg_dma;
	व्योम *sg_cpu;
पूर्ण;

काष्ठा sdmmc_dlyb अणु
	व्योम __iomem *base;
	u32 unit;
	u32 max;
पूर्ण;

अटल पूर्णांक sdmmc_idma_validate_data(काष्ठा mmci_host *host,
				    काष्ठा mmc_data *data)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	/*
	 * idma has स्थिरraपूर्णांकs on idmabase & idmasize क्रम each element
	 * excepted the last element which has no स्थिरraपूर्णांक on idmasize
	 */
	क्रम_each_sg(data->sg, sg, data->sg_len - 1, i) अणु
		अगर (!IS_ALIGNED(data->sg->offset, माप(u32)) ||
		    !IS_ALIGNED(data->sg->length, SDMMC_IDMA_BURST)) अणु
			dev_err(mmc_dev(host->mmc),
				"unaligned scatterlist: ofst:%x length:%d\n",
				data->sg->offset, data->sg->length);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!IS_ALIGNED(data->sg->offset, माप(u32))) अणु
		dev_err(mmc_dev(host->mmc),
			"unaligned last scatterlist: ofst:%x length:%d\n",
			data->sg->offset, data->sg->length);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक _sdmmc_idma_prep_data(काष्ठा mmci_host *host,
				 काष्ठा mmc_data *data)
अणु
	पूर्णांक n_elem;

	n_elem = dma_map_sg(mmc_dev(host->mmc),
			    data->sg,
			    data->sg_len,
			    mmc_get_dma_dir(data));

	अगर (!n_elem) अणु
		dev_err(mmc_dev(host->mmc), "dma_map_sg failed\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sdmmc_idma_prep_data(काष्ठा mmci_host *host,
				काष्ठा mmc_data *data, bool next)
अणु
	/* Check अगर job is alपढ़ोy prepared. */
	अगर (!next && data->host_cookie == host->next_cookie)
		वापस 0;

	वापस _sdmmc_idma_prep_data(host, data);
पूर्ण

अटल व्योम sdmmc_idma_unprep_data(काष्ठा mmci_host *host,
				   काष्ठा mmc_data *data, पूर्णांक err)
अणु
	dma_unmap_sg(mmc_dev(host->mmc), data->sg, data->sg_len,
		     mmc_get_dma_dir(data));
पूर्ण

अटल पूर्णांक sdmmc_idma_setup(काष्ठा mmci_host *host)
अणु
	काष्ठा sdmmc_idma *idma;
	काष्ठा device *dev = mmc_dev(host->mmc);

	idma = devm_kzalloc(dev, माप(*idma), GFP_KERNEL);
	अगर (!idma)
		वापस -ENOMEM;

	host->dma_priv = idma;

	अगर (host->variant->dma_lli) अणु
		idma->sg_cpu = dmam_alloc_coherent(dev, SDMMC_LLI_BUF_LEN,
						   &idma->sg_dma, GFP_KERNEL);
		अगर (!idma->sg_cpu) अणु
			dev_err(dev, "Failed to alloc IDMA descriptor\n");
			वापस -ENOMEM;
		पूर्ण
		host->mmc->max_segs = SDMMC_LLI_BUF_LEN /
			माप(काष्ठा sdmmc_lli_desc);
		host->mmc->max_seg_size = host->variant->sपंचांग32_idmअसलize_mask;
	पूर्ण अन्यथा अणु
		host->mmc->max_segs = 1;
		host->mmc->max_seg_size = host->mmc->max_req_size;
	पूर्ण

	वापस dma_set_max_seg_size(dev, host->mmc->max_seg_size);
पूर्ण

अटल पूर्णांक sdmmc_idma_start(काष्ठा mmci_host *host, अचिन्हित पूर्णांक *datactrl)

अणु
	काष्ठा sdmmc_idma *idma = host->dma_priv;
	काष्ठा sdmmc_lli_desc *desc = (काष्ठा sdmmc_lli_desc *)idma->sg_cpu;
	काष्ठा mmc_data *data = host->data;
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	अगर (!host->variant->dma_lli || data->sg_len == 1) अणु
		ग_लिखोl_relaxed(sg_dma_address(data->sg),
			       host->base + MMCI_STM32_IDMABASE0R);
		ग_लिखोl_relaxed(MMCI_STM32_IDMAEN,
			       host->base + MMCI_STM32_IDMACTRLR);
		वापस 0;
	पूर्ण

	क्रम_each_sg(data->sg, sg, data->sg_len, i) अणु
		desc[i].idmalar = (i + 1) * माप(काष्ठा sdmmc_lli_desc);
		desc[i].idmalar |= MMCI_STM32_ULA | MMCI_STM32_ULS
			| MMCI_STM32_ABR;
		desc[i].idmabase = sg_dma_address(sg);
		desc[i].idmasize = sg_dma_len(sg);
	पूर्ण

	/* notice the end of link list */
	desc[data->sg_len - 1].idmalar &= ~MMCI_STM32_ULA;

	dma_wmb();
	ग_लिखोl_relaxed(idma->sg_dma, host->base + MMCI_STM32_IDMABAR);
	ग_लिखोl_relaxed(desc[0].idmalar, host->base + MMCI_STM32_IDMALAR);
	ग_लिखोl_relaxed(desc[0].idmabase, host->base + MMCI_STM32_IDMABASE0R);
	ग_लिखोl_relaxed(desc[0].idmasize, host->base + MMCI_STM32_IDMABSIZER);
	ग_लिखोl_relaxed(MMCI_STM32_IDMAEN | MMCI_STM32_IDMALLIEN,
		       host->base + MMCI_STM32_IDMACTRLR);

	वापस 0;
पूर्ण

अटल व्योम sdmmc_idma_finalize(काष्ठा mmci_host *host, काष्ठा mmc_data *data)
अणु
	ग_लिखोl_relaxed(0, host->base + MMCI_STM32_IDMACTRLR);

	अगर (!data->host_cookie)
		sdmmc_idma_unprep_data(host, data, 0);
पूर्ण

अटल व्योम mmci_sdmmc_set_clkreg(काष्ठा mmci_host *host, अचिन्हित पूर्णांक desired)
अणु
	अचिन्हित पूर्णांक clk = 0, ddr = 0;

	अगर (host->mmc->ios.timing == MMC_TIMING_MMC_DDR52 ||
	    host->mmc->ios.timing == MMC_TIMING_UHS_DDR50)
		ddr = MCI_STM32_CLK_DDR;

	/*
	 * cclk = mclk / (2 * clkभाग)
	 * clkभाग 0 => bypass
	 * in ddr mode bypass is not possible
	 */
	अगर (desired) अणु
		अगर (desired >= host->mclk && !ddr) अणु
			host->cclk = host->mclk;
		पूर्ण अन्यथा अणु
			clk = DIV_ROUND_UP(host->mclk, 2 * desired);
			अगर (clk > MCI_STM32_CLK_CLKDIV_MSK)
				clk = MCI_STM32_CLK_CLKDIV_MSK;
			host->cclk = host->mclk / (2 * clk);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * जबतक घातer-on phase the घड़ी can't be define to 0,
		 * Only घातer-off and घातer-cyc deactivate the घड़ी.
		 * अगर desired घड़ी is 0, set max भागider
		 */
		clk = MCI_STM32_CLK_CLKDIV_MSK;
		host->cclk = host->mclk / (2 * clk);
	पूर्ण

	/* Set actual घड़ी क्रम debug */
	अगर (host->mmc->ios.घातer_mode == MMC_POWER_ON)
		host->mmc->actual_घड़ी = host->cclk;
	अन्यथा
		host->mmc->actual_घड़ी = 0;

	अगर (host->mmc->ios.bus_width == MMC_BUS_WIDTH_4)
		clk |= MCI_STM32_CLK_WIDEBUS_4;
	अगर (host->mmc->ios.bus_width == MMC_BUS_WIDTH_8)
		clk |= MCI_STM32_CLK_WIDEBUS_8;

	clk |= MCI_STM32_CLK_HWFCEN;
	clk |= host->clk_reg_add;
	clk |= ddr;

	/*
	 * SDMMC_FBCK is selected when an बाह्यal Delay Block is needed
	 * with SDR104.
	 */
	अगर (host->mmc->ios.timing >= MMC_TIMING_UHS_SDR50) अणु
		clk |= MCI_STM32_CLK_BUSSPEED;
		अगर (host->mmc->ios.timing == MMC_TIMING_UHS_SDR104) अणु
			clk &= ~MCI_STM32_CLK_SEL_MSK;
			clk |= MCI_STM32_CLK_SELFBCK;
		पूर्ण
	पूर्ण

	mmci_ग_लिखो_clkreg(host, clk);
पूर्ण

अटल व्योम sdmmc_dlyb_input_ck(काष्ठा sdmmc_dlyb *dlyb)
अणु
	अगर (!dlyb || !dlyb->base)
		वापस;

	/* Output घड़ी = Input घड़ी */
	ग_लिखोl_relaxed(0, dlyb->base + DLYB_CR);
पूर्ण

अटल व्योम mmci_sdmmc_set_pwrreg(काष्ठा mmci_host *host, अचिन्हित पूर्णांक pwr)
अणु
	काष्ठा mmc_ios ios = host->mmc->ios;
	काष्ठा sdmmc_dlyb *dlyb = host->variant_priv;

	/* adds OF options */
	pwr = host->pwr_reg_add;

	sdmmc_dlyb_input_ck(dlyb);

	अगर (ios.घातer_mode == MMC_POWER_OFF) अणु
		/* Only a reset could घातer-off sdmmc */
		reset_control_निश्चित(host->rst);
		udelay(2);
		reset_control_deनिश्चित(host->rst);

		/*
		 * Set the SDMMC in Power-cycle state.
		 * This will make that the SDMMC_D[7:0], SDMMC_CMD and SDMMC_CK
		 * are driven low, to prevent the Card from being supplied
		 * through the संकेत lines.
		 */
		mmci_ग_लिखो_pwrreg(host, MCI_STM32_PWR_CYC | pwr);
	पूर्ण अन्यथा अगर (ios.घातer_mode == MMC_POWER_ON) अणु
		/*
		 * After घातer-off (reset): the irq mask defined in probe
		 * functionis lost
		 * ault irq mask (probe) must be activated
		 */
		ग_लिखोl(MCI_IRQENABLE | host->variant->start_err,
		       host->base + MMCIMASK0);

		/* preserves voltage चयन bits */
		pwr |= host->pwr_reg & (MCI_STM32_VSWITCHEN |
					MCI_STM32_VSWITCH);

		/*
		 * After a घातer-cycle state, we must set the SDMMC in
		 * Power-off. The SDMMC_D[7:0], SDMMC_CMD and SDMMC_CK are
		 * driven high. Then we can set the SDMMC to Power-on state
		 */
		mmci_ग_लिखो_pwrreg(host, MCI_PWR_OFF | pwr);
		mdelay(1);
		mmci_ग_लिखो_pwrreg(host, MCI_PWR_ON | pwr);
	पूर्ण
पूर्ण

अटल u32 sdmmc_get_dctrl_cfg(काष्ठा mmci_host *host)
अणु
	u32 datactrl;

	datactrl = mmci_dctrl_blksz(host);

	अगर (host->mmc->card && mmc_card_sdio(host->mmc->card) &&
	    host->data->blocks == 1)
		datactrl |= MCI_DPSM_STM32_MODE_SDIO;
	अन्यथा अगर (host->data->stop && !host->mrq->sbc)
		datactrl |= MCI_DPSM_STM32_MODE_BLOCK_STOP;
	अन्यथा
		datactrl |= MCI_DPSM_STM32_MODE_BLOCK;

	वापस datactrl;
पूर्ण

अटल bool sdmmc_busy_complete(काष्ठा mmci_host *host, u32 status, u32 err_msk)
अणु
	व्योम __iomem *base = host->base;
	u32 busy_d0, busy_d0end, mask, sdmmc_status;

	mask = पढ़ोl_relaxed(base + MMCIMASK0);
	sdmmc_status = पढ़ोl_relaxed(base + MMCISTATUS);
	busy_d0end = sdmmc_status & MCI_STM32_BUSYD0END;
	busy_d0 = sdmmc_status & MCI_STM32_BUSYD0;

	/* complete अगर there is an error or busy_d0end */
	अगर ((status & err_msk) || busy_d0end)
		जाओ complete;

	/*
	 * On response the busy संकेतing is reflected in the BUSYD0 flag.
	 * अगर busy_d0 is in-progress we must activate busyd0end पूर्णांकerrupt
	 * to रुको this completion. Else this request has no busy step.
	 */
	अगर (busy_d0) अणु
		अगर (!host->busy_status) अणु
			ग_लिखोl_relaxed(mask | host->variant->busy_detect_mask,
				       base + MMCIMASK0);
			host->busy_status = status &
				(MCI_CMDSENT | MCI_CMDRESPEND);
		पूर्ण
		वापस false;
	पूर्ण

complete:
	अगर (host->busy_status) अणु
		ग_लिखोl_relaxed(mask & ~host->variant->busy_detect_mask,
			       base + MMCIMASK0);
		host->busy_status = 0;
	पूर्ण

	ग_लिखोl_relaxed(host->variant->busy_detect_mask, base + MMCICLEAR);

	वापस true;
पूर्ण

अटल व्योम sdmmc_dlyb_set_cfgr(काष्ठा sdmmc_dlyb *dlyb,
				पूर्णांक unit, पूर्णांक phase, bool sampler)
अणु
	u32 cfgr;

	ग_लिखोl_relaxed(DLYB_CR_SEN | DLYB_CR_DEN, dlyb->base + DLYB_CR);

	cfgr = FIELD_PREP(DLYB_CFGR_UNIT_MASK, unit) |
	       FIELD_PREP(DLYB_CFGR_SEL_MASK, phase);
	ग_लिखोl_relaxed(cfgr, dlyb->base + DLYB_CFGR);

	अगर (!sampler)
		ग_लिखोl_relaxed(DLYB_CR_DEN, dlyb->base + DLYB_CR);
पूर्ण

अटल पूर्णांक sdmmc_dlyb_lng_tuning(काष्ठा mmci_host *host)
अणु
	काष्ठा sdmmc_dlyb *dlyb = host->variant_priv;
	u32 cfgr;
	पूर्णांक i, lng, ret;

	क्रम (i = 0; i <= DLYB_CFGR_UNIT_MAX; i++) अणु
		sdmmc_dlyb_set_cfgr(dlyb, i, DLYB_CFGR_SEL_MAX, true);

		ret = पढ़ोl_relaxed_poll_समयout(dlyb->base + DLYB_CFGR, cfgr,
						 (cfgr & DLYB_CFGR_LNGF),
						 1, DLYB_LNG_TIMEOUT_US);
		अगर (ret) अणु
			dev_warn(mmc_dev(host->mmc),
				 "delay line cfg timeout unit:%d cfgr:%d\n",
				 i, cfgr);
			जारी;
		पूर्ण

		lng = FIELD_GET(DLYB_CFGR_LNG_MASK, cfgr);
		अगर (lng < BIT(DLYB_NB_DELAY) && lng > 0)
			अवरोध;
	पूर्ण

	अगर (i > DLYB_CFGR_UNIT_MAX)
		वापस -EINVAL;

	dlyb->unit = i;
	dlyb->max = __fls(lng);

	वापस 0;
पूर्ण

अटल पूर्णांक sdmmc_dlyb_phase_tuning(काष्ठा mmci_host *host, u32 opcode)
अणु
	काष्ठा sdmmc_dlyb *dlyb = host->variant_priv;
	पूर्णांक cur_len = 0, max_len = 0, end_of_len = 0;
	पूर्णांक phase;

	क्रम (phase = 0; phase <= dlyb->max; phase++) अणु
		sdmmc_dlyb_set_cfgr(dlyb, dlyb->unit, phase, false);

		अगर (mmc_send_tuning(host->mmc, opcode, शून्य)) अणु
			cur_len = 0;
		पूर्ण अन्यथा अणु
			cur_len++;
			अगर (cur_len > max_len) अणु
				max_len = cur_len;
				end_of_len = phase;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!max_len) अणु
		dev_err(mmc_dev(host->mmc), "no tuning point found\n");
		वापस -EINVAL;
	पूर्ण

	phase = end_of_len - max_len / 2;
	sdmmc_dlyb_set_cfgr(dlyb, dlyb->unit, phase, false);

	dev_dbg(mmc_dev(host->mmc), "unit:%d max_dly:%d phase:%d\n",
		dlyb->unit, dlyb->max, phase);

	वापस 0;
पूर्ण

अटल पूर्णांक sdmmc_execute_tuning(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	काष्ठा mmci_host *host = mmc_priv(mmc);
	काष्ठा sdmmc_dlyb *dlyb = host->variant_priv;

	अगर (!dlyb || !dlyb->base)
		वापस -EINVAL;

	अगर (sdmmc_dlyb_lng_tuning(host))
		वापस -EINVAL;

	वापस sdmmc_dlyb_phase_tuning(host, opcode);
पूर्ण

अटल व्योम sdmmc_pre_sig_volt_vचयन(काष्ठा mmci_host *host)
अणु
	/* clear the voltage चयन completion flag */
	ग_लिखोl_relaxed(MCI_STM32_VSWENDC, host->base + MMCICLEAR);
	/* enable Voltage चयन procedure */
	mmci_ग_लिखो_pwrreg(host, host->pwr_reg | MCI_STM32_VSWITCHEN);
पूर्ण

अटल पूर्णांक sdmmc_post_sig_volt_चयन(काष्ठा mmci_host *host,
				      काष्ठा mmc_ios *ios)
अणु
	अचिन्हित दीर्घ flags;
	u32 status;
	पूर्णांक ret = 0;

	अगर (ios->संकेत_voltage == MMC_SIGNAL_VOLTAGE_180) अणु
		spin_lock_irqsave(&host->lock, flags);
		mmci_ग_लिखो_pwrreg(host, host->pwr_reg | MCI_STM32_VSWITCH);
		spin_unlock_irqrestore(&host->lock, flags);

		/* रुको voltage चयन completion जबतक 10ms */
		ret = पढ़ोl_relaxed_poll_समयout(host->base + MMCISTATUS,
						 status,
						 (status & MCI_STM32_VSWEND),
						 10, SDMMC_VSWEND_TIMEOUT_US);

		ग_लिखोl_relaxed(MCI_STM32_VSWENDC | MCI_STM32_CKSTOPC,
			       host->base + MMCICLEAR);
		mmci_ग_लिखो_pwrreg(host, host->pwr_reg &
				  ~(MCI_STM32_VSWITCHEN | MCI_STM32_VSWITCH));
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा mmci_host_ops sdmmc_variant_ops = अणु
	.validate_data = sdmmc_idma_validate_data,
	.prep_data = sdmmc_idma_prep_data,
	.unprep_data = sdmmc_idma_unprep_data,
	.get_datactrl_cfg = sdmmc_get_dctrl_cfg,
	.dma_setup = sdmmc_idma_setup,
	.dma_start = sdmmc_idma_start,
	.dma_finalize = sdmmc_idma_finalize,
	.set_clkreg = mmci_sdmmc_set_clkreg,
	.set_pwrreg = mmci_sdmmc_set_pwrreg,
	.busy_complete = sdmmc_busy_complete,
	.pre_sig_volt_चयन = sdmmc_pre_sig_volt_vचयन,
	.post_sig_volt_चयन = sdmmc_post_sig_volt_चयन,
पूर्ण;

व्योम sdmmc_variant_init(काष्ठा mmci_host *host)
अणु
	काष्ठा device_node *np = host->mmc->parent->of_node;
	व्योम __iomem *base_dlyb;
	काष्ठा sdmmc_dlyb *dlyb;

	host->ops = &sdmmc_variant_ops;
	host->pwr_reg = पढ़ोl_relaxed(host->base + MMCIPOWER);

	base_dlyb = devm_of_iomap(mmc_dev(host->mmc), np, 1, शून्य);
	अगर (IS_ERR(base_dlyb))
		वापस;

	dlyb = devm_kzalloc(mmc_dev(host->mmc), माप(*dlyb), GFP_KERNEL);
	अगर (!dlyb)
		वापस;

	dlyb->base = base_dlyb;
	host->variant_priv = dlyb;
	host->mmc_ops->execute_tuning = sdmmc_execute_tuning;
पूर्ण
