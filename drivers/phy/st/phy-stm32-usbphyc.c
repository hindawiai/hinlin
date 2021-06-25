<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * STMicroelectronics STM32 USB PHY Controller driver
 *
 * Copyright (C) 2018 STMicroelectronics
 * Author(s): Amelie Delaunay <amelie.delaunay@st.com>.
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/reset.h>

#घोषणा STM32_USBPHYC_PLL	0x0
#घोषणा STM32_USBPHYC_MISC	0x8
#घोषणा STM32_USBPHYC_MONITOR(X) (0x108 + ((X) * 0x100))
#घोषणा STM32_USBPHYC_VERSION	0x3F4

/* STM32_USBPHYC_PLL bit fields */
#घोषणा PLLNDIV			GENMASK(6, 0)
#घोषणा PLLFRACIN		GENMASK(25, 10)
#घोषणा PLLEN			BIT(26)
#घोषणा PLLSTRB			BIT(27)
#घोषणा PLLSTRBYP		BIT(28)
#घोषणा PLLFRACCTL		BIT(29)
#घोषणा PLLDITHEN0		BIT(30)
#घोषणा PLLDITHEN1		BIT(31)

/* STM32_USBPHYC_MISC bit fields */
#घोषणा SWITHOST		BIT(0)

/* STM32_USBPHYC_MONITOR bit fields */
#घोषणा STM32_USBPHYC_MON_OUT	GENMASK(3, 0)
#घोषणा STM32_USBPHYC_MON_SEL	GENMASK(8, 4)
#घोषणा STM32_USBPHYC_MON_SEL_LOCKP 0x1F
#घोषणा STM32_USBPHYC_MON_OUT_LOCKP BIT(3)

/* STM32_USBPHYC_VERSION bit fields */
#घोषणा MINREV			GENMASK(3, 0)
#घोषणा MAJREV			GENMASK(7, 4)

#घोषणा PLL_FVCO_MHZ		2880
#घोषणा PLL_INFF_MIN_RATE_HZ	19200000
#घोषणा PLL_INFF_MAX_RATE_HZ	38400000
#घोषणा HZ_PER_MHZ		1000000L

काष्ठा pll_params अणु
	u8 nभाग;
	u16 frac;
पूर्ण;

काष्ठा sपंचांग32_usbphyc_phy अणु
	काष्ठा phy *phy;
	काष्ठा sपंचांग32_usbphyc *usbphyc;
	u32 index;
	bool active;
पूर्ण;

काष्ठा sपंचांग32_usbphyc अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	काष्ठा reset_control *rst;
	काष्ठा sपंचांग32_usbphyc_phy **phys;
	पूर्णांक nphys;
	काष्ठा regulator *vdda1v1;
	काष्ठा regulator *vdda1v8;
	atomic_t n_pll_cons;
	काष्ठा clk_hw clk48_hw;
	पूर्णांक चयन_setup;
पूर्ण;

अटल अंतरभूत व्योम sपंचांग32_usbphyc_set_bits(व्योम __iomem *reg, u32 bits)
अणु
	ग_लिखोl_relaxed(पढ़ोl_relaxed(reg) | bits, reg);
पूर्ण

अटल अंतरभूत व्योम sपंचांग32_usbphyc_clr_bits(व्योम __iomem *reg, u32 bits)
अणु
	ग_लिखोl_relaxed(पढ़ोl_relaxed(reg) & ~bits, reg);
पूर्ण

अटल पूर्णांक sपंचांग32_usbphyc_regulators_enable(काष्ठा sपंचांग32_usbphyc *usbphyc)
अणु
	पूर्णांक ret;

	ret = regulator_enable(usbphyc->vdda1v1);
	अगर (ret)
		वापस ret;

	ret = regulator_enable(usbphyc->vdda1v8);
	अगर (ret)
		जाओ vdda1v1_disable;

	वापस 0;

