<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Copyright (C) 2019 ASPEED Technology Inc. */
/* Copyright (C) 2019 IBM Corp. */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/math64.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>

#समावेश "sdhci-pltfm.h"

#घोषणा ASPEED_SDC_INFO			0x00
#घोषणा   ASPEED_SDC_S1_MMC8		BIT(25)
#घोषणा   ASPEED_SDC_S0_MMC8		BIT(24)
#घोषणा ASPEED_SDC_PHASE		0xf4
#घोषणा   ASPEED_SDC_S1_PHASE_IN	GENMASK(25, 21)
#घोषणा   ASPEED_SDC_S0_PHASE_IN	GENMASK(20, 16)
#घोषणा   ASPEED_SDC_S1_PHASE_OUT	GENMASK(15, 11)
#घोषणा   ASPEED_SDC_S1_PHASE_IN_EN	BIT(10)
#घोषणा   ASPEED_SDC_S1_PHASE_OUT_EN	GENMASK(9, 8)
#घोषणा   ASPEED_SDC_S0_PHASE_OUT	GENMASK(7, 3)
#घोषणा   ASPEED_SDC_S0_PHASE_IN_EN	BIT(2)
#घोषणा   ASPEED_SDC_S0_PHASE_OUT_EN	GENMASK(1, 0)
#घोषणा   ASPEED_SDC_PHASE_MAX		31

काष्ठा aspeed_sdc अणु
	काष्ठा clk *clk;
	काष्ठा resource *res;

	spinlock_t lock;
	व्योम __iomem *regs;
पूर्ण;

काष्ठा aspeed_sdhci_tap_param अणु
	bool valid;

#घोषणा ASPEED_SDHCI_TAP_PARAM_INVERT_CLK	BIT(4)
	u8 in;
	u8 out;
पूर्ण;

काष्ठा aspeed_sdhci_tap_desc अणु
	u32 tap_mask;
	u32 enable_mask;
	u8 enable_value;
पूर्ण;

काष्ठा aspeed_sdhci_phase_desc अणु
	काष्ठा aspeed_sdhci_tap_desc in;
	काष्ठा aspeed_sdhci_tap_desc out;
पूर्ण;

काष्ठा aspeed_sdhci_pdata अणु
	अचिन्हित पूर्णांक clk_भाग_start;
	स्थिर काष्ठा aspeed_sdhci_phase_desc *phase_desc;
	माप_प्रकार nr_phase_descs;
पूर्ण;

काष्ठा aspeed_sdhci अणु
	स्थिर काष्ठा aspeed_sdhci_pdata *pdata;
	काष्ठा aspeed_sdc *parent;
	u32 width_mask;
	काष्ठा mmc_clk_phase_map phase_map;
	स्थिर काष्ठा aspeed_sdhci_phase_desc *phase_desc;
पूर्ण;

अटल व्योम aspeed_sdc_configure_8bit_mode(काष्ठा aspeed_sdc *sdc,
					   काष्ठा aspeed_sdhci *sdhci,
					   bool bus8)
अणु
	u32 info;

	/* Set/clear 8 bit mode */
	spin_lock(&sdc->lock);
	info = पढ़ोl(sdc->regs + ASPEED_SDC_INFO);
	अगर (bus8)
		info |= sdhci->width_mask;
	अन्यथा
		info &= ~sdhci->width_mask;
	ग_लिखोl(info, sdc->regs + ASPEED_SDC_INFO);
	spin_unlock(&sdc->lock);
पूर्ण

अटल u32
aspeed_sdc_set_phase_tap(स्थिर काष्ठा aspeed_sdhci_tap_desc *desc,
			 u8 tap, bool enable, u32 reg)
अणु
	reg &= ~(desc->enable_mask | desc->tap_mask);
	अगर (enable) अणु
		reg |= tap << __ffs(desc->tap_mask);
		reg |= desc->enable_value << __ffs(desc->enable_mask);
	पूर्ण

	वापस reg;
