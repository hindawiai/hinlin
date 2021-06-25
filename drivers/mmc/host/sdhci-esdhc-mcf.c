<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Freescale eSDHC ColdFire family controller driver, platक्रमm bus.
 *
 * Copyright (c) 2020 Timesys Corporation
 *   Author: Angelo Dureghello <angelo.dureghello@बारys.it>
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_data/mmc-esdhc-mcf.h>
#समावेश <linux/mmc/mmc.h>
#समावेश "sdhci-pltfm.h"
#समावेश "sdhci-esdhc.h"

#घोषणा	ESDHC_PROCTL_D3CD		0x08
#घोषणा ESDHC_SYS_CTRL_DTOCV_MASK	0x0f
#घोषणा ESDHC_DEFAULT_HOST_CONTROL	0x28

/*
 * Freescale eSDHC has DMA ERR flag at bit 28, not as std spec says, bit 25.
 */
#घोषणा ESDHC_INT_VENDOR_SPEC_DMA_ERR	BIT(28)

काष्ठा pltfm_mcf_data अणु
	काष्ठा clk *clk_ipg;
	काष्ठा clk *clk_ahb;
	काष्ठा clk *clk_per;
	पूर्णांक aside;
	पूर्णांक current_bus_width;
पूर्ण;

अटल अंतरभूत व्योम esdhc_mcf_buffer_swap32(u32 *buf, पूर्णांक len)
अणु
	पूर्णांक i;
	u32 temp;

	len = (len + 3) >> 2;

	क्रम (i = 0; i < len;  i++) अणु
		temp = swab32(*buf);
		*buf++ = temp;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम esdhc_clrset_be(काष्ठा sdhci_host *host,
				   u32 mask, u32 val, पूर्णांक reg)
अणु
	व्योम __iomem *base = host->ioaddr + (reg & ~3);
	u8 shअगरt = (reg & 3) << 3;

	mask <<= shअगरt;
	val <<= shअगरt;

	अगर (reg == SDHCI_HOST_CONTROL)
		val |= ESDHC_PROCTL_D3CD;

	ग_लिखोl((पढ़ोl(base) & ~mask) | val, base);
पूर्ण

/*
 * Note: mcf is big-endian, single bytes need to be accessed at big endian
 * offsets.
 */
अटल व्योम esdhc_mcf_ग_लिखोb_be(काष्ठा sdhci_host *host, u8 val, पूर्णांक reg)
अणु
	व्योम __iomem *base = host->ioaddr + (reg & ~3);
	u8 shअगरt = (reg & 3) << 3;
	u32 mask = ~(0xff << shअगरt);

	अगर (reg == SDHCI_HOST_CONTROL) अणु
		u32 host_ctrl = ESDHC_DEFAULT_HOST_CONTROL;
		u8 dma_bits = (val & SDHCI_CTRL_DMA_MASK) >> 3;
		u8 पंचांगp = पढ़ोb(host->ioaddr + SDHCI_HOST_CONTROL + 1);

		पंचांगp &= ~0x03;
		पंचांगp |= dma_bits;

		/*
		 * Recomposition needed, restore always endianness and
		 * keep D3CD and AI, just setting bus width.
		 */
		host_ctrl |= val;
		host_ctrl |= (dma_bits << 8);
		ग_लिखोl(host_ctrl, host->ioaddr + SDHCI_HOST_CONTROL);

		वापस;
	पूर्ण

	ग_लिखोl((पढ़ोl(base) & mask) | (val << shअगरt), base);
पूर्ण