vdda1v1_disable:
	regulator_disable(usbphyc->vdda1v1);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_usbphyc_regulators_disable(काष्ठा sपंचांग32_usbphyc *usbphyc)
अणु
	पूर्णांक ret;

	ret = regulator_disable(usbphyc->vdda1v8);
	अगर (ret)
		वापस ret;

	ret = regulator_disable(usbphyc->vdda1v1);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_usbphyc_get_pll_params(u32 clk_rate,
					 काष्ठा pll_params *pll_params)
अणु
	अचिन्हित दीर्घ दीर्घ fvco, nभाग, frac;

	/*    _
	 *   | FVCO = INFF*2*(NDIV + FRACT/2^16) when DITHER_DISABLE[1] = 1
	 *   | FVCO = 2880MHz
	 *  <
	 *   | NDIV = पूर्णांकeger part of input bits to set the LDF
	 *   |_FRACT = fractional part of input bits to set the LDF
	 *  =>	PLLNDIV = पूर्णांकeger part of (FVCO / (INFF*2))
	 *  =>	PLLFRACIN = fractional part of(FVCO / INFF*2) * 2^16
	 * <=>  PLLFRACIN = ((FVCO / (INFF*2)) - PLLNDIV) * 2^16
	 */
	fvco = (अचिन्हित दीर्घ दीर्घ)PLL_FVCO_MHZ * HZ_PER_MHZ;

	nभाग = fvco;
	करो_भाग(nभाग, (clk_rate * 2));
	pll_params->nभाग = (u8)nभाग;

	frac = fvco * (1 << 16);
	करो_भाग(frac, (clk_rate * 2));
	frac = frac - (nभाग * (1 << 16));
	pll_params->frac = (u16)frac;
पूर्ण

अटल पूर्णांक sपंचांग32_usbphyc_pll_init(काष्ठा sपंचांग32_usbphyc *usbphyc)
अणु
	काष्ठा pll_params pll_params;
	u32 clk_rate = clk_get_rate(usbphyc->clk);
	u32 nभाग, frac;
	u32 usbphyc_pll;

	अगर ((clk_rate < PLL_INFF_MIN_RATE_HZ) ||
	    (clk_rate > PLL_INFF_MAX_RATE_HZ)) अणु
		dev_err(usbphyc->dev, "input clk freq (%dHz) out of range\n",
			clk_rate);
		वापस -EINVAL;
	पूर्ण

	sपंचांग32_usbphyc_get_pll_params(clk_rate, &pll_params);
	nभाग = FIELD_PREP(PLLNDIV, pll_params.nभाग);
	frac = FIELD_PREP(PLLFRACIN, pll_params.frac);

	usbphyc_pll = PLLDITHEN1 | PLLDITHEN0 | PLLSTRBYP | nभाग;

	अगर (pll_params.frac)
		usbphyc_pll |= PLLFRACCTL | frac;

	ग_लिखोl_relaxed(usbphyc_pll, usbphyc->base + STM32_USBPHYC_PLL);

	dev_dbg(usbphyc->dev, "input clk freq=%dHz, ndiv=%lu, frac=%lu\n",
		clk_rate, FIELD_GET(PLLNDIV, usbphyc_pll),
		FIELD_GET(PLLFRACIN, usbphyc_pll));

	वापस 0;
पूर्ण

अटल पूर्णांक __sपंचांग32_usbphyc_pll_disable(काष्ठा sपंचांग32_usbphyc *usbphyc)
अणु
	व्योम __iomem *pll_reg = usbphyc->base + STM32_USBPHYC_PLL;
	u32 pllen;

	sपंचांग32_usbphyc_clr_bits(pll_reg, PLLEN);

	/* Wait क्रम minimum width of घातerकरोwn pulse (ENABLE = Low) */
	अगर (पढ़ोl_relaxed_poll_समयout(pll_reg, pllen, !(pllen & PLLEN), 5, 50))
		dev_err(usbphyc->dev, "PLL not reset\n");

	वापस sपंचांग32_usbphyc_regulators_disable(usbphyc);
