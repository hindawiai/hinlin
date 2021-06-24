<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 Pengutronix, Sascha Hauer <kernel@pengutronix.de>
 */
#समावेश <linux/clk.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/soc/mediatek/infracfg.h>

#समावेश <dt-bindings/घातer/mt2701-घातer.h>
#समावेश <dt-bindings/घातer/mt2712-घातer.h>
#समावेश <dt-bindings/घातer/mt6797-घातer.h>
#समावेश <dt-bindings/घातer/mt7622-घातer.h>
#समावेश <dt-bindings/घातer/mt7623a-घातer.h>
#समावेश <dt-bindings/घातer/mt8173-घातer.h>

#घोषणा MTK_POLL_DELAY_US   10
#घोषणा MTK_POLL_TIMEOUT    USEC_PER_SEC

#घोषणा MTK_SCPD_ACTIVE_WAKEUP		BIT(0)
#घोषणा MTK_SCPD_FWAIT_SRAM		BIT(1)
#घोषणा MTK_SCPD_CAPS(_scpd, _x)	((_scpd)->data->caps & (_x))

#घोषणा SPM_VDE_PWR_CON			0x0210
#घोषणा SPM_MFG_PWR_CON			0x0214
#घोषणा SPM_VEN_PWR_CON			0x0230
#घोषणा SPM_ISP_PWR_CON			0x0238
#घोषणा SPM_DIS_PWR_CON			0x023c
#घोषणा SPM_CONN_PWR_CON		0x0280
#घोषणा SPM_VEN2_PWR_CON		0x0298
#घोषणा SPM_AUDIO_PWR_CON		0x029c	/* MT8173, MT2712 */
#घोषणा SPM_BDP_PWR_CON			0x029c	/* MT2701 */
#घोषणा SPM_ETH_PWR_CON			0x02a0
#घोषणा SPM_HIF_PWR_CON			0x02a4
#घोषणा SPM_IFR_MSC_PWR_CON		0x02a8
#घोषणा SPM_MFG_2D_PWR_CON		0x02c0
#घोषणा SPM_MFG_ASYNC_PWR_CON		0x02c4
#घोषणा SPM_USB_PWR_CON			0x02cc
#घोषणा SPM_USB2_PWR_CON		0x02d4	/* MT2712 */
#घोषणा SPM_ETHSYS_PWR_CON		0x02e0	/* MT7622 */
#घोषणा SPM_HIF0_PWR_CON		0x02e4	/* MT7622 */
#घोषणा SPM_HIF1_PWR_CON		0x02e8	/* MT7622 */
#घोषणा SPM_WB_PWR_CON			0x02ec	/* MT7622 */

#घोषणा SPM_PWR_STATUS			0x060c
#घोषणा SPM_PWR_STATUS_2ND		0x0610

#घोषणा PWR_RST_B_BIT			BIT(0)
#घोषणा PWR_ISO_BIT			BIT(1)
#घोषणा PWR_ON_BIT			BIT(2)
#घोषणा PWR_ON_2ND_BIT			BIT(3)
#घोषणा PWR_CLK_DIS_BIT			BIT(4)

#घोषणा PWR_STATUS_CONN			BIT(1)
#घोषणा PWR_STATUS_DISP			BIT(3)
#घोषणा PWR_STATUS_MFG			BIT(4)
#घोषणा PWR_STATUS_ISP			BIT(5)
#घोषणा PWR_STATUS_VDEC			BIT(7)
#घोषणा PWR_STATUS_BDP			BIT(14)
#घोषणा PWR_STATUS_ETH			BIT(15)
#घोषणा PWR_STATUS_HIF			BIT(16)
#घोषणा PWR_STATUS_IFR_MSC		BIT(17)
#घोषणा PWR_STATUS_USB2			BIT(19)	/* MT2712 */
#घोषणा PWR_STATUS_VENC_LT		BIT(20)
#घोषणा PWR_STATUS_VENC			BIT(21)
#घोषणा PWR_STATUS_MFG_2D		BIT(22)	/* MT8173 */
#घोषणा PWR_STATUS_MFG_ASYNC		BIT(23)	/* MT8173 */
#घोषणा PWR_STATUS_AUDIO		BIT(24)	/* MT8173, MT2712 */
#घोषणा PWR_STATUS_USB			BIT(25)	/* MT8173, MT2712 */
#घोषणा PWR_STATUS_ETHSYS		BIT(24)	/* MT7622 */
#घोषणा PWR_STATUS_HIF0			BIT(25)	/* MT7622 */
#घोषणा PWR_STATUS_HIF1			BIT(26)	/* MT7622 */
#घोषणा PWR_STATUS_WB			BIT(27)	/* MT7622 */

क्रमागत clk_id अणु
	CLK_NONE,
	CLK_MM,
	CLK_MFG,
	CLK_VENC,
	CLK_VENC_LT,
	CLK_ETHIF,
	CLK_VDEC,
	CLK_HIFSEL,
	CLK_JPGDEC,
	CLK_AUDIO,
	CLK_MAX,
पूर्ण;

अटल स्थिर अक्षर * स्थिर clk_names[] = अणु
	शून्य,
	"mm",
	"mfg",
	"venc",
	"venc_lt",
	"ethif",
	"vdec",
	"hif_sel",
	"jpgdec",
	"audio",
	शून्य,
पूर्ण;

#घोषणा MAX_CLKS	3

/**
 * काष्ठा scp_करोमुख्य_data - scp करोमुख्य data क्रम घातer on/off flow
 * @name: The करोमुख्य name.
 * @sta_mask: The mask क्रम घातer on/off status bit.
 * @ctl_offs: The offset क्रम मुख्य घातer control रेजिस्टर.
 * @sram_pdn_bits: The mask क्रम sram घातer control bits.
 * @sram_pdn_ack_bits: The mask क्रम sram घातer control acked bits.
 * @bus_prot_mask: The mask क्रम single step bus protection.
 * @clk_id: The basic घड़ीs required by this घातer करोमुख्य.
 * @caps: The flag क्रम active wake-up action.
 */