अटल व्योम esdhc_mcf_ग_लिखोw_be(काष्ठा sdhci_host *host, u16 val, पूर्णांक reg)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा pltfm_mcf_data *mcf_data = sdhci_pltfm_priv(pltfm_host);
	व्योम __iomem *base = host->ioaddr + (reg & ~3);
	u8 shअगरt = (reg & 3) << 3;
	u32 mask = ~(0xffff << shअगरt);

	चयन (reg) अणु
	हाल SDHCI_TRANSFER_MODE:
		mcf_data->aside = val;
		वापस;
	हाल SDHCI_COMMAND:
		अगर (host->cmd->opcode == MMC_STOP_TRANSMISSION)
			val |= SDHCI_CMD_ABORTCMD;

		/*
		 * As क्रम the fsl driver,
		 * we have to set the mode in a single ग_लिखो here.
		 */
		ग_लिखोl(val << 16 | mcf_data->aside,
		       host->ioaddr + SDHCI_TRANSFER_MODE);
		वापस;
	पूर्ण

	ग_लिखोl((पढ़ोl(base) & mask) | (val << shअगरt), base);
पूर्ण

अटल व्योम esdhc_mcf_ग_लिखोl_be(काष्ठा sdhci_host *host, u32 val, पूर्णांक reg)
अणु
	ग_लिखोl(val, host->ioaddr + reg);
पूर्ण