पूर्ण

अटल पूर्णांक sपंचांग32_usbphyc_pll_disable(काष्ठा sपंचांग32_usbphyc *usbphyc)
अणु
	/* Check अगर a phy port is still active or clk48 in use */
	अगर (atomic_dec_वापस(&usbphyc->n_pll_cons) > 0)
		वापस 0;

	वापस __sपंचांग32_usbphyc_pll_disable(usbphyc);
पूर्ण

अटल पूर्णांक sपंचांग32_usbphyc_pll_enable(काष्ठा sपंचांग32_usbphyc *usbphyc)
अणु
	व्योम __iomem *pll_reg = usbphyc->base + STM32_USBPHYC_PLL;
	bool pllen = पढ़ोl_relaxed(pll_reg) & PLLEN;
	पूर्णांक ret;

	/*
	 * Check अगर a phy port or clk48 prepare has configured the pll
	 * and ensure the PLL is enabled
	 */
	अगर (atomic_inc_वापस(&usbphyc->n_pll_cons) > 1 && pllen)
		वापस 0;

	अगर (pllen) अणु
		/*
		 * PLL shouldn't be enabled without known consumer,
		 * disable it and reinit n_pll_cons
		 */
		dev_warn(usbphyc->dev, "PLL enabled without known consumers\n");

		ret = __sपंचांग32_usbphyc_pll_disable(usbphyc);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = sपंचांग32_usbphyc_regulators_enable(usbphyc);
	अगर (ret)
		जाओ dec_n_pll_cons;

	ret = sपंचांग32_usbphyc_pll_init(usbphyc);
	अगर (ret)
		जाओ reg_disable;

	sपंचांग32_usbphyc_set_bits(pll_reg, PLLEN);

	वापस 0;

reg_disable:
	sपंचांग32_usbphyc_regulators_disable(usbphyc);

dec_n_pll_cons:
	atomic_dec(&usbphyc->n_pll_cons);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_usbphyc_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा sपंचांग32_usbphyc_phy *usbphyc_phy = phy_get_drvdata(phy);
	काष्ठा sपंचांग32_usbphyc *usbphyc = usbphyc_phy->usbphyc;
	u32 reg_mon = STM32_USBPHYC_MONITOR(usbphyc_phy->index);
	u32 monsel = FIELD_PREP(STM32_USBPHYC_MON_SEL,
				STM32_USBPHYC_MON_SEL_LOCKP);
	u32 monout;
	पूर्णांक ret;

	ret = sपंचांग32_usbphyc_pll_enable(usbphyc);
	अगर (ret)
		वापस ret;

	/* Check that PLL Lock input to PHY is High */
	ग_लिखोl_relaxed(monsel, usbphyc->base + reg_mon);
	ret = पढ़ोl_relaxed_poll_समयout(usbphyc->base + reg_mon, monout,
					 (monout & STM32_USBPHYC_MON_OUT_LOCKP),
					 100, 1000);
	अगर (ret) अणु
		dev_err(usbphyc->dev, "PLL Lock input to PHY is Low (val=%x)\n",
			(u32)(monout & STM32_USBPHYC_MON_OUT));
		जाओ pll_disable;
	पूर्ण

	usbphyc_phy->active = true;

	वापस 0;

pll_disable:
	वापस sपंचांग32_usbphyc_pll_disable(usbphyc);
पूर्ण

अटल पूर्णांक sपंचांग32_usbphyc_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा sपंचांग32_usbphyc_phy *usbphyc_phy = phy_get_drvdata(phy);
	काष्ठा sपंचांग32_usbphyc *usbphyc = usbphyc_phy->usbphyc;

	usbphyc_phy->active = false;

	वापस sपंचांग32_usbphyc_pll_disable(usbphyc);
पूर्ण