काष्ठा scp_करोमुख्य_data अणु
	स्थिर अक्षर *name;
	u32 sta_mask;
	पूर्णांक ctl_offs;
	u32 sram_pdn_bits;
	u32 sram_pdn_ack_bits;
	u32 bus_prot_mask;
	क्रमागत clk_id clk_id[MAX_CLKS];
	u8 caps;
पूर्ण;

काष्ठा scp;

काष्ठा scp_करोमुख्य अणु
	काष्ठा generic_pm_करोमुख्य genpd;
	काष्ठा scp *scp;
	काष्ठा clk *clk[MAX_CLKS];
	स्थिर काष्ठा scp_करोमुख्य_data *data;
	काष्ठा regulator *supply;
पूर्ण;

काष्ठा scp_ctrl_reg अणु
	पूर्णांक pwr_sta_offs;
	पूर्णांक pwr_sta2nd_offs;
पूर्ण;

काष्ठा scp अणु
	काष्ठा scp_करोमुख्य *करोमुख्यs;
	काष्ठा genpd_onecell_data pd_data;
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा regmap *infracfg;
	काष्ठा scp_ctrl_reg ctrl_reg;
	bool bus_prot_reg_update;
पूर्ण;

काष्ठा scp_subकरोमुख्य अणु
	पूर्णांक origin;
	पूर्णांक subकरोमुख्य;
पूर्ण;

काष्ठा scp_soc_data अणु
	स्थिर काष्ठा scp_करोमुख्य_data *करोमुख्यs;
	पूर्णांक num_करोमुख्यs;
	स्थिर काष्ठा scp_subकरोमुख्य *subकरोमुख्यs;
	पूर्णांक num_subकरोमुख्यs;
	स्थिर काष्ठा scp_ctrl_reg regs;
	bool bus_prot_reg_update;
पूर्ण;

अटल पूर्णांक scpsys_करोमुख्य_is_on(काष्ठा scp_करोमुख्य *scpd)
अणु
	काष्ठा scp *scp = scpd->scp;

	u32 status = पढ़ोl(scp->base + scp->ctrl_reg.pwr_sta_offs) &
						scpd->data->sta_mask;
	u32 status2 = पढ़ोl(scp->base + scp->ctrl_reg.pwr_sta2nd_offs) &
						scpd->data->sta_mask;

	/*
	 * A करोमुख्य is on when both status bits are set. If only one is set
	 * वापस an error. This happens जबतक घातering up a करोमुख्य
	 */

	अगर (status && status2)
		वापस true;
	अगर (!status && !status2)
		वापस false;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक scpsys_regulator_enable(काष्ठा scp_करोमुख्य *scpd)
अणु
	अगर (!scpd->supply)
		वापस 0;

	वापस regulator_enable(scpd->supply);
पूर्ण

अटल पूर्णांक scpsys_regulator_disable(काष्ठा scp_करोमुख्य *scpd)
अणु
	अगर (!scpd->supply)
		वापस 0;

	वापस regulator_disable(scpd->supply);
पूर्ण

अटल व्योम scpsys_clk_disable(काष्ठा clk *clk[], पूर्णांक max_num)
अणु
	पूर्णांक i;

	क्रम (i = max_num - 1; i >= 0; i--)
		clk_disable_unprepare(clk[i]);
पूर्ण

अटल पूर्णांक scpsys_clk_enable(काष्ठा clk *clk[], पूर्णांक max_num)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < max_num && clk[i]; i++) अणु
		ret = clk_prepare_enable(clk[i]);
		अगर (ret) अणु
			scpsys_clk_disable(clk, i);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक scpsys_sram_enable(काष्ठा scp_करोमुख्य *scpd, व्योम __iomem *ctl_addr)
अणु
	u32 val;
	u32 pdn_ack = scpd->data->sram_pdn_ack_bits;
	पूर्णांक पंचांगp;

	val = पढ़ोl(ctl_addr);
	val &= ~scpd->data->sram_pdn_bits;
	ग_लिखोl(val, ctl_addr);

	/* Either रुको until SRAM_PDN_ACK all 0 or have a क्रमce रुको */
	अगर (MTK_SCPD_CAPS(scpd, MTK_SCPD_FWAIT_SRAM)) अणु
		/*
		 * Currently, MTK_SCPD_FWAIT_SRAM is necessary only क्रम
		 * MT7622_POWER_DOMAIN_WB and thus just a trivial setup
		 * is applied here.
		 */
		usleep_range(12000, 12100);
	पूर्ण अन्यथा अणु
		/* Either रुको until SRAM_PDN_ACK all 1 or 0 */
		पूर्णांक ret = पढ़ोl_poll_समयout(ctl_addr, पंचांगp,
				(पंचांगp & pdn_ack) == 0,
				MTK_POLL_DELAY_US, MTK_POLL_TIMEOUT);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक scpsys_sram_disable(काष्ठा scp_करोमुख्य *scpd, व्योम __iomem *ctl_addr)
अणु
	u32 val;
	u32 pdn_ack = scpd->data->sram_pdn_ack_bits;
	पूर्णांक पंचांगp;

	val = पढ़ोl(ctl_addr);
	val |= scpd->data->sram_pdn_bits;
	ग_लिखोl(val, ctl_addr);

	/* Either रुको until SRAM_PDN_ACK all 1 or 0 */
	वापस पढ़ोl_poll_समयout(ctl_addr, पंचांगp,
			(पंचांगp & pdn_ack) == pdn_ack,
			MTK_POLL_DELAY_US, MTK_POLL_TIMEOUT);
पूर्ण

अटल पूर्णांक scpsys_bus_protect_enable(काष्ठा scp_करोमुख्य *scpd)
अणु
	काष्ठा scp *scp = scpd->scp;

	अगर (!scpd->data->bus_prot_mask)
		वापस 0;

	वापस mtk_infracfg_set_bus_protection(scp->infracfg,
			scpd->data->bus_prot_mask,
			scp->bus_prot_reg_update);