पूर्ण

अटल व्योम
aspeed_sdc_set_phase_taps(काष्ठा aspeed_sdc *sdc,
			  स्थिर काष्ठा aspeed_sdhci_phase_desc *desc,
			  स्थिर काष्ठा aspeed_sdhci_tap_param *taps)
अणु
	u32 reg;

	spin_lock(&sdc->lock);
	reg = पढ़ोl(sdc->regs + ASPEED_SDC_PHASE);

	reg = aspeed_sdc_set_phase_tap(&desc->in, taps->in, taps->valid, reg);
	reg = aspeed_sdc_set_phase_tap(&desc->out, taps->out, taps->valid, reg);

	ग_लिखोl(reg, sdc->regs + ASPEED_SDC_PHASE);
	spin_unlock(&sdc->lock);
पूर्ण

#घोषणा PICOSECONDS_PER_SECOND		1000000000000ULL
#घोषणा ASPEED_SDHCI_NR_TAPS		15
/* Measured value with *handwave* environmentals and अटल loading */
#घोषणा ASPEED_SDHCI_MAX_TAP_DELAY_PS	1253
अटल पूर्णांक aspeed_sdhci_phase_to_tap(काष्ठा device *dev, अचिन्हित दीर्घ rate_hz,
				     पूर्णांक phase_deg)
अणु
	u64 phase_period_ps;
	u64 prop_delay_ps;
	u64 clk_period_ps;
	अचिन्हित पूर्णांक tap;
	u8 inverted;

	phase_deg %= 360;

	अगर (phase_deg >= 180) अणु
		inverted = ASPEED_SDHCI_TAP_PARAM_INVERT_CLK;
		phase_deg -= 180;
		dev_dbg(dev,
			"Inverting clock to reduce phase correction from %d to %d degrees\n",
			phase_deg + 180, phase_deg);
	पूर्ण अन्यथा अणु
		inverted = 0;
	पूर्ण

	prop_delay_ps = ASPEED_SDHCI_MAX_TAP_DELAY_PS / ASPEED_SDHCI_NR_TAPS;
	clk_period_ps = भाग_u64(PICOSECONDS_PER_SECOND, (u64)rate_hz);
	phase_period_ps = भाग_u64((u64)phase_deg * clk_period_ps, 360ULL);

	tap = भाग_u64(phase_period_ps, prop_delay_ps);
	अगर (tap > ASPEED_SDHCI_NR_TAPS) अणु
		dev_warn(dev,
			 "Requested out of range phase tap %d for %d degrees of phase compensation at %luHz, clamping to tap %d\n",
			 tap, phase_deg, rate_hz, ASPEED_SDHCI_NR_TAPS);
		tap = ASPEED_SDHCI_NR_TAPS;
	पूर्ण

	वापस inverted | tap;
पूर्ण

अटल व्योम
aspeed_sdhci_phases_to_taps(काष्ठा device *dev, अचिन्हित दीर्घ rate,
			    स्थिर काष्ठा mmc_clk_phase *phases,
			    काष्ठा aspeed_sdhci_tap_param *taps)
अणु
	taps->valid = phases->valid;

	अगर (!phases->valid)
		वापस;

	taps->in = aspeed_sdhci_phase_to_tap(dev, rate, phases->in_deg);
	taps->out = aspeed_sdhci_phase_to_tap(dev, rate, phases->out_deg);
पूर्ण