अटल स्थिर काष्ठा phy_ops sपंचांग32_usbphyc_phy_ops = अणु
	.init = sपंचांग32_usbphyc_phy_init,
	.निकास = sपंचांग32_usbphyc_phy_निकास,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक sपंचांग32_usbphyc_clk48_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा sपंचांग32_usbphyc *usbphyc = container_of(hw, काष्ठा sपंचांग32_usbphyc, clk48_hw);

	वापस sपंचांग32_usbphyc_pll_enable(usbphyc);
पूर्ण

अटल व्योम sपंचांग32_usbphyc_clk48_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा sपंचांग32_usbphyc *usbphyc = container_of(hw, काष्ठा sपंचांग32_usbphyc, clk48_hw);

	sपंचांग32_usbphyc_pll_disable(usbphyc);
पूर्ण

अटल अचिन्हित दीर्घ sपंचांग32_usbphyc_clk48_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	वापस 48000000;
पूर्ण

अटल स्थिर काष्ठा clk_ops usbphyc_clk48_ops = अणु
	.prepare = sपंचांग32_usbphyc_clk48_prepare,
	.unprepare = sपंचांग32_usbphyc_clk48_unprepare,
	.recalc_rate = sपंचांग32_usbphyc_clk48_recalc_rate,
पूर्ण;

अटल व्योम sपंचांग32_usbphyc_clk48_unरेजिस्टर(व्योम *data)
अणु
	काष्ठा sपंचांग32_usbphyc *usbphyc = data;

	of_clk_del_provider(usbphyc->dev->of_node);
	clk_hw_unरेजिस्टर(&usbphyc->clk48_hw);
पूर्ण

अटल पूर्णांक sपंचांग32_usbphyc_clk48_रेजिस्टर(काष्ठा sपंचांग32_usbphyc *usbphyc)
अणु
	काष्ठा device_node *node = usbphyc->dev->of_node;
	काष्ठा clk_init_data init = अणु पूर्ण;
	पूर्णांक ret = 0;

	init.name = "ck_usbo_48m";
	init.ops = &usbphyc_clk48_ops;

	usbphyc->clk48_hw.init = &init;

	ret = clk_hw_रेजिस्टर(usbphyc->dev, &usbphyc->clk48_hw);
	अगर (ret)
		वापस ret;

	ret = of_clk_add_hw_provider(node, of_clk_hw_simple_get, &usbphyc->clk48_hw);
	अगर (ret)
		clk_hw_unरेजिस्टर(&usbphyc->clk48_hw);

	वापस ret;
पूर्ण

अटल व्योम sपंचांग32_usbphyc_चयन_setup(काष्ठा sपंचांग32_usbphyc *usbphyc,
				       u32 uपंचांगi_चयन)
अणु
	अगर (!uपंचांगi_चयन)
		sपंचांग32_usbphyc_clr_bits(usbphyc->base + STM32_USBPHYC_MISC,
				       SWITHOST);
	अन्यथा
		sपंचांग32_usbphyc_set_bits(usbphyc->base + STM32_USBPHYC_MISC,
				       SWITHOST);
	usbphyc->चयन_setup = uपंचांगi_चयन;
पूर्ण

अटल काष्ठा phy *sपंचांग32_usbphyc_of_xlate(काष्ठा device *dev,
					  काष्ठा of_phandle_args *args)