पूर्ण

अटल पूर्णांक scpsys_bus_protect_disable(काष्ठा scp_करोमुख्य *scpd)
अणु
	काष्ठा scp *scp = scpd->scp;

	अगर (!scpd->data->bus_prot_mask)
		वापस 0;

	वापस mtk_infracfg_clear_bus_protection(scp->infracfg,
			scpd->data->bus_prot_mask,
			scp->bus_prot_reg_update);
पूर्ण

अटल पूर्णांक scpsys_घातer_on(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा scp_करोमुख्य *scpd = container_of(genpd, काष्ठा scp_करोमुख्य, genpd);
	काष्ठा scp *scp = scpd->scp;
	व्योम __iomem *ctl_addr = scp->base + scpd->data->ctl_offs;
	u32 val;
	पूर्णांक ret, पंचांगp;

	ret = scpsys_regulator_enable(scpd);
	अगर (ret < 0)
		वापस ret;

	ret = scpsys_clk_enable(scpd->clk, MAX_CLKS);
	अगर (ret)
		जाओ err_clk;

	/* subsys घातer on */
	val = पढ़ोl(ctl_addr);
	val |= PWR_ON_BIT;
	ग_लिखोl(val, ctl_addr);
	val |= PWR_ON_2ND_BIT;
	ग_लिखोl(val, ctl_addr);

	/* रुको until PWR_ACK = 1 */
	ret = पढ़ोx_poll_समयout(scpsys_करोमुख्य_is_on, scpd, पंचांगp, पंचांगp > 0,
				 MTK_POLL_DELAY_US, MTK_POLL_TIMEOUT);
	अगर (ret < 0)
		जाओ err_pwr_ack;

	val &= ~PWR_CLK_DIS_BIT;
	ग_लिखोl(val, ctl_addr);

	val &= ~PWR_ISO_BIT;
	ग_लिखोl(val, ctl_addr);

	val |= PWR_RST_B_BIT;
	ग_लिखोl(val, ctl_addr);

	ret = scpsys_sram_enable(scpd, ctl_addr);
	अगर (ret < 0)
		जाओ err_pwr_ack;

	ret = scpsys_bus_protect_disable(scpd);
	अगर (ret < 0)
		जाओ err_pwr_ack;

	वापस 0;

err_pwr_ack:
	scpsys_clk_disable(scpd->clk, MAX_CLKS);
err_clk:
	scpsys_regulator_disable(scpd);

	dev_err(scp->dev, "Failed to power on domain %s\n", genpd->name);

	वापस ret;
पूर्ण

अटल पूर्णांक scpsys_घातer_off(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा scp_करोमुख्य *scpd = container_of(genpd, काष्ठा scp_करोमुख्य, genpd);
	काष्ठा scp *scp = scpd->scp;
	व्योम __iomem *ctl_addr = scp->base + scpd->data->ctl_offs;
	u32 val;
	पूर्णांक ret, पंचांगp;

	ret = scpsys_bus_protect_enable(scpd);
	अगर (ret < 0)
		जाओ out;

	ret = scpsys_sram_disable(scpd, ctl_addr);
	अगर (ret < 0)
		जाओ out;

	/* subsys घातer off */
	val = पढ़ोl(ctl_addr);
	val |= PWR_ISO_BIT;
	ग_लिखोl(val, ctl_addr);

	val &= ~PWR_RST_B_BIT;
	ग_लिखोl(val, ctl_addr);

	val |= PWR_CLK_DIS_BIT;
	ग_लिखोl(val, ctl_addr);

	val &= ~PWR_ON_BIT;
	ग_लिखोl(val, ctl_addr);

	val &= ~PWR_ON_2ND_BIT;
	ग_लिखोl(val, ctl_addr);

	/* रुको until PWR_ACK = 0 */
	ret = पढ़ोx_poll_समयout(scpsys_करोमुख्य_is_on, scpd, पंचांगp, पंचांगp == 0,
				 MTK_POLL_DELAY_US, MTK_POLL_TIMEOUT);
	अगर (ret < 0)
		जाओ out;

	scpsys_clk_disable(scpd->clk, MAX_CLKS);

	ret = scpsys_regulator_disable(scpd);
	अगर (ret < 0)
		जाओ out;

	वापस 0;

out:
	dev_err(scp->dev, "Failed to power off domain %s\n", genpd->name);

	वापस ret;
पूर्ण

अटल व्योम init_clks(काष्ठा platक्रमm_device *pdev, काष्ठा clk **clk)
अणु
	पूर्णांक i;

	क्रम (i = CLK_NONE + 1; i < CLK_MAX; i++)
		clk[i] = devm_clk_get(&pdev->dev, clk_names[i]);
पूर्ण

अटल काष्ठा scp *init_scp(काष्ठा platक्रमm_device *pdev,
			स्थिर काष्ठा scp_करोमुख्य_data *scp_करोमुख्य_data, पूर्णांक num,
			स्थिर काष्ठा scp_ctrl_reg *scp_ctrl_reg,
			bool bus_prot_reg_update)
अणु
	काष्ठा genpd_onecell_data *pd_data;
	काष्ठा resource *res;
	पूर्णांक i, j;
	काष्ठा scp *scp;
	काष्ठा clk *clk[CLK_MAX];

	scp = devm_kzalloc(&pdev->dev, माप(*scp), GFP_KERNEL);
	अगर (!scp)
		वापस ERR_PTR(-ENOMEM);

	scp->ctrl_reg.pwr_sta_offs = scp_ctrl_reg->pwr_sta_offs;
	scp->ctrl_reg.pwr_sta2nd_offs = scp_ctrl_reg->pwr_sta2nd_offs;

	scp->bus_prot_reg_update = bus_prot_reg_update;

	scp->dev = &pdev->dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	scp->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(scp->base))
		वापस ERR_CAST(scp->base);

	scp->करोमुख्यs = devm_kसुस्मृति(&pdev->dev,
				num, माप(*scp->करोमुख्यs), GFP_KERNEL);
	अगर (!scp->करोमुख्यs)
		वापस ERR_PTR(-ENOMEM);

	pd_data = &scp->pd_data;

	pd_data->करोमुख्यs = devm_kसुस्मृति(&pdev->dev,
			num, माप(*pd_data->करोमुख्यs), GFP_KERNEL);
	अगर (!pd_data->करोमुख्यs)
		वापस ERR_PTR(-ENOMEM);

	scp->infracfg = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
			"infracfg");
	अगर (IS_ERR(scp->infracfg)) अणु
		dev_err(&pdev->dev, "Cannot find infracfg controller: %ld\n",
				PTR_ERR(scp->infracfg));
		वापस ERR_CAST(scp->infracfg);
	पूर्ण

	क्रम (i = 0; i < num; i++) अणु
		काष्ठा scp_करोमुख्य *scpd = &scp->करोमुख्यs[i];
		स्थिर काष्ठा scp_करोमुख्य_data *data = &scp_करोमुख्य_data[i];

		scpd->supply = devm_regulator_get_optional(&pdev->dev, data->name);
		अगर (IS_ERR(scpd->supply)) अणु
			अगर (PTR_ERR(scpd->supply) == -ENODEV)
				scpd->supply = शून्य;
			अन्यथा
				वापस ERR_CAST(scpd->supply);
		पूर्ण
	पूर्ण

	pd_data->num_करोमुख्यs = num;

	init_clks(pdev, clk);

	क्रम (i = 0; i < num; i++) अणु
		काष्ठा scp_करोमुख्य *scpd = &scp->करोमुख्यs[i];
		काष्ठा generic_pm_करोमुख्य *genpd = &scpd->genpd;
		स्थिर काष्ठा scp_करोमुख्य_data *data = &scp_करोमुख्य_data[i];

		pd_data->करोमुख्यs[i] = genpd;
		scpd->scp = scp;

		scpd->data = data;

		क्रम (j = 0; j < MAX_CLKS && data->clk_id[j]; j++) अणु
			काष्ठा clk *c = clk[data->clk_id[j]];

			अगर (IS_ERR(c)) अणु
				dev_err(&pdev->dev, "%s: clk unavailable\n",
					data->name);
				वापस ERR_CAST(c);
			पूर्ण

			scpd->clk[j] = c;
		पूर्ण

		genpd->name = data->name;
		genpd->घातer_off = scpsys_घातer_off;
		genpd->घातer_on = scpsys_घातer_on;
		अगर (MTK_SCPD_CAPS(scpd, MTK_SCPD_ACTIVE_WAKEUP))
			genpd->flags |= GENPD_FLAG_ACTIVE_WAKEUP;
	पूर्ण

	वापस scp;