अटल u8 esdhc_mcf_पढ़ोb_be(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	अगर (reg == SDHCI_HOST_CONTROL) अणु
		u8 __iomem *base = host->ioaddr + (reg & ~3);
		u16 val = पढ़ोw(base + 2);
		u8 dma_bits = (val >> 5) & SDHCI_CTRL_DMA_MASK;
		u8 host_ctrl = val & 0xff;

		host_ctrl &= ~SDHCI_CTRL_DMA_MASK;
		host_ctrl |= dma_bits;

		वापस host_ctrl;
	पूर्ण

	वापस पढ़ोb(host->ioaddr + (reg ^ 0x3));
पूर्ण

अटल u16 esdhc_mcf_पढ़ोw_be(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	/*
	 * For SDHCI_HOST_VERSION, sdhci specs defines 0xFE,
	 * a wrong offset क्रम us, we are at 0xFC.
	 */
	अगर (reg == SDHCI_HOST_VERSION)
		reg -= 2;

	वापस पढ़ोw(host->ioaddr + (reg ^ 0x2));
पूर्ण

अटल u32 esdhc_mcf_पढ़ोl_be(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	u32 val;

	val = पढ़ोl(host->ioaddr + reg);

	/*
	 * RM (25.3.9) sd pin घड़ी must never exceed 25Mhz.
	 * So क्रमcing legacy mode at 25Mhz.
	 */
	अगर (unlikely(reg == SDHCI_CAPABILITIES))
		val &= ~SDHCI_CAN_DO_HISPD;

	अगर (unlikely(reg == SDHCI_INT_STATUS)) अणु
		अगर (val & ESDHC_INT_VENDOR_SPEC_DMA_ERR) अणु
			val &= ~ESDHC_INT_VENDOR_SPEC_DMA_ERR;
			val |= SDHCI_INT_ADMA_ERROR;
		पूर्ण
	पूर्ण

	वापस val;
पूर्ण

अटल अचिन्हित पूर्णांक esdhc_mcf_get_max_समयout_count(काष्ठा sdhci_host *host)
अणु
	वापस 1 << 27;
पूर्ण

अटल व्योम esdhc_mcf_set_समयout(काष्ठा sdhci_host *host,
				  काष्ठा mmc_command *cmd)
अणु
	/* Use maximum समयout counter */
	esdhc_clrset_be(host, ESDHC_SYS_CTRL_DTOCV_MASK, 0xE,
			SDHCI_TIMEOUT_CONTROL);
पूर्ण

अटल व्योम esdhc_mcf_reset(काष्ठा sdhci_host *host, u8 mask)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा pltfm_mcf_data *mcf_data = sdhci_pltfm_priv(pltfm_host);

	sdhci_reset(host, mask);

	esdhc_clrset_be(host, ESDHC_CTRL_BUSWIDTH_MASK,
			mcf_data->current_bus_width, SDHCI_HOST_CONTROL);

	sdhci_ग_लिखोl(host, host->ier, SDHCI_INT_ENABLE);
	sdhci_ग_लिखोl(host, host->ier, SDHCI_SIGNAL_ENABLE);
पूर्ण

अटल अचिन्हित पूर्णांक esdhc_mcf_pltfm_get_max_घड़ी(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);

	वापस pltfm_host->घड़ी;
पूर्ण

अटल अचिन्हित पूर्णांक esdhc_mcf_pltfm_get_min_घड़ी(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);

	वापस pltfm_host->घड़ी / 256 / 16;
पूर्ण

अटल व्योम esdhc_mcf_pltfm_set_घड़ी(काष्ठा sdhci_host *host,
				      अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	अचिन्हित दीर्घ *pll_dr = (अचिन्हित दीर्घ *)MCF_PLL_DR;
	u32 fvco, fsys, fesdhc, temp;
	स्थिर पूर्णांक sdclkfs[] = अणु2, 4, 8, 16, 32, 64, 128, 256पूर्ण;
	पूर्णांक delta, old_delta = घड़ी;
	पूर्णांक i, q, ri, rq;

	अगर (घड़ी == 0) अणु
		host->mmc->actual_घड़ी = 0;
		वापस;
	पूर्ण

	/*
	 * ColdFire eSDHC घड़ी.s
	 *
	 * pll -+-> / outभाग1 --> fsys
	 *      +-> / outभाग3 --> eSDHC घड़ी ---> / SDCCLKFS / DVS
	 *
	 * mcf5441x datasheet says:
	 * (8.1.2) eSDHC should be 40 MHz max
	 * (25.3.9) eSDHC input is, as example, 96 Mhz ...
	 * (25.3.9) sd pin घड़ी must never exceed 25Mhz
	 *
	 * fvco = fsys * outdvi1 + 1
	 * fshdc = fvco / outभाग3 + 1
	 */
	temp = पढ़ोl(pll_dr);
	fsys = pltfm_host->घड़ी;
	fvco = fsys * ((temp & 0x1f) + 1);
	fesdhc = fvco / (((temp >> 10) & 0x1f) + 1);

	क्रम (i = 0; i < 8; ++i) अणु
		पूर्णांक result = fesdhc / sdclkfs[i];

		क्रम (q = 1; q < 17; ++q) अणु
			पूर्णांक finale = result / q;

			delta = असल(घड़ी - finale);

			अगर (delta < old_delta) अणु
				old_delta = delta;
				ri = i;
				rq = q;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Apply भागisors and re-enable all the घड़ीs
	 */
	temp = ((sdclkfs[ri] >> 1) << 8) | ((rq - 1) << 4) |
		(ESDHC_CLOCK_IPGEN | ESDHC_CLOCK_HCKEN | ESDHC_CLOCK_PEREN);
	esdhc_clrset_be(host, 0x0000fff7, temp, SDHCI_CLOCK_CONTROL);

	host->mmc->actual_घड़ी = घड़ी;

	mdelay(1);
पूर्ण

अटल व्योम esdhc_mcf_pltfm_set_bus_width(काष्ठा sdhci_host *host, पूर्णांक width)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा pltfm_mcf_data *mcf_data = sdhci_pltfm_priv(pltfm_host);

	चयन (width) अणु
	हाल MMC_BUS_WIDTH_4:
		mcf_data->current_bus_width = ESDHC_CTRL_4BITBUS;
		अवरोध;
	शेष:
		mcf_data->current_bus_width = 0;
		अवरोध;
	पूर्ण

	esdhc_clrset_be(host, ESDHC_CTRL_BUSWIDTH_MASK,
			mcf_data->current_bus_width, SDHCI_HOST_CONTROL);
पूर्ण

अटल व्योम esdhc_mcf_request_करोne(काष्ठा sdhci_host *host,
				   काष्ठा mmc_request *mrq)
अणु
	काष्ठा scatterlist *sg;
	u32 *buffer;
	पूर्णांक i;

	अगर (!mrq->data || !mrq->data->bytes_xfered)
		जाओ निकास_करोne;

	अगर (mmc_get_dma_dir(mrq->data) != DMA_FROM_DEVICE)
		जाओ निकास_करोne;

	/*
	 * On mcf5441x there is no hw sdma option/flag to select the dma
	 * transfer endiannes. A swap after the transfer is needed.
	 */
	क्रम_each_sg(mrq->data->sg, sg, mrq->data->sg_len, i) अणु
		buffer = (u32 *)sg_virt(sg);
		esdhc_mcf_buffer_swap32(buffer, sg->length);
	पूर्ण

निकास_करोne:
	mmc_request_करोne(host->mmc, mrq);
पूर्ण

अटल व्योम esdhc_mcf_copy_to_bounce_buffer(काष्ठा sdhci_host *host,
					    काष्ठा mmc_data *data,
					    अचिन्हित पूर्णांक length)
अणु
	sg_copy_to_buffer(data->sg, data->sg_len,
			  host->bounce_buffer, length);

	esdhc_mcf_buffer_swap32((u32 *)host->bounce_buffer,
				data->blksz * data->blocks);
पूर्ण

अटल काष्ठा sdhci_ops sdhci_esdhc_ops = अणु
	.reset = esdhc_mcf_reset,
	.set_घड़ी = esdhc_mcf_pltfm_set_घड़ी,
	.get_max_घड़ी = esdhc_mcf_pltfm_get_max_घड़ी,
	.get_min_घड़ी = esdhc_mcf_pltfm_get_min_घड़ी,
	.set_bus_width = esdhc_mcf_pltfm_set_bus_width,
	.get_max_समयout_count = esdhc_mcf_get_max_समयout_count,
	.set_समयout = esdhc_mcf_set_समयout,
	.ग_लिखो_b = esdhc_mcf_ग_लिखोb_be,
	.ग_लिखो_w = esdhc_mcf_ग_लिखोw_be,
	.ग_लिखो_l = esdhc_mcf_ग_लिखोl_be,
	.पढ़ो_b = esdhc_mcf_पढ़ोb_be,
	.पढ़ो_w = esdhc_mcf_पढ़ोw_be,
	.पढ़ो_l = esdhc_mcf_पढ़ोl_be,
	.copy_to_bounce_buffer = esdhc_mcf_copy_to_bounce_buffer,
	.request_करोne = esdhc_mcf_request_करोne,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_esdhc_mcf_pdata = अणु
	.ops = &sdhci_esdhc_ops,
	.quirks = ESDHC_DEFAULT_QUIRKS | SDHCI_QUIRK_FORCE_DMA,
		 /*
		  * Mandatory quirk,
		  * controller करोes not support cmd23,
		  * without, on > 8G cards cmd23 is used, and
		  * driver बार out.
		  */
		  SDHCI_QUIRK2_HOST_NO_CMD23,
पूर्ण;

अटल पूर्णांक esdhc_mcf_plat_init(काष्ठा sdhci_host *host,
			       काष्ठा pltfm_mcf_data *mcf_data)
अणु
	काष्ठा mcf_esdhc_platक्रमm_data *plat_data;
	काष्ठा device *dev = mmc_dev(host->mmc);

	अगर (!dev->platक्रमm_data) अणु
		dev_err(dev, "no platform data!\n");
		वापस -EINVAL;
	पूर्ण

	plat_data = (काष्ठा mcf_esdhc_platक्रमm_data *)dev->platक्रमm_data;

	/* Card_detect */
	चयन (plat_data->cd_type) अणु
	शेष:
	हाल ESDHC_CD_CONTROLLER:
		/* We have a working card_detect back */
		host->quirks &= ~SDHCI_QUIRK_BROKEN_CARD_DETECTION;
		अवरोध;
	हाल ESDHC_CD_PERMANENT:
		host->mmc->caps |= MMC_CAP_NONREMOVABLE;
		अवरोध;
	हाल ESDHC_CD_NONE:
		अवरोध;
	पूर्ण

	चयन (plat_data->max_bus_width) अणु
	हाल 4:
		host->mmc->caps |= MMC_CAP_4_BIT_DATA;
		अवरोध;
	हाल 1:
	शेष:
		host->quirks |= SDHCI_QUIRK_FORCE_1_BIT_DATA;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sdhci_esdhc_mcf_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host;
	काष्ठा sdhci_pltfm_host *pltfm_host;
	काष्ठा pltfm_mcf_data *mcf_data;
	पूर्णांक err;

	host = sdhci_pltfm_init(pdev, &sdhci_esdhc_mcf_pdata,
				माप(*mcf_data));

	अगर (IS_ERR(host))
		वापस PTR_ERR(host);

	pltfm_host = sdhci_priv(host);
	mcf_data = sdhci_pltfm_priv(pltfm_host);

	host->sdma_boundary = 0;

	host->flags |= SDHCI_AUTO_CMD12;

	mcf_data->clk_ipg = devm_clk_get(&pdev->dev, "ipg");
	अगर (IS_ERR(mcf_data->clk_ipg)) अणु
		err = PTR_ERR(mcf_data->clk_ipg);
		जाओ err_निकास;
	पूर्ण

	mcf_data->clk_ahb = devm_clk_get(&pdev->dev, "ahb");
	अगर (IS_ERR(mcf_data->clk_ahb)) अणु
		err = PTR_ERR(mcf_data->clk_ahb);
		जाओ err_निकास;
	पूर्ण

	mcf_data->clk_per = devm_clk_get(&pdev->dev, "per");
	अगर (IS_ERR(mcf_data->clk_per)) अणु
		err = PTR_ERR(mcf_data->clk_per);
		जाओ err_निकास;
	पूर्ण

	pltfm_host->clk = mcf_data->clk_per;
	pltfm_host->घड़ी = clk_get_rate(pltfm_host->clk);
	err = clk_prepare_enable(mcf_data->clk_per);
	अगर (err)
		जाओ err_निकास;

	err = clk_prepare_enable(mcf_data->clk_ipg);
	अगर (err)
		जाओ unprep_per;

	err = clk_prepare_enable(mcf_data->clk_ahb);
	अगर (err)
		जाओ unprep_ipg;

	err = esdhc_mcf_plat_init(host, mcf_data);
	अगर (err)
		जाओ unprep_ahb;

	err = sdhci_setup_host(host);
	अगर (err)
		जाओ unprep_ahb;

	अगर (!host->bounce_buffer) अणु
		dev_err(&pdev->dev, "bounce buffer not allocated");
		err = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	err = __sdhci_add_host(host);
	अगर (err)
		जाओ cleanup;

	वापस 0;

cleanup:
	sdhci_cleanup_host(host);
unprep_ahb:
	clk_disable_unprepare(mcf_data->clk_ahb);
unprep_ipg:
	clk_disable_unprepare(mcf_data->clk_ipg);
unprep_per:
	clk_disable_unprepare(mcf_data->clk_per);
err_निकास:
	sdhci_pltfm_मुक्त(pdev);

	वापस err;
पूर्ण

अटल पूर्णांक sdhci_esdhc_mcf_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा pltfm_mcf_data *mcf_data = sdhci_pltfm_priv(pltfm_host);

	sdhci_हटाओ_host(host, 0);

	clk_disable_unprepare(mcf_data->clk_ipg);
	clk_disable_unprepare(mcf_data->clk_ahb);
	clk_disable_unprepare(mcf_data->clk_per);

	sdhci_pltfm_मुक्त(pdev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sdhci_esdhc_mcf_driver = अणु
	.driver	= अणु
		.name = "sdhci-esdhc-mcf",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
	.probe = sdhci_esdhc_mcf_probe,
	.हटाओ = sdhci_esdhc_mcf_हटाओ,
पूर्ण;

module_platक्रमm_driver(sdhci_esdhc_mcf_driver);

MODULE_DESCRIPTION("SDHCI driver for Freescale ColdFire eSDHC");
MODULE_AUTHOR("Angelo Dureghello <angelo.dureghello@timesys.com>");
MODULE_LICENSE("GPL v2");