अणु
	काष्ठा sपंचांग32_usbphyc *usbphyc = dev_get_drvdata(dev);
	काष्ठा sपंचांग32_usbphyc_phy *usbphyc_phy = शून्य;
	काष्ठा device_node *phynode = args->np;
	पूर्णांक port = 0;

	क्रम (port = 0; port < usbphyc->nphys; port++) अणु
		अगर (phynode == usbphyc->phys[port]->phy->dev.of_node) अणु
			usbphyc_phy = usbphyc->phys[port];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!usbphyc_phy) अणु
		dev_err(dev, "failed to find phy\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (((usbphyc_phy->index == 0) && (args->args_count != 0)) ||
	    ((usbphyc_phy->index == 1) && (args->args_count != 1))) अणु
		dev_err(dev, "invalid number of cells for phy port%d\n",
			usbphyc_phy->index);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* Configure the UTMI चयन क्रम PHY port#2 */
	अगर (usbphyc_phy->index == 1) अणु
		अगर (usbphyc->चयन_setup < 0) अणु
			sपंचांग32_usbphyc_चयन_setup(usbphyc, args->args[0]);
		पूर्ण अन्यथा अणु
			अगर (args->args[0] != usbphyc->चयन_setup) अणु
				dev_err(dev, "phy port1 already used\n");
				वापस ERR_PTR(-EBUSY);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस usbphyc_phy->phy;
पूर्ण

अटल पूर्णांक sपंचांग32_usbphyc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_usbphyc *usbphyc;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *child, *np = dev->of_node;
	काष्ठा phy_provider *phy_provider;
	u32 pllen, version;
	पूर्णांक ret, port = 0;

	usbphyc = devm_kzalloc(dev, माप(*usbphyc), GFP_KERNEL);
	अगर (!usbphyc)
		वापस -ENOMEM;
	usbphyc->dev = dev;
	dev_set_drvdata(dev, usbphyc);

	usbphyc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(usbphyc->base))
		वापस PTR_ERR(usbphyc->base);

	usbphyc->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(usbphyc->clk))
		वापस dev_err_probe(dev, PTR_ERR(usbphyc->clk), "clk get_failed\n");

	ret = clk_prepare_enable(usbphyc->clk);
	अगर (ret) अणु
		dev_err(dev, "clk enable failed: %d\n", ret);
		वापस ret;
	पूर्ण

	usbphyc->rst = devm_reset_control_get(dev, शून्य);
	अगर (!IS_ERR(usbphyc->rst)) अणु
		reset_control_निश्चित(usbphyc->rst);
		udelay(2);
		reset_control_deनिश्चित(usbphyc->rst);
	पूर्ण अन्यथा अणु
		ret = PTR_ERR(usbphyc->rst);
		अगर (ret == -EPROBE_DEFER)
			जाओ clk_disable;

		sपंचांग32_usbphyc_clr_bits(usbphyc->base + STM32_USBPHYC_PLL, PLLEN);
	पूर्ण

	/*
	 * Wait क्रम minimum width of घातerकरोwn pulse (ENABLE = Low):
	 * we have to ensure the PLL is disabled beक्रमe phys initialization.
	 */
	अगर (पढ़ोl_relaxed_poll_समयout(usbphyc->base + STM32_USBPHYC_PLL,
				       pllen, !(pllen & PLLEN), 5, 50)) अणु
		dev_warn(usbphyc->dev, "PLL not reset\n");
		ret = -EPROBE_DEFER;
		जाओ clk_disable;
	पूर्ण

	usbphyc->चयन_setup = -EINVAL;
	usbphyc->nphys = of_get_child_count(np);
	usbphyc->phys = devm_kसुस्मृति(dev, usbphyc->nphys,
				     माप(*usbphyc->phys), GFP_KERNEL);
	अगर (!usbphyc->phys) अणु
		ret = -ENOMEM;
		जाओ clk_disable;
	पूर्ण

	usbphyc->vdda1v1 = devm_regulator_get(dev, "vdda1v1");
	अगर (IS_ERR(usbphyc->vdda1v1)) अणु
		ret = PTR_ERR(usbphyc->vdda1v1);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get vdda1v1 supply: %d\n", ret);
		जाओ clk_disable;
	पूर्ण

	usbphyc->vdda1v8 = devm_regulator_get(dev, "vdda1v8");
	अगर (IS_ERR(usbphyc->vdda1v8)) अणु
		ret = PTR_ERR(usbphyc->vdda1v8);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get vdda1v8 supply: %d\n", ret);
		जाओ clk_disable;
	पूर्ण

	क्रम_each_child_of_node(np, child) अणु
		काष्ठा sपंचांग32_usbphyc_phy *usbphyc_phy;
		काष्ठा phy *phy;
		u32 index;

		phy = devm_phy_create(dev, child, &sपंचांग32_usbphyc_phy_ops);
		अगर (IS_ERR(phy)) अणु
			ret = PTR_ERR(phy);
			अगर (ret != -EPROBE_DEFER)
				dev_err(dev, "failed to create phy%d: %d\n",
					port, ret);
			जाओ put_child;
		पूर्ण

		usbphyc_phy = devm_kzalloc(dev, माप(*usbphyc_phy),
					   GFP_KERNEL);
		अगर (!usbphyc_phy) अणु
			ret = -ENOMEM;
			जाओ put_child;
		पूर्ण

		ret = of_property_पढ़ो_u32(child, "reg", &index);
		अगर (ret || index > usbphyc->nphys) अणु
			dev_err(&phy->dev, "invalid reg property: %d\n", ret);
			जाओ put_child;
		पूर्ण

		usbphyc->phys[port] = usbphyc_phy;
		phy_set_bus_width(phy, 8);
		phy_set_drvdata(phy, usbphyc_phy);

		usbphyc->phys[port]->phy = phy;
		usbphyc->phys[port]->usbphyc = usbphyc;
		usbphyc->phys[port]->index = index;
		usbphyc->phys[port]->active = false;

		port++;
	पूर्ण

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev,
						     sपंचांग32_usbphyc_of_xlate);
	अगर (IS_ERR(phy_provider)) अणु
		ret = PTR_ERR(phy_provider);
		dev_err(dev, "failed to register phy provider: %d\n", ret);
		जाओ clk_disable;
	पूर्ण

	ret = sपंचांग32_usbphyc_clk48_रेजिस्टर(usbphyc);
	अगर (ret) अणु
		dev_err(dev, "failed to register ck_usbo_48m clock: %d\n", ret);
		जाओ clk_disable;
	पूर्ण

	version = पढ़ोl_relaxed(usbphyc->base + STM32_USBPHYC_VERSION);
	dev_info(dev, "registered rev:%lu.%lu\n",
		 FIELD_GET(MAJREV, version), FIELD_GET(MINREV, version));

	वापस 0;