पूर्ण

अटल व्योम mtk_रेजिस्टर_घातer_करोमुख्यs(काष्ठा platक्रमm_device *pdev,
				काष्ठा scp *scp, पूर्णांक num)
अणु
	काष्ठा genpd_onecell_data *pd_data;
	पूर्णांक i, ret;

	क्रम (i = 0; i < num; i++) अणु
		काष्ठा scp_करोमुख्य *scpd = &scp->करोमुख्यs[i];
		काष्ठा generic_pm_करोमुख्य *genpd = &scpd->genpd;
		bool on;

		/*
		 * Initially turn on all करोमुख्यs to make the करोमुख्यs usable
		 * with !CONFIG_PM and to get the hardware in sync with the
		 * software.  The unused करोमुख्यs will be चयनed off during
		 * late_init समय.
		 */
		on = !WARN_ON(genpd->घातer_on(genpd) < 0);

		pm_genpd_init(genpd, शून्य, !on);
	पूर्ण

	/*
	 * We are not allowed to fail here since there is no way to unरेजिस्टर
	 * a घातer करोमुख्य. Once रेजिस्टरed above we have to keep the करोमुख्यs
	 * valid.
	 */

	pd_data = &scp->pd_data;

	ret = of_genpd_add_provider_onecell(pdev->dev.of_node, pd_data);
	अगर (ret)
		dev_err(&pdev->dev, "Failed to add OF provider: %d\n", ret);
पूर्ण

/*
 * MT2701 घातer करोमुख्य support
 */

अटल स्थिर काष्ठा scp_करोमुख्य_data scp_करोमुख्य_data_mt2701[] = अणु
	[MT2701_POWER_DOMAIN_CONN] = अणु
		.name = "conn",
		.sta_mask = PWR_STATUS_CONN,
		.ctl_offs = SPM_CONN_PWR_CON,
		.bus_prot_mask = MT2701_TOP_AXI_PROT_EN_CONN_M |
				 MT2701_TOP_AXI_PROT_EN_CONN_S,
		.clk_id = अणुCLK_NONEपूर्ण,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT2701_POWER_DOMAIN_DISP] = अणु
		.name = "disp",
		.sta_mask = PWR_STATUS_DISP,
		.ctl_offs = SPM_DIS_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.clk_id = अणुCLK_MMपूर्ण,
		.bus_prot_mask = MT2701_TOP_AXI_PROT_EN_MM_M0,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT2701_POWER_DOMAIN_MFG] = अणु
		.name = "mfg",
		.sta_mask = PWR_STATUS_MFG,
		.ctl_offs = SPM_MFG_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(12, 12),
		.clk_id = अणुCLK_MFGपूर्ण,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT2701_POWER_DOMAIN_VDEC] = अणु
		.name = "vdec",
		.sta_mask = PWR_STATUS_VDEC,
		.ctl_offs = SPM_VDE_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(12, 12),
		.clk_id = अणुCLK_MMपूर्ण,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT2701_POWER_DOMAIN_ISP] = अणु
		.name = "isp",
		.sta_mask = PWR_STATUS_ISP,
		.ctl_offs = SPM_ISP_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(13, 12),
		.clk_id = अणुCLK_MMपूर्ण,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT2701_POWER_DOMAIN_BDP] = अणु
		.name = "bdp",
		.sta_mask = PWR_STATUS_BDP,
		.ctl_offs = SPM_BDP_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.clk_id = अणुCLK_NONEपूर्ण,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT2701_POWER_DOMAIN_ETH] = अणु
		.name = "eth",
		.sta_mask = PWR_STATUS_ETH,
		.ctl_offs = SPM_ETH_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(15, 12),
		.clk_id = अणुCLK_ETHIFपूर्ण,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT2701_POWER_DOMAIN_HIF] = अणु
		.name = "hif",
		.sta_mask = PWR_STATUS_HIF,
		.ctl_offs = SPM_HIF_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(15, 12),
		.clk_id = अणुCLK_ETHIFपूर्ण,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT2701_POWER_DOMAIN_IFR_MSC] = अणु
		.name = "ifr_msc",
		.sta_mask = PWR_STATUS_IFR_MSC,
		.ctl_offs = SPM_IFR_MSC_PWR_CON,
		.clk_id = अणुCLK_NONEपूर्ण,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