अटल व्योम
aspeed_sdhci_configure_phase(काष्ठा sdhci_host *host, अचिन्हित दीर्घ rate)
अणु
	काष्ठा aspeed_sdhci_tap_param _taps = अणु0पूर्ण, *taps = &_taps;
	काष्ठा mmc_clk_phase *params;
	काष्ठा aspeed_sdhci *sdhci;
	काष्ठा device *dev;

	dev = mmc_dev(host->mmc);
	sdhci = sdhci_pltfm_priv(sdhci_priv(host));

	अगर (!sdhci->phase_desc)
		वापस;

	params = &sdhci->phase_map.phase[host->timing];
	aspeed_sdhci_phases_to_taps(dev, rate, params, taps);
	aspeed_sdc_set_phase_taps(sdhci->parent, sdhci->phase_desc, taps);
	dev_dbg(dev,
		"Using taps [%d, %d] for [%d, %d] degrees of phase correction at %luHz (%d)\n",
		taps->in & ASPEED_SDHCI_NR_TAPS,
		taps->out & ASPEED_SDHCI_NR_TAPS,
		params->in_deg, params->out_deg, rate, host->timing);
पूर्ण

अटल व्योम aspeed_sdhci_set_घड़ी(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host;
	अचिन्हित दीर्घ parent, bus;
	काष्ठा aspeed_sdhci *sdhci;
	पूर्णांक भाग;
	u16 clk;

	pltfm_host = sdhci_priv(host);
	sdhci = sdhci_pltfm_priv(pltfm_host);

	parent = clk_get_rate(pltfm_host->clk);

	sdhci_ग_लिखोw(host, 0, SDHCI_CLOCK_CONTROL);

	अगर (घड़ी == 0)
		वापस;

	अगर (WARN_ON(घड़ी > host->max_clk))
		घड़ी = host->max_clk;

	/*
	 * Regarding the AST2600:
	 *
	 * If (EMMC12C[7:6], EMMC12C[15:8] == 0) then
	 *   period of SDCLK = period of SDMCLK.
	 *
	 * If (EMMC12C[7:6], EMMC12C[15:8] != 0) then
	 *   period of SDCLK = period of SDMCLK * 2 * (EMMC12C[7:6], EMMC[15:8])
	 *
	 * If you keep EMMC12C[7:6] = 0 and EMMC12C[15:8] as one-hot,
	 * 0x1/0x2/0x4/etc, you will find it is compatible to AST2400 or AST2500
	 *
	 * Keep the one-hot behaviour क्रम backwards compatibility except क्रम
	 * supporting the value 0 in (EMMC12C[7:6], EMMC12C[15:8]), and capture
	 * the 0-value capability in clk_भाग_start.
	 */
	क्रम (भाग = sdhci->pdata->clk_भाग_start; भाग < 256; भाग *= 2) अणु
		bus = parent / भाग;
		अगर (bus <= घड़ी)
			अवरोध;
	पूर्ण

	भाग >>= 1;

	clk = भाग << SDHCI_DIVIDER_SHIFT;

	aspeed_sdhci_configure_phase(host, bus);

	sdhci_enable_clk(host, clk);
पूर्ण

अटल अचिन्हित पूर्णांक aspeed_sdhci_get_max_घड़ी(काष्ठा sdhci_host *host)
अणु
	अगर (host->mmc->f_max)
		वापस host->mmc->f_max;

	वापस sdhci_pltfm_clk_get_max_घड़ी(host);
पूर्ण

अटल व्योम aspeed_sdhci_set_bus_width(काष्ठा sdhci_host *host, पूर्णांक width)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_priv;
	काष्ठा aspeed_sdhci *aspeed_sdhci;
	काष्ठा aspeed_sdc *aspeed_sdc;
	u8 ctrl;

	pltfm_priv = sdhci_priv(host);
	aspeed_sdhci = sdhci_pltfm_priv(pltfm_priv);
	aspeed_sdc = aspeed_sdhci->parent;

	/* Set/clear 8-bit mode */
	aspeed_sdc_configure_8bit_mode(aspeed_sdc, aspeed_sdhci,
				       width == MMC_BUS_WIDTH_8);

	/* Set/clear 1 or 4 bit mode */
	ctrl = sdhci_पढ़ोb(host, SDHCI_HOST_CONTROL);
	अगर (width == MMC_BUS_WIDTH_4)
		ctrl |= SDHCI_CTRL_4BITBUS;
	अन्यथा
		ctrl &= ~SDHCI_CTRL_4BITBUS;
	sdhci_ग_लिखोb(host, ctrl, SDHCI_HOST_CONTROL);
पूर्ण

अटल u32 aspeed_sdhci_पढ़ोl(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	u32 val = पढ़ोl(host->ioaddr + reg);

	अगर (unlikely(reg == SDHCI_PRESENT_STATE) &&
	    (host->mmc->caps2 & MMC_CAP2_CD_ACTIVE_HIGH))
		val ^= SDHCI_CARD_PRESENT;

	वापस val;
पूर्ण

अटल स्थिर काष्ठा sdhci_ops aspeed_sdhci_ops = अणु
	.पढ़ो_l = aspeed_sdhci_पढ़ोl,
	.set_घड़ी = aspeed_sdhci_set_घड़ी,
	.get_max_घड़ी = aspeed_sdhci_get_max_घड़ी,
	.set_bus_width = aspeed_sdhci_set_bus_width,
	.get_समयout_घड़ी = sdhci_pltfm_clk_get_max_घड़ी,
	.reset = sdhci_reset,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data aspeed_sdhci_pdata = अणु
	.ops = &aspeed_sdhci_ops,
	.quirks = SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN,
पूर्ण;

अटल अंतरभूत पूर्णांक aspeed_sdhci_calculate_slot(काष्ठा aspeed_sdhci *dev,
					      काष्ठा resource *res)
अणु
	resource_माप_प्रकार delta;

	अगर (!res || resource_type(res) != IORESOURCE_MEM)
		वापस -EINVAL;

	अगर (res->start < dev->parent->res->start)
		वापस -EINVAL;

	delta = res->start - dev->parent->res->start;
	अगर (delta & (0x100 - 1))
		वापस -EINVAL;

	वापस (delta / 0x100) - 1;
पूर्ण

अटल पूर्णांक aspeed_sdhci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा aspeed_sdhci_pdata *aspeed_pdata;
	काष्ठा sdhci_pltfm_host *pltfm_host;
	काष्ठा aspeed_sdhci *dev;
	काष्ठा sdhci_host *host;
	काष्ठा resource *res;
	पूर्णांक slot;
	पूर्णांक ret;

	aspeed_pdata = of_device_get_match_data(&pdev->dev);
	अगर (!aspeed_pdata) अणु
		dev_err(&pdev->dev, "Missing platform configuration data\n");
		वापस -EINVAL;
	पूर्ण

	host = sdhci_pltfm_init(pdev, &aspeed_sdhci_pdata, माप(*dev));
	अगर (IS_ERR(host))
		वापस PTR_ERR(host);

	pltfm_host = sdhci_priv(host);
	dev = sdhci_pltfm_priv(pltfm_host);
	dev->pdata = aspeed_pdata;
	dev->parent = dev_get_drvdata(pdev->dev.parent);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	slot = aspeed_sdhci_calculate_slot(dev, res);

	अगर (slot < 0)
		वापस slot;
	अन्यथा अगर (slot >= 2)
		वापस -EINVAL;

	अगर (slot < dev->pdata->nr_phase_descs) अणु
		dev->phase_desc = &dev->pdata->phase_desc[slot];
	पूर्ण अन्यथा अणु
		dev_info(&pdev->dev,
			 "Phase control not supported for slot %d\n", slot);
		dev->phase_desc = शून्य;
	पूर्ण

	dev->width_mask = !slot ? ASPEED_SDC_S0_MMC8 : ASPEED_SDC_S1_MMC8;

	dev_info(&pdev->dev, "Configured for slot %d\n", slot);

	sdhci_get_of_property(pdev);

	pltfm_host->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(pltfm_host->clk))
		वापस PTR_ERR(pltfm_host->clk);

	ret = clk_prepare_enable(pltfm_host->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to enable SDIO clock\n");
		जाओ err_pltfm_मुक्त;
	पूर्ण

	ret = mmc_of_parse(host->mmc);
	अगर (ret)
		जाओ err_sdhci_add;

	अगर (dev->phase_desc)
		mmc_of_parse_clk_phase(host->mmc, &dev->phase_map);

	ret = sdhci_add_host(host);
	अगर (ret)
		जाओ err_sdhci_add;

	वापस 0;

err_sdhci_add:
	clk_disable_unprepare(pltfm_host->clk);
err_pltfm_मुक्त:
	sdhci_pltfm_मुक्त(pdev);
	वापस ret;
पूर्ण

अटल पूर्णांक aspeed_sdhci_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host;
	काष्ठा sdhci_host *host;
	पूर्णांक dead = 0;

	host = platक्रमm_get_drvdata(pdev);
	pltfm_host = sdhci_priv(host);

	sdhci_हटाओ_host(host, dead);

	clk_disable_unprepare(pltfm_host->clk);

	sdhci_pltfm_मुक्त(pdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा aspeed_sdhci_pdata ast2400_sdhci_pdata = अणु
	.clk_भाग_start = 2,
पूर्ण;

अटल स्थिर काष्ठा aspeed_sdhci_phase_desc ast2600_sdhci_phase[] = अणु
	/* SDHCI/Slot 0 */
	[0] = अणु
		.in = अणु
			.tap_mask = ASPEED_SDC_S0_PHASE_IN,
			.enable_mask = ASPEED_SDC_S0_PHASE_IN_EN,
			.enable_value = 1,
		पूर्ण,
		.out = अणु
			.tap_mask = ASPEED_SDC_S0_PHASE_OUT,
			.enable_mask = ASPEED_SDC_S0_PHASE_OUT_EN,
			.enable_value = 3,
		पूर्ण,
	पूर्ण,
	/* SDHCI/Slot 1 */
	[1] = अणु
		.in = अणु
			.tap_mask = ASPEED_SDC_S1_PHASE_IN,
			.enable_mask = ASPEED_SDC_S1_PHASE_IN_EN,
			.enable_value = 1,
		पूर्ण,
		.out = अणु
			.tap_mask = ASPEED_SDC_S1_PHASE_OUT,
			.enable_mask = ASPEED_SDC_S1_PHASE_OUT_EN,
			.enable_value = 3,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा aspeed_sdhci_pdata ast2600_sdhci_pdata = अणु
	.clk_भाग_start = 1,
	.phase_desc = ast2600_sdhci_phase,
	.nr_phase_descs = ARRAY_SIZE(ast2600_sdhci_phase),
पूर्ण;

अटल स्थिर काष्ठा of_device_id aspeed_sdhci_of_match[] = अणु
	अणु .compatible = "aspeed,ast2400-sdhci", .data = &ast2400_sdhci_pdata, पूर्ण,
	अणु .compatible = "aspeed,ast2500-sdhci", .data = &ast2400_sdhci_pdata, पूर्ण,
	अणु .compatible = "aspeed,ast2600-sdhci", .data = &ast2600_sdhci_pdata, पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver aspeed_sdhci_driver = अणु
	.driver		= अणु
		.name	= "sdhci-aspeed",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = aspeed_sdhci_of_match,
	पूर्ण,
	.probe		= aspeed_sdhci_probe,
	.हटाओ		= aspeed_sdhci_हटाओ,
पूर्ण;

अटल पूर्णांक aspeed_sdc_probe(काष्ठा platक्रमm_device *pdev)

अणु
	काष्ठा device_node *parent, *child;
	काष्ठा aspeed_sdc *sdc;
	पूर्णांक ret;

	sdc = devm_kzalloc(&pdev->dev, माप(*sdc), GFP_KERNEL);
	अगर (!sdc)
		वापस -ENOMEM;

	spin_lock_init(&sdc->lock);

	sdc->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(sdc->clk))
		वापस PTR_ERR(sdc->clk);

	ret = clk_prepare_enable(sdc->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to enable SDCLK\n");
		वापस ret;
	पूर्ण

	sdc->res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	sdc->regs = devm_ioremap_resource(&pdev->dev, sdc->res);
	अगर (IS_ERR(sdc->regs)) अणु
		ret = PTR_ERR(sdc->regs);
		जाओ err_clk;
	पूर्ण

	dev_set_drvdata(&pdev->dev, sdc);

	parent = pdev->dev.of_node;
	क्रम_each_available_child_of_node(parent, child) अणु
		काष्ठा platक्रमm_device *cpdev;

		cpdev = of_platक्रमm_device_create(child, शून्य, &pdev->dev);
		अगर (!cpdev) अणु
			of_node_put(child);
			ret = -ENODEV;
			जाओ err_clk;
		पूर्ण
	पूर्ण

	वापस 0;

err_clk:
	clk_disable_unprepare(sdc->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक aspeed_sdc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aspeed_sdc *sdc = dev_get_drvdata(&pdev->dev);

	clk_disable_unprepare(sdc->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id aspeed_sdc_of_match[] = अणु
	अणु .compatible = "aspeed,ast2400-sd-controller", पूर्ण,
	अणु .compatible = "aspeed,ast2500-sd-controller", पूर्ण,
	अणु .compatible = "aspeed,ast2600-sd-controller", पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, aspeed_sdc_of_match);

अटल काष्ठा platक्रमm_driver aspeed_sdc_driver = अणु
	.driver		= अणु
		.name	= "sd-controller-aspeed",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.pm	= &sdhci_pltfm_pmops,
		.of_match_table = aspeed_sdc_of_match,
	पूर्ण,
	.probe		= aspeed_sdc_probe,
	.हटाओ		= aspeed_sdc_हटाओ,
पूर्ण;

#अगर defined(CONFIG_MMC_SDHCI_OF_ASPEED_TEST)
#समावेश "sdhci-of-aspeed-test.c"

अटल अंतरभूत पूर्णांक aspeed_sdc_tests_init(व्योम)
अणु
	वापस __kunit_test_suites_init(aspeed_sdc_test_suites);
पूर्ण

अटल अंतरभूत व्योम aspeed_sdc_tests_निकास(व्योम)
अणु
	__kunit_test_suites_निकास(aspeed_sdc_test_suites);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक aspeed_sdc_tests_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम aspeed_sdc_tests_निकास(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init aspeed_sdc_init(व्योम)
अणु
	पूर्णांक rc;

	rc = platक्रमm_driver_रेजिस्टर(&aspeed_sdhci_driver);
	अगर (rc < 0)
		वापस rc;

	rc = platक्रमm_driver_रेजिस्टर(&aspeed_sdc_driver);
	अगर (rc < 0)
		जाओ cleanup_sdhci;

	rc = aspeed_sdc_tests_init();
	अगर (rc < 0) अणु
		platक्रमm_driver_unरेजिस्टर(&aspeed_sdc_driver);
		जाओ cleanup_sdhci;
	पूर्ण

	वापस 0;

cleanup_sdhci:
	platक्रमm_driver_unरेजिस्टर(&aspeed_sdhci_driver);

	वापस rc;
पूर्ण
module_init(aspeed_sdc_init);

अटल व्योम __निकास aspeed_sdc_निकास(व्योम)
अणु
	aspeed_sdc_tests_निकास();

	platक्रमm_driver_unरेजिस्टर(&aspeed_sdc_driver);
	platक्रमm_driver_unरेजिस्टर(&aspeed_sdhci_driver);
पूर्ण
module_निकास(aspeed_sdc_निकास);

MODULE_DESCRIPTION("Driver for the ASPEED SD/SDIO/SDHCI Controllers");
MODULE_AUTHOR("Ryan Chen <ryan_chen@aspeedtech.com>");
MODULE_AUTHOR("Andrew Jeffery <andrew@aj.id.au>");
MODULE_LICENSE("GPL");