put_child:
	of_node_put(child);
clk_disable:
	clk_disable_unprepare(usbphyc->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_usbphyc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_usbphyc *usbphyc = dev_get_drvdata(&pdev->dev);
	पूर्णांक port;

	/* Ensure PHYs are not active, to allow PLL disabling */
	क्रम (port = 0; port < usbphyc->nphys; port++)
		अगर (usbphyc->phys[port]->active)
			sपंचांग32_usbphyc_phy_निकास(usbphyc->phys[port]->phy);

	sपंचांग32_usbphyc_clk48_unरेजिस्टर(usbphyc);

	clk_disable_unprepare(usbphyc->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sपंचांग32_usbphyc_of_match[] = अणु
	अणु .compatible = "st,stm32mp1-usbphyc", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_usbphyc_of_match);

अटल काष्ठा platक्रमm_driver sपंचांग32_usbphyc_driver = अणु
	.probe = sपंचांग32_usbphyc_probe,
	.हटाओ = sपंचांग32_usbphyc_हटाओ,
	.driver = अणु
		.of_match_table = sपंचांग32_usbphyc_of_match,
		.name = "stm32-usbphyc",
	पूर्ण
पूर्ण;
module_platक्रमm_driver(sपंचांग32_usbphyc_driver);

MODULE_DESCRIPTION("STMicroelectronics STM32 USBPHYC driver");
MODULE_AUTHOR("Amelie Delaunay <amelie.delaunay@st.com>");
MODULE_LICENSE("GPL v2");