पूर्ण;

/*
 * MT2712 घातer करोमुख्य support
 */
अटल स्थिर काष्ठा scp_करोमुख्य_data scp_करोमुख्य_data_mt2712[] = अणु
	[MT2712_POWER_DOMAIN_MM] = अणु
		.name = "mm",
		.sta_mask = PWR_STATUS_DISP,
		.ctl_offs = SPM_DIS_PWR_CON,
		.sram_pdn_bits = GENMASK(8, 8),
		.sram_pdn_ack_bits = GENMASK(12, 12),
		.clk_id = अणुCLK_MMपूर्ण,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT2712_POWER_DOMAIN_VDEC] = अणु
		.name = "vdec",
		.sta_mask = PWR_STATUS_VDEC,
		.ctl_offs = SPM_VDE_PWR_CON,
		.sram_pdn_bits = GENMASK(8, 8),
		.sram_pdn_ack_bits = GENMASK(12, 12),
		.clk_id = अणुCLK_MM, CLK_VDECपूर्ण,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT2712_POWER_DOMAIN_VENC] = अणु
		.name = "venc",
		.sta_mask = PWR_STATUS_VENC,
		.ctl_offs = SPM_VEN_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(15, 12),
		.clk_id = अणुCLK_MM, CLK_VENC, CLK_JPGDECपूर्ण,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT2712_POWER_DOMAIN_ISP] = अणु
		.name = "isp",
		.sta_mask = PWR_STATUS_ISP,
		.ctl_offs = SPM_ISP_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(13, 12),
		.clk_id = अणुCLK_MMपूर्ण,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT2712_POWER_DOMAIN_AUDIO] = अणु
		.name = "audio",
		.sta_mask = PWR_STATUS_AUDIO,
		.ctl_offs = SPM_AUDIO_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(15, 12),
		.clk_id = अणुCLK_AUDIOपूर्ण,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT2712_POWER_DOMAIN_USB] = अणु
		.name = "usb",
		.sta_mask = PWR_STATUS_USB,
		.ctl_offs = SPM_USB_PWR_CON,
		.sram_pdn_bits = GENMASK(10, 8),
		.sram_pdn_ack_bits = GENMASK(14, 12),
		.clk_id = अणुCLK_NONEपूर्ण,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT2712_POWER_DOMAIN_USB2] = अणु
		.name = "usb2",
		.sta_mask = PWR_STATUS_USB2,
		.ctl_offs = SPM_USB2_PWR_CON,
		.sram_pdn_bits = GENMASK(10, 8),
		.sram_pdn_ack_bits = GENMASK(14, 12),
		.clk_id = अणुCLK_NONEपूर्ण,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT2712_POWER_DOMAIN_MFG] = अणु
		.name = "mfg",
		.sta_mask = PWR_STATUS_MFG,
		.ctl_offs = SPM_MFG_PWR_CON,
		.sram_pdn_bits = GENMASK(8, 8),
		.sram_pdn_ack_bits = GENMASK(16, 16),
		.clk_id = अणुCLK_MFGपूर्ण,
		.bus_prot_mask = BIT(14) | BIT(21) | BIT(23),
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT2712_POWER_DOMAIN_MFG_SC1] = अणु
		.name = "mfg_sc1",
		.sta_mask = BIT(22),
		.ctl_offs = 0x02c0,
		.sram_pdn_bits = GENMASK(8, 8),
		.sram_pdn_ack_bits = GENMASK(16, 16),
		.clk_id = अणुCLK_NONEपूर्ण,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT2712_POWER_DOMAIN_MFG_SC2] = अणु
		.name = "mfg_sc2",
		.sta_mask = BIT(23),
		.ctl_offs = 0x02c4,
		.sram_pdn_bits = GENMASK(8, 8),
		.sram_pdn_ack_bits = GENMASK(16, 16),
		.clk_id = अणुCLK_NONEपूर्ण,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT2712_POWER_DOMAIN_MFG_SC3] = अणु
		.name = "mfg_sc3",
		.sta_mask = BIT(30),
		.ctl_offs = 0x01f8,
		.sram_pdn_bits = GENMASK(8, 8),
		.sram_pdn_ack_bits = GENMASK(16, 16),
		.clk_id = अणुCLK_NONEपूर्ण,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा scp_subकरोमुख्य scp_subकरोमुख्य_mt2712[] = अणु
	अणुMT2712_POWER_DOMAIN_MM, MT2712_POWER_DOMAIN_VDECपूर्ण,
	अणुMT2712_POWER_DOMAIN_MM, MT2712_POWER_DOMAIN_VENCपूर्ण,
	अणुMT2712_POWER_DOMAIN_MM, MT2712_POWER_DOMAIN_ISPपूर्ण,
	अणुMT2712_POWER_DOMAIN_MFG, MT2712_POWER_DOMAIN_MFG_SC1पूर्ण,
	अणुMT2712_POWER_DOMAIN_MFG_SC1, MT2712_POWER_DOMAIN_MFG_SC2पूर्ण,
	अणुMT2712_POWER_DOMAIN_MFG_SC2, MT2712_POWER_DOMAIN_MFG_SC3पूर्ण,
पूर्ण;

/*
 * MT6797 घातer करोमुख्य support
 */

अटल स्थिर काष्ठा scp_करोमुख्य_data scp_करोमुख्य_data_mt6797[] = अणु
	[MT6797_POWER_DOMAIN_VDEC] = अणु
		.name = "vdec",
		.sta_mask = BIT(7),
		.ctl_offs = 0x300,
		.sram_pdn_bits = GENMASK(8, 8),
		.sram_pdn_ack_bits = GENMASK(12, 12),
		.clk_id = अणुCLK_VDECपूर्ण,
	पूर्ण,
	[MT6797_POWER_DOMAIN_VENC] = अणु
		.name = "venc",
		.sta_mask = BIT(21),
		.ctl_offs = 0x304,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(15, 12),
		.clk_id = अणुCLK_NONEपूर्ण,
	पूर्ण,
	[MT6797_POWER_DOMAIN_ISP] = अणु
		.name = "isp",
		.sta_mask = BIT(5),
		.ctl_offs = 0x308,
		.sram_pdn_bits = GENMASK(9, 8),
		.sram_pdn_ack_bits = GENMASK(13, 12),
		.clk_id = अणुCLK_NONEपूर्ण,
	पूर्ण,
	[MT6797_POWER_DOMAIN_MM] = अणु
		.name = "mm",
		.sta_mask = BIT(3),
		.ctl_offs = 0x30C,
		.sram_pdn_bits = GENMASK(8, 8),
		.sram_pdn_ack_bits = GENMASK(12, 12),
		.clk_id = अणुCLK_MMपूर्ण,
		.bus_prot_mask = (BIT(1) | BIT(2)),
	पूर्ण,
	[MT6797_POWER_DOMAIN_AUDIO] = अणु
		.name = "audio",
		.sta_mask = BIT(24),
		.ctl_offs = 0x314,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(15, 12),
		.clk_id = अणुCLK_NONEपूर्ण,
	पूर्ण,
	[MT6797_POWER_DOMAIN_MFG_ASYNC] = अणु
		.name = "mfg_async",
		.sta_mask = BIT(13),
		.ctl_offs = 0x334,
		.sram_pdn_bits = 0,
		.sram_pdn_ack_bits = 0,
		.clk_id = अणुCLK_MFGपूर्ण,
	पूर्ण,
	[MT6797_POWER_DOMAIN_MJC] = अणु
		.name = "mjc",
		.sta_mask = BIT(20),
		.ctl_offs = 0x310,
		.sram_pdn_bits = GENMASK(8, 8),
		.sram_pdn_ack_bits = GENMASK(12, 12),
		.clk_id = अणुCLK_NONEपूर्ण,
	पूर्ण,
पूर्ण;

#घोषणा SPM_PWR_STATUS_MT6797		0x0180
#घोषणा SPM_PWR_STATUS_2ND_MT6797	0x0184

अटल स्थिर काष्ठा scp_subकरोमुख्य scp_subकरोमुख्य_mt6797[] = अणु
	अणुMT6797_POWER_DOMAIN_MM, MT6797_POWER_DOMAIN_VDECपूर्ण,
	अणुMT6797_POWER_DOMAIN_MM, MT6797_POWER_DOMAIN_ISPपूर्ण,
	अणुMT6797_POWER_DOMAIN_MM, MT6797_POWER_DOMAIN_VENCपूर्ण,
	अणुMT6797_POWER_DOMAIN_MM, MT6797_POWER_DOMAIN_MJCपूर्ण,
पूर्ण;

/*
 * MT7622 घातer करोमुख्य support
 */

अटल स्थिर काष्ठा scp_करोमुख्य_data scp_करोमुख्य_data_mt7622[] = अणु
	[MT7622_POWER_DOMAIN_ETHSYS] = अणु
		.name = "ethsys",
		.sta_mask = PWR_STATUS_ETHSYS,
		.ctl_offs = SPM_ETHSYS_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(15, 12),
		.clk_id = अणुCLK_NONEपूर्ण,
		.bus_prot_mask = MT7622_TOP_AXI_PROT_EN_ETHSYS,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT7622_POWER_DOMAIN_HIF0] = अणु
		.name = "hif0",
		.sta_mask = PWR_STATUS_HIF0,
		.ctl_offs = SPM_HIF0_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(15, 12),
		.clk_id = अणुCLK_HIFSELपूर्ण,
		.bus_prot_mask = MT7622_TOP_AXI_PROT_EN_HIF0,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT7622_POWER_DOMAIN_HIF1] = अणु
		.name = "hif1",
		.sta_mask = PWR_STATUS_HIF1,
		.ctl_offs = SPM_HIF1_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(15, 12),
		.clk_id = अणुCLK_HIFSELपूर्ण,
		.bus_prot_mask = MT7622_TOP_AXI_PROT_EN_HIF1,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT7622_POWER_DOMAIN_WB] = अणु
		.name = "wb",
		.sta_mask = PWR_STATUS_WB,
		.ctl_offs = SPM_WB_PWR_CON,
		.sram_pdn_bits = 0,
		.sram_pdn_ack_bits = 0,
		.clk_id = अणुCLK_NONEपूर्ण,
		.bus_prot_mask = MT7622_TOP_AXI_PROT_EN_WB,
		.caps = MTK_SCPD_ACTIVE_WAKEUP | MTK_SCPD_FWAIT_SRAM,
	पूर्ण,
पूर्ण;

/*
 * MT7623A घातer करोमुख्य support
 */

अटल स्थिर काष्ठा scp_करोमुख्य_data scp_करोमुख्य_data_mt7623a[] = अणु
	[MT7623A_POWER_DOMAIN_CONN] = अणु
		.name = "conn",
		.sta_mask = PWR_STATUS_CONN,
		.ctl_offs = SPM_CONN_PWR_CON,
		.bus_prot_mask = MT2701_TOP_AXI_PROT_EN_CONN_M |
				 MT2701_TOP_AXI_PROT_EN_CONN_S,
		.clk_id = अणुCLK_NONEपूर्ण,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT7623A_POWER_DOMAIN_ETH] = अणु
		.name = "eth",
		.sta_mask = PWR_STATUS_ETH,
		.ctl_offs = SPM_ETH_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(15, 12),
		.clk_id = अणुCLK_ETHIFपूर्ण,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT7623A_POWER_DOMAIN_HIF] = अणु
		.name = "hif",
		.sta_mask = PWR_STATUS_HIF,
		.ctl_offs = SPM_HIF_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(15, 12),
		.clk_id = अणुCLK_ETHIFपूर्ण,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT7623A_POWER_DOMAIN_IFR_MSC] = अणु
		.name = "ifr_msc",
		.sta_mask = PWR_STATUS_IFR_MSC,
		.ctl_offs = SPM_IFR_MSC_PWR_CON,
		.clk_id = अणुCLK_NONEपूर्ण,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
पूर्ण;

/*
 * MT8173 घातer करोमुख्य support
 */

अटल स्थिर काष्ठा scp_करोमुख्य_data scp_करोमुख्य_data_mt8173[] = अणु
	[MT8173_POWER_DOMAIN_VDEC] = अणु
		.name = "vdec",
		.sta_mask = PWR_STATUS_VDEC,
		.ctl_offs = SPM_VDE_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(12, 12),
		.clk_id = अणुCLK_MMपूर्ण,
	पूर्ण,
	[MT8173_POWER_DOMAIN_VENC] = अणु
		.name = "venc",
		.sta_mask = PWR_STATUS_VENC,
		.ctl_offs = SPM_VEN_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(15, 12),
		.clk_id = अणुCLK_MM, CLK_VENCपूर्ण,
	पूर्ण,
	[MT8173_POWER_DOMAIN_ISP] = अणु
		.name = "isp",
		.sta_mask = PWR_STATUS_ISP,
		.ctl_offs = SPM_ISP_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(13, 12),
		.clk_id = अणुCLK_MMपूर्ण,
	पूर्ण,
	[MT8173_POWER_DOMAIN_MM] = अणु
		.name = "mm",
		.sta_mask = PWR_STATUS_DISP,
		.ctl_offs = SPM_DIS_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(12, 12),
		.clk_id = अणुCLK_MMपूर्ण,
		.bus_prot_mask = MT8173_TOP_AXI_PROT_EN_MM_M0 |
			MT8173_TOP_AXI_PROT_EN_MM_M1,
	पूर्ण,
	[MT8173_POWER_DOMAIN_VENC_LT] = अणु
		.name = "venc_lt",
		.sta_mask = PWR_STATUS_VENC_LT,
		.ctl_offs = SPM_VEN2_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(15, 12),
		.clk_id = अणुCLK_MM, CLK_VENC_LTपूर्ण,
	पूर्ण,
	[MT8173_POWER_DOMAIN_AUDIO] = अणु
		.name = "audio",
		.sta_mask = PWR_STATUS_AUDIO,
		.ctl_offs = SPM_AUDIO_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(15, 12),
		.clk_id = अणुCLK_NONEपूर्ण,
	पूर्ण,
	[MT8173_POWER_DOMAIN_USB] = अणु
		.name = "usb",
		.sta_mask = PWR_STATUS_USB,
		.ctl_offs = SPM_USB_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(15, 12),
		.clk_id = अणुCLK_NONEपूर्ण,
		.caps = MTK_SCPD_ACTIVE_WAKEUP,
	पूर्ण,
	[MT8173_POWER_DOMAIN_MFG_ASYNC] = अणु
		.name = "mfg_async",
		.sta_mask = PWR_STATUS_MFG_ASYNC,
		.ctl_offs = SPM_MFG_ASYNC_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = 0,
		.clk_id = अणुCLK_MFGपूर्ण,
	पूर्ण,
	[MT8173_POWER_DOMAIN_MFG_2D] = अणु
		.name = "mfg_2d",
		.sta_mask = PWR_STATUS_MFG_2D,
		.ctl_offs = SPM_MFG_2D_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(13, 12),
		.clk_id = अणुCLK_NONEपूर्ण,
	पूर्ण,
	[MT8173_POWER_DOMAIN_MFG] = अणु
		.name = "mfg",
		.sta_mask = PWR_STATUS_MFG,
		.ctl_offs = SPM_MFG_PWR_CON,
		.sram_pdn_bits = GENMASK(13, 8),
		.sram_pdn_ack_bits = GENMASK(21, 16),
		.clk_id = अणुCLK_NONEपूर्ण,
		.bus_prot_mask = MT8173_TOP_AXI_PROT_EN_MFG_S |
			MT8173_TOP_AXI_PROT_EN_MFG_M0 |
			MT8173_TOP_AXI_PROT_EN_MFG_M1 |
			MT8173_TOP_AXI_PROT_EN_MFG_SNOOP_OUT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा scp_subकरोमुख्य scp_subकरोमुख्य_mt8173[] = अणु
	अणुMT8173_POWER_DOMAIN_MFG_ASYNC, MT8173_POWER_DOMAIN_MFG_2Dपूर्ण,
	अणुMT8173_POWER_DOMAIN_MFG_2D, MT8173_POWER_DOMAIN_MFGपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा scp_soc_data mt2701_data = अणु
	.करोमुख्यs = scp_करोमुख्य_data_mt2701,
	.num_करोमुख्यs = ARRAY_SIZE(scp_करोमुख्य_data_mt2701),
	.regs = अणु
		.pwr_sta_offs = SPM_PWR_STATUS,
		.pwr_sta2nd_offs = SPM_PWR_STATUS_2ND
	पूर्ण,
	.bus_prot_reg_update = true,
पूर्ण;

अटल स्थिर काष्ठा scp_soc_data mt2712_data = अणु
	.करोमुख्यs = scp_करोमुख्य_data_mt2712,
	.num_करोमुख्यs = ARRAY_SIZE(scp_करोमुख्य_data_mt2712),
	.subकरोमुख्यs = scp_subकरोमुख्य_mt2712,
	.num_subकरोमुख्यs = ARRAY_SIZE(scp_subकरोमुख्य_mt2712),
	.regs = अणु
		.pwr_sta_offs = SPM_PWR_STATUS,
		.pwr_sta2nd_offs = SPM_PWR_STATUS_2ND
	पूर्ण,
	.bus_prot_reg_update = false,
पूर्ण;

अटल स्थिर काष्ठा scp_soc_data mt6797_data = अणु
	.करोमुख्यs = scp_करोमुख्य_data_mt6797,
	.num_करोमुख्यs = ARRAY_SIZE(scp_करोमुख्य_data_mt6797),
	.subकरोमुख्यs = scp_subकरोमुख्य_mt6797,
	.num_subकरोमुख्यs = ARRAY_SIZE(scp_subकरोमुख्य_mt6797),
	.regs = अणु
		.pwr_sta_offs = SPM_PWR_STATUS_MT6797,
		.pwr_sta2nd_offs = SPM_PWR_STATUS_2ND_MT6797
	पूर्ण,
	.bus_prot_reg_update = true,
पूर्ण;

अटल स्थिर काष्ठा scp_soc_data mt7622_data = अणु
	.करोमुख्यs = scp_करोमुख्य_data_mt7622,
	.num_करोमुख्यs = ARRAY_SIZE(scp_करोमुख्य_data_mt7622),
	.regs = अणु
		.pwr_sta_offs = SPM_PWR_STATUS,
		.pwr_sta2nd_offs = SPM_PWR_STATUS_2ND
	पूर्ण,
	.bus_prot_reg_update = true,
पूर्ण;

अटल स्थिर काष्ठा scp_soc_data mt7623a_data = अणु
	.करोमुख्यs = scp_करोमुख्य_data_mt7623a,
	.num_करोमुख्यs = ARRAY_SIZE(scp_करोमुख्य_data_mt7623a),
	.regs = अणु
		.pwr_sta_offs = SPM_PWR_STATUS,
		.pwr_sta2nd_offs = SPM_PWR_STATUS_2ND
	पूर्ण,
	.bus_prot_reg_update = true,
पूर्ण;

अटल स्थिर काष्ठा scp_soc_data mt8173_data = अणु
	.करोमुख्यs = scp_करोमुख्य_data_mt8173,
	.num_करोमुख्यs = ARRAY_SIZE(scp_करोमुख्य_data_mt8173),
	.subकरोमुख्यs = scp_subकरोमुख्य_mt8173,
	.num_subकरोमुख्यs = ARRAY_SIZE(scp_subकरोमुख्य_mt8173),
	.regs = अणु
		.pwr_sta_offs = SPM_PWR_STATUS,
		.pwr_sta2nd_offs = SPM_PWR_STATUS_2ND
	पूर्ण,
	.bus_prot_reg_update = true,
पूर्ण;

/*
 * scpsys driver init
 */

अटल स्थिर काष्ठा of_device_id of_scpsys_match_tbl[] = अणु
	अणु
		.compatible = "mediatek,mt2701-scpsys",
		.data = &mt2701_data,
	पूर्ण, अणु
		.compatible = "mediatek,mt2712-scpsys",
		.data = &mt2712_data,
	पूर्ण, अणु
		.compatible = "mediatek,mt6797-scpsys",
		.data = &mt6797_data,
	पूर्ण, अणु
		.compatible = "mediatek,mt7622-scpsys",
		.data = &mt7622_data,
	पूर्ण, अणु
		.compatible = "mediatek,mt7623a-scpsys",
		.data = &mt7623a_data,
	पूर्ण, अणु
		.compatible = "mediatek,mt8173-scpsys",
		.data = &mt8173_data,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;

अटल पूर्णांक scpsys_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा scp_subकरोमुख्य *sd;
	स्थिर काष्ठा scp_soc_data *soc;
	काष्ठा scp *scp;
	काष्ठा genpd_onecell_data *pd_data;
	पूर्णांक i, ret;

	soc = of_device_get_match_data(&pdev->dev);

	scp = init_scp(pdev, soc->करोमुख्यs, soc->num_करोमुख्यs, &soc->regs,
			soc->bus_prot_reg_update);
	अगर (IS_ERR(scp))
		वापस PTR_ERR(scp);

	mtk_रेजिस्टर_घातer_करोमुख्यs(pdev, scp, soc->num_करोमुख्यs);

	pd_data = &scp->pd_data;

	क्रम (i = 0, sd = soc->subकरोमुख्यs; i < soc->num_subकरोमुख्यs; i++, sd++) अणु
		ret = pm_genpd_add_subकरोमुख्य(pd_data->करोमुख्यs[sd->origin],
					     pd_data->करोमुख्यs[sd->subकरोमुख्य]);
		अगर (ret && IS_ENABLED(CONFIG_PM))
			dev_err(&pdev->dev, "Failed to add subdomain: %d\n",
				ret);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver scpsys_drv = अणु
	.probe = scpsys_probe,
	.driver = अणु
		.name = "mtk-scpsys",
		.suppress_bind_attrs = true,
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(of_scpsys_match_tbl),
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(scpsys_drv);
